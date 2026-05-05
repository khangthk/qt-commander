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

#ifndef COMPARE_H
#define COMPARE_H

#include <QFileInfo>

class Compare
{
public:
    Compare() = delete;

    /// Enumeration to indicate relative sort order of left and right tree
    /// entries.
    enum class Order
    {
        LeftIsFirst,
        Same,
        RightIsFirst
    };

    static Order compare(const QFileInfo& left, const QFileInfo& right);

    enum class Content
    {
        Identical,
        Different,
        Unknown
    };

    /// Compares the contents of two files.
    static Content contents(const QFileInfo& left, const QFileInfo& right);
};

#endif // COMPARE_H
