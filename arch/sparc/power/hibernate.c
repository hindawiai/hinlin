<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * hibernate.c:  Hibernaton support specअगरic क्रम sparc64.
 *
 * Copyright (C) 2013 Kirill V Tkhai (tkhai@yandex.ru)
 */

#समावेश <linux/mm.h>

#समावेश <यंत्र/hibernate.h>
#समावेश <यंत्र/visयंत्र.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>

काष्ठा saved_context saved_context;

/*
 *	pfn_is_nosave - check अगर given pfn is in the 'nosave' section
 */

पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nosave_begin_pfn = PFN_DOWN((अचिन्हित दीर्घ)&__nosave_begin);
	अचिन्हित दीर्घ nosave_end_pfn = PFN_DOWN((अचिन्हित दीर्घ)&__nosave_end);

	वापस (pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
पूर्ण

व्योम save_processor_state(व्योम)
अणु
	save_and_clear_fpu();
पूर्ण

व्योम restore_processor_state(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;

	tsb_context_चयन_ctx(mm, CTX_HWBITS(mm->context));
पूर्ण
