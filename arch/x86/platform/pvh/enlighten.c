<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/acpi.h>

#समावेश <xen/hvc-console.h>

#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/x86_init.h>

#समावेश <यंत्र/xen/पूर्णांकerface.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/hvm/start_info.h>

/*
 * PVH variables.
 *
 * pvh_bootparams and pvh_start_info need to live in the data segment since
 * they are used after startup_अणु32|64पूर्ण, which clear .bss, are invoked.
 */
काष्ठा boot_params pvh_bootparams __section(".data");
काष्ठा hvm_start_info pvh_start_info __section(".data");

अचिन्हित पूर्णांक pvh_start_info_sz = माप(pvh_start_info);

अटल u64 pvh_get_root_poपूर्णांकer(व्योम)
अणु
	वापस pvh_start_info.rsdp_paddr;
पूर्ण

/*
 * Xen guests are able to obtain the memory map from the hypervisor via the
 * HYPERVISOR_memory_op hypercall.
 * If we are trying to boot a Xen PVH guest, it is expected that the kernel
 * will have been configured to provide an override क्रम this routine to करो
 * just that.
 */
व्योम __init __weak mem_map_via_hcall(काष्ठा boot_params *ptr __maybe_unused)
अणु
	xen_raw_prपूर्णांकk("Error: Could not find memory map\n");
	BUG();
पूर्ण

अटल व्योम __init init_pvh_bootparams(bool xen_guest)
अणु
	अगर ((pvh_start_info.version > 0) && (pvh_start_info.memmap_entries)) अणु
		काष्ठा hvm_memmap_table_entry *ep;
		पूर्णांक i;

		ep = __va(pvh_start_info.memmap_paddr);
		pvh_bootparams.e820_entries = pvh_start_info.memmap_entries;

		क्रम (i = 0; i < pvh_bootparams.e820_entries ; i++, ep++) अणु
			pvh_bootparams.e820_table[i].addr = ep->addr;
			pvh_bootparams.e820_table[i].size = ep->size;
			pvh_bootparams.e820_table[i].type = ep->type;
		पूर्ण
	पूर्ण अन्यथा अगर (xen_guest) अणु
		mem_map_via_hcall(&pvh_bootparams);
	पूर्ण अन्यथा अणु
		/* Non-xen guests are not supported by version 0 */
		BUG();
	पूर्ण

	अगर (pvh_bootparams.e820_entries < E820_MAX_ENTRIES_ZEROPAGE - 1) अणु
		pvh_bootparams.e820_table[pvh_bootparams.e820_entries].addr =
			ISA_START_ADDRESS;
		pvh_bootparams.e820_table[pvh_bootparams.e820_entries].size =
			ISA_END_ADDRESS - ISA_START_ADDRESS;
		pvh_bootparams.e820_table[pvh_bootparams.e820_entries].type =
			E820_TYPE_RESERVED;
		pvh_bootparams.e820_entries++;
	पूर्ण अन्यथा
		xen_raw_prपूर्णांकk("Warning: Can fit ISA range into e820\n");

	pvh_bootparams.hdr.cmd_line_ptr =
		pvh_start_info.cmdline_paddr;

	/* The first module is always ramdisk. */
	अगर (pvh_start_info.nr_modules) अणु
		काष्ठा hvm_modlist_entry *modaddr =
			__va(pvh_start_info.modlist_paddr);
		pvh_bootparams.hdr.ramdisk_image = modaddr->paddr;
		pvh_bootparams.hdr.ramdisk_size = modaddr->size;
	पूर्ण

	/*
	 * See Documentation/x86/boot.rst.
	 *
	 * Version 2.12 supports Xen entry poपूर्णांक but we will use शेष x86/PC
	 * environment (i.e. hardware_subarch 0).
	 */
	pvh_bootparams.hdr.version = (2 << 8) | 12;
	pvh_bootparams.hdr.type_of_loader = ((xen_guest ? 0x9 : 0xb) << 4) | 0;

	x86_init.acpi.get_root_poपूर्णांकer = pvh_get_root_poपूर्णांकer;
पूर्ण

/*
 * If we are trying to boot a Xen PVH guest, it is expected that the kernel
 * will have been configured to provide the required override क्रम this routine.
 */
व्योम __init __weak xen_pvh_init(काष्ठा boot_params *boot_params)
अणु
	xen_raw_prपूर्णांकk("Error: Missing xen PVH initialization\n");
	BUG();
पूर्ण

अटल व्योम hypervisor_specअगरic_init(bool xen_guest)
अणु
	अगर (xen_guest)
		xen_pvh_init(&pvh_bootparams);
पूर्ण

/*
 * This routine (and those that it might call) should not use
 * anything that lives in .bss since that segment will be cleared later.
 */
व्योम __init xen_prepare_pvh(व्योम)
अणु

	u32 msr = xen_cpuid_base();
	bool xen_guest = !!msr;

	अगर (pvh_start_info.magic != XEN_HVM_START_MAGIC_VALUE) अणु
		xen_raw_prपूर्णांकk("Error: Unexpected magic value (0x%08x)\n",
				pvh_start_info.magic);
		BUG();
	पूर्ण

	स_रखो(&pvh_bootparams, 0, माप(pvh_bootparams));

	hypervisor_specअगरic_init(xen_guest);

	init_pvh_bootparams(xen_guest);
पूर्ण
