# Copyright (C) Microsoft Corporation. All rights reserved.

# This program is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

from __future__ import print_function
import __builtin__

from utils import completion_code, set_failure_dict
from datetime import datetime

global tab
tab = '    '


#######################################################
# Override system functions for Print
#######################################################
def ocsprint(*args, **kwargs):
    """
        Outside of OcsAction need to reference this function
    """
    print (*args, **kwargs)

def print(*args, **kwargs):
    """
       Override function for print
    """
    return __builtin__.print(*args, **kwargs)

# print collection in a sorted order
def print_response(d, indent=0, tablen=0):
    """
        print response from the command.    
    """
    try:
        if completion_code.cc_key in d:
            code = d.pop(completion_code.cc_key, None)              
            if tablen == 1:
                print_response(d, 0, 1)
            else:
                print_response(d)               
            print_value (completion_code.cc_key, code, indent, tablen)
             
        else:
            for k, v in sorted(d.iteritems()):
                if hasattr(v, "keys"):
                    print_header (k, indent, tablen)
                    print_response (v, indent + 1, tablen)
                elif isinstance (v, list):
                    print_header (k, indent, tablen)
                    for i in v:
                        if (hasattr (i, "keys")):
                            print_value (None, "{", indent, tablen)
                            print_response (i, indent + 1, tablen)
                            print_value (None, "}", indent, tablen)
                        else:
                            print_value (None, i, indent + 1, tablen)
                elif isinstance (v, datetime):
                    print_value (k, v.strftime ("%Y-%m-%d %H:%M:%S"), indent, tablen)
                else:
                    print_value (k, v, indent, tablen)
                    
    except Exception,e:
        ocsprint("Exception:",e)

# print collection in a sorted order
def print_log_response(d, indent=0, tablen=0):
    """
        print response from the command.    
    """
    try:
        if completion_code.cc_key in d:
            code = d.pop(completion_code.cc_key, None)              
            if tablen == 1:
                print_log_response(d, 0, 1)
            else:
                print_log_response(d)               
            print_value (completion_code.cc_key, code, indent, tablen)
             
        else:
            for k, v in (d.iteritems()):
                if hasattr(v, "keys"):
                    print_header (k, indent, tablen)
                    print_log_response (v, indent + 1, tablen)
                elif isinstance (v, list):
                    print_header (k, indent, tablen)
                    for i in v:
                        if (hasattr (i, "keys")):
                            print_value (None, "{", indent, tablen)
                            print_log_response (i, indent + 1, tablen)
                            print_value (None, "}", indent, tablen)
                        else:
                            print_value (None, i, indent + 1, tablen)
                elif isinstance (v, datetime):
                    print_value (k, v.strftime ("%Y-%m-%d %H:%M:%S"), indent, tablen)
                else:
                    print_value (k, v, indent, tablen)
                    
    except Exception,e:
        ocsprint("Exception:",e)

def print_header (k, indent, tablen):
    """
    Print the header for a group of information.
    """
    
    if tablen == 1:
        output=  ('\t' * (indent+1)+"{0} : ".format(k))
        print (output)
    else: 
        output=  (tab * (indent+1)+"{0}: ".format(k))
        print (output)
        
def print_value (k, v, indent, tablen):
    """
    Print a single response value.
    """
    
    if tablen == 1:
        output=  ('\t' * (indent+1)) + ("{0} : {1}".format(k, v) if (k) else "{0}".format (v))
    else:
        output=  (tab * (indent+1)) + ("{0}: {1}".format(k, v) if (k) else "{0}".format (v))
        
    print (output)

# Remove empty dictionaries and empty keys from the parent dictionary
def remove_empty_dict(data):
    try:
        new_data = {}
        for key,value in data.items():
            if isinstance(value,dict):
                value = remove_empty_dict(value)
            if not value in (u'', None, {}):
                new_data[key] = value  
        return new_data
    except Exception, e:
        return set_failure_dict("Failed to remove empty dict()", completion_code.failure)   

# Removes empty dictionary from parent dictionary 
def del_dictionary(data):
    for key, val in data.items():
        if val == {}:
            del data[key]
    return data
