#include <memory>
using std::unique_ptr;
using std::make_unique;


unique_ptr<int> p = make_unique<int>(5);


