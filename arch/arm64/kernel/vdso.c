<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VDSO implementations.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/cache.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/elf.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <vdso/datapage.h>
#समावेश <vdso/helpers.h>
#समावेश <vdso/vsyscall.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/संकेत32.h>
#समावेश <यंत्र/vdso.h>

बाह्य अक्षर vdso_start[], vdso_end[];
बाह्य अक्षर vdso32_start[], vdso32_end[];

क्रमागत vdso_abi अणु
	VDSO_ABI_AA64,
	VDSO_ABI_AA32,
पूर्ण;

क्रमागत vvar_pages अणु
	VVAR_DATA_PAGE_OFFSET,
	VVAR_TIMENS_PAGE_OFFSET,
	VVAR_NR_PAGES,
पूर्ण;

काष्ठा vdso_abi_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *vdso_code_start;
	स्थिर अक्षर *vdso_code_end;
	अचिन्हित दीर्घ vdso_pages;
	/* Data Mapping */
	काष्ठा vm_special_mapping *dm;
	/* Code Mapping */
	काष्ठा vm_special_mapping *cm;
पूर्ण;

अटल काष्ठा vdso_abi_info vdso_info[] __ro_after_init = अणु
	[VDSO_ABI_AA64] = अणु
		.name = "vdso",
		.vdso_code_start = vdso_start,
		.vdso_code_end = vdso_end,
	पूर्ण,
#अगर_घोषित CONFIG_COMPAT_VDSO
	[VDSO_ABI_AA32] = अणु
		.name = "vdso32",
		.vdso_code_start = vdso32_start,
		.vdso_code_end = vdso32_end,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_COMPAT_VDSO */
पूर्ण;

/*
 * The vDSO data page.
 */
अटल जोड़ अणु
	काष्ठा vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
पूर्ण vdso_data_store __page_aligned_data;
काष्ठा vdso_data *vdso_data = vdso_data_store.data;

अटल पूर्णांक vdso_mremap(स्थिर काष्ठा vm_special_mapping *sm,
		काष्ठा vm_area_काष्ठा *new_vma)
अणु
	current->mm->context.vdso = (व्योम *)new_vma->vm_start;

	वापस 0;
पूर्ण

अटल पूर्णांक __init __vdso_init(क्रमागत vdso_abi abi)
अणु
	पूर्णांक i;
	काष्ठा page **vdso_pagelist;
	अचिन्हित दीर्घ pfn;

	अगर (स_भेद(vdso_info[abi].vdso_code_start, "\177ELF", 4)) अणु
		pr_err("vDSO is not a valid ELF object!\n");
		वापस -EINVAL;
	पूर्ण

	vdso_info[abi].vdso_pages = (
			vdso_info[abi].vdso_code_end -
			vdso_info[abi].vdso_code_start) >>
			PAGE_SHIFT;

	vdso_pagelist = kसुस्मृति(vdso_info[abi].vdso_pages,
				माप(काष्ठा page *),
				GFP_KERNEL);
	अगर (vdso_pagelist == शून्य)
		वापस -ENOMEM;

	/* Grab the vDSO code pages. */
	pfn = sym_to_pfn(vdso_info[abi].vdso_code_start);

	क्रम (i = 0; i < vdso_info[abi].vdso_pages; i++)
		vdso_pagelist[i] = pfn_to_page(pfn + i);

	vdso_info[abi].cm->pages = vdso_pagelist;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
काष्ठा vdso_data *arch_get_vdso_data(व्योम *vvar_page)
अणु
	वापस (काष्ठा vdso_data *)(vvar_page);
पूर्ण

/*
 * The vvar mapping contains data क्रम a specअगरic समय namespace, so when a task
 * changes namespace we must unmap its vvar data क्रम the old namespace.
 * Subsequent faults will map in data क्रम the new namespace.
 *
 * For more details see समयns_setup_vdso_data().
 */
पूर्णांक vdso_join_समयns(काष्ठा task_काष्ठा *task, काष्ठा समय_namespace *ns)
अणु
	काष्ठा mm_काष्ठा *mm = task->mm;
	काष्ठा vm_area_काष्ठा *vma;

	mmap_पढ़ो_lock(mm);

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;

		अगर (vma_is_special_mapping(vma, vdso_info[VDSO_ABI_AA64].dm))
			zap_page_range(vma, vma->vm_start, size);
#अगर_घोषित CONFIG_COMPAT_VDSO
		अगर (vma_is_special_mapping(vma, vdso_info[VDSO_ABI_AA32].dm))
			zap_page_range(vma, vma->vm_start, size);
#पूर्ण_अगर
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	वापस 0;
पूर्ण

अटल काष्ठा page *find_समयns_vvar_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->vm_mm == current->mm))
		वापस current->nsproxy->समय_ns->vvar_page;

	/*
	 * VM_PFNMAP | VM_IO protect .fault() handler from being called
	 * through पूर्णांकerfaces like /proc/$pid/mem or
	 * process_vm_अणुपढ़ोv,ग_लिखोvपूर्ण() as दीर्घ as there's no .access()
	 * in special_mapping_vmops.
	 * For more details check_vma_flags() and __access_remote_vm()
	 */
	WARN(1, "vvar_page accessed remotely");

	वापस शून्य;
पूर्ण
#अन्यथा
अटल काष्ठा page *find_समयns_vvar_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल vm_fault_t vvar_fault(स्थिर काष्ठा vm_special_mapping *sm,
			     काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *समयns_page = find_समयns_vvar_page(vma);
	अचिन्हित दीर्घ pfn;

	चयन (vmf->pgoff) अणु
	हाल VVAR_DATA_PAGE_OFFSET:
		अगर (समयns_page)
			pfn = page_to_pfn(समयns_page);
		अन्यथा
			pfn = sym_to_pfn(vdso_data);
		अवरोध;
#अगर_घोषित CONFIG_TIME_NS
	हाल VVAR_TIMENS_PAGE_OFFSET:
		/*
		 * If a task beदीर्घs to a समय namespace then a namespace
		 * specअगरic VVAR is mapped with the VVAR_DATA_PAGE_OFFSET and
		 * the real VVAR page is mapped with the VVAR_TIMENS_PAGE_OFFSET
		 * offset.
		 * See also the comment near समयns_setup_vdso_data().
		 */
		अगर (!समयns_page)
			वापस VM_FAULT_SIGBUS;
		pfn = sym_to_pfn(vdso_data);
		अवरोध;
#पूर्ण_अगर /* CONFIG_TIME_NS */
	शेष:
		वापस VM_FAULT_SIGBUS;
	पूर्ण

	वापस vmf_insert_pfn(vma, vmf->address, pfn);
पूर्ण

अटल पूर्णांक __setup_additional_pages(क्रमागत vdso_abi abi,
				    काष्ठा mm_काष्ठा *mm,
				    काष्ठा linux_binprm *bprm,
				    पूर्णांक uses_पूर्णांकerp)
अणु
	अचिन्हित दीर्घ vdso_base, vdso_text_len, vdso_mapping_len;
	अचिन्हित दीर्घ gp_flags = 0;
	व्योम *ret;

	BUILD_BUG_ON(VVAR_NR_PAGES != __VVAR_PAGES);

	vdso_text_len = vdso_info[abi].vdso_pages << PAGE_SHIFT;
	/* Be sure to map the data page */
	vdso_mapping_len = vdso_text_len + VVAR_NR_PAGES * PAGE_SIZE;

	vdso_base = get_unmapped_area(शून्य, 0, vdso_mapping_len, 0, 0);
	अगर (IS_ERR_VALUE(vdso_base)) अणु
		ret = ERR_PTR(vdso_base);
		जाओ up_fail;
	पूर्ण

	ret = _install_special_mapping(mm, vdso_base, VVAR_NR_PAGES * PAGE_SIZE,
				       VM_READ|VM_MAYREAD|VM_PFNMAP,
				       vdso_info[abi].dm);
	अगर (IS_ERR(ret))
		जाओ up_fail;

	अगर (IS_ENABLED(CONFIG_ARM64_BTI_KERNEL) && प्रणाली_supports_bti())
		gp_flags = VM_ARM64_BTI;

	vdso_base += VVAR_NR_PAGES * PAGE_SIZE;
	mm->context.vdso = (व्योम *)vdso_base;
	ret = _install_special_mapping(mm, vdso_base, vdso_text_len,
				       VM_READ|VM_EXEC|gp_flags|
				       VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				       vdso_info[abi].cm);
	अगर (IS_ERR(ret))
		जाओ up_fail;

	वापस 0;

up_fail:
	mm->context.vdso = शून्य;
	वापस PTR_ERR(ret);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Create and map the vectors page क्रम AArch32 tasks.
 */
क्रमागत aarch32_map अणु
	AA32_MAP_VECTORS, /* kuser helpers */
	AA32_MAP_SIGPAGE,
	AA32_MAP_VVAR,
	AA32_MAP_VDSO,
पूर्ण;

अटल काष्ठा page *aarch32_vectors_page __ro_after_init;
अटल काष्ठा page *aarch32_sig_page __ro_after_init;

अटल पूर्णांक aarch32_sigpage_mremap(स्थिर काष्ठा vm_special_mapping *sm,
				  काष्ठा vm_area_काष्ठा *new_vma)
अणु
	current->mm->context.sigpage = (व्योम *)new_vma->vm_start;

	वापस 0;
पूर्ण

अटल काष्ठा vm_special_mapping aarch32_vdso_maps[] = अणु
	[AA32_MAP_VECTORS] = अणु
		.name	= "[vectors]", /* ABI */
		.pages	= &aarch32_vectors_page,
	पूर्ण,
	[AA32_MAP_SIGPAGE] = अणु
		.name	= "[sigpage]", /* ABI */
		.pages	= &aarch32_sig_page,
		.mremap	= aarch32_sigpage_mremap,
	पूर्ण,
	[AA32_MAP_VVAR] = अणु
		.name = "[vvar]",
		.fault = vvar_fault,
	पूर्ण,
	[AA32_MAP_VDSO] = अणु
		.name = "[vdso]",
		.mremap = vdso_mremap,
	पूर्ण,
पूर्ण;

अटल पूर्णांक aarch32_alloc_kuser_vdso_page(व्योम)
अणु
	बाह्य अक्षर __kuser_helper_start[], __kuser_helper_end[];
	पूर्णांक kuser_sz = __kuser_helper_end - __kuser_helper_start;
	अचिन्हित दीर्घ vdso_page;

	अगर (!IS_ENABLED(CONFIG_KUSER_HELPERS))
		वापस 0;

	vdso_page = get_zeroed_page(GFP_KERNEL);
	अगर (!vdso_page)
		वापस -ENOMEM;

	स_नकल((व्योम *)(vdso_page + 0x1000 - kuser_sz), __kuser_helper_start,
	       kuser_sz);
	aarch32_vectors_page = virt_to_page(vdso_page);
	वापस 0;
पूर्ण

#घोषणा COMPAT_SIGPAGE_POISON_WORD	0xe7fddef1
अटल पूर्णांक aarch32_alloc_sigpage(व्योम)
अणु
	बाह्य अक्षर __aarch32_sigret_code_start[], __aarch32_sigret_code_end[];
	पूर्णांक sigret_sz = __aarch32_sigret_code_end - __aarch32_sigret_code_start;
	__le32 poison = cpu_to_le32(COMPAT_SIGPAGE_POISON_WORD);
	व्योम *sigpage;

	sigpage = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!sigpage)
		वापस -ENOMEM;

	स_रखो32(sigpage, (__क्रमce u32)poison, PAGE_SIZE / माप(poison));
	स_नकल(sigpage, __aarch32_sigret_code_start, sigret_sz);
	aarch32_sig_page = virt_to_page(sigpage);
	वापस 0;
पूर्ण

अटल पूर्णांक __init __aarch32_alloc_vdso_pages(व्योम)
अणु

	अगर (!IS_ENABLED(CONFIG_COMPAT_VDSO))
		वापस 0;

	vdso_info[VDSO_ABI_AA32].dm = &aarch32_vdso_maps[AA32_MAP_VVAR];
	vdso_info[VDSO_ABI_AA32].cm = &aarch32_vdso_maps[AA32_MAP_VDSO];

	वापस __vdso_init(VDSO_ABI_AA32);
पूर्ण

अटल पूर्णांक __init aarch32_alloc_vdso_pages(व्योम)
अणु
	पूर्णांक ret;

	ret = __aarch32_alloc_vdso_pages();
	अगर (ret)
		वापस ret;

	ret = aarch32_alloc_sigpage();
	अगर (ret)
		वापस ret;

	वापस aarch32_alloc_kuser_vdso_page();
पूर्ण
arch_initcall(aarch32_alloc_vdso_pages);

अटल पूर्णांक aarch32_kuser_helpers_setup(काष्ठा mm_काष्ठा *mm)
अणु
	व्योम *ret;

	अगर (!IS_ENABLED(CONFIG_KUSER_HELPERS))
		वापस 0;

	/*
	 * Aव्योम VM_MAYWRITE क्रम compatibility with arch/arm/, where it's
	 * not safe to CoW the page containing the CPU exception vectors.
	 */
	ret = _install_special_mapping(mm, AARCH32_VECTORS_BASE, PAGE_SIZE,
				       VM_READ | VM_EXEC |
				       VM_MAYREAD | VM_MAYEXEC,
				       &aarch32_vdso_maps[AA32_MAP_VECTORS]);

	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

अटल पूर्णांक aarch32_sigवापस_setup(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ addr;
	व्योम *ret;

	addr = get_unmapped_area(शून्य, 0, PAGE_SIZE, 0, 0);
	अगर (IS_ERR_VALUE(addr)) अणु
		ret = ERR_PTR(addr);
		जाओ out;
	पूर्ण

	/*
	 * VM_MAYWRITE is required to allow gdb to Copy-on-Write and
	 * set अवरोधpoपूर्णांकs.
	 */
	ret = _install_special_mapping(mm, addr, PAGE_SIZE,
				       VM_READ | VM_EXEC | VM_MAYREAD |
				       VM_MAYWRITE | VM_MAYEXEC,
				       &aarch32_vdso_maps[AA32_MAP_SIGPAGE]);
	अगर (IS_ERR(ret))
		जाओ out;

	mm->context.sigpage = (व्योम *)addr;

out:
	वापस PTR_ERR_OR_ZERO(ret);
पूर्ण

पूर्णांक aarch32_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	ret = aarch32_kuser_helpers_setup(mm);
	अगर (ret)
		जाओ out;

	अगर (IS_ENABLED(CONFIG_COMPAT_VDSO)) अणु
		ret = __setup_additional_pages(VDSO_ABI_AA32, mm, bprm,
					       uses_पूर्णांकerp);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = aarch32_sigवापस_setup(mm);
out:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

क्रमागत aarch64_map अणु
	AA64_MAP_VVAR,
	AA64_MAP_VDSO,
पूर्ण;

अटल काष्ठा vm_special_mapping aarch64_vdso_maps[] __ro_after_init = अणु
	[AA64_MAP_VVAR] = अणु
		.name	= "[vvar]",
		.fault = vvar_fault,
	पूर्ण,
	[AA64_MAP_VDSO] = अणु
		.name	= "[vdso]",
		.mremap = vdso_mremap,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vdso_init(व्योम)
अणु
	vdso_info[VDSO_ABI_AA64].dm = &aarch64_vdso_maps[AA64_MAP_VVAR];
	vdso_info[VDSO_ABI_AA64].cm = &aarch64_vdso_maps[AA64_MAP_VDSO];

	वापस __vdso_init(VDSO_ABI_AA64);
पूर्ण
arch_initcall(vdso_init);

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	ret = __setup_additional_pages(VDSO_ABI_AA64, mm, bprm, uses_पूर्णांकerp);
	mmap_ग_लिखो_unlock(mm);

	वापस ret;
पूर्ण
