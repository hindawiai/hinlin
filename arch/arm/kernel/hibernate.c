<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hibernation support specअगरic क्रम ARM
 *
 * Derived from work on ARM hibernation support by:
 *
 * Ubuntu project, hibernation support क्रम mach-करोve
 * Copyright (C) 2010 Nokia Corporation (Hiroshi Doyu)
 * Copyright (C) 2010 Texas Instruments, Inc. (Teerth Reddy et al.)
 *  https://lkml.org/lkml/2010/6/18/4
 *  https://lists.linux-foundation.org/pipermail/linux-pm/2010-June/027422.hपंचांगl
 *  https://patchwork.kernel.org/patch/96442/
 *
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 */

#समावेश <linux/mm.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/sections.h>
#समावेश "reboot.h"

पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nosave_begin_pfn = virt_to_pfn(&__nosave_begin);
	अचिन्हित दीर्घ nosave_end_pfn = virt_to_pfn(&__nosave_end - 1);

	वापस (pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn);
पूर्ण

व्योम notrace save_processor_state(व्योम)
अणु
	WARN_ON(num_online_cpus() != 1);
	local_fiq_disable();
पूर्ण

व्योम notrace restore_processor_state(व्योम)
अणु
	local_fiq_enable();
पूर्ण

/*
 * Snapshot kernel memory and reset the प्रणाली.
 *
 * swsusp_save() is executed in the suspend finisher so that the CPU
 * context poपूर्णांकer and memory are part of the saved image, which is
 * required by the resume kernel image to restart execution from
 * swsusp_arch_suspend().
 *
 * soft_restart is not technically needed, but is used to get success
 * वापसed from cpu_suspend.
 *
 * When soft reboot completes, the hibernation snapshot is written out.
 */
अटल पूर्णांक notrace arch_save_image(अचिन्हित दीर्घ unused)
अणु
	पूर्णांक ret;

	ret = swsusp_save();
	अगर (ret == 0)
		_soft_restart(virt_to_idmap(cpu_resume), false);
	वापस ret;
पूर्ण

/*
 * Save the current CPU state beक्रमe suspend / घातeroff.
 */
पूर्णांक notrace swsusp_arch_suspend(व्योम)
अणु
	वापस cpu_suspend(0, arch_save_image);
पूर्ण

/*
 * Restore page contents क्रम physical pages that were in use during loading
 * hibernation image.  Switch to idmap_pgd so the physical page tables
 * are overwritten with the same contents.
 */
अटल व्योम notrace arch_restore_image(व्योम *unused)
अणु
	काष्ठा pbe *pbe;

	cpu_चयन_mm(idmap_pgd, &init_mm);
	क्रम (pbe = restore_pblist; pbe; pbe = pbe->next)
		copy_page(pbe->orig_address, pbe->address);

	_soft_restart(virt_to_idmap(cpu_resume), false);
पूर्ण

अटल u64 resume_stack[PAGE_SIZE/2/माप(u64)] __nosavedata;

/*
 * Resume from the hibernation image.
 * Due to the kernel heap / data restore, stack contents change underneath
 * and that would make function calls impossible; चयन to a temporary
 * stack within the nosave region to aव्योम that problem.
 */
पूर्णांक swsusp_arch_resume(व्योम)
अणु
	call_with_stack(arch_restore_image, 0,
		resume_stack + ARRAY_SIZE(resume_stack));
	वापस 0;
पूर्ण
