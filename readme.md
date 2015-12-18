G Time Diff Library
======================================

# About
* GMem is a simple and robust template based time difference measurement library for C++.

# Install
* GMem consists of only header files, and it requires no library build for using.
    * For Qt user(based on **QElapsedTimer**)
      * Include **gtimediff.pri**.
    * For None Qt user(based on **chrono**)
      * Just include and use header files in src folder.

# Examples
* See the following code. Suppose that it contains a critical routine that consumes too much time. You don't know which function is time comsuming. Anyway, you would like to figure out how long it takes time in each routine. In this case, GMem is a good solution for the problem.

```cpp
  doSometing1();
  doSometing2();
  doSometing3();
  doSometing4();
```

* Original code.

```cpp
void doSomething(int msec)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

int main()
{
  for (int i = 0; i < 10; i++)
  {
    doSomething(10);
    doSomething(20);
    doSomething(30);
    doSomething(40);
  }
}
```

* Let me add a code using **GMem** module.

```cpp
#include <GTimeDiffChrono> // Add header file

void doSomething(int msec)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

int main()
{
  GTimeDiff td; // Declare object of the class
  for (int i = 0; i < 10; i++)
  {
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

* The result. You get count, elapsed and average time information(nano-second) where check function is called.
  
```
beg     end     count   elapsed      average
1111    2222    10      101,155,750  10,115,575
2222    3333    10      201,018,290  20,101,829
3333    4444    10      301,024,734  30,102,473
4444    1111    9       360,927,856  40,103,095
```

* For more information, see [app](app/) codes.

# Supported Platforms
  * Linux / g++ 4.8.4
  * Windows / mingw 4.9.1

# Author
* [Gilbert Lee](http://www.gilgil.net)

# License
* [GNU GENERAL PUBLIC LICENSE](http://www.gnu.org/copyleft/gpl.html)
