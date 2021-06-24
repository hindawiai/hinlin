<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2004 James Cleverकरोn, IBM.
 *
 * Flat APIC subarch code.
 *
 * Hacked क्रम x86-64 by James Cleverकरोn from i386 architecture code by
 * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and
 * James Cleverकरोn.
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/acpi.h>

#समावेश <यंत्र/jailhouse_para.h>
#समावेश <यंत्र/apic.h>

#समावेश "local.h"

अटल काष्ठा apic apic_physflat;
अटल काष्ठा apic apic_flat;

काष्ठा apic *apic __ro_after_init = &apic_flat;
EXPORT_SYMBOL_GPL(apic);

अटल पूर्णांक flat_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	वापस 1;
पूर्ण

/*
 * Set up the logical destination ID.
 *
 * Intel recommends to set DFR, LDR and TPR beक्रमe enabling
 * an APIC.  See e.g. "AP-388 82489DX User's Manual" (Intel
 * करोcument number 292116).  So here it goes...
 */
व्योम flat_init_apic_ldr(व्योम)
अणु
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ num, id;

	num = smp_processor_id();
	id = 1UL << num;
	apic_ग_लिखो(APIC_DFR, APIC_DFR_FLAT);
	val = apic_पढ़ो(APIC_LDR) & ~APIC_LDR_MASK;
	val |= SET_APIC_LOGICAL_ID(id);
	apic_ग_लिखो(APIC_LDR, val);
पूर्ण

अटल व्योम _flat_send_IPI_mask(अचिन्हित दीर्घ mask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__शेष_send_IPI_dest_field(mask, vector, APIC_DEST_LOGICAL);
	local_irq_restore(flags);
पूर्ण

अटल व्योम flat_send_IPI_mask(स्थिर काष्ठा cpumask *cpumask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ mask = cpumask_bits(cpumask)[0];

	_flat_send_IPI_mask(mask, vector);
पूर्ण

अटल व्योम
flat_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *cpumask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ mask = cpumask_bits(cpumask)[0];
	पूर्णांक cpu = smp_processor_id();

	अगर (cpu < BITS_PER_LONG)
		__clear_bit(cpu, &mask);

	_flat_send_IPI_mask(mask, vector);
पूर्ण

अटल अचिन्हित पूर्णांक flat_get_apic_id(अचिन्हित दीर्घ x)
अणु
	वापस (x >> 24) & 0xFF;
पूर्ण

अटल u32 set_apic_id(अचिन्हित पूर्णांक id)
अणु
	वापस (id & 0xFF) << 24;
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_xapic_id(व्योम)
अणु
	वापस flat_get_apic_id(apic_पढ़ो(APIC_ID));
पूर्ण

अटल पूर्णांक flat_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस physid_isset(पढ़ो_xapic_id(), phys_cpu_present_map);
पूर्ण

अटल पूर्णांक flat_phys_pkg_id(पूर्णांक initial_apic_id, पूर्णांक index_msb)
अणु
	वापस initial_apic_id >> index_msb;
पूर्ण

अटल पूर्णांक flat_probe(व्योम)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा apic apic_flat __ro_after_init = अणु
	.name				= "flat",
	.probe				= flat_probe,
	.acpi_madt_oem_check		= flat_acpi_madt_oem_check,
	.apic_id_valid			= शेष_apic_id_valid,
	.apic_id_रेजिस्टरed		= flat_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= true,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= flat_init_apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= flat_phys_pkg_id,

	.get_apic_id			= flat_get_apic_id,
	.set_apic_id			= set_apic_id,

	.calc_dest_apicid		= apic_flat_calc_apicid,

	.send_IPI			= शेष_send_IPI_single,
	.send_IPI_mask			= flat_send_IPI_mask,
	.send_IPI_mask_allbutself	= flat_send_IPI_mask_allbutself,
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
पूर्ण;

/*
 * Physflat mode is used when there are more than 8 CPUs on a प्रणाली.
 * We cannot use logical delivery in this हाल because the mask
 * overflows, so use physical mode.
 */
अटल पूर्णांक physflat_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
#अगर_घोषित CONFIG_ACPI
	/*
	 * Quirk: some x86_64 machines can only use physical APIC mode
	 * regardless of how many processors are present (x86_64 ES7000
	 * is an example).
	 */
	अगर (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
		(acpi_gbl_FADT.flags & ACPI_FADT_APIC_PHYSICAL)) अणु
		prपूर्णांकk(KERN_DEBUG "system APIC only can use physical flat");
		वापस 1;
	पूर्ण

	अगर (!म_भेदन(oem_id, "IBM", 3) && !म_भेदन(oem_table_id, "EXA", 3)) अणु
		prपूर्णांकk(KERN_DEBUG "IBM Summit detected, will use apic physical");
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम physflat_init_apic_ldr(व्योम)
अणु
	/*
	 * LDR and DFR are not involved in physflat mode, rather:
	 * "In physical destination mode, the destination processor is
	 * specअगरied by its local APIC ID [...]." (Intel SDM, 10.6.2.1)
	 */
पूर्ण

अटल पूर्णांक physflat_probe(व्योम)
अणु
	अगर (apic == &apic_physflat || num_possible_cpus() > 8 ||
	    jailhouse_paravirt())
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा apic apic_physflat __ro_after_init = अणु

	.name				= "physical flat",
	.probe				= physflat_probe,
	.acpi_madt_oem_check		= physflat_acpi_madt_oem_check,
	.apic_id_valid			= शेष_apic_id_valid,
	.apic_id_रेजिस्टरed		= flat_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= physflat_init_apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= flat_phys_pkg_id,

	.get_apic_id			= flat_get_apic_id,
	.set_apic_id			= set_apic_id,

	.calc_dest_apicid		= apic_शेष_calc_apicid,

	.send_IPI			= शेष_send_IPI_single_phys,
	.send_IPI_mask			= शेष_send_IPI_mask_sequence_phys,
	.send_IPI_mask_allbutself	= शेष_send_IPI_mask_allbutself_phys,
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
पूर्ण;

/*
 * We need to check क्रम physflat first, so this order is important.
 */
apic_drivers(apic_physflat, apic_flat);
