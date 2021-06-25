<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BITOPS_H
#घोषणा _LINUX_BITOPS_H

#समावेश <यंत्र/types.h>
#समावेश <linux/bits.h>

#समावेश <uapi/linux/kernel.h>

/* Set bits in the first 'n' bytes when loaded from memory */
#अगर_घोषित __LITTLE_ENDIAN
#  define aligned_byte_mask(n) ((1UL << 8*(n))-1)
#अन्यथा
#  define aligned_byte_mask(n) (~0xffUL << (BITS_PER_LONG - 8 - 8*(n)))
#पूर्ण_अगर

#घोषणा BITS_PER_TYPE(type)	(माप(type) * BITS_PER_BYTE)
#घोषणा BITS_TO_LONGS(nr)	__KERNEL_DIV_ROUND_UP(nr, BITS_PER_TYPE(दीर्घ))
#घोषणा BITS_TO_U64(nr)		__KERNEL_DIV_ROUND_UP(nr, BITS_PER_TYPE(u64))
#घोषणा BITS_TO_U32(nr)		__KERNEL_DIV_ROUND_UP(nr, BITS_PER_TYPE(u32))
#घोषणा BITS_TO_BYTES(nr)	__KERNEL_DIV_ROUND_UP(nr, BITS_PER_TYPE(अक्षर))

बाह्य अचिन्हित पूर्णांक __sw_hweight8(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित पूर्णांक __sw_hweight16(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित पूर्णांक __sw_hweight32(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित दीर्घ __sw_hweight64(__u64 w);

/*
 * Include this here because some architectures need generic_ffs/fls in
 * scope
 */
#समावेश <यंत्र/bitops.h>

#घोषणा क्रम_each_set_bit(bit, addr, size) \
	क्रम ((bit) = find_first_bit((addr), (size));		\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

/* same as क्रम_each_set_bit() but use bit as value to start with */
#घोषणा क्रम_each_set_bit_from(bit, addr, size) \
	क्रम ((bit) = find_next_bit((addr), (size), (bit));	\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

#घोषणा क्रम_each_clear_bit(bit, addr, size) \
	क्रम ((bit) = find_first_zero_bit((addr), (size));	\
	     (bit) < (size);					\
	     (bit) = find_next_zero_bit((addr), (size), (bit) + 1))

/* same as क्रम_each_clear_bit() but use bit as value to start with */
#घोषणा क्रम_each_clear_bit_from(bit, addr, size) \
	क्रम ((bit) = find_next_zero_bit((addr), (size), (bit));	\
	     (bit) < (size);					\
	     (bit) = find_next_zero_bit((addr), (size), (bit) + 1))

/**
 * क्रम_each_set_clump8 - iterate over biपंचांगap क्रम each 8-bit clump with set bits
 * @start: bit offset to start search and to store the current iteration offset
 * @clump: location to store copy of current 8-bit clump
 * @bits: biपंचांगap address to base the search on
 * @size: biपंचांगap size in number of bits
 */
#घोषणा क्रम_each_set_clump8(start, clump, bits, size) \
	क्रम ((start) = find_first_clump8(&(clump), (bits), (size)); \
	     (start) < (size); \
	     (start) = find_next_clump8(&(clump), (bits), (size), (start) + 8))

अटल अंतरभूत पूर्णांक get_biपंचांगask_order(अचिन्हित पूर्णांक count)
अणु
	पूर्णांक order;

	order = fls(count);
	वापस order;	/* We could be slightly more clever with -1 here... */
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ hweight_दीर्घ(अचिन्हित दीर्घ w)
अणु
	वापस माप(w) == 4 ? hweight32(w) : hweight64((__u64)w);
पूर्ण

/**
 * rol64 - rotate a 64-bit value left
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u64 rol64(__u64 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << (shअगरt & 63)) | (word >> ((-shअगरt) & 63));
पूर्ण

/**
 * ror64 - rotate a 64-bit value right
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u64 ror64(__u64 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word >> (shअगरt & 63)) | (word << ((-shअगरt) & 63));
पूर्ण

/**
 * rol32 - rotate a 32-bit value left
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u32 rol32(__u32 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << (shअगरt & 31)) | (word >> ((-shअगरt) & 31));
पूर्ण

/**
 * ror32 - rotate a 32-bit value right
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u32 ror32(__u32 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word >> (shअगरt & 31)) | (word << ((-shअगरt) & 31));
पूर्ण

/**
 * rol16 - rotate a 16-bit value left
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u16 rol16(__u16 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << (shअगरt & 15)) | (word >> ((-shअगरt) & 15));
पूर्ण

/**
 * ror16 - rotate a 16-bit value right
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u16 ror16(__u16 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word >> (shअगरt & 15)) | (word << ((-shअगरt) & 15));
पूर्ण

/**
 * rol8 - rotate an 8-bit value left
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u8 rol8(__u8 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << (shअगरt & 7)) | (word >> ((-shअगरt) & 7));
पूर्ण

/**
 * ror8 - rotate an 8-bit value right
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u8 ror8(__u8 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word >> (shअगरt & 7)) | (word << ((-shअगरt) & 7));
पूर्ण

/**
 * sign_extend32 - sign extend a 32-bit value using specअगरied bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<32) to sign bit
 *
 * This is safe to use क्रम 16- and 8-bit types as well.
 */
अटल __always_अंतरभूत __s32 sign_extend32(__u32 value, पूर्णांक index)
अणु
	__u8 shअगरt = 31 - index;
	वापस (__s32)(value << shअगरt) >> shअगरt;
पूर्ण

/**
 * sign_extend64 - sign extend a 64-bit value using specअगरied bit as sign-bit
 * @value: value to sign extend
 * @index: 0 based bit index (0<=index<64) to sign bit
 */
अटल __always_अंतरभूत __s64 sign_extend64(__u64 value, पूर्णांक index)
अणु
	__u8 shअगरt = 63 - index;
	वापस (__s64)(value << shअगरt) >> shअगरt;
पूर्ण

अटल अंतरभूत अचिन्हित fls_दीर्घ(अचिन्हित दीर्घ l)
अणु
	अगर (माप(l) == 4)
		वापस fls(l);
	वापस fls64(l);
पूर्ण

अटल अंतरभूत पूर्णांक get_count_order(अचिन्हित पूर्णांक count)
अणु
	अगर (count == 0)
		वापस -1;

	वापस fls(--count);
पूर्ण

/**
 * get_count_order_दीर्घ - get order after rounding @l up to घातer of 2
 * @l: parameter
 *
 * it is same as get_count_order() but with दीर्घ type parameter
 */
अटल अंतरभूत पूर्णांक get_count_order_दीर्घ(अचिन्हित दीर्घ l)
अणु
	अगर (l == 0UL)
		वापस -1;
	वापस (पूर्णांक)fls_दीर्घ(--l);
पूर्ण

/**
 * __ffs64 - find first set bit in a 64 bit word
 * @word: The 64 bit word
 *
 * On 64 bit arches this is a synonym क्रम __ffs
 * The result is not defined अगर no bits are set, so check that @word
 * is non-zero beक्रमe calling this.
 */
अटल अंतरभूत अचिन्हित दीर्घ __ffs64(u64 word)
अणु
#अगर BITS_PER_LONG == 32
	अगर (((u32)word) == 0UL)
		वापस __ffs((u32)(word >> 32)) + 32;
#या_अगर BITS_PER_LONG != 64
#त्रुटि BITS_PER_LONG not 32 or 64
#पूर्ण_अगर
	वापस __ffs((अचिन्हित दीर्घ)word);
पूर्ण

/**
 * assign_bit - Assign value to a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 * @value: the value to assign
 */
अटल __always_अंतरभूत व्योम assign_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr,
				       bool value)
अणु
	अगर (value)
		set_bit(nr, addr);
	अन्यथा
		clear_bit(nr, addr);
पूर्ण

अटल __always_अंतरभूत व्योम __assign_bit(दीर्घ nr, अस्थिर अचिन्हित दीर्घ *addr,
					 bool value)
अणु
	अगर (value)
		__set_bit(nr, addr);
	अन्यथा
		__clear_bit(nr, addr);
पूर्ण

#अगर_घोषित __KERNEL__

#अगर_अघोषित set_mask_bits
#घोषणा set_mask_bits(ptr, mask, bits)	\
(अणु								\
	स्थिर typeof(*(ptr)) mask__ = (mask), bits__ = (bits);	\
	typeof(*(ptr)) old__, new__;				\
								\
	करो अणु							\
		old__ = READ_ONCE(*(ptr));			\
		new__ = (old__ & ~mask__) | bits__;		\
	पूर्ण जबतक (cmpxchg(ptr, old__, new__) != old__);		\
								\
	old__;							\
पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित bit_clear_unless
#घोषणा bit_clear_unless(ptr, clear, test)	\
(अणु								\
	स्थिर typeof(*(ptr)) clear__ = (clear), test__ = (test);\
	typeof(*(ptr)) old__, new__;				\
								\
	करो अणु							\
		old__ = READ_ONCE(*(ptr));			\
		new__ = old__ & ~clear__;			\
	पूर्ण जबतक (!(old__ & test__) &&				\
		 cmpxchg(ptr, old__, new__) != old__);		\
								\
	!(old__ & test__);					\
पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
