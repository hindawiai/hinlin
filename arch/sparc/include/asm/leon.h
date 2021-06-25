<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2004 Konrad Eisele (eiselekd@web.de,konrad@gaisler.com) Gaisler Research
 * Copyright (C) 2004 Stefan Holst (mail@s-holst.de) Uni-Stuttgart
 * Copyright (C) 2009 Daniel Hellstrom (daniel@gaisler.com) Aeroflex Gaisler AB
 * Copyright (C) 2009 Konrad Eisele (konrad@gaisler.com) Aeroflex Gaisler AB
 */

#अगर_अघोषित LEON_H_INCLUDE
#घोषणा LEON_H_INCLUDE

/* mmu रेजिस्टर access, ASI_LEON_MMUREGS */
#घोषणा LEON_CNR_CTRL		0x000
#घोषणा LEON_CNR_CTXP		0x100
#घोषणा LEON_CNR_CTX		0x200
#घोषणा LEON_CNR_F		0x300
#घोषणा LEON_CNR_FADDR		0x400

#घोषणा LEON_CNR_CTX_NCTX	256	/*number of MMU ctx */

#घोषणा LEON_CNR_CTRL_TLBDIS	0x80000000

#घोषणा LEON_MMUTLB_ENT_MAX	64

/*
 * diagnostic access from mmutlb.vhd:
 * 0: pte address
 * 4: pte
 * 8: additional flags
 */
#घोषणा LEON_DIAGF_LVL		0x3
#घोषणा LEON_DIAGF_WR		0x8
#घोषणा LEON_DIAGF_WR_SHIFT	3
#घोषणा LEON_DIAGF_HIT		0x10
#घोषणा LEON_DIAGF_HIT_SHIFT	4
#घोषणा LEON_DIAGF_CTX		0x1fe0
#घोषणा LEON_DIAGF_CTX_SHIFT	5
#घोषणा LEON_DIAGF_VALID	0x2000
#घोषणा LEON_DIAGF_VALID_SHIFT	13

/* irq masks */
#घोषणा LEON_HARD_INT(x)	(1 << (x))	/* irq 0-15 */
#घोषणा LEON_IRQMASK_R		0x0000fffe	/* bit 15- 1 of lregs.irqmask */
#घोषणा LEON_IRQPRIO_R		0xfffe0000	/* bit 31-17 of lregs.irqmask */

#घोषणा LEON_MCFG2_SRAMDIS		0x00002000
#घोषणा LEON_MCFG2_SDRAMEN		0x00004000
#घोषणा LEON_MCFG2_SRAMBANKSZ		0x00001e00	/* [12-9] */
#घोषणा LEON_MCFG2_SRAMBANKSZ_SHIFT	9
#घोषणा LEON_MCFG2_SDRAMBANKSZ		0x03800000	/* [25-23] */
#घोषणा LEON_MCFG2_SDRAMBANKSZ_SHIFT	23

#घोषणा LEON_TCNT0_MASK	0x7fffff


#घोषणा ASI_LEON3_SYSCTRL		0x02
#घोषणा ASI_LEON3_SYSCTRL_ICFG		0x08
#घोषणा ASI_LEON3_SYSCTRL_DCFG		0x0c
#घोषणा ASI_LEON3_SYSCTRL_CFG_SNOOPING (1 << 27)
#घोषणा ASI_LEON3_SYSCTRL_CFG_SSIZE(c) (1 << ((c >> 20) & 0xf))

#अगर_अघोषित __ASSEMBLY__

/* करो a physical address bypass ग_लिखो, i.e. क्रम 0x80000000 */
अटल अंतरभूत व्योम leon_store_reg(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ value)
अणु
	__यंत्र__ __अस्थिर__("sta %0, [%1] %2\n\t" : : "r"(value), "r"(paddr),
			     "i"(ASI_LEON_BYPASS) : "memory");
पूर्ण

/* करो a physical address bypass load, i.e. क्रम 0x80000000 */
अटल अंतरभूत अचिन्हित दीर्घ leon_load_reg(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ retval;
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t" :
			     "=r"(retval) : "r"(paddr), "i"(ASI_LEON_BYPASS));
	वापस retval;
पूर्ण

/* macro access क्रम leon_load_reg() and leon_store_reg() */
#घोषणा LEON3_BYPASS_LOAD_PA(x)	    (leon_load_reg((अचिन्हित दीर्घ)(x)))
#घोषणा LEON3_BYPASS_STORE_PA(x, v) (leon_store_reg((अचिन्हित दीर्घ)(x), (अचिन्हित दीर्घ)(v)))
#घोषणा LEON_BYPASS_LOAD_PA(x)      leon_load_reg((अचिन्हित दीर्घ)(x))
#घोषणा LEON_BYPASS_STORE_PA(x, v)  leon_store_reg((अचिन्हित दीर्घ)(x), (अचिन्हित दीर्घ)(v))

व्योम leon_चयन_mm(व्योम);
व्योम leon_init_IRQ(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ sparc_leon3_get_dcachecfg(व्योम)
अणु
	अचिन्हित पूर्णांक retval;
	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t" :
			     "=r"(retval) :
			     "r"(ASI_LEON3_SYSCTRL_DCFG),
			     "i"(ASI_LEON3_SYSCTRL));
	वापस retval;
पूर्ण

/* enable snooping */
अटल अंतरभूत व्योम sparc_leon3_enable_snooping(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("lda [%%g0] 2, %%l1\n\t"
			  "set 0x800000, %%l2\n\t"
			  "or  %%l2, %%l1, %%l2\n\t"
			  "sta %%l2, [%%g0] 2\n\t" : : : "l1", "l2");
पूर्ण;

अटल अंतरभूत पूर्णांक sparc_leon3_snooping_enabled(व्योम)
अणु
	u32 cctrl;
	__यंत्र__ __अस्थिर__("lda [%%g0] 2, %0\n\t" : "=r"(cctrl));
	वापस ((cctrl >> 23) & 1) && ((cctrl >> 17) & 1);
पूर्ण;

अटल अंतरभूत व्योम sparc_leon3_disable_cache(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("lda [%%g0] 2, %%l1\n\t"
			  "set 0x00000f, %%l2\n\t"
			  "andn  %%l2, %%l1, %%l2\n\t"
			  "sta %%l2, [%%g0] 2\n\t" : : : "l1", "l2");
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ sparc_leon3_asr17(व्योम)
अणु
	u32 asr17;
	__यंत्र__ __अस्थिर__ ("rd %%asr17, %0\n\t" : "=r"(asr17));
	वापस asr17;
पूर्ण;

अटल अंतरभूत पूर्णांक sparc_leon3_cpuid(व्योम)
अणु
	वापस sparc_leon3_asr17() >> 28;
पूर्ण

#पूर्ण_अगर /*!__ASSEMBLY__*/

#अगर_घोषित CONFIG_SMP
# define LEON3_IRQ_IPI_DEFAULT		13
# define LEON3_IRQ_TICKER		(leon3_gpसमयr_irq)
# define LEON3_IRQ_CROSS_CALL		15
#पूर्ण_अगर

#अगर defined(PAGE_SIZE_LEON_8K)
#घोषणा LEON_PAGE_SIZE_LEON 1
#या_अगर defined(PAGE_SIZE_LEON_16K)
#घोषणा LEON_PAGE_SIZE_LEON 2)
#अन्यथा
#घोषणा LEON_PAGE_SIZE_LEON 0
#पूर्ण_अगर

#अगर LEON_PAGE_SIZE_LEON == 0
/* [ 8, 6, 6 ] + 12 */
#घोषणा LEON_PGD_SH    24
#घोषणा LEON_PGD_M     0xff
#घोषणा LEON_PMD_SH    18
#घोषणा LEON_PMD_SH_V  (LEON_PGD_SH-2)
#घोषणा LEON_PMD_M     0x3f
#घोषणा LEON_PTE_SH    12
#घोषणा LEON_PTE_M     0x3f
#या_अगर LEON_PAGE_SIZE_LEON == 1
/* [ 7, 6, 6 ] + 13 */
#घोषणा LEON_PGD_SH    25
#घोषणा LEON_PGD_M     0x7f
#घोषणा LEON_PMD_SH    19
#घोषणा LEON_PMD_SH_V  (LEON_PGD_SH-1)
#घोषणा LEON_PMD_M     0x3f
#घोषणा LEON_PTE_SH    13
#घोषणा LEON_PTE_M     0x3f
#या_अगर LEON_PAGE_SIZE_LEON == 2
/* [ 6, 6, 6 ] + 14 */
#घोषणा LEON_PGD_SH    26
#घोषणा LEON_PGD_M     0x3f
#घोषणा LEON_PMD_SH    20
#घोषणा LEON_PMD_SH_V  (LEON_PGD_SH-0)
#घोषणा LEON_PMD_M     0x3f
#घोषणा LEON_PTE_SH    14
#घोषणा LEON_PTE_M     0x3f
#या_अगर LEON_PAGE_SIZE_LEON == 3
/* [ 4, 7, 6 ] + 15 */
#घोषणा LEON_PGD_SH    28
#घोषणा LEON_PGD_M     0x0f
#घोषणा LEON_PMD_SH    21
#घोषणा LEON_PMD_SH_V  (LEON_PGD_SH-0)
#घोषणा LEON_PMD_M     0x7f
#घोषणा LEON_PTE_SH    15
#घोषणा LEON_PTE_M     0x3f
#अन्यथा
#त्रुटि cannot determine LEON_PAGE_SIZE_LEON
#पूर्ण_अगर

#घोषणा LEON3_XCCR_SETS_MASK  0x07000000UL
#घोषणा LEON3_XCCR_SSIZE_MASK 0x00f00000UL

#घोषणा LEON2_CCR_DSETS_MASK 0x03000000UL
#घोषणा LEON2_CFG_SSIZE_MASK 0x00007000UL

#अगर_अघोषित __ASSEMBLY__
काष्ठा vm_area_काष्ठा;

अचिन्हित दीर्घ leon_swprobe(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ *paddr);
व्योम leon_flush_icache_all(व्योम);
व्योम leon_flush_dcache_all(व्योम);
व्योम leon_flush_cache_all(व्योम);
व्योम leon_flush_tlb_all(व्योम);
बाह्य पूर्णांक leon_flush_during_चयन;
पूर्णांक leon_flush_needed(व्योम);
व्योम leon_flush_pcache_all(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);

/* काष्ठा that hold LEON3 cache configuration रेजिस्टरs */
काष्ठा leon3_cacheregs अणु
	अचिन्हित दीर्घ ccr;	/* 0x00 - Cache Control Register  */
	अचिन्हित दीर्घ iccr;     /* 0x08 - Inकाष्ठाion Cache Configuration Register */
	अचिन्हित दीर्घ dccr;	/* 0x0c - Data Cache Configuration Register */
पूर्ण;

#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

काष्ठा device_node;
काष्ठा task_काष्ठा;
अचिन्हित पूर्णांक leon_build_device_irq(अचिन्हित पूर्णांक real_irq,
				   irq_flow_handler_t flow_handler,
				   स्थिर अक्षर *name, पूर्णांक करो_ack);
व्योम leon_update_virq_handling(अचिन्हित पूर्णांक virq,
			       irq_flow_handler_t flow_handler,
			       स्थिर अक्षर *name, पूर्णांक करो_ack);
व्योम leon_init_समयrs(व्योम);
व्योम leon_node_init(काष्ठा device_node *dp, काष्ठा device_node ***nextp);
व्योम init_leon(व्योम);
व्योम poke_leonsparc(व्योम);
व्योम leon3_getCacheRegs(काष्ठा leon3_cacheregs *regs);
बाह्य पूर्णांक leon3_ticker_irq;

#अगर_घोषित CONFIG_SMP
पूर्णांक leon_smp_nrcpus(व्योम);
व्योम leon_clear_profile_irq(पूर्णांक cpu);
व्योम leon_smp_करोne(व्योम);
व्योम leon_boot_cpus(व्योम);
पूर्णांक leon_boot_one_cpu(पूर्णांक i, काष्ठा task_काष्ठा *);
व्योम leon_init_smp(व्योम);
व्योम leon_enable_irq_cpu(अचिन्हित पूर्णांक irq_nr, अचिन्हित पूर्णांक cpu);
irqवापस_t leon_percpu_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *unused);

बाह्य अचिन्हित पूर्णांक smpleon_ipi[];
बाह्य अचिन्हित पूर्णांक linux_trap_ipi15_leon[];
बाह्य पूर्णांक leon_ipi_irq;

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* __ASSEMBLY__ */

/* macros used in leon_mm.c */
#घोषणा PFN(x)           ((x) >> PAGE_SHIFT)
#घोषणा _pfn_valid(pfn)	 ((pfn < last_valid_pfn) && (pfn >= PFN(phys_base)))
#घोषणा _SRMMU_PTE_PMASK_LEON 0xffffffff

/*
 * On LEON PCI Memory space is mapped 1:1 with physical address space.
 *
 * I/O space is located at low 64Kbytes in PCI I/O space. The I/O addresses
 * are converted पूर्णांकo CPU addresses to भव addresses that are mapped with
 * MMU to the PCI Host PCI I/O space winकरोw which are translated to the low
 * 64Kbytes by the Host controller.
 */

#पूर्ण_अगर
