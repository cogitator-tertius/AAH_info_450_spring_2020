#include <iostream>
#include <cstdlib>

using namespace std;
class road_vehicle {
  private:
    int wheels;
    int passengers;
  public:
    void set_wheels(int num) { wheels = num; }
    int get_wheels() { return wheels; }
    void set_pass(int num) { passengers = num; }
    int get_pass() { return passengers; }
};
void timer::run(){
  clock_t t1 = clock();
  cout << "Sleeping for " << seconds << " " << flush;
  while ((clock() / CLOCKS_PER_SEC - t1 / CLOCKS_PER_SEC) < seconds);
  cout << "Done\a" << endl << flush; // ring the bell
}

int main(){
  timer a(2), b("5"), c(0,10);
  a.run();
  b.run();
  c.run();
  return 0;
}