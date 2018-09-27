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

#ifndef DUMBQUEUETEST_H
#define DUMBQUEUETEST_H

#include <assert.h>
#include "dumbqueue.h"

struct ValueKey {
   int d;
   int u;
   ValueKey(int _d, int _u)
      : d(_d), u(_u) {}
   /// The relation establishes the order in the PriorityQueue
   inline bool operator<(const ValueKey& rhs) const { return d < rhs.d; }
   inline bool operator>(const ValueKey& rhs) const { return d > rhs.d; }
   inline bool operator==(const ValueKey& rhs) const { return u == rhs.u; }
   inline void operator=(const ValueKey& rhs) { u = rhs.u; d = rhs.d; }
};

class DumbQueueTest
{
  
public:
  
  DumbQueueTest() {};
  
  void test_push_top() 
  {
    DumbQueue<ValueKey> queue;
    assert(queue.empty() == true);
    queue.push(ValueKey(-10, 1));
    queue.push(ValueKey(-30, 3));
    queue.push(ValueKey(-20, 2));
    ValueKey vk = queue.top();
    
    assert(vk.d == -10 && vk.u == 1);
    assert(queue.empty() == false);
  }
  
  void test_push_pop() 
  {
    DumbQueue<ValueKey> queue;
    assert(queue.empty() == true);
    queue.push(ValueKey(-10, 1));
    queue.push(ValueKey(-30, 2));
    queue.push(ValueKey(-20, 3));
    queue.push(ValueKey(-5, 4)); //pop
    queue.push(ValueKey(-40, 5));
    queue.pop();
    ValueKey vk = queue.top();
    
    assert(vk.d == -10 && vk.u == 1);
    assert(queue.empty() == false);
  }
  
  void test_push_increase() 
  {
    DumbQueue<ValueKey> queue;
    assert(queue.empty() == true);
    queue.push(ValueKey(-10, 1));
    queue.push(ValueKey(-30, 2));
    queue.push(ValueKey(-20, 3));
    queue.push(ValueKey(-5, 4));
    queue.push(ValueKey(-40, 5));
    queue.pop();
    queue.increase(ValueKey(-55, 3), ValueKey(-2, 3));
    ValueKey vk = queue.top();
    
    assert(vk.d == -2 && vk.u == 3);
    assert(queue.empty() == false);
  }
  
    void test_push_pop_increase() 
  {
    DumbQueue<ValueKey> queue;
    assert(queue.empty() == true);
    queue.push(ValueKey(-10, 1)); 
    queue.push(ValueKey(-30, 2));
    queue.push(ValueKey(-1, 6)); //pop 1
    queue.push(ValueKey(-20, 3));
    queue.push(ValueKey(-5, 4)); //pop 2
    queue.push(ValueKey(-40, 5));
    queue.pop();
    queue.pop();
    queue.increase(ValueKey(-55, 3), ValueKey(-2, 3));
    
    ValueKey vk = queue.top();
    
    assert(vk.d == -2 && vk.u == 3);
    assert(queue.empty() == false);
  }
  
};

#endif // DUMBQUEUETEST_H
