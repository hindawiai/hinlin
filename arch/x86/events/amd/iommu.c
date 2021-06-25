<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Advanced Micro Devices, Inc.
 *
 * Author: Steven Kinney <Steven.Kinney@amd.com>
 * Author: Suravee Suthikulpanit <Suraveee.Suthikulpanit@amd.com>
 *
 * Perf: amd_iommu - AMD IOMMU Perक्रमmance Counter PMU implementation
 */

#घोषणा pr_fmt(fmt)	"perf/amd_iommu: " fmt

#समावेश <linux/perf_event.h>
#समावेश <linux/init.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/slab.h>
#समावेश <linux/amd-iommu.h>

#समावेश "../perf_event.h"
#समावेश "iommu.h"

/* iommu pmu conf masks */
#घोषणा GET_CSOURCE(x)     ((x)->conf & 0xFFULL)
#घोषणा GET_DEVID(x)       (((x)->conf >> 8)  & 0xFFFFULL)
#घोषणा GET_DOMID(x)       (((x)->conf >> 24) & 0xFFFFULL)
#घोषणा GET_PASID(x)       (((x)->conf >> 40) & 0xFFFFFULL)

/* iommu pmu conf1 masks */
#घोषणा GET_DEVID_MASK(x)  ((x)->conf1  & 0xFFFFULL)
#घोषणा GET_DOMID_MASK(x)  (((x)->conf1 >> 16) & 0xFFFFULL)
#घोषणा GET_PASID_MASK(x)  (((x)->conf1 >> 32) & 0xFFFFFULL)

#घोषणा IOMMU_NAME_SIZE 16

काष्ठा perf_amd_iommu अणु
	काष्ठा list_head list;
	काष्ठा pmu pmu;
	काष्ठा amd_iommu *iommu;
	अक्षर name[IOMMU_NAME_SIZE];
	u8 max_banks;
	u8 max_counters;
	u64 cntr_assign_mask;
	raw_spinlock_t lock;
पूर्ण;

अटल LIST_HEAD(perf_amd_iommu_list);

/*---------------------------------------------
 * sysfs क्रमmat attributes
 *---------------------------------------------*/
PMU_FORMAT_ATTR(csource,    "config:0-7");
PMU_FORMAT_ATTR(devid,      "config:8-23");
PMU_FORMAT_ATTR(करोmid,      "config:24-39");
PMU_FORMAT_ATTR(pasid,      "config:40-59");
PMU_FORMAT_ATTR(devid_mask, "config1:0-15");
PMU_FORMAT_ATTR(करोmid_mask, "config1:16-31");
PMU_FORMAT_ATTR(pasid_mask, "config1:32-51");

अटल काष्ठा attribute *iommu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_csource.attr,
	&क्रमmat_attr_devid.attr,
	&क्रमmat_attr_pasid.attr,
	&क्रमmat_attr_करोmid.attr,
	&क्रमmat_attr_devid_mask.attr,
	&क्रमmat_attr_pasid_mask.attr,
	&क्रमmat_attr_करोmid_mask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group amd_iommu_क्रमmat_group = अणु
	.name = "format",
	.attrs = iommu_क्रमmat_attrs,
पूर्ण;

/*---------------------------------------------
 * sysfs events attributes
 *---------------------------------------------*/
अटल काष्ठा attribute_group amd_iommu_events_group = अणु
	.name = "events",
पूर्ण;

काष्ठा amd_iommu_event_desc अणु
	काष्ठा device_attribute attr;
	स्थिर अक्षर *event;
पूर्ण;

अटल sमाप_प्रकार _iommu_event_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा amd_iommu_event_desc *event =
		container_of(attr, काष्ठा amd_iommu_event_desc, attr);
	वापस प्र_लिखो(buf, "%s\n", event->event);
पूर्ण

#घोषणा AMD_IOMMU_EVENT_DESC(_name, _event)			\
अणु								\
	.attr  = __ATTR(_name, 0444, _iommu_event_show, शून्य),	\
	.event = _event,					\
पूर्ण

अटल काष्ठा amd_iommu_event_desc amd_iommu_v2_event_descs[] = अणु
	AMD_IOMMU_EVENT_DESC(mem_pass_untrans,        "csource=0x01"),
	AMD_IOMMU_EVENT_DESC(mem_pass_pretrans,       "csource=0x02"),
	AMD_IOMMU_EVENT_DESC(mem_pass_excl,           "csource=0x03"),
	AMD_IOMMU_EVENT_DESC(mem_target_पात,        "csource=0x04"),
	AMD_IOMMU_EVENT_DESC(mem_trans_total,         "csource=0x05"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_tlb_pte_hit,   "csource=0x06"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_tlb_pte_mis,   "csource=0x07"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_tlb_pde_hit,   "csource=0x08"),
	AMD_IOMMU_EVENT_DESC(mem_iommu_tlb_pde_mis,   "csource=0x09"),
	AMD_IOMMU_EVENT_DESC(mem_dte_hit,             "csource=0x0a"),
	AMD_IOMMU_EVENT_DESC(mem_dte_mis,             "csource=0x0b"),
	AMD_IOMMU_EVENT_DESC(page_tbl_पढ़ो_tot,       "csource=0x0c"),
	AMD_IOMMU_EVENT_DESC(page_tbl_पढ़ो_nst,       "csource=0x0d"),
	AMD_IOMMU_EVENT_DESC(page_tbl_पढ़ो_gst,       "csource=0x0e"),
	AMD_IOMMU_EVENT_DESC(पूर्णांक_dte_hit,             "csource=0x0f"),
	AMD_IOMMU_EVENT_DESC(पूर्णांक_dte_mis,             "csource=0x10"),
	AMD_IOMMU_EVENT_DESC(cmd_processed,           "csource=0x11"),
	AMD_IOMMU_EVENT_DESC(cmd_processed_inv,       "csource=0x12"),
	AMD_IOMMU_EVENT_DESC(tlb_inv,                 "csource=0x13"),
	AMD_IOMMU_EVENT_DESC(ign_rd_wr_mmio_1ff8h,    "csource=0x14"),
	AMD_IOMMU_EVENT_DESC(vapic_पूर्णांक_non_guest,     "csource=0x15"),
	AMD_IOMMU_EVENT_DESC(vapic_पूर्णांक_guest,         "csource=0x16"),
	AMD_IOMMU_EVENT_DESC(smi_recv,                "csource=0x17"),
	AMD_IOMMU_EVENT_DESC(smi_blk,                 "csource=0x18"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

/*---------------------------------------------
 * sysfs cpumask attributes
 *---------------------------------------------*/
अटल cpumask_t iommu_cpumask;

अटल sमाप_प्रकार _iommu_cpumask_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &iommu_cpumask);
पूर्ण
अटल DEVICE_ATTR(cpumask, S_IRUGO, _iommu_cpumask_show, शून्य);

अटल काष्ठा attribute *iommu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group amd_iommu_cpumask_group = अणु
	.attrs = iommu_cpumask_attrs,
पूर्ण;

/*---------------------------------------------*/

अटल पूर्णांक get_next_avail_iommu_bnk_cntr(काष्ठा perf_event *event)
अणु
	काष्ठा perf_amd_iommu *piommu = container_of(event->pmu, काष्ठा perf_amd_iommu, pmu);
	पूर्णांक max_cntrs = piommu->max_counters;
	पूर्णांक max_banks = piommu->max_banks;
	u32 shअगरt, bank, cntr;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	raw_spin_lock_irqsave(&piommu->lock, flags);

	क्रम (bank = 0, shअगरt = 0; bank < max_banks; bank++) अणु
		क्रम (cntr = 0; cntr < max_cntrs; cntr++) अणु
			shअगरt = bank + (bank*3) + cntr;
			अगर (piommu->cntr_assign_mask & BIT_ULL(shअगरt)) अणु
				जारी;
			पूर्ण अन्यथा अणु
				piommu->cntr_assign_mask |= BIT_ULL(shअगरt);
				event->hw.iommu_bank = bank;
				event->hw.iommu_cntr = cntr;
				retval = 0;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	retval = -ENOSPC;
out:
	raw_spin_unlock_irqrestore(&piommu->lock, flags);
	वापस retval;
पूर्ण

अटल पूर्णांक clear_avail_iommu_bnk_cntr(काष्ठा perf_amd_iommu *perf_iommu,
					u8 bank, u8 cntr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक max_banks, max_cntrs;
	पूर्णांक shअगरt = 0;

	max_banks = perf_iommu->max_banks;
	max_cntrs = perf_iommu->max_counters;

	अगर ((bank > max_banks) || (cntr > max_cntrs))
		वापस -EINVAL;

	shअगरt = bank + cntr + (bank*3);

	raw_spin_lock_irqsave(&perf_iommu->lock, flags);
	perf_iommu->cntr_assign_mask &= ~(1ULL<<shअगरt);
	raw_spin_unlock_irqrestore(&perf_iommu->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_iommu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* test the event attr type check क्रम PMU क्रमागतeration */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * IOMMU counters are shared across all cores.
	 * Thereक्रमe, it करोes not support per-process mode.
	 * Also, it करोes not support event sampling mode.
	 */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	/* update the hw_perf_event काष्ठा with the iommu config data */
	hwc->conf  = event->attr.config;
	hwc->conf1 = event->attr.config1;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा amd_iommu *perf_event_2_iommu(काष्ठा perf_event *ev)
अणु
	वापस (container_of(ev->pmu, काष्ठा perf_amd_iommu, pmu))->iommu;
पूर्ण

अटल व्योम perf_iommu_enable_event(काष्ठा perf_event *ev)
अणु
	काष्ठा amd_iommu *iommu = perf_event_2_iommu(ev);
	काष्ठा hw_perf_event *hwc = &ev->hw;
	u8 bank = hwc->iommu_bank;
	u8 cntr = hwc->iommu_cntr;
	u64 reg = 0ULL;

	reg = GET_CSOURCE(hwc);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_COUNTER_SRC_REG, &reg);

	reg = GET_DEVID_MASK(hwc);
	reg = GET_DEVID(hwc) | (reg << 32);
	अगर (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_DEVID_MATCH_REG, &reg);

	reg = GET_PASID_MASK(hwc);
	reg = GET_PASID(hwc) | (reg << 32);
	अगर (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_PASID_MATCH_REG, &reg);

	reg = GET_DOMID_MASK(hwc);
	reg = GET_DOMID(hwc) | (reg << 32);
	अगर (reg)
		reg |= BIT(31);
	amd_iommu_pc_set_reg(iommu, bank, cntr, IOMMU_PC_DOMID_MATCH_REG, &reg);
पूर्ण

अटल व्योम perf_iommu_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा amd_iommu *iommu = perf_event_2_iommu(event);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 reg = 0ULL;

	amd_iommu_pc_set_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
			     IOMMU_PC_COUNTER_SRC_REG, &reg);
पूर्ण

अटल व्योम perf_iommu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;

	/*
	 * To account क्रम घातer-gating, which prevents ग_लिखो to
	 * the counter, we need to enable the counter
	 * beक्रमe setting up counter रेजिस्टर.
	 */
	perf_iommu_enable_event(event);

	अगर (flags & PERF_EF_RELOAD) अणु
		u64 count = 0;
		काष्ठा amd_iommu *iommu = perf_event_2_iommu(event);

		/*
		 * Since the IOMMU PMU only support counting mode,
		 * the counter always start with value zero.
		 */
		amd_iommu_pc_set_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
				     IOMMU_PC_COUNTER_REG, &count);
	पूर्ण

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम perf_iommu_पढ़ो(काष्ठा perf_event *event)
अणु
	u64 count;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा amd_iommu *iommu = perf_event_2_iommu(event);

	अगर (amd_iommu_pc_get_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
				 IOMMU_PC_COUNTER_REG, &count))
		वापस;

	/* IOMMU pc counter रेजिस्टर is only 48 bits */
	count &= GENMASK_ULL(47, 0);

	/*
	 * Since the counter always start with value zero,
	 * simply just accumulate the count क्रम the event.
	 */
	local64_add(count, &event->count);
पूर्ण

अटल व्योम perf_iommu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	/*
	 * To account क्रम घातer-gating, in which पढ़ोing the counter would
	 * वापस zero, we need to पढ़ो the रेजिस्टर beक्रमe disabling.
	 */
	perf_iommu_पढ़ो(event);
	hwc->state |= PERF_HES_UPTODATE;

	perf_iommu_disable_event(event);
	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;
पूर्ण

अटल पूर्णांक perf_iommu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक retval;

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* request an iommu bank/counter */
	retval = get_next_avail_iommu_bnk_cntr(event);
	अगर (retval)
		वापस retval;

	अगर (flags & PERF_EF_START)
		perf_iommu_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

अटल व्योम perf_iommu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_amd_iommu *perf_iommu =
			container_of(event->pmu, काष्ठा perf_amd_iommu, pmu);

	perf_iommu_stop(event, PERF_EF_UPDATE);

	/* clear the asचिन्हित iommu bank/counter */
	clear_avail_iommu_bnk_cntr(perf_iommu,
				   hwc->iommu_bank, hwc->iommu_cntr);

	perf_event_update_userpage(event);
पूर्ण

अटल __init पूर्णांक _init_events_attrs(व्योम)
अणु
	पूर्णांक i = 0, j;
	काष्ठा attribute **attrs;

	जबतक (amd_iommu_v2_event_descs[i].attr.attr.name)
		i++;

	attrs = kसुस्मृति(i + 1, माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	क्रम (j = 0; j < i; j++)
		attrs[j] = &amd_iommu_v2_event_descs[j].attr.attr;

	amd_iommu_events_group.attrs = attrs;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group *amd_iommu_attr_groups[] = अणु
	&amd_iommu_क्रमmat_group,
	&amd_iommu_cpumask_group,
	&amd_iommu_events_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pmu iommu_pmu __initस्थिर = अणु
	.event_init	= perf_iommu_event_init,
	.add		= perf_iommu_add,
	.del		= perf_iommu_del,
	.start		= perf_iommu_start,
	.stop		= perf_iommu_stop,
	.पढ़ो		= perf_iommu_पढ़ो,
	.task_ctx_nr	= perf_invalid_context,
	.attr_groups	= amd_iommu_attr_groups,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;

अटल __init पूर्णांक init_one_iommu(अचिन्हित पूर्णांक idx)
अणु
	काष्ठा perf_amd_iommu *perf_iommu;
	पूर्णांक ret;

	perf_iommu = kzalloc(माप(काष्ठा perf_amd_iommu), GFP_KERNEL);
	अगर (!perf_iommu)
		वापस -ENOMEM;

	raw_spin_lock_init(&perf_iommu->lock);

	perf_iommu->pmu          = iommu_pmu;
	perf_iommu->iommu        = get_amd_iommu(idx);
	perf_iommu->max_banks    = amd_iommu_pc_get_max_banks(idx);
	perf_iommu->max_counters = amd_iommu_pc_get_max_counters(idx);

	अगर (!perf_iommu->iommu ||
	    !perf_iommu->max_banks ||
	    !perf_iommu->max_counters) अणु
		kमुक्त(perf_iommu);
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(perf_iommu->name, IOMMU_NAME_SIZE, "amd_iommu_%u", idx);

	ret = perf_pmu_रेजिस्टर(&perf_iommu->pmu, perf_iommu->name, -1);
	अगर (!ret) अणु
		pr_info("Detected AMD IOMMU #%d (%d banks, %d counters/bank).\n",
			idx, perf_iommu->max_banks, perf_iommu->max_counters);
		list_add_tail(&perf_iommu->list, &perf_amd_iommu_list);
	पूर्ण अन्यथा अणु
		pr_warn("Error initializing IOMMU %d.\n", idx);
		kमुक्त(perf_iommu);
	पूर्ण
	वापस ret;
पूर्ण

अटल __init पूर्णांक amd_iommu_pc_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, cnt = 0;
	पूर्णांक ret;

	/* Make sure the IOMMU PC resource is available */
	अगर (!amd_iommu_pc_supported())
		वापस -ENODEV;

	ret = _init_events_attrs();
	अगर (ret)
		वापस ret;

	/*
	 * An IOMMU PMU is specअगरic to an IOMMU, and can function independently.
	 * So we go through all IOMMUs and ignore the one that fails init
	 * unless all IOMMU are failing.
	 */
	क्रम (i = 0; i < amd_iommu_get_num_iommus(); i++) अणु
		ret = init_one_iommu(i);
		अगर (!ret)
			cnt++;
	पूर्ण

	अगर (!cnt) अणु
		kमुक्त(amd_iommu_events_group.attrs);
		वापस -ENODEV;
	पूर्ण

	/* Init cpumask attributes to only core 0 */
	cpumask_set_cpu(0, &iommu_cpumask);
	वापस 0;
पूर्ण

device_initcall(amd_iommu_pc_init);
