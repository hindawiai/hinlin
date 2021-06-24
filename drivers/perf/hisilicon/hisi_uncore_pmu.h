<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HiSilicon SoC Hardware event counters support
 *
 * Copyright (C) 2017 Hisilicon Limited
 * Author: Anurup M <anurup.m@huawei.com>
 *         Shaokun Zhang <zhangshaokun@hisilicon.com>
 *
 * This code is based on the uncore PMUs like arm-cci and arm-ccn.
 */
#अगर_अघोषित __HISI_UNCORE_PMU_H__
#घोषणा __HISI_UNCORE_PMU_H__

#समावेश <linux/bitfield.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)     "hisi_pmu: " fmt

#घोषणा HISI_PMU_V2		0x30
#घोषणा HISI_MAX_COUNTERS 0x10
#घोषणा to_hisi_pmu(p)	(container_of(p, काष्ठा hisi_pmu, pmu))

#घोषणा HISI_PMU_ATTR(_name, _func, _config)				\
	(&((काष्ठा dev_ext_attribute[]) अणु				\
		अणु __ATTR(_name, 0444, _func, शून्य), (व्योम *)_config पूर्ण   \
	पूर्ण)[0].attr.attr)

#घोषणा HISI_PMU_FORMAT_ATTR(_name, _config)		\
	HISI_PMU_ATTR(_name, hisi_क्रमmat_sysfs_show, (व्योम *)_config)
#घोषणा HISI_PMU_EVENT_ATTR(_name, _config)		\
	HISI_PMU_ATTR(_name, hisi_event_sysfs_show, (अचिन्हित दीर्घ)_config)

#घोषणा HISI_PMU_EVENT_ATTR_EXTRACTOR(name, config, hi, lo)        \
	अटल अंतरभूत u32 hisi_get_##name(काष्ठा perf_event *event)            \
	अणु                                                                  \
		वापस FIELD_GET(GENMASK_ULL(hi, lo), event->attr.config);  \
	पूर्ण

काष्ठा hisi_pmu;

काष्ठा hisi_uncore_ops अणु
	व्योम (*ग_लिखो_evtype)(काष्ठा hisi_pmu *, पूर्णांक, u32);
	पूर्णांक (*get_event_idx)(काष्ठा perf_event *);
	u64 (*पढ़ो_counter)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *);
	व्योम (*ग_लिखो_counter)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *, u64);
	व्योम (*enable_counter)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *);
	व्योम (*disable_counter)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *);
	व्योम (*enable_counter_पूर्णांक)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *);
	व्योम (*disable_counter_पूर्णांक)(काष्ठा hisi_pmu *, काष्ठा hw_perf_event *);
	व्योम (*start_counters)(काष्ठा hisi_pmu *);
	व्योम (*stop_counters)(काष्ठा hisi_pmu *);
	u32 (*get_पूर्णांक_status)(काष्ठा hisi_pmu *hisi_pmu);
	व्योम (*clear_पूर्णांक_status)(काष्ठा hisi_pmu *hisi_pmu, पूर्णांक idx);
	व्योम (*enable_filter)(काष्ठा perf_event *event);
	व्योम (*disable_filter)(काष्ठा perf_event *event);
पूर्ण;

काष्ठा hisi_pmu_hwevents अणु
	काष्ठा perf_event *hw_events[HISI_MAX_COUNTERS];
	DECLARE_BITMAP(used_mask, HISI_MAX_COUNTERS);
	स्थिर काष्ठा attribute_group **attr_groups;
पूर्ण;

/* Generic pmu काष्ठा क्रम dअगरferent pmu types */
काष्ठा hisi_pmu अणु
	काष्ठा pmu pmu;
	स्थिर काष्ठा hisi_uncore_ops *ops;
	काष्ठा hisi_pmu_hwevents pmu_events;
	/* associated_cpus: All CPUs associated with the PMU */
	cpumask_t associated_cpus;
	/* CPU used क्रम counting */
	पूर्णांक on_cpu;
	पूर्णांक irq;
	काष्ठा device *dev;
	काष्ठा hlist_node node;
	पूर्णांक sccl_id;
	पूर्णांक ccl_id;
	व्योम __iomem *base;
	/* the ID of the PMU modules */
	u32 index_id;
	/* For DDRC PMU v2: each DDRC has more than one DMC */
	u32 sub_id;
	पूर्णांक num_counters;
	पूर्णांक counter_bits;
	/* check event code range */
	पूर्णांक check_event;
	u32 identअगरier;
पूर्ण;

पूर्णांक hisi_uncore_pmu_get_event_idx(काष्ठा perf_event *event);
व्योम hisi_uncore_pmu_पढ़ो(काष्ठा perf_event *event);
पूर्णांक hisi_uncore_pmu_add(काष्ठा perf_event *event, पूर्णांक flags);
व्योम hisi_uncore_pmu_del(काष्ठा perf_event *event, पूर्णांक flags);
व्योम hisi_uncore_pmu_start(काष्ठा perf_event *event, पूर्णांक flags);
व्योम hisi_uncore_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags);
व्योम hisi_uncore_pmu_set_event_period(काष्ठा perf_event *event);
व्योम hisi_uncore_pmu_event_update(काष्ठा perf_event *event);
पूर्णांक hisi_uncore_pmu_event_init(काष्ठा perf_event *event);
व्योम hisi_uncore_pmu_enable(काष्ठा pmu *pmu);
व्योम hisi_uncore_pmu_disable(काष्ठा pmu *pmu);
sमाप_प्रकार hisi_event_sysfs_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf);
sमाप_प्रकार hisi_क्रमmat_sysfs_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf);
sमाप_प्रकार hisi_cpumask_sysfs_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf);
पूर्णांक hisi_uncore_pmu_online_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);
पूर्णांक hisi_uncore_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);

sमाप_प्रकार hisi_uncore_pmu_identअगरier_attr_show(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *page);
पूर्णांक hisi_uncore_pmu_init_irq(काष्ठा hisi_pmu *hisi_pmu,
			     काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर /* __HISI_UNCORE_PMU_H__ */
