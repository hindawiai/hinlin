<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Set up the VMAs to tell the VM about the vDSO.
 * Copyright 2007 Andi Kleen, SUSE Lअसल.
 */

/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/elf.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/vvar.h>
#समावेश <यंत्र/page.h>

अचिन्हित पूर्णांक __पढ़ो_mostly vdso_enabled = 1;

अटल काष्ठा vm_special_mapping vvar_mapping = अणु
	.name = "[vvar]"
पूर्ण;

#अगर_घोषित	CONFIG_SPARC64
अटल काष्ठा vm_special_mapping vdso_mapping64 = अणु
	.name = "[vdso]"
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
अटल काष्ठा vm_special_mapping vdso_mapping32 = अणु
	.name = "[vdso]"
पूर्ण;
#पूर्ण_अगर

काष्ठा vvar_data *vvar_data;

काष्ठा vdso_elfinfo32 अणु
	Elf32_Ehdr	*hdr;
	Elf32_Sym	*dynsym;
	अचिन्हित दीर्घ	dynsymsize;
	स्थिर अक्षर	*dynstr;
	अचिन्हित दीर्घ	text;
पूर्ण;

काष्ठा vdso_elfinfo64 अणु
	Elf64_Ehdr	*hdr;
	Elf64_Sym	*dynsym;
	अचिन्हित दीर्घ	dynsymsize;
	स्थिर अक्षर	*dynstr;
	अचिन्हित दीर्घ	text;
पूर्ण;

काष्ठा vdso_elfinfo अणु
	जोड़ अणु
		काष्ठा vdso_elfinfo32 elf32;
		काष्ठा vdso_elfinfo64 elf64;
	पूर्ण u;
पूर्ण;

अटल व्योम *one_section64(काष्ठा vdso_elfinfo64 *e, स्थिर अक्षर *name,
			   अचिन्हित दीर्घ *size)
अणु
	स्थिर अक्षर *snames;
	Elf64_Shdr *shdrs;
	अचिन्हित पूर्णांक i;

	shdrs = (व्योम *)e->hdr + e->hdr->e_shoff;
	snames = (व्योम *)e->hdr + shdrs[e->hdr->e_shstrndx].sh_offset;
	क्रम (i = 1; i < e->hdr->e_shnum; i++) अणु
		अगर (!म_भेद(snames+shdrs[i].sh_name, name)) अणु
			अगर (size)
				*size = shdrs[i].sh_size;
			वापस (व्योम *)e->hdr + shdrs[i].sh_offset;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक find_sections64(स्थिर काष्ठा vdso_image *image, काष्ठा vdso_elfinfo *_e)
अणु
	काष्ठा vdso_elfinfo64 *e = &_e->u.elf64;

	e->hdr = image->data;
	e->dynsym = one_section64(e, ".dynsym", &e->dynsymsize);
	e->dynstr = one_section64(e, ".dynstr", शून्य);

	अगर (!e->dynsym || !e->dynstr) अणु
		pr_err("VDSO64: Missing symbol sections.\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल Elf64_Sym *find_sym64(स्थिर काष्ठा vdso_elfinfo64 *e, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < (e->dynsymsize / माप(Elf64_Sym)); i++) अणु
		Elf64_Sym *s = &e->dynsym[i];
		अगर (s->st_name == 0)
			जारी;
		अगर (!म_भेद(e->dynstr + s->st_name, name))
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक patchsym64(काष्ठा vdso_elfinfo *_e, स्थिर अक्षर *orig,
		      स्थिर अक्षर *new)
अणु
	काष्ठा vdso_elfinfo64 *e = &_e->u.elf64;
	Elf64_Sym *osym = find_sym64(e, orig);
	Elf64_Sym *nsym = find_sym64(e, new);

	अगर (!nsym || !osym) अणु
		pr_err("VDSO64: Missing symbols.\n");
		वापस -ENODEV;
	पूर्ण
	osym->st_value = nsym->st_value;
	osym->st_size = nsym->st_size;
	osym->st_info = nsym->st_info;
	osym->st_other = nsym->st_other;
	osym->st_shndx = nsym->st_shndx;

	वापस 0;
पूर्ण

अटल व्योम *one_section32(काष्ठा vdso_elfinfo32 *e, स्थिर अक्षर *name,
			   अचिन्हित दीर्घ *size)
अणु
	स्थिर अक्षर *snames;
	Elf32_Shdr *shdrs;
	अचिन्हित पूर्णांक i;

	shdrs = (व्योम *)e->hdr + e->hdr->e_shoff;
	snames = (व्योम *)e->hdr + shdrs[e->hdr->e_shstrndx].sh_offset;
	क्रम (i = 1; i < e->hdr->e_shnum; i++) अणु
		अगर (!म_भेद(snames+shdrs[i].sh_name, name)) अणु
			अगर (size)
				*size = shdrs[i].sh_size;
			वापस (व्योम *)e->hdr + shdrs[i].sh_offset;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक find_sections32(स्थिर काष्ठा vdso_image *image, काष्ठा vdso_elfinfo *_e)
अणु
	काष्ठा vdso_elfinfo32 *e = &_e->u.elf32;

	e->hdr = image->data;
	e->dynsym = one_section32(e, ".dynsym", &e->dynsymsize);
	e->dynstr = one_section32(e, ".dynstr", शून्य);

	अगर (!e->dynsym || !e->dynstr) अणु
		pr_err("VDSO32: Missing symbol sections.\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल Elf32_Sym *find_sym32(स्थिर काष्ठा vdso_elfinfo32 *e, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < (e->dynsymsize / माप(Elf32_Sym)); i++) अणु
		Elf32_Sym *s = &e->dynsym[i];
		अगर (s->st_name == 0)
			जारी;
		अगर (!म_भेद(e->dynstr + s->st_name, name))
			वापस s;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक patchsym32(काष्ठा vdso_elfinfo *_e, स्थिर अक्षर *orig,
		      स्थिर अक्षर *new)
अणु
	काष्ठा vdso_elfinfo32 *e = &_e->u.elf32;
	Elf32_Sym *osym = find_sym32(e, orig);
	Elf32_Sym *nsym = find_sym32(e, new);

	अगर (!nsym || !osym) अणु
		pr_err("VDSO32: Missing symbols.\n");
		वापस -ENODEV;
	पूर्ण
	osym->st_value = nsym->st_value;
	osym->st_size = nsym->st_size;
	osym->st_info = nsym->st_info;
	osym->st_other = nsym->st_other;
	osym->st_shndx = nsym->st_shndx;

	वापस 0;
पूर्ण

अटल पूर्णांक find_sections(स्थिर काष्ठा vdso_image *image, काष्ठा vdso_elfinfo *e,
			 bool elf64)
अणु
	अगर (elf64)
		वापस find_sections64(image, e);
	अन्यथा
		वापस find_sections32(image, e);
पूर्ण

अटल पूर्णांक patch_one_symbol(काष्ठा vdso_elfinfo *e, स्थिर अक्षर *orig,
			    स्थिर अक्षर *new_target, bool elf64)
अणु
	अगर (elf64)
		वापस patchsym64(e, orig, new_target);
	अन्यथा
		वापस patchsym32(e, orig, new_target);
पूर्ण

अटल पूर्णांक stick_patch(स्थिर काष्ठा vdso_image *image, काष्ठा vdso_elfinfo *e, bool elf64)
अणु
	पूर्णांक err;

	err = find_sections(image, e, elf64);
	अगर (err)
		वापस err;

	err = patch_one_symbol(e,
			       "__vdso_gettimeofday",
			       "__vdso_gettimeofday_stick", elf64);
	अगर (err)
		वापस err;

	वापस patch_one_symbol(e,
				"__vdso_clock_gettime",
				"__vdso_clock_gettime_stick", elf64);
	वापस 0;
पूर्ण

/*
 * Allocate pages क्रम the vdso and vvar, and copy in the vdso text from the
 * kernel image.
 */
पूर्णांक __init init_vdso_image(स्थिर काष्ठा vdso_image *image,
			   काष्ठा vm_special_mapping *vdso_mapping, bool elf64)
अणु
	पूर्णांक cnpages = (image->size) / PAGE_SIZE;
	काष्ठा page *dp, **dpp = शून्य;
	काष्ठा page *cp, **cpp = शून्य;
	काष्ठा vdso_elfinfo ei;
	पूर्णांक i, dnpages = 0;

	अगर (tlb_type != spitfire) अणु
		पूर्णांक err = stick_patch(image, &ei, elf64);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * First, the vdso text.  This is initialied data, an पूर्णांकegral number of
	 * pages दीर्घ.
	 */
	अगर (WARN_ON(image->size % PAGE_SIZE != 0))
		जाओ oom;

	cpp = kसुस्मृति(cnpages, माप(काष्ठा page *), GFP_KERNEL);
	vdso_mapping->pages = cpp;

	अगर (!cpp)
		जाओ oom;

	क्रम (i = 0; i < cnpages; i++) अणु
		cp = alloc_page(GFP_KERNEL);
		अगर (!cp)
			जाओ oom;
		cpp[i] = cp;
		copy_page(page_address(cp), image->data + i * PAGE_SIZE);
	पूर्ण

	/*
	 * Now the vvar page.  This is uninitialized data.
	 */

	अगर (vvar_data == शून्य) अणु
		dnpages = (माप(काष्ठा vvar_data) / PAGE_SIZE) + 1;
		अगर (WARN_ON(dnpages != 1))
			जाओ oom;
		dpp = kसुस्मृति(dnpages, माप(काष्ठा page *), GFP_KERNEL);
		vvar_mapping.pages = dpp;

		अगर (!dpp)
			जाओ oom;

		dp = alloc_page(GFP_KERNEL);
		अगर (!dp)
			जाओ oom;

		dpp[0] = dp;
		vvar_data = page_address(dp);
		स_रखो(vvar_data, 0, PAGE_SIZE);

		vvar_data->seq = 0;
	पूर्ण

	वापस 0;
 oom:
	अगर (cpp != शून्य) अणु
		क्रम (i = 0; i < cnpages; i++) अणु
			अगर (cpp[i] != शून्य)
				__मुक्त_page(cpp[i]);
		पूर्ण
		kमुक्त(cpp);
		vdso_mapping->pages = शून्य;
	पूर्ण

	अगर (dpp != शून्य) अणु
		क्रम (i = 0; i < dnpages; i++) अणु
			अगर (dpp[i] != शून्य)
				__मुक्त_page(dpp[i]);
		पूर्ण
		kमुक्त(dpp);
		vvar_mapping.pages = शून्य;
	पूर्ण

	pr_warn("Cannot allocate vdso\n");
	vdso_enabled = 0;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init init_vdso(व्योम)
अणु
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_SPARC64
	err = init_vdso_image(&vdso_image_64_builtin, &vdso_mapping64, true);
	अगर (err)
		वापस err;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT
	err = init_vdso_image(&vdso_image_32_builtin, &vdso_mapping32, false);
#पूर्ण_अगर
	वापस err;

पूर्ण
subsys_initcall(init_vdso);

काष्ठा linux_binprm;

/* Shuffle the vdso up a bit, अक्रमomly. */
अटल अचिन्हित दीर्घ vdso_addr(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक offset;

	/* This loses some more bits than a modulo, but is cheaper */
	offset = get_अक्रमom_पूर्णांक() & (PTRS_PER_PTE - 1);
	वापस start + (offset << PAGE_SHIFT);
पूर्ण

अटल पूर्णांक map_vdso(स्थिर काष्ठा vdso_image *image,
		काष्ठा vm_special_mapping *vdso_mapping)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ text_start, addr = 0;
	पूर्णांक ret = 0;

	mmap_ग_लिखो_lock(mm);

	/*
	 * First, get an unmapped region: then अक्रमomize it, and make sure that
	 * region is मुक्त.
	 */
	अगर (current->flags & PF_RANDOMIZE) अणु
		addr = get_unmapped_area(शून्य, 0,
					 image->size - image->sym_vvar_start,
					 0, 0);
		अगर (IS_ERR_VALUE(addr)) अणु
			ret = addr;
			जाओ up_fail;
		पूर्ण
		addr = vdso_addr(addr, image->size - image->sym_vvar_start);
	पूर्ण
	addr = get_unmapped_area(शून्य, addr,
				 image->size - image->sym_vvar_start, 0, 0);
	अगर (IS_ERR_VALUE(addr)) अणु
		ret = addr;
		जाओ up_fail;
	पूर्ण

	text_start = addr - image->sym_vvar_start;
	current->mm->context.vdso = (व्योम __user *)text_start;

	/*
	 * MAYWRITE to allow gdb to COW and set अवरोधpoपूर्णांकs
	 */
	vma = _install_special_mapping(mm,
				       text_start,
				       image->size,
				       VM_READ|VM_EXEC|
				       VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				       vdso_mapping);

	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ up_fail;
	पूर्ण

	vma = _install_special_mapping(mm,
				       addr,
				       -image->sym_vvar_start,
				       VM_READ|VM_MAYREAD,
				       &vvar_mapping);

	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		करो_munmap(mm, text_start, image->size, शून्य);
	पूर्ण

up_fail:
	अगर (ret)
		current->mm->context.vdso = शून्य;

	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु

	अगर (!vdso_enabled)
		वापस 0;

#अगर defined CONFIG_COMPAT
	अगर (!(is_32bit_task()))
		वापस map_vdso(&vdso_image_64_builtin, &vdso_mapping64);
	अन्यथा
		वापस map_vdso(&vdso_image_32_builtin, &vdso_mapping32);
#अन्यथा
	वापस map_vdso(&vdso_image_64_builtin, &vdso_mapping64);
#पूर्ण_अगर

पूर्ण

अटल __init पूर्णांक vdso_setup(अक्षर *s)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ val;

	err = kम_से_अदीर्घ(s, 10, &val);
	अगर (err)
		वापस err;
	vdso_enabled = val;
	वापस 0;
पूर्ण
__setup("vdso=", vdso_setup);
