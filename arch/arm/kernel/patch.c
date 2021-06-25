<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/mm.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/patch.h>

काष्ठा patch अणु
	व्योम *addr;
	अचिन्हित पूर्णांक insn;
पूर्ण;

#अगर_घोषित CONFIG_MMU
अटल DEFINE_RAW_SPINLOCK(patch_lock);

अटल व्योम __kprobes *patch_map(व्योम *addr, पूर्णांक fixmap, अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित पूर्णांक uपूर्णांकaddr = (uपूर्णांकptr_t) addr;
	bool module = !core_kernel_text(uपूर्णांकaddr);
	काष्ठा page *page;

	अगर (module && IS_ENABLED(CONFIG_STRICT_MODULE_RWX))
		page = vदो_स्मृति_to_page(addr);
	अन्यथा अगर (!module && IS_ENABLED(CONFIG_STRICT_KERNEL_RWX))
		page = virt_to_page(addr);
	अन्यथा
		वापस addr;

	अगर (flags)
		raw_spin_lock_irqsave(&patch_lock, *flags);

	set_fixmap(fixmap, page_to_phys(page));

	वापस (व्योम *) (__fix_to_virt(fixmap) + (uपूर्णांकaddr & ~PAGE_MASK));
पूर्ण

अटल व्योम __kprobes patch_unmap(पूर्णांक fixmap, अचिन्हित दीर्घ *flags)
अणु
	clear_fixmap(fixmap);

	अगर (flags)
		raw_spin_unlock_irqrestore(&patch_lock, *flags);
पूर्ण
#अन्यथा
अटल व्योम __kprobes *patch_map(व्योम *addr, पूर्णांक fixmap, अचिन्हित दीर्घ *flags)
अणु
	वापस addr;
पूर्ण
अटल व्योम __kprobes patch_unmap(पूर्णांक fixmap, अचिन्हित दीर्घ *flags) अणु पूर्ण
#पूर्ण_अगर

व्योम __kprobes __patch_text_real(व्योम *addr, अचिन्हित पूर्णांक insn, bool remap)
अणु
	bool thumb2 = IS_ENABLED(CONFIG_THUMB2_KERNEL);
	अचिन्हित पूर्णांक uपूर्णांकaddr = (uपूर्णांकptr_t) addr;
	bool twopage = false;
	अचिन्हित दीर्घ flags;
	व्योम *waddr = addr;
	पूर्णांक size;

	अगर (remap)
		waddr = patch_map(addr, FIX_TEXT_POKE0, &flags);

	अगर (thumb2 && __opcode_is_thumb16(insn)) अणु
		*(u16 *)waddr = __opcode_to_mem_thumb16(insn);
		size = माप(u16);
	पूर्ण अन्यथा अगर (thumb2 && (uपूर्णांकaddr & 2)) अणु
		u16 first = __opcode_thumb32_first(insn);
		u16 second = __opcode_thumb32_second(insn);
		u16 *addrh0 = waddr;
		u16 *addrh1 = waddr + 2;

		twopage = (uपूर्णांकaddr & ~PAGE_MASK) == PAGE_SIZE - 2;
		अगर (twopage && remap)
			addrh1 = patch_map(addr + 2, FIX_TEXT_POKE1, शून्य);

		*addrh0 = __opcode_to_mem_thumb16(first);
		*addrh1 = __opcode_to_mem_thumb16(second);

		अगर (twopage && addrh1 != addr + 2) अणु
			flush_kernel_vmap_range(addrh1, 2);
			patch_unmap(FIX_TEXT_POKE1, शून्य);
		पूर्ण

		size = माप(u32);
	पूर्ण अन्यथा अणु
		अगर (thumb2)
			insn = __opcode_to_mem_thumb32(insn);
		अन्यथा
			insn = __opcode_to_mem_arm(insn);

		*(u32 *)waddr = insn;
		size = माप(u32);
	पूर्ण

	अगर (waddr != addr) अणु
		flush_kernel_vmap_range(waddr, twopage ? size / 2 : size);
		patch_unmap(FIX_TEXT_POKE0, &flags);
	पूर्ण

	flush_icache_range((uपूर्णांकptr_t)(addr),
			   (uपूर्णांकptr_t)(addr) + size);
पूर्ण

अटल पूर्णांक __kprobes patch_text_stop_machine(व्योम *data)
अणु
	काष्ठा patch *patch = data;

	__patch_text(patch->addr, patch->insn);

	वापस 0;
पूर्ण

व्योम __kprobes patch_text(व्योम *addr, अचिन्हित पूर्णांक insn)
अणु
	काष्ठा patch patch = अणु
		.addr = addr,
		.insn = insn,
	पूर्ण;

	stop_machine_cpuslocked(patch_text_stop_machine, &patch, शून्य);
पूर्ण
