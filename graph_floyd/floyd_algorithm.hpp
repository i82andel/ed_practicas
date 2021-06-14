#ifndef __FLOYD_ALGORITHM_HPP__
#define __FLOYD_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"

/**
 * @brief Compute the weight matrix.
 * @arg[in] g is a weighted graph.
 * @arg[out] W is the Weight matrix.
 */
template<class T>
void compute_weight_matrix(WGraph<T>& g, FMatrix& W)
{
    W = FMatrix(g.size(), g.size(),
                std::numeric_limits<float>::infinity());

    //TODO: compute the WMatrix.
    //Hint: scan all the edges. Use the node.label() to index the matrix.
    //Hint: Assume the graph is directed.
    //Hint: Review how to move the cursors.
    for (size_t i = 0;  i < g.size(); i++)
     {
         for (size_t j = 0; j < g.size(); j++)
         {
             if (g.are_adjacent(g.node(i),g.node(j)))
             {
                 W[i][j]=g.edge(g.node(i),g.node(j))->item();
             }
             
         }
         
     }

    //
}

/**
 * @brief Search for the minium path between vertices using the Floyd's algorithm.
 * @arg[in] g is a weighted graph.
 * @arg[out] D is the Distances matrix.
 * @arg[out] I is the Intermediate matrix.
 * @pre the weigths meet the triangular inequality: d(u,v) <= d(u,k) + d(k,v) for all u!=v!=k.
 * @post if none path between u,v exists then D[u][v]==inf and I[u][v]==-1
 * @post if an edge (u,v:w) exists then D[u][v]==w and I[u][v]==-1
 * @post if a path between u,v exits then D[u][v]<inf and D[u][v]==k, k is vertex in the minimum path linking u with v.
 */
template<class T>
void floyd_algorithm(WGraph<T>& g, FMatrix& D, IMatrix& I)
{
    compute_weight_matrix<T>(g, D);
    //Set self-distances to zero.
    for (size_t i=0;i<g.size();++i)
        D[i][i]=0.0;

    I = IMatrix(g.size(), g.size(), -1);

    //TODO: Codify the Floyd algorithm.
        for (int k = 0; k < g.size(); k++)
        {
            for (int i = 0; i < g.size(); i++)
            {
                for (int j = 0; j < g.size(); j++)
                {
                    if (D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        I[i][j] = k;
                    }
                }
            }
        }
    //
}

/**
 * @brief Given the Floyd's Intermidiate matrix, compute the path.
 * @arg[in] u is the label of the start vertex.
 * @arg[in] v is the label of the end vertex.
 * @arg[in] I is the Floyd's Intermidiate matrix.
 * @arg[out] path is a vector with the sequence of vertex's labels for
 *           the minimum path linking u with v.
 * @pre Let D be the Floyd's D matrix corresponding with I, D[u][v]<inf.
 * @post u is the first item of path.
 * @post v is the last item of path.
 */
inline void
floyd_compute_path(size_t u, size_t v, IMatrix const& I,
                   std::vector<size_t>& path)
{
    //Prec: distance (u,v) < inf
    std::stack<std::pair<size_t, size_t>> s;
    path.resize(0);

    //TODO: Find the path.
    //Hint: Think first. Is it necessary to build a binary tree? or it
    //is enough to do an in-depth search using an iterative approach with
    //a stack of pairs (u->v).
    if(u==v){
        path.resize(2);
        path[0]=u;
        path[1]=v;
    }
    else{

    
    auto start=u;
    auto end=v;
    int tam = 0;
    path.resize(tam + 1);
    path[tam] = u;


        while (start != end)
        {
            tam++;
            path.resize(tam + 1);
            start = I[start][end];
            path[tam] = start;
        }
        path.resize(tam + 2);
        path[tam+1] = v;


    }
    


    //
}


#endif //__FLOYD_ALGORITHM_HPP__
