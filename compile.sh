export LD_LIBRARY_PATH=SFML-2.5.1/lib
g++ main.cpp Game/*.cpp Game/Entities/*.cpp -o game -I SFML-2.5.1/include -L SFML-2.5.1/lib -l sfml-graphics -l sfml-audio -l sfml-window -l sfml-system