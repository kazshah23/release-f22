/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include "List.h"

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
  ListNode * temp;
  while (current != nullptr) {
    temp = current;
    current = current -> next;
    delete temp;
  }

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = nullptr;
  
  if (head_ != nullptr) {
    head_ -> prev = newNode;
  } 
  if (tail_ == nullptr) {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1 

  ListNode * newNode = new ListNode(ndata);
  newNode -> next = nullptr; 
  newNode -> prev = tail_;
  

  if (tail_ != nullptr) {
    tail_ -> next = newNode;
  } 

  if (head_ == nullptr) {
    head_ = newNode;
  } 
  tail_ = newNode;
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr -> prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  // curr is iterating through normally 


  // 0 1 2 
  // 1 2 0 
  ListNode * curr = head_;
  int index = 0;

  while (curr != nullptr && curr -> next != nullptr && curr -> next -> next != nullptr) {
    ListNode * ind0 = curr;
    ListNode * ind1 = curr -> next;
    ListNode * ind2 = curr -> next -> next;

    if (ind0 -> prev != nullptr) {
      ind0 -> prev -> next = ind1;
    } else if (ind0 -> prev == nullptr) {
      head_ = ind1;
    }
    if (ind2 -> next != nullptr) {
      ind2 -> next -> prev = ind0;
    } else if (ind2 -> next == nullptr) {
      tail_ = ind0;
    }
    

    ind0 -> next = ind2 -> next;
    ind1 -> prev = ind0 -> prev;
    ind2 -> next = ind0;
    ind0 -> prev = ind2;

    curr = ind0 -> next;

    index++;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
  /** //x 
   *  ListNode * endtmp = currEnd -> prev;
      ListNode * afterend = currEnd -> next;
      ListNode * begtmp = currStart -> next;
      currStart -> prev -> next = currEnd;
      //x
      currEnd -> prev = currStart -> prev;
      //x
      currStart -> prev = currEnd -> prev;
      //x 
      currEnd -> prev -> next = currStart;
      //x
      currEnd -> next = endtmp;
      //x
      afterend -> prev = currStart;
      //x
      begtmp -> prev = currEnd;
      //x
      currStart -> next = begtmp;
  */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == nullptr || endPoint == nullptr) {
    return;
  }
  ListNode *current = startPoint;
  ListNode *temp = nullptr;
  ListNode* end = endPoint->next;
    while (current != end) {
        temp = current -> prev;
        current -> prev =  current -> next;
        current -> next = temp;   

        current = current -> prev;
    } 

    // TA Notes: std swap removes the need to create a temp variable, and just swaps them for you
    // 1 <- 2 3 4 5 6 7 -> 8 9
    std::swap(startPoint->next, endPoint->prev);
    // 1 <- 7 6 5 4 3 2 -> 8 9
    std::swap(startPoint, endPoint);

    if (startPoint -> prev != nullptr) startPoint -> prev -> next = startPoint;
    if (endPoint -> next != nullptr) endPoint -> next -> prev = endPoint;
}
  
  
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n == 1) {
    return;
  }
  if (n == length_) {
    reverse();
  }
  ListNode * current = head_;

  while (current != nullptr) {
    ListNode * beg_list = current;
    for (int i = 0; i < n - 1; i++) if (current -> next != nullptr) {current = current -> next;}
    reverse(beg_list, current);
    if (head_ == current) {head_ = beg_list;}
    if (tail_ == beg_list) {tail_ = current;}
    current = current -> next;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    } f
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first == nullptr) return second;
  if (second == nullptr) return first; 

  ListNode* one = first;
  ListNode* two = second;
  ListNode* output = nullptr;

  if(one -> data < two -> data) {
     output = one;
     one = one -> next;
  } else {    
    output = two;
    two = two -> next;
  }

  ListNode* tmp = output;
  while (one != nullptr && two != nullptr) {
    if (one -> data < two -> data) {
        tmp -> next = one;
        tmp = tmp -> next;
        one = one -> next;
    } else {
        tmp->next = two;
        tmp = tmp -> next;
        two = two -> next;
    }
  }

  if (one == nullptr) {
    tmp -> next = two;
  } else if (two == nullptr) {
    tmp -> next = one;
  }

  return output;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start -> next == NULL || chainLength == 1) return start;

  int size = 0;
  int middle = chainLength / 2;

  if (chainLength % 2 == 0) {
    size = chainLength / 2;
  } else {
    size = (chainLength - 1 / 2);
  }

  ListNode * split_half = split(start, (int) middle);
  ListNode * first_half =  mergesort(start, (int) middle);
  ListNode * second_half = mergesort(split_half, size);
  
  return merge(first_half, second_half);

}

