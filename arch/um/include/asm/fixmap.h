<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_FIXMAP_H
#घोषणा __UM_FIXMAP_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/archparam.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/thपढ़ोs.h>

/*
 * Here we define all the compile-समय 'special' भव
 * addresses. The poपूर्णांक is to have a स्थिरant address at
 * compile समय, but to set the physical address only
 * in the boot process. We allocate these special  addresses
 * from the end of भव memory (0xfffff000) backwards.
 * Also this lets us करो fail-safe vदो_स्मृति(), we
 * can guarantee that these special addresses and
 * vदो_स्मृति()-ed addresses never overlap.
 *
 * these 'compile-time allocated' memory buffers are
 * fixed-size 4k pages. (or larger अगर used with an increment
 * highger than 1) use fixmap_set(idx,phys) to associate
 * physical memory with fixmap indices.
 *
 * TLB entries of such buffers will not be flushed across
 * task चयनes.
 */

/*
 * on UP currently we will have no trace of the fixmap mechanizm,
 * no page table allocations, etc. This might change in the
 * future, say framebuffers क्रम the console driver(s) could be
 * fix-mapped?
 */
क्रमागत fixed_addresses अणु
	__end_of_fixed_addresses
पूर्ण;

बाह्य व्योम __set_fixmap (क्रमागत fixed_addresses idx,
			  अचिन्हित दीर्घ phys, pgprot_t flags);

/*
 * used by vदो_स्मृति.c.
 *
 * Leave one empty page between vदो_स्मृति'ed areas and
 * the start of the fixmap, and leave one page empty
 * at the top of mem..
 */

#घोषणा FIXADDR_TOP	(TASK_SIZE - 2 * PAGE_SIZE)
#घोषणा FIXADDR_SIZE	(__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START	(FIXADDR_TOP - FIXADDR_SIZE)

#समावेश <यंत्र-generic/fixmap.h>

#पूर्ण_अगर
