// Include standard input-output library
#include <stdio.h>

// Include string handling library
#include <string.h>

// Include header file for structure and declarations
#include "main.h"

// Function to read next 4 bytes (frame tag)
void read_tag(struct Music *info, FILE *fptr)
{
    fread(info->tag, 4, 1, fptr);   // Read 4-byte tag from file
    info->tag[4] = '\0';            // Null terminate tag string
}

// Function to read frame size and convert endian
void read_size(struct Music *info, FILE *fptr)
{
    fread(&info->size, 4, 1, fptr);         // Read 4-byte size
    convert_size(&(info->size));            // Convert big endian to little endian
}

// Function to convert big endian to little endian
void convert_size(int *size)
{
    char *c = (char*)size;                  // Treat integer as byte array

    for(int i = 0; i < 2; i++)              // Swap bytes
    {
        char temp = c[i];                  // Store current byte
        c[i] = c[3-i];                     // Swap with opposite byte
        c[3 - i] = temp;                   // Complete swap
    }
}

// Function to read frame data and skip encoding byte
void read_data(struct Music *info, FILE *fptr)
{
    // Check for invalid or large size
    if(info->size <= 0 || info->size > 100)
    {
        fseek(fptr, info->size, SEEK_CUR); // Skip invalid frame
        return;
    }

    char buffer[info->size];               // Temporary buffer

    fread(buffer, info->size, 1, fptr);    // Read full frame data

    int data_len = info->size - 1;         // Actual data length (skip encoding byte)

    memcpy(info->data, buffer + 1, data_len); // Copy data excluding encoding byte
    info->data[data_len] = '\0';              // Add null terminator
}

// Function to extract and display MP3 tag information
void get_mp3_info(char *file, struct Music *info)
{
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MP3 TAG READER AND EDITOR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *fptr = fopen(file, "rb");       // Open file in binary mode

    // Check if file opened successfully
    if(fptr == NULL)
    {
        printf("Error: File Not Found.\n");     // Error message
        printf("Please Provide a .mp3 file.\n");
        return;
    }

    fseek(fptr, 10, SEEK_SET);            // Skip 10-byte ID3 header

    // Loop through frames
    while(1)
    {
        read_tag(info, fptr);             // Read frame tag

        if(feof(fptr))                   // Check end of file
            break;

        read_size(info, fptr);           // Read frame size

        fseek(fptr, 2, SEEK_CUR);        // Skip 2-byte flags

        // Check and print tag names
        if(strcmp(info->tag, "TIT2") == 0)
            printf("\tTitle   -> ");

        else if(strcmp(info->tag, "TALB") == 0)
            printf("\tAlbum   -> ");

        else if(strcmp(info->tag, "TPE1") == 0)
            printf("\tArtist  -> ");

        else if(strcmp(info->tag, "TYER") == 0)
            printf("\tYear    -> ");

        else if(strcmp(info->tag, "TCON") == 0)
            printf("\tGenre   -> ");

        else
        {
            fseek(fptr, info->size, SEEK_CUR); // Skip unwanted frames
            continue;
        }

        read_data(info, fptr);            // Read actual data

        printf("%s\n", info->data);       // Print tag value
    }

    fclose(fptr);                         // Close file
}