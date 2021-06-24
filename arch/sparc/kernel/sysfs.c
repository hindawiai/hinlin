<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* sysfs.c: Topology sysfs support code क्रम sparc64.
 *
 * Copyright (C) 2007 David S. Miller <davem@davemloft.net>
 */
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/spitfire.h>

अटल DEFINE_PER_CPU(काष्ठा hv_mmu_statistics, mmu_stats) __attribute__((aligned(64)));

#घोषणा SHOW_MMUSTAT_ULONG(NAME) \
अटल sमाप_प्रकार show_##NAME(काष्ठा device *dev, \
			काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा hv_mmu_statistics *p = &per_cpu(mmu_stats, dev->id); \
	वापस प्र_लिखो(buf, "%lu\n", p->NAME); \
पूर्ण \
अटल DEVICE_ATTR(NAME, 0444, show_##NAME, शून्य)

SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(immu_tsb_ticks_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctx0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_8k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_64k_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_4mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_hits_ctxnon0_256mb_tte);
SHOW_MMUSTAT_ULONG(dmmu_tsb_ticks_ctxnon0_256mb_tte);

अटल काष्ठा attribute *mmu_stat_attrs[] = अणु
	&dev_attr_immu_tsb_hits_ctx0_8k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_8k_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_64k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_64k_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_4mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_4mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctx0_256mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctx0_256mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_8k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_8k_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_64k_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_64k_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_4mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&dev_attr_immu_tsb_hits_ctxnon0_256mb_tte.attr,
	&dev_attr_immu_tsb_ticks_ctxnon0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_8k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_8k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_64k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_64k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctx0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctx0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_8k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_8k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_64k_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_64k_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_4mb_tte.attr,
	&dev_attr_dmmu_tsb_hits_ctxnon0_256mb_tte.attr,
	&dev_attr_dmmu_tsb_ticks_ctxnon0_256mb_tte.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mmu_stat_group = अणु
	.attrs = mmu_stat_attrs,
	.name = "mmu_stats",
पूर्ण;

अटल दीर्घ पढ़ो_mmustat_enable(व्योम *data __maybe_unused)
अणु
	अचिन्हित दीर्घ ra = 0;

	sun4v_mmustat_info(&ra);

	वापस ra != 0;
पूर्ण

अटल दीर्घ ग_लिखो_mmustat_enable(व्योम *data)
अणु
	अचिन्हित दीर्घ ra, orig_ra, *val = data;

	अगर (*val)
		ra = __pa(&per_cpu(mmu_stats, smp_processor_id()));
	अन्यथा
		ra = 0UL;

	वापस sun4v_mmustat_conf(ra, &orig_ra);
पूर्ण

अटल sमाप_प्रकार show_mmustat_enable(काष्ठा device *s,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	दीर्घ val = work_on_cpu(s->id, पढ़ो_mmustat_enable, शून्य);

	वापस प्र_लिखो(buf, "%lx\n", val);
पूर्ण

अटल sमाप_प्रकार store_mmustat_enable(काष्ठा device *s,
			काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	दीर्घ err;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%lu", &val);
	अगर (ret != 1)
		वापस -EINVAL;

	err = work_on_cpu(s->id, ग_लिखो_mmustat_enable, &val);
	अगर (err)
		वापस -EIO;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(mmustat_enable, 0644, show_mmustat_enable, store_mmustat_enable);

अटल पूर्णांक mmu_stats_supported;

अटल पूर्णांक रेजिस्टर_mmu_stats(काष्ठा device *s)
अणु
	अगर (!mmu_stats_supported)
		वापस 0;
	device_create_file(s, &dev_attr_mmustat_enable);
	वापस sysfs_create_group(&s->kobj, &mmu_stat_group);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम unरेजिस्टर_mmu_stats(काष्ठा device *s)
अणु
	अगर (!mmu_stats_supported)
		वापस;
	sysfs_हटाओ_group(&s->kobj, &mmu_stat_group);
	device_हटाओ_file(s, &dev_attr_mmustat_enable);
पूर्ण
#पूर्ण_अगर

#घोषणा SHOW_CPUDATA_ULONG_NAME(NAME, MEMBER) \
अटल sमाप_प्रकार show_##NAME(काष्ठा device *dev, \
		काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	cpuinfo_sparc *c = &cpu_data(dev->id); \
	वापस प्र_लिखो(buf, "%lu\n", c->MEMBER); \
पूर्ण

#घोषणा SHOW_CPUDATA_UINT_NAME(NAME, MEMBER) \
अटल sमाप_प्रकार show_##NAME(काष्ठा device *dev, \
		काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	cpuinfo_sparc *c = &cpu_data(dev->id); \
	वापस प्र_लिखो(buf, "%u\n", c->MEMBER); \
पूर्ण

SHOW_CPUDATA_ULONG_NAME(घड़ी_प्रकारick, घड़ी_प्रकारick);
SHOW_CPUDATA_UINT_NAME(l1_dcache_size, dcache_size);
SHOW_CPUDATA_UINT_NAME(l1_dcache_line_size, dcache_line_size);
SHOW_CPUDATA_UINT_NAME(l1_icache_size, icache_size);
SHOW_CPUDATA_UINT_NAME(l1_icache_line_size, icache_line_size);
SHOW_CPUDATA_UINT_NAME(l2_cache_size, ecache_size);
SHOW_CPUDATA_UINT_NAME(l2_cache_line_size, ecache_line_size);

अटल काष्ठा device_attribute cpu_core_attrs[] = अणु
	__ATTR(घड़ी_प्रकारick,          0444, show_घड़ी_प्रकारick, शून्य),
	__ATTR(l1_dcache_size,      0444, show_l1_dcache_size, शून्य),
	__ATTR(l1_dcache_line_size, 0444, show_l1_dcache_line_size, शून्य),
	__ATTR(l1_icache_size,      0444, show_l1_icache_size, शून्य),
	__ATTR(l1_icache_line_size, 0444, show_l1_icache_line_size, शून्य),
	__ATTR(l2_cache_size,       0444, show_l2_cache_size, शून्य),
	__ATTR(l2_cache_line_size,  0444, show_l2_cache_line_size, शून्य),
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);

अटल पूर्णांक रेजिस्टर_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);
	काष्ठा device *s = &c->dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
		device_create_file(s, &cpu_core_attrs[i]);

	रेजिस्टर_mmu_stats(s);
	वापस 0;
पूर्ण

अटल पूर्णांक unरेजिस्टर_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);
	काष्ठा device *s = &c->dev;
	पूर्णांक i;

	unरेजिस्टर_mmu_stats(s);
	क्रम (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
		device_हटाओ_file(s, &cpu_core_attrs[i]);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __init check_mmu_stats(व्योम)
अणु
	अचिन्हित दीर्घ dummy1, err;

	अगर (tlb_type != hypervisor)
		वापस;

	err = sun4v_mmustat_info(&dummy1);
	अगर (!err)
		mmu_stats_supported = 1;
पूर्ण

अटल व्योम रेजिस्टर_nodes(व्योम)
अणु
#अगर_घोषित CONFIG_NUMA
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NUMNODES; i++)
		रेजिस्टर_one_node(i);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक cpu, ret;

	रेजिस्टर_nodes();

	check_mmu_stats();

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpu *c = &per_cpu(cpu_devices, cpu);

		रेजिस्टर_cpu(c, cpu);
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "sparc/topology:online",
				रेजिस्टर_cpu_online, unरेजिस्टर_cpu_online);
	WARN_ON(ret < 0);
	वापस 0;
पूर्ण

subsys_initcall(topology_init);
