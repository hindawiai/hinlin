<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vdso.h>

काष्ठा vdso_exception_table_entry अणु
	पूर्णांक insn, fixup;
पूर्ण;

bool fixup_vdso_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr,
			  अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ fault_addr)
अणु
	स्थिर काष्ठा vdso_image *image = current->mm->context.vdso_image;
	स्थिर काष्ठा vdso_exception_table_entry *extable;
	अचिन्हित पूर्णांक nr_entries, i;
	अचिन्हित दीर्घ base;

	/*
	 * Do not attempt to fixup #DB or #BP.  It's impossible to identअगरy
	 * whether or not a #DB/#BP originated from within an SGX enclave and
	 * SGX enclaves are currently the only use हाल क्रम vDSO fixup.
	 */
	अगर (trapnr == X86_TRAP_DB || trapnr == X86_TRAP_BP)
		वापस false;

	अगर (!current->mm->context.vdso)
		वापस false;

	base =  (अचिन्हित दीर्घ)current->mm->context.vdso + image->extable_base;
	nr_entries = image->extable_len / (माप(*extable));
	extable = image->extable;

	क्रम (i = 0; i < nr_entries; i++) अणु
		अगर (regs->ip == base + extable[i].insn) अणु
			regs->ip = base + extable[i].fixup;
			regs->di = trapnr;
			regs->si = error_code;
			regs->dx = fault_addr;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
