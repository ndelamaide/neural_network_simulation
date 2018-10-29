#include "network.h"
#include "random.h"
#include <algorithm>
#include <iostream>

using namespace std;

void Network::resize(const size_t& n){
  values.clear();
  values.resize(n);
  RNG.normal(values, 0, 1);
}

bool Network::add_link(const size_t& first, const size_t& second){
  bool exists(false);
  vector<size_t> connections(neighbors(first));
  for(auto connection: connections){
    if(connection==second){
      exists=true;
    }
  }
  if((first<values.size()) and (second<values.size()) and (first!=second)
  and (!exists)){
      links.insert(make_pair(first,second));
      links.insert(make_pair(second,first));
    return true;
  } else { return false; }
}


size_t Network::random_connect(const double& mean){
  links.clear();
  size_t connect(0);
  vector<size_t> random_nodes(values.size());
  for(size_t i(0); i < random_nodes.size();++i){
    random_nodes[i]=i;
  }
  RNG.shuffle(random_nodes);
  int size(random_nodes.size());
  for(int i(0); i< size;++i){
    int poisson(RNG.poisson(mean));
    for(int j(0);j<poisson;++j){
      if(add_link(random_nodes[random_nodes.size()-1],j)){
        ++connect;
      }
    }
    random_nodes.pop_back();
    RNG.shuffle(random_nodes);
  }
  return connect;
}

size_t Network::set_values(const std::vector<double>& newV){
  size_t success(0);
  for(int i(0); (i< newV.size()) and (i<values.size()); ++i){
    values[i]=newV[i];
    ++success;
  }
  return success;
}

size_t Network::size() const{
  return values.size();
}

size_t Network::degree(const size_t &_n) const{
  return links.count(_n);
}

double Network::value(const size_t &_n) const{
  return values[_n];
}

vector<double> Network::sorted_values() const{
  vector<double> sorted(values);
  sort(sorted.rbegin(),sorted.rend());
  return sorted;
}

vector<size_t> Network::neighbors(const size_t& k) const{
  auto range(links.equal_range(k));
  vector<size_t> neighbor;
  for(auto i(range.first); i!=range.second; ++i){
    neighbor.push_back(i->second);
  }
  sort(neighbor.rbegin(),neighbor.rend());
  return neighbor;
}
