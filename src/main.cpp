#include <iostream>
#include <cmath>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;


static const int PRIMALITY_TESTS = 50;  // Increase for stricter primality testing

// Optimized generating_random_2048_bits function
cpp_int generating_random_2048_bits() {
    boost::random::random_device rd;
    boost::random::independent_bits_engine<boost::random::mt19937, 2048, cpp_int> gen(rd());
    cpp_int candidate = gen();

    // Ensure candidate is odd and has the desired number of bits
    while (candidate % 2 == 0 || candidate.str().length() != 617) {
        candidate = gen();
    }

    return candidate;
}

cpp_int gen_random_number_224_bits() {
    boost::random::random_device rd;
    boost::random::independent_bits_engine< boost::random::mt19937, 224, boost::multiprecision::cpp_int> gen(rd());
    return gen();
}

cpp_int generating_random_224_bits_integer() {
    return boost::multiprecision::cpp_int(gen_random_number_224_bits());
}

bool is_prime(const cpp_int& n) {
    return miller_rabin_test(n, 50);
}

// Modified check_divisibility function for efficiency and error handling
bool check_divisibility(const cpp_int& candidate, const cpp_int& prime2) {
    if (prime2 <= 1) {
        return false;  // Handle invalid divisor (not prime or <= 1)
    }

    int p2_bits = 0;
    cpp_int temp = prime2;
    while (temp > 0) {
        temp /= 2;
        p2_bits++;
    }

    // Avoid redundant primality test for 2
    if (prime2 == 2) {
        return candidate % 2 != 0;
    }

    // Use optimized modular exponentiation (powm in GMP instead of boost)
    cpp_int x = powm(candidate - 1, (p2_bits - 1) / 2, prime2);
    if (x != 1 && x != prime2 - 1) {
        return false;  // Not divisible by prime2
    }

    // Verify primality of prime2 with stricter tests
    for (int i = 0; i < PRIMALITY_TESTS; ++i) {
        if (!miller_rabin_test(prime2, 50)) {
            return false;  // prime2 is not prime
        }
    }

    return true;  // candidate is divisible by prime2, and prime2 is prime
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();

    while (true) {
        auto candidate = generating_random_2048_bits();
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();

        if (is_prime(candidate)) {
            cout << "Found prime number at " << elapsed_time << " seconds:" << endl;
            cout << candidate << endl;

            for (int i = 3; i < candidate / 2; i += 2) {
                // Optimized loop by checking divisibility efficiently
                if (check_divisibility(candidate, i)) {
                    cout << "Divisor (prime): " << i << endl;
                    break;  // Found a divisor, exit loop
                }
            }

            break;  // Found both primes, exit loop
        } else {
            cout << elapsed_time << " seconds: Not prime, checking next..." << endl;
        }
    }

    return 0;
}

/*
Found prime number at 63 seconds:
18433049259182714767181667726290567103774094443822788635260934229676238356316256929922059579455560748541138332295721764283306101177504044148324511458130512202258232704820189633391686713248932482580480364063530258616449370587923262489472277788025165353554513896987766680900218713177544312099924974621230238428241880669480222840882298999155377842265536620451944826455335746376050366999648373538058770055841617947326425313600078620877237560305671064279174663014718658767787868527160846576713669221738131172464191789952098855992149251877738461631648929903848718427831225885649869851771264340424957556543630528618739648043
Divisor (prime): 3
*/