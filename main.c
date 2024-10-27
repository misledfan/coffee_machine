//CSCI-291 Coffee Machine
//Pre-processor directives 
    #include <stdio.h>
    #include <stdlib.h>

// Defining the constants for all coffe types 
    #define beans_req 8	            /* Defines coffee type      */
    #define water_req 30  	        /* Defines Water quantity   */ 
    #define syrup_req 30 	        /* Defines choco syrup amt  */
    #define milk_cap_req 70		    /*milk needed for cappucino */
    #define milk_moc_req 160

//Define constants for ingredients
    #define milk 200        
    #define water 200
    #define beans 200
    #define syrup 150

// Defining cost for respective coffe types 
    #define price_esp 3.5 
    #define price_cap 4.5
    #define price_moc 5.5

// Threshhold defines min value below which a "Not enough ingredients" pop up is sent 
    #define thr_beans 7     /* threshhold for beans   */
    #define thr_water 29    /* threshold for water   */
    #define thr_milk 69     /* threshold for milk   */
    #define thr_syrup 29  /* threshold for syrup */

// How much of everything in a variable
    int tot_beans = beans;
    int tot_water = water;
    int tot_milk = milk;
    int tot_syrup = 100;

// Initial price for individual coffee
    float prc_esp=price_esp;
    float prc_moc=price_moc;
    float prc_cap=price_cap;

// Total Sales intitial
    int tot_cap=0;
    int tot_esp=0;
    int tot_moc=0;

//Total Profit
    int tot_money=0;

//Function prototypes
void finance (int);         
void coffee_mn();           
void admin_settings();
void updateIngredientStocks(int *tot_beans, int *tot_water, int *tot_syrup, int *tot_milk);


int main() 

{	
    int run=1;
	while (run==1)
	{
		int option,coffee_type; //define option and coffe type for user input
		printf("\n\n\n--Coffee Machine--\n");
		printf("Enter an option \n 1) \t Make Coffee \n 2) \t Administrator Access \n 3) \t Exit program \n");      //can go to user side, admin side and exit
		
		scanf("%d",&option);
		
		switch (option)         //switch based on user input 
		{
	    case 1:
	        coffee_mn();
	        break;
	       
	    case 2:
	        printf("--Admin--\n");
            admin_settings();   
	        break;
	    case 3:
	        printf("Exiting....");
	        run=0;
	        break;
	    }
	}
return 0;	
}


void finance (int coffee_selection) // handles all Finance related issues, including payment, verification and change disperal
{
    float money_inserted = 0.0;     // total money inserted by user
    int coin;           // the 1 or 0.5 coin inserted in each iteration
    float mn_needed;    // price of coffee that needs to be matched for transaction to go through 

    if (coffee_selection == 1)
        {
            printf("\nYou've selected Espresso. The price is 3.5 AED. Please insert 1 AED or 50 fils coins to proceed.\n");
            mn_needed = price_esp; // Sets money needed to price of espresso
        }
        else if (coffee_selection == 2)
        {
            printf("\nYou've selected Cappuccino. The price is 4.5 AED. Please insert 1 AED or 50 fils coins to proceed.\n");
            mn_needed = price_cap; // Sets money needed to price of cappochino
        }
        
        else if (coffee_selection == 3)
        {
            printf("\nYou've selected Mocha. The price is 5.0 AED. Please insert 1 AED or 50 fils coins to proceed.\n");
            mn_needed = price_moc; // Sets money needed to price of mocha
        }
        else
        {
            printf("\nInvalid option, How did you do that?\n"); // Else loop incase User selects the wrong option 
            return;
        }

    
    while (money_inserted < mn_needed)
        {   
            printf("Insert a coin (1 for 1 AED, 2 for 0.5 AED): "); // user enters 1 for aed coin, 2 for 50 fills coin
            scanf("%d", &coin);
            
            
            if (coin == 1)
            {
                money_inserted += 1.0;  
            }
            else if (coin == 2)
            {
                money_inserted += 0.5;
            }
            else
            {
                printf("Invalid coin. Please insert either 1 AED or 0.5 AED.\n");
                continue;  // This ensures the loop keeps going without breaking
            }       

            printf("Total inserted: %.2f AED\n", money_inserted);   // total coins inserted

            if (money_inserted >= mn_needed)    // if amount inserted >= money needed, give coffee
            {
                printf("\nYou have  inserted %f AED. Your coffee is ready!\n", money_inserted);
                break;
            }
        }

    // total profit calculation based on coffe type ordered
    if (coffee_selection == 1) 
        {
            tot_money += price_esp;
        } 
        else if (coffee_selection == 2) 
        {
            tot_money += price_cap;
        }
        else if (coffee_selection == 3) 
        {
            tot_money += price_moc;
        }
}

//main coffee machine code
void coffee_mn() 
{
    int coffee_selection;

    printf("\t--Coffee Menu--\n\n");

    int avail = 0; // variable avail turns 1 if any coffee available 
    for (int i = 1; i <= 3; i++) 
    { 
        // for loop iterates through coffee options
            switch (i) {
                case 1:
                    if (tot_water <= thr_water || tot_beans <= thr_beans) { // if ingredients less than threshold, out of stock
                        printf("1) Espresso\t OUT OF STOCK!!!\n");
                    } else {
                        printf("1) Espresso\t %.2f AED\n", prc_esp); // espresso and its price
                        avail = 1;
                    }
                    break;

                case 2:
                    if (tot_milk <= thr_milk || tot_water <= thr_water || tot_beans <= thr_beans) { // if ingredients less than threshold, out of stock
                        printf("2) Cappuccino\t OUT OF STOCK!!!\n");
                    } else {
                        printf("2) Cappuccino\t %.2f AED\n", prc_cap); // cappuccino and its price
                        avail = 1;
                    }
                    break;

                case 3:
                    if (tot_milk <= thr_milk || tot_water <= thr_water || tot_beans <= thr_beans || tot_syrup <= thr_syrup) { // if ingredients less than threshold, out of stock
                        printf("3) Mocha\t OUT OF STOCK!!!\n");
                    } else {
                        printf("3) Mocha\t %.2f AED\n", prc_moc);   // mocha and its price
                        avail = 1;
                    }
                    break;
            }
        }

    if (avail == 0) // if no coffe type available, this code runs
    {
        printf("Sorry, no coffee available. Please refill ingredients.\n");
        return;
    }

    printf("\nChoose Your coffee\n"); // user choses coffee selection
    scanf("%d", &coffee_selection);

    if (coffee_selection < 1 || coffee_selection > 3) // ensures a correct option is chosen
     {
    printf("Invalid coffee selection. Please choose 1, 2, or 3.\n");
    return;
    }

    if // checks for suffecient ingredients, in case user selects out of stock coffee

    ((coffee_selection == 1 && (tot_water < water_req || tot_beans < beans_req)) ||
    (coffee_selection == 2 && (tot_water < water_req || tot_beans < beans_req || tot_milk < milk_cap_req)) ||
    (coffee_selection == 3 && (tot_water < water_req || tot_beans < beans_req || tot_milk < milk_moc_req || tot_syrup < syrup_req)))        //entire thing is the if requirement
        {
        printf("Sorry, insufficient ingredients for your selected coffee. Please refill ingredients.\n");           //if true run this 
        return;
        }


    printf("\nDid You chose Option: %d",coffee_selection);  // confirm selection
    printf("\nSelect 1 to go proceed, any other number to go back: \n");
    int op=0;

    scanf("%d",&op);
    if (op==1)
    {
         finance(coffee_selection); // finance function runs
         switch (coffee_selection)  
         
    {
        case 1: // Espresso
            printf("Here1 your coffee\n");
            // Deduct ingredients for Espresso
            tot_water -= water_req; 
            tot_beans -= beans_req;

            tot_esp++; // total espresso sold updated
            break;

        case 2: // Cappuccino
            printf("Here your coffee\n");
            // Deduct ingredients for Cappuccino
            tot_milk -= milk_cap_req;  
            tot_water -= water_req;     
            tot_beans -= beans_req;     

            tot_cap++; //total cappachino sold updated
            break;

        case 3: // Mocha
            printf("Here your coffee\n");
            // Deduct ingredients for Mocha
            tot_beans -= beans_req;     
            tot_water -= water_req;
            tot_milk -= milk_moc_req;  
            tot_syrup -= syrup_req;     

            tot_moc++; // total mocha sold updated
            break;

        default:
            printf("Invalid selection.\n"); // if user selects invalid option
            break;
    }
    }   

    // Check if ingredients are running low (after coffee is made)
    for (int i = 1; i <= 3; i++) 
    {
        switch (i) {
            case 1:
                if (tot_water <= thr_water || tot_beans <= thr_beans) {
                    printf("Ingredients low for Espresso\n");
                }
                break;

            case 2:
                if (tot_milk <= thr_milk || tot_water <= thr_water || tot_beans <= thr_beans) {
                    printf("Ingredients low for Cappuccino\n");
                }
                break;

            case 3:
                if (tot_milk <= thr_milk || tot_water <= thr_water || tot_beans <= thr_beans || tot_syrup <= thr_syrup) {
                    printf("Ingredients low for Mocha\n");
                }
                break;
        }
    }
}


void admin_settings()       // Admin settings function
{
    int admin_run=1;
    int user_pin;    // variable for pin entered by user
    int correct_pin = 1234; // variable for pin for admin access

    // Admin Pin ask:
    printf("Enter Admin PIN in Keypad to proceed ");
    scanf("%d", &user_pin); // Only Numbers can be inserted

    // Check if pin correct
    if (user_pin != correct_pin)
    {
        printf("Incorrect PIN.\n");
        return; // Return to main screen if wrong pin
    }

    printf("PIN confirmed. Access granted.\n");


    while( admin_run==1)
    {

        printf("Admin Settings\n");
        printf("Select a relevant Option\n\t");
        printf(" 1) Show ingredient quantities & sale amount.\n\t 2)  Refill machine ingredients.\n\t 3) Update coffee price.\n\t 4) Reset Total Sales \n\t 0) Exit Admin Mode.\n\n"); 
        int option;
        scanf("%d", &option);   // Ask user 


        switch (option)
        {
        case 1:
            printf("Ingredient Quantities\n\n");
            printf(" Coffee Beans: %dg\n Water: %dml\n Choco Syrup: %dml\n Milk: %dml\n", tot_beans, tot_water, tot_syrup, tot_milk); // show Ingredients left in machine
            printf("Total sales:\n Espresso: %d\n Capachino: %d\n Mocha: %d\n", tot_esp,tot_cap,tot_moc); // Show total Sales for individual coffee
             printf("Total profit: %.2f AED\n", tot_money); // Show total profit for all coffee
            break;
            
        case 2:
            printf("Updating Ingredient stocks....\n");
            updateIngredientStocks(&tot_beans, &tot_water, &tot_syrup, &tot_milk);

break;

        case 3:     // new prices for all
            printf("Updating coffee prices\n");
            printf("Enter new price for Espresso: ");
            scanf("%f", &prc_esp);  // new espresso price
            printf("Enter new price for Cappuccino: ");
            scanf("%f", &prc_cap);  // new cappuccino price
            printf("Enter new price for Mocha: ");  
            scanf("%f", &prc_moc);  // new mocha price
            break;
                
        case 4:
                tot_money = 0;
                tot_esp = 0;
                tot_cap = 0;
                tot_moc = 0;
                printf("Total sales reset successfully.\n");
        case 0:
            admin_run=0;    
        }
    }
}


void updateIngredientStocks(int *tot_beans, int *tot_water, int *tot_syrup, int *tot_milk)
 {
    printf("Updating Ingredient stocks....\n");
    
    for (int i = 0; i < 4; i++) 
    {   
        int Q = (rand() % 50) + 300;  // Random quantity for refill, remainder always less than 50, 50 + 300
        
        switch (i) 
        {
            case 0:
                *tot_beans = Q;  // Update total beans
                break;
            case 1:
                *tot_water = Q;  // Update total water
                break;
            case 2:
                *tot_syrup = Q;  // Update total syrup
                break;
            case 3:
                *tot_milk = Q;   // Update total milk
                break;
        }
    }
    
    printf("Total Beans: %d\n", *tot_beans);
    printf("Total Water: %d\n", *tot_water);
    printf("Total Syrup: %d\n", *tot_syrup);
    printf("Total Milk: %d\n", *tot_milk);
}



