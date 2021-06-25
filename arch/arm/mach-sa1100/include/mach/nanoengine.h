<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-sa1100/include/mach/nanoengine.h
 *
 * This file contains the hardware specअगरic definitions क्रम nanoEngine.
 * Only include this file from SA1100-specअगरic files.
 *
 * Copyright (C) 2010 Marcelo Roberto Jimenez <mroberto@cpti.cetuc.puc-rio.br>
 */
#अगर_अघोषित __ASM_ARCH_न_अंकOENGINE_H
#घोषणा __ASM_ARCH_न_अंकOENGINE_H

#समावेश <mach/irqs.h>

#घोषणा GPIO_PC_READY0	11 /* पढ़ोy क्रम socket 0 (active high)*/
#घोषणा GPIO_PC_READY1	12 /* पढ़ोy क्रम socket 1 (active high) */
#घोषणा GPIO_PC_CD0	13 /* detect क्रम socket 0 (active low) */
#घोषणा GPIO_PC_CD1	14 /* detect क्रम socket 1 (active low) */
#घोषणा GPIO_PC_RESET0	15 /* reset socket 0 */
#घोषणा GPIO_PC_RESET1	16 /* reset socket 1 */

#घोषणा न_अंकOENGINE_IRQ_GPIO_PCI		IRQ_GPIO0
#घोषणा न_अंकOENGINE_IRQ_GPIO_PC_READY0	IRQ_GPIO11
#घोषणा न_अंकOENGINE_IRQ_GPIO_PC_READY1	IRQ_GPIO12
#घोषणा न_अंकOENGINE_IRQ_GPIO_PC_CD0	IRQ_GPIO13
#घोषणा न_अंकOENGINE_IRQ_GPIO_PC_CD1	IRQ_GPIO14

/*
 * nanoEngine Memory Map:
 *
 * 0000.0000 - 003F.0000 -   4 MB Flash
 * C000.0000 - C1FF.FFFF -  32 MB SDRAM
 * 1860.0000 - 186F.FFFF -   1 MB Internal PCI Memory Read/Write
 * 18A1.0000 - 18A1.FFFF -  64 KB Internal PCI Config Space
 * 4000.0000 - 47FF.FFFF - 128 MB External Bus I/O - Multiplexed Mode
 * 4800.0000 - 4FFF.FFFF - 128 MB External Bus I/O - Non-Multiplexed Mode
 *
 */

#घोषणा न_अंकO_PCI_MEM_RW_PHYS		0x18600000
#घोषणा न_अंकO_PCI_MEM_RW_VIRT		0xf1000000
#घोषणा न_अंकO_PCI_MEM_RW_SIZE		SZ_1M
#घोषणा न_अंकO_PCI_CONFIG_SPACE_PHYS	0x18A10000
#घोषणा न_अंकO_PCI_CONFIG_SPACE_VIRT	0xf2000000
#घोषणा न_अंकO_PCI_CONFIG_SPACE_SIZE	SZ_64K

#पूर्ण_अगर

