<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Management Engine (FME) Global Perक्रमmance Reporting
 *
 * Copyright 2019 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xu Yilun <yilun.xu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Mitchel, Henry <henry.mitchel@पूर्णांकel.com>
 */

#समावेश <linux/perf_event.h>
#समावेश "dfl.h"
#समावेश "dfl-fme.h"

/*
 * Perक्रमmance Counter Registers क्रम Cache.
 *
 * Cache Events are listed below as CACHE_EVNT_*.
 */
#घोषणा CACHE_CTRL			0x8
#घोषणा CACHE_RESET_CNTR		BIT_ULL(0)
#घोषणा CACHE_FREEZE_CNTR		BIT_ULL(8)
#घोषणा CACHE_CTRL_EVNT			GENMASK_ULL(19, 16)
#घोषणा CACHE_EVNT_RD_HIT		0x0
#घोषणा CACHE_EVNT_WR_HIT		0x1
#घोषणा CACHE_EVNT_RD_MISS		0x2
#घोषणा CACHE_EVNT_WR_MISS		0x3
#घोषणा CACHE_EVNT_RSVD			0x4
#घोषणा CACHE_EVNT_HOLD_REQ		0x5
#घोषणा CACHE_EVNT_DATA_WR_PORT_CONTEN	0x6
#घोषणा CACHE_EVNT_TAG_WR_PORT_CONTEN	0x7
#घोषणा CACHE_EVNT_TX_REQ_STALL		0x8
#घोषणा CACHE_EVNT_RX_REQ_STALL		0x9
#घोषणा CACHE_EVNT_EVICTIONS		0xa
#घोषणा CACHE_EVNT_MAX			CACHE_EVNT_EVICTIONS
#घोषणा CACHE_CHANNEL_SEL		BIT_ULL(20)
#घोषणा CACHE_CHANNEL_RD		0
#घोषणा CACHE_CHANNEL_WR		1
#घोषणा CACHE_CNTR0			0x10
#घोषणा CACHE_CNTR1			0x18
#घोषणा CACHE_CNTR_EVNT_CNTR		GENMASK_ULL(47, 0)
#घोषणा CACHE_CNTR_EVNT			GENMASK_ULL(63, 60)

/*
 * Perक्रमmance Counter Registers क्रम Fabric.
 *
 * Fabric Events are listed below as FAB_EVNT_*
 */
#घोषणा FAB_CTRL			0x20
#घोषणा FAB_RESET_CNTR			BIT_ULL(0)
#घोषणा FAB_FREEZE_CNTR			BIT_ULL(8)
#घोषणा FAB_CTRL_EVNT			GENMASK_ULL(19, 16)
#घोषणा FAB_EVNT_PCIE0_RD		0x0
#घोषणा FAB_EVNT_PCIE0_WR		0x1
#घोषणा FAB_EVNT_PCIE1_RD		0x2
#घोषणा FAB_EVNT_PCIE1_WR		0x3
#घोषणा FAB_EVNT_UPI_RD			0x4
#घोषणा FAB_EVNT_UPI_WR			0x5
#घोषणा FAB_EVNT_MMIO_RD		0x6
#घोषणा FAB_EVNT_MMIO_WR		0x7
#घोषणा FAB_EVNT_MAX			FAB_EVNT_MMIO_WR
#घोषणा FAB_PORT_ID			GENMASK_ULL(21, 20)
#घोषणा FAB_PORT_FILTER			BIT_ULL(23)
#घोषणा FAB_PORT_FILTER_DISABLE		0
#घोषणा FAB_PORT_FILTER_ENABLE		1
#घोषणा FAB_CNTR			0x28
#घोषणा FAB_CNTR_EVNT_CNTR		GENMASK_ULL(59, 0)
#घोषणा FAB_CNTR_EVNT			GENMASK_ULL(63, 60)

/*
 * Perक्रमmance Counter Registers क्रम Clock.
 *
 * Clock Counter can't be reset or frozen by SW.
 */
#घोषणा CLK_CNTR			0x30
#घोषणा BASIC_EVNT_CLK			0x0
#घोषणा BASIC_EVNT_MAX			BASIC_EVNT_CLK

/*
 * Perक्रमmance Counter Registers क्रम IOMMU / VT-D.
 *
 * VT-D Events are listed below as VTD_EVNT_* and VTD_SIP_EVNT_*
 */
#घोषणा VTD_CTRL			0x38
#घोषणा VTD_RESET_CNTR			BIT_ULL(0)
#घोषणा VTD_FREEZE_CNTR			BIT_ULL(8)
#घोषणा VTD_CTRL_EVNT			GENMASK_ULL(19, 16)
#घोषणा VTD_EVNT_AFU_MEM_RD_TRANS	0x0
#घोषणा VTD_EVNT_AFU_MEM_WR_TRANS	0x1
#घोषणा VTD_EVNT_AFU_DEVTLB_RD_HIT	0x2
#घोषणा VTD_EVNT_AFU_DEVTLB_WR_HIT	0x3
#घोषणा VTD_EVNT_DEVTLB_4K_FILL		0x4
#घोषणा VTD_EVNT_DEVTLB_2M_FILL		0x5
#घोषणा VTD_EVNT_DEVTLB_1G_FILL		0x6
#घोषणा VTD_EVNT_MAX			VTD_EVNT_DEVTLB_1G_FILL
#घोषणा VTD_CNTR			0x40
#घोषणा VTD_CNTR_EVNT_CNTR		GENMASK_ULL(47, 0)
#घोषणा VTD_CNTR_EVNT			GENMASK_ULL(63, 60)

#घोषणा VTD_SIP_CTRL			0x48
#घोषणा VTD_SIP_RESET_CNTR		BIT_ULL(0)
#घोषणा VTD_SIP_FREEZE_CNTR		BIT_ULL(8)
#घोषणा VTD_SIP_CTRL_EVNT		GENMASK_ULL(19, 16)
#घोषणा VTD_SIP_EVNT_IOTLB_4K_HIT	0x0
#घोषणा VTD_SIP_EVNT_IOTLB_2M_HIT	0x1
#घोषणा VTD_SIP_EVNT_IOTLB_1G_HIT	0x2
#घोषणा VTD_SIP_EVNT_SLPWC_L3_HIT	0x3
#घोषणा VTD_SIP_EVNT_SLPWC_L4_HIT	0x4
#घोषणा VTD_SIP_EVNT_RCC_HIT		0x5
#घोषणा VTD_SIP_EVNT_IOTLB_4K_MISS	0x6
#घोषणा VTD_SIP_EVNT_IOTLB_2M_MISS	0x7
#घोषणा VTD_SIP_EVNT_IOTLB_1G_MISS	0x8
#घोषणा VTD_SIP_EVNT_SLPWC_L3_MISS	0x9
#घोषणा VTD_SIP_EVNT_SLPWC_L4_MISS	0xa
#घोषणा VTD_SIP_EVNT_RCC_MISS		0xb
#घोषणा VTD_SIP_EVNT_MAX		VTD_SIP_EVNT_SLPWC_L4_MISS
#घोषणा VTD_SIP_CNTR			0X50
#घोषणा VTD_SIP_CNTR_EVNT_CNTR		GENMASK_ULL(47, 0)
#घोषणा VTD_SIP_CNTR_EVNT		GENMASK_ULL(63, 60)

#घोषणा PERF_TIMEOUT			30

#घोषणा PERF_MAX_PORT_NUM		1U

/**
 * काष्ठा fme_perf_priv - priv data काष्ठाure क्रम fme perf driver
 *
 * @dev: parent device.
 * @ioaddr: mapped base address of mmio region.
 * @pmu: pmu data काष्ठाure क्रम fme perf counters.
 * @id: id of this fme perक्रमmance report निजी feature.
 * @fab_users: current user number on fabric counters.
 * @fab_port_id: used to indicate current working mode of fabric counters.
 * @fab_lock: lock to protect fabric counters working mode.
 * @cpu: active CPU to which the PMU is bound क्रम accesses.
 * @cpuhp_node: node क्रम CPU hotplug notअगरier link.
 * @cpuhp_state: state क्रम CPU hotplug notअगरication;
 */
काष्ठा fme_perf_priv अणु
	काष्ठा device *dev;
	व्योम __iomem *ioaddr;
	काष्ठा pmu pmu;
	u16 id;

	u32 fab_users;
	u32 fab_port_id;
	spinlock_t fab_lock;

	अचिन्हित पूर्णांक cpu;
	काष्ठा hlist_node node;
	क्रमागत cpuhp_state cpuhp_state;
पूर्ण;

/**
 * काष्ठा fme_perf_event_ops - callbacks क्रम fme perf events
 *
 * @event_init: callback invoked during event init.
 * @event_destroy: callback invoked during event destroy.
 * @पढ़ो_counter: callback to पढ़ो hardware counters.
 */
काष्ठा fme_perf_event_ops अणु
	पूर्णांक (*event_init)(काष्ठा fme_perf_priv *priv, u32 event, u32 portid);
	व्योम (*event_destroy)(काष्ठा fme_perf_priv *priv, u32 event,
			      u32 portid);
	u64 (*पढ़ो_counter)(काष्ठा fme_perf_priv *priv, u32 event, u32 portid);
पूर्ण;

#घोषणा to_fme_perf_priv(_pmu)	container_of(_pmu, काष्ठा fme_perf_priv, pmu)

अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा fme_perf_priv *priv;

	priv = to_fme_perf_priv(pmu);

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(priv->cpu));
पूर्ण
अटल DEVICE_ATTR_RO(cpumask);

अटल काष्ठा attribute *fme_perf_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_cpumask_group = अणु
	.attrs = fme_perf_cpumask_attrs,
पूर्ण;

#घोषणा FME_EVENT_MASK		GENMASK_ULL(11, 0)
#घोषणा FME_EVENT_SHIFT		0
#घोषणा FME_EVTYPE_MASK		GENMASK_ULL(15, 12)
#घोषणा FME_EVTYPE_SHIFT	12
#घोषणा FME_EVTYPE_BASIC	0
#घोषणा FME_EVTYPE_CACHE	1
#घोषणा FME_EVTYPE_FABRIC	2
#घोषणा FME_EVTYPE_VTD		3
#घोषणा FME_EVTYPE_VTD_SIP	4
#घोषणा FME_EVTYPE_MAX		FME_EVTYPE_VTD_SIP
#घोषणा FME_PORTID_MASK		GENMASK_ULL(23, 16)
#घोषणा FME_PORTID_SHIFT	16
#घोषणा FME_PORTID_ROOT		(0xffU)

#घोषणा get_event(_config)	FIELD_GET(FME_EVENT_MASK, _config)
#घोषणा get_evtype(_config)	FIELD_GET(FME_EVTYPE_MASK, _config)
#घोषणा get_portid(_config)	FIELD_GET(FME_PORTID_MASK, _config)

PMU_FORMAT_ATTR(event,		"config:0-11");
PMU_FORMAT_ATTR(evtype,		"config:12-15");
PMU_FORMAT_ATTR(portid,		"config:16-23");

अटल काष्ठा attribute *fme_perf_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_evtype.attr,
	&क्रमmat_attr_portid.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_क्रमmat_group = अणु
	.name = "format",
	.attrs = fme_perf_क्रमmat_attrs,
पूर्ण;

/*
 * There are no शेष events, but we need to create
 * "events" group (with empty attrs) beक्रमe updating
 * it with detected events (using pmu->attr_update).
 */
अटल काष्ठा attribute *fme_perf_events_attrs_empty[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_events_group = अणु
	.name = "events",
	.attrs = fme_perf_events_attrs_empty,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fme_perf_groups[] = अणु
	&fme_perf_क्रमmat_group,
	&fme_perf_cpumask_group,
	&fme_perf_events_group,
	शून्य,
पूर्ण;

अटल bool is_portid_root(u32 portid)
अणु
	वापस portid == FME_PORTID_ROOT;
पूर्ण

अटल bool is_portid_port(u32 portid)
अणु
	वापस portid < PERF_MAX_PORT_NUM;
पूर्ण

अटल bool is_portid_root_or_port(u32 portid)
अणु
	वापस is_portid_root(portid) || is_portid_port(portid);
पूर्ण

अटल u64 fme_पढ़ो_perf_cntr_reg(व्योम __iomem *addr)
अणु
	u32 low;
	u64 v;

	/*
	 * For 64bit counter रेजिस्टरs, the counter may increases and carries
	 * out of bit [31] between 2 32bit पढ़ोs. So add extra पढ़ोs to help
	 * to prevent this issue. This only happens in platक्रमms which करोn't
	 * support 64bit पढ़ो - पढ़ोq is split पूर्णांकo 2 पढ़ोl.
	 */
	करो अणु
		v = पढ़ोq(addr);
		low = पढ़ोl(addr);
	पूर्ण जबतक (((u32)v) > low);

	वापस v;
पूर्ण

अटल पूर्णांक basic_event_init(काष्ठा fme_perf_priv *priv, u32 event, u32 portid)
अणु
	अगर (event <= BASIC_EVNT_MAX && is_portid_root(portid))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल u64 basic_पढ़ो_event_counter(काष्ठा fme_perf_priv *priv,
				    u32 event, u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;

	वापस fme_पढ़ो_perf_cntr_reg(base + CLK_CNTR);
पूर्ण

अटल पूर्णांक cache_event_init(काष्ठा fme_perf_priv *priv, u32 event, u32 portid)
अणु
	अगर (priv->id == FME_FEATURE_ID_GLOBAL_IPERF &&
	    event <= CACHE_EVNT_MAX && is_portid_root(portid))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल u64 cache_पढ़ो_event_counter(काष्ठा fme_perf_priv *priv,
				    u32 event, u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;
	u64 v, count;
	u8 channel;

	अगर (event == CACHE_EVNT_WR_HIT || event == CACHE_EVNT_WR_MISS ||
	    event == CACHE_EVNT_DATA_WR_PORT_CONTEN ||
	    event == CACHE_EVNT_TAG_WR_PORT_CONTEN)
		channel = CACHE_CHANNEL_WR;
	अन्यथा
		channel = CACHE_CHANNEL_RD;

	/* set channel access type and cache event code. */
	v = पढ़ोq(base + CACHE_CTRL);
	v &= ~(CACHE_CHANNEL_SEL | CACHE_CTRL_EVNT);
	v |= FIELD_PREP(CACHE_CHANNEL_SEL, channel);
	v |= FIELD_PREP(CACHE_CTRL_EVNT, event);
	ग_लिखोq(v, base + CACHE_CTRL);

	अगर (पढ़ोq_poll_समयout_atomic(base + CACHE_CNTR0, v,
				      FIELD_GET(CACHE_CNTR_EVNT, v) == event,
				      1, PERF_TIMEOUT)) अणु
		dev_err(priv->dev, "timeout, unmatched cache event code in counter register.\n");
		वापस 0;
	पूर्ण

	v = fme_पढ़ो_perf_cntr_reg(base + CACHE_CNTR0);
	count = FIELD_GET(CACHE_CNTR_EVNT_CNTR, v);
	v = fme_पढ़ो_perf_cntr_reg(base + CACHE_CNTR1);
	count += FIELD_GET(CACHE_CNTR_EVNT_CNTR, v);

	वापस count;
पूर्ण

अटल bool is_fabric_event_supported(काष्ठा fme_perf_priv *priv, u32 event,
				      u32 portid)
अणु
	अगर (event > FAB_EVNT_MAX || !is_portid_root_or_port(portid))
		वापस false;

	अगर (priv->id == FME_FEATURE_ID_GLOBAL_DPERF &&
	    (event == FAB_EVNT_PCIE1_RD || event == FAB_EVNT_UPI_RD ||
	     event == FAB_EVNT_PCIE1_WR || event == FAB_EVNT_UPI_WR))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक fabric_event_init(काष्ठा fme_perf_priv *priv, u32 event, u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;
	पूर्णांक ret = 0;
	u64 v;

	अगर (!is_fabric_event_supported(priv, event, portid))
		वापस -EINVAL;

	/*
	 * as fabric counter set only can be in either overall or port mode.
	 * In overall mode, it counts overall data क्रम FPGA, and in port mode,
	 * it is configured to monitor on one inभागidual port.
	 *
	 * so every समय, a new event is initialized, driver checks
	 * current working mode and अगर someone is using this counter set.
	 */
	spin_lock(&priv->fab_lock);
	अगर (priv->fab_users && priv->fab_port_id != portid) अणु
		dev_dbg(priv->dev, "conflict fabric event monitoring mode.\n");
		ret = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	priv->fab_users++;

	/*
	 * skip अगर current working mode matches, otherwise change the working
	 * mode per input port_id, to monitor overall data or another port.
	 */
	अगर (priv->fab_port_id == portid)
		जाओ निकास;

	priv->fab_port_id = portid;

	v = पढ़ोq(base + FAB_CTRL);
	v &= ~(FAB_PORT_FILTER | FAB_PORT_ID);

	अगर (is_portid_root(portid)) अणु
		v |= FIELD_PREP(FAB_PORT_FILTER, FAB_PORT_FILTER_DISABLE);
	पूर्ण अन्यथा अणु
		v |= FIELD_PREP(FAB_PORT_FILTER, FAB_PORT_FILTER_ENABLE);
		v |= FIELD_PREP(FAB_PORT_ID, portid);
	पूर्ण
	ग_लिखोq(v, base + FAB_CTRL);

निकास:
	spin_unlock(&priv->fab_lock);
	वापस ret;
पूर्ण

अटल व्योम fabric_event_destroy(काष्ठा fme_perf_priv *priv, u32 event,
				 u32 portid)
अणु
	spin_lock(&priv->fab_lock);
	priv->fab_users--;
	spin_unlock(&priv->fab_lock);
पूर्ण

अटल u64 fabric_पढ़ो_event_counter(काष्ठा fme_perf_priv *priv, u32 event,
				     u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;
	u64 v;

	v = पढ़ोq(base + FAB_CTRL);
	v &= ~FAB_CTRL_EVNT;
	v |= FIELD_PREP(FAB_CTRL_EVNT, event);
	ग_लिखोq(v, base + FAB_CTRL);

	अगर (पढ़ोq_poll_समयout_atomic(base + FAB_CNTR, v,
				      FIELD_GET(FAB_CNTR_EVNT, v) == event,
				      1, PERF_TIMEOUT)) अणु
		dev_err(priv->dev, "timeout, unmatched fab event code in counter register.\n");
		वापस 0;
	पूर्ण

	v = fme_पढ़ो_perf_cntr_reg(base + FAB_CNTR);
	वापस FIELD_GET(FAB_CNTR_EVNT_CNTR, v);
पूर्ण

अटल पूर्णांक vtd_event_init(काष्ठा fme_perf_priv *priv, u32 event, u32 portid)
अणु
	अगर (priv->id == FME_FEATURE_ID_GLOBAL_IPERF &&
	    event <= VTD_EVNT_MAX && is_portid_port(portid))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल u64 vtd_पढ़ो_event_counter(काष्ठा fme_perf_priv *priv, u32 event,
				  u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;
	u64 v;

	event += (portid * (VTD_EVNT_MAX + 1));

	v = पढ़ोq(base + VTD_CTRL);
	v &= ~VTD_CTRL_EVNT;
	v |= FIELD_PREP(VTD_CTRL_EVNT, event);
	ग_लिखोq(v, base + VTD_CTRL);

	अगर (पढ़ोq_poll_समयout_atomic(base + VTD_CNTR, v,
				      FIELD_GET(VTD_CNTR_EVNT, v) == event,
				      1, PERF_TIMEOUT)) अणु
		dev_err(priv->dev, "timeout, unmatched vtd event code in counter register.\n");
		वापस 0;
	पूर्ण

	v = fme_पढ़ो_perf_cntr_reg(base + VTD_CNTR);
	वापस FIELD_GET(VTD_CNTR_EVNT_CNTR, v);
पूर्ण

अटल पूर्णांक vtd_sip_event_init(काष्ठा fme_perf_priv *priv, u32 event, u32 portid)
अणु
	अगर (priv->id == FME_FEATURE_ID_GLOBAL_IPERF &&
	    event <= VTD_SIP_EVNT_MAX && is_portid_root(portid))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल u64 vtd_sip_पढ़ो_event_counter(काष्ठा fme_perf_priv *priv, u32 event,
				      u32 portid)
अणु
	व्योम __iomem *base = priv->ioaddr;
	u64 v;

	v = पढ़ोq(base + VTD_SIP_CTRL);
	v &= ~VTD_SIP_CTRL_EVNT;
	v |= FIELD_PREP(VTD_SIP_CTRL_EVNT, event);
	ग_लिखोq(v, base + VTD_SIP_CTRL);

	अगर (पढ़ोq_poll_समयout_atomic(base + VTD_SIP_CNTR, v,
				      FIELD_GET(VTD_SIP_CNTR_EVNT, v) == event,
				      1, PERF_TIMEOUT)) अणु
		dev_err(priv->dev, "timeout, unmatched vtd sip event code in counter register\n");
		वापस 0;
	पूर्ण

	v = fme_पढ़ो_perf_cntr_reg(base + VTD_SIP_CNTR);
	वापस FIELD_GET(VTD_SIP_CNTR_EVNT_CNTR, v);
पूर्ण

अटल काष्ठा fme_perf_event_ops fme_perf_event_ops[] = अणु
	[FME_EVTYPE_BASIC]	= अणु.event_init = basic_event_init,
				   .पढ़ो_counter = basic_पढ़ो_event_counter,पूर्ण,
	[FME_EVTYPE_CACHE]	= अणु.event_init = cache_event_init,
				   .पढ़ो_counter = cache_पढ़ो_event_counter,पूर्ण,
	[FME_EVTYPE_FABRIC]	= अणु.event_init = fabric_event_init,
				   .event_destroy = fabric_event_destroy,
				   .पढ़ो_counter = fabric_पढ़ो_event_counter,पूर्ण,
	[FME_EVTYPE_VTD]	= अणु.event_init = vtd_event_init,
				   .पढ़ो_counter = vtd_पढ़ो_event_counter,पूर्ण,
	[FME_EVTYPE_VTD_SIP]	= अणु.event_init = vtd_sip_event_init,
				   .पढ़ो_counter = vtd_sip_पढ़ो_event_counter,पूर्ण,
पूर्ण;

अटल sमाप_प्रकार fme_perf_event_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;
	अचिन्हित दीर्घ config;
	अक्षर *ptr = buf;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	config = (अचिन्हित दीर्घ)eattr->var;

	ptr += प्र_लिखो(ptr, "event=0x%02x", (अचिन्हित पूर्णांक)get_event(config));
	ptr += प्र_लिखो(ptr, ",evtype=0x%02x", (अचिन्हित पूर्णांक)get_evtype(config));

	अगर (is_portid_root(get_portid(config)))
		ptr += प्र_लिखो(ptr, ",portid=0x%02x\n", FME_PORTID_ROOT);
	अन्यथा
		ptr += प्र_लिखो(ptr, ",portid=?\n");

	वापस (sमाप_प्रकार)(ptr - buf);
पूर्ण

#घोषणा FME_EVENT_ATTR(_name) \
	__ATTR(_name, 0444, fme_perf_event_show, शून्य)

#घोषणा FME_PORT_EVENT_CONFIG(_event, _type)				\
	(व्योम *)((((_event) << FME_EVENT_SHIFT) & FME_EVENT_MASK) |	\
		(((_type) << FME_EVTYPE_SHIFT) & FME_EVTYPE_MASK))

#घोषणा FME_EVENT_CONFIG(_event, _type)					\
	(व्योम *)((((_event) << FME_EVENT_SHIFT) & FME_EVENT_MASK) |	\
		(((_type) << FME_EVTYPE_SHIFT) & FME_EVTYPE_MASK) |	\
		(FME_PORTID_ROOT << FME_PORTID_SHIFT))

/* FME Perf Basic Events */
#घोषणा FME_EVENT_BASIC(_name, _event)					\
अटल काष्ठा dev_ext_attribute fme_perf_event_##_name = अणु		\
	.attr = FME_EVENT_ATTR(_name),					\
	.var = FME_EVENT_CONFIG(_event, FME_EVTYPE_BASIC),		\
पूर्ण

FME_EVENT_BASIC(घड़ी, BASIC_EVNT_CLK);

अटल काष्ठा attribute *fme_perf_basic_events_attrs[] = अणु
	&fme_perf_event_घड़ी.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_basic_events_group = अणु
	.name = "events",
	.attrs = fme_perf_basic_events_attrs,
पूर्ण;

/* FME Perf Cache Events */
#घोषणा FME_EVENT_CACHE(_name, _event)					\
अटल काष्ठा dev_ext_attribute fme_perf_event_cache_##_name = अणु	\
	.attr = FME_EVENT_ATTR(cache_##_name),				\
	.var = FME_EVENT_CONFIG(_event, FME_EVTYPE_CACHE),		\
पूर्ण

FME_EVENT_CACHE(पढ़ो_hit,     CACHE_EVNT_RD_HIT);
FME_EVENT_CACHE(पढ़ो_miss,    CACHE_EVNT_RD_MISS);
FME_EVENT_CACHE(ग_लिखो_hit,    CACHE_EVNT_WR_HIT);
FME_EVENT_CACHE(ग_लिखो_miss,   CACHE_EVNT_WR_MISS);
FME_EVENT_CACHE(hold_request, CACHE_EVNT_HOLD_REQ);
FME_EVENT_CACHE(tx_req_stall, CACHE_EVNT_TX_REQ_STALL);
FME_EVENT_CACHE(rx_req_stall, CACHE_EVNT_RX_REQ_STALL);
FME_EVENT_CACHE(eviction,     CACHE_EVNT_EVICTIONS);
FME_EVENT_CACHE(data_ग_लिखो_port_contention, CACHE_EVNT_DATA_WR_PORT_CONTEN);
FME_EVENT_CACHE(tag_ग_लिखो_port_contention,  CACHE_EVNT_TAG_WR_PORT_CONTEN);

अटल काष्ठा attribute *fme_perf_cache_events_attrs[] = अणु
	&fme_perf_event_cache_पढ़ो_hit.attr.attr,
	&fme_perf_event_cache_पढ़ो_miss.attr.attr,
	&fme_perf_event_cache_ग_लिखो_hit.attr.attr,
	&fme_perf_event_cache_ग_लिखो_miss.attr.attr,
	&fme_perf_event_cache_hold_request.attr.attr,
	&fme_perf_event_cache_tx_req_stall.attr.attr,
	&fme_perf_event_cache_rx_req_stall.attr.attr,
	&fme_perf_event_cache_eviction.attr.attr,
	&fme_perf_event_cache_data_ग_लिखो_port_contention.attr.attr,
	&fme_perf_event_cache_tag_ग_लिखो_port_contention.attr.attr,
	शून्य,
पूर्ण;

अटल umode_t fme_perf_events_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(kobj_to_dev(kobj));
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(pmu);

	वापस (priv->id == FME_FEATURE_ID_GLOBAL_IPERF) ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group fme_perf_cache_events_group = अणु
	.name = "events",
	.attrs = fme_perf_cache_events_attrs,
	.is_visible = fme_perf_events_visible,
पूर्ण;

/* FME Perf Fabric Events */
#घोषणा FME_EVENT_FABRIC(_name, _event)					\
अटल काष्ठा dev_ext_attribute fme_perf_event_fab_##_name = अणु		\
	.attr = FME_EVENT_ATTR(fab_##_name),				\
	.var = FME_EVENT_CONFIG(_event, FME_EVTYPE_FABRIC),		\
पूर्ण

#घोषणा FME_EVENT_FABRIC_PORT(_name, _event)				\
अटल काष्ठा dev_ext_attribute fme_perf_event_fab_port_##_name = अणु	\
	.attr = FME_EVENT_ATTR(fab_port_##_name),			\
	.var = FME_PORT_EVENT_CONFIG(_event, FME_EVTYPE_FABRIC),	\
पूर्ण

FME_EVENT_FABRIC(pcie0_पढ़ो,  FAB_EVNT_PCIE0_RD);
FME_EVENT_FABRIC(pcie0_ग_लिखो, FAB_EVNT_PCIE0_WR);
FME_EVENT_FABRIC(pcie1_पढ़ो,  FAB_EVNT_PCIE1_RD);
FME_EVENT_FABRIC(pcie1_ग_लिखो, FAB_EVNT_PCIE1_WR);
FME_EVENT_FABRIC(upi_पढ़ो,    FAB_EVNT_UPI_RD);
FME_EVENT_FABRIC(upi_ग_लिखो,   FAB_EVNT_UPI_WR);
FME_EVENT_FABRIC(mmio_पढ़ो,   FAB_EVNT_MMIO_RD);
FME_EVENT_FABRIC(mmio_ग_लिखो,  FAB_EVNT_MMIO_WR);

FME_EVENT_FABRIC_PORT(pcie0_पढ़ो,  FAB_EVNT_PCIE0_RD);
FME_EVENT_FABRIC_PORT(pcie0_ग_लिखो, FAB_EVNT_PCIE0_WR);
FME_EVENT_FABRIC_PORT(pcie1_पढ़ो,  FAB_EVNT_PCIE1_RD);
FME_EVENT_FABRIC_PORT(pcie1_ग_लिखो, FAB_EVNT_PCIE1_WR);
FME_EVENT_FABRIC_PORT(upi_पढ़ो,    FAB_EVNT_UPI_RD);
FME_EVENT_FABRIC_PORT(upi_ग_लिखो,   FAB_EVNT_UPI_WR);
FME_EVENT_FABRIC_PORT(mmio_पढ़ो,   FAB_EVNT_MMIO_RD);
FME_EVENT_FABRIC_PORT(mmio_ग_लिखो,  FAB_EVNT_MMIO_WR);

अटल काष्ठा attribute *fme_perf_fabric_events_attrs[] = अणु
	&fme_perf_event_fab_pcie0_पढ़ो.attr.attr,
	&fme_perf_event_fab_pcie0_ग_लिखो.attr.attr,
	&fme_perf_event_fab_pcie1_पढ़ो.attr.attr,
	&fme_perf_event_fab_pcie1_ग_लिखो.attr.attr,
	&fme_perf_event_fab_upi_पढ़ो.attr.attr,
	&fme_perf_event_fab_upi_ग_लिखो.attr.attr,
	&fme_perf_event_fab_mmio_पढ़ो.attr.attr,
	&fme_perf_event_fab_mmio_ग_लिखो.attr.attr,
	&fme_perf_event_fab_port_pcie0_पढ़ो.attr.attr,
	&fme_perf_event_fab_port_pcie0_ग_लिखो.attr.attr,
	&fme_perf_event_fab_port_pcie1_पढ़ो.attr.attr,
	&fme_perf_event_fab_port_pcie1_ग_लिखो.attr.attr,
	&fme_perf_event_fab_port_upi_पढ़ो.attr.attr,
	&fme_perf_event_fab_port_upi_ग_लिखो.attr.attr,
	&fme_perf_event_fab_port_mmio_पढ़ो.attr.attr,
	&fme_perf_event_fab_port_mmio_ग_लिखो.attr.attr,
	शून्य,
पूर्ण;

अटल umode_t fme_perf_fabric_events_visible(काष्ठा kobject *kobj,
					      काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(kobj_to_dev(kobj));
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(pmu);
	काष्ठा dev_ext_attribute *eattr;
	अचिन्हित दीर्घ var;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr.attr);
	var = (अचिन्हित दीर्घ)eattr->var;

	अगर (is_fabric_event_supported(priv, get_event(var), get_portid(var)))
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group fme_perf_fabric_events_group = अणु
	.name = "events",
	.attrs = fme_perf_fabric_events_attrs,
	.is_visible = fme_perf_fabric_events_visible,
पूर्ण;

/* FME Perf VTD Events */
#घोषणा FME_EVENT_VTD_PORT(_name, _event)				\
अटल काष्ठा dev_ext_attribute fme_perf_event_vtd_port_##_name = अणु	\
	.attr = FME_EVENT_ATTR(vtd_port_##_name),			\
	.var = FME_PORT_EVENT_CONFIG(_event, FME_EVTYPE_VTD),		\
पूर्ण

FME_EVENT_VTD_PORT(पढ़ो_transaction,  VTD_EVNT_AFU_MEM_RD_TRANS);
FME_EVENT_VTD_PORT(ग_लिखो_transaction, VTD_EVNT_AFU_MEM_WR_TRANS);
FME_EVENT_VTD_PORT(devtlb_पढ़ो_hit,   VTD_EVNT_AFU_DEVTLB_RD_HIT);
FME_EVENT_VTD_PORT(devtlb_ग_लिखो_hit,  VTD_EVNT_AFU_DEVTLB_WR_HIT);
FME_EVENT_VTD_PORT(devtlb_4k_fill,    VTD_EVNT_DEVTLB_4K_FILL);
FME_EVENT_VTD_PORT(devtlb_2m_fill,    VTD_EVNT_DEVTLB_2M_FILL);
FME_EVENT_VTD_PORT(devtlb_1g_fill,    VTD_EVNT_DEVTLB_1G_FILL);

अटल काष्ठा attribute *fme_perf_vtd_events_attrs[] = अणु
	&fme_perf_event_vtd_port_पढ़ो_transaction.attr.attr,
	&fme_perf_event_vtd_port_ग_लिखो_transaction.attr.attr,
	&fme_perf_event_vtd_port_devtlb_पढ़ो_hit.attr.attr,
	&fme_perf_event_vtd_port_devtlb_ग_लिखो_hit.attr.attr,
	&fme_perf_event_vtd_port_devtlb_4k_fill.attr.attr,
	&fme_perf_event_vtd_port_devtlb_2m_fill.attr.attr,
	&fme_perf_event_vtd_port_devtlb_1g_fill.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_vtd_events_group = अणु
	.name = "events",
	.attrs = fme_perf_vtd_events_attrs,
	.is_visible = fme_perf_events_visible,
पूर्ण;

/* FME Perf VTD SIP Events */
#घोषणा FME_EVENT_VTD_SIP(_name, _event)				\
अटल काष्ठा dev_ext_attribute fme_perf_event_vtd_sip_##_name = अणु	\
	.attr = FME_EVENT_ATTR(vtd_sip_##_name),			\
	.var = FME_EVENT_CONFIG(_event, FME_EVTYPE_VTD_SIP),		\
पूर्ण

FME_EVENT_VTD_SIP(iotlb_4k_hit,  VTD_SIP_EVNT_IOTLB_4K_HIT);
FME_EVENT_VTD_SIP(iotlb_2m_hit,  VTD_SIP_EVNT_IOTLB_2M_HIT);
FME_EVENT_VTD_SIP(iotlb_1g_hit,  VTD_SIP_EVNT_IOTLB_1G_HIT);
FME_EVENT_VTD_SIP(slpwc_l3_hit,  VTD_SIP_EVNT_SLPWC_L3_HIT);
FME_EVENT_VTD_SIP(slpwc_l4_hit,  VTD_SIP_EVNT_SLPWC_L4_HIT);
FME_EVENT_VTD_SIP(rcc_hit,       VTD_SIP_EVNT_RCC_HIT);
FME_EVENT_VTD_SIP(iotlb_4k_miss, VTD_SIP_EVNT_IOTLB_4K_MISS);
FME_EVENT_VTD_SIP(iotlb_2m_miss, VTD_SIP_EVNT_IOTLB_2M_MISS);
FME_EVENT_VTD_SIP(iotlb_1g_miss, VTD_SIP_EVNT_IOTLB_1G_MISS);
FME_EVENT_VTD_SIP(slpwc_l3_miss, VTD_SIP_EVNT_SLPWC_L3_MISS);
FME_EVENT_VTD_SIP(slpwc_l4_miss, VTD_SIP_EVNT_SLPWC_L4_MISS);
FME_EVENT_VTD_SIP(rcc_miss,      VTD_SIP_EVNT_RCC_MISS);

अटल काष्ठा attribute *fme_perf_vtd_sip_events_attrs[] = अणु
	&fme_perf_event_vtd_sip_iotlb_4k_hit.attr.attr,
	&fme_perf_event_vtd_sip_iotlb_2m_hit.attr.attr,
	&fme_perf_event_vtd_sip_iotlb_1g_hit.attr.attr,
	&fme_perf_event_vtd_sip_slpwc_l3_hit.attr.attr,
	&fme_perf_event_vtd_sip_slpwc_l4_hit.attr.attr,
	&fme_perf_event_vtd_sip_rcc_hit.attr.attr,
	&fme_perf_event_vtd_sip_iotlb_4k_miss.attr.attr,
	&fme_perf_event_vtd_sip_iotlb_2m_miss.attr.attr,
	&fme_perf_event_vtd_sip_iotlb_1g_miss.attr.attr,
	&fme_perf_event_vtd_sip_slpwc_l3_miss.attr.attr,
	&fme_perf_event_vtd_sip_slpwc_l4_miss.attr.attr,
	&fme_perf_event_vtd_sip_rcc_miss.attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fme_perf_vtd_sip_events_group = अणु
	.name = "events",
	.attrs = fme_perf_vtd_sip_events_attrs,
	.is_visible = fme_perf_events_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fme_perf_events_groups[] = अणु
	&fme_perf_basic_events_group,
	&fme_perf_cache_events_group,
	&fme_perf_fabric_events_group,
	&fme_perf_vtd_events_group,
	&fme_perf_vtd_sip_events_group,
	शून्य,
पूर्ण;

अटल काष्ठा fme_perf_event_ops *get_event_ops(u32 evtype)
अणु
	अगर (evtype > FME_EVTYPE_MAX)
		वापस शून्य;

	वापस &fme_perf_event_ops[evtype];
पूर्ण

अटल व्योम fme_perf_event_destroy(काष्ठा perf_event *event)
अणु
	काष्ठा fme_perf_event_ops *ops = get_event_ops(event->hw.event_base);
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(event->pmu);

	अगर (ops->event_destroy)
		ops->event_destroy(priv, event->hw.idx, event->hw.config_base);
पूर्ण

अटल पूर्णांक fme_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा fme_perf_event_ops *ops;
	u32 eventid, evtype, portid;

	/* test the event attr type check क्रम PMU क्रमागतeration */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * fme counters are shared across all cores.
	 * Thereक्रमe, it करोes not support per-process mode.
	 * Also, it करोes not support event sampling mode.
	 */
	अगर (is_sampling_event(event) || event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	अगर (event->cpu != priv->cpu)
		वापस -EINVAL;

	eventid = get_event(event->attr.config);
	portid = get_portid(event->attr.config);
	evtype = get_evtype(event->attr.config);
	अगर (evtype > FME_EVTYPE_MAX)
		वापस -EINVAL;

	hwc->event_base = evtype;
	hwc->idx = (पूर्णांक)eventid;
	hwc->config_base = portid;

	event->destroy = fme_perf_event_destroy;

	dev_dbg(priv->dev, "%s event=0x%x, evtype=0x%x, portid=0x%x,\n",
		__func__, eventid, evtype, portid);

	ops = get_event_ops(evtype);
	अगर (ops->event_init)
		वापस ops->event_init(priv, eventid, portid);

	वापस 0;
पूर्ण

अटल व्योम fme_perf_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा fme_perf_event_ops *ops = get_event_ops(event->hw.event_base);
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 now, prev, delta;

	now = ops->पढ़ो_counter(priv, (u32)hwc->idx, hwc->config_base);
	prev = local64_पढ़ो(&hwc->prev_count);
	delta = now - prev;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम fme_perf_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा fme_perf_event_ops *ops = get_event_ops(event->hw.event_base);
	काष्ठा fme_perf_priv *priv = to_fme_perf_priv(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 count;

	count = ops->पढ़ो_counter(priv, (u32)hwc->idx, hwc->config_base);
	local64_set(&hwc->prev_count, count);
पूर्ण

अटल व्योम fme_perf_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	fme_perf_event_update(event);
पूर्ण

अटल पूर्णांक fme_perf_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		fme_perf_event_start(event, flags);

	वापस 0;
पूर्ण

अटल व्योम fme_perf_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	fme_perf_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल व्योम fme_perf_event_पढ़ो(काष्ठा perf_event *event)
अणु
	fme_perf_event_update(event);
पूर्ण

अटल व्योम fme_perf_setup_hardware(काष्ठा fme_perf_priv *priv)
अणु
	व्योम __iomem *base = priv->ioaddr;
	u64 v;

	/* पढ़ो and save current working mode क्रम fabric counters */
	v = पढ़ोq(base + FAB_CTRL);

	अगर (FIELD_GET(FAB_PORT_FILTER, v) == FAB_PORT_FILTER_DISABLE)
		priv->fab_port_id = FME_PORTID_ROOT;
	अन्यथा
		priv->fab_port_id = FIELD_GET(FAB_PORT_ID, v);
पूर्ण

अटल पूर्णांक fme_perf_pmu_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
				 काष्ठा fme_perf_priv *priv)
अणु
	काष्ठा pmu *pmu = &priv->pmu;
	अक्षर *name;
	पूर्णांक ret;

	spin_lock_init(&priv->fab_lock);

	fme_perf_setup_hardware(priv);

	pmu->task_ctx_nr =	perf_invalid_context;
	pmu->attr_groups =	fme_perf_groups;
	pmu->attr_update =	fme_perf_events_groups;
	pmu->event_init =	fme_perf_event_init;
	pmu->add =		fme_perf_event_add;
	pmu->del =		fme_perf_event_del;
	pmu->start =		fme_perf_event_start;
	pmu->stop =		fme_perf_event_stop;
	pmu->पढ़ो =		fme_perf_event_पढ़ो;
	pmu->capabilities =	PERF_PMU_CAP_NO_INTERRUPT |
				PERF_PMU_CAP_NO_EXCLUDE;

	name = devm_kaप्र_लिखो(priv->dev, GFP_KERNEL, "dfl_fme%d", pdev->id);

	ret = perf_pmu_रेजिस्टर(pmu, name, -1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम fme_perf_pmu_unरेजिस्टर(काष्ठा fme_perf_priv *priv)
अणु
	perf_pmu_unरेजिस्टर(&priv->pmu);
पूर्ण

अटल पूर्णांक fme_perf_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा fme_perf_priv *priv;
	पूर्णांक target;

	priv = hlist_entry_safe(node, काष्ठा fme_perf_priv, node);

	अगर (cpu != priv->cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	priv->cpu = target;
	वापस 0;
पूर्ण

अटल पूर्णांक fme_perf_init(काष्ठा platक्रमm_device *pdev,
			 काष्ठा dfl_feature *feature)
अणु
	काष्ठा fme_perf_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->ioaddr = feature->ioaddr;
	priv->id = feature->id;
	priv->cpu = raw_smp_processor_id();

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      "perf/fpga/dfl_fme:online",
				      शून्य, fme_perf_offline_cpu);
	अगर (ret < 0)
		वापस ret;

	priv->cpuhp_state = ret;

	/* Register the pmu instance क्रम cpu hotplug */
	ret = cpuhp_state_add_instance_nocalls(priv->cpuhp_state, &priv->node);
	अगर (ret)
		जाओ cpuhp_instance_err;

	ret = fme_perf_pmu_रेजिस्टर(pdev, priv);
	अगर (ret)
		जाओ pmu_रेजिस्टर_err;

	feature->priv = priv;
	वापस 0;

pmu_रेजिस्टर_err:
	cpuhp_state_हटाओ_instance_nocalls(priv->cpuhp_state, &priv->node);
cpuhp_instance_err:
	cpuhp_हटाओ_multi_state(priv->cpuhp_state);
	वापस ret;
पूर्ण

अटल व्योम fme_perf_uinit(काष्ठा platक्रमm_device *pdev,
			   काष्ठा dfl_feature *feature)
अणु
	काष्ठा fme_perf_priv *priv = feature->priv;

	fme_perf_pmu_unरेजिस्टर(priv);
	cpuhp_state_हटाओ_instance_nocalls(priv->cpuhp_state, &priv->node);
	cpuhp_हटाओ_multi_state(priv->cpuhp_state);
पूर्ण

स्थिर काष्ठा dfl_feature_id fme_perf_id_table[] = अणु
	अणु.id = FME_FEATURE_ID_GLOBAL_IPERF,पूर्ण,
	अणु.id = FME_FEATURE_ID_GLOBAL_DPERF,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

स्थिर काष्ठा dfl_feature_ops fme_perf_ops = अणु
	.init = fme_perf_init,
	.uinit = fme_perf_uinit,
पूर्ण;
