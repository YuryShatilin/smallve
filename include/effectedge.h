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

#ifndef EFFECTEDGE_H
#define EFFECTEDGE_H

#include "ieffect.h"

namespace smle {
// Effect detect edge on image
// Using Canny filter

class EffectEdge : public IEffect
{
public:
    EffectEdge(double _threshold1 = 50.0, double _threshold2 = 200.0, int _apertureSize = 3,
               bool _l2gradient = false);

    virtual ~EffectEdge();

public:
    virtual MatPtr apply(const MatPtr &src) override;
    virtual std::string name() override;

private:
    const double mThreshold1;
    const double mThreshold2;
    const int mApertureSize;
    const bool mL2Gradient;
};

} // namespace smle
#endif // EFFECTEDGE_H
