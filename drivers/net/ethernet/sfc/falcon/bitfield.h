<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_BITFIELD_H
#घोषणा EF4_BITFIELD_H

/*
 * Efx bitfield access
 *
 * Efx NICs make extensive use of bitfields up to 128 bits
 * wide.  Since there is no native 128-bit datatype on most प्रणालीs,
 * and since 64-bit datatypes are inefficient on 32-bit प्रणालीs and
 * vice versa, we wrap accesses in a way that uses the most efficient
 * datatype.
 *
 * The NICs are PCI devices and thereक्रमe little-endian.  Since most
 * of the quantities that we deal with are DMAed to/from host memory,
 * we define our datatypes (ef4_oword_t, ef4_qword_t and
 * ef4_dword_t) to be little-endian.
 */

/* Lowest bit numbers and widths */
#घोषणा EF4_DUMMY_FIELD_LBN 0
#घोषणा EF4_DUMMY_FIELD_WIDTH 0
#घोषणा EF4_WORD_0_LBN 0
#घोषणा EF4_WORD_0_WIDTH 16
#घोषणा EF4_WORD_1_LBN 16
#घोषणा EF4_WORD_1_WIDTH 16
#घोषणा EF4_DWORD_0_LBN 0
#घोषणा EF4_DWORD_0_WIDTH 32
#घोषणा EF4_DWORD_1_LBN 32
#घोषणा EF4_DWORD_1_WIDTH 32
#घोषणा EF4_DWORD_2_LBN 64
#घोषणा EF4_DWORD_2_WIDTH 32
#घोषणा EF4_DWORD_3_LBN 96
#घोषणा EF4_DWORD_3_WIDTH 32
#घोषणा EF4_QWORD_0_LBN 0
#घोषणा EF4_QWORD_0_WIDTH 64

/* Specअगरied attribute (e.g. LBN) of the specअगरied field */
#घोषणा EF4_VAL(field, attribute) field ## _ ## attribute
/* Low bit number of the specअगरied field */
#घोषणा EF4_LOW_BIT(field) EF4_VAL(field, LBN)
/* Bit width of the specअगरied field */
#घोषणा EF4_WIDTH(field) EF4_VAL(field, WIDTH)
/* High bit number of the specअगरied field */
#घोषणा EF4_HIGH_BIT(field) (EF4_LOW_BIT(field) + EF4_WIDTH(field) - 1)
/* Mask equal in width to the specअगरied field.
 *
 * For example, a field with width 5 would have a mask of 0x1f.
 *
 * The maximum width mask that can be generated is 64 bits.
 */
#घोषणा EF4_MASK64(width)			\
	((width) == 64 ? ~((u64) 0) :		\
	 (((((u64) 1) << (width))) - 1))

/* Mask equal in width to the specअगरied field.
 *
 * For example, a field with width 5 would have a mask of 0x1f.
 *
 * The maximum width mask that can be generated is 32 bits.  Use
 * EF4_MASK64 क्रम higher width fields.
 */
#घोषणा EF4_MASK32(width)			\
	((width) == 32 ? ~((u32) 0) :		\
	 (((((u32) 1) << (width))) - 1))

/* A द्विगुनword (i.e. 4 byte) datatype - little-endian in HW */
प्रकार जोड़ ef4_dword अणु
	__le32 u32[1];
पूर्ण ef4_dword_t;

/* A quadword (i.e. 8 byte) datatype - little-endian in HW */
प्रकार जोड़ ef4_qword अणु
	__le64 u64[1];
	__le32 u32[2];
	ef4_dword_t dword[2];
पूर्ण ef4_qword_t;

/* An octword (eight-word, i.e. 16 byte) datatype - little-endian in HW */
प्रकार जोड़ ef4_oword अणु
	__le64 u64[2];
	ef4_qword_t qword[2];
	__le32 u32[4];
	ef4_dword_t dword[4];
पूर्ण ef4_oword_t;

/* Format string and value expanders क्रम prपूर्णांकk */
#घोषणा EF4_DWORD_FMT "%08x"
#घोषणा EF4_QWORD_FMT "%08x:%08x"
#घोषणा EF4_OWORD_FMT "%08x:%08x:%08x:%08x"
#घोषणा EF4_DWORD_VAL(dword)				\
	((अचिन्हित पूर्णांक) le32_to_cpu((dword).u32[0]))
#घोषणा EF4_QWORD_VAL(qword)				\
	((अचिन्हित पूर्णांक) le32_to_cpu((qword).u32[1])),	\
	((अचिन्हित पूर्णांक) le32_to_cpu((qword).u32[0]))
#घोषणा EF4_OWORD_VAL(oword)				\
	((अचिन्हित पूर्णांक) le32_to_cpu((oword).u32[3])),	\
	((अचिन्हित पूर्णांक) le32_to_cpu((oword).u32[2])),	\
	((अचिन्हित पूर्णांक) le32_to_cpu((oword).u32[1])),	\
	((अचिन्हित पूर्णांक) le32_to_cpu((oword).u32[0]))

/*
 * Extract bit field portion [low,high) from the native-endian element
 * which contains bits [min,max).
 *
 * For example, suppose "element" represents the high 32 bits of a
 * 64-bit value, and we wish to extract the bits beदीर्घing to the bit
 * field occupying bits 28-45 of this 64-bit value.
 *
 * Then EF4_EXTRACT ( element, 32, 63, 28, 45 ) would give
 *
 *   ( element ) << 4
 *
 * The result will contain the relevant bits filled in in the range
 * [0,high-low), with garbage in bits [high-low+1,...).
 */
#घोषणा EF4_EXTRACT_NATIVE(native_element, min, max, low, high)		\
	((low) > (max) || (high) < (min) ? 0 :				\
	 (low) > (min) ?						\
	 (native_element) >> ((low) - (min)) :				\
	 (native_element) << ((min) - (low)))

/*
 * Extract bit field portion [low,high) from the 64-bit little-endian
 * element which contains bits [min,max)
 */
#घोषणा EF4_EXTRACT64(element, min, max, low, high)			\
	EF4_EXTRACT_NATIVE(le64_to_cpu(element), min, max, low, high)

/*
 * Extract bit field portion [low,high) from the 32-bit little-endian
 * element which contains bits [min,max)
 */
#घोषणा EF4_EXTRACT32(element, min, max, low, high)			\
	EF4_EXTRACT_NATIVE(le32_to_cpu(element), min, max, low, high)

#घोषणा EF4_EXTRACT_OWORD64(oword, low, high)				\
	((EF4_EXTRACT64((oword).u64[0], 0, 63, low, high) |		\
	  EF4_EXTRACT64((oword).u64[1], 64, 127, low, high)) &		\
	 EF4_MASK64((high) + 1 - (low)))

#घोषणा EF4_EXTRACT_QWORD64(qword, low, high)				\
	(EF4_EXTRACT64((qword).u64[0], 0, 63, low, high) &		\
	 EF4_MASK64((high) + 1 - (low)))

#घोषणा EF4_EXTRACT_OWORD32(oword, low, high)				\
	((EF4_EXTRACT32((oword).u32[0], 0, 31, low, high) |		\
	  EF4_EXTRACT32((oword).u32[1], 32, 63, low, high) |		\
	  EF4_EXTRACT32((oword).u32[2], 64, 95, low, high) |		\
	  EF4_EXTRACT32((oword).u32[3], 96, 127, low, high)) &		\
	 EF4_MASK32((high) + 1 - (low)))

#घोषणा EF4_EXTRACT_QWORD32(qword, low, high)				\
	((EF4_EXTRACT32((qword).u32[0], 0, 31, low, high) |		\
	  EF4_EXTRACT32((qword).u32[1], 32, 63, low, high)) &		\
	 EF4_MASK32((high) + 1 - (low)))

#घोषणा EF4_EXTRACT_DWORD(dword, low, high)			\
	(EF4_EXTRACT32((dword).u32[0], 0, 31, low, high) &	\
	 EF4_MASK32((high) + 1 - (low)))

#घोषणा EF4_OWORD_FIELD64(oword, field)				\
	EF4_EXTRACT_OWORD64(oword, EF4_LOW_BIT(field),		\
			    EF4_HIGH_BIT(field))

#घोषणा EF4_QWORD_FIELD64(qword, field)				\
	EF4_EXTRACT_QWORD64(qword, EF4_LOW_BIT(field),		\
			    EF4_HIGH_BIT(field))

#घोषणा EF4_OWORD_FIELD32(oword, field)				\
	EF4_EXTRACT_OWORD32(oword, EF4_LOW_BIT(field),		\
			    EF4_HIGH_BIT(field))

#घोषणा EF4_QWORD_FIELD32(qword, field)				\
	EF4_EXTRACT_QWORD32(qword, EF4_LOW_BIT(field),		\
			    EF4_HIGH_BIT(field))

#घोषणा EF4_DWORD_FIELD(dword, field)				\
	EF4_EXTRACT_DWORD(dword, EF4_LOW_BIT(field),		\
			  EF4_HIGH_BIT(field))

#घोषणा EF4_OWORD_IS_ZERO64(oword)					\
	(((oword).u64[0] | (oword).u64[1]) == (__क्रमce __le64) 0)

#घोषणा EF4_QWORD_IS_ZERO64(qword)					\
	(((qword).u64[0]) == (__क्रमce __le64) 0)

#घोषणा EF4_OWORD_IS_ZERO32(oword)					     \
	(((oword).u32[0] | (oword).u32[1] | (oword).u32[2] | (oword).u32[3]) \
	 == (__क्रमce __le32) 0)

#घोषणा EF4_QWORD_IS_ZERO32(qword)					\
	(((qword).u32[0] | (qword).u32[1]) == (__क्रमce __le32) 0)

#घोषणा EF4_DWORD_IS_ZERO(dword)					\
	(((dword).u32[0]) == (__क्रमce __le32) 0)

#घोषणा EF4_OWORD_IS_ALL_ONES64(oword)					\
	(((oword).u64[0] & (oword).u64[1]) == ~((__क्रमce __le64) 0))

#घोषणा EF4_QWORD_IS_ALL_ONES64(qword)					\
	((qword).u64[0] == ~((__क्रमce __le64) 0))

#घोषणा EF4_OWORD_IS_ALL_ONES32(oword)					\
	(((oword).u32[0] & (oword).u32[1] & (oword).u32[2] & (oword).u32[3]) \
	 == ~((__क्रमce __le32) 0))

#घोषणा EF4_QWORD_IS_ALL_ONES32(qword)					\
	(((qword).u32[0] & (qword).u32[1]) == ~((__क्रमce __le32) 0))

#घोषणा EF4_DWORD_IS_ALL_ONES(dword)					\
	((dword).u32[0] == ~((__क्रमce __le32) 0))

#अगर BITS_PER_LONG == 64
#घोषणा EF4_OWORD_FIELD		EF4_OWORD_FIELD64
#घोषणा EF4_QWORD_FIELD		EF4_QWORD_FIELD64
#घोषणा EF4_OWORD_IS_ZERO	EF4_OWORD_IS_ZERO64
#घोषणा EF4_QWORD_IS_ZERO	EF4_QWORD_IS_ZERO64
#घोषणा EF4_OWORD_IS_ALL_ONES	EF4_OWORD_IS_ALL_ONES64
#घोषणा EF4_QWORD_IS_ALL_ONES	EF4_QWORD_IS_ALL_ONES64
#अन्यथा
#घोषणा EF4_OWORD_FIELD		EF4_OWORD_FIELD32
#घोषणा EF4_QWORD_FIELD		EF4_QWORD_FIELD32
#घोषणा EF4_OWORD_IS_ZERO	EF4_OWORD_IS_ZERO32
#घोषणा EF4_QWORD_IS_ZERO	EF4_QWORD_IS_ZERO32
#घोषणा EF4_OWORD_IS_ALL_ONES	EF4_OWORD_IS_ALL_ONES32
#घोषणा EF4_QWORD_IS_ALL_ONES	EF4_QWORD_IS_ALL_ONES32
#पूर्ण_अगर

/*
 * Conकाष्ठा bit field portion
 *
 * Creates the portion of the bit field [low,high) that lies within
 * the range [min,max).
 */
#घोषणा EF4_INSERT_NATIVE64(min, max, low, high, value)		\
	(((low > max) || (high < min)) ? 0 :			\
	 ((low > min) ?						\
	  (((u64) (value)) << (low - min)) :		\
	  (((u64) (value)) >> (min - low))))

#घोषणा EF4_INSERT_NATIVE32(min, max, low, high, value)		\
	(((low > max) || (high < min)) ? 0 :			\
	 ((low > min) ?						\
	  (((u32) (value)) << (low - min)) :		\
	  (((u32) (value)) >> (min - low))))

#घोषणा EF4_INSERT_NATIVE(min, max, low, high, value)		\
	((((max - min) >= 32) || ((high - low) >= 32)) ?	\
	 EF4_INSERT_NATIVE64(min, max, low, high, value) :	\
	 EF4_INSERT_NATIVE32(min, max, low, high, value))

/*
 * Conकाष्ठा bit field portion
 *
 * Creates the portion of the named bit field that lies within the
 * range [min,max).
 */
#घोषणा EF4_INSERT_FIELD_NATIVE(min, max, field, value)		\
	EF4_INSERT_NATIVE(min, max, EF4_LOW_BIT(field),		\
			  EF4_HIGH_BIT(field), value)

/*
 * Conकाष्ठा bit field
 *
 * Creates the portion of the named bit fields that lie within the
 * range [min,max).
 */
#घोषणा EF4_INSERT_FIELDS_NATIVE(min, max,				\
				 field1, value1,			\
				 field2, value2,			\
				 field3, value3,			\
				 field4, value4,			\
				 field5, value5,			\
				 field6, value6,			\
				 field7, value7,			\
				 field8, value8,			\
				 field9, value9,			\
				 field10, value10)			\
	(EF4_INSERT_FIELD_NATIVE((min), (max), field1, (value1)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field2, (value2)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field3, (value3)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field4, (value4)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field5, (value5)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field6, (value6)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field7, (value7)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field8, (value8)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field9, (value9)) |	\
	 EF4_INSERT_FIELD_NATIVE((min), (max), field10, (value10)))

#घोषणा EF4_INSERT_FIELDS64(...)				\
	cpu_to_le64(EF4_INSERT_FIELDS_NATIVE(__VA_ARGS__))

#घोषणा EF4_INSERT_FIELDS32(...)				\
	cpu_to_le32(EF4_INSERT_FIELDS_NATIVE(__VA_ARGS__))

#घोषणा EF4_POPULATE_OWORD64(oword, ...) करो अणु				\
	(oword).u64[0] = EF4_INSERT_FIELDS64(0, 63, __VA_ARGS__);	\
	(oword).u64[1] = EF4_INSERT_FIELDS64(64, 127, __VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा EF4_POPULATE_QWORD64(qword, ...) करो अणु				\
	(qword).u64[0] = EF4_INSERT_FIELDS64(0, 63, __VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा EF4_POPULATE_OWORD32(oword, ...) करो अणु				\
	(oword).u32[0] = EF4_INSERT_FIELDS32(0, 31, __VA_ARGS__);	\
	(oword).u32[1] = EF4_INSERT_FIELDS32(32, 63, __VA_ARGS__);	\
	(oword).u32[2] = EF4_INSERT_FIELDS32(64, 95, __VA_ARGS__);	\
	(oword).u32[3] = EF4_INSERT_FIELDS32(96, 127, __VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा EF4_POPULATE_QWORD32(qword, ...) करो अणु				\
	(qword).u32[0] = EF4_INSERT_FIELDS32(0, 31, __VA_ARGS__);	\
	(qword).u32[1] = EF4_INSERT_FIELDS32(32, 63, __VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा EF4_POPULATE_DWORD(dword, ...) करो अणु				\
	(dword).u32[0] = EF4_INSERT_FIELDS32(0, 31, __VA_ARGS__);	\
	पूर्ण जबतक (0)

#अगर BITS_PER_LONG == 64
#घोषणा EF4_POPULATE_OWORD EF4_POPULATE_OWORD64
#घोषणा EF4_POPULATE_QWORD EF4_POPULATE_QWORD64
#अन्यथा
#घोषणा EF4_POPULATE_OWORD EF4_POPULATE_OWORD32
#घोषणा EF4_POPULATE_QWORD EF4_POPULATE_QWORD32
#पूर्ण_अगर

/* Populate an octword field with various numbers of arguments */
#घोषणा EF4_POPULATE_OWORD_10 EF4_POPULATE_OWORD
#घोषणा EF4_POPULATE_OWORD_9(oword, ...) \
	EF4_POPULATE_OWORD_10(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_8(oword, ...) \
	EF4_POPULATE_OWORD_9(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_7(oword, ...) \
	EF4_POPULATE_OWORD_8(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_6(oword, ...) \
	EF4_POPULATE_OWORD_7(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_5(oword, ...) \
	EF4_POPULATE_OWORD_6(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_4(oword, ...) \
	EF4_POPULATE_OWORD_5(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_3(oword, ...) \
	EF4_POPULATE_OWORD_4(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_2(oword, ...) \
	EF4_POPULATE_OWORD_3(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_OWORD_1(oword, ...) \
	EF4_POPULATE_OWORD_2(oword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_ZERO_OWORD(oword) \
	EF4_POPULATE_OWORD_1(oword, EF4_DUMMY_FIELD, 0)
#घोषणा EF4_SET_OWORD(oword) \
	EF4_POPULATE_OWORD_4(oword, \
			     EF4_DWORD_0, 0xffffffff, \
			     EF4_DWORD_1, 0xffffffff, \
			     EF4_DWORD_2, 0xffffffff, \
			     EF4_DWORD_3, 0xffffffff)

/* Populate a quadword field with various numbers of arguments */
#घोषणा EF4_POPULATE_QWORD_10 EF4_POPULATE_QWORD
#घोषणा EF4_POPULATE_QWORD_9(qword, ...) \
	EF4_POPULATE_QWORD_10(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_8(qword, ...) \
	EF4_POPULATE_QWORD_9(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_7(qword, ...) \
	EF4_POPULATE_QWORD_8(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_6(qword, ...) \
	EF4_POPULATE_QWORD_7(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_5(qword, ...) \
	EF4_POPULATE_QWORD_6(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_4(qword, ...) \
	EF4_POPULATE_QWORD_5(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_3(qword, ...) \
	EF4_POPULATE_QWORD_4(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_2(qword, ...) \
	EF4_POPULATE_QWORD_3(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_QWORD_1(qword, ...) \
	EF4_POPULATE_QWORD_2(qword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_ZERO_QWORD(qword) \
	EF4_POPULATE_QWORD_1(qword, EF4_DUMMY_FIELD, 0)
#घोषणा EF4_SET_QWORD(qword) \
	EF4_POPULATE_QWORD_2(qword, \
			     EF4_DWORD_0, 0xffffffff, \
			     EF4_DWORD_1, 0xffffffff)

/* Populate a dword field with various numbers of arguments */
#घोषणा EF4_POPULATE_DWORD_10 EF4_POPULATE_DWORD
#घोषणा EF4_POPULATE_DWORD_9(dword, ...) \
	EF4_POPULATE_DWORD_10(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_8(dword, ...) \
	EF4_POPULATE_DWORD_9(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_7(dword, ...) \
	EF4_POPULATE_DWORD_8(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_6(dword, ...) \
	EF4_POPULATE_DWORD_7(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_5(dword, ...) \
	EF4_POPULATE_DWORD_6(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_4(dword, ...) \
	EF4_POPULATE_DWORD_5(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_3(dword, ...) \
	EF4_POPULATE_DWORD_4(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_2(dword, ...) \
	EF4_POPULATE_DWORD_3(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_POPULATE_DWORD_1(dword, ...) \
	EF4_POPULATE_DWORD_2(dword, EF4_DUMMY_FIELD, 0, __VA_ARGS__)
#घोषणा EF4_ZERO_DWORD(dword) \
	EF4_POPULATE_DWORD_1(dword, EF4_DUMMY_FIELD, 0)
#घोषणा EF4_SET_DWORD(dword) \
	EF4_POPULATE_DWORD_1(dword, EF4_DWORD_0, 0xffffffff)

/*
 * Modअगरy a named field within an alपढ़ोy-populated काष्ठाure.  Used
 * क्रम पढ़ो-modअगरy-ग_लिखो operations.
 *
 */
#घोषणा EF4_INVERT_OWORD(oword) करो अणु		\
	(oword).u64[0] = ~((oword).u64[0]);	\
	(oword).u64[1] = ~((oword).u64[1]);	\
	पूर्ण जबतक (0)

#घोषणा EF4_AND_OWORD(oword, from, mask)			\
	करो अणु							\
		(oword).u64[0] = (from).u64[0] & (mask).u64[0];	\
		(oword).u64[1] = (from).u64[1] & (mask).u64[1];	\
	पूर्ण जबतक (0)

#घोषणा EF4_OR_OWORD(oword, from, mask)				\
	करो अणु							\
		(oword).u64[0] = (from).u64[0] | (mask).u64[0];	\
		(oword).u64[1] = (from).u64[1] | (mask).u64[1];	\
	पूर्ण जबतक (0)

#घोषणा EF4_INSERT64(min, max, low, high, value)			\
	cpu_to_le64(EF4_INSERT_NATIVE(min, max, low, high, value))

#घोषणा EF4_INSERT32(min, max, low, high, value)			\
	cpu_to_le32(EF4_INSERT_NATIVE(min, max, low, high, value))

#घोषणा EF4_INPLACE_MASK64(min, max, low, high)				\
	EF4_INSERT64(min, max, low, high, EF4_MASK64((high) + 1 - (low)))

#घोषणा EF4_INPLACE_MASK32(min, max, low, high)				\
	EF4_INSERT32(min, max, low, high, EF4_MASK32((high) + 1 - (low)))

#घोषणा EF4_SET_OWORD64(oword, low, high, value) करो अणु			\
	(oword).u64[0] = (((oword).u64[0]				\
			   & ~EF4_INPLACE_MASK64(0,  63, low, high))	\
			  | EF4_INSERT64(0,  63, low, high, value));	\
	(oword).u64[1] = (((oword).u64[1]				\
			   & ~EF4_INPLACE_MASK64(64, 127, low, high))	\
			  | EF4_INSERT64(64, 127, low, high, value));	\
	पूर्ण जबतक (0)

#घोषणा EF4_SET_QWORD64(qword, low, high, value) करो अणु			\
	(qword).u64[0] = (((qword).u64[0]				\
			   & ~EF4_INPLACE_MASK64(0, 63, low, high))	\
			  | EF4_INSERT64(0, 63, low, high, value));	\
	पूर्ण जबतक (0)

#घोषणा EF4_SET_OWORD32(oword, low, high, value) करो अणु			\
	(oword).u32[0] = (((oword).u32[0]				\
			   & ~EF4_INPLACE_MASK32(0, 31, low, high))	\
			  | EF4_INSERT32(0, 31, low, high, value));	\
	(oword).u32[1] = (((oword).u32[1]				\
			   & ~EF4_INPLACE_MASK32(32, 63, low, high))	\
			  | EF4_INSERT32(32, 63, low, high, value));	\
	(oword).u32[2] = (((oword).u32[2]				\
			   & ~EF4_INPLACE_MASK32(64, 95, low, high))	\
			  | EF4_INSERT32(64, 95, low, high, value));	\
	(oword).u32[3] = (((oword).u32[3]				\
			   & ~EF4_INPLACE_MASK32(96, 127, low, high))	\
			  | EF4_INSERT32(96, 127, low, high, value));	\
	पूर्ण जबतक (0)

#घोषणा EF4_SET_QWORD32(qword, low, high, value) करो अणु			\
	(qword).u32[0] = (((qword).u32[0]				\
			   & ~EF4_INPLACE_MASK32(0, 31, low, high))	\
			  | EF4_INSERT32(0, 31, low, high, value));	\
	(qword).u32[1] = (((qword).u32[1]				\
			   & ~EF4_INPLACE_MASK32(32, 63, low, high))	\
			  | EF4_INSERT32(32, 63, low, high, value));	\
	पूर्ण जबतक (0)

#घोषणा EF4_SET_DWORD32(dword, low, high, value) करो अणु			\
	(dword).u32[0] = (((dword).u32[0]				\
			   & ~EF4_INPLACE_MASK32(0, 31, low, high))	\
			  | EF4_INSERT32(0, 31, low, high, value));	\
	पूर्ण जबतक (0)

#घोषणा EF4_SET_OWORD_FIELD64(oword, field, value)			\
	EF4_SET_OWORD64(oword, EF4_LOW_BIT(field),			\
			 EF4_HIGH_BIT(field), value)

#घोषणा EF4_SET_QWORD_FIELD64(qword, field, value)			\
	EF4_SET_QWORD64(qword, EF4_LOW_BIT(field),			\
			 EF4_HIGH_BIT(field), value)

#घोषणा EF4_SET_OWORD_FIELD32(oword, field, value)			\
	EF4_SET_OWORD32(oword, EF4_LOW_BIT(field),			\
			 EF4_HIGH_BIT(field), value)

#घोषणा EF4_SET_QWORD_FIELD32(qword, field, value)			\
	EF4_SET_QWORD32(qword, EF4_LOW_BIT(field),			\
			 EF4_HIGH_BIT(field), value)

#घोषणा EF4_SET_DWORD_FIELD(dword, field, value)			\
	EF4_SET_DWORD32(dword, EF4_LOW_BIT(field),			\
			 EF4_HIGH_BIT(field), value)



#अगर BITS_PER_LONG == 64
#घोषणा EF4_SET_OWORD_FIELD EF4_SET_OWORD_FIELD64
#घोषणा EF4_SET_QWORD_FIELD EF4_SET_QWORD_FIELD64
#अन्यथा
#घोषणा EF4_SET_OWORD_FIELD EF4_SET_OWORD_FIELD32
#घोषणा EF4_SET_QWORD_FIELD EF4_SET_QWORD_FIELD32
#पूर्ण_अगर

/* Used to aव्योम compiler warnings about shअगरt range exceeding width
 * of the data types when dma_addr_t is only 32 bits wide.
 */
#घोषणा DMA_ADDR_T_WIDTH	(8 * माप(dma_addr_t))
#घोषणा EF4_DMA_TYPE_WIDTH(width) \
	(((width) < DMA_ADDR_T_WIDTH) ? (width) : DMA_ADDR_T_WIDTH)


/* Static initialiser */
#घोषणा EF4_OWORD32(a, b, c, d)				\
	अणु .u32 = अणु cpu_to_le32(a), cpu_to_le32(b),	\
		   cpu_to_le32(c), cpu_to_le32(d) पूर्ण पूर्ण

#पूर्ण_अगर /* EF4_BITFIELD_H */
