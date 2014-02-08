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

#ifndef SMVE_EFFECTMOSAIC_H
#define SMVE_EFFECTMOSAIC_H

#include "ieffect.h"

namespace smle {

class EffectMosaic : public IEffect
{
public:
    EffectMosaic(int _mosaicSize = 6);

    virtual MatPtr apply(const MatPtr &src) override;
    virtual std::string name() override;
    ~EffectMosaic() = default;
private:
    const int mMosaicSize;

    cv::Scalar AverageColor(const IplImage *img, int row, int col);
    void SetColor(IplImage *img, int col, int row, int r, int g, int b);
};

} // namespace smle

#endif // SMVE_EFFECTMOSAIC_H
