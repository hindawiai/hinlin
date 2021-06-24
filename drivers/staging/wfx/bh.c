<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Interrupt bottom half (BH).
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/gpio/consumer.h>
#समावेश <net/mac80211.h>

#समावेश "bh.h"
#समावेश "wfx.h"
#समावेश "hwio.h"
#समावेश "traces.h"
#समावेश "hif_rx.h"
#समावेश "hif_api_cmd.h"

अटल व्योम device_wakeup(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक max_retry = 3;

	अगर (!wdev->pdata.gpio_wakeup)
		वापस;
	अगर (gpiod_get_value_cansleep(wdev->pdata.gpio_wakeup) > 0)
		वापस;

	अगर (wfx_api_older_than(wdev, 1, 4)) अणु
		gpiod_set_value_cansleep(wdev->pdata.gpio_wakeup, 1);
		अगर (!completion_करोne(&wdev->hअगर.ctrl_पढ़ोy))
			usleep_range(2000, 2500);
		वापस;
	पूर्ण
	क्रम (;;) अणु
		gpiod_set_value_cansleep(wdev->pdata.gpio_wakeup, 1);
		// completion.h करोes not provide any function to रुको
		// completion without consume it (a kind of
		// रुको_क्रम_completion_करोne_समयout()). So we have to emulate
		// it.
		अगर (रुको_क्रम_completion_समयout(&wdev->hअगर.ctrl_पढ़ोy,
						msecs_to_jअगरfies(2))) अणु
			complete(&wdev->hअगर.ctrl_पढ़ोy);
			वापस;
		पूर्ण अन्यथा अगर (max_retry-- > 0) अणु
			// Older firmwares have a race in sleep/wake-up process.
			// Reकरो the process is sufficient to unमुक्तze the
			// chip.
			dev_err(wdev->dev, "timeout while wake up chip\n");
			gpiod_set_value_cansleep(wdev->pdata.gpio_wakeup, 0);
			usleep_range(2000, 2500);
		पूर्ण अन्यथा अणु
			dev_err(wdev->dev, "max wake-up retries reached\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम device_release(काष्ठा wfx_dev *wdev)
अणु
	अगर (!wdev->pdata.gpio_wakeup)
		वापस;

	gpiod_set_value_cansleep(wdev->pdata.gpio_wakeup, 0);
पूर्ण

अटल पूर्णांक rx_helper(काष्ठा wfx_dev *wdev, माप_प्रकार पढ़ो_len, पूर्णांक *is_cnf)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hअगर_msg *hअगर;
	माप_प्रकार alloc_len;
	माप_प्रकार computed_len;
	पूर्णांक release_count;
	पूर्णांक piggyback = 0;

	WARN(पढ़ो_len > round_करोwn(0xFFF, 2) * माप(u16),
	     "%s: request exceed WFx capability", __func__);

	// Add 2 to take पूर्णांकo account piggyback size
	alloc_len = wdev->hwbus_ops->align_size(wdev->hwbus_priv, पढ़ो_len + 2);
	skb = dev_alloc_skb(alloc_len);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (wfx_data_पढ़ो(wdev, skb->data, alloc_len))
		जाओ err;

	piggyback = le16_to_cpup((__le16 *)(skb->data + alloc_len - 2));
	_trace_piggyback(piggyback, false);

	hअगर = (काष्ठा hअगर_msg *)skb->data;
	WARN(hअगर->encrypted & 0x3, "encryption is unsupported");
	अगर (WARN(पढ़ो_len < माप(काष्ठा hअगर_msg), "corrupted read"))
		जाओ err;
	computed_len = le16_to_cpu(hअगर->len);
	computed_len = round_up(computed_len, 2);
	अगर (computed_len != पढ़ो_len) अणु
		dev_err(wdev->dev, "inconsistent message length: %zu != %zu\n",
			computed_len, पढ़ो_len);
		prपूर्णांक_hex_dump(KERN_INFO, "hif: ", DUMP_PREFIX_OFFSET, 16, 1,
			       hअगर, पढ़ो_len, true);
		जाओ err;
	पूर्ण

	अगर (!(hअगर->id & HIF_ID_IS_INDICATION)) अणु
		(*is_cnf)++;
		अगर (hअगर->id == HIF_CNF_ID_MULTI_TRANSMIT)
			release_count = ((काष्ठा hअगर_cnf_multi_transmit *)hअगर->body)->num_tx_confs;
		अन्यथा
			release_count = 1;
		WARN(wdev->hअगर.tx_buffers_used < release_count, "corrupted buffer counter");
		wdev->hअगर.tx_buffers_used -= release_count;
	पूर्ण
	_trace_hअगर_recv(hअगर, wdev->hअगर.tx_buffers_used);

	अगर (hअगर->id != HIF_IND_ID_EXCEPTION && hअगर->id != HIF_IND_ID_ERROR) अणु
		अगर (hअगर->seqnum != wdev->hअगर.rx_seqnum)
			dev_warn(wdev->dev, "wrong message sequence: %d != %d\n",
				 hअगर->seqnum, wdev->hअगर.rx_seqnum);
		wdev->hअगर.rx_seqnum = (hअगर->seqnum + 1) % (HIF_COUNTER_MAX + 1);
	पूर्ण

	skb_put(skb, le16_to_cpu(hअगर->len));
	// wfx_handle_rx takes care on SKB liveसमय
	wfx_handle_rx(wdev, skb);
	अगर (!wdev->hअगर.tx_buffers_used)
		wake_up(&wdev->hअगर.tx_buffers_empty);

	वापस piggyback;

err:
	अगर (skb)
		dev_kमुक्त_skb(skb);
	वापस -EIO;
पूर्ण

अटल पूर्णांक bh_work_rx(काष्ठा wfx_dev *wdev, पूर्णांक max_msg, पूर्णांक *num_cnf)
अणु
	माप_प्रकार len;
	पूर्णांक i;
	पूर्णांक ctrl_reg, piggyback;

	piggyback = 0;
	क्रम (i = 0; i < max_msg; i++) अणु
		अगर (piggyback & CTRL_NEXT_LEN_MASK)
			ctrl_reg = piggyback;
		अन्यथा अगर (try_रुको_क्रम_completion(&wdev->hअगर.ctrl_पढ़ोy))
			ctrl_reg = atomic_xchg(&wdev->hअगर.ctrl_reg, 0);
		अन्यथा
			ctrl_reg = 0;
		अगर (!(ctrl_reg & CTRL_NEXT_LEN_MASK))
			वापस i;
		// ctrl_reg units are 16bits words
		len = (ctrl_reg & CTRL_NEXT_LEN_MASK) * 2;
		piggyback = rx_helper(wdev, len, num_cnf);
		अगर (piggyback < 0)
			वापस i;
		अगर (!(piggyback & CTRL_WLAN_READY))
			dev_err(wdev->dev, "unexpected piggyback value: ready bit not set: %04x\n",
				piggyback);
	पूर्ण
	अगर (piggyback & CTRL_NEXT_LEN_MASK) अणु
		ctrl_reg = atomic_xchg(&wdev->hअगर.ctrl_reg, piggyback);
		complete(&wdev->hअगर.ctrl_पढ़ोy);
		अगर (ctrl_reg)
			dev_err(wdev->dev, "unexpected IRQ happened: %04x/%04x\n",
				ctrl_reg, piggyback);
	पूर्ण
	वापस i;
पूर्ण

अटल व्योम tx_helper(काष्ठा wfx_dev *wdev, काष्ठा hअगर_msg *hअगर)
अणु
	पूर्णांक ret;
	व्योम *data;
	bool is_encrypted = false;
	माप_प्रकार len = le16_to_cpu(hअगर->len);

	WARN(len < माप(*hअगर), "try to send corrupted data");

	hअगर->seqnum = wdev->hअगर.tx_seqnum;
	wdev->hअगर.tx_seqnum = (wdev->hअगर.tx_seqnum + 1) % (HIF_COUNTER_MAX + 1);

	data = hअगर;
	WARN(len > wdev->hw_caps.size_inp_ch_buf,
	     "%s: request exceed WFx capability: %zu > %d\n", __func__,
	     len, wdev->hw_caps.size_inp_ch_buf);
	len = wdev->hwbus_ops->align_size(wdev->hwbus_priv, len);
	ret = wfx_data_ग_लिखो(wdev, data, len);
	अगर (ret)
		जाओ end;

	wdev->hअगर.tx_buffers_used++;
	_trace_hअगर_send(hअगर, wdev->hअगर.tx_buffers_used);
end:
	अगर (is_encrypted)
		kमुक्त(data);
पूर्ण

अटल पूर्णांक bh_work_tx(काष्ठा wfx_dev *wdev, पूर्णांक max_msg)
अणु
	काष्ठा hअगर_msg *hअगर;
	पूर्णांक i;

	क्रम (i = 0; i < max_msg; i++) अणु
		hअगर = शून्य;
		अगर (wdev->hअगर.tx_buffers_used < wdev->hw_caps.num_inp_ch_bufs) अणु
			अगर (try_रुको_क्रम_completion(&wdev->hअगर_cmd.पढ़ोy)) अणु
				WARN(!mutex_is_locked(&wdev->hअगर_cmd.lock), "data locking error");
				hअगर = wdev->hअगर_cmd.buf_send;
			पूर्ण अन्यथा अणु
				hअगर = wfx_tx_queues_get(wdev);
			पूर्ण
		पूर्ण
		अगर (!hअगर)
			वापस i;
		tx_helper(wdev, hअगर);
	पूर्ण
	वापस i;
पूर्ण

/* In SDIO mode, it is necessary to make an access to a रेजिस्टर to acknowledge
 * last received message. It could be possible to restrict this acknowledge to
 * SDIO mode and only अगर last operation was rx.
 */
अटल व्योम ack_sdio_data(काष्ठा wfx_dev *wdev)
अणु
	u32 cfg_reg;

	config_reg_पढ़ो(wdev, &cfg_reg);
	अगर (cfg_reg & 0xFF) अणु
		dev_warn(wdev->dev, "chip reports errors: %02x\n",
			 cfg_reg & 0xFF);
		config_reg_ग_लिखो_bits(wdev, 0xFF, 0x00);
	पूर्ण
पूर्ण

अटल व्योम bh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wfx_dev *wdev = container_of(work, काष्ठा wfx_dev, hअगर.bh);
	पूर्णांक stats_req = 0, stats_cnf = 0, stats_ind = 0;
	bool release_chip = false, last_op_is_rx = false;
	पूर्णांक num_tx, num_rx;

	device_wakeup(wdev);
	करो अणु
		num_tx = bh_work_tx(wdev, 32);
		stats_req += num_tx;
		अगर (num_tx)
			last_op_is_rx = false;
		num_rx = bh_work_rx(wdev, 32, &stats_cnf);
		stats_ind += num_rx;
		अगर (num_rx)
			last_op_is_rx = true;
	पूर्ण जबतक (num_rx || num_tx);
	stats_ind -= stats_cnf;

	अगर (last_op_is_rx)
		ack_sdio_data(wdev);
	अगर (!wdev->hअगर.tx_buffers_used && !work_pending(work)) अणु
		device_release(wdev);
		release_chip = true;
	पूर्ण
	_trace_bh_stats(stats_ind, stats_req, stats_cnf,
			wdev->hअगर.tx_buffers_used, release_chip);
पूर्ण

/*
 * An IRQ from chip did occur
 */
व्योम wfx_bh_request_rx(काष्ठा wfx_dev *wdev)
अणु
	u32 cur, prev;

	control_reg_पढ़ो(wdev, &cur);
	prev = atomic_xchg(&wdev->hअगर.ctrl_reg, cur);
	complete(&wdev->hअगर.ctrl_पढ़ोy);
	queue_work(प्रणाली_highpri_wq, &wdev->hअगर.bh);

	अगर (!(cur & CTRL_NEXT_LEN_MASK))
		dev_err(wdev->dev, "unexpected control register value: length field is 0: %04x\n",
			cur);
	अगर (prev != 0)
		dev_err(wdev->dev, "received IRQ but previous data was not (yet) read: %04x/%04x\n",
			prev, cur);
पूर्ण

/*
 * Driver want to send data
 */
व्योम wfx_bh_request_tx(काष्ठा wfx_dev *wdev)
अणु
	queue_work(प्रणाली_highpri_wq, &wdev->hअगर.bh);
पूर्ण

/*
 * If IRQ is not available, this function allow to manually poll the control
 * रेजिस्टर and simulate an IRQ ahen an event happened.
 *
 * Note that the device has a bug: If an IRQ उठाओ जबतक host पढ़ो control
 * रेजिस्टर, the IRQ is lost. So, use this function carefully (only duing
 * device initialisation).
 */
व्योम wfx_bh_poll_irq(काष्ठा wfx_dev *wdev)
अणु
	kसमय_प्रकार now, start;
	u32 reg;

	WARN(!wdev->poll_irq, "unexpected IRQ polling can mask IRQ");
	start = kसमय_get();
	क्रम (;;) अणु
		control_reg_पढ़ो(wdev, &reg);
		now = kसमय_get();
		अगर (reg & 0xFFF)
			अवरोध;
		अगर (kसमय_after(now, kसमय_add_ms(start, 1000))) अणु
			dev_err(wdev->dev, "time out while polling control register\n");
			वापस;
		पूर्ण
		udelay(200);
	पूर्ण
	wfx_bh_request_rx(wdev);
पूर्ण

व्योम wfx_bh_रेजिस्टर(काष्ठा wfx_dev *wdev)
अणु
	INIT_WORK(&wdev->hअगर.bh, bh_work);
	init_completion(&wdev->hअगर.ctrl_पढ़ोy);
	init_रुकोqueue_head(&wdev->hअगर.tx_buffers_empty);
पूर्ण

व्योम wfx_bh_unरेजिस्टर(काष्ठा wfx_dev *wdev)
अणु
	flush_work(&wdev->hअगर.bh);
पूर्ण
