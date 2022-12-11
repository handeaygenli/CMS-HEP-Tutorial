/*
 * MyElectron.h
 *
 *  Created on: Feb 1, 2012
 *      Author: csander
 */

#ifndef MYELECTRON_H_
#define MYELECTRON_H_

#include <TLorentzVector.h>

class MyElectron: public TLorentzVector {

   public:

      MyElectron();
      MyElectron(double px, double py, double pz, double e) {
         SetPxPyPzE(px, py, pz, e);
      }
      ;
      virtual ~MyElectron();

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
      const bool IsIsolated() {
         return (isolation < 1.);
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

#endif /* MYELECTRON_H_ */
