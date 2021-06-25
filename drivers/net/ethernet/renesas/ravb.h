<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Renesas Ethernet AVB device driver
 *
 * Copyright (C) 2014-2015 Renesas Electronics Corporation
 * Copyright (C) 2015 Renesas Solutions Corp.
 * Copyright (C) 2015-2016 Cogent Embedded, Inc. <source@cogentembedded.com>
 *
 * Based on the SuperH Ethernet driver
 */

#अगर_अघोषित __RAVB_H__
#घोषणा __RAVB_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#घोषणा BE_TX_RING_SIZE	64	/* TX ring size क्रम Best Efक्रमt */
#घोषणा BE_RX_RING_SIZE	1024	/* RX ring size क्रम Best Efक्रमt */
#घोषणा NC_TX_RING_SIZE	64	/* TX ring size क्रम Network Control */
#घोषणा NC_RX_RING_SIZE	64	/* RX ring size क्रम Network Control */
#घोषणा BE_TX_RING_MIN	64
#घोषणा BE_RX_RING_MIN	64
#घोषणा BE_TX_RING_MAX	1024
#घोषणा BE_RX_RING_MAX	2048

#घोषणा PKT_BUF_SZ	1538

/* Driver's parameters */
#घोषणा RAVB_ALIGN	128

/* Hardware समय stamp */
#घोषणा RAVB_TXTSTAMP_VALID	0x00000001	/* TX बारtamp valid */
#घोषणा RAVB_TXTSTAMP_ENABLED	0x00000010	/* Enable TX बारtamping */

#घोषणा RAVB_RXTSTAMP_VALID	0x00000001	/* RX बारtamp valid */
#घोषणा RAVB_RXTSTAMP_TYPE	0x00000006	/* RX type mask */
#घोषणा RAVB_RXTSTAMP_TYPE_V2_L2_EVENT 0x00000002
#घोषणा RAVB_RXTSTAMP_TYPE_ALL	0x00000006
#घोषणा RAVB_RXTSTAMP_ENABLED	0x00000010	/* Enable RX बारtamping */

क्रमागत ravb_reg अणु
	/* AVB-DMAC रेजिस्टरs */
	CCC	= 0x0000,
	DBAT	= 0x0004,
	DLR	= 0x0008,
	CSR	= 0x000C,
	CDAR0	= 0x0010,
	CDAR1	= 0x0014,
	CDAR2	= 0x0018,
	CDAR3	= 0x001C,
	CDAR4	= 0x0020,
	CDAR5	= 0x0024,
	CDAR6	= 0x0028,
	CDAR7	= 0x002C,
	CDAR8	= 0x0030,
	CDAR9	= 0x0034,
	CDAR10	= 0x0038,
	CDAR11	= 0x003C,
	CDAR12	= 0x0040,
	CDAR13	= 0x0044,
	CDAR14	= 0x0048,
	CDAR15	= 0x004C,
	CDAR16	= 0x0050,
	CDAR17	= 0x0054,
	CDAR18	= 0x0058,
	CDAR19	= 0x005C,
	CDAR20	= 0x0060,
	CDAR21	= 0x0064,
	ESR	= 0x0088,
	APSR	= 0x008C,	/* R-Car Gen3 only */
	RCR	= 0x0090,
	RQC0	= 0x0094,
	RQC1	= 0x0098,
	RQC2	= 0x009C,
	RQC3	= 0x00A0,
	RQC4	= 0x00A4,
	RPC	= 0x00B0,
	UFCW	= 0x00BC,
	UFCS	= 0x00C0,
	UFCV0	= 0x00C4,
	UFCV1	= 0x00C8,
	UFCV2	= 0x00CC,
	UFCV3	= 0x00D0,
	UFCV4	= 0x00D4,
	UFCD0	= 0x00E0,
	UFCD1	= 0x00E4,
	UFCD2	= 0x00E8,
	UFCD3	= 0x00EC,
	UFCD4	= 0x00F0,
	SFO	= 0x00FC,
	SFP0	= 0x0100,
	SFP1	= 0x0104,
	SFP2	= 0x0108,
	SFP3	= 0x010C,
	SFP4	= 0x0110,
	SFP5	= 0x0114,
	SFP6	= 0x0118,
	SFP7	= 0x011C,
	SFP8	= 0x0120,
	SFP9	= 0x0124,
	SFP10	= 0x0128,
	SFP11	= 0x012C,
	SFP12	= 0x0130,
	SFP13	= 0x0134,
	SFP14	= 0x0138,
	SFP15	= 0x013C,
	SFP16	= 0x0140,
	SFP17	= 0x0144,
	SFP18	= 0x0148,
	SFP19	= 0x014C,
	SFP20	= 0x0150,
	SFP21	= 0x0154,
	SFP22	= 0x0158,
	SFP23	= 0x015C,
	SFP24	= 0x0160,
	SFP25	= 0x0164,
	SFP26	= 0x0168,
	SFP27	= 0x016C,
	SFP28	= 0x0170,
	SFP29	= 0x0174,
	SFP30	= 0x0178,
	SFP31	= 0x017C,
	SFM0	= 0x01C0,
	SFM1	= 0x01C4,
	TGC	= 0x0300,
	TCCR	= 0x0304,
	TSR	= 0x0308,
	TFA0	= 0x0310,
	TFA1	= 0x0314,
	TFA2	= 0x0318,
	CIVR0	= 0x0320,
	CIVR1	= 0x0324,
	CDVR0	= 0x0328,
	CDVR1	= 0x032C,
	CUL0	= 0x0330,
	CUL1	= 0x0334,
	CLL0	= 0x0338,
	CLL1	= 0x033C,
	DIC	= 0x0350,
	DIS	= 0x0354,
	EIC	= 0x0358,
	EIS	= 0x035C,
	RIC0	= 0x0360,
	RIS0	= 0x0364,
	RIC1	= 0x0368,
	RIS1	= 0x036C,
	RIC2	= 0x0370,
	RIS2	= 0x0374,
	TIC	= 0x0378,
	TIS	= 0x037C,
	ISS	= 0x0380,
	CIE	= 0x0384,	/* R-Car Gen3 only */
	GCCR	= 0x0390,
	GMTT	= 0x0394,
	GPTC	= 0x0398,
	GTI	= 0x039C,
	GTO0	= 0x03A0,
	GTO1	= 0x03A4,
	GTO2	= 0x03A8,
	GIC	= 0x03AC,
	GIS	= 0x03B0,
	GCPT	= 0x03B4,	/* Documented क्रम R-Car Gen3 only */
	GCT0	= 0x03B8,
	GCT1	= 0x03BC,
	GCT2	= 0x03C0,
	GIE	= 0x03CC,	/* R-Car Gen3 only */
	GID	= 0x03D0,	/* R-Car Gen3 only */
	DIL	= 0x0440,	/* R-Car Gen3 only */
	RIE0	= 0x0460,	/* R-Car Gen3 only */
	RID0	= 0x0464,	/* R-Car Gen3 only */
	RIE2	= 0x0470,	/* R-Car Gen3 only */
	RID2	= 0x0474,	/* R-Car Gen3 only */
	TIE	= 0x0478,	/* R-Car Gen3 only */
	TID	= 0x047c,	/* R-Car Gen3 only */

	/* E-MAC रेजिस्टरs */
	ECMR	= 0x0500,
	RFLR	= 0x0508,
	ECSR	= 0x0510,
	ECSIPR	= 0x0518,
	PIR	= 0x0520,
	PSR	= 0x0528,
	PIPR	= 0x052c,
	MPR	= 0x0558,
	PFTCR	= 0x055c,
	PFRCR	= 0x0560,
	GECMR	= 0x05b0,
	MAHR	= 0x05c0,
	MALR	= 0x05c8,
	TROCR	= 0x0700,	/* R-Car Gen3 only */
	CEFCR	= 0x0740,
	FRECR	= 0x0748,
	TSFRCR	= 0x0750,
	TLFRCR	= 0x0758,
	RFCR	= 0x0760,
	MAFCR	= 0x0778,
पूर्ण;


/* Register bits of the Ethernet AVB */
/* CCC */
क्रमागत CCC_BIT अणु
	CCC_OPC		= 0x00000003,
	CCC_OPC_RESET	= 0x00000000,
	CCC_OPC_CONFIG	= 0x00000001,
	CCC_OPC_OPERATION = 0x00000002,
	CCC_GAC		= 0x00000080,
	CCC_DTSR	= 0x00000100,
	CCC_CSEL	= 0x00030000,
	CCC_CSEL_HPB	= 0x00010000,
	CCC_CSEL_ETH_TX	= 0x00020000,
	CCC_CSEL_GMII_REF = 0x00030000,
	CCC_LBME	= 0x01000000,
पूर्ण;

/* CSR */
क्रमागत CSR_BIT अणु
	CSR_OPS		= 0x0000000F,
	CSR_OPS_RESET	= 0x00000001,
	CSR_OPS_CONFIG	= 0x00000002,
	CSR_OPS_OPERATION = 0x00000004,
	CSR_OPS_STANDBY	= 0x00000008,	/* Documented क्रम R-Car Gen3 only */
	CSR_DTS		= 0x00000100,
	CSR_TPO0	= 0x00010000,
	CSR_TPO1	= 0x00020000,
	CSR_TPO2	= 0x00040000,
	CSR_TPO3	= 0x00080000,
	CSR_RPO		= 0x00100000,
पूर्ण;

/* ESR */
क्रमागत ESR_BIT अणु
	ESR_EQN		= 0x0000001F,
	ESR_ET		= 0x00000F00,
	ESR_EIL		= 0x00001000,
पूर्ण;

/* APSR (R-Car Gen3 only) */
क्रमागत APSR_BIT अणु
	APSR_MEMS	= 0x00000002,	/* Unकरोcumented */
	APSR_CMSW	= 0x00000010,
	APSR_RDM	= 0x00002000,
	APSR_TDM	= 0x00004000,
पूर्ण;

/* RCR */
क्रमागत RCR_BIT अणु
	RCR_EFFS	= 0x00000001,
	RCR_ENCF	= 0x00000002,
	RCR_ESF		= 0x0000000C,
	RCR_ETS0	= 0x00000010,
	RCR_ETS2	= 0x00000020,
	RCR_RFCL	= 0x1FFF0000,
पूर्ण;

/* RQC0/1/2/3/4 */
क्रमागत RQC_BIT अणु
	RQC_RSM0	= 0x00000003,
	RQC_UFCC0	= 0x00000030,
	RQC_RSM1	= 0x00000300,
	RQC_UFCC1	= 0x00003000,
	RQC_RSM2	= 0x00030000,
	RQC_UFCC2	= 0x00300000,
	RQC_RSM3	= 0x03000000,
	RQC_UFCC3	= 0x30000000,
पूर्ण;

/* RPC */
क्रमागत RPC_BIT अणु
	RPC_PCNT	= 0x00000700,
	RPC_DCNT	= 0x00FF0000,
पूर्ण;

/* UFCW */
क्रमागत UFCW_BIT अणु
	UFCW_WL0	= 0x0000003F,
	UFCW_WL1	= 0x00003F00,
	UFCW_WL2	= 0x003F0000,
	UFCW_WL3	= 0x3F000000,
पूर्ण;

/* UFCS */
क्रमागत UFCS_BIT अणु
	UFCS_SL0	= 0x0000003F,
	UFCS_SL1	= 0x00003F00,
	UFCS_SL2	= 0x003F0000,
	UFCS_SL3	= 0x3F000000,
पूर्ण;

/* UFCV0/1/2/3/4 */
क्रमागत UFCV_BIT अणु
	UFCV_CV0	= 0x0000003F,
	UFCV_CV1	= 0x00003F00,
	UFCV_CV2	= 0x003F0000,
	UFCV_CV3	= 0x3F000000,
पूर्ण;

/* UFCD0/1/2/3/4 */
क्रमागत UFCD_BIT अणु
	UFCD_DV0	= 0x0000003F,
	UFCD_DV1	= 0x00003F00,
	UFCD_DV2	= 0x003F0000,
	UFCD_DV3	= 0x3F000000,
पूर्ण;

/* SFO */
क्रमागत SFO_BIT अणु
	SFO_FBP		= 0x0000003F,
पूर्ण;

/* RTC */
क्रमागत RTC_BIT अणु
	RTC_MFL0	= 0x00000FFF,
	RTC_MFL1	= 0x0FFF0000,
पूर्ण;

/* TGC */
क्रमागत TGC_BIT अणु
	TGC_TSM0	= 0x00000001,
	TGC_TSM1	= 0x00000002,
	TGC_TSM2	= 0x00000004,
	TGC_TSM3	= 0x00000008,
	TGC_TQP		= 0x00000030,
	TGC_TQP_NONAVB	= 0x00000000,
	TGC_TQP_AVBMODE1 = 0x00000010,
	TGC_TQP_AVBMODE2 = 0x00000030,
	TGC_TBD0	= 0x00000300,
	TGC_TBD1	= 0x00003000,
	TGC_TBD2	= 0x00030000,
	TGC_TBD3	= 0x00300000,
पूर्ण;

/* TCCR */
क्रमागत TCCR_BIT अणु
	TCCR_TSRQ0	= 0x00000001,
	TCCR_TSRQ1	= 0x00000002,
	TCCR_TSRQ2	= 0x00000004,
	TCCR_TSRQ3	= 0x00000008,
	TCCR_TFEN	= 0x00000100,
	TCCR_TFR	= 0x00000200,
पूर्ण;

/* TSR */
क्रमागत TSR_BIT अणु
	TSR_CCS0	= 0x00000003,
	TSR_CCS1	= 0x0000000C,
	TSR_TFFL	= 0x00000700,
पूर्ण;

/* TFA2 */
क्रमागत TFA2_BIT अणु
	TFA2_TSV	= 0x0000FFFF,
	TFA2_TST	= 0x03FF0000,
पूर्ण;

/* DIC */
क्रमागत DIC_BIT अणु
	DIC_DPE1	= 0x00000002,
	DIC_DPE2	= 0x00000004,
	DIC_DPE3	= 0x00000008,
	DIC_DPE4	= 0x00000010,
	DIC_DPE5	= 0x00000020,
	DIC_DPE6	= 0x00000040,
	DIC_DPE7	= 0x00000080,
	DIC_DPE8	= 0x00000100,
	DIC_DPE9	= 0x00000200,
	DIC_DPE10	= 0x00000400,
	DIC_DPE11	= 0x00000800,
	DIC_DPE12	= 0x00001000,
	DIC_DPE13	= 0x00002000,
	DIC_DPE14	= 0x00004000,
	DIC_DPE15	= 0x00008000,
पूर्ण;

/* DIS */
क्रमागत DIS_BIT अणु
	DIS_DPF1	= 0x00000002,
	DIS_DPF2	= 0x00000004,
	DIS_DPF3	= 0x00000008,
	DIS_DPF4	= 0x00000010,
	DIS_DPF5	= 0x00000020,
	DIS_DPF6	= 0x00000040,
	DIS_DPF7	= 0x00000080,
	DIS_DPF8	= 0x00000100,
	DIS_DPF9	= 0x00000200,
	DIS_DPF10	= 0x00000400,
	DIS_DPF11	= 0x00000800,
	DIS_DPF12	= 0x00001000,
	DIS_DPF13	= 0x00002000,
	DIS_DPF14	= 0x00004000,
	DIS_DPF15	= 0x00008000,
पूर्ण;

/* EIC */
क्रमागत EIC_BIT अणु
	EIC_MREE	= 0x00000001,
	EIC_MTEE	= 0x00000002,
	EIC_QEE		= 0x00000004,
	EIC_SEE		= 0x00000008,
	EIC_CLLE0	= 0x00000010,
	EIC_CLLE1	= 0x00000020,
	EIC_CULE0	= 0x00000040,
	EIC_CULE1	= 0x00000080,
	EIC_TFFE	= 0x00000100,
पूर्ण;

/* EIS */
क्रमागत EIS_BIT अणु
	EIS_MREF	= 0x00000001,
	EIS_MTEF	= 0x00000002,
	EIS_QEF		= 0x00000004,
	EIS_SEF		= 0x00000008,
	EIS_CLLF0	= 0x00000010,
	EIS_CLLF1	= 0x00000020,
	EIS_CULF0	= 0x00000040,
	EIS_CULF1	= 0x00000080,
	EIS_TFFF	= 0x00000100,
	EIS_QFS		= 0x00010000,
	EIS_RESERVED	= (GENMASK(31, 17) | GENMASK(15, 11)),
पूर्ण;

/* RIC0 */
क्रमागत RIC0_BIT अणु
	RIC0_FRE0	= 0x00000001,
	RIC0_FRE1	= 0x00000002,
	RIC0_FRE2	= 0x00000004,
	RIC0_FRE3	= 0x00000008,
	RIC0_FRE4	= 0x00000010,
	RIC0_FRE5	= 0x00000020,
	RIC0_FRE6	= 0x00000040,
	RIC0_FRE7	= 0x00000080,
	RIC0_FRE8	= 0x00000100,
	RIC0_FRE9	= 0x00000200,
	RIC0_FRE10	= 0x00000400,
	RIC0_FRE11	= 0x00000800,
	RIC0_FRE12	= 0x00001000,
	RIC0_FRE13	= 0x00002000,
	RIC0_FRE14	= 0x00004000,
	RIC0_FRE15	= 0x00008000,
	RIC0_FRE16	= 0x00010000,
	RIC0_FRE17	= 0x00020000,
पूर्ण;

/* RIC0 */
क्रमागत RIS0_BIT अणु
	RIS0_FRF0	= 0x00000001,
	RIS0_FRF1	= 0x00000002,
	RIS0_FRF2	= 0x00000004,
	RIS0_FRF3	= 0x00000008,
	RIS0_FRF4	= 0x00000010,
	RIS0_FRF5	= 0x00000020,
	RIS0_FRF6	= 0x00000040,
	RIS0_FRF7	= 0x00000080,
	RIS0_FRF8	= 0x00000100,
	RIS0_FRF9	= 0x00000200,
	RIS0_FRF10	= 0x00000400,
	RIS0_FRF11	= 0x00000800,
	RIS0_FRF12	= 0x00001000,
	RIS0_FRF13	= 0x00002000,
	RIS0_FRF14	= 0x00004000,
	RIS0_FRF15	= 0x00008000,
	RIS0_FRF16	= 0x00010000,
	RIS0_FRF17	= 0x00020000,
	RIS0_RESERVED	= GENMASK(31, 18),
पूर्ण;

/* RIC1 */
क्रमागत RIC1_BIT अणु
	RIC1_RFWE	= 0x80000000,
पूर्ण;

/* RIS1 */
क्रमागत RIS1_BIT अणु
	RIS1_RFWF	= 0x80000000,
पूर्ण;

/* RIC2 */
क्रमागत RIC2_BIT अणु
	RIC2_QFE0	= 0x00000001,
	RIC2_QFE1	= 0x00000002,
	RIC2_QFE2	= 0x00000004,
	RIC2_QFE3	= 0x00000008,
	RIC2_QFE4	= 0x00000010,
	RIC2_QFE5	= 0x00000020,
	RIC2_QFE6	= 0x00000040,
	RIC2_QFE7	= 0x00000080,
	RIC2_QFE8	= 0x00000100,
	RIC2_QFE9	= 0x00000200,
	RIC2_QFE10	= 0x00000400,
	RIC2_QFE11	= 0x00000800,
	RIC2_QFE12	= 0x00001000,
	RIC2_QFE13	= 0x00002000,
	RIC2_QFE14	= 0x00004000,
	RIC2_QFE15	= 0x00008000,
	RIC2_QFE16	= 0x00010000,
	RIC2_QFE17	= 0x00020000,
	RIC2_RFFE	= 0x80000000,
पूर्ण;

/* RIS2 */
क्रमागत RIS2_BIT अणु
	RIS2_QFF0	= 0x00000001,
	RIS2_QFF1	= 0x00000002,
	RIS2_QFF2	= 0x00000004,
	RIS2_QFF3	= 0x00000008,
	RIS2_QFF4	= 0x00000010,
	RIS2_QFF5	= 0x00000020,
	RIS2_QFF6	= 0x00000040,
	RIS2_QFF7	= 0x00000080,
	RIS2_QFF8	= 0x00000100,
	RIS2_QFF9	= 0x00000200,
	RIS2_QFF10	= 0x00000400,
	RIS2_QFF11	= 0x00000800,
	RIS2_QFF12	= 0x00001000,
	RIS2_QFF13	= 0x00002000,
	RIS2_QFF14	= 0x00004000,
	RIS2_QFF15	= 0x00008000,
	RIS2_QFF16	= 0x00010000,
	RIS2_QFF17	= 0x00020000,
	RIS2_RFFF	= 0x80000000,
	RIS2_RESERVED	= GENMASK(30, 18),
पूर्ण;

/* TIC */
क्रमागत TIC_BIT अणु
	TIC_FTE0	= 0x00000001,	/* Documented क्रम R-Car Gen3 only */
	TIC_FTE1	= 0x00000002,	/* Documented क्रम R-Car Gen3 only */
	TIC_TFUE	= 0x00000100,
	TIC_TFWE	= 0x00000200,
पूर्ण;

/* TIS */
क्रमागत TIS_BIT अणु
	TIS_FTF0	= 0x00000001,	/* Documented क्रम R-Car Gen3 only */
	TIS_FTF1	= 0x00000002,	/* Documented क्रम R-Car Gen3 only */
	TIS_TFUF	= 0x00000100,
	TIS_TFWF	= 0x00000200,
	TIS_RESERVED	= (GENMASK(31, 20) | GENMASK(15, 12) | GENMASK(7, 4))
पूर्ण;

/* ISS */
क्रमागत ISS_BIT अणु
	ISS_FRS		= 0x00000001,	/* Documented क्रम R-Car Gen3 only */
	ISS_FTS		= 0x00000004,	/* Documented क्रम R-Car Gen3 only */
	ISS_ES		= 0x00000040,
	ISS_MS		= 0x00000080,
	ISS_TFUS	= 0x00000100,
	ISS_TFWS	= 0x00000200,
	ISS_RFWS	= 0x00001000,
	ISS_CGIS	= 0x00002000,
	ISS_DPS1	= 0x00020000,
	ISS_DPS2	= 0x00040000,
	ISS_DPS3	= 0x00080000,
	ISS_DPS4	= 0x00100000,
	ISS_DPS5	= 0x00200000,
	ISS_DPS6	= 0x00400000,
	ISS_DPS7	= 0x00800000,
	ISS_DPS8	= 0x01000000,
	ISS_DPS9	= 0x02000000,
	ISS_DPS10	= 0x04000000,
	ISS_DPS11	= 0x08000000,
	ISS_DPS12	= 0x10000000,
	ISS_DPS13	= 0x20000000,
	ISS_DPS14	= 0x40000000,
	ISS_DPS15	= 0x80000000,
पूर्ण;

/* CIE (R-Car Gen3 only) */
क्रमागत CIE_BIT अणु
	CIE_CRIE	= 0x00000001,
	CIE_CTIE	= 0x00000100,
	CIE_RQFM	= 0x00010000,
	CIE_CL0M	= 0x00020000,
	CIE_RFWL	= 0x00040000,
	CIE_RFFL	= 0x00080000,
पूर्ण;

/* GCCR */
क्रमागत GCCR_BIT अणु
	GCCR_TCR	= 0x00000003,
	GCCR_TCR_NOREQ	= 0x00000000, /* No request */
	GCCR_TCR_RESET	= 0x00000001, /* gPTP/AVTP presentation समयr reset */
	GCCR_TCR_CAPTURE = 0x00000003, /* Capture value set in GCCR.TCSS */
	GCCR_LTO	= 0x00000004,
	GCCR_LTI	= 0x00000008,
	GCCR_LPTC	= 0x00000010,
	GCCR_LMTT	= 0x00000020,
	GCCR_TCSS	= 0x00000300,
	GCCR_TCSS_GPTP	= 0x00000000,	/* gPTP समयr value */
	GCCR_TCSS_ADJGPTP = 0x00000100, /* Adjusted gPTP समयr value */
	GCCR_TCSS_AVTP	= 0x00000200,	/* AVTP presentation समय value */
पूर्ण;

/* GTI */
क्रमागत GTI_BIT अणु
	GTI_TIV		= 0x0FFFFFFF,
पूर्ण;

#घोषणा GTI_TIV_MAX	GTI_TIV
#घोषणा GTI_TIV_MIN	0x20

/* GIC */
क्रमागत GIC_BIT अणु
	GIC_PTCE	= 0x00000001,	/* Documented क्रम R-Car Gen3 only */
	GIC_PTME	= 0x00000004,
पूर्ण;

/* GIS */
क्रमागत GIS_BIT अणु
	GIS_PTCF	= 0x00000001,	/* Documented क्रम R-Car Gen3 only */
	GIS_PTMF	= 0x00000004,
	GIS_RESERVED	= GENMASK(15, 10),
पूर्ण;

/* GIE (R-Car Gen3 only) */
क्रमागत GIE_BIT अणु
	GIE_PTCS	= 0x00000001,
	GIE_PTOS	= 0x00000002,
	GIE_PTMS0	= 0x00000004,
	GIE_PTMS1	= 0x00000008,
	GIE_PTMS2	= 0x00000010,
	GIE_PTMS3	= 0x00000020,
	GIE_PTMS4	= 0x00000040,
	GIE_PTMS5	= 0x00000080,
	GIE_PTMS6	= 0x00000100,
	GIE_PTMS7	= 0x00000200,
	GIE_ATCS0	= 0x00010000,
	GIE_ATCS1	= 0x00020000,
	GIE_ATCS2	= 0x00040000,
	GIE_ATCS3	= 0x00080000,
	GIE_ATCS4	= 0x00100000,
	GIE_ATCS5	= 0x00200000,
	GIE_ATCS6	= 0x00400000,
	GIE_ATCS7	= 0x00800000,
	GIE_ATCS8	= 0x01000000,
	GIE_ATCS9	= 0x02000000,
	GIE_ATCS10	= 0x04000000,
	GIE_ATCS11	= 0x08000000,
	GIE_ATCS12	= 0x10000000,
	GIE_ATCS13	= 0x20000000,
	GIE_ATCS14	= 0x40000000,
	GIE_ATCS15	= 0x80000000,
पूर्ण;

/* GID (R-Car Gen3 only) */
क्रमागत GID_BIT अणु
	GID_PTCD	= 0x00000001,
	GID_PTOD	= 0x00000002,
	GID_PTMD0	= 0x00000004,
	GID_PTMD1	= 0x00000008,
	GID_PTMD2	= 0x00000010,
	GID_PTMD3	= 0x00000020,
	GID_PTMD4	= 0x00000040,
	GID_PTMD5	= 0x00000080,
	GID_PTMD6	= 0x00000100,
	GID_PTMD7	= 0x00000200,
	GID_ATCD0	= 0x00010000,
	GID_ATCD1	= 0x00020000,
	GID_ATCD2	= 0x00040000,
	GID_ATCD3	= 0x00080000,
	GID_ATCD4	= 0x00100000,
	GID_ATCD5	= 0x00200000,
	GID_ATCD6	= 0x00400000,
	GID_ATCD7	= 0x00800000,
	GID_ATCD8	= 0x01000000,
	GID_ATCD9	= 0x02000000,
	GID_ATCD10	= 0x04000000,
	GID_ATCD11	= 0x08000000,
	GID_ATCD12	= 0x10000000,
	GID_ATCD13	= 0x20000000,
	GID_ATCD14	= 0x40000000,
	GID_ATCD15	= 0x80000000,
पूर्ण;

/* RIE0 (R-Car Gen3 only) */
क्रमागत RIE0_BIT अणु
	RIE0_FRS0	= 0x00000001,
	RIE0_FRS1	= 0x00000002,
	RIE0_FRS2	= 0x00000004,
	RIE0_FRS3	= 0x00000008,
	RIE0_FRS4	= 0x00000010,
	RIE0_FRS5	= 0x00000020,
	RIE0_FRS6	= 0x00000040,
	RIE0_FRS7	= 0x00000080,
	RIE0_FRS8	= 0x00000100,
	RIE0_FRS9	= 0x00000200,
	RIE0_FRS10	= 0x00000400,
	RIE0_FRS11	= 0x00000800,
	RIE0_FRS12	= 0x00001000,
	RIE0_FRS13	= 0x00002000,
	RIE0_FRS14	= 0x00004000,
	RIE0_FRS15	= 0x00008000,
	RIE0_FRS16	= 0x00010000,
	RIE0_FRS17	= 0x00020000,
पूर्ण;

/* RID0 (R-Car Gen3 only) */
क्रमागत RID0_BIT अणु
	RID0_FRD0	= 0x00000001,
	RID0_FRD1	= 0x00000002,
	RID0_FRD2	= 0x00000004,
	RID0_FRD3	= 0x00000008,
	RID0_FRD4	= 0x00000010,
	RID0_FRD5	= 0x00000020,
	RID0_FRD6	= 0x00000040,
	RID0_FRD7	= 0x00000080,
	RID0_FRD8	= 0x00000100,
	RID0_FRD9	= 0x00000200,
	RID0_FRD10	= 0x00000400,
	RID0_FRD11	= 0x00000800,
	RID0_FRD12	= 0x00001000,
	RID0_FRD13	= 0x00002000,
	RID0_FRD14	= 0x00004000,
	RID0_FRD15	= 0x00008000,
	RID0_FRD16	= 0x00010000,
	RID0_FRD17	= 0x00020000,
पूर्ण;

/* RIE2 (R-Car Gen3 only) */
क्रमागत RIE2_BIT अणु
	RIE2_QFS0	= 0x00000001,
	RIE2_QFS1	= 0x00000002,
	RIE2_QFS2	= 0x00000004,
	RIE2_QFS3	= 0x00000008,
	RIE2_QFS4	= 0x00000010,
	RIE2_QFS5	= 0x00000020,
	RIE2_QFS6	= 0x00000040,
	RIE2_QFS7	= 0x00000080,
	RIE2_QFS8	= 0x00000100,
	RIE2_QFS9	= 0x00000200,
	RIE2_QFS10	= 0x00000400,
	RIE2_QFS11	= 0x00000800,
	RIE2_QFS12	= 0x00001000,
	RIE2_QFS13	= 0x00002000,
	RIE2_QFS14	= 0x00004000,
	RIE2_QFS15	= 0x00008000,
	RIE2_QFS16	= 0x00010000,
	RIE2_QFS17	= 0x00020000,
	RIE2_RFFS	= 0x80000000,
पूर्ण;

/* RID2 (R-Car Gen3 only) */
क्रमागत RID2_BIT अणु
	RID2_QFD0	= 0x00000001,
	RID2_QFD1	= 0x00000002,
	RID2_QFD2	= 0x00000004,
	RID2_QFD3	= 0x00000008,
	RID2_QFD4	= 0x00000010,
	RID2_QFD5	= 0x00000020,
	RID2_QFD6	= 0x00000040,
	RID2_QFD7	= 0x00000080,
	RID2_QFD8	= 0x00000100,
	RID2_QFD9	= 0x00000200,
	RID2_QFD10	= 0x00000400,
	RID2_QFD11	= 0x00000800,
	RID2_QFD12	= 0x00001000,
	RID2_QFD13	= 0x00002000,
	RID2_QFD14	= 0x00004000,
	RID2_QFD15	= 0x00008000,
	RID2_QFD16	= 0x00010000,
	RID2_QFD17	= 0x00020000,
	RID2_RFFD	= 0x80000000,
पूर्ण;

/* TIE (R-Car Gen3 only) */
क्रमागत TIE_BIT अणु
	TIE_FTS0	= 0x00000001,
	TIE_FTS1	= 0x00000002,
	TIE_FTS2	= 0x00000004,
	TIE_FTS3	= 0x00000008,
	TIE_TFUS	= 0x00000100,
	TIE_TFWS	= 0x00000200,
	TIE_MFUS	= 0x00000400,
	TIE_MFWS	= 0x00000800,
	TIE_TDPS0	= 0x00010000,
	TIE_TDPS1	= 0x00020000,
	TIE_TDPS2	= 0x00040000,
	TIE_TDPS3	= 0x00080000,
पूर्ण;

/* TID (R-Car Gen3 only) */
क्रमागत TID_BIT अणु
	TID_FTD0	= 0x00000001,
	TID_FTD1	= 0x00000002,
	TID_FTD2	= 0x00000004,
	TID_FTD3	= 0x00000008,
	TID_TFUD	= 0x00000100,
	TID_TFWD	= 0x00000200,
	TID_MFUD	= 0x00000400,
	TID_MFWD	= 0x00000800,
	TID_TDPD0	= 0x00010000,
	TID_TDPD1	= 0x00020000,
	TID_TDPD2	= 0x00040000,
	TID_TDPD3	= 0x00080000,
पूर्ण;

/* ECMR */
क्रमागत ECMR_BIT अणु
	ECMR_PRM	= 0x00000001,
	ECMR_DM		= 0x00000002,
	ECMR_TE		= 0x00000020,
	ECMR_RE		= 0x00000040,
	ECMR_MPDE	= 0x00000200,
	ECMR_TXF	= 0x00010000,	/* Documented क्रम R-Car Gen3 only */
	ECMR_RXF	= 0x00020000,
	ECMR_PFR	= 0x00040000,
	ECMR_ZPF	= 0x00080000,	/* Documented क्रम R-Car Gen3 only */
	ECMR_RZPF	= 0x00100000,
	ECMR_DPAD	= 0x00200000,
	ECMR_RCSC	= 0x00800000,
	ECMR_TRCCM	= 0x04000000,
पूर्ण;

/* ECSR */
क्रमागत ECSR_BIT अणु
	ECSR_ICD	= 0x00000001,
	ECSR_MPD	= 0x00000002,
	ECSR_LCHNG	= 0x00000004,
	ECSR_PHYI	= 0x00000008,
पूर्ण;

/* ECSIPR */
क्रमागत ECSIPR_BIT अणु
	ECSIPR_ICDIP	= 0x00000001,
	ECSIPR_MPDIP	= 0x00000002,
	ECSIPR_LCHNGIP	= 0x00000004,
पूर्ण;

/* PIR */
क्रमागत PIR_BIT अणु
	PIR_MDC		= 0x00000001,
	PIR_MMD		= 0x00000002,
	PIR_MDO		= 0x00000004,
	PIR_MDI		= 0x00000008,
पूर्ण;

/* PSR */
क्रमागत PSR_BIT अणु
	PSR_LMON	= 0x00000001,
पूर्ण;

/* PIPR */
क्रमागत PIPR_BIT अणु
	PIPR_PHYIP	= 0x00000001,
पूर्ण;

/* MPR */
क्रमागत MPR_BIT अणु
	MPR_MP		= 0x0000ffff,
पूर्ण;

/* GECMR */
क्रमागत GECMR_BIT अणु
	GECMR_SPEED	= 0x00000001,
	GECMR_SPEED_100	= 0x00000000,
	GECMR_SPEED_1000 = 0x00000001,
पूर्ण;

/* The Ethernet AVB descriptor definitions. */
काष्ठा ravb_desc अणु
	__le16 ds;		/* Descriptor size */
	u8 cc;		/* Content control MSBs (reserved) */
	u8 die_dt;	/* Descriptor पूर्णांकerrupt enable and type */
	__le32 dptr;	/* Descriptor poपूर्णांकer */
पूर्ण;

#घोषणा DPTR_ALIGN	4	/* Required descriptor poपूर्णांकer alignment */

क्रमागत DIE_DT अणु
	/* Frame data */
	DT_FMID		= 0x40,
	DT_FSTART	= 0x50,
	DT_FEND		= 0x60,
	DT_FSINGLE	= 0x70,
	/* Chain control */
	DT_LINK		= 0x80,
	DT_LINKFIX	= 0x90,
	DT_EOS		= 0xa0,
	/* HW/SW arbitration */
	DT_FEMPTY	= 0xc0,
	DT_FEMPTY_IS	= 0xd0,
	DT_FEMPTY_IC	= 0xe0,
	DT_FEMPTY_ND	= 0xf0,
	DT_LEMPTY	= 0x20,
	DT_EEMPTY	= 0x30,
पूर्ण;

काष्ठा ravb_rx_desc अणु
	__le16 ds_cc;	/* Descriptor size and content control LSBs */
	u8 msc;		/* MAC status code */
	u8 die_dt;	/* Descriptor पूर्णांकerrupt enable and type */
	__le32 dptr;	/* Descpriptor poपूर्णांकer */
पूर्ण;

काष्ठा ravb_ex_rx_desc अणु
	__le16 ds_cc;	/* Descriptor size and content control lower bits */
	u8 msc;		/* MAC status code */
	u8 die_dt;	/* Descriptor पूर्णांकerrupt enable and type */
	__le32 dptr;	/* Descpriptor poपूर्णांकer */
	__le32 ts_n;	/* Timestampe nsec */
	__le32 ts_sl;	/* Timestamp low */
	__le16 ts_sh;	/* Timestamp high */
	__le16 res;	/* Reserved bits */
पूर्ण;

क्रमागत RX_DS_CC_BIT अणु
	RX_DS		= 0x0fff, /* Data size */
	RX_TR		= 0x1000, /* Truncation indication */
	RX_EI		= 0x2000, /* Error indication */
	RX_PS		= 0xc000, /* Padding selection */
पूर्ण;

/* E-MAC status code */
क्रमागत MSC_BIT अणु
	MSC_CRC		= 0x01, /* Frame CRC error */
	MSC_RFE		= 0x02, /* Frame reception error (flagged by PHY) */
	MSC_RTSF	= 0x04, /* Frame length error (frame too लघु) */
	MSC_RTLF	= 0x08, /* Frame length error (frame too दीर्घ) */
	MSC_FRE		= 0x10, /* Fraction error (not a multiple of 8 bits) */
	MSC_CRL		= 0x20, /* Carrier lost */
	MSC_CEEF	= 0x40, /* Carrier extension error */
	MSC_MC		= 0x80, /* Multicast frame reception */
पूर्ण;

काष्ठा ravb_tx_desc अणु
	__le16 ds_tagl;	/* Descriptor size and frame tag LSBs */
	u8 tagh_tsr;	/* Frame tag MSBs and बारtamp storage request bit */
	u8 die_dt;	/* Descriptor पूर्णांकerrupt enable and type */
	__le32 dptr;	/* Descpriptor poपूर्णांकer */
पूर्ण;

क्रमागत TX_DS_TAGL_BIT अणु
	TX_DS		= 0x0fff, /* Data size */
	TX_TAGL		= 0xf000, /* Frame tag LSBs */
पूर्ण;

क्रमागत TX_TAGH_TSR_BIT अणु
	TX_TAGH		= 0x3f, /* Frame tag MSBs */
	TX_TSR		= 0x40, /* Timestamp storage request */
पूर्ण;
क्रमागत RAVB_QUEUE अणु
	RAVB_BE = 0,	/* Best Efक्रमt Queue */
	RAVB_NC,	/* Network Control Queue */
पूर्ण;

#घोषणा DBAT_ENTRY_NUM	22
#घोषणा RX_QUEUE_OFFSET	4
#घोषणा NUM_RX_QUEUE	2
#घोषणा NUM_TX_QUEUE	2

#घोषणा RX_BUF_SZ	(2048 - ETH_FCS_LEN + माप(__sum16))

/* TX descriptors per packet */
#घोषणा NUM_TX_DESC_GEN2	2
#घोषणा NUM_TX_DESC_GEN3	1

काष्ठा ravb_tstamp_skb अणु
	काष्ठा list_head list;
	काष्ठा sk_buff *skb;
	u16 tag;
पूर्ण;

काष्ठा ravb_ptp_perout अणु
	u32 target;
	u32 period;
पूर्ण;

#घोषणा N_EXT_TS	1
#घोषणा N_PER_OUT	1

काष्ठा ravb_ptp अणु
	काष्ठा ptp_घड़ी *घड़ी;
	काष्ठा ptp_घड़ी_info info;
	u32 शेष_addend;
	u32 current_addend;
	पूर्णांक extts[N_EXT_TS];
	काष्ठा ravb_ptp_perout perout[N_PER_OUT];
पूर्ण;

क्रमागत ravb_chip_id अणु
	RCAR_GEN2,
	RCAR_GEN3,
पूर्ण;

काष्ठा ravb_निजी अणु
	काष्ठा net_device *ndev;
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *addr;
	काष्ठा clk *clk;
	काष्ठा clk *refclk;
	काष्ठा mdiobb_ctrl mdiobb;
	u32 num_rx_ring[NUM_RX_QUEUE];
	u32 num_tx_ring[NUM_TX_QUEUE];
	u32 desc_bat_size;
	dma_addr_t desc_bat_dma;
	काष्ठा ravb_desc *desc_bat;
	dma_addr_t rx_desc_dma[NUM_RX_QUEUE];
	dma_addr_t tx_desc_dma[NUM_TX_QUEUE];
	काष्ठा ravb_ex_rx_desc *rx_ring[NUM_RX_QUEUE];
	काष्ठा ravb_tx_desc *tx_ring[NUM_TX_QUEUE];
	व्योम *tx_align[NUM_TX_QUEUE];
	काष्ठा sk_buff **rx_skb[NUM_RX_QUEUE];
	काष्ठा sk_buff **tx_skb[NUM_TX_QUEUE];
	u32 rx_over_errors;
	u32 rx_fअगरo_errors;
	काष्ठा net_device_stats stats[NUM_RX_QUEUE];
	u32 tstamp_tx_ctrl;
	u32 tstamp_rx_ctrl;
	काष्ठा list_head ts_skb_list;
	u32 ts_skb_tag;
	काष्ठा ravb_ptp ptp;
	spinlock_t lock;		/* Register access lock */
	u32 cur_rx[NUM_RX_QUEUE];	/* Consumer ring indices */
	u32 dirty_rx[NUM_RX_QUEUE];	/* Producer ring indices */
	u32 cur_tx[NUM_TX_QUEUE];
	u32 dirty_tx[NUM_TX_QUEUE];
	काष्ठा napi_काष्ठा napi[NUM_RX_QUEUE];
	काष्ठा work_काष्ठा work;
	/* MII transceiver section. */
	काष्ठा mii_bus *mii_bus;	/* MDIO bus control */
	पूर्णांक link;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	पूर्णांक msg_enable;
	पूर्णांक speed;
	पूर्णांक emac_irq;
	क्रमागत ravb_chip_id chip_id;
	पूर्णांक rx_irqs[NUM_RX_QUEUE];
	पूर्णांक tx_irqs[NUM_TX_QUEUE];

	अचिन्हित no_avb_link:1;
	अचिन्हित avb_link_active_low:1;
	अचिन्हित wol_enabled:1;
	अचिन्हित rxcidm:1;		/* RX Clock Internal Delay Mode */
	अचिन्हित txcidm:1;		/* TX Clock Internal Delay Mode */
	अचिन्हित rgmii_override:1;	/* Deprecated rgmii-*id behavior */
	पूर्णांक num_tx_desc;		/* TX descriptors per packet */
पूर्ण;

अटल अंतरभूत u32 ravb_पढ़ो(काष्ठा net_device *ndev, क्रमागत ravb_reg reg)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	वापस ioपढ़ो32(priv->addr + reg);
पूर्ण

अटल अंतरभूत व्योम ravb_ग_लिखो(काष्ठा net_device *ndev, u32 data,
			      क्रमागत ravb_reg reg)
अणु
	काष्ठा ravb_निजी *priv = netdev_priv(ndev);

	ioग_लिखो32(data, priv->addr + reg);
पूर्ण

व्योम ravb_modअगरy(काष्ठा net_device *ndev, क्रमागत ravb_reg reg, u32 clear,
		 u32 set);
पूर्णांक ravb_रुको(काष्ठा net_device *ndev, क्रमागत ravb_reg reg, u32 mask, u32 value);

व्योम ravb_ptp_पूर्णांकerrupt(काष्ठा net_device *ndev);
व्योम ravb_ptp_init(काष्ठा net_device *ndev, काष्ठा platक्रमm_device *pdev);
व्योम ravb_ptp_stop(काष्ठा net_device *ndev);

#पूर्ण_अगर	/* #अगर_अघोषित __RAVB_H__ */
