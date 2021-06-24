<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2001-2002 Pavel Machek <pavel@suse.cz>
 * Based on code
 * Copyright 2001 Patrick Mochel <mochel@osdl.org>
 */
#अगर_अघोषित _ASM_X86_SUSPEND_32_H
#घोषणा _ASM_X86_SUSPEND_32_H

#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/fpu/api.h>

/* image of the saved processor state */
काष्ठा saved_context अणु
	/*
	 * On x86_32, all segment रेजिस्टरs except gs are saved at kernel
	 * entry in pt_regs.
	 */
	u16 gs;
	अचिन्हित दीर्घ cr0, cr2, cr3, cr4;
	u64 misc_enable;
	bool misc_enable_saved;
	काष्ठा saved_msrs saved_msrs;
	काष्ठा desc_ptr gdt_desc;
	काष्ठा desc_ptr idt;
	u16 ldt;
	u16 tss;
	अचिन्हित दीर्घ tr;
	अचिन्हित दीर्घ safety;
	अचिन्हित दीर्घ वापस_address;
पूर्ण __attribute__((packed));

/* routines क्रम saving/restoring kernel state */
बाह्य अक्षर core_restore_code[];
बाह्य अक्षर restore_रेजिस्टरs[];

#पूर्ण_अगर /* _ASM_X86_SUSPEND_32_H */
