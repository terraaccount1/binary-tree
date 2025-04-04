#include <stdio.h>
#define STRING_SIZE 32

typedef char string[STRING_SIZE];

typedef struct
{
    string title;
    string author;
    unsigned int year;
    unsigned int pages;
    unsigned int quantity;
    double price;
} Book;

Book *new_book();
Book *new_book_title();
void *free_book(void *data);
void print_book(void *data);
int compare_title(void *a, void *b);
void save_data(void *data, FILE *file);
void set_random_mode(int mode);