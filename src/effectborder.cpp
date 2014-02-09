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

#include "include/effectborder.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace smle {


EffectBorder::EffectBorder(int _sizeBorder, int r, int g, int b):
    mSizeBorder(_sizeBorder),
    mColor(r,g,b)
{
}

EffectBorder::EffectBorder(int _sizeBorder, const cv::Scalar &_value):
    mSizeBorder(_sizeBorder),
    mColor(_value)
{
}

MatPtr EffectBorder::apply(const MatPtr &src)
{
    auto dst = new cv::Mat(*src);

    cv::copyMakeBorder(*src,*dst,
                       mSizeBorder, mSizeBorder,
                       mSizeBorder, mSizeBorder,
                       cv::BORDER_DEFAULT,
                       mColor);
    return MatPtr(dst);
}

std::string EffectBorder::name()
{
    return "Border effect";
}

} // namespace smle
