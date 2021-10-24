#ifndef UNTITLED_MASS_H
#define UNTITLED_MASS_H

#include "constants.h"
#include <math.h>
#include <compare>

class Energy;

class Mass
{
private:
    long double m_value;
public:
    Mass(long double value = 0.) : m_value(value){};
    Mass(std::string);
    ~Mass() = default;
    long double get_value() const { return m_value; }
    Mass(const Mass& rhs) : m_value(rhs.m_value) {}
    Mass& operator=(const Mass& rhs) { m_value = rhs.m_value; return *this; }
    Mass& operator+(const Mass& rhs) { m_value += rhs.m_value; return *this; }
    Mass& operator-(const Mass& rhs) { m_value -= rhs.m_value; m_value = fabs(m_value); return *this; }
    Mass& operator*(const Mass& rhs) { m_value *= rhs.m_value; return *this; }
    Mass& operator*(long double rhs) { m_value *= rhs; return *this;} // 2_kg*2 = 4_kg

    friend Mass& operator*(long double lhs, const Mass &rhs);// 2*2_kg = 4_kg

    long double operator/(const Mass& rhs); // при делении Кг / Кг = разы
    const Mass& operator/(long double rhs); // например на треть меньше

    auto operator<=>(const Mass& rhs) const = default;

// Для массы и энергии определить взаимнооднозначные операторы преобразования по формуле E=mc2.
    explicit operator Energy() const;

    friend std::ostream& operator<< (std::ostream&, const Mass&);
    friend std::istream& operator>> (std::istream &in, Mass&);
    friend Mass operator"" _kg(long double);
    friend Mass operator"" _kg(unsigned long long);
};

std::ostream& operator<< (std::ostream& out, const Mass& obj) { return out << obj.get_value() << "_kg"; }
std::istream& operator>> (std::istream &in, Mass& mass)
{
    char str[32];
    bool isError;

    do
    {
        isError = false;
        try
        {
            in.getline( str, sizeof(str) );
            mass.m_value = std::stold(str);
        }
        catch(std::exception&)
        {
            in.clear();
            std::cout << "Ошибка ввода!" << std::endl;
            std::cout << "Введите корректное значение: ";
            isError = true;
        }
    } while (isError);

    return in;
}
Mass::Mass(std::string str)
{
    const char *cstr = str.data();  //https://stackoverflow.com/questions/7352099/stdstring-to-char/7352131
    m_value=0.;
    sscanf(cstr, "%Lf_", &m_value);
}

Mass operator"" _kg(long double mass) { return Mass(mass); }
Mass operator"" _kg(unsigned long long mass) { return Mass(mass); }

long double Mass::operator/(const Mass& rhs)
{
    (rhs.m_value == 0)
    ? throw std::runtime_error("Math error: Attempted to divide by Zero\n")
    : m_value /= rhs.m_value; return get_value();
}
const Mass& Mass::operator/(const long double rhs)
{
    (rhs == 0)
    ? throw std::runtime_error("Math error: Attempted to divide by Zero\n")
    :  m_value /= rhs; return *this;
}

Mass& operator*(const long double lhs, const Mass &rhs)  { return const_cast<Mass &>(rhs) * lhs; }

#include "Energy.h"
// Для массы и энергии определить взаимнооднозначные операторы преобразования по формуле E=mc2.
Mass::operator Energy() const
{
    return Energy(m_value*C2);
}

#endif //UNTITLED_MASS_H
