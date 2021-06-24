<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:  Daniel Martensson
 *	    Dmitry.Tarnyagin  / dmitry.tarnyagin@lockless.no
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/समयr.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/caअगर_hsi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Martensson");
MODULE_DESCRIPTION("CAIF HSI driver");

/* Returns the number of padding bytes क्रम alignment. */
#घोषणा PAD_POW2(x, घात) ((((x)&((घात)-1)) == 0) ? 0 :\
				(((घात)-((x)&((घात)-1)))))

अटल स्थिर काष्ठा cfhsi_config  hsi_शेष_config = अणु

	/* Inactivity समयout on HSI, ms */
	.inactivity_समयout = HZ,

	/* Aggregation समयout (ms) of zero means no aggregation is करोne*/
	.aggregation_समयout = 1,

	/*
	 * HSI link layer flow-control thresholds.
	 * Threshold values क्रम the HSI packet queue. Flow-control will be
	 * निश्चितed when the number of packets exceeds q_high_mark. It will
	 * not be de-निश्चितed beक्रमe the number of packets drops below
	 * q_low_mark.
	 * Warning: A high threshold value might increase throughput but it
	 * will at the same समय prevent channel prioritization and increase
	 * the risk of flooding the modem. The high threshold should be above
	 * the low.
	 */
	.q_high_mark = 100,
	.q_low_mark = 50,

	/*
	 * HSI padding options.
	 * Warning: must be a base of 2 (& operation used) and can not be zero !
	 */
	.head_align = 4,
	.tail_align = 4,
पूर्ण;

#घोषणा ON 1
#घोषणा OFF 0

अटल LIST_HEAD(cfhsi_list);

अटल व्योम cfhsi_inactivity_tout(काष्ठा समयr_list *t)
अणु
	काष्ठा cfhsi *cfhsi = from_समयr(cfhsi, t, inactivity_समयr);

	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	/* Schedule घातer करोwn work queue. */
	अगर (!test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		queue_work(cfhsi->wq, &cfhsi->wake_करोwn_work);
पूर्ण

अटल व्योम cfhsi_update_aggregation_stats(काष्ठा cfhsi *cfhsi,
					   स्थिर काष्ठा sk_buff *skb,
					   पूर्णांक direction)
अणु
	काष्ठा caअगर_payload_info *info;
	पूर्णांक hpad, tpad, len;

	info = (काष्ठा caअगर_payload_info *)&skb->cb;
	hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
	tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);
	len = skb->len + hpad + tpad;

	अगर (direction > 0)
		cfhsi->aggregation_len += len;
	अन्यथा अगर (direction < 0)
		cfhsi->aggregation_len -= len;
पूर्ण

अटल bool cfhsi_can_send_aggregate(काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक i;

	अगर (cfhsi->cfg.aggregation_समयout == 0)
		वापस true;

	क्रम (i = 0; i < CFHSI_PRIO_BEBK; ++i) अणु
		अगर (cfhsi->qhead[i].qlen)
			वापस true;
	पूर्ण

	/* TODO: Use aggregation_len instead */
	अगर (cfhsi->qhead[CFHSI_PRIO_BEBK].qlen >= CFHSI_MAX_PKTS)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा sk_buff *cfhsi_dequeue(काष्ठा cfhsi *cfhsi)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < CFHSI_PRIO_LAST; ++i) अणु
		skb = skb_dequeue(&cfhsi->qhead[i]);
		अगर (skb)
			अवरोध;
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक cfhsi_tx_queue_len(काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक i, len = 0;
	क्रम (i = 0; i < CFHSI_PRIO_LAST; ++i)
		len += skb_queue_len(&cfhsi->qhead[i]);
	वापस len;
पूर्ण

अटल व्योम cfhsi_पात_tx(काष्ठा cfhsi *cfhsi)
अणु
	काष्ठा sk_buff *skb;

	क्रम (;;) अणु
		spin_lock_bh(&cfhsi->lock);
		skb = cfhsi_dequeue(cfhsi);
		अगर (!skb)
			अवरोध;

		cfhsi->ndev->stats.tx_errors++;
		cfhsi->ndev->stats.tx_dropped++;
		cfhsi_update_aggregation_stats(cfhsi, skb, -1);
		spin_unlock_bh(&cfhsi->lock);
		kमुक्त_skb(skb);
	पूर्ण
	cfhsi->tx_state = CFHSI_TX_STATE_IDLE;
	अगर (!test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		mod_समयr(&cfhsi->inactivity_समयr,
			jअगरfies + cfhsi->cfg.inactivity_समयout);
	spin_unlock_bh(&cfhsi->lock);
पूर्ण

अटल पूर्णांक cfhsi_flush_fअगरo(काष्ठा cfhsi *cfhsi)
अणु
	अक्षर buffer[32]; /* Any reasonable value */
	माप_प्रकार fअगरo_occupancy;
	पूर्णांक ret;

	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	करो अणु
		ret = cfhsi->ops->cfhsi_fअगरo_occupancy(cfhsi->ops,
				&fअगरo_occupancy);
		अगर (ret) अणु
			netdev_warn(cfhsi->ndev,
				"%s: can't get FIFO occupancy: %d.\n",
				__func__, ret);
			अवरोध;
		पूर्ण अन्यथा अगर (!fअगरo_occupancy)
			/* No more data, निकासting normally */
			अवरोध;

		fअगरo_occupancy = min(माप(buffer), fअगरo_occupancy);
		set_bit(CFHSI_FLUSH_FIFO, &cfhsi->bits);
		ret = cfhsi->ops->cfhsi_rx(buffer, fअगरo_occupancy,
				cfhsi->ops);
		अगर (ret) अणु
			clear_bit(CFHSI_FLUSH_FIFO, &cfhsi->bits);
			netdev_warn(cfhsi->ndev,
				"%s: can't read data: %d.\n",
				__func__, ret);
			अवरोध;
		पूर्ण

		ret = 5 * HZ;
		ret = रुको_event_पूर्णांकerruptible_समयout(cfhsi->flush_fअगरo_रुको,
			 !test_bit(CFHSI_FLUSH_FIFO, &cfhsi->bits), ret);

		अगर (ret < 0) अणु
			netdev_warn(cfhsi->ndev,
				"%s: can't wait for flush complete: %d.\n",
				__func__, ret);
			अवरोध;
		पूर्ण अन्यथा अगर (!ret) अणु
			ret = -ETIMEDOUT;
			netdev_warn(cfhsi->ndev,
				"%s: timeout waiting for flush complete.\n",
				__func__);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	वापस ret;
पूर्ण

अटल पूर्णांक cfhsi_tx_frm(काष्ठा cfhsi_desc *desc, काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक nfrms = 0;
	पूर्णांक pld_len = 0;
	काष्ठा sk_buff *skb;
	u8 *pfrm = desc->emb_frm + CFHSI_MAX_EMB_FRM_SZ;

	skb = cfhsi_dequeue(cfhsi);
	अगर (!skb)
		वापस 0;

	/* Clear offset. */
	desc->offset = 0;

	/* Check अगर we can embed a CAIF frame. */
	अगर (skb->len < CFHSI_MAX_EMB_FRM_SZ) अणु
		काष्ठा caअगर_payload_info *info;
		पूर्णांक hpad;
		पूर्णांक tpad;

		/* Calculate needed head alignment and tail alignment. */
		info = (काष्ठा caअगर_payload_info *)&skb->cb;

		hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
		tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);

		/* Check अगर frame still fits with added alignment. */
		अगर ((skb->len + hpad + tpad) <= CFHSI_MAX_EMB_FRM_SZ) अणु
			u8 *pemb = desc->emb_frm;
			desc->offset = CFHSI_DESC_SHORT_SZ;
			*pemb = (u8)(hpad - 1);
			pemb += hpad;

			/* Update network statistics. */
			spin_lock_bh(&cfhsi->lock);
			cfhsi->ndev->stats.tx_packets++;
			cfhsi->ndev->stats.tx_bytes += skb->len;
			cfhsi_update_aggregation_stats(cfhsi, skb, -1);
			spin_unlock_bh(&cfhsi->lock);

			/* Copy in embedded CAIF frame. */
			skb_copy_bits(skb, 0, pemb, skb->len);

			/* Consume the SKB */
			consume_skb(skb);
			skb = शून्य;
		पूर्ण
	पूर्ण

	/* Create payload CAIF frames. */
	जबतक (nfrms < CFHSI_MAX_PKTS) अणु
		काष्ठा caअगर_payload_info *info;
		पूर्णांक hpad;
		पूर्णांक tpad;

		अगर (!skb)
			skb = cfhsi_dequeue(cfhsi);

		अगर (!skb)
			अवरोध;

		/* Calculate needed head alignment and tail alignment. */
		info = (काष्ठा caअगर_payload_info *)&skb->cb;

		hpad = 1 + PAD_POW2((info->hdr_len + 1), cfhsi->cfg.head_align);
		tpad = PAD_POW2((skb->len + hpad), cfhsi->cfg.tail_align);

		/* Fill in CAIF frame length in descriptor. */
		desc->cffrm_len[nfrms] = hpad + skb->len + tpad;

		/* Fill head padding inक्रमmation. */
		*pfrm = (u8)(hpad - 1);
		pfrm += hpad;

		/* Update network statistics. */
		spin_lock_bh(&cfhsi->lock);
		cfhsi->ndev->stats.tx_packets++;
		cfhsi->ndev->stats.tx_bytes += skb->len;
		cfhsi_update_aggregation_stats(cfhsi, skb, -1);
		spin_unlock_bh(&cfhsi->lock);

		/* Copy in CAIF frame. */
		skb_copy_bits(skb, 0, pfrm, skb->len);

		/* Update payload length. */
		pld_len += desc->cffrm_len[nfrms];

		/* Update frame poपूर्णांकer. */
		pfrm += skb->len + tpad;

		/* Consume the SKB */
		consume_skb(skb);
		skb = शून्य;

		/* Update number of frames. */
		nfrms++;
	पूर्ण

	/* Unused length fields should be zero-filled (according to SPEC). */
	जबतक (nfrms < CFHSI_MAX_PKTS) अणु
		desc->cffrm_len[nfrms] = 0x0000;
		nfrms++;
	पूर्ण

	/* Check अगर we can piggy-back another descriptor. */
	अगर (cfhsi_can_send_aggregate(cfhsi))
		desc->header |= CFHSI_PIGGY_DESC;
	अन्यथा
		desc->header &= ~CFHSI_PIGGY_DESC;

	वापस CFHSI_DESC_SZ + pld_len;
पूर्ण

अटल व्योम cfhsi_start_tx(काष्ठा cfhsi *cfhsi)
अणु
	काष्ठा cfhsi_desc *desc = (काष्ठा cfhsi_desc *)cfhsi->tx_buf;
	पूर्णांक len, res;

	netdev_dbg(cfhsi->ndev, "%s.\n", __func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	करो अणु
		/* Create HSI frame. */
		len = cfhsi_tx_frm(desc, cfhsi);
		अगर (!len) अणु
			spin_lock_bh(&cfhsi->lock);
			अगर (unlikely(cfhsi_tx_queue_len(cfhsi))) अणु
				spin_unlock_bh(&cfhsi->lock);
				res = -EAGAIN;
				जारी;
			पूर्ण
			cfhsi->tx_state = CFHSI_TX_STATE_IDLE;
			/* Start inactivity समयr. */
			mod_समयr(&cfhsi->inactivity_समयr,
				jअगरfies + cfhsi->cfg.inactivity_समयout);
			spin_unlock_bh(&cfhsi->lock);
			अवरोध;
		पूर्ण

		/* Set up new transfer. */
		res = cfhsi->ops->cfhsi_tx(cfhsi->tx_buf, len, cfhsi->ops);
		अगर (WARN_ON(res < 0))
			netdev_err(cfhsi->ndev, "%s: TX error %d.\n",
				__func__, res);
	पूर्ण जबतक (res < 0);
पूर्ण

अटल व्योम cfhsi_tx_करोne(काष्ठा cfhsi *cfhsi)
अणु
	netdev_dbg(cfhsi->ndev, "%s.\n", __func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	/*
	 * Send flow on अगर flow off has been previously संकेतled
	 * and number of packets is below low water mark.
	 */
	spin_lock_bh(&cfhsi->lock);
	अगर (cfhsi->flow_off_sent &&
			cfhsi_tx_queue_len(cfhsi) <= cfhsi->cfg.q_low_mark &&
			cfhsi->cfdev.flowctrl) अणु

		cfhsi->flow_off_sent = 0;
		cfhsi->cfdev.flowctrl(cfhsi->ndev, ON);
	पूर्ण

	अगर (cfhsi_can_send_aggregate(cfhsi)) अणु
		spin_unlock_bh(&cfhsi->lock);
		cfhsi_start_tx(cfhsi);
	पूर्ण अन्यथा अणु
		mod_समयr(&cfhsi->aggregation_समयr,
			jअगरfies + cfhsi->cfg.aggregation_समयout);
		spin_unlock_bh(&cfhsi->lock);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम cfhsi_tx_करोne_cb(काष्ठा cfhsi_cb_ops *cb_ops)
अणु
	काष्ठा cfhsi *cfhsi;

	cfhsi = container_of(cb_ops, काष्ठा cfhsi, cb_ops);
	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;
	cfhsi_tx_करोne(cfhsi);
पूर्ण

अटल पूर्णांक cfhsi_rx_desc(काष्ठा cfhsi_desc *desc, काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक xfer_sz = 0;
	पूर्णांक nfrms = 0;
	u16 *plen = शून्य;
	u8 *pfrm = शून्य;

	अगर ((desc->header & ~CFHSI_PIGGY_DESC) ||
			(desc->offset > CFHSI_MAX_EMB_FRM_SZ)) अणु
		netdev_err(cfhsi->ndev, "%s: Invalid descriptor.\n",
			__func__);
		वापस -EPROTO;
	पूर्ण

	/* Check क्रम embedded CAIF frame. */
	अगर (desc->offset) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक len = 0;
		pfrm = ((u8 *)desc) + desc->offset;

		/* Remove offset padding. */
		pfrm += *pfrm + 1;

		/* Read length of CAIF frame (little endian). */
		len = *pfrm;
		len |= ((*(pfrm+1)) << 8) & 0xFF00;
		len += 2;	/* Add FCS fields. */

		/* Sanity check length of CAIF frame. */
		अगर (unlikely(len > CFHSI_MAX_CAIF_FRAME_SZ)) अणु
			netdev_err(cfhsi->ndev, "%s: Invalid length.\n",
				__func__);
			वापस -EPROTO;
		पूर्ण

		/* Allocate SKB (OK even in IRQ context). */
		skb = alloc_skb(len + 1, GFP_ATOMIC);
		अगर (!skb) अणु
			netdev_err(cfhsi->ndev, "%s: Out of memory !\n",
				__func__);
			वापस -ENOMEM;
		पूर्ण
		caअगर_निश्चित(skb != शून्य);

		skb_put_data(skb, pfrm, len);

		skb->protocol = htons(ETH_P_CAIF);
		skb_reset_mac_header(skb);
		skb->dev = cfhsi->ndev;

		netअगर_rx_any_context(skb);

		/* Update network statistics. */
		cfhsi->ndev->stats.rx_packets++;
		cfhsi->ndev->stats.rx_bytes += len;
	पूर्ण

	/* Calculate transfer length. */
	plen = desc->cffrm_len;
	जबतक (nfrms < CFHSI_MAX_PKTS && *plen) अणु
		xfer_sz += *plen;
		plen++;
		nfrms++;
	पूर्ण

	/* Check क्रम piggy-backed descriptor. */
	अगर (desc->header & CFHSI_PIGGY_DESC)
		xfer_sz += CFHSI_DESC_SZ;

	अगर ((xfer_sz % 4) || (xfer_sz > (CFHSI_BUF_SZ_RX - CFHSI_DESC_SZ))) अणु
		netdev_err(cfhsi->ndev,
				"%s: Invalid payload len: %d, ignored.\n",
			__func__, xfer_sz);
		वापस -EPROTO;
	पूर्ण
	वापस xfer_sz;
पूर्ण

अटल पूर्णांक cfhsi_rx_desc_len(काष्ठा cfhsi_desc *desc)
अणु
	पूर्णांक xfer_sz = 0;
	पूर्णांक nfrms = 0;
	u16 *plen;

	अगर ((desc->header & ~CFHSI_PIGGY_DESC) ||
			(desc->offset > CFHSI_MAX_EMB_FRM_SZ)) अणु

		pr_err("Invalid descriptor. %x %x\n", desc->header,
				desc->offset);
		वापस -EPROTO;
	पूर्ण

	/* Calculate transfer length. */
	plen = desc->cffrm_len;
	जबतक (nfrms < CFHSI_MAX_PKTS && *plen) अणु
		xfer_sz += *plen;
		plen++;
		nfrms++;
	पूर्ण

	अगर (xfer_sz % 4) अणु
		pr_err("Invalid payload len: %d, ignored.\n", xfer_sz);
		वापस -EPROTO;
	पूर्ण
	वापस xfer_sz;
पूर्ण

अटल पूर्णांक cfhsi_rx_pld(काष्ठा cfhsi_desc *desc, काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक rx_sz = 0;
	पूर्णांक nfrms = 0;
	u16 *plen = शून्य;
	u8 *pfrm = शून्य;

	/* Sanity check header and offset. */
	अगर (WARN_ON((desc->header & ~CFHSI_PIGGY_DESC) ||
			(desc->offset > CFHSI_MAX_EMB_FRM_SZ))) अणु
		netdev_err(cfhsi->ndev, "%s: Invalid descriptor.\n",
			__func__);
		वापस -EPROTO;
	पूर्ण

	/* Set frame poपूर्णांकer to start of payload. */
	pfrm = desc->emb_frm + CFHSI_MAX_EMB_FRM_SZ;
	plen = desc->cffrm_len;

	/* Skip alपढ़ोy processed frames. */
	जबतक (nfrms < cfhsi->rx_state.nfrms) अणु
		pfrm += *plen;
		rx_sz += *plen;
		plen++;
		nfrms++;
	पूर्ण

	/* Parse payload. */
	जबतक (nfrms < CFHSI_MAX_PKTS && *plen) अणु
		काष्ठा sk_buff *skb;
		u8 *pcffrm = शून्य;
		पूर्णांक len;

		/* CAIF frame starts after head padding. */
		pcffrm = pfrm + *pfrm + 1;

		/* Read length of CAIF frame (little endian). */
		len = *pcffrm;
		len |= ((*(pcffrm + 1)) << 8) & 0xFF00;
		len += 2;	/* Add FCS fields. */

		/* Sanity check length of CAIF frames. */
		अगर (unlikely(len > CFHSI_MAX_CAIF_FRAME_SZ)) अणु
			netdev_err(cfhsi->ndev, "%s: Invalid length.\n",
				__func__);
			वापस -EPROTO;
		पूर्ण

		/* Allocate SKB (OK even in IRQ context). */
		skb = alloc_skb(len + 1, GFP_ATOMIC);
		अगर (!skb) अणु
			netdev_err(cfhsi->ndev, "%s: Out of memory !\n",
				__func__);
			cfhsi->rx_state.nfrms = nfrms;
			वापस -ENOMEM;
		पूर्ण
		caअगर_निश्चित(skb != शून्य);

		skb_put_data(skb, pcffrm, len);

		skb->protocol = htons(ETH_P_CAIF);
		skb_reset_mac_header(skb);
		skb->dev = cfhsi->ndev;

		netअगर_rx_any_context(skb);

		/* Update network statistics. */
		cfhsi->ndev->stats.rx_packets++;
		cfhsi->ndev->stats.rx_bytes += len;

		pfrm += *plen;
		rx_sz += *plen;
		plen++;
		nfrms++;
	पूर्ण

	वापस rx_sz;
पूर्ण

अटल व्योम cfhsi_rx_करोne(काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक res;
	पूर्णांक desc_pld_len = 0, rx_len, rx_state;
	काष्ठा cfhsi_desc *desc = शून्य;
	u8 *rx_ptr, *rx_buf;
	काष्ठा cfhsi_desc *piggy_desc = शून्य;

	desc = (काष्ठा cfhsi_desc *)cfhsi->rx_buf;

	netdev_dbg(cfhsi->ndev, "%s\n", __func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	/* Update inactivity समयr अगर pending. */
	spin_lock_bh(&cfhsi->lock);
	mod_समयr_pending(&cfhsi->inactivity_समयr,
			jअगरfies + cfhsi->cfg.inactivity_समयout);
	spin_unlock_bh(&cfhsi->lock);

	अगर (cfhsi->rx_state.state == CFHSI_RX_STATE_DESC) अणु
		desc_pld_len = cfhsi_rx_desc_len(desc);

		अगर (desc_pld_len < 0)
			जाओ out_of_sync;

		rx_buf = cfhsi->rx_buf;
		rx_len = desc_pld_len;
		अगर (desc_pld_len > 0 && (desc->header & CFHSI_PIGGY_DESC))
			rx_len += CFHSI_DESC_SZ;
		अगर (desc_pld_len == 0)
			rx_buf = cfhsi->rx_flip_buf;
	पूर्ण अन्यथा अणु
		rx_buf = cfhsi->rx_flip_buf;

		rx_len = CFHSI_DESC_SZ;
		अगर (cfhsi->rx_state.pld_len > 0 &&
				(desc->header & CFHSI_PIGGY_DESC)) अणु

			piggy_desc = (काष्ठा cfhsi_desc *)
				(desc->emb_frm + CFHSI_MAX_EMB_FRM_SZ +
						cfhsi->rx_state.pld_len);

			cfhsi->rx_state.piggy_desc = true;

			/* Extract payload len from piggy-backed descriptor. */
			desc_pld_len = cfhsi_rx_desc_len(piggy_desc);
			अगर (desc_pld_len < 0)
				जाओ out_of_sync;

			अगर (desc_pld_len > 0) अणु
				rx_len = desc_pld_len;
				अगर (piggy_desc->header & CFHSI_PIGGY_DESC)
					rx_len += CFHSI_DESC_SZ;
			पूर्ण

			/*
			 * Copy needed inक्रमmation from the piggy-backed
			 * descriptor to the descriptor in the start.
			 */
			स_नकल(rx_buf, (u8 *)piggy_desc,
					CFHSI_DESC_SHORT_SZ);
		पूर्ण
	पूर्ण

	अगर (desc_pld_len) अणु
		rx_state = CFHSI_RX_STATE_PAYLOAD;
		rx_ptr = rx_buf + CFHSI_DESC_SZ;
	पूर्ण अन्यथा अणु
		rx_state = CFHSI_RX_STATE_DESC;
		rx_ptr = rx_buf;
		rx_len = CFHSI_DESC_SZ;
	पूर्ण

	/* Initiate next पढ़ो */
	अगर (test_bit(CFHSI_AWAKE, &cfhsi->bits)) अणु
		/* Set up new transfer. */
		netdev_dbg(cfhsi->ndev, "%s: Start RX.\n",
				__func__);

		res = cfhsi->ops->cfhsi_rx(rx_ptr, rx_len,
				cfhsi->ops);
		अगर (WARN_ON(res < 0)) अणु
			netdev_err(cfhsi->ndev, "%s: RX error %d.\n",
				__func__, res);
			cfhsi->ndev->stats.rx_errors++;
			cfhsi->ndev->stats.rx_dropped++;
		पूर्ण
	पूर्ण

	अगर (cfhsi->rx_state.state == CFHSI_RX_STATE_DESC) अणु
		/* Extract payload from descriptor */
		अगर (cfhsi_rx_desc(desc, cfhsi) < 0)
			जाओ out_of_sync;
	पूर्ण अन्यथा अणु
		/* Extract payload */
		अगर (cfhsi_rx_pld(desc, cfhsi) < 0)
			जाओ out_of_sync;
		अगर (piggy_desc) अणु
			/* Extract any payload in piggyback descriptor. */
			अगर (cfhsi_rx_desc(piggy_desc, cfhsi) < 0)
				जाओ out_of_sync;
			/* Mark no embedded frame after extracting it */
			piggy_desc->offset = 0;
		पूर्ण
	पूर्ण

	/* Update state info */
	स_रखो(&cfhsi->rx_state, 0, माप(cfhsi->rx_state));
	cfhsi->rx_state.state = rx_state;
	cfhsi->rx_ptr = rx_ptr;
	cfhsi->rx_len = rx_len;
	cfhsi->rx_state.pld_len = desc_pld_len;
	cfhsi->rx_state.piggy_desc = desc->header & CFHSI_PIGGY_DESC;

	अगर (rx_buf != cfhsi->rx_buf)
		swap(cfhsi->rx_buf, cfhsi->rx_flip_buf);
	वापस;

out_of_sync:
	netdev_err(cfhsi->ndev, "%s: Out of sync.\n", __func__);
	prपूर्णांक_hex_dump_bytes("--> ", DUMP_PREFIX_NONE,
			cfhsi->rx_buf, CFHSI_DESC_SZ);
	schedule_work(&cfhsi->out_of_sync_work);
पूर्ण

अटल व्योम cfhsi_rx_slowpath(काष्ठा समयr_list *t)
अणु
	काष्ठा cfhsi *cfhsi = from_समयr(cfhsi, t, rx_slowpath_समयr);

	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	cfhsi_rx_करोne(cfhsi);
पूर्ण

अटल व्योम cfhsi_rx_करोne_cb(काष्ठा cfhsi_cb_ops *cb_ops)
अणु
	काष्ठा cfhsi *cfhsi;

	cfhsi = container_of(cb_ops, काष्ठा cfhsi, cb_ops);
	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	अगर (test_and_clear_bit(CFHSI_FLUSH_FIFO, &cfhsi->bits))
		wake_up_पूर्णांकerruptible(&cfhsi->flush_fअगरo_रुको);
	अन्यथा
		cfhsi_rx_करोne(cfhsi);
पूर्ण

अटल व्योम cfhsi_wake_up(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;
	पूर्णांक res;
	पूर्णांक len;
	दीर्घ ret;

	cfhsi = container_of(work, काष्ठा cfhsi, wake_up_work);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	अगर (unlikely(test_bit(CFHSI_AWAKE, &cfhsi->bits))) अणु
		/* It happenes when wakeup is requested by
		 * both ends at the same समय. */
		clear_bit(CFHSI_WAKE_UP, &cfhsi->bits);
		clear_bit(CFHSI_WAKE_UP_ACK, &cfhsi->bits);
		वापस;
	पूर्ण

	/* Activate wake line. */
	cfhsi->ops->cfhsi_wake_up(cfhsi->ops);

	netdev_dbg(cfhsi->ndev, "%s: Start waiting.\n",
		__func__);

	/* Wait क्रम acknowledge. */
	ret = CFHSI_WAKE_TOUT;
	ret = रुको_event_पूर्णांकerruptible_समयout(cfhsi->wake_up_रुको,
					test_and_clear_bit(CFHSI_WAKE_UP_ACK,
							&cfhsi->bits), ret);
	अगर (unlikely(ret < 0)) अणु
		/* Interrupted by संकेत. */
		netdev_err(cfhsi->ndev, "%s: Signalled: %ld.\n",
			__func__, ret);

		clear_bit(CFHSI_WAKE_UP, &cfhsi->bits);
		cfhsi->ops->cfhsi_wake_करोwn(cfhsi->ops);
		वापस;
	पूर्ण अन्यथा अगर (!ret) अणु
		bool ca_wake = false;
		माप_प्रकार fअगरo_occupancy = 0;

		/* Wakeup समयout */
		netdev_dbg(cfhsi->ndev, "%s: Timeout.\n",
			__func__);

		/* Check FIFO to check अगर modem has sent something. */
		WARN_ON(cfhsi->ops->cfhsi_fअगरo_occupancy(cfhsi->ops,
					&fअगरo_occupancy));

		netdev_dbg(cfhsi->ndev, "%s: Bytes in FIFO: %u.\n",
				__func__, (अचिन्हित) fअगरo_occupancy);

		/* Check अगर we misssed the पूर्णांकerrupt. */
		WARN_ON(cfhsi->ops->cfhsi_get_peer_wake(cfhsi->ops,
							&ca_wake));

		अगर (ca_wake) अणु
			netdev_err(cfhsi->ndev, "%s: CA Wake missed !.\n",
				__func__);

			/* Clear the CFHSI_WAKE_UP_ACK bit to prevent race. */
			clear_bit(CFHSI_WAKE_UP_ACK, &cfhsi->bits);

			/* Continue execution. */
			जाओ wake_ack;
		पूर्ण

		clear_bit(CFHSI_WAKE_UP, &cfhsi->bits);
		cfhsi->ops->cfhsi_wake_करोwn(cfhsi->ops);
		वापस;
	पूर्ण
wake_ack:
	netdev_dbg(cfhsi->ndev, "%s: Woken.\n",
		__func__);

	/* Clear घातer up bit. */
	set_bit(CFHSI_AWAKE, &cfhsi->bits);
	clear_bit(CFHSI_WAKE_UP, &cfhsi->bits);

	/* Resume पढ़ो operation. */
	netdev_dbg(cfhsi->ndev, "%s: Start RX.\n", __func__);
	res = cfhsi->ops->cfhsi_rx(cfhsi->rx_ptr, cfhsi->rx_len, cfhsi->ops);

	अगर (WARN_ON(res < 0))
		netdev_err(cfhsi->ndev, "%s: RX err %d.\n", __func__, res);

	/* Clear घातer up acknowledment. */
	clear_bit(CFHSI_WAKE_UP_ACK, &cfhsi->bits);

	spin_lock_bh(&cfhsi->lock);

	/* Resume transmit अगर queues are not empty. */
	अगर (!cfhsi_tx_queue_len(cfhsi)) अणु
		netdev_dbg(cfhsi->ndev, "%s: Peer wake, start timer.\n",
			__func__);
		/* Start inactivity समयr. */
		mod_समयr(&cfhsi->inactivity_समयr,
				jअगरfies + cfhsi->cfg.inactivity_समयout);
		spin_unlock_bh(&cfhsi->lock);
		वापस;
	पूर्ण

	netdev_dbg(cfhsi->ndev, "%s: Host wake.\n",
		__func__);

	spin_unlock_bh(&cfhsi->lock);

	/* Create HSI frame. */
	len = cfhsi_tx_frm((काष्ठा cfhsi_desc *)cfhsi->tx_buf, cfhsi);

	अगर (likely(len > 0)) अणु
		/* Set up new transfer. */
		res = cfhsi->ops->cfhsi_tx(cfhsi->tx_buf, len, cfhsi->ops);
		अगर (WARN_ON(res < 0)) अणु
			netdev_err(cfhsi->ndev, "%s: TX error %d.\n",
				__func__, res);
			cfhsi_पात_tx(cfhsi);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_err(cfhsi->ndev,
				"%s: Failed to create HSI frame: %d.\n",
				__func__, len);
	पूर्ण
पूर्ण

अटल व्योम cfhsi_wake_करोwn(काष्ठा work_काष्ठा *work)
अणु
	दीर्घ ret;
	काष्ठा cfhsi *cfhsi = शून्य;
	माप_प्रकार fअगरo_occupancy = 0;
	पूर्णांक retry = CFHSI_WAKE_TOUT;

	cfhsi = container_of(work, काष्ठा cfhsi, wake_करोwn_work);
	netdev_dbg(cfhsi->ndev, "%s.\n", __func__);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	/* Deactivate wake line. */
	cfhsi->ops->cfhsi_wake_करोwn(cfhsi->ops);

	/* Wait क्रम acknowledge. */
	ret = CFHSI_WAKE_TOUT;
	ret = रुको_event_पूर्णांकerruptible_समयout(cfhsi->wake_करोwn_रुको,
					test_and_clear_bit(CFHSI_WAKE_DOWN_ACK,
							&cfhsi->bits), ret);
	अगर (ret < 0) अणु
		/* Interrupted by संकेत. */
		netdev_err(cfhsi->ndev, "%s: Signalled: %ld.\n",
			__func__, ret);
		वापस;
	पूर्ण अन्यथा अगर (!ret) अणु
		bool ca_wake = true;

		/* Timeout */
		netdev_err(cfhsi->ndev, "%s: Timeout.\n", __func__);

		/* Check अगर we misssed the पूर्णांकerrupt. */
		WARN_ON(cfhsi->ops->cfhsi_get_peer_wake(cfhsi->ops,
							&ca_wake));
		अगर (!ca_wake)
			netdev_err(cfhsi->ndev, "%s: CA Wake missed !.\n",
				__func__);
	पूर्ण

	/* Check FIFO occupancy. */
	जबतक (retry) अणु
		WARN_ON(cfhsi->ops->cfhsi_fअगरo_occupancy(cfhsi->ops,
							&fअगरo_occupancy));

		अगर (!fअगरo_occupancy)
			अवरोध;

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(1);
		retry--;
	पूर्ण

	अगर (!retry)
		netdev_err(cfhsi->ndev, "%s: FIFO Timeout.\n", __func__);

	/* Clear AWAKE condition. */
	clear_bit(CFHSI_AWAKE, &cfhsi->bits);

	/* Cancel pending RX requests. */
	cfhsi->ops->cfhsi_rx_cancel(cfhsi->ops);
पूर्ण

अटल व्योम cfhsi_out_of_sync(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;

	cfhsi = container_of(work, काष्ठा cfhsi, out_of_sync_work);

	rtnl_lock();
	dev_बंद(cfhsi->ndev);
	rtnl_unlock();
पूर्ण

अटल व्योम cfhsi_wake_up_cb(काष्ठा cfhsi_cb_ops *cb_ops)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;

	cfhsi = container_of(cb_ops, काष्ठा cfhsi, cb_ops);
	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	set_bit(CFHSI_WAKE_UP_ACK, &cfhsi->bits);
	wake_up_पूर्णांकerruptible(&cfhsi->wake_up_रुको);

	अगर (test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))
		वापस;

	/* Schedule wake up work queue अगर the peer initiates. */
	अगर (!test_and_set_bit(CFHSI_WAKE_UP, &cfhsi->bits))
		queue_work(cfhsi->wq, &cfhsi->wake_up_work);
पूर्ण

अटल व्योम cfhsi_wake_करोwn_cb(काष्ठा cfhsi_cb_ops *cb_ops)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;

	cfhsi = container_of(cb_ops, काष्ठा cfhsi, cb_ops);
	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	/* Initiating low घातer is only permitted by the host (us). */
	set_bit(CFHSI_WAKE_DOWN_ACK, &cfhsi->bits);
	wake_up_पूर्णांकerruptible(&cfhsi->wake_करोwn_रुको);
पूर्ण

अटल व्योम cfhsi_aggregation_tout(काष्ठा समयr_list *t)
अणु
	काष्ठा cfhsi *cfhsi = from_समयr(cfhsi, t, aggregation_समयr);

	netdev_dbg(cfhsi->ndev, "%s.\n",
		__func__);

	cfhsi_start_tx(cfhsi);
पूर्ण

अटल netdev_tx_t cfhsi_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;
	पूर्णांक start_xfer = 0;
	पूर्णांक समयr_active;
	पूर्णांक prio;

	अगर (!dev)
		वापस -EINVAL;

	cfhsi = netdev_priv(dev);

	चयन (skb->priority) अणु
	हाल TC_PRIO_BESTEFFORT:
	हाल TC_PRIO_FILLER:
	हाल TC_PRIO_BULK:
		prio = CFHSI_PRIO_BEBK;
		अवरोध;
	हाल TC_PRIO_INTERACTIVE_BULK:
		prio = CFHSI_PRIO_VI;
		अवरोध;
	हाल TC_PRIO_INTERACTIVE:
		prio = CFHSI_PRIO_VO;
		अवरोध;
	हाल TC_PRIO_CONTROL:
	शेष:
		prio = CFHSI_PRIO_CTL;
		अवरोध;
	पूर्ण

	spin_lock_bh(&cfhsi->lock);

	/* Update aggregation statistics  */
	cfhsi_update_aggregation_stats(cfhsi, skb, 1);

	/* Queue the SKB */
	skb_queue_tail(&cfhsi->qhead[prio], skb);

	/* Sanity check; xmit should not be called after unरेजिस्टर_netdev */
	अगर (WARN_ON(test_bit(CFHSI_SHUTDOWN, &cfhsi->bits))) अणु
		spin_unlock_bh(&cfhsi->lock);
		cfhsi_पात_tx(cfhsi);
		वापस -EINVAL;
	पूर्ण

	/* Send flow off अगर number of packets is above high water mark. */
	अगर (!cfhsi->flow_off_sent &&
		cfhsi_tx_queue_len(cfhsi) > cfhsi->cfg.q_high_mark &&
		cfhsi->cfdev.flowctrl) अणु
		cfhsi->flow_off_sent = 1;
		cfhsi->cfdev.flowctrl(cfhsi->ndev, OFF);
	पूर्ण

	अगर (cfhsi->tx_state == CFHSI_TX_STATE_IDLE) अणु
		cfhsi->tx_state = CFHSI_TX_STATE_XFER;
		start_xfer = 1;
	पूर्ण

	अगर (!start_xfer) अणु
		/* Send aggregate अगर it is possible */
		bool aggregate_पढ़ोy =
			cfhsi_can_send_aggregate(cfhsi) &&
			del_समयr(&cfhsi->aggregation_समयr) > 0;
		spin_unlock_bh(&cfhsi->lock);
		अगर (aggregate_पढ़ोy)
			cfhsi_start_tx(cfhsi);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Delete inactivity समयr अगर started. */
	समयr_active = del_समयr_sync(&cfhsi->inactivity_समयr);

	spin_unlock_bh(&cfhsi->lock);

	अगर (समयr_active) अणु
		काष्ठा cfhsi_desc *desc = (काष्ठा cfhsi_desc *)cfhsi->tx_buf;
		पूर्णांक len;
		पूर्णांक res;

		/* Create HSI frame. */
		len = cfhsi_tx_frm(desc, cfhsi);
		WARN_ON(!len);

		/* Set up new transfer. */
		res = cfhsi->ops->cfhsi_tx(cfhsi->tx_buf, len, cfhsi->ops);
		अगर (WARN_ON(res < 0)) अणु
			netdev_err(cfhsi->ndev, "%s: TX error %d.\n",
				__func__, res);
			cfhsi_पात_tx(cfhsi);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Schedule wake up work queue अगर the we initiate. */
		अगर (!test_and_set_bit(CFHSI_WAKE_UP, &cfhsi->bits))
			queue_work(cfhsi->wq, &cfhsi->wake_up_work);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops cfhsi_netdevops;

अटल व्योम cfhsi_setup(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा cfhsi *cfhsi = netdev_priv(dev);
	dev->features = 0;
	dev->type = ARPHRD_CAIF;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu = CFHSI_MAX_CAIF_FRAME_SZ;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->needs_मुक्त_netdev = true;
	dev->netdev_ops = &cfhsi_netdevops;
	क्रम (i = 0; i < CFHSI_PRIO_LAST; ++i)
		skb_queue_head_init(&cfhsi->qhead[i]);
	cfhsi->cfdev.link_select = CAIF_LINK_HIGH_BANDW;
	cfhsi->cfdev.use_frag = false;
	cfhsi->cfdev.use_stx = false;
	cfhsi->cfdev.use_fcs = false;
	cfhsi->ndev = dev;
	cfhsi->cfg = hsi_शेष_config;
पूर्ण

अटल पूर्णांक cfhsi_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा cfhsi *cfhsi = netdev_priv(ndev);
	पूर्णांक res;

	clear_bit(CFHSI_SHUTDOWN, &cfhsi->bits);

	/* Initialize state vaiables. */
	cfhsi->tx_state = CFHSI_TX_STATE_IDLE;
	cfhsi->rx_state.state = CFHSI_RX_STATE_DESC;

	/* Set flow info */
	cfhsi->flow_off_sent = 0;

	/*
	 * Allocate a TX buffer with the size of a HSI packet descriptors
	 * and the necessary room क्रम CAIF payload frames.
	 */
	cfhsi->tx_buf = kzalloc(CFHSI_BUF_SZ_TX, GFP_KERNEL);
	अगर (!cfhsi->tx_buf) अणु
		res = -ENODEV;
		जाओ err_alloc_tx;
	पूर्ण

	/*
	 * Allocate a RX buffer with the size of two HSI packet descriptors and
	 * the necessary room क्रम CAIF payload frames.
	 */
	cfhsi->rx_buf = kzalloc(CFHSI_BUF_SZ_RX, GFP_KERNEL);
	अगर (!cfhsi->rx_buf) अणु
		res = -ENODEV;
		जाओ err_alloc_rx;
	पूर्ण

	cfhsi->rx_flip_buf = kzalloc(CFHSI_BUF_SZ_RX, GFP_KERNEL);
	अगर (!cfhsi->rx_flip_buf) अणु
		res = -ENODEV;
		जाओ err_alloc_rx_flip;
	पूर्ण

	/* Initialize aggregation समयout */
	cfhsi->cfg.aggregation_समयout = hsi_शेष_config.aggregation_समयout;

	/* Initialize recieve vaiables. */
	cfhsi->rx_ptr = cfhsi->rx_buf;
	cfhsi->rx_len = CFHSI_DESC_SZ;

	/* Initialize spin locks. */
	spin_lock_init(&cfhsi->lock);

	/* Set up the driver. */
	cfhsi->cb_ops.tx_करोne_cb = cfhsi_tx_करोne_cb;
	cfhsi->cb_ops.rx_करोne_cb = cfhsi_rx_करोne_cb;
	cfhsi->cb_ops.wake_up_cb = cfhsi_wake_up_cb;
	cfhsi->cb_ops.wake_करोwn_cb = cfhsi_wake_करोwn_cb;

	/* Initialize the work queues. */
	INIT_WORK(&cfhsi->wake_up_work, cfhsi_wake_up);
	INIT_WORK(&cfhsi->wake_करोwn_work, cfhsi_wake_करोwn);
	INIT_WORK(&cfhsi->out_of_sync_work, cfhsi_out_of_sync);

	/* Clear all bit fields. */
	clear_bit(CFHSI_WAKE_UP_ACK, &cfhsi->bits);
	clear_bit(CFHSI_WAKE_DOWN_ACK, &cfhsi->bits);
	clear_bit(CFHSI_WAKE_UP, &cfhsi->bits);
	clear_bit(CFHSI_AWAKE, &cfhsi->bits);

	/* Create work thपढ़ो. */
	cfhsi->wq = alloc_ordered_workqueue(cfhsi->ndev->name, WQ_MEM_RECLAIM);
	अगर (!cfhsi->wq) अणु
		netdev_err(cfhsi->ndev, "%s: Failed to create work queue.\n",
			__func__);
		res = -ENODEV;
		जाओ err_create_wq;
	पूर्ण

	/* Initialize रुको queues. */
	init_रुकोqueue_head(&cfhsi->wake_up_रुको);
	init_रुकोqueue_head(&cfhsi->wake_करोwn_रुको);
	init_रुकोqueue_head(&cfhsi->flush_fअगरo_रुको);

	/* Setup the inactivity समयr. */
	समयr_setup(&cfhsi->inactivity_समयr, cfhsi_inactivity_tout, 0);
	/* Setup the slowpath RX समयr. */
	समयr_setup(&cfhsi->rx_slowpath_समयr, cfhsi_rx_slowpath, 0);
	/* Setup the aggregation समयr. */
	समयr_setup(&cfhsi->aggregation_समयr, cfhsi_aggregation_tout, 0);

	/* Activate HSI पूर्णांकerface. */
	res = cfhsi->ops->cfhsi_up(cfhsi->ops);
	अगर (res) अणु
		netdev_err(cfhsi->ndev,
			"%s: can't activate HSI interface: %d.\n",
			__func__, res);
		जाओ err_activate;
	पूर्ण

	/* Flush FIFO */
	res = cfhsi_flush_fअगरo(cfhsi);
	अगर (res) अणु
		netdev_err(cfhsi->ndev, "%s: Can't flush FIFO: %d.\n",
			__func__, res);
		जाओ err_net_reg;
	पूर्ण
	वापस res;

 err_net_reg:
	cfhsi->ops->cfhsi_करोwn(cfhsi->ops);
 err_activate:
	destroy_workqueue(cfhsi->wq);
 err_create_wq:
	kमुक्त(cfhsi->rx_flip_buf);
 err_alloc_rx_flip:
	kमुक्त(cfhsi->rx_buf);
 err_alloc_rx:
	kमुक्त(cfhsi->tx_buf);
 err_alloc_tx:
	वापस res;
पूर्ण

अटल पूर्णांक cfhsi_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा cfhsi *cfhsi = netdev_priv(ndev);
	u8 *tx_buf, *rx_buf, *flip_buf;

	/* going to shutकरोwn driver */
	set_bit(CFHSI_SHUTDOWN, &cfhsi->bits);

	/* Delete समयrs अगर pending */
	del_समयr_sync(&cfhsi->inactivity_समयr);
	del_समयr_sync(&cfhsi->rx_slowpath_समयr);
	del_समयr_sync(&cfhsi->aggregation_समयr);

	/* Cancel pending RX request (अगर any) */
	cfhsi->ops->cfhsi_rx_cancel(cfhsi->ops);

	/* Destroy workqueue */
	destroy_workqueue(cfhsi->wq);

	/* Store bufferes: will be मुक्तd later. */
	tx_buf = cfhsi->tx_buf;
	rx_buf = cfhsi->rx_buf;
	flip_buf = cfhsi->rx_flip_buf;
	/* Flush transmit queues. */
	cfhsi_पात_tx(cfhsi);

	/* Deactivate पूर्णांकerface */
	cfhsi->ops->cfhsi_करोwn(cfhsi->ops);

	/* Free buffers. */
	kमुक्त(tx_buf);
	kमुक्त(rx_buf);
	kमुक्त(flip_buf);
	वापस 0;
पूर्ण

अटल व्योम cfhsi_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा cfhsi *cfhsi = netdev_priv(dev);
	ASSERT_RTNL();
	symbol_put(cfhsi_get_device);
	list_del(&cfhsi->list);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cfhsi_netdevops = अणु
	.nकरो_uninit = cfhsi_uninit,
	.nकरो_खोलो = cfhsi_खोलो,
	.nकरो_stop = cfhsi_बंद,
	.nकरो_start_xmit = cfhsi_xmit
पूर्ण;

अटल व्योम cfhsi_netlink_parms(काष्ठा nlattr *data[], काष्ठा cfhsi *cfhsi)
अणु
	पूर्णांक i;

	अगर (!data) अणु
		pr_debug("no params data found\n");
		वापस;
	पूर्ण

	i = __IFLA_CAIF_HSI_INACTIVITY_TOUT;
	/*
	 * Inactivity समयout in millisecs. Lowest possible value is 1,
	 * and highest possible is NEXT_TIMER_MAX_DELTA.
	 */
	अगर (data[i]) अणु
		u32 inactivity_समयout = nla_get_u32(data[i]);
		/* Pre-calculate inactivity समयout. */
		cfhsi->cfg.inactivity_समयout =	inactivity_समयout * HZ / 1000;
		अगर (cfhsi->cfg.inactivity_समयout == 0)
			cfhsi->cfg.inactivity_समयout = 1;
		अन्यथा अगर (cfhsi->cfg.inactivity_समयout > NEXT_TIMER_MAX_DELTA)
			cfhsi->cfg.inactivity_समयout = NEXT_TIMER_MAX_DELTA;
	पूर्ण

	i = __IFLA_CAIF_HSI_AGGREGATION_TOUT;
	अगर (data[i])
		cfhsi->cfg.aggregation_समयout = nla_get_u32(data[i]);

	i = __IFLA_CAIF_HSI_HEAD_ALIGN;
	अगर (data[i])
		cfhsi->cfg.head_align = nla_get_u32(data[i]);

	i = __IFLA_CAIF_HSI_TAIL_ALIGN;
	अगर (data[i])
		cfhsi->cfg.tail_align = nla_get_u32(data[i]);

	i = __IFLA_CAIF_HSI_QHIGH_WATERMARK;
	अगर (data[i])
		cfhsi->cfg.q_high_mark = nla_get_u32(data[i]);

	i = __IFLA_CAIF_HSI_QLOW_WATERMARK;
	अगर (data[i])
		cfhsi->cfg.q_low_mark = nla_get_u32(data[i]);
पूर्ण

अटल पूर्णांक caअगर_hsi_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			       काष्ठा nlattr *data[],
			       काष्ठा netlink_ext_ack *extack)
अणु
	cfhsi_netlink_parms(data, netdev_priv(dev));
	netdev_state_change(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy caअगर_hsi_policy[__IFLA_CAIF_HSI_MAX + 1] = अणु
	[__IFLA_CAIF_HSI_INACTIVITY_TOUT] = अणु .type = NLA_U32, .len = 4 पूर्ण,
	[__IFLA_CAIF_HSI_AGGREGATION_TOUT] = अणु .type = NLA_U32, .len = 4 पूर्ण,
	[__IFLA_CAIF_HSI_HEAD_ALIGN] = अणु .type = NLA_U32, .len = 4 पूर्ण,
	[__IFLA_CAIF_HSI_TAIL_ALIGN] = अणु .type = NLA_U32, .len = 4 पूर्ण,
	[__IFLA_CAIF_HSI_QHIGH_WATERMARK] = अणु .type = NLA_U32, .len = 4 पूर्ण,
	[__IFLA_CAIF_HSI_QLOW_WATERMARK] = अणु .type = NLA_U32, .len = 4 पूर्ण,
पूर्ण;

अटल माप_प्रकार caअगर_hsi_get_size(स्थिर काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	माप_प्रकार s = 0;
	क्रम (i = __IFLA_CAIF_HSI_UNSPEC + 1; i < __IFLA_CAIF_HSI_MAX; i++)
		s += nla_total_size(caअगर_hsi_policy[i].len);
	वापस s;
पूर्ण

अटल पूर्णांक caअगर_hsi_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा cfhsi *cfhsi = netdev_priv(dev);

	अगर (nla_put_u32(skb, __IFLA_CAIF_HSI_INACTIVITY_TOUT,
			cfhsi->cfg.inactivity_समयout) ||
	    nla_put_u32(skb, __IFLA_CAIF_HSI_AGGREGATION_TOUT,
			cfhsi->cfg.aggregation_समयout) ||
	    nla_put_u32(skb, __IFLA_CAIF_HSI_HEAD_ALIGN,
			cfhsi->cfg.head_align) ||
	    nla_put_u32(skb, __IFLA_CAIF_HSI_TAIL_ALIGN,
			cfhsi->cfg.tail_align) ||
	    nla_put_u32(skb, __IFLA_CAIF_HSI_QHIGH_WATERMARK,
			cfhsi->cfg.q_high_mark) ||
	    nla_put_u32(skb, __IFLA_CAIF_HSI_QLOW_WATERMARK,
			cfhsi->cfg.q_low_mark))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक caअगर_hsi_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			    काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cfhsi *cfhsi = शून्य;
	काष्ठा cfhsi_ops *(*get_ops)(व्योम);

	ASSERT_RTNL();

	cfhsi = netdev_priv(dev);
	cfhsi_netlink_parms(data, cfhsi);

	get_ops = symbol_get(cfhsi_get_ops);
	अगर (!get_ops) अणु
		pr_err("%s: failed to get the cfhsi_ops\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/* Assign the HSI device. */
	cfhsi->ops = (*get_ops)();
	अगर (!cfhsi->ops) अणु
		pr_err("%s: failed to get the cfhsi_ops\n", __func__);
		जाओ err;
	पूर्ण

	/* Assign the driver to this HSI device. */
	cfhsi->ops->cb_ops = &cfhsi->cb_ops;
	अगर (रेजिस्टर_netdevice(dev)) अणु
		pr_warn("%s: caif_hsi device registration failed\n", __func__);
		जाओ err;
	पूर्ण
	/* Add CAIF HSI device to list. */
	list_add_tail(&cfhsi->list, &cfhsi_list);

	वापस 0;
err:
	symbol_put(cfhsi_get_ops);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा rtnl_link_ops caअगर_hsi_link_ops __पढ़ो_mostly = अणु
	.kind		= "cfhsi",
	.priv_size	= माप(काष्ठा cfhsi),
	.setup		= cfhsi_setup,
	.maxtype	= __IFLA_CAIF_HSI_MAX,
	.policy	= caअगर_hsi_policy,
	.newlink	= caअगर_hsi_newlink,
	.changelink	= caअगर_hsi_changelink,
	.get_size	= caअगर_hsi_get_size,
	.fill_info	= caअगर_hsi_fill_info,
पूर्ण;

अटल व्योम __निकास cfhsi_निकास_module(व्योम)
अणु
	काष्ठा list_head *list_node;
	काष्ठा list_head *n;
	काष्ठा cfhsi *cfhsi;

	rtnl_link_unरेजिस्टर(&caअगर_hsi_link_ops);

	rtnl_lock();
	list_क्रम_each_safe(list_node, n, &cfhsi_list) अणु
		cfhsi = list_entry(list_node, काष्ठा cfhsi, list);
		unरेजिस्टर_netdevice(cfhsi->ndev);
	पूर्ण
	rtnl_unlock();
पूर्ण

अटल पूर्णांक __init cfhsi_init_module(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&caअगर_hsi_link_ops);
पूर्ण

module_init(cfhsi_init_module);
module_निकास(cfhsi_निकास_module);
