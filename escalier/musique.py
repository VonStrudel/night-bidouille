import RPi.GPIO as GPIO
import os
import time 
import pigpio
GPIO.setmode(GPIO.BCM)
#PWMGPIO = 4
GPIO.setwarnings(False)
#square = []
#melodie = [1,1,1,2,3,2,1,3,2,2,1]
#melodie = [0,1,2,3,4,5,6,7]
#timing = [1,1,1,1,2,2,1,1,1,1,1]

melodie = [1,2,3,5,5,6,5,3,1,1,2,3,3,2,1,2,1,2,3,5,5,6,5,3,1,1,2,3,3,2,2,1,4,4,6,6,6,5,5,3,1,2]
timing = [0.5,0.5,1,1,1.5,0.5,1,1,1,0.5,0.5,1,1,1,1,2.5,0.5,0.5,1,1,1.5,0.5,1,1,1,0.5,0.5,1,1,1,1,2,1,1,0.5,1.5,1,1,1,1,1,2]

#melodie = [7,7,6,5,4,5]
#timing = [2,1,1,1,1,1]
notes = [0,2,4,5,7,9,11,1,3,6,8,10]
#square.append(pigpio.pulse(1<<PWMGPIO,0,4))
#square.append(pigpio.pulse(0,1<<PWMGPIO,4))
beat = 0.3
for i in range(0,len(melodie)):
	os.system("aplay -q sound/note"+str(notes[melodie[i]-1])+".wav &")
	time.sleep(beat*timing[i])
					
