#ifndef LFSRTEST_H
#define LFSRTEST_H

#include <QtTest/QtTest>


class LFSR16bitTest : public QObject
{
    Q_OBJECT
private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();



    void testLFSRInit();
    void testLFSRShift();
    void testResultMask();
};

#endif // LFSRTEST_H
