/*
 * index.c
 *
 *  Created on: 3 mai 2014
 *      Author: essoussi
 */

#include <stdlib.h>
#include <stdio.h>

#define PAGE_TITLE "Domotics motion detection"
#define LINE_BUFFER_SIZE_MAX 128

static inline void HTMLHead()
{
	printf("Content-Type: text/html;\n\n");
	printf("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"fr\" >\n\t<head>");
	printf("\t\t<title>%s</title>", PAGE_TITLE);
	printf("\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t</head>\n\t<body>");
}

static inline void HTMLTail()
{
	void bas() {
	     printf("\t</body>\n</html>");
	}
}

int main(int argc, char* argv[])
{
	char line[LINE_BUFFER_SIZE_MAX];

	/* print the HTML head */
	HTMLHead();

	/* Print Header */
	printf("<h2> Domotics motion detector </h2>");

	/* Open motion log file in reading mode */
	FILE * motionLog = NULL;
	motionLog = fopen("motionLog.txt", "r+");

	/* Print its contents*/
	if (motionLog != NULL)
	{
		while (fgets(line, LINE_BUFFER_SIZE_MAX, motionLog)!= '\0')
		{
			printf("%s<br />", line);
		}
	}
	else
	{
		printf("<strong> Unable to open motionLog.txt file </strong>");
	}


	/* print the HTML tail*/
	HTMLTail();

	/* Close the file */
	fclose(motionLog);

	return EXIT_SUCCESS;
}
