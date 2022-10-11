import RPi.GPIO as GPIO 
from time import sleep

LED = 7

GPIO.setmode(GPIO.BOARD)  
GPIO.setup( LED, GPIO.OUT)   
GPIO.output( LED, GPIO.LOW) 

delay=int(input("Enter The Delay For Blinking"))


try:
	while True:
		GPIO.output( LED, GPIO.HIGH)
                sleep(delay)
		GPIO.output( LED, GPIO.LOW)
                sleep(delay)

except KeyboardInterrupt:
	GPIO.output( LED, GPIO.LOW)
        GPIO.cleanup()
