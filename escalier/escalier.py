import RPi.GPIO as GPIO
import os
import time 
import pigpio
GPIO.setmode(GPIO.BCM)
#PWMGPIO = 4
GPIO.setwarnings(False)
#square = []
tab = []
#square.append(pigpio.pulse(1<<PWMGPIO,0,4))
#square.append(pigpio.pulse(0,1<<PWMGPIO,4))

#pi = pigpio.pi()
#pi.set_mode(PWMGPIO, pigpio.OUTPUT)
#pi.hardware_PWM(18,38000,500000)
min = 5
max = 15
for i in range(min,max):
	GPIO.setup(i, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
	tab.append(False)

#Alignement
alignement = False
state = min
while alignement == False:
	time.sleep(0.1)
	if GPIO.input(state) == False:
		os.system("aplay -q sound/note5.wav &")
		time.sleep(2)
		#os.system("aplay -q sound/note"+str(state)+".wav")
		if GPIO.input(state) == False:
			os.system("aplay -q sound/note1.wav &")
			time.sleep(0.1)
			os.system("aplay -q sound/note10.wav &")
			time.sleep(0.1)
			state += 1
		else:
			os.system("aplay -q sound/note7.wav &")
			time.sleep(0.1)
			os.system("aplay -q sound/note7.wav &")	
			time.sleep(0.1)
	else:
		print("waiting for " + str(state-min+1) + " ...")
	if state >= max:
			for i in range(0,10):
				os.system("aplay -q sound/note"+str(i)+".wav &")
				time.sleep(0.2)
			alignement = True	
#Programme
while 1:
	for i in range(5,9):
		if GPIO.input(i) == True: # < 1
			time.sleep(0.01)
			print("state[i] = " + str(tab[i-5]) + "/GPIOI = " + str(GPIO.input(i)) + "/Marche = " +  str(i-5))
			if GPIO.input(i) == True:
				if tab[i-5] == False :
					os.system("aplay -q sound/note"+str((i-5)*2)+".wav &")
					tab[i-5] = True
					time.sleep(0.01)
		else:
			if tab[i-5] == True:
				tab [i-5] = False
			#print("Nope")
		time.sleep(0.01)
			#os.system("aplay -q sound/note"+str(i)+".wav &")
			




#pi.wave_add_generic(square)

#wid = pi.wave_create()

#if wid >= 0:
#	pi.wave_send_repeat(wid)
#	time.sleep(60) 
#	pi.wave_tx_stop()
#	pi.wave_delete(wid)
#pi.stop()
