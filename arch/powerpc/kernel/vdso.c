<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 *    Copyright (C) 2004 Benjamin Herrenschmidt, IBM Corp.
 *			 <benh@kernel.crashing.org>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/slab.h>
#समावेश <linux/user.h>
#समावेश <linux/elf.h>
#समावेश <linux/security.h>
#समावेश <linux/memblock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/समय_namespace.h>
#समावेश <vdso/datapage.h>

#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/setup.h>

/* The alignment of the vDSO */
#घोषणा VDSO_ALIGNMENT	(1 << 16)

बाह्य अक्षर vdso32_start, vdso32_end;
बाह्य अक्षर vdso64_start, vdso64_end;

/*
 * The vdso data page (aka. प्रणालीcfg क्रम old ppc64 fans) is here.
 * Once the early boot kernel code no दीर्घer needs to muck around
 * with it, it will become dynamically allocated
 */
अटल जोड़ अणु
	काष्ठा vdso_arch_data	data;
	u8			page[PAGE_SIZE];
पूर्ण vdso_data_store __page_aligned_data;
काष्ठा vdso_arch_data *vdso_data = &vdso_data_store.data;

क्रमागत vvar_pages अणु
	VVAR_DATA_PAGE_OFFSET,
	VVAR_TIMENS_PAGE_OFFSET,
	VVAR_NR_PAGES,
पूर्ण;

अटल पूर्णांक vdso_mremap(स्थिर काष्ठा vm_special_mapping *sm, काष्ठा vm_area_काष्ठा *new_vma,
		       अचिन्हित दीर्घ text_size)
अणु
	अचिन्हित दीर्घ new_size = new_vma->vm_end - new_vma->vm_start;

	अगर (new_size != text_size)
		वापस -EINVAL;

	current->mm->context.vdso = (व्योम __user *)new_vma->vm_start;

	वापस 0;
पूर्ण

अटल पूर्णांक vdso32_mremap(स्थिर काष्ठा vm_special_mapping *sm, काष्ठा vm_area_काष्ठा *new_vma)
अणु
	वापस vdso_mremap(sm, new_vma, &vdso32_end - &vdso32_start);
पूर्ण

अटल पूर्णांक vdso64_mremap(स्थिर काष्ठा vm_special_mapping *sm, काष्ठा vm_area_काष्ठा *new_vma)
अणु
	वापस vdso_mremap(sm, new_vma, &vdso64_end - &vdso64_start);
पूर्ण

अटल vm_fault_t vvar_fault(स्थिर काष्ठा vm_special_mapping *sm,
			     काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf);

अटल काष्ठा vm_special_mapping vvar_spec __ro_after_init = अणु
	.name = "[vvar]",
	.fault = vvar_fault,
पूर्ण;

अटल काष्ठा vm_special_mapping vdso32_spec __ro_after_init = अणु
	.name = "[vdso]",
	.mremap = vdso32_mremap,
पूर्ण;

अटल काष्ठा vm_special_mapping vdso64_spec __ro_after_init = अणु
	.name = "[vdso]",
	.mremap = vdso64_mremap,
पूर्ण;

#अगर_घोषित CONFIG_TIME_NS
काष्ठा vdso_data *arch_get_vdso_data(व्योम *vvar_page)
अणु
	वापस ((काष्ठा vdso_arch_data *)vvar_page)->data;
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

		अगर (vma_is_special_mapping(vma, &vvar_spec))
			zap_page_range(vma, vma->vm_start, size);
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
			pfn = virt_to_pfn(vdso_data);
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

/*
 * This is called from binfmt_elf, we create the special vma क्रम the
 * vDSO and insert it पूर्णांकo the mm काष्ठा tree
 */
अटल पूर्णांक __arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	अचिन्हित दीर्घ vdso_size, vdso_base, mappings_size;
	काष्ठा vm_special_mapping *vdso_spec;
	अचिन्हित दीर्घ vvar_size = VVAR_NR_PAGES * PAGE_SIZE;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;

	अगर (is_32bit_task()) अणु
		vdso_spec = &vdso32_spec;
		vdso_size = &vdso32_end - &vdso32_start;
		vdso_base = VDSO32_MBASE;
	पूर्ण अन्यथा अणु
		vdso_spec = &vdso64_spec;
		vdso_size = &vdso64_end - &vdso64_start;
		/*
		 * On 64bit we करोn't have a preferred map address. This
		 * allows get_unmapped_area to find an area near other mmaps
		 * and most likely share a SLB entry.
		 */
		vdso_base = 0;
	पूर्ण

	mappings_size = vdso_size + vvar_size;
	mappings_size += (VDSO_ALIGNMENT - 1) & PAGE_MASK;

	/*
	 * pick a base address क्रम the vDSO in process space. We try to put it
	 * at vdso_base which is the "natural" base क्रम it, but we might fail
	 * and end up putting it अन्यथाwhere.
	 * Add enough to the size so that the result can be aligned.
	 */
	vdso_base = get_unmapped_area(शून्य, vdso_base, mappings_size, 0, 0);
	अगर (IS_ERR_VALUE(vdso_base))
		वापस vdso_base;

	/* Add required alignment. */
	vdso_base = ALIGN(vdso_base, VDSO_ALIGNMENT);

	/*
	 * Put vDSO base पूर्णांकo mm काष्ठा. We need to करो this beक्रमe calling
	 * install_special_mapping or the perf counter mmap tracking code
	 * will fail to recognise it as a vDSO.
	 */
	mm->context.vdso = (व्योम __user *)vdso_base + vvar_size;

	vma = _install_special_mapping(mm, vdso_base, vvar_size,
				       VM_READ | VM_MAYREAD | VM_IO |
				       VM_DONTDUMP | VM_PFNMAP, &vvar_spec);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	/*
	 * our vma flags करोn't have VM_WRITE so by default, the process isn't
	 * allowed to ग_लिखो those pages.
	 * gdb can अवरोध that with ptrace पूर्णांकerface, and thus trigger COW on
	 * those pages but it's then your responsibility to never करो that on
	 * the "data" page of the vDSO or you'll stop getting kernel updates
	 * and your nice userland समय_लोofday will be totally dead.
	 * It's fine to use that क्रम setting अवरोधpoपूर्णांकs in the vDSO code
	 * pages though.
	 */
	vma = _install_special_mapping(mm, vdso_base + vvar_size, vdso_size,
				       VM_READ | VM_EXEC | VM_MAYREAD |
				       VM_MAYWRITE | VM_MAYEXEC, vdso_spec);
	अगर (IS_ERR(vma))
		करो_munmap(mm, vdso_base, vvar_size, शून्य);

	वापस PTR_ERR_OR_ZERO(vma);
पूर्ण

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक rc;

	mm->context.vdso = शून्य;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	rc = __arch_setup_additional_pages(bprm, uses_पूर्णांकerp);
	अगर (rc)
		mm->context.vdso = शून्य;

	mmap_ग_लिखो_unlock(mm);
	वापस rc;
पूर्ण

#घोषणा VDSO_DO_FIXUPS(type, value, bits, sec) करो अणु					\
	व्योम *__start = (व्योम *)VDSO##bits##_SYMBOL(&vdso##bits##_start, sec##_start);	\
	व्योम *__end = (व्योम *)VDSO##bits##_SYMBOL(&vdso##bits##_start, sec##_end);	\
											\
	करो_##type##_fixups((value), __start, __end);					\
पूर्ण जबतक (0)

अटल व्योम __init vdso_fixup_features(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	VDSO_DO_FIXUPS(feature, cur_cpu_spec->cpu_features, 64, ftr_fixup);
	VDSO_DO_FIXUPS(feature, cur_cpu_spec->mmu_features, 64, mmu_ftr_fixup);
	VDSO_DO_FIXUPS(feature, घातerpc_firmware_features, 64, fw_ftr_fixup);
	VDSO_DO_FIXUPS(lwsync, cur_cpu_spec->cpu_features, 64, lwsync_fixup);
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_VDSO32
	VDSO_DO_FIXUPS(feature, cur_cpu_spec->cpu_features, 32, ftr_fixup);
	VDSO_DO_FIXUPS(feature, cur_cpu_spec->mmu_features, 32, mmu_ftr_fixup);
#अगर_घोषित CONFIG_PPC64
	VDSO_DO_FIXUPS(feature, घातerpc_firmware_features, 32, fw_ftr_fixup);
#पूर्ण_अगर /* CONFIG_PPC64 */
	VDSO_DO_FIXUPS(lwsync, cur_cpu_spec->cpu_features, 32, lwsync_fixup);
#पूर्ण_अगर
पूर्ण

/*
 * Called from setup_arch to initialize the biपंचांगap of available
 * syscalls in the प्रणालीcfg page
 */
अटल व्योम __init vdso_setup_syscall_map(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NR_syscalls; i++) अणु
		अगर (sys_call_table[i] != (अचिन्हित दीर्घ)&sys_ni_syscall)
			vdso_data->syscall_map[i >> 5] |= 0x80000000UL >> (i & 0x1f);
		अगर (IS_ENABLED(CONFIG_COMPAT) &&
		    compat_sys_call_table[i] != (अचिन्हित दीर्घ)&sys_ni_syscall)
			vdso_data->compat_syscall_map[i >> 5] |= 0x80000000UL >> (i & 0x1f);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC64
पूर्णांक vdso_अ_लोpu_init(व्योम)
अणु
	अचिन्हित दीर्घ cpu, node, val;

	/*
	 * SPRG_VDSO contains the CPU in the bottom 16 bits and the NUMA node
	 * in the next 16 bits.  The VDSO uses this to implement अ_लोpu().
	 */
	cpu = get_cpu();
	WARN_ON_ONCE(cpu > 0xffff);

	node = cpu_to_node(cpu);
	WARN_ON_ONCE(node > 0xffff);

	val = (cpu & 0xffff) | ((node & 0xffff) << 16);
	mtspr(SPRN_SPRG_VDSO_WRITE, val);
	get_paca()->sprg_vdso = val;

	put_cpu();

	वापस 0;
पूर्ण
/* We need to call this beक्रमe SMP init */
early_initcall(vdso_अ_लोpu_init);
#पूर्ण_अगर

अटल काष्ठा page ** __init vdso_setup_pages(व्योम *start, व्योम *end)
अणु
	पूर्णांक i;
	काष्ठा page **pagelist;
	पूर्णांक pages = (end - start) >> PAGE_SHIFT;

	pagelist = kसुस्मृति(pages + 1, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pagelist)
		panic("%s: Cannot allocate page list for VDSO", __func__);

	क्रम (i = 0; i < pages; i++)
		pagelist[i] = virt_to_page(start + i * PAGE_SIZE);

	वापस pagelist;
पूर्ण

अटल पूर्णांक __init vdso_init(व्योम)
अणु
#अगर_घोषित CONFIG_PPC64
	/*
	 * Fill up the "systemcfg" stuff क्रम backward compatibility
	 */
	म_नकल((अक्षर *)vdso_data->eye_catcher, "SYSTEMCFG:PPC64");
	vdso_data->version.major = SYSTEMCFG_MAJOR;
	vdso_data->version.minor = SYSTEMCFG_MINOR;
	vdso_data->processor = mfspr(SPRN_PVR);
	/*
	 * Fake the old platक्रमm number क्रम pSeries and add
	 * in LPAR bit अगर necessary
	 */
	vdso_data->platक्रमm = 0x100;
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		vdso_data->platक्रमm |= 1;
	vdso_data->physicalMemorySize = memblock_phys_mem_size();
	vdso_data->dcache_size = ppc64_caches.l1d.size;
	vdso_data->dcache_line_size = ppc64_caches.l1d.line_size;
	vdso_data->icache_size = ppc64_caches.l1i.size;
	vdso_data->icache_line_size = ppc64_caches.l1i.line_size;
	vdso_data->dcache_block_size = ppc64_caches.l1d.block_size;
	vdso_data->icache_block_size = ppc64_caches.l1i.block_size;
	vdso_data->dcache_log_block_size = ppc64_caches.l1d.log_block_size;
	vdso_data->icache_log_block_size = ppc64_caches.l1i.log_block_size;
#पूर्ण_अगर /* CONFIG_PPC64 */

	vdso_setup_syscall_map();

	vdso_fixup_features();

	अगर (IS_ENABLED(CONFIG_VDSO32))
		vdso32_spec.pages = vdso_setup_pages(&vdso32_start, &vdso32_end);

	अगर (IS_ENABLED(CONFIG_PPC64))
		vdso64_spec.pages = vdso_setup_pages(&vdso64_start, &vdso64_end);

	smp_wmb();

	वापस 0;
पूर्ण
arch_initcall(vdso_init);
