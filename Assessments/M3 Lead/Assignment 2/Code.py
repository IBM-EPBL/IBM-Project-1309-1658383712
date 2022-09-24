from random import randrange
from time import sleep

threshold=35

print('Checking Temperature And Humidity')
while True:
    temperature=randrange(10,50,1)
    humidity=randrange(10,90,1)
    print("Temperature :",temperature,"°C , Humidity :",humidity,"%")
    if temperature>threshold and humidity<threshold:
        break
    sleep(1)

print("Warning!!! Temperature Is High And Humidity Is Low!")
