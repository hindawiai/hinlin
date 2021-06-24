<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
 */

#अगर_अघोषित _LINUX_BITFIELD_H
#घोषणा _LINUX_BITFIELD_H

#समावेश <linux/build_bug.h>
#समावेश <यंत्र/byteorder.h>

/*
 * Bitfield access macros
 *
 * FIELD_अणुGET,PREPपूर्ण macros take as first parameter shअगरted mask
 * from which they extract the base mask and shअगरt amount.
 * Mask must be a compilation समय स्थिरant.
 *
 * Example:
 *
 *  #घोषणा REG_FIELD_A  GENMASK(6, 0)
 *  #घोषणा REG_FIELD_B  BIT(7)
 *  #घोषणा REG_FIELD_C  GENMASK(15, 8)
 *  #घोषणा REG_FIELD_D  GENMASK(31, 16)
 *
 * Get:
 *  a = FIELD_GET(REG_FIELD_A, reg);
 *  b = FIELD_GET(REG_FIELD_B, reg);
 *
 * Set:
 *  reg = FIELD_PREP(REG_FIELD_A, 1) |
 *	  FIELD_PREP(REG_FIELD_B, 0) |
 *	  FIELD_PREP(REG_FIELD_C, c) |
 *	  FIELD_PREP(REG_FIELD_D, 0x40);
 *
 * Modअगरy:
 *  reg &= ~REG_FIELD_C;
 *  reg |= FIELD_PREP(REG_FIELD_C, c);
 */

#घोषणा __bf_shf(x) (__builtin_ffsll(x) - 1)

#घोषणा __BF_FIELD_CHECK(_mask, _reg, _val, _pfx)			\
	(अणु								\
		BUILD_BUG_ON_MSG(!__builtin_स्थिरant_p(_mask),		\
				 _pfx "mask is not constant");		\
		BUILD_BUG_ON_MSG((_mask) == 0, _pfx "mask is zero");	\
		BUILD_BUG_ON_MSG(__builtin_स्थिरant_p(_val) ?		\
				 ~((_mask) >> __bf_shf(_mask)) & (_val) : 0, \
				 _pfx "value too large for the field"); \
		BUILD_BUG_ON_MSG((_mask) > (typeof(_reg))~0ull,		\
				 _pfx "type of reg too small for mask"); \
		__BUILD_BUG_ON_NOT_POWER_OF_2((_mask) +			\
					      (1ULL << __bf_shf(_mask))); \
	पूर्ण)

/**
 * FIELD_MAX() - produce the maximum value representable by a field
 * @_mask: shअगरted mask defining the field's length and position
 *
 * FIELD_MAX() वापसs the maximum value that can be held in the field
 * specअगरied by @_mask.
 */
#घोषणा FIELD_MAX(_mask)						\
	(अणु								\
		__BF_FIELD_CHECK(_mask, 0ULL, 0ULL, "FIELD_MAX: ");	\
		(typeof(_mask))((_mask) >> __bf_shf(_mask));		\
	पूर्ण)

/**
 * FIELD_FIT() - check अगर value fits in the field
 * @_mask: shअगरted mask defining the field's length and position
 * @_val:  value to test against the field
 *
 * Return: true अगर @_val can fit inside @_mask, false अगर @_val is too big.
 */
#घोषणा FIELD_FIT(_mask, _val)						\
	(अणु								\
		__BF_FIELD_CHECK(_mask, 0ULL, 0ULL, "FIELD_FIT: ");	\
		!((((typeof(_mask))_val) << __bf_shf(_mask)) & ~(_mask)); \
	पूर्ण)

/**
 * FIELD_PREP() - prepare a bitfield element
 * @_mask: shअगरted mask defining the field's length and position
 * @_val:  value to put in the field
 *
 * FIELD_PREP() masks and shअगरts up the value.  The result should
 * be combined with other fields of the bitfield using logical OR.
 */
#घोषणा FIELD_PREP(_mask, _val)						\
	(अणु								\
		__BF_FIELD_CHECK(_mask, 0ULL, _val, "FIELD_PREP: ");	\
		((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask);	\
	पूर्ण)

/**
 * FIELD_GET() - extract a bitfield element
 * @_mask: shअगरted mask defining the field's length and position
 * @_reg:  value of entire bitfield
 *
 * FIELD_GET() extracts the field specअगरied by @_mask from the
 * bitfield passed in as @_reg by masking and shअगरting it करोwn.
 */
#घोषणा FIELD_GET(_mask, _reg)						\
	(अणु								\
		__BF_FIELD_CHECK(_mask, _reg, 0U, "FIELD_GET: ");	\
		(typeof(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask));	\
	पूर्ण)

बाह्य व्योम __compileसमय_error("value doesn't fit into mask")
__field_overflow(व्योम);
बाह्य व्योम __compileसमय_error("bad bitfield mask")
__bad_mask(व्योम);
अटल __always_अंतरभूत u64 field_multiplier(u64 field)
अणु
	अगर ((field | (field - 1)) & ((field | (field - 1)) + 1))
		__bad_mask();
	वापस field & -field;
पूर्ण
अटल __always_अंतरभूत u64 field_mask(u64 field)
अणु
	वापस field / field_multiplier(field);
पूर्ण
#घोषणा field_max(field)	((typeof(field))field_mask(field))
#घोषणा ____MAKE_OP(type,base,to,from)					\
अटल __always_अंतरभूत __##type type##_encode_bits(base v, base field)	\
अणु									\
	अगर (__builtin_स्थिरant_p(v) && (v & ~field_mask(field)))	\
		__field_overflow();					\
	वापस to((v & field_mask(field)) * field_multiplier(field));	\
पूर्ण									\
अटल __always_अंतरभूत __##type type##_replace_bits(__##type old,	\
					base val, base field)		\
अणु									\
	वापस (old & ~to(field)) | type##_encode_bits(val, field);	\
पूर्ण									\
अटल __always_अंतरभूत व्योम type##p_replace_bits(__##type *p,		\
					base val, base field)		\
अणु									\
	*p = (*p & ~to(field)) | type##_encode_bits(val, field);	\
पूर्ण									\
अटल __always_अंतरभूत base type##_get_bits(__##type v, base field)	\
अणु									\
	वापस (from(v) & field)/field_multiplier(field);		\
पूर्ण
#घोषणा __MAKE_OP(size)							\
	____MAKE_OP(le##size,u##size,cpu_to_le##size,le##size##_to_cpu)	\
	____MAKE_OP(be##size,u##size,cpu_to_be##size,be##size##_to_cpu)	\
	____MAKE_OP(u##size,u##size,,)
____MAKE_OP(u8,u8,,)
__MAKE_OP(16)
__MAKE_OP(32)
__MAKE_OP(64)
#अघोषित __MAKE_OP
#अघोषित ____MAKE_OP

#पूर्ण_अगर
