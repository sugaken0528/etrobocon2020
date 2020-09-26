/**
 *  @file   RouteCalculatorTest.cpp
 *  @brief  RouteCalculatorクラスのテストファイル
 *  @author mutotaka0426, sugaken0528
 */
#include "RouteCalculator.h"
#include <gtest/gtest.h>

using namespace std;

namespace etrobocon2020_test {
  TEST(RouteCalculator, solveBlockBingoData)
  {
    Controller controller;
    bool isLeftCourse = true;
    BlockBingoData blockBingoData(controller, isLeftCourse);
    RouteCalculator routeCalculator(blockBingoData);
    vector<vector<int>> actualList;
    int AREASIZE = 7;
    int actualDiffX, actualDiffY;
    int expectedSX, expectedSY, expectedGX, expectedGY;
    int goalPoint;

    blockBingoData.initBlockBingoData();

    for(expectedSX = 0; expectedSX < AREASIZE; expectedSX++) {
      for(expectedSY = 0; expectedSY < AREASIZE; expectedSY++) {
        for(expectedGX = 0; expectedGX < AREASIZE; expectedGX++) {
          for(expectedGY = 0; expectedGY < AREASIZE; expectedGY++) {
            routeCalculator.solveBlockBingo(actualList, expectedSX, expectedSY, expectedGX,
                                            expectedGY);
            // スタートとゴールが指定されたものか
            goalPoint = (int)actualList.size() - 1;
            ASSERT_EQ(expectedSX, actualList[0][0]);
            ASSERT_EQ(expectedSY, actualList[0][1]);
            ASSERT_EQ(expectedGX, actualList[goalPoint][0]);
            ASSERT_EQ(expectedGY, actualList[goalPoint][1]);
            // 座標が隣り合っているか
            for(int i = 1; i < (int)actualList.size(); i++) {
              actualDiffX = abs(actualList[i - 1][0] - actualList[i][0]);
              actualDiffY = abs(actualList[i - 1][1] - actualList[i][1]);
              ASSERT_TRUE(actualDiffX == 0 || actualDiffX == 1)
                  << "actualList[" << i << "]'-actualDiffX=" << actualDiffX;
              ASSERT_TRUE(actualDiffY == 0 || actualDiffY == 1)
                  << "actualList[" << i << "]'-actualDiffY=" << actualDiffY;
              ASSERT_FALSE(actualDiffX == 0 && actualDiffY == 0);
            }
          }
        }
      }
    }

    //(2,6)のブロックと(4,4)のブロックを設置して(0,6)に行くまでの経路をテスト
  }
}  // namespace etrobocon2020_test
