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

#include "include/effectreplicate.h"

#include "include/tools/logger.h"

#include "include/opencvimpl/opencvframe.h"

namespace smle {

EffectReplicate::EffectReplicate(int _count):
    mCountCopies(_count)
{
}

void EffectReplicate::apply(FramePtr &src)
{
    int smallheight = src->getHeight() / mCountCopies;
    int smallwidth = src->getWidth() / mCountCopies;

    src->splitImage(smallwidth, smallheight);

//    auto smallImage = src->resize(smallwidth, smallheight);

//    for (int i = 0 ; i < mCountCopies ; ++i) {
//        for (int j = 0 ; j < mCountCopies ; ++j) {
//            auto part = src->partFrame(i * smallwidth, j * smallheight,
//                                       smallwidth, smallheight);
//            smallImage->copyTo(part);
//        }
//    }
//    delete smallImage;
}

std::string EffectReplicate::name()
{
    return "Replicate effect";
}


} // namespace smle
