cppspice: test_spice.cpp
	g++ -I ${HOME}/.local/include -L ./lib -Wl,-rpath '$$ORIGIN/lib' test_spice.cpp -lngspice -o cppspice
ngspice:
	ngspice -b test.spice
