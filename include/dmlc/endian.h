/*!
 *  Copyright (c) 2017 by Contributors
 * \file endian.h
 * \brief Endian testing, need c++11
 */
#ifndef DMLC_ENDIAN_H_
#define DMLC_ENDIAN_H_

#include <cstdint>
#include "./base.h"

#if defined(_WIN32) || defined (_MSC_VER)

/* Windows OS uses little endian exclusively */
#define DMLC_LITTLE_ENDIAN 1

#else

/*! \brief Endian detection via type punning */
constexpr inline int __dmlc_is_system_little_endian() {
  return ((0xDD == (const uint8_t&)0xAABBCCDD) ? 1 : 0);
}

#define DMLC_LITTLE_ENDIAN __dmlc_is_system_little_endian()

#endif

/*! \brief whether serialize using little endian */
#define DMLC_IO_NO_ENDIAN_SWAP (DMLC_LITTLE_ENDIAN == DMLC_IO_USE_LITTLE_ENDIAN)

namespace dmlc {

/*!
 * \brief A generic inplace byte swapping function.
 * \param data The data pointer.
 * \param elem_bytes The number of bytes of the data elements
 * \param num_elems Number of elements in the data.
 * \note Always try pass in constant elem_bytes to enable
 *       compiler optimization
 */
inline void ByteSwap(void* data, size_t elem_bytes, size_t num_elems) {
  for (size_t i = 0; i < num_elems; ++i) {
    uint8_t* bptr = reinterpret_cast<uint8_t*>(data) + elem_bytes * i;
    for (size_t j = 0; j < elem_bytes / 2; ++j) {
      uint8_t v = bptr[elem_bytes - 1 - j];
      bptr[elem_bytes - 1 - j] = bptr[j];
      bptr[j] = v;
    }
  }
}

}  // namespace dmlc
#endif  // DMLC_ENDIAN_H_
