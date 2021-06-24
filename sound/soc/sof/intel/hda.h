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

#अगर_अघोषित __SOF_INTEL_HDA_H
#घोषणा __SOF_INTEL_HDA_H

#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_पूर्णांकel.h>
#समावेश <sound/compress_driver.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/hdaudio_ext.h>
#समावेश "shim.h"

/* PCI रेजिस्टरs */
#घोषणा PCI_TCSEL			0x44
#घोषणा PCI_PGCTL			PCI_TCSEL
#घोषणा PCI_CGCTL			0x48

/* PCI_PGCTL bits */
#घोषणा PCI_PGCTL_ADSPPGD               BIT(2)
#घोषणा PCI_PGCTL_LSRMD_MASK		BIT(4)

/* PCI_CGCTL bits */
#घोषणा PCI_CGCTL_MISCBDCGE_MASK	BIT(6)
#घोषणा PCI_CGCTL_ADSPDCGE              BIT(1)

/* Legacy HDA रेजिस्टरs and bits used - widths are variable */
#घोषणा SOF_HDA_GCAP			0x0
#घोषणा SOF_HDA_GCTL			0x8
/* accept unsol. response enable */
#घोषणा SOF_HDA_GCTL_UNSOL		BIT(8)
#घोषणा SOF_HDA_LLCH			0x14
#घोषणा SOF_HDA_INTCTL			0x20
#घोषणा SOF_HDA_INTSTS			0x24
#घोषणा SOF_HDA_WAKESTS			0x0E
#घोषणा SOF_HDA_WAKESTS_INT_MASK	((1 << 8) - 1)
#घोषणा SOF_HDA_RIRBSTS			0x5d

/* SOF_HDA_GCTL रेजिस्टर bist */
#घोषणा SOF_HDA_GCTL_RESET		BIT(0)

/* SOF_HDA_INCTL regs */
#घोषणा SOF_HDA_INT_GLOBAL_EN		BIT(31)
#घोषणा SOF_HDA_INT_CTRL_EN		BIT(30)
#घोषणा SOF_HDA_INT_ALL_STREAM		0xff

/* SOF_HDA_INTSTS regs */
#घोषणा SOF_HDA_INTSTS_GIS		BIT(31)

#घोषणा SOF_HDA_MAX_CAPS		10
#घोषणा SOF_HDA_CAP_ID_OFF		16
#घोषणा SOF_HDA_CAP_ID_MASK		GENMASK(SOF_HDA_CAP_ID_OFF + 11,\
						SOF_HDA_CAP_ID_OFF)
#घोषणा SOF_HDA_CAP_NEXT_MASK		0xFFFF

#घोषणा SOF_HDA_GTS_CAP_ID			0x1
#घोषणा SOF_HDA_ML_CAP_ID			0x2

#घोषणा SOF_HDA_PP_CAP_ID		0x3
#घोषणा SOF_HDA_REG_PP_PPCH		0x10
#घोषणा SOF_HDA_REG_PP_PPCTL		0x04
#घोषणा SOF_HDA_REG_PP_PPSTS		0x08
#घोषणा SOF_HDA_PPCTL_PIE		BIT(31)
#घोषणा SOF_HDA_PPCTL_GPROCEN		BIT(30)

/*Venकरोr Specअगरic Registers*/
#घोषणा SOF_HDA_VS_D0I3C		0x104A

/* D0I3C Register fields */
#घोषणा SOF_HDA_VS_D0I3C_CIP		BIT(0) /* Command-In-Progress */
#घोषणा SOF_HDA_VS_D0I3C_I3		BIT(2) /* D0i3 enable bit */

/* DPIB entry size: 8 Bytes = 2 DWords */
#घोषणा SOF_HDA_DPIB_ENTRY_SIZE	0x8

#घोषणा SOF_HDA_SPIB_CAP_ID		0x4
#घोषणा SOF_HDA_DRSM_CAP_ID		0x5

#घोषणा SOF_HDA_SPIB_BASE		0x08
#घोषणा SOF_HDA_SPIB_INTERVAL		0x08
#घोषणा SOF_HDA_SPIB_SPIB		0x00
#घोषणा SOF_HDA_SPIB_MAXFIFO		0x04

#घोषणा SOF_HDA_PPHC_BASE		0x10
#घोषणा SOF_HDA_PPHC_INTERVAL		0x10

#घोषणा SOF_HDA_PPLC_BASE		0x10
#घोषणा SOF_HDA_PPLC_MULTI		0x10
#घोषणा SOF_HDA_PPLC_INTERVAL		0x10

#घोषणा SOF_HDA_DRSM_BASE		0x08
#घोषणा SOF_HDA_DRSM_INTERVAL		0x08

/* Descriptor error पूर्णांकerrupt */
#घोषणा SOF_HDA_CL_DMA_SD_INT_DESC_ERR		0x10

/* FIFO error पूर्णांकerrupt */
#घोषणा SOF_HDA_CL_DMA_SD_INT_FIFO_ERR		0x08

/* Buffer completion पूर्णांकerrupt */
#घोषणा SOF_HDA_CL_DMA_SD_INT_COMPLETE		0x04

#घोषणा SOF_HDA_CL_DMA_SD_INT_MASK \
	(SOF_HDA_CL_DMA_SD_INT_DESC_ERR | \
	SOF_HDA_CL_DMA_SD_INT_FIFO_ERR | \
	SOF_HDA_CL_DMA_SD_INT_COMPLETE)
#घोषणा SOF_HDA_SD_CTL_DMA_START		0x02 /* Stream DMA start bit */

/* Intel HD Audio Code Loader DMA Registers */
#घोषणा SOF_HDA_ADSP_LOADER_BASE		0x80
#घोषणा SOF_HDA_ADSP_DPLBASE			0x70
#घोषणा SOF_HDA_ADSP_DPUBASE			0x74
#घोषणा SOF_HDA_ADSP_DPLBASE_ENABLE		0x01

/* Stream Registers */
#घोषणा SOF_HDA_ADSP_REG_CL_SD_CTL		0x00
#घोषणा SOF_HDA_ADSP_REG_CL_SD_STS		0x03
#घोषणा SOF_HDA_ADSP_REG_CL_SD_LPIB		0x04
#घोषणा SOF_HDA_ADSP_REG_CL_SD_CBL		0x08
#घोषणा SOF_HDA_ADSP_REG_CL_SD_LVI		0x0C
#घोषणा SOF_HDA_ADSP_REG_CL_SD_FIFOW		0x0E
#घोषणा SOF_HDA_ADSP_REG_CL_SD_FIFOSIZE		0x10
#घोषणा SOF_HDA_ADSP_REG_CL_SD_FORMAT		0x12
#घोषणा SOF_HDA_ADSP_REG_CL_SD_FIFOL		0x14
#घोषणा SOF_HDA_ADSP_REG_CL_SD_BDLPL		0x18
#घोषणा SOF_HDA_ADSP_REG_CL_SD_BDLPU		0x1C
#घोषणा SOF_HDA_ADSP_SD_ENTRY_SIZE		0x20

/* CL: Software Position Based FIFO Capability Registers */
#घोषणा SOF_DSP_REG_CL_SPBFIFO \
	(SOF_HDA_ADSP_LOADER_BASE + 0x20)
#घोषणा SOF_HDA_ADSP_REG_CL_SPBFIFO_SPBFCH	0x0
#घोषणा SOF_HDA_ADSP_REG_CL_SPBFIFO_SPBFCCTL	0x4
#घोषणा SOF_HDA_ADSP_REG_CL_SPBFIFO_SPIB	0x8
#घोषणा SOF_HDA_ADSP_REG_CL_SPBFIFO_MAXFIFOS	0xc

/* Stream Number */
#घोषणा SOF_HDA_CL_SD_CTL_STREAM_TAG_SHIFT	20
#घोषणा SOF_HDA_CL_SD_CTL_STREAM_TAG_MASK \
	GENMASK(SOF_HDA_CL_SD_CTL_STREAM_TAG_SHIFT + 3,\
		SOF_HDA_CL_SD_CTL_STREAM_TAG_SHIFT)

#घोषणा HDA_DSP_HDA_BAR				0
#घोषणा HDA_DSP_PP_BAR				1
#घोषणा HDA_DSP_SPIB_BAR			2
#घोषणा HDA_DSP_DRSM_BAR			3
#घोषणा HDA_DSP_BAR				4

#घोषणा SRAM_WINDOW_OFFSET(x)			(0x80000 + (x) * 0x20000)

#घोषणा HDA_DSP_MBOX_OFFSET			SRAM_WINDOW_OFFSET(0)

#घोषणा HDA_DSP_PANIC_OFFSET(x) \
	(((x) & 0xFFFFFF) + HDA_DSP_MBOX_OFFSET)

/* SRAM winकरोw 0 FW "registers" */
#घोषणा HDA_DSP_SRAM_REG_ROM_STATUS		(HDA_DSP_MBOX_OFFSET + 0x0)
#घोषणा HDA_DSP_SRAM_REG_ROM_ERROR		(HDA_DSP_MBOX_OFFSET + 0x4)
/* FW and ROM share offset 4 */
#घोषणा HDA_DSP_SRAM_REG_FW_STATUS		(HDA_DSP_MBOX_OFFSET + 0x4)
#घोषणा HDA_DSP_SRAM_REG_FW_TRACEP		(HDA_DSP_MBOX_OFFSET + 0x8)
#घोषणा HDA_DSP_SRAM_REG_FW_END			(HDA_DSP_MBOX_OFFSET + 0xc)

#घोषणा HDA_DSP_MBOX_UPLINK_OFFSET		0x81000

#घोषणा HDA_DSP_STREAM_RESET_TIMEOUT		300
/*
 * Timeout in us, क्रम setting the stream RUN bit, during
 * start/stop the stream. The समयout expires अगर new RUN bit
 * value cannot be पढ़ो back within the specअगरied समय.
 */
#घोषणा HDA_DSP_STREAM_RUN_TIMEOUT		300

#घोषणा HDA_DSP_SPIB_ENABLE			1
#घोषणा HDA_DSP_SPIB_DISABLE			0

#घोषणा SOF_HDA_MAX_BUFFER_SIZE			(32 * PAGE_SIZE)

#घोषणा HDA_DSP_STACK_DUMP_SIZE			32

/* ROM  status/error values */
#घोषणा HDA_DSP_ROM_STS_MASK			GENMASK(23, 0)
#घोषणा HDA_DSP_ROM_INIT			0x1
#घोषणा HDA_DSP_ROM_FW_MANIFEST_LOADED		0x3
#घोषणा HDA_DSP_ROM_FW_FW_LOADED		0x4
#घोषणा HDA_DSP_ROM_FW_ENTERED			0x5
#घोषणा HDA_DSP_ROM_RFW_START			0xf
#घोषणा HDA_DSP_ROM_CSE_ERROR			40
#घोषणा HDA_DSP_ROM_CSE_WRONG_RESPONSE		41
#घोषणा HDA_DSP_ROM_IMR_TO_SMALL		42
#घोषणा HDA_DSP_ROM_BASE_FW_NOT_FOUND		43
#घोषणा HDA_DSP_ROM_CSE_VALIDATION_FAILED	44
#घोषणा HDA_DSP_ROM_IPC_FATAL_ERROR		45
#घोषणा HDA_DSP_ROM_L2_CACHE_ERROR		46
#घोषणा HDA_DSP_ROM_LOAD_OFFSET_TO_SMALL	47
#घोषणा HDA_DSP_ROM_API_PTR_INVALID		50
#घोषणा HDA_DSP_ROM_BASEFW_INCOMPAT		51
#घोषणा HDA_DSP_ROM_UNHANDLED_INTERRUPT		0xBEE00000
#घोषणा HDA_DSP_ROM_MEMORY_HOLE_ECC		0xECC00000
#घोषणा HDA_DSP_ROM_KERNEL_EXCEPTION		0xCAFE0000
#घोषणा HDA_DSP_ROM_USER_EXCEPTION		0xBEEF0000
#घोषणा HDA_DSP_ROM_UNEXPECTED_RESET		0xDECAF000
#घोषणा HDA_DSP_ROM_शून्य_FW_ENTRY		0x4c4c4e55
#घोषणा HDA_DSP_IPC_PURGE_FW			0x01004000

/* various समयout values */
#घोषणा HDA_DSP_PU_TIMEOUT		50
#घोषणा HDA_DSP_PD_TIMEOUT		50
#घोषणा HDA_DSP_RESET_TIMEOUT_US	50000
#घोषणा HDA_DSP_BASEFW_TIMEOUT_US       3000000
#घोषणा HDA_DSP_INIT_TIMEOUT_US	500000
#घोषणा HDA_DSP_CTRL_RESET_TIMEOUT		100
#घोषणा HDA_DSP_WAIT_TIMEOUT		500	/* 500 msec */
#घोषणा HDA_DSP_REG_POLL_INTERVAL_US		500	/* 0.5 msec */
#घोषणा HDA_DSP_REG_POLL_RETRY_COUNT		50

#घोषणा HDA_DSP_ADSPIC_IPC			1
#घोषणा HDA_DSP_ADSPIS_IPC			1

/* Intel HD Audio General DSP Registers */
#घोषणा HDA_DSP_GEN_BASE		0x0
#घोषणा HDA_DSP_REG_ADSPCS		(HDA_DSP_GEN_BASE + 0x04)
#घोषणा HDA_DSP_REG_ADSPIC		(HDA_DSP_GEN_BASE + 0x08)
#घोषणा HDA_DSP_REG_ADSPIS		(HDA_DSP_GEN_BASE + 0x0C)
#घोषणा HDA_DSP_REG_ADSPIC2		(HDA_DSP_GEN_BASE + 0x10)
#घोषणा HDA_DSP_REG_ADSPIS2		(HDA_DSP_GEN_BASE + 0x14)

#घोषणा HDA_DSP_REG_ADSPIS2_SNDW	BIT(5)
#घोषणा HDA_DSP_REG_SNDW_WAKE_STS      0x2C192

/* Intel HD Audio Inter-Processor Communication Registers */
#घोषणा HDA_DSP_IPC_BASE		0x40
#घोषणा HDA_DSP_REG_HIPCT		(HDA_DSP_IPC_BASE + 0x00)
#घोषणा HDA_DSP_REG_HIPCTE		(HDA_DSP_IPC_BASE + 0x04)
#घोषणा HDA_DSP_REG_HIPCI		(HDA_DSP_IPC_BASE + 0x08)
#घोषणा HDA_DSP_REG_HIPCIE		(HDA_DSP_IPC_BASE + 0x0C)
#घोषणा HDA_DSP_REG_HIPCCTL		(HDA_DSP_IPC_BASE + 0x10)

/* Intel Venकरोr Specअगरic Registers */
#घोषणा HDA_VS_INTEL_EM2		0x1030
#घोषणा HDA_VS_INTEL_EM2_L1SEN		BIT(13)
#घोषणा HDA_VS_INTEL_LTRP_GB_MASK	0x3F

/*  HIPCI */
#घोषणा HDA_DSP_REG_HIPCI_BUSY		BIT(31)
#घोषणा HDA_DSP_REG_HIPCI_MSG_MASK	0x7FFFFFFF

/* HIPCIE */
#घोषणा HDA_DSP_REG_HIPCIE_DONE	BIT(30)
#घोषणा HDA_DSP_REG_HIPCIE_MSG_MASK	0x3FFFFFFF

/* HIPCCTL */
#घोषणा HDA_DSP_REG_HIPCCTL_DONE	BIT(1)
#घोषणा HDA_DSP_REG_HIPCCTL_BUSY	BIT(0)

/* HIPCT */
#घोषणा HDA_DSP_REG_HIPCT_BUSY		BIT(31)
#घोषणा HDA_DSP_REG_HIPCT_MSG_MASK	0x7FFFFFFF

/* HIPCTE */
#घोषणा HDA_DSP_REG_HIPCTE_MSG_MASK	0x3FFFFFFF

#घोषणा HDA_DSP_ADSPIC_CL_DMA		0x2
#घोषणा HDA_DSP_ADSPIS_CL_DMA		0x2

/* Delay beक्रमe scheduling D0i3 entry */
#घोषणा BXT_D0I3_DELAY 5000

#घोषणा FW_CL_STREAM_NUMBER		0x1
#घोषणा HDA_FW_BOOT_ATTEMPTS	3

/* ADSPCS - Audio DSP Control & Status */

/*
 * Core Reset - निश्चितed high
 * CRST Mask क्रम a given core mask pattern, cm
 */
#घोषणा HDA_DSP_ADSPCS_CRST_SHIFT	0
#घोषणा HDA_DSP_ADSPCS_CRST_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CRST_SHIFT)

/*
 * Core run/stall - when set to '1' core is stalled
 * CSTALL Mask क्रम a given core mask pattern, cm
 */
#घोषणा HDA_DSP_ADSPCS_CSTALL_SHIFT	8
#घोषणा HDA_DSP_ADSPCS_CSTALL_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CSTALL_SHIFT)

/*
 * Set Power Active - when set to '1' turn cores on
 * SPA Mask क्रम a given core mask pattern, cm
 */
#घोषणा HDA_DSP_ADSPCS_SPA_SHIFT	16
#घोषणा HDA_DSP_ADSPCS_SPA_MASK(cm)	((cm) << HDA_DSP_ADSPCS_SPA_SHIFT)

/*
 * Current Power Active - घातer status of cores, set by hardware
 * CPA Mask क्रम a given core mask pattern, cm
 */
#घोषणा HDA_DSP_ADSPCS_CPA_SHIFT	24
#घोषणा HDA_DSP_ADSPCS_CPA_MASK(cm)	((cm) << HDA_DSP_ADSPCS_CPA_SHIFT)

/*
 * Mask क्रम a given number of cores
 * nc = number of supported cores
 */
#घोषणा SOF_DSP_CORES_MASK(nc)	GENMASK(((nc) - 1), 0)

/* Intel HD Audio Inter-Processor Communication Registers क्रम Cannonlake*/
#घोषणा CNL_DSP_IPC_BASE		0xc0
#घोषणा CNL_DSP_REG_HIPCTDR		(CNL_DSP_IPC_BASE + 0x00)
#घोषणा CNL_DSP_REG_HIPCTDA		(CNL_DSP_IPC_BASE + 0x04)
#घोषणा CNL_DSP_REG_HIPCTDD		(CNL_DSP_IPC_BASE + 0x08)
#घोषणा CNL_DSP_REG_HIPCIDR		(CNL_DSP_IPC_BASE + 0x10)
#घोषणा CNL_DSP_REG_HIPCIDA		(CNL_DSP_IPC_BASE + 0x14)
#घोषणा CNL_DSP_REG_HIPCIDD		(CNL_DSP_IPC_BASE + 0x18)
#घोषणा CNL_DSP_REG_HIPCCTL		(CNL_DSP_IPC_BASE + 0x28)

/*  HIPCI */
#घोषणा CNL_DSP_REG_HIPCIDR_BUSY		BIT(31)
#घोषणा CNL_DSP_REG_HIPCIDR_MSG_MASK	0x7FFFFFFF

/* HIPCIE */
#घोषणा CNL_DSP_REG_HIPCIDA_DONE	BIT(31)
#घोषणा CNL_DSP_REG_HIPCIDA_MSG_MASK	0x7FFFFFFF

/* HIPCCTL */
#घोषणा CNL_DSP_REG_HIPCCTL_DONE	BIT(1)
#घोषणा CNL_DSP_REG_HIPCCTL_BUSY	BIT(0)

/* HIPCT */
#घोषणा CNL_DSP_REG_HIPCTDR_BUSY		BIT(31)
#घोषणा CNL_DSP_REG_HIPCTDR_MSG_MASK	0x7FFFFFFF

/* HIPCTDA */
#घोषणा CNL_DSP_REG_HIPCTDA_DONE	BIT(31)
#घोषणा CNL_DSP_REG_HIPCTDA_MSG_MASK	0x7FFFFFFF

/* HIPCTDD */
#घोषणा CNL_DSP_REG_HIPCTDD_MSG_MASK	0x7FFFFFFF

/* BDL */
#घोषणा HDA_DSP_BDL_SIZE			4096
#घोषणा HDA_DSP_MAX_BDL_ENTRIES			\
	(HDA_DSP_BDL_SIZE / माप(काष्ठा sof_पूर्णांकel_dsp_bdl))

/* Number of DAIs */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_PROBES)
#घोषणा SOF_SKL_NUM_DAIS		16
#अन्यथा
#घोषणा SOF_SKL_NUM_DAIS		15
#पूर्ण_अगर

#अन्यथा
#घोषणा SOF_SKL_NUM_DAIS		8
#पूर्ण_अगर

/* Intel HD Audio SRAM Winकरोw 0*/
#घोषणा HDA_ADSP_SRAM0_BASE_SKL		0x8000

/* Firmware status winकरोw */
#घोषणा HDA_ADSP_FW_STATUS_SKL		HDA_ADSP_SRAM0_BASE_SKL
#घोषणा HDA_ADSP_ERROR_CODE_SKL		(HDA_ADSP_FW_STATUS_SKL + 0x4)

/* Host Device Memory Space */
#घोषणा APL_SSP_BASE_OFFSET	0x2000
#घोषणा CNL_SSP_BASE_OFFSET	0x10000

/* Host Device Memory Size of a Single SSP */
#घोषणा SSP_DEV_MEM_SIZE	0x1000

/* SSP Count of the Platक्रमm */
#घोषणा APL_SSP_COUNT		6
#घोषणा CNL_SSP_COUNT		3
#घोषणा ICL_SSP_COUNT		6

/* SSP Registers */
#घोषणा SSP_SSC1_OFFSET		0x4
#घोषणा SSP_SET_SCLK_SLAVE	BIT(25)
#घोषणा SSP_SET_SFRM_SLAVE	BIT(24)
#घोषणा SSP_SET_SLAVE		(SSP_SET_SCLK_SLAVE | SSP_SET_SFRM_SLAVE)

#घोषणा HDA_IDISP_ADDR		2
#घोषणा HDA_IDISP_CODEC(x) ((x) & BIT(HDA_IDISP_ADDR))

काष्ठा sof_पूर्णांकel_dsp_bdl अणु
	__le32 addr_l;
	__le32 addr_h;
	__le32 size;
	__le32 ioc;
पूर्ण __attribute((packed));

#घोषणा SOF_HDA_PLAYBACK_STREAMS	16
#घोषणा SOF_HDA_CAPTURE_STREAMS		16
#घोषणा SOF_HDA_PLAYBACK		0
#घोषणा SOF_HDA_CAPTURE			1

/* stream flags */
#घोषणा SOF_HDA_STREAM_DMI_L1_COMPATIBLE	1

/*
 * Time in ms क्रम opportunistic D0I3 entry delay.
 * This has been deliberately chosen to be दीर्घ to aव्योम race conditions.
 * Could be optimized in future.
 */
#घोषणा SOF_HDA_D0I3_WORK_DELAY_MS	5000

/* HDA DSP D0 substate */
क्रमागत sof_hda_D0_substate अणु
	SOF_HDA_DSP_PM_D0I0,	/* शेष D0 substate */
	SOF_HDA_DSP_PM_D0I3,	/* low घातer D0 substate */
पूर्ण;

/* represents DSP HDA controller frontend - i.e. host facing control */
काष्ठा sof_पूर्णांकel_hda_dev अणु
	पूर्णांक boot_iteration;

	काष्ठा hda_bus hbus;

	/* hw config */
	स्थिर काष्ठा sof_पूर्णांकel_dsp_desc *desc;

	/* trace */
	काष्ठा hdac_ext_stream *dtrace_stream;

	/* अगर position update IPC needed */
	u32 no_ipc_position;

	/* the maximum number of streams (playback + capture) supported */
	u32 stream_max;

	/* PM related */
	bool l1_support_changed;/* during suspend, is L1SEN changed or not */

	/* DMIC device */
	काष्ठा platक्रमm_device *dmic_dev;

	/* delayed work to enter D0I3 opportunistically */
	काष्ठा delayed_work d0i3_work;

	/* ACPI inक्रमmation stored between scan and probe steps */
	काष्ठा sdw_पूर्णांकel_acpi_info info;

	/* sdw context allocated by SoundWire driver */
	काष्ठा sdw_पूर्णांकel_ctx *sdw;

	/* FW घड़ी config, 0:HPRO, 1:LPRO */
	bool clk_config_lpro;
पूर्ण;

अटल अंतरभूत काष्ठा hdac_bus *sof_to_bus(काष्ठा snd_sof_dev *s)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = s->pdata->hw_pdata;

	वापस &hda->hbus.core;
पूर्ण

अटल अंतरभूत काष्ठा hda_bus *sof_to_hbus(काष्ठा snd_sof_dev *s)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = s->pdata->hw_pdata;

	वापस &hda->hbus;
पूर्ण

काष्ठा sof_पूर्णांकel_hda_stream अणु
	काष्ठा snd_sof_dev *sdev;
	काष्ठा hdac_ext_stream hda_stream;
	काष्ठा sof_पूर्णांकel_stream stream;
	पूर्णांक host_reserved; /* reserve host DMA channel */
	u32 flags;
पूर्ण;

#घोषणा hstream_to_sof_hda_stream(hstream) \
	container_of(hstream, काष्ठा sof_पूर्णांकel_hda_stream, hda_stream)

#घोषणा bus_to_sof_hda(bus) \
	container_of(bus, काष्ठा sof_पूर्णांकel_hda_dev, hbus.core)

#घोषणा SOF_STREAM_SD_OFFSET(s) \
	(SOF_HDA_ADSP_SD_ENTRY_SIZE * ((s)->index) \
	 + SOF_HDA_ADSP_LOADER_BASE)

/*
 * DSP Core services.
 */
पूर्णांक hda_dsp_probe(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_हटाओ(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_core_reset_enter(काष्ठा snd_sof_dev *sdev,
			     अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_reset_leave(काष्ठा snd_sof_dev *sdev,
			     अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_stall_reset(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_run(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_घातer_up(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_enable_core(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_घातer_करोwn(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);
bool hda_dsp_core_is_enabled(काष्ठा snd_sof_dev *sdev,
			     अचिन्हित पूर्णांक core_mask);
पूर्णांक hda_dsp_core_reset_घातer_करोwn(काष्ठा snd_sof_dev *sdev,
				  अचिन्हित पूर्णांक core_mask);
व्योम hda_dsp_ipc_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev);
व्योम hda_dsp_ipc_पूर्णांक_disable(काष्ठा snd_sof_dev *sdev);

पूर्णांक hda_dsp_set_घातer_state(काष्ठा snd_sof_dev *sdev,
			    स्थिर काष्ठा sof_dsp_घातer_state *target_state);

पूर्णांक hda_dsp_suspend(काष्ठा snd_sof_dev *sdev, u32 target_state);
पूर्णांक hda_dsp_resume(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_runसमय_suspend(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_runसमय_resume(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_runसमय_idle(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_shutकरोwn(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_set_hw_params_upon_resume(काष्ठा snd_sof_dev *sdev);
व्योम hda_dsp_dump(काष्ठा snd_sof_dev *sdev, u32 flags);
व्योम hda_ipc_dump(काष्ठा snd_sof_dev *sdev);
व्योम hda_ipc_irq_dump(काष्ठा snd_sof_dev *sdev);
व्योम hda_dsp_d0i3_work(काष्ठा work_काष्ठा *work);

/*
 * DSP PCM Operations.
 */
u32 hda_dsp_get_mult_भाग(काष्ठा snd_sof_dev *sdev, पूर्णांक rate);
u32 hda_dsp_get_bits(काष्ठा snd_sof_dev *sdev, पूर्णांक sample_bits);
पूर्णांक hda_dsp_pcm_खोलो(काष्ठा snd_sof_dev *sdev,
		     काष्ठा snd_pcm_substream *substream);
पूर्णांक hda_dsp_pcm_बंद(काष्ठा snd_sof_dev *sdev,
		      काष्ठा snd_pcm_substream *substream);
पूर्णांक hda_dsp_pcm_hw_params(काष्ठा snd_sof_dev *sdev,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params,
			  काष्ठा sof_ipc_stream_params *ipc_params);
पूर्णांक hda_dsp_stream_hw_मुक्त(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_pcm_substream *substream);
पूर्णांक hda_dsp_pcm_trigger(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
snd_pcm_uframes_t hda_dsp_pcm_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
				      काष्ठा snd_pcm_substream *substream);

/*
 * DSP Stream Operations.
 */

पूर्णांक hda_dsp_stream_init(काष्ठा snd_sof_dev *sdev);
व्योम hda_dsp_stream_मुक्त(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_stream_hw_params(काष्ठा snd_sof_dev *sdev,
			     काष्ठा hdac_ext_stream *stream,
			     काष्ठा snd_dma_buffer *dmab,
			     काष्ठा snd_pcm_hw_params *params);
पूर्णांक hda_dsp_iccmax_stream_hw_params(काष्ठा snd_sof_dev *sdev, काष्ठा hdac_ext_stream *stream,
				    काष्ठा snd_dma_buffer *dmab,
				    काष्ठा snd_pcm_hw_params *params);
पूर्णांक hda_dsp_stream_trigger(काष्ठा snd_sof_dev *sdev,
			   काष्ठा hdac_ext_stream *stream, पूर्णांक cmd);
irqवापस_t hda_dsp_stream_thपढ़ोed_handler(पूर्णांक irq, व्योम *context);
पूर्णांक hda_dsp_stream_setup_bdl(काष्ठा snd_sof_dev *sdev,
			     काष्ठा snd_dma_buffer *dmab,
			     काष्ठा hdac_stream *stream);
bool hda_dsp_check_ipc_irq(काष्ठा snd_sof_dev *sdev);
bool hda_dsp_check_stream_irq(काष्ठा snd_sof_dev *sdev);

काष्ठा hdac_ext_stream *
	hda_dsp_stream_get(काष्ठा snd_sof_dev *sdev, पूर्णांक direction, u32 flags);
पूर्णांक hda_dsp_stream_put(काष्ठा snd_sof_dev *sdev, पूर्णांक direction, पूर्णांक stream_tag);
पूर्णांक hda_dsp_stream_spib_config(काष्ठा snd_sof_dev *sdev,
			       काष्ठा hdac_ext_stream *stream,
			       पूर्णांक enable, u32 size);

व्योम hda_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
		      काष्ठा snd_pcm_substream *substream,
		      व्योम *p, माप_प्रकार sz);
पूर्णांक hda_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
		       काष्ठा snd_pcm_substream *substream,
		       स्थिर काष्ठा sof_ipc_pcm_params_reply *reply);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_PROBES)
/*
 * Probe Compress Operations.
 */
पूर्णांक hda_probe_compr_assign(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_compr_stream *cstream,
			   काष्ठा snd_soc_dai *dai);
पूर्णांक hda_probe_compr_मुक्त(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_compr_stream *cstream,
			 काष्ठा snd_soc_dai *dai);
पूर्णांक hda_probe_compr_set_params(काष्ठा snd_sof_dev *sdev,
			       काष्ठा snd_compr_stream *cstream,
			       काष्ठा snd_compr_params *params,
			       काष्ठा snd_soc_dai *dai);
पूर्णांक hda_probe_compr_trigger(काष्ठा snd_sof_dev *sdev,
			    काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai);
पूर्णांक hda_probe_compr_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
			    काष्ठा snd_compr_stream *cstream,
			    काष्ठा snd_compr_tstamp *tstamp,
			    काष्ठा snd_soc_dai *dai);
#पूर्ण_अगर

/*
 * DSP IPC Operations.
 */
पूर्णांक hda_dsp_ipc_send_msg(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_sof_ipc_msg *msg);
व्योम hda_dsp_ipc_get_reply(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_ipc_get_mailbox_offset(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_ipc_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id);

irqवापस_t hda_dsp_ipc_irq_thपढ़ो(पूर्णांक irq, व्योम *context);
पूर्णांक hda_dsp_ipc_cmd_करोne(काष्ठा snd_sof_dev *sdev, पूर्णांक dir);

/*
 * DSP Code loader.
 */
पूर्णांक hda_dsp_cl_boot_firmware(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_cl_boot_firmware_iccmax(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_cl_boot_firmware_iccmax_icl(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_cl_boot_firmware_skl(काष्ठा snd_sof_dev *sdev);

/* pre and post fw run ops */
पूर्णांक hda_dsp_pre_fw_run(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_post_fw_run(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_post_fw_run_icl(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_core_stall_icl(काष्ठा snd_sof_dev *sdev, अचिन्हित पूर्णांक core_mask);

/* parse platक्रमm specअगरic ext manअगरest ops */
पूर्णांक hda_dsp_ext_man_get_cavs_config_data(काष्ठा snd_sof_dev *sdev,
					 स्थिर काष्ठा sof_ext_man_elem_header *hdr);

/*
 * HDA Controller Operations.
 */
पूर्णांक hda_dsp_ctrl_get_caps(काष्ठा snd_sof_dev *sdev);
व्योम hda_dsp_ctrl_ppcap_enable(काष्ठा snd_sof_dev *sdev, bool enable);
व्योम hda_dsp_ctrl_ppcap_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev, bool enable);
पूर्णांक hda_dsp_ctrl_link_reset(काष्ठा snd_sof_dev *sdev, bool reset);
व्योम hda_dsp_ctrl_misc_घड़ी_gating(काष्ठा snd_sof_dev *sdev, bool enable);
पूर्णांक hda_dsp_ctrl_घड़ी_घातer_gating(काष्ठा snd_sof_dev *sdev, bool enable);
पूर्णांक hda_dsp_ctrl_init_chip(काष्ठा snd_sof_dev *sdev, bool full_reset);
व्योम hda_dsp_ctrl_stop_chip(काष्ठा snd_sof_dev *sdev);
/*
 * HDA bus operations.
 */
व्योम sof_hda_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev);

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
/*
 * HDA Codec operations.
 */
व्योम hda_codec_probe_bus(काष्ठा snd_sof_dev *sdev,
			 bool hda_codec_use_common_hdmi);
व्योम hda_codec_jack_wake_enable(काष्ठा snd_sof_dev *sdev, bool enable);
व्योम hda_codec_jack_check(काष्ठा snd_sof_dev *sdev);

#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_HDA */

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA) && \
	(IS_ENABLED(CONFIG_SND_HDA_CODEC_HDMI) || \
	 IS_ENABLED(CONFIG_SND_SOC_HDAC_HDMI))

व्योम hda_codec_i915_display_घातer(काष्ठा snd_sof_dev *sdev, bool enable);
पूर्णांक hda_codec_i915_init(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_codec_i915_निकास(काष्ठा snd_sof_dev *sdev);

#अन्यथा

अटल अंतरभूत व्योम hda_codec_i915_display_घातer(काष्ठा snd_sof_dev *sdev,
						bool enable) अणु पूर्ण
अटल अंतरभूत पूर्णांक hda_codec_i915_init(काष्ठा snd_sof_dev *sdev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक hda_codec_i915_निकास(काष्ठा snd_sof_dev *sdev) अणु वापस 0; पूर्ण

#पूर्ण_अगर

/*
 * Trace Control.
 */
पूर्णांक hda_dsp_trace_init(काष्ठा snd_sof_dev *sdev, u32 *stream_tag);
पूर्णांक hda_dsp_trace_release(काष्ठा snd_sof_dev *sdev);
पूर्णांक hda_dsp_trace_trigger(काष्ठा snd_sof_dev *sdev, पूर्णांक cmd);

/*
 * SoundWire support
 */
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_INTEL_SOUNDWIRE)

पूर्णांक hda_sdw_startup(काष्ठा snd_sof_dev *sdev);
व्योम hda_sdw_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev, bool enable);
व्योम hda_sdw_process_wakeen(काष्ठा snd_sof_dev *sdev);

#अन्यथा

अटल अंतरभूत पूर्णांक hda_sdw_acpi_scan(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hda_sdw_probe(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hda_sdw_startup(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hda_sdw_निकास(काष्ठा snd_sof_dev *sdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hda_sdw_पूर्णांक_enable(काष्ठा snd_sof_dev *sdev, bool enable)
अणु
पूर्ण

अटल अंतरभूत bool hda_dsp_check_sdw_irq(काष्ठा snd_sof_dev *sdev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत irqवापस_t hda_dsp_sdw_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत bool hda_sdw_check_wakeen_irq(काष्ठा snd_sof_dev *sdev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम hda_sdw_process_wakeen(काष्ठा snd_sof_dev *sdev)
अणु
पूर्ण
#पूर्ण_अगर

/* common dai driver */
बाह्य काष्ठा snd_soc_dai_driver skl_dai[];

/*
 * Platक्रमm Specअगरic HW असलtraction Ops.
 */
बाह्य स्थिर काष्ठा snd_sof_dsp_ops sof_apl_ops;
बाह्य स्थिर काष्ठा snd_sof_dsp_ops sof_cnl_ops;
बाह्य स्थिर काष्ठा snd_sof_dsp_ops sof_tgl_ops;
बाह्य स्थिर काष्ठा snd_sof_dsp_ops sof_icl_ops;

बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc apl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc cnl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc skl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc icl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tgl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tglh_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc ehl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc jsl_chip_info;
बाह्य स्थिर काष्ठा sof_पूर्णांकel_dsp_desc adls_chip_info;

/* machine driver select */
व्योम hda_machine_select(काष्ठा snd_sof_dev *sdev);
व्योम hda_set_mach_params(स्थिर काष्ठा snd_soc_acpi_mach *mach,
			 काष्ठा snd_sof_dev *sdev);

/* PCI driver selection and probe */
पूर्णांक hda_pci_पूर्णांकel_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id);

#पूर्ण_अगर
