<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Prepare the machine क्रम transition to रक्षित mode.
 */

#समावेश "boot.h"
#समावेश <यंत्र/segment.h>

/*
 * Invoke the realmode चयन hook अगर present; otherwise
 * disable all पूर्णांकerrupts.
 */
अटल व्योम realmode_चयन_hook(व्योम)
अणु
	अगर (boot_params.hdr.realmode_swtch) अणु
		यंत्र अस्थिर("lcallw *%0"
			     : : "m" (boot_params.hdr.realmode_swtch)
			     : "eax", "ebx", "ecx", "edx");
	पूर्ण अन्यथा अणु
		यंत्र अस्थिर("cli");
		outb(0x80, 0x70); /* Disable NMI */
		io_delay();
	पूर्ण
पूर्ण

/*
 * Disable all पूर्णांकerrupts at the legacy PIC.
 */
अटल व्योम mask_all_पूर्णांकerrupts(व्योम)
अणु
	outb(0xff, 0xa1);	/* Mask all पूर्णांकerrupts on the secondary PIC */
	io_delay();
	outb(0xfb, 0x21);	/* Mask all but cascade on the primary PIC */
	io_delay();
पूर्ण

/*
 * Reset IGNNE# अगर निश्चितed in the FPU.
 */
अटल व्योम reset_coprocessor(व्योम)
अणु
	outb(0, 0xf0);
	io_delay();
	outb(0, 0xf1);
	io_delay();
पूर्ण

/*
 * Set up the GDT
 */

काष्ठा gdt_ptr अणु
	u16 len;
	u32 ptr;
पूर्ण __attribute__((packed));

अटल व्योम setup_gdt(व्योम)
अणु
	/* There are machines which are known to not boot with the GDT
	   being 8-byte unaligned.  Intel recommends 16 byte alignment. */
	अटल स्थिर u64 boot_gdt[] __attribute__((aligned(16))) = अणु
		/* CS: code, पढ़ो/execute, 4 GB, base 0 */
		[GDT_ENTRY_BOOT_CS] = GDT_ENTRY(0xc09b, 0, 0xfffff),
		/* DS: data, पढ़ो/ग_लिखो, 4 GB, base 0 */
		[GDT_ENTRY_BOOT_DS] = GDT_ENTRY(0xc093, 0, 0xfffff),
		/* TSS: 32-bit tss, 104 bytes, base 4096 */
		/* We only have a TSS here to keep Intel VT happy;
		   we करोn't actually use it क्रम anything. */
		[GDT_ENTRY_BOOT_TSS] = GDT_ENTRY(0x0089, 4096, 103),
	पूर्ण;
	/* Xen HVM incorrectly stores a poपूर्णांकer to the gdt_ptr, instead
	   of the gdt_ptr contents.  Thus, make it अटल so it will
	   stay in memory, at least दीर्घ enough that we चयन to the
	   proper kernel GDT. */
	अटल काष्ठा gdt_ptr gdt;

	gdt.len = माप(boot_gdt)-1;
	gdt.ptr = (u32)&boot_gdt + (ds() << 4);

	यंत्र अस्थिर("lgdtl %0" : : "m" (gdt));
पूर्ण

/*
 * Set up the IDT
 */
अटल व्योम setup_idt(व्योम)
अणु
	अटल स्थिर काष्ठा gdt_ptr null_idt = अणु0, 0पूर्ण;
	यंत्र अस्थिर("lidtl %0" : : "m" (null_idt));
पूर्ण

/*
 * Actual invocation sequence
 */
व्योम go_to_रक्षित_mode(व्योम)
अणु
	/* Hook beक्रमe leaving real mode, also disables पूर्णांकerrupts */
	realmode_चयन_hook();

	/* Enable the A20 gate */
	अगर (enable_a20()) अणु
		माला_दो("A20 gate not responding, unable to boot...\n");
		die();
	पूर्ण

	/* Reset coprocessor (IGNNE#) */
	reset_coprocessor();

	/* Mask all पूर्णांकerrupts in the PIC */
	mask_all_पूर्णांकerrupts();

	/* Actual transition to रक्षित mode... */
	setup_idt();
	setup_gdt();
	रक्षित_mode_jump(boot_params.hdr.code32_start,
			    (u32)&boot_params + (ds() << 4));
पूर्ण
