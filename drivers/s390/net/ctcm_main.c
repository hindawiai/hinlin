<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2001, 2009
 * Author(s):
 *	Original CTC driver(s):
 *		Fritz Elfert (felfert@millenux.com)
 *		Dieter Wellerdiek (wel@de.ibm.com)
 *		Martin Schwidefsky (schwidefsky@de.ibm.com)
 *		Denis Joseph Barrow (barrow_dj@yahoo.com)
 *		Jochen Roehrig (roehrig@de.ibm.com)
 *		Cornelia Huck <cornelia.huck@de.ibm.com>
 *	MPC additions:
 *		Belinda Thompson (belindat@us.ibm.com)
 *		Andy Richter (richtera@us.ibm.com)
 *	Revived by:
 *		Peter Tiedemann (ptiedem@de.ibm.com)
 */

#अघोषित DEBUG
#अघोषित DEBUGDATA
#अघोषित DEBUGCCW

#घोषणा KMSG_COMPONENT "ctcm"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bitops.h>

#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>

#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <net/dst.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/idals.h>

#समावेश "ctcm_fsms.h"
#समावेश "ctcm_main.h"

/* Some common global variables */

/**
 * The root device क्रम ctcm group devices
 */
अटल काष्ठा device *ctcm_root_dev;

/*
 * Linked list of all detected channels.
 */
काष्ठा channel *channels;

/**
 * Unpack a just received skb and hand it over to
 * upper layers.
 *
 *  ch		The channel where this skb has been received.
 *  pskb	The received skb.
 */
व्योम ctcm_unpack_skb(काष्ठा channel *ch, काष्ठा sk_buff *pskb)
अणु
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	__u16 len = *((__u16 *) pskb->data);

	skb_put(pskb, 2 + LL_HEADER_LENGTH);
	skb_pull(pskb, 2);
	pskb->dev = dev;
	pskb->ip_summed = CHECKSUM_UNNECESSARY;
	जबतक (len > 0) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक skblen;
		काष्ठा ll_header *header = (काष्ठा ll_header *)pskb->data;

		skb_pull(pskb, LL_HEADER_LENGTH);
		अगर ((ch->protocol == CTCM_PROTO_S390) &&
		    (header->type != ETH_P_IP)) अणु
			अगर (!(ch->logflags & LOG_FLAG_ILLEGALPKT)) अणु
				ch->logflags |= LOG_FLAG_ILLEGALPKT;
				/*
				 * Check packet type only अगर we stick strictly
				 * to S/390's protocol of OS390. This only
				 * supports IP. Otherwise allow any packet
				 * type.
				 */
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Illegal packet type 0x%04x"
					" - dropping",
					CTCM_FUNTAIL, dev->name, header->type);
			पूर्ण
			priv->stats.rx_dropped++;
			priv->stats.rx_frame_errors++;
			वापस;
		पूर्ण
		pskb->protocol = cpu_to_be16(header->type);
		अगर ((header->length <= LL_HEADER_LENGTH) ||
		    (len <= LL_HEADER_LENGTH)) अणु
			अगर (!(ch->logflags & LOG_FLAG_ILLEGALSIZE)) अणु
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Illegal packet size %d(%d,%d)"
					"- dropping",
					CTCM_FUNTAIL, dev->name,
					header->length, dev->mtu, len);
				ch->logflags |= LOG_FLAG_ILLEGALSIZE;
			पूर्ण

			priv->stats.rx_dropped++;
			priv->stats.rx_length_errors++;
			वापस;
		पूर्ण
		header->length -= LL_HEADER_LENGTH;
		len -= LL_HEADER_LENGTH;
		अगर ((header->length > skb_tailroom(pskb)) ||
		    (header->length > len)) अणु
			अगर (!(ch->logflags & LOG_FLAG_OVERRUN)) अणु
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): Packet size %d (overrun)"
					" - dropping", CTCM_FUNTAIL,
						dev->name, header->length);
				ch->logflags |= LOG_FLAG_OVERRUN;
			पूर्ण

			priv->stats.rx_dropped++;
			priv->stats.rx_length_errors++;
			वापस;
		पूर्ण
		skb_put(pskb, header->length);
		skb_reset_mac_header(pskb);
		len -= header->length;
		skb = dev_alloc_skb(pskb->len);
		अगर (!skb) अणु
			अगर (!(ch->logflags & LOG_FLAG_NOMEM)) अणु
				CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
					"%s(%s): MEMORY allocation error",
						CTCM_FUNTAIL, dev->name);
				ch->logflags |= LOG_FLAG_NOMEM;
			पूर्ण
			priv->stats.rx_dropped++;
			वापस;
		पूर्ण
		skb_copy_from_linear_data(pskb, skb_put(skb, pskb->len),
					  pskb->len);
		skb_reset_mac_header(skb);
		skb->dev = pskb->dev;
		skb->protocol = pskb->protocol;
		pskb->ip_summed = CHECKSUM_UNNECESSARY;
		skblen = skb->len;
		/*
		 * reset logflags
		 */
		ch->logflags = 0;
		priv->stats.rx_packets++;
		priv->stats.rx_bytes += skblen;
		netअगर_rx_ni(skb);
		अगर (len > 0) अणु
			skb_pull(pskb, header->length);
			अगर (skb_tailroom(pskb) < LL_HEADER_LENGTH) अणु
				CTCM_DBF_DEV_NAME(TRACE, dev,
					"Overrun in ctcm_unpack_skb");
				ch->logflags |= LOG_FLAG_OVERRUN;
				वापस;
			पूर्ण
			skb_put(pskb, LL_HEADER_LENGTH);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Release a specअगरic channel in the channel list.
 *
 *  ch		Poपूर्णांकer to channel काष्ठा to be released.
 */
अटल व्योम channel_मुक्त(काष्ठा channel *ch)
अणु
	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s)", CTCM_FUNTAIL, ch->id);
	ch->flags &= ~CHANNEL_FLAGS_INUSE;
	fsm_newstate(ch->fsm, CTC_STATE_IDLE);
पूर्ण

/**
 * Remove a specअगरic channel in the channel list.
 *
 *  ch		Poपूर्णांकer to channel काष्ठा to be released.
 */
अटल व्योम channel_हटाओ(काष्ठा channel *ch)
अणु
	काष्ठा channel **c = &channels;
	अक्षर chid[CTCM_ID_SIZE+1];
	पूर्णांक ok = 0;

	अगर (ch == शून्य)
		वापस;
	अन्यथा
		म_नकलन(chid, ch->id, CTCM_ID_SIZE);

	channel_मुक्त(ch);
	जबतक (*c) अणु
		अगर (*c == ch) अणु
			*c = ch->next;
			fsm_delसमयr(&ch->समयr);
			अगर (IS_MPC(ch))
				fsm_delसमयr(&ch->sweep_समयr);

			kमुक्त_fsm(ch->fsm);
			clear_normalized_cda(&ch->ccw[4]);
			अगर (ch->trans_skb != शून्य) अणु
				clear_normalized_cda(&ch->ccw[1]);
				dev_kमुक्त_skb_any(ch->trans_skb);
			पूर्ण
			अगर (IS_MPC(ch)) अणु
				tasklet_समाप्त(&ch->ch_tasklet);
				tasklet_समाप्त(&ch->ch_disc_tasklet);
				kमुक्त(ch->discontact_th);
			पूर्ण
			kमुक्त(ch->ccw);
			kमुक्त(ch->irb);
			kमुक्त(ch);
			ok = 1;
			अवरोध;
		पूर्ण
		c = &((*c)->next);
	पूर्ण

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s) %s", CTCM_FUNTAIL,
			chid, ok ? "OK" : "failed");
पूर्ण

/**
 * Get a specअगरic channel from the channel list.
 *
 *  type	Type of channel we are पूर्णांकerested in.
 *  id		Id of channel we are पूर्णांकerested in.
 *  direction	Direction we want to use this channel क्रम.
 *
 * वापसs Poपूर्णांकer to a channel or शून्य अगर no matching channel available.
 */
अटल काष्ठा channel *channel_get(क्रमागत ctcm_channel_types type,
					अक्षर *id, पूर्णांक direction)
अणु
	काष्ठा channel *ch = channels;

	जबतक (ch && (म_भेदन(ch->id, id, CTCM_ID_SIZE) || (ch->type != type)))
		ch = ch->next;
	अगर (!ch) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
				"%s(%d, %s, %d) not found in channel list\n",
				CTCM_FUNTAIL, type, id, direction);
	पूर्ण अन्यथा अणु
		अगर (ch->flags & CHANNEL_FLAGS_INUSE)
			ch = शून्य;
		अन्यथा अणु
			ch->flags |= CHANNEL_FLAGS_INUSE;
			ch->flags &= ~CHANNEL_FLAGS_RWMASK;
			ch->flags |= (direction == CTCM_WRITE)
			    ? CHANNEL_FLAGS_WRITE : CHANNEL_FLAGS_READ;
			fsm_newstate(ch->fsm, CTC_STATE_STOPPED);
		पूर्ण
	पूर्ण
	वापस ch;
पूर्ण

अटल दीर्घ ctcm_check_irb_error(काष्ठा ccw_device *cdev, काष्ठा irb *irb)
अणु
	अगर (!IS_ERR(irb))
		वापस 0;

	CTCM_DBF_TEXT_(ERROR, CTC_DBF_WARN,
			"irb error %ld on device %s\n",
				PTR_ERR(irb), dev_name(&cdev->dev));

	चयन (PTR_ERR(irb)) अणु
	हाल -EIO:
		dev_err(&cdev->dev,
			"An I/O-error occurred on the CTCM device\n");
		अवरोध;
	हाल -ETIMEDOUT:
		dev_err(&cdev->dev,
			"An adapter hardware operation timed out\n");
		अवरोध;
	शेष:
		dev_err(&cdev->dev,
			"An error occurred on the adapter hardware\n");
	पूर्ण
	वापस PTR_ERR(irb);
पूर्ण


/**
 * Check sense of a unit check.
 *
 *  ch		The channel, the sense code beदीर्घs to.
 *  sense	The sense code to inspect.
 */
अटल व्योम ccw_unit_check(काष्ठा channel *ch, __u8 sense)
अणु
	CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): %02x",
				CTCM_FUNTAIL, ch->id, sense);

	अगर (sense & SNS0_INTERVENTION_REQ) अणु
		अगर (sense & 0x01) अणु
			अगर (ch->sense_rc != 0x01) अणु
				pr_notice(
					"%s: The communication peer has "
					"disconnected\n", ch->id);
				ch->sense_rc = 0x01;
			पूर्ण
			fsm_event(ch->fsm, CTC_EVENT_UC_RCRESET, ch);
		पूर्ण अन्यथा अणु
			अगर (ch->sense_rc != SNS0_INTERVENTION_REQ) अणु
				pr_notice(
					"%s: The remote operating system is "
					"not available\n", ch->id);
				ch->sense_rc = SNS0_INTERVENTION_REQ;
			पूर्ण
			fsm_event(ch->fsm, CTC_EVENT_UC_RSRESET, ch);
		पूर्ण
	पूर्ण अन्यथा अगर (sense & SNS0_EQUIPMENT_CHECK) अणु
		अगर (sense & SNS0_BUS_OUT_CHECK) अणु
			अगर (ch->sense_rc != SNS0_BUS_OUT_CHECK) अणु
				CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
					"%s(%s): remote HW error %02x",
						CTCM_FUNTAIL, ch->id, sense);
				ch->sense_rc = SNS0_BUS_OUT_CHECK;
			पूर्ण
			fsm_event(ch->fsm, CTC_EVENT_UC_HWFAIL, ch);
		पूर्ण अन्यथा अणु
			अगर (ch->sense_rc != SNS0_EQUIPMENT_CHECK) अणु
				CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
					"%s(%s): remote read parity error %02x",
						CTCM_FUNTAIL, ch->id, sense);
				ch->sense_rc = SNS0_EQUIPMENT_CHECK;
			पूर्ण
			fsm_event(ch->fsm, CTC_EVENT_UC_RXPARITY, ch);
		पूर्ण
	पूर्ण अन्यथा अगर (sense & SNS0_BUS_OUT_CHECK) अणु
		अगर (ch->sense_rc != SNS0_BUS_OUT_CHECK) अणु
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
				"%s(%s): BUS OUT error %02x",
					CTCM_FUNTAIL, ch->id, sense);
			ch->sense_rc = SNS0_BUS_OUT_CHECK;
		पूर्ण
		अगर (sense & 0x04)	/* data-streaming समयout */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXTIMEOUT, ch);
		अन्यथा			/* Data-transfer parity error */
			fsm_event(ch->fsm, CTC_EVENT_UC_TXPARITY, ch);
	पूर्ण अन्यथा अगर (sense & SNS0_CMD_REJECT) अणु
		अगर (ch->sense_rc != SNS0_CMD_REJECT) अणु
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
				"%s(%s): Command rejected",
						CTCM_FUNTAIL, ch->id);
			ch->sense_rc = SNS0_CMD_REJECT;
		पूर्ण
	पूर्ण अन्यथा अगर (sense == 0) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
			"%s(%s): Unit check ZERO",
					CTCM_FUNTAIL, ch->id);
		fsm_event(ch->fsm, CTC_EVENT_UC_ZERO, ch);
	पूर्ण अन्यथा अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
			"%s(%s): Unit check code %02x unknown",
					CTCM_FUNTAIL, ch->id, sense);
		fsm_event(ch->fsm, CTC_EVENT_UC_UNKNOWN, ch);
	पूर्ण
पूर्ण

पूर्णांक ctcm_ch_alloc_buffer(काष्ठा channel *ch)
अणु
	clear_normalized_cda(&ch->ccw[1]);
	ch->trans_skb = __dev_alloc_skb(ch->max_bufsize, GFP_ATOMIC | GFP_DMA);
	अगर (ch->trans_skb == शून्य) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s trans_skb allocation error",
			CTCM_FUNTAIL, ch->id,
			(CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ?
				"RX" : "TX");
		वापस -ENOMEM;
	पूर्ण

	ch->ccw[1].count = ch->max_bufsize;
	अगर (set_normalized_cda(&ch->ccw[1], ch->trans_skb->data)) अणु
		dev_kमुक्त_skb(ch->trans_skb);
		ch->trans_skb = शून्य;
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s set norm_cda failed",
			CTCM_FUNTAIL, ch->id,
			(CHANNEL_सूचीECTION(ch->flags) == CTCM_READ) ?
				"RX" : "TX");
		वापस -ENOMEM;
	पूर्ण

	ch->ccw[1].count = 0;
	ch->trans_skb_data = ch->trans_skb->data;
	ch->flags &= ~CHANNEL_FLAGS_बफ_मानE_CHANGED;
	वापस 0;
पूर्ण

/*
 * Interface API क्रम upper network layers
 */

/**
 * Open an पूर्णांकerface.
 * Called from generic network layer when अगरconfig up is run.
 *
 *  dev		Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * वापसs 0 on success, -ERRNO on failure. (Never fails.)
 */
पूर्णांक ctcm_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");
	अगर (!IS_MPC(priv))
		fsm_event(priv->fsm,	DEV_EVENT_START, dev);
	वापस 0;
पूर्ण

/**
 * Close an पूर्णांकerface.
 * Called from generic network layer when अगरconfig करोwn is run.
 *
 *  dev		Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * वापसs 0 on success, -ERRNO on failure. (Never fails.)
 */
पूर्णांक ctcm_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");
	अगर (!IS_MPC(priv))
		fsm_event(priv->fsm, DEV_EVENT_STOP, dev);
	वापस 0;
पूर्ण


/**
 * Transmit a packet.
 * This is a helper function क्रम ctcm_tx().
 *
 *  ch		Channel to be used क्रम sending.
 *  skb		Poपूर्णांकer to काष्ठा sk_buff of packet to send.
 *            The linklevel header has alपढ़ोy been set up
 *            by ctcm_tx().
 *
 * वापसs 0 on success, -ERRNO on failure. (Never fails.)
 */
अटल पूर्णांक ctcm_transmit_skb(काष्ठा channel *ch, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ saveflags;
	काष्ठा ll_header header;
	पूर्णांक rc = 0;
	__u16 block_len;
	पूर्णांक ccw_idx;
	काष्ठा sk_buff *nskb;
	अचिन्हित दीर्घ hi;

	/* we need to acquire the lock क्रम testing the state
	 * otherwise we can have an IRQ changing the state to
	 * TXIDLE after the test but beक्रमe acquiring the lock.
	 */
	spin_lock_irqsave(&ch->collect_lock, saveflags);
	अगर (fsm_माला_लोtate(ch->fsm) != CTC_STATE_TXIDLE) अणु
		पूर्णांक l = skb->len + LL_HEADER_LENGTH;

		अगर (ch->collect_len + l > ch->max_bufsize - 2) अणु
			spin_unlock_irqrestore(&ch->collect_lock, saveflags);
			वापस -EBUSY;
		पूर्ण अन्यथा अणु
			refcount_inc(&skb->users);
			header.length = l;
			header.type = be16_to_cpu(skb->protocol);
			header.unused = 0;
			स_नकल(skb_push(skb, LL_HEADER_LENGTH), &header,
			       LL_HEADER_LENGTH);
			skb_queue_tail(&ch->collect_queue, skb);
			ch->collect_len += l;
		पूर्ण
		spin_unlock_irqrestore(&ch->collect_lock, saveflags);
				जाओ करोne;
	पूर्ण
	spin_unlock_irqrestore(&ch->collect_lock, saveflags);
	/*
	 * Protect skb against beeing मुक्त'd by upper
	 * layers.
	 */
	refcount_inc(&skb->users);
	ch->prof.txlen += skb->len;
	header.length = skb->len + LL_HEADER_LENGTH;
	header.type = be16_to_cpu(skb->protocol);
	header.unused = 0;
	स_नकल(skb_push(skb, LL_HEADER_LENGTH), &header, LL_HEADER_LENGTH);
	block_len = skb->len + 2;
	*((__u16 *)skb_push(skb, 2)) = block_len;

	/*
	 * IDAL support in CTCM is broken, so we have to
	 * care about skb's above 2G ourselves.
	 */
	hi = ((अचिन्हित दीर्घ)skb_tail_poपूर्णांकer(skb) + LL_HEADER_LENGTH) >> 31;
	अगर (hi) अणु
		nskb = alloc_skb(skb->len, GFP_ATOMIC | GFP_DMA);
		अगर (!nskb) अणु
			refcount_dec(&skb->users);
			skb_pull(skb, LL_HEADER_LENGTH + 2);
			ctcm_clear_busy(ch->netdev);
			वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			skb_put_data(nskb, skb->data, skb->len);
			refcount_inc(&nskb->users);
			refcount_dec(&skb->users);
			dev_kमुक्त_skb_irq(skb);
			skb = nskb;
		पूर्ण
	पूर्ण

	ch->ccw[4].count = block_len;
	अगर (set_normalized_cda(&ch->ccw[4], skb->data)) अणु
		/*
		 * idal allocation failed, try via copying to
		 * trans_skb. trans_skb usually has a pre-allocated
		 * idal.
		 */
		अगर (ctcm_checkalloc_buffer(ch)) अणु
			/*
			 * Remove our header. It माला_लो added
			 * again on retransmit.
			 */
			refcount_dec(&skb->users);
			skb_pull(skb, LL_HEADER_LENGTH + 2);
			ctcm_clear_busy(ch->netdev);
			वापस -ENOMEM;
		पूर्ण

		skb_reset_tail_poपूर्णांकer(ch->trans_skb);
		ch->trans_skb->len = 0;
		ch->ccw[1].count = skb->len;
		skb_copy_from_linear_data(skb,
				skb_put(ch->trans_skb, skb->len), skb->len);
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_irq(skb);
		ccw_idx = 0;
	पूर्ण अन्यथा अणु
		skb_queue_tail(&ch->io_queue, skb);
		ccw_idx = 3;
	पूर्ण
	अगर (करो_debug_ccw)
		ctcmpc_dumpit((अक्षर *)&ch->ccw[ccw_idx],
					माप(काष्ठा ccw1) * 3);
	ch->retry = 0;
	fsm_newstate(ch->fsm, CTC_STATE_TX);
	fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
	spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
	ch->prof.send_stamp = jअगरfies;
	rc = ccw_device_start(ch->cdev, &ch->ccw[ccw_idx], 0, 0xff, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	अगर (ccw_idx == 3)
		ch->prof.करोios_single++;
	अगर (rc != 0) अणु
		fsm_delसमयr(&ch->समयr);
		ctcm_ccw_check_rc(ch, rc, "single skb TX");
		अगर (ccw_idx == 3)
			skb_dequeue_tail(&ch->io_queue);
		/*
		 * Remove our header. It माला_लो added
		 * again on retransmit.
		 */
		skb_pull(skb, LL_HEADER_LENGTH + 2);
	पूर्ण अन्यथा अगर (ccw_idx == 0) अणु
		काष्ठा net_device *dev = ch->netdev;
		काष्ठा ctcm_priv *priv = dev->ml_priv;
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len - LL_HEADER_LENGTH;
	पूर्ण
करोne:
	ctcm_clear_busy(ch->netdev);
	वापस rc;
पूर्ण

अटल व्योम ctcmpc_send_sweep_req(काष्ठा channel *rch)
अणु
	काष्ठा net_device *dev = rch->netdev;
	काष्ठा ctcm_priv *priv;
	काष्ठा mpc_group *grp;
	काष्ठा th_sweep *header;
	काष्ठा sk_buff *sweep_skb;
	काष्ठा channel *ch;
	/* पूर्णांक rc = 0; */

	priv = dev->ml_priv;
	grp = priv->mpcg;
	ch = priv->channel[CTCM_WRITE];

	/* sweep processing is not complete until response and request */
	/* has completed क्रम all पढ़ो channels in group		       */
	अगर (grp->in_sweep == 0) अणु
		grp->in_sweep = 1;
		grp->sweep_rsp_pend_num = grp->active_channels[CTCM_READ];
		grp->sweep_req_pend_num = grp->active_channels[CTCM_READ];
	पूर्ण

	sweep_skb = __dev_alloc_skb(MPC_बफ_मानE_DEFAULT, GFP_ATOMIC|GFP_DMA);

	अगर (sweep_skb == शून्य)	अणु
		/* rc = -ENOMEM; */
				जाओ nomem;
	पूर्ण

	header = skb_put_zero(sweep_skb, TH_SWEEP_LENGTH);
	header->th.th_ch_flag	= TH_SWEEP_REQ;  /* 0x0f */
	header->sw.th_last_seq	= ch->th_seq_num;

	netअगर_trans_update(dev);
	skb_queue_tail(&ch->sweep_queue, sweep_skb);

	fsm_addसमयr(&ch->sweep_समयr, 100, CTC_EVENT_RSWEEP_TIMER, ch);

	वापस;

nomem:
	grp->in_sweep = 0;
	ctcm_clear_busy(dev);
	fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);

	वापस;
पूर्ण

/*
 * MPC mode version of transmit_skb
 */
अटल पूर्णांक ctcmpc_transmit_skb(काष्ठा channel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा pdu *p_header;
	काष्ठा net_device *dev = ch->netdev;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp = priv->mpcg;
	काष्ठा th_header *header;
	काष्ठा sk_buff *nskb;
	पूर्णांक rc = 0;
	पूर्णांक ccw_idx;
	अचिन्हित दीर्घ hi;
	अचिन्हित दीर्घ saveflags = 0;	/* aव्योमs compiler warning */

	CTCM_PR_DEBUG("Enter %s: %s, cp=%i ch=0x%p id=%s state=%s\n",
			__func__, dev->name, smp_processor_id(), ch,
					ch->id, fsm_माला_लोtate_str(ch->fsm));

	अगर ((fsm_माला_लोtate(ch->fsm) != CTC_STATE_TXIDLE) || grp->in_sweep) अणु
		spin_lock_irqsave(&ch->collect_lock, saveflags);
		refcount_inc(&skb->users);

		p_header = skb_push(skb, PDU_HEADER_LENGTH);
		p_header->pdu_offset = skb->len - PDU_HEADER_LENGTH;
		p_header->pdu_proto = 0x01;
		अगर (be16_to_cpu(skb->protocol) == ETH_P_SNAP) अणु
			p_header->pdu_flag = PDU_FIRST | PDU_CNTL;
		पूर्ण अन्यथा अणु
			p_header->pdu_flag = PDU_FIRST;
		पूर्ण
		p_header->pdu_seq = 0;

		CTCM_PR_DEBUG("%s(%s): Put on collect_q - skb len: %04x \n"
				"pdu header and data for up to 32 bytes:\n",
				__func__, dev->name, skb->len);
		CTCM_D3_DUMP((अक्षर *)skb->data, min_t(पूर्णांक, 32, skb->len));

		skb_queue_tail(&ch->collect_queue, skb);
		ch->collect_len += skb->len;

		spin_unlock_irqrestore(&ch->collect_lock, saveflags);
			जाओ करोne;
	पूर्ण

	/*
	 * Protect skb against beeing मुक्त'd by upper
	 * layers.
	 */
	refcount_inc(&skb->users);

	/*
	 * IDAL support in CTCM is broken, so we have to
	 * care about skb's above 2G ourselves.
	 */
	hi = ((अचिन्हित दीर्घ)skb->tail + TH_HEADER_LENGTH) >> 31;
	अगर (hi) अणु
		nskb = __dev_alloc_skb(skb->len, GFP_ATOMIC | GFP_DMA);
		अगर (!nskb) अणु
			जाओ nomem_निकास;
		पूर्ण अन्यथा अणु
			skb_put_data(nskb, skb->data, skb->len);
			refcount_inc(&nskb->users);
			refcount_dec(&skb->users);
			dev_kमुक्त_skb_irq(skb);
			skb = nskb;
		पूर्ण
	पूर्ण

	p_header = skb_push(skb, PDU_HEADER_LENGTH);
	p_header->pdu_offset = skb->len - PDU_HEADER_LENGTH;
	p_header->pdu_proto = 0x01;
	p_header->pdu_seq = 0;
	अगर (be16_to_cpu(skb->protocol) == ETH_P_SNAP) अणु
		p_header->pdu_flag = PDU_FIRST | PDU_CNTL;
	पूर्ण अन्यथा अणु
		p_header->pdu_flag = PDU_FIRST;
	पूर्ण

	अगर (ch->collect_len > 0) अणु
		spin_lock_irqsave(&ch->collect_lock, saveflags);
		skb_queue_tail(&ch->collect_queue, skb);
		ch->collect_len += skb->len;
		skb = skb_dequeue(&ch->collect_queue);
		ch->collect_len -= skb->len;
		spin_unlock_irqrestore(&ch->collect_lock, saveflags);
	पूर्ण

	p_header = (काष्ठा pdu *)skb->data;
	p_header->pdu_flag |= PDU_LAST;

	ch->prof.txlen += skb->len - PDU_HEADER_LENGTH;

	/* put the TH on the packet */
	header = skb_push(skb, TH_HEADER_LENGTH);
	स_रखो(header, 0, TH_HEADER_LENGTH);

	header->th_ch_flag = TH_HAS_PDU;  /* Normal data */
	ch->th_seq_num++;
	header->th_seq_num = ch->th_seq_num;

	CTCM_PR_DBGDATA("%s(%s) ToVTAM_th_seq= %08x\n" ,
		       __func__, dev->name, ch->th_seq_num);

	CTCM_PR_DBGDATA("%s(%s): skb len: %04x\n - pdu header and data for "
			"up to 32 bytes sent to vtam:\n",
				__func__, dev->name, skb->len);
	CTCM_D3_DUMP((अक्षर *)skb->data, min_t(पूर्णांक, 32, skb->len));

	ch->ccw[4].count = skb->len;
	अगर (set_normalized_cda(&ch->ccw[4], skb->data)) अणु
		/*
		 * idal allocation failed, try via copying to trans_skb.
		 * trans_skb usually has a pre-allocated idal.
		 */
		अगर (ctcm_checkalloc_buffer(ch)) अणु
			/*
			 * Remove our header.
			 * It माला_लो added again on retransmit.
			 */
				जाओ nomem_निकास;
		पूर्ण

		skb_reset_tail_poपूर्णांकer(ch->trans_skb);
		ch->trans_skb->len = 0;
		ch->ccw[1].count = skb->len;
		skb_put_data(ch->trans_skb, skb->data, skb->len);
		refcount_dec(&skb->users);
		dev_kमुक्त_skb_irq(skb);
		ccw_idx = 0;
		CTCM_PR_DBGDATA("%s(%s): trans_skb len: %04x\n"
				"up to 32 bytes sent to vtam:\n",
				__func__, dev->name, ch->trans_skb->len);
		CTCM_D3_DUMP((अक्षर *)ch->trans_skb->data,
				min_t(पूर्णांक, 32, ch->trans_skb->len));
	पूर्ण अन्यथा अणु
		skb_queue_tail(&ch->io_queue, skb);
		ccw_idx = 3;
	पूर्ण
	ch->retry = 0;
	fsm_newstate(ch->fsm, CTC_STATE_TX);
	fsm_addसमयr(&ch->समयr, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);

	अगर (करो_debug_ccw)
		ctcmpc_dumpit((अक्षर *)&ch->ccw[ccw_idx],
					माप(काष्ठा ccw1) * 3);

	spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
	ch->prof.send_stamp = jअगरfies;
	rc = ccw_device_start(ch->cdev, &ch->ccw[ccw_idx], 0, 0xff, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	अगर (ccw_idx == 3)
		ch->prof.करोios_single++;
	अगर (rc != 0) अणु
		fsm_delसमयr(&ch->समयr);
		ctcm_ccw_check_rc(ch, rc, "single skb TX");
		अगर (ccw_idx == 3)
			skb_dequeue_tail(&ch->io_queue);
	पूर्ण अन्यथा अगर (ccw_idx == 0) अणु
		priv->stats.tx_packets++;
		priv->stats.tx_bytes += skb->len - TH_HEADER_LENGTH;
	पूर्ण
	अगर (ch->th_seq_num > 0xf0000000)	/* Chose at अक्रमom. */
		ctcmpc_send_sweep_req(ch);

	जाओ करोne;
nomem_निकास:
	CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_CRIT,
			"%s(%s): MEMORY allocation ERROR\n",
			CTCM_FUNTAIL, ch->id);
	rc = -ENOMEM;
	refcount_dec(&skb->users);
	dev_kमुक्त_skb_any(skb);
	fsm_event(priv->mpcg->fsm, MPCG_EVENT_INOP, dev);
करोne:
	CTCM_PR_DEBUG("Exit %s(%s)\n", __func__, dev->name);
	वापस rc;
पूर्ण

/**
 * Start transmission of a packet.
 * Called from generic network device layer.
 *
 *  skb		Poपूर्णांकer to buffer containing the packet.
 *  dev		Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * वापसs 0 अगर packet consumed, !0 अगर packet rejected.
 *         Note: If we वापस !0, then the packet is मुक्त'd by
 *               the generic network layer.
 */
/* first merge version - leaving both functions separated */
अटल पूर्णांक ctcm_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ctcm_priv *priv = dev->ml_priv;

	अगर (skb == शून्य) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
				"%s(%s): NULL sk_buff passed",
					CTCM_FUNTAIL, dev->name);
		priv->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb_headroom(skb) < (LL_HEADER_LENGTH + 2)) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): Got sk_buff with head room < %ld bytes",
			CTCM_FUNTAIL, dev->name, LL_HEADER_LENGTH + 2);
		dev_kमुक्त_skb(skb);
		priv->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	/*
	 * If channels are not running, try to restart them
	 * and throw away packet.
	 */
	अगर (fsm_माला_लोtate(priv->fsm) != DEV_STATE_RUNNING) अणु
		fsm_event(priv->fsm, DEV_EVENT_START, dev);
		dev_kमुक्त_skb(skb);
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
		priv->stats.tx_carrier_errors++;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (ctcm_test_and_set_busy(dev))
		वापस NETDEV_TX_BUSY;

	netअगर_trans_update(dev);
	अगर (ctcm_transmit_skb(priv->channel[CTCM_WRITE], skb) != 0)
		वापस NETDEV_TX_BUSY;
	वापस NETDEV_TX_OK;
पूर्ण

/* unmerged MPC variant of ctcm_tx */
अटल पूर्णांक ctcmpc_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक len = 0;
	काष्ठा ctcm_priv *priv = dev->ml_priv;
	काष्ठा mpc_group *grp  = priv->mpcg;
	काष्ठा sk_buff *newskb = शून्य;

	/*
	 * Some sanity checks ...
	 */
	अगर (skb == शून्य) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): NULL sk_buff passed",
					CTCM_FUNTAIL, dev->name);
		priv->stats.tx_dropped++;
					जाओ करोne;
	पूर्ण
	अगर (skb_headroom(skb) < (TH_HEADER_LENGTH + PDU_HEADER_LENGTH)) अणु
		CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_ERROR,
			"%s(%s): Got sk_buff with head room < %ld bytes",
			CTCM_FUNTAIL, dev->name,
				TH_HEADER_LENGTH + PDU_HEADER_LENGTH);

		CTCM_D3_DUMP((अक्षर *)skb->data, min_t(पूर्णांक, 32, skb->len));

		len =  skb->len + TH_HEADER_LENGTH + PDU_HEADER_LENGTH;
		newskb = __dev_alloc_skb(len, GFP_ATOMIC | GFP_DMA);

		अगर (!newskb) अणु
			CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_ERROR,
				"%s: %s: __dev_alloc_skb failed",
						__func__, dev->name);

			dev_kमुक्त_skb_any(skb);
			priv->stats.tx_dropped++;
			priv->stats.tx_errors++;
			priv->stats.tx_carrier_errors++;
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
					जाओ करोne;
		पूर्ण
		newskb->protocol = skb->protocol;
		skb_reserve(newskb, TH_HEADER_LENGTH + PDU_HEADER_LENGTH);
		skb_put_data(newskb, skb->data, skb->len);
		dev_kमुक्त_skb_any(skb);
		skb = newskb;
	पूर्ण

	/*
	 * If channels are not running,
	 * notअगरy anybody about a link failure and throw
	 * away packet.
	 */
	अगर ((fsm_माला_लोtate(priv->fsm) != DEV_STATE_RUNNING) ||
	   (fsm_माला_लोtate(grp->fsm) <  MPCG_STATE_XID2INITW)) अणु
		dev_kमुक्त_skb_any(skb);
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): inactive MPCGROUP - dropped",
					CTCM_FUNTAIL, dev->name);
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
		priv->stats.tx_carrier_errors++;
					जाओ करोne;
	पूर्ण

	अगर (ctcm_test_and_set_busy(dev)) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): device busy - dropped",
					CTCM_FUNTAIL, dev->name);
		dev_kमुक्त_skb_any(skb);
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
		priv->stats.tx_carrier_errors++;
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
					जाओ करोne;
	पूर्ण

	netअगर_trans_update(dev);
	अगर (ctcmpc_transmit_skb(priv->channel[CTCM_WRITE], skb) != 0) अणु
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): device error - dropped",
					CTCM_FUNTAIL, dev->name);
		dev_kमुक्त_skb_any(skb);
		priv->stats.tx_dropped++;
		priv->stats.tx_errors++;
		priv->stats.tx_carrier_errors++;
		ctcm_clear_busy(dev);
		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
					जाओ करोne;
	पूर्ण
	ctcm_clear_busy(dev);
करोne:
	अगर (करो_debug)
		MPC_DBF_DEV_NAME(TRACE, dev, "exit");

	वापस NETDEV_TX_OK;	/* handle मुक्तing of skb here */
पूर्ण


/**
 * Sets MTU of an पूर्णांकerface.
 *
 *  dev		Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *  new_mtu	The new MTU to use क्रम this पूर्णांकerface.
 *
 * वापसs 0 on success, -EINVAL अगर MTU is out of valid range.
 *         (valid range is 576 .. 65527). If VM is on the
 *         remote side, maximum MTU is 32760, however this is
 *         not checked here.
 */
अटल पूर्णांक ctcm_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ctcm_priv *priv;
	पूर्णांक max_bufsize;

	priv = dev->ml_priv;
	max_bufsize = priv->channel[CTCM_READ]->max_bufsize;

	अगर (IS_MPC(priv)) अणु
		अगर (new_mtu > max_bufsize - TH_HEADER_LENGTH)
			वापस -EINVAL;
		dev->hard_header_len = TH_HEADER_LENGTH + PDU_HEADER_LENGTH;
	पूर्ण अन्यथा अणु
		अगर (new_mtu > max_bufsize - LL_HEADER_LENGTH - 2)
			वापस -EINVAL;
		dev->hard_header_len = LL_HEADER_LENGTH + 2;
	पूर्ण
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

/**
 * Returns पूर्णांकerface statistics of a device.
 *
 *  dev		Poपूर्णांकer to पूर्णांकerface काष्ठा.
 *
 * वापसs Poपूर्णांकer to stats काष्ठा of this पूर्णांकerface.
 */
अटल काष्ठा net_device_stats *ctcm_stats(काष्ठा net_device *dev)
अणु
	वापस &((काष्ठा ctcm_priv *)dev->ml_priv)->stats;
पूर्ण

अटल व्योम ctcm_मुक्त_netdevice(काष्ठा net_device *dev)
अणु
	काष्ठा ctcm_priv *priv;
	काष्ठा mpc_group *grp;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"%s(%s)", CTCM_FUNTAIL, dev->name);
	priv = dev->ml_priv;
	अगर (priv) अणु
		grp = priv->mpcg;
		अगर (grp) अणु
			अगर (grp->fsm)
				kमुक्त_fsm(grp->fsm);
			dev_kमुक्त_skb(grp->xid_skb);
			dev_kमुक्त_skb(grp->rcvd_xid_skb);
			tasklet_समाप्त(&grp->mpc_tasklet2);
			kमुक्त(grp);
			priv->mpcg = शून्य;
		पूर्ण
		अगर (priv->fsm) अणु
			kमुक्त_fsm(priv->fsm);
			priv->fsm = शून्य;
		पूर्ण
		kमुक्त(priv->xid);
		priv->xid = शून्य;
	/*
	 * Note: kमुक्त(priv); is करोne in "opposite" function of
	 * allocator function probe_device which is हटाओ_device.
	 */
	पूर्ण
#अगर_घोषित MODULE
	मुक्त_netdev(dev);
#पूर्ण_अगर
पूर्ण

काष्ठा mpc_group *ctcmpc_init_mpc_group(काष्ठा ctcm_priv *priv);

अटल स्थिर काष्ठा net_device_ops ctcm_netdev_ops = अणु
	.nकरो_खोलो		= ctcm_खोलो,
	.nकरो_stop		= ctcm_बंद,
	.nकरो_get_stats		= ctcm_stats,
	.nकरो_change_mtu	   	= ctcm_change_mtu,
	.nकरो_start_xmit		= ctcm_tx,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ctcm_mpc_netdev_ops = अणु
	.nकरो_खोलो		= ctcm_खोलो,
	.nकरो_stop		= ctcm_बंद,
	.nकरो_get_stats		= ctcm_stats,
	.nकरो_change_mtu	   	= ctcm_change_mtu,
	.nकरो_start_xmit		= ctcmpc_tx,
पूर्ण;

अटल व्योम ctcm_dev_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_SLIP;
	dev->tx_queue_len = 100;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP;
	dev->min_mtu = 576;
	dev->max_mtu = 65527;
पूर्ण

/*
 * Initialize everything of the net device except the name and the
 * channel काष्ठाs.
 */
अटल काष्ठा net_device *ctcm_init_netdevice(काष्ठा ctcm_priv *priv)
अणु
	काष्ठा net_device *dev;
	काष्ठा mpc_group *grp;
	अगर (!priv)
		वापस शून्य;

	अगर (IS_MPC(priv))
		dev = alloc_netdev(0, MPC_DEVICE_GENE, NET_NAME_UNKNOWN,
				   ctcm_dev_setup);
	अन्यथा
		dev = alloc_netdev(0, CTC_DEVICE_GENE, NET_NAME_UNKNOWN,
				   ctcm_dev_setup);

	अगर (!dev) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_CRIT,
			"%s: MEMORY allocation ERROR",
			CTCM_FUNTAIL);
		वापस शून्य;
	पूर्ण
	dev->ml_priv = priv;
	priv->fsm = init_fsm("ctcmdev", dev_state_names, dev_event_names,
				CTCM_NR_DEV_STATES, CTCM_NR_DEV_EVENTS,
				dev_fsm, dev_fsm_len, GFP_KERNEL);
	अगर (priv->fsm == शून्य) अणु
		CTCMY_DBF_DEV(SETUP, dev, "init_fsm error");
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण
	fsm_newstate(priv->fsm, DEV_STATE_STOPPED);
	fsm_समय_रखोr(priv->fsm, &priv->restart_समयr);

	अगर (IS_MPC(priv)) अणु
		/*  MPC Group Initializations  */
		grp = ctcmpc_init_mpc_group(priv);
		अगर (grp == शून्य) अणु
			MPC_DBF_DEV(SETUP, dev, "init_mpc_group error");
			मुक्त_netdev(dev);
			वापस शून्य;
		पूर्ण
		tasklet_init(&grp->mpc_tasklet2,
				mpc_group_पढ़ोy, (अचिन्हित दीर्घ)dev);
		dev->mtu = MPC_बफ_मानE_DEFAULT -
				TH_HEADER_LENGTH - PDU_HEADER_LENGTH;

		dev->netdev_ops = &ctcm_mpc_netdev_ops;
		dev->hard_header_len = TH_HEADER_LENGTH + PDU_HEADER_LENGTH;
		priv->buffer_size = MPC_बफ_मानE_DEFAULT;
	पूर्ण अन्यथा अणु
		dev->mtu = CTCM_बफ_मानE_DEFAULT - LL_HEADER_LENGTH - 2;
		dev->netdev_ops = &ctcm_netdev_ops;
		dev->hard_header_len = LL_HEADER_LENGTH + 2;
	पूर्ण

	CTCMY_DBF_DEV(SETUP, dev, "finished");

	वापस dev;
पूर्ण

/**
 * Main IRQ handler.
 *
 *  cdev	The ccw_device the पूर्णांकerrupt is क्रम.
 *  पूर्णांकparm	पूर्णांकerruption parameter.
 *  irb		पूर्णांकerruption response block.
 */
अटल व्योम ctcm_irq_handler(काष्ठा ccw_device *cdev,
				अचिन्हित दीर्घ पूर्णांकparm, काष्ठा irb *irb)
अणु
	काष्ठा channel		*ch;
	काष्ठा net_device	*dev;
	काष्ठा ctcm_priv	*priv;
	काष्ठा ccwgroup_device	*cgdev;
	पूर्णांक cstat;
	पूर्णांक dstat;

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
		"Enter %s(%s)", CTCM_FUNTAIL, dev_name(&cdev->dev));

	अगर (ctcm_check_irb_error(cdev, irb))
		वापस;

	cgdev = dev_get_drvdata(&cdev->dev);

	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	/* Check क्रम unsolicited पूर्णांकerrupts. */
	अगर (cgdev == शून्य) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_ERROR,
			"%s(%s) unsolicited irq: c-%02x d-%02x\n",
			CTCM_FUNTAIL, dev_name(&cdev->dev), cstat, dstat);
		dev_warn(&cdev->dev,
			"The adapter received a non-specific IRQ\n");
		वापस;
	पूर्ण

	priv = dev_get_drvdata(&cgdev->dev);

	/* Try to extract channel from driver data. */
	अगर (priv->channel[CTCM_READ]->cdev == cdev)
		ch = priv->channel[CTCM_READ];
	अन्यथा अगर (priv->channel[CTCM_WRITE]->cdev == cdev)
		ch = priv->channel[CTCM_WRITE];
	अन्यथा अणु
		dev_err(&cdev->dev,
			"%s: Internal error: Can't determine channel for "
			"interrupt device %s\n",
			__func__, dev_name(&cdev->dev));
			/* Explain: inconsistent पूर्णांकernal काष्ठाures */
		वापस;
	पूर्ण

	dev = ch->netdev;
	अगर (dev == शून्य) अणु
		dev_err(&cdev->dev,
			"%s Internal error: net_device is NULL, ch = 0x%p\n",
			__func__, ch);
			/* Explain: inconsistent पूर्णांकernal काष्ठाures */
		वापस;
	पूर्ण

	/* Copy पूर्णांकerruption response block. */
	स_नकल(ch->irb, irb, माप(काष्ठा irb));

	/* Issue error message and वापस on subchannel error code */
	अगर (irb->scsw.cmd.cstat) अणु
		fsm_event(ch->fsm, CTC_EVENT_SC_UNKNOWN, ch);
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
			"%s(%s): sub-ch check %s: cs=%02x ds=%02x",
				CTCM_FUNTAIL, dev->name, ch->id, cstat, dstat);
		dev_warn(&cdev->dev,
				"A check occurred on the subchannel\n");
		वापस;
	पूर्ण

	/* Check the reason-code of a unit check */
	अगर (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) अणु
		अगर ((irb->ecw[0] & ch->sense_rc) == 0)
			/* prपूर्णांक it only once */
			CTCM_DBF_TEXT_(TRACE, CTC_DBF_WARN,
				"%s(%s): sense=%02x, ds=%02x",
				CTCM_FUNTAIL, ch->id, irb->ecw[0], dstat);
		ccw_unit_check(ch, irb->ecw[0]);
		वापस;
	पूर्ण
	अगर (irb->scsw.cmd.dstat & DEV_STAT_BUSY) अणु
		अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION)
			fsm_event(ch->fsm, CTC_EVENT_ATTNBUSY, ch);
		अन्यथा
			fsm_event(ch->fsm, CTC_EVENT_BUSY, ch);
		वापस;
	पूर्ण
	अगर (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) अणु
		fsm_event(ch->fsm, CTC_EVENT_ATTN, ch);
		वापस;
	पूर्ण
	अगर ((irb->scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS) ||
	    (irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND) ||
	    (irb->scsw.cmd.stctl ==
	     (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)))
		fsm_event(ch->fsm, CTC_EVENT_FINSTAT, ch);
	अन्यथा
		fsm_event(ch->fsm, CTC_EVENT_IRQ, ch);

पूर्ण

अटल स्थिर काष्ठा device_type ctcm_devtype = अणु
	.name = "ctcm",
	.groups = ctcm_attr_groups,
पूर्ण;

/**
 * Add ctcm specअगरic attributes.
 * Add ctcm निजी data.
 *
 *  cgdev	poपूर्णांकer to ccwgroup_device just added
 *
 * वापसs 0 on success, !0 on failure.
 */
अटल पूर्णांक ctcm_probe_device(काष्ठा ccwgroup_device *cgdev)
अणु
	काष्ठा ctcm_priv *priv;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"%s %p",
			__func__, cgdev);

	अगर (!get_device(&cgdev->dev))
		वापस -ENODEV;

	priv = kzalloc(माप(काष्ठा ctcm_priv), GFP_KERNEL);
	अगर (!priv) अणु
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s: memory allocation failure",
			CTCM_FUNTAIL);
		put_device(&cgdev->dev);
		वापस -ENOMEM;
	पूर्ण
	priv->buffer_size = CTCM_बफ_मानE_DEFAULT;
	cgdev->cdev[0]->handler = ctcm_irq_handler;
	cgdev->cdev[1]->handler = ctcm_irq_handler;
	dev_set_drvdata(&cgdev->dev, priv);
	cgdev->dev.type = &ctcm_devtype;

	वापस 0;
पूर्ण

/**
 * Add a new channel to the list of channels.
 * Keeps the channel list sorted.
 *
 *  cdev	The ccw_device to be added.
 *  type	The type class of the new channel.
 *  priv	Poपूर्णांकs to the निजी data of the ccwgroup_device.
 *
 * वापसs 0 on success, !0 on error.
 */
अटल पूर्णांक add_channel(काष्ठा ccw_device *cdev, क्रमागत ctcm_channel_types type,
				काष्ठा ctcm_priv *priv)
अणु
	काष्ठा channel **c = &channels;
	काष्ठा channel *ch;
	पूर्णांक ccw_num;
	पूर्णांक rc = 0;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
		"%s(%s), type %d, proto %d",
			__func__, dev_name(&cdev->dev),	type, priv->protocol);

	ch = kzalloc(माप(काष्ठा channel), GFP_KERNEL);
	अगर (ch == शून्य)
		वापस -ENOMEM;

	ch->protocol = priv->protocol;
	अगर (IS_MPC(priv)) अणु
		ch->discontact_th = kzalloc(TH_HEADER_LENGTH, GFP_KERNEL);
		अगर (ch->discontact_th == शून्य)
					जाओ nomem_वापस;

		ch->discontact_th->th_blk_flag = TH_DISCONTACT;
		tasklet_init(&ch->ch_disc_tasklet,
			mpc_action_send_discontact, (अचिन्हित दीर्घ)ch);

		tasklet_init(&ch->ch_tasklet, ctcmpc_bh, (अचिन्हित दीर्घ)ch);
		ch->max_bufsize = (MPC_बफ_मानE_DEFAULT - 35);
		ccw_num = 17;
	पूर्ण अन्यथा
		ccw_num = 8;

	ch->ccw = kसुस्मृति(ccw_num, माप(काष्ठा ccw1), GFP_KERNEL | GFP_DMA);
	अगर (ch->ccw == शून्य)
					जाओ nomem_वापस;

	ch->cdev = cdev;
	snम_लिखो(ch->id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev->dev));
	ch->type = type;

	/**
	 * "static" ccws are used in the following way:
	 *
	 * ccw[0..2] (Channel program क्रम generic I/O):
	 *           0: prepare
	 *           1: पढ़ो or ग_लिखो (depending on direction) with fixed
	 *              buffer (idal allocated once when buffer is allocated)
	 *           2: nop
	 * ccw[3..5] (Channel program क्रम direct ग_लिखो of packets)
	 *           3: prepare
	 *           4: ग_लिखो (idal allocated on every ग_लिखो).
	 *           5: nop
	 * ccw[6..7] (Channel program क्रम initial channel setup):
	 *           6: set extended mode
	 *           7: nop
	 *
	 * ch->ccw[0..5] are initialized in ch_action_start because
	 * the channel's direction is yet unknown here.
	 *
	 * ccws used क्रम xid2 negotiations
	 *  ch-ccw[8-14] need to be used क्रम the XID exchange either
	 *    X side XID2 Processing
	 *       8:  ग_लिखो control
	 *       9:  ग_लिखो th
	 *	     10: ग_लिखो XID
	 *	     11: पढ़ो th from secondary
	 *	     12: पढ़ो XID   from secondary
	 *	     13: पढ़ो 4 byte ID
	 *	     14: nop
	 *    Y side XID Processing
	 *	     8:  sense
	 *       9:  पढ़ो th
	 *	     10: पढ़ो XID
	 *	     11: ग_लिखो th
	 *	     12: ग_लिखो XID
	 *	     13: ग_लिखो 4 byte ID
	 *	     14: nop
	 *
	 *  ccws used क्रम द्विगुन noop due to VM timing issues
	 *  which result in unrecoverable Busy on channel
	 *       15: nop
	 *       16: nop
	 */
	ch->ccw[6].cmd_code	= CCW_CMD_SET_EXTENDED;
	ch->ccw[6].flags	= CCW_FLAG_SLI;

	ch->ccw[7].cmd_code	= CCW_CMD_NOOP;
	ch->ccw[7].flags	= CCW_FLAG_SLI;

	अगर (IS_MPC(priv)) अणु
		ch->ccw[15].cmd_code = CCW_CMD_WRITE;
		ch->ccw[15].flags    = CCW_FLAG_SLI | CCW_FLAG_CC;
		ch->ccw[15].count    = TH_HEADER_LENGTH;
		ch->ccw[15].cda      = virt_to_phys(ch->discontact_th);

		ch->ccw[16].cmd_code = CCW_CMD_NOOP;
		ch->ccw[16].flags    = CCW_FLAG_SLI;

		ch->fsm = init_fsm(ch->id, ctc_ch_state_names,
				ctc_ch_event_names, CTC_MPC_NR_STATES,
				CTC_MPC_NR_EVENTS, ctcmpc_ch_fsm,
				mpc_ch_fsm_len, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		ch->fsm = init_fsm(ch->id, ctc_ch_state_names,
				ctc_ch_event_names, CTC_NR_STATES,
				CTC_NR_EVENTS, ch_fsm,
				ch_fsm_len, GFP_KERNEL);
	पूर्ण
	अगर (ch->fsm == शून्य)
				जाओ nomem_वापस;

	fsm_newstate(ch->fsm, CTC_STATE_IDLE);

	ch->irb = kzalloc(माप(काष्ठा irb), GFP_KERNEL);
	अगर (ch->irb == शून्य)
				जाओ nomem_वापस;

	जबतक (*c && ctcm_less_than((*c)->id, ch->id))
		c = &(*c)->next;

	अगर (*c && (!म_भेदन((*c)->id, ch->id, CTCM_ID_SIZE))) अणु
		CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
				"%s (%s) already in list, using old entry",
				__func__, (*c)->id);

				जाओ मुक्त_वापस;
	पूर्ण

	spin_lock_init(&ch->collect_lock);

	fsm_समय_रखोr(ch->fsm, &ch->समयr);
	skb_queue_head_init(&ch->io_queue);
	skb_queue_head_init(&ch->collect_queue);

	अगर (IS_MPC(priv)) अणु
		fsm_समय_रखोr(ch->fsm, &ch->sweep_समयr);
		skb_queue_head_init(&ch->sweep_queue);
	पूर्ण
	ch->next = *c;
	*c = ch;
	वापस 0;

nomem_वापस:
	rc = -ENOMEM;

मुक्त_वापस:	/* note that all channel poपूर्णांकers are 0 or valid */
	kमुक्त(ch->ccw);
	kमुक्त(ch->discontact_th);
	kमुक्त_fsm(ch->fsm);
	kमुक्त(ch->irb);
	kमुक्त(ch);
	वापस rc;
पूर्ण

/*
 * Return type of a detected device.
 */
अटल क्रमागत ctcm_channel_types get_channel_type(काष्ठा ccw_device_id *id)
अणु
	क्रमागत ctcm_channel_types type;
	type = (क्रमागत ctcm_channel_types)id->driver_info;

	अगर (type == ctcm_channel_type_ficon)
		type = ctcm_channel_type_escon;

	वापस type;
पूर्ण

/**
 *
 * Setup an पूर्णांकerface.
 *
 *  cgdev	Device to be setup.
 *
 * वापसs 0 on success, !0 on failure.
 */
अटल पूर्णांक ctcm_new_device(काष्ठा ccwgroup_device *cgdev)
अणु
	अक्षर पढ़ो_id[CTCM_ID_SIZE];
	अक्षर ग_लिखो_id[CTCM_ID_SIZE];
	पूर्णांक direction;
	क्रमागत ctcm_channel_types type;
	काष्ठा ctcm_priv *priv;
	काष्ठा net_device *dev;
	काष्ठा ccw_device *cdev0;
	काष्ठा ccw_device *cdev1;
	काष्ठा channel *पढ़ोc;
	काष्ठा channel *ग_लिखोc;
	पूर्णांक ret;
	पूर्णांक result;

	priv = dev_get_drvdata(&cgdev->dev);
	अगर (!priv) अणु
		result = -ENODEV;
		जाओ out_err_result;
	पूर्ण

	cdev0 = cgdev->cdev[0];
	cdev1 = cgdev->cdev[1];

	type = get_channel_type(&cdev0->id);

	snम_लिखो(पढ़ो_id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev0->dev));
	snम_लिखो(ग_लिखो_id, CTCM_ID_SIZE, "ch-%s", dev_name(&cdev1->dev));

	ret = add_channel(cdev0, type, priv);
	अगर (ret) अणु
		result = ret;
		जाओ out_err_result;
	पूर्ण
	ret = add_channel(cdev1, type, priv);
	अगर (ret) अणु
		result = ret;
		जाओ out_हटाओ_channel1;
	पूर्ण

	ret = ccw_device_set_online(cdev0);
	अगर (ret != 0) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s(%s) set_online rc=%d",
				CTCM_FUNTAIL, पढ़ो_id, ret);
		result = -EIO;
		जाओ out_हटाओ_channel2;
	पूर्ण

	ret = ccw_device_set_online(cdev1);
	अगर (ret != 0) अणु
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s(%s) set_online rc=%d",
				CTCM_FUNTAIL, ग_लिखो_id, ret);

		result = -EIO;
		जाओ out_ccw1;
	पूर्ण

	dev = ctcm_init_netdevice(priv);
	अगर (dev == शून्य) अणु
		result = -ENODEV;
		जाओ out_ccw2;
	पूर्ण

	क्रम (direction = CTCM_READ; direction <= CTCM_WRITE; direction++) अणु
		priv->channel[direction] =
			channel_get(type, direction == CTCM_READ ?
				पढ़ो_id : ग_लिखो_id, direction);
		अगर (priv->channel[direction] == शून्य) अणु
			अगर (direction == CTCM_WRITE)
				channel_मुक्त(priv->channel[CTCM_READ]);
			result = -ENODEV;
			जाओ out_dev;
		पूर्ण
		priv->channel[direction]->netdev = dev;
		priv->channel[direction]->protocol = priv->protocol;
		priv->channel[direction]->max_bufsize = priv->buffer_size;
	पूर्ण
	/* sysfs magic */
	SET_NETDEV_DEV(dev, &cgdev->dev);

	अगर (रेजिस्टर_netdev(dev)) अणु
		result = -ENODEV;
		जाओ out_dev;
	पूर्ण

	strlcpy(priv->fsm->name, dev->name, माप(priv->fsm->name));

	dev_info(&dev->dev,
		"setup OK : r/w = %s/%s, protocol : %d\n",
			priv->channel[CTCM_READ]->id,
			priv->channel[CTCM_WRITE]->id, priv->protocol);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
		"setup(%s) OK : r/w = %s/%s, protocol : %d", dev->name,
			priv->channel[CTCM_READ]->id,
			priv->channel[CTCM_WRITE]->id, priv->protocol);

	वापस 0;
out_dev:
	ctcm_मुक्त_netdevice(dev);
out_ccw2:
	ccw_device_set_offline(cgdev->cdev[1]);
out_ccw1:
	ccw_device_set_offline(cgdev->cdev[0]);
out_हटाओ_channel2:
	पढ़ोc = channel_get(type, पढ़ो_id, CTCM_READ);
	channel_हटाओ(पढ़ोc);
out_हटाओ_channel1:
	ग_लिखोc = channel_get(type, ग_लिखो_id, CTCM_WRITE);
	channel_हटाओ(ग_लिखोc);
out_err_result:
	वापस result;
पूर्ण

/**
 * Shutकरोwn an पूर्णांकerface.
 *
 *  cgdev	Device to be shut करोwn.
 *
 * वापसs 0 on success, !0 on failure.
 */
अटल पूर्णांक ctcm_shutकरोwn_device(काष्ठा ccwgroup_device *cgdev)
अणु
	काष्ठा ctcm_priv *priv;
	काष्ठा net_device *dev;

	priv = dev_get_drvdata(&cgdev->dev);
	अगर (!priv)
		वापस -ENODEV;

	अगर (priv->channel[CTCM_READ]) अणु
		dev = priv->channel[CTCM_READ]->netdev;
		CTCM_DBF_DEV(SETUP, dev, "");
		/* Close the device */
		ctcm_बंद(dev);
		dev->flags &= ~IFF_RUNNING;
		channel_मुक्त(priv->channel[CTCM_READ]);
	पूर्ण अन्यथा
		dev = शून्य;

	अगर (priv->channel[CTCM_WRITE])
		channel_मुक्त(priv->channel[CTCM_WRITE]);

	अगर (dev) अणु
		unरेजिस्टर_netdev(dev);
		ctcm_मुक्त_netdevice(dev);
	पूर्ण

	अगर (priv->fsm)
		kमुक्त_fsm(priv->fsm);

	ccw_device_set_offline(cgdev->cdev[1]);
	ccw_device_set_offline(cgdev->cdev[0]);
	channel_हटाओ(priv->channel[CTCM_READ]);
	channel_हटाओ(priv->channel[CTCM_WRITE]);
	priv->channel[CTCM_READ] = priv->channel[CTCM_WRITE] = शून्य;

	वापस 0;

पूर्ण


अटल व्योम ctcm_हटाओ_device(काष्ठा ccwgroup_device *cgdev)
अणु
	काष्ठा ctcm_priv *priv = dev_get_drvdata(&cgdev->dev);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO,
			"removing device %p, proto : %d",
			cgdev, priv->protocol);

	अगर (cgdev->state == CCWGROUP_ONLINE)
		ctcm_shutकरोwn_device(cgdev);
	dev_set_drvdata(&cgdev->dev, शून्य);
	kमुक्त(priv);
	put_device(&cgdev->dev);
पूर्ण

अटल काष्ठा ccw_device_id ctcm_ids[] = अणु
	अणुCCW_DEVICE(0x3088, 0x08), .driver_info = ctcm_channel_type_parallelपूर्ण,
	अणुCCW_DEVICE(0x3088, 0x1e), .driver_info = ctcm_channel_type_ficonपूर्ण,
	अणुCCW_DEVICE(0x3088, 0x1f), .driver_info = ctcm_channel_type_esconपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ccw, ctcm_ids);

अटल काष्ठा ccw_driver ctcm_ccw_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= "ctcm",
	पूर्ण,
	.ids	= ctcm_ids,
	.probe	= ccwgroup_probe_ccwdev,
	.हटाओ	= ccwgroup_हटाओ_ccwdev,
	.पूर्णांक_class = IRQIO_CTC,
पूर्ण;

अटल काष्ठा ccwgroup_driver ctcm_group_driver = अणु
	.driver = अणु
		.owner	= THIS_MODULE,
		.name	= CTC_DRIVER_NAME,
	पूर्ण,
	.ccw_driver  = &ctcm_ccw_driver,
	.setup	     = ctcm_probe_device,
	.हटाओ      = ctcm_हटाओ_device,
	.set_online  = ctcm_new_device,
	.set_offline = ctcm_shutकरोwn_device,
पूर्ण;

अटल sमाप_प्रकार group_store(काष्ठा device_driver *ddrv, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	पूर्णांक err;

	err = ccwgroup_create_dev(ctcm_root_dev, &ctcm_group_driver, 2, buf);
	वापस err ? err : count;
पूर्ण
अटल DRIVER_ATTR_WO(group);

अटल काष्ठा attribute *ctcm_drv_attrs[] = अणु
	&driver_attr_group.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group ctcm_drv_attr_group = अणु
	.attrs = ctcm_drv_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *ctcm_drv_attr_groups[] = अणु
	&ctcm_drv_attr_group,
	शून्य,
पूर्ण;

/*
 * Module related routines
 */

/*
 * Prepare to be unloaded. Free IRQ's and release all resources.
 * This is called just beक्रमe this module is unloaded. It is
 * not called, अगर the usage count is !0, so we करोn't need to check
 * क्रम that.
 */
अटल व्योम __निकास ctcm_निकास(व्योम)
अणु
	ccwgroup_driver_unरेजिस्टर(&ctcm_group_driver);
	ccw_driver_unरेजिस्टर(&ctcm_ccw_driver);
	root_device_unरेजिस्टर(ctcm_root_dev);
	ctcm_unरेजिस्टर_dbf_views();
	pr_info("CTCM driver unloaded\n");
पूर्ण

/*
 * Prपूर्णांक Banner.
 */
अटल व्योम prपूर्णांक_banner(व्योम)
अणु
	pr_info("CTCM driver initialized\n");
पूर्ण

/**
 * Initialize module.
 * This is called just after the module is loaded.
 *
 * वापसs 0 on success, !0 on error.
 */
अटल पूर्णांक __init ctcm_init(व्योम)
अणु
	पूर्णांक ret;

	channels = शून्य;

	ret = ctcm_रेजिस्टर_dbf_views();
	अगर (ret)
		जाओ out_err;
	ctcm_root_dev = root_device_रेजिस्टर("ctcm");
	ret = PTR_ERR_OR_ZERO(ctcm_root_dev);
	अगर (ret)
		जाओ रेजिस्टर_err;
	ret = ccw_driver_रेजिस्टर(&ctcm_ccw_driver);
	अगर (ret)
		जाओ ccw_err;
	ctcm_group_driver.driver.groups = ctcm_drv_attr_groups;
	ret = ccwgroup_driver_रेजिस्टर(&ctcm_group_driver);
	अगर (ret)
		जाओ ccwgroup_err;
	prपूर्णांक_banner();
	वापस 0;

ccwgroup_err:
	ccw_driver_unरेजिस्टर(&ctcm_ccw_driver);
ccw_err:
	root_device_unरेजिस्टर(ctcm_root_dev);
रेजिस्टर_err:
	ctcm_unरेजिस्टर_dbf_views();
out_err:
	pr_err("%s / Initializing the ctcm device driver failed, ret = %d\n",
		__func__, ret);
	वापस ret;
पूर्ण

module_init(ctcm_init);
module_निकास(ctcm_निकास);

MODULE_AUTHOR("Peter Tiedemann <ptiedem@de.ibm.com>");
MODULE_DESCRIPTION("Network driver for S/390 CTC + CTCMPC (SNA)");
MODULE_LICENSE("GPL");

