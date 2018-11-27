# Final-Project
Final project for the C-programming course

The project handles data on global warming from different countries and dates that are organized by date and by country / city.
Constructing an interactive menu that allows you to apply data restriction criteria and display the information handled in different ways, in a Linux terminal.
Development of a graphic mode with the SDL2 library that allows visualizing the evolution of the temperature of the different cities over time.

Compile with:
  gcc *.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o WarmingUp
  
Execute with:
  ./WarmingUp
  "-g" for graphic mode or "-t" for textual mode;
  "-f1" followed by the countries file name;
  "-f2" followed by the cities file name;
