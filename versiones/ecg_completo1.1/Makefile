# ----------------------------------------------------------------
# Makefile generated by TinyOS-Plugin for Eclipse
# ----------------------------------------------------------------
# Existing and additional environment variables (introduced by the 
# TinyOS-Plugin)
#
# TOSDIR		  :		TinyOS directory
#
# APP_MAKERULES	  :		location of Makerules - file
#						(set by the environment plugin
#						normally that would be tos/apps/Makerules)
#
# ECLIPSE_PROJECT :		the eclipse project directory
# ----------------------------------------------------------------
# Examples:
#	Include Header from the current project (but in subdir)
#		PFLAGS+= -I${ECLIPSE_PROJECT}/headerf/3
#	Include Header-files from another eclipse project:
#		PFLAGS+= -I${ECLIPSE_PROJECT}/../projectname/dir
# 	Include TinyOS directory from the TinyOS-Contrib directory 
#		PFLAGS+= -I${TOSDIR}/../contrib/xbow/beta/TASKApp
# ----------------------------------------------------------------

# ----------------------------------------------------------------
# Makefile generated by TinyOS-Plugin for Eclipse
# ----------------------------------------------------------------
# Existing and additional environment variables (introduced by the 
# TinyOS-Plugin)
#
# TOSDIR		  :		TinyOS directory
#
# APP_MAKERULES	  :		location of Makerules - file
#						(set by the environment plugin
#						normally that would be tos/apps/Makerules)
#
# ECLIPSE_PROJECT :		the eclipse project directory
# ----------------------------------------------------------------
# Examples:
#	Include Header from the current project (but in subdir)
#		PFLAGS+= -I${ECLIPSE_PROJECT}/headerf/3
#	Include Header-files from another eclipse project:
#		PFLAGS+= -I${ECLIPSE_PROJECT}/../projectname/dir
# 	Include TinyOS directory from the TinyOS-Contrib directory 
#		PFLAGS+= -I${TOSDIR}/../contrib/xbow/beta/TASKApp
# ----------------------------------------------------------------
#
#COMPONENT=Rpeak
#PFLAGS += -I%T/lib/NetworkGenericComm -I%T/lib/Counters
#PFLAGS += -I%T/lib/Util
#ifdef APP_MAKERULES
#include $(APP_MAKERULES)
#else
#ifdef APP_MAKERULES
##include $(APP_MAKERULES)
#else
#include ../Makerules
#endif
#endif

# Based on original Surge application, but explicitly includes a qsort() implementation
# to work around the lack of this function in msp430-libc needed for MultiHopLEPSM.nc
COMPONENT = TOSwqrs

PFLAGS += -I%T/lib/Route -I%T/lib/Queue -I%T/lib/Broadcast -I%T/lib/NetworkGenericComm -I%T/lib/Counters

#!!!!Alex added this line
#PFLAGS += -I%T/platform/pc/CC1000Radio
PFLAGS += -I%T/platform/pc/nRF2401RadioShockBurst #FRAN
#PFLAGS += -I%T/platform/pc/nRF2401RadioShockBurst_31-07-07_12.39 #FRAN

#ifneq ($(filter telos% tmote,$(PLATFORM)),)    # FIXME: does not work... workaround:
#   CFLAGS += -DCC2420_RADIO                    # must define CFLAGS on command line
#endif

ifeq ($(PLATFORM), imec)
    CFLAGS += -DPLATFORM_IMEC
endif

ifeq ($(PLATFORM), imec_usb)
    CFLAGS += -DPLATFORM_IMEC
endif

include ../Makerules
