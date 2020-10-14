#include "MotionSequencer.h"
#include <vector>

MotionSequencer::MotionSequencer(Controller& ctrler_, bool isLeftCource_)
  : ctrler(ctrler_),
    linear(ctrler_),
    tracer(ctrler_, ctrler_.getTargetBrightness(), isLeftCource_),
    yaw(ctrler_)
{
  // stateMachine[0] = cb_cross2MidPoint;
  // stateMachine[1] = cb_midPoint2Cross;
  // stateMachine[2] = cb_yawing;
  // stateMachine[3] = cb_linear;
  // stateMachine[4] = cb_mid2Mid;
}

void MotionSequencer::route2Motion(vector<vector<int>>& route, Direction direction)
{
  Direction currentDirection = direction;

  for(int i = 0; i < route.size() - 1; i++) {
    vector<int>& currentCoordinate = route[i];
    vector<int>& nextCoordinate = route[i + 1];
    Direction nextDirection = calcNextDirection(currentCoordinate, nextCoordinate);

    // 方向転換
    int rotationAngle = calcAngle(currentDirection, nextDirection);
    if(rotationAngle != 0) {
      yaw.rotate(abs(rotationAngle), rotationAngle > 0);
    }

    // 移動
    CoordinateType currentType = getCoordinateType(currentCoordinate);
    CoordinateType nextType = getCoordinateType(nextCoordinate);
    if(currentType == CoordinateType::crossCircle && nextType == CoordinateType::middlePoint) {
    } else if(currentType == CoordinateType::middlePoint
              && nextType == CoordinateType::crossCircle) {
    } else if(currentType == CoordinateType::middlePoint
              && nextType == CoordinateType::middlePoint) {
    } else if(currentType == CoordinateType::middlePoint
              && nextType == CoordinateType::blockCircle) {
    }

    currentDirection = nextDirection;
  }
}

Direction MotionSequencer::calcNextDirection(vector<int>& currentCoordinate,
                                             vector<int>& nextCoordinate)
{
  int xDiff = nextCoordinate[0] - currentCoordinate[0];
  int yDiff = nextCoordinate[1] - currentCoordinate[1];

  if(xDiff == 0 && yDiff == -1) {
    return Direction::North;
  } else if(xDiff == 1 && yDiff == -1) {
    return Direction::NEast;
  } else if(xDiff == 1 && yDiff == 0) {
    return Direction::East;
  } else if(xDiff == 1 && yDiff == 1) {
    return Direction::SEast;
  } else if(xDiff == 0 && yDiff == 1) {
    return Direction::South;
  } else if(xDiff == -1 && yDiff == 1) {
    return Direction::SWest;
  } else if(xDiff == -1 && yDiff == 0) {
    return Direction::West;
  } else {
    return Direction::NWest;
  }
}

int MotionSequencer::calcAngle(Direction currentDirection, Direction nextDirection)
{
  int angle = static_cast<int>(nextDirection) - static_cast<int>(currentDirection);
  printf("%d %d %d\n", nextDirection, currentDirection, angle);
  if(angle > 4) {
    angle -= 8;
  } else if(angle < -4) {
    angle += 8;
  }

  return angle * 45;
}

CoordinateType MotionSequencer::getCoordinateType(vector<int>& coordinate)
{
  bool isXOdd = coordinate[0] % 2;
  bool isYOdd = coordinate[1] % 2;

  if(isXOdd && isYOdd) {
    return CoordinateType::blockCircle;
  } else if(!isXOdd && !isYOdd) {
    return CoordinateType::crossCircle;
  } else {
    return CoordinateType::middlePoint;
  }
}

// // 方向から角度を出す関数(ひとつ前の方向をどう保持するか) むずかしいな。
// Direction MotionSequencer::direction2angle(std::vector<int> x_diff, std::vector<int> y_diff,
//                                            Direction direct_)  // 北
// {
//   // よくわかりません

//   // int delta_direct;
//   //  int pre_direct = vector2direction(x_diff, y_diff);

//   // delta_direct = (int)direct_ - (int)pre_direct; //北　- 東
//   // pre_direct = direct_ ; // 前の方向を北にする
//   // direct_ = vector2direction(x_diff, y_diff); // 次に向かう位置に更新
// }

// // Rotatesion.cpp rotate関数の引数にprivateの角度を渡す
// // LineTracer:: runとruntocolor
// // MoveStraightの moveto　引数に距離または角度
// // 後退もできる

// void MotionSequencer::move(Scines scine_)
// {
//   // stateMachine[scine_]();
// }

// //
// void MotionSequencer::cb_cross2MidPoint()
// {
//   // linear.moveWhileBW();
// }

// void MotionSequencer::cb_midPoint2Cross() {}

// void MotionSequencer::cb_yawing() {}

// void MotionSequencer::cb_linear() {}

// void MotionSequencer::cb_mid2Mid() {}