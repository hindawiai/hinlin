<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 * Copyright (C) 2012 ARM Limited
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#समावेश <linux/elf.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/err.h>
#समावेश <यंत्र/page.h>
#अगर_घोषित CONFIG_GENERIC_TIME_VSYSCALL
#समावेश <vdso/datapage.h>
#अन्यथा
#समावेश <यंत्र/vdso.h>
#पूर्ण_अगर

बाह्य अक्षर vdso_start[], vdso_end[];

अटल अचिन्हित पूर्णांक vdso_pages __ro_after_init;
अटल काष्ठा page **vdso_pagelist __ro_after_init;

/*
 * The vDSO data page.
 */
अटल जोड़ अणु
	काष्ठा vdso_data	data;
	u8			page[PAGE_SIZE];
पूर्ण vdso_data_store __page_aligned_data;
काष्ठा vdso_data *vdso_data = &vdso_data_store.data;

अटल पूर्णांक __init vdso_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	vdso_pages = (vdso_end - vdso_start) >> PAGE_SHIFT;
	vdso_pagelist =
		kसुस्मृति(vdso_pages + 1, माप(काष्ठा page *), GFP_KERNEL);
	अगर (unlikely(vdso_pagelist == शून्य)) अणु
		pr_err("vdso: pagelist allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < vdso_pages; i++) अणु
		काष्ठा page *pg;

		pg = virt_to_page(vdso_start + (i << PAGE_SHIFT));
		vdso_pagelist[i] = pg;
	पूर्ण
	vdso_pagelist[i] = virt_to_page(vdso_data);

	वापस 0;
पूर्ण
arch_initcall(vdso_init);

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
	पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ vdso_base, vdso_len;
	पूर्णांक ret;

	vdso_len = (vdso_pages + 1) << PAGE_SHIFT;

	mmap_ग_लिखो_lock(mm);
	vdso_base = get_unmapped_area(शून्य, 0, vdso_len, 0, 0);
	अगर (IS_ERR_VALUE(vdso_base)) अणु
		ret = vdso_base;
		जाओ end;
	पूर्ण

	/*
	 * Put vDSO base पूर्णांकo mm काष्ठा. We need to करो this beक्रमe calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO (since arch_vma_name fails).
	 */
	mm->context.vdso = (व्योम *)vdso_base;

	ret =
	   install_special_mapping(mm, vdso_base, vdso_pages << PAGE_SHIFT,
		(VM_READ | VM_EXEC | VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC),
		vdso_pagelist);

	अगर (unlikely(ret)) अणु
		mm->context.vdso = शून्य;
		जाओ end;
	पूर्ण

	vdso_base += (vdso_pages << PAGE_SHIFT);
	ret = install_special_mapping(mm, vdso_base, PAGE_SIZE,
		(VM_READ | VM_MAYREAD), &vdso_pagelist[vdso_pages]);

	अगर (unlikely(ret))
		mm->context.vdso = शून्य;
end:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_mm && (vma->vm_start == (दीर्घ)vma->vm_mm->context.vdso))
		वापस "[vdso]";
	अगर (vma->vm_mm && (vma->vm_start ==
			   (दीर्घ)vma->vm_mm->context.vdso + PAGE_SIZE))
		वापस "[vdso_data]";
	वापस शून्य;
पूर्ण
