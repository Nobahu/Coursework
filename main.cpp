#include "mainwindow.h"
#include <Include/main_system.h>
#include <iostream>

#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow w;
    w.show();
    return a.exec();



    // RandomGenerator::seed(42);

    // GammaStream gamma(9.0, 0.5);

    // std::vector<double> gamma_intervals;
    // for (int i = 0; i < 100000; i++) {
    //     gamma_intervals.push_back(gamma.GenerateTau());
    // }
    // double gamma_sum = 0;
    // for (double val : gamma_intervals) gamma_sum += val;
    // double gamma_mean = gamma_sum / gamma_intervals.size();

    // std::cout << "Теоретическое среднее (k*theta)\n";
    // std::cout << "Фактическое среднее: " << std::fixed << std::setprecision(4) << gamma_mean << "\n\n";



    // return 0;
}
