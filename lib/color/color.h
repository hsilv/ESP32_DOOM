#pragma once
#include <iostream>

template <typename T>
constexpr const T &clamp(const T &value, const T &minValue, const T &maxValue)
{
    return (value < minValue) ? minValue : ((maxValue < value) ? maxValue : value);
}

class Color
{
public:
    Color() : r(0), g(0), b(0) {}
    Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}

    Color(int red, int green, int blue, int alpha = 255)
    {
        r = static_cast<uint8_t>(std::min(std::max(red, 0), 255));
        g = static_cast<uint8_t>(std::min(std::max(green, 0), 255));
        b = static_cast<uint8_t>(std::min(std::max(blue, 0), 255));
    }

    Color(float red, float green, float blue, float alpha = 1.0f)
    {
        r = clamp(static_cast<uint8_t>(red * 255), uint8_t(0), uint8_t(255));
        g = clamp(static_cast<uint8_t>(green * 255), uint8_t(0), uint8_t(255));
        b = clamp(static_cast<uint8_t>(blue * 255), uint8_t(0), uint8_t(255));
    }

    uint8_t &getBlue()
    {
        return b;
    }

    const uint8_t &getBlue() const
    {
        return b;
    }

    uint8_t &getGreen()
    {
        return g;
    }

    const uint8_t &getGreen() const
    {
        return g;
    }

    uint8_t &getRed()
    {
        return r;
    }

    const uint8_t &getRed() const
    {
        return r;
    }

    Color operator+(const Color &other) const
    {
        return Color(
            std::min(255, int(r) + int(other.r)),
            std::min(255, int(g) + int(other.g)),
            std::min(255, int(b) + int(other.b)));
    }

    // Overload the * operator to scale colors by a factor
    Color operator*(float factor) const
    {
        return Color(
            clamp(static_cast<uint8_t>(r * factor), uint8_t(0), uint8_t(255)),
            clamp(static_cast<uint8_t>(g * factor), uint8_t(0), uint8_t(255)),
            clamp(static_cast<uint8_t>(b * factor), uint8_t(0), uint8_t(255)));
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color)
    {
        os << "\033[1;97mColor ->\033[0m ";
        os << "\033[1;31mR:" << static_cast<int>(color.r) << "\033[0m, ";
        os << "\033[1;32mG:" << static_cast<int>(color.g) << "\033[0m, ";
        os << "\033[1;34mB:" << static_cast<int>(color.b) << "\033[0m";
        return os;
    }

    uint16_t toHex() const
    {
        uint16_t r_16 = (r * 31) / 255;
        uint16_t g_16 = (g * 63) / 255;
        uint16_t b_16 = (b * 31) / 255;

        return (r_16 << 11) | (g_16 << 5) | b_16;
    }

    void fromHex(uint32_t hexColor)
    {
        r = (hexColor >> 16) & 0xFF;
        g = (hexColor >> 8) & 0xFF;
        b = hexColor & 0xFF;
    }

private:
    uint8_t r, g, b;
};