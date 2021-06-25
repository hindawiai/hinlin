<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * 1588 PTP support क्रम Cadence GEM device.
 *
 * Copyright (C) 2017 Cadence Design Systems - https://www.cadence.com
 *
 * Authors: Rafal Ozieblo <rafalo@cadence.com>
 *          Bartosz Folta <bfolta@cadence.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/समय64.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/spinlock.h>

#समावेश "macb.h"

#घोषणा  GEM_PTP_TIMER_NAME "gem-ptp-timer"

अटल काष्ठा macb_dma_desc_ptp *macb_ptp_desc(काष्ठा macb *bp,
					       काष्ठा macb_dma_desc *desc)
अणु
	अगर (bp->hw_dma_cap == HW_DMA_CAP_PTP)
		वापस (काष्ठा macb_dma_desc_ptp *)
				((u8 *)desc + माप(काष्ठा macb_dma_desc));
	अगर (bp->hw_dma_cap == HW_DMA_CAP_64B_PTP)
		वापस (काष्ठा macb_dma_desc_ptp *)
				((u8 *)desc + माप(काष्ठा macb_dma_desc)
				+ माप(काष्ठा macb_dma_desc_64));
	वापस शून्य;
पूर्ण

अटल पूर्णांक gem_tsu_get_समय(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा macb *bp = container_of(ptp, काष्ठा macb, ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	दीर्घ first, second;
	u32 secl, sech;

	spin_lock_irqsave(&bp->tsu_clk_lock, flags);
	first = gem_पढ़ोl(bp, TN);
	secl = gem_पढ़ोl(bp, TSL);
	sech = gem_पढ़ोl(bp, TSH);
	second = gem_पढ़ोl(bp, TN);

	/* test क्रम nsec rollover */
	अगर (first > second) अणु
		/* अगर so, use later पढ़ो & re-पढ़ो seconds
		 * (assume all करोne within 1s)
		 */
		ts->tv_nsec = gem_पढ़ोl(bp, TN);
		secl = gem_पढ़ोl(bp, TSL);
		sech = gem_पढ़ोl(bp, TSH);
	पूर्ण अन्यथा अणु
		ts->tv_nsec = first;
	पूर्ण

	spin_unlock_irqrestore(&bp->tsu_clk_lock, flags);
	ts->tv_sec = (((u64)sech << GEM_TSL_SIZE) | secl)
			& TSU_SEC_MAX_VAL;
	वापस 0;
पूर्ण

अटल पूर्णांक gem_tsu_set_समय(काष्ठा ptp_घड़ी_info *ptp,
			    स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा macb *bp = container_of(ptp, काष्ठा macb, ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u32 ns, sech, secl;

	secl = (u32)ts->tv_sec;
	sech = (ts->tv_sec >> GEM_TSL_SIZE) & ((1 << GEM_TSH_SIZE) - 1);
	ns = ts->tv_nsec;

	spin_lock_irqsave(&bp->tsu_clk_lock, flags);

	/* TSH करोesn't latch the समय and no atomicity! */
	gem_ग_लिखोl(bp, TN, 0); /* clear to aव्योम overflow */
	gem_ग_लिखोl(bp, TSH, sech);
	/* ग_लिखो lower bits 2nd, क्रम synchronized secs update */
	gem_ग_लिखोl(bp, TSL, secl);
	gem_ग_लिखोl(bp, TN, ns);

	spin_unlock_irqrestore(&bp->tsu_clk_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_tsu_incr_set(काष्ठा macb *bp, काष्ठा tsu_incr *incr_spec)
अणु
	अचिन्हित दीर्घ flags;

	/* tsu_समयr_incr रेजिस्टर must be written after
	 * the tsu_समयr_incr_sub_ns रेजिस्टर and the ग_लिखो operation
	 * will cause the value written to the tsu_समयr_incr_sub_ns रेजिस्टर
	 * to take effect.
	 */
	spin_lock_irqsave(&bp->tsu_clk_lock, flags);
	/* RegBit[15:0] = Subns[23:8]; RegBit[31:24] = Subns[7:0] */
	gem_ग_लिखोl(bp, TISUBN, GEM_BF(SUBNSINCRL, incr_spec->sub_ns) |
		   GEM_BF(SUBNSINCRH, (incr_spec->sub_ns >>
			  GEM_SUBNSINCRL_SIZE)));
	gem_ग_लिखोl(bp, TI, GEM_BF(NSINCR, incr_spec->ns));
	spin_unlock_irqrestore(&bp->tsu_clk_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक gem_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा macb *bp = container_of(ptp, काष्ठा macb, ptp_घड़ी_info);
	काष्ठा tsu_incr incr_spec;
	bool neg_adj = false;
	u32 word;
	u64 adj;

	अगर (scaled_ppm < 0) अणु
		neg_adj = true;
		scaled_ppm = -scaled_ppm;
	पूर्ण

	/* Adjusपंचांगent is relative to base frequency */
	incr_spec.sub_ns = bp->tsu_incr.sub_ns;
	incr_spec.ns = bp->tsu_incr.ns;

	/* scaling: unused(8bit) | ns(8bit) | fractions(16bit) */
	word = ((u64)incr_spec.ns << GEM_SUBNSINCR_SIZE) + incr_spec.sub_ns;
	adj = (u64)scaled_ppm * word;
	/* Divide with rounding, equivalent to भग्नing भागiding:
	 * (temp / USEC_PER_SEC) + 0.5
	 */
	adj += (USEC_PER_SEC >> 1);
	adj >>= PPM_FRACTION; /* हटाओ fractions */
	adj = भाग_u64(adj, USEC_PER_SEC);
	adj = neg_adj ? (word - adj) : (word + adj);

	incr_spec.ns = (adj >> GEM_SUBNSINCR_SIZE)
			& ((1 << GEM_NSINCR_SIZE) - 1);
	incr_spec.sub_ns = adj & ((1 << GEM_SUBNSINCR_SIZE) - 1);
	gem_tsu_incr_set(bp, &incr_spec);
	वापस 0;
पूर्ण

अटल पूर्णांक gem_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा macb *bp = container_of(ptp, काष्ठा macb, ptp_घड़ी_info);
	काष्ठा बारpec64 now, then = ns_to_बारpec64(delta);
	u32 adj, sign = 0;

	अगर (delta < 0) अणु
		sign = 1;
		delta = -delta;
	पूर्ण

	अगर (delta > TSU_NSEC_MAX_VAL) अणु
		gem_tsu_get_समय(&bp->ptp_घड़ी_info, &now);
		now = बारpec64_add(now, then);

		gem_tsu_set_समय(&bp->ptp_घड़ी_info,
				 (स्थिर काष्ठा बारpec64 *)&now);
	पूर्ण अन्यथा अणु
		adj = (sign << GEM_ADDSUB_OFFSET) | delta;

		gem_ग_लिखोl(bp, TA, adj);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gem_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info gem_ptp_caps_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.name		= GEM_PTP_TIMER_NAME,
	.max_adj	= 0,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= gem_ptp_adjfine,
	.adjसमय	= gem_ptp_adjसमय,
	.समय_लो64	= gem_tsu_get_समय,
	.समय_रखो64	= gem_tsu_set_समय,
	.enable		= gem_ptp_enable,
पूर्ण;

अटल व्योम gem_ptp_init_समयr(काष्ठा macb *bp)
अणु
	u32 rem = 0;
	u64 adj;

	bp->tsu_incr.ns = भाग_u64_rem(NSEC_PER_SEC, bp->tsu_rate, &rem);
	अगर (rem) अणु
		adj = rem;
		adj <<= GEM_SUBNSINCR_SIZE;
		bp->tsu_incr.sub_ns = भाग_u64(adj, bp->tsu_rate);
	पूर्ण अन्यथा अणु
		bp->tsu_incr.sub_ns = 0;
	पूर्ण
पूर्ण

अटल व्योम gem_ptp_init_tsu(काष्ठा macb *bp)
अणु
	काष्ठा बारpec64 ts;

	/* 1. get current प्रणाली समय */
	ts = ns_to_बारpec64(kसमय_प्रकारo_ns(kसमय_get_real()));

	/* 2. set ptp समयr */
	gem_tsu_set_समय(&bp->ptp_घड़ी_info, &ts);

	/* 3. set PTP समयr increment value to BASE_INCREMENT */
	gem_tsu_incr_set(bp, &bp->tsu_incr);

	gem_ग_लिखोl(bp, TA, 0);
पूर्ण

अटल व्योम gem_ptp_clear_समयr(काष्ठा macb *bp)
अणु
	bp->tsu_incr.sub_ns = 0;
	bp->tsu_incr.ns = 0;

	gem_ग_लिखोl(bp, TISUBN, GEM_BF(SUBNSINCR, 0));
	gem_ग_लिखोl(bp, TI, GEM_BF(NSINCR, 0));
	gem_ग_लिखोl(bp, TA, 0);
पूर्ण

अटल पूर्णांक gem_hw_बारtamp(काष्ठा macb *bp, u32 dma_desc_ts_1,
			    u32 dma_desc_ts_2, काष्ठा बारpec64 *ts)
अणु
	काष्ठा बारpec64 tsu;

	ts->tv_sec = (GEM_BFEXT(DMA_SECH, dma_desc_ts_2) << GEM_DMA_SECL_SIZE) |
			GEM_BFEXT(DMA_SECL, dma_desc_ts_1);
	ts->tv_nsec = GEM_BFEXT(DMA_NSEC, dma_desc_ts_1);

	/* TSU overlapping workaround
	 * The बारtamp only contains lower few bits of seconds,
	 * so add value from 1588 समयr
	 */
	gem_tsu_get_समय(&bp->ptp_घड़ी_info, &tsu);

	/* If the top bit is set in the बारtamp,
	 * but not in 1588 समयr, it has rolled over,
	 * so subtract max size
	 */
	अगर ((ts->tv_sec & (GEM_DMA_SEC_TOP >> 1)) &&
	    !(tsu.tv_sec & (GEM_DMA_SEC_TOP >> 1)))
		ts->tv_sec -= GEM_DMA_SEC_TOP;

	ts->tv_sec += ((~GEM_DMA_SEC_MASK) & tsu.tv_sec);

	वापस 0;
पूर्ण

व्योम gem_ptp_rxstamp(काष्ठा macb *bp, काष्ठा sk_buff *skb,
		     काष्ठा macb_dma_desc *desc)
अणु
	काष्ठा skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	काष्ठा macb_dma_desc_ptp *desc_ptp;
	काष्ठा बारpec64 ts;

	अगर (GEM_BFEXT(DMA_RXVALID, desc->addr)) अणु
		desc_ptp = macb_ptp_desc(bp, desc);
		gem_hw_बारtamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);
		स_रखो(shhwtstamps, 0, माप(काष्ठा skb_shared_hwtstamps));
		shhwtstamps->hwtstamp = kसमय_set(ts.tv_sec, ts.tv_nsec);
	पूर्ण
पूर्ण

अटल व्योम gem_tstamp_tx(काष्ठा macb *bp, काष्ठा sk_buff *skb,
			  काष्ठा macb_dma_desc_ptp *desc_ptp)
अणु
	काष्ठा skb_shared_hwtstamps shhwtstamps;
	काष्ठा बारpec64 ts;

	gem_hw_बारtamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);
	स_रखो(&shhwtstamps, 0, माप(shhwtstamps));
	shhwtstamps.hwtstamp = kसमय_set(ts.tv_sec, ts.tv_nsec);
	skb_tstamp_tx(skb, &shhwtstamps);
पूर्ण

पूर्णांक gem_ptp_txstamp(काष्ठा macb_queue *queue, काष्ठा sk_buff *skb,
		    काष्ठा macb_dma_desc *desc)
अणु
	अचिन्हित दीर्घ tail = READ_ONCE(queue->tx_ts_tail);
	अचिन्हित दीर्घ head = queue->tx_ts_head;
	काष्ठा macb_dma_desc_ptp *desc_ptp;
	काष्ठा gem_tx_ts *tx_बारtamp;

	अगर (!GEM_BFEXT(DMA_TXVALID, desc->ctrl))
		वापस -EINVAL;

	अगर (CIRC_SPACE(head, tail, PTP_TS_BUFFER_SIZE) == 0)
		वापस -ENOMEM;

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	desc_ptp = macb_ptp_desc(queue->bp, desc);
	tx_बारtamp = &queue->tx_बारtamps[head];
	tx_बारtamp->skb = skb;
	/* ensure ts_1/ts_2 is loaded after ctrl (TX_USED check) */
	dma_rmb();
	tx_बारtamp->desc_ptp.ts_1 = desc_ptp->ts_1;
	tx_बारtamp->desc_ptp.ts_2 = desc_ptp->ts_2;
	/* move head */
	smp_store_release(&queue->tx_ts_head,
			  (head + 1) & (PTP_TS_BUFFER_SIZE - 1));

	schedule_work(&queue->tx_ts_task);
	वापस 0;
पूर्ण

अटल व्योम gem_tx_बारtamp_flush(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा macb_queue *queue =
			container_of(work, काष्ठा macb_queue, tx_ts_task);
	अचिन्हित दीर्घ head, tail;
	काष्ठा gem_tx_ts *tx_ts;

	/* take current head */
	head = smp_load_acquire(&queue->tx_ts_head);
	tail = queue->tx_ts_tail;

	जबतक (CIRC_CNT(head, tail, PTP_TS_BUFFER_SIZE)) अणु
		tx_ts = &queue->tx_बारtamps[tail];
		gem_tstamp_tx(queue->bp, tx_ts->skb, &tx_ts->desc_ptp);
		/* cleanup */
		dev_kमुक्त_skb_any(tx_ts->skb);
		/* हटाओ old tail */
		smp_store_release(&queue->tx_ts_tail,
				  (tail + 1) & (PTP_TS_BUFFER_SIZE - 1));
		tail = queue->tx_ts_tail;
	पूर्ण
पूर्ण

व्योम gem_ptp_init(काष्ठा net_device *dev)
अणु
	काष्ठा macb *bp = netdev_priv(dev);
	काष्ठा macb_queue *queue;
	अचिन्हित पूर्णांक q;

	bp->ptp_घड़ी_info = gem_ptp_caps_ढाँचा;

	/* nominal frequency and maximum adjusपंचांगent in ppb */
	bp->tsu_rate = bp->ptp_info->get_tsu_rate(bp);
	bp->ptp_घड़ी_info.max_adj = bp->ptp_info->get_ptp_max_adj();
	gem_ptp_init_समयr(bp);
	bp->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&bp->ptp_घड़ी_info, &dev->dev);
	अगर (IS_ERR(bp->ptp_घड़ी)) अणु
		pr_err("ptp clock register failed: %ld\n",
			PTR_ERR(bp->ptp_घड़ी));
		bp->ptp_घड़ी = शून्य;
		वापस;
	पूर्ण अन्यथा अगर (bp->ptp_घड़ी == शून्य) अणु
		pr_err("ptp clock register failed\n");
		वापस;
	पूर्ण

	spin_lock_init(&bp->tsu_clk_lock);
	क्रम (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) अणु
		queue->tx_ts_head = 0;
		queue->tx_ts_tail = 0;
		INIT_WORK(&queue->tx_ts_task, gem_tx_बारtamp_flush);
	पूर्ण

	gem_ptp_init_tsu(bp);

	dev_info(&bp->pdev->dev, "%s ptp clock registered.\n",
		 GEM_PTP_TIMER_NAME);
पूर्ण

व्योम gem_ptp_हटाओ(काष्ठा net_device *ndev)
अणु
	काष्ठा macb *bp = netdev_priv(ndev);

	अगर (bp->ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(bp->ptp_घड़ी);

	gem_ptp_clear_समयr(bp);

	dev_info(&bp->pdev->dev, "%s ptp clock unregistered.\n",
		 GEM_PTP_TIMER_NAME);
पूर्ण

अटल पूर्णांक gem_ptp_set_ts_mode(काष्ठा macb *bp,
			       क्रमागत macb_bd_control tx_bd_control,
			       क्रमागत macb_bd_control rx_bd_control)
अणु
	gem_ग_लिखोl(bp, TXBDCTRL, GEM_BF(TXTSMODE, tx_bd_control));
	gem_ग_लिखोl(bp, RXBDCTRL, GEM_BF(RXTSMODE, rx_bd_control));

	वापस 0;
पूर्ण

पूर्णांक gem_get_hwtst(काष्ठा net_device *dev, काष्ठा अगरreq *rq)
अणु
	काष्ठा hwtstamp_config *tstamp_config;
	काष्ठा macb *bp = netdev_priv(dev);

	tstamp_config = &bp->tstamp_config;
	अगर ((bp->hw_dma_cap & HW_DMA_CAP_PTP) == 0)
		वापस -EOPNOTSUPP;

	अगर (copy_to_user(rq->अगरr_data, tstamp_config, माप(*tstamp_config)))
		वापस -EFAULT;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक gem_ptp_set_one_step_sync(काष्ठा macb *bp, u8 enable)
अणु
	u32 reg_val;

	reg_val = macb_पढ़ोl(bp, NCR);

	अगर (enable)
		macb_ग_लिखोl(bp, NCR, reg_val | MACB_BIT(OSSMODE));
	अन्यथा
		macb_ग_लिखोl(bp, NCR, reg_val & ~MACB_BIT(OSSMODE));

	वापस 0;
पूर्ण

पूर्णांक gem_set_hwtst(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	क्रमागत macb_bd_control tx_bd_control = TSTAMP_DISABLED;
	क्रमागत macb_bd_control rx_bd_control = TSTAMP_DISABLED;
	काष्ठा hwtstamp_config *tstamp_config;
	काष्ठा macb *bp = netdev_priv(dev);
	u32 regval;

	tstamp_config = &bp->tstamp_config;
	अगर ((bp->hw_dma_cap & HW_DMA_CAP_PTP) == 0)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(tstamp_config, अगरr->अगरr_data,
			   माप(*tstamp_config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (tstamp_config->flags)
		वापस -EINVAL;

	चयन (tstamp_config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		अगर (gem_ptp_set_one_step_sync(bp, 1) != 0)
			वापस -दुस्फल;
		fallthrough;
	हाल HWTSTAMP_TX_ON:
		tx_bd_control = TSTAMP_ALL_FRAMES;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (tstamp_config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
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
		rx_bd_control =  TSTAMP_ALL_PTP_FRAMES;
		tstamp_config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		regval = macb_पढ़ोl(bp, NCR);
		macb_ग_लिखोl(bp, NCR, (regval | MACB_BIT(SRTSM)));
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_ALL:
		rx_bd_control = TSTAMP_ALL_FRAMES;
		tstamp_config->rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		tstamp_config->rx_filter = HWTSTAMP_FILTER_NONE;
		वापस -दुस्फल;
	पूर्ण

	अगर (gem_ptp_set_ts_mode(bp, tx_bd_control, rx_bd_control) != 0)
		वापस -दुस्फल;

	अगर (copy_to_user(अगरr->अगरr_data, tstamp_config, माप(*tstamp_config)))
		वापस -EFAULT;
	अन्यथा
		वापस 0;
पूर्ण

