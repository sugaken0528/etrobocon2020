#include "MotionSequencer.h"
#include <vector>

MotionSequencer::MotionSequencer(Controller& ctrler_, bool isLeftCource_)
  : ctrler(ctrler_),
    linear(ctrler_),
    tracer(ctrler_, ctrler_.getTargetBrightness(), isLeftCource_),
    yaw(ctrler_)
{
  stateMachine[0] = cb_cross2MidPoint;
  stateMachine[1] = cb_midPoint2Cross;
  stateMachine[2] = cb_yawing;
  stateMachine[3] = cb_linear;
  stateMachine[4] = cb_mid2Mid;
}

void MotionSequencer::cnvrtC8E2Motion(std::vector<std::vector<int>>& c8es_, Direction direct_) {}

void MotionSequencer::vectordiff(vector<vector<int>>& c8es_)
{
  // c8es_[n][n] = {{x0, y0}, {x1, y1}, ... , {xn, yn}}
  for(int i = 0; i <= c8es_.at(0).size(); i++) {  // 横の配列読み取り

    for(int j = 0; j <= c8es_.size(); j++) {  // 縦の配列読み取り

      MotionSequencer::y_diff.push_back(c8es_[i + 1][j] - c8es_[i][j]);
      MotionSequencer::x_diff.push_back(c8es_[j][i + 1] - c8es_[j][i]);
    }
  }
}

// 二点間の差分の座標から次に進む方向を返す

Direction MotionSequencer::vector2direction(std::vector<int> x_diff, std::vector<int> y_diff)
{
  Direction direct;

  for(int i = 0; i <= x_diff.size(); i++) {
    if(x_diff[i] == 0 && y_diff[i] == -1) direct = Direction::North;
    if(x_diff[i] == 1 && y_diff[i] == -1) direct = Direction::NEast;
    if(x_diff[i] == 1 && y_diff[i] == 0) direct = Direction::East;
    if(x_diff[i] == 1 && y_diff[i] == 1) direct = Direction::SEast;
    if(x_diff[i] == 0 && y_diff[i] == 1) direct = Direction::South;
    if(x_diff[i] == -1 && y_diff[i] == 1) direct = Direction::SWest;
    if(x_diff[i] == -1 && y_diff[i] == 0) direct = Direction::West;
    if(x_diff[i] == -1 && y_diff[i] == -1) direct = Direction::NWest;
  }

  return direct;  //東
}

// 方向から角度を出す関数(ひとつ前の方向をどう保持するか) むずかしいな。
Direction MotionSequencer::direction2angle(std::vector<int> x_diff, std::vector<int> y_diff,
                                           Direction direct_)  // 北
{
  // よくわかりません

  // int delta_direct;
  //  int pre_direct = vector2direction(x_diff, y_diff);

  // delta_direct = (int)direct_ - (int)pre_direct; //北　- 東
  // pre_direct = direct_ ; // 前の方向を北にする
  // direct_ = vector2direction(x_diff, y_diff); // 次に向かう位置に更新
}

// Rotatesion.cpp rotate関数の引数にprivateの角度を渡す
// LineTracer:: runとruntocolor
// MoveStraightの moveto　引数に距離または角度
// 後退もできる

void MotionSequencer::move(Scines scine_)
{
  // stateMachine[scine_]();
}

//
void MotionSequencer::cb_cross2MidPoint()
{
  // linear.moveWhileBW();
}

void MotionSequencer::cb_midPoint2Cross() {}

void MotionSequencer::cb_yawing() {}

void MotionSequencer::cb_linear() {}

void MotionSequencer::cb_mid2Mid() {}