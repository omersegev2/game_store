

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MIN_YEAR 1900

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
GameNode *find_game(GameNode *head, char *title);
GameNode *sortGamesByRating(GameNode *head);
GameNode *deleteGameByTitle(GameNode *head, char *title);
void deleteDlcByTitle(GameNode *head, char *game_title, char *dlc_title);
void insertDlcAtEnd(GameNode *head,char *game_title, char* dlc_title, float price);
void destroyList(GameLinkedList game_list);
void printGames(GameNode *head);
void printDlcsForGame(GameNode *head, char *title);
void destroy_game_node(GameNode *head);
void destroy_dlc_node(DLCNode *dlc_node);


int main(int argc, char const *argv[]){

    GameLinkedList game_list;
    game_list.head = NULL;

    printf("Welcome to the Game Library!\n");
    
    char title[MAX_LEN];
    char genre[MAX_LEN]; 
    char dlc_title[MAX_LEN]; 
    int year = 0;
    float rating = 0;
    float price = 0;
    int choice = 0;

    while(choice != 8){
        printf("\n");
        printf("\033[0;31m1.\033[0m Insert game\n");
        printf("\033[0;31m2.\033[0m Delete game\n");
        printf("\033[0;31m3.\033[0m Print all games\n");
        printf("\033[0;31m4.\033[0m Sort games by rating\n");
        printf("\033[0;31m5.\033[0m Insert DLC for a game\n");
        printf("\033[0;31m6.\033[0m Delete DLC for a game\n");
        printf("\033[0;31m7.\033[0m Print DLC for a game\n");
        printf("\033[0;31m8.\033[0m Exit\n\n");

        printf("Insert your choice: ");
        printf("\033[0;31m");
        if(scanf("%d", &choice) != 1){
            printf("\033[0m");
            printf("Invalid input. Please enter a number.\n");
            scanf("%*s");
            continue;
        }
        printf("\033[0m");
        printf("\n");

        switch (choice) {
        case 1:
            printf("Enter game title: ");
            scanf(" %[^\n]", title);

            printf("Enter game genre: ");
            scanf(" %[^\n]", genre); 

            while(1){
                printf("Enter year of release: ");
                scanf("%d", &year);
                if(year >= MIN_YEAR){
                    break;
                } else {
                    printf("Invalid year. Please enter a year from %d\n", MIN_YEAR);
                }
            }

            while(1){
                printf("Enter game rating (out of 10): ");
                scanf("%f", &rating);
                if(rating >= 0 && rating <= 10){
                    break;
                } else {
                    printf("Invalid rating. Please enter a number between 0 and 10\n");
                }
            }

            game_list.head = insertGameAtEnd(game_list.head, title, genre, year, rating);
            break;
        case 2:
            printf("Insert title of game to delete: ");
            scanf(" %[^\n]", title);
            game_list.head = deleteGameByTitle(game_list.head,title);
            break;
        case 3:
            printGames(game_list.head);
            break;
        case 4:
            game_list.head = sortGamesByRating(game_list.head);
            break;
        case 5:
            printf("Insert game title: ");
            scanf(" %[^\n]", title);

            printf("Insert DLC title: ");
            scanf(" %[^\n]", dlc_title);

            while(1){
                printf("Insert price: ");
                scanf("%f",&price);
                if(price >= 0){
                    break;
                } else {
                    printf("Invalid price. Please enter a positive number.\n");
                }
            }

            insertDlcAtEnd(game_list.head, title, dlc_title, price);
            break;
        case 6:
            printf("Insert game title: ");
            scanf(" %[^\n]", title);

            printf("Insert DLC title: ");
            scanf(" %[^\n]", dlc_title);

            deleteDlcByTitle(game_list.head, title, dlc_title);
            break;
        case 7:
            printf("Insert game title: ");
            scanf(" %[^\n]", title);

            printDlcsForGame(game_list.head, title);
            break;
        case 8:
            destroyList(game_list);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
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
        destroy_game_node(new_node);
        return NULL;
    }
    memset(new_node->title,0,strlen(title)+1);

    new_node->genre = (char *)malloc(strlen(genre)+1);
    if(new_node->genre == NULL){
        printf("Couldn't allocate memory for new_node->genre\n");
        destroy_game_node(new_node);
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
    memset(new_node,0,sizeof(DLCNode));

    new_node->title = (char *)malloc(strlen(title)+1);
    if(new_node->title == NULL){
        free(new_node);
        printf("Couldn't allocate memory for new_node->title\n");
        return NULL;
    }
    memset(new_node->title,0,strlen(title)+1);

    strcpy(new_node->title,title);
    new_node->price = price;
    new_node->next = NULL;

    return new_node;
}

void destroyList(GameLinkedList game_list){

    if(game_list.head  == NULL) return;

    GameNode *head = game_list.head;
    GameNode *curr = head;
    DLCNode *curr_dlc_node = head->dlc_head;

    while(curr){

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
}

GameNode *insertGameAtEnd(GameNode *head, char *title, char *genre, int year, float rating){
    
    GameNode *curr = head;
    GameNode *prev = head;

    while(curr != NULL){
        if(curr->title != NULL && strcmp(curr->title,title) == 0){
            printf("\nError: Game with title %s already exists in the list\n", title);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }

    GameNode *new_node = create_game_node(title, genre, year, rating);

    if(head == NULL) {
        printf("\nGame inserted successfully.\n");
        return new_node;
    }

    new_node->next = prev->next;
    prev->next = new_node;
    
    printf("\nGame inserted successfully.\n");
    return head;
}

GameNode *deleteGameByTitle(GameNode *head, char *title){

    if(!head) return head;

    GameNode *curr = head;
    GameNode *prev = head;

    while(curr != NULL){
        if(curr->title != NULL && strcmp(curr->title,title) == 0){
            if(curr == head){
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            destroy_game_node(curr);
            printf("\nGame with title %s has been deleted from the list\n", title);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("\nError: Game with title %s not found in the list\n", title);

    return head;
}

GameNode *sortGamesByRating(GameNode* head) {
    if (head == NULL || head->next == NULL) {
        return head; 
    }

    GameNode *curr, *next, *prev, *temp;
    int swapped;

    do {
        swapped = 0;
        curr = head;
        prev = NULL;

        while (curr->next != NULL) {
            next = curr->next;

            if (curr->rating < next->rating) {
                
                if (prev != NULL) {
                    prev->next = next;
                }
                else {
                    head = next;
                }
                curr->next = next->next;
                next->next = curr;
                temp = curr;
                curr = next;
                next = temp;
                swapped = 1;
            }
            prev = curr;
            curr = curr->next;
        }
    } while (swapped);

    printf("\nGames sorted by rating:\n");
    GameNode *curr_node = head;

    while (curr_node != NULL){
        printf("- %s (%.1f)\n", curr_node->title, curr_node->rating);
        curr_node = curr_node->next;
    }
    return head;
}

void insertDlcAtEnd(GameNode *head, char *game_title, char* dlc_title, float price){

    printf("\n");

    if(head == NULL){
        printf("Error: Game list is empty.\n");
    }

    DLCNode *new_dlc_node = create_dlc_node(dlc_title,price);
    if(new_dlc_node == NULL) return;

    GameNode *curr_game = find_game(head, game_title);
    if(curr_game == NULL) {
        printf("Error: No such game %s\n", game_title);
        destroy_dlc_node(new_dlc_node);
        return;
    }

    DLCNode *curr_dlc = curr_game->dlc_head;
    DLCNode *prev_dlc = NULL;

    if(curr_dlc == NULL) {
        curr_game->dlc_head = new_dlc_node;
        printf("DLC inserted successfully.\n");
        return;
    }

    while(curr_dlc->next != NULL){
        prev_dlc = curr_dlc;
        curr_dlc = curr_dlc->next;
    }

    curr_dlc->next = new_dlc_node;
    printf("DLC inserted successfully.\n");
}

GameNode *find_game(GameNode *head, char *title){

    if(head == NULL) return NULL;
    
    if(head->title != NULL && strcmp(head->title,title)==0) return head;

    return find_game(head->next, title);
}

void deleteDlcByTitle(GameNode *head, char *game_title, char *dlc_title){
    
    printf("\n");

    if(head == NULL) return;

    GameNode *curr_game = head;
    DLCNode *curr_dlc = NULL;
    DLCNode *prev_dlc = NULL;

    while(curr_game != NULL && strcmp(curr_game->title,game_title) != 0) {
        curr_game = curr_game->next;
    }

    if(curr_game == NULL){
        printf("Error: Game with title '%s' not found.\n",game_title);
        return;
    }

    curr_dlc = curr_game->dlc_head;

    if(curr_dlc != NULL && strcmp(curr_dlc->title,dlc_title) == 0){
        curr_game->dlc_head = curr_dlc->next;
        destroy_dlc_node(curr_dlc);
        printf("DLC with title '%s' has been deleted from the list.\n",dlc_title);
        return;
    }

    while(curr_dlc != NULL && strcmp(curr_dlc->title,dlc_title) != 0){
        prev_dlc = curr_dlc;
        curr_dlc = curr_dlc->next;
    }

    if(curr_dlc == NULL){
        printf("Error: DLC with title '%s' not found.\n",dlc_title);
        return;
    }

    prev_dlc->next = curr_dlc->next;
    destroy_dlc_node(curr_dlc);
    printf("DLC with title '%s' has been deleted from the list.\n",dlc_title);
}

void printDlcsForGame(GameNode *head, char *title){
    
    printf("\n");

    if(head == NULL) {
        printf("Error: The list is empty.\n");
        return;
    }

    GameNode *curr_game = find_game(head, title);
    if(curr_game == NULL) {
        printf("Error: game with title: %s, NOT FOUND.\n", title);
        return;
    }

    printf("DLCs for %s:\n", title);

    DLCNode *curr_dlc = curr_game->dlc_head;
    if(curr_dlc == NULL) {
        printf("No DLC in Game: %s\n", curr_game->title);
        return;
    }

    while(curr_dlc != NULL){
        printf("- %s ($%.2f)\n", curr_dlc->title, curr_dlc->price);
        curr_dlc = curr_dlc->next;
    }
}

void destroy_game_node(GameNode *head){

    DLCNode *curr_dlc = head->dlc_head;

    while(curr_dlc != NULL){
        curr_dlc = curr_dlc->next;
        destroy_dlc_node(curr_dlc);
        head->dlc_head = curr_dlc;
    }

    free(head->title);
    free(head->genre);
    free(head);
}

void destroy_dlc_node(DLCNode *dlc_node){
    if(dlc_node == NULL) return;

    free(dlc_node->title);
    free(dlc_node);
}

void printGames(GameNode *head){

    printf("Games in the library:\n");

    if (!head) {
        printf("null\n");
        return;
    }
    GameNode *curr = head;

    while (curr != NULL){
        printf("- %s\n", curr->title);
        curr = curr->next;
    }
}
