#include "books.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void printMenu() {
    printf("Select an action by typing the respective number:\n");
    printf("\t[1] Add a new book.\n");
    printf("\t[2] Delete an existing book.\n");
    printf("\t[3] Search for a book. [OPTIONAL:Print book's info.] \n");
    printf("\t[4] Change book's info.\n");
    printf("\t[5] Print the info of all books.\n");
    printf("\t[6] Add Review on existing book.\n");
    printf("\t[7] Exit & Save.\n");

    return;
}

book addInfo(){
    /*
    =================================================
    Creating a book pointer with name b, pointing to
    a variable type of bookR, and allocating memory
    as much as needed for a variable bookR in order
    to save book's info given by the user.
    =================================================
    */
    book b = (book)malloc(sizeof(struct bookR));
    int genre;

    //Getting book's title.
    printf("[*]Enter book's title:   ");
    fgets(b->title,sizeof(b->title),stdin);

    //Getting author's name.
    printf("[*]Enter author's name:   ");
    fgets(b->author,sizeof(b->author),stdin);

    /*
    ====================================================
    Selecting book's genre. The do-while loop is needed
    in order to check if the user gives a non acceptable
    value.
    ====================================================
    */
do{
    printf("[*]Select book's genre:\n");
    printf("\t[0] Fiction\n");
    printf("\t[1] Scientific\n");
    printf("\t[2] Politics\n");
    printf("User input:    ");
    scanf("%d",&genre);
    fflush(stdin);//Invoking undefined behavior.
    switch(genre) {
        case 0:
            printf("Genre selected -> FICTION\n");
            b->genre=fiction;
            break;
        case 1:
            printf("Genre selected -> SCIENTIFIC\n");
            b->genre=scientific;
            break;
        case 2:
            printf("Genre selected -> POLITICS\n");
            b->genre=politics;
            break;
        default:
            printf("\n\n                    WRONG INPUT!");
            printf("\n\n\n------- Please pick a number from range 0-2. -------\n");

            break;
    }
} while(genre<0 || genre>2);

    b->id=1;
    /*
    =====================================================
    Whenever a book is created it's id will be 1
    until we add it to the list where it will be modified.
    =====================================================
    */


    //Getting book's review.
    printf("[*]Add a review:   \n");
    fgets(b->reviews[0],MAXSTRING,stdin);
    fflush(stdin);

    return b; //Returning the address of the bookR variable with the info given above.
}

list list_creation(book b){
    list headNode;
    headNode=(list)malloc(sizeof(struct listR)); //Typecasting (list) because malloc returns a void pointer.
    headNode->data=b;
    headNode->link=NULL; //Points to NULL because it's the first book.      
    printf("\nList has been created. Book added with ID: %d.\n\n",headNode->data->id);
    return headNode;
}

int addBook(book b, list bList){
    //Our second argument bList is a pointer that points to the head node of the list.


    list newNode =(list)malloc(sizeof(struct listR)); //Creating a new node(listR).
    newNode->data=b;
    newNode->link=NULL; //link pointer of the new node must be set to NULL because we are adding the node at the end of the list.

    list current = bList; //Starting from head node.


    while(current->link != NULL){ //Looping until we find the last node of the list.
        current = current->link; //If not found, replace the current address, with the address of the node that 'current->link' is pointing to.
    }

    current->link=newNode; //Replacing the 'link' pointer of the last node until now, to point to the new node we added to the list.
    newNode->data->id = current->data->id + 1; //The id of the book now is +1 from the previous one.

    printf("\nBook has been successfully added. ID of the new book: %d.\n",newNode->data->id);
    return 0;
}



void list_show(list bList){
   int counting=1;
   int r=0; // To loop through reviews array list.
   if(bList==NULL){ //If no books exist in the list do the following:
        printf("No books exist in the list. Returning to the Main Menu in 2 seconds..\n\n");
   }
   while(bList!=NULL){ //While not last node do:
         char *genretype[15]; //Translating enumeration into respective string.
         if (bList->data->genre==0){
            *genretype="Fiction";
         } else if(bList->data->genre==1){
            *genretype="Scientific";
         } else{
            *genretype="Politics";
         }
        printf("\n[BOOK No%d]\n",counting);
        printf("\tID: %d \n\tTitle: %s\tAuthor: %s\tGenre: %s\n",bList->data->id,bList->data->title,bList->data->author,*genretype);
        r=0; //Making r=0 again to start reading reviews of the next book from scratch.
        while(*(bList->data->reviews[r])!=NULL){
            printf("\tReview [no%d]: %s",r+1,bList->data->reviews[r]);
            r++;
        }
        bList=bList->link; //Go to next node.
        counting++;
   }
   printf("\n");
   return;

}

book findBook(book b, list bList){
    while(bList!=NULL){ //While not last node:
        if(bList->data->id==b->id){ //Checking if the book's id stored in that node is equal to id asked from the user.
            break; //If it's found, break from the loop.
        }
        bList=bList->link; //Go to next node.
    }
    if(bList!=NULL){
        return bList->data; //Returning the data of the book with that ID.
    }else {
        return NULL; //If not found return NULL.
    }
}

int deleteBook(book b, list bList){
    list temp=NULL;
    while(bList!=NULL){ //While not last node:
        if(bList->data->id==b->id){ //Checking if the book's id stored in that node is equal to id asked from the user.
                if(bList->data->id==1){//If it's the first node ( which has an id 1 ):
                       bList=NULL; //link pointer of that node now points to NULL and stops being in our linked list.
                } else{
                    //Step no1:
                    temp->link=bList->link; //Changing the previous node's link.
                    //Step no2:
                    bList->link=NULL; //Changing current node's link to NULL, so it's being removed from the linked list.
                }
            break;
        }
        temp=bList; //Keeping the address of the previous node.
        bList=bList->link; //Go to next node.
    }

    return 0;
}

void updateId(list bList){
    int i=1;
    while(bList!=NULL){ //While not in the last node do the following:
        bList->data->id=i; //Update ID for each book.
        i++; //Increment i. That way we keep the id of each book unique.
        bList=bList->link;//Go to next node.
    }
    return;
}

void print(book b){
    char *genretype[15]; //Translating enumeration into respective string.
    if (b->genre==0){
        *genretype="Fiction";
    } else if(b->genre==1){
        *genretype="Scientific";
    } else{
        *genretype="Politics";
    }

    printf("\nID: %d \nTitle: %sAuthor: %sGenre: %s\n",b->id,b->title,b->author,*genretype);
    int r=0;
    while(*(b->reviews[r])!=NULL){
        printf("Review [no%d]:%s",r+1,b->reviews[r]);
        r++;
    }
    return;
}

int updateBook(book b, list bList){
    int r=0;
    int genre;
    char *genretype[15]; //Translating enumeration into respective string.
    if (b->genre==0){
        *genretype="Fiction";
    } else if(b->genre==1){
        *genretype="Scientific";
    } else{
        *genretype="Politics";
    }


    printf("CURRENT BOOK'S INFO:\n");
    printf("\tID: %d\n\tTitle: %s\tAuthor: %s\tGenre: %s\n",b->id,b->title,b->author,*genretype); //Showing current book's info.
    while(*(b->reviews[r])!=NULL){ //Looping through reviews arrayList and printing out existing reviews.
        printf("\tReview [no%d]:%s",r+1,b->reviews[r]);
        r++;
    }
    printf("-------------\nENTER NEW INFO:\n");
    printf("\tTitle:    ");
    fgets(b->title,sizeof(b->title),stdin); //New title.
    printf("\tAuthor:   ");
    fgets(b->author,sizeof(b->author),stdin); //New author.

    do{
    printf("\t[*]Change book's genre to:\n"); //New genre.
    printf("\t\t[0] Fiction\n");
    printf("\t\t[1] Scientific\n");
    printf("\t\t[2] Politics\n");
    printf("\tUser input:    ");
    scanf("%d",&genre);
    fflush(stdin);//Invoking undefined behavior.
    switch(genre) {
        case 0:
            printf("Genre changed to -> FICTION\n\n");
            b->genre=fiction;
            break;
        case 1:
            printf("Genre changed to -> SCIENTIFIC\n\n");
            b->genre=scientific;
            break;
        case 2:
            printf("Genre changed to -> POLITICS\n\n");
            b->genre=politics;
            break;
        default:
            printf("\n\n\n ------- !Wrong Input! Please pick a number from range 0-2 -------\n\n");
            break;
    }
    } while(genre<0 || genre>2);

    if (b->genre==0){ //Translating enumeration into respective string.
        *genretype="Fiction";
    } else if(b->genre==1){
        *genretype="Scientific";
    } else{
        *genretype="Politics";
    }

    printf("-------------\nNEW BOOK'S INFO:\n");
    printf("\tID: %d\n\tTitle: %s\tAuthor: %s\tGenre: %s\n",b->id,b->title,b->author,*genretype); //Showing new book's info.
    r=0;
    while(*(b->reviews[r])!=NULL){
        printf("\tReview [no%d]:%s",r+1,b->reviews[r]);
        r++;
    }
    return 0;
}

void availableBooks(list bList){
    printf("ID's of books in the list:  ");
    while(bList!=NULL){ //While not last node.
        printf("%d-", bList->data->id); //Showing the id of each book.
        bList=bList->link; //Go to new node.
    }
    printf("\b."); //Moving cursor back to the last '|' and overwriting it with '.'
    printf("\n");
    return;
}


void save(char *filename, list bList){
    FILE *fp;
    int r;
    fp=fopen(filename,"w"); //Opening file to write inside, overwriting in case we updated some books.

    if(bList==NULL){ //If there are no books into the list:
        printf("No list of books have been saved into the file.\n");
        printf("Now exiting..");
    }else {
    while(bList!=NULL){ //While not last node.
        fprintf(fp,"%d\n%s%s%d\n",bList->data->id,bList->data->title,bList->data->author,bList->data->genre); //Writing into the file.
        r=0;
        while(*(bList->data->reviews[r])!=NULL){
            fprintf(fp,"%s",bList->data->reviews[r]);
            r++;
        }
        bList=bList->link; //Moving to next node.
        if(bList!=NULL){ //If it's not the last node.
            fprintf(fp,"\n"); //Adding a new line to separate the books.
        }

    }
            int pbar = 0;
            for (pbar = 0; pbar < 10001; pbar++){
                printf("\rSAVING DATA. Progression:[%d%%]", pbar/100); //A saving progression bar to make it look prettier.
                fflush(stdout);
            }
            printf("\nSaving completed. Now exiting..\n");
    }

    fclose(fp); //Closing the file.
    return;
}


list load(char *filename, list bList){
    FILE *fp;

    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("No file named %s exists. File will be created.\n\n",filename);
        int pbar = 0;
        for (pbar = 0; pbar < 10001; pbar++){
            printf("\rCREATING FILE. Progression:[%d%%]", pbar/100); //A saving progression bar to make it look prettier.
            fflush(stdout);
        }
            printf("\nFile has been created! Redirecting to Main Menu..\n\n");
    } else{
        //edw edw edw
        printf("File has been found.\n");
        int pbar = 0;
        for (pbar = 0; pbar < 10001; pbar++){
            printf("\rLOADING FILE. Progression:[%d%%]", pbar/100); //A saving progression bar to make it look prettier.
            fflush(stdout);
        }
        printf("\n");

        fseek(fp, 0, SEEK_END);
        unsigned long len = (unsigned long)ftell(fp);
        if(len>0){
        
        rewind(fp);
            
        int checker = 1;
        while(checker){//While TRUE, keep reading.
            char ret[MAXSTRING]; //Saving what we read in here.
            book b = (book) malloc(sizeof(struct bookR));
            int j = 0;
            for(j; j < MAXREVIEWS; j++){ //Clearing the reviews array list for the next book.
                strcpy(b->reviews[j], "");
            }
            if(fgets(&ret, sizeof(ret), fp) != NULL){
                fflush(stdin);
                b->id = atoi(ret); //Saving the ID that we read. atoi converts char to int.
            }
            if(fgets(&ret, sizeof(ret), fp) != NULL){
                fflush(stdin);
                strcpy(b->title, ret); //Saving title.
            }
            if(fgets(&ret, sizeof(ret), fp) != NULL){
                fflush(stdin);
                strcpy(b->author, ret); //Saving author.
            }
            if(fgets(&ret, sizeof(ret), fp) != NULL){
                fflush(stdin);
                b->genre = atoi(ret); //Saving genre. atoi is used again.
            }
            if(fgets(&ret, sizeof(ret), fp) != NULL){
                fflush(stdin);
                int i = 0;
                while(ret[0] != '\n'){ //While not new_line which is the separator between books:
                    strcpy(b->reviews[i], ret); //Start adding the reviews.
                    i++;
                    if(fgets(&ret, sizeof(ret), fp) == NULL){
                        fflush(stdin);
                        checker = 0;
                        break;
                    }
                }
            }

            //Adding the book that we read into the list.
            if(bList == NULL){//For the first book we read, create the list.
                printf("\n----------------------------------------------");
                bList = list_creation(b);
            }else{ //Any other book, add it to the list.
                addBook(b, bList);
                printf("-------------------------------------------------------\n");
            }
        }
        


        
        printf("\nFile has been loaded. Redirecting to Main Menu..\n\n");
    } else {
            printf("File is empty.\n\n");
            bList=NULL;            
      }
    }
    fclose(fp); //Closing the file.
    return bList; //Returning our new header, based on what we read.
}


void addingReview(book b){
    int r=0;
    printf("[*]Add a review:   \n");
    while(*(b->reviews[r])!=NULL){//Going through the reviews array list to find an empty block to write new review.
                r++;
    }
    fgets(b->reviews[r],MAXSTRING,stdin); //Reading review from the user.
    fflush(stdin); //Invoking undefined behavior.
    return;
}
