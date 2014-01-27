#include <boost/random.hpp>
#include <boost/dynamic_bitset.hpp>
using namespace std;

boost::random::mt19937 gen;

class Gene{
public:
	boost::dynamic_bitset<> chromosome;
	int fitness;

	Gene(int l){
		boost::random::uniform_int_distribution<> dist(0, 1);
		chromosome.resize(l);
		for(int i=0;i<chromosome.size();i++){
			chromosome[i] = (bool)dist(gen);
		}
	}

	bool operator<(const Gene &g)const{
		return this->fitness > g.fitness;
	}

	// 突然変異
	void mutate(double per){
		int range = 100;
		while(per - (int)per > 1e-7){
			range *= 10;
			per *= 10;
		}
		boost::random::uniform_int_distribution<> dist(0, range);
		for(int i=0;i<chromosome.size();i++)
			if(per <= dist(gen)) chromosome.flip(i);
	}

	// choromosomeをstringに
	string to_string(){
		string str;
		boost::to_string(chromosome, str);
		return str;
	}
};


// 初期集団生成
void init_population(){
	int population_size,gene_size;

//	cout << "Population Size: ";
	cin >> population_size;
	
//	cout << "Gene Size: ";
	cin >> gene_size;

	for(int i=0;i<population_size;i++){
		population.push_back(Gene(gene_size));
	}
}

// 遺伝子評価
void evaluate_gene(Gene* g){

}

// 世代評価
void evaluate_population(){
	for(int i=0;i<population.size();i++){
		evaluate_gene(&population[i]);
	}
	sort(population.begin(), population.end());

	if(best_fitness < population[0].fitness){
		best_fitness = population[0].fitness;
		cout << "result: generation=" << generation << " fitness=" << best_fitness << " " << time(NULL)-start << "s" << endl;
		cout << '\a';
		//cout << "  gene: " << population[0].chromosome << endl;
	}
}

// 2点交叉
void two_point_crossover(vector<Gene>* next_population, Gene a, Gene b){
	boost::random::uniform_int_distribution<> dist(0, a.chromosome.size()-1);
	int end = dist(gen);
	for(int i=dist(gen);i<end;i++){
		if(a.chromosome[i] != b.chromosome[i]){
			a.chromosome.flip(i);
			b.chromosome.flip(i);
		}
	}
	next_population->push_back(a);
	next_population->push_back(b);
}

// 次世代生成
void generate_population(){
	vector<Gene> next_population;
	next_population.push_back(population[0]);

	vector<int> sum_fitness(population.size());
	sum_fitness[0] = population[0].fitness;
	for(int i=1;i<population.size();i++)
		sum_fitness[i] = population[i].fitness + sum_fitness[i-1];

	cout << sum_fitness[population.size()-1] << endl;
	boost::random::uniform_int_distribution<> dist(0, sum_fitness[population.size()-1]);

	while(next_population.size() < population.size()){
		int apos = (int)(lower_bound(sum_fitness.begin(), sum_fitness.end(), dist(gen))-sum_fitness.begin());
		int bpos = (int)(lower_bound(sum_fitness.begin(), sum_fitness.end(), dist(gen))-sum_fitness.begin());
		two_point_crossover(&next_population, population[apos], population[bpos]);
	}

	population = next_population;
}

// 集団の特別変異
void mutate_population(double per){
	for(int i=0;i<population.size();i++)
		population[i].mutate(per);
}

int main(){
	gen.seed((unsigned)time(NULL));

	start = time(NULL);
	init_population(); //初期集団生成

	double mutate_probaility; cin >> mutate_probaility; //突然変異率

	cout << "init done!" << endl;

	while(true){
		if(time(NULL)-start > 300)break; // 300sで打ち切り
		evaluate_population(); //世代評価
		generate_population(); //次世代生成
		mutate_population(mutate_probaility); //突然変異
		generation++;
	}
}
