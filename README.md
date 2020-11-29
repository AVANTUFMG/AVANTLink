# AVANT_main

Código principal do sistema de controle autônomo embarcado da equipe eletrônica

## Configuração e Monitoramento dos VANTs
O sistema de controle autônomo embarcado inclui um programa que permite configurar e monitorar os VANTs a equipe.

No momento, o programa permite
- [Criar uma missão para o VANT](#criar-missao), composta por
	- Um nome; 
	- Um ponto de partida, que deve ser inserido no formato **<latitude, longitude>** (a altura é 0 por padrão); 
	- Um ponto de chegada (opcional), que deve ser inserido no mesmo formato do ponto de partida. Se um ponto de chegada não for fornecido, todos os dados recebem -200 (um valor impossível para latitude e longitude);
	- Dois pontos de aproximação, um para o ponto de partida e um para o ponto de chegada, fornecidos pelo usuário. Esses pontos são utilizados no cálculo da rota e exigem um valor para altura (mesmo que seja 0). Os dados devem ser inseridos no formato **<latitude, longitude, altura>**;
	-  uma lista de etapas, que podem ser waypoints, inseridos no formato **<latitude, longitude, altura>** ou áreas de busca, inseridas no formato **<número de vértices, distância; x1, y1, x2, y2, ..., xn, yn,>** (note a vírgula após o **yn**); 
	-  e uma lista de velocidades. A velocidade na p-ésima posição da lista corresponde a velocidade para o VANT na p-ésima etapa.

- Salvar uma missão em formato JSON no disco do usuário.
- Carregar, exibir e editar uma missão salva.
- Exibir a missão atual do VANT; a missão que está sendo manipulada pelo usuário no momento

*Nota: os botões de Mostrar Telemetria, Configurar Airframe e Conectar a um VANT são apenas placeholders por enquanto.*

### O que preciso para rodar o programa?

O programa utiliza a biblioteca [wxWidgets](https://www.wxwidgets.org/) para compor a intereface. Por isso, o usuário precisa instalar alguns arquivos extras que são necessários para compilar o código referente à interface.

#### Windows
Se Você deseja compilar e executar o programa utilizando o Visual Studio, siga essas etapas:
1. **Download** - Faça o download do código da biblioteca pelo [site oficial](). Para baixar a versão 3.1.4, a última versão liberada, clique [aqui](https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.4/wxWidgets-3.1.4.zip).
2. **Compilação** - Após o término do download, abra o diretório que acabou de ser baixado e vá em `wxWidgets\build\msw\` e clique na solução mais recente. No meu caso é um arquivo com o nome `wx_vc16.sln`. Após abrir a solução no Visual Studio, clique em `Build -> Batch Build (Compilação -> Compilação em Lotes)`. Uma janela exibindo as opções de compilação será exibida. Clique em `Select All (Selecionar Tudo)` e depois em `Build (Compilar)`. Mas atenção, é muito importante que antes de clicar em Compilar você prepare um episódio de One Piece para assistir porque isso pode levar até cerca de 20 minutos, dependendo do computador. *Se a compilação falhar, clique em `Build -> Batch Build (Compilação -> Compilação em Lotes)` novamente e logo em seguida em `Build (Compilar)` e tente compilar novamente que isso deve resolver.
3. **Configuração do projeto** - Após o fim da compilação, as pastas `lib\vc_lib` e `lib\vc_dll` serão populadas. Assim, você pode adicionar a que deseja (dependendo se quer usar linkagem estática ou dinâmica) como dependência do projeto. Aqui usaremos linkagem estática. O que você precisa fazer é ir nas confgurações das propriedades do projeto. Você pode fazer isso clicando com o botão direito em cima do nome do projeto no gerenciador de arquivos do lado esquerda e depois em `Propriedades`. ![Propriedades](https://imgur.com/a/4S1aeLO) Em `Propriedades`, garanta que está fazendo as alterações para todas as configurações, e não apenas `Debug` ou `Release`. Para isso, basta selecionar `All Configurations (Todas as Configurações)` na caixa de seleção do canto superior esquerdo. ![Todas as Configurações](https://imgur.com/a/PCwGOBi). Agora basta adicionar o caminho para alguns diretórios como dependências. *Obs.: você pode criar uma variável de ambiente cujo valor é o caminho para onde baixou o código fonte do wxWidgets, pois isso facilita na hora de escrever os caminhos para as dependências, mas é opcional. Vou assumir que você criou essa variável e a chamou de WXWIN por uma questão de generalização*. Com a janela de `Propriedades` aberta no Visual Studio, adicione `Configuration Properties -> C/C++ -> General -> Additional Include Directories (Propriedades de Configuração -> C/C++ -> Geral -> Diretórios de Inclusão Adicional` os caminhos `$(WXWIN)\include; $(WXWIN)\include\msvc`. Agora, em `Configuration Properties -> Linker -> General -> Additional Libraries Directories (Propriedades de Configuração -> Vinculador -> Geral -> Diretórios de Bibliotecas Adicionais)` o caminho `$(WXWIN)\lib\vc_lib`. Agora aplique as mudanças clicando em `Apply (Aplicar)` e depois em `OK`. Isso é tudo, espero que o esforço tenha valido a pena.

Por outro lado, se você quiser utilizar a IDE Code::Blocks e deseja compilar a biblioteca a partir do código fonte como instruído para o Visual Studio acima, siga as instruções nesse link: [https://wiki.wxwidgets.org/CodeBlocks_Setup_Guide](#).

Se você quiser baixar apenas os DLLs e utilizar o Code::Blocks para compilar o código do programa com interface, siga as instruções neste link: [https://wiki.wxwidgets.org/Using_wxWidgets_Pre-Built_Binary_in_CodeBlocks](#)

Por fim, se quiser compilar o código via terminal ou alguma outra IDE siga as instruções em [https://github.com/wxWidgets/wxWidgets/blob/master/docs/msw/install.md](#) na seção "Building Applications Using wxWidgets" 


#### GNU/Linux
Usuários do Debian e Ubuntu podem executar o script `install.sh` para baixar os arquivos necessários para sua máquina. O script está incluído no repositório. 

Após baixar o AVANTLink, abra o terminal e execute o seguinte comando (dentro do diretório do AVANTLink ou passando o caminho para o diretório como parâmetro):

```
$ sudo bash install.sh
```
O comando `sudo` é necessário, pois o script usa o `apt` para gerenciar os pacotes e precisa de acesso ao arquivo `/etc/apt/sources.list`.

Após o término do download e instalação, execute os comandos

```
$ make clean	# não é obrigatório, porém recomendado para evitar convergências
$ make all
```
para executar o makefile que irá montar o programa. 

------------------------------

### Como usar o programa

#### Conectar a um VANT

Usado para criar um conexão entre o programa e um VANT para que dados possam ser enviados (e.g. uma missão recém criada) do computador ou recebidos (e.g. telemetria) pelo computador. Ao clicar nesse botão, uma nova tela é exibida com outros dois botões autoexplicativos: Conexão Atual e Nova Conexão.

*No momento, ambos os botões são placeholders*

#### Mostrar Telemetria

Exibe dados de telemetria enviados pelo VANT. Caso não haja um conexão estabelecida, um dialog é exibido.

*Apenas placeholder por ora*

#### Criar missão
Para criar uma missão, basta clicar em **Criar Missão** no menu principal e será exibida uma tela com os campos a serem preenchidos. No entanto, os dados devem ser inseridos em um formato específico, que é o que será abordado neste trecho. Ao clicar no botão, a seguinte tela é exibida:

![tela de criar missão](https://imgur.com/a/ymkob1H "Tela exibida ao clicar em 'Criar Missão")

1. No campo referente ao nome, basta inserir o nome normalmente (e.g. Primeira Missão)

2. No campo referente ao ponto de partida, os dados devem ser inseridos no formato **<latitude, longitude; latitude, longitude, altura>**, no qual a primeira latitude e longitude são as do ponto de partida propriamente dito (altura = 0), e as segundas latitudes, longitudes e a altura são as do ponto de aproximação. O mesmo acontece no campo do ponto de partida, com a diferença que esse não é obrigatório. Caso os dados estejam mal formatados, um dialog será exibido informando o erro ao usuário.

3. Para inserir uma etapa, basta preencher a caixa de texto posicionada acima da caixa de lista que mostra as etapas inseridas e selecionar na caixa de seleção ao lado qual o tipo de etapa. No entanto, há duas etapas possíveis: waypoint e área de busca.
	- Para adicionar um waypoint, basta inserir o texto no formato **<latitude, longitude, altura>** e o sistema reconhecerá que é um waypoint
	- Para adicionar uma área de busca, basta inserir o texto no formato **<# de vértices, distância; x1, y1, ..., xn, yn,>** (essa vírgula no final *não* é um typo) e o sistema reconhecerá como área de busca.

	Caso o formato do texto e o item selecionado na caixa de seleção sejam diferentes, um dialog será exibido informando o a divergência. Para excluir um item da lista de etapas, clique duas vezes e confirme. Para editá-lo, clique nele com o botão direito do mouse e preencha os dados no dialog exibido.
    
4. Para inserir as velocidades não há nada especial: basta digitar o número e clicar em adicionar que a velocidade inserida será adicionada ao final da lista. No entanto, há alguns macetes que podem ser úteis:
	- **<velocidade, p>** adiciona a velocidade na posição *p*
	- **<velocidade, p, n>** adiciona a velocidade *n* vezes a partir da posição *p*
	- **<velocidade, , n>** adiciona a velocidade *n* vezes ao final da lista
	
    Para remover determinada velocidade, clique no item com o botão direito e confirme.
    
Criada a missão, basta clicar no botão Salvar Missão que uma janela do Explorador de Arquivos será exbida. Selecione o local que deseja salvar a missão no seu computador e ela será salva como um arquivo JSON. O usuário pode também enviar a missão para o VANT clicando no botão Enviar Missão para o VANT, caso haja um VANT conectado.


#### Carregar missão
Para carregar e exibir uma missão previamente salva no disco, basta clicar no botão Carregar Missão, selecionar o arquivo usando a janela do Explorador de Arquivos que será exibida e confirmar.

A tela de Carregar Missão contém um botão Editar Missão que leva o usuário ao editor (a mesma tela exibida ao clicar em Criar Missão) para que seja possível editar e salvar a missão carregada caso necessário. Para editar a missão com sucesso, basta seguir o procedimento descrito para criar a missão.

#### Mostrar Missão Atual do VANT

Esse botão funciona quase exatamente como o de carregar missão, a diferença é que ele exibe a missão em execução ao invés de uma carregada dos arquivos do computador.

#### Configurar Airframe
Aqui é possível editar características físicas do avião, como o raio mínimo de curva, velocidade mínima, e etc. Configurações que variam de aeronave para aeronave.

*Também é placeholder até então*
