// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <origin/dynarray.hpp>
#include <algorithm>

namespace origin
{
  template<typename T, typename Alloc = std::allocator<T>>
    struct matrix_impl_base
    {
      
      using matrix_storage = origin::dynarray<T, Alloc>;
      
      // Member variable.
      matrix_storage matrix_data;
      
      // Array iterator types.
      using array_iterator = typename matrix_storage::iterator;
      using const_array_iterator = typename matrix_storage::const_iterator;
      using reverse_array_iterator = typename matrix_storage::reverse_iterator;
      using const_reverse_array_iterator = typename matrix_storage::const_reverse_iterator;
      
    
      // typical types to interface with.
      using value_type = typename matrix_storage::value_type;
      using size_type = typename matrix_storage::size_type;
      using allocator_type = typename matrix_storage::allocator_type;
      using pointer = typename matrix_storage::pointer;
      using const_pointer = typename matrix_storage::const_pointer;
      using reference = typename matrix_storage::reference;
      using const_reference = typename matrix_storage::const_reference;
      
      // Default/Allocator Constructor
      // Default construct an empty matrix.
      matrix_impl_base(allocator_type const& alloc = allocator_type())
        :matrix_data(alloc)
      { }
      
      // Copy Constructor
      // Creates a copy of other.
      explicit matrix_impl_base(matrix_impl_base const& other)
        :matrix_data(other.matrix_data)
      { }

      // Copy + Copy Allocator Constructor 
      // Creates a copy of other and a copy of the allocator alloc.
      matrix_impl_base(matrix_impl_base const& other, allocator_type const& alloc)
        :matrix_data(other.matrix_data, alloc)
      { }
      
      // Move constructor.
      // Moves owner ship of memory from other to the new instance.
      explicit matrix_impl_base(matrix_impl_base&& other)
        :matrix_data(std::move(other.matrix_data))
      { }
      
      
      // Move + allocator constructor.
      // Moves owner ship of memory from other to the new instance.
      matrix_impl_base(matrix_impl_base&& other, const allocator_type& alloc)
        :matrix_data(std::move(other.matrix_data), alloc)
      { }
      
      // N size Constructor.
      // Creates a matrix of size N filled with value val.
      explicit matrix_impl_base(size_type n, value_type const& val = value_type(), allocator_type const& alloc = allocator_type())
        :matrix_data(n, val, alloc)
      { }
      
      // Destructor
      // Simple default implementation because all this has to do
      // is destruct the ONLY member variable matrix_data.
      ~matrix_impl_base() = default;
      
      
      // Member Functions.
      
      // clear
      // Removes all memory and elements from the current 
      // matrix.
      void clear() noexcept
      {
        matrix_data.clear();
      }
      
      // size
      // Returns the number of elements within the matrix.
      size_type size() const noexcept
      {
        return matrix_data.size();
      }
      
      // resize
      // Simple resize function which changes the number of elements within
      // the matrix. The behavior of this function is as follows.
      //
      // new_size - The new number of elements to allocate.
      void resize(size_type new_size)
      {
        swap(matrix_data, matrix_storage(new_size));
      }
      
      // apply
      // Apply function iterates over each of the different elements 
      // within the martix.
      template<typename Func>
      void apply(Func func)
      {
        std::transform(matrix_data.begin(), matrix_data.end(),matrix_data.begin(), func);
      }
      
      void swap(matrix_impl_base& rhs)
      {
        swap(matrix_data, rhs.matrix_data);
      }
      
      /*
      using array_iterator = typename matrix_storage::iterator;
      using const_array_iterator = typename matrix_storage::const_iterator;
      using reverse_array_iterator = typename matrix_storage::reverse_iterator;
      using const_reverse_array_iterator = typename matrix_storage::const_reverse_iterator;
       */
    };
  
} // end origin