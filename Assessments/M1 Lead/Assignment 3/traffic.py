import RPi.GPIO as GPIO 
from time import sleep

RED = 8
YELLOW = 10
GREEN = 12

GPIO.setmode(GPIO.BOARD)  
GPIO.setup( (8,10,12), GPIO.OUT)   
GPIO.output( (8,10,12), GPIO.LOW) 

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
	GPIO.output( (8,10,12), GPIO.LOW)
        GPIO.cleanup()
