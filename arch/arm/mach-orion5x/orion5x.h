<शैली गुरु>
/*
 * Generic definitions of Orion SoC flavors:
 *  Orion-1, Orion-VoIP, Orion-NAS, Orion-2, and Orion-1-90.
 *
 * Maपूर्णांकainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_ORION5X_H
#घोषणा __ASM_ARCH_ORION5X_H

#समावेश "irqs.h"

/*****************************************************************************
 * Orion Address Maps
 *
 * phys
 * e0000000	PCIe MEM space
 * e8000000	PCI MEM space
 * f0000000	PCIe WA space (Orion-1/Orion-NAS only)
 * f1000000	on-chip peripheral रेजिस्टरs
 * f2000000	PCIe I/O space
 * f2100000	PCI I/O space
 * f2200000	SRAM dedicated क्रम the crypto unit
 * f4000000	device bus mappings (boot)
 * fa000000	device bus mappings (cs0)
 * fa800000	device bus mappings (cs2)
 * fc000000	device bus mappings (cs0/cs1)
 *
 * virt		phys		size
 * fec00000	f1000000	1M	on-chip peripheral रेजिस्टरs
 * fee00000	f2000000	64K	PCIe I/O space
 * fee10000	f2100000	64K	PCI I/O space
 * fd000000	f0000000	16M	PCIe WA space (Orion-1/Orion-NAS only)
 ****************************************************************************/
#घोषणा ORION5X_REGS_PHYS_BASE		0xf1000000
#घोषणा ORION5X_REGS_VIRT_BASE		IOMEM(0xfec00000)
#घोषणा ORION5X_REGS_SIZE		SZ_1M

#घोषणा ORION5X_PCIE_IO_PHYS_BASE	0xf2000000
#घोषणा ORION5X_PCIE_IO_BUS_BASE	0x00000000
#घोषणा ORION5X_PCIE_IO_SIZE		SZ_64K

#घोषणा ORION5X_PCI_IO_PHYS_BASE	0xf2100000
#घोषणा ORION5X_PCI_IO_BUS_BASE		0x00010000
#घोषणा ORION5X_PCI_IO_SIZE		SZ_64K

#घोषणा ORION5X_SRAM_PHYS_BASE		(0xf2200000)
#घोषणा ORION5X_SRAM_SIZE		SZ_8K

/* Relevant only क्रम Orion-1/Orion-NAS */
#घोषणा ORION5X_PCIE_WA_PHYS_BASE	0xf0000000
#घोषणा ORION5X_PCIE_WA_VIRT_BASE	IOMEM(0xfd000000)
#घोषणा ORION5X_PCIE_WA_SIZE		SZ_16M

#घोषणा ORION5X_PCIE_MEM_PHYS_BASE	0xe0000000
#घोषणा ORION5X_PCIE_MEM_SIZE		SZ_128M

#घोषणा ORION5X_PCI_MEM_PHYS_BASE	0xe8000000
#घोषणा ORION5X_PCI_MEM_SIZE		SZ_128M

/*******************************************************************************
 * Orion Registers Map
 ******************************************************************************/

#घोषणा ORION5X_DDR_PHYS_BASE           (ORION5X_REGS_PHYS_BASE + 0x00000)
#घोषणा  ORION5X_DDR_WINS_BASE          (ORION5X_DDR_PHYS_BASE + 0x1500)
#घोषणा  ORION5X_DDR_WINS_SZ            (0x10)
#घोषणा ORION5X_DDR_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x00000)
#घोषणा ORION5X_DEV_BUS_PHYS_BASE	(ORION5X_REGS_PHYS_BASE + 0x10000)
#घोषणा ORION5X_DEV_BUS_VIRT_BASE	(ORION5X_REGS_VIRT_BASE + 0x10000)
#घोषणा ORION5X_DEV_BUS_REG(x)		(ORION5X_DEV_BUS_VIRT_BASE + (x))
#घोषणा  GPIO_VIRT_BASE			ORION5X_DEV_BUS_REG(0x0100)
#घोषणा  SPI_PHYS_BASE			(ORION5X_DEV_BUS_PHYS_BASE + 0x0600)
#घोषणा  I2C_PHYS_BASE			(ORION5X_DEV_BUS_PHYS_BASE + 0x1000)
#घोषणा  UART0_PHYS_BASE		(ORION5X_DEV_BUS_PHYS_BASE + 0x2000)
#घोषणा  UART0_VIRT_BASE		(ORION5X_DEV_BUS_VIRT_BASE + 0x2000)
#घोषणा  UART1_PHYS_BASE		(ORION5X_DEV_BUS_PHYS_BASE + 0x2100)
#घोषणा  UART1_VIRT_BASE		(ORION5X_DEV_BUS_VIRT_BASE + 0x2100)

#घोषणा ORION5X_BRIDGE_VIRT_BASE	(ORION5X_REGS_VIRT_BASE + 0x20000)
#घोषणा ORION5X_BRIDGE_PHYS_BASE	(ORION5X_REGS_PHYS_BASE + 0x20000)
#घोषणा  ORION5X_BRIDGE_WINS_BASE       (ORION5X_BRIDGE_PHYS_BASE)
#घोषणा  ORION5X_BRIDGE_WINS_SZ         (0x80)

#घोषणा ORION5X_PCI_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x30000)

#घोषणा ORION5X_PCIE_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x40000)

#घोषणा ORION5X_USB0_PHYS_BASE		(ORION5X_REGS_PHYS_BASE + 0x50000)
#घोषणा ORION5X_USB0_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x50000)

#घोषणा ORION5X_XOR_PHYS_BASE		(ORION5X_REGS_PHYS_BASE + 0x60900)
#घोषणा ORION5X_XOR_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x60900)

#घोषणा ORION5X_ETH_PHYS_BASE		(ORION5X_REGS_PHYS_BASE + 0x70000)
#घोषणा ORION5X_ETH_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x70000)

#घोषणा ORION5X_SATA_PHYS_BASE		(ORION5X_REGS_PHYS_BASE + 0x80000)
#घोषणा ORION5X_SATA_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0x80000)

#घोषणा ORION5X_CRYPTO_PHYS_BASE	(ORION5X_REGS_PHYS_BASE + 0x90000)

#घोषणा ORION5X_USB1_PHYS_BASE		(ORION5X_REGS_PHYS_BASE + 0xa0000)
#घोषणा ORION5X_USB1_VIRT_BASE		(ORION5X_REGS_VIRT_BASE + 0xa0000)

/*******************************************************************************
 * Device Bus Registers
 ******************************************************************************/
#घोषणा MPP_0_7_CTRL		ORION5X_DEV_BUS_REG(0x000)
#घोषणा MPP_8_15_CTRL		ORION5X_DEV_BUS_REG(0x004)
#घोषणा MPP_16_19_CTRL		ORION5X_DEV_BUS_REG(0x050)
#घोषणा MPP_DEV_CTRL		ORION5X_DEV_BUS_REG(0x008)
#घोषणा MPP_RESET_SAMPLE	ORION5X_DEV_BUS_REG(0x010)
#घोषणा DEV_BANK_0_PARAM	ORION5X_DEV_BUS_REG(0x45c)
#घोषणा DEV_BANK_1_PARAM	ORION5X_DEV_BUS_REG(0x460)
#घोषणा DEV_BANK_2_PARAM	ORION5X_DEV_BUS_REG(0x464)
#घोषणा DEV_BANK_BOOT_PARAM	ORION5X_DEV_BUS_REG(0x46c)
#घोषणा DEV_BUS_CTRL		ORION5X_DEV_BUS_REG(0x4c0)
#घोषणा DEV_BUS_INT_CAUSE	ORION5X_DEV_BUS_REG(0x4d0)
#घोषणा DEV_BUS_INT_MASK	ORION5X_DEV_BUS_REG(0x4d4)

/*******************************************************************************
 * Supported Devices & Revisions
 ******************************************************************************/
/* Orion-1 (88F5181) and Orion-VoIP (88F5181L) */
#घोषणा MV88F5181_DEV_ID	0x5181
#घोषणा MV88F5181_REV_B1	3
#घोषणा MV88F5181L_REV_A0	8
#घोषणा MV88F5181L_REV_A1	9
/* Orion-NAS (88F5182) */
#घोषणा MV88F5182_DEV_ID	0x5182
#घोषणा MV88F5182_REV_A2	2
/* Orion-2 (88F5281) */
#घोषणा MV88F5281_DEV_ID	0x5281
#घोषणा MV88F5281_REV_D0	4
#घोषणा MV88F5281_REV_D1	5
#घोषणा MV88F5281_REV_D2	6
/* Orion-1-90 (88F6183) */
#घोषणा MV88F6183_DEV_ID	0x6183
#घोषणा MV88F6183_REV_B0	3

#पूर्ण_अगर
