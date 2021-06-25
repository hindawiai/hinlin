<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/smp.h>

#समावेश <xen/events.h>

#समावेश "xen-ops.h"
#समावेश "smp.h"


अटल व्योम __init xen_hvm_smp_prepare_boot_cpu(व्योम)
अणु
	BUG_ON(smp_processor_id() != 0);
	native_smp_prepare_boot_cpu();

	/*
	 * Setup vcpu_info क्रम boot CPU. Secondary CPUs get their vcpu_info
	 * in xen_cpu_up_prepare_hvm().
	 */
	xen_vcpu_setup(0);

	/*
	 * The alternative logic (which patches the unlock/lock) runs beक्रमe
	 * the smp bootup up code is activated. Hence we need to set this up
	 * the core kernel is being patched. Otherwise we will have only
	 * modules patched but not core code.
	 */
	xen_init_spinlocks();
पूर्ण

अटल व्योम __init xen_hvm_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	पूर्णांक cpu;

	native_smp_prepare_cpus(max_cpus);

	अगर (xen_have_vector_callback) अणु
		WARN_ON(xen_smp_पूर्णांकr_init(0));
		xen_init_lock_cpu(0);
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == 0)
			जारी;

		/* Set शेष vcpu_id to make sure that we करोn't use cpu-0's */
		per_cpu(xen_vcpu_id, cpu) = XEN_VCPU_ID_INVALID;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम xen_hvm_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	अगर (common_cpu_die(cpu) == 0) अणु
		अगर (xen_have_vector_callback) अणु
			xen_smp_पूर्णांकr_मुक्त(cpu);
			xen_uninit_lock_cpu(cpu);
			xen_tearकरोwn_समयr(cpu);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम xen_hvm_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर

व्योम __init xen_hvm_smp_init(व्योम)
अणु
	smp_ops.smp_prepare_boot_cpu = xen_hvm_smp_prepare_boot_cpu;
	smp_ops.smp_prepare_cpus = xen_hvm_smp_prepare_cpus;
	smp_ops.smp_cpus_करोne = xen_smp_cpus_करोne;
	smp_ops.cpu_die = xen_hvm_cpu_die;

	अगर (!xen_have_vector_callback) अणु
#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
		nopvspin = true;
#पूर्ण_अगर
		वापस;
	पूर्ण

	smp_ops.smp_send_reschedule = xen_smp_send_reschedule;
	smp_ops.send_call_func_ipi = xen_smp_send_call_function_ipi;
	smp_ops.send_call_func_single_ipi = xen_smp_send_call_function_single_ipi;
पूर्ण
