CXXFLAGS = # -DDEBUG
LIBS = -lm

all:  GenOrbitEphem

SRCS = GenOrbitEphem.cpp \
       KeplerianEllipse.cpp \
       EarthKeplerianEllipse.cpp \
       MarsKeplerianEllipse.cpp

OBJS = $(SRCS:.cpp=.o)

GenOrbitEphem:  $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

%.o:  %.c
	$(CXX) -c $<

clean:
	rm GenOrbitEphem *.o
