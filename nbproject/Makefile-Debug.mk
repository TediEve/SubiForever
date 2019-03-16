#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/bin ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_calib3d400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_core400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_dnn400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_features2d400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_flann400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_gapi400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_highgui400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_imgcodecs400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_imgproc400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_ml400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_objdetect400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_photo400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_stitching400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_video400.dll.a ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_videoio400.dll.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_calib3d400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_core400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_dnn400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_features2d400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_flann400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_gapi400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_highgui400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_imgcodecs400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_imgproc400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_ml400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_objdetect400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_photo400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_stitching400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_video400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/x64/mingw/lib/libopencv_videoio400.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cppapplication_1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../../../../openCV/OpenCV-MinGW-Build-OpenCV-4.0.1-x64/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
