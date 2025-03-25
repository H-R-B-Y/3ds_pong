ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules


NAME		:= stupid_pong
BUILD		:= build
SOURCES		:= src src/init
DATA		:=
INCLUDES	:= include
GRAPHICS	:= gfx

EMULATOR	:= $(shell which citra)

# Architecture flags for the ARM11 MPCore (Nintendo 3DS CPU)
# march = armv6k
# This specifies the ARM architecture version being targeted.
# armv6k is an extension of armv6, used in the ARM11 CPU found in the Nintendo 3DS.
# The "k" extension enables certain kernel features like atomic instructions for multiprocessing.

# mtune = mpcore 
# This optimizes the code generation for a specific CPU, in this case, mpcore.
# mpcore refers to the ARM11 MPCore, a multi-core version of the ARM11 CPU used in the 3DS.
# The compiler will schedule instructions in a way that best suits this CPU.

# mfloat-abi = hard
# This instructs the compiler to use hardware floating-point instructions instead of software emulation.
# The 3DS's ARM11 CPU has a VFPv2 (Vector Floating Point) unit, which can handle floating-point math efficiently.
# Using hardware floating-point (hard) is faster than softfp (which allows both hardware and software) or soft (which only uses software emulation).

# mtp = soft
# This controls Thread Pointer (TP) management, which is important for thread-local storage (TLS).
# soft means that the compiler will not assume the existence of a hardware register for TLS but will instead use software-based TLS handling.
# This is useful because the 3DS does not have a dedicated TP register in its CPU.
ARCH    := \
			-march=armv6k \
			-mtune=mpcore \
			-mfloat-abi=hard \
			-mtp=soft

# Compiler flags
CFLAGS	:=	-Wall -Wextra -Werror -Ofast -mword-relocations \
			-ffunction-sections \
			$(ARCH)

CFLAGS  += $(INCLUDE) -D__3DS__

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS	:= -lcitro2d -lcitro3d -lctru -lm

LIBDIRS	:= $(CTRULIB)

IMAGEMAGICK	:=	$(shell which magick)

ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(NAME)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
PNGFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_SOURCES 	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES)) \
				$(PNGFILES:.png=.bgr.o) \

export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES	:=	$(addsuffix .h,$(subst .,_,$(BINFILES))) $(PNGFILES:.png=_bgr.h)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(ICON)),)
	icons := $(wildcard *.png)
	ifneq (,$(findstring $(NAME).png,$(icons)))
		export APP_ICON := $(TOPDIR)/$(NAME).png
	else
		ifneq (,$(findstring icon.png,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.png
		endif
	endif
else
	export APP_ICON := $(TOPDIR)/$(ICON)
endif

ifeq ($(strip $(NO_SMDH)),)
	export _3DSXFLAGS += --smdh=$(CURDIR)/$(NAME).smdh
endif

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
ifneq ($(strip $(IMAGEMAGICK)),)
ifeq ($(findstring System32,$(IMAGEMAGICK)),)

HAVE_CONVERT	:=	yes

endif
endif

ifeq ($(strip $(HAVE_CONVERT)),yes)

all:	$(BUILD)

else

all:
	@echo "Image Magick not found!"
	@echo
	@echo "Please install Image Magick from http://www.imagemagick.org/ to build this example"

endif

#---------------------------------------------------------------------------------
$(BUILD):
	[ -d $@ ] || mkdir -p $@
	$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD)

rem:
	@rm -fr $(NAME).3dsx $(OUTPUT).smdh $(NAME).elf

fclean: clean rem
	@echo fclean ...

re: fclean all

run: all
	@sleep 1 && $(EMULATOR) $(NAME).3dsx & disown

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
ifeq ($(strip $(NO_SMDH)),)
$(OUTPUT).3dsx	:	$(OUTPUT).elf $(OUTPUT).smdh
else
$(OUTPUT).3dsx	:	$(OUTPUT).elf
endif

$(OFILES_SOURCES) : $(HFILES)

$(OUTPUT).elf	:	$(OFILES)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)



#---------------------------------------------------------------------------------
%_bgr.h %.bgr.o: %.bgr
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.bgr: %.png
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(IMAGEMAGICK) $< -rotate 90 $@

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
