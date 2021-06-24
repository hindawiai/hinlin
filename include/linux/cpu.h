<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/cpu.h - generic cpu definition
 *
 * This is मुख्यly क्रम topological representation. We define the 
 * basic 'struct cpu' here, which can be embedded in per-arch 
 * definitions of processors.
 *
 * Basic handling of the devices is करोne in drivers/base/cpu.c
 *
 * CPUs are exported via sysfs in the devices/प्रणाली/cpu
 * directory. 
 */
#अगर_अघोषित _LINUX_CPU_H_
#घोषणा _LINUX_CPU_H_

#समावेश <linux/node.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpuhotplug.h>

काष्ठा device;
काष्ठा device_node;
काष्ठा attribute_group;

काष्ठा cpu अणु
	पूर्णांक node_id;		/* The node which contains the CPU */
	पूर्णांक hotpluggable;	/* creates sysfs control file अगर hotpluggable */
	काष्ठा device dev;
पूर्ण;

बाह्य व्योम boot_cpu_init(व्योम);
बाह्य व्योम boot_cpu_hotplug_init(व्योम);
बाह्य व्योम cpu_init(व्योम);
बाह्य व्योम trap_init(व्योम);

बाह्य पूर्णांक रेजिस्टर_cpu(काष्ठा cpu *cpu, पूर्णांक num);
बाह्य काष्ठा device *get_cpu_device(अचिन्हित cpu);
बाह्य bool cpu_is_hotpluggable(अचिन्हित cpu);
बाह्य bool arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id);
बाह्य bool arch_find_n_match_cpu_physical_id(काष्ठा device_node *cpun,
					      पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो);

बाह्य पूर्णांक cpu_add_dev_attr(काष्ठा device_attribute *attr);
बाह्य व्योम cpu_हटाओ_dev_attr(काष्ठा device_attribute *attr);

बाह्य पूर्णांक cpu_add_dev_attr_group(काष्ठा attribute_group *attrs);
बाह्य व्योम cpu_हटाओ_dev_attr_group(काष्ठा attribute_group *attrs);

बाह्य sमाप_प्रकार cpu_show_meltकरोwn(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_spec_store_bypass(काष्ठा device *dev,
					  काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_l1tf(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_mds(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_tsx_async_पात(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_itlb_multihit(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf);
बाह्य sमाप_प्रकार cpu_show_srbds(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf);

बाह्य __म_लिखो(4, 5)
काष्ठा device *cpu_device_create(काष्ठा device *parent, व्योम *drvdata,
				 स्थिर काष्ठा attribute_group **groups,
				 स्थिर अक्षर *fmt, ...);
#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य व्योम unरेजिस्टर_cpu(काष्ठा cpu *cpu);
बाह्य sमाप_प्रकार arch_cpu_probe(स्थिर अक्षर *, माप_प्रकार);
बाह्य sमाप_प्रकार arch_cpu_release(स्थिर अक्षर *, माप_प्रकार);
#पूर्ण_अगर

/*
 * These states are not related to the core CPU hotplug mechanism. They are
 * used by various (sub)architectures to track पूर्णांकernal state
 */
#घोषणा CPU_ONLINE		0x0002 /* CPU is up */
#घोषणा CPU_UP_PREPARE		0x0003 /* CPU coming up */
#घोषणा CPU_DEAD		0x0007 /* CPU dead */
#घोषणा CPU_DEAD_FROZEN		0x0008 /* CPU समयd out on unplug */
#घोषणा CPU_POST_DEAD		0x0009 /* CPU successfully unplugged */
#घोषणा CPU_BROKEN		0x000B /* CPU did not die properly */

#अगर_घोषित CONFIG_SMP
बाह्य bool cpuhp_tasks_frozen;
पूर्णांक add_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक cpu_device_up(काष्ठा device *dev);
व्योम notअगरy_cpu_starting(अचिन्हित पूर्णांक cpu);
बाह्य व्योम cpu_maps_update_begin(व्योम);
बाह्य व्योम cpu_maps_update_करोne(व्योम);
पूर्णांक bringup_hibernate_cpu(अचिन्हित पूर्णांक sleep_cpu);
व्योम bringup_nonboot_cpus(अचिन्हित पूर्णांक setup_max_cpus);

#अन्यथा	/* CONFIG_SMP */
#घोषणा cpuhp_tasks_frozen	0

अटल अंतरभूत व्योम cpu_maps_update_begin(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम cpu_maps_update_करोne(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक add_cpu(अचिन्हित पूर्णांक cpu) अणु वापस 0;पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */
बाह्य काष्ठा bus_type cpu_subsys;

बाह्य पूर्णांक lockdep_is_cpus_held(व्योम);

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य व्योम cpus_ग_लिखो_lock(व्योम);
बाह्य व्योम cpus_ग_लिखो_unlock(व्योम);
बाह्य व्योम cpus_पढ़ो_lock(व्योम);
बाह्य व्योम cpus_पढ़ो_unlock(व्योम);
बाह्य पूर्णांक  cpus_पढ़ो_trylock(व्योम);
बाह्य व्योम lockdep_निश्चित_cpus_held(व्योम);
बाह्य व्योम cpu_hotplug_disable(व्योम);
बाह्य व्योम cpu_hotplug_enable(व्योम);
व्योम clear_tasks_mm_cpumask(पूर्णांक cpu);
पूर्णांक हटाओ_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक cpu_device_करोwn(काष्ठा device *dev);
बाह्य व्योम smp_shutकरोwn_nonboot_cpus(अचिन्हित पूर्णांक primary_cpu);

#अन्यथा /* CONFIG_HOTPLUG_CPU */

अटल अंतरभूत व्योम cpus_ग_लिखो_lock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpus_ग_लिखो_unlock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpus_पढ़ो_lock(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpus_पढ़ो_unlock(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक  cpus_पढ़ो_trylock(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम lockdep_निश्चित_cpus_held(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpu_hotplug_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम cpu_hotplug_enable(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक हटाओ_cpu(अचिन्हित पूर्णांक cpu) अणु वापस -EPERM; पूर्ण
अटल अंतरभूत व्योम smp_shutकरोwn_nonboot_cpus(अचिन्हित पूर्णांक primary_cpu) अणु पूर्ण
#पूर्ण_अगर	/* !CONFIG_HOTPLUG_CPU */

/* Wrappers which go away once all code is converted */
अटल अंतरभूत व्योम cpu_hotplug_begin(व्योम) अणु cpus_ग_लिखो_lock(); पूर्ण
अटल अंतरभूत व्योम cpu_hotplug_करोne(व्योम) अणु cpus_ग_लिखो_unlock(); पूर्ण
अटल अंतरभूत व्योम get_online_cpus(व्योम) अणु cpus_पढ़ो_lock(); पूर्ण
अटल अंतरभूत व्योम put_online_cpus(व्योम) अणु cpus_पढ़ो_unlock(); पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP_SMP
बाह्य पूर्णांक मुक्तze_secondary_cpus(पूर्णांक primary);
बाह्य व्योम thaw_secondary_cpus(व्योम);

अटल अंतरभूत पूर्णांक suspend_disable_secondary_cpus(व्योम)
अणु
	पूर्णांक cpu = 0;

	अगर (IS_ENABLED(CONFIG_PM_SLEEP_SMP_NONZERO_CPU))
		cpu = -1;

	वापस मुक्तze_secondary_cpus(cpu);
पूर्ण
अटल अंतरभूत व्योम suspend_enable_secondary_cpus(व्योम)
अणु
	वापस thaw_secondary_cpus();
पूर्ण

#अन्यथा /* !CONFIG_PM_SLEEP_SMP */
अटल अंतरभूत व्योम thaw_secondary_cpus(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक suspend_disable_secondary_cpus(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम suspend_enable_secondary_cpus(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_PM_SLEEP_SMP */

व्योम cpu_startup_entry(क्रमागत cpuhp_state state);

व्योम cpu_idle_poll_ctrl(bool enable);

/* Attach to any functions which should be considered cpuidle. */
#घोषणा __cpuidle	__section(".cpuidle.text")

bool cpu_in_idle(अचिन्हित दीर्घ pc);

व्योम arch_cpu_idle(व्योम);
व्योम arch_cpu_idle_prepare(व्योम);
व्योम arch_cpu_idle_enter(व्योम);
व्योम arch_cpu_idle_निकास(व्योम);
व्योम arch_cpu_idle_dead(व्योम);

पूर्णांक cpu_report_state(पूर्णांक cpu);
पूर्णांक cpu_check_up_prepare(पूर्णांक cpu);
व्योम cpu_set_state_online(पूर्णांक cpu);
व्योम play_idle_precise(u64 duration_ns, u64 latency_ns);

अटल अंतरभूत व्योम play_idle(अचिन्हित दीर्घ duration_us)
अणु
	play_idle_precise(duration_us * NSEC_PER_USEC, U64_MAX);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
bool cpu_रुको_death(अचिन्हित पूर्णांक cpu, पूर्णांक seconds);
bool cpu_report_death(व्योम);
व्योम cpuhp_report_idle_dead(व्योम);
#अन्यथा
अटल अंतरभूत व्योम cpuhp_report_idle_dead(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */

क्रमागत cpuhp_smt_control अणु
	CPU_SMT_ENABLED,
	CPU_SMT_DISABLED,
	CPU_SMT_FORCE_DISABLED,
	CPU_SMT_NOT_SUPPORTED,
	CPU_SMT_NOT_IMPLEMENTED,
पूर्ण;

#अगर defined(CONFIG_SMP) && defined(CONFIG_HOTPLUG_SMT)
बाह्य क्रमागत cpuhp_smt_control cpu_smt_control;
बाह्य व्योम cpu_smt_disable(bool क्रमce);
बाह्य व्योम cpu_smt_check_topology(व्योम);
बाह्य bool cpu_smt_possible(व्योम);
बाह्य पूर्णांक cpuhp_smt_enable(व्योम);
बाह्य पूर्णांक cpuhp_smt_disable(क्रमागत cpuhp_smt_control ctrlval);
#अन्यथा
# define cpu_smt_control		(CPU_SMT_NOT_IMPLEMENTED)
अटल अंतरभूत व्योम cpu_smt_disable(bool क्रमce) अणु पूर्ण
अटल अंतरभूत व्योम cpu_smt_check_topology(व्योम) अणु पूर्ण
अटल अंतरभूत bool cpu_smt_possible(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक cpuhp_smt_enable(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक cpuhp_smt_disable(क्रमागत cpuhp_smt_control ctrlval) अणु वापस 0; पूर्ण
#पूर्ण_अगर

बाह्य bool cpu_mitigations_off(व्योम);
बाह्य bool cpu_mitigations_स्वतः_nosmt(व्योम);

#पूर्ण_अगर /* _LINUX_CPU_H_ */
