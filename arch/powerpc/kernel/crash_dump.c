<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Routines क्रम करोing kexec-based kdump.
 *
 * Copyright (C) 2005, IBM Corp.
 *
 * Created by: Michael Ellerman
 */

#अघोषित DEBUG

#समावेश <linux/crash_dump.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/kdump.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/inst.h>

#अगर_घोषित DEBUG
#समावेश <यंत्र/udbg.h>
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_NONSTATIC_KERNEL
व्योम __init reserve_kdump_trampoline(व्योम)
अणु
	memblock_reserve(0, KDUMP_RESERVE_LIMIT);
पूर्ण

अटल व्योम __init create_trampoline(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ppc_inst *p = (काष्ठा ppc_inst *)addr;

	/* The maximum range of a single inकाष्ठाion branch, is the current
	 * inकाष्ठाion's address + (32 MB - 4) bytes. For the trampoline we
	 * need to branch to current address + 32 MB. So we insert a nop at
	 * the trampoline address, then the next inकाष्ठाion (+ 4 bytes)
	 * करोes a branch to (32 MB - 4). The net effect is that when we
	 * branch to "addr" we jump to ("addr" + 32 MB). Although it requires
	 * two inकाष्ठाions it करोesn't require any रेजिस्टरs.
	 */
	patch_inकाष्ठाion(p, ppc_inst(PPC_INST_NOP));
	patch_branch((व्योम *)p + 4, addr + PHYSICAL_START, 0);
पूर्ण

व्योम __init setup_kdump_trampoline(व्योम)
अणु
	अचिन्हित दीर्घ i;

	DBG(" -> setup_kdump_trampoline()\n");

	क्रम (i = KDUMP_TRAMPOLINE_START; i < KDUMP_TRAMPOLINE_END; i += 8) अणु
		create_trampoline(i);
	पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
	create_trampoline(__pa(प्रणाली_reset_fwnmi) - PHYSICAL_START);
	create_trampoline(__pa(machine_check_fwnmi) - PHYSICAL_START);
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

	DBG(" <- setup_kdump_trampoline()\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_NONSTATIC_KERNEL */

अटल माप_प्रकार copy_oldmem_vaddr(व्योम *vaddr, अक्षर *buf, माप_प्रकार csize,
                               अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	अगर (userbuf) अणु
		अगर (copy_to_user((अक्षर __user *)buf, (vaddr + offset), csize))
			वापस -EFAULT;
	पूर्ण अन्यथा
		स_नकल(buf, (vaddr + offset), csize);

	वापस csize;
पूर्ण

/**
 * copy_oldmem_page - copy one page from "oldmem"
 * @pfn: page frame number to be copied
 * @buf: target memory address क्रम the copy; this can be in kernel address
 *      space or user address space (see @userbuf)
 * @csize: number of bytes to copy
 * @offset: offset in bytes पूर्णांकo the page (based on pfn) to begin the copy
 * @userbuf: अगर set, @buf is in user address space, use copy_to_user(),
 *      otherwise @buf is in kernel address space, use स_नकल().
 *
 * Copy a page from "oldmem". For this page, there is no pte mapped
 * in the current kernel. We stitch up a pte, similar to kmap_atomic.
 */
sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ pfn, अक्षर *buf,
			माप_प्रकार csize, अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	व्योम  *vaddr;
	phys_addr_t paddr;

	अगर (!csize)
		वापस 0;

	csize = min_t(माप_प्रकार, csize, PAGE_SIZE);
	paddr = pfn << PAGE_SHIFT;

	अगर (memblock_is_region_memory(paddr, csize)) अणु
		vaddr = __va(paddr);
		csize = copy_oldmem_vaddr(vaddr, buf, csize, offset, userbuf);
	पूर्ण अन्यथा अणु
		vaddr = ioremap_cache(paddr, PAGE_SIZE);
		csize = copy_oldmem_vaddr(vaddr, buf, csize, offset, userbuf);
		iounmap(vaddr);
	पूर्ण

	वापस csize;
पूर्ण

#अगर_घोषित CONFIG_PPC_RTAS
/*
 * The crashkernel region will almost always overlap the RTAS region, so
 * we have to be careful when shrinking the crashkernel region.
 */
व्योम crash_मुक्त_reserved_phys_range(अचिन्हित दीर्घ begin, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;
	स्थिर __be32 *basep, *sizep;
	अचिन्हित पूर्णांक rtas_start = 0, rtas_end = 0;

	basep = of_get_property(rtas.dev, "linux,rtas-base", शून्य);
	sizep = of_get_property(rtas.dev, "rtas-size", शून्य);

	अगर (basep && sizep) अणु
		rtas_start = be32_to_cpup(basep);
		rtas_end = rtas_start + be32_to_cpup(sizep);
	पूर्ण

	क्रम (addr = begin; addr < end; addr += PAGE_SIZE) अणु
		/* Does this page overlap with the RTAS region? */
		अगर (addr <= rtas_end && ((addr + PAGE_SIZE) > rtas_start))
			जारी;

		मुक्त_reserved_page(pfn_to_page(addr >> PAGE_SHIFT));
	पूर्ण
पूर्ण
#पूर्ण_अगर
