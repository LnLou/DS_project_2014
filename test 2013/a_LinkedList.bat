g++ -g testLinkedListInt.cc -o a
a > a.txt
fc a.txt testLinkedListInt.txt

g++ -g testLinkedListStr.cc -o a
a > a.txt
fc a.txt testLinkedListStr.txt

g++ -g testLinkedListStr2.cc -o a
a > a.txt
fc a.txt testLinkedListStr.txt

g++ -g testLinkedListInt2.cc -o a
a > a.txt
fc a.txt testLinkedListInt.txt

pause