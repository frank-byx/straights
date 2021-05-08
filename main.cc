#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include "client.h"

int main( int argc, char * argv[] ) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();   // set seed to system time by default
  if ( argc > 1 ) {
    try {
      seed = std::stoi( std::string{ argv[1] } );                                // set seed to first command line argument if present
    } catch( std::invalid_argument & e ) {
      std::cerr << e.what() << std::endl;
      return 1;
    } catch( std::out_of_range & e ) {
      std::cerr << e.what() << std::endl;
      return -1;
    }
  }
  Client straightsClient{seed};
  straightsClient.run();
  return 0;
}
