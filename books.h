#ifndef BOOKS_H_INCLUDED
#define BOOKS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAXSTRING 100
#define MAXREVIEWS 50

typedef enum{
    fiction=0,
    scientific=1,
    politics=2
}genres;

typedef struct bookR* book; //Pointer 'book' pointing to addresses of variables /w type: bookR.
struct bookR{ //I'm sorry, i have changed the signature from book->bookR.

   char author[MAXSTRING];

   char title[MAXSTRING];

   genres genre;

   int id;

   char reviews[MAXREVIEWS][MAXSTRING];

};

typedef struct listR* list; //Pointer 'list' pointing to addresses of variables /w type: listR.
struct listR {
    book data;
    list link; // pointer we will need in order to point to next listR.
};



void printMenu(); //Printing the menu to the user.
book addInfo(); // Creating a book object and adding info given from user.
int addBook(book b, list bList); //Adding the book we created with addInfo() into the list.
list list_creation(book b); //Creating the list(adding the first book) if it does not exist.
void list_show(list bList); //Showing all the elements of the list.
book findBook(book b, list bList); //Searching for a book based on ID.
int deleteBook(book b, list bList); //Deleting a book based on ID.
void updateId(list bList); // Updating ID's after deleting a book.
void print(book b);//Shows the info of a specific book based on ID.
int updateBook(book b, list bList);  //Update book based on ID.
void availableBooks(list bList); //Showing all the available book ID's to delete or update.
void save(char *filename, list bList);  //Saving list of books into the file.
list load(char *filename, list bList);  //Loading list of books from the file.
void addingReview(book b); //Adding new review to existing book.



#endif // BOOKS_H_INCLUDED
