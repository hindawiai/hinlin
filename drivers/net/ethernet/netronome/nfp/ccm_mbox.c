<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/पन.स>
#समावेश <linux/skbuff.h>

#समावेश "ccm.h"
#समावेश "nfp_net.h"

/* CCM messages via the mailbox.  CMSGs get wrapped पूर्णांकo simple TLVs
 * and copied पूर्णांकo the mailbox.  Multiple messages can be copied to
 * क्रमm a batch.  Thपढ़ोs come in with CMSG क्रमmed in an skb, then
 * enqueue that skb onto the request queue.  If thपढ़ोs skb is first
 * in queue this thपढ़ो will handle the mailbox operation.  It copies
 * up to 64 messages पूर्णांकo the mailbox (making sure that both requests
 * and replies will fit.  After FW is करोne processing the batch it
 * copies the data out and wakes रुकोing thपढ़ोs.
 * If a thपढ़ो is रुकोing it either माला_लो its the message completed
 * (response is copied पूर्णांकo the same skb as the request, overwriting
 * it), or becomes the first in queue.
 * Completions and next-to-run are संकेतed via the control buffer
 * to limit potential cache line bounces.
 */

#घोषणा NFP_CCM_MBOX_BATCH_LIMIT	64
#घोषणा NFP_CCM_TIMEOUT			(NFP_NET_POLL_TIMEOUT * 1000)
#घोषणा NFP_CCM_MAX_QLEN		1024

क्रमागत nfp_net_mbox_cmsg_state अणु
	NFP_NET_MBOX_CMSG_STATE_QUEUED,
	NFP_NET_MBOX_CMSG_STATE_NEXT,
	NFP_NET_MBOX_CMSG_STATE_BUSY,
	NFP_NET_MBOX_CMSG_STATE_REPLY_FOUND,
	NFP_NET_MBOX_CMSG_STATE_DONE,
पूर्ण;

/**
 * काष्ठा nfp_ccm_mbox_skb_cb - CCM mailbox specअगरic info
 * @state:	processing state (/stage) of the message
 * @err:	error encountered during processing अगर any
 * @max_len:	max(request_len, reply_len)
 * @exp_reply:	expected reply length (0 means करोn't validate)
 * @posted:	the message was posted and nobody रुकोs क्रम the reply
 */
काष्ठा nfp_ccm_mbox_cmsg_cb अणु
	क्रमागत nfp_net_mbox_cmsg_state state;
	पूर्णांक err;
	अचिन्हित पूर्णांक max_len;
	अचिन्हित पूर्णांक exp_reply;
	bool posted;
पूर्ण;

अटल u32 nfp_ccm_mbox_max_msg(काष्ठा nfp_net *nn)
अणु
	वापस round_करोwn(nn->tlv_caps.mbox_len, 4) -
		NFP_NET_CFG_MBOX_SIMPLE_VAL - /* common mbox command header */
		4 * 2; /* Msg TLV plus End TLV headers */
पूर्ण

अटल व्योम
nfp_ccm_mbox_msg_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक exp_reply, पूर्णांक max_len)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_QUEUED;
	cb->err = 0;
	cb->max_len = max_len;
	cb->exp_reply = exp_reply;
	cb->posted = false;
पूर्ण

अटल पूर्णांक nfp_ccm_mbox_maxlen(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	वापस cb->max_len;
पूर्ण

अटल bool nfp_ccm_mbox_करोne(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	वापस cb->state == NFP_NET_MBOX_CMSG_STATE_DONE;
पूर्ण

अटल bool nfp_ccm_mbox_in_progress(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	वापस cb->state != NFP_NET_MBOX_CMSG_STATE_QUEUED &&
	       cb->state != NFP_NET_MBOX_CMSG_STATE_NEXT;
पूर्ण

अटल व्योम nfp_ccm_mbox_set_busy(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	cb->state = NFP_NET_MBOX_CMSG_STATE_BUSY;
पूर्ण

अटल bool nfp_ccm_mbox_is_posted(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	वापस cb->posted;
पूर्ण

अटल व्योम nfp_ccm_mbox_mark_posted(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	cb->posted = true;
पूर्ण

अटल bool nfp_ccm_mbox_is_first(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb)
अणु
	वापस skb_queue_is_first(&nn->mbox_cmsg.queue, skb);
पूर्ण

अटल bool nfp_ccm_mbox_should_run(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	वापस cb->state == NFP_NET_MBOX_CMSG_STATE_NEXT;
पूर्ण

अटल व्योम nfp_ccm_mbox_mark_next_runner(काष्ठा nfp_net *nn)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb;
	काष्ठा sk_buff *skb;

	skb = skb_peek(&nn->mbox_cmsg.queue);
	अगर (!skb)
		वापस;

	cb = (व्योम *)skb->cb;
	cb->state = NFP_NET_MBOX_CMSG_STATE_NEXT;
	अगर (cb->posted)
		queue_work(nn->mbox_cmsg.workq, &nn->mbox_cmsg.runq_work);
पूर्ण

अटल व्योम
nfp_ccm_mbox_ग_लिखो_tlv(काष्ठा nfp_net *nn, u32 off, u32 type, u32 len)
अणु
	nn_ग_लिखोl(nn, off,
		  FIELD_PREP(NFP_NET_MBOX_TLV_TYPE, type) |
		  FIELD_PREP(NFP_NET_MBOX_TLV_LEN, len));
पूर्ण

अटल व्योम nfp_ccm_mbox_copy_in(काष्ठा nfp_net *nn, काष्ठा sk_buff *last)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक reserve, i, cnt;
	__be32 *data;
	u32 off, len;

	off = nn->tlv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPLE_VAL;
	skb = __skb_peek(&nn->mbox_cmsg.queue);
	जबतक (true) अणु
		nfp_ccm_mbox_ग_लिखो_tlv(nn, off, NFP_NET_MBOX_TLV_TYPE_MSG,
				       skb->len);
		off += 4;

		/* Write data word by word, skb->data should be aligned */
		data = (__be32 *)skb->data;
		cnt = skb->len / 4;
		क्रम (i = 0 ; i < cnt; i++) अणु
			nn_ग_लिखोl(nn, off, be32_to_cpu(data[i]));
			off += 4;
		पूर्ण
		अगर (skb->len & 3) अणु
			__be32 पंचांगp = 0;

			स_नकल(&पंचांगp, &data[i], skb->len & 3);
			nn_ग_लिखोl(nn, off, be32_to_cpu(पंचांगp));
			off += 4;
		पूर्ण

		/* Reserve space अगर reply is bigger */
		len = round_up(skb->len, 4);
		reserve = nfp_ccm_mbox_maxlen(skb) - len;
		अगर (reserve > 0) अणु
			nfp_ccm_mbox_ग_लिखो_tlv(nn, off,
					       NFP_NET_MBOX_TLV_TYPE_RESV,
					       reserve);
			off += 4 + reserve;
		पूर्ण

		अगर (skb == last)
			अवरोध;
		skb = skb_queue_next(&nn->mbox_cmsg.queue, skb);
	पूर्ण

	nfp_ccm_mbox_ग_लिखो_tlv(nn, off, NFP_NET_MBOX_TLV_TYPE_END, 0);
पूर्ण

अटल काष्ठा sk_buff *
nfp_ccm_mbox_find_req(काष्ठा nfp_net *nn, __be16 tag, काष्ठा sk_buff *last)
अणु
	काष्ठा sk_buff *skb;

	skb = __skb_peek(&nn->mbox_cmsg.queue);
	जबतक (true) अणु
		अगर (__nfp_ccm_get_tag(skb) == tag)
			वापस skb;

		अगर (skb == last)
			वापस शून्य;
		skb = skb_queue_next(&nn->mbox_cmsg.queue, skb);
	पूर्ण
पूर्ण

अटल व्योम nfp_ccm_mbox_copy_out(काष्ठा nfp_net *nn, काष्ठा sk_buff *last)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb;
	u8 __iomem *data, *end;
	काष्ठा sk_buff *skb;

	data = nn->dp.ctrl_bar + nn->tlv_caps.mbox_off +
		NFP_NET_CFG_MBOX_SIMPLE_VAL;
	end = data + nn->tlv_caps.mbox_len;

	जबतक (true) अणु
		अचिन्हित पूर्णांक length, offset, type;
		काष्ठा nfp_ccm_hdr hdr;
		u32 tlv_hdr;

		tlv_hdr = पढ़ोl(data);
		type = FIELD_GET(NFP_NET_MBOX_TLV_TYPE, tlv_hdr);
		length = FIELD_GET(NFP_NET_MBOX_TLV_LEN, tlv_hdr);
		offset = data - nn->dp.ctrl_bar;

		/* Advance past the header */
		data += 4;

		अगर (data + length > end) अणु
			nn_dp_warn(&nn->dp, "mailbox oversized TLV type:%d offset:%u len:%u\n",
				   type, offset, length);
			अवरोध;
		पूर्ण

		अगर (type == NFP_NET_MBOX_TLV_TYPE_END)
			अवरोध;
		अगर (type == NFP_NET_MBOX_TLV_TYPE_RESV)
			जाओ next_tlv;
		अगर (type != NFP_NET_MBOX_TLV_TYPE_MSG &&
		    type != NFP_NET_MBOX_TLV_TYPE_MSG_NOSUP) अणु
			nn_dp_warn(&nn->dp, "mailbox unknown TLV type:%d offset:%u len:%u\n",
				   type, offset, length);
			अवरोध;
		पूर्ण

		अगर (length < 4) अणु
			nn_dp_warn(&nn->dp, "mailbox msg too short to contain header TLV type:%d offset:%u len:%u\n",
				   type, offset, length);
			अवरोध;
		पूर्ण

		hdr.raw = cpu_to_be32(पढ़ोl(data));

		skb = nfp_ccm_mbox_find_req(nn, hdr.tag, last);
		अगर (!skb) अणु
			nn_dp_warn(&nn->dp, "mailbox request not found:%u\n",
				   be16_to_cpu(hdr.tag));
			अवरोध;
		पूर्ण
		cb = (व्योम *)skb->cb;

		अगर (type == NFP_NET_MBOX_TLV_TYPE_MSG_NOSUP) अणु
			nn_dp_warn(&nn->dp,
				   "mailbox msg not supported type:%d\n",
				   nfp_ccm_get_type(skb));
			cb->err = -EIO;
			जाओ next_tlv;
		पूर्ण

		अगर (hdr.type != __NFP_CCM_REPLY(nfp_ccm_get_type(skb))) अणु
			nn_dp_warn(&nn->dp, "mailbox msg reply wrong type:%u expected:%lu\n",
				   hdr.type,
				   __NFP_CCM_REPLY(nfp_ccm_get_type(skb)));
			cb->err = -EIO;
			जाओ next_tlv;
		पूर्ण
		अगर (cb->exp_reply && length != cb->exp_reply) अणु
			nn_dp_warn(&nn->dp, "mailbox msg reply wrong size type:%u expected:%u have:%u\n",
				   hdr.type, length, cb->exp_reply);
			cb->err = -EIO;
			जाओ next_tlv;
		पूर्ण
		अगर (length > cb->max_len) अणु
			nn_dp_warn(&nn->dp, "mailbox msg oversized reply type:%u max:%u have:%u\n",
				   hdr.type, cb->max_len, length);
			cb->err = -EIO;
			जाओ next_tlv;
		पूर्ण

		अगर (!cb->posted) अणु
			__be32 *skb_data;
			पूर्णांक i, cnt;

			अगर (length <= skb->len)
				__skb_trim(skb, length);
			अन्यथा
				skb_put(skb, length - skb->len);

			/* We overcopy here slightly, but that's okay,
			 * the skb is large enough, and the garbage will
			 * be ignored (beyond skb->len).
			 */
			skb_data = (__be32 *)skb->data;
			स_नकल(skb_data, &hdr, 4);

			cnt = DIV_ROUND_UP(length, 4);
			क्रम (i = 1 ; i < cnt; i++)
				skb_data[i] = cpu_to_be32(पढ़ोl(data + i * 4));
		पूर्ण

		cb->state = NFP_NET_MBOX_CMSG_STATE_REPLY_FOUND;
next_tlv:
		data += round_up(length, 4);
		अगर (data + 4 > end) अणु
			nn_dp_warn(&nn->dp,
				   "reached end of MBOX without END TLV\n");
			अवरोध;
		पूर्ण
	पूर्ण

	smp_wmb(); /* order the skb->data vs. cb->state */
	spin_lock_bh(&nn->mbox_cmsg.queue.lock);
	करो अणु
		skb = __skb_dequeue(&nn->mbox_cmsg.queue);
		cb = (व्योम *)skb->cb;

		अगर (cb->state != NFP_NET_MBOX_CMSG_STATE_REPLY_FOUND) अणु
			cb->err = -ENOENT;
			smp_wmb(); /* order the cb->err vs. cb->state */
		पूर्ण
		cb->state = NFP_NET_MBOX_CMSG_STATE_DONE;

		अगर (cb->posted) अणु
			अगर (cb->err)
				nn_dp_warn(&nn->dp,
					   "mailbox posted msg failed type:%u err:%d\n",
					   nfp_ccm_get_type(skb), cb->err);
			dev_consume_skb_any(skb);
		पूर्ण
	पूर्ण जबतक (skb != last);

	nfp_ccm_mbox_mark_next_runner(nn);
	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);
पूर्ण

अटल व्योम
nfp_ccm_mbox_mark_all_err(काष्ठा nfp_net *nn, काष्ठा sk_buff *last, पूर्णांक err)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb;
	काष्ठा sk_buff *skb;

	spin_lock_bh(&nn->mbox_cmsg.queue.lock);
	करो अणु
		skb = __skb_dequeue(&nn->mbox_cmsg.queue);
		cb = (व्योम *)skb->cb;

		cb->err = err;
		smp_wmb(); /* order the cb->err vs. cb->state */
		cb->state = NFP_NET_MBOX_CMSG_STATE_DONE;
	पूर्ण जबतक (skb != last);

	nfp_ccm_mbox_mark_next_runner(nn);
	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);
पूर्ण

अटल व्योम nfp_ccm_mbox_run_queue_unlock(काष्ठा nfp_net *nn)
	__releases(&nn->mbox_cmsg.queue.lock)
अणु
	पूर्णांक space = nn->tlv_caps.mbox_len - NFP_NET_CFG_MBOX_SIMPLE_VAL;
	काष्ठा sk_buff *skb, *last;
	पूर्णांक cnt, err;

	space -= 4; /* क्रम End TLV */

	/* First skb must fit, because it's ours and we checked it fits */
	cnt = 1;
	last = skb = __skb_peek(&nn->mbox_cmsg.queue);
	space -= 4 + nfp_ccm_mbox_maxlen(skb);

	जबतक (!skb_queue_is_last(&nn->mbox_cmsg.queue, last)) अणु
		skb = skb_queue_next(&nn->mbox_cmsg.queue, last);
		space -= 4 + nfp_ccm_mbox_maxlen(skb);
		अगर (space < 0)
			अवरोध;
		last = skb;
		nfp_ccm_mbox_set_busy(skb);
		cnt++;
		अगर (cnt == NFP_CCM_MBOX_BATCH_LIMIT)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);

	/* Now we own all skb's marked in progress, new requests may arrive
	 * at the end of the queue.
	 */

	nn_ctrl_bar_lock(nn);

	nfp_ccm_mbox_copy_in(nn, last);

	err = nfp_net_mbox_reconfig(nn, NFP_NET_CFG_MBOX_CMD_TLV_CMSG);
	अगर (!err)
		nfp_ccm_mbox_copy_out(nn, last);
	अन्यथा
		nfp_ccm_mbox_mark_all_err(nn, last, -EIO);

	nn_ctrl_bar_unlock(nn);

	wake_up_all(&nn->mbox_cmsg.wq);
पूर्ण

अटल पूर्णांक nfp_ccm_mbox_skb_वापस(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_mbox_cmsg_cb *cb = (व्योम *)skb->cb;

	अगर (cb->err)
		dev_kमुक्त_skb_any(skb);
	वापस cb->err;
पूर्ण

/* If रुको समयd out but the command is alपढ़ोy in progress we have
 * to रुको until it finishes.  Runners has ownership of the skbs marked
 * as busy.
 */
अटल पूर्णांक
nfp_ccm_mbox_unlink_unlock(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			   क्रमागत nfp_ccm_type type)
	__releases(&nn->mbox_cmsg.queue.lock)
अणु
	bool was_first;

	अगर (nfp_ccm_mbox_in_progress(skb)) अणु
		spin_unlock_bh(&nn->mbox_cmsg.queue.lock);

		रुको_event(nn->mbox_cmsg.wq, nfp_ccm_mbox_करोne(skb));
		smp_rmb(); /* pairs with smp_wmb() after data is written */
		वापस nfp_ccm_mbox_skb_वापस(skb);
	पूर्ण

	was_first = nfp_ccm_mbox_should_run(nn, skb);
	__skb_unlink(skb, &nn->mbox_cmsg.queue);
	अगर (was_first)
		nfp_ccm_mbox_mark_next_runner(nn);

	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);

	अगर (was_first)
		wake_up_all(&nn->mbox_cmsg.wq);

	nn_dp_warn(&nn->dp, "time out waiting for mbox response to 0x%02x\n",
		   type);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक
nfp_ccm_mbox_msg_prepare(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			 क्रमागत nfp_ccm_type type,
			 अचिन्हित पूर्णांक reply_size, अचिन्हित पूर्णांक max_reply_size,
			 gfp_t flags)
अणु
	स्थिर अचिन्हित पूर्णांक mbox_max = nfp_ccm_mbox_max_msg(nn);
	अचिन्हित पूर्णांक max_len;
	sमाप_प्रकार undersize;
	पूर्णांक err;

	अगर (unlikely(!(nn->tlv_caps.mbox_cmsg_types & BIT(type)))) अणु
		nn_dp_warn(&nn->dp,
			   "message type %d not supported by mailbox\n", type);
		वापस -EINVAL;
	पूर्ण

	/* If the reply size is unknown assume it will take the entire
	 * mailbox, the callers should करो their best क्रम this to never
	 * happen.
	 */
	अगर (!max_reply_size)
		max_reply_size = mbox_max;
	max_reply_size = round_up(max_reply_size, 4);

	/* Make sure we can fit the entire reply पूर्णांकo the skb,
	 * and that we करोn't have to slow करोwn the mbox handler
	 * with allocations.
	 */
	undersize = max_reply_size - (skb_end_poपूर्णांकer(skb) - skb->data);
	अगर (undersize > 0) अणु
		err = pskb_expand_head(skb, 0, undersize, flags);
		अगर (err) अणु
			nn_dp_warn(&nn->dp,
				   "can't allocate reply buffer for mailbox\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* Make sure that request and response both fit पूर्णांकo the mailbox */
	max_len = max(max_reply_size, round_up(skb->len, 4));
	अगर (max_len > mbox_max) अणु
		nn_dp_warn(&nn->dp,
			   "message too big for tha mailbox: %u/%u vs %u\n",
			   skb->len, max_reply_size, mbox_max);
		वापस -EMSGSIZE;
	पूर्ण

	nfp_ccm_mbox_msg_init(skb, reply_size, max_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_ccm_mbox_msg_enqueue(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			 क्रमागत nfp_ccm_type type, bool critical)
अणु
	काष्ठा nfp_ccm_hdr *hdr;

	निश्चित_spin_locked(&nn->mbox_cmsg.queue.lock);

	अगर (!critical && nn->mbox_cmsg.queue.qlen >= NFP_CCM_MAX_QLEN) अणु
		nn_dp_warn(&nn->dp, "mailbox request queue too long\n");
		वापस -EBUSY;
	पूर्ण

	hdr = (व्योम *)skb->data;
	hdr->ver = NFP_CCM_ABI_VERSION;
	hdr->type = type;
	hdr->tag = cpu_to_be16(nn->mbox_cmsg.tag++);

	__skb_queue_tail(&nn->mbox_cmsg.queue, skb);

	वापस 0;
पूर्ण

पूर्णांक __nfp_ccm_mbox_communicate(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			       क्रमागत nfp_ccm_type type,
			       अचिन्हित पूर्णांक reply_size,
			       अचिन्हित पूर्णांक max_reply_size, bool critical)
अणु
	पूर्णांक err;

	err = nfp_ccm_mbox_msg_prepare(nn, skb, type, reply_size,
				       max_reply_size, GFP_KERNEL);
	अगर (err)
		जाओ err_मुक्त_skb;

	spin_lock_bh(&nn->mbox_cmsg.queue.lock);

	err = nfp_ccm_mbox_msg_enqueue(nn, skb, type, critical);
	अगर (err)
		जाओ err_unlock;

	/* First in queue takes the mailbox lock and processes the batch */
	अगर (!nfp_ccm_mbox_is_first(nn, skb)) अणु
		bool to;

		spin_unlock_bh(&nn->mbox_cmsg.queue.lock);

		to = !रुको_event_समयout(nn->mbox_cmsg.wq,
					 nfp_ccm_mbox_करोne(skb) ||
					 nfp_ccm_mbox_should_run(nn, skb),
					 msecs_to_jअगरfies(NFP_CCM_TIMEOUT));

		/* fast path क्रम those completed by another thपढ़ो */
		अगर (nfp_ccm_mbox_करोne(skb)) अणु
			smp_rmb(); /* pairs with wmb after data is written */
			वापस nfp_ccm_mbox_skb_वापस(skb);
		पूर्ण

		spin_lock_bh(&nn->mbox_cmsg.queue.lock);

		अगर (!nfp_ccm_mbox_is_first(nn, skb)) अणु
			WARN_ON(!to);

			err = nfp_ccm_mbox_unlink_unlock(nn, skb, type);
			अगर (err)
				जाओ err_मुक्त_skb;
			वापस 0;
		पूर्ण
	पूर्ण

	/* run queue expects the lock held */
	nfp_ccm_mbox_run_queue_unlock(nn);
	वापस nfp_ccm_mbox_skb_वापस(skb);

err_unlock:
	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);
err_मुक्त_skb:
	dev_kमुक्त_skb_any(skb);
	वापस err;
पूर्ण

पूर्णांक nfp_ccm_mbox_communicate(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			     क्रमागत nfp_ccm_type type,
			     अचिन्हित पूर्णांक reply_size,
			     अचिन्हित पूर्णांक max_reply_size)
अणु
	वापस __nfp_ccm_mbox_communicate(nn, skb, type, reply_size,
					  max_reply_size, false);
पूर्ण

अटल व्योम nfp_ccm_mbox_post_runq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfp_net *nn;

	nn = container_of(work, काष्ठा nfp_net, mbox_cmsg.runq_work);

	spin_lock_bh(&nn->mbox_cmsg.queue.lock);

	skb = __skb_peek(&nn->mbox_cmsg.queue);
	अगर (WARN_ON(!skb || !nfp_ccm_mbox_is_posted(skb) ||
		    !nfp_ccm_mbox_should_run(nn, skb))) अणु
		spin_unlock_bh(&nn->mbox_cmsg.queue.lock);
		वापस;
	पूर्ण

	nfp_ccm_mbox_run_queue_unlock(nn);
पूर्ण

अटल व्योम nfp_ccm_mbox_post_रुको_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nfp_net *nn;
	पूर्णांक err;

	nn = container_of(work, काष्ठा nfp_net, mbox_cmsg.रुको_work);

	skb = skb_peek(&nn->mbox_cmsg.queue);
	अगर (WARN_ON(!skb || !nfp_ccm_mbox_is_posted(skb)))
		/* Should never happen so it's unclear what to करो here.. */
		जाओ निकास_unlock_wake;

	err = nfp_net_mbox_reconfig_रुको_posted(nn);
	अगर (!err)
		nfp_ccm_mbox_copy_out(nn, skb);
	अन्यथा
		nfp_ccm_mbox_mark_all_err(nn, skb, -EIO);
निकास_unlock_wake:
	nn_ctrl_bar_unlock(nn);
	wake_up_all(&nn->mbox_cmsg.wq);
पूर्ण

पूर्णांक nfp_ccm_mbox_post(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
		      क्रमागत nfp_ccm_type type, अचिन्हित पूर्णांक max_reply_size)
अणु
	पूर्णांक err;

	err = nfp_ccm_mbox_msg_prepare(nn, skb, type, 0, max_reply_size,
				       GFP_ATOMIC);
	अगर (err)
		जाओ err_मुक्त_skb;

	nfp_ccm_mbox_mark_posted(skb);

	spin_lock_bh(&nn->mbox_cmsg.queue.lock);

	err = nfp_ccm_mbox_msg_enqueue(nn, skb, type, false);
	अगर (err)
		जाओ err_unlock;

	अगर (nfp_ccm_mbox_is_first(nn, skb)) अणु
		अगर (nn_ctrl_bar_trylock(nn)) अणु
			nfp_ccm_mbox_copy_in(nn, skb);
			nfp_net_mbox_reconfig_post(nn,
						   NFP_NET_CFG_MBOX_CMD_TLV_CMSG);
			queue_work(nn->mbox_cmsg.workq,
				   &nn->mbox_cmsg.रुको_work);
		पूर्ण अन्यथा अणु
			nfp_ccm_mbox_mark_next_runner(nn);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);

	वापस 0;

err_unlock:
	spin_unlock_bh(&nn->mbox_cmsg.queue.lock);
err_मुक्त_skb:
	dev_kमुक्त_skb_any(skb);
	वापस err;
पूर्ण

काष्ठा sk_buff *
nfp_ccm_mbox_msg_alloc(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक req_size,
		       अचिन्हित पूर्णांक reply_size, gfp_t flags)
अणु
	अचिन्हित पूर्णांक max_size;
	काष्ठा sk_buff *skb;

	अगर (!reply_size)
		max_size = nfp_ccm_mbox_max_msg(nn);
	अन्यथा
		max_size = max(req_size, reply_size);
	max_size = round_up(max_size, 4);

	skb = alloc_skb(max_size, flags);
	अगर (!skb)
		वापस शून्य;

	skb_put(skb, req_size);

	वापस skb;
पूर्ण

bool nfp_ccm_mbox_fits(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक size)
अणु
	वापस nfp_ccm_mbox_max_msg(nn) >= size;
पूर्ण

पूर्णांक nfp_ccm_mbox_init(काष्ठा nfp_net *nn)
अणु
	वापस 0;
पूर्ण

व्योम nfp_ccm_mbox_clean(काष्ठा nfp_net *nn)
अणु
	drain_workqueue(nn->mbox_cmsg.workq);
पूर्ण

पूर्णांक nfp_ccm_mbox_alloc(काष्ठा nfp_net *nn)
अणु
	skb_queue_head_init(&nn->mbox_cmsg.queue);
	init_रुकोqueue_head(&nn->mbox_cmsg.wq);
	INIT_WORK(&nn->mbox_cmsg.रुको_work, nfp_ccm_mbox_post_रुको_work);
	INIT_WORK(&nn->mbox_cmsg.runq_work, nfp_ccm_mbox_post_runq_work);

	nn->mbox_cmsg.workq = alloc_workqueue("nfp-ccm-mbox", WQ_UNBOUND, 0);
	अगर (!nn->mbox_cmsg.workq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम nfp_ccm_mbox_मुक्त(काष्ठा nfp_net *nn)
अणु
	destroy_workqueue(nn->mbox_cmsg.workq);
	WARN_ON(!skb_queue_empty(&nn->mbox_cmsg.queue));
पूर्ण
