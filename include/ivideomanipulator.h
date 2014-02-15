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

#ifndef SMLE_IVIDEOMANIPULATOR_H
#define SMLE_IVIDEOMANIPULATOR_H

#include "iframe.h"
#include "effectmanager.h"
#include <memory>

namespace smle {

class IVideoManipulator
{
public:
    virtual void nextFrame(FramePtr & _originalFrame, FramePtr & nextFrame,
                               EffectsPtr effects) = 0;

    virtual int countFrame() = 0;
    virtual bool openVideo(const std::string &filename) = 0;
    virtual bool isOpen() = 0;

    virtual void closeSafeVideo() = 0;
    virtual void setSafeVideo(const std::string &filename) = 0;

    virtual FramePtr createEmptyFrame() = 0;
};

using ManipulatorPtr = std::shared_ptr<IVideoManipulator>;

} // namespace smle

#endif // SMLE_IVIDEOMANIPULATOR_H
