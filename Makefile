#############################################################################
# Makefile for building: raspberrypi_video
# Generated by qmake (2.01a) (Qt 4.8.6) on: Wed Feb 24 23:25:20 2016
# Project:  raspberrypi_video.pro
# Template: app
# Command: /usr/lib/arm-linux-gnueabihf/qt4/bin/qmake -o Makefile raspberrypi_video.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I../raspberrypi_libs -Igen_mocs
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/arm-linux-gnueabihf -L../raspberrypi_libs/leptonSDKEmb32PUB/Debug -lLEPTON_SDK -lpigpio -lrt -lraspicam -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/arm-linux-gnueabihf/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = gen_objs/

####### Files

SOURCES       = Lepton_I2C.cpp \
		LeptonThread.cpp \
		main.cpp \
		MyLabel.cpp \
		Palettes.cpp \
		SPI.cpp gen_mocs/moc_LeptonThread.cpp \
		gen_mocs/moc_MyLabel.cpp
OBJECTS       = gen_objs/Lepton_I2C.o \
		gen_objs/LeptonThread.o \
		gen_objs/main.o \
		gen_objs/MyLabel.o \
		gen_objs/Palettes.o \
		gen_objs/SPI.o \
		gen_objs/moc_LeptonThread.o \
		gen_objs/moc_MyLabel.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		raspberrypi_video.pro
QMAKE_TARGET  = raspberrypi_video
DESTDIR       = 
TARGET        = raspberrypi_video

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): sdk $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: raspberrypi_video.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/arm-linux-gnueabihf/libQtGui.prl \
		/usr/lib/arm-linux-gnueabihf/libQtCore.prl
	$(QMAKE) -o Makefile raspberrypi_video.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/arm-linux-gnueabihf/libQtGui.prl:
/usr/lib/arm-linux-gnueabihf/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile raspberrypi_video.pro

dist: 
	@$(CHK_DIR_EXISTS) gen_objs/raspberrypi_video1.0.0 || $(MKDIR) gen_objs/raspberrypi_video1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) gen_objs/raspberrypi_video1.0.0/ && $(COPY_FILE) --parents Lepton_I2C.h LeptonThread.h MyLabel.h Palettes.h SPI.h gen_objs/raspberrypi_video1.0.0/ && $(COPY_FILE) --parents Lepton_I2C.cpp LeptonThread.cpp main.cpp MyLabel.cpp Palettes.cpp SPI.cpp gen_objs/raspberrypi_video1.0.0/ && (cd `dirname gen_objs/raspberrypi_video1.0.0` && $(TAR) raspberrypi_video1.0.0.tar raspberrypi_video1.0.0 && $(COMPRESS) raspberrypi_video1.0.0.tar) && $(MOVE) `dirname gen_objs/raspberrypi_video1.0.0`/raspberrypi_video1.0.0.tar.gz . && $(DEL_FILE) -r gen_objs/raspberrypi_video1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) -r $(OBJECTS_DIR) gen_mocs
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


sdk:
	make -C ../raspberrypi_libs/leptonSDKEmb32PUB

sdkclean:
	make -C ../raspberrypi_libs/leptonSDKEmb32PUB clean

check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: gen_mocs/moc_LeptonThread.cpp gen_mocs/moc_MyLabel.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) gen_mocs/moc_LeptonThread.cpp gen_mocs/moc_MyLabel.cpp
gen_mocs/moc_LeptonThread.cpp: /usr/local/include/pigpio.h \
		/usr/local/include/raspicam/raspicam.h \
		/usr/local/include/raspicam/raspicamtypes.h \
		LeptonThread.h
	/usr/lib/arm-linux-gnueabihf/qt4/bin/moc $(DEFINES) $(INCPATH) LeptonThread.h -o gen_mocs/moc_LeptonThread.cpp

gen_mocs/moc_MyLabel.cpp: MyLabel.h
	/usr/lib/arm-linux-gnueabihf/qt4/bin/moc $(DEFINES) $(INCPATH) MyLabel.h -o gen_mocs/moc_MyLabel.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

gen_objs/Lepton_I2C.o: Lepton_I2C.cpp Lepton_I2C.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/Lepton_I2C.o Lepton_I2C.cpp

gen_objs/LeptonThread.o: LeptonThread.cpp LeptonThread.h \
		/usr/local/include/pigpio.h \
		/usr/local/include/raspicam/raspicam.h \
		/usr/local/include/raspicam/raspicamtypes.h \
		Palettes.h \
		SPI.h \
		Lepton_I2C.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/LeptonThread.o LeptonThread.cpp

gen_objs/main.o: main.cpp LeptonThread.h \
		/usr/local/include/pigpio.h \
		/usr/local/include/raspicam/raspicam.h \
		/usr/local/include/raspicam/raspicamtypes.h \
		MyLabel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/main.o main.cpp

gen_objs/MyLabel.o: MyLabel.cpp MyLabel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/MyLabel.o MyLabel.cpp

gen_objs/Palettes.o: Palettes.cpp Palettes.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/Palettes.o Palettes.cpp

gen_objs/SPI.o: SPI.cpp SPI.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/SPI.o SPI.cpp

gen_objs/moc_LeptonThread.o: gen_mocs/moc_LeptonThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/moc_LeptonThread.o gen_mocs/moc_LeptonThread.cpp

gen_objs/moc_MyLabel.o: gen_mocs/moc_MyLabel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gen_objs/moc_MyLabel.o gen_mocs/moc_MyLabel.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

