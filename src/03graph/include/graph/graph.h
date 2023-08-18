﻿#ifndef GRAPH_H
#define GRAPH_H

#include "common/op_type.h"
#include "edge_info.h"
#include "graph_topo/graph_topo_searcher.hpp"
#include "node_info.h"

namespace refactor::graph {

    template<class T>
    struct Cell {
        mutable T value;
        Cell(T &&value) : value(std::forward<T>(value)) {}
    };

    class GraphMut {
        GraphTopoSearcher<Cell<NodeInfo>, Cell<EdgeInfo>> _topo;
        void fillEdgeInfo();

    public:
        GraphMut(GraphTopo<Cell<NodeInfo>, Cell<EdgeInfo>> &&);
        GraphTopo<NodeInfo, EdgeInfo> intoGraphTopo() const;
    };

    class Graph {
        GraphTopoSearcher<NodeInfo, EdgeInfo> searcher;

    public:
        Graph(GraphTopo<NodeInfo, EdgeInfo> &&);
        GraphTopoSearcher<NodeInfo, EdgeInfo> const &topo() const;
    };

}// namespace refactor::graph

#endif// GRAPH_H
