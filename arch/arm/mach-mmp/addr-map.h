<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *   Common address map definitions
 */

#अगर_अघोषित __ASM_MACH_ADDR_MAP_H
#घोषणा __ASM_MACH_ADDR_MAP_H

/* APB - Application Subप्रणाली Peripheral Bus
 *
 * NOTE: the DMA controller रेजिस्टरs are actually on the AXI fabric #1
 * slave port to AHB/APB bridge, due to its बंद relationship to those
 * peripherals on APB, let's count it पूर्णांकo the ABP mapping area.
 */
#घोषणा APB_PHYS_BASE		0xd4000000
#घोषणा APB_VIRT_BASE		IOMEM(0xfe000000)
#घोषणा APB_PHYS_SIZE		0x00200000

#घोषणा AXI_PHYS_BASE		0xd4200000
#घोषणा AXI_VIRT_BASE		IOMEM(0xfe200000)
#घोषणा AXI_PHYS_SIZE		0x00200000

#घोषणा PGU_PHYS_BASE		0xe0000000
#घोषणा PGU_VIRT_BASE		IOMEM(0xfe400000)
#घोषणा PGU_PHYS_SIZE		0x00100000

/* Static Memory Controller - Chip Select 0 and 1 */
#घोषणा SMC_CS0_PHYS_BASE	0x80000000
#घोषणा SMC_CS0_PHYS_SIZE	0x10000000
#घोषणा SMC_CS1_PHYS_BASE	0x90000000
#घोषणा SMC_CS1_PHYS_SIZE	0x10000000

#घोषणा APMU_VIRT_BASE		(AXI_VIRT_BASE + 0x82800)
#घोषणा APMU_REG(x)		(APMU_VIRT_BASE + (x))

#घोषणा APBC_VIRT_BASE		(APB_VIRT_BASE + 0x015000)
#घोषणा APBC_REG(x)		(APBC_VIRT_BASE + (x))

#घोषणा MPMU_VIRT_BASE		(APB_VIRT_BASE + 0x50000)
#घोषणा MPMU_REG(x)		(MPMU_VIRT_BASE + (x))

#घोषणा CIU_VIRT_BASE		(AXI_VIRT_BASE + 0x82c00)
#घोषणा CIU_REG(x)		(CIU_VIRT_BASE + (x))

#घोषणा SCU_VIRT_BASE		(PGU_VIRT_BASE)
#घोषणा SCU_REG(x)		(SCU_VIRT_BASE + (x))

#पूर्ण_अगर /* __ASM_MACH_ADDR_MAP_H */
