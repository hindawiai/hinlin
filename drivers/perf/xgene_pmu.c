<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * APM X-Gene SoC PMU (Perक्रमmance Monitor Unit)
 *
 * Copyright (c) 2016, Applied Micro Circuits Corporation
 * Author: Hoan Tran <hotran@apm.com>
 *         Tai Nguyen <ttnguyen@apm.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा CSW_CSWCR                       0x0000
#घोषणा  CSW_CSWCR_DUALMCB_MASK         BIT(0)
#घोषणा  CSW_CSWCR_MCB0_ROUTING(x)	(((x) & 0x0C) >> 2)
#घोषणा  CSW_CSWCR_MCB1_ROUTING(x)	(((x) & 0x30) >> 4)
#घोषणा MCBADDRMR                       0x0000
#घोषणा  MCBADDRMR_DUALMCU_MODE_MASK    BIT(2)

#घोषणा PCPPMU_INTSTATUS_REG	0x000
#घोषणा PCPPMU_INTMASK_REG	0x004
#घोषणा  PCPPMU_INTMASK		0x0000000F
#घोषणा  PCPPMU_INTENMASK	0xFFFFFFFF
#घोषणा  PCPPMU_INTCLRMASK	0xFFFFFFF0
#घोषणा  PCPPMU_INT_MCU		BIT(0)
#घोषणा  PCPPMU_INT_MCB		BIT(1)
#घोषणा  PCPPMU_INT_L3C		BIT(2)
#घोषणा  PCPPMU_INT_IOB		BIT(3)

#घोषणा  PCPPMU_V3_INTMASK	0x00FF33FF
#घोषणा  PCPPMU_V3_INTENMASK	0xFFFFFFFF
#घोषणा  PCPPMU_V3_INTCLRMASK	0xFF00CC00
#घोषणा  PCPPMU_V3_INT_MCU	0x000000FF
#घोषणा  PCPPMU_V3_INT_MCB	0x00000300
#घोषणा  PCPPMU_V3_INT_L3C	0x00FF0000
#घोषणा  PCPPMU_V3_INT_IOB	0x00003000

#घोषणा PMU_MAX_COUNTERS	4
#घोषणा PMU_CNT_MAX_PERIOD	0xFFFFFFFFULL
#घोषणा PMU_V3_CNT_MAX_PERIOD	0xFFFFFFFFFFFFFFFFULL
#घोषणा PMU_OVERFLOW_MASK	0xF
#घोषणा PMU_PMCR_E		BIT(0)
#घोषणा PMU_PMCR_P		BIT(1)

#घोषणा PMU_PMEVCNTR0		0x000
#घोषणा PMU_PMEVCNTR1		0x004
#घोषणा PMU_PMEVCNTR2		0x008
#घोषणा PMU_PMEVCNTR3		0x00C
#घोषणा PMU_PMEVTYPER0		0x400
#घोषणा PMU_PMEVTYPER1		0x404
#घोषणा PMU_PMEVTYPER2		0x408
#घोषणा PMU_PMEVTYPER3		0x40C
#घोषणा PMU_PMAMR0		0xA00
#घोषणा PMU_PMAMR1		0xA04
#घोषणा PMU_PMCNTENSET		0xC00
#घोषणा PMU_PMCNTENCLR		0xC20
#घोषणा PMU_PMINTENSET		0xC40
#घोषणा PMU_PMINTENCLR		0xC60
#घोषणा PMU_PMOVSR		0xC80
#घोषणा PMU_PMCR		0xE04

/* PMU रेजिस्टरs क्रम V3 */
#घोषणा PMU_PMOVSCLR		0xC80
#घोषणा PMU_PMOVSSET		0xCC0

#घोषणा to_pmu_dev(p)     container_of(p, काष्ठा xgene_pmu_dev, pmu)
#घोषणा GET_CNTR(ev)      (ev->hw.idx)
#घोषणा GET_EVENTID(ev)   (ev->hw.config & 0xFFULL)
#घोषणा GET_AGENTID(ev)   (ev->hw.config_base & 0xFFFFFFFFUL)
#घोषणा GET_AGENT1ID(ev)  ((ev->hw.config_base >> 32) & 0xFFFFFFFFUL)

काष्ठा hw_pmu_info अणु
	u32 type;
	u32 enable_mask;
	व्योम __iomem *csr;
पूर्ण;

काष्ठा xgene_pmu_dev अणु
	काष्ठा hw_pmu_info *inf;
	काष्ठा xgene_pmu *parent;
	काष्ठा pmu pmu;
	u8 max_counters;
	DECLARE_BITMAP(cntr_assign_mask, PMU_MAX_COUNTERS);
	u64 max_period;
	स्थिर काष्ठा attribute_group **attr_groups;
	काष्ठा perf_event *pmu_counter_event[PMU_MAX_COUNTERS];
पूर्ण;

काष्ठा xgene_pmu_ops अणु
	व्योम (*mask_पूर्णांक)(काष्ठा xgene_pmu *pmu);
	व्योम (*unmask_पूर्णांक)(काष्ठा xgene_pmu *pmu);
	u64 (*पढ़ो_counter)(काष्ठा xgene_pmu_dev *pmu, पूर्णांक idx);
	व्योम (*ग_लिखो_counter)(काष्ठा xgene_pmu_dev *pmu, पूर्णांक idx, u64 val);
	व्योम (*ग_लिखो_evttype)(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx, u32 val);
	व्योम (*ग_लिखो_agenपंचांगsk)(काष्ठा xgene_pmu_dev *pmu_dev, u32 val);
	व्योम (*ग_लिखो_agent1msk)(काष्ठा xgene_pmu_dev *pmu_dev, u32 val);
	व्योम (*enable_counter)(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx);
	व्योम (*disable_counter)(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx);
	व्योम (*enable_counter_पूर्णांक)(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx);
	व्योम (*disable_counter_पूर्णांक)(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx);
	व्योम (*reset_counters)(काष्ठा xgene_pmu_dev *pmu_dev);
	व्योम (*start_counters)(काष्ठा xgene_pmu_dev *pmu_dev);
	व्योम (*stop_counters)(काष्ठा xgene_pmu_dev *pmu_dev);
पूर्ण;

काष्ठा xgene_pmu अणु
	काष्ठा device *dev;
	काष्ठा hlist_node node;
	पूर्णांक version;
	व्योम __iomem *pcppmu_csr;
	u32 mcb_active_mask;
	u32 mc_active_mask;
	u32 l3c_active_mask;
	cpumask_t cpu;
	पूर्णांक irq;
	raw_spinlock_t lock;
	स्थिर काष्ठा xgene_pmu_ops *ops;
	काष्ठा list_head l3cpmus;
	काष्ठा list_head iobpmus;
	काष्ठा list_head mcbpmus;
	काष्ठा list_head mcpmus;
पूर्ण;

काष्ठा xgene_pmu_dev_ctx अणु
	अक्षर *name;
	काष्ठा list_head next;
	काष्ठा xgene_pmu_dev *pmu_dev;
	काष्ठा hw_pmu_info inf;
पूर्ण;

काष्ठा xgene_pmu_data अणु
	पूर्णांक id;
	u32 data;
पूर्ण;

क्रमागत xgene_pmu_version अणु
	PCP_PMU_V1 = 1,
	PCP_PMU_V2,
	PCP_PMU_V3,
पूर्ण;

क्रमागत xgene_pmu_dev_type अणु
	PMU_TYPE_L3C = 0,
	PMU_TYPE_IOB,
	PMU_TYPE_IOB_SLOW,
	PMU_TYPE_MCB,
	PMU_TYPE_MC,
पूर्ण;

/*
 * sysfs क्रमmat attributes
 */
अटल sमाप_प्रकार xgene_pmu_क्रमmat_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "%s\n", (अक्षर *) eattr->var);
पूर्ण

#घोषणा XGENE_PMU_FORMAT_ATTR(_name, _config)		\
	(&((काष्ठा dev_ext_attribute[]) अणु		\
		अणु .attr = __ATTR(_name, S_IRUGO, xgene_pmu_क्रमmat_show, शून्य), \
		  .var = (व्योम *) _config, पूर्ण		\
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *l3c_pmu_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(l3c_eventid, "config:0-7"),
	XGENE_PMU_FORMAT_ATTR(l3c_agentid, "config1:0-9"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_pmu_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(iob_eventid, "config:0-7"),
	XGENE_PMU_FORMAT_ATTR(iob_agentid, "config1:0-63"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mcb_pmu_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(mcb_eventid, "config:0-5"),
	XGENE_PMU_FORMAT_ATTR(mcb_agentid, "config1:0-9"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mc_pmu_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(mc_eventid, "config:0-28"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = l3c_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = iob_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcb_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = mcb_pmu_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = mc_pmu_क्रमmat_attrs,
पूर्ण;

अटल काष्ठा attribute *l3c_pmu_v3_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(l3c_eventid, "config:0-39"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_pmu_v3_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(iob_eventid, "config:0-47"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_slow_pmu_v3_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(iob_slow_eventid, "config:0-16"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mcb_pmu_v3_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(mcb_eventid, "config:0-35"),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mc_pmu_v3_क्रमmat_attrs[] = अणु
	XGENE_PMU_FORMAT_ATTR(mc_eventid, "config:0-44"),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_v3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = l3c_pmu_v3_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_pmu_v3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = iob_pmu_v3_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_slow_pmu_v3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = iob_slow_pmu_v3_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcb_pmu_v3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = mcb_pmu_v3_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_pmu_v3_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = mc_pmu_v3_क्रमmat_attrs,
पूर्ण;

/*
 * sysfs event attributes
 */
अटल sमाप_प्रकार xgene_pmu_event_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "config=0x%lx\n", (अचिन्हित दीर्घ) eattr->var);
पूर्ण

#घोषणा XGENE_PMU_EVENT_ATTR(_name, _config)		\
	(&((काष्ठा dev_ext_attribute[]) अणु		\
		अणु .attr = __ATTR(_name, S_IRUGO, xgene_pmu_event_show, शून्य), \
		  .var = (व्योम *) _config, पूर्ण		\
	 पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *l3c_pmu_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(cycle-count-भाग-64,		0x01),
	XGENE_PMU_EVENT_ATTR(पढ़ो-hit,				0x02),
	XGENE_PMU_EVENT_ATTR(पढ़ो-miss,				0x03),
	XGENE_PMU_EVENT_ATTR(ग_लिखो-need-replacement,		0x06),
	XGENE_PMU_EVENT_ATTR(ग_लिखो-not-need-replacement,	0x07),
	XGENE_PMU_EVENT_ATTR(tq-full,				0x08),
	XGENE_PMU_EVENT_ATTR(ackq-full,				0x09),
	XGENE_PMU_EVENT_ATTR(wdb-full,				0x0a),
	XGENE_PMU_EVENT_ATTR(bank-fअगरo-full,			0x0b),
	XGENE_PMU_EVENT_ATTR(odb-full,				0x0c),
	XGENE_PMU_EVENT_ATTR(wbq-full,				0x0d),
	XGENE_PMU_EVENT_ATTR(bank-conflict-fअगरo-issue,		0x0e),
	XGENE_PMU_EVENT_ATTR(bank-fअगरo-issue,			0x0f),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_pmu_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(cycle-count-भाग-64,		0x01),
	XGENE_PMU_EVENT_ATTR(axi0-पढ़ो,				0x02),
	XGENE_PMU_EVENT_ATTR(axi0-पढ़ो-partial,			0x03),
	XGENE_PMU_EVENT_ATTR(axi1-पढ़ो,				0x04),
	XGENE_PMU_EVENT_ATTR(axi1-पढ़ो-partial,			0x05),
	XGENE_PMU_EVENT_ATTR(csw-पढ़ो-block,			0x06),
	XGENE_PMU_EVENT_ATTR(csw-पढ़ो-partial,			0x07),
	XGENE_PMU_EVENT_ATTR(axi0-ग_लिखो,			0x10),
	XGENE_PMU_EVENT_ATTR(axi0-ग_लिखो-partial,		0x11),
	XGENE_PMU_EVENT_ATTR(axi1-ग_लिखो,			0x13),
	XGENE_PMU_EVENT_ATTR(axi1-ग_लिखो-partial,		0x14),
	XGENE_PMU_EVENT_ATTR(csw-inbound-dirty,			0x16),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mcb_pmu_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(cycle-count-भाग-64,		0x01),
	XGENE_PMU_EVENT_ATTR(csw-पढ़ो,				0x02),
	XGENE_PMU_EVENT_ATTR(csw-ग_लिखो-request,			0x03),
	XGENE_PMU_EVENT_ATTR(mcb-csw-stall,			0x04),
	XGENE_PMU_EVENT_ATTR(cancel-पढ़ो-gack,			0x05),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mc_pmu_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(cycle-count-भाग-64,		0x01),
	XGENE_PMU_EVENT_ATTR(act-cmd-sent,			0x02),
	XGENE_PMU_EVENT_ATTR(pre-cmd-sent,			0x03),
	XGENE_PMU_EVENT_ATTR(rd-cmd-sent,			0x04),
	XGENE_PMU_EVENT_ATTR(rda-cmd-sent,			0x05),
	XGENE_PMU_EVENT_ATTR(wr-cmd-sent,			0x06),
	XGENE_PMU_EVENT_ATTR(wra-cmd-sent,			0x07),
	XGENE_PMU_EVENT_ATTR(pde-cmd-sent,			0x08),
	XGENE_PMU_EVENT_ATTR(sre-cmd-sent,			0x09),
	XGENE_PMU_EVENT_ATTR(prea-cmd-sent,			0x0a),
	XGENE_PMU_EVENT_ATTR(ref-cmd-sent,			0x0b),
	XGENE_PMU_EVENT_ATTR(rd-rda-cmd-sent,			0x0c),
	XGENE_PMU_EVENT_ATTR(wr-wra-cmd-sent,			0x0d),
	XGENE_PMU_EVENT_ATTR(in-rd-collision,			0x0e),
	XGENE_PMU_EVENT_ATTR(in-wr-collision,			0x0f),
	XGENE_PMU_EVENT_ATTR(collision-queue-not-empty,		0x10),
	XGENE_PMU_EVENT_ATTR(collision-queue-full,		0x11),
	XGENE_PMU_EVENT_ATTR(mcu-request,			0x12),
	XGENE_PMU_EVENT_ATTR(mcu-rd-request,			0x13),
	XGENE_PMU_EVENT_ATTR(mcu-hp-rd-request,			0x14),
	XGENE_PMU_EVENT_ATTR(mcu-wr-request,			0x15),
	XGENE_PMU_EVENT_ATTR(mcu-rd-proceed-all,		0x16),
	XGENE_PMU_EVENT_ATTR(mcu-rd-proceed-cancel,		0x17),
	XGENE_PMU_EVENT_ATTR(mcu-rd-response,			0x18),
	XGENE_PMU_EVENT_ATTR(mcu-rd-proceed-speculative-all,	0x19),
	XGENE_PMU_EVENT_ATTR(mcu-rd-proceed-speculative-cancel,	0x1a),
	XGENE_PMU_EVENT_ATTR(mcu-wr-proceed-all,		0x1b),
	XGENE_PMU_EVENT_ATTR(mcu-wr-proceed-cancel,		0x1c),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = l3c_pmu_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = iob_pmu_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcb_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = mcb_pmu_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_pmu_events_attr_group = अणु
	.name = "events",
	.attrs = mc_pmu_events_attrs,
पूर्ण;

अटल काष्ठा attribute *l3c_pmu_v3_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(पढ़ो-hit,				0x01),
	XGENE_PMU_EVENT_ATTR(पढ़ो-miss,				0x02),
	XGENE_PMU_EVENT_ATTR(index-flush-eviction,		0x03),
	XGENE_PMU_EVENT_ATTR(ग_लिखो-caused-replacement,		0x04),
	XGENE_PMU_EVENT_ATTR(ग_लिखो-not-caused-replacement,	0x05),
	XGENE_PMU_EVENT_ATTR(clean-eviction,			0x06),
	XGENE_PMU_EVENT_ATTR(dirty-eviction,			0x07),
	XGENE_PMU_EVENT_ATTR(पढ़ो,				0x08),
	XGENE_PMU_EVENT_ATTR(ग_लिखो,				0x09),
	XGENE_PMU_EVENT_ATTR(request,				0x0a),
	XGENE_PMU_EVENT_ATTR(tq-bank-conflict-issue-stall,	0x0b),
	XGENE_PMU_EVENT_ATTR(tq-full,				0x0c),
	XGENE_PMU_EVENT_ATTR(ackq-full,				0x0d),
	XGENE_PMU_EVENT_ATTR(wdb-full,				0x0e),
	XGENE_PMU_EVENT_ATTR(odb-full,				0x10),
	XGENE_PMU_EVENT_ATTR(wbq-full,				0x11),
	XGENE_PMU_EVENT_ATTR(input-req-async-fअगरo-stall,	0x12),
	XGENE_PMU_EVENT_ATTR(output-req-async-fअगरo-stall,	0x13),
	XGENE_PMU_EVENT_ATTR(output-data-async-fअगरo-stall,	0x14),
	XGENE_PMU_EVENT_ATTR(total-insertion,			0x15),
	XGENE_PMU_EVENT_ATTR(sip-insertions-r-set,		0x16),
	XGENE_PMU_EVENT_ATTR(sip-insertions-r-clear,		0x17),
	XGENE_PMU_EVENT_ATTR(dip-insertions-r-set,		0x18),
	XGENE_PMU_EVENT_ATTR(dip-insertions-r-clear,		0x19),
	XGENE_PMU_EVENT_ATTR(dip-insertions-क्रमce-r-set,	0x1a),
	XGENE_PMU_EVENT_ATTR(egression,				0x1b),
	XGENE_PMU_EVENT_ATTR(replacement,			0x1c),
	XGENE_PMU_EVENT_ATTR(old-replacement,			0x1d),
	XGENE_PMU_EVENT_ATTR(young-replacement,			0x1e),
	XGENE_PMU_EVENT_ATTR(r-set-replacement,			0x1f),
	XGENE_PMU_EVENT_ATTR(r-clear-replacement,		0x20),
	XGENE_PMU_EVENT_ATTR(old-r-replacement,			0x21),
	XGENE_PMU_EVENT_ATTR(old-nr-replacement,		0x22),
	XGENE_PMU_EVENT_ATTR(young-r-replacement,		0x23),
	XGENE_PMU_EVENT_ATTR(young-nr-replacement,		0x24),
	XGENE_PMU_EVENT_ATTR(bloomfilter-clearing,		0x25),
	XGENE_PMU_EVENT_ATTR(generation-flip,			0x26),
	XGENE_PMU_EVENT_ATTR(vcc-droop-detected,		0x27),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_fast_pmu_v3_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(pa-req-buf-alloc-all,		0x01),
	XGENE_PMU_EVENT_ATTR(pa-req-buf-alloc-rd,		0x02),
	XGENE_PMU_EVENT_ATTR(pa-req-buf-alloc-wr,		0x03),
	XGENE_PMU_EVENT_ATTR(pa-all-cp-req,			0x04),
	XGENE_PMU_EVENT_ATTR(pa-cp-blk-req,			0x05),
	XGENE_PMU_EVENT_ATTR(pa-cp-ptl-req,			0x06),
	XGENE_PMU_EVENT_ATTR(pa-cp-rd-req,			0x07),
	XGENE_PMU_EVENT_ATTR(pa-cp-wr-req,			0x08),
	XGENE_PMU_EVENT_ATTR(ba-all-req,			0x09),
	XGENE_PMU_EVENT_ATTR(ba-rd-req,				0x0a),
	XGENE_PMU_EVENT_ATTR(ba-wr-req,				0x0b),
	XGENE_PMU_EVENT_ATTR(pa-rd-shared-req-issued,		0x10),
	XGENE_PMU_EVENT_ATTR(pa-rd-exclusive-req-issued,	0x11),
	XGENE_PMU_EVENT_ATTR(pa-wr-invalidate-req-issued-stashable, 0x12),
	XGENE_PMU_EVENT_ATTR(pa-wr-invalidate-req-issued-nonstashable, 0x13),
	XGENE_PMU_EVENT_ATTR(pa-wr-back-req-issued-stashable,	0x14),
	XGENE_PMU_EVENT_ATTR(pa-wr-back-req-issued-nonstashable, 0x15),
	XGENE_PMU_EVENT_ATTR(pa-ptl-wr-req,			0x16),
	XGENE_PMU_EVENT_ATTR(pa-ptl-rd-req,			0x17),
	XGENE_PMU_EVENT_ATTR(pa-wr-back-clean-data,		0x18),
	XGENE_PMU_EVENT_ATTR(pa-wr-back-cancelled-on-SS,	0x1b),
	XGENE_PMU_EVENT_ATTR(pa-barrier-occurrence,		0x1c),
	XGENE_PMU_EVENT_ATTR(pa-barrier-cycles,			0x1d),
	XGENE_PMU_EVENT_ATTR(pa-total-cp-snoops,		0x20),
	XGENE_PMU_EVENT_ATTR(pa-rd-shared-snoop,		0x21),
	XGENE_PMU_EVENT_ATTR(pa-rd-shared-snoop-hit,		0x22),
	XGENE_PMU_EVENT_ATTR(pa-rd-exclusive-snoop,		0x23),
	XGENE_PMU_EVENT_ATTR(pa-rd-exclusive-snoop-hit,		0x24),
	XGENE_PMU_EVENT_ATTR(pa-rd-wr-invalid-snoop,		0x25),
	XGENE_PMU_EVENT_ATTR(pa-rd-wr-invalid-snoop-hit,	0x26),
	XGENE_PMU_EVENT_ATTR(pa-req-buffer-full,		0x28),
	XGENE_PMU_EVENT_ATTR(cswlf-outbound-req-fअगरo-full,	0x29),
	XGENE_PMU_EVENT_ATTR(cswlf-inbound-snoop-fअगरo-backpressure, 0x2a),
	XGENE_PMU_EVENT_ATTR(cswlf-outbound-lack-fअगरo-full,	0x2b),
	XGENE_PMU_EVENT_ATTR(cswlf-inbound-gack-fअगरo-backpressure, 0x2c),
	XGENE_PMU_EVENT_ATTR(cswlf-outbound-data-fअगरo-full,	0x2d),
	XGENE_PMU_EVENT_ATTR(cswlf-inbound-data-fअगरo-backpressure, 0x2e),
	XGENE_PMU_EVENT_ATTR(cswlf-inbound-req-backpressure,	0x2f),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *iob_slow_pmu_v3_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(pa-axi0-rd-req,			0x01),
	XGENE_PMU_EVENT_ATTR(pa-axi0-wr-req,			0x02),
	XGENE_PMU_EVENT_ATTR(pa-axi1-rd-req,			0x03),
	XGENE_PMU_EVENT_ATTR(pa-axi1-wr-req,			0x04),
	XGENE_PMU_EVENT_ATTR(ba-all-axi-req,			0x07),
	XGENE_PMU_EVENT_ATTR(ba-axi-rd-req,			0x08),
	XGENE_PMU_EVENT_ATTR(ba-axi-wr-req,			0x09),
	XGENE_PMU_EVENT_ATTR(ba-मुक्त-list-empty,		0x10),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mcb_pmu_v3_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(req-receive,			0x01),
	XGENE_PMU_EVENT_ATTR(rd-req-recv,			0x02),
	XGENE_PMU_EVENT_ATTR(rd-req-recv-2,			0x03),
	XGENE_PMU_EVENT_ATTR(wr-req-recv,			0x04),
	XGENE_PMU_EVENT_ATTR(wr-req-recv-2,			0x05),
	XGENE_PMU_EVENT_ATTR(rd-req-sent-to-mcu,		0x06),
	XGENE_PMU_EVENT_ATTR(rd-req-sent-to-mcu-2,		0x07),
	XGENE_PMU_EVENT_ATTR(rd-req-sent-to-spec-mcu,		0x08),
	XGENE_PMU_EVENT_ATTR(rd-req-sent-to-spec-mcu-2,		0x09),
	XGENE_PMU_EVENT_ATTR(glbl-ack-recv-क्रम-rd-sent-to-spec-mcu, 0x0a),
	XGENE_PMU_EVENT_ATTR(glbl-ack-go-recv-क्रम-rd-sent-to-spec-mcu, 0x0b),
	XGENE_PMU_EVENT_ATTR(glbl-ack-nogo-recv-क्रम-rd-sent-to-spec-mcu, 0x0c),
	XGENE_PMU_EVENT_ATTR(glbl-ack-go-recv-any-rd-req,	0x0d),
	XGENE_PMU_EVENT_ATTR(glbl-ack-go-recv-any-rd-req-2,	0x0e),
	XGENE_PMU_EVENT_ATTR(wr-req-sent-to-mcu,		0x0f),
	XGENE_PMU_EVENT_ATTR(gack-recv,				0x10),
	XGENE_PMU_EVENT_ATTR(rd-gack-recv,			0x11),
	XGENE_PMU_EVENT_ATTR(wr-gack-recv,			0x12),
	XGENE_PMU_EVENT_ATTR(cancel-rd-gack,			0x13),
	XGENE_PMU_EVENT_ATTR(cancel-wr-gack,			0x14),
	XGENE_PMU_EVENT_ATTR(mcb-csw-req-stall,			0x15),
	XGENE_PMU_EVENT_ATTR(mcu-req-पूर्णांकf-blocked,		0x16),
	XGENE_PMU_EVENT_ATTR(mcb-mcu-rd-पूर्णांकf-stall,		0x17),
	XGENE_PMU_EVENT_ATTR(csw-rd-पूर्णांकf-blocked,		0x18),
	XGENE_PMU_EVENT_ATTR(csw-local-ack-पूर्णांकf-blocked,	0x19),
	XGENE_PMU_EVENT_ATTR(mcu-req-table-full,		0x1a),
	XGENE_PMU_EVENT_ATTR(mcu-stat-table-full,		0x1b),
	XGENE_PMU_EVENT_ATTR(mcu-wr-table-full,			0x1c),
	XGENE_PMU_EVENT_ATTR(mcu-rdreceipt-resp,		0x1d),
	XGENE_PMU_EVENT_ATTR(mcu-wrcomplete-resp,		0x1e),
	XGENE_PMU_EVENT_ATTR(mcu-retryack-resp,			0x1f),
	XGENE_PMU_EVENT_ATTR(mcu-pcrdgrant-resp,		0x20),
	XGENE_PMU_EVENT_ATTR(mcu-req-from-lastload,		0x21),
	XGENE_PMU_EVENT_ATTR(mcu-req-from-bypass,		0x22),
	XGENE_PMU_EVENT_ATTR(volt-droop-detect,			0x23),
	शून्य,
पूर्ण;

अटल काष्ठा attribute *mc_pmu_v3_events_attrs[] = अणु
	XGENE_PMU_EVENT_ATTR(cycle-count,			0x00),
	XGENE_PMU_EVENT_ATTR(act-sent,				0x01),
	XGENE_PMU_EVENT_ATTR(pre-sent,				0x02),
	XGENE_PMU_EVENT_ATTR(rd-sent,				0x03),
	XGENE_PMU_EVENT_ATTR(rda-sent,				0x04),
	XGENE_PMU_EVENT_ATTR(wr-sent,				0x05),
	XGENE_PMU_EVENT_ATTR(wra-sent,				0x06),
	XGENE_PMU_EVENT_ATTR(pd-entry-vld,			0x07),
	XGENE_PMU_EVENT_ATTR(sref-entry-vld,			0x08),
	XGENE_PMU_EVENT_ATTR(prea-sent,				0x09),
	XGENE_PMU_EVENT_ATTR(ref-sent,				0x0a),
	XGENE_PMU_EVENT_ATTR(rd-rda-sent,			0x0b),
	XGENE_PMU_EVENT_ATTR(wr-wra-sent,			0x0c),
	XGENE_PMU_EVENT_ATTR(raw-hazard,			0x0d),
	XGENE_PMU_EVENT_ATTR(war-hazard,			0x0e),
	XGENE_PMU_EVENT_ATTR(waw-hazard,			0x0f),
	XGENE_PMU_EVENT_ATTR(rar-hazard,			0x10),
	XGENE_PMU_EVENT_ATTR(raw-war-waw-hazard,		0x11),
	XGENE_PMU_EVENT_ATTR(hprd-lprd-wr-req-vld,		0x12),
	XGENE_PMU_EVENT_ATTR(lprd-req-vld,			0x13),
	XGENE_PMU_EVENT_ATTR(hprd-req-vld,			0x14),
	XGENE_PMU_EVENT_ATTR(hprd-lprd-req-vld,			0x15),
	XGENE_PMU_EVENT_ATTR(wr-req-vld,			0x16),
	XGENE_PMU_EVENT_ATTR(partial-wr-req-vld,		0x17),
	XGENE_PMU_EVENT_ATTR(rd-retry,				0x18),
	XGENE_PMU_EVENT_ATTR(wr-retry,				0x19),
	XGENE_PMU_EVENT_ATTR(retry-gnt,				0x1a),
	XGENE_PMU_EVENT_ATTR(rank-change,			0x1b),
	XGENE_PMU_EVENT_ATTR(dir-change,			0x1c),
	XGENE_PMU_EVENT_ATTR(rank-dir-change,			0x1d),
	XGENE_PMU_EVENT_ATTR(rank-active,			0x1e),
	XGENE_PMU_EVENT_ATTR(rank-idle,				0x1f),
	XGENE_PMU_EVENT_ATTR(rank-pd,				0x20),
	XGENE_PMU_EVENT_ATTR(rank-sref,				0x21),
	XGENE_PMU_EVENT_ATTR(queue-fill-gt-thresh,		0x22),
	XGENE_PMU_EVENT_ATTR(queue-rds-gt-thresh,		0x23),
	XGENE_PMU_EVENT_ATTR(queue-wrs-gt-thresh,		0x24),
	XGENE_PMU_EVENT_ATTR(phy-updt-complt,			0x25),
	XGENE_PMU_EVENT_ATTR(tz-fail,				0x26),
	XGENE_PMU_EVENT_ATTR(dram-errc,				0x27),
	XGENE_PMU_EVENT_ATTR(dram-errd,				0x28),
	XGENE_PMU_EVENT_ATTR(rd-enq,				0x29),
	XGENE_PMU_EVENT_ATTR(wr-enq,				0x2a),
	XGENE_PMU_EVENT_ATTR(पंचांगac-limit-reached,		0x2b),
	XGENE_PMU_EVENT_ATTR(पंचांगaw-tracker-full,			0x2c),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l3c_pmu_v3_events_attr_group = अणु
	.name = "events",
	.attrs = l3c_pmu_v3_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_fast_pmu_v3_events_attr_group = अणु
	.name = "events",
	.attrs = iob_fast_pmu_v3_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iob_slow_pmu_v3_events_attr_group = अणु
	.name = "events",
	.attrs = iob_slow_pmu_v3_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcb_pmu_v3_events_attr_group = अणु
	.name = "events",
	.attrs = mcb_pmu_v3_events_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mc_pmu_v3_events_attr_group = अणु
	.name = "events",
	.attrs = mc_pmu_v3_events_attrs,
पूर्ण;

/*
 * sysfs cpumask attributes
 */
अटल sमाप_प्रकार xgene_pmu_cpumask_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &pmu_dev->parent->cpu);
पूर्ण

अटल DEVICE_ATTR(cpumask, S_IRUGO, xgene_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *xgene_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pmu_cpumask_attr_group = अणु
	.attrs = xgene_pmu_cpumask_attrs,
पूर्ण;

/*
 * Per PMU device attribute groups of PMU v1 and v2
 */
अटल स्थिर काष्ठा attribute_group *l3c_pmu_attr_groups[] = अणु
	&l3c_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&l3c_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iob_pmu_attr_groups[] = अणु
	&iob_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&iob_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mcb_pmu_attr_groups[] = अणु
	&mcb_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&mcb_pmu_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mc_pmu_attr_groups[] = अणु
	&mc_pmu_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&mc_pmu_events_attr_group,
	शून्य
पूर्ण;

/*
 * Per PMU device attribute groups of PMU v3
 */
अटल स्थिर काष्ठा attribute_group *l3c_pmu_v3_attr_groups[] = अणु
	&l3c_pmu_v3_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&l3c_pmu_v3_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iob_fast_pmu_v3_attr_groups[] = अणु
	&iob_pmu_v3_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&iob_fast_pmu_v3_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iob_slow_pmu_v3_attr_groups[] = अणु
	&iob_slow_pmu_v3_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&iob_slow_pmu_v3_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mcb_pmu_v3_attr_groups[] = अणु
	&mcb_pmu_v3_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&mcb_pmu_v3_events_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group *mc_pmu_v3_attr_groups[] = अणु
	&mc_pmu_v3_क्रमmat_attr_group,
	&pmu_cpumask_attr_group,
	&mc_pmu_v3_events_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक get_next_avail_cntr(काष्ठा xgene_pmu_dev *pmu_dev)
अणु
	पूर्णांक cntr;

	cntr = find_first_zero_bit(pmu_dev->cntr_assign_mask,
				pmu_dev->max_counters);
	अगर (cntr == pmu_dev->max_counters)
		वापस -ENOSPC;
	set_bit(cntr, pmu_dev->cntr_assign_mask);

	वापस cntr;
पूर्ण

अटल व्योम clear_avail_cntr(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक cntr)
अणु
	clear_bit(cntr, pmu_dev->cntr_assign_mask);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_mask_पूर्णांक(काष्ठा xgene_pmu *xgene_pmu)
अणु
	ग_लिखोl(PCPPMU_INTENMASK, xgene_pmu->pcppmu_csr + PCPPMU_INTMASK_REG);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_v3_mask_पूर्णांक(काष्ठा xgene_pmu *xgene_pmu)
अणु
	ग_लिखोl(PCPPMU_V3_INTENMASK, xgene_pmu->pcppmu_csr + PCPPMU_INTMASK_REG);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_unmask_पूर्णांक(काष्ठा xgene_pmu *xgene_pmu)
अणु
	ग_लिखोl(PCPPMU_INTCLRMASK, xgene_pmu->pcppmu_csr + PCPPMU_INTMASK_REG);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_v3_unmask_पूर्णांक(काष्ठा xgene_pmu *xgene_pmu)
अणु
	ग_लिखोl(PCPPMU_V3_INTCLRMASK,
	       xgene_pmu->pcppmu_csr + PCPPMU_INTMASK_REG);
पूर्ण

अटल अंतरभूत u64 xgene_pmu_पढ़ो_counter32(काष्ठा xgene_pmu_dev *pmu_dev,
					   पूर्णांक idx)
अणु
	वापस पढ़ोl(pmu_dev->inf->csr + PMU_PMEVCNTR0 + (4 * idx));
पूर्ण

अटल अंतरभूत u64 xgene_pmu_पढ़ो_counter64(काष्ठा xgene_pmu_dev *pmu_dev,
					   पूर्णांक idx)
अणु
	u32 lo, hi;

	/*
	 * v3 has 64-bit counter रेजिस्टरs composed by 2 32-bit रेजिस्टरs
	 * This can be a problem अगर the counter increases and carries
	 * out of bit [31] between 2 पढ़ोs. The extra पढ़ोs would help
	 * to prevent this issue.
	 */
	करो अणु
		hi = xgene_pmu_पढ़ो_counter32(pmu_dev, 2 * idx + 1);
		lo = xgene_pmu_पढ़ो_counter32(pmu_dev, 2 * idx);
	पूर्ण जबतक (hi != xgene_pmu_पढ़ो_counter32(pmu_dev, 2 * idx + 1));

	वापस (((u64)hi << 32) | lo);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_ग_लिखो_counter32(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx, u64 val)
अणु
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMEVCNTR0 + (4 * idx));
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_ग_लिखो_counter64(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx, u64 val)
अणु
	u32 cnt_lo, cnt_hi;

	cnt_hi = upper_32_bits(val);
	cnt_lo = lower_32_bits(val);

	/* v3 has 64-bit counter रेजिस्टरs composed by 2 32-bit रेजिस्टरs */
	xgene_pmu_ग_लिखो_counter32(pmu_dev, 2 * idx, cnt_lo);
	xgene_pmu_ग_लिखो_counter32(pmu_dev, 2 * idx + 1, cnt_hi);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_ग_लिखो_evttype(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx, u32 val)
अणु
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMEVTYPER0 + (4 * idx));
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_ग_लिखो_agenपंचांगsk(काष्ठा xgene_pmu_dev *pmu_dev, u32 val)
अणु
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMAMR0);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_v3_ग_लिखो_agenपंचांगsk(काष्ठा xgene_pmu_dev *pmu_dev, u32 val) अणु पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_ग_लिखो_agent1msk(काष्ठा xgene_pmu_dev *pmu_dev, u32 val)
अणु
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMAMR1);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_v3_ग_लिखो_agent1msk(काष्ठा xgene_pmu_dev *pmu_dev, u32 val) अणु पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_enable_counter(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMCNTENSET);
	val |= 1 << idx;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMCNTENSET);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_disable_counter(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMCNTENCLR);
	val |= 1 << idx;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMCNTENCLR);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_enable_counter_पूर्णांक(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMINTENSET);
	val |= 1 << idx;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMINTENSET);
पूर्ण

अटल अंतरभूत व्योम
xgene_pmu_disable_counter_पूर्णांक(काष्ठा xgene_pmu_dev *pmu_dev, पूर्णांक idx)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMINTENCLR);
	val |= 1 << idx;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMINTENCLR);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_reset_counters(काष्ठा xgene_pmu_dev *pmu_dev)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMCR);
	val |= PMU_PMCR_P;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMCR);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_start_counters(काष्ठा xgene_pmu_dev *pmu_dev)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMCR);
	val |= PMU_PMCR_E;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMCR);
पूर्ण

अटल अंतरभूत व्योम xgene_pmu_stop_counters(काष्ठा xgene_pmu_dev *pmu_dev)
अणु
	u32 val;

	val = पढ़ोl(pmu_dev->inf->csr + PMU_PMCR);
	val &= ~PMU_PMCR_E;
	ग_लिखोl(val, pmu_dev->inf->csr + PMU_PMCR);
पूर्ण

अटल व्योम xgene_perf_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;
	पूर्णांक enabled = biपंचांगap_weight(pmu_dev->cntr_assign_mask,
			pmu_dev->max_counters);

	अगर (!enabled)
		वापस;

	xgene_pmu->ops->start_counters(pmu_dev);
पूर्ण

अटल व्योम xgene_perf_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;

	xgene_pmu->ops->stop_counters(pmu_dev);
पूर्ण

अटल पूर्णांक xgene_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा perf_event *sibling;

	/* Test the event attr type check क्रम PMU क्रमागतeration */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * SOC PMU counters are shared across all cores.
	 * Thereक्रमe, it करोes not support per-process mode.
	 * Also, it करोes not support event sampling mode.
	 */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;
	/*
	 * Many perf core operations (eg. events rotation) operate on a
	 * single CPU context. This is obvious क्रम CPU PMUs, where one
	 * expects the same sets of events being observed on all CPUs,
	 * but can lead to issues क्रम off-core PMUs, where each
	 * event could be theoretically asचिन्हित to a dअगरferent CPU. To
	 * mitigate this, we enक्रमce CPU assignment to one, selected
	 * processor (the one described in the "cpumask" attribute).
	 */
	event->cpu = cpumask_first(&pmu_dev->parent->cpu);

	hw->config = event->attr.config;
	/*
	 * Each bit of the config1 field represents an agent from which the
	 * request of the event come. The event is counted only अगर it's caused
	 * by a request of an agent has the bit cleared.
	 * By शेष, the event is counted क्रम all agents.
	 */
	hw->config_base = event->attr.config1;

	/*
	 * We must NOT create groups containing mixed PMUs, although software
	 * events are acceptable
	 */
	अगर (event->group_leader->pmu != event->pmu &&
			!is_software_event(event->group_leader))
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (sibling->pmu != event->pmu &&
				!is_software_event(sibling))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_perf_enable_event(काष्ठा perf_event *event)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;

	xgene_pmu->ops->ग_लिखो_evttype(pmu_dev, GET_CNTR(event),
				      GET_EVENTID(event));
	xgene_pmu->ops->ग_लिखो_agenपंचांगsk(pmu_dev, ~((u32)GET_AGENTID(event)));
	अगर (pmu_dev->inf->type == PMU_TYPE_IOB)
		xgene_pmu->ops->ग_लिखो_agent1msk(pmu_dev,
						~((u32)GET_AGENT1ID(event)));

	xgene_pmu->ops->enable_counter(pmu_dev, GET_CNTR(event));
	xgene_pmu->ops->enable_counter_पूर्णांक(pmu_dev, GET_CNTR(event));
पूर्ण

अटल व्योम xgene_perf_disable_event(काष्ठा perf_event *event)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;

	xgene_pmu->ops->disable_counter(pmu_dev, GET_CNTR(event));
	xgene_pmu->ops->disable_counter_पूर्णांक(pmu_dev, GET_CNTR(event));
पूर्ण

अटल व्योम xgene_perf_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;
	काष्ठा hw_perf_event *hw = &event->hw;
	/*
	 * For 32 bit counter, it has a period of 2^32. To account क्रम the
	 * possibility of extreme पूर्णांकerrupt latency we program क्रम a period of
	 * half that. Hopefully, we can handle the पूर्णांकerrupt beक्रमe another 2^31
	 * events occur and the counter overtakes its previous value.
	 * For 64 bit counter, we करोn't expect it overflow.
	 */
	u64 val = 1ULL << 31;

	local64_set(&hw->prev_count, val);
	xgene_pmu->ops->ग_लिखो_counter(pmu_dev, hw->idx, val);
पूर्ण

अटल व्योम xgene_perf_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;
	काष्ठा hw_perf_event *hw = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

again:
	prev_raw_count = local64_पढ़ो(&hw->prev_count);
	new_raw_count = xgene_pmu->ops->पढ़ो_counter(pmu_dev, GET_CNTR(event));

	अगर (local64_cmpxchg(&hw->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count)
		जाओ again;

	delta = (new_raw_count - prev_raw_count) & pmu_dev->max_period;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम xgene_perf_पढ़ो(काष्ठा perf_event *event)
अणु
	xgene_perf_event_update(event);
पूर्ण

अटल व्योम xgene_perf_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (WARN_ON_ONCE(!(hw->state & PERF_HES_STOPPED)))
		वापस;

	WARN_ON_ONCE(!(hw->state & PERF_HES_UPTODATE));
	hw->state = 0;

	xgene_perf_event_set_period(event);

	अगर (flags & PERF_EF_RELOAD) अणु
		u64 prev_raw_count =  local64_पढ़ो(&hw->prev_count);

		xgene_pmu->ops->ग_लिखो_counter(pmu_dev, GET_CNTR(event),
					      prev_raw_count);
	पूर्ण

	xgene_perf_enable_event(event);
	perf_event_update_userpage(event);
पूर्ण

अटल व्योम xgene_perf_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (hw->state & PERF_HES_UPTODATE)
		वापस;

	xgene_perf_disable_event(event);
	WARN_ON_ONCE(hw->state & PERF_HES_STOPPED);
	hw->state |= PERF_HES_STOPPED;

	अगर (hw->state & PERF_HES_UPTODATE)
		वापस;

	xgene_perf_पढ़ो(event);
	hw->state |= PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक xgene_perf_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;

	hw->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	/* Allocate an event counter */
	hw->idx = get_next_avail_cntr(pmu_dev);
	अगर (hw->idx < 0)
		वापस -EAGAIN;

	/* Update counter event poपूर्णांकer क्रम Interrupt handler */
	pmu_dev->pmu_counter_event[hw->idx] = event;

	अगर (flags & PERF_EF_START)
		xgene_perf_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

अटल व्योम xgene_perf_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;

	xgene_perf_stop(event, PERF_EF_UPDATE);

	/* clear the asचिन्हित counter */
	clear_avail_cntr(pmu_dev, GET_CNTR(event));

	perf_event_update_userpage(event);
	pmu_dev->pmu_counter_event[hw->idx] = शून्य;
पूर्ण

अटल पूर्णांक xgene_init_perf(काष्ठा xgene_pmu_dev *pmu_dev, अक्षर *name)
अणु
	काष्ठा xgene_pmu *xgene_pmu;

	अगर (pmu_dev->parent->version == PCP_PMU_V3)
		pmu_dev->max_period = PMU_V3_CNT_MAX_PERIOD;
	अन्यथा
		pmu_dev->max_period = PMU_CNT_MAX_PERIOD;
	/* First version PMU supports only single event counter */
	xgene_pmu = pmu_dev->parent;
	अगर (xgene_pmu->version == PCP_PMU_V1)
		pmu_dev->max_counters = 1;
	अन्यथा
		pmu_dev->max_counters = PMU_MAX_COUNTERS;

	/* Perf driver registration */
	pmu_dev->pmu = (काष्ठा pmu) अणु
		.attr_groups	= pmu_dev->attr_groups,
		.task_ctx_nr	= perf_invalid_context,
		.pmu_enable	= xgene_perf_pmu_enable,
		.pmu_disable	= xgene_perf_pmu_disable,
		.event_init	= xgene_perf_event_init,
		.add		= xgene_perf_add,
		.del		= xgene_perf_del,
		.start		= xgene_perf_start,
		.stop		= xgene_perf_stop,
		.पढ़ो		= xgene_perf_पढ़ो,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	/* Hardware counter init */
	xgene_pmu->ops->stop_counters(pmu_dev);
	xgene_pmu->ops->reset_counters(pmu_dev);

	वापस perf_pmu_रेजिस्टर(&pmu_dev->pmu, name, -1);
पूर्ण

अटल पूर्णांक
xgene_pmu_dev_add(काष्ठा xgene_pmu *xgene_pmu, काष्ठा xgene_pmu_dev_ctx *ctx)
अणु
	काष्ठा device *dev = xgene_pmu->dev;
	काष्ठा xgene_pmu_dev *pmu;

	pmu = devm_kzalloc(dev, माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;
	pmu->parent = xgene_pmu;
	pmu->inf = &ctx->inf;
	ctx->pmu_dev = pmu;

	चयन (pmu->inf->type) अणु
	हाल PMU_TYPE_L3C:
		अगर (!(xgene_pmu->l3c_active_mask & pmu->inf->enable_mask))
			वापस -ENODEV;
		अगर (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = l3c_pmu_v3_attr_groups;
		अन्यथा
			pmu->attr_groups = l3c_pmu_attr_groups;
		अवरोध;
	हाल PMU_TYPE_IOB:
		अगर (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = iob_fast_pmu_v3_attr_groups;
		अन्यथा
			pmu->attr_groups = iob_pmu_attr_groups;
		अवरोध;
	हाल PMU_TYPE_IOB_SLOW:
		अगर (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = iob_slow_pmu_v3_attr_groups;
		अवरोध;
	हाल PMU_TYPE_MCB:
		अगर (!(xgene_pmu->mcb_active_mask & pmu->inf->enable_mask))
			वापस -ENODEV;
		अगर (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = mcb_pmu_v3_attr_groups;
		अन्यथा
			pmu->attr_groups = mcb_pmu_attr_groups;
		अवरोध;
	हाल PMU_TYPE_MC:
		अगर (!(xgene_pmu->mc_active_mask & pmu->inf->enable_mask))
			वापस -ENODEV;
		अगर (xgene_pmu->version == PCP_PMU_V3)
			pmu->attr_groups = mc_pmu_v3_attr_groups;
		अन्यथा
			pmu->attr_groups = mc_pmu_attr_groups;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (xgene_init_perf(pmu, ctx->name)) अणु
		dev_err(dev, "%s PMU: Failed to init perf driver\n", ctx->name);
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "%s PMU registered\n", ctx->name);

	वापस 0;
पूर्ण

अटल व्योम _xgene_pmu_isr(पूर्णांक irq, काष्ठा xgene_pmu_dev *pmu_dev)
अणु
	काष्ठा xgene_pmu *xgene_pmu = pmu_dev->parent;
	व्योम __iomem *csr = pmu_dev->inf->csr;
	u32 pmovsr;
	पूर्णांक idx;

	xgene_pmu->ops->stop_counters(pmu_dev);

	अगर (xgene_pmu->version == PCP_PMU_V3)
		pmovsr = पढ़ोl(csr + PMU_PMOVSSET) & PMU_OVERFLOW_MASK;
	अन्यथा
		pmovsr = पढ़ोl(csr + PMU_PMOVSR) & PMU_OVERFLOW_MASK;

	अगर (!pmovsr)
		जाओ out;

	/* Clear पूर्णांकerrupt flag */
	अगर (xgene_pmu->version == PCP_PMU_V1)
		ग_लिखोl(0x0, csr + PMU_PMOVSR);
	अन्यथा अगर (xgene_pmu->version == PCP_PMU_V2)
		ग_लिखोl(pmovsr, csr + PMU_PMOVSR);
	अन्यथा
		ग_लिखोl(pmovsr, csr + PMU_PMOVSCLR);

	क्रम (idx = 0; idx < PMU_MAX_COUNTERS; idx++) अणु
		काष्ठा perf_event *event = pmu_dev->pmu_counter_event[idx];
		पूर्णांक overflowed = pmovsr & BIT(idx);

		/* Ignore अगर we करोn't have an event. */
		अगर (!event || !overflowed)
			जारी;
		xgene_perf_event_update(event);
		xgene_perf_event_set_period(event);
	पूर्ण

out:
	xgene_pmu->ops->start_counters(pmu_dev);
पूर्ण

अटल irqवापस_t xgene_pmu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांकr_mcu, पूर्णांकr_mcb, पूर्णांकr_l3c, पूर्णांकr_iob;
	काष्ठा xgene_pmu_dev_ctx *ctx;
	काष्ठा xgene_pmu *xgene_pmu = dev_id;
	u32 val;

	raw_spin_lock(&xgene_pmu->lock);

	/* Get Interrupt PMU source */
	val = पढ़ोl(xgene_pmu->pcppmu_csr + PCPPMU_INTSTATUS_REG);
	अगर (xgene_pmu->version == PCP_PMU_V3) अणु
		पूर्णांकr_mcu = PCPPMU_V3_INT_MCU;
		पूर्णांकr_mcb = PCPPMU_V3_INT_MCB;
		पूर्णांकr_l3c = PCPPMU_V3_INT_L3C;
		पूर्णांकr_iob = PCPPMU_V3_INT_IOB;
	पूर्ण अन्यथा अणु
		पूर्णांकr_mcu = PCPPMU_INT_MCU;
		पूर्णांकr_mcb = PCPPMU_INT_MCB;
		पूर्णांकr_l3c = PCPPMU_INT_L3C;
		पूर्णांकr_iob = PCPPMU_INT_IOB;
	पूर्ण
	अगर (val & पूर्णांकr_mcu) अणु
		list_क्रम_each_entry(ctx, &xgene_pmu->mcpmus, next) अणु
			_xgene_pmu_isr(irq, ctx->pmu_dev);
		पूर्ण
	पूर्ण
	अगर (val & पूर्णांकr_mcb) अणु
		list_क्रम_each_entry(ctx, &xgene_pmu->mcbpmus, next) अणु
			_xgene_pmu_isr(irq, ctx->pmu_dev);
		पूर्ण
	पूर्ण
	अगर (val & पूर्णांकr_l3c) अणु
		list_क्रम_each_entry(ctx, &xgene_pmu->l3cpmus, next) अणु
			_xgene_pmu_isr(irq, ctx->pmu_dev);
		पूर्ण
	पूर्ण
	अगर (val & पूर्णांकr_iob) अणु
		list_क्रम_each_entry(ctx, &xgene_pmu->iobpmus, next) अणु
			_xgene_pmu_isr(irq, ctx->pmu_dev);
		पूर्ण
	पूर्ण

	raw_spin_unlock(&xgene_pmu->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक acpi_pmu_probe_active_mcb_mcu_l3c(काष्ठा xgene_pmu *xgene_pmu,
					     काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *csw_csr, *mcba_csr, *mcbb_csr;
	अचिन्हित पूर्णांक reg;

	csw_csr = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(csw_csr)) अणु
		dev_err(&pdev->dev, "ioremap failed for CSW CSR resource\n");
		वापस PTR_ERR(csw_csr);
	पूर्ण

	mcba_csr = devm_platक्रमm_ioremap_resource(pdev, 2);
	अगर (IS_ERR(mcba_csr)) अणु
		dev_err(&pdev->dev, "ioremap failed for MCBA CSR resource\n");
		वापस PTR_ERR(mcba_csr);
	पूर्ण

	mcbb_csr = devm_platक्रमm_ioremap_resource(pdev, 3);
	अगर (IS_ERR(mcbb_csr)) अणु
		dev_err(&pdev->dev, "ioremap failed for MCBB CSR resource\n");
		वापस PTR_ERR(mcbb_csr);
	पूर्ण

	xgene_pmu->l3c_active_mask = 0x1;

	reg = पढ़ोl(csw_csr + CSW_CSWCR);
	अगर (reg & CSW_CSWCR_DUALMCB_MASK) अणु
		/* Dual MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Probe all active MC(s) */
		reg = पढ़ोl(mcbb_csr + CSW_CSWCR);
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0xF : 0x5;
	पूर्ण अन्यथा अणु
		/* Single MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Probe all active MC(s) */
		reg = पढ़ोl(mcba_csr + CSW_CSWCR);
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0x3 : 0x1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_pmu_v3_probe_active_mcb_mcu_l3c(काष्ठा xgene_pmu *xgene_pmu,
						काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *csw_csr;
	अचिन्हित पूर्णांक reg;
	u32 mcb0routing;
	u32 mcb1routing;

	csw_csr = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(csw_csr)) अणु
		dev_err(&pdev->dev, "ioremap failed for CSW CSR resource\n");
		वापस PTR_ERR(csw_csr);
	पूर्ण

	reg = पढ़ोl(csw_csr + CSW_CSWCR);
	mcb0routing = CSW_CSWCR_MCB0_ROUTING(reg);
	mcb1routing = CSW_CSWCR_MCB1_ROUTING(reg);
	अगर (reg & CSW_CSWCR_DUALMCB_MASK) अणु
		/* Dual MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Probe all active L3C(s), maximum is 8 */
		xgene_pmu->l3c_active_mask = 0xFF;
		/* Probe all active MC(s), maximum is 8 */
		अगर ((mcb0routing == 0x2) && (mcb1routing == 0x2))
			xgene_pmu->mc_active_mask = 0xFF;
		अन्यथा अगर ((mcb0routing == 0x1) && (mcb1routing == 0x1))
			xgene_pmu->mc_active_mask =  0x33;
		अन्यथा
			xgene_pmu->mc_active_mask =  0x11;
	पूर्ण अन्यथा अणु
		/* Single MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Probe all active L3C(s), maximum is 4 */
		xgene_pmu->l3c_active_mask = 0x0F;
		/* Probe all active MC(s), maximum is 4 */
		अगर (mcb0routing == 0x2)
			xgene_pmu->mc_active_mask = 0x0F;
		अन्यथा अगर (mcb0routing == 0x1)
			xgene_pmu->mc_active_mask =  0x03;
		अन्यथा
			xgene_pmu->mc_active_mask =  0x01;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fdt_pmu_probe_active_mcb_mcu_l3c(काष्ठा xgene_pmu *xgene_pmu,
					    काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *csw_map, *mcba_map, *mcbb_map;
	काष्ठा device_node *np = pdev->dev.of_node;
	अचिन्हित पूर्णांक reg;

	csw_map = syscon_regmap_lookup_by_phandle(np, "regmap-csw");
	अगर (IS_ERR(csw_map)) अणु
		dev_err(&pdev->dev, "unable to get syscon regmap csw\n");
		वापस PTR_ERR(csw_map);
	पूर्ण

	mcba_map = syscon_regmap_lookup_by_phandle(np, "regmap-mcba");
	अगर (IS_ERR(mcba_map)) अणु
		dev_err(&pdev->dev, "unable to get syscon regmap mcba\n");
		वापस PTR_ERR(mcba_map);
	पूर्ण

	mcbb_map = syscon_regmap_lookup_by_phandle(np, "regmap-mcbb");
	अगर (IS_ERR(mcbb_map)) अणु
		dev_err(&pdev->dev, "unable to get syscon regmap mcbb\n");
		वापस PTR_ERR(mcbb_map);
	पूर्ण

	xgene_pmu->l3c_active_mask = 0x1;
	अगर (regmap_पढ़ो(csw_map, CSW_CSWCR, &reg))
		वापस -EINVAL;

	अगर (reg & CSW_CSWCR_DUALMCB_MASK) अणु
		/* Dual MCB active */
		xgene_pmu->mcb_active_mask = 0x3;
		/* Probe all active MC(s) */
		अगर (regmap_पढ़ो(mcbb_map, MCBADDRMR, &reg))
			वापस 0;
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0xF : 0x5;
	पूर्ण अन्यथा अणु
		/* Single MCB active */
		xgene_pmu->mcb_active_mask = 0x1;
		/* Probe all active MC(s) */
		अगर (regmap_पढ़ो(mcba_map, MCBADDRMR, &reg))
			वापस 0;
		xgene_pmu->mc_active_mask =
			(reg & MCBADDRMR_DUALMCU_MODE_MASK) ? 0x3 : 0x1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pmu_probe_active_mcb_mcu_l3c(काष्ठा xgene_pmu *xgene_pmu,
					      काष्ठा platक्रमm_device *pdev)
अणु
	अगर (has_acpi_companion(&pdev->dev)) अणु
		अगर (xgene_pmu->version == PCP_PMU_V3)
			वापस acpi_pmu_v3_probe_active_mcb_mcu_l3c(xgene_pmu,
								    pdev);
		अन्यथा
			वापस acpi_pmu_probe_active_mcb_mcu_l3c(xgene_pmu,
								 pdev);
	पूर्ण
	वापस fdt_pmu_probe_active_mcb_mcu_l3c(xgene_pmu, pdev);
पूर्ण

अटल अक्षर *xgene_pmu_dev_name(काष्ठा device *dev, u32 type, पूर्णांक id)
अणु
	चयन (type) अणु
	हाल PMU_TYPE_L3C:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "l3c%d", id);
	हाल PMU_TYPE_IOB:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "iob%d", id);
	हाल PMU_TYPE_IOB_SLOW:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "iob_slow%d", id);
	हाल PMU_TYPE_MCB:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "mcb%d", id);
	हाल PMU_TYPE_MC:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "mc%d", id);
	शेष:
		वापस devm_kaप्र_लिखो(dev, GFP_KERNEL, "unknown");
	पूर्ण
पूर्ण

#अगर defined(CONFIG_ACPI)
अटल काष्ठा
xgene_pmu_dev_ctx *acpi_get_pmu_hw_inf(काष्ठा xgene_pmu *xgene_pmu,
				       काष्ठा acpi_device *adev, u32 type)
अणु
	काष्ठा device *dev = xgene_pmu->dev;
	काष्ठा list_head resource_list;
	काष्ठा xgene_pmu_dev_ctx *ctx;
	स्थिर जोड़ acpi_object *obj;
	काष्ठा hw_pmu_info *inf;
	व्योम __iomem *dev_csr;
	काष्ठा resource res;
	काष्ठा resource_entry *rentry;
	पूर्णांक enable_bit;
	पूर्णांक rc;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	INIT_LIST_HEAD(&resource_list);
	rc = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (rc <= 0) अणु
		dev_err(dev, "PMU type %d: No resources found\n", type);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		अगर (resource_type(rentry->res) == IORESOURCE_MEM) अणु
			res = *rentry->res;
			rentry = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (rentry) अणु
		dev_err(dev, "PMU type %d: No memory resource found\n", type);
		वापस शून्य;
	पूर्ण

	dev_csr = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(dev_csr)) अणु
		dev_err(dev, "PMU type %d: Fail to map resource\n", type);
		वापस शून्य;
	पूर्ण

	/* A PMU device node without enable-bit-index is always enabled */
	rc = acpi_dev_get_property(adev, "enable-bit-index",
				   ACPI_TYPE_INTEGER, &obj);
	अगर (rc < 0)
		enable_bit = 0;
	अन्यथा
		enable_bit = (पूर्णांक) obj->पूर्णांकeger.value;

	ctx->name = xgene_pmu_dev_name(dev, type, enable_bit);
	अगर (!ctx->name) अणु
		dev_err(dev, "PMU type %d: Fail to get device name\n", type);
		वापस शून्य;
	पूर्ण
	inf = &ctx->inf;
	inf->type = type;
	inf->csr = dev_csr;
	inf->enable_mask = 1 << enable_bit;

	वापस ctx;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id xgene_pmu_acpi_type_match[] = अणु
	अणु"APMC0D5D", PMU_TYPE_L3Cपूर्ण,
	अणु"APMC0D5E", PMU_TYPE_IOBपूर्ण,
	अणु"APMC0D5F", PMU_TYPE_MCBपूर्ण,
	अणु"APMC0D60", PMU_TYPE_MCपूर्ण,
	अणु"APMC0D84", PMU_TYPE_L3Cपूर्ण,
	अणु"APMC0D85", PMU_TYPE_IOBपूर्ण,
	अणु"APMC0D86", PMU_TYPE_IOB_SLOWपूर्ण,
	अणु"APMC0D87", PMU_TYPE_MCBपूर्ण,
	अणु"APMC0D88", PMU_TYPE_MCपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id *xgene_pmu_acpi_match_type(
					स्थिर काष्ठा acpi_device_id *ids,
					काष्ठा acpi_device *adev)
अणु
	स्थिर काष्ठा acpi_device_id *match_id = शून्य;
	स्थिर काष्ठा acpi_device_id *id;

	क्रम (id = ids; id->id[0] || id->cls; id++) अणु
		अगर (!acpi_match_device_ids(adev, id))
			match_id = id;
		अन्यथा अगर (match_id)
			अवरोध;
	पूर्ण

	वापस match_id;
पूर्ण

अटल acpi_status acpi_pmu_dev_add(acpi_handle handle, u32 level,
				    व्योम *data, व्योम **वापस_value)
अणु
	स्थिर काष्ठा acpi_device_id *acpi_id;
	काष्ठा xgene_pmu *xgene_pmu = data;
	काष्ठा xgene_pmu_dev_ctx *ctx;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;
	अगर (acpi_bus_get_status(adev) || !adev->status.present)
		वापस AE_OK;

	acpi_id = xgene_pmu_acpi_match_type(xgene_pmu_acpi_type_match, adev);
	अगर (!acpi_id)
		वापस AE_OK;

	ctx = acpi_get_pmu_hw_inf(xgene_pmu, adev, (u32)acpi_id->driver_data);
	अगर (!ctx)
		वापस AE_OK;

	अगर (xgene_pmu_dev_add(xgene_pmu, ctx)) अणु
		/* Can't add the PMU device, skip it */
		devm_kमुक्त(xgene_pmu->dev, ctx);
		वापस AE_OK;
	पूर्ण

	चयन (ctx->inf.type) अणु
	हाल PMU_TYPE_L3C:
		list_add(&ctx->next, &xgene_pmu->l3cpmus);
		अवरोध;
	हाल PMU_TYPE_IOB:
		list_add(&ctx->next, &xgene_pmu->iobpmus);
		अवरोध;
	हाल PMU_TYPE_IOB_SLOW:
		list_add(&ctx->next, &xgene_pmu->iobpmus);
		अवरोध;
	हाल PMU_TYPE_MCB:
		list_add(&ctx->next, &xgene_pmu->mcbpmus);
		अवरोध;
	हाल PMU_TYPE_MC:
		list_add(&ctx->next, &xgene_pmu->mcpmus);
		अवरोध;
	पूर्ण
	वापस AE_OK;
पूर्ण

अटल पूर्णांक acpi_pmu_probe_pmu_dev(काष्ठा xgene_pmu *xgene_pmu,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = xgene_pmu->dev;
	acpi_handle handle;
	acpi_status status;

	handle = ACPI_HANDLE(dev);
	अगर (!handle)
		वापस -EINVAL;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     acpi_pmu_dev_add, शून्य, xgene_pmu, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "failed to probe PMU devices\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक acpi_pmu_probe_pmu_dev(काष्ठा xgene_pmu *xgene_pmu,
				  काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा
xgene_pmu_dev_ctx *fdt_get_pmu_hw_inf(काष्ठा xgene_pmu *xgene_pmu,
				      काष्ठा device_node *np, u32 type)
अणु
	काष्ठा device *dev = xgene_pmu->dev;
	काष्ठा xgene_pmu_dev_ctx *ctx;
	काष्ठा hw_pmu_info *inf;
	व्योम __iomem *dev_csr;
	काष्ठा resource res;
	पूर्णांक enable_bit;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	अगर (of_address_to_resource(np, 0, &res) < 0) अणु
		dev_err(dev, "PMU type %d: No resource address found\n", type);
		वापस शून्य;
	पूर्ण

	dev_csr = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(dev_csr)) अणु
		dev_err(dev, "PMU type %d: Fail to map resource\n", type);
		वापस शून्य;
	पूर्ण

	/* A PMU device node without enable-bit-index is always enabled */
	अगर (of_property_पढ़ो_u32(np, "enable-bit-index", &enable_bit))
		enable_bit = 0;

	ctx->name = xgene_pmu_dev_name(dev, type, enable_bit);
	अगर (!ctx->name) अणु
		dev_err(dev, "PMU type %d: Fail to get device name\n", type);
		वापस शून्य;
	पूर्ण

	inf = &ctx->inf;
	inf->type = type;
	inf->csr = dev_csr;
	inf->enable_mask = 1 << enable_bit;

	वापस ctx;
पूर्ण

अटल पूर्णांक fdt_pmu_probe_pmu_dev(काष्ठा xgene_pmu *xgene_pmu,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_pmu_dev_ctx *ctx;
	काष्ठा device_node *np;

	क्रम_each_child_of_node(pdev->dev.of_node, np) अणु
		अगर (!of_device_is_available(np))
			जारी;

		अगर (of_device_is_compatible(np, "apm,xgene-pmu-l3c"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_L3C);
		अन्यथा अगर (of_device_is_compatible(np, "apm,xgene-pmu-iob"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_IOB);
		अन्यथा अगर (of_device_is_compatible(np, "apm,xgene-pmu-mcb"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_MCB);
		अन्यथा अगर (of_device_is_compatible(np, "apm,xgene-pmu-mc"))
			ctx = fdt_get_pmu_hw_inf(xgene_pmu, np, PMU_TYPE_MC);
		अन्यथा
			ctx = शून्य;

		अगर (!ctx)
			जारी;

		अगर (xgene_pmu_dev_add(xgene_pmu, ctx)) अणु
			/* Can't add the PMU device, skip it */
			devm_kमुक्त(xgene_pmu->dev, ctx);
			जारी;
		पूर्ण

		चयन (ctx->inf.type) अणु
		हाल PMU_TYPE_L3C:
			list_add(&ctx->next, &xgene_pmu->l3cpmus);
			अवरोध;
		हाल PMU_TYPE_IOB:
			list_add(&ctx->next, &xgene_pmu->iobpmus);
			अवरोध;
		हाल PMU_TYPE_IOB_SLOW:
			list_add(&ctx->next, &xgene_pmu->iobpmus);
			अवरोध;
		हाल PMU_TYPE_MCB:
			list_add(&ctx->next, &xgene_pmu->mcbpmus);
			अवरोध;
		हाल PMU_TYPE_MC:
			list_add(&ctx->next, &xgene_pmu->mcpmus);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pmu_probe_pmu_dev(काष्ठा xgene_pmu *xgene_pmu,
				   काष्ठा platक्रमm_device *pdev)
अणु
	अगर (has_acpi_companion(&pdev->dev))
		वापस acpi_pmu_probe_pmu_dev(xgene_pmu, pdev);
	वापस fdt_pmu_probe_pmu_dev(xgene_pmu, pdev);
पूर्ण

अटल स्थिर काष्ठा xgene_pmu_data xgene_pmu_data = अणु
	.id   = PCP_PMU_V1,
पूर्ण;

अटल स्थिर काष्ठा xgene_pmu_data xgene_pmu_v2_data = अणु
	.id   = PCP_PMU_V2,
पूर्ण;

अटल स्थिर काष्ठा xgene_pmu_ops xgene_pmu_ops = अणु
	.mask_पूर्णांक = xgene_pmu_mask_पूर्णांक,
	.unmask_पूर्णांक = xgene_pmu_unmask_पूर्णांक,
	.पढ़ो_counter = xgene_pmu_पढ़ो_counter32,
	.ग_लिखो_counter = xgene_pmu_ग_लिखो_counter32,
	.ग_लिखो_evttype = xgene_pmu_ग_लिखो_evttype,
	.ग_लिखो_agenपंचांगsk = xgene_pmu_ग_लिखो_agenपंचांगsk,
	.ग_लिखो_agent1msk = xgene_pmu_ग_लिखो_agent1msk,
	.enable_counter = xgene_pmu_enable_counter,
	.disable_counter = xgene_pmu_disable_counter,
	.enable_counter_पूर्णांक = xgene_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक = xgene_pmu_disable_counter_पूर्णांक,
	.reset_counters = xgene_pmu_reset_counters,
	.start_counters = xgene_pmu_start_counters,
	.stop_counters = xgene_pmu_stop_counters,
पूर्ण;

अटल स्थिर काष्ठा xgene_pmu_ops xgene_pmu_v3_ops = अणु
	.mask_पूर्णांक = xgene_pmu_v3_mask_पूर्णांक,
	.unmask_पूर्णांक = xgene_pmu_v3_unmask_पूर्णांक,
	.पढ़ो_counter = xgene_pmu_पढ़ो_counter64,
	.ग_लिखो_counter = xgene_pmu_ग_लिखो_counter64,
	.ग_लिखो_evttype = xgene_pmu_ग_लिखो_evttype,
	.ग_लिखो_agenपंचांगsk = xgene_pmu_v3_ग_लिखो_agenपंचांगsk,
	.ग_लिखो_agent1msk = xgene_pmu_v3_ग_लिखो_agent1msk,
	.enable_counter = xgene_pmu_enable_counter,
	.disable_counter = xgene_pmu_disable_counter,
	.enable_counter_पूर्णांक = xgene_pmu_enable_counter_पूर्णांक,
	.disable_counter_पूर्णांक = xgene_pmu_disable_counter_पूर्णांक,
	.reset_counters = xgene_pmu_reset_counters,
	.start_counters = xgene_pmu_start_counters,
	.stop_counters = xgene_pmu_stop_counters,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xgene_pmu_of_match[] = अणु
	अणु .compatible	= "apm,xgene-pmu",	.data = &xgene_pmu_data पूर्ण,
	अणु .compatible	= "apm,xgene-pmu-v2",	.data = &xgene_pmu_v2_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_pmu_of_match);
#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_pmu_acpi_match[] = अणु
	अणु"APMC0D5B", PCP_PMU_V1पूर्ण,
	अणु"APMC0D5C", PCP_PMU_V2पूर्ण,
	अणु"APMC0D83", PCP_PMU_V3पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_pmu_acpi_match);
#पूर्ण_अगर

अटल पूर्णांक xgene_pmu_online_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा xgene_pmu *xgene_pmu = hlist_entry_safe(node, काष्ठा xgene_pmu,
						       node);

	अगर (cpumask_empty(&xgene_pmu->cpu))
		cpumask_set_cpu(cpu, &xgene_pmu->cpu);

	/* Overflow पूर्णांकerrupt also should use the same CPU */
	WARN_ON(irq_set_affinity(xgene_pmu->irq, &xgene_pmu->cpu));

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा xgene_pmu *xgene_pmu = hlist_entry_safe(node, काष्ठा xgene_pmu,
						       node);
	काष्ठा xgene_pmu_dev_ctx *ctx;
	अचिन्हित पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &xgene_pmu->cpu))
		वापस 0;
	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	list_क्रम_each_entry(ctx, &xgene_pmu->mcpmus, next) अणु
		perf_pmu_migrate_context(&ctx->pmu_dev->pmu, cpu, target);
	पूर्ण
	list_क्रम_each_entry(ctx, &xgene_pmu->mcbpmus, next) अणु
		perf_pmu_migrate_context(&ctx->pmu_dev->pmu, cpu, target);
	पूर्ण
	list_क्रम_each_entry(ctx, &xgene_pmu->l3cpmus, next) अणु
		perf_pmu_migrate_context(&ctx->pmu_dev->pmu, cpu, target);
	पूर्ण
	list_क्रम_each_entry(ctx, &xgene_pmu->iobpmus, next) अणु
		perf_pmu_migrate_context(&ctx->pmu_dev->pmu, cpu, target);
	पूर्ण

	cpumask_set_cpu(target, &xgene_pmu->cpu);
	/* Overflow पूर्णांकerrupt also should use the same CPU */
	WARN_ON(irq_set_affinity(xgene_pmu->irq, &xgene_pmu->cpu));

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा xgene_pmu_data *dev_data;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा xgene_pmu *xgene_pmu;
	काष्ठा resource *res;
	पूर्णांक irq, rc;
	पूर्णांक version;

	/* Install a hook to update the पढ़ोer CPU in हाल it goes offline */
	rc = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
				      "CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE",
				      xgene_pmu_online_cpu,
				      xgene_pmu_offline_cpu);
	अगर (rc)
		वापस rc;

	xgene_pmu = devm_kzalloc(&pdev->dev, माप(*xgene_pmu), GFP_KERNEL);
	अगर (!xgene_pmu)
		वापस -ENOMEM;
	xgene_pmu->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, xgene_pmu);

	version = -EINVAL;
	of_id = of_match_device(xgene_pmu_of_match, &pdev->dev);
	अगर (of_id) अणु
		dev_data = (स्थिर काष्ठा xgene_pmu_data *) of_id->data;
		version = dev_data->id;
	पूर्ण

#अगर_घोषित CONFIG_ACPI
	अगर (ACPI_COMPANION(&pdev->dev)) अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(xgene_pmu_acpi_match, &pdev->dev);
		अगर (acpi_id)
			version = (पूर्णांक) acpi_id->driver_data;
	पूर्ण
#पूर्ण_अगर
	अगर (version < 0)
		वापस -ENODEV;

	अगर (version == PCP_PMU_V3)
		xgene_pmu->ops = &xgene_pmu_v3_ops;
	अन्यथा
		xgene_pmu->ops = &xgene_pmu_ops;

	INIT_LIST_HEAD(&xgene_pmu->l3cpmus);
	INIT_LIST_HEAD(&xgene_pmu->iobpmus);
	INIT_LIST_HEAD(&xgene_pmu->mcbpmus);
	INIT_LIST_HEAD(&xgene_pmu->mcpmus);

	xgene_pmu->version = version;
	dev_info(&pdev->dev, "X-Gene PMU version %d\n", xgene_pmu->version);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xgene_pmu->pcppmu_csr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xgene_pmu->pcppmu_csr)) अणु
		dev_err(&pdev->dev, "ioremap failed for PCP PMU resource\n");
		वापस PTR_ERR(xgene_pmu->pcppmu_csr);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	rc = devm_request_irq(&pdev->dev, irq, xgene_pmu_isr,
				IRQF_NOBALANCING | IRQF_NO_THREAD,
				dev_name(&pdev->dev), xgene_pmu);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Could not request IRQ %d\n", irq);
		वापस rc;
	पूर्ण

	xgene_pmu->irq = irq;

	raw_spin_lock_init(&xgene_pmu->lock);

	/* Check क्रम active MCBs and MCUs */
	rc = xgene_pmu_probe_active_mcb_mcu_l3c(xgene_pmu, pdev);
	अगर (rc) अणु
		dev_warn(&pdev->dev, "Unknown MCB/MCU active status\n");
		xgene_pmu->mcb_active_mask = 0x1;
		xgene_pmu->mc_active_mask = 0x1;
	पूर्ण

	/* Add this instance to the list used by the hotplug callback */
	rc = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
				      &xgene_pmu->node);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug", rc);
		वापस rc;
	पूर्ण

	/* Walk through the tree क्रम all PMU perf devices */
	rc = xgene_pmu_probe_pmu_dev(xgene_pmu, pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "No PMU perf devices found!\n");
		जाओ out_unरेजिस्टर;
	पूर्ण

	/* Enable पूर्णांकerrupt */
	xgene_pmu->ops->unmask_पूर्णांक(xgene_pmu);

	वापस 0;

out_unरेजिस्टर:
	cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
				    &xgene_pmu->node);
	वापस rc;
पूर्ण

अटल व्योम
xgene_pmu_dev_cleanup(काष्ठा xgene_pmu *xgene_pmu, काष्ठा list_head *pmus)
अणु
	काष्ठा xgene_pmu_dev_ctx *ctx;

	list_क्रम_each_entry(ctx, pmus, next) अणु
		perf_pmu_unरेजिस्टर(&ctx->pmu_dev->pmu);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_pmu *xgene_pmu = dev_get_drvdata(&pdev->dev);

	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->l3cpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->iobpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->mcbpmus);
	xgene_pmu_dev_cleanup(xgene_pmu, &xgene_pmu->mcpmus);
	cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE,
				    &xgene_pmu->node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xgene_pmu_driver = अणु
	.probe = xgene_pmu_probe,
	.हटाओ = xgene_pmu_हटाओ,
	.driver = अणु
		.name		= "xgene-pmu",
		.of_match_table = xgene_pmu_of_match,
		.acpi_match_table = ACPI_PTR(xgene_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(xgene_pmu_driver);
