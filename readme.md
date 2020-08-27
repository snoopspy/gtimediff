GTimeDiff Library
======================================

## About
* GTimeDiff is a simple and robust time difference measurement library for C++.

## How to use
* Just include <b>gtimediff.h</b> header file.

## Sample
* See the following code. Suppose that it contains a critical routine that consumes too much time. You don't know which function is time consuming. Anyway, you would like to figure out how long it takes time in each routine. In this case, GTimeDiff is a good solution for the problem.

```cpp
  doSometing1();
  doSometing2();
  doSometing3();
  doSometing4();
```

* Original code.

```cpp
void doSomething(int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

int main() {
  for (int i = 0; i < 10; i++) {
    doSomething(10);
    doSomething(20);
    doSomething(30);
    doSomething(40);
  }
}
```

* Let me add a code using **GTimeDiff** module.

```cpp
#include <gtimediff.h> // Add header file

void doSomething(int msec) {
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

int main() {
  GTimeDiff td; // Declare object of the class
  for (int i = 0; i < 10; i++) {
    td.check(1111); // Call check everywhere you would like to check time consuming
    doSomething(10);
    td.check(2222);
    doSomething(20);
    td.check(3333);
    doSomething(30);
    td.check(4444);
    doSomething(40);
  }
  td.report(); // Call report to see the result
}
```

* The result. You get count, elapsed and average time information where check function is called.

```
beg             end             count           elapsed         average                                           
1111            2222            10              101             10                                                
2222            3333            10              201             20                                                
3333            4444            10              301             30                                                
4444            1111            9               361             40  
```

* For more information, see [sample](sample/) code.

## Author
* [Gilbert Lee](http://gilgil.net)

## License
* [GNU GENERAL PUBLIC LICENSE](http://www.gnu.org/copyleft/gpl.html)
