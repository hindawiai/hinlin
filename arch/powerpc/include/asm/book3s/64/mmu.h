<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_MMU_H_
#घोषणा _ASM_POWERPC_BOOK3S_64_MMU_H_

#समावेश <यंत्र/page.h>

#अगर_अघोषित __ASSEMBLY__
/*
 * Page size definition
 *
 *    shअगरt : is the "PAGE_SHIFT" value क्रम that page size
 *    sllp  : is a bit mask with the value of SLB L || LP to be or'ed
 *            directly to a slbmte "vsid" value
 *    penc  : is the HPTE encoding mask क्रम the "LP" field:
 *
 */
काष्ठा mmu_psize_def अणु
	अचिन्हित पूर्णांक	shअगरt;	/* number of bits */
	पूर्णांक		penc[MMU_PAGE_COUNT];	/* HPTE encoding */
	अचिन्हित पूर्णांक	tlbiel;	/* tlbiel supported क्रम that page size */
	अचिन्हित दीर्घ	avpnm;	/* bits to mask out in AVPN in the HPTE */
	जोड़ अणु
		अचिन्हित दीर्घ	sllp;	/* SLB L||LP (exact mask to use in slbmte) */
		अचिन्हित दीर्घ ap;	/* Ap encoding used by PowerISA 3.0 */
	पूर्ण;
पूर्ण;
बाह्य काष्ठा mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT];
#पूर्ण_अगर /* __ASSEMBLY__ */

/* 64-bit classic hash table MMU */
#समावेश <यंत्र/book3s/64/mmu-hash.h>

#अगर_अघोषित __ASSEMBLY__
/*
 * ISA 3.0 partition and process table entry क्रमmat
 */
काष्ठा prtb_entry अणु
	__be64 prtb0;
	__be64 prtb1;
पूर्ण;
बाह्य काष्ठा prtb_entry *process_tb;

काष्ठा patb_entry अणु
	__be64 patb0;
	__be64 patb1;
पूर्ण;
बाह्य काष्ठा patb_entry *partition_tb;

/* Bits in patb0 field */
#घोषणा PATB_HR		(1UL << 63)
#घोषणा RPDB_MASK	0x0fffffffffffff00UL
#घोषणा RPDB_SHIFT	(1UL << 8)
#घोषणा RTS1_SHIFT	61		/* top 2 bits of radix tree size */
#घोषणा RTS1_MASK	(3UL << RTS1_SHIFT)
#घोषणा RTS2_SHIFT	5		/* bottom 3 bits of radix tree size */
#घोषणा RTS2_MASK	(7UL << RTS2_SHIFT)
#घोषणा RPDS_MASK	0x1f		/* root page dir. size field */

/* Bits in patb1 field */
#घोषणा PATB_GR		(1UL << 63)	/* guest uses radix; must match HR */
#घोषणा PRTS_MASK	0x1f		/* process table size field */
#घोषणा PRTB_MASK	0x0ffffffffffff000UL

/* Number of supported PID bits */
बाह्य अचिन्हित पूर्णांक mmu_pid_bits;

/* Base PID to allocate from */
बाह्य अचिन्हित पूर्णांक mmu_base_pid;

/*
 * memory block size used with radix translation.
 */
बाह्य अचिन्हित दीर्घ __ro_after_init radix_mem_block_size;

#घोषणा PRTB_SIZE_SHIFT	(mmu_pid_bits + 4)
#घोषणा PRTB_ENTRIES	(1ul << mmu_pid_bits)

/*
 * Power9 currently only support 64K partition table size.
 */
#घोषणा PATB_SIZE_SHIFT	16

प्रकार अचिन्हित दीर्घ mm_context_id_t;
काष्ठा spinlock;

/* Maximum possible number of NPUs in a प्रणाली. */
#घोषणा NV_MAX_NPUS 8

प्रकार काष्ठा अणु
	जोड़ अणु
		/*
		 * We use id as the PIDR content क्रम radix. On hash we can use
		 * more than one id. The extended ids are used when we start
		 * having address above 512TB. We allocate one extended id
		 * क्रम each 512TB. The new id is then used with the 49 bit
		 * EA to build a new VA. We always use ESID_BITS_1T_MASK bits
		 * from EA and new context ids to build the new VAs.
		 */
		mm_context_id_t id;
		mm_context_id_t extended_id[TASK_SIZE_USER64/TASK_CONTEXT_SIZE];
	पूर्ण;

	/* Number of bits in the mm_cpumask */
	atomic_t active_cpus;

	/* Number of users of the बाह्यal (Nest) MMU */
	atomic_t copros;

	/* Number of user space winकरोws खोलोed in process mm_context */
	atomic_t vas_winकरोws;

	काष्ठा hash_mm_context *hash_context;

	व्योम __user *vdso;
	/*
	 * pagetable fragment support
	 */
	व्योम *pte_frag;
	व्योम *pmd_frag;
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	काष्ठा list_head iommu_group_mem_list;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_MEM_KEYS
	/*
	 * Each bit represents one protection key.
	 * bit set   -> key allocated
	 * bit unset -> key available क्रम allocation
	 */
	u32 pkey_allocation_map;
	s16 execute_only_pkey; /* key holding execute-only protection */
#पूर्ण_अगर
पूर्ण mm_context_t;

अटल अंतरभूत u16 mm_ctx_user_psize(mm_context_t *ctx)
अणु
	वापस ctx->hash_context->user_psize;
पूर्ण

अटल अंतरभूत व्योम mm_ctx_set_user_psize(mm_context_t *ctx, u16 user_psize)
अणु
	ctx->hash_context->user_psize = user_psize;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *mm_ctx_low_slices(mm_context_t *ctx)
अणु
	वापस ctx->hash_context->low_slices_psize;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *mm_ctx_high_slices(mm_context_t *ctx)
अणु
	वापस ctx->hash_context->high_slices_psize;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mm_ctx_slb_addr_limit(mm_context_t *ctx)
अणु
	वापस ctx->hash_context->slb_addr_limit;
पूर्ण

अटल अंतरभूत व्योम mm_ctx_set_slb_addr_limit(mm_context_t *ctx, अचिन्हित दीर्घ limit)
अणु
	ctx->hash_context->slb_addr_limit = limit;
पूर्ण

अटल अंतरभूत काष्ठा slice_mask *slice_mask_क्रम_size(mm_context_t *ctx, पूर्णांक psize)
अणु
#अगर_घोषित CONFIG_PPC_64K_PAGES
	अगर (psize == MMU_PAGE_64K)
		वापस &ctx->hash_context->mask_64k;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (psize == MMU_PAGE_16M)
		वापस &ctx->hash_context->mask_16m;
	अगर (psize == MMU_PAGE_16G)
		वापस &ctx->hash_context->mask_16g;
#पूर्ण_अगर
	BUG_ON(psize != MMU_PAGE_4K);

	वापस &ctx->hash_context->mask_4k;
पूर्ण

#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
अटल अंतरभूत काष्ठा subpage_prot_table *mm_ctx_subpage_prot(mm_context_t *ctx)
अणु
	वापस ctx->hash_context->spt;
पूर्ण
#पूर्ण_अगर

/*
 * The current प्रणाली page and segment sizes
 */
बाह्य पूर्णांक mmu_linear_psize;
बाह्य पूर्णांक mmu_भव_psize;
बाह्य पूर्णांक mmu_vदो_स्मृति_psize;
बाह्य पूर्णांक mmu_vmemmap_psize;
बाह्य पूर्णांक mmu_io_psize;

/* MMU initialization */
व्योम mmu_early_init_devtree(व्योम);
व्योम hash__early_init_devtree(व्योम);
व्योम radix__early_init_devtree(व्योम);
#अगर_घोषित CONFIG_PPC_PKEY
व्योम pkey_early_init_devtree(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pkey_early_init_devtree(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम hash__early_init_mmu(व्योम);
बाह्य व्योम radix__early_init_mmu(व्योम);
अटल अंतरभूत व्योम __init early_init_mmu(व्योम)
अणु
	अगर (radix_enabled())
		वापस radix__early_init_mmu();
	वापस hash__early_init_mmu();
पूर्ण
बाह्य व्योम hash__early_init_mmu_secondary(व्योम);
बाह्य व्योम radix__early_init_mmu_secondary(व्योम);
अटल अंतरभूत व्योम early_init_mmu_secondary(व्योम)
अणु
	अगर (radix_enabled())
		वापस radix__early_init_mmu_secondary();
	वापस hash__early_init_mmu_secondary();
पूर्ण

बाह्य व्योम hash__setup_initial_memory_limit(phys_addr_t first_memblock_base,
					 phys_addr_t first_memblock_size);
अटल अंतरभूत व्योम setup_initial_memory_limit(phys_addr_t first_memblock_base,
					      phys_addr_t first_memblock_size)
अणु
	/*
	 * Hash has more strict restrictions. At this poपूर्णांक we करोn't
	 * know which translations we will pick. Hence go with hash
	 * restrictions.
	 */
	वापस hash__setup_initial_memory_limit(first_memblock_base,
					   first_memblock_size);
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य व्योम radix_init_pseries(व्योम);
#अन्यथा
अटल अंतरभूत व्योम radix_init_pseries(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HOTPLUG_CPU
#घोषणा arch_clear_mm_cpumask_cpu(cpu, mm)				\
	करो अणु								\
		अगर (cpumask_test_cpu(cpu, mm_cpumask(mm))) अणु		\
			atomic_dec(&(mm)->context.active_cpus);		\
			cpumask_clear_cpu(cpu, mm_cpumask(mm));		\
		पूर्ण							\
	पूर्ण जबतक (0)

व्योम cleanup_cpu_mmu_context(व्योम);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक get_user_context(mm_context_t *ctx, अचिन्हित दीर्घ ea)
अणु
	पूर्णांक index = ea >> MAX_EA_BITS_PER_CONTEXT;

	अगर (likely(index < ARRAY_SIZE(ctx->extended_id)))
		वापस ctx->extended_id[index];

	/* should never happen */
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_user_vsid(mm_context_t *ctx,
					  अचिन्हित दीर्घ ea, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ context = get_user_context(ctx, ea);

	वापस get_vsid(context, ea, ssize);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_MMU_H_ */
