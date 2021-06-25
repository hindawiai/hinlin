<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCIe host controller driver क्रम Tegra194 SoC
 *
 * Copyright (C) 2019 NVIDIA Corporation.
 *
 * Author: Vidya Sagar <vidyas@nvidia.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/reset.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश "pcie-designware.h"
#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>
#समावेश "../../pci.h"

#घोषणा APPL_PINMUX				0x0
#घोषणा APPL_PINMUX_PEX_RST			BIT(0)
#घोषणा APPL_PINMUX_CLKREQ_OVERRIDE_EN		BIT(2)
#घोषणा APPL_PINMUX_CLKREQ_OVERRIDE		BIT(3)
#घोषणा APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE_EN	BIT(4)
#घोषणा APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE	BIT(5)

#घोषणा APPL_CTRL				0x4
#घोषणा APPL_CTRL_SYS_PRE_DET_STATE		BIT(6)
#घोषणा APPL_CTRL_LTSSM_EN			BIT(7)
#घोषणा APPL_CTRL_HW_HOT_RST_EN			BIT(20)
#घोषणा APPL_CTRL_HW_HOT_RST_MODE_MASK		GENMASK(1, 0)
#घोषणा APPL_CTRL_HW_HOT_RST_MODE_SHIFT		22
#घोषणा APPL_CTRL_HW_HOT_RST_MODE_IMDT_RST	0x1

#घोषणा APPL_INTR_EN_L0_0			0x8
#घोषणा APPL_INTR_EN_L0_0_LINK_STATE_INT_EN	BIT(0)
#घोषणा APPL_INTR_EN_L0_0_MSI_RCV_INT_EN	BIT(4)
#घोषणा APPL_INTR_EN_L0_0_INT_INT_EN		BIT(8)
#घोषणा APPL_INTR_EN_L0_0_PCI_CMD_EN_INT_EN	BIT(15)
#घोषणा APPL_INTR_EN_L0_0_CDM_REG_CHK_INT_EN	BIT(19)
#घोषणा APPL_INTR_EN_L0_0_SYS_INTR_EN		BIT(30)
#घोषणा APPL_INTR_EN_L0_0_SYS_MSI_INTR_EN	BIT(31)

#घोषणा APPL_INTR_STATUS_L0			0xC
#घोषणा APPL_INTR_STATUS_L0_LINK_STATE_INT	BIT(0)
#घोषणा APPL_INTR_STATUS_L0_INT_INT		BIT(8)
#घोषणा APPL_INTR_STATUS_L0_PCI_CMD_EN_INT	BIT(15)
#घोषणा APPL_INTR_STATUS_L0_PEX_RST_INT		BIT(16)
#घोषणा APPL_INTR_STATUS_L0_CDM_REG_CHK_INT	BIT(18)

#घोषणा APPL_INTR_EN_L1_0_0				0x1C
#घोषणा APPL_INTR_EN_L1_0_0_LINK_REQ_RST_NOT_INT_EN	BIT(1)
#घोषणा APPL_INTR_EN_L1_0_0_RDLH_LINK_UP_INT_EN		BIT(3)
#घोषणा APPL_INTR_EN_L1_0_0_HOT_RESET_DONE_INT_EN	BIT(30)

#घोषणा APPL_INTR_STATUS_L1_0_0				0x20
#घोषणा APPL_INTR_STATUS_L1_0_0_LINK_REQ_RST_NOT_CHGED	BIT(1)
#घोषणा APPL_INTR_STATUS_L1_0_0_RDLH_LINK_UP_CHGED	BIT(3)
#घोषणा APPL_INTR_STATUS_L1_0_0_HOT_RESET_DONE		BIT(30)

#घोषणा APPL_INTR_STATUS_L1_1			0x2C
#घोषणा APPL_INTR_STATUS_L1_2			0x30
#घोषणा APPL_INTR_STATUS_L1_3			0x34
#घोषणा APPL_INTR_STATUS_L1_6			0x3C
#घोषणा APPL_INTR_STATUS_L1_7			0x40
#घोषणा APPL_INTR_STATUS_L1_15_CFG_BME_CHGED	BIT(1)

#घोषणा APPL_INTR_EN_L1_8_0			0x44
#घोषणा APPL_INTR_EN_L1_8_BW_MGT_INT_EN		BIT(2)
#घोषणा APPL_INTR_EN_L1_8_AUTO_BW_INT_EN	BIT(3)
#घोषणा APPL_INTR_EN_L1_8_INTX_EN		BIT(11)
#घोषणा APPL_INTR_EN_L1_8_AER_INT_EN		BIT(15)

#घोषणा APPL_INTR_STATUS_L1_8_0			0x4C
#घोषणा APPL_INTR_STATUS_L1_8_0_EDMA_INT_MASK	GENMASK(11, 6)
#घोषणा APPL_INTR_STATUS_L1_8_0_BW_MGT_INT_STS	BIT(2)
#घोषणा APPL_INTR_STATUS_L1_8_0_AUTO_BW_INT_STS	BIT(3)

#घोषणा APPL_INTR_STATUS_L1_9			0x54
#घोषणा APPL_INTR_STATUS_L1_10			0x58
#घोषणा APPL_INTR_STATUS_L1_11			0x64
#घोषणा APPL_INTR_STATUS_L1_13			0x74
#घोषणा APPL_INTR_STATUS_L1_14			0x78
#घोषणा APPL_INTR_STATUS_L1_15			0x7C
#घोषणा APPL_INTR_STATUS_L1_17			0x88

#घोषणा APPL_INTR_EN_L1_18				0x90
#घोषणा APPL_INTR_EN_L1_18_CDM_REG_CHK_CMPLT		BIT(2)
#घोषणा APPL_INTR_EN_L1_18_CDM_REG_CHK_CMP_ERR		BIT(1)
#घोषणा APPL_INTR_EN_L1_18_CDM_REG_CHK_LOGIC_ERR	BIT(0)

#घोषणा APPL_INTR_STATUS_L1_18				0x94
#घोषणा APPL_INTR_STATUS_L1_18_CDM_REG_CHK_CMPLT	BIT(2)
#घोषणा APPL_INTR_STATUS_L1_18_CDM_REG_CHK_CMP_ERR	BIT(1)
#घोषणा APPL_INTR_STATUS_L1_18_CDM_REG_CHK_LOGIC_ERR	BIT(0)

#घोषणा APPL_MSI_CTRL_1				0xAC

#घोषणा APPL_MSI_CTRL_2				0xB0

#घोषणा APPL_LEGACY_INTX			0xB8

#घोषणा APPL_LTR_MSG_1				0xC4
#घोषणा LTR_MSG_REQ				BIT(15)
#घोषणा LTR_MST_NO_SNOOP_SHIFT			16

#घोषणा APPL_LTR_MSG_2				0xC8
#घोषणा APPL_LTR_MSG_2_LTR_MSG_REQ_STATE	BIT(3)

#घोषणा APPL_LINK_STATUS			0xCC
#घोषणा APPL_LINK_STATUS_RDLH_LINK_UP		BIT(0)

#घोषणा APPL_DEBUG				0xD0
#घोषणा APPL_DEBUG_PM_LINKST_IN_L2_LAT		BIT(21)
#घोषणा APPL_DEBUG_PM_LINKST_IN_L0		0x11
#घोषणा APPL_DEBUG_LTSSM_STATE_MASK		GENMASK(8, 3)
#घोषणा APPL_DEBUG_LTSSM_STATE_SHIFT		3
#घोषणा LTSSM_STATE_PRE_DETECT			5

#घोषणा APPL_RADM_STATUS			0xE4
#घोषणा APPL_PM_XMT_TURNOFF_STATE		BIT(0)

#घोषणा APPL_DM_TYPE				0x100
#घोषणा APPL_DM_TYPE_MASK			GENMASK(3, 0)
#घोषणा APPL_DM_TYPE_RP				0x4
#घोषणा APPL_DM_TYPE_EP				0x0

#घोषणा APPL_CFG_BASE_ADDR			0x104
#घोषणा APPL_CFG_BASE_ADDR_MASK			GENMASK(31, 12)

#घोषणा APPL_CFG_IATU_DMA_BASE_ADDR		0x108
#घोषणा APPL_CFG_IATU_DMA_BASE_ADDR_MASK	GENMASK(31, 18)

#घोषणा APPL_CFG_MISC				0x110
#घोषणा APPL_CFG_MISC_SLV_EP_MODE		BIT(14)
#घोषणा APPL_CFG_MISC_ARCACHE_MASK		GENMASK(13, 10)
#घोषणा APPL_CFG_MISC_ARCACHE_SHIFT		10
#घोषणा APPL_CFG_MISC_ARCACHE_VAL		3

#घोषणा APPL_CFG_SLCG_OVERRIDE			0x114
#घोषणा APPL_CFG_SLCG_OVERRIDE_SLCG_EN_MASTER	BIT(0)

#घोषणा APPL_CAR_RESET_OVRD				0x12C
#घोषणा APPL_CAR_RESET_OVRD_CYA_OVERRIDE_CORE_RST_N	BIT(0)

#घोषणा IO_BASE_IO_DECODE				BIT(0)
#घोषणा IO_BASE_IO_DECODE_BIT8				BIT(8)

#घोषणा CFG_PREF_MEM_LIMIT_BASE_MEM_DECODE		BIT(0)
#घोषणा CFG_PREF_MEM_LIMIT_BASE_MEM_LIMIT_DECODE	BIT(16)

#घोषणा CFG_TIMER_CTRL_MAX_FUNC_NUM_OFF	0x718
#घोषणा CFG_TIMER_CTRL_ACK_NAK_SHIFT	(19)

#घोषणा EVENT_COUNTER_ALL_CLEAR		0x3
#घोषणा EVENT_COUNTER_ENABLE_ALL	0x7
#घोषणा EVENT_COUNTER_ENABLE_SHIFT	2
#घोषणा EVENT_COUNTER_EVENT_SEL_MASK	GENMASK(7, 0)
#घोषणा EVENT_COUNTER_EVENT_SEL_SHIFT	16
#घोषणा EVENT_COUNTER_EVENT_Tx_L0S	0x2
#घोषणा EVENT_COUNTER_EVENT_Rx_L0S	0x3
#घोषणा EVENT_COUNTER_EVENT_L1		0x5
#घोषणा EVENT_COUNTER_EVENT_L1_1	0x7
#घोषणा EVENT_COUNTER_EVENT_L1_2	0x8
#घोषणा EVENT_COUNTER_GROUP_SEL_SHIFT	24
#घोषणा EVENT_COUNTER_GROUP_5		0x5

#घोषणा N_FTS_VAL					52
#घोषणा FTS_VAL						52

#घोषणा PORT_LOGIC_MSI_CTRL_INT_0_EN		0x828

#घोषणा GEN3_EQ_CONTROL_OFF			0x8a8
#घोषणा GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_SHIFT	8
#घोषणा GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_MASK	GENMASK(23, 8)
#घोषणा GEN3_EQ_CONTROL_OFF_FB_MODE_MASK	GENMASK(3, 0)

#घोषणा GEN3_RELATED_OFF			0x890
#घोषणा GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL	BIT(0)
#घोषणा GEN3_RELATED_OFF_GEN3_EQ_DISABLE	BIT(16)
#घोषणा GEN3_RELATED_OFF_RATE_SHADOW_SEL_SHIFT	24
#घोषणा GEN3_RELATED_OFF_RATE_SHADOW_SEL_MASK	GENMASK(25, 24)

#घोषणा PORT_LOGIC_AMBA_ERROR_RESPONSE_DEFAULT	0x8D0
#घोषणा AMBA_ERROR_RESPONSE_CRS_SHIFT		3
#घोषणा AMBA_ERROR_RESPONSE_CRS_MASK		GENMASK(1, 0)
#घोषणा AMBA_ERROR_RESPONSE_CRS_OKAY		0
#घोषणा AMBA_ERROR_RESPONSE_CRS_OKAY_FFFFFFFF	1
#घोषणा AMBA_ERROR_RESPONSE_CRS_OKAY_FFFF0001	2

#घोषणा MSIX_ADDR_MATCH_LOW_OFF			0x940
#घोषणा MSIX_ADDR_MATCH_LOW_OFF_EN		BIT(0)
#घोषणा MSIX_ADDR_MATCH_LOW_OFF_MASK		GENMASK(31, 2)

#घोषणा MSIX_ADDR_MATCH_HIGH_OFF		0x944
#घोषणा MSIX_ADDR_MATCH_HIGH_OFF_MASK		GENMASK(31, 0)

#घोषणा PORT_LOGIC_MSIX_DOORBELL			0x948

#घोषणा CAP_SPCIE_CAP_OFF			0x154
#घोषणा CAP_SPCIE_CAP_OFF_DSP_TX_PRESET0_MASK	GENMASK(3, 0)
#घोषणा CAP_SPCIE_CAP_OFF_USP_TX_PRESET0_MASK	GENMASK(11, 8)
#घोषणा CAP_SPCIE_CAP_OFF_USP_TX_PRESET0_SHIFT	8

#घोषणा PME_ACK_TIMEOUT 10000

#घोषणा LTSSM_TIMEOUT 50000	/* 50ms */

#घोषणा GEN3_GEN4_EQ_PRESET_INIT	5

#घोषणा GEN1_CORE_CLK_FREQ	62500000
#घोषणा GEN2_CORE_CLK_FREQ	125000000
#घोषणा GEN3_CORE_CLK_FREQ	250000000
#घोषणा GEN4_CORE_CLK_FREQ	500000000

#घोषणा LTR_MSG_TIMEOUT		(100 * 1000)

#घोषणा PERST_DEBOUNCE_TIME	(5 * 1000)

#घोषणा EP_STATE_DISABLED	0
#घोषणा EP_STATE_ENABLED	1

अटल स्थिर अचिन्हित पूर्णांक pcie_gen_freq[] = अणु
	GEN1_CORE_CLK_FREQ,
	GEN2_CORE_CLK_FREQ,
	GEN3_CORE_CLK_FREQ,
	GEN4_CORE_CLK_FREQ
पूर्ण;

काष्ठा tegra_pcie_dw अणु
	काष्ठा device *dev;
	काष्ठा resource *appl_res;
	काष्ठा resource *dbi_res;
	काष्ठा resource *atu_dma_res;
	व्योम __iomem *appl_base;
	काष्ठा clk *core_clk;
	काष्ठा reset_control *core_apb_rst;
	काष्ठा reset_control *core_rst;
	काष्ठा dw_pcie pci;
	काष्ठा tegra_bpmp *bpmp;

	क्रमागत dw_pcie_device_mode mode;

	bool supports_clkreq;
	bool enable_cdm_check;
	bool link_state;
	bool update_fc_fixup;
	u8 init_link_width;
	u32 msi_ctrl_पूर्णांक;
	u32 num_lanes;
	u32 cid;
	u32 cfg_link_cap_l1sub;
	u32 pcie_cap_base;
	u32 aspm_cmrt;
	u32 aspm_pwr_on_t;
	u32 aspm_l0s_enter_lat;

	काष्ठा regulator *pex_ctl_supply;
	काष्ठा regulator *slot_ctl_3v3;
	काष्ठा regulator *slot_ctl_12v;

	अचिन्हित पूर्णांक phy_count;
	काष्ठा phy **phys;

	काष्ठा dentry *debugfs;

	/* Endpoपूर्णांक mode specअगरic */
	काष्ठा gpio_desc *pex_rst_gpiod;
	काष्ठा gpio_desc *pex_refclk_sel_gpiod;
	अचिन्हित पूर्णांक pex_rst_irq;
	पूर्णांक ep_state;
पूर्ण;

काष्ठा tegra_pcie_dw_of_data अणु
	क्रमागत dw_pcie_device_mode mode;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_pcie_dw *to_tegra_pcie(काष्ठा dw_pcie *pci)
अणु
	वापस container_of(pci, काष्ठा tegra_pcie_dw, pci);
पूर्ण

अटल अंतरभूत व्योम appl_ग_लिखोl(काष्ठा tegra_pcie_dw *pcie, स्थिर u32 value,
			       स्थिर u32 reg)
अणु
	ग_लिखोl_relaxed(value, pcie->appl_base + reg);
पूर्ण

अटल अंतरभूत u32 appl_पढ़ोl(काष्ठा tegra_pcie_dw *pcie, स्थिर u32 reg)
अणु
	वापस पढ़ोl_relaxed(pcie->appl_base + reg);
पूर्ण

काष्ठा tegra_pcie_soc अणु
	क्रमागत dw_pcie_device_mode mode;
पूर्ण;

अटल व्योम apply_bad_link_workaround(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 current_link_width;
	u16 val;

	/*
	 * NOTE:- Since this scenario is uncommon and link as such is not
	 * stable anyway, not रुकोing to confirm अगर link is really
	 * transitioning to Gen-2 speed
	 */
	val = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKSTA);
	अगर (val & PCI_EXP_LNKSTA_LBMS) अणु
		current_link_width = (val & PCI_EXP_LNKSTA_NLW) >>
				     PCI_EXP_LNKSTA_NLW_SHIFT;
		अगर (pcie->init_link_width > current_link_width) अणु
			dev_warn(pci->dev, "PCIe link is bad, width reduced\n");
			val = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base +
						PCI_EXP_LNKCTL2);
			val &= ~PCI_EXP_LNKCTL2_TLS;
			val |= PCI_EXP_LNKCTL2_TLS_2_5GT;
			dw_pcie_ग_लिखोw_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_LNKCTL2, val);

			val = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base +
						PCI_EXP_LNKCTL);
			val |= PCI_EXP_LNKCTL_RL;
			dw_pcie_ग_लिखोw_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_LNKCTL, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t tegra_pcie_rp_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_pcie_dw *pcie = arg;
	काष्ठा dw_pcie *pci = &pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	u32 val, पंचांगp;
	u16 val_w;

	val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L0);
	अगर (val & APPL_INTR_STATUS_L0_LINK_STATE_INT) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L1_0_0);
		अगर (val & APPL_INTR_STATUS_L1_0_0_LINK_REQ_RST_NOT_CHGED) अणु
			appl_ग_लिखोl(pcie, val, APPL_INTR_STATUS_L1_0_0);

			/* SBR & Surprise Link Down WAR */
			val = appl_पढ़ोl(pcie, APPL_CAR_RESET_OVRD);
			val &= ~APPL_CAR_RESET_OVRD_CYA_OVERRIDE_CORE_RST_N;
			appl_ग_लिखोl(pcie, val, APPL_CAR_RESET_OVRD);
			udelay(1);
			val = appl_पढ़ोl(pcie, APPL_CAR_RESET_OVRD);
			val |= APPL_CAR_RESET_OVRD_CYA_OVERRIDE_CORE_RST_N;
			appl_ग_लिखोl(pcie, val, APPL_CAR_RESET_OVRD);

			val = dw_pcie_पढ़ोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
			val |= PORT_LOGIC_SPEED_CHANGE;
			dw_pcie_ग_लिखोl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
		पूर्ण
	पूर्ण

	अगर (val & APPL_INTR_STATUS_L0_INT_INT) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L1_8_0);
		अगर (val & APPL_INTR_STATUS_L1_8_0_AUTO_BW_INT_STS) अणु
			appl_ग_लिखोl(pcie,
				    APPL_INTR_STATUS_L1_8_0_AUTO_BW_INT_STS,
				    APPL_INTR_STATUS_L1_8_0);
			apply_bad_link_workaround(pp);
		पूर्ण
		अगर (val & APPL_INTR_STATUS_L1_8_0_BW_MGT_INT_STS) अणु
			appl_ग_लिखोl(pcie,
				    APPL_INTR_STATUS_L1_8_0_BW_MGT_INT_STS,
				    APPL_INTR_STATUS_L1_8_0);

			val_w = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base +
						  PCI_EXP_LNKSTA);
			dev_dbg(pci->dev, "Link Speed : Gen-%u\n", val_w &
				PCI_EXP_LNKSTA_CLS);
		पूर्ण
	पूर्ण

	val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L0);
	अगर (val & APPL_INTR_STATUS_L0_CDM_REG_CHK_INT) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L1_18);
		पंचांगp = dw_pcie_पढ़ोl_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS);
		अगर (val & APPL_INTR_STATUS_L1_18_CDM_REG_CHK_CMPLT) अणु
			dev_info(pci->dev, "CDM check complete\n");
			पंचांगp |= PCIE_PL_CHK_REG_CHK_REG_COMPLETE;
		पूर्ण
		अगर (val & APPL_INTR_STATUS_L1_18_CDM_REG_CHK_CMP_ERR) अणु
			dev_err(pci->dev, "CDM comparison mismatch\n");
			पंचांगp |= PCIE_PL_CHK_REG_CHK_REG_COMPARISON_ERROR;
		पूर्ण
		अगर (val & APPL_INTR_STATUS_L1_18_CDM_REG_CHK_LOGIC_ERR) अणु
			dev_err(pci->dev, "CDM Logic error\n");
			पंचांगp |= PCIE_PL_CHK_REG_CHK_REG_LOGIC_ERROR;
		पूर्ण
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS, पंचांगp);
		पंचांगp = dw_pcie_पढ़ोl_dbi(pci, PCIE_PL_CHK_REG_ERR_ADDR);
		dev_err(pci->dev, "CDM Error Address Offset = 0x%08X\n", पंचांगp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pex_ep_event_hot_rst_करोne(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 val;

	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_0_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_1);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_2);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_3);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_6);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_7);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_8_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_9);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_10);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_11);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_13);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_14);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_15);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_17);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_MSI_CTRL_2);

	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val |= APPL_CTRL_LTSSM_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);
पूर्ण

अटल irqवापस_t tegra_pcie_ep_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_pcie_dw *pcie = arg;
	काष्ठा dw_pcie *pci = &pcie->pci;
	u32 val, speed;

	speed = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKSTA) &
		PCI_EXP_LNKSTA_CLS;
	clk_set_rate(pcie->core_clk, pcie_gen_freq[speed - 1]);

	/* If EP करोesn't advertise L1SS, just वापस */
	val = dw_pcie_पढ़ोl_dbi(pci, pcie->cfg_link_cap_l1sub);
	अगर (!(val & (PCI_L1SS_CAP_ASPM_L1_1 | PCI_L1SS_CAP_ASPM_L1_2)))
		वापस IRQ_HANDLED;

	/* Check अगर BME is set to '1' */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_COMMAND);
	अगर (val & PCI_COMMAND_MASTER) अणु
		kसमय_प्रकार समयout;

		/* 110us क्रम both snoop and no-snoop */
		val = 110 | (2 << PCI_LTR_SCALE_SHIFT) | LTR_MSG_REQ;
		val |= (val << LTR_MST_NO_SNOOP_SHIFT);
		appl_ग_लिखोl(pcie, val, APPL_LTR_MSG_1);

		/* Send LTR upstream */
		val = appl_पढ़ोl(pcie, APPL_LTR_MSG_2);
		val |= APPL_LTR_MSG_2_LTR_MSG_REQ_STATE;
		appl_ग_लिखोl(pcie, val, APPL_LTR_MSG_2);

		समयout = kसमय_add_us(kसमय_get(), LTR_MSG_TIMEOUT);
		क्रम (;;) अणु
			val = appl_पढ़ोl(pcie, APPL_LTR_MSG_2);
			अगर (!(val & APPL_LTR_MSG_2_LTR_MSG_REQ_STATE))
				अवरोध;
			अगर (kसमय_after(kसमय_get(), समयout))
				अवरोध;
			usleep_range(1000, 1100);
		पूर्ण
		अगर (val & APPL_LTR_MSG_2_LTR_MSG_REQ_STATE)
			dev_err(pcie->dev, "Failed to send LTR message\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tegra_pcie_ep_hard_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_pcie_dw *pcie = arg;
	काष्ठा dw_pcie_ep *ep = &pcie->pci.ep;
	पूर्णांक spurious = 1;
	u32 val, पंचांगp;

	val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L0);
	अगर (val & APPL_INTR_STATUS_L0_LINK_STATE_INT) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L1_0_0);
		appl_ग_लिखोl(pcie, val, APPL_INTR_STATUS_L1_0_0);

		अगर (val & APPL_INTR_STATUS_L1_0_0_HOT_RESET_DONE)
			pex_ep_event_hot_rst_करोne(pcie);

		अगर (val & APPL_INTR_STATUS_L1_0_0_RDLH_LINK_UP_CHGED) अणु
			पंचांगp = appl_पढ़ोl(pcie, APPL_LINK_STATUS);
			अगर (पंचांगp & APPL_LINK_STATUS_RDLH_LINK_UP) अणु
				dev_dbg(pcie->dev, "Link is up with Host\n");
				dw_pcie_ep_linkup(ep);
			पूर्ण
		पूर्ण

		spurious = 0;
	पूर्ण

	अगर (val & APPL_INTR_STATUS_L0_PCI_CMD_EN_INT) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_STATUS_L1_15);
		appl_ग_लिखोl(pcie, val, APPL_INTR_STATUS_L1_15);

		अगर (val & APPL_INTR_STATUS_L1_15_CFG_BME_CHGED)
			वापस IRQ_WAKE_THREAD;

		spurious = 0;
	पूर्ण

	अगर (spurious) अणु
		dev_warn(pcie->dev, "Random interrupt (STATUS = 0x%08X)\n",
			 val);
		appl_ग_लिखोl(pcie, val, APPL_INTR_STATUS_L0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_rd_own_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
				     पूर्णांक size, u32 *val)
अणु
	/*
	 * This is an endpoपूर्णांक mode specअगरic रेजिस्टर happen to appear even
	 * when controller is operating in root port mode and प्रणाली hangs
	 * when it is accessed with link being in ASPM-L1 state.
	 * So skip accessing it altogether
	 */
	अगर (!PCI_SLOT(devfn) && where == PORT_LOGIC_MSIX_DOORBELL) अणु
		*val = 0x00000000;
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, val);
पूर्ण

अटल पूर्णांक tegra_pcie_dw_wr_own_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
				     पूर्णांक size, u32 val)
अणु
	/*
	 * This is an endpoपूर्णांक mode specअगरic रेजिस्टर happen to appear even
	 * when controller is operating in root port mode and प्रणाली hangs
	 * when it is accessed with link being in ASPM-L1 state.
	 * So skip accessing it altogether
	 */
	अगर (!PCI_SLOT(devfn) && where == PORT_LOGIC_MSIX_DOORBELL)
		वापस PCIBIOS_SUCCESSFUL;

	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, val);
पूर्ण

अटल काष्ठा pci_ops tegra_pci_ops = अणु
	.map_bus = dw_pcie_own_conf_map_bus,
	.पढ़ो = tegra_pcie_dw_rd_own_conf,
	.ग_लिखो = tegra_pcie_dw_wr_own_conf,
पूर्ण;

#अगर defined(CONFIG_PCIEASPM)
अटल स्थिर u32 event_cntr_ctrl_offset[] = अणु
	0x1d8,
	0x1a8,
	0x1a8,
	0x1a8,
	0x1c4,
	0x1d8
पूर्ण;

अटल स्थिर u32 event_cntr_data_offset[] = अणु
	0x1dc,
	0x1ac,
	0x1ac,
	0x1ac,
	0x1c8,
	0x1dc
पूर्ण;

अटल व्योम disable_aspm_l11(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(&pcie->pci, pcie->cfg_link_cap_l1sub);
	val &= ~PCI_L1SS_CAP_ASPM_L1_1;
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, pcie->cfg_link_cap_l1sub, val);
पूर्ण

अटल व्योम disable_aspm_l12(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(&pcie->pci, pcie->cfg_link_cap_l1sub);
	val &= ~PCI_L1SS_CAP_ASPM_L1_2;
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, pcie->cfg_link_cap_l1sub, val);
पूर्ण

अटल अंतरभूत u32 event_counter_prog(काष्ठा tegra_pcie_dw *pcie, u32 event)
अणु
	u32 val;

	val = dw_pcie_पढ़ोl_dbi(&pcie->pci, event_cntr_ctrl_offset[pcie->cid]);
	val &= ~(EVENT_COUNTER_EVENT_SEL_MASK << EVENT_COUNTER_EVENT_SEL_SHIFT);
	val |= EVENT_COUNTER_GROUP_5 << EVENT_COUNTER_GROUP_SEL_SHIFT;
	val |= event << EVENT_COUNTER_EVENT_SEL_SHIFT;
	val |= EVENT_COUNTER_ENABLE_ALL << EVENT_COUNTER_ENABLE_SHIFT;
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, event_cntr_ctrl_offset[pcie->cid], val);
	val = dw_pcie_पढ़ोl_dbi(&pcie->pci, event_cntr_data_offset[pcie->cid]);

	वापस val;
पूर्ण

अटल पूर्णांक aspm_state_cnt(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा tegra_pcie_dw *pcie = (काष्ठा tegra_pcie_dw *)
				     dev_get_drvdata(s->निजी);
	u32 val;

	seq_म_लिखो(s, "Tx L0s entry count : %u\n",
		   event_counter_prog(pcie, EVENT_COUNTER_EVENT_Tx_L0S));

	seq_म_लिखो(s, "Rx L0s entry count : %u\n",
		   event_counter_prog(pcie, EVENT_COUNTER_EVENT_Rx_L0S));

	seq_म_लिखो(s, "Link L1 entry count : %u\n",
		   event_counter_prog(pcie, EVENT_COUNTER_EVENT_L1));

	seq_म_लिखो(s, "Link L1.1 entry count : %u\n",
		   event_counter_prog(pcie, EVENT_COUNTER_EVENT_L1_1));

	seq_म_लिखो(s, "Link L1.2 entry count : %u\n",
		   event_counter_prog(pcie, EVENT_COUNTER_EVENT_L1_2));

	/* Clear all counters */
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, event_cntr_ctrl_offset[pcie->cid],
			   EVENT_COUNTER_ALL_CLEAR);

	/* Re-enable counting */
	val = EVENT_COUNTER_ENABLE_ALL << EVENT_COUNTER_ENABLE_SHIFT;
	val |= EVENT_COUNTER_GROUP_5 << EVENT_COUNTER_GROUP_SEL_SHIFT;
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, event_cntr_ctrl_offset[pcie->cid], val);

	वापस 0;
पूर्ण

अटल व्योम init_host_aspm(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा dw_pcie *pci = &pcie->pci;
	u32 val;

	val = dw_pcie_find_ext_capability(pci, PCI_EXT_CAP_ID_L1SS);
	pcie->cfg_link_cap_l1sub = val + PCI_L1SS_CAP;

	/* Enable ASPM counters */
	val = EVENT_COUNTER_ENABLE_ALL << EVENT_COUNTER_ENABLE_SHIFT;
	val |= EVENT_COUNTER_GROUP_5 << EVENT_COUNTER_GROUP_SEL_SHIFT;
	dw_pcie_ग_लिखोl_dbi(pci, event_cntr_ctrl_offset[pcie->cid], val);

	/* Program T_cmrt and T_pwr_on values */
	val = dw_pcie_पढ़ोl_dbi(pci, pcie->cfg_link_cap_l1sub);
	val &= ~(PCI_L1SS_CAP_CM_RESTORE_TIME | PCI_L1SS_CAP_P_PWR_ON_VALUE);
	val |= (pcie->aspm_cmrt << 8);
	val |= (pcie->aspm_pwr_on_t << 19);
	dw_pcie_ग_लिखोl_dbi(pci, pcie->cfg_link_cap_l1sub, val);

	/* Program L0s and L1 entrance latencies */
	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_PORT_AFR);
	val &= ~PORT_AFR_L0S_ENTRANCE_LAT_MASK;
	val |= (pcie->aspm_l0s_enter_lat << PORT_AFR_L0S_ENTRANCE_LAT_SHIFT);
	val |= PORT_AFR_ENTER_ASPM;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_PORT_AFR, val);
पूर्ण

अटल व्योम init_debugfs(काष्ठा tegra_pcie_dw *pcie)
अणु
	debugfs_create_devm_seqfile(pcie->dev, "aspm_state_cnt", pcie->debugfs,
				    aspm_state_cnt);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम disable_aspm_l12(काष्ठा tegra_pcie_dw *pcie) अणु वापस; पूर्ण
अटल अंतरभूत व्योम disable_aspm_l11(काष्ठा tegra_pcie_dw *pcie) अणु वापस; पूर्ण
अटल अंतरभूत व्योम init_host_aspm(काष्ठा tegra_pcie_dw *pcie) अणु वापस; पूर्ण
अटल अंतरभूत व्योम init_debugfs(काष्ठा tegra_pcie_dw *pcie) अणु वापस; पूर्ण
#पूर्ण_अगर

अटल व्योम tegra_pcie_enable_प्रणाली_पूर्णांकerrupts(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val;
	u16 val_w;

	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L0_0);
	val |= APPL_INTR_EN_L0_0_LINK_STATE_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L0_0);

	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L1_0_0);
	val |= APPL_INTR_EN_L1_0_0_LINK_REQ_RST_NOT_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L1_0_0);

	अगर (pcie->enable_cdm_check) अणु
		val = appl_पढ़ोl(pcie, APPL_INTR_EN_L0_0);
		val |= APPL_INTR_EN_L0_0_CDM_REG_CHK_INT_EN;
		appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L0_0);

		val = appl_पढ़ोl(pcie, APPL_INTR_EN_L1_18);
		val |= APPL_INTR_EN_L1_18_CDM_REG_CHK_CMP_ERR;
		val |= APPL_INTR_EN_L1_18_CDM_REG_CHK_LOGIC_ERR;
		appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L1_18);
	पूर्ण

	val_w = dw_pcie_पढ़ोw_dbi(&pcie->pci, pcie->pcie_cap_base +
				  PCI_EXP_LNKSTA);
	pcie->init_link_width = (val_w & PCI_EXP_LNKSTA_NLW) >>
				PCI_EXP_LNKSTA_NLW_SHIFT;

	val_w = dw_pcie_पढ़ोw_dbi(&pcie->pci, pcie->pcie_cap_base +
				  PCI_EXP_LNKCTL);
	val_w |= PCI_EXP_LNKCTL_LBMIE;
	dw_pcie_ग_लिखोw_dbi(&pcie->pci, pcie->pcie_cap_base + PCI_EXP_LNKCTL,
			   val_w);
पूर्ण

अटल व्योम tegra_pcie_enable_legacy_पूर्णांकerrupts(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val;

	/* Enable legacy पूर्णांकerrupt generation */
	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L0_0);
	val |= APPL_INTR_EN_L0_0_SYS_INTR_EN;
	val |= APPL_INTR_EN_L0_0_INT_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L0_0);

	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L1_8_0);
	val |= APPL_INTR_EN_L1_8_INTX_EN;
	val |= APPL_INTR_EN_L1_8_AUTO_BW_INT_EN;
	val |= APPL_INTR_EN_L1_8_BW_MGT_INT_EN;
	अगर (IS_ENABLED(CONFIG_PCIEAER))
		val |= APPL_INTR_EN_L1_8_AER_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L1_8_0);
पूर्ण

अटल व्योम tegra_pcie_enable_msi_पूर्णांकerrupts(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val;

	/* Enable MSI पूर्णांकerrupt generation */
	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L0_0);
	val |= APPL_INTR_EN_L0_0_SYS_MSI_INTR_EN;
	val |= APPL_INTR_EN_L0_0_MSI_RCV_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L0_0);
पूर्ण

अटल व्योम tegra_pcie_enable_पूर्णांकerrupts(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);

	/* Clear पूर्णांकerrupt statuses beक्रमe enabling पूर्णांकerrupts */
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_0_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_1);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_2);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_3);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_6);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_7);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_8_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_9);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_10);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_11);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_13);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_14);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_15);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_17);

	tegra_pcie_enable_प्रणाली_पूर्णांकerrupts(pp);
	tegra_pcie_enable_legacy_पूर्णांकerrupts(pp);
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_pcie_enable_msi_पूर्णांकerrupts(pp);
पूर्ण

अटल व्योम config_gen3_gen4_eq_presets(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा dw_pcie *pci = &pcie->pci;
	u32 val, offset, i;

	/* Program init preset */
	क्रम (i = 0; i < pcie->num_lanes; i++) अणु
		val = dw_pcie_पढ़ोw_dbi(pci, CAP_SPCIE_CAP_OFF + (i * 2));
		val &= ~CAP_SPCIE_CAP_OFF_DSP_TX_PRESET0_MASK;
		val |= GEN3_GEN4_EQ_PRESET_INIT;
		val &= ~CAP_SPCIE_CAP_OFF_USP_TX_PRESET0_MASK;
		val |= (GEN3_GEN4_EQ_PRESET_INIT <<
			   CAP_SPCIE_CAP_OFF_USP_TX_PRESET0_SHIFT);
		dw_pcie_ग_लिखोw_dbi(pci, CAP_SPCIE_CAP_OFF + (i * 2), val);

		offset = dw_pcie_find_ext_capability(pci,
						     PCI_EXT_CAP_ID_PL_16GT) +
				PCI_PL_16GT_LE_CTRL;
		val = dw_pcie_पढ़ोb_dbi(pci, offset + i);
		val &= ~PCI_PL_16GT_LE_CTRL_DSP_TX_PRESET_MASK;
		val |= GEN3_GEN4_EQ_PRESET_INIT;
		val &= ~PCI_PL_16GT_LE_CTRL_USP_TX_PRESET_MASK;
		val |= (GEN3_GEN4_EQ_PRESET_INIT <<
			PCI_PL_16GT_LE_CTRL_USP_TX_PRESET_SHIFT);
		dw_pcie_ग_लिखोb_dbi(pci, offset + i, val);
	पूर्ण

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_RELATED_OFF);
	val &= ~GEN3_RELATED_OFF_RATE_SHADOW_SEL_MASK;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_RELATED_OFF, val);

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_EQ_CONTROL_OFF);
	val &= ~GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_MASK;
	val |= (0x3ff << GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_SHIFT);
	val &= ~GEN3_EQ_CONTROL_OFF_FB_MODE_MASK;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_EQ_CONTROL_OFF, val);

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_RELATED_OFF);
	val &= ~GEN3_RELATED_OFF_RATE_SHADOW_SEL_MASK;
	val |= (0x1 << GEN3_RELATED_OFF_RATE_SHADOW_SEL_SHIFT);
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_RELATED_OFF, val);

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_EQ_CONTROL_OFF);
	val &= ~GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_MASK;
	val |= (0x360 << GEN3_EQ_CONTROL_OFF_PSET_REQ_VEC_SHIFT);
	val &= ~GEN3_EQ_CONTROL_OFF_FB_MODE_MASK;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_EQ_CONTROL_OFF, val);

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_RELATED_OFF);
	val &= ~GEN3_RELATED_OFF_RATE_SHADOW_SEL_MASK;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_RELATED_OFF, val);
पूर्ण

अटल पूर्णांक tegra_pcie_dw_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val;

	pp->bridge->ops = &tegra_pci_ops;

	अगर (!pcie->pcie_cap_base)
		pcie->pcie_cap_base = dw_pcie_find_capability(&pcie->pci,
							      PCI_CAP_ID_EXP);

	val = dw_pcie_पढ़ोl_dbi(pci, PCI_IO_BASE);
	val &= ~(IO_BASE_IO_DECODE | IO_BASE_IO_DECODE_BIT8);
	dw_pcie_ग_लिखोl_dbi(pci, PCI_IO_BASE, val);

	val = dw_pcie_पढ़ोl_dbi(pci, PCI_PREF_MEMORY_BASE);
	val |= CFG_PREF_MEM_LIMIT_BASE_MEM_DECODE;
	val |= CFG_PREF_MEM_LIMIT_BASE_MEM_LIMIT_DECODE;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_PREF_MEMORY_BASE, val);

	dw_pcie_ग_लिखोl_dbi(pci, PCI_BASE_ADDRESS_0, 0);

	/* Enable as 0xFFFF0001 response क्रम CRS */
	val = dw_pcie_पढ़ोl_dbi(pci, PORT_LOGIC_AMBA_ERROR_RESPONSE_DEFAULT);
	val &= ~(AMBA_ERROR_RESPONSE_CRS_MASK << AMBA_ERROR_RESPONSE_CRS_SHIFT);
	val |= (AMBA_ERROR_RESPONSE_CRS_OKAY_FFFF0001 <<
		AMBA_ERROR_RESPONSE_CRS_SHIFT);
	dw_pcie_ग_लिखोl_dbi(pci, PORT_LOGIC_AMBA_ERROR_RESPONSE_DEFAULT, val);

	/* Configure Max lane width from DT */
	val = dw_pcie_पढ़ोl_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKCAP);
	val &= ~PCI_EXP_LNKCAP_MLW;
	val |= (pcie->num_lanes << PCI_EXP_LNKSTA_NLW_SHIFT);
	dw_pcie_ग_लिखोl_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKCAP, val);

	config_gen3_gen4_eq_presets(pcie);

	init_host_aspm(pcie);

	/* Disable ASPM-L1SS advertisement अगर there is no CLKREQ routing */
	अगर (!pcie->supports_clkreq) अणु
		disable_aspm_l11(pcie);
		disable_aspm_l12(pcie);
	पूर्ण

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_RELATED_OFF);
	val &= ~GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_RELATED_OFF, val);

	अगर (pcie->update_fc_fixup) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, CFG_TIMER_CTRL_MAX_FUNC_NUM_OFF);
		val |= 0x1 << CFG_TIMER_CTRL_ACK_NAK_SHIFT;
		dw_pcie_ग_लिखोl_dbi(pci, CFG_TIMER_CTRL_MAX_FUNC_NUM_OFF, val);
	पूर्ण

	clk_set_rate(pcie->core_clk, GEN4_CORE_CLK_FREQ);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_start_link(काष्ठा dw_pcie *pci)
अणु
	u32 val, offset, speed, पंचांगp;
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	काष्ठा pcie_port *pp = &pci->pp;
	bool retry = true;

	अगर (pcie->mode == DW_PCIE_EP_TYPE) अणु
		enable_irq(pcie->pex_rst_irq);
		वापस 0;
	पूर्ण

retry_link:
	/* Assert RST */
	val = appl_पढ़ोl(pcie, APPL_PINMUX);
	val &= ~APPL_PINMUX_PEX_RST;
	appl_ग_लिखोl(pcie, val, APPL_PINMUX);

	usleep_range(100, 200);

	/* Enable LTSSM */
	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val |= APPL_CTRL_LTSSM_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	/* De-निश्चित RST */
	val = appl_पढ़ोl(pcie, APPL_PINMUX);
	val |= APPL_PINMUX_PEX_RST;
	appl_ग_लिखोl(pcie, val, APPL_PINMUX);

	msleep(100);

	अगर (dw_pcie_रुको_क्रम_link(pci)) अणु
		अगर (!retry)
			वापस 0;
		/*
		 * There are some endpoपूर्णांकs which can't get the link up अगर
		 * root port has Data Link Feature (DLF) enabled.
		 * Refer Spec rev 4.0 ver 1.0 sec 3.4.2 & 7.7.4 क्रम more info
		 * on Scaled Flow Control and DLF.
		 * So, need to confirm that is indeed the हाल here and attempt
		 * link up once again with DLF disabled.
		 */
		val = appl_पढ़ोl(pcie, APPL_DEBUG);
		val &= APPL_DEBUG_LTSSM_STATE_MASK;
		val >>= APPL_DEBUG_LTSSM_STATE_SHIFT;
		पंचांगp = appl_पढ़ोl(pcie, APPL_LINK_STATUS);
		पंचांगp &= APPL_LINK_STATUS_RDLH_LINK_UP;
		अगर (!(val == 0x11 && !पंचांगp)) अणु
			/* Link is करोwn क्रम all good reasons */
			वापस 0;
		पूर्ण

		dev_info(pci->dev, "Link is down in DLL");
		dev_info(pci->dev, "Trying again with DLFE disabled\n");
		/* Disable LTSSM */
		val = appl_पढ़ोl(pcie, APPL_CTRL);
		val &= ~APPL_CTRL_LTSSM_EN;
		appl_ग_लिखोl(pcie, val, APPL_CTRL);

		reset_control_निश्चित(pcie->core_rst);
		reset_control_deनिश्चित(pcie->core_rst);

		offset = dw_pcie_find_ext_capability(pci, PCI_EXT_CAP_ID_DLF);
		val = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_DLF_CAP);
		val &= ~PCI_DLF_EXCHANGE_ENABLE;
		dw_pcie_ग_लिखोl_dbi(pci, offset, val);

		tegra_pcie_dw_host_init(pp);
		dw_pcie_setup_rc(pp);

		retry = false;
		जाओ retry_link;
	पूर्ण

	speed = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKSTA) &
		PCI_EXP_LNKSTA_CLS;
	clk_set_rate(pcie->core_clk, pcie_gen_freq[speed - 1]);

	tegra_pcie_enable_पूर्णांकerrupts(pp);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);
	u32 val = dw_pcie_पढ़ोw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_LNKSTA);

	वापस !!(val & PCI_EXP_LNKSTA_DLLLA);
पूर्ण

अटल व्योम tegra_pcie_dw_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);

	disable_irq(pcie->pex_rst_irq);
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops tegra_dw_pcie_ops = अणु
	.link_up = tegra_pcie_dw_link_up,
	.start_link = tegra_pcie_dw_start_link,
	.stop_link = tegra_pcie_dw_stop_link,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_host_ops tegra_pcie_dw_host_ops = अणु
	.host_init = tegra_pcie_dw_host_init,
पूर्ण;

अटल व्योम tegra_pcie_disable_phy(काष्ठा tegra_pcie_dw *pcie)
अणु
	अचिन्हित पूर्णांक phy_count = pcie->phy_count;

	जबतक (phy_count--) अणु
		phy_घातer_off(pcie->phys[phy_count]);
		phy_निकास(pcie->phys[phy_count]);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_pcie_enable_phy(काष्ठा tegra_pcie_dw *pcie)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < pcie->phy_count; i++) अणु
		ret = phy_init(pcie->phys[i]);
		अगर (ret < 0)
			जाओ phy_घातer_off;

		ret = phy_घातer_on(pcie->phys[i]);
		अगर (ret < 0)
			जाओ phy_निकास;
	पूर्ण

	वापस 0;

phy_घातer_off:
	जबतक (i--) अणु
		phy_घातer_off(pcie->phys[i]);
phy_निकास:
		phy_निकास(pcie->phys[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_parse_dt(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(pcie->dev);
	काष्ठा device_node *np = pcie->dev->of_node;
	पूर्णांक ret;

	pcie->dbi_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	अगर (!pcie->dbi_res) अणु
		dev_err(pcie->dev, "Failed to find \"dbi\" region\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "nvidia,aspm-cmrt-us", &pcie->aspm_cmrt);
	अगर (ret < 0) अणु
		dev_info(pcie->dev, "Failed to read ASPM T_cmrt: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "nvidia,aspm-pwr-on-t-us",
				   &pcie->aspm_pwr_on_t);
	अगर (ret < 0)
		dev_info(pcie->dev, "Failed to read ASPM Power On time: %d\n",
			 ret);

	ret = of_property_पढ़ो_u32(np, "nvidia,aspm-l0s-entrance-latency-us",
				   &pcie->aspm_l0s_enter_lat);
	अगर (ret < 0)
		dev_info(pcie->dev,
			 "Failed to read ASPM L0s Entrance latency: %d\n", ret);

	ret = of_property_पढ़ो_u32(np, "num-lanes", &pcie->num_lanes);
	अगर (ret < 0) अणु
		dev_err(pcie->dev, "Failed to read num-lanes: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "nvidia,bpmp", 1, &pcie->cid);
	अगर (ret) अणु
		dev_err(pcie->dev, "Failed to read Controller-ID: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_count_strings(np, "phy-names");
	अगर (ret < 0) अणु
		dev_err(pcie->dev, "Failed to find PHY entries: %d\n",
			ret);
		वापस ret;
	पूर्ण
	pcie->phy_count = ret;

	अगर (of_property_पढ़ो_bool(np, "nvidia,update-fc-fixup"))
		pcie->update_fc_fixup = true;

	pcie->supports_clkreq =
		of_property_पढ़ो_bool(pcie->dev->of_node, "supports-clkreq");

	pcie->enable_cdm_check =
		of_property_पढ़ो_bool(np, "snps,enable-cdm-check");

	अगर (pcie->mode == DW_PCIE_RC_TYPE)
		वापस 0;

	/* Endpoपूर्णांक mode specअगरic DT entries */
	pcie->pex_rst_gpiod = devm_gpiod_get(pcie->dev, "reset", GPIOD_IN);
	अगर (IS_ERR(pcie->pex_rst_gpiod)) अणु
		पूर्णांक err = PTR_ERR(pcie->pex_rst_gpiod);
		स्थिर अक्षर *level = KERN_ERR;

		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, pcie->dev,
			   dev_fmt("Failed to get PERST GPIO: %d\n"),
			   err);
		वापस err;
	पूर्ण

	pcie->pex_refclk_sel_gpiod = devm_gpiod_get(pcie->dev,
						    "nvidia,refclk-select",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(pcie->pex_refclk_sel_gpiod)) अणु
		पूर्णांक err = PTR_ERR(pcie->pex_refclk_sel_gpiod);
		स्थिर अक्षर *level = KERN_ERR;

		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, pcie->dev,
			   dev_fmt("Failed to get REFCLK select GPIOs: %d\n"),
			   err);
		pcie->pex_refclk_sel_gpiod = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_bpmp_set_ctrl_state(काष्ठा tegra_pcie_dw *pcie,
					  bool enable)
अणु
	काष्ठा mrq_uphy_response resp;
	काष्ठा tegra_bpmp_message msg;
	काष्ठा mrq_uphy_request req;

	/* Controller-5 करोesn't need to have its state set by BPMP-FW */
	अगर (pcie->cid == 5)
		वापस 0;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	req.cmd = CMD_UPHY_PCIE_CONTROLLER_STATE;
	req.controller_state.pcie_controller = pcie->cid;
	req.controller_state.enable = enable;

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_UPHY;
	msg.tx.data = &req;
	msg.tx.size = माप(req);
	msg.rx.data = &resp;
	msg.rx.size = माप(resp);

	वापस tegra_bpmp_transfer(pcie->bpmp, &msg);
पूर्ण

अटल पूर्णांक tegra_pcie_bpmp_set_pll_state(काष्ठा tegra_pcie_dw *pcie,
					 bool enable)
अणु
	काष्ठा mrq_uphy_response resp;
	काष्ठा tegra_bpmp_message msg;
	काष्ठा mrq_uphy_request req;

	स_रखो(&req, 0, माप(req));
	स_रखो(&resp, 0, माप(resp));

	अगर (enable) अणु
		req.cmd = CMD_UPHY_PCIE_EP_CONTROLLER_PLL_INIT;
		req.ep_ctrlr_pll_init.ep_controller = pcie->cid;
	पूर्ण अन्यथा अणु
		req.cmd = CMD_UPHY_PCIE_EP_CONTROLLER_PLL_OFF;
		req.ep_ctrlr_pll_off.ep_controller = pcie->cid;
	पूर्ण

	स_रखो(&msg, 0, माप(msg));
	msg.mrq = MRQ_UPHY;
	msg.tx.data = &req;
	msg.tx.size = माप(req);
	msg.rx.data = &resp;
	msg.rx.size = माप(resp);

	वापस tegra_bpmp_transfer(pcie->bpmp, &msg);
पूर्ण

अटल व्योम tegra_pcie_करोwnstream_dev_to_D0(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा pcie_port *pp = &pcie->pci.pp;
	काष्ठा pci_bus *child, *root_bus = शून्य;
	काष्ठा pci_dev *pdev;

	/*
	 * link करोesn't go पूर्णांकo L2 state with some of the endpoपूर्णांकs with Tegra
	 * अगर they are not in D0 state. So, need to make sure that immediate
	 * करोwnstream devices are in D0 state beक्रमe sending PME_TurnOff to put
	 * link पूर्णांकo L2 state.
	 * This is as per PCI Express Base r4.0 v1.0 September 27-2017,
	 * 5.2 Link State Power Management (Page #428).
	 */

	list_क्रम_each_entry(child, &pp->bridge->bus->children, node) अणु
		/* Bring करोwnstream devices to D0 अगर they are not alपढ़ोy in */
		अगर (child->parent == pp->bridge->bus) अणु
			root_bus = child;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!root_bus) अणु
		dev_err(pcie->dev, "Failed to find downstream devices\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry(pdev, &root_bus->devices, bus_list) अणु
		अगर (PCI_SLOT(pdev->devfn) == 0) अणु
			अगर (pci_set_घातer_state(pdev, PCI_D0))
				dev_err(pcie->dev,
					"Failed to transition %s to D0 state\n",
					dev_name(&pdev->dev));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_pcie_get_slot_regulators(काष्ठा tegra_pcie_dw *pcie)
अणु
	pcie->slot_ctl_3v3 = devm_regulator_get_optional(pcie->dev, "vpcie3v3");
	अगर (IS_ERR(pcie->slot_ctl_3v3)) अणु
		अगर (PTR_ERR(pcie->slot_ctl_3v3) != -ENODEV)
			वापस PTR_ERR(pcie->slot_ctl_3v3);

		pcie->slot_ctl_3v3 = शून्य;
	पूर्ण

	pcie->slot_ctl_12v = devm_regulator_get_optional(pcie->dev, "vpcie12v");
	अगर (IS_ERR(pcie->slot_ctl_12v)) अणु
		अगर (PTR_ERR(pcie->slot_ctl_12v) != -ENODEV)
			वापस PTR_ERR(pcie->slot_ctl_12v);

		pcie->slot_ctl_12v = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_enable_slot_regulators(काष्ठा tegra_pcie_dw *pcie)
अणु
	पूर्णांक ret;

	अगर (pcie->slot_ctl_3v3) अणु
		ret = regulator_enable(pcie->slot_ctl_3v3);
		अगर (ret < 0) अणु
			dev_err(pcie->dev,
				"Failed to enable 3.3V slot supply: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pcie->slot_ctl_12v) अणु
		ret = regulator_enable(pcie->slot_ctl_12v);
		अगर (ret < 0) अणु
			dev_err(pcie->dev,
				"Failed to enable 12V slot supply: %d\n", ret);
			जाओ fail_12v_enable;
		पूर्ण
	पूर्ण

	/*
	 * According to PCI Express Card Electromechanical Specअगरication
	 * Revision 1.1, Table-2.4, T_PVPERL (Power stable to PERST# inactive)
	 * should be a minimum of 100ms.
	 */
	अगर (pcie->slot_ctl_3v3 || pcie->slot_ctl_12v)
		msleep(100);

	वापस 0;

fail_12v_enable:
	अगर (pcie->slot_ctl_3v3)
		regulator_disable(pcie->slot_ctl_3v3);
	वापस ret;
पूर्ण

अटल व्योम tegra_pcie_disable_slot_regulators(काष्ठा tegra_pcie_dw *pcie)
अणु
	अगर (pcie->slot_ctl_12v)
		regulator_disable(pcie->slot_ctl_12v);
	अगर (pcie->slot_ctl_3v3)
		regulator_disable(pcie->slot_ctl_3v3);
पूर्ण

अटल पूर्णांक tegra_pcie_config_controller(काष्ठा tegra_pcie_dw *pcie,
					bool en_hw_hot_rst)
अणु
	पूर्णांक ret;
	u32 val;

	ret = tegra_pcie_bpmp_set_ctrl_state(pcie, true);
	अगर (ret) अणु
		dev_err(pcie->dev,
			"Failed to enable controller %u: %d\n", pcie->cid, ret);
		वापस ret;
	पूर्ण

	ret = tegra_pcie_enable_slot_regulators(pcie);
	अगर (ret < 0)
		जाओ fail_slot_reg_en;

	ret = regulator_enable(pcie->pex_ctl_supply);
	अगर (ret < 0) अणु
		dev_err(pcie->dev, "Failed to enable regulator: %d\n", ret);
		जाओ fail_reg_en;
	पूर्ण

	ret = clk_prepare_enable(pcie->core_clk);
	अगर (ret) अणु
		dev_err(pcie->dev, "Failed to enable core clock: %d\n", ret);
		जाओ fail_core_clk;
	पूर्ण

	ret = reset_control_deनिश्चित(pcie->core_apb_rst);
	अगर (ret) अणु
		dev_err(pcie->dev, "Failed to deassert core APB reset: %d\n",
			ret);
		जाओ fail_core_apb_rst;
	पूर्ण

	अगर (en_hw_hot_rst) अणु
		/* Enable HW_HOT_RST mode */
		val = appl_पढ़ोl(pcie, APPL_CTRL);
		val &= ~(APPL_CTRL_HW_HOT_RST_MODE_MASK <<
			 APPL_CTRL_HW_HOT_RST_MODE_SHIFT);
		val |= APPL_CTRL_HW_HOT_RST_EN;
		appl_ग_लिखोl(pcie, val, APPL_CTRL);
	पूर्ण

	ret = tegra_pcie_enable_phy(pcie);
	अगर (ret) अणु
		dev_err(pcie->dev, "Failed to enable PHY: %d\n", ret);
		जाओ fail_phy;
	पूर्ण

	/* Update CFG base address */
	appl_ग_लिखोl(pcie, pcie->dbi_res->start & APPL_CFG_BASE_ADDR_MASK,
		    APPL_CFG_BASE_ADDR);

	/* Configure this core क्रम RP mode operation */
	appl_ग_लिखोl(pcie, APPL_DM_TYPE_RP, APPL_DM_TYPE);

	appl_ग_लिखोl(pcie, 0x0, APPL_CFG_SLCG_OVERRIDE);

	val = appl_पढ़ोl(pcie, APPL_CTRL);
	appl_ग_लिखोl(pcie, val | APPL_CTRL_SYS_PRE_DET_STATE, APPL_CTRL);

	val = appl_पढ़ोl(pcie, APPL_CFG_MISC);
	val |= (APPL_CFG_MISC_ARCACHE_VAL << APPL_CFG_MISC_ARCACHE_SHIFT);
	appl_ग_लिखोl(pcie, val, APPL_CFG_MISC);

	अगर (!pcie->supports_clkreq) अणु
		val = appl_पढ़ोl(pcie, APPL_PINMUX);
		val |= APPL_PINMUX_CLKREQ_OVERRIDE_EN;
		val &= ~APPL_PINMUX_CLKREQ_OVERRIDE;
		appl_ग_लिखोl(pcie, val, APPL_PINMUX);
	पूर्ण

	/* Update iATU_DMA base address */
	appl_ग_लिखोl(pcie,
		    pcie->atu_dma_res->start & APPL_CFG_IATU_DMA_BASE_ADDR_MASK,
		    APPL_CFG_IATU_DMA_BASE_ADDR);

	reset_control_deनिश्चित(pcie->core_rst);

	वापस ret;

fail_phy:
	reset_control_निश्चित(pcie->core_apb_rst);
fail_core_apb_rst:
	clk_disable_unprepare(pcie->core_clk);
fail_core_clk:
	regulator_disable(pcie->pex_ctl_supply);
fail_reg_en:
	tegra_pcie_disable_slot_regulators(pcie);
fail_slot_reg_en:
	tegra_pcie_bpmp_set_ctrl_state(pcie, false);

	वापस ret;
पूर्ण

अटल व्योम tegra_pcie_unconfig_controller(काष्ठा tegra_pcie_dw *pcie)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(pcie->core_rst);
	अगर (ret)
		dev_err(pcie->dev, "Failed to assert \"core\" reset: %d\n", ret);

	tegra_pcie_disable_phy(pcie);

	ret = reset_control_निश्चित(pcie->core_apb_rst);
	अगर (ret)
		dev_err(pcie->dev, "Failed to assert APB reset: %d\n", ret);

	clk_disable_unprepare(pcie->core_clk);

	ret = regulator_disable(pcie->pex_ctl_supply);
	अगर (ret)
		dev_err(pcie->dev, "Failed to disable regulator: %d\n", ret);

	tegra_pcie_disable_slot_regulators(pcie);

	ret = tegra_pcie_bpmp_set_ctrl_state(pcie, false);
	अगर (ret)
		dev_err(pcie->dev, "Failed to disable controller %d: %d\n",
			pcie->cid, ret);
पूर्ण

अटल पूर्णांक tegra_pcie_init_controller(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा dw_pcie *pci = &pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	पूर्णांक ret;

	ret = tegra_pcie_config_controller(pcie, false);
	अगर (ret < 0)
		वापस ret;

	pp->ops = &tegra_pcie_dw_host_ops;

	ret = dw_pcie_host_init(pp);
	अगर (ret < 0) अणु
		dev_err(pcie->dev, "Failed to add PCIe port: %d\n", ret);
		जाओ fail_host_init;
	पूर्ण

	वापस 0;

fail_host_init:
	tegra_pcie_unconfig_controller(pcie);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_pcie_try_link_l2(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 val;

	अगर (!tegra_pcie_dw_link_up(&pcie->pci))
		वापस 0;

	val = appl_पढ़ोl(pcie, APPL_RADM_STATUS);
	val |= APPL_PM_XMT_TURNOFF_STATE;
	appl_ग_लिखोl(pcie, val, APPL_RADM_STATUS);

	वापस पढ़ोl_poll_समयout_atomic(pcie->appl_base + APPL_DEBUG, val,
				 val & APPL_DEBUG_PM_LINKST_IN_L2_LAT,
				 1, PME_ACK_TIMEOUT);
पूर्ण

अटल व्योम tegra_pcie_dw_pme_turnoff(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 data;
	पूर्णांक err;

	अगर (!tegra_pcie_dw_link_up(&pcie->pci)) अणु
		dev_dbg(pcie->dev, "PCIe link is not up...!\n");
		वापस;
	पूर्ण

	अगर (tegra_pcie_try_link_l2(pcie)) अणु
		dev_info(pcie->dev, "Link didn't transition to L2 state\n");
		/*
		 * TX lane घड़ी freq will reset to Gen1 only अगर link is in L2
		 * or detect state.
		 * So apply pex_rst to end poपूर्णांक to क्रमce RP to go पूर्णांकo detect
		 * state
		 */
		data = appl_पढ़ोl(pcie, APPL_PINMUX);
		data &= ~APPL_PINMUX_PEX_RST;
		appl_ग_लिखोl(pcie, data, APPL_PINMUX);

		/*
		 * Some cards करो not go to detect state even after de-निश्चितing
		 * PERST#. So, de-निश्चित LTSSM to bring link to detect state.
		 */
		data = पढ़ोl(pcie->appl_base + APPL_CTRL);
		data &= ~APPL_CTRL_LTSSM_EN;
		ग_लिखोl(data, pcie->appl_base + APPL_CTRL);

		err = पढ़ोl_poll_समयout_atomic(pcie->appl_base + APPL_DEBUG,
						data,
						((data &
						APPL_DEBUG_LTSSM_STATE_MASK) >>
						APPL_DEBUG_LTSSM_STATE_SHIFT) ==
						LTSSM_STATE_PRE_DETECT,
						1, LTSSM_TIMEOUT);
		अगर (err)
			dev_info(pcie->dev, "Link didn't go to detect state\n");
	पूर्ण
	/*
	 * DBI रेजिस्टरs may not be accessible after this as PLL-E would be
	 * करोwn depending on how CLKREQ is pulled by end poपूर्णांक
	 */
	data = appl_पढ़ोl(pcie, APPL_PINMUX);
	data |= (APPL_PINMUX_CLKREQ_OVERRIDE_EN | APPL_PINMUX_CLKREQ_OVERRIDE);
	/* Cut REFCLK to slot */
	data |= APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE_EN;
	data &= ~APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE;
	appl_ग_लिखोl(pcie, data, APPL_PINMUX);
पूर्ण

अटल व्योम tegra_pcie_deinit_controller(काष्ठा tegra_pcie_dw *pcie)
अणु
	tegra_pcie_करोwnstream_dev_to_D0(pcie);
	dw_pcie_host_deinit(&pcie->pci.pp);
	tegra_pcie_dw_pme_turnoff(pcie);
	tegra_pcie_unconfig_controller(pcie);
पूर्ण

अटल पूर्णांक tegra_pcie_config_rp(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	अक्षर *name;
	पूर्णांक ret;

	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get runtime sync for PCIe dev: %d\n",
			ret);
		जाओ fail_pm_get_sync;
	पूर्ण

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to configure sideband pins: %d\n", ret);
		जाओ fail_pm_get_sync;
	पूर्ण

	ret = tegra_pcie_init_controller(pcie);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to initialize controller: %d\n", ret);
		जाओ fail_pm_get_sync;
	पूर्ण

	pcie->link_state = tegra_pcie_dw_link_up(&pcie->pci);
	अगर (!pcie->link_state) अणु
		ret = -ENOMEDIUM;
		जाओ fail_host_init;
	पूर्ण

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOFP", dev->of_node);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ fail_host_init;
	पूर्ण

	pcie->debugfs = debugfs_create_dir(name, शून्य);
	init_debugfs(pcie);

	वापस ret;

fail_host_init:
	tegra_pcie_deinit_controller(pcie);
fail_pm_get_sync:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल व्योम pex_ep_event_pex_rst_निश्चित(काष्ठा tegra_pcie_dw *pcie)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (pcie->ep_state == EP_STATE_DISABLED)
		वापस;

	/* Disable LTSSM */
	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val &= ~APPL_CTRL_LTSSM_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	ret = पढ़ोl_poll_समयout(pcie->appl_base + APPL_DEBUG, val,
				 ((val & APPL_DEBUG_LTSSM_STATE_MASK) >>
				 APPL_DEBUG_LTSSM_STATE_SHIFT) ==
				 LTSSM_STATE_PRE_DETECT,
				 1, LTSSM_TIMEOUT);
	अगर (ret)
		dev_err(pcie->dev, "Failed to go Detect state: %d\n", ret);

	reset_control_निश्चित(pcie->core_rst);

	tegra_pcie_disable_phy(pcie);

	reset_control_निश्चित(pcie->core_apb_rst);

	clk_disable_unprepare(pcie->core_clk);

	pm_runसमय_put_sync(pcie->dev);

	ret = tegra_pcie_bpmp_set_pll_state(pcie, false);
	अगर (ret)
		dev_err(pcie->dev, "Failed to turn off UPHY: %d\n", ret);

	pcie->ep_state = EP_STATE_DISABLED;
	dev_dbg(pcie->dev, "Uninitialization of endpoint is completed\n");
पूर्ण

अटल व्योम pex_ep_event_pex_rst_deनिश्चित(काष्ठा tegra_pcie_dw *pcie)
अणु
	काष्ठा dw_pcie *pci = &pcie->pci;
	काष्ठा dw_pcie_ep *ep = &pci->ep;
	काष्ठा device *dev = pcie->dev;
	u32 val;
	पूर्णांक ret;

	अगर (pcie->ep_state == EP_STATE_ENABLED)
		वापस;

	ret = pm_runसमय_resume_and_get(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get runtime sync for PCIe dev: %d\n",
			ret);
		वापस;
	पूर्ण

	ret = tegra_pcie_bpmp_set_pll_state(pcie, true);
	अगर (ret) अणु
		dev_err(dev, "Failed to init UPHY for PCIe EP: %d\n", ret);
		जाओ fail_pll_init;
	पूर्ण

	ret = clk_prepare_enable(pcie->core_clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable core clock: %d\n", ret);
		जाओ fail_core_clk_enable;
	पूर्ण

	ret = reset_control_deनिश्चित(pcie->core_apb_rst);
	अगर (ret) अणु
		dev_err(dev, "Failed to deassert core APB reset: %d\n", ret);
		जाओ fail_core_apb_rst;
	पूर्ण

	ret = tegra_pcie_enable_phy(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable PHY: %d\n", ret);
		जाओ fail_phy;
	पूर्ण

	/* Clear any stale पूर्णांकerrupt statuses */
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_0_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_1);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_2);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_3);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_6);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_7);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_8_0);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_9);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_10);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_11);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_13);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_14);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_15);
	appl_ग_लिखोl(pcie, 0xFFFFFFFF, APPL_INTR_STATUS_L1_17);

	/* configure this core क्रम EP mode operation */
	val = appl_पढ़ोl(pcie, APPL_DM_TYPE);
	val &= ~APPL_DM_TYPE_MASK;
	val |= APPL_DM_TYPE_EP;
	appl_ग_लिखोl(pcie, val, APPL_DM_TYPE);

	appl_ग_लिखोl(pcie, 0x0, APPL_CFG_SLCG_OVERRIDE);

	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val |= APPL_CTRL_SYS_PRE_DET_STATE;
	val |= APPL_CTRL_HW_HOT_RST_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	val = appl_पढ़ोl(pcie, APPL_CFG_MISC);
	val |= APPL_CFG_MISC_SLV_EP_MODE;
	val |= (APPL_CFG_MISC_ARCACHE_VAL << APPL_CFG_MISC_ARCACHE_SHIFT);
	appl_ग_लिखोl(pcie, val, APPL_CFG_MISC);

	val = appl_पढ़ोl(pcie, APPL_PINMUX);
	val |= APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE_EN;
	val |= APPL_PINMUX_CLK_OUTPUT_IN_OVERRIDE;
	appl_ग_लिखोl(pcie, val, APPL_PINMUX);

	appl_ग_लिखोl(pcie, pcie->dbi_res->start & APPL_CFG_BASE_ADDR_MASK,
		    APPL_CFG_BASE_ADDR);

	appl_ग_लिखोl(pcie, pcie->atu_dma_res->start &
		    APPL_CFG_IATU_DMA_BASE_ADDR_MASK,
		    APPL_CFG_IATU_DMA_BASE_ADDR);

	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L0_0);
	val |= APPL_INTR_EN_L0_0_SYS_INTR_EN;
	val |= APPL_INTR_EN_L0_0_LINK_STATE_INT_EN;
	val |= APPL_INTR_EN_L0_0_PCI_CMD_EN_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L0_0);

	val = appl_पढ़ोl(pcie, APPL_INTR_EN_L1_0_0);
	val |= APPL_INTR_EN_L1_0_0_HOT_RESET_DONE_INT_EN;
	val |= APPL_INTR_EN_L1_0_0_RDLH_LINK_UP_INT_EN;
	appl_ग_लिखोl(pcie, val, APPL_INTR_EN_L1_0_0);

	reset_control_deनिश्चित(pcie->core_rst);

	अगर (pcie->update_fc_fixup) अणु
		val = dw_pcie_पढ़ोl_dbi(pci, CFG_TIMER_CTRL_MAX_FUNC_NUM_OFF);
		val |= 0x1 << CFG_TIMER_CTRL_ACK_NAK_SHIFT;
		dw_pcie_ग_लिखोl_dbi(pci, CFG_TIMER_CTRL_MAX_FUNC_NUM_OFF, val);
	पूर्ण

	config_gen3_gen4_eq_presets(pcie);

	init_host_aspm(pcie);

	/* Disable ASPM-L1SS advertisement अगर there is no CLKREQ routing */
	अगर (!pcie->supports_clkreq) अणु
		disable_aspm_l11(pcie);
		disable_aspm_l12(pcie);
	पूर्ण

	val = dw_pcie_पढ़ोl_dbi(pci, GEN3_RELATED_OFF);
	val &= ~GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL;
	dw_pcie_ग_लिखोl_dbi(pci, GEN3_RELATED_OFF, val);

	pcie->pcie_cap_base = dw_pcie_find_capability(&pcie->pci,
						      PCI_CAP_ID_EXP);
	clk_set_rate(pcie->core_clk, GEN4_CORE_CLK_FREQ);

	val = (ep->msi_mem_phys & MSIX_ADDR_MATCH_LOW_OFF_MASK);
	val |= MSIX_ADDR_MATCH_LOW_OFF_EN;
	dw_pcie_ग_लिखोl_dbi(pci, MSIX_ADDR_MATCH_LOW_OFF, val);
	val = (lower_32_bits(ep->msi_mem_phys) & MSIX_ADDR_MATCH_HIGH_OFF_MASK);
	dw_pcie_ग_लिखोl_dbi(pci, MSIX_ADDR_MATCH_HIGH_OFF, val);

	ret = dw_pcie_ep_init_complete(ep);
	अगर (ret) अणु
		dev_err(dev, "Failed to complete initialization: %d\n", ret);
		जाओ fail_init_complete;
	पूर्ण

	dw_pcie_ep_init_notअगरy(ep);

	/* Enable LTSSM */
	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val |= APPL_CTRL_LTSSM_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	pcie->ep_state = EP_STATE_ENABLED;
	dev_dbg(dev, "Initialization of endpoint is completed\n");

	वापस;

fail_init_complete:
	reset_control_निश्चित(pcie->core_rst);
	tegra_pcie_disable_phy(pcie);
fail_phy:
	reset_control_निश्चित(pcie->core_apb_rst);
fail_core_apb_rst:
	clk_disable_unprepare(pcie->core_clk);
fail_core_clk_enable:
	tegra_pcie_bpmp_set_pll_state(pcie, false);
fail_pll_init:
	pm_runसमय_put_sync(dev);
पूर्ण

अटल irqवापस_t tegra_pcie_ep_pex_rst_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tegra_pcie_dw *pcie = arg;

	अगर (gpiod_get_value(pcie->pex_rst_gpiod))
		pex_ep_event_pex_rst_निश्चित(pcie);
	अन्यथा
		pex_ep_event_pex_rst_deनिश्चित(pcie);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tegra_pcie_ep_उठाओ_legacy_irq(काष्ठा tegra_pcie_dw *pcie, u16 irq)
अणु
	/* Tegra194 supports only INTA */
	अगर (irq > 1)
		वापस -EINVAL;

	appl_ग_लिखोl(pcie, 1, APPL_LEGACY_INTX);
	usleep_range(1000, 2000);
	appl_ग_लिखोl(pcie, 0, APPL_LEGACY_INTX);
	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_ep_उठाओ_msi_irq(काष्ठा tegra_pcie_dw *pcie, u16 irq)
अणु
	अगर (unlikely(irq > 31))
		वापस -EINVAL;

	appl_ग_लिखोl(pcie, (1 << irq), APPL_MSI_CTRL_1);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_ep_उठाओ_msix_irq(काष्ठा tegra_pcie_dw *pcie, u16 irq)
अणु
	काष्ठा dw_pcie_ep *ep = &pcie->pci.ep;

	ग_लिखोl(irq, ep->msi_mem);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_ep_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				   क्रमागत pci_epc_irq_type type,
				   u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा tegra_pcie_dw *pcie = to_tegra_pcie(pci);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस tegra_pcie_ep_उठाओ_legacy_irq(pcie, पूर्णांकerrupt_num);

	हाल PCI_EPC_IRQ_MSI:
		वापस tegra_pcie_ep_उठाओ_msi_irq(pcie, पूर्णांकerrupt_num);

	हाल PCI_EPC_IRQ_MSIX:
		वापस tegra_pcie_ep_उठाओ_msix_irq(pcie, पूर्णांकerrupt_num);

	शेष:
		dev_err(pci->dev, "Unknown IRQ type\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features tegra_pcie_epc_features = अणु
	.linkup_notअगरier = true,
	.core_init_notअगरier = true,
	.msi_capable = false,
	.msix_capable = false,
	.reserved_bar = 1 << BAR_2 | 1 << BAR_3 | 1 << BAR_4 | 1 << BAR_5,
	.bar_fixed_64bit = 1 << BAR_0,
	.bar_fixed_size[0] = SZ_1M,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
tegra_pcie_ep_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	वापस &tegra_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops pcie_ep_ops = अणु
	.उठाओ_irq = tegra_pcie_ep_उठाओ_irq,
	.get_features = tegra_pcie_ep_get_features,
पूर्ण;

अटल पूर्णांक tegra_pcie_config_ep(काष्ठा tegra_pcie_dw *pcie,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci = &pcie->pci;
	काष्ठा device *dev = pcie->dev;
	काष्ठा dw_pcie_ep *ep;
	अक्षर *name;
	पूर्णांक ret;

	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	ep->page_size = SZ_64K;

	ret = gpiod_set_debounce(pcie->pex_rst_gpiod, PERST_DEBOUNCE_TIME);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set PERST GPIO debounce time: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = gpiod_to_irq(pcie->pex_rst_gpiod);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get IRQ for PERST GPIO: %d\n", ret);
		वापस ret;
	पूर्ण
	pcie->pex_rst_irq = (अचिन्हित पूर्णांक)ret;

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "tegra_pcie_%u_pex_rst_irq",
			      pcie->cid);
	अगर (!name) अणु
		dev_err(dev, "Failed to create PERST IRQ string\n");
		वापस -ENOMEM;
	पूर्ण

	irq_set_status_flags(pcie->pex_rst_irq, IRQ_NOAUTOEN);

	pcie->ep_state = EP_STATE_DISABLED;

	ret = devm_request_thपढ़ोed_irq(dev, pcie->pex_rst_irq, शून्य,
					tegra_pcie_ep_pex_rst_irq,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					name, (व्योम *)pcie);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request IRQ for PERST: %d\n", ret);
		वापस ret;
	पूर्ण

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "tegra_pcie_%u_ep_work",
			      pcie->cid);
	अगर (!name) अणु
		dev_err(dev, "Failed to create PCIe EP work thread string\n");
		वापस -ENOMEM;
	पूर्ण

	pm_runसमय_enable(dev);

	ret = dw_pcie_ep_init(ep);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize DWC Endpoint subsystem: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा tegra_pcie_dw_of_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *atu_dma_res;
	काष्ठा tegra_pcie_dw *pcie;
	काष्ठा pcie_port *pp;
	काष्ठा dw_pcie *pci;
	काष्ठा phy **phys;
	अक्षर *name;
	पूर्णांक ret;
	u32 i;

	data = of_device_get_match_data(dev);

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci = &pcie->pci;
	pci->dev = &pdev->dev;
	pci->ops = &tegra_dw_pcie_ops;
	pci->n_fts[0] = N_FTS_VAL;
	pci->n_fts[1] = FTS_VAL;
	pci->version = 0x490A;

	pp = &pci->pp;
	pp->num_vectors = MAX_MSI_IRQS;
	pcie->dev = &pdev->dev;
	pcie->mode = (क्रमागत dw_pcie_device_mode)data->mode;

	ret = tegra_pcie_dw_parse_dt(pcie);
	अगर (ret < 0) अणु
		स्थिर अक्षर *level = KERN_ERR;

		अगर (ret == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, dev,
			   dev_fmt("Failed to parse device tree: %d\n"),
			   ret);
		वापस ret;
	पूर्ण

	ret = tegra_pcie_get_slot_regulators(pcie);
	अगर (ret < 0) अणु
		स्थिर अक्षर *level = KERN_ERR;

		अगर (ret == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, dev,
			   dev_fmt("Failed to get slot regulators: %d\n"),
			   ret);
		वापस ret;
	पूर्ण

	अगर (pcie->pex_refclk_sel_gpiod)
		gpiod_set_value(pcie->pex_refclk_sel_gpiod, 1);

	pcie->pex_ctl_supply = devm_regulator_get(dev, "vddio-pex-ctl");
	अगर (IS_ERR(pcie->pex_ctl_supply)) अणु
		ret = PTR_ERR(pcie->pex_ctl_supply);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get regulator: %ld\n",
				PTR_ERR(pcie->pex_ctl_supply));
		वापस ret;
	पूर्ण

	pcie->core_clk = devm_clk_get(dev, "core");
	अगर (IS_ERR(pcie->core_clk)) अणु
		dev_err(dev, "Failed to get core clock: %ld\n",
			PTR_ERR(pcie->core_clk));
		वापस PTR_ERR(pcie->core_clk);
	पूर्ण

	pcie->appl_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						      "appl");
	अगर (!pcie->appl_res) अणु
		dev_err(dev, "Failed to find \"appl\" region\n");
		वापस -ENODEV;
	पूर्ण

	pcie->appl_base = devm_ioremap_resource(dev, pcie->appl_res);
	अगर (IS_ERR(pcie->appl_base))
		वापस PTR_ERR(pcie->appl_base);

	pcie->core_apb_rst = devm_reset_control_get(dev, "apb");
	अगर (IS_ERR(pcie->core_apb_rst)) अणु
		dev_err(dev, "Failed to get APB reset: %ld\n",
			PTR_ERR(pcie->core_apb_rst));
		वापस PTR_ERR(pcie->core_apb_rst);
	पूर्ण

	phys = devm_kसुस्मृति(dev, pcie->phy_count, माप(*phys), GFP_KERNEL);
	अगर (!phys)
		वापस -ENOMEM;

	क्रम (i = 0; i < pcie->phy_count; i++) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "p2u-%u", i);
		अगर (!name) अणु
			dev_err(dev, "Failed to create P2U string\n");
			वापस -ENOMEM;
		पूर्ण
		phys[i] = devm_phy_get(dev, name);
		kमुक्त(name);
		अगर (IS_ERR(phys[i])) अणु
			ret = PTR_ERR(phys[i]);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get PHY: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	pcie->phys = phys;

	atu_dma_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "atu_dma");
	अगर (!atu_dma_res) अणु
		dev_err(dev, "Failed to find \"atu_dma\" region\n");
		वापस -ENODEV;
	पूर्ण
	pcie->atu_dma_res = atu_dma_res;

	pci->atu_size = resource_size(atu_dma_res);
	pci->atu_base = devm_ioremap_resource(dev, atu_dma_res);
	अगर (IS_ERR(pci->atu_base))
		वापस PTR_ERR(pci->atu_base);

	pcie->core_rst = devm_reset_control_get(dev, "core");
	अगर (IS_ERR(pcie->core_rst)) अणु
		dev_err(dev, "Failed to get core reset: %ld\n",
			PTR_ERR(pcie->core_rst));
		वापस PTR_ERR(pcie->core_rst);
	पूर्ण

	pp->irq = platक्रमm_get_irq_byname(pdev, "intr");
	अगर (pp->irq < 0)
		वापस pp->irq;

	pcie->bpmp = tegra_bpmp_get(dev);
	अगर (IS_ERR(pcie->bpmp))
		वापस PTR_ERR(pcie->bpmp);

	platक्रमm_set_drvdata(pdev, pcie);

	चयन (pcie->mode) अणु
	हाल DW_PCIE_RC_TYPE:
		ret = devm_request_irq(dev, pp->irq, tegra_pcie_rp_irq_handler,
				       IRQF_SHARED, "tegra-pcie-intr", pcie);
		अगर (ret) अणु
			dev_err(dev, "Failed to request IRQ %d: %d\n", pp->irq,
				ret);
			जाओ fail;
		पूर्ण

		ret = tegra_pcie_config_rp(pcie);
		अगर (ret && ret != -ENOMEDIUM)
			जाओ fail;
		अन्यथा
			वापस 0;
		अवरोध;

	हाल DW_PCIE_EP_TYPE:
		ret = devm_request_thपढ़ोed_irq(dev, pp->irq,
						tegra_pcie_ep_hard_irq,
						tegra_pcie_ep_irq_thपढ़ो,
						IRQF_SHARED | IRQF_ONESHOT,
						"tegra-pcie-ep-intr", pcie);
		अगर (ret) अणु
			dev_err(dev, "Failed to request IRQ %d: %d\n", pp->irq,
				ret);
			जाओ fail;
		पूर्ण

		ret = tegra_pcie_config_ep(pcie, pdev);
		अगर (ret < 0)
			जाओ fail;
		अवरोध;

	शेष:
		dev_err(dev, "Invalid PCIe device type %d\n", pcie->mode);
	पूर्ण

fail:
	tegra_bpmp_put(pcie->bpmp);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_pcie_dw *pcie = platक्रमm_get_drvdata(pdev);

	अगर (!pcie->link_state)
		वापस 0;

	debugfs_हटाओ_recursive(pcie->debugfs);
	tegra_pcie_deinit_controller(pcie);
	pm_runसमय_put_sync(pcie->dev);
	pm_runसमय_disable(pcie->dev);
	tegra_bpmp_put(pcie->bpmp);
	अगर (pcie->pex_refclk_sel_gpiod)
		gpiod_set_value(pcie->pex_refclk_sel_gpiod, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie_dw *pcie = dev_get_drvdata(dev);
	u32 val;

	अगर (!pcie->link_state)
		वापस 0;

	/* Enable HW_HOT_RST mode */
	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val &= ~(APPL_CTRL_HW_HOT_RST_MODE_MASK <<
		 APPL_CTRL_HW_HOT_RST_MODE_SHIFT);
	val |= APPL_CTRL_HW_HOT_RST_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie_dw *pcie = dev_get_drvdata(dev);

	अगर (!pcie->link_state)
		वापस 0;

	/* Save MSI पूर्णांकerrupt vector */
	pcie->msi_ctrl_पूर्णांक = dw_pcie_पढ़ोl_dbi(&pcie->pci,
					       PORT_LOGIC_MSI_CTRL_INT_0_EN);
	tegra_pcie_करोwnstream_dev_to_D0(pcie);
	tegra_pcie_dw_pme_turnoff(pcie);
	tegra_pcie_unconfig_controller(pcie);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie_dw *pcie = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!pcie->link_state)
		वापस 0;

	ret = tegra_pcie_config_controller(pcie, true);
	अगर (ret < 0)
		वापस ret;

	ret = tegra_pcie_dw_host_init(&pcie->pci.pp);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to init host: %d\n", ret);
		जाओ fail_host_init;
	पूर्ण

	ret = tegra_pcie_dw_start_link(&pcie->pci);
	अगर (ret < 0)
		जाओ fail_host_init;

	/* Restore MSI पूर्णांकerrupt vector */
	dw_pcie_ग_लिखोl_dbi(&pcie->pci, PORT_LOGIC_MSI_CTRL_INT_0_EN,
			   pcie->msi_ctrl_पूर्णांक);

	वापस 0;

fail_host_init:
	tegra_pcie_unconfig_controller(pcie);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_pcie_dw_resume_early(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie_dw *pcie = dev_get_drvdata(dev);
	u32 val;

	अगर (!pcie->link_state)
		वापस 0;

	/* Disable HW_HOT_RST mode */
	val = appl_पढ़ोl(pcie, APPL_CTRL);
	val &= ~(APPL_CTRL_HW_HOT_RST_MODE_MASK <<
		 APPL_CTRL_HW_HOT_RST_MODE_SHIFT);
	val |= APPL_CTRL_HW_HOT_RST_MODE_IMDT_RST <<
	       APPL_CTRL_HW_HOT_RST_MODE_SHIFT;
	val &= ~APPL_CTRL_HW_HOT_RST_EN;
	appl_ग_लिखोl(pcie, val, APPL_CTRL);

	वापस 0;
पूर्ण

अटल व्योम tegra_pcie_dw_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_pcie_dw *pcie = platक्रमm_get_drvdata(pdev);

	अगर (!pcie->link_state)
		वापस;

	debugfs_हटाओ_recursive(pcie->debugfs);
	tegra_pcie_करोwnstream_dev_to_D0(pcie);

	disable_irq(pcie->pci.pp.irq);
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		disable_irq(pcie->pci.pp.msi_irq);

	tegra_pcie_dw_pme_turnoff(pcie);
	tegra_pcie_unconfig_controller(pcie);
पूर्ण

अटल स्थिर काष्ठा tegra_pcie_dw_of_data tegra_pcie_dw_rc_of_data = अणु
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_dw_of_data tegra_pcie_dw_ep_of_data = अणु
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_pcie_dw_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra194-pcie",
		.data = &tegra_pcie_dw_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra194-pcie-ep",
		.data = &tegra_pcie_dw_ep_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops tegra_pcie_dw_pm_ops = अणु
	.suspend_late = tegra_pcie_dw_suspend_late,
	.suspend_noirq = tegra_pcie_dw_suspend_noirq,
	.resume_noirq = tegra_pcie_dw_resume_noirq,
	.resume_early = tegra_pcie_dw_resume_early,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_pcie_dw_driver = अणु
	.probe = tegra_pcie_dw_probe,
	.हटाओ = tegra_pcie_dw_हटाओ,
	.shutकरोwn = tegra_pcie_dw_shutकरोwn,
	.driver = अणु
		.name	= "tegra194-pcie",
		.pm = &tegra_pcie_dw_pm_ops,
		.of_match_table = tegra_pcie_dw_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_pcie_dw_driver);

MODULE_DEVICE_TABLE(of, tegra_pcie_dw_of_match);

MODULE_AUTHOR("Vidya Sagar <vidyas@nvidia.com>");
MODULE_DESCRIPTION("NVIDIA PCIe host controller driver");
MODULE_LICENSE("GPL v2");
