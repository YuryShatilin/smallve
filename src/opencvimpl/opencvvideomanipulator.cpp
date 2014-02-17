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

#include "include/opencvimpl/opencvvideomanipulator.h"

#include "include/opencvimpl/opencvframe.h"
#include "include/tools/logger.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace smle {

OpenCvVideoManipulator::OpenCvVideoManipulator(const std::string &_filename)
{
    this->openVideo(_filename);
}

OpenCvVideoManipulator::~OpenCvVideoManipulator()
{
    if (mCapture != nullptr) {
        mCapture->release();
    }

    if (mWriter != nullptr) {
        mWriter->release();
    }

    delete mCapture;
}

void OpenCvVideoManipulator::nextFrame(FramePtr &_originalFrame, FramePtr &_nextFrame, EffectsPtr _effects)
{
    if (mCapture == nullptr) {
        // TODO: log
        return;
    }
    Logger::instance().messageWrite("OpenCvVideoManipulator read frame");
    cv::Mat buff;
    mCapture->read(buff);
    _originalFrame = FramePtr(new OpenCvFrame(buff));

    cv::Mat nextBuff = buff.clone();
    auto frame = new OpenCvFrame(nextBuff);
    _nextFrame = FramePtr(frame);

    _effects->apply(_nextFrame);

    if (mWriter != nullptr) {
        int w = mCapture->get(CV_CAP_PROP_FRAME_WIDTH);
        int h = mCapture->get(CV_CAP_PROP_FRAME_HEIGHT);
//        cv::resize(nextBuff, nextBuff, cv::Size(w,h));
        mWriter->write(frame->getCvMat());
    }

    Logger::instance().messageWrite("OpenCvVideoManipulator readed frame");
}

int OpenCvVideoManipulator::countFrame()
{
    if (mCapture == nullptr) {
        // TODO: log
        return -1;
    }

    return mCapture->get(CV_CAP_PROP_FRAME_COUNT);
}

bool OpenCvVideoManipulator::openVideo(const std::string &_filename)
{
    if (mCapture != nullptr) {
        // TODO: log
        mCapture->release();
        delete mCapture;
    }

    mCapture = new cv::VideoCapture(_filename);
    if (!mCapture->isOpened()) {
        Logger::instance().errorWrite("OpenCvVideoManipulator() - can't not open video "
                                      + _filename);
        delete mCapture;
    }
}

bool OpenCvVideoManipulator::isOpen()
{
    return mCapture != nullptr;
}

void OpenCvVideoManipulator::closeSafeVideo()
{
    if (mWriter == nullptr) {
        // TODO: log
        return;
    }

    mWriter->release();
    delete mWriter;
    mWriter = nullptr;
}

void OpenCvVideoManipulator::setSafeVideo(const std::string &filename)
{
    if (mWriter != nullptr) {
        // TODO: log
        mWriter->release();
        delete mWriter;
    }

    if (mCapture == nullptr) {
        // TODO: log
        return;
    }

    mWriter = new cv::VideoWriter();
    mWriter->open(filename,
                  mCapture->get(CV_CAP_PROP_FOURCC),
                  mCapture->get(CV_CAP_PROP_FPS),
                  cv::Size(mCapture->get((CV_CAP_PROP_FRAME_WIDTH)),
                           mCapture->get((CV_CAP_PROP_FRAME_HEIGHT))),
                  true);
    if (!mWriter->isOpened()) {
        // TODO: log
        closeSafeVideo();
    }
}

FramePtr OpenCvVideoManipulator::createEmptyFrame()
{
    static cv::Mat mat;
    return FramePtr(new OpenCvFrame(mat.clone()));
}

} // namespace smle

