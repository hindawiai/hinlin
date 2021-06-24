<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * APIC driver क्रम "bigsmp" xAPIC machines with more than 8 भव CPUs.
 *
 * Drives the local APIC in "clustered mode".
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/dmi.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>

#समावेश "local.h"

अटल अचिन्हित bigsmp_get_apic_id(अचिन्हित दीर्घ x)
अणु
	वापस (x >> 24) & 0xFF;
पूर्ण

अटल पूर्णांक bigsmp_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस 1;
पूर्ण

अटल bool bigsmp_check_apicid_used(physid_mask_t *map, पूर्णांक apicid)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक bigsmp_early_logical_apicid(पूर्णांक cpu)
अणु
	/* on bigsmp, logical apicid is the same as physical */
	वापस early_per_cpu(x86_cpu_to_apicid, cpu);
पूर्ण

/*
 * bigsmp enables physical destination mode
 * and करोesn't use LDR and DFR
 */
अटल व्योम bigsmp_init_apic_ldr(व्योम)
अणु
पूर्ण

अटल व्योम bigsmp_setup_apic_routing(व्योम)
अणु
	prपूर्णांकk(KERN_INFO
		"Enabling APIC mode:  Physflat.  Using %d I/O APICs\n",
		nr_ioapics);
पूर्ण

अटल पूर्णांक bigsmp_cpu_present_to_apicid(पूर्णांक mps_cpu)
अणु
	अगर (mps_cpu < nr_cpu_ids)
		वापस (पूर्णांक) per_cpu(x86_bios_cpu_apicid, mps_cpu);

	वापस BAD_APICID;
पूर्ण

अटल व्योम bigsmp_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *reपंचांगap)
अणु
	/* For clustered we करोn't have a good way to करो this yet - hack */
	physids_promote(0xFFL, reपंचांगap);
पूर्ण

अटल पूर्णांक bigsmp_check_phys_apicid_present(पूर्णांक phys_apicid)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक bigsmp_phys_pkg_id(पूर्णांक cpuid_apic, पूर्णांक index_msb)
अणु
	वापस cpuid_apic >> index_msb;
पूर्ण

अटल व्योम bigsmp_send_IPI_allbutself(पूर्णांक vector)
अणु
	शेष_send_IPI_mask_allbutself_phys(cpu_online_mask, vector);
पूर्ण

अटल व्योम bigsmp_send_IPI_all(पूर्णांक vector)
अणु
	शेष_send_IPI_mask_sequence_phys(cpu_online_mask, vector);
पूर्ण

अटल पूर्णांक dmi_bigsmp; /* can be set by dmi scanners */

अटल पूर्णांक hp_ht_bigsmp(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	prपूर्णांकk(KERN_NOTICE "%s detected: force use of apic=bigsmp\n", d->ident);
	dmi_bigsmp = 1;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा dmi_प्रणाली_id bigsmp_dmi_table[] = अणु
	अणु hp_ht_bigsmp, "HP ProLiant DL760 G2",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "HP"),
			DMI_MATCH(DMI_BIOS_VERSION, "P44-"),
		पूर्ण
	पूर्ण,

	अणु hp_ht_bigsmp, "HP ProLiant DL740",
		अणु	DMI_MATCH(DMI_BIOS_VENDOR, "HP"),
			DMI_MATCH(DMI_BIOS_VERSION, "P47-"),
		पूर्ण
	पूर्ण,
	अणु पूर्ण /* शून्य entry stops DMI scanning */
पूर्ण;

अटल पूर्णांक probe_bigsmp(व्योम)
अणु
	अगर (def_to_bigsmp)
		dmi_bigsmp = 1;
	अन्यथा
		dmi_check_प्रणाली(bigsmp_dmi_table);

	वापस dmi_bigsmp;
पूर्ण

अटल काष्ठा apic apic_bigsmp __ro_after_init = अणु

	.name				= "bigsmp",
	.probe				= probe_bigsmp,
	.acpi_madt_oem_check		= शून्य,
	.apic_id_valid			= शेष_apic_id_valid,
	.apic_id_रेजिस्टरed		= bigsmp_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 1,

	.check_apicid_used		= bigsmp_check_apicid_used,
	.init_apic_ldr			= bigsmp_init_apic_ldr,
	.ioapic_phys_id_map		= bigsmp_ioapic_phys_id_map,
	.setup_apic_routing		= bigsmp_setup_apic_routing,
	.cpu_present_to_apicid		= bigsmp_cpu_present_to_apicid,
	.apicid_to_cpu_present		= physid_set_mask_of_physid,
	.check_phys_apicid_present	= bigsmp_check_phys_apicid_present,
	.phys_pkg_id			= bigsmp_phys_pkg_id,

	.get_apic_id			= bigsmp_get_apic_id,
	.set_apic_id			= शून्य,

	.calc_dest_apicid		= apic_शेष_calc_apicid,

	.send_IPI			= शेष_send_IPI_single_phys,
	.send_IPI_mask			= शेष_send_IPI_mask_sequence_phys,
	.send_IPI_mask_allbutself	= शून्य,
	.send_IPI_allbutself		= bigsmp_send_IPI_allbutself,
	.send_IPI_all			= bigsmp_send_IPI_all,
	.send_IPI_self			= शेष_send_IPI_self,

	.inquire_remote_apic		= शेष_inquire_remote_apic,

	.पढ़ो				= native_apic_mem_पढ़ो,
	.ग_लिखो				= native_apic_mem_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_mem_ग_लिखो,
	.icr_पढ़ो			= native_apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_apic_icr_ग_लिखो,
	.रुको_icr_idle			= native_apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= native_safe_apic_रुको_icr_idle,

	.x86_32_early_logical_apicid	= bigsmp_early_logical_apicid,
पूर्ण;

व्योम __init generic_bigsmp_probe(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	अगर (!probe_bigsmp())
		वापस;

	apic = &apic_bigsmp;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (early_per_cpu(x86_cpu_to_logical_apicid,
				  cpu) == BAD_APICID)
			जारी;
		early_per_cpu(x86_cpu_to_logical_apicid, cpu) =
			bigsmp_early_logical_apicid(cpu);
	पूर्ण

	pr_info("Overriding APIC driver with %s\n", apic_bigsmp.name);
पूर्ण

apic_driver(apic_bigsmp);
