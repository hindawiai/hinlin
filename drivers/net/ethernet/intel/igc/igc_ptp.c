<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2019 Intel Corporation */

#समावेश "igc.h"

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kसमय.स>

#घोषणा INCVALUE_MASK		0x7fffffff
#घोषणा ISGN			0x80000000

#घोषणा IGC_SYSTIM_OVERFLOW_PERIOD	(HZ * 60 * 9)
#घोषणा IGC_PTP_TX_TIMEOUT		(HZ * 15)

/* SYSTIM पढ़ो access क्रम I225 */
व्योम igc_ptp_पढ़ो(काष्ठा igc_adapter *adapter, काष्ठा बारpec64 *ts)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 sec, nsec;

	/* The बारtamp is latched when SYSTIML is पढ़ो. */
	nsec = rd32(IGC_SYSTIML);
	sec = rd32(IGC_SYSTIMH);

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
पूर्ण

अटल व्योम igc_ptp_ग_लिखो_i225(काष्ठा igc_adapter *adapter,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	wr32(IGC_SYSTIML, ts->tv_nsec);
	wr32(IGC_SYSTIMH, ts->tv_sec);
पूर्ण

अटल पूर्णांक igc_ptp_adjfine_i225(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा igc_adapter *igc = container_of(ptp, काष्ठा igc_adapter,
					       ptp_caps);
	काष्ठा igc_hw *hw = &igc->hw;
	पूर्णांक neg_adj = 0;
	u64 rate;
	u32 inca;

	अगर (scaled_ppm < 0) अणु
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण
	rate = scaled_ppm;
	rate <<= 14;
	rate = भाग_u64(rate, 78125);

	inca = rate & INCVALUE_MASK;
	अगर (neg_adj)
		inca |= ISGN;

	wr32(IGC_TIMINCA, inca);

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ptp_adjसमय_i225(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा igc_adapter *igc = container_of(ptp, काष्ठा igc_adapter,
					       ptp_caps);
	काष्ठा बारpec64 now, then = ns_to_बारpec64(delta);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igc->पंचांगreg_lock, flags);

	igc_ptp_पढ़ो(igc, &now);
	now = बारpec64_add(now, then);
	igc_ptp_ग_लिखो_i225(igc, (स्थिर काष्ठा बारpec64 *)&now);

	spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ptp_समय_लोx64_i225(काष्ठा ptp_घड़ी_info *ptp,
				   काष्ठा बारpec64 *ts,
				   काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा igc_adapter *igc = container_of(ptp, काष्ठा igc_adapter,
					       ptp_caps);
	काष्ठा igc_hw *hw = &igc->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igc->पंचांगreg_lock, flags);

	ptp_पढ़ो_प्रणाली_prets(sts);
	ts->tv_nsec = rd32(IGC_SYSTIML);
	ts->tv_sec = rd32(IGC_SYSTIMH);
	ptp_पढ़ो_प्रणाली_postts(sts);

	spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ptp_समय_रखो_i225(काष्ठा ptp_घड़ी_info *ptp,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा igc_adapter *igc = container_of(ptp, काष्ठा igc_adapter,
					       ptp_caps);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igc->पंचांगreg_lock, flags);

	igc_ptp_ग_लिखो_i225(igc, ts);

	spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम igc_pin_direction(पूर्णांक pin, पूर्णांक input, u32 *ctrl, u32 *ctrl_ext)
अणु
	u32 *ptr = pin < 2 ? ctrl : ctrl_ext;
	अटल स्थिर u32 mask[IGC_N_SDP] = अणु
		IGC_CTRL_SDP0_सूची,
		IGC_CTRL_SDP1_सूची,
		IGC_CTRL_EXT_SDP2_सूची,
		IGC_CTRL_EXT_SDP3_सूची,
	पूर्ण;

	अगर (input)
		*ptr &= ~mask[pin];
	अन्यथा
		*ptr |= mask[pin];
पूर्ण

अटल व्योम igc_pin_perout(काष्ठा igc_adapter *igc, पूर्णांक chan, पूर्णांक pin, पूर्णांक freq)
अणु
	अटल स्थिर u32 igc_aux0_sel_sdp[IGC_N_SDP] = अणु
		IGC_AUX0_SEL_SDP0, IGC_AUX0_SEL_SDP1, IGC_AUX0_SEL_SDP2, IGC_AUX0_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 igc_aux1_sel_sdp[IGC_N_SDP] = अणु
		IGC_AUX1_SEL_SDP0, IGC_AUX1_SEL_SDP1, IGC_AUX1_SEL_SDP2, IGC_AUX1_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_en[IGC_N_SDP] = अणु
		IGC_TS_SDP0_EN, IGC_TS_SDP1_EN, IGC_TS_SDP2_EN, IGC_TS_SDP3_EN,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_sel_tt0[IGC_N_SDP] = अणु
		IGC_TS_SDP0_SEL_TT0, IGC_TS_SDP1_SEL_TT0,
		IGC_TS_SDP2_SEL_TT0, IGC_TS_SDP3_SEL_TT0,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_sel_tt1[IGC_N_SDP] = अणु
		IGC_TS_SDP0_SEL_TT1, IGC_TS_SDP1_SEL_TT1,
		IGC_TS_SDP2_SEL_TT1, IGC_TS_SDP3_SEL_TT1,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_sel_fc0[IGC_N_SDP] = अणु
		IGC_TS_SDP0_SEL_FC0, IGC_TS_SDP1_SEL_FC0,
		IGC_TS_SDP2_SEL_FC0, IGC_TS_SDP3_SEL_FC0,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_sel_fc1[IGC_N_SDP] = अणु
		IGC_TS_SDP0_SEL_FC1, IGC_TS_SDP1_SEL_FC1,
		IGC_TS_SDP2_SEL_FC1, IGC_TS_SDP3_SEL_FC1,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_sel_clr[IGC_N_SDP] = अणु
		IGC_TS_SDP0_SEL_FC1, IGC_TS_SDP1_SEL_FC1,
		IGC_TS_SDP2_SEL_FC1, IGC_TS_SDP3_SEL_FC1,
	पूर्ण;
	काष्ठा igc_hw *hw = &igc->hw;
	u32 ctrl, ctrl_ext, tssdp = 0;

	ctrl = rd32(IGC_CTRL);
	ctrl_ext = rd32(IGC_CTRL_EXT);
	tssdp = rd32(IGC_TSSDP);

	igc_pin_direction(pin, 0, &ctrl, &ctrl_ext);

	/* Make sure this pin is not enabled as an input. */
	अगर ((tssdp & IGC_AUX0_SEL_SDP3) == igc_aux0_sel_sdp[pin])
		tssdp &= ~IGC_AUX0_TS_SDP_EN;

	अगर ((tssdp & IGC_AUX1_SEL_SDP3) == igc_aux1_sel_sdp[pin])
		tssdp &= ~IGC_AUX1_TS_SDP_EN;

	tssdp &= ~igc_ts_sdp_sel_clr[pin];
	अगर (freq) अणु
		अगर (chan == 1)
			tssdp |= igc_ts_sdp_sel_fc1[pin];
		अन्यथा
			tssdp |= igc_ts_sdp_sel_fc0[pin];
	पूर्ण अन्यथा अणु
		अगर (chan == 1)
			tssdp |= igc_ts_sdp_sel_tt1[pin];
		अन्यथा
			tssdp |= igc_ts_sdp_sel_tt0[pin];
	पूर्ण
	tssdp |= igc_ts_sdp_en[pin];

	wr32(IGC_TSSDP, tssdp);
	wr32(IGC_CTRL, ctrl);
	wr32(IGC_CTRL_EXT, ctrl_ext);
पूर्ण

अटल व्योम igc_pin_extts(काष्ठा igc_adapter *igc, पूर्णांक chan, पूर्णांक pin)
अणु
	अटल स्थिर u32 igc_aux0_sel_sdp[IGC_N_SDP] = अणु
		IGC_AUX0_SEL_SDP0, IGC_AUX0_SEL_SDP1, IGC_AUX0_SEL_SDP2, IGC_AUX0_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 igc_aux1_sel_sdp[IGC_N_SDP] = अणु
		IGC_AUX1_SEL_SDP0, IGC_AUX1_SEL_SDP1, IGC_AUX1_SEL_SDP2, IGC_AUX1_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 igc_ts_sdp_en[IGC_N_SDP] = अणु
		IGC_TS_SDP0_EN, IGC_TS_SDP1_EN, IGC_TS_SDP2_EN, IGC_TS_SDP3_EN,
	पूर्ण;
	काष्ठा igc_hw *hw = &igc->hw;
	u32 ctrl, ctrl_ext, tssdp = 0;

	ctrl = rd32(IGC_CTRL);
	ctrl_ext = rd32(IGC_CTRL_EXT);
	tssdp = rd32(IGC_TSSDP);

	igc_pin_direction(pin, 1, &ctrl, &ctrl_ext);

	/* Make sure this pin is not enabled as an output. */
	tssdp &= ~igc_ts_sdp_en[pin];

	अगर (chan == 1) अणु
		tssdp &= ~IGC_AUX1_SEL_SDP3;
		tssdp |= igc_aux1_sel_sdp[pin] | IGC_AUX1_TS_SDP_EN;
	पूर्ण अन्यथा अणु
		tssdp &= ~IGC_AUX0_SEL_SDP3;
		tssdp |= igc_aux0_sel_sdp[pin] | IGC_AUX0_TS_SDP_EN;
	पूर्ण

	wr32(IGC_TSSDP, tssdp);
	wr32(IGC_CTRL, ctrl);
	wr32(IGC_CTRL_EXT, ctrl_ext);
पूर्ण

अटल पूर्णांक igc_ptp_feature_enable_i225(काष्ठा ptp_घड़ी_info *ptp,
				       काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा igc_adapter *igc =
		container_of(ptp, काष्ठा igc_adapter, ptp_caps);
	काष्ठा igc_hw *hw = &igc->hw;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 ts;
	पूर्णांक use_freq = 0, pin = -1;
	u32 tsim, tsauxc, tsauxc_mask, tsim_mask, trgttiml, trgttimh, freqout;
	s64 ns;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		/* Reject requests with unsupported flags */
		अगर (rq->extts.flags & ~(PTP_ENABLE_FEATURE |
					PTP_RISING_EDGE |
					PTP_FALLING_EDGE |
					PTP_STRICT_FLAGS))
			वापस -EOPNOTSUPP;

		/* Reject requests failing to enable both edges. */
		अगर ((rq->extts.flags & PTP_STRICT_FLAGS) &&
		    (rq->extts.flags & PTP_ENABLE_FEATURE) &&
		    (rq->extts.flags & PTP_EXTTS_EDGES) != PTP_EXTTS_EDGES)
			वापस -EOPNOTSUPP;

		अगर (on) अणु
			pin = ptp_find_pin(igc->ptp_घड़ी, PTP_PF_EXTTS,
					   rq->extts.index);
			अगर (pin < 0)
				वापस -EBUSY;
		पूर्ण
		अगर (rq->extts.index == 1) अणु
			tsauxc_mask = IGC_TSAUXC_EN_TS1;
			tsim_mask = IGC_TSICR_AUTT1;
		पूर्ण अन्यथा अणु
			tsauxc_mask = IGC_TSAUXC_EN_TS0;
			tsim_mask = IGC_TSICR_AUTT0;
		पूर्ण
		spin_lock_irqsave(&igc->पंचांगreg_lock, flags);
		tsauxc = rd32(IGC_TSAUXC);
		tsim = rd32(IGC_TSIM);
		अगर (on) अणु
			igc_pin_extts(igc, rq->extts.index, pin);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		पूर्ण अन्यथा अणु
			tsauxc &= ~tsauxc_mask;
			tsim &= ~tsim_mask;
		पूर्ण
		wr32(IGC_TSAUXC, tsauxc);
		wr32(IGC_TSIM, tsim);
		spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);
		वापस 0;

	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags)
			वापस -EOPNOTSUPP;

		अगर (on) अणु
			pin = ptp_find_pin(igc->ptp_घड़ी, PTP_PF_PEROUT,
					   rq->perout.index);
			अगर (pin < 0)
				वापस -EBUSY;
		पूर्ण
		ts.tv_sec = rq->perout.period.sec;
		ts.tv_nsec = rq->perout.period.nsec;
		ns = बारpec64_to_ns(&ts);
		ns = ns >> 1;
		अगर (on && (ns <= 70000000LL || ns == 125000000LL ||
			   ns == 250000000LL || ns == 500000000LL)) अणु
			अगर (ns < 8LL)
				वापस -EINVAL;
			use_freq = 1;
		पूर्ण
		ts = ns_to_बारpec64(ns);
		अगर (rq->perout.index == 1) अणु
			अगर (use_freq) अणु
				tsauxc_mask = IGC_TSAUXC_EN_CLK1;
				tsim_mask = 0;
			पूर्ण अन्यथा अणु
				tsauxc_mask = IGC_TSAUXC_EN_TT1;
				tsim_mask = IGC_TSICR_TT1;
			पूर्ण
			trgttiml = IGC_TRGTTIML1;
			trgttimh = IGC_TRGTTIMH1;
			freqout = IGC_FREQOUT1;
		पूर्ण अन्यथा अणु
			अगर (use_freq) अणु
				tsauxc_mask = IGC_TSAUXC_EN_CLK0;
				tsim_mask = 0;
			पूर्ण अन्यथा अणु
				tsauxc_mask = IGC_TSAUXC_EN_TT0;
				tsim_mask = IGC_TSICR_TT0;
			पूर्ण
			trgttiml = IGC_TRGTTIML0;
			trgttimh = IGC_TRGTTIMH0;
			freqout = IGC_FREQOUT0;
		पूर्ण
		spin_lock_irqsave(&igc->पंचांगreg_lock, flags);
		tsauxc = rd32(IGC_TSAUXC);
		tsim = rd32(IGC_TSIM);
		अगर (rq->perout.index == 1) अणु
			tsauxc &= ~(IGC_TSAUXC_EN_TT1 | IGC_TSAUXC_EN_CLK1);
			tsim &= ~IGC_TSICR_TT1;
		पूर्ण अन्यथा अणु
			tsauxc &= ~(IGC_TSAUXC_EN_TT0 | IGC_TSAUXC_EN_CLK0);
			tsim &= ~IGC_TSICR_TT0;
		पूर्ण
		अगर (on) अणु
			पूर्णांक i = rq->perout.index;

			igc_pin_perout(igc, i, pin, use_freq);
			igc->perout[i].start.tv_sec = rq->perout.start.sec;
			igc->perout[i].start.tv_nsec = rq->perout.start.nsec;
			igc->perout[i].period.tv_sec = ts.tv_sec;
			igc->perout[i].period.tv_nsec = ts.tv_nsec;
			wr32(trgttimh, rq->perout.start.sec);
			/* For now, always select समयr 0 as source. */
			wr32(trgttiml, rq->perout.start.nsec | IGC_TT_IO_TIMER_SEL_SYSTIM0);
			अगर (use_freq)
				wr32(freqout, ns);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		पूर्ण
		wr32(IGC_TSAUXC, tsauxc);
		wr32(IGC_TSIM, tsim);
		spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);
		वापस 0;

	हाल PTP_CLK_REQ_PPS:
		spin_lock_irqsave(&igc->पंचांगreg_lock, flags);
		tsim = rd32(IGC_TSIM);
		अगर (on)
			tsim |= IGC_TSICR_SYS_WRAP;
		अन्यथा
			tsim &= ~IGC_TSICR_SYS_WRAP;
		igc->pps_sys_wrap_on = on;
		wr32(IGC_TSIM, tsim);
		spin_unlock_irqrestore(&igc->पंचांगreg_lock, flags);
		वापस 0;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक igc_ptp_verअगरy_pin(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
			      क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	चयन (func) अणु
	हाल PTP_PF_NONE:
	हाल PTP_PF_EXTTS:
	हाल PTP_PF_PEROUT:
		अवरोध;
	हाल PTP_PF_PHYSYNC:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * igc_ptp_systim_to_hwtstamp - convert प्रणाली समय value to HW बारtamp
 * @adapter: board निजी काष्ठाure
 * @hwtstamps: बारtamp काष्ठाure to update
 * @systim: अचिन्हित 64bit प्रणाली समय value
 *
 * We need to convert the प्रणाली समय value stored in the RX/TXSTMP रेजिस्टरs
 * पूर्णांकo a hwtstamp which can be used by the upper level बारtamping functions.
 **/
अटल व्योम igc_ptp_systim_to_hwtstamp(काष्ठा igc_adapter *adapter,
				       काष्ठा skb_shared_hwtstamps *hwtstamps,
				       u64 systim)
अणु
	चयन (adapter->hw.mac.type) अणु
	हाल igc_i225:
		स_रखो(hwtstamps, 0, माप(*hwtstamps));
		/* Upper 32 bits contain s, lower 32 bits contain ns. */
		hwtstamps->hwtstamp = kसमय_set(systim >> 32,
						systim & 0xFFFFFFFF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * igc_ptp_rx_pktstamp - Retrieve बारtamp from Rx packet buffer
 * @adapter: Poपूर्णांकer to adapter the packet buffer beदीर्घs to
 * @buf: Poपूर्णांकer to packet buffer
 *
 * This function retrieves the बारtamp saved in the beginning of packet
 * buffer. While two बारtamps are available, one in समयr0 reference and the
 * other in समयr1 reference, this function considers only the बारtamp in
 * समयr0 reference.
 *
 * Returns बारtamp value.
 */
kसमय_प्रकार igc_ptp_rx_pktstamp(काष्ठा igc_adapter *adapter, __le32 *buf)
अणु
	kसमय_प्रकार बारtamp;
	u32 secs, nsecs;
	पूर्णांक adjust;

	/* Timestamps are saved in little endian at the beginning of the packet
	 * buffer following the layout:
	 *
	 * DWORD: | 0              | 1              | 2              | 3              |
	 * Field: | Timer1 SYSTIML | Timer1 SYSTIMH | Timer0 SYSTIML | Timer0 SYSTIMH |
	 *
	 * SYSTIML holds the nanoseconds part जबतक SYSTIMH holds the seconds
	 * part of the बारtamp.
	 */
	nsecs = le32_to_cpu(buf[2]);
	secs = le32_to_cpu(buf[3]);

	बारtamp = kसमय_set(secs, nsecs);

	/* Adjust बारtamp क्रम the RX latency based on link speed */
	चयन (adapter->link_speed) अणु
	हाल SPEED_10:
		adjust = IGC_I225_RX_LATENCY_10;
		अवरोध;
	हाल SPEED_100:
		adjust = IGC_I225_RX_LATENCY_100;
		अवरोध;
	हाल SPEED_1000:
		adjust = IGC_I225_RX_LATENCY_1000;
		अवरोध;
	हाल SPEED_2500:
		adjust = IGC_I225_RX_LATENCY_2500;
		अवरोध;
	शेष:
		adjust = 0;
		netdev_warn_once(adapter->netdev, "Imprecise timestamp\n");
		अवरोध;
	पूर्ण

	वापस kसमय_sub_ns(बारtamp, adjust);
पूर्ण

अटल व्योम igc_ptp_disable_rx_बारtamp(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 val;
	पूर्णांक i;

	wr32(IGC_TSYNCRXCTL, 0);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		val = rd32(IGC_SRRCTL(i));
		val &= ~IGC_SRRCTL_TIMESTAMP;
		wr32(IGC_SRRCTL(i), val);
	पूर्ण

	val = rd32(IGC_RXPBS);
	val &= ~IGC_RXPBS_CFG_TS_EN;
	wr32(IGC_RXPBS, val);
पूर्ण

अटल व्योम igc_ptp_enable_rx_बारtamp(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 val;
	पूर्णांक i;

	val = rd32(IGC_RXPBS);
	val |= IGC_RXPBS_CFG_TS_EN;
	wr32(IGC_RXPBS, val);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		val = rd32(IGC_SRRCTL(i));
		/* FIXME: For now, only support retrieving RX बारtamps from
		 * समयr 0.
		 */
		val |= IGC_SRRCTL_TIMER1SEL(0) | IGC_SRRCTL_TIMER0SEL(0) |
		       IGC_SRRCTL_TIMESTAMP;
		wr32(IGC_SRRCTL(i), val);
	पूर्ण

	val = IGC_TSYNCRXCTL_ENABLED | IGC_TSYNCRXCTL_TYPE_ALL |
	      IGC_TSYNCRXCTL_RXSYNSIG;
	wr32(IGC_TSYNCRXCTL, val);
पूर्ण

अटल व्योम igc_ptp_disable_tx_बारtamp(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	wr32(IGC_TSYNCTXCTL, 0);
पूर्ण

अटल व्योम igc_ptp_enable_tx_बारtamp(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	wr32(IGC_TSYNCTXCTL, IGC_TSYNCTXCTL_ENABLED | IGC_TSYNCTXCTL_TXSYNSIG);

	/* Read TXSTMP रेजिस्टरs to discard any बारtamp previously stored. */
	rd32(IGC_TXSTMPL);
	rd32(IGC_TXSTMPH);
पूर्ण

/**
 * igc_ptp_set_बारtamp_mode - setup hardware क्रम बारtamping
 * @adapter: networking device काष्ठाure
 * @config: hwtstamp configuration
 *
 * Return: 0 in हाल of success, negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक igc_ptp_set_बारtamp_mode(काष्ठा igc_adapter *adapter,
				      काष्ठा hwtstamp_config *config)
अणु
	/* reserved क्रम future extensions */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		igc_ptp_disable_tx_बारtamp(adapter);
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		igc_ptp_enable_tx_बारtamp(adapter);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		igc_ptp_disable_rx_बारtamp(adapter);
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
		igc_ptp_enable_rx_बारtamp(adapter);
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम igc_ptp_tx_समयout(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;

	dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
	adapter->ptp_tx_skb = शून्य;
	adapter->tx_hwtstamp_समयouts++;
	clear_bit_unlock(__IGC_PTP_TX_IN_PROGRESS, &adapter->state);
	/* Clear the tx valid bit in TSYNCTXCTL रेजिस्टर to enable पूर्णांकerrupt. */
	rd32(IGC_TXSTMPH);
	netdev_warn(adapter->netdev, "Tx timestamp timeout\n");
पूर्ण

व्योम igc_ptp_tx_hang(काष्ठा igc_adapter *adapter)
अणु
	bool समयout = समय_is_beक्रमe_jअगरfies(adapter->ptp_tx_start +
					      IGC_PTP_TX_TIMEOUT);

	अगर (!test_bit(__IGC_PTP_TX_IN_PROGRESS, &adapter->state))
		वापस;

	/* If we haven't received a बारtamp within the समयout, it is
	 * reasonable to assume that it will never occur, so we can unlock the
	 * बारtamp bit when this occurs.
	 */
	अगर (समयout) अणु
		cancel_work_sync(&adapter->ptp_tx_work);
		igc_ptp_tx_समयout(adapter);
	पूर्ण
पूर्ण

/**
 * igc_ptp_tx_hwtstamp - utility function which checks क्रम TX समय stamp
 * @adapter: Board निजी काष्ठाure
 *
 * If we were asked to करो hardware stamping and such a समय stamp is
 * available, then it must have been क्रम this skb here because we only
 * allow only one such packet पूर्णांकo the queue.
 */
अटल व्योम igc_ptp_tx_hwtstamp(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा sk_buff *skb = adapter->ptp_tx_skb;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक adjust = 0;
	u64 regval;

	अगर (WARN_ON_ONCE(!skb))
		वापस;

	regval = rd32(IGC_TXSTMPL);
	regval |= (u64)rd32(IGC_TXSTMPH) << 32;
	igc_ptp_systim_to_hwtstamp(adapter, &shhwtstamps, regval);

	चयन (adapter->link_speed) अणु
	हाल SPEED_10:
		adjust = IGC_I225_TX_LATENCY_10;
		अवरोध;
	हाल SPEED_100:
		adjust = IGC_I225_TX_LATENCY_100;
		अवरोध;
	हाल SPEED_1000:
		adjust = IGC_I225_TX_LATENCY_1000;
		अवरोध;
	हाल SPEED_2500:
		adjust = IGC_I225_TX_LATENCY_2500;
		अवरोध;
	पूर्ण

	shhwtstamps.hwtstamp =
		kसमय_add_ns(shhwtstamps.hwtstamp, adjust);

	/* Clear the lock early beक्रमe calling skb_tstamp_tx so that
	 * applications are not woken up beक्रमe the lock bit is clear. We use
	 * a copy of the skb poपूर्णांकer to ensure other thपढ़ोs can't change it
	 * जबतक we're notअगरying the stack.
	 */
	adapter->ptp_tx_skb = शून्य;
	clear_bit_unlock(__IGC_PTP_TX_IN_PROGRESS, &adapter->state);

	/* Notअगरy the stack and मुक्त the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * igc_ptp_tx_work
 * @work: poपूर्णांकer to work काष्ठा
 *
 * This work function polls the TSYNCTXCTL valid bit to determine when a
 * बारtamp has been taken क्रम the current stored skb.
 */
अटल व्योम igc_ptp_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igc_adapter *adapter = container_of(work, काष्ठा igc_adapter,
						   ptp_tx_work);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 tsynctxctl;

	अगर (!test_bit(__IGC_PTP_TX_IN_PROGRESS, &adapter->state))
		वापस;

	tsynctxctl = rd32(IGC_TSYNCTXCTL);
	अगर (WARN_ON_ONCE(!(tsynctxctl & IGC_TSYNCTXCTL_TXTT_0)))
		वापस;

	igc_ptp_tx_hwtstamp(adapter);
पूर्ण

/**
 * igc_ptp_set_ts_config - set hardware समय stamping config
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @अगरr: पूर्णांकerface request data
 *
 **/
पूर्णांक igc_ptp_set_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = igc_ptp_set_बारtamp_mode(adapter, &config);
	अगर (err)
		वापस err;

	/* save these settings क्रम future reference */
	स_नकल(&adapter->tstamp_config, &config,
	       माप(adapter->tstamp_config));

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * igc_ptp_get_ts_config - get hardware समय stamping config
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @अगरr: पूर्णांकerface request data
 *
 * Get the hwtstamp_config settings to वापस to the user. Rather than attempt
 * to deस्थिरruct the settings from the रेजिस्टरs, just वापस a shaकरोw copy
 * of the last known settings.
 **/
पूर्णांक igc_ptp_get_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config *config = &adapter->tstamp_config;

	वापस copy_to_user(अगरr->अगरr_data, config, माप(*config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * igc_ptp_init - Initialize PTP functionality
 * @adapter: Board निजी काष्ठाure
 *
 * This function is called at device probe to initialize the PTP
 * functionality.
 */
व्योम igc_ptp_init(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक i;

	चयन (hw->mac.type) अणु
	हाल igc_i225:
		क्रम (i = 0; i < IGC_N_SDP; i++) अणु
			काष्ठा ptp_pin_desc *ppd = &adapter->sdp_config[i];

			snम_लिखो(ppd->name, माप(ppd->name), "SDP%d", i);
			ppd->index = i;
			ppd->func = PTP_PF_NONE;
		पूर्ण
		snम_लिखो(adapter->ptp_caps.name, 16, "%pm", netdev->dev_addr);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 62499999;
		adapter->ptp_caps.adjfine = igc_ptp_adjfine_i225;
		adapter->ptp_caps.adjसमय = igc_ptp_adjसमय_i225;
		adapter->ptp_caps.समय_लोx64 = igc_ptp_समय_लोx64_i225;
		adapter->ptp_caps.समय_रखो64 = igc_ptp_समय_रखो_i225;
		adapter->ptp_caps.enable = igc_ptp_feature_enable_i225;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.pin_config = adapter->sdp_config;
		adapter->ptp_caps.n_ext_ts = IGC_N_EXTTS;
		adapter->ptp_caps.n_per_out = IGC_N_PEROUT;
		adapter->ptp_caps.n_pins = IGC_N_SDP;
		adapter->ptp_caps.verअगरy = igc_ptp_verअगरy_pin;
		अवरोध;
	शेष:
		adapter->ptp_घड़ी = शून्य;
		वापस;
	पूर्ण

	spin_lock_init(&adapter->पंचांगreg_lock);
	INIT_WORK(&adapter->ptp_tx_work, igc_ptp_tx_work);

	adapter->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	adapter->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	adapter->prev_ptp_समय = kसमय_प्रकारo_बारpec64(kसमय_get_real());
	adapter->ptp_reset_start = kसमय_get();

	adapter->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&adapter->ptp_caps,
						&adapter->pdev->dev);
	अगर (IS_ERR(adapter->ptp_घड़ी)) अणु
		adapter->ptp_घड़ी = शून्य;
		netdev_err(netdev, "ptp_clock_register failed\n");
	पूर्ण अन्यथा अगर (adapter->ptp_घड़ी) अणु
		netdev_info(netdev, "PHC added\n");
		adapter->ptp_flags |= IGC_PTP_ENABLED;
	पूर्ण
पूर्ण

अटल व्योम igc_ptp_समय_save(काष्ठा igc_adapter *adapter)
अणु
	igc_ptp_पढ़ो(adapter, &adapter->prev_ptp_समय);
	adapter->ptp_reset_start = kसमय_get();
पूर्ण

अटल व्योम igc_ptp_समय_restore(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा बारpec64 ts = adapter->prev_ptp_समय;
	kसमय_प्रकार delta;

	delta = kसमय_sub(kसमय_get(), adapter->ptp_reset_start);

	बारpec64_add_ns(&ts, kसमय_प्रकारo_ns(delta));

	igc_ptp_ग_लिखो_i225(adapter, &ts);
पूर्ण

/**
 * igc_ptp_suspend - Disable PTP work items and prepare क्रम suspend
 * @adapter: Board निजी काष्ठाure
 *
 * This function stops the overflow check work and PTP Tx बारtamp work, and
 * will prepare the device क्रम OS suspend.
 */
व्योम igc_ptp_suspend(काष्ठा igc_adapter *adapter)
अणु
	अगर (!(adapter->ptp_flags & IGC_PTP_ENABLED))
		वापस;

	cancel_work_sync(&adapter->ptp_tx_work);
	dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
	adapter->ptp_tx_skb = शून्य;
	clear_bit_unlock(__IGC_PTP_TX_IN_PROGRESS, &adapter->state);

	igc_ptp_समय_save(adapter);
पूर्ण

/**
 * igc_ptp_stop - Disable PTP device and stop the overflow check.
 * @adapter: Board निजी काष्ठाure.
 *
 * This function stops the PTP support and cancels the delayed work.
 **/
व्योम igc_ptp_stop(काष्ठा igc_adapter *adapter)
अणु
	igc_ptp_suspend(adapter);

	अगर (adapter->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		netdev_info(adapter->netdev, "PHC removed\n");
		adapter->ptp_flags &= ~IGC_PTP_ENABLED;
	पूर्ण
पूर्ण

/**
 * igc_ptp_reset - Re-enable the adapter क्रम PTP following a reset.
 * @adapter: Board निजी काष्ठाure.
 *
 * This function handles the reset work required to re-enable the PTP device.
 **/
व्योम igc_ptp_reset(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	/* reset the tstamp_config */
	igc_ptp_set_बारtamp_mode(adapter, &adapter->tstamp_config);

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);

	चयन (adapter->hw.mac.type) अणु
	हाल igc_i225:
		wr32(IGC_TSAUXC, 0x0);
		wr32(IGC_TSSDP, 0x0);
		wr32(IGC_TSIM,
		     IGC_TSICR_INTERRUPTS |
		     (adapter->pps_sys_wrap_on ? IGC_TSICR_SYS_WRAP : 0));
		wr32(IGC_IMS, IGC_IMS_TS);
		अवरोध;
	शेष:
		/* No work to करो. */
		जाओ out;
	पूर्ण

	/* Re-initialize the समयr. */
	अगर (hw->mac.type == igc_i225) अणु
		igc_ptp_समय_restore(adapter);
	पूर्ण अन्यथा अणु
		समयcounter_init(&adapter->tc, &adapter->cc,
				 kसमय_प्रकारo_ns(kसमय_get_real()));
	पूर्ण
out:
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	wrfl();
पूर्ण
