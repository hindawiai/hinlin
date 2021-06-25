<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2014 ARM Limited
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा CCN_NUM_XP_PORTS 2
#घोषणा CCN_NUM_VCS 4
#घोषणा CCN_NUM_REGIONS	256
#घोषणा CCN_REGION_SIZE	0x10000

#घोषणा CCN_ALL_OLY_ID			0xff00
#घोषणा CCN_ALL_OLY_ID__OLY_ID__SHIFT			0
#घोषणा CCN_ALL_OLY_ID__OLY_ID__MASK			0x1f
#घोषणा CCN_ALL_OLY_ID__NODE_ID__SHIFT			8
#घोषणा CCN_ALL_OLY_ID__NODE_ID__MASK			0x3f

#घोषणा CCN_MN_ERRINT_STATUS		0x0008
#घोषणा CCN_MN_ERRINT_STATUS__INTREQ__DESSERT		0x11
#घोषणा CCN_MN_ERRINT_STATUS__ALL_ERRORS__ENABLE	0x02
#घोषणा CCN_MN_ERRINT_STATUS__ALL_ERRORS__DISABLED	0x20
#घोषणा CCN_MN_ERRINT_STATUS__ALL_ERRORS__DISABLE	0x22
#घोषणा CCN_MN_ERRINT_STATUS__CORRECTED_ERRORS_ENABLE	0x04
#घोषणा CCN_MN_ERRINT_STATUS__CORRECTED_ERRORS_DISABLED	0x40
#घोषणा CCN_MN_ERRINT_STATUS__CORRECTED_ERRORS_DISABLE	0x44
#घोषणा CCN_MN_ERRINT_STATUS__PMU_EVENTS__ENABLE	0x08
#घोषणा CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLED	0x80
#घोषणा CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLE	0x88
#घोषणा CCN_MN_OLY_COMP_LIST_63_0	0x01e0
#घोषणा CCN_MN_ERR_SIG_VAL_63_0		0x0300
#घोषणा CCN_MN_ERR_SIG_VAL_63_0__DT			(1 << 1)

#घोषणा CCN_DT_ACTIVE_DSM		0x0000
#घोषणा CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(n)		((n) * 8)
#घोषणा CCN_DT_ACTIVE_DSM__DSM_ID__MASK			0xff
#घोषणा CCN_DT_CTL			0x0028
#घोषणा CCN_DT_CTL__DT_EN				(1 << 0)
#घोषणा CCN_DT_PMEVCNT(n)		(0x0100 + (n) * 0x8)
#घोषणा CCN_DT_PMCCNTR			0x0140
#घोषणा CCN_DT_PMCCNTRSR		0x0190
#घोषणा CCN_DT_PMOVSR			0x0198
#घोषणा CCN_DT_PMOVSR_CLR		0x01a0
#घोषणा CCN_DT_PMOVSR_CLR__MASK				0x1f
#घोषणा CCN_DT_PMCR			0x01a8
#घोषणा CCN_DT_PMCR__OVFL_INTR_EN			(1 << 6)
#घोषणा CCN_DT_PMCR__PMU_EN				(1 << 0)
#घोषणा CCN_DT_PMSR			0x01b0
#घोषणा CCN_DT_PMSR_REQ			0x01b8
#घोषणा CCN_DT_PMSR_CLR			0x01c0

#घोषणा CCN_HNF_PMU_EVENT_SEL		0x0600
#घोषणा CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(n)		((n) * 4)
#घोषणा CCN_HNF_PMU_EVENT_SEL__ID__MASK			0xf

#घोषणा CCN_XP_DT_CONFIG		0x0300
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__SHIFT(n)		((n) * 4)
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__MASK			0xf
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__PASS_THROUGH		0x0
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT_0_OR_1	0x1
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT(n)		(0x2 + (n))
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT(n)	(0x4 + (n))
#घोषणा CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT(d, n) (0x8 + (d) * 4 + (n))
#घोषणा CCN_XP_DT_INTERFACE_SEL		0x0308
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_IO_SEL__SHIFT(n)	(0 + (n) * 8)
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_IO_SEL__MASK	0x1
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_DEV_SEL__SHIFT(n)	(1 + (n) * 8)
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_DEV_SEL__MASK	0x1
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_VC_SEL__SHIFT(n)	(2 + (n) * 8)
#घोषणा CCN_XP_DT_INTERFACE_SEL__DT_VC_SEL__MASK	0x3
#घोषणा CCN_XP_DT_CMP_VAL_L(n)		(0x0310 + (n) * 0x40)
#घोषणा CCN_XP_DT_CMP_VAL_H(n)		(0x0318 + (n) * 0x40)
#घोषणा CCN_XP_DT_CMP_MASK_L(n)		(0x0320 + (n) * 0x40)
#घोषणा CCN_XP_DT_CMP_MASK_H(n)		(0x0328 + (n) * 0x40)
#घोषणा CCN_XP_DT_CONTROL		0x0370
#घोषणा CCN_XP_DT_CONTROL__DT_ENABLE			(1 << 0)
#घोषणा CCN_XP_DT_CONTROL__WP_ARM_SEL__SHIFT(n)		(12 + (n) * 4)
#घोषणा CCN_XP_DT_CONTROL__WP_ARM_SEL__MASK		0xf
#घोषणा CCN_XP_DT_CONTROL__WP_ARM_SEL__ALWAYS		0xf
#घोषणा CCN_XP_PMU_EVENT_SEL		0x0600
#घोषणा CCN_XP_PMU_EVENT_SEL__ID__SHIFT(n)		((n) * 7)
#घोषणा CCN_XP_PMU_EVENT_SEL__ID__MASK			0x3f

#घोषणा CCN_SBAS_PMU_EVENT_SEL		0x0600
#घोषणा CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT(n)		((n) * 4)
#घोषणा CCN_SBAS_PMU_EVENT_SEL__ID__MASK		0xf

#घोषणा CCN_RNI_PMU_EVENT_SEL		0x0600
#घोषणा CCN_RNI_PMU_EVENT_SEL__ID__SHIFT(n)		((n) * 4)
#घोषणा CCN_RNI_PMU_EVENT_SEL__ID__MASK			0xf

#घोषणा CCN_TYPE_MN	0x01
#घोषणा CCN_TYPE_DT	0x02
#घोषणा CCN_TYPE_HNF	0x04
#घोषणा CCN_TYPE_HNI	0x05
#घोषणा CCN_TYPE_XP	0x08
#घोषणा CCN_TYPE_SBSX	0x0c
#घोषणा CCN_TYPE_SBAS	0x10
#घोषणा CCN_TYPE_RNI_1P	0x14
#घोषणा CCN_TYPE_RNI_2P	0x15
#घोषणा CCN_TYPE_RNI_3P	0x16
#घोषणा CCN_TYPE_RND_1P	0x18 /* RN-D = RN-I + DVM */
#घोषणा CCN_TYPE_RND_2P	0x19
#घोषणा CCN_TYPE_RND_3P	0x1a
#घोषणा CCN_TYPE_CYCLES	0xff /* Pseuकरोtype */

#घोषणा CCN_EVENT_WATCHPOINT 0xfe /* Pseuकरोevent */

#घोषणा CCN_NUM_PMU_EVENTS		4
#घोषणा CCN_NUM_XP_WATCHPOINTS		2 /* See DT.dbg_id.num_watchpoपूर्णांकs */
#घोषणा CCN_NUM_PMU_EVENT_COUNTERS	8 /* See DT.dbg_id.num_pmucntr */
#घोषणा CCN_IDX_PMU_CYCLE_COUNTER	CCN_NUM_PMU_EVENT_COUNTERS

#घोषणा CCN_NUM_PREDEFINED_MASKS	4
#घोषणा CCN_IDX_MASK_ANY		(CCN_NUM_PMU_EVENT_COUNTERS + 0)
#घोषणा CCN_IDX_MASK_EXACT		(CCN_NUM_PMU_EVENT_COUNTERS + 1)
#घोषणा CCN_IDX_MASK_ORDER		(CCN_NUM_PMU_EVENT_COUNTERS + 2)
#घोषणा CCN_IDX_MASK_OPCODE		(CCN_NUM_PMU_EVENT_COUNTERS + 3)

काष्ठा arm_ccn_component अणु
	व्योम __iomem *base;
	u32 type;

	DECLARE_BITMAP(pmu_events_mask, CCN_NUM_PMU_EVENTS);
	जोड़ अणु
		काष्ठा अणु
			DECLARE_BITMAP(dt_cmp_mask, CCN_NUM_XP_WATCHPOINTS);
		पूर्ण xp;
	पूर्ण;
पूर्ण;

#घोषणा pmu_to_arm_ccn(_pmu) container_of(container_of(_pmu, \
	काष्ठा arm_ccn_dt, pmu), काष्ठा arm_ccn, dt)

काष्ठा arm_ccn_dt अणु
	पूर्णांक id;
	व्योम __iomem *base;

	spinlock_t config_lock;

	DECLARE_BITMAP(pmu_counters_mask, CCN_NUM_PMU_EVENT_COUNTERS + 1);
	काष्ठा अणु
		काष्ठा arm_ccn_component *source;
		काष्ठा perf_event *event;
	पूर्ण pmu_counters[CCN_NUM_PMU_EVENT_COUNTERS + 1];

	काष्ठा अणु
	       u64 l, h;
	पूर्ण cmp_mask[CCN_NUM_PMU_EVENT_COUNTERS + CCN_NUM_PREDEFINED_MASKS];

	काष्ठा hrसमयr hrसमयr;

	अचिन्हित पूर्णांक cpu;
	काष्ठा hlist_node node;

	काष्ठा pmu pmu;
पूर्ण;

काष्ठा arm_ccn अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;

	अचिन्हित sbas_present:1;
	अचिन्हित sbsx_present:1;

	पूर्णांक num_nodes;
	काष्ठा arm_ccn_component *node;

	पूर्णांक num_xps;
	काष्ठा arm_ccn_component *xp;

	काष्ठा arm_ccn_dt dt;
	पूर्णांक mn_id;
पूर्ण;

अटल पूर्णांक arm_ccn_node_to_xp(पूर्णांक node)
अणु
	वापस node / CCN_NUM_XP_PORTS;
पूर्ण

अटल पूर्णांक arm_ccn_node_to_xp_port(पूर्णांक node)
अणु
	वापस node % CCN_NUM_XP_PORTS;
पूर्ण


/*
 * Bit shअगरts and masks in these defines must be kept in sync with
 * arm_ccn_pmu_config_set() and CCN_FORMAT_ATTRs below!
 */
#घोषणा CCN_CONFIG_NODE(_config)	(((_config) >> 0) & 0xff)
#घोषणा CCN_CONFIG_XP(_config)		(((_config) >> 0) & 0xff)
#घोषणा CCN_CONFIG_TYPE(_config)	(((_config) >> 8) & 0xff)
#घोषणा CCN_CONFIG_EVENT(_config)	(((_config) >> 16) & 0xff)
#घोषणा CCN_CONFIG_PORT(_config)	(((_config) >> 24) & 0x3)
#घोषणा CCN_CONFIG_BUS(_config)		(((_config) >> 24) & 0x3)
#घोषणा CCN_CONFIG_VC(_config)		(((_config) >> 26) & 0x7)
#घोषणा CCN_CONFIG_सूची(_config)		(((_config) >> 29) & 0x1)
#घोषणा CCN_CONFIG_MASK(_config)	(((_config) >> 30) & 0xf)

अटल व्योम arm_ccn_pmu_config_set(u64 *config, u32 node_xp, u32 type, u32 port)
अणु
	*config &= ~((0xff << 0) | (0xff << 8) | (0x3 << 24));
	*config |= (node_xp << 0) | (type << 8) | (port << 24);
पूर्ण

अटल sमाप_प्रकार arm_ccn_pmu_क्रमmat_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *ea = container_of(attr,
			काष्ठा dev_ext_attribute, attr);

	वापस sysfs_emit(buf, "%s\n", (अक्षर *)ea->var);
पूर्ण

#घोषणा CCN_FORMAT_ATTR(_name, _config) \
	काष्ठा dev_ext_attribute arm_ccn_pmu_क्रमmat_attr_##_name = \
			अणु __ATTR(_name, S_IRUGO, arm_ccn_pmu_क्रमmat_show, \
			शून्य), _config पूर्ण

अटल CCN_FORMAT_ATTR(node, "config:0-7");
अटल CCN_FORMAT_ATTR(xp, "config:0-7");
अटल CCN_FORMAT_ATTR(type, "config:8-15");
अटल CCN_FORMAT_ATTR(event, "config:16-23");
अटल CCN_FORMAT_ATTR(port, "config:24-25");
अटल CCN_FORMAT_ATTR(bus, "config:24-25");
अटल CCN_FORMAT_ATTR(vc, "config:26-28");
अटल CCN_FORMAT_ATTR(dir, "config:29-29");
अटल CCN_FORMAT_ATTR(mask, "config:30-33");
अटल CCN_FORMAT_ATTR(cmp_l, "config1:0-62");
अटल CCN_FORMAT_ATTR(cmp_h, "config2:0-59");

अटल काष्ठा attribute *arm_ccn_pmu_क्रमmat_attrs[] = अणु
	&arm_ccn_pmu_क्रमmat_attr_node.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_xp.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_type.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_event.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_port.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_bus.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_vc.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_dir.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_mask.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_cmp_l.attr.attr,
	&arm_ccn_pmu_क्रमmat_attr_cmp_h.attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_ccn_pmu_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = arm_ccn_pmu_क्रमmat_attrs,
पूर्ण;


काष्ठा arm_ccn_pmu_event अणु
	काष्ठा device_attribute attr;
	u32 type;
	u32 event;
	पूर्णांक num_ports;
	पूर्णांक num_vcs;
	स्थिर अक्षर *def;
	पूर्णांक mask;
पूर्ण;

#घोषणा CCN_EVENT_ATTR(_name) \
	__ATTR(_name, S_IRUGO, arm_ccn_pmu_event_show, शून्य)

/*
 * Events defined in TRM क्रम MN, HN-I and SBSX are actually watchpoपूर्णांकs set on
 * their ports in XP they are connected to. For the sake of usability they are
 * explicitly defined here (and translated पूर्णांकo a relevant watchpoपूर्णांक in
 * arm_ccn_pmu_event_init()) so the user can easily request them without deep
 * knowledge of the flit क्रमmat.
 */

#घोषणा CCN_EVENT_MN(_name, _def, _mask) अणु .attr = CCN_EVENT_ATTR(mn_##_name), \
		.type = CCN_TYPE_MN, .event = CCN_EVENT_WATCHPOINT, \
		.num_ports = CCN_NUM_XP_PORTS, .num_vcs = CCN_NUM_VCS, \
		.def = _def, .mask = _mask, पूर्ण

#घोषणा CCN_EVENT_HNI(_name, _def, _mask) अणु \
		.attr = CCN_EVENT_ATTR(hni_##_name), .type = CCN_TYPE_HNI, \
		.event = CCN_EVENT_WATCHPOINT, .num_ports = CCN_NUM_XP_PORTS, \
		.num_vcs = CCN_NUM_VCS, .def = _def, .mask = _mask, पूर्ण

#घोषणा CCN_EVENT_SBSX(_name, _def, _mask) अणु \
		.attr = CCN_EVENT_ATTR(sbsx_##_name), .type = CCN_TYPE_SBSX, \
		.event = CCN_EVENT_WATCHPOINT, .num_ports = CCN_NUM_XP_PORTS, \
		.num_vcs = CCN_NUM_VCS, .def = _def, .mask = _mask, पूर्ण

#घोषणा CCN_EVENT_HNF(_name, _event) अणु .attr = CCN_EVENT_ATTR(hnf_##_name), \
		.type = CCN_TYPE_HNF, .event = _event, पूर्ण

#घोषणा CCN_EVENT_XP(_name, _event) अणु .attr = CCN_EVENT_ATTR(xp_##_name), \
		.type = CCN_TYPE_XP, .event = _event, \
		.num_ports = CCN_NUM_XP_PORTS, .num_vcs = CCN_NUM_VCS, पूर्ण

/*
 * RN-I & RN-D (RN-D = RN-I + DVM) nodes have dअगरferent type ID depending
 * on configuration. One of them is picked to represent the whole group,
 * as they all share the same event types.
 */
#घोषणा CCN_EVENT_RNI(_name, _event) अणु .attr = CCN_EVENT_ATTR(rni_##_name), \
		.type = CCN_TYPE_RNI_3P, .event = _event, पूर्ण

#घोषणा CCN_EVENT_SBAS(_name, _event) अणु .attr = CCN_EVENT_ATTR(sbas_##_name), \
		.type = CCN_TYPE_SBAS, .event = _event, पूर्ण

#घोषणा CCN_EVENT_CYCLES(_name) अणु .attr = CCN_EVENT_ATTR(_name), \
		.type = CCN_TYPE_CYCLES पूर्ण


अटल sमाप_प्रकार arm_ccn_pmu_event_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	काष्ठा arm_ccn_pmu_event *event = container_of(attr,
			काष्ठा arm_ccn_pmu_event, attr);
	पूर्णांक res;

	res = sysfs_emit(buf, "type=0x%x", event->type);
	अगर (event->event)
		res += sysfs_emit_at(buf, res, ",event=0x%x", event->event);
	अगर (event->def)
		res += sysfs_emit_at(buf, res, ",%s", event->def);
	अगर (event->mask)
		res += sysfs_emit_at(buf, res, ",mask=0x%x", event->mask);

	/* Arguments required by an event */
	चयन (event->type) अणु
	हाल CCN_TYPE_CYCLES:
		अवरोध;
	हाल CCN_TYPE_XP:
		res += sysfs_emit_at(buf, res, ",xp=?,vc=?");
		अगर (event->event == CCN_EVENT_WATCHPOINT)
			res += sysfs_emit_at(buf, res,
					",port=?,dir=?,cmp_l=?,cmp_h=?,mask=?");
		अन्यथा
			res += sysfs_emit_at(buf, res, ",bus=?");

		अवरोध;
	हाल CCN_TYPE_MN:
		res += sysfs_emit_at(buf, res, ",node=%d", ccn->mn_id);
		अवरोध;
	शेष:
		res += sysfs_emit_at(buf, res, ",node=?");
		अवरोध;
	पूर्ण

	res += sysfs_emit_at(buf, res, "\n");

	वापस res;
पूर्ण

अटल umode_t arm_ccn_pmu_events_is_visible(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	काष्ठा device_attribute *dev_attr = container_of(attr,
			काष्ठा device_attribute, attr);
	काष्ठा arm_ccn_pmu_event *event = container_of(dev_attr,
			काष्ठा arm_ccn_pmu_event, attr);

	अगर (event->type == CCN_TYPE_SBAS && !ccn->sbas_present)
		वापस 0;
	अगर (event->type == CCN_TYPE_SBSX && !ccn->sbsx_present)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा arm_ccn_pmu_event arm_ccn_pmu_events[] = अणु
	CCN_EVENT_MN(eobarrier, "dir=1,vc=0,cmp_h=0x1c00", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_MN(ecbarrier, "dir=1,vc=0,cmp_h=0x1e00", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_MN(dvmop, "dir=1,vc=0,cmp_h=0x2800", CCN_IDX_MASK_OPCODE),
	CCN_EVENT_HNI(txdatflits, "dir=1,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(rxdatflits, "dir=0,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(txreqflits, "dir=1,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(rxreqflits, "dir=0,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_HNI(rxreqflits_order, "dir=0,vc=0,cmp_h=0x8000",
			CCN_IDX_MASK_ORDER),
	CCN_EVENT_SBSX(txdatflits, "dir=1,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(rxdatflits, "dir=0,vc=3", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(txreqflits, "dir=1,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(rxreqflits, "dir=0,vc=0", CCN_IDX_MASK_ANY),
	CCN_EVENT_SBSX(rxreqflits_order, "dir=0,vc=0,cmp_h=0x8000",
			CCN_IDX_MASK_ORDER),
	CCN_EVENT_HNF(cache_miss, 0x1),
	CCN_EVENT_HNF(l3_sf_cache_access, 0x02),
	CCN_EVENT_HNF(cache_fill, 0x3),
	CCN_EVENT_HNF(pocq_retry, 0x4),
	CCN_EVENT_HNF(pocq_reqs_recvd, 0x5),
	CCN_EVENT_HNF(sf_hit, 0x6),
	CCN_EVENT_HNF(sf_evictions, 0x7),
	CCN_EVENT_HNF(snoops_sent, 0x8),
	CCN_EVENT_HNF(snoops_broadcast, 0x9),
	CCN_EVENT_HNF(l3_eviction, 0xa),
	CCN_EVENT_HNF(l3_fill_invalid_way, 0xb),
	CCN_EVENT_HNF(mc_retries, 0xc),
	CCN_EVENT_HNF(mc_reqs, 0xd),
	CCN_EVENT_HNF(qos_hh_retry, 0xe),
	CCN_EVENT_RNI(rdata_beats_p0, 0x1),
	CCN_EVENT_RNI(rdata_beats_p1, 0x2),
	CCN_EVENT_RNI(rdata_beats_p2, 0x3),
	CCN_EVENT_RNI(rxdat_flits, 0x4),
	CCN_EVENT_RNI(txdat_flits, 0x5),
	CCN_EVENT_RNI(txreq_flits, 0x6),
	CCN_EVENT_RNI(txreq_flits_retried, 0x7),
	CCN_EVENT_RNI(rrt_full, 0x8),
	CCN_EVENT_RNI(wrt_full, 0x9),
	CCN_EVENT_RNI(txreq_flits_replayed, 0xa),
	CCN_EVENT_XP(upload_starvation, 0x1),
	CCN_EVENT_XP(करोwnload_starvation, 0x2),
	CCN_EVENT_XP(respin, 0x3),
	CCN_EVENT_XP(valid_flit, 0x4),
	CCN_EVENT_XP(watchpoपूर्णांक, CCN_EVENT_WATCHPOINT),
	CCN_EVENT_SBAS(rdata_beats_p0, 0x1),
	CCN_EVENT_SBAS(rxdat_flits, 0x4),
	CCN_EVENT_SBAS(txdat_flits, 0x5),
	CCN_EVENT_SBAS(txreq_flits, 0x6),
	CCN_EVENT_SBAS(txreq_flits_retried, 0x7),
	CCN_EVENT_SBAS(rrt_full, 0x8),
	CCN_EVENT_SBAS(wrt_full, 0x9),
	CCN_EVENT_SBAS(txreq_flits_replayed, 0xa),
	CCN_EVENT_CYCLES(cycles),
पूर्ण;

/* Populated in arm_ccn_init() */
अटल काष्ठा attribute
		*arm_ccn_pmu_events_attrs[ARRAY_SIZE(arm_ccn_pmu_events) + 1];

अटल स्थिर काष्ठा attribute_group arm_ccn_pmu_events_attr_group = अणु
	.name = "events",
	.is_visible = arm_ccn_pmu_events_is_visible,
	.attrs = arm_ccn_pmu_events_attrs,
पूर्ण;


अटल u64 *arm_ccn_pmu_get_cmp_mask(काष्ठा arm_ccn *ccn, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ i;

	अगर (WARN_ON(!name || !name[0] || !है_षष्ठादशक(name[0]) || !name[1]))
		वापस शून्य;
	i = है_अंक(name[0]) ? name[0] - '0' : 0xa + tolower(name[0]) - 'a';

	चयन (name[1]) अणु
	हाल 'l':
		वापस &ccn->dt.cmp_mask[i].l;
	हाल 'h':
		वापस &ccn->dt.cmp_mask[i].h;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार arm_ccn_pmu_cmp_mask_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	u64 *mask = arm_ccn_pmu_get_cmp_mask(ccn, attr->attr.name);

	वापस mask ? sysfs_emit(buf, "0x%016llx\n", *mask) : -EINVAL;
पूर्ण

अटल sमाप_प्रकार arm_ccn_pmu_cmp_mask_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	u64 *mask = arm_ccn_pmu_get_cmp_mask(ccn, attr->attr.name);
	पूर्णांक err = -EINVAL;

	अगर (mask)
		err = kम_से_अदीर्घl(buf, 0, mask);

	वापस err ? err : count;
पूर्ण

#घोषणा CCN_CMP_MASK_ATTR(_name) \
	काष्ठा device_attribute arm_ccn_pmu_cmp_mask_attr_##_name = \
			__ATTR(_name, S_IRUGO | S_IWUSR, \
			arm_ccn_pmu_cmp_mask_show, arm_ccn_pmu_cmp_mask_store)

#घोषणा CCN_CMP_MASK_ATTR_RO(_name) \
	काष्ठा device_attribute arm_ccn_pmu_cmp_mask_attr_##_name = \
			__ATTR(_name, S_IRUGO, arm_ccn_pmu_cmp_mask_show, शून्य)

अटल CCN_CMP_MASK_ATTR(0l);
अटल CCN_CMP_MASK_ATTR(0h);
अटल CCN_CMP_MASK_ATTR(1l);
अटल CCN_CMP_MASK_ATTR(1h);
अटल CCN_CMP_MASK_ATTR(2l);
अटल CCN_CMP_MASK_ATTR(2h);
अटल CCN_CMP_MASK_ATTR(3l);
अटल CCN_CMP_MASK_ATTR(3h);
अटल CCN_CMP_MASK_ATTR(4l);
अटल CCN_CMP_MASK_ATTR(4h);
अटल CCN_CMP_MASK_ATTR(5l);
अटल CCN_CMP_MASK_ATTR(5h);
अटल CCN_CMP_MASK_ATTR(6l);
अटल CCN_CMP_MASK_ATTR(6h);
अटल CCN_CMP_MASK_ATTR(7l);
अटल CCN_CMP_MASK_ATTR(7h);
अटल CCN_CMP_MASK_ATTR_RO(8l);
अटल CCN_CMP_MASK_ATTR_RO(8h);
अटल CCN_CMP_MASK_ATTR_RO(9l);
अटल CCN_CMP_MASK_ATTR_RO(9h);
अटल CCN_CMP_MASK_ATTR_RO(al);
अटल CCN_CMP_MASK_ATTR_RO(ah);
अटल CCN_CMP_MASK_ATTR_RO(bl);
अटल CCN_CMP_MASK_ATTR_RO(bh);

अटल काष्ठा attribute *arm_ccn_pmu_cmp_mask_attrs[] = अणु
	&arm_ccn_pmu_cmp_mask_attr_0l.attr, &arm_ccn_pmu_cmp_mask_attr_0h.attr,
	&arm_ccn_pmu_cmp_mask_attr_1l.attr, &arm_ccn_pmu_cmp_mask_attr_1h.attr,
	&arm_ccn_pmu_cmp_mask_attr_2l.attr, &arm_ccn_pmu_cmp_mask_attr_2h.attr,
	&arm_ccn_pmu_cmp_mask_attr_3l.attr, &arm_ccn_pmu_cmp_mask_attr_3h.attr,
	&arm_ccn_pmu_cmp_mask_attr_4l.attr, &arm_ccn_pmu_cmp_mask_attr_4h.attr,
	&arm_ccn_pmu_cmp_mask_attr_5l.attr, &arm_ccn_pmu_cmp_mask_attr_5h.attr,
	&arm_ccn_pmu_cmp_mask_attr_6l.attr, &arm_ccn_pmu_cmp_mask_attr_6h.attr,
	&arm_ccn_pmu_cmp_mask_attr_7l.attr, &arm_ccn_pmu_cmp_mask_attr_7h.attr,
	&arm_ccn_pmu_cmp_mask_attr_8l.attr, &arm_ccn_pmu_cmp_mask_attr_8h.attr,
	&arm_ccn_pmu_cmp_mask_attr_9l.attr, &arm_ccn_pmu_cmp_mask_attr_9h.attr,
	&arm_ccn_pmu_cmp_mask_attr_al.attr, &arm_ccn_pmu_cmp_mask_attr_ah.attr,
	&arm_ccn_pmu_cmp_mask_attr_bl.attr, &arm_ccn_pmu_cmp_mask_attr_bh.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_ccn_pmu_cmp_mask_attr_group = अणु
	.name = "cmp_mask",
	.attrs = arm_ccn_pmu_cmp_mask_attrs,
पूर्ण;

अटल sमाप_प्रकार arm_ccn_pmu_cpumask_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(ccn->dt.cpu));
पूर्ण

अटल काष्ठा device_attribute arm_ccn_pmu_cpumask_attr =
		__ATTR(cpumask, S_IRUGO, arm_ccn_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *arm_ccn_pmu_cpumask_attrs[] = अणु
	&arm_ccn_pmu_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_ccn_pmu_cpumask_attr_group = अणु
	.attrs = arm_ccn_pmu_cpumask_attrs,
पूर्ण;

/*
 * Default poll period is 10ms, which is way over the top anyway,
 * as in the worst हाल scenario (an event every cycle), with 1GHz
 * घड़ीed bus, the smallest, 32 bit counter will overflow in
 * more than 4s.
 */
अटल अचिन्हित पूर्णांक arm_ccn_pmu_poll_period_us = 10000;
module_param_named(pmu_poll_period_us, arm_ccn_pmu_poll_period_us, uपूर्णांक,
		S_IRUGO | S_IWUSR);

अटल kसमय_प्रकार arm_ccn_pmu_समयr_period(व्योम)
अणु
	वापस ns_to_kसमय((u64)arm_ccn_pmu_poll_period_us * 1000);
पूर्ण


अटल स्थिर काष्ठा attribute_group *arm_ccn_pmu_attr_groups[] = अणु
	&arm_ccn_pmu_events_attr_group,
	&arm_ccn_pmu_क्रमmat_attr_group,
	&arm_ccn_pmu_cmp_mask_attr_group,
	&arm_ccn_pmu_cpumask_attr_group,
	शून्य
पूर्ण;


अटल पूर्णांक arm_ccn_pmu_alloc_bit(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित दीर्घ size)
अणु
	पूर्णांक bit;

	करो अणु
		bit = find_first_zero_bit(biपंचांगap, size);
		अगर (bit >= size)
			वापस -EAGAIN;
	पूर्ण जबतक (test_and_set_bit(bit, biपंचांगap));

	वापस bit;
पूर्ण

/* All RN-I and RN-D nodes have identical PMUs */
अटल पूर्णांक arm_ccn_pmu_type_eq(u32 a, u32 b)
अणु
	अगर (a == b)
		वापस 1;

	चयन (a) अणु
	हाल CCN_TYPE_RNI_1P:
	हाल CCN_TYPE_RNI_2P:
	हाल CCN_TYPE_RNI_3P:
	हाल CCN_TYPE_RND_1P:
	हाल CCN_TYPE_RND_2P:
	हाल CCN_TYPE_RND_3P:
		चयन (b) अणु
		हाल CCN_TYPE_RNI_1P:
		हाल CCN_TYPE_RNI_2P:
		हाल CCN_TYPE_RNI_3P:
		हाल CCN_TYPE_RND_1P:
		हाल CCN_TYPE_RND_2P:
		हाल CCN_TYPE_RND_3P:
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_ccn_pmu_event_alloc(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	u32 node_xp, type, event_id;
	काष्ठा arm_ccn_component *source;
	पूर्णांक bit;

	node_xp = CCN_CONFIG_NODE(event->attr.config);
	type = CCN_CONFIG_TYPE(event->attr.config);
	event_id = CCN_CONFIG_EVENT(event->attr.config);

	/* Allocate the cycle counter */
	अगर (type == CCN_TYPE_CYCLES) अणु
		अगर (test_and_set_bit(CCN_IDX_PMU_CYCLE_COUNTER,
				ccn->dt.pmu_counters_mask))
			वापस -EAGAIN;

		hw->idx = CCN_IDX_PMU_CYCLE_COUNTER;
		ccn->dt.pmu_counters[CCN_IDX_PMU_CYCLE_COUNTER].event = event;

		वापस 0;
	पूर्ण

	/* Allocate an event counter */
	hw->idx = arm_ccn_pmu_alloc_bit(ccn->dt.pmu_counters_mask,
			CCN_NUM_PMU_EVENT_COUNTERS);
	अगर (hw->idx < 0) अणु
		dev_dbg(ccn->dev, "No more counters available!\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (type == CCN_TYPE_XP)
		source = &ccn->xp[node_xp];
	अन्यथा
		source = &ccn->node[node_xp];
	ccn->dt.pmu_counters[hw->idx].source = source;

	/* Allocate an event source or a watchpoपूर्णांक */
	अगर (type == CCN_TYPE_XP && event_id == CCN_EVENT_WATCHPOINT)
		bit = arm_ccn_pmu_alloc_bit(source->xp.dt_cmp_mask,
				CCN_NUM_XP_WATCHPOINTS);
	अन्यथा
		bit = arm_ccn_pmu_alloc_bit(source->pmu_events_mask,
				CCN_NUM_PMU_EVENTS);
	अगर (bit < 0) अणु
		dev_dbg(ccn->dev, "No more event sources/watchpoints on node/XP %d!\n",
				node_xp);
		clear_bit(hw->idx, ccn->dt.pmu_counters_mask);
		वापस -EAGAIN;
	पूर्ण
	hw->config_base = bit;

	ccn->dt.pmu_counters[hw->idx].event = event;

	वापस 0;
पूर्ण

अटल व्योम arm_ccn_pmu_event_release(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (hw->idx == CCN_IDX_PMU_CYCLE_COUNTER) अणु
		clear_bit(CCN_IDX_PMU_CYCLE_COUNTER, ccn->dt.pmu_counters_mask);
	पूर्ण अन्यथा अणु
		काष्ठा arm_ccn_component *source =
				ccn->dt.pmu_counters[hw->idx].source;

		अगर (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP &&
				CCN_CONFIG_EVENT(event->attr.config) ==
				CCN_EVENT_WATCHPOINT)
			clear_bit(hw->config_base, source->xp.dt_cmp_mask);
		अन्यथा
			clear_bit(hw->config_base, source->pmu_events_mask);
		clear_bit(hw->idx, ccn->dt.pmu_counters_mask);
	पूर्ण

	ccn->dt.pmu_counters[hw->idx].source = शून्य;
	ccn->dt.pmu_counters[hw->idx].event = शून्य;
पूर्ण

अटल पूर्णांक arm_ccn_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn;
	काष्ठा hw_perf_event *hw = &event->hw;
	u32 node_xp, type, event_id;
	पूर्णांक valid;
	पूर्णांक i;
	काष्ठा perf_event *sibling;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	ccn = pmu_to_arm_ccn(event->pmu);

	अगर (hw->sample_period) अणु
		dev_dbg(ccn->dev, "Sampling not supported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (has_branch_stack(event)) अणु
		dev_dbg(ccn->dev, "Can't exclude execution levels!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (event->cpu < 0) अणु
		dev_dbg(ccn->dev, "Can't provide per-task data!\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	/*
	 * Many perf core operations (eg. events rotation) operate on a
	 * single CPU context. This is obvious क्रम CPU PMUs, where one
	 * expects the same sets of events being observed on all CPUs,
	 * but can lead to issues क्रम off-core PMUs, like CCN, where each
	 * event could be theoretically asचिन्हित to a dअगरferent CPU. To
	 * mitigate this, we enक्रमce CPU assignment to one, selected
	 * processor (the one described in the "cpumask" attribute).
	 */
	event->cpu = ccn->dt.cpu;

	node_xp = CCN_CONFIG_NODE(event->attr.config);
	type = CCN_CONFIG_TYPE(event->attr.config);
	event_id = CCN_CONFIG_EVENT(event->attr.config);

	/* Validate node/xp vs topology */
	चयन (type) अणु
	हाल CCN_TYPE_MN:
		अगर (node_xp != ccn->mn_id) अणु
			dev_dbg(ccn->dev, "Invalid MN ID %d!\n", node_xp);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल CCN_TYPE_XP:
		अगर (node_xp >= ccn->num_xps) अणु
			dev_dbg(ccn->dev, "Invalid XP ID %d!\n", node_xp);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल CCN_TYPE_CYCLES:
		अवरोध;
	शेष:
		अगर (node_xp >= ccn->num_nodes) अणु
			dev_dbg(ccn->dev, "Invalid node ID %d!\n", node_xp);
			वापस -EINVAL;
		पूर्ण
		अगर (!arm_ccn_pmu_type_eq(type, ccn->node[node_xp].type)) अणु
			dev_dbg(ccn->dev, "Invalid type 0x%x for node %d!\n",
					type, node_xp);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Validate event ID vs available क्रम the type */
	क्रम (i = 0, valid = 0; i < ARRAY_SIZE(arm_ccn_pmu_events) && !valid;
			i++) अणु
		काष्ठा arm_ccn_pmu_event *e = &arm_ccn_pmu_events[i];
		u32 port = CCN_CONFIG_PORT(event->attr.config);
		u32 vc = CCN_CONFIG_VC(event->attr.config);

		अगर (!arm_ccn_pmu_type_eq(type, e->type))
			जारी;
		अगर (event_id != e->event)
			जारी;
		अगर (e->num_ports && port >= e->num_ports) अणु
			dev_dbg(ccn->dev, "Invalid port %d for node/XP %d!\n",
					port, node_xp);
			वापस -EINVAL;
		पूर्ण
		अगर (e->num_vcs && vc >= e->num_vcs) अणु
			dev_dbg(ccn->dev, "Invalid vc %d for node/XP %d!\n",
					vc, node_xp);
			वापस -EINVAL;
		पूर्ण
		valid = 1;
	पूर्ण
	अगर (!valid) अणु
		dev_dbg(ccn->dev, "Invalid event 0x%x for node/XP %d!\n",
				event_id, node_xp);
		वापस -EINVAL;
	पूर्ण

	/* Watchpoपूर्णांक-based event क्रम a node is actually set on XP */
	अगर (event_id == CCN_EVENT_WATCHPOINT && type != CCN_TYPE_XP) अणु
		u32 port;

		type = CCN_TYPE_XP;
		port = arm_ccn_node_to_xp_port(node_xp);
		node_xp = arm_ccn_node_to_xp(node_xp);

		arm_ccn_pmu_config_set(&event->attr.config,
				node_xp, type, port);
	पूर्ण

	/*
	 * We must NOT create groups containing mixed PMUs, although software
	 * events are acceptable (क्रम example to create a CCN group
	 * periodically पढ़ो when a hrसमयr aka cpu-घड़ी leader triggers).
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

अटल u64 arm_ccn_pmu_पढ़ो_counter(काष्ठा arm_ccn *ccn, पूर्णांक idx)
अणु
	u64 res;

	अगर (idx == CCN_IDX_PMU_CYCLE_COUNTER) अणु
#अगर_घोषित पढ़ोq
		res = पढ़ोq(ccn->dt.base + CCN_DT_PMCCNTR);
#अन्यथा
		/* 40 bit counter, can करो snapshot and पढ़ो in two parts */
		ग_लिखोl(0x1, ccn->dt.base + CCN_DT_PMSR_REQ);
		जबतक (!(पढ़ोl(ccn->dt.base + CCN_DT_PMSR) & 0x1))
			;
		ग_लिखोl(0x1, ccn->dt.base + CCN_DT_PMSR_CLR);
		res = पढ़ोl(ccn->dt.base + CCN_DT_PMCCNTRSR + 4) & 0xff;
		res <<= 32;
		res |= पढ़ोl(ccn->dt.base + CCN_DT_PMCCNTRSR);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		res = पढ़ोl(ccn->dt.base + CCN_DT_PMEVCNT(idx));
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम arm_ccn_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	u64 prev_count, new_count, mask;

	करो अणु
		prev_count = local64_पढ़ो(&hw->prev_count);
		new_count = arm_ccn_pmu_पढ़ो_counter(ccn, hw->idx);
	पूर्ण जबतक (local64_xchg(&hw->prev_count, new_count) != prev_count);

	mask = (1LLU << (hw->idx == CCN_IDX_PMU_CYCLE_COUNTER ? 40 : 32)) - 1;

	local64_add((new_count - prev_count) & mask, &event->count);
पूर्ण

अटल व्योम arm_ccn_pmu_xp_dt_config(काष्ठा perf_event *event, पूर्णांक enable)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा arm_ccn_component *xp;
	u32 val, dt_cfg;

	/* Nothing to करो क्रम cycle counter */
	अगर (hw->idx == CCN_IDX_PMU_CYCLE_COUNTER)
		वापस;

	अगर (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP)
		xp = &ccn->xp[CCN_CONFIG_XP(event->attr.config)];
	अन्यथा
		xp = &ccn->xp[arm_ccn_node_to_xp(
				CCN_CONFIG_NODE(event->attr.config))];

	अगर (enable)
		dt_cfg = hw->event_base;
	अन्यथा
		dt_cfg = CCN_XP_DT_CONFIG__DT_CFG__PASS_THROUGH;

	spin_lock(&ccn->dt.config_lock);

	val = पढ़ोl(xp->base + CCN_XP_DT_CONFIG);
	val &= ~(CCN_XP_DT_CONFIG__DT_CFG__MASK <<
			CCN_XP_DT_CONFIG__DT_CFG__SHIFT(hw->idx));
	val |= dt_cfg << CCN_XP_DT_CONFIG__DT_CFG__SHIFT(hw->idx);
	ग_लिखोl(val, xp->base + CCN_XP_DT_CONFIG);

	spin_unlock(&ccn->dt.config_lock);
पूर्ण

अटल व्योम arm_ccn_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;

	local64_set(&event->hw.prev_count,
			arm_ccn_pmu_पढ़ो_counter(ccn, hw->idx));
	hw->state = 0;

	/* Set the DT bus input, engaging the counter */
	arm_ccn_pmu_xp_dt_config(event, 1);
पूर्ण

अटल व्योम arm_ccn_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	/* Disable counting, setting the DT bus to pass-through mode */
	arm_ccn_pmu_xp_dt_config(event, 0);

	अगर (flags & PERF_EF_UPDATE)
		arm_ccn_pmu_event_update(event);

	hw->state |= PERF_HES_STOPPED;
पूर्ण

अटल व्योम arm_ccn_pmu_xp_watchpoपूर्णांक_config(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा arm_ccn_component *source =
			ccn->dt.pmu_counters[hw->idx].source;
	अचिन्हित दीर्घ wp = hw->config_base;
	u32 val;
	u64 cmp_l = event->attr.config1;
	u64 cmp_h = event->attr.config2;
	u64 mask_l = ccn->dt.cmp_mask[CCN_CONFIG_MASK(event->attr.config)].l;
	u64 mask_h = ccn->dt.cmp_mask[CCN_CONFIG_MASK(event->attr.config)].h;

	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__WATCHPOINT(wp);

	/* Direction (RX/TX), device (port) & भव channel */
	val = पढ़ोl(source->base + CCN_XP_DT_INTERFACE_SEL);
	val &= ~(CCN_XP_DT_INTERFACE_SEL__DT_IO_SEL__MASK <<
			CCN_XP_DT_INTERFACE_SEL__DT_IO_SEL__SHIFT(wp));
	val |= CCN_CONFIG_सूची(event->attr.config) <<
			CCN_XP_DT_INTERFACE_SEL__DT_IO_SEL__SHIFT(wp);
	val &= ~(CCN_XP_DT_INTERFACE_SEL__DT_DEV_SEL__MASK <<
			CCN_XP_DT_INTERFACE_SEL__DT_DEV_SEL__SHIFT(wp));
	val |= CCN_CONFIG_PORT(event->attr.config) <<
			CCN_XP_DT_INTERFACE_SEL__DT_DEV_SEL__SHIFT(wp);
	val &= ~(CCN_XP_DT_INTERFACE_SEL__DT_VC_SEL__MASK <<
			CCN_XP_DT_INTERFACE_SEL__DT_VC_SEL__SHIFT(wp));
	val |= CCN_CONFIG_VC(event->attr.config) <<
			CCN_XP_DT_INTERFACE_SEL__DT_VC_SEL__SHIFT(wp);
	ग_लिखोl(val, source->base + CCN_XP_DT_INTERFACE_SEL);

	/* Comparison values */
	ग_लिखोl(cmp_l & 0xffffffff, source->base + CCN_XP_DT_CMP_VAL_L(wp));
	ग_लिखोl((cmp_l >> 32) & 0x7fffffff,
			source->base + CCN_XP_DT_CMP_VAL_L(wp) + 4);
	ग_लिखोl(cmp_h & 0xffffffff, source->base + CCN_XP_DT_CMP_VAL_H(wp));
	ग_लिखोl((cmp_h >> 32) & 0x0fffffff,
			source->base + CCN_XP_DT_CMP_VAL_H(wp) + 4);

	/* Mask */
	ग_लिखोl(mask_l & 0xffffffff, source->base + CCN_XP_DT_CMP_MASK_L(wp));
	ग_लिखोl((mask_l >> 32) & 0x7fffffff,
			source->base + CCN_XP_DT_CMP_MASK_L(wp) + 4);
	ग_लिखोl(mask_h & 0xffffffff, source->base + CCN_XP_DT_CMP_MASK_H(wp));
	ग_लिखोl((mask_h >> 32) & 0x0fffffff,
			source->base + CCN_XP_DT_CMP_MASK_H(wp) + 4);
पूर्ण

अटल व्योम arm_ccn_pmu_xp_event_config(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा arm_ccn_component *source =
			ccn->dt.pmu_counters[hw->idx].source;
	u32 val, id;

	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT(hw->config_base);

	id = (CCN_CONFIG_VC(event->attr.config) << 4) |
			(CCN_CONFIG_BUS(event->attr.config) << 3) |
			(CCN_CONFIG_EVENT(event->attr.config) << 0);

	val = पढ़ोl(source->base + CCN_XP_PMU_EVENT_SEL);
	val &= ~(CCN_XP_PMU_EVENT_SEL__ID__MASK <<
			CCN_XP_PMU_EVENT_SEL__ID__SHIFT(hw->config_base));
	val |= id << CCN_XP_PMU_EVENT_SEL__ID__SHIFT(hw->config_base);
	ग_लिखोl(val, source->base + CCN_XP_PMU_EVENT_SEL);
पूर्ण

अटल व्योम arm_ccn_pmu_node_event_config(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा arm_ccn_component *source =
			ccn->dt.pmu_counters[hw->idx].source;
	u32 type = CCN_CONFIG_TYPE(event->attr.config);
	u32 val, port;

	port = arm_ccn_node_to_xp_port(CCN_CONFIG_NODE(event->attr.config));
	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT(port,
			hw->config_base);

	/* These *_event_sel regs should be identical, but let's make sure... */
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL != CCN_SBAS_PMU_EVENT_SEL);
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL != CCN_RNI_PMU_EVENT_SEL);
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(1) !=
			CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT(1));
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT(1) !=
			CCN_RNI_PMU_EVENT_SEL__ID__SHIFT(1));
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL__ID__MASK !=
			CCN_SBAS_PMU_EVENT_SEL__ID__MASK);
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL__ID__MASK !=
			CCN_RNI_PMU_EVENT_SEL__ID__MASK);
	अगर (WARN_ON(type != CCN_TYPE_HNF && type != CCN_TYPE_SBAS &&
			!arm_ccn_pmu_type_eq(type, CCN_TYPE_RNI_3P)))
		वापस;

	/* Set the event id क्रम the pre-allocated counter */
	val = पढ़ोl(source->base + CCN_HNF_PMU_EVENT_SEL);
	val &= ~(CCN_HNF_PMU_EVENT_SEL__ID__MASK <<
		CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(hw->config_base));
	val |= CCN_CONFIG_EVENT(event->attr.config) <<
		CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(hw->config_base);
	ग_लिखोl(val, source->base + CCN_HNF_PMU_EVENT_SEL);
पूर्ण

अटल व्योम arm_ccn_pmu_event_config(काष्ठा perf_event *event)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	काष्ठा hw_perf_event *hw = &event->hw;
	u32 xp, offset, val;

	/* Cycle counter requires no setup */
	अगर (hw->idx == CCN_IDX_PMU_CYCLE_COUNTER)
		वापस;

	अगर (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP)
		xp = CCN_CONFIG_XP(event->attr.config);
	अन्यथा
		xp = arm_ccn_node_to_xp(CCN_CONFIG_NODE(event->attr.config));

	spin_lock(&ccn->dt.config_lock);

	/* Set the DT bus "distance" रेजिस्टर */
	offset = (hw->idx / 4) * 4;
	val = पढ़ोl(ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);
	val &= ~(CCN_DT_ACTIVE_DSM__DSM_ID__MASK <<
			CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4));
	val |= xp << CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4);
	ग_लिखोl(val, ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);

	अगर (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP) अणु
		अगर (CCN_CONFIG_EVENT(event->attr.config) ==
				CCN_EVENT_WATCHPOINT)
			arm_ccn_pmu_xp_watchpoपूर्णांक_config(event);
		अन्यथा
			arm_ccn_pmu_xp_event_config(event);
	पूर्ण अन्यथा अणु
		arm_ccn_pmu_node_event_config(event);
	पूर्ण

	spin_unlock(&ccn->dt.config_lock);
पूर्ण

अटल पूर्णांक arm_ccn_pmu_active_counters(काष्ठा arm_ccn *ccn)
अणु
	वापस biपंचांगap_weight(ccn->dt.pmu_counters_mask,
			     CCN_NUM_PMU_EVENT_COUNTERS + 1);
पूर्ण

अटल पूर्णांक arm_ccn_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा hw_perf_event *hw = &event->hw;
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);

	err = arm_ccn_pmu_event_alloc(event);
	अगर (err)
		वापस err;

	/*
	 * Pin the समयr, so that the overflows are handled by the chosen
	 * event->cpu (this is the same one as presented in "cpumask"
	 * attribute).
	 */
	अगर (!ccn->irq && arm_ccn_pmu_active_counters(ccn) == 1)
		hrसमयr_start(&ccn->dt.hrसमयr, arm_ccn_pmu_समयr_period(),
			      HRTIMER_MODE_REL_PINNED);

	arm_ccn_pmu_event_config(event);

	hw->state = PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		arm_ccn_pmu_event_start(event, PERF_EF_UPDATE);

	वापस 0;
पूर्ण

अटल व्योम arm_ccn_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);

	arm_ccn_pmu_event_stop(event, PERF_EF_UPDATE);

	arm_ccn_pmu_event_release(event);

	अगर (!ccn->irq && arm_ccn_pmu_active_counters(ccn) == 0)
		hrसमयr_cancel(&ccn->dt.hrसमयr);
पूर्ण

अटल व्योम arm_ccn_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	arm_ccn_pmu_event_update(event);
पूर्ण

अटल व्योम arm_ccn_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(pmu);

	u32 val = पढ़ोl(ccn->dt.base + CCN_DT_PMCR);
	val |= CCN_DT_PMCR__PMU_EN;
	ग_लिखोl(val, ccn->dt.base + CCN_DT_PMCR);
पूर्ण

अटल व्योम arm_ccn_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा arm_ccn *ccn = pmu_to_arm_ccn(pmu);

	u32 val = पढ़ोl(ccn->dt.base + CCN_DT_PMCR);
	val &= ~CCN_DT_PMCR__PMU_EN;
	ग_लिखोl(val, ccn->dt.base + CCN_DT_PMCR);
पूर्ण

अटल irqवापस_t arm_ccn_pmu_overflow_handler(काष्ठा arm_ccn_dt *dt)
अणु
	u32 pmovsr = पढ़ोl(dt->base + CCN_DT_PMOVSR);
	पूर्णांक idx;

	अगर (!pmovsr)
		वापस IRQ_NONE;

	ग_लिखोl(pmovsr, dt->base + CCN_DT_PMOVSR_CLR);

	BUILD_BUG_ON(CCN_IDX_PMU_CYCLE_COUNTER != CCN_NUM_PMU_EVENT_COUNTERS);

	क्रम (idx = 0; idx < CCN_NUM_PMU_EVENT_COUNTERS + 1; idx++) अणु
		काष्ठा perf_event *event = dt->pmu_counters[idx].event;
		पूर्णांक overflowed = pmovsr & BIT(idx);

		WARN_ON_ONCE(overflowed && !event &&
				idx != CCN_IDX_PMU_CYCLE_COUNTER);

		अगर (!event || !overflowed)
			जारी;

		arm_ccn_pmu_event_update(event);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत hrसमयr_restart arm_ccn_pmu_समयr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा arm_ccn_dt *dt = container_of(hrसमयr, काष्ठा arm_ccn_dt,
			hrसमयr);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arm_ccn_pmu_overflow_handler(dt);
	local_irq_restore(flags);

	hrसमयr_क्रमward_now(hrसमयr, arm_ccn_pmu_समयr_period());
	वापस HRTIMER_RESTART;
पूर्ण


अटल पूर्णांक arm_ccn_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_ccn_dt *dt = hlist_entry_safe(node, काष्ठा arm_ccn_dt, node);
	काष्ठा arm_ccn *ccn = container_of(dt, काष्ठा arm_ccn, dt);
	अचिन्हित पूर्णांक target;

	अगर (cpu != dt->cpu)
		वापस 0;
	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;
	perf_pmu_migrate_context(&dt->pmu, cpu, target);
	dt->cpu = target;
	अगर (ccn->irq)
		WARN_ON(irq_set_affinity_hपूर्णांक(ccn->irq, cpumask_of(dt->cpu)));
	वापस 0;
पूर्ण

अटल DEFINE_IDA(arm_ccn_pmu_ida);

अटल पूर्णांक arm_ccn_pmu_init(काष्ठा arm_ccn *ccn)
अणु
	पूर्णांक i;
	अक्षर *name;
	पूर्णांक err;

	/* Initialize DT subप्रणाली */
	ccn->dt.base = ccn->base + CCN_REGION_SIZE;
	spin_lock_init(&ccn->dt.config_lock);
	ग_लिखोl(CCN_DT_PMOVSR_CLR__MASK, ccn->dt.base + CCN_DT_PMOVSR_CLR);
	ग_लिखोl(CCN_DT_CTL__DT_EN, ccn->dt.base + CCN_DT_CTL);
	ग_लिखोl(CCN_DT_PMCR__OVFL_INTR_EN | CCN_DT_PMCR__PMU_EN,
			ccn->dt.base + CCN_DT_PMCR);
	ग_लिखोl(0x1, ccn->dt.base + CCN_DT_PMSR_CLR);
	क्रम (i = 0; i < ccn->num_xps; i++) अणु
		ग_लिखोl(0, ccn->xp[i].base + CCN_XP_DT_CONFIG);
		ग_लिखोl((CCN_XP_DT_CONTROL__WP_ARM_SEL__ALWAYS <<
				CCN_XP_DT_CONTROL__WP_ARM_SEL__SHIFT(0)) |
				(CCN_XP_DT_CONTROL__WP_ARM_SEL__ALWAYS <<
				CCN_XP_DT_CONTROL__WP_ARM_SEL__SHIFT(1)) |
				CCN_XP_DT_CONTROL__DT_ENABLE,
				ccn->xp[i].base + CCN_XP_DT_CONTROL);
	पूर्ण
	ccn->dt.cmp_mask[CCN_IDX_MASK_ANY].l = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_ANY].h = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_EXACT].l = 0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_EXACT].h = 0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_ORDER].l = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_ORDER].h = ~(0x1 << 15);
	ccn->dt.cmp_mask[CCN_IDX_MASK_OPCODE].l = ~0;
	ccn->dt.cmp_mask[CCN_IDX_MASK_OPCODE].h = ~(0x1f << 9);

	/* Get a convenient /sys/event_source/devices/ name */
	ccn->dt.id = ida_simple_get(&arm_ccn_pmu_ida, 0, 0, GFP_KERNEL);
	अगर (ccn->dt.id == 0) अणु
		name = "ccn";
	पूर्ण अन्यथा अणु
		name = devm_kaप्र_लिखो(ccn->dev, GFP_KERNEL, "ccn_%d",
				      ccn->dt.id);
		अगर (!name) अणु
			err = -ENOMEM;
			जाओ error_choose_name;
		पूर्ण
	पूर्ण

	/* Perf driver registration */
	ccn->dt.pmu = (काष्ठा pmu) अणु
		.module = THIS_MODULE,
		.attr_groups = arm_ccn_pmu_attr_groups,
		.task_ctx_nr = perf_invalid_context,
		.event_init = arm_ccn_pmu_event_init,
		.add = arm_ccn_pmu_event_add,
		.del = arm_ccn_pmu_event_del,
		.start = arm_ccn_pmu_event_start,
		.stop = arm_ccn_pmu_event_stop,
		.पढ़ो = arm_ccn_pmu_event_पढ़ो,
		.pmu_enable = arm_ccn_pmu_enable,
		.pmu_disable = arm_ccn_pmu_disable,
		.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	/* No overflow पूर्णांकerrupt? Have to use a समयr instead. */
	अगर (!ccn->irq) अणु
		dev_info(ccn->dev, "No access to interrupts, using timer.\n");
		hrसमयr_init(&ccn->dt.hrसमयr, CLOCK_MONOTONIC,
				HRTIMER_MODE_REL);
		ccn->dt.hrसमयr.function = arm_ccn_pmu_समयr_handler;
	पूर्ण

	/* Pick one CPU which we will use to collect data from CCN... */
	ccn->dt.cpu = raw_smp_processor_id();

	/* Also make sure that the overflow पूर्णांकerrupt is handled by this CPU */
	अगर (ccn->irq) अणु
		err = irq_set_affinity_hपूर्णांक(ccn->irq, cpumask_of(ccn->dt.cpu));
		अगर (err) अणु
			dev_err(ccn->dev, "Failed to set interrupt affinity!\n");
			जाओ error_set_affinity;
		पूर्ण
	पूर्ण

	cpuhp_state_add_instance_nocalls(CPUHP_AP_PERF_ARM_CCN_ONLINE,
					 &ccn->dt.node);

	err = perf_pmu_रेजिस्टर(&ccn->dt.pmu, name, -1);
	अगर (err)
		जाओ error_pmu_रेजिस्टर;

	वापस 0;

error_pmu_रेजिस्टर:
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_CCN_ONLINE,
					    &ccn->dt.node);
error_set_affinity:
error_choose_name:
	ida_simple_हटाओ(&arm_ccn_pmu_ida, ccn->dt.id);
	क्रम (i = 0; i < ccn->num_xps; i++)
		ग_लिखोl(0, ccn->xp[i].base + CCN_XP_DT_CONTROL);
	ग_लिखोl(0, ccn->dt.base + CCN_DT_PMCR);
	वापस err;
पूर्ण

अटल व्योम arm_ccn_pmu_cleanup(काष्ठा arm_ccn *ccn)
अणु
	पूर्णांक i;

	cpuhp_state_हटाओ_instance_nocalls(CPUHP_AP_PERF_ARM_CCN_ONLINE,
					    &ccn->dt.node);
	अगर (ccn->irq)
		irq_set_affinity_hपूर्णांक(ccn->irq, शून्य);
	क्रम (i = 0; i < ccn->num_xps; i++)
		ग_लिखोl(0, ccn->xp[i].base + CCN_XP_DT_CONTROL);
	ग_लिखोl(0, ccn->dt.base + CCN_DT_PMCR);
	perf_pmu_unरेजिस्टर(&ccn->dt.pmu);
	ida_simple_हटाओ(&arm_ccn_pmu_ida, ccn->dt.id);
पूर्ण

अटल पूर्णांक arm_ccn_क्रम_each_valid_region(काष्ठा arm_ccn *ccn,
		पूर्णांक (*callback)(काष्ठा arm_ccn *ccn, पूर्णांक region,
		व्योम __iomem *base, u32 type, u32 id))
अणु
	पूर्णांक region;

	क्रम (region = 0; region < CCN_NUM_REGIONS; region++) अणु
		u32 val, type, id;
		व्योम __iomem *base;
		पूर्णांक err;

		val = पढ़ोl(ccn->base + CCN_MN_OLY_COMP_LIST_63_0 +
				4 * (region / 32));
		अगर (!(val & (1 << (region % 32))))
			जारी;

		base = ccn->base + region * CCN_REGION_SIZE;
		val = पढ़ोl(base + CCN_ALL_OLY_ID);
		type = (val >> CCN_ALL_OLY_ID__OLY_ID__SHIFT) &
				CCN_ALL_OLY_ID__OLY_ID__MASK;
		id = (val >> CCN_ALL_OLY_ID__NODE_ID__SHIFT) &
				CCN_ALL_OLY_ID__NODE_ID__MASK;

		err = callback(ccn, region, base, type, id);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_ccn_get_nodes_num(काष्ठा arm_ccn *ccn, पूर्णांक region,
		व्योम __iomem *base, u32 type, u32 id)
अणु

	अगर (type == CCN_TYPE_XP && id >= ccn->num_xps)
		ccn->num_xps = id + 1;
	अन्यथा अगर (id >= ccn->num_nodes)
		ccn->num_nodes = id + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक arm_ccn_init_nodes(काष्ठा arm_ccn *ccn, पूर्णांक region,
		व्योम __iomem *base, u32 type, u32 id)
अणु
	काष्ठा arm_ccn_component *component;

	dev_dbg(ccn->dev, "Region %d: id=%u, type=0x%02x\n", region, id, type);

	चयन (type) अणु
	हाल CCN_TYPE_MN:
		ccn->mn_id = id;
		वापस 0;
	हाल CCN_TYPE_DT:
		वापस 0;
	हाल CCN_TYPE_XP:
		component = &ccn->xp[id];
		अवरोध;
	हाल CCN_TYPE_SBSX:
		ccn->sbsx_present = 1;
		component = &ccn->node[id];
		अवरोध;
	हाल CCN_TYPE_SBAS:
		ccn->sbas_present = 1;
		fallthrough;
	शेष:
		component = &ccn->node[id];
		अवरोध;
	पूर्ण

	component->base = base;
	component->type = type;

	वापस 0;
पूर्ण


अटल irqवापस_t arm_ccn_error_handler(काष्ठा arm_ccn *ccn,
		स्थिर u32 *err_sig_val)
अणु
	/* This should be really handled by firmware... */
	dev_err(ccn->dev, "Error reported in %08x%08x%08x%08x%08x%08x.\n",
			err_sig_val[5], err_sig_val[4], err_sig_val[3],
			err_sig_val[2], err_sig_val[1], err_sig_val[0]);
	dev_err(ccn->dev, "Disabling interrupt generation for all errors.\n");
	ग_लिखोl(CCN_MN_ERRINT_STATUS__ALL_ERRORS__DISABLE,
			ccn->base + CCN_MN_ERRINT_STATUS);

	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t arm_ccn_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t res = IRQ_NONE;
	काष्ठा arm_ccn *ccn = dev_id;
	u32 err_sig_val[6];
	u32 err_or;
	पूर्णांक i;

	/* PMU overflow is a special हाल */
	err_or = err_sig_val[0] = पढ़ोl(ccn->base + CCN_MN_ERR_SIG_VAL_63_0);
	अगर (err_or & CCN_MN_ERR_SIG_VAL_63_0__DT) अणु
		err_or &= ~CCN_MN_ERR_SIG_VAL_63_0__DT;
		res = arm_ccn_pmu_overflow_handler(&ccn->dt);
	पूर्ण

	/* Have to पढ़ो all err_sig_vals to clear them */
	क्रम (i = 1; i < ARRAY_SIZE(err_sig_val); i++) अणु
		err_sig_val[i] = पढ़ोl(ccn->base +
				CCN_MN_ERR_SIG_VAL_63_0 + i * 4);
		err_or |= err_sig_val[i];
	पूर्ण
	अगर (err_or)
		res |= arm_ccn_error_handler(ccn, err_sig_val);

	अगर (res != IRQ_NONE)
		ग_लिखोl(CCN_MN_ERRINT_STATUS__INTREQ__DESSERT,
				ccn->base + CCN_MN_ERRINT_STATUS);

	वापस res;
पूर्ण


अटल पूर्णांक arm_ccn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_ccn *ccn;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक irq;
	पूर्णांक err;

	ccn = devm_kzalloc(&pdev->dev, माप(*ccn), GFP_KERNEL);
	अगर (!ccn)
		वापस -ENOMEM;
	ccn->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, ccn);

	ccn->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ccn->base))
		वापस PTR_ERR(ccn->base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res)
		वापस -EINVAL;
	irq = res->start;

	/* Check अगर we can use the पूर्णांकerrupt */
	ग_लिखोl(CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLE,
			ccn->base + CCN_MN_ERRINT_STATUS);
	अगर (पढ़ोl(ccn->base + CCN_MN_ERRINT_STATUS) &
			CCN_MN_ERRINT_STATUS__PMU_EVENTS__DISABLED) अणु
		/* Can set 'disable' bits, so can acknowledge पूर्णांकerrupts */
		ग_लिखोl(CCN_MN_ERRINT_STATUS__PMU_EVENTS__ENABLE,
				ccn->base + CCN_MN_ERRINT_STATUS);
		err = devm_request_irq(ccn->dev, irq, arm_ccn_irq_handler,
				       IRQF_NOBALANCING | IRQF_NO_THREAD,
				       dev_name(ccn->dev), ccn);
		अगर (err)
			वापस err;

		ccn->irq = irq;
	पूर्ण


	/* Build topology */

	err = arm_ccn_क्रम_each_valid_region(ccn, arm_ccn_get_nodes_num);
	अगर (err)
		वापस err;

	ccn->node = devm_kसुस्मृति(ccn->dev, ccn->num_nodes, माप(*ccn->node),
				 GFP_KERNEL);
	ccn->xp = devm_kसुस्मृति(ccn->dev, ccn->num_xps, माप(*ccn->node),
			       GFP_KERNEL);
	अगर (!ccn->node || !ccn->xp)
		वापस -ENOMEM;

	err = arm_ccn_क्रम_each_valid_region(ccn, arm_ccn_init_nodes);
	अगर (err)
		वापस err;

	वापस arm_ccn_pmu_init(ccn);
पूर्ण

अटल पूर्णांक arm_ccn_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_ccn *ccn = platक्रमm_get_drvdata(pdev);

	arm_ccn_pmu_cleanup(ccn);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arm_ccn_match[] = अणु
	अणु .compatible = "arm,ccn-502", पूर्ण,
	अणु .compatible = "arm,ccn-504", पूर्ण,
	अणु .compatible = "arm,ccn-512", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_ccn_match);

अटल काष्ठा platक्रमm_driver arm_ccn_driver = अणु
	.driver = अणु
		.name = "arm-ccn",
		.of_match_table = arm_ccn_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = arm_ccn_probe,
	.हटाओ = arm_ccn_हटाओ,
पूर्ण;

अटल पूर्णांक __init arm_ccn_init(व्योम)
अणु
	पूर्णांक i, ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_CCN_ONLINE,
				      "perf/arm/ccn:online", शून्य,
				      arm_ccn_pmu_offline_cpu);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(arm_ccn_pmu_events); i++)
		arm_ccn_pmu_events_attrs[i] = &arm_ccn_pmu_events[i].attr.attr;

	ret = platक्रमm_driver_रेजिस्टर(&arm_ccn_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_CCN_ONLINE);
	वापस ret;
पूर्ण

अटल व्योम __निकास arm_ccn_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arm_ccn_driver);
	cpuhp_हटाओ_multi_state(CPUHP_AP_PERF_ARM_CCN_ONLINE);
पूर्ण

module_init(arm_ccn_init);
module_निकास(arm_ccn_निकास);

MODULE_AUTHOR("Pawel Moll <pawel.moll@arm.com>");
MODULE_LICENSE("GPL v2");
