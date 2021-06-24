<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * vdso setup क्रम s390
 *
 *  Copyright IBM Corp. 2008
 *  Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#समावेश <linux/binfmts.h>
#समावेश <linux/compat.h>
#समावेश <linux/elf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय_namespace.h>
#समावेश <vdso/datapage.h>
#समावेश <यंत्र/vdso.h>

बाह्य अक्षर vdso64_start[], vdso64_end[];
अटल अचिन्हित पूर्णांक vdso_pages;

अटल काष्ठा vm_special_mapping vvar_mapping;

अटल जोड़ अणु
	काष्ठा vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
पूर्ण vdso_data_store __page_aligned_data;

काष्ठा vdso_data *vdso_data = vdso_data_store.data;

क्रमागत vvar_pages अणु
	VVAR_DATA_PAGE_OFFSET,
	VVAR_TIMENS_PAGE_OFFSET,
	VVAR_NR_PAGES,
पूर्ण;

अचिन्हित पूर्णांक __पढ़ो_mostly vdso_enabled = 1;

अटल पूर्णांक __init vdso_setup(अक्षर *str)
अणु
	bool enabled;

	अगर (!kstrtobool(str, &enabled))
		vdso_enabled = enabled;
	वापस 1;
पूर्ण
__setup("vdso=", vdso_setup);

#अगर_घोषित CONFIG_TIME_NS
काष्ठा vdso_data *arch_get_vdso_data(व्योम *vvar_page)
अणु
	वापस (काष्ठा vdso_data *)(vvar_page);
पूर्ण

अटल काष्ठा page *find_समयns_vvar_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (likely(vma->vm_mm == current->mm))
		वापस current->nsproxy->समय_ns->vvar_page;
	/*
	 * VM_PFNMAP | VM_IO protect .fault() handler from being called
	 * through पूर्णांकerfaces like /proc/$pid/mem or
	 * process_vm_अणुपढ़ोv,ग_लिखोvपूर्ण() as दीर्घ as there's no .access()
	 * in special_mapping_vmops().
	 * For more details check_vma_flags() and __access_remote_vm()
	 */
	WARN(1, "vvar_page accessed remotely");
	वापस शून्य;
पूर्ण

/*
 * The VVAR page layout depends on whether a task beदीर्घs to the root or
 * non-root समय namespace. Whenever a task changes its namespace, the VVAR
 * page tables are cleared and then they will be re-faulted with a
 * corresponding layout.
 * See also the comment near समयns_setup_vdso_data() क्रम details.
 */
पूर्णांक vdso_join_समयns(काष्ठा task_काष्ठा *task, काष्ठा समय_namespace *ns)
अणु
	काष्ठा mm_काष्ठा *mm = task->mm;
	काष्ठा vm_area_काष्ठा *vma;

	mmap_पढ़ो_lock(mm);
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;

		अगर (!vma_is_special_mapping(vma, &vvar_mapping))
			जारी;
		zap_page_range(vma, vma->vm_start, size);
		अवरोध;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा page *find_समयns_vvar_page(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल vm_fault_t vvar_fault(स्थिर काष्ठा vm_special_mapping *sm,
			     काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *समयns_page = find_समयns_vvar_page(vma);
	अचिन्हित दीर्घ addr, pfn;
	vm_fault_t err;

	चयन (vmf->pgoff) अणु
	हाल VVAR_DATA_PAGE_OFFSET:
		pfn = virt_to_pfn(vdso_data);
		अगर (समयns_page) अणु
			/*
			 * Fault in VVAR page too, since it will be accessed
			 * to get घड़ी data anyway.
			 */
			addr = vmf->address + VVAR_TIMENS_PAGE_OFFSET * PAGE_SIZE;
			err = vmf_insert_pfn(vma, addr, pfn);
			अगर (unlikely(err & VM_FAULT_ERROR))
				वापस err;
			pfn = page_to_pfn(समयns_page);
		पूर्ण
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
		pfn = virt_to_pfn(vdso_data);
		अवरोध;
#पूर्ण_अगर /* CONFIG_TIME_NS */
	शेष:
		वापस VM_FAULT_SIGBUS;
	पूर्ण
	वापस vmf_insert_pfn(vma, vmf->address, pfn);
पूर्ण

अटल पूर्णांक vdso_mremap(स्थिर काष्ठा vm_special_mapping *sm,
		       काष्ठा vm_area_काष्ठा *vma)
अणु
	current->mm->context.vdso_base = vma->vm_start;
	वापस 0;
पूर्ण

अटल काष्ठा vm_special_mapping vvar_mapping = अणु
	.name = "[vvar]",
	.fault = vvar_fault,
पूर्ण;

अटल काष्ठा vm_special_mapping vdso_mapping = अणु
	.name = "[vdso]",
	.mremap = vdso_mremap,
पूर्ण;

पूर्णांक vdso_अ_लोpu_init(व्योम)
अणु
	set_tod_programmable_field(smp_processor_id());
	वापस 0;
पूर्ण
early_initcall(vdso_अ_लोpu_init); /* Must be called beक्रमe SMP init */

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	अचिन्हित दीर्घ vdso_text_len, vdso_mapping_len;
	अचिन्हित दीर्घ vvar_start, vdso_text_start;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक rc;

	BUILD_BUG_ON(VVAR_NR_PAGES != __VVAR_PAGES);
	अगर (!vdso_enabled || is_compat_task())
		वापस 0;
	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;
	vdso_text_len = vdso_pages << PAGE_SHIFT;
	vdso_mapping_len = vdso_text_len + VVAR_NR_PAGES * PAGE_SIZE;
	vvar_start = get_unmapped_area(शून्य, 0, vdso_mapping_len, 0, 0);
	rc = vvar_start;
	अगर (IS_ERR_VALUE(vvar_start))
		जाओ out;
	vma = _install_special_mapping(mm, vvar_start, VVAR_NR_PAGES*PAGE_SIZE,
				       VM_READ|VM_MAYREAD|VM_IO|VM_DONTDUMP|
				       VM_PFNMAP,
				       &vvar_mapping);
	rc = PTR_ERR(vma);
	अगर (IS_ERR(vma))
		जाओ out;
	vdso_text_start = vvar_start + VVAR_NR_PAGES * PAGE_SIZE;
	/* VM_MAYWRITE क्रम COW so gdb can set अवरोधpoपूर्णांकs */
	vma = _install_special_mapping(mm, vdso_text_start, vdso_text_len,
				       VM_READ|VM_EXEC|
				       VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				       &vdso_mapping);
	अगर (IS_ERR(vma)) अणु
		करो_munmap(mm, vvar_start, PAGE_SIZE, शून्य);
		rc = PTR_ERR(vma);
	पूर्ण अन्यथा अणु
		current->mm->context.vdso_base = vdso_text_start;
		rc = 0;
	पूर्ण
out:
	mmap_ग_लिखो_unlock(mm);
	वापस rc;
पूर्ण

अटल पूर्णांक __init vdso_init(व्योम)
अणु
	काष्ठा page **pages;
	पूर्णांक i;

	vdso_pages = (vdso64_end - vdso64_start) >> PAGE_SHIFT;
	pages = kसुस्मृति(vdso_pages + 1, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages) अणु
		vdso_enabled = 0;
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < vdso_pages; i++)
		pages[i] = virt_to_page(vdso64_start + i * PAGE_SIZE);
	pages[vdso_pages] = शून्य;
	vdso_mapping.pages = pages;
	वापस 0;
पूर्ण
arch_initcall(vdso_init);
