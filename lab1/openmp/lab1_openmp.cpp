#include <omp.h>
#include <iostream> 
#include <cstdint>
#include <chrono>
#include "sha256.h"

void check_commandline_passed_arguments(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Incorrect arguments passed." << std::endl;
        std::cout << "Call application " << argv[0] << " with a single argument [n]." << std::endl;
        std::cout << "Example: " << std::endl;
        std::cout << argv[0] << " 7 -- Application will try to solve crypto puzzle SHA256 with nonce that will generate 7 trailing 0s of the hashed message." << std::endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) 
{
    check_commandline_passed_arguments(argc, argv);

    int difficulty = std::stoi(argv[1]);
    SHA256 sha256;
    const std::string message("Hello World");

    std::cout << "Message:" << std::endl << message << std::endl;
    std::cout << "Hash:" << std::endl << sha256(message) << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Looking for nonce to solve crypto-puzzle with " << difficulty << " difficulty..." << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << "Application with OpenMP parameters:" << std::endl;

    int total_threads, current_thread_id;
    #pragma omp parallel num_threads(4) private(total_threads, current_thread_id)
    {
        current_thread_id = omp_get_thread_num();
        total_threads = omp_get_num_threads();
        #pragma omp critical
        {
            std::cout << "Total threads: " << total_threads << std::endl;
            std::cout << "Current thread: " << current_thread_id << std::endl;
        }
        
        // Insert your function here to solve the crypto puzzle
    }
    // Insert code to output the result

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    std::cout << duration_milliseconds.count() << " milliseconds\n";
}
