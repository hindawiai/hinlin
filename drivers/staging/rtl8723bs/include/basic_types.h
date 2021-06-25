<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __BASIC_TYPES_H__
#घोषणा __BASIC_TYPES_H__


#घोषणा SUCCESS	0
#घोषणा FAIL	(-1)

#समावेश <linux/types.h>

#घोषणा FIELD_OFFSET(s, field)	((__kernel_sमाप_प्रकार)&((s *)(0))->field)

#घोषणा SIZE_PTR __kernel_माप_प्रकार
#घोषणा SSIZE_PTR __kernel_sमाप_प्रकार

/* port from fw by thomas */
/*  TODO: Belows are Sync from SD7-Driver. It is necessary to check correctness */

/*
 *Call endian मुक्त function when
 *	1. Read/ग_लिखो packet content.
 *	2. Beक्रमe ग_लिखो पूर्णांकeger to IO.
 *	3. After पढ़ो पूर्णांकeger from IO.
*/

/*  */
/*  Byte Swapping routine. */
/*  */
#घोषणा EF1Byte	(u8)
#घोषणा EF2Byte		le16_to_cpu
#घोषणा EF4Byte	le32_to_cpu

/* Convert little data endian to host ordering */
#घोषणा EF1BYTE(_val)		\
	((u8)(_val))
#घोषणा EF2BYTE(_val)		\
	(le16_to_cpu(_val))
#घोषणा EF4BYTE(_val)		\
	(le32_to_cpu(_val))

/* Read data from memory */
#घोषणा READEF1BYTE(_ptr)	\
	EF1BYTE(*((u8 *)(_ptr)))
/* Read le16 data from memory and convert to host ordering */
#घोषणा READEF2BYTE(_ptr)	\
	EF2BYTE(*(_ptr))
#घोषणा READEF4BYTE(_ptr)	\
	EF4BYTE(*(_ptr))

/* Write data to memory */
#घोषणा WRITEEF1BYTE(_ptr, _val)			\
	करो अणु						\
		(*((u8 *)(_ptr))) = EF1BYTE(_val);	\
	पूर्ण जबतक (0)
/* Write le data to memory in host ordering */
#घोषणा WRITEEF2BYTE(_ptr, _val)			\
	करो अणु						\
		(*((u16 *)(_ptr))) = EF2BYTE(_val);	\
	पूर्ण जबतक (0)

#घोषणा WRITEEF4BYTE(_ptr, _val)			\
	करो अणु						\
		(*((u32 *)(_ptr))) = EF2BYTE(_val);	\
	पूर्ण जबतक (0)

/* Create a bit mask
 * Examples:
 * BIT_LEN_MASK_32(0) => 0x00000000
 * BIT_LEN_MASK_32(1) => 0x00000001
 * BIT_LEN_MASK_32(2) => 0x00000003
 * BIT_LEN_MASK_32(32) => 0xFFFFFFFF
 */
#घोषणा BIT_LEN_MASK_32(__bitlen)	 \
	(0xFFFFFFFF >> (32 - (__bitlen)))
#घोषणा BIT_LEN_MASK_16(__bitlen)	 \
	(0xFFFF >> (16 - (__bitlen)))
#घोषणा BIT_LEN_MASK_8(__bitlen) \
	(0xFF >> (8 - (__bitlen)))

/* Create an offset bit mask
 * Examples:
 * BIT_OFFSET_LEN_MASK_32(0, 2) => 0x00000003
 * BIT_OFFSET_LEN_MASK_32(16, 2) => 0x00030000
 */
#घोषणा BIT_OFFSET_LEN_MASK_32(__bitoffset, __bitlen) \
	(BIT_LEN_MASK_32(__bitlen) << (__bitoffset))
#घोषणा BIT_OFFSET_LEN_MASK_16(__bitoffset, __bitlen) \
	(BIT_LEN_MASK_16(__bitlen) << (__bitoffset))
#घोषणा BIT_OFFSET_LEN_MASK_8(__bitoffset, __bitlen) \
	(BIT_LEN_MASK_8(__bitlen) << (__bitoffset))

/*Description:
 * Return 4-byte value in host byte ordering from
 * 4-byte poपूर्णांकer in little-endian प्रणाली.
 */
#घोषणा LE_P4BYTE_TO_HOST_4BYTE(__pstart) \
	(EF4BYTE(*((__le32 *)(__pstart))))
#घोषणा LE_P2BYTE_TO_HOST_2BYTE(__pstart) \
	(EF2BYTE(*((__le16 *)(__pstart))))
#घोषणा LE_P1BYTE_TO_HOST_1BYTE(__pstart) \
	(EF1BYTE(*((u8 *)(__pstart))))

/*  */
/* 	Description: */
/* 		Translate subfield (continuous bits in little-endian) of 4-byte value in litten byte to */
/* 		4-byte value in host byte ordering. */
/*  */
#घोषणा LE_BITS_TO_4BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		(LE_P4BYTE_TO_HOST_4BYTE(__pstart) >> (__bitoffset))  & \
		BIT_LEN_MASK_32(__bitlen) \
	)
#घोषणा LE_BITS_TO_2BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		(LE_P2BYTE_TO_HOST_2BYTE(__pstart) >> (__bitoffset)) & \
		BIT_LEN_MASK_16(__bitlen) \
	)
#घोषणा LE_BITS_TO_1BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		(LE_P1BYTE_TO_HOST_1BYTE(__pstart) >> (__bitoffset)) & \
		BIT_LEN_MASK_8(__bitlen) \
	)

/*  */
/* 	Description: */
/* 		Mask subfield (continuous bits in little-endian) of 4-byte value in litten byte oredering */
/* 		and वापस the result in 4-byte value in host byte ordering. */
/*  */
#घोषणा LE_BITS_CLEARED_TO_4BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		LE_P4BYTE_TO_HOST_4BYTE(__pstart)  & \
		(~BIT_OFFSET_LEN_MASK_32(__bitoffset, __bitlen)) \
	)
#घोषणा LE_BITS_CLEARED_TO_2BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		LE_P2BYTE_TO_HOST_2BYTE(__pstart) & \
		(~BIT_OFFSET_LEN_MASK_16(__bitoffset, __bitlen)) \
	)
#घोषणा LE_BITS_CLEARED_TO_1BYTE(__pstart, __bitoffset, __bitlen) \
	(\
		LE_P1BYTE_TO_HOST_1BYTE(__pstart) & \
		(~BIT_OFFSET_LEN_MASK_8(__bitoffset, __bitlen)) \
	)

/*  */
/* 	Description: */
/* 		Set subfield of little-endian 4-byte value to specअगरied value. */
/*  */
#घोषणा SET_BITS_TO_LE_4BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u32 *)(__pstart)) =				\
		(						\
		LE_BITS_CLEARED_TO_4BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u32)__val) & BIT_LEN_MASK_32(__bitlen)) << (__bitoffset)) \
		)

#घोषणा SET_BITS_TO_LE_2BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u16 *)(__pstart)) =				\
		(					\
		LE_BITS_CLEARED_TO_2BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u16)__val) & BIT_LEN_MASK_16(__bitlen)) << (__bitoffset)) \
		);

#घोषणा SET_BITS_TO_LE_1BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u8 *)(__pstart)) = EF1BYTE			\
		(					\
		LE_BITS_CLEARED_TO_1BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u8)__val) & BIT_LEN_MASK_8(__bitlen)) << (__bitoffset)) \
		)

#घोषणा LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
	(\
		LE_P1BYTE_TO_HOST_1BYTE(__pStart) \
	)

#घोषणा SET_BITS_TO_LE_1BYTE_8BIT(__pStart, __BitOffset, __BitLen, __Value) \
अणु \
	*((u8 *)(__pStart)) = \
		EF1Byte(\
			LE_BITS_CLEARED_TO_1BYTE_8BIT(__pStart, __BitOffset, __BitLen) \
			| \
			((u8)__Value) \
		); \
पूर्ण

/*  Get the N-bytes alignent offset from the current length */
#घोषणा N_BYTE_ALIGMENT(__Value, __Aligment) ((__Aligment == 1) ? (__Value) : (((__Value + __Aligment - 1) / __Aligment) * __Aligment))

#घोषणा TEST_FLAG(__Flag, __testFlag)		(((__Flag) & (__testFlag)) != 0)
#घोषणा SET_FLAG(__Flag, __setFlag)			((__Flag) |= __setFlag)
#घोषणा CLEAR_FLAG(__Flag, __clearFlag)		((__Flag) &= ~(__clearFlag))
#घोषणा CLEAR_FLAGS(__Flag)					((__Flag) = 0)
#घोषणा TEST_FLAGS(__Flag, __testFlags)		(((__Flag) & (__testFlags)) == (__testFlags))

#पूर्ण_अगर /* __BASIC_TYPES_H__ */
