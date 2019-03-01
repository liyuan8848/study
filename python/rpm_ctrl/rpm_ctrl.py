from socket import *
from time import ctime
import math
import logging
import struct
import sys
import time


#azmuth ethernet address 
az_addr = '10.10.10.161'

#elevation ethernet address
el_addr = '10.10.10.162'
az_port = 5000
el_port = 5000

#receiver buffer size
buffer_size = 1024

loglevel = logging.DEBUG
# loglevel = logging.INFO



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
        self.socket.sendto(command, self.addr)
        null_response_buffer_size = 13
        data, ser_addr = self.socket.recvfrom(null_response_buffer_size)
        if not data:
            print("No data receive after NULL status command")
        else:
            print("received after NULL Status command ", repr(data))
            return data
    def angle_to_bams_format_cal(self,angle):
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


    def data_to_hex_string(self, data):
        ret = ''.join(['0x{:02X} '.format(i) for i in data])
        ret.strip()
        return ret

    def packet_to_hex_string(self, packet):
        data = self.packet_to_data(packet)
        return self.data_to_hex_string(data)

    def packet_to_data(self, packet):
        return struct.unpack('B'*len(packet), packet)

    def data_to_packet(self, data):
        return struct.pack('B'*len(data), *data)

    def set_degree(self, angle):
        print("set angle to", angle)
        data = self.angle_to_bams(angle)
        data.insert(0,0x3A)
        data.extend([0x00, 0x00, 0x00, 0x08])

        data_size = len(data)
        print("data_size ", data_size)

        data_packet = struct.pack('B'*len(data), *data)
        hex_string = self.packet_to_hex_string(data_packet)
        logging.debug('sendto:{}:{} bytes: {}'.format(self.addr, len(data_packet), hex_string))
        # print("data_packet is ", repr(data_packet))
        self.socket.sendto(data_packet, self.addr)
        rsp_buffersize = 13
        res_data, ser_addr = self.socket.recvfrom(rsp_buffersize)
        if not res_data:
            print("No data receive after set_angle command")
            
        else: 
            print("received after set_angle command ", repr(res_data), "server address ", ser_addr)
    
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
    
    def mode_command(self, angle):
        self.set_degree(angle)

    def parameter_request(self):
        command = b'\x34'
        self.socket.sendto(command,self.addr)
        para_response_buffer_size = 17
        data, ser_addr = self.socket.recvfrom(para_response_buffer_size)
        if not data:
            print("No data receive after Parameters request command")
        else:
            print("received after Parameters request command ", repr(data))
            return data

    def Ethernet_address_command(self):
        command = b'\x3b'
        self.socket.sendto(command,self.addr)
        ethernet_response_buffer_size = 6
        data, ser_addr = self.socket.recvfrom(ethernet_response_buffer_size)
        if not data:
            print("No data receive after Ethernet Address request command")
        else:
            print("received after Ethernet Address request command ", repr(data))
            return data
    
    def parameter_command(self):
        
        # The servo tuning parameters are set at the factory and should not require modification
        
        command = b'\x36'
        
        # self.socket.sendto(command,self.addr)
        # para_command_response_buffer_size = 1
        # data, ser_addr = self.socket.recvfrom(para_command_response_buffer_size)
        # if not data:
        #     print("No data receive after Ethernet Address request command")
        # else:
        #     print("received after Ethernet Address request command ", repr(data))
        #     return data

    

def Ethernet_address_request():
    pass



def main():

    print("In main()")
    logging.basicConfig(format='%(asctime)s %(levelname)s  %(pathname)s:%(lineno)s  %(message)s',
            level=loglevel)
    
    az_rpm = RPM_SocketObj(az_addr,az_port)
    el_rpm = RPM_SocketObj(el_addr,el_port)

    # reset the servo

    az_rpm.rpm_servo_on()
    el_rpm.rpm_servo_on()
    
    print("start to reset rpm")
    az_rpm.set_degree(0)
    el_rpm.set_degree(0)

   
    # Scan mode 

    # for i in range(0, 360, 5):
    #     for j in range(0, 85, 5):
    #         az_rpm.set_degree(j)
    #         el_rpm.set_degree(i)
    #         time.sleep(2)

        



if __name__ == "__main__":
    main()
