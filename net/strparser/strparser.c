<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stream Parser
 *
 * Copyright (c) 2016 Tom Herbert <tom@herbertland.com>
 */

#समावेश <linux/bpf.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/errqueue.h>
#समावेश <linux/file.h>
#समावेश <linux/in.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/poll.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/workqueue.h>
#समावेश <net/strparser.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>

अटल काष्ठा workqueue_काष्ठा *strp_wq;

काष्ठा _strp_msg अणु
	/* Internal cb काष्ठाure. काष्ठा strp_msg must be first क्रम passing
	 * to upper layer.
	 */
	काष्ठा strp_msg strp;
	पूर्णांक accum_len;
पूर्ण;

अटल अंतरभूत काष्ठा _strp_msg *_strp_msg(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा _strp_msg *)((व्योम *)skb->cb +
		दुरत्व(काष्ठा qdisc_skb_cb, data));
पूर्ण

/* Lower lock held */
अटल व्योम strp_पात_strp(काष्ठा strparser *strp, पूर्णांक err)
अणु
	/* Unrecoverable error in receive */

	cancel_delayed_work(&strp->msg_समयr_work);

	अगर (strp->stopped)
		वापस;

	strp->stopped = 1;

	अगर (strp->sk) अणु
		काष्ठा sock *sk = strp->sk;

		/* Report an error on the lower socket */
		sk->sk_err = -err;
		sk->sk_error_report(sk);
	पूर्ण
पूर्ण

अटल व्योम strp_start_समयr(काष्ठा strparser *strp, दीर्घ समयo)
अणु
	अगर (समयo && समयo != दीर्घ_उच्च)
		mod_delayed_work(strp_wq, &strp->msg_समयr_work, समयo);
पूर्ण

/* Lower lock held */
अटल व्योम strp_parser_err(काष्ठा strparser *strp, पूर्णांक err,
			    पढ़ो_descriptor_t *desc)
अणु
	desc->error = err;
	kमुक्त_skb(strp->skb_head);
	strp->skb_head = शून्य;
	strp->cb.पात_parser(strp, err);
पूर्ण

अटल अंतरभूत पूर्णांक strp_peek_len(काष्ठा strparser *strp)
अणु
	अगर (strp->sk) अणु
		काष्ठा socket *sock = strp->sk->sk_socket;

		वापस sock->ops->peek_len(sock);
	पूर्ण

	/* If we करोn't have an associated socket there's nothing to peek.
	 * Return पूर्णांक max to aव्योम stopping the strparser.
	 */

	वापस पूर्णांक_उच्च;
पूर्ण

/* Lower socket lock held */
अटल पूर्णांक __strp_recv(पढ़ो_descriptor_t *desc, काष्ठा sk_buff *orig_skb,
		       अचिन्हित पूर्णांक orig_offset, माप_प्रकार orig_len,
		       माप_प्रकार max_msg_size, दीर्घ समयo)
अणु
	काष्ठा strparser *strp = (काष्ठा strparser *)desc->arg.data;
	काष्ठा _strp_msg *sपंचांग;
	काष्ठा sk_buff *head, *skb;
	माप_प्रकार eaten = 0, cand_len;
	sमाप_प्रकार extra;
	पूर्णांक err;
	bool cloned_orig = false;

	अगर (strp->छोड़ोd)
		वापस 0;

	head = strp->skb_head;
	अगर (head) अणु
		/* Message alपढ़ोy in progress */
		अगर (unlikely(orig_offset)) अणु
			/* Getting data with a non-zero offset when a message is
			 * in progress is not expected. If it करोes happen, we
			 * need to clone and pull since we can't deal with
			 * offsets in the skbs क्रम a message expect in the head.
			 */
			orig_skb = skb_clone(orig_skb, GFP_ATOMIC);
			अगर (!orig_skb) अणु
				STRP_STATS_INCR(strp->stats.mem_fail);
				desc->error = -ENOMEM;
				वापस 0;
			पूर्ण
			अगर (!pskb_pull(orig_skb, orig_offset)) अणु
				STRP_STATS_INCR(strp->stats.mem_fail);
				kमुक्त_skb(orig_skb);
				desc->error = -ENOMEM;
				वापस 0;
			पूर्ण
			cloned_orig = true;
			orig_offset = 0;
		पूर्ण

		अगर (!strp->skb_nextp) अणु
			/* We are going to append to the frags_list of head.
			 * Need to unshare the frag_list.
			 */
			err = skb_unclone(head, GFP_ATOMIC);
			अगर (err) अणु
				STRP_STATS_INCR(strp->stats.mem_fail);
				desc->error = err;
				वापस 0;
			पूर्ण

			अगर (unlikely(skb_shinfo(head)->frag_list)) अणु
				/* We can't append to an sk_buff that alपढ़ोy
				 * has a frag_list. We create a new head, poपूर्णांक
				 * the frag_list of that to the old head, and
				 * then are able to use the old head->next क्रम
				 * appending to the message.
				 */
				अगर (WARN_ON(head->next)) अणु
					desc->error = -EINVAL;
					वापस 0;
				पूर्ण

				skb = alloc_skb_क्रम_msg(head);
				अगर (!skb) अणु
					STRP_STATS_INCR(strp->stats.mem_fail);
					desc->error = -ENOMEM;
					वापस 0;
				पूर्ण

				strp->skb_nextp = &head->next;
				strp->skb_head = skb;
				head = skb;
			पूर्ण अन्यथा अणु
				strp->skb_nextp =
				    &skb_shinfo(head)->frag_list;
			पूर्ण
		पूर्ण
	पूर्ण

	जबतक (eaten < orig_len) अणु
		/* Always clone since we will consume something */
		skb = skb_clone(orig_skb, GFP_ATOMIC);
		अगर (!skb) अणु
			STRP_STATS_INCR(strp->stats.mem_fail);
			desc->error = -ENOMEM;
			अवरोध;
		पूर्ण

		cand_len = orig_len - eaten;

		head = strp->skb_head;
		अगर (!head) अणु
			head = skb;
			strp->skb_head = head;
			/* Will set skb_nextp on next packet अगर needed */
			strp->skb_nextp = शून्य;
			sपंचांग = _strp_msg(head);
			स_रखो(sपंचांग, 0, माप(*sपंचांग));
			sपंचांग->strp.offset = orig_offset + eaten;
		पूर्ण अन्यथा अणु
			/* Unclone अगर we are appending to an skb that we
			 * alपढ़ोy share a frag_list with.
			 */
			अगर (skb_has_frag_list(skb)) अणु
				err = skb_unclone(skb, GFP_ATOMIC);
				अगर (err) अणु
					STRP_STATS_INCR(strp->stats.mem_fail);
					desc->error = err;
					अवरोध;
				पूर्ण
			पूर्ण

			sपंचांग = _strp_msg(head);
			*strp->skb_nextp = skb;
			strp->skb_nextp = &skb->next;
			head->data_len += skb->len;
			head->len += skb->len;
			head->truesize += skb->truesize;
		पूर्ण

		अगर (!sपंचांग->strp.full_len) अणु
			sमाप_प्रकार len;

			len = (*strp->cb.parse_msg)(strp, head);

			अगर (!len) अणु
				/* Need more header to determine length */
				अगर (!sपंचांग->accum_len) अणु
					/* Start RX समयr क्रम new message */
					strp_start_समयr(strp, समयo);
				पूर्ण
				sपंचांग->accum_len += cand_len;
				eaten += cand_len;
				STRP_STATS_INCR(strp->stats.need_more_hdr);
				WARN_ON(eaten != orig_len);
				अवरोध;
			पूर्ण अन्यथा अगर (len < 0) अणु
				अगर (len == -ESTRPIPE && sपंचांग->accum_len) अणु
					len = -ENODATA;
					strp->unrecov_पूर्णांकr = 1;
				पूर्ण अन्यथा अणु
					strp->पूर्णांकerrupted = 1;
				पूर्ण
				strp_parser_err(strp, len, desc);
				अवरोध;
			पूर्ण अन्यथा अगर (len > max_msg_size) अणु
				/* Message length exceeds maximum allowed */
				STRP_STATS_INCR(strp->stats.msg_too_big);
				strp_parser_err(strp, -EMSGSIZE, desc);
				अवरोध;
			पूर्ण अन्यथा अगर (len <= (sमाप_प्रकार)head->len -
					  skb->len - sपंचांग->strp.offset) अणु
				/* Length must be पूर्णांकo new skb (and also
				 * greater than zero)
				 */
				STRP_STATS_INCR(strp->stats.bad_hdr_len);
				strp_parser_err(strp, -EPROTO, desc);
				अवरोध;
			पूर्ण

			sपंचांग->strp.full_len = len;
		पूर्ण

		extra = (sमाप_प्रकार)(sपंचांग->accum_len + cand_len) -
			sपंचांग->strp.full_len;

		अगर (extra < 0) अणु
			/* Message not complete yet. */
			अगर (sपंचांग->strp.full_len - sपंचांग->accum_len >
			    strp_peek_len(strp)) अणु
				/* Don't have the whole message in the socket
				 * buffer. Set strp->need_bytes to रुको क्रम
				 * the rest of the message. Also, set "early
				 * eaten" since we've alपढ़ोy buffered the skb
				 * but करोn't consume yet per strp_पढ़ो_sock.
				 */

				अगर (!sपंचांग->accum_len) अणु
					/* Start RX समयr क्रम new message */
					strp_start_समयr(strp, समयo);
				पूर्ण

				sपंचांग->accum_len += cand_len;
				eaten += cand_len;
				strp->need_bytes = sपंचांग->strp.full_len -
						       sपंचांग->accum_len;
				STRP_STATS_ADD(strp->stats.bytes, cand_len);
				desc->count = 0; /* Stop पढ़ोing socket */
				अवरोध;
			पूर्ण
			sपंचांग->accum_len += cand_len;
			eaten += cand_len;
			WARN_ON(eaten != orig_len);
			अवरोध;
		पूर्ण

		/* Positive extra indicates more bytes than needed क्रम the
		 * message
		 */

		WARN_ON(extra > cand_len);

		eaten += (cand_len - extra);

		/* Hurray, we have a new message! */
		cancel_delayed_work(&strp->msg_समयr_work);
		strp->skb_head = शून्य;
		strp->need_bytes = 0;
		STRP_STATS_INCR(strp->stats.msgs);

		/* Give skb to upper layer */
		strp->cb.rcv_msg(strp, head);

		अगर (unlikely(strp->छोड़ोd)) अणु
			/* Upper layer छोड़ोd strp */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cloned_orig)
		kमुक्त_skb(orig_skb);

	STRP_STATS_ADD(strp->stats.bytes, eaten);

	वापस eaten;
पूर्ण

पूर्णांक strp_process(काष्ठा strparser *strp, काष्ठा sk_buff *orig_skb,
		 अचिन्हित पूर्णांक orig_offset, माप_प्रकार orig_len,
		 माप_प्रकार max_msg_size, दीर्घ समयo)
अणु
	पढ़ो_descriptor_t desc; /* Dummy arg to strp_recv */

	desc.arg.data = strp;

	वापस __strp_recv(&desc, orig_skb, orig_offset, orig_len,
			   max_msg_size, समयo);
पूर्ण
EXPORT_SYMBOL_GPL(strp_process);

अटल पूर्णांक strp_recv(पढ़ो_descriptor_t *desc, काष्ठा sk_buff *orig_skb,
		     अचिन्हित पूर्णांक orig_offset, माप_प्रकार orig_len)
अणु
	काष्ठा strparser *strp = (काष्ठा strparser *)desc->arg.data;

	वापस __strp_recv(desc, orig_skb, orig_offset, orig_len,
			   strp->sk->sk_rcvbuf, strp->sk->sk_rcvसमयo);
पूर्ण

अटल पूर्णांक शेष_पढ़ो_sock_करोne(काष्ठा strparser *strp, पूर्णांक err)
अणु
	वापस err;
पूर्ण

/* Called with lock held on lower socket */
अटल पूर्णांक strp_पढ़ो_sock(काष्ठा strparser *strp)
अणु
	काष्ठा socket *sock = strp->sk->sk_socket;
	पढ़ो_descriptor_t desc;

	अगर (unlikely(!sock || !sock->ops || !sock->ops->पढ़ो_sock))
		वापस -EBUSY;

	desc.arg.data = strp;
	desc.error = 0;
	desc.count = 1; /* give more than one skb per call */

	/* sk should be locked here, so okay to करो पढ़ो_sock */
	sock->ops->पढ़ो_sock(strp->sk, &desc, strp_recv);

	desc.error = strp->cb.पढ़ो_sock_करोne(strp, desc.error);

	वापस desc.error;
पूर्ण

/* Lower sock lock held */
व्योम strp_data_पढ़ोy(काष्ठा strparser *strp)
अणु
	अगर (unlikely(strp->stopped) || strp->छोड़ोd)
		वापस;

	/* This check is needed to synchronize with करो_strp_work.
	 * करो_strp_work acquires a process lock (lock_sock) whereas
	 * the lock held here is bh_lock_sock. The two locks can be
	 * held by dअगरferent thपढ़ोs at the same समय, but bh_lock_sock
	 * allows a thपढ़ो in BH context to safely check अगर the process
	 * lock is held. In this हाल, अगर the lock is held, queue work.
	 */
	अगर (sock_owned_by_user_nocheck(strp->sk)) अणु
		queue_work(strp_wq, &strp->work);
		वापस;
	पूर्ण

	अगर (strp->need_bytes) अणु
		अगर (strp_peek_len(strp) < strp->need_bytes)
			वापस;
	पूर्ण

	अगर (strp_पढ़ो_sock(strp) == -ENOMEM)
		queue_work(strp_wq, &strp->work);
पूर्ण
EXPORT_SYMBOL_GPL(strp_data_पढ़ोy);

अटल व्योम करो_strp_work(काष्ठा strparser *strp)
अणु
	/* We need the पढ़ो lock to synchronize with strp_data_पढ़ोy. We
	 * need the socket lock क्रम calling strp_पढ़ो_sock.
	 */
	strp->cb.lock(strp);

	अगर (unlikely(strp->stopped))
		जाओ out;

	अगर (strp->छोड़ोd)
		जाओ out;

	अगर (strp_पढ़ो_sock(strp) == -ENOMEM)
		queue_work(strp_wq, &strp->work);

out:
	strp->cb.unlock(strp);
पूर्ण

अटल व्योम strp_work(काष्ठा work_काष्ठा *w)
अणु
	करो_strp_work(container_of(w, काष्ठा strparser, work));
पूर्ण

अटल व्योम strp_msg_समयout(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा strparser *strp = container_of(w, काष्ठा strparser,
					      msg_समयr_work.work);

	/* Message assembly समयd out */
	STRP_STATS_INCR(strp->stats.msg_समयouts);
	strp->cb.lock(strp);
	strp->cb.पात_parser(strp, -ETIMEDOUT);
	strp->cb.unlock(strp);
पूर्ण

अटल व्योम strp_sock_lock(काष्ठा strparser *strp)
अणु
	lock_sock(strp->sk);
पूर्ण

अटल व्योम strp_sock_unlock(काष्ठा strparser *strp)
अणु
	release_sock(strp->sk);
पूर्ण

पूर्णांक strp_init(काष्ठा strparser *strp, काष्ठा sock *sk,
	      स्थिर काष्ठा strp_callbacks *cb)
अणु

	अगर (!cb || !cb->rcv_msg || !cb->parse_msg)
		वापस -EINVAL;

	/* The sk (sock) arg determines the mode of the stream parser.
	 *
	 * If the sock is set then the strparser is in receive callback mode.
	 * The upper layer calls strp_data_पढ़ोy to kick receive processing
	 * and strparser calls the पढ़ो_sock function on the socket to
	 * get packets.
	 *
	 * If the sock is not set then the strparser is in general mode.
	 * The upper layer calls strp_process क्रम each skb to be parsed.
	 */

	अगर (!sk) अणु
		अगर (!cb->lock || !cb->unlock)
			वापस -EINVAL;
	पूर्ण

	स_रखो(strp, 0, माप(*strp));

	strp->sk = sk;

	strp->cb.lock = cb->lock ? : strp_sock_lock;
	strp->cb.unlock = cb->unlock ? : strp_sock_unlock;
	strp->cb.rcv_msg = cb->rcv_msg;
	strp->cb.parse_msg = cb->parse_msg;
	strp->cb.पढ़ो_sock_करोne = cb->पढ़ो_sock_करोne ? : शेष_पढ़ो_sock_करोne;
	strp->cb.पात_parser = cb->पात_parser ? : strp_पात_strp;

	INIT_DELAYED_WORK(&strp->msg_समयr_work, strp_msg_समयout);
	INIT_WORK(&strp->work, strp_work);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(strp_init);

/* Sock process lock held (lock_sock) */
व्योम __strp_unछोड़ो(काष्ठा strparser *strp)
अणु
	strp->छोड़ोd = 0;

	अगर (strp->need_bytes) अणु
		अगर (strp_peek_len(strp) < strp->need_bytes)
			वापस;
	पूर्ण
	strp_पढ़ो_sock(strp);
पूर्ण
EXPORT_SYMBOL_GPL(__strp_unछोड़ो);

व्योम strp_unछोड़ो(काष्ठा strparser *strp)
अणु
	strp->छोड़ोd = 0;

	/* Sync setting छोड़ोd with RX work */
	smp_mb();

	queue_work(strp_wq, &strp->work);
पूर्ण
EXPORT_SYMBOL_GPL(strp_unछोड़ो);

/* strp must alपढ़ोy be stopped so that strp_recv will no दीर्घer be called.
 * Note that strp_करोne is not called with the lower socket held.
 */
व्योम strp_करोne(काष्ठा strparser *strp)
अणु
	WARN_ON(!strp->stopped);

	cancel_delayed_work_sync(&strp->msg_समयr_work);
	cancel_work_sync(&strp->work);

	अगर (strp->skb_head) अणु
		kमुक्त_skb(strp->skb_head);
		strp->skb_head = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(strp_करोne);

व्योम strp_stop(काष्ठा strparser *strp)
अणु
	strp->stopped = 1;
पूर्ण
EXPORT_SYMBOL_GPL(strp_stop);

व्योम strp_check_rcv(काष्ठा strparser *strp)
अणु
	queue_work(strp_wq, &strp->work);
पूर्ण
EXPORT_SYMBOL_GPL(strp_check_rcv);

अटल पूर्णांक __init strp_dev_init(व्योम)
अणु
	strp_wq = create_singlethपढ़ो_workqueue("kstrp");
	अगर (unlikely(!strp_wq))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
device_initcall(strp_dev_init);
