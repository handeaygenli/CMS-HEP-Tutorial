/*
 * MyMuon.h
 *
 *  Created on: Feb 1, 2012
 *      Author: csander
 */

#ifndef MYMUON_H_
#define MYMUON_H_

#include <TLorentzVector.h>

class MyMuon: public TLorentzVector {

   public:

      MyMuon();
      MyMuon(double px, double py, double pz, double e) {
         SetPxPyPzE(px, py, pz, e);
      }
      ;
      virtual ~MyMuon();

      void SetIsolation(double x) {
         isolation = x;
      }
      ;

      void SetCharge(int q) {
         charge = q;
      }
      ;

      const double GetIsolation() {
         return isolation;
      }
      ;

      const bool IsIsolated(double relcut = 0.05) {
         return ((isolation / Pt()) < relcut);
         //return (isolation < 1.);
      }
      ;
      const int GetCharge() {
         return charge;
      }
      ;

   private:

      double isolation;
      int charge;

};

#endif /* MYMUON_H_ */
