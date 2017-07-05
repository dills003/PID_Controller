**Traffic Sign Recognition** 

This was my attempt at Udacity's Self-Driving Car Project #2. The goal was to build a German Traffic Sign Recognition Classifier.

---

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set ([pickled dataset supplied to us](https://d17h27t6h515a5.cloudfront.net/topher/2017/February/5898cd6f_traffic-signs-data/traffic-signs-data.zip))
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./examples/SignPics.png "Visualization"
[image2]: ./examples/BarGraph.png "Visualiztation"
[image4]: ./MyGermanSigns/30kmh1.jpg "Traffic Sign 1"
[image5]: ./MyGermanSigns/RightOfWay11.jpg "Traffic Sign 2"
[image6]: ./MyGermanSigns/Stop14.jpg "Traffic Sign 3"
[image7]: ./MyGermanSigns/EndOfSpeed32.jpg "Traffic Sign 4"
[image8]: ./MyGermanSigns/RoundAbout40.jpg "Traffic Sign 5"

## Rubric Points
I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
*Writeup / README*
1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf.

Here is a link to my [project code](https://github.com/dills003/Traffic_Sign_Classifier-Project2/blob/master/P2.ipynb)

*Data Set Summary & Exploration*

The code for this step is contained in the second code cell of the IPython notebook.  

1. I used the numpy library to calculate summary statistics of the traffic
signs data set:

* The size of training set is 134799 examples.
* The size of test set is 12630 examples.
* The shape of a traffic sign image is (32, 32, 3)
* The number of unique classes/labels in the data set is 43 labels.

2. Include an exploratory visualization of the dataset and identify where the code is in your code file.

The code for this step is contained in the third code cell of the IPython notebook.  

Here is an exploratory visualization of the data set. I displayed all of the images that we would be trying to classify and also a bar graph showing how many of each sign we had to train with

![alt text][image1]
![alt text][image2]

*Design and Test a Model Architecture*

1. Describe how, and identify where in your code, you preprocessed the image data. What tecniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc.

The code for this step is contained in the fourth code cell of the IPython notebook.

As a first step, I decided to convert the images to grayscale, because all of our videos seemed to deal with grayscale images. Also, I figured a small percentage of drivers are colorblind and they seem to interpret signs just fine. Also, I figured the computing power it would take to churn throught the images would be less. I also found a nice weight system for grayscaling images, it performed better than just taking a normal average.

I originally normalized the data after grayscaling it, but the results were less than desirable. My average training accuracy never reached above a 90%. With grayscaling alone, I often achieved around 95%.

2. Describe how, and identify where in your code, you set up training, validation and testing data. 

I didn't split up the data, the data came with validation files, so that was nice. 

3. Describe, and identify where in your code, what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

The code for my final model is located in the fifth cell of the ipython notebook. I used the LeNet-5 model from our lab. I altered the second convulution activation from a sigmoid to a relu. I did this because that is what the TensorFlow labs have you do. I also altered the output and input sizes to my layers.

My final model consisted of the following layers:

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
 


4. Describe how, and identify where in your code, you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

The code for training the model is located in the sixth cell of the ipython notebook. I thought using small batch sizes would offset the fact that we have an unever distribution of training example label/pictures.

To train the model, I used the following parameters:

| Parameter         		|     Value        					| 
|:---------------------:|:---------------------------------------------:| 
| Epochs        		| 10   							| 
| Batch Size     	| 150 	|
| Learning Rate					|	0.001											|


5. Describe the approach taken for finding a solution. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

The code for calculating the accuracy of the model is located in the seventh cell of the Ipython notebook.

My final model results were:

| Set         		|     Accuracy  					| 
|:---------------------:|:---------------------------------------------:| 
| Validation        		| 0.95   							| 
| Test     	| 0.931 	|

I chose to basically copy what we did in the LeNet lab for the course. I chose that architecture because, it seemed to work well. I altered the second convolution layer to include a relu instead of a sigmoid activation function. I did this because, the TensorFlow labs used relus wherever a convolution was used. I feel like Udacity and TensorFlow are much better architecture creators than I at this point. I also changed the output sizes from some of the layers, it just felt like a smoother trasistion from layer to layer.

I had planned to use dropouts, because I think the idea is really interesting, but shrinking my batch sizes down pretty much did the same thing. This was due to the fact that the labels were so unevenly represented in the training data.

My validation numbers were better than my test, which could suggest a tiny bit of overfitting. Dropout could possibly help this. 

The biggest thing that I learned, is that there is a bunch of knobs that are available to tweak. Epochs, batch sizes, number of layers, types of layers, layer size, pooling, dropout, activations, learning, and how data is presented are all adjusments that can be made to improve the model. Getting good at this is going to take some effort. I come from PID land and three knobs can be quite the chore somethings, deep learning is something else.

Also, if I were to do this again, I would agument my data. Training needs as many examples as possible and it makes sense to have each type of example have the same number of examples.
 

Test a Model on New Images

1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs that I found on the web:

![alt text][image4] 
![alt text][image5] 
![alt text][image6] 
![alt text][image7]
![alt text][image8]

I was actually worried about the last two images the most, which proved to be correct. My training data had very few examples of these two signs compared to that of the other three. I could/should have fixed this by augmenting the data.

2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. Identify where in your code predictions were made. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

The code for making predictions on my final model is located in the 8-11 cells of the Ipython notebook.

Here are the results of the predictions:

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| 30 kmh      		| 30 kmh    									| 
| Right of Way     			| Right of Way  										|
| Stop				| Stop											|
| End of Speed      		| General caution					 				|
| Roundabout	Mandatory		| Children crossing     							|


The model was able to correctly guess 3 of the 5 traffic signs, which gives an accuracy of 60%. This compares horribly to the accuracy on the test set of 93.1%. Like I stated above, this is probably because the two problematic signs did not show up in the training data enough times. My misses, were beyond bad misses. The signs don't look anything close to one another.

3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction and identify where in your code softmax probabilities were outputted. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. 

The code for making predictions on my final model is located in the 12th cell of the Ipython notebook.

For the first image, the model is very sure that this is a 30 kmh sign (probability of 0.988), and the image does contain a 30 kmh sign. The top five soft max probabilities were:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .988         			| Speed limit (30km/h)   									| 
| .003     				| Speed limit (20km/h) 										|
| .003					| Speed limit (80km/h)										|
| .002	      			| Speed limit (50km/h)				 				|
| .001				    | Roundabout mandatory      							|


For the second image, the model is very sure that this is a Right-of-Way sign (probability of 0.993), and the image does contain a Right-of-Way sign. The top five soft max probabilities were:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .993         			| Right-of-way   									| 
| .004     				| Beware of ice/snow									|
| .001					| Double curve								|
| .0005	      			| Pedestrians				 				|
| .0003				    | Roundabout mandatory      							|


For the third image, the model is pretty sure that this is a Stop sign (probability of 0.687), and the image does contain a Stop sign. The top five soft max probabilities were:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .687         			| Stop   									| 
| .146     				| Yield									|
| .045					| Turn left ahead								|
| .023	      			| No passing 				 				|
| .016				    | Speed limit (80km/h)     							|


For the fourth image, the wheels fell off for me. The model is not sure what sign this is. The best guess was a General Caution sign (.238) and the image does not contain a General Caution sign. The images is actually of a End of Speed sign. And it gets worse, the correct sign does not appear on the top five list. The top five soft max probabilities were:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .238         			| General caution   									| 
| .171     				| Road work								|
| .116					| Priority road								|
| .094	      			| End of no passing				 				|
| .090				    | Dangerous curve to the right     							|


For the fifth and final image, the troubles continue. The model is not sure what sign this is. The best guess was a Children Crossing sign (.144) and the image does not contain a Children sign. The images is actually of a Roundabout sign. And it gets worse, the correct sign does not appear on the top five list once again. The top five soft max probabilities were:

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| .144         			| Children crossing   									| 
| .143     				| Priority road							|
| .111					| Right-of-way							|
| .089	      			| End of all speed and passing limits			 				|
| .081				    | Speed limit (60km/h)   							|
