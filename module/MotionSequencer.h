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

enum class CoordinateType { crossCircle, blockCircle, middlePoint };

class MotionSequencer {
 public:
  /** コンストラクタ
   * @param　ctrler_ 参照型コントローラクラス
   * @param  linear_ 参照型直線運動クラス
   * @param  tracer_ 参照型ライントレーサクラス
   * @param  yaw_    参照型回頭クラス
   **/
  MotionSequencer(Controller& ctrler_, bool isLeftCource_);

  /** 座標->機動変換メソッド
   * @param route_ 整数型座標ベクタ
   * @param direct_ 向き情報
   **/
  void route2Motion(vector<vector<int>>& route_, Direction direction);

 private:
  Controller& ctrler;
  MoveStraight linear;
  LineTracer tracer;  //プロパティの目安：{ 320, baseSpeed, 0.0, { 0.1,0.005, 0.01 } }
  Rotation yaw;

  Direction calcNextDirection(vector<int>& currentCoordinate, vector<int>& nextCoordinate);
  int calcAngle(Direction currentDirection, Direction nextDirection);
  CoordinateType getCoordinateType(vector<int>& coordinate);

  // Direction pre_direct;  // 1つ前の向き情報
  // /*/-------------------------------------------------------------*/
  // void (*stateMachine[5])();        //関数テーブル
  // void move(Scines scine_);         //機動
  // static void cb_cross2MidPoint();  //交点->中点
  // static void cb_midPoint2Cross();  //中点->交点
  // static void cb_yawing();          //方向転換
  // static void cb_linear();          //交点∪中点 -> ブロックサークル
  // static void cb_mid2Mid();         //中点->中点
  // /*-------------------------------------------------------------/*/

  // vector<int> x_diff;  //二点間のx差分
  // vector<int> y_diff;  //二点間のy差分
  // void vectordiff(vector<vector<int>>& c8es_);

  // // 二点間の差分の座標から次に進む方向を返す関数
  // Direction direction2angle(std::vector<int> x_diff, std::vector<int> y_diff, Direction direct_);
};

/* 二次元ベクタの読み方
for(int i=0; i<(int)list.size(); i++){
  printf("(%d, %d)->", list[i][0], list[i][1]);
}
*/

#endif  // MOTIONSEQUENCER_H