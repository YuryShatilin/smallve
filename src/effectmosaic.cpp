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

using cv::Mat;
using cv::Scalar;

EffectMosaic::EffectMosaic(int _mosaicSize):
    mMosaicSize(_mosaicSize)
{
}

MatPtr EffectMosaic::apply(const MatPtr &src)
{
    Mat* dst = new Mat(src->rows, src->cols, src->type());

    IplImage image = *src;
    IplImage dstImage = *dst;
    for(int i=0; i < image.height; i+=mMosaicSize) {
        for(int j=0; j < image.width; j+=mMosaicSize) {
            auto scalar = AverageColor(&image, i, j);

            SetColor(&dstImage, j, i, scalar[0], scalar[1], scalar[2]);
        }
    }

    return MatPtr(dst);
}

std::string EffectMosaic::name()
{
    return "Effect Mosaic, size = " + std::to_string(mMosaicSize);
}

Scalar EffectMosaic::AverageColor(const IplImage * img, int row, int col)
{
    int r, g, b;
    r = g = b = 0;
    int counter = 0;

    for(int i=row; (i < img->height)&&(i < row+mMosaicSize); i++) {
        for(int j=col; (j < img->width)&&(j < col+mMosaicSize); j++) {
            b += ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0]; // B
            g += ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1]; // G
            r += ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2]; // R
            counter++;
        }
    }

    r /= counter;
    g /= counter;
    b /= counter;

    return Scalar(r,g,b);
}


void EffectMosaic::SetColor(IplImage *img, int col, int row, int r, int g, int b)
{
    for(int i=row; (i < img->height)&&(i < row+mMosaicSize); i++) {
        for(int j=col; (j < img->width)&&(j < col+mMosaicSize); j++) {
            ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0] = b; // B
            ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1] = g; // G
            ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2] = r; // R
        }
    }
}

} // namespace smle
