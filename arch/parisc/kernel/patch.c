<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
 /*
  * functions to patch RO kernel text during runसमय
  *
  * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
  */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/mm.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/patch.h>

काष्ठा patch अणु
	व्योम *addr;
	u32 *insn;
	अचिन्हित पूर्णांक len;
पूर्ण;

अटल DEFINE_RAW_SPINLOCK(patch_lock);

अटल व्योम __kprobes *patch_map(व्योम *addr, पूर्णांक fixmap, अचिन्हित दीर्घ *flags,
				 पूर्णांक *need_unmap)
अणु
	अचिन्हित दीर्घ uपूर्णांकaddr = (uपूर्णांकptr_t) addr;
	bool module = !core_kernel_text(uपूर्णांकaddr);
	काष्ठा page *page;

	*need_unmap = 0;
	अगर (module && IS_ENABLED(CONFIG_STRICT_MODULE_RWX))
		page = vदो_स्मृति_to_page(addr);
	अन्यथा अगर (!module && IS_ENABLED(CONFIG_STRICT_KERNEL_RWX))
		page = virt_to_page(addr);
	अन्यथा
		वापस addr;

	*need_unmap = 1;
	set_fixmap(fixmap, page_to_phys(page));
	अगर (flags)
		raw_spin_lock_irqsave(&patch_lock, *flags);
	अन्यथा
		__acquire(&patch_lock);

	वापस (व्योम *) (__fix_to_virt(fixmap) + (uपूर्णांकaddr & ~PAGE_MASK));
पूर्ण

अटल व्योम __kprobes patch_unmap(पूर्णांक fixmap, अचिन्हित दीर्घ *flags)
अणु
	clear_fixmap(fixmap);

	अगर (flags)
		raw_spin_unlock_irqrestore(&patch_lock, *flags);
	अन्यथा
		__release(&patch_lock);
पूर्ण

व्योम __kprobes __patch_text_multiple(व्योम *addr, u32 *insn, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)addr;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)addr + len;
	अचिन्हित दीर्घ flags;
	u32 *p, *fixmap;
	पूर्णांक mapped;

	/* Make sure we करोn't have any aliases in cache */
	flush_kernel_vmap_range(addr, len);
	flush_icache_range(start, end);

	p = fixmap = patch_map(addr, FIX_TEXT_POKE0, &flags, &mapped);

	जबतक (len >= 4) अणु
		*p++ = *insn++;
		addr += माप(u32);
		len -= माप(u32);
		अगर (len && offset_in_page(addr) == 0) अणु
			/*
			 * We're crossing a page boundary, so
			 * need to remap
			 */
			flush_kernel_vmap_range((व्योम *)fixmap,
						(p-fixmap) * माप(*p));
			अगर (mapped)
				patch_unmap(FIX_TEXT_POKE0, &flags);
			p = fixmap = patch_map(addr, FIX_TEXT_POKE0, &flags,
						&mapped);
		पूर्ण
	पूर्ण

	flush_kernel_vmap_range((व्योम *)fixmap, (p-fixmap) * माप(*p));
	अगर (mapped)
		patch_unmap(FIX_TEXT_POKE0, &flags);
	flush_icache_range(start, end);
पूर्ण

व्योम __kprobes __patch_text(व्योम *addr, u32 insn)
अणु
	__patch_text_multiple(addr, &insn, माप(insn));
पूर्ण

अटल पूर्णांक __kprobes patch_text_stop_machine(व्योम *data)
अणु
	काष्ठा patch *patch = data;

	__patch_text_multiple(patch->addr, patch->insn, patch->len);
	वापस 0;
पूर्ण

व्योम __kprobes patch_text(व्योम *addr, अचिन्हित पूर्णांक insn)
अणु
	काष्ठा patch patch = अणु
		.addr = addr,
		.insn = &insn,
		.len = माप(insn),
	पूर्ण;

	stop_machine_cpuslocked(patch_text_stop_machine, &patch, शून्य);
पूर्ण

व्योम __kprobes patch_text_multiple(व्योम *addr, u32 *insn, अचिन्हित पूर्णांक len)
अणु

	काष्ठा patch patch = अणु
		.addr = addr,
		.insn = insn,
		.len = len
	पूर्ण;

	stop_machine_cpuslocked(patch_text_stop_machine, &patch, शून्य);
पूर्ण
