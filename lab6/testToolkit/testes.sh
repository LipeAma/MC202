MODE="alloc"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out
echo "---------------------"
MODE="get"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out
echo "---------------------"
MODE="pop"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out
echo "---------------------"
MODE="print"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out
echo "---------------------"
MODE="push"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out
echo "---------------------"
MODE="set"
gcc test-$MODE.c ../dequef.c -c && gcc test-$MODE.o dequef.o -lm && ./a.out