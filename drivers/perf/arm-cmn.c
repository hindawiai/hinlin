<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2016-2020 Arm Limited
// CMN-600 Coherent Mesh Network PMU driver

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

/* Common रेजिस्टर stuff */
#घोषणा CMN_NODE_INFO			0x0000
#घोषणा CMN_NI_NODE_TYPE		GENMASK_ULL(15, 0)
#घोषणा CMN_NI_NODE_ID			GENMASK_ULL(31, 16)
#घोषणा CMN_NI_LOGICAL_ID		GENMASK_ULL(47, 32)

#घोषणा CMN_NODEID_DEVID(reg)		((reg) & 3)
#घोषणा CMN_NODEID_PID(reg)		(((reg) >> 2) & 1)
#घोषणा CMN_NODEID_X(reg, bits)		((reg) >> (3 + (bits)))
#घोषणा CMN_NODEID_Y(reg, bits)		(((reg) >> 3) & ((1U << (bits)) - 1))

#घोषणा CMN_CHILD_INFO			0x0080
#घोषणा CMN_CI_CHILD_COUNT		GENMASK_ULL(15, 0)
#घोषणा CMN_CI_CHILD_PTR_OFFSET		GENMASK_ULL(31, 16)

#घोषणा CMN_CHILD_NODE_ADDR		GENMASK(27,0)
#घोषणा CMN_CHILD_NODE_EXTERNAL		BIT(31)

#घोषणा CMN_ADDR_NODE_PTR		GENMASK(27, 14)

#घोषणा CMN_NODE_PTR_DEVID(ptr)		(((ptr) >> 2) & 3)
#घोषणा CMN_NODE_PTR_PID(ptr)		((ptr) & 1)
#घोषणा CMN_NODE_PTR_X(ptr, bits)	((ptr) >> (6 + (bits)))
#घोषणा CMN_NODE_PTR_Y(ptr, bits)	(((ptr) >> 6) & ((1U << (bits)) - 1))

#घोषणा CMN_MAX_XPS			(8 * 8)

/* The CFG node has one other useful purpose */
#घोषणा CMN_CFGM_PERIPH_ID_2		0x0010
#घोषणा CMN_CFGM_PID2_REVISION		GENMASK(7, 4)

/* PMU रेजिस्टरs occupy the 3rd 4KB page of each node's 16KB space */
#घोषणा CMN_PMU_OFFSET			0x2000

/* For most nodes, this is all there is */
#घोषणा CMN_PMU_EVENT_SEL		0x000
#घोषणा CMN_PMU_EVENTn_ID_SHIFT(n)	((n) * 8)

/* DTMs live in the PMU space of XP रेजिस्टरs */
#घोषणा CMN_DTM_WPn(n)			(0x1A0 + (n) * 0x18)
#घोषणा CMN_DTM_WPn_CONFIG(n)		(CMN_DTM_WPn(n) + 0x00)
#घोषणा CMN_DTM_WPn_CONFIG_WP_COMBINE	BIT(6)
#घोषणा CMN_DTM_WPn_CONFIG_WP_EXCLUSIVE	BIT(5)
#घोषणा CMN_DTM_WPn_CONFIG_WP_GRP	BIT(4)
#घोषणा CMN_DTM_WPn_CONFIG_WP_CHN_SEL	GENMASK_ULL(3, 1)
#घोषणा CMN_DTM_WPn_CONFIG_WP_DEV_SEL	BIT(0)
#घोषणा CMN_DTM_WPn_VAL(n)		(CMN_DTM_WPn(n) + 0x08)
#घोषणा CMN_DTM_WPn_MASK(n)		(CMN_DTM_WPn(n) + 0x10)

#घोषणा CMN_DTM_PMU_CONFIG		0x210
#घोषणा CMN__PMEVCNT0_INPUT_SEL		GENMASK_ULL(37, 32)
#घोषणा CMN__PMEVCNT0_INPUT_SEL_WP	0x00
#घोषणा CMN__PMEVCNT0_INPUT_SEL_XP	0x04
#घोषणा CMN__PMEVCNT0_INPUT_SEL_DEV	0x10
#घोषणा CMN__PMEVCNT0_GLOBAL_NUM	GENMASK_ULL(18, 16)
#घोषणा CMN__PMEVCNTn_GLOBAL_NUM_SHIFT(n)	((n) * 4)
#घोषणा CMN__PMEVCNT_PAIRED(n)		BIT(4 + (n))
#घोषणा CMN__PMEVCNT23_COMBINED		BIT(2)
#घोषणा CMN__PMEVCNT01_COMBINED		BIT(1)
#घोषणा CMN_DTM_PMU_CONFIG_PMU_EN	BIT(0)

#घोषणा CMN_DTM_PMEVCNT			0x220

#घोषणा CMN_DTM_PMEVCNTSR		0x240

#घोषणा CMN_DTM_NUM_COUNTERS		4

/* The DTC node is where the magic happens */
#घोषणा CMN_DT_DTC_CTL			0x0a00
#घोषणा CMN_DT_DTC_CTL_DT_EN		BIT(0)

/* DTC counters are paired in 64-bit रेजिस्टरs on a 16-byte stride. Yuck */
#घोषणा _CMN_DT_CNT_REG(n)		((((n) / 2) * 4 + (n) % 2) * 4)
#घोषणा CMN_DT_PMEVCNT(n)		(CMN_PMU_OFFSET + _CMN_DT_CNT_REG(n))
#घोषणा CMN_DT_PMCCNTR			(CMN_PMU_OFFSET + 0x40)

#घोषणा CMN_DT_PMEVCNTSR(n)		(CMN_PMU_OFFSET + 0x50 + _CMN_DT_CNT_REG(n))
#घोषणा CMN_DT_PMCCNTRSR		(CMN_PMU_OFFSET + 0x90)

#घोषणा CMN_DT_PMCR			(CMN_PMU_OFFSET + 0x100)
#घोषणा CMN_DT_PMCR_PMU_EN		BIT(0)
#घोषणा CMN_DT_PMCR_CNTR_RST		BIT(5)
#घोषणा CMN_DT_PMCR_OVFL_INTR_EN	BIT(6)

#घोषणा CMN_DT_PMOVSR			(CMN_PMU_OFFSET + 0x118)
#घोषणा CMN_DT_PMOVSR_CLR		(CMN_PMU_OFFSET + 0x120)

#घोषणा CMN_DT_PMSSR			(CMN_PMU_OFFSET + 0x128)
#घोषणा CMN_DT_PMSSR_SS_STATUS(n)	BIT(n)

#घोषणा CMN_DT_PMSRR			(CMN_PMU_OFFSET + 0x130)
#घोषणा CMN_DT_PMSRR_SS_REQ		BIT(0)

#घोषणा CMN_DT_NUM_COUNTERS		8
#घोषणा CMN_MAX_DTCS			4

/*
 * Even in the worst हाल a DTC counter can't wrap in fewer than 2^42 cycles,
 * so throwing away one bit to make overflow handling easy is no big deal.
 */
#घोषणा CMN_COUNTER_INIT		0x80000000
/* Similarly क्रम the 40-bit cycle counter */
#घोषणा CMN_CC_INIT			0x8000000000ULL


/* Event attributes */
#घोषणा CMN_CONFIG_TYPE			GENMASK(15, 0)
#घोषणा CMN_CONFIG_EVENTID		GENMASK(23, 16)
#घोषणा CMN_CONFIG_OCCUPID		GENMASK(27, 24)
#घोषणा CMN_CONFIG_BYNODEID		BIT(31)
#घोषणा CMN_CONFIG_NODEID		GENMASK(47, 32)

#घोषणा CMN_EVENT_TYPE(event)		FIELD_GET(CMN_CONFIG_TYPE, (event)->attr.config)
#घोषणा CMN_EVENT_EVENTID(event)	FIELD_GET(CMN_CONFIG_EVENTID, (event)->attr.config)
#घोषणा CMN_EVENT_OCCUPID(event)	FIELD_GET(CMN_CONFIG_OCCUPID, (event)->attr.config)
#घोषणा CMN_EVENT_BYNODEID(event)	FIELD_GET(CMN_CONFIG_BYNODEID, (event)->attr.config)
#घोषणा CMN_EVENT_NODEID(event)		FIELD_GET(CMN_CONFIG_NODEID, (event)->attr.config)

#घोषणा CMN_CONFIG_WP_COMBINE		GENMASK(27, 24)
#घोषणा CMN_CONFIG_WP_DEV_SEL		BIT(48)
#घोषणा CMN_CONFIG_WP_CHN_SEL		GENMASK(50, 49)
#घोषणा CMN_CONFIG_WP_GRP		BIT(52)
#घोषणा CMN_CONFIG_WP_EXCLUSIVE		BIT(53)
#घोषणा CMN_CONFIG1_WP_VAL		GENMASK(63, 0)
#घोषणा CMN_CONFIG2_WP_MASK		GENMASK(63, 0)

#घोषणा CMN_EVENT_WP_COMBINE(event)	FIELD_GET(CMN_CONFIG_WP_COMBINE, (event)->attr.config)
#घोषणा CMN_EVENT_WP_DEV_SEL(event)	FIELD_GET(CMN_CONFIG_WP_DEV_SEL, (event)->attr.config)
#घोषणा CMN_EVENT_WP_CHN_SEL(event)	FIELD_GET(CMN_CONFIG_WP_CHN_SEL, (event)->attr.config)
#घोषणा CMN_EVENT_WP_GRP(event)		FIELD_GET(CMN_CONFIG_WP_GRP, (event)->attr.config)
#घोषणा CMN_EVENT_WP_EXCLUSIVE(event)	FIELD_GET(CMN_CONFIG_WP_EXCLUSIVE, (event)->attr.config)
#घोषणा CMN_EVENT_WP_VAL(event)		FIELD_GET(CMN_CONFIG1_WP_VAL, (event)->attr.config1)
#घोषणा CMN_EVENT_WP_MASK(event)	FIELD_GET(CMN_CONFIG2_WP_MASK, (event)->attr.config2)

/* Made-up event IDs क्रम watchpoपूर्णांक direction */
#घोषणा CMN_WP_UP			0
#घोषणा CMN_WP_DOWN			2


/* r0px probably करोn't exist in silicon, thankfully */
क्रमागत cmn_revision अणु
	CMN600_R1P0,
	CMN600_R1P1,
	CMN600_R1P2,
	CMN600_R1P3,
	CMN600_R2P0,
	CMN600_R3P0,
पूर्ण;

क्रमागत cmn_node_type अणु
	CMN_TYPE_INVALID,
	CMN_TYPE_DVM,
	CMN_TYPE_CFG,
	CMN_TYPE_DTC,
	CMN_TYPE_HNI,
	CMN_TYPE_HNF,
	CMN_TYPE_XP,
	CMN_TYPE_SBSX,
	CMN_TYPE_RNI = 0xa,
	CMN_TYPE_RND = 0xd,
	CMN_TYPE_RNSAM = 0xf,
	CMN_TYPE_CXRA = 0x100,
	CMN_TYPE_CXHA = 0x101,
	CMN_TYPE_CXLA = 0x102,
	/* Not a real node type */
	CMN_TYPE_WP = 0x7770
पूर्ण;

काष्ठा arm_cmn_node अणु
	व्योम __iomem *pmu_base;
	u16 id, logid;
	क्रमागत cmn_node_type type;

	जोड़ अणु
		/* Device node */
		काष्ठा अणु
			पूर्णांक to_xp;
			/* DN/HN-F/CXHA */
			अचिन्हित पूर्णांक occupid_val;
			अचिन्हित पूर्णांक occupid_count;
		पूर्ण;
		/* XP */
		काष्ठा अणु
			पूर्णांक dtc;
			u32 pmu_config_low;
			जोड़ अणु
				u8 input_sel[4];
				__le32 pmu_config_high;
			पूर्ण;
			s8 wp_event[4];
		पूर्ण;
	पूर्ण;

	जोड़ अणु
		u8 event[4];
		__le32 event_sel;
	पूर्ण;
पूर्ण;

काष्ठा arm_cmn_dtc अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक irq_मित्र;
	bool cc_active;

	काष्ठा perf_event *counters[CMN_DT_NUM_COUNTERS];
	काष्ठा perf_event *cycles;
पूर्ण;

#घोषणा CMN_STATE_DISABLED	BIT(0)
#घोषणा CMN_STATE_TXN		BIT(1)

काष्ठा arm_cmn अणु
	काष्ठा device *dev;
	व्योम __iomem *base;

	क्रमागत cmn_revision rev;
	u8 mesh_x;
	u8 mesh_y;
	u16 num_xps;
	u16 num_dns;
	काष्ठा arm_cmn_node *xps;
	काष्ठा arm_cmn_node *dns;

	काष्ठा arm_cmn_dtc *dtc;
	अचिन्हित पूर्णांक num_dtcs;

	पूर्णांक cpu;
	काष्ठा hlist_node cpuhp_node;

	अचिन्हित पूर्णांक state;
	काष्ठा pmu pmu;
पूर्ण;

#घोषणा to_cmn(p)	container_of(p, काष्ठा arm_cmn, pmu)

अटल पूर्णांक arm_cmn_hp_state;

काष्ठा arm_cmn_hw_event अणु
	काष्ठा arm_cmn_node *dn;
	u64 dपंचांग_idx[2];
	अचिन्हित पूर्णांक dtc_idx;
	u8 dtcs_used;
	u8 num_dns;
पूर्ण;

#घोषणा क्रम_each_hw_dn(hw, dn, i) \
	क्रम (i = 0, dn = hw->dn; i < hw->num_dns; i++, dn++)

अटल काष्ठा arm_cmn_hw_event *to_cmn_hw(काष्ठा perf_event *event)
अणु
	BUILD_BUG_ON(माप(काष्ठा arm_cmn_hw_event) > दुरत्व(काष्ठा hw_perf_event, target));
	वापस (काष्ठा arm_cmn_hw_event *)&event->hw;
पूर्ण

अटल व्योम arm_cmn_set_index(u64 x[], अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक val)
अणु
	x[pos / 32] |= (u64)val << ((pos % 32) * 2);
पूर्ण

अटल अचिन्हित पूर्णांक arm_cmn_get_index(u64 x[], अचिन्हित पूर्णांक pos)
अणु
	वापस (x[pos / 32] >> ((pos % 32) * 2)) & 3;
पूर्ण

काष्ठा arm_cmn_event_attr अणु
	काष्ठा device_attribute attr;
	क्रमागत cmn_node_type type;
	u8 eventid;
	u8 occupid;
पूर्ण;

काष्ठा arm_cmn_क्रमmat_attr अणु
	काष्ठा device_attribute attr;
	u64 field;
	पूर्णांक config;
पूर्ण;

अटल पूर्णांक arm_cmn_xyidbits(स्थिर काष्ठा arm_cmn *cmn)
अणु
	वापस cmn->mesh_x > 4 || cmn->mesh_y > 4 ? 3 : 2;
पूर्ण

अटल व्योम arm_cmn_init_node_to_xp(स्थिर काष्ठा arm_cmn *cmn,
				    काष्ठा arm_cmn_node *dn)
अणु
	पूर्णांक bits = arm_cmn_xyidbits(cmn);
	पूर्णांक x = CMN_NODEID_X(dn->id, bits);
	पूर्णांक y = CMN_NODEID_Y(dn->id, bits);
	पूर्णांक xp_idx = cmn->mesh_x * y + x;

	dn->to_xp = (cmn->xps + xp_idx) - dn;
पूर्ण

अटल काष्ठा arm_cmn_node *arm_cmn_node_to_xp(काष्ठा arm_cmn_node *dn)
अणु
	वापस dn->type == CMN_TYPE_XP ? dn : dn + dn->to_xp;
पूर्ण

अटल काष्ठा arm_cmn_node *arm_cmn_node(स्थिर काष्ठा arm_cmn *cmn,
					 क्रमागत cmn_node_type type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmn->num_dns; i++)
		अगर (cmn->dns[i].type == type)
			वापस &cmn->dns[i];
	वापस शून्य;
पूर्ण

#घोषणा CMN_EVENT_ATTR(_name, _type, _eventid, _occupid)		\
	(&((काष्ठा arm_cmn_event_attr[]) अणुअणु				\
		.attr = __ATTR(_name, 0444, arm_cmn_event_show, शून्य),	\
		.type = _type,						\
		.eventid = _eventid,					\
		.occupid = _occupid,					\
	पूर्णपूर्ण)[0].attr.attr)

अटल bool arm_cmn_is_occup_event(क्रमागत cmn_node_type type, अचिन्हित पूर्णांक id)
अणु
	वापस (type == CMN_TYPE_DVM && id == 0x05) ||
	       (type == CMN_TYPE_HNF && id == 0x0f);
पूर्ण

अटल sमाप_प्रकार arm_cmn_event_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_cmn_event_attr *eattr;

	eattr = container_of(attr, typeof(*eattr), attr);

	अगर (eattr->type == CMN_TYPE_DTC)
		वापस sysfs_emit(buf, "type=0x%x\n", eattr->type);

	अगर (eattr->type == CMN_TYPE_WP)
		वापस sysfs_emit(buf,
				  "type=0x%x,eventid=0x%x,wp_dev_sel=?,wp_chn_sel=?,wp_grp=?,wp_val=?,wp_mask=?\n",
				  eattr->type, eattr->eventid);

	अगर (arm_cmn_is_occup_event(eattr->type, eattr->eventid))
		वापस sysfs_emit(buf, "type=0x%x,eventid=0x%x,occupid=0x%x\n",
				  eattr->type, eattr->eventid, eattr->occupid);

	वापस sysfs_emit(buf, "type=0x%x,eventid=0x%x\n", eattr->type,
			  eattr->eventid);
पूर्ण

अटल umode_t arm_cmn_event_attr_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *attr,
					     पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा arm_cmn *cmn = to_cmn(dev_get_drvdata(dev));
	काष्ठा arm_cmn_event_attr *eattr;
	क्रमागत cmn_node_type type;

	eattr = container_of(attr, typeof(*eattr), attr.attr);
	type = eattr->type;

	/* Watchpoपूर्णांकs aren't nodes */
	अगर (type == CMN_TYPE_WP)
		type = CMN_TYPE_XP;

	/* Revision-specअगरic dअगरferences */
	अगर (cmn->rev < CMN600_R1P2) अणु
		अगर (type == CMN_TYPE_HNF && eattr->eventid == 0x1b)
			वापस 0;
	पूर्ण

	अगर (!arm_cmn_node(cmn, type))
		वापस 0;

	वापस attr->mode;
पूर्ण

#घोषणा _CMN_EVENT_DVM(_name, _event, _occup)			\
	CMN_EVENT_ATTR(dn_##_name, CMN_TYPE_DVM, _event, _occup)
#घोषणा CMN_EVENT_DTC(_name)					\
	CMN_EVENT_ATTR(dtc_##_name, CMN_TYPE_DTC, 0, 0)
#घोषणा _CMN_EVENT_HNF(_name, _event, _occup)			\
	CMN_EVENT_ATTR(hnf_##_name, CMN_TYPE_HNF, _event, _occup)
#घोषणा CMN_EVENT_HNI(_name, _event)				\
	CMN_EVENT_ATTR(hni_##_name, CMN_TYPE_HNI, _event, 0)
#घोषणा __CMN_EVENT_XP(_name, _event)				\
	CMN_EVENT_ATTR(mxp_##_name, CMN_TYPE_XP, _event, 0)
#घोषणा CMN_EVENT_SBSX(_name, _event)				\
	CMN_EVENT_ATTR(sbsx_##_name, CMN_TYPE_SBSX, _event, 0)
#घोषणा CMN_EVENT_RNID(_name, _event)				\
	CMN_EVENT_ATTR(rnid_##_name, CMN_TYPE_RNI, _event, 0)

#घोषणा CMN_EVENT_DVM(_name, _event)				\
	_CMN_EVENT_DVM(_name, _event, 0)
#घोषणा CMN_EVENT_HNF(_name, _event)				\
	_CMN_EVENT_HNF(_name, _event, 0)
#घोषणा _CMN_EVENT_XP(_name, _event)				\
	__CMN_EVENT_XP(e_##_name, (_event) | (0 << 2)),		\
	__CMN_EVENT_XP(w_##_name, (_event) | (1 << 2)),		\
	__CMN_EVENT_XP(n_##_name, (_event) | (2 << 2)),		\
	__CMN_EVENT_XP(s_##_name, (_event) | (3 << 2)),		\
	__CMN_EVENT_XP(p0_##_name, (_event) | (4 << 2)),	\
	__CMN_EVENT_XP(p1_##_name, (_event) | (5 << 2))

/* Good thing there are only 3 fundamental XP events... */
#घोषणा CMN_EVENT_XP(_name, _event)				\
	_CMN_EVENT_XP(req_##_name, (_event) | (0 << 5)),	\
	_CMN_EVENT_XP(rsp_##_name, (_event) | (1 << 5)),	\
	_CMN_EVENT_XP(snp_##_name, (_event) | (2 << 5)),	\
	_CMN_EVENT_XP(dat_##_name, (_event) | (3 << 5))


अटल काष्ठा attribute *arm_cmn_event_attrs[] = अणु
	CMN_EVENT_DTC(cycles),

	/*
	 * DVM node events conflict with HN-I events in the equivalent PMU
	 * slot, but our lazy लघु-cut of using the DTM counter index क्रम
	 * the PMU index as well happens to aव्योम that by स्थिरruction.
	 */
	CMN_EVENT_DVM(rxreq_dvmop,	0x01),
	CMN_EVENT_DVM(rxreq_dvmsync,	0x02),
	CMN_EVENT_DVM(rxreq_dvmop_vmid_filtered, 0x03),
	CMN_EVENT_DVM(rxreq_retried,	0x04),
	_CMN_EVENT_DVM(rxreq_trk_occupancy_all, 0x05, 0),
	_CMN_EVENT_DVM(rxreq_trk_occupancy_dvmop, 0x05, 1),
	_CMN_EVENT_DVM(rxreq_trk_occupancy_dvmsync, 0x05, 2),

	CMN_EVENT_HNF(cache_miss,	0x01),
	CMN_EVENT_HNF(slc_sf_cache_access, 0x02),
	CMN_EVENT_HNF(cache_fill,	0x03),
	CMN_EVENT_HNF(pocq_retry,	0x04),
	CMN_EVENT_HNF(pocq_reqs_recvd,	0x05),
	CMN_EVENT_HNF(sf_hit,		0x06),
	CMN_EVENT_HNF(sf_evictions,	0x07),
	CMN_EVENT_HNF(dir_snoops_sent,	0x08),
	CMN_EVENT_HNF(brd_snoops_sent,	0x09),
	CMN_EVENT_HNF(slc_eviction,	0x0a),
	CMN_EVENT_HNF(slc_fill_invalid_way, 0x0b),
	CMN_EVENT_HNF(mc_retries,	0x0c),
	CMN_EVENT_HNF(mc_reqs,		0x0d),
	CMN_EVENT_HNF(qos_hh_retry,	0x0e),
	_CMN_EVENT_HNF(qos_pocq_occupancy_all, 0x0f, 0),
	_CMN_EVENT_HNF(qos_pocq_occupancy_पढ़ो, 0x0f, 1),
	_CMN_EVENT_HNF(qos_pocq_occupancy_ग_लिखो, 0x0f, 2),
	_CMN_EVENT_HNF(qos_pocq_occupancy_atomic, 0x0f, 3),
	_CMN_EVENT_HNF(qos_pocq_occupancy_stash, 0x0f, 4),
	CMN_EVENT_HNF(pocq_addrhaz,	0x10),
	CMN_EVENT_HNF(pocq_atomic_addrhaz, 0x11),
	CMN_EVENT_HNF(ld_st_swp_adq_full, 0x12),
	CMN_EVENT_HNF(cmp_adq_full,	0x13),
	CMN_EVENT_HNF(txdat_stall,	0x14),
	CMN_EVENT_HNF(txrsp_stall,	0x15),
	CMN_EVENT_HNF(seq_full,		0x16),
	CMN_EVENT_HNF(seq_hit,		0x17),
	CMN_EVENT_HNF(snp_sent,		0x18),
	CMN_EVENT_HNF(sfbi_dir_snp_sent, 0x19),
	CMN_EVENT_HNF(sfbi_brd_snp_sent, 0x1a),
	CMN_EVENT_HNF(snp_sent_untrk,	0x1b),
	CMN_EVENT_HNF(पूर्णांकv_dirty,	0x1c),
	CMN_EVENT_HNF(stash_snp_sent,	0x1d),
	CMN_EVENT_HNF(stash_data_pull,	0x1e),
	CMN_EVENT_HNF(snp_fwded,	0x1f),

	CMN_EVENT_HNI(rrt_rd_occ_cnt_ovfl, 0x20),
	CMN_EVENT_HNI(rrt_wr_occ_cnt_ovfl, 0x21),
	CMN_EVENT_HNI(rdt_rd_occ_cnt_ovfl, 0x22),
	CMN_EVENT_HNI(rdt_wr_occ_cnt_ovfl, 0x23),
	CMN_EVENT_HNI(wdb_occ_cnt_ovfl,	0x24),
	CMN_EVENT_HNI(rrt_rd_alloc,	0x25),
	CMN_EVENT_HNI(rrt_wr_alloc,	0x26),
	CMN_EVENT_HNI(rdt_rd_alloc,	0x27),
	CMN_EVENT_HNI(rdt_wr_alloc,	0x28),
	CMN_EVENT_HNI(wdb_alloc,	0x29),
	CMN_EVENT_HNI(txrsp_retryack,	0x2a),
	CMN_EVENT_HNI(arvalid_no_arपढ़ोy, 0x2b),
	CMN_EVENT_HNI(arपढ़ोy_no_arvalid, 0x2c),
	CMN_EVENT_HNI(awvalid_no_awपढ़ोy, 0x2d),
	CMN_EVENT_HNI(awपढ़ोy_no_awvalid, 0x2e),
	CMN_EVENT_HNI(wvalid_no_wपढ़ोy,	0x2f),
	CMN_EVENT_HNI(txdat_stall,	0x30),
	CMN_EVENT_HNI(nonpcie_serialization, 0x31),
	CMN_EVENT_HNI(pcie_serialization, 0x32),

	CMN_EVENT_XP(txflit_valid,	0x01),
	CMN_EVENT_XP(txflit_stall,	0x02),
	CMN_EVENT_XP(partial_dat_flit,	0x03),
	/* We treat watchpoपूर्णांकs as a special made-up class of XP events */
	CMN_EVENT_ATTR(watchpoपूर्णांक_up, CMN_TYPE_WP, 0, 0),
	CMN_EVENT_ATTR(watchpoपूर्णांक_करोwn, CMN_TYPE_WP, 2, 0),

	CMN_EVENT_SBSX(rd_req,		0x01),
	CMN_EVENT_SBSX(wr_req,		0x02),
	CMN_EVENT_SBSX(cmo_req,		0x03),
	CMN_EVENT_SBSX(txrsp_retryack,	0x04),
	CMN_EVENT_SBSX(txdat_flitv,	0x05),
	CMN_EVENT_SBSX(txrsp_flitv,	0x06),
	CMN_EVENT_SBSX(rd_req_trkr_occ_cnt_ovfl, 0x11),
	CMN_EVENT_SBSX(wr_req_trkr_occ_cnt_ovfl, 0x12),
	CMN_EVENT_SBSX(cmo_req_trkr_occ_cnt_ovfl, 0x13),
	CMN_EVENT_SBSX(wdb_occ_cnt_ovfl, 0x14),
	CMN_EVENT_SBSX(rd_axi_trkr_occ_cnt_ovfl, 0x15),
	CMN_EVENT_SBSX(cmo_axi_trkr_occ_cnt_ovfl, 0x16),
	CMN_EVENT_SBSX(arvalid_no_arपढ़ोy, 0x21),
	CMN_EVENT_SBSX(awvalid_no_awपढ़ोy, 0x22),
	CMN_EVENT_SBSX(wvalid_no_wपढ़ोy, 0x23),
	CMN_EVENT_SBSX(txdat_stall,	0x24),
	CMN_EVENT_SBSX(txrsp_stall,	0x25),

	CMN_EVENT_RNID(s0_rdata_beats,	0x01),
	CMN_EVENT_RNID(s1_rdata_beats,	0x02),
	CMN_EVENT_RNID(s2_rdata_beats,	0x03),
	CMN_EVENT_RNID(rxdat_flits,	0x04),
	CMN_EVENT_RNID(txdat_flits,	0x05),
	CMN_EVENT_RNID(txreq_flits_total, 0x06),
	CMN_EVENT_RNID(txreq_flits_retried, 0x07),
	CMN_EVENT_RNID(rrt_occ_ovfl,	0x08),
	CMN_EVENT_RNID(wrt_occ_ovfl,	0x09),
	CMN_EVENT_RNID(txreq_flits_replayed, 0x0a),
	CMN_EVENT_RNID(wrcancel_sent,	0x0b),
	CMN_EVENT_RNID(s0_wdata_beats,	0x0c),
	CMN_EVENT_RNID(s1_wdata_beats,	0x0d),
	CMN_EVENT_RNID(s2_wdata_beats,	0x0e),
	CMN_EVENT_RNID(rrt_alloc,	0x0f),
	CMN_EVENT_RNID(wrt_alloc,	0x10),
	CMN_EVENT_RNID(rdb_unord,	0x11),
	CMN_EVENT_RNID(rdb_replay,	0x12),
	CMN_EVENT_RNID(rdb_hybrid,	0x13),
	CMN_EVENT_RNID(rdb_ord,		0x14),

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_cmn_event_attrs_group = अणु
	.name = "events",
	.attrs = arm_cmn_event_attrs,
	.is_visible = arm_cmn_event_attr_is_visible,
पूर्ण;

अटल sमाप_प्रकार arm_cmn_क्रमmat_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_cmn_क्रमmat_attr *fmt = container_of(attr, typeof(*fmt), attr);
	पूर्णांक lo = __ffs(fmt->field), hi = __fls(fmt->field);

	अगर (lo == hi)
		वापस sysfs_emit(buf, "config:%d\n", lo);

	अगर (!fmt->config)
		वापस sysfs_emit(buf, "config:%d-%d\n", lo, hi);

	वापस sysfs_emit(buf, "config%d:%d-%d\n", fmt->config, lo, hi);
पूर्ण

#घोषणा _CMN_FORMAT_ATTR(_name, _cfg, _fld)				\
	(&((काष्ठा arm_cmn_क्रमmat_attr[]) अणुअणु				\
		.attr = __ATTR(_name, 0444, arm_cmn_क्रमmat_show, शून्य),	\
		.config = _cfg,						\
		.field = _fld,						\
	पूर्णपूर्ण)[0].attr.attr)
#घोषणा CMN_FORMAT_ATTR(_name, _fld)	_CMN_FORMAT_ATTR(_name, 0, _fld)

अटल काष्ठा attribute *arm_cmn_क्रमmat_attrs[] = अणु
	CMN_FORMAT_ATTR(type, CMN_CONFIG_TYPE),
	CMN_FORMAT_ATTR(eventid, CMN_CONFIG_EVENTID),
	CMN_FORMAT_ATTR(occupid, CMN_CONFIG_OCCUPID),
	CMN_FORMAT_ATTR(bynodeid, CMN_CONFIG_BYNODEID),
	CMN_FORMAT_ATTR(nodeid, CMN_CONFIG_NODEID),

	CMN_FORMAT_ATTR(wp_dev_sel, CMN_CONFIG_WP_DEV_SEL),
	CMN_FORMAT_ATTR(wp_chn_sel, CMN_CONFIG_WP_CHN_SEL),
	CMN_FORMAT_ATTR(wp_grp, CMN_CONFIG_WP_GRP),
	CMN_FORMAT_ATTR(wp_exclusive, CMN_CONFIG_WP_EXCLUSIVE),
	CMN_FORMAT_ATTR(wp_combine, CMN_CONFIG_WP_COMBINE),

	_CMN_FORMAT_ATTR(wp_val, 1, CMN_CONFIG1_WP_VAL),
	_CMN_FORMAT_ATTR(wp_mask, 2, CMN_CONFIG2_WP_MASK),

	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_cmn_क्रमmat_attrs_group = अणु
	.name = "format",
	.attrs = arm_cmn_क्रमmat_attrs,
पूर्ण;

अटल sमाप_प्रकार arm_cmn_cpumask_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(cmn->cpu));
पूर्ण

अटल काष्ठा device_attribute arm_cmn_cpumask_attr =
		__ATTR(cpumask, 0444, arm_cmn_cpumask_show, शून्य);

अटल काष्ठा attribute *arm_cmn_cpumask_attrs[] = अणु
	&arm_cmn_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_cmn_cpumask_attr_group = अणु
	.attrs = arm_cmn_cpumask_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *arm_cmn_attr_groups[] = अणु
	&arm_cmn_event_attrs_group,
	&arm_cmn_क्रमmat_attrs_group,
	&arm_cmn_cpumask_attr_group,
	शून्य
पूर्ण;

अटल पूर्णांक arm_cmn_wp_idx(काष्ठा perf_event *event)
अणु
	वापस CMN_EVENT_EVENTID(event) + CMN_EVENT_WP_GRP(event);
पूर्ण

अटल u32 arm_cmn_wp_config(काष्ठा perf_event *event)
अणु
	u32 config;
	u32 dev = CMN_EVENT_WP_DEV_SEL(event);
	u32 chn = CMN_EVENT_WP_CHN_SEL(event);
	u32 grp = CMN_EVENT_WP_GRP(event);
	u32 exc = CMN_EVENT_WP_EXCLUSIVE(event);
	u32 combine = CMN_EVENT_WP_COMBINE(event);

	config = FIELD_PREP(CMN_DTM_WPn_CONFIG_WP_DEV_SEL, dev) |
		 FIELD_PREP(CMN_DTM_WPn_CONFIG_WP_CHN_SEL, chn) |
		 FIELD_PREP(CMN_DTM_WPn_CONFIG_WP_GRP, grp) |
		 FIELD_PREP(CMN_DTM_WPn_CONFIG_WP_EXCLUSIVE, exc);
	अगर (combine && !grp)
		config |= CMN_DTM_WPn_CONFIG_WP_COMBINE;

	वापस config;
पूर्ण

अटल व्योम arm_cmn_set_state(काष्ठा arm_cmn *cmn, u32 state)
अणु
	अगर (!cmn->state)
		ग_लिखोl_relaxed(0, cmn->dtc[0].base + CMN_DT_PMCR);
	cmn->state |= state;
पूर्ण

अटल व्योम arm_cmn_clear_state(काष्ठा arm_cmn *cmn, u32 state)
अणु
	cmn->state &= ~state;
	अगर (!cmn->state)
		ग_लिखोl_relaxed(CMN_DT_PMCR_PMU_EN | CMN_DT_PMCR_OVFL_INTR_EN,
			       cmn->dtc[0].base + CMN_DT_PMCR);
पूर्ण

अटल व्योम arm_cmn_pmu_enable(काष्ठा pmu *pmu)
अणु
	arm_cmn_clear_state(to_cmn(pmu), CMN_STATE_DISABLED);
पूर्ण

अटल व्योम arm_cmn_pmu_disable(काष्ठा pmu *pmu)
अणु
	arm_cmn_set_state(to_cmn(pmu), CMN_STATE_DISABLED);
पूर्ण

अटल u64 arm_cmn_पढ़ो_dपंचांग(काष्ठा arm_cmn *cmn, काष्ठा arm_cmn_hw_event *hw,
			    bool snapshot)
अणु
	काष्ठा arm_cmn_node *dn;
	अचिन्हित पूर्णांक i, offset;
	u64 count = 0;

	offset = snapshot ? CMN_DTM_PMEVCNTSR : CMN_DTM_PMEVCNT;
	क्रम_each_hw_dn(hw, dn, i) अणु
		काष्ठा arm_cmn_node *xp = arm_cmn_node_to_xp(dn);
		पूर्णांक dपंचांग_idx = arm_cmn_get_index(hw->dपंचांग_idx, i);
		u64 reg = पढ़ोq_relaxed(xp->pmu_base + offset);
		u16 dपंचांग_count = reg >> (dपंचांग_idx * 16);

		count += dपंचांग_count;
	पूर्ण
	वापस count;
पूर्ण

अटल u64 arm_cmn_पढ़ो_cc(काष्ठा arm_cmn_dtc *dtc)
अणु
	u64 val = पढ़ोq_relaxed(dtc->base + CMN_DT_PMCCNTR);

	ग_लिखोq_relaxed(CMN_CC_INIT, dtc->base + CMN_DT_PMCCNTR);
	वापस (val - CMN_CC_INIT) & ((CMN_CC_INIT << 1) - 1);
पूर्ण

अटल u32 arm_cmn_पढ़ो_counter(काष्ठा arm_cmn_dtc *dtc, पूर्णांक idx)
अणु
	u32 val, pmevcnt = CMN_DT_PMEVCNT(idx);

	val = पढ़ोl_relaxed(dtc->base + pmevcnt);
	ग_लिखोl_relaxed(CMN_COUNTER_INIT, dtc->base + pmevcnt);
	वापस val - CMN_COUNTER_INIT;
पूर्ण

अटल व्योम arm_cmn_init_counter(काष्ठा perf_event *event)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	अचिन्हित पूर्णांक i, pmevcnt = CMN_DT_PMEVCNT(hw->dtc_idx);
	u64 count;

	क्रम (i = 0; hw->dtcs_used & (1U << i); i++) अणु
		ग_लिखोl_relaxed(CMN_COUNTER_INIT, cmn->dtc[i].base + pmevcnt);
		cmn->dtc[i].counters[hw->dtc_idx] = event;
	पूर्ण

	count = arm_cmn_पढ़ो_dपंचांग(cmn, hw, false);
	local64_set(&event->hw.prev_count, count);
पूर्ण

अटल व्योम arm_cmn_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	u64 delta, new, prev;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	अगर (hw->dtc_idx == CMN_DT_NUM_COUNTERS) अणु
		i = __ffs(hw->dtcs_used);
		delta = arm_cmn_पढ़ो_cc(cmn->dtc + i);
		local64_add(delta, &event->count);
		वापस;
	पूर्ण
	new = arm_cmn_पढ़ो_dपंचांग(cmn, hw, false);
	prev = local64_xchg(&event->hw.prev_count, new);

	delta = new - prev;

	local_irq_save(flags);
	क्रम (i = 0; hw->dtcs_used & (1U << i); i++) अणु
		new = arm_cmn_पढ़ो_counter(cmn->dtc + i, hw->dtc_idx);
		delta += new << 16;
	पूर्ण
	local_irq_restore(flags);
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम arm_cmn_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	काष्ठा arm_cmn_node *dn;
	क्रमागत cmn_node_type type = CMN_EVENT_TYPE(event);
	पूर्णांक i;

	अगर (type == CMN_TYPE_DTC) अणु
		i = __ffs(hw->dtcs_used);
		ग_लिखोq_relaxed(CMN_CC_INIT, cmn->dtc[i].base + CMN_DT_PMCCNTR);
		cmn->dtc[i].cc_active = true;
	पूर्ण अन्यथा अगर (type == CMN_TYPE_WP) अणु
		पूर्णांक wp_idx = arm_cmn_wp_idx(event);
		u64 val = CMN_EVENT_WP_VAL(event);
		u64 mask = CMN_EVENT_WP_MASK(event);

		क्रम_each_hw_dn(hw, dn, i) अणु
			ग_लिखोq_relaxed(val, dn->pmu_base + CMN_DTM_WPn_VAL(wp_idx));
			ग_लिखोq_relaxed(mask, dn->pmu_base + CMN_DTM_WPn_MASK(wp_idx));
		पूर्ण
	पूर्ण अन्यथा क्रम_each_hw_dn(hw, dn, i) अणु
		पूर्णांक dपंचांग_idx = arm_cmn_get_index(hw->dपंचांग_idx, i);

		dn->event[dपंचांग_idx] = CMN_EVENT_EVENTID(event);
		ग_लिखोl_relaxed(le32_to_cpu(dn->event_sel), dn->pmu_base + CMN_PMU_EVENT_SEL);
	पूर्ण
पूर्ण

अटल व्योम arm_cmn_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	काष्ठा arm_cmn_node *dn;
	क्रमागत cmn_node_type type = CMN_EVENT_TYPE(event);
	पूर्णांक i;

	अगर (type == CMN_TYPE_DTC) अणु
		i = __ffs(hw->dtcs_used);
		cmn->dtc[i].cc_active = false;
	पूर्ण अन्यथा अगर (type == CMN_TYPE_WP) अणु
		पूर्णांक wp_idx = arm_cmn_wp_idx(event);

		क्रम_each_hw_dn(hw, dn, i) अणु
			ग_लिखोq_relaxed(0, dn->pmu_base + CMN_DTM_WPn_MASK(wp_idx));
			ग_लिखोq_relaxed(~0ULL, dn->pmu_base + CMN_DTM_WPn_VAL(wp_idx));
		पूर्ण
	पूर्ण अन्यथा क्रम_each_hw_dn(hw, dn, i) अणु
		पूर्णांक dपंचांग_idx = arm_cmn_get_index(hw->dपंचांग_idx, i);

		dn->event[dपंचांग_idx] = 0;
		ग_लिखोl_relaxed(le32_to_cpu(dn->event_sel), dn->pmu_base + CMN_PMU_EVENT_SEL);
	पूर्ण

	arm_cmn_event_पढ़ो(event);
पूर्ण

काष्ठा arm_cmn_val अणु
	u8 dपंचांग_count[CMN_MAX_XPS];
	u8 occupid[CMN_MAX_XPS];
	u8 wp[CMN_MAX_XPS][4];
	पूर्णांक dtc_count;
	bool cycles;
पूर्ण;

अटल व्योम arm_cmn_val_add_event(काष्ठा arm_cmn_val *val, काष्ठा perf_event *event)
अणु
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	काष्ठा arm_cmn_node *dn;
	क्रमागत cmn_node_type type;
	पूर्णांक i;
	u8 occupid;

	अगर (is_software_event(event))
		वापस;

	type = CMN_EVENT_TYPE(event);
	अगर (type == CMN_TYPE_DTC) अणु
		val->cycles = true;
		वापस;
	पूर्ण

	val->dtc_count++;
	अगर (arm_cmn_is_occup_event(type, CMN_EVENT_EVENTID(event)))
		occupid = CMN_EVENT_OCCUPID(event) + 1;
	अन्यथा
		occupid = 0;

	क्रम_each_hw_dn(hw, dn, i) अणु
		पूर्णांक wp_idx, xp = arm_cmn_node_to_xp(dn)->logid;

		val->dपंचांग_count[xp]++;
		val->occupid[xp] = occupid;

		अगर (type != CMN_TYPE_WP)
			जारी;

		wp_idx = arm_cmn_wp_idx(event);
		val->wp[xp][wp_idx] = CMN_EVENT_WP_COMBINE(event) + 1;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_cmn_validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	काष्ठा arm_cmn_node *dn;
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	क्रमागत cmn_node_type type;
	काष्ठा arm_cmn_val val;
	पूर्णांक i;
	u8 occupid;

	अगर (leader == event)
		वापस 0;

	अगर (event->pmu != leader->pmu && !is_software_event(leader))
		वापस -EINVAL;

	स_रखो(&val, 0, माप(val));

	arm_cmn_val_add_event(&val, leader);
	क्रम_each_sibling_event(sibling, leader)
		arm_cmn_val_add_event(&val, sibling);

	type = CMN_EVENT_TYPE(event);
	अगर (type == CMN_TYPE_DTC)
		वापस val.cycles ? -EINVAL : 0;

	अगर (val.dtc_count == CMN_DT_NUM_COUNTERS)
		वापस -EINVAL;

	अगर (arm_cmn_is_occup_event(type, CMN_EVENT_EVENTID(event)))
		occupid = CMN_EVENT_OCCUPID(event) + 1;
	अन्यथा
		occupid = 0;

	क्रम_each_hw_dn(hw, dn, i) अणु
		पूर्णांक wp_idx, wp_cmb, xp = arm_cmn_node_to_xp(dn)->logid;

		अगर (val.dपंचांग_count[xp] == CMN_DTM_NUM_COUNTERS)
			वापस -EINVAL;

		अगर (occupid && val.occupid[xp] && occupid != val.occupid[xp])
			वापस -EINVAL;

		अगर (type != CMN_TYPE_WP)
			जारी;

		wp_idx = arm_cmn_wp_idx(event);
		अगर (val.wp[xp][wp_idx])
			वापस -EINVAL;

		wp_cmb = val.wp[xp][wp_idx ^ 1];
		अगर (wp_cmb && wp_cmb != CMN_EVENT_WP_COMBINE(event) + 1)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arm_cmn_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	क्रमागत cmn_node_type type;
	अचिन्हित पूर्णांक i;
	bool bynodeid;
	u16 nodeid, eventid;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	event->cpu = cmn->cpu;
	अगर (event->cpu < 0)
		वापस -EINVAL;

	type = CMN_EVENT_TYPE(event);
	/* DTC events (i.e. cycles) alपढ़ोy have everything they need */
	अगर (type == CMN_TYPE_DTC)
		वापस 0;

	/* For watchpoपूर्णांकs we need the actual XP node here */
	अगर (type == CMN_TYPE_WP) अणु
		type = CMN_TYPE_XP;
		/* ...and we need a "real" direction */
		eventid = CMN_EVENT_EVENTID(event);
		अगर (eventid != CMN_WP_UP && eventid != CMN_WP_DOWN)
			वापस -EINVAL;
	पूर्ण

	bynodeid = CMN_EVENT_BYNODEID(event);
	nodeid = CMN_EVENT_NODEID(event);

	hw->dn = arm_cmn_node(cmn, type);
	क्रम (i = hw->dn - cmn->dns; i < cmn->num_dns && cmn->dns[i].type == type; i++) अणु
		अगर (!bynodeid) अणु
			hw->num_dns++;
		पूर्ण अन्यथा अगर (cmn->dns[i].id != nodeid) अणु
			hw->dn++;
		पूर्ण अन्यथा अणु
			hw->num_dns = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!hw->num_dns) अणु
		पूर्णांक bits = arm_cmn_xyidbits(cmn);

		dev_dbg(cmn->dev, "invalid node 0x%x (%d,%d,%d,%d) type 0x%x\n",
			nodeid, CMN_NODEID_X(nodeid, bits), CMN_NODEID_Y(nodeid, bits),
			CMN_NODEID_PID(nodeid), CMN_NODEID_DEVID(nodeid), type);
		वापस -EINVAL;
	पूर्ण
	/*
	 * By assuming events count in all DTC करोमुख्यs, we cunningly aव्योम
	 * needing to know anything about how XPs are asचिन्हित to करोमुख्यs.
	 */
	hw->dtcs_used = (1U << cmn->num_dtcs) - 1;

	वापस arm_cmn_validate_group(event);
पूर्ण

अटल व्योम arm_cmn_event_clear(काष्ठा arm_cmn *cmn, काष्ठा perf_event *event,
				पूर्णांक i)
अणु
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	क्रमागत cmn_node_type type = CMN_EVENT_TYPE(event);

	जबतक (i--) अणु
		काष्ठा arm_cmn_node *xp = arm_cmn_node_to_xp(hw->dn + i);
		अचिन्हित पूर्णांक dपंचांग_idx = arm_cmn_get_index(hw->dपंचांग_idx, i);

		अगर (type == CMN_TYPE_WP)
			hw->dn[i].wp_event[arm_cmn_wp_idx(event)] = -1;

		अगर (arm_cmn_is_occup_event(type, CMN_EVENT_EVENTID(event)))
			hw->dn[i].occupid_count--;

		xp->pmu_config_low &= ~CMN__PMEVCNT_PAIRED(dपंचांग_idx);
		ग_लिखोl_relaxed(xp->pmu_config_low, xp->pmu_base + CMN_DTM_PMU_CONFIG);
	पूर्ण
	स_रखो(hw->dपंचांग_idx, 0, माप(hw->dपंचांग_idx));

	क्रम (i = 0; hw->dtcs_used & (1U << i); i++)
		cmn->dtc[i].counters[hw->dtc_idx] = शून्य;
पूर्ण

अटल पूर्णांक arm_cmn_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	काष्ठा arm_cmn_dtc *dtc = &cmn->dtc[0];
	काष्ठा arm_cmn_node *dn;
	क्रमागत cmn_node_type type = CMN_EVENT_TYPE(event);
	अचिन्हित पूर्णांक i, dtc_idx, input_sel;

	अगर (type == CMN_TYPE_DTC) अणु
		i = 0;
		जबतक (cmn->dtc[i].cycles)
			अगर (++i == cmn->num_dtcs)
				वापस -ENOSPC;

		cmn->dtc[i].cycles = event;
		hw->dtc_idx = CMN_DT_NUM_COUNTERS;
		hw->dtcs_used = 1U << i;

		अगर (flags & PERF_EF_START)
			arm_cmn_event_start(event, 0);
		वापस 0;
	पूर्ण

	/* Grab a मुक्त global counter first... */
	dtc_idx = 0;
	जबतक (dtc->counters[dtc_idx])
		अगर (++dtc_idx == CMN_DT_NUM_COUNTERS)
			वापस -ENOSPC;

	hw->dtc_idx = dtc_idx;

	/* ...then the local counters to feed it. */
	क्रम_each_hw_dn(hw, dn, i) अणु
		काष्ठा arm_cmn_node *xp = arm_cmn_node_to_xp(dn);
		अचिन्हित पूर्णांक dपंचांग_idx, shअगरt;
		u64 reg;

		dपंचांग_idx = 0;
		जबतक (xp->pmu_config_low & CMN__PMEVCNT_PAIRED(dपंचांग_idx))
			अगर (++dपंचांग_idx == CMN_DTM_NUM_COUNTERS)
				जाओ मुक्त_dपंचांगs;

		अगर (type == CMN_TYPE_XP) अणु
			input_sel = CMN__PMEVCNT0_INPUT_SEL_XP + dपंचांग_idx;
		पूर्ण अन्यथा अगर (type == CMN_TYPE_WP) अणु
			पूर्णांक पंचांगp, wp_idx = arm_cmn_wp_idx(event);
			u32 cfg = arm_cmn_wp_config(event);

			अगर (dn->wp_event[wp_idx] >= 0)
				जाओ मुक्त_dपंचांगs;

			पंचांगp = dn->wp_event[wp_idx ^ 1];
			अगर (पंचांगp >= 0 && CMN_EVENT_WP_COMBINE(event) !=
					CMN_EVENT_WP_COMBINE(dtc->counters[पंचांगp]))
				जाओ मुक्त_dपंचांगs;

			input_sel = CMN__PMEVCNT0_INPUT_SEL_WP + wp_idx;
			dn->wp_event[wp_idx] = dtc_idx;
			ग_लिखोl_relaxed(cfg, dn->pmu_base + CMN_DTM_WPn_CONFIG(wp_idx));
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक port = CMN_NODEID_PID(dn->id);
			अचिन्हित पूर्णांक dev = CMN_NODEID_DEVID(dn->id);

			input_sel = CMN__PMEVCNT0_INPUT_SEL_DEV + dपंचांग_idx +
				    (port << 4) + (dev << 2);

			अगर (arm_cmn_is_occup_event(type, CMN_EVENT_EVENTID(event))) अणु
				पूर्णांक occupid = CMN_EVENT_OCCUPID(event);

				अगर (dn->occupid_count == 0) अणु
					dn->occupid_val = occupid;
					ग_लिखोl_relaxed(occupid,
						       dn->pmu_base + CMN_PMU_EVENT_SEL + 4);
				पूर्ण अन्यथा अगर (dn->occupid_val != occupid) अणु
					जाओ मुक्त_dपंचांगs;
				पूर्ण
				dn->occupid_count++;
			पूर्ण
		पूर्ण

		arm_cmn_set_index(hw->dपंचांग_idx, i, dपंचांग_idx);

		xp->input_sel[dपंचांग_idx] = input_sel;
		shअगरt = CMN__PMEVCNTn_GLOBAL_NUM_SHIFT(dपंचांग_idx);
		xp->pmu_config_low &= ~(CMN__PMEVCNT0_GLOBAL_NUM << shअगरt);
		xp->pmu_config_low |= FIELD_PREP(CMN__PMEVCNT0_GLOBAL_NUM, dtc_idx) << shअगरt;
		xp->pmu_config_low |= CMN__PMEVCNT_PAIRED(dपंचांग_idx);
		reg = (u64)le32_to_cpu(xp->pmu_config_high) << 32 | xp->pmu_config_low;
		ग_लिखोq_relaxed(reg, xp->pmu_base + CMN_DTM_PMU_CONFIG);
	पूर्ण

	/* Go go go! */
	arm_cmn_init_counter(event);

	अगर (flags & PERF_EF_START)
		arm_cmn_event_start(event, 0);

	वापस 0;

मुक्त_dपंचांगs:
	arm_cmn_event_clear(cmn, event, i);
	वापस -ENOSPC;
पूर्ण

अटल व्योम arm_cmn_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arm_cmn *cmn = to_cmn(event->pmu);
	काष्ठा arm_cmn_hw_event *hw = to_cmn_hw(event);
	क्रमागत cmn_node_type type = CMN_EVENT_TYPE(event);

	arm_cmn_event_stop(event, PERF_EF_UPDATE);

	अगर (type == CMN_TYPE_DTC)
		cmn->dtc[__ffs(hw->dtcs_used)].cycles = शून्य;
	अन्यथा
		arm_cmn_event_clear(cmn, event, hw->num_dns);
पूर्ण

/*
 * We stop the PMU क्रम both add and पढ़ो, to aव्योम skew across DTM counters.
 * In theory we could use snapshots to पढ़ो without stopping, but then it
 * becomes a lot trickier to deal with overlow and racing against पूर्णांकerrupts,
 * plus it seems they करोn't work properly on some hardware anyway :(
 */
अटल व्योम arm_cmn_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक flags)
अणु
	arm_cmn_set_state(to_cmn(pmu), CMN_STATE_TXN);
पूर्ण

अटल व्योम arm_cmn_end_txn(काष्ठा pmu *pmu)
अणु
	arm_cmn_clear_state(to_cmn(pmu), CMN_STATE_TXN);
पूर्ण

अटल पूर्णांक arm_cmn_commit_txn(काष्ठा pmu *pmu)
अणु
	arm_cmn_end_txn(pmu);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_cmn_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा arm_cmn *cmn;
	अचिन्हित पूर्णांक i, target;

	cmn = hlist_entry_safe(node, काष्ठा arm_cmn, cpuhp_node);
	अगर (cpu != cmn->cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&cmn->pmu, cpu, target);
	क्रम (i = 0; i < cmn->num_dtcs; i++)
		irq_set_affinity_hपूर्णांक(cmn->dtc[i].irq, cpumask_of(target));
	cmn->cpu = target;
	वापस 0;
पूर्ण

अटल irqवापस_t arm_cmn_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा arm_cmn_dtc *dtc = dev_id;
	irqवापस_t ret = IRQ_NONE;

	क्रम (;;) अणु
		u32 status = पढ़ोl_relaxed(dtc->base + CMN_DT_PMOVSR);
		u64 delta;
		पूर्णांक i;

		क्रम (i = 0; i < CMN_DTM_NUM_COUNTERS; i++) अणु
			अगर (status & (1U << i)) अणु
				ret = IRQ_HANDLED;
				अगर (WARN_ON(!dtc->counters[i]))
					जारी;
				delta = (u64)arm_cmn_पढ़ो_counter(dtc, i) << 16;
				local64_add(delta, &dtc->counters[i]->count);
			पूर्ण
		पूर्ण

		अगर (status & (1U << CMN_DT_NUM_COUNTERS)) अणु
			ret = IRQ_HANDLED;
			अगर (dtc->cc_active && !WARN_ON(!dtc->cycles)) अणु
				delta = arm_cmn_पढ़ो_cc(dtc);
				local64_add(delta, &dtc->cycles->count);
			पूर्ण
		पूर्ण

		ग_लिखोl_relaxed(status, dtc->base + CMN_DT_PMOVSR_CLR);

		अगर (!dtc->irq_मित्र)
			वापस ret;
		dtc += dtc->irq_मित्र;
	पूर्ण
पूर्ण

/* We can reasonably accommodate DTCs of the same CMN sharing IRQs */
अटल पूर्णांक arm_cmn_init_irqs(काष्ठा arm_cmn *cmn)
अणु
	पूर्णांक i, j, irq, err;

	क्रम (i = 0; i < cmn->num_dtcs; i++) अणु
		irq = cmn->dtc[i].irq;
		क्रम (j = i; j--; ) अणु
			अगर (cmn->dtc[j].irq == irq) अणु
				cmn->dtc[j].irq_मित्र = j - i;
				जाओ next;
			पूर्ण
		पूर्ण
		err = devm_request_irq(cmn->dev, irq, arm_cmn_handle_irq,
				       IRQF_NOBALANCING | IRQF_NO_THREAD,
				       dev_name(cmn->dev), &cmn->dtc[i]);
		अगर (err)
			वापस err;

		err = irq_set_affinity_hपूर्णांक(irq, cpumask_of(cmn->cpu));
		अगर (err)
			वापस err;
	next:
		; /* isn't C great? */
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arm_cmn_init_dपंचांग(काष्ठा arm_cmn_node *xp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		xp->wp_event[i] = -1;
		ग_लिखोq_relaxed(0, xp->pmu_base + CMN_DTM_WPn_MASK(i));
		ग_लिखोq_relaxed(~0ULL, xp->pmu_base + CMN_DTM_WPn_VAL(i));
	पूर्ण
	xp->pmu_config_low = CMN_DTM_PMU_CONFIG_PMU_EN;
	xp->dtc = -1;
पूर्ण

अटल पूर्णांक arm_cmn_init_dtc(काष्ठा arm_cmn *cmn, काष्ठा arm_cmn_node *dn, पूर्णांक idx)
अणु
	काष्ठा arm_cmn_dtc *dtc = cmn->dtc + idx;
	काष्ठा arm_cmn_node *xp;

	dtc->base = dn->pmu_base - CMN_PMU_OFFSET;
	dtc->irq = platक्रमm_get_irq(to_platक्रमm_device(cmn->dev), idx);
	अगर (dtc->irq < 0)
		वापस dtc->irq;

	ग_लिखोl_relaxed(0, dtc->base + CMN_DT_PMCR);
	ग_लिखोl_relaxed(0x1ff, dtc->base + CMN_DT_PMOVSR_CLR);
	ग_लिखोl_relaxed(CMN_DT_PMCR_OVFL_INTR_EN, dtc->base + CMN_DT_PMCR);

	/* We करो at least know that a DTC's XP must be in that DTC's करोमुख्य */
	xp = arm_cmn_node_to_xp(dn);
	xp->dtc = idx;

	वापस 0;
पूर्ण

अटल पूर्णांक arm_cmn_node_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा arm_cmn_node *dna = a, *dnb = b;
	पूर्णांक cmp;

	cmp = dna->type - dnb->type;
	अगर (!cmp)
		cmp = dna->logid - dnb->logid;
	वापस cmp;
पूर्ण

अटल पूर्णांक arm_cmn_init_dtcs(काष्ठा arm_cmn *cmn)
अणु
	काष्ठा arm_cmn_node *dn;
	पूर्णांक dtc_idx = 0;

	cmn->dtc = devm_kसुस्मृति(cmn->dev, cmn->num_dtcs, माप(cmn->dtc[0]), GFP_KERNEL);
	अगर (!cmn->dtc)
		वापस -ENOMEM;

	sort(cmn->dns, cmn->num_dns, माप(cmn->dns[0]), arm_cmn_node_cmp, शून्य);

	cmn->xps = arm_cmn_node(cmn, CMN_TYPE_XP);

	क्रम (dn = cmn->dns; dn < cmn->dns + cmn->num_dns; dn++) अणु
		अगर (dn->type != CMN_TYPE_XP)
			arm_cmn_init_node_to_xp(cmn, dn);
		अन्यथा अगर (cmn->num_dtcs == 1)
			dn->dtc = 0;

		अगर (dn->type == CMN_TYPE_DTC)
			arm_cmn_init_dtc(cmn, dn, dtc_idx++);

		/* To the PMU, RN-Ds करोn't add anything over RN-Is, so smoosh them together */
		अगर (dn->type == CMN_TYPE_RND)
			dn->type = CMN_TYPE_RNI;
	पूर्ण

	ग_लिखोl_relaxed(CMN_DT_DTC_CTL_DT_EN, cmn->dtc[0].base + CMN_DT_DTC_CTL);

	वापस 0;
पूर्ण

अटल व्योम arm_cmn_init_node_info(काष्ठा arm_cmn *cmn, u32 offset, काष्ठा arm_cmn_node *node)
अणु
	पूर्णांक level;
	u64 reg = पढ़ोq_relaxed(cmn->base + offset + CMN_NODE_INFO);

	node->type = FIELD_GET(CMN_NI_NODE_TYPE, reg);
	node->id = FIELD_GET(CMN_NI_NODE_ID, reg);
	node->logid = FIELD_GET(CMN_NI_LOGICAL_ID, reg);

	node->pmu_base = cmn->base + offset + CMN_PMU_OFFSET;

	अगर (node->type == CMN_TYPE_CFG)
		level = 0;
	अन्यथा अगर (node->type == CMN_TYPE_XP)
		level = 1;
	अन्यथा
		level = 2;

	dev_dbg(cmn->dev, "node%*c%#06hx%*ctype:%-#6x id:%-4hd off:%#x\n",
			(level * 2) + 1, ' ', node->id, 5 - (level * 2), ' ',
			node->type, node->logid, offset);
पूर्ण

अटल पूर्णांक arm_cmn_discover(काष्ठा arm_cmn *cmn, अचिन्हित पूर्णांक rgn_offset)
अणु
	व्योम __iomem *cfg_region;
	काष्ठा arm_cmn_node cfg, *dn;
	u16 child_count, child_poff;
	u32 xp_offset[CMN_MAX_XPS];
	u64 reg;
	पूर्णांक i, j;

	cfg_region = cmn->base + rgn_offset;
	reg = पढ़ोl_relaxed(cfg_region + CMN_CFGM_PERIPH_ID_2);
	cmn->rev = FIELD_GET(CMN_CFGM_PID2_REVISION, reg);
	dev_dbg(cmn->dev, "periph_id_2 revision: %d\n", cmn->rev);

	arm_cmn_init_node_info(cmn, rgn_offset, &cfg);
	अगर (cfg.type != CMN_TYPE_CFG)
		वापस -ENODEV;

	reg = पढ़ोq_relaxed(cfg_region + CMN_CHILD_INFO);
	child_count = FIELD_GET(CMN_CI_CHILD_COUNT, reg);
	child_poff = FIELD_GET(CMN_CI_CHILD_PTR_OFFSET, reg);

	cmn->num_xps = child_count;
	cmn->num_dns = cmn->num_xps;

	/* Pass 1: visit the XPs, क्रमागतerate their children */
	क्रम (i = 0; i < cmn->num_xps; i++) अणु
		reg = पढ़ोq_relaxed(cfg_region + child_poff + i * 8);
		xp_offset[i] = reg & CMN_CHILD_NODE_ADDR;

		reg = पढ़ोq_relaxed(cmn->base + xp_offset[i] + CMN_CHILD_INFO);
		cmn->num_dns += FIELD_GET(CMN_CI_CHILD_COUNT, reg);
	पूर्ण

	/* Cheeky +1 to help terminate poपूर्णांकer-based iteration */
	cmn->dns = devm_kसुस्मृति(cmn->dev, cmn->num_dns + 1,
				माप(*cmn->dns), GFP_KERNEL);
	अगर (!cmn->dns)
		वापस -ENOMEM;

	/* Pass 2: now we can actually populate the nodes */
	dn = cmn->dns;
	क्रम (i = 0; i < cmn->num_xps; i++) अणु
		व्योम __iomem *xp_region = cmn->base + xp_offset[i];
		काष्ठा arm_cmn_node *xp = dn++;

		arm_cmn_init_node_info(cmn, xp_offset[i], xp);
		arm_cmn_init_dपंचांग(xp);
		/*
		 * Thanks to the order in which XP logical IDs seem to be
		 * asचिन्हित, we can handily infer the mesh X dimension by
		 * looking out क्रम the XP at (0,1) without needing to know
		 * the exact node ID क्रमmat, which we can later derive.
		 */
		अगर (xp->id == (1 << 3))
			cmn->mesh_x = xp->logid;

		reg = पढ़ोq_relaxed(xp_region + CMN_CHILD_INFO);
		child_count = FIELD_GET(CMN_CI_CHILD_COUNT, reg);
		child_poff = FIELD_GET(CMN_CI_CHILD_PTR_OFFSET, reg);

		क्रम (j = 0; j < child_count; j++) अणु
			reg = पढ़ोq_relaxed(xp_region + child_poff + j * 8);
			/*
			 * Don't even try to touch anything बाह्यal, since in general
			 * we haven't a clue how to घातer up arbitrary CHI requesters.
			 * As of CMN-600r1 these could only be RN-SAMs or CXLAs,
			 * neither of which have any PMU events anyway.
			 * (Actually, CXLAs करो seem to have grown some events in r1p2,
			 * but they करोn't go to regular XP DTMs, and they depend on
			 * secure configuration which we can't easily deal with)
			 */
			अगर (reg & CMN_CHILD_NODE_EXTERNAL) अणु
				dev_dbg(cmn->dev, "ignoring external node %llx\n", reg);
				जारी;
			पूर्ण

			arm_cmn_init_node_info(cmn, reg & CMN_CHILD_NODE_ADDR, dn);

			चयन (dn->type) अणु
			हाल CMN_TYPE_DTC:
				cmn->num_dtcs++;
				dn++;
				अवरोध;
			/* These guys have PMU events */
			हाल CMN_TYPE_DVM:
			हाल CMN_TYPE_HNI:
			हाल CMN_TYPE_HNF:
			हाल CMN_TYPE_SBSX:
			हाल CMN_TYPE_RNI:
			हाल CMN_TYPE_RND:
			हाल CMN_TYPE_CXRA:
			हाल CMN_TYPE_CXHA:
				dn++;
				अवरोध;
			/* Nothing to see here */
			हाल CMN_TYPE_RNSAM:
			हाल CMN_TYPE_CXLA:
				अवरोध;
			/* Something has gone horribly wrong */
			शेष:
				dev_err(cmn->dev, "invalid device node type: 0x%x\n", dn->type);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Correct क्रम any nodes we skipped */
	cmn->num_dns = dn - cmn->dns;

	/*
	 * If mesh_x wasn't set during discovery then we never saw
	 * an XP at (0,1), thus we must have an Nx1 configuration.
	 */
	अगर (!cmn->mesh_x)
		cmn->mesh_x = cmn->num_xps;
	cmn->mesh_y = cmn->num_xps / cmn->mesh_x;

	dev_dbg(cmn->dev, "mesh %dx%d, ID width %d\n",
		cmn->mesh_x, cmn->mesh_y, arm_cmn_xyidbits(cmn));

	वापस 0;
पूर्ण

अटल पूर्णांक arm_cmn_acpi_probe(काष्ठा platक्रमm_device *pdev, काष्ठा arm_cmn *cmn)
अणु
	काष्ठा resource *cfg, *root;

	cfg = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!cfg)
		वापस -EINVAL;

	root = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!root)
		वापस -EINVAL;

	अगर (!resource_contains(cfg, root))
		swap(cfg, root);
	/*
	 * Note that devm_ioremap_resource() is dumb and won't let the platक्रमm
	 * device claim cfg when the ACPI companion device has alपढ़ोy claimed
	 * root within it. But since they *are* alपढ़ोy both claimed in the
	 * appropriate name, we करोn't really need to करो it again here anyway.
	 */
	cmn->base = devm_ioremap(cmn->dev, cfg->start, resource_size(cfg));
	अगर (!cmn->base)
		वापस -ENOMEM;

	वापस root->start - cfg->start;
पूर्ण

अटल पूर्णांक arm_cmn_of_probe(काष्ठा platक्रमm_device *pdev, काष्ठा arm_cmn *cmn)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 rootnode;
	पूर्णांक ret;

	cmn->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cmn->base))
		वापस PTR_ERR(cmn->base);

	ret = of_property_पढ़ो_u32(np, "arm,root-node", &rootnode);
	अगर (ret)
		वापस ret;

	वापस rootnode;
पूर्ण

अटल पूर्णांक arm_cmn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_cmn *cmn;
	स्थिर अक्षर *name;
	अटल atomic_t id;
	पूर्णांक err, rootnode;

	cmn = devm_kzalloc(&pdev->dev, माप(*cmn), GFP_KERNEL);
	अगर (!cmn)
		वापस -ENOMEM;

	cmn->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, cmn);

	अगर (has_acpi_companion(cmn->dev))
		rootnode = arm_cmn_acpi_probe(pdev, cmn);
	अन्यथा
		rootnode = arm_cmn_of_probe(pdev, cmn);
	अगर (rootnode < 0)
		वापस rootnode;

	err = arm_cmn_discover(cmn, rootnode);
	अगर (err)
		वापस err;

	err = arm_cmn_init_dtcs(cmn);
	अगर (err)
		वापस err;

	err = arm_cmn_init_irqs(cmn);
	अगर (err)
		वापस err;

	cmn->cpu = raw_smp_processor_id();
	cmn->pmu = (काष्ठा pmu) अणु
		.module = THIS_MODULE,
		.attr_groups = arm_cmn_attr_groups,
		.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
		.task_ctx_nr = perf_invalid_context,
		.pmu_enable = arm_cmn_pmu_enable,
		.pmu_disable = arm_cmn_pmu_disable,
		.event_init = arm_cmn_event_init,
		.add = arm_cmn_event_add,
		.del = arm_cmn_event_del,
		.start = arm_cmn_event_start,
		.stop = arm_cmn_event_stop,
		.पढ़ो = arm_cmn_event_पढ़ो,
		.start_txn = arm_cmn_start_txn,
		.commit_txn = arm_cmn_commit_txn,
		.cancel_txn = arm_cmn_end_txn,
	पूर्ण;

	name = devm_kaप्र_लिखो(cmn->dev, GFP_KERNEL, "arm_cmn_%d", atomic_fetch_inc(&id));
	अगर (!name)
		वापस -ENOMEM;

	err = cpuhp_state_add_instance(arm_cmn_hp_state, &cmn->cpuhp_node);
	अगर (err)
		वापस err;

	err = perf_pmu_रेजिस्टर(&cmn->pmu, name, -1);
	अगर (err)
		cpuhp_state_हटाओ_instance(arm_cmn_hp_state, &cmn->cpuhp_node);
	वापस err;
पूर्ण

अटल पूर्णांक arm_cmn_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_cmn *cmn = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	ग_लिखोl_relaxed(0, cmn->dtc[0].base + CMN_DT_DTC_CTL);

	perf_pmu_unरेजिस्टर(&cmn->pmu);
	cpuhp_state_हटाओ_instance(arm_cmn_hp_state, &cmn->cpuhp_node);

	क्रम (i = 0; i < cmn->num_dtcs; i++)
		irq_set_affinity_hपूर्णांक(cmn->dtc[i].irq, शून्य);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id arm_cmn_of_match[] = अणु
	अणु .compatible = "arm,cmn-600", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_cmn_of_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id arm_cmn_acpi_match[] = अणु
	अणु "ARMHC600", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, arm_cmn_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver arm_cmn_driver = अणु
	.driver = अणु
		.name = "arm-cmn",
		.of_match_table = of_match_ptr(arm_cmn_of_match),
		.acpi_match_table = ACPI_PTR(arm_cmn_acpi_match),
	पूर्ण,
	.probe = arm_cmn_probe,
	.हटाओ = arm_cmn_हटाओ,
पूर्ण;

अटल पूर्णांक __init arm_cmn_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      "perf/arm/cmn:online", शून्य,
				      arm_cmn_pmu_offline_cpu);
	अगर (ret < 0)
		वापस ret;

	arm_cmn_hp_state = ret;
	ret = platक्रमm_driver_रेजिस्टर(&arm_cmn_driver);
	अगर (ret)
		cpuhp_हटाओ_multi_state(arm_cmn_hp_state);
	वापस ret;
पूर्ण

अटल व्योम __निकास arm_cmn_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arm_cmn_driver);
	cpuhp_हटाओ_multi_state(arm_cmn_hp_state);
पूर्ण

module_init(arm_cmn_init);
module_निकास(arm_cmn_निकास);

MODULE_AUTHOR("Robin Murphy <robin.murphy@arm.com>");
MODULE_DESCRIPTION("Arm CMN-600 PMU driver");
MODULE_LICENSE("GPL v2");
