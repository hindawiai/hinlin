<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-footbridge/include/mach/hardware.h
 *
 *  Copyright (C) 1998-1999 Russell King.
 *
 *  This file contains the hardware definitions of the EBSA-285.
 */
#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H

/*   Virtual      Physical	Size
 * 0xff800000	0x40000000	1MB	X-Bus
 * 0xff000000	0x7c000000	1MB	PCI I/O space
 * 0xfe000000	0x42000000	1MB	CSR
 * 0xfd000000	0x78000000	1MB	Outbound ग_लिखो flush (not supported)
 * 0xfc000000	0x79000000	1MB	PCI IACK/special space
 * 0xfb000000	0x7a000000	16MB	PCI Config type 1
 * 0xfa000000	0x7b000000	16MB	PCI Config type 0
 * 0xf9000000	0x50000000	1MB	Cache flush
 * 0xf0000000	0x80000000	16MB	ISA memory
 */

#अगर_घोषित CONFIG_MMU
#घोषणा MMU_IO(a, b)	(a)
#अन्यथा
#घोषणा MMU_IO(a, b)	(b)
#पूर्ण_अगर

#घोषणा XBUS_SIZE		0x00100000
#घोषणा XBUS_BASE		MMU_IO(0xff800000, 0x40000000)

#घोषणा ARMCSR_SIZE		0x00100000
#घोषणा ARMCSR_BASE		MMU_IO(0xfe000000, 0x42000000)

#घोषणा WFLUSH_SIZE		0x00100000
#घोषणा WFLUSH_BASE		MMU_IO(0xfd000000, 0x78000000)

#घोषणा PCIIACK_SIZE		0x00100000
#घोषणा PCIIACK_BASE		MMU_IO(0xfc000000, 0x79000000)

#घोषणा PCICFG1_SIZE		0x01000000
#घोषणा PCICFG1_BASE		MMU_IO(0xfb000000, 0x7a000000)

#घोषणा PCICFG0_SIZE		0x01000000
#घोषणा PCICFG0_BASE		MMU_IO(0xfa000000, 0x7b000000)

#घोषणा PCIMEM_SIZE		0x01000000
#घोषणा PCIMEM_BASE		MMU_IO(0xf0000000, 0x80000000)

#घोषणा XBUS_CS2		0x40012000

#घोषणा XBUS_SWITCH		((अस्थिर अचिन्हित अक्षर *)(XBUS_BASE + 0x12000))
#घोषणा XBUS_SWITCH_SWITCH	((*XBUS_SWITCH) & 15)
#घोषणा XBUS_SWITCH_J17_13	((*XBUS_SWITCH) & (1 << 4))
#घोषणा XBUS_SWITCH_J17_11	((*XBUS_SWITCH) & (1 << 5))
#घोषणा XBUS_SWITCH_J17_9	((*XBUS_SWITCH) & (1 << 6))

#घोषणा UNCACHEABLE_ADDR	(ARMCSR_BASE + 0x108)	/* CSR_ROMBASEMASK */


/* PIC irq control */
#घोषणा PIC_LO			0x20
#घोषणा PIC_MASK_LO		0x21
#घोषणा PIC_HI			0xA0
#घोषणा PIC_MASK_HI		0xA1

/* GPIO pins */
#घोषणा GPIO_CCLK		0x800
#घोषणा GPIO_DSCLK		0x400
#घोषणा GPIO_E2CLK		0x200
#घोषणा GPIO_IOLOAD		0x100
#घोषणा GPIO_RED_LED		0x080
#घोषणा GPIO_WDTIMER		0x040
#घोषणा GPIO_DATA		0x020
#घोषणा GPIO_IOCLK		0x010
#घोषणा GPIO_DONE		0x008
#घोषणा GPIO_FAN		0x004
#घोषणा GPIO_GREEN_LED		0x002
#घोषणा GPIO_RESET		0x001

/* CPLD pins */
#घोषणा CPLD_DS_ENABLE		8
#घोषणा CPLD_7111_DISABLE	4
#घोषणा CPLD_UNMUTE		2
#घोषणा CPLD_FLASH_WR_ENABLE	1

#अगर_अघोषित __ASSEMBLY__
बाह्य raw_spinlock_t nw_gpio_lock;
बाह्य व्योम nw_gpio_modअगरy_op(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set);
बाह्य व्योम nw_gpio_modअगरy_io(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक in);
बाह्य अचिन्हित पूर्णांक nw_gpio_पढ़ो(व्योम);
बाह्य व्योम nw_cpld_modअगरy(अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक set);
#पूर्ण_अगर

#पूर्ण_अगर
