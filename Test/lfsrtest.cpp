#include "lfsrtest.h"
#include "linearfeedbackshiftregister.h"
#include "ps_utils.h"

void LFSR16bitTest::initTestCase()
{

}

void LFSR16bitTest::cleanupTestCase()
{

}

void LFSR16bitTest::init()
{

}

void LFSR16bitTest::cleanup()
{

}

void LFSR16bitTest::testLFSRInit()
{
    LinearFeedbackShiftRegister lfsr(16, 44257, FeedbackType::XOR, 45, 28672);

    QVERIFY(lfsr.getOutputSize() == 3);
    QVERIFY(lfsr.getMaxSequence() == 44257);
    QVERIFY(lfsr.getOutputValue() == 2);
    QVERIFY(lfsr.getRegisterSize() == 16);
}

void LFSR16bitTest::testLFSRShift()
{
    LinearFeedbackShiftRegister lfsr(16, 44257, FeedbackType::XOR, 45, 28672);

    lfsr.next();

    QVERIFY(lfsr.getOutputSize() == 3);
    QVERIFY(lfsr.getMaxSequence() == 22128);
    QVERIFY(lfsr.getOutputValue() == 5);
    QVERIFY(lfsr.getRegisterSize() == 16);

    lfsr.next();

    QVERIFY(lfsr.getOutputSize() == 3);
    QVERIFY(lfsr.getMaxSequence() == 43832);
    QVERIFY(lfsr.getOutputValue() == 2);
    QVERIFY(lfsr.getRegisterSize() == 16);

    lfsr.next();

    QVERIFY(lfsr.getOutputSize() == 3);
    QVERIFY(lfsr.getMaxSequence() == 21916);
    QVERIFY(lfsr.getOutputValue() == 5);
    QVERIFY(lfsr.getRegisterSize() == 16);
}

void LFSR16bitTest::testResultMask()
{
    //2,5,9,13
    LinearFeedbackShiftRegister lfsr(16, 44257, FeedbackType::XOR, 45, 18568);
    QVERIFY(lfsr.getOutputValue() == 6);
    QVERIFY(lfsr.getOutputSize() == 4);

    lfsr = LinearFeedbackShiftRegister(16, 44257, FeedbackType::XOR, 45, 44257);
    QVERIFY(lfsr.getOutputValue() == 255);
    QVERIFY(lfsr.getOutputSize() == 8);

    lfsr = LinearFeedbackShiftRegister(16, 44257, FeedbackType::XOR, 45, 21278);
    QVERIFY(lfsr.getOutputValue() == 0);
    QVERIFY(lfsr.getOutputSize() == 8);
}



QTEST_MAIN (LFSR16bitTest)
