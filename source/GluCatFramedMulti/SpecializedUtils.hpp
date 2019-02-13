/**
Copyright(C) 2018 ga-developers

Repository: https://github.com/ga-developers/ga-benchmark.git

This file is part of the GA-Benchmark project.

GA-Benchmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GA-Benchmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_UTILS_HPP__
#define __GABENCHMARK_SPECIALIZED_UTILS_HPP__

namespace gabenchmark {

    template<typename Scalar>
    constexpr Scalar MakeScalar(Scalar const &scalar) {
        return scalar;
    }

    template<dims_t Dimensions, typename Coordinates>
    constexpr multivector_t MakeVector(Coordinates const &coords) {
        auto e = [](int i) {
            char index[10]{};
            sprintf(index, "{%d}", i < GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ? (i + 1) : (GABENCHMARK_GLUCAT_POSITIVE_GENERATORS - (i + 1)) );
            return multivector_t(index);
        };
        
        multivector_t result;
        for (dims_t i = 0; i != Dimensions; ++i) {
            result += coords[i] * e(i);
        }
        return result;
    }

    template<grade_t Grade, dims_t Dimensions, typename Scalar, typename Factors>
    constexpr multivector_t MakeBlade(Scalar const &scalar, Factors const &factors) {
        multivector_t result = MakeScalar(scalar);
        for (auto const &coords : factors) {
            result ^= MakeVector<Dimensions>(coords);
        }
        return result;
    }

}

#endif // __GABENCHMARK_SPECIALIZED_UTILS_HPP__
