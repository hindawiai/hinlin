<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch PTP support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 National Instruments
 *      Erik Hons <erik.hons@ni.com>
 *      Bअक्रमon Streअगरf <bअक्रमon.streअगरf@ni.com>
 *      Dane Wagner <dane.wagner@ni.com>
 */

#समावेश "chip.h"
#समावेश "global2.h"
#समावेश "hwtstamp.h"
#समावेश "ptp.h"

#घोषणा MV88E6XXX_MAX_ADJ_PPB	1000000

/* Family MV88E6250:
 * Raw बारtamps are in units of 10-ns घड़ी periods.
 *
 * clkadj = scaled_ppm * 10*2^28 / (10^6 * 2^16)
 * simplअगरies to
 * clkadj = scaled_ppm * 2^7 / 5^5
 */
#घोषणा MV88E6250_CC_SHIFT	28
#घोषणा MV88E6250_CC_MULT	(10 << MV88E6250_CC_SHIFT)
#घोषणा MV88E6250_CC_MULT_NUM	(1 << 7)
#घोषणा MV88E6250_CC_MULT_DEM	3125ULL

/* Other families:
 * Raw बारtamps are in units of 8-ns घड़ी periods.
 *
 * clkadj = scaled_ppm * 8*2^28 / (10^6 * 2^16)
 * simplअगरies to
 * clkadj = scaled_ppm * 2^9 / 5^6
 */
#घोषणा MV88E6XXX_CC_SHIFT	28
#घोषणा MV88E6XXX_CC_MULT	(8 << MV88E6XXX_CC_SHIFT)
#घोषणा MV88E6XXX_CC_MULT_NUM	(1 << 9)
#घोषणा MV88E6XXX_CC_MULT_DEM	15625ULL

#घोषणा TAI_EVENT_WORK_INTERVAL msecs_to_jअगरfies(100)

#घोषणा cc_to_chip(cc) container_of(cc, काष्ठा mv88e6xxx_chip, tstamp_cc)
#घोषणा dw_overflow_to_chip(dw) container_of(dw, काष्ठा mv88e6xxx_chip, \
					     overflow_work)
#घोषणा dw_tai_event_to_chip(dw) container_of(dw, काष्ठा mv88e6xxx_chip, \
					      tai_event_work)

अटल पूर्णांक mv88e6xxx_tai_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr,
			      u16 *data, पूर्णांक len)
अणु
	अगर (!chip->info->ops->avb_ops->tai_पढ़ो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->tai_पढ़ो(chip, addr, data, len);
पूर्ण

अटल पूर्णांक mv88e6xxx_tai_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, u16 data)
अणु
	अगर (!chip->info->ops->avb_ops->tai_ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->avb_ops->tai_ग_लिखो(chip, addr, data);
पूर्ण

/* TODO: places where this are called should be using pinctrl */
अटल पूर्णांक mv88e6352_set_gpio_func(काष्ठा mv88e6xxx_chip *chip, पूर्णांक pin,
				   पूर्णांक func, पूर्णांक input)
अणु
	पूर्णांक err;

	अगर (!chip->info->ops->gpio_ops)
		वापस -EOPNOTSUPP;

	err = chip->info->ops->gpio_ops->set_dir(chip, pin, input);
	अगर (err)
		वापस err;

	वापस chip->info->ops->gpio_ops->set_pctl(chip, pin, func);
पूर्ण

अटल u64 mv88e6352_ptp_घड़ी_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mv88e6xxx_chip *chip = cc_to_chip(cc);
	u16 phc_समय[2];
	पूर्णांक err;

	err = mv88e6xxx_tai_पढ़ो(chip, MV88E6XXX_TAI_TIME_LO, phc_समय,
				 ARRAY_SIZE(phc_समय));
	अगर (err)
		वापस 0;
	अन्यथा
		वापस ((u32)phc_समय[1] << 16) | phc_समय[0];
पूर्ण

अटल u64 mv88e6165_ptp_घड़ी_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mv88e6xxx_chip *chip = cc_to_chip(cc);
	u16 phc_समय[2];
	पूर्णांक err;

	err = mv88e6xxx_tai_पढ़ो(chip, MV88E6XXX_PTP_GC_TIME_LO, phc_समय,
				 ARRAY_SIZE(phc_समय));
	अगर (err)
		वापस 0;
	अन्यथा
		वापस ((u32)phc_समय[1] << 16) | phc_समय[0];
पूर्ण

/* mv88e6352_config_eventcap - configure TAI event capture
 * @event: PTP_CLOCK_PPS (पूर्णांकernal) or PTP_CLOCK_EXTTS (बाह्यal)
 * @rising: zero क्रम falling-edge trigger, अन्यथा rising-edge trigger
 *
 * This will also reset the capture sequence counter.
 */
अटल पूर्णांक mv88e6352_config_eventcap(काष्ठा mv88e6xxx_chip *chip, पूर्णांक event,
				     पूर्णांक rising)
अणु
	u16 global_config;
	u16 cap_config;
	पूर्णांक err;

	chip->evcap_config = MV88E6XXX_TAI_CFG_CAP_OVERWRITE |
			     MV88E6XXX_TAI_CFG_CAP_CTR_START;
	अगर (!rising)
		chip->evcap_config |= MV88E6XXX_TAI_CFG_EVREQ_FALLING;

	global_config = (chip->evcap_config | chip->trig_config);
	err = mv88e6xxx_tai_ग_लिखो(chip, MV88E6XXX_TAI_CFG, global_config);
	अगर (err)
		वापस err;

	अगर (event == PTP_CLOCK_PPS) अणु
		cap_config = MV88E6XXX_TAI_EVENT_STATUS_CAP_TRIG;
	पूर्ण अन्यथा अगर (event == PTP_CLOCK_EXTTS) अणु
		/* अगर STATUS_CAP_TRIG is unset we capture PTP_EVREQ events */
		cap_config = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Write the capture config; this also clears the capture counter */
	err = mv88e6xxx_tai_ग_लिखो(chip, MV88E6XXX_TAI_EVENT_STATUS,
				  cap_config);

	वापस err;
पूर्ण

अटल व्योम mv88e6352_tai_event_work(काष्ठा work_काष्ठा *ugly)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(ugly);
	काष्ठा mv88e6xxx_chip *chip = dw_tai_event_to_chip(dw);
	काष्ठा ptp_घड़ी_event ev;
	u16 status[4];
	u32 raw_ts;
	पूर्णांक err;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_tai_पढ़ो(chip, MV88E6XXX_TAI_EVENT_STATUS,
				 status, ARRAY_SIZE(status));
	mv88e6xxx_reg_unlock(chip);

	अगर (err) अणु
		dev_err(chip->dev, "failed to read TAI status register\n");
		वापस;
	पूर्ण
	अगर (status[0] & MV88E6XXX_TAI_EVENT_STATUS_ERROR) अणु
		dev_warn(chip->dev, "missed event capture\n");
		वापस;
	पूर्ण
	अगर (!(status[0] & MV88E6XXX_TAI_EVENT_STATUS_VALID))
		जाओ out;

	raw_ts = ((u32)status[2] << 16) | status[1];

	/* Clear the valid bit so the next बारtamp can come in */
	status[0] &= ~MV88E6XXX_TAI_EVENT_STATUS_VALID;
	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_tai_ग_लिखो(chip, MV88E6XXX_TAI_EVENT_STATUS, status[0]);
	mv88e6xxx_reg_unlock(chip);

	/* This is an बाह्यal बारtamp */
	ev.type = PTP_CLOCK_EXTTS;

	/* We only have one बारtamping channel. */
	ev.index = 0;
	mv88e6xxx_reg_lock(chip);
	ev.बारtamp = समयcounter_cyc2समय(&chip->tstamp_tc, raw_ts);
	mv88e6xxx_reg_unlock(chip);

	ptp_घड़ी_event(chip->ptp_घड़ी, &ev);
out:
	schedule_delayed_work(&chip->tai_event_work, TAI_EVENT_WORK_INTERVAL);
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	पूर्णांक neg_adj = 0;
	u32 dअगरf, mult;
	u64 adj;

	अगर (scaled_ppm < 0) अणु
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण

	mult = ptp_ops->cc_mult;
	adj = ptp_ops->cc_mult_num;
	adj *= scaled_ppm;
	dअगरf = भाग_u64(adj, ptp_ops->cc_mult_dem);

	mv88e6xxx_reg_lock(chip);

	समयcounter_पढ़ो(&chip->tstamp_tc);
	chip->tstamp_cc.mult = neg_adj ? mult - dअगरf : mult + dअगरf;

	mv88e6xxx_reg_unlock(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);

	mv88e6xxx_reg_lock(chip);
	समयcounter_adjसमय(&chip->tstamp_tc, delta);
	mv88e6xxx_reg_unlock(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा बारpec64 *ts)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	u64 ns;

	mv88e6xxx_reg_lock(chip);
	ns = समयcounter_पढ़ो(&chip->tstamp_tc);
	mv88e6xxx_reg_unlock(chip);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
				 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	u64 ns;

	ns = बारpec64_to_ns(ts);

	mv88e6xxx_reg_lock(chip);
	समयcounter_init(&chip->tstamp_tc, &chip->tstamp_cc, ns);
	mv88e6xxx_reg_unlock(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6352_ptp_enable_extts(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	पूर्णांक rising = (rq->extts.flags & PTP_RISING_EDGE);
	पूर्णांक func;
	पूर्णांक pin;
	पूर्णांक err;

	/* Reject requests with unsupported flags */
	अगर (rq->extts.flags & ~(PTP_ENABLE_FEATURE |
				PTP_RISING_EDGE |
				PTP_FALLING_EDGE |
				PTP_STRICT_FLAGS))
		वापस -EOPNOTSUPP;

	/* Reject requests to enable समय stamping on both edges. */
	अगर ((rq->extts.flags & PTP_STRICT_FLAGS) &&
	    (rq->extts.flags & PTP_ENABLE_FEATURE) &&
	    (rq->extts.flags & PTP_EXTTS_EDGES) == PTP_EXTTS_EDGES)
		वापस -EOPNOTSUPP;

	pin = ptp_find_pin(chip->ptp_घड़ी, PTP_PF_EXTTS, rq->extts.index);

	अगर (pin < 0)
		वापस -EBUSY;

	mv88e6xxx_reg_lock(chip);

	अगर (on) अणु
		func = MV88E6352_G2_SCRATCH_GPIO_PCTL_EVREQ;

		err = mv88e6352_set_gpio_func(chip, pin, func, true);
		अगर (err)
			जाओ out;

		schedule_delayed_work(&chip->tai_event_work,
				      TAI_EVENT_WORK_INTERVAL);

		err = mv88e6352_config_eventcap(chip, PTP_CLOCK_EXTTS, rising);
	पूर्ण अन्यथा अणु
		func = MV88E6352_G2_SCRATCH_GPIO_PCTL_GPIO;

		err = mv88e6352_set_gpio_func(chip, pin, func, true);

		cancel_delayed_work_sync(&chip->tai_event_work);
	पूर्ण

out:
	mv88e6xxx_reg_unlock(chip);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6352_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा mv88e6xxx_chip *chip = ptp_to_chip(ptp);

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस mv88e6352_ptp_enable_extts(chip, rq, on);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6352_ptp_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
				क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	चयन (func) अणु
	हाल PTP_PF_NONE:
	हाल PTP_PF_EXTTS:
		अवरोध;
	हाल PTP_PF_PEROUT:
	हाल PTP_PF_PHYSYNC:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6165_ptp_ops = अणु
	.घड़ी_पढ़ो = mv88e6165_ptp_घड़ी_पढ़ो,
	.global_enable = mv88e6165_global_enable,
	.global_disable = mv88e6165_global_disable,
	.arr0_sts_reg = MV88E6165_PORT_PTP_ARR0_STS,
	.arr1_sts_reg = MV88E6165_PORT_PTP_ARR1_STS,
	.dep_sts_reg = MV88E6165_PORT_PTP_DEP_STS,
	.rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ),
	.cc_shअगरt = MV88E6XXX_CC_SHIFT,
	.cc_mult = MV88E6XXX_CC_MULT,
	.cc_mult_num = MV88E6XXX_CC_MULT_NUM,
	.cc_mult_dem = MV88E6XXX_CC_MULT_DEM,
पूर्ण;

स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6250_ptp_ops = अणु
	.घड़ी_पढ़ो = mv88e6352_ptp_घड़ी_पढ़ो,
	.ptp_enable = mv88e6352_ptp_enable,
	.ptp_verअगरy = mv88e6352_ptp_verअगरy,
	.event_work = mv88e6352_tai_event_work,
	.port_enable = mv88e6352_hwtstamp_port_enable,
	.port_disable = mv88e6352_hwtstamp_port_disable,
	.n_ext_ts = 1,
	.arr0_sts_reg = MV88E6XXX_PORT_PTP_ARR0_STS,
	.arr1_sts_reg = MV88E6XXX_PORT_PTP_ARR1_STS,
	.dep_sts_reg = MV88E6XXX_PORT_PTP_DEP_STS,
	.rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ),
	.cc_shअगरt = MV88E6250_CC_SHIFT,
	.cc_mult = MV88E6250_CC_MULT,
	.cc_mult_num = MV88E6250_CC_MULT_NUM,
	.cc_mult_dem = MV88E6250_CC_MULT_DEM,
पूर्ण;

स्थिर काष्ठा mv88e6xxx_ptp_ops mv88e6352_ptp_ops = अणु
	.घड़ी_पढ़ो = mv88e6352_ptp_घड़ी_पढ़ो,
	.ptp_enable = mv88e6352_ptp_enable,
	.ptp_verअगरy = mv88e6352_ptp_verअगरy,
	.event_work = mv88e6352_tai_event_work,
	.port_enable = mv88e6352_hwtstamp_port_enable,
	.port_disable = mv88e6352_hwtstamp_port_disable,
	.n_ext_ts = 1,
	.arr0_sts_reg = MV88E6XXX_PORT_PTP_ARR0_STS,
	.arr1_sts_reg = MV88E6XXX_PORT_PTP_ARR1_STS,
	.dep_sts_reg = MV88E6XXX_PORT_PTP_DEP_STS,
	.rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
		(1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ),
	.cc_shअगरt = MV88E6XXX_CC_SHIFT,
	.cc_mult = MV88E6XXX_CC_MULT,
	.cc_mult_num = MV88E6XXX_CC_MULT_NUM,
	.cc_mult_dem = MV88E6XXX_CC_MULT_DEM,
पूर्ण;

अटल u64 mv88e6xxx_ptp_घड़ी_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा mv88e6xxx_chip *chip = cc_to_chip(cc);

	अगर (chip->info->ops->ptp_ops->घड़ी_पढ़ो)
		वापस chip->info->ops->ptp_ops->घड़ी_पढ़ो(cc);

	वापस 0;
पूर्ण

/* With a 125MHz input घड़ी, the 32-bit बारtamp counter overflows in ~34.3
 * seconds; this task क्रमces periodic पढ़ोs so that we करोn't miss any.
 */
#घोषणा MV88E6XXX_TAI_OVERFLOW_PERIOD (HZ * 16)
अटल व्योम mv88e6xxx_ptp_overflow_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा mv88e6xxx_chip *chip = dw_overflow_to_chip(dw);
	काष्ठा बारpec64 ts;

	mv88e6xxx_ptp_समय_लो(&chip->ptp_घड़ी_info, &ts);

	schedule_delayed_work(&chip->overflow_work,
			      MV88E6XXX_TAI_OVERFLOW_PERIOD);
पूर्ण

पूर्णांक mv88e6xxx_ptp_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	पूर्णांक i;

	/* Set up the cycle counter */
	स_रखो(&chip->tstamp_cc, 0, माप(chip->tstamp_cc));
	chip->tstamp_cc.पढ़ो	= mv88e6xxx_ptp_घड़ी_पढ़ो;
	chip->tstamp_cc.mask	= CYCLECOUNTER_MASK(32);
	chip->tstamp_cc.mult	= ptp_ops->cc_mult;
	chip->tstamp_cc.shअगरt	= ptp_ops->cc_shअगरt;

	समयcounter_init(&chip->tstamp_tc, &chip->tstamp_cc,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	INIT_DELAYED_WORK(&chip->overflow_work, mv88e6xxx_ptp_overflow_check);
	अगर (ptp_ops->event_work)
		INIT_DELAYED_WORK(&chip->tai_event_work, ptp_ops->event_work);

	chip->ptp_घड़ी_info.owner = THIS_MODULE;
	snम_लिखो(chip->ptp_घड़ी_info.name, माप(chip->ptp_घड़ी_info.name),
		 "%s", dev_name(chip->dev));

	chip->ptp_घड़ी_info.n_ext_ts	= ptp_ops->n_ext_ts;
	chip->ptp_घड़ी_info.n_per_out	= 0;
	chip->ptp_घड़ी_info.n_pins	= mv88e6xxx_num_gpio(chip);
	chip->ptp_घड़ी_info.pps	= 0;

	क्रम (i = 0; i < chip->ptp_घड़ी_info.n_pins; ++i) अणु
		काष्ठा ptp_pin_desc *ppd = &chip->pin_config[i];

		snम_लिखो(ppd->name, माप(ppd->name), "mv88e6xxx_gpio%d", i);
		ppd->index = i;
		ppd->func = PTP_PF_NONE;
	पूर्ण
	chip->ptp_घड़ी_info.pin_config = chip->pin_config;

	chip->ptp_घड़ी_info.max_adj    = MV88E6XXX_MAX_ADJ_PPB;
	chip->ptp_घड़ी_info.adjfine	= mv88e6xxx_ptp_adjfine;
	chip->ptp_घड़ी_info.adjसमय	= mv88e6xxx_ptp_adjसमय;
	chip->ptp_घड़ी_info.समय_लो64	= mv88e6xxx_ptp_समय_लो;
	chip->ptp_घड़ी_info.समय_रखो64	= mv88e6xxx_ptp_समय_रखो;
	chip->ptp_घड़ी_info.enable	= ptp_ops->ptp_enable;
	chip->ptp_घड़ी_info.verअगरy	= ptp_ops->ptp_verअगरy;
	chip->ptp_घड़ी_info.करो_aux_work = mv88e6xxx_hwtstamp_work;

	chip->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&chip->ptp_घड़ी_info, chip->dev);
	अगर (IS_ERR(chip->ptp_घड़ी))
		वापस PTR_ERR(chip->ptp_घड़ी);

	schedule_delayed_work(&chip->overflow_work,
			      MV88E6XXX_TAI_OVERFLOW_PERIOD);

	वापस 0;
पूर्ण

व्योम mv88e6xxx_ptp_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	अगर (chip->ptp_घड़ी) अणु
		cancel_delayed_work_sync(&chip->overflow_work);
		अगर (chip->info->ops->ptp_ops->event_work)
			cancel_delayed_work_sync(&chip->tai_event_work);

		ptp_घड़ी_unरेजिस्टर(chip->ptp_घड़ी);
		chip->ptp_घड़ी = शून्य;
	पूर्ण
पूर्ण
