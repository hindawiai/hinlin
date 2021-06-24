<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARM DMC-620 memory controller PMU driver
 *
 * Copyright (C) 2020 Ampere Computing LLC.
 */

#घोषणा DMC620_PMUNAME		"arm_dmc620"
#घोषणा DMC620_DRVNAME		DMC620_PMUNAME "_pmu"
#घोषणा pr_fmt(fmt)		DMC620_DRVNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/refcount.h>

#घोषणा DMC620_PA_SHIFT					12
#घोषणा DMC620_CNT_INIT					0x80000000
#घोषणा DMC620_CNT_MAX_PERIOD				0xffffffff
#घोषणा DMC620_PMU_CLKDIV2_MAX_COUNTERS			8
#घोषणा DMC620_PMU_CLK_MAX_COUNTERS			2
#घोषणा DMC620_PMU_MAX_COUNTERS				\
	(DMC620_PMU_CLKDIV2_MAX_COUNTERS + DMC620_PMU_CLK_MAX_COUNTERS)

/*
 * The PMU रेजिस्टरs start at 0xA00 in the DMC-620 memory map, and these
 * offsets are relative to that base.
 *
 * Each counter has a group of control/value रेजिस्टरs, and the
 * DMC620_PMU_COUNTERn offsets are within a counter group.
 *
 * The counter रेजिस्टरs groups start at 0xA10.
 */
#घोषणा DMC620_PMU_OVERFLOW_STATUS_CLKDIV2		0x8
#घोषणा  DMC620_PMU_OVERFLOW_STATUS_CLKDIV2_MASK	\
		(DMC620_PMU_CLKDIV2_MAX_COUNTERS - 1)
#घोषणा DMC620_PMU_OVERFLOW_STATUS_CLK			0xC
#घोषणा  DMC620_PMU_OVERFLOW_STATUS_CLK_MASK		\
		(DMC620_PMU_CLK_MAX_COUNTERS - 1)
#घोषणा DMC620_PMU_COUNTERS_BASE			0x10
#घोषणा DMC620_PMU_COUNTERn_MASK_31_00			0x0
#घोषणा DMC620_PMU_COUNTERn_MASK_63_32			0x4
#घोषणा DMC620_PMU_COUNTERn_MATCH_31_00			0x8
#घोषणा DMC620_PMU_COUNTERn_MATCH_63_32			0xC
#घोषणा DMC620_PMU_COUNTERn_CONTROL			0x10
#घोषणा  DMC620_PMU_COUNTERn_CONTROL_ENABLE		BIT(0)
#घोषणा  DMC620_PMU_COUNTERn_CONTROL_INVERT		BIT(1)
#घोषणा  DMC620_PMU_COUNTERn_CONTROL_EVENT_MUX		GENMASK(6, 2)
#घोषणा  DMC620_PMU_COUNTERn_CONTROL_INCR_MUX		GENMASK(8, 7)
#घोषणा DMC620_PMU_COUNTERn_VALUE			0x20
/* Offset of the रेजिस्टरs क्रम a given counter, relative to 0xA00 */
#घोषणा DMC620_PMU_COUNTERn_OFFSET(n) \
	(DMC620_PMU_COUNTERS_BASE + 0x28 * (n))

अटल LIST_HEAD(dmc620_pmu_irqs);
अटल DEFINE_MUTEX(dmc620_pmu_irqs_lock);

काष्ठा dmc620_pmu_irq अणु
	काष्ठा hlist_node node;
	काष्ठा list_head pmus_node;
	काष्ठा list_head irqs_node;
	refcount_t refcount;
	अचिन्हित पूर्णांक irq_num;
	अचिन्हित पूर्णांक cpu;
पूर्ण;

काष्ठा dmc620_pmu अणु
	काष्ठा pmu pmu;

	व्योम __iomem *base;
	काष्ठा dmc620_pmu_irq *irq;
	काष्ठा list_head pmus_node;

	/*
	 * We put all clkभाग2 and clk counters to a same array.
	 * The first DMC620_PMU_CLKDIV2_MAX_COUNTERS bits beदीर्घ to
	 * clkभाग2 counters, the last DMC620_PMU_CLK_MAX_COUNTERS
	 * beदीर्घ to clk counters.
	 */
	DECLARE_BITMAP(used_mask, DMC620_PMU_MAX_COUNTERS);
	काष्ठा perf_event *events[DMC620_PMU_MAX_COUNTERS];
पूर्ण;

#घोषणा to_dmc620_pmu(p) (container_of(p, काष्ठा dmc620_pmu, pmu))

अटल पूर्णांक cpuhp_state_num;

काष्ठा dmc620_pmu_event_attr अणु
	काष्ठा device_attribute attr;
	u8 clkभाग2;
	u8 eventid;
पूर्ण;

अटल sमाप_प्रकार
dmc620_pmu_event_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा dmc620_pmu_event_attr *eattr;

	eattr = container_of(attr, typeof(*eattr), attr);

	वापस sysfs_emit(page, "event=0x%x,clkdiv2=0x%x\n", eattr->eventid, eattr->clkभाग2);
पूर्ण

#घोषणा DMC620_PMU_EVENT_ATTR(_name, _eventid, _clkभाग2)		\
	(&((काष्ठा dmc620_pmu_event_attr[]) अणुअणु				\
		.attr = __ATTR(_name, 0444, dmc620_pmu_event_show, शून्य),	\
		.clkभाग2 = _clkभाग2,						\
		.eventid = _eventid,					\
	पूर्णपूर्ण)[0].attr.attr)

अटल काष्ठा attribute *dmc620_pmu_events_attrs[] = अणु
	/* clkभाग2 events list */
	DMC620_PMU_EVENT_ATTR(clkभाग2_cycle_count, 0x0, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_allocate, 0x1, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_queue_depth, 0x2, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_रुकोing_क्रम_wr_data, 0x3, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_पढ़ो_backlog, 0x4, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_रुकोing_क्रम_mi, 0x5, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_hazard_resolution, 0x6, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_enqueue, 0x7, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_arbitrate, 0x8, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_lrank_turnaround_activate, 0x9, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_prank_turnaround_activate, 0xa, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_पढ़ो_depth, 0xb, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_ग_लिखो_depth, 0xc, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_highigh_qos_depth, 0xd, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_high_qos_depth, 0xe, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_medium_qos_depth, 0xf, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_low_qos_depth, 0x10, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_activate, 0x11, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_rdwr, 0x12, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_refresh, 0x13, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_training_request, 0x14, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_t_mac_tracker, 0x15, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_bk_fsm_tracker, 0x16, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_bk_खोलो_tracker, 0x17, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_ranks_in_pwr_करोwn, 0x18, 1),
	DMC620_PMU_EVENT_ATTR(clkभाग2_ranks_in_sref, 0x19, 1),

	/* clk events list */
	DMC620_PMU_EVENT_ATTR(clk_cycle_count, 0x0, 0),
	DMC620_PMU_EVENT_ATTR(clk_request, 0x1, 0),
	DMC620_PMU_EVENT_ATTR(clk_upload_stall, 0x2, 0),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dmc620_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = dmc620_pmu_events_attrs,
पूर्ण;

/* User ABI */
#घोषणा ATTR_CFG_FLD_mask_CFG		config
#घोषणा ATTR_CFG_FLD_mask_LO		0
#घोषणा ATTR_CFG_FLD_mask_HI		44
#घोषणा ATTR_CFG_FLD_match_CFG		config1
#घोषणा ATTR_CFG_FLD_match_LO		0
#घोषणा ATTR_CFG_FLD_match_HI		44
#घोषणा ATTR_CFG_FLD_invert_CFG		config2
#घोषणा ATTR_CFG_FLD_invert_LO		0
#घोषणा ATTR_CFG_FLD_invert_HI		0
#घोषणा ATTR_CFG_FLD_incr_CFG		config2
#घोषणा ATTR_CFG_FLD_incr_LO		1
#घोषणा ATTR_CFG_FLD_incr_HI		2
#घोषणा ATTR_CFG_FLD_event_CFG		config2
#घोषणा ATTR_CFG_FLD_event_LO		3
#घोषणा ATTR_CFG_FLD_event_HI		8
#घोषणा ATTR_CFG_FLD_clkभाग2_CFG	config2
#घोषणा ATTR_CFG_FLD_clkभाग2_LO		9
#घोषणा ATTR_CFG_FLD_clkभाग2_HI		9

#घोषणा __GEN_PMU_FORMAT_ATTR(cfg, lo, hi)			\
	(lo) == (hi) ? #cfg ":" #lo "\n" : #cfg ":" #lo "-" #hi

#घोषणा _GEN_PMU_FORMAT_ATTR(cfg, lo, hi)			\
	__GEN_PMU_FORMAT_ATTR(cfg, lo, hi)

#घोषणा GEN_PMU_FORMAT_ATTR(name)				\
	PMU_FORMAT_ATTR(name,					\
	_GEN_PMU_FORMAT_ATTR(ATTR_CFG_FLD_##name##_CFG,		\
			     ATTR_CFG_FLD_##name##_LO,		\
			     ATTR_CFG_FLD_##name##_HI))

#घोषणा _ATTR_CFG_GET_FLD(attr, cfg, lo, hi)			\
	((((attr)->cfg) >> lo) & GENMASK_ULL(hi - lo, 0))

#घोषणा ATTR_CFG_GET_FLD(attr, name)				\
	_ATTR_CFG_GET_FLD(attr,					\
			  ATTR_CFG_FLD_##name##_CFG,		\
			  ATTR_CFG_FLD_##name##_LO,		\
			  ATTR_CFG_FLD_##name##_HI)

GEN_PMU_FORMAT_ATTR(mask);
GEN_PMU_FORMAT_ATTR(match);
GEN_PMU_FORMAT_ATTR(invert);
GEN_PMU_FORMAT_ATTR(incr);
GEN_PMU_FORMAT_ATTR(event);
GEN_PMU_FORMAT_ATTR(clkभाग2);

अटल काष्ठा attribute *dmc620_pmu_क्रमmats_attrs[] = अणु
	&क्रमmat_attr_mask.attr,
	&क्रमmat_attr_match.attr,
	&क्रमmat_attr_invert.attr,
	&क्रमmat_attr_incr.attr,
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_clkभाग2.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dmc620_pmu_क्रमmat_attr_group = अणु
	.name	= "format",
	.attrs	= dmc620_pmu_क्रमmats_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dmc620_pmu_attr_groups[] = अणु
	&dmc620_pmu_events_attr_group,
	&dmc620_pmu_क्रमmat_attr_group,
	शून्य,
पूर्ण;

अटल अंतरभूत
u32 dmc620_pmu_creg_पढ़ो(काष्ठा dmc620_pmu *dmc620_pmu,
			अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(dmc620_pmu->base + DMC620_PMU_COUNTERn_OFFSET(idx) + reg);
पूर्ण

अटल अंतरभूत
व्योम dmc620_pmu_creg_ग_लिखो(काष्ठा dmc620_pmu *dmc620_pmu,
			अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, dmc620_pmu->base + DMC620_PMU_COUNTERn_OFFSET(idx) + reg);
पूर्ण

अटल
अचिन्हित पूर्णांक dmc620_event_to_counter_control(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	अचिन्हित पूर्णांक reg = 0;

	reg |= FIELD_PREP(DMC620_PMU_COUNTERn_CONTROL_INVERT,
			ATTR_CFG_GET_FLD(attr, invert));
	reg |= FIELD_PREP(DMC620_PMU_COUNTERn_CONTROL_EVENT_MUX,
			ATTR_CFG_GET_FLD(attr, event));
	reg |= FIELD_PREP(DMC620_PMU_COUNTERn_CONTROL_INCR_MUX,
			ATTR_CFG_GET_FLD(attr, incr));

	वापस reg;
पूर्ण

अटल पूर्णांक dmc620_get_event_idx(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);
	पूर्णांक idx, start_idx, end_idx;

	अगर (ATTR_CFG_GET_FLD(&event->attr, clkभाग2)) अणु
		start_idx = 0;
		end_idx = DMC620_PMU_CLKDIV2_MAX_COUNTERS;
	पूर्ण अन्यथा अणु
		start_idx = DMC620_PMU_CLKDIV2_MAX_COUNTERS;
		end_idx = DMC620_PMU_MAX_COUNTERS;
	पूर्ण

	क्रम (idx = start_idx; idx < end_idx; ++idx) अणु
		अगर (!test_and_set_bit(idx, dmc620_pmu->used_mask))
			वापस idx;
	पूर्ण

	/* The counters are all in use. */
	वापस -EAGAIN;
पूर्ण

अटल अंतरभूत
u64 dmc620_pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);

	वापस dmc620_pmu_creg_पढ़ो(dmc620_pmu,
				    event->hw.idx, DMC620_PMU_COUNTERn_VALUE);
पूर्ण

अटल व्योम dmc620_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_count, new_count;

	करो अणु
		/* We may also be called from the irq handler */
		prev_count = local64_पढ़ो(&hwc->prev_count);
		new_count = dmc620_pmu_पढ़ो_counter(event);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count,
			prev_count, new_count) != prev_count);
	delta = (new_count - prev_count) & DMC620_CNT_MAX_PERIOD;
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम dmc620_pmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);

	local64_set(&event->hw.prev_count, DMC620_CNT_INIT);
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      event->hw.idx, DMC620_PMU_COUNTERn_VALUE, DMC620_CNT_INIT);
पूर्ण

अटल व्योम dmc620_pmu_enable_counter(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);
	u32 reg;

	reg = dmc620_event_to_counter_control(event) | DMC620_PMU_COUNTERn_CONTROL_ENABLE;
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      event->hw.idx, DMC620_PMU_COUNTERn_CONTROL, reg);
पूर्ण

अटल व्योम dmc620_pmu_disable_counter(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);

	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      event->hw.idx, DMC620_PMU_COUNTERn_CONTROL, 0);
पूर्ण

अटल irqवापस_t dmc620_pmu_handle_irq(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा dmc620_pmu_irq *irq = data;
	काष्ठा dmc620_pmu *dmc620_pmu;
	irqवापस_t ret = IRQ_NONE;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(dmc620_pmu, &irq->pmus_node, pmus_node) अणु
		अचिन्हित दीर्घ status;
		काष्ठा perf_event *event;
		अचिन्हित पूर्णांक idx;

		/*
		 * HW करोesn't provide a control to atomically disable all counters.
		 * To prevent race condition (overflow happens जबतक clearing status रेजिस्टर),
		 * disable all events beक्रमe continuing
		 */
		क्रम (idx = 0; idx < DMC620_PMU_MAX_COUNTERS; idx++) अणु
			event = dmc620_pmu->events[idx];
			अगर (!event)
				जारी;
			dmc620_pmu_disable_counter(event);
		पूर्ण

		status = पढ़ोl(dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLKDIV2);
		status |= (पढ़ोl(dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLK) <<
				DMC620_PMU_CLKDIV2_MAX_COUNTERS);
		अगर (status) अणु
			क्रम_each_set_bit(idx, &status,
					DMC620_PMU_MAX_COUNTERS) अणु
				event = dmc620_pmu->events[idx];
				अगर (WARN_ON_ONCE(!event))
					जारी;
				dmc620_pmu_event_update(event);
				dmc620_pmu_event_set_period(event);
			पूर्ण

			अगर (status & DMC620_PMU_OVERFLOW_STATUS_CLKDIV2_MASK)
				ग_लिखोl(0, dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLKDIV2);

			अगर ((status >> DMC620_PMU_CLKDIV2_MAX_COUNTERS) &
				DMC620_PMU_OVERFLOW_STATUS_CLK_MASK)
				ग_लिखोl(0, dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLK);
		पूर्ण

		क्रम (idx = 0; idx < DMC620_PMU_MAX_COUNTERS; idx++) अणु
			event = dmc620_pmu->events[idx];
			अगर (!event)
				जारी;
			अगर (!(event->hw.state & PERF_HES_STOPPED))
				dmc620_pmu_enable_counter(event);
		पूर्ण

		ret = IRQ_HANDLED;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल काष्ठा dmc620_pmu_irq *__dmc620_pmu_get_irq(पूर्णांक irq_num)
अणु
	काष्ठा dmc620_pmu_irq *irq;
	पूर्णांक ret;

	list_क्रम_each_entry(irq, &dmc620_pmu_irqs, irqs_node)
		अगर (irq->irq_num == irq_num && refcount_inc_not_zero(&irq->refcount))
			वापस irq;

	irq = kzalloc(माप(*irq), GFP_KERNEL);
	अगर (!irq)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&irq->pmus_node);

	/* Pick one CPU to be the preferred one to use */
	irq->cpu = raw_smp_processor_id();
	refcount_set(&irq->refcount, 1);

	ret = request_irq(irq_num, dmc620_pmu_handle_irq,
			  IRQF_NOBALANCING | IRQF_NO_THREAD,
			  "dmc620-pmu", irq);
	अगर (ret)
		जाओ out_मुक्त_aff;

	ret = irq_set_affinity_hपूर्णांक(irq_num, cpumask_of(irq->cpu));
	अगर (ret)
		जाओ out_मुक्त_irq;

	ret = cpuhp_state_add_instance_nocalls(cpuhp_state_num, &irq->node);
	अगर (ret)
		जाओ out_मुक्त_irq;

	irq->irq_num = irq_num;
	list_add(&irq->irqs_node, &dmc620_pmu_irqs);

	वापस irq;

out_मुक्त_irq:
	मुक्त_irq(irq_num, irq);
out_मुक्त_aff:
	kमुक्त(irq);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक dmc620_pmu_get_irq(काष्ठा dmc620_pmu *dmc620_pmu, पूर्णांक irq_num)
अणु
	काष्ठा dmc620_pmu_irq *irq;

	mutex_lock(&dmc620_pmu_irqs_lock);
	irq = __dmc620_pmu_get_irq(irq_num);
	mutex_unlock(&dmc620_pmu_irqs_lock);

	अगर (IS_ERR(irq))
		वापस PTR_ERR(irq);

	dmc620_pmu->irq = irq;
	mutex_lock(&dmc620_pmu_irqs_lock);
	list_add_rcu(&dmc620_pmu->pmus_node, &irq->pmus_node);
	mutex_unlock(&dmc620_pmu_irqs_lock);

	वापस 0;
पूर्ण

अटल व्योम dmc620_pmu_put_irq(काष्ठा dmc620_pmu *dmc620_pmu)
अणु
	काष्ठा dmc620_pmu_irq *irq = dmc620_pmu->irq;

	mutex_lock(&dmc620_pmu_irqs_lock);
	list_del_rcu(&dmc620_pmu->pmus_node);

	अगर (!refcount_dec_and_test(&irq->refcount)) अणु
		mutex_unlock(&dmc620_pmu_irqs_lock);
		वापस;
	पूर्ण

	list_del(&irq->irqs_node);
	mutex_unlock(&dmc620_pmu_irqs_lock);

	WARN_ON(irq_set_affinity_hपूर्णांक(irq->irq_num, शून्य));
	मुक्त_irq(irq->irq_num, irq);
	cpuhp_state_हटाओ_instance_nocalls(cpuhp_state_num, &irq->node);
	kमुक्त(irq);
पूर्ण

अटल पूर्णांक dmc620_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_event *sibling;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * DMC 620 PMUs are shared across all cpus and cannot
	 * support task bound and sampling events.
	 */
	अगर (is_sampling_event(event) ||
		event->attach_state & PERF_ATTACH_TASK) अणु
		dev_dbg(dmc620_pmu->pmu.dev,
			"Can't support per-task counters\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Many perf core operations (eg. events rotation) operate on a
	 * single CPU context. This is obvious क्रम CPU PMUs, where one
	 * expects the same sets of events being observed on all CPUs,
	 * but can lead to issues क्रम off-core PMUs, where each
	 * event could be theoretically asचिन्हित to a dअगरferent CPU. To
	 * mitigate this, we enक्रमce CPU assignment to one, selected
	 * processor.
	 */
	event->cpu = dmc620_pmu->irq->cpu;
	अगर (event->cpu < 0)
		वापस -EINVAL;

	/*
	 * We can't atomically disable all HW counters so only one event allowed,
	 * although software events are acceptable.
	 */
	अगर (event->group_leader != event &&
			!is_software_event(event->group_leader))
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (sibling != event &&
				!is_software_event(sibling))
			वापस -EINVAL;
	पूर्ण

	hwc->idx = -1;
	वापस 0;
पूर्ण

अटल व्योम dmc620_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	dmc620_pmu_event_update(event);
पूर्ण

अटल व्योम dmc620_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	event->hw.state = 0;
	dmc620_pmu_event_set_period(event);
	dmc620_pmu_enable_counter(event);
पूर्ण

अटल व्योम dmc620_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	dmc620_pmu_disable_counter(event);
	dmc620_pmu_event_update(event);
	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक dmc620_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	u64 reg;

	idx = dmc620_get_event_idx(event);
	अगर (idx < 0)
		वापस idx;

	hwc->idx = idx;
	dmc620_pmu->events[idx] = event;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	reg = ATTR_CFG_GET_FLD(attr, mask);
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      idx, DMC620_PMU_COUNTERn_MASK_31_00, lower_32_bits(reg));
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      idx, DMC620_PMU_COUNTERn_MASK_63_32, upper_32_bits(reg));

	reg = ATTR_CFG_GET_FLD(attr, match);
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      idx, DMC620_PMU_COUNTERn_MATCH_31_00, lower_32_bits(reg));
	dmc620_pmu_creg_ग_लिखो(dmc620_pmu,
			      idx, DMC620_PMU_COUNTERn_MATCH_63_32, upper_32_bits(reg));

	अगर (flags & PERF_EF_START)
		dmc620_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);
	वापस 0;
पूर्ण

अटल व्योम dmc620_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = to_dmc620_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	dmc620_pmu_stop(event, PERF_EF_UPDATE);
	dmc620_pmu->events[idx] = शून्य;
	clear_bit(idx, dmc620_pmu->used_mask);
	perf_event_update_userpage(event);
पूर्ण

अटल पूर्णांक dmc620_pmu_cpu_tearकरोwn(अचिन्हित पूर्णांक cpu,
				   काष्ठा hlist_node *node)
अणु
	काष्ठा dmc620_pmu_irq *irq;
	काष्ठा dmc620_pmu *dmc620_pmu;
	अचिन्हित पूर्णांक target;

	irq = hlist_entry_safe(node, काष्ठा dmc620_pmu_irq, node);
	अगर (cpu != irq->cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	/* We're only reading, but this isn't the place to be involving RCU */
	mutex_lock(&dmc620_pmu_irqs_lock);
	list_क्रम_each_entry(dmc620_pmu, &irq->pmus_node, pmus_node)
		perf_pmu_migrate_context(&dmc620_pmu->pmu, irq->cpu, target);
	mutex_unlock(&dmc620_pmu_irqs_lock);

	WARN_ON(irq_set_affinity_hपूर्णांक(irq->irq_num, cpumask_of(target)));
	irq->cpu = target;

	वापस 0;
पूर्ण

अटल पूर्णांक dmc620_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu;
	काष्ठा resource *res;
	अक्षर *name;
	पूर्णांक irq_num;
	पूर्णांक i, ret;

	dmc620_pmu = devm_kzalloc(&pdev->dev,
			माप(काष्ठा dmc620_pmu), GFP_KERNEL);
	अगर (!dmc620_pmu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dmc620_pmu);

	dmc620_pmu->pmu = (काष्ठा pmu) अणु
		.module = THIS_MODULE,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
		.task_ctx_nr	= perf_invalid_context,
		.event_init	= dmc620_pmu_event_init,
		.add		= dmc620_pmu_add,
		.del		= dmc620_pmu_del,
		.start		= dmc620_pmu_start,
		.stop		= dmc620_pmu_stop,
		.पढ़ो		= dmc620_pmu_पढ़ो,
		.attr_groups	= dmc620_pmu_attr_groups,
	पूर्ण;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dmc620_pmu->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dmc620_pmu->base))
		वापस PTR_ERR(dmc620_pmu->base);

	/* Make sure device is reset beक्रमe enabling पूर्णांकerrupt */
	क्रम (i = 0; i < DMC620_PMU_MAX_COUNTERS; i++)
		dmc620_pmu_creg_ग_लिखो(dmc620_pmu, i, DMC620_PMU_COUNTERn_CONTROL, 0);
	ग_लिखोl(0, dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLKDIV2);
	ग_लिखोl(0, dmc620_pmu->base + DMC620_PMU_OVERFLOW_STATUS_CLK);

	irq_num = platक्रमm_get_irq(pdev, 0);
	अगर (irq_num < 0)
		वापस irq_num;

	ret = dmc620_pmu_get_irq(dmc620_pmu, irq_num);
	अगर (ret)
		वापस ret;

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				  "%s_%llx", DMC620_PMUNAME,
				  (u64)(res->start >> DMC620_PA_SHIFT));
	अगर (!name) अणु
		dev_err(&pdev->dev,
			  "Create name failed, PMU @%pa\n", &res->start);
		ret = -ENOMEM;
		जाओ out_tearकरोwn_dev;
	पूर्ण

	ret = perf_pmu_रेजिस्टर(&dmc620_pmu->pmu, name, -1);
	अगर (ret)
		जाओ out_tearकरोwn_dev;

	वापस 0;

out_tearकरोwn_dev:
	dmc620_pmu_put_irq(dmc620_pmu);
	synchronize_rcu();
	वापस ret;
पूर्ण

अटल पूर्णांक dmc620_pmu_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dmc620_pmu *dmc620_pmu = platक्रमm_get_drvdata(pdev);

	dmc620_pmu_put_irq(dmc620_pmu);

	/* perf will synchronise RCU beक्रमe devres can मुक्त dmc620_pmu */
	perf_pmu_unरेजिस्टर(&dmc620_pmu->pmu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id dmc620_acpi_match[] = अणु
	अणु "ARMHD620", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dmc620_acpi_match);
अटल काष्ठा platक्रमm_driver dmc620_pmu_driver = अणु
	.driver	= अणु
		.name		= DMC620_DRVNAME,
		.acpi_match_table = dmc620_acpi_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= dmc620_pmu_device_probe,
	.हटाओ	= dmc620_pmu_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init dmc620_pmu_init(व्योम)
अणु
	cpuhp_state_num = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      DMC620_DRVNAME,
				      शून्य,
				      dmc620_pmu_cpu_tearकरोwn);
	अगर (cpuhp_state_num < 0)
		वापस cpuhp_state_num;

	वापस platक्रमm_driver_रेजिस्टर(&dmc620_pmu_driver);
पूर्ण

अटल व्योम __निकास dmc620_pmu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dmc620_pmu_driver);
	cpuhp_हटाओ_multi_state(cpuhp_state_num);
पूर्ण

module_init(dmc620_pmu_init);
module_निकास(dmc620_pmu_निकास);

MODULE_DESCRIPTION("Perf driver for the ARM DMC-620 memory controller");
MODULE_AUTHOR("Tuan Phan <tuanphan@os.amperecomputing.com");
MODULE_LICENSE("GPL v2");
