#ifndef UNTITLED_ACCELERATION_H
#define UNTITLED_ACCELERATION_H

class Acceleration {
    long double x_value;
    long double y_value;
    long double z_value;
public:
    Acceleration(long double _x = 0., long double _y = 0., long double _z = 0.)
            : x_value(_x), y_value(_y), z_value(_z) {}
    Acceleration(std::string str);
    ~Acceleration() = default;

    long double vectorLength() const {return sqrt(pow(x_value,2)+pow(y_value,2)+pow(z_value,2));}
    long double length = vectorLength();

    long double get_x() const { return x_value; }
    long double get_y() const { return y_value; }
    long double get_z() const { return z_value; }
    //конструктор копирования
    Acceleration(const Acceleration& rhs) : x_value(rhs.x_value), y_value(rhs.y_value), z_value(rhs.z_value)  {}
    Acceleration& operator=(const Acceleration& rhs)
    {
        if(this == &rhs) return *this; //самоприсваивание
        x_value = rhs.x_value;
        y_value = rhs.y_value;
        z_value = rhs.z_value;
        return *this;
    }
    Acceleration operator+() const { return *this; }
    Acceleration operator-() const { return Acceleration(-x_value, -y_value, -z_value); }
    Acceleration& operator+=(const Acceleration& rhs) { x_value += rhs.x_value;  y_value += rhs.y_value; z_value += rhs.z_value; return *this;}
    Acceleration& operator-=(const Acceleration& rhs) { return (*this) += (-rhs); }
    Acceleration& operator+(const Acceleration& rhs) { return (*this) += rhs; }
    Acceleration& operator-(const Acceleration& rhs) { return (*this) -= rhs; }
    //скалярное произведение
    long double operator*(const Acceleration& rhs) { return x_value*rhs.x_value + y_value*rhs.y_value + z_value*rhs.z_value; }
    //умножение на скаляр
    Acceleration& operator*=(long double rhs) {x_value *= rhs;  y_value *= rhs; z_value *= rhs; return *this;}
    Acceleration& operator*(long double rhs) { return (*this) *= rhs;}

    friend std::ostream& operator << (std::ostream&, const Acceleration&);
    friend std::istream& operator>> (std::istream &in, Acceleration&);
    friend Acceleration operator"" _mpss(long double);
    friend Acceleration operator"" _mpss(unsigned long long);

    auto operator<=>(const Acceleration& rhs) const {
        return this->vectorLength() <=> rhs.vectorLength();
    }
    bool operator==(const Acceleration& rhs) const {
        return this->vectorLength() == rhs.vectorLength();
    }
};

Acceleration::Acceleration(std::string str)
{
    const char *cstr = str.data();  //https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
    x_value=0.; y_value=0.; z_value=0.;
    sscanf(cstr, "%*[^(](%Lf, %Lf, %Lf)", &x_value, &y_value, &z_value);
}

std::ostream& operator << (std::ostream& out, const Acceleration& obj)
{
    return out << "Acceleration(" << obj.get_x() << ", " << obj.get_y() << ", " << obj.get_z() <<")";
}

std::istream& operator>> (std::istream &in, Acceleration& value)
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

    value.x_value = _coordinates[0]; value.y_value = _coordinates[1]; value.z_value = _coordinates[2];
    return in;
}

Acceleration operator"" _mpss(long double impulse) { long double resultingValue=impulse/sqrt(3); return Acceleration(resultingValue, resultingValue ,resultingValue); }
Acceleration operator"" _mpss(unsigned long long impulse) { long double resultingValue=impulse/sqrt(3); return Acceleration(resultingValue, resultingValue ,resultingValue); }



#endif //UNTITLED_ACCELERATION_H
