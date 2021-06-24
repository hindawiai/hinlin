<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_LE_H_
#घोषणा _ASM_GENERIC_BITOPS_LE_H_

#समावेश <यंत्र-generic/bitops/find.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/swab.h>

#अगर defined(__LITTLE_ENDIAN)

#घोषणा BITOP_LE_SWIZZLE	0

अटल अंतरभूत अचिन्हित दीर्घ find_next_zero_bit_le(स्थिर व्योम *addr,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	वापस find_next_zero_bit(addr, size, offset);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_next_bit_le(स्थिर व्योम *addr,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	वापस find_next_bit(addr, size, offset);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_first_zero_bit_le(स्थिर व्योम *addr,
		अचिन्हित दीर्घ size)
अणु
	वापस find_first_zero_bit(addr, size);
पूर्ण

#या_अगर defined(__BIG_ENDIAN)

#घोषणा BITOP_LE_SWIZZLE	((BITS_PER_LONG-1) & ~0x7)

#अगर_अघोषित find_next_zero_bit_le
अटल अंतरभूत
अचिन्हित दीर्घ find_next_zero_bit_le(स्थिर व्योम *addr, अचिन्हित
		दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val = *(स्थिर अचिन्हित दीर्घ *)addr;

		अगर (unlikely(offset >= size))
			वापस size;

		val = swab(val) | ~GENMASK(size - 1, offset);
		वापस val == ~0UL ? size : ffz(val);
	पूर्ण

	वापस _find_next_bit(addr, शून्य, size, offset, ~0UL, 1);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित find_next_bit_le
अटल अंतरभूत
अचिन्हित दीर्घ find_next_bit_le(स्थिर व्योम *addr, अचिन्हित
		दीर्घ size, अचिन्हित दीर्घ offset)
अणु
	अगर (small_स्थिर_nbits(size)) अणु
		अचिन्हित दीर्घ val = *(स्थिर अचिन्हित दीर्घ *)addr;

		अगर (unlikely(offset >= size))
			वापस size;

		val = swab(val) & GENMASK(size - 1, offset);
		वापस val ? __ffs(val) : size;
	पूर्ण

	वापस _find_next_bit(addr, शून्य, size, offset, 0UL, 1);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित find_first_zero_bit_le
#घोषणा find_first_zero_bit_le(addr, size) \
	find_next_zero_bit_le((addr), (size), 0)
#पूर्ण_अगर

#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक test_bit_le(पूर्णांक nr, स्थिर व्योम *addr)
अणु
	वापस test_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत व्योम set_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	set_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत व्योम clear_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	clear_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत व्योम __set_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	__set_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत व्योम __clear_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	__clear_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	वापस test_and_set_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	वापस test_and_clear_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __test_and_set_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	वापस __test_and_set_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

अटल अंतरभूत पूर्णांक __test_and_clear_bit_le(पूर्णांक nr, व्योम *addr)
अणु
	वापस __test_and_clear_bit(nr ^ BITOP_LE_SWIZZLE, addr);
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_LE_H_ */
