# OpenGL simple template
This is a project with setups to work with opengl on linux (freeglut) with vscode as the main editor.

## Prequisted
- freeglut
```bash
sudo apt-get install freeglut3-dev
```
- vscode
## Build & Run
- __Build__:


```bash
// C++
g++ -g main.cpp -std=c++11 src/*.cpp -lGL -lGLU -lglut -lm -Iinclude -Isrc -o main
```
- __Run__:
```bash
./main
```
### Debug with vscode
Config files **.vscode** folder as my setting.

## Others
Useful tools: [HTML color code](https://html-color.codes/image) extract code of colors within an image or a picture. 
