<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/socklib.c
 *
 * Common socket helper routines क्रम RPC client and server
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/udp.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/export.h>

#समावेश "socklib.h"

/*
 * Helper काष्ठाure क्रम copying from an sk_buff.
 */
काष्ठा xdr_skb_पढ़ोer अणु
	काष्ठा sk_buff	*skb;
	अचिन्हित पूर्णांक	offset;
	माप_प्रकार		count;
	__wsum		csum;
पूर्ण;

प्रकार माप_प्रकार (*xdr_skb_पढ़ो_actor)(काष्ठा xdr_skb_पढ़ोer *desc, व्योम *to,
				     माप_प्रकार len);

/**
 * xdr_skb_पढ़ो_bits - copy some data bits from skb to पूर्णांकernal buffer
 * @desc: sk_buff copy helper
 * @to: copy destination
 * @len: number of bytes to copy
 *
 * Possibly called several बार to iterate over an sk_buff and copy
 * data out of it.
 */
अटल माप_प्रकार
xdr_skb_पढ़ो_bits(काष्ठा xdr_skb_पढ़ोer *desc, व्योम *to, माप_प्रकार len)
अणु
	अगर (len > desc->count)
		len = desc->count;
	अगर (unlikely(skb_copy_bits(desc->skb, desc->offset, to, len)))
		वापस 0;
	desc->count -= len;
	desc->offset += len;
	वापस len;
पूर्ण

/**
 * xdr_skb_पढ़ो_and_csum_bits - copy and checksum from skb to buffer
 * @desc: sk_buff copy helper
 * @to: copy destination
 * @len: number of bytes to copy
 *
 * Same as skb_पढ़ो_bits, but calculate a checksum at the same समय.
 */
अटल माप_प्रकार xdr_skb_पढ़ो_and_csum_bits(काष्ठा xdr_skb_पढ़ोer *desc, व्योम *to, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक pos;
	__wsum csum2;

	अगर (len > desc->count)
		len = desc->count;
	pos = desc->offset;
	csum2 = skb_copy_and_csum_bits(desc->skb, pos, to, len);
	desc->csum = csum_block_add(desc->csum, csum2, pos);
	desc->count -= len;
	desc->offset += len;
	वापस len;
पूर्ण

/**
 * xdr_partial_copy_from_skb - copy data out of an skb
 * @xdr: target XDR buffer
 * @base: starting offset
 * @desc: sk_buff copy helper
 * @copy_actor: भव method क्रम copying data
 *
 */
अटल sमाप_प्रकार
xdr_partial_copy_from_skb(काष्ठा xdr_buf *xdr, अचिन्हित पूर्णांक base, काष्ठा xdr_skb_पढ़ोer *desc, xdr_skb_पढ़ो_actor copy_actor)
अणु
	काष्ठा page	**ppage = xdr->pages;
	अचिन्हित पूर्णांक	len, pglen = xdr->page_len;
	sमाप_प्रकार		copied = 0;
	माप_प्रकार		ret;

	len = xdr->head[0].iov_len;
	अगर (base < len) अणु
		len -= base;
		ret = copy_actor(desc, (अक्षर *)xdr->head[0].iov_base + base, len);
		copied += ret;
		अगर (ret != len || !desc->count)
			जाओ out;
		base = 0;
	पूर्ण अन्यथा
		base -= len;

	अगर (unlikely(pglen == 0))
		जाओ copy_tail;
	अगर (unlikely(base >= pglen)) अणु
		base -= pglen;
		जाओ copy_tail;
	पूर्ण
	अगर (base || xdr->page_base) अणु
		pglen -= base;
		base += xdr->page_base;
		ppage += base >> PAGE_SHIFT;
		base &= ~PAGE_MASK;
	पूर्ण
	करो अणु
		अक्षर *kaddr;

		/* ACL likes to be lazy in allocating pages - ACLs
		 * are small by शेष but can get huge. */
		अगर ((xdr->flags & XDRBUF_SPARSE_PAGES) && *ppage == शून्य) अणु
			*ppage = alloc_page(GFP_NOWAIT | __GFP_NOWARN);
			अगर (unlikely(*ppage == शून्य)) अणु
				अगर (copied == 0)
					copied = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण

		len = PAGE_SIZE;
		kaddr = kmap_atomic(*ppage);
		अगर (base) अणु
			len -= base;
			अगर (pglen < len)
				len = pglen;
			ret = copy_actor(desc, kaddr + base, len);
			base = 0;
		पूर्ण अन्यथा अणु
			अगर (pglen < len)
				len = pglen;
			ret = copy_actor(desc, kaddr, len);
		पूर्ण
		flush_dcache_page(*ppage);
		kunmap_atomic(kaddr);
		copied += ret;
		अगर (ret != len || !desc->count)
			जाओ out;
		ppage++;
	पूर्ण जबतक ((pglen -= len) != 0);
copy_tail:
	len = xdr->tail[0].iov_len;
	अगर (base < len)
		copied += copy_actor(desc, (अक्षर *)xdr->tail[0].iov_base + base, len - base);
out:
	वापस copied;
पूर्ण

/**
 * csum_partial_copy_to_xdr - checksum and copy data
 * @xdr: target XDR buffer
 * @skb: source skb
 *
 * We have set things up such that we perक्रमm the checksum of the UDP
 * packet in parallel with the copies पूर्णांकo the RPC client iovec.  -DaveM
 */
पूर्णांक csum_partial_copy_to_xdr(काष्ठा xdr_buf *xdr, काष्ठा sk_buff *skb)
अणु
	काष्ठा xdr_skb_पढ़ोer	desc;

	desc.skb = skb;
	desc.offset = 0;
	desc.count = skb->len - desc.offset;

	अगर (skb_csum_unnecessary(skb))
		जाओ no_checksum;

	desc.csum = csum_partial(skb->data, desc.offset, skb->csum);
	अगर (xdr_partial_copy_from_skb(xdr, 0, &desc, xdr_skb_पढ़ो_and_csum_bits) < 0)
		वापस -1;
	अगर (desc.offset != skb->len) अणु
		__wsum csum2;
		csum2 = skb_checksum(skb, desc.offset, skb->len - desc.offset, 0);
		desc.csum = csum_block_add(desc.csum, csum2, desc.offset);
	पूर्ण
	अगर (desc.count)
		वापस -1;
	अगर (csum_fold(desc.csum))
		वापस -1;
	अगर (unlikely(skb->ip_summed == CHECKSUM_COMPLETE) &&
	    !skb->csum_complete_sw)
		netdev_rx_csum_fault(skb->dev, skb);
	वापस 0;
no_checksum:
	अगर (xdr_partial_copy_from_skb(xdr, 0, &desc, xdr_skb_पढ़ो_bits) < 0)
		वापस -1;
	अगर (desc.count)
		वापस -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(csum_partial_copy_to_xdr);

अटल अंतरभूत पूर्णांक xprt_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार seek)
अणु
	अगर (seek)
		iov_iter_advance(&msg->msg_iter, seek);
	वापस sock_sendmsg(sock, msg);
पूर्ण

अटल पूर्णांक xprt_send_kvec(काष्ठा socket *sock, काष्ठा msghdr *msg,
			  काष्ठा kvec *vec, माप_प्रकार seek)
अणु
	iov_iter_kvec(&msg->msg_iter, WRITE, vec, 1, vec->iov_len);
	वापस xprt_sendmsg(sock, msg, seek);
पूर्ण

अटल पूर्णांक xprt_send_pagedata(काष्ठा socket *sock, काष्ठा msghdr *msg,
			      काष्ठा xdr_buf *xdr, माप_प्रकार base)
अणु
	पूर्णांक err;

	err = xdr_alloc_bvec(xdr, GFP_KERNEL);
	अगर (err < 0)
		वापस err;

	iov_iter_bvec(&msg->msg_iter, WRITE, xdr->bvec, xdr_buf_pagecount(xdr),
		      xdr->page_len + xdr->page_base);
	वापस xprt_sendmsg(sock, msg, base + xdr->page_base);
पूर्ण

/* Common हाल:
 *  - stream transport
 *  - sending from byte 0 of the message
 *  - the message is wholly contained in @xdr's head iovec
 */
अटल पूर्णांक xprt_send_rm_and_kvec(काष्ठा socket *sock, काष्ठा msghdr *msg,
				 rpc_fraghdr marker, काष्ठा kvec *vec,
				 माप_प्रकार base)
अणु
	काष्ठा kvec iov[2] = अणु
		[0] = अणु
			.iov_base	= &marker,
			.iov_len	= माप(marker)
		पूर्ण,
		[1] = *vec,
	पूर्ण;
	माप_प्रकार len = iov[0].iov_len + iov[1].iov_len;

	iov_iter_kvec(&msg->msg_iter, WRITE, iov, 2, len);
	वापस xprt_sendmsg(sock, msg, base);
पूर्ण

/**
 * xprt_sock_sendmsg - ग_लिखो an xdr_buf directly to a socket
 * @sock: खोलो socket to send on
 * @msg: socket message metadata
 * @xdr: xdr_buf containing this request
 * @base: starting position in the buffer
 * @marker: stream record marker field
 * @sent_p: वापस the total number of bytes successfully queued क्रम sending
 *
 * Return values:
 *   On success, वापसs zero and fills in @sent_p.
 *   %-ENOTSOCK अगर  @sock is not a काष्ठा socket.
 */
पूर्णांक xprt_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
		      काष्ठा xdr_buf *xdr, अचिन्हित पूर्णांक base,
		      rpc_fraghdr marker, अचिन्हित पूर्णांक *sent_p)
अणु
	अचिन्हित पूर्णांक rmsize = marker ? माप(marker) : 0;
	अचिन्हित पूर्णांक reमुख्यder = rmsize + xdr->len - base;
	अचिन्हित पूर्णांक want;
	पूर्णांक err = 0;

	*sent_p = 0;

	अगर (unlikely(!sock))
		वापस -ENOTSOCK;

	msg->msg_flags |= MSG_MORE;
	want = xdr->head[0].iov_len + rmsize;
	अगर (base < want) अणु
		अचिन्हित पूर्णांक len = want - base;

		reमुख्यder -= len;
		अगर (reमुख्यder == 0)
			msg->msg_flags &= ~MSG_MORE;
		अगर (rmsize)
			err = xprt_send_rm_and_kvec(sock, msg, marker,
						    &xdr->head[0], base);
		अन्यथा
			err = xprt_send_kvec(sock, msg, &xdr->head[0], base);
		अगर (reमुख्यder == 0 || err != len)
			जाओ out;
		*sent_p += err;
		base = 0;
	पूर्ण अन्यथा अणु
		base -= want;
	पूर्ण

	अगर (base < xdr->page_len) अणु
		अचिन्हित पूर्णांक len = xdr->page_len - base;

		reमुख्यder -= len;
		अगर (reमुख्यder == 0)
			msg->msg_flags &= ~MSG_MORE;
		err = xprt_send_pagedata(sock, msg, xdr, base);
		अगर (reमुख्यder == 0 || err != len)
			जाओ out;
		*sent_p += err;
		base = 0;
	पूर्ण अन्यथा अणु
		base -= xdr->page_len;
	पूर्ण

	अगर (base >= xdr->tail[0].iov_len)
		वापस 0;
	msg->msg_flags &= ~MSG_MORE;
	err = xprt_send_kvec(sock, msg, &xdr->tail[0], base);
out:
	अगर (err > 0) अणु
		*sent_p += err;
		err = 0;
	पूर्ण
	वापस err;
पूर्ण
