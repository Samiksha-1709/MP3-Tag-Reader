#include "main.h"

void show_help()
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MP3 TAG READER AND EDITOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Options:\n");
    printf("\t  -v <file.mp3>               View MP3 tags\n");
    printf("\t  -e <file.mp3> -tag <value>  Edit specific tag\n");
    printf("\t  -h                          Show help menu\n");

    printf("\n   Following  Tags For Editing:\n");
    printf("  -t : Title\n");
    printf("  -A : Album\n");
    printf("  -a : Artist\n");
    printf("  -y : Year\n");
    printf("  -C : Genre\n");
    printf("  -c : Content\n");
}