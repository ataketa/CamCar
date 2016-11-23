># CamCar
>It is our first time to use github to handle the project.

>##introduction
>Our aim is to build a camera car with raspberry pi,stm32 and android(as a remote controller).
>Our car is expected to have the following function:
>>1.being able to go forward,backward,left,right
>>2.the servo in the car and turn the camera up and down
>>3.remote control
>>4.video transport 
>>5.auto Obstacle avoidance
>>6.object tracking

>##requirement 

>>###requirement:hardware

>>>####1.mcu or board
>>>>1.raspberry pi 2 or later version
>>>>2.stm32f103

>>>####2.android phone

>>>####3.motor and servo
>>>>1.tow motors with driver board
>>>>2.one servo(which is used to turn camera)

>>>####4.power bank
>>>>(we use power banks as power)

>>>####5.infared sensor
>>>>(we will use infared leds,collectors and bjts to build up our infared sensor)

>>###requirement:software

>>>####v4l2rtspserver
<pre><code>
git clone --recursive https://github.com/mpromonet/v4l2rtspserver.git
cd v4l2rtspserver/v4l2wrapper
make
cd ..
cp v4l2wrapper/libv4l2wrapper.a .
cmake . && make
make install
</code></pre>
(for more information please visit the https://github.com/mpromonet/v4l2rtspserver.git)








