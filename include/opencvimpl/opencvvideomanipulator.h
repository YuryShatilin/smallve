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

#ifndef SMLE_OPENCVVIDEOMANIPULATOR_H
#define SMLE_OPENCVVIDEOMANIPULATOR_H

#include "../ivideomanipulator.h"

#include <opencv2/highgui/highgui.hpp>

namespace smle {

class OpenCvVideoManipulator final : public IVideoManipulator
{
public:
    explicit OpenCvVideoManipulator(const std::string & _filename);
    explicit OpenCvVideoManipulator(cv::VideoCapture * _cap);

    ~OpenCvVideoManipulator();

    // IVideoManipulator interface
public:
    virtual void nextFrame(FramePtr &_originalFrame, FramePtr &_nextFrame, EffectsPtr _effects) override;
    virtual int countFrame() override;
    virtual bool openVideo(const std::string &_filename) override;
    virtual bool isOpen() override;
    virtual void closeSafeVideo() override;
    virtual void setSafeVideo(const std::string &filename) override;
    FramePtr createEmptyFrame() override;

private:
    cv::VideoCapture * mCapture = nullptr;
    cv::VideoWriter * mWriter = nullptr;
};

} // namespace smle

#endif // SMLE_OPENCVVIDEOMANIPULATOR_H
