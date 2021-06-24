<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश "uncore.h"
#समावेश "uncore_discovery.h"

अटल bool uncore_no_discover;
module_param(uncore_no_discover, bool, 0);
MODULE_PARM_DESC(uncore_no_discover, "Don't enable the Intel uncore PerfMon discovery mechanism "
				     "(default: enable the discovery mechanism).");
काष्ठा पूर्णांकel_uncore_type *empty_uncore[] = अणु शून्य, पूर्ण;
काष्ठा पूर्णांकel_uncore_type **uncore_msr_uncores = empty_uncore;
काष्ठा पूर्णांकel_uncore_type **uncore_pci_uncores = empty_uncore;
काष्ठा पूर्णांकel_uncore_type **uncore_mmio_uncores = empty_uncore;

अटल bool pcidrv_रेजिस्टरed;
काष्ठा pci_driver *uncore_pci_driver;
/* The PCI driver क्रम the device which the uncore करोesn't own. */
काष्ठा pci_driver *uncore_pci_sub_driver;
/* pci bus to socket mapping */
DEFINE_RAW_SPINLOCK(pci2phy_map_lock);
काष्ठा list_head pci2phy_map_head = LIST_HEAD_INIT(pci2phy_map_head);
काष्ठा pci_extra_dev *uncore_extra_pci_dev;
पूर्णांक __uncore_max_dies;

/* mask of cpus that collect uncore events */
अटल cpumask_t uncore_cpu_mask;

/* स्थिरraपूर्णांक क्रम the fixed counter */
अटल काष्ठा event_स्थिरraपूर्णांक uncore_स्थिरraपूर्णांक_fixed =
	EVENT_CONSTRAINT(~0ULL, 1 << UNCORE_PMC_IDX_FIXED, ~0ULL);
काष्ठा event_स्थिरraपूर्णांक uncore_स्थिरraपूर्णांक_empty =
	EVENT_CONSTRAINT(0, 0, 0);

MODULE_LICENSE("GPL");

पूर्णांक uncore_pcibus_to_dieid(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci2phy_map *map;
	पूर्णांक die_id = -1;

	raw_spin_lock(&pci2phy_map_lock);
	list_क्रम_each_entry(map, &pci2phy_map_head, list) अणु
		अगर (map->segment == pci_करोमुख्य_nr(bus)) अणु
			die_id = map->pbus_to_dieid[bus->number];
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock(&pci2phy_map_lock);

	वापस die_id;
पूर्ण

पूर्णांक uncore_die_to_segment(पूर्णांक die)
अणु
	काष्ठा pci_bus *bus = शून्य;

	/* Find first pci bus which attributes to specअगरied die. */
	जबतक ((bus = pci_find_next_bus(bus)) &&
	       (die != uncore_pcibus_to_dieid(bus)))
		;

	वापस bus ? pci_करोमुख्य_nr(bus) : -EINVAL;
पूर्ण

अटल व्योम uncore_मुक्त_pcibus_map(व्योम)
अणु
	काष्ठा pci2phy_map *map, *पंचांगp;

	list_क्रम_each_entry_safe(map, पंचांगp, &pci2phy_map_head, list) अणु
		list_del(&map->list);
		kमुक्त(map);
	पूर्ण
पूर्ण

काष्ठा pci2phy_map *__find_pci2phy_map(पूर्णांक segment)
अणु
	काष्ठा pci2phy_map *map, *alloc = शून्य;
	पूर्णांक i;

	lockdep_निश्चित_held(&pci2phy_map_lock);

lookup:
	list_क्रम_each_entry(map, &pci2phy_map_head, list) अणु
		अगर (map->segment == segment)
			जाओ end;
	पूर्ण

	अगर (!alloc) अणु
		raw_spin_unlock(&pci2phy_map_lock);
		alloc = kदो_स्मृति(माप(काष्ठा pci2phy_map), GFP_KERNEL);
		raw_spin_lock(&pci2phy_map_lock);

		अगर (!alloc)
			वापस शून्य;

		जाओ lookup;
	पूर्ण

	map = alloc;
	alloc = शून्य;
	map->segment = segment;
	क्रम (i = 0; i < 256; i++)
		map->pbus_to_dieid[i] = -1;
	list_add_tail(&map->list, &pci2phy_map_head);

end:
	kमुक्त(alloc);
	वापस map;
पूर्ण

sमाप_प्रकार uncore_event_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uncore_event_desc *event =
		container_of(attr, काष्ठा uncore_event_desc, attr);
	वापस प्र_लिखो(buf, "%s", event->config);
पूर्ण

काष्ठा पूर्णांकel_uncore_box *uncore_pmu_to_box(काष्ठा पूर्णांकel_uncore_pmu *pmu, पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक dieid = topology_logical_die_id(cpu);

	/*
	 * The अचिन्हित check also catches the '-1' वापस value क्रम non
	 * existent mappings in the topology map.
	 */
	वापस dieid < uncore_max_dies() ? pmu->boxes[dieid] : शून्य;
पूर्ण

u64 uncore_msr_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	u64 count;

	rdmsrl(event->hw.event_base, count);

	वापस count;
पूर्ण

व्योम uncore_mmio_निकास_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->io_addr)
		iounmap(box->io_addr);
पूर्ण

u64 uncore_mmio_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box,
			     काष्ठा perf_event *event)
अणु
	अगर (!box->io_addr)
		वापस 0;

	अगर (!uncore_mmio_is_valid_offset(box, event->hw.event_base))
		वापस 0;

	वापस पढ़ोq(box->io_addr + event->hw.event_base);
पूर्ण

/*
 * generic get स्थिरraपूर्णांक function क्रम shared match/mask रेजिस्टरs.
 */
काष्ठा event_स्थिरraपूर्णांक *
uncore_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	अचिन्हित दीर्घ flags;
	bool ok = false;

	/*
	 * reg->alloc can be set due to existing state, so क्रम fake box we
	 * need to ignore this, otherwise we might fail to allocate proper
	 * fake state क्रम this extra reg स्थिरraपूर्णांक.
	 */
	अगर (reg1->idx == EXTRA_REG_NONE ||
	    (!uncore_box_is_fake(box) && reg1->alloc))
		वापस शून्य;

	er = &box->shared_regs[reg1->idx];
	raw_spin_lock_irqsave(&er->lock, flags);
	अगर (!atomic_पढ़ो(&er->ref) ||
	    (er->config1 == reg1->config && er->config2 == reg2->config)) अणु
		atomic_inc(&er->ref);
		er->config1 = reg1->config;
		er->config2 = reg2->config;
		ok = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&er->lock, flags);

	अगर (ok) अणु
		अगर (!uncore_box_is_fake(box))
			reg1->alloc = 1;
		वापस शून्य;
	पूर्ण

	वापस &uncore_स्थिरraपूर्णांक_empty;
पूर्ण

व्योम uncore_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;

	/*
	 * Only put स्थिरraपूर्णांक अगर extra reg was actually allocated. Also
	 * takes care of event which करो not use an extra shared reg.
	 *
	 * Also, अगर this is a fake box we shouldn't touch any event state
	 * (reg->alloc) and we करोn't care about leaving inconsistent box
	 * state either since it will be thrown out.
	 */
	अगर (uncore_box_is_fake(box) || !reg1->alloc)
		वापस;

	er = &box->shared_regs[reg1->idx];
	atomic_dec(&er->ref);
	reg1->alloc = 0;
पूर्ण

u64 uncore_shared_reg_config(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	अचिन्हित दीर्घ flags;
	u64 config;

	er = &box->shared_regs[idx];

	raw_spin_lock_irqsave(&er->lock, flags);
	config = er->config;
	raw_spin_unlock_irqrestore(&er->lock, flags);

	वापस config;
पूर्ण

अटल व्योम uncore_assign_hw_event(काष्ठा पूर्णांकel_uncore_box *box,
				   काष्ठा perf_event *event, पूर्णांक idx)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	hwc->idx = idx;
	hwc->last_tag = ++box->tags[idx];

	अगर (uncore_pmc_fixed(hwc->idx)) अणु
		hwc->event_base = uncore_fixed_ctr(box);
		hwc->config_base = uncore_fixed_ctl(box);
		वापस;
	पूर्ण

	hwc->config_base = uncore_event_ctl(box, hwc->idx);
	hwc->event_base  = uncore_perf_ctr(box, hwc->idx);
पूर्ण

व्योम uncore_perf_event_update(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	u64 prev_count, new_count, delta;
	पूर्णांक shअगरt;

	अगर (uncore_pmc_मुक्तrunning(event->hw.idx))
		shअगरt = 64 - uncore_मुक्तrunning_bits(box, event);
	अन्यथा अगर (uncore_pmc_fixed(event->hw.idx))
		shअगरt = 64 - uncore_fixed_ctr_bits(box);
	अन्यथा
		shअगरt = 64 - uncore_perf_ctr_bits(box);

	/* the hrसमयr might modअगरy the previous event value */
again:
	prev_count = local64_पढ़ो(&event->hw.prev_count);
	new_count = uncore_पढ़ो_counter(box, event);
	अगर (local64_xchg(&event->hw.prev_count, new_count) != prev_count)
		जाओ again;

	delta = (new_count << shअगरt) - (prev_count << shअगरt);
	delta >>= shअगरt;

	local64_add(delta, &event->count);
पूर्ण

/*
 * The overflow पूर्णांकerrupt is unavailable क्रम SandyBridge-EP, is broken
 * क्रम SandyBridge. So we use hrसमयr to periodically poll the counter
 * to aव्योम overflow.
 */
अटल क्रमागत hrसमयr_restart uncore_pmu_hrसमयr(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा पूर्णांकel_uncore_box *box;
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ flags;
	पूर्णांक bit;

	box = container_of(hrसमयr, काष्ठा पूर्णांकel_uncore_box, hrसमयr);
	अगर (!box->n_active || box->cpu != smp_processor_id())
		वापस HRTIMER_NORESTART;
	/*
	 * disable local पूर्णांकerrupt to prevent uncore_pmu_event_start/stop
	 * to पूर्णांकerrupt the update process
	 */
	local_irq_save(flags);

	/*
	 * handle boxes with an active event list as opposed to active
	 * counters
	 */
	list_क्रम_each_entry(event, &box->active_list, active_entry) अणु
		uncore_perf_event_update(box, event);
	पूर्ण

	क्रम_each_set_bit(bit, box->active_mask, UNCORE_PMC_IDX_MAX)
		uncore_perf_event_update(box, box->events[bit]);

	local_irq_restore(flags);

	hrसमयr_क्रमward_now(hrसमयr, ns_to_kसमय(box->hrसमयr_duration));
	वापस HRTIMER_RESTART;
पूर्ण

व्योम uncore_pmu_start_hrसमयr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	hrसमयr_start(&box->hrसमयr, ns_to_kसमय(box->hrसमयr_duration),
		      HRTIMER_MODE_REL_PINNED);
पूर्ण

व्योम uncore_pmu_cancel_hrसमयr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	hrसमयr_cancel(&box->hrसमयr);
पूर्ण

अटल व्योम uncore_pmu_init_hrसमयr(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	hrसमयr_init(&box->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	box->hrसमयr.function = uncore_pmu_hrसमयr;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_box *uncore_alloc_box(काष्ठा पूर्णांकel_uncore_type *type,
						 पूर्णांक node)
अणु
	पूर्णांक i, size, numshared = type->num_shared_regs ;
	काष्ठा पूर्णांकel_uncore_box *box;

	size = माप(*box) + numshared * माप(काष्ठा पूर्णांकel_uncore_extra_reg);

	box = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!box)
		वापस शून्य;

	क्रम (i = 0; i < numshared; i++)
		raw_spin_lock_init(&box->shared_regs[i].lock);

	uncore_pmu_init_hrसमयr(box);
	box->cpu = -1;
	box->dieid = -1;

	/* set शेष hrसमयr समयout */
	box->hrसमयr_duration = UNCORE_PMU_HRTIMER_INTERVAL;

	INIT_LIST_HEAD(&box->active_list);

	वापस box;
पूर्ण

/*
 * Using uncore_pmu_event_init pmu event_init callback
 * as a detection poपूर्णांक क्रम uncore events.
 */
अटल पूर्णांक uncore_pmu_event_init(काष्ठा perf_event *event);

अटल bool is_box_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस &box->pmu->pmu == event->pmu;
पूर्ण

अटल पूर्णांक
uncore_collect_events(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *leader,
		      bool करोgrp)
अणु
	काष्ठा perf_event *event;
	पूर्णांक n, max_count;

	max_count = box->pmu->type->num_counters;
	अगर (box->pmu->type->fixed_ctl)
		max_count++;

	अगर (box->n_events >= max_count)
		वापस -EINVAL;

	n = box->n_events;

	अगर (is_box_event(box, leader)) अणु
		box->event_list[n] = leader;
		n++;
	पूर्ण

	अगर (!करोgrp)
		वापस n;

	क्रम_each_sibling_event(event, leader) अणु
		अगर (!is_box_event(box, event) ||
		    event->state <= PERF_EVENT_STATE_OFF)
			जारी;

		अगर (n >= max_count)
			वापस -EINVAL;

		box->event_list[n] = event;
		n++;
	पूर्ण
	वापस n;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
uncore_get_event_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (type->ops->get_स्थिरraपूर्णांक) अणु
		c = type->ops->get_स्थिरraपूर्णांक(box, event);
		अगर (c)
			वापस c;
	पूर्ण

	अगर (event->attr.config == UNCORE_FIXED_EVENT)
		वापस &uncore_स्थिरraपूर्णांक_fixed;

	अगर (type->स्थिरraपूर्णांकs) अणु
		क्रम_each_event_स्थिरraपूर्णांक(c, type->स्थिरraपूर्णांकs) अणु
			अगर ((event->hw.config & c->cmask) == c->code)
				वापस c;
		पूर्ण
	पूर्ण

	वापस &type->unस्थिरraपूर्णांकed;
पूर्ण

अटल व्योम uncore_put_event_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box,
					काष्ठा perf_event *event)
अणु
	अगर (box->pmu->type->ops->put_स्थिरraपूर्णांक)
		box->pmu->type->ops->put_स्थिरraपूर्णांक(box, event);
पूर्ण

अटल पूर्णांक uncore_assign_events(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक assign[], पूर्णांक n)
अणु
	अचिन्हित दीर्घ used_mask[BITS_TO_LONGS(UNCORE_PMC_IDX_MAX)];
	काष्ठा event_स्थिरraपूर्णांक *c;
	पूर्णांक i, wmin, wmax, ret = 0;
	काष्ठा hw_perf_event *hwc;

	biपंचांगap_zero(used_mask, UNCORE_PMC_IDX_MAX);

	क्रम (i = 0, wmin = UNCORE_PMC_IDX_MAX, wmax = 0; i < n; i++) अणु
		c = uncore_get_event_स्थिरraपूर्णांक(box, box->event_list[i]);
		box->event_स्थिरraपूर्णांक[i] = c;
		wmin = min(wmin, c->weight);
		wmax = max(wmax, c->weight);
	पूर्ण

	/* fastpath, try to reuse previous रेजिस्टर */
	क्रम (i = 0; i < n; i++) अणु
		hwc = &box->event_list[i]->hw;
		c = box->event_स्थिरraपूर्णांक[i];

		/* never asचिन्हित */
		अगर (hwc->idx == -1)
			अवरोध;

		/* स्थिरraपूर्णांक still honored */
		अगर (!test_bit(hwc->idx, c->idxmsk))
			अवरोध;

		/* not alपढ़ोy used */
		अगर (test_bit(hwc->idx, used_mask))
			अवरोध;

		__set_bit(hwc->idx, used_mask);
		अगर (assign)
			assign[i] = hwc->idx;
	पूर्ण
	/* slow path */
	अगर (i != n)
		ret = perf_assign_events(box->event_स्थिरraपूर्णांक, n,
					 wmin, wmax, n, assign);

	अगर (!assign || ret) अणु
		क्रम (i = 0; i < n; i++)
			uncore_put_event_स्थिरraपूर्णांक(box, box->event_list[i]);
	पूर्ण
	वापस ret ? -EINVAL : 0;
पूर्ण

व्योम uncore_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = uncore_event_to_box(event);
	पूर्णांक idx = event->hw.idx;

	अगर (WARN_ON_ONCE(idx == -1 || idx >= UNCORE_PMC_IDX_MAX))
		वापस;

	/*
	 * Free running counter is पढ़ो-only and always active.
	 * Use the current counter value as start poपूर्णांक.
	 * There is no overflow पूर्णांकerrupt क्रम मुक्त running counter.
	 * Use hrसमयr to periodically poll the counter to aव्योम overflow.
	 */
	अगर (uncore_pmc_मुक्तrunning(event->hw.idx)) अणु
		list_add_tail(&event->active_entry, &box->active_list);
		local64_set(&event->hw.prev_count,
			    uncore_पढ़ो_counter(box, event));
		अगर (box->n_active++ == 0)
			uncore_pmu_start_hrसमयr(box);
		वापस;
	पूर्ण

	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	event->hw.state = 0;
	box->events[idx] = event;
	box->n_active++;
	__set_bit(idx, box->active_mask);

	local64_set(&event->hw.prev_count, uncore_पढ़ो_counter(box, event));
	uncore_enable_event(box, event);

	अगर (box->n_active == 1)
		uncore_pmu_start_hrसमयr(box);
पूर्ण

व्योम uncore_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = uncore_event_to_box(event);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* Cannot disable मुक्त running counter which is पढ़ो-only */
	अगर (uncore_pmc_मुक्तrunning(hwc->idx)) अणु
		list_del(&event->active_entry);
		अगर (--box->n_active == 0)
			uncore_pmu_cancel_hrसमयr(box);
		uncore_perf_event_update(box, event);
		वापस;
	पूर्ण

	अगर (__test_and_clear_bit(hwc->idx, box->active_mask)) अणु
		uncore_disable_event(box, event);
		box->n_active--;
		box->events[hwc->idx] = शून्य;
		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;

		अगर (box->n_active == 0)
			uncore_pmu_cancel_hrसमयr(box);
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		/*
		 * Drain the reमुख्यing delta count out of a event
		 * that we are disabling:
		 */
		uncore_perf_event_update(box, event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

पूर्णांक uncore_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = uncore_event_to_box(event);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक assign[UNCORE_PMC_IDX_MAX];
	पूर्णांक i, n, ret;

	अगर (!box)
		वापस -ENODEV;

	/*
	 * The मुक्त funning counter is asचिन्हित in event_init().
	 * The मुक्त running counter event and मुक्त running counter
	 * are 1:1 mapped. It करोesn't need to be tracked in event_list.
	 */
	अगर (uncore_pmc_मुक्तrunning(hwc->idx)) अणु
		अगर (flags & PERF_EF_START)
			uncore_pmu_event_start(event, 0);
		वापस 0;
	पूर्ण

	ret = n = uncore_collect_events(box, event, false);
	अगर (ret < 0)
		वापस ret;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_ARCH;

	ret = uncore_assign_events(box, assign, n);
	अगर (ret)
		वापस ret;

	/* save events moving to new counters */
	क्रम (i = 0; i < box->n_events; i++) अणु
		event = box->event_list[i];
		hwc = &event->hw;

		अगर (hwc->idx == assign[i] &&
			hwc->last_tag == box->tags[assign[i]])
			जारी;
		/*
		 * Ensure we करोn't accidentally enable a stopped
		 * counter simply because we rescheduled.
		 */
		अगर (hwc->state & PERF_HES_STOPPED)
			hwc->state |= PERF_HES_ARCH;

		uncore_pmu_event_stop(event, PERF_EF_UPDATE);
	पूर्ण

	/* reprogram moved events पूर्णांकo new counters */
	क्रम (i = 0; i < n; i++) अणु
		event = box->event_list[i];
		hwc = &event->hw;

		अगर (hwc->idx != assign[i] ||
			hwc->last_tag != box->tags[assign[i]])
			uncore_assign_hw_event(box, event, assign[i]);
		अन्यथा अगर (i < box->n_events)
			जारी;

		अगर (hwc->state & PERF_HES_ARCH)
			जारी;

		uncore_pmu_event_start(event, 0);
	पूर्ण
	box->n_events = n;

	वापस 0;
पूर्ण

व्योम uncore_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = uncore_event_to_box(event);
	पूर्णांक i;

	uncore_pmu_event_stop(event, PERF_EF_UPDATE);

	/*
	 * The event क्रम मुक्त running counter is not tracked by event_list.
	 * It करोesn't need to क्रमce event->hw.idx = -1 to reassign the counter.
	 * Because the event and the मुक्त running counter are 1:1 mapped.
	 */
	अगर (uncore_pmc_मुक्तrunning(event->hw.idx))
		वापस;

	क्रम (i = 0; i < box->n_events; i++) अणु
		अगर (event == box->event_list[i]) अणु
			uncore_put_event_स्थिरraपूर्णांक(box, event);

			क्रम (++i; i < box->n_events; i++)
				box->event_list[i - 1] = box->event_list[i];

			--box->n_events;
			अवरोध;
		पूर्ण
	पूर्ण

	event->hw.idx = -1;
	event->hw.last_tag = ~0ULL;
पूर्ण

व्योम uncore_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = uncore_event_to_box(event);
	uncore_perf_event_update(box, event);
पूर्ण

/*
 * validation ensures the group can be loaded onto the
 * PMU अगर it was the only group available.
 */
अटल पूर्णांक uncore_validate_group(काष्ठा पूर्णांकel_uncore_pmu *pmu,
				काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा पूर्णांकel_uncore_box *fake_box;
	पूर्णांक ret = -EINVAL, n;

	/* The मुक्त running counter is always active. */
	अगर (uncore_pmc_मुक्तrunning(event->hw.idx))
		वापस 0;

	fake_box = uncore_alloc_box(pmu->type, NUMA_NO_NODE);
	अगर (!fake_box)
		वापस -ENOMEM;

	fake_box->pmu = pmu;
	/*
	 * the event is not yet connected with its
	 * siblings thereक्रमe we must first collect
	 * existing siblings, then add the new event
	 * beक्रमe we can simulate the scheduling
	 */
	n = uncore_collect_events(fake_box, leader, true);
	अगर (n < 0)
		जाओ out;

	fake_box->n_events = n;
	n = uncore_collect_events(fake_box, event, false);
	अगर (n < 0)
		जाओ out;

	fake_box->n_events = n;

	ret = uncore_assign_events(fake_box, शून्य, n);
out:
	kमुक्त(fake_box);
	वापस ret;
पूर्ण

अटल पूर्णांक uncore_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा पूर्णांकel_uncore_box *box;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक ret;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	pmu = uncore_event_to_pmu(event);
	/* no device found क्रम this pmu */
	अगर (pmu->func_id < 0)
		वापस -ENOENT;

	/* Sampling not supported yet */
	अगर (hwc->sample_period)
		वापस -EINVAL;

	/*
	 * Place all uncore events क्रम a particular physical package
	 * onto a single cpu
	 */
	अगर (event->cpu < 0)
		वापस -EINVAL;
	box = uncore_pmu_to_box(pmu, event->cpu);
	अगर (!box || box->cpu < 0)
		वापस -EINVAL;
	event->cpu = box->cpu;
	event->pmu_निजी = box;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	event->hw.idx = -1;
	event->hw.last_tag = ~0ULL;
	event->hw.extra_reg.idx = EXTRA_REG_NONE;
	event->hw.branch_reg.idx = EXTRA_REG_NONE;

	अगर (event->attr.config == UNCORE_FIXED_EVENT) अणु
		/* no fixed counter */
		अगर (!pmu->type->fixed_ctl)
			वापस -EINVAL;
		/*
		 * अगर there is only one fixed counter, only the first pmu
		 * can access the fixed counter
		 */
		अगर (pmu->type->single_fixed && pmu->pmu_idx > 0)
			वापस -EINVAL;

		/* fixed counters have event field hardcoded to zero */
		hwc->config = 0ULL;
	पूर्ण अन्यथा अगर (is_मुक्तrunning_event(event)) अणु
		hwc->config = event->attr.config;
		अगर (!check_valid_मुक्तrunning_event(box, event))
			वापस -EINVAL;
		event->hw.idx = UNCORE_PMC_IDX_FREERUNNING;
		/*
		 * The मुक्त running counter event and मुक्त running counter
		 * are always 1:1 mapped.
		 * The मुक्त running counter is always active.
		 * Assign the मुक्त running counter here.
		 */
		event->hw.event_base = uncore_मुक्तrunning_counter(box, event);
	पूर्ण अन्यथा अणु
		hwc->config = event->attr.config &
			      (pmu->type->event_mask | ((u64)pmu->type->event_mask_ext << 32));
		अगर (pmu->type->ops->hw_config) अणु
			ret = pmu->type->ops->hw_config(box, event);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (event->group_leader != event)
		ret = uncore_validate_group(pmu, event);
	अन्यथा
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम uncore_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *uncore_pmu;
	काष्ठा पूर्णांकel_uncore_box *box;

	uncore_pmu = container_of(pmu, काष्ठा पूर्णांकel_uncore_pmu, pmu);
	अगर (!uncore_pmu)
		वापस;

	box = uncore_pmu_to_box(uncore_pmu, smp_processor_id());
	अगर (!box)
		वापस;

	अगर (uncore_pmu->type->ops->enable_box)
		uncore_pmu->type->ops->enable_box(box);
पूर्ण

अटल व्योम uncore_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *uncore_pmu;
	काष्ठा पूर्णांकel_uncore_box *box;

	uncore_pmu = container_of(pmu, काष्ठा पूर्णांकel_uncore_pmu, pmu);
	अगर (!uncore_pmu)
		वापस;

	box = uncore_pmu_to_box(uncore_pmu, smp_processor_id());
	अगर (!box)
		वापस;

	अगर (uncore_pmu->type->ops->disable_box)
		uncore_pmu->type->ops->disable_box(box);
पूर्ण

अटल sमाप_प्रकार uncore_get_attr_cpumask(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &uncore_cpu_mask);
पूर्ण

अटल DEVICE_ATTR(cpumask, S_IRUGO, uncore_get_attr_cpumask, शून्य);

अटल काष्ठा attribute *uncore_pmu_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group uncore_pmu_attr_group = अणु
	.attrs = uncore_pmu_attrs,
पूर्ण;

अटल व्योम uncore_get_pmu_name(काष्ठा पूर्णांकel_uncore_pmu *pmu)
अणु
	काष्ठा पूर्णांकel_uncore_type *type = pmu->type;

	/*
	 * No uncore block name in discovery table.
	 * Use uncore_type_&typeid_&boxid as name.
	 */
	अगर (!type->name) अणु
		अगर (type->num_boxes == 1)
			प्र_लिखो(pmu->name, "uncore_type_%u", type->type_id);
		अन्यथा अणु
			प्र_लिखो(pmu->name, "uncore_type_%u_%d",
				type->type_id, type->box_ids[pmu->pmu_idx]);
		पूर्ण
		वापस;
	पूर्ण

	अगर (type->num_boxes == 1) अणु
		अगर (म_माप(type->name) > 0)
			प्र_लिखो(pmu->name, "uncore_%s", type->name);
		अन्यथा
			प्र_लिखो(pmu->name, "uncore");
	पूर्ण अन्यथा
		प्र_लिखो(pmu->name, "uncore_%s_%d", type->name, pmu->pmu_idx);

पूर्ण

अटल पूर्णांक uncore_pmu_रेजिस्टर(काष्ठा पूर्णांकel_uncore_pmu *pmu)
अणु
	पूर्णांक ret;

	अगर (!pmu->type->pmu) अणु
		pmu->pmu = (काष्ठा pmu) अणु
			.attr_groups	= pmu->type->attr_groups,
			.task_ctx_nr	= perf_invalid_context,
			.pmu_enable	= uncore_pmu_enable,
			.pmu_disable	= uncore_pmu_disable,
			.event_init	= uncore_pmu_event_init,
			.add		= uncore_pmu_event_add,
			.del		= uncore_pmu_event_del,
			.start		= uncore_pmu_event_start,
			.stop		= uncore_pmu_event_stop,
			.पढ़ो		= uncore_pmu_event_पढ़ो,
			.module		= THIS_MODULE,
			.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
			.attr_update	= pmu->type->attr_update,
		पूर्ण;
	पूर्ण अन्यथा अणु
		pmu->pmu = *pmu->type->pmu;
		pmu->pmu.attr_groups = pmu->type->attr_groups;
		pmu->pmu.attr_update = pmu->type->attr_update;
	पूर्ण

	uncore_get_pmu_name(pmu);

	ret = perf_pmu_रेजिस्टर(&pmu->pmu, pmu->name, -1);
	अगर (!ret)
		pmu->रेजिस्टरed = true;
	वापस ret;
पूर्ण

अटल व्योम uncore_pmu_unरेजिस्टर(काष्ठा पूर्णांकel_uncore_pmu *pmu)
अणु
	अगर (!pmu->रेजिस्टरed)
		वापस;
	perf_pmu_unरेजिस्टर(&pmu->pmu);
	pmu->रेजिस्टरed = false;
पूर्ण

अटल व्योम uncore_मुक्त_boxes(काष्ठा पूर्णांकel_uncore_pmu *pmu)
अणु
	पूर्णांक die;

	क्रम (die = 0; die < uncore_max_dies(); die++)
		kमुक्त(pmu->boxes[die]);
	kमुक्त(pmu->boxes);
पूर्ण

अटल व्योम uncore_type_निकास(काष्ठा पूर्णांकel_uncore_type *type)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = type->pmus;
	पूर्णांक i;

	अगर (type->cleanup_mapping)
		type->cleanup_mapping(type);

	अगर (pmu) अणु
		क्रम (i = 0; i < type->num_boxes; i++, pmu++) अणु
			uncore_pmu_unरेजिस्टर(pmu);
			uncore_मुक्त_boxes(pmu);
		पूर्ण
		kमुक्त(type->pmus);
		type->pmus = शून्य;
	पूर्ण
	अगर (type->box_ids) अणु
		kमुक्त(type->box_ids);
		type->box_ids = शून्य;
	पूर्ण
	kमुक्त(type->events_group);
	type->events_group = शून्य;
पूर्ण

अटल व्योम uncore_types_निकास(काष्ठा पूर्णांकel_uncore_type **types)
अणु
	क्रम (; *types; types++)
		uncore_type_निकास(*types);
पूर्ण

अटल पूर्णांक __init uncore_type_init(काष्ठा पूर्णांकel_uncore_type *type, bool setid)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmus;
	माप_प्रकार size;
	पूर्णांक i, j;

	pmus = kसुस्मृति(type->num_boxes, माप(*pmus), GFP_KERNEL);
	अगर (!pmus)
		वापस -ENOMEM;

	size = uncore_max_dies() * माप(काष्ठा पूर्णांकel_uncore_box *);

	क्रम (i = 0; i < type->num_boxes; i++) अणु
		pmus[i].func_id	= setid ? i : -1;
		pmus[i].pmu_idx	= i;
		pmus[i].type	= type;
		pmus[i].boxes	= kzalloc(size, GFP_KERNEL);
		अगर (!pmus[i].boxes)
			जाओ err;
	पूर्ण

	type->pmus = pmus;
	type->unस्थिरraपूर्णांकed = (काष्ठा event_स्थिरraपूर्णांक)
		__EVENT_CONSTRAINT(0, (1ULL << type->num_counters) - 1,
				0, type->num_counters, 0, 0);

	अगर (type->event_descs) अणु
		काष्ठा अणु
			काष्ठा attribute_group group;
			काष्ठा attribute *attrs[];
		पूर्ण *attr_group;
		क्रम (i = 0; type->event_descs[i].attr.attr.name; i++);

		attr_group = kzalloc(काष्ठा_size(attr_group, attrs, i + 1),
								GFP_KERNEL);
		अगर (!attr_group)
			जाओ err;

		attr_group->group.name = "events";
		attr_group->group.attrs = attr_group->attrs;

		क्रम (j = 0; j < i; j++)
			attr_group->attrs[j] = &type->event_descs[j].attr.attr;

		type->events_group = &attr_group->group;
	पूर्ण

	type->pmu_group = &uncore_pmu_attr_group;

	अगर (type->set_mapping)
		type->set_mapping(type);

	वापस 0;

err:
	क्रम (i = 0; i < type->num_boxes; i++)
		kमुक्त(pmus[i].boxes);
	kमुक्त(pmus);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init
uncore_types_init(काष्ठा पूर्णांकel_uncore_type **types, bool setid)
अणु
	पूर्णांक ret;

	क्रम (; *types; types++) अणु
		ret = uncore_type_init(*types, setid);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Get the die inक्रमmation of a PCI device.
 * @pdev: The PCI device.
 * @die: The die id which the device maps to.
 */
अटल पूर्णांक uncore_pci_get_dev_die_info(काष्ठा pci_dev *pdev, पूर्णांक *die)
अणु
	*die = uncore_pcibus_to_dieid(pdev->bus);
	अगर (*die < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_pmu *
uncore_pci_find_dev_pmu_from_types(काष्ठा pci_dev *pdev)
अणु
	काष्ठा पूर्णांकel_uncore_type **types = uncore_pci_uncores;
	काष्ठा पूर्णांकel_uncore_type *type;
	u64 box_ctl;
	पूर्णांक i, die;

	क्रम (; *types; types++) अणु
		type = *types;
		क्रम (die = 0; die < __uncore_max_dies; die++) अणु
			क्रम (i = 0; i < type->num_boxes; i++) अणु
				अगर (!type->box_ctls[die])
					जारी;
				box_ctl = type->box_ctls[die] + type->pci_offsets[i];
				अगर (pdev->devfn == UNCORE_DISCOVERY_PCI_DEVFN(box_ctl) &&
				    pdev->bus->number == UNCORE_DISCOVERY_PCI_BUS(box_ctl) &&
				    pci_करोमुख्य_nr(pdev->bus) == UNCORE_DISCOVERY_PCI_DOMAIN(box_ctl))
					वापस &type->pmus[i];
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Find the PMU of a PCI device.
 * @pdev: The PCI device.
 * @ids: The ID table of the available PCI devices with a PMU.
 *       If शून्य, search the whole uncore_pci_uncores.
 */
अटल काष्ठा पूर्णांकel_uncore_pmu *
uncore_pci_find_dev_pmu(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ids)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = शून्य;
	काष्ठा पूर्णांकel_uncore_type *type;
	kernel_uदीर्घ_t data;
	अचिन्हित पूर्णांक devfn;

	अगर (!ids)
		वापस uncore_pci_find_dev_pmu_from_types(pdev);

	जबतक (ids && ids->venकरोr) अणु
		अगर ((ids->venकरोr == pdev->venकरोr) &&
		    (ids->device == pdev->device)) अणु
			data = ids->driver_data;
			devfn = PCI_DEVFN(UNCORE_PCI_DEV_DEV(data),
					  UNCORE_PCI_DEV_FUNC(data));
			अगर (devfn == pdev->devfn) अणु
				type = uncore_pci_uncores[UNCORE_PCI_DEV_TYPE(data)];
				pmu = &type->pmus[UNCORE_PCI_DEV_IDX(data)];
				अवरोध;
			पूर्ण
		पूर्ण
		ids++;
	पूर्ण
	वापस pmu;
पूर्ण

/*
 * Register the PMU क्रम a PCI device
 * @pdev: The PCI device.
 * @type: The corresponding PMU type of the device.
 * @pmu: The corresponding PMU of the device.
 * @die: The die id which the device maps to.
 */
अटल पूर्णांक uncore_pci_pmu_रेजिस्टर(काष्ठा pci_dev *pdev,
				   काष्ठा पूर्णांकel_uncore_type *type,
				   काष्ठा पूर्णांकel_uncore_pmu *pmu,
				   पूर्णांक die)
अणु
	काष्ठा पूर्णांकel_uncore_box *box;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(pmu->boxes[die] != शून्य))
		वापस -EINVAL;

	box = uncore_alloc_box(type, NUMA_NO_NODE);
	अगर (!box)
		वापस -ENOMEM;

	अगर (pmu->func_id < 0)
		pmu->func_id = pdev->devfn;
	अन्यथा
		WARN_ON_ONCE(pmu->func_id != pdev->devfn);

	atomic_inc(&box->refcnt);
	box->dieid = die;
	box->pci_dev = pdev;
	box->pmu = pmu;
	uncore_box_init(box);

	pmu->boxes[die] = box;
	अगर (atomic_inc_वापस(&pmu->activeboxes) > 1)
		वापस 0;

	/* First active box रेजिस्टरs the pmu */
	ret = uncore_pmu_रेजिस्टर(pmu);
	अगर (ret) अणु
		pmu->boxes[die] = शून्य;
		uncore_box_निकास(box);
		kमुक्त(box);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * add a pci uncore device
 */
अटल पूर्णांक uncore_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu = शून्य;
	पूर्णांक die, ret;

	ret = uncore_pci_get_dev_die_info(pdev, &die);
	अगर (ret)
		वापस ret;

	अगर (UNCORE_PCI_DEV_TYPE(id->driver_data) == UNCORE_EXTRA_PCI_DEV) अणु
		पूर्णांक idx = UNCORE_PCI_DEV_IDX(id->driver_data);

		uncore_extra_pci_dev[die].dev[idx] = pdev;
		pci_set_drvdata(pdev, शून्य);
		वापस 0;
	पूर्ण

	type = uncore_pci_uncores[UNCORE_PCI_DEV_TYPE(id->driver_data)];

	/*
	 * Some platक्रमms, e.g.  Knights Landing, use a common PCI device ID
	 * क्रम multiple instances of an uncore PMU device type. We should check
	 * PCI slot and func to indicate the uncore box.
	 */
	अगर (id->driver_data & ~0xffff) अणु
		काष्ठा pci_driver *pci_drv = pdev->driver;

		pmu = uncore_pci_find_dev_pmu(pdev, pci_drv->id_table);
		अगर (pmu == शून्य)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		/*
		 * क्रम perक्रमmance monitoring unit with multiple boxes,
		 * each box has a dअगरferent function id.
		 */
		pmu = &type->pmus[UNCORE_PCI_DEV_IDX(id->driver_data)];
	पूर्ण

	ret = uncore_pci_pmu_रेजिस्टर(pdev, type, pmu, die);

	pci_set_drvdata(pdev, pmu->boxes[die]);

	वापस ret;
पूर्ण

/*
 * Unरेजिस्टर the PMU of a PCI device
 * @pmu: The corresponding PMU is unरेजिस्टरed.
 * @die: The die id which the device maps to.
 */
अटल व्योम uncore_pci_pmu_unरेजिस्टर(काष्ठा पूर्णांकel_uncore_pmu *pmu, पूर्णांक die)
अणु
	काष्ठा पूर्णांकel_uncore_box *box = pmu->boxes[die];

	pmu->boxes[die] = शून्य;
	अगर (atomic_dec_वापस(&pmu->activeboxes) == 0)
		uncore_pmu_unरेजिस्टर(pmu);
	uncore_box_निकास(box);
	kमुक्त(box);
पूर्ण

अटल व्योम uncore_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा पूर्णांकel_uncore_box *box;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	पूर्णांक i, die;

	अगर (uncore_pci_get_dev_die_info(pdev, &die))
		वापस;

	box = pci_get_drvdata(pdev);
	अगर (!box) अणु
		क्रम (i = 0; i < UNCORE_EXTRA_PCI_DEV_MAX; i++) अणु
			अगर (uncore_extra_pci_dev[die].dev[i] == pdev) अणु
				uncore_extra_pci_dev[die].dev[i] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		WARN_ON_ONCE(i >= UNCORE_EXTRA_PCI_DEV_MAX);
		वापस;
	पूर्ण

	pmu = box->pmu;

	pci_set_drvdata(pdev, शून्य);

	uncore_pci_pmu_unरेजिस्टर(pmu, die);
पूर्ण

अटल पूर्णांक uncore_bus_notअगरy(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data,
			     स्थिर काष्ठा pci_device_id *ids)
अणु
	काष्ठा device *dev = data;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	पूर्णांक die;

	/* Unरेजिस्टर the PMU when the device is going to be deleted. */
	अगर (action != BUS_NOTIFY_DEL_DEVICE)
		वापस NOTIFY_DONE;

	pmu = uncore_pci_find_dev_pmu(pdev, ids);
	अगर (!pmu)
		वापस NOTIFY_DONE;

	अगर (uncore_pci_get_dev_die_info(pdev, &die))
		वापस NOTIFY_DONE;

	uncore_pci_pmu_unरेजिस्टर(pmu, die);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक uncore_pci_sub_bus_notअगरy(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	वापस uncore_bus_notअगरy(nb, action, data,
				 uncore_pci_sub_driver->id_table);
पूर्ण

अटल काष्ठा notअगरier_block uncore_pci_sub_notअगरier = अणु
	.notअगरier_call = uncore_pci_sub_bus_notअगरy,
पूर्ण;

अटल व्योम uncore_pci_sub_driver_init(व्योम)
अणु
	स्थिर काष्ठा pci_device_id *ids = uncore_pci_sub_driver->id_table;
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा pci_dev *pci_sub_dev;
	bool notअगरy = false;
	अचिन्हित पूर्णांक devfn;
	पूर्णांक die;

	जबतक (ids && ids->venकरोr) अणु
		pci_sub_dev = शून्य;
		type = uncore_pci_uncores[UNCORE_PCI_DEV_TYPE(ids->driver_data)];
		/*
		 * Search the available device, and रेजिस्टर the
		 * corresponding PMU.
		 */
		जबतक ((pci_sub_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
						     ids->device, pci_sub_dev))) अणु
			devfn = PCI_DEVFN(UNCORE_PCI_DEV_DEV(ids->driver_data),
					  UNCORE_PCI_DEV_FUNC(ids->driver_data));
			अगर (devfn != pci_sub_dev->devfn)
				जारी;

			pmu = &type->pmus[UNCORE_PCI_DEV_IDX(ids->driver_data)];
			अगर (!pmu)
				जारी;

			अगर (uncore_pci_get_dev_die_info(pci_sub_dev, &die))
				जारी;

			अगर (!uncore_pci_pmu_रेजिस्टर(pci_sub_dev, type, pmu,
						     die))
				notअगरy = true;
		पूर्ण
		ids++;
	पूर्ण

	अगर (notअगरy && bus_रेजिस्टर_notअगरier(&pci_bus_type, &uncore_pci_sub_notअगरier))
		notअगरy = false;

	अगर (!notअगरy)
		uncore_pci_sub_driver = शून्य;
पूर्ण

अटल पूर्णांक uncore_pci_bus_notअगरy(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	वापस uncore_bus_notअगरy(nb, action, data, शून्य);
पूर्ण

अटल काष्ठा notअगरier_block uncore_pci_notअगरier = अणु
	.notअगरier_call = uncore_pci_bus_notअगरy,
पूर्ण;


अटल व्योम uncore_pci_pmus_रेजिस्टर(व्योम)
अणु
	काष्ठा पूर्णांकel_uncore_type **types = uncore_pci_uncores;
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा pci_dev *pdev;
	u64 box_ctl;
	पूर्णांक i, die;

	क्रम (; *types; types++) अणु
		type = *types;
		क्रम (die = 0; die < __uncore_max_dies; die++) अणु
			क्रम (i = 0; i < type->num_boxes; i++) अणु
				अगर (!type->box_ctls[die])
					जारी;
				box_ctl = type->box_ctls[die] + type->pci_offsets[i];
				pdev = pci_get_करोमुख्य_bus_and_slot(UNCORE_DISCOVERY_PCI_DOMAIN(box_ctl),
								   UNCORE_DISCOVERY_PCI_BUS(box_ctl),
								   UNCORE_DISCOVERY_PCI_DEVFN(box_ctl));
				अगर (!pdev)
					जारी;
				pmu = &type->pmus[i];

				uncore_pci_pmu_रेजिस्टर(pdev, type, pmu, die);
			पूर्ण
		पूर्ण
	पूर्ण

	bus_रेजिस्टर_notअगरier(&pci_bus_type, &uncore_pci_notअगरier);
पूर्ण

अटल पूर्णांक __init uncore_pci_init(व्योम)
अणु
	माप_प्रकार size;
	पूर्णांक ret;

	size = uncore_max_dies() * माप(काष्ठा pci_extra_dev);
	uncore_extra_pci_dev = kzalloc(size, GFP_KERNEL);
	अगर (!uncore_extra_pci_dev) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = uncore_types_init(uncore_pci_uncores, false);
	अगर (ret)
		जाओ errtype;

	अगर (uncore_pci_driver) अणु
		uncore_pci_driver->probe = uncore_pci_probe;
		uncore_pci_driver->हटाओ = uncore_pci_हटाओ;

		ret = pci_रेजिस्टर_driver(uncore_pci_driver);
		अगर (ret)
			जाओ errtype;
	पूर्ण अन्यथा
		uncore_pci_pmus_रेजिस्टर();

	अगर (uncore_pci_sub_driver)
		uncore_pci_sub_driver_init();

	pcidrv_रेजिस्टरed = true;
	वापस 0;

errtype:
	uncore_types_निकास(uncore_pci_uncores);
	kमुक्त(uncore_extra_pci_dev);
	uncore_extra_pci_dev = शून्य;
	uncore_मुक्त_pcibus_map();
err:
	uncore_pci_uncores = empty_uncore;
	वापस ret;
पूर्ण

अटल व्योम uncore_pci_निकास(व्योम)
अणु
	अगर (pcidrv_रेजिस्टरed) अणु
		pcidrv_रेजिस्टरed = false;
		अगर (uncore_pci_sub_driver)
			bus_unरेजिस्टर_notअगरier(&pci_bus_type, &uncore_pci_sub_notअगरier);
		अगर (uncore_pci_driver)
			pci_unरेजिस्टर_driver(uncore_pci_driver);
		अन्यथा
			bus_unरेजिस्टर_notअगरier(&pci_bus_type, &uncore_pci_notअगरier);
		uncore_types_निकास(uncore_pci_uncores);
		kमुक्त(uncore_extra_pci_dev);
		uncore_मुक्त_pcibus_map();
	पूर्ण
पूर्ण

अटल व्योम uncore_change_type_ctx(काष्ठा पूर्णांकel_uncore_type *type, पूर्णांक old_cpu,
				   पूर्णांक new_cpu)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = type->pmus;
	काष्ठा पूर्णांकel_uncore_box *box;
	पूर्णांक i, die;

	die = topology_logical_die_id(old_cpu < 0 ? new_cpu : old_cpu);
	क्रम (i = 0; i < type->num_boxes; i++, pmu++) अणु
		box = pmu->boxes[die];
		अगर (!box)
			जारी;

		अगर (old_cpu < 0) अणु
			WARN_ON_ONCE(box->cpu != -1);
			box->cpu = new_cpu;
			जारी;
		पूर्ण

		WARN_ON_ONCE(box->cpu != old_cpu);
		box->cpu = -1;
		अगर (new_cpu < 0)
			जारी;

		uncore_pmu_cancel_hrसमयr(box);
		perf_pmu_migrate_context(&pmu->pmu, old_cpu, new_cpu);
		box->cpu = new_cpu;
	पूर्ण
पूर्ण

अटल व्योम uncore_change_context(काष्ठा पूर्णांकel_uncore_type **uncores,
				  पूर्णांक old_cpu, पूर्णांक new_cpu)
अणु
	क्रम (; *uncores; uncores++)
		uncore_change_type_ctx(*uncores, old_cpu, new_cpu);
पूर्ण

अटल व्योम uncore_box_unref(काष्ठा पूर्णांकel_uncore_type **types, पूर्णांक id)
अणु
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा पूर्णांकel_uncore_box *box;
	पूर्णांक i;

	क्रम (; *types; types++) अणु
		type = *types;
		pmu = type->pmus;
		क्रम (i = 0; i < type->num_boxes; i++, pmu++) अणु
			box = pmu->boxes[id];
			अगर (box && atomic_dec_वापस(&box->refcnt) == 0)
				uncore_box_निकास(box);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक uncore_event_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक die, target;

	/* Check अगर निकासing cpu is used क्रम collecting uncore events */
	अगर (!cpumask_test_and_clear_cpu(cpu, &uncore_cpu_mask))
		जाओ unref;
	/* Find a new cpu to collect uncore events */
	target = cpumask_any_but(topology_die_cpumask(cpu), cpu);

	/* Migrate uncore events to the new target */
	अगर (target < nr_cpu_ids)
		cpumask_set_cpu(target, &uncore_cpu_mask);
	अन्यथा
		target = -1;

	uncore_change_context(uncore_msr_uncores, cpu, target);
	uncore_change_context(uncore_mmio_uncores, cpu, target);
	uncore_change_context(uncore_pci_uncores, cpu, target);

unref:
	/* Clear the references */
	die = topology_logical_die_id(cpu);
	uncore_box_unref(uncore_msr_uncores, die);
	uncore_box_unref(uncore_mmio_uncores, die);
	वापस 0;
पूर्ण

अटल पूर्णांक allocate_boxes(काष्ठा पूर्णांकel_uncore_type **types,
			 अचिन्हित पूर्णांक die, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा पूर्णांकel_uncore_box *box, *पंचांगp;
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	LIST_HEAD(allocated);
	पूर्णांक i;

	/* Try to allocate all required boxes */
	क्रम (; *types; types++) अणु
		type = *types;
		pmu = type->pmus;
		क्रम (i = 0; i < type->num_boxes; i++, pmu++) अणु
			अगर (pmu->boxes[die])
				जारी;
			box = uncore_alloc_box(type, cpu_to_node(cpu));
			अगर (!box)
				जाओ cleanup;
			box->pmu = pmu;
			box->dieid = die;
			list_add(&box->active_list, &allocated);
		पूर्ण
	पूर्ण
	/* Install them in the pmus */
	list_क्रम_each_entry_safe(box, पंचांगp, &allocated, active_list) अणु
		list_del_init(&box->active_list);
		box->pmu->boxes[die] = box;
	पूर्ण
	वापस 0;

cleanup:
	list_क्रम_each_entry_safe(box, पंचांगp, &allocated, active_list) अणु
		list_del_init(&box->active_list);
		kमुक्त(box);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक uncore_box_ref(काष्ठा पूर्णांकel_uncore_type **types,
			  पूर्णांक id, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा पूर्णांकel_uncore_type *type;
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा पूर्णांकel_uncore_box *box;
	पूर्णांक i, ret;

	ret = allocate_boxes(types, id, cpu);
	अगर (ret)
		वापस ret;

	क्रम (; *types; types++) अणु
		type = *types;
		pmu = type->pmus;
		क्रम (i = 0; i < type->num_boxes; i++, pmu++) अणु
			box = pmu->boxes[id];
			अगर (box && atomic_inc_वापस(&box->refcnt) == 1)
				uncore_box_init(box);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक uncore_event_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक die, target, msr_ret, mmio_ret;

	die = topology_logical_die_id(cpu);
	msr_ret = uncore_box_ref(uncore_msr_uncores, die, cpu);
	mmio_ret = uncore_box_ref(uncore_mmio_uncores, die, cpu);
	अगर (msr_ret && mmio_ret)
		वापस -ENOMEM;

	/*
	 * Check अगर there is an online cpu in the package
	 * which collects uncore events alपढ़ोy.
	 */
	target = cpumask_any_and(&uncore_cpu_mask, topology_die_cpumask(cpu));
	अगर (target < nr_cpu_ids)
		वापस 0;

	cpumask_set_cpu(cpu, &uncore_cpu_mask);

	अगर (!msr_ret)
		uncore_change_context(uncore_msr_uncores, -1, cpu);
	अगर (!mmio_ret)
		uncore_change_context(uncore_mmio_uncores, -1, cpu);
	uncore_change_context(uncore_pci_uncores, -1, cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक __init type_pmu_रेजिस्टर(काष्ठा पूर्णांकel_uncore_type *type)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < type->num_boxes; i++) अणु
		ret = uncore_pmu_रेजिस्टर(&type->pmus[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init uncore_msr_pmus_रेजिस्टर(व्योम)
अणु
	काष्ठा पूर्णांकel_uncore_type **types = uncore_msr_uncores;
	पूर्णांक ret;

	क्रम (; *types; types++) अणु
		ret = type_pmu_रेजिस्टर(*types);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init uncore_cpu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uncore_types_init(uncore_msr_uncores, true);
	अगर (ret)
		जाओ err;

	ret = uncore_msr_pmus_रेजिस्टर();
	अगर (ret)
		जाओ err;
	वापस 0;
err:
	uncore_types_निकास(uncore_msr_uncores);
	uncore_msr_uncores = empty_uncore;
	वापस ret;
पूर्ण

अटल पूर्णांक __init uncore_mmio_init(व्योम)
अणु
	काष्ठा पूर्णांकel_uncore_type **types = uncore_mmio_uncores;
	पूर्णांक ret;

	ret = uncore_types_init(types, true);
	अगर (ret)
		जाओ err;

	क्रम (; *types; types++) अणु
		ret = type_pmu_रेजिस्टर(*types);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;
err:
	uncore_types_निकास(uncore_mmio_uncores);
	uncore_mmio_uncores = empty_uncore;
	वापस ret;
पूर्ण

काष्ठा पूर्णांकel_uncore_init_fun अणु
	व्योम	(*cpu_init)(व्योम);
	पूर्णांक	(*pci_init)(व्योम);
	व्योम	(*mmio_init)(व्योम);
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun nhm_uncore_init __initस्थिर = अणु
	.cpu_init = nhm_uncore_cpu_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun snb_uncore_init __initस्थिर = अणु
	.cpu_init = snb_uncore_cpu_init,
	.pci_init = snb_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun ivb_uncore_init __initस्थिर = अणु
	.cpu_init = snb_uncore_cpu_init,
	.pci_init = ivb_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun hsw_uncore_init __initस्थिर = अणु
	.cpu_init = snb_uncore_cpu_init,
	.pci_init = hsw_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun bdw_uncore_init __initस्थिर = अणु
	.cpu_init = snb_uncore_cpu_init,
	.pci_init = bdw_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun snbep_uncore_init __initस्थिर = अणु
	.cpu_init = snbep_uncore_cpu_init,
	.pci_init = snbep_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun nhmex_uncore_init __initस्थिर = अणु
	.cpu_init = nhmex_uncore_cpu_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun ivbep_uncore_init __initस्थिर = अणु
	.cpu_init = ivbep_uncore_cpu_init,
	.pci_init = ivbep_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun hswep_uncore_init __initस्थिर = अणु
	.cpu_init = hswep_uncore_cpu_init,
	.pci_init = hswep_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun bdx_uncore_init __initस्थिर = अणु
	.cpu_init = bdx_uncore_cpu_init,
	.pci_init = bdx_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun knl_uncore_init __initस्थिर = अणु
	.cpu_init = knl_uncore_cpu_init,
	.pci_init = knl_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun skl_uncore_init __initस्थिर = अणु
	.cpu_init = skl_uncore_cpu_init,
	.pci_init = skl_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun skx_uncore_init __initस्थिर = अणु
	.cpu_init = skx_uncore_cpu_init,
	.pci_init = skx_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun icl_uncore_init __initस्थिर = अणु
	.cpu_init = icl_uncore_cpu_init,
	.pci_init = skl_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun tgl_uncore_init __initस्थिर = अणु
	.cpu_init = tgl_uncore_cpu_init,
	.mmio_init = tgl_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun tgl_l_uncore_init __initस्थिर = अणु
	.cpu_init = tgl_uncore_cpu_init,
	.mmio_init = tgl_l_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun rkl_uncore_init __initस्थिर = अणु
	.cpu_init = tgl_uncore_cpu_init,
	.pci_init = skl_uncore_pci_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun adl_uncore_init __initस्थिर = अणु
	.cpu_init = adl_uncore_cpu_init,
	.mmio_init = tgl_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun icx_uncore_init __initस्थिर = अणु
	.cpu_init = icx_uncore_cpu_init,
	.pci_init = icx_uncore_pci_init,
	.mmio_init = icx_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun snr_uncore_init __initस्थिर = अणु
	.cpu_init = snr_uncore_cpu_init,
	.pci_init = snr_uncore_pci_init,
	.mmio_init = snr_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uncore_init_fun generic_uncore_init __initस्थिर = अणु
	.cpu_init = पूर्णांकel_uncore_generic_uncore_cpu_init,
	.pci_init = पूर्णांकel_uncore_generic_uncore_pci_init,
	.mmio_init = पूर्णांकel_uncore_generic_uncore_mmio_init,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_uncore_match[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EP,		&nhm_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM,		&nhm_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE,		&nhm_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EP,		&nhm_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE,		&snb_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE,		&ivb_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL,		&hsw_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_L,		&hsw_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_G,		&hsw_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL,		&bdw_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_G,		&bdw_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(SANDYBRIDGE_X,	&snbep_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(NEHALEM_EX,		&nhmex_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(WESTMERE_EX,		&nhmex_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(IVYBRIDGE_X,		&ivbep_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(HASWELL_X,		&hswep_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_X,		&bdx_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(BROADWELL_D,		&bdx_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNL,	&knl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(XEON_PHI_KNM,	&knl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_X,		&skx_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE_L,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE,		&skl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L,		&icl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_NNPI,	&icl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE,		&icl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_D,		&icx_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_X,		&icx_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L,		&tgl_l_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE,		&tgl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ROCKETLAKE,		&rkl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE,		&adl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ALDERLAKE_L,		&adl_uncore_init),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_TREMONT_D,	&snr_uncore_init),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, पूर्णांकel_uncore_match);

अटल पूर्णांक __init पूर्णांकel_uncore_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	काष्ठा पूर्णांकel_uncore_init_fun *uncore_init;
	पूर्णांक pret = 0, cret = 0, mret = 0, ret;

	अगर (boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस -ENODEV;

	__uncore_max_dies =
		topology_max_packages() * topology_max_die_per_package();

	id = x86_match_cpu(पूर्णांकel_uncore_match);
	अगर (!id) अणु
		अगर (!uncore_no_discover && पूर्णांकel_uncore_has_discovery_tables())
			uncore_init = (काष्ठा पूर्णांकel_uncore_init_fun *)&generic_uncore_init;
		अन्यथा
			वापस -ENODEV;
	पूर्ण अन्यथा
		uncore_init = (काष्ठा पूर्णांकel_uncore_init_fun *)id->driver_data;

	अगर (uncore_init->pci_init) अणु
		pret = uncore_init->pci_init();
		अगर (!pret)
			pret = uncore_pci_init();
	पूर्ण

	अगर (uncore_init->cpu_init) अणु
		uncore_init->cpu_init();
		cret = uncore_cpu_init();
	पूर्ण

	अगर (uncore_init->mmio_init) अणु
		uncore_init->mmio_init();
		mret = uncore_mmio_init();
	पूर्ण

	अगर (cret && pret && mret) अणु
		ret = -ENODEV;
		जाओ मुक्त_discovery;
	पूर्ण

	/* Install hotplug callbacks to setup the tarमाला_लो क्रम each package */
	ret = cpuhp_setup_state(CPUHP_AP_PERF_X86_UNCORE_ONLINE,
				"perf/x86/intel/uncore:online",
				uncore_event_cpu_online,
				uncore_event_cpu_offline);
	अगर (ret)
		जाओ err;
	वापस 0;

err:
	uncore_types_निकास(uncore_msr_uncores);
	uncore_types_निकास(uncore_mmio_uncores);
	uncore_pci_निकास();
मुक्त_discovery:
	पूर्णांकel_uncore_clear_discovery_tables();
	वापस ret;
पूर्ण
module_init(पूर्णांकel_uncore_init);

अटल व्योम __निकास पूर्णांकel_uncore_निकास(व्योम)
अणु
	cpuhp_हटाओ_state(CPUHP_AP_PERF_X86_UNCORE_ONLINE);
	uncore_types_निकास(uncore_msr_uncores);
	uncore_types_निकास(uncore_mmio_uncores);
	uncore_pci_निकास();
	पूर्णांकel_uncore_clear_discovery_tables();
पूर्ण
module_निकास(पूर्णांकel_uncore_निकास);
