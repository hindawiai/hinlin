<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fast Ethernet Controller (ENET) PTP driver क्रम MX6x.
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy.h>
#समावेश <linux/fec.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_net.h>

#समावेश "fec.h"

/* FEC 1588 रेजिस्टर bits */
#घोषणा FEC_T_CTRL_SLAVE                0x00002000
#घोषणा FEC_T_CTRL_CAPTURE              0x00000800
#घोषणा FEC_T_CTRL_RESTART              0x00000200
#घोषणा FEC_T_CTRL_PERIOD_RST           0x00000030
#घोषणा FEC_T_CTRL_PERIOD_EN		0x00000010
#घोषणा FEC_T_CTRL_ENABLE               0x00000001

#घोषणा FEC_T_INC_MASK                  0x0000007f
#घोषणा FEC_T_INC_OFFSET                0
#घोषणा FEC_T_INC_CORR_MASK             0x00007f00
#घोषणा FEC_T_INC_CORR_OFFSET           8

#घोषणा FEC_T_CTRL_PINPER		0x00000080
#घोषणा FEC_T_TF0_MASK			0x00000001
#घोषणा FEC_T_TF0_OFFSET		0
#घोषणा FEC_T_TF1_MASK			0x00000002
#घोषणा FEC_T_TF1_OFFSET		1
#घोषणा FEC_T_TF2_MASK			0x00000004
#घोषणा FEC_T_TF2_OFFSET		2
#घोषणा FEC_T_TF3_MASK			0x00000008
#घोषणा FEC_T_TF3_OFFSET		3
#घोषणा FEC_T_TDRE_MASK			0x00000001
#घोषणा FEC_T_TDRE_OFFSET		0
#घोषणा FEC_T_TMODE_MASK		0x0000003C
#घोषणा FEC_T_TMODE_OFFSET		2
#घोषणा FEC_T_TIE_MASK			0x00000040
#घोषणा FEC_T_TIE_OFFSET		6
#घोषणा FEC_T_TF_MASK			0x00000080
#घोषणा FEC_T_TF_OFFSET			7

#घोषणा FEC_ATIME_CTRL		0x400
#घोषणा FEC_ATIME		0x404
#घोषणा FEC_ATIME_EVT_OFFSET	0x408
#घोषणा FEC_ATIME_EVT_PERIOD	0x40c
#घोषणा FEC_ATIME_CORR		0x410
#घोषणा FEC_ATIME_INC		0x414
#घोषणा FEC_TS_TIMESTAMP	0x418

#घोषणा FEC_TGSR		0x604
#घोषणा FEC_TCSR(n)		(0x608 + n * 0x08)
#घोषणा FEC_TCCR(n)		(0x60C + n * 0x08)
#घोषणा MAX_TIMER_CHANNEL	3
#घोषणा FEC_TMODE_TOGGLE	0x05
#घोषणा FEC_HIGH_PULSE		0x0F

#घोषणा FEC_CC_MULT	(1 << 31)
#घोषणा FEC_COUNTER_PERIOD	(1 << 31)
#घोषणा PPS_OUPUT_RELOAD_PERIOD	NSEC_PER_SEC
#घोषणा FEC_CHANNLE_0		0
#घोषणा DEFAULT_PPS_CHANNEL	FEC_CHANNLE_0

/**
 * fec_ptp_enable_pps
 * @fep: the fec_enet_निजी काष्ठाure handle
 * @enable: enable the channel pps output
 *
 * This function enble the PPS ouput on the समयr channel.
 */
अटल पूर्णांक fec_ptp_enable_pps(काष्ठा fec_enet_निजी *fep, uपूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 val, tempval;
	काष्ठा बारpec64 ts;
	u64 ns;
	val = 0;

	अगर (fep->pps_enable == enable)
		वापस 0;

	fep->pps_channel = DEFAULT_PPS_CHANNEL;
	fep->reload_period = PPS_OUPUT_RELOAD_PERIOD;

	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);

	अगर (enable) अणु
		/* clear capture or output compare पूर्णांकerrupt status अगर have.
		 */
		ग_लिखोl(FEC_T_TF_MASK, fep->hwp + FEC_TCSR(fep->pps_channel));

		/* It is recommended to द्विगुन check the TMODE field in the
		 * TCSR रेजिस्टर to be cleared beक्रमe the first compare counter
		 * is written पूर्णांकo TCCR रेजिस्टर. Just add a द्विगुन check.
		 */
		val = पढ़ोl(fep->hwp + FEC_TCSR(fep->pps_channel));
		करो अणु
			val &= ~(FEC_T_TMODE_MASK);
			ग_लिखोl(val, fep->hwp + FEC_TCSR(fep->pps_channel));
			val = पढ़ोl(fep->hwp + FEC_TCSR(fep->pps_channel));
		पूर्ण जबतक (val & FEC_T_TMODE_MASK);

		/* Dummy पढ़ो counter to update the counter */
		समयcounter_पढ़ो(&fep->tc);
		/* We want to find the first compare event in the next
		 * second poपूर्णांक. So we need to know what the ptp समय
		 * is now and how many nanoseconds is ahead to get next second.
		 * The reमुख्यing nanosecond ahead beक्रमe the next second would be
		 * NSEC_PER_SEC - ts.tv_nsec. Add the reमुख्यing nanoseconds
		 * to current समयr would be next second.
		 */
		tempval = पढ़ोl(fep->hwp + FEC_ATIME_CTRL);
		tempval |= FEC_T_CTRL_CAPTURE;
		ग_लिखोl(tempval, fep->hwp + FEC_ATIME_CTRL);

		tempval = पढ़ोl(fep->hwp + FEC_ATIME);
		/* Convert the ptp local counter to 1588 बारtamp */
		ns = समयcounter_cyc2समय(&fep->tc, tempval);
		ts = ns_to_बारpec64(ns);

		/* The tempval is  less than 3 seconds, and  so val is less than
		 * 4 seconds. No overflow क्रम 32bit calculation.
		 */
		val = NSEC_PER_SEC - (u32)ts.tv_nsec + tempval;

		/* Need to consider the situation that the current समय is
		 * very बंद to the second poपूर्णांक, which means NSEC_PER_SEC
		 * - ts.tv_nsec is बंद to be zero(For example 20ns); Since the समयr
		 * is still running when we calculate the first compare event, it is
		 * possible that the reमुख्यing nanoseonds run out beक्रमe the compare
		 * counter is calculated and written पूर्णांकo TCCR रेजिस्टर. To aव्योम
		 * this possibility, we will set the compare event to be the next
		 * of next second. The current setting is 31-bit समयr and wrap
		 * around over 2 seconds. So it is okay to set the next of next
		 * seond क्रम the समयr.
		 */
		val += NSEC_PER_SEC;

		/* We add (2 * NSEC_PER_SEC - (u32)ts.tv_nsec) to current
		 * ptp counter, which maybe cause 32-bit wrap. Since the
		 * (NSEC_PER_SEC - (u32)ts.tv_nsec) is less than 2 second.
		 * We can ensure the wrap will not cause issue. If the offset
		 * is bigger than fep->cc.mask would be a error.
		 */
		val &= fep->cc.mask;
		ग_लिखोl(val, fep->hwp + FEC_TCCR(fep->pps_channel));

		/* Calculate the second the compare event बारtamp */
		fep->next_counter = (val + fep->reload_period) & fep->cc.mask;

		/* * Enable compare event when overflow */
		val = पढ़ोl(fep->hwp + FEC_ATIME_CTRL);
		val |= FEC_T_CTRL_PINPER;
		ग_लिखोl(val, fep->hwp + FEC_ATIME_CTRL);

		/* Compare channel setting. */
		val = पढ़ोl(fep->hwp + FEC_TCSR(fep->pps_channel));
		val |= (1 << FEC_T_TF_OFFSET | 1 << FEC_T_TIE_OFFSET);
		val &= ~(1 << FEC_T_TDRE_OFFSET);
		val &= ~(FEC_T_TMODE_MASK);
		val |= (FEC_HIGH_PULSE << FEC_T_TMODE_OFFSET);
		ग_लिखोl(val, fep->hwp + FEC_TCSR(fep->pps_channel));

		/* Write the second compare event बारtamp and calculate
		 * the third बारtamp. Refer the TCCR रेजिस्टर detail in the spec.
		 */
		ग_लिखोl(fep->next_counter, fep->hwp + FEC_TCCR(fep->pps_channel));
		fep->next_counter = (fep->next_counter + fep->reload_period) & fep->cc.mask;
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, fep->hwp + FEC_TCSR(fep->pps_channel));
	पूर्ण

	fep->pps_enable = enable;
	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

/**
 * fec_ptp_पढ़ो - पढ़ो raw cycle counter (to be used by समय counter)
 * @cc: the cyclecounter काष्ठाure
 *
 * this function पढ़ोs the cyclecounter रेजिस्टरs and is called by the
 * cyclecounter काष्ठाure used to स्थिरruct a ns counter from the
 * arbitrary fixed poपूर्णांक रेजिस्टरs
 */
अटल u64 fec_ptp_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा fec_enet_निजी *fep =
		container_of(cc, काष्ठा fec_enet_निजी, cc);
	u32 tempval;

	tempval = पढ़ोl(fep->hwp + FEC_ATIME_CTRL);
	tempval |= FEC_T_CTRL_CAPTURE;
	ग_लिखोl(tempval, fep->hwp + FEC_ATIME_CTRL);

	अगर (fep->quirks & FEC_QUIRK_BUG_CAPTURE)
		udelay(1);

	वापस पढ़ोl(fep->hwp + FEC_ATIME);
पूर्ण

/**
 * fec_ptp_start_cyclecounter - create the cycle counter from hw
 * @ndev: network device
 *
 * this function initializes the समयcounter and cyclecounter
 * काष्ठाures क्रम use in generated a ns counter from the arbitrary
 * fixed poपूर्णांक cycles रेजिस्टरs in the hardware.
 */
व्योम fec_ptp_start_cyclecounter(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;
	पूर्णांक inc;

	inc = 1000000000 / fep->cycle_speed;

	/* grab the ptp lock */
	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);

	/* 1ns counter */
	ग_लिखोl(inc << FEC_T_INC_OFFSET, fep->hwp + FEC_ATIME_INC);

	/* use 31-bit समयr counter */
	ग_लिखोl(FEC_COUNTER_PERIOD, fep->hwp + FEC_ATIME_EVT_PERIOD);

	ग_लिखोl(FEC_T_CTRL_ENABLE | FEC_T_CTRL_PERIOD_RST,
		fep->hwp + FEC_ATIME_CTRL);

	स_रखो(&fep->cc, 0, माप(fep->cc));
	fep->cc.पढ़ो = fec_ptp_पढ़ो;
	fep->cc.mask = CLOCKSOURCE_MASK(31);
	fep->cc.shअगरt = 31;
	fep->cc.mult = FEC_CC_MULT;

	/* reset the ns समय counter */
	समयcounter_init(&fep->tc, &fep->cc, 0);

	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);
पूर्ण

/**
 * fec_ptp_adjfreq - adjust ptp cycle frequency
 * @ptp: the ptp घड़ी काष्ठाure
 * @ppb: parts per billion adjusपंचांगent from base
 *
 * Adjust the frequency of the ptp cycle counter by the
 * indicated ppb from the base frequency.
 *
 * Because ENET hardware frequency adjust is complex,
 * using software method to करो that.
 */
अटल पूर्णांक fec_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक neg_adj = 0;
	u32 i, पंचांगp;
	u32 corr_inc, corr_period;
	u32 corr_ns;
	u64 lhs, rhs;

	काष्ठा fec_enet_निजी *fep =
	    container_of(ptp, काष्ठा fec_enet_निजी, ptp_caps);

	अगर (ppb == 0)
		वापस 0;

	अगर (ppb < 0) अणु
		ppb = -ppb;
		neg_adj = 1;
	पूर्ण

	/* In theory, corr_inc/corr_period = ppb/NSEC_PER_SEC;
	 * Try to find the corr_inc  between 1 to fep->ptp_inc to
	 * meet adjusपंचांगent requirement.
	 */
	lhs = NSEC_PER_SEC;
	rhs = (u64)ppb * (u64)fep->ptp_inc;
	क्रम (i = 1; i <= fep->ptp_inc; i++) अणु
		अगर (lhs >= rhs) अणु
			corr_inc = i;
			corr_period = भाग_u64(lhs, rhs);
			अवरोध;
		पूर्ण
		lhs += NSEC_PER_SEC;
	पूर्ण
	/* Not found? Set it to high value - द्विगुन speed
	 * correct in every घड़ी step.
	 */
	अगर (i > fep->ptp_inc) अणु
		corr_inc = fep->ptp_inc;
		corr_period = 1;
	पूर्ण

	अगर (neg_adj)
		corr_ns = fep->ptp_inc - corr_inc;
	अन्यथा
		corr_ns = fep->ptp_inc + corr_inc;

	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);

	पंचांगp = पढ़ोl(fep->hwp + FEC_ATIME_INC) & FEC_T_INC_MASK;
	पंचांगp |= corr_ns << FEC_T_INC_CORR_OFFSET;
	ग_लिखोl(पंचांगp, fep->hwp + FEC_ATIME_INC);
	corr_period = corr_period > 1 ? corr_period - 1 : corr_period;
	ग_लिखोl(corr_period, fep->hwp + FEC_ATIME_CORR);
	/* dummy पढ़ो to update the समयr. */
	समयcounter_पढ़ो(&fep->tc);

	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

/**
 * fec_ptp_adjसमय
 * @ptp: the ptp घड़ी काष्ठाure
 * @delta: offset to adjust the cycle counter by
 *
 * adjust the समयr by resetting the समयcounter काष्ठाure.
 */
अटल पूर्णांक fec_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा fec_enet_निजी *fep =
	    container_of(ptp, काष्ठा fec_enet_निजी, ptp_caps);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);
	समयcounter_adjसमय(&fep->tc, delta);
	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);

	वापस 0;
पूर्ण

/**
 * fec_ptp_समय_लो
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 *
 * पढ़ो the समयcounter and वापस the correct value on ns,
 * after converting it पूर्णांकo a काष्ठा बारpec.
 */
अटल पूर्णांक fec_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा fec_enet_निजी *adapter =
	    container_of(ptp, काष्ठा fec_enet_निजी, ptp_caps);
	u64 ns;
	अचिन्हित दीर्घ flags;

	mutex_lock(&adapter->ptp_clk_mutex);
	/* Check the ptp घड़ी */
	अगर (!adapter->ptp_clk_on) अणु
		mutex_unlock(&adapter->ptp_clk_mutex);
		वापस -EINVAL;
	पूर्ण
	spin_lock_irqsave(&adapter->पंचांगreg_lock, flags);
	ns = समयcounter_पढ़ो(&adapter->tc);
	spin_unlock_irqrestore(&adapter->पंचांगreg_lock, flags);
	mutex_unlock(&adapter->ptp_clk_mutex);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/**
 * fec_ptp_समय_रखो
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: the बारpec containing the new समय क्रम the cycle counter
 *
 * reset the समयcounter to use a new base value instead of the kernel
 * wall समयr value.
 */
अटल पूर्णांक fec_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा fec_enet_निजी *fep =
	    container_of(ptp, काष्ठा fec_enet_निजी, ptp_caps);

	u64 ns;
	अचिन्हित दीर्घ flags;
	u32 counter;

	mutex_lock(&fep->ptp_clk_mutex);
	/* Check the ptp घड़ी */
	अगर (!fep->ptp_clk_on) अणु
		mutex_unlock(&fep->ptp_clk_mutex);
		वापस -EINVAL;
	पूर्ण

	ns = बारpec64_to_ns(ts);
	/* Get the समयr value based on बारtamp.
	 * Update the counter with the masked value.
	 */
	counter = ns & fep->cc.mask;

	spin_lock_irqsave(&fep->पंचांगreg_lock, flags);
	ग_लिखोl(counter, fep->hwp + FEC_ATIME);
	समयcounter_init(&fep->tc, &fep->cc, ns);
	spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);
	mutex_unlock(&fep->ptp_clk_mutex);
	वापस 0;
पूर्ण

/**
 * fec_ptp_enable
 * @ptp: the ptp घड़ी काष्ठाure
 * @rq: the requested feature to change
 * @on: whether to enable or disable the feature
 *
 */
अटल पूर्णांक fec_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा fec_enet_निजी *fep =
	    container_of(ptp, काष्ठा fec_enet_निजी, ptp_caps);
	पूर्णांक ret = 0;

	अगर (rq->type == PTP_CLK_REQ_PPS) अणु
		ret = fec_ptp_enable_pps(fep, on);

		वापस ret;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * fec_ptp_disable_hwts - disable hardware समय stamping
 * @ndev: poपूर्णांकer to net_device
 */
व्योम fec_ptp_disable_hwts(काष्ठा net_device *ndev)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	fep->hwts_tx_en = 0;
	fep->hwts_rx_en = 0;
पूर्ण

पूर्णांक fec_ptp_set(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	काष्ठा hwtstamp_config config;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		fep->hwts_tx_en = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		fep->hwts_tx_en = 1;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		fep->hwts_rx_en = 0;
		अवरोध;

	शेष:
		fep->hwts_rx_en = 1;
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
	    -EFAULT : 0;
पूर्ण

पूर्णांक fec_ptp_get(काष्ठा net_device *ndev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	काष्ठा hwtstamp_config config;

	config.flags = 0;
	config.tx_type = fep->hwts_tx_en ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	config.rx_filter = (fep->hwts_rx_en ?
			    HWTSTAMP_FILTER_ALL : HWTSTAMP_FILTER_NONE);

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

/*
 * fec_समय_keep - call समयcounter_पढ़ो every second to aव्योम समयr overrun
 *                 because ENET just support 32bit counter, will समयout in 4s
 */
अटल व्योम fec_समय_keep(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा fec_enet_निजी *fep = container_of(dwork, काष्ठा fec_enet_निजी, समय_keep);
	अचिन्हित दीर्घ flags;

	mutex_lock(&fep->ptp_clk_mutex);
	अगर (fep->ptp_clk_on) अणु
		spin_lock_irqsave(&fep->पंचांगreg_lock, flags);
		समयcounter_पढ़ो(&fep->tc);
		spin_unlock_irqrestore(&fep->पंचांगreg_lock, flags);
	पूर्ण
	mutex_unlock(&fep->ptp_clk_mutex);

	schedule_delayed_work(&fep->समय_keep, HZ);
पूर्ण

/* This function checks the pps event and reloads the समयr compare counter. */
अटल irqवापस_t fec_pps_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	u32 val;
	u8 channel = fep->pps_channel;
	काष्ठा ptp_घड़ी_event event;

	val = पढ़ोl(fep->hwp + FEC_TCSR(channel));
	अगर (val & FEC_T_TF_MASK) अणु
		/* Write the next next compare(not the next according the spec)
		 * value to the रेजिस्टर
		 */
		ग_लिखोl(fep->next_counter, fep->hwp + FEC_TCCR(channel));
		करो अणु
			ग_लिखोl(val, fep->hwp + FEC_TCSR(channel));
		पूर्ण जबतक (पढ़ोl(fep->hwp + FEC_TCSR(channel)) & FEC_T_TF_MASK);

		/* Update the counter; */
		fep->next_counter = (fep->next_counter + fep->reload_period) &
				fep->cc.mask;

		event.type = PTP_CLOCK_PPS;
		ptp_घड़ी_event(fep->ptp_घड़ी, &event);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/**
 * fec_ptp_init
 * @pdev: The FEC network adapter
 * @irq_idx: the पूर्णांकerrupt index
 *
 * This function perक्रमms the required steps क्रम enabling ptp
 * support. If ptp support has alपढ़ोy been loaded it simply calls the
 * cyclecounter init routine and निकासs.
 */

व्योम fec_ptp_init(काष्ठा platक्रमm_device *pdev, पूर्णांक irq_idx)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);
	पूर्णांक irq;
	पूर्णांक ret;

	fep->ptp_caps.owner = THIS_MODULE;
	strlcpy(fep->ptp_caps.name, "fec ptp", माप(fep->ptp_caps.name));

	fep->ptp_caps.max_adj = 250000000;
	fep->ptp_caps.n_alarm = 0;
	fep->ptp_caps.n_ext_ts = 0;
	fep->ptp_caps.n_per_out = 0;
	fep->ptp_caps.n_pins = 0;
	fep->ptp_caps.pps = 1;
	fep->ptp_caps.adjfreq = fec_ptp_adjfreq;
	fep->ptp_caps.adjसमय = fec_ptp_adjसमय;
	fep->ptp_caps.समय_लो64 = fec_ptp_समय_लो;
	fep->ptp_caps.समय_रखो64 = fec_ptp_समय_रखो;
	fep->ptp_caps.enable = fec_ptp_enable;

	fep->cycle_speed = clk_get_rate(fep->clk_ptp);
	अगर (!fep->cycle_speed) अणु
		fep->cycle_speed = NSEC_PER_SEC;
		dev_err(&fep->pdev->dev, "clk_ptp clock rate is zero\n");
	पूर्ण
	fep->ptp_inc = NSEC_PER_SEC / fep->cycle_speed;

	spin_lock_init(&fep->पंचांगreg_lock);

	fec_ptp_start_cyclecounter(ndev);

	INIT_DELAYED_WORK(&fep->समय_keep, fec_समय_keep);

	irq = platक्रमm_get_irq_byname_optional(pdev, "pps");
	अगर (irq < 0)
		irq = platक्रमm_get_irq_optional(pdev, irq_idx);
	/* Failure to get an irq is not fatal,
	 * only the PTP_CLOCK_PPS घड़ी events should stop
	 */
	अगर (irq >= 0) अणु
		ret = devm_request_irq(&pdev->dev, irq, fec_pps_पूर्णांकerrupt,
				       0, pdev->name, ndev);
		अगर (ret < 0)
			dev_warn(&pdev->dev, "request for pps irq failed(%d)\n",
				 ret);
	पूर्ण

	fep->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&fep->ptp_caps, &pdev->dev);
	अगर (IS_ERR(fep->ptp_घड़ी)) अणु
		fep->ptp_घड़ी = शून्य;
		dev_err(&pdev->dev, "ptp_clock_register failed\n");
	पूर्ण

	schedule_delayed_work(&fep->समय_keep, HZ);
पूर्ण

व्योम fec_ptp_stop(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा fec_enet_निजी *fep = netdev_priv(ndev);

	cancel_delayed_work_sync(&fep->समय_keep);
	अगर (fep->ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(fep->ptp_घड़ी);
पूर्ण
