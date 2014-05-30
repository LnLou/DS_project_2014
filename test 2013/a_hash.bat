g++ -g testHashCollision.cc -o a
a > a.txt
fc a.txt testHashCollision.txt

g++ -g testHashMapInt.cc -o a
a > a.txt
fc a.txt testHashMapInt.txt

g++ -g testHashMapStr.cc -o a
a > a.txt
fc a.txt testHashMapStr.txt

pause