#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
	auto found_null = s.find("null");
	auto b1 = s.find_first_of("[");
	auto b2 = s.find_last_of("]");
	if (found_null != std::string::npos) {
		return "";
	}
	else if (b1 != std::string::npos && b2 != std::string::npos) {
		return s.substr(b1, b2 - b1 + 1);
	}
	return "";
}

int main()
{
	uWS::Hub h;

	PID pid;
	// TODO: Initialize the pid variables. Try to use twiddle, sounds fun

	double Kp = 0.25;
	double Ki = 0.005;
	double Kd = 10.0;

	pid.Init(Kp, Ki, Kd); //Init my pid controller

	h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
		// "42" at the start of the message means there's a websocket message event.
		// The 4 signifies a websocket message
		// The 2 signifies a websocket event
		if (length && length > 2 && data[0] == '4' && data[1] == '2')
		{
			auto s = hasData(std::string(data).substr(0, length));
			if (s != "") {
				auto j = json::parse(s);
				std::string event = j[0].get<std::string>();
				if (event == "telemetry") {
					// j[1] is the data JSON object
					double cte = std::stod(j[1]["cte"].get<std::string>());
					//double speed = std::stod(j[1]["speed"].get<std::string>());
					//double angle = std::stod(j[1]["steering_angle"].get<std::string>()); //not used according to compilier
					double steer_value;
					/*
					* TODO: Calcuate steering value here, remember the steering value is
					* [-1, 1].
					* NOTE: Feel free to play around with the throttle and speed. Maybe use
					* another PID controller to control the speed!
					*/

/*					*****************************************************************************************************************************************
										//Twiddle here - automatic tunning
										//Get initial best err value, this is all roughed int
					pid.counts++;
					pid.dp_total = pid.dpKd + pid.dpKi + pid.dpKd;


					if (pid.dp_total > pid.twiddle_tol)
					{
						if (pid.counts <= pid.base_counts)  //builds a buffer so we aren't udating each frame
						{
							if (pid.first_pass)
							{
								pid.best_errortemp += pow(cte, 2);
								pid.best_error = pid.best_errortemp / pid.base_counts; //could be done more gracefully i know
							}
							else
							{
								pid.errortemp += pow(cte, 2);
							}
						}

						if (pid.counts == pid.base_counts)
						{
							pid.first_pass = false; //no longer the first pass
							pid.error = pid.errortemp / pid.base_counts;

							pid.Twiddle(); //increments twiddle calls count, should enumerate

							//KP and dpKp updates
							if (pid.twiddle_calls == 1) //update Kp
							{
								pid.errortemp = 0;
								pid.Kp = pid.dpKp;
								
							}
							else if (pid.twiddle_calls == 2)  //evaluate Kp update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKp *= 1.1;
									pid.Twiddle();
								}
								else //there was no improvement
								{
									pid.Kp -= 2 * pid.dpKp;
								}
							}
							else if (pid.twiddle_calls == 3)  //Revaluate dpKp update if there was no improvement on update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKp *= 1.1;
								}
								else //there was no improvement
								{
									pid.Kp += pid.dpKd;
									pid.dpKp *= 0.9;
								}
							}


							//Ki and dpKi updates
							else if (pid.twiddle_calls == 4) //update Ki
							{
								pid.errortemp = 0;
								pid.Ki = pid.dpKi;
							}
							else if (pid.twiddle_calls == 5)  //evaluate Ki update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKi *= 1.1;
									pid.Twiddle();
								}
								else //there was no improvement
								{
									pid.Ki -= 2 * pid.dpKi;
								}
							}
							else if (pid.twiddle_calls == 6)  //Revaluate dpKi update if there was no improvement on update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKi *= 1.1;
								}
								else //there was no improvement
								{
									pid.Ki += pid.dpKi;
									pid.dpKi *= 0.9;
								}

							}


							//Kd and dpKd updates
							else if (pid.twiddle_calls == 7) //update Kd
							{
								pid.errortemp = 0;
								pid.Kd = pid.dpKd;
							}
							else if (pid.twiddle_calls == 8)  //evaluate Kd update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKd *= 1.1;
									pid.twiddle_calls = 0; //reset my twiddle stuff
																	}
								else //there was no improvement
								{
									pid.Kd -= 2 * pid.dpKd;
								}
							}
							else if (pid.twiddle_calls == 9)  //Revaluate dpKd update if there was no improvement on update
							{
								pid.errortemp = 0;
								if (pid.error < pid.best_error) //there was improvement
								{
									pid.best_error = pid.error;
									pid.dpKd *= 1.1;
								}
								else //there was no improvement
								{
									pid.Kd += pid.dpKd;
									pid.dpKd *= 0.9;
								}
								pid.twiddle_calls = 0; //reset my twiddle stuff
							}
							
							pid.counts = 0;

						}
					}
					else
					{
						cout << "You are Done" << endl;
					}

					cout << "KP: " << pid.Kp << "     Ki: " << pid.Ki << "     Kd: " << pid.Kd << endl;
					cout << "Twiddle Calls: " << pid.twiddle_calls << endl;
					cout << "Best Error: " << pid.best_error << endl;
					cout << "Current Error: " << pid.error << endl;
******************************************************************************************************************************************
*/

					pid.UpdateError(cte); //takes the crosstrack error and magics it
					steer_value = pid.TotalError(); //returns a double, so I have to use it*/

					// DEBUG
					std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;
					std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

					json msgJson;
					msgJson["steering_angle"] = steer_value;
					msgJson["throttle"] = .3; //.3stock
					auto msg = "42[\"steer\"," + msgJson.dump() + "]";
					std::cout << msg << std::endl;
					ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
				}
			}
			else {
				// Manual driving
				std::string msg = "42[\"manual\",{}]";
				ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
			}
		}
	});

	// We don't need this since we're not using HTTP but if it's removed the program
	// doesn't compile :-(
	h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
		const std::string s = "<h1>Hello world!</h1>";
		if (req.getUrl().valueLength == 1)
		{
			res->end(s.data(), s.length());
		}
		else
		{
			// i guess this should be done more gracefully?
			res->end(nullptr, 0);
		}
	});

	h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
		std::cout << "Connected!!!" << std::endl;
	});

	h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
		ws.close();
		std::cout << "Disconnected" << std::endl;
	});

	int port = 4567;
	if (h.listen(port))
	{
		std::cout << "Listening to port " << port << std::endl;
	}
	else
	{
		std::cerr << "Failed to listen to port" << std::endl;
		return -1;
	}
	h.run();
}
