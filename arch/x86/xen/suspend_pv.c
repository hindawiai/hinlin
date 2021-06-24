<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/page.h>

#समावेश <यंत्र/fixmap.h>

#समावेश "xen-ops.h"

व्योम xen_pv_pre_suspend(व्योम)
अणु
	xen_mm_pin_all();

	xen_start_info->store_mfn = mfn_to_pfn(xen_start_info->store_mfn);
	xen_start_info->console.करोmU.mfn =
		mfn_to_pfn(xen_start_info->console.करोmU.mfn);

	BUG_ON(!irqs_disabled());

	HYPERVISOR_shared_info = &xen_dummy_shared_info;
	अगर (HYPERVISOR_update_va_mapping(fix_to_virt(FIX_PARAVIRT_BOOTMAP),
					 __pte_ma(0), 0))
		BUG();
पूर्ण

व्योम xen_pv_post_suspend(पूर्णांक suspend_cancelled)
अणु
	xen_build_mfn_list_list();
	set_fixmap(FIX_PARAVIRT_BOOTMAP, xen_start_info->shared_info);
	HYPERVISOR_shared_info = (व्योम *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);
	xen_setup_mfn_list_list();

	अगर (suspend_cancelled) अणु
		xen_start_info->store_mfn =
			pfn_to_mfn(xen_start_info->store_mfn);
		xen_start_info->console.करोmU.mfn =
			pfn_to_mfn(xen_start_info->console.करोmU.mfn);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_SMP
		BUG_ON(xen_cpu_initialized_map == शून्य);
		cpumask_copy(xen_cpu_initialized_map, cpu_online_mask);
#पूर्ण_अगर
		xen_vcpu_restore();
	पूर्ण

	xen_mm_unpin_all();
पूर्ण
