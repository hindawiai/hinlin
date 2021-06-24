<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CoProcessor (SPU/AFU) mm fault handler
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2007
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 * Author: Jeremy Kerr <jk@ozद_असल.org>
 */
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/copro.h>
#समावेश <यंत्र/spu.h>
#समावेश <misc/cxl-base.h>

/*
 * This ought to be kept in sync with the घातerpc specअगरic करो_page_fault
 * function. Currently, there are a few corner हालs that we haven't had
 * to handle क्रमtunately.
 */
पूर्णांक copro_handle_mm_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea,
		अचिन्हित दीर्घ dsisr, vm_fault_t *flt)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ is_ग_लिखो;
	पूर्णांक ret;

	अगर (mm == शून्य)
		वापस -EFAULT;

	अगर (mm->pgd == शून्य)
		वापस -EFAULT;

	mmap_पढ़ो_lock(mm);
	ret = -EFAULT;
	vma = find_vma(mm, ea);
	अगर (!vma)
		जाओ out_unlock;

	अगर (ea < vma->vm_start) अणु
		अगर (!(vma->vm_flags & VM_GROWSDOWN))
			जाओ out_unlock;
		अगर (expand_stack(vma, ea))
			जाओ out_unlock;
	पूर्ण

	is_ग_लिखो = dsisr & DSISR_ISSTORE;
	अगर (is_ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ out_unlock;
		/*
		 * PROT_NONE is covered by the VMA check above.
		 * and hash should get a NOHPTE fault instead of
		 * a PROTFAULT in हाल fixup is needed क्रम things
		 * like स्वतःnuma.
		 */
		अगर (!radix_enabled())
			WARN_ON_ONCE(dsisr & DSISR_PROTFAULT);
	पूर्ण

	ret = 0;
	*flt = handle_mm_fault(vma, ea, is_ग_लिखो ? FAULT_FLAG_WRITE : 0, शून्य);
	अगर (unlikely(*flt & VM_FAULT_ERROR)) अणु
		अगर (*flt & VM_FAULT_OOM) अणु
			ret = -ENOMEM;
			जाओ out_unlock;
		पूर्ण अन्यथा अगर (*flt & (VM_FAULT_SIGBUS | VM_FAULT_संक_अंश)) अणु
			ret = -EFAULT;
			जाओ out_unlock;
		पूर्ण
		BUG();
	पूर्ण

out_unlock:
	mmap_पढ़ो_unlock(mm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(copro_handle_mm_fault);

पूर्णांक copro_calculate_slb(काष्ठा mm_काष्ठा *mm, u64 ea, काष्ठा copro_slb *slb)
अणु
	u64 vsid, vsidkey;
	पूर्णांक psize, ssize;

	चयन (get_region_id(ea)) अणु
	हाल USER_REGION_ID:
		pr_devel("%s: 0x%llx -- USER_REGION_ID\n", __func__, ea);
		अगर (mm == शून्य)
			वापस 1;
		psize = get_slice_psize(mm, ea);
		ssize = user_segment_size(ea);
		vsid = get_user_vsid(&mm->context, ea, ssize);
		vsidkey = SLB_VSID_USER;
		अवरोध;
	हाल VMALLOC_REGION_ID:
		pr_devel("%s: 0x%llx -- VMALLOC_REGION_ID\n", __func__, ea);
		psize = mmu_vदो_स्मृति_psize;
		ssize = mmu_kernel_ssize;
		vsid = get_kernel_vsid(ea, mmu_kernel_ssize);
		vsidkey = SLB_VSID_KERNEL;
		अवरोध;
	हाल IO_REGION_ID:
		pr_devel("%s: 0x%llx -- IO_REGION_ID\n", __func__, ea);
		psize = mmu_io_psize;
		ssize = mmu_kernel_ssize;
		vsid = get_kernel_vsid(ea, mmu_kernel_ssize);
		vsidkey = SLB_VSID_KERNEL;
		अवरोध;
	हाल LINEAR_MAP_REGION_ID:
		pr_devel("%s: 0x%llx -- LINEAR_MAP_REGION_ID\n", __func__, ea);
		psize = mmu_linear_psize;
		ssize = mmu_kernel_ssize;
		vsid = get_kernel_vsid(ea, mmu_kernel_ssize);
		vsidkey = SLB_VSID_KERNEL;
		अवरोध;
	शेष:
		pr_debug("%s: invalid region access at %016llx\n", __func__, ea);
		वापस 1;
	पूर्ण
	/* Bad address */
	अगर (!vsid)
		वापस 1;

	vsid = (vsid << slb_vsid_shअगरt(ssize)) | vsidkey;

	vsid |= mmu_psize_defs[psize].sllp |
		((ssize == MMU_SEGSIZE_1T) ? SLB_VSID_B_1T : 0);

	slb->esid = (ea & (ssize == MMU_SEGSIZE_1T ? ESID_MASK_1T : ESID_MASK)) | SLB_ESID_V;
	slb->vsid = vsid;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copro_calculate_slb);

व्योम copro_flush_all_slbs(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_SPU_BASE
	spu_flush_all_slbs(mm);
#पूर्ण_अगर
	cxl_slbia(mm);
पूर्ण
EXPORT_SYMBOL_GPL(copro_flush_all_slbs);
