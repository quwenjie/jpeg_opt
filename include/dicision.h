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
    "UnkSquare"
};
PixelBuffer::Pixel ComponentsColor[] = {
    {255,0,0}, // coin
    {0,255,0}, // nail
    {0,0,255}, // nut
    {0,0,0}, // screw
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
        if (width<40)
        {
            return ComponentsType::Nut;
        }
        return ComponentsType::UnknownSquare;
    }

    if (ratio > 0.45 && ratio < 0.7)
    {
        if(isNail)
        {
            //cout<<"IsNail0.45-0.6"<<endl;
            return ComponentsType::Nail;
        }
        return ComponentsType::Screw;
    }
    if (ratio > 0.3 && ratio < 0.4)
    {
        cout<<"IsNail0.3-0.4"<<endl;
        return ComponentsType::Nail;
    }
    
    if (ratio < 0.2 && size > 2000)
    {
        return ComponentsType::Wrench;
    }
    if(isNail)
    {
        cout<<"IsNail"<<endl;
        return ComponentsType::Nail;
    }
    return ComponentsType::Unknown;
}