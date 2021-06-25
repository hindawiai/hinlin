<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 - 2019 Cambridge Greys Limited
 * Copyright (C) 2011 - 2014 Cisco Systems Inc
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org) and
 * James Leu (jleu@mindspring.net).
 * Copyright (C) 2001 by various other people who didn't put their name here.
 */

#समावेश <linux/memblock.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>
#समावेश <linux/fs.h>
#समावेश <uapi/linux/filter.h>
#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश <irq_user.h>
#समावेश <net_kern.h>
#समावेश <os.h>
#समावेश "mconsole_kern.h"
#समावेश "vector_user.h"
#समावेश "vector_kern.h"

/*
 * Adapted from network devices with the following major changes:
 * All transports are अटल - simplअगरies the code signअगरicantly
 * Multiple FDs/IRQs per device
 * Vector IO optionally used क्रम पढ़ो/ग_लिखो, falling back to legacy
 * based on configuration and/or availability
 * Configuration is no दीर्घer positional - L2TPv3 and GRE require up to
 * 10 parameters, passing this as positional is not fit क्रम purpose.
 * Only socket transports are supported
 */


#घोषणा DRIVER_NAME "uml-vector"
काष्ठा vector_cmd_line_arg अणु
	काष्ठा list_head list;
	पूर्णांक unit;
	अक्षर *arguments;
पूर्ण;

काष्ठा vector_device अणु
	काष्ठा list_head list;
	काष्ठा net_device *dev;
	काष्ठा platक्रमm_device pdev;
	पूर्णांक unit;
	पूर्णांक खोलोed;
पूर्ण;

अटल LIST_HEAD(vec_cmd_line);

अटल DEFINE_SPINLOCK(vector_devices_lock);
अटल LIST_HEAD(vector_devices);

अटल पूर्णांक driver_रेजिस्टरed;

अटल व्योम vector_eth_configure(पूर्णांक n, काष्ठा arglist *def);

/* Argument accessors to set variables (and/or set शेष values)
 * mtu, buffer sizing, शेष headroom, etc
 */

#घोषणा DEFAULT_HEADROOM 2
#घोषणा SAFETY_MARGIN 32
#घोषणा DEFAULT_VECTOR_SIZE 64
#घोषणा TX_SMALL_PACKET 128
#घोषणा MAX_IOV_SIZE (MAX_SKB_FRAGS + 1)
#घोषणा MAX_ITERATIONS 64

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "rx_queue_max" पूर्ण,
	अणु "rx_queue_running_average" पूर्ण,
	अणु "tx_queue_max" पूर्ण,
	अणु "tx_queue_running_average" पूर्ण,
	अणु "rx_encaps_errors" पूर्ण,
	अणु "tx_timeout_count" पूर्ण,
	अणु "tx_restart_queue" पूर्ण,
	अणु "tx_kicks" पूर्ण,
	अणु "tx_flow_control_xon" पूर्ण,
	अणु "tx_flow_control_xoff" पूर्ण,
	अणु "rx_csum_offload_good" पूर्ण,
	अणु "rx_csum_offload_errors"पूर्ण,
	अणु "sg_ok"पूर्ण,
	अणु "sg_linearized"पूर्ण,
पूर्ण;

#घोषणा VECTOR_NUM_STATS	ARRAY_SIZE(ethtool_stats_keys)

अटल व्योम vector_reset_stats(काष्ठा vector_निजी *vp)
अणु
	vp->estats.rx_queue_max = 0;
	vp->estats.rx_queue_running_average = 0;
	vp->estats.tx_queue_max = 0;
	vp->estats.tx_queue_running_average = 0;
	vp->estats.rx_encaps_errors = 0;
	vp->estats.tx_समयout_count = 0;
	vp->estats.tx_restart_queue = 0;
	vp->estats.tx_kicks = 0;
	vp->estats.tx_flow_control_xon = 0;
	vp->estats.tx_flow_control_xoff = 0;
	vp->estats.sg_ok = 0;
	vp->estats.sg_linearized = 0;
पूर्ण

अटल पूर्णांक get_mtu(काष्ठा arglist *def)
अणु
	अक्षर *mtu = uml_vector_fetch_arg(def, "mtu");
	दीर्घ result;

	अगर (mtu != शून्य) अणु
		अगर (kम_से_अदीर्घ(mtu, 10, &result) == 0)
			अगर ((result < (1 << 16) - 1) && (result >= 576))
				वापस result;
	पूर्ण
	वापस ETH_MAX_PACKET;
पूर्ण

अटल अक्षर *get_bpf_file(काष्ठा arglist *def)
अणु
	वापस uml_vector_fetch_arg(def, "bpffile");
पूर्ण

अटल bool get_bpf_flash(काष्ठा arglist *def)
अणु
	अक्षर *allow = uml_vector_fetch_arg(def, "bpfflash");
	दीर्घ result;

	अगर (allow != शून्य) अणु
		अगर (kम_से_अदीर्घ(allow, 10, &result) == 0)
			वापस (allow > 0);
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक get_depth(काष्ठा arglist *def)
अणु
	अक्षर *mtu = uml_vector_fetch_arg(def, "depth");
	दीर्घ result;

	अगर (mtu != शून्य) अणु
		अगर (kम_से_अदीर्घ(mtu, 10, &result) == 0)
			वापस result;
	पूर्ण
	वापस DEFAULT_VECTOR_SIZE;
पूर्ण

अटल पूर्णांक get_headroom(काष्ठा arglist *def)
अणु
	अक्षर *mtu = uml_vector_fetch_arg(def, "headroom");
	दीर्घ result;

	अगर (mtu != शून्य) अणु
		अगर (kम_से_अदीर्घ(mtu, 10, &result) == 0)
			वापस result;
	पूर्ण
	वापस DEFAULT_HEADROOM;
पूर्ण

अटल पूर्णांक get_req_size(काष्ठा arglist *def)
अणु
	अक्षर *gro = uml_vector_fetch_arg(def, "gro");
	दीर्घ result;

	अगर (gro != शून्य) अणु
		अगर (kम_से_अदीर्घ(gro, 10, &result) == 0) अणु
			अगर (result > 0)
				वापस 65536;
		पूर्ण
	पूर्ण
	वापस get_mtu(def) + ETH_HEADER_OTHER +
		get_headroom(def) + SAFETY_MARGIN;
पूर्ण


अटल पूर्णांक get_transport_options(काष्ठा arglist *def)
अणु
	अक्षर *transport = uml_vector_fetch_arg(def, "transport");
	अक्षर *vector = uml_vector_fetch_arg(def, "vec");

	पूर्णांक vec_rx = VECTOR_RX;
	पूर्णांक vec_tx = VECTOR_TX;
	दीर्घ parsed;
	पूर्णांक result = 0;

	अगर (transport == शून्य)
		वापस -EINVAL;

	अगर (vector != शून्य) अणु
		अगर (kम_से_अदीर्घ(vector, 10, &parsed) == 0) अणु
			अगर (parsed == 0) अणु
				vec_rx = 0;
				vec_tx = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (get_bpf_flash(def))
		result = VECTOR_BPF_FLASH;

	अगर (म_भेदन(transport, TRANS_TAP, TRANS_TAP_LEN) == 0)
		वापस result;
	अगर (म_भेदन(transport, TRANS_HYBRID, TRANS_HYBRID_LEN) == 0)
		वापस (result | vec_rx | VECTOR_BPF);
	अगर (म_भेदन(transport, TRANS_RAW, TRANS_RAW_LEN) == 0)
		वापस (result | vec_rx | vec_tx | VECTOR_QDISC_BYPASS);
	वापस (result | vec_rx | vec_tx);
पूर्ण


/* A mini-buffer क्रम packet drop पढ़ो
 * All of our supported transports are datagram oriented and we always
 * पढ़ो using recvmsg or recvmmsg. If we pass a buffer which is smaller
 * than the packet size it still counts as full packet पढ़ो and will
 * clean the incoming stream to keep sigio/epoll happy
 */

#घोषणा DROP_BUFFER_SIZE 32

अटल अक्षर *drop_buffer;

/* Array backed queues optimized क्रम bulk enqueue/dequeue and
 * 1:N (small values of N) or 1:1 enqueuer/dequeuer ratios.
 * For more details and full design rationale see
 * http://foswiki.cambridgegreys.com/Main/EatYourTailAndEnjoyIt
 */


/*
 * Advance the mmsg queue head by n = advance. Resets the queue to
 * maximum enqueue/dequeue-at-once capacity अगर possible. Called by
 * dequeuers. Caller must hold the head_lock!
 */

अटल पूर्णांक vector_advancehead(काष्ठा vector_queue *qi, पूर्णांक advance)
अणु
	पूर्णांक queue_depth;

	qi->head =
		(qi->head + advance)
			% qi->max_depth;


	spin_lock(&qi->tail_lock);
	qi->queue_depth -= advance;

	/* we are at 0, use this to
	 * reset head and tail so we can use max size vectors
	 */

	अगर (qi->queue_depth == 0) अणु
		qi->head = 0;
		qi->tail = 0;
	पूर्ण
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->tail_lock);
	वापस queue_depth;
पूर्ण

/*	Advance the queue tail by n = advance.
 *	This is called by enqueuers which should hold the
 *	head lock alपढ़ोy
 */

अटल पूर्णांक vector_advancetail(काष्ठा vector_queue *qi, पूर्णांक advance)
अणु
	पूर्णांक queue_depth;

	qi->tail =
		(qi->tail + advance)
			% qi->max_depth;
	spin_lock(&qi->head_lock);
	qi->queue_depth += advance;
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->head_lock);
	वापस queue_depth;
पूर्ण

अटल पूर्णांक prep_msg(काष्ठा vector_निजी *vp,
	काष्ठा sk_buff *skb,
	काष्ठा iovec *iov)
अणु
	पूर्णांक iov_index = 0;
	पूर्णांक nr_frags, frag;
	skb_frag_t *skb_frag;

	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (nr_frags > MAX_IOV_SIZE) अणु
		अगर (skb_linearize(skb) != 0)
			जाओ drop;
	पूर्ण
	अगर (vp->header_size > 0) अणु
		iov[iov_index].iov_len = vp->header_size;
		vp->क्रमm_header(iov[iov_index].iov_base, skb, vp);
		iov_index++;
	पूर्ण
	iov[iov_index].iov_base = skb->data;
	अगर (nr_frags > 0) अणु
		iov[iov_index].iov_len = skb->len - skb->data_len;
		vp->estats.sg_ok++;
	पूर्ण अन्यथा
		iov[iov_index].iov_len = skb->len;
	iov_index++;
	क्रम (frag = 0; frag < nr_frags; frag++) अणु
		skb_frag = &skb_shinfo(skb)->frags[frag];
		iov[iov_index].iov_base = skb_frag_address_safe(skb_frag);
		iov[iov_index].iov_len = skb_frag_size(skb_frag);
		iov_index++;
	पूर्ण
	वापस iov_index;
drop:
	वापस -1;
पूर्ण
/*
 * Generic vector enqueue with support क्रम क्रमming headers using transport
 * specअगरic callback. Allows GRE, L2TPv3, RAW and other transports
 * to use a common enqueue procedure in vector mode
 */

अटल पूर्णांक vector_enqueue(काष्ठा vector_queue *qi, काष्ठा sk_buff *skb)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(qi->dev);
	पूर्णांक queue_depth;
	पूर्णांक packet_len;
	काष्ठा mmsghdr *mmsg_vector = qi->mmsg_vector;
	पूर्णांक iov_count;

	spin_lock(&qi->tail_lock);
	spin_lock(&qi->head_lock);
	queue_depth = qi->queue_depth;
	spin_unlock(&qi->head_lock);

	अगर (skb)
		packet_len = skb->len;

	अगर (queue_depth < qi->max_depth) अणु

		*(qi->skbuff_vector + qi->tail) = skb;
		mmsg_vector += qi->tail;
		iov_count = prep_msg(
			vp,
			skb,
			mmsg_vector->msg_hdr.msg_iov
		);
		अगर (iov_count < 1)
			जाओ drop;
		mmsg_vector->msg_hdr.msg_iovlen = iov_count;
		mmsg_vector->msg_hdr.msg_name = vp->fds->remote_addr;
		mmsg_vector->msg_hdr.msg_namelen = vp->fds->remote_addr_size;
		queue_depth = vector_advancetail(qi, 1);
	पूर्ण अन्यथा
		जाओ drop;
	spin_unlock(&qi->tail_lock);
	वापस queue_depth;
drop:
	qi->dev->stats.tx_dropped++;
	अगर (skb != शून्य) अणु
		packet_len = skb->len;
		dev_consume_skb_any(skb);
		netdev_completed_queue(qi->dev, 1, packet_len);
	पूर्ण
	spin_unlock(&qi->tail_lock);
	वापस queue_depth;
पूर्ण

अटल पूर्णांक consume_vector_skbs(काष्ठा vector_queue *qi, पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक skb_index;
	पूर्णांक bytes_compl = 0;

	क्रम (skb_index = qi->head; skb_index < qi->head + count; skb_index++) अणु
		skb = *(qi->skbuff_vector + skb_index);
		/* mark as empty to ensure correct deकाष्ठाion अगर
		 * needed
		 */
		bytes_compl += skb->len;
		*(qi->skbuff_vector + skb_index) = शून्य;
		dev_consume_skb_any(skb);
	पूर्ण
	qi->dev->stats.tx_bytes += bytes_compl;
	qi->dev->stats.tx_packets += count;
	netdev_completed_queue(qi->dev, count, bytes_compl);
	वापस vector_advancehead(qi, count);
पूर्ण

/*
 * Generic vector deque via sendmmsg with support क्रम क्रमming headers
 * using transport specअगरic callback. Allows GRE, L2TPv3, RAW and
 * other transports to use a common dequeue procedure in vector mode
 */


अटल पूर्णांक vector_send(काष्ठा vector_queue *qi)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(qi->dev);
	काष्ठा mmsghdr *send_from;
	पूर्णांक result = 0, send_len, queue_depth = qi->max_depth;

	अगर (spin_trylock(&qi->head_lock)) अणु
		अगर (spin_trylock(&qi->tail_lock)) अणु
			/* update queue_depth to current value */
			queue_depth = qi->queue_depth;
			spin_unlock(&qi->tail_lock);
			जबतक (queue_depth > 0) अणु
				/* Calculate the start of the vector */
				send_len = queue_depth;
				send_from = qi->mmsg_vector;
				send_from += qi->head;
				/* Adjust vector size अगर wraparound */
				अगर (send_len + qi->head > qi->max_depth)
					send_len = qi->max_depth - qi->head;
				/* Try to TX as many packets as possible */
				अगर (send_len > 0) अणु
					result = uml_vector_sendmmsg(
						 vp->fds->tx_fd,
						 send_from,
						 send_len,
						 0
					);
					vp->in_ग_लिखो_poll =
						(result != send_len);
				पूर्ण
				/* For some of the sendmmsg error scenarios
				 * we may end being unsure in the TX success
				 * क्रम all packets. It is safer to declare
				 * them all TX-ed and blame the network.
				 */
				अगर (result < 0) अणु
					अगर (net_ratelimit())
						netdev_err(vp->dev, "sendmmsg err=%i\n",
							result);
					vp->in_error = true;
					result = send_len;
				पूर्ण
				अगर (result > 0) अणु
					queue_depth =
						consume_vector_skbs(qi, result);
					/* This is equivalent to an TX IRQ.
					 * Restart the upper layers to feed us
					 * more packets.
					 */
					अगर (result > vp->estats.tx_queue_max)
						vp->estats.tx_queue_max = result;
					vp->estats.tx_queue_running_average =
						(vp->estats.tx_queue_running_average + result) >> 1;
				पूर्ण
				netअगर_trans_update(qi->dev);
				netअगर_wake_queue(qi->dev);
				/* अगर TX is busy, अवरोध out of the send loop,
				 *  poll ग_लिखो IRQ will reschedule xmit क्रम us
				 */
				अगर (result != send_len) अणु
					vp->estats.tx_restart_queue++;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock(&qi->head_lock);
	पूर्ण अन्यथा अणु
		tasklet_schedule(&vp->tx_poll);
	पूर्ण
	वापस queue_depth;
पूर्ण

/* Queue deकाष्ठाor. Deliberately stateless so we can use
 * it in queue cleanup अगर initialization fails.
 */

अटल व्योम destroy_queue(काष्ठा vector_queue *qi)
अणु
	पूर्णांक i;
	काष्ठा iovec *iov;
	काष्ठा vector_निजी *vp = netdev_priv(qi->dev);
	काष्ठा mmsghdr *mmsg_vector;

	अगर (qi == शून्य)
		वापस;
	/* deallocate any skbuffs - we rely on any unused to be
	 * set to शून्य.
	 */
	अगर (qi->skbuff_vector != शून्य) अणु
		क्रम (i = 0; i < qi->max_depth; i++) अणु
			अगर (*(qi->skbuff_vector + i) != शून्य)
				dev_kमुक्त_skb_any(*(qi->skbuff_vector + i));
		पूर्ण
		kमुक्त(qi->skbuff_vector);
	पूर्ण
	/* deallocate matching IOV काष्ठाures including header buffs */
	अगर (qi->mmsg_vector != शून्य) अणु
		mmsg_vector = qi->mmsg_vector;
		क्रम (i = 0; i < qi->max_depth; i++) अणु
			iov = mmsg_vector->msg_hdr.msg_iov;
			अगर (iov != शून्य) अणु
				अगर ((vp->header_size > 0) &&
					(iov->iov_base != शून्य))
					kमुक्त(iov->iov_base);
				kमुक्त(iov);
			पूर्ण
			mmsg_vector++;
		पूर्ण
		kमुक्त(qi->mmsg_vector);
	पूर्ण
	kमुक्त(qi);
पूर्ण

/*
 * Queue स्थिरructor. Create a queue with a given side.
 */
अटल काष्ठा vector_queue *create_queue(
	काष्ठा vector_निजी *vp,
	पूर्णांक max_size,
	पूर्णांक header_size,
	पूर्णांक num_extra_frags)
अणु
	काष्ठा vector_queue *result;
	पूर्णांक i;
	काष्ठा iovec *iov;
	काष्ठा mmsghdr *mmsg_vector;

	result = kदो_स्मृति(माप(काष्ठा vector_queue), GFP_KERNEL);
	अगर (result == शून्य)
		वापस शून्य;
	result->max_depth = max_size;
	result->dev = vp->dev;
	result->mmsg_vector = kदो_स्मृति(
		(माप(काष्ठा mmsghdr) * max_size), GFP_KERNEL);
	अगर (result->mmsg_vector == शून्य)
		जाओ out_mmsg_fail;
	result->skbuff_vector = kदो_स्मृति(
		(माप(व्योम *) * max_size), GFP_KERNEL);
	अगर (result->skbuff_vector == शून्य)
		जाओ out_skb_fail;

	/* further failures can be handled safely by destroy_queue*/

	mmsg_vector = result->mmsg_vector;
	क्रम (i = 0; i < max_size; i++) अणु
		/* Clear all poपूर्णांकers - we use non-शून्य as marking on
		 * what to मुक्त on deकाष्ठाion
		 */
		*(result->skbuff_vector + i) = शून्य;
		mmsg_vector->msg_hdr.msg_iov = शून्य;
		mmsg_vector++;
	पूर्ण
	mmsg_vector = result->mmsg_vector;
	result->max_iov_frags = num_extra_frags;
	क्रम (i = 0; i < max_size; i++) अणु
		अगर (vp->header_size > 0)
			iov = kदो_स्मृति_array(3 + num_extra_frags,
					    माप(काष्ठा iovec),
					    GFP_KERNEL
			);
		अन्यथा
			iov = kदो_स्मृति_array(2 + num_extra_frags,
					    माप(काष्ठा iovec),
					    GFP_KERNEL
			);
		अगर (iov == शून्य)
			जाओ out_fail;
		mmsg_vector->msg_hdr.msg_iov = iov;
		mmsg_vector->msg_hdr.msg_iovlen = 1;
		mmsg_vector->msg_hdr.msg_control = शून्य;
		mmsg_vector->msg_hdr.msg_controllen = 0;
		mmsg_vector->msg_hdr.msg_flags = MSG_DONTWAIT;
		mmsg_vector->msg_hdr.msg_name = शून्य;
		mmsg_vector->msg_hdr.msg_namelen = 0;
		अगर (vp->header_size > 0) अणु
			iov->iov_base = kदो_स्मृति(header_size, GFP_KERNEL);
			अगर (iov->iov_base == शून्य)
				जाओ out_fail;
			iov->iov_len = header_size;
			mmsg_vector->msg_hdr.msg_iovlen = 2;
			iov++;
		पूर्ण
		iov->iov_base = शून्य;
		iov->iov_len = 0;
		mmsg_vector++;
	पूर्ण
	spin_lock_init(&result->head_lock);
	spin_lock_init(&result->tail_lock);
	result->queue_depth = 0;
	result->head = 0;
	result->tail = 0;
	वापस result;
out_skb_fail:
	kमुक्त(result->mmsg_vector);
out_mmsg_fail:
	kमुक्त(result);
	वापस शून्य;
out_fail:
	destroy_queue(result);
	वापस शून्य;
पूर्ण

/*
 * We करो not use the RX queue as a proper wraparound queue क्रम now
 * This is not necessary because the consumption via netअगर_rx()
 * happens in-line. While we can try using the वापस code of
 * netअगर_rx() क्रम flow control there are no drivers करोing this today.
 * For this RX specअगरic use we ignore the tail/head locks and
 * just पढ़ो पूर्णांकo a prepared queue filled with skbuffs.
 */

अटल काष्ठा sk_buff *prep_skb(
	काष्ठा vector_निजी *vp,
	काष्ठा user_msghdr *msg)
अणु
	पूर्णांक linear = vp->max_packet + vp->headroom + SAFETY_MARGIN;
	काष्ठा sk_buff *result;
	पूर्णांक iov_index = 0, len;
	काष्ठा iovec *iov = msg->msg_iov;
	पूर्णांक err, nr_frags, frag;
	skb_frag_t *skb_frag;

	अगर (vp->req_size <= linear)
		len = linear;
	अन्यथा
		len = vp->req_size;
	result = alloc_skb_with_frags(
		linear,
		len - vp->max_packet,
		3,
		&err,
		GFP_ATOMIC
	);
	अगर (vp->header_size > 0)
		iov_index++;
	अगर (result == शून्य) अणु
		iov[iov_index].iov_base = शून्य;
		iov[iov_index].iov_len = 0;
		जाओ करोne;
	पूर्ण
	skb_reserve(result, vp->headroom);
	result->dev = vp->dev;
	skb_put(result, vp->max_packet);
	result->data_len = len - vp->max_packet;
	result->len += len - vp->max_packet;
	skb_reset_mac_header(result);
	result->ip_summed = CHECKSUM_NONE;
	iov[iov_index].iov_base = result->data;
	iov[iov_index].iov_len = vp->max_packet;
	iov_index++;

	nr_frags = skb_shinfo(result)->nr_frags;
	क्रम (frag = 0; frag < nr_frags; frag++) अणु
		skb_frag = &skb_shinfo(result)->frags[frag];
		iov[iov_index].iov_base = skb_frag_address_safe(skb_frag);
		अगर (iov[iov_index].iov_base != शून्य)
			iov[iov_index].iov_len = skb_frag_size(skb_frag);
		अन्यथा
			iov[iov_index].iov_len = 0;
		iov_index++;
	पूर्ण
करोne:
	msg->msg_iovlen = iov_index;
	वापस result;
पूर्ण


/* Prepare queue क्रम recvmmsg one-shot rx - fill with fresh sk_buffs*/

अटल व्योम prep_queue_क्रम_rx(काष्ठा vector_queue *qi)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(qi->dev);
	काष्ठा mmsghdr *mmsg_vector = qi->mmsg_vector;
	व्योम **skbuff_vector = qi->skbuff_vector;
	पूर्णांक i;

	अगर (qi->queue_depth == 0)
		वापस;
	क्रम (i = 0; i < qi->queue_depth; i++) अणु
		/* it is OK अगर allocation fails - recvmmsg with शून्य data in
		 * iov argument still perक्रमms an RX, just drops the packet
		 * This allows us stop faffing around with a "drop buffer"
		 */

		*skbuff_vector = prep_skb(vp, &mmsg_vector->msg_hdr);
		skbuff_vector++;
		mmsg_vector++;
	पूर्ण
	qi->queue_depth = 0;
पूर्ण

अटल काष्ठा vector_device *find_device(पूर्णांक n)
अणु
	काष्ठा vector_device *device;
	काष्ठा list_head *ele;

	spin_lock(&vector_devices_lock);
	list_क्रम_each(ele, &vector_devices) अणु
		device = list_entry(ele, काष्ठा vector_device, list);
		अगर (device->unit == n)
			जाओ out;
	पूर्ण
	device = शून्य;
 out:
	spin_unlock(&vector_devices_lock);
	वापस device;
पूर्ण

अटल पूर्णांक vector_parse(अक्षर *str, पूर्णांक *index_out, अक्षर **str_out,
			अक्षर **error_out)
अणु
	पूर्णांक n, len, err;
	अक्षर *start = str;

	len = म_माप(str);

	जबतक ((*str != ':') && (म_माप(str) > 1))
		str++;
	अगर (*str != ':') अणु
		*error_out = "Expected ':' after device number";
		वापस -EINVAL;
	पूर्ण
	*str = '\0';

	err = kstrtouपूर्णांक(start, 0, &n);
	अगर (err < 0) अणु
		*error_out = "Bad device number";
		वापस err;
	पूर्ण

	str++;
	अगर (find_device(n)) अणु
		*error_out = "Device already configured";
		वापस -EINVAL;
	पूर्ण

	*index_out = n;
	*str_out = str;
	वापस 0;
पूर्ण

अटल पूर्णांक vector_config(अक्षर *str, अक्षर **error_out)
अणु
	पूर्णांक err, n;
	अक्षर *params;
	काष्ठा arglist *parsed;

	err = vector_parse(str, &n, &params, error_out);
	अगर (err != 0)
		वापस err;

	/* This string is broken up and the pieces used by the underlying
	 * driver. We should copy it to make sure things करो not go wrong
	 * later.
	 */

	params = kstrdup(params, GFP_KERNEL);
	अगर (params == शून्य) अणु
		*error_out = "vector_config failed to strdup string";
		वापस -ENOMEM;
	पूर्ण

	parsed = uml_parse_vector_अगरspec(params);

	अगर (parsed == शून्य) अणु
		*error_out = "vector_config failed to parse parameters";
		वापस -EINVAL;
	पूर्ण

	vector_eth_configure(n, parsed);
	वापस 0;
पूर्ण

अटल पूर्णांक vector_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out)
अणु
	अक्षर *end;
	पूर्णांक n;

	n = simple_म_से_अदीर्घ(*str, &end, 0);
	अगर ((*end != '\0') || (end == *str))
		वापस -1;

	*start_out = n;
	*end_out = n;
	*str = end;
	वापस n;
पूर्ण

अटल पूर्णांक vector_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	काष्ठा vector_device *vec_d;
	काष्ठा net_device *dev;
	काष्ठा vector_निजी *vp;

	vec_d = find_device(n);
	अगर (vec_d == शून्य)
		वापस -ENODEV;
	dev = vec_d->dev;
	vp = netdev_priv(dev);
	अगर (vp->fds != शून्य)
		वापस -EBUSY;
	unरेजिस्टर_netdev(dev);
	platक्रमm_device_unरेजिस्टर(&vec_d->pdev);
	वापस 0;
पूर्ण

/*
 * There is no shared per-transport initialization code, so
 * we will just initialize each पूर्णांकerface one by one and
 * add them to a list
 */

अटल काष्ठा platक्रमm_driver uml_net_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
	पूर्ण,
पूर्ण;


अटल व्योम vector_device_release(काष्ठा device *dev)
अणु
	काष्ठा vector_device *device = dev_get_drvdata(dev);
	काष्ठा net_device *netdev = device->dev;

	list_del(&device->list);
	kमुक्त(device);
	मुक्त_netdev(netdev);
पूर्ण

/* Bog standard recv using recvmsg - not used normally unless the user
 * explicitly specअगरies not to use recvmmsg vector RX.
 */

अटल पूर्णांक vector_legacy_rx(काष्ठा vector_निजी *vp)
अणु
	पूर्णांक pkt_len;
	काष्ठा user_msghdr hdr;
	काष्ठा iovec iov[2 + MAX_IOV_SIZE]; /* header + data use हाल only */
	पूर्णांक iovpos = 0;
	काष्ठा sk_buff *skb;
	पूर्णांक header_check;

	hdr.msg_name = शून्य;
	hdr.msg_namelen = 0;
	hdr.msg_iov = (काष्ठा iovec *) &iov;
	hdr.msg_control = शून्य;
	hdr.msg_controllen = 0;
	hdr.msg_flags = 0;

	अगर (vp->header_size > 0) अणु
		iov[0].iov_base = vp->header_rxbuffer;
		iov[0].iov_len = vp->header_size;
	पूर्ण

	skb = prep_skb(vp, &hdr);

	अगर (skb == शून्य) अणु
		/* Read a packet पूर्णांकo drop_buffer and करोn't करो
		 * anything with it.
		 */
		iov[iovpos].iov_base = drop_buffer;
		iov[iovpos].iov_len = DROP_BUFFER_SIZE;
		hdr.msg_iovlen = 1;
		vp->dev->stats.rx_dropped++;
	पूर्ण

	pkt_len = uml_vector_recvmsg(vp->fds->rx_fd, &hdr, 0);
	अगर (pkt_len < 0) अणु
		vp->in_error = true;
		वापस pkt_len;
	पूर्ण

	अगर (skb != शून्य) अणु
		अगर (pkt_len > vp->header_size) अणु
			अगर (vp->header_size > 0) अणु
				header_check = vp->verअगरy_header(
					vp->header_rxbuffer, skb, vp);
				अगर (header_check < 0) अणु
					dev_kमुक्त_skb_irq(skb);
					vp->dev->stats.rx_dropped++;
					vp->estats.rx_encaps_errors++;
					वापस 0;
				पूर्ण
				अगर (header_check > 0) अणु
					vp->estats.rx_csum_offload_good++;
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				पूर्ण
			पूर्ण
			pskb_trim(skb, pkt_len - vp->rx_header_size);
			skb->protocol = eth_type_trans(skb, skb->dev);
			vp->dev->stats.rx_bytes += skb->len;
			vp->dev->stats.rx_packets++;
			netअगर_rx(skb);
		पूर्ण अन्यथा अणु
			dev_kमुक्त_skb_irq(skb);
		पूर्ण
	पूर्ण
	वापस pkt_len;
पूर्ण

/*
 * Packet at a समय TX which falls back to vector TX अगर the
 * underlying transport is busy.
 */



अटल पूर्णांक ग_लिखोv_tx(काष्ठा vector_निजी *vp, काष्ठा sk_buff *skb)
अणु
	काष्ठा iovec iov[3 + MAX_IOV_SIZE];
	पूर्णांक iov_count, pkt_len = 0;

	iov[0].iov_base = vp->header_txbuffer;
	iov_count = prep_msg(vp, skb, (काष्ठा iovec *) &iov);

	अगर (iov_count < 1)
		जाओ drop;

	pkt_len = uml_vector_ग_लिखोv(
		vp->fds->tx_fd,
		(काष्ठा iovec *) &iov,
		iov_count
	);

	अगर (pkt_len < 0)
		जाओ drop;

	netअगर_trans_update(vp->dev);
	netअगर_wake_queue(vp->dev);

	अगर (pkt_len > 0) अणु
		vp->dev->stats.tx_bytes += skb->len;
		vp->dev->stats.tx_packets++;
	पूर्ण अन्यथा अणु
		vp->dev->stats.tx_dropped++;
	पूर्ण
	consume_skb(skb);
	वापस pkt_len;
drop:
	vp->dev->stats.tx_dropped++;
	consume_skb(skb);
	अगर (pkt_len < 0)
		vp->in_error = true;
	वापस pkt_len;
पूर्ण

/*
 * Receive as many messages as we can in one call using the special
 * mmsg vector matched to an skb vector which we prepared earlier.
 */

अटल पूर्णांक vector_mmsg_rx(काष्ठा vector_निजी *vp)
अणु
	पूर्णांक packet_count, i;
	काष्ठा vector_queue *qi = vp->rx_queue;
	काष्ठा sk_buff *skb;
	काष्ठा mmsghdr *mmsg_vector = qi->mmsg_vector;
	व्योम **skbuff_vector = qi->skbuff_vector;
	पूर्णांक header_check;

	/* Refresh the vector and make sure it is with new skbs and the
	 * iovs are updated to poपूर्णांक to them.
	 */

	prep_queue_क्रम_rx(qi);

	/* Fire the Lazy Gun - get as many packets as we can in one go. */

	packet_count = uml_vector_recvmmsg(
		vp->fds->rx_fd, qi->mmsg_vector, qi->max_depth, 0);

	अगर (packet_count < 0)
		vp->in_error = true;

	अगर (packet_count <= 0)
		वापस packet_count;

	/* We treat packet processing as enqueue, buffer refresh as dequeue
	 * The queue_depth tells us how many buffers have been used and how
	 * many करो we need to prep the next समय prep_queue_क्रम_rx() is called.
	 */

	qi->queue_depth = packet_count;

	क्रम (i = 0; i < packet_count; i++) अणु
		skb = (*skbuff_vector);
		अगर (mmsg_vector->msg_len > vp->header_size) अणु
			अगर (vp->header_size > 0) अणु
				header_check = vp->verअगरy_header(
					mmsg_vector->msg_hdr.msg_iov->iov_base,
					skb,
					vp
				);
				अगर (header_check < 0) अणु
				/* Overlay header failed to verअगरy - discard.
				 * We can actually keep this skb and reuse it,
				 * but that will make the prep logic too
				 * complex.
				 */
					dev_kमुक्त_skb_irq(skb);
					vp->estats.rx_encaps_errors++;
					जारी;
				पूर्ण
				अगर (header_check > 0) अणु
					vp->estats.rx_csum_offload_good++;
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				पूर्ण
			पूर्ण
			pskb_trim(skb,
				mmsg_vector->msg_len - vp->rx_header_size);
			skb->protocol = eth_type_trans(skb, skb->dev);
			/*
			 * We करो not need to lock on updating stats here
			 * The पूर्णांकerrupt loop is non-reentrant.
			 */
			vp->dev->stats.rx_bytes += skb->len;
			vp->dev->stats.rx_packets++;
			netअगर_rx(skb);
		पूर्ण अन्यथा अणु
			/* Overlay header too लघु to करो anything - discard.
			 * We can actually keep this skb and reuse it,
			 * but that will make the prep logic too complex.
			 */
			अगर (skb != शून्य)
				dev_kमुक्त_skb_irq(skb);
		पूर्ण
		(*skbuff_vector) = शून्य;
		/* Move to the next buffer element */
		mmsg_vector++;
		skbuff_vector++;
	पूर्ण
	अगर (packet_count > 0) अणु
		अगर (vp->estats.rx_queue_max < packet_count)
			vp->estats.rx_queue_max = packet_count;
		vp->estats.rx_queue_running_average =
			(vp->estats.rx_queue_running_average + packet_count) >> 1;
	पूर्ण
	वापस packet_count;
पूर्ण

अटल व्योम vector_rx(काष्ठा vector_निजी *vp)
अणु
	पूर्णांक err;
	पूर्णांक iter = 0;

	अगर ((vp->options & VECTOR_RX) > 0)
		जबतक (((err = vector_mmsg_rx(vp)) > 0) && (iter < MAX_ITERATIONS))
			iter++;
	अन्यथा
		जबतक (((err = vector_legacy_rx(vp)) > 0) && (iter < MAX_ITERATIONS))
			iter++;
	अगर ((err != 0) && net_ratelimit())
		netdev_err(vp->dev, "vector_rx: error(%d)\n", err);
	अगर (iter == MAX_ITERATIONS)
		netdev_err(vp->dev, "vector_rx: device stuck, remote end may have closed the connection\n");
पूर्ण

अटल पूर्णांक vector_net_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);
	पूर्णांक queue_depth = 0;

	अगर (vp->in_error) अणु
		deactivate_fd(vp->fds->rx_fd, vp->rx_irq);
		अगर ((vp->fds->rx_fd != vp->fds->tx_fd) && (vp->tx_irq != 0))
			deactivate_fd(vp->fds->tx_fd, vp->tx_irq);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर ((vp->options & VECTOR_TX) == 0) अणु
		ग_लिखोv_tx(vp, skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* We करो BQL only in the vector path, no poपूर्णांक करोing it in
	 * packet at a समय mode as there is no device queue
	 */

	netdev_sent_queue(vp->dev, skb->len);
	queue_depth = vector_enqueue(vp->tx_queue, skb);

	/* अगर the device queue is full, stop the upper layers and
	 * flush it.
	 */

	अगर (queue_depth >= vp->tx_queue->max_depth - 1) अणु
		vp->estats.tx_kicks++;
		netअगर_stop_queue(dev);
		vector_send(vp->tx_queue);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (netdev_xmit_more()) अणु
		mod_समयr(&vp->tl, vp->coalesce);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (skb->len < TX_SMALL_PACKET) अणु
		vp->estats.tx_kicks++;
		vector_send(vp->tx_queue);
	पूर्ण अन्यथा
		tasklet_schedule(&vp->tx_poll);
	वापस NETDEV_TX_OK;
पूर्ण

अटल irqवापस_t vector_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा vector_निजी *vp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस IRQ_NONE;
	vector_rx(vp);
	वापस IRQ_HANDLED;

पूर्ण

अटल irqवापस_t vector_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा vector_निजी *vp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस IRQ_NONE;
	/* We need to pay attention to it only अगर we got
	 * -EAGAIN or -ENOBUFFS from sendmmsg. Otherwise
	 * we ignore it. In the future, it may be worth
	 * it to improve the IRQ controller a bit to make
	 * tweaking the IRQ mask less costly
	 */

	अगर (vp->in_ग_लिखो_poll)
		tasklet_schedule(&vp->tx_poll);
	वापस IRQ_HANDLED;

पूर्ण

अटल पूर्णांक irq_rr;

अटल पूर्णांक vector_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);
	del_समयr(&vp->tl);

	अगर (vp->fds == शून्य)
		वापस 0;

	/* Disable and मुक्त all IRQS */
	अगर (vp->rx_irq > 0) अणु
		um_मुक्त_irq(vp->rx_irq, dev);
		vp->rx_irq = 0;
	पूर्ण
	अगर (vp->tx_irq > 0) अणु
		um_मुक्त_irq(vp->tx_irq, dev);
		vp->tx_irq = 0;
	पूर्ण
	tasklet_समाप्त(&vp->tx_poll);
	अगर (vp->fds->rx_fd > 0) अणु
		अगर (vp->bpf)
			uml_vector_detach_bpf(vp->fds->rx_fd, vp->bpf);
		os_बंद_file(vp->fds->rx_fd);
		vp->fds->rx_fd = -1;
	पूर्ण
	अगर (vp->fds->tx_fd > 0) अणु
		os_बंद_file(vp->fds->tx_fd);
		vp->fds->tx_fd = -1;
	पूर्ण
	अगर (vp->bpf != शून्य)
		kमुक्त(vp->bpf->filter);
	kमुक्त(vp->bpf);
	vp->bpf = शून्य;
	kमुक्त(vp->fds->remote_addr);
	kमुक्त(vp->transport_data);
	kमुक्त(vp->header_rxbuffer);
	kमुक्त(vp->header_txbuffer);
	अगर (vp->rx_queue != शून्य)
		destroy_queue(vp->rx_queue);
	अगर (vp->tx_queue != शून्य)
		destroy_queue(vp->tx_queue);
	kमुक्त(vp->fds);
	vp->fds = शून्य;
	spin_lock_irqsave(&vp->lock, flags);
	vp->खोलोed = false;
	vp->in_error = false;
	spin_unlock_irqrestore(&vp->lock, flags);
	वापस 0;
पूर्ण

/* TX tasklet */

अटल व्योम vector_tx_poll(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा vector_निजी *vp = from_tasklet(vp, t, tx_poll);

	vp->estats.tx_kicks++;
	vector_send(vp->tx_queue);
पूर्ण
अटल व्योम vector_reset_tx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vector_निजी *vp =
		container_of(work, काष्ठा vector_निजी, reset_tx);
	netdev_reset_queue(vp->dev);
	netअगर_start_queue(vp->dev);
	netअगर_wake_queue(vp->dev);
पूर्ण

अटल पूर्णांक vector_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err = -EINVAL;
	काष्ठा vector_device *vdevice;

	spin_lock_irqsave(&vp->lock, flags);
	अगर (vp->खोलोed) अणु
		spin_unlock_irqrestore(&vp->lock, flags);
		वापस -ENXIO;
	पूर्ण
	vp->खोलोed = true;
	spin_unlock_irqrestore(&vp->lock, flags);

	vp->bpf = uml_vector_user_bpf(get_bpf_file(vp->parsed));

	vp->fds = uml_vector_user_खोलो(vp->unit, vp->parsed);

	अगर (vp->fds == शून्य)
		जाओ out_बंद;

	अगर (build_transport_data(vp) < 0)
		जाओ out_बंद;

	अगर ((vp->options & VECTOR_RX) > 0) अणु
		vp->rx_queue = create_queue(
			vp,
			get_depth(vp->parsed),
			vp->rx_header_size,
			MAX_IOV_SIZE
		);
		vp->rx_queue->queue_depth = get_depth(vp->parsed);
	पूर्ण अन्यथा अणु
		vp->header_rxbuffer = kदो_स्मृति(
			vp->rx_header_size,
			GFP_KERNEL
		);
		अगर (vp->header_rxbuffer == शून्य)
			जाओ out_बंद;
	पूर्ण
	अगर ((vp->options & VECTOR_TX) > 0) अणु
		vp->tx_queue = create_queue(
			vp,
			get_depth(vp->parsed),
			vp->header_size,
			MAX_IOV_SIZE
		);
	पूर्ण अन्यथा अणु
		vp->header_txbuffer = kदो_स्मृति(vp->header_size, GFP_KERNEL);
		अगर (vp->header_txbuffer == शून्य)
			जाओ out_बंद;
	पूर्ण

	/* READ IRQ */
	err = um_request_irq(
		irq_rr + VECTOR_BASE_IRQ, vp->fds->rx_fd,
			IRQ_READ, vector_rx_पूर्णांकerrupt,
			IRQF_SHARED, dev->name, dev);
	अगर (err < 0) अणु
		netdev_err(dev, "vector_open: failed to get rx irq(%d)\n", err);
		err = -ENETUNREACH;
		जाओ out_बंद;
	पूर्ण
	vp->rx_irq = irq_rr + VECTOR_BASE_IRQ;
	dev->irq = irq_rr + VECTOR_BASE_IRQ;
	irq_rr = (irq_rr + 1) % VECTOR_IRQ_SPACE;

	/* WRITE IRQ - we need it only अगर we have vector TX */
	अगर ((vp->options & VECTOR_TX) > 0) अणु
		err = um_request_irq(
			irq_rr + VECTOR_BASE_IRQ, vp->fds->tx_fd,
				IRQ_WRITE, vector_tx_पूर्णांकerrupt,
				IRQF_SHARED, dev->name, dev);
		अगर (err < 0) अणु
			netdev_err(dev,
				"vector_open: failed to get tx irq(%d)\n", err);
			err = -ENETUNREACH;
			जाओ out_बंद;
		पूर्ण
		vp->tx_irq = irq_rr + VECTOR_BASE_IRQ;
		irq_rr = (irq_rr + 1) % VECTOR_IRQ_SPACE;
	पूर्ण

	अगर ((vp->options & VECTOR_QDISC_BYPASS) != 0) अणु
		अगर (!uml_raw_enable_qdisc_bypass(vp->fds->rx_fd))
			vp->options |= VECTOR_BPF;
	पूर्ण
	अगर (((vp->options & VECTOR_BPF) != 0) && (vp->bpf == शून्य))
		vp->bpf = uml_vector_शेष_bpf(dev->dev_addr);

	अगर (vp->bpf != शून्य)
		uml_vector_attach_bpf(vp->fds->rx_fd, vp->bpf);

	netअगर_start_queue(dev);

	/* clear buffer - it can happen that the host side of the पूर्णांकerface
	 * is full when we get here. In this हाल, new data is never queued,
	 * SIGIOs never arrive, and the net never works.
	 */

	vector_rx(vp);

	vector_reset_stats(vp);
	vdevice = find_device(vp->unit);
	vdevice->खोलोed = 1;

	अगर ((vp->options & VECTOR_TX) != 0)
		add_समयr(&vp->tl);
	वापस 0;
out_बंद:
	vector_net_बंद(dev);
	वापस err;
पूर्ण


अटल व्योम vector_net_set_multicast_list(काष्ठा net_device *dev)
अणु
	/* TODO: - we can करो some BPF games here */
	वापस;
पूर्ण

अटल व्योम vector_net_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);

	vp->estats.tx_समयout_count++;
	netअगर_trans_update(dev);
	schedule_work(&vp->reset_tx);
पूर्ण

अटल netdev_features_t vector_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	features &= ~(NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	वापस features;
पूर्ण

अटल पूर्णांक vector_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);
	/* Adjust buffer sizes क्रम GSO/GRO. Unक्रमtunately, there is
	 * no way to negotiate it on raw sockets, so we can change
	 * only our side.
	 */
	अगर (features & NETIF_F_GRO)
		/* All new frame buffers will be GRO-sized */
		vp->req_size = 65536;
	अन्यथा
		/* All new frame buffers will be normal sized */
		vp->req_size = vp->max_packet + vp->headroom + SAFETY_MARGIN;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम vector_net_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	vector_rx_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम vector_net_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
पूर्ण

अटल पूर्णांक vector_net_load_bpf_flash(काष्ठा net_device *dev,
				काष्ठा ethtool_flash *efl)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);
	काष्ठा vector_device *vdevice;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक result = 0;

	अगर (!(vp->options & VECTOR_BPF_FLASH)) अणु
		netdev_err(dev, "loading firmware not permitted: %s\n", efl->data);
		वापस -1;
	पूर्ण

	spin_lock(&vp->lock);

	अगर (vp->bpf != शून्य) अणु
		अगर (vp->खोलोed)
			uml_vector_detach_bpf(vp->fds->rx_fd, vp->bpf);
		kमुक्त(vp->bpf->filter);
		vp->bpf->filter = शून्य;
	पूर्ण अन्यथा अणु
		vp->bpf = kदो_स्मृति(माप(काष्ठा sock_fprog), GFP_ATOMIC);
		अगर (vp->bpf == शून्य) अणु
			netdev_err(dev, "failed to allocate memory for firmware\n");
			जाओ flash_fail;
		पूर्ण
	पूर्ण

	vdevice = find_device(vp->unit);

	अगर (request_firmware(&fw, efl->data, &vdevice->pdev.dev))
		जाओ flash_fail;

	vp->bpf->filter = kmemdup(fw->data, fw->size, GFP_ATOMIC);
	अगर (!vp->bpf->filter)
		जाओ मुक्त_buffer;

	vp->bpf->len = fw->size / माप(काष्ठा sock_filter);
	release_firmware(fw);

	अगर (vp->खोलोed)
		result = uml_vector_attach_bpf(vp->fds->rx_fd, vp->bpf);

	spin_unlock(&vp->lock);

	वापस result;

मुक्त_buffer:
	release_firmware(fw);

flash_fail:
	spin_unlock(&vp->lock);
	अगर (vp->bpf != शून्य)
		kमुक्त(vp->bpf->filter);
	kमुक्त(vp->bpf);
	vp->bpf = शून्य;
	वापस -1;
पूर्ण

अटल व्योम vector_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(netdev);

	ring->rx_max_pending = vp->rx_queue->max_depth;
	ring->tx_max_pending = vp->tx_queue->max_depth;
	ring->rx_pending = vp->rx_queue->max_depth;
	ring->tx_pending = vp->tx_queue->max_depth;
पूर्ण

अटल व्योम vector_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		*buf = '\0';
		अवरोध;
	हाल ETH_SS_STATS:
		स_नकल(buf, &ethtool_stats_keys, माप(ethtool_stats_keys));
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक vector_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस 0;
	हाल ETH_SS_STATS:
		वापस VECTOR_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम vector_get_ethtool_stats(काष्ठा net_device *dev,
	काष्ठा ethtool_stats *estats,
	u64 *पंचांगp_stats)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(dev);

	स_नकल(पंचांगp_stats, &vp->estats, माप(काष्ठा vector_estats));
पूर्ण

अटल पूर्णांक vector_get_coalesce(काष्ठा net_device *netdev,
					काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(netdev);

	ec->tx_coalesce_usecs = (vp->coalesce * 1000000) / HZ;
	वापस 0;
पूर्ण

अटल पूर्णांक vector_set_coalesce(काष्ठा net_device *netdev,
					काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा vector_निजी *vp = netdev_priv(netdev);

	vp->coalesce = (ec->tx_coalesce_usecs * HZ) / 1000000;
	अगर (vp->coalesce == 0)
		vp->coalesce = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vector_net_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_TX_USECS,
	.get_drvinfo	= vector_net_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_ts_info	= ethtool_op_get_ts_info,
	.get_ringparam	= vector_get_ringparam,
	.get_strings	= vector_get_strings,
	.get_sset_count	= vector_get_sset_count,
	.get_ethtool_stats = vector_get_ethtool_stats,
	.get_coalesce	= vector_get_coalesce,
	.set_coalesce	= vector_set_coalesce,
	.flash_device	= vector_net_load_bpf_flash,
पूर्ण;


अटल स्थिर काष्ठा net_device_ops vector_netdev_ops = अणु
	.nकरो_खोलो		= vector_net_खोलो,
	.nकरो_stop		= vector_net_बंद,
	.nकरो_start_xmit		= vector_net_start_xmit,
	.nकरो_set_rx_mode	= vector_net_set_multicast_list,
	.nकरो_tx_समयout		= vector_net_tx_समयout,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_fix_features	= vector_fix_features,
	.nकरो_set_features	= vector_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = vector_net_poll_controller,
#पूर्ण_अगर
पूर्ण;


अटल व्योम vector_समयr_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा vector_निजी *vp = from_समयr(vp, t, tl);

	vp->estats.tx_kicks++;
	vector_send(vp->tx_queue);
पूर्ण

अटल व्योम vector_eth_configure(
		पूर्णांक n,
		काष्ठा arglist *def
	)
अणु
	काष्ठा vector_device *device;
	काष्ठा net_device *dev;
	काष्ठा vector_निजी *vp;
	पूर्णांक err;

	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (device == शून्य) अणु
		prपूर्णांकk(KERN_ERR "eth_configure failed to allocate struct "
				 "vector_device\n");
		वापस;
	पूर्ण
	dev = alloc_etherdev(माप(काष्ठा vector_निजी));
	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "eth_configure: failed to allocate struct "
				 "net_device for vec%d\n", n);
		जाओ out_मुक्त_device;
	पूर्ण

	dev->mtu = get_mtu(def);

	INIT_LIST_HEAD(&device->list);
	device->unit = n;

	/* If this name ends up conflicting with an existing रेजिस्टरed
	 * netdevice, that is OK, रेजिस्टर_netdevअणु,iceपूर्ण() will notice this
	 * and fail.
	 */
	snम_लिखो(dev->name, माप(dev->name), "vec%d", n);
	uml_net_setup_etheraddr(dev, uml_vector_fetch_arg(def, "mac"));
	vp = netdev_priv(dev);

	/* sysfs रेजिस्टर */
	अगर (!driver_रेजिस्टरed) अणु
		platक्रमm_driver_रेजिस्टर(&uml_net_driver);
		driver_रेजिस्टरed = 1;
	पूर्ण
	device->pdev.id = n;
	device->pdev.name = DRIVER_NAME;
	device->pdev.dev.release = vector_device_release;
	dev_set_drvdata(&device->pdev.dev, device);
	अगर (platक्रमm_device_रेजिस्टर(&device->pdev))
		जाओ out_मुक्त_netdev;
	SET_NETDEV_DEV(dev, &device->pdev.dev);

	device->dev = dev;

	*vp = ((काष्ठा vector_निजी)
		अणु
		.list			= LIST_HEAD_INIT(vp->list),
		.dev			= dev,
		.unit			= n,
		.options		= get_transport_options(def),
		.rx_irq			= 0,
		.tx_irq			= 0,
		.parsed			= def,
		.max_packet		= get_mtu(def) + ETH_HEADER_OTHER,
		/* TODO - we need to calculate headroom so that ip header
		 * is 16 byte aligned all the समय
		 */
		.headroom		= get_headroom(def),
		.क्रमm_header		= शून्य,
		.verअगरy_header		= शून्य,
		.header_rxbuffer	= शून्य,
		.header_txbuffer	= शून्य,
		.header_size		= 0,
		.rx_header_size		= 0,
		.rexmit_scheduled	= false,
		.खोलोed			= false,
		.transport_data		= शून्य,
		.in_ग_लिखो_poll		= false,
		.coalesce		= 2,
		.req_size		= get_req_size(def),
		.in_error		= false,
		.bpf			= शून्य
	पूर्ण);

	dev->features = dev->hw_features = (NETIF_F_SG | NETIF_F_FRAGLIST);
	tasklet_setup(&vp->tx_poll, vector_tx_poll);
	INIT_WORK(&vp->reset_tx, vector_reset_tx);

	समयr_setup(&vp->tl, vector_समयr_expire, 0);
	spin_lock_init(&vp->lock);

	/* FIXME */
	dev->netdev_ops = &vector_netdev_ops;
	dev->ethtool_ops = &vector_net_ethtool_ops;
	dev->watchकरोg_समयo = (HZ >> 1);
	/* primary IRQ - fixme */
	dev->irq = 0; /* we will adjust this once खोलोed */

	rtnl_lock();
	err = रेजिस्टर_netdevice(dev);
	rtnl_unlock();
	अगर (err)
		जाओ out_unकरो_user_init;

	spin_lock(&vector_devices_lock);
	list_add(&device->list, &vector_devices);
	spin_unlock(&vector_devices_lock);

	वापस;

out_unकरो_user_init:
	वापस;
out_मुक्त_netdev:
	मुक्त_netdev(dev);
out_मुक्त_device:
	kमुक्त(device);
पूर्ण




/*
 * Invoked late in the init
 */

अटल पूर्णांक __init vector_init(व्योम)
अणु
	काष्ठा list_head *ele;
	काष्ठा vector_cmd_line_arg *def;
	काष्ठा arglist *parsed;

	list_क्रम_each(ele, &vec_cmd_line) अणु
		def = list_entry(ele, काष्ठा vector_cmd_line_arg, list);
		parsed = uml_parse_vector_अगरspec(def->arguments);
		अगर (parsed != शून्य)
			vector_eth_configure(def->unit, parsed);
	पूर्ण
	वापस 0;
पूर्ण


/* Invoked at initial argument parsing, only stores
 * arguments until a proper vector_init is called
 * later
 */

अटल पूर्णांक __init vector_setup(अक्षर *str)
अणु
	अक्षर *error;
	पूर्णांक n, err;
	काष्ठा vector_cmd_line_arg *new;

	err = vector_parse(str, &n, &str, &error);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "vector_setup - Couldn't parse '%s' : %s\n",
				 str, error);
		वापस 1;
	पूर्ण
	new = memblock_alloc(माप(*new), SMP_CACHE_BYTES);
	अगर (!new)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*new));
	INIT_LIST_HEAD(&new->list);
	new->unit = n;
	new->arguments = str;
	list_add_tail(&new->list, &vec_cmd_line);
	वापस 1;
पूर्ण

__setup("vec", vector_setup);
__uml_help(vector_setup,
"vec[0-9]+:<option>=<value>,<option>=<value>\n"
"	 Configure a vector io network device.\n\n"
);

late_initcall(vector_init);

अटल काष्ठा mc_device vector_mc = अणु
	.list		= LIST_HEAD_INIT(vector_mc.list),
	.name		= "vec",
	.config		= vector_config,
	.get_config	= शून्य,
	.id		= vector_id,
	.हटाओ		= vector_हटाओ,
पूर्ण;

#अगर_घोषित CONFIG_INET
अटल पूर्णांक vector_inetaddr_event(
	काष्ठा notअगरier_block *this,
	अचिन्हित दीर्घ event,
	व्योम *ptr)
अणु
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vector_inetaddr_notअगरier = अणु
	.notअगरier_call		= vector_inetaddr_event,
पूर्ण;

अटल व्योम inet_रेजिस्टर(व्योम)
अणु
	रेजिस्टर_inetaddr_notअगरier(&vector_inetaddr_notअगरier);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम inet_रेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vector_net_init(व्योम)
अणु
	mconsole_रेजिस्टर_dev(&vector_mc);
	inet_रेजिस्टर();
	वापस 0;
पूर्ण

__initcall(vector_net_init);



