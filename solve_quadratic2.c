#include<stdio.h>
#include<math.h>

float scan_coif (char coif);
void solve_quadratic(float coif_a, float coif_b, float coif_c);


int main()
{
    float coif_a = NAN, coif_b = NAN, coif_c = NAN, Discriminant = NAN, x1 = NAN, x2 = NAN;
    coif_a = scan_coif('a');
    coif_b = scan_coif('b');
    coif_c = scan_coif('c');
    printf("Введённое уравнение: %.1fХ^2 %+.1fX %+.1f = 0 \n", coif_a, coif_b, coif_c);
    //ввод окончен
    solve_quadratic(coif_a, coif_b, coif_c);
    return 0;
}


float scan_coif (char coif)
{
int scan_check = NAN;
float n = NAN;
    do{
        printf("Введите коэффициент %c : ", coif);
         scan_check = scanf("%f", &n);
        if (scan_check == 0)
        {
            printf("Это не число.\n ");
        }
        while (getchar() != '\n') {;}
    }while (scan_check == 0);
    return n;
}



void solve_quadratic(float coif_a, float coif_b, float coif_c)
{
double x1 = NAN, x2 = NAN, Discriminant = NAN;
if (coif_a == 0)
    {
        x1 = -coif_c/coif_b;
        printf("Корень один, а уравнение вообще не квадратное. Решние: x = %.3f", x1);
    }
    else
    {
            Discriminant = coif_b*coif_b - 4*coif_a*coif_c;
        if (Discriminant > 0.0)
        {
            x1 = (-coif_b + sqrt(Discriminant))/(2*coif_a);
            x2 = (-coif_b - sqrt(Discriminant))/(2*coif_a);
            printf("Уравнение имеет два коря: x1 = %.3f, x2 = %.3f \n", x1, x2);
        }
        if (Discriminant == 0.0) 
        {
            x1 = -coif_b/(2*coif_a);
            printf("Уравнение имеет один корень х = %.3f \n", x1);
        }
        if  (Discriminant < 0.0)
        {
        printf("Корней нет");
        }    
        
    } 
}
