<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file provides the ACPI based P-state support. This
 * module works with generic cpufreq infraकाष्ठाure. Most of
 * the code is based on i386 version
 * (arch/i386/kernel/cpu/cpufreq/acpi-cpufreq.c)
 *
 * Copyright (C) 2005 Intel Corp
 *      Venkatesh Pallipadi <venkatesh.pallipadi@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/proc_fs.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pal.h>

#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>

MODULE_AUTHOR("Venkatesh Pallipadi");
MODULE_DESCRIPTION("ACPI Processor P-States Driver");
MODULE_LICENSE("GPL");

काष्ठा cpufreq_acpi_io अणु
	काष्ठा acpi_processor_perक्रमmance	acpi_data;
	अचिन्हित पूर्णांक				resume;
पूर्ण;

काष्ठा cpufreq_acpi_req अणु
	अचिन्हित पूर्णांक		cpu;
	अचिन्हित पूर्णांक		state;
पूर्ण;

अटल काष्ठा cpufreq_acpi_io	*acpi_io_data[NR_CPUS];

अटल काष्ठा cpufreq_driver acpi_cpufreq_driver;


अटल पूर्णांक
processor_set_pstate (
	u32	value)
अणु
	s64 retval;

	pr_debug("processor_set_pstate\n");

	retval = ia64_pal_set_pstate((u64)value);

	अगर (retval) अणु
		pr_debug("Failed to set freq to 0x%x, with error 0x%llx\n",
		        value, retval);
		वापस -ENODEV;
	पूर्ण
	वापस (पूर्णांक)retval;
पूर्ण


अटल पूर्णांक
processor_get_pstate (
	u32	*value)
अणु
	u64	pstate_index = 0;
	s64 	retval;

	pr_debug("processor_get_pstate\n");

	retval = ia64_pal_get_pstate(&pstate_index,
	                             PAL_GET_PSTATE_TYPE_INSTANT);
	*value = (u32) pstate_index;

	अगर (retval)
		pr_debug("Failed to get current freq with "
			"error 0x%llx, idx 0x%x\n", retval, *value);

	वापस (पूर्णांक)retval;
पूर्ण


/* To be used only after data->acpi_data is initialized */
अटल अचिन्हित
extract_घड़ी (
	काष्ठा cpufreq_acpi_io *data,
	अचिन्हित value)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("extract_clock\n");

	क्रम (i = 0; i < data->acpi_data.state_count; i++) अणु
		अगर (value == data->acpi_data.states[i].status)
			वापस data->acpi_data.states[i].core_frequency;
	पूर्ण
	वापस data->acpi_data.states[i-1].core_frequency;
पूर्ण


अटल दीर्घ
processor_get_freq (
	व्योम *arg)
अणु
	काष्ठा cpufreq_acpi_req *req = arg;
	अचिन्हित पूर्णांक		cpu = req->cpu;
	काष्ठा cpufreq_acpi_io	*data = acpi_io_data[cpu];
	u32			value;
	पूर्णांक			ret;

	pr_debug("processor_get_freq\n");
	अगर (smp_processor_id() != cpu)
		वापस -EAGAIN;

	/* processor_get_pstate माला_लो the instantaneous frequency */
	ret = processor_get_pstate(&value);
	अगर (ret) अणु
		pr_warn("get performance failed with error %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 1000 * extract_घड़ी(data, value);
पूर्ण


अटल दीर्घ
processor_set_freq (
	व्योम *arg)
अणु
	काष्ठा cpufreq_acpi_req *req = arg;
	अचिन्हित पूर्णांक		cpu = req->cpu;
	काष्ठा cpufreq_acpi_io	*data = acpi_io_data[cpu];
	पूर्णांक			ret, state = req->state;
	u32			value;

	pr_debug("processor_set_freq\n");
	अगर (smp_processor_id() != cpu)
		वापस -EAGAIN;

	अगर (state == data->acpi_data.state) अणु
		अगर (unlikely(data->resume)) अणु
			pr_debug("Called after resume, resetting to P%d\n", state);
			data->resume = 0;
		पूर्ण अन्यथा अणु
			pr_debug("Already at target state (P%d)\n", state);
			वापस 0;
		पूर्ण
	पूर्ण

	pr_debug("Transitioning from P%d to P%d\n",
		data->acpi_data.state, state);

	/*
	 * First we ग_लिखो the target state's 'control' value to the
	 * control_रेजिस्टर.
	 */
	value = (u32) data->acpi_data.states[state].control;

	pr_debug("Transitioning to state: 0x%08x\n", value);

	ret = processor_set_pstate(value);
	अगर (ret) अणु
		pr_warn("Transition failed with error %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	data->acpi_data.state = state;
	वापस 0;
पूर्ण


अटल अचिन्हित पूर्णांक
acpi_cpufreq_get (
	अचिन्हित पूर्णांक		cpu)
अणु
	काष्ठा cpufreq_acpi_req req;
	दीर्घ ret;

	req.cpu = cpu;
	ret = work_on_cpu(cpu, processor_get_freq, &req);

	वापस ret > 0 ? (अचिन्हित पूर्णांक) ret : 0;
पूर्ण


अटल पूर्णांक
acpi_cpufreq_target (
	काष्ठा cpufreq_policy   *policy,
	अचिन्हित पूर्णांक index)
अणु
	काष्ठा cpufreq_acpi_req req;

	req.cpu = policy->cpu;
	req.state = index;

	वापस work_on_cpu(req.cpu, processor_set_freq, &req);
पूर्ण

अटल पूर्णांक
acpi_cpufreq_cpu_init (
	काष्ठा cpufreq_policy   *policy)
अणु
	अचिन्हित पूर्णांक		i;
	अचिन्हित पूर्णांक		cpu = policy->cpu;
	काष्ठा cpufreq_acpi_io	*data;
	अचिन्हित पूर्णांक		result = 0;
	काष्ठा cpufreq_frequency_table *freq_table;

	pr_debug("acpi_cpufreq_cpu_init\n");

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस (-ENOMEM);

	acpi_io_data[cpu] = data;

	result = acpi_processor_रेजिस्टर_perक्रमmance(&data->acpi_data, cpu);

	अगर (result)
		जाओ err_मुक्त;

	/* capability check */
	अगर (data->acpi_data.state_count <= 1) अणु
		pr_debug("No P-States\n");
		result = -ENODEV;
		जाओ err_unreg;
	पूर्ण

	अगर ((data->acpi_data.control_रेजिस्टर.space_id !=
					ACPI_ADR_SPACE_FIXED_HARDWARE) ||
	    (data->acpi_data.status_रेजिस्टर.space_id !=
					ACPI_ADR_SPACE_FIXED_HARDWARE)) अणु
		pr_debug("Unsupported address space [%d, %d]\n",
			(u32) (data->acpi_data.control_रेजिस्टर.space_id),
			(u32) (data->acpi_data.status_रेजिस्टर.space_id));
		result = -ENODEV;
		जाओ err_unreg;
	पूर्ण

	/* alloc freq_table */
	freq_table = kसुस्मृति(data->acpi_data.state_count + 1,
	                           माप(*freq_table),
	                           GFP_KERNEL);
	अगर (!freq_table) अणु
		result = -ENOMEM;
		जाओ err_unreg;
	पूर्ण

	/* detect transition latency */
	policy->cpuinfo.transition_latency = 0;
	क्रम (i=0; i<data->acpi_data.state_count; i++) अणु
		अगर ((data->acpi_data.states[i].transition_latency * 1000) >
		    policy->cpuinfo.transition_latency) अणु
			policy->cpuinfo.transition_latency =
			    data->acpi_data.states[i].transition_latency * 1000;
		पूर्ण
	पूर्ण

	/* table init */
	क्रम (i = 0; i <= data->acpi_data.state_count; i++)
	अणु
		अगर (i < data->acpi_data.state_count) अणु
			freq_table[i].frequency =
			      data->acpi_data.states[i].core_frequency * 1000;
		पूर्ण अन्यथा अणु
			freq_table[i].frequency = CPUFREQ_TABLE_END;
		पूर्ण
	पूर्ण

	policy->freq_table = freq_table;

	/* notअगरy BIOS that we exist */
	acpi_processor_notअगरy_smm(THIS_MODULE);

	pr_info("CPU%u - ACPI performance management activated\n", cpu);

	क्रम (i = 0; i < data->acpi_data.state_count; i++)
		pr_debug("     %cP%d: %d MHz, %d mW, %d uS, %d uS, 0x%x 0x%x\n",
			(i == data->acpi_data.state?'*':' '), i,
			(u32) data->acpi_data.states[i].core_frequency,
			(u32) data->acpi_data.states[i].घातer,
			(u32) data->acpi_data.states[i].transition_latency,
			(u32) data->acpi_data.states[i].bus_master_latency,
			(u32) data->acpi_data.states[i].status,
			(u32) data->acpi_data.states[i].control);

	/* the first call to ->target() should result in us actually
	 * writing something to the appropriate रेजिस्टरs. */
	data->resume = 1;

	वापस (result);

 err_unreg:
	acpi_processor_unरेजिस्टर_perक्रमmance(cpu);
 err_मुक्त:
	kमुक्त(data);
	acpi_io_data[cpu] = शून्य;

	वापस (result);
पूर्ण


अटल पूर्णांक
acpi_cpufreq_cpu_निकास (
	काष्ठा cpufreq_policy   *policy)
अणु
	काष्ठा cpufreq_acpi_io *data = acpi_io_data[policy->cpu];

	pr_debug("acpi_cpufreq_cpu_exit\n");

	अगर (data) अणु
		acpi_io_data[policy->cpu] = शून्य;
		acpi_processor_unरेजिस्टर_perक्रमmance(policy->cpu);
		kमुक्त(policy->freq_table);
		kमुक्त(data);
	पूर्ण

	वापस (0);
पूर्ण


अटल काष्ठा cpufreq_driver acpi_cpufreq_driver = अणु
	.verअगरy 	= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= acpi_cpufreq_target,
	.get 		= acpi_cpufreq_get,
	.init		= acpi_cpufreq_cpu_init,
	.निकास		= acpi_cpufreq_cpu_निकास,
	.name		= "acpi-cpufreq",
	.attr		= cpufreq_generic_attr,
पूर्ण;


अटल पूर्णांक __init
acpi_cpufreq_init (व्योम)
अणु
	pr_debug("acpi_cpufreq_init\n");

 	वापस cpufreq_रेजिस्टर_driver(&acpi_cpufreq_driver);
पूर्ण


अटल व्योम __निकास
acpi_cpufreq_निकास (व्योम)
अणु
	pr_debug("acpi_cpufreq_exit\n");

	cpufreq_unरेजिस्टर_driver(&acpi_cpufreq_driver);
पूर्ण

late_initcall(acpi_cpufreq_init);
module_निकास(acpi_cpufreq_निकास);
