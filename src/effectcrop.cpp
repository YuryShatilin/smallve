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

#include "include/effectcrop.h"
#include "include/tools/logger.h"

namespace smle {

EffectCrop::EffectCrop(int _x, int _y, int _w, int _h):
    mRect(_x, _y, _w, _h)
{
}

void EffectCrop::apply(FramePtr &src)
{
    if (mRect.x +  mRect.w > src->getWidth() ||
        mRect.y + mRect.h > src->getHeight()) {
        Logger::instance().errorWrite("Crop Effect can't apply");
    }

    src = FramePtr(src->partFrame(mRect)->clone());
}

std::string EffectCrop::name()
{
    return "Crop effect";
}

} // namespace smle
