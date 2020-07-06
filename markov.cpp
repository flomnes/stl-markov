#include <functional>
#include <iostream>
#include <random>
#include <vector>

class MarkovChain {
private:
  std::vector<std::discrete_distribution<int>> gen;
  unsigned state;
public:
  MarkovChain(const std::vector<std::vector<double>>& probabilities, unsigned state = 0) : state{state} {
    checkSize(probabilities);
    gen.reserve(probabilities.size());
    for(size_t ii = 0; ii < probabilities.size(); ii++) {
      const std::vector<double>& p = probabilities[ii];
      gen[ii] = std::discrete_distribution<int>(p.begin(), p.end());
    }
  }

  unsigned process(std::random_device& rd) {
    state = gen[state](rd);
    return state;
  }

  unsigned getState() const {
    return state;
  }

private:
  // Check that the probability matrix has a square shape
  // all rows are the same size : the number of rows
  void checkSize(const std::vector<std::vector<double>>& probabilities) {
    if (probabilities.size() < 1)
      std::cerr << "Empty probability vector" << std::endl;
    size_t s = probabilities.size();
    for(const std::vector<double>& vp : probabilities) {
      if (vp.size() != s) {
        std::cerr << "Wrong probability vector size" << std::endl;
        break;
      }
    }
  }
};


// Example 4x4 Markov chain
// Deterministic example 0 -> 1 -> 2 -> 3 -> 0 -> etc.
// with probability 1
int main()
{
  using namespace std;
  random_device rd;
  MarkovChain mc{{{0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1},{1, 0, 0, 0}}, 0};
  for(int ii = 0; ii < 100; ii++)
    cout << mc.process(rd) << endl;
}
