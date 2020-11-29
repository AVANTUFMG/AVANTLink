# TODO
# - adicionar flags para o compilador (entendo nada disso)
# ---------------------------------------------------------------------------

# Definindo algumas variáveis
#

PROJ_NAME=Cordyceps
SRC_FILES=$(wildcard ./build/*.cpp)
H_FILES=$(wildcard ./build/*.h)
OBJECTS:=$(patsubst ./build/%.cpp,./obj/%.o,$(wildcard ./build/*.cpp))


CXX=$(shell wx-config --cxx)
CXX_FLAGS=

WX_LIBS=$(shell wx-config --libs)
WX_CXXFLAGS=$(shell wx-config --cxxflags)

# ---------------------------------------------------------------------------
# Compilação e linkagen
#

all: prep $(PROJ_NAME)


$(PROJ_NAME): $(OBJECTS)
	@ echo "------------------------------------------------------------"
	@ echo "Compilação finalizada. Partindo para etapa de linkagen"
	@ echo " "
	@ echo "Fazendo o binario usando o $(CXX) linker"
	@ echo " "
	@ $(CXX) -o $(PROJ_NAME)  $(OBJECTS) $(WX_LIBS)
	@ echo "------------------------------------------------------------"
	@ echo "$(PROJ_NAME) criado com sucesso!"
	@ rm -r build
	@ echo " "


./obj/%.o: ./build/%.cpp
	@ echo "Compilando arquivo usando o $(CXX)"
	@ $(CXX) $(WX_CXXFLAGS) -c -o $@ $<
	@ echo " "


prep:
	@ if [ ! -d "./obj" ]; then mkdir obj; fi
	@ if [ ! -d "./build" ]; then mkdir build; fi
	@ rm build/*.cpp
	@ rm build/*.h
	@ rm build/*.hpp
	@ cp src/*.cpp build/
	@ cp include/*.h build/
	@ cp include/*.hpp build/


clean:
	@ rm -f ./obj/*.o $(PROJ_NAME)
	@ if [ -d "./obj" ]; then rmdir obj; fi

.PHONY: all prep clean

