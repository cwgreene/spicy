cppspice: test_spice.cpp
	g++ -std=c++20 -I ${HOME}/.local/include -L ./lib -Wl,-rpath '$$ORIGIN/lib' test_spice.cpp -lngspice -o cppspice
optspice: test_spice.cpp
	g++ -std=c++20 -I ${HOME}/.local/include -L ./lib -Wl,-rpath '$$ORIGIN/optlib' test_spice.cpp -lngspice -o optspice 
ngspice:
	ngspice -b test.spice
