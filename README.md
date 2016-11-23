># ==CamCar==
>It is the first time to use github to handle the project.

>##**introduction**
>*Our aim is to build a camera car with raspberry pi,stm32 and android(as a remote controller).*
>The car is expected to have following functions:
>>1.  being able to go forward,backward,left and right
>>2.  the servo in the car can turn the camera up and down
>>3.  remote control
>>4.  video transmission
>>5.  automatic  collision-avoidance
>>6.  object tracking

>##requirement 

>>###requirement:hardware

>>>####1.mcu or board
>>>>1.  raspberry pi 2 or later version
>>>>2.  stm32f103

>>>####2.android phone

>>>####3.motor and servo
>>>>1.  tow motors with the driver board
>>>>2.  one servo which is used to turn a camera

>>>####4.power bank
>>>>(we use power banks as power)

>>>####5.infrared sensor
>>>>(we would use infrared leds,collectors and bjts to build up the infrared sensor)

>>###requirement:software

>>>####v4l2rtspserver
<pre><code>
git clone --recursive https://github.com/mpromonet/v4l2rtspserver.git
cd v4l2rtspserver4l2wrapper
make
cd ..
cp v4l2wrapperbv4l2wrapper.a .
cmake . && make
make install
</code></pre>
(for more information please visit the https://github.com/mpromonet/v4l2rtspserver.git)





