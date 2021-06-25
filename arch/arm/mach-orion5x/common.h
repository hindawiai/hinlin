<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_ORION5X_COMMON_H
#घोषणा __ARCH_ORION5X_COMMON_H

#समावेश <linux/reboot.h>

काष्ठा dsa_chip_data;
काष्ठा mv643xx_eth_platक्रमm_data;
काष्ठा mv_sata_platक्रमm_data;

#घोषणा ORION_MBUS_PCIE_MEM_TARGET    0x04
#घोषणा ORION_MBUS_PCIE_MEM_ATTR      0x59
#घोषणा ORION_MBUS_PCIE_IO_TARGET     0x04
#घोषणा ORION_MBUS_PCIE_IO_ATTR       0x51
#घोषणा ORION_MBUS_PCIE_WA_TARGET     0x04
#घोषणा ORION_MBUS_PCIE_WA_ATTR       0x79
#घोषणा ORION_MBUS_PCI_MEM_TARGET     0x03
#घोषणा ORION_MBUS_PCI_MEM_ATTR       0x59
#घोषणा ORION_MBUS_PCI_IO_TARGET      0x03
#घोषणा ORION_MBUS_PCI_IO_ATTR        0x51
#घोषणा ORION_MBUS_DEVBUS_BOOT_TARGET 0x01
#घोषणा ORION_MBUS_DEVBUS_BOOT_ATTR   0x0f
#घोषणा ORION_MBUS_DEVBUS_TARGET(cs)  0x01
#घोषणा ORION_MBUS_DEVBUS_ATTR(cs)    (~(1 << cs))
#घोषणा ORION_MBUS_SRAM_TARGET        0x09
#घोषणा ORION_MBUS_SRAM_ATTR          0x00

/*
 * Basic Orion init functions used early by machine-setup.
 */
व्योम orion5x_map_io(व्योम);
व्योम orion5x_init_early(व्योम);
व्योम orion5x_init_irq(व्योम);
व्योम orion5x_init(व्योम);
व्योम orion5x_id(u32 *dev, u32 *rev, अक्षर **dev_name);
व्योम clk_init(व्योम);
बाह्य पूर्णांक orion5x_tclk;
बाह्य व्योम orion5x_समयr_init(व्योम);

व्योम orion5x_setup_wins(व्योम);

व्योम orion5x_ehci0_init(व्योम);
व्योम orion5x_ehci1_init(व्योम);
व्योम orion5x_eth_init(काष्ठा mv643xx_eth_platक्रमm_data *eth_data);
व्योम orion5x_eth_चयन_init(काष्ठा dsa_chip_data *d);
व्योम orion5x_i2c_init(व्योम);
व्योम orion5x_sata_init(काष्ठा mv_sata_platक्रमm_data *sata_data);
व्योम orion5x_spi_init(व्योम);
व्योम orion5x_uart0_init(व्योम);
व्योम orion5x_uart1_init(व्योम);
व्योम orion5x_xor_init(व्योम);
व्योम orion5x_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

/*
 * PCIe/PCI functions.
 */
काष्ठा pci_bus;
काष्ठा pci_host_bridge;
काष्ठा pci_sys_data;
काष्ठा pci_dev;

व्योम orion5x_pcie_id(u32 *dev, u32 *rev);
व्योम orion5x_pci_disable(व्योम);
व्योम orion5x_pci_set_cardbus_mode(व्योम);
पूर्णांक orion5x_pci_sys_setup(पूर्णांक nr, काष्ठा pci_sys_data *sys);
पूर्णांक orion5x_pci_sys_scan_bus(पूर्णांक nr, काष्ठा pci_host_bridge *bridge);
पूर्णांक orion5x_pci_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);

काष्ठा tag;
बाह्य व्योम __init tag_fixup_mem32(काष्ठा tag *, अक्षर **);

#अगर_घोषित CONFIG_MACH_MSS2_DT
बाह्य व्योम mss2_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mss2_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*****************************************************************************
 * Helpers to access Orion रेजिस्टरs
 ****************************************************************************/
/*
 * These are not preempt-safe.  Locks, अगर needed, must be taken
 * care of by the caller.
 */
#घोषणा orion5x_setbits(r, mask)	ग_लिखोl(पढ़ोl(r) | (mask), (r))
#घोषणा orion5x_clrbits(r, mask)	ग_लिखोl(पढ़ोl(r) & ~(mask), (r))

#पूर्ण_अगर
