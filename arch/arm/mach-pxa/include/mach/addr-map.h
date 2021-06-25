<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_ADDR_MAP_H
#घोषणा __ASM_MACH_ADDR_MAP_H

/*
 * Chip Selects
 */
#घोषणा PXA_CS0_PHYS		0x00000000
#घोषणा PXA_CS1_PHYS		0x04000000
#घोषणा PXA_CS2_PHYS		0x08000000
#घोषणा PXA_CS3_PHYS		0x0C000000
#घोषणा PXA_CS4_PHYS		0x10000000
#घोषणा PXA_CS5_PHYS		0x14000000

#घोषणा PXA300_CS0_PHYS		0x00000000	/* PXA300/PXA310 _only_ */
#घोषणा PXA300_CS1_PHYS		0x30000000	/* PXA300/PXA310 _only_ */
#घोषणा PXA3xx_CS2_PHYS		0x10000000
#घोषणा PXA3xx_CS3_PHYS		0x14000000

/*
 * Peripheral Bus
 */
#घोषणा PERIPH_PHYS		0x40000000
#घोषणा PERIPH_VIRT		IOMEM(0xf2000000)
#घोषणा PERIPH_SIZE		0x02000000

/*
 * Static Memory Controller (w/ SDRAM controls on PXA25x/PXA27x)
 */
#घोषणा PXA2XX_SMEMC_PHYS	0x48000000
#घोषणा PXA3XX_SMEMC_PHYS	0x4a000000
#घोषणा SMEMC_VIRT		IOMEM(0xf6000000)
#घोषणा SMEMC_SIZE		0x00100000

/*
 * Dynamic Memory Controller (only on PXA3xx)
 */
#घोषणा DMEMC_PHYS		0x48100000
#घोषणा DMEMC_VIRT		IOMEM(0xf6100000)
#घोषणा DMEMC_SIZE		0x00100000

/*
 * Reserved space क्रम low level debug भव addresses within
 * 0xf6200000..0xf6201000
 */

/*
 * DFI Bus क्रम न_अंकD, PXA3xx only
 */
#घोषणा न_अंकD_PHYS		0x43100000
#घोषणा न_अंकD_VIRT		IOMEM(0xf6300000)
#घोषणा न_अंकD_SIZE		0x00100000

/*
 * Internal Memory Controller (PXA27x and later)
 */
#घोषणा IMEMC_PHYS		0x58000000
#घोषणा IMEMC_VIRT		IOMEM(0xfe000000)
#घोषणा IMEMC_SIZE		0x00100000

#पूर्ण_अगर /* __ASM_MACH_ADDR_MAP_H */
