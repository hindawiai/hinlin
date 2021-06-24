<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * swsusp.c - SuperH hibernation support
 *
 * Copyright (C) 2009 Magnus Damm
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/fpu.h>

काष्ठा swsusp_arch_regs swsusp_arch_regs_cpu0;

पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ begin_pfn = __pa(&__nosave_begin) >> PAGE_SHIFT;
	अचिन्हित दीर्घ end_pfn = PAGE_ALIGN(__pa(&__nosave_end)) >> PAGE_SHIFT;

	वापस (pfn >= begin_pfn) && (pfn < end_pfn);
पूर्ण

व्योम save_processor_state(व्योम)
अणु
	init_fpu(current);
पूर्ण

व्योम restore_processor_state(व्योम)
अणु
	local_flush_tlb_all();
पूर्ण
