# Version 0.0.2 
# Cedric.Bilat@he-arc.ch
#
# Notes:
#
#	(N1) This configuration file is compiler-free.
#
#	(N2) Go in xxx.mk if you whish customize a specific compiler (where xxx= gcc, xxx = visual, ...).
#
# Conseils:
#
#	(C1) In the below definition of variables, never let a space at the end!!!
#
#	(C2) When you overrid a varaible "XXX+= YYY" be careful to let a space after the symbol "="
#

#################################################
#				Project Configurator	  		#
#################################################

##############################
#      		Basic			 #
##############################

#Name target (without extension)

TARGET_NAME:=Student_OMP

#Target type:
#	EXE 
#	SHARED_LIB
#	STATIC_LIB

TARGET_MODE:=EXE

#################
#	src aux		#
#################

# Expand the src folder.
#	Tip     : All files (.cpp, .h .lib, ...) will be considered recursively !
#	Mimimum : empty

override SRC_AUX+= ../BilatTools_CPP/src/core
override SRC_AUX+= ../BilatTools_OMP/src/core

#################
#  API Ext 		#
#################

# Define preconfigured extern API
#	Tip  	:   See ../PRODUCTION/....../api for available preconfigured api (Boost, openCV, cppTest, ...)
# 	Note	: 	apiXXX.mk define
#					.h for compil-time 
#					.so .lib for link-time
#				but nothing usefull for runtime
#	Usage   :   -include $(API)/XXX.mk
#	Mimimum : empty

include $(API)/openmp.mk
include $(API)/cppTest.mk

#############################
#      		Advanced		#
#############################

# Define compilation variable 
# 	Note	: Same as -DXXX (on command line) or #define XXX (in .ccp code)
#	Mimimum : empty
override CODE_DEFINE_VARIABLES+=#

#################################################
#						End	 			 		#
#################################################
