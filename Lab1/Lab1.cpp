#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
#include "Mass.h"
#include "Energy.h"
#include "Speed.h"
#include "Impulse.h"
#include "Acceleration.h"
#include "Force.h"

std::string line ();

int main() {
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "en-US");
    setlocale(LC_CTYPE, "Russian");
    system("chcp 1251");

    Mass fr = Mass("24_kg");
    //
    // Масса
    //
    std::cout << line() << std::endl;
    std::cout << "Масса:" << std::endl;
    std::cout << line() << std::endl;
    std::cout << "22.7_kg + 2_kg - 4_kg = "<< 22.7_kg + 2_kg - 4_kg << std::endl;
    std::cout << "22.7_kg * 2 = " << 22.7_kg * 2  << std::endl;
    std::cout << "2 * 22.7_kg * 2 + 22_kg = " << 2 * 22.7_kg * 2 + 22_kg << std::endl;
    std::cout << "22.7_kg / 2 = " << 22.7_kg / 2 << std::endl;
    std::cout << "22.7_kg / 22.7_kg = " << 22.7_kg / 22.7_kg << std::endl;
    std::cout << "Преобразование по формуле (Energy)22_kg = " << (Energy)22_kg << std::endl;

    Mass m1, m2;
    std::cout << "Сравнение масс (spaceship - определен в классе)" << std::endl;
    std::cout << "Введите массу m1 = ";
    std::cin >> m1;
    std::cout << "Введите массу m2 = ";
    std::cin >> m2;
    if( m1 < m2 )
        std::cout << m1 << " < " << m2 << std::endl;
    else if( m1 == m2 )
        std::cout << m1 << " == " << m2 << std::endl;
    else if( m1 > m2 )
        std::cout << m1 << " > " << m2 << std::endl;

    std::cout << line() << std::endl << std::endl;

    //
    // Энергия
    //
    std::cout << line() << std::endl;
    std::cout << "Энергия:" << std::endl;
    std::cout << line() << std::endl;
    std::cout << "(10.5_J + 12.2_J) * 2 = "<< (10.5_J + 12.2_J) * 2 << std::endl;
    std::cout << "10 * 10.5 = "<< 10 * 10.5 << std::endl;
    std::cout << "10_J / 2 = " << 10_J / 2  << std::endl;
    std::cout << "10_J / 2_J = " << 10_J / 2_J << std::endl;
    std::cout << "10.5_J - 20_J  = " << 10.5_J - 20_J << std::endl;
    std::cout << "Преобразование по формуле E=mc2 (Mass)13_J = " << (Energy)22_kg << std::endl;

    Energy e1, e2;
    std::cout << "Сравнение энергий (spaceship - определен в классе)" << std::endl;
    std::cout << "Введите энергию e1 = ";
    std::cin >> e1;
    std::cout << "Введите энергию e2 = ";
    std::cin >> e2;

    if( e1 < e2 )
        std::cout << e1 << " < " << e2 << std::endl;
    else if( e1 == e2 )
        std::cout << e1 << " == " << e2 << std::endl;
    else if( e1 > e2 )
        std::cout << e1 << " > " << e2 << std::endl;
    std::cout << line() << std::endl << std::endl;

    //
    // Скорость
    //
    std::cout << line() << std::endl;
    std::cout << "Скорость:" << std::endl;
    std::cout << line() << std::endl;

    Speed speed1 = Speed(1,2,3);
    std::cout << speed1 << std::endl;

    std::cout << "Обращение через указатель на метод класса:" << std::endl;
    long double(Speed::*X)() const = &Speed::get_x;
    long double(Speed::*Y)() const = &Speed::get_y;
    long double(Speed::*Z)() const = &Speed::get_z;
    std::cout << "х =" << ((speed1.*X)()) << std::endl;
    std::cout << "y =" << ((speed1.*Y)()) << std::endl;
    std::cout << "Z =" << ((speed1.*Z)()) << std::endl;

    Speed speed2 = Speed(2,3,1);
    std::cout << speed1 << " + " << speed2 << " = " << speed1 + speed2 << std::endl;
    std::cout << speed1 << " * " << speed2 << " = " << speed1 * speed2 << std::endl;
    std::cout << speed1 << " * " << 10 << " + " << speed2 << " = " << speed1 * 10 + speed2 << std::endl;

    std::cout << "Вектор 10_mps = " << 10_mps << std::endl;
    Speed temp = 10_mps;
    std::cout << "Длина вектора скорости (обратное преобразование) = " << temp.vectorLength()<< std::endl;

    std::cout << "Сравнение векторов скоростей (spaceship - определен в классе)" << std::endl;
    std::cout << "Введите вектор скорости (x, y, z) s1:" << std::endl;
    std::cin >> speed1;
    std::cout << "Введите вектор скорости (x, y, z) s2:" << std::endl;
    std::cin >> speed2;

    if( speed1 < speed2 )
        std::cout << speed1 << " < " << speed2 << std::endl;
    else if( speed1 == speed2 )
       std::cout << speed1 << " == " << speed2 << std::endl;
    else if( speed1 > speed2 )
        std::cout << speed1 << " > " << speed2 << std::endl;
    std::cout << line() << std::endl << std::endl;

    //
    // Импульс
    //
    std::cout << line() << std::endl;
    std::cout << "Импульс:" << std::endl;
    std::cout << line() << std::endl;

    Impulse impulse1 = 10_kgmps + 5_kgmps;
    std::cout << "10_kgmps +  5_kgmps = " << 10_kgmps << " + " << 5_kgmps << " = " << impulse1 << std::endl;

    std::cout << "Обращение через указатель на поле класса (length): Impulse::*ip = &Impulse::length" << std::endl;
    long double Impulse::*ilp = &Impulse::length;
    std::cout << "Длина вектора импульса (обратное преобразование) = " << impulse1.*ilp<< std::endl;

    //
    // Ускорение
    //
    std::cout << line() << std::endl;
    std::cout << "Ускорение:" << std::endl;
    std::cout << line() << std::endl;

    Acceleration acceleration = 7_mpss * 2;
    std::cout << "7_mpss * 2 = " << 7_mpss << " * " << 2 << " = " << acceleration << std::endl;

    std::cout << "Обращение через указатель на поле класса (length): Acceleration::*alp = &Acceleration::length" << std::endl;
    long double Acceleration::*alp = &Acceleration::length;
    std::cout << "Длина вектора ускорения (обратное преобразование) = " << acceleration.*alp<< std::endl;

    //
    // Сила
    //
    std::cout << line() << std::endl;
    std::cout << "Сила:" << std::endl;
    std::cout << line() << std::endl;

    Force *pForce, force2, force1 = 7_N;
    std::cout << "Задан вектор силы force1 7_N = " << force1 << std::endl;
    std::cout << "Введите свой вектор силы (x, y, z) force2:" << std::endl;
    std::cin >> force2;

    if( force1 < force2 )
        std::cout << "Ваша сила больше " << force1 << " < " << force2 << std::endl;
    else if( force1 == force2 )
        std::cout << "Силы равны " << force1 << " == " << force2 << std::endl;
    else if( force1 > force2 )
        std::cout << "Ваша сила меньше " << force1 << " > " << force2 << std::endl;
    std::cout << line() << std::endl;
    std::cout << "Обращение через указатель на функцию класса (Force::vectorLength):\nlong double (Force::*pVL)() const = &Force::vectorLength" << std::endl;
    long double (Force::*pVL)() const = &Force::vectorLength;
    std::cout << "Force *pForce; pForce = &force2; и вывод (pForce->*pVL)()" << std::endl;
    pForce = &force2;
    std::cout << "Длина вашего вектора силы (обратное преобразование) = " << (pForce->*pVL)() << std::endl;
    std::cout << line() << std::endl;

    std::cout << "Проверка записи/чтения файла с помощью << >> force1, force2" << std::endl;
    std::fstream inOut;
    inOut.open("myData.txt",  std::ios::out);
    inOut << force1 << std::endl;
    inOut << force2 << std::endl;
    inOut.close();

    std::cout << "Результат:" << std::endl;
    inOut.open("myData.txt",  std::ios::in);
    std::string str;
    while(getline(inOut, str))
    {
        std::cout << Force(str) << std::endl;
    }
    inOut.close();

    return 0;
}

std::string line() { return "==============================================================="; }