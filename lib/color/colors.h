#ifndef COLORS_H
#define COLORS_H

#include "color.h"
#include <unordered_map>
#include <string>

extern std::unordered_map<std::string, Color> colors = {
    {"+", {3, 150, 208}},
    {"-", {240, 200, 0}},
    {"|", {220, 36, 33}},
    {"*", {64, 169, 68}},
};

#endif