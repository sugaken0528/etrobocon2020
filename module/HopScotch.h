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

using namespace std;

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
   **/
  void cnvrtC8E2Motion(vector<vector<int>>& c8es_, Direction direct_);


 private:
    Controller&     ctrler; //参照型コントローラクラス
    MoveStraight&   linear; //参照型直線運動クラス
    LineTracer&     tracer; //参照型ライントレーサクラス
    Rotation&       yaw;    //参照型回頭クラス

    void cb_crossToMidPoint(); //交点->中点
    void cb_midPointToCross(); //中点->交点
    void cb_yawing();          //方向転換
    void cb_linear();          //交点∪中点 -> ブロックサークル
    void cb_midToMid();        //中点->中点
    void state();

    //二点間のx差分
    // 座標どうしの差分
    vector<int> x_diff; //二点間のx差分
    vector<int> y_diff; //二点間のy差分    
    void vectordiff(vector<vector<int>> & c8es_);


    // 座標どうしの差分から方角をとる.
    
    
};

#endif//HOPSCOTCH_H