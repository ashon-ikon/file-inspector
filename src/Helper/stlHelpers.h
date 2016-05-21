/* 
 * File:   stlHelpers.h
 * Author: yasonibare
 *
 * Created on 20 May 2016, 9:53 AM
 */

#ifndef FINSPECTOR_HELPER_STLHELPERS_H
#define FINSPECTOR_HELPER_STLHELPERS_H

/**
 * Combines two vectors together
 * eg. vector3 = vector1 + vector2
 * @param left
 * @param right
 * @return 
 */
#include <vector>
template <typename T>
std::vector<T> operator+(const std::vector<T>& left, const std::vector<T>& right) {
    std::vector<T> ret;
    ret.reserve(left.size() + right.size());
    ret.insert(ret.end(), left.begin(), left.end());
    ret.insert(ret.end(), right.begin(), right.end());
    
    return ret;
}

/**
 * Combines two vectors together
 * eg. vector1 += vector2
 * @param left
 * @param right
 * @return 
 */
template <typename T>
std::vector<T> &operator+=(std::vector<T>& left, const std::vector<T>& right) {
    left.reserve(left.size() + right.size());
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

#endif /* FINSPECTOR_HELPER_STLHELPERS_H */

