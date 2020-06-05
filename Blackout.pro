OBJECTS_DIR = ./obj

SOURCES += main.cpp \
           src/Blackout.cpp \
	       src/Configuration.cpp \
	       src/Dictionary.cpp \
	       src/Random.cpp \
	       src/Statistics.cpp

HEADERS += src/Blackout.hpp \
	       src/Random.hpp

LIBS    += -lboost_program_options
