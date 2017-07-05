**PID Controller Reflection** 

This is my reflection of the effect each of the PID components had in my implementation and how the final hyperparameters were chosen for Udacity's PID Controller Project. 67-220

---

**How it went**
My original plan was to use 'Twiddle' to automatically find all of my PID values. After implementing 'Twiddle' in the quiz, I thought it was one of the most amazing, easy-to-use tools that I have ever seen. Gone would be the days of PID guess and check. After about two days of trying to tune 'Twiddle', I gave up. I believe how I implemented or maybe my understanding of it is incorrect. My understandin of 'Twiddle' is the following:
 1. Initialize the parameters
 2. Initialize potential changes to the parameters
 3. Calculate some error
 4. Adjust a parameter with the potential change
 5. Calculate some error
 6. Check if the adjustment of the parameter worked
 7. Adjust the potential changes based on how well the update worked
 8. Repeat from 3.
 
I tried only tuning the P value, tunning all the parameters, adjusting tolerance levels, using curves, straight roads, adjusting speeds, and it was a struggle to get anywhere. I then decided to manually tune, and within 30 minutes, I was finished. I feel like I need to understand how to 'Twiddle' better, so I will revisit it later.

My understanding of the PID parameraters are as follows:
 *'P' - The higher the 'P' the more responsive your plant is, but it comes the penalty of overshoot and oscillation
 *'I' - There to decrease Steady State error. The more of it the faster the response but comes with the penalty of overshoot and oscillation.
 *'D' - There to put the brakes on the overshooting and oscillation. There to stabilize. It comes with the penalty of stabilization if you use too much of it.
 
Here is how my manual tunning went:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x1 grayscaled image   							| 
| Convolution #1     	| 1x1 stride, outputs 28x28x6 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x6 				|
| Convolution #2	    | 1x1 stride, outputs 10x10x16      									|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x16 				|
| Flatten	      	| outputs 400x1 				|
| Fully connected #1		| outputs 200x1        									|
| Sigmoid					|												|
| Fully connected #2	| outputs 43x1        									|
| Softmax	w/ Cross Entropy w/Logits			|         									|
| Loss Operation			|  Reduce Mean       									|
| Optimizer			| Adam Optimizer       									|
| Training Operation			|  Minimize       									|
 



