<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MPIC_H
#घोषणा _ASM_POWERPC_MPIC_H
#अगर_घोषित __KERNEL__

#समावेश <linux/irq.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

/*
 * Global रेजिस्टरs
 */

#घोषणा MPIC_GREG_BASE			0x01000

#घोषणा MPIC_GREG_FEATURE_0		0x00000
#घोषणा		MPIC_GREG_FEATURE_LAST_SRC_MASK		0x07ff0000
#घोषणा		MPIC_GREG_FEATURE_LAST_SRC_SHIFT	16
#घोषणा		MPIC_GREG_FEATURE_LAST_CPU_MASK		0x00001f00
#घोषणा		MPIC_GREG_FEATURE_LAST_CPU_SHIFT	8
#घोषणा		MPIC_GREG_FEATURE_VERSION_MASK		0xff
#घोषणा MPIC_GREG_FEATURE_1		0x00010
#घोषणा MPIC_GREG_GLOBAL_CONF_0		0x00020
#घोषणा		MPIC_GREG_GCONF_RESET			0x80000000
/* On the FSL mpic implementations the Mode field is expand to be
 * 2 bits wide:
 *	0b00 = pass through (पूर्णांकerrupts routed to IRQ0)
 *	0b01 = Mixed mode
 *	0b10 = reserved
 *	0b11 = External proxy / coreपूर्णांक
 */
#घोषणा		MPIC_GREG_GCONF_COREINT			0x60000000
#घोषणा		MPIC_GREG_GCONF_8259_PTHROU_DIS		0x20000000
#घोषणा		MPIC_GREG_GCONF_NO_BIAS			0x10000000
#घोषणा		MPIC_GREG_GCONF_BASE_MASK		0x000fffff
#घोषणा		MPIC_GREG_GCONF_MCK			0x08000000
#घोषणा MPIC_GREG_GLOBAL_CONF_1		0x00030
#घोषणा MPIC_GREG_VENDOR_0		0x00040
#घोषणा MPIC_GREG_VENDOR_1		0x00050
#घोषणा MPIC_GREG_VENDOR_2		0x00060
#घोषणा MPIC_GREG_VENDOR_3		0x00070
#घोषणा MPIC_GREG_VENDOR_ID		0x00080
#घोषणा 	MPIC_GREG_VENDOR_ID_STEPPING_MASK	0x00ff0000
#घोषणा 	MPIC_GREG_VENDOR_ID_STEPPING_SHIFT	16
#घोषणा 	MPIC_GREG_VENDOR_ID_DEVICE_ID_MASK	0x0000ff00
#घोषणा 	MPIC_GREG_VENDOR_ID_DEVICE_ID_SHIFT	8
#घोषणा 	MPIC_GREG_VENDOR_ID_VENDOR_ID_MASK	0x000000ff
#घोषणा MPIC_GREG_PROCESSOR_INIT	0x00090
#घोषणा MPIC_GREG_IPI_VECTOR_PRI_0	0x000a0
#घोषणा MPIC_GREG_IPI_VECTOR_PRI_1	0x000b0
#घोषणा MPIC_GREG_IPI_VECTOR_PRI_2	0x000c0
#घोषणा MPIC_GREG_IPI_VECTOR_PRI_3	0x000d0
#घोषणा MPIC_GREG_IPI_STRIDE		0x10
#घोषणा MPIC_GREG_SPURIOUS		0x000e0
#घोषणा MPIC_GREG_TIMER_FREQ		0x000f0

/*
 *
 * Timer रेजिस्टरs
 */
#घोषणा MPIC_TIMER_BASE			0x01100
#घोषणा MPIC_TIMER_STRIDE		0x40
#घोषणा MPIC_TIMER_GROUP_STRIDE		0x1000

#घोषणा MPIC_TIMER_CURRENT_CNT		0x00000
#घोषणा MPIC_TIMER_BASE_CNT		0x00010
#घोषणा MPIC_TIMER_VECTOR_PRI		0x00020
#घोषणा MPIC_TIMER_DESTINATION		0x00030

/*
 * Per-Processor रेजिस्टरs
 */

#घोषणा MPIC_CPU_THISBASE		0x00000
#घोषणा MPIC_CPU_BASE			0x20000
#घोषणा MPIC_CPU_STRIDE			0x01000

#घोषणा MPIC_CPU_IPI_DISPATCH_0		0x00040
#घोषणा MPIC_CPU_IPI_DISPATCH_1		0x00050
#घोषणा MPIC_CPU_IPI_DISPATCH_2		0x00060
#घोषणा MPIC_CPU_IPI_DISPATCH_3		0x00070
#घोषणा MPIC_CPU_IPI_DISPATCH_STRIDE	0x00010
#घोषणा MPIC_CPU_CURRENT_TASK_PRI	0x00080
#घोषणा 	MPIC_CPU_TASKPRI_MASK			0x0000000f
#घोषणा MPIC_CPU_WHOAMI			0x00090
#घोषणा 	MPIC_CPU_WHOAMI_MASK			0x0000001f
#घोषणा MPIC_CPU_INTACK			0x000a0
#घोषणा MPIC_CPU_EOI			0x000b0
#घोषणा MPIC_CPU_MCACK			0x000c0

/*
 * Per-source रेजिस्टरs
 */

#घोषणा MPIC_IRQ_BASE			0x10000
#घोषणा MPIC_IRQ_STRIDE			0x00020
#घोषणा MPIC_IRQ_VECTOR_PRI		0x00000
#घोषणा 	MPIC_VECPRI_MASK			0x80000000
#घोषणा 	MPIC_VECPRI_ACTIVITY			0x40000000	/* Read Only */
#घोषणा 	MPIC_VECPRI_PRIORITY_MASK		0x000f0000
#घोषणा 	MPIC_VECPRI_PRIORITY_SHIFT		16
#घोषणा 	MPIC_VECPRI_VECTOR_MASK			0x000007ff
#घोषणा 	MPIC_VECPRI_POLARITY_POSITIVE		0x00800000
#घोषणा 	MPIC_VECPRI_POLARITY_NEGATIVE		0x00000000
#घोषणा 	MPIC_VECPRI_POLARITY_MASK		0x00800000
#घोषणा 	MPIC_VECPRI_SENSE_LEVEL			0x00400000
#घोषणा 	MPIC_VECPRI_SENSE_EDGE			0x00000000
#घोषणा 	MPIC_VECPRI_SENSE_MASK			0x00400000
#घोषणा MPIC_IRQ_DESTINATION		0x00010

#घोषणा MPIC_FSL_BRR1			0x00000
#घोषणा 	MPIC_FSL_BRR1_VER			0x0000ffff

#घोषणा MPIC_MAX_IRQ_SOURCES	2048
#घोषणा MPIC_MAX_CPUS		32
#घोषणा MPIC_MAX_ISU		32

#घोषणा MPIC_MAX_ERR      32
#घोषणा MPIC_FSL_ERR_INT  16

/*
 * Tsi108 implementation of MPIC has many dअगरferences from the original one
 */

/*
 * Global रेजिस्टरs
 */

#घोषणा TSI108_GREG_BASE		0x00000
#घोषणा TSI108_GREG_FEATURE_0		0x00000
#घोषणा TSI108_GREG_GLOBAL_CONF_0	0x00004
#घोषणा TSI108_GREG_VENDOR_ID		0x0000c
#घोषणा TSI108_GREG_IPI_VECTOR_PRI_0	0x00204		/* Doorbell 0 */
#घोषणा TSI108_GREG_IPI_STRIDE		0x0c
#घोषणा TSI108_GREG_SPURIOUS		0x00010
#घोषणा TSI108_GREG_TIMER_FREQ		0x00014

/*
 * Timer रेजिस्टरs
 */
#घोषणा TSI108_TIMER_BASE		0x0030
#घोषणा TSI108_TIMER_STRIDE		0x10
#घोषणा TSI108_TIMER_CURRENT_CNT	0x00000
#घोषणा TSI108_TIMER_BASE_CNT		0x00004
#घोषणा TSI108_TIMER_VECTOR_PRI		0x00008
#घोषणा TSI108_TIMER_DESTINATION	0x0000c

/*
 * Per-Processor रेजिस्टरs
 */
#घोषणा TSI108_CPU_BASE			0x00300
#घोषणा TSI108_CPU_STRIDE		0x00040
#घोषणा TSI108_CPU_IPI_DISPATCH_0	0x00200
#घोषणा TSI108_CPU_IPI_DISPATCH_STRIDE	0x00000
#घोषणा TSI108_CPU_CURRENT_TASK_PRI	0x00000
#घोषणा TSI108_CPU_WHOAMI		0xffffffff
#घोषणा TSI108_CPU_INTACK		0x00004
#घोषणा TSI108_CPU_EOI			0x00008
#घोषणा TSI108_CPU_MCACK		0x00004 /* Doesn't really exist here */

/*
 * Per-source रेजिस्टरs
 */
#घोषणा TSI108_IRQ_BASE			0x00100
#घोषणा TSI108_IRQ_STRIDE		0x00008
#घोषणा TSI108_IRQ_VECTOR_PRI		0x00000
#घोषणा TSI108_VECPRI_VECTOR_MASK	0x000000ff
#घोषणा TSI108_VECPRI_POLARITY_POSITIVE	0x01000000
#घोषणा TSI108_VECPRI_POLARITY_NEGATIVE	0x00000000
#घोषणा TSI108_VECPRI_SENSE_LEVEL	0x02000000
#घोषणा TSI108_VECPRI_SENSE_EDGE	0x00000000
#घोषणा TSI108_VECPRI_POLARITY_MASK	0x01000000
#घोषणा TSI108_VECPRI_SENSE_MASK	0x02000000
#घोषणा TSI108_IRQ_DESTINATION		0x00004

/* weird mpic रेजिस्टर indices and mask bits in the HW info array */
क्रमागत अणु
	MPIC_IDX_GREG_BASE = 0,
	MPIC_IDX_GREG_FEATURE_0,
	MPIC_IDX_GREG_GLOBAL_CONF_0,
	MPIC_IDX_GREG_VENDOR_ID,
	MPIC_IDX_GREG_IPI_VECTOR_PRI_0,
	MPIC_IDX_GREG_IPI_STRIDE,
	MPIC_IDX_GREG_SPURIOUS,
	MPIC_IDX_GREG_TIMER_FREQ,

	MPIC_IDX_TIMER_BASE,
	MPIC_IDX_TIMER_STRIDE,
	MPIC_IDX_TIMER_CURRENT_CNT,
	MPIC_IDX_TIMER_BASE_CNT,
	MPIC_IDX_TIMER_VECTOR_PRI,
	MPIC_IDX_TIMER_DESTINATION,

	MPIC_IDX_CPU_BASE,
	MPIC_IDX_CPU_STRIDE,
	MPIC_IDX_CPU_IPI_DISPATCH_0,
	MPIC_IDX_CPU_IPI_DISPATCH_STRIDE,
	MPIC_IDX_CPU_CURRENT_TASK_PRI,
	MPIC_IDX_CPU_WHOAMI,
	MPIC_IDX_CPU_INTACK,
	MPIC_IDX_CPU_EOI,
	MPIC_IDX_CPU_MCACK,

	MPIC_IDX_IRQ_BASE,
	MPIC_IDX_IRQ_STRIDE,
	MPIC_IDX_IRQ_VECTOR_PRI,

	MPIC_IDX_VECPRI_VECTOR_MASK,
	MPIC_IDX_VECPRI_POLARITY_POSITIVE,
	MPIC_IDX_VECPRI_POLARITY_NEGATIVE,
	MPIC_IDX_VECPRI_SENSE_LEVEL,
	MPIC_IDX_VECPRI_SENSE_EDGE,
	MPIC_IDX_VECPRI_POLARITY_MASK,
	MPIC_IDX_VECPRI_SENSE_MASK,
	MPIC_IDX_IRQ_DESTINATION,
	MPIC_IDX_END
पूर्ण;


#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
/* Fixup table entry */
काष्ठा mpic_irq_fixup
अणु
	u8 __iomem	*base;
	u8 __iomem	*applebase;
	u32		data;
	अचिन्हित पूर्णांक	index;
पूर्ण;
#पूर्ण_अगर /* CONFIG_MPIC_U3_HT_IRQS */


क्रमागत mpic_reg_type अणु
	mpic_access_mmio_le,
	mpic_access_mmio_be,
#अगर_घोषित CONFIG_PPC_DCR
	mpic_access_dcr
#पूर्ण_अगर
पूर्ण;

काष्ठा mpic_reg_bank अणु
	u32 __iomem	*base;
#अगर_घोषित CONFIG_PPC_DCR
	dcr_host_t	dhost;
#पूर्ण_अगर /* CONFIG_PPC_DCR */
पूर्ण;

काष्ठा mpic_irq_save अणु
	u32		vecprio,
			dest;
#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	u32		fixup_data;
#पूर्ण_अगर
पूर्ण;

/* The instance data of a given MPIC */
काष्ठा mpic
अणु
	/* The OpenFirmware dt node क्रम this MPIC */
	काष्ठा device_node *node;

	/* The remapper क्रम this MPIC */
	काष्ठा irq_करोमुख्य	*irqhost;

	/* The "linux" controller काष्ठा */
	काष्ठा irq_chip		hc_irq;
#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	काष्ठा irq_chip		hc_ht_irq;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	काष्ठा irq_chip		hc_ipi;
#पूर्ण_अगर
	काष्ठा irq_chip		hc_पंचांग;
	काष्ठा irq_chip		hc_err;
	स्थिर अक्षर		*name;
	/* Flags */
	अचिन्हित पूर्णांक		flags;
	/* How many irq sources in a given ISU */
	अचिन्हित पूर्णांक		isu_size;
	अचिन्हित पूर्णांक		isu_shअगरt;
	अचिन्हित पूर्णांक		isu_mask;
	/* Number of sources */
	अचिन्हित पूर्णांक		num_sources;

	/* vector numbers used क्रम पूर्णांकernal sources (ipi/समयrs) */
	अचिन्हित पूर्णांक		ipi_vecs[4];
	अचिन्हित पूर्णांक		समयr_vecs[8];
	/* vector numbers used क्रम FSL MPIC error पूर्णांकerrupts */
	अचिन्हित पूर्णांक		err_पूर्णांक_vecs[MPIC_MAX_ERR];

	/* Spurious vector to program पूर्णांकo unused sources */
	अचिन्हित पूर्णांक		spurious_vec;

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
	/* The fixup table */
	काष्ठा mpic_irq_fixup	*fixups;
	raw_spinlock_t	fixup_lock;
#पूर्ण_अगर

	/* Register access method */
	क्रमागत mpic_reg_type	reg_type;

	/* The physical base address of the MPIC */
	phys_addr_t paddr;

	/* The various ioremap'ed bases */
	काष्ठा mpic_reg_bank	thiscpuregs;
	काष्ठा mpic_reg_bank	gregs;
	काष्ठा mpic_reg_bank	पंचांगregs;
	काष्ठा mpic_reg_bank	cpuregs[MPIC_MAX_CPUS];
	काष्ठा mpic_reg_bank	isus[MPIC_MAX_ISU];

	/* ioremap'ed base क्रम error पूर्णांकerrupt रेजिस्टरs */
	u32 __iomem	*err_regs;

	/* Protected sources */
	अचिन्हित दीर्घ		*रक्षित;

#अगर_घोषित CONFIG_MPIC_WEIRD
	/* Poपूर्णांकer to HW info array */
	u32			*hw_set;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा msi_biपंचांगap	msi_biपंचांगap;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MPIC_BROKEN_REGREAD
	u32			isu_reg0_shaकरोw[MPIC_MAX_IRQ_SOURCES];
#पूर्ण_अगर

	/* link */
	काष्ठा mpic		*next;

#अगर_घोषित CONFIG_PM
	काष्ठा mpic_irq_save	*save_data;
#पूर्ण_अगर
पूर्ण;

बाह्य काष्ठा bus_type mpic_subsys;

/*
 * MPIC flags (passed to mpic_alloc)
 *
 * The top 4 bits contain an MPIC bhw id that is used to index the
 * रेजिस्टर offsets and some masks when CONFIG_MPIC_WEIRD is set.
 * Note setting any ID (leaving those bits to 0) means standard MPIC
 */

/*
 * This is a secondary ("chained") controller; it only uses the CPU0
 * रेजिस्टरs.  Primary controllers have IPIs and affinity control.
 */
#घोषणा MPIC_SECONDARY			0x00000001

/* Set this क्रम a big-endian MPIC */
#घोषणा MPIC_BIG_ENDIAN			0x00000002
/* Broken U3 MPIC */
#घोषणा MPIC_U3_HT_IRQS			0x00000004
/* Broken IPI रेजिस्टरs (स्वतःdetected) */
#घोषणा MPIC_BROKEN_IPI			0x00000008
/* Spurious vector requires EOI */
#घोषणा MPIC_SPV_EOI			0x00000020
/* No passthrough disable */
#घोषणा MPIC_NO_PTHROU_DIS		0x00000040
/* DCR based MPIC */
#घोषणा MPIC_USES_DCR			0x00000080
/* MPIC has 11-bit vector fields (or larger) */
#घोषणा MPIC_LARGE_VECTORS		0x00000100
/* Enable delivery of prio 15 पूर्णांकerrupts as MCK instead of EE */
#घोषणा MPIC_ENABLE_MCK			0x00000200
/* Disable bias among target selection, spपढ़ो पूर्णांकerrupts evenly */
#घोषणा MPIC_NO_BIAS			0x00000400
/* Destination only supports a single CPU at a समय */
#घोषणा MPIC_SINGLE_DEST_CPU		0x00001000
/* Enable CoreInt delivery of पूर्णांकerrupts */
#घोषणा MPIC_ENABLE_COREINT		0x00002000
/* Do not reset the MPIC during initialization */
#घोषणा MPIC_NO_RESET			0x00004000
/* Freescale MPIC (compatible includes "fsl,mpic") */
#घोषणा MPIC_FSL			0x00008000
/* Freescale MPIC supports EIMR (error पूर्णांकerrupt mask रेजिस्टर).
 * This flag is set क्रम MPIC version >= 4.1 (version determined
 * from the BRR1 रेजिस्टर).
*/
#घोषणा MPIC_FSL_HAS_EIMR		0x00010000

/* MPIC HW modअगरication ID */
#घोषणा MPIC_REGSET_MASK		0xf0000000
#घोषणा MPIC_REGSET(val)		(((val) & 0xf ) << 28)
#घोषणा MPIC_GET_REGSET(flags)		(((flags) >> 28) & 0xf)

#घोषणा	MPIC_REGSET_STANDARD		MPIC_REGSET(0)	/* Original MPIC */
#घोषणा	MPIC_REGSET_TSI108		MPIC_REGSET(1)	/* Tsi108/109 PIC */

/* Get the version of primary MPIC */
#अगर_घोषित CONFIG_MPIC
बाह्य u32 fsl_mpic_primary_get_version(व्योम);
#अन्यथा
अटल अंतरभूत u32 fsl_mpic_primary_get_version(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Allocate the controller काष्ठाure and setup the linux irq descs
 * क्रम the range अगर पूर्णांकerrupts passed in. No HW initialization is
 * actually perक्रमmed.
 * 
 * @phys_addr:	physial base address of the MPIC
 * @flags:	flags, see स्थिरants above
 * @isu_size:	number of पूर्णांकerrupts in an ISU. Use 0 to use a
 *              standard ISU-less setup (aka घातermac)
 * @irq_offset: first irq number to assign to this mpic
 * @irq_count:  number of irqs to use with this mpic IRQ sources. Pass 0
 *	        to match the number of sources
 * @ipi_offset: first irq number to assign to this mpic IPI sources,
 *		used only on primary mpic
 * @senses:	array of sense values
 * @senses_num: number of entries in the array
 *
 * Note about the sense array. If none is passed, all पूर्णांकerrupts are
 * setup to be level negative unless MPIC_U3_HT_IRQS is set in which
 * हाल they are edge positive (and the array is ignored anyway).
 * The values in the array start at the first source of the MPIC,
 * that is senses[0] correspond to linux irq "irq_offset".
 */
बाह्य काष्ठा mpic *mpic_alloc(काष्ठा device_node *node,
			       phys_addr_t phys_addr,
			       अचिन्हित पूर्णांक flags,
			       अचिन्हित पूर्णांक isu_size,
			       अचिन्हित पूर्णांक irq_count,
			       स्थिर अक्षर *name);

/* Assign ISUs, to call beक्रमe mpic_init()
 *
 * @mpic:	controller काष्ठाure as वापसed by mpic_alloc()
 * @isu_num:	ISU number
 * @phys_addr:	physical address of the ISU
 */
बाह्य व्योम mpic_assign_isu(काष्ठा mpic *mpic, अचिन्हित पूर्णांक isu_num,
			    phys_addr_t phys_addr);


/* Initialize the controller. After this has been called, none of the above
 * should be called again क्रम this mpic
 */
बाह्य व्योम mpic_init(काष्ठा mpic *mpic);

/*
 * All of the following functions must only be used after the
 * ISUs have been asचिन्हित and the controller fully initialized
 * with mpic_init()
 */


/* Change the priority of an पूर्णांकerrupt. Default is 8 क्रम irqs and
 * 10 क्रम IPIs. You can call this on both IPIs and IRQ numbers, but the
 * IPI number is then the offset'ed (linux irq number mapped to the IPI)
 */
बाह्य व्योम mpic_irq_set_priority(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक pri);

/* Setup a non-boot CPU */
बाह्य व्योम mpic_setup_this_cpu(व्योम);

/* Clean up क्रम kexec (or cpu offline or ...) */
बाह्य व्योम mpic_tearकरोwn_this_cpu(पूर्णांक secondary);

/* Get the current cpu priority क्रम this cpu (0..15) */
बाह्य पूर्णांक mpic_cpu_get_priority(व्योम);

/* Set the current cpu priority क्रम this cpu */
बाह्य व्योम mpic_cpu_set_priority(पूर्णांक prio);

/* Request IPIs on primary mpic */
बाह्य व्योम mpic_request_ipis(व्योम);

/* Send a message (IPI) to a given target (cpu number or MSG_*) */
व्योम smp_mpic_message_pass(पूर्णांक target, पूर्णांक msg);

/* Unmask a specअगरic virq */
बाह्य व्योम mpic_unmask_irq(काष्ठा irq_data *d);
/* Mask a specअगरic virq */
बाह्य व्योम mpic_mask_irq(काष्ठा irq_data *d);
/* EOI a specअगरic virq */
बाह्य व्योम mpic_end_irq(काष्ठा irq_data *d);

/* Fetch पूर्णांकerrupt from a given mpic */
बाह्य अचिन्हित पूर्णांक mpic_get_one_irq(काष्ठा mpic *mpic);
/* This one माला_लो from the primary mpic */
बाह्य अचिन्हित पूर्णांक mpic_get_irq(व्योम);
/* This one माला_लो from the primary mpic via CoreInt*/
बाह्य अचिन्हित पूर्णांक mpic_get_coreपूर्णांक_irq(व्योम);
/* Fetch Machine Check पूर्णांकerrupt from primary mpic */
बाह्य अचिन्हित पूर्णांक mpic_get_mcirq(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_MPIC_H */
