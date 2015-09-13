/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl

Copyright(c) 2014 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <UnitTest++/UnitTest++.h>

#include <cstdint>

#include "../binary.h"
#include "../bitset.h"
#include "../fnv_1.h"
#include "../integral_limits.h"

#undef max

// Count bits the easy way.
template <typename T>
size_t test_count(T value)
{
  size_t count = 0;

  for (size_t i = 0; i < etl::integral_limits<T>::bits; ++i)
  {
    if ((value & (T(1) << i)) != 0)
    {
      ++count;
    }
  }

  return count;
}

// Check parity the easy way.
template <typename T>
size_t test_parity(T value)
{
  size_t count = test_count(value);

  return count & 1;
}

// Power of 2.
uint64_t test_power_of_2(int power)
{
  uint64_t result = 1;

  for (int i = 0; i < power; ++i)
  {
    result *= 2;
  }

  return result;
}

// Fold bits.
template <typename TReturn>
TReturn test_fold_bits(uint64_t value, int size)
{
  int bits_remaining = 64;
  uint64_t mask = test_power_of_2(size) - 1;
  TReturn  result = 0;

  while (bits_remaining > size)
  {
    result = result ^ (value & mask);
    value  = value >> size;
    bits_remaining -= size;
  }

  result = result ^ (value & mask);

  return result;
}

namespace
{
  SUITE(test_binary)
  {
    //*************************************************************************
    TEST(test_rotate_left8)
    {
      uint8_t value;

      value = 0x00;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0, int(value));

      value = 0x21;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x42, int(value));

      value = 0x42;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x84, int(value));

      value = 0x84;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x09, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 2);
      CHECK_EQUAL(0xDE, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 3);
      CHECK_EQUAL(0xBD, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 4);
      CHECK_EQUAL(0x7B, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 5);
      CHECK_EQUAL(0xF6, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 6);
      CHECK_EQUAL(0xED, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 7);
      CHECK_EQUAL(0xDB, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 8);
      CHECK_EQUAL(0xB7, int(value));

      value = 0xB7;
      value = etl::rotate_left(value, 9);
      CHECK_EQUAL(0x6F, int(value));
    }

    //*************************************************************************
    TEST(test_rotate_left16)
    {
      uint16_t value;

      value = 0x0000;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0, value);

      value = 0x8421;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x0843, value);

      value = 0x0843;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x1086, value);

      value = 0x1086;
      value = etl::rotate_left(value);
      CHECK_EQUAL(0x210C, value);

      value = 0xB73C;
      value = etl::rotate_left(value, 2);
      CHECK_EQUAL(0xDCF2, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 3);
      CHECK_EQUAL(0xB9E5, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 4);
      CHECK_EQUAL(0x73CB, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 5);
      CHECK_EQUAL(0xE796, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 6);
      CHECK_EQUAL(0xCF2D, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 7);
      CHECK_EQUAL(0x9E5B, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 8);
      CHECK_EQUAL(0x3CB7, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 9);
      CHECK_EQUAL(0x796E, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 9);
      CHECK_EQUAL(0x796E, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 10);
      CHECK_EQUAL(0xF2DC, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 11);
      CHECK_EQUAL(0xE5B9, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 12);
      CHECK_EQUAL(0xCB73, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 13);
      CHECK_EQUAL(0x96E7, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 14);
      CHECK_EQUAL(0x2DCF, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 15);
      CHECK_EQUAL(0x5B9E, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 16);
      CHECK_EQUAL(0xB73C, int(value));

      value = 0xB73C;
      value = etl::rotate_left(value, 17);
      CHECK_EQUAL(0x6E79, int(value));
    }

    //*************************************************************************
    TEST(test_rotate_right8)
    {
      uint8_t value;

      value = 0x00;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0, int(value));

      value = 0x21;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0x90, int(value));

      value = 0x42;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0x21, int(value));

      value = 0x84;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0x42, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 2);
      CHECK_EQUAL(0xED, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 3);
      CHECK_EQUAL(0xF6, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 4);
      CHECK_EQUAL(0x7B, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 5);
      CHECK_EQUAL(0xBD, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 6);
      CHECK_EQUAL(0xDE, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 7);
      CHECK_EQUAL(0x6F, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 8);
      CHECK_EQUAL(0xB7, int(value));

      value = 0xB7;
      value = etl::rotate_right(value, 9);
      CHECK_EQUAL(0xDB, int(value));
    }

    //*************************************************************************
    TEST(test_rotate_right16)
    {
      uint16_t value;

      value = 0x0000;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0, value);

      value = 0x8421;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0xC210, value);

      value = 0xC210;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0x6108, value);

      value = 0x6108;
      value = etl::rotate_right(value);
      CHECK_EQUAL(0x3084, value);

      value = 0xB73C;
      value = etl::rotate_right(value, 2);
      CHECK_EQUAL(0x2DCF, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 3);
      CHECK_EQUAL(0x96E7, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 4);
      CHECK_EQUAL(0xCB73, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 5);
      CHECK_EQUAL(0xE5B9, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 6);
      CHECK_EQUAL(0xF2DC, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 7);
      CHECK_EQUAL(0x796E, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 8);
      CHECK_EQUAL(0x3CB7, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 9);
      CHECK_EQUAL(0x9E5B, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 9);
      CHECK_EQUAL(0x9E5B, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 10);
      CHECK_EQUAL(0xCF2D, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 11);
      CHECK_EQUAL(0xE796, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 12);
      CHECK_EQUAL(0x73CB, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 13);
      CHECK_EQUAL(0xB9E5, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 14);
      CHECK_EQUAL(0xDCF2, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 15);
      CHECK_EQUAL(0x6E79, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 16);
      CHECK_EQUAL(0xB73C, int(value));

      value = 0xB73C;
      value = etl::rotate_right(value, 17);
      CHECK_EQUAL(0x5B9E, int(value));
    }

    //*************************************************************************
    TEST(test_rotate16)
    {
      uint16_t value;

      value = 0xB73C;
      value = etl::rotate(value, 4);
      CHECK_EQUAL(0x73CB, int(value));

      value = 0xB73C;
      value = etl::rotate(value, -4);
      CHECK_EQUAL(0xCB73, int(value));
    }

    //*************************************************************************
    TEST(test_reverse_bits8)
    {
      uint8_t value;

      value = 0xF0;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x0F, int(value));

      value = 0x0F;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0xF0, int(value));

      value = 0xA5;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0xA5, int(value));

      value = 0x5A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5A, int(value));

      value = 0xCA;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x53, int(value));

      value = 0xAC;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x35, int(value));
    }

    //*************************************************************************
    TEST(test_reverse_bits16)
    {
      uint16_t value;

      value = 0xFC5A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5A3F, value);

      value = 0x5A5A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5A5A, value);

      value = 0xA5A5;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0xA5A5, value);
    }

    //*************************************************************************
    TEST(test_reverse_bits32)
    {
      uint32_t value;

      value = 0xF0C3A55A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5AA5C30F, value);

      value = 0xA5A5A5A5;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0xA5A5A5A5, value);

      value = 0x5A5A5A5A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5A5A5A5A, value);
    }

    //*************************************************************************
    TEST(test_reverse_bits64)
    {
      uint64_t value;

      value = 0x1234ABCDF0C3A55A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5AA5C30FB3D52C48, value);

      value = 0xA5A5A5A5A5A5A5A5;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0xA5A5A5A5A5A5A5A5, value);

      value = 0x5A5A5A5A5A5A5A5A;
      value = etl::reverse_bits(value);
      CHECK_EQUAL(0x5A5A5A5A5A5A5A5A, value);
    }

    //*************************************************************************
    TEST(test_reverse_bytes16)
    {
      uint16_t value;

      value = 0xFC5A;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0x5AFC, value);

      value = 0x5AA5;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0xA55A, value);

      value = 0xA55A;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0x5AA5, value);
    }

    //*************************************************************************
    TEST(test_reverse_bytes32)
    {
      uint32_t value;

      value = 0xF0C3A55A;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0x5AA5C3F0, value);

      value = 0xA5A55A5A;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0x5A5AA5A5, value);

      value = 0x5A5AA5A5;
      value = etl::reverse_bytes(value);
      CHECK_EQUAL(0xA5A55A5A, value);
    }

    //*************************************************************************
    TEST(test_binary_to_gray8)
    {
      uint8_t last_gray = 0;

      for (size_t i = 1; i <= std::numeric_limits<uint8_t>::max(); ++i)
      {
        uint8_t gray = etl::binary_to_gray(uint8_t(i));
        uint8_t result = gray ^ last_gray;
        last_gray = gray;

        bool pass = ((result != 0) && !(result & (result - 1)));

        // Only one bit should be set.
        CHECK(pass);
      }
    }

    //*************************************************************************
    TEST(test_binary_to_gray16)
    {
      uint16_t last_gray = 0;

      for (size_t i = 1; i <= std::numeric_limits<uint16_t>::max(); ++i)
      {
        uint16_t gray   = etl::binary_to_gray(uint16_t(i));
        uint16_t result = gray ^ last_gray;
        last_gray       = gray;

        bool pass = ((result != 0) && !(result & (result - 1)));

        // Only one bit should be set.
        CHECK(pass);
      }
    }

    //*************************************************************************
    TEST(test_binary_to_gray32)
    {
      etl::fnv_1a_32<> hash;

      hash.add(1);

      for (size_t i = 1; i < 1000000; ++i)
      {
        uint32_t value = hash.value();

        uint32_t last_gray = etl::binary_to_gray(uint32_t(value));
        uint32_t gray      = etl::binary_to_gray(uint32_t(value + 1));
        uint32_t result    = gray ^ last_gray;

        bool pass = ((result != 0) && !(result & (result - 1)));

        hash.add(1);

        // Only one bit should be set.
        CHECK(pass);
      }
    }

    //*************************************************************************
    TEST(test_binary_to_gray64)
    {
      etl::fnv_1a_64<> hash;

      hash.add(1);

      for (size_t i = 1; i < 1000000; ++i)
      {
        uint64_t value = hash.value();

        uint64_t last_gray = etl::binary_to_gray(uint64_t(value));
        uint64_t gray = etl::binary_to_gray(uint64_t(value + 1));
        uint64_t result = gray ^ last_gray;

        bool pass = ((result != 0) && !(result & (result - 1)));

        hash.add(1);

        // Only one bit should be set.
        CHECK(pass);
      }
    }

    //*************************************************************************
    TEST(test_count_bits_8)
    {
      for (size_t i = 1; i <= std::numeric_limits<uint16_t>::max(); ++i)
      {
        CHECK_EQUAL(test_count(i), etl::count_bits(i));
      }
    }

    //*************************************************************************
    TEST(test_count_bits_16)
    {
      for (size_t i = 1; i <= std::numeric_limits<uint16_t>::max(); ++i)
      {
        CHECK_EQUAL(test_count(i), etl::count_bits(i));
      }
    } 
    
    //*************************************************************************
    TEST(test_count_bits_32)
    {
      etl::fnv_1a_32<> hash;

      for (size_t i = 0; i < 1000000; ++i)
      {
        hash.add(1);

        uint32_t value = hash.value();

        CHECK_EQUAL(test_count(value), etl::count_bits(value));
      }
    }

    //*************************************************************************
    TEST(test_count_bits_64)
    {
      etl::fnv_1a_64<> hash;

      for (size_t i = 0; i < 1000000; ++i)
      {
        hash.add(1);

        uint64_t value = hash.value();

        CHECK_EQUAL(test_count(value), etl::count_bits(value));
      }
    }

    //*************************************************************************
    TEST(test_parity_8)
    {
      for (size_t i = 1; i <= std::numeric_limits<uint8_t>::max(); ++i)
      {
        CHECK_EQUAL(test_parity(i), etl::parity(i));
      }
    }

    //*************************************************************************
    TEST(test_parity_16)
    {
      for (size_t i = 1; i <= std::numeric_limits<uint16_t>::max(); ++i)
      {
        CHECK_EQUAL(test_parity(i), etl::parity(i));
      }
    }

    //*************************************************************************
    TEST(test_parity_32)
    {
      etl::fnv_1a_32<> hash;

      for (size_t i = 0; i < 1000000; ++i)
      {
        hash.add(1);

        uint32_t value = hash.value();

        CHECK_EQUAL(test_parity(value), etl::parity(value));
      }
    }

    //*************************************************************************
    TEST(test_parity_64)
    {
      etl::fnv_1a_64<> hash;

      for (size_t i = 0; i < 1000000; ++i)
      {
        hash.add(1);

        uint64_t value = hash.value();

        CHECK_EQUAL(test_parity(value), etl::parity(value));
      }
    }

    //*************************************************************************
    TEST(test_fold_bits)
    {
      const uint64_t data = 0xF8E9DACBBCAD9E8F;

      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  1), (etl::fold_bits<uint64_t,  1>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  2), (etl::fold_bits<uint64_t,  2>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  3), (etl::fold_bits<uint64_t,  3>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  4), (etl::fold_bits<uint64_t,  4>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  5), (etl::fold_bits<uint64_t,  5>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  6), (etl::fold_bits<uint64_t,  6>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  7), (etl::fold_bits<uint64_t,  7>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  8), (etl::fold_bits<uint64_t,  8>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data,  9), (etl::fold_bits<uint64_t,  9>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 10), (etl::fold_bits<uint64_t, 10>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 11), (etl::fold_bits<uint64_t, 11>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 12), (etl::fold_bits<uint64_t, 12>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 13), (etl::fold_bits<uint64_t, 13>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 14), (etl::fold_bits<uint64_t, 14>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 15), (etl::fold_bits<uint64_t, 15>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 16), (etl::fold_bits<uint64_t, 16>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 17), (etl::fold_bits<uint64_t, 17>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 18), (etl::fold_bits<uint64_t, 18>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 19), (etl::fold_bits<uint64_t, 19>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 20), (etl::fold_bits<uint64_t, 20>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 21), (etl::fold_bits<uint64_t, 21>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 22), (etl::fold_bits<uint64_t, 22>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 23), (etl::fold_bits<uint64_t, 23>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 24), (etl::fold_bits<uint64_t, 24>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 25), (etl::fold_bits<uint64_t, 25>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 26), (etl::fold_bits<uint64_t, 26>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 27), (etl::fold_bits<uint64_t, 27>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 28), (etl::fold_bits<uint64_t, 28>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 29), (etl::fold_bits<uint64_t, 29>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 30), (etl::fold_bits<uint64_t, 30>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 31), (etl::fold_bits<uint64_t, 31>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 32), (etl::fold_bits<uint64_t, 32>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 33), (etl::fold_bits<uint64_t, 33>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 34), (etl::fold_bits<uint64_t, 34>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 35), (etl::fold_bits<uint64_t, 35>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 36), (etl::fold_bits<uint64_t, 36>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 37), (etl::fold_bits<uint64_t, 37>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 38), (etl::fold_bits<uint64_t, 38>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 39), (etl::fold_bits<uint64_t, 39>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 40), (etl::fold_bits<uint64_t, 40>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 41), (etl::fold_bits<uint64_t, 41>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 42), (etl::fold_bits<uint64_t, 42>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 43), (etl::fold_bits<uint64_t, 43>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 44), (etl::fold_bits<uint64_t, 44>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 45), (etl::fold_bits<uint64_t, 45>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 46), (etl::fold_bits<uint64_t, 46>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 47), (etl::fold_bits<uint64_t, 47>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 48), (etl::fold_bits<uint64_t, 48>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 49), (etl::fold_bits<uint64_t, 49>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 50), (etl::fold_bits<uint64_t, 50>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 51), (etl::fold_bits<uint64_t, 51>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 52), (etl::fold_bits<uint64_t, 52>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 53), (etl::fold_bits<uint64_t, 53>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 54), (etl::fold_bits<uint64_t, 54>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 55), (etl::fold_bits<uint64_t, 55>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 56), (etl::fold_bits<uint64_t, 56>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 57), (etl::fold_bits<uint64_t, 57>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 58), (etl::fold_bits<uint64_t, 58>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 59), (etl::fold_bits<uint64_t, 59>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 60), (etl::fold_bits<uint64_t, 60>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 61), (etl::fold_bits<uint64_t, 61>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 62), (etl::fold_bits<uint64_t, 62>(data)));
      CHECK_EQUAL(test_fold_bits<uint64_t>(data, 63), (etl::fold_bits<uint64_t, 63>(data)));
    }
  };
}
