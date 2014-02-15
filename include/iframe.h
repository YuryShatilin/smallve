/*

  smallve GPL Source Code
  Copyright (C) 2014 Yury Shatilin.

  This file is part of the smallve GPL Source Code (smallve Source Code).

  smallve Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  smallve Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with smallve Source Code. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SMLE_IFRAME_H
#define SMLE_IFRAME_H

#include <memory>

namespace smle {

using uchar = unsigned char;


enum class ConversionCode : unsigned int {
    BgrToGray = 0,
    GrayToBgr
};

class Pixel {
public:
    Pixel(uchar _r, uchar _g, uchar _b) :
        r(_r), g(_g), b(_b)
    {}
    Pixel() = default;
    uchar r = 0,
        g = 0,
        b = 0;
};

class Rect {
public:
    Rect(int _x, int _y, int _w, int _h):
        x(_x), y(_y), w(_w), h(_h)
    {}
    Rect() = default;
    int x = 0,
        y = 0,
        w = 0,
        h = 0;
};

// interface Frame
class IFrame
{
public:

    IFrame(IFrame & frame);
    IFrame(int width, int height);

    virtual Pixel getValue(int i, int j) = 0;
    virtual void setValue(int i, int j, Pixel value) = 0;
    virtual int channels() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    virtual IFrame * cvtColor(ConversionCode code) = 0;
    virtual IFrame * detectEdge(double threshold1, double threshold2) = 0;
    virtual IFrame * blur(int cwidth, int cheight) = 0;

    virtual bool isEmpty() = 0;

    virtual void copyTo(IFrame * other) = 0;
    virtual IFrame* partFrame(int x, int y, int width, int height) = 0;
    virtual IFrame* partFrame(Rect rect) = 0;

    virtual IFrame * clone() = 0;
    virtual IFrame& operator=(IFrame & other) = 0;

    virtual void addBorder(int size, Pixel color) = 0;
    virtual IFrame * resize(int width, int height) = 0;

    virtual void minus(const IFrame & other) = 0;
};

using FramePtr = std::shared_ptr<IFrame>;

} // namespace smle

#endif // SMLE_IFRAME_H
