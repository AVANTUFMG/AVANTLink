# TODO
# - adicionar flags para o compilador (entendo nada disso)
# ---------------------------------------------------------------------------

# Definindo algumas variáveis
#

PROJ_NAME=AVANTLink
SRC_FILES=$(wildcard ./build/*.cpp)
H_FILES=$(wildcard ./build/*.h)
OBJECTS:=$(patsubst ./build/%.cpp,./obj/%.o,$(wildcard ./build/*.cpp))


CXX=$(shell wx-config --cxx)

WX_LIBS=$(shell wx-config --libs)
WX_CXXFLAGS=$(shell wx-config --cxxflags)

# ---------------------------------------------------------------------------
# Compilação e linkagen
#

all: obj_folder $(PROJ_NAME)


obj_folder:
	@ if [ ! -d "./obj" ]; then mkdir obj; fi


$(PROJ_NAME): $(OBJECTS)
	@ echo "------------------------------------------------------------"
	@ echo "Compilação finalizada. Partindo para etapa de linkagen"
	@ echo " "
	@ echo "Fazendo o binario usando o $(CXX) linker"
	@ echo " "
	@ $(CXX) -o $(PROJ_NAME)  $(OBJECTS) $(WX_LIBS)
	@ echo "------------------------------------------------------------"
	@ echo "$(PROJ_NAME) criado com sucesso! Digite ./$(PROJ_NAME) e aperte Enter para executá-lo"
	@ echo " "


./obj/%.o: ./build/%.cpp
	@ echo "Compilando arquivo usando o $(CXX)"
	@ $(CXX) $(WX_CXXFLAGS) -c -o $@ $<
	@ echo " "


clean:
	@ rm -f ./obj/*.o $(PROJ_NAME)
	@ if [ -d "./obj" ]; then rmdir obj; fi

.PHONY: all clean

