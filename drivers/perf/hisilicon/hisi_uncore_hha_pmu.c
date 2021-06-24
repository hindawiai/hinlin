<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SoC HHA uncore Hardware event counters support
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

/* HHA रेजिस्टर definition */
#घोषणा HHA_INT_MASK		0x0804
#घोषणा HHA_INT_STATUS		0x0808
#घोषणा HHA_INT_CLEAR		0x080C
#घोषणा HHA_VERSION		0x1cf0
#घोषणा HHA_PERF_CTRL		0x1E00
#घोषणा HHA_EVENT_CTRL		0x1E04
#घोषणा HHA_SRCID_CTRL		0x1E08
#घोषणा HHA_DATSRC_CTRL		0x1BF0
#घोषणा HHA_EVENT_TYPE0		0x1E80
/*
 * If the HW version only supports a 48-bit counter, then
 * bits [63:48] are reserved, which are Read-As-Zero and
 * Writes-Ignored.
 */
#घोषणा HHA_CNT0_LOWER		0x1F00

/* HHA PMU v1 has 16 counters and v2 only has 8 counters */
#घोषणा HHA_V1_NR_COUNTERS	0x10
#घोषणा HHA_V2_NR_COUNTERS	0x8

#घोषणा HHA_PERF_CTRL_EN	0x1
#घोषणा HHA_TRACETAG_EN		BIT(31)
#घोषणा HHA_SRCID_EN		BIT(2)
#घोषणा HHA_SRCID_CMD_SHIFT	6
#घोषणा HHA_SRCID_MSK_SHIFT	20
#घोषणा HHA_SRCID_CMD		GENMASK(16, 6)
#घोषणा HHA_SRCID_MSK		GENMASK(30, 20)
#घोषणा HHA_DATSRC_SKT_EN	BIT(23)
#घोषणा HHA_EVTYPE_NONE		0xff
#घोषणा HHA_V1_NR_EVENT		0x65
#घोषणा HHA_V2_NR_EVENT		0xCE

HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_cmd, config1, 10, 0);
HISI_PMU_EVENT_ATTR_EXTRACTOR(srcid_msk, config1, 21, 11);
HISI_PMU_EVENT_ATTR_EXTRACTOR(tracetag_en, config1, 22, 22);
HISI_PMU_EVENT_ATTR_EXTRACTOR(datasrc_skt, config1, 23, 23);

अटल व्योम hisi_hha_pmu_enable_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 tt_en = hisi_get_tracetag_en(event);

	अगर (tt_en) अणु
		u32 val;

		val = पढ़ोl(hha_pmu->base + HHA_SRCID_CTRL);
		val |= HHA_TRACETAG_EN;
		ग_लिखोl(val, hha_pmu->base + HHA_SRCID_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_clear_tracetag(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 val;

	val = पढ़ोl(hha_pmu->base + HHA_SRCID_CTRL);
	val &= ~HHA_TRACETAG_EN;
	ग_लिखोl(val, hha_pmu->base + HHA_SRCID_CTRL);
पूर्ण

अटल व्योम hisi_hha_pmu_config_ds(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 ds_skt = hisi_get_datasrc_skt(event);

	अगर (ds_skt) अणु
		u32 val;

		val = पढ़ोl(hha_pmu->base + HHA_DATSRC_CTRL);
		val |= HHA_DATSRC_SKT_EN;
		ग_लिखोl(ds_skt, hha_pmu->base + HHA_DATSRC_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_clear_ds(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 ds_skt = hisi_get_datasrc_skt(event);

	अगर (ds_skt) अणु
		u32 val;

		val = पढ़ोl(hha_pmu->base + HHA_DATSRC_CTRL);
		val &= ~HHA_DATSRC_SKT_EN;
		ग_लिखोl(ds_skt, hha_pmu->base + HHA_DATSRC_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_config_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd) अणु
		u32 val, msk;

		msk = hisi_get_srcid_msk(event);
		val = पढ़ोl(hha_pmu->base + HHA_SRCID_CTRL);
		val |= HHA_SRCID_EN | (cmd << HHA_SRCID_CMD_SHIFT) |
			(msk << HHA_SRCID_MSK_SHIFT);
		ग_लिखोl(val, hha_pmu->base + HHA_SRCID_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_disable_srcid(काष्ठा perf_event *event)
अणु
	काष्ठा hisi_pmu *hha_pmu = to_hisi_pmu(event->pmu);
	u32 cmd = hisi_get_srcid_cmd(event);

	अगर (cmd) अणु
		u32 val;

		val = पढ़ोl(hha_pmu->base + HHA_SRCID_CTRL);
		val &= ~(HHA_SRCID_EN | HHA_SRCID_MSK | HHA_SRCID_CMD);
		ग_लिखोl(val, hha_pmu->base + HHA_SRCID_CTRL);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_enable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_hha_pmu_enable_tracetag(event);
		hisi_hha_pmu_config_ds(event);
		hisi_hha_pmu_config_srcid(event);
	पूर्ण
पूर्ण

अटल व्योम hisi_hha_pmu_disable_filter(काष्ठा perf_event *event)
अणु
	अगर (event->attr.config1 != 0x0) अणु
		hisi_hha_pmu_disable_srcid(event);
		hisi_hha_pmu_clear_ds(event);
		hisi_hha_pmu_clear_tracetag(event);
	पूर्ण
पूर्ण

/*
 * Select the counter रेजिस्टर offset using the counter index
 * each counter is 48-bits.
 */
अटल u32 hisi_hha_pmu_get_counter_offset(पूर्णांक cntr_idx)
अणु
	वापस (HHA_CNT0_LOWER + (cntr_idx * 8));
पूर्ण

अटल u64 hisi_hha_pmu_पढ़ो_counter(काष्ठा hisi_pmu *hha_pmu,
				     काष्ठा hw_perf_event *hwc)
अणु
	/* Read 64 bits and like L3C, top 16 bits are RAZ */
	वापस पढ़ोq(hha_pmu->base + hisi_hha_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_hha_pmu_ग_लिखो_counter(काष्ठा hisi_pmu *hha_pmu,
				       काष्ठा hw_perf_event *hwc, u64 val)
अणु
	/* Write 64 bits and like L3C, top 16 bits are WI */
	ग_लिखोq(val, hha_pmu->base + hisi_hha_pmu_get_counter_offset(hwc->idx));
पूर्ण

अटल व्योम hisi_hha_pmu_ग_लिखो_evtype(काष्ठा hisi_pmu *hha_pmu, पूर्णांक idx,
				      u32 type)
अणु
	u32 reg, reg_idx, shअगरt, val;

	/*
	 * Select the appropriate event select रेजिस्टर(HHA_EVENT_TYPEx).
	 * There are 4 event select रेजिस्टरs क्रम the 16 hardware counters.
	 * Event code is 8-bits and क्रम the first 4 hardware counters,
	 * HHA_EVENT_TYPE0 is chosen. For the next 4 hardware counters,
	 * HHA_EVENT_TYPE1 is chosen and so on.
	 */
	reg = HHA_EVENT_TYPE0 + 4 * (idx / 4);
	reg_idx = idx % 4;
	shअगरt = 8 * reg_idx;

	/* Write event code to HHA_EVENT_TYPEx रेजिस्टर */
	val = पढ़ोl(hha_pmu->base + reg);
	val &= ~(HHA_EVTYPE_NONE << shअगरt);
	val |= (type << shअगरt);
	ग_लिखोl(val, hha_pmu->base + reg);
पूर्ण

अटल व्योम hisi_hha_pmu_start_counters(काष्ठा hisi_pmu *hha_pmu)
अणु
	u32 val;

	/*
	 * Set perf_enable bit in HHA_PERF_CTRL to start event
	 * counting क्रम all enabled counters.
	 */
	val = पढ़ोl(hha_pmu->base + HHA_PERF_CTRL);
	val |= HHA_PERF_CTRL_EN;
	ग_लिखोl(val, hha_pmu->base + HHA_PERF_CTRL);
पूर्ण

अटल व्योम hisi_hha_pmu_stop_counters(काष्ठा hisi_pmu *hha_pmu)
अणु
	u32 val;

	/*
	 * Clear perf_enable bit in HHA_PERF_CTRL to stop event
	 * counting क्रम all enabled counters.
	 */
	val = पढ़ोl(hha_pmu->base + HHA_PERF_CTRL);
	val &= ~(HHA_PERF_CTRL_EN);
	ग_लिखोl(val, hha_pmu->base + HHA_PERF_CTRL);
पूर्ण

अटल व्योम hisi_hha_pmu_enable_counter(काष्ठा hisi_pmu *hha_pmu,
					काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Enable counter index in HHA_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(hha_pmu->base + HHA_EVENT_CTRL);
	val |= (1 << hwc->idx);
	ग_लिखोl(val, hha_pmu->base + HHA_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_hha_pmu_disable_counter(काष्ठा hisi_pmu *hha_pmu,
					 काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Clear counter index in HHA_EVENT_CTRL रेजिस्टर */
	val = पढ़ोl(hha_pmu->base + HHA_EVENT_CTRL);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, hha_pmu->base + HHA_EVENT_CTRL);
पूर्ण

अटल व्योम hisi_hha_pmu_enable_counter_पूर्णांक(काष्ठा hisi_pmu *hha_pmu,
					    काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 0 to enable पूर्णांकerrupt */
	val = पढ़ोl(hha_pmu->base + HHA_INT_MASK);
	val &= ~(1 << hwc->idx);
	ग_लिखोl(val, hha_pmu->base + HHA_INT_MASK);
पूर्ण

अटल व्योम hisi_hha_pmu_disable_counter_पूर्णांक(काष्ठा hisi_pmu *hha_pmu,
					     काष्ठा hw_perf_event *hwc)
अणु
	u32 val;

	/* Write 1 to mask पूर्णांकerrupt */
	val = पढ़ोl(hha_pmu->base + HHA_INT_MASK);
	val |= (1 << hwc->idx);
	ग_लिखोl(val, hha_pmu->base + HHA_INT_MASK);
पूर्ण

अटल u32 hisi_hha_pmu_get_पूर्णांक_status(काष्ठा hisi_pmu *hha_pmu)
अणु
	वापस पढ़ोl(hha_pmu->base + HHA_INT_STATUS);
पूर्ण

अटल व्योम hisi_hha_pmu_clear_पूर्णांक_status(काष्ठा hisi_pmu *hha_pmu, पूर्णांक idx)
अणु
	ग_लिखोl(1 << idx, hha_pmu->base + HHA_INT_CLEAR);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_hha_pmu_acpi_match[] = अणु
	अणु "HISI0243", पूर्ण,
	अणु "HISI0244", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hisi_hha_pmu_acpi_match);

अटल पूर्णांक hisi_hha_pmu_init_data(काष्ठा platक्रमm_device *pdev,
				  काष्ठा hisi_pmu *hha_pmu)
अणु
	अचिन्हित दीर्घ दीर्घ id;
	acpi_status status;

	/*
	 * Use SCCL_ID and UID to identअगरy the HHA PMU, जबतक
	 * SCCL_ID is in MPIDR[aff2].
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,scl-id",
				     &hha_pmu->sccl_id)) अणु
		dev_err(&pdev->dev, "Can not read hha sccl-id!\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Early versions of BIOS support _UID by mistake, so we support
	 * both "hisilicon, idx-id" as preference, अगर available.
	 */
	अगर (device_property_पढ़ो_u32(&pdev->dev, "hisilicon,idx-id",
				     &hha_pmu->index_id)) अणु
		status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(&pdev->dev),
					       "_UID", शून्य, &id);
		अगर (ACPI_FAILURE(status)) अणु
			dev_err(&pdev->dev, "Cannot read idx-id!\n");
			वापस -EINVAL;
		पूर्ण

		hha_pmu->index_id = id;
	पूर्ण
	/* HHA PMUs only share the same SCCL */
	hha_pmu->ccl_id = -1;

	hha_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hha_pmu->base)) अणु
		dev_err(&pdev->dev, "ioremap failed for hha_pmu resource\n");
		वापस PTR_ERR(hha_pmu->base);
	पूर्ण

	hha_pmu->identअगरier = पढ़ोl(hha_pmu->base + HHA_VERSION);

	वापस 0;
पूर्ण

अटल काष्ठा attribute *hisi_hha_pmu_v1_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_v1_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_hha_pmu_v1_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_hha_pmu_v2_क्रमmat_attr[] = अणु
	HISI_PMU_FORMAT_ATTR(event, "config:0-7"),
	HISI_PMU_FORMAT_ATTR(srcid_cmd, "config1:0-10"),
	HISI_PMU_FORMAT_ATTR(srcid_msk, "config1:11-21"),
	HISI_PMU_FORMAT_ATTR(tracetag_en, "config1:22"),
	HISI_PMU_FORMAT_ATTR(datasrc_skt, "config1:23"),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_v2_क्रमmat_group = अणु
	.name = "format",
	.attrs = hisi_hha_pmu_v2_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_hha_pmu_v1_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(rx_ops_num,		0x00),
	HISI_PMU_EVENT_ATTR(rx_outer,		0x01),
	HISI_PMU_EVENT_ATTR(rx_sccl,		0x02),
	HISI_PMU_EVENT_ATTR(rx_ccix,		0x03),
	HISI_PMU_EVENT_ATTR(rx_wbi,		0x04),
	HISI_PMU_EVENT_ATTR(rx_wbip,		0x05),
	HISI_PMU_EVENT_ATTR(rx_wtistash,	0x11),
	HISI_PMU_EVENT_ATTR(rd_ddr_64b,		0x1c),
	HISI_PMU_EVENT_ATTR(wr_ddr_64b,		0x1d),
	HISI_PMU_EVENT_ATTR(rd_ddr_128b,	0x1e),
	HISI_PMU_EVENT_ATTR(wr_ddr_128b,	0x1f),
	HISI_PMU_EVENT_ATTR(spill_num,		0x20),
	HISI_PMU_EVENT_ATTR(spill_success,	0x21),
	HISI_PMU_EVENT_ATTR(bi_num,		0x23),
	HISI_PMU_EVENT_ATTR(mediated_num,	0x32),
	HISI_PMU_EVENT_ATTR(tx_snp_num,		0x33),
	HISI_PMU_EVENT_ATTR(tx_snp_outer,	0x34),
	HISI_PMU_EVENT_ATTR(tx_snp_ccix,	0x35),
	HISI_PMU_EVENT_ATTR(rx_snprspdata,	0x38),
	HISI_PMU_EVENT_ATTR(rx_snprsp_outer,	0x3c),
	HISI_PMU_EVENT_ATTR(sdir-lookup,	0x40),
	HISI_PMU_EVENT_ATTR(edir-lookup,	0x41),
	HISI_PMU_EVENT_ATTR(sdir-hit,		0x42),
	HISI_PMU_EVENT_ATTR(edir-hit,		0x43),
	HISI_PMU_EVENT_ATTR(sdir-home-migrate,	0x4c),
	HISI_PMU_EVENT_ATTR(edir-home-migrate,  0x4d),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_v1_events_group = अणु
	.name = "events",
	.attrs = hisi_hha_pmu_v1_events_attr,
पूर्ण;

अटल काष्ठा attribute *hisi_hha_pmu_v2_events_attr[] = अणु
	HISI_PMU_EVENT_ATTR(rx_ops_num,		0x00),
	HISI_PMU_EVENT_ATTR(rx_outer,		0x01),
	HISI_PMU_EVENT_ATTR(rx_sccl,		0x02),
	HISI_PMU_EVENT_ATTR(hha_retry,		0x2e),
	HISI_PMU_EVENT_ATTR(cycles,		0x55),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_v2_events_group = अणु
	.name = "events",
	.attrs = hisi_hha_pmu_v2_events_attr,
पूर्ण;

अटल DEVICE_ATTR(cpumask, 0444, hisi_cpumask_sysfs_show, शून्य);

अटल काष्ठा attribute *hisi_hha_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_cpumask_attr_group = अणु
	.attrs = hisi_hha_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा device_attribute hisi_hha_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, hisi_uncore_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *hisi_hha_pmu_identअगरier_attrs[] = अणु
	&hisi_hha_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hisi_hha_pmu_identअगरier_group = अणु
	.attrs = hisi_hha_pmu_identअगरier_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_hha_pmu_v1_attr_groups[] = अणु
	&hisi_hha_pmu_v1_क्रमmat_group,
	&hisi_hha_pmu_v1_events_group,
	&hisi_hha_pmu_cpumask_attr_group,
	&hisi_hha_pmu_identअगरier_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hisi_hha_pmu_v2_attr_groups[] = अणु
	&hisi_hha_pmu_v2_क्रमmat_group,
	&hisi_hha_pmu_v2_events_group,
	&hisi_hha_pmu_cpumask_attr_group,
	&hisi_hha_pmu_identअगरier_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hisi_uncore_ops hisi_uncore_hha_ops = अणु
	.ग_लिखो_evtype		= hisi_hha_pmu_ग_लिखो_evtype,
	.get_event_idx		= hisi_uncore_pmu_get_event_idx,
	.start_counters		= hisi_hha_pmu_start_counters,
	.stop_counters		= hisi_hha_pmu_stop_counters,
	.enable_counter		= hisi_hha_pmu_enable_counter,
	.disable_counter	= hisi_hha_pmu_disable_counter,
	.enable_counter_पूर्णांक	= hisi_hha_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक	= hisi_hha_pmu_disable_counter_पूर्णांक,
	.ग_लिखो_counter		= hisi_hha_pmu_ग_लिखो_counter,
	.पढ़ो_counter		= hisi_hha_pmu_पढ़ो_counter,
	.get_पूर्णांक_status		= hisi_hha_pmu_get_पूर्णांक_status,
	.clear_पूर्णांक_status	= hisi_hha_pmu_clear_पूर्णांक_status,
	.enable_filter		= hisi_hha_pmu_enable_filter,
	.disable_filter		= hisi_hha_pmu_disable_filter,
पूर्ण;

अटल पूर्णांक hisi_hha_pmu_dev_probe(काष्ठा platक्रमm_device *pdev,
				  काष्ठा hisi_pmu *hha_pmu)
अणु
	पूर्णांक ret;

	ret = hisi_hha_pmu_init_data(pdev, hha_pmu);
	अगर (ret)
		वापस ret;

	ret = hisi_uncore_pmu_init_irq(hha_pmu, pdev);
	अगर (ret)
		वापस ret;

	अगर (hha_pmu->identअगरier >= HISI_PMU_V2) अणु
		hha_pmu->counter_bits = 64;
		hha_pmu->check_event = HHA_V2_NR_EVENT;
		hha_pmu->pmu_events.attr_groups = hisi_hha_pmu_v2_attr_groups;
		hha_pmu->num_counters = HHA_V2_NR_COUNTERS;
	पूर्ण अन्यथा अणु
		hha_pmu->counter_bits = 48;
		hha_pmu->check_event = HHA_V1_NR_EVENT;
		hha_pmu->pmu_events.attr_groups = hisi_hha_pmu_v1_attr_groups;
		hha_pmu->num_counters = HHA_V1_NR_COUNTERS;
	पूर्ण
	hha_pmu->ops = &hisi_uncore_hha_ops;
	hha_pmu->dev = &pdev->dev;
	hha_pmu->on_cpu = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_hha_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *hha_pmu;
	अक्षर *name;
	पूर्णांक ret;

	hha_pmu = devm_kzalloc(&pdev->dev, माप(*hha_pmu), GFP_KERNEL);
	अगर (!hha_pmu)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hha_pmu);

	ret = hisi_hha_pmu_dev_probe(pdev, hha_pmu);
	अगर (ret)
		वापस ret;

	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE,
				       &hha_pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug\n", ret);
		वापस ret;
	पूर्ण

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "hisi_sccl%u_hha%u",
			      hha_pmu->sccl_id, hha_pmu->index_id);
	hha_pmu->pmu = (काष्ठा pmu) अणु
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
		.attr_groups	= hha_pmu->pmu_events.attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	ret = perf_pmu_रेजिस्टर(&hha_pmu->pmu, name, -1);
	अगर (ret) अणु
		dev_err(hha_pmu->dev, "HHA PMU register failed!\n");
		cpuhp_state_हटाओ_instance_nocalls(
			CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE, &hha_pmu->node);
		irq_set_affinity_hपूर्णांक(hha_pmu->irq, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_hha_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_pmu *hha_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&hha_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE,
					    &hha_pmu->node);
	irq_set_affinity_hपूर्णांक(hha_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hisi_hha_pmu_driver = अणु
	.driver = अणु
		.name = "hisi_hha_pmu",
		.acpi_match_table = ACPI_PTR(hisi_hha_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = hisi_hha_pmu_probe,
	.हटाओ = hisi_hha_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init hisi_hha_pmu_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE,
				      "AP_PERF_ARM_HISI_HHA_ONLINE",
				      hisi_uncore_pmu_online_cpu,
				      hisi_uncore_pmu_offline_cpu);
	अगर (ret) अणु
		pr_err("HHA PMU: Error setup hotplug, ret = %d;\n", ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&hisi_hha_pmu_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE);

	वापस ret;
पूर्ण
module_init(hisi_hha_pmu_module_init);

अटल व्योम __निकास hisi_hha_pmu_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&hisi_hha_pmu_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE);
पूर्ण
module_निकास(hisi_hha_pmu_module_निकास);

MODULE_DESCRIPTION("HiSilicon SoC HHA uncore PMU driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Shaokun Zhang <zhangshaokun@hisilicon.com>");
MODULE_AUTHOR("Anurup M <anurup.m@huawei.com>");
