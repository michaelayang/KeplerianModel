CXXFLAGS = # -DDEBUG
LIBS = -lm

all:  ProjectMarsToEarthSky

SRCS = ProjectMarsToEarthSky.cpp

OBJS = $(SRCS:.cpp=.o)

ProjectMarsToEarthSky:  $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

%.o:  %.c
	$(CXX) -c $<

clean:
	rm ProjectMarsToEarthSky *.o
