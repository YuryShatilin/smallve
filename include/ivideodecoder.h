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

#ifndef IVIDEODECODER_H
#define IVIDEODECODER_H

#include "iframe.h"

namespace smle {

// interface for video decoder
class IVideoDecoder
{
public:
    virtual IFrame * nextFrame() = 0;
    virtual int frameCount() = 0;

    virtual bool isOpen() = 0;
    virtual bool open() = 0;

    virtual int getFps() = 0;
    virtual int getFourcc() = 0;
};

} // namespace smle

#endif // IVIDEODECODER_H
