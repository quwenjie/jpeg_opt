#pragma once
#include <iostream>
#include "ddraw.h"
enum ComponentsType
{
    Coin,
    Nail,
    Nut,
    Screw,
    Box,
    Wrench,
    Unknown,
    UnknownSquare
};

std::string ComponentsTypeName[] = {
    "Coin",
    "Nail",
    "Nut",
    "Screw",
    "Box",
    "Wrench",
    "Unknown",
    "UnknownSquare"
};
PixelBuffer::Pixel ComponentsColor[] = {
    {255,0,0}, // coin
    {0,255,0}, // nail
    {0,0,255}, // nut
    {255,255,0}, // screw
    {255,0,255}, // box
    {0,255,255}, // wrench
    {255,255,255}, // unknown
    {127,127,127}, // unknownSquare
};

ComponentsType judge(double size, double boxSize,double width,double height,bool isNail) //width>height
{
    double ratio = size / boxSize;
    if(width<1.15*height)
    {
        if (ratio > 0.85 )
        {
            return ComponentsType::Box;
        }
        if (ratio > 0.73 && ratio < 0.82 && size > 4000 )
        {
            return ComponentsType::Coin;
        }
        if (ratio > 0.2 && ratio < 0.3 && size < 500)
        {
            return ComponentsType::Nut;
        }
        return ComponentsType::UnknownSquare;
    }
    if (ratio > 0.45 && ratio < 0.6)
    {
        if(isNail){
            return ComponentsType::Nail;
        }
        return ComponentsType::Screw;
    }
    if (ratio > 0.3 && ratio < 0.4)
    {
        return ComponentsType::Nail;
    }
    
    if (ratio < 0.2 && size > 2000)
    {
        return ComponentsType::Wrench;
    }
    if(isNail){
        return ComponentsType::Nail;
    }
    return ComponentsType::Unknown;
}