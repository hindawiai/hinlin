<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __ASM_POWERPC_IMC_PMU_H
#घोषणा __ASM_POWERPC_IMC_PMU_H

/*
 * IMC Nest Perक्रमmance Monitor counter support.
 *
 * Copyright (C) 2017 Madhavan Srinivasan, IBM Corporation.
 *           (C) 2017 Anju T Sudhakar, IBM Corporation.
 *           (C) 2017 Hemant K Shaw, IBM Corporation.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/opal.h>

/*
 * Compatibility macros क्रम IMC devices
 */
#घोषणा IMC_DTB_COMPAT			"ibm,opal-in-memory-counters"
#घोषणा IMC_DTB_UNIT_COMPAT		"ibm,imc-counters"


/*
 * LDBAR: Counter address and Enable/Disable macro.
 * perf/imc-pmu.c has the LDBAR layout inक्रमmation.
 */
#घोषणा THREAD_IMC_LDBAR_MASK           0x0003ffffffffe000ULL
#घोषणा THREAD_IMC_ENABLE               0x8000000000000000ULL
#घोषणा TRACE_IMC_ENABLE		0x4000000000000000ULL

/*
 * For debugfs पूर्णांकerface क्रम imc-mode and imc-command
 */
#घोषणा IMC_CNTL_BLK_OFFSET		0x3FC00
#घोषणा IMC_CNTL_BLK_CMD_OFFSET		8
#घोषणा IMC_CNTL_BLK_MODE_OFFSET	32

/*
 * Structure to hold memory address inक्रमmation क्रम imc units.
 */
काष्ठा imc_mem_info अणु
	u64 *vbase;
	u32 id;
पूर्ण;

/*
 * Place holder क्रम nest pmu events and values.
 */
काष्ठा imc_events अणु
	u32 value;
	अक्षर *name;
	अक्षर *unit;
	अक्षर *scale;
पूर्ण;

/*
 * Trace IMC hardware updates a 64bytes record on
 * Core Perक्रमmance Monitoring Counter (CPMC)
 * overflow. Here is the layout क्रम the trace imc record
 *
 * DW 0 : Timebase
 * DW 1 : Program Counter
 * DW 2 : PIDR inक्रमmation
 * DW 3 : CPMC1
 * DW 4 : CPMC2
 * DW 5 : CPMC3
 * Dw 6 : CPMC4
 * DW 7 : Timebase
 * .....
 *
 * The following is the data काष्ठाure to hold trace imc data.
 */
काष्ठा trace_imc_data अणु
	u64 tb1;
	u64 ip;
	u64 val;
	u64 cpmc1;
	u64 cpmc2;
	u64 cpmc3;
	u64 cpmc4;
	u64 tb2;
पूर्ण;

/* Event attribute array index */
#घोषणा IMC_FORMAT_ATTR		0
#घोषणा IMC_EVENT_ATTR		1
#घोषणा IMC_CPUMASK_ATTR	2
#घोषणा IMC_शून्य_ATTR		3

/* PMU Format attribute macros */
#घोषणा IMC_EVENT_OFFSET_MASK	0xffffffffULL

/*
 * Macro to mask bits 0:21 of first द्विगुन word(which is the समयbase) to
 * compare with 8th द्विगुन word (समयbase) of trace imc record data.
 */
#घोषणा IMC_TRACE_RECORD_TB1_MASK      0x3ffffffffffULL

/*
 * Bit 0:1 in third DW of IMC trace record
 * specअगरies the MSR[HV PR] values.
 */
#घोषणा IMC_TRACE_RECORD_VAL_HVPR(x)	((x) >> 62)

/*
 * Device tree parser code detects IMC pmu support and
 * रेजिस्टरs new IMC pmus. This काष्ठाure will hold the
 * pmu functions, events, counter memory inक्रमmation
 * and attrs क्रम each imc pmu and will be referenced at
 * the समय of pmu registration.
 */
काष्ठा imc_pmu अणु
	काष्ठा pmu pmu;
	काष्ठा imc_mem_info *mem_info;
	काष्ठा imc_events *events;
	/*
	 * Attribute groups क्रम the PMU. Slot 0 used क्रम
	 * क्रमmat attribute, slot 1 used क्रम cpusmask attribute,
	 * slot 2 used क्रम event attribute. Slot 3 keep as
	 * शून्य.
	 */
	स्थिर काष्ठा attribute_group *attr_groups[4];
	u32 counter_mem_size;
	पूर्णांक करोमुख्य;
	/*
	 * flag to notअगरy whether the memory is mmaped
	 * or allocated by kernel.
	 */
	bool imc_counter_mmaped;
पूर्ण;

/*
 * Structure to hold id, lock and reference count क्रम the imc events which
 * are inited.
 */
काष्ठा imc_pmu_ref अणु
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक id;
	पूर्णांक refc;
पूर्ण;

/*
 * In-Memory Collection Counters type.
 * Data comes from Device tree.
 * Three device type are supported.
 */

क्रमागत अणु
	IMC_TYPE_THREAD		= 0x1,
	IMC_TYPE_TRACE		= 0x2,
	IMC_TYPE_CORE		= 0x4,
	IMC_TYPE_CHIP           = 0x10,
पूर्ण;

/*
 * Doमुख्यs क्रम IMC PMUs
 */
#घोषणा IMC_DOMAIN_NEST		1
#घोषणा IMC_DOMAIN_CORE		2
#घोषणा IMC_DOMAIN_THREAD	3
/* For trace-imc the करोमुख्य is still thपढ़ो but it operates in trace-mode */
#घोषणा IMC_DOMAIN_TRACE	4

बाह्य पूर्णांक init_imc_pmu(काष्ठा device_node *parent,
				काष्ठा imc_pmu *pmu_ptr, पूर्णांक pmu_id);
बाह्य व्योम thपढ़ो_imc_disable(व्योम);
बाह्य पूर्णांक get_max_nest_dev(व्योम);
बाह्य व्योम unरेजिस्टर_thपढ़ो_imc(व्योम);
#पूर्ण_अगर /* __ASM_POWERPC_IMC_PMU_H */
