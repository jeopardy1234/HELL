#include "shell.h"

void AddNodeLL(bgpr *node, bgpr *head)
{
    if(head -> next == NULL)
    {
        head->next = node;
        node->next = NULL;
        return;
    }
    bgpr *prev = head;
    head = head->next;
    while(head != NULL)
    {
        if(strcmp(head->process, node->process) <= 0)
        {
            head = head->next;
            prev = prev->next;
        }
        else
        {
            prev->next = node;
            node->next = head;
            return ;
        }
    }
    prev->next = node;
    node->next = NULL;
}

void printLL(bgpr *head)
{
    //bgpr *head = head;
    head = head->next;
    while(head != NULL)
    {
        printf("%s\n", head->process);
        head = head->next;
        fflush(stdout);
    }
}

