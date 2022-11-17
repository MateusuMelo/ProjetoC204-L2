#include <iostream>
#include <list>
#include <iomanip>
#include <cmath>
#include <string.h>
#include <stdio.h>

using namespace std;

struct no
{
	int v; // vertice adjacente
	int peso; // peso da aresta
};

struct passageiro
{
	int start; // inicio da corrida
	int end; // destino da corrido
};

/*
-------------------------PARA FINS CIENTÍFICOS:---------------------
Coloque quantas horas foram gastas tentando fazer o código funcionar
na parede do programador.

-------------------------HORAS GASTAS: 8h---------------------------

Problemas atuais:

A prioridade deve ser de quem pediu primeiro ou a pessoa mais próxima do uber?

Devemos sair do nosso caminho para pegar uma pessoa que está próxima?
- Se sim devemos continuar o caminho ou ir para um outro caminho mais curto?
- Qual pessoa receberia prioridade a que vai ser mais rápida ou a que chegou primeiro?

--------------------------------------------------------------------
*/





void cria_aresta(list<no>adj[], int nVertices, int u, int v, int p, int orientado)
{
	no aux; //essa variavel vai pegar as variaveis (v ; peso) dentro do struct e vai virar em um nó

	aux.v = v; //estou pegando o v que foi registrado e jogando dentro do struct.v
	aux.peso = p; ////estou pegando o peso que foi registrado e jogando dentro do struct.peso

	adj[u].push_back(aux); //estou jogando no final da fila o auxiliar, e usando o vertice de origem como contador

	if(orientado == 0)
	{
		aux.v = u; //estou pegando o u que foi registrado e jogando dentro do struct.v
		adj[v].push_back(aux); //estou jogando no final da fila o auxiliar, e usando o vertice de origem como contador
	}
}


void dijkstra(list<no>adj[], int nVertices, int start, int end, int &valor, int aux) //var aux 0 - para retornar o custo e 1 - para retonar proxima cidade
{
	int intree[20]; //isso significa se o vertice foi sel
	int distance[20]; //isso é a distancia de um vertice para o seu parente, que inicialmente é infinito
	int parent[20]; //parent é o vertice que o vertice de origem esta conectado
	int weight; //é uma variavel de varredura para o peso de uma aresta de origem/destino
	int destino; //é uma variavel de varredura para o destino de alguma origem
	int dist;
	list <no> :: iterator p;
	int u, v; //contadores
	list <int> lista;
	list<int>::iterator c;

	/*
	O que isso está fazendo é: eu estou declarando que todos os vertices são falsos, ou seja
	eles não estão sendo usados, que a distancia deles são "infinito" e que eles não tem um
	parente (undiscovered)
	*/
	for(u = 0; u < nVertices; u++)
	{
		intree[u] = false; //todo valor de intree é falso (não varrido/não esta sendo usado)
		distance[u] = 100000; //todo valor da distancia de aresta é infinita
		parent[u] = -1; //todo parente é undiscovered
	}

	distance[start] = 0;
	v = start;

	/*
	O objetivo disso é de fazer uma varredura em todos os nossos vertices, no qual a primeira
	instancia vai ser sempre o valor do start, ou seja "intree[start]" vai ser varrido primeiro
	e vamos ficar em loop até tudo estiver reorganizado
	*/
	while(intree[v] == false)
	{
		intree[v] = true;

		/*
		O objetivo disso é varrer os nós do vertice que nós estamos vendo agora
		*/
		for(p = adj[v].begin(); p != adj[v].end(); p++)
		{
			destino = p -> v;
			weight = p -> peso;
			/*
			Esse if vai verificar qual é o menor peso/distancia de cada aresta e guardar o valor
			*/
			if(distance[destino] > distance[v] + weight)
			{
				distance[destino] = distance[v] + weight;
				parent[destino] = v;
			}
		}

		v = 0;
		dist = 100000;
		/*
		Esse for vai pegar o proximo valor de  v para fazermos a varredura
		*/
		for(u = 0; u < nVertices; u++)
		{
			if(intree[u] == false && dist > distance[u])
			{
				dist = distance[u];
				v = u;
			}
		}
	}


	//saida dos valores da lista organizados

	u = end;
	lista.push_front(end);

	while(u != -1)
	{
		lista.push_front(parent[u]);

		u = parent[u];
	}
	lista.pop_front();
	c = lista.begin();
	c++;

	if(aux == 0)
	{
		valor = distance[end];
	}
	else
	{
		valor = *c;
	}
	cout << endl;
}

int cam_custo(list<no>adj[], int nVertices, int start, int end)
{
	int valor;
	dijkstra(adj, nVertices, start, end, valor, 0);

	return valor;
}
int prox_cidade(list<no>adj[], int nVertices, int start, int end)
{
	int valor;
	dijkstra(adj, nVertices, start, end, valor, 1);
	return valor;
}

int chegou(passageiro p[10], int cidade, int contpass)
{
	for(int i = 1; i <= contpass; i++)
	{
		if(p[i].end == cidade)
		{
			return i;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");

	//declarando as variaveis
	int numerov; //numero de vertices
	int grafo = 0; //orientação do grafo 1 - Orientado 0 - Não Orientado
	int u; //vertice de origem
	int v; //vertice de destino
	int contpass = 1; //contagem de passageiros
	int cidade;
	int prioridade = 1;
	int secundario;
	int totalpass; //entrada para a quantidade total de passageiros no carro
	int peso; //peso do vertice
	int fim = 0;
	list<no>adj[10]; //lista de adjacencia
	list <no> :: iterator q;
	passageiro p[10];

	cout << "Informações para o GPS....." << endl;

	cout << "Inicializando o criador de mapa...." << endl;

	cout << endl;

	cout << "Quantos núcleos terão no seu mapa: ";

	//entrada das especificações do grafo
	cin >> numerov; //entrada do numero de vertices do grafo

	cout << endl;

	cout << "Entre com as rotas de cada núcleo - Colocar 0 0 0 ao acabar! " << endl;

	do
	{

		cin >> u; //entrada do vertice de origem
		cin >> v; //entrada do vertice de destino
		cin >> peso; //entrada do peso entre os vertices
		cria_aresta(adj, numerov, u, v, peso, grafo);

	}
	while(u != 0 && v != 0 && peso != 0);


	cout << endl;

	cout << "Crianção do mapa feita....." << endl << endl;

	cout << "Indique sua cidade atual: " << endl;
	cin >> cidade;

	cout << "Inicializando as informações dos passageiros...." << endl;

	cout << endl;

	cout << "Quantidade máxima de lugares: ";

	cin >> totalpass;

	cout << "Quantidade de passageiros: ";

	cin >> contpass;


	for(int i = 1; i <= contpass; i++)
	{
		cout << "Coloque a origem do " << i << " passageiro: ";
		cin >> 	p[i].start; //vertice de destino final da árvore

		cout << "Coloque o destino do " << i << " passageiro: ";
		cin >> p[i].end; //vertice de destino final da árvore

	}
	for(int i = 1; i <= contpass; i++) // Pegando passageiro mais proximo
	{
		cout << cam_custo(adj, numerov, cidade, p[i].start);
		if(cam_custo(adj, numerov, cidade, p[i].start) < cam_custo(adj, numerov, cidade, p[prioridade].start))
		{
			prioridade = i;
		}
	}
	cout << "Menor caminho, passageiro: " << prioridade << " na cidade: " << p[prioridade].start << endl;
	cidade = p[prioridade].start;
	cout << "Indo para a cidade: " << cidade << " - Passageiro: " << prioridade << " embarcado." << endl;

	p[prioridade].start = NULL;
	p[prioridade].start = p[prioridade].end; // retirando o start para nao atrapalhar nas proximas comaprações*/


	cout << cam_custo(adj, numerov, cidade, p[prioridade].start) << endl;
	do
	{
		for(int i = 1; i <= contpass; i++)
		{
			cout << cam_custo(adj, numerov, cidade, 3) << " < "<< cam_custo(adj, numerov, cidade, p[i].start)<<endl;
			if(cam_custo(adj, numerov, cidade, p[prioridade].end) < cam_custo(adj, numerov, cidade, p[i].start)) //Se o custo da proxima cidade da rota for menor que o custo da cidade do proximo passageiro
			{
				cout << "Indo para a cidade: " << prox_cidade(adj, numerov, cidade, p[prioridade].end) << endl;
				cidade = prox_cidade(adj, numerov, cidade, p[prioridade].end);
			}
			else
			{
				cout << "Menor caminho, passageiro: " << i << " na cidade: " << p[i].start << endl;
				cidade = p[i].start;
				cout << "Indo para a cidade: " << cidade << " - Passageiro: " << i << " embarcado." << endl;
				p[i].start = NULL;
				secundario = i;


			}
			if(cidade == p[i].end)
			{
				cout << "Passageiro: " << prioridade << " desembarcado" << endl;
				
				prioridade = secundario;
				fim += 1;
			}


		}


	}
	while(fim != contpass);

	return 0; //retorna 0
}
