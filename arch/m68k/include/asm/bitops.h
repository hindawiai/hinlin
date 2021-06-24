<शैली गुरु>
#अगर_अघोषित _M68K_BITOPS_H
#घोषणा _M68K_BITOPS_H
/*
 * Copyright 1992, Linus Torvalds.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

/*
 *	Bit access functions vary across the ColdFire and 68k families.
 *	So we will अवरोध them out here, and then macro in the ones we want.
 *
 *	ColdFire - supports standard bset/bclr/bchg with रेजिस्टर opeअक्रम only
 *	68000    - supports standard bset/bclr/bchg with memory opeअक्रम
 *	>= 68020 - also supports the bfset/bfclr/bfchg inकाष्ठाions
 *
 *	Although it is possible to use only the bset/bclr/bchg with रेजिस्टर
 *	opeअक्रमs on all platक्रमms you end up with larger generated code.
 *	So we use the best क्रमm possible on a given platक्रमm.
 */

अटल अंतरभूत व्योम bset_reg_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bset %1,(%0)"
		:
		: "a" (p), "di" (nr & 7)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम bset_mem_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bset %1,%0"
		: "+m" (*p)
		: "di" (nr & 7));
पूर्ण

अटल अंतरभूत व्योम bfset_mem_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	__यंत्र__ __अस्थिर__ ("bfset %1{%0:#1}"
		:
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	set_bit(nr, vaddr)	bset_reg_set_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	set_bit(nr, vaddr)	bset_mem_set_bit(nr, vaddr)
#अन्यथा
#घोषणा set_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
				bset_mem_set_bit(nr, vaddr) : \
				bfset_mem_set_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __set_bit(nr, vaddr)	set_bit(nr, vaddr)


अटल अंतरभूत व्योम bclr_reg_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bclr %1,(%0)"
		:
		: "a" (p), "di" (nr & 7)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम bclr_mem_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bclr %1,%0"
		: "+m" (*p)
		: "di" (nr & 7));
पूर्ण

अटल अंतरभूत व्योम bfclr_mem_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	__यंत्र__ __अस्थिर__ ("bfclr %1{%0:#1}"
		:
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	clear_bit(nr, vaddr)	bclr_reg_clear_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	clear_bit(nr, vaddr)	bclr_mem_clear_bit(nr, vaddr)
#अन्यथा
#घोषणा clear_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
				bclr_mem_clear_bit(nr, vaddr) : \
				bfclr_mem_clear_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __clear_bit(nr, vaddr)	clear_bit(nr, vaddr)


अटल अंतरभूत व्योम bchg_reg_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bchg %1,(%0)"
		:
		: "a" (p), "di" (nr & 7)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम bchg_mem_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;

	__यंत्र__ __अस्थिर__ ("bchg %1,%0"
		: "+m" (*p)
		: "di" (nr & 7));
पूर्ण

अटल अंतरभूत व्योम bfchg_mem_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	__यंत्र__ __अस्थिर__ ("bfchg %1{%0:#1}"
		:
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	change_bit(nr, vaddr)	bchg_reg_change_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	change_bit(nr, vaddr)	bchg_mem_change_bit(nr, vaddr)
#अन्यथा
#घोषणा change_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
				bchg_mem_change_bit(nr, vaddr) : \
				bfchg_mem_change_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __change_bit(nr, vaddr)	change_bit(nr, vaddr)


अटल अंतरभूत पूर्णांक test_bit(पूर्णांक nr, स्थिर अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	वापस (vaddr[nr >> 5] & (1UL << (nr & 31))) != 0;
पूर्ण


अटल अंतरभूत पूर्णांक bset_reg_test_and_set_bit(पूर्णांक nr,
					    अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bset %2,(%1); sne %0"
		: "=d" (retval)
		: "a" (p), "di" (nr & 7)
		: "memory");
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bset_mem_test_and_set_bit(पूर्णांक nr,
					    अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bset %2,%1; sne %0"
		: "=d" (retval), "+m" (*p)
		: "di" (nr & 7));
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bfset_mem_test_and_set_bit(पूर्णांक nr,
					     अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bfset %2{%1:#1}; sne %0"
		: "=d" (retval)
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
	वापस retval;
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	test_and_set_bit(nr, vaddr)	bset_reg_test_and_set_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	test_and_set_bit(nr, vaddr)	bset_mem_test_and_set_bit(nr, vaddr)
#अन्यथा
#घोषणा test_and_set_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
					bset_mem_test_and_set_bit(nr, vaddr) : \
					bfset_mem_test_and_set_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __test_and_set_bit(nr, vaddr)	test_and_set_bit(nr, vaddr)


अटल अंतरभूत पूर्णांक bclr_reg_test_and_clear_bit(पूर्णांक nr,
					      अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bclr %2,(%1); sne %0"
		: "=d" (retval)
		: "a" (p), "di" (nr & 7)
		: "memory");
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bclr_mem_test_and_clear_bit(पूर्णांक nr,
					      अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bclr %2,%1; sne %0"
		: "=d" (retval), "+m" (*p)
		: "di" (nr & 7));
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bfclr_mem_test_and_clear_bit(पूर्णांक nr,
					       अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bfclr %2{%1:#1}; sne %0"
		: "=d" (retval)
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
	वापस retval;
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	test_and_clear_bit(nr, vaddr)	bclr_reg_test_and_clear_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	test_and_clear_bit(nr, vaddr)	bclr_mem_test_and_clear_bit(nr, vaddr)
#अन्यथा
#घोषणा test_and_clear_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
					bclr_mem_test_and_clear_bit(nr, vaddr) : \
					bfclr_mem_test_and_clear_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __test_and_clear_bit(nr, vaddr)	test_and_clear_bit(nr, vaddr)


अटल अंतरभूत पूर्णांक bchg_reg_test_and_change_bit(पूर्णांक nr,
					       अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bchg %2,(%1); sne %0"
		: "=d" (retval)
		: "a" (p), "di" (nr & 7)
		: "memory");
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bchg_mem_test_and_change_bit(पूर्णांक nr,
					       अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर *p = (अक्षर *)vaddr + (nr ^ 31) / 8;
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bchg %2,%1; sne %0"
		: "=d" (retval), "+m" (*p)
		: "di" (nr & 7));
	वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक bfchg_mem_test_and_change_bit(पूर्णांक nr,
						अस्थिर अचिन्हित दीर्घ *vaddr)
अणु
	अक्षर retval;

	__यंत्र__ __अस्थिर__ ("bfchg %2{%1:#1}; sne %0"
		: "=d" (retval)
		: "d" (nr ^ 31), "o" (*vaddr)
		: "memory");
	वापस retval;
पूर्ण

#अगर defined(CONFIG_COLDFIRE)
#घोषणा	test_and_change_bit(nr, vaddr)	bchg_reg_test_and_change_bit(nr, vaddr)
#या_अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#घोषणा	test_and_change_bit(nr, vaddr)	bchg_mem_test_and_change_bit(nr, vaddr)
#अन्यथा
#घोषणा test_and_change_bit(nr, vaddr)	(__builtin_स्थिरant_p(nr) ? \
					bchg_mem_test_and_change_bit(nr, vaddr) : \
					bfchg_mem_test_and_change_bit(nr, vaddr))
#पूर्ण_अगर

#घोषणा __test_and_change_bit(nr, vaddr) test_and_change_bit(nr, vaddr)


/*
 *	The true 68020 and more advanced processors support the "bfffo"
 *	inकाष्ठाion क्रम finding bits. ColdFire and simple 68000 parts
 *	(including CPU32) करो not support this. They simply use the generic
 *	functions.
 */
#अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)
#समावेश <यंत्र-generic/bitops/ffz.h>
#अन्यथा

अटल अंतरभूत पूर्णांक find_first_zero_bit(स्थिर अचिन्हित दीर्घ *vaddr,
				      अचिन्हित size)
अणु
	स्थिर अचिन्हित दीर्घ *p = vaddr;
	पूर्णांक res = 32;
	अचिन्हित पूर्णांक words;
	अचिन्हित दीर्घ num;

	अगर (!size)
		वापस 0;

	words = (size + 31) >> 5;
	जबतक (!(num = ~*p++)) अणु
		अगर (!--words)
			जाओ out;
	पूर्ण

	__यंत्र__ __अस्थिर__ ("bfffo %1{#0,#0},%0"
			      : "=d" (res) : "d" (num & -num));
	res ^= 31;
out:
	res += ((दीर्घ)p - (दीर्घ)vaddr - 4) * 8;
	वापस res < size ? res : size;
पूर्ण
#घोषणा find_first_zero_bit find_first_zero_bit

अटल अंतरभूत पूर्णांक find_next_zero_bit(स्थिर अचिन्हित दीर्घ *vaddr, पूर्णांक size,
				     पूर्णांक offset)
अणु
	स्थिर अचिन्हित दीर्घ *p = vaddr + (offset >> 5);
	पूर्णांक bit = offset & 31UL, res;

	अगर (offset >= size)
		वापस size;

	अगर (bit) अणु
		अचिन्हित दीर्घ num = ~*p++ & (~0UL << bit);
		offset -= bit;

		/* Look क्रम zero in first दीर्घword */
		__यंत्र__ __अस्थिर__ ("bfffo %1{#0,#0},%0"
				      : "=d" (res) : "d" (num & -num));
		अगर (res < 32) अणु
			offset += res ^ 31;
			वापस offset < size ? offset : size;
		पूर्ण
		offset += 32;

		अगर (offset >= size)
			वापस size;
	पूर्ण
	/* No zero yet, search reमुख्यing full bytes क्रम a zero */
	वापस offset + find_first_zero_bit(p, size - offset);
पूर्ण
#घोषणा find_next_zero_bit find_next_zero_bit

अटल अंतरभूत पूर्णांक find_first_bit(स्थिर अचिन्हित दीर्घ *vaddr, अचिन्हित size)
अणु
	स्थिर अचिन्हित दीर्घ *p = vaddr;
	पूर्णांक res = 32;
	अचिन्हित पूर्णांक words;
	अचिन्हित दीर्घ num;

	अगर (!size)
		वापस 0;

	words = (size + 31) >> 5;
	जबतक (!(num = *p++)) अणु
		अगर (!--words)
			जाओ out;
	पूर्ण

	__यंत्र__ __अस्थिर__ ("bfffo %1{#0,#0},%0"
			      : "=d" (res) : "d" (num & -num));
	res ^= 31;
out:
	res += ((दीर्घ)p - (दीर्घ)vaddr - 4) * 8;
	वापस res < size ? res : size;
पूर्ण
#घोषणा find_first_bit find_first_bit

अटल अंतरभूत पूर्णांक find_next_bit(स्थिर अचिन्हित दीर्घ *vaddr, पूर्णांक size,
				पूर्णांक offset)
अणु
	स्थिर अचिन्हित दीर्घ *p = vaddr + (offset >> 5);
	पूर्णांक bit = offset & 31UL, res;

	अगर (offset >= size)
		वापस size;

	अगर (bit) अणु
		अचिन्हित दीर्घ num = *p++ & (~0UL << bit);
		offset -= bit;

		/* Look क्रम one in first दीर्घword */
		__यंत्र__ __अस्थिर__ ("bfffo %1{#0,#0},%0"
				      : "=d" (res) : "d" (num & -num));
		अगर (res < 32) अणु
			offset += res ^ 31;
			वापस offset < size ? offset : size;
		पूर्ण
		offset += 32;

		अगर (offset >= size)
			वापस size;
	पूर्ण
	/* No one yet, search reमुख्यing full bytes क्रम a one */
	वापस offset + find_first_bit(p, size - offset);
पूर्ण
#घोषणा find_next_bit find_next_bit

/*
 * ffz = Find First Zero in word. Undefined अगर no zero exists,
 * so code should check against ~0UL first..
 */
अटल अंतरभूत अचिन्हित दीर्घ ffz(अचिन्हित दीर्घ word)
अणु
	पूर्णांक res;

	__यंत्र__ __अस्थिर__ ("bfffo %1{#0,#0},%0"
			      : "=d" (res) : "d" (~word & -~word));
	वापस res ^ 31;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित __KERNEL__

#अगर defined(CONFIG_CPU_HAS_NO_BITFIELDS)

/*
 *	The newer ColdFire family members support a "bitrev" inकाष्ठाion
 *	and we can use that to implement a fast ffs. Older Coldfire parts,
 *	and normal 68000 parts करोn't have anything special, so we use the
 *	generic functions क्रम those.
 */
#अगर (defined(__mcfisaaplus__) || defined(__mcfisac__)) && \
	!defined(CONFIG_M68000) && !defined(CONFIG_MCPU32)
अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	__यंत्र__ __अस्थिर__ ("bitrev %0; ff1 %0"
		: "=d" (x)
		: "0" (x));
	वापस x;
पूर्ण

अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	अगर (!x)
		वापस 0;
	वापस __ffs(x) + 1;
पूर्ण

#अन्यथा
#समावेश <यंत्र-generic/bitops/ffs.h>
#समावेश <यंत्र-generic/bitops/__ffs.h>
#पूर्ण_अगर

#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/__fls.h>

#अन्यथा

/*
 *	ffs: find first bit set. This is defined the same way as
 *	the libc and compiler builtin ffs routines, thereक्रमe
 *	dअगरfers in spirit from the above ffz (man ffs).
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	पूर्णांक cnt;

	__यंत्र__ ("bfffo %1{#0:#0},%0"
		: "=d" (cnt)
		: "dm" (x & -x));
	वापस 32 - cnt;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ x)
अणु
	वापस ffs(x) - 1;
पूर्ण

/*
 *	fls: find last bit set.
 */
अटल अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक cnt;

	__यंत्र__ ("bfffo %1{#0,#0},%0"
		: "=d" (cnt)
		: "dm" (x));
	वापस 32 - cnt;
पूर्ण

अटल अंतरभूत पूर्णांक __fls(पूर्णांक x)
अणु
	वापस fls(x) - 1;
पूर्ण

#पूर्ण_अगर

/* Simple test-and-set bit locks */
#घोषणा test_and_set_bit_lock	test_and_set_bit
#घोषणा clear_bit_unlock	clear_bit
#घोषणा __clear_bit_unlock	clear_bit_unlock

#समावेश <यंत्र-generic/bitops/ext2-atomic.h>
#समावेश <यंत्र-generic/bitops/fls64.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/le.h>
#पूर्ण_अगर /* __KERNEL__ */

#समावेश <यंत्र-generic/bitops/find.h>

#पूर्ण_अगर /* _M68K_BITOPS_H */
