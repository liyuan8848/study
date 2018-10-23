%module CswigToPY

#define __attribute__(x)

%{

#include "uart_packet.h"
#include <stdlib.h>
#include <stdint.h>
#include "addresses_ports.h"

%}

%include "uart_packet.h"
%include "addresses_ports.h"
