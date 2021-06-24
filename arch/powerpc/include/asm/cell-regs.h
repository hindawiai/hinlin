<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cbe_regs.h
 *
 * This file is पूर्णांकended to hold the various रेजिस्टर definitions क्रम CBE
 * on-chip प्रणाली devices (memory controller, IO controller, etc...)
 *
 * (C) Copyright IBM Corporation 2001,2006
 *
 * Authors: Maximino Aguilar (maguilar@us.ibm.com)
 *          David J. Erb (djerb@us.ibm.com)
 *
 * (c) 2006 Benjamin Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 */

#अगर_अघोषित CBE_REGS_H
#घोषणा CBE_REGS_H

#समावेश <यंत्र/cell-pmu.h>

/*
 *
 * Some HID रेजिस्टर definitions
 *
 */

/* CBE specअगरic HID0 bits */
#घोषणा HID0_CBE_THERM_WAKEUP	0x0000020000000000ul
#घोषणा HID0_CBE_SYSERR_WAKEUP	0x0000008000000000ul
#घोषणा HID0_CBE_THERM_INT_EN	0x0000000400000000ul
#घोषणा HID0_CBE_SYSERR_INT_EN	0x0000000200000000ul

#घोषणा MAX_CBE		2

/*
 *
 * Pervasive unit रेजिस्टर definitions
 *
 */

जोड़ spe_reg अणु
	u64 val;
	u8 spe[8];
पूर्ण;

जोड़ ppe_spe_reg अणु
	u64 val;
	काष्ठा अणु
		u32 ppe;
		u32 spe;
	पूर्ण;
पूर्ण;


काष्ठा cbe_pmd_regs अणु
	/* Debug Bus Control */
	u64	pad_0x0000;					/* 0x0000 */

	u64	group_control;					/* 0x0008 */

	u8	pad_0x0010_0x00a8 [0x00a8 - 0x0010];		/* 0x0010 */

	u64	debug_bus_control;				/* 0x00a8 */

	u8	pad_0x00b0_0x0100 [0x0100 - 0x00b0];		/* 0x00b0 */

	u64	trace_aux_data;					/* 0x0100 */
	u64	trace_buffer_0_63;				/* 0x0108 */
	u64	trace_buffer_64_127;				/* 0x0110 */
	u64	trace_address;					/* 0x0118 */
	u64	ext_tr_समयr;					/* 0x0120 */

	u8	pad_0x0128_0x0400 [0x0400 - 0x0128];		/* 0x0128 */

	/* Perक्रमmance Monitor */
	u64	pm_status;					/* 0x0400 */
	u64	pm_control;					/* 0x0408 */
	u64	pm_पूर्णांकerval;					/* 0x0410 */
	u64	pm_ctr[4];					/* 0x0418 */
	u64	pm_start_stop;					/* 0x0438 */
	u64	pm07_control[8];				/* 0x0440 */

	u8	pad_0x0480_0x0800 [0x0800 - 0x0480];		/* 0x0480 */

	/* Thermal Sensor Registers */
	जोड़	spe_reg	ts_ctsr1;				/* 0x0800 */
	u64	ts_ctsr2;					/* 0x0808 */
	जोड़	spe_reg	ts_mtsr1;				/* 0x0810 */
	u64	ts_mtsr2;					/* 0x0818 */
	जोड़	spe_reg	ts_itr1;				/* 0x0820 */
	u64	ts_itr2;					/* 0x0828 */
	u64	ts_gitr;					/* 0x0830 */
	u64	ts_isr;						/* 0x0838 */
	u64	ts_imr;						/* 0x0840 */
	जोड़	spe_reg	पंचांग_cr1;					/* 0x0848 */
	u64	पंचांग_cr2;						/* 0x0850 */
	u64	पंचांग_simr;					/* 0x0858 */
	जोड़	ppe_spe_reg पंचांग_tpr;				/* 0x0860 */
	जोड़	spe_reg	पंचांग_str1;				/* 0x0868 */
	u64	पंचांग_str2;					/* 0x0870 */
	जोड़	ppe_spe_reg पंचांग_tsr;				/* 0x0878 */

	/* Power Management */
	u64	pmcr;						/* 0x0880 */
#घोषणा CBE_PMD_PAUSE_ZERO_CONTROL	0x10000
	u64	pmsr;						/* 0x0888 */

	/* Time Base Register */
	u64	tbr;						/* 0x0890 */

	u8	pad_0x0898_0x0c00 [0x0c00 - 0x0898];		/* 0x0898 */

	/* Fault Isolation Registers */
	u64	checkstop_fir;					/* 0x0c00 */
	u64	recoverable_fir;				/* 0x0c08 */
	u64	spec_att_mchk_fir;				/* 0x0c10 */
	u32	fir_mode_reg;					/* 0x0c18 */
	u8	pad_0x0c1c_0x0c20 [4];				/* 0x0c1c */
#घोषणा CBE_PMD_FIR_MODE_M8		0x00800
	u64	fir_enable_mask;				/* 0x0c20 */

	u8	pad_0x0c28_0x0ca8 [0x0ca8 - 0x0c28];		/* 0x0c28 */
	u64	ras_esc_0;					/* 0x0ca8 */
	u8	pad_0x0cb0_0x1000 [0x1000 - 0x0cb0];		/* 0x0cb0 */
पूर्ण;

बाह्य काष्ठा cbe_pmd_regs __iomem *cbe_get_pmd_regs(काष्ठा device_node *np);
बाह्य काष्ठा cbe_pmd_regs __iomem *cbe_get_cpu_pmd_regs(पूर्णांक cpu);

/*
 * PMU shaकरोw रेजिस्टरs
 *
 * Many of the रेजिस्टरs in the perक्रमmance monitoring unit are ग_लिखो-only,
 * so we need to save a copy of what we ग_लिखो to those रेजिस्टरs.
 *
 * The actual data counters are पढ़ो/ग_लिखो. However, writing to the counters
 * only takes effect अगर the PMU is enabled. Otherwise the value is stored in
 * a hardware latch until the next समय the PMU is enabled. So we save a copy
 * of the counter values अगर we need to पढ़ो them back जबतक the PMU is
 * disabled. The counter_value_in_latch field is a biपंचांगap indicating which
 * counters currently have a value रुकोing to be written.
 */

काष्ठा cbe_pmd_shaकरोw_regs अणु
	u32 group_control;
	u32 debug_bus_control;
	u32 trace_address;
	u32 ext_tr_समयr;
	u32 pm_status;
	u32 pm_control;
	u32 pm_पूर्णांकerval;
	u32 pm_start_stop;
	u32 pm07_control[NR_CTRS];

	u32 pm_ctr[NR_PHYS_CTRS];
	u32 counter_value_in_latch;
पूर्ण;

बाह्य काष्ठा cbe_pmd_shaकरोw_regs *cbe_get_pmd_shaकरोw_regs(काष्ठा device_node *np);
बाह्य काष्ठा cbe_pmd_shaकरोw_regs *cbe_get_cpu_pmd_shaकरोw_regs(पूर्णांक cpu);

/*
 *
 * IIC unit रेजिस्टर definitions
 *
 */

काष्ठा cbe_iic_pending_bits अणु
	u32 data;
	u8 flags;
	u8 class;
	u8 source;
	u8 prio;
पूर्ण;

#घोषणा CBE_IIC_IRQ_VALID	0x80
#घोषणा CBE_IIC_IRQ_IPI		0x40

काष्ठा cbe_iic_thपढ़ो_regs अणु
	काष्ठा cbe_iic_pending_bits pending;
	काष्ठा cbe_iic_pending_bits pending_destr;
	u64 generate;
	u64 prio;
पूर्ण;

काष्ठा cbe_iic_regs अणु
	u8	pad_0x0000_0x0400[0x0400 - 0x0000];		/* 0x0000 */

	/* IIC पूर्णांकerrupt रेजिस्टरs */
	काष्ठा	cbe_iic_thपढ़ो_regs thपढ़ो[2];			/* 0x0400 */

	u64	iic_ir;						/* 0x0440 */
#घोषणा CBE_IIC_IR_PRIO(x)      (((x) & 0xf) << 12)
#घोषणा CBE_IIC_IR_DEST_NODE(x) (((x) & 0xf) << 4)
#घोषणा CBE_IIC_IR_DEST_UNIT(x) ((x) & 0xf)
#घोषणा CBE_IIC_IR_IOC_0        0x0
#घोषणा CBE_IIC_IR_IOC_1S       0xb
#घोषणा CBE_IIC_IR_PT_0         0xe
#घोषणा CBE_IIC_IR_PT_1         0xf

	u64	iic_is;						/* 0x0448 */
#घोषणा CBE_IIC_IS_PMI		0x2

	u8	pad_0x0450_0x0500[0x0500 - 0x0450];		/* 0x0450 */

	/* IOC FIR */
	u64	ioc_fir_reset;					/* 0x0500 */
	u64	ioc_fir_set;					/* 0x0508 */
	u64	ioc_checkstop_enable;				/* 0x0510 */
	u64	ioc_fir_error_mask;				/* 0x0518 */
	u64	ioc_syserr_enable;				/* 0x0520 */
	u64	ioc_fir;					/* 0x0528 */

	u8	pad_0x0530_0x1000[0x1000 - 0x0530];		/* 0x0530 */
पूर्ण;

बाह्य काष्ठा cbe_iic_regs __iomem *cbe_get_iic_regs(काष्ठा device_node *np);
बाह्य काष्ठा cbe_iic_regs __iomem *cbe_get_cpu_iic_regs(पूर्णांक cpu);


काष्ठा cbe_mic_पंचांग_regs अणु
	u8	pad_0x0000_0x0040[0x0040 - 0x0000];		/* 0x0000 */

	u64	mic_ctl_cnfg2;					/* 0x0040 */
#घोषणा CBE_MIC_ENABLE_AUX_TRC		0x8000000000000000LL
#घोषणा CBE_MIC_DISABLE_PWR_SAV_2	0x0200000000000000LL
#घोषणा CBE_MIC_DISABLE_AUX_TRC_WRAP	0x0100000000000000LL
#घोषणा CBE_MIC_ENABLE_AUX_TRC_INT	0x0080000000000000LL

	u64	pad_0x0048;					/* 0x0048 */

	u64	mic_aux_trc_base;				/* 0x0050 */
	u64	mic_aux_trc_max_addr;				/* 0x0058 */
	u64	mic_aux_trc_cur_addr;				/* 0x0060 */
	u64	mic_aux_trc_grf_addr;				/* 0x0068 */
	u64	mic_aux_trc_grf_data;				/* 0x0070 */

	u64	pad_0x0078;					/* 0x0078 */

	u64	mic_ctl_cnfg_0;					/* 0x0080 */
#घोषणा CBE_MIC_DISABLE_PWR_SAV_0	0x8000000000000000LL

	u64	pad_0x0088;					/* 0x0088 */

	u64	slow_fast_समयr_0;				/* 0x0090 */
	u64	slow_next_समयr_0;				/* 0x0098 */

	u8	pad_0x00a0_0x00f8[0x00f8 - 0x00a0];		/* 0x00a0 */
	u64    	mic_df_ecc_address_0;				/* 0x00f8 */

	u8	pad_0x0100_0x01b8[0x01b8 - 0x0100];		/* 0x0100 */
	u64    	mic_df_ecc_address_1;				/* 0x01b8 */

	u64	mic_ctl_cnfg_1;					/* 0x01c0 */
#घोषणा CBE_MIC_DISABLE_PWR_SAV_1	0x8000000000000000LL

	u64	pad_0x01c8;					/* 0x01c8 */

	u64	slow_fast_समयr_1;				/* 0x01d0 */
	u64	slow_next_समयr_1;				/* 0x01d8 */

	u8	pad_0x01e0_0x0208[0x0208 - 0x01e0];		/* 0x01e0 */
	u64	mic_exc;					/* 0x0208 */
#घोषणा CBE_MIC_EXC_BLOCK_SCRUB		0x0800000000000000ULL
#घोषणा CBE_MIC_EXC_FAST_SCRUB		0x0100000000000000ULL

	u64	mic_mnt_cfg;					/* 0x0210 */
#घोषणा CBE_MIC_MNT_CFG_CHAN_0_POP	0x0002000000000000ULL
#घोषणा CBE_MIC_MNT_CFG_CHAN_1_POP	0x0004000000000000ULL

	u64	mic_df_config;					/* 0x0218 */
#घोषणा CBE_MIC_ECC_DISABLE_0		0x4000000000000000ULL
#घोषणा CBE_MIC_ECC_REP_SINGLE_0	0x2000000000000000ULL
#घोषणा CBE_MIC_ECC_DISABLE_1		0x0080000000000000ULL
#घोषणा CBE_MIC_ECC_REP_SINGLE_1	0x0040000000000000ULL

	u8	pad_0x0220_0x0230[0x0230 - 0x0220];		/* 0x0220 */
	u64	mic_fir;					/* 0x0230 */
#घोषणा CBE_MIC_FIR_ECC_SINGLE_0_ERR	0x0200000000000000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_0_ERR	0x0100000000000000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_1_ERR	0x0080000000000000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_1_ERR	0x0040000000000000ULL
#घोषणा CBE_MIC_FIR_ECC_ERR_MASK	0xffff000000000000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_0_CTE	0x0000020000000000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_0_CTE	0x0000010000000000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_1_CTE	0x0000008000000000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_1_CTE	0x0000004000000000ULL
#घोषणा CBE_MIC_FIR_ECC_CTE_MASK	0x0000ffff00000000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_0_RESET	0x0000000002000000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_0_RESET	0x0000000001000000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_1_RESET	0x0000000000800000ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_1_RESET	0x0000000000400000ULL
#घोषणा CBE_MIC_FIR_ECC_RESET_MASK	0x00000000ffff0000ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_0_SET	0x0000000000000200ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_0_SET	0x0000000000000100ULL
#घोषणा CBE_MIC_FIR_ECC_SINGLE_1_SET	0x0000000000000080ULL
#घोषणा CBE_MIC_FIR_ECC_MULTI_1_SET	0x0000000000000040ULL
#घोषणा CBE_MIC_FIR_ECC_SET_MASK	0x000000000000ffffULL
	u64	mic_fir_debug;					/* 0x0238 */

	u8	pad_0x0240_0x1000[0x1000 - 0x0240];		/* 0x0240 */
पूर्ण;

बाह्य काष्ठा cbe_mic_पंचांग_regs __iomem *cbe_get_mic_पंचांग_regs(काष्ठा device_node *np);
बाह्य काष्ठा cbe_mic_पंचांग_regs __iomem *cbe_get_cpu_mic_पंचांग_regs(पूर्णांक cpu);


/* Cell page table entries */
#घोषणा CBE_IOPTE_PP_W		0x8000000000000000ul /* protection: ग_लिखो */
#घोषणा CBE_IOPTE_PP_R		0x4000000000000000ul /* protection: पढ़ो */
#घोषणा CBE_IOPTE_M		0x2000000000000000ul /* coherency required */
#घोषणा CBE_IOPTE_SO_R		0x1000000000000000ul /* ordering: ग_लिखोs */
#घोषणा CBE_IOPTE_SO_RW		0x1800000000000000ul /* ordering: r & w */
#घोषणा CBE_IOPTE_RPN_Mask	0x07fffffffffff000ul /* RPN */
#घोषणा CBE_IOPTE_H		0x0000000000000800ul /* cache hपूर्णांक */
#घोषणा CBE_IOPTE_IOID_Mask	0x00000000000007fful /* ioid */

/* some utility functions to deal with SMT */
बाह्य u32 cbe_get_hw_thपढ़ो_id(पूर्णांक cpu);
बाह्य u32 cbe_cpu_to_node(पूर्णांक cpu);
बाह्य u32 cbe_node_to_cpu(पूर्णांक node);

/* Init this module early */
बाह्य व्योम cbe_regs_init(व्योम);


#पूर्ण_अगर /* CBE_REGS_H */
