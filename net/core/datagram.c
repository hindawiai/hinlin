<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	SUCS NET3:
 *
 *	Generic datagram handling routines. These are generic क्रम all
 *	protocols. Possibly a generic IP version on top of these would
 *	make sense. Not tonight however 8-).
 *	This is used because UDP, RAW, PACKET, DDP, IPX, AX.25 and
 *	NetROM layer all have identical poll code and mostly
 *	identical recvmsg() code. So we share it here. The poll was
 *	shared beक्रमe but buried in udp.c so I moved it.
 *
 *	Authors:	Alan Cox <alan@lxorguk.ukuu.org.uk>. (datagram_poll() from old
 *						     udp.c code)
 *
 *	Fixes:
 *		Alan Cox	:	शून्य वापस from skb_peek_copy()
 *					understood
 *		Alan Cox	:	Rewrote skb_पढ़ो_datagram to aव्योम the
 *					skb_peek_copy stuff.
 *		Alan Cox	:	Added support क्रम SOCK_SEQPACKET.
 *					IPX can no दीर्घer use the SO_TYPE hack
 *					but AX.25 now works right, and SPX is
 *					feasible.
 *		Alan Cox	:	Fixed ग_लिखो poll of non IP protocol
 *					crash.
 *		Florian  La Roche:	Changed क्रम my new skbuff handling.
 *		Darryl Miles	:	Fixed non-blocking SOCK_SEQPACKET.
 *		Linus Torvalds	:	BSD semantic fixes.
 *		Alan Cox	:	Datagram iovec handling
 *		Darryl Miles	:	Fixed non-blocking SOCK_STREAM.
 *		Alan Cox	:	POSIXisms
 *		Pete Wyckoff    :       Unconnected accept() fix.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/poll.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>

#समावेश <net/checksum.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <trace/events/skb.h>
#समावेश <net/busy_poll.h>

#समावेश "datagram.h"

/*
 *	Is a socket 'connection oriented' ?
 */
अटल अंतरभूत पूर्णांक connection_based(काष्ठा sock *sk)
अणु
	वापस sk->sk_type == SOCK_SEQPACKET || sk->sk_type == SOCK_STREAM;
पूर्ण

अटल पूर्णांक receiver_wake_function(रुको_queue_entry_t *रुको, अचिन्हित पूर्णांक mode, पूर्णांक sync,
				  व्योम *key)
अणु
	/*
	 * Aव्योम a wakeup अगर event not पूर्णांकeresting क्रम us
	 */
	अगर (key && !(key_to_poll(key) & (EPOLLIN | EPOLLERR)))
		वापस 0;
	वापस स्वतःहटाओ_wake_function(रुको, mode, sync, key);
पूर्ण
/*
 * Wait क्रम the last received packet to be dअगरferent from skb
 */
पूर्णांक __skb_रुको_क्रम_more_packets(काष्ठा sock *sk, काष्ठा sk_buff_head *queue,
				पूर्णांक *err, दीर्घ *समयo_p,
				स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक error;
	DEFINE_WAIT_FUNC(रुको, receiver_wake_function);

	prepare_to_रुको_exclusive(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);

	/* Socket errors? */
	error = sock_error(sk);
	अगर (error)
		जाओ out_err;

	अगर (READ_ONCE(queue->prev) != skb)
		जाओ out;

	/* Socket shut करोwn? */
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		जाओ out_noerr;

	/* Sequenced packets can come disconnected.
	 * If so we report the problem
	 */
	error = -ENOTCONN;
	अगर (connection_based(sk) &&
	    !(sk->sk_state == TCP_ESTABLISHED || sk->sk_state == TCP_LISTEN))
		जाओ out_err;

	/* handle संकेतs */
	अगर (संकेत_pending(current))
		जाओ पूर्णांकerrupted;

	error = 0;
	*समयo_p = schedule_समयout(*समयo_p);
out:
	finish_रुको(sk_sleep(sk), &रुको);
	वापस error;
पूर्णांकerrupted:
	error = sock_पूर्णांकr_त्रुटि_सं(*समयo_p);
out_err:
	*err = error;
	जाओ out;
out_noerr:
	*err = 0;
	error = 1;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(__skb_रुको_क्रम_more_packets);

अटल काष्ठा sk_buff *skb_set_peeked(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *nskb;

	अगर (skb->peeked)
		वापस skb;

	/* We have to unshare an skb beक्रमe modअगरying it. */
	अगर (!skb_shared(skb))
		जाओ करोne;

	nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (!nskb)
		वापस ERR_PTR(-ENOMEM);

	skb->prev->next = nskb;
	skb->next->prev = nskb;
	nskb->prev = skb->prev;
	nskb->next = skb->next;

	consume_skb(skb);
	skb = nskb;

करोne:
	skb->peeked = 1;

	वापस skb;
पूर्ण

काष्ठा sk_buff *__skb_try_recv_from_queue(काष्ठा sock *sk,
					  काष्ठा sk_buff_head *queue,
					  अचिन्हित पूर्णांक flags,
					  पूर्णांक *off, पूर्णांक *err,
					  काष्ठा sk_buff **last)
अणु
	bool peek_at_off = false;
	काष्ठा sk_buff *skb;
	पूर्णांक _off = 0;

	अगर (unlikely(flags & MSG_PEEK && *off >= 0)) अणु
		peek_at_off = true;
		_off = *off;
	पूर्ण

	*last = queue->prev;
	skb_queue_walk(queue, skb) अणु
		अगर (flags & MSG_PEEK) अणु
			अगर (peek_at_off && _off >= skb->len &&
			    (_off || skb->peeked)) अणु
				_off -= skb->len;
				जारी;
			पूर्ण
			अगर (!skb->len) अणु
				skb = skb_set_peeked(skb);
				अगर (IS_ERR(skb)) अणु
					*err = PTR_ERR(skb);
					वापस शून्य;
				पूर्ण
			पूर्ण
			refcount_inc(&skb->users);
		पूर्ण अन्यथा अणु
			__skb_unlink(skb, queue);
		पूर्ण
		*off = _off;
		वापस skb;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 *	__skb_try_recv_datagram - Receive a datagram skbuff
 *	@sk: socket
 *	@queue: socket queue from which to receive
 *	@flags: MSG\_ flags
 *	@off: an offset in bytes to peek skb from. Returns an offset
 *	      within an skb where data actually starts
 *	@err: error code वापसed
 *	@last: set to last peeked message to inक्रमm the रुको function
 *	       what to look क्रम when peeking
 *
 *	Get a datagram skbuff, understands the peeking, nonblocking wakeups
 *	and possible races. This replaces identical code in packet, raw and
 *	udp, as well as the IPX AX.25 and Appletalk. It also finally fixes
 *	the दीर्घ standing peek and पढ़ो race क्रम datagram sockets. If you
 *	alter this routine remember it must be re-entrant.
 *
 *	This function will lock the socket अगर a skb is वापसed, so
 *	the caller needs to unlock the socket in that हाल (usually by
 *	calling skb_मुक्त_datagram). Returns शून्य with @err set to
 *	-EAGAIN अगर no data was available or to some other value अगर an
 *	error was detected.
 *
 *	* It करोes not lock socket since today. This function is
 *	* मुक्त of race conditions. This measure should/can improve
 *	* signअगरicantly datagram socket latencies at high loads,
 *	* when data copying to user space takes lots of समय.
 *	* (BTW I've just समाप्तed the last cli() in IP/IPv6/core/netlink/packet
 *	*  8) Great win.)
 *	*			                    --ANK (980729)
 *
 *	The order of the tests when we find no data रुकोing are specअगरied
 *	quite explicitly by POSIX 1003.1g, करोn't change them without having
 *	the standard around please.
 */
काष्ठा sk_buff *__skb_try_recv_datagram(काष्ठा sock *sk,
					काष्ठा sk_buff_head *queue,
					अचिन्हित पूर्णांक flags, पूर्णांक *off, पूर्णांक *err,
					काष्ठा sk_buff **last)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ cpu_flags;
	/*
	 * Caller is allowed not to check sk->sk_err beक्रमe skb_recv_datagram()
	 */
	पूर्णांक error = sock_error(sk);

	अगर (error)
		जाओ no_packet;

	करो अणु
		/* Again only user level code calls this function, so nothing
		 * पूर्णांकerrupt level will suddenly eat the receive_queue.
		 *
		 * Look at current nfs client by the way...
		 * However, this function was correct in any हाल. 8)
		 */
		spin_lock_irqsave(&queue->lock, cpu_flags);
		skb = __skb_try_recv_from_queue(sk, queue, flags, off, &error,
						last);
		spin_unlock_irqrestore(&queue->lock, cpu_flags);
		अगर (error)
			जाओ no_packet;
		अगर (skb)
			वापस skb;

		अगर (!sk_can_busy_loop(sk))
			अवरोध;

		sk_busy_loop(sk, flags & MSG_DONTWAIT);
	पूर्ण जबतक (READ_ONCE(queue->prev) != *last);

	error = -EAGAIN;

no_packet:
	*err = error;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__skb_try_recv_datagram);

काष्ठा sk_buff *__skb_recv_datagram(काष्ठा sock *sk,
				    काष्ठा sk_buff_head *sk_queue,
				    अचिन्हित पूर्णांक flags, पूर्णांक *off, पूर्णांक *err)
अणु
	काष्ठा sk_buff *skb, *last;
	दीर्घ समयo;

	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);

	करो अणु
		skb = __skb_try_recv_datagram(sk, sk_queue, flags, off, err,
					      &last);
		अगर (skb)
			वापस skb;

		अगर (*err != -EAGAIN)
			अवरोध;
	पूर्ण जबतक (समयo &&
		 !__skb_रुको_क्रम_more_packets(sk, sk_queue, err,
					      &समयo, last));

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__skb_recv_datagram);

काष्ठा sk_buff *skb_recv_datagram(काष्ठा sock *sk, अचिन्हित पूर्णांक flags,
				  पूर्णांक noblock, पूर्णांक *err)
अणु
	पूर्णांक off = 0;

	वापस __skb_recv_datagram(sk, &sk->sk_receive_queue,
				   flags | (noblock ? MSG_DONTWAIT : 0),
				   &off, err);
पूर्ण
EXPORT_SYMBOL(skb_recv_datagram);

व्योम skb_मुक्त_datagram(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	consume_skb(skb);
	sk_mem_reclaim_partial(sk);
पूर्ण
EXPORT_SYMBOL(skb_मुक्त_datagram);

व्योम __skb_मुक्त_datagram_locked(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	bool slow;

	अगर (!skb_unref(skb)) अणु
		sk_peek_offset_bwd(sk, len);
		वापस;
	पूर्ण

	slow = lock_sock_fast(sk);
	sk_peek_offset_bwd(sk, len);
	skb_orphan(skb);
	sk_mem_reclaim_partial(sk);
	unlock_sock_fast(sk, slow);

	/* skb is now orphaned, can be मुक्तd outside of locked section */
	__kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(__skb_मुक्त_datagram_locked);

पूर्णांक __sk_queue_drop_skb(काष्ठा sock *sk, काष्ठा sk_buff_head *sk_queue,
			काष्ठा sk_buff *skb, अचिन्हित पूर्णांक flags,
			व्योम (*deकाष्ठाor)(काष्ठा sock *sk,
					   काष्ठा sk_buff *skb))
अणु
	पूर्णांक err = 0;

	अगर (flags & MSG_PEEK) अणु
		err = -ENOENT;
		spin_lock_bh(&sk_queue->lock);
		अगर (skb->next) अणु
			__skb_unlink(skb, sk_queue);
			refcount_dec(&skb->users);
			अगर (deकाष्ठाor)
				deकाष्ठाor(sk, skb);
			err = 0;
		पूर्ण
		spin_unlock_bh(&sk_queue->lock);
	पूर्ण

	atomic_inc(&sk->sk_drops);
	वापस err;
पूर्ण
EXPORT_SYMBOL(__sk_queue_drop_skb);

/**
 *	skb_समाप्त_datagram - Free a datagram skbuff क्रमcibly
 *	@sk: socket
 *	@skb: datagram skbuff
 *	@flags: MSG\_ flags
 *
 *	This function मुक्तs a datagram skbuff that was received by
 *	skb_recv_datagram.  The flags argument must match the one
 *	used क्रम skb_recv_datagram.
 *
 *	If the MSG_PEEK flag is set, and the packet is still on the
 *	receive queue of the socket, it will be taken off the queue
 *	beक्रमe it is मुक्तd.
 *
 *	This function currently only disables BH when acquiring the
 *	sk_receive_queue lock.  Thereक्रमe it must not be used in a
 *	context where that lock is acquired in an IRQ context.
 *
 *	It वापसs 0 अगर the packet was हटाओd by us.
 */

पूर्णांक skb_समाप्त_datagram(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err = __sk_queue_drop_skb(sk, &sk->sk_receive_queue, skb, flags,
				      शून्य);

	kमुक्त_skb(skb);
	sk_mem_reclaim_partial(sk);
	वापस err;
पूर्ण
EXPORT_SYMBOL(skb_समाप्त_datagram);

INसूचीECT_CALLABLE_DECLARE(अटल माप_प्रकार simple_copy_to_iter(स्थिर व्योम *addr,
						माप_प्रकार bytes,
						व्योम *data __always_unused,
						काष्ठा iov_iter *i));

अटल पूर्णांक __skb_datagram_iter(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			       काष्ठा iov_iter *to, पूर्णांक len, bool fault_लघु,
			       माप_प्रकार (*cb)(स्थिर व्योम *, माप_प्रकार, व्योम *,
					    काष्ठा iov_iter *), व्योम *data)
अणु
	पूर्णांक start = skb_headlen(skb);
	पूर्णांक i, copy = start - offset, start_off = offset, n;
	काष्ठा sk_buff *frag_iter;

	/* Copy header. */
	अगर (copy > 0) अणु
		अगर (copy > len)
			copy = len;
		n = INसूचीECT_CALL_1(cb, simple_copy_to_iter,
				    skb->data + offset, copy, data, to);
		offset += n;
		अगर (n != copy)
			जाओ लघु_copy;
		अगर ((len -= copy) == 0)
			वापस 0;
	पूर्ण

	/* Copy paged appendix. Hmm... why करोes this look so complicated? */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(frag);
		अगर ((copy = end - offset) > 0) अणु
			काष्ठा page *page = skb_frag_page(frag);
			u8 *vaddr = kmap(page);

			अगर (copy > len)
				copy = len;
			n = INसूचीECT_CALL_1(cb, simple_copy_to_iter,
					vaddr + skb_frag_off(frag) + offset - start,
					copy, data, to);
			kunmap(page);
			offset += n;
			अगर (n != copy)
				जाओ लघु_copy;
			अगर (!(len -= copy))
				वापस 0;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			अगर (__skb_datagram_iter(frag_iter, offset - start,
						to, copy, fault_लघु, cb, data))
				जाओ fault;
			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण
	अगर (!len)
		वापस 0;

	/* This is not really a user copy fault, but rather someone
	 * gave us a bogus length on the skb.  We should probably
	 * prपूर्णांक a warning here as it may indicate a kernel bug.
	 */

fault:
	iov_iter_revert(to, offset - start_off);
	वापस -EFAULT;

लघु_copy:
	अगर (fault_लघु || iov_iter_count(to))
		जाओ fault;

	वापस 0;
पूर्ण

/**
 *	skb_copy_and_hash_datagram_iter - Copy datagram to an iovec iterator
 *          and update a hash.
 *	@skb: buffer to copy
 *	@offset: offset in the buffer to start copying from
 *	@to: iovec iterator to copy to
 *	@len: amount of data to copy from buffer to iovec
 *      @hash: hash request to update
 */
पूर्णांक skb_copy_and_hash_datagram_iter(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			   काष्ठा iov_iter *to, पूर्णांक len,
			   काष्ठा ahash_request *hash)
अणु
	वापस __skb_datagram_iter(skb, offset, to, len, true,
			hash_and_copy_to_iter, hash);
पूर्ण
EXPORT_SYMBOL(skb_copy_and_hash_datagram_iter);

अटल माप_प्रकार simple_copy_to_iter(स्थिर व्योम *addr, माप_प्रकार bytes,
		व्योम *data __always_unused, काष्ठा iov_iter *i)
अणु
	वापस copy_to_iter(addr, bytes, i);
पूर्ण

/**
 *	skb_copy_datagram_iter - Copy a datagram to an iovec iterator.
 *	@skb: buffer to copy
 *	@offset: offset in the buffer to start copying from
 *	@to: iovec iterator to copy to
 *	@len: amount of data to copy from buffer to iovec
 */
पूर्णांक skb_copy_datagram_iter(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
			   काष्ठा iov_iter *to, पूर्णांक len)
अणु
	trace_skb_copy_datagram_iovec(skb, len);
	वापस __skb_datagram_iter(skb, offset, to, len, false,
			simple_copy_to_iter, शून्य);
पूर्ण
EXPORT_SYMBOL(skb_copy_datagram_iter);

/**
 *	skb_copy_datagram_from_iter - Copy a datagram from an iov_iter.
 *	@skb: buffer to copy
 *	@offset: offset in the buffer to start copying to
 *	@from: the copy source
 *	@len: amount of data to copy to buffer from iovec
 *
 *	Returns 0 or -EFAULT.
 */
पूर्णांक skb_copy_datagram_from_iter(काष्ठा sk_buff *skb, पूर्णांक offset,
				 काष्ठा iov_iter *from,
				 पूर्णांक len)
अणु
	पूर्णांक start = skb_headlen(skb);
	पूर्णांक i, copy = start - offset;
	काष्ठा sk_buff *frag_iter;

	/* Copy header. */
	अगर (copy > 0) अणु
		अगर (copy > len)
			copy = len;
		अगर (copy_from_iter(skb->data + offset, copy, from) != copy)
			जाओ fault;
		अगर ((len -= copy) == 0)
			वापस 0;
		offset += copy;
	पूर्ण

	/* Copy paged appendix. Hmm... why करोes this look so complicated? */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		पूर्णांक end;
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		WARN_ON(start > offset + len);

		end = start + skb_frag_size(frag);
		अगर ((copy = end - offset) > 0) अणु
			माप_प्रकार copied;

			अगर (copy > len)
				copy = len;
			copied = copy_page_from_iter(skb_frag_page(frag),
					  skb_frag_off(frag) + offset - start,
					  copy, from);
			अगर (copied != copy)
				जाओ fault;

			अगर (!(len -= copy))
				वापस 0;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण

	skb_walk_frags(skb, frag_iter) अणु
		पूर्णांक end;

		WARN_ON(start > offset + len);

		end = start + frag_iter->len;
		अगर ((copy = end - offset) > 0) अणु
			अगर (copy > len)
				copy = len;
			अगर (skb_copy_datagram_from_iter(frag_iter,
							offset - start,
							from, copy))
				जाओ fault;
			अगर ((len -= copy) == 0)
				वापस 0;
			offset += copy;
		पूर्ण
		start = end;
	पूर्ण
	अगर (!len)
		वापस 0;

fault:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(skb_copy_datagram_from_iter);

पूर्णांक __zerocopy_sg_from_iter(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा iov_iter *from, माप_प्रकार length)
अणु
	पूर्णांक frag = skb_shinfo(skb)->nr_frags;

	जबतक (length && iov_iter_count(from)) अणु
		काष्ठा page *pages[MAX_SKB_FRAGS];
		काष्ठा page *last_head = शून्य;
		माप_प्रकार start;
		sमाप_प्रकार copied;
		अचिन्हित दीर्घ truesize;
		पूर्णांक refs, n = 0;

		अगर (frag == MAX_SKB_FRAGS)
			वापस -EMSGSIZE;

		copied = iov_iter_get_pages(from, pages, length,
					    MAX_SKB_FRAGS - frag, &start);
		अगर (copied < 0)
			वापस -EFAULT;

		iov_iter_advance(from, copied);
		length -= copied;

		truesize = PAGE_ALIGN(copied + start);
		skb->data_len += copied;
		skb->len += copied;
		skb->truesize += truesize;
		अगर (sk && sk->sk_type == SOCK_STREAM) अणु
			sk_wmem_queued_add(sk, truesize);
			sk_mem_अक्षरge(sk, truesize);
		पूर्ण अन्यथा अणु
			refcount_add(truesize, &skb->sk->sk_wmem_alloc);
		पूर्ण
		क्रम (refs = 0; copied != 0; start = 0) अणु
			पूर्णांक size = min_t(पूर्णांक, copied, PAGE_SIZE - start);
			काष्ठा page *head = compound_head(pages[n]);

			start += (pages[n] - head) << PAGE_SHIFT;
			copied -= size;
			n++;
			अगर (frag) अणु
				skb_frag_t *last = &skb_shinfo(skb)->frags[frag - 1];

				अगर (head == skb_frag_page(last) &&
				    start == skb_frag_off(last) + skb_frag_size(last)) अणु
					skb_frag_size_add(last, size);
					/* We combined this page, we need to release
					 * a reference. Since compound pages refcount
					 * is shared among many pages, batch the refcount
					 * adjusपंचांगents to limit false sharing.
					 */
					last_head = head;
					refs++;
					जारी;
				पूर्ण
			पूर्ण
			अगर (refs) अणु
				page_ref_sub(last_head, refs);
				refs = 0;
			पूर्ण
			skb_fill_page_desc(skb, frag++, head, start, size);
		पूर्ण
		अगर (refs)
			page_ref_sub(last_head, refs);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__zerocopy_sg_from_iter);

/**
 *	zerocopy_sg_from_iter - Build a zerocopy datagram from an iov_iter
 *	@skb: buffer to copy
 *	@from: the source to copy from
 *
 *	The function will first copy up to headlen, and then pin the userspace
 *	pages and build frags through them.
 *
 *	Returns 0, -EFAULT or -EMSGSIZE.
 */
पूर्णांक zerocopy_sg_from_iter(काष्ठा sk_buff *skb, काष्ठा iov_iter *from)
अणु
	पूर्णांक copy = min_t(पूर्णांक, skb_headlen(skb), iov_iter_count(from));

	/* copy up to skb headlen */
	अगर (skb_copy_datagram_from_iter(skb, 0, from, copy))
		वापस -EFAULT;

	वापस __zerocopy_sg_from_iter(शून्य, skb, from, ~0U);
पूर्ण
EXPORT_SYMBOL(zerocopy_sg_from_iter);

/**
 *	skb_copy_and_csum_datagram - Copy datagram to an iovec iterator
 *          and update a checksum.
 *	@skb: buffer to copy
 *	@offset: offset in the buffer to start copying from
 *	@to: iovec iterator to copy to
 *	@len: amount of data to copy from buffer to iovec
 *      @csump: checksum poपूर्णांकer
 */
अटल पूर्णांक skb_copy_and_csum_datagram(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset,
				      काष्ठा iov_iter *to, पूर्णांक len,
				      __wsum *csump)
अणु
	काष्ठा csum_state csdata = अणु .csum = *csump पूर्ण;
	पूर्णांक ret;

	ret = __skb_datagram_iter(skb, offset, to, len, true,
				  csum_and_copy_to_iter, &csdata);
	अगर (ret)
		वापस ret;

	*csump = csdata.csum;
	वापस 0;
पूर्ण

/**
 *	skb_copy_and_csum_datagram_msg - Copy and checksum skb to user iovec.
 *	@skb: skbuff
 *	@hlen: hardware length
 *	@msg: destination
 *
 *	Caller _must_ check that skb will fit to this iovec.
 *
 *	Returns: 0       - success.
 *		 -EINVAL - checksum failure.
 *		 -EFAULT - fault during copy.
 */
पूर्णांक skb_copy_and_csum_datagram_msg(काष्ठा sk_buff *skb,
				   पूर्णांक hlen, काष्ठा msghdr *msg)
अणु
	__wsum csum;
	पूर्णांक chunk = skb->len - hlen;

	अगर (!chunk)
		वापस 0;

	अगर (msg_data_left(msg) < chunk) अणु
		अगर (__skb_checksum_complete(skb))
			वापस -EINVAL;
		अगर (skb_copy_datagram_msg(skb, hlen, msg, chunk))
			जाओ fault;
	पूर्ण अन्यथा अणु
		csum = csum_partial(skb->data, hlen, skb->csum);
		अगर (skb_copy_and_csum_datagram(skb, hlen, &msg->msg_iter,
					       chunk, &csum))
			जाओ fault;

		अगर (csum_fold(csum)) अणु
			iov_iter_revert(&msg->msg_iter, chunk);
			वापस -EINVAL;
		पूर्ण

		अगर (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
		    !skb->csum_complete_sw)
			netdev_rx_csum_fault(शून्य, skb);
	पूर्ण
	वापस 0;
fault:
	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL(skb_copy_and_csum_datagram_msg);

/**
 * 	datagram_poll - generic datagram poll
 *	@file: file काष्ठा
 *	@sock: socket
 *	@रुको: poll table
 *
 *	Datagram poll: Again totally generic. This also handles
 *	sequenced packet sockets providing the socket receive queue
 *	is only ever holding data पढ़ोy to receive.
 *
 *	Note: when you *करोn't* use this routine क्रम this protocol,
 *	and you use a dअगरferent ग_लिखो policy from sock_ग_लिखोable()
 *	then please supply your own ग_लिखो_space callback.
 */
__poll_t datagram_poll(काष्ठा file *file, काष्ठा socket *sock,
			   poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	/* exceptional events? */
	अगर (sk->sk_err || !skb_queue_empty_lockless(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP | EPOLLIN | EPOLLRDNORM;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	/* पढ़ोable? */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Connection-based need to check क्रम termination and startup */
	अगर (connection_based(sk)) अणु
		अगर (sk->sk_state == TCP_CLOSE)
			mask |= EPOLLHUP;
		/* connection hasn't started yet? */
		अगर (sk->sk_state == TCP_SYN_SENT)
			वापस mask;
	पूर्ण

	/* writable? */
	अगर (sock_ग_लिखोable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
	अन्यथा
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	वापस mask;
पूर्ण
EXPORT_SYMBOL(datagram_poll);
