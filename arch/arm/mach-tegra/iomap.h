<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 *	Erik Gilling <konkers@google.com>
 */

#अगर_अघोषित __MACH_TEGRA_IOMAP_H
#घोषणा __MACH_TEGRA_IOMAP_H

#समावेश <linux/pgtable.h>
#समावेश <linux/sizes.h>

#घोषणा TEGRA_IRAM_BASE			0x40000000
#घोषणा TEGRA_IRAM_SIZE			SZ_256K

#घोषणा TEGRA_ARM_PERIF_BASE		0x50040000
#घोषणा TEGRA_ARM_PERIF_SIZE		SZ_8K

#घोषणा TEGRA_ARM_INT_DIST_BASE		0x50041000
#घोषणा TEGRA_ARM_INT_DIST_SIZE		SZ_4K

#घोषणा TEGRA_TMR1_BASE			0x60005000
#घोषणा TEGRA_TMR1_SIZE			SZ_8

#घोषणा TEGRA_TMR2_BASE			0x60005008
#घोषणा TEGRA_TMR2_SIZE			SZ_8

#घोषणा TEGRA_TMRUS_BASE		0x60005010
#घोषणा TEGRA_TMRUS_SIZE		SZ_64

#घोषणा TEGRA_TMR3_BASE			0x60005050
#घोषणा TEGRA_TMR3_SIZE			SZ_8

#घोषणा TEGRA_TMR4_BASE			0x60005058
#घोषणा TEGRA_TMR4_SIZE			SZ_8

#घोषणा TEGRA_CLK_RESET_BASE		0x60006000
#घोषणा TEGRA_CLK_RESET_SIZE		SZ_4K

#घोषणा TEGRA_FLOW_CTRL_BASE		0x60007000
#घोषणा TEGRA_FLOW_CTRL_SIZE		20

#घोषणा TEGRA_SB_BASE			0x6000C200
#घोषणा TEGRA_SB_SIZE			256

#घोषणा TEGRA_EXCEPTION_VECTORS_BASE    0x6000F000
#घोषणा TEGRA_EXCEPTION_VECTORS_SIZE    SZ_4K

#घोषणा TEGRA_APB_MISC_BASE		0x70000000
#घोषणा TEGRA_APB_MISC_SIZE		SZ_4K

#घोषणा TEGRA_UARTA_BASE		0x70006000
#घोषणा TEGRA_UARTA_SIZE		SZ_64

#घोषणा TEGRA_UARTB_BASE		0x70006040
#घोषणा TEGRA_UARTB_SIZE		SZ_64

#घोषणा TEGRA_UARTC_BASE		0x70006200
#घोषणा TEGRA_UARTC_SIZE		SZ_256

#घोषणा TEGRA_UARTD_BASE		0x70006300
#घोषणा TEGRA_UARTD_SIZE		SZ_256

#घोषणा TEGRA_UARTE_BASE		0x70006400
#घोषणा TEGRA_UARTE_SIZE		SZ_256

#घोषणा TEGRA_PMC_BASE			0x7000E400
#घोषणा TEGRA_PMC_SIZE			SZ_256

#घोषणा TEGRA_EMC_BASE			0x7000F400
#घोषणा TEGRA_EMC_SIZE			SZ_1K

#घोषणा TEGRA_EMC0_BASE			0x7001A000
#घोषणा TEGRA_EMC0_SIZE			SZ_2K

#घोषणा TEGRA_EMC1_BASE			0x7001A800
#घोषणा TEGRA_EMC1_SIZE			SZ_2K

#घोषणा TEGRA124_EMC_BASE		0x7001B000
#घोषणा TEGRA124_EMC_SIZE		SZ_2K

#घोषणा TEGRA_CSITE_BASE		0x70040000
#घोषणा TEGRA_CSITE_SIZE		SZ_256K

/* On TEGRA, many peripherals are very बंदly packed in
 * two 256MB io winकरोws (that actually only use about 64KB
 * at the start of each).
 *
 * We will just map the first MMU section of each winकरोw (to minimize
 * pt entries needed) and provide a macro to transक्रमm physical
 * io addresses to an appropriate व्योम __iomem *.
 */

#घोषणा IO_IRAM_PHYS	0x40000000
#घोषणा IO_IRAM_VIRT	IOMEM(0xFE400000)
#घोषणा IO_IRAM_SIZE	SZ_256K

#घोषणा IO_CPU_PHYS	0x50040000
#घोषणा IO_CPU_VIRT	IOMEM(0xFE440000)
#घोषणा IO_CPU_SIZE	SZ_16K

#घोषणा IO_PPSB_PHYS	0x60000000
#घोषणा IO_PPSB_VIRT	IOMEM(0xFE200000)
#घोषणा IO_PPSB_SIZE	SECTION_SIZE

#घोषणा IO_APB_PHYS	0x70000000
#घोषणा IO_APB_VIRT	IOMEM(0xFE000000)
#घोषणा IO_APB_SIZE	SECTION_SIZE

#घोषणा IO_TO_VIRT_BETWEEN(p, st, sz)	((p) >= (st) && (p) < ((st) + (sz)))
#घोषणा IO_TO_VIRT_XLATE(p, pst, vst)	(((p) - (pst) + (vst)))

#घोषणा IO_TO_VIRT(n) ( \
	IO_TO_VIRT_BETWEEN((n), IO_PPSB_PHYS, IO_PPSB_SIZE) ?		\
		IO_TO_VIRT_XLATE((n), IO_PPSB_PHYS, IO_PPSB_VIRT) :	\
	IO_TO_VIRT_BETWEEN((n), IO_APB_PHYS, IO_APB_SIZE) ?		\
		IO_TO_VIRT_XLATE((n), IO_APB_PHYS, IO_APB_VIRT) :	\
	IO_TO_VIRT_BETWEEN((n), IO_CPU_PHYS, IO_CPU_SIZE) ?		\
		IO_TO_VIRT_XLATE((n), IO_CPU_PHYS, IO_CPU_VIRT) :	\
	IO_TO_VIRT_BETWEEN((n), IO_IRAM_PHYS, IO_IRAM_SIZE) ?		\
		IO_TO_VIRT_XLATE((n), IO_IRAM_PHYS, IO_IRAM_VIRT) :	\
	शून्य)

#घोषणा IO_ADDRESS(n) (IO_TO_VIRT(n))

#पूर्ण_अगर
