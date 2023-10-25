/*
 * File: main.c
 * Author: Karter Melad
 * Date: Thu 18 Oct 2023 12:22 AM
 * Description: Lab Activity main file
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PlaylistNode.h"

void NewLineTrim(char * line);

void BufferPurge(void) {
    char c = getchar();
    while(c != '\n' && c != EOF) {
        c = getchar();
    }
}

int main(void) {

    // Initialize and declare variables
    char title[50];
    int quit = 0;
    char menuOption;
    int length = 0;
    int quantity = 0;
    
    PlaylistNode * head = NULL;
    PlaylistNode * tail = NULL;
    PlaylistNode * current = NULL;
    PlaylistNode * last = NULL;

    PlaylistNode node;

    printf("Enter playlist's title:\n");
    fgets(title, 50, stdin);
    NewLineTrim(title);
    printf("\n");

    // Create menu with user options
    while(quit != 1) {
        printf("%s PLAYLIST MENU\n", title);
        printf("a - Add song\n");
        printf("r - Remove song\n");
        printf("c - Change position of song\n");
        printf("s - Output songs by specific artist\n");
        printf("t - Output total time of playlist (in seconds)\n");
        printf("o - Output full playlist\n");
        printf("q - Quit\n\n");
        printf("Choose an option: ");
        scanf(" %c", &menuOption);
        printf("\n");

        switch(menuOption) {
            // Outputs the full playlist
            case 'O':
            case 'o': {
                printf("OUTPUT FULL PLAYLIST\n");
                int i = 1;
                if(quantity == 0) {
                    printf("Playlist is empty :(\n\n");
                } else {
                    current = head;
                    while(current != NULL) {
                        printf("%d.\n", i);
                        PrintPlaylistNode(current);
                        printf("\n");
                        current = GetNextPlaylistNode(current);
                        i++;
                    }
                }
                break;
            }
            // Outputs the total time of the full playlist
            case 'T':
            case 't': {
                printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
                current = head;
                while(current != NULL) {
                    length += current->songLength;
                    current = GetNextPlaylistNode(current);
                }
                printf("Total time: %d seconds\n\n", length);
                break;
            }
            // Outputs songs from a specific artist
            case 'S':
            case 's': {
                BufferPurge();
                printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
                printf("Enter artist's name: ");
                int k = 1;
                fgets(node.uniqueID, 50, stdin);
                NewLineTrim(node.uniqueID);
                current = head;
                printf("\n");
                while(current != NULL) {
                    if(strcmp(node.uniqueID, current->artistName)== 0) {
                        printf("%d.\n", k);
                        PrintPlaylistNode(current);
                        printf("\n");
                    }
                    k++;
                    current = GetNextPlaylistNode(current);
                }
                break;
            }
            // Change the position of a song in the playlist
            case 'C':
            case 'c': {
                BufferPurge();
                printf("CHANGE POSITION OF SONG\n");
                int song1 = 0;
                int song2 = 0;
                int numSongs = 0;
                int d = 0;
                PlaylistNode* c = NULL;
                PlaylistNode* p = NULL;
                PlaylistNode* a = NULL;

                printf("Enter song's current position: ");
                scanf(" %d", &song1);
                printf("Enter a new position for song: ");
                scanf(" %d", &song2);
                d = song1 - song2;

                current = head;

                while(current != NULL) {
                    numSongs++;
                    current = GetNextPlaylistNode(current);
                    if(GetNextPlaylistNode(current)== NULL) {
                        tail = current;
                    }
                }

                if(song2 > numSongs) {
                    song2 = numSongs;
                }

                current = head;
                for(int i = 1; i < song1; i++) {
                    if(i + 1 == song1) {
                        p = current;
                    }
                    current = GetNextPlaylistNode(current);
                }
                c = current;

                if(song2 == 0) {
                    p->nextNodePtr = current->nextNodePtr;
                    c = head;
                    head = current;
                    head->nextNodePtr = c;
                }
                else if(d > 0) {
                    if(current == head) {
                        for(int i = 1; i < song2; i++) {
                            current = GetNextPlaylistNode(current);
                        }
                        a = GetNextPlaylistNode(head);
                        InsertPlaylistNodeAfter(current, head);
                        head = a;
                    }
                }
                break;
            }
            // Remove a song from the playlist
            case 'R':
            case 'r': {
                BufferPurge();
                printf("REMOVE SONG\n");
                printf("Enter song's unique ID:\n");
                fgets(node.uniqueID, 50, stdin);
                NewLineTrim(node.uniqueID);
                current = head;
                if(strcmp(node.uniqueID, head->uniqueID)== 0) {
                    printf("\"%s\" removed.\n\n", head->songName);
                    head = GetNextPlaylistNode(head);
                } else {
                    while(current != NULL) {
                        if(strcmp(current->uniqueID, node.uniqueID)== 0) {
                            strcpy(node.songName, current->songName);
                        }
                        current = GetNextPlaylistNode(current);
                    }
                    DestroyPlaylistNode(head);
                    printf("\"%s\" removed.\n\n", node.songName);
                }
                quantity--;
                break;
            }
            // Add a song to the playlist
            case 'A':
            case 'a': {
                BufferPurge();
                printf("ADD SONG\n");
                printf("Enter song's unique ID:\n");
                fgets(node.uniqueID, 50, stdin);
                NewLineTrim(node.uniqueID);
                printf("Enter song's name:\n");
                fgets(node.songName, 50, stdin);
                NewLineTrim(node.songName);
                printf("Enter artist's name:\n");
                fgets(node.artistName, 50, stdin);
                NewLineTrim(node.artistName);
                printf("Enter song's length (in seconds):\n");
                scanf("%d", &node.songLength);
                printf("\n");

                current = CreatePlaylistNode(node.uniqueID, node.songName, node.artistName, node.songLength);

                if(quantity == 0) {
                    head = current;
                    last = head;
                } else {
                    InsertPlaylistNodeAfter(last, current);
                    last = current;
                }
                quantity++;
                break;
            }
            // Close the menu and program
            case 'Q':
            case 'q': {
                printf("Goodbye friend!\n");
                quit = 1;
                break;
            }
        }
    }
}

/*
 * NewLineTrim: Remoe the trailing newline
 *  character from strings returned from fgets.
 * line - NULL terminated string
 */
void NewLineTrim(char * line) {
    size_t lineLength;
    if(line == NULL) {
        return;
    }
    lineLength = strlen(line);
    if(line[lineLength - 1] == '\n') {
        line[lineLength - 1] = '\0';
    }
}