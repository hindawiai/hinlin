<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PCIe host controller driver क्रम Tegra SoCs
 *
 * Copyright (c) 2010, CompuLab, Ltd.
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Based on NVIDIA PCIe driver
 * Copyright (c) 2008-2009, NVIDIA Corporation.
 *
 * Bits taken from arch/arm/mach-करोve/pcie.c
 *
 * Author: Thierry Reding <treding@nvidia.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <soc/tegra/cpuidle.h>
#समावेश <soc/tegra/pmc.h>

#समावेश "../pci.h"

#घोषणा INT_PCI_MSI_NR (8 * 32)

/* रेजिस्टर definitions */

#घोषणा AFI_AXI_BAR0_SZ	0x00
#घोषणा AFI_AXI_BAR1_SZ	0x04
#घोषणा AFI_AXI_BAR2_SZ	0x08
#घोषणा AFI_AXI_BAR3_SZ	0x0c
#घोषणा AFI_AXI_BAR4_SZ	0x10
#घोषणा AFI_AXI_BAR5_SZ	0x14

#घोषणा AFI_AXI_BAR0_START	0x18
#घोषणा AFI_AXI_BAR1_START	0x1c
#घोषणा AFI_AXI_BAR2_START	0x20
#घोषणा AFI_AXI_BAR3_START	0x24
#घोषणा AFI_AXI_BAR4_START	0x28
#घोषणा AFI_AXI_BAR5_START	0x2c

#घोषणा AFI_FPCI_BAR0	0x30
#घोषणा AFI_FPCI_BAR1	0x34
#घोषणा AFI_FPCI_BAR2	0x38
#घोषणा AFI_FPCI_BAR3	0x3c
#घोषणा AFI_FPCI_BAR4	0x40
#घोषणा AFI_FPCI_BAR5	0x44

#घोषणा AFI_CACHE_BAR0_SZ	0x48
#घोषणा AFI_CACHE_BAR0_ST	0x4c
#घोषणा AFI_CACHE_BAR1_SZ	0x50
#घोषणा AFI_CACHE_BAR1_ST	0x54

#घोषणा AFI_MSI_BAR_SZ		0x60
#घोषणा AFI_MSI_FPCI_BAR_ST	0x64
#घोषणा AFI_MSI_AXI_BAR_ST	0x68

#घोषणा AFI_MSI_VEC(x)		(0x6c + ((x) * 4))
#घोषणा AFI_MSI_EN_VEC(x)	(0x8c + ((x) * 4))

#घोषणा AFI_CONFIGURATION		0xac
#घोषणा  AFI_CONFIGURATION_EN_FPCI		(1 << 0)
#घोषणा  AFI_CONFIGURATION_CLKEN_OVERRIDE	(1 << 31)

#घोषणा AFI_FPCI_ERROR_MASKS	0xb0

#घोषणा AFI_INTR_MASK		0xb4
#घोषणा  AFI_INTR_MASK_INT_MASK	(1 << 0)
#घोषणा  AFI_INTR_MASK_MSI_MASK	(1 << 8)

#घोषणा AFI_INTR_CODE			0xb8
#घोषणा  AFI_INTR_CODE_MASK		0xf
#घोषणा  AFI_INTR_INI_SLAVE_ERROR	1
#घोषणा  AFI_INTR_INI_DECODE_ERROR	2
#घोषणा  AFI_INTR_TARGET_ABORT		3
#घोषणा  AFI_INTR_MASTER_ABORT		4
#घोषणा  AFI_INTR_INVALID_WRITE		5
#घोषणा  AFI_INTR_LEGACY		6
#घोषणा  AFI_INTR_FPCI_DECODE_ERROR	7
#घोषणा  AFI_INTR_AXI_DECODE_ERROR	8
#घोषणा  AFI_INTR_FPCI_TIMEOUT		9
#घोषणा  AFI_INTR_PE_PRSNT_SENSE	10
#घोषणा  AFI_INTR_PE_CLKREQ_SENSE	11
#घोषणा  AFI_INTR_CLKCLAMP_SENSE	12
#घोषणा  AFI_INTR_RDY4PD_SENSE		13
#घोषणा  AFI_INTR_P2P_ERROR		14

#घोषणा AFI_INTR_SIGNATURE	0xbc
#घोषणा AFI_UPPER_FPCI_ADDRESS	0xc0
#घोषणा AFI_SM_INTR_ENABLE	0xc4
#घोषणा  AFI_SM_INTR_INTA_ASSERT	(1 << 0)
#घोषणा  AFI_SM_INTR_INTB_ASSERT	(1 << 1)
#घोषणा  AFI_SM_INTR_INTC_ASSERT	(1 << 2)
#घोषणा  AFI_SM_INTR_INTD_ASSERT	(1 << 3)
#घोषणा  AFI_SM_INTR_INTA_DEASSERT	(1 << 4)
#घोषणा  AFI_SM_INTR_INTB_DEASSERT	(1 << 5)
#घोषणा  AFI_SM_INTR_INTC_DEASSERT	(1 << 6)
#घोषणा  AFI_SM_INTR_INTD_DEASSERT	(1 << 7)

#घोषणा AFI_AFI_INTR_ENABLE		0xc8
#घोषणा  AFI_INTR_EN_INI_SLVERR		(1 << 0)
#घोषणा  AFI_INTR_EN_INI_DECERR		(1 << 1)
#घोषणा  AFI_INTR_EN_TGT_SLVERR		(1 << 2)
#घोषणा  AFI_INTR_EN_TGT_DECERR		(1 << 3)
#घोषणा  AFI_INTR_EN_TGT_WRERR		(1 << 4)
#घोषणा  AFI_INTR_EN_DFPCI_DECERR	(1 << 5)
#घोषणा  AFI_INTR_EN_AXI_DECERR		(1 << 6)
#घोषणा  AFI_INTR_EN_FPCI_TIMEOUT	(1 << 7)
#घोषणा  AFI_INTR_EN_PRSNT_SENSE	(1 << 8)

#घोषणा AFI_PCIE_PME		0xf0

#घोषणा AFI_PCIE_CONFIG					0x0f8
#घोषणा  AFI_PCIE_CONFIG_PCIE_DISABLE(x)		(1 << ((x) + 1))
#घोषणा  AFI_PCIE_CONFIG_PCIE_DISABLE_ALL		0xe
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_MASK	(0xf << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE	(0x0 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420	(0x0 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1	(0x0 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_401	(0x0 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL	(0x1 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222	(0x1 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1	(0x1 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211	(0x1 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411	(0x2 << 20)
#घोषणा  AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_111	(0x2 << 20)
#घोषणा  AFI_PCIE_CONFIG_PCIE_CLKREQ_GPIO(x)		(1 << ((x) + 29))
#घोषणा  AFI_PCIE_CONFIG_PCIE_CLKREQ_GPIO_ALL		(0x7 << 29)

#घोषणा AFI_FUSE			0x104
#घोषणा  AFI_FUSE_PCIE_T0_GEN2_DIS	(1 << 2)

#घोषणा AFI_PEX0_CTRL			0x110
#घोषणा AFI_PEX1_CTRL			0x118
#घोषणा  AFI_PEX_CTRL_RST		(1 << 0)
#घोषणा  AFI_PEX_CTRL_CLKREQ_EN		(1 << 1)
#घोषणा  AFI_PEX_CTRL_REFCLK_EN		(1 << 3)
#घोषणा  AFI_PEX_CTRL_OVERRIDE_EN	(1 << 4)

#घोषणा AFI_PLLE_CONTROL		0x160
#घोषणा  AFI_PLLE_CONTROL_BYPASS_PADS2PLLE_CONTROL (1 << 9)
#घोषणा  AFI_PLLE_CONTROL_PADS2PLLE_CONTROL_EN (1 << 1)

#घोषणा AFI_PEXBIAS_CTRL_0		0x168

#घोषणा RP_ECTL_2_R1	0x00000e84
#घोषणा  RP_ECTL_2_R1_RX_CTLE_1C_MASK		0xffff

#घोषणा RP_ECTL_4_R1	0x00000e8c
#घोषणा  RP_ECTL_4_R1_RX_CDR_CTRL_1C_MASK	(0xffff << 16)
#घोषणा  RP_ECTL_4_R1_RX_CDR_CTRL_1C_SHIFT	16

#घोषणा RP_ECTL_5_R1	0x00000e90
#घोषणा  RP_ECTL_5_R1_RX_EQ_CTRL_L_1C_MASK	0xffffffff

#घोषणा RP_ECTL_6_R1	0x00000e94
#घोषणा  RP_ECTL_6_R1_RX_EQ_CTRL_H_1C_MASK	0xffffffff

#घोषणा RP_ECTL_2_R2	0x00000ea4
#घोषणा  RP_ECTL_2_R2_RX_CTLE_1C_MASK	0xffff

#घोषणा RP_ECTL_4_R2	0x00000eac
#घोषणा  RP_ECTL_4_R2_RX_CDR_CTRL_1C_MASK	(0xffff << 16)
#घोषणा  RP_ECTL_4_R2_RX_CDR_CTRL_1C_SHIFT	16

#घोषणा RP_ECTL_5_R2	0x00000eb0
#घोषणा  RP_ECTL_5_R2_RX_EQ_CTRL_L_1C_MASK	0xffffffff

#घोषणा RP_ECTL_6_R2	0x00000eb4
#घोषणा  RP_ECTL_6_R2_RX_EQ_CTRL_H_1C_MASK	0xffffffff

#घोषणा RP_VEND_XP	0x00000f00
#घोषणा  RP_VEND_XP_DL_UP			(1 << 30)
#घोषणा  RP_VEND_XP_OPPORTUNISTIC_ACK		(1 << 27)
#घोषणा  RP_VEND_XP_OPPORTUNISTIC_UPDATEFC	(1 << 28)
#घोषणा  RP_VEND_XP_UPDATE_FC_THRESHOLD_MASK	(0xff << 18)

#घोषणा RP_VEND_CTL0	0x00000f44
#घोषणा  RP_VEND_CTL0_DSK_RST_PULSE_WIDTH_MASK	(0xf << 12)
#घोषणा  RP_VEND_CTL0_DSK_RST_PULSE_WIDTH	(0x9 << 12)

#घोषणा RP_VEND_CTL1	0x00000f48
#घोषणा  RP_VEND_CTL1_ERPT	(1 << 13)

#घोषणा RP_VEND_XP_BIST	0x00000f4c
#घोषणा  RP_VEND_XP_BIST_GOTO_L1_L2_AFTER_DLLP_DONE	(1 << 28)

#घोषणा RP_VEND_CTL2 0x00000fa8
#घोषणा  RP_VEND_CTL2_PCA_ENABLE (1 << 7)

#घोषणा RP_PRIV_MISC	0x00000fe0
#घोषणा  RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT		(0xe << 0)
#घोषणा  RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT		(0xf << 0)
#घोषणा  RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD_MASK	(0x7f << 16)
#घोषणा  RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD		(0xf << 16)
#घोषणा  RP_PRIV_MISC_CTLR_CLK_CLAMP_ENABLE		(1 << 23)
#घोषणा  RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD_MASK	(0x7f << 24)
#घोषणा  RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD		(0xf << 24)
#घोषणा  RP_PRIV_MISC_TMS_CLK_CLAMP_ENABLE		(1 << 31)

#घोषणा RP_LINK_CONTROL_STATUS			0x00000090
#घोषणा  RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE	0x20000000
#घोषणा  RP_LINK_CONTROL_STATUS_LINKSTAT_MASK	0x3fff0000

#घोषणा RP_LINK_CONTROL_STATUS_2		0x000000b0

#घोषणा PADS_CTL_SEL		0x0000009c

#घोषणा PADS_CTL		0x000000a0
#घोषणा  PADS_CTL_IDDQ_1L	(1 << 0)
#घोषणा  PADS_CTL_TX_DATA_EN_1L	(1 << 6)
#घोषणा  PADS_CTL_RX_DATA_EN_1L	(1 << 10)

#घोषणा PADS_PLL_CTL_TEGRA20			0x000000b8
#घोषणा PADS_PLL_CTL_TEGRA30			0x000000b4
#घोषणा  PADS_PLL_CTL_RST_B4SM			(1 << 1)
#घोषणा  PADS_PLL_CTL_LOCKDET			(1 << 8)
#घोषणा  PADS_PLL_CTL_REFCLK_MASK		(0x3 << 16)
#घोषणा  PADS_PLL_CTL_REFCLK_INTERNAL_CML	(0 << 16)
#घोषणा  PADS_PLL_CTL_REFCLK_INTERNAL_CMOS	(1 << 16)
#घोषणा  PADS_PLL_CTL_REFCLK_EXTERNAL		(2 << 16)
#घोषणा  PADS_PLL_CTL_TXCLKREF_MASK		(0x1 << 20)
#घोषणा  PADS_PLL_CTL_TXCLKREF_DIV10		(0 << 20)
#घोषणा  PADS_PLL_CTL_TXCLKREF_DIV5		(1 << 20)
#घोषणा  PADS_PLL_CTL_TXCLKREF_BUF_EN		(1 << 22)

#घोषणा PADS_REFCLK_CFG0			0x000000c8
#घोषणा PADS_REFCLK_CFG1			0x000000cc
#घोषणा PADS_REFCLK_BIAS			0x000000d0

/*
 * Fields in PADS_REFCLK_CFG*. Those रेजिस्टरs क्रमm an array of 16-bit
 * entries, one entry per PCIe port. These field definitions and desired
 * values aren't in the TRM, but करो come from NVIDIA.
 */
#घोषणा PADS_REFCLK_CFG_TERM_SHIFT		2  /* 6:2 */
#घोषणा PADS_REFCLK_CFG_E_TERM_SHIFT		7
#घोषणा PADS_REFCLK_CFG_PREDI_SHIFT		8  /* 11:8 */
#घोषणा PADS_REFCLK_CFG_DRVI_SHIFT		12 /* 15:12 */

#घोषणा PME_ACK_TIMEOUT 10000
#घोषणा LINK_RETRAIN_TIMEOUT 100000 /* in usec */

काष्ठा tegra_msi अणु
	DECLARE_BITMAP(used, INT_PCI_MSI_NR);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा mutex map_lock;
	spinlock_t mask_lock;
	व्योम *virt;
	dma_addr_t phys;
	पूर्णांक irq;
पूर्ण;

/* used to dअगरferentiate between Tegra SoC generations */
काष्ठा tegra_pcie_port_soc अणु
	काष्ठा अणु
		u8 turnoff_bit;
		u8 ack_bit;
	पूर्ण pme;
पूर्ण;

काष्ठा tegra_pcie_soc अणु
	अचिन्हित पूर्णांक num_ports;
	स्थिर काष्ठा tegra_pcie_port_soc *ports;
	अचिन्हित पूर्णांक msi_base_shअगरt;
	अचिन्हित दीर्घ afi_pex2_ctrl;
	u32 pads_pll_ctl;
	u32 tx_ref_sel;
	u32 pads_refclk_cfg0;
	u32 pads_refclk_cfg1;
	u32 update_fc_threshold;
	bool has_pex_clkreq_en;
	bool has_pex_bias_ctrl;
	bool has_पूर्णांकr_prsnt_sense;
	bool has_cml_clk;
	bool has_gen2;
	bool क्रमce_pca_enable;
	bool program_uphy;
	bool update_clamp_threshold;
	bool program_deskew_समय;
	bool update_fc_समयr;
	bool has_cache_bars;
	काष्ठा अणु
		काष्ठा अणु
			u32 rp_ectl_2_r1;
			u32 rp_ectl_4_r1;
			u32 rp_ectl_5_r1;
			u32 rp_ectl_6_r1;
			u32 rp_ectl_2_r2;
			u32 rp_ectl_4_r2;
			u32 rp_ectl_5_r2;
			u32 rp_ectl_6_r2;
		पूर्ण regs;
		bool enable;
	पूर्ण ectl;
पूर्ण;

काष्ठा tegra_pcie अणु
	काष्ठा device *dev;

	व्योम __iomem *pads;
	व्योम __iomem *afi;
	व्योम __iomem *cfg;
	पूर्णांक irq;

	काष्ठा resource cs;

	काष्ठा clk *pex_clk;
	काष्ठा clk *afi_clk;
	काष्ठा clk *pll_e;
	काष्ठा clk *cml_clk;

	काष्ठा reset_control *pex_rst;
	काष्ठा reset_control *afi_rst;
	काष्ठा reset_control *pcie_xrst;

	bool legacy_phy;
	काष्ठा phy *phy;

	काष्ठा tegra_msi msi;

	काष्ठा list_head ports;
	u32 xbar_config;

	काष्ठा regulator_bulk_data *supplies;
	अचिन्हित पूर्णांक num_supplies;

	स्थिर काष्ठा tegra_pcie_soc *soc;
	काष्ठा dentry *debugfs;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_pcie *msi_to_pcie(काष्ठा tegra_msi *msi)
अणु
	वापस container_of(msi, काष्ठा tegra_pcie, msi);
पूर्ण

काष्ठा tegra_pcie_port अणु
	काष्ठा tegra_pcie *pcie;
	काष्ठा device_node *np;
	काष्ठा list_head list;
	काष्ठा resource regs;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक lanes;

	काष्ठा phy **phys;

	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

काष्ठा tegra_pcie_bus अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक nr;
पूर्ण;

अटल अंतरभूत व्योम afi_ग_लिखोl(काष्ठा tegra_pcie *pcie, u32 value,
			      अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, pcie->afi + offset);
पूर्ण

अटल अंतरभूत u32 afi_पढ़ोl(काष्ठा tegra_pcie *pcie, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(pcie->afi + offset);
पूर्ण

अटल अंतरभूत व्योम pads_ग_लिखोl(काष्ठा tegra_pcie *pcie, u32 value,
			       अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(value, pcie->pads + offset);
पूर्ण

अटल अंतरभूत u32 pads_पढ़ोl(काष्ठा tegra_pcie *pcie, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(pcie->pads + offset);
पूर्ण

/*
 * The configuration space mapping on Tegra is somewhat similar to the ECAM
 * defined by PCIe. However it deviates a bit in how the 4 bits क्रम extended
 * रेजिस्टर accesses are mapped:
 *
 *    [27:24] extended रेजिस्टर number
 *    [23:16] bus number
 *    [15:11] device number
 *    [10: 8] function number
 *    [ 7: 0] रेजिस्टर number
 *
 * Mapping the whole extended configuration space would require 256 MiB of
 * भव address space, only a small part of which will actually be used.
 *
 * To work around this, a 4 KiB region is used to generate the required
 * configuration transaction with relevant B:D:F and रेजिस्टर offset values.
 * This is achieved by dynamically programming base address and size of
 * AFI_AXI_BAR used क्रम end poपूर्णांक config space mapping to make sure that the
 * address (access to which generates correct config transaction) falls in
 * this 4 KiB region.
 */
अटल अचिन्हित पूर्णांक tegra_pcie_conf_offset(u8 bus, अचिन्हित पूर्णांक devfn,
					   अचिन्हित पूर्णांक where)
अणु
	वापस ((where & 0xf00) << 16) | (bus << 16) | (PCI_SLOT(devfn) << 11) |
	       (PCI_FUNC(devfn) << 8) | (where & 0xff);
पूर्ण

अटल व्योम __iomem *tegra_pcie_map_bus(काष्ठा pci_bus *bus,
					अचिन्हित पूर्णांक devfn,
					पूर्णांक where)
अणु
	काष्ठा tegra_pcie *pcie = bus->sysdata;
	व्योम __iomem *addr = शून्य;

	अगर (bus->number == 0) अणु
		अचिन्हित पूर्णांक slot = PCI_SLOT(devfn);
		काष्ठा tegra_pcie_port *port;

		list_क्रम_each_entry(port, &pcie->ports, list) अणु
			अगर (port->index + 1 == slot) अणु
				addr = port->base + (where & ~3);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक offset;
		u32 base;

		offset = tegra_pcie_conf_offset(bus->number, devfn, where);

		/* move 4 KiB winकरोw to offset within the FPCI region */
		base = 0xfe100000 + ((offset & ~(SZ_4K - 1)) >> 8);
		afi_ग_लिखोl(pcie, base, AFI_FPCI_BAR0);

		/* move to correct offset within the 4 KiB page */
		addr = pcie->cfg + (offset & (SZ_4K - 1));
	पूर्ण

	वापस addr;
पूर्ण

अटल पूर्णांक tegra_pcie_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				  पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	अगर (bus->number == 0)
		वापस pci_generic_config_पढ़ो32(bus, devfn, where, size,
						 value);

	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, value);
पूर्ण

अटल पूर्णांक tegra_pcie_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 value)
अणु
	अगर (bus->number == 0)
		वापस pci_generic_config_ग_लिखो32(bus, devfn, where, size,
						  value);

	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, value);
पूर्ण

अटल काष्ठा pci_ops tegra_pcie_ops = अणु
	.map_bus = tegra_pcie_map_bus,
	.पढ़ो = tegra_pcie_config_पढ़ो,
	.ग_लिखो = tegra_pcie_config_ग_लिखो,
पूर्ण;

अटल अचिन्हित दीर्घ tegra_pcie_port_get_pex_ctrl(काष्ठा tegra_pcie_port *port)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	अचिन्हित दीर्घ ret = 0;

	चयन (port->index) अणु
	हाल 0:
		ret = AFI_PEX0_CTRL;
		अवरोध;

	हाल 1:
		ret = AFI_PEX1_CTRL;
		अवरोध;

	हाल 2:
		ret = soc->afi_pex2_ctrl;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tegra_pcie_port_reset(काष्ठा tegra_pcie_port *port)
अणु
	अचिन्हित दीर्घ ctrl = tegra_pcie_port_get_pex_ctrl(port);
	अचिन्हित दीर्घ value;

	/* pulse reset संकेत */
	अगर (port->reset_gpio) अणु
		gpiod_set_value(port->reset_gpio, 1);
	पूर्ण अन्यथा अणु
		value = afi_पढ़ोl(port->pcie, ctrl);
		value &= ~AFI_PEX_CTRL_RST;
		afi_ग_लिखोl(port->pcie, value, ctrl);
	पूर्ण

	usleep_range(1000, 2000);

	अगर (port->reset_gpio) अणु
		gpiod_set_value(port->reset_gpio, 0);
	पूर्ण अन्यथा अणु
		value = afi_पढ़ोl(port->pcie, ctrl);
		value |= AFI_PEX_CTRL_RST;
		afi_ग_लिखोl(port->pcie, value, ctrl);
	पूर्ण
पूर्ण

अटल व्योम tegra_pcie_enable_rp_features(काष्ठा tegra_pcie_port *port)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	u32 value;

	/* Enable AER capability */
	value = पढ़ोl(port->base + RP_VEND_CTL1);
	value |= RP_VEND_CTL1_ERPT;
	ग_लिखोl(value, port->base + RP_VEND_CTL1);

	/* Optimal settings to enhance bandwidth */
	value = पढ़ोl(port->base + RP_VEND_XP);
	value |= RP_VEND_XP_OPPORTUNISTIC_ACK;
	value |= RP_VEND_XP_OPPORTUNISTIC_UPDATEFC;
	ग_लिखोl(value, port->base + RP_VEND_XP);

	/*
	 * LTSSM will रुको क्रम DLLP to finish beक्रमe entering L1 or L2,
	 * to aव्योम truncation of PM messages which results in receiver errors
	 */
	value = पढ़ोl(port->base + RP_VEND_XP_BIST);
	value |= RP_VEND_XP_BIST_GOTO_L1_L2_AFTER_DLLP_DONE;
	ग_लिखोl(value, port->base + RP_VEND_XP_BIST);

	value = पढ़ोl(port->base + RP_PRIV_MISC);
	value |= RP_PRIV_MISC_CTLR_CLK_CLAMP_ENABLE;
	value |= RP_PRIV_MISC_TMS_CLK_CLAMP_ENABLE;

	अगर (soc->update_clamp_threshold) अणु
		value &= ~(RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD_MASK |
				RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD_MASK);
		value |= RP_PRIV_MISC_CTLR_CLK_CLAMP_THRESHOLD |
			RP_PRIV_MISC_TMS_CLK_CLAMP_THRESHOLD;
	पूर्ण

	ग_लिखोl(value, port->base + RP_PRIV_MISC);
पूर्ण

अटल व्योम tegra_pcie_program_ectl_settings(काष्ठा tegra_pcie_port *port)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	u32 value;

	value = पढ़ोl(port->base + RP_ECTL_2_R1);
	value &= ~RP_ECTL_2_R1_RX_CTLE_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_2_r1;
	ग_लिखोl(value, port->base + RP_ECTL_2_R1);

	value = पढ़ोl(port->base + RP_ECTL_4_R1);
	value &= ~RP_ECTL_4_R1_RX_CDR_CTRL_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_4_r1 <<
				RP_ECTL_4_R1_RX_CDR_CTRL_1C_SHIFT;
	ग_लिखोl(value, port->base + RP_ECTL_4_R1);

	value = पढ़ोl(port->base + RP_ECTL_5_R1);
	value &= ~RP_ECTL_5_R1_RX_EQ_CTRL_L_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_5_r1;
	ग_लिखोl(value, port->base + RP_ECTL_5_R1);

	value = पढ़ोl(port->base + RP_ECTL_6_R1);
	value &= ~RP_ECTL_6_R1_RX_EQ_CTRL_H_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_6_r1;
	ग_लिखोl(value, port->base + RP_ECTL_6_R1);

	value = पढ़ोl(port->base + RP_ECTL_2_R2);
	value &= ~RP_ECTL_2_R2_RX_CTLE_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_2_r2;
	ग_लिखोl(value, port->base + RP_ECTL_2_R2);

	value = पढ़ोl(port->base + RP_ECTL_4_R2);
	value &= ~RP_ECTL_4_R2_RX_CDR_CTRL_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_4_r2 <<
				RP_ECTL_4_R2_RX_CDR_CTRL_1C_SHIFT;
	ग_लिखोl(value, port->base + RP_ECTL_4_R2);

	value = पढ़ोl(port->base + RP_ECTL_5_R2);
	value &= ~RP_ECTL_5_R2_RX_EQ_CTRL_L_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_5_r2;
	ग_लिखोl(value, port->base + RP_ECTL_5_R2);

	value = पढ़ोl(port->base + RP_ECTL_6_R2);
	value &= ~RP_ECTL_6_R2_RX_EQ_CTRL_H_1C_MASK;
	value |= soc->ectl.regs.rp_ectl_6_r2;
	ग_लिखोl(value, port->base + RP_ECTL_6_R2);
पूर्ण

अटल व्योम tegra_pcie_apply_sw_fixup(काष्ठा tegra_pcie_port *port)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	u32 value;

	/*
	 * Someबार link speed change from Gen2 to Gen1 fails due to
	 * instability in deskew logic on lane-0. Increase the deskew
	 * retry समय to resolve this issue.
	 */
	अगर (soc->program_deskew_समय) अणु
		value = पढ़ोl(port->base + RP_VEND_CTL0);
		value &= ~RP_VEND_CTL0_DSK_RST_PULSE_WIDTH_MASK;
		value |= RP_VEND_CTL0_DSK_RST_PULSE_WIDTH;
		ग_लिखोl(value, port->base + RP_VEND_CTL0);
	पूर्ण

	अगर (soc->update_fc_समयr) अणु
		value = पढ़ोl(port->base + RP_VEND_XP);
		value &= ~RP_VEND_XP_UPDATE_FC_THRESHOLD_MASK;
		value |= soc->update_fc_threshold;
		ग_लिखोl(value, port->base + RP_VEND_XP);
	पूर्ण

	/*
	 * PCIe link करोesn't come up with few legacy PCIe endpoपूर्णांकs अगर
	 * root port advertises both Gen-1 and Gen-2 speeds in Tegra.
	 * Hence, the strategy followed here is to initially advertise
	 * only Gen-1 and after link is up, retrain link to Gen-2 speed
	 */
	value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS_2);
	value &= ~PCI_EXP_LNKSTA_CLS;
	value |= PCI_EXP_LNKSTA_CLS_2_5GB;
	ग_लिखोl(value, port->base + RP_LINK_CONTROL_STATUS_2);
पूर्ण

अटल व्योम tegra_pcie_port_enable(काष्ठा tegra_pcie_port *port)
अणु
	अचिन्हित दीर्घ ctrl = tegra_pcie_port_get_pex_ctrl(port);
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	अचिन्हित दीर्घ value;

	/* enable reference घड़ी */
	value = afi_पढ़ोl(port->pcie, ctrl);
	value |= AFI_PEX_CTRL_REFCLK_EN;

	अगर (soc->has_pex_clkreq_en)
		value |= AFI_PEX_CTRL_CLKREQ_EN;

	value |= AFI_PEX_CTRL_OVERRIDE_EN;

	afi_ग_लिखोl(port->pcie, value, ctrl);

	tegra_pcie_port_reset(port);

	अगर (soc->क्रमce_pca_enable) अणु
		value = पढ़ोl(port->base + RP_VEND_CTL2);
		value |= RP_VEND_CTL2_PCA_ENABLE;
		ग_लिखोl(value, port->base + RP_VEND_CTL2);
	पूर्ण

	tegra_pcie_enable_rp_features(port);

	अगर (soc->ectl.enable)
		tegra_pcie_program_ectl_settings(port);

	tegra_pcie_apply_sw_fixup(port);
पूर्ण

अटल व्योम tegra_pcie_port_disable(काष्ठा tegra_pcie_port *port)
अणु
	अचिन्हित दीर्घ ctrl = tegra_pcie_port_get_pex_ctrl(port);
	स्थिर काष्ठा tegra_pcie_soc *soc = port->pcie->soc;
	अचिन्हित दीर्घ value;

	/* निश्चित port reset */
	value = afi_पढ़ोl(port->pcie, ctrl);
	value &= ~AFI_PEX_CTRL_RST;
	afi_ग_लिखोl(port->pcie, value, ctrl);

	/* disable reference घड़ी */
	value = afi_पढ़ोl(port->pcie, ctrl);

	अगर (soc->has_pex_clkreq_en)
		value &= ~AFI_PEX_CTRL_CLKREQ_EN;

	value &= ~AFI_PEX_CTRL_REFCLK_EN;
	afi_ग_लिखोl(port->pcie, value, ctrl);

	/* disable PCIe port and set CLKREQ# as GPIO to allow PLLE घातer करोwn */
	value = afi_पढ़ोl(port->pcie, AFI_PCIE_CONFIG);
	value |= AFI_PCIE_CONFIG_PCIE_DISABLE(port->index);
	value |= AFI_PCIE_CONFIG_PCIE_CLKREQ_GPIO(port->index);
	afi_ग_लिखोl(port->pcie, value, AFI_PCIE_CONFIG);
पूर्ण

अटल व्योम tegra_pcie_port_मुक्त(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा tegra_pcie *pcie = port->pcie;
	काष्ठा device *dev = pcie->dev;

	devm_iounmap(dev, port->base);
	devm_release_mem_region(dev, port->regs.start,
				resource_size(&port->regs));
	list_del(&port->list);
	devm_kमुक्त(dev, port);
पूर्ण

/* Tegra PCIE root complex wrongly reports device class */
अटल व्योम tegra_pcie_fixup_class(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0bf0, tegra_pcie_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0bf1, tegra_pcie_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e1c, tegra_pcie_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_NVIDIA, 0x0e1d, tegra_pcie_fixup_class);

/* Tegra20 and Tegra30 PCIE requires relaxed ordering */
अटल व्योम tegra_pcie_relax_enable(काष्ठा pci_dev *dev)
अणु
	pcie_capability_set_word(dev, PCI_EXP_DEVCTL, PCI_EXP_DEVCTL_RELAX_EN);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, 0x0bf0, tegra_pcie_relax_enable);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, 0x0bf1, tegra_pcie_relax_enable);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, 0x0e1c, tegra_pcie_relax_enable);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_NVIDIA, 0x0e1d, tegra_pcie_relax_enable);

अटल पूर्णांक tegra_pcie_map_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
	काष्ठा tegra_pcie *pcie = pdev->bus->sysdata;
	पूर्णांक irq;

	tegra_cpuidle_pcie_irqs_in_use();

	irq = of_irq_parse_and_map_pci(pdev, slot, pin);
	अगर (!irq)
		irq = pcie->irq;

	वापस irq;
पूर्ण

अटल irqवापस_t tegra_pcie_isr(पूर्णांक irq, व्योम *arg)
अणु
	स्थिर अक्षर *err_msg[] = अणु
		"Unknown",
		"AXI slave error",
		"AXI decode error",
		"Target abort",
		"Master abort",
		"Invalid write",
		"Legacy interrupt",
		"Response decoding error",
		"AXI response decoding error",
		"Transaction timeout",
		"Slot present pin change",
		"Slot clock request change",
		"TMS clock ramp change",
		"TMS ready for power down",
		"Peer2Peer error",
	पूर्ण;
	काष्ठा tegra_pcie *pcie = arg;
	काष्ठा device *dev = pcie->dev;
	u32 code, signature;

	code = afi_पढ़ोl(pcie, AFI_INTR_CODE) & AFI_INTR_CODE_MASK;
	signature = afi_पढ़ोl(pcie, AFI_INTR_SIGNATURE);
	afi_ग_लिखोl(pcie, 0, AFI_INTR_CODE);

	अगर (code == AFI_INTR_LEGACY)
		वापस IRQ_NONE;

	अगर (code >= ARRAY_SIZE(err_msg))
		code = 0;

	/*
	 * करो not pollute kernel log with master पात reports since they
	 * happen a lot during क्रमागतeration
	 */
	अगर (code == AFI_INTR_MASTER_ABORT || code == AFI_INTR_PE_PRSNT_SENSE)
		dev_dbg(dev, "%s, signature: %08x\n", err_msg[code], signature);
	अन्यथा
		dev_err(dev, "%s, signature: %08x\n", err_msg[code], signature);

	अगर (code == AFI_INTR_TARGET_ABORT || code == AFI_INTR_MASTER_ABORT ||
	    code == AFI_INTR_FPCI_DECODE_ERROR) अणु
		u32 fpci = afi_पढ़ोl(pcie, AFI_UPPER_FPCI_ADDRESS) & 0xff;
		u64 address = (u64)fpci << 32 | (signature & 0xfffffffc);

		अगर (code == AFI_INTR_MASTER_ABORT)
			dev_dbg(dev, "  FPCI address: %10llx\n", address);
		अन्यथा
			dev_err(dev, "  FPCI address: %10llx\n", address);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * FPCI map is as follows:
 * - 0xfdfc000000: I/O space
 * - 0xfdfe000000: type 0 configuration space
 * - 0xfdff000000: type 1 configuration space
 * - 0xfe00000000: type 0 extended configuration space
 * - 0xfe10000000: type 1 extended configuration space
 */
अटल व्योम tegra_pcie_setup_translations(काष्ठा tegra_pcie *pcie)
अणु
	u32 size;
	काष्ठा resource_entry *entry;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);

	/* Bar 0: type 1 extended configuration space */
	size = resource_size(&pcie->cs);
	afi_ग_लिखोl(pcie, pcie->cs.start, AFI_AXI_BAR0_START);
	afi_ग_लिखोl(pcie, size >> 12, AFI_AXI_BAR0_SZ);

	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		u32 fpci_bar, axi_address;
		काष्ठा resource *res = entry->res;

		size = resource_size(res);

		चयन (resource_type(res)) अणु
		हाल IORESOURCE_IO:
			/* Bar 1: करोwnstream IO bar */
			fpci_bar = 0xfdfc0000;
			axi_address = pci_pio_to_address(res->start);
			afi_ग_लिखोl(pcie, axi_address, AFI_AXI_BAR1_START);
			afi_ग_लिखोl(pcie, size >> 12, AFI_AXI_BAR1_SZ);
			afi_ग_लिखोl(pcie, fpci_bar, AFI_FPCI_BAR1);
			अवरोध;
		हाल IORESOURCE_MEM:
			fpci_bar = (((res->start >> 12) & 0x0fffffff) << 4) | 0x1;
			axi_address = res->start;

			अगर (res->flags & IORESOURCE_PREFETCH) अणु
				/* Bar 2: prefetchable memory BAR */
				afi_ग_लिखोl(pcie, axi_address, AFI_AXI_BAR2_START);
				afi_ग_लिखोl(pcie, size >> 12, AFI_AXI_BAR2_SZ);
				afi_ग_लिखोl(pcie, fpci_bar, AFI_FPCI_BAR2);

			पूर्ण अन्यथा अणु
				/* Bar 3: non prefetchable memory BAR */
				afi_ग_लिखोl(pcie, axi_address, AFI_AXI_BAR3_START);
				afi_ग_लिखोl(pcie, size >> 12, AFI_AXI_BAR3_SZ);
				afi_ग_लिखोl(pcie, fpci_bar, AFI_FPCI_BAR3);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* शून्य out the reमुख्यing BARs as they are not used */
	afi_ग_लिखोl(pcie, 0, AFI_AXI_BAR4_START);
	afi_ग_लिखोl(pcie, 0, AFI_AXI_BAR4_SZ);
	afi_ग_लिखोl(pcie, 0, AFI_FPCI_BAR4);

	afi_ग_लिखोl(pcie, 0, AFI_AXI_BAR5_START);
	afi_ग_लिखोl(pcie, 0, AFI_AXI_BAR5_SZ);
	afi_ग_लिखोl(pcie, 0, AFI_FPCI_BAR5);

	अगर (pcie->soc->has_cache_bars) अणु
		/* map all upstream transactions as uncached */
		afi_ग_लिखोl(pcie, 0, AFI_CACHE_BAR0_ST);
		afi_ग_लिखोl(pcie, 0, AFI_CACHE_BAR0_SZ);
		afi_ग_लिखोl(pcie, 0, AFI_CACHE_BAR1_ST);
		afi_ग_लिखोl(pcie, 0, AFI_CACHE_BAR1_SZ);
	पूर्ण

	/* MSI translations are setup only when needed */
	afi_ग_लिखोl(pcie, 0, AFI_MSI_FPCI_BAR_ST);
	afi_ग_लिखोl(pcie, 0, AFI_MSI_BAR_SZ);
	afi_ग_लिखोl(pcie, 0, AFI_MSI_AXI_BAR_ST);
	afi_ग_लिखोl(pcie, 0, AFI_MSI_BAR_SZ);
पूर्ण

अटल पूर्णांक tegra_pcie_pll_रुको(काष्ठा tegra_pcie *pcie, अचिन्हित दीर्घ समयout)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	u32 value;

	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = pads_पढ़ोl(pcie, soc->pads_pll_ctl);
		अगर (value & PADS_PLL_CTL_LOCKDET)
			वापस 0;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक tegra_pcie_phy_enable(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	u32 value;
	पूर्णांक err;

	/* initialize पूर्णांकernal PHY, enable up to 16 PCIE lanes */
	pads_ग_लिखोl(pcie, 0x0, PADS_CTL_SEL);

	/* override IDDQ to 1 on all 4 lanes */
	value = pads_पढ़ोl(pcie, PADS_CTL);
	value |= PADS_CTL_IDDQ_1L;
	pads_ग_लिखोl(pcie, value, PADS_CTL);

	/*
	 * Set up PHY PLL inमाला_दो select PLLE output as refघड़ी,
	 * set TX ref sel to भाग10 (not भाग5).
	 */
	value = pads_पढ़ोl(pcie, soc->pads_pll_ctl);
	value &= ~(PADS_PLL_CTL_REFCLK_MASK | PADS_PLL_CTL_TXCLKREF_MASK);
	value |= PADS_PLL_CTL_REFCLK_INTERNAL_CML | soc->tx_ref_sel;
	pads_ग_लिखोl(pcie, value, soc->pads_pll_ctl);

	/* reset PLL */
	value = pads_पढ़ोl(pcie, soc->pads_pll_ctl);
	value &= ~PADS_PLL_CTL_RST_B4SM;
	pads_ग_लिखोl(pcie, value, soc->pads_pll_ctl);

	usleep_range(20, 100);

	/* take PLL out of reset  */
	value = pads_पढ़ोl(pcie, soc->pads_pll_ctl);
	value |= PADS_PLL_CTL_RST_B4SM;
	pads_ग_लिखोl(pcie, value, soc->pads_pll_ctl);

	/* रुको क्रम the PLL to lock */
	err = tegra_pcie_pll_रुको(pcie, 500);
	अगर (err < 0) अणु
		dev_err(dev, "PLL failed to lock: %d\n", err);
		वापस err;
	पूर्ण

	/* turn off IDDQ override */
	value = pads_पढ़ोl(pcie, PADS_CTL);
	value &= ~PADS_CTL_IDDQ_1L;
	pads_ग_लिखोl(pcie, value, PADS_CTL);

	/* enable TX/RX data */
	value = pads_पढ़ोl(pcie, PADS_CTL);
	value |= PADS_CTL_TX_DATA_EN_1L | PADS_CTL_RX_DATA_EN_1L;
	pads_ग_लिखोl(pcie, value, PADS_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_phy_disable(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	u32 value;

	/* disable TX/RX data */
	value = pads_पढ़ोl(pcie, PADS_CTL);
	value &= ~(PADS_CTL_TX_DATA_EN_1L | PADS_CTL_RX_DATA_EN_1L);
	pads_ग_लिखोl(pcie, value, PADS_CTL);

	/* override IDDQ */
	value = pads_पढ़ोl(pcie, PADS_CTL);
	value |= PADS_CTL_IDDQ_1L;
	pads_ग_लिखोl(pcie, value, PADS_CTL);

	/* reset PLL */
	value = pads_पढ़ोl(pcie, soc->pads_pll_ctl);
	value &= ~PADS_PLL_CTL_RST_B4SM;
	pads_ग_लिखोl(pcie, value, soc->pads_pll_ctl);

	usleep_range(20, 100);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_port_phy_घातer_on(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा device *dev = port->pcie->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < port->lanes; i++) अणु
		err = phy_घातer_on(port->phys[i]);
		अगर (err < 0) अणु
			dev_err(dev, "failed to power on PHY#%u: %d\n", i, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_port_phy_घातer_off(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा device *dev = port->pcie->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < port->lanes; i++) अणु
		err = phy_घातer_off(port->phys[i]);
		अगर (err < 0) अणु
			dev_err(dev, "failed to power off PHY#%u: %d\n", i,
				err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_phy_घातer_on(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा tegra_pcie_port *port;
	पूर्णांक err;

	अगर (pcie->legacy_phy) अणु
		अगर (pcie->phy)
			err = phy_घातer_on(pcie->phy);
		अन्यथा
			err = tegra_pcie_phy_enable(pcie);

		अगर (err < 0)
			dev_err(dev, "failed to power on PHY: %d\n", err);

		वापस err;
	पूर्ण

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		err = tegra_pcie_port_phy_घातer_on(port);
		अगर (err < 0) अणु
			dev_err(dev,
				"failed to power on PCIe port %u PHY: %d\n",
				port->index, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_phy_घातer_off(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा tegra_pcie_port *port;
	पूर्णांक err;

	अगर (pcie->legacy_phy) अणु
		अगर (pcie->phy)
			err = phy_घातer_off(pcie->phy);
		अन्यथा
			err = tegra_pcie_phy_disable(pcie);

		अगर (err < 0)
			dev_err(dev, "failed to power off PHY: %d\n", err);

		वापस err;
	पूर्ण

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		err = tegra_pcie_port_phy_घातer_off(port);
		अगर (err < 0) अणु
			dev_err(dev,
				"failed to power off PCIe port %u PHY: %d\n",
				port->index, err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_pcie_enable_controller(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	काष्ठा tegra_pcie_port *port;
	अचिन्हित दीर्घ value;

	/* enable PLL घातer करोwn */
	अगर (pcie->phy) अणु
		value = afi_पढ़ोl(pcie, AFI_PLLE_CONTROL);
		value &= ~AFI_PLLE_CONTROL_BYPASS_PADS2PLLE_CONTROL;
		value |= AFI_PLLE_CONTROL_PADS2PLLE_CONTROL_EN;
		afi_ग_लिखोl(pcie, value, AFI_PLLE_CONTROL);
	पूर्ण

	/* घातer करोwn PCIe slot घड़ी bias pad */
	अगर (soc->has_pex_bias_ctrl)
		afi_ग_लिखोl(pcie, 0, AFI_PEXBIAS_CTRL_0);

	/* configure mode and disable all ports */
	value = afi_पढ़ोl(pcie, AFI_PCIE_CONFIG);
	value &= ~AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_MASK;
	value |= AFI_PCIE_CONFIG_PCIE_DISABLE_ALL | pcie->xbar_config;
	value |= AFI_PCIE_CONFIG_PCIE_CLKREQ_GPIO_ALL;

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		value &= ~AFI_PCIE_CONFIG_PCIE_DISABLE(port->index);
		value &= ~AFI_PCIE_CONFIG_PCIE_CLKREQ_GPIO(port->index);
	पूर्ण

	afi_ग_लिखोl(pcie, value, AFI_PCIE_CONFIG);

	अगर (soc->has_gen2) अणु
		value = afi_पढ़ोl(pcie, AFI_FUSE);
		value &= ~AFI_FUSE_PCIE_T0_GEN2_DIS;
		afi_ग_लिखोl(pcie, value, AFI_FUSE);
	पूर्ण अन्यथा अणु
		value = afi_पढ़ोl(pcie, AFI_FUSE);
		value |= AFI_FUSE_PCIE_T0_GEN2_DIS;
		afi_ग_लिखोl(pcie, value, AFI_FUSE);
	पूर्ण

	/* Disable AFI dynamic घड़ी gating and enable PCIe */
	value = afi_पढ़ोl(pcie, AFI_CONFIGURATION);
	value |= AFI_CONFIGURATION_EN_FPCI;
	value |= AFI_CONFIGURATION_CLKEN_OVERRIDE;
	afi_ग_लिखोl(pcie, value, AFI_CONFIGURATION);

	value = AFI_INTR_EN_INI_SLVERR | AFI_INTR_EN_INI_DECERR |
		AFI_INTR_EN_TGT_SLVERR | AFI_INTR_EN_TGT_DECERR |
		AFI_INTR_EN_TGT_WRERR | AFI_INTR_EN_DFPCI_DECERR;

	अगर (soc->has_पूर्णांकr_prsnt_sense)
		value |= AFI_INTR_EN_PRSNT_SENSE;

	afi_ग_लिखोl(pcie, value, AFI_AFI_INTR_ENABLE);
	afi_ग_लिखोl(pcie, 0xffffffff, AFI_SM_INTR_ENABLE);

	/* करोn't enable MSI क्रम now, only when needed */
	afi_ग_लिखोl(pcie, AFI_INTR_MASK_INT_MASK, AFI_INTR_MASK);

	/* disable all exceptions */
	afi_ग_लिखोl(pcie, 0, AFI_FPCI_ERROR_MASKS);
पूर्ण

अटल व्योम tegra_pcie_घातer_off(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	पूर्णांक err;

	reset_control_निश्चित(pcie->afi_rst);

	clk_disable_unprepare(pcie->pll_e);
	अगर (soc->has_cml_clk)
		clk_disable_unprepare(pcie->cml_clk);
	clk_disable_unprepare(pcie->afi_clk);

	अगर (!dev->pm_करोमुख्य)
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_PCIE);

	err = regulator_bulk_disable(pcie->num_supplies, pcie->supplies);
	अगर (err < 0)
		dev_warn(dev, "failed to disable regulators: %d\n", err);
पूर्ण

अटल पूर्णांक tegra_pcie_घातer_on(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	पूर्णांक err;

	reset_control_निश्चित(pcie->pcie_xrst);
	reset_control_निश्चित(pcie->afi_rst);
	reset_control_निश्चित(pcie->pex_rst);

	अगर (!dev->pm_करोमुख्य)
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_PCIE);

	/* enable regulators */
	err = regulator_bulk_enable(pcie->num_supplies, pcie->supplies);
	अगर (err < 0)
		dev_err(dev, "failed to enable regulators: %d\n", err);

	अगर (!dev->pm_करोमुख्य) अणु
		err = tegra_घातergate_घातer_on(TEGRA_POWERGATE_PCIE);
		अगर (err) अणु
			dev_err(dev, "failed to power ungate: %d\n", err);
			जाओ regulator_disable;
		पूर्ण
		err = tegra_घातergate_हटाओ_clamping(TEGRA_POWERGATE_PCIE);
		अगर (err) अणु
			dev_err(dev, "failed to remove clamp: %d\n", err);
			जाओ घातergate;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(pcie->afi_clk);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable AFI clock: %d\n", err);
		जाओ घातergate;
	पूर्ण

	अगर (soc->has_cml_clk) अणु
		err = clk_prepare_enable(pcie->cml_clk);
		अगर (err < 0) अणु
			dev_err(dev, "failed to enable CML clock: %d\n", err);
			जाओ disable_afi_clk;
		पूर्ण
	पूर्ण

	err = clk_prepare_enable(pcie->pll_e);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable PLLE clock: %d\n", err);
		जाओ disable_cml_clk;
	पूर्ण

	reset_control_deनिश्चित(pcie->afi_rst);

	वापस 0;

disable_cml_clk:
	अगर (soc->has_cml_clk)
		clk_disable_unprepare(pcie->cml_clk);
disable_afi_clk:
	clk_disable_unprepare(pcie->afi_clk);
घातergate:
	अगर (!dev->pm_करोमुख्य)
		tegra_घातergate_घातer_off(TEGRA_POWERGATE_PCIE);
regulator_disable:
	regulator_bulk_disable(pcie->num_supplies, pcie->supplies);

	वापस err;
पूर्ण

अटल व्योम tegra_pcie_apply_pad_settings(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;

	/* Configure the reference घड़ी driver */
	pads_ग_लिखोl(pcie, soc->pads_refclk_cfg0, PADS_REFCLK_CFG0);

	अगर (soc->num_ports > 2)
		pads_ग_लिखोl(pcie, soc->pads_refclk_cfg1, PADS_REFCLK_CFG1);
पूर्ण

अटल पूर्णांक tegra_pcie_घड़ीs_get(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;

	pcie->pex_clk = devm_clk_get(dev, "pex");
	अगर (IS_ERR(pcie->pex_clk))
		वापस PTR_ERR(pcie->pex_clk);

	pcie->afi_clk = devm_clk_get(dev, "afi");
	अगर (IS_ERR(pcie->afi_clk))
		वापस PTR_ERR(pcie->afi_clk);

	pcie->pll_e = devm_clk_get(dev, "pll_e");
	अगर (IS_ERR(pcie->pll_e))
		वापस PTR_ERR(pcie->pll_e);

	अगर (soc->has_cml_clk) अणु
		pcie->cml_clk = devm_clk_get(dev, "cml");
		अगर (IS_ERR(pcie->cml_clk))
			वापस PTR_ERR(pcie->cml_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_resets_get(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;

	pcie->pex_rst = devm_reset_control_get_exclusive(dev, "pex");
	अगर (IS_ERR(pcie->pex_rst))
		वापस PTR_ERR(pcie->pex_rst);

	pcie->afi_rst = devm_reset_control_get_exclusive(dev, "afi");
	अगर (IS_ERR(pcie->afi_rst))
		वापस PTR_ERR(pcie->afi_rst);

	pcie->pcie_xrst = devm_reset_control_get_exclusive(dev, "pcie_x");
	अगर (IS_ERR(pcie->pcie_xrst))
		वापस PTR_ERR(pcie->pcie_xrst);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_phys_get_legacy(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	पूर्णांक err;

	pcie->phy = devm_phy_optional_get(dev, "pcie");
	अगर (IS_ERR(pcie->phy)) अणु
		err = PTR_ERR(pcie->phy);
		dev_err(dev, "failed to get PHY: %d\n", err);
		वापस err;
	पूर्ण

	err = phy_init(pcie->phy);
	अगर (err < 0) अणु
		dev_err(dev, "failed to initialize PHY: %d\n", err);
		वापस err;
	पूर्ण

	pcie->legacy_phy = true;

	वापस 0;
पूर्ण

अटल काष्ठा phy *devm_of_phy_optional_get_index(काष्ठा device *dev,
						  काष्ठा device_node *np,
						  स्थिर अक्षर *consumer,
						  अचिन्हित पूर्णांक index)
अणु
	काष्ठा phy *phy;
	अक्षर *name;

	name = kaप्र_लिखो(GFP_KERNEL, "%s-%u", consumer, index);
	अगर (!name)
		वापस ERR_PTR(-ENOMEM);

	phy = devm_of_phy_get(dev, np, name);
	kमुक्त(name);

	अगर (PTR_ERR(phy) == -ENODEV)
		phy = शून्य;

	वापस phy;
पूर्ण

अटल पूर्णांक tegra_pcie_port_get_phys(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा device *dev = port->pcie->dev;
	काष्ठा phy *phy;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	port->phys = devm_kसुस्मृति(dev, माप(phy), port->lanes, GFP_KERNEL);
	अगर (!port->phys)
		वापस -ENOMEM;

	क्रम (i = 0; i < port->lanes; i++) अणु
		phy = devm_of_phy_optional_get_index(dev, port->np, "pcie", i);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to get PHY#%u: %ld\n", i,
				PTR_ERR(phy));
			वापस PTR_ERR(phy);
		पूर्ण

		err = phy_init(phy);
		अगर (err < 0) अणु
			dev_err(dev, "failed to initialize PHY#%u: %d\n", i,
				err);
			वापस err;
		पूर्ण

		port->phys[i] = phy;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_pcie_phys_get(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	काष्ठा device_node *np = pcie->dev->of_node;
	काष्ठा tegra_pcie_port *port;
	पूर्णांक err;

	अगर (!soc->has_gen2 || of_find_property(np, "phys", शून्य) != शून्य)
		वापस tegra_pcie_phys_get_legacy(pcie);

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		err = tegra_pcie_port_get_phys(port);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_pcie_phys_put(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा tegra_pcie_port *port;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक err, i;

	अगर (pcie->legacy_phy) अणु
		err = phy_निकास(pcie->phy);
		अगर (err < 0)
			dev_err(dev, "failed to teardown PHY: %d\n", err);
		वापस;
	पूर्ण

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		क्रम (i = 0; i < port->lanes; i++) अणु
			err = phy_निकास(port->phys[i]);
			अगर (err < 0)
				dev_err(dev, "failed to teardown PHY#%u: %d\n",
					i, err);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_pcie_get_resources(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	पूर्णांक err;

	err = tegra_pcie_घड़ीs_get(pcie);
	अगर (err) अणु
		dev_err(dev, "failed to get clocks: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_pcie_resets_get(pcie);
	अगर (err) अणु
		dev_err(dev, "failed to get resets: %d\n", err);
		वापस err;
	पूर्ण

	अगर (soc->program_uphy) अणु
		err = tegra_pcie_phys_get(pcie);
		अगर (err < 0) अणु
			dev_err(dev, "failed to get PHYs: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	pcie->pads = devm_platक्रमm_ioremap_resource_byname(pdev, "pads");
	अगर (IS_ERR(pcie->pads)) अणु
		err = PTR_ERR(pcie->pads);
		जाओ phys_put;
	पूर्ण

	pcie->afi = devm_platक्रमm_ioremap_resource_byname(pdev, "afi");
	अगर (IS_ERR(pcie->afi)) अणु
		err = PTR_ERR(pcie->afi);
		जाओ phys_put;
	पूर्ण

	/* request configuration space, but remap later, on demand */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cs");
	अगर (!res) अणु
		err = -EADDRNOTAVAIL;
		जाओ phys_put;
	पूर्ण

	pcie->cs = *res;

	/* स्थिरrain configuration space to 4 KiB */
	pcie->cs.end = pcie->cs.start + SZ_4K - 1;

	pcie->cfg = devm_ioremap_resource(dev, &pcie->cs);
	अगर (IS_ERR(pcie->cfg)) अणु
		err = PTR_ERR(pcie->cfg);
		जाओ phys_put;
	पूर्ण

	/* request पूर्णांकerrupt */
	err = platक्रमm_get_irq_byname(pdev, "intr");
	अगर (err < 0)
		जाओ phys_put;

	pcie->irq = err;

	err = request_irq(pcie->irq, tegra_pcie_isr, IRQF_SHARED, "PCIE", pcie);
	अगर (err) अणु
		dev_err(dev, "failed to register IRQ: %d\n", err);
		जाओ phys_put;
	पूर्ण

	वापस 0;

phys_put:
	अगर (soc->program_uphy)
		tegra_pcie_phys_put(pcie);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_pcie_put_resources(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;

	अगर (pcie->irq > 0)
		मुक्त_irq(pcie->irq, pcie);

	अगर (soc->program_uphy)
		tegra_pcie_phys_put(pcie);

	वापस 0;
पूर्ण

अटल व्योम tegra_pcie_pme_turnoff(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा tegra_pcie *pcie = port->pcie;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	पूर्णांक err;
	u32 val;
	u8 ack_bit;

	val = afi_पढ़ोl(pcie, AFI_PCIE_PME);
	val |= (0x1 << soc->ports[port->index].pme.turnoff_bit);
	afi_ग_लिखोl(pcie, val, AFI_PCIE_PME);

	ack_bit = soc->ports[port->index].pme.ack_bit;
	err = पढ़ोl_poll_समयout(pcie->afi + AFI_PCIE_PME, val,
				 val & (0x1 << ack_bit), 1, PME_ACK_TIMEOUT);
	अगर (err)
		dev_err(pcie->dev, "PME Ack is not received on port: %d\n",
			port->index);

	usleep_range(10000, 11000);

	val = afi_पढ़ोl(pcie, AFI_PCIE_PME);
	val &= ~(0x1 << soc->ports[port->index].pme.turnoff_bit);
	afi_ग_लिखोl(pcie, val, AFI_PCIE_PME);
पूर्ण

अटल व्योम tegra_pcie_msi_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा tegra_pcie *pcie = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा tegra_msi *msi = &pcie->msi;
	काष्ठा device *dev = pcie->dev;
	अचिन्हित पूर्णांक i;

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < 8; i++) अणु
		अचिन्हित दीर्घ reg = afi_पढ़ोl(pcie, AFI_MSI_VEC(i));

		जबतक (reg) अणु
			अचिन्हित पूर्णांक offset = find_first_bit(&reg, 32);
			अचिन्हित पूर्णांक index = i * 32 + offset;
			अचिन्हित पूर्णांक irq;

			irq = irq_find_mapping(msi->करोमुख्य->parent, index);
			अगर (irq) अणु
				generic_handle_irq(irq);
			पूर्ण अन्यथा अणु
				/*
				 * that's weird who triggered this?
				 * just clear it
				 */
				dev_info(dev, "unexpected MSI\n");
				afi_ग_लिखोl(pcie, BIT(index % 32), AFI_MSI_VEC(index));
			पूर्ण

			/* see अगर there's any more pending in this vector */
			reg = afi_पढ़ोl(pcie, AFI_MSI_VEC(i));
		पूर्ण
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम tegra_msi_top_irq_ack(काष्ठा irq_data *d)
अणु
	irq_chip_ack_parent(d);
पूर्ण

अटल व्योम tegra_msi_top_irq_mask(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम tegra_msi_top_irq_unmask(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip tegra_msi_top_chip = अणु
	.name		= "Tegra PCIe MSI",
	.irq_ack	= tegra_msi_top_irq_ack,
	.irq_mask	= tegra_msi_top_irq_mask,
	.irq_unmask	= tegra_msi_top_irq_unmask,
पूर्ण;

अटल व्योम tegra_msi_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा tegra_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_pcie *pcie = msi_to_pcie(msi);
	अचिन्हित पूर्णांक index = d->hwirq / 32;

	/* clear the पूर्णांकerrupt */
	afi_ग_लिखोl(pcie, BIT(d->hwirq % 32), AFI_MSI_VEC(index));
पूर्ण

अटल व्योम tegra_msi_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा tegra_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_pcie *pcie = msi_to_pcie(msi);
	अचिन्हित पूर्णांक index = d->hwirq / 32;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&msi->mask_lock, flags);
	value = afi_पढ़ोl(pcie, AFI_MSI_EN_VEC(index));
	value &= ~BIT(d->hwirq % 32);
	afi_ग_लिखोl(pcie, value, AFI_MSI_EN_VEC(index));
	spin_unlock_irqrestore(&msi->mask_lock, flags);
पूर्ण

अटल व्योम tegra_msi_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा tegra_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा tegra_pcie *pcie = msi_to_pcie(msi);
	अचिन्हित पूर्णांक index = d->hwirq / 32;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&msi->mask_lock, flags);
	value = afi_पढ़ोl(pcie, AFI_MSI_EN_VEC(index));
	value |= BIT(d->hwirq % 32);
	afi_ग_लिखोl(pcie, value, AFI_MSI_EN_VEC(index));
	spin_unlock_irqrestore(&msi->mask_lock, flags);
पूर्ण

अटल पूर्णांक tegra_msi_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम tegra_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा tegra_msi *msi = irq_data_get_irq_chip_data(data);

	msg->address_lo = lower_32_bits(msi->phys);
	msg->address_hi = upper_32_bits(msi->phys);
	msg->data = data->hwirq;
पूर्ण

अटल काष्ठा irq_chip tegra_msi_bottom_chip = अणु
	.name			= "Tegra MSI",
	.irq_ack		= tegra_msi_irq_ack,
	.irq_mask		= tegra_msi_irq_mask,
	.irq_unmask		= tegra_msi_irq_unmask,
	.irq_set_affinity 	= tegra_msi_set_affinity,
	.irq_compose_msi_msg	= tegra_compose_msi_msg,
पूर्ण;

अटल पूर्णांक tegra_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा tegra_msi *msi = करोमुख्य->host_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक hwirq;

	mutex_lock(&msi->map_lock);

	hwirq = biपंचांगap_find_मुक्त_region(msi->used, INT_PCI_MSI_NR, order_base_2(nr_irqs));

	mutex_unlock(&msi->map_lock);

	अगर (hwirq < 0)
		वापस -ENOSPC;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &tegra_msi_bottom_chip, करोमुख्य->host_data,
				    handle_edge_irq, शून्य, शून्य);

	tegra_cpuidle_pcie_irqs_in_use();

	वापस 0;
पूर्ण

अटल व्योम tegra_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा tegra_msi *msi = करोमुख्य->host_data;

	mutex_lock(&msi->map_lock);

	biपंचांगap_release_region(msi->used, d->hwirq, order_base_2(nr_irqs));

	mutex_unlock(&msi->map_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops tegra_msi_करोमुख्य_ops = अणु
	.alloc = tegra_msi_करोमुख्य_alloc,
	.मुक्त = tegra_msi_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info tegra_msi_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_PCI_MSIX),
	.chip	= &tegra_msi_top_chip,
पूर्ण;

अटल पूर्णांक tegra_allocate_करोमुख्यs(काष्ठा tegra_msi *msi)
अणु
	काष्ठा tegra_pcie *pcie = msi_to_pcie(msi);
	काष्ठा fwnode_handle *fwnode = dev_fwnode(pcie->dev);
	काष्ठा irq_करोमुख्य *parent;

	parent = irq_करोमुख्य_create_linear(fwnode, INT_PCI_MSI_NR,
					  &tegra_msi_करोमुख्य_ops, msi);
	अगर (!parent) अणु
		dev_err(pcie->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण
	irq_करोमुख्य_update_bus_token(parent, DOMAIN_BUS_NEXUS);

	msi->करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode, &tegra_msi_info, parent);
	अगर (!msi->करोमुख्य) अणु
		dev_err(pcie->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(parent);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_मुक्त_करोमुख्यs(काष्ठा tegra_msi *msi)
अणु
	काष्ठा irq_करोमुख्य *parent = msi->करोमुख्य->parent;

	irq_करोमुख्य_हटाओ(msi->करोमुख्य);
	irq_करोमुख्य_हटाओ(parent);
पूर्ण

अटल पूर्णांक tegra_pcie_msi_setup(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(pcie->dev);
	काष्ठा tegra_msi *msi = &pcie->msi;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक err;

	mutex_init(&msi->map_lock);
	spin_lock_init(&msi->mask_lock);

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		err = tegra_allocate_करोमुख्यs(msi);
		अगर (err)
			वापस err;
	पूर्ण

	err = platक्रमm_get_irq_byname(pdev, "msi");
	अगर (err < 0)
		जाओ मुक्त_irq_करोमुख्य;

	msi->irq = err;

	irq_set_chained_handler_and_data(msi->irq, tegra_pcie_msi_irq, pcie);

	/* Though the PCIe controller can address >32-bit address space, to
	 * facilitate endpoपूर्णांकs that support only 32-bit MSI target address,
	 * the mask is set to 32-bit to make sure that MSI target address is
	 * always a 32-bit address
	 */
	err = dma_set_coherent_mask(dev, DMA_BIT_MASK(32));
	अगर (err < 0) अणु
		dev_err(dev, "failed to set DMA coherent mask: %d\n", err);
		जाओ मुक्त_irq;
	पूर्ण

	msi->virt = dma_alloc_attrs(dev, PAGE_SIZE, &msi->phys, GFP_KERNEL,
				    DMA_ATTR_NO_KERNEL_MAPPING);
	अगर (!msi->virt) अणु
		dev_err(dev, "failed to allocate DMA memory for MSI\n");
		err = -ENOMEM;
		जाओ मुक्त_irq;
	पूर्ण

	वापस 0;

मुक्त_irq:
	irq_set_chained_handler_and_data(msi->irq, शून्य, शून्य);
मुक्त_irq_करोमुख्य:
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_मुक्त_करोमुख्यs(msi);

	वापस err;
पूर्ण

अटल व्योम tegra_pcie_enable_msi(काष्ठा tegra_pcie *pcie)
अणु
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	काष्ठा tegra_msi *msi = &pcie->msi;
	u32 reg, msi_state[INT_PCI_MSI_NR / 32];
	पूर्णांक i;

	afi_ग_लिखोl(pcie, msi->phys >> soc->msi_base_shअगरt, AFI_MSI_FPCI_BAR_ST);
	afi_ग_लिखोl(pcie, msi->phys, AFI_MSI_AXI_BAR_ST);
	/* this रेजिस्टर is in 4K increments */
	afi_ग_लिखोl(pcie, 1, AFI_MSI_BAR_SZ);

	/* Restore the MSI allocation state */
	biपंचांगap_to_arr32(msi_state, msi->used, INT_PCI_MSI_NR);
	क्रम (i = 0; i < ARRAY_SIZE(msi_state); i++)
		afi_ग_लिखोl(pcie, msi_state[i], AFI_MSI_EN_VEC(i));

	/* and unmask the MSI पूर्णांकerrupt */
	reg = afi_पढ़ोl(pcie, AFI_INTR_MASK);
	reg |= AFI_INTR_MASK_MSI_MASK;
	afi_ग_लिखोl(pcie, reg, AFI_INTR_MASK);
पूर्ण

अटल व्योम tegra_pcie_msi_tearकरोwn(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा tegra_msi *msi = &pcie->msi;
	अचिन्हित पूर्णांक i, irq;

	dma_मुक्त_attrs(pcie->dev, PAGE_SIZE, msi->virt, msi->phys,
		       DMA_ATTR_NO_KERNEL_MAPPING);

	क्रम (i = 0; i < INT_PCI_MSI_NR; i++) अणु
		irq = irq_find_mapping(msi->करोमुख्य, i);
		अगर (irq > 0)
			irq_करोमुख्य_मुक्त_irqs(irq, 1);
	पूर्ण

	irq_set_chained_handler_and_data(msi->irq, शून्य, शून्य);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_मुक्त_करोमुख्यs(msi);
पूर्ण

अटल पूर्णांक tegra_pcie_disable_msi(काष्ठा tegra_pcie *pcie)
अणु
	u32 value;

	/* mask the MSI पूर्णांकerrupt */
	value = afi_पढ़ोl(pcie, AFI_INTR_MASK);
	value &= ~AFI_INTR_MASK_MSI_MASK;
	afi_ग_लिखोl(pcie, value, AFI_INTR_MASK);

	वापस 0;
पूर्ण

अटल व्योम tegra_pcie_disable_पूर्णांकerrupts(काष्ठा tegra_pcie *pcie)
अणु
	u32 value;

	value = afi_पढ़ोl(pcie, AFI_INTR_MASK);
	value &= ~AFI_INTR_MASK_INT_MASK;
	afi_ग_लिखोl(pcie, value, AFI_INTR_MASK);
पूर्ण

अटल पूर्णांक tegra_pcie_get_xbar_config(काष्ठा tegra_pcie *pcie, u32 lanes,
				      u32 *xbar)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node;

	अगर (of_device_is_compatible(np, "nvidia,tegra186-pcie")) अणु
		चयन (lanes) अणु
		हाल 0x010004:
			dev_info(dev, "4x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_401;
			वापस 0;

		हाल 0x010102:
			dev_info(dev, "2x1, 1X1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211;
			वापस 0;

		हाल 0x010101:
			dev_info(dev, "1x1, 1x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_111;
			वापस 0;

		शेष:
			dev_info(dev, "wrong configuration updated in DT, "
				 "switching to default 2x1, 1x1, 1x1 "
				 "configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra124-pcie") ||
		   of_device_is_compatible(np, "nvidia,tegra210-pcie")) अणु
		चयन (lanes) अणु
		हाल 0x0000104:
			dev_info(dev, "4x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1;
			वापस 0;

		हाल 0x0000102:
			dev_info(dev, "2x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra30-pcie")) अणु
		चयन (lanes) अणु
		हाल 0x00000204:
			dev_info(dev, "4x1, 2x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420;
			वापस 0;

		हाल 0x00020202:
			dev_info(dev, "2x3 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222;
			वापस 0;

		हाल 0x00010104:
			dev_info(dev, "4x1, 1x2 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra20-pcie")) अणु
		चयन (lanes) अणु
		हाल 0x00000004:
			dev_info(dev, "single-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE;
			वापस 0;

		हाल 0x00000202:
			dev_info(dev, "dual-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Check whether a given set of supplies is available in a device tree node.
 * This is used to check whether the new or the legacy device tree bindings
 * should be used.
 */
अटल bool of_regulator_bulk_available(काष्ठा device_node *np,
					काष्ठा regulator_bulk_data *supplies,
					अचिन्हित पूर्णांक num_supplies)
अणु
	अक्षर property[32];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_supplies; i++) अणु
		snम_लिखो(property, 32, "%s-supply", supplies[i].supply);

		अगर (of_find_property(np, property, शून्य) == शून्य)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Old versions of the device tree binding क्रम this device used a set of घातer
 * supplies that didn't match the hardware inमाला_दो. This happened to work क्रम a
 * number of हालs but is not future proof. However to preserve backwards-
 * compatibility with old device trees, this function will try to use the old
 * set of supplies.
 */
अटल पूर्णांक tegra_pcie_get_legacy_regulators(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node;

	अगर (of_device_is_compatible(np, "nvidia,tegra30-pcie"))
		pcie->num_supplies = 3;
	अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra20-pcie"))
		pcie->num_supplies = 2;

	अगर (pcie->num_supplies == 0) अणु
		dev_err(dev, "device %pOF not supported in legacy mode\n", np);
		वापस -ENODEV;
	पूर्ण

	pcie->supplies = devm_kसुस्मृति(dev, pcie->num_supplies,
				      माप(*pcie->supplies),
				      GFP_KERNEL);
	अगर (!pcie->supplies)
		वापस -ENOMEM;

	pcie->supplies[0].supply = "pex-clk";
	pcie->supplies[1].supply = "vdd";

	अगर (pcie->num_supplies > 2)
		pcie->supplies[2].supply = "avdd";

	वापस devm_regulator_bulk_get(dev, pcie->num_supplies, pcie->supplies);
पूर्ण

/*
 * Obtains the list of regulators required क्रम a particular generation of the
 * IP block.
 *
 * This would've been nice to करो simply by providing अटल tables क्रम use
 * with the regulator_bulk_*() API, but unक्रमtunately Tegra30 is a bit quirky
 * in that it has two pairs or AVDD_PEX and VDD_PEX supplies (PEXA and PEXB)
 * and either seems to be optional depending on which ports are being used.
 */
अटल पूर्णांक tegra_pcie_get_regulators(काष्ठा tegra_pcie *pcie, u32 lane_mask)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node;
	अचिन्हित पूर्णांक i = 0;

	अगर (of_device_is_compatible(np, "nvidia,tegra186-pcie")) अणु
		pcie->num_supplies = 4;

		pcie->supplies = devm_kसुस्मृति(pcie->dev, pcie->num_supplies,
					      माप(*pcie->supplies),
					      GFP_KERNEL);
		अगर (!pcie->supplies)
			वापस -ENOMEM;

		pcie->supplies[i++].supply = "dvdd-pex";
		pcie->supplies[i++].supply = "hvdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "vddio-pexctl-aud";
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra210-pcie")) अणु
		pcie->num_supplies = 3;

		pcie->supplies = devm_kसुस्मृति(pcie->dev, pcie->num_supplies,
					      माप(*pcie->supplies),
					      GFP_KERNEL);
		अगर (!pcie->supplies)
			वापस -ENOMEM;

		pcie->supplies[i++].supply = "hvddio-pex";
		pcie->supplies[i++].supply = "dvddio-pex";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra124-pcie")) अणु
		pcie->num_supplies = 4;

		pcie->supplies = devm_kसुस्मृति(dev, pcie->num_supplies,
					      माप(*pcie->supplies),
					      GFP_KERNEL);
		अगर (!pcie->supplies)
			वापस -ENOMEM;

		pcie->supplies[i++].supply = "avddio-pex";
		pcie->supplies[i++].supply = "dvddio-pex";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra30-pcie")) अणु
		bool need_pexa = false, need_pexb = false;

		/* VDD_PEXA and AVDD_PEXA supply lanes 0 to 3 */
		अगर (lane_mask & 0x0f)
			need_pexa = true;

		/* VDD_PEXB and AVDD_PEXB supply lanes 4 to 5 */
		अगर (lane_mask & 0x30)
			need_pexb = true;

		pcie->num_supplies = 4 + (need_pexa ? 2 : 0) +
					 (need_pexb ? 2 : 0);

		pcie->supplies = devm_kसुस्मृति(dev, pcie->num_supplies,
					      माप(*pcie->supplies),
					      GFP_KERNEL);
		अगर (!pcie->supplies)
			वापस -ENOMEM;

		pcie->supplies[i++].supply = "avdd-pex-pll";
		pcie->supplies[i++].supply = "hvdd-pex";
		pcie->supplies[i++].supply = "vddio-pex-ctl";
		pcie->supplies[i++].supply = "avdd-plle";

		अगर (need_pexa) अणु
			pcie->supplies[i++].supply = "avdd-pexa";
			pcie->supplies[i++].supply = "vdd-pexa";
		पूर्ण

		अगर (need_pexb) अणु
			pcie->supplies[i++].supply = "avdd-pexb";
			pcie->supplies[i++].supply = "vdd-pexb";
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "nvidia,tegra20-pcie")) अणु
		pcie->num_supplies = 5;

		pcie->supplies = devm_kसुस्मृति(dev, pcie->num_supplies,
					      माप(*pcie->supplies),
					      GFP_KERNEL);
		अगर (!pcie->supplies)
			वापस -ENOMEM;

		pcie->supplies[0].supply = "avdd-pex";
		pcie->supplies[1].supply = "vdd-pex";
		pcie->supplies[2].supply = "avdd-pex-pll";
		pcie->supplies[3].supply = "avdd-plle";
		pcie->supplies[4].supply = "vddio-pex-clk";
	पूर्ण

	अगर (of_regulator_bulk_available(dev->of_node, pcie->supplies,
					pcie->num_supplies))
		वापस devm_regulator_bulk_get(dev, pcie->num_supplies,
					       pcie->supplies);

	/*
	 * If not all regulators are available क्रम this new scheme, assume
	 * that the device tree complies with an older version of the device
	 * tree binding.
	 */
	dev_info(dev, "using legacy DT binding for power supplies\n");

	devm_kमुक्त(dev, pcie->supplies);
	pcie->num_supplies = 0;

	वापस tegra_pcie_get_legacy_regulators(pcie);
पूर्ण

अटल पूर्णांक tegra_pcie_parse_dt(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node, *port;
	स्थिर काष्ठा tegra_pcie_soc *soc = pcie->soc;
	u32 lanes = 0, mask = 0;
	अचिन्हित पूर्णांक lane = 0;
	पूर्णांक err;

	/* parse root ports */
	क्रम_each_child_of_node(np, port) अणु
		काष्ठा tegra_pcie_port *rp;
		अचिन्हित पूर्णांक index;
		u32 value;
		अक्षर *label;

		err = of_pci_get_devfn(port);
		अगर (err < 0) अणु
			dev_err(dev, "failed to parse address: %d\n", err);
			जाओ err_node_put;
		पूर्ण

		index = PCI_SLOT(err);

		अगर (index < 1 || index > soc->num_ports) अणु
			dev_err(dev, "invalid port number: %d\n", index);
			err = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		index--;

		err = of_property_पढ़ो_u32(port, "nvidia,num-lanes", &value);
		अगर (err < 0) अणु
			dev_err(dev, "failed to parse # of lanes: %d\n",
				err);
			जाओ err_node_put;
		पूर्ण

		अगर (value > 16) अणु
			dev_err(dev, "invalid # of lanes: %u\n", value);
			err = -EINVAL;
			जाओ err_node_put;
		पूर्ण

		lanes |= value << (index << 3);

		अगर (!of_device_is_available(port)) अणु
			lane += value;
			जारी;
		पूर्ण

		mask |= ((1 << value) - 1) << lane;
		lane += value;

		rp = devm_kzalloc(dev, माप(*rp), GFP_KERNEL);
		अगर (!rp) अणु
			err = -ENOMEM;
			जाओ err_node_put;
		पूर्ण

		err = of_address_to_resource(port, 0, &rp->regs);
		अगर (err < 0) अणु
			dev_err(dev, "failed to parse address: %d\n", err);
			जाओ err_node_put;
		पूर्ण

		INIT_LIST_HEAD(&rp->list);
		rp->index = index;
		rp->lanes = value;
		rp->pcie = pcie;
		rp->np = port;

		rp->base = devm_pci_remap_cfg_resource(dev, &rp->regs);
		अगर (IS_ERR(rp->base))
			वापस PTR_ERR(rp->base);

		label = devm_kaप्र_लिखो(dev, GFP_KERNEL, "pex-reset-%u", index);
		अगर (!label) अणु
			dev_err(dev, "failed to create reset GPIO label\n");
			वापस -ENOMEM;
		पूर्ण

		/*
		 * Returns -ENOENT अगर reset-gpios property is not populated
		 * and in this हाल fall back to using AFI per port रेजिस्टर
		 * to toggle PERST# SFIO line.
		 */
		rp->reset_gpio = devm_gpiod_get_from_of_node(dev, port,
							     "reset-gpios", 0,
							     GPIOD_OUT_LOW,
							     label);
		अगर (IS_ERR(rp->reset_gpio)) अणु
			अगर (PTR_ERR(rp->reset_gpio) == -ENOENT) अणु
				rp->reset_gpio = शून्य;
			पूर्ण अन्यथा अणु
				dev_err(dev, "failed to get reset GPIO: %ld\n",
					PTR_ERR(rp->reset_gpio));
				वापस PTR_ERR(rp->reset_gpio);
			पूर्ण
		पूर्ण

		list_add_tail(&rp->list, &pcie->ports);
	पूर्ण

	err = tegra_pcie_get_xbar_config(pcie, lanes, &pcie->xbar_config);
	अगर (err < 0) अणु
		dev_err(dev, "invalid lane configuration\n");
		वापस err;
	पूर्ण

	err = tegra_pcie_get_regulators(pcie, mask);
	अगर (err < 0)
		वापस err;

	वापस 0;

err_node_put:
	of_node_put(port);
	वापस err;
पूर्ण

/*
 * FIXME: If there are no PCIe cards attached, then calling this function
 * can result in the increase of the bootup समय as there are big समयout
 * loops.
 */
#घोषणा TEGRA_PCIE_LINKUP_TIMEOUT	200	/* up to 1.2 seconds */
अटल bool tegra_pcie_port_check_link(काष्ठा tegra_pcie_port *port)
अणु
	काष्ठा device *dev = port->pcie->dev;
	अचिन्हित पूर्णांक retries = 3;
	अचिन्हित दीर्घ value;

	/* override presence detection */
	value = पढ़ोl(port->base + RP_PRIV_MISC);
	value &= ~RP_PRIV_MISC_PRSNT_MAP_EP_ABSNT;
	value |= RP_PRIV_MISC_PRSNT_MAP_EP_PRSNT;
	ग_लिखोl(value, port->base + RP_PRIV_MISC);

	करो अणु
		अचिन्हित पूर्णांक समयout = TEGRA_PCIE_LINKUP_TIMEOUT;

		करो अणु
			value = पढ़ोl(port->base + RP_VEND_XP);

			अगर (value & RP_VEND_XP_DL_UP)
				अवरोध;

			usleep_range(1000, 2000);
		पूर्ण जबतक (--समयout);

		अगर (!समयout) अणु
			dev_dbg(dev, "link %u down, retrying\n", port->index);
			जाओ retry;
		पूर्ण

		समयout = TEGRA_PCIE_LINKUP_TIMEOUT;

		करो अणु
			value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS);

			अगर (value & RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE)
				वापस true;

			usleep_range(1000, 2000);
		पूर्ण जबतक (--समयout);

retry:
		tegra_pcie_port_reset(port);
	पूर्ण जबतक (--retries);

	वापस false;
पूर्ण

अटल व्योम tegra_pcie_change_link_speed(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा tegra_pcie_port *port;
	kसमय_प्रकार deadline;
	u32 value;

	list_क्रम_each_entry(port, &pcie->ports, list) अणु
		/*
		 * "Supported Link Speeds Vector" in "Link Capabilities 2"
		 * is not supported by Tegra. tegra_pcie_change_link_speed()
		 * is called only क्रम Tegra chips which support Gen2.
		 * So there no harm अगर supported link speed is not verअगरied.
		 */
		value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS_2);
		value &= ~PCI_EXP_LNKSTA_CLS;
		value |= PCI_EXP_LNKSTA_CLS_5_0GB;
		ग_लिखोl(value, port->base + RP_LINK_CONTROL_STATUS_2);

		/*
		 * Poll until link comes back from recovery to aव्योम race
		 * condition.
		 */
		deadline = kसमय_add_us(kसमय_get(), LINK_RETRAIN_TIMEOUT);

		जबतक (kसमय_beक्रमe(kसमय_get(), deadline)) अणु
			value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS);
			अगर ((value & PCI_EXP_LNKSTA_LT) == 0)
				अवरोध;

			usleep_range(2000, 3000);
		पूर्ण

		अगर (value & PCI_EXP_LNKSTA_LT)
			dev_warn(dev, "PCIe port %u link is in recovery\n",
				 port->index);

		/* Retrain the link */
		value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS);
		value |= PCI_EXP_LNKCTL_RL;
		ग_लिखोl(value, port->base + RP_LINK_CONTROL_STATUS);

		deadline = kसमय_add_us(kसमय_get(), LINK_RETRAIN_TIMEOUT);

		जबतक (kसमय_beक्रमe(kसमय_get(), deadline)) अणु
			value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS);
			अगर ((value & PCI_EXP_LNKSTA_LT) == 0)
				अवरोध;

			usleep_range(2000, 3000);
		पूर्ण

		अगर (value & PCI_EXP_LNKSTA_LT)
			dev_err(dev, "failed to retrain link of port %u\n",
				port->index);
	पूर्ण
पूर्ण

अटल व्योम tegra_pcie_enable_ports(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा tegra_pcie_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list) अणु
		dev_info(dev, "probing port %u, using %u lanes\n",
			 port->index, port->lanes);

		tegra_pcie_port_enable(port);
	पूर्ण

	/* Start LTSSM from Tegra side */
	reset_control_deनिश्चित(pcie->pcie_xrst);

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list) अणु
		अगर (tegra_pcie_port_check_link(port))
			जारी;

		dev_info(dev, "link %u down, ignoring\n", port->index);

		tegra_pcie_port_disable(port);
		tegra_pcie_port_मुक्त(port);
	पूर्ण

	अगर (pcie->soc->has_gen2)
		tegra_pcie_change_link_speed(pcie);
पूर्ण

अटल व्योम tegra_pcie_disable_ports(काष्ठा tegra_pcie *pcie)
अणु
	काष्ठा tegra_pcie_port *port, *पंचांगp;

	reset_control_निश्चित(pcie->pcie_xrst);

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list)
		tegra_pcie_port_disable(port);
पूर्ण

अटल स्थिर काष्ठा tegra_pcie_port_soc tegra20_pcie_ports[] = अणु
	अणु .pme.turnoff_bit = 0, .pme.ack_bit =  5 पूर्ण,
	अणु .pme.turnoff_bit = 8, .pme.ack_bit = 10 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_soc tegra20_pcie = अणु
	.num_ports = 2,
	.ports = tegra20_pcie_ports,
	.msi_base_shअगरt = 0,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA20,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_DIV10,
	.pads_refclk_cfg0 = 0xfa5cfa5c,
	.has_pex_clkreq_en = false,
	.has_pex_bias_ctrl = false,
	.has_पूर्णांकr_prsnt_sense = false,
	.has_cml_clk = false,
	.has_gen2 = false,
	.क्रमce_pca_enable = false,
	.program_uphy = true,
	.update_clamp_threshold = false,
	.program_deskew_समय = false,
	.update_fc_समयr = false,
	.has_cache_bars = true,
	.ectl.enable = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_port_soc tegra30_pcie_ports[] = अणु
	अणु .pme.turnoff_bit =  0, .pme.ack_bit =  5 पूर्ण,
	अणु .pme.turnoff_bit =  8, .pme.ack_bit = 10 पूर्ण,
	अणु .pme.turnoff_bit = 16, .pme.ack_bit = 18 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_soc tegra30_pcie = अणु
	.num_ports = 3,
	.ports = tegra30_pcie_ports,
	.msi_base_shअगरt = 8,
	.afi_pex2_ctrl = 0x128,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.pads_refclk_cfg0 = 0xfa5cfa5c,
	.pads_refclk_cfg1 = 0xfa5cfa5c,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_पूर्णांकr_prsnt_sense = true,
	.has_cml_clk = true,
	.has_gen2 = false,
	.क्रमce_pca_enable = false,
	.program_uphy = true,
	.update_clamp_threshold = false,
	.program_deskew_समय = false,
	.update_fc_समयr = false,
	.has_cache_bars = false,
	.ectl.enable = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_soc tegra124_pcie = अणु
	.num_ports = 2,
	.ports = tegra20_pcie_ports,
	.msi_base_shअगरt = 8,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.pads_refclk_cfg0 = 0x44ac44ac,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_पूर्णांकr_prsnt_sense = true,
	.has_cml_clk = true,
	.has_gen2 = true,
	.क्रमce_pca_enable = false,
	.program_uphy = true,
	.update_clamp_threshold = true,
	.program_deskew_समय = false,
	.update_fc_समयr = false,
	.has_cache_bars = false,
	.ectl.enable = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_soc tegra210_pcie = अणु
	.num_ports = 2,
	.ports = tegra20_pcie_ports,
	.msi_base_shअगरt = 8,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.pads_refclk_cfg0 = 0x90b890b8,
	/* FC threshold is bit[25:18] */
	.update_fc_threshold = 0x01800000,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_पूर्णांकr_prsnt_sense = true,
	.has_cml_clk = true,
	.has_gen2 = true,
	.क्रमce_pca_enable = true,
	.program_uphy = true,
	.update_clamp_threshold = true,
	.program_deskew_समय = true,
	.update_fc_समयr = true,
	.has_cache_bars = false,
	.ectl = अणु
		.regs = अणु
			.rp_ectl_2_r1 = 0x0000000f,
			.rp_ectl_4_r1 = 0x00000067,
			.rp_ectl_5_r1 = 0x55010000,
			.rp_ectl_6_r1 = 0x00000001,
			.rp_ectl_2_r2 = 0x0000008f,
			.rp_ectl_4_r2 = 0x000000c7,
			.rp_ectl_5_r2 = 0x55010000,
			.rp_ectl_6_r2 = 0x00000001,
		पूर्ण,
		.enable = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_port_soc tegra186_pcie_ports[] = अणु
	अणु .pme.turnoff_bit =  0, .pme.ack_bit =  5 पूर्ण,
	अणु .pme.turnoff_bit =  8, .pme.ack_bit = 10 पूर्ण,
	अणु .pme.turnoff_bit = 12, .pme.ack_bit = 14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_pcie_soc tegra186_pcie = अणु
	.num_ports = 3,
	.ports = tegra186_pcie_ports,
	.msi_base_shअगरt = 8,
	.afi_pex2_ctrl = 0x19c,
	.pads_pll_ctl = PADS_PLL_CTL_TEGRA30,
	.tx_ref_sel = PADS_PLL_CTL_TXCLKREF_BUF_EN,
	.pads_refclk_cfg0 = 0x80b880b8,
	.pads_refclk_cfg1 = 0x000480b8,
	.has_pex_clkreq_en = true,
	.has_pex_bias_ctrl = true,
	.has_पूर्णांकr_prsnt_sense = true,
	.has_cml_clk = false,
	.has_gen2 = true,
	.क्रमce_pca_enable = false,
	.program_uphy = false,
	.update_clamp_threshold = false,
	.program_deskew_समय = false,
	.update_fc_समयr = false,
	.has_cache_bars = false,
	.ectl.enable = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_pcie_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-pcie", .data = &tegra186_pcie पूर्ण,
	अणु .compatible = "nvidia,tegra210-pcie", .data = &tegra210_pcie पूर्ण,
	अणु .compatible = "nvidia,tegra124-pcie", .data = &tegra124_pcie पूर्ण,
	अणु .compatible = "nvidia,tegra30-pcie", .data = &tegra30_pcie पूर्ण,
	अणु .compatible = "nvidia,tegra20-pcie", .data = &tegra20_pcie पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम *tegra_pcie_ports_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा tegra_pcie *pcie = s->निजी;

	अगर (list_empty(&pcie->ports))
		वापस शून्य;

	seq_म_लिखो(s, "Index  Status\n");

	वापस seq_list_start(&pcie->ports, *pos);
पूर्ण

अटल व्योम *tegra_pcie_ports_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा tegra_pcie *pcie = s->निजी;

	वापस seq_list_next(v, &pcie->ports, pos);
पूर्ण

अटल व्योम tegra_pcie_ports_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक tegra_pcie_ports_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	bool up = false, active = false;
	काष्ठा tegra_pcie_port *port;
	अचिन्हित पूर्णांक value;

	port = list_entry(v, काष्ठा tegra_pcie_port, list);

	value = पढ़ोl(port->base + RP_VEND_XP);

	अगर (value & RP_VEND_XP_DL_UP)
		up = true;

	value = पढ़ोl(port->base + RP_LINK_CONTROL_STATUS);

	अगर (value & RP_LINK_CONTROL_STATUS_DL_LINK_ACTIVE)
		active = true;

	seq_म_लिखो(s, "%2u     ", port->index);

	अगर (up)
		seq_म_लिखो(s, "up");

	अगर (active) अणु
		अगर (up)
			seq_म_लिखो(s, ", ");

		seq_म_लिखो(s, "active");
	पूर्ण

	seq_म_लिखो(s, "\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations tegra_pcie_ports_sops = अणु
	.start = tegra_pcie_ports_seq_start,
	.next = tegra_pcie_ports_seq_next,
	.stop = tegra_pcie_ports_seq_stop,
	.show = tegra_pcie_ports_seq_show,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(tegra_pcie_ports);

अटल व्योम tegra_pcie_debugfs_निकास(काष्ठा tegra_pcie *pcie)
अणु
	debugfs_हटाओ_recursive(pcie->debugfs);
	pcie->debugfs = शून्य;
पूर्ण

अटल व्योम tegra_pcie_debugfs_init(काष्ठा tegra_pcie *pcie)
अणु
	pcie->debugfs = debugfs_create_dir("pcie", शून्य);

	debugfs_create_file("ports", S_IFREG | S_IRUGO, pcie->debugfs, pcie,
			    &tegra_pcie_ports_fops);
पूर्ण

अटल पूर्णांक tegra_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *host;
	काष्ठा tegra_pcie *pcie;
	पूर्णांक err;

	host = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!host)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(host);
	host->sysdata = pcie;
	platक्रमm_set_drvdata(pdev, pcie);

	pcie->soc = of_device_get_match_data(dev);
	INIT_LIST_HEAD(&pcie->ports);
	pcie->dev = dev;

	err = tegra_pcie_parse_dt(pcie);
	अगर (err < 0)
		वापस err;

	err = tegra_pcie_get_resources(pcie);
	अगर (err < 0) अणु
		dev_err(dev, "failed to request resources: %d\n", err);
		वापस err;
	पूर्ण

	err = tegra_pcie_msi_setup(pcie);
	अगर (err < 0) अणु
		dev_err(dev, "failed to enable MSI support: %d\n", err);
		जाओ put_resources;
	पूर्ण

	pm_runसमय_enable(pcie->dev);
	err = pm_runसमय_get_sync(pcie->dev);
	अगर (err < 0) अणु
		dev_err(dev, "fail to enable pcie controller: %d\n", err);
		जाओ pm_runसमय_put;
	पूर्ण

	host->ops = &tegra_pcie_ops;
	host->map_irq = tegra_pcie_map_irq;

	err = pci_host_probe(host);
	अगर (err < 0) अणु
		dev_err(dev, "failed to register host: %d\n", err);
		जाओ pm_runसमय_put;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_pcie_debugfs_init(pcie);

	वापस 0;

pm_runसमय_put:
	pm_runसमय_put_sync(pcie->dev);
	pm_runसमय_disable(pcie->dev);
	tegra_pcie_msi_tearकरोwn(pcie);
put_resources:
	tegra_pcie_put_resources(pcie);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	काष्ठा tegra_pcie_port *port, *पंचांगp;

	अगर (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_pcie_debugfs_निकास(pcie);

	pci_stop_root_bus(host->bus);
	pci_हटाओ_root_bus(host->bus);
	pm_runसमय_put_sync(pcie->dev);
	pm_runसमय_disable(pcie->dev);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_pcie_msi_tearकरोwn(pcie);

	tegra_pcie_put_resources(pcie);

	list_क्रम_each_entry_safe(port, पंचांगp, &pcie->ports, list)
		tegra_pcie_port_मुक्त(port);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_pcie_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie *pcie = dev_get_drvdata(dev);
	काष्ठा tegra_pcie_port *port;
	पूर्णांक err;

	list_क्रम_each_entry(port, &pcie->ports, list)
		tegra_pcie_pme_turnoff(port);

	tegra_pcie_disable_ports(pcie);

	/*
	 * AFI_INTR is unmasked in tegra_pcie_enable_controller(), mask it to
	 * aव्योम unwanted पूर्णांकerrupts उठाओd by AFI after pex_rst is निश्चितed.
	 */
	tegra_pcie_disable_पूर्णांकerrupts(pcie);

	अगर (pcie->soc->program_uphy) अणु
		err = tegra_pcie_phy_घातer_off(pcie);
		अगर (err < 0)
			dev_err(dev, "failed to power off PHY(s): %d\n", err);
	पूर्ण

	reset_control_निश्चित(pcie->pex_rst);
	clk_disable_unprepare(pcie->pex_clk);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_pcie_disable_msi(pcie);

	pinctrl_pm_select_idle_state(dev);
	tegra_pcie_घातer_off(pcie);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_pcie_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_pcie *pcie = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_pcie_घातer_on(pcie);
	अगर (err) अणु
		dev_err(dev, "tegra pcie power on fail: %d\n", err);
		वापस err;
	पूर्ण

	err = pinctrl_pm_select_शेष_state(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to disable PCIe IO DPD: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	tegra_pcie_enable_controller(pcie);
	tegra_pcie_setup_translations(pcie);

	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		tegra_pcie_enable_msi(pcie);

	err = clk_prepare_enable(pcie->pex_clk);
	अगर (err) अणु
		dev_err(dev, "failed to enable PEX clock: %d\n", err);
		जाओ pex_dpd_enable;
	पूर्ण

	reset_control_deनिश्चित(pcie->pex_rst);

	अगर (pcie->soc->program_uphy) अणु
		err = tegra_pcie_phy_घातer_on(pcie);
		अगर (err < 0) अणु
			dev_err(dev, "failed to power on PHY(s): %d\n", err);
			जाओ disable_pex_clk;
		पूर्ण
	पूर्ण

	tegra_pcie_apply_pad_settings(pcie);
	tegra_pcie_enable_ports(pcie);

	वापस 0;

disable_pex_clk:
	reset_control_निश्चित(pcie->pex_rst);
	clk_disable_unprepare(pcie->pex_clk);
pex_dpd_enable:
	pinctrl_pm_select_idle_state(dev);
घातeroff:
	tegra_pcie_घातer_off(pcie);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_pcie_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_pcie_pm_suspend, tegra_pcie_pm_resume, शून्य)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(tegra_pcie_pm_suspend,
				      tegra_pcie_pm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_pcie_driver = अणु
	.driver = अणु
		.name = "tegra-pcie",
		.of_match_table = tegra_pcie_of_match,
		.suppress_bind_attrs = true,
		.pm = &tegra_pcie_pm_ops,
	पूर्ण,
	.probe = tegra_pcie_probe,
	.हटाओ = tegra_pcie_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_pcie_driver);
MODULE_LICENSE("GPL");
