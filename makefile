#
# PROGRAM:    assignment8.cc
# PROGRAMMER: Margaret Higginbotham
# LOGON ID:   Z1793581
# DATE DUE:   April 18, 2018
#

# Complier Variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assignment8.exe: assignment8.cc
	g++ $(CCFLAGS) assignment8.cc -o assignment8.exe

# Pseudo-target to remove object code and executable files
clean:
	-rm assignment8.exe
