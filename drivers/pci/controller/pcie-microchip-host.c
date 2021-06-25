<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip AXI PCIe Bridge host controller driver
 *
 * Copyright (c) 2018 - 2020 Microchip Corporation. All rights reserved.
 *
 * Author: Daire McNamara <daire.mcnamara@microchip.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "../pci.h"

/* Number of MSI IRQs */
#घोषणा MC_NUM_MSI_IRQS				32
#घोषणा MC_NUM_MSI_IRQS_CODED			5

/* PCIe Bridge Phy and Controller Phy offsets */
#घोषणा MC_PCIE1_BRIDGE_ADDR			0x00008000u
#घोषणा MC_PCIE1_CTRL_ADDR			0x0000a000u

#घोषणा MC_PCIE_BRIDGE_ADDR			(MC_PCIE1_BRIDGE_ADDR)
#घोषणा MC_PCIE_CTRL_ADDR			(MC_PCIE1_CTRL_ADDR)

/* PCIe Controller Phy Regs */
#घोषणा SEC_ERROR_CNT				0x20
#घोषणा DED_ERROR_CNT				0x24
#घोषणा SEC_ERROR_INT				0x28
#घोषणा  SEC_ERROR_INT_TX_RAM_SEC_ERR_INT	GENMASK(3, 0)
#घोषणा  SEC_ERROR_INT_RX_RAM_SEC_ERR_INT	GENMASK(7, 4)
#घोषणा  SEC_ERROR_INT_PCIE2AXI_RAM_SEC_ERR_INT	GENMASK(11, 8)
#घोषणा  SEC_ERROR_INT_AXI2PCIE_RAM_SEC_ERR_INT	GENMASK(15, 12)
#घोषणा  NUM_SEC_ERROR_INTS			(4)
#घोषणा SEC_ERROR_INT_MASK			0x2c
#घोषणा DED_ERROR_INT				0x30
#घोषणा  DED_ERROR_INT_TX_RAM_DED_ERR_INT	GENMASK(3, 0)
#घोषणा  DED_ERROR_INT_RX_RAM_DED_ERR_INT	GENMASK(7, 4)
#घोषणा  DED_ERROR_INT_PCIE2AXI_RAM_DED_ERR_INT	GENMASK(11, 8)
#घोषणा  DED_ERROR_INT_AXI2PCIE_RAM_DED_ERR_INT	GENMASK(15, 12)
#घोषणा  NUM_DED_ERROR_INTS			(4)
#घोषणा DED_ERROR_INT_MASK			0x34
#घोषणा ECC_CONTROL				0x38
#घोषणा  ECC_CONTROL_TX_RAM_INJ_ERROR_0		BIT(0)
#घोषणा  ECC_CONTROL_TX_RAM_INJ_ERROR_1		BIT(1)
#घोषणा  ECC_CONTROL_TX_RAM_INJ_ERROR_2		BIT(2)
#घोषणा  ECC_CONTROL_TX_RAM_INJ_ERROR_3		BIT(3)
#घोषणा  ECC_CONTROL_RX_RAM_INJ_ERROR_0		BIT(4)
#घोषणा  ECC_CONTROL_RX_RAM_INJ_ERROR_1		BIT(5)
#घोषणा  ECC_CONTROL_RX_RAM_INJ_ERROR_2		BIT(6)
#घोषणा  ECC_CONTROL_RX_RAM_INJ_ERROR_3		BIT(7)
#घोषणा  ECC_CONTROL_PCIE2AXI_RAM_INJ_ERROR_0	BIT(8)
#घोषणा  ECC_CONTROL_PCIE2AXI_RAM_INJ_ERROR_1	BIT(9)
#घोषणा  ECC_CONTROL_PCIE2AXI_RAM_INJ_ERROR_2	BIT(10)
#घोषणा  ECC_CONTROL_PCIE2AXI_RAM_INJ_ERROR_3	BIT(11)
#घोषणा  ECC_CONTROL_AXI2PCIE_RAM_INJ_ERROR_0	BIT(12)
#घोषणा  ECC_CONTROL_AXI2PCIE_RAM_INJ_ERROR_1	BIT(13)
#घोषणा  ECC_CONTROL_AXI2PCIE_RAM_INJ_ERROR_2	BIT(14)
#घोषणा  ECC_CONTROL_AXI2PCIE_RAM_INJ_ERROR_3	BIT(15)
#घोषणा  ECC_CONTROL_TX_RAM_ECC_BYPASS		BIT(24)
#घोषणा  ECC_CONTROL_RX_RAM_ECC_BYPASS		BIT(25)
#घोषणा  ECC_CONTROL_PCIE2AXI_RAM_ECC_BYPASS	BIT(26)
#घोषणा  ECC_CONTROL_AXI2PCIE_RAM_ECC_BYPASS	BIT(27)
#घोषणा LTSSM_STATE				0x5c
#घोषणा  LTSSM_L0_STATE				0x10
#घोषणा PCIE_EVENT_INT				0x14c
#घोषणा  PCIE_EVENT_INT_L2_EXIT_INT		BIT(0)
#घोषणा  PCIE_EVENT_INT_HOTRST_EXIT_INT		BIT(1)
#घोषणा  PCIE_EVENT_INT_DLUP_EXIT_INT		BIT(2)
#घोषणा  PCIE_EVENT_INT_MASK			GENMASK(2, 0)
#घोषणा  PCIE_EVENT_INT_L2_EXIT_INT_MASK	BIT(16)
#घोषणा  PCIE_EVENT_INT_HOTRST_EXIT_INT_MASK	BIT(17)
#घोषणा  PCIE_EVENT_INT_DLUP_EXIT_INT_MASK	BIT(18)
#घोषणा  PCIE_EVENT_INT_ENB_MASK		GENMASK(18, 16)
#घोषणा  PCIE_EVENT_INT_ENB_SHIFT		16
#घोषणा  NUM_PCIE_EVENTS			(3)

/* PCIe Bridge Phy Regs */
#घोषणा PCIE_PCI_IDS_DW1			0x9c

/* PCIe Config space MSI capability काष्ठाure */
#घोषणा MC_MSI_CAP_CTRL_OFFSET			0xe0u
#घोषणा  MC_MSI_MAX_Q_AVAIL			(MC_NUM_MSI_IRQS_CODED << 1)
#घोषणा  MC_MSI_Q_SIZE				(MC_NUM_MSI_IRQS_CODED << 4)

#घोषणा IMASK_LOCAL				0x180
#घोषणा  DMA_END_ENGINE_0_MASK			0x00000000u
#घोषणा  DMA_END_ENGINE_0_SHIFT			0
#घोषणा  DMA_END_ENGINE_1_MASK			0x00000000u
#घोषणा  DMA_END_ENGINE_1_SHIFT			1
#घोषणा  DMA_ERROR_ENGINE_0_MASK		0x00000100u
#घोषणा  DMA_ERROR_ENGINE_0_SHIFT		8
#घोषणा  DMA_ERROR_ENGINE_1_MASK		0x00000200u
#घोषणा  DMA_ERROR_ENGINE_1_SHIFT		9
#घोषणा  A_ATR_EVT_POST_ERR_MASK		0x00010000u
#घोषणा  A_ATR_EVT_POST_ERR_SHIFT		16
#घोषणा  A_ATR_EVT_FETCH_ERR_MASK		0x00020000u
#घोषणा  A_ATR_EVT_FETCH_ERR_SHIFT		17
#घोषणा  A_ATR_EVT_DISCARD_ERR_MASK		0x00040000u
#घोषणा  A_ATR_EVT_DISCARD_ERR_SHIFT		18
#घोषणा  A_ATR_EVT_DOORBELL_MASK		0x00000000u
#घोषणा  A_ATR_EVT_DOORBELL_SHIFT		19
#घोषणा  P_ATR_EVT_POST_ERR_MASK		0x00100000u
#घोषणा  P_ATR_EVT_POST_ERR_SHIFT		20
#घोषणा  P_ATR_EVT_FETCH_ERR_MASK		0x00200000u
#घोषणा  P_ATR_EVT_FETCH_ERR_SHIFT		21
#घोषणा  P_ATR_EVT_DISCARD_ERR_MASK		0x00400000u
#घोषणा  P_ATR_EVT_DISCARD_ERR_SHIFT		22
#घोषणा  P_ATR_EVT_DOORBELL_MASK		0x00000000u
#घोषणा  P_ATR_EVT_DOORBELL_SHIFT		23
#घोषणा  PM_MSI_INT_INTA_MASK			0x01000000u
#घोषणा  PM_MSI_INT_INTA_SHIFT			24
#घोषणा  PM_MSI_INT_INTB_MASK			0x02000000u
#घोषणा  PM_MSI_INT_INTB_SHIFT			25
#घोषणा  PM_MSI_INT_INTC_MASK			0x04000000u
#घोषणा  PM_MSI_INT_INTC_SHIFT			26
#घोषणा  PM_MSI_INT_INTD_MASK			0x08000000u
#घोषणा  PM_MSI_INT_INTD_SHIFT			27
#घोषणा  PM_MSI_INT_INTX_MASK			0x0f000000u
#घोषणा  PM_MSI_INT_INTX_SHIFT			24
#घोषणा  PM_MSI_INT_MSI_MASK			0x10000000u
#घोषणा  PM_MSI_INT_MSI_SHIFT			28
#घोषणा  PM_MSI_INT_AER_EVT_MASK		0x20000000u
#घोषणा  PM_MSI_INT_AER_EVT_SHIFT		29
#घोषणा  PM_MSI_INT_EVENTS_MASK			0x40000000u
#घोषणा  PM_MSI_INT_EVENTS_SHIFT		30
#घोषणा  PM_MSI_INT_SYS_ERR_MASK		0x80000000u
#घोषणा  PM_MSI_INT_SYS_ERR_SHIFT		31
#घोषणा  NUM_LOCAL_EVENTS			15
#घोषणा ISTATUS_LOCAL				0x184
#घोषणा IMASK_HOST				0x188
#घोषणा ISTATUS_HOST				0x18c
#घोषणा MSI_ADDR				0x190
#घोषणा ISTATUS_MSI				0x194

/* PCIe Master table init defines */
#घोषणा ATR0_PCIE_WIN0_SRCADDR_PARAM		0x600u
#घोषणा  ATR0_PCIE_ATR_SIZE			0x25
#घोषणा  ATR0_PCIE_ATR_SIZE_SHIFT		1
#घोषणा ATR0_PCIE_WIN0_SRC_ADDR			0x604u
#घोषणा ATR0_PCIE_WIN0_TRSL_ADDR_LSB		0x608u
#घोषणा ATR0_PCIE_WIN0_TRSL_ADDR_UDW		0x60cu
#घोषणा ATR0_PCIE_WIN0_TRSL_PARAM		0x610u

/* PCIe AXI slave table init defines */
#घोषणा ATR0_AXI4_SLV0_SRCADDR_PARAM		0x800u
#घोषणा  ATR_SIZE_SHIFT				1
#घोषणा  ATR_IMPL_ENABLE			1
#घोषणा ATR0_AXI4_SLV0_SRC_ADDR			0x804u
#घोषणा ATR0_AXI4_SLV0_TRSL_ADDR_LSB		0x808u
#घोषणा ATR0_AXI4_SLV0_TRSL_ADDR_UDW		0x80cu
#घोषणा ATR0_AXI4_SLV0_TRSL_PARAM		0x810u
#घोषणा  PCIE_TX_RX_INTERFACE			0x00000000u
#घोषणा  PCIE_CONFIG_INTERFACE			0x00000001u

#घोषणा ATR_ENTRY_SIZE				32

#घोषणा EVENT_PCIE_L2_EXIT			0
#घोषणा EVENT_PCIE_HOTRST_EXIT			1
#घोषणा EVENT_PCIE_DLUP_EXIT			2
#घोषणा EVENT_SEC_TX_RAM_SEC_ERR		3
#घोषणा EVENT_SEC_RX_RAM_SEC_ERR		4
#घोषणा EVENT_SEC_AXI2PCIE_RAM_SEC_ERR		5
#घोषणा EVENT_SEC_PCIE2AXI_RAM_SEC_ERR		6
#घोषणा EVENT_DED_TX_RAM_DED_ERR		7
#घोषणा EVENT_DED_RX_RAM_DED_ERR		8
#घोषणा EVENT_DED_AXI2PCIE_RAM_DED_ERR		9
#घोषणा EVENT_DED_PCIE2AXI_RAM_DED_ERR		10
#घोषणा EVENT_LOCAL_DMA_END_ENGINE_0		11
#घोषणा EVENT_LOCAL_DMA_END_ENGINE_1		12
#घोषणा EVENT_LOCAL_DMA_ERROR_ENGINE_0		13
#घोषणा EVENT_LOCAL_DMA_ERROR_ENGINE_1		14
#घोषणा EVENT_LOCAL_A_ATR_EVT_POST_ERR		15
#घोषणा EVENT_LOCAL_A_ATR_EVT_FETCH_ERR		16
#घोषणा EVENT_LOCAL_A_ATR_EVT_DISCARD_ERR	17
#घोषणा EVENT_LOCAL_A_ATR_EVT_DOORBELL		18
#घोषणा EVENT_LOCAL_P_ATR_EVT_POST_ERR		19
#घोषणा EVENT_LOCAL_P_ATR_EVT_FETCH_ERR		20
#घोषणा EVENT_LOCAL_P_ATR_EVT_DISCARD_ERR	21
#घोषणा EVENT_LOCAL_P_ATR_EVT_DOORBELL		22
#घोषणा EVENT_LOCAL_PM_MSI_INT_INTX		23
#घोषणा EVENT_LOCAL_PM_MSI_INT_MSI		24
#घोषणा EVENT_LOCAL_PM_MSI_INT_AER_EVT		25
#घोषणा EVENT_LOCAL_PM_MSI_INT_EVENTS		26
#घोषणा EVENT_LOCAL_PM_MSI_INT_SYS_ERR		27
#घोषणा NUM_EVENTS				28

#घोषणा PCIE_EVENT_CAUSE(x, s)	\
	[EVENT_PCIE_ ## x] = अणु __stringअगरy(x), s पूर्ण

#घोषणा SEC_ERROR_CAUSE(x, s) \
	[EVENT_SEC_ ## x] = अणु __stringअगरy(x), s पूर्ण

#घोषणा DED_ERROR_CAUSE(x, s) \
	[EVENT_DED_ ## x] = अणु __stringअगरy(x), s पूर्ण

#घोषणा LOCAL_EVENT_CAUSE(x, s) \
	[EVENT_LOCAL_ ## x] = अणु __stringअगरy(x), s पूर्ण

#घोषणा PCIE_EVENT(x) \
	.base = MC_PCIE_CTRL_ADDR, \
	.offset = PCIE_EVENT_INT, \
	.mask_offset = PCIE_EVENT_INT, \
	.mask_high = 1, \
	.mask = PCIE_EVENT_INT_ ## x ## _INT, \
	.enb_mask = PCIE_EVENT_INT_ENB_MASK

#घोषणा SEC_EVENT(x) \
	.base = MC_PCIE_CTRL_ADDR, \
	.offset = SEC_ERROR_INT, \
	.mask_offset = SEC_ERROR_INT_MASK, \
	.mask = SEC_ERROR_INT_ ## x ## _INT, \
	.mask_high = 1, \
	.enb_mask = 0

#घोषणा DED_EVENT(x) \
	.base = MC_PCIE_CTRL_ADDR, \
	.offset = DED_ERROR_INT, \
	.mask_offset = DED_ERROR_INT_MASK, \
	.mask_high = 1, \
	.mask = DED_ERROR_INT_ ## x ## _INT, \
	.enb_mask = 0

#घोषणा LOCAL_EVENT(x) \
	.base = MC_PCIE_BRIDGE_ADDR, \
	.offset = ISTATUS_LOCAL, \
	.mask_offset = IMASK_LOCAL, \
	.mask_high = 0, \
	.mask = x ## _MASK, \
	.enb_mask = 0

#घोषणा PCIE_EVENT_TO_EVENT_MAP(x) \
	अणु PCIE_EVENT_INT_ ## x ## _INT, EVENT_PCIE_ ## x पूर्ण

#घोषणा SEC_ERROR_TO_EVENT_MAP(x) \
	अणु SEC_ERROR_INT_ ## x ## _INT, EVENT_SEC_ ## x पूर्ण

#घोषणा DED_ERROR_TO_EVENT_MAP(x) \
	अणु DED_ERROR_INT_ ## x ## _INT, EVENT_DED_ ## x पूर्ण

#घोषणा LOCAL_STATUS_TO_EVENT_MAP(x) \
	अणु x ## _MASK, EVENT_LOCAL_ ## x पूर्ण

काष्ठा event_map अणु
	u32 reg_mask;
	u32 event_bit;
पूर्ण;

काष्ठा mc_msi अणु
	काष्ठा mutex lock;		/* Protect used biपंचांगap */
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा irq_करोमुख्य *dev_करोमुख्य;
	u32 num_vectors;
	u64 vector_phy;
	DECLARE_BITMAP(used, MC_NUM_MSI_IRQS);
पूर्ण;

काष्ठा mc_port अणु
	व्योम __iomem *axi_base_addr;
	काष्ठा device *dev;
	काष्ठा irq_करोमुख्य *पूर्णांकx_करोमुख्य;
	काष्ठा irq_करोमुख्य *event_करोमुख्य;
	raw_spinlock_t lock;
	काष्ठा mc_msi msi;
पूर्ण;

काष्ठा cause अणु
	स्थिर अक्षर *sym;
	स्थिर अक्षर *str;
पूर्ण;

अटल स्थिर काष्ठा cause event_cause[NUM_EVENTS] = अणु
	PCIE_EVENT_CAUSE(L2_EXIT, "L2 exit event"),
	PCIE_EVENT_CAUSE(HOTRST_EXIT, "Hot reset exit event"),
	PCIE_EVENT_CAUSE(DLUP_EXIT, "DLUP exit event"),
	SEC_ERROR_CAUSE(TX_RAM_SEC_ERR,  "sec error in tx buffer"),
	SEC_ERROR_CAUSE(RX_RAM_SEC_ERR,  "sec error in rx buffer"),
	SEC_ERROR_CAUSE(PCIE2AXI_RAM_SEC_ERR,  "sec error in pcie2axi buffer"),
	SEC_ERROR_CAUSE(AXI2PCIE_RAM_SEC_ERR,  "sec error in axi2pcie buffer"),
	DED_ERROR_CAUSE(TX_RAM_DED_ERR,  "ded error in tx buffer"),
	DED_ERROR_CAUSE(RX_RAM_DED_ERR,  "ded error in rx buffer"),
	DED_ERROR_CAUSE(PCIE2AXI_RAM_DED_ERR,  "ded error in pcie2axi buffer"),
	DED_ERROR_CAUSE(AXI2PCIE_RAM_DED_ERR,  "ded error in axi2pcie buffer"),
	LOCAL_EVENT_CAUSE(DMA_ERROR_ENGINE_0, "dma engine 0 error"),
	LOCAL_EVENT_CAUSE(DMA_ERROR_ENGINE_1, "dma engine 1 error"),
	LOCAL_EVENT_CAUSE(A_ATR_EVT_POST_ERR, "axi write request error"),
	LOCAL_EVENT_CAUSE(A_ATR_EVT_FETCH_ERR, "axi read request error"),
	LOCAL_EVENT_CAUSE(A_ATR_EVT_DISCARD_ERR, "axi read timeout"),
	LOCAL_EVENT_CAUSE(P_ATR_EVT_POST_ERR, "pcie write request error"),
	LOCAL_EVENT_CAUSE(P_ATR_EVT_FETCH_ERR, "pcie read request error"),
	LOCAL_EVENT_CAUSE(P_ATR_EVT_DISCARD_ERR, "pcie read timeout"),
	LOCAL_EVENT_CAUSE(PM_MSI_INT_AER_EVT, "aer event"),
	LOCAL_EVENT_CAUSE(PM_MSI_INT_EVENTS, "pm/ltr/hotplug event"),
	LOCAL_EVENT_CAUSE(PM_MSI_INT_SYS_ERR, "system error"),
पूर्ण;

अटल काष्ठा event_map pcie_event_to_event[] = अणु
	PCIE_EVENT_TO_EVENT_MAP(L2_EXIT),
	PCIE_EVENT_TO_EVENT_MAP(HOTRST_EXIT),
	PCIE_EVENT_TO_EVENT_MAP(DLUP_EXIT),
पूर्ण;

अटल काष्ठा event_map sec_error_to_event[] = अणु
	SEC_ERROR_TO_EVENT_MAP(TX_RAM_SEC_ERR),
	SEC_ERROR_TO_EVENT_MAP(RX_RAM_SEC_ERR),
	SEC_ERROR_TO_EVENT_MAP(PCIE2AXI_RAM_SEC_ERR),
	SEC_ERROR_TO_EVENT_MAP(AXI2PCIE_RAM_SEC_ERR),
पूर्ण;

अटल काष्ठा event_map ded_error_to_event[] = अणु
	DED_ERROR_TO_EVENT_MAP(TX_RAM_DED_ERR),
	DED_ERROR_TO_EVENT_MAP(RX_RAM_DED_ERR),
	DED_ERROR_TO_EVENT_MAP(PCIE2AXI_RAM_DED_ERR),
	DED_ERROR_TO_EVENT_MAP(AXI2PCIE_RAM_DED_ERR),
पूर्ण;

अटल काष्ठा event_map local_status_to_event[] = अणु
	LOCAL_STATUS_TO_EVENT_MAP(DMA_END_ENGINE_0),
	LOCAL_STATUS_TO_EVENT_MAP(DMA_END_ENGINE_1),
	LOCAL_STATUS_TO_EVENT_MAP(DMA_ERROR_ENGINE_0),
	LOCAL_STATUS_TO_EVENT_MAP(DMA_ERROR_ENGINE_1),
	LOCAL_STATUS_TO_EVENT_MAP(A_ATR_EVT_POST_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(A_ATR_EVT_FETCH_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(A_ATR_EVT_DISCARD_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(A_ATR_EVT_DOORBELL),
	LOCAL_STATUS_TO_EVENT_MAP(P_ATR_EVT_POST_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(P_ATR_EVT_FETCH_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(P_ATR_EVT_DISCARD_ERR),
	LOCAL_STATUS_TO_EVENT_MAP(P_ATR_EVT_DOORBELL),
	LOCAL_STATUS_TO_EVENT_MAP(PM_MSI_INT_INTX),
	LOCAL_STATUS_TO_EVENT_MAP(PM_MSI_INT_MSI),
	LOCAL_STATUS_TO_EVENT_MAP(PM_MSI_INT_AER_EVT),
	LOCAL_STATUS_TO_EVENT_MAP(PM_MSI_INT_EVENTS),
	LOCAL_STATUS_TO_EVENT_MAP(PM_MSI_INT_SYS_ERR),
पूर्ण;

काष्ठा अणु
	u32 base;
	u32 offset;
	u32 mask;
	u32 shअगरt;
	u32 enb_mask;
	u32 mask_high;
	u32 mask_offset;
पूर्ण event_descs[] = अणु
	अणु PCIE_EVENT(L2_EXIT) पूर्ण,
	अणु PCIE_EVENT(HOTRST_EXIT) पूर्ण,
	अणु PCIE_EVENT(DLUP_EXIT) पूर्ण,
	अणु SEC_EVENT(TX_RAM_SEC_ERR) पूर्ण,
	अणु SEC_EVENT(RX_RAM_SEC_ERR) पूर्ण,
	अणु SEC_EVENT(PCIE2AXI_RAM_SEC_ERR) पूर्ण,
	अणु SEC_EVENT(AXI2PCIE_RAM_SEC_ERR) पूर्ण,
	अणु DED_EVENT(TX_RAM_DED_ERR) पूर्ण,
	अणु DED_EVENT(RX_RAM_DED_ERR) पूर्ण,
	अणु DED_EVENT(PCIE2AXI_RAM_DED_ERR) पूर्ण,
	अणु DED_EVENT(AXI2PCIE_RAM_DED_ERR) पूर्ण,
	अणु LOCAL_EVENT(DMA_END_ENGINE_0) पूर्ण,
	अणु LOCAL_EVENT(DMA_END_ENGINE_1) पूर्ण,
	अणु LOCAL_EVENT(DMA_ERROR_ENGINE_0) पूर्ण,
	अणु LOCAL_EVENT(DMA_ERROR_ENGINE_1) पूर्ण,
	अणु LOCAL_EVENT(A_ATR_EVT_POST_ERR) पूर्ण,
	अणु LOCAL_EVENT(A_ATR_EVT_FETCH_ERR) पूर्ण,
	अणु LOCAL_EVENT(A_ATR_EVT_DISCARD_ERR) पूर्ण,
	अणु LOCAL_EVENT(A_ATR_EVT_DOORBELL) पूर्ण,
	अणु LOCAL_EVENT(P_ATR_EVT_POST_ERR) पूर्ण,
	अणु LOCAL_EVENT(P_ATR_EVT_FETCH_ERR) पूर्ण,
	अणु LOCAL_EVENT(P_ATR_EVT_DISCARD_ERR) पूर्ण,
	अणु LOCAL_EVENT(P_ATR_EVT_DOORBELL) पूर्ण,
	अणु LOCAL_EVENT(PM_MSI_INT_INTX) पूर्ण,
	अणु LOCAL_EVENT(PM_MSI_INT_MSI) पूर्ण,
	अणु LOCAL_EVENT(PM_MSI_INT_AER_EVT) पूर्ण,
	अणु LOCAL_EVENT(PM_MSI_INT_EVENTS) पूर्ण,
	अणु LOCAL_EVENT(PM_MSI_INT_SYS_ERR) पूर्ण,
पूर्ण;

अटल अक्षर poss_clks[][5] = अणु "fic0", "fic1", "fic2", "fic3" पूर्ण;

अटल व्योम mc_pcie_enable_msi(काष्ठा mc_port *port, व्योम __iomem *base)
अणु
	काष्ठा mc_msi *msi = &port->msi;
	u32 cap_offset = MC_MSI_CAP_CTRL_OFFSET;
	u16 msg_ctrl = पढ़ोw_relaxed(base + cap_offset + PCI_MSI_FLAGS);

	msg_ctrl |= PCI_MSI_FLAGS_ENABLE;
	msg_ctrl &= ~PCI_MSI_FLAGS_QMASK;
	msg_ctrl |= MC_MSI_MAX_Q_AVAIL;
	msg_ctrl &= ~PCI_MSI_FLAGS_QSIZE;
	msg_ctrl |= MC_MSI_Q_SIZE;
	msg_ctrl |= PCI_MSI_FLAGS_64BIT;

	ग_लिखोw_relaxed(msg_ctrl, base + cap_offset + PCI_MSI_FLAGS);

	ग_लिखोl_relaxed(lower_32_bits(msi->vector_phy),
		       base + cap_offset + PCI_MSI_ADDRESS_LO);
	ग_लिखोl_relaxed(upper_32_bits(msi->vector_phy),
		       base + cap_offset + PCI_MSI_ADDRESS_HI);
पूर्ण

अटल व्योम mc_handle_msi(काष्ठा irq_desc *desc)
अणु
	काष्ठा mc_port *port = irq_desc_get_handler_data(desc);
	काष्ठा device *dev = port->dev;
	काष्ठा mc_msi *msi = &port->msi;
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	status = पढ़ोl_relaxed(bridge_base_addr + ISTATUS_LOCAL);
	अगर (status & PM_MSI_INT_MSI_MASK) अणु
		status = पढ़ोl_relaxed(bridge_base_addr + ISTATUS_MSI);
		क्रम_each_set_bit(bit, &status, msi->num_vectors) अणु
			virq = irq_find_mapping(msi->dev_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
			अन्यथा
				dev_err_ratelimited(dev, "bad MSI IRQ %d\n",
						    bit);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mc_msi_bottom_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	u32 bitpos = data->hwirq;
	अचिन्हित दीर्घ status;

	ग_लिखोl_relaxed(BIT(bitpos), bridge_base_addr + ISTATUS_MSI);
	status = पढ़ोl_relaxed(bridge_base_addr + ISTATUS_MSI);
	अगर (!status)
		ग_लिखोl_relaxed(BIT(PM_MSI_INT_MSI_SHIFT),
			       bridge_base_addr + ISTATUS_LOCAL);
पूर्ण

अटल व्योम mc_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	phys_addr_t addr = port->msi.vector_phy;

	msg->address_lo = lower_32_bits(addr);
	msg->address_hi = upper_32_bits(addr);
	msg->data = data->hwirq;

	dev_dbg(port->dev, "msi#%x address_hi %#x address_lo %#x\n",
		(पूर्णांक)data->hwirq, msg->address_hi, msg->address_lo);
पूर्ण

अटल पूर्णांक mc_msi_set_affinity(काष्ठा irq_data *irq_data,
			       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल काष्ठा irq_chip mc_msi_bottom_irq_chip = अणु
	.name = "Microchip MSI",
	.irq_ack = mc_msi_bottom_irq_ack,
	.irq_compose_msi_msg = mc_compose_msi_msg,
	.irq_set_affinity = mc_msi_set_affinity,
पूर्ण;

अटल पूर्णांक mc_irq_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा mc_port *port = करोमुख्य->host_data;
	काष्ठा mc_msi *msi = &port->msi;
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	अचिन्हित दीर्घ bit;
	u32 val;

	mutex_lock(&msi->lock);
	bit = find_first_zero_bit(msi->used, msi->num_vectors);
	अगर (bit >= msi->num_vectors) अणु
		mutex_unlock(&msi->lock);
		वापस -ENOSPC;
	पूर्ण

	set_bit(bit, msi->used);

	irq_करोमुख्य_set_info(करोमुख्य, virq, bit, &mc_msi_bottom_irq_chip,
			    करोमुख्य->host_data, handle_edge_irq, शून्य, शून्य);

	/* Enable MSI पूर्णांकerrupts */
	val = पढ़ोl_relaxed(bridge_base_addr + IMASK_LOCAL);
	val |= PM_MSI_INT_MSI_MASK;
	ग_लिखोl_relaxed(val, bridge_base_addr + IMASK_LOCAL);

	mutex_unlock(&msi->lock);

	वापस 0;
पूर्ण

अटल व्योम mc_irq_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(d);
	काष्ठा mc_msi *msi = &port->msi;

	mutex_lock(&msi->lock);

	अगर (test_bit(d->hwirq, msi->used))
		__clear_bit(d->hwirq, msi->used);
	अन्यथा
		dev_err(port->dev, "trying to free unused MSI%lu\n", d->hwirq);

	mutex_unlock(&msi->lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops msi_करोमुख्य_ops = अणु
	.alloc	= mc_irq_msi_करोमुख्य_alloc,
	.मुक्त	= mc_irq_msi_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा irq_chip mc_msi_irq_chip = अणु
	.name = "Microchip PCIe MSI",
	.irq_ack = irq_chip_ack_parent,
	.irq_mask = pci_msi_mask_irq,
	.irq_unmask = pci_msi_unmask_irq,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info mc_msi_करोमुख्य_info = अणु
	.flags = (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		  MSI_FLAG_PCI_MSIX),
	.chip = &mc_msi_irq_chip,
पूर्ण;

अटल पूर्णांक mc_allocate_msi_करोमुख्यs(काष्ठा mc_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा fwnode_handle *fwnode = of_node_to_fwnode(dev->of_node);
	काष्ठा mc_msi *msi = &port->msi;

	mutex_init(&port->msi.lock);

	msi->dev_करोमुख्य = irq_करोमुख्य_add_linear(शून्य, msi->num_vectors,
						&msi_करोमुख्य_ops, port);
	अगर (!msi->dev_करोमुख्य) अणु
		dev_err(dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	msi->msi_करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode, &mc_msi_करोमुख्य_info,
						    msi->dev_करोमुख्य);
	अगर (!msi->msi_करोमुख्य) अणु
		dev_err(dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(msi->dev_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mc_handle_पूर्णांकx(काष्ठा irq_desc *desc)
अणु
	काष्ठा mc_port *port = irq_desc_get_handler_data(desc);
	काष्ठा device *dev = port->dev;
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	अचिन्हित दीर्घ status;
	u32 bit;
	u32 virq;

	status = पढ़ोl_relaxed(bridge_base_addr + ISTATUS_LOCAL);
	अगर (status & PM_MSI_INT_INTX_MASK) अणु
		status &= PM_MSI_INT_INTX_MASK;
		status >>= PM_MSI_INT_INTX_SHIFT;
		क्रम_each_set_bit(bit, &status, PCI_NUM_INTX) अणु
			virq = irq_find_mapping(port->पूर्णांकx_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
			अन्यथा
				dev_err_ratelimited(dev, "bad INTx IRQ %d\n",
						    bit);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mc_ack_पूर्णांकx_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	u32 mask = BIT(data->hwirq + PM_MSI_INT_INTX_SHIFT);

	ग_लिखोl_relaxed(mask, bridge_base_addr + ISTATUS_LOCAL);
पूर्ण

अटल व्योम mc_mask_पूर्णांकx_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	अचिन्हित दीर्घ flags;
	u32 mask = BIT(data->hwirq + PM_MSI_INT_INTX_SHIFT);
	u32 val;

	raw_spin_lock_irqsave(&port->lock, flags);
	val = पढ़ोl_relaxed(bridge_base_addr + IMASK_LOCAL);
	val &= ~mask;
	ग_लिखोl_relaxed(val, bridge_base_addr + IMASK_LOCAL);
	raw_spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम mc_unmask_पूर्णांकx_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	अचिन्हित दीर्घ flags;
	u32 mask = BIT(data->hwirq + PM_MSI_INT_INTX_SHIFT);
	u32 val;

	raw_spin_lock_irqsave(&port->lock, flags);
	val = पढ़ोl_relaxed(bridge_base_addr + IMASK_LOCAL);
	val |= mask;
	ग_लिखोl_relaxed(val, bridge_base_addr + IMASK_LOCAL);
	raw_spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल काष्ठा irq_chip mc_पूर्णांकx_irq_chip = अणु
	.name = "Microchip PCIe INTx",
	.irq_ack = mc_ack_पूर्णांकx_irq,
	.irq_mask = mc_mask_पूर्णांकx_irq,
	.irq_unmask = mc_unmask_पूर्णांकx_irq,
पूर्ण;

अटल पूर्णांक mc_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			    irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &mc_पूर्णांकx_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = mc_pcie_पूर्णांकx_map,
पूर्ण;

अटल अंतरभूत u32 reg_to_event(u32 reg, काष्ठा event_map field)
अणु
	वापस (reg & field.reg_mask) ? BIT(field.event_bit) : 0;
पूर्ण

अटल u32 pcie_events(व्योम __iomem *addr)
अणु
	u32 reg = पढ़ोl_relaxed(addr);
	u32 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pcie_event_to_event); i++)
		val |= reg_to_event(reg, pcie_event_to_event[i]);

	वापस val;
पूर्ण

अटल u32 sec_errors(व्योम __iomem *addr)
अणु
	u32 reg = पढ़ोl_relaxed(addr);
	u32 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sec_error_to_event); i++)
		val |= reg_to_event(reg, sec_error_to_event[i]);

	वापस val;
पूर्ण

अटल u32 ded_errors(व्योम __iomem *addr)
अणु
	u32 reg = पढ़ोl_relaxed(addr);
	u32 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ded_error_to_event); i++)
		val |= reg_to_event(reg, ded_error_to_event[i]);

	वापस val;
पूर्ण

अटल u32 local_events(व्योम __iomem *addr)
अणु
	u32 reg = पढ़ोl_relaxed(addr);
	u32 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(local_status_to_event); i++)
		val |= reg_to_event(reg, local_status_to_event[i]);

	वापस val;
पूर्ण

अटल u32 get_events(काष्ठा mc_port *port)
अणु
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	व्योम __iomem *ctrl_base_addr = port->axi_base_addr + MC_PCIE_CTRL_ADDR;
	u32 events = 0;

	events |= pcie_events(ctrl_base_addr + PCIE_EVENT_INT);
	events |= sec_errors(ctrl_base_addr + SEC_ERROR_INT);
	events |= ded_errors(ctrl_base_addr + DED_ERROR_INT);
	events |= local_events(bridge_base_addr + ISTATUS_LOCAL);

	वापस events;
पूर्ण

अटल irqवापस_t mc_event_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mc_port *port = dev_id;
	काष्ठा device *dev = port->dev;
	काष्ठा irq_data *data;

	data = irq_करोमुख्य_get_irq_data(port->event_करोमुख्य, irq);

	अगर (event_cause[data->hwirq].str)
		dev_err_ratelimited(dev, "%s\n", event_cause[data->hwirq].str);
	अन्यथा
		dev_err_ratelimited(dev, "bad event IRQ %ld\n", data->hwirq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mc_handle_event(काष्ठा irq_desc *desc)
अणु
	काष्ठा mc_port *port = irq_desc_get_handler_data(desc);
	अचिन्हित दीर्घ events;
	u32 bit;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);

	chained_irq_enter(chip, desc);

	events = get_events(port);

	क्रम_each_set_bit(bit, &events, NUM_EVENTS)
		generic_handle_irq(irq_find_mapping(port->event_करोमुख्य, bit));

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम mc_ack_event_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	u32 event = data->hwirq;
	व्योम __iomem *addr;
	u32 mask;

	addr = port->axi_base_addr + event_descs[event].base +
		event_descs[event].offset;
	mask = event_descs[event].mask;
	mask |= event_descs[event].enb_mask;

	ग_लिखोl_relaxed(mask, addr);
पूर्ण

अटल व्योम mc_mask_event_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	u32 event = data->hwirq;
	व्योम __iomem *addr;
	u32 mask;
	u32 val;

	addr = port->axi_base_addr + event_descs[event].base +
		event_descs[event].mask_offset;
	mask = event_descs[event].mask;
	अगर (event_descs[event].enb_mask) अणु
		mask <<= PCIE_EVENT_INT_ENB_SHIFT;
		mask &= PCIE_EVENT_INT_ENB_MASK;
	पूर्ण

	अगर (!event_descs[event].mask_high)
		mask = ~mask;

	raw_spin_lock(&port->lock);
	val = पढ़ोl_relaxed(addr);
	अगर (event_descs[event].mask_high)
		val |= mask;
	अन्यथा
		val &= mask;

	ग_लिखोl_relaxed(val, addr);
	raw_spin_unlock(&port->lock);
पूर्ण

अटल व्योम mc_unmask_event_irq(काष्ठा irq_data *data)
अणु
	काष्ठा mc_port *port = irq_data_get_irq_chip_data(data);
	u32 event = data->hwirq;
	व्योम __iomem *addr;
	u32 mask;
	u32 val;

	addr = port->axi_base_addr + event_descs[event].base +
		event_descs[event].mask_offset;
	mask = event_descs[event].mask;

	अगर (event_descs[event].enb_mask)
		mask <<= PCIE_EVENT_INT_ENB_SHIFT;

	अगर (event_descs[event].mask_high)
		mask = ~mask;

	अगर (event_descs[event].enb_mask)
		mask &= PCIE_EVENT_INT_ENB_MASK;

	raw_spin_lock(&port->lock);
	val = पढ़ोl_relaxed(addr);
	अगर (event_descs[event].mask_high)
		val &= mask;
	अन्यथा
		val |= mask;
	ग_लिखोl_relaxed(val, addr);
	raw_spin_unlock(&port->lock);
पूर्ण

अटल काष्ठा irq_chip mc_event_irq_chip = अणु
	.name = "Microchip PCIe EVENT",
	.irq_ack = mc_ack_event_irq,
	.irq_mask = mc_mask_event_irq,
	.irq_unmask = mc_unmask_event_irq,
पूर्ण;

अटल पूर्णांक mc_pcie_event_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &mc_event_irq_chip, handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops event_करोमुख्य_ops = अणु
	.map = mc_pcie_event_map,
पूर्ण;

अटल अंतरभूत काष्ठा clk *mc_pcie_init_clk(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = devm_clk_get_optional(dev, id);
	अगर (IS_ERR(clk))
		वापस clk;
	अगर (!clk)
		वापस clk;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ERR_PTR(ret);

	devm_add_action_or_reset(dev, (व्योम (*) (व्योम *))clk_disable_unprepare,
				 clk);

	वापस clk;
पूर्ण

अटल पूर्णांक mc_pcie_init_clks(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा clk *fic;

	/*
	 * PCIe may be घड़ीed via Fabric Interface using between 1 and 4
	 * घड़ीs. Scan DT क्रम घड़ीs and enable them अगर present
	 */
	क्रम (i = 0; i < ARRAY_SIZE(poss_clks); i++) अणु
		fic = mc_pcie_init_clk(dev, poss_clks[i]);
		अगर (IS_ERR(fic))
			वापस PTR_ERR(fic);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mc_pcie_init_irq_करोमुख्यs(काष्ठा mc_port *port)
अणु
	काष्ठा device *dev = port->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *pcie_पूर्णांकc_node;

	/* Setup INTx */
	pcie_पूर्णांकc_node = of_get_next_child(node, शून्य);
	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "failed to find PCIe Intc node\n");
		वापस -EINVAL;
	पूर्ण

	port->event_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, NUM_EVENTS,
						   &event_करोमुख्य_ops, port);
	अगर (!port->event_करोमुख्य) अणु
		dev_err(dev, "failed to get event domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_करोमुख्य_update_bus_token(port->event_करोमुख्य, DOMAIN_BUS_NEXUS);

	port->पूर्णांकx_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
						  &पूर्णांकx_करोमुख्य_ops, port);
	अगर (!port->पूर्णांकx_करोमुख्य) अणु
		dev_err(dev, "failed to get an INTx IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	irq_करोमुख्य_update_bus_token(port->पूर्णांकx_करोमुख्य, DOMAIN_BUS_WIRED);

	of_node_put(pcie_पूर्णांकc_node);
	raw_spin_lock_init(&port->lock);

	वापस mc_allocate_msi_करोमुख्यs(port);
पूर्ण

अटल व्योम mc_pcie_setup_winकरोw(व्योम __iomem *bridge_base_addr, u32 index,
				 phys_addr_t axi_addr, phys_addr_t pci_addr,
				 माप_प्रकार size)
अणु
	u32 atr_sz = ilog2(size) - 1;
	u32 val;

	अगर (index == 0)
		val = PCIE_CONFIG_INTERFACE;
	अन्यथा
		val = PCIE_TX_RX_INTERFACE;

	ग_लिखोl(val, bridge_base_addr + (index * ATR_ENTRY_SIZE) +
	       ATR0_AXI4_SLV0_TRSL_PARAM);

	val = lower_32_bits(axi_addr) | (atr_sz << ATR_SIZE_SHIFT) |
			    ATR_IMPL_ENABLE;
	ग_लिखोl(val, bridge_base_addr + (index * ATR_ENTRY_SIZE) +
	       ATR0_AXI4_SLV0_SRCADDR_PARAM);

	val = upper_32_bits(axi_addr);
	ग_लिखोl(val, bridge_base_addr + (index * ATR_ENTRY_SIZE) +
	       ATR0_AXI4_SLV0_SRC_ADDR);

	val = lower_32_bits(pci_addr);
	ग_लिखोl(val, bridge_base_addr + (index * ATR_ENTRY_SIZE) +
	       ATR0_AXI4_SLV0_TRSL_ADDR_LSB);

	val = upper_32_bits(pci_addr);
	ग_लिखोl(val, bridge_base_addr + (index * ATR_ENTRY_SIZE) +
	       ATR0_AXI4_SLV0_TRSL_ADDR_UDW);

	val = पढ़ोl(bridge_base_addr + ATR0_PCIE_WIN0_SRCADDR_PARAM);
	val |= (ATR0_PCIE_ATR_SIZE << ATR0_PCIE_ATR_SIZE_SHIFT);
	ग_लिखोl(val, bridge_base_addr + ATR0_PCIE_WIN0_SRCADDR_PARAM);
	ग_लिखोl(0, bridge_base_addr + ATR0_PCIE_WIN0_SRC_ADDR);
पूर्ण

अटल पूर्णांक mc_pcie_setup_winकरोws(काष्ठा platक्रमm_device *pdev,
				 काष्ठा mc_port *port)
अणु
	व्योम __iomem *bridge_base_addr =
		port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	काष्ठा pci_host_bridge *bridge = platक्रमm_get_drvdata(pdev);
	काष्ठा resource_entry *entry;
	u64 pci_addr;
	u32 index = 1;

	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		अगर (resource_type(entry->res) == IORESOURCE_MEM) अणु
			pci_addr = entry->res->start - entry->offset;
			mc_pcie_setup_winकरोw(bridge_base_addr, index,
					     entry->res->start, pci_addr,
					     resource_size(entry->res));
			index++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mc_platक्रमm_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा mc_port *port;
	व्योम __iomem *bridge_base_addr;
	व्योम __iomem *ctrl_base_addr;
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i, पूर्णांकx_irq, msi_irq, event_irq;
	u32 val;
	पूर्णांक err;

	port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;
	port->dev = dev;

	ret = mc_pcie_init_clks(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to get clock resources, error %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	port->axi_base_addr = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(port->axi_base_addr))
		वापस PTR_ERR(port->axi_base_addr);

	bridge_base_addr = port->axi_base_addr + MC_PCIE_BRIDGE_ADDR;
	ctrl_base_addr = port->axi_base_addr + MC_PCIE_CTRL_ADDR;

	port->msi.vector_phy = MSI_ADDR;
	port->msi.num_vectors = MC_NUM_MSI_IRQS;
	ret = mc_pcie_init_irq_करोमुख्यs(port);
	अगर (ret) अणु
		dev_err(dev, "failed creating IRQ domains\n");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;

	क्रम (i = 0; i < NUM_EVENTS; i++) अणु
		event_irq = irq_create_mapping(port->event_करोमुख्य, i);
		अगर (!event_irq) अणु
			dev_err(dev, "failed to map hwirq %d\n", i);
			वापस -ENXIO;
		पूर्ण

		err = devm_request_irq(dev, event_irq, mc_event_handler,
				       0, event_cause[i].sym, port);
		अगर (err) अणु
			dev_err(dev, "failed to request IRQ %d\n", event_irq);
			वापस err;
		पूर्ण
	पूर्ण

	पूर्णांकx_irq = irq_create_mapping(port->event_करोमुख्य,
				      EVENT_LOCAL_PM_MSI_INT_INTX);
	अगर (!पूर्णांकx_irq) अणु
		dev_err(dev, "failed to map INTx interrupt\n");
		वापस -ENXIO;
	पूर्ण

	/* Plug the INTx chained handler */
	irq_set_chained_handler_and_data(पूर्णांकx_irq, mc_handle_पूर्णांकx, port);

	msi_irq = irq_create_mapping(port->event_करोमुख्य,
				     EVENT_LOCAL_PM_MSI_INT_MSI);
	अगर (!msi_irq)
		वापस -ENXIO;

	/* Plug the MSI chained handler */
	irq_set_chained_handler_and_data(msi_irq, mc_handle_msi, port);

	/* Plug the मुख्य event chained handler */
	irq_set_chained_handler_and_data(irq, mc_handle_event, port);

	/* Hardware करोesn't setup MSI by शेष */
	mc_pcie_enable_msi(port, cfg->win);

	val = पढ़ोl_relaxed(bridge_base_addr + IMASK_LOCAL);
	val |= PM_MSI_INT_INTX_MASK;
	ग_लिखोl_relaxed(val, bridge_base_addr + IMASK_LOCAL);

	ग_लिखोl_relaxed(val, ctrl_base_addr + ECC_CONTROL);

	val = PCIE_EVENT_INT_L2_EXIT_INT |
	      PCIE_EVENT_INT_HOTRST_EXIT_INT |
	      PCIE_EVENT_INT_DLUP_EXIT_INT;
	ग_लिखोl_relaxed(val, ctrl_base_addr + PCIE_EVENT_INT);

	val = SEC_ERROR_INT_TX_RAM_SEC_ERR_INT |
	      SEC_ERROR_INT_RX_RAM_SEC_ERR_INT |
	      SEC_ERROR_INT_PCIE2AXI_RAM_SEC_ERR_INT |
	      SEC_ERROR_INT_AXI2PCIE_RAM_SEC_ERR_INT;
	ग_लिखोl_relaxed(val, ctrl_base_addr + SEC_ERROR_INT);
	ग_लिखोl_relaxed(0, ctrl_base_addr + SEC_ERROR_INT_MASK);
	ग_लिखोl_relaxed(0, ctrl_base_addr + SEC_ERROR_CNT);

	val = DED_ERROR_INT_TX_RAM_DED_ERR_INT |
	      DED_ERROR_INT_RX_RAM_DED_ERR_INT |
	      DED_ERROR_INT_PCIE2AXI_RAM_DED_ERR_INT |
	      DED_ERROR_INT_AXI2PCIE_RAM_DED_ERR_INT;
	ग_लिखोl_relaxed(val, ctrl_base_addr + DED_ERROR_INT);
	ग_लिखोl_relaxed(0, ctrl_base_addr + DED_ERROR_INT_MASK);
	ग_लिखोl_relaxed(0, ctrl_base_addr + DED_ERROR_CNT);

	ग_लिखोl_relaxed(0, bridge_base_addr + IMASK_HOST);
	ग_लिखोl_relaxed(GENMASK(31, 0), bridge_base_addr + ISTATUS_HOST);

	/* Configure Address Translation Table 0 क्रम PCIe config space */
	mc_pcie_setup_winकरोw(bridge_base_addr, 0, cfg->res.start & 0xffffffff,
			     cfg->res.start, resource_size(&cfg->res));

	वापस mc_pcie_setup_winकरोws(pdev, port);
पूर्ण

अटल स्थिर काष्ठा pci_ecam_ops mc_ecam_ops = अणु
	.init = mc_platक्रमm_init,
	.pci_ops = अणु
		.map_bus = pci_ecam_map_bus,
		.पढ़ो = pci_generic_config_पढ़ो,
		.ग_लिखो = pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id mc_pcie_of_match[] = अणु
	अणु
		.compatible = "microchip,pcie-host-1.0",
		.data = &mc_ecam_ops,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mc_pcie_of_match)

अटल काष्ठा platक्रमm_driver mc_pcie_driver = अणु
	.probe = pci_host_common_probe,
	.driver = अणु
		.name = "microchip-pcie",
		.of_match_table = mc_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mc_pcie_driver);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microchip PCIe host controller driver");
MODULE_AUTHOR("Daire McNamara <daire.mcnamara@microchip.com>");
