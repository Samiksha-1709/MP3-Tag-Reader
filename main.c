/*
Name = Samiksha Mane

Description = The MP3 Tag Reader and Editor is a command-line based application developed in the C programming language
that allows users to view and modify metadata (ID3 tags) of MP3 audio files. The project works by directly reading and
manipulating the binary structure of MP3 files, specifically the ID3v2 tag frames, to extract and update information
such as title, artist, album, year, and genre.
*/


#include "main.h"

// Function to validate view option input
int view_mp3(int argc, char *file)
{
    // Check if correct number of arguments are passed
    if(argc == 3)
    {
        // Check if file is .mp3
        if(strstr(file, ".mp3"))
        {
            return 0;   // valid input
        }
        else
        {
            // Error if not mp3 file
            printf("\nError : Please provide only .mp3 file...\n");
            return 1;
        }
    }
    // Error for wrong argument format
    printf("\nError : Please Provide Following Options...\n");
    printf("\nUsage : ./a.out -v <file.mp3>\n");
    return 1;
}

// Function to validate edit option input
int edit_mp3(int argc, char *argv)
{
    // Check if correct number of arguments are passed
    if(argc == 5)
    {
        // Check if file is .mp3
        if(strstr(argv, ".mp3"))
        {
            return 0;   // valid input
        }
        else
        {
            // Error if not mp3 file
            printf("\nError : Please Provide only .mp3 file...\n");
            return 1;
        }

    }
    // Error for wrong argument format
    printf("\nError : Please Provide Following Options...\n");
    printf("\nUsage : ./a.out -e <file.mp3> -tag modified_value\n");
    return 1;
}

// Function to validate help option
int help_mp3(int argc, char *argv)
{
    // Check if only help argument is given
    if(argc == 2)
    {
        return 0;   // valid input
    }

    // Error for wrong usage
    printf("\nError : Please Provide Following Options...\n");
    printf("\nUsage : ./a.out -h\n");
    return 1;
}

// Main function starts execution
int main(int argc, char *argv[])
{
    struct Music M_Info;   // Declare structure variable

    // Check if arguments are >= 3
    if(argc >= 3)
    {
        // Check for view option
        if(strcmp(argv[1], "-v") == 0)
        {
            // Validate input
            if(view_mp3(argc, argv[2]) == 0)
            {
                printf("\nView Option Selected ✅\n");

                // Call function to display MP3 info
                get_mp3_info(argv[2], &M_Info);
            }
        }

        // Check for edit option
        else if(strcmp(argv[1], "-e") == 0)
        {
            // Validate input
            if(edit_mp3(argc, argv[2]) == 0)
            {
                printf("\nEdit Option Selected ✅\n");

                // Call function to edit MP3 tag
                write_mp3_info(argv[2], argv[3], argv[4], &M_Info);

                printf("\nEdited SuccessFully ✅\n");

                // Display updated info
                get_mp3_info(argv[2], &M_Info);
            }
        }

        // If wrong option is given
        else
        {
            printf("\nError : Wrong Option Selected.\n");
            printf("\nPlease Select The Proper Option.\n");

            // Show help menu
            show_help();
        }
    }

    // Check for help option
    else if(argc >= 2)
    {
        // If -h option is given
        if(strcmp(argv[1], "-h") == 0)
        {
            // Validate help input
            if(help_mp3(argc, argv[1]) == 0)
            {
                // Display help
                show_help();
            }
        }
        else
        {
            // Invalid argument message
            printf("\nInvalid Arguments...\n");
            printf("Usage : -v (view), -e (edit), -h (help)\n");
        }
    }

    // If no proper arguments
    else
    {
        printf("\nArguments are not proper... \n");

        // Show help
        show_help();
    }

    return 0;   // End of program
}