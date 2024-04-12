#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
///Khuffash

typedef struct
{
    int student_id;
    int t_date;
    char travelling_time[10];
    char destination[15];
    char fromArea[15];

} passengers ;

typedef struct
{
    int bus_NO;
    int t_date;
    char travelling_time[10];
    char destination[30];
    char fromArea[30];
    float ticket;
    int capicity;
    struct node *Next;
} busses;

struct node
{
    passengers passenger_node ;
    struct node *Next;
};

int counter(char filename[50]) //function to count the lines in files, hence will count the number of busses/passengers in each file
{

    FILE *fp;
    int count = 0;
    char c;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;
    return count+2;
}

void removeChar(char * str, char charToRemmove)//function to remove a character in a specific string, used this to remove ':' in traveling time for the passenger and departure time for the bus;
{
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++)
    {
        if(str[i] == charToRemmove)
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }
}

void insert_end_bus(busses bus_array[],passengers data,int index)// this function will assign passengers to buses according to some conditions
{
    struct node *ptr=(struct node *)malloc(sizeof(struct node));
    struct node *tmp;
    ptr->passenger_node=data;
    if(bus_array[index].Next==NULL)
    {
        ptr->Next=NULL;
        bus_array[index].Next=ptr;
    }
    else
    {
        tmp=bus_array[index].Next;
        while(tmp->Next != NULL)
        {
            tmp=tmp->Next;
        }
        tmp->Next=ptr;
        ptr->Next=NULL;
    }
}

void printbusses(busses bus_array[],int index)//this function will Print a specific bus information along with its passengers informations
{
    struct node *ptr;
    ptr=bus_array[index].Next;
    if(bus_array[index].Next==NULL)
    {
        printf("Bus is empty\n");
        return;
    }
    printf("*Bus Number\t*Date\t*Departure-time\t*From\t\t*To\n");
    printf("%5d\t%14d\t%10s\t%5s\t%5s\n\n",bus_array[index].bus_NO,bus_array[index].t_date,bus_array[index].travelling_time,bus_array[index].fromArea,bus_array[index].destination);
    printf("Students Assinged to This Bus: \n ");
    printf("*Student Id\t*Date\t*Travelling Time\t\t*From\t\t*To\n");

    while(ptr != NULL)
    {

        printf("%5d\t%14d\t%10s\t\t%15s\t%15s\n",ptr->passenger_node.student_id,ptr->passenger_node.t_date,ptr->passenger_node.travelling_time,ptr->passenger_node.fromArea,ptr->passenger_node.destination);
        ptr=ptr->Next;
    }
}

struct node *head;
void insert_end_passenger(passengers data)//this function creates the linked list for passengers and inserts at end.
{
    struct node *ptr=(struct node *)malloc(sizeof(struct node));
    struct node *temp;

    ptr->passenger_node=data;
    if(head==NULL)
    {
        ptr->Next=NULL;
        head=ptr;
    }
    else
    {
        temp=head;
        while(temp->Next != NULL)
        {
            temp=temp->Next;
        }
        temp->Next=ptr;
        ptr->Next=NULL;
    }

}
void displayList() //this function prints the linked list
{
    struct node *ptr;
    ptr=head;
    if(head==NULL)
    {
        printf("List is empty");
        return;
    }
    printf("*Student Id\t*Date\t*Travelling Time\t\t*From\t\t*To\n");
    while(ptr != NULL)
    {
        printf("%5d\t%14d\t%10s\t\t%15s\t%15s\n\n",ptr->passenger_node.student_id,ptr->passenger_node.t_date,ptr->passenger_node.travelling_time,ptr->passenger_node.fromArea,ptr->passenger_node.destination);
        ptr=ptr->Next;
    }

}
struct node *head_unmatched;
void insert_end_unmatched(passengers data)//this function inserts a specific node at unmatched linked list
{
    struct node *ptr=(struct node *)malloc(sizeof(struct node));
    struct node *temp;

    ptr->passenger_node=data;
    if(head_unmatched==NULL)
    {
        ptr->Next=NULL;
        head_unmatched=ptr;
    }
    else
    {
        temp=head_unmatched;
        while(temp->Next != NULL)
        {
            temp=temp->Next;
        }
        temp->Next=ptr;
        ptr->Next=NULL;
    }

}
void displayList_unmatched()// this function prints the unmatched linked list
{
    struct node *ptr;
    ptr=head_unmatched;
    if(head_unmatched==NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("*Student Id\t*Date\t*Travelling Time\t\t*From\t\t*To\n");
    while(ptr != NULL)
    {
        printf("%5d\t%14d\t%10s\t\t%15s\t%15s\n",ptr->passenger_node.student_id,ptr->passenger_node.t_date,ptr->passenger_node.travelling_time,ptr->passenger_node.fromArea,ptr->passenger_node.destination);
        ptr=ptr->Next;
    }

}
void DeleteList(struct node *head)//this function deletes a linked list
{
    struct node *ptr,*tmpnode;
    ptr=head->Next;
    head->Next=NULL;

    while(ptr!=NULL)
    {
        tmpnode=ptr->Next;
        free(ptr);
        ptr=tmpnode;
    }
}

void Delete_node(struct node *head_delete,int stu_id)//this function deletes a specific node at a linked list
{
    struct node *tmp=head_delete;
    struct node *prev;
    /*
    if(tmp != NULL && tmp->passenger_node.student_id == stu_id)//checks if the head contains the id *will not enter / head does not contain data
    {
        head_delete=tmp->Next;
        free(tmp);
        return;
    }*/
    while(tmp != NULL && tmp->passenger_node.student_id != stu_id)
    {
        prev=tmp;
        tmp=tmp->Next;
    }
    if(tmp == NULL)
        return;
    prev->Next=tmp->Next;
    free(tmp);
    printf("Passenger Deleted!\n");
}

int main()
{
    FILE *passenger;
    passenger=fopen("passengers.txt","r");

    if(!passenger) printf("ERROR LOADING THE PASSENGER FILE");//checks if the file exists
    char passenger_info[150];

    while(!feof(passenger))//while loop to read the passenger data from passenger file and store them into a linked list
    {
        passengers temp_passenger;

        fgets(passenger_info,150,passenger);

        int *cutter=strtok(passenger_info,"#");
        temp_passenger.student_id=atoi(cutter);

        cutter=strtok(NULL,"#");
        temp_passenger.t_date=atoi(cutter);

        cutter=strtok(NULL,"#");
        strcpy(temp_passenger.travelling_time,cutter);

        cutter=strtok(NULL,"#");
        strcpy(temp_passenger.fromArea,cutter);

        cutter=strtok(NULL,"#");

        int *cutline=strtok(cutter,"\n");
        strcpy(temp_passenger.destination,cutline);

        insert_end_passenger(temp_passenger);
    }

    FILE *buss;
    buss=fopen("busses.txt","r");

    if(!buss) printf("ERROR LOADING THE PASSENGER FILE");//checks if the file exists
    int index=counter("busses.txt")-1;


    busses bus_array[index];

    int i=0;
    char buss_info[150];
    while(!feof(buss))//while loop to read the buses data from the buses file and store them into Array
    {

        fgets(buss_info,150,buss);

        int *cutterb=strtok(buss_info,"#");
        bus_array[i].bus_NO=atoi(cutterb);

        cutterb=strtok(NULL,"#");
        bus_array[i].t_date=atoi(cutterb);

        cutterb=strtok(NULL,"#");
        strcpy(bus_array[i].travelling_time,cutterb);

        cutterb=strtok(NULL,"#");
        strcpy(bus_array[i].fromArea,cutterb);

        cutterb=strtok(NULL,"#");
        strcpy(bus_array[i].destination,cutterb);

        cutterb=strtok(NULL,"#");
        bus_array[i].ticket=atof(cutterb);

        cutterb=strtok(NULL,"#");
        bus_array[i].capicity=atoi(cutterb);

        bus_array[i].Next=NULL; // making a header for every index
        i++;
    }

    int print_choice;
    passengers p1;
    struct node *ptr_trvs=head;


    while(1) //while loop which will list the option for the user;
    {
        printf("1. Load the bus information file\n");
        printf("2. Load the passenger information file\n");
        printf("3. Assign passengers and print assignment information of all busses\n");
        printf("4. Print a specific bus information along with its passengers information (names and IDs)\n");
        printf("5. Print unmatched passengers\n");
        printf("6. Add new passenger\n");
        printf("7. Delete passenger\n");
        printf("8. Delete bus number\n");
        printf("9. Exit\n");
        int choice=0;
        printf("Enter Your Choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("*Bus Number\t*Date\t*Departure-time\t*From\t\t*To\t*Price of Ticket\t*Capacity\n");
            for(int i=0; i<index; i++) //for loop to print the bus data
            {
                printf("%5d\t%14d\t%10s\t%5s\t\t%5s\t%.1f\t%15d\n\n",bus_array[i].bus_NO,bus_array[i].t_date,bus_array[i].travelling_time,bus_array[i].fromArea,bus_array[i].destination,bus_array[i].ticket,bus_array[i].capicity);
            }
            break;

        case 2:
            displayList();
            break;

        case 3:
           ///every passenger loops for all the buses and so on
            while(ptr_trvs != NULL)//while loop to loop the passengers
            {
                int counter2=0;

                for(int i=0; i<index; i++)//for loop to loop the buses
                {
                    char temp1[10],temp2[10];

                    strcpy(temp1,ptr_trvs->passenger_node.travelling_time);
                    (temp1,':');
                    int pass_t=atoi(temp1);

                    strcpy(temp2,bus_array[i].travelling_time);
                    removeChar(temp2,':');
                    int bus_t=atoi(temp2);


                    if((ptr_trvs->passenger_node.t_date==bus_array[i].t_date) && (strcmp(ptr_trvs->passenger_node.fromArea,bus_array[i].fromArea)==0) && (bus_array[i].capicity>0)&& ((strcmp(ptr_trvs->passenger_node.destination,bus_array[i].destination ))==0) && (bus_t>=pass_t)==1)
                    {//condition to assign every passenger to certain bus
                        printf("Assigned: %d to %d\n",ptr_trvs->passenger_node.student_id,bus_array[i].bus_NO);
                        insert_end_bus(bus_array,ptr_trvs->passenger_node,i);
                        bus_array[i].capicity--;//decreases the capacity if the condition satisfies
                    }
                    else
                    {
                        counter2++;//counts how many times the condition does not satisfy
                    }
                }
                if(counter2==index)//if the counter equals the number of busses then no bus accepts that passenger then assign it to unmatched
                {
                    printf("Assigned: %d to *unmatched\n",ptr_trvs->passenger_node.student_id);
                    insert_end_unmatched(ptr_trvs->passenger_node);
                }

                ptr_trvs=ptr_trvs->Next;//to traverse the linked lsit
            }
            break;

        case 4:
            printf("Please Enter the bus number: ");
            scanf("%d",&print_choice);

            for(int i=0; i<index; i++)//for loop to check what bus has been entered
            {
                if(print_choice==bus_array[i].bus_NO)
                {
                    printbusses(bus_array,i);
                    break;
                }
            }
            break;

        case 5:
            printf("Students that have no Bus: \n");
            displayList_unmatched();
            break;

        case 6:
            printf("Enter the Data of the passenger\nStudent number: ");
            scanf("%d",&p1.student_id);
            struct node *ptr=head;
            while(ptr !=NULL)//checks if the id already exists or not.
            {
                if(p1.student_id==ptr->passenger_node.student_id)
                {
                    while(p1.student_id==ptr->passenger_node.student_id)
                    {
                        printf("ERROR- Enter Another Id: ");
                        scanf("%d",&p1.student_id);
                    }
                }
                ptr=ptr->Next;
            }

            printf("Date: ");
            scanf("%d",&p1.t_date);
            printf("Traveling Time: ");
            scanf("%s",p1.travelling_time);
            printf("From: ");
            //fgets(p1.fromArea,69,stdin);
            scanf("%s",p1.fromArea);
            printf("To: ");
            //fgets(p1.destination,69,stdin);
            scanf("%s",p1.destination);
            int counter3;

            char temp1[10],temp2[10];
            strcpy(temp1,p1.travelling_time);
            removeChar(temp1,':');
            int pass_t=atoi(temp1);

            strcpy(temp2,bus_array[i].travelling_time);
            removeChar(temp2,':');
            int bus_t=atoi(temp2);

            for(int i=0; i<index; i++)
            {
                if((p1.t_date==bus_array[i].t_date) && (strcmp(p1.fromArea,bus_array[i].fromArea)==0) && (bus_array[i].capicity>0)&& ((strcmp(p1.destination,bus_array[i].destination ))==0) && (bus_t>=pass_t)==1)
                {
                    insert_end_bus(bus_array,p1,i);
                    printf("Assigned: %d to %d\n", p1.student_id,bus_array[i].bus_NO);
                    bus_array[i].capicity--;

                }
                else
                {
                    counter3++;

                }
            }
            if(counter3==index)
            {
                insert_end_unmatched(p1);
                printf("Assigned: %d to *unmatched\n", p1.student_id);
            }
            break;
        case 7:
            //array[i] to null / unmatched to null;
            //delete //c
            //re ; case 3

            for(int i=0; i<index; i++)
            {
                bus_array[i].Next=NULL;
            }
            DeleteList(head_unmatched);
            head_unmatched=NULL;
            printf("Enter a student Id to delete: ");
            int stu_id;
            scanf("%d",&stu_id);
            ///
            Delete_node(head,stu_id);
            ///

            ptr_trvs=head;
            while(ptr_trvs != NULL)
            {
                int counter2=0;

                for(int i=0; i<index; i++)
                {
                    char temp1[10],temp2[10];

                    strcpy(temp1,ptr_trvs->passenger_node.travelling_time);
                    removeChar(temp1,':');
                    int pass_t=atoi(temp1);

                    strcpy(temp2,bus_array[i].travelling_time);
                    removeChar(temp2,':');
                    int bus_t=atoi(temp2);

                    if((ptr_trvs->passenger_node.t_date==bus_array[i].t_date) && (strcmp(ptr_trvs->passenger_node.fromArea,bus_array[i].fromArea)==0) && (bus_array[i].capicity>0)&& ((strcmp(ptr_trvs->passenger_node.destination,bus_array[i].destination ))==0) && (bus_t>=pass_t)==1)
                    {
                        //printf("Assigned: %d to %d\n",ptr_trvs->passenger_node.student_id,bus_array[i].bus_NO);
                        insert_end_bus(bus_array,ptr_trvs->passenger_node,i);
                        bus_array[i].capicity--;


                    }
                    else
                    {
                        counter2++;

                    }
                }
                if(counter2==index)
                {
                    //printf("Assigned: %d to *unmatched\n",ptr_trvs->passenger_node.student_id);
                    insert_end_unmatched(ptr_trvs->passenger_node);
                }

                ptr_trvs=ptr_trvs->Next;
            }
            break;
        case 8:
            //finds the bus to be deleted -> shift the array
            for(int i=0; i<index; i++)
            {
                bus_array[i].Next=NULL;
            }
            DeleteList(head_unmatched);
            head_unmatched=NULL;




            printf("Enter a Bus Number to Delete : ");
            int bus_no;
            scanf("%d",&bus_no);

            int flag3=0;
            int flag;
            for(int i=0; i<index; i++)
            {
                if(bus_array[i].bus_NO==bus_no)
                {
                    flag=i;
                    flag3=1;
                    break;
                }
            }

            if(flag3!=1)
            {
                printf("Bus not Found !\n");
            }
            else
            {
                // printbusses(bus_array,i);
                printf("Bus Deleted!\nRe-Assaining Passengers:\n");
            }



            for(int i = flag-1; i<index-1; i++)
            {
                bus_array[i+1]=bus_array[i+2];
            }
            index--;

            //displayList();
            ptr_trvs=head;
            while(ptr_trvs != NULL)
            {
                int counter2=0;

                for(int i=0; i<index; i++)
                {
                    char temp1[10],temp2[10];

                    strcpy(temp1,ptr_trvs->passenger_node.travelling_time);
                    removeChar(temp1,':');
                    int pass_t=atoi(temp1);

                    strcpy(temp2,bus_array[i].travelling_time);
                    removeChar(temp2,':');
                    int bus_t=atoi(temp2);

                    if((ptr_trvs->passenger_node.t_date==bus_array[i].t_date) && (strcmp(ptr_trvs->passenger_node.fromArea,bus_array[i].fromArea)==0) && (bus_array[i].capicity>0)&& ((strcmp(ptr_trvs->passenger_node.destination,bus_array[i].destination ))==0) && (bus_t>=pass_t)==1)
                    {
                        printf("Assigned: %d to %d\n",ptr_trvs->passenger_node.student_id,bus_array[i].bus_NO);
                        insert_end_bus(bus_array,ptr_trvs->passenger_node,i);
                        bus_array[i].capicity--;


                    }
                    else
                    {
                        counter2++;

                    }
                }
                if(counter2==index)
                {
                    printf("Assigned: %d to *unmatched\n",ptr_trvs->passenger_node.student_id);
                    insert_end_unmatched(ptr_trvs->passenger_node);
                }

                ptr_trvs=ptr_trvs->Next;
            }


            break;
        case 9:
            return;
            break;
        default:
            printf("WRONG CHOICE-REENTER\n");
        }

    }
    fclose(passenger);
    fclose(buss);


    return 0;
}
