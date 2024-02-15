#include<stdio.h>

#include<string.h>


float getGrandTotal(float Amount) {
    float GrandTotal = 0;
   
    float CGSTRate = 0.09;
    float SGSTRate = 0.09;

    
    float CGSTAmount = Amount * CGSTRate;
    float SGSTAmount = Amount * SGSTRate;

    
    GrandTotal = Amount + CGSTAmount + SGSTAmount;

    return GrandTotal;
}

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

    fp1 = fopen("1_1bill.txt", "w");
    fp2 = fopen("2_2bill.txt","a");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter the customer name: ");
    gets(cust_name);

    printf("Enter no of items: ");
    scanf("%d", &no_items);

    fprintf(fp1,"------------------------CASH RECEIPT------------------------\n");

    fprintf(fp1,"%-27s%s%-27s\n\n"," ","******"," ");

    fprintf(fp1, "========================SUPER MARKET========================\n");

    fprintf(fp1,"%-25s%s%-25s\n"," ","21,CG-City"," ");

    fprintf(fp1,"%-23s%s%-23s\n"," ","Lucknow-41306"," ");

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

    fprintf(fp1,"%-23s%s%-24s\n"," ","#THANK YOU#"," ");

    fprintf(fp1,"%-24s%s%-25s\n"," ","VISIT AGAIN"," ");

    fprintf(fp1,"============================================================");
    fprintf(fp2,"============================================================\n\n\n");

    fclose(fp1);
    fclose(fp2);

    return 0;
}