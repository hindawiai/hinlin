<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMU_H_
#घोषणा _ASM_POWERPC_MMU_H_
#अगर_घोषित __KERNEL__

#समावेश <linux/types.h>

#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * MMU features bit definitions
 */

/*
 * MMU families
 */
#घोषणा MMU_FTR_HPTE_TABLE		ASM_CONST(0x00000001)
#घोषणा MMU_FTR_TYPE_8xx		ASM_CONST(0x00000002)
#घोषणा MMU_FTR_TYPE_40x		ASM_CONST(0x00000004)
#घोषणा MMU_FTR_TYPE_44x		ASM_CONST(0x00000008)
#घोषणा MMU_FTR_TYPE_FSL_E		ASM_CONST(0x00000010)
#घोषणा MMU_FTR_TYPE_47x		ASM_CONST(0x00000020)

/* Radix page table supported and enabled */
#घोषणा MMU_FTR_TYPE_RADIX		ASM_CONST(0x00000040)

/*
 * Inभागidual features below.
 */

/*
 * Supports KUAP feature
 * key 0 controlling userspace addresses on radix
 * Key 3 on hash
 */
#घोषणा MMU_FTR_BOOK3S_KUAP		ASM_CONST(0x00000200)

/*
 * Supports KUEP feature
 * key 0 controlling userspace addresses on radix
 * Key 3 on hash
 */
#घोषणा MMU_FTR_BOOK3S_KUEP		ASM_CONST(0x00000400)

/*
 * Support क्रम memory protection keys.
 */
#घोषणा MMU_FTR_PKEY			ASM_CONST(0x00000800)

/* Guest Translation Shootकरोwn Enable */
#घोषणा MMU_FTR_GTSE			ASM_CONST(0x00001000)

/*
 * Support क्रम 68 bit VA space. We added that from ISA 2.05
 */
#घोषणा MMU_FTR_68_BIT_VA		ASM_CONST(0x00002000)
/*
 * Kernel पढ़ो only support.
 * We added the ppp value 0b110 in ISA 2.04.
 */
#घोषणा MMU_FTR_KERNEL_RO		ASM_CONST(0x00004000)

/*
 * We need to clear top 16bits of va (from the reमुख्यing 64 bits )in
 * tlbie* inकाष्ठाions
 */
#घोषणा MMU_FTR_TLBIE_CROP_VA		ASM_CONST(0x00008000)

/* Enable use of high BAT रेजिस्टरs */
#घोषणा MMU_FTR_USE_HIGH_BATS		ASM_CONST(0x00010000)

/* Enable >32-bit physical addresses on 32-bit processor, only used
 * by CONFIG_PPC_BOOK3S_32 currently as BookE supports that from day 1
 */
#घोषणा MMU_FTR_BIG_PHYS		ASM_CONST(0x00020000)

/* Enable use of broadcast TLB invalidations. We करोn't always set it
 * on processors that support it due to other स्थिरraपूर्णांकs with the
 * use of such invalidations
 */
#घोषणा MMU_FTR_USE_TLBIVAX_BCAST	ASM_CONST(0x00040000)

/* Enable use of tlbilx invalidate inकाष्ठाions.
 */
#घोषणा MMU_FTR_USE_TLBILX		ASM_CONST(0x00080000)

/* This indicates that the processor cannot handle multiple outstanding
 * broadcast tlbivax or tlbsync. This makes the code use a spinlock
 * around such invalidate क्रमms.
 */
#घोषणा MMU_FTR_LOCK_BCAST_INVAL	ASM_CONST(0x00100000)

/* This indicates that the processor करोesn't handle way selection
 * properly and needs SW to track and update the LRU state.  This
 * is specअगरic to an errata on e300c2/c3/c4 class parts
 */
#घोषणा MMU_FTR_NEED_DTLB_SW_LRU	ASM_CONST(0x00200000)

/* Enable use of TLB reservation.  Processor should support tlbsrx.
 * inकाष्ठाion and MAS0[WQ].
 */
#घोषणा MMU_FTR_USE_TLBRSRV		ASM_CONST(0x00800000)

/* Use paired MAS रेजिस्टरs (MAS7||MAS3, etc.)
 */
#घोषणा MMU_FTR_USE_PAIRED_MAS		ASM_CONST(0x01000000)

/* Doesn't support the B bit (1T segment) in SLBIE
 */
#घोषणा MMU_FTR_NO_SLBIE_B		ASM_CONST(0x02000000)

/* Support 16M large pages
 */
#घोषणा MMU_FTR_16M_PAGE		ASM_CONST(0x04000000)

/* Supports TLBIEL variant
 */
#घोषणा MMU_FTR_TLBIEL			ASM_CONST(0x08000000)

/* Supports tlbies w/o locking
 */
#घोषणा MMU_FTR_LOCKLESS_TLBIE		ASM_CONST(0x10000000)

/* Large pages can be marked CI
 */
#घोषणा MMU_FTR_CI_LARGE_PAGE		ASM_CONST(0x20000000)

/* 1T segments available
 */
#घोषणा MMU_FTR_1T_SEGMENT		ASM_CONST(0x40000000)

/* MMU feature bit sets क्रम various CPUs */
#घोषणा MMU_FTRS_DEFAULT_HPTE_ARCH_V2	(MMU_FTR_HPTE_TABLE | MMU_FTR_TLBIEL | MMU_FTR_16M_PAGE)
#घोषणा MMU_FTRS_POWER		MMU_FTRS_DEFAULT_HPTE_ARCH_V2
#घोषणा MMU_FTRS_PPC970		MMU_FTRS_POWER | MMU_FTR_TLBIE_CROP_VA
#घोषणा MMU_FTRS_POWER5		MMU_FTRS_POWER | MMU_FTR_LOCKLESS_TLBIE
#घोषणा MMU_FTRS_POWER6		MMU_FTRS_POWER5 | MMU_FTR_KERNEL_RO | MMU_FTR_68_BIT_VA
#घोषणा MMU_FTRS_POWER7		MMU_FTRS_POWER6
#घोषणा MMU_FTRS_POWER8		MMU_FTRS_POWER6
#घोषणा MMU_FTRS_POWER9		MMU_FTRS_POWER6
#घोषणा MMU_FTRS_POWER10	MMU_FTRS_POWER6
#घोषणा MMU_FTRS_CELL		MMU_FTRS_DEFAULT_HPTE_ARCH_V2 | \
				MMU_FTR_CI_LARGE_PAGE
#घोषणा MMU_FTRS_PA6T		MMU_FTRS_DEFAULT_HPTE_ARCH_V2 | \
				MMU_FTR_CI_LARGE_PAGE | MMU_FTR_NO_SLBIE_B
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/bug.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/page.h>

प्रकार pte_t *pgtable_t;

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
#समावेश <यंत्र/percpu.h>
DECLARE_PER_CPU(पूर्णांक, next_tlbcam_idx);
#पूर्ण_अगर

क्रमागत अणु
	MMU_FTRS_POSSIBLE =
#अगर defined(CONFIG_PPC_BOOK3S_64) || defined(CONFIG_PPC_BOOK3S_604)
		MMU_FTR_HPTE_TABLE |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_8xx
		MMU_FTR_TYPE_8xx |
#पूर्ण_अगर
#अगर_घोषित CONFIG_40x
		MMU_FTR_TYPE_40x |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_47x
		MMU_FTR_TYPE_47x | MMU_FTR_USE_TLBIVAX_BCAST | MMU_FTR_LOCK_BCAST_INVAL |
#या_अगर defined(CONFIG_44x)
		MMU_FTR_TYPE_44x |
#पूर्ण_अगर
#अगर_घोषित CONFIG_E500
		MMU_FTR_TYPE_FSL_E | MMU_FTR_BIG_PHYS | MMU_FTR_USE_TLBILX |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_32
		MMU_FTR_USE_HIGH_BATS |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_83xx
		MMU_FTR_NEED_DTLB_SW_LRU |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3E_64
		MMU_FTR_USE_TLBRSRV | MMU_FTR_USE_PAIRED_MAS |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
		MMU_FTR_NO_SLBIE_B | MMU_FTR_16M_PAGE | MMU_FTR_TLBIEL |
		MMU_FTR_LOCKLESS_TLBIE | MMU_FTR_CI_LARGE_PAGE |
		MMU_FTR_1T_SEGMENT | MMU_FTR_TLBIE_CROP_VA |
		MMU_FTR_KERNEL_RO | MMU_FTR_68_BIT_VA |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_RADIX_MMU
		MMU_FTR_TYPE_RADIX |
		MMU_FTR_GTSE |
#पूर्ण_अगर /* CONFIG_PPC_RADIX_MMU */
#अगर_घोषित CONFIG_PPC_KUAP
	MMU_FTR_BOOK3S_KUAP |
#पूर्ण_अगर /* CONFIG_PPC_KUAP */
#अगर_घोषित CONFIG_PPC_MEM_KEYS
	MMU_FTR_PKEY |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_KUEP
	MMU_FTR_BOOK3S_KUEP |
#पूर्ण_अगर /* CONFIG_PPC_KUAP */

		0,
पूर्ण;

#अगर defined(CONFIG_PPC_BOOK3S_604) && !defined(CONFIG_PPC_BOOK3S_603)
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_HPTE_TABLE
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_8xx
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_TYPE_8xx
#पूर्ण_अगर
#अगर_घोषित CONFIG_40x
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_TYPE_40x
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_47x
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_TYPE_47x
#या_अगर defined(CONFIG_44x)
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_TYPE_44x
#पूर्ण_अगर
#अगर defined(CONFIG_E200) || defined(CONFIG_E500)
#घोषणा MMU_FTRS_ALWAYS		MMU_FTR_TYPE_FSL_E
#पूर्ण_अगर

#अगर_अघोषित MMU_FTRS_ALWAYS
#घोषणा MMU_FTRS_ALWAYS		0
#पूर्ण_अगर

अटल __always_अंतरभूत bool early_mmu_has_feature(अचिन्हित दीर्घ feature)
अणु
	अगर (MMU_FTRS_ALWAYS & feature)
		वापस true;

	वापस !!(MMU_FTRS_POSSIBLE & cur_cpu_spec->mmu_features & feature);
पूर्ण

#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECKS
#समावेश <linux/jump_label.h>

#घोषणा NUM_MMU_FTR_KEYS	32

बाह्य काष्ठा अटल_key_true mmu_feature_keys[NUM_MMU_FTR_KEYS];

बाह्य व्योम mmu_feature_keys_init(व्योम);

अटल __always_अंतरभूत bool mmu_has_feature(अचिन्हित दीर्घ feature)
अणु
	पूर्णांक i;

#अगर_अघोषित __clang__ /* clang can't cope with this */
	BUILD_BUG_ON(!__builtin_स्थिरant_p(feature));
#पूर्ण_अगर

#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECK_DEBUG
	अगर (!अटल_key_initialized) अणु
		prपूर्णांकk("Warning! mmu_has_feature() used prior to jump label init!\n");
		dump_stack();
		वापस early_mmu_has_feature(feature);
	पूर्ण
#पूर्ण_अगर

	अगर (MMU_FTRS_ALWAYS & feature)
		वापस true;

	अगर (!(MMU_FTRS_POSSIBLE & feature))
		वापस false;

	i = __builtin_ctzl(feature);
	वापस अटल_branch_likely(&mmu_feature_keys[i]);
पूर्ण

अटल अंतरभूत व्योम mmu_clear_feature(अचिन्हित दीर्घ feature)
अणु
	पूर्णांक i;

	i = __builtin_ctzl(feature);
	cur_cpu_spec->mmu_features &= ~feature;
	अटल_branch_disable(&mmu_feature_keys[i]);
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम mmu_feature_keys_init(व्योम)
अणु

पूर्ण

अटल __always_अंतरभूत bool mmu_has_feature(अचिन्हित दीर्घ feature)
अणु
	वापस early_mmu_has_feature(feature);
पूर्ण

अटल अंतरभूत व्योम mmu_clear_feature(अचिन्हित दीर्घ feature)
अणु
	cur_cpu_spec->mmu_features &= ~feature;
पूर्ण
#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

बाह्य अचिन्हित पूर्णांक __start___mmu_ftr_fixup, __stop___mmu_ftr_fixup;

#अगर_घोषित CONFIG_PPC64
/* This is our real memory area size on ppc64 server, on embedded, we
 * make it match the size our of bolted TLB area
 */
बाह्य u64 ppc64_rma_size;

/* Cleanup function used by kexec */
बाह्य व्योम mmu_cleanup_all(व्योम);
बाह्य व्योम radix__mmu_cleanup_all(व्योम);

/* Functions क्रम creating and updating partition table on POWER9 */
बाह्य व्योम mmu_partition_table_init(व्योम);
बाह्य व्योम mmu_partition_table_set_entry(अचिन्हित पूर्णांक lpid, अचिन्हित दीर्घ dw0,
					  अचिन्हित दीर्घ dw1, bool flush);
#पूर्ण_अगर /* CONFIG_PPC64 */

काष्ठा mm_काष्ठा;
#अगर_घोषित CONFIG_DEBUG_VM
बाह्य व्योम निश्चित_pte_locked(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
#अन्यथा /* CONFIG_DEBUG_VM */
अटल अंतरभूत व्योम निश्चित_pte_locked(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_DEBUG_VM */

#अगर_घोषित CONFIG_PPC_RADIX_MMU
अटल अंतरभूत bool radix_enabled(व्योम)
अणु
	वापस mmu_has_feature(MMU_FTR_TYPE_RADIX);
पूर्ण

अटल अंतरभूत bool early_radix_enabled(व्योम)
अणु
	वापस early_mmu_has_feature(MMU_FTR_TYPE_RADIX);
पूर्ण
#अन्यथा
अटल अंतरभूत bool radix_enabled(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool early_radix_enabled(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
अटल अंतरभूत bool strict_kernel_rwx_enabled(व्योम)
अणु
	वापस rodata_enabled;
पूर्ण
#अन्यथा
अटल अंतरभूत bool strict_kernel_rwx_enabled(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* !__ASSEMBLY__ */

/* The kernel use the स्थिरants below to index in the page sizes array.
 * The use of fixed स्थिरants क्रम this purpose is better क्रम perक्रमmances
 * of the low level hash refill handlers.
 *
 * A non supported page size has a "shift" field set to 0
 *
 * Any new page size being implemented can get a new entry in here. Whether
 * the kernel will use it or not is a dअगरferent matter though. The actual page
 * size used by hugetlbfs is not defined here and may be made variable
 *
 * Note: This array ended up being a false good idea as it's growing to the
 * poपूर्णांक where I wonder अगर we should replace it with something dअगरferent,
 * to think about, feedback welcome. --BenH.
 */

/* These are #घोषणाs as they have to be used in assembly */
#घोषणा MMU_PAGE_4K	0
#घोषणा MMU_PAGE_16K	1
#घोषणा MMU_PAGE_64K	2
#घोषणा MMU_PAGE_64K_AP	3	/* "Admixed pages" (hash64 only) */
#घोषणा MMU_PAGE_256K	4
#घोषणा MMU_PAGE_512K	5
#घोषणा MMU_PAGE_1M	6
#घोषणा MMU_PAGE_2M	7
#घोषणा MMU_PAGE_4M	8
#घोषणा MMU_PAGE_8M	9
#घोषणा MMU_PAGE_16M	10
#घोषणा MMU_PAGE_64M	11
#घोषणा MMU_PAGE_256M	12
#घोषणा MMU_PAGE_1G	13
#घोषणा MMU_PAGE_16G	14
#घोषणा MMU_PAGE_64G	15

/*
 * N.B. we need to change the type of hpte_page_sizes अगर this माला_लो to be > 16
 * Also we need to change he type of mm_context.low/high_slices_psize.
 */
#घोषणा MMU_PAGE_COUNT	16

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/book3s/64/mmu.h>
#अन्यथा /* CONFIG_PPC_BOOK3S_64 */

#अगर_अघोषित __ASSEMBLY__
/* MMU initialization */
बाह्य व्योम early_init_mmu(व्योम);
बाह्य व्योम early_init_mmu_secondary(व्योम);
बाह्य व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
				       phys_addr_t first_memblock_size);
अटल अंतरभूत व्योम mmu_early_init_devtree(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम pkey_early_init_devtree(व्योम) अणुपूर्ण

बाह्य व्योम *abatron_pteptrs[2];
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर

#अगर defined(CONFIG_PPC_BOOK3S_32)
/* 32-bit classic hash table MMU */
#समावेश <यंत्र/book3s/32/mmu-hash.h>
#या_अगर defined(CONFIG_PPC_MMU_NOHASH)
#समावेश <यंत्र/nohash/mmu.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_MMU_H_ */
