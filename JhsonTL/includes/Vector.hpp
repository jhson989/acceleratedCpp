
#ifndef __VEC__
#define __VEC__

#include <iostream>
#include <memory>
#include <algorithm>

template <class T>
class Vec {

public:
    
    // Class types
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::size_t size_type;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    /** Constructors **/
    Vec () {create ();}
    explicit Vec (size_type n, const_reference val = T()) {create (n, val);}
    Vec (const Vec& v) {create (v.begin (), v.end ());}
    
    /** Destructor **/
    ~Vec () {uncreate ();}

    /** Vec operators **/
    // Size function
    size_type size () const {return (avail-data);}
    
    // Indexing operator
    reference operator[] (size_type i) {return data[i];}
    const_reference operator[] (size_type i) const {return data[i];}

    // Iterator function
    iterator begin() {return data;}
    const_iterator begin() const {return data;}
    iterator end() {return avail;}
    const_iterator end() const {return avail;}

    // Assignment operator
    Vec& operator= (const Vec& rhs)  {
        if (&rhs != this) {
            uncreate ();
            create (rhs.begin(), rhs.end());
        }
        return *this;
    }

    // Manipulation operator
    void push_back (const_reference val) {
        if (avail == limit) {
            grow ();
        }
        unchecked_append (val);
    }
    void pop_back () {
        unchecked_pop ();
        if ((avail-data) == (limit-data)/2) {
            cut ();
        }   
    }

    void erase (const size_type at) {
        unchecked_drop (data+at);
        if ((avail-data) == (limit-data)/2) {
            cut ();
        }  

    }

    // Utils
    void print () {
        for (iterator n=data; n<avail; n++)
            std::cout << *n << " ";
        std::cout << std::endl;
    }


private:
    
    iterator data;
    iterator limit;
    iterator avail;

    std::allocator<T> alloc; // uninitialized memory allocation

    void create () {
        data = limit = avail = 0;
    }
    
    void create (size_type n, const_reference val) {
        data = alloc.allocate (n); 
        limit = avail = data + n;
        std::uninitialized_fill (data, limit, val);
    }

    void create (const_iterator begin, const_iterator end) {
        data = alloc.allocate (end-begin);
        limit = avail = std::uninitialized_copy (begin, end, data);
    }

    void uncreate () {
        if (data) {
            iterator it = avail;
            while (it != data) {
                alloc.destroy (--it);
            }
            alloc.deallocate (data, limit-data);
        }
        data = limit = avail = 0;
    }

    
    void grow () {
        size_type new_size = std::max (2*(limit-data), difference_type (1));

        iterator new_data = alloc.allocate (new_size);
        iterator new_avail = std::uninitialized_copy (data, avail, new_data);

        uncreate ();
    
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }

    void cut () {
        size_type new_size = avail - data;

        if (new_size == difference_type (0)) {
            uncreate ();
            return;
        }  
        iterator new_data = alloc.allocate (new_size);
        iterator new_avail = std::uninitialized_copy (data, avail, new_data);
        data = new_data;
        avail = new_avail;
        limit = data + new_size;
    }


    void unchecked_append (const_reference val) {
        alloc.construct (avail++, val);
    }

    void unchecked_pop () {
        alloc.destroy (avail--);
    }

    void unchecked_drop (iterator at) {

        for (iterator n=at+1; n<avail; n++)
            *(n-1) = *n;

        alloc.destroy (avail--);
    }
};

#endif
