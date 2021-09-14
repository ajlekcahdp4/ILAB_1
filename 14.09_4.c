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
    {2,   1,  0,  -1,      -1, 1},
    {2,   1, -3,  2,        1, 2},
    {1,   1, -2,  1,      1, NAN},
    {0,   12, 1,  3,    NAN, NAN},
    {2,   1, -5,  6,        2, 3},
    {1,   0,  1,  -5,     5, NAN},
    {0,   0,  0,  6,    NAN, NAN},
    {2,   1,  3,  2,      -2, -1},
    {1,   0.00001, 1, -5, 5, NAN},
    {1,   1,  6,  9,     -3, NAN}
};


void clear_buffer();
void scan_coefficients (double*coef_a,double *coef_b, double *coef_c);
double scan_coef(char coef);
double epsilon_compare(double DBL1, double DBL2);
void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2, int *roots_number);
int solve_quadratic(double coef_a, double coef_b, double coef_c, double *x1, double *x2);
int solve_linear(double coef_b, double coef_c, double *x1);
void run_unit_test();
void unit_test(struct test_inf test, int *errors, int *curTestIndex);
void print_roots(double *x1, double *x2, int roots_number);
void restart(int *solve_more);

//doxygen



//-----------------------------

int main()
{
    int solve_more = 1;
    while (solve_more == 1)
        {
        //solving eqution start
        double coef_a = NAN;
        double coef_b = NAN;
        double coef_c = NAN;
        double x1 = NAN;
        double x2 = NAN;
        int roots_number = 0;
        scan_coefficients (&coef_a, &coef_b, &coef_c);
        printf("\nIntroduced equation: %.4fX^2 %+.4fX %+.4f = 0 \n", coef_a, coef_b, coef_c);
        solve_equation(coef_a, coef_b, coef_c, &x1, &x2, &roots_number);
        print_roots(&x1, &x2, roots_number);
        //solving equation finished
        restart(&solve_more);//ask user to solve more equations
        }
    
    run_unit_test();
    printf("\nThank you for choosing our program!\nThe end.");
    return 0; 
}



void clear_buffer ()
{
    while(getchar() != '\n');
}


void scan_coefficients (double *coef_a, double *coef_b, double *coef_c)
{
    *coef_a = scan_coef('a');
    *coef_b = scan_coef('b');
    *coef_c = scan_coef('c');
}


double scan_coef (char coef)
{
    int scan_check = 0;
    double num_to_read = NAN;
    double real_coef = NAN;
    while(scan_check == 0)
    {
        printf("Enter the coefficient %c : ", coef);
        scan_check = scanf("%lf", &num_to_read);
        if (scan_check == 0)
        {
            printf("It's not a number.\n");
            clear_buffer();
        }
        else
            if (scan_check == 1 && getchar() != '\n')
            {
                scan_check = 0;
                printf("It's not a number.\n");
                clear_buffer();
            }
    }
    
    return num_to_read;
}




int solve_quadratic(double coef_a, double coef_b, double coef_c,double *x1,double *x2)
{
    double Discriminant = NAN;
    double discriminant_root = NAN;
    Discriminant = coef_b*coef_b - 4*coef_a*coef_c;
    if (epsilon_compare (Discriminant, 0)){
        *x1 = -coef_b/(2*coef_a);
        return 1;
    }
    else
        if (Discriminant > 0)
        {
            discriminant_root = sqrt(Discriminant);
            *x1 = (-coef_b - discriminant_root)/(2*coef_a);
            *x2 = (-coef_b + discriminant_root)/(2*coef_a);
            return 2;
        }
        else 
            return 0;    
     
}



double epsilon_compare (double DBL1, double DBL2)
{
    double epsilon = 1e-4; 
    if (fabs(DBL1 - DBL2)  < epsilon)
        return 1;
    else
        return 0;
}



int solve_linear(double coef_b, double coef_c,double *x1)
{
    if(epsilon_compare(coef_b, 0))
        return 0;
    else{
        *x1 = -coef_c/coef_b;
        return 1;
    }
}



void solve_equation(double coef_a, double coef_b, double coef_c, double *x1, double *x2, int *roots_number) 
{
    if (epsilon_compare (coef_a, 0))
       *roots_number = solve_linear(coef_b, coef_c, x1);
    else
       *roots_number = solve_quadratic(coef_a, coef_b, coef_c, x1, x2);
}


void print_roots(double *x1, double *x2, int roots_number)
{
    switch  (roots_number)
    {
    case -1:
        printf("\nThe equation has infinite number of roots\n");
        break;
    case 0:
        printf("\nThe equation has no roots\n\n");
        break;
    case 1:
        printf("\nThe equation has one root: Х = %.4f\n\n", *x1);
        break;
    case 2:
        printf("\nThe equation has two roots: Х1 = %.4f и Х2 = %.4f\n\n", *x1, *x2);
        break;
    default:
        printf("\nERROR: unexpected number of roots\n");
    }
}


void restart(int *solve_more)
{ 
    int scan_check = 0;
    while (scan_check != 1)
    {
        printf("\nDo you want to solve one more qudratic equation?\n");
        printf("if you want to solve one more equation - enter 1, else enter 0 -->");
        scan_check = scanf("%d", solve_more);
        if (scan_check != 1)
        {
            printf("It's not 1 or 0\n");
            clear_buffer ();     
        }
        else
        {
            if (getchar () != '\n')
            {
                printf("It's not 1 or 0\n");
                clear_buffer();
                scan_check = 0;
            }
            else
                if(*solve_more != 1 && *solve_more != 0)
                {
                    printf("It's not 1 or 0---\n");
                    scan_check = 0;
                }
        }
    }
}


void run_unit_test()
{
    int unit_test_start = -1;
    int curTestIndex = 0;
    int errors = 0;
    int scan_check = 0;
    while (scan_check == 0)
    {
        printf("Do you want to start unit test?\n");
        printf("if you want it - enter 1, else enter 0 -->");
        scan_check = scanf("%d", &unit_test_start);
        if (scan_check == 0)
        {
            printf("It's not 1 or 0\n");
            clear_buffer ();
        }
        else 
        {
            if (getchar() != '\n')
            {
                printf("It's not 1 or 0\n");
                scan_check = 0;
                clear_buffer ();
            }
            else
                if (unit_test_start != 1 && unit_test_start != 0)
                {
                    printf("It's not 1 or 0\n");
                    scan_check = 0;
                }
        }
        
    }
    if(unit_test_start == 1)
    {
        for (curTestIndex = 0; curTestIndex <= 10; curTestIndex++)
            unit_test(massive[curTestIndex], &errors, &curTestIndex);
        printf("\nUnitest finished\n");
        if (errors == 0)
            printf("No errors happend\n");
    }
        
}


void unit_test (struct test_inf test, int *errors, int *curTestIndex)
{
    double x1=NAN, x2=NAN;
    int roots_number = 0;
    solve_equation(test.coef_a, test.coef_b, test.coef_c, &x1, &x2, &roots_number);
    //printf("x1 = %lf, x2 = %lf\n", x1, x2);
    //printf("root1 = %lf, root2 = %lf\n", test.root1, test.root2);
    switch (test.root_number)
    {
    case 0:
        if(isnan(x1) != 1)
            *errors++;
        break;
    case 1:
        if(epsilon_compare(x1, test.root1) == 0)
            *errors++;
        break;
    case 2:
        if(epsilon_compare(x1, test.root1) == 0 || epsilon_compare(x2, test.root2) == 0)
            *errors++;
        break;
    default:;
    }
    if (*errors > 0)
    {
         printf("\nThere's an error in test №%d. \n", *curTestIndex+1);
         printf("Was entered the equation: %lfХ^2 %+lfX %+lf = 0 \n", test.coef_a, test.coef_b, test.coef_c);
         printf("Expected roots %lf и %lf\n", test.root1, test.root2);
         printf("Got roots: %lf и %lf\n", x1, x2);
    }
}