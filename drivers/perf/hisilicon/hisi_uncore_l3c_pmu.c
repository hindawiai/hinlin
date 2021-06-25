<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SoC L3C uncore Hardware event counters support
 *
 * Copyright (C) 2017 Hisilicon Limited
 * Author: Anurup M <anurup.m@huawei.com>
 *         Shaokun Zhang <zhangshaokun@hisilicon.com>
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

/* L3C रेजिस्टर definition */
#घोषणा L3C_PERF_CTRL		0x0408
#घोषणा L3C_INT_MASK		0x0800
#घोषणा L3C_INT_STATUS		0x0808
#घोषणा L3C_INT_CLEAR		0x080c
#घोषणा L3C_CORE_CTRL           0x1b04
#घोषणा L3C_TRACETAG_CTRL       0x1b20
#घोषणा L3C_DATSRC_TYPE         0x1b48
#घोषणा L3C_DATSRC_CTRL         0x1bf0
#घोषणा L3C_EVENT_CTRL	        0x1c00
#घोषणा L3C_VERSION		0x1cf0
#घोषणा L3C_EVENT_TYPE0		0x1d00
/*
 * If the HW version only supports a 48-bit counter, then
 * bits [63:48] are reserved, which are Read-As-Zero and
 * Writes-Ignored.
 */
#घोषणा L3C_CNTR0_LOWER		0x1e00

/* L3C has 8-counters */
#घोषणा L3C_NR_COUNTERS		0x8

#घोषणा L3C_PERF_CTRL_EN	0x10000
#घोषणा L3C_TRACETAG_EN		BIT(31)
#घोषणा L3C_TRACETAG_REQ_SHIFT	7
#घोषणा L3C_TRACETAG_MARK_EN	BIT(0)
#घोषणा L3C_TRACETAG_REQ_EN	(L3C_TRACETAG_MARK_EN | BIT(2))
#घोषणा L3C_TRACETAG_CORE_EN	(L3C_TRACETAG_MARK_EN | BIT(3))
#घोषणा L3C_CORE_EN		BIT(20)
#घोषणा L3C_COER_NONE		0x0
#घोषणा L3C_DATSRC_MASK		0xFF
#घोषणा L3C_DATSRC_SKT_EN	BIT(23)
#घोषणा L3C_DATSRC_NONE		0x0
#घोषणा L3C_EVTYPE_NONE		0xff
#घोषणा L3C_V1_NR_EVENTS	0x59
#घोषणा L3C_V2_NR_EVENTS	0xFF

HISI_PMU_EVENT_ATTR_EXTRACTOR(tt_core, config1, 7, 0);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tt_req, config1, 10, 8);
HISI_PMU_EVENT_ATTR_EXTRACTOR(datasrc_cfg, config1, 15, 11);
HISI_PMU_EVENT_ATTR_EXTRACTOR(datasrc_skt, config1, 16, 16);

अटल व्योम hisi_l3c_pmu_config_req_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 tt_req = hisi_get_tt_req(event);

	अगर (tt_req) अणु
		u32 val;

		/* Set request-type क्रम tracetag */
		val = पढ़ोl(l3c_pmu->base + L3C_TRACETAG_CTRL);
		val |= tt_req << L3C_TRACETAG_REQ_SHIFT;
		val |= L3C_TRACETAG_REQ_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_TRACETAG_CTRL);

		/* Enable request-tracetag statistics */
		val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
		val |= L3C_TRACETAG_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_clear_req_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 tt_req = hisi_get_tt_req(event);

	अगर (tt_req) अणु
		u32 val;

		/* Clear request-type */
		val = पढ़ोl(l3c_pmu->base + L3C_TRACETAG_CTRL);
		val &= ~(tt_req << L3C_TRACETAG_REQ_SHIFT);
		val &= ~L3C_TRACETAG_REQ_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_TRACETAG_CTRL);

		/* Disable request-tracetag statistics */
		val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
		val &= ~L3C_TRACETAG_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_ग_लिखो_ds(काष्ठा perf_event *event, u32 ds_cfg)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u32 reg, reg_idx, shअगरt, val;
	पूर्णांक idx = hwc->idx;

	/*
	 * Select the appropriate datasource रेजिस्टर(L3C_DATSRC_TYPE0/1).
	 * There are 2 datasource ctrl रेजिस्टर क्रम the 8 hardware counters.
	 * Datasrc is 8-bits and क्रम the क्रमmer 4 hardware counters,
	 * L3C_DATSRC_TYPE0 is chosen. For the latter 4 hardware counters,
	 * L3C_DATSRC_TYPE1 is chosen.
	 */
	reg = L3C_DATSRC_TYPE + (idx / 4) * 4;
	reg_idx = idx % 4;
	shअगरt = 8 * reg_idx;

	val = पढ़ोl(l3c_pmu->base + reg);
	val &= ~(L3C_DATSRC_MASK << shअगरt);
	val |= ds_cfg << shअगरt;
	ग_लिखोl(val, l3c_pmu->base + reg);
पूर्ण

अटल व्योम hisi_l3c_pmu_config_ds(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 ds_cfg = hisi_get_datasrc_cfg(event);
	u32 ds_skt = hisi_get_datasrc_skt(event);

	अगर (ds_cfg)
		hisi_l3c_pmu_ग_लिखो_ds(event, ds_cfg);

	अगर (ds_skt) अणु
		u32 val;

		val = पढ़ोl(l3c_pmu->base + L3C_DATSRC_CTRL);
		val |= L3C_DATSRC_SKT_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_DATSRC_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_clear_ds(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 ds_cfg = hisi_get_datasrc_cfg(event);
	u32 ds_skt = hisi_get_datasrc_skt(event);

	अगर (ds_cfg)
		hisi_l3c_pmu_ग_लिखो_ds(event, L3C_DATSRC_NONE);

	अगर (ds_skt) अणु
		u32 val;

		val = पढ़ोl(l3c_pmu->base + L3C_DATSRC_CTRL);
		val &= ~L3C_DATSRC_SKT_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_DATSRC_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_config_core_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 core = hisi_get_tt_core(event);

	अगर (core) अणु
		u32 val;

		/* Config and enable core inक्रमmation */
		ग_लिखोl(core, l3c_pmu->base + L3C_CORE_CTRL);
		val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
		val |= L3C_CORE_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);

		/* Enable core-tracetag statistics */
		val = पढ़ोl(l3c_pmu->base + L3C_TRACETAG_CTRL);
		val |= L3C_TRACETAG_CORE_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_TRACETAG_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_clear_core_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *l3c_pmu = to_hisi_pmu(event->pmu);
	u32 core = hisi_get_tt_core(event);

	अगर (core) अणु
		u32 val;

		/* Clear core inक्रमmation */
		ग_लिखोl(L3C_COER_NONE, l3c_pmu->base + L3C_CORE_CTRL);
		val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
		val &= ~L3C_CORE_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);

		/* Disable core-tracetag statistics */
		val = पढ़ोl(l3c_pmu->base + L3C_TRACETAG_CTRL);
		val &= ~L3C_TRACETAG_CORE_EN;
		ग_लिखोl(val, l3c_pmu->base + L3C_TRACETAG_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_enable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_l3c_pmu_config_req_tracetag(event);
		hisi_l3c_pmu_config_core_tracetag(event);
		hisi_l3c_pmu_config_ds(event);
	पूर्ण
पूर्ण

अटल व्योम hisi_l3c_pmu_disable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_l3c_pmu_clear_ds(event);
		hisi_l3c_pmu_clear_core_tracetag(event);
		hisi_l3c_pmu_clear_req_tracetag(event);
	पूर्ण
पूर्ण

/*
 * Select the counter रेजिस्टर offset using the counter index
 */
अटल u32 hisi_l3c_pmu_get_counter_offset(पूर्णांक cntr_idx)
अणु
	वापस (L3C_CNTR0_LOWER + (cntr_idx * 8));
पूर्ण

अटल u64 hisi_l3c_pmu_पढ़ो_counter(काष्ठा hisi_pmu *l3c_pmu,
				     काष्ठा hw_perf_event *hwc)
अणु
	वापस पढ़ोq(l3c_pmu->base + hisi_l3c_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_l3c_pmu_ग_लिखो_counter(काष्ठा hisi_pmu *l3c_pmu,
				       काष्ठा hw_perf_event *hwc, u64 val)
अणु
	ग_लिखोq(val, l3c_pmu->base + hisi_l3c_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_l3c_pmu_ग_लिखो_evtype(काष्ठा hisi_pmu *l3c_pmu, पूर्णांक idx,
				      u32 type)
अणु
	u32 reg, reg_idx, shअगरt, val;

	/*
	 * Select the appropriate event select रेजिस्टर(L3C_EVENT_TYPE0/1).
	 * There are 2 event select रेजिस्टरs क्रम the 8 hardware counters.
	 * Event code is 8-bits and क्रम the क्रमmer 4 hardware counters,
	 * L3C_EVENT_TYPE0 is chosen. For the latter 4 hardware counters,
	 * L3C_EVENT_TYPE1 is chosen.
	 */
	reg = L3C_EVENT_TYPE0 + (idx / 4) * 4;
	reg_idx = idx % 4;
	shअगरt = 8 * reg_idx;

	/* Write event code to L3C_EVENT_TYPEx Register */
	val = पढ़ोl(l3c_pmu->base + reg);
	val &= ~(L3C_EVTYPE_NONE << shअगरt);
	val |= (type << shअगरt);
	ग_लिखोl(val, l3c_pmu->base + reg);
पूर्ण

अटल व्योम hisi_l3c_pmu_start_counters(काष्ठा hisi_pmu *l3c_pmu)
अणु
	u32 val;

	/*
	 * Set perf_enable bit in L3C_PERF_CTRL रेजिस्टर to start counting
	 * क्रम all enabled counters.
	 */
	val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
	val |= L3C_PERF_CTRL_EN;
	ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);
पूर्ण

अटल व्योम hisi_l3c_pmu_stop_counters(काष्ठा hisi_pmu *l3c_pmu)
अणु
	u32 val;

	/*
	 * Clear perf_enable bit in L3C_PERF_CTRL रेजिस्टर to stop counting
	 * क्रम all enabled counters.
	 */
	val = पढ़ोl(l3c_pmu->base + L3C_PERF_CTRL);
	val &= ~(L3C_PERF_CTRL_EN);
	ग_लिखोl(val, l3c_pmu->base + L3C_PERF_CTRL);
पूर्ण

अटल व्योम hisi_l3c_pmu_enable_counter(काष्ठा hisi_pmu *l3c_pmu,
					काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Enable counter index in L3C_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(l3c_pmu->base + L3C_EVENT_CTRL);
	val |= (1 << hwc->idx);
	ग_लिखोl(val, l3c_pmu->base + L3C_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_l3c_pmu_disable_counter(काष्ठा hisi_pmu *l3c_pmu,
					 काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Clear counter index in L3C_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(l3c_pmu->base + L3C_EVENT_CTRL);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, l3c_pmu->base + L3C_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_l3c_pmu_enable_counter_पूर्णांक(काष्ठा hisi_pmu *l3c_pmu,
					    काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(l3c_pmu->base + L3C_INT_MASK);
	/* Write 0 to enable पूर्णांकerrupt */
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, l3c_pmu->base + L3C_INT_MASK);
पूर्ण

अटल व्योम hisi_l3c_pmu_disable_counter_पूर्णांक(काष्ठा hisi_pmu *l3c_pmu,
					     काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	val = पढ़ोl(l3c_pmu->base + L3C_INT_MASK);
	/* Write 1 to mask पूर्णांकerrupt */
	val |= (1 << hwc->idx);
	ग_लिखोl(val, l3c_pmu->base + L3C_INT_MASK);
पूर्ण

अटल u32 hisi_l3c_pmu_get_पूर्णांक_status(काष्ठा hisi_pmu *l3c_pmu)
अणु
	वापस पढ़ोl(l3c_pmu->base + L3C_INT_STATUS);
पूर्ण

अटल व्योम hisi_l3c_pmu_clear_पूर्णांक_status(काष्ठा hisi_pmu *l3c_pmu, पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, l3c_pmu->base + L3C_INT_CLEAR);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_l3c_pmu_acpi_match[] = अणु
	अणु "HISI0213", पूर्ण,
	अणु "HISI0214", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_l3c_pmu_acpi_match);

अटल पूर्णांक hisi_l3c_pmu_init_data(काष्ठा platक्रमm_device *pdev,
				  काष्ठा hisi_pmu *l3c_pmu)
अणु
	/*
	 * Use the SCCL_ID and CCL_ID to identअगरy the L3C PMU, जबतक
	 * SCCL_ID is in MPIDR[aff2] and CCL_ID is in MPIDR[aff1].
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,scl-id",
				     &l3c_pmu->sccl_id)) अणु
		dev_err(&pdev->dev, "Can not read l3c sccl-id!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,ccl-id",
				     &l3c_pmu->ccl_id)) अणु
		dev_err(&pdev->dev, "Can not read l3c ccl-id!\n");
		वापस -EINVAL;
	पूर्ण

	l3c_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(l3c_pmu->base)) अणु
		dev_err(&pdev->dev, "ioremap failed for l3c_pmu resource\n");
		वापस PTR_ERR(l3c_pmu->base);
	पूर्ण

	l3c_pmu->identअगरier = पढ़ोl(l3c_pmu->base + L3C_VERSION);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hisi_l3c_pmu_v1_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_v1_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_l3c_pmu_v1_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_l3c_pmu_v2_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	HISI_PMU_FORMAT_ATTR(tt_core, "config1:0-7"),
	HISI_PMU_FORMAT_ATTR(tt_req, "config1:8-10"),
	HISI_PMU_FORMAT_ATTR(datasrc_cfg, "config1:11-15"),
	HISI_PMU_FORMAT_ATTR(datasrc_skt, "config1:16"),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_v2_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_l3c_pmu_v2_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_l3c_pmu_v1_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(rd_cpipe,		0x00),
	HISI_PMU_EVENT_ATTR(wr_cpipe,		0x01),
	HISI_PMU_EVENT_ATTR(rd_hit_cpipe,	0x02),
	HISI_PMU_EVENT_ATTR(wr_hit_cpipe,	0x03),
	HISI_PMU_EVENT_ATTR(victim_num,		0x04),
	HISI_PMU_EVENT_ATTR(rd_spipe,		0x20),
	HISI_PMU_EVENT_ATTR(wr_spipe,		0x21),
	HISI_PMU_EVENT_ATTR(rd_hit_spipe,	0x22),
	HISI_PMU_EVENT_ATTR(wr_hit_spipe,	0x23),
	HISI_PMU_EVENT_ATTR(back_invalid,	0x29),
	HISI_PMU_EVENT_ATTR(retry_cpu,		0x40),
	HISI_PMU_EVENT_ATTR(retry_ring,		0x41),
	HISI_PMU_EVENT_ATTR(prefetch_drop,	0x42),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_v1_events_group = अणु
	.name = "events",
	.attrs = hisi_l3c_pmu_v1_events_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_l3c_pmu_v2_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(l3c_hit,		0x48),
	HISI_PMU_EVENT_ATTR(cycles,		0x7f),
	HISI_PMU_EVENT_ATTR(l3c_ref,		0xb8),
	HISI_PMU_EVENT_ATTR(dat_access,		0xb9),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_v2_events_group = अणु
	.name = "events",
	.attrs = hisi_l3c_pmu_v2_events_attr,
पूर्ण;

अटल DEVICE_ATTR(cpumask, 0444, hisi_cpumask_sysfs_show, शून्य);

अटल काष्ठा attribute *hisi_l3c_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_cpumask_attr_group = अणु
	.attrs = hisi_l3c_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा device_attribute hisi_l3c_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, hisi_uncore_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *hisi_l3c_pmu_identअगरier_attrs[] = अणु
	&hisi_l3c_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_l3c_pmu_identअगरier_group = अणु
	.attrs = hisi_l3c_pmu_identअगरier_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_l3c_pmu_v1_attr_groups[] = अणु
	&hisi_l3c_pmu_v1_क्रमmat_group,
	&hisi_l3c_pmu_v1_events_group,
	&hisi_l3c_pmu_cpumask_attr_group,
	&hisi_l3c_pmu_identअगरier_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_l3c_pmu_v2_attr_groups[] = अणु
	&hisi_l3c_pmu_v2_क्रमmat_group,
	&hisi_l3c_pmu_v2_events_group,
	&hisi_l3c_pmu_cpumask_attr_group,
	&hisi_l3c_pmu_identअगरier_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_l3c_ops = अणु
	.ग_लिखो_evtype		= hisi_l3c_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_uncore_pmu_get_event_idx,
	.start_counters		= hisi_l3c_pmu_start_counters,
	.stop_counters		= hisi_l3c_pmu_stop_counters,
	.enable_counter		= hisi_l3c_pmu_enable_counter,
	.disable_counter	= hisi_l3c_pmu_disable_counter,
	.enable_counter_पूर्णांक	= hisi_l3c_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_l3c_pmu_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_l3c_pmu_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_l3c_pmu_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_l3c_pmu_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_l3c_pmu_clear_पूर्णांक_status,
	.enable_filter		= hisi_l3c_pmu_enable_filter,
	.disable_filter		= hisi_l3c_pmu_disable_filter,
पूर्ण;

अटल पूर्णांक hisi_l3c_pmu_dev_probe(काष्ठा platक्रमm_device *pdev,
				  काष्ठा hisi_pmu *l3c_pmu)
अणु
	पूर्णांक ret;

	ret = hisi_l3c_pmu_init_data(pdev, l3c_pmu);
	अगर (ret)
		वापस ret;

	ret = hisi_uncore_pmu_init_irq(l3c_pmu, pdev);
	अगर (ret)
		वापस ret;

	अगर (l3c_pmu->identअगरier >= HISI_PMU_V2) अणु
		l3c_pmu->counter_bits = 64;
		l3c_pmu->check_event = L3C_V2_NR_EVENTS;
		l3c_pmu->pmu_events.attr_groups = hisi_l3c_pmu_v2_attr_groups;
	पूर्ण अन्यथा अणु
		l3c_pmu->counter_bits = 48;
		l3c_pmu->check_event = L3C_V1_NR_EVENTS;
		l3c_pmu->pmu_events.attr_groups = hisi_l3c_pmu_v1_attr_groups;
	पूर्ण

	l3c_pmu->num_counters = L3C_NR_COUNTERS;
	l3c_pmu->ops = &hisi_uncore_l3c_ops;
	l3c_pmu->dev = &pdev->dev;
	l3c_pmu->on_cpu = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_l3c_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *l3c_pmu;
	अक्षर *name;
	पूर्णांक ret;

	l3c_pmu = devm_kzalloc(&pdev->dev, माप(*l3c_pmu), GFP_KERNEL);
	अगर (!l3c_pmu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, l3c_pmu);

	ret = hisi_l3c_pmu_dev_probe(pdev, l3c_pmu);
	अगर (ret)
		वापस ret;

	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_HISI_L3_ONLINE,
				       &l3c_pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * CCL_ID is used to identअगरy the L3C in the same SCCL which was
	 * used _UID by mistake.
	 */
	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "hisi_sccl%u_l3c%u",
			      l3c_pmu->sccl_id, l3c_pmu->ccl_id);
	l3c_pmu->pmu = (काष्ठा pmu) अणु
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
		.attr_groups	= l3c_pmu->pmu_events.attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	ret = perf_pmu_रेजिस्टर(&l3c_pmu->pmu, name, -1);
	अगर (ret) अणु
		dev_err(l3c_pmu->dev, "L3C PMU register failed!\n");
		cpuhp_state_हटाओ_instance_nocalls(
			CPUHP_AP_PERF_ARM_HISI_L3_ONLINE, &l3c_pmu->node);
		irq_set_affinity_hपूर्णांक(l3c_pmu->irq, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_l3c_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *l3c_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&l3c_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_HISI_L3_ONLINE,
					    &l3c_pmu->node);
	irq_set_affinity_hपूर्णांक(l3c_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_l3c_pmu_driver = अणु
	.driver = अणु
		.name = "hisi_l3c_pmu",
		.acpi_match_table = ACPI_PTR(hisi_l3c_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = hisi_l3c_pmu_probe,
	.हटाओ = hisi_l3c_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init hisi_l3c_pmu_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_HISI_L3_ONLINE,
				      "AP_PERF_ARM_HISI_L3_ONLINE",
				      hisi_uncore_pmu_online_cpu,
				      hisi_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("L3C PMU: Error setup hotplug, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hisi_l3c_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_L3_ONLINE);

	वापस ret;
पूर्ण
module_init(hisi_l3c_pmu_module_init);

अटल व्योम __निकास hisi_l3c_pmu_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_l3c_pmu_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_L3_ONLINE);
पूर्ण
module_निकास(hisi_l3c_pmu_module_निकास);

MODULE_DESCRIPTION("HiSilicon SoC L3C uncore PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Anurup M <anurup.m@huawei.com>");
MODULE_AUTHOR("Shaokun Zhang <zhangshaokun@hisilicon.com>");
