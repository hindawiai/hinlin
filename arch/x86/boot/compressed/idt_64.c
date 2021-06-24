<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <यंत्र/trap_pf.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/trapnr.h>
#समावेश "misc.h"

अटल व्योम set_idt_entry(पूर्णांक vector, व्योम (*handler)(व्योम))
अणु
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)handler;
	gate_desc entry;

	स_रखो(&entry, 0, माप(entry));

	entry.offset_low    = (u16)(address & 0xffff);
	entry.segment       = __KERNEL_CS;
	entry.bits.type     = GATE_TRAP;
	entry.bits.p        = 1;
	entry.offset_middle = (u16)((address >> 16) & 0xffff);
	entry.offset_high   = (u32)(address >> 32);

	स_नकल(&boot_idt[vector], &entry, माप(entry));
पूर्ण

/* Have this here so we करोn't need to include <यंत्र/desc.h> */
अटल व्योम load_boot_idt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	यंत्र अस्थिर("lidt %0"::"m" (*dtr));
पूर्ण

/* Setup IDT beक्रमe kernel jumping to  .Lrelocated */
व्योम load_stage1_idt(व्योम)
अणु
	boot_idt_desc.address = (अचिन्हित दीर्घ)boot_idt;


	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT))
		set_idt_entry(X86_TRAP_VC, boot_stage1_vc);

	load_boot_idt(&boot_idt_desc);
पूर्ण

/* Setup IDT after kernel jumping to  .Lrelocated */
व्योम load_stage2_idt(व्योम)
अणु
	boot_idt_desc.address = (अचिन्हित दीर्घ)boot_idt;

	set_idt_entry(X86_TRAP_PF, boot_page_fault);

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	set_idt_entry(X86_TRAP_VC, boot_stage2_vc);
#पूर्ण_अगर

	load_boot_idt(&boot_idt_desc);
पूर्ण

व्योम cleanup_exception_handling(व्योम)
अणु
	/*
	 * Flush GHCB from cache and map it encrypted again when running as
	 * SEV-ES guest.
	 */
	sev_es_shutकरोwn_ghcb();

	/* Set a null-idt, disabling #PF and #VC handling */
	boot_idt_desc.size    = 0;
	boot_idt_desc.address = 0;
	load_boot_idt(&boot_idt_desc);
पूर्ण
