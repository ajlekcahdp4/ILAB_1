//=================================================================================================================
//          Program, that solve quadratic equations
//=================================================================================================================
/*!
        \author Alex Romanov
        \version 1.0
        \date 25.09.2021
*/


#include<stdio.h>
#include<math.h>

/*!
\brief Structure of test information for unit-test
*/
struct test_inf {
    short  root_number;///< number of roots

    double coef_a;///< Coefficient a
    double coef_b;///< Coefficient b
    double coef_c;///< Coefficient c

    double root1;///< First root or NAN
    double root2;///< Second root or NAN
};

struct test_inf massive[11] = {
    {2,   1,  0,  -1,      -1, 1},
    {2,   1, -3,  2,        1, 2},
    {1,   1, -2,  1,      1, NAN},
    {0,   12, 1,  3,    NAN, NAN},
    {2,   1, -5,  6,        2, 3},
    {1,   0.0,  1.0,  -5.0,     5, NAN},
    {0,   0,  0,  6,    NAN, NAN},
    {2,   1,  3,  2,      -2, -1},
    {1,   0.00001, 1, -5, 5, NAN},
    {1,   1,  6,  9,     -3, NAN}
};

/*!
Clear input buffer.
*/
void ClearBuffer ();


/*!
Run ScanCoef() 3 times and scan all coefficience of quadratic.
\param coef_a, coef_b, coef_c
Addresses of variables containing coefficients of quadratic equations
*/
void ScanCoefficients (double*coef_a,double *coef_b, double *coef_c);


/*!
Scan 1 coefficient of quadratic equation.
\param coef
Name of the read coefficient
\return Value of the read coefficient
*/
double ScanCoef (char coef);


/*!
Compare 2 double using epsilon. Return 1 if they are equale and 0 if they not.
\param DBL1, DBL2
Double numbers that need to be compared
\return 1 if the difference between the numbers are less then EPSILON and 0, if It is greater
*/
int EpsilonCompare (double DBL1, double DBL2);


/*!
Finds out if equation is linear or quadratic. Run SolveLinear() if the equation is linear and SolveQuadratic() if quadratic
\param coef_a, coef_b, coef_c
Coefficient of the quadratic equation
\param x1, x2
Addresses of variables containing value of the roots of equation
\param roots_number
Address of variable containing number of roots of equation
*/
void SolveEquation (double coef_a, double coef_b, double coef_c, double *x1, double *x2, int *roots_number);


/*!
Solve quadratic equation, using discriminant
\param coef_a, coef_b, coef_c
Coefficients of quadratic equation
\param x1, x2
Addresses of variables containing value of the roots of equation
\return number of roots of quadratic equation
*/
int SolveQuadratic (double coef_a, double coef_b, double coef_c, double *x1, double *x2);


/*!
Solve linear equation
\param coef_b, coef_c
Coefficients of linear equation
\param x1
Address of variable, containing value of the first root of equation
\return Number of roots of equation and -1 if equation has infinite number of roots
*/
int SolveLinear (double coef_b, double coef_c, double *x1);


/*!
Ask user to start unit-test of SolveEquation()
If user agreed, then start run unit-test
*/
void RunUnitTest ();


/*!
Run SolveEquation() with the test coefficients that contained in structure in the array of structure
Then checks if roots, came from SolveEquation() matches with test roots from structure.
\param test
structure of type test_inf
\param errors
Address of variable, that count number of wrong tests
\param cutTestIndex
Adress of variable, containing number of curent test
*/
void UnitTest (struct test_inf test, int *errors, int *curTestIndex);

/*!
Print roots of quadratic equation.
\param x1, x2
roots of quadratic equation
\param roots_number
number of roots
*/
void PrintRoots (double x1, double x2, int roots_number);

/*!
Ask user if he wants to solve more equation and save his decision in solve_more
\param solve_more
address of variable, containing users decision about solving more equation
*/
void Restart (int *solve_more);
/*!
Return the greatest of 2 double numbers
\param DBL1, DBL2
Double numbers
\return the greatest of numbers
*/
double Max (double a, double b);

/*!
Ask user to enter binary decision 1(YES) or 0(NO). Checks that user entered only 1 or 0 and then save this decision in var:decision
\param decision
Address of the variable in which the decision will be stored.
\return 1 if user entered decision correct and 0 if incorrect
*/
int BinaryInput (int *decision);



//-----------------------------

int main ()
{
    int solve_more = 1;
    while (solve_more == 1)
        {
        double coef_a = NAN;
        double coef_b = NAN;
        double coef_c = NAN;
        double x1 = NAN;
        double x2 = NAN;
        int roots_number = 0;
        ScanCoefficients (&coef_a, &coef_b, &coef_c);
        SolveEquation(coef_a, coef_b, coef_c, &x1, &x2, &roots_number);
        PrintRoots(x1, x2, roots_number);
        Restart(&solve_more);//!ask user to solve more equations
        }

    RunUnitTest ();
    printf("\nThank you for choosing our program!\nThe end.");
    return 0;
}



void ClearBuffer ()
{
    while(getchar() != '\n');
}


void ScanCoefficients (double *coef_a, double *coef_b, double *coef_c)
{
    double max_coef = NAN;
    *coef_a = ScanCoef('a');
    *coef_b = ScanCoef('b');
    *coef_c = ScanCoef('c');
    max_coef = Max (fabs(*coef_a), fabs(*coef_b));
    max_coef = Max (fabs(max_coef), fabs(*coef_c));
    if (max_coef <= 1e-4)
        printf("\nThe introduced equation is equivalent to: %.4fX^2 %+.4fX %+.4f = 0 \n", *coef_a/1e-5, *coef_b/1e-5, *coef_c/1e-5);
    else
        printf("\nIntroduced equation: %.4fX^2 %+.4fX %+.4f = 0 \n", *coef_a, *coef_b, *coef_c);
    *coef_a /= max_coef;
    *coef_b /= max_coef;
    *coef_c /= max_coef;
}


double ScanCoef (char coef)
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
            ClearBuffer();
        }
        else
            if (scan_check == 1 && getchar() != '\n')
            {
                scan_check = 0;
                printf("It's not a number.\n");
                ClearBuffer();
            }
    }

    return num_to_read;
}




int SolveQuadratic (double coef_a, double coef_b, double coef_c,double *x1,double *x2)
{
    double Discriminant = NAN;
    double discriminant_root = NAN;
    Discriminant = coef_b*coef_b - 4*coef_a*coef_c;
    if (EpsilonCompare (Discriminant, 0)){
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



int EpsilonCompare (double DBL1, double DBL2)
{
    double EPSILON = 1e-4;
    if (fabs(DBL1 - DBL2)  < EPSILON)
        return 1;
    else
        return 0;
}



int SolveLinear (double coef_b, double coef_c,double *x1)
{
    if(EpsilonCompare(coef_b, 0)||isnanf(coef_c))
        return -1;
    else{
        *x1 = -coef_c/coef_b;
        return 1;
    }
}



void SolveEquation (double coef_a, double coef_b, double coef_c, double *x1, double *x2, int *roots_number)
{
    if (EpsilonCompare (coef_a, 0)||isnanf(coef_a)){
        *roots_number = SolveLinear(coef_b, coef_c, x1);
    }
    else
       *roots_number = SolveQuadratic(coef_a, coef_b, coef_c, x1, x2);
}


void PrintRoots (double x1, double x2, int roots_number)
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
        printf("\nThe equation has one root: X = %.4f\n\n", x1);
        break;
    case 2:
        printf("\nThe equation has two roots: X1 = %.4f and X2 = %.4f\n\n", x1, x2);
        break;
    default:
        printf("\nERROR: unexpected number of roots\n");
    }
}


void Restart (int *solve_more)
{
    int scan_check = 0;
    while (scan_check == 0)
    {
        printf("\nDo you want to solve one more qudratic equation?\n");
        scan_check = BinaryInput (solve_more);
    }
}


void RunUnitTest ()
{
    int unit_test_start = 0;
    int cur_test_index = 0;
    int errors = 0;
    int scan_check = 0;
    while (scan_check == 0)
    {
        printf("\nDo you want to start unit test?\n");
        scan_check = BinaryInput (&unit_test_start);

    }
    if (unit_test_start == 1)
    {
        for (cur_test_index = 0; cur_test_index <= 10; cur_test_index++)
            UnitTest(massive[cur_test_index], &errors, &cur_test_index);
        printf("\nUnitest finished\n");
        if (errors == 0)
            printf("No errors happend\n");
    }

}


void UnitTest (struct test_inf test, int *errors, int *curTestIndex)
{
    double x1=NAN, x2=NAN;
    int roots_number = 0;
    SolveEquation(test.coef_a, test.coef_b, test.coef_c, &x1, &x2, &roots_number);
    //printf("x1 = %lf, x2 = %lf\n", x1, x2);
    //printf("root1 = %lf, root2 = %lf\n", test.root1, test.root2);
    switch (test.root_number)
    {
    case 0:
        if (isnanf(x1) != 1)
            *errors++;
        break;
    case 1:
        if (EpsilonCompare(x1, test.root1) == 0)
            *errors++;
        break;
    case 2:
        if (EpsilonCompare(x1, test.root1) == 0 || EpsilonCompare(x2, test.root2) == 0)
            *errors++;
        break;
    default:;
    }
    if (*errors > 0)
    {
         printf ("\nThere's an error in test %d. \n", *curTestIndex+1);
         printf ("Was entered the equation: %lfX^2 %+lfX %+lf = 0 \n", test.coef_a, test.coef_b, test.coef_c);
         printf ("Expected roots %lf and %lf\n", test.root1, test.root2);
         printf ("Got roots: %lf and %lf\n", x1, x2);
    }
}

double Max (double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}

int BinaryInput (int *decision)
{
    int scan_check = 0;
    printf("if you want it - enter 1, else enter 0 -->");
    scan_check = scanf ("%d", decision);
    if (scan_check == 0)
    {
        printf ("It's not 1 or 0\n");
        ClearBuffer ();
        return 0;
    }
    else
    {
        if (getchar () != '\n')
        {
            printf ("It's not 1 or 0\n");
            ClearBuffer ();
            return 0;
        }
        else
            if (*decision != 1 && *decision != 0)
            {
                printf ("It's not 1 or 0\n");
                return 0;
            }
            else
                return 1;
    }
}
