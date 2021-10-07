#include "shell.h"

void AddNodeLL(bgpr *node, bgpr *head)
{

    // if(head -> next == NULL)
    // {
    //     //printf("first,\n");
    //     head->next = node;
    //     node->next = NULL;
    //     //printf("%d\n", node->job_number);
    //     //printf("%d\n", head->next);
    //     return;
    // }
    bgpr *temp = head;
    //head = head->next;
    while(temp->next != NULL)
    {
        //printf("%s\n" , head->process);
        // if(strcmp(head->process, node->process) <= 0)
        // {
        //     printf("less");
        //     head = head->next;
        //     prev = prev->next;
        // }
        // else
        // {
        //     printf("more\n");
        //     prev->next = node;
        //     node->next = head;
        //     return ;
        // }
        temp = temp->next;
        // prev = prev->next;
    }
    // prev->next = node;
    // node->next = NULL;

    temp->next = node;
    node->next = NULL;
}

void printLL(bgpr *head)
{
    bgpr *temp = head;
    temp = temp->next;
    while(temp != NULL)
    {
        printf("%s\n", temp->process);
        temp = temp->next;
        fflush(stdout);
    }
}