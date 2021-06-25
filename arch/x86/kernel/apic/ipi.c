<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/io_apic.h>

#समावेश "local.h"

DEFINE_STATIC_KEY_FALSE(apic_use_ipi_लघुhand);

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक apic_ipi_लघुhand_off __ro_after_init;

अटल __init पूर्णांक apic_ipi_लघुhand(अक्षर *str)
अणु
	get_option(&str, &apic_ipi_लघुhand_off);
	वापस 1;
पूर्ण
__setup("no_ipi_broadcast=", apic_ipi_लघुhand);

अटल पूर्णांक __init prपूर्णांक_ipi_mode(व्योम)
अणु
	pr_info("IPI shorthand broadcast: %s\n",
		apic_ipi_लघुhand_off ? "disabled" : "enabled");
	वापस 0;
पूर्ण
late_initcall(prपूर्णांक_ipi_mode);

व्योम apic_smt_update(व्योम)
अणु
	/*
	 * Do not चयन to broadcast mode अगर:
	 * - Disabled on the command line
	 * - Only a single CPU is online
	 * - Not all present CPUs have been at least booted once
	 *
	 * The latter is important as the local APIC might be in some
	 * अक्रमom state and a broadcast might cause havoc. That's
	 * especially true क्रम NMI broadcasting.
	 */
	अगर (apic_ipi_लघुhand_off || num_online_cpus() == 1 ||
	    !cpumask_equal(cpu_present_mask, &cpus_booted_once_mask)) अणु
		अटल_branch_disable(&apic_use_ipi_लघुhand);
	पूर्ण अन्यथा अणु
		अटल_branch_enable(&apic_use_ipi_लघुhand);
	पूर्ण
पूर्ण

व्योम apic_send_IPI_allbutself(अचिन्हित पूर्णांक vector)
अणु
	अगर (num_online_cpus() < 2)
		वापस;

	अगर (अटल_branch_likely(&apic_use_ipi_लघुhand))
		apic->send_IPI_allbutself(vector);
	अन्यथा
		apic->send_IPI_mask_allbutself(cpu_online_mask, vector);
पूर्ण

/*
 * Send a 'reschedule' IPI to another CPU. It goes straight through and
 * wastes no समय serializing anything. Worst हाल is that we lose a
 * reschedule ...
 */
व्योम native_smp_send_reschedule(पूर्णांक cpu)
अणु
	अगर (unlikely(cpu_is_offline(cpu))) अणु
		WARN(1, "sched: Unexpected reschedule of offline CPU#%d!\n", cpu);
		वापस;
	पूर्ण
	apic->send_IPI(cpu, RESCHEDULE_VECTOR);
पूर्ण

व्योम native_send_call_func_single_ipi(पूर्णांक cpu)
अणु
	apic->send_IPI(cpu, CALL_FUNCTION_SINGLE_VECTOR);
पूर्ण

व्योम native_send_call_func_ipi(स्थिर काष्ठा cpumask *mask)
अणु
	अगर (अटल_branch_likely(&apic_use_ipi_लघुhand)) अणु
		अचिन्हित पूर्णांक cpu = smp_processor_id();

		अगर (!cpumask_or_equal(mask, cpumask_of(cpu), cpu_online_mask))
			जाओ sendmask;

		अगर (cpumask_test_cpu(cpu, mask))
			apic->send_IPI_all(CALL_FUNCTION_VECTOR);
		अन्यथा अगर (num_online_cpus() > 1)
			apic->send_IPI_allbutself(CALL_FUNCTION_VECTOR);
		वापस;
	पूर्ण

sendmask:
	apic->send_IPI_mask(mask, CALL_FUNCTION_VECTOR);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल अंतरभूत पूर्णांक __prepare_ICR2(अचिन्हित पूर्णांक mask)
अणु
	वापस SET_APIC_DEST_FIELD(mask);
पूर्ण

अटल अंतरभूत व्योम __xapic_रुको_icr_idle(व्योम)
अणु
	जबतक (native_apic_mem_पढ़ो(APIC_ICR) & APIC_ICR_BUSY)
		cpu_relax();
पूर्ण

व्योम __शेष_send_IPI_लघुcut(अचिन्हित पूर्णांक लघुcut, पूर्णांक vector)
अणु
	/*
	 * Subtle. In the हाल of the 'never do double writes' workaround
	 * we have to lock out पूर्णांकerrupts to be safe.  As we करोn't care
	 * of the value पढ़ो we use an atomic rmw access to aव्योम costly
	 * cli/sti.  Otherwise we use an even cheaper single atomic ग_लिखो
	 * to the APIC.
	 */
	अचिन्हित पूर्णांक cfg;

	/*
	 * Wait क्रम idle.
	 */
	अगर (unlikely(vector == NMI_VECTOR))
		safe_apic_रुको_icr_idle();
	अन्यथा
		__xapic_रुको_icr_idle();

	/*
	 * No need to touch the target chip field. Also the destination
	 * mode is ignored when a लघुhand is used.
	 */
	cfg = __prepare_ICR(लघुcut, vector, 0);

	/*
	 * Send the IPI. The ग_लिखो to APIC_ICR fires this off.
	 */
	native_apic_mem_ग_लिखो(APIC_ICR, cfg);
पूर्ण

/*
 * This is used to send an IPI with no लघुhand notation (the destination is
 * specअगरied in bits 56 to 63 of the ICR).
 */
व्योम __शेष_send_IPI_dest_field(अचिन्हित पूर्णांक mask, पूर्णांक vector, अचिन्हित पूर्णांक dest)
अणु
	अचिन्हित दीर्घ cfg;

	/*
	 * Wait क्रम idle.
	 */
	अगर (unlikely(vector == NMI_VECTOR))
		safe_apic_रुको_icr_idle();
	अन्यथा
		__xapic_रुको_icr_idle();

	/*
	 * prepare target chip field
	 */
	cfg = __prepare_ICR2(mask);
	native_apic_mem_ग_लिखो(APIC_ICR2, cfg);

	/*
	 * program the ICR
	 */
	cfg = __prepare_ICR(0, vector, dest);

	/*
	 * Send the IPI. The ग_लिखो to APIC_ICR fires this off.
	 */
	native_apic_mem_ग_लिखो(APIC_ICR, cfg);
पूर्ण

व्योम शेष_send_IPI_single_phys(पूर्णांक cpu, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__शेष_send_IPI_dest_field(per_cpu(x86_cpu_to_apicid, cpu),
				      vector, APIC_DEST_PHYSICAL);
	local_irq_restore(flags);
पूर्ण

व्योम शेष_send_IPI_mask_sequence_phys(स्थिर काष्ठा cpumask *mask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ query_cpu;
	अचिन्हित दीर्घ flags;

	/*
	 * Hack. The clustered APIC addressing mode करोesn't allow us to send
	 * to an arbitrary mask, so I करो a unicast to each CPU instead.
	 * - mbligh
	 */
	local_irq_save(flags);
	क्रम_each_cpu(query_cpu, mask) अणु
		__शेष_send_IPI_dest_field(per_cpu(x86_cpu_to_apicid,
				query_cpu), vector, APIC_DEST_PHYSICAL);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

व्योम शेष_send_IPI_mask_allbutself_phys(स्थिर काष्ठा cpumask *mask,
						 पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	अचिन्हित पूर्णांक query_cpu;
	अचिन्हित दीर्घ flags;

	/* See Hack comment above */

	local_irq_save(flags);
	क्रम_each_cpu(query_cpu, mask) अणु
		अगर (query_cpu == this_cpu)
			जारी;
		__शेष_send_IPI_dest_field(per_cpu(x86_cpu_to_apicid,
				 query_cpu), vector, APIC_DEST_PHYSICAL);
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * Helper function क्रम APICs which insist on cpumasks
 */
व्योम शेष_send_IPI_single(पूर्णांक cpu, पूर्णांक vector)
अणु
	apic->send_IPI_mask(cpumask_of(cpu), vector);
पूर्ण

व्योम शेष_send_IPI_allbutself(पूर्णांक vector)
अणु
	__शेष_send_IPI_लघुcut(APIC_DEST_ALLBUT, vector);
पूर्ण

व्योम शेष_send_IPI_all(पूर्णांक vector)
अणु
	__शेष_send_IPI_लघुcut(APIC_DEST_ALLINC, vector);
पूर्ण

व्योम शेष_send_IPI_self(पूर्णांक vector)
अणु
	__शेष_send_IPI_लघुcut(APIC_DEST_SELF, vector);
पूर्ण

#अगर_घोषित CONFIG_X86_32

व्योम शेष_send_IPI_mask_sequence_logical(स्थिर काष्ठा cpumask *mask,
						 पूर्णांक vector)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक query_cpu;

	/*
	 * Hack. The clustered APIC addressing mode करोesn't allow us to send
	 * to an arbitrary mask, so I करो a unicasts to each CPU instead. This
	 * should be modअगरied to करो 1 message per cluster ID - mbligh
	 */

	local_irq_save(flags);
	क्रम_each_cpu(query_cpu, mask)
		__शेष_send_IPI_dest_field(
			early_per_cpu(x86_cpu_to_logical_apicid, query_cpu),
			vector, APIC_DEST_LOGICAL);
	local_irq_restore(flags);
पूर्ण

व्योम शेष_send_IPI_mask_allbutself_logical(स्थिर काष्ठा cpumask *mask,
						 पूर्णांक vector)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक query_cpu;
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();

	/* See Hack comment above */

	local_irq_save(flags);
	क्रम_each_cpu(query_cpu, mask) अणु
		अगर (query_cpu == this_cpu)
			जारी;
		__शेष_send_IPI_dest_field(
			early_per_cpu(x86_cpu_to_logical_apicid, query_cpu),
			vector, APIC_DEST_LOGICAL);
		पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * This is only used on smaller machines.
 */
व्योम शेष_send_IPI_mask_logical(स्थिर काष्ठा cpumask *cpumask, पूर्णांक vector)
अणु
	अचिन्हित दीर्घ mask = cpumask_bits(cpumask)[0];
	अचिन्हित दीर्घ flags;

	अगर (!mask)
		वापस;

	local_irq_save(flags);
	WARN_ON(mask & ~cpumask_bits(cpu_online_mask)[0]);
	__शेष_send_IPI_dest_field(mask, vector, APIC_DEST_LOGICAL);
	local_irq_restore(flags);
पूर्ण

/* must come after the send_IPI functions above क्रम inlining */
अटल पूर्णांक convert_apicid_to_cpu(पूर्णांक apic_id)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		अगर (per_cpu(x86_cpu_to_apicid, i) == apic_id)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

पूर्णांक safe_smp_processor_id(व्योम)
अणु
	पूर्णांक apicid, cpuid;

	अगर (!boot_cpu_has(X86_FEATURE_APIC))
		वापस 0;

	apicid = hard_smp_processor_id();
	अगर (apicid == BAD_APICID)
		वापस 0;

	cpuid = convert_apicid_to_cpu(apicid);

	वापस cpuid >= 0 ? cpuid : 0;
पूर्ण
#पूर्ण_अगर
