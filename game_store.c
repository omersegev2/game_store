#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

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

DLCNode *create_dlc_node(char *title, float price);
GameNode *create_game_node(char *title, char *genre, int year, float rating);
GameNode *insertGameAtEnd(GameNode *head, char *title, char *genre, int year, float rating);
void sortGamesByRating(GameNode *head);
void deleteGameByTitle(GameNode *head, char *title);
GameNode *find_game(GameNode *head, char *title);
void insertDlcAtEnd(GameNode *head,char *game_title, char* dlc_title, float price);
void destroyList(GameLinkedList *game_list);
void printGames(GameNode *head);
void printDlcsForGame(GameNode *head, char *title);
void destroy_game_node(GameNode *head);
void swap_nodes(GameNode **head, GameNode *newNode);


int main(int argc, char const *argv[]){

    GameLinkedList *game_list = (GameLinkedList *)malloc(sizeof(GameLinkedList));
    if(game_list == NULL){
        printf("Couldn't allocate memory for game_list");
        return -1;
    }
    

    game_list->head = (GameNode *)malloc(sizeof(GameNode));
    if(game_list->head == NULL){
        free(game_list);
        printf("Couldn't allocate memory for game_list.head");
        return -1;
    }
    game_list->head = NULL;
    
    printf("Video Game List Operations \n");
    printf("---------------------\n");

    int choice;
    char title[MAX_LEN];
    char genre[MAX_LEN]; 
    char dlc_title[MAX_LEN]; 
    int year = 0;
    float rating = 0;
    float price = 0;


    while(choice != 8){
        printf("1. Insert game\n");
        printf("2. Delete game\n");
        printf("3. Print games\n");
        printf("4. Sort games by rating\n");
        printf("5. Insert DLC to game\n");
        printf("6. Delete DLC by title\n");
        printf("7. Print DLC\n");
        printf("8. Exit\n");
        if(scanf("%d", &choice) != 1){
            printf("Invalid input. Please enter a number.\n");
            scanf("%*s");
            continue;
        }

        switch (choice) {
        case 1:
            printf("Insert title: ");
            scanf("%s",title);

            printf("Insert genre: ");
            scanf("%s",genre);

            printf("Insert year: ");
            scanf("%d",&year);

            printf("Insert rating: ");
            scanf("%f",&rating);

            game_list->head = insertGameAtEnd(game_list->head, title, genre, year, rating);
            break;
        case 2:
            printf("Insert title of game to delete: ");
            scanf("%s",title);
            deleteGameByTitle(game_list->head,title);
            break;
        case 3:
            printGames(game_list->head);
            break;
        case 4:
            sortGamesByRating(game_list->head);
            break;
        case 5:

            printf("Insert game title: ");
            scanf("%s",title);

            printf("Insert DLC title: ");
            scanf("%s",dlc_title);

            printf("Insert price: ");
            scanf("%f",&price);

            insertDlcAtEnd(game_list->head, title, dlc_title, price);
            break;
        case 6:
            break;
        case 7:
            printf("Insert game title: ");
            scanf("%s",title);

            printDlcsForGame(game_list->head, title);
            break;
        case 8:
            destroyList(game_list);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("---------------------\n");
    }

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

DLCNode *create_dlc_node(char *title, float price){
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
    new_node->next = NULL;

    return new_node;
}

void destroyList(GameLinkedList *game_list){

    if(game_list == NULL || game_list->head == NULL) return;

    GameNode *head = game_list->head;
    GameNode *curr = head;
    DLCNode *curr_dlc_node = head->dlc_head;

    while(head != NULL){

        head = curr->next;

        while(curr->dlc_head != NULL){
            curr->dlc_head = curr_dlc_node->next;
            free(curr_dlc_node->title);
            free(curr_dlc_node);
            curr_dlc_node = curr->dlc_head;
        }

        free(curr->title);
        free(curr->genre);
        free(curr);
        curr = head;
    }
    free(game_list);
}

GameNode *insertGameAtEnd(GameNode *head, char *title, char *genre, int year, float rating){
    
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

void deleteGameByTitle(GameNode *head, char *title){

    if(!head) return;

    GameNode *curr = head;
    GameNode *prev = head;

    while(curr != NULL){
        if(curr->title != NULL && strcmp(curr->title,title) == 0){
            prev->next = curr->next;
            destroy_game_node(curr);
            printf("Game with title %s has been deleted from the list\n", title);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Error: Game with title %s not found in the list\n", title);

    return;
}

void sortGamesByRating(GameNode *head){

    GameNode *current = head;
    GameNode *nextNode;
    
    GameNode *answerList = NULL; 

    while (current != NULL) {
        nextNode = current->next;
        swap_nodes(&answerList, current);
        current = nextNode;
    }

    head = answerList;
}

void insertDlcAtEnd(GameNode *head, char *game_title, char* dlc_title, float price){

    DLCNode *new_dlc_node = create_dlc_node(dlc_title,price);
    if(new_dlc_node == NULL) return;

    GameNode *curr_game = find_game(head, game_title);
    if(curr_game == NULL) {
        printf("No such game %s\n", game_title);
        return;
    }

    DLCNode *curr_dlc = curr_game->dlc_head;
    DLCNode *prev_dlc = curr_game->dlc_head;

    
    if(curr_game->dlc_head == NULL) {
        curr_game->dlc_head = new_dlc_node;
        return;
    }

    while(curr_dlc != NULL && curr_dlc->next != NULL){
        prev_dlc = curr_dlc;
        curr_dlc = curr_dlc->next;
    }

    new_dlc_node->next = curr_dlc->next;
    prev_dlc->next = new_dlc_node;
    
}

GameNode *find_game(GameNode *head, char *title){

    if(head == NULL) return NULL;
    
    if(head->title != NULL && strcmp(head->title,title)==0) return head;

    return find_game(head->next, title);
}

void delete_dlc_by_title(){

}

void printDlcsForGame(GameNode *head, char *title){
    
    printf("---------------------\n");
    printf("\033[34m");

    if(!head) {
        printf("null\n");
        return;
    }

    GameNode *curr_game = find_game(head, title);
    if(curr_game == NULL) return;

    DLCNode *curr_dlc = curr_game->dlc_head;
    if(curr_dlc == NULL) {
        printf("No DLC in Game: %s", curr_game->title);
        return;
    }

    while(curr_dlc != NULL){
        printf("%s\n", curr_dlc->title);
        curr_dlc = curr_dlc->next;
    }

    printf("\033[0m");
}

void destroy_game_node(GameNode *head){

    DLCNode *curr_dlc = head->dlc_head;

    while(curr_dlc != NULL){
        curr_dlc = curr_dlc->next;
        free(head->dlc_head->title);
        free(head->dlc_head);
        head->dlc_head = curr_dlc;
    }

    free(head->title);
    free(head->genre);
    free(head);
}

void printGames(GameNode *head){

    printf("---------------------\n");
    printf("\033[34m");

    if (!head) {
        printf("null\n");
        return;
    }
    GameNode *curr = head->next;

    while (curr != NULL){
        printf("%s\n", curr->title);
        curr = curr->next;
    }
    printf("\033[0m");
}

void swap_nodes(GameNode **head, GameNode *newNode) {
   GameNode temp;
   GameNode *current = &temp;
   temp.next = *head;

   while (current->next != NULL && current->next->rating < newNode->rating) {
      current = current->next;
   }

   newNode->next = current->next;
   current->next = newNode;
   *head = temp.next;
}

