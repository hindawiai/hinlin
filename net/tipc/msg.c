<शैली गुरु>
/*
 * net/tipc/msg.c: TIPC message header routines
 *
 * Copyright (c) 2000-2006, 2014-2015, Ericsson AB
 * Copyright (c) 2005, 2010-2011, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <net/sock.h>
#समावेश "core.h"
#समावेश "msg.h"
#समावेश "addr.h"
#समावेश "name_table.h"
#समावेश "crypto.h"

#घोषणा MAX_FORWARD_SIZE 1024
#अगर_घोषित CONFIG_TIPC_CRYPTO
#घोषणा BUF_HEADROOM ALIGN(((LL_MAX_HEADER + 48) + EHDR_MAX_SIZE), 16)
#घोषणा BUF_TAILROOM (TIPC_AES_GCM_TAG_SIZE)
#अन्यथा
#घोषणा BUF_HEADROOM (LL_MAX_HEADER + 48)
#घोषणा BUF_TAILROOM 16
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक align(अचिन्हित पूर्णांक i)
अणु
	वापस (i + 3) & ~3u;
पूर्ण

/**
 * tipc_buf_acquire - creates a TIPC message buffer
 * @size: message size (including TIPC header)
 * @gfp: memory allocation flags
 *
 * Return: a new buffer with data poपूर्णांकers set to the specअगरied size.
 *
 * NOTE:
 * Headroom is reserved to allow prepending of a data link header.
 * There may also be unrequested tailroom present at the buffer's end.
 */
काष्ठा sk_buff *tipc_buf_acquire(u32 size, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;
#अगर_घोषित CONFIG_TIPC_CRYPTO
	अचिन्हित पूर्णांक buf_size = (BUF_HEADROOM + size + BUF_TAILROOM + 3) & ~3u;
#अन्यथा
	अचिन्हित पूर्णांक buf_size = (BUF_HEADROOM + size + 3) & ~3u;
#पूर्ण_अगर

	skb = alloc_skb_fclone(buf_size, gfp);
	अगर (skb) अणु
		skb_reserve(skb, BUF_HEADROOM);
		skb_put(skb, size);
		skb->next = शून्य;
	पूर्ण
	वापस skb;
पूर्ण

व्योम tipc_msg_init(u32 own_node, काष्ठा tipc_msg *m, u32 user, u32 type,
		   u32 hsize, u32 dnode)
अणु
	स_रखो(m, 0, hsize);
	msg_set_version(m);
	msg_set_user(m, user);
	msg_set_hdr_sz(m, hsize);
	msg_set_size(m, hsize);
	msg_set_prevnode(m, own_node);
	msg_set_type(m, type);
	अगर (hsize > SHORT_H_SIZE) अणु
		msg_set_orignode(m, own_node);
		msg_set_destnode(m, dnode);
	पूर्ण
पूर्ण

काष्ठा sk_buff *tipc_msg_create(uपूर्णांक user, uपूर्णांक type,
				uपूर्णांक hdr_sz, uपूर्णांक data_sz, u32 dnode,
				u32 onode, u32 dport, u32 oport, पूर्णांक errcode)
अणु
	काष्ठा tipc_msg *msg;
	काष्ठा sk_buff *buf;

	buf = tipc_buf_acquire(hdr_sz + data_sz, GFP_ATOMIC);
	अगर (unlikely(!buf))
		वापस शून्य;

	msg = buf_msg(buf);
	tipc_msg_init(onode, msg, user, type, hdr_sz, dnode);
	msg_set_size(msg, hdr_sz + data_sz);
	msg_set_origport(msg, oport);
	msg_set_destport(msg, dport);
	msg_set_errcode(msg, errcode);
	वापस buf;
पूर्ण

/* tipc_buf_append(): Append a buffer to the fragment list of another buffer
 * @*headbuf: in:  शून्य क्रम first frag, otherwise value वापसed from prev call
 *            out: set when successful non-complete reassembly, otherwise शून्य
 * @*buf:     in:  the buffer to append. Always defined
 *            out: head buf after successful complete reassembly, otherwise शून्य
 * Returns 1 when reassembly complete, otherwise 0
 */
पूर्णांक tipc_buf_append(काष्ठा sk_buff **headbuf, काष्ठा sk_buff **buf)
अणु
	काष्ठा sk_buff *head = *headbuf;
	काष्ठा sk_buff *frag = *buf;
	काष्ठा sk_buff *tail = शून्य;
	काष्ठा tipc_msg *msg;
	u32 fragid;
	पूर्णांक delta;
	bool headstolen;

	अगर (!frag)
		जाओ err;

	msg = buf_msg(frag);
	fragid = msg_type(msg);
	frag->next = शून्य;
	skb_pull(frag, msg_hdr_sz(msg));

	अगर (fragid == FIRST_FRAGMENT) अणु
		अगर (unlikely(head))
			जाओ err;
		*buf = शून्य;
		अगर (skb_has_frag_list(frag) && __skb_linearize(frag))
			जाओ err;
		frag = skb_unshare(frag, GFP_ATOMIC);
		अगर (unlikely(!frag))
			जाओ err;
		head = *headbuf = frag;
		TIPC_SKB_CB(head)->tail = शून्य;
		वापस 0;
	पूर्ण

	अगर (!head)
		जाओ err;

	अगर (skb_try_coalesce(head, frag, &headstolen, &delta)) अणु
		kमुक्त_skb_partial(frag, headstolen);
	पूर्ण अन्यथा अणु
		tail = TIPC_SKB_CB(head)->tail;
		अगर (!skb_has_frag_list(head))
			skb_shinfo(head)->frag_list = frag;
		अन्यथा
			tail->next = frag;
		head->truesize += frag->truesize;
		head->data_len += frag->len;
		head->len += frag->len;
		TIPC_SKB_CB(head)->tail = frag;
	पूर्ण

	अगर (fragid == LAST_FRAGMENT) अणु
		TIPC_SKB_CB(head)->validated = 0;
		अगर (unlikely(!tipc_msg_validate(&head)))
			जाओ err;
		*buf = head;
		TIPC_SKB_CB(head)->tail = शून्य;
		*headbuf = शून्य;
		वापस 1;
	पूर्ण
	*buf = शून्य;
	वापस 0;
err:
	kमुक्त_skb(*buf);
	kमुक्त_skb(*headbuf);
	*buf = *headbuf = शून्य;
	वापस 0;
पूर्ण

/**
 * tipc_msg_append(): Append data to tail of an existing buffer queue
 * @_hdr: header to be used
 * @m: the data to be appended
 * @mss: max allowable size of buffer
 * @dlen: size of data to be appended
 * @txq: queue to append to
 *
 * Return: the number of 1k blocks appended or त्रुटि_सं value
 */
पूर्णांक tipc_msg_append(काष्ठा tipc_msg *_hdr, काष्ठा msghdr *m, पूर्णांक dlen,
		    पूर्णांक mss, काष्ठा sk_buff_head *txq)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक accounted, total, curr;
	पूर्णांक mlen, cpy, rem = dlen;
	काष्ठा tipc_msg *hdr;

	skb = skb_peek_tail(txq);
	accounted = skb ? msg_blocks(buf_msg(skb)) : 0;
	total = accounted;

	करो अणु
		अगर (!skb || skb->len >= mss) अणु
			skb = tipc_buf_acquire(mss, GFP_KERNEL);
			अगर (unlikely(!skb))
				वापस -ENOMEM;
			skb_orphan(skb);
			skb_trim(skb, MIN_H_SIZE);
			hdr = buf_msg(skb);
			skb_copy_to_linear_data(skb, _hdr, MIN_H_SIZE);
			msg_set_hdr_sz(hdr, MIN_H_SIZE);
			msg_set_size(hdr, MIN_H_SIZE);
			__skb_queue_tail(txq, skb);
			total += 1;
		पूर्ण
		hdr = buf_msg(skb);
		curr = msg_blocks(hdr);
		mlen = msg_size(hdr);
		cpy = min_t(माप_प्रकार, rem, mss - mlen);
		अगर (cpy != copy_from_iter(skb->data + mlen, cpy, &m->msg_iter))
			वापस -EFAULT;
		msg_set_size(hdr, mlen + cpy);
		skb_put(skb, cpy);
		rem -= cpy;
		total += msg_blocks(hdr) - curr;
	पूर्ण जबतक (rem > 0);
	वापस total - accounted;
पूर्ण

/* tipc_msg_validate - validate basic क्रमmat of received message
 *
 * This routine ensures a TIPC message has an acceptable header, and at least
 * as much data as the header indicates it should.  The routine also ensures
 * that the entire message header is stored in the मुख्य fragment of the message
 * buffer, to simplअगरy future access to message header fields.
 *
 * Note: Having extra info present in the message header or data areas is OK.
 * TIPC will ignore the excess, under the assumption that it is optional info
 * पूर्णांकroduced by a later release of the protocol.
 */
bool tipc_msg_validate(काष्ठा sk_buff **_skb)
अणु
	काष्ठा sk_buff *skb = *_skb;
	काष्ठा tipc_msg *hdr;
	पूर्णांक msz, hsz;

	/* Ensure that flow control ratio condition is satisfied */
	अगर (unlikely(skb->truesize / buf_roundup_len(skb) >= 4)) अणु
		skb = skb_copy_expand(skb, BUF_HEADROOM, 0, GFP_ATOMIC);
		अगर (!skb)
			वापस false;
		kमुक्त_skb(*_skb);
		*_skb = skb;
	पूर्ण

	अगर (unlikely(TIPC_SKB_CB(skb)->validated))
		वापस true;

	अगर (unlikely(!pskb_may_pull(skb, MIN_H_SIZE)))
		वापस false;

	hsz = msg_hdr_sz(buf_msg(skb));
	अगर (unlikely(hsz < MIN_H_SIZE) || (hsz > MAX_H_SIZE))
		वापस false;
	अगर (unlikely(!pskb_may_pull(skb, hsz)))
		वापस false;

	hdr = buf_msg(skb);
	अगर (unlikely(msg_version(hdr) != TIPC_VERSION))
		वापस false;

	msz = msg_size(hdr);
	अगर (unlikely(msz < hsz))
		वापस false;
	अगर (unlikely((msz - hsz) > TIPC_MAX_USER_MSG_SIZE))
		वापस false;
	अगर (unlikely(skb->len < msz))
		वापस false;

	TIPC_SKB_CB(skb)->validated = 1;
	वापस true;
पूर्ण

/**
 * tipc_msg_fragment - build a fragment skb list क्रम TIPC message
 *
 * @skb: TIPC message skb
 * @hdr: पूर्णांकernal msg header to be put on the top of the fragments
 * @pkपंचांगax: max size of a fragment incl. the header
 * @frags: वापसed fragment skb list
 *
 * Return: 0 अगर the fragmentation is successful, otherwise: -EINVAL
 * or -ENOMEM
 */
पूर्णांक tipc_msg_fragment(काष्ठा sk_buff *skb, स्थिर काष्ठा tipc_msg *hdr,
		      पूर्णांक pkपंचांगax, काष्ठा sk_buff_head *frags)
अणु
	पूर्णांक pktno, nof_fragms, dsz, dmax, eat;
	काष्ठा tipc_msg *_hdr;
	काष्ठा sk_buff *_skb;
	u8 *data;

	/* Non-linear buffer? */
	अगर (skb_linearize(skb))
		वापस -ENOMEM;

	data = (u8 *)skb->data;
	dsz = msg_size(buf_msg(skb));
	dmax = pkपंचांगax - INT_H_SIZE;
	अगर (dsz <= dmax || !dmax)
		वापस -EINVAL;

	nof_fragms = dsz / dmax + 1;
	क्रम (pktno = 1; pktno <= nof_fragms; pktno++) अणु
		अगर (pktno < nof_fragms)
			eat = dmax;
		अन्यथा
			eat = dsz % dmax;
		/* Allocate a new fragment */
		_skb = tipc_buf_acquire(INT_H_SIZE + eat, GFP_ATOMIC);
		अगर (!_skb)
			जाओ error;
		skb_orphan(_skb);
		__skb_queue_tail(frags, _skb);
		/* Copy header & data to the fragment */
		skb_copy_to_linear_data(_skb, hdr, INT_H_SIZE);
		skb_copy_to_linear_data_offset(_skb, INT_H_SIZE, data, eat);
		data += eat;
		/* Update the fragment's header */
		_hdr = buf_msg(_skb);
		msg_set_fragm_no(_hdr, pktno);
		msg_set_nof_fragms(_hdr, nof_fragms);
		msg_set_size(_hdr, INT_H_SIZE + eat);
	पूर्ण
	वापस 0;

error:
	__skb_queue_purge(frags);
	__skb_queue_head_init(frags);
	वापस -ENOMEM;
पूर्ण

/**
 * tipc_msg_build - create buffer chain containing specअगरied header and data
 * @mhdr: Message header, to be prepended to data
 * @m: User message
 * @offset: buffer offset क्रम fragmented messages (FIXME)
 * @dsz: Total length of user data
 * @pkपंचांगax: Max packet size that can be used
 * @list: Buffer or chain of buffers to be वापसed to caller
 *
 * Note that the recursive call we are making here is safe, since it can
 * logically go only one further level करोwn.
 *
 * Return: message data size or त्रुटि_सं: -ENOMEM, -EFAULT
 */
पूर्णांक tipc_msg_build(काष्ठा tipc_msg *mhdr, काष्ठा msghdr *m, पूर्णांक offset,
		   पूर्णांक dsz, पूर्णांक pkपंचांगax, काष्ठा sk_buff_head *list)
अणु
	पूर्णांक mhsz = msg_hdr_sz(mhdr);
	काष्ठा tipc_msg pkthdr;
	पूर्णांक msz = mhsz + dsz;
	पूर्णांक pktrem = pkपंचांगax;
	काष्ठा sk_buff *skb;
	पूर्णांक drem = dsz;
	पूर्णांक pktno = 1;
	अक्षर *pktpos;
	पूर्णांक pktsz;
	पूर्णांक rc;

	msg_set_size(mhdr, msz);

	/* No fragmentation needed? */
	अगर (likely(msz <= pkपंचांगax)) अणु
		skb = tipc_buf_acquire(msz, GFP_KERNEL);

		/* Fall back to smaller MTU अगर node local message */
		अगर (unlikely(!skb)) अणु
			अगर (pkपंचांगax != MAX_MSG_SIZE)
				वापस -ENOMEM;
			rc = tipc_msg_build(mhdr, m, offset, dsz, FB_MTU, list);
			अगर (rc != dsz)
				वापस rc;
			अगर (tipc_msg_assemble(list))
				वापस dsz;
			वापस -ENOMEM;
		पूर्ण
		skb_orphan(skb);
		__skb_queue_tail(list, skb);
		skb_copy_to_linear_data(skb, mhdr, mhsz);
		pktpos = skb->data + mhsz;
		अगर (copy_from_iter_full(pktpos, dsz, &m->msg_iter))
			वापस dsz;
		rc = -EFAULT;
		जाओ error;
	पूर्ण

	/* Prepare reusable fragment header */
	tipc_msg_init(msg_prevnode(mhdr), &pkthdr, MSG_FRAGMENTER,
		      FIRST_FRAGMENT, INT_H_SIZE, msg_destnode(mhdr));
	msg_set_size(&pkthdr, pkपंचांगax);
	msg_set_fragm_no(&pkthdr, pktno);
	msg_set_importance(&pkthdr, msg_importance(mhdr));

	/* Prepare first fragment */
	skb = tipc_buf_acquire(pkपंचांगax, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	skb_orphan(skb);
	__skb_queue_tail(list, skb);
	pktpos = skb->data;
	skb_copy_to_linear_data(skb, &pkthdr, INT_H_SIZE);
	pktpos += INT_H_SIZE;
	pktrem -= INT_H_SIZE;
	skb_copy_to_linear_data_offset(skb, INT_H_SIZE, mhdr, mhsz);
	pktpos += mhsz;
	pktrem -= mhsz;

	करो अणु
		अगर (drem < pktrem)
			pktrem = drem;

		अगर (!copy_from_iter_full(pktpos, pktrem, &m->msg_iter)) अणु
			rc = -EFAULT;
			जाओ error;
		पूर्ण
		drem -= pktrem;

		अगर (!drem)
			अवरोध;

		/* Prepare new fragment: */
		अगर (drem < (pkपंचांगax - INT_H_SIZE))
			pktsz = drem + INT_H_SIZE;
		अन्यथा
			pktsz = pkपंचांगax;
		skb = tipc_buf_acquire(pktsz, GFP_KERNEL);
		अगर (!skb) अणु
			rc = -ENOMEM;
			जाओ error;
		पूर्ण
		skb_orphan(skb);
		__skb_queue_tail(list, skb);
		msg_set_type(&pkthdr, FRAGMENT);
		msg_set_size(&pkthdr, pktsz);
		msg_set_fragm_no(&pkthdr, ++pktno);
		skb_copy_to_linear_data(skb, &pkthdr, INT_H_SIZE);
		pktpos = skb->data + INT_H_SIZE;
		pktrem = pktsz - INT_H_SIZE;

	पूर्ण जबतक (1);
	msg_set_type(buf_msg(skb), LAST_FRAGMENT);
	वापस dsz;
error:
	__skb_queue_purge(list);
	__skb_queue_head_init(list);
	वापस rc;
पूर्ण

/**
 * tipc_msg_bundle - Append contents of a buffer to tail of an existing one
 * @bskb: the bundle buffer to append to
 * @msg: message to be appended
 * @max: max allowable size क्रम the bundle buffer
 *
 * Return: "true" अगर bundling has been perक्रमmed, otherwise "false"
 */
अटल bool tipc_msg_bundle(काष्ठा sk_buff *bskb, काष्ठा tipc_msg *msg,
			    u32 max)
अणु
	काष्ठा tipc_msg *bmsg = buf_msg(bskb);
	u32 msz, bsz, offset, pad;

	msz = msg_size(msg);
	bsz = msg_size(bmsg);
	offset = align(bsz);
	pad = offset - bsz;

	अगर (unlikely(skb_tailroom(bskb) < (pad + msz)))
		वापस false;
	अगर (unlikely(max < (offset + msz)))
		वापस false;

	skb_put(bskb, pad + msz);
	skb_copy_to_linear_data_offset(bskb, offset, msg, msz);
	msg_set_size(bmsg, offset + msz);
	msg_set_msgcnt(bmsg, msg_msgcnt(bmsg) + 1);
	वापस true;
पूर्ण

/**
 * tipc_msg_try_bundle - Try to bundle a new message to the last one
 * @tskb: the last/target message to which the new one will be appended
 * @skb: the new message skb poपूर्णांकer
 * @mss: max message size (header inclusive)
 * @dnode: destination node क्रम the message
 * @new_bundle: अगर this call made a new bundle or not
 *
 * Return: "true" अगर the new message skb is potential क्रम bundling this समय or
 * later, in the हाल a bundling has been करोne this समय, the skb is consumed
 * (the skb poपूर्णांकer = शून्य).
 * Otherwise, "false" अगर the skb cannot be bundled at all.
 */
bool tipc_msg_try_bundle(काष्ठा sk_buff *tskb, काष्ठा sk_buff **skb, u32 mss,
			 u32 dnode, bool *new_bundle)
अणु
	काष्ठा tipc_msg *msg, *inner, *outer;
	u32 tsz;

	/* First, check अगर the new buffer is suitable क्रम bundling */
	msg = buf_msg(*skb);
	अगर (msg_user(msg) == MSG_FRAGMENTER)
		वापस false;
	अगर (msg_user(msg) == TUNNEL_PROTOCOL)
		वापस false;
	अगर (msg_user(msg) == BCAST_PROTOCOL)
		वापस false;
	अगर (mss <= INT_H_SIZE + msg_size(msg))
		वापस false;

	/* Ok, but the last/target buffer can be empty? */
	अगर (unlikely(!tskb))
		वापस true;

	/* Is it a bundle alपढ़ोy? Try to bundle the new message to it */
	अगर (msg_user(buf_msg(tskb)) == MSG_BUNDLER) अणु
		*new_bundle = false;
		जाओ bundle;
	पूर्ण

	/* Make a new bundle of the two messages अगर possible */
	tsz = msg_size(buf_msg(tskb));
	अगर (unlikely(mss < align(INT_H_SIZE + tsz) + msg_size(msg)))
		वापस true;
	अगर (unlikely(pskb_expand_head(tskb, INT_H_SIZE, mss - tsz - INT_H_SIZE,
				      GFP_ATOMIC)))
		वापस true;
	inner = buf_msg(tskb);
	skb_push(tskb, INT_H_SIZE);
	outer = buf_msg(tskb);
	tipc_msg_init(msg_prevnode(inner), outer, MSG_BUNDLER, 0, INT_H_SIZE,
		      dnode);
	msg_set_importance(outer, msg_importance(inner));
	msg_set_size(outer, INT_H_SIZE + tsz);
	msg_set_msgcnt(outer, 1);
	*new_bundle = true;

bundle:
	अगर (likely(tipc_msg_bundle(tskb, msg, mss))) अणु
		consume_skb(*skb);
		*skb = शून्य;
	पूर्ण
	वापस true;
पूर्ण

/**
 *  tipc_msg_extract(): extract bundled inner packet from buffer
 *  @skb: buffer to be extracted from.
 *  @iskb: extracted inner buffer, to be वापसed
 *  @pos: position in outer message of msg to be extracted.
 *  Returns position of next msg.
 *  Consumes outer buffer when last packet extracted
 *  Return: true when there is an extracted buffer, otherwise false
 */
bool tipc_msg_extract(काष्ठा sk_buff *skb, काष्ठा sk_buff **iskb, पूर्णांक *pos)
अणु
	काष्ठा tipc_msg *hdr, *ihdr;
	पूर्णांक imsz;

	*iskb = शून्य;
	अगर (unlikely(skb_linearize(skb)))
		जाओ none;

	hdr = buf_msg(skb);
	अगर (unlikely(*pos > (msg_data_sz(hdr) - MIN_H_SIZE)))
		जाओ none;

	ihdr = (काष्ठा tipc_msg *)(msg_data(hdr) + *pos);
	imsz = msg_size(ihdr);

	अगर ((*pos + imsz) > msg_data_sz(hdr))
		जाओ none;

	*iskb = tipc_buf_acquire(imsz, GFP_ATOMIC);
	अगर (!*iskb)
		जाओ none;

	skb_copy_to_linear_data(*iskb, ihdr, imsz);
	अगर (unlikely(!tipc_msg_validate(iskb)))
		जाओ none;

	*pos += align(imsz);
	वापस true;
none:
	kमुक्त_skb(skb);
	kमुक्त_skb(*iskb);
	*iskb = शून्य;
	वापस false;
पूर्ण

/**
 * tipc_msg_reverse(): swap source and destination addresses and add error code
 * @own_node: originating node id क्रम reversed message
 * @skb:  buffer containing message to be reversed; will be consumed
 * @err:  error code to be set in message, अगर any
 * Replaces consumed buffer with new one when successful
 * Return: true अगर success, otherwise false
 */
bool tipc_msg_reverse(u32 own_node,  काष्ठा sk_buff **skb, पूर्णांक err)
अणु
	काष्ठा sk_buff *_skb = *skb;
	काष्ठा tipc_msg *_hdr, *hdr;
	पूर्णांक hlen, dlen;

	अगर (skb_linearize(_skb))
		जाओ निकास;
	_hdr = buf_msg(_skb);
	dlen = min_t(uपूर्णांक, msg_data_sz(_hdr), MAX_FORWARD_SIZE);
	hlen = msg_hdr_sz(_hdr);

	अगर (msg_dest_droppable(_hdr))
		जाओ निकास;
	अगर (msg_errcode(_hdr))
		जाओ निकास;

	/* Never वापस SHORT header */
	अगर (hlen == SHORT_H_SIZE)
		hlen = BASIC_H_SIZE;

	/* Don't वापस data aदीर्घ with SYN+, - sender has a clone */
	अगर (msg_is_syn(_hdr) && err == TIPC_ERR_OVERLOAD)
		dlen = 0;

	/* Allocate new buffer to वापस */
	*skb = tipc_buf_acquire(hlen + dlen, GFP_ATOMIC);
	अगर (!*skb)
		जाओ निकास;
	स_नकल((*skb)->data, _skb->data, msg_hdr_sz(_hdr));
	स_नकल((*skb)->data + hlen, msg_data(_hdr), dlen);

	/* Build reverse header in new buffer */
	hdr = buf_msg(*skb);
	msg_set_hdr_sz(hdr, hlen);
	msg_set_errcode(hdr, err);
	msg_set_non_seq(hdr, 0);
	msg_set_origport(hdr, msg_destport(_hdr));
	msg_set_destport(hdr, msg_origport(_hdr));
	msg_set_destnode(hdr, msg_prevnode(_hdr));
	msg_set_prevnode(hdr, own_node);
	msg_set_orignode(hdr, own_node);
	msg_set_size(hdr, hlen + dlen);
	skb_orphan(_skb);
	kमुक्त_skb(_skb);
	वापस true;
निकास:
	kमुक्त_skb(_skb);
	*skb = शून्य;
	वापस false;
पूर्ण

bool tipc_msg_skb_clone(काष्ठा sk_buff_head *msg, काष्ठा sk_buff_head *cpy)
अणु
	काष्ठा sk_buff *skb, *_skb;

	skb_queue_walk(msg, skb) अणु
		_skb = skb_clone(skb, GFP_ATOMIC);
		अगर (!_skb) अणु
			__skb_queue_purge(cpy);
			pr_err_ratelimited("Failed to clone buffer chain\n");
			वापस false;
		पूर्ण
		__skb_queue_tail(cpy, _skb);
	पूर्ण
	वापस true;
पूर्ण

/**
 * tipc_msg_lookup_dest(): try to find new destination क्रम named message
 * @net: poपूर्णांकer to associated network namespace
 * @skb: the buffer containing the message.
 * @err: error code to be used by caller अगर lookup fails
 * Does not consume buffer
 * Return: true अगर a destination is found, false otherwise
 */
bool tipc_msg_lookup_dest(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक *err)
अणु
	काष्ठा tipc_msg *msg = buf_msg(skb);
	u32 scope = msg_lookup_scope(msg);
	u32 self = tipc_own_addr(net);
	u32 inst = msg_nameinst(msg);
	काष्ठा tipc_socket_addr sk;
	काष्ठा tipc_uaddr ua;

	अगर (!msg_isdata(msg))
		वापस false;
	अगर (!msg_named(msg))
		वापस false;
	अगर (msg_errcode(msg))
		वापस false;
	*err = TIPC_ERR_NO_NAME;
	अगर (skb_linearize(skb))
		वापस false;
	msg = buf_msg(skb);
	अगर (msg_reroute_cnt(msg))
		वापस false;
	tipc_uaddr(&ua, TIPC_SERVICE_RANGE, scope,
		   msg_nametype(msg), inst, inst);
	sk.node = tipc_scope2node(net, scope);
	अगर (!tipc_nametbl_lookup_anycast(net, &ua, &sk))
		वापस false;
	msg_incr_reroute_cnt(msg);
	अगर (sk.node != self)
		msg_set_prevnode(msg, self);
	msg_set_destnode(msg, sk.node);
	msg_set_destport(msg, sk.ref);
	*err = TIPC_OK;

	वापस true;
पूर्ण

/* tipc_msg_assemble() - assemble chain of fragments पूर्णांकo one message
 */
bool tipc_msg_assemble(काष्ठा sk_buff_head *list)
अणु
	काष्ठा sk_buff *skb, *पंचांगp = शून्य;

	अगर (skb_queue_len(list) == 1)
		वापस true;

	जबतक ((skb = __skb_dequeue(list))) अणु
		skb->next = शून्य;
		अगर (tipc_buf_append(&पंचांगp, &skb)) अणु
			__skb_queue_tail(list, skb);
			वापस true;
		पूर्ण
		अगर (!पंचांगp)
			अवरोध;
	पूर्ण
	__skb_queue_purge(list);
	__skb_queue_head_init(list);
	pr_warn("Failed do assemble buffer\n");
	वापस false;
पूर्ण

/* tipc_msg_reassemble() - clone a buffer chain of fragments and
 *                         reassemble the clones पूर्णांकo one message
 */
bool tipc_msg_reassemble(काष्ठा sk_buff_head *list, काष्ठा sk_buff_head *rcvq)
अणु
	काष्ठा sk_buff *skb, *_skb;
	काष्ठा sk_buff *frag = शून्य;
	काष्ठा sk_buff *head = शून्य;
	पूर्णांक hdr_len;

	/* Copy header अगर single buffer */
	अगर (skb_queue_len(list) == 1) अणु
		skb = skb_peek(list);
		hdr_len = skb_headroom(skb) + msg_hdr_sz(buf_msg(skb));
		_skb = __pskb_copy(skb, hdr_len, GFP_ATOMIC);
		अगर (!_skb)
			वापस false;
		__skb_queue_tail(rcvq, _skb);
		वापस true;
	पूर्ण

	/* Clone all fragments and reassemble */
	skb_queue_walk(list, skb) अणु
		frag = skb_clone(skb, GFP_ATOMIC);
		अगर (!frag)
			जाओ error;
		frag->next = शून्य;
		अगर (tipc_buf_append(&head, &frag))
			अवरोध;
		अगर (!head)
			जाओ error;
	पूर्ण
	__skb_queue_tail(rcvq, frag);
	वापस true;
error:
	pr_warn("Failed do clone local mcast rcv buffer\n");
	kमुक्त_skb(head);
	वापस false;
पूर्ण

bool tipc_msg_pskb_copy(u32 dst, काष्ठा sk_buff_head *msg,
			काष्ठा sk_buff_head *cpy)
अणु
	काष्ठा sk_buff *skb, *_skb;

	skb_queue_walk(msg, skb) अणु
		_skb = pskb_copy(skb, GFP_ATOMIC);
		अगर (!_skb) अणु
			__skb_queue_purge(cpy);
			वापस false;
		पूर्ण
		msg_set_destnode(buf_msg(_skb), dst);
		__skb_queue_tail(cpy, _skb);
	पूर्ण
	वापस true;
पूर्ण

/* tipc_skb_queue_sorted(); sort pkt पूर्णांकo list according to sequence number
 * @list: list to be appended to
 * @seqno: sequence number of buffer to add
 * @skb: buffer to add
 */
bool __tipc_skb_queue_sorted(काष्ठा sk_buff_head *list, u16 seqno,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *_skb, *पंचांगp;

	अगर (skb_queue_empty(list) || less(seqno, buf_seqno(skb_peek(list)))) अणु
		__skb_queue_head(list, skb);
		वापस true;
	पूर्ण

	अगर (more(seqno, buf_seqno(skb_peek_tail(list)))) अणु
		__skb_queue_tail(list, skb);
		वापस true;
	पूर्ण

	skb_queue_walk_safe(list, _skb, पंचांगp) अणु
		अगर (more(seqno, buf_seqno(_skb)))
			जारी;
		अगर (seqno == buf_seqno(_skb))
			अवरोध;
		__skb_queue_beक्रमe(list, _skb, skb);
		वापस true;
	पूर्ण
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

व्योम tipc_skb_reject(काष्ठा net *net, पूर्णांक err, काष्ठा sk_buff *skb,
		     काष्ठा sk_buff_head *xmitq)
अणु
	अगर (tipc_msg_reverse(tipc_own_addr(net), &skb, err))
		__skb_queue_tail(xmitq, skb);
पूर्ण
