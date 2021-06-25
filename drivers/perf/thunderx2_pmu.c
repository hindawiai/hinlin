<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CAVIUM THUNDERX2 SoC PMU UNCORE
 * Copyright (C) 2018 Cavium Inc.
 * Author: Ganapatrao Kulkarni <gkulkarni@cavium.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>

/* Each ThunderX2(TX2) Socket has a L3C and DMC UNCORE PMU device.
 * Each UNCORE PMU device consists of 4 independent programmable counters.
 * Counters are 32 bit and करो not support overflow पूर्णांकerrupt,
 * they need to be sampled beक्रमe overflow(i.e, at every 2 seconds).
 */

#घोषणा TX2_PMU_DMC_L3C_MAX_COUNTERS	4
#घोषणा TX2_PMU_CCPI2_MAX_COUNTERS	8
#घोषणा TX2_PMU_MAX_COUNTERS		TX2_PMU_CCPI2_MAX_COUNTERS


#घोषणा TX2_PMU_DMC_CHANNELS		8
#घोषणा TX2_PMU_L3_TILES		16

#घोषणा TX2_PMU_HRTIMER_INTERVAL	(2 * NSEC_PER_SEC)
#घोषणा GET_EVENTID(ev, mask)		((ev->hw.config) & mask)
#घोषणा GET_COUNTERID(ev, mask)		((ev->hw.idx) & mask)
 /* 1 byte per counter(4 counters).
  * Event id is encoded in bits [5:1] of a byte,
  */
#घोषणा DMC_EVENT_CFG(idx, val)		((val) << (((idx) * 8) + 1))

/* bits[3:0] to select counters, are indexed from 8 to 15. */
#घोषणा CCPI2_COUNTER_OFFSET		8

#घोषणा L3C_COUNTER_CTL			0xA8
#घोषणा L3C_COUNTER_DATA		0xAC
#घोषणा DMC_COUNTER_CTL			0x234
#घोषणा DMC_COUNTER_DATA		0x240

#घोषणा CCPI2_PERF_CTL			0x108
#घोषणा CCPI2_COUNTER_CTL		0x10C
#घोषणा CCPI2_COUNTER_SEL		0x12c
#घोषणा CCPI2_COUNTER_DATA_L		0x130
#घोषणा CCPI2_COUNTER_DATA_H		0x134

/* L3C event IDs */
#घोषणा L3_EVENT_READ_REQ		0xD
#घोषणा L3_EVENT_WRITEBACK_REQ		0xE
#घोषणा L3_EVENT_INV_N_WRITE_REQ	0xF
#घोषणा L3_EVENT_INV_REQ		0x10
#घोषणा L3_EVENT_EVICT_REQ		0x13
#घोषणा L3_EVENT_INV_N_WRITE_HIT	0x14
#घोषणा L3_EVENT_INV_HIT		0x15
#घोषणा L3_EVENT_READ_HIT		0x17
#घोषणा L3_EVENT_MAX			0x18

/* DMC event IDs */
#घोषणा DMC_EVENT_COUNT_CYCLES		0x1
#घोषणा DMC_EVENT_WRITE_TXNS		0xB
#घोषणा DMC_EVENT_DATA_TRANSFERS	0xD
#घोषणा DMC_EVENT_READ_TXNS		0xF
#घोषणा DMC_EVENT_MAX			0x10

#घोषणा CCPI2_EVENT_REQ_PKT_SENT	0x3D
#घोषणा CCPI2_EVENT_SNOOP_PKT_SENT	0x65
#घोषणा CCPI2_EVENT_DATA_PKT_SENT	0x105
#घोषणा CCPI2_EVENT_GIC_PKT_SENT	0x12D
#घोषणा CCPI2_EVENT_MAX			0x200

#घोषणा CCPI2_PERF_CTL_ENABLE		BIT(0)
#घोषणा CCPI2_PERF_CTL_START		BIT(1)
#घोषणा CCPI2_PERF_CTL_RESET		BIT(4)
#घोषणा CCPI2_EVENT_LEVEL_RISING_EDGE	BIT(10)
#घोषणा CCPI2_EVENT_TYPE_EDGE_SENSITIVE	BIT(11)

क्रमागत tx2_uncore_type अणु
	PMU_TYPE_L3C,
	PMU_TYPE_DMC,
	PMU_TYPE_CCPI2,
	PMU_TYPE_INVALID,
पूर्ण;

/*
 * Each socket has 3 uncore devices associated with a PMU. The DMC and
 * L3C have 4 32-bit counters and the CCPI2 has 8 64-bit counters.
 */
काष्ठा tx2_uncore_pmu अणु
	काष्ठा hlist_node hpnode;
	काष्ठा list_head  entry;
	काष्ठा pmu pmu;
	अक्षर *name;
	पूर्णांक node;
	पूर्णांक cpu;
	u32 max_counters;
	u32 counters_mask;
	u32 prorate_factor;
	u32 max_events;
	u32 events_mask;
	u64 hrसमयr_पूर्णांकerval;
	व्योम __iomem *base;
	DECLARE_BITMAP(active_counters, TX2_PMU_MAX_COUNTERS);
	काष्ठा perf_event *events[TX2_PMU_MAX_COUNTERS];
	काष्ठा device *dev;
	काष्ठा hrसमयr hrसमयr;
	स्थिर काष्ठा attribute_group **attr_groups;
	क्रमागत tx2_uncore_type type;
	क्रमागत hrसमयr_restart (*hrसमयr_callback)(काष्ठा hrसमयr *cb);
	व्योम (*init_cntr_base)(काष्ठा perf_event *event,
			काष्ठा tx2_uncore_pmu *tx2_pmu);
	व्योम (*stop_event)(काष्ठा perf_event *event);
	व्योम (*start_event)(काष्ठा perf_event *event, पूर्णांक flags);
पूर्ण;

अटल LIST_HEAD(tx2_pmus);

अटल अंतरभूत काष्ठा tx2_uncore_pmu *pmu_to_tx2_pmu(काष्ठा pmu *pmu)
अणु
	वापस container_of(pmu, काष्ठा tx2_uncore_pmu, pmu);
पूर्ण

#घोषणा TX2_PMU_FORMAT_ATTR(_var, _name, _क्रमmat)			\
अटल sमाप_प्रकार								\
__tx2_pmu_##_var##_show(काष्ठा device *dev,				\
			       काष्ठा device_attribute *attr,		\
			       अक्षर *page)				\
अणु									\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);			\
	वापस sysfs_emit(page, _क्रमmat "\n");				\
पूर्ण									\
									\
अटल काष्ठा device_attribute क्रमmat_attr_##_var =			\
	__ATTR(_name, 0444, __tx2_pmu_##_var##_show, शून्य)

TX2_PMU_FORMAT_ATTR(event, event, "config:0-4");
TX2_PMU_FORMAT_ATTR(event_ccpi2, event, "config:0-9");

अटल काष्ठा attribute *l3c_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *dmc_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ccpi2_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event_ccpi2.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = l3c_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dmc_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = dmc_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ccpi2_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = ccpi2_pmu_क्रमmat_attrs,
पूर्ण;

/*
 * sysfs event attributes
 */
अटल sमाप_प्रकार tx2_pmu_event_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "event=0x%lx\n", (अचिन्हित दीर्घ) eattr->var);
पूर्ण

#घोषणा TX2_EVENT_ATTR(name, config) \
	PMU_EVENT_ATTR(name, tx2_pmu_event_attr_##name, \
			config, tx2_pmu_event_show)

TX2_EVENT_ATTR(पढ़ो_request, L3_EVENT_READ_REQ);
TX2_EVENT_ATTR(ग_लिखोback_request, L3_EVENT_WRITEBACK_REQ);
TX2_EVENT_ATTR(inv_nग_लिखो_request, L3_EVENT_INV_N_WRITE_REQ);
TX2_EVENT_ATTR(inv_request, L3_EVENT_INV_REQ);
TX2_EVENT_ATTR(evict_request, L3_EVENT_EVICT_REQ);
TX2_EVENT_ATTR(inv_nग_लिखो_hit, L3_EVENT_INV_N_WRITE_HIT);
TX2_EVENT_ATTR(inv_hit, L3_EVENT_INV_HIT);
TX2_EVENT_ATTR(पढ़ो_hit, L3_EVENT_READ_HIT);

अटल काष्ठा attribute *l3c_pmu_events_attrs[] = अणु
	&tx2_pmu_event_attr_पढ़ो_request.attr.attr,
	&tx2_pmu_event_attr_ग_लिखोback_request.attr.attr,
	&tx2_pmu_event_attr_inv_nग_लिखो_request.attr.attr,
	&tx2_pmu_event_attr_inv_request.attr.attr,
	&tx2_pmu_event_attr_evict_request.attr.attr,
	&tx2_pmu_event_attr_inv_nग_लिखो_hit.attr.attr,
	&tx2_pmu_event_attr_inv_hit.attr.attr,
	&tx2_pmu_event_attr_पढ़ो_hit.attr.attr,
	शून्य,
पूर्ण;

TX2_EVENT_ATTR(cnt_cycles, DMC_EVENT_COUNT_CYCLES);
TX2_EVENT_ATTR(ग_लिखो_txns, DMC_EVENT_WRITE_TXNS);
TX2_EVENT_ATTR(data_transfers, DMC_EVENT_DATA_TRANSFERS);
TX2_EVENT_ATTR(पढ़ो_txns, DMC_EVENT_READ_TXNS);

अटल काष्ठा attribute *dmc_pmu_events_attrs[] = अणु
	&tx2_pmu_event_attr_cnt_cycles.attr.attr,
	&tx2_pmu_event_attr_ग_लिखो_txns.attr.attr,
	&tx2_pmu_event_attr_data_transfers.attr.attr,
	&tx2_pmu_event_attr_पढ़ो_txns.attr.attr,
	शून्य,
पूर्ण;

TX2_EVENT_ATTR(req_pktsent, CCPI2_EVENT_REQ_PKT_SENT);
TX2_EVENT_ATTR(snoop_pktsent, CCPI2_EVENT_SNOOP_PKT_SENT);
TX2_EVENT_ATTR(data_pktsent, CCPI2_EVENT_DATA_PKT_SENT);
TX2_EVENT_ATTR(gic_pktsent, CCPI2_EVENT_GIC_PKT_SENT);

अटल काष्ठा attribute *ccpi2_pmu_events_attrs[] = अणु
	&tx2_pmu_event_attr_req_pktsent.attr.attr,
	&tx2_pmu_event_attr_snoop_pktsent.attr.attr,
	&tx2_pmu_event_attr_data_pktsent.attr.attr,
	&tx2_pmu_event_attr_gic_pktsent.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = l3c_pmu_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dmc_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = dmc_pmu_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ccpi2_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = ccpi2_pmu_events_attrs,
पूर्ण;

/*
 * sysfs cpumask attributes
 */
अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(dev_get_drvdata(dev));
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(tx2_pmu->cpu));
पूर्ण
अटल DEVICE_ATTR_RO(cpumask);

अटल काष्ठा attribute *tx2_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pmu_cpumask_attr_group = अणु
	.attrs = tx2_pmu_cpumask_attrs,
पूर्ण;

/*
 * Per PMU device attribute groups
 */
अटल स्थिर काष्ठा attribute_group *l3c_pmu_attr_groups[] = अणु
	&l3c_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&l3c_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dmc_pmu_attr_groups[] = अणु
	&dmc_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&dmc_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ccpi2_pmu_attr_groups[] = अणु
	&ccpi2_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&ccpi2_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल अंतरभूत u32 reg_पढ़ोl(अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ोl((व्योम __iomem *)addr);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखोl(u32 val, अचिन्हित दीर्घ addr)
अणु
	ग_लिखोl(val, (व्योम __iomem *)addr);
पूर्ण

अटल पूर्णांक alloc_counter(काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	पूर्णांक counter;

	counter = find_first_zero_bit(tx2_pmu->active_counters,
				tx2_pmu->max_counters);
	अगर (counter == tx2_pmu->max_counters)
		वापस -ENOSPC;

	set_bit(counter, tx2_pmu->active_counters);
	वापस counter;
पूर्ण

अटल अंतरभूत व्योम मुक्त_counter(काष्ठा tx2_uncore_pmu *tx2_pmu, पूर्णांक counter)
अणु
	clear_bit(counter, tx2_pmu->active_counters);
पूर्ण

अटल व्योम init_cntr_base_l3c(काष्ठा perf_event *event,
		काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u32 cmask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->counters_mask;

	/* counter ctrl/data reg offset at 8 */
	hwc->config_base = (अचिन्हित दीर्घ)tx2_pmu->base
		+ L3C_COUNTER_CTL + (8 * GET_COUNTERID(event, cmask));
	hwc->event_base =  (अचिन्हित दीर्घ)tx2_pmu->base
		+ L3C_COUNTER_DATA + (8 * GET_COUNTERID(event, cmask));
पूर्ण

अटल व्योम init_cntr_base_dmc(काष्ठा perf_event *event,
		काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u32 cmask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->counters_mask;

	hwc->config_base = (अचिन्हित दीर्घ)tx2_pmu->base
		+ DMC_COUNTER_CTL;
	/* counter data reg offset at 0xc */
	hwc->event_base = (अचिन्हित दीर्घ)tx2_pmu->base
		+ DMC_COUNTER_DATA + (0xc * GET_COUNTERID(event, cmask));
पूर्ण

अटल व्योम init_cntr_base_ccpi2(काष्ठा perf_event *event,
		काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u32 cmask;

	cmask = tx2_pmu->counters_mask;

	hwc->config_base = (अचिन्हित दीर्घ)tx2_pmu->base
		+ CCPI2_COUNTER_CTL + (4 * GET_COUNTERID(event, cmask));
	hwc->event_base =  (अचिन्हित दीर्घ)tx2_pmu->base;
पूर्ण

अटल व्योम uncore_start_event_l3c(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u32 val, emask;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	emask = tx2_pmu->events_mask;

	/* event id encoded in bits [07:03] */
	val = GET_EVENTID(event, emask) << 3;
	reg_ग_लिखोl(val, hwc->config_base);
	local64_set(&hwc->prev_count, 0);
	reg_ग_लिखोl(0, hwc->event_base);
पूर्ण

अटल अंतरभूत व्योम uncore_stop_event_l3c(काष्ठा perf_event *event)
अणु
	reg_ग_लिखोl(0, event->hw.config_base);
पूर्ण

अटल व्योम uncore_start_event_dmc(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u32 val, cmask, emask;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	पूर्णांक idx, event_id;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->counters_mask;
	emask = tx2_pmu->events_mask;

	idx = GET_COUNTERID(event, cmask);
	event_id = GET_EVENTID(event, emask);

	/* enable and start counters.
	 * 8 bits क्रम each counter, bits[05:01] of a counter to set event type.
	 */
	val = reg_पढ़ोl(hwc->config_base);
	val &= ~DMC_EVENT_CFG(idx, 0x1f);
	val |= DMC_EVENT_CFG(idx, event_id);
	reg_ग_लिखोl(val, hwc->config_base);
	local64_set(&hwc->prev_count, 0);
	reg_ग_लिखोl(0, hwc->event_base);
पूर्ण

अटल व्योम uncore_stop_event_dmc(काष्ठा perf_event *event)
अणु
	u32 val, cmask;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	पूर्णांक idx;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	cmask = tx2_pmu->counters_mask;
	idx = GET_COUNTERID(event, cmask);

	/* clear event type(bits[05:01]) to stop counter */
	val = reg_पढ़ोl(hwc->config_base);
	val &= ~DMC_EVENT_CFG(idx, 0x1f);
	reg_ग_लिखोl(val, hwc->config_base);
पूर्ण

अटल व्योम uncore_start_event_ccpi2(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	u32 emask;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	emask = tx2_pmu->events_mask;

	/* Bit [09:00] to set event id.
	 * Bits [10], set level to rising edge.
	 * Bits [11], set type to edge sensitive.
	 */
	reg_ग_लिखोl((CCPI2_EVENT_TYPE_EDGE_SENSITIVE |
			CCPI2_EVENT_LEVEL_RISING_EDGE |
			GET_EVENTID(event, emask)), hwc->config_base);

	/* reset[4], enable[0] and start[1] counters */
	reg_ग_लिखोl(CCPI2_PERF_CTL_RESET |
			CCPI2_PERF_CTL_START |
			CCPI2_PERF_CTL_ENABLE,
			hwc->event_base + CCPI2_PERF_CTL);
	local64_set(&event->hw.prev_count, 0ULL);
पूर्ण

अटल व्योम uncore_stop_event_ccpi2(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* disable and stop counter */
	reg_ग_लिखोl(0, hwc->event_base + CCPI2_PERF_CTL);
पूर्ण

अटल व्योम tx2_uncore_event_update(काष्ठा perf_event *event)
अणु
	u64 prev, delta, new = 0;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	क्रमागत tx2_uncore_type type;
	u32 prorate_factor;
	u32 cmask, emask;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	type = tx2_pmu->type;
	cmask = tx2_pmu->counters_mask;
	emask = tx2_pmu->events_mask;
	prorate_factor = tx2_pmu->prorate_factor;
	अगर (type == PMU_TYPE_CCPI2) अणु
		reg_ग_लिखोl(CCPI2_COUNTER_OFFSET +
				GET_COUNTERID(event, cmask),
				hwc->event_base + CCPI2_COUNTER_SEL);
		new = reg_पढ़ोl(hwc->event_base + CCPI2_COUNTER_DATA_H);
		new = (new << 32) +
			reg_पढ़ोl(hwc->event_base + CCPI2_COUNTER_DATA_L);
		prev = local64_xchg(&hwc->prev_count, new);
		delta = new - prev;
	पूर्ण अन्यथा अणु
		new = reg_पढ़ोl(hwc->event_base);
		prev = local64_xchg(&hwc->prev_count, new);
		/* handles rollover of 32 bit counter */
		delta = (u32)(((1UL << 32) - prev) + new);
	पूर्ण

	/* DMC event data_transfers granularity is 16 Bytes, convert it to 64 */
	अगर (type == PMU_TYPE_DMC &&
			GET_EVENTID(event, emask) == DMC_EVENT_DATA_TRANSFERS)
		delta = delta/4;

	/* L3C and DMC has 16 and 8 पूर्णांकerleave channels respectively.
	 * The sampled value is क्रम channel 0 and multiplied with
	 * prorate_factor to get the count क्रम a device.
	 */
	local64_add(delta * prorate_factor, &event->count);
पूर्ण

अटल क्रमागत tx2_uncore_type get_tx2_pmu_type(काष्ठा acpi_device *adev)
अणु
	पूर्णांक i = 0;
	काष्ठा acpi_tx2_pmu_device अणु
		__u8 id[ACPI_ID_LEN];
		क्रमागत tx2_uncore_type type;
	पूर्ण devices[] = अणु
		अणु"CAV901D", PMU_TYPE_L3Cपूर्ण,
		अणु"CAV901F", PMU_TYPE_DMCपूर्ण,
		अणु"CAV901E", PMU_TYPE_CCPI2पूर्ण,
		अणु"", PMU_TYPE_INVALIDपूर्ण
	पूर्ण;

	जबतक (devices[i].type != PMU_TYPE_INVALID) अणु
		अगर (!म_भेद(acpi_device_hid(adev), devices[i].id))
			अवरोध;
		i++;
	पूर्ण

	वापस devices[i].type;
पूर्ण

अटल bool tx2_uncore_validate_event(काष्ठा pmu *pmu,
				  काष्ठा perf_event *event, पूर्णांक *counters)
अणु
	अगर (is_software_event(event))
		वापस true;
	/* Reject groups spanning multiple HW PMUs. */
	अगर (event->pmu != pmu)
		वापस false;

	*counters = *counters + 1;
	वापस true;
पूर्ण

/*
 * Make sure the group of events can be scheduled at once
 * on the PMU.
 */
अटल bool tx2_uncore_validate_event_group(काष्ठा perf_event *event,
		पूर्णांक max_counters)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	पूर्णांक counters = 0;

	अगर (event->group_leader == event)
		वापस true;

	अगर (!tx2_uncore_validate_event(event->pmu, leader, &counters))
		वापस false;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!tx2_uncore_validate_event(event->pmu, sibling, &counters))
			वापस false;
	पूर्ण

	अगर (!tx2_uncore_validate_event(event->pmu, event, &counters))
		वापस false;

	/*
	 * If the group requires more counters than the HW has,
	 * it cannot ever be scheduled.
	 */
	वापस counters <= max_counters;
पूर्ण


अटल पूर्णांक tx2_uncore_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	/* Test the event attr type check क्रम PMU क्रमागतeration */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * SOC PMU counters are shared across all cores.
	 * Thereक्रमe, it करोes not support per-process mode.
	 * Also, it करोes not support event sampling mode.
	 */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	अगर (tx2_pmu->cpu >= nr_cpu_ids)
		वापस -EINVAL;
	event->cpu = tx2_pmu->cpu;

	अगर (event->attr.config >= tx2_pmu->max_events)
		वापस -EINVAL;

	/* store event id */
	hwc->config = event->attr.config;

	/* Validate the group */
	अगर (!tx2_uncore_validate_event_group(event, tx2_pmu->max_counters))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम tx2_uncore_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	hwc->state = 0;
	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	tx2_pmu->start_event(event, flags);
	perf_event_update_userpage(event);

	/* No hrसमयr needed क्रम CCPI2, 64-bit counters */
	अगर (!tx2_pmu->hrसमयr_callback)
		वापस;

	/* Start समयr क्रम first event */
	अगर (biपंचांगap_weight(tx2_pmu->active_counters,
				tx2_pmu->max_counters) == 1) अणु
		hrसमयr_start(&tx2_pmu->hrसमयr,
			ns_to_kसमय(tx2_pmu->hrसमयr_पूर्णांकerval),
			HRTIMER_MODE_REL_PINNED);
	पूर्ण
पूर्ण

अटल व्योम tx2_uncore_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	tx2_pmu->stop_event(event);
	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;
	अगर (flags & PERF_EF_UPDATE) अणु
		tx2_uncore_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक tx2_uncore_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = pmu_to_tx2_pmu(event->pmu);

	/* Allocate a मुक्त counter */
	hwc->idx  = alloc_counter(tx2_pmu);
	अगर (hwc->idx < 0)
		वापस -EAGAIN;

	tx2_pmu->events[hwc->idx] = event;
	/* set counter control and data रेजिस्टरs base address */
	tx2_pmu->init_cntr_base(event, tx2_pmu);

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (flags & PERF_EF_START)
		tx2_uncore_event_start(event, flags);

	वापस 0;
पूर्ण

अटल व्योम tx2_uncore_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu = pmu_to_tx2_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u32 cmask;

	cmask = tx2_pmu->counters_mask;
	tx2_uncore_event_stop(event, PERF_EF_UPDATE);

	/* clear the asचिन्हित counter */
	मुक्त_counter(tx2_pmu, GET_COUNTERID(event, cmask));

	perf_event_update_userpage(event);
	tx2_pmu->events[hwc->idx] = शून्य;
	hwc->idx = -1;

	अगर (!tx2_pmu->hrसमयr_callback)
		वापस;

	अगर (biपंचांगap_empty(tx2_pmu->active_counters, tx2_pmu->max_counters))
		hrसमयr_cancel(&tx2_pmu->hrसमयr);
पूर्ण

अटल व्योम tx2_uncore_event_पढ़ो(काष्ठा perf_event *event)
अणु
	tx2_uncore_event_update(event);
पूर्ण

अटल क्रमागत hrसमयr_restart tx2_hrसमयr_callback(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	पूर्णांक max_counters, idx;

	tx2_pmu = container_of(समयr, काष्ठा tx2_uncore_pmu, hrसमयr);
	max_counters = tx2_pmu->max_counters;

	अगर (biपंचांगap_empty(tx2_pmu->active_counters, max_counters))
		वापस HRTIMER_NORESTART;

	क्रम_each_set_bit(idx, tx2_pmu->active_counters, max_counters) अणु
		काष्ठा perf_event *event = tx2_pmu->events[idx];

		tx2_uncore_event_update(event);
	पूर्ण
	hrसमयr_क्रमward_now(समयr, ns_to_kसमय(tx2_pmu->hrसमयr_पूर्णांकerval));
	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक tx2_uncore_pmu_रेजिस्टर(
		काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	काष्ठा device *dev = tx2_pmu->dev;
	अक्षर *name = tx2_pmu->name;

	/* Perf event registration */
	tx2_pmu->pmu = (काष्ठा pmu) अणु
		.module         = THIS_MODULE,
		.attr_groups	= tx2_pmu->attr_groups,
		.task_ctx_nr	= perf_invalid_context,
		.event_init	= tx2_uncore_event_init,
		.add		= tx2_uncore_event_add,
		.del		= tx2_uncore_event_del,
		.start		= tx2_uncore_event_start,
		.stop		= tx2_uncore_event_stop,
		.पढ़ो		= tx2_uncore_event_पढ़ो,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	tx2_pmu->pmu.name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
			"%s", name);

	वापस perf_pmu_रेजिस्टर(&tx2_pmu->pmu, tx2_pmu->pmu.name, -1);
पूर्ण

अटल पूर्णांक tx2_uncore_pmu_add_dev(काष्ठा tx2_uncore_pmu *tx2_pmu)
अणु
	पूर्णांक ret, cpu;

	cpu = cpumask_any_and(cpumask_of_node(tx2_pmu->node),
			cpu_online_mask);

	tx2_pmu->cpu = cpu;

	अगर (tx2_pmu->hrसमयr_callback) अणु
		hrसमयr_init(&tx2_pmu->hrसमयr,
				CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		tx2_pmu->hrसमयr.function = tx2_pmu->hrसमयr_callback;
	पूर्ण

	ret = tx2_uncore_pmu_रेजिस्टर(tx2_pmu);
	अगर (ret) अणु
		dev_err(tx2_pmu->dev, "%s PMU: Failed to init driver\n",
				tx2_pmu->name);
		वापस -ENODEV;
	पूर्ण

	/* रेजिस्टर hotplug callback क्रम the pmu */
	ret = cpuhp_state_add_instance(
			CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE,
			&tx2_pmu->hpnode);
	अगर (ret) अणु
		dev_err(tx2_pmu->dev, "Error %d registering hotplug", ret);
		वापस ret;
	पूर्ण

	/* Add to list */
	list_add(&tx2_pmu->entry, &tx2_pmus);

	dev_dbg(tx2_pmu->dev, "%s PMU UNCORE registered\n",
			tx2_pmu->pmu.name);
	वापस ret;
पूर्ण

अटल काष्ठा tx2_uncore_pmu *tx2_uncore_pmu_init_dev(काष्ठा device *dev,
		acpi_handle handle, काष्ठा acpi_device *adev, u32 type)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	व्योम __iomem *base;
	काष्ठा resource res;
	काष्ठा resource_entry *rentry;
	काष्ठा list_head list;
	पूर्णांक ret;

	INIT_LIST_HEAD(&list);
	ret = acpi_dev_get_resources(adev, &list, शून्य, शून्य);
	अगर (ret <= 0) अणु
		dev_err(dev, "failed to parse _CRS method, error %d\n", ret);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(rentry, &list, node) अणु
		अगर (resource_type(rentry->res) == IORESOURCE_MEM) अणु
			res = *rentry->res;
			rentry = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	acpi_dev_मुक्त_resource_list(&list);

	अगर (rentry) अणु
		dev_err(dev, "PMU type %d: Fail to find resource\n", type);
		वापस शून्य;
	पूर्ण

	base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "PMU type %d: Fail to map resource\n", type);
		वापस शून्य;
	पूर्ण

	tx2_pmu = devm_kzalloc(dev, माप(*tx2_pmu), GFP_KERNEL);
	अगर (!tx2_pmu)
		वापस शून्य;

	tx2_pmu->dev = dev;
	tx2_pmu->type = type;
	tx2_pmu->base = base;
	tx2_pmu->node = dev_to_node(dev);
	INIT_LIST_HEAD(&tx2_pmu->entry);

	चयन (tx2_pmu->type) अणु
	हाल PMU_TYPE_L3C:
		tx2_pmu->max_counters = TX2_PMU_DMC_L3C_MAX_COUNTERS;
		tx2_pmu->counters_mask = 0x3;
		tx2_pmu->prorate_factor = TX2_PMU_L3_TILES;
		tx2_pmu->max_events = L3_EVENT_MAX;
		tx2_pmu->events_mask = 0x1f;
		tx2_pmu->hrसमयr_पूर्णांकerval = TX2_PMU_HRTIMER_INTERVAL;
		tx2_pmu->hrसमयr_callback = tx2_hrसमयr_callback;
		tx2_pmu->attr_groups = l3c_pmu_attr_groups;
		tx2_pmu->name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				"uncore_l3c_%d", tx2_pmu->node);
		tx2_pmu->init_cntr_base = init_cntr_base_l3c;
		tx2_pmu->start_event = uncore_start_event_l3c;
		tx2_pmu->stop_event = uncore_stop_event_l3c;
		अवरोध;
	हाल PMU_TYPE_DMC:
		tx2_pmu->max_counters = TX2_PMU_DMC_L3C_MAX_COUNTERS;
		tx2_pmu->counters_mask = 0x3;
		tx2_pmu->prorate_factor = TX2_PMU_DMC_CHANNELS;
		tx2_pmu->max_events = DMC_EVENT_MAX;
		tx2_pmu->events_mask = 0x1f;
		tx2_pmu->hrसमयr_पूर्णांकerval = TX2_PMU_HRTIMER_INTERVAL;
		tx2_pmu->hrसमयr_callback = tx2_hrसमयr_callback;
		tx2_pmu->attr_groups = dmc_pmu_attr_groups;
		tx2_pmu->name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				"uncore_dmc_%d", tx2_pmu->node);
		tx2_pmu->init_cntr_base = init_cntr_base_dmc;
		tx2_pmu->start_event = uncore_start_event_dmc;
		tx2_pmu->stop_event = uncore_stop_event_dmc;
		अवरोध;
	हाल PMU_TYPE_CCPI2:
		/* CCPI2 has 8 counters */
		tx2_pmu->max_counters = TX2_PMU_CCPI2_MAX_COUNTERS;
		tx2_pmu->counters_mask = 0x7;
		tx2_pmu->prorate_factor = 1;
		tx2_pmu->max_events = CCPI2_EVENT_MAX;
		tx2_pmu->events_mask = 0x1ff;
		tx2_pmu->attr_groups = ccpi2_pmu_attr_groups;
		tx2_pmu->name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				"uncore_ccpi2_%d", tx2_pmu->node);
		tx2_pmu->init_cntr_base = init_cntr_base_ccpi2;
		tx2_pmu->start_event = uncore_start_event_ccpi2;
		tx2_pmu->stop_event = uncore_stop_event_ccpi2;
		tx2_pmu->hrसमयr_callback = शून्य;
		अवरोध;
	हाल PMU_TYPE_INVALID:
		devm_kमुक्त(dev, tx2_pmu);
		वापस शून्य;
	पूर्ण

	वापस tx2_pmu;
पूर्ण

अटल acpi_status tx2_uncore_pmu_add(acpi_handle handle, u32 level,
				    व्योम *data, व्योम **वापस_value)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	काष्ठा acpi_device *adev;
	क्रमागत tx2_uncore_type type;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;
	अगर (acpi_bus_get_status(adev) || !adev->status.present)
		वापस AE_OK;

	type = get_tx2_pmu_type(adev);
	अगर (type == PMU_TYPE_INVALID)
		वापस AE_OK;

	tx2_pmu = tx2_uncore_pmu_init_dev((काष्ठा device *)data,
			handle, adev, type);

	अगर (!tx2_pmu)
		वापस AE_ERROR;

	अगर (tx2_uncore_pmu_add_dev(tx2_pmu)) अणु
		/* Can't add the PMU device, पात */
		वापस AE_ERROR;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल पूर्णांक tx2_uncore_pmu_online_cpu(अचिन्हित पूर्णांक cpu,
		काष्ठा hlist_node *hpnode)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu;

	tx2_pmu = hlist_entry_safe(hpnode,
			काष्ठा tx2_uncore_pmu, hpnode);

	/* Pick this CPU, If there is no CPU/PMU association and both are
	 * from same node.
	 */
	अगर ((tx2_pmu->cpu >= nr_cpu_ids) &&
		(tx2_pmu->node == cpu_to_node(cpu)))
		tx2_pmu->cpu = cpu;

	वापस 0;
पूर्ण

अटल पूर्णांक tx2_uncore_pmu_offline_cpu(अचिन्हित पूर्णांक cpu,
		काष्ठा hlist_node *hpnode)
अणु
	पूर्णांक new_cpu;
	काष्ठा tx2_uncore_pmu *tx2_pmu;
	काष्ठा cpumask cpu_online_mask_temp;

	tx2_pmu = hlist_entry_safe(hpnode,
			काष्ठा tx2_uncore_pmu, hpnode);

	अगर (cpu != tx2_pmu->cpu)
		वापस 0;

	अगर (tx2_pmu->hrसमयr_callback)
		hrसमयr_cancel(&tx2_pmu->hrसमयr);

	cpumask_copy(&cpu_online_mask_temp, cpu_online_mask);
	cpumask_clear_cpu(cpu, &cpu_online_mask_temp);
	new_cpu = cpumask_any_and(
			cpumask_of_node(tx2_pmu->node),
			&cpu_online_mask_temp);

	tx2_pmu->cpu = new_cpu;
	अगर (new_cpu >= nr_cpu_ids)
		वापस 0;
	perf_pmu_migrate_context(&tx2_pmu->pmu, cpu, new_cpu);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id tx2_uncore_acpi_match[] = अणु
	अणु"CAV901C", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, tx2_uncore_acpi_match);

अटल पूर्णांक tx2_uncore_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	acpi_handle handle;
	acpi_status status;

	set_dev_node(dev, acpi_get_node(ACPI_HANDLE(dev)));

	अगर (!has_acpi_companion(dev))
		वापस -ENODEV;

	handle = ACPI_HANDLE(dev);
	अगर (!handle)
		वापस -EINVAL;

	/* Walk through the tree क्रम all PMU UNCORE devices */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     tx2_uncore_pmu_add,
				     शून्य, dev, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "failed to probe PMU devices\n");
		वापस_ACPI_STATUS(status);
	पूर्ण

	dev_info(dev, "node%d: pmu uncore registered\n", dev_to_node(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक tx2_uncore_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tx2_uncore_pmu *tx2_pmu, *temp;
	काष्ठा device *dev = &pdev->dev;

	अगर (!list_empty(&tx2_pmus)) अणु
		list_क्रम_each_entry_safe(tx2_pmu, temp, &tx2_pmus, entry) अणु
			अगर (tx2_pmu->node == dev_to_node(dev)) अणु
				cpuhp_state_हटाओ_instance_nocalls(
					CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE,
					&tx2_pmu->hpnode);
				perf_pmu_unरेजिस्टर(&tx2_pmu->pmu);
				list_del(&tx2_pmu->entry);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tx2_uncore_driver = अणु
	.driver = अणु
		.name		= "tx2-uncore-pmu",
		.acpi_match_table = ACPI_PTR(tx2_uncore_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = tx2_uncore_probe,
	.हटाओ = tx2_uncore_हटाओ,
पूर्ण;

अटल पूर्णांक __init tx2_uncore_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE,
				      "perf/tx2/uncore:online",
				      tx2_uncore_pmu_online_cpu,
				      tx2_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("TX2 PMU: setup hotplug failed(%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = platक्रमm_driver_रेजिस्टर(&tx2_uncore_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE);

	वापस ret;
पूर्ण
module_init(tx2_uncore_driver_init);

अटल व्योम __निकास tx2_uncore_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tx2_uncore_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE);
पूर्ण
module_निकास(tx2_uncore_driver_निकास);

MODULE_DESCRIPTION("ThunderX2 UNCORE PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ganapatrao Kulkarni <gkulkarni@cavium.com>");
