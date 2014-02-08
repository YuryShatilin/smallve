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


class Smallve final
{
public:
    Smallve(const std::string & _filename);
    Smallve(int _device);
    Smallve(cv::VideoCapture * cap);

    virtual ~Smallve();

    MatPtr nextFrame();
    MatPtr getCurrentFrame() const;

    void addEffect(IEffect * _effect);
    void removeEffect(IEffect * _effect);
    inline const std::list<IEffect*> & getEffects();

    void applyFullVideo();

    void setVideoSafed(const std::string & _name, int _foucrr);
    void saveVideo();
    void cancelVideoSafed();

    bool isVideoSafed();

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
