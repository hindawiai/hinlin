<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCIe host controller driver क्रम Mobiveil PCIe Host controller
 *
 * Copyright (c) 2018 Mobiveil Inc.
 * Copyright 2019 NXP
 *
 * Author: Subrahmanya Lingappa <l.subrahmanya@mobiveil.co.in>
 *	   Hou Zhiqiang <Zhiqiang.Hou@nxp.com>
 */

#अगर_अघोषित _PCIE_MOBIVEIL_H
#घोषणा _PCIE_MOBIVEIL_H

#समावेश <linux/pci.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश "../../pci.h"

/* रेजिस्टर offsets and bit positions */

/*
 * translation tables are grouped पूर्णांकo winकरोws, each winकरोw रेजिस्टरs are
 * grouped पूर्णांकo blocks of 4 or 16 रेजिस्टरs each
 */
#घोषणा PAB_REG_BLOCK_SIZE		16
#घोषणा PAB_EXT_REG_BLOCK_SIZE		4

#घोषणा PAB_REG_ADDR(offset, win)	\
	(offset + (win * PAB_REG_BLOCK_SIZE))
#घोषणा PAB_EXT_REG_ADDR(offset, win)	\
	(offset + (win * PAB_EXT_REG_BLOCK_SIZE))

#घोषणा LTSSM_STATUS			0x0404
#घोषणा  LTSSM_STATUS_L0_MASK		0x3f
#घोषणा  LTSSM_STATUS_L0		0x2d

#घोषणा PAB_CTRL			0x0808
#घोषणा  AMBA_PIO_ENABLE_SHIFT		0
#घोषणा  PEX_PIO_ENABLE_SHIFT		1
#घोषणा  PAGE_SEL_SHIFT			13
#घोषणा  PAGE_SEL_MASK			0x3f
#घोषणा  PAGE_LO_MASK			0x3ff
#घोषणा  PAGE_SEL_OFFSET_SHIFT		10

#घोषणा PAB_ACTIVITY_STAT		0x81c

#घोषणा PAB_AXI_PIO_CTRL		0x0840
#घोषणा  APIO_EN_MASK			0xf

#घोषणा PAB_PEX_PIO_CTRL		0x08c0
#घोषणा  PIO_ENABLE_SHIFT		0

#घोषणा PAB_INTP_AMBA_MISC_ENB		0x0b0c
#घोषणा PAB_INTP_AMBA_MISC_STAT		0x0b1c
#घोषणा  PAB_INTP_RESET			BIT(1)
#घोषणा  PAB_INTP_MSI			BIT(3)
#घोषणा  PAB_INTP_INTA			BIT(5)
#घोषणा  PAB_INTP_INTB			BIT(6)
#घोषणा  PAB_INTP_INTC			BIT(7)
#घोषणा  PAB_INTP_INTD			BIT(8)
#घोषणा  PAB_INTP_PCIE_UE		BIT(9)
#घोषणा  PAB_INTP_IE_PMREDI		BIT(29)
#घोषणा  PAB_INTP_IE_EC			BIT(30)
#घोषणा  PAB_INTP_MSI_MASK		PAB_INTP_MSI
#घोषणा  PAB_INTP_INTX_MASK		(PAB_INTP_INTA | PAB_INTP_INTB |\
					PAB_INTP_INTC | PAB_INTP_INTD)

#घोषणा PAB_AXI_AMAP_CTRL(win)		PAB_REG_ADDR(0x0ba0, win)
#घोषणा  WIN_ENABLE_SHIFT		0
#घोषणा  WIN_TYPE_SHIFT			1
#घोषणा  WIN_TYPE_MASK			0x3
#घोषणा  WIN_SIZE_MASK			0xfffffc00

#घोषणा PAB_EXT_AXI_AMAP_SIZE(win)	PAB_EXT_REG_ADDR(0xbaf0, win)

#घोषणा PAB_EXT_AXI_AMAP_AXI_WIN(win)	PAB_EXT_REG_ADDR(0x80a0, win)
#घोषणा PAB_AXI_AMAP_AXI_WIN(win)	PAB_REG_ADDR(0x0ba4, win)
#घोषणा  AXI_WINDOW_ALIGN_MASK		3

#घोषणा PAB_AXI_AMAP_PEX_WIN_L(win)	PAB_REG_ADDR(0x0ba8, win)
#घोषणा  PAB_BUS_SHIFT			24
#घोषणा  PAB_DEVICE_SHIFT		19
#घोषणा  PAB_FUNCTION_SHIFT		16

#घोषणा PAB_AXI_AMAP_PEX_WIN_H(win)	PAB_REG_ADDR(0x0bac, win)
#घोषणा PAB_INTP_AXI_PIO_CLASS		0x474

#घोषणा PAB_PEX_AMAP_CTRL(win)		PAB_REG_ADDR(0x4ba0, win)
#घोषणा  AMAP_CTRL_EN_SHIFT		0
#घोषणा  AMAP_CTRL_TYPE_SHIFT		1
#घोषणा  AMAP_CTRL_TYPE_MASK		3

#घोषणा PAB_EXT_PEX_AMAP_SIZEN(win)	PAB_EXT_REG_ADDR(0xbef0, win)
#घोषणा PAB_EXT_PEX_AMAP_AXI_WIN(win)	PAB_EXT_REG_ADDR(0xb4a0, win)
#घोषणा PAB_PEX_AMAP_AXI_WIN(win)	PAB_REG_ADDR(0x4ba4, win)
#घोषणा PAB_PEX_AMAP_PEX_WIN_L(win)	PAB_REG_ADDR(0x4ba8, win)
#घोषणा PAB_PEX_AMAP_PEX_WIN_H(win)	PAB_REG_ADDR(0x4bac, win)

/* starting offset of INTX bits in status रेजिस्टर */
#घोषणा PAB_INTX_START			5

/* supported number of MSI पूर्णांकerrupts */
#घोषणा PCI_NUM_MSI			16

/* MSI रेजिस्टरs */
#घोषणा MSI_BASE_LO_OFFSET		0x04
#घोषणा MSI_BASE_HI_OFFSET		0x08
#घोषणा MSI_SIZE_OFFSET			0x0c
#घोषणा MSI_ENABLE_OFFSET		0x14
#घोषणा MSI_STATUS_OFFSET		0x18
#घोषणा MSI_DATA_OFFSET			0x20
#घोषणा MSI_ADDR_L_OFFSET		0x24
#घोषणा MSI_ADDR_H_OFFSET		0x28

/* outbound and inbound winकरोw definitions */
#घोषणा WIN_NUM_0			0
#घोषणा WIN_NUM_1			1
#घोषणा CFG_WINDOW_TYPE			0
#घोषणा IO_WINDOW_TYPE			1
#घोषणा MEM_WINDOW_TYPE			2
#घोषणा IB_WIN_SIZE			((u64)256 * 1024 * 1024 * 1024)
#घोषणा MAX_PIO_WINDOWS			8

/* Parameters क्रम the रुकोing क्रम link up routine */
#घोषणा LINK_WAIT_MAX_RETRIES		10
#घोषणा LINK_WAIT_MIN			90000
#घोषणा LINK_WAIT_MAX			100000

#घोषणा PAGED_ADDR_BNDRY		0xc00
#घोषणा OFFSET_TO_PAGE_ADDR(off)	\
	((off & PAGE_LO_MASK) | PAGED_ADDR_BNDRY)
#घोषणा OFFSET_TO_PAGE_IDX(off)		\
	((off >> PAGE_SEL_OFFSET_SHIFT) & PAGE_SEL_MASK)

काष्ठा mobiveil_msi अणु			/* MSI inक्रमmation */
	काष्ठा mutex lock;		/* protect biपंचांगap variable */
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा irq_करोमुख्य *dev_करोमुख्य;
	phys_addr_t msi_pages_phys;
	पूर्णांक num_of_vectors;
	DECLARE_BITMAP(msi_irq_in_use, PCI_NUM_MSI);
पूर्ण;

काष्ठा mobiveil_pcie;

काष्ठा mobiveil_rp_ops अणु
	पूर्णांक (*पूर्णांकerrupt_init)(काष्ठा mobiveil_pcie *pcie);
पूर्ण;

काष्ठा mobiveil_root_port अणु
	व्योम __iomem *config_axi_slave_base;	/* endpoपूर्णांक config base */
	काष्ठा resource *ob_io_res;
	काष्ठा mobiveil_rp_ops *ops;
	पूर्णांक irq;
	raw_spinlock_t पूर्णांकx_mask_lock;
	काष्ठा irq_करोमुख्य *पूर्णांकx_करोमुख्य;
	काष्ठा mobiveil_msi msi;
	काष्ठा pci_host_bridge *bridge;
पूर्ण;

काष्ठा mobiveil_pab_ops अणु
	पूर्णांक (*link_up)(काष्ठा mobiveil_pcie *pcie);
पूर्ण;

काष्ठा mobiveil_pcie अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *csr_axi_slave_base;	/* root port config base */
	व्योम __iomem *apb_csr_base;	/* MSI रेजिस्टर base */
	phys_addr_t pcie_reg_base;	/* Physical PCIe Controller Base */
	पूर्णांक apio_wins;
	पूर्णांक ppio_wins;
	पूर्णांक ob_wins_configured;		/* configured outbound winकरोws */
	पूर्णांक ib_wins_configured;		/* configured inbound winकरोws */
	स्थिर काष्ठा mobiveil_pab_ops *ops;
	काष्ठा mobiveil_root_port rp;
पूर्ण;

पूर्णांक mobiveil_pcie_host_probe(काष्ठा mobiveil_pcie *pcie);
पूर्णांक mobiveil_host_init(काष्ठा mobiveil_pcie *pcie, bool reinit);
bool mobiveil_pcie_link_up(काष्ठा mobiveil_pcie *pcie);
पूर्णांक mobiveil_bringup_link(काष्ठा mobiveil_pcie *pcie);
व्योम program_ob_winकरोws(काष्ठा mobiveil_pcie *pcie, पूर्णांक win_num, u64 cpu_addr,
			u64 pci_addr, u32 type, u64 size);
व्योम program_ib_winकरोws(काष्ठा mobiveil_pcie *pcie, पूर्णांक win_num, u64 cpu_addr,
			u64 pci_addr, u32 type, u64 size);
u32 mobiveil_csr_पढ़ो(काष्ठा mobiveil_pcie *pcie, u32 off, माप_प्रकार size);
व्योम mobiveil_csr_ग_लिखो(काष्ठा mobiveil_pcie *pcie, u32 val, u32 off,
			माप_प्रकार size);

अटल अंतरभूत u32 mobiveil_csr_पढ़ोl(काष्ठा mobiveil_pcie *pcie, u32 off)
अणु
	वापस mobiveil_csr_पढ़ो(pcie, off, 0x4);
पूर्ण

अटल अंतरभूत u16 mobiveil_csr_पढ़ोw(काष्ठा mobiveil_pcie *pcie, u32 off)
अणु
	वापस mobiveil_csr_पढ़ो(pcie, off, 0x2);
पूर्ण

अटल अंतरभूत u8 mobiveil_csr_पढ़ोb(काष्ठा mobiveil_pcie *pcie, u32 off)
अणु
	वापस mobiveil_csr_पढ़ो(pcie, off, 0x1);
पूर्ण


अटल अंतरभूत व्योम mobiveil_csr_ग_लिखोl(काष्ठा mobiveil_pcie *pcie, u32 val,
				       u32 off)
अणु
	mobiveil_csr_ग_लिखो(pcie, val, off, 0x4);
पूर्ण

अटल अंतरभूत व्योम mobiveil_csr_ग_लिखोw(काष्ठा mobiveil_pcie *pcie, u16 val,
				       u32 off)
अणु
	mobiveil_csr_ग_लिखो(pcie, val, off, 0x2);
पूर्ण

अटल अंतरभूत व्योम mobiveil_csr_ग_लिखोb(काष्ठा mobiveil_pcie *pcie, u8 val,
				       u32 off)
अणु
	mobiveil_csr_ग_लिखो(pcie, val, off, 0x1);
पूर्ण

#पूर्ण_अगर /* _PCIE_MOBIVEIL_H */
