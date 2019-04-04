import math

a_list = [0x10, 0x11, 0x12]

print [hex(i) for i in a_list]

a_list.insert(0, 0x09)

print [hex(i) for i in a_list]

a_list.extend([0x13, 0x14, 0x15])

print [hex(i) for i in a_list]

def bams_to_degree(pos):
    
    high_pos = pos[0]
    mid_pos = pos[1]
    low_pos = pos[2]

    new_pos = (high_pos<<16) + (mid_pos<<8) + low_pos
    degree = new_pos*180.0/pow(2, 23)
    return degree

def angle_to_bams_format_cal(angle):
    # calculate angle in degree to binary angle Measurement
    angle = angle - math.floor(float(angle)/360.0)*360.0

    print("angle is ", angle)

    print("final value is ", hex(int(round(angle/180.0 * pow(2, 23))) & 0x00FFFFFF))

    return int(round(angle/180.0 * pow(2, 23))) & 0x00FFFFFF



def test_input(input):
    print("intput is ", input)
    pos = angle_to_bams_format_cal(input)

    temp = [(pos & 0xff0000)>>16, (pos & 0xff00)>>8 , pos&0x0000ff]
    print("temp is ",temp)

    result = bams_to_degree(temp)

    print("result is ", result)


angle = 0
test_input(angle)

angle = 45
test_input(angle)


angle = -45
test_input(angle)


angle = 315
test_input(angle)

angle = 360+45.15
test_input(angle)
