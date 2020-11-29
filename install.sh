#!/bin/bash

# Verifica se o caminho informado é válido e corresponde ao AVANTLink
verificar_dir(){
	if [ -d "$path/src" ] && [ -d "$path/include" ] && [ -d "$path/main_test_pathfinding" ] && [ -f "$path/AVANT_main.cbp" ] && [ -f "$path/AVANT_main.depend" ]; then
		
		echo valido
	else 

		[[ 1 -eq 0 ]]
	fi
}

# Script que de fato instala a biblioteca
instalar_bib() {
	
	get_os_info
	

	# Adicionar os dados do OS à URL do repositório
	if [ "$id" = Ubuntu ]; then
		repo_url="http://repos.codelite.org/wx3.0.5/ubuntu/ $codename universe"

	elif [ "$id" = Debian ]; then
		repo_url="http://repos.codelite.org/wx3.0.5/debian/ $codename libs"
		
	fi
	
	
	# Adiciona a chave de autenticação ao apt
	apt-key adv --fetch-keys $key_url
	
	apt-add-repository "deb $repo_url"

	
	# Necessário depois de adicionar a URL ao /etc/apt/sources.list
	apt-get update

	# Finalmente, instala os arquivos. Os seis primeiros são obrigatórios; os outros ranqueados em ordem 
	# decrescente de importância
	apt-get install libwxbase3.0-0-unofficial
	apt-get install libwxbase3.0-dev
	apt-get install	libwxgtk3.0-0-unofficial
	apt-get install libwxgtk3.0-dev
	apt-get install wx3.0-headers
	apt-get install	wx-common
	apt-get install	libwxbase3.0-dbg
	apt-get install	libwxgtk3.0-dbg
	apt-get install	wx3.0-i18n
	apt-get install	wx3.0-examples
	apt-get install	wx3.0-doc
	
	echo " "
	echo "wxWidgets instalado com sucesso"
	echo " "

}


# Só para o usuário confirmar que quer instalar
confirmar() {
	if [ ! -f makefile ]; then
		echo "Não foi possível encontrar o makefile no diretório atual. Se prosseguir, o wxWidgets será baixado, mas o AVANTLink não será montado"
	else
		echo "wxWidgets será baixado, se ainda não tiver sido instalado, e o AVANTLink será montado em seguida"
	fi

	echo "Deseja continuar? (s/n)"
	read resposta
	
	if [ $resposta = "S" ] || [ $resposta = "s" ] ; then
		instalar_bib
	
	elif [ $resposta = "N" ] || [ $resposta = "n" ]; then
		echo "Operação cancelada"
		exit 0

	else
		echo "Caractere inválido. Tente novamente"
		confirmar
	fi
}

# Pega o nome da distro e codename para usar na instalação
get_os_info() {
	if [ -f /etc/os-release ]; then
		. /etc/os-release
		id=$NAME			# e.g. Ubuntu
		codename=$UBUNTU_CODENAME	# e.g. "18.04"
		if [ "$id" = Ubuntu ]; then 
			repo_url="http://repos.codelite.org/wx3.0.5/ubuntu/"
		elif [ "$id" = Debian ]; then
			repo_url="http://repos.codelite.org/wx3.0.5/debian/"
		fi

	elif type lsb_release >/dev/null 2>&1; then
		id=$(lsb_release -si)
		codename=$(lsb_release -sc)
		
	elif [ -f /etc/lsb_release ]; then
		# Para algumas versões do Debian e Ubuntu que não tem o comando lsb_release
		id=$DISTRIB_ID
		codename=$DISTRIB_CODENAME
		
	fi
}


# URL para a chave de autenticação do CodeLite
key_url="http://repos.codelite.org/CodeLite.asc"

# Caminho do AVANTLink
path=$1
path=${path%/}

# Começa a execução daqui
if [ $# -eq 0 ]; then
	path="."
	if [ ! `verificar_dir` ]; then
		echo "O diretório atual não é o AVANTLink. Você pode navegar até ele antes de instalar a biblioteca ou passar o caminho para ele como argumento."
		exit 1
	else
		confirmar
	fi

elif [ ! -d "$path" ]; then
	echo "'$path' não encontrado."
	exit 1

elif [ ! `verificar_dir` ]; then
	echo "'$path' não corresponde ao AVANTLink."
	exit 1

else 
	confirmar

	
fi


src_dir="src"
include_dir="include"
build_dir="build"

[[ ! -d "$build_dir" ]] && mkdir build
[[ -f "$build_dir/"*.cpp ]] && rm "$build_dir/"*.cpp
[[ -f "$build_dir/"*.h ]] && rm "$build_dir/".h
[[ -f "$build_dir/".hpp ]] && rm "$build_dir/"*.hpp

cp "$src_dir/"*.cpp "$build_dir"
cp "$include_dir/"*.h "$build_dir"
cp "$include_dir/"*.hpp "$build_dir"

if [ -f "$path/"makefile ]; then
	make clean
	make all
fi

[[ -d "$build_dir" ]] && rm -r "$build_dir"

exit 0

