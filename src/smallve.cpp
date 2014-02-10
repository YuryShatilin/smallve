#include "include/smallve.h"

#include "include/tools/logger.h"
#include "include/ieffect.h"

#include <assert.h>
#include <iostream>
#include <opencv/cv.h>

using namespace cv;

namespace smle {

Smallve::Smallve(const std::string &_filename)
{
    open(_filename);
}

Smallve::~Smallve()
{
    delete mCapture;
    if (mVideoSafed) {
        saveVideo();
    }

    while (!mCacheFrames.empty()) {
        mCacheFrames.pop();
    }

    delete mVideoWriter;
}

MatPtr Smallve::nextFrame()
{
    assert (mCapture != nullptr);

    if (mCacheFrames.empty()) {
        readNextFrame();
    }

    mCurrentFrame = mCacheFrames.front();
    mCacheFrames.pop();

    if (!mCurrentFrame->empty()) {
        applyFilters();

        if (mVideoSafed) {
            Logger::instance().messageWrite("write frame in " + mVideoName);
            mVideoWriter->write(*mCurrentFrame);
        }
    }

    return mCurrentFrame;
}

MatPtr Smallve::getCurrentFrame() const
{
    return mCurrentFrame;
}

void Smallve::addEffect(IEffect *_effect)
{
    Logger::instance().messageWrite("Add effect: " + _effect->name());
    mEffects.push_back(_effect);
}

void Smallve::removeEffect(IEffect *_effect)
{
    Logger::instance().messageWrite("Remove effect: " + _effect->name());
    mEffects.remove(_effect);
}

void Smallve::setVideoSafed(const std::string &_name)
{
    if (mCapture == nullptr) {
        Logger::instance().warningWrite("Not save video");
        return;
    }

    Logger::instance().messageWrite(std::string("Begin write video: ") + _name);

    mVideoSafed = true;
    mVideoName = _name;
    cv::Size size = cv::Size((int)mCapture->get(CV_CAP_PROP_FRAME_WIDTH),
                  (int)mCapture->get(CV_CAP_PROP_FRAME_HEIGHT));

    double fps = mCapture->get(CV_CAP_PROP_FPS);
    int fourcc = mCapture->get(CV_CAP_PROP_FOURCC);
    try {
        mVideoWriter = new VideoWriter(mVideoName, fourcc, fps, size, true);
        if (!mVideoWriter->isOpened()){
            Logger::instance().errorWrite("Smallve::setVideoSafed : videowriter can not open");
            delete mVideoWriter;
            mVideoSafed = false;
        }
    } catch (cv::Exception & ex) {
        Logger::instance().errorWrite("cv::Exception " + ex.msg);
        mVideoSafed = false;
        delete mVideoWriter;
    }
}

void Smallve::saveVideo()
{
    if (mVideoWriter == nullptr) {
        Logger::instance().warningWrite("video can't save");
        return;
    }

    try {
        Logger::instance().messageWrite("Save video " + mVideoName);
        mVideoWriter->release();
    } catch (cv::Exception & ex) {
        Logger::instance().errorWrite("cv::Exception " + ex.msg);
    }

    delete mVideoWriter;
    mVideoWriter = nullptr;
    mVideoSafed = false;
}


bool Smallve::isVideoSafed()
{
    return mVideoSafed;
}

bool Smallve::isOpenedCapture()
{
    return mCapture != nullptr;
}

bool Smallve::open(const std::string &_filename)
{
    mCapture = new cv::VideoCapture(_filename);
    readNextFrame();
    if (!mCapture->isOpened()) {
        Logger::instance().errorWrite("Capture is not open");
        Logger::instance().errorWrite("Filename - " + _filename);
        delete mCapture;
        return false;
    }
    return true;
}

void Smallve::applyFilters()
{
    for (auto & effect : mEffects) {
        Logger::instance().messageWrite("Apply " + effect->name());
        mCurrentFrame = effect->apply(mCurrentFrame);
    }
}

void Smallve::readNextFrame()
{
    assert(mCapture != nullptr);
    MatPtr buff(new cv::Mat());

    *mCapture >> *buff;
    mCacheFrames.push(buff);
}

void Smallve::applyFullVideo() {
    int count = 0;
    while (!mCurrentFrame->empty()) {
        Logger::instance().messageWrite("");
        applyFilters();
        nextFrame();
        count += 1;
    }
    Logger::instance().messageWrite(std::string("count frames: " + count));
}

} // namespace smle
