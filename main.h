#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<string.h>

//structure to store MP3 tag details
struct Music
{
    //tag name (dx :TPE1 TIT2, TALB,TYEAR,TCON)
    char tag[5];   
    int size;  //size of frame
    char flag[3];  //flags of frame
    char data[600];  //data frame
};

//convert big to little endian
void convert_size(int *size);

//read 4 byte tag from file
void read_tag(struct Music *info, FILE *fptr);

//read frame size from file
void read_size(struct Music *info, FILE *fptr);

//read frame data from file
void read_data(struct Music *info, FILE *fptr);

//display MP3 tag information
void get_mp3_info(char *file, struct Music *info);

//edit MP3 tag information
void write_mp3_info(char *file, char *opt, char *modify, struct Music *info);

//display help menu
void show_help();

//funtion to handle view option
int view_mp3(int argc, char *file);

//function to handle edit option
int edit_mp3(int argc, char *argv);

//function to handle help function
int help(int argc, char *argv);



#endif