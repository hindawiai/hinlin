<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acmacros.h - C macros क्रम the entire subप्रणाली.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACMACROS_H__
#घोषणा __ACMACROS_H__

/*
 * Extract data using a poपूर्णांकer. Any more than a byte and we
 * get पूर्णांकo potential alignment issues -- see the STORE macros below.
 * Use with care.
 */
#घोषणा ACPI_CAST8(ptr)                 ACPI_CAST_PTR (u8, (ptr))
#घोषणा ACPI_CAST16(ptr)                ACPI_CAST_PTR (u16, (ptr))
#घोषणा ACPI_CAST32(ptr)                ACPI_CAST_PTR (u32, (ptr))
#घोषणा ACPI_CAST64(ptr)                ACPI_CAST_PTR (u64, (ptr))
#घोषणा ACPI_GET8(ptr)                  (*ACPI_CAST8 (ptr))
#घोषणा ACPI_GET16(ptr)                 (*ACPI_CAST16 (ptr))
#घोषणा ACPI_GET32(ptr)                 (*ACPI_CAST32 (ptr))
#घोषणा ACPI_GET64(ptr)                 (*ACPI_CAST64 (ptr))
#घोषणा ACPI_SET8(ptr, val)             (*ACPI_CAST8 (ptr) = (u8) (val))
#घोषणा ACPI_SET16(ptr, val)            (*ACPI_CAST16 (ptr) = (u16) (val))
#घोषणा ACPI_SET32(ptr, val)            (*ACPI_CAST32 (ptr) = (u32) (val))
#घोषणा ACPI_SET64(ptr, val)            (*ACPI_CAST64 (ptr) = (u64) (val))

/*
 * म_लिखो() क्रमmat helper. This macro is a workaround क्रम the dअगरficulties
 * with emitting 64-bit पूर्णांकegers and 64-bit poपूर्णांकers with the same code
 * क्रम both 32-bit and 64-bit hosts.
 */
#घोषणा ACPI_FORMAT_UINT64(i)           ACPI_HIDWORD(i), ACPI_LODWORD(i)

/*
 * Macros क्रम moving data around to/from buffers that are possibly unaligned.
 * If the hardware supports the transfer of unaligned data, just करो the store.
 * Otherwise, we have to move one byte at a समय.
 */
#अगर_घोषित ACPI_BIG_ENDIAN
/*
 * Macros क्रम big-endian machines
 */

/* These macros reverse the bytes during the move, converting little-endian to big endian */

	 /* Big Endian      <==        Little Endian */
	 /*  Hi...Lo                     Lo...Hi     */
/* 16-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_16_TO_16(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[1];\
			  ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[0];पूर्ण

#घोषणा ACPI_MOVE_16_TO_32(d, s)        अणु(*(u32 *)(व्योम *)(d))=0;\
					  ((u8 *)(व्योम *)(d))[2] = ((u8 *)(व्योम *)(s))[1];\
					  ((u8 *)(व्योम *)(d))[3] = ((u8 *)(व्योम *)(s))[0];पूर्ण

#घोषणा ACPI_MOVE_16_TO_64(d, s)        अणु(*(u64 *)(व्योम *)(d))=0;\
							   ((u8 *)(व्योम *)(d))[6] = ((u8 *)(व्योम *)(s))[1];\
							   ((u8 *)(व्योम *)(d))[7] = ((u8 *)(व्योम *)(s))[0];पूर्ण

/* 32-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */

#घोषणा ACPI_MOVE_32_TO_32(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[3];\
									  ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[2];\
									  ((  u8 *)(व्योम *)(d))[2] = ((u8 *)(व्योम *)(s))[1];\
									  ((  u8 *)(व्योम *)(d))[3] = ((u8 *)(व्योम *)(s))[0];पूर्ण

#घोषणा ACPI_MOVE_32_TO_64(d, s)        अणु(*(u64 *)(व्योम *)(d))=0;\
										   ((u8 *)(व्योम *)(d))[4] = ((u8 *)(व्योम *)(s))[3];\
										   ((u8 *)(व्योम *)(d))[5] = ((u8 *)(व्योम *)(s))[2];\
										   ((u8 *)(व्योम *)(d))[6] = ((u8 *)(व्योम *)(s))[1];\
										   ((u8 *)(व्योम *)(d))[7] = ((u8 *)(व्योम *)(s))[0];पूर्ण

/* 64-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */

#घोषणा ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Truncate to 32 */

#घोषणा ACPI_MOVE_64_TO_64(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[7];\
										 ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[6];\
										 ((  u8 *)(व्योम *)(d))[2] = ((u8 *)(व्योम *)(s))[5];\
										 ((  u8 *)(व्योम *)(d))[3] = ((u8 *)(व्योम *)(s))[4];\
										 ((  u8 *)(व्योम *)(d))[4] = ((u8 *)(व्योम *)(s))[3];\
										 ((  u8 *)(व्योम *)(d))[5] = ((u8 *)(व्योम *)(s))[2];\
										 ((  u8 *)(व्योम *)(d))[6] = ((u8 *)(व्योम *)(s))[1];\
										 ((  u8 *)(व्योम *)(d))[7] = ((u8 *)(व्योम *)(s))[0];पूर्ण
#अन्यथा
/*
 * Macros क्रम little-endian machines
 */

#अगर_अघोषित ACPI_MISALIGNMENT_NOT_SUPPORTED

/* The hardware supports unaligned transfers, just करो the little-endian move */

/* 16-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_16_TO_16(d, s)        *(u16 *)(व्योम *)(d) = *(u16 *)(व्योम *)(s)
#घोषणा ACPI_MOVE_16_TO_32(d, s)        *(u32 *)(व्योम *)(d) = *(u16 *)(व्योम *)(s)
#घोषणा ACPI_MOVE_16_TO_64(d, s)        *(u64 *)(व्योम *)(d) = *(u16 *)(व्योम *)(s)

/* 32-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */
#घोषणा ACPI_MOVE_32_TO_32(d, s)        *(u32 *)(व्योम *)(d) = *(u32 *)(व्योम *)(s)
#घोषणा ACPI_MOVE_32_TO_64(d, s)        *(u64 *)(व्योम *)(d) = *(u32 *)(व्योम *)(s)

/* 64-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */
#घोषणा ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Truncate to 32 */
#घोषणा ACPI_MOVE_64_TO_64(d, s)        *(u64 *)(व्योम *)(d) = *(u64 *)(व्योम *)(s)

#अन्यथा
/*
 * The hardware करोes not support unaligned transfers. We must move the
 * data one byte at a समय. These macros work whether the source or
 * the destination (or both) is/are unaligned. (Little-endian move)
 */

/* 16-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_16_TO_16(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[0];\
										 ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[1];पूर्ण

#घोषणा ACPI_MOVE_16_TO_32(d, s)        अणु(*(u32 *)(व्योम *)(d)) = 0; ACPI_MOVE_16_TO_16(d, s);पूर्ण
#घोषणा ACPI_MOVE_16_TO_64(d, s)        अणु(*(u64 *)(व्योम *)(d)) = 0; ACPI_MOVE_16_TO_16(d, s);पूर्ण

/* 32-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_32_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */

#घोषणा ACPI_MOVE_32_TO_32(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[0];\
										 ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[1];\
										 ((  u8 *)(व्योम *)(d))[2] = ((u8 *)(व्योम *)(s))[2];\
										 ((  u8 *)(व्योम *)(d))[3] = ((u8 *)(व्योम *)(s))[3];पूर्ण

#घोषणा ACPI_MOVE_32_TO_64(d, s)        अणु(*(u64 *)(व्योम *)(d)) = 0; ACPI_MOVE_32_TO_32(d, s);पूर्ण

/* 64-bit source, 16/32/64 destination */

#घोषणा ACPI_MOVE_64_TO_16(d, s)        ACPI_MOVE_16_TO_16(d, s)	/* Truncate to 16 */
#घोषणा ACPI_MOVE_64_TO_32(d, s)        ACPI_MOVE_32_TO_32(d, s)	/* Truncate to 32 */
#घोषणा ACPI_MOVE_64_TO_64(d, s)        अणु((  u8 *)(व्योम *)(d))[0] = ((u8 *)(व्योम *)(s))[0];\
										 ((  u8 *)(व्योम *)(d))[1] = ((u8 *)(व्योम *)(s))[1];\
										 ((  u8 *)(व्योम *)(d))[2] = ((u8 *)(व्योम *)(s))[2];\
										 ((  u8 *)(व्योम *)(d))[3] = ((u8 *)(व्योम *)(s))[3];\
										 ((  u8 *)(व्योम *)(d))[4] = ((u8 *)(व्योम *)(s))[4];\
										 ((  u8 *)(व्योम *)(d))[5] = ((u8 *)(व्योम *)(s))[5];\
										 ((  u8 *)(व्योम *)(d))[6] = ((u8 *)(व्योम *)(s))[6];\
										 ((  u8 *)(व्योम *)(d))[7] = ((u8 *)(व्योम *)(s))[7];पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Fast घातer-of-two math macros क्रम non-optimized compilers
 */
#घोषणा _ACPI_DIV(value, घातer_of2)     ((u32) ((value) >> (घातer_of2)))
#घोषणा _ACPI_MUL(value, घातer_of2)     ((u32) ((value) << (घातer_of2)))
#घोषणा _ACPI_MOD(value, भागisor)       ((u32) ((value) & ((भागisor) -1)))

#घोषणा ACPI_DIV_2(a)                   _ACPI_DIV(a, 1)
#घोषणा ACPI_MUL_2(a)                   _ACPI_MUL(a, 1)
#घोषणा ACPI_MOD_2(a)                   _ACPI_MOD(a, 2)

#घोषणा ACPI_DIV_4(a)                   _ACPI_DIV(a, 2)
#घोषणा ACPI_MUL_4(a)                   _ACPI_MUL(a, 2)
#घोषणा ACPI_MOD_4(a)                   _ACPI_MOD(a, 4)

#घोषणा ACPI_DIV_8(a)                   _ACPI_DIV(a, 3)
#घोषणा ACPI_MUL_8(a)                   _ACPI_MUL(a, 3)
#घोषणा ACPI_MOD_8(a)                   _ACPI_MOD(a, 8)

#घोषणा ACPI_DIV_16(a)                  _ACPI_DIV(a, 4)
#घोषणा ACPI_MUL_16(a)                  _ACPI_MUL(a, 4)
#घोषणा ACPI_MOD_16(a)                  _ACPI_MOD(a, 16)

#घोषणा ACPI_DIV_32(a)                  _ACPI_DIV(a, 5)
#घोषणा ACPI_MUL_32(a)                  _ACPI_MUL(a, 5)
#घोषणा ACPI_MOD_32(a)                  _ACPI_MOD(a, 32)

/* Test क्रम ASCII अक्षरacter */

#घोषणा ACPI_IS_ASCII(c)                ((c) < 0x80)

/* Signed पूर्णांकegers */

#घोषणा ACPI_SIGN_POSITIVE              0
#घोषणा ACPI_SIGN_NEGATIVE              1

/*
 * Rounding macros (Power of two boundaries only)
 */
#घोषणा ACPI_ROUND_DOWN(value, boundary)    (((acpi_size)(value)) & \
												(~(((acpi_size) boundary)-1)))

#घोषणा ACPI_ROUND_UP(value, boundary)      ((((acpi_size)(value)) + \
												(((acpi_size) boundary)-1)) & \
												(~(((acpi_size) boundary)-1)))

/* Note: माप(acpi_size) evaluates to either 4 or 8 (32- vs 64-bit mode) */

#घोषणा ACPI_ROUND_DOWN_TO_32BIT(a)         ACPI_ROUND_DOWN(a, 4)
#घोषणा ACPI_ROUND_DOWN_TO_64BIT(a)         ACPI_ROUND_DOWN(a, 8)
#घोषणा ACPI_ROUND_DOWN_TO_NATIVE_WORD(a)   ACPI_ROUND_DOWN(a, माप(acpi_size))

#घोषणा ACPI_ROUND_UP_TO_32BIT(a)           ACPI_ROUND_UP(a, 4)
#घोषणा ACPI_ROUND_UP_TO_64BIT(a)           ACPI_ROUND_UP(a, 8)
#घोषणा ACPI_ROUND_UP_TO_NATIVE_WORD(a)     ACPI_ROUND_UP(a, माप(acpi_size))

#घोषणा ACPI_ROUND_BITS_UP_TO_BYTES(a)      ACPI_DIV_8((a) + 7)
#घोषणा ACPI_ROUND_BITS_DOWN_TO_BYTES(a)    ACPI_DIV_8((a))

#घोषणा ACPI_ROUND_UP_TO_1K(a)              (((a) + 1023) >> 10)

/* Generic (non-घातer-of-two) rounding */

#घोषणा ACPI_ROUND_UP_TO(value, boundary)   (((value) + ((boundary)-1)) / (boundary))

#घोषणा ACPI_IS_MISALIGNED(value)           (((acpi_size) value) & (माप(acpi_size)-1))

/* Generic bit manipulation */

#अगर_अघोषित ACPI_USE_NATIVE_BIT_FINDER

#घोषणा __ACPI_FIND_LAST_BIT_2(a, r)        ((((u8)  (a)) & 0x02) ? (r)+1 : (r))
#घोषणा __ACPI_FIND_LAST_BIT_4(a, r)        ((((u8)  (a)) & 0x0C) ? \
											 __ACPI_FIND_LAST_BIT_2  ((a)>>2,  (r)+2) : \
											 __ACPI_FIND_LAST_BIT_2  ((a), (r)))
#घोषणा __ACPI_FIND_LAST_BIT_8(a, r)        ((((u8)  (a)) & 0xF0) ? \
											 __ACPI_FIND_LAST_BIT_4  ((a)>>4,  (r)+4) : \
											 __ACPI_FIND_LAST_BIT_4  ((a), (r)))
#घोषणा __ACPI_FIND_LAST_BIT_16(a, r)       ((((u16) (a)) & 0xFF00) ? \
											 __ACPI_FIND_LAST_BIT_8  ((a)>>8,  (r)+8) : \
											 __ACPI_FIND_LAST_BIT_8  ((a), (r)))
#घोषणा __ACPI_FIND_LAST_BIT_32(a, r)       ((((u32) (a)) & 0xFFFF0000) ? \
											 __ACPI_FIND_LAST_BIT_16 ((a)>>16, (r)+16) : \
											 __ACPI_FIND_LAST_BIT_16 ((a), (r)))
#घोषणा __ACPI_FIND_LAST_BIT_64(a, r)       ((((u64) (a)) & 0xFFFFFFFF00000000) ? \
											 __ACPI_FIND_LAST_BIT_32 ((a)>>32, (r)+32) : \
											 __ACPI_FIND_LAST_BIT_32 ((a), (r)))

#घोषणा ACPI_FIND_LAST_BIT_8(a)             ((a) ? __ACPI_FIND_LAST_BIT_8 (a, 1) : 0)
#घोषणा ACPI_FIND_LAST_BIT_16(a)            ((a) ? __ACPI_FIND_LAST_BIT_16 (a, 1) : 0)
#घोषणा ACPI_FIND_LAST_BIT_32(a)            ((a) ? __ACPI_FIND_LAST_BIT_32 (a, 1) : 0)
#घोषणा ACPI_FIND_LAST_BIT_64(a)            ((a) ? __ACPI_FIND_LAST_BIT_64 (a, 1) : 0)

#घोषणा __ACPI_FIND_FIRST_BIT_2(a, r)       ((((u8) (a)) & 0x01) ? (r) : (r)+1)
#घोषणा __ACPI_FIND_FIRST_BIT_4(a, r)       ((((u8) (a)) & 0x03) ? \
											 __ACPI_FIND_FIRST_BIT_2  ((a), (r)) : \
											 __ACPI_FIND_FIRST_BIT_2  ((a)>>2, (r)+2))
#घोषणा __ACPI_FIND_FIRST_BIT_8(a, r)       ((((u8) (a)) & 0x0F) ? \
											 __ACPI_FIND_FIRST_BIT_4  ((a), (r)) : \
											 __ACPI_FIND_FIRST_BIT_4  ((a)>>4, (r)+4))
#घोषणा __ACPI_FIND_FIRST_BIT_16(a, r)      ((((u16) (a)) & 0x00FF) ? \
											 __ACPI_FIND_FIRST_BIT_8  ((a), (r)) : \
											 __ACPI_FIND_FIRST_BIT_8  ((a)>>8, (r)+8))
#घोषणा __ACPI_FIND_FIRST_BIT_32(a, r)      ((((u32) (a)) & 0x0000FFFF) ? \
											 __ACPI_FIND_FIRST_BIT_16 ((a), (r)) : \
											 __ACPI_FIND_FIRST_BIT_16 ((a)>>16, (r)+16))
#घोषणा __ACPI_FIND_FIRST_BIT_64(a, r)      ((((u64) (a)) & 0x00000000FFFFFFFF) ? \
											 __ACPI_FIND_FIRST_BIT_32 ((a), (r)) : \
											 __ACPI_FIND_FIRST_BIT_32 ((a)>>32, (r)+32))

#घोषणा ACPI_FIND_FIRST_BIT_8(a)            ((a) ? __ACPI_FIND_FIRST_BIT_8 (a, 1) : 0)
#घोषणा ACPI_FIND_FIRST_BIT_16(a)           ((a) ? __ACPI_FIND_FIRST_BIT_16 (a, 1) : 0)
#घोषणा ACPI_FIND_FIRST_BIT_32(a)           ((a) ? __ACPI_FIND_FIRST_BIT_32 (a, 1) : 0)
#घोषणा ACPI_FIND_FIRST_BIT_64(a)           ((a) ? __ACPI_FIND_FIRST_BIT_64 (a, 1) : 0)

#पूर्ण_अगर				/* ACPI_USE_NATIVE_BIT_FINDER */

/* Generic (घातer-of-two) rounding */

#घोषणा ACPI_ROUND_UP_POWER_OF_TWO_8(a)     ((u8) \
											(((u16) 1) <<  ACPI_FIND_LAST_BIT_8  ((a)  - 1)))
#घोषणा ACPI_ROUND_DOWN_POWER_OF_TWO_8(a)   ((u8) \
											(((u16) 1) << (ACPI_FIND_LAST_BIT_8  ((a)) - 1)))
#घोषणा ACPI_ROUND_UP_POWER_OF_TWO_16(a)    ((u16) \
											(((u32) 1) <<  ACPI_FIND_LAST_BIT_16 ((a)  - 1)))
#घोषणा ACPI_ROUND_DOWN_POWER_OF_TWO_16(a)  ((u16) \
											(((u32) 1) << (ACPI_FIND_LAST_BIT_16 ((a)) - 1)))
#घोषणा ACPI_ROUND_UP_POWER_OF_TWO_32(a)    ((u32) \
											(((u64) 1) <<  ACPI_FIND_LAST_BIT_32 ((a)  - 1)))
#घोषणा ACPI_ROUND_DOWN_POWER_OF_TWO_32(a)  ((u32) \
											(((u64) 1) << (ACPI_FIND_LAST_BIT_32 ((a)) - 1)))
#घोषणा ACPI_IS_ALIGNED(a, s)               (((a) & ((s) - 1)) == 0)
#घोषणा ACPI_IS_POWER_OF_TWO(a)             ACPI_IS_ALIGNED(a, a)

/*
 * Biपंचांगask creation
 * Bit positions start at zero.
 * MASK_BITS_ABOVE creates a mask starting AT the position and above
 * MASK_BITS_BELOW creates a mask starting one bit BELOW the position
 * MASK_BITS_ABOVE/BELOW accepts a bit offset to create a mask
 * MASK_BITS_ABOVE/BELOW_32/64 accepts a bit width to create a mask
 * Note: The ACPI_INTEGER_BIT_SIZE check is used to bypass compiler
 * dअगरferences with the shअगरt चालक
 */
#घोषणा ACPI_MASK_BITS_ABOVE(position)      (~((ACPI_UINT64_MAX) << ((u32) (position))))
#घोषणा ACPI_MASK_BITS_BELOW(position)      ((ACPI_UINT64_MAX) << ((u32) (position)))
#घोषणा ACPI_MASK_BITS_ABOVE_32(width)      ((u32) ACPI_MASK_BITS_ABOVE(width))
#घोषणा ACPI_MASK_BITS_BELOW_32(width)      ((u32) ACPI_MASK_BITS_BELOW(width))
#घोषणा ACPI_MASK_BITS_ABOVE_64(width)      ((width) == ACPI_INTEGER_BIT_SIZE ? \
												ACPI_UINT64_MAX : \
												ACPI_MASK_BITS_ABOVE(width))
#घोषणा ACPI_MASK_BITS_BELOW_64(width)      ((width) == ACPI_INTEGER_BIT_SIZE ? \
												(u64) 0 : \
												ACPI_MASK_BITS_BELOW(width))

/* Bitfields within ACPI रेजिस्टरs */

#घोषणा ACPI_REGISTER_PREPARE_BITS(val, pos, mask) \
	((val << pos) & mask)

#घोषणा ACPI_REGISTER_INSERT_VALUE(reg, pos, mask, val) \
	reg = (reg & (~(mask))) | ACPI_REGISTER_PREPARE_BITS(val, pos, mask)

#घोषणा ACPI_INSERT_BITS(target, mask, source) \
	target = ((target & (~(mask))) | (source & mask))

/* Generic bitfield macros and masks */

#घोषणा ACPI_GET_BITS(source_ptr, position, mask) \
	((*(source_ptr) >> (position)) & (mask))

#घोषणा ACPI_SET_BITS(target_ptr, position, mask, value) \
	(*(target_ptr) |= (((value) & (mask)) << (position)))

#घोषणा ACPI_1BIT_MASK      0x00000001
#घोषणा ACPI_2BIT_MASK      0x00000003
#घोषणा ACPI_3BIT_MASK      0x00000007
#घोषणा ACPI_4BIT_MASK      0x0000000F
#घोषणा ACPI_5BIT_MASK      0x0000001F
#घोषणा ACPI_6BIT_MASK      0x0000003F
#घोषणा ACPI_7BIT_MASK      0x0000007F
#घोषणा ACPI_8BIT_MASK      0x000000FF
#घोषणा ACPI_16BIT_MASK     0x0000FFFF
#घोषणा ACPI_24BIT_MASK     0x00FFFFFF

/* Macros to extract flag bits from position zero */

#घोषणा ACPI_GET_1BIT_FLAG(value)                   ((value) & ACPI_1BIT_MASK)
#घोषणा ACPI_GET_2BIT_FLAG(value)                   ((value) & ACPI_2BIT_MASK)
#घोषणा ACPI_GET_3BIT_FLAG(value)                   ((value) & ACPI_3BIT_MASK)
#घोषणा ACPI_GET_4BIT_FLAG(value)                   ((value) & ACPI_4BIT_MASK)

/* Macros to extract flag bits from position one and above */

#घोषणा ACPI_EXTRACT_1BIT_FLAG(field, position)     (ACPI_GET_1BIT_FLAG ((field) >> position))
#घोषणा ACPI_EXTRACT_2BIT_FLAG(field, position)     (ACPI_GET_2BIT_FLAG ((field) >> position))
#घोषणा ACPI_EXTRACT_3BIT_FLAG(field, position)     (ACPI_GET_3BIT_FLAG ((field) >> position))
#घोषणा ACPI_EXTRACT_4BIT_FLAG(field, position)     (ACPI_GET_4BIT_FLAG ((field) >> position))

/* ACPI Pathname helpers */

#घोषणा ACPI_IS_ROOT_PREFIX(c)      ((c) == (u8) 0x5C)	/* Backslash */
#घोषणा ACPI_IS_PARENT_PREFIX(c)    ((c) == (u8) 0x5E)	/* Carat */
#घोषणा ACPI_IS_PATH_SEPARATOR(c)   ((c) == (u8) 0x2E)	/* Period (करोt) */

/*
 * An object of type काष्ठा acpi_namespace_node can appear in some contexts
 * where a poपूर्णांकer to an object of type जोड़ acpi_opeअक्रम_object can also
 * appear. This macro is used to distinguish them.
 *
 * The "DescriptorType" field is the second field in both काष्ठाures.
 */
#घोषणा ACPI_GET_DESCRIPTOR_PTR(d)      (((जोड़ acpi_descriptor *)(व्योम *)(d))->common.common_poपूर्णांकer)
#घोषणा ACPI_SET_DESCRIPTOR_PTR(d, p)   (((जोड़ acpi_descriptor *)(व्योम *)(d))->common.common_poपूर्णांकer = (p))
#घोषणा ACPI_GET_DESCRIPTOR_TYPE(d)     (((जोड़ acpi_descriptor *)(व्योम *)(d))->common.descriptor_type)
#घोषणा ACPI_SET_DESCRIPTOR_TYPE(d, t)  (((जोड़ acpi_descriptor *)(व्योम *)(d))->common.descriptor_type = (t))

/*
 * Macros क्रम the master AML opcode table
 */
#अगर defined (ACPI_DISASSEMBLER) || defined (ACPI_DEBUG_OUTPUT)
#घोषणा ACPI_OP(name, Pargs, Iargs, obj_type, class, type, flags) \
	अणुname, (u32)(Pargs), (u32)(Iargs), (u32)(flags), obj_type, class, typeपूर्ण
#अन्यथा
#घोषणा ACPI_OP(name, Pargs, Iargs, obj_type, class, type, flags) \
	अणु(u32)(Pargs), (u32)(Iargs), (u32)(flags), obj_type, class, typeपूर्ण
#पूर्ण_अगर

#घोषणा ARG_TYPE_WIDTH                  5
#घोषणा ARG_1(x)                        ((u32)(x))
#घोषणा ARG_2(x)                        ((u32)(x) << (1 * ARG_TYPE_WIDTH))
#घोषणा ARG_3(x)                        ((u32)(x) << (2 * ARG_TYPE_WIDTH))
#घोषणा ARG_4(x)                        ((u32)(x) << (3 * ARG_TYPE_WIDTH))
#घोषणा ARG_5(x)                        ((u32)(x) << (4 * ARG_TYPE_WIDTH))
#घोषणा ARG_6(x)                        ((u32)(x) << (5 * ARG_TYPE_WIDTH))

#घोषणा ARGI_LIST1(a)                   (ARG_1(a))
#घोषणा ARGI_LIST2(a, b)                (ARG_1(b)|ARG_2(a))
#घोषणा ARGI_LIST3(a, b, c)             (ARG_1(c)|ARG_2(b)|ARG_3(a))
#घोषणा ARGI_LIST4(a, b, c, d)          (ARG_1(d)|ARG_2(c)|ARG_3(b)|ARG_4(a))
#घोषणा ARGI_LIST5(a, b, c, d, e)       (ARG_1(e)|ARG_2(d)|ARG_3(c)|ARG_4(b)|ARG_5(a))
#घोषणा ARGI_LIST6(a, b, c, d, e, f)    (ARG_1(f)|ARG_2(e)|ARG_3(d)|ARG_4(c)|ARG_5(b)|ARG_6(a))

#घोषणा ARGP_LIST1(a)                   (ARG_1(a))
#घोषणा ARGP_LIST2(a, b)                (ARG_1(a)|ARG_2(b))
#घोषणा ARGP_LIST3(a, b, c)             (ARG_1(a)|ARG_2(b)|ARG_3(c))
#घोषणा ARGP_LIST4(a, b, c, d)          (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d))
#घोषणा ARGP_LIST5(a, b, c, d, e)       (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e))
#घोषणा ARGP_LIST6(a, b, c, d, e, f)    (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e)|ARG_6(f))

#घोषणा GET_CURRENT_ARG_TYPE(list)      (list & ((u32) 0x1F))
#घोषणा INCREMENT_ARG_LIST(list)        (list >>= ((u32) ARG_TYPE_WIDTH))

/*
 * Ascii error messages can be configured out
 */
#अगर_अघोषित ACPI_NO_ERROR_MESSAGES
/*
 * Error reporting. The callers module and line number are inserted by AE_INFO,
 * the plist contains a set of parens to allow variable-length lists.
 * These macros are used क्रम both the debug and non-debug versions of the code.
 */
#घोषणा ACPI_ERROR_NAMESPACE(s, p, e)       acpi_ut_prefixed_namespace_error (AE_INFO, s, p, e);
#घोषणा ACPI_ERROR_METHOD(s, n, p, e)       acpi_ut_method_error (AE_INFO, s, n, p, e);
#घोषणा ACPI_WARN_PREDEFINED(plist)         acpi_ut_predefined_warning plist
#घोषणा ACPI_INFO_PREDEFINED(plist)         acpi_ut_predefined_info plist
#घोषणा ACPI_BIOS_ERROR_PREDEFINED(plist)   acpi_ut_predefined_bios_error plist
#घोषणा ACPI_ERROR_ONLY(s)                  s

#अन्यथा

/* No error messages */

#घोषणा ACPI_ERROR_NAMESPACE(s, p, e)
#घोषणा ACPI_ERROR_METHOD(s, n, p, e)
#घोषणा ACPI_WARN_PREDEFINED(plist)
#घोषणा ACPI_INFO_PREDEFINED(plist)
#घोषणा ACPI_BIOS_ERROR_PREDEFINED(plist)
#घोषणा ACPI_ERROR_ONLY(s)

#पूर्ण_अगर				/* ACPI_NO_ERROR_MESSAGES */

#अगर (!ACPI_REDUCED_HARDWARE)
#घोषणा ACPI_HW_OPTIONAL_FUNCTION(addr)     addr
#अन्यथा
#घोषणा ACPI_HW_OPTIONAL_FUNCTION(addr)     शून्य
#पूर्ण_अगर

/*
 * Macros used क्रम ACPICA utilities only
 */

/* Generate a UUID */

#घोषणा ACPI_INIT_UUID(a, b, c, d0, d1, d2, d3, d4, d5, d6, d7) \
	(a) & 0xFF, ((a) >> 8) & 0xFF, ((a) >> 16) & 0xFF, ((a) >> 24) & 0xFF, \
	(b) & 0xFF, ((b) >> 8) & 0xFF, \
	(c) & 0xFF, ((c) >> 8) & 0xFF, \
	(d0), (d1), (d2), (d3), (d4), (d5), (d6), (d7)

#घोषणा ACPI_IS_OCTAL_DIGIT(d)              (((अक्षर)(d) >= '0') && ((char)(d) <= '7'))

/*
 * Macros used क्रम the ASL-/ASL+ converter utility
 */
#अगर_घोषित ACPI_ASL_COMPILER

#घोषणा ASL_CV_LABEL_खाताNODE(a)         cv_label_file_node(a);
#घोषणा ASL_CV_CAPTURE_COMMENTS_ONLY(a)   cv_capture_comments_only (a);
#घोषणा ASL_CV_CAPTURE_COMMENTS(a)       cv_capture_comments (a);
#घोषणा ASL_CV_TRANSFER_COMMENTS(a)      cv_transfer_comments (a);
#घोषणा ASL_CV_CLOSE_PAREN(a,b)          cv_बंद_paren_ग_लिखो_comment(a,b);
#घोषणा ASL_CV_CLOSE_BRACE(a,b)          cv_बंद_brace_ग_लिखो_comment(a,b);
#घोषणा ASL_CV_SWITCH_खाताS(a,b)         cv_चयन_files(a,b);
#घोषणा ASL_CV_CLEAR_OP_COMMENTS(a)       cv_clear_op_comments(a);
#घोषणा ASL_CV_PRINT_ONE_COMMENT(a,b,c,d) cv_prपूर्णांक_one_comment_type (a,b,c,d);
#घोषणा ASL_CV_PRINT_ONE_COMMENT_LIST(a,b) cv_prपूर्णांक_one_comment_list (a,b);
#घोषणा ASL_CV_खाता_HAS_SWITCHED(a)       cv_file_has_चयनed(a)
#घोषणा ASL_CV_INIT_खाताTREE(a,b)      cv_init_file_tree(a,b);

#अन्यथा

#घोषणा ASL_CV_LABEL_खाताNODE(a)
#घोषणा ASL_CV_CAPTURE_COMMENTS_ONLY(a)
#घोषणा ASL_CV_CAPTURE_COMMENTS(a)
#घोषणा ASL_CV_TRANSFER_COMMENTS(a)
#घोषणा ASL_CV_CLOSE_PAREN(a,b)          acpi_os_म_लिखो (")");
#घोषणा ASL_CV_CLOSE_BRACE(a,b)          acpi_os_म_लिखो ("}");
#घोषणा ASL_CV_SWITCH_खाताS(a,b)
#घोषणा ASL_CV_CLEAR_OP_COMMENTS(a)
#घोषणा ASL_CV_PRINT_ONE_COMMENT(a,b,c,d)
#घोषणा ASL_CV_PRINT_ONE_COMMENT_LIST(a,b)
#घोषणा ASL_CV_खाता_HAS_SWITCHED(a)       0
#घोषणा ASL_CV_INIT_खाताTREE(a,b)

#पूर्ण_अगर

#पूर्ण_अगर				/* ACMACROS_H */
