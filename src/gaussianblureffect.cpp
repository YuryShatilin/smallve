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

#include "include/gaussianblureffect.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace smle {

GaussianBlurEffect::GaussianBlurEffect(cv::Size _kSize):
    mKSzie(_kSize)
{
}

MatPtr GaussianBlurEffect::apply(const MatPtr &src)
{
    auto dst = new cv::Mat(*src);

    cv::GaussianBlur(*src, *dst, mKSzie, 0, 0);

    return MatPtr(dst);
}

std::string GaussianBlurEffect::name()
{
    return "Blur effect";
}

} // namespace smle
