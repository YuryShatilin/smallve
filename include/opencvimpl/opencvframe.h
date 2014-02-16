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

#ifndef SMLE_OPENCVFRAME_H
#define SMLE_OPENCVFRAME_H

#include "../iframe.h"

#include <opencv2/core/core.hpp>

namespace smle {

class OpenCvFrame : public IFrame
{
public:
    explicit OpenCvFrame(cv::Mat _mat);

    OpenCvFrame() = delete;
    OpenCvFrame(const OpenCvFrame & _frame) = delete;

    virtual ~OpenCvFrame();

    // IFrame interface
public:
    virtual Pixel getValue(int i, int j) override;
    virtual void setValue(int i, int j, Pixel value) override;
    virtual int channels() override;
    virtual int getWidth() override;
    virtual int getHeight() override;
    virtual IFrame *cvtColor(ConversionCode code) override;
    virtual IFrame *detectEdge(double threshold1, double threshold2) override;
    virtual IFrame *blur(int cwidth, int cheight) override;
    virtual bool isEmpty() override;

    virtual void copyTo(IFrame *other) override;

    virtual IFrame *partFrame(int x, int y, int width, int height) override;
    virtual IFrame *partFrame(Rect rect) override;
    virtual IFrame *clone() override;

    virtual void addBorder(int size, Pixel color) override;
    virtual IFrame *resize(int width, int height) override;

    const cv::Mat & getCvMat() const;

private:
    cv::Mat mMat;
    IplImage mImage;
};

} // namespace smle

#endif // SMLE_OPENCVFRAME_H
