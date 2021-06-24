<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ALPHA_SETUP_H
#घोषणा __ALPHA_SETUP_H

#घोषणा COMMAND_LINE_SIZE	256

/*
 * We leave one page क्रम the initial stack page, and one page क्रम
 * the initial process काष्ठाure. Also, the console eats 3 MB क्रम
 * the initial bootloader (one of which we can reclaim later).
 */
#घोषणा BOOT_PCB	0x20000000
#घोषणा BOOT_ADDR	0x20000000
/* Remove when official MILO sources have ELF support: */
#घोषणा BOOT_SIZE	(16*1024)

#अगर_घोषित CONFIG_ALPHA_LEGACY_START_ADDRESS
#घोषणा KERNEL_START_PHYS	0x300000 /* Old bootloaders hardcoded this.  */
#अन्यथा
#घोषणा KERNEL_START_PHYS	0x1000000 /* required: Wildfire/Titan/Marvel */
#पूर्ण_अगर

#घोषणा KERNEL_START	(PAGE_OFFSET+KERNEL_START_PHYS)
#घोषणा SWAPPER_PGD	KERNEL_START
#घोषणा INIT_STACK	(PAGE_OFFSET+KERNEL_START_PHYS+0x02000)
#घोषणा EMPTY_PGT	(PAGE_OFFSET+KERNEL_START_PHYS+0x04000)
#घोषणा EMPTY_PGE	(PAGE_OFFSET+KERNEL_START_PHYS+0x08000)
#घोषणा ZERO_PGE	(PAGE_OFFSET+KERNEL_START_PHYS+0x0A000)

#घोषणा START_ADDR	(PAGE_OFFSET+KERNEL_START_PHYS+0x10000)

/*
 * This is setup by the secondary bootstrap loader.  Because
 * the zero page is zeroed out as soon as the vm प्रणाली is
 * initialized, we need to copy things out पूर्णांकo a more permanent
 * place.
 */
#घोषणा PARAM			ZERO_PGE
#घोषणा COMMAND_LINE		((अक्षर*)(PARAM + 0x0000))
#घोषणा INITRD_START		(*(अचिन्हित दीर्घ *) (PARAM+0x100))
#घोषणा INITRD_SIZE		(*(अचिन्हित दीर्घ *) (PARAM+0x108))

#पूर्ण_अगर
