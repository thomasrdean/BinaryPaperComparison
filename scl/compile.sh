cd $(dirname "$0");
./sclparsergenerator-RestructuredParser/generateParser.sh -T ./sclparsergenerator-RestructuredParser/Txl --input SCL5 --tmp INTERMEDIATE --build BUILD/ --copy;
cd BUILD;
make;
