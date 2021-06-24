<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_ARCREGS_H
#घोषणा _ASM_ARC_ARCREGS_H

/* Build Configuration Registers */
#घोषणा ARC_REG_AUX_DCCM	0x18	/* DCCM Base Addr ARCv2 */
#घोषणा ARC_REG_ERP_CTRL	0x3F	/* ARCv2 Error protection control */
#घोषणा ARC_REG_DCCM_BASE_BUILD	0x61	/* DCCM Base Addr ARCompact */
#घोषणा ARC_REG_CRC_BCR		0x62
#घोषणा ARC_REG_VECBASE_BCR	0x68
#घोषणा ARC_REG_PERIBASE_BCR	0x69
#घोषणा ARC_REG_FP_BCR		0x6B	/* ARCompact: Single-Precision FPU */
#घोषणा ARC_REG_DPFP_BCR	0x6C	/* ARCompact: Dbl Precision FPU */
#घोषणा ARC_REG_ERP_BUILD	0xc7	/* ARCv2 Error protection Build: ECC/Parity */
#घोषणा ARC_REG_FP_V2_BCR	0xc8	/* ARCv2 FPU */
#घोषणा ARC_REG_SLC_BCR		0xce
#घोषणा ARC_REG_DCCM_BUILD	0x74	/* DCCM size (common) */
#घोषणा ARC_REG_AP_BCR		0x76
#घोषणा ARC_REG_ICCM_BUILD	0x78	/* ICCM size (common) */
#घोषणा ARC_REG_XY_MEM_BCR	0x79
#घोषणा ARC_REG_MAC_BCR		0x7a
#घोषणा ARC_REG_MUL_BCR		0x7b
#घोषणा ARC_REG_SWAP_BCR	0x7c
#घोषणा ARC_REG_NORM_BCR	0x7d
#घोषणा ARC_REG_MIXMAX_BCR	0x7e
#घोषणा ARC_REG_BARREL_BCR	0x7f
#घोषणा ARC_REG_D_UNCACH_BCR	0x6A
#घोषणा ARC_REG_BPU_BCR		0xc0
#घोषणा ARC_REG_ISA_CFG_BCR	0xc1
#घोषणा ARC_REG_LPB_BUILD	0xE9	/* ARCv2 Loop Buffer Build */
#घोषणा ARC_REG_RTT_BCR		0xF2
#घोषणा ARC_REG_IRQ_BCR		0xF3
#घोषणा ARC_REG_MICRO_ARCH_BCR	0xF9	/* ARCv2 Product revision */
#घोषणा ARC_REG_SMART_BCR	0xFF
#घोषणा ARC_REG_CLUSTER_BCR	0xcf
#घोषणा ARC_REG_AUX_ICCM	0x208	/* ICCM Base Addr (ARCv2) */
#घोषणा ARC_REG_LPB_CTRL	0x488	/* ARCv2 Loop Buffer control */
#घोषणा ARC_REG_FPU_CTRL	0x300
#घोषणा ARC_REG_FPU_STATUS	0x301

/* Common क्रम ARCompact and ARCv2 status रेजिस्टर */
#घोषणा ARC_REG_STATUS32	0x0A

/* status32 Bits Positions */
#घोषणा STATUS_AE_BIT		5	/* Exception active */
#घोषणा STATUS_DE_BIT		6	/* PC is in delay slot */
#घोषणा STATUS_U_BIT		7	/* User/Kernel mode */
#घोषणा STATUS_Z_BIT            11
#घोषणा STATUS_L_BIT		12	/* Loop inhibit */

/* These masks correspond to the status word(STATUS_32) bits */
#घोषणा STATUS_AE_MASK		(1<<STATUS_AE_BIT)
#घोषणा STATUS_DE_MASK		(1<<STATUS_DE_BIT)
#घोषणा STATUS_U_MASK		(1<<STATUS_U_BIT)
#घोषणा STATUS_Z_MASK		(1<<STATUS_Z_BIT)
#घोषणा STATUS_L_MASK		(1<<STATUS_L_BIT)

/*
 * ECR: Exception Cause Reg bits-n-pieces
 * [23:16] = Exception Vector
 * [15: 8] = Exception Cause Code
 * [ 7: 0] = Exception Parameters (क्रम certain types only)
 */
#अगर_घोषित CONFIG_ISA_ARCOMPACT
#घोषणा ECR_V_MEM_ERR			0x01
#घोषणा ECR_V_INSN_ERR			0x02
#घोषणा ECR_V_MACH_CHK			0x20
#घोषणा ECR_V_ITLB_MISS			0x21
#घोषणा ECR_V_DTLB_MISS			0x22
#घोषणा ECR_V_PROTV			0x23
#घोषणा ECR_V_TRAP			0x25
#अन्यथा
#घोषणा ECR_V_MEM_ERR			0x01
#घोषणा ECR_V_INSN_ERR			0x02
#घोषणा ECR_V_MACH_CHK			0x03
#घोषणा ECR_V_ITLB_MISS			0x04
#घोषणा ECR_V_DTLB_MISS			0x05
#घोषणा ECR_V_PROTV			0x06
#घोषणा ECR_V_TRAP			0x09
#घोषणा ECR_V_MISALIGN			0x0d
#पूर्ण_अगर

/* DTLB Miss and Protection Violation Cause Codes */

#घोषणा ECR_C_PROTV_INST_FETCH		0x00
#घोषणा ECR_C_PROTV_LOAD		0x01
#घोषणा ECR_C_PROTV_STORE		0x02
#घोषणा ECR_C_PROTV_XCHG		0x03
#घोषणा ECR_C_PROTV_MISALIG_DATA	0x04

#घोषणा ECR_C_BIT_PROTV_MISALIG_DATA	10

/* Machine Check Cause Code Values */
#घोषणा ECR_C_MCHK_DUP_TLB		0x01

/* DTLB Miss Exception Cause Code Values */
#घोषणा ECR_C_BIT_DTLB_LD_MISS		8
#घोषणा ECR_C_BIT_DTLB_ST_MISS		9

/* Auxiliary रेजिस्टरs */
#घोषणा AUX_IDENTITY		4
#घोषणा AUX_EXEC_CTRL		8
#घोषणा AUX_INTR_VEC_BASE	0x25
#घोषणा AUX_VOL			0x5e

/*
 * Floating Pt Registers
 * Status regs are पढ़ो-only (build-समय) so need not be saved/restored
 */
#घोषणा ARC_AUX_FP_STAT         0x300
#घोषणा ARC_AUX_DPFP_1L         0x301
#घोषणा ARC_AUX_DPFP_1H         0x302
#घोषणा ARC_AUX_DPFP_2L         0x303
#घोषणा ARC_AUX_DPFP_2H         0x304
#घोषणा ARC_AUX_DPFP_STAT       0x305

/*
 * DSP-related रेजिस्टरs
 * Registers names must correspond to dsp_callee_regs काष्ठाure fields names
 * क्रम स्वतःmatic offset calculation in DSP_AUX_SAVE_RESTORE macros.
 */
#घोषणा ARC_AUX_DSP_BUILD	0x7A
#घोषणा ARC_AUX_ACC0_LO		0x580
#घोषणा ARC_AUX_ACC0_GLO	0x581
#घोषणा ARC_AUX_ACC0_HI		0x582
#घोषणा ARC_AUX_ACC0_GHI	0x583
#घोषणा ARC_AUX_DSP_BFLY0	0x598
#घोषणा ARC_AUX_DSP_CTRL	0x59F
#घोषणा ARC_AUX_DSP_FFT_CTRL	0x59E

#घोषणा ARC_AUX_AGU_BUILD	0xCC
#घोषणा ARC_AUX_AGU_AP0		0x5C0
#घोषणा ARC_AUX_AGU_AP1		0x5C1
#घोषणा ARC_AUX_AGU_AP2		0x5C2
#घोषणा ARC_AUX_AGU_AP3		0x5C3
#घोषणा ARC_AUX_AGU_OS0		0x5D0
#घोषणा ARC_AUX_AGU_OS1		0x5D1
#घोषणा ARC_AUX_AGU_MOD0	0x5E0
#घोषणा ARC_AUX_AGU_MOD1	0x5E1
#घोषणा ARC_AUX_AGU_MOD2	0x5E2
#घोषणा ARC_AUX_AGU_MOD3	0x5E3

#अगर_अघोषित __ASSEMBLY__

#समावेश <soc/arc/aux.h>

/* Helpers */
#घोषणा TO_KB(bytes)		((bytes) >> 10)
#घोषणा TO_MB(bytes)		(TO_KB(bytes) >> 10)
#घोषणा PAGES_TO_KB(n_pages)	((n_pages) << (PAGE_SHIFT - 10))
#घोषणा PAGES_TO_MB(n_pages)	(PAGES_TO_KB(n_pages) >> 10)


/*
 ***************************************************************
 * Build Configuration Registers, with encoded hardware config
 */
काष्ठा bcr_identity अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक chip_id:16, cpu_id:8, family:8;
#अन्यथा
	अचिन्हित पूर्णांक family:8, cpu_id:8, chip_id:16;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_isa_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक भाग_rem:4, pad2:4, ldd:1, unalign:1, atomic:1, be:1,
		     pad1:12, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, pad1:12, be:1, atomic:1, unalign:1,
		     ldd:1, pad2:4, भाग_rem:4;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_uarch_build_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:8, prod:8, maj:8, min:8;
#अन्यथा
	अचिन्हित पूर्णांक min:8, maj:8, prod:8, pad:8;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_mpy अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:8, x1616:8, dsp:4, cycles:2, type:2, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, type:2, cycles:2, dsp:4, x1616:8, pad:8;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_iccm_arcompact अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक base:16, pad:5, sz:3, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, sz:3, pad:5, base:16;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_iccm_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:8, sz11:4, sz01:4, sz10:4, sz00:4, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, sz00:4, sz10:4, sz01:4, sz11:4, pad:8;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_dccm_arcompact अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक res:21, sz:3, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, sz:3, res:21;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_dccm_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad2:12, cyc:3, pad1:1, sz1:4, sz0:4, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, sz0:4, sz1:4, pad1:1, cyc:3, pad2:12;
#पूर्ण_अगर
पूर्ण;

/* ARCompact: Both SP and DP FPU BCRs have same क्रमmat */
काष्ठा bcr_fp_arcompact अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक fast:1, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, fast:1;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_fp_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad2:15, dp:1, pad1:7, sp:1, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, sp:1, pad1:7, dp:1, pad2:15;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_actionpoपूर्णांक अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:21, min:1, num:2, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, num:2, min:1, pad:21;
#पूर्ण_अगर
पूर्ण;

#समावेश <soc/arc/समयrs.h>

काष्ठा bcr_bpu_arcompact अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad2:19, fam:1, pad:2, ent:2, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, ent:2, pad:2, fam:1, pad2:19;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_bpu_arcv2 अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:6, fbe:2, tqe:2, ts:4, ft:1, rse:2, pte:3, bce:3, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, bce:3, pte:3, rse:2, ft:1, ts:4, tqe:2, fbe:2, pad:6;
#पूर्ण_अगर
पूर्ण;

/* Error Protection Build: ECC/Parity */
काष्ठा bcr_erp अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad3:5, mmu:3, pad2:4, ic:3, dc:3, pad1:6, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, pad1:6, dc:3, ic:3, pad2:4, mmu:3, pad3:5;
#पूर्ण_अगर
पूर्ण;

/* Error Protection Control */
काष्ठा ctl_erp अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad2:27, mpd:1, pad1:2, dpd:1, dpi:1;
#अन्यथा
	अचिन्हित पूर्णांक dpi:1, dpd:1, pad1:2, mpd:1, pad2:27;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_lpb अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:16, entries:8, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, entries:8, pad:16;
#पूर्ण_अगर
पूर्ण;

काष्ठा bcr_generic अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक info:24, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, info:24;
#पूर्ण_अगर
पूर्ण;

/*
 *******************************************************************
 * Generic काष्ठाures to hold build configuration used at runसमय
 */

काष्ठा cpuinfo_arc_mmu अणु
	अचिन्हित पूर्णांक ver:4, pg_sz_k:8, s_pg_sz_m:8, pad:10, sasid:1, pae:1;
	अचिन्हित पूर्णांक sets:12, ways:4, u_dtlb:8, u_itlb:8;
पूर्ण;

काष्ठा cpuinfo_arc_cache अणु
	अचिन्हित पूर्णांक sz_k:14, line_len:8, assoc:4, alias:1, vipt:1, pad:4;
पूर्ण;

काष्ठा cpuinfo_arc_bpu अणु
	अचिन्हित पूर्णांक ver, full, num_cache, num_pred, ret_stk;
पूर्ण;

काष्ठा cpuinfo_arc_ccm अणु
	अचिन्हित पूर्णांक base_addr, sz;
पूर्ण;

काष्ठा cpuinfo_arc अणु
	काष्ठा cpuinfo_arc_cache icache, dcache, slc;
	काष्ठा cpuinfo_arc_mmu mmu;
	काष्ठा cpuinfo_arc_bpu bpu;
	काष्ठा bcr_identity core;
	काष्ठा bcr_isa_arcv2 isa;
	स्थिर अक्षर *release, *name;
	अचिन्हित पूर्णांक vec_base;
	काष्ठा cpuinfo_arc_ccm iccm, dccm;
	काष्ठा अणु
		अचिन्हित पूर्णांक swap:1, norm:1, minmax:1, barrel:1, crc:1, swape:1, pad1:2,
			     fpu_sp:1, fpu_dp:1, dual:1, dual_enb:1, pad2:4,
			     ap_num:4, ap_full:1, smart:1, rtt:1, pad3:1,
			     समयr0:1, समयr1:1, rtc:1, gfrc:1, pad4:4;
	पूर्ण extn;
	काष्ठा bcr_mpy extn_mpy;
पूर्ण;

बाह्य काष्ठा cpuinfo_arc cpuinfo_arc700[];

अटल अंतरभूत पूर्णांक is_isa_arcv2(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ISA_ARCV2);
पूर्ण

अटल अंतरभूत पूर्णांक is_isa_arcompact(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ISA_ARCOMPACT);
पूर्ण

#पूर्ण_अगर /* __ASEMBLY__ */

#पूर्ण_अगर /* _ASM_ARC_ARCREGS_H */
