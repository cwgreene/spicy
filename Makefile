cppspice:
	g++ -I ${HOME}/.local/include -L ./lib -Wl,-rpath '$$ORIGIN/lib' test_spice.cpp -lngspice -o cppspice
