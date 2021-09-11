#include<stdio.h>
#include<math.h>


struct test_inf {
    short  root_number;
    
    double coef_a;
    double coef_b;
    double coef_c;
    
    double root1;
    double root2;
};

struct test_inf massive[10] = {
    {2,   1, 0, -1,   -1, 1},
    {2,   1, -3, 2,   1, 2},
    {1,   1, -2, 1,   1, NAN},
    {0,   12, 1, 3,   NAN, NAN},
    {2,   1, -5, 6,   2, 3}
};


void clear_buffer();
double scan_coef(char coef);
double epsilon_compare(double DBL1, double DBL2);
void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2);
void solve_quadratic(double coef_a, double coef_b, double coef_c, double *x1, double *x2);
double solve_linear(double coef_b, double coef_c, double *x1);
void run_unitest(int *unitest_start);
void unitest(struct test_inf test, int *errors, int *curTestIndex);
void print_roots(double *x1, double *x2);
void restart(int *solve_more);





//-----------------------------

int main()
{
    int unitest_start;
    int ask_user_to_solve_more;
    do
    {
        double coef_a = NAN;
        double coef_b = NAN;
        double coef_c = NAN;
        double x1 = NAN;
        double x2 = NAN;
        coef_a = scan_coef('a');
        coef_b = scan_coef('b');
        coef_c = scan_coef('c');
        printf("\nIntroduced equation: %lfX^2 %+lfX %+lf = 0 \n", coef_a, coef_b, coef_c);
        solve_equation(coef_a, coef_b, coef_c, &x1, &x2);
        print_roots(&x1, &x2);
        //
        restart(&ask_user_to_solve_more);
    }while(ask_user_to_solve_more != 0);
    
    run_unitest(&unitest_start);
    printf("\nThank you for choosing our program.\nThe end.");
    return 0; 
}



void clear_buffer()
{
    while(getchar() != '\n'){;}
}




double scan_coef (char coef)
{
    int scan_check = 0;
    double num_to_read = NAN;
    double real_coef = NAN;
    do {
        printf("Enter the coefficient %c : ", coef);
        scan_check = scanf("%lf", &num_to_read);
        if (scan_check == 0)
            printf("It's not a number.\n ");
        clear_buffer();
    } while (scan_check == 0);
    
    return num_to_read;
}




void solve_quadratic(double coef_a, double coef_b, double coef_c,double *x1,double *x2)
{
    double Discriminant = NAN;
    double discriminant_root = NAN;
    Discriminant = coef_b*coef_b - 4*coef_a*coef_c;
    if (epsilon_compare (Discriminant, 0)) 
        *x1 = -coef_b/(2*coef_a);
    else
        if (Discriminant > 0)
        {
            discriminant_root = sqrt(Discriminant);
            *x1 = (-coef_b - discriminant_root)/(2*coef_a);
            *x2 = (-coef_b + discriminant_root)/(2*coef_a);
        }    
     
}



double epsilon_compare (double DBL1, double DBL2)
{
    double epsilon = 1e-4; 
    if (fabs(DBL1 - DBL2)  < epsilon)
        return 1;
    else
        return 0;
}



double solve_linear(double coef_b, double coef_c,double *x1)
{
    if(epsilon_compare(coef_b, 0))
        printf("It's not an equation\n");
    else
        *x1 = -coef_c/coef_b;
}



void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2) 
{
    if (epsilon_compare (coef_a, 0))
        solve_linear(coef_b, coef_c, x1);
    else
        solve_quadratic(coef_a, coef_b, coef_c, x1, x2);
}


void print_roots(double *x1, double *x2)
{
    if (isnan(*x1) & isnan(*x2))
        printf("\nThe equation has no roots\n\n");
    else{
    
          if (isnan(*x2) ==1)
            printf("\nThe equation has one root: Х = %lf\n\n", *x1);
          else
            printf("\nThe equation has two roots: Х1 = %lf и Х2 = %lf\n\n", *x1, *x2);
        }
}


void restart(int *ask_user_to_solve_more)
{
    printf("\nDo you want to solve one more quadratic equation\n");
    printf("If you want it - enter 1, else enter 0: ");
    scanf("%d", ask_user_to_solve_more);
    clear_buffer();
    while ((*ask_user_to_solve_more != 1) && (*ask_user_to_solve_more != 0))
    {
        printf("\nIt's not 0 or 1\n");
        printf("if you want to solve one more equation - enter 1, else enter 0 -->");
        scanf("%d", ask_user_to_solve_more);
        clear_buffer();
    }
}


void run_unitest(int *unitest_start)
{
  int curTestIndex = 0;
  int errors = 0;

    printf("\nDo you want to start unitest? \n");
    printf("if you want it - enter 1, else enter 0: ");
    scanf("%d", unitest_start);
    clear_buffer();
    while ((*unitest_start != 0) && (*unitest_start != 1))
    {
        printf("\nIt's not 0 or 1\n");
        printf("if you want it - enter 1, else enter 0 -->");
        scanf("%d", unitest_start);
        clear_buffer();
    }
    if(*unitest_start == 1)
    {
        for (curTestIndex = 0; curTestIndex <= 10; curTestIndex++)
            unitest(massive[curTestIndex], &errors, &curTestIndex);
            printf("No errors happend\n");
    }
        
}


void unitest (struct test_inf test, int *errors, int *curTestIndex)
{
   double x1=NAN, x2=NAN;
   solve_equation(test.coef_a, test.coef_b, test.coef_c, &x1, &x2);
  // printf("x1 = %lf, x2 = %lf\n", x1, x2);
  // printf("root1 = %lf, root2 = %lf\n", test.root1, test.root2);
   if (test.root_number ==2){   
       if ((x1 != test.root1) || (x2 != test.root2))
           *errors++;
   }
   if (test.root_number == 1){
     if (x1 !=  test.root1)
       *errors++;
   }
   if (test.root_number == 0) {
     if (isnan(x1) != 1)
       *errors++;
   }
   if (*errors > 0)
   {
         printf("\nThere's an error in test №%d. \n", *curTestIndex+1);
         printf("Was entered the equation: %lfХ^2 %+lfX %+lf = 0 \n", test.coef_a, test.coef_b, test.coef_c);
         printf("Expected roots %lf и %lf\n", test.root1, test.root2);
         printf("Got roots: %lf и %lf\n", x1, x2);
   }
}