# rvg-containers

Welcome to rvg-containers, a fixed container repo with header only implementation.

This is a repo about fixed containers, its very work in progress and it is made to be used in a game engine that I work and at the moment.

It's not made to follow any standards or how mostly code, I will try be the most consistent possible but will adapt as I need (and learn more).

I plan to move to a different build system (well we really not need a build system, but at the moment it's easier for me to test in this sandbox app) in the future (still need to learn them).

The main purpose is simple of use AND SPEED, memory usage might be a bit higher (not much). 
This containers focus is lower sized containers (10000-).
Classes like fixed_vector really shouldn't have any issues with bigger sizes, but classes like fixed_map implement the map in a vector style with linear search, which will perform worse in larger size compared to a implementation like std::unordered_map (find/erase), while should give way better performance while iterating.

Feel free to contact me on discord Rovug#1023 for anything about the containers.


## (PT-BR / Google Translate)

Bem-vindo ao rvg-containers, um repositório de contêiner fixo com implementação somente de cabeçalho.

Este é um repositório sobre containers fixos, ele é feito para ser usado em um motor de jogo que eu trabalho e no momento está muito em andamento.

Não é feito para seguir nenhum padrão ou como código, tentarei ser o mais consistente possível, mas adaptarei conforme necessário (e aprenderei mais).

Pretendo mudar para um sistema de compilação diferente (bem, realmente não precisamos de um sistema de compilação, mas no momento é mais fácil para mim testar neste aplicativo sandbox) no futuro (ainda preciso aprendê-los).

O objetivo principal é simples de usar E VELOCIDADE, o uso de memória pode ser um pouco maior (não muito). O foco deste contêiner são contêineres de tamanho menor (10000-).

Sinta-se à vontade para entrar em contato comigo no Discord Rovug#1023 para qualquer coisa sobre os contêineres.
