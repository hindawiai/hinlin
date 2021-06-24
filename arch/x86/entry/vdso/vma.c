<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007 Andi Kleen, SUSE Lअसल.
 *
 * This contains most of the x86 vDSO kernel-side code.
 */
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/elf.h>
#समावेश <linux/cpu.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/समय_namespace.h>

#समावेश <यंत्र/pvघड़ी.h>
#समावेश <यंत्र/vgtod.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/vvar.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <घड़ीsource/hyperv_समयr.h>

#अघोषित _ASM_X86_VVAR_H
#घोषणा EMIT_VVAR(name, offset)	\
	स्थिर माप_प्रकार name ## _offset = offset;
#समावेश <यंत्र/vvar.h>

काष्ठा vdso_data *arch_get_vdso_data(व्योम *vvar_page)
अणु
	वापस (काष्ठा vdso_data *)(vvar_page + _vdso_data_offset);
पूर्ण
#अघोषित EMIT_VVAR

अचिन्हित पूर्णांक vघड़ीs_used __पढ़ो_mostly;

#अगर defined(CONFIG_X86_64)
अचिन्हित पूर्णांक __पढ़ो_mostly vdso64_enabled = 1;
#पूर्ण_अगर

व्योम __init init_vdso_image(स्थिर काष्ठा vdso_image *image)
अणु
	BUG_ON(image->size % PAGE_SIZE != 0);

	apply_alternatives((काष्ठा alt_instr *)(image->data + image->alt),
			   (काष्ठा alt_instr *)(image->data + image->alt +
						image->alt_len));
पूर्ण

अटल स्थिर काष्ठा vm_special_mapping vvar_mapping;
काष्ठा linux_binprm;

अटल vm_fault_t vdso_fault(स्थिर काष्ठा vm_special_mapping *sm,
		      काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf)
अणु
	स्थिर काष्ठा vdso_image *image = vma->vm_mm->context.vdso_image;

	अगर (!image || (vmf->pgoff << PAGE_SHIFT) >= image->size)
		वापस VM_FAULT_SIGBUS;

	vmf->page = virt_to_page(image->data + (vmf->pgoff << PAGE_SHIFT));
	get_page(vmf->page);
	वापस 0;
पूर्ण

अटल व्योम vdso_fix_landing(स्थिर काष्ठा vdso_image *image,
		काष्ठा vm_area_काष्ठा *new_vma)
अणु
#अगर defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	अगर (in_ia32_syscall() && image == &vdso_image_32) अणु
		काष्ठा pt_regs *regs = current_pt_regs();
		अचिन्हित दीर्घ vdso_land = image->sym_पूर्णांक80_landing_pad;
		अचिन्हित दीर्घ old_land_addr = vdso_land +
			(अचिन्हित दीर्घ)current->mm->context.vdso;

		/* Fixing userspace landing - look at करो_fast_syscall_32 */
		अगर (regs->ip == old_land_addr)
			regs->ip = new_vma->vm_start + vdso_land;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक vdso_mremap(स्थिर काष्ठा vm_special_mapping *sm,
		काष्ठा vm_area_काष्ठा *new_vma)
अणु
	स्थिर काष्ठा vdso_image *image = current->mm->context.vdso_image;

	vdso_fix_landing(image, new_vma);
	current->mm->context.vdso = (व्योम __user *)new_vma->vm_start;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
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
 * The vvar page layout depends on whether a task beदीर्घs to the root or
 * non-root समय namespace. Whenever a task changes its namespace, the VVAR
 * page tables are cleared and then they will re-faulted with a
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

		अगर (vma_is_special_mapping(vma, &vvar_mapping))
			zap_page_range(vma, vma->vm_start, size);
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
	स्थिर काष्ठा vdso_image *image = vma->vm_mm->context.vdso_image;
	अचिन्हित दीर्घ pfn;
	दीर्घ sym_offset;

	अगर (!image)
		वापस VM_FAULT_SIGBUS;

	sym_offset = (दीर्घ)(vmf->pgoff << PAGE_SHIFT) +
		image->sym_vvar_start;

	/*
	 * Sanity check: a symbol offset of zero means that the page
	 * करोes not exist क्रम this vdso image, not that the page is at
	 * offset zero relative to the text mapping.  This should be
	 * impossible here, because sym_offset should only be zero क्रम
	 * the page past the end of the vvar mapping.
	 */
	अगर (sym_offset == 0)
		वापस VM_FAULT_SIGBUS;

	अगर (sym_offset == image->sym_vvar_page) अणु
		काष्ठा page *समयns_page = find_समयns_vvar_page(vma);

		pfn = __pa_symbol(&__vvar_page) >> PAGE_SHIFT;

		/*
		 * If a task beदीर्घs to a समय namespace then a namespace
		 * specअगरic VVAR is mapped with the sym_vvar_page offset and
		 * the real VVAR page is mapped with the sym_समयns_page
		 * offset.
		 * See also the comment near समयns_setup_vdso_data().
		 */
		अगर (समयns_page) अणु
			अचिन्हित दीर्घ addr;
			vm_fault_t err;

			/*
			 * Optimization: inside समय namespace pre-fault
			 * VVAR page too. As on समयns page there are only
			 * offsets क्रम घड़ीs on VVAR, it'll be faulted
			 * लघुly by VDSO code.
			 */
			addr = vmf->address + (image->sym_समयns_page - sym_offset);
			err = vmf_insert_pfn(vma, addr, pfn);
			अगर (unlikely(err & VM_FAULT_ERROR))
				वापस err;

			pfn = page_to_pfn(समयns_page);
		पूर्ण

		वापस vmf_insert_pfn(vma, vmf->address, pfn);
	पूर्ण अन्यथा अगर (sym_offset == image->sym_pvघड़ी_page) अणु
		काष्ठा pvघड़ी_vsyscall_समय_info *pvti =
			pvघड़ी_get_pvti_cpu0_va();
		अगर (pvti && vघड़ी_was_used(VDSO_CLOCKMODE_PVCLOCK)) अणु
			वापस vmf_insert_pfn_prot(vma, vmf->address,
					__pa(pvti) >> PAGE_SHIFT,
					pgprot_decrypted(vma->vm_page_prot));
		पूर्ण
	पूर्ण अन्यथा अगर (sym_offset == image->sym_hvघड़ी_page) अणु
		काष्ठा ms_hyperv_tsc_page *tsc_pg = hv_get_tsc_page();

		अगर (tsc_pg && vघड़ी_was_used(VDSO_CLOCKMODE_HVCLOCK))
			वापस vmf_insert_pfn(vma, vmf->address,
					virt_to_phys(tsc_pg) >> PAGE_SHIFT);
	पूर्ण अन्यथा अगर (sym_offset == image->sym_समयns_page) अणु
		काष्ठा page *समयns_page = find_समयns_vvar_page(vma);

		अगर (!समयns_page)
			वापस VM_FAULT_SIGBUS;

		pfn = __pa_symbol(&__vvar_page) >> PAGE_SHIFT;
		वापस vmf_insert_pfn(vma, vmf->address, pfn);
	पूर्ण

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_special_mapping vdso_mapping = अणु
	.name = "[vdso]",
	.fault = vdso_fault,
	.mremap = vdso_mremap,
पूर्ण;
अटल स्थिर काष्ठा vm_special_mapping vvar_mapping = अणु
	.name = "[vvar]",
	.fault = vvar_fault,
पूर्ण;

/*
 * Add vdso and vvar mappings to current process.
 * @image          - blob to map
 * @addr           - request a specअगरic address (zero to map at मुक्त addr)
 */
अटल पूर्णांक map_vdso(स्थिर काष्ठा vdso_image *image, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ text_start;
	पूर्णांक ret = 0;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	addr = get_unmapped_area(शून्य, addr,
				 image->size - image->sym_vvar_start, 0, 0);
	अगर (IS_ERR_VALUE(addr)) अणु
		ret = addr;
		जाओ up_fail;
	पूर्ण

	text_start = addr - image->sym_vvar_start;

	/*
	 * MAYWRITE to allow gdb to COW and set अवरोधpoपूर्णांकs
	 */
	vma = _install_special_mapping(mm,
				       text_start,
				       image->size,
				       VM_READ|VM_EXEC|
				       VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				       &vdso_mapping);

	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ up_fail;
	पूर्ण

	vma = _install_special_mapping(mm,
				       addr,
				       -image->sym_vvar_start,
				       VM_READ|VM_MAYREAD|VM_IO|VM_DONTDUMP|
				       VM_PFNMAP,
				       &vvar_mapping);

	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		करो_munmap(mm, text_start, image->size, शून्य);
	पूर्ण अन्यथा अणु
		current->mm->context.vdso = (व्योम __user *)text_start;
		current->mm->context.vdso_image = image;
	पूर्ण

up_fail:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * Put the vdso above the (अक्रमomized) stack with another अक्रमomized
 * offset.  This way there is no hole in the middle of address space.
 * To save memory make sure it is still in the same PTE as the stack
 * top.  This करोesn't give that many अक्रमom bits.
 *
 * Note that this algorithm is imperfect: the distribution of the vdso
 * start address within a PMD is biased toward the end.
 *
 * Only used क्रम the 64-bit and x32 vdsos.
 */
अटल अचिन्हित दीर्घ vdso_addr(अचिन्हित दीर्घ start, अचिन्हित len)
अणु
	अचिन्हित दीर्घ addr, end;
	अचिन्हित offset;

	/*
	 * Round up the start address.  It can start out unaligned as a result
	 * of stack start अक्रमomization.
	 */
	start = PAGE_ALIGN(start);

	/* Round the lowest possible end address up to a PMD boundary. */
	end = (start + len + PMD_SIZE - 1) & PMD_MASK;
	अगर (end >= TASK_SIZE_MAX)
		end = TASK_SIZE_MAX;
	end -= len;

	अगर (end > start) अणु
		offset = get_अक्रमom_पूर्णांक() % (((end - start) >> PAGE_SHIFT) + 1);
		addr = start + (offset << PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		addr = start;
	पूर्ण

	/*
	 * Forcibly align the final address in हाल we have a hardware
	 * issue that requires alignment क्रम perक्रमmance reasons.
	 */
	addr = align_vdso_addr(addr);

	वापस addr;
पूर्ण

अटल पूर्णांक map_vdso_अक्रमomized(स्थिर काष्ठा vdso_image *image)
अणु
	अचिन्हित दीर्घ addr = vdso_addr(current->mm->start_stack, image->size-image->sym_vvar_start);

	वापस map_vdso(image, addr);
पूर्ण
#पूर्ण_अगर

पूर्णांक map_vdso_once(स्थिर काष्ठा vdso_image *image, अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;

	mmap_ग_लिखो_lock(mm);
	/*
	 * Check अगर we have alपढ़ोy mapped vdso blob - fail to prevent
	 * abusing from userspace install_special_mapping, which may
	 * not करो accounting and rlimit right.
	 * We could search vma near context.vdso, but it's a slowpath,
	 * so let's explicitly check all VMAs to be completely sure.
	 */
	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (vma_is_special_mapping(vma, &vdso_mapping) ||
				vma_is_special_mapping(vma, &vvar_mapping)) अणु
			mmap_ग_लिखो_unlock(mm);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	mmap_ग_लिखो_unlock(mm);

	वापस map_vdso(image, addr);
पूर्ण

#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
अटल पूर्णांक load_vdso32(व्योम)
अणु
	अगर (vdso32_enabled != 1)  /* Other values all mean "disabled" */
		वापस 0;

	वापस map_vdso(&vdso_image_32, 0);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_64
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	अगर (!vdso64_enabled)
		वापस 0;

	वापस map_vdso_अक्रमomized(&vdso_image_64);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
पूर्णांक compat_arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
				       पूर्णांक uses_पूर्णांकerp, bool x32)
अणु
#अगर_घोषित CONFIG_X86_X32_ABI
	अगर (x32) अणु
		अगर (!vdso64_enabled)
			वापस 0;
		वापस map_vdso_अक्रमomized(&vdso_image_x32);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_IA32_EMULATION
	वापस load_vdso32();
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर
#अन्यथा
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	वापस load_vdso32();
पूर्ण
#पूर्ण_अगर

bool arch_syscall_is_vdso_sigवापस(काष्ठा pt_regs *regs)
अणु
#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
	स्थिर काष्ठा vdso_image *image = current->mm->context.vdso_image;
	अचिन्हित दीर्घ vdso = (अचिन्हित दीर्घ) current->mm->context.vdso;

	अगर (in_ia32_syscall() && image == &vdso_image_32) अणु
		अगर (regs->ip == vdso + image->sym_vdso32_sigवापस_landing_pad ||
		    regs->ip == vdso + image->sym_vdso32_rt_sigवापस_landing_pad)
			वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_X86_64
अटल __init पूर्णांक vdso_setup(अक्षर *s)
अणु
	vdso64_enabled = simple_म_से_अदीर्घ(s, शून्य, 0);
	वापस 0;
पूर्ण
__setup("vdso=", vdso_setup);

अटल पूर्णांक __init init_vdso(व्योम)
अणु
	BUILD_BUG_ON(VDSO_CLOCKMODE_MAX >= 32);

	init_vdso_image(&vdso_image_64);

#अगर_घोषित CONFIG_X86_X32_ABI
	init_vdso_image(&vdso_image_x32);
#पूर्ण_अगर

	वापस 0;
पूर्ण
subsys_initcall(init_vdso);
#पूर्ण_अगर /* CONFIG_X86_64 */
