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

#ifndef LOGGER_H
#define LOGGER_H

// TODO: singleton

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace smle {

using std::string;

enum class LoggerLevel : int {
    High = 0,	// output messages, errors, warnings
    Average, 	// output errors, warnings
    Weak,		// output errors
    Off,		// disable output
};

class Logger final
{
private:
    Logger();

    Logger(const Logger & logger) = delete;

    std::string mLastMessage;
    std::ofstream mOut;

    static const std::string FILENAME;
    static const std::string WARR_PREFIX;
    static const std::string MESS_PREFIX;
    static const std::string ERR_PREFIX;

    template<class T>
    void write(std::string prefix, std::ostream & stream, T obj);

    LoggerLevel mLevel = LoggerLevel::High;

public:
    static Logger & instance();

    template <class T>
    Logger &operator<< (T obj);

    template <class T>
    void errorWrite(T obj);

    template <class T>
    void warningWrite(T obj);

    template <class T>
    void messageWrite(T obj);

    ~Logger();
    LoggerLevel getLevel() const;
    void setLevel(const LoggerLevel &value);

    inline const std::string & getLastMessage() const;
};

const std::string &Logger::getLastMessage() const
{
    return mLastMessage;
}

template <class T>
void Logger::write(std::string prefix, std::ostream & stream, T obj)
{
    if (mOut.is_open()) {
        mOut << prefix << ": " << obj << std::endl;
        std::stringstream ss;
        ss << prefix << ": " << obj << std::endl;
        mLastMessage = ss.str();
    }
#ifdef SMALLVE_DEBUG
    stream << prefix << ": " << obj << std::endl;
#endif
}


template <class T>
void Logger::messageWrite(T obj)
{
    if (mLevel <= LoggerLevel::High) {
        write(MESS_PREFIX, std::cout, obj);
    }
}

template <class T>
void Logger::warningWrite(T obj)
{
    if (mLevel <= LoggerLevel::Average ) {
        write(WARR_PREFIX, std::cout, obj);
    }
}

template <class T>
void Logger::errorWrite(T obj)
{
    if (mLevel <= LoggerLevel::Weak) {
        write(ERR_PREFIX, std::cout, obj);
    }
}

template<class T>
Logger &Logger::operator<<(T obj)
{
    this->messageWrite(obj);
    return *this;
}

} // namespace smle

#endif // LOGGER_H
