#include "test_quadratic_equation.h"

std::pair<double, double> findRoots(double a, double b, double c)
{
    // throw std::logic_error("Waiting to be implemented");
    std::pair<double,double> ret (0,0);
    double x1, x2, discriminant, realPart, imaginaryPart;
    // cout << "Enter coefficients a, b and c: ";
    // cin >> a >> b >> c;
    discriminant = b*b - 4*a*c;

    if (discriminant > 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);
        cout << "Roots are real and different." << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
        ret.first = x1;
        ret.second = x2;
    }

    else if (discriminant == 0) {
        cout << "Roots are real and same." << endl;
        x1 = -b/(2*a);
        cout << "x1 = x2 =" << x1 << endl;
        ret.first = ret.second = x1;
    }

    else {
        realPart = -b/(2*a);
        imaginaryPart =sqrt(-discriminant)/(2*a);
        cout << "Roots are complex and different." << endl;
        cout << "x1 = " << realPart << "+" << imaginaryPart << "i" << endl;
        cout << "x2 = " << realPart << "-" << imaginaryPart << "i" << endl;
    }

    return ret;
}

int test_quadratic_equation()
{
    // 2x^2 + 10x + 8 = 0
    std::pair<double,double> roots = findRoots(2, 10, 8);
    std::cout << "Roots: " + std::to_string(roots.first) + ", " + std::to_string(roots.second) << endl;
    // 2x^2 + 5x -3 = 0
    roots = findRoots(2, 5, -3);
    std::cout << "Roots: " + std::to_string(roots.first) + ", " + std::to_string(roots.second) << endl;
    return 0;
}
