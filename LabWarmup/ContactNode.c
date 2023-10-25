/*
 * File: ContactNode.c
 * Author: Karter Melad
 * Date: Wed 18 Oct 2023 09:41 PM
 * Description: Provides functionality to the 
 *    ContactNode.h file functions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ContactNode.h"

ContactNode* CreateContactNode(char name[], char phoneNumInit[]) {

   ContactNode * thisNode = (ContactNode *)malloc(sizeof(ContactNode));

   if(thisNode == NULL) {
      return NULL;
   }

   strncpy(thisNode->contactName, name, CONTACT_FIELD_SIZE);
   strncpy(thisNode->contactPhoneNum, phoneNumInit, CONTACT_FIELD_SIZE);
   thisNode->nextNodePtr = NULL;

   return thisNode;
}

int InsertContactAfter(ContactNode* nodeInList, ContactNode* newNode) {
   ContactNode* tempNext = NULL;

   if(nodeInList == NULL || newNode == NULL) {
      return -1;
   }

   tempNext = nodeInList->nextNodePtr;
   nodeInList->nextNodePtr = newNode;
   newNode->nextNodePtr = tempNext;

   return 0;
}

ContactNode* GetNextContact(ContactNode* nodeInList) {

   if(nodeInList == NULL) {
      return NULL;
   }
   return nodeInList->nextNodePtr;
}

void PrintContactNode(ContactNode* thisNode) {

   if(thisNode == NULL) {
      return;
   }

   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n", thisNode->contactPhoneNum);

   return;
}

void DestroyContactNode(ContactNode* thisNode) {
   if (thisNode == NULL) {
      return;
   }
   free(thisNode);
}