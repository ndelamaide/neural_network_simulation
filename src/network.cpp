#include "network.h"
#include "random.h"
#include <algorithm>

using namespace std;

void network::resize(const size_t& n){
  values.clear();
  values.resize(n);
  RNG.normal(values, 0, 1);
}

bool network::add_link(const size_t& first, const size_t& second){
  if(((first<values.size()) and (second<values.size()) and (first!=second))
    and ((make_pair(first,second)!=links.find(first)) and (make_pair(second,first)!=links.find(second)))){
    links.insert(make_pair(first,second),make_pair(second,first));
    return true;
  } else { return false; }
}

size_t network::random_connect(const double& mean){
  for(size_t i(0); i< values.size(); ++i){
    while(add_link(i, RNG.uniform_double(0,values.size())) or (int j(0)<=RNG.poisson(mean))){
      ++j;
    }
  }
}

size_t network::set_values(const std::vector<double>& newV){
  size_t success(0);
  for(int i(0); (i< newV.size()) and (i<values.size()); ++i){
    values[i]=newV[i];
    ++success;
  }
  return success;
}

size_t network::size() const{
  return values.size();
}

size_t network::degree(const size_t &_n) const{
  return links.count(_n);
}

double network::value(const size_t &_n) const{
  return values[_n];
}

vector<double> network::sorted_values() const{
  vector<double> sorted(values);
  sort(sorted.begin(),sorted.end());
  return sorted;
}

vector<size_t> network::neighbors(const size_t& k) const{
  auto range(links.equal_range(k));
  vector<size_t> neighbors();
  for(auto i(range.first); i!=range.second; ++i){
    neighbors.push_back(i->second);
  }
  return neighbors;
}
