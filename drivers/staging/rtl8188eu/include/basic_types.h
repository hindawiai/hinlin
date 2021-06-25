<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __BASIC_TYPES_H__
#घोषणा __BASIC_TYPES_H__

#समावेश <linux/types.h>
#घोषणा NDIS_OID uपूर्णांक

/* port from fw */
/*  TODO: Macros Below are Sync from SD7-Driver. It is necessary
 * to check correctness
 */

/*
 *	Call endian मुक्त function when
 *		1. Read/ग_लिखो packet content.
 *		2. Beक्रमe ग_लिखो पूर्णांकeger to IO.
 *		3. After पढ़ो पूर्णांकeger from IO.
 */

/* Convert little data endian to host ordering */
#घोषणा EF1BYTE(_val)		\
	((u8)(_val))
#घोषणा EF2BYTE(_val)		\
	(le16_to_cpu(_val))
#घोषणा EF4BYTE(_val)		\
	(le32_to_cpu(_val))

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

/* Description:
 * Translate subfield (continuous bits in little-endian) of 4-byte
 * value to host byte ordering.
 */
#घोषणा LE_BITS_TO_4BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		(LE_P4BYTE_TO_HOST_4BYTE(__pstart) >> (__bitoffset))  & \
		BIT_LEN_MASK_32(__bitlen) \
	)
#घोषणा LE_BITS_TO_2BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		(LE_P2BYTE_TO_HOST_2BYTE(__pstart) >> (__bitoffset)) & \
		BIT_LEN_MASK_16(__bitlen) \
	)
#घोषणा LE_BITS_TO_1BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		(LE_P1BYTE_TO_HOST_1BYTE(__pstart) >> (__bitoffset)) & \
		BIT_LEN_MASK_8(__bitlen) \
	)

/* Description:
 * Mask subfield (continuous bits in little-endian) of 4-byte value
 * and वापस the result in 4-byte value in host byte ordering.
 */
#घोषणा LE_BITS_CLEARED_TO_4BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		LE_P4BYTE_TO_HOST_4BYTE(__pstart)  & \
		(~BIT_OFFSET_LEN_MASK_32(__bitoffset, __bitlen)) \
	)
#घोषणा LE_BITS_CLEARED_TO_2BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		LE_P2BYTE_TO_HOST_2BYTE(__pstart) & \
		(~BIT_OFFSET_LEN_MASK_16(__bitoffset, __bitlen)) \
	)
#घोषणा LE_BITS_CLEARED_TO_1BYTE(__pstart, __bitoffset, __bitlen) \
	( \
		LE_P1BYTE_TO_HOST_1BYTE(__pstart) & \
		(~BIT_OFFSET_LEN_MASK_8(__bitoffset, __bitlen)) \
	)

/* Description:
 * Set subfield of little-endian 4-byte value to specअगरied value.
 */
#घोषणा SET_BITS_TO_LE_4BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u32 *)(__pstart)) =				\
		(							\
		LE_BITS_CLEARED_TO_4BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u32)__val) & BIT_LEN_MASK_32(__bitlen)) << (__bitoffset)) \
		)

#घोषणा SET_BITS_TO_LE_2BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u16 *)(__pstart)) =				\
		(						\
		LE_BITS_CLEARED_TO_2BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u16)__val) & BIT_LEN_MASK_16(__bitlen)) << (__bitoffset)) \
		);

#घोषणा SET_BITS_TO_LE_1BYTE(__pstart, __bitoffset, __bitlen, __val) \
		*((u8 *)(__pstart)) = EF1BYTE			\
		(						\
		LE_BITS_CLEARED_TO_1BYTE(__pstart, __bitoffset, __bitlen) | \
		((((u8)__val) & BIT_LEN_MASK_8(__bitlen)) << (__bitoffset)) \
		)

#पूर्ण_अगर /* __BASIC_TYPES_H__ */
