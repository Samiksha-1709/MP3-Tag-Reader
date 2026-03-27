// Include header file for structure and function declarations
#include "main.h"

// Function to edit the tag in MP3 file
void write_mp3_info(char *file, char *opt, char *modify, struct Music *info)
{
    char tag[5];   // Variable to store frame tag

    // Map user option to ID3 frame tag
    if (strcmp(opt, "-t") == 0)
        strcpy(tag, "TIT2");   // Title
    else if (strcmp(opt, "-A") == 0)
        strcpy(tag, "TALB");   // Album
    else if (strcmp(opt, "-a") == 0)
        strcpy(tag, "TPE1");   // Artist
    else if (strcmp(opt, "-y") == 0)
        strcpy(tag, "TYER");   // Year
    else if (strcmp(opt, "-C") == 0)
        strcpy(tag, "COMM");   // Comment
    else if (strcmp(opt, "-c") == 0)
        strcpy(tag, "TCON");   // Genre
    else
    {
        printf("\nError : Invalid Tag Option Selected ❌.\n"); // Invalid option
        return;
    }

    // Open original file in read binary mode
    FILE *fp = fopen(file, "rb");

    // Check if file exists
    if(fp == NULL)
    {
        printf("\nError : File Not Found❌.\n");
        return;
    }

    // Open temporary file in write binary mode
    FILE *op = fopen("sample.mp3", "wb");

    // Copy first 10 bytes (ID3 header)
    char buf[10];
    fread(buf, 10, 1, fp);     // Read header
    fwrite(buf, 10, 1, op);    // Write header

    // Loop through first 6 frames
    for(int i = 0; i < 6; i++)
    {
        read_tag(info, fp);    // Read frame tag
        read_size(info, fp);   // Read frame size

        fread(info->flag, 2, 1, fp);  // Read 2-byte flags

        // Check if this is the tag to modify
        if(strcmp(tag, info->tag) == 0)
        {
            fwrite(info->tag, 4, 1, op);  // Write tag

            int new_size = strlen(modify) + 1;   // New size (+ encoding byte)
            int size_copy = new_size;

            convert_size(&size_copy);            // Convert to big endian

            fwrite(&size_copy, 4, 1, op);        // Write new size
            fwrite(info->flag, 2, 1, op);        // Write flags

            char encoding = 0;                   // Encoding byte
            fwrite(&encoding, 1, 1, op);

            fwrite(modify, strlen(modify)+1, 1, op); // Write modified data

            fseek(fp, info->size, SEEK_CUR);     // Skip old data

            printf("\nTag Modified Successfully ✅.\n");

            break;   // Stop loop after editing
        }
        else
        {
            fwrite(info->tag, 4, 1, op);         // Write tag

            int temp_size = info->size;
            int size_copy = temp_size;

            convert_size(&size_copy);            // Convert size

            fwrite(&size_copy, 4, 1, op);        // Write size
            fwrite(info->flag, 2, 1, op);        // Write flags

            char buffer[temp_size];              // Buffer to store frame data

            fread(buffer, temp_size, 1, fp);     // Read original data
            fwrite(buffer, temp_size, 1, op);    // Write original data
        }
    }

    // Copy remaining data after frames
    char copy[1024];
    int bytes;

    while((bytes = fread(copy, 1, sizeof(copy), fp)) > 0)
    {
        fwrite(copy, 1, bytes, op);   // Copy rest of file
    }

    fclose(fp);   // Close original file
    fclose(op);   // Close temp file

    remove(file);                 // Delete original file
    rename("sample.mp3", file);   // Rename temp to original
}