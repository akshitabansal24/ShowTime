#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_seats(int **arr)
{

    printf("   ");
    for (int i=0; i<12; i++)
    {
        printf(" %d ",i);
    }
    printf("\n\n");

    for (int i=0; i<10; i++)
    {
        printf("%c  ",i+65);
        for (int j=0; j<12; j++)
        {
            if (arr[i][j]==0)
            {
                printf("\x1b[32m - \x1b[0m");
            }
            else if(arr[i][j]==1)
            {
                printf("\x1b[31m X \x1b[0m");
            }
            else if(arr[i][j]==2)
            {
                printf("\x1b[33m O \x1b[0m");
            }
        }
        printf("\n");
    }

}

int** fill_seats()
{

    int **seats = malloc(sizeof(int*) * 10);
    for(int i = 0; i < 10; i++)
    {
        seats[i] = malloc(sizeof(int*) * 12);
    }
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<12; j++)
        {

            seats[i][j]=rand()%2;
        }
    }
    return seats;
}

void print_bill(char* movie, char* cinema, char* time, float price, int tickets, char** seats)
{

    FILE *fp;
    fp = fopen("/tmp/yourTicket.txt", "w+");

    fprintf(fp,"\n\n\t**************************************\n\n");

    (tickets==1)?fprintf(fp,"\tDEAR CUSTOMER, YOU BOOKED %d TICKET\n\tFOR %s\n",tickets,movie):fprintf(fp,"\tDEAR CUSTOMER, YOU BOOKED %d TICKETS\n\tFOR %s\n",tickets,movie);

    fprintf(fp,"\tTHE SHOW IS BOOKED AT %s ",cinema);

    fprintf(fp,"AT %s\n",time);

    (tickets==1)? fprintf(fp,"\t%d TICKET OF %.2f IS BOOKED\n",tickets,price): fprintf(fp,"\t%d TICKETS OF %.2f ARE BOOKED\n",tickets,price);

    fprintf(fp,"\tTOTAL AMOUNT TO BE PAID IS: %.2f\n",tickets*price);

    (tickets==1)?fprintf(fp,"\tYOUR SEAT IS :\n"):fprintf(fp,"\tYOUR SEATS ARE :\n");

    for (int i=0; i<tickets; i++)
    {
        (i==tickets-1)? fprintf(fp,"\t%s ",seats[i]): fprintf(fp,"\t%s, ",seats[i]);
    }

    fprintf(fp,"\n\n\t***************************************\n\n\n");
    fclose(fp);

    printf("YOUR TICKET HAS BEEN SAVED IN C:/cygwin64/tmp/yourTicket.txt");

}

int take_input(int min, int max)
{
    int n;
    scanf("%d",&n);
    while(n<min || n>max){
        printf("Invalid response. Please enter between %d and %d\n",min,max);
        scanf("%d",&n);
    }
    return n;
}

void generate_bill(char* movie, char* cinema, char* time, float price, int tickets, char** seats)
{

    printf("\n\n\t**************************************\n\n");

    (tickets==1)?printf("\tDEAR CUSTOMER, YOU BOOKED %d TICKET\n\tFOR %s\n",tickets,movie):printf("\tDEAR CUSTOMER, YOU BOOKED %d TICKETS\n\tFOR %s\n",tickets,movie);

    printf("\tTHE SHOW IS BOOKED AT %s ",cinema);

    printf("AT %s\n",time);

    (tickets==1)? printf("\t%d TICKET OF %.2f IS BOOKED\n",tickets,price): printf("\t%d TICKETS OF %.2f ARE BOOKED\n",tickets,price);

    printf("\tTOTAL AMOUNT TO BE PAID IS: %.2f\n",tickets*price);

    (tickets==1)?printf("\tYOUR SEAT IS :\n"):printf("\tYOUR SEATS ARE :\n");

    for (int i=0; i<tickets; i++)
    {
        (i==tickets-1)? printf("\t%s ",seats[i]): printf("\t%s, ",seats[i]);
    }

    printf("\n\n\t***************************************\n\n\n");

}

int main()

{
    char movies[5][50]= {"Bhool Bhulaiyaa 2","Laal Singh Chaddha","Thor","Sher Bagga","Prithviraj"};
    printf("CHOOSE MOVIE\n");
    for(int i=0; i<5; i++)
    {
        printf("ENTER %d - %s\n",i,movies[i]);
    }
    int movie_choice=take_input(0,sizeof(movies)/sizeof(movies[0])-1);

    char cinemas[4][50]= {"PVR","IMAX","INOX","CARNIVAL"};
    printf("CHOOSE CINEMA\n");
    for(int i=0; i<4; i++)
    {
        printf("ENTER %d - %s\n",i,cinemas[i]);
    }
    int cinema_choice=take_input(0,sizeof(cinemas)/sizeof(cinemas[0])-1);

    char times[6][50]= {"10:00 AM","12:00 PM","02:00 PM","04:30 PM","08:00 PM","10:00 PM"};
    printf("CHOOSE TIME\n");
    for(int i=0; i<6; i++)
    {
        printf("ENTER %d - %s\n",i,times[i]);
    }
    int time_choice=take_input(0,sizeof(times)/sizeof(times[0])-1);

    float prices[3]= {220, 300, 450};
    printf("CHOOSE PRICE\n");
    for(int i=0; i<3; i++)
    {
        printf("%d - %.2f\n",i,prices[i]);
    }
    int price_choice=take_input(0,sizeof(prices)/sizeof(prices[0])-1);

    printf("HOW MANY SEATS YOU WANT TO BOOK?\n");
    int n;
    scanf("%d",&n);

    time_t t;
    srand((unsigned)time(&t));

    int **p_arr=fill_seats();

    print_seats(p_arr);

    char **selected_seats = malloc(sizeof(char*) * n);

    for(int i=0; i<n; i++)
    {
        seat_selection:

        printf("Enter seat\n");
        char row;
        int col;

        scanf(" %c%d",&row,&col);

        while(row<65 || row>75 || col<0 || col > 12)
        {
            printf("Enter valid seat number\n");
            goto seat_selection;
        }
        while(p_arr[row-65][col]==1)
        {
            printf("Seat already occupied. Try again\n");
            goto seat_selection;
        }

        p_arr[row-65][col]=2;

        char* selected_seat = malloc(sizeof(char*) * 2);
        selected_seat[0]=row;
        selected_seat[1]=col+48;
        selected_seats[i]=selected_seat;
    }

    print_seats(p_arr);

    generate_bill(movies[movie_choice],cinemas[cinema_choice],times[time_choice],prices[price_choice],n,selected_seats);
    printf("DO YOU WANT A COPY OF YOUR TICKET?\nENTER 0 - YES\n");
    int copy;
    scanf("%d",&copy);
    if (copy==0)
    {
        print_bill(movies[movie_choice],cinemas[cinema_choice],times[time_choice],prices[price_choice],n,selected_seats);
    }

    return 0;
}
