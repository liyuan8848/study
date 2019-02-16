from socket import *
from time import ctime
import math
import logging
import struct
import sys


#azmuth ethernet address 
az_host = '10.10.10.161'

#elevation ethernet address
el_host = '10.10.10.162'
az_port = 5000
el_port = 5000

#receiver buffer size
buffer_size = 1024



class RPM_SocketObj:

    def __init__(self, ip_addr, port):
        self.ip_addr = ip_addr 
        self.port = port 
        self.socket = socket(AF_INET, SOCK_DGRAM)
        self.addr = (ip_addr,port)
        
    
    def rpm_servo_on(self):
        command = b'\x07'
        self.socket.sendto(command,self.addr)
        rsp_buffersize = 1
        data, ser_addr = self.socket.recvfrom(rsp_buffersize)
        if not data:
            print("No data receive after servo_on command")
        else:
            print("received after servo_on command ", repr(data))
    
    def rpm_servo_off(self):
        command = b'\x08'
        self.socket.sendto(command,self.addr)
        rsp_buffersize = 1
        data, ser_addr = self.socket.recvfrom(rsp_buffersize)
        if not data:
            print("No data receive after servo_on command")
            
        else: 
            print("received after servo_on command ", repr(data))
    
    def NULL_status_request(self):
        command = b'\x33'
        self.socket.sendto(command,self.addr)
        null_response_buffer_size = 13
        data, ser_addr = self.socket.recvfrom(null_response_buffer_size)
        if not data:
            print("No data receive after NULL status command")
        else:
            print("received after NULL Status command ", repr(data))
            return data
    def angle_to_bams_format_cal(angle):
        # calculate angle in degree to binary angle Measurement
        # tested with -45, 315, 45, 405, 45.55, those cases work as expected 
        angle = angle - math.floor(float(angle)/360.0)*360.0
        return int(round(angle/180.0 *pow(2,23))) & 0x00FFFFFF
    
    def angle_to_bams(self, angle):
        bams = self.angle_to_bams_format_cal(angle)
        high_byte = (bams & 0xFF0000) >> 16
        mid_byte = (bams & 0x00FF00) >> 8
        low_byte = (bams & 0x0000FF)
        return [high_byte, mid_byte, low_byte]

    def set_degree(self, angle):
        data = self.angle_to_bams(angle)
        data.insert(0,0x3A)
        data.extend([0x00, 0x00, 0x00, 0x08])
        self.socket.sendto(data, self.addr)
    
    def bams_to_degree(self, pos):
        
        high_pos = pos[0]
        mid_pos = pos[1]
        low_pos = pos[2]

        new_pos = (high_pos<<16) + (mid_pos[1]<<8) + low_pos
        degree = new_pos*180.0/pow(2, 23)
        return degree

    def get_degree(self):
        self.rpm_servo_on()
        data = self.NULL_status_request()
        if data[0] :
           pos = data[1:4]
           angle = self.bams_to_degree(pos)
        return angle           
    
    


az_addr = (az_host, az_port)
el_addr = (el_host, el_port)



def parameter_command():
    pass

def mode_command():
    pass

def Ethernet_address_command():
    pass



def parameter_request():
    pass

def Ethernet_address_request():
    pass



def main():

    print("In main()")
    
    az_rpm = RPM_SocketObj(az_addr,az_port)
    el_rpm = RPM_SocketObj(el_addr,el_port)

    az_socket = az_rpm.socket
    el_socket = el_rpm.socket




if __name__ == "__main__":
    main()
