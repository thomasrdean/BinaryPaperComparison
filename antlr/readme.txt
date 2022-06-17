you need to get the antlr jar and the antlr c++ runtime, then unpack the runtime

actually, the jar is in here and the zip of the runtime is in here too (for versioning or whatever)

do
`rm -r antlr4cpp`
`unzip antlr4-cpp-runtime-4.10.1-source.zip -d antlr4cpp`
`cd binary/build`
`cmake -DCMAKE_BUILD_TYPE=Debug ..`
`make`
`./parser <pcap>`
