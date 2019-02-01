CC = g++
SORCES = src/md5.cc
CFLAGS = -shared -fPIC
LFLAGS = -l crypto -l boost_system
TARGET = ./bin/libmd5.so

$(TARGET): $(SOURCES)
	$(CC) $(SORCES) $(CFLAGS) $(LFLAGS) -o $(TARGET)

clean:
	rm $(TARGET)
