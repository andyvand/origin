namespace origin
{
  /**
   * @internal
   * The binomial heap node stores the non-dependent (template) link structure 
   * for a node in a binomial heap. This includes..
   */
  struct binomial_heap_node
  {
    public:
      typedef std::size_t size_type;

      binomial_heap_node()
        : parent{-1}, child{-1}, right_sibling{-1}, degree{0} 
      { }
      
      size_type index;          // Index of the the referenced element.
      size_type parent;         // Parent index
      size_type child;          // First? child index
      size_type right_sibling;  // Right sibling index
      size_type degree;         // Number of children?
  };

  // FIXME: Make this an operation on the binoial node called, set_parent
  // or something similar.
  /** 
   * @internal
   * Link the node x as the child of y.
   */
  void binomial_link(binomial_heap_node& x, binomial_heap_node& y, size_t m, size_t n)
  {
    x.parent = n;
    x.right_sibling = y.child;
    y.child = m;
    y.degree = y.degree + 1;
  }

  /**
   * A binomial heap...
   */
  template<typename T,
           typename Comp = std::less<T>,
           typename Alloc = std::allocator<T>>
    class binomial_heap
    {
    public:
      typedef T const value_type;
      typedef size_t size_type;
      typedef Comp value_compare;
    private:
      typedef binomial_heap_node node_type;
      typedef std::vector<value_type> value_list;
      typedef std::vector<node_type> node_list;
      typedef std::vector<size_type> reverse_list;
    public:
      
      /** @name Initialization */
      //@{
      /**
       * @brief Default constructor
       */
      //@{
      binomial_heap(value_compare const& comp = value_compare{})
        : compare_{comp}, top_{-1}, head_{-1} 
      { }
      
      /**
       * @brief Range constructor
       */
      template<typename ForwardIterator>
      binomial_heap(ForwardIterator first, 
                    ForwardIterator last,
                    value_compare const& comp = value_compare{})
        : compare_{comp}, top_{-1}, head_{-1}
      {
        reserve(std::distance(first, last));
        while(first != last) {
          push(*first);
          ++first;
        }
      }
      
      binomial_heap(std::initializer_list<T> lst, 
                    value_compare const& comp = value_compare{})
        : compare_{comp}, top_{-1}, head_{-1}
      {
        reserve(lst.size());
        for(auto &x : lst) {
          push(x);
        }
      }
      //@}

      bool empty() const
      {
        return data_.size()==0;
      }
        
      size_type size() const
      {
        return data_.size();
      }
      
      value_compare value_comp() const
      {
        return compare_;
      }

      size_type capacity() const
      {
        return data_.capacity();
      }

      void reserve(size_type n)
      {
        reversemap_.reserve(n);
        data_.reserve(n);
        nodes_.reserve(n);
      }
        
      /** @name Heap operations */
      //@{
      value_type const& top() const
      {
        return data_[nodes_[top_].index];
      }
      
      void push(const value_type& d); 
        
      void pop();
      //@}

    private:
      void merge(size_type index);
      void unite(size_type index);
      size_type get_new_top();       

      
      // Return true if the elements at m and n violate the heap order.
      bool less(size_type m, size_type n) const
      {
        return compare_(m, n);
      }
      
      // Return true if the elements at m and n observe the heap order.
      bool not_less(size_type m, size_type n) const
      {
        return !less(m, n);
      }
      
    private:
      std::vector<T, Alloc> data_;              // Contains elements
      std::vector<binomial_heap_node> nodes_;   // Contains node data
      std::vector<size_type> reversemap_;
        
      Comp compare_;

      size_type top_;
      size_type head_;
    };
  
  template<typename T, typename Comp, typename Alloc>
    auto binomial_heap<T, Comp, Alloc>::get_new_top() -> size_type
    {
      size_type top_index;
      size_type tmp;
      if (head_ == size_type(-1)) {
        return -1;
      }
      
      top_index = head_;
      tmp = nodes_[top_index].right_sibling;
      
      while (tmp != size_type(-1)) {
        if(!compare_(data_[nodes_[tmp].index], 
                    data_[nodes_[top_index].index])) 
        {
          top_index = tmp;
        }
        
        tmp = nodes_[tmp].right_sibling;
      }
      
      return top_index;
    }
  
  
  template<typename T, typename Comp, typename Alloc>
    void binomial_heap<T, Comp, Alloc>::push(const value_type& d)
    {
      binomial_heap_node obj;
      size_type index;
    
      data_.push_back(d);
  
      obj.index = data_.size() - 1;
      obj.parent = size_type(-1);
      obj.right_sibling = size_type(-1);
      obj.child = size_type(-1);
      obj.degree = 0;
      
      nodes_.push_back(obj);
      
      index = nodes_.size() - 1;

      reversemap_.push_back(index);

      if (head_ == size_type(-1)) {
        /* New heap */
        head_ = index;
        top_ = head_;
      } else {
        /* Unite the 1 element heap with the existing heap */
        binomial_heap_union(index);
        if (!compare_(data_[nodes_[index].index], data_[nodes_[top_].index]))
          top_ = index;
      }
    }
  
  
  template<typename T, typename Comp, typename Alloc>
    void binomial_heap<T, Comp, Alloc>::merge(size_type index)
    {
      size_type p = head_;
      size_type q = index;
      
      size_type current = nodes_.size();
      size_type initial_size = -1;
      nodes_.push_back(binomial_heap_node());
      
      while (p != initial_size || q != initial_size) {
        if (q == initial_size || 
            (p != initial_size && nodes_[p].degree < nodes_[q].degree)) {
          nodes_[current].right_sibling = p;
          current = p;
          p = nodes_[p].right_sibling;
        } else {
          nodes_[current].right_sibling = q ;
          current = q;
          q = nodes_[q].right_sibling;
        }
      }
      
      head_ = nodes_.back().right_sibling;
      nodes_.pop_back();
    }
  
  
  template<typename T, typename Comp, typename Alloc>
    void binomial_heap<T, Comp, Alloc>::unite(size_type index)
    {
      /* Merge the root lists */
      merge(index);
      if (nodes_[head_].right_sibling == size_type(-1)) {
        return;
      }
        
      size_type x = head_;
      size_type next_x = nodes_[head_].right_sibling;
      size_type prev_x = size_type(-1);
      
      while (next_x != size_type(-1)) {
        if ((nodes_[x].degree != nodes_[next_x].degree) 
              || (nodes_[next_x].right_sibling != size_type(-1) 
              && nodes_[nodes_[next_x].right_sibling].degree 
              == nodes_[x].degree)) {
          prev_x = x;
          x = next_x;
        } else {
          if (!compare_ (data_[nodes_[x].index], data_[nodes_[next_x].index])) {
            nodes_[x].right_sibling = nodes_[next_x].right_sibling;
            binomial_link(nodes_[next_x], nodes_[x], next_x, x);
          } else {
            if (prev_x == size_type (-1)) {
              head_ = next_x;
            } else {
              nodes_[prev_x].right_sibling = next_x;
            }
             
            binomial_link(nodes_[x], nodes_[next_x], x, next_x);
            x = next_x;
          }
        }
        
        next_x = nodes_[x].right_sibling;
      }
    }
  
  
  template<typename T, typename Comp, typename Alloc>
    void binomial_heap<T, Comp, Alloc>::pop()
    {
      size_type new_head = size_type(-1);
      
      if (head_ == size_type(-1)) {
        return;
      }
    
      size_type temp = top_;
  
      /* Reverse the list */
      if (nodes_[top_].child != size_type(-1)) {
        size_type tmp_head = nodes_[top_].child;
        size_type tmp_sibling;
        
        while (tmp_head != size_type(-1)) {
          tmp_sibling = nodes_[tmp_head].right_sibling;
          nodes_[tmp_head].parent = size_type(-1);
          nodes_[tmp_head].right_sibling = new_head;
          new_head = tmp_head;
          tmp_head = tmp_sibling;
        }
      }
      
      if (nodes_[head_].right_sibling == size_type(-1)) {
        head_ = new_head;
      } else {
        if (head_ == top_) {
          head_ = nodes_[head_].right_sibling;
        } else {
          size_type tmp = head_;
          while (nodes_[tmp].right_sibling != top_) {
            tmp = nodes_[tmp].right_sibling;
          }
            
          nodes_[tmp].right_sibling = nodes_[top_].right_sibling;
        }
        
        binomial_heap_union(new_head);
      }
      
  
      size_type index = reversemap_.back();
  
      // copy the last element to location of old top element
      data_[nodes_[temp].index] = data_[data_.size()-1];
  
      reversemap_[nodes_[temp].index] = index;

      //point the index of the old element to correct location
      nodes_[index].index = nodes_[temp].index;
  
      // Invalidating the entries of node
      nodes_[temp].parent = -1;
      nodes_[temp].child = -1;
      nodes_[temp].right_sibling = -1;
      nodes_[temp].degree = 0;
      nodes_[temp].index = -1;
  
      data_.pop_back();
  
      reversemap_.pop_back();

      top_ = get_new_top();
    }
  
  template<typename T, typename Comp, typename Alloc>
    template<typename Char, typename Traits>
    void binomial_heap<T, Comp, Alloc>::print(std::basic_ostream<Char, Traits>& os)
    {
      if(head_ != size_type(-1)) {
        size_type i = head_;
        do {
          print_recur(i, os);
          os << '\n';
          i = nodes_[i].right_sibling;
        } while(i != size_type(-1));
      }
    }


  /** 
   * The mutable binomial heap...
   *
   * @tparam T
   * @tparam Comp
   * @tparam Map
   * @tparam Alloc
   */
  template<typename T, 
           typename Comp = std::less<T>,
           typename Map = hash_index<T>,
           typename Alloc = std::allocator<T>> 
    class mutable_binomial_heap
    {
    private:
      typedef T value_type;
      typedef size_t size_type;
      typedef Comp value_compare;
      
      /* Random access container which holds the heap elements */
      std::vector<T, Alloc> data_;
      std::vector<binomial_heap_node> nodes_;
        
      value_compare compare_;
      std::unordered_map<T, size_type> id_;     // Index map
      
      size_type top_;   // Index of the root element
      size_type head_;  // Index of the top element

      /*
       * print_recur: Helper function for displaying the binomial heap
       * Input:
       * size_type x : Index of the element
       * ostresm &os : Reference to the ouput stream
       * Output:
       * Prints the nodes for a particular binomial tree identified by x
       * Return Value: None       
       */
      template<typename Char, typename Traits>
      void print_recur(size_type x, std::basic_ostream<Char, Traits>& os)
      {
        if (x != size_type (-1)) {
          os << data_[nodes_[x].index];
          if (nodes_[x].degree > 0) {
            os << '(';
               size_type i = nodes_[x].child;
              do {
                print_recur (i, os);
                os << " ";
                i = nodes_[i].right_sibling;
              } while (i != size_type(-1));
              os << ")";
          }
        }
      }
        
      /*
       * merge: Function to merge two binomial heaps
       * Input: 
       * size_type x : Index of the root element of the heap to be merged
       * Output:
       * Merges the heap pointed to by x in the main heap pointed to by head_
       * Return Value:
       * None       
       */
      void merge (size_type index);

      /*
       * mutable_binomial_heap_union: Unites the heap pointed to by head_ with 
       * the heap specified
       * Input: 
       * size_type index: Index of the root element of the heap to be united
       * Output:
       * United binomial heap
       * Return Value:
       * None       
       */
      void mutable_binomial_heap_union (size_type index);
          
      /*
       * get_new_top: Function to find the index of new root element
       * Input: 
       * None
       * Output:
       * Index of the new root
       * Return Value:
       * size_type: Index of the new root
       */
      size_type get_new_top(); 
        
    public:
      /**
       * @brief Default constructor
       */
      mutable_binomial_heap(value_compare const& comp = value_compare{}) 
        : compare_{comp}, top_{-1}, head_{-1} 
      { }
        
      /**
       * @brief Range constructor
       */
      template<typename Iter>
        mutable_binomial_heap(Iter first, 
                              Iter last,
                              value_compare const& comp = value_compare{}) 
          : compare_{comp}, top_{-1}, head_{-1}
        {
          while(first != last)
            push(*first++);
        }
        
      /**
       * @brief Initializer list constructor
       */
      mutable_binomial_heap(std::initializer_list<T> list,
                            value_compare const& comp = value_compare{}) 
        : compare_{comp}, top_{-1}, head_{-1}
      {
        for(auto const& x : list)
          push(x);
      }

      /*
       * print: Function for displaying the binomial heap
       * Input:
       * ostresm &os : Reference to the ouput stream
       * Output:
       * Outputs the binomial heap to the specified output stream
       * Return Value:
       * None       
       * Note: This a helper function developed for unit testing
       */
      template<typename Char, typename Traits>
        void print(std::basic_ostream<Char, Traits>& os);
        
        
      /*
       * Update: Updates the given element in the heap
       * Input: 
       * value_type &d: Reference to element which has to be updated
       * Output:
       * Updated heap
       * Return Value:
       * None       
       * Precondition: Element d must already be updated in the map
       */
      void update(const value_type& d);
        
      /*
       * push: Insets the given element in the heap
       * Input: 
       * value_type &d: Reference to element which has to be inserted
       * Output:
       * Heap with the new element inserted
       * Return Value:
       * None       
       * Precondition: Element d must already be present in the map
       */
      void push(const value_type& d); 
        
        
      /*
       * top: Function to return the top element of the heap
       * Input: 
       * None
       * Output:
       * top element
       * Return Value:
       * value_type &: Reference to the top element is retured
       */
      value_type& top()
      {
        return data_[nodes_[top_].index];
      }
      
      /*
       * top: Constant Function to return the const top element of the heap
       * Input: 
       * None
       * Output:
       * top element
       * Return Value:
       * value_type &: Reference to the top element is retured
       */
      const value_type& top() const
      {
        return data_[nodes_[top_].index];
      }

      /**
       * Return true if the heap is empty.
       */
      bool empty() const
      {
        // FIXME: There should also be no elements.
        return head_ == -1u;
      }
        
      /*
       * size: Function to find the size of the heap
       * Input: 
       * None
       * Output:
       * Number of elements in the heap
       * Return Value:
       * size_type : Number of elements
       */
      size_type size() const
      {
        return data_.size();
      }
        
      value_compare value_comp() const
      {
        return compare_;
      }
        

      void reserve(size_type n)
      {
        data_.reserve(n);
        nodes_.reserve(n);
      }
        
      size_type capacity() const
      {
        return data_.capacity();
      }

      /*
       * pop: Removes the top element from the heap
       * Input: 
       * None
       * Output:
       * binomial heap with a new top element
       * Return Value:
       * None
       */
      void pop();
      
    private:
      // Return true if the elements at m and n violate the heap order.
      bool less(size_type m, size_type n) const
      {
        return compare_(m, n);
      }
      
      // Return true if the elements at m and n observe the heap order.
      bool not_less(size_type m, size_type n) const
      {
        return !less(m, n);
      }
    };
  
  template <class T, class Comp, class Map, class Alloc>
    auto mutable_binomial_heap<T, Comp, Map, Alloc>::get_new_top() -> size_type
    {
      size_type top_index;
      size_type tmp;
      if (head_ == size_type(-1)) {
        return -1;
      }
      
      top_index = head_;
      tmp = nodes_[top_index].right_sibling;
      
      while (tmp != size_type(-1)) {
        if (!compare_(data_[nodes_[tmp].index], data_[nodes_[top_index].index])) {
          top_index = tmp;
        }
        
        tmp = nodes_[tmp].right_sibling;
      }
      
      return top_index;
    }
  
  
  template <class T, class Comp, class Map, class Alloc>
    void mutable_binomial_heap<T, Comp, Map, Alloc>::push(const value_type& d)
    {
      binomial_heap_node obj;
      size_type index;
    
      data_.push_back(d);

      obj.index = data_.size() - 1;
      obj.parent = size_type(-1);
      obj.right_sibling = size_type(-1);
      obj.child = size_type(-1);
      obj.degree = 0;
      
      nodes_.push_back(obj);
      index = nodes_.size() - 1;
      id_[d] = index;

      if(empty()) {
        head_ = index;
        top_ = head_;
      } else {
        /* Unite the 1 element heap with the existing heap */
        mutable_binomial_heap_union(index);
        if (!compare_(data_[nodes_[index].index], data_[nodes_[top_].index]))
            top_ = index;
      }
    }
  
  
  template <class T, class Comp, class Map, class Alloc>
    void mutable_binomial_heap<T, Comp, Map, Alloc>::update(const value_type& d)
    {
      size_type index = id_[d];
      size_type parent = nodes_[index].parent;
      size_type temp;
      data_[nodes_[index].index] = d;
      
      while (parent != size_type(-1) && 
            !compare_(d, data_[nodes_[parent].index])) {
        data_[nodes_[index].index] = data_[nodes_[parent].index];
        data_[nodes_[parent].index] = d;

        id_[data_[nodes_[index].index]] = index;
        
        index = parent;
        parent = nodes_[parent].parent;
      }

      id_[d] = index;
      
      if (!compare_(d, data_[nodes_[top_].index])) {
        top_ = index;
      }
    }
  
  
  template <class T, class Comp, class Map, class Alloc>
    void mutable_binomial_heap<T, Comp, Map, Alloc>::merge (size_type index)
    {
      size_type p = head_;
      size_type q = index;
      
      size_type current = nodes_.size();
      size_type initial_size = -1;
      nodes_.push_back(binomial_heap_node());
      
      while (p != initial_size || q != initial_size) {
        if (q == initial_size || 
              (p != initial_size && nodes_[p].degree < nodes_[q].degree)) {
          nodes_[current].right_sibling = p;
          current = p;
          p = nodes_[p].right_sibling;
        } else {
          nodes_[current].right_sibling = q ;
          current = q;
          q = nodes_[q].right_sibling;
        }
      }
      
      head_ = nodes_.back().right_sibling;
      nodes_.pop_back();
    }
  
  
  template <class T, class Comp, class Map, class Alloc>
    void mutable_binomial_heap<T, Comp, Map, Alloc>::mutable_binomial_heap_union (size_type index)
    {
      /* Merge the root lists */
      merge(index);
      if (nodes_[head_].right_sibling == size_type(-1)) {
        return;
      }
      
      size_type x = head_;
      size_type next_x = nodes_[head_].right_sibling;
      size_type prev_x = size_type(-1);
      
      while (next_x != size_type(-1)) {
        if ((nodes_[x].degree != nodes_[next_x].degree) 
              || (nodes_[next_x].right_sibling != size_type(-1) 
                  && nodes_[nodes_[next_x].right_sibling].degree 
                  == nodes_[x].degree)) {
            prev_x = x;
            x = next_x;
        } else {
          if (!compare_ (data_[nodes_[x].index], data_[nodes_[next_x].index])) {
            nodes_[x].right_sibling = nodes_[next_x].right_sibling;
            binomial_link(nodes_[next_x], nodes_[x], next_x, x);
          } else {
            if (prev_x == size_type (-1)) {
              head_ = next_x;
            } else {
              nodes_[prev_x].right_sibling = next_x;
            }
            
            binomial_link(nodes_[x], nodes_[next_x], x, next_x);
            x = next_x;
          }
        }
        
        next_x = nodes_[x].right_sibling;
      }
    }
  
  
  template <class T, class Comp, class Map, class Alloc>
    void mutable_binomial_heap<T, Comp, Map, Alloc>::pop()
    {
      size_type new_head = size_type(-1);
      
      if (head_ == size_type(-1)) {
        return;
      }
    
      size_type temp = top_;
  
      /* Reverse the list */
      if (nodes_[top_].child != size_type(-1)) {
        size_type tmp_head = nodes_[top_].child;
        size_type tmp_sibling;
        
        while (tmp_head != size_type(-1)) {
          tmp_sibling = nodes_[tmp_head].right_sibling;
          nodes_[tmp_head].parent = size_type(-1);
          nodes_[tmp_head].right_sibling = new_head;
          new_head = tmp_head;
          tmp_head = tmp_sibling;
        }
      }
      
      if (nodes_[head_].right_sibling == size_type(-1)) {
        head_ = new_head;
      } else {
        if (head_ == top_) {
          head_ = nodes_[head_].right_sibling;
        } else {
          size_type tmp = head_;
          while (nodes_[tmp].right_sibling != top_) {
            tmp = nodes_[tmp].right_sibling;
          }
            
          nodes_[tmp].right_sibling = nodes_[top_].right_sibling;
        }
        
        mutable_binomial_heap_union(new_head);
      }
      
  
      // where in nodes_ old last element is stored
      size_type index = id_[data_[data_.size()-1]];
  
      // copy the last element to location of old top element
      data_[nodes_[temp].index] = data_[data_.size()-1];
  
      //point the index of the old element to correct location
      nodes_[index].index = nodes_[temp].index;
  
      // Invalidating the entries of node
      nodes_[temp].parent = -1;
      nodes_[temp].child = -1;
      nodes_[temp].right_sibling = -1;
      nodes_[temp].degree = 0;
      nodes_[temp].index = -1;
  
      data_.pop_back();
  
      top_ = get_new_top();
  }
  
  template <class T, class Comp, class Map, class Alloc>
    template<typename Char, typename Traits>
      void mutable_binomial_heap<T, Comp, Map, Alloc>::
        print(std::basic_ostream<Char, Traits>& os)
      {
        if (head_ != size_type(-1)) {
          size_type i = head_;
          do {
            print_recur(i, os);
            os << '\n';
            i = nodes_[i].right_sibling;
          } while (i != size_type(-1));
        }
      }

} // namespace origin
