import RPi.GPIO as GPIO 
from time import sleep

RED = 22
YELLOW = 24
GREEN = 26

GPIO.setmode(GPIO.BOARD)  
GPIO.setup( 22,24,26), GPIO.OUT)   
GPIO.output( (22,24,26), GPIO.LOW) 

try:
	while True:
		GPIO.output( RED, GPIO.HIGH)
                sleep(60)
		GPIO.output( RED, GPIO.LOW)
		GPIO.output( YELLOW, GPIO.HIGH)
                sleep(5)
		GPIO.output( YELLOW, GPIO.LOW)
		GPIO.output( GREEN, GPIO.HIGH)
                sleep(20)
		GPIO.output( GREEN, GPIO.LOW)

except KeyboardInterrupt:
	GPIO.output( (22,24,26), GPIO.LOW)
        GPIO.cleanup()
