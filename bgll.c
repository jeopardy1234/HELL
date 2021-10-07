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
    bgpr *prev = head;
    //head = head->next;
    while(head->next != NULL)
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
        head = head->next;
        // prev = prev->next;
    }
    // prev->next = node;
    // node->next = NULL;

    head->next = node;
    node->next = NULL;
}

void printLL(bgpr *head)
{
    head = head->next;
    while(head != NULL)
    {
        printf("%s\n", head->process);
        head = head->next;
    }
}