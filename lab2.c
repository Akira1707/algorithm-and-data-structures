#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define ALPHABET_SIZE 26

struct People{
	char name[MAX_NAME_LENGTH];
	char phone[MAX_PHONE_LENGTH];
	struct People* next;
};

struct PeopleList{
	struct People* head;
};

struct PhoneBook{
	struct PeopleList alphabet[ALPHABET_SIZE];
};

void initPhoneBook(struct PhoneBook* phonebook){
	int i;
	for (i = 0; i< ALPHABET_SIZE; i++){
		phonebook->alphabet[i].head = NULL;
	}
}
void addPeople(struct PhoneBook* phonebook, const char* name, const char* phone){
	struct PeopleList* list;
	int index = name[0] - 65;
	list = &phonebook->alphabet[index];
	
	struct People* newPeople = (struct People*)malloc(sizeof(struct People));
	if (newPeople == NULL){
		printf("Memory allocation error");
		return;
	}
	strcpy(newPeople->name,name);
	strcpy(newPeople->phone, phone);
	newPeople->next = list->head;
	list->head = newPeople;
}

struct People* findPeople(struct PhoneBook* phonebook, const char* name){
	struct PeopleList* list;
	int index = name[0] - 65;
	list = &phonebook->alphabet[index];
	struct People* current = list->head;
	while(current!= NULL){
		if (strcmp(current->name, name) == 0){
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void deletePeople(struct PhoneBook* phonebook, const char* name){
	struct PeopleList* list;
	int index = name[0] - 65;
	list = &phonebook->alphabet[index];
	struct People* current = list->head;
	struct People* prev = NULL;
	
	while(current!=NULL){
		if (strcmp(current->name,name)==0){
			if(prev != NULL){
				prev->next = current->next;
			}else{
				list->head = current->next;
			}
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void sortPhoneBook(struct PhoneBook* phonebook) {
	struct PeopleList* list;
	int i;
	
	for(i=0; i<ALPHABET_SIZE; i++){
		list = &phonebook->alphabet[i];
        struct People* current = list->head;
        struct People* sortedList = NULL; 
        struct People* next;

        while (current != NULL) {
            next = current->next;
            insertPeopleSorted(&sortedList, current); 
            current = next;
        }
        list->head = sortedList;
    } 
}
	
void insertPeopleSorted(struct People** sortedList, struct People* newPeople) {
    struct People* current;    
    if (*sortedList == NULL || strcmp(newPeople->name, (*sortedList)->name) <= 0) {
        newPeople->next = *sortedList;
        *sortedList = newPeople;
    } else {        
        current = *sortedList;
        while (current->next != NULL && strcmp(newPeople->name, current->next->name) > 0) {
            current = current->next;
        }
        newPeople->next = current->next;
        current->next = newPeople;
    }
}
void savePhoneBook(struct PhoneBook* phonebook, const char* filename){
	FILE* file = fopen(filename,"wb");
	if (file == NULL){
		printf("Failed to open file");
		return;
	}
	
	struct PeopleList* list;
	struct People* current;
	int i;
	
	for(i=0; i<ALPHABET_SIZE;i++){
		list =  &phonebook->alphabet[i];
		current = list->head;
		while(current != NULL){
			fwrite(current, sizeof(struct People), 1, file);
			current = current->next;
		}
	}
	fclose(file);
}

void loadPhoneBook(struct PhoneBook* phonebook, const char* filename){
	FILE* file = fopen(filename,"rb");
	if (file == NULL){
		printf("Failed to open file");
		exit(1);
	}
	
	initPhoneBook(phonebook);
	struct People people;
	while (fread(&people, sizeof(struct People), 1, file) == 1) {
		char first = people.name[0];
		int index = first - 65;
		addPeople(&phonebook->alphabet[index],people.name,people.phone);
	}
	fclose(file);
}

int main(){
	struct PhoneBook phonebook;
	initPhoneBook(&phonebook);
	
	loadPhoneBook(&phonebook, "phonebook.txt");
	addPeople(&phonebook, "Trinh", "09227282882");
	
	struct People* foundPeople = findPeople(&phonebook, "Trinh");
    if (foundPeople != NULL) {
        printf("Found: %s - %s\n", foundPeople->name, foundPeople->phone);
    } else {
        printf("Not found.\n");
    }
    
    deletePeople(&phonebook, "Trinh");
    sortPhoneBook(&phonebook);
    savePhoneBook(&phonebook, "phonebook.txt");
    
    return 0;
}





