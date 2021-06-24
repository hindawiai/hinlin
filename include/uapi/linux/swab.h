<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SWAB_H
#घोषणा _UAPI_LINUX_SWAB_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/swab.h>

/*
 * casts are necessary क्रम स्थिरants, because we never know how क्रम sure
 * how U/UL/ULL map to __u16, __u32, __u64. At least not in a portable way.
 */
#घोषणा ___स्थिरant_swab16(x) ((__u16)(				\
	(((__u16)(x) & (__u16)0x00ffU) << 8) |			\
	(((__u16)(x) & (__u16)0xff00U) >> 8)))

#घोषणा ___स्थिरant_swab32(x) ((__u32)(				\
	(((__u32)(x) & (__u32)0x000000ffUL) << 24) |		\
	(((__u32)(x) & (__u32)0x0000ff00UL) <<  8) |		\
	(((__u32)(x) & (__u32)0x00ff0000UL) >>  8) |		\
	(((__u32)(x) & (__u32)0xff000000UL) >> 24)))

#घोषणा ___स्थिरant_swab64(x) ((__u64)(				\
	(((__u64)(x) & (__u64)0x00000000000000ffULL) << 56) |	\
	(((__u64)(x) & (__u64)0x000000000000ff00ULL) << 40) |	\
	(((__u64)(x) & (__u64)0x0000000000ff0000ULL) << 24) |	\
	(((__u64)(x) & (__u64)0x00000000ff000000ULL) <<  8) |	\
	(((__u64)(x) & (__u64)0x000000ff00000000ULL) >>  8) |	\
	(((__u64)(x) & (__u64)0x0000ff0000000000ULL) >> 24) |	\
	(((__u64)(x) & (__u64)0x00ff000000000000ULL) >> 40) |	\
	(((__u64)(x) & (__u64)0xff00000000000000ULL) >> 56)))

#घोषणा ___स्थिरant_swahw32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x0000ffffUL) << 16) |		\
	(((__u32)(x) & (__u32)0xffff0000UL) >> 16)))

#घोषणा ___स्थिरant_swahb32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x00ff00ffUL) << 8) |		\
	(((__u32)(x) & (__u32)0xff00ff00UL) >> 8)))

/*
 * Implement the following as अंतरभूतs, but define the पूर्णांकerface using
 * macros to allow स्थिरant folding when possible:
 * ___swab16, ___swab32, ___swab64, ___swahw32, ___swahb32
 */

अटल अंतरभूत __attribute_स्थिर__ __u16 __fswab16(__u16 val)
अणु
#अगर defined (__arch_swab16)
	वापस __arch_swab16(val);
#अन्यथा
	वापस ___स्थिरant_swab16(val);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ __u32 __fswab32(__u32 val)
अणु
#अगर defined(__arch_swab32)
	वापस __arch_swab32(val);
#अन्यथा
	वापस ___स्थिरant_swab32(val);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ __u64 __fswab64(__u64 val)
अणु
#अगर defined (__arch_swab64)
	वापस __arch_swab64(val);
#या_अगर defined(__SWAB_64_THRU_32__)
	__u32 h = val >> 32;
	__u32 l = val & ((1ULL << 32) - 1);
	वापस (((__u64)__fswab32(l)) << 32) | ((__u64)(__fswab32(h)));
#अन्यथा
	वापस ___स्थिरant_swab64(val);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ __u32 __fswahw32(__u32 val)
अणु
#अगर_घोषित __arch_swahw32
	वापस __arch_swahw32(val);
#अन्यथा
	वापस ___स्थिरant_swahw32(val);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ __u32 __fswahb32(__u32 val)
अणु
#अगर_घोषित __arch_swahb32
	वापस __arch_swahb32(val);
#अन्यथा
	वापस ___स्थिरant_swahb32(val);
#पूर्ण_अगर
पूर्ण

/**
 * __swab16 - वापस a byteswapped 16-bit value
 * @x: value to byteswap
 */
#अगर_घोषित __HAVE_BUILTIN_BSWAP16__
#घोषणा __swab16(x) (__u16)__builtin_bswap16((__u16)(x))
#अन्यथा
#घोषणा __swab16(x)				\
	(__builtin_स्थिरant_p((__u16)(x)) ?	\
	___स्थिरant_swab16(x) :			\
	__fswab16(x))
#पूर्ण_अगर

/**
 * __swab32 - वापस a byteswapped 32-bit value
 * @x: value to byteswap
 */
#अगर_घोषित __HAVE_BUILTIN_BSWAP32__
#घोषणा __swab32(x) (__u32)__builtin_bswap32((__u32)(x))
#अन्यथा
#घोषणा __swab32(x)				\
	(__builtin_स्थिरant_p((__u32)(x)) ?	\
	___स्थिरant_swab32(x) :			\
	__fswab32(x))
#पूर्ण_अगर

/**
 * __swab64 - वापस a byteswapped 64-bit value
 * @x: value to byteswap
 */
#अगर_घोषित __HAVE_BUILTIN_BSWAP64__
#घोषणा __swab64(x) (__u64)__builtin_bswap64((__u64)(x))
#अन्यथा
#घोषणा __swab64(x)				\
	(__builtin_स्थिरant_p((__u64)(x)) ?	\
	___स्थिरant_swab64(x) :			\
	__fswab64(x))
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित दीर्घ __swab(स्थिर अचिन्हित दीर्घ y)
अणु
#अगर __BITS_PER_LONG == 64
	वापस __swab64(y);
#अन्यथा /* __BITS_PER_LONG == 32 */
	वापस __swab32(y);
#पूर्ण_अगर
पूर्ण

/**
 * __swahw32 - वापस a word-swapped 32-bit value
 * @x: value to wordswap
 *
 * __swahw32(0x12340000) is 0x00001234
 */
#घोषणा __swahw32(x)				\
	(__builtin_स्थिरant_p((__u32)(x)) ?	\
	___स्थिरant_swahw32(x) :		\
	__fswahw32(x))

/**
 * __swahb32 - वापस a high and low byte-swapped 32-bit value
 * @x: value to byteswap
 *
 * __swahb32(0x12345678) is 0x34127856
 */
#घोषणा __swahb32(x)				\
	(__builtin_स्थिरant_p((__u32)(x)) ?	\
	___स्थिरant_swahb32(x) :		\
	__fswahb32(x))

/**
 * __swab16p - वापस a byteswapped 16-bit value from a poपूर्णांकer
 * @p: poपूर्णांकer to a naturally-aligned 16-bit value
 */
अटल __always_अंतरभूत __u16 __swab16p(स्थिर __u16 *p)
अणु
#अगर_घोषित __arch_swab16p
	वापस __arch_swab16p(p);
#अन्यथा
	वापस __swab16(*p);
#पूर्ण_अगर
पूर्ण

/**
 * __swab32p - वापस a byteswapped 32-bit value from a poपूर्णांकer
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 */
अटल __always_अंतरभूत __u32 __swab32p(स्थिर __u32 *p)
अणु
#अगर_घोषित __arch_swab32p
	वापस __arch_swab32p(p);
#अन्यथा
	वापस __swab32(*p);
#पूर्ण_अगर
पूर्ण

/**
 * __swab64p - वापस a byteswapped 64-bit value from a poपूर्णांकer
 * @p: poपूर्णांकer to a naturally-aligned 64-bit value
 */
अटल __always_अंतरभूत __u64 __swab64p(स्थिर __u64 *p)
अणु
#अगर_घोषित __arch_swab64p
	वापस __arch_swab64p(p);
#अन्यथा
	वापस __swab64(*p);
#पूर्ण_अगर
पूर्ण

/**
 * __swahw32p - वापस a wordswapped 32-bit value from a poपूर्णांकer
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 *
 * See __swahw32() क्रम details of wordswapping.
 */
अटल अंतरभूत __u32 __swahw32p(स्थिर __u32 *p)
अणु
#अगर_घोषित __arch_swahw32p
	वापस __arch_swahw32p(p);
#अन्यथा
	वापस __swahw32(*p);
#पूर्ण_अगर
पूर्ण

/**
 * __swahb32p - वापस a high and low byteswapped 32-bit value from a poपूर्णांकer
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 *
 * See __swahb32() क्रम details of high/low byteswapping.
 */
अटल अंतरभूत __u32 __swahb32p(स्थिर __u32 *p)
अणु
#अगर_घोषित __arch_swahb32p
	वापस __arch_swahb32p(p);
#अन्यथा
	वापस __swahb32(*p);
#पूर्ण_अगर
पूर्ण

/**
 * __swab16s - byteswap a 16-bit value in-place
 * @p: poपूर्णांकer to a naturally-aligned 16-bit value
 */
अटल अंतरभूत व्योम __swab16s(__u16 *p)
अणु
#अगर_घोषित __arch_swab16s
	__arch_swab16s(p);
#अन्यथा
	*p = __swab16p(p);
#पूर्ण_अगर
पूर्ण
/**
 * __swab32s - byteswap a 32-bit value in-place
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 */
अटल __always_अंतरभूत व्योम __swab32s(__u32 *p)
अणु
#अगर_घोषित __arch_swab32s
	__arch_swab32s(p);
#अन्यथा
	*p = __swab32p(p);
#पूर्ण_अगर
पूर्ण

/**
 * __swab64s - byteswap a 64-bit value in-place
 * @p: poपूर्णांकer to a naturally-aligned 64-bit value
 */
अटल __always_अंतरभूत व्योम __swab64s(__u64 *p)
अणु
#अगर_घोषित __arch_swab64s
	__arch_swab64s(p);
#अन्यथा
	*p = __swab64p(p);
#पूर्ण_अगर
पूर्ण

/**
 * __swahw32s - wordswap a 32-bit value in-place
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 *
 * See __swahw32() क्रम details of wordswapping
 */
अटल अंतरभूत व्योम __swahw32s(__u32 *p)
अणु
#अगर_घोषित __arch_swahw32s
	__arch_swahw32s(p);
#अन्यथा
	*p = __swahw32p(p);
#पूर्ण_अगर
पूर्ण

/**
 * __swahb32s - high and low byteswap a 32-bit value in-place
 * @p: poपूर्णांकer to a naturally-aligned 32-bit value
 *
 * See __swahb32() क्रम details of high and low byte swapping
 */
अटल अंतरभूत व्योम __swahb32s(__u32 *p)
अणु
#अगर_घोषित __arch_swahb32s
	__arch_swahb32s(p);
#अन्यथा
	*p = __swahb32p(p);
#पूर्ण_अगर
पूर्ण


#पूर्ण_अगर /* _UAPI_LINUX_SWAB_H */
