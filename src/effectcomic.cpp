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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace smle {

EffectComic::EffectComic()
{
}


void EffectComic::getGray(const cv::Mat& input, cv::Mat& gray)
{
    const int numChannes = input.channels();
    if (numChannes == 4) {
        cv::cvtColor(input, gray, CV_BGRA2GRAY);
    }
    else if (numChannes == 3) {
        cv::cvtColor(input, gray, CV_BGR2GRAY);
    }
    else if (numChannes == 1) {
        gray = input;
    }
}

MatPtr EffectComic::apply(const MatPtr &src)
{
    auto dst = new cv::Mat(src->rows, src->cols, src->type());
    cv::Mat bgr = src->clone();
    cv::Mat buff;

    // very slow :( uncomment at feuture
    cv::pyrMeanShiftFiltering(bgr, bgr, 15, 40);

    getGray(bgr, buff);
    cv::Canny(buff, *dst, 150, 200);

    cv::cvtColor(*dst, buff, CV_GRAY2BGR);

    *dst = bgr - buff;

    return MatPtr(dst);
}

std::string EffectComic::name()
{
    return "Comic effect";
}

} // namespace smle

