<शैली गुरु>
/*
 * Generic definitions क्रम Marvell MV78xx0 SoC flavors:
 *  MV781x0 and MV782x0.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __ASM_ARCH_MV78XX0_H
#घोषणा __ASM_ARCH_MV78XX0_H

#समावेश "irqs.h"

/*
 * Marvell MV78xx0 address maps.
 *
 * phys
 * c0000000	PCIe Memory space
 * f0800000	PCIe #0 I/O space
 * f0900000	PCIe #1 I/O space
 * f0a00000	PCIe #2 I/O space
 * f0b00000	PCIe #3 I/O space
 * f0c00000	PCIe #4 I/O space
 * f0d00000	PCIe #5 I/O space
 * f0e00000	PCIe #6 I/O space
 * f0f00000	PCIe #7 I/O space
 * f1000000	on-chip peripheral रेजिस्टरs
 *
 * virt		phys		size
 * fe400000	f102x000	16K	core-specअगरic peripheral रेजिस्टरs
 * fee00000	f0800000	64K	PCIe #0 I/O space
 * fee10000	f0900000	64K	PCIe #1 I/O space
 * fee20000	f0a00000	64K	PCIe #2 I/O space
 * fee30000	f0b00000	64K	PCIe #3 I/O space
 * fee40000	f0c00000	64K	PCIe #4 I/O space
 * fee50000	f0d00000	64K	PCIe #5 I/O space
 * fee60000	f0e00000	64K	PCIe #6 I/O space
 * fee70000	f0f00000	64K	PCIe #7 I/O space
 * fec00000	f1000000	1M	on-chip peripheral रेजिस्टरs
 */
#घोषणा MV78XX0_CORE0_REGS_PHYS_BASE	0xf1020000
#घोषणा MV78XX0_CORE1_REGS_PHYS_BASE	0xf1024000
#घोषणा MV78XX0_CORE_REGS_VIRT_BASE	IOMEM(0xfe400000)
#घोषणा MV78XX0_CORE_REGS_PHYS_BASE	0xfe400000
#घोषणा MV78XX0_CORE_REGS_SIZE		SZ_16K

#घोषणा MV78XX0_PCIE_IO_PHYS_BASE(i)	(0xf0800000 + ((i) << 20))
#घोषणा MV78XX0_PCIE_IO_SIZE		SZ_1M

#घोषणा MV78XX0_REGS_PHYS_BASE		0xf1000000
#घोषणा MV78XX0_REGS_VIRT_BASE		IOMEM(0xfec00000)
#घोषणा MV78XX0_REGS_SIZE		SZ_1M

#घोषणा MV78XX0_PCIE_MEM_PHYS_BASE	0xc0000000
#घोषणा MV78XX0_PCIE_MEM_SIZE		0x30000000

/*
 * Core-specअगरic peripheral रेजिस्टरs.
 */
#घोषणा BRIDGE_VIRT_BASE	(MV78XX0_CORE_REGS_VIRT_BASE)
#घोषणा BRIDGE_PHYS_BASE	(MV78XX0_CORE_REGS_PHYS_BASE)
#घोषणा  BRIDGE_WINS_CPU0_BASE  (MV78XX0_CORE0_REGS_PHYS_BASE)
#घोषणा  BRIDGE_WINS_CPU1_BASE  (MV78XX0_CORE1_REGS_PHYS_BASE)
#घोषणा  BRIDGE_WINS_SZ         (0xA000)

/*
 * Register Map
 */
#घोषणा DDR_VIRT_BASE		(MV78XX0_REGS_VIRT_BASE + 0x00000)
#घोषणा DDR_PHYS_BASE           (MV78XX0_REGS_PHYS_BASE + 0x00000)
#घोषणा  DDR_WINDOW_CPU0_BASE	(DDR_PHYS_BASE + 0x1500)
#घोषणा  DDR_WINDOW_CPU1_BASE	(DDR_PHYS_BASE + 0x1570)
#घोषणा  DDR_WINDOW_CPU_SZ      (0x20)

#घोषणा DEV_BUS_PHYS_BASE	(MV78XX0_REGS_PHYS_BASE + 0x10000)
#घोषणा DEV_BUS_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x10000)
#घोषणा  SAMPLE_AT_RESET_LOW	(DEV_BUS_VIRT_BASE + 0x0030)
#घोषणा  SAMPLE_AT_RESET_HIGH	(DEV_BUS_VIRT_BASE + 0x0034)
#घोषणा  GPIO_VIRT_BASE		(DEV_BUS_VIRT_BASE + 0x0100)
#घोषणा  I2C_0_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x1000)
#घोषणा  I2C_1_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x1100)
#घोषणा  UART0_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x2000)
#घोषणा  UART0_VIRT_BASE	(DEV_BUS_VIRT_BASE + 0x2000)
#घोषणा  UART1_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x2100)
#घोषणा  UART1_VIRT_BASE	(DEV_BUS_VIRT_BASE + 0x2100)
#घोषणा  UART2_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x2200)
#घोषणा  UART2_VIRT_BASE	(DEV_BUS_VIRT_BASE + 0x2200)
#घोषणा  UART3_PHYS_BASE	(DEV_BUS_PHYS_BASE + 0x2300)
#घोषणा  UART3_VIRT_BASE	(DEV_BUS_VIRT_BASE + 0x2300)

#घोषणा GE10_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x30000)
#घोषणा GE11_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x34000)

#घोषणा PCIE00_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x40000)
#घोषणा PCIE01_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x44000)
#घोषणा PCIE02_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x48000)
#घोषणा PCIE03_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x4c000)

#घोषणा USB0_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x50000)
#घोषणा USB1_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x51000)
#घोषणा USB2_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x52000)

#घोषणा GE00_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x70000)
#घोषणा GE01_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0x74000)

#घोषणा PCIE10_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x80000)
#घोषणा PCIE11_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x84000)
#घोषणा PCIE12_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x88000)
#घोषणा PCIE13_VIRT_BASE	(MV78XX0_REGS_VIRT_BASE + 0x8c000)

#घोषणा SATA_PHYS_BASE		(MV78XX0_REGS_PHYS_BASE + 0xa0000)

/*
 * Supported devices and revisions.
 */
#घोषणा MV78X00_Z0_DEV_ID	0x6381
#घोषणा MV78X00_REV_Z0		1

#घोषणा MV78100_DEV_ID		0x7810
#घोषणा MV78100_REV_A0		1
#घोषणा MV78100_REV_A1		2

#घोषणा MV78200_DEV_ID		0x7820
#घोषणा MV78200_REV_A0		1

#पूर्ण_अगर
