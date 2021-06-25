<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Synopsys DesignWare PCIe host controller driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		https://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#अगर_अघोषित _PCIE_DESIGNWARE_H
#घोषणा _PCIE_DESIGNWARE_H

#समावेश <linux/bitfield.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/pci.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>

/* Parameters क्रम the रुकोing क्रम link up routine */
#घोषणा LINK_WAIT_MAX_RETRIES		10
#घोषणा LINK_WAIT_USLEEP_MIN		90000
#घोषणा LINK_WAIT_USLEEP_MAX		100000

/* Parameters क्रम the रुकोing क्रम iATU enabled routine */
#घोषणा LINK_WAIT_MAX_IATU_RETRIES	5
#घोषणा LINK_WAIT_IATU			9

/* Synopsys-specअगरic PCIe configuration रेजिस्टरs */
#घोषणा PCIE_PORT_AFR			0x70C
#घोषणा PORT_AFR_N_FTS_MASK		GENMASK(15, 8)
#घोषणा PORT_AFR_N_FTS(n)		FIELD_PREP(PORT_AFR_N_FTS_MASK, n)
#घोषणा PORT_AFR_CC_N_FTS_MASK		GENMASK(23, 16)
#घोषणा PORT_AFR_CC_N_FTS(n)		FIELD_PREP(PORT_AFR_CC_N_FTS_MASK, n)
#घोषणा PORT_AFR_ENTER_ASPM		BIT(30)
#घोषणा PORT_AFR_L0S_ENTRANCE_LAT_SHIFT	24
#घोषणा PORT_AFR_L0S_ENTRANCE_LAT_MASK	GENMASK(26, 24)
#घोषणा PORT_AFR_L1_ENTRANCE_LAT_SHIFT	27
#घोषणा PORT_AFR_L1_ENTRANCE_LAT_MASK	GENMASK(29, 27)

#घोषणा PCIE_PORT_LINK_CONTROL		0x710
#घोषणा PORT_LINK_DLL_LINK_EN		BIT(5)
#घोषणा PORT_LINK_FAST_LINK_MODE	BIT(7)
#घोषणा PORT_LINK_MODE_MASK		GENMASK(21, 16)
#घोषणा PORT_LINK_MODE(n)		FIELD_PREP(PORT_LINK_MODE_MASK, n)
#घोषणा PORT_LINK_MODE_1_LANES		PORT_LINK_MODE(0x1)
#घोषणा PORT_LINK_MODE_2_LANES		PORT_LINK_MODE(0x3)
#घोषणा PORT_LINK_MODE_4_LANES		PORT_LINK_MODE(0x7)
#घोषणा PORT_LINK_MODE_8_LANES		PORT_LINK_MODE(0xf)

#घोषणा PCIE_PORT_DEBUG0		0x728
#घोषणा PORT_LOGIC_LTSSM_STATE_MASK	0x1f
#घोषणा PORT_LOGIC_LTSSM_STATE_L0	0x11
#घोषणा PCIE_PORT_DEBUG1		0x72C
#घोषणा PCIE_PORT_DEBUG1_LINK_UP		BIT(4)
#घोषणा PCIE_PORT_DEBUG1_LINK_IN_TRAINING	BIT(29)

#घोषणा PCIE_LINK_WIDTH_SPEED_CONTROL	0x80C
#घोषणा PORT_LOGIC_N_FTS_MASK		GENMASK(7, 0)
#घोषणा PORT_LOGIC_SPEED_CHANGE		BIT(17)
#घोषणा PORT_LOGIC_LINK_WIDTH_MASK	GENMASK(12, 8)
#घोषणा PORT_LOGIC_LINK_WIDTH(n)	FIELD_PREP(PORT_LOGIC_LINK_WIDTH_MASK, n)
#घोषणा PORT_LOGIC_LINK_WIDTH_1_LANES	PORT_LOGIC_LINK_WIDTH(0x1)
#घोषणा PORT_LOGIC_LINK_WIDTH_2_LANES	PORT_LOGIC_LINK_WIDTH(0x2)
#घोषणा PORT_LOGIC_LINK_WIDTH_4_LANES	PORT_LOGIC_LINK_WIDTH(0x4)
#घोषणा PORT_LOGIC_LINK_WIDTH_8_LANES	PORT_LOGIC_LINK_WIDTH(0x8)

#घोषणा PCIE_MSI_ADDR_LO		0x820
#घोषणा PCIE_MSI_ADDR_HI		0x824
#घोषणा PCIE_MSI_INTR0_ENABLE		0x828
#घोषणा PCIE_MSI_INTR0_MASK		0x82C
#घोषणा PCIE_MSI_INTR0_STATUS		0x830

#घोषणा PCIE_PORT_MULTI_LANE_CTRL	0x8C0
#घोषणा PORT_MLTI_UPCFG_SUPPORT		BIT(7)

#घोषणा PCIE_ATU_VIEWPORT		0x900
#घोषणा PCIE_ATU_REGION_INBOUND		BIT(31)
#घोषणा PCIE_ATU_REGION_OUTBOUND	0
#घोषणा PCIE_ATU_CR1			0x904
#घोषणा PCIE_ATU_INCREASE_REGION_SIZE	BIT(13)
#घोषणा PCIE_ATU_TYPE_MEM		0x0
#घोषणा PCIE_ATU_TYPE_IO		0x2
#घोषणा PCIE_ATU_TYPE_CFG0		0x4
#घोषणा PCIE_ATU_TYPE_CFG1		0x5
#घोषणा PCIE_ATU_TD			BIT(8)
#घोषणा PCIE_ATU_FUNC_NUM(pf)           ((pf) << 20)
#घोषणा PCIE_ATU_CR2			0x908
#घोषणा PCIE_ATU_ENABLE			BIT(31)
#घोषणा PCIE_ATU_BAR_MODE_ENABLE	BIT(30)
#घोषणा PCIE_ATU_FUNC_NUM_MATCH_EN      BIT(19)
#घोषणा PCIE_ATU_LOWER_BASE		0x90C
#घोषणा PCIE_ATU_UPPER_BASE		0x910
#घोषणा PCIE_ATU_LIMIT			0x914
#घोषणा PCIE_ATU_LOWER_TARGET		0x918
#घोषणा PCIE_ATU_BUS(x)			FIELD_PREP(GENMASK(31, 24), x)
#घोषणा PCIE_ATU_DEV(x)			FIELD_PREP(GENMASK(23, 19), x)
#घोषणा PCIE_ATU_FUNC(x)		FIELD_PREP(GENMASK(18, 16), x)
#घोषणा PCIE_ATU_UPPER_TARGET		0x91C
#घोषणा PCIE_ATU_UPPER_LIMIT		0x924

#घोषणा PCIE_MISC_CONTROL_1_OFF		0x8BC
#घोषणा PCIE_DBI_RO_WR_EN		BIT(0)

#घोषणा PCIE_MSIX_DOORBELL		0x948
#घोषणा PCIE_MSIX_DOORBELL_PF_SHIFT	24

#घोषणा PCIE_PL_CHK_REG_CONTROL_STATUS			0xB20
#घोषणा PCIE_PL_CHK_REG_CHK_REG_START			BIT(0)
#घोषणा PCIE_PL_CHK_REG_CHK_REG_CONTINUOUS		BIT(1)
#घोषणा PCIE_PL_CHK_REG_CHK_REG_COMPARISON_ERROR	BIT(16)
#घोषणा PCIE_PL_CHK_REG_CHK_REG_LOGIC_ERROR		BIT(17)
#घोषणा PCIE_PL_CHK_REG_CHK_REG_COMPLETE		BIT(18)

#घोषणा PCIE_PL_CHK_REG_ERR_ADDR			0xB28

/*
 * iATU Unroll-specअगरic रेजिस्टर definitions
 * From 4.80 core version the address translation will be made by unroll
 */
#घोषणा PCIE_ATU_UNR_REGION_CTRL1	0x00
#घोषणा PCIE_ATU_UNR_REGION_CTRL2	0x04
#घोषणा PCIE_ATU_UNR_LOWER_BASE		0x08
#घोषणा PCIE_ATU_UNR_UPPER_BASE		0x0C
#घोषणा PCIE_ATU_UNR_LOWER_LIMIT	0x10
#घोषणा PCIE_ATU_UNR_LOWER_TARGET	0x14
#घोषणा PCIE_ATU_UNR_UPPER_TARGET	0x18
#घोषणा PCIE_ATU_UNR_UPPER_LIMIT	0x20

/*
 * The शेष address offset between dbi_base and atu_base. Root controller
 * drivers are not required to initialize atu_base अगर the offset matches this
 * शेष; the driver core स्वतःmatically derives atu_base from dbi_base using
 * this offset, अगर atu_base not set.
 */
#घोषणा DEFAULT_DBI_ATU_OFFSET (0x3 << 20)

/* Register address builder */
#घोषणा PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(region) \
		((region) << 9)

#घोषणा PCIE_GET_ATU_INB_UNR_REG_OFFSET(region) \
		(((region) << 9) | BIT(8))

#घोषणा MAX_MSI_IRQS			256
#घोषणा MAX_MSI_IRQS_PER_CTRL		32
#घोषणा MAX_MSI_CTRLS			(MAX_MSI_IRQS / MAX_MSI_IRQS_PER_CTRL)
#घोषणा MSI_REG_CTRL_BLOCK_SIZE		12
#घोषणा MSI_DEF_NUM_VECTORS		32

/* Maximum number of inbound/outbound iATUs */
#घोषणा MAX_IATU_IN			256
#घोषणा MAX_IATU_OUT			256

काष्ठा pcie_port;
काष्ठा dw_pcie;
काष्ठा dw_pcie_ep;

क्रमागत dw_pcie_region_type अणु
	DW_PCIE_REGION_UNKNOWN,
	DW_PCIE_REGION_INBOUND,
	DW_PCIE_REGION_OUTBOUND,
पूर्ण;

क्रमागत dw_pcie_device_mode अणु
	DW_PCIE_UNKNOWN_TYPE,
	DW_PCIE_EP_TYPE,
	DW_PCIE_LEG_EP_TYPE,
	DW_PCIE_RC_TYPE,
पूर्ण;

काष्ठा dw_pcie_host_ops अणु
	पूर्णांक (*host_init)(काष्ठा pcie_port *pp);
	पूर्णांक (*msi_host_init)(काष्ठा pcie_port *pp);
पूर्ण;

काष्ठा pcie_port अणु
	bool			has_msi_ctrl:1;
	u64			cfg0_base;
	व्योम __iomem		*va_cfg0_base;
	u32			cfg0_size;
	resource_माप_प्रकार		io_base;
	phys_addr_t		io_bus_addr;
	u32			io_size;
	पूर्णांक			irq;
	स्थिर काष्ठा dw_pcie_host_ops *ops;
	पूर्णांक			msi_irq;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	काष्ठा irq_करोमुख्य	*msi_करोमुख्य;
	u16			msi_msg;
	dma_addr_t		msi_data;
	काष्ठा irq_chip		*msi_irq_chip;
	u32			num_vectors;
	u32			irq_mask[MAX_MSI_CTRLS];
	काष्ठा pci_host_bridge  *bridge;
	raw_spinlock_t		lock;
	DECLARE_BITMAP(msi_irq_in_use, MAX_MSI_IRQS);
पूर्ण;

क्रमागत dw_pcie_as_type अणु
	DW_PCIE_AS_UNKNOWN,
	DW_PCIE_AS_MEM,
	DW_PCIE_AS_IO,
पूर्ण;

काष्ठा dw_pcie_ep_ops अणु
	व्योम	(*ep_init)(काष्ठा dw_pcie_ep *ep);
	पूर्णांक	(*उठाओ_irq)(काष्ठा dw_pcie_ep *ep, u8 func_no,
			     क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num);
	स्थिर काष्ठा pci_epc_features* (*get_features)(काष्ठा dw_pcie_ep *ep);
	/*
	 * Provide a method to implement the dअगरferent func config space
	 * access क्रम dअगरferent platक्रमm, अगर dअगरferent func have dअगरferent
	 * offset, वापस the offset of func. अगर use ग_लिखो a रेजिस्टर way
	 * वापस a 0, and implement code in callback function of platक्रमm
	 * driver.
	 */
	अचिन्हित पूर्णांक (*func_conf_select)(काष्ठा dw_pcie_ep *ep, u8 func_no);
पूर्ण;

काष्ठा dw_pcie_ep_func अणु
	काष्ठा list_head	list;
	u8			func_no;
	u8			msi_cap;	/* MSI capability offset */
	u8			msix_cap;	/* MSI-X capability offset */
पूर्ण;

काष्ठा dw_pcie_ep अणु
	काष्ठा pci_epc		*epc;
	काष्ठा list_head	func_list;
	स्थिर काष्ठा dw_pcie_ep_ops *ops;
	phys_addr_t		phys_base;
	माप_प्रकार			addr_size;
	माप_प्रकार			page_size;
	u8			bar_to_atu[PCI_STD_NUM_BARS];
	phys_addr_t		*outbound_addr;
	अचिन्हित दीर्घ		*ib_winकरोw_map;
	अचिन्हित दीर्घ		*ob_winकरोw_map;
	व्योम __iomem		*msi_mem;
	phys_addr_t		msi_mem_phys;
	काष्ठा pci_epf_bar	*epf_bar[PCI_STD_NUM_BARS];
पूर्ण;

काष्ठा dw_pcie_ops अणु
	u64	(*cpu_addr_fixup)(काष्ठा dw_pcie *pcie, u64 cpu_addr);
	u32	(*पढ़ो_dbi)(काष्ठा dw_pcie *pcie, व्योम __iomem *base, u32 reg,
			    माप_प्रकार size);
	व्योम	(*ग_लिखो_dbi)(काष्ठा dw_pcie *pcie, व्योम __iomem *base, u32 reg,
			     माप_प्रकार size, u32 val);
	व्योम    (*ग_लिखो_dbi2)(काष्ठा dw_pcie *pcie, व्योम __iomem *base, u32 reg,
			      माप_प्रकार size, u32 val);
	पूर्णांक	(*link_up)(काष्ठा dw_pcie *pcie);
	पूर्णांक	(*start_link)(काष्ठा dw_pcie *pcie);
	व्योम	(*stop_link)(काष्ठा dw_pcie *pcie);
पूर्ण;

काष्ठा dw_pcie अणु
	काष्ठा device		*dev;
	व्योम __iomem		*dbi_base;
	व्योम __iomem		*dbi_base2;
	/* Used when iatu_unroll_enabled is true */
	व्योम __iomem		*atu_base;
	माप_प्रकार			atu_size;
	u32			num_ib_winकरोws;
	u32			num_ob_winकरोws;
	काष्ठा pcie_port	pp;
	काष्ठा dw_pcie_ep	ep;
	स्थिर काष्ठा dw_pcie_ops *ops;
	अचिन्हित पूर्णांक		version;
	पूर्णांक			num_lanes;
	पूर्णांक			link_gen;
	u8			n_fts[2];
	bool			iatu_unroll_enabled: 1;
	bool			io_cfg_atu_shared: 1;
पूर्ण;

#घोषणा to_dw_pcie_from_pp(port) container_of((port), काष्ठा dw_pcie, pp)

#घोषणा to_dw_pcie_from_ep(endpoपूर्णांक)   \
		container_of((endpoपूर्णांक), काष्ठा dw_pcie, ep)

u8 dw_pcie_find_capability(काष्ठा dw_pcie *pci, u8 cap);
u16 dw_pcie_find_ext_capability(काष्ठा dw_pcie *pci, u8 cap);

पूर्णांक dw_pcie_पढ़ो(व्योम __iomem *addr, पूर्णांक size, u32 *val);
पूर्णांक dw_pcie_ग_लिखो(व्योम __iomem *addr, पूर्णांक size, u32 val);

u32 dw_pcie_पढ़ो_dbi(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size);
व्योम dw_pcie_ग_लिखो_dbi(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size, u32 val);
व्योम dw_pcie_ग_लिखो_dbi2(काष्ठा dw_pcie *pci, u32 reg, माप_प्रकार size, u32 val);
पूर्णांक dw_pcie_link_up(काष्ठा dw_pcie *pci);
व्योम dw_pcie_upconfig_setup(काष्ठा dw_pcie *pci);
पूर्णांक dw_pcie_रुको_क्रम_link(काष्ठा dw_pcie *pci);
व्योम dw_pcie_prog_outbound_atu(काष्ठा dw_pcie *pci, पूर्णांक index,
			       पूर्णांक type, u64 cpu_addr, u64 pci_addr,
			       u64 size);
व्योम dw_pcie_prog_ep_outbound_atu(काष्ठा dw_pcie *pci, u8 func_no, पूर्णांक index,
				  पूर्णांक type, u64 cpu_addr, u64 pci_addr,
				  u64 size);
पूर्णांक dw_pcie_prog_inbound_atu(काष्ठा dw_pcie *pci, u8 func_no, पूर्णांक index,
			     पूर्णांक bar, u64 cpu_addr,
			     क्रमागत dw_pcie_as_type as_type);
व्योम dw_pcie_disable_atu(काष्ठा dw_pcie *pci, पूर्णांक index,
			 क्रमागत dw_pcie_region_type type);
व्योम dw_pcie_setup(काष्ठा dw_pcie *pci);
व्योम dw_pcie_iatu_detect(काष्ठा dw_pcie *pci);

अटल अंतरभूत व्योम dw_pcie_ग_लिखोl_dbi(काष्ठा dw_pcie *pci, u32 reg, u32 val)
अणु
	dw_pcie_ग_लिखो_dbi(pci, reg, 0x4, val);
पूर्ण

अटल अंतरभूत u32 dw_pcie_पढ़ोl_dbi(काष्ठा dw_pcie *pci, u32 reg)
अणु
	वापस dw_pcie_पढ़ो_dbi(pci, reg, 0x4);
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ग_लिखोw_dbi(काष्ठा dw_pcie *pci, u32 reg, u16 val)
अणु
	dw_pcie_ग_लिखो_dbi(pci, reg, 0x2, val);
पूर्ण

अटल अंतरभूत u16 dw_pcie_पढ़ोw_dbi(काष्ठा dw_pcie *pci, u32 reg)
अणु
	वापस dw_pcie_पढ़ो_dbi(pci, reg, 0x2);
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ग_लिखोb_dbi(काष्ठा dw_pcie *pci, u32 reg, u8 val)
अणु
	dw_pcie_ग_लिखो_dbi(pci, reg, 0x1, val);
पूर्ण

अटल अंतरभूत u8 dw_pcie_पढ़ोb_dbi(काष्ठा dw_pcie *pci, u32 reg)
अणु
	वापस dw_pcie_पढ़ो_dbi(pci, reg, 0x1);
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ग_लिखोl_dbi2(काष्ठा dw_pcie *pci, u32 reg, u32 val)
अणु
	dw_pcie_ग_लिखो_dbi2(pci, reg, 0x4, val);
पूर्ण

अटल अंतरभूत व्योम dw_pcie_dbi_ro_wr_en(काष्ठा dw_pcie *pci)
अणु
	u32 reg;
	u32 val;

	reg = PCIE_MISC_CONTROL_1_OFF;
	val = dw_pcie_पढ़ोl_dbi(pci, reg);
	val |= PCIE_DBI_RO_WR_EN;
	dw_pcie_ग_लिखोl_dbi(pci, reg, val);
पूर्ण

अटल अंतरभूत व्योम dw_pcie_dbi_ro_wr_dis(काष्ठा dw_pcie *pci)
अणु
	u32 reg;
	u32 val;

	reg = PCIE_MISC_CONTROL_1_OFF;
	val = dw_pcie_पढ़ोl_dbi(pci, reg);
	val &= ~PCIE_DBI_RO_WR_EN;
	dw_pcie_ग_लिखोl_dbi(pci, reg, val);
पूर्ण

#अगर_घोषित CONFIG_PCIE_DW_HOST
irqवापस_t dw_handle_msi_irq(काष्ठा pcie_port *pp);
व्योम dw_pcie_setup_rc(काष्ठा pcie_port *pp);
पूर्णांक dw_pcie_host_init(काष्ठा pcie_port *pp);
व्योम dw_pcie_host_deinit(काष्ठा pcie_port *pp);
पूर्णांक dw_pcie_allocate_करोमुख्यs(काष्ठा pcie_port *pp);
व्योम __iomem *dw_pcie_own_conf_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				       पूर्णांक where);
#अन्यथा
अटल अंतरभूत irqवापस_t dw_handle_msi_irq(काष्ठा pcie_port *pp)
अणु
	वापस IRQ_NONE;
पूर्ण

अटल अंतरभूत व्योम dw_pcie_setup_rc(काष्ठा pcie_port *pp)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dw_pcie_host_deinit(काष्ठा pcie_port *pp)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_allocate_करोमुख्यs(काष्ठा pcie_port *pp)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम __iomem *dw_pcie_own_conf_map_bus(काष्ठा pci_bus *bus,
						     अचिन्हित पूर्णांक devfn,
						     पूर्णांक where)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PCIE_DW_EP
व्योम dw_pcie_ep_linkup(काष्ठा dw_pcie_ep *ep);
पूर्णांक dw_pcie_ep_init(काष्ठा dw_pcie_ep *ep);
पूर्णांक dw_pcie_ep_init_complete(काष्ठा dw_pcie_ep *ep);
व्योम dw_pcie_ep_init_notअगरy(काष्ठा dw_pcie_ep *ep);
व्योम dw_pcie_ep_निकास(काष्ठा dw_pcie_ep *ep);
पूर्णांक dw_pcie_ep_उठाओ_legacy_irq(काष्ठा dw_pcie_ep *ep, u8 func_no);
पूर्णांक dw_pcie_ep_उठाओ_msi_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
			     u8 पूर्णांकerrupt_num);
पूर्णांक dw_pcie_ep_उठाओ_msix_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
			     u16 पूर्णांकerrupt_num);
पूर्णांक dw_pcie_ep_उठाओ_msix_irq_करोorbell(काष्ठा dw_pcie_ep *ep, u8 func_no,
				       u16 पूर्णांकerrupt_num);
व्योम dw_pcie_ep_reset_bar(काष्ठा dw_pcie *pci, क्रमागत pci_barno bar);
काष्ठा dw_pcie_ep_func *
dw_pcie_ep_get_func_from_ep(काष्ठा dw_pcie_ep *ep, u8 func_no);
#अन्यथा
अटल अंतरभूत व्योम dw_pcie_ep_linkup(काष्ठा dw_pcie_ep *ep)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_init_complete(काष्ठा dw_pcie_ep *ep)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ep_init_notअगरy(काष्ठा dw_pcie_ep *ep)
अणु
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ep_निकास(काष्ठा dw_pcie_ep *ep)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_उठाओ_legacy_irq(काष्ठा dw_pcie_ep *ep, u8 func_no)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_उठाओ_msi_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
					   u8 पूर्णांकerrupt_num)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_उठाओ_msix_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
					   u16 पूर्णांकerrupt_num)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dw_pcie_ep_उठाओ_msix_irq_करोorbell(काष्ठा dw_pcie_ep *ep,
						     u8 func_no,
						     u16 पूर्णांकerrupt_num)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dw_pcie_ep_reset_bar(काष्ठा dw_pcie *pci, क्रमागत pci_barno bar)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dw_pcie_ep_func *
dw_pcie_ep_get_func_from_ep(काष्ठा dw_pcie_ep *ep, u8 func_no)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _PCIE_DESIGNWARE_H */
