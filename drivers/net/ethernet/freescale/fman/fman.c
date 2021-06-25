<शैली गुरु>
/*
 * Copyright 2008-2015 Freescale Semiconductor Inc.
 * Copyright 2020 NXP
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fsl/guts.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/libfdt_env.h>

#समावेश "fman.h"
#समावेश "fman_muram.h"
#समावेश "fman_keygen.h"

/* General defines */
#घोषणा FMAN_LIODN_TBL			64	/* size of LIODN table */
#घोषणा MAX_NUM_OF_MACS			10
#घोषणा FM_NUM_OF_FMAN_CTRL_EVENT_REGS	4
#घोषणा BASE_RX_PORTID			0x08
#घोषणा BASE_TX_PORTID			0x28

/* Modules रेजिस्टरs offsets */
#घोषणा BMI_OFFSET		0x00080000
#घोषणा QMI_OFFSET		0x00080400
#घोषणा KG_OFFSET		0x000C1000
#घोषणा DMA_OFFSET		0x000C2000
#घोषणा FPM_OFFSET		0x000C3000
#घोषणा IMEM_OFFSET		0x000C4000
#घोषणा HWP_OFFSET		0x000C7000
#घोषणा CGP_OFFSET		0x000DB000

/* Exceptions bit map */
#घोषणा EX_DMA_BUS_ERROR		0x80000000
#घोषणा EX_DMA_READ_ECC			0x40000000
#घोषणा EX_DMA_SYSTEM_WRITE_ECC	0x20000000
#घोषणा EX_DMA_FM_WRITE_ECC		0x10000000
#घोषणा EX_FPM_STALL_ON_TASKS		0x08000000
#घोषणा EX_FPM_SINGLE_ECC		0x04000000
#घोषणा EX_FPM_DOUBLE_ECC		0x02000000
#घोषणा EX_QMI_SINGLE_ECC		0x01000000
#घोषणा EX_QMI_DEQ_FROM_UNKNOWN_PORTID	0x00800000
#घोषणा EX_QMI_DOUBLE_ECC		0x00400000
#घोषणा EX_BMI_LIST_RAM_ECC		0x00200000
#घोषणा EX_BMI_STORAGE_PROखाता_ECC	0x00100000
#घोषणा EX_BMI_STATISTICS_RAM_ECC	0x00080000
#घोषणा EX_IRAM_ECC			0x00040000
#घोषणा EX_MURAM_ECC			0x00020000
#घोषणा EX_BMI_DISPATCH_RAM_ECC	0x00010000
#घोषणा EX_DMA_SINGLE_PORT_ECC		0x00008000

/* DMA defines */
/* masks */
#घोषणा DMA_MODE_BER			0x00200000
#घोषणा DMA_MODE_ECC			0x00000020
#घोषणा DMA_MODE_SECURE_PROT		0x00000800
#घोषणा DMA_MODE_AXI_DBG_MASK		0x0F000000

#घोषणा DMA_TRANSFER_PORTID_MASK	0xFF000000
#घोषणा DMA_TRANSFER_TNUM_MASK		0x00FF0000
#घोषणा DMA_TRANSFER_LIODN_MASK	0x00000FFF

#घोषणा DMA_STATUS_BUS_ERR		0x08000000
#घोषणा DMA_STATUS_READ_ECC		0x04000000
#घोषणा DMA_STATUS_SYSTEM_WRITE_ECC	0x02000000
#घोषणा DMA_STATUS_FM_WRITE_ECC	0x01000000
#घोषणा DMA_STATUS_FM_SPDAT_ECC	0x00080000

#घोषणा DMA_MODE_CACHE_OR_SHIFT		30
#घोषणा DMA_MODE_AXI_DBG_SHIFT			24
#घोषणा DMA_MODE_CEN_SHIFT			13
#घोषणा DMA_MODE_CEN_MASK			0x00000007
#घोषणा DMA_MODE_DBG_SHIFT			7
#घोषणा DMA_MODE_AID_MODE_SHIFT		4

#घोषणा DMA_THRESH_COMMQ_SHIFT			24
#घोषणा DMA_THRESH_READ_INT_BUF_SHIFT		16
#घोषणा DMA_THRESH_READ_INT_BUF_MASK		0x0000003f
#घोषणा DMA_THRESH_WRITE_INT_BUF_MASK		0x0000003f

#घोषणा DMA_TRANSFER_PORTID_SHIFT		24
#घोषणा DMA_TRANSFER_TNUM_SHIFT		16

#घोषणा DMA_CAM_SIZखातापूर्ण_ENTRY			0x40
#घोषणा DMA_CAM_UNITS				8

#घोषणा DMA_LIODN_SHIFT		16
#घोषणा DMA_LIODN_BASE_MASK	0x00000FFF

/* FPM defines */
#घोषणा FPM_EV_MASK_DOUBLE_ECC		0x80000000
#घोषणा FPM_EV_MASK_STALL		0x40000000
#घोषणा FPM_EV_MASK_SINGLE_ECC		0x20000000
#घोषणा FPM_EV_MASK_RELEASE_FM		0x00010000
#घोषणा FPM_EV_MASK_DOUBLE_ECC_EN	0x00008000
#घोषणा FPM_EV_MASK_STALL_EN		0x00004000
#घोषणा FPM_EV_MASK_SINGLE_ECC_EN	0x00002000
#घोषणा FPM_EV_MASK_EXTERNAL_HALT	0x00000008
#घोषणा FPM_EV_MASK_ECC_ERR_HALT	0x00000004

#घोषणा FPM_RAM_MURAM_ECC		0x00008000
#घोषणा FPM_RAM_IRAM_ECC		0x00004000
#घोषणा FPM_IRAM_ECC_ERR_EX_EN		0x00020000
#घोषणा FPM_MURAM_ECC_ERR_EX_EN	0x00040000
#घोषणा FPM_RAM_IRAM_ECC_EN		0x40000000
#घोषणा FPM_RAM_RAMS_ECC_EN		0x80000000
#घोषणा FPM_RAM_RAMS_ECC_EN_SRC_SEL	0x08000000

#घोषणा FPM_REV1_MAJOR_MASK		0x0000FF00
#घोषणा FPM_REV1_MINOR_MASK		0x000000FF

#घोषणा FPM_DISP_LIMIT_SHIFT		24

#घोषणा FPM_PRT_FM_CTL1			0x00000001
#घोषणा FPM_PRT_FM_CTL2			0x00000002
#घोषणा FPM_PORT_FM_CTL_PORTID_SHIFT	24
#घोषणा FPM_PRC_ORA_FM_CTL_SEL_SHIFT	16

#घोषणा FPM_THR1_PRS_SHIFT		24
#घोषणा FPM_THR1_KG_SHIFT		16
#घोषणा FPM_THR1_PLCR_SHIFT		8
#घोषणा FPM_THR1_BMI_SHIFT		0

#घोषणा FPM_THR2_QMI_ENQ_SHIFT		24
#घोषणा FPM_THR2_QMI_DEQ_SHIFT		0
#घोषणा FPM_THR2_FM_CTL1_SHIFT		16
#घोषणा FPM_THR2_FM_CTL2_SHIFT		8

#घोषणा FPM_EV_MASK_CAT_ERR_SHIFT	1
#घोषणा FPM_EV_MASK_DMA_ERR_SHIFT	0

#घोषणा FPM_REV1_MAJOR_SHIFT		8

#घोषणा FPM_RSTC_FM_RESET		0x80000000
#घोषणा FPM_RSTC_MAC0_RESET		0x40000000
#घोषणा FPM_RSTC_MAC1_RESET		0x20000000
#घोषणा FPM_RSTC_MAC2_RESET		0x10000000
#घोषणा FPM_RSTC_MAC3_RESET		0x08000000
#घोषणा FPM_RSTC_MAC8_RESET		0x04000000
#घोषणा FPM_RSTC_MAC4_RESET		0x02000000
#घोषणा FPM_RSTC_MAC5_RESET		0x01000000
#घोषणा FPM_RSTC_MAC6_RESET		0x00800000
#घोषणा FPM_RSTC_MAC7_RESET		0x00400000
#घोषणा FPM_RSTC_MAC9_RESET		0x00200000

#घोषणा FPM_TS_INT_SHIFT		16
#घोषणा FPM_TS_CTL_EN			0x80000000

/* BMI defines */
#घोषणा BMI_INIT_START				0x80000000
#घोषणा BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC	0x80000000
#घोषणा BMI_ERR_INTR_EN_LIST_RAM_ECC		0x40000000
#घोषणा BMI_ERR_INTR_EN_STATISTICS_RAM_ECC	0x20000000
#घोषणा BMI_ERR_INTR_EN_DISPATCH_RAM_ECC	0x10000000
#घोषणा BMI_NUM_OF_TASKS_MASK			0x3F000000
#घोषणा BMI_NUM_OF_EXTRA_TASKS_MASK		0x000F0000
#घोषणा BMI_NUM_OF_DMAS_MASK			0x00000F00
#घोषणा BMI_NUM_OF_EXTRA_DMAS_MASK		0x0000000F
#घोषणा BMI_FIFO_SIZE_MASK			0x000003FF
#घोषणा BMI_EXTRA_FIFO_SIZE_MASK		0x03FF0000
#घोषणा BMI_CFG2_DMAS_MASK			0x0000003F
#घोषणा BMI_CFG2_TASKS_MASK			0x0000003F

#घोषणा BMI_CFG2_TASKS_SHIFT		16
#घोषणा BMI_CFG2_DMAS_SHIFT		0
#घोषणा BMI_CFG1_FIFO_SIZE_SHIFT	16
#घोषणा BMI_NUM_OF_TASKS_SHIFT		24
#घोषणा BMI_EXTRA_NUM_OF_TASKS_SHIFT	16
#घोषणा BMI_NUM_OF_DMAS_SHIFT		8
#घोषणा BMI_EXTRA_NUM_OF_DMAS_SHIFT	0

#घोषणा BMI_FIFO_ALIGN			0x100

#घोषणा BMI_EXTRA_FIFO_SIZE_SHIFT	16

/* QMI defines */
#घोषणा QMI_CFG_ENQ_EN			0x80000000
#घोषणा QMI_CFG_DEQ_EN			0x40000000
#घोषणा QMI_CFG_EN_COUNTERS		0x10000000
#घोषणा QMI_CFG_DEQ_MASK		0x0000003F
#घोषणा QMI_CFG_ENQ_MASK		0x00003F00
#घोषणा QMI_CFG_ENQ_SHIFT		8

#घोषणा QMI_ERR_INTR_EN_DOUBLE_ECC	0x80000000
#घोषणा QMI_ERR_INTR_EN_DEQ_FROM_DEF	0x40000000
#घोषणा QMI_INTR_EN_SINGLE_ECC		0x80000000

#घोषणा QMI_GS_HALT_NOT_BUSY		0x00000002

/* HWP defines */
#घोषणा HWP_RPIMAC_PEN			0x00000001

/* IRAM defines */
#घोषणा IRAM_IADD_AIE			0x80000000
#घोषणा IRAM_READY			0x80000000

/* Default values */
#घोषणा DEFAULT_CATASTROPHIC_ERR		0
#घोषणा DEFAULT_DMA_ERR				0
#घोषणा DEFAULT_AID_MODE			FMAN_DMA_AID_OUT_TNUM
#घोषणा DEFAULT_DMA_COMM_Q_LOW			0x2A
#घोषणा DEFAULT_DMA_COMM_Q_HIGH		0x3F
#घोषणा DEFAULT_CACHE_OVERRIDE			0
#घोषणा DEFAULT_DMA_CAM_NUM_OF_ENTRIES		64
#घोषणा DEFAULT_DMA_DBG_CNT_MODE		0
#घोषणा DEFAULT_DMA_SOS_EMERGENCY		0
#घोषणा DEFAULT_DMA_WATCHDOG			0
#घोषणा DEFAULT_DISP_LIMIT			0
#घोषणा DEFAULT_PRS_DISP_TH			16
#घोषणा DEFAULT_PLCR_DISP_TH			16
#घोषणा DEFAULT_KG_DISP_TH			16
#घोषणा DEFAULT_BMI_DISP_TH			16
#घोषणा DEFAULT_QMI_ENQ_DISP_TH		16
#घोषणा DEFAULT_QMI_DEQ_DISP_TH		16
#घोषणा DEFAULT_FM_CTL1_DISP_TH		16
#घोषणा DEFAULT_FM_CTL2_DISP_TH		16

#घोषणा DFLT_AXI_DBG_NUM_OF_BEATS		1

#घोषणा DFLT_DMA_READ_INT_BUF_LOW(dma_thresh_max_buf)	\
	((dma_thresh_max_buf + 1) / 2)
#घोषणा DFLT_DMA_READ_INT_BUF_HIGH(dma_thresh_max_buf)	\
	((dma_thresh_max_buf + 1) * 3 / 4)
#घोषणा DFLT_DMA_WRITE_INT_BUF_LOW(dma_thresh_max_buf)	\
	((dma_thresh_max_buf + 1) / 2)
#घोषणा DFLT_DMA_WRITE_INT_BUF_HIGH(dma_thresh_max_buf)\
	((dma_thresh_max_buf + 1) * 3 / 4)

#घोषणा DMA_COMM_Q_LOW_FMAN_V3		0x2A
#घोषणा DMA_COMM_Q_LOW_FMAN_V2(dma_thresh_max_commq)		\
	((dma_thresh_max_commq + 1) / 2)
#घोषणा DFLT_DMA_COMM_Q_LOW(major, dma_thresh_max_commq)	\
	((major == 6) ? DMA_COMM_Q_LOW_FMAN_V3 :		\
	DMA_COMM_Q_LOW_FMAN_V2(dma_thresh_max_commq))

#घोषणा DMA_COMM_Q_HIGH_FMAN_V3	0x3f
#घोषणा DMA_COMM_Q_HIGH_FMAN_V2(dma_thresh_max_commq)		\
	((dma_thresh_max_commq + 1) * 3 / 4)
#घोषणा DFLT_DMA_COMM_Q_HIGH(major, dma_thresh_max_commq)	\
	((major == 6) ? DMA_COMM_Q_HIGH_FMAN_V3 :		\
	DMA_COMM_Q_HIGH_FMAN_V2(dma_thresh_max_commq))

#घोषणा TOTAL_NUM_OF_TASKS_FMAN_V3L	59
#घोषणा TOTAL_NUM_OF_TASKS_FMAN_V3H	124
#घोषणा DFLT_TOTAL_NUM_OF_TASKS(major, minor, bmi_max_num_of_tasks)	\
	((major == 6) ? ((minor == 1 || minor == 4) ?			\
	TOTAL_NUM_OF_TASKS_FMAN_V3L : TOTAL_NUM_OF_TASKS_FMAN_V3H) :	\
	bmi_max_num_of_tasks)

#घोषणा DMA_CAM_NUM_OF_ENTRIES_FMAN_V3		64
#घोषणा DMA_CAM_NUM_OF_ENTRIES_FMAN_V2		32
#घोषणा DFLT_DMA_CAM_NUM_OF_ENTRIES(major)			\
	(major == 6 ? DMA_CAM_NUM_OF_ENTRIES_FMAN_V3 :		\
	DMA_CAM_NUM_OF_ENTRIES_FMAN_V2)

#घोषणा FM_TIMESTAMP_1_USEC_BIT             8

/* Defines used क्रम enabling/disabling FMan पूर्णांकerrupts */
#घोषणा ERR_INTR_EN_DMA         0x00010000
#घोषणा ERR_INTR_EN_FPM         0x80000000
#घोषणा ERR_INTR_EN_BMI         0x00800000
#घोषणा ERR_INTR_EN_QMI         0x00400000
#घोषणा ERR_INTR_EN_MURAM       0x00040000
#घोषणा ERR_INTR_EN_MAC0        0x00004000
#घोषणा ERR_INTR_EN_MAC1        0x00002000
#घोषणा ERR_INTR_EN_MAC2        0x00001000
#घोषणा ERR_INTR_EN_MAC3        0x00000800
#घोषणा ERR_INTR_EN_MAC4        0x00000400
#घोषणा ERR_INTR_EN_MAC5        0x00000200
#घोषणा ERR_INTR_EN_MAC6        0x00000100
#घोषणा ERR_INTR_EN_MAC7        0x00000080
#घोषणा ERR_INTR_EN_MAC8        0x00008000
#घोषणा ERR_INTR_EN_MAC9        0x00000040

#घोषणा INTR_EN_QMI             0x40000000
#घोषणा INTR_EN_MAC0            0x00080000
#घोषणा INTR_EN_MAC1            0x00040000
#घोषणा INTR_EN_MAC2            0x00020000
#घोषणा INTR_EN_MAC3            0x00010000
#घोषणा INTR_EN_MAC4            0x00000040
#घोषणा INTR_EN_MAC5            0x00000020
#घोषणा INTR_EN_MAC6            0x00000008
#घोषणा INTR_EN_MAC7            0x00000002
#घोषणा INTR_EN_MAC8            0x00200000
#घोषणा INTR_EN_MAC9            0x00100000
#घोषणा INTR_EN_REV0            0x00008000
#घोषणा INTR_EN_REV1            0x00004000
#घोषणा INTR_EN_REV2            0x00002000
#घोषणा INTR_EN_REV3            0x00001000
#घोषणा INTR_EN_TMR             0x01000000

क्रमागत fman_dma_aid_mode अणु
	FMAN_DMA_AID_OUT_PORT_ID = 0,		  /* 4 LSB of PORT_ID */
	FMAN_DMA_AID_OUT_TNUM			  /* 4 LSB of TNUM */
पूर्ण;

काष्ठा fman_iram_regs अणु
	u32 iadd;	/* FM IRAM inकाष्ठाion address रेजिस्टर */
	u32 idata;	/* FM IRAM inकाष्ठाion data रेजिस्टर */
	u32 itcfg;	/* FM IRAM timing config रेजिस्टर */
	u32 iपढ़ोy;	/* FM IRAM पढ़ोy रेजिस्टर */
पूर्ण;

काष्ठा fman_fpm_regs अणु
	u32 fmfp_tnc;		/* FPM TNUM Control 0x00 */
	u32 fmfp_prc;		/* FPM Port_ID FmCtl Association 0x04 */
	u32 fmfp_brkc;		/* FPM Breakpoपूर्णांक Control 0x08 */
	u32 fmfp_mxd;		/* FPM Flush Control 0x0c */
	u32 fmfp_dist1;		/* FPM Dispatch Thresholds1 0x10 */
	u32 fmfp_dist2;		/* FPM Dispatch Thresholds2 0x14 */
	u32 fm_epi;		/* FM Error Pending Interrupts 0x18 */
	u32 fm_rie;		/* FM Error Interrupt Enable 0x1c */
	u32 fmfp_fcev[4];	/* FPM FMan-Controller Event 1-4 0x20-0x2f */
	u32 res0030[4];		/* res 0x30 - 0x3f */
	u32 fmfp_cee[4];	/* PM FMan-Controller Event 1-4 0x40-0x4f */
	u32 res0050[4];		/* res 0x50-0x5f */
	u32 fmfp_tsc1;		/* FPM TimeStamp Control1 0x60 */
	u32 fmfp_tsc2;		/* FPM TimeStamp Control2 0x64 */
	u32 fmfp_tsp;		/* FPM Time Stamp 0x68 */
	u32 fmfp_tsf;		/* FPM Time Stamp Fraction 0x6c */
	u32 fm_rcr;		/* FM Rams Control 0x70 */
	u32 fmfp_extc;		/* FPM External Requests Control 0x74 */
	u32 fmfp_ext1;		/* FPM External Requests Config1 0x78 */
	u32 fmfp_ext2;		/* FPM External Requests Config2 0x7c */
	u32 fmfp_drd[16];	/* FPM Data_Ram Data 0-15 0x80 - 0xbf */
	u32 fmfp_dra;		/* FPM Data Ram Access 0xc0 */
	u32 fm_ip_rev_1;	/* FM IP Block Revision 1 0xc4 */
	u32 fm_ip_rev_2;	/* FM IP Block Revision 2 0xc8 */
	u32 fm_rstc;		/* FM Reset Command 0xcc */
	u32 fm_cld;		/* FM Classअगरier Debug 0xd0 */
	u32 fm_npi;		/* FM Normal Pending Interrupts 0xd4 */
	u32 fmfp_exte;		/* FPM External Requests Enable 0xd8 */
	u32 fmfp_ee;		/* FPM Event&Mask 0xdc */
	u32 fmfp_cev[4];	/* FPM CPU Event 1-4 0xe0-0xef */
	u32 res00f0[4];		/* res 0xf0-0xff */
	u32 fmfp_ps[50];	/* FPM Port Status 0x100-0x1c7 */
	u32 res01c8[14];	/* res 0x1c8-0x1ff */
	u32 fmfp_clfabc;	/* FPM CLFABC 0x200 */
	u32 fmfp_clfcc;		/* FPM CLFCC 0x204 */
	u32 fmfp_clfaval;	/* FPM CLFAVAL 0x208 */
	u32 fmfp_clfbval;	/* FPM CLFBVAL 0x20c */
	u32 fmfp_clfcval;	/* FPM CLFCVAL 0x210 */
	u32 fmfp_clfamsk;	/* FPM CLFAMSK 0x214 */
	u32 fmfp_clfbmsk;	/* FPM CLFBMSK 0x218 */
	u32 fmfp_clfcmsk;	/* FPM CLFCMSK 0x21c */
	u32 fmfp_clfamc;	/* FPM CLFAMC 0x220 */
	u32 fmfp_clfbmc;	/* FPM CLFBMC 0x224 */
	u32 fmfp_clfcmc;	/* FPM CLFCMC 0x228 */
	u32 fmfp_decceh;	/* FPM DECCEH 0x22c */
	u32 res0230[116];	/* res 0x230 - 0x3ff */
	u32 fmfp_ts[128];	/* 0x400: FPM Task Status 0x400 - 0x5ff */
	u32 res0600[0x400 - 384];
पूर्ण;

काष्ठा fman_bmi_regs अणु
	u32 fmbm_init;		/* BMI Initialization 0x00 */
	u32 fmbm_cfg1;		/* BMI Configuration 1 0x04 */
	u32 fmbm_cfg2;		/* BMI Configuration 2 0x08 */
	u32 res000c[5];		/* 0x0c - 0x1f */
	u32 fmbm_ievr;		/* Interrupt Event Register 0x20 */
	u32 fmbm_ier;		/* Interrupt Enable Register 0x24 */
	u32 fmbm_अगरr;		/* Interrupt Force Register 0x28 */
	u32 res002c[5];		/* 0x2c - 0x3f */
	u32 fmbm_arb[8];	/* BMI Arbitration 0x40 - 0x5f */
	u32 res0060[12];	/* 0x60 - 0x8f */
	u32 fmbm_dtc[3];	/* Debug Trap Counter 0x90 - 0x9b */
	u32 res009c;		/* 0x9c */
	u32 fmbm_dcv[3][4];	/* Debug Compare val 0xa0-0xcf */
	u32 fmbm_dcm[3][4];	/* Debug Compare Mask 0xd0-0xff */
	u32 fmbm_gde;		/* BMI Global Debug Enable 0x100 */
	u32 fmbm_pp[63];	/* BMI Port Parameters 0x104 - 0x1ff */
	u32 res0200;		/* 0x200 */
	u32 fmbm_pfs[63];	/* BMI Port FIFO Size 0x204 - 0x2ff */
	u32 res0300;		/* 0x300 */
	u32 fmbm_spliodn[63];	/* Port Partition ID 0x304 - 0x3ff */
पूर्ण;

काष्ठा fman_qmi_regs अणु
	u32 fmqm_gc;		/* General Configuration Register 0x00 */
	u32 res0004;		/* 0x04 */
	u32 fmqm_eie;		/* Error Interrupt Event Register 0x08 */
	u32 fmqm_eien;		/* Error Interrupt Enable Register 0x0c */
	u32 fmqm_eअगर;		/* Error Interrupt Force Register 0x10 */
	u32 fmqm_ie;		/* Interrupt Event Register 0x14 */
	u32 fmqm_ien;		/* Interrupt Enable Register 0x18 */
	u32 fmqm_अगर;		/* Interrupt Force Register 0x1c */
	u32 fmqm_gs;		/* Global Status Register 0x20 */
	u32 fmqm_ts;		/* Task Status Register 0x24 */
	u32 fmqm_etfc;		/* Enqueue Total Frame Counter 0x28 */
	u32 fmqm_dtfc;		/* Dequeue Total Frame Counter 0x2c */
	u32 fmqm_dc0;		/* Dequeue Counter 0 0x30 */
	u32 fmqm_dc1;		/* Dequeue Counter 1 0x34 */
	u32 fmqm_dc2;		/* Dequeue Counter 2 0x38 */
	u32 fmqm_dc3;		/* Dequeue Counter 3 0x3c */
	u32 fmqm_dfdc;		/* Dequeue FQID from Default Counter 0x40 */
	u32 fmqm_dfcc;		/* Dequeue FQID from Context Counter 0x44 */
	u32 fmqm_dffc;		/* Dequeue FQID from FD Counter 0x48 */
	u32 fmqm_dcc;		/* Dequeue Confirm Counter 0x4c */
	u32 res0050[7];		/* 0x50 - 0x6b */
	u32 fmqm_tapc;		/* Tnum Aging Period Control 0x6c */
	u32 fmqm_dmcvc;		/* Dequeue MAC Command Valid Counter 0x70 */
	u32 fmqm_dअगरdcc;	/* Dequeue Invalid FD Command Counter 0x74 */
	u32 fmqm_da1v;		/* Dequeue A1 Valid Counter 0x78 */
	u32 res007c;		/* 0x7c */
	u32 fmqm_dtc;		/* 0x80 Debug Trap Counter 0x80 */
	u32 fmqm_efddd;		/* 0x84 Enqueue Frame desc Dynamic dbg 0x84 */
	u32 res0088[2];		/* 0x88 - 0x8f */
	काष्ठा अणु
		u32 fmqm_dtcfg1;	/* 0x90 dbg trap cfg 1 Register 0x00 */
		u32 fmqm_dtval1;	/* Debug Trap Value 1 Register 0x04 */
		u32 fmqm_dपंचांग1;		/* Debug Trap Mask 1 Register 0x08 */
		u32 fmqm_dtc1;		/* Debug Trap Counter 1 Register 0x0c */
		u32 fmqm_dtcfg2;	/* dbg Trap cfg 2 Register 0x10 */
		u32 fmqm_dtval2;	/* Debug Trap Value 2 Register 0x14 */
		u32 fmqm_dपंचांग2;		/* Debug Trap Mask 2 Register 0x18 */
		u32 res001c;		/* 0x1c */
	पूर्ण dbg_traps[3];			/* 0x90 - 0xef */
	u8 res00f0[0x400 - 0xf0];	/* 0xf0 - 0x3ff */
पूर्ण;

काष्ठा fman_dma_regs अणु
	u32 fmdmsr;	/* FM DMA status रेजिस्टर 0x00 */
	u32 fmdmmr;	/* FM DMA mode रेजिस्टर 0x04 */
	u32 fmdmtr;	/* FM DMA bus threshold रेजिस्टर 0x08 */
	u32 fmdmhy;	/* FM DMA bus hysteresis रेजिस्टर 0x0c */
	u32 fmdmsetr;	/* FM DMA SOS emergency Threshold Register 0x10 */
	u32 fmdmtah;	/* FM DMA transfer bus address high reg 0x14 */
	u32 fmdmtal;	/* FM DMA transfer bus address low reg 0x18 */
	u32 fmdmtcid;	/* FM DMA transfer bus communication ID reg 0x1c */
	u32 fmdmra;	/* FM DMA bus पूर्णांकernal ram address रेजिस्टर 0x20 */
	u32 fmdmrd;	/* FM DMA bus पूर्णांकernal ram data रेजिस्टर 0x24 */
	u32 fmdmwcr;	/* FM DMA CAM watchकरोg counter value 0x28 */
	u32 fmdmebcr;	/* FM DMA CAM base in MURAM रेजिस्टर 0x2c */
	u32 fmdmccqdr;	/* FM DMA CAM and CMD Queue Debug reg 0x30 */
	u32 fmdmccqvr1;	/* FM DMA CAM and CMD Queue Value reg #1 0x34 */
	u32 fmdmccqvr2;	/* FM DMA CAM and CMD Queue Value reg #2 0x38 */
	u32 fmdmcqvr3;	/* FM DMA CMD Queue Value रेजिस्टर #3 0x3c */
	u32 fmdmcqvr4;	/* FM DMA CMD Queue Value रेजिस्टर #4 0x40 */
	u32 fmdmcqvr5;	/* FM DMA CMD Queue Value रेजिस्टर #5 0x44 */
	u32 fmdmsefrc;	/* FM DMA Semaphore Entry Full Reject Cntr 0x48 */
	u32 fmdmsqfrc;	/* FM DMA Semaphore Queue Full Reject Cntr 0x4c */
	u32 fmdmssrc;	/* FM DMA Semaphore SYNC Reject Counter 0x50 */
	u32 fmdmdcr;	/* FM DMA Debug Counter 0x54 */
	u32 fmdmemsr;	/* FM DMA Emergency Smoother Register 0x58 */
	u32 res005c;	/* 0x5c */
	u32 fmdmplr[FMAN_LIODN_TBL / 2];	/* DMA LIODN regs 0x60-0xdf */
	u32 res00e0[0x400 - 56];
पूर्ण;

काष्ठा fman_hwp_regs अणु
	u32 res0000[0x844 / 4];		/* 0x000..0x843 */
	u32 fmprrpimac;	/* FM Parser Internal memory access control */
	u32 res[(0x1000 - 0x848) / 4];	/* 0x848..0xFFF */
पूर्ण;

/* Structure that holds current FMan state.
 * Used क्रम saving run समय inक्रमmation.
 */
काष्ठा fman_state_काष्ठा अणु
	u8 fm_id;
	u16 fm_clk_freq;
	काष्ठा fman_rev_info rev_info;
	bool enabled_समय_stamp;
	u8 count1_micro_bit;
	u8 total_num_of_tasks;
	u8 accumulated_num_of_tasks;
	u32 accumulated_fअगरo_size;
	u8 accumulated_num_of_खोलो_dmas;
	u8 accumulated_num_of_deq_tnums;
	u32 exceptions;
	u32 extra_fअगरo_pool_size;
	u8 extra_tasks_pool_size;
	u8 extra_खोलो_dmas_pool_size;
	u16 port_mfl[MAX_NUM_OF_MACS];
	u16 mac_mfl[MAX_NUM_OF_MACS];

	/* SOC specअगरic */
	u32 fm_iram_size;
	/* DMA */
	u32 dma_thresh_max_commq;
	u32 dma_thresh_max_buf;
	u32 max_num_of_खोलो_dmas;
	/* QMI */
	u32 qmi_max_num_of_tnums;
	u32 qmi_def_tnums_thresh;
	/* BMI */
	u32 bmi_max_num_of_tasks;
	u32 bmi_max_fअगरo_size;
	/* General */
	u32 fm_port_num_of_cg;
	u32 num_of_rx_ports;
	u32 total_fअगरo_size;

	u32 qman_channel_base;
	u32 num_of_qman_channels;

	काष्ठा resource *res;
पूर्ण;

/* Structure that holds FMan initial configuration */
काष्ठा fman_cfg अणु
	u8 disp_limit_tsh;
	u8 prs_disp_tsh;
	u8 plcr_disp_tsh;
	u8 kg_disp_tsh;
	u8 bmi_disp_tsh;
	u8 qmi_enq_disp_tsh;
	u8 qmi_deq_disp_tsh;
	u8 fm_ctl1_disp_tsh;
	u8 fm_ctl2_disp_tsh;
	पूर्णांक dma_cache_override;
	क्रमागत fman_dma_aid_mode dma_aid_mode;
	u32 dma_axi_dbg_num_of_beats;
	u32 dma_cam_num_of_entries;
	u32 dma_watchकरोg;
	u8 dma_comm_qtsh_asrt_emer;
	u32 dma_ग_लिखो_buf_tsh_asrt_emer;
	u32 dma_पढ़ो_buf_tsh_asrt_emer;
	u8 dma_comm_qtsh_clr_emer;
	u32 dma_ग_लिखो_buf_tsh_clr_emer;
	u32 dma_पढ़ो_buf_tsh_clr_emer;
	u32 dma_sos_emergency;
	पूर्णांक dma_dbg_cnt_mode;
	पूर्णांक catastrophic_err;
	पूर्णांक dma_err;
	u32 exceptions;
	u16 clk_freq;
	u32 cam_base_addr;
	u32 fअगरo_base_addr;
	u32 total_fअगरo_size;
	u32 total_num_of_tasks;
	u32 qmi_def_tnums_thresh;
पूर्ण;

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
अटल bool fman_has_err_a050385;
#पूर्ण_अगर

अटल irqवापस_t fman_exceptions(काष्ठा fman *fman,
				   क्रमागत fman_exceptions exception)
अणु
	dev_dbg(fman->dev, "%s: FMan[%d] exception %d\n",
		__func__, fman->state->fm_id, exception);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fman_bus_error(काष्ठा fman *fman, u8 __maybe_unused port_id,
				  u64 __maybe_unused addr,
				  u8 __maybe_unused tnum,
				  u16 __maybe_unused liodn)
अणु
	dev_dbg(fman->dev, "%s: FMan[%d] bus error: port_id[%d]\n",
		__func__, fman->state->fm_id, port_id);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत irqवापस_t call_mac_isr(काष्ठा fman *fman, u8 id)
अणु
	अगर (fman->पूर्णांकr_mng[id].isr_cb) अणु
		fman->पूर्णांकr_mng[id].isr_cb(fman->पूर्णांकr_mng[id].src_handle);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल अंतरभूत u8 hw_port_id_to_sw_port_id(u8 major, u8 hw_port_id)
अणु
	u8 sw_port_id = 0;

	अगर (hw_port_id >= BASE_TX_PORTID)
		sw_port_id = hw_port_id - BASE_TX_PORTID;
	अन्यथा अगर (hw_port_id >= BASE_RX_PORTID)
		sw_port_id = hw_port_id - BASE_RX_PORTID;
	अन्यथा
		sw_port_id = 0;

	वापस sw_port_id;
पूर्ण

अटल व्योम set_port_order_restoration(काष्ठा fman_fpm_regs __iomem *fpm_rg,
				       u8 port_id)
अणु
	u32 पंचांगp = 0;

	पंचांगp = port_id << FPM_PORT_FM_CTL_PORTID_SHIFT;

	पंचांगp |= FPM_PRT_FM_CTL2 | FPM_PRT_FM_CTL1;

	/* order restoration */
	अगर (port_id % 2)
		पंचांगp |= FPM_PRT_FM_CTL1 << FPM_PRC_ORA_FM_CTL_SEL_SHIFT;
	अन्यथा
		पंचांगp |= FPM_PRT_FM_CTL2 << FPM_PRC_ORA_FM_CTL_SEL_SHIFT;

	ioग_लिखो32be(पंचांगp, &fpm_rg->fmfp_prc);
पूर्ण

अटल व्योम set_port_liodn(काष्ठा fman *fman, u8 port_id,
			   u32 liodn_base, u32 liodn_ofst)
अणु
	u32 पंचांगp;

	ioग_लिखो32be(liodn_ofst, &fman->bmi_regs->fmbm_spliodn[port_id - 1]);
	अगर (!IS_ENABLED(CONFIG_FSL_PAMU))
		वापस;
	/* set LIODN base क्रम this port */
	पंचांगp = ioपढ़ो32be(&fman->dma_regs->fmdmplr[port_id / 2]);
	अगर (port_id % 2) अणु
		पंचांगp &= ~DMA_LIODN_BASE_MASK;
		पंचांगp |= liodn_base;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~(DMA_LIODN_BASE_MASK << DMA_LIODN_SHIFT);
		पंचांगp |= liodn_base << DMA_LIODN_SHIFT;
	पूर्ण
	ioग_लिखो32be(पंचांगp, &fman->dma_regs->fmdmplr[port_id / 2]);
पूर्ण

अटल व्योम enable_rams_ecc(काष्ठा fman_fpm_regs __iomem *fpm_rg)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&fpm_rg->fm_rcr);
	अगर (पंचांगp & FPM_RAM_RAMS_ECC_EN_SRC_SEL)
		ioग_लिखो32be(पंचांगp | FPM_RAM_IRAM_ECC_EN, &fpm_rg->fm_rcr);
	अन्यथा
		ioग_लिखो32be(पंचांगp | FPM_RAM_RAMS_ECC_EN |
			    FPM_RAM_IRAM_ECC_EN, &fpm_rg->fm_rcr);
पूर्ण

अटल व्योम disable_rams_ecc(काष्ठा fman_fpm_regs __iomem *fpm_rg)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&fpm_rg->fm_rcr);
	अगर (पंचांगp & FPM_RAM_RAMS_ECC_EN_SRC_SEL)
		ioग_लिखो32be(पंचांगp & ~FPM_RAM_IRAM_ECC_EN, &fpm_rg->fm_rcr);
	अन्यथा
		ioग_लिखो32be(पंचांगp & ~(FPM_RAM_RAMS_ECC_EN | FPM_RAM_IRAM_ECC_EN),
			    &fpm_rg->fm_rcr);
पूर्ण

अटल व्योम fman_defconfig(काष्ठा fman_cfg *cfg)
अणु
	स_रखो(cfg, 0, माप(काष्ठा fman_cfg));

	cfg->catastrophic_err = DEFAULT_CATASTROPHIC_ERR;
	cfg->dma_err = DEFAULT_DMA_ERR;
	cfg->dma_aid_mode = DEFAULT_AID_MODE;
	cfg->dma_comm_qtsh_clr_emer = DEFAULT_DMA_COMM_Q_LOW;
	cfg->dma_comm_qtsh_asrt_emer = DEFAULT_DMA_COMM_Q_HIGH;
	cfg->dma_cache_override = DEFAULT_CACHE_OVERRIDE;
	cfg->dma_cam_num_of_entries = DEFAULT_DMA_CAM_NUM_OF_ENTRIES;
	cfg->dma_dbg_cnt_mode = DEFAULT_DMA_DBG_CNT_MODE;
	cfg->dma_sos_emergency = DEFAULT_DMA_SOS_EMERGENCY;
	cfg->dma_watchकरोg = DEFAULT_DMA_WATCHDOG;
	cfg->disp_limit_tsh = DEFAULT_DISP_LIMIT;
	cfg->prs_disp_tsh = DEFAULT_PRS_DISP_TH;
	cfg->plcr_disp_tsh = DEFAULT_PLCR_DISP_TH;
	cfg->kg_disp_tsh = DEFAULT_KG_DISP_TH;
	cfg->bmi_disp_tsh = DEFAULT_BMI_DISP_TH;
	cfg->qmi_enq_disp_tsh = DEFAULT_QMI_ENQ_DISP_TH;
	cfg->qmi_deq_disp_tsh = DEFAULT_QMI_DEQ_DISP_TH;
	cfg->fm_ctl1_disp_tsh = DEFAULT_FM_CTL1_DISP_TH;
	cfg->fm_ctl2_disp_tsh = DEFAULT_FM_CTL2_DISP_TH;
पूर्ण

अटल पूर्णांक dma_init(काष्ठा fman *fman)
अणु
	काष्ठा fman_dma_regs __iomem *dma_rg = fman->dma_regs;
	काष्ठा fman_cfg *cfg = fman->cfg;
	u32 पंचांगp_reg;

	/* Init DMA Registers */

	/* clear status reg events */
	पंचांगp_reg = (DMA_STATUS_BUS_ERR | DMA_STATUS_READ_ECC |
		   DMA_STATUS_SYSTEM_WRITE_ECC | DMA_STATUS_FM_WRITE_ECC);
	ioग_लिखो32be(ioपढ़ो32be(&dma_rg->fmdmsr) | पंचांगp_reg, &dma_rg->fmdmsr);

	/* configure mode रेजिस्टर */
	पंचांगp_reg = 0;
	पंचांगp_reg |= cfg->dma_cache_override << DMA_MODE_CACHE_OR_SHIFT;
	अगर (cfg->exceptions & EX_DMA_BUS_ERROR)
		पंचांगp_reg |= DMA_MODE_BER;
	अगर ((cfg->exceptions & EX_DMA_SYSTEM_WRITE_ECC) |
	    (cfg->exceptions & EX_DMA_READ_ECC) |
	    (cfg->exceptions & EX_DMA_FM_WRITE_ECC))
		पंचांगp_reg |= DMA_MODE_ECC;
	अगर (cfg->dma_axi_dbg_num_of_beats)
		पंचांगp_reg |= (DMA_MODE_AXI_DBG_MASK &
			((cfg->dma_axi_dbg_num_of_beats - 1)
			<< DMA_MODE_AXI_DBG_SHIFT));

	पंचांगp_reg |= (((cfg->dma_cam_num_of_entries / DMA_CAM_UNITS) - 1) &
		DMA_MODE_CEN_MASK) << DMA_MODE_CEN_SHIFT;
	पंचांगp_reg |= DMA_MODE_SECURE_PROT;
	पंचांगp_reg |= cfg->dma_dbg_cnt_mode << DMA_MODE_DBG_SHIFT;
	पंचांगp_reg |= cfg->dma_aid_mode << DMA_MODE_AID_MODE_SHIFT;

	ioग_लिखो32be(पंचांगp_reg, &dma_rg->fmdmmr);

	/* configure thresholds रेजिस्टर */
	पंचांगp_reg = ((u32)cfg->dma_comm_qtsh_asrt_emer <<
		DMA_THRESH_COMMQ_SHIFT);
	पंचांगp_reg |= (cfg->dma_पढ़ो_buf_tsh_asrt_emer &
		DMA_THRESH_READ_INT_BUF_MASK) << DMA_THRESH_READ_INT_BUF_SHIFT;
	पंचांगp_reg |= cfg->dma_ग_लिखो_buf_tsh_asrt_emer &
		DMA_THRESH_WRITE_INT_BUF_MASK;

	ioग_लिखो32be(पंचांगp_reg, &dma_rg->fmdmtr);

	/* configure hysteresis रेजिस्टर */
	पंचांगp_reg = ((u32)cfg->dma_comm_qtsh_clr_emer <<
		DMA_THRESH_COMMQ_SHIFT);
	पंचांगp_reg |= (cfg->dma_पढ़ो_buf_tsh_clr_emer &
		DMA_THRESH_READ_INT_BUF_MASK) << DMA_THRESH_READ_INT_BUF_SHIFT;
	पंचांगp_reg |= cfg->dma_ग_लिखो_buf_tsh_clr_emer &
		DMA_THRESH_WRITE_INT_BUF_MASK;

	ioग_लिखो32be(पंचांगp_reg, &dma_rg->fmdmhy);

	/* configure emergency threshold */
	ioग_लिखो32be(cfg->dma_sos_emergency, &dma_rg->fmdmsetr);

	/* configure Watchकरोg */
	ioग_लिखो32be((cfg->dma_watchकरोg * cfg->clk_freq), &dma_rg->fmdmwcr);

	ioग_लिखो32be(cfg->cam_base_addr, &dma_rg->fmdmebcr);

	/* Allocate MURAM क्रम CAM */
	fman->cam_size =
		(u32)(fman->cfg->dma_cam_num_of_entries * DMA_CAM_SIZखातापूर्ण_ENTRY);
	fman->cam_offset = fman_muram_alloc(fman->muram, fman->cam_size);
	अगर (IS_ERR_VALUE(fman->cam_offset)) अणु
		dev_err(fman->dev, "%s: MURAM alloc for DMA CAM failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (fman->state->rev_info.major == 2) अणु
		u32 __iomem *cam_base_addr;

		fman_muram_मुक्त_mem(fman->muram, fman->cam_offset,
				    fman->cam_size);

		fman->cam_size = fman->cfg->dma_cam_num_of_entries * 72 + 128;
		fman->cam_offset = fman_muram_alloc(fman->muram,
						    fman->cam_size);
		अगर (IS_ERR_VALUE(fman->cam_offset)) अणु
			dev_err(fman->dev, "%s: MURAM alloc for DMA CAM failed\n",
				__func__);
			वापस -ENOMEM;
		पूर्ण

		अगर (fman->cfg->dma_cam_num_of_entries % 8 ||
		    fman->cfg->dma_cam_num_of_entries > 32) अणु
			dev_err(fman->dev, "%s: wrong dma_cam_num_of_entries\n",
				__func__);
			वापस -EINVAL;
		पूर्ण

		cam_base_addr = (u32 __iomem *)
			fman_muram_offset_to_vbase(fman->muram,
						   fman->cam_offset);
		ioग_लिखो32be(~((1 <<
			    (32 - fman->cfg->dma_cam_num_of_entries)) - 1),
			    cam_base_addr);
	पूर्ण

	fman->cfg->cam_base_addr = fman->cam_offset;

	वापस 0;
पूर्ण

अटल व्योम fpm_init(काष्ठा fman_fpm_regs __iomem *fpm_rg, काष्ठा fman_cfg *cfg)
अणु
	u32 पंचांगp_reg;
	पूर्णांक i;

	/* Init FPM Registers */

	पंचांगp_reg = (u32)(cfg->disp_limit_tsh << FPM_DISP_LIMIT_SHIFT);
	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fmfp_mxd);

	पंचांगp_reg = (((u32)cfg->prs_disp_tsh << FPM_THR1_PRS_SHIFT) |
		   ((u32)cfg->kg_disp_tsh << FPM_THR1_KG_SHIFT) |
		   ((u32)cfg->plcr_disp_tsh << FPM_THR1_PLCR_SHIFT) |
		   ((u32)cfg->bmi_disp_tsh << FPM_THR1_BMI_SHIFT));
	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fmfp_dist1);

	पंचांगp_reg =
		(((u32)cfg->qmi_enq_disp_tsh << FPM_THR2_QMI_ENQ_SHIFT) |
		 ((u32)cfg->qmi_deq_disp_tsh << FPM_THR2_QMI_DEQ_SHIFT) |
		 ((u32)cfg->fm_ctl1_disp_tsh << FPM_THR2_FM_CTL1_SHIFT) |
		 ((u32)cfg->fm_ctl2_disp_tsh << FPM_THR2_FM_CTL2_SHIFT));
	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fmfp_dist2);

	/* define exceptions and error behavior */
	पंचांगp_reg = 0;
	/* Clear events */
	पंचांगp_reg |= (FPM_EV_MASK_STALL | FPM_EV_MASK_DOUBLE_ECC |
		    FPM_EV_MASK_SINGLE_ECC);
	/* enable पूर्णांकerrupts */
	अगर (cfg->exceptions & EX_FPM_STALL_ON_TASKS)
		पंचांगp_reg |= FPM_EV_MASK_STALL_EN;
	अगर (cfg->exceptions & EX_FPM_SINGLE_ECC)
		पंचांगp_reg |= FPM_EV_MASK_SINGLE_ECC_EN;
	अगर (cfg->exceptions & EX_FPM_DOUBLE_ECC)
		पंचांगp_reg |= FPM_EV_MASK_DOUBLE_ECC_EN;
	पंचांगp_reg |= (cfg->catastrophic_err << FPM_EV_MASK_CAT_ERR_SHIFT);
	पंचांगp_reg |= (cfg->dma_err << FPM_EV_MASK_DMA_ERR_SHIFT);
	/* FMan is not halted upon बाह्यal halt activation */
	पंचांगp_reg |= FPM_EV_MASK_EXTERNAL_HALT;
	/* Man is not halted upon  Unrecoverable ECC error behavior */
	पंचांगp_reg |= FPM_EV_MASK_ECC_ERR_HALT;
	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fmfp_ee);

	/* clear all fmCtls event रेजिस्टरs */
	क्रम (i = 0; i < FM_NUM_OF_FMAN_CTRL_EVENT_REGS; i++)
		ioग_लिखो32be(0xFFFFFFFF, &fpm_rg->fmfp_cev[i]);

	/* RAM ECC -  enable and clear events */
	/* first we need to clear all parser memory,
	 * as it is uninitialized and may cause ECC errors
	 */
	/* event bits */
	पंचांगp_reg = (FPM_RAM_MURAM_ECC | FPM_RAM_IRAM_ECC);

	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fm_rcr);

	पंचांगp_reg = 0;
	अगर (cfg->exceptions & EX_IRAM_ECC) अणु
		पंचांगp_reg |= FPM_IRAM_ECC_ERR_EX_EN;
		enable_rams_ecc(fpm_rg);
	पूर्ण
	अगर (cfg->exceptions & EX_MURAM_ECC) अणु
		पंचांगp_reg |= FPM_MURAM_ECC_ERR_EX_EN;
		enable_rams_ecc(fpm_rg);
	पूर्ण
	ioग_लिखो32be(पंचांगp_reg, &fpm_rg->fm_rie);
पूर्ण

अटल व्योम bmi_init(काष्ठा fman_bmi_regs __iomem *bmi_rg,
		     काष्ठा fman_cfg *cfg)
अणु
	u32 पंचांगp_reg;

	/* Init BMI Registers */

	/* define common resources */
	पंचांगp_reg = cfg->fअगरo_base_addr;
	पंचांगp_reg = पंचांगp_reg / BMI_FIFO_ALIGN;

	पंचांगp_reg |= ((cfg->total_fअगरo_size / FMAN_BMI_FIFO_UNITS - 1) <<
		    BMI_CFG1_FIFO_SIZE_SHIFT);
	ioग_लिखो32be(पंचांगp_reg, &bmi_rg->fmbm_cfg1);

	पंचांगp_reg = ((cfg->total_num_of_tasks - 1) & BMI_CFG2_TASKS_MASK) <<
		   BMI_CFG2_TASKS_SHIFT;
	/* num of DMA's will be dynamically updated when each port is set */
	ioग_लिखो32be(पंचांगp_reg, &bmi_rg->fmbm_cfg2);

	/* define unmaskable exceptions, enable and clear events */
	पंचांगp_reg = 0;
	ioग_लिखो32be(BMI_ERR_INTR_EN_LIST_RAM_ECC |
		    BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC |
		    BMI_ERR_INTR_EN_STATISTICS_RAM_ECC |
		    BMI_ERR_INTR_EN_DISPATCH_RAM_ECC, &bmi_rg->fmbm_ievr);

	अगर (cfg->exceptions & EX_BMI_LIST_RAM_ECC)
		पंचांगp_reg |= BMI_ERR_INTR_EN_LIST_RAM_ECC;
	अगर (cfg->exceptions & EX_BMI_STORAGE_PROखाता_ECC)
		पंचांगp_reg |= BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC;
	अगर (cfg->exceptions & EX_BMI_STATISTICS_RAM_ECC)
		पंचांगp_reg |= BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
	अगर (cfg->exceptions & EX_BMI_DISPATCH_RAM_ECC)
		पंचांगp_reg |= BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
	ioग_लिखो32be(पंचांगp_reg, &bmi_rg->fmbm_ier);
पूर्ण

अटल व्योम qmi_init(काष्ठा fman_qmi_regs __iomem *qmi_rg,
		     काष्ठा fman_cfg *cfg)
अणु
	u32 पंचांगp_reg;

	/* Init QMI Registers */

	/* Clear error पूर्णांकerrupt events */

	ioग_लिखो32be(QMI_ERR_INTR_EN_DOUBLE_ECC | QMI_ERR_INTR_EN_DEQ_FROM_DEF,
		    &qmi_rg->fmqm_eie);
	पंचांगp_reg = 0;
	अगर (cfg->exceptions & EX_QMI_DEQ_FROM_UNKNOWN_PORTID)
		पंचांगp_reg |= QMI_ERR_INTR_EN_DEQ_FROM_DEF;
	अगर (cfg->exceptions & EX_QMI_DOUBLE_ECC)
		पंचांगp_reg |= QMI_ERR_INTR_EN_DOUBLE_ECC;
	/* enable events */
	ioग_लिखो32be(पंचांगp_reg, &qmi_rg->fmqm_eien);

	पंचांगp_reg = 0;
	/* Clear पूर्णांकerrupt events */
	ioग_लिखो32be(QMI_INTR_EN_SINGLE_ECC, &qmi_rg->fmqm_ie);
	अगर (cfg->exceptions & EX_QMI_SINGLE_ECC)
		पंचांगp_reg |= QMI_INTR_EN_SINGLE_ECC;
	/* enable events */
	ioग_लिखो32be(पंचांगp_reg, &qmi_rg->fmqm_ien);
पूर्ण

अटल व्योम hwp_init(काष्ठा fman_hwp_regs __iomem *hwp_rg)
अणु
	/* enable HW Parser */
	ioग_लिखो32be(HWP_RPIMAC_PEN, &hwp_rg->fmprrpimac);
पूर्ण

अटल पूर्णांक enable(काष्ठा fman *fman, काष्ठा fman_cfg *cfg)
अणु
	u32 cfg_reg = 0;

	/* Enable all modules */

	/* clear&enable global counters - calculate reg and save क्रम later,
	 * because it's the same reg क्रम QMI enable
	 */
	cfg_reg = QMI_CFG_EN_COUNTERS;

	/* Set enqueue and dequeue thresholds */
	cfg_reg |= (cfg->qmi_def_tnums_thresh << 8) | cfg->qmi_def_tnums_thresh;

	ioग_लिखो32be(BMI_INIT_START, &fman->bmi_regs->fmbm_init);
	ioग_लिखो32be(cfg_reg | QMI_CFG_ENQ_EN | QMI_CFG_DEQ_EN,
		    &fman->qmi_regs->fmqm_gc);

	वापस 0;
पूर्ण

अटल पूर्णांक set_exception(काष्ठा fman *fman,
			 क्रमागत fman_exceptions exception, bool enable)
अणु
	u32 पंचांगp;

	चयन (exception) अणु
	हाल FMAN_EX_DMA_BUS_ERROR:
		पंचांगp = ioपढ़ो32be(&fman->dma_regs->fmdmmr);
		अगर (enable)
			पंचांगp |= DMA_MODE_BER;
		अन्यथा
			पंचांगp &= ~DMA_MODE_BER;
		/* disable bus error */
		ioग_लिखो32be(पंचांगp, &fman->dma_regs->fmdmmr);
		अवरोध;
	हाल FMAN_EX_DMA_READ_ECC:
	हाल FMAN_EX_DMA_SYSTEM_WRITE_ECC:
	हाल FMAN_EX_DMA_FM_WRITE_ECC:
		पंचांगp = ioपढ़ो32be(&fman->dma_regs->fmdmmr);
		अगर (enable)
			पंचांगp |= DMA_MODE_ECC;
		अन्यथा
			पंचांगp &= ~DMA_MODE_ECC;
		ioग_लिखो32be(पंचांगp, &fman->dma_regs->fmdmmr);
		अवरोध;
	हाल FMAN_EX_FPM_STALL_ON_TASKS:
		पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fmfp_ee);
		अगर (enable)
			पंचांगp |= FPM_EV_MASK_STALL_EN;
		अन्यथा
			पंचांगp &= ~FPM_EV_MASK_STALL_EN;
		ioग_लिखो32be(पंचांगp, &fman->fpm_regs->fmfp_ee);
		अवरोध;
	हाल FMAN_EX_FPM_SINGLE_ECC:
		पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fmfp_ee);
		अगर (enable)
			पंचांगp |= FPM_EV_MASK_SINGLE_ECC_EN;
		अन्यथा
			पंचांगp &= ~FPM_EV_MASK_SINGLE_ECC_EN;
		ioग_लिखो32be(पंचांगp, &fman->fpm_regs->fmfp_ee);
		अवरोध;
	हाल FMAN_EX_FPM_DOUBLE_ECC:
		पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fmfp_ee);
		अगर (enable)
			पंचांगp |= FPM_EV_MASK_DOUBLE_ECC_EN;
		अन्यथा
			पंचांगp &= ~FPM_EV_MASK_DOUBLE_ECC_EN;
		ioग_लिखो32be(पंचांगp, &fman->fpm_regs->fmfp_ee);
		अवरोध;
	हाल FMAN_EX_QMI_SINGLE_ECC:
		पंचांगp = ioपढ़ो32be(&fman->qmi_regs->fmqm_ien);
		अगर (enable)
			पंचांगp |= QMI_INTR_EN_SINGLE_ECC;
		अन्यथा
			पंचांगp &= ~QMI_INTR_EN_SINGLE_ECC;
		ioग_लिखो32be(पंचांगp, &fman->qmi_regs->fmqm_ien);
		अवरोध;
	हाल FMAN_EX_QMI_DOUBLE_ECC:
		पंचांगp = ioपढ़ो32be(&fman->qmi_regs->fmqm_eien);
		अगर (enable)
			पंचांगp |= QMI_ERR_INTR_EN_DOUBLE_ECC;
		अन्यथा
			पंचांगp &= ~QMI_ERR_INTR_EN_DOUBLE_ECC;
		ioग_लिखो32be(पंचांगp, &fman->qmi_regs->fmqm_eien);
		अवरोध;
	हाल FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID:
		पंचांगp = ioपढ़ो32be(&fman->qmi_regs->fmqm_eien);
		अगर (enable)
			पंचांगp |= QMI_ERR_INTR_EN_DEQ_FROM_DEF;
		अन्यथा
			पंचांगp &= ~QMI_ERR_INTR_EN_DEQ_FROM_DEF;
		ioग_लिखो32be(पंचांगp, &fman->qmi_regs->fmqm_eien);
		अवरोध;
	हाल FMAN_EX_BMI_LIST_RAM_ECC:
		पंचांगp = ioपढ़ो32be(&fman->bmi_regs->fmbm_ier);
		अगर (enable)
			पंचांगp |= BMI_ERR_INTR_EN_LIST_RAM_ECC;
		अन्यथा
			पंचांगp &= ~BMI_ERR_INTR_EN_LIST_RAM_ECC;
		ioग_लिखो32be(पंचांगp, &fman->bmi_regs->fmbm_ier);
		अवरोध;
	हाल FMAN_EX_BMI_STORAGE_PROखाता_ECC:
		पंचांगp = ioपढ़ो32be(&fman->bmi_regs->fmbm_ier);
		अगर (enable)
			पंचांगp |= BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC;
		अन्यथा
			पंचांगp &= ~BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC;
		ioग_लिखो32be(पंचांगp, &fman->bmi_regs->fmbm_ier);
		अवरोध;
	हाल FMAN_EX_BMI_STATISTICS_RAM_ECC:
		पंचांगp = ioपढ़ो32be(&fman->bmi_regs->fmbm_ier);
		अगर (enable)
			पंचांगp |= BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
		अन्यथा
			पंचांगp &= ~BMI_ERR_INTR_EN_STATISTICS_RAM_ECC;
		ioग_लिखो32be(पंचांगp, &fman->bmi_regs->fmbm_ier);
		अवरोध;
	हाल FMAN_EX_BMI_DISPATCH_RAM_ECC:
		पंचांगp = ioपढ़ो32be(&fman->bmi_regs->fmbm_ier);
		अगर (enable)
			पंचांगp |= BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
		अन्यथा
			पंचांगp &= ~BMI_ERR_INTR_EN_DISPATCH_RAM_ECC;
		ioग_लिखो32be(पंचांगp, &fman->bmi_regs->fmbm_ier);
		अवरोध;
	हाल FMAN_EX_IRAM_ECC:
		पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fm_rie);
		अगर (enable) अणु
			/* enable ECC अगर not enabled */
			enable_rams_ecc(fman->fpm_regs);
			/* enable ECC पूर्णांकerrupts */
			पंचांगp |= FPM_IRAM_ECC_ERR_EX_EN;
		पूर्ण अन्यथा अणु
			/* ECC mechanism may be disabled,
			 * depending on driver status
			 */
			disable_rams_ecc(fman->fpm_regs);
			पंचांगp &= ~FPM_IRAM_ECC_ERR_EX_EN;
		पूर्ण
		ioग_लिखो32be(पंचांगp, &fman->fpm_regs->fm_rie);
		अवरोध;
	हाल FMAN_EX_MURAM_ECC:
		पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fm_rie);
		अगर (enable) अणु
			/* enable ECC अगर not enabled */
			enable_rams_ecc(fman->fpm_regs);
			/* enable ECC पूर्णांकerrupts */
			पंचांगp |= FPM_MURAM_ECC_ERR_EX_EN;
		पूर्ण अन्यथा अणु
			/* ECC mechanism may be disabled,
			 * depending on driver status
			 */
			disable_rams_ecc(fman->fpm_regs);
			पंचांगp &= ~FPM_MURAM_ECC_ERR_EX_EN;
		पूर्ण
		ioग_लिखो32be(पंचांगp, &fman->fpm_regs->fm_rie);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम resume(काष्ठा fman_fpm_regs __iomem *fpm_rg)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&fpm_rg->fmfp_ee);
	/* clear पंचांगp_reg event bits in order not to clear standing events */
	पंचांगp &= ~(FPM_EV_MASK_DOUBLE_ECC |
		 FPM_EV_MASK_STALL | FPM_EV_MASK_SINGLE_ECC);
	पंचांगp |= FPM_EV_MASK_RELEASE_FM;

	ioग_लिखो32be(पंचांगp, &fpm_rg->fmfp_ee);
पूर्ण

अटल पूर्णांक fill_soc_specअगरic_params(काष्ठा fman_state_काष्ठा *state)
अणु
	u8 minor = state->rev_info.minor;
	/* P4080 - Major 2
	 * P2041/P3041/P5020/P5040 - Major 3
	 * Tx/Bx - Major 6
	 */
	चयन (state->rev_info.major) अणु
	हाल 3:
		state->bmi_max_fअगरo_size	= 160 * 1024;
		state->fm_iram_size		= 64 * 1024;
		state->dma_thresh_max_commq	= 31;
		state->dma_thresh_max_buf	= 127;
		state->qmi_max_num_of_tnums	= 64;
		state->qmi_def_tnums_thresh	= 48;
		state->bmi_max_num_of_tasks	= 128;
		state->max_num_of_खोलो_dmas	= 32;
		state->fm_port_num_of_cg	= 256;
		state->num_of_rx_ports	= 6;
		state->total_fअगरo_size	= 136 * 1024;
		अवरोध;

	हाल 2:
		state->bmi_max_fअगरo_size	= 160 * 1024;
		state->fm_iram_size		= 64 * 1024;
		state->dma_thresh_max_commq	= 31;
		state->dma_thresh_max_buf	= 127;
		state->qmi_max_num_of_tnums	= 64;
		state->qmi_def_tnums_thresh	= 48;
		state->bmi_max_num_of_tasks	= 128;
		state->max_num_of_खोलो_dmas	= 32;
		state->fm_port_num_of_cg	= 256;
		state->num_of_rx_ports	= 5;
		state->total_fअगरo_size	= 100 * 1024;
		अवरोध;

	हाल 6:
		state->dma_thresh_max_commq	= 83;
		state->dma_thresh_max_buf	= 127;
		state->qmi_max_num_of_tnums	= 64;
		state->qmi_def_tnums_thresh	= 32;
		state->fm_port_num_of_cg	= 256;

		/* FManV3L */
		अगर (minor == 1 || minor == 4) अणु
			state->bmi_max_fअगरo_size	= 192 * 1024;
			state->bmi_max_num_of_tasks	= 64;
			state->max_num_of_खोलो_dmas	= 32;
			state->num_of_rx_ports		= 5;
			अगर (minor == 1)
				state->fm_iram_size	= 32 * 1024;
			अन्यथा
				state->fm_iram_size	= 64 * 1024;
			state->total_fअगरo_size		= 156 * 1024;
		पूर्ण
		/* FManV3H */
		अन्यथा अगर (minor == 0 || minor == 2 || minor == 3) अणु
			state->bmi_max_fअगरo_size	= 384 * 1024;
			state->fm_iram_size		= 64 * 1024;
			state->bmi_max_num_of_tasks	= 128;
			state->max_num_of_खोलो_dmas	= 84;
			state->num_of_rx_ports		= 8;
			state->total_fअगरo_size		= 295 * 1024;
		पूर्ण अन्यथा अणु
			pr_err("Unsupported FManv3 version\n");
			वापस -EINVAL;
		पूर्ण

		अवरोध;
	शेष:
		pr_err("Unsupported FMan version\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool is_init_करोne(काष्ठा fman_cfg *cfg)
अणु
	/* Checks अगर FMan driver parameters were initialized */
	अगर (!cfg)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम मुक्त_init_resources(काष्ठा fman *fman)
अणु
	अगर (fman->cam_offset)
		fman_muram_मुक्त_mem(fman->muram, fman->cam_offset,
				    fman->cam_size);
	अगर (fman->fअगरo_offset)
		fman_muram_मुक्त_mem(fman->muram, fman->fअगरo_offset,
				    fman->fअगरo_size);
पूर्ण

अटल irqवापस_t bmi_err_event(काष्ठा fman *fman)
अणु
	u32 event, mask, क्रमce;
	काष्ठा fman_bmi_regs __iomem *bmi_rg = fman->bmi_regs;
	irqवापस_t ret = IRQ_NONE;

	event = ioपढ़ो32be(&bmi_rg->fmbm_ievr);
	mask = ioपढ़ो32be(&bmi_rg->fmbm_ier);
	event &= mask;
	/* clear the क्रमced events */
	क्रमce = ioपढ़ो32be(&bmi_rg->fmbm_अगरr);
	अगर (क्रमce & event)
		ioग_लिखो32be(क्रमce & ~event, &bmi_rg->fmbm_अगरr);
	/* clear the acknowledged events */
	ioग_लिखो32be(event, &bmi_rg->fmbm_ievr);

	अगर (event & BMI_ERR_INTR_EN_STORAGE_PROखाता_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_BMI_STORAGE_PROखाता_ECC);
	अगर (event & BMI_ERR_INTR_EN_LIST_RAM_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_BMI_LIST_RAM_ECC);
	अगर (event & BMI_ERR_INTR_EN_STATISTICS_RAM_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_BMI_STATISTICS_RAM_ECC);
	अगर (event & BMI_ERR_INTR_EN_DISPATCH_RAM_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_BMI_DISPATCH_RAM_ECC);

	वापस ret;
पूर्ण

अटल irqवापस_t qmi_err_event(काष्ठा fman *fman)
अणु
	u32 event, mask, क्रमce;
	काष्ठा fman_qmi_regs __iomem *qmi_rg = fman->qmi_regs;
	irqवापस_t ret = IRQ_NONE;

	event = ioपढ़ो32be(&qmi_rg->fmqm_eie);
	mask = ioपढ़ो32be(&qmi_rg->fmqm_eien);
	event &= mask;

	/* clear the क्रमced events */
	क्रमce = ioपढ़ो32be(&qmi_rg->fmqm_eअगर);
	अगर (क्रमce & event)
		ioग_लिखो32be(क्रमce & ~event, &qmi_rg->fmqm_eअगर);
	/* clear the acknowledged events */
	ioग_लिखो32be(event, &qmi_rg->fmqm_eie);

	अगर (event & QMI_ERR_INTR_EN_DOUBLE_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_QMI_DOUBLE_ECC);
	अगर (event & QMI_ERR_INTR_EN_DEQ_FROM_DEF)
		ret = fman->exception_cb(fman,
					 FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID);

	वापस ret;
पूर्ण

अटल irqवापस_t dma_err_event(काष्ठा fman *fman)
अणु
	u32 status, mask, com_id;
	u8 tnum, port_id, relative_port_id;
	u16 liodn;
	काष्ठा fman_dma_regs __iomem *dma_rg = fman->dma_regs;
	irqवापस_t ret = IRQ_NONE;

	status = ioपढ़ो32be(&dma_rg->fmdmsr);
	mask = ioपढ़ो32be(&dma_rg->fmdmmr);

	/* clear DMA_STATUS_BUS_ERR अगर mask has no DMA_MODE_BER */
	अगर ((mask & DMA_MODE_BER) != DMA_MODE_BER)
		status &= ~DMA_STATUS_BUS_ERR;

	/* clear relevant bits अगर mask has no DMA_MODE_ECC */
	अगर ((mask & DMA_MODE_ECC) != DMA_MODE_ECC)
		status &= ~(DMA_STATUS_FM_SPDAT_ECC |
			    DMA_STATUS_READ_ECC |
			    DMA_STATUS_SYSTEM_WRITE_ECC |
			    DMA_STATUS_FM_WRITE_ECC);

	/* clear set events */
	ioग_लिखो32be(status, &dma_rg->fmdmsr);

	अगर (status & DMA_STATUS_BUS_ERR) अणु
		u64 addr;

		addr = (u64)ioपढ़ो32be(&dma_rg->fmdmtal);
		addr |= ((u64)(ioपढ़ो32be(&dma_rg->fmdmtah)) << 32);

		com_id = ioपढ़ो32be(&dma_rg->fmdmtcid);
		port_id = (u8)(((com_id & DMA_TRANSFER_PORTID_MASK) >>
			       DMA_TRANSFER_PORTID_SHIFT));
		relative_port_id =
		hw_port_id_to_sw_port_id(fman->state->rev_info.major, port_id);
		tnum = (u8)((com_id & DMA_TRANSFER_TNUM_MASK) >>
			    DMA_TRANSFER_TNUM_SHIFT);
		liodn = (u16)(com_id & DMA_TRANSFER_LIODN_MASK);
		ret = fman->bus_error_cb(fman, relative_port_id, addr, tnum,
					 liodn);
	पूर्ण
	अगर (status & DMA_STATUS_FM_SPDAT_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_DMA_SINGLE_PORT_ECC);
	अगर (status & DMA_STATUS_READ_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_DMA_READ_ECC);
	अगर (status & DMA_STATUS_SYSTEM_WRITE_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_DMA_SYSTEM_WRITE_ECC);
	अगर (status & DMA_STATUS_FM_WRITE_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_DMA_FM_WRITE_ECC);

	वापस ret;
पूर्ण

अटल irqवापस_t fpm_err_event(काष्ठा fman *fman)
अणु
	u32 event;
	काष्ठा fman_fpm_regs __iomem *fpm_rg = fman->fpm_regs;
	irqवापस_t ret = IRQ_NONE;

	event = ioपढ़ो32be(&fpm_rg->fmfp_ee);
	/* clear the all occurred events */
	ioग_लिखो32be(event, &fpm_rg->fmfp_ee);

	अगर ((event & FPM_EV_MASK_DOUBLE_ECC) &&
	    (event & FPM_EV_MASK_DOUBLE_ECC_EN))
		ret = fman->exception_cb(fman, FMAN_EX_FPM_DOUBLE_ECC);
	अगर ((event & FPM_EV_MASK_STALL) && (event & FPM_EV_MASK_STALL_EN))
		ret = fman->exception_cb(fman, FMAN_EX_FPM_STALL_ON_TASKS);
	अगर ((event & FPM_EV_MASK_SINGLE_ECC) &&
	    (event & FPM_EV_MASK_SINGLE_ECC_EN))
		ret = fman->exception_cb(fman, FMAN_EX_FPM_SINGLE_ECC);

	वापस ret;
पूर्ण

अटल irqवापस_t muram_err_पूर्णांकr(काष्ठा fman *fman)
अणु
	u32 event, mask;
	काष्ठा fman_fpm_regs __iomem *fpm_rg = fman->fpm_regs;
	irqवापस_t ret = IRQ_NONE;

	event = ioपढ़ो32be(&fpm_rg->fm_rcr);
	mask = ioपढ़ो32be(&fpm_rg->fm_rie);

	/* clear MURAM event bit (करो not clear IRAM event) */
	ioग_लिखो32be(event & ~FPM_RAM_IRAM_ECC, &fpm_rg->fm_rcr);

	अगर ((mask & FPM_MURAM_ECC_ERR_EX_EN) && (event & FPM_RAM_MURAM_ECC))
		ret = fman->exception_cb(fman, FMAN_EX_MURAM_ECC);

	वापस ret;
पूर्ण

अटल irqवापस_t qmi_event(काष्ठा fman *fman)
अणु
	u32 event, mask, क्रमce;
	काष्ठा fman_qmi_regs __iomem *qmi_rg = fman->qmi_regs;
	irqवापस_t ret = IRQ_NONE;

	event = ioपढ़ो32be(&qmi_rg->fmqm_ie);
	mask = ioपढ़ो32be(&qmi_rg->fmqm_ien);
	event &= mask;
	/* clear the क्रमced events */
	क्रमce = ioपढ़ो32be(&qmi_rg->fmqm_अगर);
	अगर (क्रमce & event)
		ioग_लिखो32be(क्रमce & ~event, &qmi_rg->fmqm_अगर);
	/* clear the acknowledged events */
	ioग_लिखो32be(event, &qmi_rg->fmqm_ie);

	अगर (event & QMI_INTR_EN_SINGLE_ECC)
		ret = fman->exception_cb(fman, FMAN_EX_QMI_SINGLE_ECC);

	वापस ret;
पूर्ण

अटल व्योम enable_समय_stamp(काष्ठा fman *fman)
अणु
	काष्ठा fman_fpm_regs __iomem *fpm_rg = fman->fpm_regs;
	u16 fm_clk_freq = fman->state->fm_clk_freq;
	u32 पंचांगp, पूर्णांकgr, ts_freq, frac;

	ts_freq = (u32)(1 << fman->state->count1_micro_bit);
	/* configure बारtamp so that bit 8 will count 1 microsecond
	 * Find effective count rate at TIMESTAMP least signअगरicant bits:
	 * Effective_Count_Rate = 1MHz x 2^8 = 256MHz
	 * Find frequency ratio between effective count rate and the घड़ी:
	 * Effective_Count_Rate / CLK e.g. क्रम 600 MHz घड़ी:
	 * 256/600 = 0.4266666...
	 */

	पूर्णांकgr = ts_freq / fm_clk_freq;
	/* we multiply by 2^16 to keep the fraction of the भागision
	 * we करो not भाग back, since we ग_लिखो this value as a fraction
	 * see spec
	 */

	frac = ((ts_freq << 16) - (पूर्णांकgr << 16) * fm_clk_freq) / fm_clk_freq;
	/* we check reमुख्यder of the भागision in order to round up अगर not पूर्णांक */
	अगर (((ts_freq << 16) - (पूर्णांकgr << 16) * fm_clk_freq) % fm_clk_freq)
		frac++;

	पंचांगp = (पूर्णांकgr << FPM_TS_INT_SHIFT) | (u16)frac;
	ioग_लिखो32be(पंचांगp, &fpm_rg->fmfp_tsc2);

	/* enable बारtamp with original घड़ी */
	ioग_लिखो32be(FPM_TS_CTL_EN, &fpm_rg->fmfp_tsc1);
	fman->state->enabled_समय_stamp = true;
पूर्ण

अटल पूर्णांक clear_iram(काष्ठा fman *fman)
अणु
	काष्ठा fman_iram_regs __iomem *iram;
	पूर्णांक i, count;

	iram = fman->base_addr + IMEM_OFFSET;

	/* Enable the स्वतः-increment */
	ioग_लिखो32be(IRAM_IADD_AIE, &iram->iadd);
	count = 100;
	करो अणु
		udelay(1);
	पूर्ण जबतक ((ioपढ़ो32be(&iram->iadd) != IRAM_IADD_AIE) && --count);
	अगर (count == 0)
		वापस -EBUSY;

	क्रम (i = 0; i < (fman->state->fm_iram_size / 4); i++)
		ioग_लिखो32be(0xffffffff, &iram->idata);

	ioग_लिखो32be(fman->state->fm_iram_size - 4, &iram->iadd);
	count = 100;
	करो अणु
		udelay(1);
	पूर्ण जबतक ((ioपढ़ो32be(&iram->idata) != 0xffffffff) && --count);
	अगर (count == 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल u32 get_exception_flag(क्रमागत fman_exceptions exception)
अणु
	u32 bit_mask;

	चयन (exception) अणु
	हाल FMAN_EX_DMA_BUS_ERROR:
		bit_mask = EX_DMA_BUS_ERROR;
		अवरोध;
	हाल FMAN_EX_DMA_SINGLE_PORT_ECC:
		bit_mask = EX_DMA_SINGLE_PORT_ECC;
		अवरोध;
	हाल FMAN_EX_DMA_READ_ECC:
		bit_mask = EX_DMA_READ_ECC;
		अवरोध;
	हाल FMAN_EX_DMA_SYSTEM_WRITE_ECC:
		bit_mask = EX_DMA_SYSTEM_WRITE_ECC;
		अवरोध;
	हाल FMAN_EX_DMA_FM_WRITE_ECC:
		bit_mask = EX_DMA_FM_WRITE_ECC;
		अवरोध;
	हाल FMAN_EX_FPM_STALL_ON_TASKS:
		bit_mask = EX_FPM_STALL_ON_TASKS;
		अवरोध;
	हाल FMAN_EX_FPM_SINGLE_ECC:
		bit_mask = EX_FPM_SINGLE_ECC;
		अवरोध;
	हाल FMAN_EX_FPM_DOUBLE_ECC:
		bit_mask = EX_FPM_DOUBLE_ECC;
		अवरोध;
	हाल FMAN_EX_QMI_SINGLE_ECC:
		bit_mask = EX_QMI_SINGLE_ECC;
		अवरोध;
	हाल FMAN_EX_QMI_DOUBLE_ECC:
		bit_mask = EX_QMI_DOUBLE_ECC;
		अवरोध;
	हाल FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID:
		bit_mask = EX_QMI_DEQ_FROM_UNKNOWN_PORTID;
		अवरोध;
	हाल FMAN_EX_BMI_LIST_RAM_ECC:
		bit_mask = EX_BMI_LIST_RAM_ECC;
		अवरोध;
	हाल FMAN_EX_BMI_STORAGE_PROखाता_ECC:
		bit_mask = EX_BMI_STORAGE_PROखाता_ECC;
		अवरोध;
	हाल FMAN_EX_BMI_STATISTICS_RAM_ECC:
		bit_mask = EX_BMI_STATISTICS_RAM_ECC;
		अवरोध;
	हाल FMAN_EX_BMI_DISPATCH_RAM_ECC:
		bit_mask = EX_BMI_DISPATCH_RAM_ECC;
		अवरोध;
	हाल FMAN_EX_MURAM_ECC:
		bit_mask = EX_MURAM_ECC;
		अवरोध;
	शेष:
		bit_mask = 0;
		अवरोध;
	पूर्ण

	वापस bit_mask;
पूर्ण

अटल पूर्णांक get_module_event(क्रमागत fman_event_modules module, u8 mod_id,
			    क्रमागत fman_पूर्णांकr_type पूर्णांकr_type)
अणु
	पूर्णांक event;

	चयन (module) अणु
	हाल FMAN_MOD_MAC:
		अगर (पूर्णांकr_type == FMAN_INTR_TYPE_ERR)
			event = FMAN_EV_ERR_MAC0 + mod_id;
		अन्यथा
			event = FMAN_EV_MAC0 + mod_id;
		अवरोध;
	हाल FMAN_MOD_FMAN_CTRL:
		अगर (पूर्णांकr_type == FMAN_INTR_TYPE_ERR)
			event = FMAN_EV_CNT;
		अन्यथा
			event = (FMAN_EV_FMAN_CTRL_0 + mod_id);
		अवरोध;
	हाल FMAN_MOD_DUMMY_LAST:
		event = FMAN_EV_CNT;
		अवरोध;
	शेष:
		event = FMAN_EV_CNT;
		अवरोध;
	पूर्ण

	वापस event;
पूर्ण

अटल पूर्णांक set_size_of_fअगरo(काष्ठा fman *fman, u8 port_id, u32 *size_of_fअगरo,
			    u32 *extra_size_of_fअगरo)
अणु
	काष्ठा fman_bmi_regs __iomem *bmi_rg = fman->bmi_regs;
	u32 fअगरo = *size_of_fअगरo;
	u32 extra_fअगरo = *extra_size_of_fअगरo;
	u32 पंचांगp;

	/* अगर this is the first समय a port requires extra_fअगरo_pool_size,
	 * the total extra_fअगरo_pool_size must be initialized to 1 buffer per
	 * port
	 */
	अगर (extra_fअगरo && !fman->state->extra_fअगरo_pool_size)
		fman->state->extra_fअगरo_pool_size =
			fman->state->num_of_rx_ports * FMAN_BMI_FIFO_UNITS;

	fman->state->extra_fअगरo_pool_size =
		max(fman->state->extra_fअगरo_pool_size, extra_fअगरo);

	/* check that there are enough uncommitted fअगरo size */
	अगर ((fman->state->accumulated_fअगरo_size + fअगरo) >
	    (fman->state->total_fअगरo_size -
	    fman->state->extra_fअगरo_pool_size)) अणु
		dev_err(fman->dev, "%s: Requested fifo size and extra size exceed total FIFO size.\n",
			__func__);
		वापस -EAGAIN;
	पूर्ण

	/* Read, modअगरy and ग_लिखो to HW */
	पंचांगp = (fअगरo / FMAN_BMI_FIFO_UNITS - 1) |
	       ((extra_fअगरo / FMAN_BMI_FIFO_UNITS) <<
	       BMI_EXTRA_FIFO_SIZE_SHIFT);
	ioग_लिखो32be(पंचांगp, &bmi_rg->fmbm_pfs[port_id - 1]);

	/* update accumulated */
	fman->state->accumulated_fअगरo_size += fअगरo;

	वापस 0;
पूर्ण

अटल पूर्णांक set_num_of_tasks(काष्ठा fman *fman, u8 port_id, u8 *num_of_tasks,
			    u8 *num_of_extra_tasks)
अणु
	काष्ठा fman_bmi_regs __iomem *bmi_rg = fman->bmi_regs;
	u8 tasks = *num_of_tasks;
	u8 extra_tasks = *num_of_extra_tasks;
	u32 पंचांगp;

	अगर (extra_tasks)
		fman->state->extra_tasks_pool_size =
		max(fman->state->extra_tasks_pool_size, extra_tasks);

	/* check that there are enough uncommitted tasks */
	अगर ((fman->state->accumulated_num_of_tasks + tasks) >
	    (fman->state->total_num_of_tasks -
	     fman->state->extra_tasks_pool_size)) अणु
		dev_err(fman->dev, "%s: Requested num_of_tasks and extra tasks pool for fm%d exceed total num_of_tasks.\n",
			__func__, fman->state->fm_id);
		वापस -EAGAIN;
	पूर्ण
	/* update accumulated */
	fman->state->accumulated_num_of_tasks += tasks;

	/* Write to HW */
	पंचांगp = ioपढ़ो32be(&bmi_rg->fmbm_pp[port_id - 1]) &
	    ~(BMI_NUM_OF_TASKS_MASK | BMI_NUM_OF_EXTRA_TASKS_MASK);
	पंचांगp |= ((u32)((tasks - 1) << BMI_NUM_OF_TASKS_SHIFT) |
		(u32)(extra_tasks << BMI_EXTRA_NUM_OF_TASKS_SHIFT));
	ioग_लिखो32be(पंचांगp, &bmi_rg->fmbm_pp[port_id - 1]);

	वापस 0;
पूर्ण

अटल पूर्णांक set_num_of_खोलो_dmas(काष्ठा fman *fman, u8 port_id,
				u8 *num_of_खोलो_dmas,
				u8 *num_of_extra_खोलो_dmas)
अणु
	काष्ठा fman_bmi_regs __iomem *bmi_rg = fman->bmi_regs;
	u8 खोलो_dmas = *num_of_खोलो_dmas;
	u8 extra_खोलो_dmas = *num_of_extra_खोलो_dmas;
	u8 total_num_dmas = 0, current_val = 0, current_extra_val = 0;
	u32 पंचांगp;

	अगर (!खोलो_dmas) अणु
		/* Configuration according to values in the HW.
		 * पढ़ो the current number of खोलो Dma's
		 */
		पंचांगp = ioपढ़ो32be(&bmi_rg->fmbm_pp[port_id - 1]);
		current_extra_val = (u8)((पंचांगp & BMI_NUM_OF_EXTRA_DMAS_MASK) >>
					 BMI_EXTRA_NUM_OF_DMAS_SHIFT);

		पंचांगp = ioपढ़ो32be(&bmi_rg->fmbm_pp[port_id - 1]);
		current_val = (u8)(((पंचांगp & BMI_NUM_OF_DMAS_MASK) >>
				   BMI_NUM_OF_DMAS_SHIFT) + 1);

		/* This is the first configuration and user did not
		 * specअगरy value (!खोलो_dmas), reset values will be used
		 * and we just save these values क्रम resource management
		 */
		fman->state->extra_खोलो_dmas_pool_size =
			(u8)max(fman->state->extra_खोलो_dmas_pool_size,
				current_extra_val);
		fman->state->accumulated_num_of_खोलो_dmas += current_val;
		*num_of_खोलो_dmas = current_val;
		*num_of_extra_खोलो_dmas = current_extra_val;
		वापस 0;
	पूर्ण

	अगर (extra_खोलो_dmas > current_extra_val)
		fman->state->extra_खोलो_dmas_pool_size =
		    (u8)max(fman->state->extra_खोलो_dmas_pool_size,
			    extra_खोलो_dmas);

	अगर ((fman->state->rev_info.major < 6) &&
	    (fman->state->accumulated_num_of_खोलो_dmas - current_val +
	     खोलो_dmas > fman->state->max_num_of_खोलो_dmas)) अणु
		dev_err(fman->dev, "%s: Requested num_of_open_dmas for fm%d exceeds total num_of_open_dmas.\n",
			__func__, fman->state->fm_id);
		वापस -EAGAIN;
	पूर्ण अन्यथा अगर ((fman->state->rev_info.major >= 6) &&
		   !((fman->state->rev_info.major == 6) &&
		   (fman->state->rev_info.minor == 0)) &&
		   (fman->state->accumulated_num_of_खोलो_dmas -
		   current_val + खोलो_dmas >
		   fman->state->dma_thresh_max_commq + 1)) अणु
		dev_err(fman->dev, "%s: Requested num_of_open_dmas for fm%d exceeds DMA Command queue (%d)\n",
			__func__, fman->state->fm_id,
		       fman->state->dma_thresh_max_commq + 1);
		वापस -EAGAIN;
	पूर्ण

	WARN_ON(fman->state->accumulated_num_of_खोलो_dmas < current_val);
	/* update acummulated */
	fman->state->accumulated_num_of_खोलो_dmas -= current_val;
	fman->state->accumulated_num_of_खोलो_dmas += खोलो_dmas;

	अगर (fman->state->rev_info.major < 6)
		total_num_dmas =
		    (u8)(fman->state->accumulated_num_of_खोलो_dmas +
		    fman->state->extra_खोलो_dmas_pool_size);

	/* calculate reg */
	पंचांगp = ioपढ़ो32be(&bmi_rg->fmbm_pp[port_id - 1]) &
	    ~(BMI_NUM_OF_DMAS_MASK | BMI_NUM_OF_EXTRA_DMAS_MASK);
	पंचांगp |= (u32)(((खोलो_dmas - 1) << BMI_NUM_OF_DMAS_SHIFT) |
			   (extra_खोलो_dmas << BMI_EXTRA_NUM_OF_DMAS_SHIFT));
	ioग_लिखो32be(पंचांगp, &bmi_rg->fmbm_pp[port_id - 1]);

	/* update total num of DMA's with committed number of खोलो DMAS,
	 * and max uncommitted pool.
	 */
	अगर (total_num_dmas) अणु
		पंचांगp = ioपढ़ो32be(&bmi_rg->fmbm_cfg2) & ~BMI_CFG2_DMAS_MASK;
		पंचांगp |= (u32)(total_num_dmas - 1) << BMI_CFG2_DMAS_SHIFT;
		ioग_लिखो32be(पंचांगp, &bmi_rg->fmbm_cfg2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fman_config(काष्ठा fman *fman)
अणु
	व्योम __iomem *base_addr;
	पूर्णांक err;

	base_addr = fman->dts_params.base_addr;

	fman->state = kzalloc(माप(*fman->state), GFP_KERNEL);
	अगर (!fman->state)
		जाओ err_fm_state;

	/* Allocate the FM driver's parameters काष्ठाure */
	fman->cfg = kzalloc(माप(*fman->cfg), GFP_KERNEL);
	अगर (!fman->cfg)
		जाओ err_fm_drv;

	/* Initialize MURAM block */
	fman->muram =
		fman_muram_init(fman->dts_params.muram_res.start,
				resource_size(&fman->dts_params.muram_res));
	अगर (!fman->muram)
		जाओ err_fm_soc_specअगरic;

	/* Initialize FM parameters which will be kept by the driver */
	fman->state->fm_id = fman->dts_params.id;
	fman->state->fm_clk_freq = fman->dts_params.clk_freq;
	fman->state->qman_channel_base = fman->dts_params.qman_channel_base;
	fman->state->num_of_qman_channels =
		fman->dts_params.num_of_qman_channels;
	fman->state->res = fman->dts_params.res;
	fman->exception_cb = fman_exceptions;
	fman->bus_error_cb = fman_bus_error;
	fman->fpm_regs = base_addr + FPM_OFFSET;
	fman->bmi_regs = base_addr + BMI_OFFSET;
	fman->qmi_regs = base_addr + QMI_OFFSET;
	fman->dma_regs = base_addr + DMA_OFFSET;
	fman->hwp_regs = base_addr + HWP_OFFSET;
	fman->kg_regs = base_addr + KG_OFFSET;
	fman->base_addr = base_addr;

	spin_lock_init(&fman->spinlock);
	fman_defconfig(fman->cfg);

	fman->state->extra_fअगरo_pool_size = 0;
	fman->state->exceptions = (EX_DMA_BUS_ERROR                 |
					EX_DMA_READ_ECC              |
					EX_DMA_SYSTEM_WRITE_ECC      |
					EX_DMA_FM_WRITE_ECC          |
					EX_FPM_STALL_ON_TASKS        |
					EX_FPM_SINGLE_ECC            |
					EX_FPM_DOUBLE_ECC            |
					EX_QMI_DEQ_FROM_UNKNOWN_PORTID |
					EX_BMI_LIST_RAM_ECC          |
					EX_BMI_STORAGE_PROखाता_ECC   |
					EX_BMI_STATISTICS_RAM_ECC    |
					EX_MURAM_ECC                 |
					EX_BMI_DISPATCH_RAM_ECC      |
					EX_QMI_DOUBLE_ECC            |
					EX_QMI_SINGLE_ECC);

	/* Read FMan revision क्रम future use*/
	fman_get_revision(fman, &fman->state->rev_info);

	err = fill_soc_specअगरic_params(fman->state);
	अगर (err)
		जाओ err_fm_soc_specअगरic;

	/* FM_AID_MODE_NO_TNUM_SW005 Errata workaround */
	अगर (fman->state->rev_info.major >= 6)
		fman->cfg->dma_aid_mode = FMAN_DMA_AID_OUT_PORT_ID;

	fman->cfg->qmi_def_tnums_thresh = fman->state->qmi_def_tnums_thresh;

	fman->state->total_num_of_tasks =
	(u8)DFLT_TOTAL_NUM_OF_TASKS(fman->state->rev_info.major,
				    fman->state->rev_info.minor,
				    fman->state->bmi_max_num_of_tasks);

	अगर (fman->state->rev_info.major < 6) अणु
		fman->cfg->dma_comm_qtsh_clr_emer =
		(u8)DFLT_DMA_COMM_Q_LOW(fman->state->rev_info.major,
					fman->state->dma_thresh_max_commq);

		fman->cfg->dma_comm_qtsh_asrt_emer =
		(u8)DFLT_DMA_COMM_Q_HIGH(fman->state->rev_info.major,
					 fman->state->dma_thresh_max_commq);

		fman->cfg->dma_cam_num_of_entries =
		DFLT_DMA_CAM_NUM_OF_ENTRIES(fman->state->rev_info.major);

		fman->cfg->dma_पढ़ो_buf_tsh_clr_emer =
		DFLT_DMA_READ_INT_BUF_LOW(fman->state->dma_thresh_max_buf);

		fman->cfg->dma_पढ़ो_buf_tsh_asrt_emer =
		DFLT_DMA_READ_INT_BUF_HIGH(fman->state->dma_thresh_max_buf);

		fman->cfg->dma_ग_लिखो_buf_tsh_clr_emer =
		DFLT_DMA_WRITE_INT_BUF_LOW(fman->state->dma_thresh_max_buf);

		fman->cfg->dma_ग_लिखो_buf_tsh_asrt_emer =
		DFLT_DMA_WRITE_INT_BUF_HIGH(fman->state->dma_thresh_max_buf);

		fman->cfg->dma_axi_dbg_num_of_beats =
		DFLT_AXI_DBG_NUM_OF_BEATS;
	पूर्ण

	वापस 0;

err_fm_soc_specअगरic:
	kमुक्त(fman->cfg);
err_fm_drv:
	kमुक्त(fman->state);
err_fm_state:
	kमुक्त(fman);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fman_reset(काष्ठा fman *fman)
अणु
	u32 count;
	पूर्णांक err = 0;

	अगर (fman->state->rev_info.major < 6) अणु
		ioग_लिखो32be(FPM_RSTC_FM_RESET, &fman->fpm_regs->fm_rstc);
		/* Wait क्रम reset completion */
		count = 100;
		करो अणु
			udelay(1);
		पूर्ण जबतक (((ioपढ़ो32be(&fman->fpm_regs->fm_rstc)) &
			 FPM_RSTC_FM_RESET) && --count);
		अगर (count == 0)
			err = -EBUSY;

		जाओ _वापस;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_PPC
		काष्ठा device_node *guts_node;
		काष्ठा ccsr_guts __iomem *guts_regs;
		u32 devdisr2, reg;

		/* Errata A007273 */
		guts_node =
			of_find_compatible_node(शून्य, शून्य,
						"fsl,qoriq-device-config-2.0");
		अगर (!guts_node) अणु
			dev_err(fman->dev, "%s: Couldn't find guts node\n",
				__func__);
			जाओ guts_node;
		पूर्ण

		guts_regs = of_iomap(guts_node, 0);
		अगर (!guts_regs) अणु
			dev_err(fman->dev, "%s: Couldn't map %pOF regs\n",
				__func__, guts_node);
			जाओ guts_regs;
		पूर्ण
#घोषणा FMAN1_ALL_MACS_MASK	0xFCC00000
#घोषणा FMAN2_ALL_MACS_MASK	0x000FCC00
		/* Read current state */
		devdisr2 = ioपढ़ो32be(&guts_regs->devdisr2);
		अगर (fman->dts_params.id == 0)
			reg = devdisr2 & ~FMAN1_ALL_MACS_MASK;
		अन्यथा
			reg = devdisr2 & ~FMAN2_ALL_MACS_MASK;

		/* Enable all MACs */
		ioग_लिखो32be(reg, &guts_regs->devdisr2);
#पूर्ण_अगर

		/* Perक्रमm FMan reset */
		ioग_लिखो32be(FPM_RSTC_FM_RESET, &fman->fpm_regs->fm_rstc);

		/* Wait क्रम reset completion */
		count = 100;
		करो अणु
			udelay(1);
		पूर्ण जबतक (((ioपढ़ो32be(&fman->fpm_regs->fm_rstc)) &
			 FPM_RSTC_FM_RESET) && --count);
		अगर (count == 0) अणु
#अगर_घोषित CONFIG_PPC
			iounmap(guts_regs);
			of_node_put(guts_node);
#पूर्ण_अगर
			err = -EBUSY;
			जाओ _वापस;
		पूर्ण
#अगर_घोषित CONFIG_PPC

		/* Restore devdisr2 value */
		ioग_लिखो32be(devdisr2, &guts_regs->devdisr2);

		iounmap(guts_regs);
		of_node_put(guts_node);
#पूर्ण_अगर

		जाओ _वापस;

#अगर_घोषित CONFIG_PPC
guts_regs:
		of_node_put(guts_node);
guts_node:
		dev_dbg(fman->dev, "%s: Didn't perform FManV3 reset due to Errata A007273!\n",
			__func__);
#पूर्ण_अगर
	पूर्ण
_वापस:
	वापस err;
पूर्ण

अटल पूर्णांक fman_init(काष्ठा fman *fman)
अणु
	काष्ठा fman_cfg *cfg = शून्य;
	पूर्णांक err = 0, i, count;

	अगर (is_init_करोne(fman->cfg))
		वापस -EINVAL;

	fman->state->count1_micro_bit = FM_TIMESTAMP_1_USEC_BIT;

	cfg = fman->cfg;

	/* clear revision-dependent non existing exception */
	अगर (fman->state->rev_info.major < 6)
		fman->state->exceptions &= ~FMAN_EX_BMI_DISPATCH_RAM_ECC;

	अगर (fman->state->rev_info.major >= 6)
		fman->state->exceptions &= ~FMAN_EX_QMI_SINGLE_ECC;

	/* clear CPG */
	स_रखो_io((व्योम __iomem *)(fman->base_addr + CGP_OFFSET), 0,
		  fman->state->fm_port_num_of_cg);

	/* Save LIODN info beक्रमe FMan reset
	 * Skipping non-existent port 0 (i = 1)
	 */
	क्रम (i = 1; i < FMAN_LIODN_TBL; i++) अणु
		u32 liodn_base;

		fman->liodn_offset[i] =
			ioपढ़ो32be(&fman->bmi_regs->fmbm_spliodn[i - 1]);
		अगर (!IS_ENABLED(CONFIG_FSL_PAMU))
			जारी;
		liodn_base = ioपढ़ो32be(&fman->dma_regs->fmdmplr[i / 2]);
		अगर (i % 2) अणु
			/* FMDM_PLR LSB holds LIODN base क्रम odd ports */
			liodn_base &= DMA_LIODN_BASE_MASK;
		पूर्ण अन्यथा अणु
			/* FMDM_PLR MSB holds LIODN base क्रम even ports */
			liodn_base >>= DMA_LIODN_SHIFT;
			liodn_base &= DMA_LIODN_BASE_MASK;
		पूर्ण
		fman->liodn_base[i] = liodn_base;
	पूर्ण

	err = fman_reset(fman);
	अगर (err)
		वापस err;

	अगर (ioपढ़ो32be(&fman->qmi_regs->fmqm_gs) & QMI_GS_HALT_NOT_BUSY) अणु
		resume(fman->fpm_regs);
		/* Wait until QMI is not in halt not busy state */
		count = 100;
		करो अणु
			udelay(1);
		पूर्ण जबतक (((ioपढ़ो32be(&fman->qmi_regs->fmqm_gs)) &
			 QMI_GS_HALT_NOT_BUSY) && --count);
		अगर (count == 0)
			dev_warn(fman->dev, "%s: QMI is in halt not busy state\n",
				 __func__);
	पूर्ण

	अगर (clear_iram(fman) != 0)
		वापस -EINVAL;

	cfg->exceptions = fman->state->exceptions;

	/* Init DMA Registers */

	err = dma_init(fman);
	अगर (err != 0) अणु
		मुक्त_init_resources(fman);
		वापस err;
	पूर्ण

	/* Init FPM Registers */
	fpm_init(fman->fpm_regs, fman->cfg);

	/* define common resources */
	/* allocate MURAM क्रम FIFO according to total size */
	fman->fअगरo_offset = fman_muram_alloc(fman->muram,
					     fman->state->total_fअगरo_size);
	अगर (IS_ERR_VALUE(fman->fअगरo_offset)) अणु
		मुक्त_init_resources(fman);
		dev_err(fman->dev, "%s: MURAM alloc for BMI FIFO failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	cfg->fअगरo_base_addr = fman->fअगरo_offset;
	cfg->total_fअगरo_size = fman->state->total_fअगरo_size;
	cfg->total_num_of_tasks = fman->state->total_num_of_tasks;
	cfg->clk_freq = fman->state->fm_clk_freq;

	/* Init BMI Registers */
	bmi_init(fman->bmi_regs, fman->cfg);

	/* Init QMI Registers */
	qmi_init(fman->qmi_regs, fman->cfg);

	/* Init HW Parser */
	hwp_init(fman->hwp_regs);

	/* Init KeyGen */
	fman->keygen = keygen_init(fman->kg_regs);
	अगर (!fman->keygen)
		वापस -EINVAL;

	err = enable(fman, cfg);
	अगर (err != 0)
		वापस err;

	enable_समय_stamp(fman);

	kमुक्त(fman->cfg);
	fman->cfg = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक fman_set_exception(काष्ठा fman *fman,
			      क्रमागत fman_exceptions exception, bool enable)
अणु
	u32 bit_mask = 0;

	अगर (!is_init_करोne(fman->cfg))
		वापस -EINVAL;

	bit_mask = get_exception_flag(exception);
	अगर (bit_mask) अणु
		अगर (enable)
			fman->state->exceptions |= bit_mask;
		अन्यथा
			fman->state->exceptions &= ~bit_mask;
	पूर्ण अन्यथा अणु
		dev_err(fman->dev, "%s: Undefined exception (%d)\n",
			__func__, exception);
		वापस -EINVAL;
	पूर्ण

	वापस set_exception(fman, exception, enable);
पूर्ण

/**
 * fman_रेजिस्टर_पूर्णांकr
 * @fman:	A Poपूर्णांकer to FMan device
 * @module:	Calling module
 * @mod_id:	Module id (अगर more than 1 exists, '0' अगर not)
 * @पूर्णांकr_type:	Interrupt type (error/normal) selection.
 * @isr_cb:	The पूर्णांकerrupt service routine.
 * @src_arg:	Argument to be passed to isr_cb.
 *
 * Used to रेजिस्टर an event handler to be processed by FMan
 *
 * Return: 0 on success; Error code otherwise.
 */
व्योम fman_रेजिस्टर_पूर्णांकr(काष्ठा fman *fman, क्रमागत fman_event_modules module,
			u8 mod_id, क्रमागत fman_पूर्णांकr_type पूर्णांकr_type,
			व्योम (*isr_cb)(व्योम *src_arg), व्योम *src_arg)
अणु
	पूर्णांक event = 0;

	event = get_module_event(module, mod_id, पूर्णांकr_type);
	WARN_ON(event >= FMAN_EV_CNT);

	/* रेजिस्टर in local FM काष्ठाure */
	fman->पूर्णांकr_mng[event].isr_cb = isr_cb;
	fman->पूर्णांकr_mng[event].src_handle = src_arg;
पूर्ण
EXPORT_SYMBOL(fman_रेजिस्टर_पूर्णांकr);

/**
 * fman_unरेजिस्टर_पूर्णांकr
 * @fman:	A Poपूर्णांकer to FMan device
 * @module:	Calling module
 * @mod_id:	Module id (अगर more than 1 exists, '0' अगर not)
 * @पूर्णांकr_type:	Interrupt type (error/normal) selection.
 *
 * Used to unरेजिस्टर an event handler to be processed by FMan
 *
 * Return: 0 on success; Error code otherwise.
 */
व्योम fman_unरेजिस्टर_पूर्णांकr(काष्ठा fman *fman, क्रमागत fman_event_modules module,
			  u8 mod_id, क्रमागत fman_पूर्णांकr_type पूर्णांकr_type)
अणु
	पूर्णांक event = 0;

	event = get_module_event(module, mod_id, पूर्णांकr_type);
	WARN_ON(event >= FMAN_EV_CNT);

	fman->पूर्णांकr_mng[event].isr_cb = शून्य;
	fman->पूर्णांकr_mng[event].src_handle = शून्य;
पूर्ण
EXPORT_SYMBOL(fman_unरेजिस्टर_पूर्णांकr);

/**
 * fman_set_port_params
 * @fman:		A Poपूर्णांकer to FMan device
 * @port_params:	Port parameters
 *
 * Used by FMan Port to pass parameters to the FMan
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_set_port_params(काष्ठा fman *fman,
			 काष्ठा fman_port_init_params *port_params)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	u8 port_id = port_params->port_id, mac_id;

	spin_lock_irqsave(&fman->spinlock, flags);

	err = set_num_of_tasks(fman, port_params->port_id,
			       &port_params->num_of_tasks,
			       &port_params->num_of_extra_tasks);
	अगर (err)
		जाओ वापस_err;

	/* TX Ports */
	अगर (port_params->port_type != FMAN_PORT_TYPE_RX) अणु
		u32 enq_th, deq_th, reg;

		/* update qmi ENQ/DEQ threshold */
		fman->state->accumulated_num_of_deq_tnums +=
			port_params->deq_pipeline_depth;
		enq_th = (ioपढ़ो32be(&fman->qmi_regs->fmqm_gc) &
			  QMI_CFG_ENQ_MASK) >> QMI_CFG_ENQ_SHIFT;
		/* अगर enq_th is too big, we reduce it to the max value
		 * that is still 0
		 */
		अगर (enq_th >= (fman->state->qmi_max_num_of_tnums -
		    fman->state->accumulated_num_of_deq_tnums)) अणु
			enq_th =
			fman->state->qmi_max_num_of_tnums -
			fman->state->accumulated_num_of_deq_tnums - 1;

			reg = ioपढ़ो32be(&fman->qmi_regs->fmqm_gc);
			reg &= ~QMI_CFG_ENQ_MASK;
			reg |= (enq_th << QMI_CFG_ENQ_SHIFT);
			ioग_लिखो32be(reg, &fman->qmi_regs->fmqm_gc);
		पूर्ण

		deq_th = ioपढ़ो32be(&fman->qmi_regs->fmqm_gc) &
				    QMI_CFG_DEQ_MASK;
		/* अगर deq_th is too small, we enlarge it to the min
		 * value that is still 0.
		 * depTh may not be larger than 63
		 * (fman->state->qmi_max_num_of_tnums-1).
		 */
		अगर ((deq_th <= fman->state->accumulated_num_of_deq_tnums) &&
		    (deq_th < fman->state->qmi_max_num_of_tnums - 1)) अणु
			deq_th = fman->state->accumulated_num_of_deq_tnums + 1;
			reg = ioपढ़ो32be(&fman->qmi_regs->fmqm_gc);
			reg &= ~QMI_CFG_DEQ_MASK;
			reg |= deq_th;
			ioग_लिखो32be(reg, &fman->qmi_regs->fmqm_gc);
		पूर्ण
	पूर्ण

	err = set_size_of_fअगरo(fman, port_params->port_id,
			       &port_params->size_of_fअगरo,
			       &port_params->extra_size_of_fअगरo);
	अगर (err)
		जाओ वापस_err;

	err = set_num_of_खोलो_dmas(fman, port_params->port_id,
				   &port_params->num_of_खोलो_dmas,
				   &port_params->num_of_extra_खोलो_dmas);
	अगर (err)
		जाओ वापस_err;

	set_port_liodn(fman, port_id, fman->liodn_base[port_id],
		       fman->liodn_offset[port_id]);

	अगर (fman->state->rev_info.major < 6)
		set_port_order_restoration(fman->fpm_regs, port_id);

	mac_id = hw_port_id_to_sw_port_id(fman->state->rev_info.major, port_id);

	अगर (port_params->max_frame_length >= fman->state->mac_mfl[mac_id]) अणु
		fman->state->port_mfl[mac_id] = port_params->max_frame_length;
	पूर्ण अन्यथा अणु
		dev_warn(fman->dev, "%s: Port (%d) max_frame_length is smaller than MAC (%d) current MTU\n",
			 __func__, port_id, mac_id);
		err = -EINVAL;
		जाओ वापस_err;
	पूर्ण

	spin_unlock_irqrestore(&fman->spinlock, flags);

	वापस 0;

वापस_err:
	spin_unlock_irqrestore(&fman->spinlock, flags);
	वापस err;
पूर्ण
EXPORT_SYMBOL(fman_set_port_params);

/**
 * fman_reset_mac
 * @fman:	A Poपूर्णांकer to FMan device
 * @mac_id:	MAC id to be reset
 *
 * Reset a specअगरic MAC
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_reset_mac(काष्ठा fman *fman, u8 mac_id)
अणु
	काष्ठा fman_fpm_regs __iomem *fpm_rg = fman->fpm_regs;
	u32 msk, समयout = 100;

	अगर (fman->state->rev_info.major >= 6) अणु
		dev_err(fman->dev, "%s: FMan MAC reset no available for FMan V3!\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	/* Get the relevant bit mask */
	चयन (mac_id) अणु
	हाल 0:
		msk = FPM_RSTC_MAC0_RESET;
		अवरोध;
	हाल 1:
		msk = FPM_RSTC_MAC1_RESET;
		अवरोध;
	हाल 2:
		msk = FPM_RSTC_MAC2_RESET;
		अवरोध;
	हाल 3:
		msk = FPM_RSTC_MAC3_RESET;
		अवरोध;
	हाल 4:
		msk = FPM_RSTC_MAC4_RESET;
		अवरोध;
	हाल 5:
		msk = FPM_RSTC_MAC5_RESET;
		अवरोध;
	हाल 6:
		msk = FPM_RSTC_MAC6_RESET;
		अवरोध;
	हाल 7:
		msk = FPM_RSTC_MAC7_RESET;
		अवरोध;
	हाल 8:
		msk = FPM_RSTC_MAC8_RESET;
		अवरोध;
	हाल 9:
		msk = FPM_RSTC_MAC9_RESET;
		अवरोध;
	शेष:
		dev_warn(fman->dev, "%s: Illegal MAC Id [%d]\n",
			 __func__, mac_id);
		वापस -EINVAL;
	पूर्ण

	/* reset */
	ioग_लिखो32be(msk, &fpm_rg->fm_rstc);
	जबतक ((ioपढ़ो32be(&fpm_rg->fm_rstc) & msk) && --समयout)
		udelay(10);

	अगर (!समयout)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_reset_mac);

/**
 * fman_set_mac_max_frame
 * @fman:	A Poपूर्णांकer to FMan device
 * @mac_id:	MAC id
 * @mfl:	Maximum frame length
 *
 * Set maximum frame length of specअगरic MAC in FMan driver
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_set_mac_max_frame(काष्ठा fman *fman, u8 mac_id, u16 mfl)
अणु
	/* अगर port is alपढ़ोy initialized, check that MaxFrameLength is smaller
	 * or equal to the port's max
	 */
	अगर ((!fman->state->port_mfl[mac_id]) ||
	    (mfl <= fman->state->port_mfl[mac_id])) अणु
		fman->state->mac_mfl[mac_id] = mfl;
	पूर्ण अन्यथा अणु
		dev_warn(fman->dev, "%s: MAC max_frame_length is larger than Port max_frame_length\n",
			 __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_set_mac_max_frame);

/**
 * fman_get_घड़ी_freq
 * @fman:	A Poपूर्णांकer to FMan device
 *
 * Get FMan घड़ी frequency
 *
 * Return: FMan घड़ी frequency
 */
u16 fman_get_घड़ी_freq(काष्ठा fman *fman)
अणु
	वापस fman->state->fm_clk_freq;
पूर्ण

/**
 * fman_get_bmi_max_fअगरo_size
 * @fman:	A Poपूर्णांकer to FMan device
 *
 * Get FMan maximum FIFO size
 *
 * Return: FMan Maximum FIFO size
 */
u32 fman_get_bmi_max_fअगरo_size(काष्ठा fman *fman)
अणु
	वापस fman->state->bmi_max_fअगरo_size;
पूर्ण
EXPORT_SYMBOL(fman_get_bmi_max_fअगरo_size);

/**
 * fman_get_revision
 * @fman:		- Poपूर्णांकer to the FMan module
 * @rev_info:		- A काष्ठाure of revision inक्रमmation parameters.
 *
 * Returns the FM revision
 *
 * Allowed only following fman_init().
 *
 * Return: 0 on success; Error code otherwise.
 */
व्योम fman_get_revision(काष्ठा fman *fman, काष्ठा fman_rev_info *rev_info)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&fman->fpm_regs->fm_ip_rev_1);
	rev_info->major = (u8)((पंचांगp & FPM_REV1_MAJOR_MASK) >>
				FPM_REV1_MAJOR_SHIFT);
	rev_info->minor = पंचांगp & FPM_REV1_MINOR_MASK;
पूर्ण
EXPORT_SYMBOL(fman_get_revision);

/**
 * fman_get_qman_channel_id
 * @fman:	A Poपूर्णांकer to FMan device
 * @port_id:	Port id
 *
 * Get QMan channel ID associated to the Port id
 *
 * Return: QMan channel ID
 */
u32 fman_get_qman_channel_id(काष्ठा fman *fman, u32 port_id)
अणु
	पूर्णांक i;

	अगर (fman->state->rev_info.major >= 6) अणु
		अटल स्थिर u32 port_ids[] = अणु
			0x30, 0x31, 0x28, 0x29, 0x2a, 0x2b,
			0x2c, 0x2d, 0x2, 0x3, 0x4, 0x5, 0x7, 0x7
		पूर्ण;

		क्रम (i = 0; i < fman->state->num_of_qman_channels; i++) अणु
			अगर (port_ids[i] == port_id)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 port_ids[] = अणु
			0x30, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x1,
			0x2, 0x3, 0x4, 0x5, 0x7, 0x7
		पूर्ण;

		क्रम (i = 0; i < fman->state->num_of_qman_channels; i++) अणु
			अगर (port_ids[i] == port_id)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == fman->state->num_of_qman_channels)
		वापस 0;

	वापस fman->state->qman_channel_base + i;
पूर्ण
EXPORT_SYMBOL(fman_get_qman_channel_id);

/**
 * fman_get_mem_region
 * @fman:	A Poपूर्णांकer to FMan device
 *
 * Get FMan memory region
 *
 * Return: A काष्ठाure with FMan memory region inक्रमmation
 */
काष्ठा resource *fman_get_mem_region(काष्ठा fman *fman)
अणु
	वापस fman->state->res;
पूर्ण
EXPORT_SYMBOL(fman_get_mem_region);

/* Bootargs defines */
/* Extra headroom क्रम RX buffers - Default, min and max */
#घोषणा FSL_FM_RX_EXTRA_HEADROOM	64
#घोषणा FSL_FM_RX_EXTRA_HEADROOM_MIN	16
#घोषणा FSL_FM_RX_EXTRA_HEADROOM_MAX	384

/* Maximum frame length */
#घोषणा FSL_FM_MAX_FRAME_SIZE			1522
#घोषणा FSL_FM_MAX_POSSIBLE_FRAME_SIZE		9600
#घोषणा FSL_FM_MIN_POSSIBLE_FRAME_SIZE		64

/* Extra headroom क्रम Rx buffers.
 * FMan is inकाष्ठाed to allocate, on the Rx path, this amount of
 * space at the beginning of a data buffer, beside the DPA निजी
 * data area and the IC fields.
 * Does not impact Tx buffer layout.
 * Configurable from bootargs. 64 by शेष, it's needed on
 * particular क्रमwarding scenarios that add extra headers to the
 * क्रमwarded frame.
 */
अटल पूर्णांक fsl_fm_rx_extra_headroom = FSL_FM_RX_EXTRA_HEADROOM;
module_param(fsl_fm_rx_extra_headroom, पूर्णांक, 0);
MODULE_PARM_DESC(fsl_fm_rx_extra_headroom, "Extra headroom for Rx buffers");

/* Max frame size, across all पूर्णांकerfaces.
 * Configurable from bootargs, to aव्योम allocating oversized (socket)
 * buffers when not using jumbo frames.
 * Must be large enough to accommodate the network MTU, but small enough
 * to aव्योम wasting skb memory.
 */
अटल पूर्णांक fsl_fm_max_frm = FSL_FM_MAX_FRAME_SIZE;
module_param(fsl_fm_max_frm, पूर्णांक, 0);
MODULE_PARM_DESC(fsl_fm_max_frm, "Maximum frame size, across all interfaces");

/**
 * fman_get_max_frm
 *
 * Return: Max frame length configured in the FM driver
 */
u16 fman_get_max_frm(व्योम)
अणु
	अटल bool fm_check_mfl;

	अगर (!fm_check_mfl) अणु
		अगर (fsl_fm_max_frm > FSL_FM_MAX_POSSIBLE_FRAME_SIZE ||
		    fsl_fm_max_frm < FSL_FM_MIN_POSSIBLE_FRAME_SIZE) अणु
			pr_warn("Invalid fsl_fm_max_frm value (%d) in bootargs, valid range is %d-%d. Falling back to the default (%d)\n",
				fsl_fm_max_frm,
				FSL_FM_MIN_POSSIBLE_FRAME_SIZE,
				FSL_FM_MAX_POSSIBLE_FRAME_SIZE,
				FSL_FM_MAX_FRAME_SIZE);
			fsl_fm_max_frm = FSL_FM_MAX_FRAME_SIZE;
		पूर्ण
		fm_check_mfl = true;
	पूर्ण

	वापस fsl_fm_max_frm;
पूर्ण
EXPORT_SYMBOL(fman_get_max_frm);

/**
 * fman_get_rx_extra_headroom
 *
 * Return: Extra headroom size configured in the FM driver
 */
पूर्णांक fman_get_rx_extra_headroom(व्योम)
अणु
	अटल bool fm_check_rx_extra_headroom;

	अगर (!fm_check_rx_extra_headroom) अणु
		अगर (fsl_fm_rx_extra_headroom > FSL_FM_RX_EXTRA_HEADROOM_MAX ||
		    fsl_fm_rx_extra_headroom < FSL_FM_RX_EXTRA_HEADROOM_MIN) अणु
			pr_warn("Invalid fsl_fm_rx_extra_headroom value (%d) in bootargs, valid range is %d-%d. Falling back to the default (%d)\n",
				fsl_fm_rx_extra_headroom,
				FSL_FM_RX_EXTRA_HEADROOM_MIN,
				FSL_FM_RX_EXTRA_HEADROOM_MAX,
				FSL_FM_RX_EXTRA_HEADROOM);
			fsl_fm_rx_extra_headroom = FSL_FM_RX_EXTRA_HEADROOM;
		पूर्ण

		fm_check_rx_extra_headroom = true;
		fsl_fm_rx_extra_headroom = ALIGN(fsl_fm_rx_extra_headroom, 16);
	पूर्ण

	वापस fsl_fm_rx_extra_headroom;
पूर्ण
EXPORT_SYMBOL(fman_get_rx_extra_headroom);

/**
 * fman_bind
 * @fm_dev:	FMan OF device poपूर्णांकer
 *
 * Bind to a specअगरic FMan device.
 *
 * Allowed only after the port was created.
 *
 * Return: A poपूर्णांकer to the FMan device
 */
काष्ठा fman *fman_bind(काष्ठा device *fm_dev)
अणु
	वापस (काष्ठा fman *)(dev_get_drvdata(get_device(fm_dev)));
पूर्ण
EXPORT_SYMBOL(fman_bind);

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
bool fman_has_errata_a050385(व्योम)
अणु
	वापस fman_has_err_a050385;
पूर्ण
EXPORT_SYMBOL(fman_has_errata_a050385);
#पूर्ण_अगर

अटल irqवापस_t fman_err_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा fman *fman = (काष्ठा fman *)handle;
	u32 pending;
	काष्ठा fman_fpm_regs __iomem *fpm_rg;
	irqवापस_t single_ret, ret = IRQ_NONE;

	अगर (!is_init_करोne(fman->cfg))
		वापस IRQ_NONE;

	fpm_rg = fman->fpm_regs;

	/* error पूर्णांकerrupts */
	pending = ioपढ़ो32be(&fpm_rg->fm_epi);
	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & ERR_INTR_EN_BMI) अणु
		single_ret = bmi_err_event(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_QMI) अणु
		single_ret = qmi_err_event(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_FPM) अणु
		single_ret = fpm_err_event(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_DMA) अणु
		single_ret = dma_err_event(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MURAM) अणु
		single_ret = muram_err_पूर्णांकr(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	/* MAC error पूर्णांकerrupts */
	अगर (pending & ERR_INTR_EN_MAC0) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 0);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC1) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 1);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC2) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 2);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC3) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 3);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC4) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 4);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC5) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 5);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC6) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 6);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC7) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 7);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC8) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 8);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & ERR_INTR_EN_MAC9) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_ERR_MAC0 + 9);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t fman_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा fman *fman = (काष्ठा fman *)handle;
	u32 pending;
	काष्ठा fman_fpm_regs __iomem *fpm_rg;
	irqवापस_t single_ret, ret = IRQ_NONE;

	अगर (!is_init_करोne(fman->cfg))
		वापस IRQ_NONE;

	fpm_rg = fman->fpm_regs;

	/* normal पूर्णांकerrupts */
	pending = ioपढ़ो32be(&fpm_rg->fm_npi);
	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & INTR_EN_QMI) अणु
		single_ret = qmi_event(fman);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	/* MAC पूर्णांकerrupts */
	अगर (pending & INTR_EN_MAC0) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 0);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC1) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 1);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC2) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 2);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC3) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 3);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC4) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 4);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC5) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 5);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC6) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 6);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC7) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 7);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC8) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 8);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण
	अगर (pending & INTR_EN_MAC9) अणु
		single_ret = call_mac_isr(fman, FMAN_EV_MAC0 + 9);
		अगर (single_ret == IRQ_HANDLED)
			ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id fman_muram_match[] = अणु
	अणु
		.compatible = "fsl,fman-muram"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fman_muram_match);

अटल काष्ठा fman *पढ़ो_dts_node(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा fman *fman;
	काष्ठा device_node *fm_node, *muram_node;
	काष्ठा resource *res;
	u32 val, range[2];
	पूर्णांक err, irq;
	काष्ठा clk *clk;
	u32 clk_rate;
	phys_addr_t phys_base_addr;
	resource_माप_प्रकार mem_size;

	fman = kzalloc(माप(*fman), GFP_KERNEL);
	अगर (!fman)
		वापस शून्य;

	fm_node = of_node_get(of_dev->dev.of_node);

	err = of_property_पढ़ो_u32(fm_node, "cell-index", &val);
	अगर (err) अणु
		dev_err(&of_dev->dev, "%s: failed to read cell-index for %pOF\n",
			__func__, fm_node);
		जाओ fman_node_put;
	पूर्ण
	fman->dts_params.id = (u8)val;

	/* Get the FM पूर्णांकerrupt */
	res = platक्रमm_get_resource(of_dev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&of_dev->dev, "%s: Can't get FMan IRQ resource\n",
			__func__);
		जाओ fman_node_put;
	पूर्ण
	irq = res->start;

	/* Get the FM error पूर्णांकerrupt */
	res = platक्रमm_get_resource(of_dev, IORESOURCE_IRQ, 1);
	अगर (!res) अणु
		dev_err(&of_dev->dev, "%s: Can't get FMan Error IRQ resource\n",
			__func__);
		जाओ fman_node_put;
	पूर्ण
	fman->dts_params.err_irq = res->start;

	/* Get the FM address */
	res = platक्रमm_get_resource(of_dev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&of_dev->dev, "%s: Can't get FMan memory resource\n",
			__func__);
		जाओ fman_node_put;
	पूर्ण

	phys_base_addr = res->start;
	mem_size = resource_size(res);

	clk = of_clk_get(fm_node, 0);
	अगर (IS_ERR(clk)) अणु
		dev_err(&of_dev->dev, "%s: Failed to get FM%d clock structure\n",
			__func__, fman->dts_params.id);
		जाओ fman_node_put;
	पूर्ण

	clk_rate = clk_get_rate(clk);
	अगर (!clk_rate) अणु
		dev_err(&of_dev->dev, "%s: Failed to determine FM%d clock rate\n",
			__func__, fman->dts_params.id);
		जाओ fman_node_put;
	पूर्ण
	/* Rounding to MHz */
	fman->dts_params.clk_freq = DIV_ROUND_UP(clk_rate, 1000000);

	err = of_property_पढ़ो_u32_array(fm_node, "fsl,qman-channel-range",
					 &range[0], 2);
	अगर (err) अणु
		dev_err(&of_dev->dev, "%s: failed to read fsl,qman-channel-range for %pOF\n",
			__func__, fm_node);
		जाओ fman_node_put;
	पूर्ण
	fman->dts_params.qman_channel_base = range[0];
	fman->dts_params.num_of_qman_channels = range[1];

	/* Get the MURAM base address and size */
	muram_node = of_find_matching_node(fm_node, fman_muram_match);
	अगर (!muram_node) अणु
		dev_err(&of_dev->dev, "%s: could not find MURAM node\n",
			__func__);
		जाओ fman_मुक्त;
	पूर्ण

	err = of_address_to_resource(muram_node, 0,
				     &fman->dts_params.muram_res);
	अगर (err) अणु
		of_node_put(muram_node);
		dev_err(&of_dev->dev, "%s: of_address_to_resource() = %d\n",
			__func__, err);
		जाओ fman_मुक्त;
	पूर्ण

	of_node_put(muram_node);

	err = devm_request_irq(&of_dev->dev, irq, fman_irq, IRQF_SHARED,
			       "fman", fman);
	अगर (err < 0) अणु
		dev_err(&of_dev->dev, "%s: irq %d allocation failed (error = %d)\n",
			__func__, irq, err);
		जाओ fman_मुक्त;
	पूर्ण

	अगर (fman->dts_params.err_irq != 0) अणु
		err = devm_request_irq(&of_dev->dev, fman->dts_params.err_irq,
				       fman_err_irq, IRQF_SHARED,
				       "fman-err", fman);
		अगर (err < 0) अणु
			dev_err(&of_dev->dev, "%s: irq %d allocation failed (error = %d)\n",
				__func__, fman->dts_params.err_irq, err);
			जाओ fman_मुक्त;
		पूर्ण
	पूर्ण

	fman->dts_params.res =
		devm_request_mem_region(&of_dev->dev, phys_base_addr,
					mem_size, "fman");
	अगर (!fman->dts_params.res) अणु
		dev_err(&of_dev->dev, "%s: request_mem_region() failed\n",
			__func__);
		जाओ fman_मुक्त;
	पूर्ण

	fman->dts_params.base_addr =
		devm_ioremap(&of_dev->dev, phys_base_addr, mem_size);
	अगर (!fman->dts_params.base_addr) अणु
		dev_err(&of_dev->dev, "%s: devm_ioremap() failed\n", __func__);
		जाओ fman_मुक्त;
	पूर्ण

	fman->dev = &of_dev->dev;

	err = of_platक्रमm_populate(fm_node, शून्य, शून्य, &of_dev->dev);
	अगर (err) अणु
		dev_err(&of_dev->dev, "%s: of_platform_populate() failed\n",
			__func__);
		जाओ fman_मुक्त;
	पूर्ण

#अगर_घोषित CONFIG_DPAA_ERRATUM_A050385
	fman_has_err_a050385 =
		of_property_पढ़ो_bool(fm_node, "fsl,erratum-a050385");
#पूर्ण_अगर

	वापस fman;

fman_node_put:
	of_node_put(fm_node);
fman_मुक्त:
	kमुक्त(fman);
	वापस शून्य;
पूर्ण

अटल पूर्णांक fman_probe(काष्ठा platक्रमm_device *of_dev)
अणु
	काष्ठा fman *fman;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = &of_dev->dev;

	fman = पढ़ो_dts_node(of_dev);
	अगर (!fman)
		वापस -EIO;

	err = fman_config(fman);
	अगर (err) अणु
		dev_err(dev, "%s: FMan config failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (fman_init(fman) != 0) अणु
		dev_err(dev, "%s: FMan init failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (fman->dts_params.err_irq == 0) अणु
		fman_set_exception(fman, FMAN_EX_DMA_BUS_ERROR, false);
		fman_set_exception(fman, FMAN_EX_DMA_READ_ECC, false);
		fman_set_exception(fman, FMAN_EX_DMA_SYSTEM_WRITE_ECC, false);
		fman_set_exception(fman, FMAN_EX_DMA_FM_WRITE_ECC, false);
		fman_set_exception(fman, FMAN_EX_DMA_SINGLE_PORT_ECC, false);
		fman_set_exception(fman, FMAN_EX_FPM_STALL_ON_TASKS, false);
		fman_set_exception(fman, FMAN_EX_FPM_SINGLE_ECC, false);
		fman_set_exception(fman, FMAN_EX_FPM_DOUBLE_ECC, false);
		fman_set_exception(fman, FMAN_EX_QMI_SINGLE_ECC, false);
		fman_set_exception(fman, FMAN_EX_QMI_DOUBLE_ECC, false);
		fman_set_exception(fman,
				   FMAN_EX_QMI_DEQ_FROM_UNKNOWN_PORTID, false);
		fman_set_exception(fman, FMAN_EX_BMI_LIST_RAM_ECC, false);
		fman_set_exception(fman, FMAN_EX_BMI_STORAGE_PROखाता_ECC,
				   false);
		fman_set_exception(fman, FMAN_EX_BMI_STATISTICS_RAM_ECC, false);
		fman_set_exception(fman, FMAN_EX_BMI_DISPATCH_RAM_ECC, false);
	पूर्ण

	dev_set_drvdata(dev, fman);

	dev_dbg(dev, "FMan%d probed\n", fman->dts_params.id);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fman_match[] = अणु
	अणु
		.compatible = "fsl,fman"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, fman_match);

अटल काष्ठा platक्रमm_driver fman_driver = अणु
	.driver = अणु
		.name = "fsl-fman",
		.of_match_table = fman_match,
	पूर्ण,
	.probe = fman_probe,
पूर्ण;

अटल पूर्णांक __init fman_load(व्योम)
अणु
	पूर्णांक err;

	pr_debug("FSL DPAA FMan driver\n");

	err = platक्रमm_driver_रेजिस्टर(&fman_driver);
	अगर (err < 0)
		pr_err("Error, platform_driver_register() = %d\n", err);

	वापस err;
पूर्ण
module_init(fman_load);

अटल व्योम __निकास fman_unload(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fman_driver);
पूर्ण
module_निकास(fman_unload);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Freescale DPAA Frame Manager driver");
