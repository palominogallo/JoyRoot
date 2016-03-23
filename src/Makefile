CXX = g++
CXXFLAGS = -g -Wall -fPIC `root-config --cflags`
ROOTLDFLAGS=`root-config --glibs`
INCLUDE += -I$(JOYROOTROOT)/include
# for shared libraries
LDFLAGS += -shared -Wl,-install_name
#LDFLAGS += -shared -Wl,-soname

OBJS = Plot1.o Utils1.o mydict.o
MYROOTDICT = mydict.cc
MYROOTDICTH = mydict.h
MYROOTDICTHEADERS = $(JOYROOTROOT)/include/Plot1.hh $(JOYROOTROOT)/include/Utils1.hh $(JOYROOTROOT)/include/LinkDef.hh

TARGET =libJOYROOT.so

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS),$(TARGET) -o $(TARGET) $(OBJS) $(ROOTLDFLAGS)
	if [ ! -d ${JOYROOTROOT}/lib ]; then mkdir $(JOYROOTROOT)/lib; fi
	ln -sf $(JOYROOTROOT)/src/$(TARGET) ${JOYROOTROOT}/lib/$(TARGET)

$(OBJS): %.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ 

$(MYROOTDICT): $(MYROOTDICTHEADERS)
	rootcint -f $@ -c $(CXXFLAGS) $(INCLUDE) -p $^

clean:
	rm $(JOYROOTROOT)/lib/$(TARGET)
	rm $(TARGET)
	rm $(OBJS)
	rm $(MYROOTDICT)
	rm $(MYROOTDICTH)
