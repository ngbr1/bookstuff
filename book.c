#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 1000
#define MAX_USERS 1000
#define MAX_TRANS 5000

struct Book {
    int id;
    char title[100];
    char author[100];
    int year;
    int quantity;
    int available;
    int borrow_count; 
};

struct User {
    int id;
    char name[100];
    int borrowed_count;
};

struct Transaction {
    int user_id;
    int book_id;
    int type; // 1 = borrow, 2 = return
};

struct Book books[MAX_BOOKS];
int book_count = 0;

struct User users[MAX_USERS];
int user_count = 0;

struct Transaction transactions[MAX_TRANS];
int trans_count = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt() {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter a number: ");
        clearInputBuffer();
    }
    return value;
}

void sanitizeString(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|') {
            str[i] = '-';
        }
    }
}

int findUserIndex(int id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].id == id) return i;
    }
    return -1;
}

int findBookIndex(int id) {
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id) return i;
    }
    return -1;
}

void saveData() {
    FILE *fb = fopen("books.txt", "w");
    if (fb) {
        for (int i = 0; i < book_count; i++) {
            fprintf(fb, "%d|%s|%s|%d|%d|%d|%d\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].quantity, books[i].available, books[i].borrow_count);
        }
        fclose(fb);
    }

    FILE *fu = fopen("users.txt", "w");
    if (fu) {
        for (int i = 0; i < user_count; i++) {
            fprintf(fu, "%d|%s|%d\n", users[i].id, users[i].name, users[i].borrowed_count);
        }
        fclose(fu);
    }

    FILE *ft = fopen("transactions.txt", "w");
    if (ft) {
        for (int i = 0; i < trans_count; i++) {
            // Saved without date
            fprintf(ft, "%d|%d|%d\n", transactions[i].user_id, transactions[i].book_id, transactions[i].type);
        }
        fclose(ft);
    }
}

void addPresetBook(int id, const char* title, const char* author, int year, int quantity) {
    if (book_count < MAX_BOOKS) {
        books[book_count].id = id;
        strncpy(books[book_count].title, title, 99);
        books[book_count].title[99] = '\0';
        strncpy(books[book_count].author, author, 99);
        books[book_count].author[99] = '\0';
        books[book_count].year = year;
        books[book_count].quantity = quantity;
        books[book_count].available = quantity;
        books[book_count].borrow_count = 0;
        book_count++;
    }
}

void loadData() {
    FILE *fb = fopen("books.txt", "r");
    if (fb) {
while (fscanf(fb, "%d|%99[^|]|%99[^|]|%d|%d|%d|%d\n", &books[book_count].id, books[book_count].title, books[book_count].author, &books[book_count].year, &books[book_count].quantity, &books[book_count].available, &books[book_count].borrow_count) == 7) {
            if (book_count < MAX_BOOKS - 1) book_count++;
            else break;
        }
        fclose(fb);
    } else {
        addPresetBook(154, "cheeseburger", "beeangoodshape", 2021, 1);
        addPresetBook(153, "that one infinite game", "beeangoodshape", 2025, 1000);
        addPresetBook(152, "hes in your wall", "beeangoodshape", 2023, 4);
        addPresetBook(7922, "doyouknow", "themuffinman", 1820, 4);
        addPresetBook(7923, "wholivesin", "drurylane", 1889, 4);
        addPresetBook(333, "tellmewhy", "aint nothing", 1999, 12);
        addPresetBook(42, "buta", "hearthache", 1999, 4);
    }

    FILE *fu = fopen("users.txt", "r");
    if (fu) {
        while (fscanf(fu, "%d|%99[^|]|%d\n", &users[user_count].id, users[user_count].name, &users[user_count].borrowed_count) == 3) {
            if (user_count < MAX_USERS - 1) user_count++;
            else break;
        }
        fclose(fu);
    }

    FILE *ft = fopen("transactions.txt", "r");
    if (ft) {
        // Loaded without date
        while (fscanf(ft, "%d|%d|%d\n", &transactions[trans_count].user_id, &transactions[trans_count].book_id, &transactions[trans_count].type) == 3) {
            if (trans_count < MAX_TRANS - 1) trans_count++;
            else break;
        }
        fclose(ft);
    }
}

void showMenu() {
    printf("\n⠀⣀⣤⣤⣤⣀⠀⠀⠀⠀⣀⣤⣤⣤⣀⠀      ========== LIBRARY SYSTEM ==========\n");
    printf("⣼⣿⣿⣿⣿⣿⣷⡆⢰⣾⣿⣿⣿⣿⣿⣷      1. Add new book\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      2. Display book list\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      3. Search book\n");
    printf("⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿      4. Borrow book\n");
    printf("⠛⠛⠛⠿⠿⣿⣿⡇⢸⣿⣿⠿⠿⠛⠛⠛      5. Return book\n");
    printf("⠙⠓⠒⠶⠦⣄⡉⡃⢘⢉⣠⠴⠶⠒⠚⠋      6. Add User\n");
    printf("      ⠀⠁⠈⠀⠀⠀⠀        7. Display Users\n");
    printf("                      8. View Transactions\n");
    printf("                      9. Statistics\n");
    printf("                      0. Exit & Save\n");
    printf("⠀⠀⠀⠀⠀⠀⠀         ⠀⠀⠀      Choose: ");
}

void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("Error: Library database is full (Max %d books).\n", MAX_BOOKS);
        return;
    }

    struct Book b;
    printf("Enter book ID: ");
    b.id = getValidInt();
    
    if (findBookIndex(b.id) != -1) {
        printf("Error: Book with ID %d already exists.\n", b.id);
        return;
    }
    if (b.id <= 0) {
        printf("Error: Book ID must be a positive number.\n");
        return;
    }
printf("Enter title: ");
    scanf(" %99[^\n]", b.title);
    sanitizeString(b.title);

    printf("Enter author: ");
    scanf(" %99[^\n]", b.author);
    sanitizeString(b.author);

    printf("Enter year: ");
    b.year = getValidInt();

    printf("Enter quantity: ");
    b.quantity = getValidInt();
    if (b.quantity <= 0) {
        printf("Error: Quantity must be greater than 0.\n");
        return;
    }
    
    b.available = b.quantity;
    b.borrow_count = 0;
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
    printf("2. Sort by Title (Alphabetical)\n");
    printf("3. Sort by Year (Newest to Oldest)\n");
    printf("4. Sort by Year (Oldest to Newest)\n");
    printf("5. Sort by Available Quantity\n");
    printf("Choose how to view the list: ");
    sort_choice = getValidInt();

    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            int should_swap = 0;
            
            if (sort_choice == 1 && books[j].id > books[j+1].id) should_swap = 1;
            else if (sort_choice == 2 && strcmp(books[j].title, books[j+1].title) > 0) should_swap = 1;
            else if (sort_choice == 3 && books[j].year < books[j+1].year) should_swap = 1;
            else if (sort_choice == 4 && books[j].year > books[j+1].year) should_swap = 1;
            else if (sort_choice == 5 && books[j].available < books[j+1].available) should_swap = 1;

            if (should_swap == 1) {
                struct Book temp = books[j];
                books[j] = books[j+1];
                books[j+1] = temp;
            }
        }
    }

    printf("\nID\t%-25s\t%-15s\tYear\tAvail/Qty\n", "Title", "Author");
    printf("------------------------------------------------------------------------------\n");
    for(int i = 0; i < book_count; i++) {
        printf("%d\t%-25.25s\t%-15.15s\t%d\t%d/%d\n",
            books[i].id, books[i].title, books[i].author, 
            books[i].year, books[i].available, books[i].quantity);
    }
}

void searchBook() {
    int choice;
    printf("\n--- Advanced Search ---\n");
    printf("1. Search by ID\n");
    printf("2. Search by Title\n");
    printf("3. Search by Author\n");
    printf("4. Search by Year\n");
    printf("Choose option: ");
    choice = getValidInt();

    int found = 0;
    
    if (choice == 1 || choice == 4) {
        int search_num;
        printf("Enter ID/Year: ");
        search_num = getValidInt();
        for (int i = 0; i < book_count; i++) {
            if ((choice == 1 && books[i].id == search_num) || (choice == 4 && books[i].year == search_num)) {
printf("\nFound: [%d] '%s' by %s (%d) - %d/%d available\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].available, books[i].quantity);
                found = 1;
            }
        }
    } else if (choice == 2 || choice == 3) {
        char search_str[100];
        printf("Enter Title/Author to search: ");
        scanf(" %99[^\n]", search_str);
        for (int i = 0; i < book_count; i++) {
            if ((choice == 2 && strstr(books[i].title, search_str) != NULL) || 
                (choice == 3 && strstr(books[i].author, search_str) != NULL)) {
                printf("\nFound: [%d] '%s' by %s (%d) - %d/%d available\n", books[i].id, books[i].title, books[i].author, books[i].year, books[i].available, books[i].quantity);
                found = 1;
            }
        }
    } else {
        printf("Invalid search option.\n");
        return;
    }

    if (found == 0) printf("\nNo books matched your search.\n");
}

void borrowBook() {
    if (trans_count >= MAX_TRANS) {
        printf("Error: Transaction limit reached. Contact Admin.\n");
        return;
    }

    int user_id, book_id;
    printf("Enter User ID: ");
    user_id = getValidInt();
    
    int u_idx = findUserIndex(user_id);
    if (u_idx == -1) {
        printf("Error: User ID not found.\n");
        return;
    }

    printf("Enter Book ID to borrow: ");
    book_id = getValidInt();

    int b_idx = findBookIndex(book_id);
    if (b_idx == -1) {
        printf("Error: Book ID not found.\n");
        return;
    }

    if (books[b_idx].available > 0) {
        books[b_idx].available
