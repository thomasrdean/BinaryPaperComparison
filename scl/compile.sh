cd $(dirname "$0");
~/msc/sclparsergenerator/generateParser.sh -T ~/msc/sclparsergenerator/Txl --input SCL5 --tmp INTERMEDIATE --build BUILD/ --copy;
cd BUILD;
make;
