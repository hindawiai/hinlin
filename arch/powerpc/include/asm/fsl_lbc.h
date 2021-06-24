<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Freescale Local Bus Controller
 *
 * Copyright तऊ 2006-2007, 2010 Freescale Semiconductor
 *
 * Authors: Nick Spence <nick.spence@मुक्तscale.com>,
 *          Scott Wood <scottwood@मुक्तscale.com>
 *          Jack Lan <jack.lan@मुक्तscale.com>
 */

#अगर_अघोषित __ASM_FSL_LBC_H
#घोषणा __ASM_FSL_LBC_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>

काष्ठा fsl_lbc_bank अणु
	__be32 br;             /**< Base Register  */
#घोषणा BR_BA           0xFFFF8000
#घोषणा BR_BA_SHIFT             15
#घोषणा BR_PS           0x00001800
#घोषणा BR_PS_SHIFT             11
#घोषणा BR_PS_8         0x00000800  /* Port Size 8 bit */
#घोषणा BR_PS_16        0x00001000  /* Port Size 16 bit */
#घोषणा BR_PS_32        0x00001800  /* Port Size 32 bit */
#घोषणा BR_DECC         0x00000600
#घोषणा BR_DECC_SHIFT            9
#घोषणा BR_DECC_OFF     0x00000000  /* HW ECC checking and generation off */
#घोषणा BR_DECC_CHK     0x00000200  /* HW ECC checking on, generation off */
#घोषणा BR_DECC_CHK_GEN 0x00000400  /* HW ECC checking and generation on */
#घोषणा BR_WP           0x00000100
#घोषणा BR_WP_SHIFT              8
#घोषणा BR_MSEL         0x000000E0
#घोषणा BR_MSEL_SHIFT            5
#घोषणा BR_MS_GPCM      0x00000000  /* GPCM */
#घोषणा BR_MS_FCM       0x00000020  /* FCM */
#घोषणा BR_MS_SDRAM     0x00000060  /* SDRAM */
#घोषणा BR_MS_UPMA      0x00000080  /* UPMA */
#घोषणा BR_MS_UPMB      0x000000A0  /* UPMB */
#घोषणा BR_MS_UPMC      0x000000C0  /* UPMC */
#घोषणा BR_V            0x00000001
#घोषणा BR_V_SHIFT               0
#घोषणा BR_RES          ~(BR_BA|BR_PS|BR_DECC|BR_WP|BR_MSEL|BR_V)

	__be32 or;             /**< Base Register  */
#घोषणा OR0 0x5004
#घोषणा OR1 0x500C
#घोषणा OR2 0x5014
#घोषणा OR3 0x501C
#घोषणा OR4 0x5024
#घोषणा OR5 0x502C
#घोषणा OR6 0x5034
#घोषणा OR7 0x503C

#घोषणा OR_FCM_AM               0xFFFF8000
#घोषणा OR_FCM_AM_SHIFT                 15
#घोषणा OR_FCM_BCTLD            0x00001000
#घोषणा OR_FCM_BCTLD_SHIFT              12
#घोषणा OR_FCM_PGS              0x00000400
#घोषणा OR_FCM_PGS_SHIFT                10
#घोषणा OR_FCM_CSCT             0x00000200
#घोषणा OR_FCM_CSCT_SHIFT                9
#घोषणा OR_FCM_CST              0x00000100
#घोषणा OR_FCM_CST_SHIFT                 8
#घोषणा OR_FCM_CHT              0x00000080
#घोषणा OR_FCM_CHT_SHIFT                 7
#घोषणा OR_FCM_SCY              0x00000070
#घोषणा OR_FCM_SCY_SHIFT                 4
#घोषणा OR_FCM_SCY_1            0x00000010
#घोषणा OR_FCM_SCY_2            0x00000020
#घोषणा OR_FCM_SCY_3            0x00000030
#घोषणा OR_FCM_SCY_4            0x00000040
#घोषणा OR_FCM_SCY_5            0x00000050
#घोषणा OR_FCM_SCY_6            0x00000060
#घोषणा OR_FCM_SCY_7            0x00000070
#घोषणा OR_FCM_RST              0x00000008
#घोषणा OR_FCM_RST_SHIFT                 3
#घोषणा OR_FCM_TRLX             0x00000004
#घोषणा OR_FCM_TRLX_SHIFT                2
#घोषणा OR_FCM_EHTR             0x00000002
#घोषणा OR_FCM_EHTR_SHIFT                1

#घोषणा OR_GPCM_AM		0xFFFF8000
#घोषणा OR_GPCM_AM_SHIFT		15
पूर्ण;

काष्ठा fsl_lbc_regs अणु
	काष्ठा fsl_lbc_bank bank[12];
	u8 res0[0x8];
	__be32 mar;             /**< UPM Address Register */
	u8 res1[0x4];
	__be32 mamr;            /**< UPMA Mode Register */
#घोषणा MxMR_OP_NO	(0 << 28) /**< normal operation */
#घोषणा MxMR_OP_WA	(1 << 28) /**< ग_लिखो array */
#घोषणा MxMR_OP_RA	(2 << 28) /**< पढ़ो array */
#घोषणा MxMR_OP_RP	(3 << 28) /**< run pattern */
#घोषणा MxMR_MAD	0x3f      /**< machine address */
	__be32 mbmr;            /**< UPMB Mode Register */
	__be32 mcmr;            /**< UPMC Mode Register */
	u8 res2[0x8];
	__be32 mrtpr;           /**< Memory Refresh Timer Prescaler Register */
	__be32 mdr;             /**< UPM Data Register */
	u8 res3[0x4];
	__be32 lsor;            /**< Special Operation Initiation Register */
	__be32 lsdmr;           /**< SDRAM Mode Register */
	u8 res4[0x8];
	__be32 lurt;            /**< UPM Refresh Timer */
	__be32 lsrt;            /**< SDRAM Refresh Timer */
	u8 res5[0x8];
	__be32 ltesr;           /**< Transfer Error Status Register */
#घोषणा LTESR_BM   0x80000000
#घोषणा LTESR_FCT  0x40000000
#घोषणा LTESR_PAR  0x20000000
#घोषणा LTESR_WP   0x04000000
#घोषणा LTESR_ATMW 0x00800000
#घोषणा LTESR_ATMR 0x00400000
#घोषणा LTESR_CS   0x00080000
#घोषणा LTESR_UPM  0x00000002
#घोषणा LTESR_CC   0x00000001
#घोषणा LTESR_न_अंकD_MASK (LTESR_FCT | LTESR_PAR | LTESR_CC)
#घोषणा LTESR_MASK      (LTESR_BM | LTESR_FCT | LTESR_PAR | LTESR_WP \
			 | LTESR_ATMW | LTESR_ATMR | LTESR_CS | LTESR_UPM \
			 | LTESR_CC)
#घोषणा LTESR_CLEAR	0xFFFFFFFF
#घोषणा LTECCR_CLEAR	0xFFFFFFFF
#घोषणा LTESR_STATUS	LTESR_MASK
#घोषणा LTEIR_ENABLE	LTESR_MASK
#घोषणा LTEDR_ENABLE	0x00000000
	__be32 ltedr;           /**< Transfer Error Disable Register */
	__be32 lteir;           /**< Transfer Error Interrupt Register */
	__be32 lteatr;          /**< Transfer Error Attributes Register */
	__be32 ltear;           /**< Transfer Error Address Register */
	__be32 lteccr;          /**< Transfer Error ECC Register */
	u8 res6[0x8];
	__be32 lbcr;            /**< Configuration Register */
#घोषणा LBCR_LDIS  0x80000000
#घोषणा LBCR_LDIS_SHIFT    31
#घोषणा LBCR_BCTLC 0x00C00000
#घोषणा LBCR_BCTLC_SHIFT   22
#घोषणा LBCR_AHD   0x00200000
#घोषणा LBCR_LPBSE 0x00020000
#घोषणा LBCR_LPBSE_SHIFT   17
#घोषणा LBCR_EPAR  0x00010000
#घोषणा LBCR_EPAR_SHIFT    16
#घोषणा LBCR_BMT   0x0000FF00
#घोषणा LBCR_BMT_SHIFT      8
#घोषणा LBCR_BMTPS 0x0000000F
#घोषणा LBCR_BMTPS_SHIFT    0
#घोषणा LBCR_INIT  0x00040000
	__be32 lcrr;            /**< Clock Ratio Register */
#घोषणा LCRR_DBYP    0x80000000
#घोषणा LCRR_DBYP_SHIFT      31
#घोषणा LCRR_BUFCMDC 0x30000000
#घोषणा LCRR_BUFCMDC_SHIFT   28
#घोषणा LCRR_ECL     0x03000000
#घोषणा LCRR_ECL_SHIFT       24
#घोषणा LCRR_EADC    0x00030000
#घोषणा LCRR_EADC_SHIFT      16
#घोषणा LCRR_CLKDIV  0x0000000F
#घोषणा LCRR_CLKDIV_SHIFT     0
	u8 res7[0x8];
	__be32 fmr;             /**< Flash Mode Register */
#घोषणा FMR_CWTO     0x0000F000
#घोषणा FMR_CWTO_SHIFT       12
#घोषणा FMR_BOOT     0x00000800
#घोषणा FMR_ECCM     0x00000100
#घोषणा FMR_AL       0x00000030
#घोषणा FMR_AL_SHIFT          4
#घोषणा FMR_OP       0x00000003
#घोषणा FMR_OP_SHIFT          0
	__be32 fir;             /**< Flash Inकाष्ठाion Register */
#घोषणा FIR_OP0      0xF0000000
#घोषणा FIR_OP0_SHIFT        28
#घोषणा FIR_OP1      0x0F000000
#घोषणा FIR_OP1_SHIFT        24
#घोषणा FIR_OP2      0x00F00000
#घोषणा FIR_OP2_SHIFT        20
#घोषणा FIR_OP3      0x000F0000
#घोषणा FIR_OP3_SHIFT        16
#घोषणा FIR_OP4      0x0000F000
#घोषणा FIR_OP4_SHIFT        12
#घोषणा FIR_OP5      0x00000F00
#घोषणा FIR_OP5_SHIFT         8
#घोषणा FIR_OP6      0x000000F0
#घोषणा FIR_OP6_SHIFT         4
#घोषणा FIR_OP7      0x0000000F
#घोषणा FIR_OP7_SHIFT         0
#घोषणा FIR_OP_NOP   0x0	/* No operation and end of sequence */
#घोषणा FIR_OP_CA    0x1        /* Issue current column address */
#घोषणा FIR_OP_PA    0x2        /* Issue current block+page address */
#घोषणा FIR_OP_UA    0x3        /* Issue user defined address */
#घोषणा FIR_OP_CM0   0x4        /* Issue command from FCR[CMD0] */
#घोषणा FIR_OP_CM1   0x5        /* Issue command from FCR[CMD1] */
#घोषणा FIR_OP_CM2   0x6        /* Issue command from FCR[CMD2] */
#घोषणा FIR_OP_CM3   0x7        /* Issue command from FCR[CMD3] */
#घोषणा FIR_OP_WB    0x8        /* Write FBCR bytes from FCM buffer */
#घोषणा FIR_OP_WS    0x9        /* Write 1 or 2 bytes from MDR[AS] */
#घोषणा FIR_OP_RB    0xA        /* Read FBCR bytes to FCM buffer */
#घोषणा FIR_OP_RS    0xB        /* Read 1 or 2 bytes to MDR[AS] */
#घोषणा FIR_OP_CW0   0xC        /* Wait then issue FCR[CMD0] */
#घोषणा FIR_OP_CW1   0xD        /* Wait then issue FCR[CMD1] */
#घोषणा FIR_OP_RBW   0xE        /* Wait then पढ़ो FBCR bytes */
#घोषणा FIR_OP_RSW   0xE        /* Wait then पढ़ो 1 or 2 bytes */
	__be32 fcr;             /**< Flash Command Register */
#घोषणा FCR_CMD0     0xFF000000
#घोषणा FCR_CMD0_SHIFT       24
#घोषणा FCR_CMD1     0x00FF0000
#घोषणा FCR_CMD1_SHIFT       16
#घोषणा FCR_CMD2     0x0000FF00
#घोषणा FCR_CMD2_SHIFT        8
#घोषणा FCR_CMD3     0x000000FF
#घोषणा FCR_CMD3_SHIFT        0
	__be32 fbar;            /**< Flash Block Address Register */
#घोषणा FBAR_BLK     0x00FFFFFF
	__be32 fpar;            /**< Flash Page Address Register */
#घोषणा FPAR_SP_PI   0x00007C00
#घोषणा FPAR_SP_PI_SHIFT     10
#घोषणा FPAR_SP_MS   0x00000200
#घोषणा FPAR_SP_CI   0x000001FF
#घोषणा FPAR_SP_CI_SHIFT      0
#घोषणा FPAR_LP_PI   0x0003F000
#घोषणा FPAR_LP_PI_SHIFT     12
#घोषणा FPAR_LP_MS   0x00000800
#घोषणा FPAR_LP_CI   0x000007FF
#घोषणा FPAR_LP_CI_SHIFT      0
	__be32 fbcr;            /**< Flash Byte Count Register */
#घोषणा FBCR_BC      0x00000FFF
पूर्ण;

/*
 * FSL UPM routines
 */
काष्ठा fsl_upm अणु
	__be32 __iomem *mxmr;
	पूर्णांक width;
पूर्ण;

बाह्य u32 fsl_lbc_addr(phys_addr_t addr_base);
बाह्य पूर्णांक fsl_lbc_find(phys_addr_t addr_base);
बाह्य पूर्णांक fsl_upm_find(phys_addr_t addr_base, काष्ठा fsl_upm *upm);

/**
 * fsl_upm_start_pattern - start UPM patterns execution
 * @upm:	poपूर्णांकer to the fsl_upm काष्ठाure obtained via fsl_upm_find
 * @pat_offset:	UPM pattern offset क्रम the command to be executed
 *
 * This routine programmes UPM so the next memory access that hits an UPM
 * will trigger pattern execution, starting at pat_offset.
 */
अटल अंतरभूत व्योम fsl_upm_start_pattern(काष्ठा fsl_upm *upm, u8 pat_offset)
अणु
	clrsetbits_be32(upm->mxmr, MxMR_MAD, MxMR_OP_RP | pat_offset);
पूर्ण

/**
 * fsl_upm_end_pattern - end UPM patterns execution
 * @upm:	poपूर्णांकer to the fsl_upm काष्ठाure obtained via fsl_upm_find
 *
 * This routine reverts UPM to normal operation mode.
 */
अटल अंतरभूत व्योम fsl_upm_end_pattern(काष्ठा fsl_upm *upm)
अणु
	clrbits32(upm->mxmr, MxMR_OP_RP);

	जबतक (in_be32(upm->mxmr) & MxMR_OP_RP)
		cpu_relax();
पूर्ण

/* overview of the fsl lbc controller */

काष्ठा fsl_lbc_ctrl अणु
	/* device info */
	काष्ठा device			*dev;
	काष्ठा fsl_lbc_regs __iomem	*regs;
	पूर्णांक				irq[2];
	रुको_queue_head_t		irq_रुको;
	spinlock_t			lock;
	व्योम				*nand;

	/* status पढ़ो from LTESR by irq handler */
	अचिन्हित पूर्णांक			irq_status;

#अगर_घोषित CONFIG_SUSPEND
	/* save regs when प्रणाली go to deep-sleep */
	काष्ठा fsl_lbc_regs		*saved_regs;
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक fsl_upm_run_pattern(काष्ठा fsl_upm *upm, व्योम __iomem *io_base,
			       u32 mar);
बाह्य काष्ठा fsl_lbc_ctrl *fsl_lbc_ctrl_dev;

#पूर्ण_अगर /* __ASM_FSL_LBC_H */
