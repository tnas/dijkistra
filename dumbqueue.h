/*
 * Copyright 2015 Thiago Nascimento <thiago.rodrigues@tre-es.jus.br>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <vector>
#include <algorithm>
#include <boost/concept_check.hpp>

#define INITIAL_QUEUE_CAPACITY 10

using namespace std;
using std::vector;
using std::iter_swap;

// ************************
// Template Declaration
// ************************
template<typename T>
class DumbQueue
{
private :
    vector<T> queue;
public:
    
    struct handle_type 
    { 
      T operator*() const;
    };

    DumbQueue();
    ~DumbQueue();
    
    bool empty();
    T push(T node);
    void pop();
    void increase(T target, T update);
    T top();
};

// ************************
// Template Implementation
// ************************
template<typename T>
DumbQueue<T>::DumbQueue()
{
  queue.reserve(INITIAL_QUEUE_CAPACITY);
}

template<typename T>
DumbQueue<T>::~DumbQueue()
{
  queue.clear();
}

template<typename T>
bool DumbQueue<T>::empty()
{
  return queue.empty();
}


template<typename T>
T DumbQueue<T>::push(T node) 
{
  queue.push_back(node);
  return queue.back();
}

template<typename T>
void DumbQueue<T>::pop()
{
  typedef typename vector<T>::iterator vector_iterator;
  
  vector_iterator max_element = queue.begin();
  
  vector_iterator it;
  for (it = queue.begin(); it != queue.end(); ++it)
    if (*it > *max_element) max_element = it;
  
  // swapping max element and last element
  iter_swap(max_element, it);
  
  /*  
  T temp = *it; 
  *it = *max_element;
  *max_element = temp;
  */
  
  queue.pop_back();
}


template<typename T>
void DumbQueue<T>::increase(T target, T update)
{
  typedef typename vector<T>::iterator vector_iterator;
  
  for (vector_iterator it = queue.begin(); it != queue.end(); ++it)
  {
    if (*it == target) 
    {
      *it = update;
      break;
    }
  }
}

template<typename T>
T DumbQueue<T>::top()
{
  typedef typename vector<T>::iterator vector_iterator;
  
  vector_iterator max_element = queue.begin();
  
  vector_iterator it;
  for (it = queue.begin(); it != queue.end(); ++it)
    if (*it > *max_element) max_element = it;
  
  return *max_element;
}
