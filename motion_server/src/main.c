/*
 * main.c
 *
 *  Created on: 3 mai 2014
 *      Author: essoussi
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

#define READ_BUFFER_SIZE 128

#include <gst/gst.h>
#include <glib.h>

GMainLoop *loop;
GstElement *pipeline;
guint bus_watch_id;
int playing = 0;

#define AUDIO_FILE_NAME "katusha.ogg"

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data)
{
	GMainLoop *loop = (GMainLoop *) data;

	switch (GST_MESSAGE_TYPE(msg))
	{

	case GST_MESSAGE_EOS:
		g_print("[INFO AUDIO] End of stream\n");
		g_main_loop_quit(loop);
		break;

	case GST_MESSAGE_ERROR:
	{
		gchar *debug;
		GError * error;

		gst_message_parse_error(msg, &error, &debug);
		g_free(debug);

		g_printerr("[ERROR AUDIO] Error: %s\n", error->message);
		g_error_free(error);

		g_main_loop_quit(loop);
		break;
	}
	default:
		break;
	}

	return TRUE;
}

static void on_pad_added(GstElement *element, GstPad *pad, gpointer data)
{
	GstPad *sinkpad;
	GstElement *decoder = (GstElement *) data;

	/* We can now link this pad with the vorbis-decoder sink pad */
	g_print("[INFO AUDIO] Dynamic pad created, linking demuxer/decoder\n");

	sinkpad = gst_element_get_static_pad(decoder, "sink");

	gst_pad_link(pad, sinkpad);

	gst_object_unref(sinkpad);
}

int init_audio_player(int argc, char* argv[])
{

	GstElement *source, *demuxer, *decoder, *conv, *sink;
	GstBus *bus;

	/* Initialisation */
	gst_init(&argc, &argv);

	loop = g_main_loop_new(NULL, FALSE);

	/* Create gstreamer elements */
	pipeline = gst_pipeline_new("audio-player");
	source = gst_element_factory_make("filesrc", "file-source");
	demuxer = gst_element_factory_make("oggdemux", "ogg-demuxer");
	decoder = gst_element_factory_make("vorbisdec", "vorbis-decoder");
	conv = gst_element_factory_make("audioconvert", "converter");
	sink = gst_element_factory_make("autoaudiosink", "audio-output");

	if (!pipeline || !source || !demuxer || !decoder || !conv || !sink)
	{
		g_printerr(
				"[ERROR AUDIO] One element could not be created. Exiting.\n");
		return -1;
	}

	/* Set up the pipeline */

	/* we set the input filename to the source element */
	g_object_set(G_OBJECT(source), "location", AUDIO_FILE_NAME, NULL);

	/* we add a message handler */
	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);
	gst_object_unref(bus);

	/* we add all elements into the pipeline */
	/* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
	gst_bin_add_many(GST_BIN(pipeline), source, demuxer, decoder, conv, sink,
	NULL);

	/* we link the elements together */
	/* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
	gst_element_link(source, demuxer);
	gst_element_link_many(decoder, conv, sink, NULL);
	g_signal_connect(demuxer, "pad-added", G_CALLBACK(on_pad_added), decoder);

	return 0; /* success */

}

void* play(void* args)
{
	if (playing == 0)
	{
		playing = 1;

		/* Set the pipeline to "playing" state*/
		g_print("[INFO AUDIO] Now playing: %s\n", AUDIO_FILE_NAME);
		gst_element_set_state(pipeline, GST_STATE_PLAYING);

		/* Iterate */
		g_print("[INFO AUDIO] Running...\n");
		g_main_loop_run(loop);

		/* Out of the main loop, clean up nicely */
		g_print("[INFO AUDIO] Returned, stopping playback\n");
		gst_element_set_state(pipeline, GST_STATE_NULL);

		g_print("[INFO AUDIO] Deleting pipeline\n");
		gst_object_unref(GST_OBJECT(pipeline));
		g_main_loop_unref(loop);
		playing = 0;
	}
	else
	{
		g_print("[INFO AUDIO] already playing ... \n");
	}
	pthread_exit(0);
}

int main(int argc, char* argv[])
{
	int listeningSocket, dataSocket;
	pthread_t player_thread;
	size_t _read = 0;
	FILE* motionLog = NULL;
	char readBuffer[READ_BUFFER_SIZE] = {0};

	/* Create the listening connection socket */
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == -1)
	{
		perror("socket()");
		exit(errno);
	}

	/* Description of the listening socket */
	struct sockaddr_in sin =
	{ 0 };
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(0xA380);

	/* Binding the socket*/
	if (bind(listeningSocket, (struct sockaddr *) &sin, sizeof(sin)) == -1)
	{
		perror("[ERROR] bind:");
		exit(errno);
	}

	/*Initialize the audio player  */
	if (init_audio_player(argc, argv) == -1)
	{
		fprintf(stderr,
				"[WARNING] Error while initializing the audio player\n");
	}
	while (1)
	{
		/* Open the motionLog in writing mode */
		motionLog = fopen("/var/www/hesdom.com/motionLog.txt", "a+");

		if (motionLog == NULL)
		{
			perror("[ERROR] fopen: ");
			exit(errno);
		}

		/* Listening to only one client */
		printf("===================================================\n");
		printf("[INFO] Listening to connections ... \n");
		if (listen(listeningSocket, 1) == -1)
		{
			perror("listen()");
			exit(errno);
		}

		/* Accepting the data socket*/
		memset(&sin, 0, sizeof(sin));
		socklen_t sinsize = sizeof(sin);

		dataSocket = accept(listeningSocket, (struct sockaddr *) &sin,
				&sinsize);
		if (dataSocket == -1)
		{
			perror("[ERROR] accept:");
			exit(errno);
		}

		printf("[INFO] A client has been connected\n");

		while ((_read = read(dataSocket, readBuffer, sizeof(readBuffer))) != -1)
		{
			if (_read == 0)
			{
				/* The client has disconnected, relistening */
				printf("[WARNING] The client has disconnected. \n");
				break;
			}
			else
			{
				/* Write in file the data */
				if (fputs(readBuffer, motionLog) < 0)
				{
					perror("[ERROR] fputs:");
					fprintf(stderr, "[WARNING] Continue anyway .. \n");
				}
				/* Play the music */
				pthread_create(&player_thread, 0, play, NULL);
				pthread_detach(player_thread);
			}
			/* reinit the buffer */
			memset(readBuffer,0, sizeof(readBuffer));
		}

		if (_read == -1)
		{
			fprintf(stderr, "[ERROR] %s\n", strerror(errno));
		}

		/* Close sockets */
		if (close(dataSocket) == -1)
		{
			fprintf(stderr, "[ERROR] %s\n", strerror(errno));
		}

		/* Close log file */
		if (fclose(motionLog) == EOF)
		{
			perror("[ERROR] fclose: ");
		}

		/* Restarting the server (infinite loop)*/
		printf("\n\n >>> Restarting the server ... \n\n");

	}
	close(listeningSocket);

	return EXIT_SUCCESS;
}

