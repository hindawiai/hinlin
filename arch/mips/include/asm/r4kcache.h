<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Inline assembly cache operations.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997 - 2002 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 2004 Ralf Baechle (ralf@linux-mips.org)
 */
#अगर_अघोषित _ASM_R4KCACHE_H
#घोषणा _ASM_R4KCACHE_H

#समावेश <linux/stringअगरy.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्र-eva.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/unroll.h>

बाह्य व्योम (*r4k_blast_dcache)(व्योम);
बाह्य व्योम (*r4k_blast_icache)(व्योम);

/*
 * This macro वापस a properly sign-extended address suitable as base address
 * क्रम indexed cache operations.  Two issues here:
 *
 *  - The MIPS32 and MIPS64 specs permit an implementation to directly derive
 *    the index bits from the भव address.	This अवरोधs with tradition
 *    set by the R4000.	 To keep unpleasant surprises from happening we pick
 *    an address in KSEG0 / CKSEG0.
 *  - We need a properly sign extended address क्रम 64-bit code.	 To get away
 *    without अगरdefs we let the compiler करो it by a type cast.
 */
#घोषणा INDEX_BASE	CKSEG0

#घोषणा _cache_op(insn, op, addr)					\
	__यंत्र__ __अस्थिर__(						\
	"	.set	push					\n"	\
	"	.set	noreorder				\n"	\
	"	.set "MIPS_ISA_ARCH_LEVEL"			\n"	\
	"	" insn("%0", "%1") "				\n"	\
	"	.set	pop					\n"	\
	:								\
	: "i" (op), "R" (*(अचिन्हित अक्षर *)(addr)))

#घोषणा cache_op(op, addr)						\
	_cache_op(kernel_cache, op, addr)

अटल अंतरभूत व्योम flush_icache_line_indexed(अचिन्हित दीर्घ addr)
अणु
	cache_op(Index_Invalidate_I, addr);
पूर्ण

अटल अंतरभूत व्योम flush_dcache_line_indexed(अचिन्हित दीर्घ addr)
अणु
	cache_op(Index_Writeback_Inv_D, addr);
पूर्ण

अटल अंतरभूत व्योम flush_scache_line_indexed(अचिन्हित दीर्घ addr)
अणु
	cache_op(Index_Writeback_Inv_SD, addr);
पूर्ण

अटल अंतरभूत व्योम flush_icache_line(अचिन्हित दीर्घ addr)
अणु
	चयन (boot_cpu_type()) अणु
	हाल CPU_LOONGSON2EF:
		cache_op(Hit_Invalidate_I_Loongson2, addr);
		अवरोध;

	शेष:
		cache_op(Hit_Invalidate_I, addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_dcache_line(अचिन्हित दीर्घ addr)
अणु
	cache_op(Hit_Writeback_Inv_D, addr);
पूर्ण

अटल अंतरभूत व्योम invalidate_dcache_line(अचिन्हित दीर्घ addr)
अणु
	cache_op(Hit_Invalidate_D, addr);
पूर्ण

अटल अंतरभूत व्योम invalidate_scache_line(अचिन्हित दीर्घ addr)
अणु
	cache_op(Hit_Invalidate_SD, addr);
पूर्ण

अटल अंतरभूत व्योम flush_scache_line(अचिन्हित दीर्घ addr)
अणु
	cache_op(Hit_Writeback_Inv_SD, addr);
पूर्ण

#अगर_घोषित CONFIG_EVA

#घोषणा रक्षित_cache_op(op, addr)				\
(अणु								\
	पूर्णांक __err = 0;						\
	__यंत्र__ __अस्थिर__(					\
	"	.set	push			\n"		\
	"	.set	noreorder		\n"		\
	"	.set	mips0			\n"		\
	"	.set	eva			\n"		\
	"1:	cachee	%1, (%2)		\n"		\
	"2:	.insn				\n"		\
	"	.set	pop			\n"		\
	"	.section .fixup,\"ax\"		\n"		\
	"3:	li	%0, %3			\n"		\
	"	j	2b			\n"		\
	"	.previous			\n"		\
	"	.section __ex_table,\"a\"	\n"		\
	"	"STR(PTR)" 1b, 3b		\n"		\
	"	.previous"					\
	: "+r" (__err)						\
	: "i" (op), "r" (addr), "i" (-EFAULT));			\
	__err;							\
पूर्ण)
#अन्यथा

#घोषणा रक्षित_cache_op(op, addr)				\
(अणु								\
	पूर्णांक __err = 0;						\
	__यंत्र__ __अस्थिर__(					\
	"	.set	push			\n"		\
	"	.set	noreorder		\n"		\
	"	.set "MIPS_ISA_ARCH_LEVEL"	\n"		\
	"1:	cache	%1, (%2)		\n"		\
	"2:	.insn				\n"		\
	"	.set	pop			\n"		\
	"	.section .fixup,\"ax\"		\n"		\
	"3:	li	%0, %3			\n"		\
	"	j	2b			\n"		\
	"	.previous			\n"		\
	"	.section __ex_table,\"a\"	\n"		\
	"	"STR(PTR)" 1b, 3b		\n"		\
	"	.previous"					\
	: "+r" (__err)						\
	: "i" (op), "r" (addr), "i" (-EFAULT));			\
	__err;							\
पूर्ण)
#पूर्ण_अगर

/*
 * The next two are क्रम badland addresses like संकेत trampolines.
 */
अटल अंतरभूत पूर्णांक रक्षित_flush_icache_line(अचिन्हित दीर्घ addr)
अणु
	चयन (boot_cpu_type()) अणु
	हाल CPU_LOONGSON2EF:
		वापस रक्षित_cache_op(Hit_Invalidate_I_Loongson2, addr);

	शेष:
		वापस रक्षित_cache_op(Hit_Invalidate_I, addr);
	पूर्ण
पूर्ण

/*
 * R10000 / R12000 hazard - these processors करोn't support the Hit_Writeback_D
 * cacheop so we use Hit_Writeback_Inv_D which is supported by all R4000-style
 * caches.  We're talking about one cacheline unnecessarily getting invalidated
 * here so the penalty isn't overly hard.
 */
अटल अंतरभूत पूर्णांक रक्षित_ग_लिखोback_dcache_line(अचिन्हित दीर्घ addr)
अणु
	वापस रक्षित_cache_op(Hit_Writeback_Inv_D, addr);
पूर्ण

अटल अंतरभूत पूर्णांक रक्षित_ग_लिखोback_scache_line(अचिन्हित दीर्घ addr)
अणु
	वापस रक्षित_cache_op(Hit_Writeback_Inv_SD, addr);
पूर्ण

/*
 * This one is RM7000-specअगरic
 */
अटल अंतरभूत व्योम invalidate_tcache_page(अचिन्हित दीर्घ addr)
अणु
	cache_op(Page_Invalidate_T, addr);
पूर्ण

#घोषणा cache_unroll(बार, insn, op, addr, lsize) करो अणु			\
	पूर्णांक i = 0;							\
	unroll(बार, _cache_op, insn, op, (addr) + (i++ * (lsize)));	\
पूर्ण जबतक (0)

/* build blast_xxx, blast_xxx_page, blast_xxx_page_indexed */
#घोषणा __BUILD_BLAST_CACHE(pfx, desc, indexop, hitop, lsize, extra)	\
अटल अंतरभूत व्योम extra##blast_##pfx##cache##lsize(व्योम)		\
अणु									\
	अचिन्हित दीर्घ start = INDEX_BASE;				\
	अचिन्हित दीर्घ end = start + current_cpu_data.desc.waysize;	\
	अचिन्हित दीर्घ ws_inc = 1UL << current_cpu_data.desc.waybit;	\
	अचिन्हित दीर्घ ws_end = current_cpu_data.desc.ways <<		\
			       current_cpu_data.desc.waybit;		\
	अचिन्हित दीर्घ ws, addr;						\
									\
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)				\
		क्रम (addr = start; addr < end; addr += lsize * 32)	\
			cache_unroll(32, kernel_cache, indexop,		\
				     addr | ws, lsize);			\
पूर्ण									\
									\
अटल अंतरभूत व्योम extra##blast_##pfx##cache##lsize##_page(अचिन्हित दीर्घ page) \
अणु									\
	अचिन्हित दीर्घ start = page;					\
	अचिन्हित दीर्घ end = page + PAGE_SIZE;				\
									\
	करो अणु								\
		cache_unroll(32, kernel_cache, hitop, start, lsize);	\
		start += lsize * 32;					\
	पूर्ण जबतक (start < end);						\
पूर्ण									\
									\
अटल अंतरभूत व्योम extra##blast_##pfx##cache##lsize##_page_indexed(अचिन्हित दीर्घ page) \
अणु									\
	अचिन्हित दीर्घ indexmask = current_cpu_data.desc.waysize - 1;	\
	अचिन्हित दीर्घ start = INDEX_BASE + (page & indexmask);		\
	अचिन्हित दीर्घ end = start + PAGE_SIZE;				\
	अचिन्हित दीर्घ ws_inc = 1UL << current_cpu_data.desc.waybit;	\
	अचिन्हित दीर्घ ws_end = current_cpu_data.desc.ways <<		\
			       current_cpu_data.desc.waybit;		\
	अचिन्हित दीर्घ ws, addr;						\
									\
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)				\
		क्रम (addr = start; addr < end; addr += lsize * 32)	\
			cache_unroll(32, kernel_cache, indexop,		\
				     addr | ws, lsize);			\
पूर्ण

__BUILD_BLAST_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D, 16, )
__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 16, )
__BUILD_BLAST_CACHE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 16, )
__BUILD_BLAST_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D, 32, )
__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 32, )
__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I_Loongson2, 32, loongson2_)
__BUILD_BLAST_CACHE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 32, )
__BUILD_BLAST_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D, 64, )
__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 64, )
__BUILD_BLAST_CACHE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 64, )
__BUILD_BLAST_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D, 128, )
__BUILD_BLAST_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 128, )
__BUILD_BLAST_CACHE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 128, )

__BUILD_BLAST_CACHE(inv_d, dcache, Index_Writeback_Inv_D, Hit_Invalidate_D, 16, )
__BUILD_BLAST_CACHE(inv_d, dcache, Index_Writeback_Inv_D, Hit_Invalidate_D, 32, )
__BUILD_BLAST_CACHE(inv_s, scache, Index_Writeback_Inv_SD, Hit_Invalidate_SD, 16, )
__BUILD_BLAST_CACHE(inv_s, scache, Index_Writeback_Inv_SD, Hit_Invalidate_SD, 32, )
__BUILD_BLAST_CACHE(inv_s, scache, Index_Writeback_Inv_SD, Hit_Invalidate_SD, 64, )
__BUILD_BLAST_CACHE(inv_s, scache, Index_Writeback_Inv_SD, Hit_Invalidate_SD, 128, )

#घोषणा __BUILD_BLAST_USER_CACHE(pfx, desc, indexop, hitop, lsize) \
अटल अंतरभूत व्योम blast_##pfx##cache##lsize##_user_page(अचिन्हित दीर्घ page) \
अणु									\
	अचिन्हित दीर्घ start = page;					\
	अचिन्हित दीर्घ end = page + PAGE_SIZE;				\
									\
	करो अणु								\
		cache_unroll(32, user_cache, hitop, start, lsize);	\
		start += lsize * 32;					\
	पूर्ण जबतक (start < end);						\
पूर्ण

__BUILD_BLAST_USER_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D,
			 16)
__BUILD_BLAST_USER_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 16)
__BUILD_BLAST_USER_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D,
			 32)
__BUILD_BLAST_USER_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 32)
__BUILD_BLAST_USER_CACHE(d, dcache, Index_Writeback_Inv_D, Hit_Writeback_Inv_D,
			 64)
__BUILD_BLAST_USER_CACHE(i, icache, Index_Invalidate_I, Hit_Invalidate_I, 64)

/* build blast_xxx_range, रक्षित_blast_xxx_range */
#घोषणा __BUILD_BLAST_CACHE_RANGE(pfx, desc, hitop, prot, extra)	\
अटल अंतरभूत व्योम prot##extra##blast_##pfx##cache##_range(अचिन्हित दीर्घ start, \
						    अचिन्हित दीर्घ end)	\
अणु									\
	अचिन्हित दीर्घ lsize = cpu_##desc##_line_size();			\
	अचिन्हित दीर्घ addr = start & ~(lsize - 1);			\
	अचिन्हित दीर्घ aend = (end - 1) & ~(lsize - 1);			\
									\
	जबतक (1) अणु							\
		prot##cache_op(hitop, addr);				\
		अगर (addr == aend)					\
			अवरोध;						\
		addr += lsize;						\
	पूर्ण								\
पूर्ण

__BUILD_BLAST_CACHE_RANGE(d, dcache, Hit_Writeback_Inv_D, रक्षित_, )
__BUILD_BLAST_CACHE_RANGE(i, icache, Hit_Invalidate_I, रक्षित_, )
__BUILD_BLAST_CACHE_RANGE(s, scache, Hit_Writeback_Inv_SD, रक्षित_, )
__BUILD_BLAST_CACHE_RANGE(i, icache, Hit_Invalidate_I_Loongson2, \
	रक्षित_, loongson2_)
__BUILD_BLAST_CACHE_RANGE(d, dcache, Hit_Writeback_Inv_D, , )
__BUILD_BLAST_CACHE_RANGE(i, icache, Hit_Invalidate_I, , )
__BUILD_BLAST_CACHE_RANGE(s, scache, Hit_Writeback_Inv_SD, , )
/* blast_inv_dcache_range */
__BUILD_BLAST_CACHE_RANGE(inv_d, dcache, Hit_Invalidate_D, , )
__BUILD_BLAST_CACHE_RANGE(inv_s, scache, Hit_Invalidate_SD, , )

/* Currently, this is very specअगरic to Loongson-3 */
#घोषणा __BUILD_BLAST_CACHE_NODE(pfx, desc, indexop, hitop, lsize)	\
अटल अंतरभूत व्योम blast_##pfx##cache##lsize##_node(दीर्घ node)		\
अणु									\
	अचिन्हित दीर्घ start = CAC_BASE | nid_to_addrbase(node);		\
	अचिन्हित दीर्घ end = start + current_cpu_data.desc.waysize;	\
	अचिन्हित दीर्घ ws_inc = 1UL << current_cpu_data.desc.waybit;	\
	अचिन्हित दीर्घ ws_end = current_cpu_data.desc.ways <<		\
			       current_cpu_data.desc.waybit;		\
	अचिन्हित दीर्घ ws, addr;						\
									\
	क्रम (ws = 0; ws < ws_end; ws += ws_inc)				\
		क्रम (addr = start; addr < end; addr += lsize * 32)	\
			cache_unroll(32, kernel_cache, indexop,		\
				     addr | ws, lsize);			\
पूर्ण

__BUILD_BLAST_CACHE_NODE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 16)
__BUILD_BLAST_CACHE_NODE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 32)
__BUILD_BLAST_CACHE_NODE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 64)
__BUILD_BLAST_CACHE_NODE(s, scache, Index_Writeback_Inv_SD, Hit_Writeback_Inv_SD, 128)

#पूर्ण_अगर /* _ASM_R4KCACHE_H */
