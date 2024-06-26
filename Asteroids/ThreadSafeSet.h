#pragma once
#include "ReadersWriterLock.h"
#include <set>

template <class Key,
    class Compare = std::less<Key>,
    class Alloc = std::allocator<Key>>
    class thread_safe_set : public std::set<Key, Compare, Alloc>
{
    typedef typename std::set<Key, Compare, Alloc>::iterator iterator;
    typedef typename std::set<Key, Compare, Alloc>::const_iterator const_iterator;
    typedef typename std::set<Key, Compare, Alloc>::key_type key_type;
    typedef typename std::set<Key, Compare, Alloc>::key_compare key_compare;
    typedef typename std::set<Key, Compare, Alloc>::allocator_type allocator_type;
    typedef typename std::set<Key, Compare, Alloc>::value_type value_type;
    typedef typename std::set<Key, Compare, Alloc>::size_type size_type;
    typedef typename std::set<Key, Compare, Alloc> set;

    mutable ReadersWriterLock rwl;

public:
    explicit thread_safe_set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : std::set<Key, Compare, Alloc>(comp, alloc) {}
    explicit thread_safe_set(const allocator_type& alloc) : std::set<Key, Compare, Alloc>(alloc) {}
    template <class InputIterator> 
    thread_safe_set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : std::set<Key, Compare, Alloc>(first, last, comp, alloc) {}
    thread_safe_set(const set& x) : std::set<Key, Compare, Alloc>(x) {}
    thread_safe_set(const thread_safe_set& x) : std::set<Key, Compare, Alloc>(x) {}
    thread_safe_set(const thread_safe_set& x, const allocator_type& alloc) : std::set<Key, Compare, Alloc>(x, alloc) {}
    thread_safe_set(set&& x) : std::set<Key, Compare, Alloc>(x) {}
    thread_safe_set(thread_safe_set&& x) : std::set<Key, Compare, Alloc>(x) {}
    thread_safe_set(set&& x, const allocator_type& alloc) : std::set<Key, Compare, Alloc>(x, alloc) {}
    thread_safe_set(thread_safe_set&& x, const allocator_type& alloc) : std::set<Key, Compare, Alloc>(x, alloc) {}
    thread_safe_set(std::initializer_list<value_type> il, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : std::set<Key, Compare, Alloc>(il, comp, alloc) {}
    thread_safe_set<Key, Compare, Alloc>& operator= (const set& x)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::operator=(x);
        this->rwl.unlock_write();
        return(ret);
    }
    thread_safe_set<Key, Compare, Alloc>& operator= (const thread_safe_set<Key, Compare, Alloc>& x)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::operator=(x);
        this->rwl.unlock_write();
        return(ret);
    }
    thread_safe_set<Key, Compare, Alloc>& operator= (set&& x)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::operator=(x);
        this->rwl.unlock_write();
        return(ret);
    }
    thread_safe_set<Key, Compare, Alloc>& operator= (thread_safe_set<Key, Compare, Alloc>&& x)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::operator=(x);
        this->rwl.unlock_write();
        return(ret);
    }
    thread_safe_set<Key, Compare, Alloc>& operator= (std::initializer_list<value_type> il)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::operator=(il);
        this->rwl.unlock_write();
        return(ret);
    }
    bool empty() const noexcept
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::empty();
        this->rwl.unlock_read();
        return(ret);
    }
    size_type size() const noexcept
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::size();
        this->rwl.unlock_read();
        return(ret);
    }
    std::pair<iterator, bool> insert(const value_type& val)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::insert(val);
        this->rwl.unlock_write();
        return(ret);
    }
    std::pair<iterator, bool> insert(value_type&& val)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::insert(std::move(val));
        this->rwl.unlock_write();
        return(ret);
    }
    iterator insert(iterator position, const value_type& val)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::insert(position, val);
        this->rwl.unlock_write();
        return(ret);
    }
    iterator insert(iterator position, value_type&& val)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::insert(position, std::move(val));
        this->rwl.unlock_write();
        return(ret);
    }
    template <class InputIterator> void insert(InputIterator first, InputIterator last)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::insert(first, last);
        this->rwl.unlock_write();
        return(ret);
    }
    iterator erase(const_iterator position)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::erase(position);
        this->rwl.unlock_write();
        return(ret);
    }
    size_type erase(const key_type& k)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::erase(k);
        this->rwl.unlock_write();
        return(ret);
    }
    iterator erase(const_iterator first, const_iterator last)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::erase(first, last);
        this->rwl.unlock_write();
        return(ret);
    }
    void swap(set& x)
    {
        this->rwl.lock_write();
        this->std::set<Key, Compare, Alloc>::swap(x);
        this->rwl.unlock_write();
    }
    void swap(thread_safe_set<Key, Compare, Alloc>& x)
    {
        this->rwl.lock_write();
        x.lock_write();
        this->std::set<Key, Compare, Alloc>::swap(x);
        x.unlock_write();
        this->rwl.unlock_write();
    }
    void clear() noexcept
    {
        this->rwl.lock_write();
        this->std::set<Key, Compare, Alloc>::clear();
        this->rwl.unlock_write();
    }
    template <class... Args> 
    std::pair<iterator, bool> emplace(Args&&... args)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::emplace(args...);
        this->rwl.unlock_write();
        return(ret);
    }
    template <class... Args> 
    iterator emplace_hint(const_iterator position, Args&&... args)
    {
        this->rwl.lock_write();
        auto ret = this->std::set<Key, Compare, Alloc>::emplace_hint(position, args...);
        this->rwl.unlock_write();
        return(ret);
    }
    iterator find(const key_type& k)
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::find(k);
        this->rwl.unlock_read();
        return(ret);
    }
    const_iterator find(const key_type& k) const
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::find(k);
        this->rwl.unlock_read();
        return(ret);
    }
    size_type count(const key_type& k) const
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::count(k);
        this->rwl.unlock_read();
        return(ret);
    }
    iterator lower_bound(const key_type& k)
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::lower_bound(k);
        this->rwl.unlock_read();
        return(ret);
    }
    const_iterator lower_bound(const key_type& k) const
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::lower_bound(k);
        this->rwl.unlock_read();
        return(ret);
    }
    iterator upper_bound(const key_type& k)
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::upper_bound(k);
        this->rwl.unlock_read();
        return(ret);
    }
    const_iterator upper_bound(const key_type& k) const
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::upper_bound(k);
        this->rwl.unlock_read();
        return(ret);
    }
    std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::equal_range(k);
        this->rwl.unlock_read();
        return(ret);
    }
    std::pair<iterator, iterator> equal_range(const key_type& k)
    {
        this->rwl.lock_read();
        auto ret = this->std::set<Key, Compare, Alloc>::equal_range(k);
        this->rwl.unlock_read();
        return(ret);
    }
    inline bool set_lock_style(ReadersWriterLock::LockStyle lockStyle) { return(this->rwl.set_lock_style(lockStyle)); }
    inline void lock_read() { (this->rwl.lock_read)(); }
    inline void unlock_read() { (this->rwl.unlock_read)(); }
    inline void lock_write() { (this->rwl.lock_write)(); }
    inline void unlock_write() { (this->rwl.unlock_write)(); }
};