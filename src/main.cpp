#include <iostream>
#include <chrono>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;


static const int PRIMALITY_TESTS = 25;  // Increase for stricter primality testing

// Optimized generating_random_2048_bits function
cpp_int generating_random_2048_bits_integer() {
    boost::random::random_device rd;
    boost::random::independent_bits_engine<boost::random::mt19937, 2048, cpp_int> gen(rd());
    cpp_int prime_candidate = gen();

    // Ensure candidate is odd and has the desired number of bits
    while (prime_candidate % 2 == 0 || prime_candidate.str().length() != 617) {
        prime_candidate = gen();
    }

    return prime_candidate;
}

cpp_int gen_random_number_224_bits_integer() {
    boost::random::random_device rd;
    boost::random::independent_bits_engine< boost::random::mt19937, 224, boost::multiprecision::cpp_int> gen(rd());
    cpp_int divisor = gen();

    // Ensure candidate is odd and has the desired number of bits
    while (divisor % 2 == 0 || divisor.str().length() != 68) {
        divisor = gen();
    }

    return divisor;
}

bool is_prime(const cpp_int& n) {
    return miller_rabin_test(n, PRIMALITY_TESTS);
}

// Modified check_divisibility function for efficiency and error handling
bool check_divisibility(const cpp_int& candidate, const cpp_int& divisor) {

  // Perform modular exponentiation once and store the result
  cpp_int x = powm(candidate - 1, (divisor - 1) / 2, divisor);

  // Check divisibility based on x
  if (x != 1 && x != divisor - 1) {
    return false;
  }

    int p2_bits = 0;
    cpp_int temp = divisor;
    while (temp > 0) {
        temp /= 2;
        p2_bits++;
    }

  // Optimization for divisor 2
  if (divisor == 2) {
    return candidate % 2 != 0;
  }

  // Second Check with optimized exponentiation
  cpp_int x2 = powm(candidate - 1, (p2_bits  - 1) / 2, divisor);

  // Check divisibility based on x2
  if (x2 != 1 && x2 != divisor - 1) {
    return false;
  }

  // Divisible by divisor, no need to check primality
  return true;
}


vector<cpp_int> divisors(){
    
    vector<cpp_int> divisors;

    while(true){

        cpp_int number = gen_random_number_224_bits_integer();

    	if(is_prime(number))
            divisors.push_back(number);

        if (divisors.size() == 99)
            break;

    }

    return divisors;
}

int main() {
    // start the timer
    std::chrono::steady_clock::time_point start_time, current_time;
    long long elapsed_time;
    start_time = chrono::high_resolution_clock::now();
    
    cpp_int candidate;
    cpp_int divisor;

    while (true) {
        // Generate a random 2048-bit integer
        candidate = generating_random_2048_bits_integer();
        
        // calculate the time elapsed
        current_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
        string stringPrime2 = "";

        // Check if the candidate is prime
        if (is_prime(candidate)) {
            // Print the prime number and the time elapsed
            cout << "Found prime number at " << elapsed_time << " seconds" << endl;
            _sleep(1000);
            break;
        } else {
            cout << elapsed_time << " seconds: Not prime, checking next..." << endl;
        }
    }

    unsigned int i = 0;
    vector<cpp_int> divisorList;

    // Find the first prime divisor
    while (true) {

        if (i == 99) {
            i = 0;
            divisors();
        }

        // calculate the time elapsed
        current_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();        

        if(i == 0)
            divisorList = divisors();

        // Optimized loop by checking divisibility efficiently
        if (check_divisibility(candidate, divisorList[i])) {
            cout << "Divisor (prime) Found at " << elapsed_time << " seconds" << endl;
            break;
        }
        else
            cout << elapsed_time << " seconds: Not prime or divisor(" << divisor << "), checking next..." << endl;
        
        i++;
    }
    cout << "Found prime number at " << elapsed_time << " seconds:" << endl;
    cout << "Prime Number" << candidate << endl;
    cout << "Divisor (prime):" << divisor << endl;

    return 0;
}

/*
Found prime number at 63 seconds:
18433049259182714767181667726290567103774094443822788635260934229676238356316256929922059579455560748541138332295721764283306101177504044148324511458130512202258232704820189633391686713248932482580480364063530258616449370587923262489472277788025165353554513896987766680900218713177544312099924974621230238428241880669480222840882298999155377842265536620451944826455335746376050366999648373538058770055841617947326425313600078620877237560305671064279174663014718658767787868527160846576713669221738131172464191789952098855992149251877738461631648929903848718427831225885649869851771264340424957556543630528618739648043
Divisor (prime): 3
*/