#ifndef SMALLVE_H
#define SMALLVE_H

#include <string>
#include <list>
#include <memory>
#include <queue>

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "ieffect.h"

namespace smle {

// TODO: replicate effect
// filters effect
// crop effect
// Composite effect
// Mememnto Pattern ?
// Save previous mats in some effects
// Maybe save original frames
// Properties in Smallve
//

class Smallve final
{
public:
    Smallve(const std::string & _filename);
    Smallve() = default;

    virtual ~Smallve();

    MatPtr nextFrame();
    MatPtr getCurrentFrame() const;

    void addEffect(IEffect * _effect);
    void removeEffect(IEffect * _effect);
    inline const std::list<IEffect*> & getEffects();

    void applyFullVideo();

    void setVideoSafed(const std::string & _name);
    void saveVideo();

    bool isVideoSafed();
    bool isOpenedCapture();

    bool open(const std::string & _filename);
private:
    cv::VideoCapture * mCapture = nullptr;

    MatPtr mCurrentFrame;

    std::list<IEffect*> mEffects;
    std::queue<MatPtr> mCacheFrames;

    bool mVideoSafed = false;

    cv::VideoWriter * mVideoWriter = nullptr;
    std::string mVideoName = "smallve.avi";

    void applyFilters();
    void readNextFrame();
};

const std::list<IEffect *> &Smallve::getEffects()
{
    return mEffects;
}

} // namespace smle
#endif // SMALLVE_H
