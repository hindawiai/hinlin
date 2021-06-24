<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2011 Riअक्षरd Cochran <riअक्षरdcochran@gmail.com> */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pci.h>
#समावेश <linux/ptp_classअगरy.h>

#समावेश "igb.h"

#घोषणा INCVALUE_MASK		0x7fffffff
#घोषणा ISGN			0x80000000

/* The 82580 बारync updates the प्रणाली समयr every 8ns by 8ns,
 * and this update value cannot be reprogrammed.
 *
 * Neither the 82576 nor the 82580 offer रेजिस्टरs wide enough to hold
 * nanoseconds समय values क्रम very दीर्घ. For the 82580, SYSTIM always
 * counts nanoseconds, but the upper 24 bits are not available. The
 * frequency is adjusted by changing the 32 bit fractional nanoseconds
 * रेजिस्टर, TIMINCA.
 *
 * For the 82576, the SYSTIM रेजिस्टर समय unit is affect by the
 * choice of the 24 bit TININCA:IV (incvalue) field. Five bits of this
 * field are needed to provide the nominal 16 nanosecond period,
 * leaving 19 bits क्रम fractional nanoseconds.
 *
 * We scale the NIC घड़ी cycle by a large factor so that relatively
 * small घड़ी corrections can be added or subtracted at each घड़ी
 * tick. The drawbacks of a large factor are a) that the घड़ी
 * रेजिस्टर overflows more quickly (not such a big deal) and b) that
 * the increment per tick has to fit पूर्णांकo 24 bits.  As a result we
 * need to use a shअगरt of 19 so we can fit a value of 16 पूर्णांकo the
 * TIMINCA रेजिस्टर.
 *
 *
 *             SYSTIMH            SYSTIML
 *        +--------------+   +---+---+------+
 *  82576 |      32      |   | 8 | 5 |  19  |
 *        +--------------+   +---+---+------+
 *         \________ 45 bits _______/  fract
 *
 *        +----------+---+   +--------------+
 *  82580 |    24    | 8 |   |      32      |
 *        +----------+---+   +--------------+
 *          reserved  \______ 40 bits _____/
 *
 *
 * The 45 bit 82576 SYSTIM overflows every
 *   2^45 * 10^-9 / 3600 = 9.77 hours.
 *
 * The 40 bit 82580 SYSTIM overflows every
 *   2^40 * 10^-9 /  60  = 18.3 minutes.
 *
 * SYSTIM is converted to real समय using a समयcounter. As
 * समयcounter_cyc2समय() allows old बारtamps, the समयcounter needs
 * to be updated at least once per half of the SYSTIM पूर्णांकerval.
 * Scheduling of delayed work is not very accurate, and also the NIC
 * घड़ी can be adjusted to run up to 6% faster and the प्रणाली घड़ी
 * up to 10% slower, so we aim क्रम 6 minutes to be sure the actual
 * पूर्णांकerval in the NIC समय is लघुer than 9.16 minutes.
 */

#घोषणा IGB_SYSTIM_OVERFLOW_PERIOD	(HZ * 60 * 6)
#घोषणा IGB_PTP_TX_TIMEOUT		(HZ * 15)
#घोषणा INCPERIOD_82576			BIT(E1000_TIMINCA_16NS_SHIFT)
#घोषणा INCVALUE_82576_MASK		GENMASK(E1000_TIMINCA_16NS_SHIFT - 1, 0)
#घोषणा INCVALUE_82576			(16u << IGB_82576_TSYNC_SHIFT)
#घोषणा IGB_NBITS_82580			40

अटल व्योम igb_ptp_tx_hwtstamp(काष्ठा igb_adapter *adapter);

/* SYSTIM पढ़ो access क्रम the 82576 */
अटल u64 igb_ptp_पढ़ो_82576(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा igb_adapter *igb = container_of(cc, काष्ठा igb_adapter, cc);
	काष्ठा e1000_hw *hw = &igb->hw;
	u64 val;
	u32 lo, hi;

	lo = rd32(E1000_SYSTIML);
	hi = rd32(E1000_SYSTIMH);

	val = ((u64) hi) << 32;
	val |= lo;

	वापस val;
पूर्ण

/* SYSTIM पढ़ो access क्रम the 82580 */
अटल u64 igb_ptp_पढ़ो_82580(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा igb_adapter *igb = container_of(cc, काष्ठा igb_adapter, cc);
	काष्ठा e1000_hw *hw = &igb->hw;
	u32 lo, hi;
	u64 val;

	/* The बारtamp latches on lowest रेजिस्टर पढ़ो. For the 82580
	 * the lowest रेजिस्टर is SYSTIMR instead of SYSTIML.  However we only
	 * need to provide nanosecond resolution, so we just ignore it.
	 */
	rd32(E1000_SYSTIMR);
	lo = rd32(E1000_SYSTIML);
	hi = rd32(E1000_SYSTIMH);

	val = ((u64) hi) << 32;
	val |= lo;

	वापस val;
पूर्ण

/* SYSTIM पढ़ो access क्रम I210/I211 */
अटल व्योम igb_ptp_पढ़ो_i210(काष्ठा igb_adapter *adapter,
			      काष्ठा बारpec64 *ts)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 sec, nsec;

	/* The बारtamp latches on lowest रेजिस्टर पढ़ो. For I210/I211, the
	 * lowest रेजिस्टर is SYSTIMR. Since we only need to provide nanosecond
	 * resolution, we can ignore it.
	 */
	rd32(E1000_SYSTIMR);
	nsec = rd32(E1000_SYSTIML);
	sec = rd32(E1000_SYSTIMH);

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
पूर्ण

अटल व्योम igb_ptp_ग_लिखो_i210(काष्ठा igb_adapter *adapter,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Writing the SYSTIMR रेजिस्टर is not necessary as it only provides
	 * sub-nanosecond resolution.
	 */
	wr32(E1000_SYSTIML, ts->tv_nsec);
	wr32(E1000_SYSTIMH, (u32)ts->tv_sec);
पूर्ण

/**
 * igb_ptp_systim_to_hwtstamp - convert प्रणाली समय value to hw बारtamp
 * @adapter: board निजी काष्ठाure
 * @hwtstamps: बारtamp काष्ठाure to update
 * @systim: अचिन्हित 64bit प्रणाली समय value.
 *
 * We need to convert the प्रणाली समय value stored in the RX/TXSTMP रेजिस्टरs
 * पूर्णांकo a hwtstamp which can be used by the upper level बारtamping functions.
 *
 * The 'tmreg_lock' spinlock is used to protect the consistency of the
 * प्रणाली समय value. This is needed because पढ़ोing the 64 bit समय
 * value involves पढ़ोing two (or three) 32 bit रेजिस्टरs. The first
 * पढ़ो latches the value. Ditto क्रम writing.
 *
 * In addition, here have extended the प्रणाली समय with an overflow
 * counter in software.
 **/
अटल व्योम igb_ptp_systim_to_hwtstamp(काष्ठा igb_adapter *adapter,
				       काष्ठा skb_shared_hwtstamps *hwtstamps,
				       u64 systim)
अणु
	अचिन्हित दीर्घ flags;
	u64 ns;

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_82576:
	हाल e1000_82580:
	हाल e1000_i354:
	हाल e1000_i350:
		spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);

		ns = समयcounter_cyc2समय(&adapter->tc, systim);

		spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

		स_रखो(hwtstamps, 0, माप(*hwtstamps));
		hwtstamps->hwtstamp = ns_to_kसमय(ns);
		अवरोध;
	हाल e1000_i210:
	हाल e1000_i211:
		स_रखो(hwtstamps, 0, माप(*hwtstamps));
		/* Upper 32 bits contain s, lower 32 bits contain ns. */
		hwtstamps->hwtstamp = kसमय_set(systim >> 32,
						systim & 0xFFFFFFFF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* PTP घड़ी operations */
अटल पूर्णांक igb_ptp_adjfreq_82576(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	पूर्णांक neg_adj = 0;
	u64 rate;
	u32 incvalue;

	अगर (ppb < 0) अणु
		neg_adj = 1;
		ppb = -ppb;
	पूर्ण
	rate = ppb;
	rate <<= 14;
	rate = भाग_u64(rate, 1953125);

	incvalue = 16 << IGB_82576_TSYNC_SHIFT;

	अगर (neg_adj)
		incvalue -= rate;
	अन्यथा
		incvalue += rate;

	wr32(E1000_TIMINCA, INCPERIOD_82576 | (incvalue & INCVALUE_82576_MASK));

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_adjfine_82580(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	पूर्णांक neg_adj = 0;
	u64 rate;
	u32 inca;

	अगर (scaled_ppm < 0) अणु
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण
	rate = scaled_ppm;
	rate <<= 13;
	rate = भाग_u64(rate, 15625);

	inca = rate & INCVALUE_MASK;
	अगर (neg_adj)
		inca |= ISGN;

	wr32(E1000_TIMINCA, inca);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_adjसमय_82576(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);
	समयcounter_adjसमय(&igb->tc, delta);
	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_adjसमय_i210(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 now, then = ns_to_बारpec64(delta);

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	igb_ptp_पढ़ो_i210(igb, &now);
	now = बारpec64_add(now, then);
	igb_ptp_ग_लिखो_i210(igb, (स्थिर काष्ठा बारpec64 *)&now);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_समय_लोx_82576(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा बारpec64 *ts,
				  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	अचिन्हित दीर्घ flags;
	u32 lo, hi;
	u64 ns;

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	ptp_पढ़ो_प्रणाली_prets(sts);
	lo = rd32(E1000_SYSTIML);
	ptp_पढ़ो_प्रणाली_postts(sts);
	hi = rd32(E1000_SYSTIMH);

	ns = समयcounter_cyc2समय(&igb->tc, ((u64)hi << 32) | lo);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_समय_लोx_82580(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा बारpec64 *ts,
				  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	अचिन्हित दीर्घ flags;
	u32 lo, hi;
	u64 ns;

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	ptp_पढ़ो_प्रणाली_prets(sts);
	rd32(E1000_SYSTIMR);
	ptp_पढ़ो_प्रणाली_postts(sts);
	lo = rd32(E1000_SYSTIML);
	hi = rd32(E1000_SYSTIMH);

	ns = समयcounter_cyc2समय(&igb->tc, ((u64)hi << 32) | lo);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_समय_लोx_i210(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा बारpec64 *ts,
				 काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	ptp_पढ़ो_प्रणाली_prets(sts);
	rd32(E1000_SYSTIMR);
	ptp_पढ़ो_प्रणाली_postts(sts);
	ts->tv_nsec = rd32(E1000_SYSTIML);
	ts->tv_sec = rd32(E1000_SYSTIMH);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_समय_रखो_82576(काष्ठा ptp_घड़ी_info *ptp,
				 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	अचिन्हित दीर्घ flags;
	u64 ns;

	ns = बारpec64_to_ns(ts);

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	समयcounter_init(&igb->tc, &igb->cc, ns);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ptp_समय_रखो_i210(काष्ठा ptp_घड़ी_info *ptp,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा igb_adapter *igb = container_of(ptp, काष्ठा igb_adapter,
					       ptp_caps);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&igb->पंचांगreg_lock, flags);

	igb_ptp_ग_लिखो_i210(igb, ts);

	spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम igb_pin_direction(पूर्णांक pin, पूर्णांक input, u32 *ctrl, u32 *ctrl_ext)
अणु
	u32 *ptr = pin < 2 ? ctrl : ctrl_ext;
	अटल स्थिर u32 mask[IGB_N_SDP] = अणु
		E1000_CTRL_SDP0_सूची,
		E1000_CTRL_SDP1_सूची,
		E1000_CTRL_EXT_SDP2_सूची,
		E1000_CTRL_EXT_SDP3_सूची,
	पूर्ण;

	अगर (input)
		*ptr &= ~mask[pin];
	अन्यथा
		*ptr |= mask[pin];
पूर्ण

अटल व्योम igb_pin_extts(काष्ठा igb_adapter *igb, पूर्णांक chan, पूर्णांक pin)
अणु
	अटल स्थिर u32 aux0_sel_sdp[IGB_N_SDP] = अणु
		AUX0_SEL_SDP0, AUX0_SEL_SDP1, AUX0_SEL_SDP2, AUX0_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 aux1_sel_sdp[IGB_N_SDP] = अणु
		AUX1_SEL_SDP0, AUX1_SEL_SDP1, AUX1_SEL_SDP2, AUX1_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_en[IGB_N_SDP] = अणु
		TS_SDP0_EN, TS_SDP1_EN, TS_SDP2_EN, TS_SDP3_EN,
	पूर्ण;
	काष्ठा e1000_hw *hw = &igb->hw;
	u32 ctrl, ctrl_ext, tssdp = 0;

	ctrl = rd32(E1000_CTRL);
	ctrl_ext = rd32(E1000_CTRL_EXT);
	tssdp = rd32(E1000_TSSDP);

	igb_pin_direction(pin, 1, &ctrl, &ctrl_ext);

	/* Make sure this pin is not enabled as an output. */
	tssdp &= ~ts_sdp_en[pin];

	अगर (chan == 1) अणु
		tssdp &= ~AUX1_SEL_SDP3;
		tssdp |= aux1_sel_sdp[pin] | AUX1_TS_SDP_EN;
	पूर्ण अन्यथा अणु
		tssdp &= ~AUX0_SEL_SDP3;
		tssdp |= aux0_sel_sdp[pin] | AUX0_TS_SDP_EN;
	पूर्ण

	wr32(E1000_TSSDP, tssdp);
	wr32(E1000_CTRL, ctrl);
	wr32(E1000_CTRL_EXT, ctrl_ext);
पूर्ण

अटल व्योम igb_pin_perout(काष्ठा igb_adapter *igb, पूर्णांक chan, पूर्णांक pin, पूर्णांक freq)
अणु
	अटल स्थिर u32 aux0_sel_sdp[IGB_N_SDP] = अणु
		AUX0_SEL_SDP0, AUX0_SEL_SDP1, AUX0_SEL_SDP2, AUX0_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 aux1_sel_sdp[IGB_N_SDP] = अणु
		AUX1_SEL_SDP0, AUX1_SEL_SDP1, AUX1_SEL_SDP2, AUX1_SEL_SDP3,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_en[IGB_N_SDP] = अणु
		TS_SDP0_EN, TS_SDP1_EN, TS_SDP2_EN, TS_SDP3_EN,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_sel_tt0[IGB_N_SDP] = अणु
		TS_SDP0_SEL_TT0, TS_SDP1_SEL_TT0,
		TS_SDP2_SEL_TT0, TS_SDP3_SEL_TT0,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_sel_tt1[IGB_N_SDP] = अणु
		TS_SDP0_SEL_TT1, TS_SDP1_SEL_TT1,
		TS_SDP2_SEL_TT1, TS_SDP3_SEL_TT1,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_sel_fc0[IGB_N_SDP] = अणु
		TS_SDP0_SEL_FC0, TS_SDP1_SEL_FC0,
		TS_SDP2_SEL_FC0, TS_SDP3_SEL_FC0,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_sel_fc1[IGB_N_SDP] = अणु
		TS_SDP0_SEL_FC1, TS_SDP1_SEL_FC1,
		TS_SDP2_SEL_FC1, TS_SDP3_SEL_FC1,
	पूर्ण;
	अटल स्थिर u32 ts_sdp_sel_clr[IGB_N_SDP] = अणु
		TS_SDP0_SEL_FC1, TS_SDP1_SEL_FC1,
		TS_SDP2_SEL_FC1, TS_SDP3_SEL_FC1,
	पूर्ण;
	काष्ठा e1000_hw *hw = &igb->hw;
	u32 ctrl, ctrl_ext, tssdp = 0;

	ctrl = rd32(E1000_CTRL);
	ctrl_ext = rd32(E1000_CTRL_EXT);
	tssdp = rd32(E1000_TSSDP);

	igb_pin_direction(pin, 0, &ctrl, &ctrl_ext);

	/* Make sure this pin is not enabled as an input. */
	अगर ((tssdp & AUX0_SEL_SDP3) == aux0_sel_sdp[pin])
		tssdp &= ~AUX0_TS_SDP_EN;

	अगर ((tssdp & AUX1_SEL_SDP3) == aux1_sel_sdp[pin])
		tssdp &= ~AUX1_TS_SDP_EN;

	tssdp &= ~ts_sdp_sel_clr[pin];
	अगर (freq) अणु
		अगर (chan == 1)
			tssdp |= ts_sdp_sel_fc1[pin];
		अन्यथा
			tssdp |= ts_sdp_sel_fc0[pin];
	पूर्ण अन्यथा अणु
		अगर (chan == 1)
			tssdp |= ts_sdp_sel_tt1[pin];
		अन्यथा
			tssdp |= ts_sdp_sel_tt0[pin];
	पूर्ण
	tssdp |= ts_sdp_en[pin];

	wr32(E1000_TSSDP, tssdp);
	wr32(E1000_CTRL, ctrl);
	wr32(E1000_CTRL_EXT, ctrl_ext);
पूर्ण

अटल पूर्णांक igb_ptp_feature_enable_i210(काष्ठा ptp_घड़ी_info *ptp,
				       काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा igb_adapter *igb =
		container_of(ptp, काष्ठा igb_adapter, ptp_caps);
	काष्ठा e1000_hw *hw = &igb->hw;
	u32 tsauxc, tsim, tsauxc_mask, tsim_mask, trgttiml, trgttimh, freqout;
	अचिन्हित दीर्घ flags;
	काष्ठा बारpec64 ts;
	पूर्णांक use_freq = 0, pin = -1;
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
			pin = ptp_find_pin(igb->ptp_घड़ी, PTP_PF_EXTTS,
					   rq->extts.index);
			अगर (pin < 0)
				वापस -EBUSY;
		पूर्ण
		अगर (rq->extts.index == 1) अणु
			tsauxc_mask = TSAUXC_EN_TS1;
			tsim_mask = TSINTR_AUTT1;
		पूर्ण अन्यथा अणु
			tsauxc_mask = TSAUXC_EN_TS0;
			tsim_mask = TSINTR_AUTT0;
		पूर्ण
		spin_lock_irqsave(&igb->पंचांगreg_lock, flags);
		tsauxc = rd32(E1000_TSAUXC);
		tsim = rd32(E1000_TSIM);
		अगर (on) अणु
			igb_pin_extts(igb, rq->extts.index, pin);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		पूर्ण अन्यथा अणु
			tsauxc &= ~tsauxc_mask;
			tsim &= ~tsim_mask;
		पूर्ण
		wr32(E1000_TSAUXC, tsauxc);
		wr32(E1000_TSIM, tsim);
		spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);
		वापस 0;

	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags)
			वापस -EOPNOTSUPP;

		अगर (on) अणु
			pin = ptp_find_pin(igb->ptp_घड़ी, PTP_PF_PEROUT,
					   rq->perout.index);
			अगर (pin < 0)
				वापस -EBUSY;
		पूर्ण
		ts.tv_sec = rq->perout.period.sec;
		ts.tv_nsec = rq->perout.period.nsec;
		ns = बारpec64_to_ns(&ts);
		ns = ns >> 1;
		अगर (on && ((ns <= 70000000LL) || (ns == 125000000LL) ||
			   (ns == 250000000LL) || (ns == 500000000LL))) अणु
			अगर (ns < 8LL)
				वापस -EINVAL;
			use_freq = 1;
		पूर्ण
		ts = ns_to_बारpec64(ns);
		अगर (rq->perout.index == 1) अणु
			अगर (use_freq) अणु
				tsauxc_mask = TSAUXC_EN_CLK1 | TSAUXC_ST1;
				tsim_mask = 0;
			पूर्ण अन्यथा अणु
				tsauxc_mask = TSAUXC_EN_TT1;
				tsim_mask = TSINTR_TT1;
			पूर्ण
			trgttiml = E1000_TRGTTIML1;
			trgttimh = E1000_TRGTTIMH1;
			freqout = E1000_FREQOUT1;
		पूर्ण अन्यथा अणु
			अगर (use_freq) अणु
				tsauxc_mask = TSAUXC_EN_CLK0 | TSAUXC_ST0;
				tsim_mask = 0;
			पूर्ण अन्यथा अणु
				tsauxc_mask = TSAUXC_EN_TT0;
				tsim_mask = TSINTR_TT0;
			पूर्ण
			trgttiml = E1000_TRGTTIML0;
			trgttimh = E1000_TRGTTIMH0;
			freqout = E1000_FREQOUT0;
		पूर्ण
		spin_lock_irqsave(&igb->पंचांगreg_lock, flags);
		tsauxc = rd32(E1000_TSAUXC);
		tsim = rd32(E1000_TSIM);
		अगर (rq->perout.index == 1) अणु
			tsauxc &= ~(TSAUXC_EN_TT1 | TSAUXC_EN_CLK1 | TSAUXC_ST1);
			tsim &= ~TSINTR_TT1;
		पूर्ण अन्यथा अणु
			tsauxc &= ~(TSAUXC_EN_TT0 | TSAUXC_EN_CLK0 | TSAUXC_ST0);
			tsim &= ~TSINTR_TT0;
		पूर्ण
		अगर (on) अणु
			पूर्णांक i = rq->perout.index;
			igb_pin_perout(igb, i, pin, use_freq);
			igb->perout[i].start.tv_sec = rq->perout.start.sec;
			igb->perout[i].start.tv_nsec = rq->perout.start.nsec;
			igb->perout[i].period.tv_sec = ts.tv_sec;
			igb->perout[i].period.tv_nsec = ts.tv_nsec;
			wr32(trgttimh, rq->perout.start.sec);
			wr32(trgttiml, rq->perout.start.nsec);
			अगर (use_freq)
				wr32(freqout, ns);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		पूर्ण
		wr32(E1000_TSAUXC, tsauxc);
		wr32(E1000_TSIM, tsim);
		spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);
		वापस 0;

	हाल PTP_CLK_REQ_PPS:
		spin_lock_irqsave(&igb->पंचांगreg_lock, flags);
		tsim = rd32(E1000_TSIM);
		अगर (on)
			tsim |= TSINTR_SYS_WRAP;
		अन्यथा
			tsim &= ~TSINTR_SYS_WRAP;
		igb->pps_sys_wrap_on = !!on;
		wr32(E1000_TSIM, tsim);
		spin_unlock_irqrestore(&igb->पंचांगreg_lock, flags);
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक igb_ptp_feature_enable(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक igb_ptp_verअगरy_pin(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
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
 * igb_ptp_tx_work
 * @work: poपूर्णांकer to work काष्ठा
 *
 * This work function polls the TSYNCTXCTL valid bit to determine when a
 * बारtamp has been taken क्रम the current stored skb.
 **/
अटल व्योम igb_ptp_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igb_adapter *adapter = container_of(work, काष्ठा igb_adapter,
						   ptp_tx_work);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tsynctxctl;

	अगर (!adapter->ptp_tx_skb)
		वापस;

	अगर (समय_is_beक्रमe_jअगरfies(adapter->ptp_tx_start +
				   IGB_PTP_TX_TIMEOUT)) अणु
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
		adapter->tx_hwtstamp_समयouts++;
		/* Clear the tx valid bit in TSYNCTXCTL रेजिस्टर to enable
		 * पूर्णांकerrupt
		 */
		rd32(E1000_TXSTMPH);
		dev_warn(&adapter->pdev->dev, "clearing Tx timestamp hang\n");
		वापस;
	पूर्ण

	tsynctxctl = rd32(E1000_TSYNCTXCTL);
	अगर (tsynctxctl & E1000_TSYNCTXCTL_VALID)
		igb_ptp_tx_hwtstamp(adapter);
	अन्यथा
		/* reschedule to check later */
		schedule_work(&adapter->ptp_tx_work);
पूर्ण

अटल व्योम igb_ptp_overflow_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा igb_adapter *igb =
		container_of(work, काष्ठा igb_adapter, ptp_overflow_work.work);
	काष्ठा बारpec64 ts;
	u64 ns;

	/* Update the समयcounter */
	ns = समयcounter_पढ़ो(&igb->tc);

	ts = ns_to_बारpec64(ns);
	pr_debug("igb overflow check at %lld.%09lu\n",
		 (दीर्घ दीर्घ) ts.tv_sec, ts.tv_nsec);

	schedule_delayed_work(&igb->ptp_overflow_work,
			      IGB_SYSTIM_OVERFLOW_PERIOD);
पूर्ण

/**
 * igb_ptp_rx_hang - detect error हाल when Rx बारtamp रेजिस्टरs latched
 * @adapter: निजी network adapter काष्ठाure
 *
 * This watchकरोg task is scheduled to detect error हाल where hardware has
 * dropped an Rx packet that was बारtamped when the ring is full. The
 * particular error is rare but leaves the device in a state unable to बारtamp
 * any future packets.
 **/
व्योम igb_ptp_rx_hang(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tsyncrxctl = rd32(E1000_TSYNCRXCTL);
	अचिन्हित दीर्घ rx_event;

	/* Other hardware uses per-packet बारtamps */
	अगर (hw->mac.type != e1000_82576)
		वापस;

	/* If we करोn't have a valid बारtamp in the रेजिस्टरs, just update the
	 * समयout counter and निकास
	 */
	अगर (!(tsyncrxctl & E1000_TSYNCRXCTL_VALID)) अणु
		adapter->last_rx_ptp_check = jअगरfies;
		वापस;
	पूर्ण

	/* Determine the most recent watchकरोg or rx_बारtamp event */
	rx_event = adapter->last_rx_ptp_check;
	अगर (समय_after(adapter->last_rx_बारtamp, rx_event))
		rx_event = adapter->last_rx_बारtamp;

	/* Only need to पढ़ो the high RXSTMP रेजिस्टर to clear the lock */
	अगर (समय_is_beक्रमe_jअगरfies(rx_event + 5 * HZ)) अणु
		rd32(E1000_RXSTMPH);
		adapter->last_rx_ptp_check = jअगरfies;
		adapter->rx_hwtstamp_cleared++;
		dev_warn(&adapter->pdev->dev, "clearing Rx timestamp hang\n");
	पूर्ण
पूर्ण

/**
 * igb_ptp_tx_hang - detect error हाल where Tx बारtamp never finishes
 * @adapter: निजी network adapter काष्ठाure
 */
व्योम igb_ptp_tx_hang(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool समयout = समय_is_beक्रमe_jअगरfies(adapter->ptp_tx_start +
					      IGB_PTP_TX_TIMEOUT);

	अगर (!adapter->ptp_tx_skb)
		वापस;

	अगर (!test_bit(__IGB_PTP_TX_IN_PROGRESS, &adapter->state))
		वापस;

	/* If we haven't received a बारtamp within the समयout, it is
	 * reasonable to assume that it will never occur, so we can unlock the
	 * बारtamp bit when this occurs.
	 */
	अगर (समयout) अणु
		cancel_work_sync(&adapter->ptp_tx_work);
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
		adapter->tx_hwtstamp_समयouts++;
		/* Clear the tx valid bit in TSYNCTXCTL रेजिस्टर to enable
		 * पूर्णांकerrupt
		 */
		rd32(E1000_TXSTMPH);
		dev_warn(&adapter->pdev->dev, "clearing Tx timestamp hang\n");
	पूर्ण
पूर्ण

/**
 * igb_ptp_tx_hwtstamp - utility function which checks क्रम TX समय stamp
 * @adapter: Board निजी काष्ठाure.
 *
 * If we were asked to करो hardware stamping and such a समय stamp is
 * available, then it must have been क्रम this skb here because we only
 * allow only one such packet पूर्णांकo the queue.
 **/
अटल व्योम igb_ptp_tx_hwtstamp(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा sk_buff *skb = adapter->ptp_tx_skb;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	u64 regval;
	पूर्णांक adjust = 0;

	regval = rd32(E1000_TXSTMPL);
	regval |= (u64)rd32(E1000_TXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, &shhwtstamps, regval);
	/* adjust बारtamp क्रम the TX latency based on link speed */
	अगर (adapter->hw.mac.type == e1000_i210) अणु
		चयन (adapter->link_speed) अणु
		हाल SPEED_10:
			adjust = IGB_I210_TX_LATENCY_10;
			अवरोध;
		हाल SPEED_100:
			adjust = IGB_I210_TX_LATENCY_100;
			अवरोध;
		हाल SPEED_1000:
			adjust = IGB_I210_TX_LATENCY_1000;
			अवरोध;
		पूर्ण
	पूर्ण

	shhwtstamps.hwtstamp =
		kसमय_add_ns(shhwtstamps.hwtstamp, adjust);

	/* Clear the lock early beक्रमe calling skb_tstamp_tx so that
	 * applications are not woken up beक्रमe the lock bit is clear. We use
	 * a copy of the skb poपूर्णांकer to ensure other thपढ़ोs can't change it
	 * जबतक we're notअगरying the stack.
	 */
	adapter->ptp_tx_skb = शून्य;
	clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);

	/* Notअगरy the stack and मुक्त the skb after we've unlocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kमुक्त_skb_any(skb);
पूर्ण

/**
 * igb_ptp_rx_pktstamp - retrieve Rx per packet बारtamp
 * @q_vector: Poपूर्णांकer to पूर्णांकerrupt specअगरic काष्ठाure
 * @va: Poपूर्णांकer to address containing Rx buffer
 * @बारtamp: Poपूर्णांकer where बारtamp will be stored
 *
 * This function is meant to retrieve a बारtamp from the first buffer of an
 * incoming frame.  The value is stored in little endian क्रमmat starting on
 * byte 8
 *
 * Returns: The बारtamp header length or 0 अगर not available
 **/
पूर्णांक igb_ptp_rx_pktstamp(काष्ठा igb_q_vector *q_vector, व्योम *va,
			kसमय_प्रकार *बारtamp)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा skb_shared_hwtstamps ts;
	__le64 *regval = (__le64 *)va;
	पूर्णांक adjust = 0;

	अगर (!(adapter->ptp_flags & IGB_PTP_ENABLED))
		वापस 0;

	/* The बारtamp is recorded in little endian क्रमmat.
	 * DWORD: 0        1        2        3
	 * Field: Reserved Reserved SYSTIML  SYSTIMH
	 */

	/* check reserved dwords are zero, be/le करोesn't matter क्रम zero */
	अगर (regval[0])
		वापस 0;

	igb_ptp_systim_to_hwtstamp(adapter, &ts, le64_to_cpu(regval[1]));

	/* adjust बारtamp क्रम the RX latency based on link speed */
	अगर (adapter->hw.mac.type == e1000_i210) अणु
		चयन (adapter->link_speed) अणु
		हाल SPEED_10:
			adjust = IGB_I210_RX_LATENCY_10;
			अवरोध;
		हाल SPEED_100:
			adjust = IGB_I210_RX_LATENCY_100;
			अवरोध;
		हाल SPEED_1000:
			adjust = IGB_I210_RX_LATENCY_1000;
			अवरोध;
		पूर्ण
	पूर्ण

	*बारtamp = kसमय_sub_ns(ts.hwtstamp, adjust);

	वापस IGB_TS_HDR_LEN;
पूर्ण

/**
 * igb_ptp_rx_rgtstamp - retrieve Rx बारtamp stored in रेजिस्टर
 * @q_vector: Poपूर्णांकer to पूर्णांकerrupt specअगरic काष्ठाure
 * @skb: Buffer containing बारtamp and packet
 *
 * This function is meant to retrieve a बारtamp from the पूर्णांकernal रेजिस्टरs
 * of the adapter and store it in the skb.
 **/
व्योम igb_ptp_rx_rgtstamp(काष्ठा igb_q_vector *q_vector, काष्ठा sk_buff *skb)
अणु
	काष्ठा igb_adapter *adapter = q_vector->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक adjust = 0;
	u64 regval;

	अगर (!(adapter->ptp_flags & IGB_PTP_ENABLED))
		वापस;

	/* If this bit is set, then the RX रेजिस्टरs contain the समय stamp. No
	 * other packet will be समय stamped until we पढ़ो these रेजिस्टरs, so
	 * पढ़ो the रेजिस्टरs to make them available again. Because only one
	 * packet can be समय stamped at a समय, we know that the रेजिस्टर
	 * values must beदीर्घ to this one here and thereक्रमe we करोn't need to
	 * compare any of the additional attributes stored क्रम it.
	 *
	 * If nothing went wrong, then it should have a shared tx_flags that we
	 * can turn पूर्णांकo a skb_shared_hwtstamps.
	 */
	अगर (!(rd32(E1000_TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID))
		वापस;

	regval = rd32(E1000_RXSTMPL);
	regval |= (u64)rd32(E1000_RXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adapter, skb_hwtstamps(skb), regval);

	/* adjust बारtamp क्रम the RX latency based on link speed */
	अगर (adapter->hw.mac.type == e1000_i210) अणु
		चयन (adapter->link_speed) अणु
		हाल SPEED_10:
			adjust = IGB_I210_RX_LATENCY_10;
			अवरोध;
		हाल SPEED_100:
			adjust = IGB_I210_RX_LATENCY_100;
			अवरोध;
		हाल SPEED_1000:
			adjust = IGB_I210_RX_LATENCY_1000;
			अवरोध;
		पूर्ण
	पूर्ण
	skb_hwtstamps(skb)->hwtstamp =
		kसमय_sub_ns(skb_hwtstamps(skb)->hwtstamp, adjust);

	/* Update the last_rx_बारtamp समयr in order to enable watchकरोg check
	 * क्रम error हाल of latched बारtamp on a dropped packet.
	 */
	adapter->last_rx_बारtamp = jअगरfies;
पूर्ण

/**
 * igb_ptp_get_ts_config - get hardware समय stamping config
 * @netdev: netdev काष्ठा
 * @अगरr: पूर्णांकerface काष्ठा
 *
 * Get the hwtstamp_config settings to वापस to the user. Rather than attempt
 * to deस्थिरruct the settings from the रेजिस्टरs, just वापस a shaकरोw copy
 * of the last known settings.
 **/
पूर्णांक igb_ptp_get_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config *config = &adapter->tstamp_config;

	वापस copy_to_user(अगरr->अगरr_data, config, माप(*config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * igb_ptp_set_बारtamp_mode - setup hardware क्रम बारtamping
 * @adapter: networking device काष्ठाure
 * @config: hwtstamp configuration
 *
 * Outgoing समय stamping can be enabled and disabled. Play nice and
 * disable it when requested, although it shouldn't हाल any overhead
 * when no packet needs it. At most one packet in the queue may be
 * marked क्रम समय stamping, otherwise it would be impossible to tell
 * क्रम sure to which packet the hardware समय stamp beदीर्घs.
 *
 * Incoming समय stamping has to be configured via the hardware
 * filters. Not all combinations are supported, in particular event
 * type has to be specअगरied. Matching the kind of event packet is
 * not supported, with the exception of "all V2 events regardless of
 * level 2 or 4".
 */
अटल पूर्णांक igb_ptp_set_बारtamp_mode(काष्ठा igb_adapter *adapter,
				      काष्ठा hwtstamp_config *config)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = E1000_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
	u32 tsync_rx_cfg = 0;
	bool is_l4 = false;
	bool is_l2 = false;
	u32 regval;

	/* reserved क्रम future extensions */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tsync_rx_ctl = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_cfg = E1000_TSYNCRXCFG_PTP_V1_SYNC_MESSAGE;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		tsync_rx_cfg = E1000_TSYNCRXCFG_PTP_V1_DELAY_REQ_MESSAGE;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_EVENT_V2;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		is_l2 = true;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
		/* 82576 cannot बारtamp all packets, which it needs to करो to
		 * support both V1 Sync and Delay_Req messages
		 */
		अगर (hw->mac.type != e1000_82576) अणु
			tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
			config->rx_filter = HWTSTAMP_FILTER_ALL;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		वापस -दुस्फल;
	पूर्ण

	अगर (hw->mac.type == e1000_82575) अणु
		अगर (tsync_rx_ctl | tsync_tx_ctl)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* Per-packet बारtamping only works अगर all packets are
	 * बारtamped, so enable बारtamping in all packets as
	 * दीर्घ as one Rx filter was configured.
	 */
	अगर ((hw->mac.type >= e1000_82580) && tsync_rx_ctl) अणु
		tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		is_l2 = true;
		is_l4 = true;

		अगर ((hw->mac.type == e1000_i210) ||
		    (hw->mac.type == e1000_i211)) अणु
			regval = rd32(E1000_RXPBS);
			regval |= E1000_RXPBS_CFG_TS_EN;
			wr32(E1000_RXPBS, regval);
		पूर्ण
	पूर्ण

	/* enable/disable TX */
	regval = rd32(E1000_TSYNCTXCTL);
	regval &= ~E1000_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	wr32(E1000_TSYNCTXCTL, regval);

	/* enable/disable RX */
	regval = rd32(E1000_TSYNCRXCTL);
	regval &= ~(E1000_TSYNCRXCTL_ENABLED | E1000_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	wr32(E1000_TSYNCRXCTL, regval);

	/* define which PTP packets are समय stamped */
	wr32(E1000_TSYNCRXCFG, tsync_rx_cfg);

	/* define ethertype filter क्रम बारtamped packets */
	अगर (is_l2)
		wr32(E1000_ETQF(IGB_ETQF_FILTER_1588),
		     (E1000_ETQF_FILTER_ENABLE | /* enable filter */
		      E1000_ETQF_1588 | /* enable बारtamping */
		      ETH_P_1588));     /* 1588 eth protocol type */
	अन्यथा
		wr32(E1000_ETQF(IGB_ETQF_FILTER_1588), 0);

	/* L4 Queue Filter[3]: filter by destination port and protocol */
	अगर (is_l4) अणु
		u32 ftqf = (IPPROTO_UDP /* UDP */
			| E1000_FTQF_VF_BP /* VF not compared */
			| E1000_FTQF_1588_TIME_STAMP /* Enable Timestamping */
			| E1000_FTQF_MASK); /* mask all inमाला_दो */
		ftqf &= ~E1000_FTQF_MASK_PROTO_BP; /* enable protocol check */

		wr32(E1000_IMIR(3), htons(PTP_EV_PORT));
		wr32(E1000_IMIREXT(3),
		     (E1000_IMIREXT_SIZE_BP | E1000_IMIREXT_CTRL_BP));
		अगर (hw->mac.type == e1000_82576) अणु
			/* enable source port check */
			wr32(E1000_SPQF(3), htons(PTP_EV_PORT));
			ftqf &= ~E1000_FTQF_MASK_SOURCE_PORT_BP;
		पूर्ण
		wr32(E1000_FTQF(3), ftqf);
	पूर्ण अन्यथा अणु
		wr32(E1000_FTQF(3), E1000_FTQF_MASK);
	पूर्ण
	wrfl();

	/* clear TX/RX समय stamp रेजिस्टरs, just to be sure */
	regval = rd32(E1000_TXSTMPL);
	regval = rd32(E1000_TXSTMPH);
	regval = rd32(E1000_RXSTMPL);
	regval = rd32(E1000_RXSTMPH);

	वापस 0;
पूर्ण

/**
 * igb_ptp_set_ts_config - set hardware समय stamping config
 * @netdev: netdev काष्ठा
 * @अगरr: पूर्णांकerface काष्ठा
 *
 **/
पूर्णांक igb_ptp_set_ts_config(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;
	पूर्णांक err;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	err = igb_ptp_set_बारtamp_mode(adapter, &config);
	अगर (err)
		वापस err;

	/* save these settings क्रम future reference */
	स_नकल(&adapter->tstamp_config, &config,
	       माप(adapter->tstamp_config));

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/**
 * igb_ptp_init - Initialize PTP functionality
 * @adapter: Board निजी काष्ठाure
 *
 * This function is called at device probe to initialize the PTP
 * functionality.
 */
व्योम igb_ptp_init(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
		snम_लिखो(adapter->ptp_caps.name, 16, "%pm", netdev->dev_addr);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 999999881;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.pps = 0;
		adapter->ptp_caps.adjfreq = igb_ptp_adjfreq_82576;
		adapter->ptp_caps.adjसमय = igb_ptp_adjसमय_82576;
		adapter->ptp_caps.समय_लोx64 = igb_ptp_समय_लोx_82576;
		adapter->ptp_caps.समय_रखो64 = igb_ptp_समय_रखो_82576;
		adapter->ptp_caps.enable = igb_ptp_feature_enable;
		adapter->cc.पढ़ो = igb_ptp_पढ़ो_82576;
		adapter->cc.mask = CYCLECOUNTER_MASK(64);
		adapter->cc.mult = 1;
		adapter->cc.shअगरt = IGB_82576_TSYNC_SHIFT;
		adapter->ptp_flags |= IGB_PTP_OVERFLOW_CHECK;
		अवरोध;
	हाल e1000_82580:
	हाल e1000_i354:
	हाल e1000_i350:
		snम_लिखो(adapter->ptp_caps.name, 16, "%pm", netdev->dev_addr);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 62499999;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.pps = 0;
		adapter->ptp_caps.adjfine = igb_ptp_adjfine_82580;
		adapter->ptp_caps.adjसमय = igb_ptp_adjसमय_82576;
		adapter->ptp_caps.समय_लोx64 = igb_ptp_समय_लोx_82580;
		adapter->ptp_caps.समय_रखो64 = igb_ptp_समय_रखो_82576;
		adapter->ptp_caps.enable = igb_ptp_feature_enable;
		adapter->cc.पढ़ो = igb_ptp_पढ़ो_82580;
		adapter->cc.mask = CYCLECOUNTER_MASK(IGB_NBITS_82580);
		adapter->cc.mult = 1;
		adapter->cc.shअगरt = 0;
		adapter->ptp_flags |= IGB_PTP_OVERFLOW_CHECK;
		अवरोध;
	हाल e1000_i210:
	हाल e1000_i211:
		क्रम (i = 0; i < IGB_N_SDP; i++) अणु
			काष्ठा ptp_pin_desc *ppd = &adapter->sdp_config[i];

			snम_लिखो(ppd->name, माप(ppd->name), "SDP%d", i);
			ppd->index = i;
			ppd->func = PTP_PF_NONE;
		पूर्ण
		snम_लिखो(adapter->ptp_caps.name, 16, "%pm", netdev->dev_addr);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 62499999;
		adapter->ptp_caps.n_ext_ts = IGB_N_EXTTS;
		adapter->ptp_caps.n_per_out = IGB_N_PEROUT;
		adapter->ptp_caps.n_pins = IGB_N_SDP;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.pin_config = adapter->sdp_config;
		adapter->ptp_caps.adjfine = igb_ptp_adjfine_82580;
		adapter->ptp_caps.adjसमय = igb_ptp_adjसमय_i210;
		adapter->ptp_caps.समय_लोx64 = igb_ptp_समय_लोx_i210;
		adapter->ptp_caps.समय_रखो64 = igb_ptp_समय_रखो_i210;
		adapter->ptp_caps.enable = igb_ptp_feature_enable_i210;
		adapter->ptp_caps.verअगरy = igb_ptp_verअगरy_pin;
		अवरोध;
	शेष:
		adapter->ptp_घड़ी = शून्य;
		वापस;
	पूर्ण

	spin_lock_init(&adapter->पंचांगreg_lock);
	INIT_WORK(&adapter->ptp_tx_work, igb_ptp_tx_work);

	अगर (adapter->ptp_flags & IGB_PTP_OVERFLOW_CHECK)
		INIT_DELAYED_WORK(&adapter->ptp_overflow_work,
				  igb_ptp_overflow_check);

	adapter->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
	adapter->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	igb_ptp_reset(adapter);

	adapter->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&adapter->ptp_caps,
						&adapter->pdev->dev);
	अगर (IS_ERR(adapter->ptp_घड़ी)) अणु
		adapter->ptp_घड़ी = शून्य;
		dev_err(&adapter->pdev->dev, "ptp_clock_register failed\n");
	पूर्ण अन्यथा अगर (adapter->ptp_घड़ी) अणु
		dev_info(&adapter->pdev->dev, "added PHC on %s\n",
			 adapter->netdev->name);
		adapter->ptp_flags |= IGB_PTP_ENABLED;
	पूर्ण
पूर्ण

/**
 * igb_ptp_suspend - Disable PTP work items and prepare क्रम suspend
 * @adapter: Board निजी काष्ठाure
 *
 * This function stops the overflow check work and PTP Tx बारtamp work, and
 * will prepare the device क्रम OS suspend.
 */
व्योम igb_ptp_suspend(काष्ठा igb_adapter *adapter)
अणु
	अगर (!(adapter->ptp_flags & IGB_PTP_ENABLED))
		वापस;

	अगर (adapter->ptp_flags & IGB_PTP_OVERFLOW_CHECK)
		cancel_delayed_work_sync(&adapter->ptp_overflow_work);

	cancel_work_sync(&adapter->ptp_tx_work);
	अगर (adapter->ptp_tx_skb) अणु
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
		clear_bit_unlock(__IGB_PTP_TX_IN_PROGRESS, &adapter->state);
	पूर्ण
पूर्ण

/**
 * igb_ptp_stop - Disable PTP device and stop the overflow check.
 * @adapter: Board निजी काष्ठाure.
 *
 * This function stops the PTP support and cancels the delayed work.
 **/
व्योम igb_ptp_stop(काष्ठा igb_adapter *adapter)
अणु
	igb_ptp_suspend(adapter);

	अगर (adapter->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		dev_info(&adapter->pdev->dev, "removed PHC on %s\n",
			 adapter->netdev->name);
		adapter->ptp_flags &= ~IGB_PTP_ENABLED;
	पूर्ण
पूर्ण

/**
 * igb_ptp_reset - Re-enable the adapter क्रम PTP following a reset.
 * @adapter: Board निजी काष्ठाure.
 *
 * This function handles the reset work required to re-enable the PTP device.
 **/
व्योम igb_ptp_reset(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;

	/* reset the tstamp_config */
	igb_ptp_set_बारtamp_mode(adapter, &adapter->tstamp_config);

	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_82576:
		/* Dial the nominal frequency. */
		wr32(E1000_TIMINCA, INCPERIOD_82576 | INCVALUE_82576);
		अवरोध;
	हाल e1000_82580:
	हाल e1000_i354:
	हाल e1000_i350:
	हाल e1000_i210:
	हाल e1000_i211:
		wr32(E1000_TSAUXC, 0x0);
		wr32(E1000_TSSDP, 0x0);
		wr32(E1000_TSIM,
		     TSYNC_INTERRUPTS |
		     (adapter->pps_sys_wrap_on ? TSINTR_SYS_WRAP : 0));
		wr32(E1000_IMS, E1000_IMS_TS);
		अवरोध;
	शेष:
		/* No work to करो. */
		जाओ out;
	पूर्ण

	/* Re-initialize the समयr. */
	अगर ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211)) अणु
		काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(kसमय_get_real());

		igb_ptp_ग_लिखो_i210(adapter, &ts);
	पूर्ण अन्यथा अणु
		समयcounter_init(&adapter->tc, &adapter->cc,
				 kसमय_प्रकारo_ns(kसमय_get_real()));
	पूर्ण
out:
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);

	wrfl();

	अगर (adapter->ptp_flags & IGB_PTP_OVERFLOW_CHECK)
		schedule_delayed_work(&adapter->ptp_overflow_work,
				      IGB_SYSTIM_OVERFLOW_PERIOD);
पूर्ण
