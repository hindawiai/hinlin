<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/crash_dump.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/hvm.h>

#समावेश "mmu.h"

#अगर_घोषित CONFIG_PROC_VMCORE
/*
 * This function is used in two contexts:
 * - the kdump kernel has to check whether a pfn of the crashed kernel
 *   was a ballooned page. vmcore is using this function to decide
 *   whether to access a pfn of the crashed kernel.
 * - the kexec kernel has to check whether a pfn was ballooned by the
 *   previous kernel. If the pfn is ballooned, handle it properly.
 * Returns 0 अगर the pfn is not backed by a RAM page, the caller may
 * handle the pfn special in this हाल.
 */
अटल पूर्णांक xen_oldmem_pfn_is_ram(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा xen_hvm_get_mem_type a = अणु
		.करोmid = DOMID_SELF,
		.pfn = pfn,
	पूर्ण;
	पूर्णांक ram;

	अगर (HYPERVISOR_hvm_op(HVMOP_get_mem_type, &a))
		वापस -ENXIO;

	चयन (a.mem_type) अणु
	हाल HVMMEM_mmio_dm:
		ram = 0;
		अवरोध;
	हाल HVMMEM_ram_rw:
	हाल HVMMEM_ram_ro:
	शेष:
		ram = 1;
		अवरोध;
	पूर्ण

	वापस ram;
पूर्ण
#पूर्ण_अगर

अटल व्योम xen_hvm_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा xen_hvm_pagetable_dying a;
	पूर्णांक rc;

	a.करोmid = DOMID_SELF;
	a.gpa = __pa(mm->pgd);
	rc = HYPERVISOR_hvm_op(HVMOP_pagetable_dying, &a);
	WARN_ON_ONCE(rc < 0);
पूर्ण

अटल पूर्णांक is_pagetable_dying_supported(व्योम)
अणु
	काष्ठा xen_hvm_pagetable_dying a;
	पूर्णांक rc = 0;

	a.करोmid = DOMID_SELF;
	a.gpa = 0x00;
	rc = HYPERVISOR_hvm_op(HVMOP_pagetable_dying, &a);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_DEBUG "HVMOP_pagetable_dying not supported\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

व्योम __init xen_hvm_init_mmu_ops(व्योम)
अणु
	अगर (is_pagetable_dying_supported())
		pv_ops.mmu.निकास_mmap = xen_hvm_निकास_mmap;
#अगर_घोषित CONFIG_PROC_VMCORE
	WARN_ON(रेजिस्टर_oldmem_pfn_is_ram(&xen_oldmem_pfn_is_ram));
#पूर्ण_अगर
पूर्ण
