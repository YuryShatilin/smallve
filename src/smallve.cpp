#include "include/smallve.h"

#include "include/tools/logger.h"
#include "include/ieffect.h"

#include <assert.h>
#include <iostream>

namespace smle {

Smallve::Smallve(ManipulatorPtr _manipulator, EffectsPtr effects)
{
    mManipulator = _manipulator;
    mEffects = effects;
}

Smallve::~Smallve()
{
//    delete mCapture;
//    if (mVideoSafed) {
//        saveVideo();
//    }

//    while (!mCacheFrames.empty()) {
//        mCacheFrames.pop();
//    }

//    delete mVideoWriter;
}

FramePtr Smallve::nextFrame()
{
    Logger::instance().messageWrite("Read next frame");
    mManipulator->nextFrame(mOriginalFrame, mCurrentFrame, mEffects);
    return mCurrentFrame;
}

FramePtr Smallve::getCurrentFrame() const
{
    return mCurrentFrame;
}

FramePtr Smallve::getOriginalFrame() const
{
    return mOriginalFrame;
}

//void Smallve::setVideoSafed(const std::string &_name)
//{
//    if (mCapture == nullptr) {
//        Logger::instance().warningWrite("Not save video");
//        return;
//    }

//    Logger::instance().messageWrite(std::string("Begin write video: ") + _name);

//    mVideoSafed = true;
//    mVideoName = _name;
//    cv::Size size = cv::Size((int)mCapture->get(CV_CAP_PROP_FRAME_WIDTH),
//                  (int)mCapture->get(CV_CAP_PROP_FRAME_HEIGHT));

//    double fps = mCapture->get(CV_CAP_PROP_FPS);
//    int fourcc = mCapture->get(CV_CAP_PROP_FOURCC);
//    try {
//        mVideoWriter = new VideoWriter(mVideoName, fourcc, fps, size, true);
//        if (!mVideoWriter->isOpened()){
//            Logger::instance().errorWrite("Smallve::setVideoSafed : videowriter can not open");
//            delete mVideoWriter;
//            mVideoSafed = false;
//        }
//    } catch (cv::Exception & ex) {
//        Logger::instance().errorWrite("cv::Exception " + ex.msg);
//        mVideoSafed = false;
//        delete mVideoWriter;
//    }
//}

//void Smallve::saveVideo()
//{
//    if (mVideoWriter == nullptr) {
//        Logger::instance().warningWrite("video can't save");
//        return;
//    }

//    try {
//        Logger::instance().messageWrite("Save video " + mVideoName);
//        mVideoWriter->release();
//    } catch (cv::Exception & ex) {
//        Logger::instance().errorWrite("cv::Exception " + ex.msg);
//    }

//    delete mVideoWriter;
//    mVideoWriter = nullptr;
//    mVideoSafed = false;
//}


//bool Smallve::isVideoSafed()
//{
//    return mVideoSafed;
//}

//bool Smallve::isOpenedCapture()
//{
//    return mCapture != nullptr;
//}

//bool Smallve::open(const std::string &_filename)
//{
//    mCapture = new cv::VideoCapture(_filename);
//    readNextFrame();
//    if (!mCapture->isOpened()) {
//        Logger::instance().errorWrite("Capture is not open");
//        Logger::instance().errorWrite("Filename - " + _filename);
//        delete mCapture;
//        return false;
//    }
//    return true;
//}

//void Smallve::applyFilters()
//{
//    for (auto & effect : mEffects) {
//        Logger::instance().messageWrite("Apply " + effect->name());
//        mCurrentFrame = effect->apply(mCurrentFrame);
//    }
//}

//void Smallve::readNextFrame()
//{
//    assert(mCapture != nullptr);
//    MatPtr buff(new cv::Mat());

//    *mCapture >> *buff;
//    mCacheFrames.push(buff);
//}

void Smallve::applyFullVideo() {
    Logger::instance().messageWrite("Apply for full video");
//    readNextFrame();
    int count = mManipulator->countFrame();
    int cur_frame = 0;
    for (;;) {
        nextFrame();
        if (mCurrentFrame->isEmpty()) {
            break;
        }

        Logger::instance().messageWrite(std::string("Frame ") +
                                        std::to_string(cur_frame) + ": "
                                        + std::to_string(count));
        cur_frame += 1;
    }
}

ManipulatorPtr Smallve::getManipulator()
{
    return mManipulator;
}

EffectsPtr Smallve::getEffects()
{
    return mEffects;
}

} // namespace smle
