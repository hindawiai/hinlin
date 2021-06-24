<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/pcie.h
 *
 * Marvell Orion SoC PCIe handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_PCIE_H
#घोषणा __PLAT_PCIE_H

काष्ठा pci_bus;

u32 orion_pcie_dev_id(व्योम __iomem *base);
u32 orion_pcie_rev(व्योम __iomem *base);
पूर्णांक orion_pcie_link_up(व्योम __iomem *base);
पूर्णांक orion_pcie_x4_mode(व्योम __iomem *base);
पूर्णांक orion_pcie_get_local_bus_nr(व्योम __iomem *base);
व्योम orion_pcie_set_local_bus_nr(व्योम __iomem *base, पूर्णांक nr);
व्योम orion_pcie_reset(व्योम __iomem *base);
व्योम orion_pcie_setup(व्योम __iomem *base);
पूर्णांक orion_pcie_rd_conf(व्योम __iomem *base, काष्ठा pci_bus *bus,
		       u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक orion_pcie_rd_conf_tlp(व्योम __iomem *base, काष्ठा pci_bus *bus,
			   u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक orion_pcie_rd_conf_wa(व्योम __iomem *wa_base, काष्ठा pci_bus *bus,
			  u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val);
पूर्णांक orion_pcie_wr_conf(व्योम __iomem *base, काष्ठा pci_bus *bus,
		       u32 devfn, पूर्णांक where, पूर्णांक size, u32 val);


#पूर्ण_अगर
