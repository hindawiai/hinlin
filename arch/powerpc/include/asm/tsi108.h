<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * common routine and memory layout क्रम Tundra TSI108(Grendel) host bridge
 * memory controller.
 *
 * Author: Jacob Pan (jacob.pan@मुक्तscale.com)
 *	   Alex Bounine (alexandreb@tundra.com)
 *
 * Copyright 2004-2006 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __PPC_KERNEL_TSI108_H
#घोषणा __PPC_KERNEL_TSI108_H

#समावेश <यंत्र/pci-bridge.h>

/* Size of entire रेजिस्टर space */
#घोषणा TSI108_REG_SIZE		(0x10000)

/* Sizes of रेजिस्टर spaces क्रम inभागidual blocks */
#घोषणा TSI108_HLP_SIZE		0x1000
#घोषणा TSI108_PCI_SIZE		0x1000
#घोषणा TSI108_CLK_SIZE		0x1000
#घोषणा TSI108_PB_SIZE		0x1000
#घोषणा TSI108_SD_SIZE		0x1000
#घोषणा TSI108_DMA_SIZE		0x1000
#घोषणा TSI108_ETH_SIZE		0x1000
#घोषणा TSI108_I2C_SIZE		0x400
#घोषणा TSI108_MPIC_SIZE	0x400
#घोषणा TSI108_UART0_SIZE	0x200
#घोषणा TSI108_GPIO_SIZE	0x200
#घोषणा TSI108_UART1_SIZE	0x200

/* Offsets within Tsi108(A) CSR space क्रम inभागidual blocks */
#घोषणा TSI108_HLP_OFFSET	0x0000
#घोषणा TSI108_PCI_OFFSET	0x1000
#घोषणा TSI108_CLK_OFFSET	0x2000
#घोषणा TSI108_PB_OFFSET	0x3000
#घोषणा TSI108_SD_OFFSET	0x4000
#घोषणा TSI108_DMA_OFFSET	0x5000
#घोषणा TSI108_ETH_OFFSET	0x6000
#घोषणा TSI108_I2C_OFFSET	0x7000
#घोषणा TSI108_MPIC_OFFSET	0x7400
#घोषणा TSI108_UART0_OFFSET	0x7800
#घोषणा TSI108_GPIO_OFFSET	0x7A00
#घोषणा TSI108_UART1_OFFSET	0x7C00

/* Tsi108 रेजिस्टरs used by common code components */
#घोषणा TSI108_PCI_CSR		(0x004)
#घोषणा TSI108_PCI_IRP_CFG_CTL	(0x180)
#घोषणा TSI108_PCI_IRP_STAT	(0x184)
#घोषणा TSI108_PCI_IRP_ENABLE	(0x188)
#घोषणा TSI108_PCI_IRP_INTAD	(0x18C)

#घोषणा TSI108_PCI_IRP_STAT_P_INT	(0x00400000)
#घोषणा TSI108_PCI_IRP_ENABLE_P_INT	(0x00400000)

#घोषणा TSI108_CG_PWRUP_STATUS	(0x234)

#घोषणा TSI108_PB_ISR		(0x00C)
#घोषणा TSI108_PB_ERRCS		(0x404)
#घोषणा TSI108_PB_AERR		(0x408)

#घोषणा TSI108_PB_ERRCS_ES		(1 << 1)
#घोषणा TSI108_PB_ISR_PBS_RD_ERR	(1 << 8)

#घोषणा TSI108_PCI_CFG_SIZE		(0x01000000)

/*
 * PHY Configuration Options
 *
 * Specअगरy "bcm54xx" in the compatible property of your device tree phy
 * nodes अगर your board uses the Broadcom PHYs
 */
#घोषणा TSI108_PHY_MV88E	0	/* Marvel 88Exxxx PHY */
#घोषणा TSI108_PHY_BCM54XX	1	/* Broadcom BCM54xx PHY */

/* Global variables */

बाह्य u32 tsi108_pci_cfg_base;
/* Exported functions */

बाह्य पूर्णांक tsi108_direct_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				      पूर्णांक offset, पूर्णांक len, u32 val);
बाह्य पूर्णांक tsi108_direct_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक offset, पूर्णांक len, u32 * val);
बाह्य व्योम tsi108_clear_pci_error(u32 pci_cfg_base);

बाह्य phys_addr_t get_csrbase(व्योम);

प्रकार काष्ठा अणु
	u32 regs;		/* hw रेजिस्टरs base address */
	u32 phyregs;		/* phy रेजिस्टरs base address */
	u16 phy;		/* phy address */
	u16 irq_num;		/* irq number */
	u8 mac_addr[6];		/* phy mac address */
	u16 phy_type;	/* type of phy on board */
पूर्ण hw_info;

बाह्य u32 get_vir_csrbase(व्योम);
बाह्य u32 tsi108_csr_vir_base;

अटल अंतरभूत u32 tsi108_पढ़ो_reg(u32 reg_offset)
अणु
	वापस in_be32((अस्थिर u32 *)(tsi108_csr_vir_base + reg_offset));
पूर्ण

अटल अंतरभूत व्योम tsi108_ग_लिखो_reg(u32 reg_offset, u32 val)
अणु
	out_be32((अस्थिर u32 *)(tsi108_csr_vir_base + reg_offset), val);
पूर्ण

#पूर्ण_अगर				/* __PPC_KERNEL_TSI108_H */
