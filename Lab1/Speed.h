#ifndef UNTITLED_SPEED_H
#define UNTITLED_SPEED_H

#include <iostream>
#include <stdexcept>
#include <cmath>

class Speed {
    long double x_value;
    long double y_value;
    long double z_value;
public:
    Speed(long double _x = 0., long double _y = 0., long double _z = 0.)
            : x_value(_x), y_value(_y), z_value(_z) {}
    Speed(std::string str);
    ~Speed() = default;
    long double get_x() const { return x_value; }
    long double get_y() const { return y_value; }
    long double get_z() const { return z_value; }

    Speed(const Speed& rhs) : x_value(rhs.x_value), y_value(rhs.y_value), z_value(rhs.z_value)  {}
    Speed& operator=(const Speed& rhs)
    {
        if(this == &rhs) return *this; //самоприсваивание
        x_value = rhs.x_value;
        y_value = rhs.y_value;
        z_value = rhs.z_value;
        return *this;
    }
    Speed operator+() const { return *this; }
    Speed operator-() const { return Speed(-x_value, -y_value, -z_value); }
    Speed& operator+=(const Speed& rhs) { x_value += rhs.x_value;  y_value += rhs.y_value; z_value += rhs.z_value; return *this;}
    Speed& operator-=(const Speed& rhs) { return (*this) += (-rhs); }
    Speed& operator+(const Speed& rhs) { return (*this) += rhs; }
    Speed& operator-(const Speed& rhs) { return (*this) -= rhs; }
    //скалярное произведение
    long double operator*(const Speed& rhs) { return x_value*rhs.x_value + y_value*rhs.y_value + z_value*rhs.z_value; }
    //умножение на скаляр
    Speed& operator*=(long double rhs) {x_value *= rhs;  y_value *= rhs; z_value *= rhs; return *this;}
    Speed& operator*(long double rhs) { return (*this) *= rhs;}

    friend std::ostream& operator << (std::ostream&, const Speed&);
    friend std::istream& operator>> (std::istream &in, Speed&);
    friend Speed operator"" _mps(long double);
    friend Speed operator"" _mps(unsigned long long);

    long double vectorLength() const {return sqrt(pow(x_value,2)+pow(y_value,2)+pow(z_value,2));}
    auto operator<=>(const Speed& rhs) const {
        return this->vectorLength() <=> rhs.vectorLength();
    }
    bool operator==(const Speed& rhs) const {
        return this->vectorLength() == rhs.vectorLength();
    }
};

Speed::Speed(std::string str)
{
    const char *cstr = str.data();  //https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
    x_value=0.; y_value=0.; z_value=0.;
    sscanf(cstr, "%*[^(](%Lf, %Lf, %Lf)", &x_value, &y_value, &z_value);
}

std::ostream& operator << (std::ostream& out, const Speed& obj)
{
    return out << "Speed(" << obj.get_x() << ", " << obj.get_y() << ", " << obj.get_z() <<")";
}

std::istream& operator>> (std::istream &in, Speed& speed)
{
    long double _coordinates[3];
    char _coordinatesName[3] = {'x', 'y', 'z'};
    char str[32];
    bool isError;

    for (int i = 0; i < 3; ++i) {
        do {
            std::cout << _coordinatesName[i] << "= ";
            isError = false;
            try {
                in.getline(str, sizeof(str));
                _coordinates[i] = std::stold(str);
            }
            catch (std::exception &e) {
                in.clear();
                std::cout << "Ошибка ввода!" << std::endl;
                std::cout << "Введите корректное значение: ";
                isError = true;
            }
        } while (isError);
    }

    speed.x_value = _coordinates[0]; speed.y_value = _coordinates[1]; speed.z_value = _coordinates[2];
    return in;
}

Speed operator"" _mps(long double speed) { long double resultingValue=speed/sqrt(3); return Speed(resultingValue, resultingValue ,resultingValue); }
Speed operator"" _mps(unsigned long long speed) { long double resultingValue=speed/sqrt(3); return Speed(resultingValue, resultingValue ,resultingValue); }

#endif //UNTITLED_SPEED_H
