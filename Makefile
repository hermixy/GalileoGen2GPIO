#
# Copyright 2015 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#

include resources.mk
include $(WIND_USR_MK)/defs.default.mk
include $(WIND_KRNL_MK)/defs.toolfamily.mk
include $(WIND_BUILD_TOOL)/$(TOOL_VERSION)/usr/defs.$(CPU).mk
SOURCEDIR=sources
-include app.mk

CFILES = $(shell find $(SOURCEDIR) -name '*.c')
CXXFILES = $(shell find $(SOURCEDIR) -name '*.cc' -o -name '*.cpp')
ASFILES = $(shell find $(SOURCEDIR) -name '*.s')
OBJS = $(addsuffix .o,$(notdir $(basename $(CFILES)) $(basename $(ASFILES)) $(basename $(CXXFILES))))
OBJ_DIR=obj
VXE_DIR=obj

EXE_STRIP:=$(EXE)
EXE:=$(EXE).debug

$(VXE_DIR)/$(EXE_STRIP): $(VXE_DIR)/$(EXE)
	cp $(VXE_DIR)/$(EXE) $(VXE_DIR)/$(EXE_STRIP)

default: $(VXE_DIR)/$(EXE)

define _catsub
	@echo $1 >> $2

endef

dirname = $(patsubst %/,%,$(dir $1))

$(foreach f, $(CFILES) $(ASFILES) $(CXXFILES), \
    $(eval SRC_DIRS += $(patsubst %/,%,$(dir $f))))

vpath %.c $(SRC_DIRS)
vpath %.s $(SRC_DIRS)
vpath %.cc $(SRC_DIRS)
vpath %.cpp $(SRC_DIRS)

ifneq ($(subst diab,,$(TOOL)),$(TOOL))
EXTRA_DEFINE	+=-O0 -g $(CC_DEBUG_STACK) -Xdebug-dwarf3
else
ifneq ($(subst 4_3_3,,$(TOOL_VERSION)),$(TOOL_VERSION))
EXTRA_DEFINE	+=-O0 -g
else
EXTRA_DEFINE	+=-O0 -g -gdwarf-3
endif
endif

include $(WIND_USR_MK)/rules.rtp.mk
