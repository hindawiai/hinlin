<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NOOP APIC driver.
 *
 * Does almost nothing and should be substituted by a real apic driver via
 * probe routine.
 *
 * Though in हाल अगर apic is disabled (क्रम some reason) we try
 * to not uglअगरy the caller's code and allow to call (some) apic routines
 * like self-ipi, etc...
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/apic.h>

अटल व्योम noop_init_apic_ldr(व्योम) अणु पूर्ण
अटल व्योम noop_send_IPI(पूर्णांक cpu, पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_send_IPI_mask(स्थिर काष्ठा cpumask *cpumask, पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *cpumask, पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_send_IPI_allbutself(पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_send_IPI_all(पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_send_IPI_self(पूर्णांक vector) अणु पूर्ण
अटल व्योम noop_apic_रुको_icr_idle(व्योम) अणु पूर्ण
अटल व्योम noop_apic_icr_ग_लिखो(u32 low, u32 id) अणु पूर्ण

अटल पूर्णांक noop_wakeup_secondary_cpu(पूर्णांक apicid, अचिन्हित दीर्घ start_eip)
अणु
	वापस -1;
पूर्ण

अटल u32 noop_safe_apic_रुको_icr_idle(व्योम)
अणु
	वापस 0;
पूर्ण

अटल u64 noop_apic_icr_पढ़ो(व्योम)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक noop_phys_pkg_id(पूर्णांक cpuid_apic, पूर्णांक index_msb)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक noop_get_apic_id(अचिन्हित दीर्घ x)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक noop_probe(व्योम)
अणु
	/*
	 * NOOP apic should not ever be
	 * enabled via probe routine
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक noop_apic_id_रेजिस्टरed(व्योम)
अणु
	/*
	 * अगर we would be really "pedantic"
	 * we should pass पढ़ो_apic_id() here
	 * but since NOOP suppose APIC ID = 0
	 * lets save a few cycles
	 */
	वापस physid_isset(0, phys_cpu_present_map);
पूर्ण

अटल u32 noop_apic_पढ़ो(u32 reg)
अणु
	WARN_ON_ONCE(boot_cpu_has(X86_FEATURE_APIC) && !disable_apic);
	वापस 0;
पूर्ण

अटल व्योम noop_apic_ग_लिखो(u32 reg, u32 v)
अणु
	WARN_ON_ONCE(boot_cpu_has(X86_FEATURE_APIC) && !disable_apic);
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक noop_x86_32_early_logical_apicid(पूर्णांक cpu)
अणु
	वापस BAD_APICID;
पूर्ण
#पूर्ण_अगर

काष्ठा apic apic_noop __ro_after_init = अणु
	.name				= "noop",
	.probe				= noop_probe,
	.acpi_madt_oem_check		= शून्य,

	.apic_id_valid			= शेष_apic_id_valid,
	.apic_id_रेजिस्टरed		= noop_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= true,

	.disable_esr			= 0,

	.check_apicid_used		= शेष_check_apicid_used,
	.init_apic_ldr			= noop_init_apic_ldr,
	.ioapic_phys_id_map		= शेष_ioapic_phys_id_map,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= physid_set_mask_of_physid,

	.check_phys_apicid_present	= शेष_check_phys_apicid_present,

	.phys_pkg_id			= noop_phys_pkg_id,

	.get_apic_id			= noop_get_apic_id,
	.set_apic_id			= शून्य,

	.calc_dest_apicid		= apic_flat_calc_apicid,

	.send_IPI			= noop_send_IPI,
	.send_IPI_mask			= noop_send_IPI_mask,
	.send_IPI_mask_allbutself	= noop_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= noop_send_IPI_allbutself,
	.send_IPI_all			= noop_send_IPI_all,
	.send_IPI_self			= noop_send_IPI_self,

	.wakeup_secondary_cpu		= noop_wakeup_secondary_cpu,

	.inquire_remote_apic		= शून्य,

	.पढ़ो				= noop_apic_पढ़ो,
	.ग_लिखो				= noop_apic_ग_लिखो,
	.eoi_ग_लिखो			= noop_apic_ग_लिखो,
	.icr_पढ़ो			= noop_apic_icr_पढ़ो,
	.icr_ग_लिखो			= noop_apic_icr_ग_लिखो,
	.रुको_icr_idle			= noop_apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= noop_safe_apic_रुको_icr_idle,

#अगर_घोषित CONFIG_X86_32
	.x86_32_early_logical_apicid	= noop_x86_32_early_logical_apicid,
#पूर्ण_अगर
पूर्ण;
