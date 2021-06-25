<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2018 Microchip Technology Inc. */

#समावेश <linux/netdevice.h>

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/net_tstamp.h>
#समावेश "lan743x_main.h"

#समावेश "lan743x_ptp.h"

#घोषणा LAN743X_LED0_ENABLE		20	/* LED0 offset in HW_CFG */
#घोषणा LAN743X_LED_ENABLE(pin)		BIT(LAN743X_LED0_ENABLE + (pin))

#घोषणा LAN743X_PTP_MAX_FREQ_ADJ_IN_PPB		(31249999)
#घोषणा LAN743X_PTP_MAX_FINE_ADJ_IN_SCALED_PPM	(2047999934)

अटल bool lan743x_ptp_is_enabled(काष्ठा lan743x_adapter *adapter);
अटल व्योम lan743x_ptp_enable(काष्ठा lan743x_adapter *adapter);
अटल व्योम lan743x_ptp_disable(काष्ठा lan743x_adapter *adapter);
अटल व्योम lan743x_ptp_reset(काष्ठा lan743x_adapter *adapter);
अटल व्योम lan743x_ptp_घड़ी_set(काष्ठा lan743x_adapter *adapter,
				  u32 seconds, u32 nano_seconds,
				  u32 sub_nano_seconds);

पूर्णांक lan743x_gpio_init(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_gpio *gpio = &adapter->gpio;

	spin_lock_init(&gpio->gpio_lock);

	gpio->gpio_cfg0 = 0; /* set all direction to input, data = 0 */
	gpio->gpio_cfg1 = 0x0FFF0000;/* disable all gpio, set to खोलो drain */
	gpio->gpio_cfg2 = 0;/* set all to 1588 low polarity level */
	gpio->gpio_cfg3 = 0;/* disable all 1588 output */
	lan743x_csr_ग_लिखो(adapter, GPIO_CFG0, gpio->gpio_cfg0);
	lan743x_csr_ग_लिखो(adapter, GPIO_CFG1, gpio->gpio_cfg1);
	lan743x_csr_ग_लिखो(adapter, GPIO_CFG2, gpio->gpio_cfg2);
	lan743x_csr_ग_लिखो(adapter, GPIO_CFG3, gpio->gpio_cfg3);

	वापस 0;
पूर्ण

अटल व्योम lan743x_ptp_रुको_till_cmd_करोne(काष्ठा lan743x_adapter *adapter,
					   u32 bit_mask)
अणु
	पूर्णांक समयout = 1000;
	u32 data = 0;

	जबतक (समयout &&
	       (data = (lan743x_csr_पढ़ो(adapter, PTP_CMD_CTL) &
	       bit_mask))) अणु
		usleep_range(1000, 20000);
		समयout--;
	पूर्ण
	अगर (data) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "timeout waiting for cmd to be done, cmd = 0x%08X\n",
			  bit_mask);
	पूर्ण
पूर्ण

अटल व्योम lan743x_ptp_tx_ts_enqueue_ts(काष्ठा lan743x_adapter *adapter,
					 u32 seconds, u32 nano_seconds,
					 u32 header)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	अगर (ptp->tx_ts_queue_size < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) अणु
		ptp->tx_ts_seconds_queue[ptp->tx_ts_queue_size] = seconds;
		ptp->tx_ts_nseconds_queue[ptp->tx_ts_queue_size] = nano_seconds;
		ptp->tx_ts_header_queue[ptp->tx_ts_queue_size] = header;
		ptp->tx_ts_queue_size++;
	पूर्ण अन्यथा अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "tx ts queue overflow\n");
	पूर्ण
	spin_unlock_bh(&ptp->tx_ts_lock);
पूर्ण

अटल व्योम lan743x_ptp_tx_ts_complete(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	काष्ठा skb_shared_hwtstamps tstamps;
	u32 header, nseconds, seconds;
	bool ignore_sync = false;
	काष्ठा sk_buff *skb;
	पूर्णांक c, i;

	spin_lock_bh(&ptp->tx_ts_lock);
	c = ptp->tx_ts_skb_queue_size;

	अगर (c > ptp->tx_ts_queue_size)
		c = ptp->tx_ts_queue_size;
	अगर (c <= 0)
		जाओ करोne;

	क्रम (i = 0; i < c; i++) अणु
		ignore_sync = ((ptp->tx_ts_ignore_sync_queue &
				BIT(i)) != 0);
		skb = ptp->tx_ts_skb_queue[i];
		nseconds = ptp->tx_ts_nseconds_queue[i];
		seconds = ptp->tx_ts_seconds_queue[i];
		header = ptp->tx_ts_header_queue[i];

		स_रखो(&tstamps, 0, माप(tstamps));
		tstamps.hwtstamp = kसमय_set(seconds, nseconds);
		अगर (!ignore_sync ||
		    ((header & PTP_TX_MSG_HEADER_MSG_TYPE_) !=
		    PTP_TX_MSG_HEADER_MSG_TYPE_SYNC_))
			skb_tstamp_tx(skb, &tstamps);

		dev_kमुक्त_skb(skb);

		ptp->tx_ts_skb_queue[i] = शून्य;
		ptp->tx_ts_seconds_queue[i] = 0;
		ptp->tx_ts_nseconds_queue[i] = 0;
		ptp->tx_ts_header_queue[i] = 0;
	पूर्ण

	/* shअगरt queue */
	ptp->tx_ts_ignore_sync_queue >>= c;
	क्रम (i = c; i < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS; i++) अणु
		ptp->tx_ts_skb_queue[i - c] = ptp->tx_ts_skb_queue[i];
		ptp->tx_ts_seconds_queue[i - c] = ptp->tx_ts_seconds_queue[i];
		ptp->tx_ts_nseconds_queue[i - c] = ptp->tx_ts_nseconds_queue[i];
		ptp->tx_ts_header_queue[i - c] = ptp->tx_ts_header_queue[i];

		ptp->tx_ts_skb_queue[i] = शून्य;
		ptp->tx_ts_seconds_queue[i] = 0;
		ptp->tx_ts_nseconds_queue[i] = 0;
		ptp->tx_ts_header_queue[i] = 0;
	पूर्ण
	ptp->tx_ts_skb_queue_size -= c;
	ptp->tx_ts_queue_size -= c;
करोne:
	ptp->pending_tx_बारtamps -= c;
	spin_unlock_bh(&ptp->tx_ts_lock);
पूर्ण

अटल पूर्णांक lan743x_ptp_reserve_event_ch(काष्ठा lan743x_adapter *adapter,
					पूर्णांक event_channel)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	पूर्णांक result = -ENODEV;

	mutex_lock(&ptp->command_lock);
	अगर (!(test_bit(event_channel, &ptp->used_event_ch))) अणु
		ptp->used_event_ch |= BIT(event_channel);
		result = event_channel;
	पूर्ण अन्यथा अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "attempted to reserved a used event_channel = %d\n",
			   event_channel);
	पूर्ण
	mutex_unlock(&ptp->command_lock);
	वापस result;
पूर्ण

अटल व्योम lan743x_ptp_release_event_ch(काष्ठा lan743x_adapter *adapter,
					 पूर्णांक event_channel)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);
	अगर (test_bit(event_channel, &ptp->used_event_ch)) अणु
		ptp->used_event_ch &= ~BIT(event_channel);
	पूर्ण अन्यथा अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "attempted release on a not used event_channel = %d\n",
			   event_channel);
	पूर्ण
	mutex_unlock(&ptp->command_lock);
पूर्ण

अटल व्योम lan743x_ptp_घड़ी_get(काष्ठा lan743x_adapter *adapter,
				  u32 *seconds, u32 *nano_seconds,
				  u32 *sub_nano_seconds);
अटल व्योम lan743x_ptp_घड़ी_step(काष्ठा lan743x_adapter *adapter,
				   s64 समय_step_ns);

अटल व्योम lan743x_led_mux_enable(काष्ठा lan743x_adapter *adapter,
				   पूर्णांक pin, bool enable)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	अगर (ptp->leds_multiplexed &&
	    ptp->led_enabled[pin]) अणु
		u32 val = lan743x_csr_पढ़ो(adapter, HW_CFG);

		अगर (enable)
			val |= LAN743X_LED_ENABLE(pin);
		अन्यथा
			val &= ~LAN743X_LED_ENABLE(pin);

		lan743x_csr_ग_लिखो(adapter, HW_CFG, val);
	पूर्ण
पूर्ण

अटल व्योम lan743x_led_mux_save(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	u32 id_rev = adapter->csr.id_rev & ID_REV_ID_MASK_;

	अगर (id_rev == ID_REV_ID_LAN7430_) अणु
		पूर्णांक i;
		u32 val = lan743x_csr_पढ़ो(adapter, HW_CFG);

		क्रम (i = 0; i < LAN7430_N_LED; i++) अणु
			bool led_enabled = (val & LAN743X_LED_ENABLE(i)) != 0;

			ptp->led_enabled[i] = led_enabled;
		पूर्ण
		ptp->leds_multiplexed = true;
	पूर्ण अन्यथा अणु
		ptp->leds_multiplexed = false;
	पूर्ण
पूर्ण

अटल व्योम lan743x_led_mux_restore(काष्ठा lan743x_adapter *adapter)
अणु
	u32 id_rev = adapter->csr.id_rev & ID_REV_ID_MASK_;

	अगर (id_rev == ID_REV_ID_LAN7430_) अणु
		पूर्णांक i;

		क्रम (i = 0; i < LAN7430_N_LED; i++)
			lan743x_led_mux_enable(adapter, i, true);
	पूर्ण
पूर्ण

अटल पूर्णांक lan743x_gpio_rsrv_ptp_out(काष्ठा lan743x_adapter *adapter,
				     पूर्णांक pin, पूर्णांक event_channel)
अणु
	काष्ठा lan743x_gpio *gpio = &adapter->gpio;
	अचिन्हित दीर्घ irq_flags = 0;
	पूर्णांक bit_mask = BIT(pin);
	पूर्णांक ret = -EBUSY;

	spin_lock_irqsave(&gpio->gpio_lock, irq_flags);

	अगर (!(gpio->used_bits & bit_mask)) अणु
		gpio->used_bits |= bit_mask;
		gpio->output_bits |= bit_mask;
		gpio->ptp_bits |= bit_mask;

		/* assign pin to GPIO function */
		lan743x_led_mux_enable(adapter, pin, false);

		/* set as output, and zero initial value */
		gpio->gpio_cfg0 |= GPIO_CFG0_GPIO_सूची_BIT_(pin);
		gpio->gpio_cfg0 &= ~GPIO_CFG0_GPIO_DATA_BIT_(pin);
		lan743x_csr_ग_लिखो(adapter, GPIO_CFG0, gpio->gpio_cfg0);

		/* enable gpio, and set buffer type to push pull */
		gpio->gpio_cfg1 &= ~GPIO_CFG1_GPIOEN_BIT_(pin);
		gpio->gpio_cfg1 |= GPIO_CFG1_GPIOBUF_BIT_(pin);
		lan743x_csr_ग_लिखो(adapter, GPIO_CFG1, gpio->gpio_cfg1);

		/* set 1588 polarity to high */
		gpio->gpio_cfg2 |= GPIO_CFG2_1588_POL_BIT_(pin);
		lan743x_csr_ग_लिखो(adapter, GPIO_CFG2, gpio->gpio_cfg2);

		अगर (event_channel == 0) अणु
			/* use channel A */
			gpio->gpio_cfg3 &= ~GPIO_CFG3_1588_CH_SEL_BIT_(pin);
		पूर्ण अन्यथा अणु
			/* use channel B */
			gpio->gpio_cfg3 |= GPIO_CFG3_1588_CH_SEL_BIT_(pin);
		पूर्ण
		gpio->gpio_cfg3 |= GPIO_CFG3_1588_OE_BIT_(pin);
		lan743x_csr_ग_लिखो(adapter, GPIO_CFG3, gpio->gpio_cfg3);

		ret = pin;
	पूर्ण
	spin_unlock_irqrestore(&gpio->gpio_lock, irq_flags);
	वापस ret;
पूर्ण

अटल व्योम lan743x_gpio_release(काष्ठा lan743x_adapter *adapter, पूर्णांक pin)
अणु
	काष्ठा lan743x_gpio *gpio = &adapter->gpio;
	अचिन्हित दीर्घ irq_flags = 0;
	पूर्णांक bit_mask = BIT(pin);

	spin_lock_irqsave(&gpio->gpio_lock, irq_flags);
	अगर (gpio->used_bits & bit_mask) अणु
		gpio->used_bits &= ~bit_mask;
		अगर (gpio->output_bits & bit_mask) अणु
			gpio->output_bits &= ~bit_mask;

			अगर (gpio->ptp_bits & bit_mask) अणु
				gpio->ptp_bits &= ~bit_mask;
				/* disable ptp output */
				gpio->gpio_cfg3 &= ~GPIO_CFG3_1588_OE_BIT_(pin);
				lan743x_csr_ग_लिखो(adapter, GPIO_CFG3,
						  gpio->gpio_cfg3);
			पूर्ण
			/* release gpio output */

			/* disable gpio */
			gpio->gpio_cfg1 |= GPIO_CFG1_GPIOEN_BIT_(pin);
			gpio->gpio_cfg1 &= ~GPIO_CFG1_GPIOBUF_BIT_(pin);
			lan743x_csr_ग_लिखो(adapter, GPIO_CFG1, gpio->gpio_cfg1);

			/* reset back to input */
			gpio->gpio_cfg0 &= ~GPIO_CFG0_GPIO_सूची_BIT_(pin);
			gpio->gpio_cfg0 &= ~GPIO_CFG0_GPIO_DATA_BIT_(pin);
			lan743x_csr_ग_लिखो(adapter, GPIO_CFG0, gpio->gpio_cfg0);

			/* assign pin to original function */
			lan743x_led_mux_enable(adapter, pin, true);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gpio->gpio_lock, irq_flags);
पूर्ण

अटल पूर्णांक lan743x_ptpci_adjfine(काष्ठा ptp_घड़ी_info *ptpci, दीर्घ scaled_ppm)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);
	u32 lan743x_rate_adj = 0;
	bool positive = true;
	u64 u64_delta = 0;

	अगर ((scaled_ppm < (-LAN743X_PTP_MAX_FINE_ADJ_IN_SCALED_PPM)) ||
	    scaled_ppm > LAN743X_PTP_MAX_FINE_ADJ_IN_SCALED_PPM) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (scaled_ppm > 0) अणु
		u64_delta = (u64)scaled_ppm;
		positive = true;
	पूर्ण अन्यथा अणु
		u64_delta = (u64)(-scaled_ppm);
		positive = false;
	पूर्ण
	u64_delta = (u64_delta << 19);
	lan743x_rate_adj = भाग_u64(u64_delta, 1000000);

	अगर (positive)
		lan743x_rate_adj |= PTP_CLOCK_RATE_ADJ_सूची_;

	lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_RATE_ADJ,
			  lan743x_rate_adj);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ptpci_adjfreq(काष्ठा ptp_घड़ी_info *ptpci, s32 delta_ppb)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);
	u32 lan743x_rate_adj = 0;
	bool positive = true;
	u32 u32_delta = 0;
	u64 u64_delta = 0;

	अगर ((delta_ppb < (-LAN743X_PTP_MAX_FREQ_ADJ_IN_PPB)) ||
	    delta_ppb > LAN743X_PTP_MAX_FREQ_ADJ_IN_PPB) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (delta_ppb > 0) अणु
		u32_delta = (u32)delta_ppb;
		positive = true;
	पूर्ण अन्यथा अणु
		u32_delta = (u32)(-delta_ppb);
		positive = false;
	पूर्ण
	u64_delta = (((u64)u32_delta) << 35);
	lan743x_rate_adj = भाग_u64(u64_delta, 1000000000);

	अगर (positive)
		lan743x_rate_adj |= PTP_CLOCK_RATE_ADJ_सूची_;

	lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_RATE_ADJ,
			  lan743x_rate_adj);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ptpci_adjसमय(काष्ठा ptp_घड़ी_info *ptpci, s64 delta)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);

	lan743x_ptp_घड़ी_step(adapter, delta);

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ptpci_समय_लो64(काष्ठा ptp_घड़ी_info *ptpci,
				   काष्ठा बारpec64 *ts)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);
	u32 nano_seconds = 0;
	u32 seconds = 0;

	lan743x_ptp_घड़ी_get(adapter, &seconds, &nano_seconds, शून्य);
	ts->tv_sec = seconds;
	ts->tv_nsec = nano_seconds;

	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ptpci_समय_रखो64(काष्ठा ptp_घड़ी_info *ptpci,
				   स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);
	u32 nano_seconds = 0;
	u32 seconds = 0;

	अगर (ts) अणु
		अगर (ts->tv_sec > 0xFFFFFFFFLL ||
		    ts->tv_sec < 0) अणु
			netअगर_warn(adapter, drv, adapter->netdev,
				   "ts->tv_sec out of range, %lld\n",
				   ts->tv_sec);
			वापस -दुस्फल;
		पूर्ण
		अगर (ts->tv_nsec >= 1000000000L ||
		    ts->tv_nsec < 0) अणु
			netअगर_warn(adapter, drv, adapter->netdev,
				   "ts->tv_nsec out of range, %ld\n",
				   ts->tv_nsec);
			वापस -दुस्फल;
		पूर्ण
		seconds = ts->tv_sec;
		nano_seconds = ts->tv_nsec;
		lan743x_ptp_घड़ी_set(adapter, seconds, nano_seconds, 0);
	पूर्ण अन्यथा अणु
		netअगर_warn(adapter, drv, adapter->netdev, "ts == NULL\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lan743x_ptp_perout_off(काष्ठा lan743x_adapter *adapter,
				   अचिन्हित पूर्णांक index)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	u32 general_config = 0;
	काष्ठा lan743x_ptp_perout *perout = &ptp->perout[index];

	अगर (perout->gpio_pin >= 0) अणु
		lan743x_gpio_release(adapter, perout->gpio_pin);
		perout->gpio_pin = -1;
	पूर्ण

	अगर (perout->event_ch >= 0) अणु
		/* set target to far in the future, effectively disabling it */
		lan743x_csr_ग_लिखो(adapter,
				  PTP_CLOCK_TARGET_SEC_X(perout->event_ch),
				  0xFFFF0000);
		lan743x_csr_ग_लिखो(adapter,
				  PTP_CLOCK_TARGET_NS_X(perout->event_ch),
				  0);

		general_config = lan743x_csr_पढ़ो(adapter, PTP_GENERAL_CONFIG);
		general_config |= PTP_GENERAL_CONFIG_RELOAD_ADD_X_
				  (perout->event_ch);
		lan743x_csr_ग_लिखो(adapter, PTP_GENERAL_CONFIG, general_config);
		lan743x_ptp_release_event_ch(adapter, perout->event_ch);
		perout->event_ch = -1;
	पूर्ण
पूर्ण

अटल पूर्णांक lan743x_ptp_perout(काष्ठा lan743x_adapter *adapter, पूर्णांक on,
			      काष्ठा ptp_perout_request *perout_request)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	u32 period_sec = 0, period_nsec = 0;
	u32 start_sec = 0, start_nsec = 0;
	u32 general_config = 0;
	पूर्णांक pulse_width = 0;
	पूर्णांक perout_pin = 0;
	अचिन्हित पूर्णांक index = perout_request->index;
	काष्ठा lan743x_ptp_perout *perout = &ptp->perout[index];

	/* Reject requests with unsupported flags */
	अगर (perout_request->flags)
		वापस -EOPNOTSUPP;

	अगर (on) अणु
		perout_pin = ptp_find_pin(ptp->ptp_घड़ी, PTP_PF_PEROUT,
					  perout_request->index);
		अगर (perout_pin < 0)
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		lan743x_ptp_perout_off(adapter, index);
		वापस 0;
	पूर्ण

	अगर (perout->event_ch >= 0 ||
	    perout->gpio_pin >= 0) अणु
		/* alपढ़ोy on, turn off first */
		lan743x_ptp_perout_off(adapter, index);
	पूर्ण

	perout->event_ch = lan743x_ptp_reserve_event_ch(adapter, index);

	अगर (perout->event_ch < 0) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "Failed to reserve event channel %d for PEROUT\n",
			   index);
		जाओ failed;
	पूर्ण

	perout->gpio_pin = lan743x_gpio_rsrv_ptp_out(adapter,
						     perout_pin,
						     perout->event_ch);

	अगर (perout->gpio_pin < 0) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "Failed to reserve gpio %d for PEROUT\n",
			   perout_pin);
		जाओ failed;
	पूर्ण

	start_sec = perout_request->start.sec;
	start_sec += perout_request->start.nsec / 1000000000;
	start_nsec = perout_request->start.nsec % 1000000000;

	period_sec = perout_request->period.sec;
	period_sec += perout_request->period.nsec / 1000000000;
	period_nsec = perout_request->period.nsec % 1000000000;

	अगर (period_sec == 0) अणु
		अगर (period_nsec >= 400000000) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_200MS_;
		पूर्ण अन्यथा अगर (period_nsec >= 20000000) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_10MS_;
		पूर्ण अन्यथा अगर (period_nsec >= 2000000) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_1MS_;
		पूर्ण अन्यथा अगर (period_nsec >= 200000) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_100US_;
		पूर्ण अन्यथा अगर (period_nsec >= 20000) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_10US_;
		पूर्ण अन्यथा अगर (period_nsec >= 200) अणु
			pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_100NS_;
		पूर्ण अन्यथा अणु
			netअगर_warn(adapter, drv, adapter->netdev,
				   "perout period too small, minimum is 200nS\n");
			जाओ failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		pulse_width = PTP_GENERAL_CONFIG_CLOCK_EVENT_200MS_;
	पूर्ण

	/* turn off by setting target far in future */
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_SEC_X(perout->event_ch),
			  0xFFFF0000);
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_NS_X(perout->event_ch), 0);

	/* Configure to pulse every period */
	general_config = lan743x_csr_पढ़ो(adapter, PTP_GENERAL_CONFIG);
	general_config &= ~(PTP_GENERAL_CONFIG_CLOCK_EVENT_X_MASK_
			  (perout->event_ch));
	general_config |= PTP_GENERAL_CONFIG_CLOCK_EVENT_X_SET_
			  (perout->event_ch, pulse_width);
	general_config &= ~PTP_GENERAL_CONFIG_RELOAD_ADD_X_
			  (perout->event_ch);
	lan743x_csr_ग_लिखो(adapter, PTP_GENERAL_CONFIG, general_config);

	/* set the reload to one toggle cycle */
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_RELOAD_SEC_X(perout->event_ch),
			  period_sec);
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_RELOAD_NS_X(perout->event_ch),
			  period_nsec);

	/* set the start समय */
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_SEC_X(perout->event_ch),
			  start_sec);
	lan743x_csr_ग_लिखो(adapter,
			  PTP_CLOCK_TARGET_NS_X(perout->event_ch),
			  start_nsec);

	वापस 0;

failed:
	lan743x_ptp_perout_off(adapter, index);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक lan743x_ptpci_enable(काष्ठा ptp_घड़ी_info *ptpci,
				काष्ठा ptp_घड़ी_request *request, पूर्णांक on)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);

	अगर (request) अणु
		चयन (request->type) अणु
		हाल PTP_CLK_REQ_EXTTS:
			वापस -EINVAL;
		हाल PTP_CLK_REQ_PEROUT:
			अगर (request->perout.index < ptpci->n_per_out)
				वापस lan743x_ptp_perout(adapter, on,
							  &request->perout);
			वापस -EINVAL;
		हाल PTP_CLK_REQ_PPS:
			वापस -EINVAL;
		शेष:
			netअगर_err(adapter, drv, adapter->netdev,
				  "request->type == %d, Unknown\n",
				  request->type);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_err(adapter, drv, adapter->netdev, "request == NULL\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lan743x_ptpci_verअगरy_pin_config(काष्ठा ptp_घड़ी_info *ptp,
					   अचिन्हित पूर्णांक pin,
					   क्रमागत ptp_pin_function func,
					   अचिन्हित पूर्णांक chan)
अणु
	पूर्णांक result = 0;

	/* Confirm the requested function is supported. Parameter
	 * validation is करोne by the caller.
	 */
	चयन (func) अणु
	हाल PTP_PF_NONE:
	हाल PTP_PF_PEROUT:
		अवरोध;
	हाल PTP_PF_EXTTS:
	हाल PTP_PF_PHYSYNC:
	शेष:
		result = -1;
		अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल दीर्घ lan743x_ptpci_करो_aux_work(काष्ठा ptp_घड़ी_info *ptpci)
अणु
	काष्ठा lan743x_ptp *ptp =
		container_of(ptpci, काष्ठा lan743x_ptp, ptp_घड़ी_info);
	काष्ठा lan743x_adapter *adapter =
		container_of(ptp, काष्ठा lan743x_adapter, ptp);
	u32 cap_info, cause, header, nsec, seconds;
	bool new_बारtamp_available = false;
	पूर्णांक count = 0;

	जबतक ((count < 100) &&
	       (lan743x_csr_पढ़ो(adapter, PTP_INT_STS) & PTP_INT_BIT_TX_TS_)) अणु
		count++;
		cap_info = lan743x_csr_पढ़ो(adapter, PTP_CAP_INFO);

		अगर (PTP_CAP_INFO_TX_TS_CNT_GET_(cap_info) > 0) अणु
			seconds = lan743x_csr_पढ़ो(adapter,
						   PTP_TX_EGRESS_SEC);
			nsec = lan743x_csr_पढ़ो(adapter, PTP_TX_EGRESS_NS);
			cause = (nsec &
				 PTP_TX_EGRESS_NS_CAPTURE_CAUSE_MASK_);
			header = lan743x_csr_पढ़ो(adapter,
						  PTP_TX_MSG_HEADER);

			अगर (cause == PTP_TX_EGRESS_NS_CAPTURE_CAUSE_SW_) अणु
				nsec &= PTP_TX_EGRESS_NS_TS_NS_MASK_;
				lan743x_ptp_tx_ts_enqueue_ts(adapter,
							     seconds, nsec,
							     header);
				new_बारtamp_available = true;
			पूर्ण अन्यथा अगर (cause ==
				PTP_TX_EGRESS_NS_CAPTURE_CAUSE_AUTO_) अणु
				netअगर_err(adapter, drv, adapter->netdev,
					  "Auto capture cause not supported\n");
			पूर्ण अन्यथा अणु
				netअगर_warn(adapter, drv, adapter->netdev,
					   "unknown tx timestamp capture cause\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			netअगर_warn(adapter, drv, adapter->netdev,
				   "TX TS INT but no TX TS CNT\n");
		पूर्ण
		lan743x_csr_ग_लिखो(adapter, PTP_INT_STS, PTP_INT_BIT_TX_TS_);
	पूर्ण

	अगर (new_बारtamp_available)
		lan743x_ptp_tx_ts_complete(adapter);

	lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_1588_);

	वापस -1;
पूर्ण

अटल व्योम lan743x_ptp_घड़ी_get(काष्ठा lan743x_adapter *adapter,
				  u32 *seconds, u32 *nano_seconds,
				  u32 *sub_nano_seconds)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);

	lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_CLOCK_READ_);
	lan743x_ptp_रुको_till_cmd_करोne(adapter, PTP_CMD_CTL_PTP_CLOCK_READ_);

	अगर (seconds)
		(*seconds) = lan743x_csr_पढ़ो(adapter, PTP_CLOCK_SEC);

	अगर (nano_seconds)
		(*nano_seconds) = lan743x_csr_पढ़ो(adapter, PTP_CLOCK_NS);

	अगर (sub_nano_seconds)
		(*sub_nano_seconds) =
		lan743x_csr_पढ़ो(adapter, PTP_CLOCK_SUBNS);

	mutex_unlock(&ptp->command_lock);
पूर्ण

अटल व्योम lan743x_ptp_घड़ी_step(काष्ठा lan743x_adapter *adapter,
				   s64 समय_step_ns)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	u32 nano_seconds_step = 0;
	u64 असल_समय_step_ns = 0;
	u32 अचिन्हित_seconds = 0;
	u32 nano_seconds = 0;
	u32 reमुख्यder = 0;
	s32 seconds = 0;

	अगर (समय_step_ns >  15000000000LL) अणु
		/* convert to घड़ी set */
		lan743x_ptp_घड़ी_get(adapter, &अचिन्हित_seconds,
				      &nano_seconds, शून्य);
		अचिन्हित_seconds += भाग_u64_rem(समय_step_ns, 1000000000LL,
						&reमुख्यder);
		nano_seconds += reमुख्यder;
		अगर (nano_seconds >= 1000000000) अणु
			अचिन्हित_seconds++;
			nano_seconds -= 1000000000;
		पूर्ण
		lan743x_ptp_घड़ी_set(adapter, अचिन्हित_seconds,
				      nano_seconds, 0);
		वापस;
	पूर्ण अन्यथा अगर (समय_step_ns < -15000000000LL) अणु
		/* convert to घड़ी set */
		समय_step_ns = -समय_step_ns;

		lan743x_ptp_घड़ी_get(adapter, &अचिन्हित_seconds,
				      &nano_seconds, शून्य);
		अचिन्हित_seconds -= भाग_u64_rem(समय_step_ns, 1000000000LL,
						&reमुख्यder);
		nano_seconds_step = reमुख्यder;
		अगर (nano_seconds < nano_seconds_step) अणु
			अचिन्हित_seconds--;
			nano_seconds += 1000000000;
		पूर्ण
		nano_seconds -= nano_seconds_step;
		lan743x_ptp_घड़ी_set(adapter, अचिन्हित_seconds,
				      nano_seconds, 0);
		वापस;
	पूर्ण

	/* करो घड़ी step */
	अगर (समय_step_ns >= 0) अणु
		असल_समय_step_ns = (u64)(समय_step_ns);
		seconds = (s32)भाग_u64_rem(असल_समय_step_ns, 1000000000,
					   &reमुख्यder);
		nano_seconds = (u32)reमुख्यder;
	पूर्ण अन्यथा अणु
		असल_समय_step_ns = (u64)(-समय_step_ns);
		seconds = -((s32)भाग_u64_rem(असल_समय_step_ns, 1000000000,
					     &reमुख्यder));
		nano_seconds = (u32)reमुख्यder;
		अगर (nano_seconds > 0) अणु
			/* subtracting nano seconds is not allowed
			 * convert to subtracting from seconds,
			 * and adding to nanoseconds
			 */
			seconds--;
			nano_seconds = (1000000000 - nano_seconds);
		पूर्ण
	पूर्ण

	अगर (nano_seconds > 0) अणु
		/* add 8 ns to cover the likely normal increment */
		nano_seconds += 8;
	पूर्ण

	अगर (nano_seconds >= 1000000000) अणु
		/* carry पूर्णांकo seconds */
		seconds++;
		nano_seconds -= 1000000000;
	पूर्ण

	जबतक (seconds) अणु
		mutex_lock(&ptp->command_lock);
		अगर (seconds > 0) अणु
			u32 adjusपंचांगent_value = (u32)seconds;

			अगर (adjusपंचांगent_value > 0xF)
				adjusपंचांगent_value = 0xF;
			lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_STEP_ADJ,
					  PTP_CLOCK_STEP_ADJ_सूची_ |
					  adjusपंचांगent_value);
			seconds -= ((s32)adjusपंचांगent_value);
		पूर्ण अन्यथा अणु
			u32 adjusपंचांगent_value = (u32)(-seconds);

			अगर (adjusपंचांगent_value > 0xF)
				adjusपंचांगent_value = 0xF;
			lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_STEP_ADJ,
					  adjusपंचांगent_value);
			seconds += ((s32)adjusपंचांगent_value);
		पूर्ण
		lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL,
				  PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_);
		lan743x_ptp_रुको_till_cmd_करोne(adapter,
					       PTP_CMD_CTL_PTP_CLOCK_STEP_SEC_);
		mutex_unlock(&ptp->command_lock);
	पूर्ण
	अगर (nano_seconds) अणु
		mutex_lock(&ptp->command_lock);
		lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_STEP_ADJ,
				  PTP_CLOCK_STEP_ADJ_सूची_ |
				  (nano_seconds &
				  PTP_CLOCK_STEP_ADJ_VALUE_MASK_));
		lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL,
				  PTP_CMD_CTL_PTP_CLK_STP_NSEC_);
		lan743x_ptp_रुको_till_cmd_करोne(adapter,
					       PTP_CMD_CTL_PTP_CLK_STP_NSEC_);
		mutex_unlock(&ptp->command_lock);
	पूर्ण
पूर्ण

व्योम lan743x_ptp_isr(व्योम *context)
अणु
	काष्ठा lan743x_adapter *adapter = (काष्ठा lan743x_adapter *)context;
	काष्ठा lan743x_ptp *ptp = शून्य;
	पूर्णांक enable_flag = 1;
	u32 ptp_पूर्णांक_sts = 0;

	ptp = &adapter->ptp;

	lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_1588_);

	ptp_पूर्णांक_sts = lan743x_csr_पढ़ो(adapter, PTP_INT_STS);
	ptp_पूर्णांक_sts &= lan743x_csr_पढ़ो(adapter, PTP_INT_EN_SET);

	अगर (ptp_पूर्णांक_sts & PTP_INT_BIT_TX_TS_) अणु
		ptp_schedule_worker(ptp->ptp_घड़ी, 0);
		enable_flag = 0;/* tasklet will re-enable later */
	पूर्ण
	अगर (ptp_पूर्णांक_sts & PTP_INT_BIT_TX_SWTS_ERR_) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "PTP TX Software Timestamp Error\n");
		/* clear पूर्णांक status bit */
		lan743x_csr_ग_लिखो(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TX_SWTS_ERR_);
	पूर्ण
	अगर (ptp_पूर्णांक_sts & PTP_INT_BIT_TIMER_B_) अणु
		/* clear पूर्णांक status bit */
		lan743x_csr_ग_लिखो(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TIMER_B_);
	पूर्ण
	अगर (ptp_पूर्णांक_sts & PTP_INT_BIT_TIMER_A_) अणु
		/* clear पूर्णांक status bit */
		lan743x_csr_ग_लिखो(adapter, PTP_INT_STS,
				  PTP_INT_BIT_TIMER_A_);
	पूर्ण

	अगर (enable_flag) अणु
		/* re-enable isr */
		lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_1588_);
	पूर्ण
पूर्ण

अटल व्योम lan743x_ptp_tx_ts_enqueue_skb(काष्ठा lan743x_adapter *adapter,
					  काष्ठा sk_buff *skb, bool ignore_sync)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	अगर (ptp->tx_ts_skb_queue_size < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) अणु
		ptp->tx_ts_skb_queue[ptp->tx_ts_skb_queue_size] = skb;
		अगर (ignore_sync)
			ptp->tx_ts_ignore_sync_queue |=
				BIT(ptp->tx_ts_skb_queue_size);
		ptp->tx_ts_skb_queue_size++;
	पूर्ण अन्यथा अणु
		/* this should never happen, so दीर्घ as the tx channel
		 * calls and honors the result from
		 * lan743x_ptp_request_tx_बारtamp
		 */
		netअगर_err(adapter, drv, adapter->netdev,
			  "tx ts skb queue overflow\n");
		dev_kमुक्त_skb(skb);
	पूर्ण
	spin_unlock_bh(&ptp->tx_ts_lock);
पूर्ण

अटल व्योम lan743x_ptp_sync_to_प्रणाली_घड़ी(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_घड़ीtai_ts64(&ts);

	lan743x_ptp_घड़ी_set(adapter, ts.tv_sec, ts.tv_nsec, 0);
पूर्ण

व्योम lan743x_ptp_update_latency(काष्ठा lan743x_adapter *adapter,
				u32 link_speed)
अणु
	चयन (link_speed) अणु
	हाल 10:
		lan743x_csr_ग_लिखो(adapter, PTP_LATENCY,
				  PTP_LATENCY_TX_SET_(0) |
				  PTP_LATENCY_RX_SET_(0));
		अवरोध;
	हाल 100:
		lan743x_csr_ग_लिखो(adapter, PTP_LATENCY,
				  PTP_LATENCY_TX_SET_(181) |
				  PTP_LATENCY_RX_SET_(594));
		अवरोध;
	हाल 1000:
		lan743x_csr_ग_लिखो(adapter, PTP_LATENCY,
				  PTP_LATENCY_TX_SET_(30) |
				  PTP_LATENCY_RX_SET_(525));
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक lan743x_ptp_init(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	पूर्णांक i;

	mutex_init(&ptp->command_lock);
	spin_lock_init(&ptp->tx_ts_lock);
	ptp->used_event_ch = 0;

	क्रम (i = 0; i < LAN743X_PTP_N_EVENT_CHAN; i++) अणु
		ptp->perout[i].event_ch = -1;
		ptp->perout[i].gpio_pin = -1;
	पूर्ण

	lan743x_led_mux_save(adapter);

	वापस 0;
पूर्ण

पूर्णांक lan743x_ptp_खोलो(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	पूर्णांक ret = -ENODEV;
	u32 temp;
	पूर्णांक i;
	पूर्णांक n_pins;

	lan743x_ptp_reset(adapter);
	lan743x_ptp_sync_to_प्रणाली_घड़ी(adapter);
	temp = lan743x_csr_पढ़ो(adapter, PTP_TX_MOD2);
	temp |= PTP_TX_MOD2_TX_PTP_CLR_UDPV4_CHKSUM_;
	lan743x_csr_ग_लिखो(adapter, PTP_TX_MOD2, temp);
	lan743x_ptp_enable(adapter);
	lan743x_csr_ग_लिखो(adapter, INT_EN_SET, INT_BIT_1588_);
	lan743x_csr_ग_लिखो(adapter, PTP_INT_EN_SET,
			  PTP_INT_BIT_TX_SWTS_ERR_ | PTP_INT_BIT_TX_TS_);
	ptp->flags |= PTP_FLAG_ISR_ENABLED;

	अगर (!IS_ENABLED(CONFIG_PTP_1588_CLOCK))
		वापस 0;

	चयन (adapter->csr.id_rev & ID_REV_ID_MASK_) अणु
	हाल ID_REV_ID_LAN7430_:
		n_pins = LAN7430_N_GPIO;
		अवरोध;
	हाल ID_REV_ID_LAN7431_:
		n_pins = LAN7431_N_GPIO;
		अवरोध;
	शेष:
		netअगर_warn(adapter, drv, adapter->netdev,
			   "Unknown LAN743x (%08x). Assuming no GPIO\n",
			   adapter->csr.id_rev);
		n_pins = 0;
		अवरोध;
	पूर्ण

	अगर (n_pins > LAN743X_PTP_N_GPIO)
		n_pins = LAN743X_PTP_N_GPIO;

	क्रम (i = 0; i < n_pins; i++) अणु
		काष्ठा ptp_pin_desc *ptp_pin = &ptp->pin_config[i];

		snम_लिखो(ptp_pin->name,
			 माप(ptp_pin->name), "lan743x_ptp_pin_%02d", i);
		ptp_pin->index = i;
		ptp_pin->func = PTP_PF_NONE;
	पूर्ण

	ptp->ptp_घड़ी_info.owner = THIS_MODULE;
	snम_लिखो(ptp->ptp_घड़ी_info.name, 16, "%pm",
		 adapter->netdev->dev_addr);
	ptp->ptp_घड़ी_info.max_adj = LAN743X_PTP_MAX_FREQ_ADJ_IN_PPB;
	ptp->ptp_घड़ी_info.n_alarm = 0;
	ptp->ptp_घड़ी_info.n_ext_ts = 0;
	ptp->ptp_घड़ी_info.n_per_out = LAN743X_PTP_N_EVENT_CHAN;
	ptp->ptp_घड़ी_info.n_pins = n_pins;
	ptp->ptp_घड़ी_info.pps = 0;
	ptp->ptp_घड़ी_info.pin_config = ptp->pin_config;
	ptp->ptp_घड़ी_info.adjfine = lan743x_ptpci_adjfine;
	ptp->ptp_घड़ी_info.adjfreq = lan743x_ptpci_adjfreq;
	ptp->ptp_घड़ी_info.adjसमय = lan743x_ptpci_adjसमय;
	ptp->ptp_घड़ी_info.समय_लो64 = lan743x_ptpci_समय_लो64;
	ptp->ptp_घड़ी_info.अ_लोrosststamp = शून्य;
	ptp->ptp_घड़ी_info.समय_रखो64 = lan743x_ptpci_समय_रखो64;
	ptp->ptp_घड़ी_info.enable = lan743x_ptpci_enable;
	ptp->ptp_घड़ी_info.करो_aux_work = lan743x_ptpci_करो_aux_work;
	ptp->ptp_घड़ी_info.verअगरy = lan743x_ptpci_verअगरy_pin_config;

	ptp->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&ptp->ptp_घड़ी_info,
					    &adapter->pdev->dev);

	अगर (IS_ERR(ptp->ptp_घड़ी)) अणु
		netअगर_err(adapter, अगरup, adapter->netdev,
			  "ptp_clock_register failed\n");
		जाओ करोne;
	पूर्ण
	ptp->flags |= PTP_FLAG_PTP_CLOCK_REGISTERED;
	netअगर_info(adapter, अगरup, adapter->netdev,
		   "successfully registered ptp clock\n");

	वापस 0;
करोne:
	lan743x_ptp_बंद(adapter);
	वापस ret;
पूर्ण

व्योम lan743x_ptp_बंद(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	पूर्णांक index;

	अगर (IS_ENABLED(CONFIG_PTP_1588_CLOCK) &&
	    (ptp->flags & PTP_FLAG_PTP_CLOCK_REGISTERED)) अणु
		ptp_घड़ी_unरेजिस्टर(ptp->ptp_घड़ी);
		ptp->ptp_घड़ी = शून्य;
		ptp->flags &= ~PTP_FLAG_PTP_CLOCK_REGISTERED;
		netअगर_info(adapter, drv, adapter->netdev,
			   "ptp clock unregister\n");
	पूर्ण

	अगर (ptp->flags & PTP_FLAG_ISR_ENABLED) अणु
		lan743x_csr_ग_लिखो(adapter, PTP_INT_EN_CLR,
				  PTP_INT_BIT_TX_SWTS_ERR_ |
				  PTP_INT_BIT_TX_TS_);
		lan743x_csr_ग_लिखो(adapter, INT_EN_CLR, INT_BIT_1588_);
		ptp->flags &= ~PTP_FLAG_ISR_ENABLED;
	पूर्ण

	/* clean up pending बारtamp requests */
	lan743x_ptp_tx_ts_complete(adapter);
	spin_lock_bh(&ptp->tx_ts_lock);
	क्रम (index = 0;
		index < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS;
		index++) अणु
		काष्ठा sk_buff *skb = ptp->tx_ts_skb_queue[index];

		dev_kमुक्त_skb(skb);
		ptp->tx_ts_skb_queue[index] = शून्य;
		ptp->tx_ts_seconds_queue[index] = 0;
		ptp->tx_ts_nseconds_queue[index] = 0;
	पूर्ण
	ptp->tx_ts_skb_queue_size = 0;
	ptp->tx_ts_queue_size = 0;
	ptp->pending_tx_बारtamps = 0;
	spin_unlock_bh(&ptp->tx_ts_lock);

	lan743x_led_mux_restore(adapter);

	lan743x_ptp_disable(adapter);
पूर्ण

अटल व्योम lan743x_ptp_set_sync_ts_insert(काष्ठा lan743x_adapter *adapter,
					   bool ts_insert_enable)
अणु
	u32 ptp_tx_mod = lan743x_csr_पढ़ो(adapter, PTP_TX_MOD);

	अगर (ts_insert_enable)
		ptp_tx_mod |= PTP_TX_MOD_TX_PTP_SYNC_TS_INSERT_;
	अन्यथा
		ptp_tx_mod &= ~PTP_TX_MOD_TX_PTP_SYNC_TS_INSERT_;

	lan743x_csr_ग_लिखो(adapter, PTP_TX_MOD, ptp_tx_mod);
पूर्ण

अटल bool lan743x_ptp_is_enabled(काष्ठा lan743x_adapter *adapter)
अणु
	अगर (lan743x_csr_पढ़ो(adapter, PTP_CMD_CTL) & PTP_CMD_CTL_PTP_ENABLE_)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम lan743x_ptp_enable(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);

	अगर (lan743x_ptp_is_enabled(adapter)) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "PTP already enabled\n");
		जाओ करोne;
	पूर्ण
	lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_ENABLE_);
करोne:
	mutex_unlock(&ptp->command_lock);
पूर्ण

अटल व्योम lan743x_ptp_disable(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);
	अगर (!lan743x_ptp_is_enabled(adapter)) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "PTP already disabled\n");
		जाओ करोne;
	पूर्ण
	lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_DISABLE_);
	lan743x_ptp_रुको_till_cmd_करोne(adapter, PTP_CMD_CTL_PTP_ENABLE_);
करोne:
	mutex_unlock(&ptp->command_lock);
पूर्ण

अटल व्योम lan743x_ptp_reset(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);

	अगर (lan743x_ptp_is_enabled(adapter)) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "Attempting reset while enabled\n");
		जाओ करोne;
	पूर्ण

	lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_RESET_);
	lan743x_ptp_रुको_till_cmd_करोne(adapter, PTP_CMD_CTL_PTP_RESET_);
करोne:
	mutex_unlock(&ptp->command_lock);
पूर्ण

अटल व्योम lan743x_ptp_घड़ी_set(काष्ठा lan743x_adapter *adapter,
				  u32 seconds, u32 nano_seconds,
				  u32 sub_nano_seconds)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	mutex_lock(&ptp->command_lock);

	lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_SEC, seconds);
	lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_NS, nano_seconds);
	lan743x_csr_ग_लिखो(adapter, PTP_CLOCK_SUBNS, sub_nano_seconds);

	lan743x_csr_ग_लिखो(adapter, PTP_CMD_CTL, PTP_CMD_CTL_PTP_CLOCK_LOAD_);
	lan743x_ptp_रुको_till_cmd_करोne(adapter, PTP_CMD_CTL_PTP_CLOCK_LOAD_);
	mutex_unlock(&ptp->command_lock);
पूर्ण

bool lan743x_ptp_request_tx_बारtamp(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;
	bool result = false;

	spin_lock_bh(&ptp->tx_ts_lock);
	अगर (ptp->pending_tx_बारtamps < LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS) अणु
		/* request granted */
		ptp->pending_tx_बारtamps++;
		result = true;
	पूर्ण
	spin_unlock_bh(&ptp->tx_ts_lock);
	वापस result;
पूर्ण

व्योम lan743x_ptp_unrequest_tx_बारtamp(काष्ठा lan743x_adapter *adapter)
अणु
	काष्ठा lan743x_ptp *ptp = &adapter->ptp;

	spin_lock_bh(&ptp->tx_ts_lock);
	अगर (ptp->pending_tx_बारtamps > 0)
		ptp->pending_tx_बारtamps--;
	अन्यथा
		netअगर_err(adapter, drv, adapter->netdev,
			  "unrequest failed, pending_tx_timestamps==0\n");
	spin_unlock_bh(&ptp->tx_ts_lock);
पूर्ण

व्योम lan743x_ptp_tx_बारtamp_skb(काष्ठा lan743x_adapter *adapter,
				  काष्ठा sk_buff *skb, bool ignore_sync)
अणु
	lan743x_ptp_tx_ts_enqueue_skb(adapter, skb, ignore_sync);

	lan743x_ptp_tx_ts_complete(adapter);
पूर्ण

पूर्णांक lan743x_ptp_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा lan743x_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;
	पूर्णांक ret = 0;
	पूर्णांक index;

	अगर (!अगरr) अणु
		netअगर_err(adapter, drv, adapter->netdev,
			  "SIOCSHWTSTAMP, ifr == NULL\n");
		वापस -EINVAL;
	पूर्ण

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	अगर (config.flags) अणु
		netअगर_warn(adapter, drv, adapter->netdev,
			   "ignoring hwtstamp_config.flags == 0x%08X, expected 0\n",
			   config.flags);
	पूर्ण

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		क्रम (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_बारtamping_mode(&adapter->tx[index],
							 false, false);
		lan743x_ptp_set_sync_ts_insert(adapter, false);
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		क्रम (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_बारtamping_mode(&adapter->tx[index],
							 true, false);
		lan743x_ptp_set_sync_ts_insert(adapter, false);
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_SYNC:
		क्रम (index = 0; index < LAN743X_MAX_TX_CHANNELS;
			index++)
			lan743x_tx_set_बारtamping_mode(&adapter->tx[index],
							 true, true);

		lan743x_ptp_set_sync_ts_insert(adapter, true);
		अवरोध;
	हाल HWTSTAMP_TX_ONESTEP_P2P:
		ret = -दुस्फल;
		अवरोध;
	शेष:
		netअगर_warn(adapter, drv, adapter->netdev,
			   "  tx_type = %d, UNKNOWN\n", config.tx_type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!ret)
		वापस copy_to_user(अगरr->अगरr_data, &config,
			माप(config)) ? -EFAULT : 0;
	वापस ret;
पूर्ण
