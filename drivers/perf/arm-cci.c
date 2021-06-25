<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// CCI Cache Coherent Interconnect PMU driver
// Copyright (C) 2013-2018 Arm Ltd.
// Author: Punit Agrawal <punit.agrawal@arm.com>, Suzuki Poulose <suzuki.poulose@arm.com>

#समावेश <linux/arm-cci.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा DRIVER_NAME		"ARM-CCI PMU"

#घोषणा CCI_PMCR		0x0100
#घोषणा CCI_PID2		0x0fe8

#घोषणा CCI_PMCR_CEN		0x00000001
#घोषणा CCI_PMCR_NCNT_MASK	0x0000f800
#घोषणा CCI_PMCR_NCNT_SHIFT	11

#घोषणा CCI_PID2_REV_MASK	0xf0
#घोषणा CCI_PID2_REV_SHIFT	4

#घोषणा CCI_PMU_EVT_SEL		0x000
#घोषणा CCI_PMU_CNTR		0x004
#घोषणा CCI_PMU_CNTR_CTRL	0x008
#घोषणा CCI_PMU_OVRFLW		0x00c

#घोषणा CCI_PMU_OVRFLW_FLAG	1

#घोषणा CCI_PMU_CNTR_SIZE(model)	((model)->cntr_size)
#घोषणा CCI_PMU_CNTR_BASE(model, idx)	((idx) * CCI_PMU_CNTR_SIZE(model))
#घोषणा CCI_PMU_CNTR_MASK		((1ULL << 32) -1)
#घोषणा CCI_PMU_CNTR_LAST(cci_pmu)	(cci_pmu->num_cntrs - 1)

#घोषणा CCI_PMU_MAX_HW_CNTRS(model) \
	((model)->num_hw_cntrs + (model)->fixed_hw_cntrs)

/* Types of पूर्णांकerfaces that can generate events */
क्रमागत अणु
	CCI_IF_SLAVE,
	CCI_IF_MASTER,
#अगर_घोषित CONFIG_ARM_CCI5xx_PMU
	CCI_IF_GLOBAL,
#पूर्ण_अगर
	CCI_IF_MAX,
पूर्ण;

#घोषणा NUM_HW_CNTRS_CII_4XX	4
#घोषणा NUM_HW_CNTRS_CII_5XX	8
#घोषणा NUM_HW_CNTRS_MAX	NUM_HW_CNTRS_CII_5XX

#घोषणा FIXED_HW_CNTRS_CII_4XX	1
#घोषणा FIXED_HW_CNTRS_CII_5XX	0
#घोषणा FIXED_HW_CNTRS_MAX	FIXED_HW_CNTRS_CII_4XX

#घोषणा HW_CNTRS_MAX		(NUM_HW_CNTRS_MAX + FIXED_HW_CNTRS_MAX)

काष्ठा event_range अणु
	u32 min;
	u32 max;
पूर्ण;

काष्ठा cci_pmu_hw_events अणु
	काष्ठा perf_event **events;
	अचिन्हित दीर्घ *used_mask;
	raw_spinlock_t pmu_lock;
पूर्ण;

काष्ठा cci_pmu;
/*
 * काष्ठा cci_pmu_model:
 * @fixed_hw_cntrs - Number of fixed event counters
 * @num_hw_cntrs - Maximum number of programmable event counters
 * @cntr_size - Size of an event counter mapping
 */
काष्ठा cci_pmu_model अणु
	अक्षर *name;
	u32 fixed_hw_cntrs;
	u32 num_hw_cntrs;
	u32 cntr_size;
	काष्ठा attribute **क्रमmat_attrs;
	काष्ठा attribute **event_attrs;
	काष्ठा event_range event_ranges[CCI_IF_MAX];
	पूर्णांक (*validate_hw_event)(काष्ठा cci_pmu *, अचिन्हित दीर्घ);
	पूर्णांक (*get_event_idx)(काष्ठा cci_pmu *, काष्ठा cci_pmu_hw_events *, अचिन्हित दीर्घ);
	व्योम (*ग_लिखो_counters)(काष्ठा cci_pmu *, अचिन्हित दीर्घ *);
पूर्ण;

अटल काष्ठा cci_pmu_model cci_pmu_models[];

काष्ठा cci_pmu अणु
	व्योम __iomem *base;
	व्योम __iomem *ctrl_base;
	काष्ठा pmu pmu;
	पूर्णांक cpu;
	पूर्णांक nr_irqs;
	पूर्णांक *irqs;
	अचिन्हित दीर्घ active_irqs;
	स्थिर काष्ठा cci_pmu_model *model;
	काष्ठा cci_pmu_hw_events hw_events;
	काष्ठा platक्रमm_device *plat_device;
	पूर्णांक num_cntrs;
	atomic_t active_events;
	काष्ठा mutex reserve_mutex;
पूर्ण;

#घोषणा to_cci_pmu(c)	(container_of(c, काष्ठा cci_pmu, pmu))

अटल काष्ठा cci_pmu *g_cci_pmu;

क्रमागत cci_models अणु
#अगर_घोषित CONFIG_ARM_CCI400_PMU
	CCI400_R0,
	CCI400_R1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_CCI5xx_PMU
	CCI500_R0,
	CCI550_R0,
#पूर्ण_अगर
	CCI_MODEL_MAX
पूर्ण;

अटल व्योम pmu_ग_लिखो_counters(काष्ठा cci_pmu *cci_pmu,
				 अचिन्हित दीर्घ *mask);
अटल sमाप_प्रकार __maybe_unused cci_pmu_क्रमmat_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार __maybe_unused cci_pmu_event_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);

#घोषणा CCI_EXT_ATTR_ENTRY(_name, _func, _config) 				\
	&((काष्ठा dev_ext_attribute[]) अणु					\
		अणु __ATTR(_name, S_IRUGO, _func, शून्य), (व्योम *)_config पूर्ण	\
	पूर्ण)[0].attr.attr

#घोषणा CCI_FORMAT_EXT_ATTR_ENTRY(_name, _config) \
	CCI_EXT_ATTR_ENTRY(_name, cci_pmu_क्रमmat_show, (अक्षर *)_config)
#घोषणा CCI_EVENT_EXT_ATTR_ENTRY(_name, _config) \
	CCI_EXT_ATTR_ENTRY(_name, cci_pmu_event_show, (अचिन्हित दीर्घ)_config)

/* CCI400 PMU Specअगरic definitions */

#अगर_घोषित CONFIG_ARM_CCI400_PMU

/* Port ids */
#घोषणा CCI400_PORT_S0		0
#घोषणा CCI400_PORT_S1		1
#घोषणा CCI400_PORT_S2		2
#घोषणा CCI400_PORT_S3		3
#घोषणा CCI400_PORT_S4		4
#घोषणा CCI400_PORT_M0		5
#घोषणा CCI400_PORT_M1		6
#घोषणा CCI400_PORT_M2		7

#घोषणा CCI400_R1_PX		5

/*
 * Instead of an event id to monitor CCI cycles, a dedicated counter is
 * provided. Use 0xff to represent CCI cycles and hope that no future revisions
 * make use of this event in hardware.
 */
क्रमागत cci400_perf_events अणु
	CCI400_PMU_CYCLES = 0xff
पूर्ण;

#घोषणा CCI400_PMU_CYCLE_CNTR_IDX	0
#घोषणा CCI400_PMU_CNTR0_IDX		1

/*
 * CCI PMU event id is an 8-bit value made of two parts - bits 7:5 क्रम one of 8
 * ports and bits 4:0 are event codes. There are dअगरferent event codes
 * associated with each port type.
 *
 * Additionally, the range of events associated with the port types changed
 * between Rev0 and Rev1.
 *
 * The स्थिरants below define the range of valid codes क्रम each port type क्रम
 * the dअगरferent revisions and are used to validate the event to be monitored.
 */

#घोषणा CCI400_PMU_EVENT_MASK		0xffUL
#घोषणा CCI400_PMU_EVENT_SOURCE_SHIFT	5
#घोषणा CCI400_PMU_EVENT_SOURCE_MASK	0x7
#घोषणा CCI400_PMU_EVENT_CODE_SHIFT	0
#घोषणा CCI400_PMU_EVENT_CODE_MASK	0x1f
#घोषणा CCI400_PMU_EVENT_SOURCE(event) \
	((event >> CCI400_PMU_EVENT_SOURCE_SHIFT) & \
			CCI400_PMU_EVENT_SOURCE_MASK)
#घोषणा CCI400_PMU_EVENT_CODE(event) \
	((event >> CCI400_PMU_EVENT_CODE_SHIFT) & CCI400_PMU_EVENT_CODE_MASK)

#घोषणा CCI400_R0_SLAVE_PORT_MIN_EV	0x00
#घोषणा CCI400_R0_SLAVE_PORT_MAX_EV	0x13
#घोषणा CCI400_R0_MASTER_PORT_MIN_EV	0x14
#घोषणा CCI400_R0_MASTER_PORT_MAX_EV	0x1a

#घोषणा CCI400_R1_SLAVE_PORT_MIN_EV	0x00
#घोषणा CCI400_R1_SLAVE_PORT_MAX_EV	0x14
#घोषणा CCI400_R1_MASTER_PORT_MIN_EV	0x00
#घोषणा CCI400_R1_MASTER_PORT_MAX_EV	0x11

#घोषणा CCI400_CYCLE_EVENT_EXT_ATTR_ENTRY(_name, _config) \
	CCI_EXT_ATTR_ENTRY(_name, cci400_pmu_cycle_event_show, \
					(अचिन्हित दीर्घ)_config)

अटल sमाप_प्रकार cci400_pmu_cycle_event_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf);

अटल काष्ठा attribute *cci400_pmu_क्रमmat_attrs[] = अणु
	CCI_FORMAT_EXT_ATTR_ENTRY(event, "config:0-4"),
	CCI_FORMAT_EXT_ATTR_ENTRY(source, "config:5-7"),
	शून्य
पूर्ण;

अटल काष्ठा attribute *cci400_r0_pmu_event_attrs[] = अणु
	/* Slave events */
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_any, 0x0),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_device, 0x01),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_normal_or_nonshareable, 0x2),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_inner_or_outershareable, 0x3),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_cache_मुख्यtenance, 0x4),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_mem_barrier, 0x5),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_sync_barrier, 0x6),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_dvm_msg, 0x7),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_dvm_msg_sync, 0x8),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_stall_tt_full, 0x9),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_data_last_hs_snoop, 0xA),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_data_stall_rvalids_h_rपढ़ोy_l, 0xB),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_any, 0xC),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_device, 0xD),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_normal_or_nonshareable, 0xE),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_inner_or_outershare_wback_wclean, 0xF),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_ग_लिखो_unique, 0x10),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_ग_लिखो_line_unique, 0x11),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_evict, 0x12),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_stall_tt_full, 0x13),
	/* Master events */
	CCI_EVENT_EXT_ATTR_ENTRY(mi_retry_speculative_fetch, 0x14),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_addr_hazard, 0x15),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_id_hazard, 0x16),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_tt_full, 0x17),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_barrier_hazard, 0x18),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_barrier_hazard, 0x19),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_tt_full, 0x1A),
	/* Special event क्रम cycles counter */
	CCI400_CYCLE_EVENT_EXT_ATTR_ENTRY(cycles, 0xff),
	शून्य
पूर्ण;

अटल काष्ठा attribute *cci400_r1_pmu_event_attrs[] = अणु
	/* Slave events */
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_any, 0x0),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_device, 0x01),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_normal_or_nonshareable, 0x2),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_inner_or_outershareable, 0x3),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_cache_मुख्यtenance, 0x4),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_mem_barrier, 0x5),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_sync_barrier, 0x6),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_dvm_msg, 0x7),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_dvm_msg_sync, 0x8),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_stall_tt_full, 0x9),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_data_last_hs_snoop, 0xA),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_data_stall_rvalids_h_rपढ़ोy_l, 0xB),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_any, 0xC),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_device, 0xD),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_normal_or_nonshareable, 0xE),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_inner_or_outershare_wback_wclean, 0xF),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_ग_लिखो_unique, 0x10),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_ग_लिखो_line_unique, 0x11),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_evict, 0x12),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_stall_tt_full, 0x13),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_stall_slave_id_hazard, 0x14),
	/* Master events */
	CCI_EVENT_EXT_ATTR_ENTRY(mi_retry_speculative_fetch, 0x0),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_stall_cycle_addr_hazard, 0x1),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_master_id_hazard, 0x2),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_hi_prio_rtq_full, 0x3),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_barrier_hazard, 0x4),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_barrier_hazard, 0x5),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_wtq_full, 0x6),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_low_prio_rtq_full, 0x7),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_mid_prio_rtq_full, 0x8),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_qvn_vn0, 0x9),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_qvn_vn1, 0xA),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_qvn_vn2, 0xB),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall_qvn_vn3, 0xC),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_qvn_vn0, 0xD),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_qvn_vn1, 0xE),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_qvn_vn2, 0xF),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall_qvn_vn3, 0x10),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_unique_or_line_unique_addr_hazard, 0x11),
	/* Special event क्रम cycles counter */
	CCI400_CYCLE_EVENT_EXT_ATTR_ENTRY(cycles, 0xff),
	शून्य
पूर्ण;

अटल sमाप_प्रकार cci400_pmu_cycle_event_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
				काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "config=0x%lx\n", (अचिन्हित दीर्घ)eattr->var);
पूर्ण

अटल पूर्णांक cci400_get_event_idx(काष्ठा cci_pmu *cci_pmu,
				काष्ठा cci_pmu_hw_events *hw,
				अचिन्हित दीर्घ cci_event)
अणु
	पूर्णांक idx;

	/* cycles event idx is fixed */
	अगर (cci_event == CCI400_PMU_CYCLES) अणु
		अगर (test_and_set_bit(CCI400_PMU_CYCLE_CNTR_IDX, hw->used_mask))
			वापस -EAGAIN;

		वापस CCI400_PMU_CYCLE_CNTR_IDX;
	पूर्ण

	क्रम (idx = CCI400_PMU_CNTR0_IDX; idx <= CCI_PMU_CNTR_LAST(cci_pmu); ++idx)
		अगर (!test_and_set_bit(idx, hw->used_mask))
			वापस idx;

	/* No counters available */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक cci400_validate_hw_event(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ hw_event)
अणु
	u8 ev_source = CCI400_PMU_EVENT_SOURCE(hw_event);
	u8 ev_code = CCI400_PMU_EVENT_CODE(hw_event);
	पूर्णांक अगर_type;

	अगर (hw_event & ~CCI400_PMU_EVENT_MASK)
		वापस -ENOENT;

	अगर (hw_event == CCI400_PMU_CYCLES)
		वापस hw_event;

	चयन (ev_source) अणु
	हाल CCI400_PORT_S0:
	हाल CCI400_PORT_S1:
	हाल CCI400_PORT_S2:
	हाल CCI400_PORT_S3:
	हाल CCI400_PORT_S4:
		/* Slave Interface */
		अगर_type = CCI_IF_SLAVE;
		अवरोध;
	हाल CCI400_PORT_M0:
	हाल CCI400_PORT_M1:
	हाल CCI400_PORT_M2:
		/* Master Interface */
		अगर_type = CCI_IF_MASTER;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (ev_code >= cci_pmu->model->event_ranges[अगर_type].min &&
		ev_code <= cci_pmu->model->event_ranges[अगर_type].max)
		वापस hw_event;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक probe_cci400_revision(काष्ठा cci_pmu *cci_pmu)
अणु
	पूर्णांक rev;
	rev = पढ़ोl_relaxed(cci_pmu->ctrl_base + CCI_PID2) & CCI_PID2_REV_MASK;
	rev >>= CCI_PID2_REV_SHIFT;

	अगर (rev < CCI400_R1_PX)
		वापस CCI400_R0;
	अन्यथा
		वापस CCI400_R1;
पूर्ण

अटल स्थिर काष्ठा cci_pmu_model *probe_cci_model(काष्ठा cci_pmu *cci_pmu)
अणु
	अगर (platक्रमm_has_secure_cci_access())
		वापस &cci_pmu_models[probe_cci400_revision(cci_pmu)];
	वापस शून्य;
पूर्ण
#अन्यथा	/* !CONFIG_ARM_CCI400_PMU */
अटल अंतरभूत काष्ठा cci_pmu_model *probe_cci_model(काष्ठा cci_pmu *cci_pmu)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर	/* CONFIG_ARM_CCI400_PMU */

#अगर_घोषित CONFIG_ARM_CCI5xx_PMU

/*
 * CCI5xx PMU event id is an 9-bit value made of two parts.
 *	 bits [8:5] - Source क्रम the event
 *	 bits [4:0] - Event code (specअगरic to type of पूर्णांकerface)
 *
 *
 */

/* Port ids */
#घोषणा CCI5xx_PORT_S0			0x0
#घोषणा CCI5xx_PORT_S1			0x1
#घोषणा CCI5xx_PORT_S2			0x2
#घोषणा CCI5xx_PORT_S3			0x3
#घोषणा CCI5xx_PORT_S4			0x4
#घोषणा CCI5xx_PORT_S5			0x5
#घोषणा CCI5xx_PORT_S6			0x6

#घोषणा CCI5xx_PORT_M0			0x8
#घोषणा CCI5xx_PORT_M1			0x9
#घोषणा CCI5xx_PORT_M2			0xa
#घोषणा CCI5xx_PORT_M3			0xb
#घोषणा CCI5xx_PORT_M4			0xc
#घोषणा CCI5xx_PORT_M5			0xd
#घोषणा CCI5xx_PORT_M6			0xe

#घोषणा CCI5xx_PORT_GLOBAL		0xf

#घोषणा CCI5xx_PMU_EVENT_MASK		0x1ffUL
#घोषणा CCI5xx_PMU_EVENT_SOURCE_SHIFT	0x5
#घोषणा CCI5xx_PMU_EVENT_SOURCE_MASK	0xf
#घोषणा CCI5xx_PMU_EVENT_CODE_SHIFT	0x0
#घोषणा CCI5xx_PMU_EVENT_CODE_MASK	0x1f

#घोषणा CCI5xx_PMU_EVENT_SOURCE(event)	\
	((event >> CCI5xx_PMU_EVENT_SOURCE_SHIFT) & CCI5xx_PMU_EVENT_SOURCE_MASK)
#घोषणा CCI5xx_PMU_EVENT_CODE(event)	\
	((event >> CCI5xx_PMU_EVENT_CODE_SHIFT) & CCI5xx_PMU_EVENT_CODE_MASK)

#घोषणा CCI5xx_SLAVE_PORT_MIN_EV	0x00
#घोषणा CCI5xx_SLAVE_PORT_MAX_EV	0x1f
#घोषणा CCI5xx_MASTER_PORT_MIN_EV	0x00
#घोषणा CCI5xx_MASTER_PORT_MAX_EV	0x06
#घोषणा CCI5xx_GLOBAL_PORT_MIN_EV	0x00
#घोषणा CCI5xx_GLOBAL_PORT_MAX_EV	0x0f


#घोषणा CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(_name, _config) \
	CCI_EXT_ATTR_ENTRY(_name, cci5xx_pmu_global_event_show, \
					(अचिन्हित दीर्घ) _config)

अटल sमाप_प्रकार cci5xx_pmu_global_event_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf);

अटल काष्ठा attribute *cci5xx_pmu_क्रमmat_attrs[] = अणु
	CCI_FORMAT_EXT_ATTR_ENTRY(event, "config:0-4"),
	CCI_FORMAT_EXT_ATTR_ENTRY(source, "config:5-8"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *cci5xx_pmu_event_attrs[] = अणु
	/* Slave events */
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_arvalid, 0x0),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_dev, 0x1),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_nonshareable, 0x2),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_shareable_non_alloc, 0x3),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_shareable_alloc, 0x4),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_invalidate, 0x5),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_cache_मुख्यt, 0x6),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_dvm_msg, 0x7),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_rval, 0x8),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_hs_rlast_snoop, 0x9),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_hs_awalid, 0xA),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_dev, 0xB),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_non_shareable, 0xC),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_share_wb, 0xD),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_share_wlu, 0xE),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_share_wunique, 0xF),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_evict, 0x10),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_wrevict, 0x11),
	CCI_EVENT_EXT_ATTR_ENTRY(si_w_data_beat, 0x12),
	CCI_EVENT_EXT_ATTR_ENTRY(si_srq_acvalid, 0x13),
	CCI_EVENT_EXT_ATTR_ENTRY(si_srq_पढ़ो, 0x14),
	CCI_EVENT_EXT_ATTR_ENTRY(si_srq_clean, 0x15),
	CCI_EVENT_EXT_ATTR_ENTRY(si_srq_data_transfer_low, 0x16),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rrq_stall_arvalid, 0x17),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_data_stall, 0x18),
	CCI_EVENT_EXT_ATTR_ENTRY(si_wrq_stall, 0x19),
	CCI_EVENT_EXT_ATTR_ENTRY(si_w_data_stall, 0x1A),
	CCI_EVENT_EXT_ATTR_ENTRY(si_w_resp_stall, 0x1B),
	CCI_EVENT_EXT_ATTR_ENTRY(si_srq_stall, 0x1C),
	CCI_EVENT_EXT_ATTR_ENTRY(si_s_data_stall, 0x1D),
	CCI_EVENT_EXT_ATTR_ENTRY(si_rq_stall_ot_limit, 0x1E),
	CCI_EVENT_EXT_ATTR_ENTRY(si_r_stall_arbit, 0x1F),

	/* Master events */
	CCI_EVENT_EXT_ATTR_ENTRY(mi_r_data_beat_any, 0x0),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_w_data_beat_any, 0x1),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_rrq_stall, 0x2),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_r_data_stall, 0x3),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_wrq_stall, 0x4),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_w_data_stall, 0x5),
	CCI_EVENT_EXT_ATTR_ENTRY(mi_w_resp_stall, 0x6),

	/* Global events */
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_filter_bank_0_1, 0x0),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_filter_bank_2_3, 0x1),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_filter_bank_4_5, 0x2),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_filter_bank_6_7, 0x3),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_miss_filter_bank_0_1, 0x4),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_miss_filter_bank_2_3, 0x5),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_miss_filter_bank_4_5, 0x6),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_access_miss_filter_bank_6_7, 0x7),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_back_invalidation, 0x8),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_stall_alloc_busy, 0x9),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_stall_tt_full, 0xA),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_wrq, 0xB),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_cd_hs, 0xC),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_rq_stall_addr_hazard, 0xD),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_rq_stall_tt_full, 0xE),
	CCI5xx_GLOBAL_EVENT_EXT_ATTR_ENTRY(cci_snoop_rq_tzmp1_prot, 0xF),
	शून्य
पूर्ण;

अटल sमाप_प्रकार cci5xx_pmu_global_event_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
					काष्ठा dev_ext_attribute, attr);
	/* Global events have single fixed source code */
	वापस sysfs_emit(buf, "event=0x%lx,source=0x%x\n",
			  (अचिन्हित दीर्घ)eattr->var, CCI5xx_PORT_GLOBAL);
पूर्ण

/*
 * CCI500 provides 8 independent event counters that can count
 * any of the events available.
 * CCI500 PMU event source ids
 *	0x0-0x6 - Slave पूर्णांकerfaces
 *	0x8-0xD - Master पूर्णांकerfaces
 *	0xf     - Global Events
 *	0x7,0xe - Reserved
 */
अटल पूर्णांक cci500_validate_hw_event(काष्ठा cci_pmu *cci_pmu,
					अचिन्हित दीर्घ hw_event)
अणु
	u32 ev_source = CCI5xx_PMU_EVENT_SOURCE(hw_event);
	u32 ev_code = CCI5xx_PMU_EVENT_CODE(hw_event);
	पूर्णांक अगर_type;

	अगर (hw_event & ~CCI5xx_PMU_EVENT_MASK)
		वापस -ENOENT;

	चयन (ev_source) अणु
	हाल CCI5xx_PORT_S0:
	हाल CCI5xx_PORT_S1:
	हाल CCI5xx_PORT_S2:
	हाल CCI5xx_PORT_S3:
	हाल CCI5xx_PORT_S4:
	हाल CCI5xx_PORT_S5:
	हाल CCI5xx_PORT_S6:
		अगर_type = CCI_IF_SLAVE;
		अवरोध;
	हाल CCI5xx_PORT_M0:
	हाल CCI5xx_PORT_M1:
	हाल CCI5xx_PORT_M2:
	हाल CCI5xx_PORT_M3:
	हाल CCI5xx_PORT_M4:
	हाल CCI5xx_PORT_M5:
		अगर_type = CCI_IF_MASTER;
		अवरोध;
	हाल CCI5xx_PORT_GLOBAL:
		अगर_type = CCI_IF_GLOBAL;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (ev_code >= cci_pmu->model->event_ranges[अगर_type].min &&
		ev_code <= cci_pmu->model->event_ranges[अगर_type].max)
		वापस hw_event;

	वापस -ENOENT;
पूर्ण

/*
 * CCI550 provides 8 independent event counters that can count
 * any of the events available.
 * CCI550 PMU event source ids
 *	0x0-0x6 - Slave पूर्णांकerfaces
 *	0x8-0xe - Master पूर्णांकerfaces
 *	0xf     - Global Events
 *	0x7	- Reserved
 */
अटल पूर्णांक cci550_validate_hw_event(काष्ठा cci_pmu *cci_pmu,
					अचिन्हित दीर्घ hw_event)
अणु
	u32 ev_source = CCI5xx_PMU_EVENT_SOURCE(hw_event);
	u32 ev_code = CCI5xx_PMU_EVENT_CODE(hw_event);
	पूर्णांक अगर_type;

	अगर (hw_event & ~CCI5xx_PMU_EVENT_MASK)
		वापस -ENOENT;

	चयन (ev_source) अणु
	हाल CCI5xx_PORT_S0:
	हाल CCI5xx_PORT_S1:
	हाल CCI5xx_PORT_S2:
	हाल CCI5xx_PORT_S3:
	हाल CCI5xx_PORT_S4:
	हाल CCI5xx_PORT_S5:
	हाल CCI5xx_PORT_S6:
		अगर_type = CCI_IF_SLAVE;
		अवरोध;
	हाल CCI5xx_PORT_M0:
	हाल CCI5xx_PORT_M1:
	हाल CCI5xx_PORT_M2:
	हाल CCI5xx_PORT_M3:
	हाल CCI5xx_PORT_M4:
	हाल CCI5xx_PORT_M5:
	हाल CCI5xx_PORT_M6:
		अगर_type = CCI_IF_MASTER;
		अवरोध;
	हाल CCI5xx_PORT_GLOBAL:
		अगर_type = CCI_IF_GLOBAL;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (ev_code >= cci_pmu->model->event_ranges[अगर_type].min &&
		ev_code <= cci_pmu->model->event_ranges[अगर_type].max)
		वापस hw_event;

	वापस -ENOENT;
पूर्ण

#पूर्ण_अगर	/* CONFIG_ARM_CCI5xx_PMU */

/*
 * Program the CCI PMU counters which have PERF_HES_ARCH set
 * with the event period and mark them पढ़ोy beक्रमe we enable
 * PMU.
 */
अटल व्योम cci_pmu_sync_counters(काष्ठा cci_pmu *cci_pmu)
अणु
	पूर्णांक i;
	काष्ठा cci_pmu_hw_events *cci_hw = &cci_pmu->hw_events;
	DECLARE_BITMAP(mask, HW_CNTRS_MAX);

	biपंचांगap_zero(mask, cci_pmu->num_cntrs);
	क्रम_each_set_bit(i, cci_pmu->hw_events.used_mask, cci_pmu->num_cntrs) अणु
		काष्ठा perf_event *event = cci_hw->events[i];

		अगर (WARN_ON(!event))
			जारी;

		/* Leave the events which are not counting */
		अगर (event->hw.state & PERF_HES_STOPPED)
			जारी;
		अगर (event->hw.state & PERF_HES_ARCH) अणु
			set_bit(i, mask);
			event->hw.state &= ~PERF_HES_ARCH;
		पूर्ण
	पूर्ण

	pmu_ग_लिखो_counters(cci_pmu, mask);
पूर्ण

/* Should be called with cci_pmu->hw_events->pmu_lock held */
अटल व्योम __cci_pmu_enable_nosync(काष्ठा cci_pmu *cci_pmu)
अणु
	u32 val;

	/* Enable all the PMU counters. */
	val = पढ़ोl_relaxed(cci_pmu->ctrl_base + CCI_PMCR) | CCI_PMCR_CEN;
	ग_लिखोl(val, cci_pmu->ctrl_base + CCI_PMCR);
पूर्ण

/* Should be called with cci_pmu->hw_events->pmu_lock held */
अटल व्योम __cci_pmu_enable_sync(काष्ठा cci_pmu *cci_pmu)
अणु
	cci_pmu_sync_counters(cci_pmu);
	__cci_pmu_enable_nosync(cci_pmu);
पूर्ण

/* Should be called with cci_pmu->hw_events->pmu_lock held */
अटल व्योम __cci_pmu_disable(काष्ठा cci_pmu *cci_pmu)
अणु
	u32 val;

	/* Disable all the PMU counters. */
	val = पढ़ोl_relaxed(cci_pmu->ctrl_base + CCI_PMCR) & ~CCI_PMCR_CEN;
	ग_लिखोl(val, cci_pmu->ctrl_base + CCI_PMCR);
पूर्ण

अटल sमाप_प्रकार cci_pmu_क्रमmat_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
				काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "%s\n", (अक्षर *)eattr->var);
पूर्ण

अटल sमाप_प्रकार cci_pmu_event_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr = container_of(attr,
				काष्ठा dev_ext_attribute, attr);
	/* source parameter is mandatory क्रम normal PMU events */
	वापस sysfs_emit(buf, "source=?,event=0x%lx\n",
			  (अचिन्हित दीर्घ)eattr->var);
पूर्ण

अटल पूर्णांक pmu_is_valid_counter(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx)
अणु
	वापस 0 <= idx && idx <= CCI_PMU_CNTR_LAST(cci_pmu);
पूर्ण

अटल u32 pmu_पढ़ो_रेजिस्टर(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl_relaxed(cci_pmu->base +
			     CCI_PMU_CNTR_BASE(cci_pmu->model, idx) + offset);
पूर्ण

अटल व्योम pmu_ग_लिखो_रेजिस्टर(काष्ठा cci_pmu *cci_pmu, u32 value,
			       पूर्णांक idx, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl_relaxed(value, cci_pmu->base +
		       CCI_PMU_CNTR_BASE(cci_pmu->model, idx) + offset);
पूर्ण

अटल व्योम pmu_disable_counter(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx)
अणु
	pmu_ग_लिखो_रेजिस्टर(cci_pmu, 0, idx, CCI_PMU_CNTR_CTRL);
पूर्ण

अटल व्योम pmu_enable_counter(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx)
अणु
	pmu_ग_लिखो_रेजिस्टर(cci_pmu, 1, idx, CCI_PMU_CNTR_CTRL);
पूर्ण

अटल bool __maybe_unused
pmu_counter_is_enabled(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx)
अणु
	वापस (pmu_पढ़ो_रेजिस्टर(cci_pmu, idx, CCI_PMU_CNTR_CTRL) & 0x1) != 0;
पूर्ण

अटल व्योम pmu_set_event(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx, अचिन्हित दीर्घ event)
अणु
	pmu_ग_लिखो_रेजिस्टर(cci_pmu, event, idx, CCI_PMU_EVT_SEL);
पूर्ण

/*
 * For all counters on the CCI-PMU, disable any 'enabled' counters,
 * saving the changed counters in the mask, so that we can restore
 * it later using pmu_restore_counters. The mask is निजी to the
 * caller. We cannot rely on the used_mask मुख्यtained by the CCI_PMU
 * as it only tells us अगर the counter is asचिन्हित to perf_event or not.
 * The state of the perf_event cannot be locked by the PMU layer, hence
 * we check the inभागidual counter status (which can be locked by
 * cci_pm->hw_events->pmu_lock).
 *
 * @mask should be initialised to empty by the caller.
 */
अटल व्योम __maybe_unused
pmu_save_counters(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cci_pmu->num_cntrs; i++) अणु
		अगर (pmu_counter_is_enabled(cci_pmu, i)) अणु
			set_bit(i, mask);
			pmu_disable_counter(cci_pmu, i);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Restore the status of the counters. Reversal of the pmu_save_counters().
 * For each counter set in the mask, enable the counter back.
 */
अटल व्योम __maybe_unused
pmu_restore_counters(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक i;

	क्रम_each_set_bit(i, mask, cci_pmu->num_cntrs)
		pmu_enable_counter(cci_pmu, i);
पूर्ण

/*
 * Returns the number of programmable counters actually implemented
 * by the cci
 */
अटल u32 pmu_get_max_counters(काष्ठा cci_pmu *cci_pmu)
अणु
	वापस (पढ़ोl_relaxed(cci_pmu->ctrl_base + CCI_PMCR) &
		CCI_PMCR_NCNT_MASK) >> CCI_PMCR_NCNT_SHIFT;
पूर्ण

अटल पूर्णांक pmu_get_event_idx(काष्ठा cci_pmu_hw_events *hw, काष्ठा perf_event *event)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	अचिन्हित दीर्घ cci_event = event->hw.config_base;
	पूर्णांक idx;

	अगर (cci_pmu->model->get_event_idx)
		वापस cci_pmu->model->get_event_idx(cci_pmu, hw, cci_event);

	/* Generic code to find an unused idx from the mask */
	क्रम(idx = 0; idx <= CCI_PMU_CNTR_LAST(cci_pmu); idx++)
		अगर (!test_and_set_bit(idx, hw->used_mask))
			वापस idx;

	/* No counters available */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक pmu_map_event(काष्ठा perf_event *event)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);

	अगर (event->attr.type < PERF_TYPE_MAX ||
			!cci_pmu->model->validate_hw_event)
		वापस -ENOENT;

	वापस	cci_pmu->model->validate_hw_event(cci_pmu, event->attr.config);
पूर्ण

अटल पूर्णांक pmu_request_irq(काष्ठा cci_pmu *cci_pmu, irq_handler_t handler)
अणु
	पूर्णांक i;
	काष्ठा platक्रमm_device *pmu_device = cci_pmu->plat_device;

	अगर (unlikely(!pmu_device))
		वापस -ENODEV;

	अगर (cci_pmu->nr_irqs < 1) अणु
		dev_err(&pmu_device->dev, "no irqs for CCI PMUs defined\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Register all available CCI PMU पूर्णांकerrupts. In the पूर्णांकerrupt handler
	 * we iterate over the counters checking क्रम पूर्णांकerrupt source (the
	 * overflowing counter) and clear it.
	 *
	 * This should allow handling of non-unique पूर्णांकerrupt क्रम the counters.
	 */
	क्रम (i = 0; i < cci_pmu->nr_irqs; i++) अणु
		पूर्णांक err = request_irq(cci_pmu->irqs[i], handler, IRQF_SHARED,
				"arm-cci-pmu", cci_pmu);
		अगर (err) अणु
			dev_err(&pmu_device->dev, "unable to request IRQ%d for ARM CCI PMU counters\n",
				cci_pmu->irqs[i]);
			वापस err;
		पूर्ण

		set_bit(i, &cci_pmu->active_irqs);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pmu_मुक्त_irq(काष्ठा cci_pmu *cci_pmu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cci_pmu->nr_irqs; i++) अणु
		अगर (!test_and_clear_bit(i, &cci_pmu->active_irqs))
			जारी;

		मुक्त_irq(cci_pmu->irqs[i], cci_pmu);
	पूर्ण
पूर्ण

अटल u32 pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	काष्ठा hw_perf_event *hw_counter = &event->hw;
	पूर्णांक idx = hw_counter->idx;
	u32 value;

	अगर (unlikely(!pmu_is_valid_counter(cci_pmu, idx))) अणु
		dev_err(&cci_pmu->plat_device->dev, "Invalid CCI PMU counter %d\n", idx);
		वापस 0;
	पूर्ण
	value = pmu_पढ़ो_रेजिस्टर(cci_pmu, idx, CCI_PMU_CNTR);

	वापस value;
पूर्ण

अटल व्योम pmu_ग_लिखो_counter(काष्ठा cci_pmu *cci_pmu, u32 value, पूर्णांक idx)
अणु
	pmu_ग_लिखो_रेजिस्टर(cci_pmu, value, idx, CCI_PMU_CNTR);
पूर्ण

अटल व्योम __pmu_ग_लिखो_counters(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक i;
	काष्ठा cci_pmu_hw_events *cci_hw = &cci_pmu->hw_events;

	क्रम_each_set_bit(i, mask, cci_pmu->num_cntrs) अणु
		काष्ठा perf_event *event = cci_hw->events[i];

		अगर (WARN_ON(!event))
			जारी;
		pmu_ग_लिखो_counter(cci_pmu, local64_पढ़ो(&event->hw.prev_count), i);
	पूर्ण
पूर्ण

अटल व्योम pmu_ग_लिखो_counters(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ *mask)
अणु
	अगर (cci_pmu->model->ग_लिखो_counters)
		cci_pmu->model->ग_लिखो_counters(cci_pmu, mask);
	अन्यथा
		__pmu_ग_लिखो_counters(cci_pmu, mask);
पूर्ण

#अगर_घोषित CONFIG_ARM_CCI5xx_PMU

/*
 * CCI-500/CCI-550 has advanced घातer saving policies, which could gate the
 * घड़ीs to the PMU counters, which makes the ग_लिखोs to them ineffective.
 * The only way to ग_लिखो to those counters is when the global counters
 * are enabled and the particular counter is enabled.
 *
 * So we करो the following :
 *
 * 1) Disable all the PMU counters, saving their current state
 * 2) Enable the global PMU profiling, now that all counters are
 *    disabled.
 *
 * For each counter to be programmed, repeat steps 3-7:
 *
 * 3) Write an invalid event code to the event control रेजिस्टर क्रम the
      counter, so that the counters are not modअगरied.
 * 4) Enable the counter control क्रम the counter.
 * 5) Set the counter value
 * 6) Disable the counter
 * 7) Restore the event in the target counter
 *
 * 8) Disable the global PMU.
 * 9) Restore the status of the rest of the counters.
 *
 * We choose an event which क्रम CCI-5xx is guaranteed not to count.
 * We use the highest possible event code (0x1f) क्रम the master पूर्णांकerface 0.
 */
#घोषणा CCI5xx_INVALID_EVENT	((CCI5xx_PORT_M0 << CCI5xx_PMU_EVENT_SOURCE_SHIFT) | \
				 (CCI5xx_PMU_EVENT_CODE_MASK << CCI5xx_PMU_EVENT_CODE_SHIFT))
अटल व्योम cci5xx_pmu_ग_लिखो_counters(काष्ठा cci_pmu *cci_pmu, अचिन्हित दीर्घ *mask)
अणु
	पूर्णांक i;
	DECLARE_BITMAP(saved_mask, HW_CNTRS_MAX);

	biपंचांगap_zero(saved_mask, cci_pmu->num_cntrs);
	pmu_save_counters(cci_pmu, saved_mask);

	/*
	 * Now that all the counters are disabled, we can safely turn the PMU on,
	 * without syncing the status of the counters
	 */
	__cci_pmu_enable_nosync(cci_pmu);

	क्रम_each_set_bit(i, mask, cci_pmu->num_cntrs) अणु
		काष्ठा perf_event *event = cci_pmu->hw_events.events[i];

		अगर (WARN_ON(!event))
			जारी;

		pmu_set_event(cci_pmu, i, CCI5xx_INVALID_EVENT);
		pmu_enable_counter(cci_pmu, i);
		pmu_ग_लिखो_counter(cci_pmu, local64_पढ़ो(&event->hw.prev_count), i);
		pmu_disable_counter(cci_pmu, i);
		pmu_set_event(cci_pmu, i, event->hw.config_base);
	पूर्ण

	__cci_pmu_disable(cci_pmu);

	pmu_restore_counters(cci_pmu, saved_mask);
पूर्ण

#पूर्ण_अगर	/* CONFIG_ARM_CCI5xx_PMU */

अटल u64 pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

	करो अणु
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
		new_raw_count = pmu_पढ़ो_counter(event);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
		 new_raw_count) != prev_raw_count);

	delta = (new_raw_count - prev_raw_count) & CCI_PMU_CNTR_MASK;

	local64_add(delta, &event->count);

	वापस new_raw_count;
पूर्ण

अटल व्योम pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	pmu_event_update(event);
पूर्ण

अटल व्योम pmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	/*
	 * The CCI PMU counters have a period of 2^32. To account क्रम the
	 * possiblity of extreme पूर्णांकerrupt latency we program क्रम a period of
	 * half that. Hopefully we can handle the पूर्णांकerrupt beक्रमe another 2^31
	 * events occur and the counter overtakes its previous value.
	 */
	u64 val = 1ULL << 31;
	local64_set(&hwc->prev_count, val);

	/*
	 * CCI PMU uses PERF_HES_ARCH to keep track of the counters, whose
	 * values needs to be sync-ed with the s/w state beक्रमe the PMU is
	 * enabled.
	 * Mark this counter क्रम sync.
	 */
	hwc->state |= PERF_HES_ARCH;
पूर्ण

अटल irqवापस_t pmu_handle_irq(पूर्णांक irq_num, व्योम *dev)
अणु
	काष्ठा cci_pmu *cci_pmu = dev;
	काष्ठा cci_pmu_hw_events *events = &cci_pmu->hw_events;
	पूर्णांक idx, handled = IRQ_NONE;

	raw_spin_lock(&events->pmu_lock);

	/* Disable the PMU जबतक we walk through the counters */
	__cci_pmu_disable(cci_pmu);
	/*
	 * Iterate over counters and update the corresponding perf events.
	 * This should work regardless of whether we have per-counter overflow
	 * पूर्णांकerrupt or a combined overflow पूर्णांकerrupt.
	 */
	क्रम (idx = 0; idx <= CCI_PMU_CNTR_LAST(cci_pmu); idx++) अणु
		काष्ठा perf_event *event = events->events[idx];

		अगर (!event)
			जारी;

		/* Did this counter overflow? */
		अगर (!(pmu_पढ़ो_रेजिस्टर(cci_pmu, idx, CCI_PMU_OVRFLW) &
		      CCI_PMU_OVRFLW_FLAG))
			जारी;

		pmu_ग_लिखो_रेजिस्टर(cci_pmu, CCI_PMU_OVRFLW_FLAG, idx,
							CCI_PMU_OVRFLW);

		pmu_event_update(event);
		pmu_event_set_period(event);
		handled = IRQ_HANDLED;
	पूर्ण

	/* Enable the PMU and sync possibly overflowed counters */
	__cci_pmu_enable_sync(cci_pmu);
	raw_spin_unlock(&events->pmu_lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक cci_pmu_get_hw(काष्ठा cci_pmu *cci_pmu)
अणु
	पूर्णांक ret = pmu_request_irq(cci_pmu, pmu_handle_irq);
	अगर (ret) अणु
		pmu_मुक्त_irq(cci_pmu);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cci_pmu_put_hw(काष्ठा cci_pmu *cci_pmu)
अणु
	pmu_मुक्त_irq(cci_pmu);
पूर्ण

अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	atomic_t *active_events = &cci_pmu->active_events;
	काष्ठा mutex *reserve_mutex = &cci_pmu->reserve_mutex;

	अगर (atomic_dec_and_mutex_lock(active_events, reserve_mutex)) अणु
		cci_pmu_put_hw(cci_pmu);
		mutex_unlock(reserve_mutex);
	पूर्ण
पूर्ण

अटल व्योम cci_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(pmu);
	काष्ठा cci_pmu_hw_events *hw_events = &cci_pmu->hw_events;
	पूर्णांक enabled = biपंचांगap_weight(hw_events->used_mask, cci_pmu->num_cntrs);
	अचिन्हित दीर्घ flags;

	अगर (!enabled)
		वापस;

	raw_spin_lock_irqsave(&hw_events->pmu_lock, flags);
	__cci_pmu_enable_sync(cci_pmu);
	raw_spin_unlock_irqrestore(&hw_events->pmu_lock, flags);

पूर्ण

अटल व्योम cci_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(pmu);
	काष्ठा cci_pmu_hw_events *hw_events = &cci_pmu->hw_events;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&hw_events->pmu_lock, flags);
	__cci_pmu_disable(cci_pmu);
	raw_spin_unlock_irqrestore(&hw_events->pmu_lock, flags);
पूर्ण

/*
 * Check अगर the idx represents a non-programmable counter.
 * All the fixed event counters are mapped beक्रमe the programmable
 * counters.
 */
अटल bool pmu_fixed_hw_idx(काष्ठा cci_pmu *cci_pmu, पूर्णांक idx)
अणु
	वापस (idx >= 0) && (idx < cci_pmu->model->fixed_hw_cntrs);
पूर्ण

अटल व्योम cci_pmu_start(काष्ठा perf_event *event, पूर्णांक pmu_flags)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	काष्ठा cci_pmu_hw_events *hw_events = &cci_pmu->hw_events;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	अचिन्हित दीर्घ flags;

	/*
	 * To handle पूर्णांकerrupt latency, we always reprogram the period
	 * regardlesss of PERF_EF_RELOAD.
	 */
	अगर (pmu_flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	अगर (unlikely(!pmu_is_valid_counter(cci_pmu, idx))) अणु
		dev_err(&cci_pmu->plat_device->dev, "Invalid CCI PMU counter %d\n", idx);
		वापस;
	पूर्ण

	raw_spin_lock_irqsave(&hw_events->pmu_lock, flags);

	/* Configure the counter unless you are counting a fixed event */
	अगर (!pmu_fixed_hw_idx(cci_pmu, idx))
		pmu_set_event(cci_pmu, idx, hwc->config_base);

	pmu_event_set_period(event);
	pmu_enable_counter(cci_pmu, idx);

	raw_spin_unlock_irqrestore(&hw_events->pmu_lock, flags);
पूर्ण

अटल व्योम cci_pmu_stop(काष्ठा perf_event *event, पूर्णांक pmu_flags)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (hwc->state & PERF_HES_STOPPED)
		वापस;

	अगर (unlikely(!pmu_is_valid_counter(cci_pmu, idx))) अणु
		dev_err(&cci_pmu->plat_device->dev, "Invalid CCI PMU counter %d\n", idx);
		वापस;
	पूर्ण

	/*
	 * We always reprogram the counter, so ignore PERF_EF_UPDATE. See
	 * cci_pmu_start()
	 */
	pmu_disable_counter(cci_pmu, idx);
	pmu_event_update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक cci_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	काष्ठा cci_pmu_hw_events *hw_events = &cci_pmu->hw_events;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;

	/* If we करोn't have a space क्रम the counter then finish early. */
	idx = pmu_get_event_idx(hw_events, event);
	अगर (idx < 0)
		वापस idx;

	event->hw.idx = idx;
	hw_events->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	अगर (flags & PERF_EF_START)
		cci_pmu_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम cci_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	काष्ठा cci_pmu_hw_events *hw_events = &cci_pmu->hw_events;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	cci_pmu_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = शून्य;
	clear_bit(idx, hw_events->used_mask);

	perf_event_update_userpage(event);
पूर्ण

अटल पूर्णांक validate_event(काष्ठा pmu *cci_pmu,
			  काष्ठा cci_pmu_hw_events *hw_events,
			  काष्ठा perf_event *event)
अणु
	अगर (is_software_event(event))
		वापस 1;

	/*
	 * Reject groups spanning multiple HW PMUs (e.g. CPU + CCI). The
	 * core perf code won't check that the pmu->ctx == leader->ctx
	 * until after pmu->event_init(event).
	 */
	अगर (event->pmu != cci_pmu)
		वापस 0;

	अगर (event->state < PERF_EVENT_STATE_OFF)
		वापस 1;

	अगर (event->state == PERF_EVENT_STATE_OFF && !event->attr.enable_on_exec)
		वापस 1;

	वापस pmu_get_event_idx(hw_events, event) >= 0;
पूर्ण

अटल पूर्णांक validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	अचिन्हित दीर्घ mask[BITS_TO_LONGS(HW_CNTRS_MAX)];
	काष्ठा cci_pmu_hw_events fake_pmu = अणु
		/*
		 * Initialise the fake PMU. We only need to populate the
		 * used_mask क्रम the purposes of validation.
		 */
		.used_mask = mask,
	पूर्ण;
	स_रखो(mask, 0, BITS_TO_LONGS(cci_pmu->num_cntrs) * माप(अचिन्हित दीर्घ));

	अगर (!validate_event(event->pmu, &fake_pmu, leader))
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!validate_event(event->pmu, &fake_pmu, sibling))
			वापस -EINVAL;
	पूर्ण

	अगर (!validate_event(event->pmu, &fake_pmu, event))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक mapping;

	mapping = pmu_map_event(event);

	अगर (mapping < 0) अणु
		pr_debug("event %x:%llx not supported\n", event->attr.type,
			 event->attr.config);
		वापस mapping;
	पूर्ण

	/*
	 * We करोn't assign an index until we actually place the event onto
	 * hardware. Use -1 to signअगरy that we haven't decided where to put it
	 * yet.
	 */
	hwc->idx		= -1;
	hwc->config_base	= 0;
	hwc->config		= 0;
	hwc->event_base		= 0;

	/*
	 * Store the event encoding पूर्णांकo the config_base field.
	 */
	hwc->config_base	    |= (अचिन्हित दीर्घ)mapping;

	अगर (event->group_leader != event) अणु
		अगर (validate_group(event) != 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cci_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(event->pmu);
	atomic_t *active_events = &cci_pmu->active_events;
	पूर्णांक err = 0;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* Shared by all CPUs, no meaningful state to sample */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EOPNOTSUPP;

	/*
	 * Following the example set by other "uncore" PMUs, we accept any CPU
	 * and reग_लिखो its affinity dynamically rather than having perf core
	 * handle cpu == -1 and pid == -1 क्रम this हाल.
	 *
	 * The perf core will pin online CPUs क्रम the duration of this call and
	 * the event being installed पूर्णांकo its context, so the PMU's CPU can't
	 * change under our feet.
	 */
	अगर (event->cpu < 0)
		वापस -EINVAL;
	event->cpu = cci_pmu->cpu;

	event->destroy = hw_perf_event_destroy;
	अगर (!atomic_inc_not_zero(active_events)) अणु
		mutex_lock(&cci_pmu->reserve_mutex);
		अगर (atomic_पढ़ो(active_events) == 0)
			err = cci_pmu_get_hw(cci_pmu);
		अगर (!err)
			atomic_inc(active_events);
		mutex_unlock(&cci_pmu->reserve_mutex);
	पूर्ण
	अगर (err)
		वापस err;

	err = __hw_perf_event_init(event);
	अगर (err)
		hw_perf_event_destroy(event);

	वापस err;
पूर्ण

अटल sमाप_प्रकार pmu_cpumask_attr_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा cci_pmu *cci_pmu = to_cci_pmu(pmu);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(cci_pmu->cpu));
पूर्ण

अटल काष्ठा device_attribute pmu_cpumask_attr =
	__ATTR(cpumask, S_IRUGO, pmu_cpumask_attr_show, शून्य);

अटल काष्ठा attribute *pmu_attrs[] = अणु
	&pmu_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pmu_attr_group = अणु
	.attrs = pmu_attrs,
पूर्ण;

अटल काष्ठा attribute_group pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = शून्य,		/* Filled in cci_pmu_init_attrs */
पूर्ण;

अटल काष्ठा attribute_group pmu_event_attr_group = अणु
	.name = "events",
	.attrs = शून्य,		/* Filled in cci_pmu_init_attrs */
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pmu_attr_groups[] = अणु
	&pmu_attr_group,
	&pmu_क्रमmat_attr_group,
	&pmu_event_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक cci_pmu_init(काष्ठा cci_pmu *cci_pmu, काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा cci_pmu_model *model = cci_pmu->model;
	अक्षर *name = model->name;
	u32 num_cntrs;

	अगर (WARN_ON(model->num_hw_cntrs > NUM_HW_CNTRS_MAX))
		वापस -EINVAL;
	अगर (WARN_ON(model->fixed_hw_cntrs > FIXED_HW_CNTRS_MAX))
		वापस -EINVAL;

	pmu_event_attr_group.attrs = model->event_attrs;
	pmu_क्रमmat_attr_group.attrs = model->क्रमmat_attrs;

	cci_pmu->pmu = (काष्ठा pmu) अणु
		.module		= THIS_MODULE,
		.name		= cci_pmu->model->name,
		.task_ctx_nr	= perf_invalid_context,
		.pmu_enable	= cci_pmu_enable,
		.pmu_disable	= cci_pmu_disable,
		.event_init	= cci_pmu_event_init,
		.add		= cci_pmu_add,
		.del		= cci_pmu_del,
		.start		= cci_pmu_start,
		.stop		= cci_pmu_stop,
		.पढ़ो		= pmu_पढ़ो,
		.attr_groups	= pmu_attr_groups,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	cci_pmu->plat_device = pdev;
	num_cntrs = pmu_get_max_counters(cci_pmu);
	अगर (num_cntrs > cci_pmu->model->num_hw_cntrs) अणु
		dev_warn(&pdev->dev,
			"PMU implements more counters(%d) than supported by"
			" the model(%d), truncated.",
			num_cntrs, cci_pmu->model->num_hw_cntrs);
		num_cntrs = cci_pmu->model->num_hw_cntrs;
	पूर्ण
	cci_pmu->num_cntrs = num_cntrs + cci_pmu->model->fixed_hw_cntrs;

	वापस perf_pmu_रेजिस्टर(&cci_pmu->pmu, name, -1);
पूर्ण

अटल पूर्णांक cci_pmu_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक target;

	अगर (!g_cci_pmu || cpu != g_cci_pmu->cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&g_cci_pmu->pmu, cpu, target);
	g_cci_pmu->cpu = target;
	वापस 0;
पूर्ण

अटल __maybe_unused काष्ठा cci_pmu_model cci_pmu_models[] = अणु
#अगर_घोषित CONFIG_ARM_CCI400_PMU
	[CCI400_R0] = अणु
		.name = "CCI_400",
		.fixed_hw_cntrs = FIXED_HW_CNTRS_CII_4XX, /* Cycle counter */
		.num_hw_cntrs = NUM_HW_CNTRS_CII_4XX,
		.cntr_size = SZ_4K,
		.क्रमmat_attrs = cci400_pmu_क्रमmat_attrs,
		.event_attrs = cci400_r0_pmu_event_attrs,
		.event_ranges = अणु
			[CCI_IF_SLAVE] = अणु
				CCI400_R0_SLAVE_PORT_MIN_EV,
				CCI400_R0_SLAVE_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_MASTER] = अणु
				CCI400_R0_MASTER_PORT_MIN_EV,
				CCI400_R0_MASTER_PORT_MAX_EV,
			पूर्ण,
		पूर्ण,
		.validate_hw_event = cci400_validate_hw_event,
		.get_event_idx = cci400_get_event_idx,
	पूर्ण,
	[CCI400_R1] = अणु
		.name = "CCI_400_r1",
		.fixed_hw_cntrs = FIXED_HW_CNTRS_CII_4XX, /* Cycle counter */
		.num_hw_cntrs = NUM_HW_CNTRS_CII_4XX,
		.cntr_size = SZ_4K,
		.क्रमmat_attrs = cci400_pmu_क्रमmat_attrs,
		.event_attrs = cci400_r1_pmu_event_attrs,
		.event_ranges = अणु
			[CCI_IF_SLAVE] = अणु
				CCI400_R1_SLAVE_PORT_MIN_EV,
				CCI400_R1_SLAVE_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_MASTER] = अणु
				CCI400_R1_MASTER_PORT_MIN_EV,
				CCI400_R1_MASTER_PORT_MAX_EV,
			पूर्ण,
		पूर्ण,
		.validate_hw_event = cci400_validate_hw_event,
		.get_event_idx = cci400_get_event_idx,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_CCI5xx_PMU
	[CCI500_R0] = अणु
		.name = "CCI_500",
		.fixed_hw_cntrs = FIXED_HW_CNTRS_CII_5XX,
		.num_hw_cntrs = NUM_HW_CNTRS_CII_5XX,
		.cntr_size = SZ_64K,
		.क्रमmat_attrs = cci5xx_pmu_क्रमmat_attrs,
		.event_attrs = cci5xx_pmu_event_attrs,
		.event_ranges = अणु
			[CCI_IF_SLAVE] = अणु
				CCI5xx_SLAVE_PORT_MIN_EV,
				CCI5xx_SLAVE_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_MASTER] = अणु
				CCI5xx_MASTER_PORT_MIN_EV,
				CCI5xx_MASTER_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_GLOBAL] = अणु
				CCI5xx_GLOBAL_PORT_MIN_EV,
				CCI5xx_GLOBAL_PORT_MAX_EV,
			पूर्ण,
		पूर्ण,
		.validate_hw_event = cci500_validate_hw_event,
		.ग_लिखो_counters	= cci5xx_pmu_ग_लिखो_counters,
	पूर्ण,
	[CCI550_R0] = अणु
		.name = "CCI_550",
		.fixed_hw_cntrs = FIXED_HW_CNTRS_CII_5XX,
		.num_hw_cntrs = NUM_HW_CNTRS_CII_5XX,
		.cntr_size = SZ_64K,
		.क्रमmat_attrs = cci5xx_pmu_क्रमmat_attrs,
		.event_attrs = cci5xx_pmu_event_attrs,
		.event_ranges = अणु
			[CCI_IF_SLAVE] = अणु
				CCI5xx_SLAVE_PORT_MIN_EV,
				CCI5xx_SLAVE_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_MASTER] = अणु
				CCI5xx_MASTER_PORT_MIN_EV,
				CCI5xx_MASTER_PORT_MAX_EV,
			पूर्ण,
			[CCI_IF_GLOBAL] = अणु
				CCI5xx_GLOBAL_PORT_MIN_EV,
				CCI5xx_GLOBAL_PORT_MAX_EV,
			पूर्ण,
		पूर्ण,
		.validate_hw_event = cci550_validate_hw_event,
		.ग_लिखो_counters	= cci5xx_pmu_ग_लिखो_counters,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा of_device_id arm_cci_pmu_matches[] = अणु
#अगर_घोषित CONFIG_ARM_CCI400_PMU
	अणु
		.compatible = "arm,cci-400-pmu",
		.data	= शून्य,
	पूर्ण,
	अणु
		.compatible = "arm,cci-400-pmu,r0",
		.data	= &cci_pmu_models[CCI400_R0],
	पूर्ण,
	अणु
		.compatible = "arm,cci-400-pmu,r1",
		.data	= &cci_pmu_models[CCI400_R1],
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_CCI5xx_PMU
	अणु
		.compatible = "arm,cci-500-pmu,r0",
		.data = &cci_pmu_models[CCI500_R0],
	पूर्ण,
	अणु
		.compatible = "arm,cci-550-pmu,r0",
		.data = &cci_pmu_models[CCI550_R0],
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_cci_pmu_matches);

अटल bool is_duplicate_irq(पूर्णांक irq, पूर्णांक *irqs, पूर्णांक nr_irqs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_irqs; i++)
		अगर (irq == irqs[i])
			वापस true;

	वापस false;
पूर्ण

अटल काष्ठा cci_pmu *cci_pmu_alloc(काष्ठा device *dev)
अणु
	काष्ठा cci_pmu *cci_pmu;
	स्थिर काष्ठा cci_pmu_model *model;

	/*
	 * All allocations are devm_* hence we करोn't have to मुक्त
	 * them explicitly on an error, as it would end up in driver
	 * detach.
	 */
	cci_pmu = devm_kzalloc(dev, माप(*cci_pmu), GFP_KERNEL);
	अगर (!cci_pmu)
		वापस ERR_PTR(-ENOMEM);

	cci_pmu->ctrl_base = *(व्योम __iomem **)dev->platक्रमm_data;

	model = of_device_get_match_data(dev);
	अगर (!model) अणु
		dev_warn(dev,
			 "DEPRECATED compatible property, requires secure access to CCI registers");
		model = probe_cci_model(cci_pmu);
	पूर्ण
	अगर (!model) अणु
		dev_warn(dev, "CCI PMU version not supported\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	cci_pmu->model = model;
	cci_pmu->irqs = devm_kसुस्मृति(dev, CCI_PMU_MAX_HW_CNTRS(model),
					माप(*cci_pmu->irqs), GFP_KERNEL);
	अगर (!cci_pmu->irqs)
		वापस ERR_PTR(-ENOMEM);
	cci_pmu->hw_events.events = devm_kसुस्मृति(dev,
					     CCI_PMU_MAX_HW_CNTRS(model),
					     माप(*cci_pmu->hw_events.events),
					     GFP_KERNEL);
	अगर (!cci_pmu->hw_events.events)
		वापस ERR_PTR(-ENOMEM);
	cci_pmu->hw_events.used_mask = devm_kसुस्मृति(dev,
						BITS_TO_LONGS(CCI_PMU_MAX_HW_CNTRS(model)),
						माप(*cci_pmu->hw_events.used_mask),
						GFP_KERNEL);
	अगर (!cci_pmu->hw_events.used_mask)
		वापस ERR_PTR(-ENOMEM);

	वापस cci_pmu;
पूर्ण

अटल पूर्णांक cci_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cci_pmu *cci_pmu;
	पूर्णांक i, ret, irq;

	cci_pmu = cci_pmu_alloc(&pdev->dev);
	अगर (IS_ERR(cci_pmu))
		वापस PTR_ERR(cci_pmu);

	cci_pmu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cci_pmu->base))
		वापस -ENOMEM;

	/*
	 * CCI PMU has one overflow पूर्णांकerrupt per counter; but some may be tied
	 * together to a common पूर्णांकerrupt.
	 */
	cci_pmu->nr_irqs = 0;
	क्रम (i = 0; i < CCI_PMU_MAX_HW_CNTRS(cci_pmu->model); i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0)
			अवरोध;

		अगर (is_duplicate_irq(irq, cci_pmu->irqs, cci_pmu->nr_irqs))
			जारी;

		cci_pmu->irqs[cci_pmu->nr_irqs++] = irq;
	पूर्ण

	/*
	 * Ensure that the device tree has as many पूर्णांकerrupts as the number
	 * of counters.
	 */
	अगर (i < CCI_PMU_MAX_HW_CNTRS(cci_pmu->model)) अणु
		dev_warn(&pdev->dev, "In-correct number of interrupts: %d, should be %d\n",
			i, CCI_PMU_MAX_HW_CNTRS(cci_pmu->model));
		वापस -EINVAL;
	पूर्ण

	raw_spin_lock_init(&cci_pmu->hw_events.pmu_lock);
	mutex_init(&cci_pmu->reserve_mutex);
	atomic_set(&cci_pmu->active_events, 0);

	cci_pmu->cpu = raw_smp_processor_id();
	g_cci_pmu = cci_pmu;
	cpuhp_setup_state_nocalls(CPUHP_AP_PERF_ARM_CCI_ONLINE,
				  "perf/arm/cci:online", शून्य,
				  cci_pmu_offline_cpu);

	ret = cci_pmu_init(cci_pmu, pdev);
	अगर (ret)
		जाओ error_pmu_init;

	pr_info("ARM %s PMU driver probed", cci_pmu->model->name);
	वापस 0;

error_pmu_init:
	cpuhp_हटाओ_state(CPUHP_AP_PERF_ARM_CCI_ONLINE);
	g_cci_pmu = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक cci_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!g_cci_pmu)
		वापस 0;

	cpuhp_हटाओ_state(CPUHP_AP_PERF_ARM_CCI_ONLINE);
	perf_pmu_unरेजिस्टर(&g_cci_pmu->pmu);
	g_cci_pmu = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cci_pmu_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = arm_cci_pmu_matches,
		   .suppress_bind_attrs = true,
		  पूर्ण,
	.probe = cci_pmu_probe,
	.हटाओ = cci_pmu_हटाओ,
पूर्ण;

module_platक्रमm_driver(cci_pmu_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ARM CCI PMU support");
