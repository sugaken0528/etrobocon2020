/**
 * @file HopScotch.h
 * @brief 座標情報を機動に変換するクラス
 * @author T.Yoshino(Mikoyaan), D.Hirayama(Kanikama)
 **/

#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H

#include <vector>
#include "Controller.h"
#include "MoveStraight.h"
#include "LineTracer.h"
#include "Rotation.h"
#include "BlockBingoData.h"

using namespace std;

enum class Scines {
  C2M = 0,  //交点から中点
  M2C,      //中点から交点
  YAW,      //回頭
  LIN,      //直線運動クラス
  M2M       //中点から中点
};

//※このフォーマットで適切か菅くんに要確認　9/11/2020　ヨシ
enum class Direction { North, NEast, East, SEast, South, SWest, West, NWest };

class HopScotch {
 public:
  /** コンストラクタ
   * @param　ctrler_ 参照型コントローラクラス
   * @param  linear_ 参照型直線運動クラス
   * @param  tracer_ 参照型ライントレーサクラス
   * @param  yaw_    参照型回頭クラス
   **/
  HopScotch(Controller& ctrler_, MoveStraight& linear_, LineTracer& tracer_, Rotation& yaw_);

  /** 座標->機動変換メソッド
   * @param c8es_ 整数型座標ベクタ (c8es = coordinates)
   * @param direct_ 向き情報
   **/ //↓略すな
  void cnvrtC8E2Motion(vector<vector<int>>& c8es_, Direction direct_);

 private:
  Controller& ctrler;    //参照型コントローラクラス
  MoveStraight& linear;  //参照型直線運動クラス
  LineTracer& tracer;  //参照型ライントレーサクラス プロパティの目安：{ 320, baseSpeed, 0.0, { 0.1,
                       //0.005, 0.01 } }// 第3区間
  Rotation& yaw;  //参照型回頭クラス

  Direction pre_direct;  // 1つ前の向き情報

  /*/-------------------------------------------------------------*/
  void (*stateMachine[5])();        //関数テーブル
  void move(Scines scine_);         //機動
  static void cb_cross2MidPoint();  //交点->中点
  static void cb_midPoint2Cross();  //中点->交点
  static void cb_yawing();          //方向転換
  static void cb_linear();          //交点∪中点 -> ブロックサークル
  static void cb_mid2Mid();         //中点->中点
  /*-------------------------------------------------------------/*/

  vector<int> x_diff;  //二点間のx差分
  vector<int> y_diff;  //二点間のy差分
  void vectordiff(vector<vector<int>>& c8es_);

  // 二点間の差分の座標から次に進む方向を返す関数
  Direction vector2direction(vector<int> x_diff, vector<int> y_diff);
  Direction direction2angle(std::vector<int> x_diff, std::vector<int> y_diff, Direction direct_);
};

/* 二次元ベクタの読み方
for(int i=0; i<(int)list.size(); i++){
  printf("(%d, %d)->", list[i][0], list[i][1]);
}
*/

#endif  // HOPSCOTCH_H