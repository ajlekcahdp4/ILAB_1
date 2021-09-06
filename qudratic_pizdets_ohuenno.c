#include<stdio.h>
#include<math.h>


struct test_inf {
    short root_number;
    double coef_a;
    double coef_b;
    double coef_c;
    double root1;
    double root2;
};

struct test_inf massive[10] = 
{
{
  2,
  1,
  0,
  -1,
  -1,
  1,
},
{
  2,
  1,
  -3,
  2,
  1,
  2,
},
{
  1,
  1,
  -2,
  1,
  1,
  NAN,
},
{
  0,
  12,
  1,
  3,
  NAN,
  NAN,
},
{
  2,
  1,
  -5,
  6,
  2,
  3,
}
};



double scan_coif (char coif);
double epsilon_check(double coef, double number);
void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2);
void solve_quadratic(double coef_a, double coef_b, double coef_c, double *x1, double *x2);
double solve_linear(double coef_b, double coef_c, double *x1);
void run_unitest(int *unitest_start);
void unitest (struct test_inf test, int *errors, int *index);
void print_function(double *x1, double *x2);
void restart(int *solve_more);







int main()
{
    int unitest_start = 2;
    int solve_more = 2;
do
{
    double coef_a = NAN;
    double coef_b = NAN;
    double coef_c = NAN;
    double x1 = NAN;
    double x2 = NAN;
    coef_a = scan_coif('a');
    coef_b = scan_coif('b');
    coef_c = scan_coif('c');
    printf("\nIntroduced equation: %lfХ^2 %+lfX %+lf = 0 \n", coef_a, coef_b, coef_c);
    //ввод окончен
    solve_equation(coef_a, coef_b, coef_c, &x1, &x2);
    print_function(&x1, &x2);
    restart(&solve_more);
}while(solve_more != 0);

    run_unitest(&unitest_start);
    
    printf("\nThank you for choosing our program.\nThe end.");
return 0; 
}





double scan_coif (char coif)
{
    int scan_check = 0;
    double n = NAN;
    double real_coef = NAN;
    do {
        printf("Enter the coefficient %c : ", coif);
        scan_check = scanf("%lf", &n);
        if (scan_check == 0)
        {
            printf("It's not a number.\n ");
        }
        while (getchar() != '\n') {;}
    } while (scan_check == 0);
    
    
    real_coef = epsilon_check(n, 0);
    
    return real_coef;
}




void solve_quadratic(double coef_a, double coef_b, double coef_c,double *x1,double *x2)
{
    double Discriminant = NAN;
    double discriminant_root = NAN;
    Discriminant = coef_b*coef_b - 4*coef_a*coef_c;
    Discriminant = epsilon_check(Discriminant, 0);
        if (Discriminant > 0.0)
        {
            discriminant_root = sqrt(Discriminant);
            discriminant_root = epsilon_check(discriminant_root, 0);
            *x1 = (-coef_b - discriminant_root)/(2*coef_a);
            *x2 = (-coef_b + discriminant_root)/(2*coef_a);
        }
        if (Discriminant == 0.0) 
        {
            *x1 = -coef_b/(2*coef_a);
        }    
        
     
}



double epsilon_check(double coef, double number)
{
    double epsilon = 1e-6;
    double real_coef = NAN;
    
    if (fabs(coef - number)  > epsilon)
        real_coef = coef;
    else
        real_coef = 0;
        
    return real_coef;
}



double solve_linear(double coef_b, double coef_c,double *x1)
{
    if(coef_b == 0)
        printf("It's not an equation\n");
    else
        *x1 = -coef_c/coef_b;
}



void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2) 
{
    if (coef_a == 0)
            solve_linear(coef_b, coef_c, x1);
    else
      solve_quadratic(coef_a, coef_b, coef_c, x1, x2);
}


void print_function(double *x1, double *x2)
{
    if ((isnan(*x1)==1)& (isnan(*x2)==1))
      printf("\nThe equation has no roots\n\n");
    else{
    
          if (isnan(*x2) ==1)
            printf("\nThe equation has one root: Х = %lf\n\n", *x1);
          else
            printf("\nThe equation has two roots: Х1 = %lf и Х2 = %lf\n\n", *x1, *x2);
        }
}


void restart(int *solve_more)
{
    printf("\nDo you want to solve one more quadratic equation\n");
    printf("If you want it - enter 1, else enter 0: ");
    scanf("%d", solve_more);
    while(getchar() != '\n'){;}
    while ((*solve_more != 1)&&(*solve_more != 0))
    {
        printf("\nIt's not 0 or 1\n");
        printf("if you want to solve one more equation - enter 1, else enter 0 -->");
        scanf("%d", solve_more);
        while(getchar() != '\n'){;}
    }
}


void run_unitest(int *unitest_start)
{
  int index = 0;
  int errors = 0;

    printf("\nDo you want to start unitest? \n");
    printf("if you want it - enter 1, else enter 0: ");
    scanf("%d", unitest_start);
    while(getchar() != '\n'){;}
    while ((*unitest_start != 0) && (*unitest_start != 1))
    {
        printf("\nIt's not 0 or 1\n");
        printf("if you want it - enter 1, else enter 0 -->");
        scanf("%d", unitest_start);
        while(getchar() != '\n'){;}
    }
    if(*unitest_start == 1)
    {
        for (index = 0; index <= 10; index++)
            unitest(massive[index], &errors, &index);
            printf("No errors happend\n");
    }
        
}


void unitest (struct test_inf test, int *errors, int *index)
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
         printf("\nThere's an error in test №%d. \n", *index+1);
         printf("Was entered the equation: %lfХ^2 %+lfX %+lf = 0 \n", test.coef_a, test.coef_b, test.coef_c);
         printf("Expected roots %lf и %lf\n", test.root1, test.root2);
         printf("Got roots: %lf и %lf\n", x1, x2);
   }
}