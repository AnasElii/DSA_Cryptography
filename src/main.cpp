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


// Generating a random number
cpp_int generating_random_2048_bits(){
    boost::random::random_device rd;
    boost::random::independent_bits_engine< boost::random::mt19937, 2048, boost::multiprecision::cpp_int> gen(rd());
    return gen();
}

cpp_int generating_random_2048_bits_integer() {
    return boost::multiprecision::cpp_int(generating_random_2048_bits());
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

bool check_divisibility(cpp_int candedate, cpp_int prime2) {
    
    int p2_bits = 0;
    cpp_int temp = prime2;
    while (temp > 0) {
        temp = temp / 2;
        p2_bits++;
    }

    cpp_int x = powm(candedate-1, (p2_bits - 1) / 2, prime2);

    if (x != 1) {
        cout << "prime2 is not a divisor!" << endl;
        return false;
    }


    if (is_prime(prime2)) {
        cout << "prime2 is a devidor and prime!" << endl;
        return true;
    }
    else {
        cout << "prime 2 is not a devidor or a prime" << endl;
        return false;
    }
}

int main(){
    string genNumber = "";
    int index = 0;

    auto start_time = chrono::high_resolution_clock::now();
    auto candedate = generating_random_2048_bits_integer();
    auto prime2 = generating_random_224_bits_integer();

    while(true){

       /* if(candedate.str().length() != 617){
            cout << "The number is not 2048 bits long" << endl;
            continue;
        }*/

        auto current_time = chrono::high_resolution_clock::now();
        auto elupsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();

        if (is_prime(candedate)){
            cout << "1th Prime Number found At " << elupsed_time << " | number is : \n" << candedate << endl;

            while (true) {
                prime2 = generating_random_224_bits_integer();

                if (check_divisibility(candedate, prime2)) {                    
                    break;
                }
            
            }

            cout << "1th Prime number: " << candedate << endl;
            cout << "2th Prime number: " << prime2 << endl;

            break;
        } else {
            cout << "Time: " << elupsed_time << "| The number " << index << " with length " << candedate.str().length() << " is not prime" << endl;
            
            genNumber = candedate.str();
            candedate = 0;
            index++;
            candedate = generating_random_2048_bits_integer();
            continue;   
        }
    }

    return 0;
}