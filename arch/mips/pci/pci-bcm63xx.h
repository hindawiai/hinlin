<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PCI_BCM63XX_H_
#घोषणा PCI_BCM63XX_H_

#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_dev_pci.h>

/*
 * Cardbus shares  the PCI bus, but has	 no IDSEL, so a	 special id is
 * reserved क्रम it.  If you have a standard PCI device at this id, you
 * need to change the following definition.
 */
#घोषणा CARDBUS_PCI_IDSEL	0x8


#घोषणा PCIE_BUS_BRIDGE		0
#घोषणा PCIE_BUS_DEVICE		1

/*
 * defined in ops-bcm63xx.c
 */
बाह्य काष्ठा pci_ops bcm63xx_pci_ops;
बाह्य काष्ठा pci_ops bcm63xx_cb_ops;
बाह्य काष्ठा pci_ops bcm63xx_pcie_ops;

/*
 * defined in pci-bcm63xx.c
 */
बाह्य व्योम __iomem *pci_iospace_start;

#पूर्ण_अगर /* ! PCI_BCM63XX_H_ */
