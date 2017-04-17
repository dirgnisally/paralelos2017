#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct list_node_s {
	int data;
	struct list_node_s *next;
};

int Member(int value, struct list_node_s *head_p) {
	struct list_node_s *curr_p = head_p;
	
	while (curr_p != NULL && curr_p−>data < value)
	curr_p = curr_p−>next;
	
	if (curr_p == NULL || curr_p−>data > value) {
		return 0;
	} else {
	return 1;
	}
};

int main(int argc, char **argv)
{
	return 0;
}
