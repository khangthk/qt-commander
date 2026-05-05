/*
 -------------------------------------------------------------------------------
    This file is part of the Qt Commander file manager.
    Copyright (C) 2026  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include "compare.h"
#include <algorithm>
#include <fstream>

Compare::Order Compare::compare(const QFileInfo &left, const QFileInfo &right)
{
    if (left.isDir() != right.isDir())
    {
        return left.isDir() ? Order::LeftIsFirst : Order::RightIsFirst;
    }

    const int cmp = left.fileName().compare(right.fileName());
    if (cmp < 0)
    {
        return Order::LeftIsFirst;
    }
    if (cmp == 0)
    {
        return Order::Same;
    }
    // cmp > 0
    return Order::RightIsFirst;
}

Compare::Content Compare::contents(const QFileInfo &left, const QFileInfo &right)
{
    std::ifstream streamLeft(left.filesystemAbsoluteFilePath(),
                             std::ios_base::binary | std::ios_base::ate);
    if (streamLeft.fail())
    {
        return Content::Unknown;
    }
    std::ifstream streamRight(right.filesystemAbsoluteFilePath(),
                              std::ios_base::binary | std::ios_base::ate);
    if (streamRight.fail())
    {
        streamLeft.close();
        return Content::Unknown;
    }

    // Check for same size.
    if (streamLeft.tellg() != streamRight.tellg()) {
        return Content::Different;
    }

    streamLeft.seekg(0, std::ifstream::beg);
    streamRight.seekg(0, std::ifstream::beg);

    return std::equal(std::istreambuf_iterator<char>(streamLeft.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(streamRight.rdbuf()))
        ? Content::Identical : Content::Different;
}
