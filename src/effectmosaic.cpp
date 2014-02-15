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

#include "include/effectmosaic.h"

namespace smle {

EffectMosaic::EffectMosaic(int _mosaicSize):
    mMosaicSize(_mosaicSize)
{
}

void EffectMosaic::apply(FramePtr &src)
{

    for(int i=0; i < src->getHeight(); i+=mMosaicSize) {
        for(int j=0; j < src->getWidth(); j+=mMosaicSize) {
            auto pixel = AverageColor(src.get(), i, j);
            SetColor(src.get(), j, i, pixel);
        }
    }
}

std::string EffectMosaic::name()
{
    return "Effect Mosaic, size = " + std::to_string(mMosaicSize);
}

Pixel EffectMosaic::AverageColor(IFrame *img, int row, int col)
{
    int r, g, b;
    r = g = b = 0;
    int counter = 0;

    for(int i=row; (i < img->getHeight())&&(i < row+mMosaicSize); i++) {
        for(int j=col; (j < img->getWidth())&&(j < col+mMosaicSize); j++) {
            b += img->getValue(i,j).b;
            g += img->getValue(i,j).g;
            r += img->getValue(i,j).r;
            counter++;
        }
    }

    r /= counter;
    g /= counter;
    b /= counter;

    return Pixel(r,g,b);
}


void EffectMosaic::SetColor(IFrame *img, int col, int row, Pixel value)
{
//    Pixel p(r,g,b);
    for(int i=row; (i < img->getHeight())&&(i < row+mMosaicSize); i++) {
        for(int j=col; (j < img->getWidth())&&(j < col+mMosaicSize); j++) {
            img->setValue(i,j,value);
        }
    }
}

} // namespace smle
