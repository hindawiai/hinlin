<शैली गुरु>
/*
 * net/tipc/trace.c: TIPC tracepoपूर्णांकs code
 *
 * Copyright (c) 2018, Ericsson AB
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "ASIS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
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

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

/*
 * socket tuples क्रम filtering in socket traces:
 * (portid, sock type, name type, name lower, name upper)
 */
अचिन्हित दीर्घ sysctl_tipc_sk_filter[5] __पढ़ो_mostly = अणु0, पूर्ण;

/**
 * tipc_skb_dump - dump TIPC skb data
 * @skb: skb to be dumped
 * @more: dump more?
 *        - false: dump only tipc msg data
 *        - true: dump kernel-related skb data and tipc cb[] array as well
 * @buf: वापसed buffer of dump data in क्रमmat
 */
पूर्णांक tipc_skb_dump(काष्ठा sk_buff *skb, bool more, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	माप_प्रकार sz = (more) ? SKB_LMAX : SKB_LMIN;
	काष्ठा tipc_msg *hdr;
	काष्ठा tipc_skb_cb *skbcb;

	अगर (!skb) अणु
		i += scnम_लिखो(buf, sz, "msg: (null)\n");
		वापस i;
	पूर्ण

	hdr = buf_msg(skb);
	skbcb = TIPC_SKB_CB(skb);

	/* tipc msg data section */
	i += scnम_लिखो(buf, sz, "msg: %u", msg_user(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_type(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_hdr_sz(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_data_sz(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %x", msg_orignode(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %x", msg_destnode(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_seqno(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_ack(hdr));
	i += scnम_लिखो(buf + i, sz - i, " %u", msg_bcast_ack(hdr));
	चयन (msg_user(hdr)) अणु
	हाल LINK_PROTOCOL:
		i += scnम_लिखो(buf + i, sz - i, " %c", msg_net_plane(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_probe(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_peer_stopping(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_session(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_next_sent(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_seq_gap(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_bc_snd_nxt(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_bc_gap(hdr));
		अवरोध;
	हाल TIPC_LOW_IMPORTANCE:
	हाल TIPC_MEDIUM_IMPORTANCE:
	हाल TIPC_HIGH_IMPORTANCE:
	हाल TIPC_CRITICAL_IMPORTANCE:
	हाल CONN_MANAGER:
	हाल SOCK_WAKEUP:
		i += scnम_लिखो(buf + i, sz - i, " | %u", msg_origport(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_destport(hdr));
		चयन (msg_type(hdr)) अणु
		हाल TIPC_NAMED_MSG:
			i += scnम_लिखो(buf + i, sz - i, " %u",
				       msg_nametype(hdr));
			i += scnम_लिखो(buf + i, sz - i, " %u",
				       msg_nameinst(hdr));
			अवरोध;
		हाल TIPC_MCAST_MSG:
			i += scnम_लिखो(buf + i, sz - i, " %u",
				       msg_nametype(hdr));
			i += scnम_लिखो(buf + i, sz - i, " %u",
				       msg_namelower(hdr));
			i += scnम_लिखो(buf + i, sz - i, " %u",
				       msg_nameupper(hdr));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		i += scnम_लिखो(buf + i, sz - i, " | %u",
			       msg_src_droppable(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u",
			       msg_dest_droppable(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_errcode(hdr));
		i += scnम_लिखो(buf + i, sz - i, " %u", msg_reroute_cnt(hdr));
		अवरोध;
	शेष:
		/* need more? */
		अवरोध;
	पूर्ण

	i += scnम_लिखो(buf + i, sz - i, "\n");
	अगर (!more)
		वापस i;

	/* kernel-related skb data section */
	i += scnम_लिखो(buf + i, sz - i, "skb: %s",
		       (skb->dev) ? skb->dev->name : "n/a");
	i += scnम_लिखो(buf + i, sz - i, " %u", skb->len);
	i += scnम_लिखो(buf + i, sz - i, " %u", skb->data_len);
	i += scnम_लिखो(buf + i, sz - i, " %u", skb->hdr_len);
	i += scnम_लिखो(buf + i, sz - i, " %u", skb->truesize);
	i += scnम_लिखो(buf + i, sz - i, " %u", skb_cloned(skb));
	i += scnम_लिखो(buf + i, sz - i, " %p", skb->sk);
	i += scnम_लिखो(buf + i, sz - i, " %u", skb_shinfo(skb)->nr_frags);
	i += scnम_लिखो(buf + i, sz - i, " %llx",
		       kसमय_प्रकारo_ms(skb_get_kसमय(skb)));
	i += scnम_लिखो(buf + i, sz - i, " %llx\n",
		       kसमय_प्रकारo_ms(skb_hwtstamps(skb)->hwtstamp));

	/* tipc skb cb[] data section */
	i += scnम_लिखो(buf + i, sz - i, "cb[]: %u", skbcb->bytes_पढ़ो);
	i += scnम_लिखो(buf + i, sz - i, " %u", skbcb->orig_member);
	i += scnम_लिखो(buf + i, sz - i, " %u",
		       jअगरfies_to_msecs(skbcb->nxt_retr));
	i += scnम_लिखो(buf + i, sz - i, " %u", skbcb->validated);
	i += scnम_लिखो(buf + i, sz - i, " %u", skbcb->chain_imp);
	i += scnम_लिखो(buf + i, sz - i, " %u\n", skbcb->ackers);

	वापस i;
पूर्ण

/**
 * tipc_list_dump - dump TIPC skb list/queue
 * @list: list of skbs to be dumped
 * @more: dump more?
 *        - false: dump only the head & tail skbs
 *        - true: dump the first & last 5 skbs
 * @buf: वापसed buffer of dump data in क्रमmat
 */
पूर्णांक tipc_list_dump(काष्ठा sk_buff_head *list, bool more, अक्षर *buf)
अणु
	पूर्णांक i = 0;
	माप_प्रकार sz = (more) ? LIST_LMAX : LIST_LMIN;
	u32 count, len;
	काष्ठा sk_buff *hskb, *tskb, *skb, *पंचांगp;

	अगर (!list) अणु
		i += scnम_लिखो(buf, sz, "(null)\n");
		वापस i;
	पूर्ण

	len = skb_queue_len(list);
	i += scnम_लिखो(buf, sz, "len = %d\n", len);

	अगर (!len)
		वापस i;

	अगर (!more) अणु
		hskb = skb_peek(list);
		i += scnम_लिखो(buf + i, sz - i, "  head ");
		i += tipc_skb_dump(hskb, false, buf + i);
		अगर (len > 1) अणु
			tskb = skb_peek_tail(list);
			i += scnम_लिखो(buf + i, sz - i, "  tail ");
			i += tipc_skb_dump(tskb, false, buf + i);
		पूर्ण
	पूर्ण अन्यथा अणु
		count = 0;
		skb_queue_walk_safe(list, skb, पंचांगp) अणु
			count++;
			अगर (count == 6)
				i += scnम_लिखो(buf + i, sz - i, "  .\n  .\n");
			अगर (count > 5 && count <= len - 5)
				जारी;
			i += scnम_लिखो(buf + i, sz - i, "  #%d ", count);
			i += tipc_skb_dump(skb, false, buf + i);
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण
