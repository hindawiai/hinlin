<शैली गुरु>
/* Copyright (c) 2018, Mellanox Technologies All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <crypto/aead.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <net/dst.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/tcp.h>
#समावेश <net/tls.h>

#समावेश "trace.h"

/* device_offload_lock is used to synchronize tls_dev_add
 * against NETDEV_DOWN notअगरications.
 */
अटल DECLARE_RWSEM(device_offload_lock);

अटल व्योम tls_device_gc_task(काष्ठा work_काष्ठा *work);

अटल DECLARE_WORK(tls_device_gc_work, tls_device_gc_task);
अटल LIST_HEAD(tls_device_gc_list);
अटल LIST_HEAD(tls_device_list);
अटल LIST_HEAD(tls_device_करोwn_list);
अटल DEFINE_SPINLOCK(tls_device_lock);

अटल व्योम tls_device_मुक्त_ctx(काष्ठा tls_context *ctx)
अणु
	अगर (ctx->tx_conf == TLS_HW) अणु
		kमुक्त(tls_offload_ctx_tx(ctx));
		kमुक्त(ctx->tx.rec_seq);
		kमुक्त(ctx->tx.iv);
	पूर्ण

	अगर (ctx->rx_conf == TLS_HW)
		kमुक्त(tls_offload_ctx_rx(ctx));

	tls_ctx_मुक्त(शून्य, ctx);
पूर्ण

अटल व्योम tls_device_gc_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tls_context *ctx, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(gc_list);

	spin_lock_irqsave(&tls_device_lock, flags);
	list_splice_init(&tls_device_gc_list, &gc_list);
	spin_unlock_irqrestore(&tls_device_lock, flags);

	list_क्रम_each_entry_safe(ctx, पंचांगp, &gc_list, list) अणु
		काष्ठा net_device *netdev = ctx->netdev;

		अगर (netdev && ctx->tx_conf == TLS_HW) अणु
			netdev->tlsdev_ops->tls_dev_del(netdev, ctx,
							TLS_OFFLOAD_CTX_सूची_TX);
			dev_put(netdev);
			ctx->netdev = शून्य;
		पूर्ण

		list_del(&ctx->list);
		tls_device_मुक्त_ctx(ctx);
	पूर्ण
पूर्ण

अटल व्योम tls_device_queue_ctx_deकाष्ठाion(काष्ठा tls_context *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tls_device_lock, flags);
	list_move_tail(&ctx->list, &tls_device_gc_list);

	/* schedule_work inside the spinlock
	 * to make sure tls_device_करोwn रुकोs क्रम that work.
	 */
	schedule_work(&tls_device_gc_work);

	spin_unlock_irqrestore(&tls_device_lock, flags);
पूर्ण

/* We assume that the socket is alपढ़ोy connected */
अटल काष्ठा net_device *get_netdev_क्रम_sock(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst = sk_dst_get(sk);
	काष्ठा net_device *netdev = शून्य;

	अगर (likely(dst)) अणु
		netdev = netdev_sk_get_lowest_dev(dst->dev, sk);
		dev_hold(netdev);
	पूर्ण

	dst_release(dst);

	वापस netdev;
पूर्ण

अटल व्योम destroy_record(काष्ठा tls_record_info *record)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < record->num_frags; i++)
		__skb_frag_unref(&record->frags[i]);
	kमुक्त(record);
पूर्ण

अटल व्योम delete_all_records(काष्ठा tls_offload_context_tx *offload_ctx)
अणु
	काष्ठा tls_record_info *info, *temp;

	list_क्रम_each_entry_safe(info, temp, &offload_ctx->records_list, list) अणु
		list_del(&info->list);
		destroy_record(info);
	पूर्ण

	offload_ctx->retransmit_hपूर्णांक = शून्य;
पूर्ण

अटल व्योम tls_icsk_clean_acked(काष्ठा sock *sk, u32 acked_seq)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_record_info *info, *temp;
	काष्ठा tls_offload_context_tx *ctx;
	u64 deleted_records = 0;
	अचिन्हित दीर्घ flags;

	अगर (!tls_ctx)
		वापस;

	ctx = tls_offload_ctx_tx(tls_ctx);

	spin_lock_irqsave(&ctx->lock, flags);
	info = ctx->retransmit_hपूर्णांक;
	अगर (info && !beक्रमe(acked_seq, info->end_seq))
		ctx->retransmit_hपूर्णांक = शून्य;

	list_क्रम_each_entry_safe(info, temp, &ctx->records_list, list) अणु
		अगर (beक्रमe(acked_seq, info->end_seq))
			अवरोध;
		list_del(&info->list);

		destroy_record(info);
		deleted_records++;
	पूर्ण

	ctx->unacked_record_sn += deleted_records;
	spin_unlock_irqrestore(&ctx->lock, flags);
पूर्ण

/* At this poपूर्णांक, there should be no references on this
 * socket and no in-flight SKBs associated with this
 * socket, so it is safe to मुक्त all the resources.
 */
व्योम tls_device_sk_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);

	tls_ctx->sk_deकाष्ठा(sk);

	अगर (tls_ctx->tx_conf == TLS_HW) अणु
		अगर (ctx->खोलो_record)
			destroy_record(ctx->खोलो_record);
		delete_all_records(ctx);
		crypto_मुक्त_aead(ctx->aead_send);
		clean_acked_data_disable(inet_csk(sk));
	पूर्ण

	अगर (refcount_dec_and_test(&tls_ctx->refcount))
		tls_device_queue_ctx_deकाष्ठाion(tls_ctx);
पूर्ण
EXPORT_SYMBOL_GPL(tls_device_sk_deकाष्ठा);

व्योम tls_device_मुक्त_resources_tx(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);

	tls_मुक्त_partial_record(sk, tls_ctx);
पूर्ण

व्योम tls_offload_tx_resync_request(काष्ठा sock *sk, u32 got_seq, u32 exp_seq)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);

	trace_tls_device_tx_resync_req(sk, got_seq, exp_seq);
	WARN_ON(test_and_set_bit(TLS_TX_SYNC_SCHED, &tls_ctx->flags));
पूर्ण
EXPORT_SYMBOL_GPL(tls_offload_tx_resync_request);

अटल व्योम tls_device_resync_tx(काष्ठा sock *sk, काष्ठा tls_context *tls_ctx,
				 u32 seq)
अणु
	काष्ठा net_device *netdev;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;
	u8 *rcd_sn;

	skb = tcp_ग_लिखो_queue_tail(sk);
	अगर (skb)
		TCP_SKB_CB(skb)->eor = 1;

	rcd_sn = tls_ctx->tx.rec_seq;

	trace_tls_device_tx_resync_send(sk, seq, rcd_sn);
	करोwn_पढ़ो(&device_offload_lock);
	netdev = tls_ctx->netdev;
	अगर (netdev)
		err = netdev->tlsdev_ops->tls_dev_resync(netdev, sk, seq,
							 rcd_sn,
							 TLS_OFFLOAD_CTX_सूची_TX);
	up_पढ़ो(&device_offload_lock);
	अगर (err)
		वापस;

	clear_bit_unlock(TLS_TX_SYNC_SCHED, &tls_ctx->flags);
पूर्ण

अटल व्योम tls_append_frag(काष्ठा tls_record_info *record,
			    काष्ठा page_frag *pfrag,
			    पूर्णांक size)
अणु
	skb_frag_t *frag;

	frag = &record->frags[record->num_frags - 1];
	अगर (skb_frag_page(frag) == pfrag->page &&
	    skb_frag_off(frag) + skb_frag_size(frag) == pfrag->offset) अणु
		skb_frag_size_add(frag, size);
	पूर्ण अन्यथा अणु
		++frag;
		__skb_frag_set_page(frag, pfrag->page);
		skb_frag_off_set(frag, pfrag->offset);
		skb_frag_size_set(frag, size);
		++record->num_frags;
		get_page(pfrag->page);
	पूर्ण

	pfrag->offset += size;
	record->len += size;
पूर्ण

अटल पूर्णांक tls_push_record(काष्ठा sock *sk,
			   काष्ठा tls_context *ctx,
			   काष्ठा tls_offload_context_tx *offload_ctx,
			   काष्ठा tls_record_info *record,
			   पूर्णांक flags)
अणु
	काष्ठा tls_prot_info *prot = &ctx->prot_info;
	काष्ठा tcp_sock *tp = tcp_sk(sk);
	skb_frag_t *frag;
	पूर्णांक i;

	record->end_seq = tp->ग_लिखो_seq + record->len;
	list_add_tail_rcu(&record->list, &offload_ctx->records_list);
	offload_ctx->खोलो_record = शून्य;

	अगर (test_bit(TLS_TX_SYNC_SCHED, &ctx->flags))
		tls_device_resync_tx(sk, ctx, tp->ग_लिखो_seq);

	tls_advance_record_sn(sk, prot, &ctx->tx);

	क्रम (i = 0; i < record->num_frags; i++) अणु
		frag = &record->frags[i];
		sg_unmark_end(&offload_ctx->sg_tx_data[i]);
		sg_set_page(&offload_ctx->sg_tx_data[i], skb_frag_page(frag),
			    skb_frag_size(frag), skb_frag_off(frag));
		sk_mem_अक्षरge(sk, skb_frag_size(frag));
		get_page(skb_frag_page(frag));
	पूर्ण
	sg_mark_end(&offload_ctx->sg_tx_data[record->num_frags - 1]);

	/* all पढ़ोy, send */
	वापस tls_push_sg(sk, ctx, offload_ctx->sg_tx_data, 0, flags);
पूर्ण

अटल पूर्णांक tls_device_record_बंद(काष्ठा sock *sk,
				   काष्ठा tls_context *ctx,
				   काष्ठा tls_record_info *record,
				   काष्ठा page_frag *pfrag,
				   अचिन्हित अक्षर record_type)
अणु
	काष्ठा tls_prot_info *prot = &ctx->prot_info;
	पूर्णांक ret;

	/* append tag
	 * device will fill in the tag, we just need to append a placeholder
	 * use socket memory to improve coalescing (re-using a single buffer
	 * increases frag count)
	 * अगर we can't allocate memory now, steal some back from data
	 */
	अगर (likely(skb_page_frag_refill(prot->tag_size, pfrag,
					sk->sk_allocation))) अणु
		ret = 0;
		tls_append_frag(record, pfrag, prot->tag_size);
	पूर्ण अन्यथा अणु
		ret = prot->tag_size;
		अगर (record->len <= prot->overhead_size)
			वापस -ENOMEM;
	पूर्ण

	/* fill prepend */
	tls_fill_prepend(ctx, skb_frag_address(&record->frags[0]),
			 record->len - prot->overhead_size,
			 record_type);
	वापस ret;
पूर्ण

अटल पूर्णांक tls_create_new_record(काष्ठा tls_offload_context_tx *offload_ctx,
				 काष्ठा page_frag *pfrag,
				 माप_प्रकार prepend_size)
अणु
	काष्ठा tls_record_info *record;
	skb_frag_t *frag;

	record = kदो_स्मृति(माप(*record), GFP_KERNEL);
	अगर (!record)
		वापस -ENOMEM;

	frag = &record->frags[0];
	__skb_frag_set_page(frag, pfrag->page);
	skb_frag_off_set(frag, pfrag->offset);
	skb_frag_size_set(frag, prepend_size);

	get_page(pfrag->page);
	pfrag->offset += prepend_size;

	record->num_frags = 1;
	record->len = prepend_size;
	offload_ctx->खोलो_record = record;
	वापस 0;
पूर्ण

अटल पूर्णांक tls_करो_allocation(काष्ठा sock *sk,
			     काष्ठा tls_offload_context_tx *offload_ctx,
			     काष्ठा page_frag *pfrag,
			     माप_प्रकार prepend_size)
अणु
	पूर्णांक ret;

	अगर (!offload_ctx->खोलो_record) अणु
		अगर (unlikely(!skb_page_frag_refill(prepend_size, pfrag,
						   sk->sk_allocation))) अणु
			READ_ONCE(sk->sk_prot)->enter_memory_pressure(sk);
			sk_stream_moderate_sndbuf(sk);
			वापस -ENOMEM;
		पूर्ण

		ret = tls_create_new_record(offload_ctx, pfrag, prepend_size);
		अगर (ret)
			वापस ret;

		अगर (pfrag->size > pfrag->offset)
			वापस 0;
	पूर्ण

	अगर (!sk_page_frag_refill(sk, pfrag))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक tls_device_copy_data(व्योम *addr, माप_प्रकार bytes, काष्ठा iov_iter *i)
अणु
	माप_प्रकार pre_copy, nocache;

	pre_copy = ~((अचिन्हित दीर्घ)addr - 1) & (SMP_CACHE_BYTES - 1);
	अगर (pre_copy) अणु
		pre_copy = min(pre_copy, bytes);
		अगर (copy_from_iter(addr, pre_copy, i) != pre_copy)
			वापस -EFAULT;
		bytes -= pre_copy;
		addr += pre_copy;
	पूर्ण

	nocache = round_करोwn(bytes, SMP_CACHE_BYTES);
	अगर (copy_from_iter_nocache(addr, nocache, i) != nocache)
		वापस -EFAULT;
	bytes -= nocache;
	addr += nocache;

	अगर (bytes && copy_from_iter(addr, bytes, i) != bytes)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक tls_push_data(काष्ठा sock *sk,
			 काष्ठा iov_iter *msg_iter,
			 माप_प्रकार size, पूर्णांक flags,
			 अचिन्हित अक्षर record_type)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);
	काष्ठा tls_record_info *record;
	पूर्णांक tls_push_record_flags;
	काष्ठा page_frag *pfrag;
	माप_प्रकार orig_size = size;
	u32 max_खोलो_record_len;
	bool more = false;
	bool करोne = false;
	पूर्णांक copy, rc = 0;
	दीर्घ समयo;

	अगर (flags &
	    ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL | MSG_SENDPAGE_NOTLAST))
		वापस -EOPNOTSUPP;

	अगर (unlikely(sk->sk_err))
		वापस -sk->sk_err;

	flags |= MSG_SENDPAGE_DECRYPTED;
	tls_push_record_flags = flags | MSG_SENDPAGE_NOTLAST;

	समयo = sock_sndसमयo(sk, flags & MSG_DONTWAIT);
	अगर (tls_is_partially_sent_record(tls_ctx)) अणु
		rc = tls_push_partial_record(sk, tls_ctx, flags);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	pfrag = sk_page_frag(sk);

	/* TLS_HEADER_SIZE is not counted as part of the TLS record, and
	 * we need to leave room क्रम an authentication tag.
	 */
	max_खोलो_record_len = TLS_MAX_PAYLOAD_SIZE +
			      prot->prepend_size;
	करो अणु
		rc = tls_करो_allocation(sk, ctx, pfrag, prot->prepend_size);
		अगर (unlikely(rc)) अणु
			rc = sk_stream_रुको_memory(sk, &समयo);
			अगर (!rc)
				जारी;

			record = ctx->खोलो_record;
			अगर (!record)
				अवरोध;
handle_error:
			अगर (record_type != TLS_RECORD_TYPE_DATA) अणु
				/* aव्योम sending partial
				 * record with type !=
				 * application_data
				 */
				size = orig_size;
				destroy_record(record);
				ctx->खोलो_record = शून्य;
			पूर्ण अन्यथा अगर (record->len > prot->prepend_size) अणु
				जाओ last_record;
			पूर्ण

			अवरोध;
		पूर्ण

		record = ctx->खोलो_record;
		copy = min_t(माप_प्रकार, size, (pfrag->size - pfrag->offset));
		copy = min_t(माप_प्रकार, copy, (max_खोलो_record_len - record->len));

		rc = tls_device_copy_data(page_address(pfrag->page) +
					  pfrag->offset, copy, msg_iter);
		अगर (rc)
			जाओ handle_error;
		tls_append_frag(record, pfrag, copy);

		size -= copy;
		अगर (!size) अणु
last_record:
			tls_push_record_flags = flags;
			अगर (flags & (MSG_SENDPAGE_NOTLAST | MSG_MORE)) अणु
				more = true;
				अवरोध;
			पूर्ण

			करोne = true;
		पूर्ण

		अगर (करोne || record->len >= max_खोलो_record_len ||
		    (record->num_frags >= MAX_SKB_FRAGS - 1)) अणु
			rc = tls_device_record_बंद(sk, tls_ctx, record,
						     pfrag, record_type);
			अगर (rc) अणु
				अगर (rc > 0) अणु
					size += rc;
				पूर्ण अन्यथा अणु
					size = orig_size;
					destroy_record(record);
					ctx->खोलो_record = शून्य;
					अवरोध;
				पूर्ण
			पूर्ण

			rc = tls_push_record(sk,
					     tls_ctx,
					     ctx,
					     record,
					     tls_push_record_flags);
			अगर (rc < 0)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (!करोne);

	tls_ctx->pending_खोलो_record_frags = more;

	अगर (orig_size - size > 0)
		rc = orig_size - size;

	वापस rc;
पूर्ण

पूर्णांक tls_device_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	अचिन्हित अक्षर record_type = TLS_RECORD_TYPE_DATA;
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	पूर्णांक rc;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);

	अगर (unlikely(msg->msg_controllen)) अणु
		rc = tls_proccess_cmsg(sk, msg, &record_type);
		अगर (rc)
			जाओ out;
	पूर्ण

	rc = tls_push_data(sk, &msg->msg_iter, size,
			   msg->msg_flags, record_type);

out:
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	वापस rc;
पूर्ण

पूर्णांक tls_device_sendpage(काष्ठा sock *sk, काष्ठा page *page,
			पूर्णांक offset, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा iov_iter	msg_iter;
	अक्षर *kaddr;
	काष्ठा kvec iov;
	पूर्णांक rc;

	अगर (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);

	अगर (flags & MSG_OOB) अणु
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	kaddr = kmap(page);
	iov.iov_base = kaddr + offset;
	iov.iov_len = size;
	iov_iter_kvec(&msg_iter, WRITE, &iov, 1, size);
	rc = tls_push_data(sk, &msg_iter, size,
			   flags, TLS_RECORD_TYPE_DATA);
	kunmap(page);

out:
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	वापस rc;
पूर्ण

काष्ठा tls_record_info *tls_get_record(काष्ठा tls_offload_context_tx *context,
				       u32 seq, u64 *p_record_sn)
अणु
	u64 record_sn = context->hपूर्णांक_record_sn;
	काष्ठा tls_record_info *info, *last;

	info = context->retransmit_hपूर्णांक;
	अगर (!info ||
	    beक्रमe(seq, info->end_seq - info->len)) अणु
		/* अगर retransmit_hपूर्णांक is irrelevant start
		 * from the beginning of the list
		 */
		info = list_first_entry_or_null(&context->records_list,
						काष्ठा tls_record_info, list);
		अगर (!info)
			वापस शून्य;
		/* send the start_marker record अगर seq number is beक्रमe the
		 * tls offload start marker sequence number. This record is
		 * required to handle TCP packets which are beक्रमe TLS offload
		 * started.
		 *  And अगर it's not start marker, look अगर this seq number
		 * beदीर्घs to the list.
		 */
		अगर (likely(!tls_record_is_start_marker(info))) अणु
			/* we have the first record, get the last record to see
			 * अगर this seq number beदीर्घs to the list.
			 */
			last = list_last_entry(&context->records_list,
					       काष्ठा tls_record_info, list);

			अगर (!between(seq, tls_record_start_seq(info),
				     last->end_seq))
				वापस शून्य;
		पूर्ण
		record_sn = context->unacked_record_sn;
	पूर्ण

	/* We just need the _rcu क्रम the READ_ONCE() */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_from_rcu(info, &context->records_list, list) अणु
		अगर (beक्रमe(seq, info->end_seq)) अणु
			अगर (!context->retransmit_hपूर्णांक ||
			    after(info->end_seq,
				  context->retransmit_hपूर्णांक->end_seq)) अणु
				context->hपूर्णांक_record_sn = record_sn;
				context->retransmit_hपूर्णांक = info;
			पूर्ण
			*p_record_sn = record_sn;
			जाओ निकास_rcu_unlock;
		पूर्ण
		record_sn++;
	पूर्ण
	info = शून्य;

निकास_rcu_unlock:
	rcu_पढ़ो_unlock();
	वापस info;
पूर्ण
EXPORT_SYMBOL(tls_get_record);

अटल पूर्णांक tls_device_push_pending_record(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा iov_iter	msg_iter;

	iov_iter_kvec(&msg_iter, WRITE, शून्य, 0, 0);
	वापस tls_push_data(sk, &msg_iter, 0, flags, TLS_RECORD_TYPE_DATA);
पूर्ण

व्योम tls_device_ग_लिखो_space(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	अगर (tls_is_partially_sent_record(ctx)) अणु
		gfp_t sk_allocation = sk->sk_allocation;

		WARN_ON_ONCE(sk->sk_ग_लिखो_pending);

		sk->sk_allocation = GFP_ATOMIC;
		tls_push_partial_record(sk, ctx,
					MSG_DONTWAIT | MSG_NOSIGNAL |
					MSG_SENDPAGE_DECRYPTED);
		sk->sk_allocation = sk_allocation;
	पूर्ण
पूर्ण

अटल व्योम tls_device_resync_rx(काष्ठा tls_context *tls_ctx,
				 काष्ठा sock *sk, u32 seq, u8 *rcd_sn)
अणु
	काष्ठा tls_offload_context_rx *rx_ctx = tls_offload_ctx_rx(tls_ctx);
	काष्ठा net_device *netdev;

	trace_tls_device_rx_resync_send(sk, seq, rcd_sn, rx_ctx->resync_type);
	rcu_पढ़ो_lock();
	netdev = READ_ONCE(tls_ctx->netdev);
	अगर (netdev)
		netdev->tlsdev_ops->tls_dev_resync(netdev, sk, seq, rcd_sn,
						   TLS_OFFLOAD_CTX_सूची_RX);
	rcu_पढ़ो_unlock();
	TLS_INC_STATS(sock_net(sk), LINUX_MIB_TLSRXDEVICERESYNC);
पूर्ण

अटल bool
tls_device_rx_resync_async(काष्ठा tls_offload_resync_async *resync_async,
			   s64 resync_req, u32 *seq, u16 *rcd_delta)
अणु
	u32 is_async = resync_req & RESYNC_REQ_ASYNC;
	u32 req_seq = resync_req >> 32;
	u32 req_end = req_seq + ((resync_req >> 16) & 0xffff);
	u16 i;

	*rcd_delta = 0;

	अगर (is_async) अणु
		/* shouldn't get to wraparound:
		 * too दीर्घ in async stage, something bad happened
		 */
		अगर (WARN_ON_ONCE(resync_async->rcd_delta == अच_लघु_उच्च))
			वापस false;

		/* asynchronous stage: log all headers seq such that
		 * req_seq <= seq <= end_seq, and रुको क्रम real resync request
		 */
		अगर (beक्रमe(*seq, req_seq))
			वापस false;
		अगर (!after(*seq, req_end) &&
		    resync_async->loglen < TLS_DEVICE_RESYNC_ASYNC_LOGMAX)
			resync_async->log[resync_async->loglen++] = *seq;

		resync_async->rcd_delta++;

		वापस false;
	पूर्ण

	/* synchronous stage: check against the logged entries and
	 * proceed to check the next entries अगर no match was found
	 */
	क्रम (i = 0; i < resync_async->loglen; i++)
		अगर (req_seq == resync_async->log[i] &&
		    atomic64_try_cmpxchg(&resync_async->req, &resync_req, 0)) अणु
			*rcd_delta = resync_async->rcd_delta - i;
			*seq = req_seq;
			resync_async->loglen = 0;
			resync_async->rcd_delta = 0;
			वापस true;
		पूर्ण

	resync_async->loglen = 0;
	resync_async->rcd_delta = 0;

	अगर (req_seq == *seq &&
	    atomic64_try_cmpxchg(&resync_async->req,
				 &resync_req, 0))
		वापस true;

	वापस false;
पूर्ण

व्योम tls_device_rx_resync_new_rec(काष्ठा sock *sk, u32 rcd_len, u32 seq)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_offload_context_rx *rx_ctx;
	u8 rcd_sn[TLS_MAX_REC_SEQ_SIZE];
	u32 sock_data, is_req_pending;
	काष्ठा tls_prot_info *prot;
	s64 resync_req;
	u16 rcd_delta;
	u32 req_seq;

	अगर (tls_ctx->rx_conf != TLS_HW)
		वापस;
	अगर (unlikely(test_bit(TLS_RX_DEV_DEGRADED, &tls_ctx->flags)))
		वापस;

	prot = &tls_ctx->prot_info;
	rx_ctx = tls_offload_ctx_rx(tls_ctx);
	स_नकल(rcd_sn, tls_ctx->rx.rec_seq, prot->rec_seq_size);

	चयन (rx_ctx->resync_type) अणु
	हाल TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ:
		resync_req = atomic64_पढ़ो(&rx_ctx->resync_req);
		req_seq = resync_req >> 32;
		seq += TLS_HEADER_SIZE - 1;
		is_req_pending = resync_req;

		अगर (likely(!is_req_pending) || req_seq != seq ||
		    !atomic64_try_cmpxchg(&rx_ctx->resync_req, &resync_req, 0))
			वापस;
		अवरोध;
	हाल TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT:
		अगर (likely(!rx_ctx->resync_nh_करो_now))
			वापस;

		/* head of next rec is alपढ़ोy in, note that the sock_inq will
		 * include the currently parsed message when called from parser
		 */
		sock_data = tcp_inq(sk);
		अगर (sock_data > rcd_len) अणु
			trace_tls_device_rx_resync_nh_delay(sk, sock_data,
							    rcd_len);
			वापस;
		पूर्ण

		rx_ctx->resync_nh_करो_now = 0;
		seq += rcd_len;
		tls_bigपूर्णांक_increment(rcd_sn, prot->rec_seq_size);
		अवरोध;
	हाल TLS_OFFLOAD_SYNC_TYPE_DRIVER_REQ_ASYNC:
		resync_req = atomic64_पढ़ो(&rx_ctx->resync_async->req);
		is_req_pending = resync_req;
		अगर (likely(!is_req_pending))
			वापस;

		अगर (!tls_device_rx_resync_async(rx_ctx->resync_async,
						resync_req, &seq, &rcd_delta))
			वापस;
		tls_bigपूर्णांक_subtract(rcd_sn, rcd_delta);
		अवरोध;
	पूर्ण

	tls_device_resync_rx(tls_ctx, sk, seq, rcd_sn);
पूर्ण

अटल व्योम tls_device_core_ctrl_rx_resync(काष्ठा tls_context *tls_ctx,
					   काष्ठा tls_offload_context_rx *ctx,
					   काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा strp_msg *rxm;

	/* device will request resyncs by itself based on stream scan */
	अगर (ctx->resync_type != TLS_OFFLOAD_SYNC_TYPE_CORE_NEXT_HINT)
		वापस;
	/* alपढ़ोy scheduled */
	अगर (ctx->resync_nh_करो_now)
		वापस;
	/* seen decrypted fragments since last fully-failed record */
	अगर (ctx->resync_nh_reset) अणु
		ctx->resync_nh_reset = 0;
		ctx->resync_nh.decrypted_failed = 1;
		ctx->resync_nh.decrypted_tgt = TLS_DEVICE_RESYNC_NH_START_IVAL;
		वापस;
	पूर्ण

	अगर (++ctx->resync_nh.decrypted_failed <= ctx->resync_nh.decrypted_tgt)
		वापस;

	/* करोing resync, bump the next target in हाल it fails */
	अगर (ctx->resync_nh.decrypted_tgt < TLS_DEVICE_RESYNC_NH_MAX_IVAL)
		ctx->resync_nh.decrypted_tgt *= 2;
	अन्यथा
		ctx->resync_nh.decrypted_tgt += TLS_DEVICE_RESYNC_NH_MAX_IVAL;

	rxm = strp_msg(skb);

	/* head of next rec is alपढ़ोy in, parser will sync क्रम us */
	अगर (tcp_inq(sk) > rxm->full_len) अणु
		trace_tls_device_rx_resync_nh_schedule(sk);
		ctx->resync_nh_करो_now = 1;
	पूर्ण अन्यथा अणु
		काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
		u8 rcd_sn[TLS_MAX_REC_SEQ_SIZE];

		स_नकल(rcd_sn, tls_ctx->rx.rec_seq, prot->rec_seq_size);
		tls_bigपूर्णांक_increment(rcd_sn, prot->rec_seq_size);

		tls_device_resync_rx(tls_ctx, sk, tcp_sk(sk)->copied_seq,
				     rcd_sn);
	पूर्ण
पूर्ण

अटल पूर्णांक tls_device_reencrypt(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा strp_msg *rxm = strp_msg(skb);
	पूर्णांक err = 0, offset = rxm->offset, copy, nsg, data_len, pos;
	काष्ठा sk_buff *skb_iter, *unused;
	काष्ठा scatterlist sg[1];
	अक्षर *orig_buf, *buf;

	orig_buf = kदो_स्मृति(rxm->full_len + TLS_HEADER_SIZE +
			   TLS_CIPHER_AES_GCM_128_IV_SIZE, sk->sk_allocation);
	अगर (!orig_buf)
		वापस -ENOMEM;
	buf = orig_buf;

	nsg = skb_cow_data(skb, 0, &unused);
	अगर (unlikely(nsg < 0)) अणु
		err = nsg;
		जाओ मुक्त_buf;
	पूर्ण

	sg_init_table(sg, 1);
	sg_set_buf(&sg[0], buf,
		   rxm->full_len + TLS_HEADER_SIZE +
		   TLS_CIPHER_AES_GCM_128_IV_SIZE);
	err = skb_copy_bits(skb, offset, buf,
			    TLS_HEADER_SIZE + TLS_CIPHER_AES_GCM_128_IV_SIZE);
	अगर (err)
		जाओ मुक्त_buf;

	/* We are पूर्णांकerested only in the decrypted data not the auth */
	err = decrypt_skb(sk, skb, sg);
	अगर (err != -EBADMSG)
		जाओ मुक्त_buf;
	अन्यथा
		err = 0;

	data_len = rxm->full_len - TLS_CIPHER_AES_GCM_128_TAG_SIZE;

	अगर (skb_pagelen(skb) > offset) अणु
		copy = min_t(पूर्णांक, skb_pagelen(skb) - offset, data_len);

		अगर (skb->decrypted) अणु
			err = skb_store_bits(skb, offset, buf, copy);
			अगर (err)
				जाओ मुक्त_buf;
		पूर्ण

		offset += copy;
		buf += copy;
	पूर्ण

	pos = skb_pagelen(skb);
	skb_walk_frags(skb, skb_iter) अणु
		पूर्णांक frag_pos;

		/* Practically all frags must beदीर्घ to msg अगर reencrypt
		 * is needed with current strparser and coalescing logic,
		 * but strparser may "get optimized", so let's be safe.
		 */
		अगर (pos + skb_iter->len <= offset)
			जाओ करोne_with_frag;
		अगर (pos >= data_len + rxm->offset)
			अवरोध;

		frag_pos = offset - pos;
		copy = min_t(पूर्णांक, skb_iter->len - frag_pos,
			     data_len + rxm->offset - offset);

		अगर (skb_iter->decrypted) अणु
			err = skb_store_bits(skb_iter, frag_pos, buf, copy);
			अगर (err)
				जाओ मुक्त_buf;
		पूर्ण

		offset += copy;
		buf += copy;
करोne_with_frag:
		pos += skb_iter->len;
	पूर्ण

मुक्त_buf:
	kमुक्त(orig_buf);
	वापस err;
पूर्ण

पूर्णांक tls_device_decrypted(काष्ठा sock *sk, काष्ठा tls_context *tls_ctx,
			 काष्ठा sk_buff *skb, काष्ठा strp_msg *rxm)
अणु
	काष्ठा tls_offload_context_rx *ctx = tls_offload_ctx_rx(tls_ctx);
	पूर्णांक is_decrypted = skb->decrypted;
	पूर्णांक is_encrypted = !is_decrypted;
	काष्ठा sk_buff *skb_iter;

	/* Check अगर all the data is decrypted alपढ़ोy */
	skb_walk_frags(skb, skb_iter) अणु
		is_decrypted &= skb_iter->decrypted;
		is_encrypted &= !skb_iter->decrypted;
	पूर्ण

	trace_tls_device_decrypted(sk, tcp_sk(sk)->copied_seq - rxm->full_len,
				   tls_ctx->rx.rec_seq, rxm->full_len,
				   is_encrypted, is_decrypted);

	ctx->sw.decrypted |= is_decrypted;

	अगर (unlikely(test_bit(TLS_RX_DEV_DEGRADED, &tls_ctx->flags))) अणु
		अगर (likely(is_encrypted || is_decrypted))
			वापस 0;

		/* After tls_device_करोwn disables the offload, the next SKB will
		 * likely have initial fragments decrypted, and final ones not
		 * decrypted. We need to reencrypt that single SKB.
		 */
		वापस tls_device_reencrypt(sk, skb);
	पूर्ण

	/* Return immediately अगर the record is either entirely plaपूर्णांकext or
	 * entirely ciphertext. Otherwise handle reencrypt partially decrypted
	 * record.
	 */
	अगर (is_decrypted) अणु
		ctx->resync_nh_reset = 1;
		वापस 0;
	पूर्ण
	अगर (is_encrypted) अणु
		tls_device_core_ctrl_rx_resync(tls_ctx, ctx, sk, skb);
		वापस 0;
	पूर्ण

	ctx->resync_nh_reset = 1;
	वापस tls_device_reencrypt(sk, skb);
पूर्ण

अटल व्योम tls_device_attach(काष्ठा tls_context *ctx, काष्ठा sock *sk,
			      काष्ठा net_device *netdev)
अणु
	अगर (sk->sk_deकाष्ठा != tls_device_sk_deकाष्ठा) अणु
		refcount_set(&ctx->refcount, 1);
		dev_hold(netdev);
		ctx->netdev = netdev;
		spin_lock_irq(&tls_device_lock);
		list_add_tail(&ctx->list, &tls_device_list);
		spin_unlock_irq(&tls_device_lock);

		ctx->sk_deकाष्ठा = sk->sk_deकाष्ठा;
		smp_store_release(&sk->sk_deकाष्ठा, tls_device_sk_deकाष्ठा);
	पूर्ण
पूर्ण

पूर्णांक tls_set_device_offload(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	u16 nonce_size, tag_size, iv_size, rec_seq_size, salt_size;
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा tls_prot_info *prot = &tls_ctx->prot_info;
	काष्ठा tls_record_info *start_marker_record;
	काष्ठा tls_offload_context_tx *offload_ctx;
	काष्ठा tls_crypto_info *crypto_info;
	काष्ठा net_device *netdev;
	अक्षर *iv, *rec_seq;
	काष्ठा sk_buff *skb;
	__be64 rcd_sn;
	पूर्णांक rc;

	अगर (!ctx)
		वापस -EINVAL;

	अगर (ctx->priv_ctx_tx)
		वापस -EEXIST;

	start_marker_record = kदो_स्मृति(माप(*start_marker_record), GFP_KERNEL);
	अगर (!start_marker_record)
		वापस -ENOMEM;

	offload_ctx = kzalloc(TLS_OFFLOAD_CONTEXT_SIZE_TX, GFP_KERNEL);
	अगर (!offload_ctx) अणु
		rc = -ENOMEM;
		जाओ मुक्त_marker_record;
	पूर्ण

	crypto_info = &ctx->crypto_send.info;
	अगर (crypto_info->version != TLS_1_2_VERSION) अणु
		rc = -EOPNOTSUPP;
		जाओ मुक्त_offload_ctx;
	पूर्ण

	चयन (crypto_info->cipher_type) अणु
	हाल TLS_CIPHER_AES_GCM_128:
		nonce_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		tag_size = TLS_CIPHER_AES_GCM_128_TAG_SIZE;
		iv_size = TLS_CIPHER_AES_GCM_128_IV_SIZE;
		iv = ((काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info)->iv;
		rec_seq_size = TLS_CIPHER_AES_GCM_128_REC_SEQ_SIZE;
		salt_size = TLS_CIPHER_AES_GCM_128_SALT_SIZE;
		rec_seq =
		 ((काष्ठा tls12_crypto_info_aes_gcm_128 *)crypto_info)->rec_seq;
		अवरोध;
	शेष:
		rc = -EINVAL;
		जाओ मुक्त_offload_ctx;
	पूर्ण

	/* Sanity-check the rec_seq_size क्रम stack allocations */
	अगर (rec_seq_size > TLS_MAX_REC_SEQ_SIZE) अणु
		rc = -EINVAL;
		जाओ मुक्त_offload_ctx;
	पूर्ण

	prot->version = crypto_info->version;
	prot->cipher_type = crypto_info->cipher_type;
	prot->prepend_size = TLS_HEADER_SIZE + nonce_size;
	prot->tag_size = tag_size;
	prot->overhead_size = prot->prepend_size + prot->tag_size;
	prot->iv_size = iv_size;
	prot->salt_size = salt_size;
	ctx->tx.iv = kदो_स्मृति(iv_size + TLS_CIPHER_AES_GCM_128_SALT_SIZE,
			     GFP_KERNEL);
	अगर (!ctx->tx.iv) अणु
		rc = -ENOMEM;
		जाओ मुक्त_offload_ctx;
	पूर्ण

	स_नकल(ctx->tx.iv + TLS_CIPHER_AES_GCM_128_SALT_SIZE, iv, iv_size);

	prot->rec_seq_size = rec_seq_size;
	ctx->tx.rec_seq = kmemdup(rec_seq, rec_seq_size, GFP_KERNEL);
	अगर (!ctx->tx.rec_seq) अणु
		rc = -ENOMEM;
		जाओ मुक्त_iv;
	पूर्ण

	rc = tls_sw_fallback_init(sk, offload_ctx, crypto_info);
	अगर (rc)
		जाओ मुक्त_rec_seq;

	/* start at rec_seq - 1 to account क्रम the start marker record */
	स_नकल(&rcd_sn, ctx->tx.rec_seq, माप(rcd_sn));
	offload_ctx->unacked_record_sn = be64_to_cpu(rcd_sn) - 1;

	start_marker_record->end_seq = tcp_sk(sk)->ग_लिखो_seq;
	start_marker_record->len = 0;
	start_marker_record->num_frags = 0;

	INIT_LIST_HEAD(&offload_ctx->records_list);
	list_add_tail(&start_marker_record->list, &offload_ctx->records_list);
	spin_lock_init(&offload_ctx->lock);
	sg_init_table(offload_ctx->sg_tx_data,
		      ARRAY_SIZE(offload_ctx->sg_tx_data));

	clean_acked_data_enable(inet_csk(sk), &tls_icsk_clean_acked);
	ctx->push_pending_record = tls_device_push_pending_record;

	/* TLS offload is greatly simplअगरied अगर we करोn't send
	 * SKBs where only part of the payload needs to be encrypted.
	 * So mark the last skb in the ग_लिखो queue as end of record.
	 */
	skb = tcp_ग_लिखो_queue_tail(sk);
	अगर (skb)
		TCP_SKB_CB(skb)->eor = 1;

	netdev = get_netdev_क्रम_sock(sk);
	अगर (!netdev) अणु
		pr_err_ratelimited("%s: netdev not found\n", __func__);
		rc = -EINVAL;
		जाओ disable_cad;
	पूर्ण

	अगर (!(netdev->features & NETIF_F_HW_TLS_TX)) अणु
		rc = -EOPNOTSUPP;
		जाओ release_netdev;
	पूर्ण

	/* Aव्योम offloading अगर the device is करोwn
	 * We करोn't want to offload new flows after
	 * the NETDEV_DOWN event
	 *
	 * device_offload_lock is taken in tls_devices's NETDEV_DOWN
	 * handler thus protecting from the device going करोwn beक्रमe
	 * ctx was added to tls_device_list.
	 */
	करोwn_पढ़ो(&device_offload_lock);
	अगर (!(netdev->flags & IFF_UP)) अणु
		rc = -EINVAL;
		जाओ release_lock;
	पूर्ण

	ctx->priv_ctx_tx = offload_ctx;
	rc = netdev->tlsdev_ops->tls_dev_add(netdev, sk, TLS_OFFLOAD_CTX_सूची_TX,
					     &ctx->crypto_send.info,
					     tcp_sk(sk)->ग_लिखो_seq);
	trace_tls_device_offload_set(sk, TLS_OFFLOAD_CTX_सूची_TX,
				     tcp_sk(sk)->ग_लिखो_seq, rec_seq, rc);
	अगर (rc)
		जाओ release_lock;

	tls_device_attach(ctx, sk, netdev);
	up_पढ़ो(&device_offload_lock);

	/* following this assignment tls_is_sk_tx_device_offloaded
	 * will वापस true and the context might be accessed
	 * by the netdev's xmit function.
	 */
	smp_store_release(&sk->sk_validate_xmit_skb, tls_validate_xmit_skb);
	dev_put(netdev);

	वापस 0;

release_lock:
	up_पढ़ो(&device_offload_lock);
release_netdev:
	dev_put(netdev);
disable_cad:
	clean_acked_data_disable(inet_csk(sk));
	crypto_मुक्त_aead(offload_ctx->aead_send);
मुक्त_rec_seq:
	kमुक्त(ctx->tx.rec_seq);
मुक्त_iv:
	kमुक्त(ctx->tx.iv);
मुक्त_offload_ctx:
	kमुक्त(offload_ctx);
	ctx->priv_ctx_tx = शून्य;
मुक्त_marker_record:
	kमुक्त(start_marker_record);
	वापस rc;
पूर्ण

पूर्णांक tls_set_device_offload_rx(काष्ठा sock *sk, काष्ठा tls_context *ctx)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 *info;
	काष्ठा tls_offload_context_rx *context;
	काष्ठा net_device *netdev;
	पूर्णांक rc = 0;

	अगर (ctx->crypto_recv.info.version != TLS_1_2_VERSION)
		वापस -EOPNOTSUPP;

	netdev = get_netdev_क्रम_sock(sk);
	अगर (!netdev) अणु
		pr_err_ratelimited("%s: netdev not found\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!(netdev->features & NETIF_F_HW_TLS_RX)) अणु
		rc = -EOPNOTSUPP;
		जाओ release_netdev;
	पूर्ण

	/* Aव्योम offloading अगर the device is करोwn
	 * We करोn't want to offload new flows after
	 * the NETDEV_DOWN event
	 *
	 * device_offload_lock is taken in tls_devices's NETDEV_DOWN
	 * handler thus protecting from the device going करोwn beक्रमe
	 * ctx was added to tls_device_list.
	 */
	करोwn_पढ़ो(&device_offload_lock);
	अगर (!(netdev->flags & IFF_UP)) अणु
		rc = -EINVAL;
		जाओ release_lock;
	पूर्ण

	context = kzalloc(TLS_OFFLOAD_CONTEXT_SIZE_RX, GFP_KERNEL);
	अगर (!context) अणु
		rc = -ENOMEM;
		जाओ release_lock;
	पूर्ण
	context->resync_nh_reset = 1;

	ctx->priv_ctx_rx = context;
	rc = tls_set_sw_offload(sk, ctx, 0);
	अगर (rc)
		जाओ release_ctx;

	rc = netdev->tlsdev_ops->tls_dev_add(netdev, sk, TLS_OFFLOAD_CTX_सूची_RX,
					     &ctx->crypto_recv.info,
					     tcp_sk(sk)->copied_seq);
	info = (व्योम *)&ctx->crypto_recv.info;
	trace_tls_device_offload_set(sk, TLS_OFFLOAD_CTX_सूची_RX,
				     tcp_sk(sk)->copied_seq, info->rec_seq, rc);
	अगर (rc)
		जाओ मुक्त_sw_resources;

	tls_device_attach(ctx, sk, netdev);
	up_पढ़ो(&device_offload_lock);

	dev_put(netdev);

	वापस 0;

मुक्त_sw_resources:
	up_पढ़ो(&device_offload_lock);
	tls_sw_मुक्त_resources_rx(sk);
	करोwn_पढ़ो(&device_offload_lock);
release_ctx:
	ctx->priv_ctx_rx = शून्य;
release_lock:
	up_पढ़ो(&device_offload_lock);
release_netdev:
	dev_put(netdev);
	वापस rc;
पूर्ण

व्योम tls_device_offload_cleanup_rx(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *tls_ctx = tls_get_ctx(sk);
	काष्ठा net_device *netdev;

	करोwn_पढ़ो(&device_offload_lock);
	netdev = tls_ctx->netdev;
	अगर (!netdev)
		जाओ out;

	netdev->tlsdev_ops->tls_dev_del(netdev, tls_ctx,
					TLS_OFFLOAD_CTX_सूची_RX);

	अगर (tls_ctx->tx_conf != TLS_HW) अणु
		dev_put(netdev);
		tls_ctx->netdev = शून्य;
	पूर्ण अन्यथा अणु
		set_bit(TLS_RX_DEV_CLOSED, &tls_ctx->flags);
	पूर्ण
out:
	up_पढ़ो(&device_offload_lock);
	tls_sw_release_resources_rx(sk);
पूर्ण

अटल पूर्णांक tls_device_करोwn(काष्ठा net_device *netdev)
अणु
	काष्ठा tls_context *ctx, *पंचांगp;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	/* Request a ग_लिखो lock to block new offload attempts */
	करोwn_ग_लिखो(&device_offload_lock);

	spin_lock_irqsave(&tls_device_lock, flags);
	list_क्रम_each_entry_safe(ctx, पंचांगp, &tls_device_list, list) अणु
		अगर (ctx->netdev != netdev ||
		    !refcount_inc_not_zero(&ctx->refcount))
			जारी;

		list_move(&ctx->list, &list);
	पूर्ण
	spin_unlock_irqrestore(&tls_device_lock, flags);

	list_क्रम_each_entry_safe(ctx, पंचांगp, &list, list)	अणु
		/* Stop offloaded TX and चयन to the fallback.
		 * tls_is_sk_tx_device_offloaded will वापस false.
		 */
		WRITE_ONCE(ctx->sk->sk_validate_xmit_skb, tls_validate_xmit_skb_sw);

		/* Stop the RX and TX resync.
		 * tls_dev_resync must not be called after tls_dev_del.
		 */
		WRITE_ONCE(ctx->netdev, शून्य);

		/* Start skipping the RX resync logic completely. */
		set_bit(TLS_RX_DEV_DEGRADED, &ctx->flags);

		/* Sync with inflight packets. After this poपूर्णांक:
		 * TX: no non-encrypted packets will be passed to the driver.
		 * RX: resync requests from the driver will be ignored.
		 */
		synchronize_net();

		/* Release the offload context on the driver side. */
		अगर (ctx->tx_conf == TLS_HW)
			netdev->tlsdev_ops->tls_dev_del(netdev, ctx,
							TLS_OFFLOAD_CTX_सूची_TX);
		अगर (ctx->rx_conf == TLS_HW &&
		    !test_bit(TLS_RX_DEV_CLOSED, &ctx->flags))
			netdev->tlsdev_ops->tls_dev_del(netdev, ctx,
							TLS_OFFLOAD_CTX_सूची_RX);

		dev_put(netdev);

		/* Move the context to a separate list क्रम two reasons:
		 * 1. When the context is deallocated, list_del is called.
		 * 2. It's no longer an offloaded context, so we don't want to
		 *    run offload-specअगरic code on this context.
		 */
		spin_lock_irqsave(&tls_device_lock, flags);
		list_move_tail(&ctx->list, &tls_device_करोwn_list);
		spin_unlock_irqrestore(&tls_device_lock, flags);

		/* Device contexts क्रम RX and TX will be मुक्तd in on sk_deकाष्ठा
		 * by tls_device_मुक्त_ctx. rx_conf and tx_conf stay in TLS_HW.
		 */
	पूर्ण

	up_ग_लिखो(&device_offload_lock);

	flush_work(&tls_device_gc_work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक tls_dev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			 व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (!dev->tlsdev_ops &&
	    !(dev->features & (NETIF_F_HW_TLS_RX | NETIF_F_HW_TLS_TX)))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
	हाल NETDEV_FEAT_CHANGE:
		अगर (netअगर_is_bond_master(dev))
			वापस NOTIFY_DONE;
		अगर ((dev->features & NETIF_F_HW_TLS_RX) &&
		    !dev->tlsdev_ops->tls_dev_resync)
			वापस NOTIFY_BAD;

		अगर  (dev->tlsdev_ops &&
		     dev->tlsdev_ops->tls_dev_add &&
		     dev->tlsdev_ops->tls_dev_del)
			वापस NOTIFY_DONE;
		अन्यथा
			वापस NOTIFY_BAD;
	हाल NETDEV_DOWN:
		वापस tls_device_करोwn(dev);
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block tls_dev_notअगरier = अणु
	.notअगरier_call	= tls_dev_event,
पूर्ण;

व्योम __init tls_device_init(व्योम)
अणु
	रेजिस्टर_netdevice_notअगरier(&tls_dev_notअगरier);
पूर्ण

व्योम __निकास tls_device_cleanup(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&tls_dev_notअगरier);
	flush_work(&tls_device_gc_work);
	clean_acked_data_flush();
पूर्ण
