# Simulação Computacional - Incêndio em uma floresta
[![NPM](https://img.shields.io/npm/l/react)](https://github.com/DanSantiago/SimulacaoFloresta/blob/main/LICENCE) 

# Sobre o projeto

O projeto foi desenvolvido durante uma disciplina de introdução a computação científica na graduação como método de introdução a simulações computacionais. A ideia era criar um algoritmo que simulasse uma floresta pegando fogo (com condições de contorno - funciona como uma floresta cilíndrica) dada as condições iniciais.

Na pasta do projeto há três modos do algoritmo: 
1) "florestadados.c" 
2) "florestafinal.c" 
3) "florestaimprime.c"

Em 1, o algoritmo executa o número de simulações definidas e salva em diferentes arquivos os resultados obtidos em cada simulação e também o arquivo da média.

Em 2, o algoritmo executa o número de simulações definidas e salva somente o arquivo o arquivo da média.

Em 3, o algoritmo executa o número de simulações e salva em diferentes arquivos os resultados obtidos em cada simulação e também o arquivo da média. Além disso, faz uma representação visual na tela do que acontece em cada simulação.

A diferença entre os programas consiste na capacidade em executar mais simulações, no "florestaimprime.c" a capacidade é pequena, já que imprime na tela uma representação visual. No "florestadados.c", a capacidade é maior que a anterior mas ainda não é a ideal, já que cria vários arquivos. Já no "florestafinal.c" temos o melhor caso, que roda sem problemas, já que apenas imprime 1 arquivo no final. 

É claro que cada arquivo tem sua função: o 1 serve para validação do arquivo de média (já que você terá acesso a todos os arquivos utilizados no cálculo); o 2 serve para uma explicação do que acontece, já que fica mais fácil com um auxílio visual; o 3 serve para se obter melhores dados, já que é possível executar mais simulações,  obtendo assim, dados mais precisos.


## Demonstração

Como é o caso mais "interessante visualmente", a demonstração é do arquivo "florestaimprime.c"

https://user-images.githubusercontent.com/75077046/194087169-2202c111-7872-499a-ad65-ba03f64f0cd4.mp4

- "Y": representa onde há árvore
- "*": árvore em chama
- ".": cinza (árvore já queimada)
- " ": espaço vazio

# Tecnologias utilizadas
- C

## Bibliotecas utilizadas
- stdio
- stdlib
- unistd

OBS: O algoritmo foi gerado no ambiente Linux e podem ocorrer erros de compatibilidade se executado no ambiente Windows.

# Como executar o projeto

Basta baixar a pasta do projeto, compilar o arquivo desejado (dentre os três disponíveis) com seu compilador de preferência e executar o arquivo gerado.

Algumas variáveis de execução podem ser modificadas caso seja de interesse, uma breve descrição delas:

- L: tamanho da malha
- p: probabilidade de ser árvore naquele sítio
- sims: número de simulações
- stepsmax: número máximo de passos de cada simulação

OBS: Os arquivos gerados estão descritos em colunas, sendo a ordem:

passo | porcentagem de árvores | porcentagem de espaços vazios | porcentagem de cinzas | porcentagem de fogo

# Autor

Daniel Santiago da Silva

https://www.linkedin.com/in/danielssilva13/



