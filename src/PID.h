#ifndef PID_H
#define PID_H

#include <vector>
using namespace std; //Twiddle

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 

  double Kp;
  double Ki;
  double Kd;
  
  //Keep track of CTE - From Python Quiz
  double diff_cte;
  double total_cte;
  double prev_cte;
  bool first_update;

  //Used for my steering angle return
  double s_angle;

 /*//Twiddle variables
  double dpKp;
  double dpKi;
  double dpKd;
  int twiddle_calls;
  bool first_pass;
  double twiddle_tol;
  double best_errortemp;
  double best_error;
  double errortemp;
  double error;
  int counts;
  int base_counts;
  double dp_total;
*/

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);
  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

 /* 
  * Use Twiddle to auto tune 
  
  void Twiddle();
  void TwiddleDone();
*/

};

#endif /* PID_H */
