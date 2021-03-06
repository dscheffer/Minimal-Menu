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

#include "ApplicationLauncher.hpp"
#include "QProcessWrapper.hpp"

using namespace testing;

namespace
{

class MockQProcessWrapper : public QProcessWrapper
{
public:
    MockQProcessWrapper() { };
    ~MockQProcessWrapper() { };

    MOCK_METHOD0(readAllStandardError, QByteArray());
    MOCK_METHOD0(readAllStandardOutput, QByteArray());
    MOCK_METHOD2(start, void(const QString &program, const QStringList &arguments));
    MOCK_METHOD1(startDetached, bool(const QString &program));
    MOCK_METHOD2(startDetached, bool(const QString &program, const QStringList &arguments));
    MOCK_METHOD0(waitForFinished, bool());
    MOCK_METHOD0(close, void());
};


/*
 * TESTS
 */
TEST(ApplicationLauncherTest, LaunchTest)
{
    ApplicationLauncher launcher;
    std::shared_ptr<MockQProcessWrapper> process(new MockQProcessWrapper());
    EXPECT_CALL(*process, startDetached(QString("A"))).Times(AtLeast(1));
    EXPECT_CALL(*process, close()).Times(AtLeast(1));
    launcher.setProcess(std::shared_ptr<QProcessWrapper>(process));

    launcher.launch("A");
}

TEST(ApplicationLauncherTest, UsernameFound)
{
    ApplicationLauncher launcher;
    std::shared_ptr<MockQProcessWrapper> process(new MockQProcessWrapper());
    ON_CALL(*process, readAllStandardOutput())
    .WillByDefault(Return("username"));
    EXPECT_CALL(*process, start(_, _)).Times(AtLeast(1));
    EXPECT_CALL(*process, waitForFinished()).Times(AtLeast(1));
    launcher.setProcess(process);

    QString username = launcher.getUsername();

    ASSERT_EQ(std::string("username"), username.toStdString());
}

TEST(ApplicationLauncherTest, UpdateCountNonZero)
{
    ApplicationLauncher launcher;
    std::shared_ptr<MockQProcessWrapper> process(new MockQProcessWrapper());
    ON_CALL(*process, readAllStandardError())
    .WillByDefault(Return("222;2"));
    launcher.setProcess(process);

    int count = launcher.getUpdateCount();

    ASSERT_EQ(222, count);
}

TEST(ApplicationLauncherTest, UpdateCountEmpty)
{
    ApplicationLauncher launcher;
    std::shared_ptr<MockQProcessWrapper> process(new MockQProcessWrapper());
    ON_CALL(*process, readAllStandardError())
    .WillByDefault(Return(""));
    launcher.setProcess(process);

    int count = launcher.getUpdateCount();

    ASSERT_EQ(-1, count);
}

TEST(ApplicationLauncherTest, UpdateCountInvalid)
{
    ApplicationLauncher launcher;
    std::shared_ptr<MockQProcessWrapper> process(new MockQProcessWrapper());
    ON_CALL(*process, readAllStandardError())
    .WillByDefault(Return("ABCDEF"));
    launcher.setProcess(process);

    int count = launcher.getUpdateCount();

    ASSERT_EQ(-1, count);
}

TEST(ApplicationLauncherTest, UpdateCountAptCheckUnavailable)
{
    ApplicationLauncher launcher;
    launcher.setAptCheck("AAAAA");

    int count = launcher.getUpdateCount();

    ASSERT_EQ(0, count);
}

}