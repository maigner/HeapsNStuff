//
//  main.cpp
//  HeapsNStuff
//
//  Created by Martin Aigner on 03/03/15.
//  Copyright (c) 2015 Martin Aigner. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include "Heap.h"

using namespace std;

template<typename TimeT = std::chrono::microseconds>
struct measure {
  template<typename F, typename ...Args>
  static typename TimeT::rep execution(F func, Args&&... args)
  {
    auto start = std::chrono::system_clock::now();
    func(std::forward<Args>(args)...);
    auto duration = std::chrono::duration_cast< TimeT>
    (std::chrono::system_clock::now() - start);
    return duration.count();
  }
};


inline double fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}


auto testLectureHeap(uint32_t nelem) {

  // setup experiment, part of warm-up phase
  double *elements = new double[nelem];
  for (uint32_t i = 0; i < nelem; ++i) {
    elements[i] = fRand(0.0, 100.0);
  }
  Heap myHeap(nelem);
  
  // run experiment
  auto t = measure<>::execution(
                              [] (Heap& h, double* e, uint32_t n)
                              {
                                for (uint32_t i = 0; i < n; ++i) {
                                  h.push(e[i]);
                                }
                              },
                              myHeap, elements, nelem);
  
  delete [] elements;
  return t;
}

auto testSTLHeap(uint32_t nelem) {
  
  // setup experiment, part of warm-up phase
  double *elements = new double[nelem];
  //double *heap_data = new double[nelem];
  double *heap_data = new double[nelem];
  for (uint32_t i = 0; i < nelem; ++i) {
    elements[i] = fRand(0.0, 100.0);
  }
  
  std::make_heap(heap_data, heap_data+nelem);
  
  // run experiment
  auto t = measure<>::execution(
                              [] (double* h, double* e, uint32_t n)
                              {
                                for (uint32_t i = 0; i < n; ++i) {
                                  h[n-1] = e[i];
                                  std::push_heap(h, h+n);
                                }
                              },
                              heap_data, elements, nelem);
  
  delete [] elements;
  delete [] heap_data;
  return t;
}

template<typename T>
double arithmetic_mean(T* data, uint32_t nelem) {
  double sum = 0.0;
  for (uint32_t i = 0; i <nelem; ++i) {
    sum += data[i];
  }
  return sum / static_cast<double>(nelem);
}

template<typename T>
double sample_standard_deviation(T* data, uint32_t nelem) {
  double sum = 0.0;
  double mean = arithmetic_mean(data, nelem);
  
  for (uint32_t i = 0; i <nelem; ++i) {
    double diff = data[i]-mean;
    sum += diff * diff;
  }
  
  return sqrt((1.0/static_cast<double>(nelem-1)) * sum);
}

int main(int argc, const char * argv[]) {
  
  //const unsigned reps = 10; // Why 10?
  const unsigned reps = 20; // Why 20?
  u_int64_t samples[reps];
  
  for (unsigned i = 100; i <= 10000000; i *= 10) {
    
    cout << "n\t" << i;
    
    for (unsigned j = 0; j < reps; ++j) {
      samples[j] = testLectureHeap(i);
    }
    
    cout << "\tt_MyHeap\t" << arithmetic_mean(samples, reps);
    cout << "\tdev_MyHeap\t" << sample_standard_deviation(samples, reps);
    
    for (unsigned j = 0; j < reps; ++j) {
      samples[j] = testSTLHeap(i);
    }
    
    cout << "\tt_STLHeap\t" << arithmetic_mean(samples, reps);
    cout << "\tdev_STLHeap\t" << sample_standard_deviation(samples, reps);

    cout << endl;
  }
  
  return EXIT_SUCCESS;
}
