<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2020, Mellanox Technologies inc.  All rights reserved.
 */
#अगर_अघोषित _IBA_DEFS_H_
#घोषणा _IBA_DEFS_H_

#समावेश <linux/kernel.h>
#समावेश <linux/bitfield.h>
#समावेश <यंत्र/unaligned.h>

अटल अंतरभूत u32 _iba_get8(स्थिर u8 *ptr)
अणु
	वापस *ptr;
पूर्ण

अटल अंतरभूत व्योम _iba_set8(u8 *ptr, u32 mask, u32 prep_value)
अणु
	*ptr = (*ptr & ~mask) | prep_value;
पूर्ण

अटल अंतरभूत u16 _iba_get16(स्थिर __be16 *ptr)
अणु
	वापस be16_to_cpu(*ptr);
पूर्ण

अटल अंतरभूत व्योम _iba_set16(__be16 *ptr, u16 mask, u16 prep_value)
अणु
	*ptr = cpu_to_be16((be16_to_cpu(*ptr) & ~mask) | prep_value);
पूर्ण

अटल अंतरभूत u32 _iba_get32(स्थिर __be32 *ptr)
अणु
	वापस be32_to_cpu(*ptr);
पूर्ण

अटल अंतरभूत व्योम _iba_set32(__be32 *ptr, u32 mask, u32 prep_value)
अणु
	*ptr = cpu_to_be32((be32_to_cpu(*ptr) & ~mask) | prep_value);
पूर्ण

अटल अंतरभूत u64 _iba_get64(स्थिर __be64 *ptr)
अणु
	/*
	 * The mads are स्थिरructed so that 32 bit and smaller are naturally
	 * aligned, everything larger has a max alignment of 4 bytes.
	 */
	वापस be64_to_cpu(get_unaligned(ptr));
पूर्ण

अटल अंतरभूत व्योम _iba_set64(__be64 *ptr, u64 mask, u64 prep_value)
अणु
	put_unaligned(cpu_to_be64((_iba_get64(ptr) & ~mask) | prep_value), ptr);
पूर्ण

#घोषणा _IBA_SET(field_काष्ठा, field_offset, field_mask, num_bits, ptr, value) \
	(अणु                                                                     \
		field_काष्ठा *_ptr = ptr;                                      \
		_iba_set##num_bits((व्योम *)_ptr + (field_offset), field_mask,  \
				   FIELD_PREP(field_mask, value));             \
	पूर्ण)
#घोषणा IBA_SET(field, ptr, value) _IBA_SET(field, ptr, value)

#घोषणा _IBA_GET_MEM_PTR(field_काष्ठा, field_offset, type, num_bits, ptr)      \
	(अणु                                                                     \
		field_काष्ठा *_ptr = ptr;                                      \
		(type *)((व्योम *)_ptr + (field_offset));                       \
	पूर्ण)
#घोषणा IBA_GET_MEM_PTR(field, ptr) _IBA_GET_MEM_PTR(field, ptr)

/* FIXME: A set should always set the entire field, meaning we should zero the trailing bytes */
#घोषणा _IBA_SET_MEM(field_काष्ठा, field_offset, type, num_bits, ptr, in,      \
		     bytes)                                                    \
	(अणु                                                                     \
		स्थिर type *_in_ptr = in;                                      \
		WARN_ON(bytes * 8 > num_bits);                                 \
		अगर (in && bytes)                                               \
			स_नकल(_IBA_GET_MEM_PTR(field_काष्ठा, field_offset,    \
						type, num_bits, ptr),          \
			       _in_ptr, bytes);                                \
	पूर्ण)
#घोषणा IBA_SET_MEM(field, ptr, in, bytes) _IBA_SET_MEM(field, ptr, in, bytes)

#घोषणा _IBA_GET(field_काष्ठा, field_offset, field_mask, num_bits, ptr)        \
	(अणु                                                                     \
		स्थिर field_काष्ठा *_ptr = ptr;                                \
		(u##num_bits) FIELD_GET(                                       \
			field_mask, _iba_get##num_bits((स्थिर व्योम *)_ptr +    \
						       (field_offset)));       \
	पूर्ण)
#घोषणा IBA_GET(field, ptr) _IBA_GET(field, ptr)

#घोषणा _IBA_GET_MEM(field_काष्ठा, field_offset, type, num_bits, ptr, out,     \
		     bytes)                                                    \
	(अणु                                                                     \
		type *_out_ptr = out;                                          \
		WARN_ON(bytes * 8 > num_bits);                                 \
		अगर (out && bytes)                                              \
			स_नकल(_out_ptr,                                       \
			       _IBA_GET_MEM_PTR(field_काष्ठा, field_offset,    \
						type, num_bits, ptr),          \
			       bytes);                                         \
	पूर्ण)
#घोषणा IBA_GET_MEM(field, ptr, out, bytes) _IBA_GET_MEM(field, ptr, out, bytes)

/*
 * The generated list becomes the parameters to the macros, the order is:
 *  - काष्ठा this applies to
 *  - starting offset of the max
 *  - GENMASK or GENMASK_ULL in CPU order
 *  - The width of data the mask operations should work on, in bits
 */

/*
 * Extraction using a tabular description like table 106. bit_offset is from
 * the Byte[Bit] notation.
 */
#घोषणा IBA_FIELD_BLOC(field_काष्ठा, byte_offset, bit_offset, num_bits)        \
	field_काष्ठा, byte_offset,                                             \
		GENMASK(7 - (bit_offset), 7 - (bit_offset) - (num_bits - 1)),  \
		8
#घोषणा IBA_FIELD8_LOC(field_काष्ठा, byte_offset, num_bits)                    \
	IBA_FIELD_BLOC(field_काष्ठा, byte_offset, 0, num_bits)

#घोषणा IBA_FIELD16_LOC(field_काष्ठा, byte_offset, num_bits)                   \
	field_काष्ठा, (byte_offset)&0xFFFE,                                    \
		GENMASK(15 - (((byte_offset) % 2) * 8),                        \
			15 - (((byte_offset) % 2) * 8) - (num_bits - 1)),      \
		16

#घोषणा IBA_FIELD32_LOC(field_काष्ठा, byte_offset, num_bits)                   \
	field_काष्ठा, (byte_offset)&0xFFFC,                                    \
		GENMASK(31 - (((byte_offset) % 4) * 8),                        \
			31 - (((byte_offset) % 4) * 8) - (num_bits - 1)),      \
		32

#घोषणा IBA_FIELD64_LOC(field_काष्ठा, byte_offset)                             \
	field_काष्ठा, byte_offset, GENMASK_ULL(63, 0), 64
/*
 * In IBTA spec, everything that is more than 64bits is multiple
 * of bytes without leftover bits.
 */
#घोषणा IBA_FIELD_MLOC(field_काष्ठा, byte_offset, num_bits, type)              \
	field_काष्ठा, byte_offset, type, num_bits

#पूर्ण_अगर /* _IBA_DEFS_H_ */
