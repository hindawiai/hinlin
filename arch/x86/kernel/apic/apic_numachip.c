<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Numascale NumaConnect-Specअगरic APIC Code
 *
 * Copyright (C) 2011 Numascale AS. All rights reserved.
 *
 * Send feedback to <support@numascale.com>
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/numachip/numachip.h>
#समावेश <यंत्र/numachip/numachip_csr.h>


#समावेश "local.h"

u8 numachip_प्रणाली __पढ़ो_mostly;
अटल स्थिर काष्ठा apic apic_numachip1;
अटल स्थिर काष्ठा apic apic_numachip2;
अटल व्योम (*numachip_apic_icr_ग_लिखो)(पूर्णांक apicid, अचिन्हित पूर्णांक val) __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक numachip1_get_apic_id(अचिन्हित दीर्घ x)
अणु
	अचिन्हित दीर्घ value;
	अचिन्हित पूर्णांक id = (x >> 24) & 0xff;

	अगर (अटल_cpu_has(X86_FEATURE_NODEID_MSR)) अणु
		rdmsrl(MSR_FAM10H_NODE_ID, value);
		id |= (value << 2) & 0xff00;
	पूर्ण

	वापस id;
पूर्ण

अटल u32 numachip1_set_apic_id(अचिन्हित पूर्णांक id)
अणु
	वापस (id & 0xff) << 24;
पूर्ण

अटल अचिन्हित पूर्णांक numachip2_get_apic_id(अचिन्हित दीर्घ x)
अणु
	u64 mcfg;

	rdmsrl(MSR_FAM10H_MMIO_CONF_BASE, mcfg);
	वापस ((mcfg >> (28 - 8)) & 0xfff00) | (x >> 24);
पूर्ण

अटल u32 numachip2_set_apic_id(अचिन्हित पूर्णांक id)
अणु
	वापस id << 24;
पूर्ण

अटल पूर्णांक numachip_apic_id_valid(u32 apicid)
अणु
	/* Trust what bootloader passes in MADT */
	वापस 1;
पूर्ण

अटल पूर्णांक numachip_apic_id_रेजिस्टरed(व्योम)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक numachip_phys_pkg_id(पूर्णांक initial_apic_id, पूर्णांक index_msb)
अणु
	वापस initial_apic_id >> index_msb;
पूर्ण

अटल व्योम numachip1_apic_icr_ग_लिखो(पूर्णांक apicid, अचिन्हित पूर्णांक val)
अणु
	ग_लिखो_lcsr(CSR_G3_EXT_IRQ_GEN, (apicid << 16) | val);
पूर्ण

अटल व्योम numachip2_apic_icr_ग_लिखो(पूर्णांक apicid, अचिन्हित पूर्णांक val)
अणु
	numachip2_ग_लिखो32_lcsr(NUMACHIP2_APIC_ICR, (apicid << 12) | val);
पूर्ण

अटल पूर्णांक numachip_wakeup_secondary(पूर्णांक phys_apicid, अचिन्हित दीर्घ start_rip)
अणु
	numachip_apic_icr_ग_लिखो(phys_apicid, APIC_DM_INIT);
	numachip_apic_icr_ग_लिखो(phys_apicid, APIC_DM_STARTUP |
		(start_rip >> 12));

	वापस 0;
पूर्ण

अटल व्योम numachip_send_IPI_one(पूर्णांक cpu, पूर्णांक vector)
अणु
	पूर्णांक local_apicid, apicid = per_cpu(x86_cpu_to_apicid, cpu);
	अचिन्हित पूर्णांक dmode;

	preempt_disable();
	local_apicid = __this_cpu_पढ़ो(x86_cpu_to_apicid);

	/* Send via local APIC where non-local part matches */
	अगर (!((apicid ^ local_apicid) >> NUMACHIP_LAPIC_BITS)) अणु
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		__शेष_send_IPI_dest_field(apicid, vector,
			APIC_DEST_PHYSICAL);
		local_irq_restore(flags);
		preempt_enable();
		वापस;
	पूर्ण
	preempt_enable();

	dmode = (vector == NMI_VECTOR) ? APIC_DM_NMI : APIC_DM_FIXED;
	numachip_apic_icr_ग_लिखो(apicid, dmode | vector);
पूर्ण

अटल व्योम numachip_send_IPI_mask(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask)
		numachip_send_IPI_one(cpu, vector);
पूर्ण

अटल व्योम numachip_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask,
						पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, mask) अणु
		अगर (cpu != this_cpu)
			numachip_send_IPI_one(cpu, vector);
	पूर्ण
पूर्ण

अटल व्योम numachip_send_IPI_allbutself(पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu != this_cpu)
			numachip_send_IPI_one(cpu, vector);
	पूर्ण
पूर्ण

अटल व्योम numachip_send_IPI_all(पूर्णांक vector)
अणु
	numachip_send_IPI_mask(cpu_online_mask, vector);
पूर्ण

अटल व्योम numachip_send_IPI_self(पूर्णांक vector)
अणु
	apic_ग_लिखो(APIC_SELF_IPI, vector);
पूर्ण

अटल पूर्णांक __init numachip1_probe(व्योम)
अणु
	वापस apic == &apic_numachip1;
पूर्ण

अटल पूर्णांक __init numachip2_probe(व्योम)
अणु
	वापस apic == &apic_numachip2;
पूर्ण

अटल व्योम fixup_cpu_id(काष्ठा cpuinfo_x86 *c, पूर्णांक node)
अणु
	u64 val;
	u32 nodes = 1;

	this_cpu_ग_लिखो(cpu_llc_id, node);

	/* Account क्रम nodes per socket in multi-core-module processors */
	अगर (boot_cpu_has(X86_FEATURE_NODEID_MSR)) अणु
		rdmsrl(MSR_FAM10H_NODE_ID, val);
		nodes = ((val >> 3) & 7) + 1;
	पूर्ण

	c->phys_proc_id = node / nodes;
पूर्ण

अटल पूर्णांक __init numachip_प्रणाली_init(व्योम)
अणु
	/* Map the LCSR area and set up the apic_icr_ग_लिखो function */
	चयन (numachip_प्रणाली) अणु
	हाल 1:
		init_extra_mapping_uc(NUMACHIP_LCSR_BASE, NUMACHIP_LCSR_SIZE);
		numachip_apic_icr_ग_लिखो = numachip1_apic_icr_ग_लिखो;
		अवरोध;
	हाल 2:
		init_extra_mapping_uc(NUMACHIP2_LCSR_BASE, NUMACHIP2_LCSR_SIZE);
		numachip_apic_icr_ग_लिखो = numachip2_apic_icr_ग_लिखो;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	x86_cpuinit.fixup_cpu_id = fixup_cpu_id;
	x86_init.pci.arch_init = pci_numachip_init;

	वापस 0;
पूर्ण
early_initcall(numachip_प्रणाली_init);

अटल पूर्णांक numachip1_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	अगर ((म_भेदन(oem_id, "NUMASC", 6) != 0) ||
	    (म_भेदन(oem_table_id, "NCONNECT", 8) != 0))
		वापस 0;

	numachip_प्रणाली = 1;

	वापस 1;
पूर्ण

अटल पूर्णांक numachip2_acpi_madt_oem_check(अक्षर *oem_id, अक्षर *oem_table_id)
अणु
	अगर ((म_भेदन(oem_id, "NUMASC", 6) != 0) ||
	    (म_भेदन(oem_table_id, "NCONECT2", 8) != 0))
		वापस 0;

	numachip_प्रणाली = 2;

	वापस 1;
पूर्ण

/* APIC IPIs are queued */
अटल व्योम numachip_apic_रुको_icr_idle(व्योम)
अणु
पूर्ण

/* APIC NMI IPIs are queued */
अटल u32 numachip_safe_apic_रुको_icr_idle(व्योम)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा apic apic_numachip1 __refस्थिर = अणु
	.name				= "NumaConnect system",
	.probe				= numachip1_probe,
	.acpi_madt_oem_check		= numachip1_acpi_madt_oem_check,
	.apic_id_valid			= numachip_apic_id_valid,
	.apic_id_रेजिस्टरed		= numachip_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= flat_init_apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= numachip_phys_pkg_id,

	.get_apic_id			= numachip1_get_apic_id,
	.set_apic_id			= numachip1_set_apic_id,

	.calc_dest_apicid		= apic_शेष_calc_apicid,

	.send_IPI			= numachip_send_IPI_one,
	.send_IPI_mask			= numachip_send_IPI_mask,
	.send_IPI_mask_allbutself	= numachip_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= numachip_send_IPI_allbutself,
	.send_IPI_all			= numachip_send_IPI_all,
	.send_IPI_self			= numachip_send_IPI_self,

	.wakeup_secondary_cpu		= numachip_wakeup_secondary,
	.inquire_remote_apic		= शून्य, /* REMRD not supported */

	.पढ़ो				= native_apic_mem_पढ़ो,
	.ग_लिखो				= native_apic_mem_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_mem_ग_लिखो,
	.icr_पढ़ो			= native_apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_apic_icr_ग_लिखो,
	.रुको_icr_idle			= numachip_apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= numachip_safe_apic_रुको_icr_idle,
पूर्ण;

apic_driver(apic_numachip1);

अटल स्थिर काष्ठा apic apic_numachip2 __refस्थिर = अणु
	.name				= "NumaConnect2 system",
	.probe				= numachip2_probe,
	.acpi_madt_oem_check		= numachip2_acpi_madt_oem_check,
	.apic_id_valid			= numachip_apic_id_valid,
	.apic_id_रेजिस्टरed		= numachip_apic_id_रेजिस्टरed,

	.delivery_mode			= APIC_DELIVERY_MODE_FIXED,
	.dest_mode_logical		= false,

	.disable_esr			= 0,

	.check_apicid_used		= शून्य,
	.init_apic_ldr			= flat_init_apic_ldr,
	.ioapic_phys_id_map		= शून्य,
	.setup_apic_routing		= शून्य,
	.cpu_present_to_apicid		= शेष_cpu_present_to_apicid,
	.apicid_to_cpu_present		= शून्य,
	.check_phys_apicid_present	= शेष_check_phys_apicid_present,
	.phys_pkg_id			= numachip_phys_pkg_id,

	.get_apic_id			= numachip2_get_apic_id,
	.set_apic_id			= numachip2_set_apic_id,

	.calc_dest_apicid		= apic_शेष_calc_apicid,

	.send_IPI			= numachip_send_IPI_one,
	.send_IPI_mask			= numachip_send_IPI_mask,
	.send_IPI_mask_allbutself	= numachip_send_IPI_mask_allbutself,
	.send_IPI_allbutself		= numachip_send_IPI_allbutself,
	.send_IPI_all			= numachip_send_IPI_all,
	.send_IPI_self			= numachip_send_IPI_self,

	.wakeup_secondary_cpu		= numachip_wakeup_secondary,
	.inquire_remote_apic		= शून्य, /* REMRD not supported */

	.पढ़ो				= native_apic_mem_पढ़ो,
	.ग_लिखो				= native_apic_mem_ग_लिखो,
	.eoi_ग_लिखो			= native_apic_mem_ग_लिखो,
	.icr_पढ़ो			= native_apic_icr_पढ़ो,
	.icr_ग_लिखो			= native_apic_icr_ग_लिखो,
	.रुको_icr_idle			= numachip_apic_रुको_icr_idle,
	.safe_रुको_icr_idle		= numachip_safe_apic_रुको_icr_idle,
पूर्ण;

apic_driver(apic_numachip2);
