<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_MTE_KASAN_H
#घोषणा __ASM_MTE_KASAN_H

#समावेश <यंत्र/mte-def.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_ARM64_MTE

/*
 * These functions are meant to be only used from KASAN runसमय through
 * the arch_*() पूर्णांकerface defined in यंत्र/memory.h.
 * These functions करोn't include प्रणाली_supports_mte() checks,
 * as KASAN only calls them when MTE is supported and enabled.
 */

अटल अंतरभूत u8 mte_get_ptr_tag(व्योम *ptr)
अणु
	/* Note: The क्रमmat of KASAN tags is 0xF<x> */
	u8 tag = 0xF0 | (u8)(((u64)(ptr)) >> MTE_TAG_SHIFT);

	वापस tag;
पूर्ण

/* Get allocation tag क्रम the address. */
अटल अंतरभूत u8 mte_get_mem_tag(व्योम *addr)
अणु
	यंत्र(__MTE_PREAMBLE "ldg %0, [%0]"
		: "+r" (addr));

	वापस mte_get_ptr_tag(addr);
पूर्ण

/* Generate a अक्रमom tag. */
अटल अंतरभूत u8 mte_get_अक्रमom_tag(व्योम)
अणु
	व्योम *addr;

	यंत्र(__MTE_PREAMBLE "irg %0, %0"
		: "=r" (addr));

	वापस mte_get_ptr_tag(addr);
पूर्ण

/*
 * Assign allocation tags क्रम a region of memory based on the poपूर्णांकer tag.
 * Note: The address must be non-शून्य and MTE_GRANULE_SIZE aligned and
 * size must be non-zero and MTE_GRANULE_SIZE aligned.
 */
अटल अंतरभूत व्योम mte_set_mem_tag_range(व्योम *addr, माप_प्रकार size,
						u8 tag, bool init)
अणु
	u64 curr, end;

	अगर (!size)
		वापस;

	curr = (u64)__tag_set(addr, tag);
	end = curr + size;

	/*
	 * 'asm volatile' is required to prevent the compiler to move
	 * the statement outside of the loop.
	 */
	अगर (init) अणु
		करो अणु
			यंत्र अस्थिर(__MTE_PREAMBLE "stzg %0, [%0]"
				     :
				     : "r" (curr)
				     : "memory");
			curr += MTE_GRANULE_SIZE;
		पूर्ण जबतक (curr != end);
	पूर्ण अन्यथा अणु
		करो अणु
			यंत्र अस्थिर(__MTE_PREAMBLE "stg %0, [%0]"
				     :
				     : "r" (curr)
				     : "memory");
			curr += MTE_GRANULE_SIZE;
		पूर्ण जबतक (curr != end);
	पूर्ण
पूर्ण

व्योम mte_enable_kernel_sync(व्योम);
व्योम mte_enable_kernel_async(व्योम);
व्योम mte_init_tags(u64 max_tag);

व्योम mte_set_report_once(bool state);
bool mte_report_once(व्योम);

#अन्यथा /* CONFIG_ARM64_MTE */

अटल अंतरभूत u8 mte_get_ptr_tag(व्योम *ptr)
अणु
	वापस 0xFF;
पूर्ण

अटल अंतरभूत u8 mte_get_mem_tag(व्योम *addr)
अणु
	वापस 0xFF;
पूर्ण

अटल अंतरभूत u8 mte_get_अक्रमom_tag(व्योम)
अणु
	वापस 0xFF;
पूर्ण

अटल अंतरभूत व्योम mte_set_mem_tag_range(व्योम *addr, माप_प्रकार size,
						u8 tag, bool init)
अणु
पूर्ण

अटल अंतरभूत व्योम mte_enable_kernel_sync(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mte_enable_kernel_async(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम mte_init_tags(u64 max_tag)
अणु
पूर्ण

अटल अंतरभूत व्योम mte_set_report_once(bool state)
अणु
पूर्ण

अटल अंतरभूत bool mte_report_once(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_ARM64_MTE */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_MTE_KASAN_H  */
