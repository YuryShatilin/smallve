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

#include "include/tools/logger.h"

namespace smle {

using std::string;

const string Logger::FILENAME = "smallve.log";
const string Logger::WARR_PREFIX = "[W]";
const string Logger::ERR_PREFIX = "[E]";
const string Logger::MESS_PREFIX = "[M]";

Logger::Logger()
{
    mOut.open("smallve.log");
#ifdef SMALLVE_DEBUG
    setLevel(LoggerLevel::High);
#endif
}

LoggerLevel Logger::getLevel() const
{
    return mLevel;
}

void Logger::setLevel(const LoggerLevel &value)
{
#ifndef SMALLVE_DEBUG
    mLevel = value;
#else
    this->errorWrite("in debug level always equals hight");
#endif
}


Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::~Logger()
{
    if (mOut.is_open()) {
        mOut.close();
    }
}

}// namespace smlv

