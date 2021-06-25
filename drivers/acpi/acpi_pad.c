<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * acpi_pad.c ACPI Processor Aggregator Driver
 *
 * Copyright (c) 2009, Intel Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/cpu.h>
#समावेश <linux/tick.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/mरुको.h>
#समावेश <xen/xen.h>

#घोषणा ACPI_PROCESSOR_AGGREGATOR_CLASS	"acpi_pad"
#घोषणा ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME "Processor Aggregator"
#घोषणा ACPI_PROCESSOR_AGGREGATOR_NOTIFY 0x80
अटल DEFINE_MUTEX(isolated_cpus_lock);
अटल DEFINE_MUTEX(round_robin_lock);

अटल अचिन्हित दीर्घ घातer_saving_mरुको_eax;

अटल अचिन्हित अक्षर tsc_detected_unstable;
अटल अचिन्हित अक्षर tsc_marked_unstable;

अटल व्योम घातer_saving_mरुको_init(व्योम)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	अचिन्हित पूर्णांक highest_cstate = 0;
	अचिन्हित पूर्णांक highest_subcstate = 0;
	पूर्णांक i;

	अगर (!boot_cpu_has(X86_FEATURE_MWAIT))
		वापस;
	अगर (boot_cpu_data.cpuid_level < CPUID_MWAIT_LEAF)
		वापस;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &edx);

	अगर (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK))
		वापस;

	edx >>= MWAIT_SUBSTATE_SIZE;
	क्रम (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) अणु
		अगर (edx & MWAIT_SUBSTATE_MASK) अणु
			highest_cstate = i;
			highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
		पूर्ण
	पूर्ण
	घातer_saving_mरुको_eax = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
		(highest_subcstate - 1);

#अगर defined(CONFIG_X86)
	चयन (boot_cpu_data.x86_venकरोr) अणु
	हाल X86_VENDOR_HYGON:
	हाल X86_VENDOR_AMD:
	हाल X86_VENDOR_INTEL:
	हाल X86_VENDOR_ZHAOXIN:
		/*
		 * AMD Fam10h TSC will tick in all
		 * C/P/S0/S1 states when this bit is set.
		 */
		अगर (!boot_cpu_has(X86_FEATURE_NONSTOP_TSC))
			tsc_detected_unstable = 1;
		अवरोध;
	शेष:
		/* TSC could halt in idle */
		tsc_detected_unstable = 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित दीर्घ cpu_weight[NR_CPUS];
अटल पूर्णांक tsk_in_cpu[NR_CPUS] = अणु[0 ... NR_CPUS-1] = -1पूर्ण;
अटल DECLARE_BITMAP(pad_busy_cpus_bits, NR_CPUS);
अटल व्योम round_robin_cpu(अचिन्हित पूर्णांक tsk_index)
अणु
	काष्ठा cpumask *pad_busy_cpus = to_cpumask(pad_busy_cpus_bits);
	cpumask_var_t पंचांगp;
	पूर्णांक cpu;
	अचिन्हित दीर्घ min_weight = -1;
	अचिन्हित दीर्घ preferred_cpu;

	अगर (!alloc_cpumask_var(&पंचांगp, GFP_KERNEL))
		वापस;

	mutex_lock(&round_robin_lock);
	cpumask_clear(पंचांगp);
	क्रम_each_cpu(cpu, pad_busy_cpus)
		cpumask_or(पंचांगp, पंचांगp, topology_sibling_cpumask(cpu));
	cpumask_andnot(पंचांगp, cpu_online_mask, पंचांगp);
	/* aव्योम HT sibilings अगर possible */
	अगर (cpumask_empty(पंचांगp))
		cpumask_andnot(पंचांगp, cpu_online_mask, pad_busy_cpus);
	अगर (cpumask_empty(पंचांगp)) अणु
		mutex_unlock(&round_robin_lock);
		मुक्त_cpumask_var(पंचांगp);
		वापस;
	पूर्ण
	क्रम_each_cpu(cpu, पंचांगp) अणु
		अगर (cpu_weight[cpu] < min_weight) अणु
			min_weight = cpu_weight[cpu];
			preferred_cpu = cpu;
		पूर्ण
	पूर्ण

	अगर (tsk_in_cpu[tsk_index] != -1)
		cpumask_clear_cpu(tsk_in_cpu[tsk_index], pad_busy_cpus);
	tsk_in_cpu[tsk_index] = preferred_cpu;
	cpumask_set_cpu(preferred_cpu, pad_busy_cpus);
	cpu_weight[preferred_cpu]++;
	mutex_unlock(&round_robin_lock);

	set_cpus_allowed_ptr(current, cpumask_of(preferred_cpu));

	मुक्त_cpumask_var(पंचांगp);
पूर्ण

अटल व्योम निकास_round_robin(अचिन्हित पूर्णांक tsk_index)
अणु
	काष्ठा cpumask *pad_busy_cpus = to_cpumask(pad_busy_cpus_bits);

	cpumask_clear_cpu(tsk_in_cpu[tsk_index], pad_busy_cpus);
	tsk_in_cpu[tsk_index] = -1;
पूर्ण

अटल अचिन्हित पूर्णांक idle_pct = 5; /* percentage */
अटल अचिन्हित पूर्णांक round_robin_समय = 1; /* second */
अटल पूर्णांक घातer_saving_thपढ़ो(व्योम *data)
अणु
	पूर्णांक करो_sleep;
	अचिन्हित पूर्णांक tsk_index = (अचिन्हित दीर्घ)data;
	u64 last_jअगरfies = 0;

	sched_set_fअगरo_low(current);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अचिन्हित दीर्घ expire_समय;

		/* round robin to cpus */
		expire_समय = last_jअगरfies + round_robin_समय * HZ;
		अगर (समय_beक्रमe(expire_समय, jअगरfies)) अणु
			last_jअगरfies = jअगरfies;
			round_robin_cpu(tsk_index);
		पूर्ण

		करो_sleep = 0;

		expire_समय = jअगरfies + HZ * (100 - idle_pct) / 100;

		जबतक (!need_resched()) अणु
			अगर (tsc_detected_unstable && !tsc_marked_unstable) अणु
				/* TSC could halt in idle, so notअगरy users */
				mark_tsc_unstable("TSC halts in idle");
				tsc_marked_unstable = 1;
			पूर्ण
			local_irq_disable();
			tick_broadcast_enable();
			tick_broadcast_enter();
			stop_critical_timings();

			mरुको_idle_with_hपूर्णांकs(घातer_saving_mरुको_eax, 1);

			start_critical_timings();
			tick_broadcast_निकास();
			local_irq_enable();

			अगर (समय_beक्रमe(expire_समय, jअगरfies)) अणु
				करो_sleep = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * current sched_rt has threshold क्रम rt task running समय.
		 * When a rt task uses 95% CPU समय, the rt thपढ़ो will be
		 * scheduled out क्रम 5% CPU समय to not starve other tasks. But
		 * the mechanism only works when all CPUs have RT task running,
		 * as अगर one CPU hasn't RT task, RT task from other CPUs will
		 * borrow CPU समय from this CPU and cause RT task use > 95%
		 * CPU समय. To make 'avoid starvation' work, takes a nap here.
		 */
		अगर (unlikely(करो_sleep))
			schedule_समयout_समाप्तable(HZ * idle_pct / 100);

		/* If an बाह्यal event has set the need_resched flag, then
		 * we need to deal with it, or this loop will जारी to
		 * spin without calling __mरुको().
		 */
		अगर (unlikely(need_resched()))
			schedule();
	पूर्ण

	निकास_round_robin(tsk_index);
	वापस 0;
पूर्ण

अटल काष्ठा task_काष्ठा *ps_tsks[NR_CPUS];
अटल अचिन्हित पूर्णांक ps_tsk_num;
अटल पूर्णांक create_घातer_saving_task(व्योम)
अणु
	पूर्णांक rc;

	ps_tsks[ps_tsk_num] = kthपढ़ो_run(घातer_saving_thपढ़ो,
		(व्योम *)(अचिन्हित दीर्घ)ps_tsk_num,
		"acpi_pad/%d", ps_tsk_num);

	अगर (IS_ERR(ps_tsks[ps_tsk_num])) अणु
		rc = PTR_ERR(ps_tsks[ps_tsk_num]);
		ps_tsks[ps_tsk_num] = शून्य;
	पूर्ण अन्यथा अणु
		rc = 0;
		ps_tsk_num++;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम destroy_घातer_saving_task(व्योम)
अणु
	अगर (ps_tsk_num > 0) अणु
		ps_tsk_num--;
		kthपढ़ो_stop(ps_tsks[ps_tsk_num]);
		ps_tsks[ps_tsk_num] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम set_घातer_saving_task_num(अचिन्हित पूर्णांक num)
अणु
	अगर (num > ps_tsk_num) अणु
		जबतक (ps_tsk_num < num) अणु
			अगर (create_घातer_saving_task())
				वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (num < ps_tsk_num) अणु
		जबतक (ps_tsk_num > num)
			destroy_घातer_saving_task();
	पूर्ण
पूर्ण

अटल व्योम acpi_pad_idle_cpus(अचिन्हित पूर्णांक num_cpus)
अणु
	get_online_cpus();

	num_cpus = min_t(अचिन्हित पूर्णांक, num_cpus, num_online_cpus());
	set_घातer_saving_task_num(num_cpus);

	put_online_cpus();
पूर्ण

अटल uपूर्णांक32_t acpi_pad_idle_cpus_num(व्योम)
अणु
	वापस ps_tsk_num;
पूर्ण

अटल sमाप_प्रकार rrसमय_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ num;

	अगर (kम_से_अदीर्घ(buf, 0, &num))
		वापस -EINVAL;
	अगर (num < 1 || num >= 100)
		वापस -EINVAL;
	mutex_lock(&isolated_cpus_lock);
	round_robin_समय = num;
	mutex_unlock(&isolated_cpus_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rrसमय_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", round_robin_समय);
पूर्ण
अटल DEVICE_ATTR_RW(rrसमय);

अटल sमाप_प्रकार idlepct_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ num;

	अगर (kम_से_अदीर्घ(buf, 0, &num))
		वापस -EINVAL;
	अगर (num < 1 || num >= 100)
		वापस -EINVAL;
	mutex_lock(&isolated_cpus_lock);
	idle_pct = num;
	mutex_unlock(&isolated_cpus_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार idlepct_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", idle_pct);
पूर्ण
अटल DEVICE_ATTR_RW(idlepct);

अटल sमाप_प्रकार idlecpus_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ num;

	अगर (kम_से_अदीर्घ(buf, 0, &num))
		वापस -EINVAL;
	mutex_lock(&isolated_cpus_lock);
	acpi_pad_idle_cpus(num);
	mutex_unlock(&isolated_cpus_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार idlecpus_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(false, buf,
				       to_cpumask(pad_busy_cpus_bits));
पूर्ण

अटल DEVICE_ATTR_RW(idlecpus);

अटल पूर्णांक acpi_pad_add_sysfs(काष्ठा acpi_device *device)
अणु
	पूर्णांक result;

	result = device_create_file(&device->dev, &dev_attr_idlecpus);
	अगर (result)
		वापस -ENODEV;
	result = device_create_file(&device->dev, &dev_attr_idlepct);
	अगर (result) अणु
		device_हटाओ_file(&device->dev, &dev_attr_idlecpus);
		वापस -ENODEV;
	पूर्ण
	result = device_create_file(&device->dev, &dev_attr_rrसमय);
	अगर (result) अणु
		device_हटाओ_file(&device->dev, &dev_attr_idlecpus);
		device_हटाओ_file(&device->dev, &dev_attr_idlepct);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम acpi_pad_हटाओ_sysfs(काष्ठा acpi_device *device)
अणु
	device_हटाओ_file(&device->dev, &dev_attr_idlecpus);
	device_हटाओ_file(&device->dev, &dev_attr_idlepct);
	device_हटाओ_file(&device->dev, &dev_attr_rrसमय);
पूर्ण

/*
 * Query firmware how many CPUs should be idle
 * वापस -1 on failure
 */
अटल पूर्णांक acpi_pad_pur(acpi_handle handle)
अणु
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *package;
	पूर्णांक num = -1;

	अगर (ACPI_FAILURE(acpi_evaluate_object(handle, "_PUR", शून्य, &buffer)))
		वापस num;

	अगर (!buffer.length || !buffer.poपूर्णांकer)
		वापस num;

	package = buffer.poपूर्णांकer;

	अगर (package->type == ACPI_TYPE_PACKAGE &&
		package->package.count == 2 &&
		package->package.elements[0].पूर्णांकeger.value == 1) /* rev 1 */

		num = package->package.elements[1].पूर्णांकeger.value;

	kमुक्त(buffer.poपूर्णांकer);
	वापस num;
पूर्ण

अटल व्योम acpi_pad_handle_notअगरy(acpi_handle handle)
अणु
	पूर्णांक num_cpus;
	uपूर्णांक32_t idle_cpus;
	काष्ठा acpi_buffer param = अणु
		.length = 4,
		.poपूर्णांकer = (व्योम *)&idle_cpus,
	पूर्ण;

	mutex_lock(&isolated_cpus_lock);
	num_cpus = acpi_pad_pur(handle);
	अगर (num_cpus < 0) अणु
		mutex_unlock(&isolated_cpus_lock);
		वापस;
	पूर्ण
	acpi_pad_idle_cpus(num_cpus);
	idle_cpus = acpi_pad_idle_cpus_num();
	acpi_evaluate_ost(handle, ACPI_PROCESSOR_AGGREGATOR_NOTIFY, 0, &param);
	mutex_unlock(&isolated_cpus_lock);
पूर्ण

अटल व्योम acpi_pad_notअगरy(acpi_handle handle, u32 event,
	व्योम *data)
अणु
	काष्ठा acpi_device *device = data;

	चयन (event) अणु
	हाल ACPI_PROCESSOR_AGGREGATOR_NOTIFY:
		acpi_pad_handle_notअगरy(handle);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
			dev_name(&device->dev), event, 0);
		अवरोध;
	शेष:
		pr_warn("Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_pad_add(काष्ठा acpi_device *device)
अणु
	acpi_status status;

	म_नकल(acpi_device_name(device), ACPI_PROCESSOR_AGGREGATOR_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_PROCESSOR_AGGREGATOR_CLASS);

	अगर (acpi_pad_add_sysfs(device))
		वापस -ENODEV;

	status = acpi_install_notअगरy_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notअगरy, device);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pad_हटाओ_sysfs(device);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_pad_हटाओ(काष्ठा acpi_device *device)
अणु
	mutex_lock(&isolated_cpus_lock);
	acpi_pad_idle_cpus(0);
	mutex_unlock(&isolated_cpus_lock);

	acpi_हटाओ_notअगरy_handler(device->handle,
		ACPI_DEVICE_NOTIFY, acpi_pad_notअगरy);
	acpi_pad_हटाओ_sysfs(device);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id pad_device_ids[] = अणु
	अणु"ACPI000C", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, pad_device_ids);

अटल काष्ठा acpi_driver acpi_pad_driver = अणु
	.name = "processor_aggregator",
	.class = ACPI_PROCESSOR_AGGREGATOR_CLASS,
	.ids = pad_device_ids,
	.ops = अणु
		.add = acpi_pad_add,
		.हटाओ = acpi_pad_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init acpi_pad_init(व्योम)
अणु
	/* Xen ACPI PAD is used when running as Xen Dom0. */
	अगर (xen_initial_करोमुख्य())
		वापस -ENODEV;

	घातer_saving_mरुको_init();
	अगर (घातer_saving_mरुको_eax == 0)
		वापस -EINVAL;

	वापस acpi_bus_रेजिस्टर_driver(&acpi_pad_driver);
पूर्ण

अटल व्योम __निकास acpi_pad_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_pad_driver);
पूर्ण

module_init(acpi_pad_init);
module_निकास(acpi_pad_निकास);
MODULE_AUTHOR("Shaohua Li<shaohua.li@intel.com>");
MODULE_DESCRIPTION("ACPI Processor Aggregator Driver");
MODULE_LICENSE("GPL");
