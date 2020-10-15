/**
 * @file MotionSequencer.h
 * @brief 座標情報を機動に変換するクラス
 * @author T.Yoshino(Mikoyaan), D.Hirayama(Kanikama)
 **/

#ifndef MOTIONSEQUENCER_H
#define MOTIONSEQUENCER_H

#include <vector>
#include "Controller.h"
#include "MoveStraight.h"
#include "LineTracer.h"
#include "Rotation.h"
#include "BlockBingoData.h"

using namespace std;

enum class BingoMotion {
  turn,      // 方向転換
  c2m,       // 交点サークルから中点への移動
  m2c,       // 中点から交点サークルへの移動
  m2m,       // 中点から中点への移動
  getBlock,  // ブロックサークルのブロック取得
  setBlock,  // ブロックサークルにブロック設置
};

class MotionSequencer {
 public:
  /** コンストラクタ
   * @param　controller_
   * @param isLeftCourse
   **/
  MotionSequencer(Controller& controller_, bool isLeftCource_, BlockBingoData blockBingoData_);

  /** 経路->動作変換
   * @param route_ 経路
   **/
  void route2Motion(vector<Coordinate>& route_);

 private:
  Controller& controller;
  bool isLeftCourse;
  BlockBingoData blockBingoData;
  MoveStraight moveStraight;
  LineTracer lineTracer;
  Rotation rotation;

  int calcRotationAngle(Direction currentDirection, Direction nextDirection);
};
#endif  // MOTIONSEQUENCER_H