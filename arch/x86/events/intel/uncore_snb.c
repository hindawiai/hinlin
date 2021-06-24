<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Nehalem/SandBridge/Haswell/Broadwell/Skylake uncore support */
#समावेश "uncore.h"

/* Uncore IMC PCI IDs */
#घोषणा PCI_DEVICE_ID_INTEL_SNB_IMC		0x0100
#घोषणा PCI_DEVICE_ID_INTEL_IVB_IMC		0x0154
#घोषणा PCI_DEVICE_ID_INTEL_IVB_E3_IMC		0x0150
#घोषणा PCI_DEVICE_ID_INTEL_HSW_IMC		0x0c00
#घोषणा PCI_DEVICE_ID_INTEL_HSW_U_IMC		0x0a04
#घोषणा PCI_DEVICE_ID_INTEL_BDW_IMC		0x1604
#घोषणा PCI_DEVICE_ID_INTEL_SKL_U_IMC		0x1904
#घोषणा PCI_DEVICE_ID_INTEL_SKL_Y_IMC		0x190c
#घोषणा PCI_DEVICE_ID_INTEL_SKL_HD_IMC		0x1900
#घोषणा PCI_DEVICE_ID_INTEL_SKL_HQ_IMC		0x1910
#घोषणा PCI_DEVICE_ID_INTEL_SKL_SD_IMC		0x190f
#घोषणा PCI_DEVICE_ID_INTEL_SKL_SQ_IMC		0x191f
#घोषणा PCI_DEVICE_ID_INTEL_SKL_E3_IMC		0x1918
#घोषणा PCI_DEVICE_ID_INTEL_KBL_Y_IMC		0x590c
#घोषणा PCI_DEVICE_ID_INTEL_KBL_U_IMC		0x5904
#घोषणा PCI_DEVICE_ID_INTEL_KBL_UQ_IMC		0x5914
#घोषणा PCI_DEVICE_ID_INTEL_KBL_SD_IMC		0x590f
#घोषणा PCI_DEVICE_ID_INTEL_KBL_SQ_IMC		0x591f
#घोषणा PCI_DEVICE_ID_INTEL_KBL_HQ_IMC		0x5910
#घोषणा PCI_DEVICE_ID_INTEL_KBL_WQ_IMC		0x5918
#घोषणा PCI_DEVICE_ID_INTEL_CFL_2U_IMC		0x3ecc
#घोषणा PCI_DEVICE_ID_INTEL_CFL_4U_IMC		0x3ed0
#घोषणा PCI_DEVICE_ID_INTEL_CFL_4H_IMC		0x3e10
#घोषणा PCI_DEVICE_ID_INTEL_CFL_6H_IMC		0x3ec4
#घोषणा PCI_DEVICE_ID_INTEL_CFL_2S_D_IMC	0x3e0f
#घोषणा PCI_DEVICE_ID_INTEL_CFL_4S_D_IMC	0x3e1f
#घोषणा PCI_DEVICE_ID_INTEL_CFL_6S_D_IMC	0x3ec2
#घोषणा PCI_DEVICE_ID_INTEL_CFL_8S_D_IMC	0x3e30
#घोषणा PCI_DEVICE_ID_INTEL_CFL_4S_W_IMC	0x3e18
#घोषणा PCI_DEVICE_ID_INTEL_CFL_6S_W_IMC	0x3ec6
#घोषणा PCI_DEVICE_ID_INTEL_CFL_8S_W_IMC	0x3e31
#घोषणा PCI_DEVICE_ID_INTEL_CFL_4S_S_IMC	0x3e33
#घोषणा PCI_DEVICE_ID_INTEL_CFL_6S_S_IMC	0x3eca
#घोषणा PCI_DEVICE_ID_INTEL_CFL_8S_S_IMC	0x3e32
#घोषणा PCI_DEVICE_ID_INTEL_AML_YD_IMC		0x590c
#घोषणा PCI_DEVICE_ID_INTEL_AML_YQ_IMC		0x590d
#घोषणा PCI_DEVICE_ID_INTEL_WHL_UQ_IMC		0x3ed0
#घोषणा PCI_DEVICE_ID_INTEL_WHL_4_UQ_IMC	0x3e34
#घोषणा PCI_DEVICE_ID_INTEL_WHL_UD_IMC		0x3e35
#घोषणा PCI_DEVICE_ID_INTEL_CML_H1_IMC		0x9b44
#घोषणा PCI_DEVICE_ID_INTEL_CML_H2_IMC		0x9b54
#घोषणा PCI_DEVICE_ID_INTEL_CML_H3_IMC		0x9b64
#घोषणा PCI_DEVICE_ID_INTEL_CML_U1_IMC		0x9b51
#घोषणा PCI_DEVICE_ID_INTEL_CML_U2_IMC		0x9b61
#घोषणा PCI_DEVICE_ID_INTEL_CML_U3_IMC		0x9b71
#घोषणा PCI_DEVICE_ID_INTEL_CML_S1_IMC		0x9b33
#घोषणा PCI_DEVICE_ID_INTEL_CML_S2_IMC		0x9b43
#घोषणा PCI_DEVICE_ID_INTEL_CML_S3_IMC		0x9b53
#घोषणा PCI_DEVICE_ID_INTEL_CML_S4_IMC		0x9b63
#घोषणा PCI_DEVICE_ID_INTEL_CML_S5_IMC		0x9b73
#घोषणा PCI_DEVICE_ID_INTEL_ICL_U_IMC		0x8a02
#घोषणा PCI_DEVICE_ID_INTEL_ICL_U2_IMC		0x8a12
#घोषणा PCI_DEVICE_ID_INTEL_TGL_U1_IMC		0x9a02
#घोषणा PCI_DEVICE_ID_INTEL_TGL_U2_IMC		0x9a04
#घोषणा PCI_DEVICE_ID_INTEL_TGL_U3_IMC		0x9a12
#घोषणा PCI_DEVICE_ID_INTEL_TGL_U4_IMC		0x9a14
#घोषणा PCI_DEVICE_ID_INTEL_TGL_H_IMC		0x9a36
#घोषणा PCI_DEVICE_ID_INTEL_RKL_1_IMC		0x4c43
#घोषणा PCI_DEVICE_ID_INTEL_RKL_2_IMC		0x4c53
#घोषणा PCI_DEVICE_ID_INTEL_ADL_1_IMC		0x4660
#घोषणा PCI_DEVICE_ID_INTEL_ADL_2_IMC		0x4641

/* SNB event control */
#घोषणा SNB_UNC_CTL_EV_SEL_MASK			0x000000ff
#घोषणा SNB_UNC_CTL_UMASK_MASK			0x0000ff00
#घोषणा SNB_UNC_CTL_EDGE_DET			(1 << 18)
#घोषणा SNB_UNC_CTL_EN				(1 << 22)
#घोषणा SNB_UNC_CTL_INVERT			(1 << 23)
#घोषणा SNB_UNC_CTL_CMASK_MASK			0x1f000000
#घोषणा NHM_UNC_CTL_CMASK_MASK			0xff000000
#घोषणा NHM_UNC_FIXED_CTR_CTL_EN		(1 << 0)

#घोषणा SNB_UNC_RAW_EVENT_MASK			(SNB_UNC_CTL_EV_SEL_MASK | \
						 SNB_UNC_CTL_UMASK_MASK | \
						 SNB_UNC_CTL_EDGE_DET | \
						 SNB_UNC_CTL_INVERT | \
						 SNB_UNC_CTL_CMASK_MASK)

#घोषणा NHM_UNC_RAW_EVENT_MASK			(SNB_UNC_CTL_EV_SEL_MASK | \
						 SNB_UNC_CTL_UMASK_MASK | \
						 SNB_UNC_CTL_EDGE_DET | \
						 SNB_UNC_CTL_INVERT | \
						 NHM_UNC_CTL_CMASK_MASK)

/* SNB global control रेजिस्टर */
#घोषणा SNB_UNC_PERF_GLOBAL_CTL                 0x391
#घोषणा SNB_UNC_FIXED_CTR_CTRL                  0x394
#घोषणा SNB_UNC_FIXED_CTR                       0x395

/* SNB uncore global control */
#घोषणा SNB_UNC_GLOBAL_CTL_CORE_ALL             ((1 << 4) - 1)
#घोषणा SNB_UNC_GLOBAL_CTL_EN                   (1 << 29)

/* SNB Cbo रेजिस्टर */
#घोषणा SNB_UNC_CBO_0_PERFEVTSEL0               0x700
#घोषणा SNB_UNC_CBO_0_PER_CTR0                  0x706
#घोषणा SNB_UNC_CBO_MSR_OFFSET                  0x10

/* SNB ARB रेजिस्टर */
#घोषणा SNB_UNC_ARB_PER_CTR0			0x3b0
#घोषणा SNB_UNC_ARB_PERFEVTSEL0			0x3b2
#घोषणा SNB_UNC_ARB_MSR_OFFSET			0x10

/* NHM global control रेजिस्टर */
#घोषणा NHM_UNC_PERF_GLOBAL_CTL                 0x391
#घोषणा NHM_UNC_FIXED_CTR                       0x394
#घोषणा NHM_UNC_FIXED_CTR_CTRL                  0x395

/* NHM uncore global control */
#घोषणा NHM_UNC_GLOBAL_CTL_EN_PC_ALL            ((1ULL << 8) - 1)
#घोषणा NHM_UNC_GLOBAL_CTL_EN_FC                (1ULL << 32)

/* NHM uncore रेजिस्टर */
#घोषणा NHM_UNC_PERFEVTSEL0                     0x3c0
#घोषणा NHM_UNC_UNCORE_PMC0                     0x3b0

/* SKL uncore global control */
#घोषणा SKL_UNC_PERF_GLOBAL_CTL			0xe01
#घोषणा SKL_UNC_GLOBAL_CTL_CORE_ALL		((1 << 5) - 1)

/* ICL Cbo रेजिस्टर */
#घोषणा ICL_UNC_CBO_CONFIG			0x396
#घोषणा ICL_UNC_NUM_CBO_MASK			0xf
#घोषणा ICL_UNC_CBO_0_PER_CTR0			0x702
#घोषणा ICL_UNC_CBO_MSR_OFFSET			0x8

/* ICL ARB रेजिस्टर */
#घोषणा ICL_UNC_ARB_PER_CTR			0x3b1
#घोषणा ICL_UNC_ARB_PERFEVTSEL			0x3b3

/* ADL uncore global control */
#घोषणा ADL_UNC_PERF_GLOBAL_CTL			0x2ff0
#घोषणा ADL_UNC_FIXED_CTR_CTRL                  0x2fde
#घोषणा ADL_UNC_FIXED_CTR                       0x2fdf

/* ADL Cbo रेजिस्टर */
#घोषणा ADL_UNC_CBO_0_PER_CTR0			0x2002
#घोषणा ADL_UNC_CBO_0_PERFEVTSEL0		0x2000
#घोषणा ADL_UNC_CTL_THRESHOLD			0x3f000000
#घोषणा ADL_UNC_RAW_EVENT_MASK			(SNB_UNC_CTL_EV_SEL_MASK | \
						 SNB_UNC_CTL_UMASK_MASK | \
						 SNB_UNC_CTL_EDGE_DET | \
						 SNB_UNC_CTL_INVERT | \
						 ADL_UNC_CTL_THRESHOLD)

/* ADL ARB रेजिस्टर */
#घोषणा ADL_UNC_ARB_PER_CTR0			0x2FD2
#घोषणा ADL_UNC_ARB_PERFEVTSEL0			0x2FD0
#घोषणा ADL_UNC_ARB_MSR_OFFSET			0x8

DEFINE_UNCORE_FORMAT_ATTR(event, event, "config:0-7");
DEFINE_UNCORE_FORMAT_ATTR(umask, umask, "config:8-15");
DEFINE_UNCORE_FORMAT_ATTR(edge, edge, "config:18");
DEFINE_UNCORE_FORMAT_ATTR(inv, inv, "config:23");
DEFINE_UNCORE_FORMAT_ATTR(cmask5, cmask, "config:24-28");
DEFINE_UNCORE_FORMAT_ATTR(cmask8, cmask, "config:24-31");
DEFINE_UNCORE_FORMAT_ATTR(threshold, threshold, "config:24-29");

/* Sandy Bridge uncore support */
अटल व्योम snb_uncore_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (hwc->idx < UNCORE_PMC_IDX_FIXED)
		wrmsrl(hwc->config_base, hwc->config | SNB_UNC_CTL_EN);
	अन्यथा
		wrmsrl(hwc->config_base, SNB_UNC_CTL_EN);
पूर्ण

अटल व्योम snb_uncore_msr_disable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	wrmsrl(event->hw.config_base, 0);
पूर्ण

अटल व्योम snb_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0) अणु
		wrmsrl(SNB_UNC_PERF_GLOBAL_CTL,
			SNB_UNC_GLOBAL_CTL_EN | SNB_UNC_GLOBAL_CTL_CORE_ALL);
	पूर्ण
पूर्ण

अटल व्योम snb_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(SNB_UNC_PERF_GLOBAL_CTL,
		SNB_UNC_GLOBAL_CTL_EN | SNB_UNC_GLOBAL_CTL_CORE_ALL);
पूर्ण

अटल व्योम snb_uncore_msr_निकास_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(SNB_UNC_PERF_GLOBAL_CTL, 0);
पूर्ण

अटल काष्ठा uncore_event_desc snb_uncore_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks, "event=0xff,umask=0x00"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा attribute *snb_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask5.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snb_uncore_क्रमmat_group = अणु
	.name		= "format",
	.attrs		= snb_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops snb_uncore_msr_ops = अणु
	.init_box	= snb_uncore_msr_init_box,
	.enable_box	= snb_uncore_msr_enable_box,
	.निकास_box	= snb_uncore_msr_निकास_box,
	.disable_event	= snb_uncore_msr_disable_event,
	.enable_event	= snb_uncore_msr_enable_event,
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक snb_uncore_arb_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x80, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x83, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snb_uncore_cbox = अणु
	.name		= "cbox",
	.num_counters   = 2,
	.num_boxes	= 4,
	.perf_ctr_bits	= 44,
	.fixed_ctr_bits	= 48,
	.perf_ctr	= SNB_UNC_CBO_0_PER_CTR0,
	.event_ctl	= SNB_UNC_CBO_0_PERFEVTSEL0,
	.fixed_ctr	= SNB_UNC_FIXED_CTR,
	.fixed_ctl	= SNB_UNC_FIXED_CTR_CTRL,
	.single_fixed	= 1,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.msr_offset	= SNB_UNC_CBO_MSR_OFFSET,
	.ops		= &snb_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
	.event_descs	= snb_uncore_events,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snb_uncore_arb = अणु
	.name		= "arb",
	.num_counters   = 2,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.perf_ctr	= SNB_UNC_ARB_PER_CTR0,
	.event_ctl	= SNB_UNC_ARB_PERFEVTSEL0,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.msr_offset	= SNB_UNC_ARB_MSR_OFFSET,
	.स्थिरraपूर्णांकs	= snb_uncore_arb_स्थिरraपूर्णांकs,
	.ops		= &snb_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snb_msr_uncores[] = अणु
	&snb_uncore_cbox,
	&snb_uncore_arb,
	शून्य,
पूर्ण;

व्योम snb_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = snb_msr_uncores;
	अगर (snb_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		snb_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
पूर्ण

अटल व्योम skl_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0) अणु
		wrmsrl(SKL_UNC_PERF_GLOBAL_CTL,
			SNB_UNC_GLOBAL_CTL_EN | SKL_UNC_GLOBAL_CTL_CORE_ALL);
	पूर्ण

	/* The 8th CBOX has dअगरferent MSR space */
	अगर (box->pmu->pmu_idx == 7)
		__set_bit(UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS, &box->flags);
पूर्ण

अटल व्योम skl_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(SKL_UNC_PERF_GLOBAL_CTL,
		SNB_UNC_GLOBAL_CTL_EN | SKL_UNC_GLOBAL_CTL_CORE_ALL);
पूर्ण

अटल व्योम skl_uncore_msr_निकास_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(SKL_UNC_PERF_GLOBAL_CTL, 0);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops skl_uncore_msr_ops = अणु
	.init_box	= skl_uncore_msr_init_box,
	.enable_box	= skl_uncore_msr_enable_box,
	.निकास_box	= skl_uncore_msr_निकास_box,
	.disable_event	= snb_uncore_msr_disable_event,
	.enable_event	= snb_uncore_msr_enable_event,
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skl_uncore_cbox = अणु
	.name		= "cbox",
	.num_counters   = 4,
	.num_boxes	= 8,
	.perf_ctr_bits	= 44,
	.fixed_ctr_bits	= 48,
	.perf_ctr	= SNB_UNC_CBO_0_PER_CTR0,
	.event_ctl	= SNB_UNC_CBO_0_PERFEVTSEL0,
	.fixed_ctr	= SNB_UNC_FIXED_CTR,
	.fixed_ctl	= SNB_UNC_FIXED_CTR_CTRL,
	.single_fixed	= 1,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.msr_offset	= SNB_UNC_CBO_MSR_OFFSET,
	.ops		= &skl_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
	.event_descs	= snb_uncore_events,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *skl_msr_uncores[] = अणु
	&skl_uncore_cbox,
	&snb_uncore_arb,
	शून्य,
पूर्ण;

व्योम skl_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = skl_msr_uncores;
	अगर (skl_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		skl_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	snb_uncore_arb.ops = &skl_uncore_msr_ops;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops icl_uncore_msr_ops = अणु
	.disable_event	= snb_uncore_msr_disable_event,
	.enable_event	= snb_uncore_msr_enable_event,
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icl_uncore_cbox = अणु
	.name		= "cbox",
	.num_counters   = 2,
	.perf_ctr_bits	= 44,
	.perf_ctr	= ICL_UNC_CBO_0_PER_CTR0,
	.event_ctl	= SNB_UNC_CBO_0_PERFEVTSEL0,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.msr_offset	= ICL_UNC_CBO_MSR_OFFSET,
	.ops		= &icl_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा uncore_event_desc icl_uncore_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks, "event=0xff"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा attribute *icl_uncore_घड़ी_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group icl_uncore_घड़ी_क्रमmat_group = अणु
	.name = "format",
	.attrs = icl_uncore_घड़ी_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icl_uncore_घड़ीbox = अणु
	.name		= "clock",
	.num_counters	= 1,
	.num_boxes	= 1,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNB_UNC_FIXED_CTR,
	.fixed_ctl	= SNB_UNC_FIXED_CTR_CTRL,
	.single_fixed	= 1,
	.event_mask	= SNB_UNC_CTL_EV_SEL_MASK,
	.क्रमmat_group	= &icl_uncore_घड़ी_क्रमmat_group,
	.ops		= &icl_uncore_msr_ops,
	.event_descs	= icl_uncore_events,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icl_uncore_arb = अणु
	.name		= "arb",
	.num_counters   = 1,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.perf_ctr	= ICL_UNC_ARB_PER_CTR,
	.event_ctl	= ICL_UNC_ARB_PERFEVTSEL,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.ops		= &icl_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *icl_msr_uncores[] = अणु
	&icl_uncore_cbox,
	&icl_uncore_arb,
	&icl_uncore_घड़ीbox,
	शून्य,
पूर्ण;

अटल पूर्णांक icl_get_cbox_num(व्योम)
अणु
	u64 num_boxes;

	rdmsrl(ICL_UNC_CBO_CONFIG, num_boxes);

	वापस num_boxes & ICL_UNC_NUM_CBO_MASK;
पूर्ण

व्योम icl_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = icl_msr_uncores;
	icl_uncore_cbox.num_boxes = icl_get_cbox_num();
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type *tgl_msr_uncores[] = अणु
	&icl_uncore_cbox,
	&snb_uncore_arb,
	&icl_uncore_घड़ीbox,
	शून्य,
पूर्ण;

अटल व्योम rkl_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(SKL_UNC_PERF_GLOBAL_CTL, SNB_UNC_GLOBAL_CTL_EN);
पूर्ण

व्योम tgl_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = tgl_msr_uncores;
	icl_uncore_cbox.num_boxes = icl_get_cbox_num();
	icl_uncore_cbox.ops = &skl_uncore_msr_ops;
	icl_uncore_घड़ीbox.ops = &skl_uncore_msr_ops;
	snb_uncore_arb.ops = &skl_uncore_msr_ops;
	skl_uncore_msr_ops.init_box = rkl_uncore_msr_init_box;
पूर्ण

अटल व्योम adl_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(ADL_UNC_PERF_GLOBAL_CTL, SNB_UNC_GLOBAL_CTL_EN);
पूर्ण

अटल व्योम adl_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(ADL_UNC_PERF_GLOBAL_CTL, SNB_UNC_GLOBAL_CTL_EN);
पूर्ण

अटल व्योम adl_uncore_msr_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(ADL_UNC_PERF_GLOBAL_CTL, 0);
पूर्ण

अटल व्योम adl_uncore_msr_निकास_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अगर (box->pmu->pmu_idx == 0)
		wrmsrl(ADL_UNC_PERF_GLOBAL_CTL, 0);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops adl_uncore_msr_ops = अणु
	.init_box	= adl_uncore_msr_init_box,
	.enable_box	= adl_uncore_msr_enable_box,
	.disable_box	= adl_uncore_msr_disable_box,
	.निकास_box	= adl_uncore_msr_निकास_box,
	.disable_event	= snb_uncore_msr_disable_event,
	.enable_event	= snb_uncore_msr_enable_event,
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल काष्ठा attribute *adl_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_threshold.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adl_uncore_क्रमmat_group = अणु
	.name		= "format",
	.attrs		= adl_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type adl_uncore_cbox = अणु
	.name		= "cbox",
	.num_counters   = 2,
	.perf_ctr_bits	= 44,
	.perf_ctr	= ADL_UNC_CBO_0_PER_CTR0,
	.event_ctl	= ADL_UNC_CBO_0_PERFEVTSEL0,
	.event_mask	= ADL_UNC_RAW_EVENT_MASK,
	.msr_offset	= ICL_UNC_CBO_MSR_OFFSET,
	.ops		= &adl_uncore_msr_ops,
	.क्रमmat_group	= &adl_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type adl_uncore_arb = अणु
	.name		= "arb",
	.num_counters   = 2,
	.num_boxes	= 2,
	.perf_ctr_bits	= 44,
	.perf_ctr	= ADL_UNC_ARB_PER_CTR0,
	.event_ctl	= ADL_UNC_ARB_PERFEVTSEL0,
	.event_mask	= SNB_UNC_RAW_EVENT_MASK,
	.msr_offset	= ADL_UNC_ARB_MSR_OFFSET,
	.स्थिरraपूर्णांकs	= snb_uncore_arb_स्थिरraपूर्णांकs,
	.ops		= &adl_uncore_msr_ops,
	.क्रमmat_group	= &snb_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type adl_uncore_घड़ीbox = अणु
	.name		= "clock",
	.num_counters	= 1,
	.num_boxes	= 1,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= ADL_UNC_FIXED_CTR,
	.fixed_ctl	= ADL_UNC_FIXED_CTR_CTRL,
	.single_fixed	= 1,
	.event_mask	= SNB_UNC_CTL_EV_SEL_MASK,
	.क्रमmat_group	= &icl_uncore_घड़ी_क्रमmat_group,
	.ops		= &adl_uncore_msr_ops,
	.event_descs	= icl_uncore_events,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *adl_msr_uncores[] = अणु
	&adl_uncore_cbox,
	&adl_uncore_arb,
	&adl_uncore_घड़ीbox,
	शून्य,
पूर्ण;

व्योम adl_uncore_cpu_init(व्योम)
अणु
	adl_uncore_cbox.num_boxes = icl_get_cbox_num();
	uncore_msr_uncores = adl_msr_uncores;
पूर्ण

क्रमागत अणु
	SNB_PCI_UNCORE_IMC,
पूर्ण;

अटल काष्ठा uncore_event_desc snb_uncore_imc_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(data_पढ़ोs,  "event=0x01"),
	INTEL_UNCORE_EVENT_DESC(data_पढ़ोs.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(data_पढ़ोs.unit, "MiB"),

	INTEL_UNCORE_EVENT_DESC(data_ग_लिखोs, "event=0x02"),
	INTEL_UNCORE_EVENT_DESC(data_ग_लिखोs.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(data_ग_लिखोs.unit, "MiB"),

	INTEL_UNCORE_EVENT_DESC(gt_requests, "event=0x03"),
	INTEL_UNCORE_EVENT_DESC(gt_requests.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(gt_requests.unit, "MiB"),

	INTEL_UNCORE_EVENT_DESC(ia_requests, "event=0x04"),
	INTEL_UNCORE_EVENT_DESC(ia_requests.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(ia_requests.unit, "MiB"),

	INTEL_UNCORE_EVENT_DESC(io_requests, "event=0x05"),
	INTEL_UNCORE_EVENT_DESC(io_requests.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(io_requests.unit, "MiB"),

	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

#घोषणा SNB_UNCORE_PCI_IMC_EVENT_MASK		0xff
#घोषणा SNB_UNCORE_PCI_IMC_BAR_OFFSET		0x48

/* page size multiple covering all config regs */
#घोषणा SNB_UNCORE_PCI_IMC_MAP_SIZE		0x6000

#घोषणा SNB_UNCORE_PCI_IMC_DATA_READS		0x1
#घोषणा SNB_UNCORE_PCI_IMC_DATA_READS_BASE	0x5050
#घोषणा SNB_UNCORE_PCI_IMC_DATA_WRITES		0x2
#घोषणा SNB_UNCORE_PCI_IMC_DATA_WRITES_BASE	0x5054
#घोषणा SNB_UNCORE_PCI_IMC_CTR_BASE		SNB_UNCORE_PCI_IMC_DATA_READS_BASE

/* BW अवरोध करोwn- legacy counters */
#घोषणा SNB_UNCORE_PCI_IMC_GT_REQUESTS		0x3
#घोषणा SNB_UNCORE_PCI_IMC_GT_REQUESTS_BASE	0x5040
#घोषणा SNB_UNCORE_PCI_IMC_IA_REQUESTS		0x4
#घोषणा SNB_UNCORE_PCI_IMC_IA_REQUESTS_BASE	0x5044
#घोषणा SNB_UNCORE_PCI_IMC_IO_REQUESTS		0x5
#घोषणा SNB_UNCORE_PCI_IMC_IO_REQUESTS_BASE	0x5048

क्रमागत perf_snb_uncore_imc_मुक्तrunning_types अणु
	SNB_PCI_UNCORE_IMC_DATA_READS		= 0,
	SNB_PCI_UNCORE_IMC_DATA_WRITES,
	SNB_PCI_UNCORE_IMC_GT_REQUESTS,
	SNB_PCI_UNCORE_IMC_IA_REQUESTS,
	SNB_PCI_UNCORE_IMC_IO_REQUESTS,

	SNB_PCI_UNCORE_IMC_FREERUNNING_TYPE_MAX,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters snb_uncore_imc_मुक्तrunning[] = अणु
	[SNB_PCI_UNCORE_IMC_DATA_READS]		= अणु SNB_UNCORE_PCI_IMC_DATA_READS_BASE,
							0x0, 0x0, 1, 32 पूर्ण,
	[SNB_PCI_UNCORE_IMC_DATA_WRITES]	= अणु SNB_UNCORE_PCI_IMC_DATA_WRITES_BASE,
							0x0, 0x0, 1, 32 पूर्ण,
	[SNB_PCI_UNCORE_IMC_GT_REQUESTS]	= अणु SNB_UNCORE_PCI_IMC_GT_REQUESTS_BASE,
							0x0, 0x0, 1, 32 पूर्ण,
	[SNB_PCI_UNCORE_IMC_IA_REQUESTS]	= अणु SNB_UNCORE_PCI_IMC_IA_REQUESTS_BASE,
							0x0, 0x0, 1, 32 पूर्ण,
	[SNB_PCI_UNCORE_IMC_IO_REQUESTS]	= अणु SNB_UNCORE_PCI_IMC_IO_REQUESTS_BASE,
							0x0, 0x0, 1, 32 पूर्ण,
पूर्ण;

अटल काष्ठा attribute *snb_uncore_imc_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snb_uncore_imc_क्रमmat_group = अणु
	.name = "format",
	.attrs = snb_uncore_imc_क्रमmats_attr,
पूर्ण;

अटल व्योम snb_uncore_imc_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक where = SNB_UNCORE_PCI_IMC_BAR_OFFSET;
	resource_माप_प्रकार addr;
	u32 pci_dword;

	pci_पढ़ो_config_dword(pdev, where, &pci_dword);
	addr = pci_dword;

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	pci_पढ़ो_config_dword(pdev, where + 4, &pci_dword);
	addr |= ((resource_माप_प्रकार)pci_dword << 32);
#पूर्ण_अगर

	addr &= ~(PAGE_SIZE - 1);

	box->io_addr = ioremap(addr, type->mmio_map_size);
	अगर (!box->io_addr)
		pr_warn("perf uncore: Failed to ioremap for %s.\n", type->name);

	box->hrसमयr_duration = UNCORE_SNB_IMC_HRTIMER_INTERVAL;
पूर्ण

अटल व्योम snb_uncore_imc_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणुपूर्ण

अटल व्योम snb_uncore_imc_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणुपूर्ण

अटल व्योम snb_uncore_imc_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणुपूर्ण

अटल व्योम snb_uncore_imc_disable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणुपूर्ण

/*
 * Keep the custom event_init() function compatible with old event
 * encoding क्रम मुक्त running counters.
 */
अटल पूर्णांक snb_uncore_imc_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu;
	काष्ठा पूर्णांकel_uncore_box *box;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 cfg = event->attr.config & SNB_UNCORE_PCI_IMC_EVENT_MASK;
	पूर्णांक idx, base;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	pmu = uncore_event_to_pmu(event);
	/* no device found क्रम this pmu */
	अगर (pmu->func_id < 0)
		वापस -ENOENT;

	/* Sampling not supported yet */
	अगर (hwc->sample_period)
		वापस -EINVAL;

	/* unsupported modes and filters */
	अगर (event->attr.sample_period) /* no sampling */
		वापस -EINVAL;

	/*
	 * Place all uncore events क्रम a particular physical package
	 * onto a single cpu
	 */
	अगर (event->cpu < 0)
		वापस -EINVAL;

	/* check only supported bits are set */
	अगर (event->attr.config & ~SNB_UNCORE_PCI_IMC_EVENT_MASK)
		वापस -EINVAL;

	box = uncore_pmu_to_box(pmu, event->cpu);
	अगर (!box || box->cpu < 0)
		वापस -EINVAL;

	event->cpu = box->cpu;
	event->pmu_निजी = box;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	event->hw.idx = -1;
	event->hw.last_tag = ~0ULL;
	event->hw.extra_reg.idx = EXTRA_REG_NONE;
	event->hw.branch_reg.idx = EXTRA_REG_NONE;
	/*
	 * check event is known (whitelist, determines counter)
	 */
	चयन (cfg) अणु
	हाल SNB_UNCORE_PCI_IMC_DATA_READS:
		base = SNB_UNCORE_PCI_IMC_DATA_READS_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		अवरोध;
	हाल SNB_UNCORE_PCI_IMC_DATA_WRITES:
		base = SNB_UNCORE_PCI_IMC_DATA_WRITES_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		अवरोध;
	हाल SNB_UNCORE_PCI_IMC_GT_REQUESTS:
		base = SNB_UNCORE_PCI_IMC_GT_REQUESTS_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		अवरोध;
	हाल SNB_UNCORE_PCI_IMC_IA_REQUESTS:
		base = SNB_UNCORE_PCI_IMC_IA_REQUESTS_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		अवरोध;
	हाल SNB_UNCORE_PCI_IMC_IO_REQUESTS:
		base = SNB_UNCORE_PCI_IMC_IO_REQUESTS_BASE;
		idx = UNCORE_PMC_IDX_FREERUNNING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* must be करोne beक्रमe validate_group */
	event->hw.event_base = base;
	event->hw.idx = idx;

	/* Convert to standard encoding क्रमmat क्रम मुक्तrunning counters */
	event->hw.config = ((cfg - 1) << 8) | 0x10ff;

	/* no group validation needed, we have मुक्त running counters */

	वापस 0;
पूर्ण

अटल पूर्णांक snb_uncore_imc_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

पूर्णांक snb_pci2phy_map_init(पूर्णांक devid)
अणु
	काष्ठा pci_dev *dev = शून्य;
	काष्ठा pci2phy_map *map;
	पूर्णांक bus, segment;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL, devid, dev);
	अगर (!dev)
		वापस -ENOTTY;

	bus = dev->bus->number;
	segment = pci_करोमुख्य_nr(dev->bus);

	raw_spin_lock(&pci2phy_map_lock);
	map = __find_pci2phy_map(segment);
	अगर (!map) अणु
		raw_spin_unlock(&pci2phy_map_lock);
		pci_dev_put(dev);
		वापस -ENOMEM;
	पूर्ण
	map->pbus_to_dieid[bus] = 0;
	raw_spin_unlock(&pci2phy_map_lock);

	pci_dev_put(dev);

	वापस 0;
पूर्ण

अटल काष्ठा pmu snb_uncore_imc_pmu = अणु
	.task_ctx_nr	= perf_invalid_context,
	.event_init	= snb_uncore_imc_event_init,
	.add		= uncore_pmu_event_add,
	.del		= uncore_pmu_event_del,
	.start		= uncore_pmu_event_start,
	.stop		= uncore_pmu_event_stop,
	.पढ़ो		= uncore_pmu_event_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops snb_uncore_imc_ops = अणु
	.init_box	= snb_uncore_imc_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.enable_box	= snb_uncore_imc_enable_box,
	.disable_box	= snb_uncore_imc_disable_box,
	.disable_event	= snb_uncore_imc_disable_event,
	.enable_event	= snb_uncore_imc_enable_event,
	.hw_config	= snb_uncore_imc_hw_config,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snb_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 5,
	.num_boxes	= 1,
	.num_मुक्तrunning_types	= SNB_PCI_UNCORE_IMC_FREERUNNING_TYPE_MAX,
	.mmio_map_size	= SNB_UNCORE_PCI_IMC_MAP_SIZE,
	.मुक्तrunning	= snb_uncore_imc_मुक्तrunning,
	.event_descs	= snb_uncore_imc_events,
	.क्रमmat_group	= &snb_uncore_imc_क्रमmat_group,
	.ops		= &snb_uncore_imc_ops,
	.pmu		= &snb_uncore_imc_pmu,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snb_pci_uncores[] = अणु
	[SNB_PCI_UNCORE_IMC]	= &snb_uncore_imc,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snb_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SNB_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ivb_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_IVB_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_IVB_E3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hsw_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_HSW_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_HSW_U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id bdw_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BDW_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id skl_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_Y_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_HD_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_HQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_SD_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_SQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SKL_E3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_Y_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_UQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_SD_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_SQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_HQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KBL_WQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_2U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_4U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_4H_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_6H_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_2S_D_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_4S_D_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_6S_D_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_8S_D_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_4S_W_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_6S_W_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_8S_W_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_4S_S_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_6S_S_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CFL_8S_S_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_AML_YD_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_AML_YQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WHL_UQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WHL_4_UQ_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WHL_UD_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_H1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_H2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_H3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_U1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_U2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_U3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_S1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_S2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_S3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_S4_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CML_S5_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id icl_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICL_U_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICL_U2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_RKL_1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_RKL_2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver snb_uncore_pci_driver = अणु
	.name		= "snb_uncore",
	.id_table	= snb_uncore_pci_ids,
पूर्ण;

अटल काष्ठा pci_driver ivb_uncore_pci_driver = अणु
	.name		= "ivb_uncore",
	.id_table	= ivb_uncore_pci_ids,
पूर्ण;

अटल काष्ठा pci_driver hsw_uncore_pci_driver = अणु
	.name		= "hsw_uncore",
	.id_table	= hsw_uncore_pci_ids,
पूर्ण;

अटल काष्ठा pci_driver bdw_uncore_pci_driver = अणु
	.name		= "bdw_uncore",
	.id_table	= bdw_uncore_pci_ids,
पूर्ण;

अटल काष्ठा pci_driver skl_uncore_pci_driver = अणु
	.name		= "skl_uncore",
	.id_table	= skl_uncore_pci_ids,
पूर्ण;

अटल काष्ठा pci_driver icl_uncore_pci_driver = अणु
	.name		= "icl_uncore",
	.id_table	= icl_uncore_pci_ids,
पूर्ण;

काष्ठा imc_uncore_pci_dev अणु
	__u32 pci_id;
	काष्ठा pci_driver *driver;
पूर्ण;
#घोषणा IMC_DEV(a, d) \
	अणु .pci_id = PCI_DEVICE_ID_INTEL_##a, .driver = (d) पूर्ण

अटल स्थिर काष्ठा imc_uncore_pci_dev desktop_imc_pci_ids[] = अणु
	IMC_DEV(SNB_IMC, &snb_uncore_pci_driver),
	IMC_DEV(IVB_IMC, &ivb_uncore_pci_driver),    /* 3rd Gen Core processor */
	IMC_DEV(IVB_E3_IMC, &ivb_uncore_pci_driver), /* Xeon E3-1200 v2/3rd Gen Core processor */
	IMC_DEV(HSW_IMC, &hsw_uncore_pci_driver),    /* 4th Gen Core Processor */
	IMC_DEV(HSW_U_IMC, &hsw_uncore_pci_driver),  /* 4th Gen Core ULT Mobile Processor */
	IMC_DEV(BDW_IMC, &bdw_uncore_pci_driver),    /* 5th Gen Core U */
	IMC_DEV(SKL_Y_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core Y */
	IMC_DEV(SKL_U_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core U */
	IMC_DEV(SKL_HD_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core H Dual Core */
	IMC_DEV(SKL_HQ_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core H Quad Core */
	IMC_DEV(SKL_SD_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core S Dual Core */
	IMC_DEV(SKL_SQ_IMC, &skl_uncore_pci_driver),  /* 6th Gen Core S Quad Core */
	IMC_DEV(SKL_E3_IMC, &skl_uncore_pci_driver),  /* Xeon E3 V5 Gen Core processor */
	IMC_DEV(KBL_Y_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core Y */
	IMC_DEV(KBL_U_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core U */
	IMC_DEV(KBL_UQ_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core U Quad Core */
	IMC_DEV(KBL_SD_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core S Dual Core */
	IMC_DEV(KBL_SQ_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core S Quad Core */
	IMC_DEV(KBL_HQ_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core H Quad Core */
	IMC_DEV(KBL_WQ_IMC, &skl_uncore_pci_driver),  /* 7th Gen Core S 4 cores Work Station */
	IMC_DEV(CFL_2U_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core U 2 Cores */
	IMC_DEV(CFL_4U_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core U 4 Cores */
	IMC_DEV(CFL_4H_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core H 4 Cores */
	IMC_DEV(CFL_6H_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core H 6 Cores */
	IMC_DEV(CFL_2S_D_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 2 Cores Desktop */
	IMC_DEV(CFL_4S_D_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 4 Cores Desktop */
	IMC_DEV(CFL_6S_D_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 6 Cores Desktop */
	IMC_DEV(CFL_8S_D_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 8 Cores Desktop */
	IMC_DEV(CFL_4S_W_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 4 Cores Work Station */
	IMC_DEV(CFL_6S_W_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 6 Cores Work Station */
	IMC_DEV(CFL_8S_W_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 8 Cores Work Station */
	IMC_DEV(CFL_4S_S_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 4 Cores Server */
	IMC_DEV(CFL_6S_S_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 6 Cores Server */
	IMC_DEV(CFL_8S_S_IMC, &skl_uncore_pci_driver),  /* 8th Gen Core S 8 Cores Server */
	IMC_DEV(AML_YD_IMC, &skl_uncore_pci_driver),	/* 8th Gen Core Y Mobile Dual Core */
	IMC_DEV(AML_YQ_IMC, &skl_uncore_pci_driver),	/* 8th Gen Core Y Mobile Quad Core */
	IMC_DEV(WHL_UQ_IMC, &skl_uncore_pci_driver),	/* 8th Gen Core U Mobile Quad Core */
	IMC_DEV(WHL_4_UQ_IMC, &skl_uncore_pci_driver),	/* 8th Gen Core U Mobile Quad Core */
	IMC_DEV(WHL_UD_IMC, &skl_uncore_pci_driver),	/* 8th Gen Core U Mobile Dual Core */
	IMC_DEV(CML_H1_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_H2_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_H3_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_U1_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_U2_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_U3_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_S1_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_S2_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_S3_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_S4_IMC, &skl_uncore_pci_driver),
	IMC_DEV(CML_S5_IMC, &skl_uncore_pci_driver),
	IMC_DEV(ICL_U_IMC, &icl_uncore_pci_driver),	/* 10th Gen Core Mobile */
	IMC_DEV(ICL_U2_IMC, &icl_uncore_pci_driver),	/* 10th Gen Core Mobile */
	IMC_DEV(RKL_1_IMC, &icl_uncore_pci_driver),
	IMC_DEV(RKL_2_IMC, &icl_uncore_pci_driver),
	अणु  /* end marker */ पूर्ण
पूर्ण;


#घोषणा क्रम_each_imc_pci_id(x, t) \
	क्रम (x = (t); (x)->pci_id; x++)

अटल काष्ठा pci_driver *imc_uncore_find_dev(व्योम)
अणु
	स्थिर काष्ठा imc_uncore_pci_dev *p;
	पूर्णांक ret;

	क्रम_each_imc_pci_id(p, desktop_imc_pci_ids) अणु
		ret = snb_pci2phy_map_init(p->pci_id);
		अगर (ret == 0)
			वापस p->driver;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक imc_uncore_pci_init(व्योम)
अणु
	काष्ठा pci_driver *imc_drv = imc_uncore_find_dev();

	अगर (!imc_drv)
		वापस -ENODEV;

	uncore_pci_uncores = snb_pci_uncores;
	uncore_pci_driver = imc_drv;

	वापस 0;
पूर्ण

पूर्णांक snb_uncore_pci_init(व्योम)
अणु
	वापस imc_uncore_pci_init();
पूर्ण

पूर्णांक ivb_uncore_pci_init(व्योम)
अणु
	वापस imc_uncore_pci_init();
पूर्ण
पूर्णांक hsw_uncore_pci_init(व्योम)
अणु
	वापस imc_uncore_pci_init();
पूर्ण

पूर्णांक bdw_uncore_pci_init(व्योम)
अणु
	वापस imc_uncore_pci_init();
पूर्ण

पूर्णांक skl_uncore_pci_init(व्योम)
अणु
	वापस imc_uncore_pci_init();
पूर्ण

/* end of Sandy Bridge uncore support */

/* Nehalem uncore support */
अटल व्योम nhm_uncore_msr_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(NHM_UNC_PERF_GLOBAL_CTL, 0);
पूर्ण

अटल व्योम nhm_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	wrmsrl(NHM_UNC_PERF_GLOBAL_CTL, NHM_UNC_GLOBAL_CTL_EN_PC_ALL | NHM_UNC_GLOBAL_CTL_EN_FC);
पूर्ण

अटल व्योम nhm_uncore_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (hwc->idx < UNCORE_PMC_IDX_FIXED)
		wrmsrl(hwc->config_base, hwc->config | SNB_UNC_CTL_EN);
	अन्यथा
		wrmsrl(hwc->config_base, NHM_UNC_FIXED_CTR_CTL_EN);
पूर्ण

अटल काष्ठा attribute *nhm_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_cmask8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nhm_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = nhm_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा uncore_event_desc nhm_uncore_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks,                "event=0xff,umask=0x00"),
	INTEL_UNCORE_EVENT_DESC(qmc_ग_लिखोs_full_any,       "event=0x2f,umask=0x0f"),
	INTEL_UNCORE_EVENT_DESC(qmc_normal_पढ़ोs_any,      "event=0x2c,umask=0x0f"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_ioh_पढ़ोs,     "event=0x20,umask=0x01"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_ioh_ग_लिखोs,    "event=0x20,umask=0x02"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_remote_पढ़ोs,  "event=0x20,umask=0x04"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_remote_ग_लिखोs, "event=0x20,umask=0x08"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_local_पढ़ोs,   "event=0x20,umask=0x10"),
	INTEL_UNCORE_EVENT_DESC(qhl_request_local_ग_लिखोs,  "event=0x20,umask=0x20"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops nhm_uncore_msr_ops = अणु
	.disable_box	= nhm_uncore_msr_disable_box,
	.enable_box	= nhm_uncore_msr_enable_box,
	.disable_event	= snb_uncore_msr_disable_event,
	.enable_event	= nhm_uncore_msr_enable_event,
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type nhm_uncore = अणु
	.name		= "",
	.num_counters   = 8,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.event_ctl	= NHM_UNC_PERFEVTSEL0,
	.perf_ctr	= NHM_UNC_UNCORE_PMC0,
	.fixed_ctr	= NHM_UNC_FIXED_CTR,
	.fixed_ctl	= NHM_UNC_FIXED_CTR_CTRL,
	.event_mask	= NHM_UNC_RAW_EVENT_MASK,
	.event_descs	= nhm_uncore_events,
	.ops		= &nhm_uncore_msr_ops,
	.क्रमmat_group	= &nhm_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *nhm_msr_uncores[] = अणु
	&nhm_uncore,
	शून्य,
पूर्ण;

व्योम nhm_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = nhm_msr_uncores;
पूर्ण

/* end of Nehalem uncore support */

/* Tiger Lake MMIO uncore support */

अटल स्थिर काष्ठा pci_device_id tgl_uncore_pci_ids[] = अणु
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGL_U1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGL_U2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGL_U3_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGL_U4_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TGL_H_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ADL_1_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* IMC */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ADL_2_IMC),
		.driver_data = UNCORE_PCI_DEV_DATA(SNB_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

क्रमागत perf_tgl_uncore_imc_मुक्तrunning_types अणु
	TGL_MMIO_UNCORE_IMC_DATA_TOTAL,
	TGL_MMIO_UNCORE_IMC_DATA_READ,
	TGL_MMIO_UNCORE_IMC_DATA_WRITE,
	TGL_MMIO_UNCORE_IMC_FREERUNNING_TYPE_MAX
पूर्ण;

अटल काष्ठा मुक्तrunning_counters tgl_l_uncore_imc_मुक्तrunning[] = अणु
	[TGL_MMIO_UNCORE_IMC_DATA_TOTAL]	= अणु 0x5040, 0x0, 0x0, 1, 64 पूर्ण,
	[TGL_MMIO_UNCORE_IMC_DATA_READ]		= अणु 0x5058, 0x0, 0x0, 1, 64 पूर्ण,
	[TGL_MMIO_UNCORE_IMC_DATA_WRITE]	= अणु 0x50A0, 0x0, 0x0, 1, 64 पूर्ण,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters tgl_uncore_imc_मुक्तrunning[] = अणु
	[TGL_MMIO_UNCORE_IMC_DATA_TOTAL]	= अणु 0xd840, 0x0, 0x0, 1, 64 पूर्ण,
	[TGL_MMIO_UNCORE_IMC_DATA_READ]		= अणु 0xd858, 0x0, 0x0, 1, 64 पूर्ण,
	[TGL_MMIO_UNCORE_IMC_DATA_WRITE]	= अणु 0xd8A0, 0x0, 0x0, 1, 64 पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc tgl_uncore_imc_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(data_total,         "event=0xff,umask=0x10"),
	INTEL_UNCORE_EVENT_DESC(data_total.scale,   "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(data_total.unit,    "MiB"),

	INTEL_UNCORE_EVENT_DESC(data_पढ़ो,         "event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(data_पढ़ो.scale,   "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(data_पढ़ो.unit,    "MiB"),

	INTEL_UNCORE_EVENT_DESC(data_ग_लिखो,        "event=0xff,umask=0x30"),
	INTEL_UNCORE_EVENT_DESC(data_ग_लिखो.scale,  "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(data_ग_लिखो.unit,   "MiB"),

	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_dev *tgl_uncore_get_mc_dev(व्योम)
अणु
	स्थिर काष्ठा pci_device_id *ids = tgl_uncore_pci_ids;
	काष्ठा pci_dev *mc_dev = शून्य;

	जबतक (ids && ids->venकरोr) अणु
		mc_dev = pci_get_device(PCI_VENDOR_ID_INTEL, ids->device, शून्य);
		अगर (mc_dev)
			वापस mc_dev;
		ids++;
	पूर्ण

	वापस mc_dev;
पूर्ण

#घोषणा TGL_UNCORE_MMIO_IMC_MEM_OFFSET		0x10000
#घोषणा TGL_UNCORE_PCI_IMC_MAP_SIZE		0xe000

अटल व्योम tgl_uncore_imc_मुक्तrunning_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = tgl_uncore_get_mc_dev();
	काष्ठा पूर्णांकel_uncore_pmu *pmu = box->pmu;
	काष्ठा पूर्णांकel_uncore_type *type = pmu->type;
	resource_माप_प्रकार addr;
	u32 mch_bar;

	अगर (!pdev) अणु
		pr_warn("perf uncore: Cannot find matched IMC device.\n");
		वापस;
	पूर्ण

	pci_पढ़ो_config_dword(pdev, SNB_UNCORE_PCI_IMC_BAR_OFFSET, &mch_bar);
	/* MCHBAR is disabled */
	अगर (!(mch_bar & BIT(0))) अणु
		pr_warn("perf uncore: MCHBAR is disabled. Failed to map IMC free-running counters.\n");
		वापस;
	पूर्ण
	mch_bar &= ~BIT(0);
	addr = (resource_माप_प्रकार)(mch_bar + TGL_UNCORE_MMIO_IMC_MEM_OFFSET * pmu->pmu_idx);

#अगर_घोषित CONFIG_PHYS_ADDR_T_64BIT
	pci_पढ़ो_config_dword(pdev, SNB_UNCORE_PCI_IMC_BAR_OFFSET + 4, &mch_bar);
	addr |= ((resource_माप_प्रकार)mch_bar << 32);
#पूर्ण_अगर

	box->io_addr = ioremap(addr, type->mmio_map_size);
	अगर (!box->io_addr)
		pr_warn("perf uncore: Failed to ioremap for %s.\n", type->name);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops tgl_uncore_imc_मुक्तrunning_ops = अणु
	.init_box	= tgl_uncore_imc_मुक्तrunning_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
	.hw_config	= uncore_मुक्तrunning_hw_config,
पूर्ण;

अटल काष्ठा attribute *tgl_uncore_imc_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tgl_uncore_imc_क्रमmat_group = अणु
	.name = "format",
	.attrs = tgl_uncore_imc_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type tgl_uncore_imc_मुक्त_running = अणु
	.name			= "imc_free_running",
	.num_counters		= 3,
	.num_boxes		= 2,
	.num_मुक्तrunning_types	= TGL_MMIO_UNCORE_IMC_FREERUNNING_TYPE_MAX,
	.mmio_map_size		= TGL_UNCORE_PCI_IMC_MAP_SIZE,
	.मुक्तrunning		= tgl_uncore_imc_मुक्तrunning,
	.ops			= &tgl_uncore_imc_मुक्तrunning_ops,
	.event_descs		= tgl_uncore_imc_events,
	.क्रमmat_group		= &tgl_uncore_imc_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *tgl_mmio_uncores[] = अणु
	&tgl_uncore_imc_मुक्त_running,
	शून्य
पूर्ण;

व्योम tgl_l_uncore_mmio_init(व्योम)
अणु
	tgl_uncore_imc_मुक्त_running.मुक्तrunning = tgl_l_uncore_imc_मुक्तrunning;
	uncore_mmio_uncores = tgl_mmio_uncores;
पूर्ण

व्योम tgl_uncore_mmio_init(व्योम)
अणु
	uncore_mmio_uncores = tgl_mmio_uncores;
पूर्ण

/* end of Tiger Lake MMIO uncore support */
