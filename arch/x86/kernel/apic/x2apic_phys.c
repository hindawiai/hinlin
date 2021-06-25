<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/cpumask.h>
#समावेश <linux/acpi.h>

#समावेश "local.h"

पूर्णांक x2apic_phys;

अटल काष्ठा apic apic_x2apic_phys;
अटल u32 x2apic_max_apicid __ro_after_init;

व्योम __init x2apic_set_max_apicid(u32 apicid)
अणु
	x2apic_max_apicid = apicid;
पूर्ण

अटल पूर्णांक __init set_x2apic_phys_mode(अक्षर *arg)
अणु
	x2apic_phys = 1;
	वापस 0;
पूर्ण
early_param("x2apic_phys", set_x2apic_phys_mode);

अटल bool x2apic_fadt_phys(व्योम)
अणु
#अगर_घोषित CONFIG_ACPI
	अगर ((acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID) &&
		(acpi_gbl_FADT.flags & ACPI_FADT_APIC_PHYSICAL)) अणु
		prपूर्णांकk(KERN_DEBUG "System requires x2apic physical mode\n");
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक x2apic_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	वापस x2apic_enabled() && (x2apic_phys || x2apic_fadt_phys());
पूर्ण

अटल व्योम x2apic_send_IPI(पूर्णांक cpu, पूर्णांक vector)
अणु
	u32 dest = per_cpu(x86_cpu_to_apicid, cpu);

	/* x2apic MSRs are special and need a special fence: */
	weak_wrmsr_fence();
	__x2apic_send_IPI_dest(dest, vector, APIC_DEST_PHYSICAL);
पूर्ण

अटल व्योम
__x2apic_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector, पूर्णांक apic_dest)
अणु
	अचिन्हित दीर्घ query_cpu;
	अचिन्हित दीर्घ this_cpu;
	अचिन्हित दीर्घ flags;

	/* x2apic MSRs are special and need a special fence: */
	weak_wrmsr_fence();

	local_irq_save(flags);

	this_cpu = smp_processor_id();
	क्रम_each_cpu(query_cpu, mask) अणु
		अगर (apic_dest == APIC_DEST_ALLBUT && this_cpu == query_cpu)
			जारी;
		__x2apic_send_IPI_dest(per_cpu(x86_cpu_to_apicid, query_cpu),
				       vector, APIC_DEST_PHYSICAL);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

अटल व्योम x2apic_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLINC);
पूर्ण

अटल व्योम
 x2apic_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	__x2apic_send_IPI_mask(mask, vector, APIC_DEST_ALLBUT);
पूर्ण

अटल व्योम x2apic_send_IPI_allbutself(पूर्णांक vector)
अणु
	__x2apic_send_IPI_लघुhand(vector, APIC_DEST_ALLBUT);
पूर्ण

अटल व्योम x2apic_send_IPI_all(पूर्णांक vector)
अणु
	__x2apic_send_IPI_लघुhand(vector, APIC_DEST_ALLINC);
पूर्ण

अटल व्योम init_x2apic_ldr(व्योम)
अणु
पूर्ण

अटल पूर्णांक x2apic_phys_probe(व्योम)
अणु
	अगर (x2apic_mode && (x2apic_phys || x2apic_fadt_phys()))
		वापस 1;

	वापस apic == &apic_x2apic_phys;
पूर्ण

/* Common x2apic functions, also used by x2apic_cluster */
पूर्णांक x2apic_apic_id_valid(u32 apicid)
अणु
	अगर (x2apic_max_apicid && apicid > x2apic_max_apicid)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक x2apic_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस 1;
पूर्ण

व्योम __x2apic_send_IPI_dest(अचिन्हित पूर्णांक apicid, पूर्णांक vector, अचिन्हित पूर्णांक dest)
अणु
	अचिन्हित दीर्घ cfg = __prepare_ICR(0, vector, dest);
	native_x2apic_icr_ग_लिखो(cfg, apicid);
पूर्ण

व्योम __x2apic_send_IPI_लघुhand(पूर्णांक vector, u32 which)
अणु
	अचिन्हित दीर्घ cfg = __prepare_ICR(which, vector, 0);

	/* x2apic MSRs are special and need a special fence: */
	weak_wrmsr_fence();
	native_x2apic_icr_ग_लिखो(cfg, 0);
पूर्ण

अचिन्हित पूर्णांक x2apic_get_apic_id(अचिन्हित दीर्घ id)
अणु
	वापस id;
पूर्ण

u32 x2apic_set_apic_id(अचिन्हित पूर्णांक id)
अणु
	वापस id;
पूर्ण

पूर्णांक x2apic_phys_pkg_id(पूर्णांक initial_apicid, पूर्णांक index_msb)
अणु
	वापस initial_apicid >> index_msb;
पूर्ण

व्योम x2apic_send_IPI_self(पूर्णांक vector)
अणु
	apic_ग_लिखो(APIC_SELF_IPI, vector);
पूर्ण

अटल काष्ठा apic apic_x2apic_phys __ro_after_init = अणु

	.name				= "physical x2apic",
	.probe				= x2apic_phys_probe,
	.acpi_madt_oem_check		= x2apic_acpi_madt_oem_check,
	.apic_id_valid			= x2apic_apic_id_valid,
	.apic_id_रेजिस्टरed		= x2apic_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= init_x2apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= x2apic_phys_pkg_id,

	.get_apic_id			= x2apic_get_apic_id,
	.set_apic_id			= x2apic_set_apic_id,

	.calc_dest_apicid		= apic_शेष_calc_apicid,

	.send_IPI			= x2apic_send_IPI,
	.send_IPI_mask			= x2apic_send_IPI_mask,
	.send_IPI_mask_allbutself	= x2apic_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= x2apic_send_IPI_allbutself,
	.send_IPI_all			= x2apic_send_IPI_all,
	.send_IPI_self			= x2apic_send_IPI_self,

	.inquire_remote_apic		= शून्य,

	.पढ़ो				= native_apic_msr_पढ़ो,
	.ग_लिखो				= native_apic_msr_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_msr_eoi_ग_लिखो,
	.icr_पढ़ो			= native_x2apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_x2apic_icr_ग_लिखो,
	.रुको_icr_idle			= native_x2apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= native_safe_x2apic_रुको_icr_idle,
पूर्ण;

apic_driver(apic_x2apic_phys);
