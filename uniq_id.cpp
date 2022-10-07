#include <string>
#include <vector>
using namespace std;

#define UNIQ_ID x// Реализуйте этот макрос так, чтобы функция main компилировалась

#define STR_HELPER(x) #x
#define UNIQ_ID STR_HELPER(x)
int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}