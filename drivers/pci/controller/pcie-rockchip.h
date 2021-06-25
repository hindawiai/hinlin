<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Rockchip AXI PCIe controller driver
 *
 * Copyright (c) 2018 Rockchip, Inc.
 *
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 *
 */

#अगर_अघोषित _PCIE_ROCKCHIP_H
#घोषणा _PCIE_ROCKCHIP_H

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>

/*
 * The upper 16 bits of PCIE_CLIENT_CONFIG are a ग_लिखो mask क्रम the lower 16
 * bits.  This allows atomic updates of the रेजिस्टर without locking.
 */
#घोषणा HIWORD_UPDATE(mask, val)	(((mask) << 16) | (val))
#घोषणा HIWORD_UPDATE_BIT(val)		HIWORD_UPDATE(val, val)

#घोषणा ENCODE_LANES(x)			((((x) >> 1) & 3) << 4)
#घोषणा MAX_LANE_NUM			4
#घोषणा MAX_REGION_LIMIT		32
#घोषणा MIN_EP_APERTURE			28

#घोषणा PCIE_CLIENT_BASE		0x0
#घोषणा PCIE_CLIENT_CONFIG		(PCIE_CLIENT_BASE + 0x00)
#घोषणा   PCIE_CLIENT_CONF_ENABLE	  HIWORD_UPDATE_BIT(0x0001)
#घोषणा   PCIE_CLIENT_CONF_DISABLE       HIWORD_UPDATE(0x0001, 0)
#घोषणा   PCIE_CLIENT_LINK_TRAIN_ENABLE	  HIWORD_UPDATE_BIT(0x0002)
#घोषणा   PCIE_CLIENT_ARI_ENABLE	  HIWORD_UPDATE_BIT(0x0008)
#घोषणा   PCIE_CLIENT_CONF_LANE_NUM(x)	  HIWORD_UPDATE(0x0030, ENCODE_LANES(x))
#घोषणा   PCIE_CLIENT_MODE_RC		  HIWORD_UPDATE_BIT(0x0040)
#घोषणा   PCIE_CLIENT_MODE_EP            HIWORD_UPDATE(0x0040, 0)
#घोषणा   PCIE_CLIENT_GEN_SEL_1		  HIWORD_UPDATE(0x0080, 0)
#घोषणा   PCIE_CLIENT_GEN_SEL_2		  HIWORD_UPDATE_BIT(0x0080)
#घोषणा PCIE_CLIENT_DEBUG_OUT_0		(PCIE_CLIENT_BASE + 0x3c)
#घोषणा   PCIE_CLIENT_DEBUG_LTSSM_MASK		GENMASK(5, 0)
#घोषणा   PCIE_CLIENT_DEBUG_LTSSM_L1		0x18
#घोषणा   PCIE_CLIENT_DEBUG_LTSSM_L2		0x19
#घोषणा PCIE_CLIENT_BASIC_STATUS1	(PCIE_CLIENT_BASE + 0x48)
#घोषणा   PCIE_CLIENT_LINK_STATUS_UP		0x00300000
#घोषणा   PCIE_CLIENT_LINK_STATUS_MASK		0x00300000
#घोषणा PCIE_CLIENT_INT_MASK		(PCIE_CLIENT_BASE + 0x4c)
#घोषणा PCIE_CLIENT_INT_STATUS		(PCIE_CLIENT_BASE + 0x50)
#घोषणा   PCIE_CLIENT_INTR_MASK			GENMASK(8, 5)
#घोषणा   PCIE_CLIENT_INTR_SHIFT		5
#घोषणा   PCIE_CLIENT_INT_LEGACY_DONE		BIT(15)
#घोषणा   PCIE_CLIENT_INT_MSG			BIT(14)
#घोषणा   PCIE_CLIENT_INT_HOT_RST		BIT(13)
#घोषणा   PCIE_CLIENT_INT_DPA			BIT(12)
#घोषणा   PCIE_CLIENT_INT_FATAL_ERR		BIT(11)
#घोषणा   PCIE_CLIENT_INT_NFATAL_ERR		BIT(10)
#घोषणा   PCIE_CLIENT_INT_CORR_ERR		BIT(9)
#घोषणा   PCIE_CLIENT_INT_INTD			BIT(8)
#घोषणा   PCIE_CLIENT_INT_INTC			BIT(7)
#घोषणा   PCIE_CLIENT_INT_INTB			BIT(6)
#घोषणा   PCIE_CLIENT_INT_INTA			BIT(5)
#घोषणा   PCIE_CLIENT_INT_LOCAL			BIT(4)
#घोषणा   PCIE_CLIENT_INT_UDMA			BIT(3)
#घोषणा   PCIE_CLIENT_INT_PHY			BIT(2)
#घोषणा   PCIE_CLIENT_INT_HOT_PLUG		BIT(1)
#घोषणा   PCIE_CLIENT_INT_PWR_STCG		BIT(0)

#घोषणा PCIE_CLIENT_INT_LEGACY \
	(PCIE_CLIENT_INT_INTA | PCIE_CLIENT_INT_INTB | \
	PCIE_CLIENT_INT_INTC | PCIE_CLIENT_INT_INTD)

#घोषणा PCIE_CLIENT_INT_CLI \
	(PCIE_CLIENT_INT_CORR_ERR | PCIE_CLIENT_INT_NFATAL_ERR | \
	PCIE_CLIENT_INT_FATAL_ERR | PCIE_CLIENT_INT_DPA | \
	PCIE_CLIENT_INT_HOT_RST | PCIE_CLIENT_INT_MSG | \
	PCIE_CLIENT_INT_LEGACY_DONE | PCIE_CLIENT_INT_LEGACY | \
	PCIE_CLIENT_INT_PHY)

#घोषणा PCIE_CORE_CTRL_MGMT_BASE	0x900000
#घोषणा PCIE_CORE_CTRL			(PCIE_CORE_CTRL_MGMT_BASE + 0x000)
#घोषणा   PCIE_CORE_PL_CONF_SPEED_5G		0x00000008
#घोषणा   PCIE_CORE_PL_CONF_SPEED_MASK		0x00000018
#घोषणा   PCIE_CORE_PL_CONF_LANE_MASK		0x00000006
#घोषणा   PCIE_CORE_PL_CONF_LANE_SHIFT		1
#घोषणा PCIE_CORE_CTRL_PLC1		(PCIE_CORE_CTRL_MGMT_BASE + 0x004)
#घोषणा   PCIE_CORE_CTRL_PLC1_FTS_MASK		GENMASK(23, 8)
#घोषणा   PCIE_CORE_CTRL_PLC1_FTS_SHIFT		8
#घोषणा   PCIE_CORE_CTRL_PLC1_FTS_CNT		0xffff
#घोषणा PCIE_CORE_TXCREDIT_CFG1		(PCIE_CORE_CTRL_MGMT_BASE + 0x020)
#घोषणा   PCIE_CORE_TXCREDIT_CFG1_MUI_MASK	0xFFFF0000
#घोषणा   PCIE_CORE_TXCREDIT_CFG1_MUI_SHIFT	16
#घोषणा   PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE(x) \
		(((x) >> 3) << PCIE_CORE_TXCREDIT_CFG1_MUI_SHIFT)
#घोषणा PCIE_CORE_LANE_MAP             (PCIE_CORE_CTRL_MGMT_BASE + 0x200)
#घोषणा   PCIE_CORE_LANE_MAP_MASK              0x0000000f
#घोषणा   PCIE_CORE_LANE_MAP_REVERSE           BIT(16)
#घोषणा PCIE_CORE_INT_STATUS		(PCIE_CORE_CTRL_MGMT_BASE + 0x20c)
#घोषणा   PCIE_CORE_INT_PRFPE			BIT(0)
#घोषणा   PCIE_CORE_INT_CRFPE			BIT(1)
#घोषणा   PCIE_CORE_INT_RRPE			BIT(2)
#घोषणा   PCIE_CORE_INT_PRFO			BIT(3)
#घोषणा   PCIE_CORE_INT_CRFO			BIT(4)
#घोषणा   PCIE_CORE_INT_RT			BIT(5)
#घोषणा   PCIE_CORE_INT_RTR			BIT(6)
#घोषणा   PCIE_CORE_INT_PE			BIT(7)
#घोषणा   PCIE_CORE_INT_MTR			BIT(8)
#घोषणा   PCIE_CORE_INT_UCR			BIT(9)
#घोषणा   PCIE_CORE_INT_FCE			BIT(10)
#घोषणा   PCIE_CORE_INT_CT			BIT(11)
#घोषणा   PCIE_CORE_INT_UTC			BIT(18)
#घोषणा   PCIE_CORE_INT_MMVC			BIT(19)
#घोषणा PCIE_CORE_CONFIG_VENDOR		(PCIE_CORE_CTRL_MGMT_BASE + 0x44)
#घोषणा PCIE_CORE_INT_MASK		(PCIE_CORE_CTRL_MGMT_BASE + 0x210)
#घोषणा PCIE_CORE_PHY_FUNC_CFG		(PCIE_CORE_CTRL_MGMT_BASE + 0x2c0)
#घोषणा PCIE_RC_BAR_CONF		(PCIE_CORE_CTRL_MGMT_BASE + 0x300)
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_DISABLED		0x0
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_IO_32BITS		0x1
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_MEM_32BITS		0x4
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_32BITS	0x5
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_MEM_64BITS		0x6
#घोषणा ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_64BITS	0x7

#घोषणा PCIE_CORE_INT \
		(PCIE_CORE_INT_PRFPE | PCIE_CORE_INT_CRFPE | \
		 PCIE_CORE_INT_RRPE | PCIE_CORE_INT_CRFO | \
		 PCIE_CORE_INT_RT | PCIE_CORE_INT_RTR | \
		 PCIE_CORE_INT_PE | PCIE_CORE_INT_MTR | \
		 PCIE_CORE_INT_UCR | PCIE_CORE_INT_FCE | \
		 PCIE_CORE_INT_CT | PCIE_CORE_INT_UTC | \
		 PCIE_CORE_INT_MMVC)

#घोषणा PCIE_RC_RP_ATS_BASE		0x400000
#घोषणा PCIE_RC_CONFIG_NORMAL_BASE	0x800000
#घोषणा PCIE_RC_CONFIG_BASE		0xa00000
#घोषणा PCIE_RC_CONFIG_RID_CCR		(PCIE_RC_CONFIG_BASE + 0x08)
#घोषणा   PCIE_RC_CONFIG_SCC_SHIFT		16
#घोषणा PCIE_RC_CONFIG_DCR		(PCIE_RC_CONFIG_BASE + 0xc4)
#घोषणा   PCIE_RC_CONFIG_DCR_CSPL_SHIFT		18
#घोषणा   PCIE_RC_CONFIG_DCR_CSPL_LIMIT		0xff
#घोषणा   PCIE_RC_CONFIG_DCR_CPLS_SHIFT		26
#घोषणा PCIE_RC_CONFIG_DCSR		(PCIE_RC_CONFIG_BASE + 0xc8)
#घोषणा   PCIE_RC_CONFIG_DCSR_MPS_MASK		GENMASK(7, 5)
#घोषणा   PCIE_RC_CONFIG_DCSR_MPS_256		(0x1 << 5)
#घोषणा PCIE_RC_CONFIG_LINK_CAP		(PCIE_RC_CONFIG_BASE + 0xcc)
#घोषणा   PCIE_RC_CONFIG_LINK_CAP_L0S		BIT(10)
#घोषणा PCIE_RC_CONFIG_LCS		(PCIE_RC_CONFIG_BASE + 0xd0)
#घोषणा PCIE_RC_CONFIG_L1_SUBSTATE_CTRL2 (PCIE_RC_CONFIG_BASE + 0x90c)
#घोषणा PCIE_RC_CONFIG_THP_CAP		(PCIE_RC_CONFIG_BASE + 0x274)
#घोषणा   PCIE_RC_CONFIG_THP_CAP_NEXT_MASK	GENMASK(31, 20)

#घोषणा PCIE_CORE_AXI_CONF_BASE		0xc00000
#घोषणा PCIE_CORE_OB_REGION_ADDR0	(PCIE_CORE_AXI_CONF_BASE + 0x0)
#घोषणा   PCIE_CORE_OB_REGION_ADDR0_NUM_BITS	0x3f
#घोषणा   PCIE_CORE_OB_REGION_ADDR0_LO_ADDR	0xffffff00
#घोषणा PCIE_CORE_OB_REGION_ADDR1	(PCIE_CORE_AXI_CONF_BASE + 0x4)
#घोषणा PCIE_CORE_OB_REGION_DESC0	(PCIE_CORE_AXI_CONF_BASE + 0x8)
#घोषणा PCIE_CORE_OB_REGION_DESC1	(PCIE_CORE_AXI_CONF_BASE + 0xc)

#घोषणा PCIE_CORE_AXI_INBOUND_BASE	0xc00800
#घोषणा PCIE_RP_IB_ADDR0		(PCIE_CORE_AXI_INBOUND_BASE + 0x0)
#घोषणा   PCIE_CORE_IB_REGION_ADDR0_NUM_BITS	0x3f
#घोषणा   PCIE_CORE_IB_REGION_ADDR0_LO_ADDR	0xffffff00
#घोषणा PCIE_RP_IB_ADDR1		(PCIE_CORE_AXI_INBOUND_BASE + 0x4)

/* Size of one AXI Region (not Region 0) */
#घोषणा AXI_REGION_SIZE				BIT(20)
/* Size of Region 0, equal to sum of sizes of other regions */
#घोषणा AXI_REGION_0_SIZE			(32 * (0x1 << 20))
#घोषणा OB_REG_SIZE_SHIFT			5
#घोषणा IB_ROOT_PORT_REG_SIZE_SHIFT		3
#घोषणा AXI_WRAPPER_IO_WRITE			0x6
#घोषणा AXI_WRAPPER_MEM_WRITE			0x2
#घोषणा AXI_WRAPPER_TYPE0_CFG			0xa
#घोषणा AXI_WRAPPER_TYPE1_CFG			0xb
#घोषणा AXI_WRAPPER_NOR_MSG			0xc

#घोषणा MAX_AXI_IB_ROOTPORT_REGION_NUM		3
#घोषणा MIN_AXI_ADDR_BITS_PASSED		8
#घोषणा PCIE_RC_SEND_PME_OFF			0x11960
#घोषणा ROCKCHIP_VENDOR_ID			0x1d87
#घोषणा PCIE_LINK_IS_L2(x) \
	(((x) & PCIE_CLIENT_DEBUG_LTSSM_MASK) == PCIE_CLIENT_DEBUG_LTSSM_L2)
#घोषणा PCIE_LINK_UP(x) \
	(((x) & PCIE_CLIENT_LINK_STATUS_MASK) == PCIE_CLIENT_LINK_STATUS_UP)
#घोषणा PCIE_LINK_IS_GEN2(x) \
	(((x) & PCIE_CORE_PL_CONF_SPEED_MASK) == PCIE_CORE_PL_CONF_SPEED_5G)

#घोषणा RC_REGION_0_ADDR_TRANS_H		0x00000000
#घोषणा RC_REGION_0_ADDR_TRANS_L		0x00000000
#घोषणा RC_REGION_0_PASS_BITS			(25 - 1)
#घोषणा RC_REGION_0_TYPE_MASK			GENMASK(3, 0)
#घोषणा MAX_AXI_WRAPPER_REGION_NUM		33

#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_TO_RC		0x0
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_VIA_ADDR		0x1
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_VIA_ID		0x2
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_BROADCAST		0x3
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_LOCAL_INTX		0x4
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_PME_ACK		0x5
#घोषणा ROCKCHIP_PCIE_MSG_CODE_ASSERT_INTA		0x20
#घोषणा ROCKCHIP_PCIE_MSG_CODE_ASSERT_INTB		0x21
#घोषणा ROCKCHIP_PCIE_MSG_CODE_ASSERT_INTC		0x22
#घोषणा ROCKCHIP_PCIE_MSG_CODE_ASSERT_INTD		0x23
#घोषणा ROCKCHIP_PCIE_MSG_CODE_DEASSERT_INTA		0x24
#घोषणा ROCKCHIP_PCIE_MSG_CODE_DEASSERT_INTB		0x25
#घोषणा ROCKCHIP_PCIE_MSG_CODE_DEASSERT_INTC		0x26
#घोषणा ROCKCHIP_PCIE_MSG_CODE_DEASSERT_INTD		0x27
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING_MASK			GENMASK(7, 5)
#घोषणा ROCKCHIP_PCIE_MSG_ROUTING(route) \
	(((route) << 5) & ROCKCHIP_PCIE_MSG_ROUTING_MASK)
#घोषणा ROCKCHIP_PCIE_MSG_CODE_MASK			GENMASK(15, 8)
#घोषणा ROCKCHIP_PCIE_MSG_CODE(code) \
	(((code) << 8) & ROCKCHIP_PCIE_MSG_CODE_MASK)
#घोषणा ROCKCHIP_PCIE_MSG_NO_DATA			BIT(16)

#घोषणा ROCKCHIP_PCIE_EP_CMD_STATUS			0x4
#घोषणा   ROCKCHIP_PCIE_EP_CMD_STATUS_IS		BIT(19)
#घोषणा ROCKCHIP_PCIE_EP_MSI_CTRL_REG			0x90
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_OFFSET		17
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_MASK		GENMASK(19, 17)
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET		20
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK		GENMASK(22, 20)
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_ME				BIT(16)
#घोषणा   ROCKCHIP_PCIE_EP_MSI_CTRL_MASK_MSI_CAP	BIT(24)
#घोषणा ROCKCHIP_PCIE_EP_DUMMY_IRQ_ADDR				0x1
#घोषणा ROCKCHIP_PCIE_EP_PCI_LEGACY_IRQ_ADDR		0x3
#घोषणा ROCKCHIP_PCIE_EP_FUNC_BASE(fn)	(((fn) << 12) & GENMASK(19, 12))
#घोषणा ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar) \
	(PCIE_RC_RP_ATS_BASE + 0x0840 + (fn) * 0x0040 + (bar) * 0x0008)
#घोषणा ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar) \
	(PCIE_RC_RP_ATS_BASE + 0x0844 + (fn) * 0x0040 + (bar) * 0x0008)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(r) \
	(PCIE_RC_RP_ATS_BASE + 0x0000 + ((r) & 0x1f) * 0x0020)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK	GENMASK(19, 12)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN(devfn) \
	(((devfn) << 12) & \
		 ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK	GENMASK(27, 20)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_BUS(bus) \
		(((bus) << 20) & ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(r) \
		(PCIE_RC_RP_ATS_BASE + 0x0004 + ((r) & 0x1f) * 0x0020)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID	BIT(23)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK	GENMASK(31, 24)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN(devfn) \
		(((devfn) << 24) & ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_DESC0(r) \
		(PCIE_RC_RP_ATS_BASE + 0x0008 + ((r) & 0x1f) * 0x0020)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_DESC1(r)	\
		(PCIE_RC_RP_ATS_BASE + 0x000c + ((r) & 0x1f) * 0x0020)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0(r) \
		(PCIE_RC_RP_ATS_BASE + 0x0018 + ((r) & 0x1f) * 0x0020)
#घोषणा ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1(r) \
		(PCIE_RC_RP_ATS_BASE + 0x001c + ((r) & 0x1f) * 0x0020)

#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG0(fn) \
		(PCIE_CORE_CTRL_MGMT_BASE + 0x0240 + (fn) * 0x0008)
#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG1(fn) \
		(PCIE_CORE_CTRL_MGMT_BASE + 0x0244 + (fn) * 0x0008)
#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) \
		(GENMASK(4, 0) << ((b) * 8))
#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE(b, a) \
		(((a) << ((b) * 8)) & \
		 ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b))
#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b) \
		(GENMASK(7, 5) << ((b) * 8))
#घोषणा ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, c) \
		(((c) << ((b) * 8 + 5)) & \
		 ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b))

काष्ठा rockchip_pcie अणु
	व्योम	__iomem *reg_base;		/* DT axi-base */
	व्योम	__iomem *apb_base;		/* DT apb-base */
	bool    legacy_phy;
	काष्ठा  phy *phys[MAX_LANE_NUM];
	काष्ठा	reset_control *core_rst;
	काष्ठा	reset_control *mgmt_rst;
	काष्ठा	reset_control *mgmt_sticky_rst;
	काष्ठा	reset_control *pipe_rst;
	काष्ठा	reset_control *pm_rst;
	काष्ठा	reset_control *aclk_rst;
	काष्ठा	reset_control *pclk_rst;
	काष्ठा	clk *aclk_pcie;
	काष्ठा	clk *aclk_perf_pcie;
	काष्ठा	clk *hclk_pcie;
	काष्ठा	clk *clk_pcie_pm;
	काष्ठा	regulator *vpcie12v; /* 12V घातer supply */
	काष्ठा	regulator *vpcie3v3; /* 3.3V घातer supply */
	काष्ठा	regulator *vpcie1v8; /* 1.8V घातer supply */
	काष्ठा	regulator *vpcie0v9; /* 0.9V घातer supply */
	काष्ठा	gpio_desc *ep_gpio;
	u32	lanes;
	u8      lanes_map;
	पूर्णांक	link_gen;
	काष्ठा	device *dev;
	काष्ठा	irq_करोमुख्य *irq_करोमुख्य;
	पूर्णांक     offset;
	व्योम    __iomem *msg_region;
	phys_addr_t msg_bus_addr;
	bool is_rc;
	काष्ठा resource *mem_res;
पूर्ण;

अटल u32 rockchip_pcie_पढ़ो(काष्ठा rockchip_pcie *rockchip, u32 reg)
अणु
	वापस पढ़ोl(rockchip->apb_base + reg);
पूर्ण

अटल व्योम rockchip_pcie_ग_लिखो(काष्ठा rockchip_pcie *rockchip, u32 val,
				u32 reg)
अणु
	ग_लिखोl(val, rockchip->apb_base + reg);
पूर्ण

पूर्णांक rockchip_pcie_parse_dt(काष्ठा rockchip_pcie *rockchip);
पूर्णांक rockchip_pcie_init_port(काष्ठा rockchip_pcie *rockchip);
पूर्णांक rockchip_pcie_get_phys(काष्ठा rockchip_pcie *rockchip);
व्योम rockchip_pcie_deinit_phys(काष्ठा rockchip_pcie *rockchip);
पूर्णांक rockchip_pcie_enable_घड़ीs(काष्ठा rockchip_pcie *rockchip);
व्योम rockchip_pcie_disable_घड़ीs(व्योम *data);
व्योम rockchip_pcie_cfg_configuration_accesses(
		काष्ठा rockchip_pcie *rockchip, u32 type);

#पूर्ण_अगर /* _PCIE_ROCKCHIP_H */
