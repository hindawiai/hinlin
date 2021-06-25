<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/arm/mach-footbridge/cats-hw.c
 *
 * CATS machine fixup
 *
 * Copyright (C) 1998, 1999 Russell King, Phil Blundell
 */
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/setup.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

#घोषणा CFG_PORT	0x370
#घोषणा INDEX_PORT	(CFG_PORT)
#घोषणा DATA_PORT	(CFG_PORT + 1)

अटल पूर्णांक __init cats_hw_init(व्योम)
अणु
	अगर (machine_is_cats()) अणु
		/* Set Aladdin to CONFIGURE mode */
		outb(0x51, CFG_PORT);
		outb(0x23, CFG_PORT);

		/* Select logical device 3 */
		outb(0x07, INDEX_PORT);
		outb(0x03, DATA_PORT);

		/* Set parallel port to DMA channel 3, ECP+EPP1.9, 
		   enable EPP समयout */
		outb(0x74, INDEX_PORT);
		outb(0x03, DATA_PORT);
	
		outb(0xf0, INDEX_PORT);
		outb(0x0f, DATA_PORT);

		outb(0xf1, INDEX_PORT);
		outb(0x07, DATA_PORT);

		/* Select logical device 4 */
		outb(0x07, INDEX_PORT);
		outb(0x04, DATA_PORT);

		/* UART1 high speed mode */
		outb(0xf0, INDEX_PORT);
		outb(0x02, DATA_PORT);

		/* Select logical device 5 */
		outb(0x07, INDEX_PORT);
		outb(0x05, DATA_PORT);

		/* UART2 high speed mode */
		outb(0xf0, INDEX_PORT);
		outb(0x02, DATA_PORT);

		/* Set Aladdin to RUN mode */
		outb(0xbb, CFG_PORT);
	पूर्ण

	वापस 0;
पूर्ण

__initcall(cats_hw_init);

/*
 * CATS uses soft-reboot by शेष, since
 * hard reboots fail on early boards.
 */
अटल व्योम __init
fixup_cats(काष्ठा tag *tags, अक्षर **cmdline)
अणु
#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_DUMMY_CONSOLE)
	screen_info.orig_video_lines  = 25;
	screen_info.orig_video_poपूर्णांकs = 16;
	screen_info.orig_y = 24;
#पूर्ण_अगर
पूर्ण

MACHINE_START(CATS, "Chalice-CATS")
	/* Maपूर्णांकainer: Philip Blundell */
	.atag_offset	= 0x100,
	.reboot_mode	= REBOOT_SOFT,
	.fixup		= fixup_cats,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.init_समय	= isa_समयr_init,
	.restart	= footbridge_restart,
MACHINE_END
