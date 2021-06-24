<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/smp.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>

#समावेश <xen/events.h>

#समावेश <xen/hvc-console.h>
#समावेश "xen-ops.h"
#समावेश "smp.h"

अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_resched_irq) = अणु .irq = -1 पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_callfunc_irq) = अणु .irq = -1 पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_callfuncsingle_irq) = अणु .irq = -1 पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा xen_common_irq, xen_debug_irq) = अणु .irq = -1 पूर्ण;

अटल irqवापस_t xen_call_function_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t xen_call_function_single_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/*
 * Reschedule call back.
 */
अटल irqवापस_t xen_reschedule_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	inc_irq_stat(irq_resched_count);
	scheduler_ipi();

	वापस IRQ_HANDLED;
पूर्ण

व्योम xen_smp_पूर्णांकr_मुक्त(अचिन्हित पूर्णांक cpu)
अणु
	अगर (per_cpu(xen_resched_irq, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_resched_irq, cpu).irq, शून्य);
		per_cpu(xen_resched_irq, cpu).irq = -1;
		kमुक्त(per_cpu(xen_resched_irq, cpu).name);
		per_cpu(xen_resched_irq, cpu).name = शून्य;
	पूर्ण
	अगर (per_cpu(xen_callfunc_irq, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_callfunc_irq, cpu).irq, शून्य);
		per_cpu(xen_callfunc_irq, cpu).irq = -1;
		kमुक्त(per_cpu(xen_callfunc_irq, cpu).name);
		per_cpu(xen_callfunc_irq, cpu).name = शून्य;
	पूर्ण
	अगर (per_cpu(xen_debug_irq, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_debug_irq, cpu).irq, शून्य);
		per_cpu(xen_debug_irq, cpu).irq = -1;
		kमुक्त(per_cpu(xen_debug_irq, cpu).name);
		per_cpu(xen_debug_irq, cpu).name = शून्य;
	पूर्ण
	अगर (per_cpu(xen_callfuncsingle_irq, cpu).irq >= 0) अणु
		unbind_from_irqhandler(per_cpu(xen_callfuncsingle_irq, cpu).irq,
				       शून्य);
		per_cpu(xen_callfuncsingle_irq, cpu).irq = -1;
		kमुक्त(per_cpu(xen_callfuncsingle_irq, cpu).name);
		per_cpu(xen_callfuncsingle_irq, cpu).name = शून्य;
	पूर्ण
पूर्ण

पूर्णांक xen_smp_पूर्णांकr_init(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc;
	अक्षर *resched_name, *callfunc_name, *debug_name;

	resched_name = kaप्र_लिखो(GFP_KERNEL, "resched%d", cpu);
	rc = bind_ipi_to_irqhandler(XEN_RESCHEDULE_VECTOR,
				    cpu,
				    xen_reschedule_पूर्णांकerrupt,
				    IRQF_PERCPU|IRQF_NOBALANCING,
				    resched_name,
				    शून्य);
	अगर (rc < 0)
		जाओ fail;
	per_cpu(xen_resched_irq, cpu).irq = rc;
	per_cpu(xen_resched_irq, cpu).name = resched_name;

	callfunc_name = kaप्र_लिखो(GFP_KERNEL, "callfunc%d", cpu);
	rc = bind_ipi_to_irqhandler(XEN_CALL_FUNCTION_VECTOR,
				    cpu,
				    xen_call_function_पूर्णांकerrupt,
				    IRQF_PERCPU|IRQF_NOBALANCING,
				    callfunc_name,
				    शून्य);
	अगर (rc < 0)
		जाओ fail;
	per_cpu(xen_callfunc_irq, cpu).irq = rc;
	per_cpu(xen_callfunc_irq, cpu).name = callfunc_name;

	अगर (!xen_fअगरo_events) अणु
		debug_name = kaप्र_लिखो(GFP_KERNEL, "debug%d", cpu);
		rc = bind_virq_to_irqhandler(VIRQ_DEBUG, cpu,
					     xen_debug_पूर्णांकerrupt,
					     IRQF_PERCPU | IRQF_NOBALANCING,
					     debug_name, शून्य);
		अगर (rc < 0)
			जाओ fail;
		per_cpu(xen_debug_irq, cpu).irq = rc;
		per_cpu(xen_debug_irq, cpu).name = debug_name;
	पूर्ण

	callfunc_name = kaप्र_लिखो(GFP_KERNEL, "callfuncsingle%d", cpu);
	rc = bind_ipi_to_irqhandler(XEN_CALL_FUNCTION_SINGLE_VECTOR,
				    cpu,
				    xen_call_function_single_पूर्णांकerrupt,
				    IRQF_PERCPU|IRQF_NOBALANCING,
				    callfunc_name,
				    शून्य);
	अगर (rc < 0)
		जाओ fail;
	per_cpu(xen_callfuncsingle_irq, cpu).irq = rc;
	per_cpu(xen_callfuncsingle_irq, cpu).name = callfunc_name;

	वापस 0;

 fail:
	xen_smp_पूर्णांकr_मुक्त(cpu);
	वापस rc;
पूर्ण

व्योम __init xen_smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu, rc, count = 0;

	अगर (xen_hvm_करोमुख्य())
		native_smp_cpus_करोne(max_cpus);
	अन्यथा
		calculate_max_logical_packages();

	अगर (xen_have_vcpu_info_placement)
		वापस;

	क्रम_each_online_cpu(cpu) अणु
		अगर (xen_vcpu_nr(cpu) < MAX_VIRT_CPUS)
			जारी;

		rc = हटाओ_cpu(cpu);

		अगर (rc == 0) अणु
			/*
			 * Reset vcpu_info so this cpu cannot be onlined again.
			 */
			xen_vcpu_info_reset(cpu);
			count++;
		पूर्ण अन्यथा अणु
			pr_warn("%s: failed to bring CPU %d down, error %d\n",
				__func__, cpu, rc);
		पूर्ण
	पूर्ण
	WARN(count, "%s: brought %d CPUs offline\n", __func__, count);
पूर्ण

व्योम xen_smp_send_reschedule(पूर्णांक cpu)
अणु
	xen_send_IPI_one(cpu, XEN_RESCHEDULE_VECTOR);
पूर्ण

अटल व्योम __xen_send_IPI_mask(स्थिर काष्ठा cpumask *mask,
			      पूर्णांक vector)
अणु
	अचिन्हित cpu;

	क्रम_each_cpu_and(cpu, mask, cpu_online_mask)
		xen_send_IPI_one(cpu, vector);
पूर्ण

व्योम xen_smp_send_call_function_ipi(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpu;

	__xen_send_IPI_mask(mask, XEN_CALL_FUNCTION_VECTOR);

	/* Make sure other vcpus get a chance to run अगर they need to. */
	क्रम_each_cpu(cpu, mask) अणु
		अगर (xen_vcpu_stolen(cpu)) अणु
			HYPERVISOR_sched_op(SCHEDOP_yield, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम xen_smp_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	__xen_send_IPI_mask(cpumask_of(cpu),
			  XEN_CALL_FUNCTION_SINGLE_VECTOR);
पूर्ण

अटल अंतरभूत पूर्णांक xen_map_vector(पूर्णांक vector)
अणु
	पूर्णांक xen_vector;

	चयन (vector) अणु
	हाल RESCHEDULE_VECTOR:
		xen_vector = XEN_RESCHEDULE_VECTOR;
		अवरोध;
	हाल CALL_FUNCTION_VECTOR:
		xen_vector = XEN_CALL_FUNCTION_VECTOR;
		अवरोध;
	हाल CALL_FUNCTION_SINGLE_VECTOR:
		xen_vector = XEN_CALL_FUNCTION_SINGLE_VECTOR;
		अवरोध;
	हाल IRQ_WORK_VECTOR:
		xen_vector = XEN_IRQ_WORK_VECTOR;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल NMI_VECTOR:
	हाल APIC_DM_NMI: /* Some use that instead of NMI_VECTOR */
		xen_vector = XEN_NMI_VECTOR;
		अवरोध;
#पूर्ण_अगर
	शेष:
		xen_vector = -1;
		prपूर्णांकk(KERN_ERR "xen: vector 0x%x is not implemented\n",
			vector);
	पूर्ण

	वापस xen_vector;
पूर्ण

व्योम xen_send_IPI_mask(स्थिर काष्ठा cpumask *mask,
			      पूर्णांक vector)
अणु
	पूर्णांक xen_vector = xen_map_vector(vector);

	अगर (xen_vector >= 0)
		__xen_send_IPI_mask(mask, xen_vector);
पूर्ण

व्योम xen_send_IPI_all(पूर्णांक vector)
अणु
	पूर्णांक xen_vector = xen_map_vector(vector);

	अगर (xen_vector >= 0)
		__xen_send_IPI_mask(cpu_online_mask, xen_vector);
पूर्ण

व्योम xen_send_IPI_self(पूर्णांक vector)
अणु
	पूर्णांक xen_vector = xen_map_vector(vector);

	अगर (xen_vector >= 0)
		xen_send_IPI_one(smp_processor_id(), xen_vector);
पूर्ण

व्योम xen_send_IPI_mask_allbutself(स्थिर काष्ठा cpumask *mask,
				पूर्णांक vector)
अणु
	अचिन्हित cpu;
	अचिन्हित पूर्णांक this_cpu = smp_processor_id();
	पूर्णांक xen_vector = xen_map_vector(vector);

	अगर (!(num_online_cpus() > 1) || (xen_vector < 0))
		वापस;

	क्रम_each_cpu_and(cpu, mask, cpu_online_mask) अणु
		अगर (this_cpu == cpu)
			जारी;

		xen_send_IPI_one(cpu, xen_vector);
	पूर्ण
पूर्ण

व्योम xen_send_IPI_allbutself(पूर्णांक vector)
अणु
	xen_send_IPI_mask_allbutself(cpu_online_mask, vector);
पूर्ण

अटल irqवापस_t xen_call_function_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	irq_enter();
	generic_smp_call_function_पूर्णांकerrupt();
	inc_irq_stat(irq_call_count);
	irq_निकास();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xen_call_function_single_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	irq_enter();
	generic_smp_call_function_single_पूर्णांकerrupt();
	inc_irq_stat(irq_call_count);
	irq_निकास();

	वापस IRQ_HANDLED;
पूर्ण
