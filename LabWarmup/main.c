/*
 * File: main.c
 * Author: Karter Melad
 * Date: Thu 18 Oct 2023 10:07 PM
 * Description: LabWarmup main file
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "ContactNode.h"

void NewLineTrim(char * line);

int main(void) {

   char fullName[50] = "";
   char phoneNum[50] = "";
   int rc;
   const int NUM_CONTACTS = 3;

   ContactNode * headNode = NULL;
   ContactNode * tailNode = NULL;
   ContactNode * currentNode = NULL;
  
   // Contact entry loop
   for(int i = 0;i < NUM_CONTACTS; i++) {

      printf("Person %d\n", i+1);
      printf("Enter name:\n");
      fgets(fullName, 50, stdin);
      NewLineTrim(fullName);
      printf("Enter phone number:\n");
      fgets(phoneNum, 50, stdin);
      NewLineTrim(phoneNum);
      printf("You entered: %s, %s\n\n", fullName, phoneNum);

      // Create ContactNode and verify
      currentNode = CreateContactNode(fullName, phoneNum);
      if(currentNode == NULL) {
         printf("Error: Unable to create node...\n");
         printf("Name: %s\n", fullName);
         printf("Phone Number: %s\n", phoneNum);
         return -1;
      }

      // Check if this is the first node in the list
      if(headNode == NULL) {
         headNode = currentNode;
         tailNode = currentNode;
      } else {
         rc = InsertContactAfter(tailNode, currentNode);
         if(rc < 0) {
            printf("Error: Unable to insert node into list...\n");
            PrintContactNode(currentNode);
            return -1;
         }
         tailNode = currentNode;
      }
   }

   // Print contact list
   printf("CONTACT LIST\n");
   currentNode = headNode;
   while(currentNode != NULL) {
      PrintContactNode(currentNode);
      currentNode = GetNextContact(currentNode);
      printf("\n");
   }

   // Clean up the nodes in the list
   currentNode = headNode;
   ContactNode * nextNode;
   while(currentNode != NULL) {
      nextNode = GetNextContact(currentNode);
      DestroyContactNode(currentNode);
      currentNode = nextNode;
   }

   return 0;
}

void BufferPurge(void) {
   char c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
   }
}

/*
 * NewLineTrim: Remove the trailing newline
 *    character from strings returned from fgets.
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