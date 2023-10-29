#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Line{
    char word[50];
    int key;
    struct Line *next;
};

//Function for displaying a list on the screen
void printLines(struct Line* head){
	struct Line* current = head;
	while (current != NULL){
		printf("%s %d\n", current->word, current->key);
		current = current->next;
	}
}

// Function to insert an element into a sorted list
int insertLine(struct Line** head, char word[50], int key){
	struct Line* newLine = (struct Line*)malloc(sizeof(struct Line));
	
	strcpy(newLine->word, word);
	newLine->key = key;
	newLine->next = NULL;
	
	if (*head == NULL || key < (*head)->key){
		newLine->next = *head;
		*head = newLine;
				
	}else{
		struct Line* current = *head;
		while (current->next != NULL && key>= current->next->key){
			if (key == current->next->key) {
                return 1;
           }   
			current = current->next;			
		}
		
		newLine->next = current->next;
		current->next = newLine;
	}
	return 0;
}

//Function to check the presence of a word by key number
int searchByKey(struct Line* head, int key){
	struct Line* current = head;
	while (current != NULL){
		if (current->key == key){
			printf("Word corresponding to key number %d: %s\n",key,current->word);
			return -1;
		}
		current = current->next;
	}
	printf("Word with key number %d not found.\n",key);
	return 0;
}
void Free(struct Line* head){
	struct Line* temp;
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main(){
	struct Line* head = NULL;
	char word[50];
	int key;
	int error;
	FILE* file = fopen("input.txt","r");
	
	if (file == NULL){
		printf("Failed to open file\n");
		return 1;
	}
	
	while (fscanf(file, "%s %d",word,&key)!=EOF){
		error = insertLine(&head,word,key);
		if(error==1){
			printf("Error: duplicate keywords\n");
			fclose(file);
			return 0;
		}
	}
	
	fclose(file);
	
	printf("Print list of lines:\n");
	printLines(head);
	
	int searchKey;
	printf("Enter the key number to search: ");
	scanf("%d", &searchKey);
	searchByKey(head, searchKey);
	
	Free(head);
	return 0;
}
