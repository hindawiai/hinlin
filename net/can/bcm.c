<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * bcm.c - Broadcast Manager to filter/send (cyclic) CAN content
 *
 * Copyright (c) 2002-2017 Volkswagen Group Electronic Research
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of Volkswagen nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Alternatively, provided that this notice is retained in full, this
 * software may be distributed under the terms of the GNU General
 * Public License ("GPL") version 2, in which हाल the provisions of the
 * GPL apply INSTEAD OF those given above.
 *
 * The provided data काष्ठाures and बाह्यal पूर्णांकerfaces from this code
 * are not restricted to be used by modules with a GPL compatible license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/list.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/socket.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/can/bcm.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/net_namespace.h>

/*
 * To send multiple CAN frame content within TX_SETUP or to filter
 * CAN messages with multiplex index within RX_SETUP, the number of
 * dअगरferent filters is limited to 256 due to the one byte index value.
 */
#घोषणा MAX_NFRAMES 256

/* limit समयrs to 400 days क्रम sending/समयouts */
#घोषणा BCM_TIMER_SEC_MAX (400 * 24 * 60 * 60)

/* use of last_frames[index].flags */
#घोषणा RX_RECV    0x40 /* received data क्रम this element */
#घोषणा RX_THR     0x80 /* element not been sent due to throttle feature */
#घोषणा BCM_CAN_FLAGS_MASK 0x3F /* to clean निजी flags after usage */

/* get best masking value क्रम can_rx_रेजिस्टर() क्रम a given single can_id */
#घोषणा REGMASK(id) ((id & CAN_EFF_FLAG) ? \
		     (CAN_EFF_MASK | CAN_EFF_FLAG | CAN_RTR_FLAG) : \
		     (CAN_SFF_MASK | CAN_EFF_FLAG | CAN_RTR_FLAG))

MODULE_DESCRIPTION("PF_CAN broadcast manager protocol");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Oliver Hartkopp <oliver.hartkopp@volkswagen.de>");
MODULE_ALIAS("can-proto-2");

#घोषणा BCM_MIN_NAMELEN CAN_REQUIRED_SIZE(काष्ठा sockaddr_can, can_अगरindex)

/*
 * easy access to the first 64 bit of can(fd)_frame payload. cp->data is
 * 64 bit aligned so the offset has to be multiples of 8 which is ensured
 * by the only callers in bcm_rx_cmp_to_index() bcm_rx_handler().
 */
अटल अंतरभूत u64 get_u64(स्थिर काष्ठा canfd_frame *cp, पूर्णांक offset)
अणु
	वापस *(u64 *)(cp->data + offset);
पूर्ण

काष्ठा bcm_op अणु
	काष्ठा list_head list;
	पूर्णांक अगरindex;
	canid_t can_id;
	u32 flags;
	अचिन्हित दीर्घ frames_असल, frames_filtered;
	काष्ठा bcm_समयval ival1, ival2;
	काष्ठा hrसमयr समयr, thrसमयr;
	kसमय_प्रकार rx_stamp, kt_ival1, kt_ival2, kt_lasपंचांगsg;
	पूर्णांक rx_अगरindex;
	पूर्णांक cfsiz;
	u32 count;
	u32 nframes;
	u32 currframe;
	/* व्योम poपूर्णांकers to arrays of काष्ठा can[fd]_frame */
	व्योम *frames;
	व्योम *last_frames;
	काष्ठा canfd_frame sframe;
	काष्ठा canfd_frame last_sframe;
	काष्ठा sock *sk;
	काष्ठा net_device *rx_reg_dev;
पूर्ण;

काष्ठा bcm_sock अणु
	काष्ठा sock sk;
	पूर्णांक bound;
	पूर्णांक अगरindex;
	काष्ठा list_head notअगरier;
	काष्ठा list_head rx_ops;
	काष्ठा list_head tx_ops;
	अचिन्हित दीर्घ dropped_usr_msgs;
	काष्ठा proc_dir_entry *bcm_proc_पढ़ो;
	अक्षर procname [32]; /* inode number in decimal with \0 */
पूर्ण;

अटल LIST_HEAD(bcm_notअगरier_list);
अटल DEFINE_SPINLOCK(bcm_notअगरier_lock);
अटल काष्ठा bcm_sock *bcm_busy_notअगरier;

अटल अंतरभूत काष्ठा bcm_sock *bcm_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा bcm_sock *)sk;
पूर्ण

अटल अंतरभूत kसमय_प्रकार bcm_समयval_to_kसमय(काष्ठा bcm_समयval tv)
अणु
	वापस kसमय_set(tv.tv_sec, tv.tv_usec * NSEC_PER_USEC);
पूर्ण

/* check limitations क्रम समयval provided by user */
अटल bool bcm_is_invalid_tv(काष्ठा bcm_msg_head *msg_head)
अणु
	अगर ((msg_head->ival1.tv_sec < 0) ||
	    (msg_head->ival1.tv_sec > BCM_TIMER_SEC_MAX) ||
	    (msg_head->ival1.tv_usec < 0) ||
	    (msg_head->ival1.tv_usec >= USEC_PER_SEC) ||
	    (msg_head->ival2.tv_sec < 0) ||
	    (msg_head->ival2.tv_sec > BCM_TIMER_SEC_MAX) ||
	    (msg_head->ival2.tv_usec < 0) ||
	    (msg_head->ival2.tv_usec >= USEC_PER_SEC))
		वापस true;

	वापस false;
पूर्ण

#घोषणा CFSIZ(flags) ((flags & CAN_FD_FRAME) ? CANFD_MTU : CAN_MTU)
#घोषणा OPSIZ माप(काष्ठा bcm_op)
#घोषणा MHSIZ माप(काष्ठा bcm_msg_head)

/*
 * procfs functions
 */
#अगर IS_ENABLED(CONFIG_PROC_FS)
अटल अक्षर *bcm_proc_getअगरname(काष्ठा net *net, अक्षर *result, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;

	अगर (!अगरindex)
		वापस "any";

	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (dev)
		म_नकल(result, dev->name);
	अन्यथा
		म_नकल(result, "???");
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

अटल पूर्णांक bcm_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अक्षर अगरname[IFNAMSIZ];
	काष्ठा net *net = m->निजी;
	काष्ठा sock *sk = (काष्ठा sock *)PDE_DATA(m->file->f_inode);
	काष्ठा bcm_sock *bo = bcm_sk(sk);
	काष्ठा bcm_op *op;

	seq_म_लिखो(m, ">>> socket %pK", sk->sk_socket);
	seq_म_लिखो(m, " / sk %pK", sk);
	seq_म_लिखो(m, " / bo %pK", bo);
	seq_म_लिखो(m, " / dropped %lu", bo->dropped_usr_msgs);
	seq_म_लिखो(m, " / bound %s", bcm_proc_getअगरname(net, अगरname, bo->अगरindex));
	seq_म_लिखो(m, " <<<\n");

	list_क्रम_each_entry(op, &bo->rx_ops, list) अणु

		अचिन्हित दीर्घ reduction;

		/* prपूर्णांक only active entries & prevent भागision by zero */
		अगर (!op->frames_असल)
			जारी;

		seq_म_लिखो(m, "rx_op: %03X %-5s ", op->can_id,
			   bcm_proc_getअगरname(net, अगरname, op->अगरindex));

		अगर (op->flags & CAN_FD_FRAME)
			seq_म_लिखो(m, "(%u)", op->nframes);
		अन्यथा
			seq_म_लिखो(m, "[%u]", op->nframes);

		seq_म_लिखो(m, "%c ", (op->flags & RX_CHECK_DLC) ? 'd' : ' ');

		अगर (op->kt_ival1)
			seq_म_लिखो(m, "timeo=%lld ",
				   (दीर्घ दीर्घ)kसमय_प्रकारo_us(op->kt_ival1));

		अगर (op->kt_ival2)
			seq_म_लिखो(m, "thr=%lld ",
				   (दीर्घ दीर्घ)kसमय_प्रकारo_us(op->kt_ival2));

		seq_म_लिखो(m, "# recv %ld (%ld) => reduction: ",
			   op->frames_filtered, op->frames_असल);

		reduction = 100 - (op->frames_filtered * 100) / op->frames_असल;

		seq_म_लिखो(m, "%s%ld%%\n",
			   (reduction == 100) ? "near " : "", reduction);
	पूर्ण

	list_क्रम_each_entry(op, &bo->tx_ops, list) अणु

		seq_म_लिखो(m, "tx_op: %03X %s ", op->can_id,
			   bcm_proc_getअगरname(net, अगरname, op->अगरindex));

		अगर (op->flags & CAN_FD_FRAME)
			seq_म_लिखो(m, "(%u) ", op->nframes);
		अन्यथा
			seq_म_लिखो(m, "[%u] ", op->nframes);

		अगर (op->kt_ival1)
			seq_म_लिखो(m, "t1=%lld ",
				   (दीर्घ दीर्घ)kसमय_प्रकारo_us(op->kt_ival1));

		अगर (op->kt_ival2)
			seq_म_लिखो(m, "t2=%lld ",
				   (दीर्घ दीर्घ)kसमय_प्रकारo_us(op->kt_ival2));

		seq_म_लिखो(m, "# sent %ld\n", op->frames_असल);
	पूर्ण
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 * bcm_can_tx - send the (next) CAN frame to the appropriate CAN पूर्णांकerface
 *              of the given bcm tx op
 */
अटल व्योम bcm_can_tx(काष्ठा bcm_op *op)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	काष्ठा canfd_frame *cf = op->frames + op->cfsiz * op->currframe;

	/* no target device? => निकास */
	अगर (!op->अगरindex)
		वापस;

	dev = dev_get_by_index(sock_net(op->sk), op->अगरindex);
	अगर (!dev) अणु
		/* RFC: should this bcm_op हटाओ itself here? */
		वापस;
	पूर्ण

	skb = alloc_skb(op->cfsiz + माप(काष्ठा can_skb_priv), gfp_any());
	अगर (!skb)
		जाओ out;

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;

	skb_put_data(skb, cf, op->cfsiz);

	/* send with loopback */
	skb->dev = dev;
	can_skb_set_owner(skb, op->sk);
	can_send(skb, 1);

	/* update statistics */
	op->currframe++;
	op->frames_असल++;

	/* reached last frame? */
	अगर (op->currframe >= op->nframes)
		op->currframe = 0;
out:
	dev_put(dev);
पूर्ण

/*
 * bcm_send_to_user - send a BCM message to the userspace
 *                    (consisting of bcm_msg_head + x CAN frames)
 */
अटल व्योम bcm_send_to_user(काष्ठा bcm_op *op, काष्ठा bcm_msg_head *head,
			     काष्ठा canfd_frame *frames, पूर्णांक has_बारtamp)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा canfd_frame *firstframe;
	काष्ठा sockaddr_can *addr;
	काष्ठा sock *sk = op->sk;
	अचिन्हित पूर्णांक datalen = head->nframes * op->cfsiz;
	पूर्णांक err;

	skb = alloc_skb(माप(*head) + datalen, gfp_any());
	अगर (!skb)
		वापस;

	skb_put_data(skb, head, माप(*head));

	अगर (head->nframes) अणु
		/* CAN frames starting here */
		firstframe = (काष्ठा canfd_frame *)skb_tail_poपूर्णांकer(skb);

		skb_put_data(skb, frames, datalen);

		/*
		 * the BCM uses the flags-element of the canfd_frame
		 * काष्ठाure क्रम पूर्णांकernal purposes. This is only
		 * relevant क्रम updates that are generated by the
		 * BCM, where nframes is 1
		 */
		अगर (head->nframes == 1)
			firstframe->flags &= BCM_CAN_FLAGS_MASK;
	पूर्ण

	अगर (has_बारtamp) अणु
		/* restore rx बारtamp */
		skb->tstamp = op->rx_stamp;
	पूर्ण

	/*
	 *  Put the datagram to the queue so that bcm_recvmsg() can
	 *  get it from there.  We need to pass the पूर्णांकerface index to
	 *  bcm_recvmsg().  We pass a whole काष्ठा sockaddr_can in skb->cb
	 *  containing the पूर्णांकerface index.
	 */

	sock_skb_cb_check_size(माप(काष्ठा sockaddr_can));
	addr = (काष्ठा sockaddr_can *)skb->cb;
	स_रखो(addr, 0, माप(*addr));
	addr->can_family  = AF_CAN;
	addr->can_अगरindex = op->rx_अगरindex;

	err = sock_queue_rcv_skb(sk, skb);
	अगर (err < 0) अणु
		काष्ठा bcm_sock *bo = bcm_sk(sk);

		kमुक्त_skb(skb);
		/* करोn't care about overflows in this statistic */
		bo->dropped_usr_msgs++;
	पूर्ण
पूर्ण

अटल bool bcm_tx_set_expiry(काष्ठा bcm_op *op, काष्ठा hrसमयr *hrt)
अणु
	kसमय_प्रकार ival;

	अगर (op->kt_ival1 && op->count)
		ival = op->kt_ival1;
	अन्यथा अगर (op->kt_ival2)
		ival = op->kt_ival2;
	अन्यथा
		वापस false;

	hrसमयr_set_expires(hrt, kसमय_add(kसमय_get(), ival));
	वापस true;
पूर्ण

अटल व्योम bcm_tx_start_समयr(काष्ठा bcm_op *op)
अणु
	अगर (bcm_tx_set_expiry(op, &op->समयr))
		hrसमयr_start_expires(&op->समयr, HRTIMER_MODE_ABS_SOFT);
पूर्ण

/* bcm_tx_समयout_handler - perक्रमms cyclic CAN frame transmissions */
अटल क्रमागत hrसमयr_restart bcm_tx_समयout_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा bcm_op *op = container_of(hrसमयr, काष्ठा bcm_op, समयr);
	काष्ठा bcm_msg_head msg_head;

	अगर (op->kt_ival1 && (op->count > 0)) अणु
		op->count--;
		अगर (!op->count && (op->flags & TX_COUNTEVT)) अणु

			/* create notअगरication to user */
			स_रखो(&msg_head, 0, माप(msg_head));
			msg_head.opcode  = TX_EXPIRED;
			msg_head.flags   = op->flags;
			msg_head.count   = op->count;
			msg_head.ival1   = op->ival1;
			msg_head.ival2   = op->ival2;
			msg_head.can_id  = op->can_id;
			msg_head.nframes = 0;

			bcm_send_to_user(op, &msg_head, शून्य, 0);
		पूर्ण
		bcm_can_tx(op);

	पूर्ण अन्यथा अगर (op->kt_ival2) अणु
		bcm_can_tx(op);
	पूर्ण

	वापस bcm_tx_set_expiry(op, &op->समयr) ?
		HRTIMER_RESTART : HRTIMER_NORESTART;
पूर्ण

/*
 * bcm_rx_changed - create a RX_CHANGED notअगरication due to changed content
 */
अटल व्योम bcm_rx_changed(काष्ठा bcm_op *op, काष्ठा canfd_frame *data)
अणु
	काष्ठा bcm_msg_head head;

	/* update statistics */
	op->frames_filtered++;

	/* prevent statistics overflow */
	अगर (op->frames_filtered > अच_दीर्घ_उच्च/100)
		op->frames_filtered = op->frames_असल = 0;

	/* this element is not throttled anymore */
	data->flags &= (BCM_CAN_FLAGS_MASK|RX_RECV);

	स_रखो(&head, 0, माप(head));
	head.opcode  = RX_CHANGED;
	head.flags   = op->flags;
	head.count   = op->count;
	head.ival1   = op->ival1;
	head.ival2   = op->ival2;
	head.can_id  = op->can_id;
	head.nframes = 1;

	bcm_send_to_user(op, &head, data, 1);
पूर्ण

/*
 * bcm_rx_update_and_send - process a detected relevant receive content change
 *                          1. update the last received data
 *                          2. send a notअगरication to the user (अगर possible)
 */
अटल व्योम bcm_rx_update_and_send(काष्ठा bcm_op *op,
				   काष्ठा canfd_frame *lastdata,
				   स्थिर काष्ठा canfd_frame *rxdata)
अणु
	स_नकल(lastdata, rxdata, op->cfsiz);

	/* mark as used and throttled by शेष */
	lastdata->flags |= (RX_RECV|RX_THR);

	/* throttling mode inactive ? */
	अगर (!op->kt_ival2) अणु
		/* send RX_CHANGED to the user immediately */
		bcm_rx_changed(op, lastdata);
		वापस;
	पूर्ण

	/* with active throttling समयr we are just करोne here */
	अगर (hrसमयr_active(&op->thrसमयr))
		वापस;

	/* first reception with enabled throttling mode */
	अगर (!op->kt_lasपंचांगsg)
		जाओ rx_changed_समय_रखो;

	/* got a second frame inside a potential throttle period? */
	अगर (kसमय_us_delta(kसमय_get(), op->kt_lasपंचांगsg) <
	    kसमय_प्रकारo_us(op->kt_ival2)) अणु
		/* करो not send the saved data - only start throttle समयr */
		hrसमयr_start(&op->thrसमयr,
			      kसमय_add(op->kt_lasपंचांगsg, op->kt_ival2),
			      HRTIMER_MODE_ABS_SOFT);
		वापस;
	पूर्ण

	/* the gap was that big, that throttling was not needed here */
rx_changed_समय_रखो:
	bcm_rx_changed(op, lastdata);
	op->kt_lasपंचांगsg = kसमय_get();
पूर्ण

/*
 * bcm_rx_cmp_to_index - (bit)compares the currently received data to क्रमmerly
 *                       received data stored in op->last_frames[]
 */
अटल व्योम bcm_rx_cmp_to_index(काष्ठा bcm_op *op, अचिन्हित पूर्णांक index,
				स्थिर काष्ठा canfd_frame *rxdata)
अणु
	काष्ठा canfd_frame *cf = op->frames + op->cfsiz * index;
	काष्ठा canfd_frame *lcf = op->last_frames + op->cfsiz * index;
	पूर्णांक i;

	/*
	 * no one uses the MSBs of flags क्रम comparison,
	 * so we use it here to detect the first समय of reception
	 */

	अगर (!(lcf->flags & RX_RECV)) अणु
		/* received data क्रम the first समय => send update to user */
		bcm_rx_update_and_send(op, lcf, rxdata);
		वापस;
	पूर्ण

	/* करो a real check in CAN frame data section */
	क्रम (i = 0; i < rxdata->len; i += 8) अणु
		अगर ((get_u64(cf, i) & get_u64(rxdata, i)) !=
		    (get_u64(cf, i) & get_u64(lcf, i))) अणु
			bcm_rx_update_and_send(op, lcf, rxdata);
			वापस;
		पूर्ण
	पूर्ण

	अगर (op->flags & RX_CHECK_DLC) अणु
		/* करो a real check in CAN frame length */
		अगर (rxdata->len != lcf->len) अणु
			bcm_rx_update_and_send(op, lcf, rxdata);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * bcm_rx_startसमयr - enable समयout monitoring क्रम CAN frame reception
 */
अटल व्योम bcm_rx_startसमयr(काष्ठा bcm_op *op)
अणु
	अगर (op->flags & RX_NO_AUTOTIMER)
		वापस;

	अगर (op->kt_ival1)
		hrसमयr_start(&op->समयr, op->kt_ival1, HRTIMER_MODE_REL_SOFT);
पूर्ण

/* bcm_rx_समयout_handler - when the (cyclic) CAN frame reception समयd out */
अटल क्रमागत hrसमयr_restart bcm_rx_समयout_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा bcm_op *op = container_of(hrसमयr, काष्ठा bcm_op, समयr);
	काष्ठा bcm_msg_head msg_head;

	/* अगर user wants to be inक्रमmed, when cyclic CAN-Messages come back */
	अगर ((op->flags & RX_ANNOUNCE_RESUME) && op->last_frames) अणु
		/* clear received CAN frames to indicate 'nothing received' */
		स_रखो(op->last_frames, 0, op->nframes * op->cfsiz);
	पूर्ण

	/* create notअगरication to user */
	स_रखो(&msg_head, 0, माप(msg_head));
	msg_head.opcode  = RX_TIMEOUT;
	msg_head.flags   = op->flags;
	msg_head.count   = op->count;
	msg_head.ival1   = op->ival1;
	msg_head.ival2   = op->ival2;
	msg_head.can_id  = op->can_id;
	msg_head.nframes = 0;

	bcm_send_to_user(op, &msg_head, शून्य, 0);

	वापस HRTIMER_NORESTART;
पूर्ण

/*
 * bcm_rx_करो_flush - helper क्रम bcm_rx_thr_flush
 */
अटल अंतरभूत पूर्णांक bcm_rx_करो_flush(काष्ठा bcm_op *op, अचिन्हित पूर्णांक index)
अणु
	काष्ठा canfd_frame *lcf = op->last_frames + op->cfsiz * index;

	अगर ((op->last_frames) && (lcf->flags & RX_THR)) अणु
		bcm_rx_changed(op, lcf);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * bcm_rx_thr_flush - Check क्रम throttled data and send it to the userspace
 */
अटल पूर्णांक bcm_rx_thr_flush(काष्ठा bcm_op *op)
अणु
	पूर्णांक updated = 0;

	अगर (op->nframes > 1) अणु
		अचिन्हित पूर्णांक i;

		/* क्रम MUX filter we start at index 1 */
		क्रम (i = 1; i < op->nframes; i++)
			updated += bcm_rx_करो_flush(op, i);

	पूर्ण अन्यथा अणु
		/* क्रम RX_FILTER_ID and simple filter */
		updated += bcm_rx_करो_flush(op, 0);
	पूर्ण

	वापस updated;
पूर्ण

/*
 * bcm_rx_thr_handler - the समय क्रम blocked content updates is over now:
 *                      Check क्रम throttled data and send it to the userspace
 */
अटल क्रमागत hrसमयr_restart bcm_rx_thr_handler(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा bcm_op *op = container_of(hrसमयr, काष्ठा bcm_op, thrसमयr);

	अगर (bcm_rx_thr_flush(op)) अणु
		hrसमयr_क्रमward(hrसमयr, kसमय_get(), op->kt_ival2);
		वापस HRTIMER_RESTART;
	पूर्ण अन्यथा अणु
		/* rearm throttle handling */
		op->kt_lasपंचांगsg = 0;
		वापस HRTIMER_NORESTART;
	पूर्ण
पूर्ण

/*
 * bcm_rx_handler - handle a CAN frame reception
 */
अटल व्योम bcm_rx_handler(काष्ठा sk_buff *skb, व्योम *data)
अणु
	काष्ठा bcm_op *op = (काष्ठा bcm_op *)data;
	स्थिर काष्ठा canfd_frame *rxframe = (काष्ठा canfd_frame *)skb->data;
	अचिन्हित पूर्णांक i;

	अगर (op->can_id != rxframe->can_id)
		वापस;

	/* make sure to handle the correct frame type (CAN / CAN FD) */
	अगर (skb->len != op->cfsiz)
		वापस;

	/* disable समयout */
	hrसमयr_cancel(&op->समयr);

	/* save rx बारtamp */
	op->rx_stamp = skb->tstamp;
	/* save originator क्रम recvfrom() */
	op->rx_अगरindex = skb->dev->अगरindex;
	/* update statistics */
	op->frames_असल++;

	अगर (op->flags & RX_RTR_FRAME) अणु
		/* send reply क्रम RTR-request (placed in op->frames[0]) */
		bcm_can_tx(op);
		वापस;
	पूर्ण

	अगर (op->flags & RX_FILTER_ID) अणु
		/* the easiest हाल */
		bcm_rx_update_and_send(op, op->last_frames, rxframe);
		जाओ rx_startसमयr;
	पूर्ण

	अगर (op->nframes == 1) अणु
		/* simple compare with index 0 */
		bcm_rx_cmp_to_index(op, 0, rxframe);
		जाओ rx_startसमयr;
	पूर्ण

	अगर (op->nframes > 1) अणु
		/*
		 * multiplex compare
		 *
		 * find the first multiplex mask that fits.
		 * Remark: The MUX-mask is stored in index 0 - but only the
		 * first 64 bits of the frame data[] are relevant (CAN FD)
		 */

		क्रम (i = 1; i < op->nframes; i++) अणु
			अगर ((get_u64(op->frames, 0) & get_u64(rxframe, 0)) ==
			    (get_u64(op->frames, 0) &
			     get_u64(op->frames + op->cfsiz * i, 0))) अणु
				bcm_rx_cmp_to_index(op, i, rxframe);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

rx_startसमयr:
	bcm_rx_startसमयr(op);
पूर्ण

/*
 * helpers क्रम bcm_op handling: find & delete bcm [rx|tx] op elements
 */
अटल काष्ठा bcm_op *bcm_find_op(काष्ठा list_head *ops,
				  काष्ठा bcm_msg_head *mh, पूर्णांक अगरindex)
अणु
	काष्ठा bcm_op *op;

	list_क्रम_each_entry(op, ops, list) अणु
		अगर ((op->can_id == mh->can_id) && (op->अगरindex == अगरindex) &&
		    (op->flags & CAN_FD_FRAME) == (mh->flags & CAN_FD_FRAME))
			वापस op;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम bcm_हटाओ_op(काष्ठा bcm_op *op)
अणु
	hrसमयr_cancel(&op->समयr);
	hrसमयr_cancel(&op->thrसमयr);

	अगर ((op->frames) && (op->frames != &op->sframe))
		kमुक्त(op->frames);

	अगर ((op->last_frames) && (op->last_frames != &op->last_sframe))
		kमुक्त(op->last_frames);

	kमुक्त(op);
पूर्ण

अटल व्योम bcm_rx_unreg(काष्ठा net_device *dev, काष्ठा bcm_op *op)
अणु
	अगर (op->rx_reg_dev == dev) अणु
		can_rx_unरेजिस्टर(dev_net(dev), dev, op->can_id,
				  REGMASK(op->can_id), bcm_rx_handler, op);

		/* mark as हटाओd subscription */
		op->rx_reg_dev = शून्य;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "can-bcm: bcm_rx_unreg: registered device "
		       "mismatch %p %p\n", op->rx_reg_dev, dev);
पूर्ण

/*
 * bcm_delete_rx_op - find and हटाओ a rx op (वापसs number of हटाओd ops)
 */
अटल पूर्णांक bcm_delete_rx_op(काष्ठा list_head *ops, काष्ठा bcm_msg_head *mh,
			    पूर्णांक अगरindex)
अणु
	काष्ठा bcm_op *op, *n;

	list_क्रम_each_entry_safe(op, n, ops, list) अणु
		अगर ((op->can_id == mh->can_id) && (op->अगरindex == अगरindex) &&
		    (op->flags & CAN_FD_FRAME) == (mh->flags & CAN_FD_FRAME)) अणु

			/*
			 * Don't care if we're bound or not (due to netdev
			 * problems) can_rx_unरेजिस्टर() is always a save
			 * thing to करो here.
			 */
			अगर (op->अगरindex) अणु
				/*
				 * Only हटाओ subscriptions that had not
				 * been हटाओd due to NETDEV_UNREGISTER
				 * in bcm_notअगरier()
				 */
				अगर (op->rx_reg_dev) अणु
					काष्ठा net_device *dev;

					dev = dev_get_by_index(sock_net(op->sk),
							       op->अगरindex);
					अगर (dev) अणु
						bcm_rx_unreg(dev, op);
						dev_put(dev);
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा
				can_rx_unरेजिस्टर(sock_net(op->sk), शून्य,
						  op->can_id,
						  REGMASK(op->can_id),
						  bcm_rx_handler, op);

			list_del(&op->list);
			bcm_हटाओ_op(op);
			वापस 1; /* करोne */
		पूर्ण
	पूर्ण

	वापस 0; /* not found */
पूर्ण

/*
 * bcm_delete_tx_op - find and हटाओ a tx op (वापसs number of हटाओd ops)
 */
अटल पूर्णांक bcm_delete_tx_op(काष्ठा list_head *ops, काष्ठा bcm_msg_head *mh,
			    पूर्णांक अगरindex)
अणु
	काष्ठा bcm_op *op, *n;

	list_क्रम_each_entry_safe(op, n, ops, list) अणु
		अगर ((op->can_id == mh->can_id) && (op->अगरindex == अगरindex) &&
		    (op->flags & CAN_FD_FRAME) == (mh->flags & CAN_FD_FRAME)) अणु
			list_del(&op->list);
			bcm_हटाओ_op(op);
			वापस 1; /* करोne */
		पूर्ण
	पूर्ण

	वापस 0; /* not found */
पूर्ण

/*
 * bcm_पढ़ो_op - पढ़ो out a bcm_op and send it to the user (क्रम bcm_sendmsg)
 */
अटल पूर्णांक bcm_पढ़ो_op(काष्ठा list_head *ops, काष्ठा bcm_msg_head *msg_head,
		       पूर्णांक अगरindex)
अणु
	काष्ठा bcm_op *op = bcm_find_op(ops, msg_head, अगरindex);

	अगर (!op)
		वापस -EINVAL;

	/* put current values पूर्णांकo msg_head */
	msg_head->flags   = op->flags;
	msg_head->count   = op->count;
	msg_head->ival1   = op->ival1;
	msg_head->ival2   = op->ival2;
	msg_head->nframes = op->nframes;

	bcm_send_to_user(op, msg_head, op->frames, 0);

	वापस MHSIZ;
पूर्ण

/*
 * bcm_tx_setup - create or update a bcm tx op (क्रम bcm_sendmsg)
 */
अटल पूर्णांक bcm_tx_setup(काष्ठा bcm_msg_head *msg_head, काष्ठा msghdr *msg,
			पूर्णांक अगरindex, काष्ठा sock *sk)
अणु
	काष्ठा bcm_sock *bo = bcm_sk(sk);
	काष्ठा bcm_op *op;
	काष्ठा canfd_frame *cf;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* we need a real device to send frames */
	अगर (!अगरindex)
		वापस -ENODEV;

	/* check nframes boundaries - we need at least one CAN frame */
	अगर (msg_head->nframes < 1 || msg_head->nframes > MAX_NFRAMES)
		वापस -EINVAL;

	/* check समयval limitations */
	अगर ((msg_head->flags & SETTIMER) && bcm_is_invalid_tv(msg_head))
		वापस -EINVAL;

	/* check the given can_id */
	op = bcm_find_op(&bo->tx_ops, msg_head, अगरindex);
	अगर (op) अणु
		/* update existing BCM operation */

		/*
		 * Do we need more space क्रम the CAN frames than currently
		 * allocated? -> This is a _really_ unusual use-हाल and
		 * thereक्रमe (complनिकासy / locking) it is not supported.
		 */
		अगर (msg_head->nframes > op->nframes)
			वापस -E2BIG;

		/* update CAN frames content */
		क्रम (i = 0; i < msg_head->nframes; i++) अणु

			cf = op->frames + op->cfsiz * i;
			err = स_नकल_from_msg((u8 *)cf, msg, op->cfsiz);

			अगर (op->flags & CAN_FD_FRAME) अणु
				अगर (cf->len > 64)
					err = -EINVAL;
			पूर्ण अन्यथा अणु
				अगर (cf->len > 8)
					err = -EINVAL;
			पूर्ण

			अगर (err < 0)
				वापस err;

			अगर (msg_head->flags & TX_CP_CAN_ID) अणु
				/* copy can_id पूर्णांकo frame */
				cf->can_id = msg_head->can_id;
			पूर्ण
		पूर्ण
		op->flags = msg_head->flags;

	पूर्ण अन्यथा अणु
		/* insert new BCM operation क्रम the given can_id */

		op = kzalloc(OPSIZ, GFP_KERNEL);
		अगर (!op)
			वापस -ENOMEM;

		op->can_id = msg_head->can_id;
		op->cfsiz = CFSIZ(msg_head->flags);
		op->flags = msg_head->flags;

		/* create array क्रम CAN frames and copy the data */
		अगर (msg_head->nframes > 1) अणु
			op->frames = kदो_स्मृति_array(msg_head->nframes,
						   op->cfsiz,
						   GFP_KERNEL);
			अगर (!op->frames) अणु
				kमुक्त(op);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा
			op->frames = &op->sframe;

		क्रम (i = 0; i < msg_head->nframes; i++) अणु

			cf = op->frames + op->cfsiz * i;
			err = स_नकल_from_msg((u8 *)cf, msg, op->cfsiz);

			अगर (op->flags & CAN_FD_FRAME) अणु
				अगर (cf->len > 64)
					err = -EINVAL;
			पूर्ण अन्यथा अणु
				अगर (cf->len > 8)
					err = -EINVAL;
			पूर्ण

			अगर (err < 0) अणु
				अगर (op->frames != &op->sframe)
					kमुक्त(op->frames);
				kमुक्त(op);
				वापस err;
			पूर्ण

			अगर (msg_head->flags & TX_CP_CAN_ID) अणु
				/* copy can_id पूर्णांकo frame */
				cf->can_id = msg_head->can_id;
			पूर्ण
		पूर्ण

		/* tx_ops never compare with previous received messages */
		op->last_frames = शून्य;

		/* bcm_can_tx / bcm_tx_समयout_handler needs this */
		op->sk = sk;
		op->अगरindex = अगरindex;

		/* initialize uninitialized (kzalloc) काष्ठाure */
		hrसमयr_init(&op->समयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL_SOFT);
		op->समयr.function = bcm_tx_समयout_handler;

		/* currently unused in tx_ops */
		hrसमयr_init(&op->thrसमयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL_SOFT);

		/* add this bcm_op to the list of the tx_ops */
		list_add(&op->list, &bo->tx_ops);

	पूर्ण /* अगर ((op = bcm_find_op(&bo->tx_ops, msg_head->can_id, अगरindex))) */

	अगर (op->nframes != msg_head->nframes) अणु
		op->nframes   = msg_head->nframes;
		/* start multiple frame transmission with index 0 */
		op->currframe = 0;
	पूर्ण

	/* check flags */

	अगर (op->flags & TX_RESET_MULTI_IDX) अणु
		/* start multiple frame transmission with index 0 */
		op->currframe = 0;
	पूर्ण

	अगर (op->flags & SETTIMER) अणु
		/* set समयr values */
		op->count = msg_head->count;
		op->ival1 = msg_head->ival1;
		op->ival2 = msg_head->ival2;
		op->kt_ival1 = bcm_समयval_to_kसमय(msg_head->ival1);
		op->kt_ival2 = bcm_समयval_to_kसमय(msg_head->ival2);

		/* disable an active समयr due to zero values? */
		अगर (!op->kt_ival1 && !op->kt_ival2)
			hrसमयr_cancel(&op->समयr);
	पूर्ण

	अगर (op->flags & STARTTIMER) अणु
		hrसमयr_cancel(&op->समयr);
		/* spec: send CAN frame when starting समयr */
		op->flags |= TX_ANNOUNCE;
	पूर्ण

	अगर (op->flags & TX_ANNOUNCE) अणु
		bcm_can_tx(op);
		अगर (op->count)
			op->count--;
	पूर्ण

	अगर (op->flags & STARTTIMER)
		bcm_tx_start_समयr(op);

	वापस msg_head->nframes * op->cfsiz + MHSIZ;
पूर्ण

/*
 * bcm_rx_setup - create or update a bcm rx op (क्रम bcm_sendmsg)
 */
अटल पूर्णांक bcm_rx_setup(काष्ठा bcm_msg_head *msg_head, काष्ठा msghdr *msg,
			पूर्णांक अगरindex, काष्ठा sock *sk)
अणु
	काष्ठा bcm_sock *bo = bcm_sk(sk);
	काष्ठा bcm_op *op;
	पूर्णांक करो_rx_रेजिस्टर;
	पूर्णांक err = 0;

	अगर ((msg_head->flags & RX_FILTER_ID) || (!(msg_head->nframes))) अणु
		/* be robust against wrong usage ... */
		msg_head->flags |= RX_FILTER_ID;
		/* ignore trailing garbage */
		msg_head->nframes = 0;
	पूर्ण

	/* the first element contains the mux-mask => MAX_NFRAMES + 1  */
	अगर (msg_head->nframes > MAX_NFRAMES + 1)
		वापस -EINVAL;

	अगर ((msg_head->flags & RX_RTR_FRAME) &&
	    ((msg_head->nframes != 1) ||
	     (!(msg_head->can_id & CAN_RTR_FLAG))))
		वापस -EINVAL;

	/* check समयval limitations */
	अगर ((msg_head->flags & SETTIMER) && bcm_is_invalid_tv(msg_head))
		वापस -EINVAL;

	/* check the given can_id */
	op = bcm_find_op(&bo->rx_ops, msg_head, अगरindex);
	अगर (op) अणु
		/* update existing BCM operation */

		/*
		 * Do we need more space क्रम the CAN frames than currently
		 * allocated? -> This is a _really_ unusual use-हाल and
		 * thereक्रमe (complनिकासy / locking) it is not supported.
		 */
		अगर (msg_head->nframes > op->nframes)
			वापस -E2BIG;

		अगर (msg_head->nframes) अणु
			/* update CAN frames content */
			err = स_नकल_from_msg(op->frames, msg,
					      msg_head->nframes * op->cfsiz);
			अगर (err < 0)
				वापस err;

			/* clear last_frames to indicate 'nothing received' */
			स_रखो(op->last_frames, 0, msg_head->nframes * op->cfsiz);
		पूर्ण

		op->nframes = msg_head->nframes;
		op->flags = msg_head->flags;

		/* Only an update -> करो not call can_rx_रेजिस्टर() */
		करो_rx_रेजिस्टर = 0;

	पूर्ण अन्यथा अणु
		/* insert new BCM operation क्रम the given can_id */
		op = kzalloc(OPSIZ, GFP_KERNEL);
		अगर (!op)
			वापस -ENOMEM;

		op->can_id = msg_head->can_id;
		op->nframes = msg_head->nframes;
		op->cfsiz = CFSIZ(msg_head->flags);
		op->flags = msg_head->flags;

		अगर (msg_head->nframes > 1) अणु
			/* create array क्रम CAN frames and copy the data */
			op->frames = kदो_स्मृति_array(msg_head->nframes,
						   op->cfsiz,
						   GFP_KERNEL);
			अगर (!op->frames) अणु
				kमुक्त(op);
				वापस -ENOMEM;
			पूर्ण

			/* create and init array क्रम received CAN frames */
			op->last_frames = kसुस्मृति(msg_head->nframes,
						  op->cfsiz,
						  GFP_KERNEL);
			अगर (!op->last_frames) अणु
				kमुक्त(op->frames);
				kमुक्त(op);
				वापस -ENOMEM;
			पूर्ण

		पूर्ण अन्यथा अणु
			op->frames = &op->sframe;
			op->last_frames = &op->last_sframe;
		पूर्ण

		अगर (msg_head->nframes) अणु
			err = स_नकल_from_msg(op->frames, msg,
					      msg_head->nframes * op->cfsiz);
			अगर (err < 0) अणु
				अगर (op->frames != &op->sframe)
					kमुक्त(op->frames);
				अगर (op->last_frames != &op->last_sframe)
					kमुक्त(op->last_frames);
				kमुक्त(op);
				वापस err;
			पूर्ण
		पूर्ण

		/* bcm_can_tx / bcm_tx_समयout_handler needs this */
		op->sk = sk;
		op->अगरindex = अगरindex;

		/* अगरindex क्रम समयout events w/o previous frame reception */
		op->rx_अगरindex = अगरindex;

		/* initialize uninitialized (kzalloc) काष्ठाure */
		hrसमयr_init(&op->समयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL_SOFT);
		op->समयr.function = bcm_rx_समयout_handler;

		hrसमयr_init(&op->thrसमयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL_SOFT);
		op->thrसमयr.function = bcm_rx_thr_handler;

		/* add this bcm_op to the list of the rx_ops */
		list_add(&op->list, &bo->rx_ops);

		/* call can_rx_रेजिस्टर() */
		करो_rx_रेजिस्टर = 1;

	पूर्ण /* अगर ((op = bcm_find_op(&bo->rx_ops, msg_head->can_id, अगरindex))) */

	/* check flags */

	अगर (op->flags & RX_RTR_FRAME) अणु
		काष्ठा canfd_frame *frame0 = op->frames;

		/* no समयrs in RTR-mode */
		hrसमयr_cancel(&op->thrसमयr);
		hrसमयr_cancel(&op->समयr);

		/*
		 * funny feature in RX(!)_SETUP only क्रम RTR-mode:
		 * copy can_id पूर्णांकo frame BUT without RTR-flag to
		 * prevent a full-load-loopback-test ... ;-]
		 */
		अगर ((op->flags & TX_CP_CAN_ID) ||
		    (frame0->can_id == op->can_id))
			frame0->can_id = op->can_id & ~CAN_RTR_FLAG;

	पूर्ण अन्यथा अणु
		अगर (op->flags & SETTIMER) अणु

			/* set समयr value */
			op->ival1 = msg_head->ival1;
			op->ival2 = msg_head->ival2;
			op->kt_ival1 = bcm_समयval_to_kसमय(msg_head->ival1);
			op->kt_ival2 = bcm_समयval_to_kसमय(msg_head->ival2);

			/* disable an active समयr due to zero value? */
			अगर (!op->kt_ival1)
				hrसमयr_cancel(&op->समयr);

			/*
			 * In any हाल cancel the throttle समयr, flush
			 * potentially blocked msgs and reset throttle handling
			 */
			op->kt_lasपंचांगsg = 0;
			hrसमयr_cancel(&op->thrसमयr);
			bcm_rx_thr_flush(op);
		पूर्ण

		अगर ((op->flags & STARTTIMER) && op->kt_ival1)
			hrसमयr_start(&op->समयr, op->kt_ival1,
				      HRTIMER_MODE_REL_SOFT);
	पूर्ण

	/* now we can रेजिस्टर क्रम can_ids, अगर we added a new bcm_op */
	अगर (करो_rx_रेजिस्टर) अणु
		अगर (अगरindex) अणु
			काष्ठा net_device *dev;

			dev = dev_get_by_index(sock_net(sk), अगरindex);
			अगर (dev) अणु
				err = can_rx_रेजिस्टर(sock_net(sk), dev,
						      op->can_id,
						      REGMASK(op->can_id),
						      bcm_rx_handler, op,
						      "bcm", sk);

				op->rx_reg_dev = dev;
				dev_put(dev);
			पूर्ण

		पूर्ण अन्यथा
			err = can_rx_रेजिस्टर(sock_net(sk), शून्य, op->can_id,
					      REGMASK(op->can_id),
					      bcm_rx_handler, op, "bcm", sk);
		अगर (err) अणु
			/* this bcm rx op is broken -> हटाओ it */
			list_del(&op->list);
			bcm_हटाओ_op(op);
			वापस err;
		पूर्ण
	पूर्ण

	वापस msg_head->nframes * op->cfsiz + MHSIZ;
पूर्ण

/*
 * bcm_tx_send - send a single CAN frame to the CAN पूर्णांकerface (क्रम bcm_sendmsg)
 */
अटल पूर्णांक bcm_tx_send(काष्ठा msghdr *msg, पूर्णांक अगरindex, काष्ठा sock *sk,
		       पूर्णांक cfsiz)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net_device *dev;
	पूर्णांक err;

	/* we need a real device to send frames */
	अगर (!अगरindex)
		वापस -ENODEV;

	skb = alloc_skb(cfsiz + माप(काष्ठा can_skb_priv), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	can_skb_reserve(skb);

	err = स_नकल_from_msg(skb_put(skb, cfsiz), msg, cfsiz);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	dev = dev_get_by_index(sock_net(sk), अगरindex);
	अगर (!dev) अणु
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	can_skb_prv(skb)->अगरindex = dev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;
	skb->dev = dev;
	can_skb_set_owner(skb, sk);
	err = can_send(skb, 1); /* send with loopback */
	dev_put(dev);

	अगर (err)
		वापस err;

	वापस cfsiz + MHSIZ;
पूर्ण

/*
 * bcm_sendmsg - process BCM commands (opcodes) from the userspace
 */
अटल पूर्णांक bcm_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा bcm_sock *bo = bcm_sk(sk);
	पूर्णांक अगरindex = bo->अगरindex; /* शेष अगरindex क्रम this bcm_op */
	काष्ठा bcm_msg_head msg_head;
	पूर्णांक cfsiz;
	पूर्णांक ret; /* पढ़ो bytes or error codes as वापस value */

	अगर (!bo->bound)
		वापस -ENOTCONN;

	/* check क्रम valid message length from userspace */
	अगर (size < MHSIZ)
		वापस -EINVAL;

	/* पढ़ो message head inक्रमmation */
	ret = स_नकल_from_msg((u8 *)&msg_head, msg, MHSIZ);
	अगर (ret < 0)
		वापस ret;

	cfsiz = CFSIZ(msg_head.flags);
	अगर ((size - MHSIZ) % cfsiz)
		वापस -EINVAL;

	/* check क्रम alternative अगरindex क्रम this bcm_op */

	अगर (!अगरindex && msg->msg_name) अणु
		/* no bound device as शेष => check msg_name */
		DECLARE_SOCKADDR(काष्ठा sockaddr_can *, addr, msg->msg_name);

		अगर (msg->msg_namelen < BCM_MIN_NAMELEN)
			वापस -EINVAL;

		अगर (addr->can_family != AF_CAN)
			वापस -EINVAL;

		/* अगरindex from sendto() */
		अगरindex = addr->can_अगरindex;

		अगर (अगरindex) अणु
			काष्ठा net_device *dev;

			dev = dev_get_by_index(sock_net(sk), अगरindex);
			अगर (!dev)
				वापस -ENODEV;

			अगर (dev->type != ARPHRD_CAN) अणु
				dev_put(dev);
				वापस -ENODEV;
			पूर्ण

			dev_put(dev);
		पूर्ण
	पूर्ण

	lock_sock(sk);

	चयन (msg_head.opcode) अणु

	हाल TX_SETUP:
		ret = bcm_tx_setup(&msg_head, msg, अगरindex, sk);
		अवरोध;

	हाल RX_SETUP:
		ret = bcm_rx_setup(&msg_head, msg, अगरindex, sk);
		अवरोध;

	हाल TX_DELETE:
		अगर (bcm_delete_tx_op(&bo->tx_ops, &msg_head, अगरindex))
			ret = MHSIZ;
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल RX_DELETE:
		अगर (bcm_delete_rx_op(&bo->rx_ops, &msg_head, अगरindex))
			ret = MHSIZ;
		अन्यथा
			ret = -EINVAL;
		अवरोध;

	हाल TX_READ:
		/* reuse msg_head क्रम the reply to TX_READ */
		msg_head.opcode  = TX_STATUS;
		ret = bcm_पढ़ो_op(&bo->tx_ops, &msg_head, अगरindex);
		अवरोध;

	हाल RX_READ:
		/* reuse msg_head क्रम the reply to RX_READ */
		msg_head.opcode  = RX_STATUS;
		ret = bcm_पढ़ो_op(&bo->rx_ops, &msg_head, अगरindex);
		अवरोध;

	हाल TX_SEND:
		/* we need exactly one CAN frame behind the msg head */
		अगर ((msg_head.nframes != 1) || (size != cfsiz + MHSIZ))
			ret = -EINVAL;
		अन्यथा
			ret = bcm_tx_send(msg, अगरindex, sk, cfsiz);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	release_sock(sk);

	वापस ret;
पूर्ण

/*
 * notअगरication handler क्रम netdevice status changes
 */
अटल व्योम bcm_notअगरy(काष्ठा bcm_sock *bo, अचिन्हित दीर्घ msg,
		       काष्ठा net_device *dev)
अणु
	काष्ठा sock *sk = &bo->sk;
	काष्ठा bcm_op *op;
	पूर्णांक notअगरy_enodev = 0;

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		वापस;

	चयन (msg) अणु

	हाल NETDEV_UNREGISTER:
		lock_sock(sk);

		/* हटाओ device specअगरic receive entries */
		list_क्रम_each_entry(op, &bo->rx_ops, list)
			अगर (op->rx_reg_dev == dev)
				bcm_rx_unreg(dev, op);

		/* हटाओ device reference, अगर this is our bound device */
		अगर (bo->bound && bo->अगरindex == dev->अगरindex) अणु
			bo->bound   = 0;
			bo->अगरindex = 0;
			notअगरy_enodev = 1;
		पूर्ण

		release_sock(sk);

		अगर (notअगरy_enodev) अणु
			sk->sk_err = ENODEV;
			अगर (!sock_flag(sk, SOCK_DEAD))
				sk->sk_error_report(sk);
		पूर्ण
		अवरोध;

	हाल NETDEV_DOWN:
		अगर (bo->bound && bo->अगरindex == dev->अगरindex) अणु
			sk->sk_err = ENETDOWN;
			अगर (!sock_flag(sk, SOCK_DEAD))
				sk->sk_error_report(sk);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ msg,
			व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (dev->type != ARPHRD_CAN)
		वापस NOTIFY_DONE;
	अगर (msg != NETDEV_UNREGISTER && msg != NETDEV_DOWN)
		वापस NOTIFY_DONE;
	अगर (unlikely(bcm_busy_notअगरier)) /* Check क्रम reentrant bug. */
		वापस NOTIFY_DONE;

	spin_lock(&bcm_notअगरier_lock);
	list_क्रम_each_entry(bcm_busy_notअगरier, &bcm_notअगरier_list, notअगरier) अणु
		spin_unlock(&bcm_notअगरier_lock);
		bcm_notअगरy(bcm_busy_notअगरier, msg, dev);
		spin_lock(&bcm_notअगरier_lock);
	पूर्ण
	bcm_busy_notअगरier = शून्य;
	spin_unlock(&bcm_notअगरier_lock);
	वापस NOTIFY_DONE;
पूर्ण

/*
 * initial settings क्रम all BCM sockets to be set at socket creation समय
 */
अटल पूर्णांक bcm_init(काष्ठा sock *sk)
अणु
	काष्ठा bcm_sock *bo = bcm_sk(sk);

	bo->bound            = 0;
	bo->अगरindex          = 0;
	bo->dropped_usr_msgs = 0;
	bo->bcm_proc_पढ़ो    = शून्य;

	INIT_LIST_HEAD(&bo->tx_ops);
	INIT_LIST_HEAD(&bo->rx_ops);

	/* set notअगरier */
	spin_lock(&bcm_notअगरier_lock);
	list_add_tail(&bo->notअगरier, &bcm_notअगरier_list);
	spin_unlock(&bcm_notअगरier_lock);

	वापस 0;
पूर्ण

/*
 * standard socket functions
 */
अटल पूर्णांक bcm_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net;
	काष्ठा bcm_sock *bo;
	काष्ठा bcm_op *op, *next;

	अगर (!sk)
		वापस 0;

	net = sock_net(sk);
	bo = bcm_sk(sk);

	/* हटाओ bcm_ops, समयr, rx_unरेजिस्टर(), etc. */

	spin_lock(&bcm_notअगरier_lock);
	जबतक (bcm_busy_notअगरier == bo) अणु
		spin_unlock(&bcm_notअगरier_lock);
		schedule_समयout_unपूर्णांकerruptible(1);
		spin_lock(&bcm_notअगरier_lock);
	पूर्ण
	list_del(&bo->notअगरier);
	spin_unlock(&bcm_notअगरier_lock);

	lock_sock(sk);

	list_क्रम_each_entry_safe(op, next, &bo->tx_ops, list)
		bcm_हटाओ_op(op);

	list_क्रम_each_entry_safe(op, next, &bo->rx_ops, list) अणु
		/*
		 * Don't care if we're bound or not (due to netdev problems)
		 * can_rx_unरेजिस्टर() is always a save thing to करो here.
		 */
		अगर (op->अगरindex) अणु
			/*
			 * Only हटाओ subscriptions that had not
			 * been हटाओd due to NETDEV_UNREGISTER
			 * in bcm_notअगरier()
			 */
			अगर (op->rx_reg_dev) अणु
				काष्ठा net_device *dev;

				dev = dev_get_by_index(net, op->अगरindex);
				अगर (dev) अणु
					bcm_rx_unreg(dev, op);
					dev_put(dev);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			can_rx_unरेजिस्टर(net, शून्य, op->can_id,
					  REGMASK(op->can_id),
					  bcm_rx_handler, op);

		bcm_हटाओ_op(op);
	पूर्ण

#अगर IS_ENABLED(CONFIG_PROC_FS)
	/* हटाओ procfs entry */
	अगर (net->can.bcmproc_dir && bo->bcm_proc_पढ़ो)
		हटाओ_proc_entry(bo->procname, net->can.bcmproc_dir);
#पूर्ण_अगर /* CONFIG_PROC_FS */

	/* हटाओ device reference */
	अगर (bo->bound) अणु
		bo->bound   = 0;
		bo->अगरindex = 0;
	पूर्ण

	sock_orphan(sk);
	sock->sk = शून्य;

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक len,
		       पूर्णांक flags)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा bcm_sock *bo = bcm_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक ret = 0;

	अगर (len < BCM_MIN_NAMELEN)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (bo->bound) अणु
		ret = -EISCONN;
		जाओ fail;
	पूर्ण

	/* bind a device to this socket */
	अगर (addr->can_अगरindex) अणु
		काष्ठा net_device *dev;

		dev = dev_get_by_index(net, addr->can_अगरindex);
		अगर (!dev) अणु
			ret = -ENODEV;
			जाओ fail;
		पूर्ण
		अगर (dev->type != ARPHRD_CAN) अणु
			dev_put(dev);
			ret = -ENODEV;
			जाओ fail;
		पूर्ण

		bo->अगरindex = dev->अगरindex;
		dev_put(dev);

	पूर्ण अन्यथा अणु
		/* no पूर्णांकerface reference क्रम अगरindex = 0 ('any' CAN device) */
		bo->अगरindex = 0;
	पूर्ण

#अगर IS_ENABLED(CONFIG_PROC_FS)
	अगर (net->can.bcmproc_dir) अणु
		/* unique socket address as filename */
		प्र_लिखो(bo->procname, "%lu", sock_i_ino(sk));
		bo->bcm_proc_पढ़ो = proc_create_net_single(bo->procname, 0644,
						     net->can.bcmproc_dir,
						     bcm_proc_show, sk);
		अगर (!bo->bcm_proc_पढ़ो) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

	bo->bound = 1;

fail:
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		       पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक error = 0;
	पूर्णांक noblock;
	पूर्णांक err;

	noblock =  flags & MSG_DONTWAIT;
	flags   &= ~MSG_DONTWAIT;
	skb = skb_recv_datagram(sk, flags, noblock, &error);
	अगर (!skb)
		वापस error;

	अगर (skb->len < size)
		size = skb->len;

	err = स_नकल_to_msg(msg, skb->data, size);
	अगर (err < 0) अणु
		skb_मुक्त_datagram(sk, skb);
		वापस err;
	पूर्ण

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (msg->msg_name) अणु
		__sockaddr_check_size(BCM_MIN_NAMELEN);
		msg->msg_namelen = BCM_MIN_NAMELEN;
		स_नकल(msg->msg_name, skb->cb, msg->msg_namelen);
	पूर्ण

	skb_मुक्त_datagram(sk, skb);

	वापस size;
पूर्ण

अटल पूर्णांक bcm_sock_no_ioctlcmd(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	/* no ioctls क्रम socket layer -> hand it करोwn to NIC layer */
	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा proto_ops bcm_ops = अणु
	.family        = PF_CAN,
	.release       = bcm_release,
	.bind          = sock_no_bind,
	.connect       = bcm_connect,
	.socketpair    = sock_no_socketpair,
	.accept        = sock_no_accept,
	.getname       = sock_no_getname,
	.poll          = datagram_poll,
	.ioctl         = bcm_sock_no_ioctlcmd,
	.gettstamp     = sock_gettstamp,
	.listen        = sock_no_listen,
	.shutकरोwn      = sock_no_shutकरोwn,
	.sendmsg       = bcm_sendmsg,
	.recvmsg       = bcm_recvmsg,
	.mmap          = sock_no_mmap,
	.sendpage      = sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto bcm_proto __पढ़ो_mostly = अणु
	.name       = "CAN_BCM",
	.owner      = THIS_MODULE,
	.obj_size   = माप(काष्ठा bcm_sock),
	.init       = bcm_init,
पूर्ण;

अटल स्थिर काष्ठा can_proto bcm_can_proto = अणु
	.type       = SOCK_DGRAM,
	.protocol   = CAN_BCM,
	.ops        = &bcm_ops,
	.prot       = &bcm_proto,
पूर्ण;

अटल पूर्णांक canbcm_pernet_init(काष्ठा net *net)
अणु
#अगर IS_ENABLED(CONFIG_PROC_FS)
	/* create /proc/net/can-bcm directory */
	net->can.bcmproc_dir = proc_net_सूची_गढ़ो(net, "can-bcm", net->proc_net);
#पूर्ण_अगर /* CONFIG_PROC_FS */

	वापस 0;
पूर्ण

अटल व्योम canbcm_pernet_निकास(काष्ठा net *net)
अणु
#अगर IS_ENABLED(CONFIG_PROC_FS)
	/* हटाओ /proc/net/can-bcm directory */
	अगर (net->can.bcmproc_dir)
		हटाओ_proc_entry("can-bcm", net->proc_net);
#पूर्ण_अगर /* CONFIG_PROC_FS */
पूर्ण

अटल काष्ठा pernet_operations canbcm_pernet_ops __पढ़ो_mostly = अणु
	.init = canbcm_pernet_init,
	.निकास = canbcm_pernet_निकास,
पूर्ण;

अटल काष्ठा notअगरier_block canbcm_notअगरier = अणु
	.notअगरier_call = bcm_notअगरier
पूर्ण;

अटल पूर्णांक __init bcm_module_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("can: broadcast manager protocol\n");

	err = can_proto_रेजिस्टर(&bcm_can_proto);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "can: registration of bcm protocol failed\n");
		वापस err;
	पूर्ण

	रेजिस्टर_pernet_subsys(&canbcm_pernet_ops);
	रेजिस्टर_netdevice_notअगरier(&canbcm_notअगरier);
	वापस 0;
पूर्ण

अटल व्योम __निकास bcm_module_निकास(व्योम)
अणु
	can_proto_unरेजिस्टर(&bcm_can_proto);
	unरेजिस्टर_netdevice_notअगरier(&canbcm_notअगरier);
	unरेजिस्टर_pernet_subsys(&canbcm_pernet_ops);
पूर्ण

module_init(bcm_module_init);
module_निकास(bcm_module_निकास);
