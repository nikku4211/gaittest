# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ../gbdk
endif

LCC = $(GBDK_HOME)/bin/lcc
PNG2ASSET = $(GBDK_HOME)/bin/png2asset
ROMUSAGE = tools/romusage
PNG2CHR = tools/pilbmp2nes.py

ifdef COMSPEC
PY := python.exe
else
PY :=
endif

# Set platforms to build here, spaced separated. (These are in the separate Makefile.targets)
# They can also be built/cleaned individually: "make gg" and "make gg-clean"
# Possible are: gb gbc pocket megaduck sms gg
TARGETS=sms gg

# Configure platform specific LCC flags here:
LCCFLAGS_sms     =
LCCFLAGS_gg      =

LCCFLAGS += $(LCCFLAGS_$(EXT)) # This adds the current platform specific LCC Flags

LCCFLAGS += -Wl-j -Wm-ya4 -autobank -Wb-ext=.rel -Wb-v # MBC + Autobanking related flags

P2AMAPTMFLAGS_sms    = -map -maps_only -no_palettes -use_map_attributes -pack_mode sms -b 255
P2AMAPTMFLAGS_gg     = -map -maps_only -no_palettes -use_map_attributes -pack_mode sms -b 255

P2AMAPTMFLAGS = $(P2AMAPTMFLAGS_$(EXT))

P2AMAPTSFLAGS_sms    = -tiles_only -map -bpp 4 -max_palettes 1 -pack_mode sms -b 255
P2AMAPTSFLAGS_gg     = -tiles_only -map -bpp 4 -max_palettes 1 -pack_mode sms -b 255

P2AMAPTSFLAGS = $(P2AMAPTSFLAGS_$(EXT))

P2ASPRGBFLAGS = -bpp 2 -tiles_only -b 255
P2ASPRSMSFLAGS = -bpp 4 -tiles_only -pack_mode sms -b 255

GBDK_DEBUG = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif


# You can set the name of the ROM file here
PROJECTNAME = gaittest
CFLAGS += -I$(OBJDIR) -Wf-Iinclude -Wf-MMD -Wf-Wp-MP

SRCDIR      = src
OBJDIR      = obj/$(EXT)
RESOBJSRC   = obj/$(EXT)/res
RESOBJSRCMAP   = obj/$(EXT)/res/map
RESOBJSRCSPR   = obj/$(EXT)/res/spr
RESDIR      = res
RESMAPDIR		= res/map
RESSPRDIR		= res/spr
BINDIR      = build/$(EXT)
MKDIRS      = $(OBJDIR) $(BINDIR) $(RESOBJSRC) $(RESOBJSRCMAP) $(RESOBJSRCSPR) # See bottom of Makefile for directory auto-creation

BINS	    = $(OBJDIR)/$(PROJECTNAME).$(EXT)
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESMAPDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

# For png2asset: converting map source pngs -> .c -> .o
MAPPNGS    = $(foreach dir,$(RESMAPDIR),$(notdir $(wildcard $(dir)/*.png)))
MAPTSSRCS    = $(MAPPNGS:%.png=$(RESOBJSRCMAP)/%_tiles.c)
MAPTMSRCS    = $(MAPPNGS:%.png=$(RESOBJSRCMAP)/%_map.c)
MAPTSOBJS    = $(MAPTSSRCS:$(RESOBJSRCMAP)/%.c=$(OBJDIR)/%.o)
MAPTMOBJS    = $(MAPTMSRCS:$(RESOBJSRCMAP)/%.c=$(OBJDIR)/%.o)

GBSPRPNGS    = $(foreach dir,$(RESSPRDIR),$(notdir $(wildcard $(dir)/*gb.png)))
SMSSPRPNGS    = $(foreach dir,$(RESSPRDIR),$(notdir $(wildcard $(dir)/*sms.png)))
GBSPRSRCS    = $(GBSPRPNGS:%.png=$(RESOBJSRCSPR)/%.c)
SMSSPRSRCS    = $(SMSSPRPNGS:%.png=$(RESOBJSRCSPR)/%.c)
GBSPROBJS    = $(GBSPRSRCS:$(RESOBJSRCSPR)/%.c=$(OBJDIR)/%.o)
SMSSPROBJS    = $(SMSSPRSRCS:$(RESOBJSRCSPR)/%.c=$(OBJDIR)/%.o)

.PRECIOUS: $(MAPSRCS)

# Builds all targets sequentially
all: $(TARGETS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Use png2asset to convert the png into C formatted tile data
# -c ...   : Set C output file
# Convert .pngs in res/map -> .c files in obj/<platform ext>/src/
$(RESOBJSRCMAP)/%_tiles.c:	$(RESMAPDIR)/%.png
	$(PNG2ASSET) $< $(P2AMAPTSFLAGS) -o $@
	
# Use png2asset to convert the png into C formatted map data
# -c ...   : Set C output file
# Convert .pngs in res/map -> .c files in obj/<platform ext>/src/
$(RESOBJSRCMAP)/%_map.c:	$(RESMAPDIR)/%.png
	$(PNG2ASSET) $< $(P2AMAPTMFLAGS) -o $@
	
# Use png2asset to convert the png into binary formatted tile data
# -c ...   : Set C output file
# Convert .pngs in res/spr -> .c files in obj/<platform ext>/src/
$(RESOBJSRCSPR)/%.c:	$(RESSPRDIR)/%.png
	$(PNG2ASSET) $< $(P2ASPRGBFLAGS) -o $@
	
# Use png2asset to convert the png into binary formatted tile data
# -c ...   : Set C output file
# Convert metasprite .pngs in res/spr/ -> .c files in obj/<platform ext>/src/
$(RESOBJSRCSPR)/%.c:	$(RESSPRDIR)/%.png
	$(PNG2ASSET) $< $(P2ASPRSMSFLAGS) -o $@

# Compile the map pngs that were converted to .c files
# .c files in obj/<platform ext>/src/ -> .o files in obj/
$(OBJDIR)/%.o:	$(RESOBJSRCMAP)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<
	
# Compile the spr pngs that were converted to .c files
# .c files in obj/<platform ext>/src/ -> .o files in obj/
$(OBJDIR)/%.o:	$(RESOBJSRCSPR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# Dependencies (using output from -Wf-MMD -Wf-Wp-MP)
DEPS = $(OBJS:%.o=%.d)

-include $(DEPS)

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) $(CFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) $(CFLAGS) -S -o $@ $<
	
# Convert and build maps first so they're available when compiling the main sources
$(OBJS):	$(MAPTMOBJS) $(MAPTSOBJS) $(GBSPROBJS) $(SMSSPROBJS)

# Link the compiled object files into a .gg ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) $(CFLAGS) -o $(BINDIR)/$(PROJECTNAME).$(EXT) $(MAPTMOBJS) $(MAPTSOBJS) $(GBSPROBJS) $(SMSSPROBJS) $(OBJS)

clean:
	@echo Cleaning
	@for target in $(TARGETS); do \
		$(MAKE) $$target-clean; \
	done

# Include available build targets
include Makefile.targets


# create necessary directories after Makefile is parsed but before build
# info prevents the command from being pasted into the makefile
ifneq ($(strip $(EXT)),)           # Only make the directories if EXT has been set by a target
$(info $(shell mkdir -p $(MKDIRS)))
endif