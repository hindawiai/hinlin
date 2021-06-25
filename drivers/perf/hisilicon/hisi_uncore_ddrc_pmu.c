<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SoC DDRC uncore Hardware event counters support
 *
 * Copyright (C) 2017 Hisilicon Limited
 * Author: Shaokun Zhang <zhangshaokun@hisilicon.com>
 *         Anurup M <anurup.m@huawei.com>
 *
 * This code is based on the uncore PMUs like arm-cci and arm-ccn.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/list.h>
#समावेश <linux/smp.h>

#समावेश "hisi_uncore_pmu.h"

/* DDRC रेजिस्टर definition in v1 */
#घोषणा DDRC_PERF_CTRL		0x010
#घोषणा DDRC_FLUX_WR		0x380
#घोषणा DDRC_FLUX_RD		0x384
#घोषणा DDRC_FLUX_WCMD          0x388
#घोषणा DDRC_FLUX_RCMD          0x38c
#घोषणा DDRC_PRE_CMD            0x3c0
#घोषणा DDRC_ACT_CMD            0x3c4
#घोषणा DDRC_RNK_CHG            0x3cc
#घोषणा DDRC_RW_CHG             0x3d0
#घोषणा DDRC_EVENT_CTRL         0x6C0
#घोषणा DDRC_INT_MASK		0x6c8
#घोषणा DDRC_INT_STATUS		0x6cc
#घोषणा DDRC_INT_CLEAR		0x6d0
#घोषणा DDRC_VERSION		0x710

/* DDRC रेजिस्टर definition in v2 */
#घोषणा DDRC_V2_INT_MASK	0x528
#घोषणा DDRC_V2_INT_STATUS	0x52c
#घोषणा DDRC_V2_INT_CLEAR	0x530
#घोषणा DDRC_V2_EVENT_CNT	0xe00
#घोषणा DDRC_V2_EVENT_CTRL	0xe70
#घोषणा DDRC_V2_EVENT_TYPE	0xe74
#घोषणा DDRC_V2_PERF_CTRL	0xeA0

/* DDRC has 8-counters */
#घोषणा DDRC_NR_COUNTERS	0x8
#घोषणा DDRC_V1_PERF_CTRL_EN	0x2
#घोषणा DDRC_V2_PERF_CTRL_EN	0x1
#घोषणा DDRC_V1_NR_EVENTS	0x7
#घोषणा DDRC_V2_NR_EVENTS	0x90

/*
 * For PMU v1, there are eight-events and every event has been mapped
 * to fixed-purpose counters which रेजिस्टर offset is not consistent.
 * Thereक्रमe there is no ग_लिखो event type and we assume that event
 * code (0 to 7) is equal to counter index in PMU driver.
 */
#घोषणा GET_DDRC_EVENTID(hwc)	(hwc->config_base & 0x7)

अटल स्थिर u32 ddrc_reg_off[] = अणु
	DDRC_FLUX_WR, DDRC_FLUX_RD, DDRC_FLUX_WCMD, DDRC_FLUX_RCMD,
	DDRC_PRE_CMD, DDRC_ACT_CMD, DDRC_RNK_CHG, DDRC_RW_CHG
पूर्ण;

/*
 * Select the counter रेजिस्टर offset using the counter index.
 * In PMU v1, there are no programmable counter, the count
 * is पढ़ो क्रमm the statistics counter रेजिस्टर itself.
 */
अटल u32 hisi_ddrc_pmu_v1_get_counter_offset(पूर्णांक cntr_idx)
अणु
	वापस ddrc_reg_off[cntr_idx];
पूर्ण

अटल u32 hisi_ddrc_pmu_v2_get_counter_offset(पूर्णांक cntr_idx)
अणु
	वापस DDRC_V2_EVENT_CNT + cntr_idx * 8;
पूर्ण

अटल u64 hisi_ddrc_pmu_v1_पढ़ो_counter(काष्ठा hisi_pmu *ddrc_pmu,
				      काष्ठा hw_perf_event *hwc)
अणु
	वापस पढ़ोl(ddrc_pmu->base +
		     hisi_ddrc_pmu_v1_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_ग_लिखो_counter(काष्ठा hisi_pmu *ddrc_pmu,
					काष्ठा hw_perf_event *hwc, u64 val)
अणु
	ग_लिखोl((u32)val,
	       ddrc_pmu->base + hisi_ddrc_pmu_v1_get_counter_offset(hwc->idx));
पूर्ण

अटल u64 hisi_ddrc_pmu_v2_पढ़ो_counter(काष्ठा hisi_pmu *ddrc_pmu,
					 काष्ठा hw_perf_event *hwc)
अणु
	वापस पढ़ोq(ddrc_pmu->base +
		     hisi_ddrc_pmu_v2_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_ग_लिखो_counter(काष्ठा hisi_pmu *ddrc_pmu,
					   काष्ठा hw_perf_event *hwc, u64 val)
अणु
	ग_लिखोq(val,
	       ddrc_pmu->base + hisi_ddrc_pmu_v2_get_counter_offset(hwc->idx));
पूर्ण

/*
 * For DDRC PMU v1, event has been mapped to fixed-purpose counter by hardware,
 * so there is no need to ग_लिखो event type, जबतक it is programmable counter in
 * PMU v2.
 */
अटल व्योम hisi_ddrc_pmu_ग_लिखो_evtype(काष्ठा hisi_pmu *hha_pmu, पूर्णांक idx,
				       u32 type)
अणु
	u32 offset;

	अगर (hha_pmu->identअगरier >= HISI_PMU_V2) अणु
		offset = DDRC_V2_EVENT_TYPE + 4 * idx;
		ग_लिखोl(type, hha_pmu->base + offset);
	पूर्ण
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_start_counters(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	u32 val;

	/* Set perf_enable in DDRC_PERF_CTRL to start event counting */
	val = पढ़ोl(ddrc_pmu->base + DDRC_PERF_CTRL);
	val |= DDRC_V1_PERF_CTRL_EN;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_PERF_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_stop_counters(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	u32 val;

	/* Clear perf_enable in DDRC_PERF_CTRL to stop event counting */
	val = पढ़ोl(ddrc_pmu->base + DDRC_PERF_CTRL);
	val &= ~DDRC_V1_PERF_CTRL_EN;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_PERF_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_enable_counter(काष्ठा hisi_pmu *ddrc_pmu,
					    काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Set counter index(event code) in DDRC_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(ddrc_pmu->base + DDRC_EVENT_CTRL);
	val |= (1 << GET_DDRC_EVENTID(hwc));
	ग_लिखोl(val, ddrc_pmu->base + DDRC_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_disable_counter(काष्ठा hisi_pmu *ddrc_pmu,
					     काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Clear counter index(event code) in DDRC_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(ddrc_pmu->base + DDRC_EVENT_CTRL);
	val &= ~(1 << GET_DDRC_EVENTID(hwc));
	ग_लिखोl(val, ddrc_pmu->base + DDRC_EVENT_CTRL);
पूर्ण

अटल पूर्णांक hisi_ddrc_pmu_v1_get_event_idx(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *ddrc_pmu = to_hisi_pmu(event->pmu);
	अचिन्हित दीर्घ *used_mask = ddrc_pmu->pmu_events.used_mask;
	काष्ठा hw_perf_event *hwc = &event->hw;
	/* For DDRC PMU, we use event code as counter index */
	पूर्णांक idx = GET_DDRC_EVENTID(hwc);

	अगर (test_bit(idx, used_mask))
		वापस -EAGAIN;

	set_bit(idx, used_mask);

	वापस idx;
पूर्ण

अटल पूर्णांक hisi_ddrc_pmu_v2_get_event_idx(काष्ठा perf_event *event)
अणु
	वापस hisi_uncore_pmu_get_event_idx(event);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_start_counters(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_PERF_CTRL);
	val |= DDRC_V2_PERF_CTRL_EN;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_PERF_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_stop_counters(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_PERF_CTRL);
	val &= ~DDRC_V2_PERF_CTRL_EN;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_PERF_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_enable_counter(काष्ठा hisi_pmu *ddrc_pmu,
					    काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_EVENT_CTRL);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_disable_counter(काष्ठा hisi_pmu *ddrc_pmu,
					     काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_EVENT_CTRL);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_enable_counter_पूर्णांक(काष्ठा hisi_pmu *ddrc_pmu,
						काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 0 to enable पूर्णांकerrupt */
	val = पढ़ोl(ddrc_pmu->base + DDRC_INT_MASK);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, ddrc_pmu->base + DDRC_INT_MASK);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_disable_counter_पूर्णांक(काष्ठा hisi_pmu *ddrc_pmu,
						 काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 1 to mask पूर्णांकerrupt */
	val = पढ़ोl(ddrc_pmu->base + DDRC_INT_MASK);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_INT_MASK);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_enable_counter_पूर्णांक(काष्ठा hisi_pmu *ddrc_pmu,
						काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_INT_MASK);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_INT_MASK);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_disable_counter_पूर्णांक(काष्ठा hisi_pmu *ddrc_pmu,
						काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(ddrc_pmu->base + DDRC_V2_INT_MASK);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, ddrc_pmu->base + DDRC_V2_INT_MASK);
पूर्ण

अटल u32 hisi_ddrc_pmu_v1_get_पूर्णांक_status(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	वापस पढ़ोl(ddrc_pmu->base + DDRC_INT_STATUS);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v1_clear_पूर्णांक_status(काष्ठा hisi_pmu *ddrc_pmu,
					      पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, ddrc_pmu->base + DDRC_INT_CLEAR);
पूर्ण

अटल u32 hisi_ddrc_pmu_v2_get_पूर्णांक_status(काष्ठा hisi_pmu *ddrc_pmu)
अणु
	वापस पढ़ोl(ddrc_pmu->base + DDRC_V2_INT_STATUS);
पूर्ण

अटल व्योम hisi_ddrc_pmu_v2_clear_पूर्णांक_status(काष्ठा hisi_pmu *ddrc_pmu,
					      पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, ddrc_pmu->base + DDRC_V2_INT_CLEAR);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_ddrc_pmu_acpi_match[] = अणु
	अणु "HISI0233", पूर्ण,
	अणु "HISI0234", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_ddrc_pmu_acpi_match);

अटल पूर्णांक hisi_ddrc_pmu_init_data(काष्ठा platक्रमm_device *pdev,
				   काष्ठा hisi_pmu *ddrc_pmu)
अणु
	/*
	 * Use the SCCL_ID and DDRC channel ID to identअगरy the
	 * DDRC PMU, जबतक SCCL_ID is in MPIDR[aff2].
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,ch-id",
				     &ddrc_pmu->index_id)) अणु
		dev_err(&pdev->dev, "Can not read ddrc channel-id!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,scl-id",
				     &ddrc_pmu->sccl_id)) अणु
		dev_err(&pdev->dev, "Can not read ddrc sccl-id!\n");
		वापस -EINVAL;
	पूर्ण
	/* DDRC PMUs only share the same SCCL */
	ddrc_pmu->ccl_id = -1;

	ddrc_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ddrc_pmu->base)) अणु
		dev_err(&pdev->dev, "ioremap failed for ddrc_pmu resource\n");
		वापस PTR_ERR(ddrc_pmu->base);
	पूर्ण

	ddrc_pmu->identअगरier = पढ़ोl(ddrc_pmu->base + DDRC_VERSION);
	अगर (ddrc_pmu->identअगरier >= HISI_PMU_V2) अणु
		अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,sub-id",
					     &ddrc_pmu->sub_id)) अणु
			dev_err(&pdev->dev, "Can not read sub-id!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hisi_ddrc_pmu_v1_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-4"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_v1_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_ddrc_pmu_v1_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_ddrc_pmu_v2_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_v2_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_ddrc_pmu_v2_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_ddrc_pmu_v1_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(flux_wr,		0x00),
	HISI_PMU_EVENT_ATTR(flux_rd,		0x01),
	HISI_PMU_EVENT_ATTR(flux_wcmd,		0x02),
	HISI_PMU_EVENT_ATTR(flux_rcmd,		0x03),
	HISI_PMU_EVENT_ATTR(pre_cmd,		0x04),
	HISI_PMU_EVENT_ATTR(act_cmd,		0x05),
	HISI_PMU_EVENT_ATTR(rnk_chg,		0x06),
	HISI_PMU_EVENT_ATTR(rw_chg,		0x07),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_v1_events_group = अणु
	.name = "events",
	.attrs = hisi_ddrc_pmu_v1_events_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_ddrc_pmu_v2_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(cycles,		0x00),
	HISI_PMU_EVENT_ATTR(flux_wr,		0x83),
	HISI_PMU_EVENT_ATTR(flux_rd,		0x84),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_v2_events_group = अणु
	.name = "events",
	.attrs = hisi_ddrc_pmu_v2_events_attr,
पूर्ण;

अटल DEVICE_ATTR(cpumask, 0444, hisi_cpumask_sysfs_show, शून्य);

अटल काष्ठा attribute *hisi_ddrc_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_cpumask_attr_group = अणु
	.attrs = hisi_ddrc_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा device_attribute hisi_ddrc_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, hisi_uncore_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *hisi_ddrc_pmu_identअगरier_attrs[] = अणु
	&hisi_ddrc_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_ddrc_pmu_identअगरier_group = अणु
	.attrs = hisi_ddrc_pmu_identअगरier_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_ddrc_pmu_v1_attr_groups[] = अणु
	&hisi_ddrc_pmu_v1_क्रमmat_group,
	&hisi_ddrc_pmu_v1_events_group,
	&hisi_ddrc_pmu_cpumask_attr_group,
	&hisi_ddrc_pmu_identअगरier_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_ddrc_pmu_v2_attr_groups[] = अणु
	&hisi_ddrc_pmu_v2_क्रमmat_group,
	&hisi_ddrc_pmu_v2_events_group,
	&hisi_ddrc_pmu_cpumask_attr_group,
	&hisi_ddrc_pmu_identअगरier_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_ddrc_v1_ops = अणु
	.ग_लिखो_evtype           = hisi_ddrc_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_ddrc_pmu_v1_get_event_idx,
	.start_counters		= hisi_ddrc_pmu_v1_start_counters,
	.stop_counters		= hisi_ddrc_pmu_v1_stop_counters,
	.enable_counter		= hisi_ddrc_pmu_v1_enable_counter,
	.disable_counter	= hisi_ddrc_pmu_v1_disable_counter,
	.enable_counter_पूर्णांक	= hisi_ddrc_pmu_v1_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_ddrc_pmu_v1_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_ddrc_pmu_v1_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_ddrc_pmu_v1_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_ddrc_pmu_v1_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_ddrc_pmu_v1_clear_पूर्णांक_status,
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_ddrc_v2_ops = अणु
	.ग_लिखो_evtype           = hisi_ddrc_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_ddrc_pmu_v2_get_event_idx,
	.start_counters		= hisi_ddrc_pmu_v2_start_counters,
	.stop_counters		= hisi_ddrc_pmu_v2_stop_counters,
	.enable_counter		= hisi_ddrc_pmu_v2_enable_counter,
	.disable_counter	= hisi_ddrc_pmu_v2_disable_counter,
	.enable_counter_पूर्णांक	= hisi_ddrc_pmu_v2_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_ddrc_pmu_v2_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_ddrc_pmu_v2_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_ddrc_pmu_v2_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_ddrc_pmu_v2_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_ddrc_pmu_v2_clear_पूर्णांक_status,
पूर्ण;

अटल पूर्णांक hisi_ddrc_pmu_dev_probe(काष्ठा platक्रमm_device *pdev,
				   काष्ठा hisi_pmu *ddrc_pmu)
अणु
	पूर्णांक ret;

	ret = hisi_ddrc_pmu_init_data(pdev, ddrc_pmu);
	अगर (ret)
		वापस ret;

	ret = hisi_uncore_pmu_init_irq(ddrc_pmu, pdev);
	अगर (ret)
		वापस ret;

	अगर (ddrc_pmu->identअगरier >= HISI_PMU_V2) अणु
		ddrc_pmu->counter_bits = 48;
		ddrc_pmu->check_event = DDRC_V2_NR_EVENTS;
		ddrc_pmu->pmu_events.attr_groups = hisi_ddrc_pmu_v2_attr_groups;
		ddrc_pmu->ops = &hisi_uncore_ddrc_v2_ops;
	पूर्ण अन्यथा अणु
		ddrc_pmu->counter_bits = 32;
		ddrc_pmu->check_event = DDRC_V1_NR_EVENTS;
		ddrc_pmu->pmu_events.attr_groups = hisi_ddrc_pmu_v1_attr_groups;
		ddrc_pmu->ops = &hisi_uncore_ddrc_v1_ops;
	पूर्ण

	ddrc_pmu->num_counters = DDRC_NR_COUNTERS;
	ddrc_pmu->dev = &pdev->dev;
	ddrc_pmu->on_cpu = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_ddrc_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *ddrc_pmu;
	अक्षर *name;
	पूर्णांक ret;

	ddrc_pmu = devm_kzalloc(&pdev->dev, माप(*ddrc_pmu), GFP_KERNEL);
	अगर (!ddrc_pmu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddrc_pmu);

	ret = hisi_ddrc_pmu_dev_probe(pdev, ddrc_pmu);
	अगर (ret)
		वापस ret;

	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE,
				       &ddrc_pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug;\n", ret);
		वापस ret;
	पूर्ण

	अगर (ddrc_pmu->identअगरier >= HISI_PMU_V2)
		name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				      "hisi_sccl%u_ddrc%u_%u",
				      ddrc_pmu->sccl_id, ddrc_pmu->index_id,
				      ddrc_pmu->sub_id);
	अन्यथा
		name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
				      "hisi_sccl%u_ddrc%u", ddrc_pmu->sccl_id,
				      ddrc_pmu->index_id);

	ddrc_pmu->pmu = (काष्ठा pmu) अणु
		.name		= name,
		.module		= THIS_MODULE,
		.task_ctx_nr	= perf_invalid_context,
		.event_init	= hisi_uncore_pmu_event_init,
		.pmu_enable	= hisi_uncore_pmu_enable,
		.pmu_disable	= hisi_uncore_pmu_disable,
		.add		= hisi_uncore_pmu_add,
		.del		= hisi_uncore_pmu_del,
		.start		= hisi_uncore_pmu_start,
		.stop		= hisi_uncore_pmu_stop,
		.पढ़ो		= hisi_uncore_pmu_पढ़ो,
		.attr_groups	= ddrc_pmu->pmu_events.attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	ret = perf_pmu_रेजिस्टर(&ddrc_pmu->pmu, name, -1);
	अगर (ret) अणु
		dev_err(ddrc_pmu->dev, "DDRC PMU register failed!\n");
		cpuhp_state_हटाओ_instance_nocalls(
			CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE, &ddrc_pmu->node);
		irq_set_affinity_hपूर्णांक(ddrc_pmu->irq, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_ddrc_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *ddrc_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&ddrc_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE,
					    &ddrc_pmu->node);
	irq_set_affinity_hपूर्णांक(ddrc_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_ddrc_pmu_driver = अणु
	.driver = अणु
		.name = "hisi_ddrc_pmu",
		.acpi_match_table = ACPI_PTR(hisi_ddrc_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = hisi_ddrc_pmu_probe,
	.हटाओ = hisi_ddrc_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init hisi_ddrc_pmu_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE,
				      "AP_PERF_ARM_HISI_DDRC_ONLINE",
				      hisi_uncore_pmu_online_cpu,
				      hisi_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("DDRC PMU: setup hotplug, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hisi_ddrc_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE);

	वापस ret;
पूर्ण
module_init(hisi_ddrc_pmu_module_init);

अटल व्योम __निकास hisi_ddrc_pmu_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_ddrc_pmu_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE);

पूर्ण
module_निकास(hisi_ddrc_pmu_module_निकास);

MODULE_DESCRIPTION("HiSilicon SoC DDRC uncore PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Shaokun Zhang <zhangshaokun@hisilicon.com>");
MODULE_AUTHOR("Anurup M <anurup.m@huawei.com>");
