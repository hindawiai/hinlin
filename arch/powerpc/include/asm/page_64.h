<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PAGE_64_H
#घोषणा _ASM_POWERPC_PAGE_64_H

/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 */

#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * We always define HW_PAGE_SHIFT to 12 as use of 64K pages reमुख्यs Linux
 * specअगरic, every notion of page number shared with the firmware, TCEs,
 * iommu, etc... still uses a page size of 4K.
 */
#घोषणा HW_PAGE_SHIFT		12
#घोषणा HW_PAGE_SIZE		(ASM_CONST(1) << HW_PAGE_SHIFT)
#घोषणा HW_PAGE_MASK		(~(HW_PAGE_SIZE-1))

/*
 * PAGE_FACTOR is the number of bits factor between PAGE_SHIFT and
 * HW_PAGE_SHIFT, that is 4K pages.
 */
#घोषणा PAGE_FACTOR		(PAGE_SHIFT - HW_PAGE_SHIFT)

/* Segment size; normal 256M segments */
#घोषणा SID_SHIFT		28
#घोषणा SID_MASK		ASM_CONST(0xfffffffff)
#घोषणा ESID_MASK		0xfffffffff0000000UL
#घोषणा GET_ESID(x)		(((x) >> SID_SHIFT) & SID_MASK)

/* 1T segments */
#घोषणा SID_SHIFT_1T		40
#घोषणा SID_MASK_1T		0xffffffUL
#घोषणा ESID_MASK_1T		0xffffff0000000000UL
#घोषणा GET_ESID_1T(x)		(((x) >> SID_SHIFT_1T) & SID_MASK_1T)

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/cache.h>

प्रकार अचिन्हित दीर्घ pte_basic_t;

अटल अंतरभूत व्योम clear_page(व्योम *addr)
अणु
	अचिन्हित दीर्घ iterations;
	अचिन्हित दीर्घ onex, twox, fourx, eightx;

	iterations = ppc64_caches.l1d.blocks_per_page / 8;

	/*
	 * Some verisions of gcc use multiply inकाष्ठाions to
	 * calculate the offsets so lets give it a hand to
	 * करो better.
	 */
	onex = ppc64_caches.l1d.block_size;
	twox = onex << 1;
	fourx = onex << 2;
	eightx = onex << 3;

	यंत्र अस्थिर(
	"mtctr	%1	# clear_page\न\
	.balign	16\न\
1:	dcbz	0,%0\न\
	dcbz	%3,%0\न\
	dcbz	%4,%0\न\
	dcbz	%5,%0\न\
	dcbz	%6,%0\न\
	dcbz	%7,%0\न\
	dcbz	%8,%0\न\
	dcbz	%9,%0\न\
	add	%0,%0,%10\न\
	bdnz+	1b"
	: "=&r" (addr)
	: "r" (iterations), "0" (addr), "b" (onex), "b" (twox),
		"b" (twox+onex), "b" (fourx), "b" (fourx+onex),
		"b" (twox+fourx), "b" (eightx-onex), "r" (eightx)
	: "ctr", "memory");
पूर्ण

बाह्य व्योम copy_page(व्योम *to, व्योम *from);

/* Log 2 of page table size */
बाह्य u64 ppc64_pft_size;

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा VM_DATA_DEFAULT_FLAGS \
	(is_32bit_task() ? \
	 VM_DATA_DEFAULT_FLAGS32 : VM_DATA_DEFAULT_FLAGS64)

/*
 * This is the शेष अगर a program करोesn't have a PT_GNU_STACK
 * program header entry. The PPC64 ELF ABI has a non executable stack
 * stack by शेष, so in the असलence of a PT_GNU_STACK program header
 * we turn execute permission off.
 */
#घोषणा VM_STACK_DEFAULT_FLAGS32	VM_DATA_FLAGS_EXEC
#घोषणा VM_STACK_DEFAULT_FLAGS64	VM_DATA_FLAGS_NON_EXEC

#घोषणा VM_STACK_DEFAULT_FLAGS \
	(is_32bit_task() ? \
	 VM_STACK_DEFAULT_FLAGS32 : VM_STACK_DEFAULT_FLAGS64)

#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _ASM_POWERPC_PAGE_64_H */
