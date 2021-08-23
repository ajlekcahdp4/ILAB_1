#include<stdio.h>
#include<math.h>

float enter (cof)
{
int sup;
float n;
    do{
        printf("Введите коэффициент %c : ", cof);
        sup = scanf("%f", &n);
        if (sup == 0)
        {
            printf("Это не число.\n ");
        }
        scanf("%*[^\n]");
    }while (sup == 0);
    return n;
}

// главная функция
int main()
{
    float a, b, c, D, x1, x2;
    a = enter('a');
    b = enter('b');
    c = enter('c');
    printf("Введённое уравнение: %.2fХ^2 %+.2fX %+.2f = 0 \n", a, b, c);
    //ввод окончен
   if (a == 0)
    {
        x1 = -c/b;
        printf("Корень один, а уравнение вообще не квадратное. Решние: x = %.3f", x1);
    }
    else
    {
            D = b*b - 4*a*c;
        if (D > 0.0)
        {
            x1 = (-b + sqrt(D))/(2*a);
            x2 = (-b - sqrt(D))/(2*a);
            printf("Уравнение имеет два коря: x1 = %.3f, x2 = %.3f \n", x1, x2);
        }
        if (D == 0.0) 
        {
            x1 = -b/(2*a);
            printf("Уравнение имеет один корень х = %.3f \n", x1);
        }
        if  (D < 0.0)
        {
        printf("Корней нет");
        }    
        
    } 
    return 0;
}