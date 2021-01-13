# Copyright (C) Microsoft Corporation. All rights reserved.

# This program is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

from netaddr import valid_ipv4, valid_ipv6, INET_PTON

class completion_code:
    cc_key = "Completion Code"
    success = "Success"
    failure = "Failure"
    fwdecompress = "FirmwareDecompress"
    deviceoff = "DevicePoweredOff"
    notpresent = "DeviceNotPresent"
    desc = "Status Description"
    ipmi_code = "IPMI Completion Code"
    state_desc = "Description"
    err_code = "ErrorCode"
    unknown = "Unknown"
    redfish_msg = "Use Redfish# mode to run this command. Interface Type: REST"
    rest_notsupported = "Command not supported. Interface Type: REST"

def set_failure_dict(error_msg, cc_code=completion_code.failure):
    return set_result_dict (cc_code, error_msg)

def set_success_dict(values=None):
    return set_result_dict(completion_code.success, None, values) 

def set_result_dict(code, msg, result=None):
    if result is None:
        result = {}

    result[completion_code.cc_key] = code
    if msg:
        result[completion_code.desc] = msg

    return result

def check_success(values={}):
    if completion_code.cc_key in values:
        if values[completion_code.cc_key] == completion_code.success:
            return True

    return False

def parse_args_retain_case(parser, args):
    """ Make the args lower-cased then parse them using argparse
        After that, we loop over the values in the argparse.Namespace object created
        and replace the lowercased values with correct casing

        Ex.1.:
           args = ['-C', 'aRgC', '-i', '31', '-p', 'admin']

           will create:
           command_args = argparse.Namespace('-c'='argc', '-i'=31, '-p'='admin')

           and we will loop over the values list: ['argc', 31, 'admin] and replace
           'argc' with 'aRgC' using args_lower_to_actual_dict

           Note: '31' (str) changed to 31 (int) so we need 'get' from the dict

        Ex.2.:
           -i 31 -c sdr get Energy_Storage

           will create:
           command_args = argparse.Namespace('-i'=31, '-c'=['sdr', 'get', 'energy_storage'])

           values list will be: [31, ['sdr', 'get', 'energy_storage']]
           so, we need to make sure that for multiple words, we loop inside that list as well
    """
    args_lower = [string.lower() for string in args]
    command_args = parser.parse_args(args_lower)

    args_lower_to_actual_dict = {arg.lower():arg for arg in args}
    for key, value in vars(command_args).iteritems():
        if key == "command":
                continue

        if isinstance(value, list):
            actual_value =  [args_lower_to_actual_dict.get(val, val) for val in value]
        else:
            actual_value = args_lower_to_actual_dict.get(value, value)
        vars(command_args)[key] = actual_value

    return command_args

def validate_pubsub_port(broker_port):
    valid = True
    error_msg = None
    try:
        port_num = int(broker_port)
        # TCP ports 1 - 1024 are reserved
        if port_num not in range(1025, 65535):
            valid = False
    except ValueError:
        valid = False

    if not valid:
        error_msg = "Invalid port number"

    return valid, error_msg


def validate_pubsub_broker(broker_addr):
    colon_count = broker_addr.count(':')
    port_num = 0
    if colon_count < 2:
        # IPv4
        ipv4_addr = broker_addr
        if colon_count == 1:
            ipv4_addr, port = broker_addr.split(':')
            valid_port, error_msg = validate_pubsub_port(port)
            if not valid_port:
                return False, error_msg

        if not valid_ipv4(ipv4_addr, flags = INET_PTON):
            return False, "Invalid IPv4 address"
    elif colon_count < 9:
        # IPv6
        ipv6_addr = broker_addr
        if colon_count == 8 or broker_addr[0] == '[':
            if broker_addr[0] != '[' or broker_addr.find(']:') == -1:
                return False, "Invalid IP address format"

            ipv6_addr, port = broker_addr[1:].split(']:')
            valid_port, error_msg = validate_pubsub_port(port)
            if not valid_port:
                return False, error_msg

        if not valid_ipv6(ipv6_addr, flags = INET_PTON):
            return False, "Invalid IPv6 address"
    else:
        return False, "Invalid IP address format"

    return True, None

def check_valid_hex_digit(digit):
    try:
        int(digit, 16)
    except:
        return 0
    else:
        return 1

# Wrapper to replace dictionary key with input value recursively
def util_replace_dict_value(inputdict, searchkey, replaceval):
    for key, value in inputdict.items():
        if(key == searchkey):
            inputdict[searchkey] = replaceval
        elif isinstance(value, list):
            for item in value:
                if isinstance(item, dict):
                    for subkey, val in item.items():
                        if(subkey == searchkey):
                            item[searchkey] = replaceval