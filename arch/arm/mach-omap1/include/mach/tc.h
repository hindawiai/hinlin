<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * arch/arm/plat-omap/include/mach/tc.h
 *
 * OMAP Traffic Controller
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#अगर_अघोषित __ASM_ARCH_TC_H
#घोषणा __ASM_ARCH_TC_H

#घोषणा TCMIF_BASE		0xfffecc00
#घोषणा OMAP_TC_OCPT1_PRIOR	(TCMIF_BASE + 0x00)
#घोषणा OMAP_TC_EMIFS_PRIOR	(TCMIF_BASE + 0x04)
#घोषणा OMAP_TC_EMIFF_PRIOR	(TCMIF_BASE + 0x08)
#घोषणा EMIFS_CONFIG		(TCMIF_BASE + 0x0c)
#घोषणा EMIFS_CS0_CONFIG	(TCMIF_BASE + 0x10)
#घोषणा EMIFS_CS1_CONFIG	(TCMIF_BASE + 0x14)
#घोषणा EMIFS_CS2_CONFIG	(TCMIF_BASE + 0x18)
#घोषणा EMIFS_CS3_CONFIG	(TCMIF_BASE + 0x1c)
#घोषणा EMIFF_SDRAM_CONFIG	(TCMIF_BASE + 0x20)
#घोषणा EMIFF_MRS		(TCMIF_BASE + 0x24)
#घोषणा TC_TIMEOUT1		(TCMIF_BASE + 0x28)
#घोषणा TC_TIMEOUT2		(TCMIF_BASE + 0x2c)
#घोषणा TC_TIMEOUT3		(TCMIF_BASE + 0x30)
#घोषणा TC_ENDIANISM		(TCMIF_BASE + 0x34)
#घोषणा EMIFF_SDRAM_CONFIG_2	(TCMIF_BASE + 0x3c)
#घोषणा EMIF_CFG_DYNAMIC_WS	(TCMIF_BASE + 0x40)
#घोषणा EMIFS_ACS0		(TCMIF_BASE + 0x50)
#घोषणा EMIFS_ACS1		(TCMIF_BASE + 0x54)
#घोषणा EMIFS_ACS2		(TCMIF_BASE + 0x58)
#घोषणा EMIFS_ACS3		(TCMIF_BASE + 0x5c)
#घोषणा OMAP_TC_OCPT2_PRIOR	(TCMIF_BASE + 0xd0)

/* बाह्यal EMIFS chipselect regions */
#घोषणा	OMAP_CS0_PHYS		0x00000000
#घोषणा	OMAP_CS0_SIZE		SZ_64M

#घोषणा	OMAP_CS1_PHYS		0x04000000
#घोषणा	OMAP_CS1_SIZE		SZ_64M

#घोषणा	OMAP_CS1A_PHYS		OMAP_CS1_PHYS
#घोषणा	OMAP_CS1A_SIZE		SZ_32M

#घोषणा	OMAP_CS1B_PHYS		(OMAP_CS1A_PHYS + OMAP_CS1A_SIZE)
#घोषणा	OMAP_CS1B_SIZE		SZ_32M

#घोषणा	OMAP_CS2_PHYS		0x08000000
#घोषणा	OMAP_CS2_SIZE		SZ_64M

#घोषणा	OMAP_CS2A_PHYS		OMAP_CS2_PHYS
#घोषणा	OMAP_CS2A_SIZE		SZ_32M

#घोषणा	OMAP_CS2B_PHYS		(OMAP_CS2A_PHYS + OMAP_CS2A_SIZE)
#घोषणा	OMAP_CS2B_SIZE		SZ_32M

#घोषणा	OMAP_CS3_PHYS		0x0c000000
#घोषणा	OMAP_CS3_SIZE		SZ_64M

#अगर_अघोषित	__ASSEMBLER__

/* EMIF Slow Interface Configuration Register */
#घोषणा OMAP_EMIFS_CONFIG_FR		(1 << 4)
#घोषणा OMAP_EMIFS_CONFIG_PDE		(1 << 3)
#घोषणा OMAP_EMIFS_CONFIG_PWD_EN	(1 << 2)
#घोषणा OMAP_EMIFS_CONFIG_BM		(1 << 1)
#घोषणा OMAP_EMIFS_CONFIG_WP		(1 << 0)

#घोषणा EMIFS_CCS(n)		(EMIFS_CS0_CONFIG + (4 * (n)))
#घोषणा EMIFS_ACS(n)		(EMIFS_ACS0 + (4 * (n)))

#पूर्ण_अगर	/* __ASSEMBLER__ */

#पूर्ण_अगर	/* __ASM_ARCH_TC_H */
