X2DCLI
Xinput to DirectInput
by Beterhans (beter_hans@hotmail.com)
version data: Mar 20 2017

This console app is aim to fix the z-axis problem for the Xbox360 controller on old windows games (should also works on Xbox one controller).

----- Back ground ----
The Xbox360 controller come with 2 sets of API can be used by a Game.
Xinput (the new one) which don't have z-axis problem.
Direct Input (the old one) which have z-axis problem.
And OLD Game Can't use new Xinput since they are old.

The z-axis problem is the problem that the driver treat left right trigger as a single z-axis. make you unable to press them simultaneously.
This is unacceptable if you want to play racing game well.
And this is intentional by Microsoft. so they knew it and won't fix it.

----- Solution ------
take the new Xinput data to a virtual old Directinput gamepad with 2 axises.

Video DEMO on Youtube
https://www.youtube.com/watch?v=UERyvjPWFsQ

----- Installation --
X2DCLI is portable. no install is needed. but it's just part of the sulution.
So.
1. Make sure you have DirectX fully installed. If you are not sure about it run DirectX setup again. https://www.microsoft.com/en-us/download/details.aspx?id=35
2. go to http://vjoystick.sourceforge.net/site/index.php/download-a-install/download download a virtual joysitck named vJoy.
3. install vjoy
4. config a vjoy device with 2 silders. (no button or other axis is needed you can delete them.) remember the vjoy device ID.
5. plug in Xbox360 controller.
6. run this X2DCLI
7. answer question and run.

---- Know issue and workround ---
While you have your X2DCLI running, if you press triggers actually the vjoy is moving and the old z-axis are also moving!
This makes game confuse when you want to assign key to a function.
So I provided a mode that X2DCLI will press the left or right trigger for you without pressing the real controller.
to active these mode answer runmode as 1 or 2.
but sometimes the game will take the axis inverted. (press is no gas, no press is gas) If you found the axis is inverted try re-assign again make sure this time the direction is different.


--- Donate ---
Please donate me if you like this little app.
Paypal: beterhans.sg@gmail.com
