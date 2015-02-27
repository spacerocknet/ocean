#!/bin/sh
echo "Generate C# API code from protobuf"
PROTO_CSHARP_PORT=/home/hongsan/setup/protobuf-csharp-port
protoc --proto_path=../api ../api/comm.proto --include_imports --descriptor_set_out=comm.pb
mono $PROTO_CSHARP_PORT/tools/ProtoGen.exe comm.pb -output_directory=../client/client
rm comm.pb