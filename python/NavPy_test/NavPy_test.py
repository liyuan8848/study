# -*- coding: utf-8 -*-
import numpy as np
import navpy


ned = [0,0,1]
lat_ref, lon_ref, alt_ref = 45.0, -93.0, 250.0 # deg, deg, meters
ecef = navpy.ned2ecef(ned, lat_ref, lon_ref, alt_ref)
ecef2 = navpy.lla2ecef(lat_ref, lon_ref, alt_ref,model='wgs84')
print "ecef %r" % (ecef)
print "ecef2%r" %(ecef2)
