<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon PA uncore Hardware event counters support
 *
 * Copyright (C) 2020 HiSilicon Limited
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

/* PA रेजिस्टर definition */
#घोषणा PA_PERF_CTRL			0x1c00
#घोषणा PA_EVENT_CTRL			0x1c04
#घोषणा PA_TT_CTRL			0x1c08
#घोषणा PA_TGTID_CTRL			0x1c14
#घोषणा PA_SRCID_CTRL			0x1c18
#घोषणा PA_INT_MASK			0x1c70
#घोषणा PA_INT_STATUS			0x1c78
#घोषणा PA_INT_CLEAR			0x1c7c
#घोषणा PA_EVENT_TYPE0			0x1c80
#घोषणा PA_PMU_VERSION			0x1cf0
#घोषणा PA_EVENT_CNT0_L			0x1f00

#घोषणा PA_EVTYPE_MASK			0xff
#घोषणा PA_NR_COUNTERS			0x8
#घोषणा PA_PERF_CTRL_EN			BIT(0)
#घोषणा PA_TRACETAG_EN			BIT(4)
#घोषणा PA_TGTID_EN			BIT(11)
#घोषणा PA_SRCID_EN			BIT(11)
#घोषणा PA_TGTID_NONE			0
#घोषणा PA_SRCID_NONE			0
#घोषणा PA_TGTID_MSK_SHIFT		12
#घोषणा PA_SRCID_MSK_SHIFT		12

HISI_PMU_EVENT_ATTR_EXTRACTOR(tgtid_cmd, config1, 10, 0);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tgtid_msk, config1, 21, 11);
HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_cmd, config1, 32, 22);
HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_msk, config1, 43, 33);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tracetag_en, config1, 44, 44);

अटल व्योम hisi_pa_pmu_enable_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_tracetag_en(event);

	अगर (tt_en) अणु
		u32 val;

		val = पढ़ोl(pa_pmu->base + PA_TT_CTRL);
		val |= PA_TRACETAG_EN;
		ग_लिखोl(val, pa_pmu->base + PA_TT_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_pa_pmu_clear_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_tracetag_en(event);

	अगर (tt_en) अणु
		u32 val;

		val = पढ़ोl(pa_pmu->base + PA_TT_CTRL);
		val &= ~PA_TRACETAG_EN;
		ग_लिखोl(val, pa_pmu->base + PA_TT_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_pa_pmu_config_tgtid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_tgtid_cmd(event);

	अगर (cmd) अणु
		u32 msk = hisi_get_tgtid_msk(event);
		u32 val = cmd | PA_TGTID_EN | (msk << PA_TGTID_MSK_SHIFT);

		ग_लिखोl(val, pa_pmu->base + PA_TGTID_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_pa_pmu_clear_tgtid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_tgtid_cmd(event);

	अगर (cmd)
		ग_लिखोl(PA_TGTID_NONE, pa_pmu->base + PA_TGTID_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_config_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd) अणु
		u32 msk = hisi_get_srcid_msk(event);
		u32 val = cmd | PA_SRCID_EN | (msk << PA_SRCID_MSK_SHIFT);

		ग_लिखोl(val, pa_pmu->base + PA_SRCID_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_pa_pmu_clear_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *pa_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd)
		ग_लिखोl(PA_SRCID_NONE, pa_pmu->base + PA_SRCID_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_enable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_pa_pmu_enable_tracetag(event);
		hisi_pa_pmu_config_srcid(event);
		hisi_pa_pmu_config_tgtid(event);
	पूर्ण
पूर्ण

अटल व्योम hisi_pa_pmu_disable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_pa_pmu_clear_tgtid(event);
		hisi_pa_pmu_clear_srcid(event);
		hisi_pa_pmu_clear_tracetag(event);
	पूर्ण
पूर्ण

अटल u32 hisi_pa_pmu_get_counter_offset(पूर्णांक idx)
अणु
	वापस (PA_EVENT_CNT0_L + idx * 8);
पूर्ण

अटल u64 hisi_pa_pmu_पढ़ो_counter(काष्ठा hisi_pmu *pa_pmu,
				    काष्ठा hw_perf_event *hwc)
अणु
	वापस पढ़ोq(pa_pmu->base + hisi_pa_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_pa_pmu_ग_लिखो_counter(काष्ठा hisi_pmu *pa_pmu,
				      काष्ठा hw_perf_event *hwc, u64 val)
अणु
	ग_लिखोq(val, pa_pmu->base + hisi_pa_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_pa_pmu_ग_लिखो_evtype(काष्ठा hisi_pmu *pa_pmu, पूर्णांक idx,
				     u32 type)
अणु
	u32 reg, reg_idx, shअगरt, val;

	/*
	 * Select the appropriate event select रेजिस्टर(PA_EVENT_TYPE0/1).
	 * There are 2 event select रेजिस्टरs क्रम the 8 hardware counters.
	 * Event code is 8-bits and क्रम the क्रमmer 4 hardware counters,
	 * PA_EVENT_TYPE0 is chosen. For the latter 4 hardware counters,
	 * PA_EVENT_TYPE1 is chosen.
	 */
	reg = PA_EVENT_TYPE0 + (idx / 4) * 4;
	reg_idx = idx % 4;
	shअगरt = 8 * reg_idx;

	/* Write event code to pa_EVENT_TYPEx Register */
	val = पढ़ोl(pa_pmu->base + reg);
	val &= ~(PA_EVTYPE_MASK << shअगरt);
	val |= (type << shअगरt);
	ग_लिखोl(val, pa_pmu->base + reg);
पूर्ण

अटल व्योम hisi_pa_pmu_start_counters(काष्ठा hisi_pmu *pa_pmu)
अणु
	u32 val;

	val = पढ़ोl(pa_pmu->base + PA_PERF_CTRL);
	val |= PA_PERF_CTRL_EN;
	ग_लिखोl(val, pa_pmu->base + PA_PERF_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_stop_counters(काष्ठा hisi_pmu *pa_pmu)
अणु
	u32 val;

	val = पढ़ोl(pa_pmu->base + PA_PERF_CTRL);
	val &= ~(PA_PERF_CTRL_EN);
	ग_लिखोl(val, pa_pmu->base + PA_PERF_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_enable_counter(काष्ठा hisi_pmu *pa_pmu,
				       काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Enable counter index in PA_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(pa_pmu->base + PA_EVENT_CTRL);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, pa_pmu->base + PA_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_disable_counter(काष्ठा hisi_pmu *pa_pmu,
					काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Clear counter index in PA_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(pa_pmu->base + PA_EVENT_CTRL);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, pa_pmu->base + PA_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_pa_pmu_enable_counter_पूर्णांक(काष्ठा hisi_pmu *pa_pmu,
					   काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 0 to enable पूर्णांकerrupt */
	val = पढ़ोl(pa_pmu->base + PA_INT_MASK);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, pa_pmu->base + PA_INT_MASK);
पूर्ण

अटल व्योम hisi_pa_pmu_disable_counter_पूर्णांक(काष्ठा hisi_pmu *pa_pmu,
					    काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 1 to mask पूर्णांकerrupt */
	val = पढ़ोl(pa_pmu->base + PA_INT_MASK);
	val |= 1 << hwc->idx;
	ग_लिखोl(val, pa_pmu->base + PA_INT_MASK);
पूर्ण

अटल u32 hisi_pa_pmu_get_पूर्णांक_status(काष्ठा hisi_pmu *pa_pmu)
अणु
	वापस पढ़ोl(pa_pmu->base + PA_INT_STATUS);
पूर्ण

अटल व्योम hisi_pa_pmu_clear_पूर्णांक_status(काष्ठा hisi_pmu *pa_pmu, पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, pa_pmu->base + PA_INT_CLEAR);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_pa_pmu_acpi_match[] = अणु
	अणु "HISI0273", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_pa_pmu_acpi_match);

अटल पूर्णांक hisi_pa_pmu_init_data(काष्ठा platक्रमm_device *pdev,
				   काष्ठा hisi_pmu *pa_pmu)
अणु
	/*
	 * Use the SCCL_ID and the index ID to identअगरy the PA PMU,
	 * जबतक SCCL_ID is the nearst SCCL_ID from this SICL and
	 * CPU core is chosen from this SCCL to manage this PMU.
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,scl-id",
				     &pa_pmu->sccl_id)) अणु
		dev_err(&pdev->dev, "Cannot read sccl-id!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,idx-id",
				     &pa_pmu->index_id)) अणु
		dev_err(&pdev->dev, "Cannot read idx-id!\n");
		वापस -EINVAL;
	पूर्ण

	pa_pmu->ccl_id = -1;

	pa_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pa_pmu->base)) अणु
		dev_err(&pdev->dev, "ioremap failed for pa_pmu resource.\n");
		वापस PTR_ERR(pa_pmu->base);
	पूर्ण

	pa_pmu->identअगरier = पढ़ोl(pa_pmu->base + PA_PMU_VERSION);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hisi_pa_pmu_v2_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	HISI_PMU_FORMAT_ATTR(tgtid_cmd, "config1:0-10"),
	HISI_PMU_FORMAT_ATTR(tgtid_msk, "config1:11-21"),
	HISI_PMU_FORMAT_ATTR(srcid_cmd, "config1:22-32"),
	HISI_PMU_FORMAT_ATTR(srcid_msk, "config1:33-43"),
	HISI_PMU_FORMAT_ATTR(tracetag_en, "config1:44"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_pa_pmu_v2_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_pa_pmu_v2_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_pa_pmu_v2_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(rx_req,		0x40),
	HISI_PMU_EVENT_ATTR(tx_req,             0x5c),
	HISI_PMU_EVENT_ATTR(cycle,		0x78),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_pa_pmu_v2_events_group = अणु
	.name = "events",
	.attrs = hisi_pa_pmu_v2_events_attr,
पूर्ण;

अटल DEVICE_ATTR(cpumask, 0444, hisi_cpumask_sysfs_show, शून्य);

अटल काष्ठा attribute *hisi_pa_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_pa_pmu_cpumask_attr_group = अणु
	.attrs = hisi_pa_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा device_attribute hisi_pa_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, hisi_uncore_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *hisi_pa_pmu_identअगरier_attrs[] = अणु
	&hisi_pa_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group hisi_pa_pmu_identअगरier_group = अणु
	.attrs = hisi_pa_pmu_identअगरier_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_pa_pmu_v2_attr_groups[] = अणु
	&hisi_pa_pmu_v2_क्रमmat_group,
	&hisi_pa_pmu_v2_events_group,
	&hisi_pa_pmu_cpumask_attr_group,
	&hisi_pa_pmu_identअगरier_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_pa_ops = अणु
	.ग_लिखो_evtype		= hisi_pa_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_uncore_pmu_get_event_idx,
	.start_counters		= hisi_pa_pmu_start_counters,
	.stop_counters		= hisi_pa_pmu_stop_counters,
	.enable_counter		= hisi_pa_pmu_enable_counter,
	.disable_counter	= hisi_pa_pmu_disable_counter,
	.enable_counter_पूर्णांक	= hisi_pa_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_pa_pmu_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_pa_pmu_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_pa_pmu_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_pa_pmu_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_pa_pmu_clear_पूर्णांक_status,
	.enable_filter		= hisi_pa_pmu_enable_filter,
	.disable_filter		= hisi_pa_pmu_disable_filter,
पूर्ण;

अटल पूर्णांक hisi_pa_pmu_dev_probe(काष्ठा platक्रमm_device *pdev,
				 काष्ठा hisi_pmu *pa_pmu)
अणु
	पूर्णांक ret;

	ret = hisi_pa_pmu_init_data(pdev, pa_pmu);
	अगर (ret)
		वापस ret;

	ret = hisi_uncore_pmu_init_irq(pa_pmu, pdev);
	अगर (ret)
		वापस ret;

	pa_pmu->pmu_events.attr_groups = hisi_pa_pmu_v2_attr_groups;
	pa_pmu->num_counters = PA_NR_COUNTERS;
	pa_pmu->ops = &hisi_uncore_pa_ops;
	pa_pmu->check_event = 0xB0;
	pa_pmu->counter_bits = 64;
	pa_pmu->dev = &pdev->dev;
	pa_pmu->on_cpu = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_pa_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *pa_pmu;
	अक्षर *name;
	पूर्णांक ret;

	pa_pmu = devm_kzalloc(&pdev->dev, माप(*pa_pmu), GFP_KERNEL);
	अगर (!pa_pmu)
		वापस -ENOMEM;

	ret = hisi_pa_pmu_dev_probe(pdev, pa_pmu);
	अगर (ret)
		वापस ret;
	/*
	 * PA is attached in SICL and the CPU core is chosen to manage this
	 * PMU which is the nearest SCCL, जबतक its SCCL_ID is greater than
	 * one with the SICL_ID.
	 */
	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "hisi_sicl%u_pa%u",
			      pa_pmu->sccl_id - 1, pa_pmu->index_id);
	अगर (!name)
		वापस -ENOMEM;

	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE,
				       &pa_pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug\n", ret);
		वापस ret;
	पूर्ण

	pa_pmu->pmu = (काष्ठा pmu) अणु
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
		.attr_groups    = pa_pmu->pmu_events.attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	ret = perf_pmu_रेजिस्टर(&pa_pmu->pmu, name, -1);
	अगर (ret) अणु
		dev_err(pa_pmu->dev, "PMU register failed, ret = %d\n", ret);
		cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE,
					    &pa_pmu->node);
		irq_set_affinity_hपूर्णांक(pa_pmu->irq, शून्य);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pa_pmu);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_pa_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *pa_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&pa_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE,
					    &pa_pmu->node);
	irq_set_affinity_hपूर्णांक(pa_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_pa_pmu_driver = अणु
	.driver = अणु
		.name = "hisi_pa_pmu",
		.acpi_match_table = hisi_pa_pmu_acpi_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = hisi_pa_pmu_probe,
	.हटाओ = hisi_pa_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init hisi_pa_pmu_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE,
				      "AP_PERF_ARM_HISI_PA_ONLINE",
				      hisi_uncore_pmu_online_cpu,
				      hisi_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("PA PMU: cpuhp state setup failed, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hisi_pa_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE);

	वापस ret;
पूर्ण
module_init(hisi_pa_pmu_module_init);

अटल व्योम __निकास hisi_pa_pmu_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_pa_pmu_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_PA_ONLINE);
पूर्ण
module_निकास(hisi_pa_pmu_module_निकास);

MODULE_DESCRIPTION("HiSilicon Protocol Adapter uncore PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Shaokun Zhang <zhangshaokun@hisilicon.com>");
MODULE_AUTHOR("Qi Liu <liuqi115@huawei.com>");
