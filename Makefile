prog3: prog3.cpp
	g++ -Wall -std=c++17 prog3.cpp -o prog3

clean:
	rm -f *.o prog3 out.txt

run:
	./prog3 -m 2 -c -0.5 -d -1 -1 "test/input9a.txt" -2 "test/input9b.txt"
