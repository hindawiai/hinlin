<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot PTP घड़ी driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 * Copyright 2020 NXP
 */
#समावेश <linux/समय64.h>

#समावेश <soc/mscc/ocelot_ptp.h>
#समावेश <soc/mscc/ocelot_sys.h>
#समावेश <soc/mscc/ocelot.h>

पूर्णांक ocelot_ptp_समय_लो64(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा ocelot *ocelot = container_of(ptp, काष्ठा ocelot, ptp_info);
	अचिन्हित दीर्घ flags;
	समय64_t s;
	u32 val;
	s64 ns;

	spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);

	val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);
	val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK | PTP_PIN_CFG_DOM);
	val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_SAVE);
	ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);

	s = ocelot_पढ़ो_rix(ocelot, PTP_PIN_TOD_SEC_MSB, TOD_ACC_PIN) & 0xffff;
	s <<= 32;
	s += ocelot_पढ़ो_rix(ocelot, PTP_PIN_TOD_SEC_LSB, TOD_ACC_PIN);
	ns = ocelot_पढ़ो_rix(ocelot, PTP_PIN_TOD_NSEC, TOD_ACC_PIN);

	spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);

	/* Deal with negative values */
	अगर (ns >= 0x3ffffff0 && ns <= 0x3fffffff) अणु
		s--;
		ns &= 0xf;
		ns += 999999984;
	पूर्ण

	set_normalized_बारpec64(ts, s, ns);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_समय_लो64);

पूर्णांक ocelot_ptp_समय_रखो64(काष्ठा ptp_घड़ी_info *ptp,
			 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा ocelot *ocelot = container_of(ptp, काष्ठा ocelot, ptp_info);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);

	val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);
	val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK | PTP_PIN_CFG_DOM);
	val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_IDLE);

	ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);

	ocelot_ग_लिखो_rix(ocelot, lower_32_bits(ts->tv_sec), PTP_PIN_TOD_SEC_LSB,
			 TOD_ACC_PIN);
	ocelot_ग_लिखो_rix(ocelot, upper_32_bits(ts->tv_sec), PTP_PIN_TOD_SEC_MSB,
			 TOD_ACC_PIN);
	ocelot_ग_लिखो_rix(ocelot, ts->tv_nsec, PTP_PIN_TOD_NSEC, TOD_ACC_PIN);

	val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);
	val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK | PTP_PIN_CFG_DOM);
	val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_LOAD);

	ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);

	spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_समय_रखो64);

पूर्णांक ocelot_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	अगर (delta > -(NSEC_PER_SEC / 2) && delta < (NSEC_PER_SEC / 2)) अणु
		काष्ठा ocelot *ocelot = container_of(ptp, काष्ठा ocelot,
						     ptp_info);
		अचिन्हित दीर्घ flags;
		u32 val;

		spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);

		val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);
		val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK |
			 PTP_PIN_CFG_DOM);
		val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_IDLE);

		ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);

		ocelot_ग_लिखो_rix(ocelot, 0, PTP_PIN_TOD_SEC_LSB, TOD_ACC_PIN);
		ocelot_ग_लिखो_rix(ocelot, 0, PTP_PIN_TOD_SEC_MSB, TOD_ACC_PIN);
		ocelot_ग_लिखो_rix(ocelot, delta, PTP_PIN_TOD_NSEC, TOD_ACC_PIN);

		val = ocelot_पढ़ो_rix(ocelot, PTP_PIN_CFG, TOD_ACC_PIN);
		val &= ~(PTP_PIN_CFG_SYNC | PTP_PIN_CFG_ACTION_MASK |
			 PTP_PIN_CFG_DOM);
		val |= PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_DELTA);

		ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, TOD_ACC_PIN);

		spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
	पूर्ण अन्यथा अणु
		/* Fall back using ocelot_ptp_समय_रखो64 which is not exact. */
		काष्ठा बारpec64 ts;
		u64 now;

		ocelot_ptp_समय_लो64(ptp, &ts);

		now = kसमय_प्रकारo_ns(बारpec64_to_kसमय(ts));
		ts = ns_to_बारpec64(now + delta);

		ocelot_ptp_समय_रखो64(ptp, &ts);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_adjसमय);

पूर्णांक ocelot_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा ocelot *ocelot = container_of(ptp, काष्ठा ocelot, ptp_info);
	u32 unit = 0, direction = 0;
	अचिन्हित दीर्घ flags;
	u64 adj = 0;

	spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);

	अगर (!scaled_ppm)
		जाओ disable_adj;

	अगर (scaled_ppm < 0) अणु
		direction = PTP_CFG_CLK_ADJ_CFG_सूची;
		scaled_ppm = -scaled_ppm;
	पूर्ण

	adj = PSEC_PER_SEC << 16;
	करो_भाग(adj, scaled_ppm);
	करो_भाग(adj, 1000);

	/* If the adjusपंचांगent value is too large, use ns instead */
	अगर (adj >= (1L << 30)) अणु
		unit = PTP_CFG_CLK_ADJ_FREQ_NS;
		करो_भाग(adj, 1000);
	पूर्ण

	/* Still too big */
	अगर (adj >= (1L << 30))
		जाओ disable_adj;

	ocelot_ग_लिखो(ocelot, unit | adj, PTP_CLK_CFG_ADJ_FREQ);
	ocelot_ग_लिखो(ocelot, PTP_CFG_CLK_ADJ_CFG_ENA | direction,
		     PTP_CLK_CFG_ADJ_CFG);

	spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
	वापस 0;

disable_adj:
	ocelot_ग_लिखो(ocelot, 0, PTP_CLK_CFG_ADJ_CFG);

	spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_adjfine);

पूर्णांक ocelot_ptp_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
		      क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	चयन (func) अणु
	हाल PTP_PF_NONE:
	हाल PTP_PF_PEROUT:
		अवरोध;
	हाल PTP_PF_EXTTS:
	हाल PTP_PF_PHYSYNC:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_verअगरy);

पूर्णांक ocelot_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
		      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा ocelot *ocelot = container_of(ptp, काष्ठा ocelot, ptp_info);
	काष्ठा बारpec64 ts_phase, ts_period;
	क्रमागत ocelot_ptp_pins ptp_pin;
	अचिन्हित दीर्घ flags;
	bool pps = false;
	पूर्णांक pin = -1;
	s64 wf_high;
	s64 wf_low;
	u32 val;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags & ~(PTP_PEROUT_DUTY_CYCLE |
					 PTP_PEROUT_PHASE))
			वापस -EOPNOTSUPP;

		pin = ptp_find_pin(ocelot->ptp_घड़ी, PTP_PF_PEROUT,
				   rq->perout.index);
		अगर (pin == 0)
			ptp_pin = PTP_PIN_0;
		अन्यथा अगर (pin == 1)
			ptp_pin = PTP_PIN_1;
		अन्यथा अगर (pin == 2)
			ptp_pin = PTP_PIN_2;
		अन्यथा अगर (pin == 3)
			ptp_pin = PTP_PIN_3;
		अन्यथा
			वापस -EBUSY;

		ts_period.tv_sec = rq->perout.period.sec;
		ts_period.tv_nsec = rq->perout.period.nsec;

		अगर (ts_period.tv_sec == 1 && ts_period.tv_nsec == 0)
			pps = true;

		/* Handle turning off */
		अगर (!on) अणु
			spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);
			val = PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_IDLE);
			ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, ptp_pin);
			spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
			अवरोध;
		पूर्ण

		अगर (rq->perout.flags & PTP_PEROUT_PHASE) अणु
			ts_phase.tv_sec = rq->perout.phase.sec;
			ts_phase.tv_nsec = rq->perout.phase.nsec;
		पूर्ण अन्यथा अणु
			/* Compatibility */
			ts_phase.tv_sec = rq->perout.start.sec;
			ts_phase.tv_nsec = rq->perout.start.nsec;
		पूर्ण
		अगर (ts_phase.tv_sec || (ts_phase.tv_nsec && !pps)) अणु
			dev_warn(ocelot->dev,
				 "Absolute start time not supported!\n");
			dev_warn(ocelot->dev,
				 "Accept nsec for PPS phase adjustment, otherwise start time should be 0 0.\n");
			वापस -EINVAL;
		पूर्ण

		/* Calculate waveक्रमm high and low बार */
		अगर (rq->perout.flags & PTP_PEROUT_DUTY_CYCLE) अणु
			काष्ठा बारpec64 ts_on;

			ts_on.tv_sec = rq->perout.on.sec;
			ts_on.tv_nsec = rq->perout.on.nsec;

			wf_high = बारpec64_to_ns(&ts_on);
		पूर्ण अन्यथा अणु
			अगर (pps) अणु
				wf_high = 1000;
			पूर्ण अन्यथा अणु
				wf_high = बारpec64_to_ns(&ts_period);
				wf_high = भाग_s64(wf_high, 2);
			पूर्ण
		पूर्ण

		wf_low = बारpec64_to_ns(&ts_period);
		wf_low -= wf_high;

		/* Handle PPS request */
		अगर (pps) अणु
			spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);
			ocelot_ग_लिखो_rix(ocelot, ts_phase.tv_nsec,
					 PTP_PIN_WF_LOW_PERIOD, ptp_pin);
			ocelot_ग_लिखो_rix(ocelot, wf_high,
					 PTP_PIN_WF_HIGH_PERIOD, ptp_pin);
			val = PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_CLOCK);
			val |= PTP_PIN_CFG_SYNC;
			ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, ptp_pin);
			spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
			अवरोध;
		पूर्ण

		/* Handle periodic घड़ी */
		अगर (wf_high > 0x3fffffff || wf_high <= 0x6)
			वापस -EINVAL;
		अगर (wf_low > 0x3fffffff || wf_low <= 0x6)
			वापस -EINVAL;

		spin_lock_irqsave(&ocelot->ptp_घड़ी_lock, flags);
		ocelot_ग_लिखो_rix(ocelot, wf_low, PTP_PIN_WF_LOW_PERIOD,
				 ptp_pin);
		ocelot_ग_लिखो_rix(ocelot, wf_high, PTP_PIN_WF_HIGH_PERIOD,
				 ptp_pin);
		val = PTP_PIN_CFG_ACTION(PTP_PIN_ACTION_CLOCK);
		ocelot_ग_लिखो_rix(ocelot, val, PTP_PIN_CFG, ptp_pin);
		spin_unlock_irqrestore(&ocelot->ptp_घड़ी_lock, flags);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_ptp_enable);

पूर्णांक ocelot_init_बारtamp(काष्ठा ocelot *ocelot,
			  स्थिर काष्ठा ptp_घड़ी_info *info)
अणु
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	पूर्णांक i;

	ocelot->ptp_info = *info;

	क्रम (i = 0; i < OCELOT_PTP_PINS_NUM; i++) अणु
		काष्ठा ptp_pin_desc *p = &ocelot->ptp_pins[i];

		snम_लिखो(p->name, माप(p->name), "switch_1588_dat%d", i);
		p->index = i;
		p->func = PTP_PF_NONE;
	पूर्ण

	ocelot->ptp_info.pin_config = &ocelot->ptp_pins[0];

	ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&ocelot->ptp_info, ocelot->dev);
	अगर (IS_ERR(ptp_घड़ी))
		वापस PTR_ERR(ptp_घड़ी);
	/* Check अगर PHC support is missing at the configuration level */
	अगर (!ptp_घड़ी)
		वापस 0;

	ocelot->ptp_घड़ी = ptp_घड़ी;

	ocelot_ग_लिखो(ocelot, SYS_PTP_CFG_PTP_STAMP_WID(30), SYS_PTP_CFG);
	ocelot_ग_लिखो(ocelot, 0xffffffff, ANA_TABLES_PTP_ID_LOW);
	ocelot_ग_लिखो(ocelot, 0xffffffff, ANA_TABLES_PTP_ID_HIGH);

	ocelot_ग_लिखो(ocelot, PTP_CFG_MISC_PTP_EN, PTP_CFG_MISC);

	/* There is no device reconfiguration, PTP Rx stamping is always
	 * enabled.
	 */
	ocelot->hwtstamp_config.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_init_बारtamp);

पूर्णांक ocelot_deinit_बारtamp(काष्ठा ocelot *ocelot)
अणु
	अगर (ocelot->ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(ocelot->ptp_घड़ी);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_deinit_बारtamp);
