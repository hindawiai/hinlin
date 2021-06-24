<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/acpi.h>

#समावेश <xen/hvc-console.h>

#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/e820/api.h>

#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/पूर्णांकerface/memory.h>

#समावेश "xen-ops.h"

/*
 * PVH variables.
 *
 * The variable xen_pvh needs to live in the data segment since it is used
 * after startup_अणु32|64पूर्ण is invoked, which will clear the .bss segment.
 */
bool xen_pvh __section(".data") = 0;

व्योम __init xen_pvh_init(काष्ठा boot_params *boot_params)
अणु
	u32 msr;
	u64 pfn;

	xen_pvh = 1;
	xen_करोमुख्य_type = XEN_HVM_DOMAIN;
	xen_start_flags = pvh_start_info.flags;

	msr = cpuid_ebx(xen_cpuid_base() + 2);
	pfn = __pa(hypercall_page);
	wrmsr_safe(msr, (u32)pfn, (u32)(pfn >> 32));

	xen_efi_init(boot_params);
पूर्ण

व्योम __init mem_map_via_hcall(काष्ठा boot_params *boot_params_p)
अणु
	काष्ठा xen_memory_map memmap;
	पूर्णांक rc;

	memmap.nr_entries = ARRAY_SIZE(boot_params_p->e820_table);
	set_xen_guest_handle(memmap.buffer, boot_params_p->e820_table);
	rc = HYPERVISOR_memory_op(XENMEM_memory_map, &memmap);
	अगर (rc) अणु
		xen_raw_prपूर्णांकk("XENMEM_memory_map failed (%d)\n", rc);
		BUG();
	पूर्ण
	boot_params_p->e820_entries = memmap.nr_entries;
पूर्ण
