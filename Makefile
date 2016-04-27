CXXFLAGS = # -DDEBUG
LIBS = -lm

all:  GenOrbitEphem

GenOrbitEphem:  GenOrbitEphem.o KeplerianEllipse.o
	$(CXX) -o $@ GenOrbitEphem.o KeplerianEllipse.o $(LIBS)

%.o:  %.c
	$(CXX) -c $<

clean:
	rm GenOrbitEphem *.o
