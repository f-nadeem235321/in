#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string isbn;
    string author;
    string publisher;
    int copies=0;
    int edition=0;
};

void addBook(Book books[], int& count);
void deleteBook(Book books[], int& count);
void modifyBook(Book books[], int count);
void searchBookByISBN(Book books[], int count);
void searchBookByTitle(Book books[], int count);
void sortByTitle(Book books[], int count);
void sortByEdition(Book books[], int count);
void borrowBook(Book books[], int count);
void returnBook(Book books[], int count);
void displayBooks(Book books[], int count);

int main() {
    Book books[100];
    int count = 0;
    int choice;

    do {
        cout << endl << "======= Library Management System =======" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Delete Book" << endl;
        cout << "3. Modify Book" << endl;
        cout << "4. Search by ISBN" << endl;
        cout << "5. Search by Title" << endl;
        cout << "6. Sort by Title" << endl;
        cout << "7. Sort by Edition" << endl;
        cout << "8. Borrow Book" << endl;
        cout << "9. Return Book" << endl;
        cout << "10. Display All Books" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(books, count); break;
        case 2: deleteBook(books, count); break;
        case 3: modifyBook(books, count); break;
        case 4: searchBookByISBN(books, count); break;
        case 5: searchBookByTitle(books, count); break;
        case 6: sortByTitle(books, count); break;
        case 7: sortByEdition(books, count); break;
        case 8: borrowBook(books, count); break;
        case 9: returnBook(books, count); break;
        case 10: displayBooks(books, count); break;
        case 0: cout << "Exiting program..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}


void addBook(Book books[], int& count) {
    cout << endl << "--- Add New Book ---" << endl;

    cout << "Enter Title (one word): ";
    cin >> books[count].title;

    cout << "Enter ISBN: ";
    cin >> books[count].isbn;

    cout << "Enter Author (one word): ";
    cin >> books[count].author;

    cout << "Enter Publisher (one word): ";
    cin >> books[count].publisher;

    cout << "Enter Edition (number): ";
    cin >> books[count].edition;

    cout << "Enter Number of Copies: ";
    cin >> books[count].copies;

    count++;
    cout << "Book Added Successfully!" << endl;
}

void deleteBook(Book books[], int& count) {
    cout << endl << "--- Delete Book ---" << endl;
    string isbn;
    cout << "Enter ISBN to delete: ";
    cin >> isbn;

    for (int i = 0; i < count; i++) {
        if (books[i].isbn == isbn) {
            for (int j = i; j < count - 1; j++) {
                books[j] = books[j + 1];
            }
            count--;
            cout << "Book deleted successfully!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

void modifyBook(Book books[], int count) {
    cout << endl << "--- Modify Book ---" << endl;
    string isbn;
    cout << "Enter ISBN to modify: ";
    cin >> isbn;

    for (int i = 0; i < count; i++) {
        if (books[i].isbn == isbn) {
            cout << "Enter New Title: ";
            cin >> books[i].title;

            cout << "Enter New Author: ";
            cin >> books[i].author;

            cout << "Enter New Publisher: ";
            cin >> books[i].publisher;

            cout << "Enter New Edition: ";
            cin >> books[i].edition;

            cout << "Enter New Copies: ";
            cin >> books[i].copies;

            cout << "Book Updated!" << endl;
            return;
        }
    }

    cout << "Book Not Found!" << endl;
}

void searchBookByISBN(Book books[], int count) {
    cout << endl << "--- Search By ISBN ---" << endl;
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;

    for (int i = 0; i < count; i++) {
        if (books[i].isbn == isbn) {
            cout << endl << "Book Found!" << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Publisher: " << books[i].publisher << endl;
            cout << "Edition: " << books[i].edition << endl;
            cout << "Copies: " << books[i].copies << endl;
            return;
        }
    }
    cout << "Book Not Found!" << endl;
}

void searchBookByTitle(Book books[], int count) {
    cout << endl << "--- Search By Title ---" << endl;
    string title;
    cout << "Enter Title: ";
    cin >> title;

    for (int i = 0; i < count; i++) {
        if (books[i].title == title) {
            cout << endl << "Book Found!" << endl;
            cout << "ISBN: " << books[i].isbn << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Publisher: " << books[i].publisher << endl;
            cout << "Edition: " << books[i].edition << endl;
            cout << "Copies: " << books[i].copies << endl;
            return;
        }
    }

    cout << "Book Not Found!" << endl;
}

void sortByTitle(Book books[], int count) {
    cout << endl << "--- Sorting By Title ---" << endl;

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].title > books[j].title) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    cout << "Books Sorted!" << endl;
}

void sortByEdition(Book books[], int count) {
    cout << endl << "--- Sorting By Edition (Same Titles) ---" << endl;

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].title == books[j].title &&
                books[i].edition > books[j].edition) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    cout << "Books Sorted by Edition!" << endl;
}

void borrowBook(Book books[], int count) {
    cout << endl << "--- Borrow Book ---" << endl;
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;

    for (int i = 0; i < count; i++) {
        if (books[i].isbn == isbn) {
            if (books[i].copies > 0) {
                books[i].copies--;
                cout << "Book Borrowed!" << endl;
            }
            else {
                cout << "No copies available!" << endl;
            }
            return;
        }
    }

    cout << "Book Not Found!" << endl;
}

void returnBook(Book books[], int count) {
    cout << endl << "--- Return Book ---" << endl;
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;

    for (int i = 0; i < count; i++) {
        if (books[i].isbn == isbn) {
            books[i].copies++;
            cout << "Book Returned!" << endl;
            return;
        }
    }

    cout << "Book Not Found!" << endl;
}

void displayBooks(Book books[], int count) {
    cout << endl << "--- All Books ---" << endl;

    if (count == 0) {
        cout << "No books in library!" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << endl << "Book #" << i + 1 << endl;
        cout << "Title: " << books[i].title << endl;
        cout << "ISBN: " << books[i].isbn << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "Publisher: " << books[i].publisher << endl;
        cout << "Edition: " << books[i].edition << endl;
        cout << "Copies: " << books[i].copies << endl;
    }
}