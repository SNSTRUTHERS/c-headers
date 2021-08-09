/**
 * @file atomics.h
 * @author Simon Bolivar
 * @date 27 Jul 2021
 * 
 * @brief Cross-compiler atomic operations.
 * 
 * @copyright LGPL3
 */

#ifndef ATOMICS_H_
#define ATOMICS_H_

#include "macrodefs.h"

/**
 * @fn bool atomic_compare_exchange_strong_int8(
 *         volatile atomic_int8* a,
 *         int8_t* b,
 *         int8_t c
 *     )
 * @brief Performs a compare-exchange operation on an 8-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in,out] b Pointer to an 8-bit signed integer to swap with @e a.
 * @param[in]     c An 8-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_int8
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_uint8(
 *         volatile atomic_uint8* a,
 *         uint8_t* b,
 *         uint8_t c
 *     )
 * @brief Performs a compare-exchange operation on an 8-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in,out] b Pointer to an 8-bit unsigned integer to swap with @e a.
 * @param[in]     c An 8-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_uint8
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_int16(
 *         volatile atomic_int16* a,
 *         int16_t* b,
 *         int16_t c
 *     )
 * @brief Performs a compare-exchange operation on an 16-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in,out] b Pointer to a 16-bit signed integer to swap with @e a.
 * @param[in]     c A 16-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_int16
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_uint16(
 *         volatile atomic_uint16* a,
 *         uint16_t* b,
 *         uint16_t c
 *     )
 * @brief Performs a compare-exchange operation on an 16-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in,out] b Pointer to a 16-bit unsigned integer to swap with @e a.
 * @param[in]     c A 16-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_uint16
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_int32(
 *         volatile atomic_int32* a,
 *         int32_t* b,
 *         int32_t c
 *     )
 * @brief Performs a compare-exchange operation on an 32-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in,out] b Pointer to a 32-bit signed integer to swap with @e a.
 * @param[in]     c A 32-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_int32
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_uint32(
 *         volatile atomic_uint32* a,
 *         uint32_t* b,
 *         uint32_t c
 *     )
 * @brief Performs a compare-exchange operation on an 32-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in,out] b Pointer to a 32-bit unsigned integer to swap with @e a.
 * @param[in]     c A 32-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_uint32
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_int64(
 *         volatile atomic_int64* a,
 *         int64_t* b,
 *         int64_t c
 *     )
 * @brief Performs a compare-exchange operation on an 64-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in,out] b Pointer to a 64-bit signed integer to swap with @e a.
 * @param[in]     c A 64-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_int64
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_strong_uint64(
 *         volatile atomic_uint64* a,
 *         uint64_t* b,
 *         uint64_t c
 *     )
 * @brief Performs a compare-exchange operation on an 64-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in,out] b Pointer to a 64-bit unsigned integer to swap with @e a.
 * @param[in]     c A 64-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the weak version of this function, this is required to return
 *       @c true when @e c equals the value at @e a. On certain machines, this
 *       this can result in a drop in performance when looping.
 * 
 * @sa atomic_compare_exchange_weak_uint64
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_int8(
 *         volatile atomic_int8* a,
 *         int8_t* b,
 *         int8_t c
 *     )
 * @brief Performs a compare-exchange operation on an 8-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in,out] b Pointer to an 8-bit signed integer to swap with @e a.
 * @param[in]     c An 8-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_int8
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_uint8(
 *         volatile atomic_uint8* a,
 *         uint8_t* b,
 *         uint8_t c
 *     )
 * @brief Performs a compare-exchange operation on an 8-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in,out] b Pointer to an 8-bit unsigned integer to swap with @e a.
 * @param[in]     c An 8-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_uint8
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_int16(
 *         volatile atomic_int16* a,
 *         int16_t* b,
 *         int16_t c
 *     )
 * @brief Performs a compare-exchange operation on a 16-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in,out] b Pointer to a 16-bit signed integer to swap with @e a.
 * @param[in]     c A 16-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_int16
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_uint16(
 *         volatile atomic_uint16* a,
 *         uint16_t* b,
 *         uint16_t c
 *     )
 * @brief Performs a compare-exchange operation on a 16-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in,out] b Pointer to a 16-bit unsigned integer to swap with @e a.
 * @param[in]     c A 16-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_uint16
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_int32(
 *         volatile atomic_int32* a,
 *         int32_t* b,
 *         int32_t c
 *     )
 * @brief Performs a compare-exchange operation on a 32-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in,out] b Pointer to a 32-bit signed integer to swap with @e a.
 * @param[in]     c A 32-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_int32
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_uint32(
 *         volatile atomic_uint32* a,
 *         uint32_t* b,
 *         uint32_t c
 *     )
 * @brief Performs a compare-exchange operation on a 32-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in,out] b Pointer to a 32-bit unsigned integer to swap with @e a.
 * @param[in]     c A 32-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_uint32
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_int64(
 *         volatile atomic_int64* a,
 *         int64_t* b,
 *         int64_t c
 *     )
 * @brief Performs a compare-exchange operation on a 64-bit signed integer.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in,out] b Pointer to a 64-bit signed integer to swap with @e a.
 * @param[in]     c A 64-bit signed integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_int64
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn bool atomic_compare_exchange_weak_uint64(
 *         volatile atomic_uint64* a,
 *         uint64_t* b,
 *         uint64_t c
 *     )
 * @brief Performs a compare-exchange operation on a 64-bit unsigned integer.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in,out] b Pointer to a 64-bit unsigned integer to swap with @e a.
 * @param[in]     c A 64-bit unsigned integer to compare with @e a.
 * 
 * @note If the function returns @c false, the value at @e b is overwritten
 *       with the value at @e a.
 * @note Unlike the strong version of this function, this isn't required to
 *       return @c true when @e c equals the value at @e a. On certain machines,
 *       this can result in better performance when looping.
 * 
 * @sa atomic_compare_exchange_strong_uint64
 * 
 * @returns @c true if the @e c value stored in @e a match; @c false otherwise.
 */
/**
 * @fn int8_t atomic_exchange_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically swaps two signed 8-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_exchange_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically swaps two unsigned 8-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_exchange_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically swaps two signed 16-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_exchange_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically swaps two unsigned 16-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_exchange_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically swaps two signed 32-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_exchange_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically swaps two unsigned 32-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_exchange_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically swaps two signed 64-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_exchange_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically swaps two unsigned 64-bit values.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to swap with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_fetch_add_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically adds a signed 8-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_fetch_add_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically adds an unsigned 8-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_fetch_add_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically adds a signed 16-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_fetch_add_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically adds an unsigned 16-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_fetch_add_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically adds a signed 32-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_fetch_add_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically adds an unsigned 32-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_fetch_add_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically adds a signed 64-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_fetch_add_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically adds an unsigned 64-bit value to another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to add to @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_fetch_sub_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically subtracts a signed 8-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_fetch_sub_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically subtracts an unsigned 8-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_fetch_sub_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically subtracts a signed 16-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_fetch_sub_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically subtracts an unsigned 16-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_fetch_sub_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically subtracts a signed 32-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_fetch_sub_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically subtracts an unsigned 32-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_fetch_sub_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically subtracts a signed 64-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_fetch_sub_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically subtracts an unsigned 64-bit value from another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to subtract from @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_fetch_and_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically bitwise-ands a signed 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_fetch_and_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically bitwise-ands an unsigned 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_fetch_and_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically bitwise-ands a signed 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_fetch_and_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically bitwise-ands an unsigned 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_fetch_and_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically bitwise-ands a signed 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_fetch_and_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically bitwise-ands an unsigned 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_fetch_and_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically bitwise-ands a signed 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_fetch_and_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically bitwise-ands an unsigned 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to and with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_fetch_or_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically bitwise-ors a signed 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_fetch_or_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically bitwise-ors an unsigned 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_fetch_or_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically bitwise-ors a signed 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_fetch_or_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically bitwise-ors an unsigned 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_fetch_or_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically bitwise-ors a signed 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_fetch_or_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically bitwise-ors an unsigned 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_fetch_or_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically bitwise-ors a signed 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_fetch_or_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically bitwise-ors an unsigned 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to or with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_fetch_xor_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically exclusive-ors a signed 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint8_t atomic_fetch_xor_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically exclusive-ors an unsigned 8-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int16_t atomic_fetch_xor_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically exclusive-ors a signed 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint16_t atomic_fetch_xor_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically exclusive-ors an unsigned 16-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int32_t atomic_fetch_xor_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically exclusive-ors a signed 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint32_t atomic_fetch_xor_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically exclusive-ors an unsigned 32-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int64_t atomic_fetch_xor_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically exclusive-ors a signed 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn uint64_t atomic_fetch_xor_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically exclusive-ors an unsigned 64-bit value with another.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to xor with @e a.
 * 
 * @returns The previous value stored in @e a.
 */
/**
 * @fn int8_t atomic_load_int8(const volatile atomic_int8* a)
 * @brief Atomically reads a signed 8-bit value.
 * 
 * @param[in] a Pointer to an atomic 8-bit signed integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn uint8_t atomic_load_uint8(const volatile atomic_uint8* a)
 * @brief Atomically reads an unsigned 8-bit value.
 * 
 * @param[in] a Pointer to an atomic 8-bit unsigned integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn int16_t atomic_load_int16(const volatile atomic_int16* a)
 * @brief Atomically reads a signed 16-bit value.
 * 
 * @param[in] a Pointer to an atomic 16-bit signed integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn uint16_t atomic_load_uint16(const volatile atomic_uint16* a)
 * @brief Atomically reads an unsigned 16-bit value.
 * 
 * @param[in] a Pointer to an atomic 16-bit unsigned integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn int32_t atomic_load_int32(const volatile atomic_int32* a)
 * @brief Atomically reads a signed 32-bit value.
 * 
 * @param[in] a Pointer to an atomic 32-bit signed integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn uint32_t atomic_load_uint32(const volatile atomic_uint32* a)
 * @brief Atomically reads an unsigned 32-bit value.
 * 
 * @param[in] a Pointer to an atomic 32-bit unsigned integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn int64_t atomic_load_int64(const volatile atomic_int64* a)
 * @brief Atomically reads a signed 64-bit value.
 * 
 * @param[in] a Pointer to an atomic 64-bit signed integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn uint64_t atomic_load_uint65(const volatile atomic_uint64* a)
 * @brief Atomically reads an unsigned 64-bit value.
 * 
 * @param[in] a Pointer to an atomic 64-bit unsigned integer.
 * 
 * @returns The value stored in @e a.
 */
/**
 * @fn void atomic_store_int8(volatile atomic_int8* a, int8_t b)
 * @brief Atomically writes a signed 8-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit signed integer.
 * @param[in]     b An 8-bit signed integer to write into @e a.
 */
/**
 * @fn void atomic_store_uint8(volatile atomic_uint8* a, uint8_t b)
 * @brief Atomically writes an unsigned 8-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 8-bit unsigned integer.
 * @param[in]     b An 8-bit unsigned integer to write into @e a.
 */
/**
 * @fn void atomic_store_int16(volatile atomic_int16* a, int16_t b)
 * @brief Atomically writes a signed 16-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit signed integer.
 * @param[in]     b A 16-bit signed integer to write into @e a.
 */
/**
 * @fn void atomic_store_uint16(volatile atomic_uint16* a, uint16_t b)
 * @brief Atomically writes an unsigned 16-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 16-bit unsigned integer.
 * @param[in]     b A 16-bit unsigned integer to write into @e a.
 */
/**
 * @fn void atomic_store_int32(volatile atomic_int32* a, int32_t b)
 * @brief Atomically writes a signed 32-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit signed integer.
 * @param[in]     b A 32-bit signed integer to write into @e a.
 */
/**
 * @fn void atomic_store_uint32(volatile atomic_uint32* a, uint32_t b)
 * @brief Atomically writes an unsigned 32-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 32-bit unsigned integer.
 * @param[in]     b A 32-bit unsigned integer to write into @e a.
 */
/**
 * @fn void atomic_store_int64(volatile atomic_int64* a, int64_t b)
 * @brief Atomically writes a signed 64-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit signed integer.
 * @param[in]     b A 64-bit signed integer to write into @e a.
 */
/**
 * @fn void atomic_store_uint64(volatile atomic_uint64* a, uint64_t b)
 * @brief Atomically writes an unsigned 64-bit value.
 * 
 * @param[in,out] a Pointer to an atomic 64-bit unsigned integer.
 * @param[in]     b A 64-bit unsigned integer to write into @e a.
 */
#ifdef _INT64_DEFINED
#   define __MACRODEFS_ENUMERATE_ATOMICS(macro) \
        macro(int8) macro(uint8) \
        macro(int16) macro(uint16) \
        macro(int32) macro(uint32) \
        macro(int64) macro(uint64)
#else /* don't define 64-bit operations if unsupported */
#   define __MACRODEFS_ENUMERATE_ATOMICS(macro) \
        macro(int8) macro(uint8) \
        macro(int16) macro(uint16) \
        macro(int32) macro(uint32)
#endif
#if CPP_PREREQ(201103L) /* C++11 atomics */
#   ifdef __serenity__ /* serenity atomics */
#       include <AK/Atomic.h>
#       define __GENERATE_ATOMIC_TYPE(x) typedef Atomic<x ##_t> atomic_ ##x;
            __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_TYPE)
#       undef __GENERATE_ATOMIC_TYPE
#   else /* libc++ atomics */
#       include <atomic>
#       define __GENERATE_ATOMIC_TYPE(x) \
            typedef std::atomic<x ##_t> atomic_ ##x;
            __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_TYPE)
#       undef __GENERATE_ATOMIC_TYPE
#   endif
#elif !defined(__STDC_NO_ATOMICS__) /* C11 atomics */
#   include <stdatomic.h>
#   define __GENERATE_ATOMIC_TYPE(x) typedef _Atomic x ##_t atomic_ ##x;
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_TYPE)
#   undef __GENERATE_ATOMIC_TYPE
#else
#   define __GENERATE_ATOMIC_TYPE(x) typedef struct { x ##_t val; } atomic_ ##x;
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_TYPE)
#   undef __GENERATE_ATOMIC_TYPE
#   define _NO_STANDARD_ATOMICS 1
#endif
#ifdef _NO_STANDARD_ATOMICS /* compiler/platform-specific implementations */
#   undef _NO_STANDARD_ATOMICS
#   if GCC_PREREQ(40700) || (__has_builtin(__atomic_load_n) && \
        __has_builtin(__atomic_store_n) && __has_builtin(__atomic_load_n) && \
        __has_builtin(__atomic_compare_exchange_n) && \
        __has_builtin(__atomic_fetch_add) && \
        __has_builtin(__atomic_fetch_sub) && \
        __has_builtin(__atomic_fetch_and) && \
        __has_builtin(__atomic_fetch_or) && \
        __has_builtin(__atomic_fetch_xor)) /* GCC 4.7+ __atomic builtins */
#       define __GENERATE_ATOMIC_FUNC(x, y) \
            static_inline x ##_t y ##_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return __ ##y(&a->val, b, __ATOMIC_SEQ_CST); \
            }
#       define __GENERATE_ATOMIC_FUNCS(x) \
            static_inline x ##_t atomic_load_ ##x ( \
                const volatile atomic_ ##x* a \
            ) { \
                return __atomic_load_n(&a->val, __ATOMIC_SEQ_CST); \
            } \
            static_inline void atomic_store_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                __atomic_store_n(&a->val, b, __ATOMIC_SEQ_CST); \
            } \
            static_inline x ##_t atomic_exchange_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return __atomic_exchange_n(&a->val, b, __ATOMIC_SEQ_CST); \
            } \
            static_inline bool atomic_compare_exchange_strong_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                return __atomic_compare_exchange_n( \
                    &a->val, b, c, false, \
                    __ATOMIC_SEQ_CST, \
                    __ATOMIC_SEQ_CST \
                ); \
            } \
            static_inline bool atomic_compare_exchange_weak_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                return __atomic_compare_exchange_n( \
                    &a->val, b, c, true, \
                    __ATOMIC_SEQ_CST, \
                    __ATOMIC_SEQ_CST \
                ); \
            } \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_add) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_sub) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_and) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_or) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_xor)
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#       ifdef __cplusplus
#           define volatile
            __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#           undef volatile
#       endif
#       undef __GENERATE_ATOMIC_FUNCS
#       undef __GENERATE_ATOMIC_FUNC
#   elif GCC_PREREQ(1) /* GCC legacy __sync builtins */
#       define __GENERATE_ATOMIC_FUNC(x, y) \
            static_inline x ##_t atomic_fetch_ ##y ##_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return __sync_fetch_and_ ##y(&a->val, b); \
            }
#       define __GENERATE_ATOMIC_FUNCS(x) \
            static_inline x ##_t atomic_load_ ##x ( \
                const volatile atomic_ ##x* a \
            ) { \
                return __sync_fetch_and_add(&a->val, 0); \
            } \
            static_inline void atomic_store_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                __sync_lock_test_and_set(&a->val, b); \
                __sync_lock_release(&a->val); \
            } \ \
            static_inline x ##_t atomic_exchange_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                x ##_t result = __sync_lock_test_and_set(&a->val, b); \
                __sync_lock_release(&a->val); \
                return result; \
            } \
            static_inline bool atomic_compare_exchange_strong_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                x ##_t result = __sync_val_compare_and_swap(&a->val, *b, c); \
                if (result != c) \
                    *b = result; \
                return result != c; \
            } \
            static_inline bool atomic_compare_exchange_weak_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                return atomic_compare_exchange_strong_ ##x(a, b, c); \
            } \
            __GENERATE_ATOMIC_FUNC(x, add) \
            __GENERATE_ATOMIC_FUNC(x, sub) \
            __GENERATE_ATOMIC_FUNC(x, and) \
            __GENERATE_ATOMIC_FUNC(x, or) \
            __GENERATE_ATOMIC_FUNC(x, xor)
#       pragma GCC diagnostic push
#       pragma GCC diagnostic ignored "-Wcast-qual"
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#       ifdef __cplusplus
#           define volatile
            __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#           undef volatile
#       endif
#       pragma GCC diagnostic pop
#       undef __GENERATE_ATOMIC_FUNCS
#       undef __GENERATE_ATOMIC_FUNC
#   elif MSVC_PREREQ(1500) /* MSVC 2008+ atomic intrinsics */
#       include <intrin.h>
#       define __MSVC_ATOMIC_SUFFIX_int8    8
#       define __MSVC_ATOMIC_SUFFIX_uint8   8
#       define __MSVC_ATOMIC_SUFFIX_int16  16
#       define __MSVC_ATOMIC_SUFFIX_uint16 16
#       define __MSVC_ATOMIC_SUFFIX_int32
#       define __MSVC_ATOMIC_SUFFIX_uint32
#       define __MSVC_ATOMIC_SUFFIX_int64  64
#       define __MSVC_ATOMIC_SUFFIX_uint64 64
#       define __MSVC_ATOMIC_TYPE_int8   char
#       define __MSVC_ATOMIC_TYPE_uint8  char
#       define __MSVC_ATOMIC_TYPE_int16  short
#       define __MSVC_ATOMIC_TYPE_uint16 short
#       define __MSVC_ATOMIC_TYPE_int32  int
#       define __MSVC_ATOMIC_TYPE_uint32 int
#       define __MSVC_ATOMIC_TYPE_int64  __int64
#       define __MSVC_ATOMIC_TYPE_uint64 __int64
#       define __GENERATE_ATOMIC_FUNCS(x) \
            static_inline x ##_t atomic_load_ ##x ( \
                const volatile atomic_ ##x* a \
            ) { \
                return (x ##_t)CONCATENATE(_InterlockedCompareExchange, \
                    __MSVC_ATOMIC_SUFFIX_ ##x \
                )((volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, 0, 0); \
            } \
            static_inline void atomic_store_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                CONCATENATE(_InterlockedExchange, __MSVC_ATOMIC_SUFFIX_ ##x)( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline x ##_t atomic_exchange_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return CONCATENATE( \
                    _InterlockedExchange, __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline bool atomic_compare_exchange_strong_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                x ##_t result = CONCATENATE(_InterlockedCompareExchange, \
                    __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)*b, \
                    (__MSVC_ATOMIC_TYPE_ ##x)c \
                ); \
                if (result != c) \
                    *b = result; \
                return result != c; \
            } \
            static_inline bool atomic_compare_exchange_weak_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t* b, \
                x ##_t c \
            ) { \
                return atomic_compare_exchange_strong_ ##x(a, b, c); \
            } \
            static_inline x ##_t atomic_fetch_add_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return CONCATENATE( \
                    _InterlockedExchangeAdd, __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline x ##_t atomic_fetch_sub_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return atomic_fetch_add( \
                    a, \
                    (x ##_t)-(__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline x ##_t atomic_fetch_and_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return CONCATENATE( \
                    _InterlockedAnd, __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline x ##_t atomic_fetch_or_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return CONCATENATE( \
                    _InterlockedOr, __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            } \
            static_inline x ##_t atomic_fetch_xor_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                return CONCATENATE( \
                    _InterlockedXor, __MSVC_ATOMIC_SUFFIX_ ##x \
                )( \
                    (volatile __MSVC_ATOMIC_TYPE_ ##x*)&a->val, \
                    (__MSVC_ATOMIC_TYPE_ ##x)b \
                ); \
            }
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#       ifdef __cplusplus
#           define volatile
            __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#           undef volatile
#       endif
#       undef __MSVC_ATOMIC_SUFFIX_int8
#       undef __MSVC_ATOMIC_SUFFIX_uint8
#       undef __MSVC_ATOMIC_SUFFIX_int16
#       undef __MSVC_ATOMIC_SUFFIX_uint16
#       undef __MSVC_ATOMIC_SUFFIX_int32
#       undef __MSVC_ATOMIC_SUFFIX_uint32
#       undef __MSVC_ATOMIC_SUFFIX_int64
#       undef __MSVC_ATOMIC_SUFFIX_uint64
#       undef __MSVC_ATOMIC_TYPE_int8
#       undef __MSVC_ATOMIC_TYPE_uint8
#       undef __MSVC_ATOMIC_TYPE_int16
#       undef __MSVC_ATOMIC_TYPE_uint16
#       undef __MSVC_ATOMIC_TYPE_int32
#       undef __MSVC_ATOMIC_TYPE_uint32
#       undef __MSVC_ATOMIC_TYPE_int64
#       undef __MSVC_ATOMIC_TYPE_uint64
#   elif defined(__WATCOMC__) && defined(__i386__) /* Watcom x86 assembly */
        /* TODO: finish Watcom x86 auxilaries */
#       define __GENERATE_ATOMIC_FUNCDEFS(x) \
            extern _inline x ##_t atomic_exchange_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ); \
            extern _inline x ##_t atomic_load_ ##x ( \
                const volatile atomic_ ##x* a  \
            );
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCDEFS)
#       pragma aux atomic_exchange_int8 = \
            "lock xchg [ecx], al" \
            parm [ecx] [al] \
            value [al] \
            modify exact [al];
#       pragma aux atomic_exchange_uint8 = \
            "lock xchg [ecx], al" \
            parm [ecx] [al] \
            value [al] \
            modify exact [al];
#       pragma aux atomic_exchange_int16 = \
            "lock xchg [ecx], ax" \
            parm [ecx] [ax] \
            value [ax] \
            modify exact [ax];
#       pragma aux atomic_exchange_uint16 = \
            "lock xchg [ecx], ax" \
            parm [ecx] [ax] \
            value [ax] \
            modify exact [ax];
#       pragma aux atomic_exchange_int32 = \
            "lock xchg [ecx], eax" \
            parm [ecx] [eax] \
            value [eax] \
            modify exact [eax];
#       pragma aux atomic_exchange_uint32 = \
            "lock xchg [ecx], eax" \
            parm [ecx] [eax] \
            value [eax] \
            modify exact [eax];
#       pragma aux atomic_load_int8 = \
            "mfence" \
            "mov [ecx], al" \
            parm [ecx] \
            value [al] \
            modify exact [al];
#       pragma aux atomic_load_uint8 = \
            "mfence" \
            "mov [ecx], al" \
            parm [ecx] \
            value [al] \
            modify exact [al];
#       pragma aux atomic_load_int16 = \
            "mfence" \
            "mov [ecx], ax" \
            parm [ecx] \
            value [ax] \
            modify exact [ax];
#       pragma aux atomic_load_uint16 = \
            "mfence" \
            "mov [ecx], ax" \
            parm [ecx] \
            value [ax] \
            modify exact [ax];
#       pragma aux atomic_load_int32 = \
            "mfence" \
            "mov [ecx], eax" \
            parm [ecx] \
            value [eax] \
            modify exact [eax];
#       pragma aux atomic_load_uint32 = \
            "mfence" \
            "mov [ecx], eax" \
            parm [ecx] \
            value [eax] \
            modify exact [eax];
#       ifdef _INT64_DEFINED /* TODO: 64-bit Watcom auxilaries */
#           pragma aux atomic_exchange_int64 = \
                "lock xchg [ecx], rax" \
                parm [ecx] [rax] \
                value [rax] \
                modify exact [rax];
#           pragma aux atomic_exchange_uint64 = \
                "lock xchg [ecx], rax" \
                parm [ecx] [rax] \
                value [rax] \
                modify exact [rax];
#           pragma aux atomic_load_int64 = \
                "mfence" \
                "mov [ecx], rax" \
                parm [ecx] \
                value [eax] \
                modify exact [rax];
#           pragma aux atomic_load_uint64 = \
                "mfence" \
                "mov [ecx], rax" \
                parm [ecx] \
                value [rax] \
                modify exact [rax];
#       endif
#       define __GENERATE_ATOMIC_FUNCS(x) \
            static_inline void atomic_store_ ##x ( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) { \
                (void)atomic_exchange_ ##x(a, b); \
            }

#       undef __GENERATE_ATOMIC_FUNCS
#       undef __GENERATE_ATOMIC_FUNCDEFS
#   else
#       define _NO_ATOMICS 1
#   endif
#   if !defined(_NO_ATOMICS) && STDC_PREREQ(201112L)
#       if UINTPTR_MAX == UINT64_MAX
#           define __ATOMIC_PTR(t, x, y) y ##_uint64 x
#       else
#           define __ATOMIC_PTR(t, x, y) y ##_uint32 y
#       endif
#       define __GENERATE_ATOMIC_GENERIC(t, x, y) (_Generic((x), \
            atomic_int8*:   t   ##_int8 y, \
            atomic_uint8*:  t  ##_uint8 y, \
            atomic_int16*:  t  ##_int16 y, \
            atomic_uint16*: t ##_uint16 y, \
            atomic_int32*:  t  ##_int32 y, \
            atomic_uint32*: t ##_uint32 y, \
            atomic_int64*:  t  ##_int64 y, \
            atomic_uint64*: t ##_uint64 y, \
        ))
#       define atomic_load(a) \
            __GENERATE_ATOMIC_GENERIC(atomic_load, a, (a))
#       define atomic_store(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_store, a, ((a), (b)))
#       define atomic_compare_exchange_strong(a, b, c) \
            __GENERATE_ATOMIC_GENERIC( \
                atomic_compare_exchange_strong, \
                a, \
                ((a), (b), (c)) \
            )
#       define atomic_compare_exchange_weak(a, b, c) \
            __GENERATE_ATOMIC_GENERIC( \
                atomic_compare_exchange_weak, \
                a, \
                ((a), (b), (c)) \
            )
#       define atomic_exchange(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_exchange, a, ((a), (b)))
#       define atomic_fetch_add(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_fetch_add, a, ((a), (b)))
#       define atomic_fetch_sub(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_fetch_sub, a, ((a), (b)))
#       define atomic_fetch_and(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_fetch_and, a, ((a), (b)))
#       define atomic_fetch_or(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_fetch_or, a, ((a), (b)))
#       define atomic_fetch_xor(a, b) \
            __GENERATE_ATOMIC_GENERIC(atomic_fetch_xor, a, ((a), (b)))
#   elif !defined(_NO_ATOMICS) && CPP_PREREQ(1L)
#       if !CPP_PREREQ(201103L)
#           define noexcept
#       endif
    #   define __GENERATE_ATOMIC_FUNC(x, y) \
            static_inline x ##_t y( \
                volatile atomic_ ##x* a, \
                x ##_t b \
            ) noexcept { \
                return y(a, b); \
            } \
            static_inline x ##_t y( \
                atomic_ ##x* a, \
                x ##_t b \
            ) noexcept { \
                return y(a, b); \
            }
#       define __GENERATE_ATOMIC_FUNCS(x) \
            static_inline T atomic_load( \
                const volatile atomic_ ##x* a \
            ) noexcept { \
                return atomic_load_ ##x(a); \
            } \
            static_inline T atomic_load( \
                const atomic_ ##x* a \
            ) noexcept { \
                return atomic_load_ ##x(a); \
            } \
            static_inline void atomic_store( \
                volatile atomic_ ##x* a, \
                T b \
            ) noexcept { \
                atomic_store_ ##x(a, b); \
            } \
            static_inline void atomic_store( \
                atomic_ ##x* a, \
                T b \
            ) noexcept { \
                atomic_store_ ##x(a, b); \
            } \
            static_inline T atomic_compare_exchange_strong( \
                volatile atomic_ ##x* a, \
                T* b, \
                T c \
            ) noexcept { \
                return atomic_compare_exchange_strong_ ##x(a, b, c); \
            } \
            static_inline T atomic_compare_exchange_strong( \
                atomic_ ##x* a, \
                T* b, \
                T c \
            ) noexcept { \
                return atomic_compare_exchange_strong_ ##x(a, b, c); \
            } \
            static_inline T atomic_compare_exchange_weak( \
                volatile atomic_ ##x* a, \
                T* b, \
                T c \
            ) noexcept { \
                return atomic_compare_exchange_weak_ ##x(a, b, c); \
            } \
            static_inline T atomic_compare_exchange_weak( \
                atomic_ ##x* a, \
                T* b, \
                T c \
            ) noexcept { \
                return atomic_compare_exchange_weak_ ##x(a, b, c); \
            } \
            __GENERATE_ATOMIC_FUNC(x, atomic_exchange) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_add) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_sub) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_and) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_or) \
            __GENERATE_ATOMIC_FUNC(x, atomic_fetch_xor)
        __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#       if !CPP_PREREQ(201103L)
#           undef noexcept
#       endif
#       undef __GENERATE_ATOMIC_FUNCS
#       undef __GENERATE_ATOMIC_FUNC
#   endif
#else /* standard-compliant atomic implementations */
#   define __GENERATE_OTHER_ATOMIC_FUNCS(x) \
        static_inline x ##_t atomic_load_ ##x ( \
            const volatile atomic_ ##x* a \
        ) { \
            return atomic_load(a); \
        } \
        static_inline void atomic_store_ ##x ( \
            volatile atomic_ ##x* a, \
            x ##_t b \
        ) { \
            atomic_store(a, b); \
        } \
        static_inline bool atomic_compare_exchange_strong_ ##x ( \
            volatile atomic_ ##x* a, \
            x ##_t* b, \
            x ##_t c \
        ) { \
            return atomic_compare_exchange_strong(a, b, c); \
        } \
        static_inline bool atomic_compare_exchange_weak_ ##x ( \
            volatile atomic_ ##x* a, \
            x ##_t* b, \
            x ##_t c \
        ) { \
            return atomic_compare_exchange_weak(a, b, c); \
        }
#   define __GENERATE_ATOMIC_FUNC(x, y) \
        static_inline x ##_t y ##_ ##x (volatile atomic_ ##x* a, x ##_t b) { \
            return y(a, b); \
        }
#   define __GENERATE_ATOMIC_FUNCS(x) \
        __GENERATE_ATOMIC_FUNC(x, atomic_exchange) \
        __GENERATE_ATOMIC_FUNC(x, atomic_fetch_add) \
        __GENERATE_ATOMIC_FUNC(x, atomic_fetch_sub) \
        __GENERATE_ATOMIC_FUNC(x, atomic_fetch_and) \
        __GENERATE_ATOMIC_FUNC(x, atomic_fetch_or) \
        __GENERATE_ATOMIC_FUNC(x, atomic_fetch_xor) \
        __GENERATE_OTHER_ATOMIC_FUNCS(x)
    __MACRODEFS_ENUMERATE_ATOMICS(__GENERATE_ATOMIC_FUNCS)
#   undef __GENERATE_ATOMIC_FUNCS
#   undef __GENERATE_OTHER_ATOMIC_FUNCS
#   undef __GENERATE_ATOMIC_FUNC
#endif
#undef __MACRODEFS_ENUMERATE_ATOMICS

#endif /* ATOMICS_H_ */
