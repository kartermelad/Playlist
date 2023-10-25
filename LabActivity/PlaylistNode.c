/*
 * File: PlaylistNode.c
 * Author: Karter Melad
 * Date: Wed 18 Oct 2023 11:30 PM
 * Description: Lab Activity file to support the
 *      given PlaylistNode.h file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PlaylistNode.h"

PlaylistNode* CreatePlaylistNode(char id[], char songName[], char artistName[], int songLength) {

    PlaylistNode * thisNode = (PlaylistNode *)malloc(sizeof(PlaylistNode));

    if(thisNode == NULL) {
        return NULL;
    }

    strncpy(thisNode->uniqueID, id, 50);
    strncpy(thisNode->songName, songName, 50);
    strncpy(thisNode->artistName, artistName, 50);
    thisNode->songLength = songLength;
    thisNode->nextNodePtr = NULL;

    return thisNode;
}

int InsertPlaylistNodeAfter(PlaylistNode* nodeInList, PlaylistNode* newNode) {
    PlaylistNode* tempNext = NULL;

    if(nodeInList == NULL || newNode == NULL) {
        return -1;
    }

    tempNext = nodeInList->nextNodePtr;
    nodeInList->nextNodePtr = newNode;
    newNode->nextNodePtr = tempNext;

    return 0;
}

int SetNextPlaylistNode(PlaylistNode* nodeInList, PlaylistNode* newNode) {
    if(nodeInList == NULL) {
        return -1;
    }
    nodeInList->nextNodePtr = newNode;

    return 0;
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* nodeInList) {
    if(nodeInList == NULL) {
        return NULL;
    }
    return nodeInList->nextNodePtr;
}

void PrintPlaylistNode(PlaylistNode* thisNode) {
    printf("Unique ID: %s\n", thisNode->uniqueID);
    printf("Song Name: %s\n", thisNode->songName);
    printf("Artist Name: %s\n", thisNode->artistName);
    printf("Song Length (in seconds): %d\n", thisNode->songLength);
    return;
}

void DestroyPlaylistNode(PlaylistNode* thisNode) {
    if(thisNode == NULL) {
        return;
    }
    free(thisNode);
}
