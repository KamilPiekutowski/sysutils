#*********************************************************************
# This is the makefile for the Adafruit SSD1306 OLED library driver
#
#       02/18/2013      Charles-Henri Hallard (http://hallard.me)
#                                                       Modified for compiling and use on Raspberry ArduiPi Board
#                                                       LCD size and connection are now passed as arguments on
#                                                       the command line (no more #define on compilation needed)
#                                                       ArduiPi project documentation http://hallard.me/arduipi
#
#       2/23/2021       Kamil Piekutowski (https://github.com/KamilPiekutowski)
#                                                       Modified for compiling with Yocto.
#
# *********************************************************************

prefix := $(DESTDIR)/usr

# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast 
#CCFLAGS=


# define all programs
PROGRAMS = cputemp
SOURCES = ${PROGRAMS:=.c}

all: ${PROGRAMS}

${PROGRAMS}: ${SOURCES}
	$(CC) ${CCFLAGS} -Wall $@.c -o $@

clean:
	rm -rf $(PROGRAMS)
