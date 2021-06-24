<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * STM32 ALSA SoC Digital Audio Interface (SAI) driver.
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author(s): Olivier Moysan <olivier.moysan@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/bitfield.h>

/******************** SAI Register Map **************************************/

/* Global configuration रेजिस्टर */
#घोषणा STM_SAI_GCR		0x00

/* Sub-block A&B रेजिस्टरs offsets, relative to A&B sub-block addresses */
#घोषणा STM_SAI_CR1_REGX	0x00	/* A offset: 0x04. B offset: 0x24 */
#घोषणा STM_SAI_CR2_REGX	0x04
#घोषणा STM_SAI_FRCR_REGX	0x08
#घोषणा STM_SAI_SLOTR_REGX	0x0C
#घोषणा STM_SAI_IMR_REGX	0x10
#घोषणा STM_SAI_SR_REGX		0x14
#घोषणा STM_SAI_CLRFR_REGX	0x18
#घोषणा STM_SAI_DR_REGX		0x1C

/* Sub-block A रेजिस्टरs, relative to sub-block A address */
#घोषणा STM_SAI_PDMCR_REGX	0x40
#घोषणा STM_SAI_PDMLY_REGX	0x44

/* Hardware configuration रेजिस्टरs */
#घोषणा STM_SAI_HWCFGR		0x3F0
#घोषणा STM_SAI_VERR		0x3F4
#घोषणा STM_SAI_IDR		0x3F8
#घोषणा STM_SAI_SIDR		0x3FC

/******************** Bit definition क्रम SAI_GCR रेजिस्टर *******************/
#घोषणा SAI_GCR_SYNCIN_SHIFT	0
#घोषणा SAI_GCR_SYNCIN_WDTH	2
#घोषणा SAI_GCR_SYNCIN_MASK	GENMASK(1, SAI_GCR_SYNCIN_SHIFT)
#घोषणा SAI_GCR_SYNCIN_MAX	FIELD_GET(SAI_GCR_SYNCIN_MASK,\
				SAI_GCR_SYNCIN_MASK)

#घोषणा SAI_GCR_SYNCOUT_SHIFT	4
#घोषणा SAI_GCR_SYNCOUT_MASK	GENMASK(5, SAI_GCR_SYNCOUT_SHIFT)

/******************* Bit definition क्रम SAI_XCR1 रेजिस्टर *******************/
#घोषणा SAI_XCR1_RX_TX_SHIFT	0
#घोषणा SAI_XCR1_RX_TX		BIT(SAI_XCR1_RX_TX_SHIFT)
#घोषणा SAI_XCR1_SLAVE_SHIFT	1
#घोषणा SAI_XCR1_SLAVE		BIT(SAI_XCR1_SLAVE_SHIFT)

#घोषणा SAI_XCR1_PRTCFG_SHIFT	2
#घोषणा SAI_XCR1_PRTCFG_MASK	GENMASK(3, SAI_XCR1_PRTCFG_SHIFT)
#घोषणा SAI_XCR1_PRTCFG_SET(x)	((x) << SAI_XCR1_PRTCFG_SHIFT)

#घोषणा SAI_XCR1_DS_SHIFT	5
#घोषणा SAI_XCR1_DS_MASK	GENMASK(7, SAI_XCR1_DS_SHIFT)
#घोषणा SAI_XCR1_DS_SET(x)	((x) << SAI_XCR1_DS_SHIFT)

#घोषणा SAI_XCR1_LSBFIRST_SHIFT	8
#घोषणा SAI_XCR1_LSBFIRST	BIT(SAI_XCR1_LSBFIRST_SHIFT)
#घोषणा SAI_XCR1_CKSTR_SHIFT	9
#घोषणा SAI_XCR1_CKSTR		BIT(SAI_XCR1_CKSTR_SHIFT)

#घोषणा SAI_XCR1_SYNCEN_SHIFT	10
#घोषणा SAI_XCR1_SYNCEN_MASK	GENMASK(11, SAI_XCR1_SYNCEN_SHIFT)
#घोषणा SAI_XCR1_SYNCEN_SET(x)	((x) << SAI_XCR1_SYNCEN_SHIFT)

#घोषणा SAI_XCR1_MONO_SHIFT	12
#घोषणा SAI_XCR1_MONO		BIT(SAI_XCR1_MONO_SHIFT)
#घोषणा SAI_XCR1_OUTDRIV_SHIFT	13
#घोषणा SAI_XCR1_OUTDRIV	BIT(SAI_XCR1_OUTDRIV_SHIFT)
#घोषणा SAI_XCR1_SAIEN_SHIFT	16
#घोषणा SAI_XCR1_SAIEN		BIT(SAI_XCR1_SAIEN_SHIFT)
#घोषणा SAI_XCR1_DMAEN_SHIFT	17
#घोषणा SAI_XCR1_DMAEN		BIT(SAI_XCR1_DMAEN_SHIFT)
#घोषणा SAI_XCR1_NODIV_SHIFT	19
#घोषणा SAI_XCR1_NODIV		BIT(SAI_XCR1_NODIV_SHIFT)

#घोषणा SAI_XCR1_MCKDIV_SHIFT	20
#घोषणा SAI_XCR1_MCKDIV_WIDTH(x)	(((x) == STM_SAI_STM32F4) ? 4 : 6)
#घोषणा SAI_XCR1_MCKDIV_MASK(x) GENMASK((SAI_XCR1_MCKDIV_SHIFT + (x) - 1),\
				SAI_XCR1_MCKDIV_SHIFT)
#घोषणा SAI_XCR1_MCKDIV_SET(x)	((x) << SAI_XCR1_MCKDIV_SHIFT)
#घोषणा SAI_XCR1_MCKDIV_MAX(x)	((1 << SAI_XCR1_MCKDIV_WIDTH(x)) - 1)

#घोषणा SAI_XCR1_OSR_SHIFT	26
#घोषणा SAI_XCR1_OSR		BIT(SAI_XCR1_OSR_SHIFT)

#घोषणा SAI_XCR1_MCKEN_SHIFT	27
#घोषणा SAI_XCR1_MCKEN		BIT(SAI_XCR1_MCKEN_SHIFT)

/******************* Bit definition क्रम SAI_XCR2 रेजिस्टर *******************/
#घोषणा SAI_XCR2_FTH_SHIFT	0
#घोषणा SAI_XCR2_FTH_MASK	GENMASK(2, SAI_XCR2_FTH_SHIFT)
#घोषणा SAI_XCR2_FTH_SET(x)	((x) << SAI_XCR2_FTH_SHIFT)

#घोषणा SAI_XCR2_FFLUSH_SHIFT	3
#घोषणा SAI_XCR2_FFLUSH		BIT(SAI_XCR2_FFLUSH_SHIFT)
#घोषणा SAI_XCR2_TRIS_SHIFT	4
#घोषणा SAI_XCR2_TRIS		BIT(SAI_XCR2_TRIS_SHIFT)
#घोषणा SAI_XCR2_MUTE_SHIFT	5
#घोषणा SAI_XCR2_MUTE		BIT(SAI_XCR2_MUTE_SHIFT)
#घोषणा SAI_XCR2_MUTEVAL_SHIFT	6
#घोषणा SAI_XCR2_MUTEVAL	BIT(SAI_XCR2_MUTEVAL_SHIFT)

#घोषणा SAI_XCR2_MUTECNT_SHIFT	7
#घोषणा SAI_XCR2_MUTECNT_MASK	GENMASK(12, SAI_XCR2_MUTECNT_SHIFT)
#घोषणा SAI_XCR2_MUTECNT_SET(x)	((x) << SAI_XCR2_MUTECNT_SHIFT)

#घोषणा SAI_XCR2_CPL_SHIFT	13
#घोषणा SAI_XCR2_CPL		BIT(SAI_XCR2_CPL_SHIFT)

#घोषणा SAI_XCR2_COMP_SHIFT	14
#घोषणा SAI_XCR2_COMP_MASK	GENMASK(15, SAI_XCR2_COMP_SHIFT)
#घोषणा SAI_XCR2_COMP_SET(x)	((x) << SAI_XCR2_COMP_SHIFT)

/****************** Bit definition क्रम SAI_XFRCR रेजिस्टर *******************/
#घोषणा SAI_XFRCR_FRL_SHIFT	0
#घोषणा SAI_XFRCR_FRL_MASK	GENMASK(7, SAI_XFRCR_FRL_SHIFT)
#घोषणा SAI_XFRCR_FRL_SET(x)	((x) << SAI_XFRCR_FRL_SHIFT)

#घोषणा SAI_XFRCR_FSALL_SHIFT	8
#घोषणा SAI_XFRCR_FSALL_MASK	GENMASK(14, SAI_XFRCR_FSALL_SHIFT)
#घोषणा SAI_XFRCR_FSALL_SET(x)	((x) << SAI_XFRCR_FSALL_SHIFT)

#घोषणा SAI_XFRCR_FSDEF_SHIFT	16
#घोषणा SAI_XFRCR_FSDEF		BIT(SAI_XFRCR_FSDEF_SHIFT)
#घोषणा SAI_XFRCR_FSPOL_SHIFT	17
#घोषणा SAI_XFRCR_FSPOL		BIT(SAI_XFRCR_FSPOL_SHIFT)
#घोषणा SAI_XFRCR_FSOFF_SHIFT	18
#घोषणा SAI_XFRCR_FSOFF		BIT(SAI_XFRCR_FSOFF_SHIFT)

/****************** Bit definition क्रम SAI_XSLOTR रेजिस्टर ******************/
#घोषणा SAI_XSLOTR_FBOFF_SHIFT	0
#घोषणा SAI_XSLOTR_FBOFF_MASK	GENMASK(4, SAI_XSLOTR_FBOFF_SHIFT)
#घोषणा SAI_XSLOTR_FBOFF_SET(x)	((x) << SAI_XSLOTR_FBOFF_SHIFT)

#घोषणा SAI_XSLOTR_SLOTSZ_SHIFT	6
#घोषणा SAI_XSLOTR_SLOTSZ_MASK	GENMASK(7, SAI_XSLOTR_SLOTSZ_SHIFT)
#घोषणा SAI_XSLOTR_SLOTSZ_SET(x)	((x) << SAI_XSLOTR_SLOTSZ_SHIFT)

#घोषणा SAI_XSLOTR_NBSLOT_SHIFT 8
#घोषणा SAI_XSLOTR_NBSLOT_MASK	GENMASK(11, SAI_XSLOTR_NBSLOT_SHIFT)
#घोषणा SAI_XSLOTR_NBSLOT_SET(x) ((x) << SAI_XSLOTR_NBSLOT_SHIFT)

#घोषणा SAI_XSLOTR_SLOTEN_SHIFT	16
#घोषणा SAI_XSLOTR_SLOTEN_WIDTH	16
#घोषणा SAI_XSLOTR_SLOTEN_MASK	GENMASK(31, SAI_XSLOTR_SLOTEN_SHIFT)
#घोषणा SAI_XSLOTR_SLOTEN_SET(x) ((x) << SAI_XSLOTR_SLOTEN_SHIFT)

/******************* Bit definition क्रम SAI_XIMR रेजिस्टर *******************/
#घोषणा SAI_XIMR_OVRUDRIE	BIT(0)
#घोषणा SAI_XIMR_MUTEDETIE	BIT(1)
#घोषणा SAI_XIMR_WCKCFGIE	BIT(2)
#घोषणा SAI_XIMR_FREQIE		BIT(3)
#घोषणा SAI_XIMR_CNRDYIE	BIT(4)
#घोषणा SAI_XIMR_AFSDETIE	BIT(5)
#घोषणा SAI_XIMR_LFSDETIE	BIT(6)

#घोषणा SAI_XIMR_SHIFT	0
#घोषणा SAI_XIMR_MASK		GENMASK(6, SAI_XIMR_SHIFT)

/******************** Bit definition क्रम SAI_XSR रेजिस्टर *******************/
#घोषणा SAI_XSR_OVRUDR		BIT(0)
#घोषणा SAI_XSR_MUTEDET		BIT(1)
#घोषणा SAI_XSR_WCKCFG		BIT(2)
#घोषणा SAI_XSR_FREQ		BIT(3)
#घोषणा SAI_XSR_CNRDY		BIT(4)
#घोषणा SAI_XSR_AFSDET		BIT(5)
#घोषणा SAI_XSR_LFSDET		BIT(6)

#घोषणा SAI_XSR_SHIFT	0
#घोषणा SAI_XSR_MASK		GENMASK(6, SAI_XSR_SHIFT)

/****************** Bit definition क्रम SAI_XCLRFR रेजिस्टर ******************/
#घोषणा SAI_XCLRFR_COVRUDR	BIT(0)
#घोषणा SAI_XCLRFR_CMUTEDET	BIT(1)
#घोषणा SAI_XCLRFR_CWCKCFG	BIT(2)
#घोषणा SAI_XCLRFR_CFREQ	BIT(3)
#घोषणा SAI_XCLRFR_CCNRDY	BIT(4)
#घोषणा SAI_XCLRFR_CAFSDET	BIT(5)
#घोषणा SAI_XCLRFR_CLFSDET	BIT(6)

#घोषणा SAI_XCLRFR_SHIFT	0
#घोषणा SAI_XCLRFR_MASK		GENMASK(6, SAI_XCLRFR_SHIFT)

/****************** Bit definition क्रम SAI_PDMCR रेजिस्टर ******************/
#घोषणा SAI_PDMCR_PDMEN		BIT(0)

#घोषणा SAI_PDMCR_MICNBR_SHIFT	4
#घोषणा SAI_PDMCR_MICNBR_MASK	GENMASK(5, SAI_PDMCR_MICNBR_SHIFT)
#घोषणा SAI_PDMCR_MICNBR_SET(x)	((x) << SAI_PDMCR_MICNBR_SHIFT)

#घोषणा SAI_PDMCR_CKEN1		BIT(8)
#घोषणा SAI_PDMCR_CKEN2		BIT(9)
#घोषणा SAI_PDMCR_CKEN3		BIT(10)
#घोषणा SAI_PDMCR_CKEN4		BIT(11)

/****************** Bit definition क्रम (SAI_PDMDLY रेजिस्टर ****************/
#घोषणा SAI_PDMDLY_1L_SHIFT	0
#घोषणा SAI_PDMDLY_1L_MASK	GENMASK(2, SAI_PDMDLY_1L_SHIFT)
#घोषणा SAI_PDMDLY_1L_WIDTH	3

#घोषणा SAI_PDMDLY_1R_SHIFT	4
#घोषणा SAI_PDMDLY_1R_MASK	GENMASK(6, SAI_PDMDLY_1R_SHIFT)
#घोषणा SAI_PDMDLY_1R_WIDTH	3

#घोषणा SAI_PDMDLY_2L_SHIFT	8
#घोषणा SAI_PDMDLY_2L_MASK	GENMASK(10, SAI_PDMDLY_2L_SHIFT)
#घोषणा SAI_PDMDLY_2L_WIDTH	3

#घोषणा SAI_PDMDLY_2R_SHIFT	12
#घोषणा SAI_PDMDLY_2R_MASK	GENMASK(14, SAI_PDMDLY_2R_SHIFT)
#घोषणा SAI_PDMDLY_2R_WIDTH	3

#घोषणा SAI_PDMDLY_3L_SHIFT	16
#घोषणा SAI_PDMDLY_3L_MASK	GENMASK(18, SAI_PDMDLY_3L_SHIFT)
#घोषणा SAI_PDMDLY_3L_WIDTH	3

#घोषणा SAI_PDMDLY_3R_SHIFT	20
#घोषणा SAI_PDMDLY_3R_MASK	GENMASK(22, SAI_PDMDLY_3R_SHIFT)
#घोषणा SAI_PDMDLY_3R_WIDTH	3

#घोषणा SAI_PDMDLY_4L_SHIFT	24
#घोषणा SAI_PDMDLY_4L_MASK	GENMASK(26, SAI_PDMDLY_4L_SHIFT)
#घोषणा SAI_PDMDLY_4L_WIDTH	3

#घोषणा SAI_PDMDLY_4R_SHIFT	28
#घोषणा SAI_PDMDLY_4R_MASK	GENMASK(30, SAI_PDMDLY_4R_SHIFT)
#घोषणा SAI_PDMDLY_4R_WIDTH	3

/* Registers below apply to SAI version 2.1 and more */

/* Bit definition क्रम SAI_HWCFGR रेजिस्टर */
#घोषणा SAI_HWCFGR_FIFO_SIZE	GENMASK(7, 0)
#घोषणा SAI_HWCFGR_SPDIF_PDM	GENMASK(11, 8)
#घोषणा SAI_HWCFGR_REGOUT	GENMASK(19, 12)

/* Bit definition क्रम SAI_VERR रेजिस्टर */
#घोषणा SAI_VERR_MIN_MASK	GENMASK(3, 0)
#घोषणा SAI_VERR_MAJ_MASK	GENMASK(7, 4)

/* Bit definition क्रम SAI_IDR रेजिस्टर */
#घोषणा SAI_IDR_ID_MASK		GENMASK(31, 0)

/* Bit definition क्रम SAI_SIDR रेजिस्टर */
#घोषणा SAI_SIDR_ID_MASK	GENMASK(31, 0)

#घोषणा SAI_IPIDR_NUMBER	0x00130031

/* SAI version numbers are 1.x क्रम F4. Major version number set to 1 क्रम F4 */
#घोषणा STM_SAI_STM32F4		BIT(4)
/* Dummy version number क्रम H7 socs and next */
#घोषणा STM_SAI_STM32H7		0x0

#घोषणा STM_SAI_IS_F4(ip)	((ip)->conf.version == STM_SAI_STM32F4)
#घोषणा STM_SAI_HAS_SPDIF_PDM(ip)\
				((ip)->pdata->conf.has_spdअगर_pdm)

क्रमागत sपंचांग32_sai_syncout अणु
	STM_SAI_SYNC_OUT_NONE,
	STM_SAI_SYNC_OUT_A,
	STM_SAI_SYNC_OUT_B,
पूर्ण;

/**
 * काष्ठा sपंचांग32_sai_conf - SAI configuration
 * @version: SAI version
 * @fअगरo_size: SAI fअगरo size as words number
 * @has_spdअगर_pdm: SAI S/PDIF and PDM features support flag
 */
काष्ठा sपंचांग32_sai_conf अणु
	u32 version;
	u32 fअगरo_size;
	bool has_spdअगर_pdm;
पूर्ण;

/**
 * काष्ठा sपंचांग32_sai_data - निजी data of SAI instance driver
 * @pdev: device data poपूर्णांकer
 * @base: common रेजिस्टर bank भव base address
 * @pclk: SAI bus घड़ी
 * @clk_x8k: SAI parent घड़ी क्रम sampling frequencies multiple of 8kHz
 * @clk_x11k: SAI parent घड़ी क्रम sampling frequencies multiple of 11kHz
 * @conf: SAI hardware capabitilites
 * @irq: SAI पूर्णांकerrupt line
 * @set_sync: poपूर्णांकer to synchro mode configuration callback
 * @gcr: SAI Global Configuration Register
 */
काष्ठा sपंचांग32_sai_data अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	काष्ठा clk *pclk;
	काष्ठा clk *clk_x8k;
	काष्ठा clk *clk_x11k;
	काष्ठा sपंचांग32_sai_conf conf;
	पूर्णांक irq;
	पूर्णांक (*set_sync)(काष्ठा sपंचांग32_sai_data *sai,
			काष्ठा device_node *np_provider, पूर्णांक synco, पूर्णांक synci);
	u32 gcr;
पूर्ण;
