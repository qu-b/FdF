# 42 Fil De Fer

This project consists of making wireframe graphics from simple text files. The files are a bunch
of numbers separated by spaces, which can be considered as altitudes. Each number can therefore be
thought of as a 3-dimensional vector, with x and y coordinates corresponding to the respective
horizontal and vertical positions in the file, and the altitude itself is the z-coordinate.

Here is an example of one these files:
![Text file example](img/text-file-example.png)
The aim of the project is to turn into something like this, using the basic graphical library MiniLibX:

![42](img/42.png)

The first challenge was to transform the data into a usable format. In order to do so, I used the get_next_line() function I created in a previous project, which enables the program to parse the text file line by line. I then use a split() function to split each line using the spaces as separator, which means I can store each number in an integer matrix, with the atoi() function. This caused me some problems when I tried to get a spherical projection from the data, so I ended up converting the integer matrix into an array of 3-dimensional vectors. Using vectors meant it was easier to convert the cartesian coordinates to polar coordinates, and thus create pretty spherical projections like these:

![mars](img/mars.png)
![earth](img/earth.png)
![ocean](img/ocean.png)
