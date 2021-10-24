#ifndef UNTITLED_ENERGY_H
#define UNTITLED_ENERGY_H

#include "constants.h"

class Mass;

class Energy
{
private:
long double e_value;
public:
    Energy(long double value = 0.) : e_value(value) {}
    Energy(std::string);

    ~Energy() = default;
    long double get_value() const { return e_value; }
    Energy(const Energy& rhs) : e_value(rhs.e_value) {}
    Energy& operator=(const Energy& rhs) { e_value = rhs.e_value; return *this; }
    Energy& operator+(const Energy& rhs) { e_value += rhs.e_value; return *this; }
    Energy& operator-(const Energy& rhs) { e_value -= rhs.e_value; e_value = fabs(e_value); return *this; }
    Energy& operator*(const Energy& rhs) { e_value *= rhs.e_value; return *this; }
    Energy& operator*(long double rhs) { e_value *= rhs; return *this;} // 2_J*2 = 4_J

    friend Energy& operator*(long double lhs, const Energy &rhs);// 2*2_J = 4_J

    long double operator/(const Energy& rhs); // при делении J / J = разы
    const Energy& operator/(long double rhs); // например на треть меньше

    auto operator<=>(const Energy& rhs) const = default;

    // Для массы и энергии определить взаимнооднозначные операторы преобразования по формуле E=mc^2.
    explicit operator Mass() const;

    friend std::ostream& operator<< (std::ostream&, const Energy&);
    friend std::istream& operator>> (std::istream &in, Energy& energy);

    friend Energy operator"" _J(long double energy);
    friend Energy operator"" _J(unsigned long long energy);
};

std::ostream& operator << (std::ostream& out, const Energy& obj) { return out << obj.get_value() << "_J"; }
std::istream& operator>> (std::istream &in, Energy& energy)
{
    char str[32];
    bool isError;

    do
    {
        isError = false;
        try
        {
            in.getline( str, sizeof(str) );
            energy.e_value = std::stold(str);
        }
        catch(std::exception& e)
        {
            in.clear();
            std::cout << "Ошибка ввода!" << std::endl;
            std::cout << "Введите корректное значение: ";
            isError = true;
        }
    } while (isError);

    return in;
}
Energy::Energy(std::string str)
{
    const char *cstr = str.data();  //https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
    e_value=0.;
    sscanf(cstr, "%Lf_", &e_value);
}
std::istream& operator>> (std::istream &in, Energy& energy);

Energy operator"" _J(long double energy) { return Energy(energy); }
Energy operator"" _J(unsigned long long energy) { return Energy(energy); }

long double Energy::operator/(const Energy& rhs)
{
    (rhs.e_value == 0)
    ? throw std::runtime_error("Math error: Attempted to divide by Zero\n")
    : e_value /= rhs.e_value; return get_value();
}
const Energy& Energy::operator/(const long double rhs)
{
    (rhs == 0)
    ? throw std::runtime_error("Math error: Attempted to divide by Zero\n")
    :  e_value /= rhs; return *this;
}

Energy& operator*(const long double lhs, const Energy &rhs)  { return const_cast<Energy &>(rhs) * lhs; }

#include "Mass.h"
Energy::operator Mass() const
{
    return Mass(e_value/C2);
}

#endif //UNTITLED_ENERGY_H
