<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_MIPS_CPS_H__
# error Please include यंत्र/mips-cps.h rather than यंत्र/mips-cm.h
#पूर्ण_अगर

#अगर_अघोषित __MIPS_ASM_MIPS_CM_H__
#घोषणा __MIPS_ASM_MIPS_CM_H__

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>

/* The base address of the CM GCR block */
बाह्य व्योम __iomem *mips_gcr_base;

/* The base address of the CM L2-only sync region */
बाह्य व्योम __iomem *mips_cm_l2sync_base;

/**
 * __mips_cm_phys_base - retrieve the physical base address of the CM
 *
 * This function वापसs the physical base address of the Coherence Manager
 * global control block, or 0 अगर no Coherence Manager is present. It provides
 * a शेष implementation which पढ़ोs the CMGCRBase रेजिस्टर where available,
 * and may be overridden by platक्रमms which determine this address in a
 * dअगरferent way by defining a function with the same prototype except क्रम the
 * name mips_cm_phys_base (without underscores).
 */
बाह्य phys_addr_t __mips_cm_phys_base(व्योम);

/*
 * mips_cm_is64 - determine CM रेजिस्टर width
 *
 * The CM रेजिस्टर width is determined by the version of the CM, with CM3
 * पूर्णांकroducing 64 bit GCRs and all prior CM versions having 32 bit GCRs.
 * However we may run a kernel built क्रम MIPS32 on a प्रणाली with 64 bit GCRs,
 * or vice-versa. This variable indicates the width of the memory accesses
 * that the kernel will perक्रमm to GCRs, which may dअगरfer from the actual
 * width of the GCRs.
 *
 * It's set to 0 क्रम 32-bit accesses and 1 क्रम 64-bit accesses.
 */
बाह्य पूर्णांक mips_cm_is64;

/**
 * mips_cm_error_report - Report CM cache errors
 */
#अगर_घोषित CONFIG_MIPS_CM
बाह्य व्योम mips_cm_error_report(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mips_cm_error_report(व्योम) अणुपूर्ण
#पूर्ण_अगर

/**
 * mips_cm_probe - probe क्रम a Coherence Manager
 *
 * Attempt to detect the presence of a Coherence Manager. Returns 0 अगर a CM
 * is successfully detected, अन्यथा -त्रुटि_सं.
 */
#अगर_घोषित CONFIG_MIPS_CM
बाह्य पूर्णांक mips_cm_probe(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक mips_cm_probe(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/**
 * mips_cm_present - determine whether a Coherence Manager is present
 *
 * Returns true अगर a CM is present in the प्रणाली, अन्यथा false.
 */
अटल अंतरभूत bool mips_cm_present(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_CM
	वापस mips_gcr_base != शून्य;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/**
 * mips_cm_has_l2sync - determine whether an L2-only sync region is present
 *
 * Returns true अगर the प्रणाली implements an L2-only sync region, अन्यथा false.
 */
अटल अंतरभूत bool mips_cm_has_l2sync(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_CM
	वापस mips_cm_l2sync_base != शून्य;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

/* Offsets to रेजिस्टर blocks from the CM base address */
#घोषणा MIPS_CM_GCB_OFS		0x0000 /* Global Control Block */
#घोषणा MIPS_CM_CLCB_OFS	0x2000 /* Core Local Control Block */
#घोषणा MIPS_CM_COCB_OFS	0x4000 /* Core Other Control Block */
#घोषणा MIPS_CM_GDB_OFS		0x6000 /* Global Debug Block */

/* Total size of the CM memory mapped रेजिस्टरs */
#घोषणा MIPS_CM_GCR_SIZE	0x8000

/* Size of the L2-only sync region */
#घोषणा MIPS_CM_L2SYNC_SIZE	0x1000

#घोषणा GCR_ACCESSOR_RO(sz, off, name)					\
	CPS_ACCESSOR_RO(gcr, sz, MIPS_CM_GCB_OFS + off, name)		\
	CPS_ACCESSOR_RO(gcr, sz, MIPS_CM_COCB_OFS + off, redir_##name)

#घोषणा GCR_ACCESSOR_RW(sz, off, name)					\
	CPS_ACCESSOR_RW(gcr, sz, MIPS_CM_GCB_OFS + off, name)		\
	CPS_ACCESSOR_RW(gcr, sz, MIPS_CM_COCB_OFS + off, redir_##name)

#घोषणा GCR_CX_ACCESSOR_RO(sz, off, name)				\
	CPS_ACCESSOR_RO(gcr, sz, MIPS_CM_CLCB_OFS + off, cl_##name)	\
	CPS_ACCESSOR_RO(gcr, sz, MIPS_CM_COCB_OFS + off, co_##name)

#घोषणा GCR_CX_ACCESSOR_RW(sz, off, name)				\
	CPS_ACCESSOR_RW(gcr, sz, MIPS_CM_CLCB_OFS + off, cl_##name)	\
	CPS_ACCESSOR_RW(gcr, sz, MIPS_CM_COCB_OFS + off, co_##name)

/* GCR_CONFIG - Inक्रमmation about the प्रणाली */
GCR_ACCESSOR_RO(64, 0x000, config)
#घोषणा CM_GCR_CONFIG_CLUSTER_COH_CAPABLE	BIT_ULL(43)
#घोषणा CM_GCR_CONFIG_CLUSTER_ID		GENMASK_ULL(39, 32)
#घोषणा CM_GCR_CONFIG_NUM_CLUSTERS		GENMASK(29, 23)
#घोषणा CM_GCR_CONFIG_NUMIOCU			GENMASK(15, 8)
#घोषणा CM_GCR_CONFIG_PCORES			GENMASK(7, 0)

/* GCR_BASE - Base address of the Global Configuration Registers (GCRs) */
GCR_ACCESSOR_RW(64, 0x008, base)
#घोषणा CM_GCR_BASE_GCRBASE			GENMASK_ULL(47, 15)
#घोषणा CM_GCR_BASE_CMDEFTGT			GENMASK(1, 0)
#घोषणा  CM_GCR_BASE_CMDEFTGT_MEM		0
#घोषणा  CM_GCR_BASE_CMDEFTGT_RESERVED		1
#घोषणा  CM_GCR_BASE_CMDEFTGT_IOCU0		2
#घोषणा  CM_GCR_BASE_CMDEFTGT_IOCU1		3

/* GCR_ACCESS - Controls core/IOCU access to GCRs */
GCR_ACCESSOR_RW(32, 0x020, access)
#घोषणा CM_GCR_ACCESS_ACCESSEN			GENMASK(7, 0)

/* GCR_REV - Indicates the Coherence Manager revision */
GCR_ACCESSOR_RO(32, 0x030, rev)
#घोषणा CM_GCR_REV_MAJOR			GENMASK(15, 8)
#घोषणा CM_GCR_REV_MINOR			GENMASK(7, 0)

#घोषणा CM_ENCODE_REV(major, minor) \
		(((major) << __ffs(CM_GCR_REV_MAJOR)) | \
		 ((minor) << __ffs(CM_GCR_REV_MINOR)))

#घोषणा CM_REV_CM2				CM_ENCODE_REV(6, 0)
#घोषणा CM_REV_CM2_5				CM_ENCODE_REV(7, 0)
#घोषणा CM_REV_CM3				CM_ENCODE_REV(8, 0)
#घोषणा CM_REV_CM3_5				CM_ENCODE_REV(9, 0)

/* GCR_ERR_CONTROL - Control error checking logic */
GCR_ACCESSOR_RW(32, 0x038, err_control)
#घोषणा CM_GCR_ERR_CONTROL_L2_ECC_EN		BIT(1)
#घोषणा CM_GCR_ERR_CONTROL_L2_ECC_SUPPORT	BIT(0)

/* GCR_ERR_MASK - Control which errors are reported as पूर्णांकerrupts */
GCR_ACCESSOR_RW(64, 0x040, error_mask)

/* GCR_ERR_CAUSE - Indicates the type of error that occurred */
GCR_ACCESSOR_RW(64, 0x048, error_cause)
#घोषणा CM_GCR_ERROR_CAUSE_ERRTYPE		GENMASK(31, 27)
#घोषणा CM3_GCR_ERROR_CAUSE_ERRTYPE		GENMASK_ULL(63, 58)
#घोषणा CM_GCR_ERROR_CAUSE_ERRINFO		GENMASK(26, 0)

/* GCR_ERR_ADDR - Indicates the address associated with an error */
GCR_ACCESSOR_RW(64, 0x050, error_addr)

/* GCR_ERR_MULT - Indicates when multiple errors have occurred */
GCR_ACCESSOR_RW(64, 0x058, error_mult)
#घोषणा CM_GCR_ERROR_MULT_ERR2ND		GENMASK(4, 0)

/* GCR_L2_ONLY_SYNC_BASE - Base address of the L2 cache-only sync region */
GCR_ACCESSOR_RW(64, 0x070, l2_only_sync_base)
#घोषणा CM_GCR_L2_ONLY_SYNC_BASE_SYNCBASE	GENMASK(31, 12)
#घोषणा CM_GCR_L2_ONLY_SYNC_BASE_SYNCEN		BIT(0)

/* GCR_GIC_BASE - Base address of the Global Interrupt Controller (GIC) */
GCR_ACCESSOR_RW(64, 0x080, gic_base)
#घोषणा CM_GCR_GIC_BASE_GICBASE			GENMASK(31, 17)
#घोषणा CM_GCR_GIC_BASE_GICEN			BIT(0)

/* GCR_CPC_BASE - Base address of the Cluster Power Controller (CPC) */
GCR_ACCESSOR_RW(64, 0x088, cpc_base)
#घोषणा CM_GCR_CPC_BASE_CPCBASE			GENMASK(31, 15)
#घोषणा CM_GCR_CPC_BASE_CPCEN			BIT(0)

/* GCR_REGn_BASE - Base addresses of CM address regions */
GCR_ACCESSOR_RW(64, 0x090, reg0_base)
GCR_ACCESSOR_RW(64, 0x0a0, reg1_base)
GCR_ACCESSOR_RW(64, 0x0b0, reg2_base)
GCR_ACCESSOR_RW(64, 0x0c0, reg3_base)
#घोषणा CM_GCR_REGn_BASE_BASEADDR		GENMASK(31, 16)

/* GCR_REGn_MASK - Size & destination of CM address regions */
GCR_ACCESSOR_RW(64, 0x098, reg0_mask)
GCR_ACCESSOR_RW(64, 0x0a8, reg1_mask)
GCR_ACCESSOR_RW(64, 0x0b8, reg2_mask)
GCR_ACCESSOR_RW(64, 0x0c8, reg3_mask)
#घोषणा CM_GCR_REGn_MASK_ADDRMASK		GENMASK(31, 16)
#घोषणा CM_GCR_REGn_MASK_CCAOVR			GENMASK(7, 5)
#घोषणा CM_GCR_REGn_MASK_CCAOVREN		BIT(4)
#घोषणा CM_GCR_REGn_MASK_DROPL2			BIT(2)
#घोषणा CM_GCR_REGn_MASK_CMTGT			GENMASK(1, 0)
#घोषणा  CM_GCR_REGn_MASK_CMTGT_DISABLED	0x0
#घोषणा  CM_GCR_REGn_MASK_CMTGT_MEM		0x1
#घोषणा  CM_GCR_REGn_MASK_CMTGT_IOCU0		0x2
#घोषणा  CM_GCR_REGn_MASK_CMTGT_IOCU1		0x3

/* GCR_GIC_STATUS - Indicates presence of a Global Interrupt Controller (GIC) */
GCR_ACCESSOR_RO(32, 0x0d0, gic_status)
#घोषणा CM_GCR_GIC_STATUS_EX			BIT(0)

/* GCR_CPC_STATUS - Indicates presence of a Cluster Power Controller (CPC) */
GCR_ACCESSOR_RO(32, 0x0f0, cpc_status)
#घोषणा CM_GCR_CPC_STATUS_EX			BIT(0)

/* GCR_L2_CONFIG - Indicates L2 cache configuration when Config5.L2C=1 */
GCR_ACCESSOR_RW(32, 0x130, l2_config)
#घोषणा CM_GCR_L2_CONFIG_BYPASS			BIT(20)
#घोषणा CM_GCR_L2_CONFIG_SET_SIZE		GENMASK(15, 12)
#घोषणा CM_GCR_L2_CONFIG_LINE_SIZE		GENMASK(11, 8)
#घोषणा CM_GCR_L2_CONFIG_ASSOC			GENMASK(7, 0)

/* GCR_SYS_CONFIG2 - Further inक्रमmation about the प्रणाली */
GCR_ACCESSOR_RO(32, 0x150, sys_config2)
#घोषणा CM_GCR_SYS_CONFIG2_MAXVPW		GENMASK(3, 0)

/* GCR_L2_PFT_CONTROL - Controls hardware L2 prefetching */
GCR_ACCESSOR_RW(32, 0x300, l2_pft_control)
#घोषणा CM_GCR_L2_PFT_CONTROL_PAGEMASK		GENMASK(31, 12)
#घोषणा CM_GCR_L2_PFT_CONTROL_PFTEN		BIT(8)
#घोषणा CM_GCR_L2_PFT_CONTROL_NPFT		GENMASK(7, 0)

/* GCR_L2_PFT_CONTROL_B - Controls hardware L2 prefetching */
GCR_ACCESSOR_RW(32, 0x308, l2_pft_control_b)
#घोषणा CM_GCR_L2_PFT_CONTROL_B_CEN		BIT(8)
#घोषणा CM_GCR_L2_PFT_CONTROL_B_PORTID		GENMASK(7, 0)

/* GCR_L2SM_COP - L2 cache op state machine control */
GCR_ACCESSOR_RW(32, 0x620, l2sm_cop)
#घोषणा CM_GCR_L2SM_COP_PRESENT			BIT(31)
#घोषणा CM_GCR_L2SM_COP_RESULT			GENMASK(8, 6)
#घोषणा  CM_GCR_L2SM_COP_RESULT_DONTCARE	0
#घोषणा  CM_GCR_L2SM_COP_RESULT_DONE_OK		1
#घोषणा  CM_GCR_L2SM_COP_RESULT_DONE_ERROR	2
#घोषणा  CM_GCR_L2SM_COP_RESULT_ABORT_OK	3
#घोषणा  CM_GCR_L2SM_COP_RESULT_ABORT_ERROR	4
#घोषणा CM_GCR_L2SM_COP_RUNNING			BIT(5)
#घोषणा CM_GCR_L2SM_COP_TYPE			GENMASK(4, 2)
#घोषणा  CM_GCR_L2SM_COP_TYPE_IDX_WBINV		0
#घोषणा  CM_GCR_L2SM_COP_TYPE_IDX_STORETAG	1
#घोषणा  CM_GCR_L2SM_COP_TYPE_IDX_STORETAGDATA	2
#घोषणा  CM_GCR_L2SM_COP_TYPE_HIT_INV		4
#घोषणा  CM_GCR_L2SM_COP_TYPE_HIT_WBINV		5
#घोषणा  CM_GCR_L2SM_COP_TYPE_HIT_WB		6
#घोषणा  CM_GCR_L2SM_COP_TYPE_FETCHLOCK		7
#घोषणा CM_GCR_L2SM_COP_CMD			GENMASK(1, 0)
#घोषणा  CM_GCR_L2SM_COP_CMD_START		1	/* only when idle */
#घोषणा  CM_GCR_L2SM_COP_CMD_ABORT		3	/* only when running */

/* GCR_L2SM_TAG_ADDR_COP - L2 cache op state machine address control */
GCR_ACCESSOR_RW(64, 0x628, l2sm_tag_addr_cop)
#घोषणा CM_GCR_L2SM_TAG_ADDR_COP_NUM_LINES	GENMASK_ULL(63, 48)
#घोषणा CM_GCR_L2SM_TAG_ADDR_COP_START_TAG	GENMASK_ULL(47, 6)

/* GCR_BEV_BASE - Controls the location of the BEV क्रम घातered up cores */
GCR_ACCESSOR_RW(64, 0x680, bev_base)

/* GCR_Cx_RESET_RELEASE - Controls core reset क्रम CM 1.x */
GCR_CX_ACCESSOR_RW(32, 0x000, reset_release)

/* GCR_Cx_COHERENCE - Controls core coherence */
GCR_CX_ACCESSOR_RW(32, 0x008, coherence)
#घोषणा CM_GCR_Cx_COHERENCE_COHDOMAINEN		GENMASK(7, 0)
#घोषणा CM3_GCR_Cx_COHERENCE_COHEN		BIT(0)

/* GCR_Cx_CONFIG - Inक्रमmation about a core's configuration */
GCR_CX_ACCESSOR_RO(32, 0x010, config)
#घोषणा CM_GCR_Cx_CONFIG_IOCUTYPE		GENMASK(11, 10)
#घोषणा CM_GCR_Cx_CONFIG_PVPE			GENMASK(9, 0)

/* GCR_Cx_OTHER - Configure the core-other/redirect GCR block */
GCR_CX_ACCESSOR_RW(32, 0x018, other)
#घोषणा CM_GCR_Cx_OTHER_CORENUM			GENMASK(31, 16)	/* CM < 3 */
#घोषणा CM_GCR_Cx_OTHER_CLUSTER_EN		BIT(31)		/* CM >= 3.5 */
#घोषणा CM_GCR_Cx_OTHER_GIC_EN			BIT(30)		/* CM >= 3.5 */
#घोषणा CM_GCR_Cx_OTHER_BLOCK			GENMASK(25, 24)	/* CM >= 3.5 */
#घोषणा  CM_GCR_Cx_OTHER_BLOCK_LOCAL		0
#घोषणा  CM_GCR_Cx_OTHER_BLOCK_GLOBAL		1
#घोषणा  CM_GCR_Cx_OTHER_BLOCK_USER		2
#घोषणा  CM_GCR_Cx_OTHER_BLOCK_GLOBAL_HIGH	3
#घोषणा CM_GCR_Cx_OTHER_CLUSTER			GENMASK(21, 16)	/* CM >= 3.5 */
#घोषणा CM3_GCR_Cx_OTHER_CORE			GENMASK(13, 8)	/* CM >= 3 */
#घोषणा  CM_GCR_Cx_OTHER_CORE_CM		32
#घोषणा CM3_GCR_Cx_OTHER_VP			GENMASK(2, 0)	/* CM >= 3 */

/* GCR_Cx_RESET_BASE - Configure where घातered up cores will fetch from */
GCR_CX_ACCESSOR_RW(32, 0x020, reset_base)
#घोषणा CM_GCR_Cx_RESET_BASE_BEVEXCBASE		GENMASK(31, 12)

/* GCR_Cx_ID - Identअगरy the current core */
GCR_CX_ACCESSOR_RO(32, 0x028, id)
#घोषणा CM_GCR_Cx_ID_CLUSTER			GENMASK(15, 8)
#घोषणा CM_GCR_Cx_ID_CORE			GENMASK(7, 0)

/* GCR_Cx_RESET_EXT_BASE - Configure behaviour when cores reset or घातer up */
GCR_CX_ACCESSOR_RW(32, 0x030, reset_ext_base)
#घोषणा CM_GCR_Cx_RESET_EXT_BASE_EVARESET	BIT(31)
#घोषणा CM_GCR_Cx_RESET_EXT_BASE_UEB		BIT(30)
#घोषणा CM_GCR_Cx_RESET_EXT_BASE_BEVEXCMASK	GENMASK(27, 20)
#घोषणा CM_GCR_Cx_RESET_EXT_BASE_BEVEXCPA	GENMASK(7, 1)
#घोषणा CM_GCR_Cx_RESET_EXT_BASE_PRESENT	BIT(0)

/**
 * mips_cm_l2sync - perक्रमm an L2-only sync operation
 *
 * If an L2-only sync region is present in the प्रणाली then this function
 * perक्रमms and L2-only sync and वापसs zero. Otherwise it वापसs -ENODEV.
 */
अटल अंतरभूत पूर्णांक mips_cm_l2sync(व्योम)
अणु
	अगर (!mips_cm_has_l2sync())
		वापस -ENODEV;

	ग_लिखोl(0, mips_cm_l2sync_base);
	वापस 0;
पूर्ण

/**
 * mips_cm_revision() - वापस CM revision
 *
 * Return: The revision of the CM, from GCR_REV, or 0 अगर no CM is present. The
 * वापस value should be checked against the CM_REV_* macros.
 */
अटल अंतरभूत पूर्णांक mips_cm_revision(व्योम)
अणु
	अगर (!mips_cm_present())
		वापस 0;

	वापस पढ़ो_gcr_rev();
पूर्ण

/**
 * mips_cm_max_vp_width() - वापस the width in bits of VP indices
 *
 * Return: the width, in bits, of VP indices in fields that combine core & VP
 * indices.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cm_max_vp_width(व्योम)
अणु
	बाह्य पूर्णांक smp_num_siblings;
	uपूर्णांक32_t cfg;

	अगर (mips_cm_revision() >= CM_REV_CM3)
		वापस पढ़ो_gcr_sys_config2() & CM_GCR_SYS_CONFIG2_MAXVPW;

	अगर (mips_cm_present()) अणु
		/*
		 * We presume that all cores in the प्रणाली will have the same
		 * number of VP(E)s, and अगर that ever changes then this will
		 * need revisiting.
		 */
		cfg = पढ़ो_gcr_cl_config() & CM_GCR_Cx_CONFIG_PVPE;
		वापस (cfg >> __ffs(CM_GCR_Cx_CONFIG_PVPE)) + 1;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_SMP))
		वापस smp_num_siblings;

	वापस 1;
पूर्ण

/**
 * mips_cm_vp_id() - calculate the hardware VP ID क्रम a CPU
 * @cpu: the CPU whose VP ID to calculate
 *
 * Hardware such as the GIC uses identअगरiers क्रम VPs which may not match the
 * CPU numbers used by Linux. This function calculates the hardware VP
 * identअगरier corresponding to a given CPU.
 *
 * Return: the VP ID क्रम the CPU.
 */
अटल अंतरभूत अचिन्हित पूर्णांक mips_cm_vp_id(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक core = cpu_core(&cpu_data[cpu]);
	अचिन्हित पूर्णांक vp = cpu_vpe_id(&cpu_data[cpu]);

	वापस (core * mips_cm_max_vp_width()) + vp;
पूर्ण

#अगर_घोषित CONFIG_MIPS_CM

/**
 * mips_cm_lock_other - lock access to redirect/other region
 * @cluster: the other cluster to be accessed
 * @core: the other core to be accessed
 * @vp: the VP within the other core to be accessed
 * @block: the रेजिस्टर block to be accessed
 *
 * Configure the redirect/other region क्रम the local core/VP (depending upon
 * the CM revision) to target the specअगरied @cluster, @core, @vp & रेजिस्टर
 * @block. Must be called beक्रमe using the redirect/other region, and followed
 * by a call to mips_cm_unlock_other() when access to the redirect/other region
 * is complete.
 *
 * This function acquires a spinlock such that code between it &
 * mips_cm_unlock_other() calls cannot be pre-empted by anything which may
 * reconfigure the redirect/other region, and cannot be पूर्णांकerfered with by
 * another VP in the core. As such calls to this function should not be nested.
 */
बाह्य व्योम mips_cm_lock_other(अचिन्हित पूर्णांक cluster, अचिन्हित पूर्णांक core,
			       अचिन्हित पूर्णांक vp, अचिन्हित पूर्णांक block);

/**
 * mips_cm_unlock_other - unlock access to redirect/other region
 *
 * Must be called after mips_cm_lock_other() once all required access to the
 * redirect/other region has been completed.
 */
बाह्य व्योम mips_cm_unlock_other(व्योम);

#अन्यथा /* !CONFIG_MIPS_CM */

अटल अंतरभूत व्योम mips_cm_lock_other(अचिन्हित पूर्णांक cluster, अचिन्हित पूर्णांक core,
				      अचिन्हित पूर्णांक vp, अचिन्हित पूर्णांक block) अणु पूर्ण
अटल अंतरभूत व्योम mips_cm_unlock_other(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_CM */

/**
 * mips_cm_lock_other_cpu - lock access to redirect/other region
 * @cpu: the other CPU whose रेजिस्टर we want to access
 *
 * Configure the redirect/other region क्रम the local core/VP (depending upon
 * the CM revision) to target the specअगरied @cpu & रेजिस्टर @block. This is
 * equivalent to calling mips_cm_lock_other() but accepts a Linux CPU number
 * क्रम convenience.
 */
अटल अंतरभूत व्योम mips_cm_lock_other_cpu(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक block)
अणु
	काष्ठा cpuinfo_mips *d = &cpu_data[cpu];

	mips_cm_lock_other(cpu_cluster(d), cpu_core(d), cpu_vpe_id(d), block);
पूर्ण

#पूर्ण_अगर /* __MIPS_ASM_MIPS_CM_H__ */
