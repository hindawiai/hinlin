<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2009 - 2019 Broadcom */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/reset.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "../pci.h"

/* BRCM_PCIE_CAP_REGS - Offset क्रम the mandatory capability config regs */
#घोषणा BRCM_PCIE_CAP_REGS				0x00ac

/* Broadcom STB PCIe Register Offsets */
#घोषणा PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1				0x0188
#घोषणा  PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1_ENDIAN_MODE_BAR2_MASK	0xc
#घोषणा  PCIE_RC_CFG_VENDOR_SPCIFIC_REG1_LITTLE_ENDIAN			0x0

#घोषणा PCIE_RC_CFG_PRIV1_ID_VAL3			0x043c
#घोषणा  PCIE_RC_CFG_PRIV1_ID_VAL3_CLASS_CODE_MASK	0xffffff

#घोषणा PCIE_RC_CFG_PRIV1_LINK_CAPABILITY			0x04dc
#घोषणा  PCIE_RC_CFG_PRIV1_LINK_CAPABILITY_ASPM_SUPPORT_MASK	0xc00

#घोषणा PCIE_RC_DL_MDIO_ADDR				0x1100
#घोषणा PCIE_RC_DL_MDIO_WR_DATA				0x1104
#घोषणा PCIE_RC_DL_MDIO_RD_DATA				0x1108

#घोषणा PCIE_MISC_MISC_CTRL				0x4008
#घोषणा  PCIE_MISC_MISC_CTRL_SCB_ACCESS_EN_MASK		0x1000
#घोषणा  PCIE_MISC_MISC_CTRL_CFG_READ_UR_MODE_MASK	0x2000
#घोषणा  PCIE_MISC_MISC_CTRL_MAX_BURST_SIZE_MASK	0x300000

#घोषणा  PCIE_MISC_MISC_CTRL_SCB0_SIZE_MASK		0xf8000000
#घोषणा  PCIE_MISC_MISC_CTRL_SCB1_SIZE_MASK		0x07c00000
#घोषणा  PCIE_MISC_MISC_CTRL_SCB2_SIZE_MASK		0x0000001f
#घोषणा  SCB_SIZE_MASK(x) PCIE_MISC_MISC_CTRL_SCB ## x ## _SIZE_MASK

#घोषणा PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO		0x400c
#घोषणा PCIE_MEM_WIN0_LO(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LO + ((win) * 8)

#घोषणा PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI		0x4010
#घोषणा PCIE_MEM_WIN0_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_HI + ((win) * 8)

#घोषणा PCIE_MISC_RC_BAR1_CONFIG_LO			0x402c
#घोषणा  PCIE_MISC_RC_BAR1_CONFIG_LO_SIZE_MASK		0x1f

#घोषणा PCIE_MISC_RC_BAR2_CONFIG_LO			0x4034
#घोषणा  PCIE_MISC_RC_BAR2_CONFIG_LO_SIZE_MASK		0x1f
#घोषणा PCIE_MISC_RC_BAR2_CONFIG_HI			0x4038

#घोषणा PCIE_MISC_RC_BAR3_CONFIG_LO			0x403c
#घोषणा  PCIE_MISC_RC_BAR3_CONFIG_LO_SIZE_MASK		0x1f

#घोषणा PCIE_MISC_MSI_BAR_CONFIG_LO			0x4044
#घोषणा PCIE_MISC_MSI_BAR_CONFIG_HI			0x4048

#घोषणा PCIE_MISC_MSI_DATA_CONFIG			0x404c
#घोषणा  PCIE_MISC_MSI_DATA_CONFIG_VAL_32		0xffe06540
#घोषणा  PCIE_MISC_MSI_DATA_CONFIG_VAL_8		0xfff86540

#घोषणा PCIE_MISC_PCIE_CTRL				0x4064
#घोषणा  PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK	0x1
#घोषणा PCIE_MISC_PCIE_CTRL_PCIE_PERSTB_MASK		0x4

#घोषणा PCIE_MISC_PCIE_STATUS				0x4068
#घोषणा  PCIE_MISC_PCIE_STATUS_PCIE_PORT_MASK		0x80
#घोषणा  PCIE_MISC_PCIE_STATUS_PCIE_DL_ACTIVE_MASK	0x20
#घोषणा  PCIE_MISC_PCIE_STATUS_PCIE_PHYLINKUP_MASK	0x10
#घोषणा  PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK	0x40

#घोषणा PCIE_MISC_REVISION				0x406c
#घोषणा  BRCM_PCIE_HW_REV_33				0x0303
#घोषणा  BRCM_PCIE_HW_REV_3_20				0x0320

#घोषणा PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT		0x4070
#घोषणा  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_LIMIT_MASK	0xfff00000
#घोषणा  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK	0xfff0
#घोषणा PCIE_MEM_WIN0_BASE_LIMIT(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT + ((win) * 4)

#घोषणा PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI			0x4080
#घोषणा  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK	0xff
#घोषणा PCIE_MEM_WIN0_BASE_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI + ((win) * 8)

#घोषणा PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI			0x4084
#घोषणा  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI_LIMIT_MASK	0xff
#घोषणा PCIE_MEM_WIN0_LIMIT_HI(win)	\
		PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI + ((win) * 8)

#घोषणा PCIE_MISC_HARD_PCIE_HARD_DEBUG					0x4204
#घोषणा  PCIE_MISC_HARD_PCIE_HARD_DEBUG_CLKREQ_DEBUG_ENABLE_MASK	0x2
#घोषणा  PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK		0x08000000


#घोषणा PCIE_INTR2_CPU_BASE		0x4300
#घोषणा PCIE_MSI_INTR2_BASE		0x4500
/* Offsets from PCIE_INTR2_CPU_BASE and PCIE_MSI_INTR2_BASE */
#घोषणा  MSI_INT_STATUS			0x0
#घोषणा  MSI_INT_CLR			0x8
#घोषणा  MSI_INT_MASK_SET		0x10
#घोषणा  MSI_INT_MASK_CLR		0x14

#घोषणा PCIE_EXT_CFG_DATA				0x8000
#घोषणा PCIE_EXT_CFG_INDEX				0x9000

#घोषणा  PCIE_RGR1_SW_INIT_1_PERST_MASK			0x1
#घोषणा  PCIE_RGR1_SW_INIT_1_PERST_SHIFT		0x0

#घोषणा RGR1_SW_INIT_1_INIT_GENERIC_MASK		0x2
#घोषणा RGR1_SW_INIT_1_INIT_GENERIC_SHIFT		0x1
#घोषणा RGR1_SW_INIT_1_INIT_7278_MASK			0x1
#घोषणा RGR1_SW_INIT_1_INIT_7278_SHIFT			0x0

/* PCIe parameters */
#घोषणा BRCM_NUM_PCIE_OUT_WINS		0x4
#घोषणा BRCM_INT_PCI_MSI_NR		32
#घोषणा BRCM_INT_PCI_MSI_LEGACY_NR	8
#घोषणा BRCM_INT_PCI_MSI_SHIFT		0

/* MSI target adresses */
#घोषणा BRCM_MSI_TARGET_ADDR_LT_4GB	0x0fffffffcULL
#घोषणा BRCM_MSI_TARGET_ADDR_GT_4GB	0xffffffffcULL

/* MDIO रेजिस्टरs */
#घोषणा MDIO_PORT0			0x0
#घोषणा MDIO_DATA_MASK			0x7fffffff
#घोषणा MDIO_PORT_MASK			0xf0000
#घोषणा MDIO_REGAD_MASK			0xffff
#घोषणा MDIO_CMD_MASK			0xfff00000
#घोषणा MDIO_CMD_READ			0x1
#घोषणा MDIO_CMD_WRITE			0x0
#घोषणा MDIO_DATA_DONE_MASK		0x80000000
#घोषणा MDIO_RD_DONE(x)			(((x) & MDIO_DATA_DONE_MASK) ? 1 : 0)
#घोषणा MDIO_WT_DONE(x)			(((x) & MDIO_DATA_DONE_MASK) ? 0 : 1)
#घोषणा SSC_REGS_ADDR			0x1100
#घोषणा SET_ADDR_OFFSET			0x1f
#घोषणा SSC_CNTL_OFFSET			0x2
#घोषणा SSC_CNTL_OVRD_EN_MASK		0x8000
#घोषणा SSC_CNTL_OVRD_VAL_MASK		0x4000
#घोषणा SSC_STATUS_OFFSET		0x1
#घोषणा SSC_STATUS_SSC_MASK		0x400
#घोषणा SSC_STATUS_PLL_LOCK_MASK	0x800
#घोषणा PCIE_BRCM_MAX_MEMC		3

#घोषणा IDX_ADDR(pcie)			(pcie->reg_offsets[EXT_CFG_INDEX])
#घोषणा DATA_ADDR(pcie)			(pcie->reg_offsets[EXT_CFG_DATA])
#घोषणा PCIE_RGR1_SW_INIT_1(pcie)	(pcie->reg_offsets[RGR1_SW_INIT_1])

/* Rescal रेजिस्टरs */
#घोषणा PCIE_DVT_PMU_PCIE_PHY_CTRL				0xc700
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_NFLDS			0x3
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_DIG_RESET_MASK		0x4
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_DIG_RESET_SHIFT	0x2
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_RESET_MASK		0x2
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_RESET_SHIFT		0x1
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_PWRDN_MASK		0x1
#घोषणा  PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_PWRDN_SHIFT		0x0

/* Forward declarations */
काष्ठा brcm_pcie;
अटल अंतरभूत व्योम brcm_pcie_bridge_sw_init_set_7278(काष्ठा brcm_pcie *pcie, u32 val);
अटल अंतरभूत व्योम brcm_pcie_bridge_sw_init_set_generic(काष्ठा brcm_pcie *pcie, u32 val);
अटल अंतरभूत व्योम brcm_pcie_perst_set_4908(काष्ठा brcm_pcie *pcie, u32 val);
अटल अंतरभूत व्योम brcm_pcie_perst_set_7278(काष्ठा brcm_pcie *pcie, u32 val);
अटल अंतरभूत व्योम brcm_pcie_perst_set_generic(काष्ठा brcm_pcie *pcie, u32 val);

क्रमागत अणु
	RGR1_SW_INIT_1,
	EXT_CFG_INDEX,
	EXT_CFG_DATA,
पूर्ण;

क्रमागत अणु
	RGR1_SW_INIT_1_INIT_MASK,
	RGR1_SW_INIT_1_INIT_SHIFT,
पूर्ण;

क्रमागत pcie_type अणु
	GENERIC,
	BCM4908,
	BCM7278,
	BCM2711,
पूर्ण;

काष्ठा pcie_cfg_data अणु
	स्थिर पूर्णांक *offsets;
	स्थिर क्रमागत pcie_type type;
	व्योम (*perst_set)(काष्ठा brcm_pcie *pcie, u32 val);
	व्योम (*bridge_sw_init_set)(काष्ठा brcm_pcie *pcie, u32 val);
पूर्ण;

अटल स्थिर पूर्णांक pcie_offsets[] = अणु
	[RGR1_SW_INIT_1] = 0x9210,
	[EXT_CFG_INDEX]  = 0x9000,
	[EXT_CFG_DATA]   = 0x9004,
पूर्ण;

अटल स्थिर काष्ठा pcie_cfg_data generic_cfg = अणु
	.offsets	= pcie_offsets,
	.type		= GENERIC,
	.perst_set	= brcm_pcie_perst_set_generic,
	.bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
पूर्ण;

अटल स्थिर काष्ठा pcie_cfg_data bcm4908_cfg = अणु
	.offsets	= pcie_offsets,
	.type		= BCM4908,
	.perst_set	= brcm_pcie_perst_set_4908,
	.bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
पूर्ण;

अटल स्थिर पूर्णांक pcie_offset_bcm7278[] = अणु
	[RGR1_SW_INIT_1] = 0xc010,
	[EXT_CFG_INDEX] = 0x9000,
	[EXT_CFG_DATA] = 0x9004,
पूर्ण;

अटल स्थिर काष्ठा pcie_cfg_data bcm7278_cfg = अणु
	.offsets	= pcie_offset_bcm7278,
	.type		= BCM7278,
	.perst_set	= brcm_pcie_perst_set_7278,
	.bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_7278,
पूर्ण;

अटल स्थिर काष्ठा pcie_cfg_data bcm2711_cfg = अणु
	.offsets	= pcie_offsets,
	.type		= BCM2711,
	.perst_set	= brcm_pcie_perst_set_generic,
	.bridge_sw_init_set = brcm_pcie_bridge_sw_init_set_generic,
पूर्ण;

काष्ठा brcm_msi अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा device_node	*np;
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
	काष्ठा irq_करोमुख्य	*inner_करोमुख्य;
	काष्ठा mutex		lock; /* guards the alloc/मुक्त operations */
	u64			target_addr;
	पूर्णांक			irq;
	/* used indicates which MSI पूर्णांकerrupts have been alloc'd */
	अचिन्हित दीर्घ		used;
	bool			legacy;
	/* Some chips have MSIs in bits [31..24] of a shared रेजिस्टर. */
	पूर्णांक			legacy_shअगरt;
	पूर्णांक			nr; /* No. of MSI available, depends on chip */
	/* This is the base poपूर्णांकer क्रम पूर्णांकerrupt status/set/clr regs */
	व्योम __iomem		*पूर्णांकr_base;
पूर्ण;

/* Internal PCIe Host Controller Inक्रमmation.*/
काष्ठा brcm_pcie अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा device_node	*np;
	bool			ssc;
	पूर्णांक			gen;
	u64			msi_target_addr;
	काष्ठा brcm_msi		*msi;
	स्थिर पूर्णांक		*reg_offsets;
	क्रमागत pcie_type		type;
	काष्ठा reset_control	*rescal;
	काष्ठा reset_control	*perst_reset;
	पूर्णांक			num_memc;
	u64			memc_size[PCIE_BRCM_MAX_MEMC];
	u32			hw_rev;
	व्योम			(*perst_set)(काष्ठा brcm_pcie *pcie, u32 val);
	व्योम			(*bridge_sw_init_set)(काष्ठा brcm_pcie *pcie, u32 val);
पूर्ण;

/*
 * This is to convert the size of the inbound "BAR" region to the
 * non-linear values of PCIE_X_MISC_RC_BAR[123]_CONFIG_LO.SIZE
 */
अटल पूर्णांक brcm_pcie_encode_ibar_size(u64 size)
अणु
	पूर्णांक log2_in = ilog2(size);

	अगर (log2_in >= 12 && log2_in <= 15)
		/* Covers 4KB to 32KB (inclusive) */
		वापस (log2_in - 12) + 0x1c;
	अन्यथा अगर (log2_in >= 16 && log2_in <= 35)
		/* Covers 64KB to 32GB, (inclusive) */
		वापस log2_in - 15;
	/* Something is awry so disable */
	वापस 0;
पूर्ण

अटल u32 brcm_pcie_mdio_क्रमm_pkt(पूर्णांक port, पूर्णांक regad, पूर्णांक cmd)
अणु
	u32 pkt = 0;

	pkt |= FIELD_PREP(MDIO_PORT_MASK, port);
	pkt |= FIELD_PREP(MDIO_REGAD_MASK, regad);
	pkt |= FIELD_PREP(MDIO_CMD_MASK, cmd);

	वापस pkt;
पूर्ण

/* negative वापस value indicates error */
अटल पूर्णांक brcm_pcie_mdio_पढ़ो(व्योम __iomem *base, u8 port, u8 regad, u32 *val)
अणु
	पूर्णांक tries;
	u32 data;

	ग_लिखोl(brcm_pcie_mdio_क्रमm_pkt(port, regad, MDIO_CMD_READ),
		   base + PCIE_RC_DL_MDIO_ADDR);
	पढ़ोl(base + PCIE_RC_DL_MDIO_ADDR);

	data = पढ़ोl(base + PCIE_RC_DL_MDIO_RD_DATA);
	क्रम (tries = 0; !MDIO_RD_DONE(data) && tries < 10; tries++) अणु
		udelay(10);
		data = पढ़ोl(base + PCIE_RC_DL_MDIO_RD_DATA);
	पूर्ण

	*val = FIELD_GET(MDIO_DATA_MASK, data);
	वापस MDIO_RD_DONE(data) ? 0 : -EIO;
पूर्ण

/* negative वापस value indicates error */
अटल पूर्णांक brcm_pcie_mdio_ग_लिखो(व्योम __iomem *base, u8 port,
				u8 regad, u16 wrdata)
अणु
	पूर्णांक tries;
	u32 data;

	ग_लिखोl(brcm_pcie_mdio_क्रमm_pkt(port, regad, MDIO_CMD_WRITE),
		   base + PCIE_RC_DL_MDIO_ADDR);
	पढ़ोl(base + PCIE_RC_DL_MDIO_ADDR);
	ग_लिखोl(MDIO_DATA_DONE_MASK | wrdata, base + PCIE_RC_DL_MDIO_WR_DATA);

	data = पढ़ोl(base + PCIE_RC_DL_MDIO_WR_DATA);
	क्रम (tries = 0; !MDIO_WT_DONE(data) && tries < 10; tries++) अणु
		udelay(10);
		data = पढ़ोl(base + PCIE_RC_DL_MDIO_WR_DATA);
	पूर्ण

	वापस MDIO_WT_DONE(data) ? 0 : -EIO;
पूर्ण

/*
 * Configures device क्रम Spपढ़ो Spectrum Clocking (SSC) mode; a negative
 * वापस value indicates error.
 */
अटल पूर्णांक brcm_pcie_set_ssc(काष्ठा brcm_pcie *pcie)
अणु
	पूर्णांक pll, ssc;
	पूर्णांक ret;
	u32 पंचांगp;

	ret = brcm_pcie_mdio_ग_लिखो(pcie->base, MDIO_PORT0, SET_ADDR_OFFSET,
				   SSC_REGS_ADDR);
	अगर (ret < 0)
		वापस ret;

	ret = brcm_pcie_mdio_पढ़ो(pcie->base, MDIO_PORT0,
				  SSC_CNTL_OFFSET, &पंचांगp);
	अगर (ret < 0)
		वापस ret;

	u32p_replace_bits(&पंचांगp, 1, SSC_CNTL_OVRD_EN_MASK);
	u32p_replace_bits(&पंचांगp, 1, SSC_CNTL_OVRD_VAL_MASK);
	ret = brcm_pcie_mdio_ग_लिखो(pcie->base, MDIO_PORT0,
				   SSC_CNTL_OFFSET, पंचांगp);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);
	ret = brcm_pcie_mdio_पढ़ो(pcie->base, MDIO_PORT0,
				  SSC_STATUS_OFFSET, &पंचांगp);
	अगर (ret < 0)
		वापस ret;

	ssc = FIELD_GET(SSC_STATUS_SSC_MASK, पंचांगp);
	pll = FIELD_GET(SSC_STATUS_PLL_LOCK_MASK, पंचांगp);

	वापस ssc && pll ? 0 : -EIO;
पूर्ण

/* Limits operation to a specअगरic generation (1, 2, or 3) */
अटल व्योम brcm_pcie_set_gen(काष्ठा brcm_pcie *pcie, पूर्णांक gen)
अणु
	u16 lnkctl2 = पढ़ोw(pcie->base + BRCM_PCIE_CAP_REGS + PCI_EXP_LNKCTL2);
	u32 lnkcap = पढ़ोl(pcie->base + BRCM_PCIE_CAP_REGS + PCI_EXP_LNKCAP);

	lnkcap = (lnkcap & ~PCI_EXP_LNKCAP_SLS) | gen;
	ग_लिखोl(lnkcap, pcie->base + BRCM_PCIE_CAP_REGS + PCI_EXP_LNKCAP);

	lnkctl2 = (lnkctl2 & ~0xf) | gen;
	ग_लिखोw(lnkctl2, pcie->base + BRCM_PCIE_CAP_REGS + PCI_EXP_LNKCTL2);
पूर्ण

अटल व्योम brcm_pcie_set_outbound_win(काष्ठा brcm_pcie *pcie,
				       अचिन्हित पूर्णांक win, u64 cpu_addr,
				       u64 pcie_addr, u64 size)
अणु
	u32 cpu_addr_mb_high, limit_addr_mb_high;
	phys_addr_t cpu_addr_mb, limit_addr_mb;
	पूर्णांक high_addr_shअगरt;
	u32 पंचांगp;

	/* Set the base of the pcie_addr winकरोw */
	ग_लिखोl(lower_32_bits(pcie_addr), pcie->base + PCIE_MEM_WIN0_LO(win));
	ग_लिखोl(upper_32_bits(pcie_addr), pcie->base + PCIE_MEM_WIN0_HI(win));

	/* Write the addr base & limit lower bits (in MBs) */
	cpu_addr_mb = cpu_addr / SZ_1M;
	limit_addr_mb = (cpu_addr + size - 1) / SZ_1M;

	पंचांगp = पढ़ोl(pcie->base + PCIE_MEM_WIN0_BASE_LIMIT(win));
	u32p_replace_bits(&पंचांगp, cpu_addr_mb,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK);
	u32p_replace_bits(&पंचांगp, limit_addr_mb,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_LIMIT_MASK);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_MEM_WIN0_BASE_LIMIT(win));

	/* Write the cpu & limit addr upper bits */
	high_addr_shअगरt =
		HWEIGHT32(PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_BASE_MASK);

	cpu_addr_mb_high = cpu_addr_mb >> high_addr_shअगरt;
	पंचांगp = पढ़ोl(pcie->base + PCIE_MEM_WIN0_BASE_HI(win));
	u32p_replace_bits(&पंचांगp, cpu_addr_mb_high,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_BASE_HI_BASE_MASK);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_MEM_WIN0_BASE_HI(win));

	limit_addr_mb_high = limit_addr_mb >> high_addr_shअगरt;
	पंचांगp = पढ़ोl(pcie->base + PCIE_MEM_WIN0_LIMIT_HI(win));
	u32p_replace_bits(&पंचांगp, limit_addr_mb_high,
			  PCIE_MISC_CPU_2_PCIE_MEM_WIN0_LIMIT_HI_LIMIT_MASK);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_MEM_WIN0_LIMIT_HI(win));
पूर्ण

अटल काष्ठा irq_chip brcm_msi_irq_chip = अणु
	.name            = "BRCM STB PCIe MSI",
	.irq_ack         = irq_chip_ack_parent,
	.irq_mask        = pci_msi_mask_irq,
	.irq_unmask      = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info brcm_msi_करोमुख्य_info = अणु
	/* Multi MSI is supported by the controller, but not by this driver */
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS),
	.chip	= &brcm_msi_irq_chip,
पूर्ण;

अटल व्योम brcm_pcie_msi_isr(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ status, virq;
	काष्ठा brcm_msi *msi;
	काष्ठा device *dev;
	u32 bit;

	chained_irq_enter(chip, desc);
	msi = irq_desc_get_handler_data(desc);
	dev = msi->dev;

	status = पढ़ोl(msi->पूर्णांकr_base + MSI_INT_STATUS);
	status >>= msi->legacy_shअगरt;

	क्रम_each_set_bit(bit, &status, msi->nr) अणु
		virq = irq_find_mapping(msi->inner_करोमुख्य, bit);
		अगर (virq)
			generic_handle_irq(virq);
		अन्यथा
			dev_dbg(dev, "unexpected MSI\n");
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम brcm_msi_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा brcm_msi *msi = irq_data_get_irq_chip_data(data);

	msg->address_lo = lower_32_bits(msi->target_addr);
	msg->address_hi = upper_32_bits(msi->target_addr);
	msg->data = (0xffff & PCIE_MISC_MSI_DATA_CONFIG_VAL_32) | data->hwirq;
पूर्ण

अटल पूर्णांक brcm_msi_set_affinity(काष्ठा irq_data *irq_data,
				 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम brcm_msi_ack_irq(काष्ठा irq_data *data)
अणु
	काष्ठा brcm_msi *msi = irq_data_get_irq_chip_data(data);
	स्थिर पूर्णांक shअगरt_amt = data->hwirq + msi->legacy_shअगरt;

	ग_लिखोl(1 << shअगरt_amt, msi->पूर्णांकr_base + MSI_INT_CLR);
पूर्ण


अटल काष्ठा irq_chip brcm_msi_bottom_irq_chip = अणु
	.name			= "BRCM STB MSI",
	.irq_compose_msi_msg	= brcm_msi_compose_msi_msg,
	.irq_set_affinity	= brcm_msi_set_affinity,
	.irq_ack                = brcm_msi_ack_irq,
पूर्ण;

अटल पूर्णांक brcm_msi_alloc(काष्ठा brcm_msi *msi)
अणु
	पूर्णांक hwirq;

	mutex_lock(&msi->lock);
	hwirq = biपंचांगap_find_मुक्त_region(&msi->used, msi->nr, 0);
	mutex_unlock(&msi->lock);

	वापस hwirq;
पूर्ण

अटल व्योम brcm_msi_मुक्त(काष्ठा brcm_msi *msi, अचिन्हित दीर्घ hwirq)
अणु
	mutex_lock(&msi->lock);
	biपंचांगap_release_region(&msi->used, hwirq, 0);
	mutex_unlock(&msi->lock);
पूर्ण

अटल पूर्णांक brcm_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				 अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा brcm_msi *msi = करोमुख्य->host_data;
	पूर्णांक hwirq;

	hwirq = brcm_msi_alloc(msi);

	अगर (hwirq < 0)
		वापस hwirq;

	irq_करोमुख्य_set_info(करोमुख्य, virq, (irq_hw_number_t)hwirq,
			    &brcm_msi_bottom_irq_chip, करोमुख्य->host_data,
			    handle_edge_irq, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल व्योम brcm_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				 अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा brcm_msi *msi = irq_data_get_irq_chip_data(d);

	brcm_msi_मुक्त(msi, d->hwirq);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc	= brcm_irq_करोमुख्य_alloc,
	.मुक्त	= brcm_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक brcm_allocate_करोमुख्यs(काष्ठा brcm_msi *msi)
अणु
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(msi->np);
	काष्ठा device *dev = msi->dev;

	msi->inner_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, msi->nr, &msi_करोमुख्य_ops, msi);
	अगर (!msi->inner_करोमुख्य) अणु
		dev_err(dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode,
						    &brcm_msi_करोमुख्य_info,
						    msi->inner_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		dev_err(dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम brcm_मुक्त_करोमुख्यs(काष्ठा brcm_msi *msi)
अणु
	irq_करोमुख्य_हटाओ(msi->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(msi->inner_करोमुख्य);
पूर्ण

अटल व्योम brcm_msi_हटाओ(काष्ठा brcm_pcie *pcie)
अणु
	काष्ठा brcm_msi *msi = pcie->msi;

	अगर (!msi)
		वापस;
	irq_set_chained_handler_and_data(msi->irq, शून्य, शून्य);
	brcm_मुक्त_करोमुख्यs(msi);
पूर्ण

अटल व्योम brcm_msi_set_regs(काष्ठा brcm_msi *msi)
अणु
	u32 val = __GENMASK(31, msi->legacy_shअगरt);

	ग_लिखोl(val, msi->पूर्णांकr_base + MSI_INT_MASK_CLR);
	ग_लिखोl(val, msi->पूर्णांकr_base + MSI_INT_CLR);

	/*
	 * The 0 bit of PCIE_MISC_MSI_BAR_CONFIG_LO is repurposed to MSI
	 * enable, which we set to 1.
	 */
	ग_लिखोl(lower_32_bits(msi->target_addr) | 0x1,
	       msi->base + PCIE_MISC_MSI_BAR_CONFIG_LO);
	ग_लिखोl(upper_32_bits(msi->target_addr),
	       msi->base + PCIE_MISC_MSI_BAR_CONFIG_HI);

	val = msi->legacy ? PCIE_MISC_MSI_DATA_CONFIG_VAL_8 : PCIE_MISC_MSI_DATA_CONFIG_VAL_32;
	ग_लिखोl(val, msi->base + PCIE_MISC_MSI_DATA_CONFIG);
पूर्ण

अटल पूर्णांक brcm_pcie_enable_msi(काष्ठा brcm_pcie *pcie)
अणु
	काष्ठा brcm_msi *msi;
	पूर्णांक irq, ret;
	काष्ठा device *dev = pcie->dev;

	irq = irq_of_parse_and_map(dev->of_node, 1);
	अगर (irq <= 0) अणु
		dev_err(dev, "cannot map MSI interrupt\n");
		वापस -ENODEV;
	पूर्ण

	msi = devm_kzalloc(dev, माप(काष्ठा brcm_msi), GFP_KERNEL);
	अगर (!msi)
		वापस -ENOMEM;

	mutex_init(&msi->lock);
	msi->dev = dev;
	msi->base = pcie->base;
	msi->np = pcie->np;
	msi->target_addr = pcie->msi_target_addr;
	msi->irq = irq;
	msi->legacy = pcie->hw_rev < BRCM_PCIE_HW_REV_33;

	अगर (msi->legacy) अणु
		msi->पूर्णांकr_base = msi->base + PCIE_INTR2_CPU_BASE;
		msi->nr = BRCM_INT_PCI_MSI_LEGACY_NR;
		msi->legacy_shअगरt = 24;
	पूर्ण अन्यथा अणु
		msi->पूर्णांकr_base = msi->base + PCIE_MSI_INTR2_BASE;
		msi->nr = BRCM_INT_PCI_MSI_NR;
		msi->legacy_shअगरt = 0;
	पूर्ण

	ret = brcm_allocate_करोमुख्यs(msi);
	अगर (ret)
		वापस ret;

	irq_set_chained_handler_and_data(msi->irq, brcm_pcie_msi_isr, msi);

	brcm_msi_set_regs(msi);
	pcie->msi = msi;

	वापस 0;
पूर्ण

/* The controller is capable of serving in both RC and EP roles */
अटल bool brcm_pcie_rc_mode(काष्ठा brcm_pcie *pcie)
अणु
	व्योम __iomem *base = pcie->base;
	u32 val = पढ़ोl(base + PCIE_MISC_PCIE_STATUS);

	वापस !!FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_PORT_MASK, val);
पूर्ण

अटल bool brcm_pcie_link_up(काष्ठा brcm_pcie *pcie)
अणु
	u32 val = पढ़ोl(pcie->base + PCIE_MISC_PCIE_STATUS);
	u32 dla = FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_DL_ACTIVE_MASK, val);
	u32 plu = FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_PHYLINKUP_MASK, val);

	वापस dla && plu;
पूर्ण

अटल व्योम __iomem *brcm_pcie_map_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
					पूर्णांक where)
अणु
	काष्ठा brcm_pcie *pcie = bus->sysdata;
	व्योम __iomem *base = pcie->base;
	पूर्णांक idx;

	/* Accesses to the RC go right to the RC रेजिस्टरs अगर slot==0 */
	अगर (pci_is_root_bus(bus))
		वापस PCI_SLOT(devfn) ? शून्य : base + where;

	/* For devices, ग_लिखो to the config space index रेजिस्टर */
	idx = PCIE_ECAM_OFFSET(bus->number, devfn, 0);
	ग_लिखोl(idx, pcie->base + PCIE_EXT_CFG_INDEX);
	वापस base + PCIE_EXT_CFG_DATA + where;
पूर्ण

अटल काष्ठा pci_ops brcm_pcie_ops = अणु
	.map_bus = brcm_pcie_map_conf,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल अंतरभूत व्योम brcm_pcie_bridge_sw_init_set_generic(काष्ठा brcm_pcie *pcie, u32 val)
अणु
	u32 पंचांगp, mask =  RGR1_SW_INIT_1_INIT_GENERIC_MASK;
	u32 shअगरt = RGR1_SW_INIT_1_INIT_GENERIC_SHIFT;

	पंचांगp = पढ़ोl(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
	पंचांगp = (पंचांगp & ~mask) | ((val << shअगरt) & mask);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
पूर्ण

अटल अंतरभूत व्योम brcm_pcie_bridge_sw_init_set_7278(काष्ठा brcm_pcie *pcie, u32 val)
अणु
	u32 पंचांगp, mask =  RGR1_SW_INIT_1_INIT_7278_MASK;
	u32 shअगरt = RGR1_SW_INIT_1_INIT_7278_SHIFT;

	पंचांगp = पढ़ोl(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
	पंचांगp = (पंचांगp & ~mask) | ((val << shअगरt) & mask);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
पूर्ण

अटल अंतरभूत व्योम brcm_pcie_perst_set_4908(काष्ठा brcm_pcie *pcie, u32 val)
अणु
	अगर (WARN_ONCE(!pcie->perst_reset, "missing PERST# reset controller\n"))
		वापस;

	अगर (val)
		reset_control_निश्चित(pcie->perst_reset);
	अन्यथा
		reset_control_deनिश्चित(pcie->perst_reset);
पूर्ण

अटल अंतरभूत व्योम brcm_pcie_perst_set_7278(काष्ठा brcm_pcie *pcie, u32 val)
अणु
	u32 पंचांगp;

	/* Perst bit has moved and निश्चित value is 0 */
	पंचांगp = पढ़ोl(pcie->base + PCIE_MISC_PCIE_CTRL);
	u32p_replace_bits(&पंचांगp, !val, PCIE_MISC_PCIE_CTRL_PCIE_PERSTB_MASK);
	ग_लिखोl(पंचांगp, pcie->base +  PCIE_MISC_PCIE_CTRL);
पूर्ण

अटल अंतरभूत व्योम brcm_pcie_perst_set_generic(काष्ठा brcm_pcie *pcie, u32 val)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
	u32p_replace_bits(&पंचांगp, val, PCIE_RGR1_SW_INIT_1_PERST_MASK);
	ग_लिखोl(पंचांगp, pcie->base + PCIE_RGR1_SW_INIT_1(pcie));
पूर्ण

अटल अंतरभूत पूर्णांक brcm_pcie_get_rc_bar2_size_and_offset(काष्ठा brcm_pcie *pcie,
							u64 *rc_bar2_size,
							u64 *rc_bar2_offset)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);
	काष्ठा resource_entry *entry;
	काष्ठा device *dev = pcie->dev;
	u64 lowest_pcie_addr = ~(u64)0;
	पूर्णांक ret, i = 0;
	u64 size = 0;

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges) अणु
		u64 pcie_beg = entry->res->start - entry->offset;

		size += entry->res->end - entry->res->start + 1;
		अगर (pcie_beg < lowest_pcie_addr)
			lowest_pcie_addr = pcie_beg;
	पूर्ण

	अगर (lowest_pcie_addr == ~(u64)0) अणु
		dev_err(dev, "DT node has no dma-ranges\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_variable_u64_array(pcie->np, "brcm,scb-sizes", pcie->memc_size, 1,
						  PCIE_BRCM_MAX_MEMC);

	अगर (ret <= 0) अणु
		/* Make an educated guess */
		pcie->num_memc = 1;
		pcie->memc_size[0] = 1ULL << fls64(size - 1);
	पूर्ण अन्यथा अणु
		pcie->num_memc = ret;
	पूर्ण

	/* Each memc is viewed through a "port" that is a घातer of 2 */
	क्रम (i = 0, size = 0; i < pcie->num_memc; i++)
		size += pcie->memc_size[i];

	/* System memory starts at this address in PCIe-space */
	*rc_bar2_offset = lowest_pcie_addr;
	/* The sum of all memc views must also be a घातer of 2 */
	*rc_bar2_size = 1ULL << fls64(size - 1);

	/*
	 * We validate the inbound memory view even though we should trust
	 * whatever the device-tree provides. This is because of an HW issue on
	 * early Raspberry Pi 4's revisions (bcm2711). It turns out its
	 * firmware has to dynamically edit dma-ranges due to a bug on the
	 * PCIe controller पूर्णांकegration, which prohibits any access above the
	 * lower 3GB of memory. Given this, we decided to keep the dma-ranges
	 * in check, aव्योमing hard to debug device-tree related issues in the
	 * future:
	 *
	 * The PCIe host controller by design must set the inbound viewport to
	 * be a contiguous arrangement of all of the प्रणाली's memory.  In
	 * addition, its size mut be a घातer of two.  To further complicate
	 * matters, the viewport must start on a pcie-address that is aligned
	 * on a multiple of its size.  If a portion of the viewport करोes not
	 * represent प्रणाली memory -- e.g. 3GB of memory requires a 4GB
	 * viewport -- we can map the outbound memory in or after 3GB and even
	 * though the viewport will overlap the outbound memory the controller
	 * will know to send outbound memory करोwnstream and everything अन्यथा
	 * upstream.
	 *
	 * For example:
	 *
	 * - The best-हाल scenario, memory up to 3GB, is to place the inbound
	 *   region in the first 4GB of pcie-space, as some legacy devices can
	 *   only address 32bits. We would also like to put the MSI under 4GB
	 *   as well, since some devices require a 32bit MSI target address.
	 *
	 * - If the प्रणाली memory is 4GB or larger we cannot start the inbound
	 *   region at location 0 (since we have to allow some space क्रम
	 *   outbound memory @ 3GB). So instead it will  start at the 1x
	 *   multiple of its size
	 */
	अगर (!*rc_bar2_size || (*rc_bar2_offset & (*rc_bar2_size - 1)) ||
	    (*rc_bar2_offset < SZ_4G && *rc_bar2_offset > SZ_2G)) अणु
		dev_err(dev, "Invalid rc_bar2_offset/size: size 0x%llx, off 0x%llx\n",
			*rc_bar2_size, *rc_bar2_offset);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_pcie_setup(काष्ठा brcm_pcie *pcie)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);
	u64 rc_bar2_offset, rc_bar2_size;
	व्योम __iomem *base = pcie->base;
	काष्ठा device *dev = pcie->dev;
	काष्ठा resource_entry *entry;
	bool ssc_good = false;
	काष्ठा resource *res;
	पूर्णांक num_out_wins = 0;
	u16 nlw, cls, lnksta;
	पूर्णांक i, ret, memc;
	u32 पंचांगp, burst, aspm_support;

	/* Reset the bridge */
	pcie->bridge_sw_init_set(pcie, 1);
	usleep_range(100, 200);

	/* Take the bridge out of reset */
	pcie->bridge_sw_init_set(pcie, 0);

	पंचांगp = पढ़ोl(base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);
	पंचांगp &= ~PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK;
	ग_लिखोl(पंचांगp, base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);
	/* Wait क्रम SerDes to be stable */
	usleep_range(100, 200);

	/*
	 * SCB_MAX_BURST_SIZE is a two bit field.  For GENERIC chips it
	 * is encoded as 0=128, 1=256, 2=512, 3=Rsvd, क्रम BCM7278 it
	 * is encoded as 0=Rsvd, 1=128, 2=256, 3=512.
	 */
	अगर (pcie->type == BCM2711)
		burst = 0x0; /* 128B */
	अन्यथा अगर (pcie->type == BCM7278)
		burst = 0x3; /* 512 bytes */
	अन्यथा
		burst = 0x2; /* 512 bytes */

	/* Set SCB_MAX_BURST_SIZE, CFG_READ_UR_MODE, SCB_ACCESS_EN */
	पंचांगp = पढ़ोl(base + PCIE_MISC_MISC_CTRL);
	u32p_replace_bits(&पंचांगp, 1, PCIE_MISC_MISC_CTRL_SCB_ACCESS_EN_MASK);
	u32p_replace_bits(&पंचांगp, 1, PCIE_MISC_MISC_CTRL_CFG_READ_UR_MODE_MASK);
	u32p_replace_bits(&पंचांगp, burst, PCIE_MISC_MISC_CTRL_MAX_BURST_SIZE_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_MISC_CTRL);

	ret = brcm_pcie_get_rc_bar2_size_and_offset(pcie, &rc_bar2_size,
						    &rc_bar2_offset);
	अगर (ret)
		वापस ret;

	पंचांगp = lower_32_bits(rc_bar2_offset);
	u32p_replace_bits(&पंचांगp, brcm_pcie_encode_ibar_size(rc_bar2_size),
			  PCIE_MISC_RC_BAR2_CONFIG_LO_SIZE_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_RC_BAR2_CONFIG_LO);
	ग_लिखोl(upper_32_bits(rc_bar2_offset),
	       base + PCIE_MISC_RC_BAR2_CONFIG_HI);

	पंचांगp = पढ़ोl(base + PCIE_MISC_MISC_CTRL);
	क्रम (memc = 0; memc < pcie->num_memc; memc++) अणु
		u32 scb_size_val = ilog2(pcie->memc_size[memc]) - 15;

		अगर (memc == 0)
			u32p_replace_bits(&पंचांगp, scb_size_val, SCB_SIZE_MASK(0));
		अन्यथा अगर (memc == 1)
			u32p_replace_bits(&पंचांगp, scb_size_val, SCB_SIZE_MASK(1));
		अन्यथा अगर (memc == 2)
			u32p_replace_bits(&पंचांगp, scb_size_val, SCB_SIZE_MASK(2));
	पूर्ण
	ग_लिखोl(पंचांगp, base + PCIE_MISC_MISC_CTRL);

	/*
	 * We ideally want the MSI target address to be located in the 32bit
	 * addressable memory area. Some devices might depend on it. This is
	 * possible either when the inbound winकरोw is located above the lower
	 * 4GB or when the inbound area is smaller than 4GB (taking पूर्णांकo
	 * account the rounding-up we're क्रमced to perक्रमm).
	 */
	अगर (rc_bar2_offset >= SZ_4G || (rc_bar2_size + rc_bar2_offset) < SZ_4G)
		pcie->msi_target_addr = BRCM_MSI_TARGET_ADDR_LT_4GB;
	अन्यथा
		pcie->msi_target_addr = BRCM_MSI_TARGET_ADDR_GT_4GB;

	/* disable the PCIe->GISB memory winकरोw (RC_BAR1) */
	पंचांगp = पढ़ोl(base + PCIE_MISC_RC_BAR1_CONFIG_LO);
	पंचांगp &= ~PCIE_MISC_RC_BAR1_CONFIG_LO_SIZE_MASK;
	ग_लिखोl(पंचांगp, base + PCIE_MISC_RC_BAR1_CONFIG_LO);

	/* disable the PCIe->SCB memory winकरोw (RC_BAR3) */
	पंचांगp = पढ़ोl(base + PCIE_MISC_RC_BAR3_CONFIG_LO);
	पंचांगp &= ~PCIE_MISC_RC_BAR3_CONFIG_LO_SIZE_MASK;
	ग_लिखोl(पंचांगp, base + PCIE_MISC_RC_BAR3_CONFIG_LO);

	अगर (pcie->gen)
		brcm_pcie_set_gen(pcie, pcie->gen);

	/* Unनिश्चित the fundamental reset */
	pcie->perst_set(pcie, 0);

	/*
	 * Give the RC/EP समय to wake up, beक्रमe trying to configure RC.
	 * Intermittently check status क्रम link-up, up to a total of 100ms.
	 */
	क्रम (i = 0; i < 100 && !brcm_pcie_link_up(pcie); i += 5)
		msleep(5);

	अगर (!brcm_pcie_link_up(pcie)) अणु
		dev_err(dev, "link down\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!brcm_pcie_rc_mode(pcie)) अणु
		dev_err(dev, "PCIe misconfigured; is in EP mode\n");
		वापस -EINVAL;
	पूर्ण

	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		res = entry->res;

		अगर (resource_type(res) != IORESOURCE_MEM)
			जारी;

		अगर (num_out_wins >= BRCM_NUM_PCIE_OUT_WINS) अणु
			dev_err(pcie->dev, "too many outbound wins\n");
			वापस -EINVAL;
		पूर्ण

		brcm_pcie_set_outbound_win(pcie, num_out_wins, res->start,
					   res->start - entry->offset,
					   resource_size(res));
		num_out_wins++;
	पूर्ण

	/* Don't advertise L0s capability if 'aspm-no-l0s' */
	aspm_support = PCIE_LINK_STATE_L1;
	अगर (!of_property_पढ़ो_bool(pcie->np, "aspm-no-l0s"))
		aspm_support |= PCIE_LINK_STATE_L0S;
	पंचांगp = पढ़ोl(base + PCIE_RC_CFG_PRIV1_LINK_CAPABILITY);
	u32p_replace_bits(&पंचांगp, aspm_support,
		PCIE_RC_CFG_PRIV1_LINK_CAPABILITY_ASPM_SUPPORT_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_RC_CFG_PRIV1_LINK_CAPABILITY);

	/*
	 * For config space accesses on the RC, show the right class क्रम
	 * a PCIe-PCIe bridge (the शेष setting is to be EP mode).
	 */
	पंचांगp = पढ़ोl(base + PCIE_RC_CFG_PRIV1_ID_VAL3);
	u32p_replace_bits(&पंचांगp, 0x060400,
			  PCIE_RC_CFG_PRIV1_ID_VAL3_CLASS_CODE_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_RC_CFG_PRIV1_ID_VAL3);

	अगर (pcie->ssc) अणु
		ret = brcm_pcie_set_ssc(pcie);
		अगर (ret == 0)
			ssc_good = true;
		अन्यथा
			dev_err(dev, "failed attempt to enter ssc mode\n");
	पूर्ण

	lnksta = पढ़ोw(base + BRCM_PCIE_CAP_REGS + PCI_EXP_LNKSTA);
	cls = FIELD_GET(PCI_EXP_LNKSTA_CLS, lnksta);
	nlw = FIELD_GET(PCI_EXP_LNKSTA_NLW, lnksta);
	dev_info(dev, "link up, %s x%u %s\n",
		 pci_speed_string(pcie_link_speed[cls]), nlw,
		 ssc_good ? "(SSC)" : "(!SSC)");

	/* PCIe->SCB endian mode क्रम BAR */
	पंचांगp = पढ़ोl(base + PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1);
	u32p_replace_bits(&पंचांगp, PCIE_RC_CFG_VENDOR_SPCIFIC_REG1_LITTLE_ENDIAN,
		PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1_ENDIAN_MODE_BAR2_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_RC_CFG_VENDOR_VENDOR_SPECIFIC_REG1);

	/*
	 * Refclk from RC should be gated with CLKREQ# input when ASPM L0s,L1
	 * is enabled => setting the CLKREQ_DEBUG_ENABLE field to 1.
	 */
	पंचांगp = पढ़ोl(base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);
	पंचांगp |= PCIE_MISC_HARD_PCIE_HARD_DEBUG_CLKREQ_DEBUG_ENABLE_MASK;
	ग_लिखोl(पंचांगp, base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);

	वापस 0;
पूर्ण

/* L23 is a low-घातer PCIe link state */
अटल व्योम brcm_pcie_enter_l23(काष्ठा brcm_pcie *pcie)
अणु
	व्योम __iomem *base = pcie->base;
	पूर्णांक l23, i;
	u32 पंचांगp;

	/* Assert request क्रम L23 */
	पंचांगp = पढ़ोl(base + PCIE_MISC_PCIE_CTRL);
	u32p_replace_bits(&पंचांगp, 1, PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_PCIE_CTRL);

	/* Wait up to 36 msec क्रम L23 */
	पंचांगp = पढ़ोl(base + PCIE_MISC_PCIE_STATUS);
	l23 = FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK, पंचांगp);
	क्रम (i = 0; i < 15 && !l23; i++) अणु
		usleep_range(2000, 2400);
		पंचांगp = पढ़ोl(base + PCIE_MISC_PCIE_STATUS);
		l23 = FIELD_GET(PCIE_MISC_PCIE_STATUS_PCIE_LINK_IN_L23_MASK,
				पंचांगp);
	पूर्ण

	अगर (!l23)
		dev_err(pcie->dev, "failed to enter low-power link state\n");
पूर्ण

अटल पूर्णांक brcm_phy_cntl(काष्ठा brcm_pcie *pcie, स्थिर पूर्णांक start)
अणु
	अटल स्थिर u32 shअगरts[PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_NFLDS] = अणु
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_PWRDN_SHIFT,
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_RESET_SHIFT,
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_DIG_RESET_SHIFT,पूर्ण;
	अटल स्थिर u32 masks[PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_NFLDS] = अणु
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_PWRDN_MASK,
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_RESET_MASK,
		PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_DIG_RESET_MASK,पूर्ण;
	स्थिर पूर्णांक beg = start ? 0 : PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_NFLDS - 1;
	स्थिर पूर्णांक end = start ? PCIE_DVT_PMU_PCIE_PHY_CTRL_DAST_NFLDS : -1;
	u32 पंचांगp, combined_mask = 0;
	u32 val;
	व्योम __iomem *base = pcie->base;
	पूर्णांक i, ret;

	क्रम (i = beg; i != end; start ? i++ : i--) अणु
		val = start ? BIT_MASK(shअगरts[i]) : 0;
		पंचांगp = पढ़ोl(base + PCIE_DVT_PMU_PCIE_PHY_CTRL);
		पंचांगp = (पंचांगp & ~masks[i]) | (val & masks[i]);
		ग_लिखोl(पंचांगp, base + PCIE_DVT_PMU_PCIE_PHY_CTRL);
		usleep_range(50, 200);
		combined_mask |= masks[i];
	पूर्ण

	पंचांगp = पढ़ोl(base + PCIE_DVT_PMU_PCIE_PHY_CTRL);
	val = start ? combined_mask : 0;

	ret = (पंचांगp & combined_mask) == val ? 0 : -EIO;
	अगर (ret)
		dev_err(pcie->dev, "failed to %s phy\n", (start ? "start" : "stop"));

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक brcm_phy_start(काष्ठा brcm_pcie *pcie)
अणु
	वापस pcie->rescal ? brcm_phy_cntl(pcie, 1) : 0;
पूर्ण

अटल अंतरभूत पूर्णांक brcm_phy_stop(काष्ठा brcm_pcie *pcie)
अणु
	वापस pcie->rescal ? brcm_phy_cntl(pcie, 0) : 0;
पूर्ण

अटल व्योम brcm_pcie_turn_off(काष्ठा brcm_pcie *pcie)
अणु
	व्योम __iomem *base = pcie->base;
	पूर्णांक पंचांगp;

	अगर (brcm_pcie_link_up(pcie))
		brcm_pcie_enter_l23(pcie);
	/* Assert fundamental reset */
	pcie->perst_set(pcie, 1);

	/* Deनिश्चित request क्रम L23 in हाल it was निश्चितed */
	पंचांगp = पढ़ोl(base + PCIE_MISC_PCIE_CTRL);
	u32p_replace_bits(&पंचांगp, 0, PCIE_MISC_PCIE_CTRL_PCIE_L23_REQUEST_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_PCIE_CTRL);

	/* Turn off SerDes */
	पंचांगp = पढ़ोl(base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);
	u32p_replace_bits(&पंचांगp, 1, PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);

	/* Shutकरोwn PCIe bridge */
	pcie->bridge_sw_init_set(pcie, 1);
पूर्ण

अटल पूर्णांक brcm_pcie_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcm_pcie *pcie = dev_get_drvdata(dev);
	पूर्णांक ret;

	brcm_pcie_turn_off(pcie);
	ret = brcm_phy_stop(pcie);
	reset_control_rearm(pcie->rescal);
	clk_disable_unprepare(pcie->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक brcm_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा brcm_pcie *pcie = dev_get_drvdata(dev);
	व्योम __iomem *base;
	u32 पंचांगp;
	पूर्णांक ret;

	base = pcie->base;
	clk_prepare_enable(pcie->clk);

	ret = reset_control_reset(pcie->rescal);
	अगर (ret)
		जाओ err_disable_clk;

	ret = brcm_phy_start(pcie);
	अगर (ret)
		जाओ err_reset;

	/* Take bridge out of reset so we can access the SERDES reg */
	pcie->bridge_sw_init_set(pcie, 0);

	/* SERDES_IDDQ = 0 */
	पंचांगp = पढ़ोl(base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);
	u32p_replace_bits(&पंचांगp, 0, PCIE_MISC_HARD_PCIE_HARD_DEBUG_SERDES_IDDQ_MASK);
	ग_लिखोl(पंचांगp, base + PCIE_MISC_HARD_PCIE_HARD_DEBUG);

	/* रुको क्रम serdes to be stable */
	udelay(100);

	ret = brcm_pcie_setup(pcie);
	अगर (ret)
		जाओ err_reset;

	अगर (pcie->msi)
		brcm_msi_set_regs(pcie->msi);

	वापस 0;

err_reset:
	reset_control_rearm(pcie->rescal);
err_disable_clk:
	clk_disable_unprepare(pcie->clk);
	वापस ret;
पूर्ण

अटल व्योम __brcm_pcie_हटाओ(काष्ठा brcm_pcie *pcie)
अणु
	brcm_msi_हटाओ(pcie);
	brcm_pcie_turn_off(pcie);
	brcm_phy_stop(pcie);
	reset_control_rearm(pcie->rescal);
	clk_disable_unprepare(pcie->clk);
पूर्ण

अटल पूर्णांक brcm_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcm_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);

	pci_stop_root_bus(bridge->bus);
	pci_हटाओ_root_bus(bridge->bus);
	__brcm_pcie_हटाओ(pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id brcm_pcie_match[] = अणु
	अणु .compatible = "brcm,bcm2711-pcie", .data = &bcm2711_cfg पूर्ण,
	अणु .compatible = "brcm,bcm4908-pcie", .data = &bcm4908_cfg पूर्ण,
	अणु .compatible = "brcm,bcm7211-pcie", .data = &generic_cfg पूर्ण,
	अणु .compatible = "brcm,bcm7278-pcie", .data = &bcm7278_cfg पूर्ण,
	अणु .compatible = "brcm,bcm7216-pcie", .data = &bcm7278_cfg पूर्ण,
	अणु .compatible = "brcm,bcm7445-pcie", .data = &generic_cfg पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक brcm_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node, *msi_np;
	काष्ठा pci_host_bridge *bridge;
	स्थिर काष्ठा pcie_cfg_data *data;
	काष्ठा brcm_pcie *pcie;
	पूर्णांक ret;

	bridge = devm_pci_alloc_host_bridge(&pdev->dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		pr_err("failed to look up compatible string\n");
		वापस -EINVAL;
	पूर्ण

	pcie = pci_host_bridge_priv(bridge);
	pcie->dev = &pdev->dev;
	pcie->np = np;
	pcie->reg_offsets = data->offsets;
	pcie->type = data->type;
	pcie->perst_set = data->perst_set;
	pcie->bridge_sw_init_set = data->bridge_sw_init_set;

	pcie->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pcie->base))
		वापस PTR_ERR(pcie->base);

	pcie->clk = devm_clk_get_optional(&pdev->dev, "sw_pcie");
	अगर (IS_ERR(pcie->clk))
		वापस PTR_ERR(pcie->clk);

	ret = of_pci_get_max_link_speed(np);
	pcie->gen = (ret < 0) ? 0 : ret;

	pcie->ssc = of_property_पढ़ो_bool(np, "brcm,enable-ssc");

	ret = clk_prepare_enable(pcie->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not enable clock\n");
		वापस ret;
	पूर्ण
	pcie->rescal = devm_reset_control_get_optional_shared(&pdev->dev, "rescal");
	अगर (IS_ERR(pcie->rescal)) अणु
		clk_disable_unprepare(pcie->clk);
		वापस PTR_ERR(pcie->rescal);
	पूर्ण
	pcie->perst_reset = devm_reset_control_get_optional_exclusive(&pdev->dev, "perst");
	अगर (IS_ERR(pcie->perst_reset)) अणु
		clk_disable_unprepare(pcie->clk);
		वापस PTR_ERR(pcie->perst_reset);
	पूर्ण

	ret = reset_control_reset(pcie->rescal);
	अगर (ret)
		dev_err(&pdev->dev, "failed to deassert 'rescal'\n");

	ret = brcm_phy_start(pcie);
	अगर (ret) अणु
		reset_control_rearm(pcie->rescal);
		clk_disable_unprepare(pcie->clk);
		वापस ret;
	पूर्ण

	ret = brcm_pcie_setup(pcie);
	अगर (ret)
		जाओ fail;

	pcie->hw_rev = पढ़ोl(pcie->base + PCIE_MISC_REVISION);
	अगर (pcie->type == BCM4908 && pcie->hw_rev >= BRCM_PCIE_HW_REV_3_20) अणु
		dev_err(pcie->dev, "hardware revision with unsupported PERST# setup\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	msi_np = of_parse_phandle(pcie->np, "msi-parent", 0);
	अगर (pci_msi_enabled() && msi_np == pcie->np) अणु
		ret = brcm_pcie_enable_msi(pcie);
		अगर (ret) अणु
			dev_err(pcie->dev, "probe of internal MSI failed");
			जाओ fail;
		पूर्ण
	पूर्ण

	bridge->ops = &brcm_pcie_ops;
	bridge->sysdata = pcie;

	platक्रमm_set_drvdata(pdev, pcie);

	वापस pci_host_probe(bridge);
fail:
	__brcm_pcie_हटाओ(pcie);
	वापस ret;
पूर्ण

MODULE_DEVICE_TABLE(of, brcm_pcie_match);

अटल स्थिर काष्ठा dev_pm_ops brcm_pcie_pm_ops = अणु
	.suspend = brcm_pcie_suspend,
	.resume = brcm_pcie_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver brcm_pcie_driver = अणु
	.probe = brcm_pcie_probe,
	.हटाओ = brcm_pcie_हटाओ,
	.driver = अणु
		.name = "brcm-pcie",
		.of_match_table = brcm_pcie_match,
		.pm = &brcm_pcie_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(brcm_pcie_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Broadcom STB PCIe RC driver");
MODULE_AUTHOR("Broadcom");
