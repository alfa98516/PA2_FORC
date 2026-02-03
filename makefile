file = main.cpp
out = a.out
warnings = pedantic
std = c++03

make:
	g++ -W$(warnings) -g -std=$(std) $(file) -o $(out)
fast:
	g++ -W$(warnings) -g -Ofast -std=$(std) $(file) -o $(out)
1:
	g++ -W$(warnings) -g -O1 -std=$(std) $(file) -o $(out)
2:
	g++ -W$(warnings) -g -O2 -std=$(std) $(file) -o $(out)
3:
	g++ -W$(warnings) -g -O3 -std=$(std) $(file) -o $(out)
