//----------------------------------------------------------------------------------------------------------------------
// QB64-PE pointer helper routines
// Copyright (c) 2023 Samuel Gomes
//----------------------------------------------------------------------------------------------------------------------

#pragma once

#include "Common.h"
#include <cstring>

/// @brief Casts a QB64 _OFFSET to an unsigned integer. Needed because QB64 does not allow converting or using _OFFSET in expressions (fully :()
/// @param p A pointer (_OFFSET)
/// @return Pointer value (uintptr_t)
inline uintptr_t CLngPtr(uintptr_t p)
{
    return p;
}

/// @brief Casts a QB64 _OFFSET to a C string. QB64 does the right thing to convert this to a QB64 string
/// @param p A pointer (_OFFSET)
/// @return A C string (char ptr)
inline const char *CStr(uintptr_t p)
{
    return reinterpret_cast<const char *>(p);
}

/// @brief Peeks a BYTE (8-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return BYTE value
inline uint8_t PeekByte(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const uint8_t *>(p) + o);
}

/// @brief Poke a BYTE (8-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n BYTE value
inline void PokeByte(uintptr_t p, uintptr_t o, uint8_t n)
{
    *(reinterpret_cast<uint8_t *>(p) + o) = n;
}

/// @brief Peek an INTEGER (16-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return INTEGER value
inline uint16_t PeekInteger(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const uint16_t *>(p) + o);
}

/// @brief Poke an INTEGER (16-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n INTEGER value
inline void PokeInteger(uintptr_t p, uintptr_t o, uint16_t n)
{
    *(reinterpret_cast<uint16_t *>(p) + o) = n;
}

/// @brief Peek a LONG (32-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return LONG value
inline uint32_t PeekLong(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const uint32_t *>(p) + o);
}

/// @brief Poke a LONG (32-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n LONG value
inline void PokeLong(uintptr_t p, uintptr_t o, uint32_t n)
{
    *(reinterpret_cast<uint32_t *>(p) + o) = n;
}

/// @brief Peek a INTEGER64 (64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return INTEGER64 value
inline uint64_t PeekInteger64(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const uint64_t *>(p) + o);
}

/// @brief Poke a INTEGER64 (64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n INTEGER64 value
inline void PokeInteger64(uintptr_t p, uintptr_t o, uint64_t n)
{
    *(reinterpret_cast<uint64_t *>(p) + o) = n;
}

/// @brief Peek a SINGLE (32-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return SINGLE value
inline float PeekSingle(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const float *>(p) + o);
}

/// @brief Poke a SINGLE (32-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n SINGLE value
inline void PokeSingle(uintptr_t p, uintptr_t o, float n)
{
    *(reinterpret_cast<float *>(p) + o) = n;
}

/// @brief Peek a DOUBLE (64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return DOUBLE value
inline double PeekDouble(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const double *>(p) + o);
}

/// @brief Poke a DOUBLE (64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n DOUBLE value
inline void PokeDouble(uintptr_t p, uintptr_t o, double n)
{
    *(reinterpret_cast<double *>(p) + o) = n;
}

/// @brief Peek an OFFSET (32/64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @return DOUBLE value
inline uintptr_t PeekOffset(uintptr_t p, uintptr_t o)
{
    return *(reinterpret_cast<const uintptr_t *>(p) + o);
}

/// @brief Poke an OFFSET (32/64-bits) value at p + o
/// @param p Pointer base
/// @param o Offset from base
/// @param n DOUBLE value
inline void PokeOffset(uintptr_t p, uintptr_t o, uintptr_t n)
{
    *(reinterpret_cast<uintptr_t *>(p) + o) = n;
}

/// @brief Gets a UDT value from a pointer positon offset by o. Same as t = p[o]
/// @param p The base pointer
/// @param o Offset from base (each offset is t_size bytes)
/// @param t A pointer to the UDT variable
/// @param t_size The size of the UTD variable in bytes
inline void PeekType(uintptr_t p, uintptr_t o, uintptr_t t, size_t t_size)
{
    memcpy((void *)t, (const uint8_t *)p + (o * t_size), t_size);
}

/// @brief Sets a UDT value to a pointer position offset by o. Same as p[o] = t
/// @param p The base pointer
/// @param o Offset from base (each offset is t_size bytes)
/// @param t A pointer to the UDT variable
/// @param t_size The size of the UTD variable in bytes
inline void PokeType(uintptr_t p, uintptr_t o, uintptr_t t, size_t t_size)
{
    memcpy((uint8_t *)p + (o * t_size), (void *)t, t_size);
}

/// @brief Peek a character value in a string. Zero based, faster and unsafe than ASC
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The ASCII character at position o
inline uint8_t PeekStringByte(const char *s, uintptr_t o)
{
    return s[o];
}

/// @brief Poke a character value in a string. Zero based, faster and unsafe than ASC
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The ASCII character at position o
inline void PokeStringByte(char *s, uintptr_t o, uint8_t n)
{
    s[o] = n;
}

/// @brief Peek an integer value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The integer at position o
inline uint16_t PeekStringInteger(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const uint16_t *>(&s[o * sizeof(uint16_t)]);
}

/// @brief Poke an integer value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The integer at position o
inline void PokeStringInteger(char *s, uintptr_t o, uint16_t n)
{
    *reinterpret_cast<uint16_t *>(&s[o * sizeof(uint16_t)]) = n;
}

/// @brief Peek a long value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The long at position o
inline uint32_t PeekStringLong(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const uint32_t *>(&s[o * sizeof(uint32_t)]);
}

/// @brief Poke an long value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The long at position o
inline void PokeStringLong(char *s, uintptr_t o, uint32_t n)
{
    *reinterpret_cast<uint32_t *>(&s[o * sizeof(uint32_t)]) = n;
}

/// @brief Peek an integer64 value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The integer64 at position o
inline uint64_t PeekStringInteger64(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const uint64_t *>(&s[o * sizeof(uint64_t)]);
}

/// @brief Poke an integer64 value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The integer64 at position o
inline void PokeStringInteger64(char *s, uintptr_t o, uint64_t n)
{
    *reinterpret_cast<uint64_t *>(&s[o * sizeof(uint64_t)]) = n;
}

/// @brief Peek a single value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The single at position o
inline float PeekStringSingle(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const float *>(&s[o * sizeof(float)]);
}

/// @brief Poke a single value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The single at position o
inline void PokeStringSingle(char *s, uintptr_t o, float n)
{
    *reinterpret_cast<float *>(&s[o * sizeof(float)]) = n;
}

/// @brief Peek a double value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The double at position o
inline double PeekStringDouble(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const double *>(&s[o * sizeof(double)]);
}

/// @brief Poke a double value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The double at position o
inline void PokeStringDouble(char *s, uintptr_t o, double n)
{
    *reinterpret_cast<double *>(&s[o * sizeof(double)]) = n;
}

/// @brief Peek an Offset value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @return The Offset at position o
inline uintptr_t PeekStringOffset(const char *s, uintptr_t o)
{
    return *reinterpret_cast<const uintptr_t *>(&s[o * sizeof(uint64_t)]);
}

/// @brief Poke an Offset value in a string
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param n The Offset at position o
inline void PokeStringOffset(char *s, uintptr_t o, uintptr_t n)
{
    *reinterpret_cast<uintptr_t *>(&s[o * sizeof(uint64_t)]) = n;
}

/// @brief Gets a UDT value from a string offset
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param t A pointer to the UDT variable
/// @param t_size The size of the UTD variable in bytes
inline void PeekStringType(const char *s, uintptr_t o, uintptr_t t, size_t t_size)
{
    memcpy((void *)t, s + (o * t_size), t_size);
}

/// @brief Sets a UDT value to a string offset
/// @param s A QB64 string
/// @param o Offset from base (zero based)
/// @param t A pointer to the UDT variable
/// @param t_size The size of the UTD variable in bytes
inline void PokeStringType(char *s, uintptr_t o, uintptr_t t, size_t t_size)
{
    memcpy(s + (o * t_size), (void *)t, t_size);
}