#!/usr/bin/env python
import httplib, urllib
import time
import Adafruit_DHT

KEY = 'G8K5SR525HYW4DAR'
headers = {"Content-type": "application/x-www-formurlencoded","Accept": "text/plain"}
DEBUG = True
sensor = Adafruit_DHT.DHT22
pin=23
# function to read 1 minute load average from system

def read_temp():
    if DEBUG:
        print("Reading temperature from dht11 sensor")
        humidity, temperature = Adafruit_DHT.read_retry(sensor,pin)
    return temperature 

while True:
    temp = read_temp()
    params = urllib.urlencode({'field1': temp, 'key':KEY})
    conn = httplib.HTTPConnection("api.thingspeak.com:80")
    try:
        conn.request("POST", "/update", params, headers)
        response = conn.getresponse()
        if DEBUG:
            print(response.status, response.reason)
        data = response.read()
        conn.close()
    except:
        print("Connection failed")
    time.sleep(10)
