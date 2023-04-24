#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

typedef struct game_node {
    char* title;
    char* genre;
    int year;
    float rating;
    struct game_node* next;
    struct dlc_node* dlc_head;
} GameNode;

typedef struct dlc_node {
    char* title;
    float price;
    struct dlc_node* next;
} DLCNode;

typedef struct {
    GameNode* head;
} GameLinkedList;

GameNode *create_game_node(char *title, char *genre, int year, float rating);
GameNode *insert_game_at_end(GameNode *head, char *title, char *genre, int year, float rating);
DLCNode *create_dlc_node(char *title, float price, DLCNode *next);
void destroy_list(GameLinkedList *game_list);
void print_games(GameNode *head);


int main(int argc, char const *argv[]){

    GameLinkedList *game_list = (GameLinkedList *)malloc(sizeof(GameLinkedList));
    if(game_list == NULL){
        printf("Couldn't allocate memory for game_list");
        return -1;
    }
    memset(game_list,0,sizeof(GameLinkedList));

    game_list->head = (GameNode *)malloc(sizeof(GameNode));
    if(game_list->head == NULL){
        printf("Couldn't allocate memory for game_list.head");
        return -1;
    }
    memset(game_list->head,0,sizeof(GameNode));

    
    printf("Video Game List Operations \n");
    printf("---------------------\n");

    int choice, i = 1;
    char title[MAX_CHAR];
    char genre[MAX_CHAR]; 
    int year;
    float rating;
    float price;


    while(i){

        printf("1. Insert game at beginning\n");
        printf("2. Insert game at end\n");
        printf("3. Delete game from beginning\n");
        printf("4. Delete game from end\n");
        printf("5. Print list\n");
        printf("6. Find game by title\n");
        printf("7. Update game information\n");
        printf("8. Sort list by title\n");
        printf("9. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            break;
        case 2:
            printf("Insert title: ");
            scanf("%s",title);

            printf("Insert genre: ");
            scanf("%s",genre);

            printf("Insert year: ");
            scanf("%d",&year);

            printf("Insert rating: ");
            scanf("%f",&rating);

            game_list->head = insert_game_at_end(game_list->head, title, genre, year, rating);
            break;
        case 3:
            printf("3. Delete game from beginning\n");
            break;
        case 4:
            printf("4. Delete game from end\n");
            break;
        case 5:
            // printf("5. Print list\n");
            print_games(game_list->head);
            break;
        case 6:
            printf("6. Find game by title\n");
            break;
        case 7:
            printf("7. Update game information\n");
            break;
        case 8:
            printf("8. Sort list by title\n");
            break;
        case 9:
            printf("9. Exit\n");
            i=0;
            break;
        default:
            break;
        }
        printf("----------------------------\n");
    }
    
    print_games(game_list->head);
    destroy_list(game_list);

    return 0;
}

GameNode *create_game_node(char *title, char *genre, int year, float rating){
    GameNode *new_node = (GameNode *)malloc(sizeof(GameNode));
    if(new_node == NULL){
        printf("Couldn't allocate memory for new_node\n");
        return NULL;
    }
    memset(new_node,0,sizeof(GameNode));

    new_node->title = (char *)malloc(strlen(title)+1);
    if(new_node->title == NULL){
        printf("Couldn't allocate memory for new_node->title\n");
        return NULL;
    }
    memset(new_node->title,0,strlen(title)+1);

    new_node->genre = (char *)malloc(strlen(genre)+1);
    if(new_node->genre == NULL){
        printf("Couldn't allocate memory for new_node->genre\n");
        return NULL;
    }
    memset(new_node->genre,0,strlen(genre)+1);

    strcpy(new_node->title,title);
    strcpy(new_node->genre,genre);
    new_node->year = year;
    new_node->rating = rating;
    new_node->next = NULL;
    new_node->dlc_head = NULL;

    return new_node;   
}

DLCNode *create_dlc_node(char *title, float price, DLCNode *next){
    DLCNode *new_node = (DLCNode *)malloc(sizeof(DLCNode));
    if(new_node == NULL){
        printf("Couldn't allocate memory for new_node\n");
        return NULL;
    }
    new_node->title = (char *)malloc(strlen(title)+1);
    if(new_node->title == NULL){
        printf("Couldn't allocate memory for new_node->title\n");
        return NULL;
    }

    strcpy(new_node->title,title);
    new_node->price = price;
    new_node->next = next;

    return new_node;
}

void destroy_list(GameLinkedList *game_list){

    // If the head node is null, there is nothing to free
    if(!game_list->head) return;

    // Initialize pointers to head and current nodes, and current DLC node
    GameNode *head = game_list->head;
    GameNode *curr = head;
    DLCNode *curr_dlc_node = head->dlc_head;

    // Iterate through each node in the linked list
    while(head != NULL){

        // Update head pointer to next node
        head = curr->next;

        // Free any DLC nodes attached to the current game node
        while(curr->dlc_head != NULL){
            head->dlc_head = curr_dlc_node->next;
            free(curr_dlc_node->title);
            free(curr_dlc_node);
            curr_dlc_node = head->dlc_head;
        }

        // Free the current game node and update the current node pointer
        free(curr->title);
        free(curr->genre);
        free(curr);
        curr = head;
    }
}

GameNode *insert_game_at_end(GameNode *head, char *title, char *genre, int year, float rating){
    
    
    GameNode *curr = head;
    GameNode *prev = head;

    while(curr != NULL){
        if(curr->title != NULL && strcmp(curr->title,title) == 0){
            printf("Error: Game with title %s already exists in the list\n", title);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }

    GameNode *new_node = create_game_node(title, genre, year, rating);

    if (new_node == NULL) 
        return head;

    if(head == NULL) 
        return new_node;

    new_node->next = prev->next;
    prev->next = new_node;

    return head;
}

void delete_game_by_title(){

}

void print_games(GameNode *head){
    if (!head) {
        printf("null\n");
        return;
    }
    GameNode *curr = head->next;

    while (curr != NULL){
        printf("%s\n", curr->title);
        curr = curr->next;
    }
}

void sort_games_by_rating(){

}

void insert_dlc_at_end(){

}

void delete_dlc_by_title(){

}

void print_dlcs_for_game(){

}
