#include <boost/random.hpp>
#include "common_part.h"

boost::random::mt19937 gen;
int population_size, crossover_size, mutate_probability, elite_selection, generation = 1, time_limit;
double best_fitness = -1;
time_t start;

class Gene{
public:
	vector<int> chromosome;
	double fitness;

	Gene(int l = 0){
		fitness = 0;
		for(int i = 1; i < l; i++) chromosome.push_back(i);
		random_shuffle(chromosome.begin(), chromosome.end());
	}

	bool operator<(const Gene g)const{
		return this->fitness > g.fitness;
	}

	// 突然変異
	void mutate(double per){
		int range = 100;
		boost::random::uniform_int_distribution<> dist(0, range);

		while(per - (int)per > 1e-7){
			range *= 10;
			per *= 10;
		}

		if(per > dist(gen))return;
		boost::random::uniform_int_distribution<> rng(0, chromosome.size()-1);

		for(int apos = rng(gen), bpos = rng(gen); apos < bpos; apos++, bpos--)
			swap(chromosome[apos], chromosome[bpos]);
	}

	void print_route(){
		cout << 0;
		for(int i = 0; i < chromosome.size(); i++)
			cout << "-" << chromosome[i];
		cout << "-" << 0 << endl;
	}
};

vector<Gene> population;
Gene best;

void init_population(){
	cin >> population_size;
	cout << "Population Size: " << population_size << endl;
	
	cin >> crossover_size;
	cout << "Crossover size: " << crossover_size << endl;

	cin >> mutate_probability;
	cout << "Mutate probability: " << mutate_probability << endl;

	cin >> elite_selection;
	cout << "Elite selection: " << elite_selection << endl;

	cin >> time_limit;
	cout << "Time Limit: " << time_limit << endl;

	for(int i = 0; i < population_size; i++)
		population.push_back(Gene(point_num));
}

// 遺伝子評価
void evaluate_gene(Gene* g){
	double dist = distance(points[0], points[g->chromosome[0]]);
	for(int i = 0; i < g->chromosome.size()-1; i++){
		dist += distance(points[g->chromosome[i]], points[g->chromosome[i+1]]);
	}
	dist += distance(points[g->chromosome[g->chromosome.size()-1]], points[0]);
	g->fitness = 1e8 / dist;
}

// 世代評価
void evaluate_population(){
	for(int i = 0; i < population.size(); i++)
		evaluate_gene(&population[i]);

	sort(population.begin(), population.end());

	if(best_fitness < population[0].fitness){
		best_fitness = population[0].fitness;
		best = population[0];
		cout << "result: generation=" << generation << " distance=" << 1e8/best_fitness << " " << time(NULL)-start << "s" << endl;
		cout << '\a';
	}
}

void order_crossover(vector<Gene>* population, vector<int> a, vector<int> b){
	boost::random::uniform_int_distribution<> dist(0, a.size()-1);
	int pos = dist(gen);
	Gene anew, bnew;
	for(int i = 0; i < pos; i++)anew.chromosome.push_back(a[i]);
	for(int i = 0; i < b.size(); i++){
		bool flag = true;
		for(int j = 0; j < pos; j++) flag &= !(b[i] == a[j]);
		if(flag) anew.chromosome.push_back(b[i]);
	}
	for(int i = 0; i < pos; i++)bnew.chromosome.push_back(b[i]);
	for(int i = 0; i < a.size(); i++){
		bool flag = true;
		for(int j = 0; j < pos; j++) flag &= !(a[i] == b[j]);
		if(flag) bnew.chromosome.push_back(a[i]);
	}
	population->push_back(anew);
	population->push_back(bnew);
}

void crossover_population(){
	vector<Gene> next_population = population;
	boost::random::uniform_int_distribution<> dist(0, population.size()-1);

	for(int i = 0; i < crossover_size; i++){
		int apos = dist(gen), bpos = dist(gen);
		while(apos == bpos)bpos = dist(gen);
		order_crossover(&next_population, population[apos].chromosome, population[bpos].chromosome);
	}
	population = next_population;
}

// 集団の特別変異
void mutate_population(double per){
	for(int i=0;i<population.size();i++)
		population[i].mutate(per);
}

void select_population(){
	vector<Gene> next_population;
	for(int i = 0; i < min(elite_selection, (int)population.size()); i++)
		next_population.push_back(population[i]);

	vector<int> sum_fitness(population.size());
	sum_fitness[0] = population[0].fitness;
	for(int i = 1; i < population.size(); i++)
		sum_fitness[i] = sum_fitness[i-1] + population[i].fitness;

	boost::random::uniform_int_distribution<> dist(0, sum_fitness[sum_fitness.size()-1]);

	while(next_population.size() < population_size){
		int pos = (int)(lower_bound(sum_fitness.begin(), sum_fitness.end(), dist(gen))-sum_fitness.begin());
		next_population.push_back(population[pos]);
	}

	population = next_population;
}


int main(){
	gen.seed((unsigned)time(NULL));

	input();
	init_population();

	start = (unsigned)time(NULL);
	evaluate_population();
	while(true){
		if(generation % 10000 == 0)cout << "generation: " << generation  << " " << time(NULL)-start << "s" << endl;
		if(time(NULL)-start >= time_limit)break;
		crossover_population();
		mutate_population(mutate_probability);
		evaluate_population();
		select_population();

		generation++;
	}
	cout << "generation: " << generation  << " Finish!" << endl;
	best.print_route();
}
