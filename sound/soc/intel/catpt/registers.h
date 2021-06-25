<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 * Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
 */

#अगर_अघोषित __SND_SOC_INTEL_CATPT_REGS_H
#घोषणा __SND_SOC_INTEL_CATPT_REGS_H

#समावेश <linux/bitops.h>
#समावेश <linux/iopoll.h>
#समावेश <uapi/linux/pci_regs.h>

#घोषणा CATPT_SHIM_REGS_SIZE	4096
#घोषणा CATPT_DMA_REGS_SIZE	1024
#घोषणा CATPT_DMA_COUNT		2
#घोषणा CATPT_SSP_REGS_SIZE	512

/* DSP Shim रेजिस्टरs */

#घोषणा CATPT_SHIM_CS1		0x00
#घोषणा CATPT_SHIM_ISC		0x18
#घोषणा CATPT_SHIM_ISD		0x20
#घोषणा CATPT_SHIM_IMC		0x28
#घोषणा CATPT_SHIM_IMD		0x30
#घोषणा CATPT_SHIM_IPCC		0x38
#घोषणा CATPT_SHIM_IPCD		0x40
#घोषणा CATPT_SHIM_CLKCTL	0x78
#घोषणा CATPT_SHIM_CS2		0x80
#घोषणा CATPT_SHIM_LTRC		0xE0
#घोषणा CATPT_SHIM_HMDC		0xE8

#घोषणा CATPT_CS_LPCS		BIT(31)
#घोषणा CATPT_CS_SFCR(ssp)	BIT(27 + (ssp))
#घोषणा CATPT_CS_S1IOCS		BIT(23)
#घोषणा CATPT_CS_S0IOCS		BIT(21)
#घोषणा CATPT_CS_PCE		BIT(15)
#घोषणा CATPT_CS_SDPM(ssp)	BIT(11 + (ssp))
#घोषणा CATPT_CS_STALL		BIT(10)
#घोषणा CATPT_CS_DCS		GENMASK(6, 4)
/* b100 DSP core & audio fabric high घड़ी */
#घोषणा CATPT_CS_DCS_HIGH	(0x4 << 4)
#घोषणा CATPT_CS_SBCS(ssp)	BIT(2 + (ssp))
#घोषणा CATPT_CS_RST		BIT(1)

#घोषणा CATPT_ISC_IPCDB		BIT(1)
#घोषणा CATPT_ISC_IPCCD		BIT(0)
#घोषणा CATPT_ISD_DCPWM		BIT(31)
#घोषणा CATPT_ISD_IPCCB		BIT(1)
#घोषणा CATPT_ISD_IPCDD		BIT(0)

#घोषणा CATPT_IMC_IPCDB		BIT(1)
#घोषणा CATPT_IMC_IPCCD		BIT(0)
#घोषणा CATPT_IMD_IPCCB		BIT(1)
#घोषणा CATPT_IMD_IPCDD		BIT(0)

#घोषणा CATPT_IPCC_BUSY		BIT(31)
#घोषणा CATPT_IPCC_DONE		BIT(30)
#घोषणा CATPT_IPCD_BUSY		BIT(31)
#घोषणा CATPT_IPCD_DONE		BIT(30)

#घोषणा CATPT_CLKCTL_CFCIP	BIT(31)
#घोषणा CATPT_CLKCTL_SMOS	GENMASK(25, 24)

#घोषणा CATPT_HMDC_HDDA(e, ch)	BIT(8 * (e) + (ch))

/* शेषs to reset SHIM रेजिस्टरs to after each घातer cycle */
#घोषणा CATPT_CS_DEFAULT	0x8480040E
#घोषणा CATPT_ISC_DEFAULT	0x0
#घोषणा CATPT_ISD_DEFAULT	0x0
#घोषणा CATPT_IMC_DEFAULT	0x7FFF0003
#घोषणा CATPT_IMD_DEFAULT	0x7FFF0003
#घोषणा CATPT_IPCC_DEFAULT	0x0
#घोषणा CATPT_IPCD_DEFAULT	0x0
#घोषणा CATPT_CLKCTL_DEFAULT	0x7FF
#घोषणा CATPT_CS2_DEFAULT	0x0
#घोषणा CATPT_LTRC_DEFAULT	0x0
#घोषणा CATPT_HMDC_DEFAULT	0x0

/* PCI Configuration रेजिस्टरs */

#घोषणा CATPT_PCI_PMCAPID	0x80
#घोषणा CATPT_PCI_PMCS		(CATPT_PCI_PMCAPID + PCI_PM_CTRL)
#घोषणा CATPT_PCI_VDRTCTL0	0xA0
#घोषणा CATPT_PCI_VDRTCTL2	0xA8

#घोषणा CATPT_VDRTCTL2_DTCGE	BIT(10)
#घोषणा CATPT_VDRTCTL2_DCLCGE	BIT(1)
#घोषणा CATPT_VDRTCTL2_CGEALL	0xF7F

/* LPT PCI Configuration bits */

#घोषणा LPT_VDRTCTL0_DSRAMPGE(b)	BIT(16 + (b))
#घोषणा LPT_VDRTCTL0_DSRAMPGE_MASK	GENMASK(31, 16)
#घोषणा LPT_VDRTCTL0_ISRAMPGE(b)	BIT(6 + (b))
#घोषणा LPT_VDRTCTL0_ISRAMPGE_MASK	GENMASK(15, 6)
#घोषणा LPT_VDRTCTL0_D3SRAMPGD		BIT(2)
#घोषणा LPT_VDRTCTL0_D3PGD		BIT(1)
#घोषणा LPT_VDRTCTL0_APLLSE		BIT(0)

/* WPT PCI Configuration bits */

#घोषणा WPT_VDRTCTL0_DSRAMPGE(b)	BIT(12 + (b))
#घोषणा WPT_VDRTCTL0_DSRAMPGE_MASK	GENMASK(31, 12)
#घोषणा WPT_VDRTCTL0_ISRAMPGE(b)	BIT(2 + (b))
#घोषणा WPT_VDRTCTL0_ISRAMPGE_MASK	GENMASK(11, 2)
#घोषणा WPT_VDRTCTL0_D3SRAMPGD		BIT(1)
#घोषणा WPT_VDRTCTL0_D3PGD		BIT(0)

#घोषणा WPT_VDRTCTL2_APLLSE		BIT(31)

/* शेषs to reset SSP रेजिस्टरs to after each घातer cycle */
#घोषणा CATPT_SSC0_DEFAULT		0x0
#घोषणा CATPT_SSC1_DEFAULT		0x0
#घोषणा CATPT_SSS_DEFAULT		0xF004
#घोषणा CATPT_SSIT_DEFAULT		0x0
#घोषणा CATPT_SSD_DEFAULT		0xC43893A3
#घोषणा CATPT_SSTO_DEFAULT		0x0
#घोषणा CATPT_SSPSP_DEFAULT		0x0
#घोषणा CATPT_SSTSA_DEFAULT		0x0
#घोषणा CATPT_SSRSA_DEFAULT		0x0
#घोषणा CATPT_SSTSS_DEFAULT		0x0
#घोषणा CATPT_SSCR2_DEFAULT		0x0
#घोषणा CATPT_SSPSP2_DEFAULT		0x0

/* Physically the same block, access address dअगरfers between host and dsp */
#घोषणा CATPT_DSP_DRAM_OFFSET		0x400000
#घोषणा catpt_to_host_offset(offset)	((offset) & ~(CATPT_DSP_DRAM_OFFSET))
#घोषणा catpt_to_dsp_offset(offset)	((offset) | CATPT_DSP_DRAM_OFFSET)

#घोषणा CATPT_MEMBLOCK_SIZE	0x8000
#घोषणा catpt_num_dram(cdev)	(hweight_दीर्घ((cdev)->spec->dram_mask))
#घोषणा catpt_num_iram(cdev)	(hweight_दीर्घ((cdev)->spec->iram_mask))
#घोषणा catpt_dram_size(cdev)	(catpt_num_dram(cdev) * CATPT_MEMBLOCK_SIZE)
#घोषणा catpt_iram_size(cdev)	(catpt_num_iram(cdev) * CATPT_MEMBLOCK_SIZE)

/* registry I/O helpers */

#घोषणा catpt_shim_addr(cdev) \
	((cdev)->lpe_ba + (cdev)->spec->host_shim_offset)
#घोषणा catpt_dma_addr(cdev, dma) \
	((cdev)->lpe_ba + (cdev)->spec->host_dma_offset[dma])
#घोषणा catpt_ssp_addr(cdev, ssp) \
	((cdev)->lpe_ba + (cdev)->spec->host_ssp_offset[ssp])
#घोषणा catpt_inbox_addr(cdev) \
	((cdev)->lpe_ba + (cdev)->ipc.config.inbox_offset)
#घोषणा catpt_outbox_addr(cdev) \
	((cdev)->lpe_ba + (cdev)->ipc.config.outbox_offset)

#घोषणा catpt_ग_लिखोl_ssp(cdev, ssp, reg, val) \
	ग_लिखोl(val, catpt_ssp_addr(cdev, ssp) + (reg))

#घोषणा catpt_पढ़ोl_shim(cdev, reg) \
	पढ़ोl(catpt_shim_addr(cdev) + CATPT_SHIM_##reg)
#घोषणा catpt_ग_लिखोl_shim(cdev, reg, val) \
	ग_लिखोl(val, catpt_shim_addr(cdev) + CATPT_SHIM_##reg)
#घोषणा catpt_updatel_shim(cdev, reg, mask, val) \
	catpt_ग_लिखोl_shim(cdev, reg, \
			  (catpt_पढ़ोl_shim(cdev, reg) & ~(mask)) | (val))

#घोषणा catpt_पढ़ोl_poll_shim(cdev, reg, val, cond, delay_us, समयout_us) \
	पढ़ोl_poll_समयout(catpt_shim_addr(cdev) + CATPT_SHIM_##reg, \
			   val, cond, delay_us, समयout_us)

#घोषणा catpt_पढ़ोl_pci(cdev, reg) \
	पढ़ोl(cdev->pci_ba + CATPT_PCI_##reg)
#घोषणा catpt_ग_लिखोl_pci(cdev, reg, val) \
	ग_लिखोl(val, cdev->pci_ba + CATPT_PCI_##reg)
#घोषणा catpt_updatel_pci(cdev, reg, mask, val) \
	catpt_ग_लिखोl_pci(cdev, reg, \
			 (catpt_पढ़ोl_pci(cdev, reg) & ~(mask)) | (val))

#घोषणा catpt_पढ़ोl_poll_pci(cdev, reg, val, cond, delay_us, समयout_us) \
	पढ़ोl_poll_समयout((cdev)->pci_ba + CATPT_PCI_##reg, \
			   val, cond, delay_us, समयout_us)

#पूर्ण_अगर
