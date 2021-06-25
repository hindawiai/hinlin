<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_ptp.c:
 * Definition of functions क्रम Linux PTP support.
 */

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीsource.h>

#समावेश "aq_nic.h"
#समावेश "aq_ptp.h"
#समावेश "aq_ring.h"
#समावेश "aq_phy.h"
#समावेश "aq_filters.h"

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)

#घोषणा AQ_PTP_TX_TIMEOUT        (HZ *  10)

#घोषणा POLL_SYNC_TIMER_MS 15

क्रमागत ptp_speed_offsets अणु
	ptp_offset_idx_10 = 0,
	ptp_offset_idx_100,
	ptp_offset_idx_1000,
	ptp_offset_idx_2500,
	ptp_offset_idx_5000,
	ptp_offset_idx_10000,
पूर्ण;

काष्ठा ptp_skb_ring अणु
	काष्ठा sk_buff **buff;
	spinlock_t lock;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
पूर्ण;

काष्ठा ptp_tx_समयout अणु
	spinlock_t lock;
	bool active;
	अचिन्हित दीर्घ tx_start;
पूर्ण;

काष्ठा aq_ptp_s अणु
	काष्ठा aq_nic_s *aq_nic;
	काष्ठा hwtstamp_config hwtstamp_config;
	spinlock_t ptp_lock;
	spinlock_t ptp_ring_lock;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_info;

	atomic_t offset_egress;
	atomic_t offset_ingress;

	काष्ठा aq_ring_param_s ptp_ring_param;

	काष्ठा ptp_tx_समयout ptp_tx_समयout;

	अचिन्हित पूर्णांक idx_vector;
	काष्ठा napi_काष्ठा napi;

	काष्ठा aq_ring_s ptp_tx;
	काष्ठा aq_ring_s ptp_rx;
	काष्ठा aq_ring_s hwts_rx;

	काष्ठा ptp_skb_ring skb_ring;

	काष्ठा aq_rx_filter_l3l4 udp_filter;
	काष्ठा aq_rx_filter_l2 eth_type_filter;

	काष्ठा delayed_work poll_sync;
	u32 poll_समयout_ms;

	bool extts_pin_enabled;
	u64 last_sync1588_ts;

	bool a1_ptp;
पूर्ण;

काष्ठा ptp_पंचांग_offset अणु
	अचिन्हित पूर्णांक mbps;
	पूर्णांक egress;
	पूर्णांक ingress;
पूर्ण;

अटल काष्ठा ptp_पंचांग_offset ptp_offset[6];

व्योम aq_ptp_पंचांग_offset_set(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक mbps)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	पूर्णांक i, egress, ingress;

	अगर (!aq_ptp)
		वापस;

	egress = 0;
	ingress = 0;

	क्रम (i = 0; i < ARRAY_SIZE(ptp_offset); i++) अणु
		अगर (mbps == ptp_offset[i].mbps) अणु
			egress = ptp_offset[i].egress;
			ingress = ptp_offset[i].ingress;
			अवरोध;
		पूर्ण
	पूर्ण

	atomic_set(&aq_ptp->offset_egress, egress);
	atomic_set(&aq_ptp->offset_ingress, ingress);
पूर्ण

अटल पूर्णांक __aq_ptp_skb_put(काष्ठा ptp_skb_ring *ring, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक next_head = (ring->head + 1) % ring->size;

	अगर (next_head == ring->tail)
		वापस -ENOMEM;

	ring->buff[ring->head] = skb_get(skb);
	ring->head = next_head;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ptp_skb_put(काष्ठा ptp_skb_ring *ring, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&ring->lock, flags);
	ret = __aq_ptp_skb_put(ring, skb);
	spin_unlock_irqrestore(&ring->lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *__aq_ptp_skb_get(काष्ठा ptp_skb_ring *ring)
अणु
	काष्ठा sk_buff *skb;

	अगर (ring->tail == ring->head)
		वापस शून्य;

	skb = ring->buff[ring->tail];
	ring->tail = (ring->tail + 1) % ring->size;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *aq_ptp_skb_get(काष्ठा ptp_skb_ring *ring)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;

	spin_lock_irqsave(&ring->lock, flags);
	skb = __aq_ptp_skb_get(ring);
	spin_unlock_irqrestore(&ring->lock, flags);

	वापस skb;
पूर्ण

अटल अचिन्हित पूर्णांक aq_ptp_skb_buf_len(काष्ठा ptp_skb_ring *ring)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक len;

	spin_lock_irqsave(&ring->lock, flags);
	len = (ring->head >= ring->tail) ?
	ring->head - ring->tail :
	ring->size - ring->tail + ring->head;
	spin_unlock_irqrestore(&ring->lock, flags);

	वापस len;
पूर्ण

अटल पूर्णांक aq_ptp_skb_ring_init(काष्ठा ptp_skb_ring *ring, अचिन्हित पूर्णांक size)
अणु
	काष्ठा sk_buff **buff = kदो_स्मृति(माप(*buff) * size, GFP_KERNEL);

	अगर (!buff)
		वापस -ENOMEM;

	spin_lock_init(&ring->lock);

	ring->buff = buff;
	ring->size = size;
	ring->head = 0;
	ring->tail = 0;

	वापस 0;
पूर्ण

अटल व्योम aq_ptp_skb_ring_clean(काष्ठा ptp_skb_ring *ring)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = aq_ptp_skb_get(ring)) != शून्य)
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल व्योम aq_ptp_skb_ring_release(काष्ठा ptp_skb_ring *ring)
अणु
	अगर (ring->buff) अणु
		aq_ptp_skb_ring_clean(ring);
		kमुक्त(ring->buff);
		ring->buff = शून्य;
	पूर्ण
पूर्ण

अटल व्योम aq_ptp_tx_समयout_init(काष्ठा ptp_tx_समयout *समयout)
अणु
	spin_lock_init(&समयout->lock);
	समयout->active = false;
पूर्ण

अटल व्योम aq_ptp_tx_समयout_start(काष्ठा aq_ptp_s *aq_ptp)
अणु
	काष्ठा ptp_tx_समयout *समयout = &aq_ptp->ptp_tx_समयout;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&समयout->lock, flags);
	समयout->active = true;
	समयout->tx_start = jअगरfies;
	spin_unlock_irqrestore(&समयout->lock, flags);
पूर्ण

अटल व्योम aq_ptp_tx_समयout_update(काष्ठा aq_ptp_s *aq_ptp)
अणु
	अगर (!aq_ptp_skb_buf_len(&aq_ptp->skb_ring)) अणु
		काष्ठा ptp_tx_समयout *समयout = &aq_ptp->ptp_tx_समयout;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&समयout->lock, flags);
		समयout->active = false;
		spin_unlock_irqrestore(&समयout->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम aq_ptp_tx_समयout_check(काष्ठा aq_ptp_s *aq_ptp)
अणु
	काष्ठा ptp_tx_समयout *समयout = &aq_ptp->ptp_tx_समयout;
	अचिन्हित दीर्घ flags;
	bool समयout_flag;

	समयout_flag = false;

	spin_lock_irqsave(&समयout->lock, flags);
	अगर (समयout->active) अणु
		समयout_flag = समय_is_beक्रमe_jअगरfies(समयout->tx_start +
						      AQ_PTP_TX_TIMEOUT);
		/* reset active flag अगर समयout detected */
		अगर (समयout_flag)
			समयout->active = false;
	पूर्ण
	spin_unlock_irqrestore(&समयout->lock, flags);

	अगर (समयout_flag) अणु
		aq_ptp_skb_ring_clean(&aq_ptp->skb_ring);
		netdev_err(aq_ptp->aq_nic->ndev,
			   "PTP Timeout. Clearing Tx Timestamp SKBs\n");
	पूर्ण
पूर्ण

/* aq_ptp_adjfine
 * @ptp: the ptp घड़ी काष्ठाure
 * @ppb: parts per billion adjusपंचांगent from base
 *
 * adjust the frequency of the ptp cycle counter by the
 * indicated ppb from the base frequency.
 */
अटल पूर्णांक aq_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;

	mutex_lock(&aq_nic->fwreq_mutex);
	aq_nic->aq_hw_ops->hw_adj_घड़ी_freq(aq_nic->aq_hw,
					     scaled_ppm_to_ppb(scaled_ppm));
	mutex_unlock(&aq_nic->fwreq_mutex);

	वापस 0;
पूर्ण

/* aq_ptp_adjसमय
 * @ptp: the ptp घड़ी काष्ठाure
 * @delta: offset to adjust the cycle counter by
 *
 * adjust the समयr by resetting the समयcounter काष्ठाure.
 */
अटल पूर्णांक aq_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&aq_ptp->ptp_lock, flags);
	aq_nic->aq_hw_ops->hw_adj_sys_घड़ी(aq_nic->aq_hw, delta);
	spin_unlock_irqrestore(&aq_ptp->ptp_lock, flags);

	वापस 0;
पूर्ण

/* aq_ptp_समय_लो
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 *
 * पढ़ो the समयcounter and वापस the correct value on ns,
 * after converting it पूर्णांकo a काष्ठा बारpec.
 */
अटल पूर्णांक aq_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	अचिन्हित दीर्घ flags;
	u64 ns;

	spin_lock_irqsave(&aq_ptp->ptp_lock, flags);
	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &ns);
	spin_unlock_irqrestore(&aq_ptp->ptp_lock, flags);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

/* aq_ptp_समय_रखो
 * @ptp: the ptp घड़ी काष्ठाure
 * @ts: the बारpec containing the new समय क्रम the cycle counter
 *
 * reset the समयcounter to use a new base value instead of the kernel
 * wall समयr value.
 */
अटल पूर्णांक aq_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			  स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	अचिन्हित दीर्घ flags;
	u64 ns = बारpec64_to_ns(ts);
	u64 now;

	spin_lock_irqsave(&aq_ptp->ptp_lock, flags);
	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &now);
	aq_nic->aq_hw_ops->hw_adj_sys_घड़ी(aq_nic->aq_hw, (s64)ns - (s64)now);

	spin_unlock_irqrestore(&aq_ptp->ptp_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम aq_ptp_convert_to_hwtstamp(काष्ठा aq_ptp_s *aq_ptp,
				       काष्ठा skb_shared_hwtstamps *hwtstamp,
				       u64 बारtamp)
अणु
	स_रखो(hwtstamp, 0, माप(*hwtstamp));
	hwtstamp->hwtstamp = ns_to_kसमय(बारtamp);
पूर्ण

अटल पूर्णांक aq_ptp_hw_pin_conf(काष्ठा aq_nic_s *aq_nic, u32 pin_index, u64 start,
			      u64 period)
अणु
	अगर (period)
		netdev_dbg(aq_nic->ndev,
			   "Enable GPIO %d pulsing, start time %llu, period %u\n",
			   pin_index, start, (u32)period);
	अन्यथा
		netdev_dbg(aq_nic->ndev,
			   "Disable GPIO %d pulsing, start time %llu, period %u\n",
			   pin_index, start, (u32)period);

	/* Notअगरy hardware of request to being sending pulses.
	 * If period is ZERO then pulsen is disabled.
	 */
	mutex_lock(&aq_nic->fwreq_mutex);
	aq_nic->aq_hw_ops->hw_gpio_pulse(aq_nic->aq_hw, pin_index,
					 start, (u32)period);
	mutex_unlock(&aq_nic->fwreq_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ptp_perout_pin_configure(काष्ठा ptp_घड़ी_info *ptp,
				       काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा ptp_घड़ी_प्रकारime *t = &rq->perout.period;
	काष्ठा ptp_घड़ी_प्रकारime *s = &rq->perout.start;
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 start, period;
	u32 pin_index = rq->perout.index;

	/* verअगरy the request channel is there */
	अगर (pin_index >= ptp->n_per_out)
		वापस -EINVAL;

	/* we cannot support periods greater
	 * than 4 seconds due to reg limit
	 */
	अगर (t->sec > 4 || t->sec < 0)
		वापस -दुस्फल;

	/* convert to अचिन्हित 64b ns,
	 * verअगरy we can put it in a 32b रेजिस्टर
	 */
	period = on ? t->sec * NSEC_PER_SEC + t->nsec : 0;

	/* verअगरy the value is in range supported by hardware */
	अगर (period > U32_MAX)
		वापस -दुस्फल;
	/* convert to अचिन्हित 64b ns */
	/* TODO convert to AQ समय */
	start = on ? s->sec * NSEC_PER_SEC + s->nsec : 0;

	aq_ptp_hw_pin_conf(aq_nic, pin_index, start, period);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ptp_pps_pin_configure(काष्ठा ptp_घड़ी_info *ptp,
				    काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 start, period;
	u32 pin_index = 0;
	u32 rest = 0;

	/* verअगरy the request channel is there */
	अगर (pin_index >= ptp->n_per_out)
		वापस -EINVAL;

	aq_nic->aq_hw_ops->hw_get_ptp_ts(aq_nic->aq_hw, &start);
	भाग_u64_rem(start, NSEC_PER_SEC, &rest);
	period = on ? NSEC_PER_SEC : 0; /* PPS - pulse per second */
	start = on ? start - rest + NSEC_PER_SEC *
		(rest > 990000000LL ? 2 : 1) : 0;

	aq_ptp_hw_pin_conf(aq_nic, pin_index, start, period);

	वापस 0;
पूर्ण

अटल व्योम aq_ptp_extts_pin_ctrl(काष्ठा aq_ptp_s *aq_ptp)
अणु
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u32 enable = aq_ptp->extts_pin_enabled;

	अगर (aq_nic->aq_hw_ops->hw_extts_gpio_enable)
		aq_nic->aq_hw_ops->hw_extts_gpio_enable(aq_nic->aq_hw, 0,
							enable);
पूर्ण

अटल पूर्णांक aq_ptp_extts_pin_configure(काष्ठा ptp_घड़ी_info *ptp,
				      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(ptp, काष्ठा aq_ptp_s, ptp_info);

	u32 pin_index = rq->extts.index;

	अगर (pin_index >= ptp->n_ext_ts)
		वापस -EINVAL;

	aq_ptp->extts_pin_enabled = !!on;
	अगर (on) अणु
		aq_ptp->poll_समयout_ms = POLL_SYNC_TIMER_MS;
		cancel_delayed_work_sync(&aq_ptp->poll_sync);
		schedule_delayed_work(&aq_ptp->poll_sync,
				      msecs_to_jअगरfies(aq_ptp->poll_समयout_ms));
	पूर्ण

	aq_ptp_extts_pin_ctrl(aq_ptp);
	वापस 0;
पूर्ण

/* aq_ptp_gpio_feature_enable
 * @ptp: the ptp घड़ी काष्ठाure
 * @rq: the requested feature to change
 * @on: whether to enable or disable the feature
 */
अटल पूर्णांक aq_ptp_gpio_feature_enable(काष्ठा ptp_घड़ी_info *ptp,
				      काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_EXTTS:
		वापस aq_ptp_extts_pin_configure(ptp, rq, on);
	हाल PTP_CLK_REQ_PEROUT:
		वापस aq_ptp_perout_pin_configure(ptp, rq, on);
	हाल PTP_CLK_REQ_PPS:
		वापस aq_ptp_pps_pin_configure(ptp, rq, on);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/* aq_ptp_verअगरy
 * @ptp: the ptp घड़ी काष्ठाure
 * @pin: index of the pin in question
 * @func: the desired function to use
 * @chan: the function channel index to use
 */
अटल पूर्णांक aq_ptp_verअगरy(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
			 क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	/* verअगरy the requested pin is there */
	अगर (!ptp->pin_config || pin >= ptp->n_pins)
		वापस -EINVAL;

	/* enक्रमce locked channels, no changing them */
	अगर (chan != ptp->pin_config[pin].chan)
		वापस -EINVAL;

	/* we want to keep the functions locked as well */
	अगर (func != ptp->pin_config[pin].func)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* aq_ptp_tx_hwtstamp - utility function which checks क्रम TX समय stamp
 * @adapter: the निजी adapter काष्ठा
 *
 * अगर the बारtamp is valid, we convert it पूर्णांकo the समयcounter ns
 * value, then store that result पूर्णांकo the hwtstamps काष्ठाure which
 * is passed up the network stack
 */
व्योम aq_ptp_tx_hwtstamp(काष्ठा aq_nic_s *aq_nic, u64 बारtamp)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	काष्ठा sk_buff *skb = aq_ptp_skb_get(&aq_ptp->skb_ring);
	काष्ठा skb_shared_hwtstamps hwtstamp;

	अगर (!skb) अणु
		netdev_err(aq_nic->ndev, "have timestamp but tx_queues empty\n");
		वापस;
	पूर्ण

	बारtamp += atomic_पढ़ो(&aq_ptp->offset_egress);
	aq_ptp_convert_to_hwtstamp(aq_ptp, &hwtstamp, बारtamp);
	skb_tstamp_tx(skb, &hwtstamp);
	dev_kमुक्त_skb_any(skb);

	aq_ptp_tx_समयout_update(aq_ptp);
पूर्ण

/* aq_ptp_rx_hwtstamp - utility function which checks क्रम RX समय stamp
 * @adapter: poपूर्णांकer to adapter काष्ठा
 * @skb: particular skb to send बारtamp with
 *
 * अगर the बारtamp is valid, we convert it पूर्णांकo the समयcounter ns
 * value, then store that result पूर्णांकo the hwtstamps काष्ठाure which
 * is passed up the network stack
 */
अटल व्योम aq_ptp_rx_hwtstamp(काष्ठा aq_ptp_s *aq_ptp, काष्ठा sk_buff *skb,
			       u64 बारtamp)
अणु
	बारtamp -= atomic_पढ़ो(&aq_ptp->offset_ingress);
	aq_ptp_convert_to_hwtstamp(aq_ptp, skb_hwtstamps(skb), बारtamp);
पूर्ण

व्योम aq_ptp_hwtstamp_config_get(काष्ठा aq_ptp_s *aq_ptp,
				काष्ठा hwtstamp_config *config)
अणु
	*config = aq_ptp->hwtstamp_config;
पूर्ण

अटल व्योम aq_ptp_prepare_filters(काष्ठा aq_ptp_s *aq_ptp)
अणु
	aq_ptp->udp_filter.cmd = HW_ATL_RX_ENABLE_FLTR_L3L4 |
			       HW_ATL_RX_ENABLE_CMP_PROT_L4 |
			       HW_ATL_RX_UDP |
			       HW_ATL_RX_ENABLE_CMP_DEST_PORT_L4 |
			       HW_ATL_RX_HOST << HW_ATL_RX_ACTION_FL3F4_SHIFT |
			       HW_ATL_RX_ENABLE_QUEUE_L3L4 |
			       aq_ptp->ptp_rx.idx << HW_ATL_RX_QUEUE_FL3L4_SHIFT;
	aq_ptp->udp_filter.p_dst = PTP_EV_PORT;

	aq_ptp->eth_type_filter.ethertype = ETH_P_1588;
	aq_ptp->eth_type_filter.queue = aq_ptp->ptp_rx.idx;
पूर्ण

पूर्णांक aq_ptp_hwtstamp_config_set(काष्ठा aq_ptp_s *aq_ptp,
			       काष्ठा hwtstamp_config *config)
अणु
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	स्थिर काष्ठा aq_hw_ops *hw_ops;
	पूर्णांक err = 0;

	hw_ops = aq_nic->aq_hw_ops;
	अगर (config->tx_type == HWTSTAMP_TX_ON ||
	    config->rx_filter == HWTSTAMP_FILTER_PTP_V2_EVENT) अणु
		aq_ptp_prepare_filters(aq_ptp);
		अगर (hw_ops->hw_filter_l3l4_set) अणु
			err = hw_ops->hw_filter_l3l4_set(aq_nic->aq_hw,
							 &aq_ptp->udp_filter);
		पूर्ण
		अगर (!err && hw_ops->hw_filter_l2_set) अणु
			err = hw_ops->hw_filter_l2_set(aq_nic->aq_hw,
						       &aq_ptp->eth_type_filter);
		पूर्ण
		aq_utils_obj_set(&aq_nic->flags, AQ_NIC_PTP_DPATH_UP);
	पूर्ण अन्यथा अणु
		aq_ptp->udp_filter.cmd &= ~HW_ATL_RX_ENABLE_FLTR_L3L4;
		अगर (hw_ops->hw_filter_l3l4_set) अणु
			err = hw_ops->hw_filter_l3l4_set(aq_nic->aq_hw,
							 &aq_ptp->udp_filter);
		पूर्ण
		अगर (!err && hw_ops->hw_filter_l2_clear) अणु
			err = hw_ops->hw_filter_l2_clear(aq_nic->aq_hw,
							&aq_ptp->eth_type_filter);
		पूर्ण
		aq_utils_obj_clear(&aq_nic->flags, AQ_NIC_PTP_DPATH_UP);
	पूर्ण

	अगर (err)
		वापस -EREMOTEIO;

	aq_ptp->hwtstamp_config = *config;

	वापस 0;
पूर्ण

bool aq_ptp_ring(काष्ठा aq_nic_s *aq_nic, काष्ठा aq_ring_s *ring)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस false;

	वापस &aq_ptp->ptp_tx == ring ||
	       &aq_ptp->ptp_rx == ring || &aq_ptp->hwts_rx == ring;
पूर्ण

u16 aq_ptp_extract_ts(काष्ठा aq_nic_s *aq_nic, काष्ठा sk_buff *skb, u8 *p,
		      अचिन्हित पूर्णांक len)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	u64 बारtamp = 0;
	u16 ret = aq_nic->aq_hw_ops->rx_extract_ts(aq_nic->aq_hw,
						   p, len, &बारtamp);

	अगर (ret > 0)
		aq_ptp_rx_hwtstamp(aq_ptp, skb, बारtamp);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_ptp_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा aq_ptp_s *aq_ptp = container_of(napi, काष्ठा aq_ptp_s, napi);
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	bool was_cleaned = false;
	पूर्णांक work_करोne = 0;
	पूर्णांक err;

	/* Processing PTP TX traffic */
	err = aq_nic->aq_hw_ops->hw_ring_tx_head_update(aq_nic->aq_hw,
							&aq_ptp->ptp_tx);
	अगर (err < 0)
		जाओ err_निकास;

	अगर (aq_ptp->ptp_tx.sw_head != aq_ptp->ptp_tx.hw_head) अणु
		aq_ring_tx_clean(&aq_ptp->ptp_tx);

		was_cleaned = true;
	पूर्ण

	/* Processing HW_TIMESTAMP RX traffic */
	err = aq_nic->aq_hw_ops->hw_ring_hwts_rx_receive(aq_nic->aq_hw,
							 &aq_ptp->hwts_rx);
	अगर (err < 0)
		जाओ err_निकास;

	अगर (aq_ptp->hwts_rx.sw_head != aq_ptp->hwts_rx.hw_head) अणु
		aq_ring_hwts_rx_clean(&aq_ptp->hwts_rx, aq_nic);

		err = aq_nic->aq_hw_ops->hw_ring_hwts_rx_fill(aq_nic->aq_hw,
							      &aq_ptp->hwts_rx);
		अगर (err < 0)
			जाओ err_निकास;

		was_cleaned = true;
	पूर्ण

	/* Processing PTP RX traffic */
	err = aq_nic->aq_hw_ops->hw_ring_rx_receive(aq_nic->aq_hw,
						    &aq_ptp->ptp_rx);
	अगर (err < 0)
		जाओ err_निकास;

	अगर (aq_ptp->ptp_rx.sw_head != aq_ptp->ptp_rx.hw_head) अणु
		अचिन्हित पूर्णांक sw_tail_old;

		err = aq_ring_rx_clean(&aq_ptp->ptp_rx, napi, &work_करोne, budget);
		अगर (err < 0)
			जाओ err_निकास;

		sw_tail_old = aq_ptp->ptp_rx.sw_tail;
		err = aq_ring_rx_fill(&aq_ptp->ptp_rx);
		अगर (err < 0)
			जाओ err_निकास;

		err = aq_nic->aq_hw_ops->hw_ring_rx_fill(aq_nic->aq_hw,
							 &aq_ptp->ptp_rx,
							 sw_tail_old);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	अगर (was_cleaned)
		work_करोne = budget;

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		aq_nic->aq_hw_ops->hw_irq_enable(aq_nic->aq_hw,
					BIT_ULL(aq_ptp->ptp_ring_param.vec_idx));
	पूर्ण

err_निकास:
	वापस work_करोne;
पूर्ण

अटल irqवापस_t aq_ptp_isr(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा aq_ptp_s *aq_ptp = निजी;
	पूर्णांक err = 0;

	अगर (!aq_ptp) अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण
	napi_schedule(&aq_ptp->napi);

err_निकास:
	वापस err >= 0 ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

पूर्णांक aq_ptp_xmit(काष्ठा aq_nic_s *aq_nic, काष्ठा sk_buff *skb)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	काष्ठा aq_ring_s *ring = &aq_ptp->ptp_tx;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक err = NETDEV_TX_OK;
	अचिन्हित पूर्णांक frags;

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		जाओ err_निकास;
	पूर्ण

	frags = skb_shinfo(skb)->nr_frags + 1;
	/* Frags cannot be bigger 16KB
	 * because PTP usually works
	 * without Jumbo even in a background
	 */
	अगर (frags > AQ_CFG_SKB_FRAGS_MAX || frags > aq_ring_avail_dx(ring)) अणु
		/* Drop packet because it करोesn't make sence to delay it */
		dev_kमुक्त_skb_any(skb);
		जाओ err_निकास;
	पूर्ण

	err = aq_ptp_skb_put(&aq_ptp->skb_ring, skb);
	अगर (err) अणु
		netdev_err(aq_nic->ndev, "SKB Ring is overflow (%u)!\n",
			   ring->size);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	aq_ptp_tx_समयout_start(aq_ptp);
	skb_tx_बारtamp(skb);

	spin_lock_irqsave(&aq_nic->aq_ptp->ptp_ring_lock, irq_flags);
	frags = aq_nic_map_skb(aq_nic, skb, ring);

	अगर (likely(frags)) अणु
		err = aq_nic->aq_hw_ops->hw_ring_tx_xmit(aq_nic->aq_hw,
						       ring, frags);
		अगर (err >= 0) अणु
			u64_stats_update_begin(&ring->stats.tx.syncp);
			++ring->stats.tx.packets;
			ring->stats.tx.bytes += skb->len;
			u64_stats_update_end(&ring->stats.tx.syncp);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = NETDEV_TX_BUSY;
	पूर्ण
	spin_unlock_irqrestore(&aq_nic->aq_ptp->ptp_ring_lock, irq_flags);

err_निकास:
	वापस err;
पूर्ण

व्योम aq_ptp_service_task(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस;

	aq_ptp_tx_समयout_check(aq_ptp);
पूर्ण

पूर्णांक aq_ptp_irq_alloc(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा pci_dev *pdev = aq_nic->pdev;
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	पूर्णांक err = 0;

	अगर (!aq_ptp)
		वापस 0;

	अगर (pdev->msix_enabled || pdev->msi_enabled) अणु
		err = request_irq(pci_irq_vector(pdev, aq_ptp->idx_vector),
				  aq_ptp_isr, 0, aq_nic->ndev->name, aq_ptp);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण

err_निकास:
	वापस err;
पूर्ण

व्योम aq_ptp_irq_मुक्त(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	काष्ठा pci_dev *pdev = aq_nic->pdev;

	अगर (!aq_ptp)
		वापस;

	मुक्त_irq(pci_irq_vector(pdev, aq_ptp->idx_vector), aq_ptp);
पूर्ण

पूर्णांक aq_ptp_ring_init(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	पूर्णांक err = 0;

	अगर (!aq_ptp)
		वापस 0;

	err = aq_ring_init(&aq_ptp->ptp_tx, ATL_RING_TX);
	अगर (err < 0)
		जाओ err_निकास;
	err = aq_nic->aq_hw_ops->hw_ring_tx_init(aq_nic->aq_hw,
						 &aq_ptp->ptp_tx,
						 &aq_ptp->ptp_ring_param);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_ring_init(&aq_ptp->ptp_rx, ATL_RING_RX);
	अगर (err < 0)
		जाओ err_निकास;
	err = aq_nic->aq_hw_ops->hw_ring_rx_init(aq_nic->aq_hw,
						 &aq_ptp->ptp_rx,
						 &aq_ptp->ptp_ring_param);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_ring_rx_fill(&aq_ptp->ptp_rx);
	अगर (err < 0)
		जाओ err_rx_मुक्त;
	err = aq_nic->aq_hw_ops->hw_ring_rx_fill(aq_nic->aq_hw,
						 &aq_ptp->ptp_rx,
						 0U);
	अगर (err < 0)
		जाओ err_rx_मुक्त;

	err = aq_ring_init(&aq_ptp->hwts_rx, ATL_RING_RX);
	अगर (err < 0)
		जाओ err_rx_मुक्त;
	err = aq_nic->aq_hw_ops->hw_ring_rx_init(aq_nic->aq_hw,
						 &aq_ptp->hwts_rx,
						 &aq_ptp->ptp_ring_param);
	अगर (err < 0)
		जाओ err_निकास;
	err = aq_nic->aq_hw_ops->hw_ring_hwts_rx_fill(aq_nic->aq_hw,
						      &aq_ptp->hwts_rx);
	अगर (err < 0)
		जाओ err_निकास;

	वापस err;

err_rx_मुक्त:
	aq_ring_rx_deinit(&aq_ptp->ptp_rx);
err_निकास:
	वापस err;
पूर्ण

पूर्णांक aq_ptp_ring_start(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	पूर्णांक err = 0;

	अगर (!aq_ptp)
		वापस 0;

	err = aq_nic->aq_hw_ops->hw_ring_tx_start(aq_nic->aq_hw, &aq_ptp->ptp_tx);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_nic->aq_hw_ops->hw_ring_rx_start(aq_nic->aq_hw, &aq_ptp->ptp_rx);
	अगर (err < 0)
		जाओ err_निकास;

	err = aq_nic->aq_hw_ops->hw_ring_rx_start(aq_nic->aq_hw,
						  &aq_ptp->hwts_rx);
	अगर (err < 0)
		जाओ err_निकास;

	napi_enable(&aq_ptp->napi);

err_निकास:
	वापस err;
पूर्ण

व्योम aq_ptp_ring_stop(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस;

	aq_nic->aq_hw_ops->hw_ring_tx_stop(aq_nic->aq_hw, &aq_ptp->ptp_tx);
	aq_nic->aq_hw_ops->hw_ring_rx_stop(aq_nic->aq_hw, &aq_ptp->ptp_rx);

	aq_nic->aq_hw_ops->hw_ring_rx_stop(aq_nic->aq_hw, &aq_ptp->hwts_rx);

	napi_disable(&aq_ptp->napi);
पूर्ण

व्योम aq_ptp_ring_deinit(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp || !aq_ptp->ptp_tx.aq_nic || !aq_ptp->ptp_rx.aq_nic)
		वापस;

	aq_ring_tx_clean(&aq_ptp->ptp_tx);
	aq_ring_rx_deinit(&aq_ptp->ptp_rx);
पूर्ण

पूर्णांक aq_ptp_ring_alloc(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	अचिन्हित पूर्णांक tx_ring_idx, rx_ring_idx;
	काष्ठा aq_ring_s *hwts;
	काष्ठा aq_ring_s *ring;
	पूर्णांक err;

	अगर (!aq_ptp)
		वापस 0;

	tx_ring_idx = aq_ptp_ring_idx(aq_nic->aq_nic_cfg.tc_mode);

	ring = aq_ring_tx_alloc(&aq_ptp->ptp_tx, aq_nic,
				tx_ring_idx, &aq_nic->aq_nic_cfg);
	अगर (!ring) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	rx_ring_idx = aq_ptp_ring_idx(aq_nic->aq_nic_cfg.tc_mode);

	ring = aq_ring_rx_alloc(&aq_ptp->ptp_rx, aq_nic,
				rx_ring_idx, &aq_nic->aq_nic_cfg);
	अगर (!ring) अणु
		err = -ENOMEM;
		जाओ err_निकास_ptp_tx;
	पूर्ण

	hwts = aq_ring_hwts_rx_alloc(&aq_ptp->hwts_rx, aq_nic, PTP_HWST_RING_IDX,
				     aq_nic->aq_nic_cfg.rxds,
				     aq_nic->aq_nic_cfg.aq_hw_caps->rxd_size);
	अगर (!hwts) अणु
		err = -ENOMEM;
		जाओ err_निकास_ptp_rx;
	पूर्ण

	err = aq_ptp_skb_ring_init(&aq_ptp->skb_ring, aq_nic->aq_nic_cfg.rxds);
	अगर (err != 0) अणु
		err = -ENOMEM;
		जाओ err_निकास_hwts_rx;
	पूर्ण

	aq_ptp->ptp_ring_param.vec_idx = aq_ptp->idx_vector;
	aq_ptp->ptp_ring_param.cpu = aq_ptp->ptp_ring_param.vec_idx +
			aq_nic_get_cfg(aq_nic)->aq_rss.base_cpu_number;
	cpumask_set_cpu(aq_ptp->ptp_ring_param.cpu,
			&aq_ptp->ptp_ring_param.affinity_mask);

	वापस 0;

err_निकास_hwts_rx:
	aq_ring_मुक्त(&aq_ptp->hwts_rx);
err_निकास_ptp_rx:
	aq_ring_मुक्त(&aq_ptp->ptp_rx);
err_निकास_ptp_tx:
	aq_ring_मुक्त(&aq_ptp->ptp_tx);
err_निकास:
	वापस err;
पूर्ण

व्योम aq_ptp_ring_मुक्त(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस;

	aq_ring_मुक्त(&aq_ptp->ptp_tx);
	aq_ring_मुक्त(&aq_ptp->ptp_rx);
	aq_ring_मुक्त(&aq_ptp->hwts_rx);

	aq_ptp_skb_ring_release(&aq_ptp->skb_ring);
पूर्ण

#घोषणा MAX_PTP_GPIO_COUNT 4

अटल काष्ठा ptp_घड़ी_info aq_ptp_घड़ी = अणु
	.owner		= THIS_MODULE,
	.name		= "atlantic ptp",
	.max_adj	= 999999999,
	.n_ext_ts	= 0,
	.pps		= 0,
	.adjfine	= aq_ptp_adjfine,
	.adjसमय	= aq_ptp_adjसमय,
	.समय_लो64	= aq_ptp_समय_लो,
	.समय_रखो64	= aq_ptp_समय_रखो,
	.n_per_out	= 0,
	.enable		= aq_ptp_gpio_feature_enable,
	.n_pins		= 0,
	.verअगरy		= aq_ptp_verअगरy,
	.pin_config	= शून्य,
पूर्ण;

#घोषणा ptp_offset_init(__idx, __mbps, __egress, __ingress)   करो अणु \
		ptp_offset[__idx].mbps = (__mbps); \
		ptp_offset[__idx].egress = (__egress); \
		ptp_offset[__idx].ingress = (__ingress); पूर्ण \
		जबतक (0)

अटल व्योम aq_ptp_offset_init_from_fw(स्थिर काष्ठा hw_atl_ptp_offset *offsets)
अणु
	पूर्णांक i;

	/* Load offsets क्रम PTP */
	क्रम (i = 0; i < ARRAY_SIZE(ptp_offset); i++) अणु
		चयन (i) अणु
		/* 100M */
		हाल ptp_offset_idx_100:
			ptp_offset_init(i, 100,
					offsets->egress_100,
					offsets->ingress_100);
			अवरोध;
		/* 1G */
		हाल ptp_offset_idx_1000:
			ptp_offset_init(i, 1000,
					offsets->egress_1000,
					offsets->ingress_1000);
			अवरोध;
		/* 2.5G */
		हाल ptp_offset_idx_2500:
			ptp_offset_init(i, 2500,
					offsets->egress_2500,
					offsets->ingress_2500);
			अवरोध;
		/* 5G */
		हाल ptp_offset_idx_5000:
			ptp_offset_init(i, 5000,
					offsets->egress_5000,
					offsets->ingress_5000);
			अवरोध;
		/* 10G */
		हाल ptp_offset_idx_10000:
			ptp_offset_init(i, 10000,
					offsets->egress_10000,
					offsets->ingress_10000);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम aq_ptp_offset_init(स्थिर काष्ठा hw_atl_ptp_offset *offsets)
अणु
	स_रखो(ptp_offset, 0, माप(ptp_offset));

	aq_ptp_offset_init_from_fw(offsets);
पूर्ण

अटल व्योम aq_ptp_gpio_init(काष्ठा ptp_घड़ी_info *info,
			     काष्ठा hw_atl_info *hw_info)
अणु
	काष्ठा ptp_pin_desc pin_desc[MAX_PTP_GPIO_COUNT];
	u32 extts_pin_cnt = 0;
	u32 out_pin_cnt = 0;
	u32 i;

	स_रखो(pin_desc, 0, माप(pin_desc));

	क्रम (i = 0; i < MAX_PTP_GPIO_COUNT - 1; i++) अणु
		अगर (hw_info->gpio_pin[i] ==
		    (GPIO_PIN_FUNCTION_PTP0 + out_pin_cnt)) अणु
			snम_लिखो(pin_desc[out_pin_cnt].name,
				 माप(pin_desc[out_pin_cnt].name),
				 "AQ_GPIO%d", i);
			pin_desc[out_pin_cnt].index = out_pin_cnt;
			pin_desc[out_pin_cnt].chan = out_pin_cnt;
			pin_desc[out_pin_cnt++].func = PTP_PF_PEROUT;
		पूर्ण
	पूर्ण

	info->n_per_out = out_pin_cnt;

	अगर (hw_info->caps_ex & BIT(CAPS_EX_PHY_CTRL_TS_PIN)) अणु
		extts_pin_cnt += 1;

		snम_लिखो(pin_desc[out_pin_cnt].name,
			 माप(pin_desc[out_pin_cnt].name),
			  "AQ_GPIO%d", out_pin_cnt);
		pin_desc[out_pin_cnt].index = out_pin_cnt;
		pin_desc[out_pin_cnt].chan = 0;
		pin_desc[out_pin_cnt].func = PTP_PF_EXTTS;
	पूर्ण

	info->n_pins = out_pin_cnt + extts_pin_cnt;
	info->n_ext_ts = extts_pin_cnt;

	अगर (!info->n_pins)
		वापस;

	info->pin_config = kसुस्मृति(info->n_pins, माप(काष्ठा ptp_pin_desc),
				   GFP_KERNEL);

	अगर (!info->pin_config)
		वापस;

	स_नकल(info->pin_config, &pin_desc,
	       माप(काष्ठा ptp_pin_desc) * info->n_pins);
पूर्ण

व्योम aq_ptp_घड़ी_init(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	काष्ठा बारpec64 ts;

	kसमय_get_real_ts64(&ts);
	aq_ptp_समय_रखो(&aq_ptp->ptp_info, &ts);
पूर्ण

अटल व्योम aq_ptp_poll_sync_work_cb(काष्ठा work_काष्ठा *w);

पूर्णांक aq_ptp_init(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx_vec)
अणु
	bool a1_ptp = ATL_HW_IS_CHIP_FEATURE(aq_nic->aq_hw, ATLANTIC);
	काष्ठा hw_atl_utils_mbox mbox;
	काष्ठा ptp_घड़ी *घड़ी;
	काष्ठा aq_ptp_s *aq_ptp;
	पूर्णांक err = 0;

	अगर (!a1_ptp) अणु
		aq_nic->aq_ptp = शून्य;
		वापस 0;
	पूर्ण

	अगर (!aq_nic->aq_hw_ops->hw_get_ptp_ts) अणु
		aq_nic->aq_ptp = शून्य;
		वापस 0;
	पूर्ण

	अगर (!aq_nic->aq_fw_ops->enable_ptp) अणु
		aq_nic->aq_ptp = शून्य;
		वापस 0;
	पूर्ण

	hw_atl_utils_mpi_पढ़ो_stats(aq_nic->aq_hw, &mbox);

	अगर (!(mbox.info.caps_ex & BIT(CAPS_EX_PHY_PTP_EN))) अणु
		aq_nic->aq_ptp = शून्य;
		वापस 0;
	पूर्ण

	aq_ptp_offset_init(&mbox.info.ptp_offset);

	aq_ptp = kzalloc(माप(*aq_ptp), GFP_KERNEL);
	अगर (!aq_ptp) अणु
		err = -ENOMEM;
		जाओ err_निकास;
	पूर्ण

	aq_ptp->aq_nic = aq_nic;
	aq_ptp->a1_ptp = a1_ptp;

	spin_lock_init(&aq_ptp->ptp_lock);
	spin_lock_init(&aq_ptp->ptp_ring_lock);

	aq_ptp->ptp_info = aq_ptp_घड़ी;
	aq_ptp_gpio_init(&aq_ptp->ptp_info, &mbox.info);
	घड़ी = ptp_घड़ी_रेजिस्टर(&aq_ptp->ptp_info, &aq_nic->ndev->dev);
	अगर (IS_ERR(घड़ी)) अणु
		netdev_err(aq_nic->ndev, "ptp_clock_register failed\n");
		err = PTR_ERR(घड़ी);
		जाओ err_निकास;
	पूर्ण
	aq_ptp->ptp_घड़ी = घड़ी;
	aq_ptp_tx_समयout_init(&aq_ptp->ptp_tx_समयout);

	atomic_set(&aq_ptp->offset_egress, 0);
	atomic_set(&aq_ptp->offset_ingress, 0);

	netअगर_napi_add(aq_nic_get_ndev(aq_nic), &aq_ptp->napi,
		       aq_ptp_poll, AQ_CFG_NAPI_WEIGHT);

	aq_ptp->idx_vector = idx_vec;

	aq_nic->aq_ptp = aq_ptp;

	/* enable ptp counter */
	aq_utils_obj_set(&aq_nic->aq_hw->flags, AQ_HW_PTP_AVAILABLE);
	mutex_lock(&aq_nic->fwreq_mutex);
	aq_nic->aq_fw_ops->enable_ptp(aq_nic->aq_hw, 1);
	aq_ptp_घड़ी_init(aq_nic);
	mutex_unlock(&aq_nic->fwreq_mutex);

	INIT_DELAYED_WORK(&aq_ptp->poll_sync, &aq_ptp_poll_sync_work_cb);
	aq_ptp->eth_type_filter.location =
			aq_nic_reserve_filter(aq_nic, aq_rx_filter_ethertype);
	aq_ptp->udp_filter.location =
			aq_nic_reserve_filter(aq_nic, aq_rx_filter_l3l4);

	वापस 0;

err_निकास:
	अगर (aq_ptp)
		kमुक्त(aq_ptp->ptp_info.pin_config);
	kमुक्त(aq_ptp);
	aq_nic->aq_ptp = शून्य;
	वापस err;
पूर्ण

व्योम aq_ptp_unरेजिस्टर(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस;

	ptp_घड़ी_unरेजिस्टर(aq_ptp->ptp_घड़ी);
पूर्ण

व्योम aq_ptp_मुक्त(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस;

	aq_nic_release_filter(aq_nic, aq_rx_filter_ethertype,
			      aq_ptp->eth_type_filter.location);
	aq_nic_release_filter(aq_nic, aq_rx_filter_l3l4,
			      aq_ptp->udp_filter.location);
	cancel_delayed_work_sync(&aq_ptp->poll_sync);
	/* disable ptp */
	mutex_lock(&aq_nic->fwreq_mutex);
	aq_nic->aq_fw_ops->enable_ptp(aq_nic->aq_hw, 0);
	mutex_unlock(&aq_nic->fwreq_mutex);

	kमुक्त(aq_ptp->ptp_info.pin_config);

	netअगर_napi_del(&aq_ptp->napi);
	kमुक्त(aq_ptp);
	aq_nic->aq_ptp = शून्य;
पूर्ण

काष्ठा ptp_घड़ी *aq_ptp_get_ptp_घड़ी(काष्ठा aq_ptp_s *aq_ptp)
अणु
	वापस aq_ptp->ptp_घड़ी;
पूर्ण

/* PTP बाह्यal GPIO nanoseconds count */
अटल uपूर्णांक64_t aq_ptp_get_sync1588_ts(काष्ठा aq_nic_s *aq_nic)
अणु
	u64 ts = 0;

	अगर (aq_nic->aq_hw_ops->hw_get_sync_ts)
		aq_nic->aq_hw_ops->hw_get_sync_ts(aq_nic->aq_hw, &ts);

	वापस ts;
पूर्ण

अटल व्योम aq_ptp_start_work(काष्ठा aq_ptp_s *aq_ptp)
अणु
	अगर (aq_ptp->extts_pin_enabled) अणु
		aq_ptp->poll_समयout_ms = POLL_SYNC_TIMER_MS;
		aq_ptp->last_sync1588_ts =
				aq_ptp_get_sync1588_ts(aq_ptp->aq_nic);
		schedule_delayed_work(&aq_ptp->poll_sync,
				      msecs_to_jअगरfies(aq_ptp->poll_समयout_ms));
	पूर्ण
पूर्ण

पूर्णांक aq_ptp_link_change(काष्ठा aq_nic_s *aq_nic)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;

	अगर (!aq_ptp)
		वापस 0;

	अगर (aq_nic->aq_hw->aq_link_status.mbps)
		aq_ptp_start_work(aq_ptp);
	अन्यथा
		cancel_delayed_work_sync(&aq_ptp->poll_sync);

	वापस 0;
पूर्ण

अटल bool aq_ptp_sync_ts_updated(काष्ठा aq_ptp_s *aq_ptp, u64 *new_ts)
अणु
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 sync_ts2;
	u64 sync_ts;

	sync_ts = aq_ptp_get_sync1588_ts(aq_nic);

	अगर (sync_ts != aq_ptp->last_sync1588_ts) अणु
		sync_ts2 = aq_ptp_get_sync1588_ts(aq_nic);
		अगर (sync_ts != sync_ts2) अणु
			sync_ts = sync_ts2;
			sync_ts2 = aq_ptp_get_sync1588_ts(aq_nic);
			अगर (sync_ts != sync_ts2) अणु
				netdev_err(aq_nic->ndev,
					   "%s: Unable to get correct GPIO TS",
					   __func__);
				sync_ts = 0;
			पूर्ण
		पूर्ण

		*new_ts = sync_ts;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक aq_ptp_check_sync1588(काष्ठा aq_ptp_s *aq_ptp)
अणु
	काष्ठा aq_nic_s *aq_nic = aq_ptp->aq_nic;
	u64 sync_ts;

	 /* Sync1588 pin was triggered */
	अगर (aq_ptp_sync_ts_updated(aq_ptp, &sync_ts)) अणु
		अगर (aq_ptp->extts_pin_enabled) अणु
			काष्ठा ptp_घड़ी_event ptp_event;
			u64 समय = 0;

			aq_nic->aq_hw_ops->hw_ts_to_sys_घड़ी(aq_nic->aq_hw,
							      sync_ts, &समय);
			ptp_event.index = aq_ptp->ptp_info.n_pins - 1;
			ptp_event.बारtamp = समय;

			ptp_event.type = PTP_CLOCK_EXTTS;
			ptp_घड़ी_event(aq_ptp->ptp_घड़ी, &ptp_event);
		पूर्ण

		aq_ptp->last_sync1588_ts = sync_ts;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aq_ptp_poll_sync_work_cb(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(w);
	काष्ठा aq_ptp_s *aq_ptp = container_of(dw, काष्ठा aq_ptp_s, poll_sync);

	aq_ptp_check_sync1588(aq_ptp);

	अगर (aq_ptp->extts_pin_enabled) अणु
		अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(aq_ptp->poll_समयout_ms);

		schedule_delayed_work(&aq_ptp->poll_sync, समयout);
	पूर्ण
पूर्ण

पूर्णांक aq_ptp_get_ring_cnt(काष्ठा aq_nic_s *aq_nic, स्थिर क्रमागत atl_ring_type ring_type)
अणु
	अगर (!aq_nic->aq_ptp)
		वापस 0;

	/* Additional RX ring is allocated क्रम PTP HWTS on A1 */
	वापस (aq_nic->aq_ptp->a1_ptp && ring_type == ATL_RING_RX) ? 2 : 1;
पूर्ण

u64 *aq_ptp_get_stats(काष्ठा aq_nic_s *aq_nic, u64 *data)
अणु
	काष्ठा aq_ptp_s *aq_ptp = aq_nic->aq_ptp;
	अचिन्हित पूर्णांक count = 0U;

	अगर (!aq_ptp)
		वापस data;

	count = aq_ring_fill_stats_data(&aq_ptp->ptp_rx, data);
	data += count;
	count = aq_ring_fill_stats_data(&aq_ptp->ptp_tx, data);
	data += count;

	अगर (aq_ptp->a1_ptp) अणु
		/* Only Receive ring क्रम HWTS */
		count = aq_ring_fill_stats_data(&aq_ptp->hwts_rx, data);
		data += count;
	पूर्ण

	वापस data;
पूर्ण

#पूर्ण_अगर
