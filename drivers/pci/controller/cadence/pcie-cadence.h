<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (c) 2017 Cadence
// Cadence PCIe controller driver.
// Author: Cyrille Pitchen <cyrille.pitchen@मुक्त-electrons.com>

#अगर_अघोषित _PCIE_CADENCE_H
#घोषणा _PCIE_CADENCE_H

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>

/* Parameters क्रम the रुकोing क्रम link up routine */
#घोषणा LINK_WAIT_MAX_RETRIES	10
#घोषणा LINK_WAIT_USLEEP_MIN	90000
#घोषणा LINK_WAIT_USLEEP_MAX	100000

/*
 * Local Management Registers
 */
#घोषणा CDNS_PCIE_LM_BASE	0x00100000

/* Venकरोr ID Register */
#घोषणा CDNS_PCIE_LM_ID		(CDNS_PCIE_LM_BASE + 0x0044)
#घोषणा  CDNS_PCIE_LM_ID_VENDOR_MASK	GENMASK(15, 0)
#घोषणा  CDNS_PCIE_LM_ID_VENDOR_SHIFT	0
#घोषणा  CDNS_PCIE_LM_ID_VENDOR(vid) \
	(((vid) << CDNS_PCIE_LM_ID_VENDOR_SHIFT) & CDNS_PCIE_LM_ID_VENDOR_MASK)
#घोषणा  CDNS_PCIE_LM_ID_SUBSYS_MASK	GENMASK(31, 16)
#घोषणा  CDNS_PCIE_LM_ID_SUBSYS_SHIFT	16
#घोषणा  CDNS_PCIE_LM_ID_SUBSYS(sub) \
	(((sub) << CDNS_PCIE_LM_ID_SUBSYS_SHIFT) & CDNS_PCIE_LM_ID_SUBSYS_MASK)

/* Root Port Requestor ID Register */
#घोषणा CDNS_PCIE_LM_RP_RID	(CDNS_PCIE_LM_BASE + 0x0228)
#घोषणा  CDNS_PCIE_LM_RP_RID_MASK	GENMASK(15, 0)
#घोषणा  CDNS_PCIE_LM_RP_RID_SHIFT	0
#घोषणा  CDNS_PCIE_LM_RP_RID_(rid) \
	(((rid) << CDNS_PCIE_LM_RP_RID_SHIFT) & CDNS_PCIE_LM_RP_RID_MASK)

/* Endpoपूर्णांक Bus and Device Number Register */
#घोषणा CDNS_PCIE_LM_EP_ID	(CDNS_PCIE_LM_BASE + 0x022c)
#घोषणा  CDNS_PCIE_LM_EP_ID_DEV_MASK	GENMASK(4, 0)
#घोषणा  CDNS_PCIE_LM_EP_ID_DEV_SHIFT	0
#घोषणा  CDNS_PCIE_LM_EP_ID_BUS_MASK	GENMASK(15, 8)
#घोषणा  CDNS_PCIE_LM_EP_ID_BUS_SHIFT	8

/* Endpoपूर्णांक Function f BAR b Configuration Registers */
#घोषणा CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn) \
	(CDNS_PCIE_LM_BASE + 0x0240 + (fn) * 0x0008)
#घोषणा CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn) \
	(CDNS_PCIE_LM_BASE + 0x0244 + (fn) * 0x0008)
#घोषणा  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) \
	(GENMASK(4, 0) << ((b) * 8))
#घोषणा  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, a) \
	(((a) << ((b) * 8)) & CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b))
#घोषणा  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b) \
	(GENMASK(7, 5) << ((b) * 8))
#घोषणा  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, c) \
	(((c) << ((b) * 8 + 5)) & CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b))

/* Endpoपूर्णांक Function Configuration Register */
#घोषणा CDNS_PCIE_LM_EP_FUNC_CFG	(CDNS_PCIE_LM_BASE + 0x02c0)

/* Root Complex BAR Configuration Register */
#घोषणा CDNS_PCIE_LM_RC_BAR_CFG	(CDNS_PCIE_LM_BASE + 0x0300)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE_MASK	GENMASK(5, 0)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE(a) \
	(((a) << 0) & CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE_MASK)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL_MASK		GENMASK(8, 6)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL(c) \
	(((c) << 6) & CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL_MASK)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE_MASK	GENMASK(13, 9)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE(a) \
	(((a) << 9) & CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE_MASK)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL_MASK		GENMASK(16, 14)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL(c) \
	(((c) << 14) & CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL_MASK)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE	BIT(17)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_32BITS	0
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS	BIT(18)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE		BIT(19)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_IO_16BITS		0
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS		BIT(20)
#घोषणा  CDNS_PCIE_LM_RC_BAR_CFG_CHECK_ENABLE		BIT(31)

/* BAR control values applicable to both Endpoपूर्णांक Function and Root Complex */
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED		0x0
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS		0x1
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS		0x4
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS	0x5
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS		0x6
#घोषणा  CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS	0x7

#घोषणा LM_RC_BAR_CFG_CTRL_DISABLED(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_CTRL_IO_32BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar)	\
	(CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar)	\
	(CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS << (((bar) * 8) + 6))
#घोषणा LM_RC_BAR_CFG_APERTURE(bar, aperture)		\
					(((aperture) - 2) << ((bar) * 8))

/*
 * Endpoपूर्णांक Function Registers (PCI configuration space क्रम endpoपूर्णांक functions)
 */
#घोषणा CDNS_PCIE_EP_FUNC_BASE(fn)	(((fn) << 12) & GENMASK(19, 12))

#घोषणा CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET	0x90
#घोषणा CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET	0xb0

/*
 * Root Port Registers (PCI configuration space क्रम the root port function)
 */
#घोषणा CDNS_PCIE_RP_BASE	0x00200000
#घोषणा CDNS_PCIE_RP_CAP_OFFSET 0xc0

/*
 * Address Translation Registers
 */
#घोषणा CDNS_PCIE_AT_BASE	0x00400000

/* Region r Outbound AXI to PCIe Address Translation Register 0 */
#घोषणा CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r) \
	(CDNS_PCIE_AT_BASE + 0x0000 + ((r) & 0x1f) * 0x0020)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS_MASK	GENMASK(5, 0)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS_MASK)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK	GENMASK(19, 12)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN(devfn) \
	(((devfn) << 12) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK	GENMASK(27, 20)
#घोषणा  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS(bus) \
	(((bus) << 20) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK)

/* Region r Outbound AXI to PCIe Address Translation Register 1 */
#घोषणा CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r) \
	(CDNS_PCIE_AT_BASE + 0x0004 + ((r) & 0x1f) * 0x0020)

/* Region r Outbound PCIe Descriptor Register 0 */
#घोषणा CDNS_PCIE_AT_OB_REGION_DESC0(r) \
	(CDNS_PCIE_AT_BASE + 0x0008 + ((r) & 0x1f) * 0x0020)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MASK		GENMASK(3, 0)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM		0x2
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO		0x6
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE0	0xa
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE1	0xb
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_NORMAL_MSG	0xc
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_VENDOR_MSG	0xd
/* Bit 23 MUST be set in RC mode. */
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID	BIT(23)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK	GENMASK(31, 24)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(devfn) \
	(((devfn) << 24) & CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK)

/* Region r Outbound PCIe Descriptor Register 1 */
#घोषणा CDNS_PCIE_AT_OB_REGION_DESC1(r)	\
	(CDNS_PCIE_AT_BASE + 0x000c + ((r) & 0x1f) * 0x0020)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC1_BUS_MASK	GENMASK(7, 0)
#घोषणा  CDNS_PCIE_AT_OB_REGION_DESC1_BUS(bus) \
	((bus) & CDNS_PCIE_AT_OB_REGION_DESC1_BUS_MASK)

/* Region r AXI Region Base Address Register 0 */
#घोषणा CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r) \
	(CDNS_PCIE_AT_BASE + 0x0018 + ((r) & 0x1f) * 0x0020)
#घोषणा  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS_MASK	GENMASK(5, 0)
#घोषणा  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS_MASK)

/* Region r AXI Region Base Address Register 1 */
#घोषणा CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r) \
	(CDNS_PCIE_AT_BASE + 0x001c + ((r) & 0x1f) * 0x0020)

/* Root Port BAR Inbound PCIe to AXI Address Translation Register */
#घोषणा CDNS_PCIE_AT_IB_RP_BAR_ADDR0(bar) \
	(CDNS_PCIE_AT_BASE + 0x0800 + (bar) * 0x0008)
#घोषणा  CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS_MASK	GENMASK(5, 0)
#घोषणा  CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS_MASK)
#घोषणा CDNS_PCIE_AT_IB_RP_BAR_ADDR1(bar) \
	(CDNS_PCIE_AT_BASE + 0x0804 + (bar) * 0x0008)

/* AXI link करोwn रेजिस्टर */
#घोषणा CDNS_PCIE_AT_LINKDOWN (CDNS_PCIE_AT_BASE + 0x0824)

क्रमागत cdns_pcie_rp_bar अणु
	RP_BAR_UNDEFINED = -1,
	RP_BAR0,
	RP_BAR1,
	RP_NO_BAR
पूर्ण;

#घोषणा CDNS_PCIE_RP_MAX_IB	0x3
#घोषणा CDNS_PCIE_MAX_OB	32

काष्ठा cdns_pcie_rp_ib_bar अणु
	u64 size;
	bool मुक्त;
पूर्ण;

/* Endpoपूर्णांक Function BAR Inbound PCIe to AXI Address Translation Register */
#घोषणा CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar) \
	(CDNS_PCIE_AT_BASE + 0x0840 + (fn) * 0x0040 + (bar) * 0x0008)
#घोषणा CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar) \
	(CDNS_PCIE_AT_BASE + 0x0844 + (fn) * 0x0040 + (bar) * 0x0008)

/* Normal/Venकरोr specअगरic message access: offset inside some outbound region */
#घोषणा CDNS_PCIE_NORMAL_MSG_ROUTING_MASK	GENMASK(7, 5)
#घोषणा CDNS_PCIE_NORMAL_MSG_ROUTING(route) \
	(((route) << 5) & CDNS_PCIE_NORMAL_MSG_ROUTING_MASK)
#घोषणा CDNS_PCIE_NORMAL_MSG_CODE_MASK		GENMASK(15, 8)
#घोषणा CDNS_PCIE_NORMAL_MSG_CODE(code) \
	(((code) << 8) & CDNS_PCIE_NORMAL_MSG_CODE_MASK)
#घोषणा CDNS_PCIE_MSG_NO_DATA			BIT(16)

काष्ठा cdns_pcie;

क्रमागत cdns_pcie_msg_code अणु
	MSG_CODE_ASSERT_INTA	= 0x20,
	MSG_CODE_ASSERT_INTB	= 0x21,
	MSG_CODE_ASSERT_INTC	= 0x22,
	MSG_CODE_ASSERT_INTD	= 0x23,
	MSG_CODE_DEASSERT_INTA	= 0x24,
	MSG_CODE_DEASSERT_INTB	= 0x25,
	MSG_CODE_DEASSERT_INTC	= 0x26,
	MSG_CODE_DEASSERT_INTD	= 0x27,
पूर्ण;

क्रमागत cdns_pcie_msg_routing अणु
	/* Route to Root Complex */
	MSG_ROUTING_TO_RC,

	/* Use Address Routing */
	MSG_ROUTING_BY_ADDR,

	/* Use ID Routing */
	MSG_ROUTING_BY_ID,

	/* Route as Broadcast Message from Root Complex */
	MSG_ROUTING_BCAST,

	/* Local message; terminate at receiver (INTx messages) */
	MSG_ROUTING_LOCAL,

	/* Gather & route to Root Complex (PME_TO_Ack message) */
	MSG_ROUTING_GATHER,
पूर्ण;

काष्ठा cdns_pcie_ops अणु
	पूर्णांक	(*start_link)(काष्ठा cdns_pcie *pcie);
	व्योम	(*stop_link)(काष्ठा cdns_pcie *pcie);
	bool	(*link_up)(काष्ठा cdns_pcie *pcie);
	u64     (*cpu_addr_fixup)(काष्ठा cdns_pcie *pcie, u64 cpu_addr);
पूर्ण;

/**
 * काष्ठा cdns_pcie - निजी data क्रम Cadence PCIe controller drivers
 * @reg_base: IO mapped रेजिस्टर base
 * @mem_res: start/end offsets in the physical प्रणाली memory to map PCI accesses
 * @is_rc: tell whether the PCIe controller mode is Root Complex or Endpoपूर्णांक.
 * @bus: In Root Complex mode, the bus number
 * @ops: Platक्रमm specअगरic ops to control various inमाला_दो from Cadence PCIe
 *       wrapper
 */
काष्ठा cdns_pcie अणु
	व्योम __iomem		*reg_base;
	काष्ठा resource		*mem_res;
	काष्ठा device		*dev;
	bool			is_rc;
	पूर्णांक			phy_count;
	काष्ठा phy		**phy;
	काष्ठा device_link	**link;
	स्थिर काष्ठा cdns_pcie_ops *ops;
पूर्ण;

/**
 * काष्ठा cdns_pcie_rc - निजी data क्रम this PCIe Root Complex driver
 * @pcie: Cadence PCIe controller
 * @dev: poपूर्णांकer to PCIe device
 * @cfg_res: start/end offsets in the physical प्रणाली memory to map PCI
 *           configuration space accesses
 * @cfg_base: IO mapped winकरोw to access the PCI configuration space of a
 *            single function at a समय
 * @venकरोr_id: PCI venकरोr ID
 * @device_id: PCI device ID
 * @avail_ib_bar: Satus of RP_BAR0, RP_BAR1 and	RP_NO_BAR अगर it's मुक्त or
 *                available
 * @quirk_retrain_flag: Retrain link as quirk क्रम PCIe Gen2
 */
काष्ठा cdns_pcie_rc अणु
	काष्ठा cdns_pcie	pcie;
	काष्ठा resource		*cfg_res;
	व्योम __iomem		*cfg_base;
	u32			venकरोr_id;
	u32			device_id;
	bool			avail_ib_bar[CDNS_PCIE_RP_MAX_IB];
	bool                    quirk_retrain_flag;
पूर्ण;

/**
 * काष्ठा cdns_pcie_epf - Structure to hold info about endpoपूर्णांक function
 * @epf_bar: reference to the pci_epf_bar क्रम the six Base Address Registers
 */
काष्ठा cdns_pcie_epf अणु
	काष्ठा pci_epf_bar *epf_bar[PCI_STD_NUM_BARS];
पूर्ण;

/**
 * काष्ठा cdns_pcie_ep - निजी data क्रम this PCIe endpoपूर्णांक controller driver
 * @pcie: Cadence PCIe controller
 * @max_regions: maximum number of regions supported by hardware
 * @ob_region_map: biपंचांगask of mapped outbound regions
 * @ob_addr: base addresses in the AXI bus where the outbound regions start
 * @irq_phys_addr: base address on the AXI bus where the MSI/legacy IRQ
 *		   dedicated outbound regions is mapped.
 * @irq_cpu_addr: base address in the CPU space where a ग_लिखो access triggers
 *		  the sending of a memory ग_लिखो (MSI) / normal message (legacy
 *		  IRQ) TLP through the PCIe bus.
 * @irq_pci_addr: used to save the current mapping of the MSI/legacy IRQ
 *		  dedicated outbound region.
 * @irq_pci_fn: the latest PCI function that has updated the mapping of
 *		the MSI/legacy IRQ dedicated outbound region.
 * @irq_pending: biपंचांगask of निश्चितed legacy IRQs.
 * @lock: spin lock to disable पूर्णांकerrupts जबतक modअगरying PCIe controller
 *        रेजिस्टरs fields (RMW) accessible by both remote RC and EP to
 *        minimize समय between पढ़ो and ग_लिखो
 * @epf: Structure to hold info about endpoपूर्णांक function
 */
काष्ठा cdns_pcie_ep अणु
	काष्ठा cdns_pcie	pcie;
	u32			max_regions;
	अचिन्हित दीर्घ		ob_region_map;
	phys_addr_t		*ob_addr;
	phys_addr_t		irq_phys_addr;
	व्योम __iomem		*irq_cpu_addr;
	u64			irq_pci_addr;
	u8			irq_pci_fn;
	u8			irq_pending;
	/* protect writing to PCI_STATUS जबतक raising legacy पूर्णांकerrupts */
	spinlock_t		lock;
	काष्ठा cdns_pcie_epf	*epf;
पूर्ण;


/* Register access */
अटल अंतरभूत व्योम cdns_pcie_ग_लिखोl(काष्ठा cdns_pcie *pcie, u32 reg, u32 value)
अणु
	ग_लिखोl(value, pcie->reg_base + reg);
पूर्ण

अटल अंतरभूत u32 cdns_pcie_पढ़ोl(काष्ठा cdns_pcie *pcie, u32 reg)
अणु
	वापस पढ़ोl(pcie->reg_base + reg);
पूर्ण

अटल अंतरभूत u32 cdns_pcie_पढ़ो_sz(व्योम __iomem *addr, पूर्णांक size)
अणु
	व्योम __iomem *aligned_addr = PTR_ALIGN_DOWN(addr, 0x4);
	अचिन्हित पूर्णांक offset = (अचिन्हित दीर्घ)addr & 0x3;
	u32 val = पढ़ोl(aligned_addr);

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size)) अणु
		pr_warn("Address %p and size %d are not aligned\n", addr, size);
		वापस 0;
	पूर्ण

	अगर (size > 2)
		वापस val;

	वापस (val >> (8 * offset)) & ((1 << (size * 8)) - 1);
पूर्ण

अटल अंतरभूत व्योम cdns_pcie_ग_लिखो_sz(व्योम __iomem *addr, पूर्णांक size, u32 value)
अणु
	व्योम __iomem *aligned_addr = PTR_ALIGN_DOWN(addr, 0x4);
	अचिन्हित पूर्णांक offset = (अचिन्हित दीर्घ)addr & 0x3;
	u32 mask;
	u32 val;

	अगर (!IS_ALIGNED((uपूर्णांकptr_t)addr, size)) अणु
		pr_warn("Address %p and size %d are not aligned\n", addr, size);
		वापस;
	पूर्ण

	अगर (size > 2) अणु
		ग_लिखोl(value, addr);
		वापस;
	पूर्ण

	mask = ~(((1 << (size * 8)) - 1) << (offset * 8));
	val = पढ़ोl(aligned_addr) & mask;
	val |= value << (offset * 8);
	ग_लिखोl(val, aligned_addr);
पूर्ण

/* Root Port रेजिस्टर access */
अटल अंतरभूत व्योम cdns_pcie_rp_ग_लिखोb(काष्ठा cdns_pcie *pcie,
				       u32 reg, u8 value)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_RP_BASE + reg;

	cdns_pcie_ग_लिखो_sz(addr, 0x1, value);
पूर्ण

अटल अंतरभूत व्योम cdns_pcie_rp_ग_लिखोw(काष्ठा cdns_pcie *pcie,
				       u32 reg, u16 value)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_RP_BASE + reg;

	cdns_pcie_ग_लिखो_sz(addr, 0x2, value);
पूर्ण

अटल अंतरभूत u16 cdns_pcie_rp_पढ़ोw(काष्ठा cdns_pcie *pcie, u32 reg)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_RP_BASE + reg;

	वापस cdns_pcie_पढ़ो_sz(addr, 0x2);
पूर्ण

/* Endpoपूर्णांक Function रेजिस्टर access */
अटल अंतरभूत व्योम cdns_pcie_ep_fn_ग_लिखोb(काष्ठा cdns_pcie *pcie, u8 fn,
					  u32 reg, u8 value)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg;

	cdns_pcie_ग_लिखो_sz(addr, 0x1, value);
पूर्ण

अटल अंतरभूत व्योम cdns_pcie_ep_fn_ग_लिखोw(काष्ठा cdns_pcie *pcie, u8 fn,
					  u32 reg, u16 value)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg;

	cdns_pcie_ग_लिखो_sz(addr, 0x2, value);
पूर्ण

अटल अंतरभूत व्योम cdns_pcie_ep_fn_ग_लिखोl(काष्ठा cdns_pcie *pcie, u8 fn,
					  u32 reg, u32 value)
अणु
	ग_लिखोl(value, pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
पूर्ण

अटल अंतरभूत u16 cdns_pcie_ep_fn_पढ़ोw(काष्ठा cdns_pcie *pcie, u8 fn, u32 reg)
अणु
	व्योम __iomem *addr = pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg;

	वापस cdns_pcie_पढ़ो_sz(addr, 0x2);
पूर्ण

अटल अंतरभूत u32 cdns_pcie_ep_fn_पढ़ोl(काष्ठा cdns_pcie *pcie, u8 fn, u32 reg)
अणु
	वापस पढ़ोl(pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
पूर्ण

अटल अंतरभूत पूर्णांक cdns_pcie_start_link(काष्ठा cdns_pcie *pcie)
अणु
	अगर (pcie->ops->start_link)
		वापस pcie->ops->start_link(pcie);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cdns_pcie_stop_link(काष्ठा cdns_pcie *pcie)
अणु
	अगर (pcie->ops->stop_link)
		pcie->ops->stop_link(pcie);
पूर्ण

अटल अंतरभूत bool cdns_pcie_link_up(काष्ठा cdns_pcie *pcie)
अणु
	अगर (pcie->ops->link_up)
		वापस pcie->ops->link_up(pcie);

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_PCIE_CADENCE_HOST
पूर्णांक cdns_pcie_host_setup(काष्ठा cdns_pcie_rc *rc);
व्योम __iomem *cdns_pci_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where);
#अन्यथा
अटल अंतरभूत पूर्णांक cdns_pcie_host_setup(काष्ठा cdns_pcie_rc *rc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __iomem *cdns_pci_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
					     पूर्णांक where)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_CADENCE_EP
पूर्णांक cdns_pcie_ep_setup(काष्ठा cdns_pcie_ep *ep);
#अन्यथा
अटल अंतरभूत पूर्णांक cdns_pcie_ep_setup(काष्ठा cdns_pcie_ep *ep)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
व्योम cdns_pcie_set_outbound_region(काष्ठा cdns_pcie *pcie, u8 busnr, u8 fn,
				   u32 r, bool is_io,
				   u64 cpu_addr, u64 pci_addr, माप_प्रकार size);

व्योम cdns_pcie_set_outbound_region_क्रम_normal_msg(काष्ठा cdns_pcie *pcie,
						  u8 busnr, u8 fn,
						  u32 r, u64 cpu_addr);

व्योम cdns_pcie_reset_outbound_region(काष्ठा cdns_pcie *pcie, u32 r);
व्योम cdns_pcie_disable_phy(काष्ठा cdns_pcie *pcie);
पूर्णांक cdns_pcie_enable_phy(काष्ठा cdns_pcie *pcie);
पूर्णांक cdns_pcie_init_phy(काष्ठा device *dev, काष्ठा cdns_pcie *pcie);
बाह्य स्थिर काष्ठा dev_pm_ops cdns_pcie_pm_ops;

#पूर्ण_अगर /* _PCIE_CADENCE_H */
