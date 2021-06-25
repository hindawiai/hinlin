<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2021, Linaro Ltd <loic.poulain@linaro.org> */
#समावेश <linux/kernel.h>
#समावेश <linux/mhi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/wwan.h>

/* MHI wwan flags */
क्रमागत mhi_wwan_flags अणु
	MHI_WWAN_DL_CAP,
	MHI_WWAN_UL_CAP,
	MHI_WWAN_RX_REFILL,
पूर्ण;

#घोषणा MHI_WWAN_MAX_MTU	0x8000

काष्ठा mhi_wwan_dev अणु
	/* Lower level is a mhi dev, upper level is a wwan port */
	काष्ठा mhi_device *mhi_dev;
	काष्ठा wwan_port *wwan_port;

	/* State and capabilities */
	अचिन्हित दीर्घ flags;
	माप_प्रकार mtu;

	/* Protect against concurrent TX and TX-completion (bh) */
	spinlock_t tx_lock;

	/* Protect RX budget and rx_refill scheduling */
	spinlock_t rx_lock;
	काष्ठा work_काष्ठा rx_refill;

	/* RX budget is initially set to the size of the MHI RX queue and is
	 * used to limit the number of allocated and queued packets. It is
	 * decremented on data queueing and incremented on data release.
	 */
	अचिन्हित पूर्णांक rx_budget;
पूर्ण;

/* Increment RX budget and schedule RX refill अगर necessary */
अटल व्योम mhi_wwan_rx_budget_inc(काष्ठा mhi_wwan_dev *mhiwwan)
अणु
	spin_lock(&mhiwwan->rx_lock);

	mhiwwan->rx_budget++;

	अगर (test_bit(MHI_WWAN_RX_REFILL, &mhiwwan->flags))
		schedule_work(&mhiwwan->rx_refill);

	spin_unlock(&mhiwwan->rx_lock);
पूर्ण

/* Decrement RX budget अगर non-zero and वापस true on success */
अटल bool mhi_wwan_rx_budget_dec(काष्ठा mhi_wwan_dev *mhiwwan)
अणु
	bool ret = false;

	spin_lock(&mhiwwan->rx_lock);

	अगर (mhiwwan->rx_budget) अणु
		mhiwwan->rx_budget--;
		अगर (test_bit(MHI_WWAN_RX_REFILL, &mhiwwan->flags))
			ret = true;
	पूर्ण

	spin_unlock(&mhiwwan->rx_lock);

	वापस ret;
पूर्ण

अटल व्योम __mhi_skb_deकाष्ठाor(काष्ठा sk_buff *skb)
अणु
	/* RX buffer has been consumed, increase the allowed budget */
	mhi_wwan_rx_budget_inc(skb_shinfo(skb)->deकाष्ठाor_arg);
पूर्ण

अटल व्योम mhi_wwan_ctrl_refill_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = container_of(work, काष्ठा mhi_wwan_dev, rx_refill);
	काष्ठा mhi_device *mhi_dev = mhiwwan->mhi_dev;

	जबतक (mhi_wwan_rx_budget_dec(mhiwwan)) अणु
		काष्ठा sk_buff *skb;

		skb = alloc_skb(mhiwwan->mtu, GFP_KERNEL);
		अगर (!skb) अणु
			mhi_wwan_rx_budget_inc(mhiwwan);
			अवरोध;
		पूर्ण

		/* To prevent unlimited buffer allocation अगर nothing consumes
		 * the RX buffers (passed to WWAN core), track their lअगरespan
		 * to not allocate more than allowed budget.
		 */
		skb->deकाष्ठाor = __mhi_skb_deकाष्ठाor;
		skb_shinfo(skb)->deकाष्ठाor_arg = mhiwwan;

		अगर (mhi_queue_skb(mhi_dev, DMA_FROM_DEVICE, skb, mhiwwan->mtu, MHI_EOT)) अणु
			dev_err(&mhi_dev->dev, "Failed to queue buffer\n");
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mhi_wwan_ctrl_start(काष्ठा wwan_port *port)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = wwan_port_get_drvdata(port);
	पूर्णांक ret;

	/* Start mhi device's channel(s) */
	ret = mhi_prepare_क्रम_transfer(mhiwwan->mhi_dev);
	अगर (ret)
		वापस ret;

	/* Don't allocate more buffers than MHI channel queue size */
	mhiwwan->rx_budget = mhi_get_मुक्त_desc_count(mhiwwan->mhi_dev, DMA_FROM_DEVICE);

	/* Add buffers to the MHI inbound queue */
	अगर (test_bit(MHI_WWAN_DL_CAP, &mhiwwan->flags)) अणु
		set_bit(MHI_WWAN_RX_REFILL, &mhiwwan->flags);
		mhi_wwan_ctrl_refill_work(&mhiwwan->rx_refill);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mhi_wwan_ctrl_stop(काष्ठा wwan_port *port)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = wwan_port_get_drvdata(port);

	spin_lock(&mhiwwan->rx_lock);
	clear_bit(MHI_WWAN_RX_REFILL, &mhiwwan->flags);
	spin_unlock(&mhiwwan->rx_lock);

	cancel_work_sync(&mhiwwan->rx_refill);

	mhi_unprepare_from_transfer(mhiwwan->mhi_dev);
पूर्ण

अटल पूर्णांक mhi_wwan_ctrl_tx(काष्ठा wwan_port *port, काष्ठा sk_buff *skb)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = wwan_port_get_drvdata(port);
	पूर्णांक ret;

	अगर (skb->len > mhiwwan->mtu)
		वापस -EMSGSIZE;

	अगर (!test_bit(MHI_WWAN_UL_CAP, &mhiwwan->flags))
		वापस -EOPNOTSUPP;

	/* Queue the packet क्रम MHI transfer and check fullness of the queue */
	spin_lock_bh(&mhiwwan->tx_lock);
	ret = mhi_queue_skb(mhiwwan->mhi_dev, DMA_TO_DEVICE, skb, skb->len, MHI_EOT);
	अगर (mhi_queue_is_full(mhiwwan->mhi_dev, DMA_TO_DEVICE))
		wwan_port_txoff(port);
	spin_unlock_bh(&mhiwwan->tx_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा wwan_port_ops wwan_pops = अणु
	.start = mhi_wwan_ctrl_start,
	.stop = mhi_wwan_ctrl_stop,
	.tx = mhi_wwan_ctrl_tx,
पूर्ण;

अटल व्योम mhi_ul_xfer_cb(काष्ठा mhi_device *mhi_dev,
			   काष्ठा mhi_result *mhi_result)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = dev_get_drvdata(&mhi_dev->dev);
	काष्ठा wwan_port *port = mhiwwan->wwan_port;
	काष्ठा sk_buff *skb = mhi_result->buf_addr;

	dev_dbg(&mhi_dev->dev, "%s: status: %d xfer_len: %zu\n", __func__,
		mhi_result->transaction_status, mhi_result->bytes_xferd);

	/* MHI core has करोne with the buffer, release it */
	consume_skb(skb);

	/* There is likely new slot available in the MHI queue, re-allow TX */
	spin_lock_bh(&mhiwwan->tx_lock);
	अगर (!mhi_queue_is_full(mhiwwan->mhi_dev, DMA_TO_DEVICE))
		wwan_port_txon(port);
	spin_unlock_bh(&mhiwwan->tx_lock);
पूर्ण

अटल व्योम mhi_dl_xfer_cb(काष्ठा mhi_device *mhi_dev,
			   काष्ठा mhi_result *mhi_result)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = dev_get_drvdata(&mhi_dev->dev);
	काष्ठा wwan_port *port = mhiwwan->wwan_port;
	काष्ठा sk_buff *skb = mhi_result->buf_addr;

	dev_dbg(&mhi_dev->dev, "%s: status: %d receive_len: %zu\n", __func__,
		mhi_result->transaction_status, mhi_result->bytes_xferd);

	अगर (mhi_result->transaction_status &&
	    mhi_result->transaction_status != -EOVERFLOW) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* MHI core करोes not update skb->len, करो it beक्रमe क्रमward */
	skb_put(skb, mhi_result->bytes_xferd);
	wwan_port_rx(port, skb);

	/* Do not increment rx budget nor refill RX buffers now, रुको क्रम the
	 * buffer to be consumed. Done from __mhi_skb_deकाष्ठाor().
	 */
पूर्ण

अटल पूर्णांक mhi_wwan_ctrl_probe(काष्ठा mhi_device *mhi_dev,
			       स्थिर काष्ठा mhi_device_id *id)
अणु
	काष्ठा mhi_controller *cntrl = mhi_dev->mhi_cntrl;
	काष्ठा mhi_wwan_dev *mhiwwan;
	काष्ठा wwan_port *port;

	mhiwwan = kzalloc(माप(*mhiwwan), GFP_KERNEL);
	अगर (!mhiwwan)
		वापस -ENOMEM;

	mhiwwan->mhi_dev = mhi_dev;
	mhiwwan->mtu = MHI_WWAN_MAX_MTU;
	INIT_WORK(&mhiwwan->rx_refill, mhi_wwan_ctrl_refill_work);
	spin_lock_init(&mhiwwan->tx_lock);
	spin_lock_init(&mhiwwan->rx_lock);

	अगर (mhi_dev->dl_chan)
		set_bit(MHI_WWAN_DL_CAP, &mhiwwan->flags);
	अगर (mhi_dev->ul_chan)
		set_bit(MHI_WWAN_UL_CAP, &mhiwwan->flags);

	dev_set_drvdata(&mhi_dev->dev, mhiwwan);

	/* Register as a wwan port, id->driver_data contains wwan port type */
	port = wwan_create_port(&cntrl->mhi_dev->dev, id->driver_data,
				&wwan_pops, mhiwwan);
	अगर (IS_ERR(port)) अणु
		kमुक्त(mhiwwan);
		वापस PTR_ERR(port);
	पूर्ण

	mhiwwan->wwan_port = port;

	वापस 0;
पूर्ण;

अटल व्योम mhi_wwan_ctrl_हटाओ(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_wwan_dev *mhiwwan = dev_get_drvdata(&mhi_dev->dev);

	wwan_हटाओ_port(mhiwwan->wwan_port);
	kमुक्त(mhiwwan);
पूर्ण

अटल स्थिर काष्ठा mhi_device_id mhi_wwan_ctrl_match_table[] = अणु
	अणु .chan = "DUN", .driver_data = WWAN_PORT_AT पूर्ण,
	अणु .chan = "MBIM", .driver_data = WWAN_PORT_MBIM पूर्ण,
	अणु .chan = "QMI", .driver_data = WWAN_PORT_QMI पूर्ण,
	अणु .chan = "DIAG", .driver_data = WWAN_PORT_QCDM पूर्ण,
	अणु .chan = "FIREHOSE", .driver_data = WWAN_PORT_FIREHOSE पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(mhi, mhi_wwan_ctrl_match_table);

अटल काष्ठा mhi_driver mhi_wwan_ctrl_driver = अणु
	.id_table = mhi_wwan_ctrl_match_table,
	.हटाओ = mhi_wwan_ctrl_हटाओ,
	.probe = mhi_wwan_ctrl_probe,
	.ul_xfer_cb = mhi_ul_xfer_cb,
	.dl_xfer_cb = mhi_dl_xfer_cb,
	.driver = अणु
		.name = "mhi_wwan_ctrl",
	पूर्ण,
पूर्ण;

module_mhi_driver(mhi_wwan_ctrl_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MHI WWAN CTRL Driver");
MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
