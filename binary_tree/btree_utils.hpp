#ifndef __ED_BTree_Utils_HPP__
#define __ED_BTree_Utils_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>

#include "btree.hpp"

#include <algorithm>
#include <queue>

template <class T>
struct Processor
{
    bool operator()(T const& value)
    {
        std::cout << value << " ";
        return true;
    }
};

template<class T>
struct Processor_check_btree_in_order
{
    std::vector<T> vector_;

    Processor_check_btree_in_order()
    {
        vector_.clear(); 
    }

    bool operator()(T const& item)
    {
        vector_.push_back(item);
        return true;
    }

    std::vector<T> vec()
    {
        return vector_;
    }
};

/**
 * @brief Compute the height of a tree.
 * The tree's height is the longitude of the longest branch connecting the root
 * node with a leaf node, or -1 if the tree was empty.
 *
 * @param t is the tree.
 * @return the tree's height or -1 if it is a empty tree.
 * @pre t!=nullptr
 */
template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int ret_val = -1;

    //TODO
    if(not t->is_empty())
    {
    	auto t_left = t->left();

    	auto max_left = -1;

    	if(t_left->is_empty() == false)
    		max_left = compute_height<T>(t_left);

    	auto t_right = t->right();

    	auto max_right = -1;

    	if(t_right->is_empty() == false)
    		max_right = compute_height<T>(t_right);

    	if(max_left > max_right)
    		ret_val = max_left + 1;
    	else
    		ret_val = max_right + 1;

    }

    return ret_val;
}

/**
 * @brief Compute the number of nodes in the tree.
 *
 * @param t is the tree.
 * @return the number of nodes in the tree.
 * @pre t!=nullptr
 * @post t->is_empty() and ret_val==0
 * @post !t->is_empty() and ret_val>0
 */
template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;


    //TODO
    if(not t->is_empty())
  	{
  		ret_val += 1;

  		auto left = t->left();

  		if(left->is_empty() == false)
      		ret_val += compute_size<T>(t->left());

      	auto right = t->right();

      	if(right->is_empty() == false)
  			ret_val += compute_size<T>(t->right());
  	}
    assert(!t->is_empty() || ret_val==0);
    assert(t->is_empty() || ret_val>0);
    return ret_val;
}

/**
 * @brief Prefix processing of a binary tree
 * The template class Processor must have an closure interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */



template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if(tree->is_empty() == false)
    {
    	retVal = p(tree->item());

    	auto left = tree->left();

	    if(left->is_empty() == false)
	    	retVal = retVal && prefix_process<T>(left,p);

	   	auto right = tree->right();

	    if(right->is_empty() == false)
	    	retVal = retVal && prefix_process<T>(right,p);
    }

    return retVal;
}

/**
 * @brief Infix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if(not tree->is_empty())
    {
    	auto left = tree->left();

	    if(left->is_empty() == false)
	    	retVal = infix_process<T>(left,p);

	    retVal = retVal && p(tree->item());

	   	auto right = tree->right();

	    if(right->is_empty() == false)
	    	retVal = retVal && infix_process<T>(right,p);
    }

    return retVal;
}

/**
 * @brief Postfix processing of a binary tree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;

    //TODO
    if(not tree->is_empty())
    {
    	auto left = tree->left();

	    if(left->is_empty() == false)
	    	retVal = postfix_process<T>(left,p);

	   	auto right = tree->right();

	    if(right->is_empty() == false)
	    	retVal = retVal && postfix_process<T>(right,p);

	    retVal = retVal && p(tree->item());
    }

    return retVal;
}


/**
 * @brief Bread-first processing of a btree.
 * The template class Processor must have an apply interface:
 *
 * bool Processor::operator()(T const& item).
 *
 * that makes something with item and returning true when the processing must
 * continue or false to stop it.
 *
 * A lambda expression can be used too.
 *
 * @return true if all nodes were processed.
 * @pre tree!=nullptr
 */
template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool ret_val = true;

    //TODO
    //Hint: may be you need to use std::queue
    std::vector <typename BTree<T>::Ref> cola;

    cola.push_back(tree);

    while(not cola.empty() and ret_val)
    {
    	auto subtree = cola.front();

    	if(not subtree->is_empty())
    	{
    		ret_val = ret_val && p(subtree->item());
   			cola.push_back(subtree->left());
   			cola.push_back(subtree->right());
    	}

    	cola.erase(cola.begin());
    }

    return ret_val;
}

/**
 * @brief Check is a binary tree is in order.
 * A binary tree is in order whether it is the empty tree or
 * when for each subtree, the root node is greater than all its proper left
 * descendants and less than all its proper right descendants.
 *
 * @param tree is the tree to be checked.
 * @return true if the input tree is in order.
 */


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;

    //TODO
    if(tree->is_empty() == false)
    {
        Processor_check_btree_in_order<T> p;

        infix_process<T>(tree,p);

        auto vec = p.vec();

        ret_val = std::is_sorted(vec.begin(),vec.end());
    }
    //
    return ret_val;
}

/**
 * @brief Search a item into the tree.
 *
 * The input tree must be in order, a optimized search process can be used.
 *
 * @param tree is a in order binary tree.
 * @param v is the value to be found.
 * @pre check_btree_in_order(tree)
 * @return true if the value is in the tree.
 */
template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;

    //TODO
    if(tree->is_empty() == false)
    {
    	if(v < tree->item())
    	{
    		auto left = tree->left();

    		if( left->is_empty() == false)
    			ret_val = has_in_order<T>(left,v);
    	}
    	else if(v > tree->item())
    	{
    		auto right = tree->right();

    		if( right->is_empty() == false)
    			ret_val = has_in_order<T>(right,v);
    	}
    	else
    	{
    		ret_val = true;
    	}
    }
    return ret_val;
}

/**
 * @brief Insert in orde a value intro a binary tree.
 * @see check_btree_in_order to know what is mean this.
 * If the value is already in tree, nothing is inserted.
 *
 * @param tree is the tree where inserting.
 * @param v is the value to be inserted.
 *
 * @pre check_btree_in_order(tree)
 * @post has_in_order(tree, v)
 */
template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));

    //TODO
    if(tree->is_empty())
    {
    	tree->create_root(v);
    }
    else if(v < tree->item())
    {
    	if(tree->left()->is_empty())
    	{
    		auto l_tree = BTree<T>::create();
    		l_tree->create_root(v);
    		tree->set_left(l_tree);	
    	}
    	else
    	{
    		auto aux = tree->left();
    		insert_in_order<T>(aux,v);
    		tree->set_left(aux);
    	}
    }
    else if(v > tree->item())
    {
    	if(tree->right()->is_empty())
    	{
    		auto r_tree = BTree<T>::create();
    		r_tree->create_root(v);
    		tree->set_right(r_tree);	
    	}
    	else
    	{
    		auto aux = tree->right();
    		insert_in_order<T>(aux,v);
    		tree->set_right(aux);
    	}
    }
    //
   assert(has_in_order<T>(tree, v));
}



#endif
