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

#include "include/opencvimpl/opencvframe.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace smle {

OpenCvFrame::OpenCvFrame(cv::Mat _mat):
    IFrame()
{
    mMat = _mat;
    mImage = _mat;
}

OpenCvFrame::~OpenCvFrame()
{
    mMat.release();
}

Pixel OpenCvFrame::getValue(int i, int j)
{
    Pixel p;
//    IplImage image = *mMat;
//    int w = image.widthStep;

    ///TODO: implemetns this
//    p.b = image.imageData[];
//    p.r = image.imageData[];
//    p.g = image.imageData[];
    return p;
}

void OpenCvFrame::setValue(int i, int j, Pixel value)
{
    /// TODO: implemetns this
    Pixel p;
//    IplImage image = *mMat;
//    int w = image.widthStep;
}

int OpenCvFrame::channels()
{
    return mMat.channels();
}

int OpenCvFrame::getWidth()
{
    return mImage.width;
}

int OpenCvFrame::getHeight()
{
    mImage.height;
}

IFrame *OpenCvFrame::cvtColor(ConversionCode code)
{
    cv::Mat newMat;// = mMat.clone();
    switch (code) {
    case ConversionCode::BgrToGray:
        cv::cvtColor(mMat, newMat, CV_BGR2GRAY);
        break;
    case ConversionCode::GrayToBgr:
        cv::cvtColor(mMat, newMat, CV_GRAY2BGR);
        break;
    }

    return new OpenCvFrame(newMat);
}

IFrame *OpenCvFrame::detectEdge(double threshold1, double threshold2)
{
    cv::Mat newMat;
    cv::Canny(mMat, newMat, threshold1, threshold2);
    return new OpenCvFrame(newMat);
}

IFrame *OpenCvFrame::blur(int cwidth, int cheight)
{
    cv::Mat newMat;
    cv::GaussianBlur(mMat, newMat, cv::Size(cwidth, cheight), 0, 0);
    return new OpenCvFrame(newMat);
}

bool OpenCvFrame::isEmpty()
{
    return mMat.empty();
}

void OpenCvFrame::copyTo(IFrame *other)
{
    // TODO: i unknow release this function !!
}

IFrame *OpenCvFrame::partFrame(int x, int y, int width, int height)
{
    auto part = mMat(cv::Rect(x,y,width,height));
    return new OpenCvFrame(part);
}

IFrame *OpenCvFrame::partFrame(Rect rect)
{
    return partFrame(rect.x, rect.y, rect.w, rect.h);
}

IFrame *OpenCvFrame::clone()
{
    return new OpenCvFrame(mMat.clone());
}

void OpenCvFrame::addBorder(int size, Pixel color)
{
//    cv::Mat newMat;
    cv::copyMakeBorder(mMat, mMat,
                       size, size, size, size,
                       cv::BORDER_CONSTANT,
                       cv::Scalar(color.r, color.b, color.g));

//    return new OpenCvFrame(newMat);
}

IFrame *OpenCvFrame::resize(int width, int height)
{
    cv::Mat newMat;
    cv::resize(mMat, newMat, cv::Size(width, height));

    return new OpenCvFrame(newMat);
}

const cv::Mat &OpenCvFrame::getCvMat() const
{
    return mMat;
}

} // namespace smle
