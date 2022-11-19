import time
import sys
import ibmiotf.application
import ibmiotf.device
import random

organization = "92rnyd"
deviceType = "GPS"
deviceId = "1234"
authMethod = "token"
authToken = "12345678"
   
try:
	deviceOptions = {"org": organization, "type": deviceType, "id": deviceId, "auth-method": authMethod, "auth-token": authToken}
	deviceCli = ibmiotf.device.Client(deviceOptions)
	
except Exception as e:
	print("Caught exception connecting device: %s" % str(e))
	sys.exit()

deviceCli.connect()

while True:
        name="Child"
        #latitude,longitude=9.525498643996373,77.85547697431774  #inarea
        #latitude,longitude=9.531834223946193,77.84996742667008  #outarea
        data = { 'name' : name, 'lat': latitude ,'lon': longitude }
        #print data
        def myOnPublishCallback():
            print ("Published Latitude = ",latitude,"Longitude = ",longitude,"to IBM Watson")

        success = deviceCli.publishEvent("IoTSensor", "json", data, qos=0, on_publish=myOnPublishCallback)
        if not success:
            print("Not connected to IoTF")
        time.sleep(10)
        
deviceCli.disconnect()
