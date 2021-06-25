<शैली गुरु>
/*
 * Copyright (c) 2006, 2017 Oracle and/or its affiliates. All rights reserved.
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
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <net/tcp.h>

#समावेश "rds.h"
#समावेश "tcp.h"

अटल काष्ठा kmem_cache *rds_tcp_incoming_slab;

अटल व्योम rds_tcp_inc_purge(काष्ठा rds_incoming *inc)
अणु
	काष्ठा rds_tcp_incoming *tinc;
	tinc = container_of(inc, काष्ठा rds_tcp_incoming, ti_inc);
	rdsdebug("purging tinc %p inc %p\n", tinc, inc);
	skb_queue_purge(&tinc->ti_skb_list);
पूर्ण

व्योम rds_tcp_inc_मुक्त(काष्ठा rds_incoming *inc)
अणु
	काष्ठा rds_tcp_incoming *tinc;
	tinc = container_of(inc, काष्ठा rds_tcp_incoming, ti_inc);
	rds_tcp_inc_purge(inc);
	rdsdebug("freeing tinc %p inc %p\n", tinc, inc);
	kmem_cache_मुक्त(rds_tcp_incoming_slab, tinc);
पूर्ण

/*
 * this is pretty lame, but, whatever.
 */
पूर्णांक rds_tcp_inc_copy_to_user(काष्ठा rds_incoming *inc, काष्ठा iov_iter *to)
अणु
	काष्ठा rds_tcp_incoming *tinc;
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;

	अगर (!iov_iter_count(to))
		जाओ out;

	tinc = container_of(inc, काष्ठा rds_tcp_incoming, ti_inc);

	skb_queue_walk(&tinc->ti_skb_list, skb) अणु
		अचिन्हित दीर्घ to_copy, skb_off;
		क्रम (skb_off = 0; skb_off < skb->len; skb_off += to_copy) अणु
			to_copy = iov_iter_count(to);
			to_copy = min(to_copy, skb->len - skb_off);

			अगर (skb_copy_datagram_iter(skb, skb_off, to, to_copy))
				वापस -EFAULT;

			rds_stats_add(s_copy_to_user, to_copy);
			ret += to_copy;

			अगर (!iov_iter_count(to))
				जाओ out;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * We have a series of skbs that have fragmented pieces of the congestion
 * biपंचांगap.  They must add up to the exact size of the congestion biपंचांगap.  We
 * use the skb helpers to copy those पूर्णांकo the pages that make up the in-memory
 * congestion biपंचांगap क्रम the remote address of this connection.  We then tell
 * the congestion core that the biपंचांगap has been changed so that it can wake up
 * sleepers.
 *
 * This is racing with sending paths which are using test_bit to see अगर the
 * biपंचांगap indicates that their recipient is congested.
 */

अटल व्योम rds_tcp_cong_recv(काष्ठा rds_connection *conn,
			      काष्ठा rds_tcp_incoming *tinc)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक to_copy, skb_off;
	अचिन्हित पूर्णांक map_off;
	अचिन्हित पूर्णांक map_page;
	काष्ठा rds_cong_map *map;
	पूर्णांक ret;

	/* catch completely corrupt packets */
	अगर (be32_to_cpu(tinc->ti_inc.i_hdr.h_len) != RDS_CONG_MAP_BYTES)
		वापस;

	map_page = 0;
	map_off = 0;
	map = conn->c_fcong;

	skb_queue_walk(&tinc->ti_skb_list, skb) अणु
		skb_off = 0;
		जबतक (skb_off < skb->len) अणु
			to_copy = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - map_off,
					skb->len - skb_off);

			BUG_ON(map_page >= RDS_CONG_MAP_PAGES);

			/* only वापसs 0 or -error */
			ret = skb_copy_bits(skb, skb_off,
				(व्योम *)map->m_page_addrs[map_page] + map_off,
				to_copy);
			BUG_ON(ret != 0);

			skb_off += to_copy;
			map_off += to_copy;
			अगर (map_off == PAGE_SIZE) अणु
				map_off = 0;
				map_page++;
			पूर्ण
		पूर्ण
	पूर्ण

	rds_cong_map_updated(map, ~(u64) 0);
पूर्ण

काष्ठा rds_tcp_desc_arg अणु
	काष्ठा rds_conn_path *conn_path;
	gfp_t gfp;
पूर्ण;

अटल पूर्णांक rds_tcp_data_recv(पढ़ो_descriptor_t *desc, काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	काष्ठा rds_tcp_desc_arg *arg = desc->arg.data;
	काष्ठा rds_conn_path *cp = arg->conn_path;
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	काष्ठा rds_tcp_incoming *tinc = tc->t_tinc;
	काष्ठा sk_buff *clone;
	माप_प्रकार left = len, to_copy;

	rdsdebug("tcp data tc %p skb %p offset %u len %zu\n", tc, skb, offset,
		 len);

	/*
	 * tcp_पढ़ो_sock() पूर्णांकerprets partial progress as an indication to stop
	 * processing.
	 */
	जबतक (left) अणु
		अगर (!tinc) अणु
			tinc = kmem_cache_alloc(rds_tcp_incoming_slab,
						arg->gfp);
			अगर (!tinc) अणु
				desc->error = -ENOMEM;
				जाओ out;
			पूर्ण
			tc->t_tinc = tinc;
			rdsdebug("alloced tinc %p\n", tinc);
			rds_inc_path_init(&tinc->ti_inc, cp,
					  &cp->cp_conn->c_faddr);
			tinc->ti_inc.i_rx_lat_trace[RDS_MSG_RX_HDR] =
					local_घड़ी();

			/*
			 * XXX * we might be able to use the __ variants when
			 * we've alपढ़ोy serialized at a higher level.
			 */
			skb_queue_head_init(&tinc->ti_skb_list);
		पूर्ण

		अगर (left && tc->t_tinc_hdr_rem) अणु
			to_copy = min(tc->t_tinc_hdr_rem, left);
			rdsdebug("copying %zu header from skb %p\n", to_copy,
				 skb);
			skb_copy_bits(skb, offset,
				      (अक्षर *)&tinc->ti_inc.i_hdr +
						माप(काष्ठा rds_header) -
						tc->t_tinc_hdr_rem,
				      to_copy);
			tc->t_tinc_hdr_rem -= to_copy;
			left -= to_copy;
			offset += to_copy;

			अगर (tc->t_tinc_hdr_rem == 0) अणु
				/* could be 0 क्रम a 0 len message */
				tc->t_tinc_data_rem =
					be32_to_cpu(tinc->ti_inc.i_hdr.h_len);
				tinc->ti_inc.i_rx_lat_trace[RDS_MSG_RX_START] =
					local_घड़ी();
			पूर्ण
		पूर्ण

		अगर (left && tc->t_tinc_data_rem) अणु
			to_copy = min(tc->t_tinc_data_rem, left);

			clone = pskb_extract(skb, offset, to_copy, arg->gfp);
			अगर (!clone) अणु
				desc->error = -ENOMEM;
				जाओ out;
			पूर्ण

			skb_queue_tail(&tinc->ti_skb_list, clone);

			rdsdebug("skb %p data %p len %d off %u to_copy %zu -> "
				 "clone %p data %p len %d\n",
				 skb, skb->data, skb->len, offset, to_copy,
				 clone, clone->data, clone->len);

			tc->t_tinc_data_rem -= to_copy;
			left -= to_copy;
			offset += to_copy;
		पूर्ण

		अगर (tc->t_tinc_hdr_rem == 0 && tc->t_tinc_data_rem == 0) अणु
			काष्ठा rds_connection *conn = cp->cp_conn;

			अगर (tinc->ti_inc.i_hdr.h_flags == RDS_FLAG_CONG_BITMAP)
				rds_tcp_cong_recv(conn, tinc);
			अन्यथा
				rds_recv_incoming(conn, &conn->c_faddr,
						  &conn->c_laddr,
						  &tinc->ti_inc,
						  arg->gfp);

			tc->t_tinc_hdr_rem = माप(काष्ठा rds_header);
			tc->t_tinc_data_rem = 0;
			tc->t_tinc = शून्य;
			rds_inc_put(&tinc->ti_inc);
			tinc = शून्य;
		पूर्ण
	पूर्ण
out:
	rdsdebug("returning len %zu left %zu skb len %d rx queue depth %d\n",
		 len, left, skb->len,
		 skb_queue_len(&tc->t_sock->sk->sk_receive_queue));
	वापस len - left;
पूर्ण

/* the caller has to hold the sock lock */
अटल पूर्णांक rds_tcp_पढ़ो_sock(काष्ठा rds_conn_path *cp, gfp_t gfp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	काष्ठा socket *sock = tc->t_sock;
	पढ़ो_descriptor_t desc;
	काष्ठा rds_tcp_desc_arg arg;

	/* It's like glib in the kernel! */
	arg.conn_path = cp;
	arg.gfp = gfp;
	desc.arg.data = &arg;
	desc.error = 0;
	desc.count = 1; /* give more than one skb per call */

	tcp_पढ़ो_sock(sock->sk, &desc, rds_tcp_data_recv);
	rdsdebug("tcp_read_sock for tc %p gfp 0x%x returned %d\n", tc, gfp,
		 desc.error);

	वापस desc.error;
पूर्ण

/*
 * We hold the sock lock to serialize our rds_tcp_recv->tcp_पढ़ो_sock from
 * data_पढ़ोy.
 *
 * अगर we fail to allocate we're in trouble.. blindly रुको some समय beक्रमe
 * trying again to see अगर the VM can मुक्त up something क्रम us.
 */
पूर्णांक rds_tcp_recv_path(काष्ठा rds_conn_path *cp)
अणु
	काष्ठा rds_tcp_connection *tc = cp->cp_transport_data;
	काष्ठा socket *sock = tc->t_sock;
	पूर्णांक ret = 0;

	rdsdebug("recv worker path [%d] tc %p sock %p\n",
		 cp->cp_index, tc, sock);

	lock_sock(sock->sk);
	ret = rds_tcp_पढ़ो_sock(cp, GFP_KERNEL);
	release_sock(sock->sk);

	वापस ret;
पूर्ण

व्योम rds_tcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	व्योम (*पढ़ोy)(काष्ठा sock *sk);
	काष्ठा rds_conn_path *cp;
	काष्ठा rds_tcp_connection *tc;

	rdsdebug("data ready sk %p\n", sk);

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	cp = sk->sk_user_data;
	अगर (!cp) अणु /* check क्रम tearकरोwn race */
		पढ़ोy = sk->sk_data_पढ़ोy;
		जाओ out;
	पूर्ण

	tc = cp->cp_transport_data;
	पढ़ोy = tc->t_orig_data_पढ़ोy;
	rds_tcp_stats_inc(s_tcp_data_पढ़ोy_calls);

	अगर (rds_tcp_पढ़ो_sock(cp, GFP_ATOMIC) == -ENOMEM) अणु
		rcu_पढ़ो_lock();
		अगर (!rds_destroy_pending(cp->cp_conn))
			queue_delayed_work(rds_wq, &cp->cp_recv_w, 0);
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
	पढ़ोy(sk);
पूर्ण

पूर्णांक rds_tcp_recv_init(व्योम)
अणु
	rds_tcp_incoming_slab = kmem_cache_create("rds_tcp_incoming",
					माप(काष्ठा rds_tcp_incoming),
					0, 0, शून्य);
	अगर (!rds_tcp_incoming_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम rds_tcp_recv_निकास(व्योम)
अणु
	kmem_cache_destroy(rds_tcp_incoming_slab);
पूर्ण
