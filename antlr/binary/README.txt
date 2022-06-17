
pmain.cpp is a stripped down version of pmain from SCLParser (old version)
that finds arp and udp packets and passes them to the generated antler parser.

ByteInputStream is a copy of ANTLRInputStream that takes a wchar32_t array
as data. You have to allocate a byte array and copy the bytes the new array (which
converts them up in the process). The extra cast is to prevent sign extension
since wchar32_t is signed in gcc.

The getText() returns a string of decimal numbers (TODO add spaces) for error message, etc.

cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

output is called parser in the build directory.
