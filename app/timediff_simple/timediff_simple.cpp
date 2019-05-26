#include <chrono>
#include <thread>
#include <gtimediffchrono.h>

int main() {
  GTimeDiffChrono td(__LINE__);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  td.check(__LINE__);
  return 0;
}
