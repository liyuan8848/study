#!/usr/bin/env  python

from distutils.core import setup, Extension

CswigToPY_module = Extension('_CswigToPY',
                           sources=['CswigToPY_wrap.c', 'uart_packet.c'],
                           )

setup (name = 'CswigToPY',
       version = '0.1',
       author      = "Yuan Li",
       ext_modules = [CswigToPY_module],
       py_modules = ["CswigToPY"],
       )
