#ifndef __ED_BTree_Utils_HPP__
#define __ED_BTree_Utils_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>


#include "btree.hpp"

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
    int ret_val = 0, leftHeight = 0, rightHeight = 0;
    
    if(t->is_empty()) return -1;;

    //TODO

    leftHeight = compute_height<T>(t->left());
    rightHeight = compute_height<T>(t->right());
    

    if (rightHeight >= leftHeight)
    {
        ret_val = 1 + rightHeight;
        return ret_val;

    }else{

        ret_val = 1 + leftHeight;
        return ret_val;
    }

    
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
    if(t->is_empty()){

        return 0;

    }

    ret_val++;

    ret_val = ret_val + compute_size<T>(t->left());
    ret_val = ret_val + compute_size<T>(t->right());

    
    

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
    
    if (tree->is_empty())
    {
        return true;
    }
    

    if(p(tree->item())==true){
        if(!tree->left()->is_empty())
        prefix_process<T>(tree->left(),p);
        if(!tree->right()->is_empty())
        prefix_process<T>(tree->right(),p);

        return true;

    }
    else{
        return false;
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

    if (tree->is_empty())
    {
        return true;
    }

    if(!tree->left()->is_empty()){
        infix_process<T>(tree->left(),p);
    }
    retVal = p(tree->item());
    if(!tree->right()->is_empty()){
        infix_process<T>(tree->right(),p);
    }
    if(retVal == true){
        return true;
    }
    else{
        return false;
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

    if (tree->is_empty())
    {
        return true;
    }

    if(!tree->left()->is_empty()){
        postfix_process<T>(tree->left(),p);
    }
     if(!tree->right()->is_empty()){
        postfix_process<T>(tree->right(),p);
    }
    if(p(tree->item())==true){

        return true;
    }
     else{

        return false;
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

    
    if (tree->is_empty())
    {
        return true;

    }

    

    if (check_btree_in_order<T>(tree->left()) == false || check_btree_in_order<T>(tree->right()) == false){

        return false;

    }

    if ((tree->right()->is_empty() == false && tree->right()->item() < tree->item()) || (tree->left()->is_empty() == false && tree->left()->item() > tree->item()) )
    {
        return false;

    }else{

        return true;

    }

    
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
    bool ret_val = true;

    //TODO

    if (tree->is_empty())
    {
        return false;
    }
    else
    {
        if (v > tree->item())
        {
            return has_in_order<T>(tree->right(),v);
        }
        else if (v < tree->item())
        {
            return has_in_order<T>(tree->left(),v);
        }

    }

    //

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


    //

    assert(has_in_order<T>(tree, v));
}



#endif
