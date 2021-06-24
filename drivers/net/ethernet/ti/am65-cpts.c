<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* TI K3 AM65x Common Platक्रमm Time Sync
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश "am65-cpts.h"

काष्ठा am65_genf_regs अणु
	u32 comp_lo;	/* Comparison Low Value 0:31 */
	u32 comp_hi;	/* Comparison High Value 32:63 */
	u32 control;	/* control */
	u32 length;	/* Length */
	u32 ppm_low;	/* PPM Load Low Value 0:31 */
	u32 ppm_hi;	/* PPM Load High Value 32:63 */
	u32 ts_nudge;	/* Nudge value */
पूर्ण __aligned(32) __packed;

#घोषणा AM65_CPTS_GENF_MAX_NUM 9
#घोषणा AM65_CPTS_ESTF_MAX_NUM 8

काष्ठा am65_cpts_regs अणु
	u32 idver;		/* Identअगरication and version */
	u32 control;		/* Time sync control */
	u32 rftclk_sel;		/* Reference Clock Select Register */
	u32 ts_push;		/* Time stamp event push */
	u32 ts_load_val_lo;	/* Time Stamp Load Low Value 0:31 */
	u32 ts_load_en;		/* Time stamp load enable */
	u32 ts_comp_lo;		/* Time Stamp Comparison Low Value 0:31 */
	u32 ts_comp_length;	/* Time Stamp Comparison Length */
	u32 पूर्णांकstat_raw;	/* Time sync पूर्णांकerrupt status raw */
	u32 पूर्णांकstat_masked;	/* Time sync पूर्णांकerrupt status masked */
	u32 पूर्णांक_enable;		/* Time sync पूर्णांकerrupt enable */
	u32 ts_comp_nudge;	/* Time Stamp Comparison Nudge Value */
	u32 event_pop;		/* Event पूर्णांकerrupt pop */
	u32 event_0;		/* Event Time Stamp lo 0:31 */
	u32 event_1;		/* Event Type Fields */
	u32 event_2;		/* Event Type Fields करोमुख्य */
	u32 event_3;		/* Event Time Stamp hi 32:63 */
	u32 ts_load_val_hi;	/* Time Stamp Load High Value 32:63 */
	u32 ts_comp_hi;		/* Time Stamp Comparison High Value 32:63 */
	u32 ts_add_val;		/* Time Stamp Add value */
	u32 ts_ppm_low;		/* Time Stamp PPM Load Low Value 0:31 */
	u32 ts_ppm_hi;		/* Time Stamp PPM Load High Value 32:63 */
	u32 ts_nudge;		/* Time Stamp Nudge value */
	u32 reserv[33];
	काष्ठा am65_genf_regs genf[AM65_CPTS_GENF_MAX_NUM];
	काष्ठा am65_genf_regs estf[AM65_CPTS_ESTF_MAX_NUM];
पूर्ण;

/* CONTROL_REG */
#घोषणा AM65_CPTS_CONTROL_EN			BIT(0)
#घोषणा AM65_CPTS_CONTROL_INT_TEST		BIT(1)
#घोषणा AM65_CPTS_CONTROL_TS_COMP_POLARITY	BIT(2)
#घोषणा AM65_CPTS_CONTROL_TSTAMP_EN		BIT(3)
#घोषणा AM65_CPTS_CONTROL_SEQUENCE_EN		BIT(4)
#घोषणा AM65_CPTS_CONTROL_64MODE		BIT(5)
#घोषणा AM65_CPTS_CONTROL_TS_COMP_TOG		BIT(6)
#घोषणा AM65_CPTS_CONTROL_TS_PPM_सूची		BIT(7)
#घोषणा AM65_CPTS_CONTROL_HW1_TS_PUSH_EN	BIT(8)
#घोषणा AM65_CPTS_CONTROL_HW2_TS_PUSH_EN	BIT(9)
#घोषणा AM65_CPTS_CONTROL_HW3_TS_PUSH_EN	BIT(10)
#घोषणा AM65_CPTS_CONTROL_HW4_TS_PUSH_EN	BIT(11)
#घोषणा AM65_CPTS_CONTROL_HW5_TS_PUSH_EN	BIT(12)
#घोषणा AM65_CPTS_CONTROL_HW6_TS_PUSH_EN	BIT(13)
#घोषणा AM65_CPTS_CONTROL_HW7_TS_PUSH_EN	BIT(14)
#घोषणा AM65_CPTS_CONTROL_HW8_TS_PUSH_EN	BIT(15)
#घोषणा AM65_CPTS_CONTROL_HW1_TS_PUSH_OFFSET	(8)

#घोषणा AM65_CPTS_CONTROL_TX_GENF_CLR_EN	BIT(17)

#घोषणा AM65_CPTS_CONTROL_TS_SYNC_SEL_MASK	(0xF)
#घोषणा AM65_CPTS_CONTROL_TS_SYNC_SEL_SHIFT	(28)

/* RFTCLK_SEL_REG */
#घोषणा AM65_CPTS_RFTCLK_SEL_MASK		(0x1F)

/* TS_PUSH_REG */
#घोषणा AM65_CPTS_TS_PUSH			BIT(0)

/* TS_LOAD_EN_REG */
#घोषणा AM65_CPTS_TS_LOAD_EN			BIT(0)

/* INTSTAT_RAW_REG */
#घोषणा AM65_CPTS_INTSTAT_RAW_TS_PEND		BIT(0)

/* INTSTAT_MASKED_REG */
#घोषणा AM65_CPTS_INTSTAT_MASKED_TS_PEND	BIT(0)

/* INT_ENABLE_REG */
#घोषणा AM65_CPTS_INT_ENABLE_TS_PEND_EN		BIT(0)

/* TS_COMP_NUDGE_REG */
#घोषणा AM65_CPTS_TS_COMP_NUDGE_MASK		(0xFF)

/* EVENT_POP_REG */
#घोषणा AM65_CPTS_EVENT_POP			BIT(0)

/* EVENT_1_REG */
#घोषणा AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK	GENMASK(15, 0)

#घोषणा AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK	GENMASK(19, 16)
#घोषणा AM65_CPTS_EVENT_1_MESSAGE_TYPE_SHIFT	(16)

#घोषणा AM65_CPTS_EVENT_1_EVENT_TYPE_MASK	GENMASK(23, 20)
#घोषणा AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT	(20)

#घोषणा AM65_CPTS_EVENT_1_PORT_NUMBER_MASK	GENMASK(28, 24)
#घोषणा AM65_CPTS_EVENT_1_PORT_NUMBER_SHIFT	(24)

/* EVENT_2_REG */
#घोषणा AM65_CPTS_EVENT_2_REG_DOMAIN_MASK	(0xFF)
#घोषणा AM65_CPTS_EVENT_2_REG_DOMAIN_SHIFT	(0)

क्रमागत अणु
	AM65_CPTS_EV_PUSH,	/* Time Stamp Push Event */
	AM65_CPTS_EV_ROLL,	/* Time Stamp Rollover Event */
	AM65_CPTS_EV_HALF,	/* Time Stamp Half Rollover Event */
	AM65_CPTS_EV_HW,		/* Hardware Time Stamp Push Event */
	AM65_CPTS_EV_RX,		/* Ethernet Receive Event */
	AM65_CPTS_EV_TX,		/* Ethernet Transmit Event */
	AM65_CPTS_EV_TS_COMP,	/* Time Stamp Compare Event */
	AM65_CPTS_EV_HOST,	/* Host Transmit Event */
पूर्ण;

काष्ठा am65_cpts_event अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ पंचांगo;
	u32 event1;
	u32 event2;
	u64 बारtamp;
पूर्ण;

#घोषणा AM65_CPTS_FIFO_DEPTH		(16)
#घोषणा AM65_CPTS_MAX_EVENTS		(32)
#घोषणा AM65_CPTS_EVENT_RX_TX_TIMEOUT	(20) /* ms */
#घोषणा AM65_CPTS_SKB_TX_WORK_TIMEOUT	1 /* jअगरfies */
#घोषणा AM65_CPTS_MIN_PPM		0x400

काष्ठा am65_cpts अणु
	काष्ठा device *dev;
	काष्ठा am65_cpts_regs __iomem *reg;
	काष्ठा ptp_घड़ी_info ptp_info;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	पूर्णांक phc_index;
	काष्ठा clk_hw *clk_mux_hw;
	काष्ठा device_node *clk_mux_np;
	काष्ठा clk *refclk;
	u32 refclk_freq;
	काष्ठा list_head events;
	काष्ठा list_head pool;
	काष्ठा am65_cpts_event pool_data[AM65_CPTS_MAX_EVENTS];
	spinlock_t lock; /* protects events lists*/
	u32 ext_ts_inमाला_दो;
	u32 genf_num;
	u32 ts_add_val;
	पूर्णांक irq;
	काष्ठा mutex ptp_clk_lock; /* PHC access sync */
	u64 बारtamp;
	u32 genf_enable;
	u32 hw_ts_enable;
	काष्ठा sk_buff_head txq;
पूर्ण;

काष्ठा am65_cpts_skb_cb_data अणु
	अचिन्हित दीर्घ पंचांगo;
	u32 skb_mtype_seqid;
पूर्ण;

#घोषणा am65_cpts_ग_लिखो32(c, v, r) ग_लिखोl(v, &(c)->reg->r)
#घोषणा am65_cpts_पढ़ो32(c, r) पढ़ोl(&(c)->reg->r)

अटल व्योम am65_cpts_समय_रखो(काष्ठा am65_cpts *cpts, u64 start_tstamp)
अणु
	u32 val;

	val = upper_32_bits(start_tstamp);
	am65_cpts_ग_लिखो32(cpts, val, ts_load_val_hi);
	val = lower_32_bits(start_tstamp);
	am65_cpts_ग_लिखो32(cpts, val, ts_load_val_lo);

	am65_cpts_ग_लिखो32(cpts, AM65_CPTS_TS_LOAD_EN, ts_load_en);
पूर्ण

अटल व्योम am65_cpts_set_add_val(काष्ठा am65_cpts *cpts)
अणु
	/* select coefficient according to the rate */
	cpts->ts_add_val = (NSEC_PER_SEC / cpts->refclk_freq - 1) & 0x7;

	am65_cpts_ग_लिखो32(cpts, cpts->ts_add_val, ts_add_val);
पूर्ण

अटल व्योम am65_cpts_disable(काष्ठा am65_cpts *cpts)
अणु
	am65_cpts_ग_लिखो32(cpts, 0, control);
	am65_cpts_ग_लिखो32(cpts, 0, पूर्णांक_enable);
पूर्ण

अटल पूर्णांक am65_cpts_event_get_port(काष्ठा am65_cpts_event *event)
अणु
	वापस (event->event1 & AM65_CPTS_EVENT_1_PORT_NUMBER_MASK) >>
		AM65_CPTS_EVENT_1_PORT_NUMBER_SHIFT;
पूर्ण

अटल पूर्णांक am65_cpts_event_get_type(काष्ठा am65_cpts_event *event)
अणु
	वापस (event->event1 & AM65_CPTS_EVENT_1_EVENT_TYPE_MASK) >>
		AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT;
पूर्ण

अटल पूर्णांक am65_cpts_cpts_purge_events(काष्ठा am65_cpts *cpts)
अणु
	काष्ठा list_head *this, *next;
	काष्ठा am65_cpts_event *event;
	पूर्णांक हटाओd = 0;

	list_क्रम_each_safe(this, next, &cpts->events) अणु
		event = list_entry(this, काष्ठा am65_cpts_event, list);
		अगर (समय_after(jअगरfies, event->पंचांगo)) अणु
			list_del_init(&event->list);
			list_add(&event->list, &cpts->pool);
			++हटाओd;
		पूर्ण
	पूर्ण

	अगर (हटाओd)
		dev_dbg(cpts->dev, "event pool cleaned up %d\n", हटाओd);
	वापस हटाओd ? 0 : -1;
पूर्ण

अटल bool am65_cpts_fअगरo_pop_event(काष्ठा am65_cpts *cpts,
				     काष्ठा am65_cpts_event *event)
अणु
	u32 r = am65_cpts_पढ़ो32(cpts, पूर्णांकstat_raw);

	अगर (r & AM65_CPTS_INTSTAT_RAW_TS_PEND) अणु
		event->बारtamp = am65_cpts_पढ़ो32(cpts, event_0);
		event->event1 = am65_cpts_पढ़ो32(cpts, event_1);
		event->event2 = am65_cpts_पढ़ो32(cpts, event_2);
		event->बारtamp |= (u64)am65_cpts_पढ़ो32(cpts, event_3) << 32;
		am65_cpts_ग_लिखो32(cpts, AM65_CPTS_EVENT_POP, event_pop);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक am65_cpts_fअगरo_पढ़ो(काष्ठा am65_cpts *cpts)
अणु
	काष्ठा ptp_घड़ी_event pevent;
	काष्ठा am65_cpts_event *event;
	bool schedule = false;
	पूर्णांक i, type, ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cpts->lock, flags);
	क्रम (i = 0; i < AM65_CPTS_FIFO_DEPTH; i++) अणु
		event = list_first_entry_or_null(&cpts->pool,
						 काष्ठा am65_cpts_event, list);

		अगर (!event) अणु
			अगर (am65_cpts_cpts_purge_events(cpts)) अणु
				dev_err(cpts->dev, "cpts: event pool empty\n");
				ret = -1;
				जाओ out;
			पूर्ण
			जारी;
		पूर्ण

		अगर (am65_cpts_fअगरo_pop_event(cpts, event))
			अवरोध;

		type = am65_cpts_event_get_type(event);
		चयन (type) अणु
		हाल AM65_CPTS_EV_PUSH:
			cpts->बारtamp = event->बारtamp;
			dev_dbg(cpts->dev, "AM65_CPTS_EV_PUSH t:%llu\n",
				cpts->बारtamp);
			अवरोध;
		हाल AM65_CPTS_EV_RX:
		हाल AM65_CPTS_EV_TX:
			event->पंचांगo = jअगरfies +
				msecs_to_jअगरfies(AM65_CPTS_EVENT_RX_TX_TIMEOUT);

			list_del_init(&event->list);
			list_add_tail(&event->list, &cpts->events);

			dev_dbg(cpts->dev,
				"AM65_CPTS_EV_TX e1:%08x e2:%08x t:%lld\n",
				event->event1, event->event2,
				event->बारtamp);
			schedule = true;
			अवरोध;
		हाल AM65_CPTS_EV_HW:
			pevent.index = am65_cpts_event_get_port(event) - 1;
			pevent.बारtamp = event->बारtamp;
			pevent.type = PTP_CLOCK_EXTTS;
			dev_dbg(cpts->dev, "AM65_CPTS_EV_HW p:%d t:%llu\n",
				pevent.index, event->बारtamp);

			ptp_घड़ी_event(cpts->ptp_घड़ी, &pevent);
			अवरोध;
		हाल AM65_CPTS_EV_HOST:
			अवरोध;
		हाल AM65_CPTS_EV_ROLL:
		हाल AM65_CPTS_EV_HALF:
		हाल AM65_CPTS_EV_TS_COMP:
			dev_dbg(cpts->dev,
				"AM65_CPTS_EVT: %d e1:%08x e2:%08x t:%lld\n",
				type,
				event->event1, event->event2,
				event->बारtamp);
			अवरोध;
		शेष:
			dev_err(cpts->dev, "cpts: unknown event type\n");
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&cpts->lock, flags);

	अगर (schedule)
		ptp_schedule_worker(cpts->ptp_घड़ी, 0);

	वापस ret;
पूर्ण

अटल u64 am65_cpts_समय_लो(काष्ठा am65_cpts *cpts,
			     काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	अचिन्हित दीर्घ flags;
	u64 val = 0;

	/* temporarily disable cpts पूर्णांकerrupt to aव्योम पूर्णांकentional
	 * द्विगुनd पढ़ो. Interrupt can be in-flight - it's Ok.
	 */
	am65_cpts_ग_लिखो32(cpts, 0, पूर्णांक_enable);

	/* use spin_lock_irqsave() here as it has to run very fast */
	spin_lock_irqsave(&cpts->lock, flags);
	ptp_पढ़ो_प्रणाली_prets(sts);
	am65_cpts_ग_लिखो32(cpts, AM65_CPTS_TS_PUSH, ts_push);
	am65_cpts_पढ़ो32(cpts, ts_push);
	ptp_पढ़ो_प्रणाली_postts(sts);
	spin_unlock_irqrestore(&cpts->lock, flags);

	am65_cpts_fअगरo_पढ़ो(cpts);

	am65_cpts_ग_लिखो32(cpts, AM65_CPTS_INT_ENABLE_TS_PEND_EN, पूर्णांक_enable);

	val = cpts->बारtamp;

	वापस val;
पूर्ण

अटल irqवापस_t am65_cpts_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा am65_cpts *cpts = dev_id;

	अगर (am65_cpts_fअगरo_पढ़ो(cpts))
		dev_dbg(cpts->dev, "cpts: unable to obtain a time stamp\n");

	वापस IRQ_HANDLED;
पूर्ण

/* PTP घड़ी operations */
अटल पूर्णांक am65_cpts_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);
	पूर्णांक neg_adj = 0;
	u64 adj_period;
	u32 val;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण

	/* base freq = 1GHz = 1 000 000 000
	 * ppb_norm = ppb * base_freq / घड़ी_freq;
	 * ppm_norm = ppb_norm / 1000
	 * adj_period = 1 000 000 / ppm_norm
	 * adj_period = 1 000 000 000 / ppb_norm
	 * adj_period = 1 000 000 000 / (ppb * base_freq / घड़ी_freq)
	 * adj_period = (1 000 000 000 * घड़ी_freq) / (ppb * base_freq)
	 * adj_period = घड़ी_freq / ppb
	 */
	adj_period = भाग_u64(cpts->refclk_freq, ppb);

	mutex_lock(&cpts->ptp_clk_lock);

	val = am65_cpts_पढ़ो32(cpts, control);
	अगर (neg_adj)
		val |= AM65_CPTS_CONTROL_TS_PPM_सूची;
	अन्यथा
		val &= ~AM65_CPTS_CONTROL_TS_PPM_सूची;
	am65_cpts_ग_लिखो32(cpts, val, control);

	val = upper_32_bits(adj_period) & 0x3FF;
	am65_cpts_ग_लिखो32(cpts, val, ts_ppm_hi);
	val = lower_32_bits(adj_period);
	am65_cpts_ग_लिखो32(cpts, val, ts_ppm_low);

	mutex_unlock(&cpts->ptp_clk_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpts_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);
	s64 ns;

	mutex_lock(&cpts->ptp_clk_lock);
	ns = am65_cpts_समय_लो(cpts, शून्य);
	ns += delta;
	am65_cpts_समय_रखो(cpts, ns);
	mutex_unlock(&cpts->ptp_clk_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpts_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा बारpec64 *ts,
				  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);
	u64 ns;

	mutex_lock(&cpts->ptp_clk_lock);
	ns = am65_cpts_समय_लो(cpts, sts);
	mutex_unlock(&cpts->ptp_clk_lock);
	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

u64 am65_cpts_ns_समय_लो(काष्ठा am65_cpts *cpts)
अणु
	u64 ns;

	/* reuse ptp_clk_lock as it serialize ts push */
	mutex_lock(&cpts->ptp_clk_lock);
	ns = am65_cpts_समय_लो(cpts, शून्य);
	mutex_unlock(&cpts->ptp_clk_lock);

	वापस ns;
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_ns_समय_लो);

अटल पूर्णांक am65_cpts_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
				 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);
	u64 ns;

	ns = बारpec64_to_ns(ts);
	mutex_lock(&cpts->ptp_clk_lock);
	am65_cpts_समय_रखो(cpts, ns);
	mutex_unlock(&cpts->ptp_clk_lock);

	वापस 0;
पूर्ण

अटल व्योम am65_cpts_extts_enable_hw(काष्ठा am65_cpts *cpts, u32 index, पूर्णांक on)
अणु
	u32 v;

	v = am65_cpts_पढ़ो32(cpts, control);
	अगर (on) अणु
		v |= BIT(AM65_CPTS_CONTROL_HW1_TS_PUSH_OFFSET + index);
		cpts->hw_ts_enable |= BIT(index);
	पूर्ण अन्यथा अणु
		v &= ~BIT(AM65_CPTS_CONTROL_HW1_TS_PUSH_OFFSET + index);
		cpts->hw_ts_enable &= ~BIT(index);
	पूर्ण
	am65_cpts_ग_लिखो32(cpts, v, control);
पूर्ण

अटल पूर्णांक am65_cpts_extts_enable(काष्ठा am65_cpts *cpts, u32 index, पूर्णांक on)
अणु
	अगर (!!(cpts->hw_ts_enable & BIT(index)) == !!on)
		वापस 0;

	mutex_lock(&cpts->ptp_clk_lock);
	am65_cpts_extts_enable_hw(cpts, index, on);
	mutex_unlock(&cpts->ptp_clk_lock);

	dev_dbg(cpts->dev, "%s: ExtTS:%u %s\n",
		__func__, index, on ? "enabled" : "disabled");

	वापस 0;
पूर्ण

पूर्णांक am65_cpts_estf_enable(काष्ठा am65_cpts *cpts, पूर्णांक idx,
			  काष्ठा am65_cpts_estf_cfg *cfg)
अणु
	u64 cycles;
	u32 val;

	cycles = cfg->ns_period * cpts->refclk_freq;
	cycles = DIV_ROUND_UP(cycles, NSEC_PER_SEC);
	अगर (cycles > U32_MAX)
		वापस -EINVAL;

	/* according to TRM should be zeroed */
	am65_cpts_ग_लिखो32(cpts, 0, estf[idx].length);

	val = upper_32_bits(cfg->ns_start);
	am65_cpts_ग_लिखो32(cpts, val, estf[idx].comp_hi);
	val = lower_32_bits(cfg->ns_start);
	am65_cpts_ग_लिखो32(cpts, val, estf[idx].comp_lo);
	val = lower_32_bits(cycles);
	am65_cpts_ग_लिखो32(cpts, val, estf[idx].length);

	dev_dbg(cpts->dev, "%s: ESTF:%u enabled\n", __func__, idx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_estf_enable);

व्योम am65_cpts_estf_disable(काष्ठा am65_cpts *cpts, पूर्णांक idx)
अणु
	am65_cpts_ग_लिखो32(cpts, 0, estf[idx].length);

	dev_dbg(cpts->dev, "%s: ESTF:%u disabled\n", __func__, idx);
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_estf_disable);

अटल व्योम am65_cpts_perout_enable_hw(काष्ठा am65_cpts *cpts,
				       काष्ठा ptp_perout_request *req, पूर्णांक on)
अणु
	u64 ns_period, ns_start, cycles;
	काष्ठा बारpec64 ts;
	u32 val;

	अगर (on) अणु
		ts.tv_sec = req->period.sec;
		ts.tv_nsec = req->period.nsec;
		ns_period = बारpec64_to_ns(&ts);

		cycles = (ns_period * cpts->refclk_freq) / NSEC_PER_SEC;

		ts.tv_sec = req->start.sec;
		ts.tv_nsec = req->start.nsec;
		ns_start = बारpec64_to_ns(&ts);

		val = upper_32_bits(ns_start);
		am65_cpts_ग_लिखो32(cpts, val, genf[req->index].comp_hi);
		val = lower_32_bits(ns_start);
		am65_cpts_ग_लिखो32(cpts, val, genf[req->index].comp_lo);
		val = lower_32_bits(cycles);
		am65_cpts_ग_लिखो32(cpts, val, genf[req->index].length);

		cpts->genf_enable |= BIT(req->index);
	पूर्ण अन्यथा अणु
		am65_cpts_ग_लिखो32(cpts, 0, genf[req->index].length);

		cpts->genf_enable &= ~BIT(req->index);
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpts_perout_enable(काष्ठा am65_cpts *cpts,
				   काष्ठा ptp_perout_request *req, पूर्णांक on)
अणु
	अगर (!!(cpts->genf_enable & BIT(req->index)) == !!on)
		वापस 0;

	mutex_lock(&cpts->ptp_clk_lock);
	am65_cpts_perout_enable_hw(cpts, req, on);
	mutex_unlock(&cpts->ptp_clk_lock);

	dev_dbg(cpts->dev, "%s: GenF:%u %s\n",
		__func__, req->index, on ? "enabled" : "disabled");

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpts_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस am65_cpts_extts_enable(cpts, rq->extts.index, on);
	हाल PTP_CLK_REQ_PEROUT:
		वापस am65_cpts_perout_enable(cpts, &rq->perout, on);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल दीर्घ am65_cpts_ts_work(काष्ठा ptp_घड़ी_info *ptp);

अटल काष्ठा ptp_घड़ी_info am65_ptp_info = अणु
	.owner		= THIS_MODULE,
	.name		= "CTPS timer",
	.adjfreq	= am65_cpts_ptp_adjfreq,
	.adjसमय	= am65_cpts_ptp_adjसमय,
	.समय_लोx64	= am65_cpts_ptp_समय_लोx,
	.समय_रखो64	= am65_cpts_ptp_समय_रखो,
	.enable		= am65_cpts_ptp_enable,
	.करो_aux_work	= am65_cpts_ts_work,
पूर्ण;

अटल bool am65_cpts_match_tx_ts(काष्ठा am65_cpts *cpts,
				  काष्ठा am65_cpts_event *event)
अणु
	काष्ठा sk_buff_head txq_list;
	काष्ठा sk_buff *skb, *पंचांगp;
	अचिन्हित दीर्घ flags;
	bool found = false;
	u32 mtype_seqid;

	mtype_seqid = event->event1 &
		      (AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK |
		       AM65_CPTS_EVENT_1_EVENT_TYPE_MASK |
		       AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK);

	__skb_queue_head_init(&txq_list);

	spin_lock_irqsave(&cpts->txq.lock, flags);
	skb_queue_splice_init(&cpts->txq, &txq_list);
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	/* no need to grab txq.lock as access is always करोne under cpts->lock */
	skb_queue_walk_safe(&txq_list, skb, पंचांगp) अणु
		काष्ठा skb_shared_hwtstamps ssh;
		काष्ठा am65_cpts_skb_cb_data *skb_cb =
					(काष्ठा am65_cpts_skb_cb_data *)skb->cb;

		अगर (mtype_seqid == skb_cb->skb_mtype_seqid) अणु
			u64 ns = event->बारtamp;

			स_रखो(&ssh, 0, माप(ssh));
			ssh.hwtstamp = ns_to_kसमय(ns);
			skb_tstamp_tx(skb, &ssh);
			found = true;
			__skb_unlink(skb, &txq_list);
			dev_consume_skb_any(skb);
			dev_dbg(cpts->dev,
				"match tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, skb_cb->पंचांगo)) अणु
			/* समयout any expired skbs over 100 ms */
			dev_dbg(cpts->dev,
				"expiring tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			__skb_unlink(skb, &txq_list);
			dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&cpts->txq.lock, flags);
	skb_queue_splice(&txq_list, &cpts->txq);
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	वापस found;
पूर्ण

अटल व्योम am65_cpts_find_ts(काष्ठा am65_cpts *cpts)
अणु
	काष्ठा am65_cpts_event *event;
	काष्ठा list_head *this, *next;
	LIST_HEAD(events_मुक्त);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(events);

	spin_lock_irqsave(&cpts->lock, flags);
	list_splice_init(&cpts->events, &events);
	spin_unlock_irqrestore(&cpts->lock, flags);

	list_क्रम_each_safe(this, next, &events) अणु
		event = list_entry(this, काष्ठा am65_cpts_event, list);
		अगर (am65_cpts_match_tx_ts(cpts, event) ||
		    समय_after(jअगरfies, event->पंचांगo)) अणु
			list_del_init(&event->list);
			list_add(&event->list, &events_मुक्त);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&cpts->lock, flags);
	list_splice_tail(&events, &cpts->events);
	list_splice_tail(&events_मुक्त, &cpts->pool);
	spin_unlock_irqrestore(&cpts->lock, flags);
पूर्ण

अटल दीर्घ am65_cpts_ts_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा am65_cpts *cpts = container_of(ptp, काष्ठा am65_cpts, ptp_info);
	अचिन्हित दीर्घ flags;
	दीर्घ delay = -1;

	am65_cpts_find_ts(cpts);

	spin_lock_irqsave(&cpts->txq.lock, flags);
	अगर (!skb_queue_empty(&cpts->txq))
		delay = AM65_CPTS_SKB_TX_WORK_TIMEOUT;
	spin_unlock_irqrestore(&cpts->txq.lock, flags);

	वापस delay;
पूर्ण

/**
 * am65_cpts_rx_enable - enable rx बारtamping
 * @cpts: cpts handle
 * @en: enable
 *
 * This functions enables rx packets बारtamping. The CPTS can बारtamp all
 * rx packets.
 */
व्योम am65_cpts_rx_enable(काष्ठा am65_cpts *cpts, bool en)
अणु
	u32 val;

	mutex_lock(&cpts->ptp_clk_lock);
	val = am65_cpts_पढ़ो32(cpts, control);
	अगर (en)
		val |= AM65_CPTS_CONTROL_TSTAMP_EN;
	अन्यथा
		val &= ~AM65_CPTS_CONTROL_TSTAMP_EN;
	am65_cpts_ग_लिखो32(cpts, val, control);
	mutex_unlock(&cpts->ptp_clk_lock);
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_rx_enable);

अटल पूर्णांक am65_skb_get_mtype_seqid(काष्ठा sk_buff *skb, u32 *mtype_seqid)
अणु
	अचिन्हित पूर्णांक ptp_class = ptp_classअगरy_raw(skb);
	काष्ठा ptp_header *hdr;
	u8 msgtype;
	u16 seqid;

	अगर (ptp_class == PTP_CLASS_NONE)
		वापस 0;

	hdr = ptp_parse_header(skb, ptp_class);
	अगर (!hdr)
		वापस 0;

	msgtype = ptp_get_msgtype(hdr, ptp_class);
	seqid	= ntohs(hdr->sequence_id);

	*mtype_seqid  = (msgtype << AM65_CPTS_EVENT_1_MESSAGE_TYPE_SHIFT) &
			AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK;
	*mtype_seqid |= (seqid & AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK);

	वापस 1;
पूर्ण

/**
 * am65_cpts_tx_बारtamp - save tx packet क्रम बारtamping
 * @cpts: cpts handle
 * @skb: packet
 *
 * This functions saves tx packet क्रम बारtamping अगर packet can be बारtamped.
 * The future processing is करोne in from PTP auxiliary worker.
 */
व्योम am65_cpts_tx_बारtamp(काष्ठा am65_cpts *cpts, काष्ठा sk_buff *skb)
अणु
	काष्ठा am65_cpts_skb_cb_data *skb_cb = (व्योम *)skb->cb;

	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS))
		वापस;

	/* add frame to queue क्रम processing later.
	 * The periodic FIFO check will handle this.
	 */
	skb_get(skb);
	/* get the बारtamp क्रम समयouts */
	skb_cb->पंचांगo = jअगरfies + msecs_to_jअगरfies(100);
	skb_queue_tail(&cpts->txq, skb);
	ptp_schedule_worker(cpts->ptp_घड़ी, 0);
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_tx_बारtamp);

/**
 * am65_cpts_prep_tx_बारtamp - check and prepare tx packet क्रम बारtamping
 * @cpts: cpts handle
 * @skb: packet
 *
 * This functions should be called from .xmit().
 * It checks अगर packet can be बारtamped, fills पूर्णांकernal cpts data
 * in skb-cb and marks packet as SKBTX_IN_PROGRESS.
 */
व्योम am65_cpts_prep_tx_बारtamp(काष्ठा am65_cpts *cpts, काष्ठा sk_buff *skb)
अणु
	काष्ठा am65_cpts_skb_cb_data *skb_cb = (व्योम *)skb->cb;
	पूर्णांक ret;

	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		वापस;

	ret = am65_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	अगर (!ret)
		वापस;
	skb_cb->skb_mtype_seqid |= (AM65_CPTS_EV_TX <<
				   AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT);

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_prep_tx_बारtamp);

पूर्णांक am65_cpts_phc_index(काष्ठा am65_cpts *cpts)
अणु
	वापस cpts->phc_index;
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_phc_index);

अटल व्योम cpts_मुक्त_clk_mux(व्योम *data)
अणु
	काष्ठा am65_cpts *cpts = data;

	of_clk_del_provider(cpts->clk_mux_np);
	clk_hw_unरेजिस्टर_mux(cpts->clk_mux_hw);
	of_node_put(cpts->clk_mux_np);
पूर्ण

अटल पूर्णांक cpts_of_mux_clk_setup(काष्ठा am65_cpts *cpts,
				 काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर **parent_names;
	अक्षर *clk_mux_name;
	व्योम __iomem *reg;
	पूर्णांक ret = -EINVAL;

	cpts->clk_mux_np = of_get_child_by_name(node, "refclk-mux");
	अगर (!cpts->clk_mux_np)
		वापस 0;

	num_parents = of_clk_get_parent_count(cpts->clk_mux_np);
	अगर (num_parents < 1) अणु
		dev_err(cpts->dev, "mux-clock %pOF must have parents\n",
			cpts->clk_mux_np);
		जाओ mux_fail;
	पूर्ण

	parent_names = devm_kसुस्मृति(cpts->dev, माप(अक्षर *), num_parents,
				    GFP_KERNEL);
	अगर (!parent_names) अणु
		ret = -ENOMEM;
		जाओ mux_fail;
	पूर्ण

	of_clk_parent_fill(cpts->clk_mux_np, parent_names, num_parents);

	clk_mux_name = devm_kaप्र_लिखो(cpts->dev, GFP_KERNEL, "%s.%pOFn",
				      dev_name(cpts->dev), cpts->clk_mux_np);
	अगर (!clk_mux_name) अणु
		ret = -ENOMEM;
		जाओ mux_fail;
	पूर्ण

	reg = &cpts->reg->rftclk_sel;
	/* dev must be शून्य to aव्योम recursive incrementing
	 * of module refcnt
	 */
	cpts->clk_mux_hw = clk_hw_रेजिस्टर_mux(शून्य, clk_mux_name,
					       parent_names, num_parents,
					       0, reg, 0, 5, 0, शून्य);
	अगर (IS_ERR(cpts->clk_mux_hw)) अणु
		ret = PTR_ERR(cpts->clk_mux_hw);
		जाओ mux_fail;
	पूर्ण

	ret = of_clk_add_hw_provider(cpts->clk_mux_np, of_clk_hw_simple_get,
				     cpts->clk_mux_hw);
	अगर (ret)
		जाओ clk_hw_रेजिस्टर;

	ret = devm_add_action_or_reset(cpts->dev, cpts_मुक्त_clk_mux, cpts);
	अगर (ret)
		dev_err(cpts->dev, "failed to add clkmux reset action %d", ret);

	वापस ret;

clk_hw_रेजिस्टर:
	clk_hw_unरेजिस्टर_mux(cpts->clk_mux_hw);
mux_fail:
	of_node_put(cpts->clk_mux_np);
	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpts_of_parse(काष्ठा am65_cpts *cpts, काष्ठा device_node *node)
अणु
	u32 prop[2];

	अगर (!of_property_पढ़ो_u32(node, "ti,cpts-ext-ts-inputs", &prop[0]))
		cpts->ext_ts_inमाला_दो = prop[0];

	अगर (!of_property_पढ़ो_u32(node, "ti,cpts-periodic-outputs", &prop[0]))
		cpts->genf_num = prop[0];

	वापस cpts_of_mux_clk_setup(cpts, node);
पूर्ण

अटल व्योम am65_cpts_release(व्योम *data)
अणु
	काष्ठा am65_cpts *cpts = data;

	ptp_घड़ी_unरेजिस्टर(cpts->ptp_घड़ी);
	am65_cpts_disable(cpts);
	clk_disable_unprepare(cpts->refclk);
पूर्ण

काष्ठा am65_cpts *am65_cpts_create(काष्ठा device *dev, व्योम __iomem *regs,
				   काष्ठा device_node *node)
अणु
	काष्ठा am65_cpts *cpts;
	पूर्णांक ret, i;

	cpts = devm_kzalloc(dev, माप(*cpts), GFP_KERNEL);
	अगर (!cpts)
		वापस ERR_PTR(-ENOMEM);

	cpts->dev = dev;
	cpts->reg = (काष्ठा am65_cpts_regs __iomem *)regs;

	cpts->irq = of_irq_get_byname(node, "cpts");
	अगर (cpts->irq <= 0) अणु
		ret = cpts->irq ?: -ENXIO;
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get IRQ number (err = %d)\n",
				ret);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = am65_cpts_of_parse(cpts, node);
	अगर (ret)
		वापस ERR_PTR(ret);

	mutex_init(&cpts->ptp_clk_lock);
	INIT_LIST_HEAD(&cpts->events);
	INIT_LIST_HEAD(&cpts->pool);
	spin_lock_init(&cpts->lock);
	skb_queue_head_init(&cpts->txq);

	क्रम (i = 0; i < AM65_CPTS_MAX_EVENTS; i++)
		list_add(&cpts->pool_data[i].list, &cpts->pool);

	cpts->refclk = devm_get_clk_from_child(dev, node, "cpts");
	अगर (IS_ERR(cpts->refclk)) अणु
		ret = PTR_ERR(cpts->refclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get refclk %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = clk_prepare_enable(cpts->refclk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable refclk %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	cpts->refclk_freq = clk_get_rate(cpts->refclk);

	am65_ptp_info.max_adj = cpts->refclk_freq / AM65_CPTS_MIN_PPM;
	cpts->ptp_info = am65_ptp_info;

	अगर (cpts->ext_ts_inमाला_दो)
		cpts->ptp_info.n_ext_ts = cpts->ext_ts_inमाला_दो;
	अगर (cpts->genf_num)
		cpts->ptp_info.n_per_out = cpts->genf_num;

	am65_cpts_set_add_val(cpts);

	am65_cpts_ग_लिखो32(cpts, AM65_CPTS_CONTROL_EN |
			  AM65_CPTS_CONTROL_64MODE |
			  AM65_CPTS_CONTROL_TX_GENF_CLR_EN,
			  control);
	am65_cpts_ग_लिखो32(cpts, AM65_CPTS_INT_ENABLE_TS_PEND_EN, पूर्णांक_enable);

	/* set समय to the current प्रणाली समय */
	am65_cpts_समय_रखो(cpts, kसमय_प्रकारo_ns(kसमय_get_real()));

	cpts->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&cpts->ptp_info, cpts->dev);
	अगर (IS_ERR_OR_शून्य(cpts->ptp_घड़ी)) अणु
		dev_err(dev, "Failed to register ptp clk %ld\n",
			PTR_ERR(cpts->ptp_घड़ी));
		ret = cpts->ptp_घड़ी ? PTR_ERR(cpts->ptp_घड़ी) : -ENODEV;
		जाओ refclk_disable;
	पूर्ण
	cpts->phc_index = ptp_घड़ी_index(cpts->ptp_घड़ी);

	ret = devm_add_action_or_reset(dev, am65_cpts_release, cpts);
	अगर (ret) अणु
		dev_err(dev, "failed to add ptpclk reset action %d", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, cpts->irq, शून्य,
					am65_cpts_पूर्णांकerrupt,
					IRQF_ONESHOT, dev_name(dev), cpts);
	अगर (ret < 0) अणु
		dev_err(cpts->dev, "error attaching irq %d\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	dev_info(dev, "CPTS ver 0x%08x, freq:%u, add_val:%u\n",
		 am65_cpts_पढ़ो32(cpts, idver),
		 cpts->refclk_freq, cpts->ts_add_val);

	वापस cpts;

refclk_disable:
	clk_disable_unprepare(cpts->refclk);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(am65_cpts_create);

अटल पूर्णांक am65_cpts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा am65_cpts *cpts;
	काष्ठा resource *res;
	व्योम __iomem *base;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cpts");
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	cpts = am65_cpts_create(dev, base, node);
	वापस PTR_ERR_OR_ZERO(cpts);
पूर्ण

अटल स्थिर काष्ठा of_device_id am65_cpts_of_match[] = अणु
	अणु .compatible = "ti,am65-cpts", पूर्ण,
	अणु .compatible = "ti,j721e-cpts", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, am65_cpts_of_match);

अटल काष्ठा platक्रमm_driver am65_cpts_driver = अणु
	.probe		= am65_cpts_probe,
	.driver		= अणु
		.name	= "am65-cpts",
		.of_match_table = am65_cpts_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(am65_cpts_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Grygorii Strashko <grygorii.strashko@ti.com>");
MODULE_DESCRIPTION("TI K3 AM65 CPTS driver");
