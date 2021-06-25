<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Shared Transport Line discipline driver Core
 *	This hooks up ST KIM driver and ST LL driver
 *  Copyright (C) 2009-2010 Texas Instruments
 *  Author: Pavan Savoy <pavan_savoy@ti.com>
 */

#घोषणा pr_fmt(fmt)	"(stc): " fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/tty.h>

#समावेश <linux/seq_file.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/ti_wilink_st.h>

बाह्य व्योम st_kim_recv(व्योम *, स्थिर अचिन्हित अक्षर *, दीर्घ);
व्योम st_पूर्णांक_recv(व्योम *, स्थिर अचिन्हित अक्षर *, दीर्घ);
/*
 * function poपूर्णांकer poपूर्णांकing to either,
 * st_kim_recv during registration to receive fw करोwnload responses
 * st_पूर्णांक_recv after registration to receive proto stack responses
 */
अटल व्योम (*st_recv) (व्योम *, स्थिर अचिन्हित अक्षर *, दीर्घ);

/********************************************************************/
अटल व्योम add_channel_to_table(काष्ठा st_data_s *st_gdata,
		काष्ठा st_proto_s *new_proto)
अणु
	pr_info("%s: id %d\n", __func__, new_proto->chnl_id);
	/* list now has the channel id as index itself */
	st_gdata->list[new_proto->chnl_id] = new_proto;
	st_gdata->is_रेजिस्टरed[new_proto->chnl_id] = true;
पूर्ण

अटल व्योम हटाओ_channel_from_table(काष्ठा st_data_s *st_gdata,
		काष्ठा st_proto_s *proto)
अणु
	pr_info("%s: id %d\n", __func__, proto->chnl_id);
/*	st_gdata->list[proto->chnl_id] = शून्य; */
	st_gdata->is_रेजिस्टरed[proto->chnl_id] = false;
पूर्ण

/*
 * called from KIM during firmware करोwnload.
 *
 * This is a wrapper function to tty->ops->ग_लिखो_room.
 * It वापसs number of मुक्त space available in
 * uart tx buffer.
 */
पूर्णांक st_get_uart_wr_room(काष्ठा st_data_s *st_gdata)
अणु
	काष्ठा tty_काष्ठा *tty;
	अगर (unlikely(st_gdata == शून्य || st_gdata->tty == शून्य)) अणु
		pr_err("tty unavailable to perform write");
		वापस -1;
	पूर्ण
	tty = st_gdata->tty;
	वापस tty->ops->ग_लिखो_room(tty);
पूर्ण

/*
 * can be called in from
 * -- KIM (during fw करोwnload)
 * -- ST Core (during st_ग_लिखो)
 *
 *  This is the पूर्णांकernal ग_लिखो function - a wrapper
 *  to tty->ops->ग_लिखो
 */
पूर्णांक st_पूर्णांक_ग_लिखो(काष्ठा st_data_s *st_gdata,
	स्थिर अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	काष्ठा tty_काष्ठा *tty;
	अगर (unlikely(st_gdata == शून्य || st_gdata->tty == शून्य)) अणु
		pr_err("tty unavailable to perform write");
		वापस -EINVAL;
	पूर्ण
	tty = st_gdata->tty;
#अगर_घोषित VERBOSE
	prपूर्णांक_hex_dump(KERN_DEBUG, "<out<", DUMP_PREFIX_NONE,
		16, 1, data, count, 0);
#पूर्ण_अगर
	वापस tty->ops->ग_लिखो(tty, data, count);

पूर्ण

/*
 * push the skb received to relevant
 * protocol stacks
 */
अटल व्योम st_send_frame(अचिन्हित अक्षर chnl_id, काष्ठा st_data_s *st_gdata)
अणु
	pr_debug(" %s(prot:%d) ", __func__, chnl_id);

	अगर (unlikely
	    (st_gdata == शून्य || st_gdata->rx_skb == शून्य
	     || st_gdata->is_रेजिस्टरed[chnl_id] == false)) अणु
		pr_err("chnl_id %d not registered, no data to send?",
			   chnl_id);
		kमुक्त_skb(st_gdata->rx_skb);
		वापस;
	पूर्ण
	/*
	 * this cannot fail
	 * this shouldn't take दीर्घ
	 * - should be just skb_queue_tail क्रम the
	 *   protocol stack driver
	 */
	अगर (likely(st_gdata->list[chnl_id]->recv != शून्य)) अणु
		अगर (unlikely
			(st_gdata->list[chnl_id]->recv
			(st_gdata->list[chnl_id]->priv_data, st_gdata->rx_skb)
			     != 0)) अणु
			pr_err(" proto stack %d's ->recv failed", chnl_id);
			kमुक्त_skb(st_gdata->rx_skb);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err(" proto stack %d's ->recv null", chnl_id);
		kमुक्त_skb(st_gdata->rx_skb);
	पूर्ण
	वापस;
पूर्ण

/*
 * st_reg_complete - to call registration complete callbacks
 * of all protocol stack drivers
 * This function is being called with spin lock held, protocol drivers are
 * only expected to complete their रुकोs and करो nothing more than that.
 */
अटल व्योम st_reg_complete(काष्ठा st_data_s *st_gdata, पूर्णांक err)
अणु
	अचिन्हित अक्षर i = 0;
	pr_info(" %s ", __func__);
	क्रम (i = 0; i < ST_MAX_CHANNELS; i++) अणु
		अगर (likely(st_gdata != शून्य &&
			st_gdata->is_रेजिस्टरed[i] == true &&
				st_gdata->list[i]->reg_complete_cb != शून्य)) अणु
			st_gdata->list[i]->reg_complete_cb
				(st_gdata->list[i]->priv_data, err);
			pr_info("protocol %d's cb sent %d\n", i, err);
			अगर (err) अणु /* cleanup रेजिस्टरed protocol */
				st_gdata->is_रेजिस्टरed[i] = false;
				अगर (st_gdata->protos_रेजिस्टरed)
					st_gdata->protos_रेजिस्टरed--;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक st_check_data_len(काष्ठा st_data_s *st_gdata,
	अचिन्हित अक्षर chnl_id, पूर्णांक len)
अणु
	पूर्णांक room = skb_tailroom(st_gdata->rx_skb);

	pr_debug("len %d room %d", len, room);

	अगर (!len) अणु
		/*
		 * Received packet has only packet header and
		 * has zero length payload. So, ask ST CORE to
		 * क्रमward the packet to protocol driver (BT/FM/GPS)
		 */
		st_send_frame(chnl_id, st_gdata);

	पूर्ण अन्यथा अगर (len > room) अणु
		/*
		 * Received packet's payload length is larger.
		 * We can't accommodate it in created skb.
		 */
		pr_err("Data length is too large len %d room %d", len,
			   room);
		kमुक्त_skb(st_gdata->rx_skb);
	पूर्ण अन्यथा अणु
		/*
		 * Packet header has non-zero payload length and
		 * we have enough space in created skb. Lets पढ़ो
		 * payload data */
		st_gdata->rx_state = ST_W4_DATA;
		st_gdata->rx_count = len;
		वापस len;
	पूर्ण

	/* Change ST state to जारी to process next packet */
	st_gdata->rx_state = ST_W4_PACKET_TYPE;
	st_gdata->rx_skb = शून्य;
	st_gdata->rx_count = 0;
	st_gdata->rx_chnl = 0;

	वापस 0;
पूर्ण

/*
 * st_wakeup_ack - पूर्णांकernal function क्रम action when wake-up ack
 *	received
 */
अटल अंतरभूत व्योम st_wakeup_ack(काष्ठा st_data_s *st_gdata,
	अचिन्हित अक्षर cmd)
अणु
	काष्ठा sk_buff *रुकोing_skb;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&st_gdata->lock, flags);
	/*
	 * de-Q from रुकोQ and Q in txQ now that the
	 * chip is awake
	 */
	जबतक ((रुकोing_skb = skb_dequeue(&st_gdata->tx_रुकोq)))
		skb_queue_tail(&st_gdata->txq, रुकोing_skb);

	/* state क्रमwarded to ST LL */
	st_ll_sleep_state(st_gdata, (अचिन्हित दीर्घ)cmd);
	spin_unlock_irqrestore(&st_gdata->lock, flags);

	/* wake up to send the recently copied skbs from रुकोQ */
	st_tx_wakeup(st_gdata);
पूर्ण

/*
 * st_पूर्णांक_recv - ST's पूर्णांकernal receive function.
 *	Decodes received RAW data and क्रमwards to corresponding
 *	client drivers (Bluetooth,FM,GPS..etc).
 *	This can receive various types of packets,
 *	HCI-Events, ACL, SCO, 4 types of HCI-LL PM packets
 *	CH-8 packets from FM, CH-9 packets from GPS cores.
 */
व्योम st_पूर्णांक_recv(व्योम *disc_data,
	स्थिर अचिन्हित अक्षर *data, दीर्घ count)
अणु
	अक्षर *ptr;
	काष्ठा st_proto_s *proto;
	अचिन्हित लघु payload_len = 0;
	पूर्णांक len = 0;
	अचिन्हित अक्षर type = 0;
	अचिन्हित अक्षर *plen;
	काष्ठा st_data_s *st_gdata = (काष्ठा st_data_s *)disc_data;
	अचिन्हित दीर्घ flags;

	ptr = (अक्षर *)data;
	/* tty_receive sent null ? */
	अगर (unlikely(ptr == शून्य) || (st_gdata == शून्य)) अणु
		pr_err(" received null from TTY ");
		वापस;
	पूर्ण

	pr_debug("count %ld rx_state %ld"
		   "rx_count %ld", count, st_gdata->rx_state,
		   st_gdata->rx_count);

	spin_lock_irqsave(&st_gdata->lock, flags);
	/* Decode received bytes here */
	जबतक (count) अणु
		अगर (st_gdata->rx_count) अणु
			len = min_t(अचिन्हित पूर्णांक, st_gdata->rx_count, count);
			skb_put_data(st_gdata->rx_skb, ptr, len);
			st_gdata->rx_count -= len;
			count -= len;
			ptr += len;

			अगर (st_gdata->rx_count)
				जारी;

			/* Check ST RX state machine , where are we? */
			चयन (st_gdata->rx_state) अणु
			/* Waiting क्रम complete packet ? */
			हाल ST_W4_DATA:
				pr_debug("Complete pkt received");
				/*
				 * Ask ST CORE to क्रमward
				 * the packet to protocol driver
				 */
				st_send_frame(st_gdata->rx_chnl, st_gdata);

				st_gdata->rx_state = ST_W4_PACKET_TYPE;
				st_gdata->rx_skb = शून्य;
				जारी;
			/* parse the header to know details */
			हाल ST_W4_HEADER:
				proto = st_gdata->list[st_gdata->rx_chnl];
				plen =
				&st_gdata->rx_skb->data
				[proto->offset_len_in_hdr];
				pr_debug("plen pointing to %x\n", *plen);
				अगर (proto->len_size == 1) /* 1 byte len field */
					payload_len = *(अचिन्हित अक्षर *)plen;
				अन्यथा अगर (proto->len_size == 2)
					payload_len =
					__le16_to_cpu(*(अचिन्हित लघु *)plen);
				अन्यथा
					pr_info("%s: invalid length "
					"for id %d\n",
					__func__, proto->chnl_id);
				st_check_data_len(st_gdata, proto->chnl_id,
						payload_len);
				pr_debug("off %d, pay len %d\n",
					proto->offset_len_in_hdr, payload_len);
				जारी;
			पूर्ण	/* end of चयन rx_state */
		पूर्ण

		/* end of अगर rx_count */

		/*
		 * Check first byte of packet and identअगरy module
		 * owner (BT/FM/GPS)
		 */
		चयन (*ptr) अणु
		हाल LL_SLEEP_IND:
		हाल LL_SLEEP_ACK:
		हाल LL_WAKE_UP_IND:
			pr_debug("PM packet");
			/*
			 * this takes appropriate action based on
			 * sleep state received --
			 */
			st_ll_sleep_state(st_gdata, *ptr);
			/*
			 * अगर WAKEUP_IND collides copy from रुकोq to txq
			 * and assume chip awake
			 */
			spin_unlock_irqrestore(&st_gdata->lock, flags);
			अगर (st_ll_माला_लोtate(st_gdata) == ST_LL_AWAKE)
				st_wakeup_ack(st_gdata, LL_WAKE_UP_ACK);
			spin_lock_irqsave(&st_gdata->lock, flags);

			ptr++;
			count--;
			जारी;
		हाल LL_WAKE_UP_ACK:
			pr_debug("PM packet");

			spin_unlock_irqrestore(&st_gdata->lock, flags);
			/* wake up ack received */
			st_wakeup_ack(st_gdata, *ptr);
			spin_lock_irqsave(&st_gdata->lock, flags);

			ptr++;
			count--;
			जारी;
			/* Unknow packet? */
		शेष:
			type = *ptr;

			/*
			 * Default हाल means non-HCILL packets,
			 * possibilities are packets क्रम:
			 * (a) valid protocol -  Supported Protocols within
			 *     the ST_MAX_CHANNELS.
			 * (b) रेजिस्टरed protocol - Checked by
			 *     "st_gdata->list[type] == NULL)" are supported
			 *     protocols only.
			 *  Rules out any invalid protocol and
			 *  unरेजिस्टरed protocols with channel ID < 16.
			 */

			अगर ((type >= ST_MAX_CHANNELS) ||
					(st_gdata->list[type] == शून्य)) अणु
				pr_err("chip/interface misbehavior: "
						"dropping frame starting "
						"with 0x%02x\n", type);
				जाओ करोne;
			पूर्ण

			st_gdata->rx_skb = alloc_skb(
					st_gdata->list[type]->max_frame_size,
					GFP_ATOMIC);
			अगर (st_gdata->rx_skb == शून्य) अणु
				pr_err("out of memory: dropping\n");
				जाओ करोne;
			पूर्ण

			skb_reserve(st_gdata->rx_skb,
					st_gdata->list[type]->reserve);
			/* next 2 required क्रम BT only */
			st_gdata->rx_skb->cb[0] = type; /*pkt_type*/
			st_gdata->rx_skb->cb[1] = 0; /*incoming*/
			st_gdata->rx_chnl = *ptr;
			st_gdata->rx_state = ST_W4_HEADER;
			st_gdata->rx_count = st_gdata->list[type]->hdr_len;
			pr_debug("rx_count %ld\n", st_gdata->rx_count);
		पूर्ण
		ptr++;
		count--;
	पूर्ण
करोne:
	spin_unlock_irqrestore(&st_gdata->lock, flags);
	pr_debug("done %s", __func__);
	वापस;
पूर्ण

/*
 * st_पूर्णांक_dequeue - पूर्णांकernal de-Q function.
 *	If the previous data set was not written
 *	completely, वापस that skb which has the pending data.
 *	In normal हालs, वापस top of txq.
 */
अटल काष्ठा sk_buff *st_पूर्णांक_dequeue(काष्ठा st_data_s *st_gdata)
अणु
	काष्ठा sk_buff *वापसing_skb;

	pr_debug("%s", __func__);
	अगर (st_gdata->tx_skb != शून्य) अणु
		वापसing_skb = st_gdata->tx_skb;
		st_gdata->tx_skb = शून्य;
		वापस वापसing_skb;
	पूर्ण
	वापस skb_dequeue(&st_gdata->txq);
पूर्ण

/*
 * st_पूर्णांक_enqueue - पूर्णांकernal Q-ing function.
 *	Will either Q the skb to txq or the tx_रुकोq
 *	depending on the ST LL state.
 *	If the chip is asleep, then Q it onto रुकोq and
 *	wakeup the chip.
 *	txq and रुकोq needs protection since the other contexts
 *	may be sending data, waking up chip.
 */
अटल व्योम st_पूर्णांक_enqueue(काष्ठा st_data_s *st_gdata, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags = 0;

	pr_debug("%s", __func__);
	spin_lock_irqsave(&st_gdata->lock, flags);

	चयन (st_ll_माला_लोtate(st_gdata)) अणु
	हाल ST_LL_AWAKE:
		pr_debug("ST LL is AWAKE, sending normally");
		skb_queue_tail(&st_gdata->txq, skb);
		अवरोध;
	हाल ST_LL_ASLEEP_TO_AWAKE:
		skb_queue_tail(&st_gdata->tx_रुकोq, skb);
		अवरोध;
	हाल ST_LL_AWAKE_TO_ASLEEP:
		pr_err("ST LL is illegal state(%ld),"
			   "purging received skb.", st_ll_माला_लोtate(st_gdata));
		kमुक्त_skb(skb);
		अवरोध;
	हाल ST_LL_ASLEEP:
		skb_queue_tail(&st_gdata->tx_रुकोq, skb);
		st_ll_wakeup(st_gdata);
		अवरोध;
	शेष:
		pr_err("ST LL is illegal state(%ld),"
			   "purging received skb.", st_ll_माला_लोtate(st_gdata));
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&st_gdata->lock, flags);
	pr_debug("done %s", __func__);
	वापस;
पूर्ण

/*
 * पूर्णांकernal wakeup function
 * called from either
 * - TTY layer when ग_लिखो's finished
 * - st_ग_लिखो (in context of the protocol stack)
 */
अटल व्योम work_fn_ग_लिखो_wakeup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा st_data_s *st_gdata = container_of(work, काष्ठा st_data_s,
			work_ग_लिखो_wakeup);

	st_tx_wakeup((व्योम *)st_gdata);
पूर्ण
व्योम st_tx_wakeup(काष्ठा st_data_s *st_data)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;	/* क्रम irq save flags */
	pr_debug("%s", __func__);
	/* check क्रम sending & set flag sending here */
	अगर (test_and_set_bit(ST_TX_SENDING, &st_data->tx_state)) अणु
		pr_debug("ST already sending");
		/* keep sending */
		set_bit(ST_TX_WAKEUP, &st_data->tx_state);
		वापस;
		/* TX_WAKEUP will be checked in another
		 * context
		 */
	पूर्ण
	करो अणु			/* come back अगर st_tx_wakeup is set */
		/* woke-up to ग_लिखो */
		clear_bit(ST_TX_WAKEUP, &st_data->tx_state);
		जबतक ((skb = st_पूर्णांक_dequeue(st_data))) अणु
			पूर्णांक len;
			spin_lock_irqsave(&st_data->lock, flags);
			/* enable wake-up from TTY */
			set_bit(TTY_DO_WRITE_WAKEUP, &st_data->tty->flags);
			len = st_पूर्णांक_ग_लिखो(st_data, skb->data, skb->len);
			skb_pull(skb, len);
			/* अगर skb->len = len as expected, skb->len=0 */
			अगर (skb->len) अणु
				/* would be the next skb to be sent */
				st_data->tx_skb = skb;
				spin_unlock_irqrestore(&st_data->lock, flags);
				अवरोध;
			पूर्ण
			kमुक्त_skb(skb);
			spin_unlock_irqrestore(&st_data->lock, flags);
		पूर्ण
		/* अगर wake-up is set in another context- restart sending */
	पूर्ण जबतक (test_bit(ST_TX_WAKEUP, &st_data->tx_state));

	/* clear flag sending */
	clear_bit(ST_TX_SENDING, &st_data->tx_state);
पूर्ण

/********************************************************************/
/* functions called from ST KIM
*/
व्योम kim_st_list_protocols(काष्ठा st_data_s *st_gdata, व्योम *buf)
अणु
	seq_म_लिखो(buf, "[%d]\nBT=%c\nFM=%c\nGPS=%c\n",
			st_gdata->protos_रेजिस्टरed,
			st_gdata->is_रेजिस्टरed[0x04] == true ? 'R' : 'U',
			st_gdata->is_रेजिस्टरed[0x08] == true ? 'R' : 'U',
			st_gdata->is_रेजिस्टरed[0x09] == true ? 'R' : 'U');
पूर्ण

/********************************************************************/
/*
 * functions called from protocol stack drivers
 * to be EXPORT-ed
 */
दीर्घ st_रेजिस्टर(काष्ठा st_proto_s *new_proto)
अणु
	काष्ठा st_data_s	*st_gdata;
	दीर्घ err = 0;
	अचिन्हित दीर्घ flags = 0;

	st_kim_ref(&st_gdata, 0);
	अगर (st_gdata == शून्य || new_proto == शून्य || new_proto->recv == शून्य
	    || new_proto->reg_complete_cb == शून्य) अणु
		pr_err("gdata/new_proto/recv or reg_complete_cb not ready");
		वापस -EINVAL;
	पूर्ण

	अगर (new_proto->chnl_id >= ST_MAX_CHANNELS) अणु
		pr_err("chnl_id %d not supported", new_proto->chnl_id);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (st_gdata->is_रेजिस्टरed[new_proto->chnl_id] == true) अणु
		pr_err("chnl_id %d already registered", new_proto->chnl_id);
		वापस -EALREADY;
	पूर्ण

	/* can be from process context only */
	spin_lock_irqsave(&st_gdata->lock, flags);

	अगर (test_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state)) अणु
		pr_info(" ST_REG_IN_PROGRESS:%d ", new_proto->chnl_id);
		/* fw करोwnload in progress */

		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_रेजिस्टरed++;
		new_proto->ग_लिखो = st_ग_लिखो;

		set_bit(ST_REG_PENDING, &st_gdata->st_state);
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		वापस -EINPROGRESS;
	पूर्ण अन्यथा अगर (st_gdata->protos_रेजिस्टरed == ST_EMPTY) अणु
		pr_info(" chnl_id list empty :%d ", new_proto->chnl_id);
		set_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
		st_recv = st_kim_recv;

		/* enable the ST LL - to set शेष chip state */
		st_ll_enable(st_gdata);

		/* release lock previously held - re-locked below */
		spin_unlock_irqrestore(&st_gdata->lock, flags);

		/*
		 * this may take a जबतक to complete
		 * since it involves BT fw करोwnload
		 */
		err = st_kim_start(st_gdata->kim_data);
		अगर (err != 0) अणु
			clear_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
			अगर ((st_gdata->protos_रेजिस्टरed != ST_EMPTY) &&
			    (test_bit(ST_REG_PENDING, &st_gdata->st_state))) अणु
				pr_err(" KIM failure complete callback ");
				spin_lock_irqsave(&st_gdata->lock, flags);
				st_reg_complete(st_gdata, err);
				spin_unlock_irqrestore(&st_gdata->lock, flags);
				clear_bit(ST_REG_PENDING, &st_gdata->st_state);
			पूर्ण
			वापस -EINVAL;
		पूर्ण

		spin_lock_irqsave(&st_gdata->lock, flags);

		clear_bit(ST_REG_IN_PROGRESS, &st_gdata->st_state);
		st_recv = st_पूर्णांक_recv;

		/*
		 * this is where all pending registration
		 * are संकेतled to be complete by calling callback functions
		 */
		अगर ((st_gdata->protos_रेजिस्टरed != ST_EMPTY) &&
		    (test_bit(ST_REG_PENDING, &st_gdata->st_state))) अणु
			pr_debug(" call reg complete callback ");
			st_reg_complete(st_gdata, 0);
		पूर्ण
		clear_bit(ST_REG_PENDING, &st_gdata->st_state);

		/*
		 * check क्रम alपढ़ोy रेजिस्टरed once more,
		 * since the above check is old
		 */
		अगर (st_gdata->is_रेजिस्टरed[new_proto->chnl_id] == true) अणु
			pr_err(" proto %d already registered ",
				   new_proto->chnl_id);
			spin_unlock_irqrestore(&st_gdata->lock, flags);
			वापस -EALREADY;
		पूर्ण

		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_रेजिस्टरed++;
		new_proto->ग_लिखो = st_ग_लिखो;
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		वापस err;
	पूर्ण
	/* अगर fw is alपढ़ोy करोwnloaded & new stack रेजिस्टरs protocol */
	अन्यथा अणु
		add_channel_to_table(st_gdata, new_proto);
		st_gdata->protos_रेजिस्टरed++;
		new_proto->ग_लिखो = st_ग_लिखो;

		/* lock alपढ़ोy held beक्रमe entering अन्यथा */
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		वापस err;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(st_रेजिस्टर);

/*
 * to unरेजिस्टर a protocol -
 * to be called from protocol stack driver
 */
दीर्घ st_unरेजिस्टर(काष्ठा st_proto_s *proto)
अणु
	दीर्घ err = 0;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा st_data_s	*st_gdata;

	pr_debug("%s: %d ", __func__, proto->chnl_id);

	st_kim_ref(&st_gdata, 0);
	अगर (!st_gdata || proto->chnl_id >= ST_MAX_CHANNELS) अणु
		pr_err(" chnl_id %d not supported", proto->chnl_id);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	spin_lock_irqsave(&st_gdata->lock, flags);

	अगर (st_gdata->is_रेजिस्टरed[proto->chnl_id] == false) अणु
		pr_err(" chnl_id %d not registered", proto->chnl_id);
		spin_unlock_irqrestore(&st_gdata->lock, flags);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (st_gdata->protos_रेजिस्टरed)
		st_gdata->protos_रेजिस्टरed--;

	हटाओ_channel_from_table(st_gdata, proto);
	spin_unlock_irqrestore(&st_gdata->lock, flags);

	अगर ((st_gdata->protos_रेजिस्टरed == ST_EMPTY) &&
	    (!test_bit(ST_REG_PENDING, &st_gdata->st_state))) अणु
		pr_info(" all chnl_ids unregistered ");

		/* stop traffic on tty */
		अगर (st_gdata->tty) अणु
			tty_ldisc_flush(st_gdata->tty);
			stop_tty(st_gdata->tty);
		पूर्ण

		/* all chnl_ids now unरेजिस्टरed */
		st_kim_stop(st_gdata->kim_data);
		/* disable ST LL */
		st_ll_disable(st_gdata);
	पूर्ण
	वापस err;
पूर्ण

/*
 * called in protocol stack drivers
 * via the ग_लिखो function poपूर्णांकer
 */
दीर्घ st_ग_लिखो(काष्ठा sk_buff *skb)
अणु
	काष्ठा st_data_s *st_gdata;
	दीर्घ len;

	st_kim_ref(&st_gdata, 0);
	अगर (unlikely(skb == शून्य || st_gdata == शून्य
		|| st_gdata->tty == शून्य)) अणु
		pr_err("data/tty unavailable to perform write");
		वापस -EINVAL;
	पूर्ण

	pr_debug("%d to be written", skb->len);
	len = skb->len;

	/* st_ll to decide where to enqueue the skb */
	st_पूर्णांक_enqueue(st_gdata, skb);
	/* wake up */
	st_tx_wakeup(st_gdata);

	/* वापस number of bytes written */
	वापस len;
पूर्ण

/* क्रम protocols making use of shared transport */
EXPORT_SYMBOL_GPL(st_unरेजिस्टर);

/********************************************************************/
/*
 * functions called from TTY layer
 */
अटल पूर्णांक st_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा st_data_s *st_gdata;
	pr_info("%s ", __func__);

	st_kim_ref(&st_gdata, 0);
	st_gdata->tty = tty;
	tty->disc_data = st_gdata;

	/* करोn't करो an wakeup क्रम now */
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	/* mem alपढ़ोy allocated
	 */
	tty->receive_room = 65536;
	/* Flush any pending अक्षरacters in the driver and discipline. */
	tty_ldisc_flush(tty);
	tty_driver_flush_buffer(tty);
	/*
	 * संकेत to UIM via KIM that -
	 * installation of N_TI_WL ldisc is complete
	 */
	st_kim_complete(st_gdata->kim_data);
	pr_debug("done %s", __func__);

	वापस 0;
पूर्ण

अटल व्योम st_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित अक्षर i;
	अचिन्हित दीर्घ flags;
	काष्ठा	st_data_s *st_gdata = tty->disc_data;

	pr_info("%s ", __func__);

	/*
	 * TODO:
	 * अगर a protocol has been रेजिस्टरed & line discipline
	 * un-installed क्रम some reason - what should be करोne ?
	 */
	spin_lock_irqsave(&st_gdata->lock, flags);
	क्रम (i = ST_BT; i < ST_MAX_CHANNELS; i++) अणु
		अगर (st_gdata->is_रेजिस्टरed[i] == true)
			pr_err("%d not un-registered", i);
		st_gdata->list[i] = शून्य;
		st_gdata->is_रेजिस्टरed[i] = false;
	पूर्ण
	st_gdata->protos_रेजिस्टरed = 0;
	spin_unlock_irqrestore(&st_gdata->lock, flags);
	/*
	 * संकेत to UIM via KIM that -
	 * N_TI_WL ldisc is un-installed
	 */
	st_kim_complete(st_gdata->kim_data);
	st_gdata->tty = शून्य;
	/* Flush any pending अक्षरacters in the driver and discipline. */
	tty_ldisc_flush(tty);
	tty_driver_flush_buffer(tty);

	spin_lock_irqsave(&st_gdata->lock, flags);
	/* empty out txq and tx_रुकोq */
	skb_queue_purge(&st_gdata->txq);
	skb_queue_purge(&st_gdata->tx_रुकोq);
	/* reset the TTY Rx states of ST */
	st_gdata->rx_count = 0;
	st_gdata->rx_state = ST_W4_PACKET_TYPE;
	kमुक्त_skb(st_gdata->rx_skb);
	st_gdata->rx_skb = शून्य;
	spin_unlock_irqrestore(&st_gdata->lock, flags);

	pr_debug("%s: done ", __func__);
पूर्ण

अटल व्योम st_tty_receive(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *data,
			   अक्षर *tty_flags, पूर्णांक count)
अणु
#अगर_घोषित VERBOSE
	prपूर्णांक_hex_dump(KERN_DEBUG, ">in>", DUMP_PREFIX_NONE,
		16, 1, data, count, 0);
#पूर्ण_अगर

	/*
	 * अगर fw करोwnload is in progress then route incoming data
	 * to KIM क्रम validation
	 */
	st_recv(tty->disc_data, data, count);
	pr_debug("done %s", __func__);
पूर्ण

/*
 * wake-up function called in from the TTY layer
 * inside the पूर्णांकernal wakeup function will be called
 */
अटल व्योम st_tty_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा	st_data_s *st_gdata = tty->disc_data;
	pr_debug("%s ", __func__);
	/* करोn't करो an wakeup क्रम now */
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	/*
	 * schedule the पूर्णांकernal wakeup instead of calling directly to
	 * aव्योम lockup (port->lock needed in tty->ops->ग_लिखो is
	 * alपढ़ोy taken here
	 */
	schedule_work(&st_gdata->work_ग_लिखो_wakeup);
पूर्ण

अटल व्योम st_tty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा	st_data_s *st_gdata = tty->disc_data;
	pr_debug("%s ", __func__);

	kमुक्त_skb(st_gdata->tx_skb);
	st_gdata->tx_skb = शून्य;

	tty_driver_flush_buffer(tty);
	वापस;
पूर्ण

अटल काष्ठा tty_ldisc_ops st_ldisc_ops = अणु
	.name = "n_st",
	.खोलो = st_tty_खोलो,
	.बंद = st_tty_बंद,
	.receive_buf = st_tty_receive,
	.ग_लिखो_wakeup = st_tty_wakeup,
	.flush_buffer = st_tty_flush_buffer,
	.owner = THIS_MODULE
पूर्ण;

/********************************************************************/
पूर्णांक st_core_init(काष्ठा st_data_s **core_data)
अणु
	काष्ठा st_data_s *st_gdata;
	दीर्घ err;

	err = tty_रेजिस्टर_ldisc(N_TI_WL, &st_ldisc_ops);
	अगर (err) अणु
		pr_err("error registering %d line discipline %ld",
			   N_TI_WL, err);
		वापस err;
	पूर्ण
	pr_debug("registered n_shared line discipline");

	st_gdata = kzalloc(माप(काष्ठा st_data_s), GFP_KERNEL);
	अगर (!st_gdata) अणु
		pr_err("memory allocation failed");
		err = tty_unरेजिस्टर_ldisc(N_TI_WL);
		अगर (err)
			pr_err("unable to un-register ldisc %ld", err);
		err = -ENOMEM;
		वापस err;
	पूर्ण

	/* Initialize ST TxQ and Tx रुकोQ queue head. All BT/FM/GPS module skb's
	 * will be pushed in this queue क्रम actual transmission.
	 */
	skb_queue_head_init(&st_gdata->txq);
	skb_queue_head_init(&st_gdata->tx_रुकोq);

	/* Locking used in st_पूर्णांक_enqueue() to aव्योम multiple execution */
	spin_lock_init(&st_gdata->lock);

	err = st_ll_init(st_gdata);
	अगर (err) अणु
		pr_err("error during st_ll initialization(%ld)", err);
		kमुक्त(st_gdata);
		err = tty_unरेजिस्टर_ldisc(N_TI_WL);
		अगर (err)
			pr_err("unable to un-register ldisc");
		वापस err;
	पूर्ण

	INIT_WORK(&st_gdata->work_ग_लिखो_wakeup, work_fn_ग_लिखो_wakeup);

	*core_data = st_gdata;
	वापस 0;
पूर्ण

व्योम st_core_निकास(काष्ठा st_data_s *st_gdata)
अणु
	दीर्घ err;
	/* पूर्णांकernal module cleanup */
	err = st_ll_deinit(st_gdata);
	अगर (err)
		pr_err("error during deinit of ST LL %ld", err);

	अगर (st_gdata != शून्य) अणु
		/* Free ST Tx Qs and skbs */
		skb_queue_purge(&st_gdata->txq);
		skb_queue_purge(&st_gdata->tx_रुकोq);
		kमुक्त_skb(st_gdata->rx_skb);
		kमुक्त_skb(st_gdata->tx_skb);
		/* TTY ldisc cleanup */
		err = tty_unरेजिस्टर_ldisc(N_TI_WL);
		अगर (err)
			pr_err("unable to un-register ldisc %ld", err);
		/* मुक्त the global data poपूर्णांकer */
		kमुक्त(st_gdata);
	पूर्ण
पूर्ण
