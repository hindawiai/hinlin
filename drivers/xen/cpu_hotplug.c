<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/notअगरier.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/cpu.h>

अटल व्योम enable_hotplug_cpu(पूर्णांक cpu)
अणु
	अगर (!cpu_present(cpu))
		xen_arch_रेजिस्टर_cpu(cpu);

	set_cpu_present(cpu, true);
पूर्ण

अटल व्योम disable_hotplug_cpu(पूर्णांक cpu)
अणु
	अगर (!cpu_is_hotpluggable(cpu))
		वापस;
	lock_device_hotplug();
	अगर (cpu_online(cpu))
		device_offline(get_cpu_device(cpu));
	अगर (!cpu_online(cpu) && cpu_present(cpu)) अणु
		xen_arch_unरेजिस्टर_cpu(cpu);
		set_cpu_present(cpu, false);
	पूर्ण
	unlock_device_hotplug();
पूर्ण

अटल पूर्णांक vcpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक err;
	अक्षर dir[16], state[16];

	प्र_लिखो(dir, "cpu/%u", cpu);
	err = xenbus_म_पूछो(XBT_NIL, dir, "availability", "%15s", state);
	अगर (err != 1) अणु
		अगर (!xen_initial_करोमुख्य())
			pr_err("Unable to read cpu state\n");
		वापस err;
	पूर्ण

	अगर (म_भेद(state, "online") == 0)
		वापस 1;
	अन्यथा अगर (म_भेद(state, "offline") == 0)
		वापस 0;

	pr_err("unknown state(%s) on CPU%d\n", state, cpu);
	वापस -EINVAL;
पूर्ण
अटल व्योम vcpu_hotplug(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu >= nr_cpu_ids || !cpu_possible(cpu))
		वापस;

	चयन (vcpu_online(cpu)) अणु
	हाल 1:
		enable_hotplug_cpu(cpu);
		अवरोध;
	हाल 0:
		disable_hotplug_cpu(cpu);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम handle_vcpu_hotplug_event(काष्ठा xenbus_watch *watch,
				      स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	अचिन्हित पूर्णांक cpu;
	अक्षर *cpustr;

	cpustr = म_माला(path, "cpu/");
	अगर (cpustr != शून्य) अणु
		माला_पूछो(cpustr, "cpu/%u", &cpu);
		vcpu_hotplug(cpu);
	पूर्ण
पूर्ण

अटल पूर्णांक setup_cpu_watcher(काष्ठा notअगरier_block *notअगरier,
			      अचिन्हित दीर्घ event, व्योम *data)
अणु
	पूर्णांक cpu;
	अटल काष्ठा xenbus_watch cpu_watch = अणु
		.node = "cpu",
		.callback = handle_vcpu_hotplug_eventपूर्ण;

	(व्योम)रेजिस्टर_xenbus_watch(&cpu_watch);

	क्रम_each_possible_cpu(cpu) अणु
		अगर (vcpu_online(cpu) == 0)
			disable_hotplug_cpu(cpu);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init setup_vcpu_hotplug_event(व्योम)
अणु
	अटल काष्ठा notअगरier_block xsn_cpu = अणु
		.notअगरier_call = setup_cpu_watcher पूर्ण;

#अगर_घोषित CONFIG_X86
	अगर (!xen_pv_करोमुख्य() && !xen_pvh_करोमुख्य())
#अन्यथा
	अगर (!xen_करोमुख्य())
#पूर्ण_अगर
		वापस -ENODEV;

	रेजिस्टर_xenstore_notअगरier(&xsn_cpu);

	वापस 0;
पूर्ण

late_initcall(setup_vcpu_hotplug_event);

