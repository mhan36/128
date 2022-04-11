#include "trivial_graph.hpp"

#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <utility>

void TrivialGraph::AddEdge(const std::string& v1, const std::string& v2) {
  if (!VertexInGraph(v1) || !VertexInGraph(v2)) {
    throw std::invalid_argument("not in graph");
  }
  GetAdjacencyList(v1).push_back(v2);
  GetAdjacencyList(v2).push_back(v1);
}

void TrivialGraph::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");
  graph_.insert(std::pair(vertex, std::list<std::string>()));
}

std::vector<std::string> TrivialGraph::DepthFirstTraversal(const std::string& origin) {
  std::string start = origin;
  std::vector<std::string> traversal;
  std::vector<std::string> seen;
  
  std::stack<std::string> stack;
  stack.push(start);
  seen.push_back(start);
  
  while(!stack.empty()) {
    
    start = stack.top();
    stack.pop();
    
    bool vis = false;
    for (std::string visit : traversal) {
      if (visit == start) {
        vis = true;
      }
    }
    
    if (!vis) {
      //std::cout << "now on vertex:  " << start << std::endl;
      traversal.push_back(start);
    } else {
      continue;
    }
    
    for (std::string str : GetAdjacencyList(start)) {
      bool vis = false;
      for (std::string visit : traversal) {
        if (visit == str) {
          vis = true;
        }
      }
      
      if (!vis) {
        bool saw = false;
        for (std::string node : seen) {
          if (node == str) {
            saw = true;
          }
        }
        
        if (saw) {
          continue;
        } else {
          seen.push_back(str);
          stack.push(str);
        }
        
        //std::cout << "push onto stack: " << str << std::endl;
     

      } else {
        continue;
      }
    }
    
  }
  

  return traversal;
}

std::list<std::string>& TrivialGraph::GetAdjacencyList(
    const std::string& vertex) {
  return graph_.find(vertex)->second;
}

bool TrivialGraph::VertexInGraph(const std::string vertex) {
  if (graph_.find(vertex) != graph_.end())
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const TrivialGraph& graph) {
  os << "Contents:" << std::endl;

  for (const auto& pair : graph.graph_) {
    os << "  " << std::setw(15) << pair.first << ": [";
    int i = pair.second.size() - 1;
    for (const auto& list_entry : pair.second) {
      os << list_entry;
      if (i != 0)
        os << ", ";
      i -= 1;
    }

    os << "]" << std::endl;
  }

  return os;
}
