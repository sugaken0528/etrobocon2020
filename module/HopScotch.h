/**
 * @file HopScotch.h
 * @brief 座標情報を機動に変換するクラス
 * @author T.Yoshino(Mikoyaan), D.Hirayama(Kanikama)
 **/

#ifndef HOPSCOTCH_H
#define HOPSCOTCH_H

#include "Controller.h"
#include "MoveStraight.h"
#include "LineTracer.h"
#include "Rotation.h"
#include <vector>

//※このフォーマットで適切か菅くんに要確認　9/11/2020
enum Direction { North, NEast, East, SEast, South, SWest, West, NWest };

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
   * @param direct_ 列挙型向き情報
   **/
  void cnvrtC8E2Motion(std::vector<std::vector<int>>& c8es_, Direction direct_);

 private:
};

#endif  // HOPSCOTCH_H
