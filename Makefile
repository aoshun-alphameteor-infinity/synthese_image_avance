#
# Les variables d'environnement libG3X, incG3X
# sont definies dans le fichier ~/.bashrc par le script ../install.sh
#
#compilateur : gcc ou g++
CC = g++

#compil en mode 'debug' (DBG=yes) ou optmisée (-O2)
DBG = no

ifeq ($(DBG),yes) #en mode debug
  CFLAGS = -g -Wpointer-arith -Wall -I./include -std=c++11
else               #en mode normal
  CFLAGS = -O2 -I./include -I./lib -std=c++11
endif

# assemblage des infos de lib. et inc.
lib = -lGLEW -lGLU -lGL -lglut
# fichiers *.c locaux
src = src/
# fichiers *.h locaux et lib.
inc = inc/
# fichiers *.o locaux
obj = obj/

target = $(obj)shader.o $(obj)matrix.o $(obj)camera.o $(obj)object3D.o $(obj)canonical_sphere.o $(obj)canonical_cube.o $(obj)canonical_tore.o $(obj)canonical_cylinder.o $(obj)canonical_cone.o $(obj)canonical_horn.o $(obj)tree.o $(obj)leaf.o $(obj)node.o $(obj)anim_node.o $(obj)castle.o $(obj)onagre.o $(obj)scene.o $(obj)interface.o $(obj)main.o $(obj)stbi_image.o

all : scene

$(obj)stbi_image.o : lib/stb/stb_image.c
	@echo "librairie stb"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "------------------------"

# règle générique de création de xxx.o à partir de src/xxx.cpp
$(obj)%.o : $(src)%.cpp
	@echo "module $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "------------------------"

# règle générique de création de l'executable xxx à partir de src/xxx.cpp (1 seul module)
% : $(obj)%.o
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

# Règle de compilation de test
scene : $(target)
	@echo "assemblage [$^]->$@"
	@$(CC) $^ $(lib) -o $@
	@echo "------------------------"

.PHONY : clean cleanall ?

# informations sur les paramètres de compilation
? :
	@echo "---------infos de compilation----------"
	@echo "  processeur     : $(PROCBIT)"
	@echo "  compilateur    : $(CC)"
	@echo "  options        : $(CFLAGS)"

clean :
	@rm -f $(obj)*.o
cleanall :
	@rm -f $(obj)*.o scene
superclean : cleanall
	@rm $(src)*.cpp~ Makefile~ $(inc)*.hpp~
