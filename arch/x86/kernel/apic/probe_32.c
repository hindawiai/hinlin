<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Default generic APIC driver. This handles up to 8 CPUs.
 *
 * Copyright 2003 Andi Kleen, SuSE Lअसल.
 *
 * Generic x86 APIC driver probe layer.
 */
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>

#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/acpi.h>

#समावेश "local.h"

अटल पूर्णांक शेष_x86_32_early_logical_apicid(पूर्णांक cpu)
अणु
	वापस 1 << cpu;
पूर्ण

अटल व्योम setup_apic_flat_routing(व्योम)
अणु
#अगर_घोषित CONFIG_X86_IO_APIC
	prपूर्णांकk(KERN_INFO
		"Enabling APIC mode:  Flat.  Using %d I/O APICs\n",
		nr_ioapics);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक शेष_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस physid_isset(पढ़ो_apic_id(), phys_cpu_present_map);
पूर्ण

/*
 * Set up the logical destination ID.  Intel recommends to set DFR, LDR and
 * TPR beक्रमe enabling an APIC.  See e.g. "AP-388 82489DX User's Manual"
 * (Intel करोcument number 292116).
 */
अटल व्योम शेष_init_apic_ldr(व्योम)
अणु
	अचिन्हित दीर्घ val;

	apic_ग_लिखो(APIC_DFR, APIC_DFR_VALUE);
	val = apic_पढ़ो(APIC_LDR) & ~APIC_LDR_MASK;
	val |= SET_APIC_LOGICAL_ID(1UL << smp_processor_id());
	apic_ग_लिखो(APIC_LDR, val);
पूर्ण

अटल पूर्णांक शेष_phys_pkg_id(पूर्णांक cpuid_apic, पूर्णांक index_msb)
अणु
	वापस cpuid_apic >> index_msb;
पूर्ण

/* should be called last. */
अटल पूर्णांक probe_शेष(व्योम)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा apic apic_शेष __ro_after_init = अणु

	.name				= "default",
	.probe				= probe_शेष,
	.acpi_madt_oem_check		= शून्य,
	.apic_id_valid			= शेष_apic_id_valid,
	.apic_id_रेजिस्टरed		= शेष_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= true,

	.disable_esr			= 0,

	.check_apicid_used		= शेष_check_apicid_used,
	.init_apic_ldr			= शेष_init_apic_ldr,
	.ioapic_phys_id_map		= शेष_ioapic_phys_id_map,
	.setup_apic_routing		= setup_apic_flat_routing,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= physid_set_mask_of_physid,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= शेष_phys_pkg_id,

	.get_apic_id			= शेष_get_apic_id,
	.set_apic_id			= शून्य,

	.calc_dest_apicid		= apic_flat_calc_apicid,

	.send_IPI			= शेष_send_IPI_single,
	.send_IPI_mask			= शेष_send_IPI_mask_logical,
	.send_IPI_mask_allbutself	= शेष_send_IPI_mask_allbutself_logical,
	.send_IPI_allbutself		= शेष_send_IPI_allbutself,
	.send_IPI_all			= शेष_send_IPI_all,
	.send_IPI_self			= शेष_send_IPI_self,

	.inquire_remote_apic		= शेष_inquire_remote_apic,

	.पढ़ो				= native_apic_mem_पढ़ो,
	.ग_लिखो				= native_apic_mem_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_mem_ग_लिखो,
	.icr_पढ़ो			= native_apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_apic_icr_ग_लिखो,
	.रुको_icr_idle			= native_apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= native_safe_apic_रुको_icr_idle,

	.x86_32_early_logical_apicid	= शेष_x86_32_early_logical_apicid,
पूर्ण;

apic_driver(apic_शेष);

काष्ठा apic *apic __ro_after_init = &apic_शेष;
EXPORT_SYMBOL_GPL(apic);

अटल पूर्णांक cmdline_apic __initdata;
अटल पूर्णांक __init parse_apic(अक्षर *arg)
अणु
	काष्ठा apic **drv;

	अगर (!arg)
		वापस -EINVAL;

	क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
		अगर (!म_भेद((*drv)->name, arg)) अणु
			apic = *drv;
			cmdline_apic = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	/* Parsed again by __setup क्रम debug/verbose */
	वापस 0;
पूर्ण
early_param("apic", parse_apic);

व्योम __init शेष_setup_apic_routing(व्योम)
अणु
	पूर्णांक version = boot_cpu_apic_version;

	अगर (num_possible_cpus() > 8) अणु
		चयन (boot_cpu_data.x86_venकरोr) अणु
		हाल X86_VENDOR_INTEL:
			अगर (!APIC_XAPIC(version)) अणु
				def_to_bigsmp = 0;
				अवरोध;
			पूर्ण
			/* P4 and above */
			fallthrough;
		हाल X86_VENDOR_HYGON:
		हाल X86_VENDOR_AMD:
			def_to_bigsmp = 1;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_X86_BIGSMP
	/*
	 * This is used to चयन to bigsmp mode when
	 * - There is no apic= option specअगरied by the user
	 * - generic_apic_probe() has chosen apic_शेष as the sub_arch
	 * - we find more than 8 CPUs in acpi LAPIC listing with xAPIC support
	 */

	अगर (!cmdline_apic && apic == &apic_शेष)
		generic_bigsmp_probe();
#पूर्ण_अगर

	अगर (apic->setup_apic_routing)
		apic->setup_apic_routing();
पूर्ण

व्योम __init generic_apic_probe(व्योम)
अणु
	अगर (!cmdline_apic) अणु
		काष्ठा apic **drv;

		क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
			अगर ((*drv)->probe()) अणु
				apic = *drv;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Not visible without early console */
		अगर (drv == __apicdrivers_end)
			panic("Didn't find an APIC driver");
	पूर्ण
	prपूर्णांकk(KERN_INFO "Using APIC driver %s\n", apic->name);
पूर्ण

/* This function can चयन the APIC even after the initial ->probe() */
पूर्णांक __init शेष_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	काष्ठा apic **drv;

	क्रम (drv = __apicdrivers; drv < __apicdrivers_end; drv++) अणु
		अगर (!(*drv)->acpi_madt_oem_check)
			जारी;
		अगर (!(*drv)->acpi_madt_oem_check(oem_id, oem_table_id))
			जारी;

		अगर (!cmdline_apic) अणु
			apic = *drv;
			prपूर्णांकk(KERN_INFO "Switched to APIC driver `%s'.\n",
			       apic->name);
		पूर्ण
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
