#include<stdio.h>
#include<time.h>
#include<string.h>
#include<locale.h>
char* gettime() {
    time_t CurTime;

    time(&CurTime);

    static char TimeStr[100];

    setlocale(LC_TIME, "en_US.UTF-8");

    strftime(TimeStr, sizeof(TimeStr), "%Y-%m-%d %H:%M:%S", localtime(&CurTime));
    return TimeStr;
}
float getGrandTotal(float Amount) {
    float GrandTotal = 0;
   
    float CGSTRate = 0.09;
    float SGSTRate = 0.09;

    
    float CGSTAmount = Amount * CGSTRate;
    float SGSTAmount = Amount * SGSTRate;

    
    GrandTotal = Amount + CGSTAmount + SGSTAmount;

    return GrandTotal;
}
// int countWordInFile(char *CASHWord) {
//     FILE *file = fopen("3_bill.txt", "a");
//     fprintf(file,"CASH\n");
//     char ch;
    

//     fseek(file, 0, SEEK_SET); 
//     char temp[1000];
//     int count = 0;

//     while (!feof(file))
//     {
//         ch = fgetc(file);
//         if (ch == '\n')
//         {
//             count ++;
//         }
//     }

//     fclose(file);

//     return count;
// }

int main() {

    FILE *fp1;
    FILE *fp2;
   

    char cust_name[50];
    int no_items;
    char Item[50];
    int Quantity;
    float Price;
    float Amount=0;
    float final_Amount=0;
    int Table_No;
    int No_Guests;
    float GrandTotal;
    int server_no;
    
    fp1 = fopen("1_bill.txt", "w");
    fp2 = fopen("2_bill.txt","a");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    char CASHWord[4] = "CASH";

    printf("Enter the customer name: ");
    gets(cust_name);

    printf("Table NO: ");
    scanf("%d",&Table_No);

    printf("No of Guests:");
    scanf("%d",&No_Guests);

    printf("Server no:");
    scanf("%d",&server_no);

    printf("Enter no of items: ");
    scanf("%d", &no_items);

    fprintf(fp1,"------------------------CASH RECEIPT------------------------\n");
    fprintf(fp2,"------------------------CASH RECEIPT------------------------\n");
    
    // int Bill_No=countWordInFile(CASHWord) + 1;
    // fprintf(fp2,"Bill.No-%d\n",Bill_No);

    fprintf(fp1,"%-27s%s%-27s\n\n"," ","******"," ");

    fprintf(fp1, "=========================Hotel IITL=========================\n");

    fprintf(fp1,"%-25s%s%-25s\n"," ","21,CG-City"," ");

    fprintf(fp1,"%-23s%s%-23s\n"," ","Lucknow-41306"," ");

    char *Time = gettime();

    fprintf(fp1,"%-20s%s%-20s\n"," ",Time," ");
    fprintf(fp2,"%-20s%s%-20s\n"," ",Time," ");
   
   
    fprintf(fp1,"%-20sTable No:%d %d-Guest%-20s\n"," ",Table_No,No_Guests," ");
    fprintf(fp2,"%-20sTable No:%d %d-Guest%-20s\n"," ",Table_No,No_Guests," ");

    fprintf(fp1,"%-24sServer No:%d%-24s\n"," ",server_no," ");
    fprintf(fp2,"%-24sServer No:%d%-24s\n"," ",server_no," ");

    fprintf(fp1, "Customer Name= %s\n", cust_name);
    fprintf(fp2, "Customer Name= %s\n", cust_name);

    fprintf(fp1, "============================================================");
    fprintf(fp2, "============================================================");

    fprintf(fp1,"\n%-30s%-10s%-10s%-10s\n", "Item","Quantity","Price","Total");
    fprintf(fp2,"\n%-30s%-10s%-10s%-10s\n", "Item","Quantity","Price","Total");

    fprintf(fp1,"------------------------------------------------------------\n");
    fprintf(fp2,"------------------------------------------------------------\n");

    for (int i = 1; i <= no_items; i++) {

        printf("Enter name of item %d: ", i);
        scanf("%s", &Item);

        printf("Enter no of %s: ", Item);
        scanf("%d", &Quantity);

        fprintf(fp1, "%-30s", Item);
        fprintf(fp2, "%-30s", Item);

        fprintf(fp1,"%-10d", Quantity);
        fprintf(fp2,"%-10d", Quantity);

        printf("Enter cost of 1 %s: ", Item);
        scanf("%f", &Price);

        Amount = Price*Quantity;
        final_Amount += Amount;

        fprintf(fp1,"₹%-10.2f",Price);
        fprintf(fp2,"₹%-10.2f",Price);

        fprintf(fp1,"₹%-10.2f\n",Amount); 
        fprintf(fp2,"₹%-10.2f\n",Amount); 
    }

    fprintf(fp1,"------------------------------------------------------------\n");
    fprintf(fp2,"------------------------------------------------------------\n");

    fprintf(fp1,"%-51s₹%-10.2f\n"," ",final_Amount);
    fprintf(fp2,"%-51s₹%-10.2f\n"," ",final_Amount);

    fprintf(fp1,"%-40s%s\n"," ","--------------------");
    fprintf(fp2,"%-40s%s\n"," ","--------------------");

    fprintf(fp1,"%-41s%-10s₹%-10.2f\n"," ","SGST@9%",0.09*final_Amount);
    fprintf(fp2,"%-41s%-10s₹%-10.2f\n"," ","SGST@9%",0.09*final_Amount);

    fprintf(fp1,"%-41s%-10s₹%-10.2f\n"," ","CGST@9%",0.09*final_Amount);
    fprintf(fp2,"%-41s%-10s₹%-10.2f\n"," ","CGST@9%",0.09*final_Amount);

    fprintf(fp1,"%-40s%s\n"," ","--------------------");
    fprintf(fp2,"%-40s%s\n"," ","--------------------");

    GrandTotal=getGrandTotal(final_Amount);

    fprintf(fp1,"%-35s%-16s₹%-10.2f\n"," ","Grand Total",GrandTotal);
    fprintf(fp2,"%-35s%-16s₹%-10.2f\n"," ","Grand Total",GrandTotal);

    fprintf(fp1,"------------------------------------------------------------\n");
    fprintf(fp2,"------------------------------------------------------------\n");

    printf("Type 0 for 0%% Tip\nType 1 for 10%% Tip\nType 2 for 20%% Tip\nType 3 for 30%% Tip\n");

    int Tip_in;
    
    scanf("%d",&Tip_in);

    float Tip=0.1*Tip_in*GrandTotal;

    if (Tip_in<4 && Tip_in>=0)
    {
       
    printf("payable tip is: %0.2f\n",Tip);
    }
    else
    {

        printf("Enter valid no for tip\n");
    }

    fprintf(fp2,"%s%d %s ₹%0.2f\n","Server no:",server_no,"got",Tip);

    fprintf(fp1,"%-20s%s%-21s\n"," ","Tip is not included"," ");

    fprintf(fp1,"%-23s%s%-24s\n"," ","#THANK YOU#"," ");

    fprintf(fp1,"============================================================");
    fprintf(fp2,"============================================================\n\n\n");

    fclose(fp1);
    fclose(fp2);
    
    return 0;
}