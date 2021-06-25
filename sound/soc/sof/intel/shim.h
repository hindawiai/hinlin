<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2017 Intel Corporation. All rights reserved.
 *
 * Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __SOF_INTEL_SHIM_H
#घोषणा __SOF_INTEL_SHIM_H

/*
 * SHIM रेजिस्टरs क्रम BYT, BSW, CHT, BDW
 */

#घोषणा SHIM_CSR		(SHIM_OFFSET + 0x00)
#घोषणा SHIM_PISR		(SHIM_OFFSET + 0x08)
#घोषणा SHIM_PIMR		(SHIM_OFFSET + 0x10)
#घोषणा SHIM_ISRX		(SHIM_OFFSET + 0x18)
#घोषणा SHIM_ISRD		(SHIM_OFFSET + 0x20)
#घोषणा SHIM_IMRX		(SHIM_OFFSET + 0x28)
#घोषणा SHIM_IMRD		(SHIM_OFFSET + 0x30)
#घोषणा SHIM_IPCX		(SHIM_OFFSET + 0x38)
#घोषणा SHIM_IPCD		(SHIM_OFFSET + 0x40)
#घोषणा SHIM_ISRSC		(SHIM_OFFSET + 0x48)
#घोषणा SHIM_ISRLPESC		(SHIM_OFFSET + 0x50)
#घोषणा SHIM_IMRSC		(SHIM_OFFSET + 0x58)
#घोषणा SHIM_IMRLPESC		(SHIM_OFFSET + 0x60)
#घोषणा SHIM_IPCSC		(SHIM_OFFSET + 0x68)
#घोषणा SHIM_IPCLPESC		(SHIM_OFFSET + 0x70)
#घोषणा SHIM_CLKCTL		(SHIM_OFFSET + 0x78)
#घोषणा SHIM_CSR2		(SHIM_OFFSET + 0x80)
#घोषणा SHIM_LTRC		(SHIM_OFFSET + 0xE0)
#घोषणा SHIM_HMDC		(SHIM_OFFSET + 0xE8)

#घोषणा SHIM_PWMCTRL		0x1000

/*
 * SST SHIM रेजिस्टर bits क्रम BYT, BSW, CHT, BDW
 * Register bit naming and functionaility can dअगरfer between devices.
 */

/* CSR / CS */
#घोषणा SHIM_CSR_RST		BIT(1)
#घोषणा SHIM_CSR_SBCS0		BIT(2)
#घोषणा SHIM_CSR_SBCS1		BIT(3)
#घोषणा SHIM_CSR_DCS(x)		((x) << 4)
#घोषणा SHIM_CSR_DCS_MASK	(0x7 << 4)
#घोषणा SHIM_CSR_STALL		BIT(10)
#घोषणा SHIM_CSR_S0IOCS		BIT(21)
#घोषणा SHIM_CSR_S1IOCS		BIT(23)
#घोषणा SHIM_CSR_LPCS		BIT(31)
#घोषणा SHIM_CSR_24MHZ_LPCS \
	(SHIM_CSR_SBCS0 | SHIM_CSR_SBCS1 | SHIM_CSR_LPCS)
#घोषणा SHIM_CSR_24MHZ_NO_LPCS	(SHIM_CSR_SBCS0 | SHIM_CSR_SBCS1)
#घोषणा SHIM_BYT_CSR_RST	BIT(0)
#घोषणा SHIM_BYT_CSR_VECTOR_SEL	BIT(1)
#घोषणा SHIM_BYT_CSR_STALL	BIT(2)
#घोषणा SHIM_BYT_CSR_PWAITMODE	BIT(3)

/*  ISRX / ISC */
#घोषणा SHIM_ISRX_BUSY		BIT(1)
#घोषणा SHIM_ISRX_DONE		BIT(0)
#घोषणा SHIM_BYT_ISRX_REQUEST	BIT(1)

/*  ISRD / ISD */
#घोषणा SHIM_ISRD_BUSY		BIT(1)
#घोषणा SHIM_ISRD_DONE		BIT(0)

/* IMRX / IMC */
#घोषणा SHIM_IMRX_BUSY		BIT(1)
#घोषणा SHIM_IMRX_DONE		BIT(0)
#घोषणा SHIM_BYT_IMRX_REQUEST	BIT(1)

/* IMRD / IMD */
#घोषणा SHIM_IMRD_DONE		BIT(0)
#घोषणा SHIM_IMRD_BUSY		BIT(1)
#घोषणा SHIM_IMRD_SSP0		BIT(16)
#घोषणा SHIM_IMRD_DMAC0		BIT(21)
#घोषणा SHIM_IMRD_DMAC1		BIT(22)
#घोषणा SHIM_IMRD_DMAC		(SHIM_IMRD_DMAC0 | SHIM_IMRD_DMAC1)

/*  IPCX / IPCC */
#घोषणा	SHIM_IPCX_DONE		BIT(30)
#घोषणा	SHIM_IPCX_BUSY		BIT(31)
#घोषणा SHIM_BYT_IPCX_DONE	BIT_ULL(62)
#घोषणा SHIM_BYT_IPCX_BUSY	BIT_ULL(63)

/*  IPCD */
#घोषणा	SHIM_IPCD_DONE		BIT(30)
#घोषणा	SHIM_IPCD_BUSY		BIT(31)
#घोषणा SHIM_BYT_IPCD_DONE	BIT_ULL(62)
#घोषणा SHIM_BYT_IPCD_BUSY	BIT_ULL(63)

/* CLKCTL */
#घोषणा SHIM_CLKCTL_SMOS(x)	((x) << 24)
#घोषणा SHIM_CLKCTL_MASK	(3 << 24)
#घोषणा SHIM_CLKCTL_DCPLCG	BIT(18)
#घोषणा SHIM_CLKCTL_SCOE1	BIT(17)
#घोषणा SHIM_CLKCTL_SCOE0	BIT(16)

/* CSR2 / CS2 */
#घोषणा SHIM_CSR2_SDFD_SSP0	BIT(1)
#घोषणा SHIM_CSR2_SDFD_SSP1	BIT(2)

/* LTRC */
#घोषणा SHIM_LTRC_VAL(x)	((x) << 0)

/* HMDC */
#घोषणा SHIM_HMDC_HDDA0(x)	((x) << 0)
#घोषणा SHIM_HMDC_HDDA1(x)	((x) << 7)
#घोषणा SHIM_HMDC_HDDA_E0_CH0	1
#घोषणा SHIM_HMDC_HDDA_E0_CH1	2
#घोषणा SHIM_HMDC_HDDA_E0_CH2	4
#घोषणा SHIM_HMDC_HDDA_E0_CH3	8
#घोषणा SHIM_HMDC_HDDA_E1_CH0	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH0)
#घोषणा SHIM_HMDC_HDDA_E1_CH1	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH1)
#घोषणा SHIM_HMDC_HDDA_E1_CH2	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH2)
#घोषणा SHIM_HMDC_HDDA_E1_CH3	SHIM_HMDC_HDDA1(SHIM_HMDC_HDDA_E0_CH3)
#घोषणा SHIM_HMDC_HDDA_E0_ALLCH	\
	(SHIM_HMDC_HDDA_E0_CH0 | SHIM_HMDC_HDDA_E0_CH1 | \
	 SHIM_HMDC_HDDA_E0_CH2 | SHIM_HMDC_HDDA_E0_CH3)
#घोषणा SHIM_HMDC_HDDA_E1_ALLCH	\
	(SHIM_HMDC_HDDA_E1_CH0 | SHIM_HMDC_HDDA_E1_CH1 | \
	 SHIM_HMDC_HDDA_E1_CH2 | SHIM_HMDC_HDDA_E1_CH3)

/* Audio DSP PCI रेजिस्टरs */
#घोषणा PCI_VDRTCTL0		0xa0
#घोषणा PCI_VDRTCTL1		0xa4
#घोषणा PCI_VDRTCTL2		0xa8
#घोषणा PCI_VDRTCTL3		0xaC

/* VDRTCTL0 */
#घोषणा PCI_VDRTCL0_D3PGD		BIT(0)
#घोषणा PCI_VDRTCL0_D3SRAMPGD		BIT(1)
#घोषणा PCI_VDRTCL0_DSRAMPGE_SHIFT	12
#घोषणा PCI_VDRTCL0_DSRAMPGE_MASK	GENMASK(PCI_VDRTCL0_DSRAMPGE_SHIFT + 19,\
						PCI_VDRTCL0_DSRAMPGE_SHIFT)
#घोषणा PCI_VDRTCL0_ISRAMPGE_SHIFT	2
#घोषणा PCI_VDRTCL0_ISRAMPGE_MASK	GENMASK(PCI_VDRTCL0_ISRAMPGE_SHIFT + 9,\
						PCI_VDRTCL0_ISRAMPGE_SHIFT)

/* VDRTCTL2 */
#घोषणा PCI_VDRTCL2_DCLCGE		BIT(1)
#घोषणा PCI_VDRTCL2_DTCGE		BIT(10)
#घोषणा PCI_VDRTCL2_APLLSE_MASK		BIT(31)

/* PMCS */
#घोषणा PCI_PMCS		0x84
#घोषणा PCI_PMCS_PS_MASK	0x3

/* DSP hardware descriptor */
काष्ठा sof_पूर्णांकel_dsp_desc अणु
	पूर्णांक cores_num;
	पूर्णांक host_managed_cores_mask;
	पूर्णांक init_core_mask; /* cores available after fw boot */
	पूर्णांक ipc_req;
	पूर्णांक ipc_req_mask;
	पूर्णांक ipc_ack;
	पूर्णांक ipc_ack_mask;
	पूर्णांक ipc_ctl;
	पूर्णांक rom_init_समयout;
	पूर्णांक ssp_count;			/* ssp count of the platक्रमm */
	पूर्णांक ssp_base_offset;		/* base address of the SSPs */
पूर्ण;

बाह्य स्थिर काष्ठा snd_sof_dsp_ops sof_tng_ops;

बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tng_chip_info;

काष्ठा sof_पूर्णांकel_stream अणु
	माप_प्रकार posn_offset;
पूर्ण;

#पूर्ण_अगर
