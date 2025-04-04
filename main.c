#include <stdio.h>
#include <stdlib.h>
#include "tree/b_tree.h"
#include "data/data.h"
#include "print/color_print.h"

void start(Tree *tree, FILE *file);
void menu();
void menu_actions(Tree *tree, int option);
void clear();

int main(int argc, char *argv[])
{
    FILE *file = fopen("books.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    Tree *tree = create_tree();
    if (tree == NULL)
    {
        printf("Error creating tree\n");
        return 1;
    }

    set_random_mode(1);
    start(tree, file);

    tree = free_tree(tree, free_book);
    fclose(file);
    return 0;
}

void start(Tree *tree, FILE *file)
{
    int option = 0;

    do
    {
        freopen("books.txt", "w", file);
        save_in_file(tree->root, file, save_data);
        fflush(file);
        menu();
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("\nChoose an option: ");
        scanf("%d", &option);
        reset_print();
        clear();
        menu_actions(tree, option);
    } while (option >= 1 && option <= 9);

    reset_print();
}

void menu()
{
    set_print(STYLE_BRIGHT, COLOR_GREEN);
    printf("1. Insert\n");
    printf("2. Print\n");
    printf("3. Depth\n");
    printf("4. Search\n");
    printf("5. Node depth\n");
    printf("6. Node height\n");
    printf("7. Print leaves\n");
    printf("8. Clean tree\n");
    printf("9. Remove tree\n");
    printf("Something else to exit\n");
}

void menu_actions(Tree *tree, int option)
{
    void *data;

    switch (option)
    {
    case 1:
    {
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        data = (void *)new_book();
        tree->root = add_node(tree->root, data, compare_title);
        printf("\n");
        reset_print();
        break;
    }

    case 2:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Printing tree...\n");
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        print_tree(tree->root, print_book);
        reset_print();
        break;
    }

    case 3:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Tree depth: %d\n\n", tree_depth(tree->root)-1);
        reset_print();
        break;
    }

    case 4:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Enter book to search: \n");
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        data = (void *)new_book_title();
        void *found = search_tree(tree->root, data, compare_title);
        if (found != NULL)
        {
            printf("\nFound: ");
            print_book(found);
            printf("\n");
        }
        else
        {
            printf("Not found\n\n");
        }
        reset_print();
        break;
    }

    case 5:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Enter book to search: \n");
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        data = (void *)new_book_title();
        int depth = node_depth(tree->root, data, compare_title);
        if (depth != -1)
        {
            printf("Node depth: %d\n\n", depth);
        }
        else
        {
            printf("Not found\n\n");
        }
        reset_print();
        break;
    }

    case 6:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Enter book to search: \n");
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        data = (void *)new_book_title();
        int height = node_height(tree->root, data, compare_title);
        if (height != -1)
        {
            printf("Node height: %d\n\n", height);
        }
        else
        {
            printf("Not found\n\n");
        }
        reset_print();
        break;
    }

    case 7:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Printing leaves...\n");
        set_print(STYLE_BRIGHT, COLOR_CYAN);
        print_leaves(tree->root, print_book);
        reset_print();
        break;
    }

    case 8:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Cleaning tree...\n");
        reset_print();
        tree->root = free_tree_data(tree->root, free_book);
        break;
    }

    case 9:
    {
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        printf("Removing tree...\n");
        reset_print();
        tree = free_tree(tree, free_book);
        exit(EXIT_SUCCESS);
        break;
    }

    default:
        break;
    }
}

void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}