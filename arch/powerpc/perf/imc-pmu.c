<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * In-Memory Collection (IMC) Perक्रमmance Monitor counter support.
 *
 * Copyright (C) 2017 Madhavan Srinivasan, IBM Corporation.
 *           (C) 2017 Anju T Sudhakar, IBM Corporation.
 *           (C) 2017 Hemant K Shaw, IBM Corporation.
 */
#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/imc-pmu.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/माला.स>

/* Nest IMC data काष्ठाures and variables */

/*
 * Used to aव्योम races in counting the nest-pmu units during hotplug
 * रेजिस्टर and unरेजिस्टर
 */
अटल DEFINE_MUTEX(nest_init_lock);
अटल DEFINE_PER_CPU(काष्ठा imc_pmu_ref *, local_nest_imc_refc);
अटल काष्ठा imc_pmu **per_nest_pmu_arr;
अटल cpumask_t nest_imc_cpumask;
अटल काष्ठा imc_pmu_ref *nest_imc_refc;
अटल पूर्णांक nest_pmus;

/* Core IMC data काष्ठाures and variables */

अटल cpumask_t core_imc_cpumask;
अटल काष्ठा imc_pmu_ref *core_imc_refc;
अटल काष्ठा imc_pmu *core_imc_pmu;

/* Thपढ़ो IMC data काष्ठाures and variables */

अटल DEFINE_PER_CPU(u64 *, thपढ़ो_imc_mem);
अटल काष्ठा imc_pmu *thपढ़ो_imc_pmu;
अटल पूर्णांक thपढ़ो_imc_mem_size;

/* Trace IMC data काष्ठाures */
अटल DEFINE_PER_CPU(u64 *, trace_imc_mem);
अटल काष्ठा imc_pmu_ref *trace_imc_refc;
अटल पूर्णांक trace_imc_mem_size;

/*
 * Global data काष्ठाure used to aव्योम races between thपढ़ो,
 * core and trace-imc
 */
अटल काष्ठा imc_pmu_ref imc_global_refc = अणु
	.lock = __MUTEX_INITIALIZER(imc_global_refc.lock),
	.id = 0,
	.refc = 0,
पूर्ण;

अटल काष्ठा imc_pmu *imc_event_to_pmu(काष्ठा perf_event *event)
अणु
	वापस container_of(event->pmu, काष्ठा imc_pmu, pmu);
पूर्ण

PMU_FORMAT_ATTR(event, "config:0-61");
PMU_FORMAT_ATTR(offset, "config:0-31");
PMU_FORMAT_ATTR(rvalue, "config:32");
PMU_FORMAT_ATTR(mode, "config:33-40");
अटल काष्ठा attribute *imc_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_offset.attr,
	&क्रमmat_attr_rvalue.attr,
	&क्रमmat_attr_mode.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group imc_क्रमmat_group = अणु
	.name = "format",
	.attrs = imc_क्रमmat_attrs,
पूर्ण;

/* Format attribute क्रम imc trace-mode */
PMU_FORMAT_ATTR(cpmc_reserved, "config:0-19");
PMU_FORMAT_ATTR(cpmc_event, "config:20-27");
PMU_FORMAT_ATTR(cpmc_samplesel, "config:28-29");
PMU_FORMAT_ATTR(cpmc_load, "config:30-61");
अटल काष्ठा attribute *trace_imc_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_cpmc_reserved.attr,
	&क्रमmat_attr_cpmc_event.attr,
	&क्रमmat_attr_cpmc_samplesel.attr,
	&क्रमmat_attr_cpmc_load.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group trace_imc_क्रमmat_group = अणु
.name = "format",
.attrs = trace_imc_क्रमmat_attrs,
पूर्ण;

/* Get the cpumask prपूर्णांकed to a buffer "buf" */
अटल sमाप_प्रकार imc_pmu_cpumask_get_attr(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा imc_pmu *imc_pmu = container_of(pmu, काष्ठा imc_pmu, pmu);
	cpumask_t *active_mask;

	चयन(imc_pmu->करोमुख्य)अणु
	हाल IMC_DOMAIN_NEST:
		active_mask = &nest_imc_cpumask;
		अवरोध;
	हाल IMC_DOMAIN_CORE:
		active_mask = &core_imc_cpumask;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, active_mask);
पूर्ण

अटल DEVICE_ATTR(cpumask, S_IRUGO, imc_pmu_cpumask_get_attr, शून्य);

अटल काष्ठा attribute *imc_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group imc_pmu_cpumask_attr_group = अणु
	.attrs = imc_pmu_cpumask_attrs,
पूर्ण;

/* device_str_attr_create : Populate event "name" and string "str" in attribute */
अटल काष्ठा attribute *device_str_attr_create(स्थिर अक्षर *name, स्थिर अक्षर *str)
अणु
	काष्ठा perf_pmu_events_attr *attr;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (!attr)
		वापस शून्य;
	sysfs_attr_init(&attr->attr.attr);

	attr->event_str = str;
	attr->attr.attr.name = name;
	attr->attr.attr.mode = 0444;
	attr->attr.show = perf_event_sysfs_show;

	वापस &attr->attr.attr;
पूर्ण

अटल पूर्णांक imc_parse_event(काष्ठा device_node *np, स्थिर अक्षर *scale,
				  स्थिर अक्षर *unit, स्थिर अक्षर *prefix,
				  u32 base, काष्ठा imc_events *event)
अणु
	स्थिर अक्षर *s;
	u32 reg;

	अगर (of_property_पढ़ो_u32(np, "reg", &reg))
		जाओ error;
	/* Add the base_reg value to the "reg" */
	event->value = base + reg;

	अगर (of_property_पढ़ो_string(np, "event-name", &s))
		जाओ error;

	event->name = kaप्र_लिखो(GFP_KERNEL, "%s%s", prefix, s);
	अगर (!event->name)
		जाओ error;

	अगर (of_property_पढ़ो_string(np, "scale", &s))
		s = scale;

	अगर (s) अणु
		event->scale = kstrdup(s, GFP_KERNEL);
		अगर (!event->scale)
			जाओ error;
	पूर्ण

	अगर (of_property_पढ़ो_string(np, "unit", &s))
		s = unit;

	अगर (s) अणु
		event->unit = kstrdup(s, GFP_KERNEL);
		अगर (!event->unit)
			जाओ error;
	पूर्ण

	वापस 0;
error:
	kमुक्त(event->unit);
	kमुक्त(event->scale);
	kमुक्त(event->name);
	वापस -EINVAL;
पूर्ण

/*
 * imc_मुक्त_events: Function to cleanup the events list, having
 * 		    "nr_entries".
 */
अटल व्योम imc_मुक्त_events(काष्ठा imc_events *events, पूर्णांक nr_entries)
अणु
	पूर्णांक i;

	/* Nothing to clean, वापस */
	अगर (!events)
		वापस;
	क्रम (i = 0; i < nr_entries; i++) अणु
		kमुक्त(events[i].unit);
		kमुक्त(events[i].scale);
		kमुक्त(events[i].name);
	पूर्ण

	kमुक्त(events);
पूर्ण

/*
 * update_events_in_group: Update the "events" inक्रमmation in an attr_group
 *                         and assign the attr_group to the pmu "pmu".
 */
अटल पूर्णांक update_events_in_group(काष्ठा device_node *node, काष्ठा imc_pmu *pmu)
अणु
	काष्ठा attribute_group *attr_group;
	काष्ठा attribute **attrs, *dev_str;
	काष्ठा device_node *np, *pmu_events;
	u32 handle, base_reg;
	पूर्णांक i = 0, j = 0, ct, ret;
	स्थिर अक्षर *prefix, *g_scale, *g_unit;
	स्थिर अक्षर *ev_val_str, *ev_scale_str, *ev_unit_str;

	अगर (!of_property_पढ़ो_u32(node, "events", &handle))
		pmu_events = of_find_node_by_phandle(handle);
	अन्यथा
		वापस 0;

	/* Did not find any node with a given phandle */
	अगर (!pmu_events)
		वापस 0;

	/* Get a count of number of child nodes */
	ct = of_get_child_count(pmu_events);

	/* Get the event prefix */
	अगर (of_property_पढ़ो_string(node, "events-prefix", &prefix))
		वापस 0;

	/* Get a global unit and scale data अगर available */
	अगर (of_property_पढ़ो_string(node, "scale", &g_scale))
		g_scale = शून्य;

	अगर (of_property_पढ़ो_string(node, "unit", &g_unit))
		g_unit = शून्य;

	/* "reg" property gives out the base offset of the counters data */
	of_property_पढ़ो_u32(node, "reg", &base_reg);

	/* Allocate memory क्रम the events */
	pmu->events = kसुस्मृति(ct, माप(काष्ठा imc_events), GFP_KERNEL);
	अगर (!pmu->events)
		वापस -ENOMEM;

	ct = 0;
	/* Parse the events and update the काष्ठा */
	क्रम_each_child_of_node(pmu_events, np) अणु
		ret = imc_parse_event(np, g_scale, g_unit, prefix, base_reg, &pmu->events[ct]);
		अगर (!ret)
			ct++;
	पूर्ण

	/* Allocate memory क्रम attribute group */
	attr_group = kzalloc(माप(*attr_group), GFP_KERNEL);
	अगर (!attr_group) अणु
		imc_मुक्त_events(pmu->events, ct);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Allocate memory क्रम attributes.
	 * Since we have count of events क्रम this pmu, we also allocate
	 * memory क्रम the scale and unit attribute क्रम now.
	 * "ct" has the total event काष्ठाs added from the events-parent node.
	 * So allocate three बार the "ct" (this includes event, event_scale and
	 * event_unit).
	 */
	attrs = kसुस्मृति(((ct * 3) + 1), माप(काष्ठा attribute *), GFP_KERNEL);
	अगर (!attrs) अणु
		kमुक्त(attr_group);
		imc_मुक्त_events(pmu->events, ct);
		वापस -ENOMEM;
	पूर्ण

	attr_group->name = "events";
	attr_group->attrs = attrs;
	करो अणु
		ev_val_str = kaप्र_लिखो(GFP_KERNEL, "event=0x%x", pmu->events[i].value);
		dev_str = device_str_attr_create(pmu->events[i].name, ev_val_str);
		अगर (!dev_str)
			जारी;

		attrs[j++] = dev_str;
		अगर (pmu->events[i].scale) अणु
			ev_scale_str = kaप्र_लिखो(GFP_KERNEL, "%s.scale", pmu->events[i].name);
			dev_str = device_str_attr_create(ev_scale_str, pmu->events[i].scale);
			अगर (!dev_str)
				जारी;

			attrs[j++] = dev_str;
		पूर्ण

		अगर (pmu->events[i].unit) अणु
			ev_unit_str = kaप्र_लिखो(GFP_KERNEL, "%s.unit", pmu->events[i].name);
			dev_str = device_str_attr_create(ev_unit_str, pmu->events[i].unit);
			अगर (!dev_str)
				जारी;

			attrs[j++] = dev_str;
		पूर्ण
	पूर्ण जबतक (++i < ct);

	/* Save the event attribute */
	pmu->attr_groups[IMC_EVENT_ATTR] = attr_group;

	वापस 0;
पूर्ण

/* get_nest_pmu_ref: Return the imc_pmu_ref काष्ठा क्रम the given node */
अटल काष्ठा imc_pmu_ref *get_nest_pmu_ref(पूर्णांक cpu)
अणु
	वापस per_cpu(local_nest_imc_refc, cpu);
पूर्ण

अटल व्योम nest_change_cpu_context(पूर्णांक old_cpu, पूर्णांक new_cpu)
अणु
	काष्ठा imc_pmu **pn = per_nest_pmu_arr;

	अगर (old_cpu < 0 || new_cpu < 0)
		वापस;

	जबतक (*pn) अणु
		perf_pmu_migrate_context(&(*pn)->pmu, old_cpu, new_cpu);
		pn++;
	पूर्ण
पूर्ण

अटल पूर्णांक ppc_nest_imc_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक nid, target = -1;
	स्थिर काष्ठा cpumask *l_cpumask;
	काष्ठा imc_pmu_ref *ref;

	/*
	 * Check in the designated list क्रम this cpu. Dont bother
	 * अगर not one of them.
	 */
	अगर (!cpumask_test_and_clear_cpu(cpu, &nest_imc_cpumask))
		वापस 0;

	/*
	 * Check whether nest_imc is रेजिस्टरed. We could end up here अगर the
	 * cpuhotplug callback registration fails. i.e, callback invokes the
	 * offline path क्रम all successfully रेजिस्टरed nodes. At this stage,
	 * nest_imc pmu will not be रेजिस्टरed and we should वापस here.
	 *
	 * We वापस with a zero since this is not an offline failure. And
	 * cpuhp_setup_state() वापसs the actual failure reason to the caller,
	 * which in turn will call the cleanup routine.
	 */
	अगर (!nest_pmus)
		वापस 0;

	/*
	 * Now that this cpu is one of the designated,
	 * find a next cpu a) which is online and b) in same chip.
	 */
	nid = cpu_to_node(cpu);
	l_cpumask = cpumask_of_node(nid);
	target = cpumask_last(l_cpumask);

	/*
	 * If this(target) is the last cpu in the cpumask क्रम this chip,
	 * check क्रम any possible online cpu in the chip.
	 */
	अगर (unlikely(target == cpu))
		target = cpumask_any_but(l_cpumask, cpu);

	/*
	 * Update the cpumask with the target cpu and
	 * migrate the context अगर needed
	 */
	अगर (target >= 0 && target < nr_cpu_ids) अणु
		cpumask_set_cpu(target, &nest_imc_cpumask);
		nest_change_cpu_context(cpu, target);
	पूर्ण अन्यथा अणु
		opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
				       get_hard_smp_processor_id(cpu));
		/*
		 * If this is the last cpu in this chip then, skip the reference
		 * count mutex lock and make the reference count on this chip zero.
		 */
		ref = get_nest_pmu_ref(cpu);
		अगर (!ref)
			वापस -EINVAL;

		ref->refc = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_nest_imc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpumask *l_cpumask;
	अटल काष्ठा cpumask पंचांगp_mask;
	पूर्णांक res;

	/* Get the cpumask of this node */
	l_cpumask = cpumask_of_node(cpu_to_node(cpu));

	/*
	 * If this is not the first online CPU on this node, then
	 * just वापस.
	 */
	अगर (cpumask_and(&पंचांगp_mask, l_cpumask, &nest_imc_cpumask))
		वापस 0;

	/*
	 * If this is the first online cpu on this node
	 * disable the nest counters by making an OPAL call.
	 */
	res = opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
				     get_hard_smp_processor_id(cpu));
	अगर (res)
		वापस res;

	/* Make this CPU the designated target क्रम counter collection */
	cpumask_set_cpu(cpu, &nest_imc_cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक nest_pmu_cpumask_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE,
				 "perf/powerpc/imc:online",
				 ppc_nest_imc_cpu_online,
				 ppc_nest_imc_cpu_offline);
पूर्ण

अटल व्योम nest_imc_counters_release(काष्ठा perf_event *event)
अणु
	पूर्णांक rc, node_id;
	काष्ठा imc_pmu_ref *ref;

	अगर (event->cpu < 0)
		वापस;

	node_id = cpu_to_node(event->cpu);

	/*
	 * See अगर we need to disable the nest PMU.
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we करोn't race with another task करोing
	 * enable or disable the nest counters.
	 */
	ref = get_nest_pmu_ref(event->cpu);
	अगर (!ref)
		वापस;

	/* Take the mutex lock क्रम this node and then decrement the reference count */
	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		/*
		 * The scenario where this is true is, when perf session is
		 * started, followed by offlining of all cpus in a given node.
		 *
		 * In the cpuhotplug offline path, ppc_nest_imc_cpu_offline()
		 * function set the ref->count to zero, अगर the cpu which is
		 * about to offline is the last cpu in a given node and make
		 * an OPAL call to disable the engine in that node.
		 *
		 */
		mutex_unlock(&ref->lock);
		वापस;
	पूर्ण
	ref->refc--;
	अगर (ref->refc == 0) अणु
		rc = opal_imc_counters_stop(OPAL_IMC_COUNTERS_NEST,
					    get_hard_smp_processor_id(event->cpu));
		अगर (rc) अणु
			mutex_unlock(&ref->lock);
			pr_err("nest-imc: Unable to stop the counters for core %d\n", node_id);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ref->refc < 0) अणु
		WARN(1, "nest-imc: Invalid event reference count\n");
		ref->refc = 0;
	पूर्ण
	mutex_unlock(&ref->lock);
पूर्ण

अटल पूर्णांक nest_imc_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक chip_id, rc, node_id;
	u32 l_config, config = event->attr.config;
	काष्ठा imc_mem_info *pcni;
	काष्ठा imc_pmu *pmu;
	काष्ठा imc_pmu_ref *ref;
	bool flag = false;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* Sampling not supported */
	अगर (event->hw.sample_period)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	pmu = imc_event_to_pmu(event);

	/* Sanity check क्रम config (event offset) */
	अगर ((config & IMC_EVENT_OFFSET_MASK) > pmu->counter_mem_size)
		वापस -EINVAL;

	/*
	 * Nest HW counter memory resides in a per-chip reserve-memory (HOMER).
	 * Get the base memory addresss क्रम this cpu.
	 */
	chip_id = cpu_to_chip_id(event->cpu);

	/* Return, अगर chip_id is not valid */
	अगर (chip_id < 0)
		वापस -ENODEV;

	pcni = pmu->mem_info;
	करो अणु
		अगर (pcni->id == chip_id) अणु
			flag = true;
			अवरोध;
		पूर्ण
		pcni++;
	पूर्ण जबतक (pcni->vbase != 0);

	अगर (!flag)
		वापस -ENODEV;

	/*
	 * Add the event offset to the base address.
	 */
	l_config = config & IMC_EVENT_OFFSET_MASK;
	event->hw.event_base = (u64)pcni->vbase + l_config;
	node_id = cpu_to_node(event->cpu);

	/*
	 * Get the imc_pmu_ref काष्ठा क्रम this node.
	 * Take the mutex lock and then increment the count of nest pmu events
	 * inited.
	 */
	ref = get_nest_pmu_ref(event->cpu);
	अगर (!ref)
		वापस -EINVAL;

	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		rc = opal_imc_counters_start(OPAL_IMC_COUNTERS_NEST,
					     get_hard_smp_processor_id(event->cpu));
		अगर (rc) अणु
			mutex_unlock(&ref->lock);
			pr_err("nest-imc: Unable to start the counters for node %d\n",
									node_id);
			वापस rc;
		पूर्ण
	पूर्ण
	++ref->refc;
	mutex_unlock(&ref->lock);

	event->destroy = nest_imc_counters_release;
	वापस 0;
पूर्ण

/*
 * core_imc_mem_init : Initializes memory क्रम the current core.
 *
 * Uses alloc_pages_node() and uses the वापसed address as an argument to
 * an opal call to configure the pdbar. The address sent as an argument is
 * converted to physical address beक्रमe the opal call is made. This is the
 * base address at which the core imc counters are populated.
 */
अटल पूर्णांक core_imc_mem_init(पूर्णांक cpu, पूर्णांक size)
अणु
	पूर्णांक nid, rc = 0, core_id = (cpu / thपढ़ोs_per_core);
	काष्ठा imc_mem_info *mem_info;
	काष्ठा page *page;

	/*
	 * alloc_pages_node() will allocate memory क्रम core in the
	 * local node only.
	 */
	nid = cpu_to_node(cpu);
	mem_info = &core_imc_pmu->mem_info[core_id];
	mem_info->id = core_id;

	/* We need only vbase क्रम core counters */
	page = alloc_pages_node(nid,
				GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE |
				__GFP_NOWARN, get_order(size));
	अगर (!page)
		वापस -ENOMEM;
	mem_info->vbase = page_address(page);

	/* Init the mutex */
	core_imc_refc[core_id].id = core_id;
	mutex_init(&core_imc_refc[core_id].lock);

	rc = opal_imc_counters_init(OPAL_IMC_COUNTERS_CORE,
				__pa((व्योम *)mem_info->vbase),
				get_hard_smp_processor_id(cpu));
	अगर (rc) अणु
		मुक्त_pages((u64)mem_info->vbase, get_order(size));
		mem_info->vbase = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool is_core_imc_mem_inited(पूर्णांक cpu)
अणु
	काष्ठा imc_mem_info *mem_info;
	पूर्णांक core_id = (cpu / thपढ़ोs_per_core);

	mem_info = &core_imc_pmu->mem_info[core_id];
	अगर (!mem_info->vbase)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ppc_core_imc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर काष्ठा cpumask *l_cpumask;
	अटल काष्ठा cpumask पंचांगp_mask;
	पूर्णांक ret = 0;

	/* Get the cpumask क्रम this core */
	l_cpumask = cpu_sibling_mask(cpu);

	/* If a cpu क्रम this core is alपढ़ोy set, then, करोn't करो anything */
	अगर (cpumask_and(&पंचांगp_mask, l_cpumask, &core_imc_cpumask))
		वापस 0;

	अगर (!is_core_imc_mem_inited(cpu)) अणु
		ret = core_imc_mem_init(cpu, core_imc_pmu->counter_mem_size);
		अगर (ret) अणु
			pr_info("core_imc memory allocation for cpu %d failed\n", cpu);
			वापस ret;
		पूर्ण
	पूर्ण

	/* set the cpu in the mask */
	cpumask_set_cpu(cpu, &core_imc_cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_core_imc_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक core_id;
	पूर्णांक ncpu;
	काष्ठा imc_pmu_ref *ref;

	/*
	 * clear this cpu out of the mask, अगर not present in the mask,
	 * करोn't bother करोing anything.
	 */
	अगर (!cpumask_test_and_clear_cpu(cpu, &core_imc_cpumask))
		वापस 0;

	/*
	 * Check whether core_imc is रेजिस्टरed. We could end up here
	 * अगर the cpuhotplug callback registration fails. i.e, callback
	 * invokes the offline path क्रम all sucessfully रेजिस्टरed cpus.
	 * At this stage, core_imc pmu will not be रेजिस्टरed and we
	 * should वापस here.
	 *
	 * We वापस with a zero since this is not an offline failure.
	 * And cpuhp_setup_state() वापसs the actual failure reason
	 * to the caller, which पूर्णांकurn will call the cleanup routine.
	 */
	अगर (!core_imc_pmu->pmu.event_init)
		वापस 0;

	/* Find any online cpu in that core except the current "cpu" */
	ncpu = cpumask_last(cpu_sibling_mask(cpu));

	अगर (unlikely(ncpu == cpu))
		ncpu = cpumask_any_but(cpu_sibling_mask(cpu), cpu);

	अगर (ncpu >= 0 && ncpu < nr_cpu_ids) अणु
		cpumask_set_cpu(ncpu, &core_imc_cpumask);
		perf_pmu_migrate_context(&core_imc_pmu->pmu, cpu, ncpu);
	पूर्ण अन्यथा अणु
		/*
		 * If this is the last cpu in this core then, skip taking refernce
		 * count mutex lock क्रम this core and directly zero "refc" क्रम
		 * this core.
		 */
		opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
				       get_hard_smp_processor_id(cpu));
		core_id = cpu / thपढ़ोs_per_core;
		ref = &core_imc_refc[core_id];
		अगर (!ref)
			वापस -EINVAL;

		ref->refc = 0;
		/*
		 * Reduce the global reference count, अगर this is the
		 * last cpu in this core and core-imc event running
		 * in this cpu.
		 */
		mutex_lock(&imc_global_refc.lock);
		अगर (imc_global_refc.id == IMC_DOMAIN_CORE)
			imc_global_refc.refc--;

		mutex_unlock(&imc_global_refc.lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक core_imc_pmu_cpumask_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE,
				 "perf/powerpc/imc_core:online",
				 ppc_core_imc_cpu_online,
				 ppc_core_imc_cpu_offline);
पूर्ण

अटल व्योम reset_global_refc(काष्ठा perf_event *event)
अणु
		mutex_lock(&imc_global_refc.lock);
		imc_global_refc.refc--;

		/*
		 * If no other thपढ़ो is running any
		 * event क्रम this करोमुख्य(thपढ़ो/core/trace),
		 * set the global id to zero.
		 */
		अगर (imc_global_refc.refc <= 0) अणु
			imc_global_refc.refc = 0;
			imc_global_refc.id = 0;
		पूर्ण
		mutex_unlock(&imc_global_refc.lock);
पूर्ण

अटल व्योम core_imc_counters_release(काष्ठा perf_event *event)
अणु
	पूर्णांक rc, core_id;
	काष्ठा imc_pmu_ref *ref;

	अगर (event->cpu < 0)
		वापस;
	/*
	 * See अगर we need to disable the IMC PMU.
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we करोn't race with another task करोing
	 * enable or disable the core counters.
	 */
	core_id = event->cpu / thपढ़ोs_per_core;

	/* Take the mutex lock and decrement the refernce count क्रम this core */
	ref = &core_imc_refc[core_id];
	अगर (!ref)
		वापस;

	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		/*
		 * The scenario where this is true is, when perf session is
		 * started, followed by offlining of all cpus in a given core.
		 *
		 * In the cpuhotplug offline path, ppc_core_imc_cpu_offline()
		 * function set the ref->count to zero, अगर the cpu which is
		 * about to offline is the last cpu in a given core and make
		 * an OPAL call to disable the engine in that core.
		 *
		 */
		mutex_unlock(&ref->lock);
		वापस;
	पूर्ण
	ref->refc--;
	अगर (ref->refc == 0) अणु
		rc = opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
					    get_hard_smp_processor_id(event->cpu));
		अगर (rc) अणु
			mutex_unlock(&ref->lock);
			pr_err("IMC: Unable to stop the counters for core %d\n", core_id);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ref->refc < 0) अणु
		WARN(1, "core-imc: Invalid event reference count\n");
		ref->refc = 0;
	पूर्ण
	mutex_unlock(&ref->lock);

	reset_global_refc(event);
पूर्ण

अटल पूर्णांक core_imc_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक core_id, rc;
	u64 config = event->attr.config;
	काष्ठा imc_mem_info *pcmi;
	काष्ठा imc_pmu *pmu;
	काष्ठा imc_pmu_ref *ref;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* Sampling not supported */
	अगर (event->hw.sample_period)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	event->hw.idx = -1;
	pmu = imc_event_to_pmu(event);

	/* Sanity check क्रम config (event offset) */
	अगर (((config & IMC_EVENT_OFFSET_MASK) > pmu->counter_mem_size))
		वापस -EINVAL;

	अगर (!is_core_imc_mem_inited(event->cpu))
		वापस -ENODEV;

	core_id = event->cpu / thपढ़ोs_per_core;
	pcmi = &core_imc_pmu->mem_info[core_id];
	अगर ((!pcmi->vbase))
		वापस -ENODEV;

	/* Get the core_imc mutex क्रम this core */
	ref = &core_imc_refc[core_id];
	अगर (!ref)
		वापस -EINVAL;

	/*
	 * Core pmu units are enabled only when it is used.
	 * See अगर this is triggered क्रम the first समय.
	 * If yes, take the mutex lock and enable the core counters.
	 * If not, just increment the count in core_imc_refc काष्ठा.
	 */
	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		rc = opal_imc_counters_start(OPAL_IMC_COUNTERS_CORE,
					     get_hard_smp_processor_id(event->cpu));
		अगर (rc) अणु
			mutex_unlock(&ref->lock);
			pr_err("core-imc: Unable to start the counters for core %d\n",
									core_id);
			वापस rc;
		पूर्ण
	पूर्ण
	++ref->refc;
	mutex_unlock(&ref->lock);

	/*
	 * Since the प्रणाली can run either in accumulation or trace-mode
	 * of IMC at a समय, core-imc events are allowed only अगर no other
	 * trace/thपढ़ो imc events are enabled/monitored.
	 *
	 * Take the global lock, and check the refc.id
	 * to know whether any other trace/thपढ़ो imc
	 * events are running.
	 */
	mutex_lock(&imc_global_refc.lock);
	अगर (imc_global_refc.id == 0 || imc_global_refc.id == IMC_DOMAIN_CORE) अणु
		/*
		 * No other trace/thपढ़ो imc events are running in
		 * the प्रणाली, so set the refc.id to core-imc.
		 */
		imc_global_refc.id = IMC_DOMAIN_CORE;
		imc_global_refc.refc++;
	पूर्ण अन्यथा अणु
		mutex_unlock(&imc_global_refc.lock);
		वापस -EBUSY;
	पूर्ण
	mutex_unlock(&imc_global_refc.lock);

	event->hw.event_base = (u64)pcmi->vbase + (config & IMC_EVENT_OFFSET_MASK);
	event->destroy = core_imc_counters_release;
	वापस 0;
पूर्ण

/*
 * Allocates a page of memory क्रम each of the online cpus, and load
 * LDBAR with 0.
 * The physical base address of the page allocated क्रम a cpu will be
 * written to the LDBAR क्रम that cpu, when the thपढ़ो-imc event
 * is added.
 *
 * LDBAR Register Layout:
 *
 *  0          4         8         12        16        20        24        28
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | |       [   ]    [                   Counter Address [8:50]
 *   | * Mode    |
 *   |           * PB Scope
 *   * Enable/Disable
 *
 *  32        36        40        44        48        52        56        60
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *           Counter Address [8:50]              ]
 *
 */
अटल पूर्णांक thपढ़ो_imc_mem_alloc(पूर्णांक cpu_id, पूर्णांक size)
अणु
	u64 *local_mem = per_cpu(thपढ़ो_imc_mem, cpu_id);
	पूर्णांक nid = cpu_to_node(cpu_id);

	अगर (!local_mem) अणु
		काष्ठा page *page;
		/*
		 * This हाल could happen only once at start, since we करोnt
		 * मुक्त the memory in cpu offline path.
		 */
		page = alloc_pages_node(nid,
				  GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE |
				  __GFP_NOWARN, get_order(size));
		अगर (!page)
			वापस -ENOMEM;
		local_mem = page_address(page);

		per_cpu(thपढ़ो_imc_mem, cpu_id) = local_mem;
	पूर्ण

	mtspr(SPRN_LDBAR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_thपढ़ो_imc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	वापस thपढ़ो_imc_mem_alloc(cpu, thपढ़ो_imc_mem_size);
पूर्ण

अटल पूर्णांक ppc_thपढ़ो_imc_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * Set the bit 0 of LDBAR to zero.
	 *
	 * If bit 0 of LDBAR is unset, it will stop posting
	 * the counter data to memory.
	 * For thपढ़ो-imc, bit 0 of LDBAR will be set to 1 in the
	 * event_add function. So reset this bit here, to stop the updates
	 * to memory in the cpu_offline path.
	 */
	mtspr(SPRN_LDBAR, (mfspr(SPRN_LDBAR) & (~(1UL << 63))));

	/* Reduce the refc अगर thपढ़ो-imc event running on this cpu */
	mutex_lock(&imc_global_refc.lock);
	अगर (imc_global_refc.id == IMC_DOMAIN_THREAD)
		imc_global_refc.refc--;
	mutex_unlock(&imc_global_refc.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_imc_cpu_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE,
			  "perf/powerpc/imc_thread:online",
			  ppc_thपढ़ो_imc_cpu_online,
			  ppc_thपढ़ो_imc_cpu_offline);
पूर्ण

अटल पूर्णांक thपढ़ो_imc_event_init(काष्ठा perf_event *event)
अणु
	u32 config = event->attr.config;
	काष्ठा task_काष्ठा *target;
	काष्ठा imc_pmu *pmu;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (!perfmon_capable())
		वापस -EACCES;

	/* Sampling not supported */
	अगर (event->hw.sample_period)
		वापस -EINVAL;

	event->hw.idx = -1;
	pmu = imc_event_to_pmu(event);

	/* Sanity check क्रम config offset */
	अगर (((config & IMC_EVENT_OFFSET_MASK) > pmu->counter_mem_size))
		वापस -EINVAL;

	target = event->hw.target;
	अगर (!target)
		वापस -EINVAL;

	mutex_lock(&imc_global_refc.lock);
	/*
	 * Check अगर any other trace/core imc events are running in the
	 * प्रणाली, अगर not set the global id to thपढ़ो-imc.
	 */
	अगर (imc_global_refc.id == 0 || imc_global_refc.id == IMC_DOMAIN_THREAD) अणु
		imc_global_refc.id = IMC_DOMAIN_THREAD;
		imc_global_refc.refc++;
	पूर्ण अन्यथा अणु
		mutex_unlock(&imc_global_refc.lock);
		वापस -EBUSY;
	पूर्ण
	mutex_unlock(&imc_global_refc.lock);

	event->pmu->task_ctx_nr = perf_sw_context;
	event->destroy = reset_global_refc;
	वापस 0;
पूर्ण

अटल bool is_thपढ़ो_imc_pmu(काष्ठा perf_event *event)
अणु
	अगर (!म_भेदन(event->pmu->name, "thread_imc", म_माप("thread_imc")))
		वापस true;

	वापस false;
पूर्ण

अटल u64 * get_event_base_addr(काष्ठा perf_event *event)
अणु
	u64 addr;

	अगर (is_thपढ़ो_imc_pmu(event)) अणु
		addr = (u64)per_cpu(thपढ़ो_imc_mem, smp_processor_id());
		वापस (u64 *)(addr + (event->attr.config & IMC_EVENT_OFFSET_MASK));
	पूर्ण

	वापस (u64 *)event->hw.event_base;
पूर्ण

अटल व्योम thपढ़ो_imc_pmu_start_txn(काष्ठा pmu *pmu,
				     अचिन्हित पूर्णांक txn_flags)
अणु
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;
	perf_pmu_disable(pmu);
पूर्ण

अटल व्योम thपढ़ो_imc_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	perf_pmu_enable(pmu);
पूर्ण

अटल पूर्णांक thपढ़ो_imc_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण

अटल u64 imc_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	u64 *addr, data;

	/*
	 * In-Memory Collection (IMC) counters are मुक्त flowing counters.
	 * So we take a snapshot of the counter value on enable and save it
	 * to calculate the delta at later stage to present the event counter
	 * value.
	 */
	addr = get_event_base_addr(event);
	data = be64_to_cpu(READ_ONCE(*addr));
	local64_set(&event->hw.prev_count, data);

	वापस data;
पूर्ण

अटल व्योम imc_event_update(काष्ठा perf_event *event)
अणु
	u64 counter_prev, counter_new, final_count;

	counter_prev = local64_पढ़ो(&event->hw.prev_count);
	counter_new = imc_पढ़ो_counter(event);
	final_count = counter_new - counter_prev;

	/* Update the delta to the event count */
	local64_add(final_count, &event->count);
पूर्ण

अटल व्योम imc_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	/*
	 * In Memory Counters are मुक्त flowing counters. HW or the microcode
	 * keeps adding to the counter offset in memory. To get event
	 * counter value, we snapshot the value here and we calculate
	 * delta at later poपूर्णांक.
	 */
	imc_पढ़ो_counter(event);
पूर्ण

अटल व्योम imc_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	/*
	 * Take a snapshot and calculate the delta and update
	 * the event counter values.
	 */
	imc_event_update(event);
पूर्ण

अटल पूर्णांक imc_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		imc_event_start(event, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक thपढ़ो_imc_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक core_id;
	काष्ठा imc_pmu_ref *ref;
	u64 ldbar_value, *local_mem = per_cpu(thपढ़ो_imc_mem, smp_processor_id());

	अगर (flags & PERF_EF_START)
		imc_event_start(event, flags);

	अगर (!is_core_imc_mem_inited(smp_processor_id()))
		वापस -EINVAL;

	core_id = smp_processor_id() / thपढ़ोs_per_core;
	ldbar_value = ((u64)local_mem & THREAD_IMC_LDBAR_MASK) | THREAD_IMC_ENABLE;
	mtspr(SPRN_LDBAR, ldbar_value);

	/*
	 * imc pmus are enabled only when it is used.
	 * See अगर this is triggered क्रम the first समय.
	 * If yes, take the mutex lock and enable the counters.
	 * If not, just increment the count in ref count काष्ठा.
	 */
	ref = &core_imc_refc[core_id];
	अगर (!ref)
		वापस -EINVAL;

	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		अगर (opal_imc_counters_start(OPAL_IMC_COUNTERS_CORE,
		    get_hard_smp_processor_id(smp_processor_id()))) अणु
			mutex_unlock(&ref->lock);
			pr_err("thपढ़ो-imc: Unable to start the counter\
				क्रम core %d\न", core_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	++ref->refc;
	mutex_unlock(&ref->lock);
	वापस 0;
पूर्ण

अटल व्योम thपढ़ो_imc_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु

	पूर्णांक core_id;
	काष्ठा imc_pmu_ref *ref;

	core_id = smp_processor_id() / thपढ़ोs_per_core;
	ref = &core_imc_refc[core_id];
	अगर (!ref) अणु
		pr_debug("imc: Failed to get event reference count\n");
		वापस;
	पूर्ण

	mutex_lock(&ref->lock);
	ref->refc--;
	अगर (ref->refc == 0) अणु
		अगर (opal_imc_counters_stop(OPAL_IMC_COUNTERS_CORE,
		    get_hard_smp_processor_id(smp_processor_id()))) अणु
			mutex_unlock(&ref->lock);
			pr_err("thपढ़ो-imc: Unable to stop the counters\
				क्रम core %d\न", core_id);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ref->refc < 0) अणु
		ref->refc = 0;
	पूर्ण
	mutex_unlock(&ref->lock);

	/* Set bit 0 of LDBAR to zero, to stop posting updates to memory */
	mtspr(SPRN_LDBAR, (mfspr(SPRN_LDBAR) & (~(1UL << 63))));

	/*
	 * Take a snapshot and calculate the delta and update
	 * the event counter values.
	 */
	imc_event_update(event);
पूर्ण

/*
 * Allocate a page of memory क्रम each cpu, and load LDBAR with 0.
 */
अटल पूर्णांक trace_imc_mem_alloc(पूर्णांक cpu_id, पूर्णांक size)
अणु
	u64 *local_mem = per_cpu(trace_imc_mem, cpu_id);
	पूर्णांक phys_id = cpu_to_node(cpu_id), rc = 0;
	पूर्णांक core_id = (cpu_id / thपढ़ोs_per_core);

	अगर (!local_mem) अणु
		काष्ठा page *page;

		page = alloc_pages_node(phys_id,
				GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE |
				__GFP_NOWARN, get_order(size));
		अगर (!page)
			वापस -ENOMEM;
		local_mem = page_address(page);
		per_cpu(trace_imc_mem, cpu_id) = local_mem;

		/* Initialise the counters क्रम trace mode */
		rc = opal_imc_counters_init(OPAL_IMC_COUNTERS_TRACE, __pa((व्योम *)local_mem),
					    get_hard_smp_processor_id(cpu_id));
		अगर (rc) अणु
			pr_info("IMC:opal init failed for trace imc\n");
			वापस rc;
		पूर्ण
	पूर्ण

	/* Init the mutex, अगर not alपढ़ोy */
	trace_imc_refc[core_id].id = core_id;
	mutex_init(&trace_imc_refc[core_id].lock);

	mtspr(SPRN_LDBAR, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_trace_imc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	वापस trace_imc_mem_alloc(cpu, trace_imc_mem_size);
पूर्ण

अटल पूर्णांक ppc_trace_imc_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * No need to set bit 0 of LDBAR to zero, as
	 * it is set to zero क्रम imc trace-mode
	 *
	 * Reduce the refc अगर any trace-imc event running
	 * on this cpu.
	 */
	mutex_lock(&imc_global_refc.lock);
	अगर (imc_global_refc.id == IMC_DOMAIN_TRACE)
		imc_global_refc.refc--;
	mutex_unlock(&imc_global_refc.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक trace_imc_cpu_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE,
			  "perf/powerpc/imc_trace:online",
			  ppc_trace_imc_cpu_online,
			  ppc_trace_imc_cpu_offline);
पूर्ण

अटल u64 get_trace_imc_event_base_addr(व्योम)
अणु
	वापस (u64)per_cpu(trace_imc_mem, smp_processor_id());
पूर्ण

/*
 * Function to parse trace-imc data obtained
 * and to prepare the perf sample.
 */
अटल पूर्णांक trace_imc_prepare_sample(काष्ठा trace_imc_data *mem,
				    काष्ठा perf_sample_data *data,
				    u64 *prev_tb,
				    काष्ठा perf_event_header *header,
				    काष्ठा perf_event *event)
अणु
	/* Sanity checks क्रम a valid record */
	अगर (be64_to_cpu(READ_ONCE(mem->tb1)) > *prev_tb)
		*prev_tb = be64_to_cpu(READ_ONCE(mem->tb1));
	अन्यथा
		वापस -EINVAL;

	अगर ((be64_to_cpu(READ_ONCE(mem->tb1)) & IMC_TRACE_RECORD_TB1_MASK) !=
			 be64_to_cpu(READ_ONCE(mem->tb2)))
		वापस -EINVAL;

	/* Prepare perf sample */
	data->ip =  be64_to_cpu(READ_ONCE(mem->ip));
	data->period = event->hw.last_period;

	header->type = PERF_RECORD_SAMPLE;
	header->size = माप(*header) + event->header_size;
	header->misc = 0;

	अगर (cpu_has_feature(CPU_FTR_ARCH_31)) अणु
		चयन (IMC_TRACE_RECORD_VAL_HVPR(be64_to_cpu(READ_ONCE(mem->val)))) अणु
		हाल 0:/* when MSR HV and PR not set in the trace-record */
			header->misc |= PERF_RECORD_MISC_GUEST_KERNEL;
			अवरोध;
		हाल 1: /* MSR HV is 0 and PR is 1 */
			header->misc |= PERF_RECORD_MISC_GUEST_USER;
			अवरोध;
		हाल 2: /* MSR HV is 1 and PR is 0 */
			header->misc |= PERF_RECORD_MISC_KERNEL;
			अवरोध;
		हाल 3: /* MSR HV is 1 and PR is 1 */
			header->misc |= PERF_RECORD_MISC_USER;
			अवरोध;
		शेष:
			pr_info("IMC: Unable to set the flag based on MSR bits\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (is_kernel_addr(data->ip))
			header->misc |= PERF_RECORD_MISC_KERNEL;
		अन्यथा
			header->misc |= PERF_RECORD_MISC_USER;
	पूर्ण
	perf_event_header__init_id(header, data, event);

	वापस 0;
पूर्ण

अटल व्योम dump_trace_imc_data(काष्ठा perf_event *event)
अणु
	काष्ठा trace_imc_data *mem;
	पूर्णांक i, ret;
	u64 prev_tb = 0;

	mem = (काष्ठा trace_imc_data *)get_trace_imc_event_base_addr();
	क्रम (i = 0; i < (trace_imc_mem_size / माप(काष्ठा trace_imc_data));
		i++, mem++) अणु
		काष्ठा perf_sample_data data;
		काष्ठा perf_event_header header;

		ret = trace_imc_prepare_sample(mem, &data, &prev_tb, &header, event);
		अगर (ret) /* Exit, अगर not a valid record */
			अवरोध;
		अन्यथा अणु
			/* If this is a valid record, create the sample */
			काष्ठा perf_output_handle handle;

			अगर (perf_output_begin(&handle, &data, event, header.size))
				वापस;

			perf_output_sample(&handle, &header, &data, event);
			perf_output_end(&handle);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक trace_imc_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक core_id = smp_processor_id() / thपढ़ोs_per_core;
	काष्ठा imc_pmu_ref *ref = शून्य;
	u64 local_mem, ldbar_value;

	/* Set trace-imc bit in ldbar and load ldbar with per-thपढ़ो memory address */
	local_mem = get_trace_imc_event_base_addr();
	ldbar_value = ((u64)local_mem & THREAD_IMC_LDBAR_MASK) | TRACE_IMC_ENABLE;

	/* trace-imc reference count */
	अगर (trace_imc_refc)
		ref = &trace_imc_refc[core_id];
	अगर (!ref) अणु
		pr_debug("imc: Failed to get the event reference count\n");
		वापस -EINVAL;
	पूर्ण

	mtspr(SPRN_LDBAR, ldbar_value);
	mutex_lock(&ref->lock);
	अगर (ref->refc == 0) अणु
		अगर (opal_imc_counters_start(OPAL_IMC_COUNTERS_TRACE,
				get_hard_smp_processor_id(smp_processor_id()))) अणु
			mutex_unlock(&ref->lock);
			pr_err("trace-imc: Unable to start the counters for core %d\n", core_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	++ref->refc;
	mutex_unlock(&ref->lock);
	वापस 0;
पूर्ण

अटल व्योम trace_imc_event_पढ़ो(काष्ठा perf_event *event)
अणु
	वापस;
पूर्ण

अटल व्योम trace_imc_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u64 local_mem = get_trace_imc_event_base_addr();
	dump_trace_imc_data(event);
	स_रखो((व्योम *)local_mem, 0, माप(u64));
पूर्ण

अटल व्योम trace_imc_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	वापस;
पूर्ण

अटल व्योम trace_imc_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक core_id = smp_processor_id() / thपढ़ोs_per_core;
	काष्ठा imc_pmu_ref *ref = शून्य;

	अगर (trace_imc_refc)
		ref = &trace_imc_refc[core_id];
	अगर (!ref) अणु
		pr_debug("imc: Failed to get event reference count\n");
		वापस;
	पूर्ण

	mutex_lock(&ref->lock);
	ref->refc--;
	अगर (ref->refc == 0) अणु
		अगर (opal_imc_counters_stop(OPAL_IMC_COUNTERS_TRACE,
				get_hard_smp_processor_id(smp_processor_id()))) अणु
			mutex_unlock(&ref->lock);
			pr_err("trace-imc: Unable to stop the counters for core %d\n", core_id);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ref->refc < 0) अणु
		ref->refc = 0;
	पूर्ण
	mutex_unlock(&ref->lock);

	trace_imc_event_stop(event, flags);
पूर्ण

अटल पूर्णांक trace_imc_event_init(काष्ठा perf_event *event)
अणु
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (!perfmon_capable())
		वापस -EACCES;

	/* Return अगर this is a couting event */
	अगर (event->attr.sample_period == 0)
		वापस -ENOENT;

	/*
	 * Take the global lock, and make sure
	 * no other thपढ़ो is running any core/thपढ़ो imc
	 * events
	 */
	mutex_lock(&imc_global_refc.lock);
	अगर (imc_global_refc.id == 0 || imc_global_refc.id == IMC_DOMAIN_TRACE) अणु
		/*
		 * No core/thपढ़ो imc events are running in the
		 * प्रणाली, so set the refc.id to trace-imc.
		 */
		imc_global_refc.id = IMC_DOMAIN_TRACE;
		imc_global_refc.refc++;
	पूर्ण अन्यथा अणु
		mutex_unlock(&imc_global_refc.lock);
		वापस -EBUSY;
	पूर्ण
	mutex_unlock(&imc_global_refc.lock);

	event->hw.idx = -1;

	event->pmu->task_ctx_nr = perf_hw_context;
	event->destroy = reset_global_refc;
	वापस 0;
पूर्ण

/* update_pmu_ops : Populate the appropriate operations क्रम "pmu" */
अटल पूर्णांक update_pmu_ops(काष्ठा imc_pmu *pmu)
अणु
	pmu->pmu.task_ctx_nr = perf_invalid_context;
	pmu->pmu.add = imc_event_add;
	pmu->pmu.del = imc_event_stop;
	pmu->pmu.start = imc_event_start;
	pmu->pmu.stop = imc_event_stop;
	pmu->pmu.पढ़ो = imc_event_update;
	pmu->pmu.attr_groups = pmu->attr_groups;
	pmu->pmu.capabilities = PERF_PMU_CAP_NO_EXCLUDE;
	pmu->attr_groups[IMC_FORMAT_ATTR] = &imc_क्रमmat_group;

	चयन (pmu->करोमुख्य) अणु
	हाल IMC_DOMAIN_NEST:
		pmu->pmu.event_init = nest_imc_event_init;
		pmu->attr_groups[IMC_CPUMASK_ATTR] = &imc_pmu_cpumask_attr_group;
		अवरोध;
	हाल IMC_DOMAIN_CORE:
		pmu->pmu.event_init = core_imc_event_init;
		pmu->attr_groups[IMC_CPUMASK_ATTR] = &imc_pmu_cpumask_attr_group;
		अवरोध;
	हाल IMC_DOMAIN_THREAD:
		pmu->pmu.event_init = thपढ़ो_imc_event_init;
		pmu->pmu.add = thपढ़ो_imc_event_add;
		pmu->pmu.del = thपढ़ो_imc_event_del;
		pmu->pmu.start_txn = thपढ़ो_imc_pmu_start_txn;
		pmu->pmu.cancel_txn = thपढ़ो_imc_pmu_cancel_txn;
		pmu->pmu.commit_txn = thपढ़ो_imc_pmu_commit_txn;
		अवरोध;
	हाल IMC_DOMAIN_TRACE:
		pmu->pmu.event_init = trace_imc_event_init;
		pmu->pmu.add = trace_imc_event_add;
		pmu->pmu.del = trace_imc_event_del;
		pmu->pmu.start = trace_imc_event_start;
		pmu->pmu.stop = trace_imc_event_stop;
		pmu->pmu.पढ़ो = trace_imc_event_पढ़ो;
		pmu->attr_groups[IMC_FORMAT_ATTR] = &trace_imc_क्रमmat_group;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* init_nest_pmu_ref: Initialize the imc_pmu_ref काष्ठा क्रम all the nodes */
अटल पूर्णांक init_nest_pmu_ref(व्योम)
अणु
	पूर्णांक nid, i, cpu;

	nest_imc_refc = kसुस्मृति(num_possible_nodes(), माप(*nest_imc_refc),
								GFP_KERNEL);

	अगर (!nest_imc_refc)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_node(nid) अणु
		/*
		 * Mutex lock to aव्योम races जबतक tracking the number of
		 * sessions using the chip's nest pmu units.
		 */
		mutex_init(&nest_imc_refc[i].lock);

		/*
		 * Loop to init the "id" with the node_id. Variable "i" initialized to
		 * 0 and will be used as index to the array. "i" will not go off the
		 * end of the array since the "for_each_node" loops क्रम "N_POSSIBLE"
		 * nodes only.
		 */
		nest_imc_refc[i++].id = nid;
	पूर्ण

	/*
	 * Loop to init the per_cpu "local_nest_imc_refc" with the proper
	 * "nest_imc_refc" index. This makes get_nest_pmu_ref() alot simple.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		nid = cpu_to_node(cpu);
		क्रम (i = 0; i < num_possible_nodes(); i++) अणु
			अगर (nest_imc_refc[i].id == nid) अणु
				per_cpu(local_nest_imc_refc, cpu) = &nest_imc_refc[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cleanup_all_core_imc_memory(व्योम)
अणु
	पूर्णांक i, nr_cores = DIV_ROUND_UP(num_possible_cpus(), thपढ़ोs_per_core);
	काष्ठा imc_mem_info *ptr = core_imc_pmu->mem_info;
	पूर्णांक size = core_imc_pmu->counter_mem_size;

	/* mem_info will never be शून्य */
	क्रम (i = 0; i < nr_cores; i++) अणु
		अगर (ptr[i].vbase)
			मुक्त_pages((u64)ptr[i].vbase, get_order(size));
	पूर्ण

	kमुक्त(ptr);
	kमुक्त(core_imc_refc);
पूर्ण

अटल व्योम thपढ़ो_imc_ldbar_disable(व्योम *dummy)
अणु
	/*
	 * By setting 0th bit of LDBAR to zero, we disable thपढ़ो-imc
	 * updates to memory.
	 */
	mtspr(SPRN_LDBAR, (mfspr(SPRN_LDBAR) & (~(1UL << 63))));
पूर्ण

व्योम thपढ़ो_imc_disable(व्योम)
अणु
	on_each_cpu(thपढ़ो_imc_ldbar_disable, शून्य, 1);
पूर्ण

अटल व्योम cleanup_all_thपढ़ो_imc_memory(व्योम)
अणु
	पूर्णांक i, order = get_order(thपढ़ो_imc_mem_size);

	क्रम_each_online_cpu(i) अणु
		अगर (per_cpu(thपढ़ो_imc_mem, i))
			मुक्त_pages((u64)per_cpu(thपढ़ो_imc_mem, i), order);

	पूर्ण
पूर्ण

अटल व्योम cleanup_all_trace_imc_memory(व्योम)
अणु
	पूर्णांक i, order = get_order(trace_imc_mem_size);

	क्रम_each_online_cpu(i) अणु
		अगर (per_cpu(trace_imc_mem, i))
			मुक्त_pages((u64)per_cpu(trace_imc_mem, i), order);

	पूर्ण
	kमुक्त(trace_imc_refc);
पूर्ण

/* Function to मुक्त the attr_groups which are dynamically allocated */
अटल व्योम imc_common_mem_मुक्त(काष्ठा imc_pmu *pmu_ptr)
अणु
	अगर (pmu_ptr->attr_groups[IMC_EVENT_ATTR])
		kमुक्त(pmu_ptr->attr_groups[IMC_EVENT_ATTR]->attrs);
	kमुक्त(pmu_ptr->attr_groups[IMC_EVENT_ATTR]);
पूर्ण

/*
 * Common function to unरेजिस्टर cpu hotplug callback and
 * मुक्त the memory.
 * TODO: Need to handle pmu unरेजिस्टरing, which will be
 * करोne in followup series.
 */
अटल व्योम imc_common_cpuhp_mem_मुक्त(काष्ठा imc_pmu *pmu_ptr)
अणु
	अगर (pmu_ptr->करोमुख्य == IMC_DOMAIN_NEST) अणु
		mutex_lock(&nest_init_lock);
		अगर (nest_pmus == 1) अणु
			cpuhp_हटाओ_state(CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE);
			kमुक्त(nest_imc_refc);
			kमुक्त(per_nest_pmu_arr);
			per_nest_pmu_arr = शून्य;
		पूर्ण

		अगर (nest_pmus > 0)
			nest_pmus--;
		mutex_unlock(&nest_init_lock);
	पूर्ण

	/* Free core_imc memory */
	अगर (pmu_ptr->करोमुख्य == IMC_DOMAIN_CORE) अणु
		cpuhp_हटाओ_state(CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE);
		cleanup_all_core_imc_memory();
	पूर्ण

	/* Free thपढ़ो_imc memory */
	अगर (pmu_ptr->करोमुख्य == IMC_DOMAIN_THREAD) अणु
		cpuhp_हटाओ_state(CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE);
		cleanup_all_thपढ़ो_imc_memory();
	पूर्ण

	अगर (pmu_ptr->करोमुख्य == IMC_DOMAIN_TRACE) अणु
		cpuhp_हटाओ_state(CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE);
		cleanup_all_trace_imc_memory();
	पूर्ण
पूर्ण

/*
 * Function to unरेजिस्टर thपढ़ो-imc अगर core-imc
 * is not रेजिस्टरed.
 */
व्योम unरेजिस्टर_thपढ़ो_imc(व्योम)
अणु
	imc_common_cpuhp_mem_मुक्त(thपढ़ो_imc_pmu);
	imc_common_mem_मुक्त(thपढ़ो_imc_pmu);
	perf_pmu_unरेजिस्टर(&thपढ़ो_imc_pmu->pmu);
पूर्ण

/*
 * imc_mem_init : Function to support memory allocation क्रम core imc.
 */
अटल पूर्णांक imc_mem_init(काष्ठा imc_pmu *pmu_ptr, काष्ठा device_node *parent,
								पूर्णांक pmu_index)
अणु
	स्थिर अक्षर *s;
	पूर्णांक nr_cores, cpu, res = -ENOMEM;

	अगर (of_property_पढ़ो_string(parent, "name", &s))
		वापस -ENODEV;

	चयन (pmu_ptr->करोमुख्य) अणु
	हाल IMC_DOMAIN_NEST:
		/* Update the pmu name */
		pmu_ptr->pmu.name = kaप्र_लिखो(GFP_KERNEL, "%s%s_imc", "nest_", s);
		अगर (!pmu_ptr->pmu.name)
			जाओ err;

		/* Needed क्रम hotplug/migration */
		अगर (!per_nest_pmu_arr) अणु
			per_nest_pmu_arr = kसुस्मृति(get_max_nest_dev() + 1,
						माप(काष्ठा imc_pmu *),
						GFP_KERNEL);
			अगर (!per_nest_pmu_arr)
				जाओ err;
		पूर्ण
		per_nest_pmu_arr[pmu_index] = pmu_ptr;
		अवरोध;
	हाल IMC_DOMAIN_CORE:
		/* Update the pmu name */
		pmu_ptr->pmu.name = kaप्र_लिखो(GFP_KERNEL, "%s%s", s, "_imc");
		अगर (!pmu_ptr->pmu.name)
			जाओ err;

		nr_cores = DIV_ROUND_UP(num_possible_cpus(), thपढ़ोs_per_core);
		pmu_ptr->mem_info = kसुस्मृति(nr_cores, माप(काष्ठा imc_mem_info),
								GFP_KERNEL);

		अगर (!pmu_ptr->mem_info)
			जाओ err;

		core_imc_refc = kसुस्मृति(nr_cores, माप(काष्ठा imc_pmu_ref),
								GFP_KERNEL);

		अगर (!core_imc_refc) अणु
			kमुक्त(pmu_ptr->mem_info);
			जाओ err;
		पूर्ण

		core_imc_pmu = pmu_ptr;
		अवरोध;
	हाल IMC_DOMAIN_THREAD:
		/* Update the pmu name */
		pmu_ptr->pmu.name = kaप्र_लिखो(GFP_KERNEL, "%s%s", s, "_imc");
		अगर (!pmu_ptr->pmu.name)
			जाओ err;

		thपढ़ो_imc_mem_size = pmu_ptr->counter_mem_size;
		क्रम_each_online_cpu(cpu) अणु
			res = thपढ़ो_imc_mem_alloc(cpu, pmu_ptr->counter_mem_size);
			अगर (res) अणु
				cleanup_all_thपढ़ो_imc_memory();
				जाओ err;
			पूर्ण
		पूर्ण

		thपढ़ो_imc_pmu = pmu_ptr;
		अवरोध;
	हाल IMC_DOMAIN_TRACE:
		/* Update the pmu name */
		pmu_ptr->pmu.name = kaप्र_लिखो(GFP_KERNEL, "%s%s", s, "_imc");
		अगर (!pmu_ptr->pmu.name)
			वापस -ENOMEM;

		nr_cores = DIV_ROUND_UP(num_possible_cpus(), thपढ़ोs_per_core);
		trace_imc_refc = kसुस्मृति(nr_cores, माप(काष्ठा imc_pmu_ref),
								GFP_KERNEL);
		अगर (!trace_imc_refc)
			वापस -ENOMEM;

		trace_imc_mem_size = pmu_ptr->counter_mem_size;
		क्रम_each_online_cpu(cpu) अणु
			res = trace_imc_mem_alloc(cpu, trace_imc_mem_size);
			अगर (res) अणु
				cleanup_all_trace_imc_memory();
				जाओ err;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
err:
	वापस res;
पूर्ण

/*
 * init_imc_pmu : Setup and रेजिस्टर the IMC pmu device.
 *
 * @parent:	Device tree unit node
 * @pmu_ptr:	memory allocated क्रम this pmu
 * @pmu_idx:	Count of nest pmc रेजिस्टरed
 *
 * init_imc_pmu() setup pmu cpumask and रेजिस्टरs क्रम a cpu hotplug callback.
 * Handles failure हालs and accordingly मुक्तs memory.
 */
पूर्णांक init_imc_pmu(काष्ठा device_node *parent, काष्ठा imc_pmu *pmu_ptr, पूर्णांक pmu_idx)
अणु
	पूर्णांक ret;

	ret = imc_mem_init(pmu_ptr, parent, pmu_idx);
	अगर (ret)
		जाओ err_मुक्त_mem;

	चयन (pmu_ptr->करोमुख्य) अणु
	हाल IMC_DOMAIN_NEST:
		/*
		* Nest imc pmu need only one cpu per chip, we initialize the
		* cpumask क्रम the first nest imc pmu and use the same क्रम the
		* rest. To handle the cpuhotplug callback unरेजिस्टर, we track
		* the number of nest pmus in "nest_pmus".
		*/
		mutex_lock(&nest_init_lock);
		अगर (nest_pmus == 0) अणु
			ret = init_nest_pmu_ref();
			अगर (ret) अणु
				mutex_unlock(&nest_init_lock);
				kमुक्त(per_nest_pmu_arr);
				per_nest_pmu_arr = शून्य;
				जाओ err_मुक्त_mem;
			पूर्ण
			/* Register क्रम cpu hotplug notअगरication. */
			ret = nest_pmu_cpumask_init();
			अगर (ret) अणु
				mutex_unlock(&nest_init_lock);
				kमुक्त(nest_imc_refc);
				kमुक्त(per_nest_pmu_arr);
				per_nest_pmu_arr = शून्य;
				जाओ err_मुक्त_mem;
			पूर्ण
		पूर्ण
		nest_pmus++;
		mutex_unlock(&nest_init_lock);
		अवरोध;
	हाल IMC_DOMAIN_CORE:
		ret = core_imc_pmu_cpumask_init();
		अगर (ret) अणु
			cleanup_all_core_imc_memory();
			जाओ err_मुक्त_mem;
		पूर्ण

		अवरोध;
	हाल IMC_DOMAIN_THREAD:
		ret = thपढ़ो_imc_cpu_init();
		अगर (ret) अणु
			cleanup_all_thपढ़ो_imc_memory();
			जाओ err_मुक्त_mem;
		पूर्ण

		अवरोध;
	हाल IMC_DOMAIN_TRACE:
		ret = trace_imc_cpu_init();
		अगर (ret) अणु
			cleanup_all_trace_imc_memory();
			जाओ err_मुक्त_mem;
		पूर्ण

		अवरोध;
	शेष:
		वापस  -EINVAL;	/* Unknown करोमुख्य */
	पूर्ण

	ret = update_events_in_group(parent, pmu_ptr);
	अगर (ret)
		जाओ err_मुक्त_cpuhp_mem;

	ret = update_pmu_ops(pmu_ptr);
	अगर (ret)
		जाओ err_मुक्त_cpuhp_mem;

	ret = perf_pmu_रेजिस्टर(&pmu_ptr->pmu, pmu_ptr->pmu.name, -1);
	अगर (ret)
		जाओ err_मुक्त_cpuhp_mem;

	pr_debug("%s performance monitor hardware support registered\n",
							pmu_ptr->pmu.name);

	वापस 0;

err_मुक्त_cpuhp_mem:
	imc_common_cpuhp_mem_मुक्त(pmu_ptr);
err_मुक्त_mem:
	imc_common_mem_मुक्त(pmu_ptr);
	वापस ret;
पूर्ण
