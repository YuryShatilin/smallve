#ifndef SMALLVE_H
#define SMALLVE_H

#include <string>
#include <list>
#include <queue>

#include "ieffect.h"
#include "ivideomanipulator.h"
#include "effectmanager.h"

namespace smle {

class Smallve final
{
public:
    explicit Smallve(ManipulatorPtr _manipulator, EffectsPtr effects);

    Smallve() = delete;

    ~Smallve();

    FramePtr nextFrame();
    FramePtr getCurrentFrame() const;
    FramePtr getOriginalFrame() const;

    void applyFullVideo();

    ManipulatorPtr getManipulator();
    EffectsPtr getEffects();

private:
    FramePtr mCurrentFrame;
    FramePtr mOriginalFrame;

    ManipulatorPtr mManipulator;
    EffectsPtr mEffects;
};

} // namespace smle
#endif // SMALLVE_H
