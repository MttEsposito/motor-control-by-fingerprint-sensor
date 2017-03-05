# motor-control-by-fingerprint-sensor
arduino code for controlling motor by fingerprint sensor

Component Required:

1x Arduino UNO

1x Arduino Motor Shield

2x Led (i used green/red)

2x Resitence 220 Ω(for led)

1x Fingerprint Sensor

Assembly passage:

USE THE 1.69 ARDUINO VESRION BECAUSE WITH THE LAST VERSION I GOT SOME ISSUE
https://www.arduino.cc/en/Main/OldSoftwareReleases

1)First connect the arduino-motor-shield on the arduino UNO

2)Load the code on the arduino

3)Connect the fingerprint sensor to arduino (Green wire to pin 6 and white wire to pin 7) and open the enroll code than load it into the arduino

4)After load open serial monitor on the arduino program and follow the instructions on the arduino code

5)Then load the code MyFingerprint on the board but first modify the case of the if on success code and put the id you stored in the flash   of the fingerprint

6)Connect the Led with the Resitence on the breadboard and then connect it to the arduino pin 5 the other led on pin 4

10)Connect the motor to the channel A on arduino

11)Power the board and try it
