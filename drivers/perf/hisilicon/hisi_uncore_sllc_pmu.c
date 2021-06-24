<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SLLC uncore Hardware event counters support
 *
 * Copyright (C) 2020 Hisilicon Limited
 * Author: Shaokun Zhang <zhangshaokun@hisilicon.com>
 *
 * This code is based on the uncore PMUs like arm-cci and arm-ccn.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/list.h>
#समावेश <linux/smp.h>

#समावेश "hisi_uncore_pmu.h"

/* SLLC रेजिस्टर definition */
#घोषणा SLLC_INT_MASK			0x0814
#घोषणा SLLC_INT_STATUS			0x0818
#घोषणा SLLC_INT_CLEAR			0x081c
#घोषणा SLLC_PERF_CTRL			0x1c00
#घोषणा SLLC_SRCID_CTRL			0x1c04
#घोषणा SLLC_TGTID_CTRL			0x1c08
#घोषणा SLLC_EVENT_CTRL			0x1c14
#घोषणा SLLC_EVENT_TYPE0		0x1c18
#घोषणा SLLC_VERSION			0x1cf0
#घोषणा SLLC_EVENT_CNT0_L		0x1d00

#घोषणा SLLC_EVTYPE_MASK		0xff
#घोषणा SLLC_PERF_CTRL_EN		BIT(0)
#घोषणा SLLC_FILT_EN			BIT(1)
#घोषणा SLLC_TRACETAG_EN		BIT(2)
#घोषणा SLLC_SRCID_EN			BIT(4)
#घोषणा SLLC_SRCID_NONE			0x0
#घोषणा SLLC_TGTID_EN			BIT(5)
#घोषणा SLLC_TGTID_NONE			0x0
#घोषणा SLLC_TGTID_MIN_SHIFT		1
#घोषणा SLLC_TGTID_MAX_SHIFT		12
#घोषणा SLLC_SRCID_CMD_SHIFT		1
#घोषणा SLLC_SRCID_MSK_SHIFT		12
#घोषणा SLLC_NR_EVENTS			0x80

HISI_PMU_EVENT_ATTR_EXTRACTOR(tgtid_min, config1, 10, 0);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tgtid_max, config1, 21, 11);
HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_cmd, config1, 32, 22);
HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_msk, config1, 43, 33);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tracetag_en, config1, 44, 44);

अटल bool tgtid_is_valid(u32 max, u32 min)
अणु
	वापस max > 0 && max >= min;
पूर्ण

अटल व्योम hisi_sllc_pmu_enable_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_tracetag_en(event);

	अगर (tt_en) अणु
		u32 val;

		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val |= SLLC_TRACETAG_EN | SLLC_FILT_EN;
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_disable_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_tracetag_en(event);

	अगर (tt_en) अणु
		u32 val;

		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val &= ~(SLLC_TRACETAG_EN | SLLC_FILT_EN);
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_config_tgtid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 min = hisi_get_tgtid_min(event);
	u32 max = hisi_get_tgtid_max(event);

	अगर (tgtid_is_valid(max, min)) अणु
		u32 val = (max << SLLC_TGTID_MAX_SHIFT) | (min << SLLC_TGTID_MIN_SHIFT);

		ग_लिखोl(val, sllc_pmu->base + SLLC_TGTID_CTRL);
		/* Enable the tgtid */
		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val |= SLLC_TGTID_EN | SLLC_FILT_EN;
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_clear_tgtid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 min = hisi_get_tgtid_min(event);
	u32 max = hisi_get_tgtid_max(event);

	अगर (tgtid_is_valid(max, min)) अणु
		u32 val;

		ग_लिखोl(SLLC_TGTID_NONE, sllc_pmu->base + SLLC_TGTID_CTRL);
		/* Disable the tgtid */
		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val &= ~(SLLC_TGTID_EN | SLLC_FILT_EN);
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_config_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd) अणु
		u32 val, msk;

		msk = hisi_get_srcid_msk(event);
		val = (cmd << SLLC_SRCID_CMD_SHIFT) | (msk << SLLC_SRCID_MSK_SHIFT);
		ग_लिखोl(val, sllc_pmu->base + SLLC_SRCID_CTRL);
		/* Enable the srcid */
		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val |= SLLC_SRCID_EN | SLLC_FILT_EN;
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_clear_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *sllc_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd) अणु
		u32 val;

		ग_लिखोl(SLLC_SRCID_NONE, sllc_pmu->base + SLLC_SRCID_CTRL);
		/* Disable the srcid */
		val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
		val &= ~(SLLC_SRCID_EN | SLLC_FILT_EN);
		ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_enable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_sllc_pmu_enable_tracetag(event);
		hisi_sllc_pmu_config_srcid(event);
		hisi_sllc_pmu_config_tgtid(event);
	पूर्ण
पूर्ण

अटल व्योम hisi_sllc_pmu_clear_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_sllc_pmu_disable_tracetag(event);
		hisi_sllc_pmu_clear_srcid(event);
		hisi_sllc_pmu_clear_tgtid(event);
	पूर्ण
पूर्ण

अटल u32 hisi_sllc_pmu_get_counter_offset(पूर्णांक idx)
अणु
	वापस (SLLC_EVENT_CNT0_L + idx * 8);
पूर्ण

अटल u64 hisi_sllc_pmu_पढ़ो_counter(काष्ठा hisi_pmu *sllc_pmu,
				      काष्ठा hw_perf_event *hwc)
अणु
	वापस पढ़ोq(sllc_pmu->base +
		     hisi_sllc_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_sllc_pmu_ग_लिखो_counter(काष्ठा hisi_pmu *sllc_pmu,
					काष्ठा hw_perf_event *hwc, u64 val)
अणु
	ग_लिखोq(val, sllc_pmu->base +
	       hisi_sllc_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_sllc_pmu_ग_लिखो_evtype(काष्ठा hisi_pmu *sllc_pmu, पूर्णांक idx,
				       u32 type)
अणु
	u32 reg, reg_idx, shअगरt, val;

	/*
	 * Select the appropriate event select रेजिस्टर(SLLC_EVENT_TYPE0/1).
	 * There are 2 event select रेजिस्टरs क्रम the 8 hardware counters.
	 * Event code is 8-bits and क्रम the क्रमmer 4 hardware counters,
	 * SLLC_EVENT_TYPE0 is chosen. For the latter 4 hardware counters,
	 * SLLC_EVENT_TYPE1 is chosen.
	 */
	reg = SLLC_EVENT_TYPE0 + (idx / 4) * 4;
	reg_idx = idx % 4;
	shअगरt = 8 * reg_idx;

	/* Write event code to SLLC_EVENT_TYPEx Register */
	val = पढ़ोl(sllc_pmu->base + reg);
	val &= ~(SLLC_EVTYPE_MASK << shअगरt);
	val |= (type << shअगरt);
	ग_लिखोl(val, sllc_pmu->base + reg);
पूर्ण

अटल व्योम hisi_sllc_pmu_start_counters(काष्ठा hisi_pmu *sllc_pmu)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
	val |= SLLC_PERF_CTRL_EN;
	ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
पूर्ण

अटल व्योम hisi_sllc_pmu_stop_counters(काष्ठा hisi_pmu *sllc_pmu)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_PERF_CTRL);
	val &= ~(SLLC_PERF_CTRL_EN);
	ग_लिखोl(val, sllc_pmu->base + SLLC_PERF_CTRL);
पूर्ण

अटल व्योम hisi_sllc_pmu_enable_counter(काष्ठा hisi_pmu *sllc_pmu,
					 काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_EVENT_CTRL);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, sllc_pmu->base + SLLC_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_sllc_pmu_disable_counter(काष्ठा hisi_pmu *sllc_pmu,
					  काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_EVENT_CTRL);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, sllc_pmu->base + SLLC_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_sllc_pmu_enable_counter_पूर्णांक(काष्ठा hisi_pmu *sllc_pmu,
					     काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_INT_MASK);
	/* Write 0 to enable पूर्णांकerrupt */
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, sllc_pmu->base + SLLC_INT_MASK);
पूर्ण

अटल व्योम hisi_sllc_pmu_disable_counter_पूर्णांक(काष्ठा hisi_pmu *sllc_pmu,
					      काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(sllc_pmu->base + SLLC_INT_MASK);
	/* Write 1 to mask पूर्णांकerrupt */
	val |= 1 << hwc->idx;
	ग_लिखोl(val, sllc_pmu->base + SLLC_INT_MASK);
पूर्ण

अटल u32 hisi_sllc_pmu_get_पूर्णांक_status(काष्ठा hisi_pmu *sllc_pmu)
अणु
	वापस पढ़ोl(sllc_pmu->base + SLLC_INT_STATUS);
पूर्ण

अटल व्योम hisi_sllc_pmu_clear_पूर्णांक_status(काष्ठा hisi_pmu *sllc_pmu, पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, sllc_pmu->base + SLLC_INT_CLEAR);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_sllc_pmu_acpi_match[] = अणु
	अणु "HISI0263", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_sllc_pmu_acpi_match);

अटल पूर्णांक hisi_sllc_pmu_init_data(काष्ठा platक्रमm_device *pdev,
				   काष्ठा hisi_pmu *sllc_pmu)
अणु
	/*
	 * Use the SCCL_ID and the index ID to identअगरy the SLLC PMU,
	 * जबतक SCCL_ID is from MPIDR_EL1 by CPU.
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,scl-id",
				     &sllc_pmu->sccl_id)) अणु
		dev_err(&pdev->dev, "Cannot read sccl-id!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,idx-id",
				     &sllc_pmu->index_id)) अणु
		dev_err(&pdev->dev, "Cannot read idx-id!\n");
		वापस -EINVAL;
	पूर्ण

	/* SLLC PMUs only share the same SCCL */
	sllc_pmu->ccl_id = -1;

	sllc_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sllc_pmu->base)) अणु
		dev_err(&pdev->dev, "ioremap failed for sllc_pmu resource.\n");
		वापस PTR_ERR(sllc_pmu->base);
	पूर्ण

	sllc_pmu->identअगरier = पढ़ोl(sllc_pmu->base + SLLC_VERSION);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hisi_sllc_pmu_v2_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	HISI_PMU_FORMAT_ATTR(tgtid_min, "config1:0-10"),
	HISI_PMU_FORMAT_ATTR(tgtid_max, "config1:11-21"),
	HISI_PMU_FORMAT_ATTR(srcid_cmd, "config1:22-32"),
	HISI_PMU_FORMAT_ATTR(srcid_msk, "config1:33-43"),
	HISI_PMU_FORMAT_ATTR(tracetag_en, "config1:44"),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_sllc_pmu_v2_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_sllc_pmu_v2_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_sllc_pmu_v2_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(rx_req,             0x30),
	HISI_PMU_EVENT_ATTR(rx_data,            0x31),
	HISI_PMU_EVENT_ATTR(tx_req,             0x34),
	HISI_PMU_EVENT_ATTR(tx_data,            0x35),
	HISI_PMU_EVENT_ATTR(cycles,             0x09),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_sllc_pmu_v2_events_group = अणु
	.name = "events",
	.attrs = hisi_sllc_pmu_v2_events_attr,
पूर्ण;

अटल DEVICE_ATTR(cpumask, 0444, hisi_cpumask_sysfs_show, शून्य);

अटल काष्ठा attribute *hisi_sllc_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_sllc_pmu_cpumask_attr_group = अणु
	.attrs = hisi_sllc_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा device_attribute hisi_sllc_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, hisi_uncore_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *hisi_sllc_pmu_identअगरier_attrs[] = अणु
	&hisi_sllc_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group hisi_sllc_pmu_identअगरier_group = अणु
	.attrs = hisi_sllc_pmu_identअगरier_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_sllc_pmu_v2_attr_groups[] = अणु
	&hisi_sllc_pmu_v2_क्रमmat_group,
	&hisi_sllc_pmu_v2_events_group,
	&hisi_sllc_pmu_cpumask_attr_group,
	&hisi_sllc_pmu_identअगरier_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_sllc_ops = अणु
	.ग_लिखो_evtype		= hisi_sllc_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_uncore_pmu_get_event_idx,
	.start_counters		= hisi_sllc_pmu_start_counters,
	.stop_counters		= hisi_sllc_pmu_stop_counters,
	.enable_counter		= hisi_sllc_pmu_enable_counter,
	.disable_counter	= hisi_sllc_pmu_disable_counter,
	.enable_counter_पूर्णांक	= hisi_sllc_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_sllc_pmu_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_sllc_pmu_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_sllc_pmu_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_sllc_pmu_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_sllc_pmu_clear_पूर्णांक_status,
	.enable_filter		= hisi_sllc_pmu_enable_filter,
	.disable_filter		= hisi_sllc_pmu_clear_filter,
पूर्ण;

अटल पूर्णांक hisi_sllc_pmu_dev_probe(काष्ठा platक्रमm_device *pdev,
				   काष्ठा hisi_pmu *sllc_pmu)
अणु
	पूर्णांक ret;

	ret = hisi_sllc_pmu_init_data(pdev, sllc_pmu);
	अगर (ret)
		वापस ret;

	ret = hisi_uncore_pmu_init_irq(sllc_pmu, pdev);
	अगर (ret)
		वापस ret;

	sllc_pmu->pmu_events.attr_groups = hisi_sllc_pmu_v2_attr_groups;
	sllc_pmu->ops = &hisi_uncore_sllc_ops;
	sllc_pmu->check_event = SLLC_NR_EVENTS;
	sllc_pmu->counter_bits = 64;
	sllc_pmu->num_counters = 8;
	sllc_pmu->dev = &pdev->dev;
	sllc_pmu->on_cpu = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_sllc_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *sllc_pmu;
	अक्षर *name;
	पूर्णांक ret;

	sllc_pmu = devm_kzalloc(&pdev->dev, माप(*sllc_pmu), GFP_KERNEL);
	अगर (!sllc_pmu)
		वापस -ENOMEM;

	ret = hisi_sllc_pmu_dev_probe(pdev, sllc_pmu);
	अगर (ret)
		वापस ret;

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "hisi_sccl%u_sllc%u",
			      sllc_pmu->sccl_id, sllc_pmu->index_id);
	अगर (!name)
		वापस -ENOMEM;

	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE,
				       &sllc_pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug\n", ret);
		वापस ret;
	पूर्ण

	sllc_pmu->pmu = (काष्ठा pmu) अणु
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
		.attr_groups    = sllc_pmu->pmu_events.attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	ret = perf_pmu_रेजिस्टर(&sllc_pmu->pmu, name, -1);
	अगर (ret) अणु
		dev_err(sllc_pmu->dev, "PMU register failed, ret = %d\n", ret);
		cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE,
					    &sllc_pmu->node);
		irq_set_affinity_hपूर्णांक(sllc_pmu->irq, शून्य);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sllc_pmu);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_sllc_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *sllc_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&sllc_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE,
					    &sllc_pmu->node);
	irq_set_affinity_hपूर्णांक(sllc_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_sllc_pmu_driver = अणु
	.driver = अणु
		.name = "hisi_sllc_pmu",
		.acpi_match_table = hisi_sllc_pmu_acpi_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = hisi_sllc_pmu_probe,
	.हटाओ = hisi_sllc_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init hisi_sllc_pmu_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE,
				      "AP_PERF_ARM_HISI_SLLC_ONLINE",
				      hisi_uncore_pmu_online_cpu,
				      hisi_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("SLLC PMU: cpuhp state setup failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hisi_sllc_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE);

	वापस ret;
पूर्ण
module_init(hisi_sllc_pmu_module_init);

अटल व्योम __निकास hisi_sllc_pmu_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_sllc_pmu_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE);
पूर्ण
module_निकास(hisi_sllc_pmu_module_निकास);

MODULE_DESCRIPTION("HiSilicon SLLC uncore PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Shaokun Zhang <zhangshaokun@hisilicon.com>");
MODULE_AUTHOR("Qi Liu <liuqi115@huawei.com>");
