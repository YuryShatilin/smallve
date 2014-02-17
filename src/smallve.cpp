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
