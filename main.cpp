#include <iostream>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/multiprecision/miller_rabin.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;


// Generating a random number
// cpp_int generating_random_100_bits_integer(){
//     random_device rd;
//     independent_bits_engine<mt19937, 6805, cpp_int> gen(rd());
//     return gen();
// }

// bool is_prime(const cpp_int &n){
//     if(n <= 1){
//         return false;
//     }
//     if(n <= 3){
//         return true;
//     }
//     if(n % 2 == 0 || n % 3 == 0){
//         return false;
//     }
//     for(cpp_int i = 5; i * i <= n; i = i + 6){
//         if(n % i == 0 || n % (i + 2) == 0){
//             return false;
//         }
//     }
//     return true;
// }

bool is_prime(const cpp_int& n) {
    return miller_rabin_test(n, 25); // Adjust the number of iterations as needed
}


int main(){
    int n;
    // cout << "Enter a number" << endl;
    // cin >> n;

    // if(n >= 1){
    //     n % 2 == 0 ? cout << "Not prime" : cout << "Prime\n";
    // }
    boost::random::random_device rd;
    independent_bits_engine<mt19937, 100, cpp_int> gen(rd());
    cout << gen() << endl;

    // cpp_int candedate = generating_random_100_bits_integer();
    // cout << "Generated Number: " << candedate << "\n Number Length: " << candedate.str().length() << endl;

//    int nonce = 0;
//    while(true){
//        cpp_int candedate = generating_random_100_bits_integer();
//        if(!is_prime(candedate)){
//             cout << "Nonce: " << nonce << endl;
//             nonce++;
//             continue;   
//         }
        
//         cout << "Nonce: " << nonce << endl;
//         cout << "Prime: " << candedate << endl;
//         break;

//    }
    return 0;
}

// P
// 27609917172339383022350711843748160763540369353719821680895911657156395645376444554108157590203098522345448312572800098543463107048833326042379946529004743900873768403815236148268851687304645149604078398303265247884228758447160906982209269907994319811284822807311655020133871812795937132774137415998816564396786352321841873701982840551286760664924908980226987876005556175159752203280153251836802718164491139608124464069682190116593043833605246850149390349833471090654981922673823659798717454448963045554857831604690776454055911564594557538060114158447923994411560782699749199223269973625937312493424065176395889416101

// Q
// 15749856326764396990596796320634368940014372725240818555524247883959