#include <regex>
#ifndef UNTITLED_FORCE_H
#define UNTITLED_FORCE_H



class Force {
    long double x_value;
    long double y_value;
    long double z_value;
public:
    Force(long double _x = 0., long double _y = 0., long double _z = 0.)
            : x_value(_x), y_value(_y), z_value(_z) {}
    Force(std::string);
    ~Force() = default;

    long double vectorLength() const {return sqrt(pow(x_value,2)+pow(y_value,2)+pow(z_value,2));}
    long double length = vectorLength();

    long double get_x() const { return x_value; }
    long double get_y() const { return y_value; }
    long double get_z() const { return z_value; }
    //конструктор копировани€
    Force(const Force& rhs) : x_value(rhs.x_value), y_value(rhs.y_value), z_value(rhs.z_value)  {}


    Force& operator=(const Force& rhs)
    {
        if(this == &rhs) return *this; //самоприсваивание
        x_value = rhs.x_value;
        y_value = rhs.y_value;
        z_value = rhs.z_value;
        return *this;
    }
    Force operator+() const { return *this; }
    Force operator-() const { return Force(-x_value, -y_value, -z_value); }
    Force& operator+=(const Force& rhs) { x_value += rhs.x_value;  y_value += rhs.y_value; z_value += rhs.z_value; return *this;}
    Force& operator-=(const Force& rhs) { return (*this) += (-rhs); }
    Force& operator+(const Force& rhs) { return (*this) += rhs; }
    Force& operator-(const Force& rhs) { return (*this) -= rhs; }
    //скал€рное произведение
    long double operator*(const Force& rhs) { return x_value*rhs.x_value + y_value*rhs.y_value + z_value*rhs.z_value; }
    //умножение на скал€р
    Force& operator*=(long double rhs) {x_value *= rhs;  y_value *= rhs; z_value *= rhs; return *this;}
    Force& operator*(long double rhs) { return (*this) *= rhs;}

    friend std::ostream& operator << (std::ostream&, const Force&);
    friend std::istream& operator>> (std::istream &in, Force&);
    friend Force operator"" _N(long double);
    friend Force operator"" _N(unsigned long long);

    auto operator<=>(const Force& rhs) const {
        return this->vectorLength() <=> rhs.vectorLength();
    }
    bool operator==(const Force rhs) const {
        return this->vectorLength() == rhs.vectorLength();
    }
};

Force::Force(std::string input)
{
    setlocale(LC_NUMERIC, "en-US");

    const std::regex rgx(R"(\S+\((\S+),\s(\S+),\s(\S+)\))"); //https://habr.com/ru/company/otus/blog/532056/
    std::smatch match;
    x_value = 0.; y_value = 0.; z_value = 0.;
    if (std::regex_match(input, match, rgx))
    {
        x_value = std::stold("3.1"); y_value = std::stold(match[2]); z_value = std::stold(match[3]);
    }
}

std::ostream& operator << (std::ostream& out, const Force& obj)
{
    return out << "Force(" << obj.get_x() << ", " << obj.get_y() << ", " << obj.get_z() <<")";
}

std::istream& operator>> (std::istream &in, Force& value)
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
                std::cout << "ќшибка ввода!" << std::endl;
                std::cout << "¬ведите корректное значение: ";
                isError = true;
            }
        } while (isError);
    }

    value.x_value = _coordinates[0]; value.y_value = _coordinates[1]; value.z_value = _coordinates[2];
    return in;
}

Force operator"" _N(long double force) { long double resultingValue=force/sqrt(3); return Force(resultingValue, resultingValue ,resultingValue); }
Force operator"" _N(unsigned long long force) { long double resultingValue=force/sqrt(3); return Force(resultingValue, resultingValue ,resultingValue); }

#endif //UNTITLED_FORCE_H
