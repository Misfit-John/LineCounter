#don't indent!
debug_var=1
ifeq ($(debug_var),1)
DEBUG_FLAG=-g -DDEBUG
else
DEBUG_FLAG=-DRELEASE
endif

CC=clang
CXX=clang++
AR=ar
PLATFORM_FLAG=-D_UNIX_ $(DEBUG_FLAG) 
INCLUDE_FLAGS=-I./header 
CPP_FLAG=--std=c++0x
LINK_FLAG=-lpthread
TARGET=counter

CFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS)
CPPFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS) $(CPP_FLAG)

SOURCES=$(wildcard ./Core/*.cpp ./*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))
HEADERS=$(wildcard ./header/*.h)

$(TARGET):$(OBJS) 
	@echo "============ make target ============="
	$(CXX) $(OBJS) $(LINK_FLAG) -o $(TARGET)  

release:clean makefile
	@echo "============ release ================="
	make debug_var=0

depend:$(SOURCES) $(HEADERS)
	@echo "============ now generat dpend ======="
	-rm depend
	-@sh ./depend_generator.sh "$(CPPFLAGS)" > /dev/null

clean:
	@echo "============ now clean ==============="
	-rm $(TARGET)
	-rm $(OBJS)
	-rm depend

-include depend

