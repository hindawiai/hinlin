<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2008 by Sascha Hauer <kernel@pengutronix.de>
 */

#अगर_अघोषित __ARCH_ARM_MACH_MX3_CRM_REGS_H__
#घोषणा __ARCH_ARM_MACH_MX3_CRM_REGS_H__

#घोषणा CKIH_CLK_FREQ           26000000
#घोषणा CKIH_CLK_FREQ_27MHZ     27000000
#घोषणा CKIL_CLK_FREQ           32768

बाह्य व्योम __iomem *mx3_ccm_base;

/* Register addresses */
#घोषणा MXC_CCM_CCMR		0x00
#घोषणा MXC_CCM_PDR0		0x04
#घोषणा MXC_CCM_PDR1		0x08
#घोषणा MX35_CCM_PDR2		0x0C
#घोषणा MXC_CCM_RCSR		0x0C
#घोषणा MX35_CCM_PDR3		0x10
#घोषणा MXC_CCM_MPCTL		0x10
#घोषणा MX35_CCM_PDR4		0x14
#घोषणा MXC_CCM_UPCTL		0x14
#घोषणा MX35_CCM_RCSR		0x18
#घोषणा MXC_CCM_SRPCTL		0x18
#घोषणा MX35_CCM_MPCTL		0x1C
#घोषणा MXC_CCM_COSR		0x1C
#घोषणा MX35_CCM_PPCTL		0x20
#घोषणा MXC_CCM_CGR0		0x20
#घोषणा MX35_CCM_ACMR		0x24
#घोषणा MXC_CCM_CGR1		0x24
#घोषणा MX35_CCM_COSR		0x28
#घोषणा MXC_CCM_CGR2		0x28
#घोषणा MX35_CCM_CGR0		0x2C
#घोषणा MXC_CCM_WIMR		0x2C
#घोषणा MX35_CCM_CGR1		0x30
#घोषणा MXC_CCM_LDC		0x30
#घोषणा MX35_CCM_CGR2		0x34
#घोषणा MXC_CCM_DCVR0		0x34
#घोषणा MX35_CCM_CGR3		0x38
#घोषणा MXC_CCM_DCVR1		0x38
#घोषणा MXC_CCM_DCVR2		0x3C
#घोषणा MXC_CCM_DCVR3		0x40
#घोषणा MXC_CCM_LTR0		0x44
#घोषणा MXC_CCM_LTR1		0x48
#घोषणा MXC_CCM_LTR2		0x4C
#घोषणा MXC_CCM_LTR3		0x50
#घोषणा MXC_CCM_LTBR0		0x54
#घोषणा MXC_CCM_LTBR1		0x58
#घोषणा MXC_CCM_PMCR0		0x5C
#घोषणा MXC_CCM_PMCR1		0x60
#घोषणा MXC_CCM_PDR2		0x64

/* Register bit definitions */
#घोषणा MXC_CCM_CCMR_WBEN                       (1 << 27)
#घोषणा MXC_CCM_CCMR_CSCS                       (1 << 25)
#घोषणा MXC_CCM_CCMR_PERCS                      (1 << 24)
#घोषणा MXC_CCM_CCMR_SSI1S_OFFSET               18
#घोषणा MXC_CCM_CCMR_SSI1S_MASK                 (0x3 << 18)
#घोषणा MXC_CCM_CCMR_SSI2S_OFFSET               21
#घोषणा MXC_CCM_CCMR_SSI2S_MASK                 (0x3 << 21)
#घोषणा MXC_CCM_CCMR_LPM_OFFSET                 14
#घोषणा MXC_CCM_CCMR_LPM_MASK                   (0x3 << 14)
#घोषणा MXC_CCM_CCMR_LPM_WAIT_MX35		(0x1 << 14)
#घोषणा MXC_CCM_CCMR_FIRS_OFFSET                11
#घोषणा MXC_CCM_CCMR_FIRS_MASK                  (0x3 << 11)
#घोषणा MXC_CCM_CCMR_UPE                        (1 << 9)
#घोषणा MXC_CCM_CCMR_SPE                        (1 << 8)
#घोषणा MXC_CCM_CCMR_MDS                        (1 << 7)
#घोषणा MXC_CCM_CCMR_SBYCS                      (1 << 4)
#घोषणा MXC_CCM_CCMR_MPE                        (1 << 3)
#घोषणा MXC_CCM_CCMR_PRCS_OFFSET                1
#घोषणा MXC_CCM_CCMR_PRCS_MASK                  (0x3 << 1)

#घोषणा MXC_CCM_PDR0_CSI_PODF_OFFSET            26
#घोषणा MXC_CCM_PDR0_CSI_PODF_MASK              (0x3F << 26)
#घोषणा MXC_CCM_PDR0_CSI_PRDF_OFFSET            23
#घोषणा MXC_CCM_PDR0_CSI_PRDF_MASK              (0x7 << 23)
#घोषणा MXC_CCM_PDR0_PER_PODF_OFFSET            16
#घोषणा MXC_CCM_PDR0_PER_PODF_MASK              (0x1F << 16)
#घोषणा MXC_CCM_PDR0_HSP_PODF_OFFSET            11
#घोषणा MXC_CCM_PDR0_HSP_PODF_MASK              (0x7 << 11)
#घोषणा MXC_CCM_PDR0_NFC_PODF_OFFSET            8
#घोषणा MXC_CCM_PDR0_NFC_PODF_MASK              (0x7 << 8)
#घोषणा MXC_CCM_PDR0_IPG_PODF_OFFSET            6
#घोषणा MXC_CCM_PDR0_IPG_PODF_MASK              (0x3 << 6)
#घोषणा MXC_CCM_PDR0_MAX_PODF_OFFSET            3
#घोषणा MXC_CCM_PDR0_MAX_PODF_MASK              (0x7 << 3)
#घोषणा MXC_CCM_PDR0_MCU_PODF_OFFSET            0
#घोषणा MXC_CCM_PDR0_MCU_PODF_MASK              0x7

#घोषणा MXC_CCM_PDR1_USB_PRDF_OFFSET            30
#घोषणा MXC_CCM_PDR1_USB_PRDF_MASK              (0x3 << 30)
#घोषणा MXC_CCM_PDR1_USB_PODF_OFFSET            27
#घोषणा MXC_CCM_PDR1_USB_PODF_MASK              (0x7 << 27)
#घोषणा MXC_CCM_PDR1_FIRI_PRE_PODF_OFFSET       24
#घोषणा MXC_CCM_PDR1_FIRI_PRE_PODF_MASK         (0x7 << 24)
#घोषणा MXC_CCM_PDR1_FIRI_PODF_OFFSET           18
#घोषणा MXC_CCM_PDR1_FIRI_PODF_MASK             (0x3F << 18)
#घोषणा MXC_CCM_PDR1_SSI2_PRE_PODF_OFFSET       15
#घोषणा MXC_CCM_PDR1_SSI2_PRE_PODF_MASK         (0x7 << 15)
#घोषणा MXC_CCM_PDR1_SSI2_PODF_OFFSET           9
#घोषणा MXC_CCM_PDR1_SSI2_PODF_MASK             (0x3F << 9)
#घोषणा MXC_CCM_PDR1_SSI1_PRE_PODF_OFFSET       6
#घोषणा MXC_CCM_PDR1_SSI1_PRE_PODF_MASK         (0x7 << 6)
#घोषणा MXC_CCM_PDR1_SSI1_PODF_OFFSET           0
#घोषणा MXC_CCM_PDR1_SSI1_PODF_MASK             0x3F

/* Bit definitions क्रम RCSR */
#घोषणा MXC_CCM_RCSR_NF16B			0x80000000

/*
 * LTR0 रेजिस्टर offsets
 */
#घोषणा MXC_CCM_LTR0_DIV3CK_OFFSET              1
#घोषणा MXC_CCM_LTR0_DIV3CK_MASK                (0x3 << 1)
#घोषणा MXC_CCM_LTR0_DNTHR_OFFSET               16
#घोषणा MXC_CCM_LTR0_DNTHR_MASK                 (0x3F << 16)
#घोषणा MXC_CCM_LTR0_UPTHR_OFFSET               22
#घोषणा MXC_CCM_LTR0_UPTHR_MASK                 (0x3F << 22)

/*
 * LTR1 रेजिस्टर offsets
 */
#घोषणा MXC_CCM_LTR1_PNCTHR_OFFSET              0
#घोषणा MXC_CCM_LTR1_PNCTHR_MASK                0x3F
#घोषणा MXC_CCM_LTR1_UPCNT_OFFSET               6
#घोषणा MXC_CCM_LTR1_UPCNT_MASK                 (0xFF << 6)
#घोषणा MXC_CCM_LTR1_DNCNT_OFFSET               14
#घोषणा MXC_CCM_LTR1_DNCNT_MASK                 (0xFF << 14)
#घोषणा MXC_CCM_LTR1_LTBRSR_MASK                0x400000
#घोषणा MXC_CCM_LTR1_LTBRSR_OFFSET              22
#घोषणा MXC_CCM_LTR1_LTBRSR                     0x400000
#घोषणा MXC_CCM_LTR1_LTBRSH                     0x800000

/*
 * LTR2 bit definitions. x ranges from 0 क्रम WSW9 to 6 क्रम WSW15
 */
#घोषणा MXC_CCM_LTR2_WSW_OFFSET(x)              (11 + (x) * 3)
#घोषणा MXC_CCM_LTR2_WSW_MASK(x)                (0x7 << \
					MXC_CCM_LTR2_WSW_OFFSET((x)))
#घोषणा MXC_CCM_LTR2_EMAC_OFFSET                0
#घोषणा MXC_CCM_LTR2_EMAC_MASK                  0x1FF

/*
 * LTR3 bit definitions. x ranges from 0 क्रम WSW0 to 8 क्रम WSW8
 */
#घोषणा MXC_CCM_LTR3_WSW_OFFSET(x)              (5 + (x) * 3)
#घोषणा MXC_CCM_LTR3_WSW_MASK(x)                (0x7 << \
					MXC_CCM_LTR3_WSW_OFFSET((x)))

#घोषणा MXC_CCM_PMCR0_DFSUP1                    0x80000000
#घोषणा MXC_CCM_PMCR0_DFSUP1_SPLL               (0 << 31)
#घोषणा MXC_CCM_PMCR0_DFSUP1_MPLL               (1 << 31)
#घोषणा MXC_CCM_PMCR0_DFSUP0                    0x40000000
#घोषणा MXC_CCM_PMCR0_DFSUP0_PLL                (0 << 30)
#घोषणा MXC_CCM_PMCR0_DFSUP0_PDR                (1 << 30)
#घोषणा MXC_CCM_PMCR0_DFSUP_MASK                (0x3 << 30)

#घोषणा DVSUP_TURBO				0
#घोषणा DVSUP_HIGH				1
#घोषणा DVSUP_MEDIUM				2
#घोषणा DVSUP_LOW				3
#घोषणा MXC_CCM_PMCR0_DVSUP_TURBO               (DVSUP_TURBO << 28)
#घोषणा MXC_CCM_PMCR0_DVSUP_HIGH                (DVSUP_HIGH << 28)
#घोषणा MXC_CCM_PMCR0_DVSUP_MEDIUM              (DVSUP_MEDIUM << 28)
#घोषणा MXC_CCM_PMCR0_DVSUP_LOW                 (DVSUP_LOW << 28)
#घोषणा MXC_CCM_PMCR0_DVSUP_OFFSET              28
#घोषणा MXC_CCM_PMCR0_DVSUP_MASK                (0x3 << 28)
#घोषणा MXC_CCM_PMCR0_UDSC                      0x08000000
#घोषणा MXC_CCM_PMCR0_UDSC_MASK                 (1 << 27)
#घोषणा MXC_CCM_PMCR0_UDSC_UP                   (1 << 27)
#घोषणा MXC_CCM_PMCR0_UDSC_DOWN                 (0 << 27)

#घोषणा MXC_CCM_PMCR0_VSCNT_1                   (0x0 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_2                   (0x1 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_3                   (0x2 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_4                   (0x3 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_5                   (0x4 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_6                   (0x5 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_7                   (0x6 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_8                   (0x7 << 24)
#घोषणा MXC_CCM_PMCR0_VSCNT_OFFSET              24
#घोषणा MXC_CCM_PMCR0_VSCNT_MASK                (0x7 << 24)
#घोषणा MXC_CCM_PMCR0_DVFEV                     0x00800000
#घोषणा MXC_CCM_PMCR0_DVFIS                     0x00400000
#घोषणा MXC_CCM_PMCR0_LBMI                      0x00200000
#घोषणा MXC_CCM_PMCR0_LBFL                      0x00100000
#घोषणा MXC_CCM_PMCR0_LBCF_4                    (0x0 << 18)
#घोषणा MXC_CCM_PMCR0_LBCF_8                    (0x1 << 18)
#घोषणा MXC_CCM_PMCR0_LBCF_12                   (0x2 << 18)
#घोषणा MXC_CCM_PMCR0_LBCF_16                   (0x3 << 18)
#घोषणा MXC_CCM_PMCR0_LBCF_OFFSET               18
#घोषणा MXC_CCM_PMCR0_LBCF_MASK                 (0x3 << 18)
#घोषणा MXC_CCM_PMCR0_PTVIS                     0x00020000
#घोषणा MXC_CCM_PMCR0_UPDTEN                    0x00010000
#घोषणा MXC_CCM_PMCR0_UPDTEN_MASK               (0x1 << 16)
#घोषणा MXC_CCM_PMCR0_FSVAIM                    0x00008000
#घोषणा MXC_CCM_PMCR0_FSVAI_OFFSET              13
#घोषणा MXC_CCM_PMCR0_FSVAI_MASK                (0x3 << 13)
#घोषणा MXC_CCM_PMCR0_DPVCR                     0x00001000
#घोषणा MXC_CCM_PMCR0_DPVV                      0x00000800
#घोषणा MXC_CCM_PMCR0_WFIM                      0x00000400
#घोषणा MXC_CCM_PMCR0_DRCE3                     0x00000200
#घोषणा MXC_CCM_PMCR0_DRCE2                     0x00000100
#घोषणा MXC_CCM_PMCR0_DRCE1                     0x00000080
#घोषणा MXC_CCM_PMCR0_DRCE0                     0x00000040
#घोषणा MXC_CCM_PMCR0_DCR                       0x00000020
#घोषणा MXC_CCM_PMCR0_DVFEN                     0x00000010
#घोषणा MXC_CCM_PMCR0_PTVAIM                    0x00000008
#घोषणा MXC_CCM_PMCR0_PTVAI_OFFSET              1
#घोषणा MXC_CCM_PMCR0_PTVAI_MASK                (0x3 << 1)
#घोषणा MXC_CCM_PMCR0_DPTEN                     0x00000001

#घोषणा MXC_CCM_PMCR1_DVGP_OFFSET               0
#घोषणा MXC_CCM_PMCR1_DVGP_MASK                 (0xF)

#घोषणा MXC_CCM_PMCR1_PLLRDIS                      (0x1 << 7)
#घोषणा MXC_CCM_PMCR1_EMIRQ_EN                      (0x1 << 8)

#घोषणा MXC_CCM_DCVR_ULV_MASK                   (0x3FF << 22)
#घोषणा MXC_CCM_DCVR_ULV_OFFSET                 22
#घोषणा MXC_CCM_DCVR_LLV_MASK                   (0x3FF << 12)
#घोषणा MXC_CCM_DCVR_LLV_OFFSET                 12
#घोषणा MXC_CCM_DCVR_ELV_MASK                   (0x3FF << 2)
#घोषणा MXC_CCM_DCVR_ELV_OFFSET                 2

#घोषणा MXC_CCM_PDR2_MST2_PDF_MASK              (0x3F << 7)
#घोषणा MXC_CCM_PDR2_MST2_PDF_OFFSET            7
#घोषणा MXC_CCM_PDR2_MST1_PDF_MASK              0x3F
#घोषणा MXC_CCM_PDR2_MST1_PDF_OFFSET            0

#घोषणा MXC_CCM_COSR_CLKOSEL_MASK               0x0F
#घोषणा MXC_CCM_COSR_CLKOSEL_OFFSET             0
#घोषणा MXC_CCM_COSR_CLKOUTDIV_MASK             (0x07 << 6)
#घोषणा MXC_CCM_COSR_CLKOUTDIV_OFFSET           6
#घोषणा MXC_CCM_COSR_CLKOEN                     (1 << 9)

/*
 * PMCR0 रेजिस्टर offsets
 */
#घोषणा MXC_CCM_PMCR0_LBFL_OFFSET   20
#घोषणा MXC_CCM_PMCR0_DFSUP0_OFFSET 30
#घोषणा MXC_CCM_PMCR0_DFSUP1_OFFSET 31

#पूर्ण_अगर				/* __ARCH_ARM_MACH_MX3_CRM_REGS_H__ */
