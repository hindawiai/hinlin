<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 SiFive
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/memory.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/stop_machine.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/patch.h>

काष्ठा patch_insn अणु
	व्योम *addr;
	u32 insn;
	atomic_t cpu_count;
पूर्ण;

#अगर_घोषित CONFIG_MMU
/*
 * The fix_to_virt(, idx) needs a स्थिर value (not a dynamic variable of
 * reg-a0) or BUILD_BUG_ON failed with "idx >= __end_of_fixed_addresses".
 * So use '__always_inline' and 'const unsigned int fixmap' here.
 */
अटल __always_अंतरभूत व्योम *patch_map(व्योम *addr, स्थिर अचिन्हित पूर्णांक fixmap)
अणु
	uपूर्णांकptr_t uपूर्णांकaddr = (uपूर्णांकptr_t) addr;
	काष्ठा page *page;

	अगर (core_kernel_text(uपूर्णांकaddr))
		page = phys_to_page(__pa_symbol(addr));
	अन्यथा अगर (IS_ENABLED(CONFIG_STRICT_MODULE_RWX))
		page = vदो_स्मृति_to_page(addr);
	अन्यथा
		वापस addr;

	BUG_ON(!page);

	वापस (व्योम *)set_fixmap_offset(fixmap, page_to_phys(page) +
					 (uपूर्णांकaddr & ~PAGE_MASK));
पूर्ण

अटल व्योम patch_unmap(पूर्णांक fixmap)
अणु
	clear_fixmap(fixmap);
पूर्ण
NOKPROBE_SYMBOL(patch_unmap);

अटल पूर्णांक patch_insn_ग_लिखो(व्योम *addr, स्थिर व्योम *insn, माप_प्रकार len)
अणु
	व्योम *waddr = addr;
	bool across_pages = (((uपूर्णांकptr_t) addr & ~PAGE_MASK) + len) > PAGE_SIZE;
	पूर्णांक ret;

	/*
	 * Beक्रमe reaching here, it was expected to lock the text_mutex
	 * alपढ़ोy, so we करोn't need to give another lock here and could
	 * ensure that it was safe between each cores.
	 */
	lockdep_निश्चित_held(&text_mutex);

	अगर (across_pages)
		patch_map(addr + len, FIX_TEXT_POKE1);

	waddr = patch_map(addr, FIX_TEXT_POKE0);

	ret = copy_to_kernel_nofault(waddr, insn, len);

	patch_unmap(FIX_TEXT_POKE0);

	अगर (across_pages)
		patch_unmap(FIX_TEXT_POKE1);

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(patch_insn_ग_लिखो);
#अन्यथा
अटल पूर्णांक patch_insn_ग_लिखो(व्योम *addr, स्थिर व्योम *insn, माप_प्रकार len)
अणु
	वापस copy_to_kernel_nofault(addr, insn, len);
पूर्ण
NOKPROBE_SYMBOL(patch_insn_ग_लिखो);
#पूर्ण_अगर /* CONFIG_MMU */

पूर्णांक patch_text_nosync(व्योम *addr, स्थिर व्योम *insns, माप_प्रकार len)
अणु
	u32 *tp = addr;
	पूर्णांक ret;

	ret = patch_insn_ग_लिखो(tp, insns, len);

	अगर (!ret)
		flush_icache_range((uपूर्णांकptr_t) tp, (uपूर्णांकptr_t) tp + len);

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(patch_text_nosync);

अटल पूर्णांक patch_text_cb(व्योम *data)
अणु
	काष्ठा patch_insn *patch = data;
	पूर्णांक ret = 0;

	अगर (atomic_inc_वापस(&patch->cpu_count) == 1) अणु
		ret =
		    patch_text_nosync(patch->addr, &patch->insn,
					    GET_INSN_LENGTH(patch->insn));
		atomic_inc(&patch->cpu_count);
	पूर्ण अन्यथा अणु
		जबतक (atomic_पढ़ो(&patch->cpu_count) <= num_online_cpus())
			cpu_relax();
		smp_mb();
	पूर्ण

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(patch_text_cb);

पूर्णांक patch_text(व्योम *addr, u32 insn)
अणु
	काष्ठा patch_insn patch = अणु
		.addr = addr,
		.insn = insn,
		.cpu_count = ATOMIC_INIT(0),
	पूर्ण;

	वापस stop_machine_cpuslocked(patch_text_cb,
				       &patch, cpu_online_mask);
पूर्ण
NOKPROBE_SYMBOL(patch_text);
