import struct
import ctypes

var = struct.pack('hhl',5,10,15)
print("Size of String representation is {}.".format(struct.calcsize('hhl')))
size = struct.calcsize('hhl')
print size

buff = ctypes.create_string_buffer(size)

print(struct.pack_into('hhl', buff, 0, 5, 10, 15))
print(struct.unpack_from('hhl',buff,0))

print var
print struct.unpack('hhl',var)

var = struct.pack('iii',10, 20, 30)

print var

print struct.unpack('iii',var)
