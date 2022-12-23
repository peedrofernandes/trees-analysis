[🇺🇸 🇬🇧 View in English](./README.md)

# Análise de Árvores

## Sobre o que é esse repositório?

Esse repositório é relacionado a um projeto desenvolvido durante a disciplina de **Estrutura de Dados** do curso Bacharelado em Ciência da Computação na Universidade do Estado de Santa Catarina por [Pedro Fernandes](https://github.com/peedrofernandes) e [André Fidelis](), em Novembro de 2022.

O principal objetivo é mensurar a complexidade computacional temporal das operações de inserção das estruturas de árvores de busca mais utilizadas: **Árvore AVL**, **Árvore Rubro-negra** e a **Árvore B**. O projeto foi dividido em duas partes: Uma na **Linguagem C** e a outra em **Python**.

## Primeira parte (C)

Para criar as estruturas das árvores e usá-las, criamos cada estrutura na linguagem C e as colocamos no diretório `./trees`, sendo que cada árvore específica possui seu próprio subdiretório. Dentro de cada um, há uma versão regular da árvore e uma versão com **contador**. Cada uma das versões é composta por um arquivo do tipo `.c` que contém implementações de funções e um `.h` que contém assinaturas de funções e tipos de dados. A versão com contador, basicamente, conta com os mesmos tipos de dados e funções, com a exceção de que cada função possui um parâmetro a mais **qtd**, que é um ponteiro para inteiro que será incrementado a cada operação computacional. Essas operações incluem, entre outras:
- Testes lógicos;
- Atribuições de variáveis;
- Chamadas à funções;
- Chamadas de retorno.

Vale notar que as versões com contador de cada árvore está denotada por `arvore-counter.c` ou `arvore-counter.h` (onde 'arvore' é o nome da árvore em si).

Novamente dentro do diretório `./trees`, há um arquivo `main.c` cuja responsabilidade é usar todas as estruturas de dados até então criadas para criar **arquivos** contendo o **número de operações** em comparação com o **tamanho do arquivo de entrada**. Usamos uma instância da árvore AVL, outra da árvore Rubro-negra e três instâncias da árvore B, sendo os graus de cada árvore 1, 5 e 10, respectivamente. Consideramos **todos os tamanhos de input de dados de 1 até 1000**, almejando criar uma **lista de pontos dispersos** em um gráfico 2D (essa é a segunda parte do trabalho, que será feita em Python). Criamos dois casos para cada árvore: O **pior caso** das operações de inserção, que é o caso no qual o input é ordenado (exigindo mais operações de balanceamento de cada árvore) e um **caso médio** que pseudo-aleatoriamente gera os inputs de dados. Para ter significância estatística, fizemos o caso médio dez vezes, gerando dados aleatórios a cada vez, e consideramos o número de operações de cada caso médio como sendo a média entre os casos.

## Segunda parte (Python)

Dentro da pasta `./image-generators`, há três elementos:
- Uma pasta `venv` cuja responsabilidade é forencer um ambiente virtual para que os pacotes do Python funcionem corretamente;
- `generateScatteredPoints.py` - Um arquivo cujo principal objetivo é gerar os arquivos correspondentes com pontos dispersos. Esse arquivo gera dois outros arquivos dentro da pasta `./files`:
  - `avgCaseScattered.png` - Pontos do caso médio dispersos no gráfico;
  - `worstCaseScattered.png` - Pontos do pior caso dispersos no gráfico;
- `generateRegression.py` - Um arquivo cujo principal objetivo é usar **regressão polinomial** para calcular funções que aproximam o comportamento da complexidade computacional das operações de inserção de cada árvore. Gera dois arquivos no diretório `./files`:
  - `avgCaseFunctions.png` - Funções geradas para representar o caso médio, geradas por regressões polinomiais;
  - `worstCaseFunctions.png` - Funções geradas para representar o pior caso, geradas por regressões polinomiais;

# Como inicializar

Para que você mesmo possa testar o projeto, simplesmente clone o repositório na sua máquina local, usando:

```
git clone https://github.com/peedrofernandes/trees-analysis.git
```

Então, navegue para o diretório no qual você clonou o repositório e rode o seguinte comando:

```
./run.sh
```

Automaticamente, o comando vai fazer tudo o que precisa fazer. Verifique os arquivos gerados (especialmente os arquivos .png) e veja se o resultado se parece com isso:

![worstCaseScattered](https://user-images.githubusercontent.com/82897023/209393267-f071480d-7624-4a4c-bb6e-ec9c66c74264.png)
![worstCaseFunctions](https://user-images.githubusercontent.com/82897023/209393228-454b65f9-cdb3-4589-a004-a6d8b2557576.png)

![avgCaseScattered](https://user-images.githubusercontent.com/82897023/209393218-152be260-e3d7-4526-8f14-137f04aefc1f.png)
![avgCaseFunctions](https://user-images.githubusercontent.com/82897023/209393263-894f8a1a-21a9-44bb-8a65-5b3b352a2bd4.png)

Em caso de erro, por favor, entre em contato:

[![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)](https://github.com/peedrofernandes)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](gm.pedro.fernandes@gmail.com)
[![LinkedIn](https://img.shields.io/badge/linkedin-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)](https://linkedin.com/in/pedrofariafernandes)

Obrigado!
