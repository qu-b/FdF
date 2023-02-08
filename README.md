# Fil De Fer
## This project is about representing a landscape as a 3D object in which all surfaces are outlined in lines.

This is a [42](https://42.fr/en/homepage/) curriculum project. It consists of making wireframe graphics from simple text files. The files are sequences of altitudes to be rendered as a wireframe model.

Here is an example of one those files:
![Text file example](img/text-file-example.png)

The aim is to turn such a file into an isometric projection, using the school's basic graphics library MiniLibX.

![42](img/42.png)

The subject for the assignment can be found [here](subject.pdf).

I decided to go for every bonus, to add spherical projections, colors and bending, in order to make the project more fun.

![turning-42](https://j.gifs.com/mq9RJR.gif)


![earth](img/earth.png)
## Build
To build the project, first clone it and then run `make` in the repository.
```bash
$ git clone --recursive https://github.com/qu-b/FdF.git
```
```bash
$ make
```
## Run
```bash
./fdf maps/example_map.fdf
```
![mars](img/mars.png)

## Program Controls

|Key|Action|
|---|---|
|`Up / Down`| Y axis Rotation|
|` Left / Right`| X axis Rotation|
|`< / >`| Z axis Rotation|
|`+ / -`| Zoom |
|`] / [`| Altitude Modifier + / -|
|`L`| Diagonals ON /OFF|
|`G`| Spherical view ON /OFF|
|`H`| On GEO view Shadow side ON /OFF|
|`I`| Isometric view |
|`P`| Parallel view |
|`R`| Reset |
|`A / W / S / D`| Translation |
|`B / V`| Bendg + / -|
|`1`| Earth Color Scheme|
|`2`| Black & White Color Scheme|
|`3`| |
|`4`| Neon Color Scheme|
|`ESC`|Close and Exit|

![ocean](img/ocean.png)
![earth](img/flatearth.png)
