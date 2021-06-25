<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 8237A DMA controller suspend functions.
 *
 * Written by Pierre Ossman, 2005.
 */

#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/x86_init.h>

/*
 * This module just handles suspend/resume issues with the
 * 8237A DMA controller (used क्रम ISA and LPC).
 * Allocation is handled in kernel/dma.c and normal usage is
 * in यंत्र/dma.h.
 */

अटल व्योम i8237A_resume(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	flags = claim_dma_lock();

	dma_outb(0, DMA1_RESET_REG);
	dma_outb(0, DMA2_RESET_REG);

	क्रम (i = 0; i < 8; i++) अणु
		set_dma_addr(i, 0x000000);
		/* DMA count is a bit weird so this is not 0 */
		set_dma_count(i, 1);
	पूर्ण

	/* Enable cascade DMA or channel 0-3 won't work */
	enable_dma(4);

	release_dma_lock(flags);
पूर्ण

अटल काष्ठा syscore_ops i8237_syscore_ops = अणु
	.resume		= i8237A_resume,
पूर्ण;

अटल पूर्णांक __init i8237A_init_ops(व्योम)
अणु
	/*
	 * From SKL PCH onwards, the legacy DMA device is हटाओd in which the
	 * I/O ports (81h-83h, 87h, 89h-8Bh, 8Fh) related to it are हटाओd
	 * as well. All हटाओd ports must वापस 0xff क्रम a inb() request.
	 *
	 * Note: DMA_PAGE_2 (port 0x81) should not be checked क्रम detecting
	 * the presence of DMA device since it may be used by BIOS to decode
	 * LPC traffic क्रम POST codes. Original LPC only decodes one byte of
	 * port 0x80 but some BIOS may choose to enhance PCH LPC port 0x8x
	 * decoding.
	 */
	अगर (dma_inb(DMA_PAGE_0) == 0xFF)
		वापस -ENODEV;

	/*
	 * It is not required to load this driver as newer SoC may not
	 * support 8237 DMA or bus mastering from LPC. Platक्रमm firmware
	 * must announce the support क्रम such legacy devices via
	 * ACPI_FADT_LEGACY_DEVICES field in FADT table.
	 */
	अगर (x86_pnpbios_disabled() && dmi_get_bios_year() >= 2017)
		वापस -ENODEV;

	रेजिस्टर_syscore_ops(&i8237_syscore_ops);
	वापस 0;
पूर्ण
device_initcall(i8237A_init_ops);
