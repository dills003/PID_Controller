#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	//Load the PID variables from main
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;

	//Initialize the error stuff to zero
	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;

	//Initialize my cte variables
	diff_cte = 0.0;
	total_cte = 0.0;
	prev_cte = 0.0;
	first_update = false;

	//Initialize my steering angle
	s_angle = 0.0;

/*	//Initilize twiddle
	dpKp = 1.0;
	dpKi = 1.0;
	dpKd = 1.0;
	twiddle_calls = 0;
	first_pass = true;
	twiddle_tol = 0.5;
	best_errortemp = 0.0;
	best_error = 0.0;
	errortemp = 0.0;
	error = 0.0;
	counts = 0;
	base_counts = 25;
	dp_total = 0;
*/
}

void PID::UpdateError(double cte) {

	if (!first_update) //first run we have no previous cte
	{
		prev_cte = cte;
		first_update = true;
	}
	
	//update all my cte values
	diff_cte = cte - prev_cte;;
	total_cte += cte;
	prev_cte = cte;

	//update all of the error
	p_error = -Kp * cte;
	i_error = -Ki * total_cte;
	d_error = -Kd * diff_cte;

}

double PID::TotalError() { //returns the steering angle of the car -1 to 1 are values I can use
	
	//add up all of the error
	s_angle =  p_error + i_error + d_error;

	if (s_angle < -1)
	{
		s_angle = -1;
	}
	else if (s_angle > 1)
	{
		s_angle = 1;
	}

	return s_angle;
}

/*
void PID::Twiddle() { //increments twiddle
	twiddle_calls++;
}

void PID::TwiddleDone() { //sets twiddle to start again
	twiddle_calls = 0;
}
*/