<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel Core SoC Power Management Controller Header File
 *
 * Copyright (c) 2016, Intel Corporation.
 * All Rights Reserved.
 *
 * Authors: Rajneesh Bhardwaj <rajneesh.bhardwaj@पूर्णांकel.com>
 *          Vishwanath Somayaji <vishwanath.somayaji@पूर्णांकel.com>
 */

#अगर_अघोषित PMC_CORE_H
#घोषणा PMC_CORE_H

#समावेश <linux/bits.h>

#घोषणा PMC_BASE_ADDR_DEFAULT			0xFE000000

/* Sunrise Poपूर्णांक Power Management Controller PCI Device ID */
#घोषणा SPT_PMC_PCI_DEVICE_ID			0x9d21
#घोषणा SPT_PMC_BASE_ADDR_OFFSET		0x48
#घोषणा SPT_PMC_SLP_S0_RES_COUNTER_OFFSET	0x13c
#घोषणा SPT_PMC_PM_CFG_OFFSET			0x18
#घोषणा SPT_PMC_PM_STS_OFFSET			0x1c
#घोषणा SPT_PMC_MTPMC_OFFSET			0x20
#घोषणा SPT_PMC_MFPMC_OFFSET			0x38
#घोषणा SPT_PMC_LTR_IGNORE_OFFSET		0x30C
#घोषणा SPT_PMC_VRIC1_OFFSET			0x31c
#घोषणा SPT_PMC_MPHY_CORE_STS_0			0x1143
#घोषणा SPT_PMC_MPHY_CORE_STS_1			0x1142
#घोषणा SPT_PMC_MPHY_COM_STS_0			0x1155
#घोषणा SPT_PMC_MMIO_REG_LEN			0x1000
#घोषणा SPT_PMC_SLP_S0_RES_COUNTER_STEP		0x68
#घोषणा PMC_BASE_ADDR_MASK			~(SPT_PMC_MMIO_REG_LEN - 1)
#घोषणा MTPMC_MASK				0xffff0000
#घोषणा PPFEAR_MAX_NUM_ENTRIES			12
#घोषणा SPT_PPFEAR_NUM_ENTRIES			5
#घोषणा SPT_PMC_READ_DISABLE_BIT		0x16
#घोषणा SPT_PMC_MSG_FULL_STS_BIT		0x18
#घोषणा NUM_RETRIES				100
#घोषणा SPT_NUM_IP_IGN_ALLOWED			17

#घोषणा SPT_PMC_LTR_CUR_PLT			0x350
#घोषणा SPT_PMC_LTR_CUR_ASLT			0x354
#घोषणा SPT_PMC_LTR_SPA				0x360
#घोषणा SPT_PMC_LTR_SPB				0x364
#घोषणा SPT_PMC_LTR_SATA			0x368
#घोषणा SPT_PMC_LTR_GBE				0x36C
#घोषणा SPT_PMC_LTR_XHCI			0x370
#घोषणा SPT_PMC_LTR_RESERVED			0x374
#घोषणा SPT_PMC_LTR_ME				0x378
#घोषणा SPT_PMC_LTR_EVA				0x37C
#घोषणा SPT_PMC_LTR_SPC				0x380
#घोषणा SPT_PMC_LTR_AZ				0x384
#घोषणा SPT_PMC_LTR_LPSS			0x38C
#घोषणा SPT_PMC_LTR_CAM				0x390
#घोषणा SPT_PMC_LTR_SPD				0x394
#घोषणा SPT_PMC_LTR_SPE				0x398
#घोषणा SPT_PMC_LTR_ESPI			0x39C
#घोषणा SPT_PMC_LTR_SCC				0x3A0
#घोषणा SPT_PMC_LTR_ISH				0x3A4

/* Sunrise Poपूर्णांक: PGD PFET Enable Ack Status Registers */
क्रमागत ppfear_regs अणु
	SPT_PMC_XRAM_PPFEAR0A = 0x590,
	SPT_PMC_XRAM_PPFEAR0B,
	SPT_PMC_XRAM_PPFEAR0C,
	SPT_PMC_XRAM_PPFEAR0D,
	SPT_PMC_XRAM_PPFEAR1A,
पूर्ण;

#घोषणा SPT_PMC_BIT_PMC				BIT(0)
#घोषणा SPT_PMC_BIT_OPI				BIT(1)
#घोषणा SPT_PMC_BIT_SPI				BIT(2)
#घोषणा SPT_PMC_BIT_XHCI			BIT(3)
#घोषणा SPT_PMC_BIT_SPA				BIT(4)
#घोषणा SPT_PMC_BIT_SPB				BIT(5)
#घोषणा SPT_PMC_BIT_SPC				BIT(6)
#घोषणा SPT_PMC_BIT_GBE				BIT(7)

#घोषणा SPT_PMC_BIT_SATA			BIT(0)
#घोषणा SPT_PMC_BIT_HDA_PGD0			BIT(1)
#घोषणा SPT_PMC_BIT_HDA_PGD1			BIT(2)
#घोषणा SPT_PMC_BIT_HDA_PGD2			BIT(3)
#घोषणा SPT_PMC_BIT_HDA_PGD3			BIT(4)
#घोषणा SPT_PMC_BIT_RSVD_0B			BIT(5)
#घोषणा SPT_PMC_BIT_LPSS			BIT(6)
#घोषणा SPT_PMC_BIT_LPC				BIT(7)

#घोषणा SPT_PMC_BIT_SMB				BIT(0)
#घोषणा SPT_PMC_BIT_ISH				BIT(1)
#घोषणा SPT_PMC_BIT_P2SB			BIT(2)
#घोषणा SPT_PMC_BIT_DFX				BIT(3)
#घोषणा SPT_PMC_BIT_SCC				BIT(4)
#घोषणा SPT_PMC_BIT_RSVD_0C			BIT(5)
#घोषणा SPT_PMC_BIT_FUSE			BIT(6)
#घोषणा SPT_PMC_BIT_CAMREA			BIT(7)

#घोषणा SPT_PMC_BIT_RSVD_0D			BIT(0)
#घोषणा SPT_PMC_BIT_USB3_OTG			BIT(1)
#घोषणा SPT_PMC_BIT_EXI				BIT(2)
#घोषणा SPT_PMC_BIT_CSE				BIT(3)
#घोषणा SPT_PMC_BIT_CSME_KVM			BIT(4)
#घोषणा SPT_PMC_BIT_CSME_PMT			BIT(5)
#घोषणा SPT_PMC_BIT_CSME_CLINK			BIT(6)
#घोषणा SPT_PMC_BIT_CSME_PTIO			BIT(7)

#घोषणा SPT_PMC_BIT_CSME_USBR			BIT(0)
#घोषणा SPT_PMC_BIT_CSME_SUSRAM			BIT(1)
#घोषणा SPT_PMC_BIT_CSME_SMT			BIT(2)
#घोषणा SPT_PMC_BIT_RSVD_1A			BIT(3)
#घोषणा SPT_PMC_BIT_CSME_SMS2			BIT(4)
#घोषणा SPT_PMC_BIT_CSME_SMS1			BIT(5)
#घोषणा SPT_PMC_BIT_CSME_RTC			BIT(6)
#घोषणा SPT_PMC_BIT_CSME_PSF			BIT(7)

#घोषणा SPT_PMC_BIT_MPHY_LANE0			BIT(0)
#घोषणा SPT_PMC_BIT_MPHY_LANE1			BIT(1)
#घोषणा SPT_PMC_BIT_MPHY_LANE2			BIT(2)
#घोषणा SPT_PMC_BIT_MPHY_LANE3			BIT(3)
#घोषणा SPT_PMC_BIT_MPHY_LANE4			BIT(4)
#घोषणा SPT_PMC_BIT_MPHY_LANE5			BIT(5)
#घोषणा SPT_PMC_BIT_MPHY_LANE6			BIT(6)
#घोषणा SPT_PMC_BIT_MPHY_LANE7			BIT(7)

#घोषणा SPT_PMC_BIT_MPHY_LANE8			BIT(0)
#घोषणा SPT_PMC_BIT_MPHY_LANE9			BIT(1)
#घोषणा SPT_PMC_BIT_MPHY_LANE10			BIT(2)
#घोषणा SPT_PMC_BIT_MPHY_LANE11			BIT(3)
#घोषणा SPT_PMC_BIT_MPHY_LANE12			BIT(4)
#घोषणा SPT_PMC_BIT_MPHY_LANE13			BIT(5)
#घोषणा SPT_PMC_BIT_MPHY_LANE14			BIT(6)
#घोषणा SPT_PMC_BIT_MPHY_LANE15			BIT(7)

#घोषणा SPT_PMC_BIT_MPHY_CMN_LANE0		BIT(0)
#घोषणा SPT_PMC_BIT_MPHY_CMN_LANE1		BIT(1)
#घोषणा SPT_PMC_BIT_MPHY_CMN_LANE2		BIT(2)
#घोषणा SPT_PMC_BIT_MPHY_CMN_LANE3		BIT(3)

#घोषणा SPT_PMC_VRIC1_SLPS0LVEN			BIT(13)
#घोषणा SPT_PMC_VRIC1_XTALSDQDIS		BIT(22)

/* Cannonlake Power Management Controller रेजिस्टर offsets */
#घोषणा CNP_PMC_SLPS0_DBG_OFFSET		0x10B4
#घोषणा CNP_PMC_PM_CFG_OFFSET			0x1818
#घोषणा CNP_PMC_SLP_S0_RES_COUNTER_OFFSET	0x193C
#घोषणा CNP_PMC_LTR_IGNORE_OFFSET		0x1B0C
/* Cannonlake: PGD PFET Enable Ack Status Register(s) start */
#घोषणा CNP_PMC_HOST_PPFEAR0A			0x1D90

#घोषणा CNP_PMC_LATCH_SLPS0_EVENTS		BIT(31)

#घोषणा CNP_PMC_MMIO_REG_LEN			0x2000
#घोषणा CNP_PPFEAR_NUM_ENTRIES			8
#घोषणा CNP_PMC_READ_DISABLE_BIT		22
#घोषणा CNP_NUM_IP_IGN_ALLOWED			19
#घोषणा CNP_PMC_LTR_CUR_PLT			0x1B50
#घोषणा CNP_PMC_LTR_CUR_ASLT			0x1B54
#घोषणा CNP_PMC_LTR_SPA				0x1B60
#घोषणा CNP_PMC_LTR_SPB				0x1B64
#घोषणा CNP_PMC_LTR_SATA			0x1B68
#घोषणा CNP_PMC_LTR_GBE				0x1B6C
#घोषणा CNP_PMC_LTR_XHCI			0x1B70
#घोषणा CNP_PMC_LTR_RESERVED			0x1B74
#घोषणा CNP_PMC_LTR_ME				0x1B78
#घोषणा CNP_PMC_LTR_EVA				0x1B7C
#घोषणा CNP_PMC_LTR_SPC				0x1B80
#घोषणा CNP_PMC_LTR_AZ				0x1B84
#घोषणा CNP_PMC_LTR_LPSS			0x1B8C
#घोषणा CNP_PMC_LTR_CAM				0x1B90
#घोषणा CNP_PMC_LTR_SPD				0x1B94
#घोषणा CNP_PMC_LTR_SPE				0x1B98
#घोषणा CNP_PMC_LTR_ESPI			0x1B9C
#घोषणा CNP_PMC_LTR_SCC				0x1BA0
#घोषणा CNP_PMC_LTR_ISH				0x1BA4
#घोषणा CNP_PMC_LTR_CNV				0x1BF0
#घोषणा CNP_PMC_LTR_EMMC			0x1BF4
#घोषणा CNP_PMC_LTR_UFSX2			0x1BF8

#घोषणा LTR_DECODED_VAL				GENMASK(9, 0)
#घोषणा LTR_DECODED_SCALE			GENMASK(12, 10)
#घोषणा LTR_REQ_SNOOP				BIT(15)
#घोषणा LTR_REQ_NONSNOOP			BIT(31)

#घोषणा ICL_PPFEAR_NUM_ENTRIES			9
#घोषणा ICL_NUM_IP_IGN_ALLOWED			20
#घोषणा ICL_PMC_LTR_WIGIG			0x1BFC
#घोषणा ICL_PMC_SLP_S0_RES_COUNTER_STEP		0x64

#घोषणा LPM_MAX_NUM_MODES			8
#घोषणा GET_X2_COUNTER(v)			((v) >> 1)
#घोषणा LPM_STS_LATCH_MODE			BIT(31)

#घोषणा TGL_PMC_SLP_S0_RES_COUNTER_STEP		0x7A
#घोषणा TGL_PMC_LTR_THC0			0x1C04
#घोषणा TGL_PMC_LTR_THC1			0x1C08
#घोषणा TGL_NUM_IP_IGN_ALLOWED			23
#घोषणा TGL_PMC_LPM_RES_COUNTER_STEP_X2		61	/* 30.5us * 2 */

/*
 * Tigerlake Power Management Controller रेजिस्टर offsets
 */
#घोषणा TGL_LPM_STS_LATCH_EN_OFFSET		0x1C34
#घोषणा TGL_LPM_EN_OFFSET			0x1C78
#घोषणा TGL_LPM_RESIDENCY_OFFSET		0x1C80

/* Tigerlake Low Power Mode debug रेजिस्टरs */
#घोषणा TGL_LPM_STATUS_OFFSET			0x1C3C
#घोषणा TGL_LPM_LIVE_STATUS_OFFSET		0x1C5C
#घोषणा TGL_LPM_PRI_OFFSET			0x1C7C
#घोषणा TGL_LPM_NUM_MAPS			6

/* Extended Test Mode Register 3 (CNL and later) */
#घोषणा ETR3_OFFSET				0x1048
#घोषणा ETR3_CF9GR				BIT(20)
#घोषणा ETR3_CF9LOCK				BIT(31)

/* Extended Test Mode Register LPM bits (TGL and later */
#घोषणा ETR3_CLEAR_LPM_EVENTS			BIT(28)

स्थिर अक्षर *pmc_lpm_modes[] = अणु
	"S0i2.0",
	"S0i2.1",
	"S0i2.2",
	"S0i3.0",
	"S0i3.1",
	"S0i3.2",
	"S0i3.3",
	"S0i3.4",
	शून्य
पूर्ण;

काष्ठा pmc_bit_map अणु
	स्थिर अक्षर *name;
	u32 bit_mask;
पूर्ण;

/**
 * काष्ठा pmc_reg_map - Structure used to define parameter unique to a
			PCH family
 * @pfear_sts:		Maps name of IP block to PPFEAR* bit
 * @mphy_sts:		Maps name of MPHY lane to MPHY status lane status bit
 * @pll_sts:		Maps name of PLL to corresponding bit status
 * @slps0_dbg_maps:	Array of SLP_S0_DBG* रेजिस्टरs containing debug info
 * @ltr_show_sts:	Maps PCH IP Names to their MMIO रेजिस्टर offsets
 * @slp_s0_offset:	PWRMBASE offset to पढ़ो SLP_S0 residency
 * @ltr_ignore_offset:	PWRMBASE offset to पढ़ो/ग_लिखो LTR ignore bit
 * @regmap_length:	Length of memory to map from PWRMBASE address to access
 * @ppfear0_offset:	PWRMBASE offset to to पढ़ो PPFEAR*
 * @ppfear_buckets:	Number of 8 bits blocks to पढ़ो all IP blocks from
 *			PPFEAR
 * @pm_cfg_offset:	PWRMBASE offset to PM_CFG रेजिस्टर
 * @pm_पढ़ो_disable_bit: Bit index to पढ़ो PMC_READ_DISABLE
 * @slps0_dbg_offset:	PWRMBASE offset to SLP_S0_DEBUG_REG*
 *
 * Each PCH has unique set of रेजिस्टर offsets and bit indexes. This काष्ठाure
 * captures them to have a common implementation.
 */
काष्ठा pmc_reg_map अणु
	स्थिर काष्ठा pmc_bit_map **pfear_sts;
	स्थिर काष्ठा pmc_bit_map *mphy_sts;
	स्थिर काष्ठा pmc_bit_map *pll_sts;
	स्थिर काष्ठा pmc_bit_map **slps0_dbg_maps;
	स्थिर काष्ठा pmc_bit_map *ltr_show_sts;
	स्थिर काष्ठा pmc_bit_map *msr_sts;
	स्थिर काष्ठा pmc_bit_map **lpm_sts;
	स्थिर u32 slp_s0_offset;
	स्थिर पूर्णांक slp_s0_res_counter_step;
	स्थिर u32 ltr_ignore_offset;
	स्थिर पूर्णांक regmap_length;
	स्थिर u32 ppfear0_offset;
	स्थिर पूर्णांक ppfear_buckets;
	स्थिर u32 pm_cfg_offset;
	स्थिर पूर्णांक pm_पढ़ो_disable_bit;
	स्थिर u32 slps0_dbg_offset;
	स्थिर u32 ltr_ignore_max;
	स्थिर u32 pm_vric1_offset;
	/* Low Power Mode रेजिस्टरs */
	स्थिर पूर्णांक lpm_num_maps;
	स्थिर पूर्णांक lpm_res_counter_step_x2;
	स्थिर u32 lpm_sts_latch_en_offset;
	स्थिर u32 lpm_en_offset;
	स्थिर u32 lpm_priority_offset;
	स्थिर u32 lpm_residency_offset;
	स्थिर u32 lpm_status_offset;
	स्थिर u32 lpm_live_status_offset;
	स्थिर u32 etr3_offset;
पूर्ण;

/**
 * काष्ठा pmc_dev - pmc device काष्ठाure
 * @base_addr:		contains pmc base address
 * @regbase:		poपूर्णांकer to io-remapped memory location
 * @map:		poपूर्णांकer to pmc_reg_map काष्ठा that contains platक्रमm
 *			specअगरic attributes
 * @dbgfs_dir:		path to debugfs पूर्णांकerface
 * @pmc_xram_पढ़ो_bit:	flag to indicate whether PMC XRAM shaकरोw रेजिस्टरs
 *			used to पढ़ो MPHY PG and PLL status are available
 * @mutex_lock:		mutex to complete one transcation
 * @check_counters:	On resume, check अगर counters are getting incremented
 * @pc10_counter:	PC10 residency counter
 * @s0ix_counter:	S0ix residency (step adjusted)
 * @num_lpm_modes:	Count of enabled modes
 * @lpm_en_modes:	Array of enabled modes from lowest to highest priority
 * @lpm_req_regs:	List of substate requirements
 *
 * pmc_dev contains info about घातer management controller device.
 */
काष्ठा pmc_dev अणु
	u32 base_addr;
	व्योम __iomem *regbase;
	स्थिर काष्ठा pmc_reg_map *map;
	काष्ठा dentry *dbgfs_dir;
	पूर्णांक pmc_xram_पढ़ो_bit;
	काष्ठा mutex lock; /* generic mutex lock क्रम PMC Core */

	bool check_counters; /* Check क्रम counter increments on resume */
	u64 pc10_counter;
	u64 s0ix_counter;
	पूर्णांक num_lpm_modes;
	पूर्णांक lpm_en_modes[LPM_MAX_NUM_MODES];
	u32 *lpm_req_regs;
पूर्ण;

#घोषणा pmc_क्रम_each_mode(i, mode, pmcdev)		\
	क्रम (i = 0, mode = pmcdev->lpm_en_modes[i];	\
	     i < pmcdev->num_lpm_modes;			\
	     i++, mode = pmcdev->lpm_en_modes[i])

#घोषणा DEFINE_PMC_CORE_ATTR_WRITE(__name)				\
अटल पूर्णांक __name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	वापस single_खोलो(file, __name ## _show, inode->i_निजी);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations __name ## _fops = अणु			\
	.owner		= THIS_MODULE,					\
	.खोलो		= __name ## _खोलो,				\
	.पढ़ो		= seq_पढ़ो,					\
	.ग_लिखो		= __name ## _ग_लिखो,				\
	.release	= single_release,				\
पूर्ण

#पूर्ण_अगर /* PMC_CORE_H */
