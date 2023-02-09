# Fil De Fer

## This project is about representing a landscape as a 3D object in which all surfaces are outlined in lines.
<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/qu-b/FdF?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/qu-b/FdF?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/qu-b/FdF?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/qu-b/FdF?color=green" />
</p>


This is a [42](https://42.fr/en/homepage/) curriculum project. It consists of making wireframe graphics from simple text files. The files are sequences of altitudes to be rendered as a wireframe model.

Here is an example of one those files:
![Text file example](img/text-file-example.png)

The aim is to turn such a file into an isometric projection, using the school's basic graphics library MiniLibX.

![42](img/42.png)

The subject for the assignment can be found [here](subject.pdf).

I decided to go for every bonus, to add spherical projections, colors and bending, in order to make the project more fun.

![turning-42](img/42.gif)


![earth](img/earth.png)
## Build
To build the project, first clone it and then run `make` in the repository.
```bash
git clone --recursive https://github.com/qu-b/FdF.git
```
```bash
make
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
|`[ / ]`| Altitude Modifier + / -|
|`L`| Diagonals ON /OFF|
|`G`| Spherical view ON /OFF|
|`H`| On GEO view Shadow side ON /OFF|
|`I`| Isometric view |
|`P`| Parallel view |
|`R`| Reset |
|`A / W / S / D`| Translation |
|`B / V`| Bend + / -|
|`1`| Earth Color Scheme|
|`2`| Black & White Color Scheme|
|`3`| Blue & Yellow Color Scheme|
|`4`| Neon Color Scheme|
|`ESC`|Close and Exit|

![ocean](img/ocean.png)
![earth](img/flatearth.png)
