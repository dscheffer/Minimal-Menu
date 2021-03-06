/*
 *   Copyright (c) 2018 Dennis Scheffer.
 *
 *   This file is part of Minimal Menu.
 *
 *   Minimal Menu is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Minimal Menu is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Minimal Menu.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "RecentlyUsedHandler.hpp"

using namespace testing;

namespace
{

/*
 * TESTS
 */
TEST(RecentDocumentHandlerTest, GetRecentlyUsedApplications)
{
    RecentlyUsedHandler handler;
    handler.update();

    QQmlListProperty<ActivityEntry> result = handler.getRecentlyUsedApplications();
    int count = result.count(&result);
    EXPECT_EQ(handler.recentlyUsedCount, count);
}

TEST(RecentDocumentHandlerTest, GetRecentlyUsedDocuments)
{
    RecentlyUsedHandler handler;
    handler.update();

    QQmlListProperty<ActivityEntry> result = handler.getRecentlyUsedDocuments();
    int count = result.count(&result);
    EXPECT_EQ(handler.recentlyUsedCount, count);
}

}