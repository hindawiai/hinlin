<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2001-2003 Pavel Machek <pavel@suse.cz>
 * Based on code
 * Copyright 2001 Patrick Mochel <mochel@osdl.org>
 */
#अगर_अघोषित _ASM_X86_SUSPEND_64_H
#घोषणा _ASM_X86_SUSPEND_64_H

#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/fpu/api.h>

/*
 * Image of the saved processor state, used by the low level ACPI suspend to
 * RAM code and by the low level hibernation code.
 *
 * If you modअगरy it, fix arch/x86/kernel/acpi/wakeup_64.S and make sure that
 * __save/__restore_processor_state(), defined in arch/x86/kernel/suspend_64.c,
 * still work as required.
 */
काष्ठा saved_context अणु
	काष्ठा pt_regs regs;

	/*
	 * User CS and SS are saved in current_pt_regs().  The rest of the
	 * segment selectors need to be saved and restored here.
	 */
	u16 ds, es, fs, gs;

	/*
	 * Usermode FSBASE and GSBASE may not match the fs and gs selectors,
	 * so we save them separately.  We save the kernelmode GSBASE to
	 * restore percpu access after resume.
	 */
	अचिन्हित दीर्घ kernelmode_gs_base, usermode_gs_base, fs_base;

	अचिन्हित दीर्घ cr0, cr2, cr3, cr4;
	u64 misc_enable;
	bool misc_enable_saved;
	काष्ठा saved_msrs saved_msrs;
	अचिन्हित दीर्घ efer;
	u16 gdt_pad; /* Unused */
	काष्ठा desc_ptr gdt_desc;
	u16 idt_pad;
	काष्ठा desc_ptr idt;
	u16 ldt;
	u16 tss;
	अचिन्हित दीर्घ tr;
	अचिन्हित दीर्घ safety;
	अचिन्हित दीर्घ वापस_address;
पूर्ण __attribute__((packed));

#घोषणा loaddebug(thपढ़ो,रेजिस्टर) \
	set_debugreg((thपढ़ो)->debugreg##रेजिस्टर, रेजिस्टर)

/* routines क्रम saving/restoring kernel state */
बाह्य अक्षर core_restore_code[];
बाह्य अक्षर restore_रेजिस्टरs[];

#पूर्ण_अगर /* _ASM_X86_SUSPEND_64_H */
