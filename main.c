
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "books.h"


/*
==============================================
    Author:      Christopher Vradis
    A.M:         21308
    Tutor:       Konstantinos Tserpes
    Description: Project for DIT (HUA), Book application.
                 Comments have been written in English to
                 make it easier for you to read and for me
                 to write them.
    O.S:         Windows 10
    I.D.E:       Code::Blocks 16.01
==============================================
*/

int main(int argc, char *argv[])
{


    system ("color 0F"); // Changing background and text color. WINDOWS ONLY.
    printf("\n[Name of .exe running: %s]\n\n",argv[0]);


    if(argc==2){
    int choice, id_search; //'choice' variable to store user's input for menu. 'id_search' variable to store the id the user wants to search for.
    list headNode = NULL; //list pointer to check if the list is empty or not.

    /*
    ===============================================================
    new_book is needed to store the data of the book that user gave.
    s_book is needed in order to search for a specific id.
    result is needed to store the data of the book we found.
    ===============================================================
    */
    book new_book, s_book, result;
    int flag=1; // A variable we will need to reshow the menu to the user.


    printf("               |---------------------------------|\n");
    printf("               |        LOADING BOOK LIST        |\n");
    printf("               |---------------------------------|\n");
    headNode = load(argv[1],headNode); //Changing value of our headNode.


    while(flag){//while flag remains 1 reshow the menu.

    printf("               |---------------------------------|\n");
    printf("               |          BOOK APPLICATION       |\n");
    printf("               |---------------------------------|\n\n");
    printf("[Working on file: %s]\n",argv[1]);
    printMenu();
    printf("User input:    ");
    scanf("%d",&choice); //Stores the input of the user into var. 'choice'.
    fflush(stdin); //Invoking undefined behavior.
    printf("\n"); //Putting a space to make it clearer.


   /*
   ===========================================================
    While the user selects a non existing number from the menu,
    show error message, reprint the menu, rescan his choice.
   ===========================================================
   */
      while (  choice<1  || choice>7  ){
        printf("\n\n\n                    WRONG INPUT!");
        printf("\n\n\n------- Please pick a number from range 1-6. -------\n\n");
        printf("[Working on file: %s]\n",argv[1]);
        printMenu();
        printf("User input:    ");
        scanf("%d",&choice);
        fflush(stdin); //Invoking undefined behavior.
        printf("\n");
    }


    switch(choice){

        case 1:
            printf("               |---------------------------------|\n");
            printf("               |           ADDING BOOK           |\n");
            printf("               |---------------------------------|\n\n");
            new_book = addInfo(); //Saving book info given by the user in new_book.
            /*
            ==================================================
            We have to check if this is the first book or not
            using the list pointer named 'headNode' we created.
            ==================================================
            */
            if(headNode!=NULL){//It's not the first book.
                addBook(new_book,headNode); //Add book to the List.
                updateId(headNode); //Re-update the IDs.
            }else { //It's the first book.
                headNode = list_creation(new_book);
                 /*
                 =================================================================
                 Now headNode stores the address of a listR variable with the data
                 of new_book and a pointer 'link' having value NULL until we
                 add a new book.
                 =================================================================
                */
            }
            printf("Returning to the Main Menu in 2 seconds..\n\n");
            Sleep(2000); //Waiting 2 seconds before reshowing the menu.
            break;
        case 2:
            printf("               |---------------------------------|\n");
            printf("               |           DELETING BOOK         |\n");
            printf("               |---------------------------------|\n\n");

            s_book = (book)malloc(sizeof(struct bookR)); //Allocating memory for a book variable named s_book.

            availableBooks(headNode); //Showing which book ID's exist to help the user choose one.
            printf("Enter the ID of the book you would like to delete:      ");
            scanf("%d", &id_search);
            fflush(stdin); //Invoking undefined behavior.
            s_book->id=id_search; //Storing the ID given by the user to the book's ID we created.
            result = findBook(s_book, headNode); //Storing the data if the book has been found, else is NULL.

            if( result!=NULL){ //If book has been found.
                if(result->id==1){ //If the book that he wants to delete has ID of 1 do:
                    list temp=headNode->link; //Saving the link pointer of the first node to change it to Null.
                    headNode=headNode->link; //headNode now points to second node which will become the first after deleting first node.
                    deleteBook(result,temp);
                }else {
                deleteBook(result, headNode);
                }
                updateId(headNode); //Updating the ID's after deleting the node, keeping the IDs of the books unique.
            }else{ //If book with given ID has not been found.
                printf("No book with id: %d has been found in the list.\n\n",id_search);
            }

            break;
        case 3:
            printf("               |---------------------------------|\n");
            printf("               |          SEARCHING BOOK         |\n");
            printf("               |---------------------------------|\n\n");
            s_book = (book)malloc(sizeof(struct bookR)); //Allocating memory for a book variable named s_book.

            printf("Enter the ID of the book you would like to search:      ");
            scanf("%d", &id_search);
            fflush(stdin); //Invoking undefined behavior.
            s_book->id=id_search; //Storing the ID given by the user to the book's id we created.
            result = findBook(s_book, headNode); //Storing the data if the book has been found, else is NULL.
            if( result!=NULL){ //If book has been found.
                int show=0;
                printf("Book has been found. Would you like to print it's info?\n");
                printf("\t[1]Yes.\n\t[2]No\n");
                printf("User Input:    ");
                scanf("%d",&show);
                fflush(stdin); //Invoking undefined behavior.
                while(show<1 || show>2){ //While he gives a wrong input.
                   printf("WRONG INPUT. Please type 1 to print book's info or 2 to go back to the main menu.\n");
                   printf("User Input:    ");
                   scanf("%d",&show);
                   fflush(stdin); //Invoking undefined behavior.
                }
                 if(show==1){ // If user says yes.
                    print(result);
                    Sleep(2000);//Waiting 2 seconds before reshowing the menu.
                }else{ //If user says no.
                    printf("Redirecting to Main Menu..\n");
                    Sleep(1000); //Waiting 1 second before reshowing the menu.
                    break;
                }

            }else{//If book has not be found.
                printf("No book with id: %d has been found in the list.\n\n",id_search);
            }
            break;
        case 4:
            printf("               |---------------------------------|\n");
            printf("               |          EDITING BOOK           |\n");
            printf("               |---------------------------------|\n\n");
            s_book = (book)malloc(sizeof(struct bookR)); //Allocating memory for a book variable named s_book.
            availableBooks(headNode); //Showing which book ID's exist to help the user choose one.

            printf("Enter the ID of the book you would like to edit:      ");
            scanf("%d", &id_search);
            fflush(stdin); //Invoking undefined behavior.
            s_book->id=id_search; //Storing the ID given by the user to the book's id we created.
            result = findBook(s_book, headNode); //Storing the data if the book has been found, else is NULL.
            if( result!=NULL){ //If book has been found.
                    printf("\nBook has been found. Editing book's info...\n\n");
                    updateBook(result,headNode);
                    printf("Book info has been updated. Returning to the Main Menu in 3 seconds..\n\n");
                    Sleep(3000); //Waiting 3 seconds before reshowing the menu.
            } else{ //If book has not been found.
                 printf("No book with ID: %d has been found in the list.\n\n",id_search);
                 printf("Returning to the Main Menu in 2 seconds..\n\n");
                 Sleep(2000); //Waiting 2 seconds before reshowing the menu.
            }
            break;
        case 5:
            printf("               |---------------------------------|\n");
            printf("               |         PRINTING BOOKS          |\n");
            printf("               |---------------------------------|\n\n");
            list_show(headNode); //Showing all the books from the list.
            Sleep(2000); //Waiting 2 seconds before reshowing the menu.
            break;
        case 6:
            printf("               |---------------------------------|\n");
            printf("               |          ADDING REVIEW          |\n");
            printf("               |---------------------------------|\n\n");
            s_book = (book)malloc(sizeof(struct bookR)); //Allocating memory for a book variable named s_book.
            availableBooks(headNode); //Showing which book ID's exist to help the user choose one.

            printf("Enter the ID of the book you would like to add a review:      ");
            scanf("%d", &id_search);
            fflush(stdin); //Invoking undefined behavior.
            s_book->id=id_search; //Storing the ID given by the user to the book's id we created.
            result = findBook(s_book, headNode); //Storing the data if the book has been found, else is NULL.
            if( result!=NULL){ //If book has been found.
                    printf("\nBook has been found. Adding review to the book...\n\n");
                    addingReview(result);
                    printf("Review has been added. Returning to the Main Menu in 3 seconds..\n\n");
                    Sleep(3000); //Waiting 3 seconds before reshowing the menu.
            } else{
                 printf("No book with ID: %d has been found in the list.\n\n",id_search);
                 printf("Returning to the Main Menu in 2 seconds..\n\n");
                 Sleep(2000); //Waiting 2 seconds before reshowing the menu.
            }
            break;
        default:
            printf("               |---------------------------------|\n");
            printf("               |       EXITING APPLICATION       |\n");
            printf("               |---------------------------------|\n\n");
            save(argv[1],headNode); //Saving the list into file before exiting.
            Sleep(2000); //Waiting 2 seconds before reshowing the menu.
            flag=0; //Changing to 0 in order to end the while loop and the program.
            break;
    }
    }
    } else { //Printf's if number of arguments is wrong.
        printf("|----------------------------------------------------------------|\n");
        printf("|          -!ERROR!- WRONG NUMBER OF ARGUMENTS GIVEN.            |\n");
        printf("|CORRECT No. of arguments: 2.                                    |\n");
        printf("|YOUR    No. of arguments: %d                                     |\n",argc);
        printf("|1st argument: name of .exe | 2nd argument: name of book to load.|\n");
        printf("|Please retry and follow the instructions of the row above.      |\n");
        printf("|----------------------------------------------------------------|\n");
    }

    return 0;

}
