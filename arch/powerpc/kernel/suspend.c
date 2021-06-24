<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Suspend support specअगरic क्रम घातer.
 *
 * Copyright (c) 2002 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2001 Patrick Mochel <mochel@osdl.org>
 */

#समावेश <linux/mm.h>
#समावेश <linux/suspend.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

/*
 *	pfn_is_nosave - check अगर given pfn is in the 'nosave' section
 */

पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nosave_begin_pfn = __pa(&__nosave_begin) >> PAGE_SHIFT;
	अचिन्हित दीर्घ nosave_end_pfn = PAGE_ALIGN(__pa(&__nosave_end)) >> PAGE_SHIFT;
	वापस (pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
पूर्ण
