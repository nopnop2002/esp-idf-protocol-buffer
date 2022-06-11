# esp-idf-protocol-buffer
Example of Google Protocol Buffers Serialize and Deserialize with ESP-IDF.   

In MQTT for IoT devices, JSON is used as the serialization format of the message.   
However, for low-performance hardware, JSON parsing in C is a heavy load.   
So when I was looking for a good serialized format that could be implemented in C, I found protobuf.

ESP-IDF includes [this](https://developers.google.com/protocol-buffers/) Google Protocol Buffers library.   
You can use Protocol Buffers components as standard.   
But there is no example code in ESP-IDF.   

I ported from [this](https://github.com/protobuf-c/protobuf-c/wiki/Examples).


# Installation
```
git clone https://github.com/nopnop2002/esp-idf-protocol-buffer
cd esp-idf-protocol-buffer
idf.py flash monitor
```

- Serialize
```
I (328) MAIN: Writing 4 serialized bytes
I (338) MAIN: 0x3ffaff78   08 0a 10 02                                       |....|
```
- DeSerialize
```
I (338) MAIN: deserialize: a=10
I (348) MAIN: deserialize: b=2
```



# How to use Protocol Buffers

### Install protobuf-c-compiler and c-library in ubuntu
```
sudo apt install protobuf-c-compiler libprotobuf-c-dev
```

### Make define file
```
$ cat amessage.proto
syntax = "proto2";

message AMessage {
  required int32 a=1;
  optional int32 b=2;
}
```

### Compile define file
protoc-c generates header files and source code.   
```
$ protoc-c --c_out=. amessage.proto

$ ls amessage.*
amessage.pb-c.c  amessage.pb-c.h  amessage.proto
```

### Copy header files and source code in your project
```
$ cp amessage.pb-c.* /your_project/main/
```

