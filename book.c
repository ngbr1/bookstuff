#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 1000

struct Book {
    int id;
    char title[100];
    char author[100];
    int year;
    int quantity;
    int available;
};

struct Book books[MAX_BOOKS];
int book_count = 0;

void addPresetBook(int id, const char* title, const char* author, int year, int quantity) {
    if (book_count < MAX_BOOKS) {
        books[book_count].id = id;
        strcpy(books[book_count].title, title);
        strcpy(books[book_count].author, author);
        books[book_count].year = year;
        books[book_count].quantity = quantity;
        books[book_count].available = quantity;
        book_count++;
    }
}

void showMenu() {
    printf("\n⠀⣀⣤⣤⣤⣀⠀⠀⠀⠀⣀⣤⣤⣤⣀⠀      ========== LIBRARY SYSTEM ==========\n");
    printf("⣼⣿⣿⣿⣿⣿⣷⡆⢰⣾⣿⣿⣿⣿⣿⣷      1. Add new book\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      2. Display book list\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      3. Search book\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      4. Borrow book\n");
    printf("⠛⠛⠛⠿⠿⣿⣿⡇⢸⣿⣿⠿⠿⠛⠛⠛      5. Return book\n");
    printf("⠙⠓⠒⠶⠦⣄⡉⡃⢘⢉⣠⠴⠶⠒⠚⠋      0. Exit\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠁⠈⠀⠀⠀⠀⠀⠀⠀      Choose: ");
}

void addBook() {
    struct Book b;
    printf("Enter book ID: ");
    scanf("%d", &b.id);
    printf("Enter title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter year: ");
    scanf("%d", &b.year);
    printf("Enter quantity: ");
    scanf("%d", &b.quantity);
    
    b.available = b.quantity;
    books[book_count++] = b;
    printf("Book added successfully!\n");
}

void displayBooks() {
    if (book_count == 0) {
        printf("\nThe library is currently empty!\n");
        return;
    }

    int sort_choice;
    printf("\n--- Display Options ---\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Year (Newest to Oldest)\n");
    printf("3. Sort by Year (Oldest to Newest)\n");
    printf("Choose how to view the list: ");
    scanf("%d", &sort_choice);

    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            int should_swap = 0;
            
            if (sort_choice == 1) {
                if (books[j].id > books[j+1].id) should_swap = 1;
            } 
            else if (sort_choice == 2) {
                if (books[j].year < books[j+1].year) should_swap = 1;
            } 
            else if (sort_choice == 3) {
                if (books[j].year > books[j+1].year) should_swap = 1;
            }

            if (should_swap == 1) {
                struct Book temp = books[j];
                books[j] = books[j+1];
                books[j+1] = temp;
            }
        }
    }

    printf("\nID\tTitle\t\t\tAuthor\t\tYear\tAvailable\n");
    printf("------------------------------------------------------------------------\n");
    for(int i = 0; i < book_count; i++) {
        printf("%d\t%-20s\t%-15s\t%d\t%d/%d\n",
            books[i].id,
            books[i].title,
            books[i].author,
            books[i].year,
            books[i].available,
            books[i].quantity);
    }
}

void searchBook() {
    int search_id;
    int found = 0;

    printf("Enter book ID to search: ");
    scanf("%d", &search_id);
    
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == search_id) {
            printf("\n--- Book Found ---\n");
            printf("ID: %d\n", books[i].id);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Year: %d\n", books[i].year);
            printf("Available/Quantity: %d/%d\n", books[i].available, books[i].quantity);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Error: Book with ID %d not found.\n", search_id);
    }
}

void borrowBook() {
    int borrow_id;
    int found = 0;

    printf("Enter book ID to borrow: ");
    scanf("%d", &borrow_id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == borrow_id) {
            found = 1;
            if (books[i].available > 0) {
                books[i].available--; 
                printf("Successfully borrowed '%s'.\n", books[i].title);
            } else {
                printf("Sorry, '%s' is currently out of stock.\n", books[i].title);
            }
            break;
        }
    }

    if (found == 0) {
        printf("Error: Book with ID %d not found.\n", borrow_id);
    }
}

void returnBook() {
    int return_id;
    int found = 0;

    printf("Enter book ID to return: ");
    scanf("%d", &return_id);

    for (int i = 0; i < book_count; i++) {
        if (books[i].id == return_id) {
            found = 1;
            if (books[i].available < books[i].quantity) {
                books[i].available++; 
                printf("Successfully returned '%s'.\n", books[i].title);
            } else {
                printf("Error: All copies of '%s' are already in the library.\n", books[i].title);
            }
            break;
        }
    }

    if (found == 0) {
        printf("Error: Book with ID %d not found.\n", return_id);
    }
}

int main() {
    addPresetBook(154, "cheeseburger", "beeangoodshape", 2021, 1);
    addPresetBook(153, "that one infinite game", "beeangoodshape", 2025, 1000);
    addPresetBook(152, "hes in your wall", "beeangoodshape", 2023, 4);
    addPresetBook(7922, "doyouknow", "themuffinman", 1820, 4);
    addPresetBook(7923, "wholivesin", "drurylane", 1889, 4);
    addPresetBook(333, "tellmewhy", "aint nothing", 1999, 12);
    addPresetBook(42, "buta", "hearthache", 1999, 4);
    
    
    
    

    int choice;
    while(1) {
        showMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 0:
                printf("Exiting Library System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}