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
cpp_int generating_random_2048_bits_integer(){
    boost::random::random_device rd;
    boost::random::independent_bits_engine< boost::random::mt19937, 6805, boost::multiprecision::cpp_int> gen(rd());
    // boost::random::independent_bits_engine<boost::random::mt19937, 2048 / 32, cpp_int> gen(rd());
    return gen();
}

bool is_prime(const cpp_int& n) {
    
    // if(n <= 1) return false;
    // if(n <= 3) return true;
    // if(n % 2 == 0) return false;
    
    // for(cpp_int i = 3; i * i <=n; i+=2){
    //     if(n % i == 0) return false;
    // }
    // bool result = n / 2 == 0 ? true : false;
    // return result;
    return miller_rabin_test(n, 5); // Adjust the number of iterations as needed
}


int main(){
    string genNumber = "";
    int index = 0;
    int sameNumber = 0;

    auto start_time = chrono::high_resolution_clock::now();

    while(true){
        boost::multiprecision::cpp_int candedate = generating_random_2048_bits_integer();
        // cout << "Generated Number: " << candedate << "\n Number Length: " << candedate.str().length() << endl;
        
        if(sameNumber >= 10){
            cout << "The number is the same as the previous one 10 times" << endl;
            break;
        }

        if(candedate.str().length() < 2048){
            cout << "The number is not 2048 bits long" << endl;
            continue;
        }

        if(genNumber == candedate.str()){
            cout << "The number is the same as the previous one" << endl;
            sameNumber++;
            continue;
        }

        if (is_prime(candedate)){
            cout << "The number is prime" << endl;
            cout << "The number is: \n" << candedate << endl;
            break;
        } else {
            auto current_time = chrono::high_resolution_clock::now();
            auto elupsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
            cout << "Time: " << elupsed_time << "| The number " << index << " with length " << candedate.str().length() << " is not prime" << endl;
            
            genNumber = candedate.str();
            candedate = 0;
            index++;
            continue;   
        }
    }

    return 0;
}