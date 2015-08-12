CXX = g++
CXXFLAGS = -c -g -Wall -fPIC `root-config --cflags`
ROOTLDFLAGS=`root-config --glibs`
INCLUDE += -I$(JOYROOTROOT)/include
# for shared libraries
LDFLAGS += -shared -Wl,-install_name
#LDFLAGS += -shared -Wl,-soname #gcc4.6
OBJS = Plot1.o Utils1.o

TARGET =libJOYROOT.so

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS),$(TARGET) -o $(TARGET) $(OBJS) $(ROOTLDFLAGS)
	if [ ! -d ${JOYROOTROOT}/lib ]; then mkdir $(JOYROOTROOT)/lib; fi
	ln -sf $(JOYROOTROOT)/src/$(TARGET) ${JOYROOTROOT}/lib/$(TARGET)

$(OBJS): %.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@ 

clean:
	rm $(JOYROOTROOT)/lib/$(TARGET)
	rm $(TARGET)
	rm $(OBJS)
