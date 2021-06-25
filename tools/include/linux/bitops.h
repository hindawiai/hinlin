<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_BITOPS_H_
#घोषणा _TOOLS_LINUX_BITOPS_H_

#समावेश <यंत्र/types.h>
#समावेश <सीमा.स>
#अगर_अघोषित __WORDSIZE
#घोषणा __WORDSIZE (__SIZखातापूर्ण_LONG__ * 8)
#पूर्ण_अगर

#अगर_अघोषित BITS_PER_LONG
# define BITS_PER_LONG __WORDSIZE
#पूर्ण_अगर
#समावेश <linux/bits.h>
#समावेश <linux/compiler.h>

#घोषणा BITS_PER_TYPE(type)	(माप(type) * BITS_PER_BYTE)
#घोषणा BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_TYPE(दीर्घ))
#घोषणा BITS_TO_U64(nr)		DIV_ROUND_UP(nr, BITS_PER_TYPE(u64))
#घोषणा BITS_TO_U32(nr)		DIV_ROUND_UP(nr, BITS_PER_TYPE(u32))
#घोषणा BITS_TO_BYTES(nr)	DIV_ROUND_UP(nr, BITS_PER_TYPE(अक्षर))

बाह्य अचिन्हित पूर्णांक __sw_hweight8(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित पूर्णांक __sw_hweight16(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित पूर्णांक __sw_hweight32(अचिन्हित पूर्णांक w);
बाह्य अचिन्हित दीर्घ __sw_hweight64(__u64 w);

/*
 * Include this here because some architectures need generic_ffs/fls in
 * scope
 *
 * XXX: this needs to be यंत्र/bitops.h, when we get to per arch optimizations
 */
#समावेश <यंत्र-generic/bitops.h>

#घोषणा क्रम_each_set_bit(bit, addr, size) \
	क्रम ((bit) = find_first_bit((addr), (size));		\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

#घोषणा क्रम_each_clear_bit(bit, addr, size) \
	क्रम ((bit) = find_first_zero_bit((addr), (size));       \
	     (bit) < (size);                                    \
	     (bit) = find_next_zero_bit((addr), (size), (bit) + 1))

/* same as क्रम_each_set_bit() but use bit as value to start with */
#घोषणा क्रम_each_set_bit_from(bit, addr, size) \
	क्रम ((bit) = find_next_bit((addr), (size), (bit));	\
	     (bit) < (size);					\
	     (bit) = find_next_bit((addr), (size), (bit) + 1))

अटल अंतरभूत अचिन्हित दीर्घ hweight_दीर्घ(अचिन्हित दीर्घ w)
अणु
	वापस माप(w) == 4 ? hweight32(w) : hweight64(w);
पूर्ण

अटल अंतरभूत अचिन्हित fls_दीर्घ(अचिन्हित दीर्घ l)
अणु
	अगर (माप(l) == 4)
		वापस fls(l);
	वापस fls64(l);
पूर्ण

/**
 * rol32 - rotate a 32-bit value left
 * @word: value to rotate
 * @shअगरt: bits to roll
 */
अटल अंतरभूत __u32 rol32(__u32 word, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस (word << shअगरt) | (word >> ((-shअगरt) & 31));
पूर्ण

#पूर्ण_अगर
