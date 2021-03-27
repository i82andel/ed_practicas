#ifndef __ED_BTree_HPP__
#define __ED_BTree_HPP__

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

/** @brief a BTree's Node.*/
template <class T>
class BTNode
{
public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTNode<T> > Ref;

    /** @name Life cicle.*/
    /** @{*/

    /** @brief Create a BTNode.
     * @post n_children() == 0
     */
    BTNode (T const& it=T(), BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        //TODO
        item_ = it;
        leftNode_ = left;
        rightNode_ = right;

    }

    /**
     * @brief Create a BTNode using dynamic memory.
     * @param it the value save in the node.
     * @param left links to the left child.
     * @param right links to the right child.
     * @return a shared referente to the new node.
     */
    static typename BTNode<T>::Ref create(T const& it, BTNode<T>::Ref left=nullptr, BTNode<T>::Ref right=nullptr)
    {
        return std::make_shared<BTNode<T>> (it, left, right);
    }

    std::ostream& fold(std::ostream& out, BTNode<T>::Ref next) const{

    	if (next == nullptr)
    	{
    		out<<"[]";

    	}else{

    		out<<"[";
    		out<<item_;

    		fold(out, leftNode_);
    		fold(out, rightNode_);

    		out<<"]";
    	}

    	return out;
    }
    /** @brief Destroy a BTNode. **/
    ~BTNode()
    {}

    /** @}*/

    /** @name Observers.*/
    /** @{*/

    /** @brief Get the data item.*/
    const T& item() const
    {
        //TODO
        return item_;
    }

    /** @brief Has it a left child?*/
    bool has_left() const
    {
        //TODO
        if (leftNode_ == nullptr) return false;
        return true;
    }

    /** @brief get the left child.*/
    BTNode<T>::Ref left() const
    {
        //TODO
        return leftNode_;
    }

    /** @brief Has it a right child? */
    bool has_right() const
    {
        //TODO
        if (rightNode_ == nullptr) return false;
        return true;
    }

    /** @brief get the right child.*/
    BTNode<T>::Ref right() const
    {
        //TODO
        return rightNode_;
    }
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/

    /** @brief Set the data item.*/
    void set_item(const T& new_it)
    {
        //TODO
        item_ = new_it;
    }

    /** @brief Set the left child.*/
    void set_left(BTNode<T>::Ref new_child)
    {
        //TODO
        leftNode_ = new_child;
    }

    /** @brief Remove link to the left child. */
    void remove_left()
    {
        //TODO: hint see std::share_ptr doc.
        leftNode_ = nullptr;
    }

    /** @brief Set the right child.*/
    void set_right(BTNode<T>::Ref new_child)
    {
        //TODO
        rightNode_= new_child;
    }

    /** @brief Remove linkt to the right child. */
    void remove_right()
    {
        //TODO: hint see std::share_ptr doc.
        rightNode_ = nullptr;
    }

protected:
    //TODO
    //Hint: use typename SNode<T>::Ref for the link to other nodes.
    T item_;
    BTNode<T>::Ref leftNode_;
    BTNode<T> ::Ref rightNode_;
};

/**
 * @brief ADT BTree.
 * Models a BTree of T.
 */
template<class T>
class BTree
{
  public:

    /** @brief Define a shared reference to a BTNode.
     * Manages the storage of a pointer, providing a limited garbage-collection
     * facility, possibly sharing that management with other objects.
     * @see http://www.cplusplus.com/reference/memory/shared_ptr/
     */
    typedef std::shared_ptr< BTree<T> > Ref;

  /** @name Life cicle.*/
  /** @{*/

    /** @brief Create an empty BTree.
     * @post is_empty()
     */
    BTree ()
    {
        root_ = nullptr;
        assert(is_empty());
    }

  /** @brief Create Leaf BTree.
   * @post not is_empty()
   */
  BTree (const T& item)
  {
      //TODO
      root_ = BTNode<T>::create(item);
  }

  /**
   * @brief Create an empty BTree.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create()
  {
      return std::make_shared<BTree<T>> ();
  }

  /**
   * @brief Create a leaf BTree.
   * @param item is the root's item.
   * @return a shared referente to the new tree.
   */
  static typename BTree<T>::Ref create(T const& item)
  {
      auto tree = std::make_shared<BTree<T>>();
      tree->item(item);
      return tree;

  }

  /**
   * @brief Load a tree from a input stream.
   *
   * The input format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @return a reference to the tree created.
   * @warning runtime_error will throw if worng input format was found.
   */
  static typename BTree<T>::Ref create (std::istream& in) noexcept(false)
  {
      auto tree = BTree<T>::create();
      std::string token, aux;

      if (!in)
      {
      		throw std::runtime_error("Wrong input format.");
      }

      //TODO
    
      char skip;
      std::getline(in, aux, '\n');

      if (aux[1] != '[' or aux[aux.size()-1] != ']'){
         
         throw std::runtime_error("Wrong input format.");

      }
      
      in >> token;
      if (token == "[]") { 

        return tree;

      }

      	if (!in){
      		
      		throw std::runtime_error("Wrong input format.");

      	}

        in>>token;
      	std::istringstream translater(token);


        T itemAux;
        translater >> itemAux;
        tree->set_item(itemAux);

        if (!in){
      		
      		throw std::runtime_error("Wrong input format.");
      		
      	}


        if (!in){
      		
      		throw std::runtime_error("Wrong input format.");
      		
      	}

        in >> token;
        
        
        if (token == "[]")
        {

        	tree->set_left(nullptr);

        }else{

        	auto left_tree = BTree<T>::create(in);
			tree->set_left(left_tree);

        }


        in >> token;
        
        if (token == "[]")
        {
        	
        	tree->set_right(nullptr);

        }else{

        	auto right_tree = BTree<T>::create(in);
        	tree->set_right(right_tree);

        }

        return tree;

      }

      


    /*if (token == '[')
    {
        in >>token;
        in >> item;
   
        auto left_tree = BTree<T>::create(in);
		tree->set_left(left_tree);

        auto right_tree = BTree<T>::create(in);
        tree->set_right(right_tree);
        
        in >>token;

		if (token != ']')
		{

            throw std::runtime_error("Wrong input format.");

		}        

    }

    return tree;
      
  }*/



  /** @brief Destroy a BTree.**/
  ~BTree()
  {}

  /** @}*/

  /** @name Observers*/

  /** @{*/

  /** @brief is the list empty?.*/
  bool is_empty () const
  {
      //TODO
      if (root_ == nullptr) return true;
      return false;
  }

  /** @brief Get the root item.
   * @pre not is_empty();
   */
  T const& item() const
  {
      assert(!is_empty());
      //TODO
      return root_->item();
  }

  /**
   * @brief Get the left subtree.
   * @return a reference to the left subtree.
   * @pre !is_empty()
   */
  typename BTree<T>::Ref left() const
  {
      assert(!is_empty());
      BTree<T>::Ref l_subtree;

      //TODO
        l_subtree->root_ = root_->left();
      //

      return l_subtree;
  }

  /**
   * @brief Get the right subtree.
   * @return a reference to the right subtree.
   * @pre !is_empty()   
   */
  typename BTree<T>::Ref right() const
  {
      assert(!is_empty());
      BTree<T>::Ref r_subtree;

      //TODO
      r_subtree->root_ = root_->right();
      //

      return r_subtree;
  }

  /** a binary tree.
   *
   * The output format will be:
   * '[]' for the empty tree.
   * '[ <item> <left-subtree> <right-subtree> ']'
   *
   * For example a tree with three nodes:
   * "[ 2 [ 1 [] [] ] [ 3 [] [] ] ]"
   *
   * @param out is the output stream.
   * @param tree is the tree.
   * @return the output stream.
   * @pre tree!=nullptr
   */
  std::ostream& fold(std::ostream& out) const
  {
      //TODO

  		root_->fold(out, root_);

      //
      return out;
  }

  /** @}*/

  /** @name Modifiers*/

  /** @{*/

  /**
   * @brief set the roor's item.
   * @pre not is_empty()
   */
  void set_item(const T& new_it)
  {
      assert(!is_empty());
      //TODO
      root_->set_item(new_it);
  }

  /**
   * @brief Create the root node.
   * item is the new root item.
   * @post !is_empty()
   */
  void create_root(T const& item)
  {
      //TODO
      root_ = BTNode<T>::create(item);
      assert(!is_empty());
  }

  /**
   * @brief Remove the link to the root node.
   * @post is_empty()
   */
  void remove_root()
  {
      //TODO
      root_ = nullptr;
      assert(is_empty());

      
  }

  /**
   * @brief Attach a new subtree as left child of root.
   * @param new_left is the new left subtree.
   * @pre !is_empty()
   */
  void set_left(typename BTree<T>::Ref new_left)
  {
      assert(!is_empty());
      //TODO
      root_->set_left(new_left->root_);
  }

  /**
   * @brief Detach the left child of root.
   * @pre !is_empty()
   */
  void remove_left()
  {
      assert(!is_empty());
      //TODO
      root_->set_left(nullptr);
  }

  /**
   * @brief Attach a new subtree as right child of root.
   * @param t is the new right subtree.
   */
  void set_right(typename BTree<T>::Ref new_right)
  {
      assert(!is_empty());
      //TODO
      root_->set_right(new_right->root_);
  }

  /**
   * @brief Detach the right child of root.
   * @pre !is_empty()
   */
  void remove_right()
  {
      assert(!is_empty());
      //TODO
      root_->set_right(nullptr);
  }

  /** @}*/

protected:

  //TODO
  typename BTNode<T>::Ref root_;

};
#endif
