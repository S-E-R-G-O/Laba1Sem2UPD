#ifndef UNTITLED_IMPULSE_H
#define UNTITLED_IMPULSE_H

class Impulse {
    long double x_value{};
    long double y_value{};
    long double z_value{};
public:
    Impulse(long double _x = 0., long double _y = 0., long double _z = 0.)
            : x_value(_x), y_value(_y), z_value(_z) {}
    ~Impulse() = default;
    long double get_x() const { return x_value; }
    long double get_y() const { return y_value; }
    long double get_z() const { return z_value; }
    //конструктор копирования
    Impulse(const Impulse& rhs) : x_value(rhs.x_value), y_value(rhs.y_value), z_value(rhs.z_value)  {}
    Impulse(std::string str);
    Impulse& operator=(const Impulse& rhs)
    {
        if(this == &rhs) return *this; //самоприсваивание
        x_value = rhs.x_value;
        y_value = rhs.y_value;
        z_value = rhs.z_value;
        return *this;
    }
    Impulse operator+() const { return *this; }
    Impulse operator-() const { return Impulse(-x_value, -y_value, -z_value); }
    Impulse& operator+=(const Impulse& rhs) { x_value += rhs.x_value;  y_value += rhs.y_value; z_value += rhs.z_value; return *this;}
    Impulse& operator-=(const Impulse& rhs) { return (*this) += (-rhs); }
    Impulse& operator+(const Impulse& rhs) { return (*this) += rhs; }
    Impulse& operator-(const Impulse& rhs) { return (*this) -= rhs; }
    //скалярное произведение
    long double operator*(const Impulse& rhs) { return x_value*rhs.x_value + y_value*rhs.y_value + z_value*rhs.z_value; }
    //умножение на скаляр
    Impulse& operator*=(long double rhs) {x_value *= rhs;  y_value *= rhs; z_value *= rhs; return *this;}
    Impulse& operator*(long double rhs) { return (*this) *= rhs;}

    friend std::ostream& operator << (std::ostream&, const Impulse&);
    friend std::istream& operator>> (std::istream &in, Impulse&);
    friend Impulse operator"" _kgmps(long double);
    friend Impulse operator"" _kgmps(unsigned long long);

    long double vectorLength() const {return sqrt(pow(x_value,2)+pow(y_value,2)+pow(z_value,2));}
    auto operator<=>(const Impulse& rhs) const {
        return this->vectorLength() <=> rhs.vectorLength();
    }
    bool operator==(const Impulse& rhs) const {
        return this->vectorLength() == rhs.vectorLength();
    }

    long double length = vectorLength();
};

Impulse::Impulse(std::string str)
{
    const char *cstr = str.data();  //https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
    x_value=0.; y_value=0.; z_value=0.;
    sscanf(cstr, "%*[^(](%Lf, %Lf, %Lf)", &x_value, &y_value, &z_value);
}

std::ostream& operator << (std::ostream& out, const Impulse& obj)
{
    return out << "Impulse(" << obj.get_x() << ", " << obj.get_y() << ", " << obj.get_z() <<")";
}

std::istream& operator>> (std::istream &in, Impulse& impulse)
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

    impulse.x_value = _coordinates[0]; impulse.y_value = _coordinates[1]; impulse.z_value = _coordinates[2];
    return in;
}

Impulse operator"" _kgmps(long double impulse) { long double resultingValue=impulse/sqrt(3); return Impulse(resultingValue, resultingValue ,resultingValue); }
Impulse operator"" _kgmps(unsigned long long impulse) { long double resultingValue=impulse/sqrt(3); return Impulse(resultingValue, resultingValue ,resultingValue); }


#endif //UNTITLED_IMPULSE_H
