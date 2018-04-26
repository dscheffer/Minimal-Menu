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
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "KSMClient.hpp"
#include "QDBusConnectionWrapper.hpp"

#include <iostream>

using namespace testing;

namespace
{

class MockQDBusConnectionWrapper : public QDBusConnectionWrapper
{
public:
    MockQDBusConnectionWrapper() { };
    ~MockQDBusConnectionWrapper() { };

    MOCK_METHOD1(send, bool(const QDBusMessage message));
};

MATCHER_P(MessageMethod, p0, std::string(negation ? "Does not" : "Does") + " match " + PrintToString(p0))
{
    return arg.member() == p0;
}

MATCHER_P2(MessageMethod, p0, p1, std::string(negation ? "Does not" : "Does") + " match " + PrintToString(p0) + " with argument " + PrintToString(p1))
{
    return arg.member() == p0 && arg.arguments()[1] == p1;
}

/*
 * TESTS
 */
TEST(KSMClientTest, LogoutTest)
{
    KSMClient client;
    std::shared_ptr<MockQDBusConnectionWrapper> mock(new MockQDBusConnectionWrapper());
    EXPECT_CALL(*mock, send(MessageMethod("logout", 0))).Times(AtLeast(1));
    client.setConnection(mock);

    client.logout();
}

TEST(KSMClientTest, RebootTest)
{
    KSMClient client;
    std::shared_ptr<MockQDBusConnectionWrapper> mock(new MockQDBusConnectionWrapper());
    EXPECT_CALL(*mock, send(MessageMethod("logout", 1))).Times(AtLeast(1));
    client.setConnection(mock);

    client.reboot();
}

TEST(KSMClientTest, ShutdownTest)
{
    KSMClient client;
    std::shared_ptr<MockQDBusConnectionWrapper> mock(new MockQDBusConnectionWrapper());
    EXPECT_CALL(*mock, send(MessageMethod("logout", 2))).Times(AtLeast(1));
    client.setConnection(mock);

    client.shutdown();
}

TEST(KSMClientTest, SwitchUserTest)
{
    KSMClient client;
    std::shared_ptr<MockQDBusConnectionWrapper> mock(new MockQDBusConnectionWrapper());
    EXPECT_CALL(*mock, send(MessageMethod("openSwitchUserDialog"))).Times(AtLeast(1));
    client.setConnection(mock);

    client.switchUser();
}

}