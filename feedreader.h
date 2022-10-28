#ifndef _FEEDREADER_H_
#define _FEEDREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_handling.h"
#include "xml.h"
#include "ssl.h"

#define is ==

#define FEED_END 66 
#define TMP_FILENAME "_tmp.feedreader"

int write_time;
int write_author;
int write_url;
char *certfile;
char *certaddr;
char *url;
char *feedfile;

#endif