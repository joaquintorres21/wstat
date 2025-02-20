import interface as ui
import socket as skt
from os import getenv
import time

class Data_ESP:

    __temperature = 0
    __humidity = 0
    __co2 = 0
    __pressure = 0
    __uv = 0

    def __init__(self, DHT_22, MQ_135, BMP_280, MI8511):
        self.__temperature = DHT_22[0]
        self.__humidity = DHT_22[1]
        self.__co2 = MQ_135
        self.__pressure = BMP_280
        self.__uv = MI8511

    def get_temperature(self): 
        return self.__temperature
    
    def get_humidity(self): 
        return self.__humidity
    
    def get_co2(self): 
        return self.__co2
    
    def get_pressure(self): 
        return self.__pressure
    

if __name__ == '__main__':

    port = getenv("SV_PORT")
    data_length = getenv("DATA_LENGTH")
    socket = skt.socket()
    socket.bind('localhost', port)
    socket.listen(3)

    comm, controller = socket.accept()
    print(f"Conexión con {controller} establecida")
    t0 = time.time()
    while(time.time()-t0 < 5): pass
    data = socket.recv(data_length)
        
    

    
    