<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* spitfire.h: SpitFire/BlackBird/Cheetah अंतरभूत MMU operations.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC64_SPITFIRE_H
#घोषणा _SPARC64_SPITFIRE_H

#अगर_घोषित CONFIG_SPARC64

#समावेश <यंत्र/asi.h>

/* The following रेजिस्टर addresses are accessible via ASI_DMMU
 * and ASI_IMMU, that is there is a distinct and unique copy of
 * each these रेजिस्टरs क्रम each TLB.
 */
#घोषणा TSB_TAG_TARGET		0x0000000000000000 /* All chips				*/
#घोषणा TLB_SFSR		0x0000000000000018 /* All chips				*/
#घोषणा TSB_REG			0x0000000000000028 /* All chips				*/
#घोषणा TLB_TAG_ACCESS		0x0000000000000030 /* All chips				*/
#घोषणा VIRT_WATCHPOINT		0x0000000000000038 /* All chips				*/
#घोषणा PHYS_WATCHPOINT		0x0000000000000040 /* All chips				*/
#घोषणा TSB_EXTENSION_P		0x0000000000000048 /* Ultra-III and later		*/
#घोषणा TSB_EXTENSION_S		0x0000000000000050 /* Ultra-III and later, D-TLB only	*/
#घोषणा TSB_EXTENSION_N		0x0000000000000058 /* Ultra-III and later		*/
#घोषणा TLB_TAG_ACCESS_EXT	0x0000000000000060 /* Ultra-III+ and later		*/

/* These रेजिस्टरs only exist as one entity, and are accessed
 * via ASI_DMMU only.
 */
#घोषणा PRIMARY_CONTEXT		0x0000000000000008
#घोषणा SECONDARY_CONTEXT	0x0000000000000010
#घोषणा DMMU_SFAR		0x0000000000000020
#घोषणा VIRT_WATCHPOINT		0x0000000000000038
#घोषणा PHYS_WATCHPOINT		0x0000000000000040

#घोषणा SPITFIRE_HIGHEST_LOCKED_TLBENT	(64 - 1)
#घोषणा CHEETAH_HIGHEST_LOCKED_TLBENT	(16 - 1)

#घोषणा L1DCACHE_SIZE		0x4000

#घोषणा SUN4V_CHIP_INVALID	0x00
#घोषणा SUN4V_CHIP_NIAGARA1	0x01
#घोषणा SUN4V_CHIP_NIAGARA2	0x02
#घोषणा SUN4V_CHIP_NIAGARA3	0x03
#घोषणा SUN4V_CHIP_NIAGARA4	0x04
#घोषणा SUN4V_CHIP_NIAGARA5	0x05
#घोषणा SUN4V_CHIP_SPARC_M6	0x06
#घोषणा SUN4V_CHIP_SPARC_M7	0x07
#घोषणा SUN4V_CHIP_SPARC_M8	0x08
#घोषणा SUN4V_CHIP_SPARC64X	0x8a
#घोषणा SUN4V_CHIP_SPARC_SN	0x8b
#घोषणा SUN4V_CHIP_UNKNOWN	0xff

/*
 * The following CPU_ID_xxx स्थिरants are used
 * to identअगरy the CPU type in the setup phase
 * (see head_64.S)
 */
#घोषणा CPU_ID_NIAGARA1		('1')
#घोषणा CPU_ID_NIAGARA2		('2')
#घोषणा CPU_ID_NIAGARA3		('3')
#घोषणा CPU_ID_NIAGARA4		('4')
#घोषणा CPU_ID_NIAGARA5		('5')
#घोषणा CPU_ID_M6		('6')
#घोषणा CPU_ID_M7		('7')
#घोषणा CPU_ID_M8		('8')
#घोषणा CPU_ID_SONOMA1		('N')

#अगर_अघोषित __ASSEMBLY__

क्रमागत ultra_tlb_layout अणु
	spitfire = 0,
	cheetah = 1,
	cheetah_plus = 2,
	hypervisor = 3,
पूर्ण;

बाह्य क्रमागत ultra_tlb_layout tlb_type;

बाह्य पूर्णांक sun4v_chip_type;

बाह्य पूर्णांक cheetah_pcache_क्रमced_on;
व्योम cheetah_enable_pcache(व्योम);

#घोषणा sparc64_highest_locked_tlbent()	\
	(tlb_type == spitfire ? \
	 SPITFIRE_HIGHEST_LOCKED_TLBENT : \
	 CHEETAH_HIGHEST_LOCKED_TLBENT)

बाह्य पूर्णांक num_kernel_image_mappings;

/* The data cache is ग_लिखो through, so this just invalidates the
 * specअगरied line.
 */
अटल अंतरभूत व्योम spitfire_put_dcache_tag(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ tag)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (tag), "r" (addr), "i" (ASI_DCACHE_TAG));
पूर्ण

/* The inकाष्ठाion cache lines are flushed with this, but note that
 * this करोes not flush the pipeline.  It is possible क्रम a line to
 * get flushed but stale inकाष्ठाions to still be in the pipeline,
 * a flush inकाष्ठाion (to any address) is sufficient to handle
 * this issue after the line is invalidated.
 */
अटल अंतरभूत व्योम spitfire_put_icache_tag(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ tag)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (tag), "r" (addr), "i" (ASI_IC_TAG));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ spitfire_get_dtlb_data(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" (entry << 3), "i" (ASI_DTLB_DATA_ACCESS));

	/* Clear TTE diag bits. */
	data &= ~0x0003fe0000000000UL;

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ spitfire_get_dtlb_tag(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" (entry << 3), "i" (ASI_DTLB_TAG_READ));
	वापस tag;
पूर्ण

अटल अंतरभूत व्योम spitfire_put_dtlb_data(पूर्णांक entry, अचिन्हित दीर्घ data)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data), "r" (entry << 3),
			       "i" (ASI_DTLB_DATA_ACCESS));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ spitfire_get_itlb_data(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" (entry << 3), "i" (ASI_ITLB_DATA_ACCESS));

	/* Clear TTE diag bits. */
	data &= ~0x0003fe0000000000UL;

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ spitfire_get_itlb_tag(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" (entry << 3), "i" (ASI_ITLB_TAG_READ));
	वापस tag;
पूर्ण

अटल अंतरभूत व्योम spitfire_put_itlb_data(पूर्णांक entry, अचिन्हित दीर्घ data)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data), "r" (entry << 3),
			       "i" (ASI_ITLB_DATA_ACCESS));
पूर्ण

अटल अंतरभूत व्योम spitfire_flush_dtlb_nucleus_page(अचिन्हित दीर्घ page)
अणु
	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %1\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (page | 0x20), "i" (ASI_DMMU_DEMAP));
पूर्ण

अटल अंतरभूत व्योम spitfire_flush_itlb_nucleus_page(अचिन्हित दीर्घ page)
अणु
	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %1\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (page | 0x20), "i" (ASI_IMMU_DEMAP));
पूर्ण

/* Cheetah has "all non-locked" tlb flushes. */
अटल अंतरभूत व्योम cheetah_flush_dtlb_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %1\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (0x80), "i" (ASI_DMMU_DEMAP));
पूर्ण

अटल अंतरभूत व्योम cheetah_flush_itlb_all(व्योम)
अणु
	__यंत्र__ __अस्थिर__("stxa	%%g0, [%0] %1\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (0x80), "i" (ASI_IMMU_DEMAP));
पूर्ण

/* Cheetah has a 4-tlb layout so direct access is a bit dअगरferent.
 * The first two TLBs are fully assosciative, hold 16 entries, and are
 * used only क्रम locked and >8K sized translations.  One exists क्रम
 * data accesses and one क्रम inकाष्ठाion accesses.
 *
 * The third TLB is क्रम data accesses to 8K non-locked translations, is
 * 2 way assosciative, and holds 512 entries.  The fourth TLB is क्रम
 * inकाष्ठाion accesses to 8K non-locked translations, is 2 way
 * assosciative, and holds 128 entries.
 *
 * Cheetah has some bug where bogus data can be वापसed from
 * ASI_अणुD,Iपूर्णTLB_DATA_ACCESS loads, करोing the load twice fixes
 * the problem क्रम me. -DaveM
 */
अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_ldtlb_data(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %%g0\n\t"
			     "ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" ((0 << 16) | (entry << 3)),
			     "i" (ASI_DTLB_DATA_ACCESS));

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_litlb_data(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %%g0\n\t"
			     "ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" ((0 << 16) | (entry << 3)),
			     "i" (ASI_ITLB_DATA_ACCESS));

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_ldtlb_tag(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" ((0 << 16) | (entry << 3)),
			     "i" (ASI_DTLB_TAG_READ));

	वापस tag;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_litlb_tag(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" ((0 << 16) | (entry << 3)),
			     "i" (ASI_ITLB_TAG_READ));

	वापस tag;
पूर्ण

अटल अंतरभूत व्योम cheetah_put_ldtlb_data(पूर्णांक entry, अचिन्हित दीर्घ data)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data),
			       "r" ((0 << 16) | (entry << 3)),
			       "i" (ASI_DTLB_DATA_ACCESS));
पूर्ण

अटल अंतरभूत व्योम cheetah_put_litlb_data(पूर्णांक entry, अचिन्हित दीर्घ data)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data),
			       "r" ((0 << 16) | (entry << 3)),
			       "i" (ASI_ITLB_DATA_ACCESS));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_dtlb_data(पूर्णांक entry, पूर्णांक tlb)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %%g0\n\t"
			     "ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" ((tlb << 16) | (entry << 3)), "i" (ASI_DTLB_DATA_ACCESS));

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_dtlb_tag(पूर्णांक entry, पूर्णांक tlb)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" ((tlb << 16) | (entry << 3)), "i" (ASI_DTLB_TAG_READ));
	वापस tag;
पूर्ण

अटल अंतरभूत व्योम cheetah_put_dtlb_data(पूर्णांक entry, अचिन्हित दीर्घ data, पूर्णांक tlb)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data),
			       "r" ((tlb << 16) | (entry << 3)),
			       "i" (ASI_DTLB_DATA_ACCESS));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_itlb_data(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ data;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %%g0\n\t"
			     "ldxa	[%1] %2, %0"
			     : "=r" (data)
			     : "r" ((2 << 16) | (entry << 3)),
                               "i" (ASI_ITLB_DATA_ACCESS));

	वापस data;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ cheetah_get_itlb_tag(पूर्णांक entry)
अणु
	अचिन्हित दीर्घ tag;

	__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
			     : "=r" (tag)
			     : "r" ((2 << 16) | (entry << 3)), "i" (ASI_ITLB_TAG_READ));
	वापस tag;
पूर्ण

अटल अंतरभूत व्योम cheetah_put_itlb_data(पूर्णांक entry, अचिन्हित दीर्घ data)
अणु
	__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2\n\t"
			     "membar	#Sync"
			     : /* No outमाला_दो */
			     : "r" (data), "r" ((2 << 16) | (entry << 3)),
			       "i" (ASI_ITLB_DATA_ACCESS));
पूर्ण

#पूर्ण_अगर /* !(__ASSEMBLY__) */
#पूर्ण_अगर /* CONFIG_SPARC64 */
#पूर्ण_अगर /* !(_SPARC64_SPITFIRE_H) */
