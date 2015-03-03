//
//  Heap.h
//  HeapsNStuff
//
//  Created by Martin Aigner on 03/03/15.
//  Copyright (c) 2015 Martin Aigner. All rights reserved.
//

#ifndef __HeapsNStuff__Heap__
#define __HeapsNStuff__Heap__

#include <algorithm>
#include <cstdint>


class Heap {
public:
  Heap(uint32_t n) : elements_(0), size_(n), data_(new double[n]) { }
  virtual ~Heap() { delete [] data_; }
  
  inline bool empty () const {
    return elements_ == 0;
  }
  
  inline double top() const {
    //assert elements_ > 0
    return data_[0];
  }
  
  inline void push(double d) {
    // assert elements_ < size_
    data_[elements_++] = d;
    uint32_t idx = elements_ - 1;
    while (idx != 0) {
      uint32_t pidx = ParentIndex(idx);
      if (data_[pidx] < d) {
        std::swap(data_[idx], data_[pidx]);
      } else
        break;
      idx = pidx;
    }
  }
  
  inline void pop() {
    //assert elements > 0
    data_[0] = data_[--elements_];
    uint32_t idx = 0;
    do {
      uint32_t children = Children(idx);
      if (children == 0) break;
      uint32_t max_idx = LeftIndex(idx);
      if (children == 2 && data_[max_idx] < data_[max_idx + 1]) {
        max_idx++;
      }
      if (data_[idx] < data_[max_idx]) {
        std::swap(data_[idx], data_[max_idx]);
        idx = max_idx;
      } else
        break;
    } while (true);
  }
  
private:
  uint32_t elements_;
  uint32_t size_;
  double *data_;
  
  inline uint32_t LeftIndex(uint32_t idx) const {
    return 2 * idx + 1;
  }
  
  inline uint32_t RightIndex(uint32_t idx) const {
    return 2 * idx + 2;
  }
  
  inline uint32_t ParentIndex(uint32_t idx) const {
    return (idx - 1) / 2;
  }
  
  inline uint32_t Children(uint32_t idx) const {
    if (elements_ <= LeftIndex(idx)) return 0;
    else if (elements_ > RightIndex(idx)) return 2;
    else return 1;
  }
  
};







#endif /* defined(__HeapsNStuff__Heap__) */
