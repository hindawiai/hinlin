<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module help क्रम घातerpc.
    Copyright (C) 2001, 2003 Rusty Russell IBM Corporation.
    Copyright (C) 2008 Freescale Semiconductor, Inc.

*/
#समावेश <linux/elf.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/err.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/module.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/firmware.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>

अटल LIST_HEAD(module_bug_list);

अटल स्थिर Elf_Shdr *find_section(स्थिर Elf_Ehdr *hdr,
				    स्थिर Elf_Shdr *sechdrs,
				    स्थिर अक्षर *name)
अणु
	अक्षर *secstrings;
	अचिन्हित पूर्णांक i;

	secstrings = (अक्षर *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	क्रम (i = 1; i < hdr->e_shnum; i++)
		अगर (म_भेद(secstrings+sechdrs[i].sh_name, name) == 0)
			वापस &sechdrs[i];
	वापस शून्य;
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		स्थिर Elf_Shdr *sechdrs, काष्ठा module *me)
अणु
	स्थिर Elf_Shdr *sect;
	पूर्णांक rc;

	rc = module_finalize_ftrace(me, sechdrs);
	अगर (rc)
		वापस rc;

	/* Apply feature fixups */
	sect = find_section(hdr, sechdrs, "__ftr_fixup");
	अगर (sect != शून्य)
		करो_feature_fixups(cur_cpu_spec->cpu_features,
				  (व्योम *)sect->sh_addr,
				  (व्योम *)sect->sh_addr + sect->sh_size);

	sect = find_section(hdr, sechdrs, "__mmu_ftr_fixup");
	अगर (sect != शून्य)
		करो_feature_fixups(cur_cpu_spec->mmu_features,
				  (व्योम *)sect->sh_addr,
				  (व्योम *)sect->sh_addr + sect->sh_size);

#अगर_घोषित CONFIG_PPC64
	sect = find_section(hdr, sechdrs, "__fw_ftr_fixup");
	अगर (sect != शून्य)
		करो_feature_fixups(घातerpc_firmware_features,
				  (व्योम *)sect->sh_addr,
				  (व्योम *)sect->sh_addr + sect->sh_size);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित PPC64_ELF_ABI_v1
	sect = find_section(hdr, sechdrs, ".opd");
	अगर (sect != शून्य) अणु
		me->arch.start_opd = sect->sh_addr;
		me->arch.end_opd = sect->sh_addr + sect->sh_size;
	पूर्ण
#पूर्ण_अगर /* PPC64_ELF_ABI_v1 */

#अगर_घोषित CONFIG_PPC_BARRIER_NOSPEC
	sect = find_section(hdr, sechdrs, "__spec_barrier_fixup");
	अगर (sect != शून्य)
		करो_barrier_nospec_fixups_range(barrier_nospec_enabled,
				  (व्योम *)sect->sh_addr,
				  (व्योम *)sect->sh_addr + sect->sh_size);
#पूर्ण_अगर /* CONFIG_PPC_BARRIER_NOSPEC */

	sect = find_section(hdr, sechdrs, "__lwsync_fixup");
	अगर (sect != शून्य)
		करो_lwsync_fixups(cur_cpu_spec->cpu_features,
				 (व्योम *)sect->sh_addr,
				 (व्योम *)sect->sh_addr + sect->sh_size);

	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम *
__module_alloc(अचिन्हित दीर्घ size, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * Don't करो huge page allocations क्रम modules yet until more testing
	 * is करोne. STRICT_MODULE_RWX may require extra work to support this
	 * too.
	 */
	वापस __vदो_स्मृति_node_range(size, 1, start, end, GFP_KERNEL, PAGE_KERNEL_EXEC,
				    VM_FLUSH_RESET_PERMS | VM_NO_HUGE_VMAP,
				    NUMA_NO_NODE, __builtin_वापस_address(0));
पूर्ण

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
#अगर_घोषित MODULES_VADDR
	अचिन्हित दीर्घ limit = (अचिन्हित दीर्घ)_etext - SZ_32M;
	व्योम *ptr = शून्य;

	BUILD_BUG_ON(TASK_SIZE > MODULES_VADDR);

	/* First try within 32M limit from _etext to aव्योम branch trampolines */
	अगर (MODULES_VADDR < PAGE_OFFSET && MODULES_END > limit)
		ptr = __module_alloc(size, limit, MODULES_END);

	अगर (!ptr)
		ptr = __module_alloc(size, MODULES_VADDR, MODULES_END);

	वापस ptr;
#अन्यथा
	वापस __module_alloc(size, VMALLOC_START, VMALLOC_END);
#पूर्ण_अगर
पूर्ण
