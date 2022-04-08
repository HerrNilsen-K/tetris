//
// Created by karl on 08.04.22.
//

#ifndef TETRIS_RANDOMGENERATOR_HPP
#define TETRIS_RANDOMGENERATOR_HPP

#include <random>

namespace generate {
    //Generate function for random numbers between min and max
    template<typename T>
    T random(T min, T max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dis(min, max);
        return dis(gen);
    }
}

#endif //TETRIS_RANDOMGENERATOR_HPP
