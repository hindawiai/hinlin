<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2017 NXP
 * Copyright 2016 Freescale Semiconductor, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>

#घोषणा COUNTER_CNTL		0x0
#घोषणा COUNTER_READ		0x20

#घोषणा COUNTER_DPCR1		0x30

#घोषणा CNTL_OVER		0x1
#घोषणा CNTL_CLEAR		0x2
#घोषणा CNTL_EN			0x4
#घोषणा CNTL_EN_MASK		0xFFFFFFFB
#घोषणा CNTL_CLEAR_MASK		0xFFFFFFFD
#घोषणा CNTL_OVER_MASK		0xFFFFFFFE

#घोषणा CNTL_CSV_SHIFT		24
#घोषणा CNTL_CSV_MASK		(0xFF << CNTL_CSV_SHIFT)

#घोषणा EVENT_CYCLES_ID		0
#घोषणा EVENT_CYCLES_COUNTER	0
#घोषणा NUM_COUNTERS		4

#घोषणा AXI_MASKING_REVERT	0xffff0000	/* AXI_MASKING(MSB 16bits) + AXI_ID(LSB 16bits) */

#घोषणा to_ddr_pmu(p)		container_of(p, काष्ठा ddr_pmu, pmu)

#घोषणा DDR_PERF_DEV_NAME	"imx8_ddr"
#घोषणा DDR_CPUHP_CB_NAME	DDR_PERF_DEV_NAME "_perf_pmu"

अटल DEFINE_IDA(ddr_ida);

/* DDR Perf hardware feature */
#घोषणा DDR_CAP_AXI_ID_FILTER			0x1     /* support AXI ID filter */
#घोषणा DDR_CAP_AXI_ID_FILTER_ENHANCED		0x3     /* support enhanced AXI ID filter */

काष्ठा fsl_ddr_devtype_data अणु
	अचिन्हित पूर्णांक quirks;    /* quirks needed क्रम dअगरferent DDR Perf core */
	स्थिर अक्षर *identअगरier;	/* प्रणाली PMU identअगरier क्रम userspace */
पूर्ण;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8_devtype_data;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8m_devtype_data = अणु
	.quirks = DDR_CAP_AXI_ID_FILTER,
पूर्ण;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8mq_devtype_data = अणु
	.quirks = DDR_CAP_AXI_ID_FILTER,
	.identअगरier = "i.MX8MQ",
पूर्ण;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8mm_devtype_data = अणु
	.quirks = DDR_CAP_AXI_ID_FILTER,
	.identअगरier = "i.MX8MM",
पूर्ण;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8mn_devtype_data = अणु
	.quirks = DDR_CAP_AXI_ID_FILTER,
	.identअगरier = "i.MX8MN",
पूर्ण;

अटल स्थिर काष्ठा fsl_ddr_devtype_data imx8mp_devtype_data = अणु
	.quirks = DDR_CAP_AXI_ID_FILTER_ENHANCED,
	.identअगरier = "i.MX8MP",
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_ddr_pmu_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8-ddr-pmu", .data = &imx8_devtype_dataपूर्ण,
	अणु .compatible = "fsl,imx8m-ddr-pmu", .data = &imx8m_devtype_dataपूर्ण,
	अणु .compatible = "fsl,imx8mq-ddr-pmu", .data = &imx8mq_devtype_dataपूर्ण,
	अणु .compatible = "fsl,imx8mm-ddr-pmu", .data = &imx8mm_devtype_dataपूर्ण,
	अणु .compatible = "fsl,imx8mn-ddr-pmu", .data = &imx8mn_devtype_dataपूर्ण,
	अणु .compatible = "fsl,imx8mp-ddr-pmu", .data = &imx8mp_devtype_dataपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_ddr_pmu_dt_ids);

काष्ठा ddr_pmu अणु
	काष्ठा pmu pmu;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक cpu;
	काष्ठा	hlist_node node;
	काष्ठा	device *dev;
	काष्ठा perf_event *events[NUM_COUNTERS];
	पूर्णांक active_events;
	क्रमागत cpuhp_state cpuhp_state;
	स्थिर काष्ठा fsl_ddr_devtype_data *devtype_data;
	पूर्णांक irq;
	पूर्णांक id;
पूर्ण;

अटल sमाप_प्रकार ddr_perf_identअगरier_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *page)
अणु
	काष्ठा ddr_pmu *pmu = dev_get_drvdata(dev);

	वापस sysfs_emit(page, "%s\n", pmu->devtype_data->identअगरier);
पूर्ण

अटल umode_t ddr_perf_identअगरier_attr_visible(काष्ठा kobject *kobj,
						काष्ठा attribute *attr,
						पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा ddr_pmu *pmu = dev_get_drvdata(dev);

	अगर (!pmu->devtype_data->identअगरier)
		वापस 0;
	वापस attr->mode;
पूर्ण;

अटल काष्ठा device_attribute ddr_perf_identअगरier_attr =
	__ATTR(identअगरier, 0444, ddr_perf_identअगरier_show, शून्य);

अटल काष्ठा attribute *ddr_perf_identअगरier_attrs[] = अणु
	&ddr_perf_identअगरier_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ddr_perf_identअगरier_attr_group = अणु
	.attrs = ddr_perf_identअगरier_attrs,
	.is_visible = ddr_perf_identअगरier_attr_visible,
पूर्ण;

क्रमागत ddr_perf_filter_capabilities अणु
	PERF_CAP_AXI_ID_FILTER = 0,
	PERF_CAP_AXI_ID_FILTER_ENHANCED,
	PERF_CAP_AXI_ID_FEAT_MAX,
पूर्ण;

अटल u32 ddr_perf_filter_cap_get(काष्ठा ddr_pmu *pmu, पूर्णांक cap)
अणु
	u32 quirks = pmu->devtype_data->quirks;

	चयन (cap) अणु
	हाल PERF_CAP_AXI_ID_FILTER:
		वापस !!(quirks & DDR_CAP_AXI_ID_FILTER);
	हाल PERF_CAP_AXI_ID_FILTER_ENHANCED:
		quirks &= DDR_CAP_AXI_ID_FILTER_ENHANCED;
		वापस quirks == DDR_CAP_AXI_ID_FILTER_ENHANCED;
	शेष:
		WARN(1, "unknown filter cap %d\n", cap);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ddr_perf_filter_cap_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा ddr_pmu *pmu = dev_get_drvdata(dev);
	काष्ठा dev_ext_attribute *ea =
		container_of(attr, काष्ठा dev_ext_attribute, attr);
	पूर्णांक cap = (दीर्घ)ea->var;

	वापस sysfs_emit(buf, "%u\n", ddr_perf_filter_cap_get(pmu, cap));
पूर्ण

#घोषणा PERF_EXT_ATTR_ENTRY(_name, _func, _var)				\
	(&((काष्ठा dev_ext_attribute) अणु					\
		__ATTR(_name, 0444, _func, शून्य), (व्योम *)_var		\
	पूर्ण).attr.attr)

#घोषणा PERF_FILTER_EXT_ATTR_ENTRY(_name, _var)				\
	PERF_EXT_ATTR_ENTRY(_name, ddr_perf_filter_cap_show, _var)

अटल काष्ठा attribute *ddr_perf_filter_cap_attr[] = अणु
	PERF_FILTER_EXT_ATTR_ENTRY(filter, PERF_CAP_AXI_ID_FILTER),
	PERF_FILTER_EXT_ATTR_ENTRY(enhanced_filter, PERF_CAP_AXI_ID_FILTER_ENHANCED),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ddr_perf_filter_cap_attr_group = अणु
	.name = "caps",
	.attrs = ddr_perf_filter_cap_attr,
पूर्ण;

अटल sमाप_प्रकार ddr_perf_cpumask_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ddr_pmu *pmu = dev_get_drvdata(dev);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(pmu->cpu));
पूर्ण

अटल काष्ठा device_attribute ddr_perf_cpumask_attr =
	__ATTR(cpumask, 0444, ddr_perf_cpumask_show, शून्य);

अटल काष्ठा attribute *ddr_perf_cpumask_attrs[] = अणु
	&ddr_perf_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ddr_perf_cpumask_attr_group = अणु
	.attrs = ddr_perf_cpumask_attrs,
पूर्ण;

अटल sमाप_प्रकार
ddr_pmu_event_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		   अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	वापस sysfs_emit(page, "event=0x%02llx\n", pmu_attr->id);
पूर्ण

#घोषणा IMX8_DDR_PMU_EVENT_ATTR(_name, _id)				\
	(&((काष्ठा perf_pmu_events_attr[]) अणु				\
		अणु .attr = __ATTR(_name, 0444, ddr_pmu_event_show, शून्य),\
		  .id = _id, पूर्ण						\
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *ddr_perf_events_attrs[] = अणु
	IMX8_DDR_PMU_EVENT_ATTR(cycles, EVENT_CYCLES_ID),
	IMX8_DDR_PMU_EVENT_ATTR(selfresh, 0x01),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-accesses, 0x04),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो-accesses, 0x05),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-queue-depth, 0x08),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो-queue-depth, 0x09),
	IMX8_DDR_PMU_EVENT_ATTR(lp-पढ़ो-credit-cnt, 0x10),
	IMX8_DDR_PMU_EVENT_ATTR(hp-पढ़ो-credit-cnt, 0x11),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो-credit-cnt, 0x12),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-command, 0x20),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो-command, 0x21),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-modअगरy-ग_लिखो-command, 0x22),
	IMX8_DDR_PMU_EVENT_ATTR(hp-पढ़ो, 0x23),
	IMX8_DDR_PMU_EVENT_ATTR(hp-req-nocredit, 0x24),
	IMX8_DDR_PMU_EVENT_ATTR(hp-xact-credit, 0x25),
	IMX8_DDR_PMU_EVENT_ATTR(lp-req-nocredit, 0x26),
	IMX8_DDR_PMU_EVENT_ATTR(lp-xact-credit, 0x27),
	IMX8_DDR_PMU_EVENT_ATTR(wr-xact-credit, 0x29),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-cycles, 0x2a),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो-cycles, 0x2b),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-ग_लिखो-transition, 0x30),
	IMX8_DDR_PMU_EVENT_ATTR(preअक्षरge, 0x31),
	IMX8_DDR_PMU_EVENT_ATTR(activate, 0x32),
	IMX8_DDR_PMU_EVENT_ATTR(load-mode, 0x33),
	IMX8_DDR_PMU_EVENT_ATTR(perf-mwr, 0x34),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो, 0x35),
	IMX8_DDR_PMU_EVENT_ATTR(पढ़ो-activate, 0x36),
	IMX8_DDR_PMU_EVENT_ATTR(refresh, 0x37),
	IMX8_DDR_PMU_EVENT_ATTR(ग_लिखो, 0x38),
	IMX8_DDR_PMU_EVENT_ATTR(raw-hazard, 0x39),
	IMX8_DDR_PMU_EVENT_ATTR(axid-पढ़ो, 0x41),
	IMX8_DDR_PMU_EVENT_ATTR(axid-ग_लिखो, 0x42),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ddr_perf_events_attr_group = अणु
	.name = "events",
	.attrs = ddr_perf_events_attrs,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-7");
PMU_FORMAT_ATTR(axi_id, "config1:0-15");
PMU_FORMAT_ATTR(axi_mask, "config1:16-31");

अटल काष्ठा attribute *ddr_perf_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_axi_id.attr,
	&क्रमmat_attr_axi_mask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ddr_perf_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = ddr_perf_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&ddr_perf_events_attr_group,
	&ddr_perf_क्रमmat_attr_group,
	&ddr_perf_cpumask_attr_group,
	&ddr_perf_filter_cap_attr_group,
	&ddr_perf_identअगरier_attr_group,
	शून्य,
पूर्ण;

अटल bool ddr_perf_is_filtered(काष्ठा perf_event *event)
अणु
	वापस event->attr.config == 0x41 || event->attr.config == 0x42;
पूर्ण

अटल u32 ddr_perf_filter_val(काष्ठा perf_event *event)
अणु
	वापस event->attr.config1;
पूर्ण

अटल bool ddr_perf_filters_compatible(काष्ठा perf_event *a,
					काष्ठा perf_event *b)
अणु
	अगर (!ddr_perf_is_filtered(a))
		वापस true;
	अगर (!ddr_perf_is_filtered(b))
		वापस true;
	वापस ddr_perf_filter_val(a) == ddr_perf_filter_val(b);
पूर्ण

अटल bool ddr_perf_is_enhanced_filtered(काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक filt;
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);

	filt = pmu->devtype_data->quirks & DDR_CAP_AXI_ID_FILTER_ENHANCED;
	वापस (filt == DDR_CAP_AXI_ID_FILTER_ENHANCED) &&
		ddr_perf_is_filtered(event);
पूर्ण

अटल u32 ddr_perf_alloc_counter(काष्ठा ddr_pmu *pmu, पूर्णांक event)
अणु
	पूर्णांक i;

	/*
	 * Always map cycle event to counter 0
	 * Cycles counter is dedicated क्रम cycle event
	 * can't used क्रम the other events
	 */
	अगर (event == EVENT_CYCLES_ID) अणु
		अगर (pmu->events[EVENT_CYCLES_COUNTER] == शून्य)
			वापस EVENT_CYCLES_COUNTER;
		अन्यथा
			वापस -ENOENT;
	पूर्ण

	क्रम (i = 1; i < NUM_COUNTERS; i++) अणु
		अगर (pmu->events[i] == शून्य)
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल व्योम ddr_perf_मुक्त_counter(काष्ठा ddr_pmu *pmu, पूर्णांक counter)
अणु
	pmu->events[counter] = शून्य;
पूर्ण

अटल u32 ddr_perf_पढ़ो_counter(काष्ठा ddr_pmu *pmu, पूर्णांक counter)
अणु
	काष्ठा perf_event *event = pmu->events[counter];
	व्योम __iomem *base = pmu->base;

	/*
	 * वापस bytes instead of bursts from ddr transaction क्रम
	 * axid-पढ़ो and axid-ग_लिखो event अगर PMU core supports enhanced
	 * filter.
	 */
	base += ddr_perf_is_enhanced_filtered(event) ? COUNTER_DPCR1 :
						       COUNTER_READ;
	वापस पढ़ोl_relaxed(base + counter * 4);
पूर्ण

अटल पूर्णांक ddr_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_event *sibling;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EOPNOTSUPP;

	अगर (event->cpu < 0) अणु
		dev_warn(pmu->dev, "Can't provide per-task data!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * We must NOT create groups containing mixed PMUs, although software
	 * events are acceptable (क्रम example to create a CCN group
	 * periodically पढ़ो when a hrसमयr aka cpu-घड़ी leader triggers).
	 */
	अगर (event->group_leader->pmu != event->pmu &&
			!is_software_event(event->group_leader))
		वापस -EINVAL;

	अगर (pmu->devtype_data->quirks & DDR_CAP_AXI_ID_FILTER) अणु
		अगर (!ddr_perf_filters_compatible(event, event->group_leader))
			वापस -EINVAL;
		क्रम_each_sibling_event(sibling, event->group_leader) अणु
			अगर (!ddr_perf_filters_compatible(event, sibling))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (sibling->pmu != event->pmu &&
				!is_software_event(sibling))
			वापस -EINVAL;
	पूर्ण

	event->cpu = pmu->cpu;
	hwc->idx = -1;

	वापस 0;
पूर्ण

अटल व्योम ddr_perf_counter_enable(काष्ठा ddr_pmu *pmu, पूर्णांक config,
				  पूर्णांक counter, bool enable)
अणु
	u8 reg = counter * 4 + COUNTER_CNTL;
	पूर्णांक val;

	अगर (enable) अणु
		/*
		 * cycle counter is special which should firstly ग_लिखो 0 then
		 * ग_लिखो 1 पूर्णांकo CLEAR bit to clear it. Other counters only
		 * need ग_लिखो 0 पूर्णांकo CLEAR bit and it turns out to be 1 by
		 * hardware. Below enable flow is harmless क्रम all counters.
		 */
		ग_लिखोl(0, pmu->base + reg);
		val = CNTL_EN | CNTL_CLEAR;
		val |= FIELD_PREP(CNTL_CSV_MASK, config);
		ग_लिखोl(val, pmu->base + reg);
	पूर्ण अन्यथा अणु
		/* Disable counter */
		val = पढ़ोl_relaxed(pmu->base + reg) & CNTL_EN_MASK;
		ग_लिखोl(val, pmu->base + reg);
	पूर्ण
पूर्ण

अटल bool ddr_perf_counter_overflow(काष्ठा ddr_pmu *pmu, पूर्णांक counter)
अणु
	पूर्णांक val;

	val = पढ़ोl_relaxed(pmu->base + counter * 4 + COUNTER_CNTL);

	वापस val & CNTL_OVER;
पूर्ण

अटल व्योम ddr_perf_counter_clear(काष्ठा ddr_pmu *pmu, पूर्णांक counter)
अणु
	u8 reg = counter * 4 + COUNTER_CNTL;
	पूर्णांक val;

	val = पढ़ोl_relaxed(pmu->base + reg);
	val &= ~CNTL_CLEAR;
	ग_लिखोl(val, pmu->base + reg);

	val |= CNTL_CLEAR;
	ग_लिखोl(val, pmu->base + reg);
पूर्ण

अटल व्योम ddr_perf_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 new_raw_count;
	पूर्णांक counter = hwc->idx;
	पूर्णांक ret;

	new_raw_count = ddr_perf_पढ़ो_counter(pmu, counter);
	local64_add(new_raw_count, &event->count);

	/*
	 * For legacy SoCs: event counter जारी counting when overflow,
	 *                  no need to clear the counter.
	 * For new SoCs: event counter stop counting when overflow, need
	 *               clear counter to let it count again.
	 */
	अगर (counter != EVENT_CYCLES_COUNTER) अणु
		ret = ddr_perf_counter_overflow(pmu, counter);
		अगर (ret)
			dev_warn_ratelimited(pmu->dev,  "events lost due to counter overflow (config 0x%llx)\n",
					     event->attr.config);
	पूर्ण

	/* clear counter every समय क्रम both cycle counter and event counter */
	ddr_perf_counter_clear(pmu, counter);
पूर्ण

अटल व्योम ddr_perf_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	local64_set(&hwc->prev_count, 0);

	ddr_perf_counter_enable(pmu, event->attr.config, counter, true);

	hwc->state = 0;
पूर्ण

अटल पूर्णांक ddr_perf_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter;
	पूर्णांक cfg = event->attr.config;
	पूर्णांक cfg1 = event->attr.config1;

	अगर (pmu->devtype_data->quirks & DDR_CAP_AXI_ID_FILTER) अणु
		पूर्णांक i;

		क्रम (i = 1; i < NUM_COUNTERS; i++) अणु
			अगर (pmu->events[i] &&
			    !ddr_perf_filters_compatible(event, pmu->events[i]))
				वापस -EINVAL;
		पूर्ण

		अगर (ddr_perf_is_filtered(event)) अणु
			/* revert axi id masking(axi_mask) value */
			cfg1 ^= AXI_MASKING_REVERT;
			ग_लिखोl(cfg1, pmu->base + COUNTER_DPCR1);
		पूर्ण
	पूर्ण

	counter = ddr_perf_alloc_counter(pmu, cfg);
	अगर (counter < 0) अणु
		dev_dbg(pmu->dev, "There are not enough counters\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	pmu->events[counter] = event;
	pmu->active_events++;
	hwc->idx = counter;

	hwc->state |= PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		ddr_perf_event_start(event, flags);

	वापस 0;
पूर्ण

अटल व्योम ddr_perf_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	ddr_perf_counter_enable(pmu, event->attr.config, counter, false);
	ddr_perf_event_update(event);

	hwc->state |= PERF_HES_STOPPED;
पूर्ण

अटल व्योम ddr_perf_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा ddr_pmu *pmu = to_ddr_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक counter = hwc->idx;

	ddr_perf_event_stop(event, PERF_EF_UPDATE);

	ddr_perf_मुक्त_counter(pmu, counter);
	pmu->active_events--;
	hwc->idx = -1;
पूर्ण

अटल व्योम ddr_perf_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा ddr_pmu *ddr_pmu = to_ddr_pmu(pmu);

	/* enable cycle counter अगर cycle is not active event list */
	अगर (ddr_pmu->events[EVENT_CYCLES_COUNTER] == शून्य)
		ddr_perf_counter_enable(ddr_pmu,
				      EVENT_CYCLES_ID,
				      EVENT_CYCLES_COUNTER,
				      true);
पूर्ण

अटल व्योम ddr_perf_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा ddr_pmu *ddr_pmu = to_ddr_pmu(pmu);

	अगर (ddr_pmu->events[EVENT_CYCLES_COUNTER] == शून्य)
		ddr_perf_counter_enable(ddr_pmu,
				      EVENT_CYCLES_ID,
				      EVENT_CYCLES_COUNTER,
				      false);
पूर्ण

अटल पूर्णांक ddr_perf_init(काष्ठा ddr_pmu *pmu, व्योम __iomem *base,
			 काष्ठा device *dev)
अणु
	*pmu = (काष्ठा ddr_pmu) अणु
		.pmu = (काष्ठा pmu) अणु
			.module	      = THIS_MODULE,
			.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
			.task_ctx_nr = perf_invalid_context,
			.attr_groups = attr_groups,
			.event_init  = ddr_perf_event_init,
			.add	     = ddr_perf_event_add,
			.del	     = ddr_perf_event_del,
			.start	     = ddr_perf_event_start,
			.stop	     = ddr_perf_event_stop,
			.पढ़ो	     = ddr_perf_event_update,
			.pmu_enable  = ddr_perf_pmu_enable,
			.pmu_disable = ddr_perf_pmu_disable,
		पूर्ण,
		.base = base,
		.dev = dev,
	पूर्ण;

	pmu->id = ida_simple_get(&ddr_ida, 0, 0, GFP_KERNEL);
	वापस pmu->id;
पूर्ण

अटल irqवापस_t ddr_perf_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा ddr_pmu *pmu = (काष्ठा ddr_pmu *) p;
	काष्ठा perf_event *event;

	/* all counter will stop अगर cycle counter disabled */
	ddr_perf_counter_enable(pmu,
			      EVENT_CYCLES_ID,
			      EVENT_CYCLES_COUNTER,
			      false);
	/*
	 * When the cycle counter overflows, all counters are stopped,
	 * and an IRQ is उठाओd. If any other counter overflows, it
	 * जारीs counting, and no IRQ is उठाओd. But क्रम new SoCs,
	 * such as i.MX8MP, event counter would stop when overflow, so
	 * we need use cycle counter to stop overflow of event counter.
	 *
	 * Cycles occur at least 4 बार as often as other events, so we
	 * can update all events on a cycle counter overflow and not
	 * lose events.
	 *
	 */
	क्रम (i = 0; i < NUM_COUNTERS; i++) अणु

		अगर (!pmu->events[i])
			जारी;

		event = pmu->events[i];

		ddr_perf_event_update(event);
	पूर्ण

	ddr_perf_counter_enable(pmu,
			      EVENT_CYCLES_ID,
			      EVENT_CYCLES_COUNTER,
			      true);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ddr_perf_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा ddr_pmu *pmu = hlist_entry_safe(node, काष्ठा ddr_pmu, node);
	पूर्णांक target;

	अगर (cpu != pmu->cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&pmu->pmu, cpu, target);
	pmu->cpu = target;

	WARN_ON(irq_set_affinity_hपूर्णांक(pmu->irq, cpumask_of(pmu->cpu)));

	वापस 0;
पूर्ण

अटल पूर्णांक ddr_perf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ddr_pmu *pmu;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	अक्षर *name;
	पूर्णांक num;
	पूर्णांक ret;
	पूर्णांक irq;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	np = pdev->dev.of_node;

	pmu = devm_kzalloc(&pdev->dev, माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	num = ddr_perf_init(pmu, base, &pdev->dev);

	platक्रमm_set_drvdata(pdev, pmu);

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, DDR_PERF_DEV_NAME "%d",
			      num);
	अगर (!name)
		वापस -ENOMEM;

	pmu->devtype_data = of_device_get_match_data(&pdev->dev);

	pmu->cpu = raw_smp_processor_id();
	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      DDR_CPUHP_CB_NAME,
				      शून्य,
				      ddr_perf_offline_cpu);

	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cpuhp_setup_state_multi failed\n");
		जाओ cpuhp_state_err;
	पूर्ण

	pmu->cpuhp_state = ret;

	/* Register the pmu instance क्रम cpu hotplug */
	ret = cpuhp_state_add_instance_nocalls(pmu->cpuhp_state, &pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug\n", ret);
		जाओ cpuhp_instance_err;
	पूर्ण

	/* Request irq */
	irq = of_irq_get(np, 0);
	अगर (irq < 0) अणु
		dev_err(&pdev->dev, "Failed to get irq: %d", irq);
		ret = irq;
		जाओ ddr_perf_err;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq,
					ddr_perf_irq_handler,
					IRQF_NOBALANCING | IRQF_NO_THREAD,
					DDR_CPUHP_CB_NAME,
					pmu);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Request irq failed: %d", ret);
		जाओ ddr_perf_err;
	पूर्ण

	pmu->irq = irq;
	ret = irq_set_affinity_hपूर्णांक(pmu->irq, cpumask_of(pmu->cpu));
	अगर (ret) अणु
		dev_err(pmu->dev, "Failed to set interrupt affinity!\n");
		जाओ ddr_perf_err;
	पूर्ण

	ret = perf_pmu_रेजिस्टर(&pmu->pmu, name, -1);
	अगर (ret)
		जाओ ddr_perf_err;

	वापस 0;

ddr_perf_err:
	cpuhp_state_हटाओ_instance_nocalls(pmu->cpuhp_state, &pmu->node);
cpuhp_instance_err:
	cpuhp_हटाओ_multi_state(pmu->cpuhp_state);
cpuhp_state_err:
	ida_simple_हटाओ(&ddr_ida, pmu->id);
	dev_warn(&pdev->dev, "i.MX8 DDR Perf PMU failed (%d), disabled\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ddr_perf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ddr_pmu *pmu = platक्रमm_get_drvdata(pdev);

	cpuhp_state_हटाओ_instance_nocalls(pmu->cpuhp_state, &pmu->node);
	cpuhp_हटाओ_multi_state(pmu->cpuhp_state);
	irq_set_affinity_hपूर्णांक(pmu->irq, शून्य);

	perf_pmu_unरेजिस्टर(&pmu->pmu);

	ida_simple_हटाओ(&ddr_ida, pmu->id);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_ddr_pmu_driver = अणु
	.driver         = अणु
		.name   = "imx-ddr-pmu",
		.of_match_table = imx_ddr_pmu_dt_ids,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe          = ddr_perf_probe,
	.हटाओ         = ddr_perf_हटाओ,
पूर्ण;

module_platक्रमm_driver(imx_ddr_pmu_driver);
MODULE_LICENSE("GPL v2");
