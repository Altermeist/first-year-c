/* 
 * File:   Lab4.c
 * Author: Nicholas Park
 *
 * Created on October 17, 2015, 9:25 PM
 */




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>

/*
 * 
 */

double gaussFunc(double x, double spread) {
    double height;
    //bool done;

    height = exp(-(x * x) / spread);

    return height;
}

int main(void) {
    //bool done = false;
    double spread, a, b, width, sum;
    int n;
    


    do {
        printf("Enter the spread value (must be >0): ");
        scanf("%lf", &spread);
    }    while (spread <= 0);


    //loop {
    //while (n>=1) {

    do {
    printf("Please the number of rectangles (n): ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Exiting.");
        return 0;
        //bool done = true;
    } 
    else {
        printf("Enter the interval of integration (a b): ");
        scanf("%lf %lf", &a, &b);

        if (a > b) {
            do {
            printf("Invalid interval!\n");
            printf("Enter the interval of integration (a b): ");
            scanf("%lf %lf", &a, &b);
            }
    while (a > b);
        }
        double x;
        sum = 0;
        width = ((b - a) / n);
        x = a + (width / 2);
        //for (int i = 0; i <= n; i++) {
        //sum = 0;
        for (x = a + (width / 2); x <= b; x += width) {

            sum = sum + gaussFunc(x, spread) * width;
    
        }

        printf("Integral of Gaussian with spread %.3lf on [%.3lf, %.3lf] with n = %d is: %.3lf \n\n", spread, a, b, n, sum);
    }
    }
    while (n >= 1);

    //}
    return 0;
}

        // user enters Spread, double.
        // if Spread <= 0, ask User for new Spread
        // 2. User enters 'n', num of rectangles (int) If n<1, exit & print Exiting
        // User enters limits of integration (a,b) double. If lower limit of 'a' > upper limit of 'b'
        // tell User that interval is invalid and ask again
        // print approx for f(x) = e^-x/spread to 3 decimals 
        // repeat from step 2 & ask for 'n' again
        //    }
        //}
/*double int_midrect(double a, double b, double n, double gaussFunc()) {
    double p, x, y, spread, area;
    int n, a, b;
    //y = exp(pow(-x , 2 / spread));
    
    x = ((b - a)/n);
    y = (a + (x/2));
    for(p = a; x <= (b - x)); p = p + x) {
        sum = sum + 
    } 
            
    for(int iterate; n >= 1; iterate++) {
        for()
    }
    area = 
            
            return area;
}


 */