<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2017 NXP
 * Copyright 2011,2016 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>

#समावेश "common.h"

#घोषणा MMDC_MAPSR		0x404
#घोषणा BP_MMDC_MAPSR_PSD	0
#घोषणा BP_MMDC_MAPSR_PSS	4

#घोषणा MMDC_MDMISC		0x18
#घोषणा BM_MMDC_MDMISC_DDR_TYPE	0x18
#घोषणा BP_MMDC_MDMISC_DDR_TYPE	0x3

#घोषणा TOTAL_CYCLES		0x0
#घोषणा BUSY_CYCLES		0x1
#घोषणा READ_ACCESSES		0x2
#घोषणा WRITE_ACCESSES		0x3
#घोषणा READ_BYTES		0x4
#घोषणा WRITE_BYTES		0x5

/* Enables, resets, मुक्तzes, overflow profiling*/
#घोषणा DBG_DIS			0x0
#घोषणा DBG_EN			0x1
#घोषणा DBG_RST			0x2
#घोषणा PRF_FRZ			0x4
#घोषणा CYC_OVF			0x8
#घोषणा PROखाता_SEL		0x10

#घोषणा MMDC_MADPCR0	0x410
#घोषणा MMDC_MADPCR1	0x414
#घोषणा MMDC_MADPSR0	0x418
#घोषणा MMDC_MADPSR1	0x41C
#घोषणा MMDC_MADPSR2	0x420
#घोषणा MMDC_MADPSR3	0x424
#घोषणा MMDC_MADPSR4	0x428
#घोषणा MMDC_MADPSR5	0x42C

#घोषणा MMDC_NUM_COUNTERS	6

#घोषणा MMDC_FLAG_PROखाता_SEL	0x1
#घोषणा MMDC_PRF_AXI_ID_CLEAR	0x0

#घोषणा to_mmdc_pmu(p) container_of(p, काष्ठा mmdc_pmu, pmu)

अटल पूर्णांक ddr_type;

काष्ठा fsl_mmdc_devtype_data अणु
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा fsl_mmdc_devtype_data imx6q_data = अणु
पूर्ण;

अटल स्थिर काष्ठा fsl_mmdc_devtype_data imx6qp_data = अणु
	.flags = MMDC_FLAG_PROखाता_SEL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_mmdc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-mmdc", .data = (व्योम *)&imx6q_dataपूर्ण,
	अणु .compatible = "fsl,imx6qp-mmdc", .data = (व्योम *)&imx6qp_dataपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PERF_EVENTS

अटल क्रमागत cpuhp_state cpuhp_mmdc_state;
अटल DEFINE_IDA(mmdc_ida);

PMU_EVENT_ATTR_STRING(total-cycles, mmdc_pmu_total_cycles, "event=0x00")
PMU_EVENT_ATTR_STRING(busy-cycles, mmdc_pmu_busy_cycles, "event=0x01")
PMU_EVENT_ATTR_STRING(पढ़ो-accesses, mmdc_pmu_पढ़ो_accesses, "event=0x02")
PMU_EVENT_ATTR_STRING(ग_लिखो-accesses, mmdc_pmu_ग_लिखो_accesses, "event=0x03")
PMU_EVENT_ATTR_STRING(पढ़ो-bytes, mmdc_pmu_पढ़ो_bytes, "event=0x04")
PMU_EVENT_ATTR_STRING(पढ़ो-bytes.unit, mmdc_pmu_पढ़ो_bytes_unit, "MB");
PMU_EVENT_ATTR_STRING(पढ़ो-bytes.scale, mmdc_pmu_पढ़ो_bytes_scale, "0.000001");
PMU_EVENT_ATTR_STRING(ग_लिखो-bytes, mmdc_pmu_ग_लिखो_bytes, "event=0x05")
PMU_EVENT_ATTR_STRING(ग_लिखो-bytes.unit, mmdc_pmu_ग_लिखो_bytes_unit, "MB");
PMU_EVENT_ATTR_STRING(ग_लिखो-bytes.scale, mmdc_pmu_ग_लिखो_bytes_scale, "0.000001");

काष्ठा mmdc_pmu अणु
	काष्ठा pmu pmu;
	व्योम __iomem *mmdc_base;
	cpumask_t cpu;
	काष्ठा hrसमयr hrसमयr;
	अचिन्हित पूर्णांक active_events;
	काष्ठा device *dev;
	काष्ठा perf_event *mmdc_events[MMDC_NUM_COUNTERS];
	काष्ठा hlist_node node;
	काष्ठा fsl_mmdc_devtype_data *devtype_data;
पूर्ण;

/*
 * Polling period is set to one second, overflow of total-cycles (the fastest
 * increasing counter) takes ten seconds so one second is safe
 */
अटल अचिन्हित पूर्णांक mmdc_pmu_poll_period_us = 1000000;

module_param_named(pmu_pmu_poll_period_us, mmdc_pmu_poll_period_us, uपूर्णांक,
		S_IRUGO | S_IWUSR);

अटल kसमय_प्रकार mmdc_pmu_समयr_period(व्योम)
अणु
	वापस ns_to_kसमय((u64)mmdc_pmu_poll_period_us * 1000);
पूर्ण

अटल sमाप_प्रकार mmdc_pmu_cpumask_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = dev_get_drvdata(dev);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &pmu_mmdc->cpu);
पूर्ण

अटल काष्ठा device_attribute mmdc_pmu_cpumask_attr =
	__ATTR(cpumask, S_IRUGO, mmdc_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *mmdc_pmu_cpumask_attrs[] = अणु
	&mmdc_pmu_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mmdc_pmu_cpumask_attr_group = अणु
	.attrs = mmdc_pmu_cpumask_attrs,
पूर्ण;

अटल काष्ठा attribute *mmdc_pmu_events_attrs[] = अणु
	&mmdc_pmu_total_cycles.attr.attr,
	&mmdc_pmu_busy_cycles.attr.attr,
	&mmdc_pmu_पढ़ो_accesses.attr.attr,
	&mmdc_pmu_ग_लिखो_accesses.attr.attr,
	&mmdc_pmu_पढ़ो_bytes.attr.attr,
	&mmdc_pmu_पढ़ो_bytes_unit.attr.attr,
	&mmdc_pmu_पढ़ो_bytes_scale.attr.attr,
	&mmdc_pmu_ग_लिखो_bytes.attr.attr,
	&mmdc_pmu_ग_लिखो_bytes_unit.attr.attr,
	&mmdc_pmu_ग_लिखो_bytes_scale.attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mmdc_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = mmdc_pmu_events_attrs,
पूर्ण;

PMU_FORMAT_ATTR(event, "config:0-63");
PMU_FORMAT_ATTR(axi_id, "config1:0-63");

अटल काष्ठा attribute *mmdc_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_axi_id.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group mmdc_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = mmdc_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *attr_groups[] = अणु
	&mmdc_pmu_events_attr_group,
	&mmdc_pmu_क्रमmat_attr_group,
	&mmdc_pmu_cpumask_attr_group,
	शून्य,
पूर्ण;

अटल u32 mmdc_pmu_पढ़ो_counter(काष्ठा mmdc_pmu *pmu_mmdc, पूर्णांक cfg)
अणु
	व्योम __iomem *mmdc_base, *reg;

	mmdc_base = pmu_mmdc->mmdc_base;

	चयन (cfg) अणु
	हाल TOTAL_CYCLES:
		reg = mmdc_base + MMDC_MADPSR0;
		अवरोध;
	हाल BUSY_CYCLES:
		reg = mmdc_base + MMDC_MADPSR1;
		अवरोध;
	हाल READ_ACCESSES:
		reg = mmdc_base + MMDC_MADPSR2;
		अवरोध;
	हाल WRITE_ACCESSES:
		reg = mmdc_base + MMDC_MADPSR3;
		अवरोध;
	हाल READ_BYTES:
		reg = mmdc_base + MMDC_MADPSR4;
		अवरोध;
	हाल WRITE_BYTES:
		reg = mmdc_base + MMDC_MADPSR5;
		अवरोध;
	शेष:
		वापस WARN_ONCE(1,
			"invalid configuration %d for mmdc counter", cfg);
	पूर्ण
	वापस पढ़ोl(reg);
पूर्ण

अटल पूर्णांक mmdc_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = hlist_entry_safe(node, काष्ठा mmdc_pmu, node);
	पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &pmu_mmdc->cpu))
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&pmu_mmdc->pmu, cpu, target);
	cpumask_set_cpu(target, &pmu_mmdc->cpu);

	वापस 0;
पूर्ण

अटल bool mmdc_pmu_group_event_is_valid(काष्ठा perf_event *event,
					  काष्ठा pmu *pmu,
					  अचिन्हित दीर्घ *used_counters)
अणु
	पूर्णांक cfg = event->attr.config;

	अगर (is_software_event(event))
		वापस true;

	अगर (event->pmu != pmu)
		वापस false;

	वापस !test_and_set_bit(cfg, used_counters);
पूर्ण

/*
 * Each event has a single fixed-purpose counter, so we can only have a
 * single active event क्रम each at any poपूर्णांक in समय. Here we just check
 * क्रम duplicates, and rely on mmdc_pmu_event_init to verअगरy that the HW
 * event numbers are valid.
 */
अटल bool mmdc_pmu_group_is_valid(काष्ठा perf_event *event)
अणु
	काष्ठा pmu *pmu = event->pmu;
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा perf_event *sibling;
	अचिन्हित दीर्घ counter_mask = 0;

	set_bit(leader->attr.config, &counter_mask);

	अगर (event != leader) अणु
		अगर (!mmdc_pmu_group_event_is_valid(event, pmu, &counter_mask))
			वापस false;
	पूर्ण

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!mmdc_pmu_group_event_is_valid(sibling, pmu, &counter_mask))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक mmdc_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	पूर्णांक cfg = event->attr.config;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EOPNOTSUPP;

	अगर (event->cpu < 0) अणु
		dev_warn(pmu_mmdc->dev, "Can't provide per-task data!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (event->attr.sample_period)
		वापस -EINVAL;

	अगर (cfg < 0 || cfg >= MMDC_NUM_COUNTERS)
		वापस -EINVAL;

	अगर (!mmdc_pmu_group_is_valid(event))
		वापस -EINVAL;

	event->cpu = cpumask_first(&pmu_mmdc->cpu);
	वापस 0;
पूर्ण

अटल व्योम mmdc_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

	करो अणु
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
		new_raw_count = mmdc_pmu_पढ़ो_counter(pmu_mmdc,
						      event->attr.config);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
		new_raw_count) != prev_raw_count);

	delta = (new_raw_count - prev_raw_count) & 0xFFFFFFFF;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम mmdc_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	व्योम __iomem *mmdc_base, *reg;
	u32 val;

	mmdc_base = pmu_mmdc->mmdc_base;
	reg = mmdc_base + MMDC_MADPCR0;

	/*
	 * hrसमयr is required because mmdc करोes not provide an पूर्णांकerrupt so
	 * polling is necessary
	 */
	hrसमयr_start(&pmu_mmdc->hrसमयr, mmdc_pmu_समयr_period(),
			HRTIMER_MODE_REL_PINNED);

	local64_set(&hwc->prev_count, 0);

	ग_लिखोl(DBG_RST, reg);

	/*
	 * Write the AXI id parameter to MADPCR1.
	 */
	val = event->attr.config1;
	reg = mmdc_base + MMDC_MADPCR1;
	ग_लिखोl(val, reg);

	reg = mmdc_base + MMDC_MADPCR0;
	val = DBG_EN;
	अगर (pmu_mmdc->devtype_data->flags & MMDC_FLAG_PROखाता_SEL)
		val |= PROखाता_SEL;

	ग_लिखोl(val, reg);
पूर्ण

अटल पूर्णांक mmdc_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	पूर्णांक cfg = event->attr.config;

	अगर (flags & PERF_EF_START)
		mmdc_pmu_event_start(event, flags);

	अगर (pmu_mmdc->mmdc_events[cfg] != शून्य)
		वापस -EAGAIN;

	pmu_mmdc->mmdc_events[cfg] = event;
	pmu_mmdc->active_events++;

	local64_set(&hwc->prev_count, mmdc_pmu_पढ़ो_counter(pmu_mmdc, cfg));

	वापस 0;
पूर्ण

अटल व्योम mmdc_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	व्योम __iomem *mmdc_base, *reg;

	mmdc_base = pmu_mmdc->mmdc_base;
	reg = mmdc_base + MMDC_MADPCR0;

	ग_लिखोl(PRF_FRZ, reg);

	reg = mmdc_base + MMDC_MADPCR1;
	ग_लिखोl(MMDC_PRF_AXI_ID_CLEAR, reg);

	mmdc_pmu_event_update(event);
पूर्ण

अटल व्योम mmdc_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = to_mmdc_pmu(event->pmu);
	पूर्णांक cfg = event->attr.config;

	pmu_mmdc->mmdc_events[cfg] = शून्य;
	pmu_mmdc->active_events--;

	अगर (pmu_mmdc->active_events == 0)
		hrसमयr_cancel(&pmu_mmdc->hrसमयr);

	mmdc_pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल व्योम mmdc_pmu_overflow_handler(काष्ठा mmdc_pmu *pmu_mmdc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MMDC_NUM_COUNTERS; i++) अणु
		काष्ठा perf_event *event = pmu_mmdc->mmdc_events[i];

		अगर (event)
			mmdc_pmu_event_update(event);
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart mmdc_pmu_समयr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = container_of(hrसमयr, काष्ठा mmdc_pmu,
			hrसमयr);

	mmdc_pmu_overflow_handler(pmu_mmdc);
	hrसमयr_क्रमward_now(hrसमयr, mmdc_pmu_समयr_period());

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक mmdc_pmu_init(काष्ठा mmdc_pmu *pmu_mmdc,
		व्योम __iomem *mmdc_base, काष्ठा device *dev)
अणु
	पूर्णांक mmdc_num;

	*pmu_mmdc = (काष्ठा mmdc_pmu) अणु
		.pmu = (काष्ठा pmu) अणु
			.task_ctx_nr    = perf_invalid_context,
			.attr_groups    = attr_groups,
			.event_init     = mmdc_pmu_event_init,
			.add            = mmdc_pmu_event_add,
			.del            = mmdc_pmu_event_del,
			.start          = mmdc_pmu_event_start,
			.stop           = mmdc_pmu_event_stop,
			.पढ़ो           = mmdc_pmu_event_update,
			.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
		पूर्ण,
		.mmdc_base = mmdc_base,
		.dev = dev,
		.active_events = 0,
	पूर्ण;

	mmdc_num = ida_simple_get(&mmdc_ida, 0, 0, GFP_KERNEL);

	वापस mmdc_num;
पूर्ण

अटल पूर्णांक imx_mmdc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc = platक्रमm_get_drvdata(pdev);

	cpuhp_state_हटाओ_instance_nocalls(cpuhp_mmdc_state, &pmu_mmdc->node);
	perf_pmu_unरेजिस्टर(&pmu_mmdc->pmu);
	kमुक्त(pmu_mmdc);
	वापस 0;
पूर्ण

अटल पूर्णांक imx_mmdc_perf_init(काष्ठा platक्रमm_device *pdev, व्योम __iomem *mmdc_base)
अणु
	काष्ठा mmdc_pmu *pmu_mmdc;
	अक्षर *name;
	पूर्णांक mmdc_num;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(imx_mmdc_dt_ids, &pdev->dev);

	pmu_mmdc = kzalloc(माप(*pmu_mmdc), GFP_KERNEL);
	अगर (!pmu_mmdc) अणु
		pr_err("failed to allocate PMU device!\n");
		वापस -ENOMEM;
	पूर्ण

	/* The first instance रेजिस्टरs the hotplug state */
	अगर (!cpuhp_mmdc_state) अणु
		ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
					      "perf/arm/mmdc:online", शून्य,
					      mmdc_pmu_offline_cpu);
		अगर (ret < 0) अणु
			pr_err("cpuhp_setup_state_multi failed\n");
			जाओ pmu_मुक्त;
		पूर्ण
		cpuhp_mmdc_state = ret;
	पूर्ण

	mmdc_num = mmdc_pmu_init(pmu_mmdc, mmdc_base, &pdev->dev);
	अगर (mmdc_num == 0)
		name = "mmdc";
	अन्यथा
		name = devm_kaप्र_लिखो(&pdev->dev,
				GFP_KERNEL, "mmdc%d", mmdc_num);

	pmu_mmdc->devtype_data = (काष्ठा fsl_mmdc_devtype_data *)of_id->data;

	hrसमयr_init(&pmu_mmdc->hrसमयr, CLOCK_MONOTONIC,
			HRTIMER_MODE_REL);
	pmu_mmdc->hrसमयr.function = mmdc_pmu_समयr_handler;

	cpumask_set_cpu(raw_smp_processor_id(), &pmu_mmdc->cpu);

	/* Register the pmu instance क्रम cpu hotplug */
	cpuhp_state_add_instance_nocalls(cpuhp_mmdc_state, &pmu_mmdc->node);

	ret = perf_pmu_रेजिस्टर(&(pmu_mmdc->pmu), name, -1);
	अगर (ret)
		जाओ pmu_रेजिस्टर_err;

	platक्रमm_set_drvdata(pdev, pmu_mmdc);
	वापस 0;

pmu_रेजिस्टर_err:
	pr_warn("MMDC Perf PMU failed (%d), disabled\n", ret);
	cpuhp_state_हटाओ_instance_nocalls(cpuhp_mmdc_state, &pmu_mmdc->node);
	hrसमयr_cancel(&pmu_mmdc->hrसमयr);
pmu_मुक्त:
	kमुक्त(pmu_mmdc);
	वापस ret;
पूर्ण

#अन्यथा
#घोषणा imx_mmdc_हटाओ शून्य
#घोषणा imx_mmdc_perf_init(pdev, mmdc_base) 0
#पूर्ण_अगर

अटल पूर्णांक imx_mmdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	व्योम __iomem *mmdc_base, *reg;
	काष्ठा clk *mmdc_ipg_clk;
	u32 val;
	पूर्णांक err;

	/* the ipg घड़ी is optional */
	mmdc_ipg_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mmdc_ipg_clk))
		mmdc_ipg_clk = शून्य;

	err = clk_prepare_enable(mmdc_ipg_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to enable mmdc ipg clock.\n");
		वापस err;
	पूर्ण

	mmdc_base = of_iomap(np, 0);
	WARN_ON(!mmdc_base);

	reg = mmdc_base + MMDC_MDMISC;
	/* Get ddr type */
	val = पढ़ोl_relaxed(reg);
	ddr_type = (val & BM_MMDC_MDMISC_DDR_TYPE) >>
		 BP_MMDC_MDMISC_DDR_TYPE;

	reg = mmdc_base + MMDC_MAPSR;

	/* Enable स्वतःmatic घातer saving */
	val = पढ़ोl_relaxed(reg);
	val &= ~(1 << BP_MMDC_MAPSR_PSD);
	ग_लिखोl_relaxed(val, reg);

	वापस imx_mmdc_perf_init(pdev, mmdc_base);
पूर्ण

पूर्णांक imx_mmdc_get_ddr_type(व्योम)
अणु
	वापस ddr_type;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_mmdc_driver = अणु
	.driver		= अणु
		.name	= "imx-mmdc",
		.of_match_table = imx_mmdc_dt_ids,
	पूर्ण,
	.probe		= imx_mmdc_probe,
	.हटाओ		= imx_mmdc_हटाओ,
पूर्ण;

अटल पूर्णांक __init imx_mmdc_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&imx_mmdc_driver);
पूर्ण
postcore_initcall(imx_mmdc_init);
