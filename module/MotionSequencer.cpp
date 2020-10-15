#include "MotionSequencer.h"

MotionSequencer::MotionSequencer(Controller& controller_, bool isLeftCource_,
                                 BlockBingoData blockBingoData_)
  : controller(controller_),
    isLeftCourse(isLeftCource_),
    blockBingoData(blockBingoData_),
    moveStraight(controller_),
    lineTracer(controller_, controller_.getTargetBrightness(), isLeftCource_),
    rotation(controller_)
{
}

void MotionSequencer::route2Motion(vector<Coordinate>& route)
{
  Coordinate& currentCoordinate = route.front();
  Direction currentDirection = blockBingoData.getDirection();

  for(int i = 1; i < route.size(); i++) {
    Coordinate& nextCoordinate = route[i];
    Direction nextDirection = blockBingoData.calcNextDirection(currentCoordinate, nextCoordinate);

    printf("(%d,%d) -> (%d,%d) 現在方位:%d\n", currentCoordinate.x, currentCoordinate.y,
           nextCoordinate.x, nextCoordinate.y, currentDirection);

    // 方向転換
    int rotationAngle = calcRotationAngle(currentDirection, nextDirection);
    if(rotationAngle != 0) {
      // rotation.rotate(abs(rotationAngle), rotationAngle > 0);
      printf("方向転換%d°\n", rotationAngle);
    }

    // 移動
    NodeType currentType = blockBingoData.checkNode(currentCoordinate);
    NodeType nextType = blockBingoData.checkNode(nextCoordinate);
    if(currentType == NodeType::crossCircle && nextType == NodeType::middlePoint) {
      // 交点サークルから中点への移動
      // lineTracer.run({ 175, 30, 0.0, { 0.1, 0.005, 0.01 } });
      printf("交点サークルから中点への移動\n");

    } else if(currentType == NodeType::crossCircle && nextType == NodeType::blockCircle) {
      // 交点サークルからブロックサークルへの移動
      // moveStraight.moveTo(186.7);
      printf("交点サークルからブロックサークルへの移動\n");
      if(i == route.size() - 1
         && blockBingoData.getBlockCircle(nextCoordinate).block.blockColor == Color::none) {
        // ブロックサークルにブロックを設置する場合
        // moveStraight.moveTo(-186.7);
        printf("ブロックサークルから交点サークルへ戻る\n");
      }

    } else if(currentType == NodeType::middlePoint && nextType == NodeType::crossCircle) {
      // 中点から交点サークルへの移動
      // lineTracer.runToColor(30, 0.1, 0.005, 0.01, 0.0);
      // moveStraight.moveTo(110);
      printf("中点から交点サークルへの移動\n");

    } else if(currentType == NodeType::middlePoint && nextType == NodeType::middlePoint) {
      // 中点から中点への移動
      // moveStraight.moveTo(247.48);
      printf("中点から中点への移動\n");

    } else if(currentType == NodeType::middlePoint && nextType == NodeType::blockCircle) {
      // 中点からブロックサークルへの移動
      // moveStraight.moveTo(145);
      printf("中点からブロックサークルへの移動\n");
      if(i == route.size() - 1
         && blockBingoData.getBlockCircle(nextCoordinate).block.blockColor == Color::none) {
        // ブロックサークルにブロックを設置する場合
        // moveStraight.moveTo(-145);
        printf("ブロックサークルから中点へ戻る\n");
      }

    } else if(currentType == NodeType::blockCircle && nextType == NodeType::crossCircle) {
      // ブロックサークルから交点サークルへの移動
      // moveStraight.moveTo(186.7);
      printf("ブロックサークルから交点サークルへの移動\n");

    } else if(currentType == NodeType::blockCircle && nextType == NodeType::middlePoint) {
      // ブロックサークルから中点への移動
      // moveStraight.moveTo(145);
      printf("ブロックサークルから中点への移動\n");
    }

    currentCoordinate = nextCoordinate;
    currentDirection = nextDirection;
  }
}

int MotionSequencer::calcRotationAngle(Direction currentDirection, Direction nextDirection)
{
  int angle = static_cast<int>(nextDirection) - static_cast<int>(currentDirection);

  if(angle > 4) {
    angle -= 8;
  } else if(angle < -4) {
    angle += 8;
  }

  return angle * 45;
}