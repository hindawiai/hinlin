<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Nehalem-EX/Wesपंचांगere-EX uncore support */
#समावेश "uncore.h"

/* NHM-EX event control */
#घोषणा NHMEX_PMON_CTL_EV_SEL_MASK	0x000000ff
#घोषणा NHMEX_PMON_CTL_UMASK_MASK	0x0000ff00
#घोषणा NHMEX_PMON_CTL_EN_BIT0		(1 << 0)
#घोषणा NHMEX_PMON_CTL_EDGE_DET		(1 << 18)
#घोषणा NHMEX_PMON_CTL_PMI_EN		(1 << 20)
#घोषणा NHMEX_PMON_CTL_EN_BIT22		(1 << 22)
#घोषणा NHMEX_PMON_CTL_INVERT		(1 << 23)
#घोषणा NHMEX_PMON_CTL_TRESH_MASK	0xff000000
#घोषणा NHMEX_PMON_RAW_EVENT_MASK	(NHMEX_PMON_CTL_EV_SEL_MASK | \
					 NHMEX_PMON_CTL_UMASK_MASK | \
					 NHMEX_PMON_CTL_EDGE_DET | \
					 NHMEX_PMON_CTL_INVERT | \
					 NHMEX_PMON_CTL_TRESH_MASK)

/* NHM-EX Ubox */
#घोषणा NHMEX_U_MSR_PMON_GLOBAL_CTL		0xc00
#घोषणा NHMEX_U_MSR_PMON_CTR			0xc11
#घोषणा NHMEX_U_MSR_PMON_EV_SEL			0xc10

#घोषणा NHMEX_U_PMON_GLOBAL_EN			(1 << 0)
#घोषणा NHMEX_U_PMON_GLOBAL_PMI_CORE_SEL	0x0000001e
#घोषणा NHMEX_U_PMON_GLOBAL_EN_ALL		(1 << 28)
#घोषणा NHMEX_U_PMON_GLOBAL_RST_ALL		(1 << 29)
#घोषणा NHMEX_U_PMON_GLOBAL_FRZ_ALL		(1 << 31)

#घोषणा NHMEX_U_PMON_RAW_EVENT_MASK		\
		(NHMEX_PMON_CTL_EV_SEL_MASK |	\
		 NHMEX_PMON_CTL_EDGE_DET)

/* NHM-EX Cbox */
#घोषणा NHMEX_C0_MSR_PMON_GLOBAL_CTL		0xd00
#घोषणा NHMEX_C0_MSR_PMON_CTR0			0xd11
#घोषणा NHMEX_C0_MSR_PMON_EV_SEL0		0xd10
#घोषणा NHMEX_C_MSR_OFFSET			0x20

/* NHM-EX Bbox */
#घोषणा NHMEX_B0_MSR_PMON_GLOBAL_CTL		0xc20
#घोषणा NHMEX_B0_MSR_PMON_CTR0			0xc31
#घोषणा NHMEX_B0_MSR_PMON_CTL0			0xc30
#घोषणा NHMEX_B_MSR_OFFSET			0x40
#घोषणा NHMEX_B0_MSR_MATCH			0xe45
#घोषणा NHMEX_B0_MSR_MASK			0xe46
#घोषणा NHMEX_B1_MSR_MATCH			0xe4d
#घोषणा NHMEX_B1_MSR_MASK			0xe4e

#घोषणा NHMEX_B_PMON_CTL_EN			(1 << 0)
#घोषणा NHMEX_B_PMON_CTL_EV_SEL_SHIFT		1
#घोषणा NHMEX_B_PMON_CTL_EV_SEL_MASK		\
		(0x1f << NHMEX_B_PMON_CTL_EV_SEL_SHIFT)
#घोषणा NHMEX_B_PMON_CTR_SHIFT		6
#घोषणा NHMEX_B_PMON_CTR_MASK		\
		(0x3 << NHMEX_B_PMON_CTR_SHIFT)
#घोषणा NHMEX_B_PMON_RAW_EVENT_MASK		\
		(NHMEX_B_PMON_CTL_EV_SEL_MASK | \
		 NHMEX_B_PMON_CTR_MASK)

/* NHM-EX Sbox */
#घोषणा NHMEX_S0_MSR_PMON_GLOBAL_CTL		0xc40
#घोषणा NHMEX_S0_MSR_PMON_CTR0			0xc51
#घोषणा NHMEX_S0_MSR_PMON_CTL0			0xc50
#घोषणा NHMEX_S_MSR_OFFSET			0x80
#घोषणा NHMEX_S0_MSR_MM_CFG			0xe48
#घोषणा NHMEX_S0_MSR_MATCH			0xe49
#घोषणा NHMEX_S0_MSR_MASK			0xe4a
#घोषणा NHMEX_S1_MSR_MM_CFG			0xe58
#घोषणा NHMEX_S1_MSR_MATCH			0xe59
#घोषणा NHMEX_S1_MSR_MASK			0xe5a

#घोषणा NHMEX_S_PMON_MM_CFG_EN			(0x1ULL << 63)
#घोषणा NHMEX_S_EVENT_TO_R_PROG_EV		0

/* NHM-EX Mbox */
#घोषणा NHMEX_M0_MSR_GLOBAL_CTL			0xca0
#घोषणा NHMEX_M0_MSR_PMU_DSP			0xca5
#घोषणा NHMEX_M0_MSR_PMU_ISS			0xca6
#घोषणा NHMEX_M0_MSR_PMU_MAP			0xca7
#घोषणा NHMEX_M0_MSR_PMU_MSC_THR		0xca8
#घोषणा NHMEX_M0_MSR_PMU_PGT			0xca9
#घोषणा NHMEX_M0_MSR_PMU_PLD			0xcaa
#घोषणा NHMEX_M0_MSR_PMU_ZDP_CTL_FVC		0xcab
#घोषणा NHMEX_M0_MSR_PMU_CTL0			0xcb0
#घोषणा NHMEX_M0_MSR_PMU_CNT0			0xcb1
#घोषणा NHMEX_M_MSR_OFFSET			0x40
#घोषणा NHMEX_M0_MSR_PMU_MM_CFG			0xe54
#घोषणा NHMEX_M1_MSR_PMU_MM_CFG			0xe5c

#घोषणा NHMEX_M_PMON_MM_CFG_EN			(1ULL << 63)
#घोषणा NHMEX_M_PMON_ADDR_MATCH_MASK		0x3ffffffffULL
#घोषणा NHMEX_M_PMON_ADDR_MASK_MASK		0x7ffffffULL
#घोषणा NHMEX_M_PMON_ADDR_MASK_SHIFT		34

#घोषणा NHMEX_M_PMON_CTL_EN			(1 << 0)
#घोषणा NHMEX_M_PMON_CTL_PMI_EN			(1 << 1)
#घोषणा NHMEX_M_PMON_CTL_COUNT_MODE_SHIFT	2
#घोषणा NHMEX_M_PMON_CTL_COUNT_MODE_MASK	\
	(0x3 << NHMEX_M_PMON_CTL_COUNT_MODE_SHIFT)
#घोषणा NHMEX_M_PMON_CTL_STORAGE_MODE_SHIFT	4
#घोषणा NHMEX_M_PMON_CTL_STORAGE_MODE_MASK	\
	(0x3 << NHMEX_M_PMON_CTL_STORAGE_MODE_SHIFT)
#घोषणा NHMEX_M_PMON_CTL_WRAP_MODE		(1 << 6)
#घोषणा NHMEX_M_PMON_CTL_FLAG_MODE		(1 << 7)
#घोषणा NHMEX_M_PMON_CTL_INC_SEL_SHIFT		9
#घोषणा NHMEX_M_PMON_CTL_INC_SEL_MASK		\
	(0x1f << NHMEX_M_PMON_CTL_INC_SEL_SHIFT)
#घोषणा NHMEX_M_PMON_CTL_SET_FLAG_SEL_SHIFT	19
#घोषणा NHMEX_M_PMON_CTL_SET_FLAG_SEL_MASK	\
	(0x7 << NHMEX_M_PMON_CTL_SET_FLAG_SEL_SHIFT)
#घोषणा NHMEX_M_PMON_RAW_EVENT_MASK			\
		(NHMEX_M_PMON_CTL_COUNT_MODE_MASK |	\
		 NHMEX_M_PMON_CTL_STORAGE_MODE_MASK |	\
		 NHMEX_M_PMON_CTL_WRAP_MODE |		\
		 NHMEX_M_PMON_CTL_FLAG_MODE |		\
		 NHMEX_M_PMON_CTL_INC_SEL_MASK |	\
		 NHMEX_M_PMON_CTL_SET_FLAG_SEL_MASK)

#घोषणा NHMEX_M_PMON_ZDP_CTL_FVC_MASK		(((1 << 11) - 1) | (1 << 23))
#घोषणा NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(n)	(0x7ULL << (11 + 3 * (n)))

#घोषणा WSMEX_M_PMON_ZDP_CTL_FVC_MASK		(((1 << 12) - 1) | (1 << 24))
#घोषणा WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(n)	(0x7ULL << (12 + 3 * (n)))

/*
 * use the 9~13 bits to select event If the 7th bit is not set,
 * otherwise use the 19~21 bits to select event.
 */
#घोषणा MBOX_INC_SEL(x) ((x) << NHMEX_M_PMON_CTL_INC_SEL_SHIFT)
#घोषणा MBOX_SET_FLAG_SEL(x) (((x) << NHMEX_M_PMON_CTL_SET_FLAG_SEL_SHIFT) | \
				NHMEX_M_PMON_CTL_FLAG_MODE)
#घोषणा MBOX_INC_SEL_MASK (NHMEX_M_PMON_CTL_INC_SEL_MASK | \
			   NHMEX_M_PMON_CTL_FLAG_MODE)
#घोषणा MBOX_SET_FLAG_SEL_MASK (NHMEX_M_PMON_CTL_SET_FLAG_SEL_MASK | \
				NHMEX_M_PMON_CTL_FLAG_MODE)
#घोषणा MBOX_INC_SEL_EXTAR_REG(c, r) \
		EVENT_EXTRA_REG(MBOX_INC_SEL(c), NHMEX_M0_MSR_PMU_##r, \
				MBOX_INC_SEL_MASK, (u64)-1, NHMEX_M_##r)
#घोषणा MBOX_SET_FLAG_SEL_EXTRA_REG(c, r) \
		EVENT_EXTRA_REG(MBOX_SET_FLAG_SEL(c), NHMEX_M0_MSR_PMU_##r, \
				MBOX_SET_FLAG_SEL_MASK, \
				(u64)-1, NHMEX_M_##r)

/* NHM-EX Rbox */
#घोषणा NHMEX_R_MSR_GLOBAL_CTL			0xe00
#घोषणा NHMEX_R_MSR_PMON_CTL0			0xe10
#घोषणा NHMEX_R_MSR_PMON_CNT0			0xe11
#घोषणा NHMEX_R_MSR_OFFSET			0x20

#घोषणा NHMEX_R_MSR_PORTN_QLX_CFG(n)		\
		((n) < 4 ? (0xe0c + (n)) : (0xe2c + (n) - 4))
#घोषणा NHMEX_R_MSR_PORTN_IPERF_CFG0(n)		(0xe04 + (n))
#घोषणा NHMEX_R_MSR_PORTN_IPERF_CFG1(n)		(0xe24 + (n))
#घोषणा NHMEX_R_MSR_PORTN_XBR_OFFSET(n)		\
		(((n) < 4 ? 0 : 0x10) + (n) * 4)
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(n)	\
		(0xe60 + NHMEX_R_MSR_PORTN_XBR_OFFSET(n))
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET1_MATCH(n)	\
		(NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(n) + 1)
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET1_MASK(n)	\
		(NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(n) + 2)
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(n)	\
		(0xe70 + NHMEX_R_MSR_PORTN_XBR_OFFSET(n))
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET2_MATCH(n)	\
		(NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(n) + 1)
#घोषणा NHMEX_R_MSR_PORTN_XBR_SET2_MASK(n)	\
		(NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(n) + 2)

#घोषणा NHMEX_R_PMON_CTL_EN			(1 << 0)
#घोषणा NHMEX_R_PMON_CTL_EV_SEL_SHIFT		1
#घोषणा NHMEX_R_PMON_CTL_EV_SEL_MASK		\
		(0x1f << NHMEX_R_PMON_CTL_EV_SEL_SHIFT)
#घोषणा NHMEX_R_PMON_CTL_PMI_EN			(1 << 6)
#घोषणा NHMEX_R_PMON_RAW_EVENT_MASK		NHMEX_R_PMON_CTL_EV_SEL_MASK

/* NHM-EX Wbox */
#घोषणा NHMEX_W_MSR_GLOBAL_CTL			0xc80
#घोषणा NHMEX_W_MSR_PMON_CNT0			0xc90
#घोषणा NHMEX_W_MSR_PMON_EVT_SEL0		0xc91
#घोषणा NHMEX_W_MSR_PMON_FIXED_CTR		0x394
#घोषणा NHMEX_W_MSR_PMON_FIXED_CTL		0x395

#घोषणा NHMEX_W_PMON_GLOBAL_FIXED_EN		(1ULL << 31)

#घोषणा __BITS_VALUE(x, i, n)  ((typeof(x))(((x) >> ((i) * (n))) & \
				((1ULL << (n)) - 1)))

DEFINE_UNCORE_FORMAT_ATTR(event, event, "config:0-7");
DEFINE_UNCORE_FORMAT_ATTR(event5, event, "config:1-5");
DEFINE_UNCORE_FORMAT_ATTR(umask, umask, "config:8-15");
DEFINE_UNCORE_FORMAT_ATTR(edge, edge, "config:18");
DEFINE_UNCORE_FORMAT_ATTR(inv, inv, "config:23");
DEFINE_UNCORE_FORMAT_ATTR(thresh8, thresh, "config:24-31");
DEFINE_UNCORE_FORMAT_ATTR(counter, counter, "config:6-7");
DEFINE_UNCORE_FORMAT_ATTR(match, match, "config1:0-63");
DEFINE_UNCORE_FORMAT_ATTR(mask, mask, "config2:0-63");

अटल व्योम nhmex_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(NHMEX_U_MSR_PMON_GLOBAL_CTL, NHMEX_U_PMON_GLOBAL_EN_ALL);
पूर्ण

अटल व्योम nhmex_uncore_msr_निकास_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(NHMEX_U_MSR_PMON_GLOBAL_CTL, 0);
पूर्ण

अटल व्योम nhmex_uncore_msr_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित msr = uncore_msr_box_ctl(box);
	u64 config;

	अगर (msr) अणु
		rdmsrl(msr, config);
		config &= ~((1ULL << uncore_num_counters(box)) - 1);
		/* WBox has a fixed counter */
		अगर (uncore_msr_fixed_ctl(box))
			config &= ~NHMEX_W_PMON_GLOBAL_FIXED_EN;
		wrmsrl(msr, config);
	पूर्ण
पूर्ण

अटल व्योम nhmex_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित msr = uncore_msr_box_ctl(box);
	u64 config;

	अगर (msr) अणु
		rdmsrl(msr, config);
		config |= (1ULL << uncore_num_counters(box)) - 1;
		/* WBox has a fixed counter */
		अगर (uncore_msr_fixed_ctl(box))
			config |= NHMEX_W_PMON_GLOBAL_FIXED_EN;
		wrmsrl(msr, config);
	पूर्ण
पूर्ण

अटल व्योम nhmex_uncore_msr_disable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	wrmsrl(event->hw.config_base, 0);
पूर्ण

अटल व्योम nhmex_uncore_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (hwc->idx == UNCORE_PMC_IDX_FIXED)
		wrmsrl(hwc->config_base, NHMEX_PMON_CTL_EN_BIT0);
	अन्यथा अगर (box->pmu->type->event_mask & NHMEX_PMON_CTL_EN_BIT0)
		wrmsrl(hwc->config_base, hwc->config | NHMEX_PMON_CTL_EN_BIT22);
	अन्यथा
		wrmsrl(hwc->config_base, hwc->config | NHMEX_PMON_CTL_EN_BIT0);
पूर्ण

#घोषणा NHMEX_UNCORE_OPS_COMMON_INIT()				\
	.init_box	= nhmex_uncore_msr_init_box,		\
	.निकास_box	= nhmex_uncore_msr_निकास_box,		\
	.disable_box	= nhmex_uncore_msr_disable_box,		\
	.enable_box	= nhmex_uncore_msr_enable_box,		\
	.disable_event	= nhmex_uncore_msr_disable_event,	\
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter

अटल काष्ठा पूर्णांकel_uncore_ops nhmex_uncore_ops = अणु
	NHMEX_UNCORE_OPS_COMMON_INIT(),
	.enable_event	= nhmex_uncore_msr_enable_event,
पूर्ण;

अटल काष्ठा attribute *nhmex_uncore_ubox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_edge.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_ubox_क्रमmat_group = अणु
	.name		= "format",
	.attrs		= nhmex_uncore_ubox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_ubox = अणु
	.name		= "ubox",
	.num_counters	= 1,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.event_ctl	= NHMEX_U_MSR_PMON_EV_SEL,
	.perf_ctr	= NHMEX_U_MSR_PMON_CTR,
	.event_mask	= NHMEX_U_PMON_RAW_EVENT_MASK,
	.box_ctl	= NHMEX_U_MSR_PMON_GLOBAL_CTL,
	.ops		= &nhmex_uncore_ops,
	.क्रमmat_group	= &nhmex_uncore_ubox_क्रमmat_group
पूर्ण;

अटल काष्ठा attribute *nhmex_uncore_cbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_cbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = nhmex_uncore_cbox_क्रमmats_attr,
पूर्ण;

/* msr offset क्रम each instance of cbox */
अटल अचिन्हित nhmex_cbox_msr_offsets[] = अणु
	0x0, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x240, 0x2c0,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_cbox = अणु
	.name			= "cbox",
	.num_counters		= 6,
	.num_boxes		= 10,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_C0_MSR_PMON_EV_SEL0,
	.perf_ctr		= NHMEX_C0_MSR_PMON_CTR0,
	.event_mask		= NHMEX_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_C0_MSR_PMON_GLOBAL_CTL,
	.msr_offsets		= nhmex_cbox_msr_offsets,
	.pair_ctr_ctl		= 1,
	.ops			= &nhmex_uncore_ops,
	.क्रमmat_group		= &nhmex_uncore_cbox_क्रमmat_group
पूर्ण;

अटल काष्ठा uncore_event_desc nhmex_uncore_wbox_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks, "event=0xff,umask=0"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_wbox = अणु
	.name			= "wbox",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_W_MSR_PMON_CNT0,
	.perf_ctr		= NHMEX_W_MSR_PMON_EVT_SEL0,
	.fixed_ctr		= NHMEX_W_MSR_PMON_FIXED_CTR,
	.fixed_ctl		= NHMEX_W_MSR_PMON_FIXED_CTL,
	.event_mask		= NHMEX_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_W_MSR_GLOBAL_CTL,
	.pair_ctr_ctl		= 1,
	.event_descs		= nhmex_uncore_wbox_events,
	.ops			= &nhmex_uncore_ops,
	.क्रमmat_group		= &nhmex_uncore_cbox_क्रमmat_group
पूर्ण;

अटल पूर्णांक nhmex_bbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;
	पूर्णांक ctr, ev_sel;

	ctr = (hwc->config & NHMEX_B_PMON_CTR_MASK) >>
		NHMEX_B_PMON_CTR_SHIFT;
	ev_sel = (hwc->config & NHMEX_B_PMON_CTL_EV_SEL_MASK) >>
		  NHMEX_B_PMON_CTL_EV_SEL_SHIFT;

	/* events that करो not use the match/mask रेजिस्टरs */
	अगर ((ctr == 0 && ev_sel > 0x3) || (ctr == 1 && ev_sel > 0x6) ||
	    (ctr == 2 && ev_sel != 0x4) || ctr == 3)
		वापस 0;

	अगर (box->pmu->pmu_idx == 0)
		reg1->reg = NHMEX_B0_MSR_MATCH;
	अन्यथा
		reg1->reg = NHMEX_B1_MSR_MATCH;
	reg1->idx = 0;
	reg1->config = event->attr.config1;
	reg2->config = event->attr.config2;
	वापस 0;
पूर्ण

अटल व्योम nhmex_bbox_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;

	अगर (reg1->idx != EXTRA_REG_NONE) अणु
		wrmsrl(reg1->reg, reg1->config);
		wrmsrl(reg1->reg + 1, reg2->config);
	पूर्ण
	wrmsrl(hwc->config_base, NHMEX_PMON_CTL_EN_BIT0 |
		(hwc->config & NHMEX_B_PMON_CTL_EV_SEL_MASK));
पूर्ण

/*
 * The Bbox has 4 counters, but each counter monitors dअगरferent events.
 * Use bits 6-7 in the event config to select counter.
 */
अटल काष्ठा event_स्थिरraपूर्णांक nhmex_uncore_bbox_स्थिरraपूर्णांकs[] = अणु
	EVENT_CONSTRAINT(0 , 1, 0xc0),
	EVENT_CONSTRAINT(0x40, 2, 0xc0),
	EVENT_CONSTRAINT(0x80, 4, 0xc0),
	EVENT_CONSTRAINT(0xc0, 8, 0xc0),
	EVENT_CONSTRAINT_END,
पूर्ण;

अटल काष्ठा attribute *nhmex_uncore_bbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event5.attr,
	&क्रमmat_attr_counter.attr,
	&क्रमmat_attr_match.attr,
	&क्रमmat_attr_mask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_bbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = nhmex_uncore_bbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops nhmex_uncore_bbox_ops = अणु
	NHMEX_UNCORE_OPS_COMMON_INIT(),
	.enable_event		= nhmex_bbox_msr_enable_event,
	.hw_config		= nhmex_bbox_hw_config,
	.get_स्थिरraपूर्णांक		= uncore_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= uncore_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_bbox = अणु
	.name			= "bbox",
	.num_counters		= 4,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_B0_MSR_PMON_CTL0,
	.perf_ctr		= NHMEX_B0_MSR_PMON_CTR0,
	.event_mask		= NHMEX_B_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_B0_MSR_PMON_GLOBAL_CTL,
	.msr_offset		= NHMEX_B_MSR_OFFSET,
	.pair_ctr_ctl		= 1,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= nhmex_uncore_bbox_स्थिरraपूर्णांकs,
	.ops			= &nhmex_uncore_bbox_ops,
	.क्रमmat_group		= &nhmex_uncore_bbox_क्रमmat_group
पूर्ण;

अटल पूर्णांक nhmex_sbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;

	/* only TO_R_PROG_EV event uses the match/mask रेजिस्टर */
	अगर ((hwc->config & NHMEX_PMON_CTL_EV_SEL_MASK) !=
	    NHMEX_S_EVENT_TO_R_PROG_EV)
		वापस 0;

	अगर (box->pmu->pmu_idx == 0)
		reg1->reg = NHMEX_S0_MSR_MM_CFG;
	अन्यथा
		reg1->reg = NHMEX_S1_MSR_MM_CFG;
	reg1->idx = 0;
	reg1->config = event->attr.config1;
	reg2->config = event->attr.config2;
	वापस 0;
पूर्ण

अटल व्योम nhmex_sbox_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;

	अगर (reg1->idx != EXTRA_REG_NONE) अणु
		wrmsrl(reg1->reg, 0);
		wrmsrl(reg1->reg + 1, reg1->config);
		wrmsrl(reg1->reg + 2, reg2->config);
		wrmsrl(reg1->reg, NHMEX_S_PMON_MM_CFG_EN);
	पूर्ण
	wrmsrl(hwc->config_base, hwc->config | NHMEX_PMON_CTL_EN_BIT22);
पूर्ण

अटल काष्ठा attribute *nhmex_uncore_sbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_match.attr,
	&क्रमmat_attr_mask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_sbox_क्रमmat_group = अणु
	.name			= "format",
	.attrs			= nhmex_uncore_sbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops nhmex_uncore_sbox_ops = अणु
	NHMEX_UNCORE_OPS_COMMON_INIT(),
	.enable_event		= nhmex_sbox_msr_enable_event,
	.hw_config		= nhmex_sbox_hw_config,
	.get_स्थिरraपूर्णांक		= uncore_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= uncore_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_sbox = अणु
	.name			= "sbox",
	.num_counters		= 4,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_S0_MSR_PMON_CTL0,
	.perf_ctr		= NHMEX_S0_MSR_PMON_CTR0,
	.event_mask		= NHMEX_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_S0_MSR_PMON_GLOBAL_CTL,
	.msr_offset		= NHMEX_S_MSR_OFFSET,
	.pair_ctr_ctl		= 1,
	.num_shared_regs	= 1,
	.ops			= &nhmex_uncore_sbox_ops,
	.क्रमmat_group		= &nhmex_uncore_sbox_क्रमmat_group
पूर्ण;

क्रमागत अणु
	EXTRA_REG_NHMEX_M_FILTER,
	EXTRA_REG_NHMEX_M_DSP,
	EXTRA_REG_NHMEX_M_ISS,
	EXTRA_REG_NHMEX_M_MAP,
	EXTRA_REG_NHMEX_M_MSC_THR,
	EXTRA_REG_NHMEX_M_PGT,
	EXTRA_REG_NHMEX_M_PLD,
	EXTRA_REG_NHMEX_M_ZDP_CTL_FVC,
पूर्ण;

अटल काष्ठा extra_reg nhmex_uncore_mbox_extra_regs[] = अणु
	MBOX_INC_SEL_EXTAR_REG(0x0, DSP),
	MBOX_INC_SEL_EXTAR_REG(0x4, MSC_THR),
	MBOX_INC_SEL_EXTAR_REG(0x5, MSC_THR),
	MBOX_INC_SEL_EXTAR_REG(0x9, ISS),
	/* event 0xa uses two extra रेजिस्टरs */
	MBOX_INC_SEL_EXTAR_REG(0xa, ISS),
	MBOX_INC_SEL_EXTAR_REG(0xa, PLD),
	MBOX_INC_SEL_EXTAR_REG(0xb, PLD),
	/* events 0xd ~ 0x10 use the same extra रेजिस्टर */
	MBOX_INC_SEL_EXTAR_REG(0xd, ZDP_CTL_FVC),
	MBOX_INC_SEL_EXTAR_REG(0xe, ZDP_CTL_FVC),
	MBOX_INC_SEL_EXTAR_REG(0xf, ZDP_CTL_FVC),
	MBOX_INC_SEL_EXTAR_REG(0x10, ZDP_CTL_FVC),
	MBOX_INC_SEL_EXTAR_REG(0x16, PGT),
	MBOX_SET_FLAG_SEL_EXTRA_REG(0x0, DSP),
	MBOX_SET_FLAG_SEL_EXTRA_REG(0x1, ISS),
	MBOX_SET_FLAG_SEL_EXTRA_REG(0x5, PGT),
	MBOX_SET_FLAG_SEL_EXTRA_REG(0x6, MAP),
	EVENT_EXTRA_END
पूर्ण;

/* Nehalem-EX or Wesपंचांगere-EX ? */
अटल bool uncore_nhmex;

अटल bool nhmex_mbox_get_shared_reg(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx, u64 config)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	अचिन्हित दीर्घ flags;
	bool ret = false;
	u64 mask;

	अगर (idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC) अणु
		er = &box->shared_regs[idx];
		raw_spin_lock_irqsave(&er->lock, flags);
		अगर (!atomic_पढ़ो(&er->ref) || er->config == config) अणु
			atomic_inc(&er->ref);
			er->config = config;
			ret = true;
		पूर्ण
		raw_spin_unlock_irqrestore(&er->lock, flags);

		वापस ret;
	पूर्ण
	/*
	 * The ZDP_CTL_FVC MSR has 4 fields which are used to control
	 * events 0xd ~ 0x10. Besides these 4 fields, there are additional
	 * fields which are shared.
	 */
	idx -= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	अगर (WARN_ON_ONCE(idx >= 4))
		वापस false;

	/* mask of the shared fields */
	अगर (uncore_nhmex)
		mask = NHMEX_M_PMON_ZDP_CTL_FVC_MASK;
	अन्यथा
		mask = WSMEX_M_PMON_ZDP_CTL_FVC_MASK;
	er = &box->shared_regs[EXTRA_REG_NHMEX_M_ZDP_CTL_FVC];

	raw_spin_lock_irqsave(&er->lock, flags);
	/* add mask of the non-shared field अगर it's in use */
	अगर (__BITS_VALUE(atomic_पढ़ो(&er->ref), idx, 8)) अणु
		अगर (uncore_nhmex)
			mask |= NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		अन्यथा
			mask |= WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	पूर्ण

	अगर (!atomic_पढ़ो(&er->ref) || !((er->config ^ config) & mask)) अणु
		atomic_add(1 << (idx * 8), &er->ref);
		अगर (uncore_nhmex)
			mask = NHMEX_M_PMON_ZDP_CTL_FVC_MASK |
				NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		अन्यथा
			mask = WSMEX_M_PMON_ZDP_CTL_FVC_MASK |
				WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
		er->config &= ~mask;
		er->config |= (config & mask);
		ret = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&er->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम nhmex_mbox_put_shared_reg(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;

	अगर (idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC) अणु
		er = &box->shared_regs[idx];
		atomic_dec(&er->ref);
		वापस;
	पूर्ण

	idx -= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	er = &box->shared_regs[EXTRA_REG_NHMEX_M_ZDP_CTL_FVC];
	atomic_sub(1 << (idx * 8), &er->ref);
पूर्ण

अटल u64 nhmex_mbox_alter_er(काष्ठा perf_event *event, पूर्णांक new_idx, bool modअगरy)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	u64 idx, orig_idx = __BITS_VALUE(reg1->idx, 0, 8);
	u64 config = reg1->config;

	/* get the non-shared control bits and shअगरt them */
	idx = orig_idx - EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
	अगर (uncore_nhmex)
		config &= NHMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	अन्यथा
		config &= WSMEX_M_PMON_ZDP_CTL_FVC_EVENT_MASK(idx);
	अगर (new_idx > orig_idx) अणु
		idx = new_idx - orig_idx;
		config <<= 3 * idx;
	पूर्ण अन्यथा अणु
		idx = orig_idx - new_idx;
		config >>= 3 * idx;
	पूर्ण

	/* add the shared control bits back */
	अगर (uncore_nhmex)
		config |= NHMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	अन्यथा
		config |= WSMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	config |= NHMEX_M_PMON_ZDP_CTL_FVC_MASK & reg1->config;
	अगर (modअगरy) अणु
		/* adjust the मुख्य event selector */
		अगर (new_idx > orig_idx)
			hwc->config += idx << NHMEX_M_PMON_CTL_INC_SEL_SHIFT;
		अन्यथा
			hwc->config -= idx << NHMEX_M_PMON_CTL_INC_SEL_SHIFT;
		reg1->config = config;
		reg1->idx = ~0xff | new_idx;
	पूर्ण
	वापस config;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
nhmex_mbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	पूर्णांक i, idx[2], alloc = 0;
	u64 config1 = reg1->config;

	idx[0] = __BITS_VALUE(reg1->idx, 0, 8);
	idx[1] = __BITS_VALUE(reg1->idx, 1, 8);
again:
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!uncore_box_is_fake(box) && (reg1->alloc & (0x1 << i)))
			idx[i] = 0xff;

		अगर (idx[i] == 0xff)
			जारी;

		अगर (!nhmex_mbox_get_shared_reg(box, idx[i],
				__BITS_VALUE(config1, i, 32)))
			जाओ fail;
		alloc |= (0x1 << i);
	पूर्ण

	/* क्रम the match/mask रेजिस्टरs */
	अगर (reg2->idx != EXTRA_REG_NONE &&
	    (uncore_box_is_fake(box) || !reg2->alloc) &&
	    !nhmex_mbox_get_shared_reg(box, reg2->idx, reg2->config))
		जाओ fail;

	/*
	 * If it's a fake box -- as per validate_अणुgroup,eventपूर्ण() we
	 * shouldn't touch event state and we can aव्योम करोing so
	 * since both will only call get_event_स्थिरraपूर्णांकs() once
	 * on each event, this aव्योमs the need क्रम reg->alloc.
	 */
	अगर (!uncore_box_is_fake(box)) अणु
		अगर (idx[0] != 0xff && idx[0] != __BITS_VALUE(reg1->idx, 0, 8))
			nhmex_mbox_alter_er(event, idx[0], true);
		reg1->alloc |= alloc;
		अगर (reg2->idx != EXTRA_REG_NONE)
			reg2->alloc = 1;
	पूर्ण
	वापस शून्य;
fail:
	अगर (idx[0] != 0xff && !(alloc & 0x1) &&
	    idx[0] >= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC) अणु
		/*
		 * events 0xd ~ 0x10 are functional identical, but are
		 * controlled by dअगरferent fields in the ZDP_CTL_FVC
		 * रेजिस्टर. If we failed to take one field, try the
		 * rest 3 choices.
		 */
		BUG_ON(__BITS_VALUE(reg1->idx, 1, 8) != 0xff);
		idx[0] -= EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
		idx[0] = (idx[0] + 1) % 4;
		idx[0] += EXTRA_REG_NHMEX_M_ZDP_CTL_FVC;
		अगर (idx[0] != __BITS_VALUE(reg1->idx, 0, 8)) अणु
			config1 = nhmex_mbox_alter_er(event, idx[0], false);
			जाओ again;
		पूर्ण
	पूर्ण

	अगर (alloc & 0x1)
		nhmex_mbox_put_shared_reg(box, idx[0]);
	अगर (alloc & 0x2)
		nhmex_mbox_put_shared_reg(box, idx[1]);
	वापस &uncore_स्थिरraपूर्णांक_empty;
पूर्ण

अटल व्योम nhmex_mbox_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &event->hw.branch_reg;

	अगर (uncore_box_is_fake(box))
		वापस;

	अगर (reg1->alloc & 0x1)
		nhmex_mbox_put_shared_reg(box, __BITS_VALUE(reg1->idx, 0, 8));
	अगर (reg1->alloc & 0x2)
		nhmex_mbox_put_shared_reg(box, __BITS_VALUE(reg1->idx, 1, 8));
	reg1->alloc = 0;

	अगर (reg2->alloc) अणु
		nhmex_mbox_put_shared_reg(box, reg2->idx);
		reg2->alloc = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक nhmex_mbox_extra_reg_idx(काष्ठा extra_reg *er)
अणु
	अगर (er->idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC)
		वापस er->idx;
	वापस er->idx + (er->event >> NHMEX_M_PMON_CTL_INC_SEL_SHIFT) - 0xd;
पूर्ण

अटल पूर्णांक nhmex_mbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	काष्ठा extra_reg *er;
	अचिन्हित msr;
	पूर्णांक reg_idx = 0;
	/*
	 * The mbox events may require 2 extra MSRs at the most. But only
	 * the lower 32 bits in these MSRs are signअगरicant, so we can use
	 * config1 to pass two MSRs' config.
	 */
	क्रम (er = nhmex_uncore_mbox_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		अगर (event->attr.config1 & ~er->valid_mask)
			वापस -EINVAL;

		msr = er->msr + type->msr_offset * box->pmu->pmu_idx;
		अगर (WARN_ON_ONCE(msr >= 0xffff || er->idx >= 0xff))
			वापस -EINVAL;

		/* always use the 32~63 bits to pass the PLD config */
		अगर (er->idx == EXTRA_REG_NHMEX_M_PLD)
			reg_idx = 1;
		अन्यथा अगर (WARN_ON_ONCE(reg_idx > 0))
			वापस -EINVAL;

		reg1->idx &= ~(0xff << (reg_idx * 8));
		reg1->reg &= ~(0xffff << (reg_idx * 16));
		reg1->idx |= nhmex_mbox_extra_reg_idx(er) << (reg_idx * 8);
		reg1->reg |= msr << (reg_idx * 16);
		reg1->config = event->attr.config1;
		reg_idx++;
	पूर्ण
	/*
	 * The mbox only provides ability to perक्रमm address matching
	 * क्रम the PLD events.
	 */
	अगर (reg_idx == 2) अणु
		reg2->idx = EXTRA_REG_NHMEX_M_FILTER;
		अगर (event->attr.config2 & NHMEX_M_PMON_MM_CFG_EN)
			reg2->config = event->attr.config2;
		अन्यथा
			reg2->config = ~0ULL;
		अगर (box->pmu->pmu_idx == 0)
			reg2->reg = NHMEX_M0_MSR_PMU_MM_CFG;
		अन्यथा
			reg2->reg = NHMEX_M1_MSR_PMU_MM_CFG;
	पूर्ण
	वापस 0;
पूर्ण

अटल u64 nhmex_mbox_shared_reg_config(काष्ठा पूर्णांकel_uncore_box *box, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	अचिन्हित दीर्घ flags;
	u64 config;

	अगर (idx < EXTRA_REG_NHMEX_M_ZDP_CTL_FVC)
		वापस box->shared_regs[idx].config;

	er = &box->shared_regs[EXTRA_REG_NHMEX_M_ZDP_CTL_FVC];
	raw_spin_lock_irqsave(&er->lock, flags);
	config = er->config;
	raw_spin_unlock_irqrestore(&er->lock, flags);
	वापस config;
पूर्ण

अटल व्योम nhmex_mbox_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;
	पूर्णांक idx;

	idx = __BITS_VALUE(reg1->idx, 0, 8);
	अगर (idx != 0xff)
		wrmsrl(__BITS_VALUE(reg1->reg, 0, 16),
			nhmex_mbox_shared_reg_config(box, idx));
	idx = __BITS_VALUE(reg1->idx, 1, 8);
	अगर (idx != 0xff)
		wrmsrl(__BITS_VALUE(reg1->reg, 1, 16),
			nhmex_mbox_shared_reg_config(box, idx));

	अगर (reg2->idx != EXTRA_REG_NONE) अणु
		wrmsrl(reg2->reg, 0);
		अगर (reg2->config != ~0ULL) अणु
			wrmsrl(reg2->reg + 1,
				reg2->config & NHMEX_M_PMON_ADDR_MATCH_MASK);
			wrmsrl(reg2->reg + 2, NHMEX_M_PMON_ADDR_MASK_MASK &
				(reg2->config >> NHMEX_M_PMON_ADDR_MASK_SHIFT));
			wrmsrl(reg2->reg, NHMEX_M_PMON_MM_CFG_EN);
		पूर्ण
	पूर्ण

	wrmsrl(hwc->config_base, hwc->config | NHMEX_PMON_CTL_EN_BIT0);
पूर्ण

DEFINE_UNCORE_FORMAT_ATTR(count_mode,		count_mode,	"config:2-3");
DEFINE_UNCORE_FORMAT_ATTR(storage_mode,		storage_mode,	"config:4-5");
DEFINE_UNCORE_FORMAT_ATTR(wrap_mode,		wrap_mode,	"config:6");
DEFINE_UNCORE_FORMAT_ATTR(flag_mode,		flag_mode,	"config:7");
DEFINE_UNCORE_FORMAT_ATTR(inc_sel,		inc_sel,	"config:9-13");
DEFINE_UNCORE_FORMAT_ATTR(set_flag_sel,		set_flag_sel,	"config:19-21");
DEFINE_UNCORE_FORMAT_ATTR(filter_cfg_en,	filter_cfg_en,	"config2:63");
DEFINE_UNCORE_FORMAT_ATTR(filter_match,		filter_match,	"config2:0-33");
DEFINE_UNCORE_FORMAT_ATTR(filter_mask,		filter_mask,	"config2:34-61");
DEFINE_UNCORE_FORMAT_ATTR(dsp,			dsp,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(thr,			thr,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(fvc,			fvc,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(pgt,			pgt,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(map,			map,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(iss,			iss,		"config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(pld,			pld,		"config1:32-63");

अटल काष्ठा attribute *nhmex_uncore_mbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_count_mode.attr,
	&क्रमmat_attr_storage_mode.attr,
	&क्रमmat_attr_wrap_mode.attr,
	&क्रमmat_attr_flag_mode.attr,
	&क्रमmat_attr_inc_sel.attr,
	&क्रमmat_attr_set_flag_sel.attr,
	&क्रमmat_attr_filter_cfg_en.attr,
	&क्रमmat_attr_filter_match.attr,
	&क्रमmat_attr_filter_mask.attr,
	&क्रमmat_attr_dsp.attr,
	&क्रमmat_attr_thr.attr,
	&क्रमmat_attr_fvc.attr,
	&क्रमmat_attr_pgt.attr,
	&क्रमmat_attr_map.attr,
	&क्रमmat_attr_iss.attr,
	&क्रमmat_attr_pld.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_mbox_क्रमmat_group = अणु
	.name		= "format",
	.attrs		= nhmex_uncore_mbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा uncore_event_desc nhmex_uncore_mbox_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(bbox_cmds_पढ़ो, "inc_sel=0xd,fvc=0x2800"),
	INTEL_UNCORE_EVENT_DESC(bbox_cmds_ग_लिखो, "inc_sel=0xd,fvc=0x2820"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc wsmex_uncore_mbox_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(bbox_cmds_पढ़ो, "inc_sel=0xd,fvc=0x5000"),
	INTEL_UNCORE_EVENT_DESC(bbox_cmds_ग_लिखो, "inc_sel=0xd,fvc=0x5040"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops nhmex_uncore_mbox_ops = अणु
	NHMEX_UNCORE_OPS_COMMON_INIT(),
	.enable_event	= nhmex_mbox_msr_enable_event,
	.hw_config	= nhmex_mbox_hw_config,
	.get_स्थिरraपूर्णांक	= nhmex_mbox_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक	= nhmex_mbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_mbox = अणु
	.name			= "mbox",
	.num_counters		= 6,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_M0_MSR_PMU_CTL0,
	.perf_ctr		= NHMEX_M0_MSR_PMU_CNT0,
	.event_mask		= NHMEX_M_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_M0_MSR_GLOBAL_CTL,
	.msr_offset		= NHMEX_M_MSR_OFFSET,
	.pair_ctr_ctl		= 1,
	.num_shared_regs	= 8,
	.event_descs		= nhmex_uncore_mbox_events,
	.ops			= &nhmex_uncore_mbox_ops,
	.क्रमmat_group		= &nhmex_uncore_mbox_क्रमmat_group,
पूर्ण;

अटल व्योम nhmex_rbox_alter_er(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;

	/* adjust the मुख्य event selector and extra रेजिस्टर index */
	अगर (reg1->idx % 2) अणु
		reg1->idx--;
		hwc->config -= 1 << NHMEX_R_PMON_CTL_EV_SEL_SHIFT;
	पूर्ण अन्यथा अणु
		reg1->idx++;
		hwc->config += 1 << NHMEX_R_PMON_CTL_EV_SEL_SHIFT;
	पूर्ण

	/* adjust extra रेजिस्टर config */
	चयन (reg1->idx % 6) अणु
	हाल 2:
		/* shअगरt the 8~15 bits to the 0~7 bits */
		reg1->config >>= 8;
		अवरोध;
	हाल 3:
		/* shअगरt the 0~7 bits to the 8~15 bits */
		reg1->config <<= 8;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Each rbox has 4 event set which monitor PQI port 0~3 or 4~7.
 * An event set consists of 6 events, the 3rd and 4th events in
 * an event set use the same extra रेजिस्टर. So an event set uses
 * 5 extra रेजिस्टरs.
 */
अटल काष्ठा event_स्थिरraपूर्णांक *
nhmex_rbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	अचिन्हित दीर्घ flags;
	पूर्णांक idx, er_idx;
	u64 config1;
	bool ok = false;

	अगर (!uncore_box_is_fake(box) && reg1->alloc)
		वापस शून्य;

	idx = reg1->idx % 6;
	config1 = reg1->config;
again:
	er_idx = idx;
	/* the 3rd and 4th events use the same extra रेजिस्टर */
	अगर (er_idx > 2)
		er_idx--;
	er_idx += (reg1->idx / 6) * 5;

	er = &box->shared_regs[er_idx];
	raw_spin_lock_irqsave(&er->lock, flags);
	अगर (idx < 2) अणु
		अगर (!atomic_पढ़ो(&er->ref) || er->config == reg1->config) अणु
			atomic_inc(&er->ref);
			er->config = reg1->config;
			ok = true;
		पूर्ण
	पूर्ण अन्यथा अगर (idx == 2 || idx == 3) अणु
		/*
		 * these two events use dअगरferent fields in a extra रेजिस्टर,
		 * the 0~7 bits and the 8~15 bits respectively.
		 */
		u64 mask = 0xff << ((idx - 2) * 8);
		अगर (!__BITS_VALUE(atomic_पढ़ो(&er->ref), idx - 2, 8) ||
				!((er->config ^ config1) & mask)) अणु
			atomic_add(1 << ((idx - 2) * 8), &er->ref);
			er->config &= ~mask;
			er->config |= config1 & mask;
			ok = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&er->ref) ||
				(er->config == (hwc->config >> 32) &&
				 er->config1 == reg1->config &&
				 er->config2 == reg2->config)) अणु
			atomic_inc(&er->ref);
			er->config = (hwc->config >> 32);
			er->config1 = reg1->config;
			er->config2 = reg2->config;
			ok = true;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&er->lock, flags);

	अगर (!ok) अणु
		/*
		 * The Rbox events are always in pairs. The paired
		 * events are functional identical, but use dअगरferent
		 * extra रेजिस्टरs. If we failed to take an extra
		 * रेजिस्टर, try the alternative.
		 */
		idx ^= 1;
		अगर (idx != reg1->idx % 6) अणु
			अगर (idx == 2)
				config1 >>= 8;
			अन्यथा अगर (idx == 3)
				config1 <<= 8;
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!uncore_box_is_fake(box)) अणु
			अगर (idx != reg1->idx % 6)
				nhmex_rbox_alter_er(box, event);
			reg1->alloc = 1;
		पूर्ण
		वापस शून्य;
	पूर्ण
	वापस &uncore_स्थिरraपूर्णांक_empty;
पूर्ण

अटल व्योम nhmex_rbox_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_extra_reg *er;
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	पूर्णांक idx, er_idx;

	अगर (uncore_box_is_fake(box) || !reg1->alloc)
		वापस;

	idx = reg1->idx % 6;
	er_idx = idx;
	अगर (er_idx > 2)
		er_idx--;
	er_idx += (reg1->idx / 6) * 5;

	er = &box->shared_regs[er_idx];
	अगर (idx == 2 || idx == 3)
		atomic_sub(1 << ((idx - 2) * 8), &er->ref);
	अन्यथा
		atomic_dec(&er->ref);

	reg1->alloc = 0;
पूर्ण

अटल पूर्णांक nhmex_rbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &event->hw.branch_reg;
	पूर्णांक idx;

	idx = (event->hw.config & NHMEX_R_PMON_CTL_EV_SEL_MASK) >>
		NHMEX_R_PMON_CTL_EV_SEL_SHIFT;
	अगर (idx >= 0x18)
		वापस -EINVAL;

	reg1->idx = idx;
	reg1->config = event->attr.config1;

	चयन (idx % 6) अणु
	हाल 4:
	हाल 5:
		hwc->config |= event->attr.config & (~0ULL << 32);
		reg2->config = event->attr.config2;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nhmex_rbox_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;
	पूर्णांक idx, port;

	idx = reg1->idx;
	port = idx / 6 + box->pmu->pmu_idx * 4;

	चयन (idx % 6) अणु
	हाल 0:
		wrmsrl(NHMEX_R_MSR_PORTN_IPERF_CFG0(port), reg1->config);
		अवरोध;
	हाल 1:
		wrmsrl(NHMEX_R_MSR_PORTN_IPERF_CFG1(port), reg1->config);
		अवरोध;
	हाल 2:
	हाल 3:
		wrmsrl(NHMEX_R_MSR_PORTN_QLX_CFG(port),
			uncore_shared_reg_config(box, 2 + (idx / 6) * 5));
		अवरोध;
	हाल 4:
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(port),
			hwc->config >> 32);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MATCH(port), reg1->config);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MASK(port), reg2->config);
		अवरोध;
	हाल 5:
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(port),
			hwc->config >> 32);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MATCH(port), reg1->config);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MASK(port), reg2->config);
		अवरोध;
	पूर्ण

	wrmsrl(hwc->config_base, NHMEX_PMON_CTL_EN_BIT0 |
		(hwc->config & NHMEX_R_PMON_CTL_EV_SEL_MASK));
पूर्ण

DEFINE_UNCORE_FORMAT_ATTR(xbr_mm_cfg, xbr_mm_cfg, "config:32-63");
DEFINE_UNCORE_FORMAT_ATTR(xbr_match, xbr_match, "config1:0-63");
DEFINE_UNCORE_FORMAT_ATTR(xbr_mask, xbr_mask, "config2:0-63");
DEFINE_UNCORE_FORMAT_ATTR(qlx_cfg, qlx_cfg, "config1:0-15");
DEFINE_UNCORE_FORMAT_ATTR(iperf_cfg, iperf_cfg, "config1:0-31");

अटल काष्ठा attribute *nhmex_uncore_rbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event5.attr,
	&क्रमmat_attr_xbr_mm_cfg.attr,
	&क्रमmat_attr_xbr_match.attr,
	&क्रमmat_attr_xbr_mask.attr,
	&क्रमmat_attr_qlx_cfg.attr,
	&क्रमmat_attr_iperf_cfg.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhmex_uncore_rbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = nhmex_uncore_rbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा uncore_event_desc nhmex_uncore_rbox_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(qpi0_flit_send,		"event=0x0,iperf_cfg=0x80000000"),
	INTEL_UNCORE_EVENT_DESC(qpi1_filt_send,		"event=0x6,iperf_cfg=0x80000000"),
	INTEL_UNCORE_EVENT_DESC(qpi0_idle_filt,		"event=0x0,iperf_cfg=0x40000000"),
	INTEL_UNCORE_EVENT_DESC(qpi1_idle_filt,		"event=0x6,iperf_cfg=0x40000000"),
	INTEL_UNCORE_EVENT_DESC(qpi0_date_response,	"event=0x0,iperf_cfg=0xc4"),
	INTEL_UNCORE_EVENT_DESC(qpi1_date_response,	"event=0x6,iperf_cfg=0xc4"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops nhmex_uncore_rbox_ops = अणु
	NHMEX_UNCORE_OPS_COMMON_INIT(),
	.enable_event		= nhmex_rbox_msr_enable_event,
	.hw_config		= nhmex_rbox_hw_config,
	.get_स्थिरraपूर्णांक		= nhmex_rbox_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= nhmex_rbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhmex_uncore_rbox = अणु
	.name			= "rbox",
	.num_counters		= 8,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.event_ctl		= NHMEX_R_MSR_PMON_CTL0,
	.perf_ctr		= NHMEX_R_MSR_PMON_CNT0,
	.event_mask		= NHMEX_R_PMON_RAW_EVENT_MASK,
	.box_ctl		= NHMEX_R_MSR_GLOBAL_CTL,
	.msr_offset		= NHMEX_R_MSR_OFFSET,
	.pair_ctr_ctl		= 1,
	.num_shared_regs	= 20,
	.event_descs		= nhmex_uncore_rbox_events,
	.ops			= &nhmex_uncore_rbox_ops,
	.क्रमmat_group		= &nhmex_uncore_rbox_क्रमmat_group
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *nhmex_msr_uncores[] = अणु
	&nhmex_uncore_ubox,
	&nhmex_uncore_cbox,
	&nhmex_uncore_bbox,
	&nhmex_uncore_sbox,
	&nhmex_uncore_mbox,
	&nhmex_uncore_rbox,
	&nhmex_uncore_wbox,
	शून्य,
पूर्ण;

व्योम nhmex_uncore_cpu_init(व्योम)
अणु
	अगर (boot_cpu_data.x86_model == 46)
		uncore_nhmex = true;
	अन्यथा
		nhmex_uncore_mbox.event_descs = wsmex_uncore_mbox_events;
	अगर (nhmex_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		nhmex_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = nhmex_msr_uncores;
पूर्ण
/* end of Nehalem-EX uncore support */
