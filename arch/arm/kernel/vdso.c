<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Adapted from arm64 version.
 *
 * Copyright (C) 2012 ARM Limited
 * Copyright (C) 2015 Mentor Graphics Corporation.
 */

#समावेश <linux/cache.h>
#समावेश <linux/elf.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/of.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/arch_समयr.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <घड़ीsource/arm_arch_समयr.h>
#समावेश <vdso/helpers.h>
#समावेश <vdso/vsyscall.h>

#घोषणा MAX_SYMNAME	64

अटल काष्ठा page **vdso_text_pagelist;

बाह्य अक्षर vdso_start[], vdso_end[];

/* Total number of pages needed क्रम the data and text portions of the VDSO. */
अचिन्हित पूर्णांक vdso_total_pages __ro_after_init;

/*
 * The VDSO data page.
 */
अटल जोड़ vdso_data_store vdso_data_store __page_aligned_data;
काष्ठा vdso_data *vdso_data = vdso_data_store.data;

अटल काष्ठा page *vdso_data_page __ro_after_init;
अटल स्थिर काष्ठा vm_special_mapping vdso_data_mapping = अणु
	.name = "[vvar]",
	.pages = &vdso_data_page,
पूर्ण;

अटल पूर्णांक vdso_mremap(स्थिर काष्ठा vm_special_mapping *sm,
		काष्ठा vm_area_काष्ठा *new_vma)
अणु
	current->mm->context.vdso = new_vma->vm_start;

	वापस 0;
पूर्ण

अटल काष्ठा vm_special_mapping vdso_text_mapping __ro_after_init = अणु
	.name = "[vdso]",
	.mremap = vdso_mremap,
पूर्ण;

काष्ठा elfinfo अणु
	Elf32_Ehdr	*hdr;		/* ptr to ELF */
	Elf32_Sym	*dynsym;	/* ptr to .dynsym section */
	अचिन्हित दीर्घ	dynsymsize;	/* size of .dynsym section */
	अक्षर		*dynstr;	/* ptr to .dynstr section */
पूर्ण;

/* Cached result of boot-समय check क्रम whether the arch समयr exists,
 * and अगर so, whether the भव counter is useable.
 */
bool cntvct_ok __ro_after_init;

अटल bool __init cntvct_functional(व्योम)
अणु
	काष्ठा device_node *np;
	bool ret = false;

	अगर (!IS_ENABLED(CONFIG_ARM_ARCH_TIMER))
		जाओ out;

	/* The arm_arch_समयr core should export
	 * arch_समयr_use_भव or similar so we करोn't have to करो
	 * this.
	 */
	np = of_find_compatible_node(शून्य, शून्य, "arm,armv7-timer");
	अगर (!np)
		np = of_find_compatible_node(शून्य, शून्य, "arm,armv8-timer");
	अगर (!np)
		जाओ out_put;

	अगर (of_property_पढ़ो_bool(np, "arm,cpu-registers-not-fw-configured"))
		जाओ out_put;

	ret = true;

out_put:
	of_node_put(np);
out:
	वापस ret;
पूर्ण

अटल व्योम * __init find_section(Elf32_Ehdr *ehdr, स्थिर अक्षर *name,
				  अचिन्हित दीर्घ *size)
अणु
	Elf32_Shdr *sechdrs;
	अचिन्हित पूर्णांक i;
	अक्षर *secnames;

	/* Grab section headers and strings so we can tell who is who */
	sechdrs = (व्योम *)ehdr + ehdr->e_shoff;
	secnames = (व्योम *)ehdr + sechdrs[ehdr->e_shstrndx].sh_offset;

	/* Find the section they want */
	क्रम (i = 1; i < ehdr->e_shnum; i++) अणु
		अगर (म_भेद(secnames + sechdrs[i].sh_name, name) == 0) अणु
			अगर (size)
				*size = sechdrs[i].sh_size;
			वापस (व्योम *)ehdr + sechdrs[i].sh_offset;
		पूर्ण
	पूर्ण

	अगर (size)
		*size = 0;
	वापस शून्य;
पूर्ण

अटल Elf32_Sym * __init find_symbol(काष्ठा elfinfo *lib, स्थिर अक्षर *symname)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < (lib->dynsymsize / माप(Elf32_Sym)); i++) अणु
		अक्षर name[MAX_SYMNAME], *c;

		अगर (lib->dynsym[i].st_name == 0)
			जारी;
		strlcpy(name, lib->dynstr + lib->dynsym[i].st_name,
			MAX_SYMNAME);
		c = म_अक्षर(name, '@');
		अगर (c)
			*c = 0;
		अगर (म_भेद(symname, name) == 0)
			वापस &lib->dynsym[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __init vdso_nullpatch_one(काष्ठा elfinfo *lib, स्थिर अक्षर *symname)
अणु
	Elf32_Sym *sym;

	sym = find_symbol(lib, symname);
	अगर (!sym)
		वापस;

	sym->st_name = 0;
पूर्ण

अटल व्योम __init patch_vdso(व्योम *ehdr)
अणु
	काष्ठा elfinfo einfo;

	einfo = (काष्ठा elfinfo) अणु
		.hdr = ehdr,
	पूर्ण;

	einfo.dynsym = find_section(einfo.hdr, ".dynsym", &einfo.dynsymsize);
	einfo.dynstr = find_section(einfo.hdr, ".dynstr", शून्य);

	/* If the भव counter is असलent or non-functional we करोn't
	 * want programs to incur the slight additional overhead of
	 * dispatching through the VDSO only to fall back to syscalls.
	 */
	अगर (!cntvct_ok) अणु
		vdso_nullpatch_one(&einfo, "__vdso_gettimeofday");
		vdso_nullpatch_one(&einfo, "__vdso_clock_gettime");
		vdso_nullpatch_one(&einfo, "__vdso_clock_gettime64");
	पूर्ण
पूर्ण

अटल पूर्णांक __init vdso_init(व्योम)
अणु
	अचिन्हित पूर्णांक text_pages;
	पूर्णांक i;

	अगर (स_भेद(vdso_start, "\177ELF", 4)) अणु
		pr_err("VDSO is not a valid ELF object!\n");
		वापस -ENOEXEC;
	पूर्ण

	text_pages = (vdso_end - vdso_start) >> PAGE_SHIFT;

	/* Allocate the VDSO text pagelist */
	vdso_text_pagelist = kसुस्मृति(text_pages, माप(काष्ठा page *),
				     GFP_KERNEL);
	अगर (vdso_text_pagelist == शून्य)
		वापस -ENOMEM;

	/* Grab the VDSO data page. */
	vdso_data_page = virt_to_page(vdso_data);

	/* Grab the VDSO text pages. */
	क्रम (i = 0; i < text_pages; i++) अणु
		काष्ठा page *page;

		page = virt_to_page(vdso_start + i * PAGE_SIZE);
		vdso_text_pagelist[i] = page;
	पूर्ण

	vdso_text_mapping.pages = vdso_text_pagelist;

	vdso_total_pages = 1; /* क्रम the data/vvar page */
	vdso_total_pages += text_pages;

	cntvct_ok = cntvct_functional();

	patch_vdso(vdso_start);

	वापस 0;
पूर्ण
arch_initcall(vdso_init);

अटल पूर्णांक install_vvar(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	vma = _install_special_mapping(mm, addr, PAGE_SIZE,
				       VM_READ | VM_MAYREAD,
				       &vdso_data_mapping);

	वापस PTR_ERR_OR_ZERO(vma);
पूर्ण

/* assumes mmap_lock is ग_लिखो-locked */
व्योम arm_install_vdso(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ len;

	mm->context.vdso = 0;

	अगर (vdso_text_pagelist == शून्य)
		वापस;

	अगर (install_vvar(mm, addr))
		वापस;

	/* Account क्रम vvar page. */
	addr += PAGE_SIZE;
	len = (vdso_total_pages - 1) << PAGE_SHIFT;

	vma = _install_special_mapping(mm, addr, len,
		VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
		&vdso_text_mapping);

	अगर (!IS_ERR(vma))
		mm->context.vdso = addr;
पूर्ण

