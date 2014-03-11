/* Program to display a lotto  game.  Users are presented with a menu of 6 options.  
    They are not allowed to select options 2-5 until option 1 of 
    playing, i.e, entering the numbers, the game is chosen and completed without errors of duplication. 
    They should then be able to access the menu
    to display, sort, compare,. show frequency of entries and play again.

    Date: 14th March 2012
    Author: Aisling Friel
*/
//test 1 from github.com
#include <stdio.h> 
#include <conio.h>
#define ROW 6 //for array of lotto numbers
#define LIST 42 //for the amount of eligible numbers


/*Declare Function Prototypes*/
void lottery(int*, int, int*, int*,int, int*,int);
void display(int*, int, int*);
void sort(int*, int);
void win(int*, int, int*);
void frequency(int*, int, int*, int);
void exit();

main()
{
    int num[ROW]; //lottter numbers
    int countNum[LIST]= {0};//for frequency of numbers inputted
    int countBonus[LIST]= {0}; //for frequency of bonus numbers inputted
    
    int num1=0;
    int *bonus;
    int bon = 0;
    int fake = 0;
    
    bonus = &bon;
       
    
    printf("\n\nWelcome to the Lottery Game\n"
    "Below are the Menu Options\n\n");
    
    //begin fake menu- only allows user to enter 1 to play lotto
    
    printf("\n\n\n\nMenu items\n\n"  
    "1   Play Lotto\n"
    "2   Display Your Current Lotto Numbers \n"
    "3   Sort Your Lotto Numbers\n"
    "4   Have You Won?\n"
    "5   Compare Number Input Frequency\n"
    "6   Exit\n");
    
    printf("\n\nInput a single number for menu\n");
    scanf("%d", &fake);//number from 0-9 is inputted
    flushall();
    
    while (fake !=1)
    {
        printf("You must play the lotto before choosing anyother option\n");
        scanf("%d", &fake);
        flushall();
            
    }//end while for fake menu
    
    if (fake==1)
        lottery(num,ROW, bonus, countNum,LIST, countBonus, LIST);//playAgain () won't be called until user enters 1
        
    printf("Thank you for entering your numbers\n");
    
    //Real Menu options below
    
    while (num1!=6)
    {//begin while (choice is not exit)  for the main menu
    
       printf("\n\nMenu items\n\n"  
        "1   Play Lotto\n"
        "2   Display Your Current Lotto Numbers \n"
        "3   Sort Your Lotto Numbers\n"
        "4   Have You Won?\n"
        "5   Compare Number Input Frequency\n"
        "6   Exit\n");
    
        printf("\n\nInput a single number for menu\n");
        scanf("%d", &num1);//number from 0-9 is inputted
        flushall();
   
        switch (num1)//depending on user's choice of number a function is called.
        {
            case 1:
                lottery(num,ROW, bonus, countNum,LIST, countBonus, LIST);
                break;
            case 2:
                display(num,ROW, bonus);
                break;
            case 3:
                sort(num,ROW);
                break;
            case 4:
                win(num, ROW,bonus);
                break;
            case 5:
                frequency(countNum, LIST, countBonus, LIST);
                break;
            case 6:
                exit();
                break;
        
            default:
                printf("this is an invalid entry");
        }//end switch operation
    }//end while (num! = 6) for menu

}// end main


//*ptr = num[ROW]; *pcnum = countNum[LIST]; *pcbonus = countBonus[LIST]
//implement fxn lottery()
void lottery(int *ptr, int,int *bonus, int *pcnum,int, int *pcbonus,int)
{
   
    int i;
    int counter = 0;
    int value;
    
    printf("\n\n\nPlease enter your bonus number\n");
    scanf("%d", bonus);
    flushall(); //to clear buffer in case of character entry
    
    
    while (*bonus <1 || *bonus >42)
    {
        printf("Your bonus number should be between 1 and 42\n");
        scanf("%d", bonus);
        flushall();
    }
    
    (*(pcbonus + (*bonus-1)))++;//increments the counting bonus array by 1 via element number of bonus number (-1 as array starts at 0)
    
    
    //Entering the 1st of the 6 lotto numbers;
    printf("Enter 6 numbers\n\n");
    
    scanf("%d", &value);
    flushall();
    
    while ((value <1 || value >42)||(*bonus== value))
    {
        printf("Invalid Entry.\n"
        "Entry should be a number between 1 and 42 that is different from Bonus Number.\n");
        scanf("%d", &value);
        flushall();
    }//end while() error checking for first entry of lotto numbers
    
    
    *(ptr +0) = value; //once error checking is done-number is automatically entered into the first element of array
    
    (*(pcnum + (value-1)))++; // increments the value (-1 to allow for array starting at 0) equivalent element number of  CountNum array by 1. 
    //eg if value 42 then CountNum[41] is incremented
    counter++;//see below
    
 //as long as counter is less than ROW
    while(counter < ROW)//counter starts at 1 as first number is already inputted in array (no need to check it against itself)
    {
        //expect new lotto number input
        scanf("%d", &value);
        flushall();
        
            
        //check each value in array against current lotto number value up as far as counter value
        for(i = 0; i < counter ;i++)
        {
            if (*bonus== value)
            {
            printf("This is the same as bonus - enter again\n");
            i=counter +1;  //goes out of for() and skips if() to go back to while loop()
                
            }//end if () checking if lotto number is the same as the bonus number
        

            //if current lotto number already exists in the array
            if(*(ptr+i) == value)
            {
                printf("Duplicate - enter other number\n\n");
                //stop looking at values in array and exit for() as i> counter
                i=counter +1; 
                
            }//end if() to see if lotto number is already entered
            
           
            if(value <1 || value >42)
            {
                printf("Input must be a number between 1 and 42\n\n");
                //stop looking at values in array and exit for()
                i=counter + 1;
                
            }//end if
            
        }//end for () checking for duplicates and invalid entries-if none, i will be equal to counter
        

        //if current lotto number not found in array  and not equal to bonus
        //add it to the end of the values already found and increment counter by 1
        
        if(i==counter)
        {
            *(ptr + (counter)) = value;//puts value into counter value element of array
            
        
            /*increment the count of lotto numbers played by 1 using the element number of value (-1)*/
            (*(pcnum + (value - 1)))++; 
            
            counter++; //counter is incremented and program goes back to start of while loop()
            
        }//end if () to save correct entry lotto number
        
    }//while () for inputting lotto numbers
    
}//end fxn lottery()


void display(int *ptr, int, int *bonus)
{
    int i;
    
    for (i=0; i<ROW; i++)
    {
        printf("Your Lotto numbers are %d\n", *(ptr+i));
        
    }
    printf("Your bonus number is %d\n", *bonus);
}//end fxn display()


/*Implement Function sort()*/
void sort(int *ptr, int)
{
    int i, j, temp;
    
    //sort the numbers
    for (i = 0; i <ROW-1; i++)
    {
        for(j=0; j<ROW-1; j++)
        {
            if (*(ptr +(j+1))< (*(ptr+j)))
            {
                temp = *(ptr+j);
                *(ptr+j) = *(ptr+(j+1));
                *(ptr+(j+1))= temp;
            }//end if
            
        }//end inner for
    }//end outer for() to sort numbers
    
    for( i = 0; i<ROW; i++)
    {
        printf("Number %d of your lotto numbers is %d\n",i+1,*(ptr+i));
    }
    
}//end fxn sort


/*Implement function win()*/
void win(int *ptr,int, int *bonus)
{
    int i;
    int total = 0;
    int win[ROW]= {1,3,5,7,9,11};
    int spare = 42;
    int j;
    
    /*Check if the numbers in the array match the winning numbers*/
    for (j=0;j<ROW; j++)
    {
        for( i = 0; i<ROW; i++)
        {
            if (*(ptr+j) == win[i])
            {
                total++;
            }//end if
        
        }//end for
    }///end outer for () checking for winning numbers.
    
    
    printf("\nMatch %d numbers\n", total);
    if (total ==6)
        printf("\nMatch 6\tJackpot\n");
    if(total == 5 && *bonus == spare)
        printf("\nMatch 5 + Bonus\tAlmost - just 1 away\n");
    if (total == 5)
        printf("\nMatch 5\tHolidays paid for\n");
    if(total == 4 && *bonus == spare)
        printf("\nMatch 4 + Bonus\tNight out\n");
    if (total == 4)
        printf("\nMatch 4\tFull petrol tank\n");
    if(total == 3 && *bonus == spare)
        printf("\nMatch 3 + Bonus\tFree lotto scratch card\n");
    else printf("No luck today\n");

}//end fxn win()


/*implement function frequency()*/
void frequency( int *pcnum,int, int *pcbonus, int)
{
    int i;
    //check how many times any number has been played for the bonus number
    for (i = 0; i<LIST; i++)
    {
        if (*(pcbonus + i)!=0)
        {
        printf("Bonus Number %d has been played %d times\n", i +1, *(pcbonus + i));//i+1 to allow for array starting at 0
        }//end if
    
    }//end for
    
    //check how many times each lotto number has been played
    for (i = 0; i<LIST; i++)
    {
        if (*(pcnum + i)!=0)
        {
        printf("\nLotto Number %d has been played %d times", i +1, *(pcnum + i));
        }//end if
        
    }//end for to display lotto frequency input
    
}//fxn frequency


/*implement function exit()*/
void exit()
{
    //nothing here as you want to exit program
    
}//end fxn exit()




    
    
        
