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

#include "include/effectcomic.h"

namespace smle {

EffectComic::EffectComic()
{
}

void EffectComic::apply(FramePtr &src)
{
//    auto dst = new cv::Mat(src->rows, src->cols, src->type());
//    cv::Mat bgr = src->clone();
//    cv::Mat buff;
    FramePtr buff = FramePtr(src->cvtColor(ConversionCode::BgrToGray));

    buff = FramePtr(buff->detectEdge(150, 200));
    buff = FramePtr(buff->cvtColor(ConversionCode::GrayToBgr));

    src->minus(*buff);

    // very slow :( uncomment at feuture
//    cv::pyrMeanShiftFiltering(bgr, bgr, 15, 40);

//    getGray(bgr, buff);
//    cv::Canny(buff, *dst, 150, 200);

//    cv::cvtColor(*dst, buff, CV_GRAY2BGR);

//    *dst = bgr - buff;

//    return MatPtr(dst);
}

std::string EffectComic::name()
{
    return "Comic effect";
}

} // namespace smle

