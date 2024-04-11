# OpenGL template
This is a project with setups to work with opengl on linux (freeglut) with vscode as the main editor.

## Prequisted
- freeglut
```bash
sudo apt-get install freeglut3-dev
```
- vscode
## Build & Run
- __Build__:

**In c:** 
```bash
gcc main.c -lGL -lGLU -lglut 
```
**In cpp:**
```bash
g++ filename.c -lGL -lGLU -lglut
```
- __Run__:
```bash
./main
```
### Debug with vscode
Config files **.vscode** folder as my setting.
