#include "HopScotch.h"
#include <vector>

HopScotch::HopScotch(Controller& ctrler_, MoveStraight& linear_, LineTracer& tracer_, Rotation& yaw_)
: ctrler(ctrler_), linear(linear_), tracer(tracer_), yaw(yaw_)
{
  
}

void HopScotch::cnvrtC8E2Motion(std::vector<std::vector<int>>& c8es_, Direction direct_)
{
 
}

void HopScotch::vectordiff(vector<vector<int>> & c8es_)
{
    // c8es_[n][n] = {{x0, y0}, {x1, y1}, ... , {xn, yn}}    
    for(int i = 0; i <= c8es_.at(0).size(); i++) {  // 横の配列読み取り


        for(int j = 0; j <= c8es_.size(); j++) {      // 縦の配列読み取り

            HopScotch::y_diff.push_back(c8es_[i+1][j] - c8es_[i][j]);
            HopScotch::x_diff.push_back(c8es_[j][i+1] - c8es_[j][i]);
        }
    }
}

// Rotatesion.cpp rotate関数の引数にprivateの角度を渡す

// LineTracer:: runとruntocolor


// MoveStraightの moveto　引数に距離または角度
// 後退もできる


void HopScotch::state()
{
  static void (HopScotch::*stateMachine[])() = {
    &HopScotch::cb_crossToMidPoint,
    cb_midPointToCross,
    cb_yawing,
    cb_linear,
    cb_midToMid
  };


}
