/*
 * MyPhoton.h
 *
 *  Created on: Feb 1, 2012
 *      Author: csander
 */

#ifndef MYPHOTON_H_
#define MYPHOTON_H_

#include <TLorentzVector.h>

class MyPhoton: public TLorentzVector {

   public:

      MyPhoton();
      MyPhoton(double px, double py, double pz, double e) {
         SetPxPyPzE(px, py, pz, e);
      }
      ;
      virtual ~MyPhoton();

      void SetIsolation(double x) {
         isolation = x;
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

   private:

      double isolation;

};

#endif /* MYPHOTON_H_ */
