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

#include "include/tools/logger.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace smle {

OpenCvFrame::OpenCvFrame(cv::Mat _mat)
{
    mMat = _mat;
//    mImage = _mat;
}

OpenCvFrame::~OpenCvFrame()
{
    mMat.release();
}

Pixel OpenCvFrame::getValue(int i, int j)
{
    // TODO: log
    IplImage mImage = mMat;
    Pixel p;
    p.b = ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 0]; // B
    p.g = ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 1]; // G
    p.r = ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 2]; // R
    return p;
}

void OpenCvFrame::setValue(int i, int j, Pixel value)
{
    // TODO: log
    IplImage mImage = mMat;
    uchar * shift = (uchar*)(mImage.imageData + i*mImage.widthStep
                               + j*mImage.nChannels);
    ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 0] = value.b;
    ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 1] = value.g;
    ((uchar *)(mImage.imageData + i*mImage.widthStep))[j*mImage.nChannels + 2] = value.r;
}

int OpenCvFrame::channels()
{
    return mMat.channels();
}

int OpenCvFrame::getWidth()
{
//    return mImage.width;
    return mMat.size().width;
}

int OpenCvFrame::getHeight()
{
    return mMat.size().height;
}

void OpenCvFrame::cvtColor(ConversionCode code)
{
//    cv::Mat aa;
    cv::Mat newMat;
    switch (code) {
    case ConversionCode::BgrToGray:
        if (mMat.channels() >= 3) {
            cv::cvtColor(mMat, newMat, CV_BGR2GRAY);
            mMat.release();
            cv::cvtColor(newMat, mMat, CV_GRAY2BGR);
            newMat.release();
        }
        break;
    }
}

IFrame *OpenCvFrame::detectEdge(double threshold1, double threshold2) const
{
    cv::Mat newMat;
    cv::Canny(mMat, newMat, threshold1, threshold2);
    return new OpenCvFrame(newMat);
}

IFrame *OpenCvFrame::blur(int cwidth, int cheight) const
{
    cv::Mat newMat;
    cv::GaussianBlur(mMat, newMat, cv::Size(cwidth, cheight), 0, 0);
    return new OpenCvFrame(newMat);
}

bool OpenCvFrame::isEmpty()
{
    return mMat.empty();
}

IFrame *OpenCvFrame::partFrame(int x, int y, int width, int height)
{
    if (x + width > getWidth() || y + height > getHeight())
        return nullptr;

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
    cv::Mat newMat;
    cv::copyMakeBorder(mMat, newMat,
                       size, size, size, size,
                       cv::BORDER_CONSTANT,
                       cv::Scalar(color.r, color.g, color.b));

    auto sizeMat = mMat.size();
    mMat.release();
    cv::resize(newMat, mMat, sizeMat);
//    mImage = mMat;
}

void OpenCvFrame::resize(int width, int height)
{
    cv::Mat newMat;
    cv::resize(mMat, newMat, cv::Size(width, height));
    mMat.release();
    mMat = newMat;
//    mImage = mMat;
//    return new OpenCvFrame(newMat);
}

void OpenCvFrame::splitImage(int _width, int _height)
{
    assert (getWidth() > _width && getHeight() > _height);
    cv::Mat small;
    cv::resize(mMat, small, cv::Size(_width, _height));
    int count = getWidth() / _width;
    for (int i = 0 ; i < count ; ++i) {
        for (int j = 0 ; j < count ; ++j) {
            auto part = mMat(cv::Rect(i * _width, j * _height,
                                       _width, _height));
            small.copyTo(part);
        }
    }
    small.release();
}

const cv::Mat &OpenCvFrame::getCvMat() const
{
    return mMat;
}

} // namespace smle
