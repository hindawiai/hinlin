<शैली गुरु>
/*
 * Copyright (c) 2009-2014 Chelsio, Inc. All rights reserved.
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
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
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
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समयr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <net/neighbour.h>
#समावेश <net/netevent.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>

#समावेश <rdma/ib_addr.h>

#समावेश <libcxgb_cm.h>
#समावेश "iw_cxgb4.h"
#समावेश "clip_tbl.h"

अटल अक्षर *states[] = अणु
	"idle",
	"listen",
	"connecting",
	"mpa_wait_req",
	"mpa_req_sent",
	"mpa_req_rcvd",
	"mpa_rep_sent",
	"fpdu_mode",
	"aborting",
	"closing",
	"moribund",
	"dead",
	शून्य,
पूर्ण;

अटल पूर्णांक nocong;
module_param(nocong, पूर्णांक, 0644);
MODULE_PARM_DESC(nocong, "Turn of congestion control (default=0)");

अटल पूर्णांक enable_ecn;
module_param(enable_ecn, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_ecn, "Enable ECN (default=0/disabled)");

अटल पूर्णांक dack_mode;
module_param(dack_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(dack_mode, "Delayed ack mode (default=0)");

uपूर्णांक c4iw_max_पढ़ो_depth = 32;
module_param(c4iw_max_पढ़ो_depth, पूर्णांक, 0644);
MODULE_PARM_DESC(c4iw_max_पढ़ो_depth,
		 "Per-connection max ORD/IRD (default=32)");

अटल पूर्णांक enable_tcp_बारtamps;
module_param(enable_tcp_बारtamps, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_tcp_बारtamps, "Enable tcp timestamps (default=0)");

अटल पूर्णांक enable_tcp_sack;
module_param(enable_tcp_sack, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_tcp_sack, "Enable tcp SACK (default=0)");

अटल पूर्णांक enable_tcp_winकरोw_scaling = 1;
module_param(enable_tcp_winकरोw_scaling, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_tcp_winकरोw_scaling,
		 "Enable tcp window scaling (default=1)");

अटल पूर्णांक peer2peer = 1;
module_param(peer2peer, पूर्णांक, 0644);
MODULE_PARM_DESC(peer2peer, "Support peer2peer ULPs (default=1)");

अटल पूर्णांक p2p_type = FW_RI_INIT_P2PTYPE_READ_REQ;
module_param(p2p_type, पूर्णांक, 0644);
MODULE_PARM_DESC(p2p_type, "RDMAP opcode to use for the RTR message: "
			   "1=RDMA_READ 0=RDMA_WRITE (default 1)");

अटल पूर्णांक ep_समयout_secs = 60;
module_param(ep_समयout_secs, पूर्णांक, 0644);
MODULE_PARM_DESC(ep_समयout_secs, "CM Endpoint operation timeout "
				   "in seconds (default=60)");

अटल पूर्णांक mpa_rev = 2;
module_param(mpa_rev, पूर्णांक, 0644);
MODULE_PARM_DESC(mpa_rev, "MPA Revision, 0 supports amso1100, "
		"1 is RFC5044 spec compliant, 2 is IETF MPA Peer Connect Draft"
		" compliant (default=2)");

अटल पूर्णांक markers_enabled;
module_param(markers_enabled, पूर्णांक, 0644);
MODULE_PARM_DESC(markers_enabled, "Enable MPA MARKERS (default(0)=disabled)");

अटल पूर्णांक crc_enabled = 1;
module_param(crc_enabled, पूर्णांक, 0644);
MODULE_PARM_DESC(crc_enabled, "Enable MPA CRC (default(1)=enabled)");

अटल पूर्णांक rcv_win = 256 * 1024;
module_param(rcv_win, पूर्णांक, 0644);
MODULE_PARM_DESC(rcv_win, "TCP receive window in bytes (default=256KB)");

अटल पूर्णांक snd_win = 128 * 1024;
module_param(snd_win, पूर्णांक, 0644);
MODULE_PARM_DESC(snd_win, "TCP send window in bytes (default=128KB)");

अटल काष्ठा workqueue_काष्ठा *workq;

अटल काष्ठा sk_buff_head rxq;

अटल काष्ठा sk_buff *get_skb(काष्ठा sk_buff *skb, पूर्णांक len, gfp_t gfp);
अटल व्योम ep_समयout(काष्ठा समयr_list *t);
अटल व्योम connect_reply_upcall(काष्ठा c4iw_ep *ep, पूर्णांक status);
अटल पूर्णांक sched(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb);

अटल LIST_HEAD(समयout_list);
अटल DEFINE_SPINLOCK(समयout_lock);

अटल व्योम deref_cm_id(काष्ठा c4iw_ep_common *epc)
अणु
	epc->cm_id->rem_ref(epc->cm_id);
	epc->cm_id = शून्य;
	set_bit(CM_ID_DEREFED, &epc->history);
पूर्ण

अटल व्योम ref_cm_id(काष्ठा c4iw_ep_common *epc)
अणु
	set_bit(CM_ID_REFED, &epc->history);
	epc->cm_id->add_ref(epc->cm_id);
पूर्ण

अटल व्योम deref_qp(काष्ठा c4iw_ep *ep)
अणु
	c4iw_qp_rem_ref(&ep->com.qp->ibqp);
	clear_bit(QP_REFERENCED, &ep->com.flags);
	set_bit(QP_DEREFED, &ep->com.history);
पूर्ण

अटल व्योम ref_qp(काष्ठा c4iw_ep *ep)
अणु
	set_bit(QP_REFERENCED, &ep->com.flags);
	set_bit(QP_REFED, &ep->com.history);
	c4iw_qp_add_ref(&ep->com.qp->ibqp);
पूर्ण

अटल व्योम start_ep_समयr(काष्ठा c4iw_ep *ep)
अणु
	pr_debug("ep %p\n", ep);
	अगर (समयr_pending(&ep->समयr)) अणु
		pr_err("%s timer already started! ep %p\n",
		       __func__, ep);
		वापस;
	पूर्ण
	clear_bit(TIMEOUT, &ep->com.flags);
	c4iw_get_ep(&ep->com);
	ep->समयr.expires = jअगरfies + ep_समयout_secs * HZ;
	add_समयr(&ep->समयr);
पूर्ण

अटल पूर्णांक stop_ep_समयr(काष्ठा c4iw_ep *ep)
अणु
	pr_debug("ep %p stopping\n", ep);
	del_समयr_sync(&ep->समयr);
	अगर (!test_and_set_bit(TIMEOUT, &ep->com.flags)) अणु
		c4iw_put_ep(&ep->com);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक c4iw_l2t_send(काष्ठा c4iw_rdev *rdev, काष्ठा sk_buff *skb,
		  काष्ठा l2t_entry *l2e)
अणु
	पूर्णांक	error = 0;

	अगर (c4iw_fatal_error(rdev)) अणु
		kमुक्त_skb(skb);
		pr_err("%s - device in error state - dropping\n", __func__);
		वापस -EIO;
	पूर्ण
	error = cxgb4_l2t_send(rdev->lldi.ports[0], skb, l2e);
	अगर (error < 0)
		kमुक्त_skb(skb);
	अन्यथा अगर (error == NET_XMIT_DROP)
		वापस -ENOMEM;
	वापस error < 0 ? error : 0;
पूर्ण

पूर्णांक c4iw_ofld_send(काष्ठा c4iw_rdev *rdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक	error = 0;

	अगर (c4iw_fatal_error(rdev)) अणु
		kमुक्त_skb(skb);
		pr_err("%s - device in error state - dropping\n", __func__);
		वापस -EIO;
	पूर्ण
	error = cxgb4_ofld_send(rdev->lldi.ports[0], skb);
	अगर (error < 0)
		kमुक्त_skb(skb);
	वापस error < 0 ? error : 0;
पूर्ण

अटल व्योम release_tid(काष्ठा c4iw_rdev *rdev, u32 hwtid, काष्ठा sk_buff *skb)
अणु
	u32 len = roundup(माप(काष्ठा cpl_tid_release), 16);

	skb = get_skb(skb, len, GFP_KERNEL);
	अगर (!skb)
		वापस;

	cxgb_mk_tid_release(skb, len, hwtid, 0);
	c4iw_ofld_send(rdev, skb);
	वापस;
पूर्ण

अटल व्योम set_emss(काष्ठा c4iw_ep *ep, u16 opt)
अणु
	ep->emss = ep->com.dev->rdev.lldi.mtus[TCPOPT_MSS_G(opt)] -
		   ((AF_INET == ep->com.remote_addr.ss_family) ?
		    माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr)) -
		   माप(काष्ठा tcphdr);
	ep->mss = ep->emss;
	अगर (TCPOPT_TSTAMP_G(opt))
		ep->emss -= round_up(TCPOLEN_TIMESTAMP, 4);
	अगर (ep->emss < 128)
		ep->emss = 128;
	अगर (ep->emss & 7)
		pr_debug("Warning: misaligned mtu idx %u mss %u emss=%u\n",
			 TCPOPT_MSS_G(opt), ep->mss, ep->emss);
	pr_debug("mss_idx %u mss %u emss=%u\n", TCPOPT_MSS_G(opt), ep->mss,
		 ep->emss);
पूर्ण

अटल क्रमागत c4iw_ep_state state_पढ़ो(काष्ठा c4iw_ep_common *epc)
अणु
	क्रमागत c4iw_ep_state state;

	mutex_lock(&epc->mutex);
	state = epc->state;
	mutex_unlock(&epc->mutex);
	वापस state;
पूर्ण

अटल व्योम __state_set(काष्ठा c4iw_ep_common *epc, क्रमागत c4iw_ep_state new)
अणु
	epc->state = new;
पूर्ण

अटल व्योम state_set(काष्ठा c4iw_ep_common *epc, क्रमागत c4iw_ep_state new)
अणु
	mutex_lock(&epc->mutex);
	pr_debug("%s -> %s\n", states[epc->state], states[new]);
	__state_set(epc, new);
	mutex_unlock(&epc->mutex);
	वापस;
पूर्ण

अटल पूर्णांक alloc_ep_skb_list(काष्ठा sk_buff_head *ep_skb_list, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	माप_प्रकार len;

	len = roundup(माप(जोड़ cpl_wr_size), 16);
	क्रम (i = 0; i < size; i++) अणु
		skb = alloc_skb(len, GFP_KERNEL);
		अगर (!skb)
			जाओ fail;
		skb_queue_tail(ep_skb_list, skb);
	पूर्ण
	वापस 0;
fail:
	skb_queue_purge(ep_skb_list);
	वापस -ENOMEM;
पूर्ण

अटल व्योम *alloc_ep(पूर्णांक size, gfp_t gfp)
अणु
	काष्ठा c4iw_ep_common *epc;

	epc = kzalloc(size, gfp);
	अगर (epc) अणु
		epc->wr_रुकोp = c4iw_alloc_wr_रुको(gfp);
		अगर (!epc->wr_रुकोp) अणु
			kमुक्त(epc);
			epc = शून्य;
			जाओ out;
		पूर्ण
		kref_init(&epc->kref);
		mutex_init(&epc->mutex);
		c4iw_init_wr_रुको(epc->wr_रुकोp);
	पूर्ण
	pr_debug("alloc ep %p\n", epc);
out:
	वापस epc;
पूर्ण

अटल व्योम हटाओ_ep_tid(काष्ठा c4iw_ep *ep)
अणु
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&ep->com.dev->hwtids, flags);
	__xa_erase(&ep->com.dev->hwtids, ep->hwtid);
	अगर (xa_empty(&ep->com.dev->hwtids))
		wake_up(&ep->com.dev->रुको);
	xa_unlock_irqrestore(&ep->com.dev->hwtids, flags);
पूर्ण

अटल पूर्णांक insert_ep_tid(काष्ठा c4iw_ep *ep)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	xa_lock_irqsave(&ep->com.dev->hwtids, flags);
	err = __xa_insert(&ep->com.dev->hwtids, ep->hwtid, ep, GFP_KERNEL);
	xa_unlock_irqrestore(&ep->com.dev->hwtids, flags);

	वापस err;
पूर्ण

/*
 * Atomically lookup the ep ptr given the tid and grab a reference on the ep.
 */
अटल काष्ठा c4iw_ep *get_ep_from_tid(काष्ठा c4iw_dev *dev, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा c4iw_ep *ep;
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&dev->hwtids, flags);
	ep = xa_load(&dev->hwtids, tid);
	अगर (ep)
		c4iw_get_ep(&ep->com);
	xa_unlock_irqrestore(&dev->hwtids, flags);
	वापस ep;
पूर्ण

/*
 * Atomically lookup the ep ptr given the stid and grab a reference on the ep.
 */
अटल काष्ठा c4iw_listen_ep *get_ep_from_stid(काष्ठा c4iw_dev *dev,
					       अचिन्हित पूर्णांक stid)
अणु
	काष्ठा c4iw_listen_ep *ep;
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&dev->stids, flags);
	ep = xa_load(&dev->stids, stid);
	अगर (ep)
		c4iw_get_ep(&ep->com);
	xa_unlock_irqrestore(&dev->stids, flags);
	वापस ep;
पूर्ण

व्योम _c4iw_मुक्त_ep(काष्ठा kref *kref)
अणु
	काष्ठा c4iw_ep *ep;

	ep = container_of(kref, काष्ठा c4iw_ep, com.kref);
	pr_debug("ep %p state %s\n", ep, states[ep->com.state]);
	अगर (test_bit(QP_REFERENCED, &ep->com.flags))
		deref_qp(ep);
	अगर (test_bit(RELEASE_RESOURCES, &ep->com.flags)) अणु
		अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
			काष्ठा sockaddr_in6 *sin6 =
					(काष्ठा sockaddr_in6 *)
					&ep->com.local_addr;

			cxgb4_clip_release(
					ep->com.dev->rdev.lldi.ports[0],
					(स्थिर u32 *)&sin6->sin6_addr.s6_addr,
					1);
		पूर्ण
		cxgb4_हटाओ_tid(ep->com.dev->rdev.lldi.tids, 0, ep->hwtid,
				 ep->com.local_addr.ss_family);
		dst_release(ep->dst);
		cxgb4_l2t_release(ep->l2t);
		kमुक्त_skb(ep->mpa_skb);
	पूर्ण
	अगर (!skb_queue_empty(&ep->com.ep_skb_list))
		skb_queue_purge(&ep->com.ep_skb_list);
	c4iw_put_wr_रुको(ep->com.wr_रुकोp);
	kमुक्त(ep);
पूर्ण

अटल व्योम release_ep_resources(काष्ठा c4iw_ep *ep)
अणु
	set_bit(RELEASE_RESOURCES, &ep->com.flags);

	/*
	 * If we have a hwtid, then हटाओ it from the idr table
	 * so lookups will no दीर्घer find this endpoपूर्णांक.  Otherwise
	 * we have a race where one thपढ़ो finds the ep ptr just
	 * beक्रमe the other thपढ़ो is मुक्तing the ep memory.
	 */
	अगर (ep->hwtid != -1)
		हटाओ_ep_tid(ep);
	c4iw_put_ep(&ep->com);
पूर्ण

अटल पूर्णांक status2त्रुटि_सं(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल CPL_ERR_NONE:
		वापस 0;
	हाल CPL_ERR_CONN_RESET:
		वापस -ECONNRESET;
	हाल CPL_ERR_ARP_MISS:
		वापस -EHOSTUNREACH;
	हाल CPL_ERR_CONN_TIMEDOUT:
		वापस -ETIMEDOUT;
	हाल CPL_ERR_TCAM_FULL:
		वापस -ENOMEM;
	हाल CPL_ERR_CONN_EXIST:
		वापस -EADDRINUSE;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Try and reuse skbs alपढ़ोy allocated...
 */
अटल काष्ठा sk_buff *get_skb(काष्ठा sk_buff *skb, पूर्णांक len, gfp_t gfp)
अणु
	अगर (skb && !skb_is_nonlinear(skb) && !skb_cloned(skb)) अणु
		skb_trim(skb, 0);
		skb_get(skb);
		skb_reset_transport_header(skb);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(len, gfp);
		अगर (!skb)
			वापस शून्य;
	पूर्ण
	t4_set_arp_err_handler(skb, शून्य, शून्य);
	वापस skb;
पूर्ण

अटल काष्ठा net_device *get_real_dev(काष्ठा net_device *egress_dev)
अणु
	वापस rdma_vlan_dev_real_dev(egress_dev) ? : egress_dev;
पूर्ण

अटल व्योम arp_failure_discard(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	pr_err("ARP failure\n");
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम mpa_start_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	pr_err("ARP failure during MPA Negotiation - Closing Connection\n");
पूर्ण

क्रमागत अणु
	NUM_FAKE_CPLS = 2,
	FAKE_CPL_PUT_EP_SAFE = NUM_CPL_CMDS + 0,
	FAKE_CPL_PASS_PUT_EP_SAFE = NUM_CPL_CMDS + 1,
पूर्ण;

अटल पूर्णांक _put_ep_safe(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;

	ep = *((काष्ठा c4iw_ep **)(skb->cb + 2 * माप(व्योम *)));
	release_ep_resources(ep);
	वापस 0;
पूर्ण

अटल पूर्णांक _put_pass_ep_safe(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;

	ep = *((काष्ठा c4iw_ep **)(skb->cb + 2 * माप(व्योम *)));
	c4iw_put_ep(&ep->parent_ep->com);
	release_ep_resources(ep);
	वापस 0;
पूर्ण

/*
 * Fake up a special CPL opcode and call sched() so process_work() will call
 * _put_ep_safe() in a safe context to मुक्त the ep resources.  This is needed
 * because ARP error handlers are called in an ATOMIC context, and
 * _c4iw_मुक्त_ep() needs to block.
 */
अटल व्योम queue_arp_failure_cpl(काष्ठा c4iw_ep *ep, काष्ठा sk_buff *skb,
				  पूर्णांक cpl)
अणु
	काष्ठा cpl_act_establish *rpl = cplhdr(skb);

	/* Set our special ARP_FAILURE opcode */
	rpl->ot.opcode = cpl;

	/*
	 * Save ep in the skb->cb area, after where sched() will save the dev
	 * ptr.
	 */
	*((काष्ठा c4iw_ep **)(skb->cb + 2 * माप(व्योम *))) = ep;
	sched(ep->com.dev, skb);
पूर्ण

/* Handle an ARP failure क्रम an accept */
अटल व्योम pass_accept_rpl_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep = handle;

	pr_err("ARP failure during accept - tid %u - dropping connection\n",
	       ep->hwtid);

	__state_set(&ep->com, DEAD);
	queue_arp_failure_cpl(ep, skb, FAKE_CPL_PASS_PUT_EP_SAFE);
पूर्ण

/*
 * Handle an ARP failure क्रम an active खोलो.
 */
अटल व्योम act_खोलो_req_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep = handle;

	pr_err("ARP failure during connect\n");
	connect_reply_upcall(ep, -EHOSTUNREACH);
	__state_set(&ep->com, DEAD);
	अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 =
			(काष्ठा sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
	पूर्ण
	xa_erase_irq(&ep->com.dev->atids, ep->atid);
	cxgb4_मुक्त_atid(ep->com.dev->rdev.lldi.tids, ep->atid);
	queue_arp_failure_cpl(ep, skb, FAKE_CPL_PUT_EP_SAFE);
पूर्ण

/*
 * Handle an ARP failure क्रम a CPL_ABORT_REQ.  Change it पूर्णांकo a no RST variant
 * and send it aदीर्घ.
 */
अटल व्योम पात_arp_failure(व्योम *handle, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;
	काष्ठा c4iw_ep *ep = handle;
	काष्ठा c4iw_rdev *rdev = &ep->com.dev->rdev;
	काष्ठा cpl_पात_req *req = cplhdr(skb);

	pr_debug("rdev %p\n", rdev);
	req->cmd = CPL_ABORT_NO_RST;
	skb_get(skb);
	ret = c4iw_ofld_send(rdev, skb);
	अगर (ret) अणु
		__state_set(&ep->com, DEAD);
		queue_arp_failure_cpl(ep, skb, FAKE_CPL_PUT_EP_SAFE);
	पूर्ण अन्यथा
		kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक send_flowc(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा fw_flowc_wr *flowc;
	काष्ठा sk_buff *skb = skb_dequeue(&ep->com.ep_skb_list);
	u16 vlan = ep->l2t->vlan;
	पूर्णांक nparams;
	पूर्णांक flowclen, flowclen16;

	अगर (WARN_ON(!skb))
		वापस -ENOMEM;

	अगर (vlan == CPL_L2T_VLAN_NONE)
		nparams = 9;
	अन्यथा
		nparams = 10;

	flowclen = दुरत्व(काष्ठा fw_flowc_wr, mnemval[nparams]);
	flowclen16 = DIV_ROUND_UP(flowclen, 16);
	flowclen = flowclen16 * 16;

	flowc = __skb_put(skb, flowclen);
	स_रखो(flowc, 0, flowclen);

	flowc->op_to_nparams = cpu_to_be32(FW_WR_OP_V(FW_FLOWC_WR) |
					   FW_FLOWC_WR_NPARAMS_V(nparams));
	flowc->flowid_len16 = cpu_to_be32(FW_WR_LEN16_V(flowclen16) |
					  FW_WR_FLOWID_V(ep->hwtid));

	flowc->mnemval[0].mnemonic = FW_FLOWC_MNEM_PFNVFN;
	flowc->mnemval[0].val = cpu_to_be32(FW_PFVF_CMD_PFN_V
					    (ep->com.dev->rdev.lldi.pf));
	flowc->mnemval[1].mnemonic = FW_FLOWC_MNEM_CH;
	flowc->mnemval[1].val = cpu_to_be32(ep->tx_chan);
	flowc->mnemval[2].mnemonic = FW_FLOWC_MNEM_PORT;
	flowc->mnemval[2].val = cpu_to_be32(ep->tx_chan);
	flowc->mnemval[3].mnemonic = FW_FLOWC_MNEM_IQID;
	flowc->mnemval[3].val = cpu_to_be32(ep->rss_qid);
	flowc->mnemval[4].mnemonic = FW_FLOWC_MNEM_SNDNXT;
	flowc->mnemval[4].val = cpu_to_be32(ep->snd_seq);
	flowc->mnemval[5].mnemonic = FW_FLOWC_MNEM_RCVNXT;
	flowc->mnemval[5].val = cpu_to_be32(ep->rcv_seq);
	flowc->mnemval[6].mnemonic = FW_FLOWC_MNEM_SNDBUF;
	flowc->mnemval[6].val = cpu_to_be32(ep->snd_win);
	flowc->mnemval[7].mnemonic = FW_FLOWC_MNEM_MSS;
	flowc->mnemval[7].val = cpu_to_be32(ep->emss);
	flowc->mnemval[8].mnemonic = FW_FLOWC_MNEM_RCV_SCALE;
	flowc->mnemval[8].val = cpu_to_be32(ep->snd_wscale);
	अगर (nparams == 10) अणु
		u16 pri;
		pri = (vlan & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
		flowc->mnemval[9].mnemonic = FW_FLOWC_MNEM_SCHEDCLASS;
		flowc->mnemval[9].val = cpu_to_be32(pri);
	पूर्ण

	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);
	वापस c4iw_ofld_send(&ep->com.dev->rdev, skb);
पूर्ण

अटल पूर्णांक send_halख_बंद(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा sk_buff *skb = skb_dequeue(&ep->com.ep_skb_list);
	u32 wrlen = roundup(माप(काष्ठा cpl_बंद_con_req), 16);

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	अगर (WARN_ON(!skb))
		वापस -ENOMEM;

	cxgb_mk_बंद_con_req(skb, wrlen, ep->hwtid, ep->txq_idx,
			      शून्य, arp_failure_discard);

	वापस c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
पूर्ण

अटल व्योम पढ़ो_tcb(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_get_tcb *req;
	पूर्णांक wrlen = roundup(माप(*req), 16);

	skb = get_skb(शून्य, माप(*req), GFP_KERNEL);
	अगर (WARN_ON(!skb))
		वापस;

	set_wr_txq(skb, CPL_PRIORITY_CONTROL, ep->ctrlq_idx);
	req = (काष्ठा cpl_get_tcb *) skb_put(skb, wrlen);
	स_रखो(req, 0, wrlen);
	INIT_TP_WR(req, ep->hwtid);
	OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_GET_TCB, ep->hwtid));
	req->reply_ctrl = htons(REPLY_CHAN_V(0) | QUEUENO_V(ep->rss_qid));

	/*
	 * keep a ref on the ep so the tcb is not unlocked beक्रमe this
	 * cpl completes. The ref is released in पढ़ो_tcb_rpl().
	 */
	c4iw_get_ep(&ep->com);
	अगर (WARN_ON(c4iw_ofld_send(&ep->com.dev->rdev, skb)))
		c4iw_put_ep(&ep->com);
पूर्ण

अटल पूर्णांक send_पात_req(काष्ठा c4iw_ep *ep)
अणु
	u32 wrlen = roundup(माप(काष्ठा cpl_पात_req), 16);
	काष्ठा sk_buff *req_skb = skb_dequeue(&ep->com.ep_skb_list);

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	अगर (WARN_ON(!req_skb))
		वापस -ENOMEM;

	cxgb_mk_पात_req(req_skb, wrlen, ep->hwtid, ep->txq_idx,
			  ep, पात_arp_failure);

	वापस c4iw_l2t_send(&ep->com.dev->rdev, req_skb, ep->l2t);
पूर्ण

अटल पूर्णांक send_पात(काष्ठा c4iw_ep *ep)
अणु
	अगर (!ep->com.qp || !ep->com.qp->srq) अणु
		send_पात_req(ep);
		वापस 0;
	पूर्ण
	set_bit(ABORT_REQ_IN_PROGRESS, &ep->com.flags);
	पढ़ो_tcb(ep);
	वापस 0;
पूर्ण

अटल पूर्णांक send_connect(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा cpl_act_खोलो_req *req = शून्य;
	काष्ठा cpl_t5_act_खोलो_req *t5req = शून्य;
	काष्ठा cpl_t6_act_खोलो_req *t6req = शून्य;
	काष्ठा cpl_act_खोलो_req6 *req6 = शून्य;
	काष्ठा cpl_t5_act_खोलो_req6 *t5req6 = शून्य;
	काष्ठा cpl_t6_act_खोलो_req6 *t6req6 = शून्य;
	काष्ठा sk_buff *skb;
	u64 opt0;
	u32 opt2;
	अचिन्हित पूर्णांक mtu_idx;
	u32 wscale;
	पूर्णांक win, sizev4, sizev6, wrlen;
	काष्ठा sockaddr_in *la = (काष्ठा sockaddr_in *)
				 &ep->com.local_addr;
	काष्ठा sockaddr_in *ra = (काष्ठा sockaddr_in *)
				 &ep->com.remote_addr;
	काष्ठा sockaddr_in6 *la6 = (काष्ठा sockaddr_in6 *)
				   &ep->com.local_addr;
	काष्ठा sockaddr_in6 *ra6 = (काष्ठा sockaddr_in6 *)
				   &ep->com.remote_addr;
	पूर्णांक ret;
	क्रमागत chip_type adapter_type = ep->com.dev->rdev.lldi.adapter_type;
	u32 isn = (pअक्रमom_u32() & ~7UL) - 1;
	काष्ठा net_device *netdev;
	u64 params;

	netdev = ep->com.dev->rdev.lldi.ports[0];

	चयन (CHELSIO_CHIP_VERSION(adapter_type)) अणु
	हाल CHELSIO_T4:
		sizev4 = माप(काष्ठा cpl_act_खोलो_req);
		sizev6 = माप(काष्ठा cpl_act_खोलो_req6);
		अवरोध;
	हाल CHELSIO_T5:
		sizev4 = माप(काष्ठा cpl_t5_act_खोलो_req);
		sizev6 = माप(काष्ठा cpl_t5_act_खोलो_req6);
		अवरोध;
	हाल CHELSIO_T6:
		sizev4 = माप(काष्ठा cpl_t6_act_खोलो_req);
		sizev6 = माप(काष्ठा cpl_t6_act_खोलो_req6);
		अवरोध;
	शेष:
		pr_err("T%d Chip is not supported\n",
		       CHELSIO_CHIP_VERSION(adapter_type));
		वापस -EINVAL;
	पूर्ण

	wrlen = (ep->com.remote_addr.ss_family == AF_INET) ?
			roundup(sizev4, 16) :
			roundup(sizev6, 16);

	pr_debug("ep %p atid %u\n", ep, ep->atid);

	skb = get_skb(शून्य, wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("%s - failed to alloc skb\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_SETUP, ep->ctrlq_idx);

	cxgb_best_mtu(ep->com.dev->rdev.lldi.mtus, ep->mtu, &mtu_idx,
		      enable_tcp_बारtamps,
		      (ep->com.remote_addr.ss_family == AF_INET) ? 0 : 1);
	wscale = cxgb_compute_wscale(rcv_win);

	/*
	 * Specअगरy the largest winकरोw that will fit in opt0. The
	 * reमुख्यder will be specअगरied in the rx_data_ack.
	 */
	win = ep->rcv_win >> 10;
	अगर (win > RCV_बफ_मान_M)
		win = RCV_बफ_मान_M;

	opt0 = (nocong ? NO_CONG_F : 0) |
	       KEEP_ALIVE_F |
	       DELACK_F |
	       WND_SCALE_V(wscale) |
	       MSS_IDX_V(mtu_idx) |
	       L2T_IDX_V(ep->l2t->idx) |
	       TX_CHAN_V(ep->tx_chan) |
	       SMAC_SEL_V(ep->smac_idx) |
	       DSCP_V(ep->tos >> 2) |
	       ULP_MODE_V(ULP_MODE_TCPDDP) |
	       RCV_बफ_मान_V(win);
	opt2 = RX_CHANNEL_V(0) |
	       CCTRL_ECN_V(enable_ecn) |
	       RSS_QUEUE_VALID_F | RSS_QUEUE_V(ep->rss_qid);
	अगर (enable_tcp_बारtamps)
		opt2 |= TSTAMPS_EN_F;
	अगर (enable_tcp_sack)
		opt2 |= SACK_EN_F;
	अगर (wscale && enable_tcp_winकरोw_scaling)
		opt2 |= WND_SCALE_EN_F;
	अगर (CHELSIO_CHIP_VERSION(adapter_type) > CHELSIO_T4) अणु
		अगर (peer2peer)
			isn += 4;

		opt2 |= T5_OPT_2_VALID_F;
		opt2 |= CONG_CNTRL_V(CONG_ALG_TAHOE);
		opt2 |= T5_ISS_F;
	पूर्ण

	params = cxgb4_select_ntuple(netdev, ep->l2t);

	अगर (ep->com.remote_addr.ss_family == AF_INET6)
		cxgb4_clip_get(ep->com.dev->rdev.lldi.ports[0],
			       (स्थिर u32 *)&la6->sin6_addr.s6_addr, 1);

	t4_set_arp_err_handler(skb, ep, act_खोलो_req_arp_failure);

	अगर (ep->com.remote_addr.ss_family == AF_INET) अणु
		चयन (CHELSIO_CHIP_VERSION(adapter_type)) अणु
		हाल CHELSIO_T4:
			req = skb_put(skb, wrlen);
			INIT_TP_WR(req, 0);
			अवरोध;
		हाल CHELSIO_T5:
			t5req = skb_put(skb, wrlen);
			INIT_TP_WR(t5req, 0);
			req = (काष्ठा cpl_act_खोलो_req *)t5req;
			अवरोध;
		हाल CHELSIO_T6:
			t6req = skb_put(skb, wrlen);
			INIT_TP_WR(t6req, 0);
			req = (काष्ठा cpl_act_खोलो_req *)t6req;
			t5req = (काष्ठा cpl_t5_act_खोलो_req *)t6req;
			अवरोध;
		शेष:
			pr_err("T%d Chip is not supported\n",
			       CHELSIO_CHIP_VERSION(adapter_type));
			ret = -EINVAL;
			जाओ clip_release;
		पूर्ण

		OPCODE_TID(req) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ,
					((ep->rss_qid<<14) | ep->atid)));
		req->local_port = la->sin_port;
		req->peer_port = ra->sin_port;
		req->local_ip = la->sin_addr.s_addr;
		req->peer_ip = ra->sin_addr.s_addr;
		req->opt0 = cpu_to_be64(opt0);

		अगर (is_t4(ep->com.dev->rdev.lldi.adapter_type)) अणु
			req->params = cpu_to_be32(params);
			req->opt2 = cpu_to_be32(opt2);
		पूर्ण अन्यथा अणु
			अगर (is_t5(ep->com.dev->rdev.lldi.adapter_type)) अणु
				t5req->params =
					  cpu_to_be64(FILTER_TUPLE_V(params));
				t5req->rsvd = cpu_to_be32(isn);
				pr_debug("snd_isn %u\n", t5req->rsvd);
				t5req->opt2 = cpu_to_be32(opt2);
			पूर्ण अन्यथा अणु
				t6req->params =
					  cpu_to_be64(FILTER_TUPLE_V(params));
				t6req->rsvd = cpu_to_be32(isn);
				pr_debug("snd_isn %u\n", t6req->rsvd);
				t6req->opt2 = cpu_to_be32(opt2);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (CHELSIO_CHIP_VERSION(adapter_type)) अणु
		हाल CHELSIO_T4:
			req6 = skb_put(skb, wrlen);
			INIT_TP_WR(req6, 0);
			अवरोध;
		हाल CHELSIO_T5:
			t5req6 = skb_put(skb, wrlen);
			INIT_TP_WR(t5req6, 0);
			req6 = (काष्ठा cpl_act_खोलो_req6 *)t5req6;
			अवरोध;
		हाल CHELSIO_T6:
			t6req6 = skb_put(skb, wrlen);
			INIT_TP_WR(t6req6, 0);
			req6 = (काष्ठा cpl_act_खोलो_req6 *)t6req6;
			t5req6 = (काष्ठा cpl_t5_act_खोलो_req6 *)t6req6;
			अवरोध;
		शेष:
			pr_err("T%d Chip is not supported\n",
			       CHELSIO_CHIP_VERSION(adapter_type));
			ret = -EINVAL;
			जाओ clip_release;
		पूर्ण

		OPCODE_TID(req6) = cpu_to_be32(MK_OPCODE_TID(CPL_ACT_OPEN_REQ6,
					((ep->rss_qid<<14)|ep->atid)));
		req6->local_port = la6->sin6_port;
		req6->peer_port = ra6->sin6_port;
		req6->local_ip_hi = *((__be64 *)(la6->sin6_addr.s6_addr));
		req6->local_ip_lo = *((__be64 *)(la6->sin6_addr.s6_addr + 8));
		req6->peer_ip_hi = *((__be64 *)(ra6->sin6_addr.s6_addr));
		req6->peer_ip_lo = *((__be64 *)(ra6->sin6_addr.s6_addr + 8));
		req6->opt0 = cpu_to_be64(opt0);

		अगर (is_t4(ep->com.dev->rdev.lldi.adapter_type)) अणु
			req6->params = cpu_to_be32(cxgb4_select_ntuple(netdev,
								      ep->l2t));
			req6->opt2 = cpu_to_be32(opt2);
		पूर्ण अन्यथा अणु
			अगर (is_t5(ep->com.dev->rdev.lldi.adapter_type)) अणु
				t5req6->params =
					    cpu_to_be64(FILTER_TUPLE_V(params));
				t5req6->rsvd = cpu_to_be32(isn);
				pr_debug("snd_isn %u\n", t5req6->rsvd);
				t5req6->opt2 = cpu_to_be32(opt2);
			पूर्ण अन्यथा अणु
				t6req6->params =
					    cpu_to_be64(FILTER_TUPLE_V(params));
				t6req6->rsvd = cpu_to_be32(isn);
				pr_debug("snd_isn %u\n", t6req6->rsvd);
				t6req6->opt2 = cpu_to_be32(opt2);
			पूर्ण

		पूर्ण
	पूर्ण

	set_bit(ACT_OPEN_REQ, &ep->com.history);
	ret = c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
clip_release:
	अगर (ret && ep->com.remote_addr.ss_family == AF_INET6)
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&la6->sin6_addr.s6_addr, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक send_mpa_req(काष्ठा c4iw_ep *ep, काष्ठा sk_buff *skb,
			u8 mpa_rev_to_use)
अणु
	पूर्णांक mpalen, wrlen, ret;
	काष्ठा fw_ofld_tx_data_wr *req;
	काष्ठा mpa_message *mpa;
	काष्ठा mpa_v2_conn_params mpa_v2_params;

	pr_debug("ep %p tid %u pd_len %d\n",
		 ep, ep->hwtid, ep->plen);

	mpalen = माप(*mpa) + ep->plen;
	अगर (mpa_rev_to_use == 2)
		mpalen += माप(काष्ठा mpa_v2_conn_params);
	wrlen = roundup(mpalen + माप(*req), 16);
	skb = get_skb(skb, wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		connect_reply_upcall(ep, -ENOMEM);
		वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);

	req = skb_put_zero(skb, wrlen);
	req->op_to_immdlen = cpu_to_be32(
		FW_WR_OP_V(FW_OFLD_TX_DATA_WR) |
		FW_WR_COMPL_F |
		FW_WR_IMMDLEN_V(mpalen));
	req->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(ep->hwtid) |
		FW_WR_LEN16_V(wrlen >> 4));
	req->plen = cpu_to_be32(mpalen);
	req->tunnel_to_proxy = cpu_to_be32(
		FW_OFLD_TX_DATA_WR_FLUSH_F |
		FW_OFLD_TX_DATA_WR_SHOVE_F);

	mpa = (काष्ठा mpa_message *)(req + 1);
	स_नकल(mpa->key, MPA_KEY_REQ, माप(mpa->key));

	mpa->flags = 0;
	अगर (crc_enabled)
		mpa->flags |= MPA_CRC;
	अगर (markers_enabled) अणु
		mpa->flags |= MPA_MARKERS;
		ep->mpa_attr.recv_marker_enabled = 1;
	पूर्ण अन्यथा अणु
		ep->mpa_attr.recv_marker_enabled = 0;
	पूर्ण
	अगर (mpa_rev_to_use == 2)
		mpa->flags |= MPA_ENHANCED_RDMA_CONN;

	mpa->निजी_data_size = htons(ep->plen);
	mpa->revision = mpa_rev_to_use;
	अगर (mpa_rev_to_use == 1) अणु
		ep->tried_with_mpa_v1 = 1;
		ep->retry_with_mpa_v1 = 0;
	पूर्ण

	अगर (mpa_rev_to_use == 2) अणु
		mpa->निजी_data_size =
			htons(ntohs(mpa->निजी_data_size) +
			      माप(काष्ठा mpa_v2_conn_params));
		pr_debug("initiator ird %u ord %u\n", ep->ird,
			 ep->ord);
		mpa_v2_params.ird = htons((u16)ep->ird);
		mpa_v2_params.ord = htons((u16)ep->ord);

		अगर (peer2peer) अणु
			mpa_v2_params.ird |= htons(MPA_V2_PEER2PEER_MODEL);
			अगर (p2p_type == FW_RI_INIT_P2PTYPE_RDMA_WRITE)
				mpa_v2_params.ord |=
					htons(MPA_V2_RDMA_WRITE_RTR);
			अन्यथा अगर (p2p_type == FW_RI_INIT_P2PTYPE_READ_REQ)
				mpa_v2_params.ord |=
					htons(MPA_V2_RDMA_READ_RTR);
		पूर्ण
		स_नकल(mpa->निजी_data, &mpa_v2_params,
		       माप(काष्ठा mpa_v2_conn_params));

		अगर (ep->plen)
			स_नकल(mpa->निजी_data +
			       माप(काष्ठा mpa_v2_conn_params),
			       ep->mpa_pkt + माप(*mpa), ep->plen);
	पूर्ण अन्यथा
		अगर (ep->plen)
			स_नकल(mpa->निजी_data,
					ep->mpa_pkt + माप(*mpa), ep->plen);

	/*
	 * Reference the mpa skb.  This ensures the data area
	 * will reमुख्य in memory until the hw acks the tx.
	 * Function fw4_ack() will deref it.
	 */
	skb_get(skb);
	t4_set_arp_err_handler(skb, शून्य, arp_failure_discard);
	ep->mpa_skb = skb;
	ret = c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
	अगर (ret)
		वापस ret;
	start_ep_समयr(ep);
	__state_set(&ep->com, MPA_REQ_SENT);
	ep->mpa_attr.initiator = 1;
	ep->snd_seq += mpalen;
	वापस ret;
पूर्ण

अटल पूर्णांक send_mpa_reject(काष्ठा c4iw_ep *ep, स्थिर व्योम *pdata, u8 plen)
अणु
	पूर्णांक mpalen, wrlen;
	काष्ठा fw_ofld_tx_data_wr *req;
	काष्ठा mpa_message *mpa;
	काष्ठा sk_buff *skb;
	काष्ठा mpa_v2_conn_params mpa_v2_params;

	pr_debug("ep %p tid %u pd_len %d\n",
		 ep, ep->hwtid, ep->plen);

	mpalen = माप(*mpa) + plen;
	अगर (ep->mpa_attr.version == 2 && ep->mpa_attr.enhanced_rdma_conn)
		mpalen += माप(काष्ठा mpa_v2_conn_params);
	wrlen = roundup(mpalen + माप(*req), 16);

	skb = get_skb(शून्य, wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("%s - cannot alloc skb!\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);

	req = skb_put_zero(skb, wrlen);
	req->op_to_immdlen = cpu_to_be32(
		FW_WR_OP_V(FW_OFLD_TX_DATA_WR) |
		FW_WR_COMPL_F |
		FW_WR_IMMDLEN_V(mpalen));
	req->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(ep->hwtid) |
		FW_WR_LEN16_V(wrlen >> 4));
	req->plen = cpu_to_be32(mpalen);
	req->tunnel_to_proxy = cpu_to_be32(
		FW_OFLD_TX_DATA_WR_FLUSH_F |
		FW_OFLD_TX_DATA_WR_SHOVE_F);

	mpa = (काष्ठा mpa_message *)(req + 1);
	स_रखो(mpa, 0, माप(*mpa));
	स_नकल(mpa->key, MPA_KEY_REP, माप(mpa->key));
	mpa->flags = MPA_REJECT;
	mpa->revision = ep->mpa_attr.version;
	mpa->निजी_data_size = htons(plen);

	अगर (ep->mpa_attr.version == 2 && ep->mpa_attr.enhanced_rdma_conn) अणु
		mpa->flags |= MPA_ENHANCED_RDMA_CONN;
		mpa->निजी_data_size =
			htons(ntohs(mpa->निजी_data_size) +
			      माप(काष्ठा mpa_v2_conn_params));
		mpa_v2_params.ird = htons(((u16)ep->ird) |
					  (peer2peer ? MPA_V2_PEER2PEER_MODEL :
					   0));
		mpa_v2_params.ord = htons(((u16)ep->ord) | (peer2peer ?
					  (p2p_type ==
					   FW_RI_INIT_P2PTYPE_RDMA_WRITE ?
					   MPA_V2_RDMA_WRITE_RTR : p2p_type ==
					   FW_RI_INIT_P2PTYPE_READ_REQ ?
					   MPA_V2_RDMA_READ_RTR : 0) : 0));
		स_नकल(mpa->निजी_data, &mpa_v2_params,
		       माप(काष्ठा mpa_v2_conn_params));

		अगर (ep->plen)
			स_नकल(mpa->निजी_data +
			       माप(काष्ठा mpa_v2_conn_params), pdata, plen);
	पूर्ण अन्यथा
		अगर (plen)
			स_नकल(mpa->निजी_data, pdata, plen);

	/*
	 * Reference the mpa skb again.  This ensures the data area
	 * will reमुख्य in memory until the hw acks the tx.
	 * Function fw4_ack() will deref it.
	 */
	skb_get(skb);
	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);
	t4_set_arp_err_handler(skb, शून्य, mpa_start_arp_failure);
	ep->mpa_skb = skb;
	ep->snd_seq += mpalen;
	वापस c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
पूर्ण

अटल पूर्णांक send_mpa_reply(काष्ठा c4iw_ep *ep, स्थिर व्योम *pdata, u8 plen)
अणु
	पूर्णांक mpalen, wrlen;
	काष्ठा fw_ofld_tx_data_wr *req;
	काष्ठा mpa_message *mpa;
	काष्ठा sk_buff *skb;
	काष्ठा mpa_v2_conn_params mpa_v2_params;

	pr_debug("ep %p tid %u pd_len %d\n",
		 ep, ep->hwtid, ep->plen);

	mpalen = माप(*mpa) + plen;
	अगर (ep->mpa_attr.version == 2 && ep->mpa_attr.enhanced_rdma_conn)
		mpalen += माप(काष्ठा mpa_v2_conn_params);
	wrlen = roundup(mpalen + माप(*req), 16);

	skb = get_skb(शून्य, wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("%s - cannot alloc skb!\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);

	req = skb_put_zero(skb, wrlen);
	req->op_to_immdlen = cpu_to_be32(
		FW_WR_OP_V(FW_OFLD_TX_DATA_WR) |
		FW_WR_COMPL_F |
		FW_WR_IMMDLEN_V(mpalen));
	req->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(ep->hwtid) |
		FW_WR_LEN16_V(wrlen >> 4));
	req->plen = cpu_to_be32(mpalen);
	req->tunnel_to_proxy = cpu_to_be32(
		FW_OFLD_TX_DATA_WR_FLUSH_F |
		FW_OFLD_TX_DATA_WR_SHOVE_F);

	mpa = (काष्ठा mpa_message *)(req + 1);
	स_रखो(mpa, 0, माप(*mpa));
	स_नकल(mpa->key, MPA_KEY_REP, माप(mpa->key));
	mpa->flags = 0;
	अगर (ep->mpa_attr.crc_enabled)
		mpa->flags |= MPA_CRC;
	अगर (ep->mpa_attr.recv_marker_enabled)
		mpa->flags |= MPA_MARKERS;
	mpa->revision = ep->mpa_attr.version;
	mpa->निजी_data_size = htons(plen);

	अगर (ep->mpa_attr.version == 2 && ep->mpa_attr.enhanced_rdma_conn) अणु
		mpa->flags |= MPA_ENHANCED_RDMA_CONN;
		mpa->निजी_data_size =
			htons(ntohs(mpa->निजी_data_size) +
			      माप(काष्ठा mpa_v2_conn_params));
		mpa_v2_params.ird = htons((u16)ep->ird);
		mpa_v2_params.ord = htons((u16)ep->ord);
		अगर (peer2peer && (ep->mpa_attr.p2p_type !=
					FW_RI_INIT_P2PTYPE_DISABLED)) अणु
			mpa_v2_params.ird |= htons(MPA_V2_PEER2PEER_MODEL);

			अगर (p2p_type == FW_RI_INIT_P2PTYPE_RDMA_WRITE)
				mpa_v2_params.ord |=
					htons(MPA_V2_RDMA_WRITE_RTR);
			अन्यथा अगर (p2p_type == FW_RI_INIT_P2PTYPE_READ_REQ)
				mpa_v2_params.ord |=
					htons(MPA_V2_RDMA_READ_RTR);
		पूर्ण

		स_नकल(mpa->निजी_data, &mpa_v2_params,
		       माप(काष्ठा mpa_v2_conn_params));

		अगर (ep->plen)
			स_नकल(mpa->निजी_data +
			       माप(काष्ठा mpa_v2_conn_params), pdata, plen);
	पूर्ण अन्यथा
		अगर (plen)
			स_नकल(mpa->निजी_data, pdata, plen);

	/*
	 * Reference the mpa skb.  This ensures the data area
	 * will reमुख्य in memory until the hw acks the tx.
	 * Function fw4_ack() will deref it.
	 */
	skb_get(skb);
	t4_set_arp_err_handler(skb, शून्य, mpa_start_arp_failure);
	ep->mpa_skb = skb;
	__state_set(&ep->com, MPA_REP_SENT);
	ep->snd_seq += mpalen;
	वापस c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
पूर्ण

अटल पूर्णांक act_establish(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_act_establish *req = cplhdr(skb);
	अचिन्हित लघु tcp_opt = ntohs(req->tcp_opt);
	अचिन्हित पूर्णांक tid = GET_TID(req);
	अचिन्हित पूर्णांक atid = TID_TID_G(ntohl(req->tos_atid));
	काष्ठा tid_info *t = dev->rdev.lldi.tids;
	पूर्णांक ret;

	ep = lookup_atid(t, atid);

	pr_debug("ep %p tid %u snd_isn %u rcv_isn %u\n", ep, tid,
		 be32_to_cpu(req->snd_isn), be32_to_cpu(req->rcv_isn));

	mutex_lock(&ep->com.mutex);
	dst_confirm(ep->dst);

	/* setup the hwtid क्रम this connection */
	ep->hwtid = tid;
	cxgb4_insert_tid(t, ep, tid, ep->com.local_addr.ss_family);
	insert_ep_tid(ep);

	ep->snd_seq = be32_to_cpu(req->snd_isn);
	ep->rcv_seq = be32_to_cpu(req->rcv_isn);
	ep->snd_wscale = TCPOPT_SND_WSCALE_G(tcp_opt);

	set_emss(ep, tcp_opt);

	/* dealloc the atid */
	xa_erase_irq(&ep->com.dev->atids, atid);
	cxgb4_मुक्त_atid(t, atid);
	set_bit(ACT_ESTAB, &ep->com.history);

	/* start MPA negotiation */
	ret = send_flowc(ep);
	अगर (ret)
		जाओ err;
	अगर (ep->retry_with_mpa_v1)
		ret = send_mpa_req(ep, skb, 1);
	अन्यथा
		ret = send_mpa_req(ep, skb, mpa_rev);
	अगर (ret)
		जाओ err;
	mutex_unlock(&ep->com.mutex);
	वापस 0;
err:
	mutex_unlock(&ep->com.mutex);
	connect_reply_upcall(ep, -ENOMEM);
	c4iw_ep_disconnect(ep, 0, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल व्योम बंद_complete_upcall(काष्ठा c4iw_ep *ep, पूर्णांक status)
अणु
	काष्ठा iw_cm_event event;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_CLOSE;
	event.status = status;
	अगर (ep->com.cm_id) अणु
		pr_debug("close complete delivered ep %p cm_id %p tid %u\n",
			 ep, ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		deref_cm_id(&ep->com);
		set_bit(CLOSE_UPCALL, &ep->com.history);
	पूर्ण
पूर्ण

अटल व्योम peer_बंद_upcall(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा iw_cm_event event;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_DISCONNECT;
	अगर (ep->com.cm_id) अणु
		pr_debug("peer close delivered ep %p cm_id %p tid %u\n",
			 ep, ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		set_bit(DISCONN_UPCALL, &ep->com.history);
	पूर्ण
पूर्ण

अटल व्योम peer_पात_upcall(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा iw_cm_event event;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_CLOSE;
	event.status = -ECONNRESET;
	अगर (ep->com.cm_id) अणु
		pr_debug("abort delivered ep %p cm_id %p tid %u\n", ep,
			 ep->com.cm_id, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		deref_cm_id(&ep->com);
		set_bit(ABORT_UPCALL, &ep->com.history);
	पूर्ण
पूर्ण

अटल व्योम connect_reply_upcall(काष्ठा c4iw_ep *ep, पूर्णांक status)
अणु
	काष्ठा iw_cm_event event;

	pr_debug("ep %p tid %u status %d\n",
		 ep, ep->hwtid, status);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_CONNECT_REPLY;
	event.status = status;
	स_नकल(&event.local_addr, &ep->com.local_addr,
	       माप(ep->com.local_addr));
	स_नकल(&event.remote_addr, &ep->com.remote_addr,
	       माप(ep->com.remote_addr));

	अगर ((status == 0) || (status == -ECONNREFUSED)) अणु
		अगर (!ep->tried_with_mpa_v1) अणु
			/* this means MPA_v2 is used */
			event.ord = ep->ird;
			event.ird = ep->ord;
			event.निजी_data_len = ep->plen -
				माप(काष्ठा mpa_v2_conn_params);
			event.निजी_data = ep->mpa_pkt +
				माप(काष्ठा mpa_message) +
				माप(काष्ठा mpa_v2_conn_params);
		पूर्ण अन्यथा अणु
			/* this means MPA_v1 is used */
			event.ord = cur_max_पढ़ो_depth(ep->com.dev);
			event.ird = cur_max_पढ़ो_depth(ep->com.dev);
			event.निजी_data_len = ep->plen;
			event.निजी_data = ep->mpa_pkt +
				माप(काष्ठा mpa_message);
		पूर्ण
	पूर्ण

	pr_debug("ep %p tid %u status %d\n", ep,
		 ep->hwtid, status);
	set_bit(CONN_RPL_UPCALL, &ep->com.history);
	ep->com.cm_id->event_handler(ep->com.cm_id, &event);

	अगर (status < 0)
		deref_cm_id(&ep->com);
पूर्ण

अटल पूर्णांक connect_request_upcall(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा iw_cm_event event;
	पूर्णांक ret;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_CONNECT_REQUEST;
	स_नकल(&event.local_addr, &ep->com.local_addr,
	       माप(ep->com.local_addr));
	स_नकल(&event.remote_addr, &ep->com.remote_addr,
	       माप(ep->com.remote_addr));
	event.provider_data = ep;
	अगर (!ep->tried_with_mpa_v1) अणु
		/* this means MPA_v2 is used */
		event.ord = ep->ord;
		event.ird = ep->ird;
		event.निजी_data_len = ep->plen -
			माप(काष्ठा mpa_v2_conn_params);
		event.निजी_data = ep->mpa_pkt + माप(काष्ठा mpa_message) +
			माप(काष्ठा mpa_v2_conn_params);
	पूर्ण अन्यथा अणु
		/* this means MPA_v1 is used. Send max supported */
		event.ord = cur_max_पढ़ो_depth(ep->com.dev);
		event.ird = cur_max_पढ़ो_depth(ep->com.dev);
		event.निजी_data_len = ep->plen;
		event.निजी_data = ep->mpa_pkt + माप(काष्ठा mpa_message);
	पूर्ण
	c4iw_get_ep(&ep->com);
	ret = ep->parent_ep->com.cm_id->event_handler(ep->parent_ep->com.cm_id,
						      &event);
	अगर (ret)
		c4iw_put_ep(&ep->com);
	set_bit(CONNREQ_UPCALL, &ep->com.history);
	c4iw_put_ep(&ep->parent_ep->com);
	वापस ret;
पूर्ण

अटल व्योम established_upcall(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा iw_cm_event event;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	स_रखो(&event, 0, माप(event));
	event.event = IW_CM_EVENT_ESTABLISHED;
	event.ird = ep->ord;
	event.ord = ep->ird;
	अगर (ep->com.cm_id) अणु
		pr_debug("ep %p tid %u\n", ep, ep->hwtid);
		ep->com.cm_id->event_handler(ep->com.cm_id, &event);
		set_bit(ESTAB_UPCALL, &ep->com.history);
	पूर्ण
पूर्ण

अटल पूर्णांक update_rx_credits(काष्ठा c4iw_ep *ep, u32 credits)
अणु
	काष्ठा sk_buff *skb;
	u32 wrlen = roundup(माप(काष्ठा cpl_rx_data_ack), 16);
	u32 credit_dack;

	pr_debug("ep %p tid %u credits %u\n",
		 ep, ep->hwtid, credits);
	skb = get_skb(शून्य, wrlen, GFP_KERNEL);
	अगर (!skb) अणु
		pr_err("update_rx_credits - cannot alloc skb!\n");
		वापस 0;
	पूर्ण

	/*
	 * If we couldn't specअगरy the entire rcv winकरोw at connection setup
	 * due to the limit in the number of bits in the RCV_बफ_मान field,
	 * then add the overage in to the credits वापसed.
	 */
	अगर (ep->rcv_win > RCV_बफ_मान_M * 1024)
		credits += ep->rcv_win - RCV_बफ_मान_M * 1024;

	credit_dack = credits | RX_FORCE_ACK_F | RX_DACK_CHANGE_F |
		      RX_DACK_MODE_V(dack_mode);

	cxgb_mk_rx_data_ack(skb, wrlen, ep->hwtid, ep->ctrlq_idx,
			    credit_dack);

	c4iw_ofld_send(&ep->com.dev->rdev, skb);
	वापस credits;
पूर्ण

#घोषणा RELAXED_IRD_NEGOTIATION 1

/*
 * process_mpa_reply - process streaming mode MPA reply
 *
 * Returns:
 *
 * 0 upon success indicating a connect request was delivered to the ULP
 * or the mpa request is incomplete but valid so far.
 *
 * 1 अगर a failure requires the caller to बंद the connection.
 *
 * 2 अगर a failure requires the caller to पात the connection.
 */
अटल पूर्णांक process_mpa_reply(काष्ठा c4iw_ep *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा mpa_message *mpa;
	काष्ठा mpa_v2_conn_params *mpa_v2_params;
	u16 plen;
	u16 resp_ird, resp_ord;
	u8 rtr_mismatch = 0, insuff_ird = 0;
	काष्ठा c4iw_qp_attributes attrs;
	क्रमागत c4iw_qp_attr_mask mask;
	पूर्णांक err;
	पूर्णांक disconnect = 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	/*
	 * If we get more than the supported amount of निजी data
	 * then we must fail this connection.
	 */
	अगर (ep->mpa_pkt_len + skb->len > माप(ep->mpa_pkt)) अणु
		err = -EINVAL;
		जाओ err_stop_समयr;
	पूर्ण

	/*
	 * copy the new data पूर्णांकo our accumulation buffer.
	 */
	skb_copy_from_linear_data(skb, &(ep->mpa_pkt[ep->mpa_pkt_len]),
				  skb->len);
	ep->mpa_pkt_len += skb->len;

	/*
	 * अगर we करोn't even have the mpa message, then bail.
	 */
	अगर (ep->mpa_pkt_len < माप(*mpa))
		वापस 0;
	mpa = (काष्ठा mpa_message *) ep->mpa_pkt;

	/* Validate MPA header. */
	अगर (mpa->revision > mpa_rev) अणु
		pr_err("%s MPA version mismatch. Local = %d, Received = %d\n",
		       __func__, mpa_rev, mpa->revision);
		err = -EPROTO;
		जाओ err_stop_समयr;
	पूर्ण
	अगर (स_भेद(mpa->key, MPA_KEY_REP, माप(mpa->key))) अणु
		err = -EPROTO;
		जाओ err_stop_समयr;
	पूर्ण

	plen = ntohs(mpa->निजी_data_size);

	/*
	 * Fail अगर there's too much निजी data.
	 */
	अगर (plen > MPA_MAX_PRIVATE_DATA) अणु
		err = -EPROTO;
		जाओ err_stop_समयr;
	पूर्ण

	/*
	 * If plen करोes not account क्रम pkt size
	 */
	अगर (ep->mpa_pkt_len > (माप(*mpa) + plen)) अणु
		err = -EPROTO;
		जाओ err_stop_समयr;
	पूर्ण

	ep->plen = (u8) plen;

	/*
	 * If we करोn't have all the pdata yet, then bail.
	 * We'll जारी process when more data arrives.
	 */
	अगर (ep->mpa_pkt_len < (माप(*mpa) + plen))
		वापस 0;

	अगर (mpa->flags & MPA_REJECT) अणु
		err = -ECONNREFUSED;
		जाओ err_stop_समयr;
	पूर्ण

	/*
	 * Stop mpa समयr.  If it expired, then
	 * we ignore the MPA reply.  process_समयout()
	 * will पात the connection.
	 */
	अगर (stop_ep_समयr(ep))
		वापस 0;

	/*
	 * If we get here we have accumulated the entire mpa
	 * start reply message including निजी data. And
	 * the MPA header is valid.
	 */
	__state_set(&ep->com, FPDU_MODE);
	ep->mpa_attr.crc_enabled = (mpa->flags & MPA_CRC) | crc_enabled ? 1 : 0;
	ep->mpa_attr.xmit_marker_enabled = mpa->flags & MPA_MARKERS ? 1 : 0;
	ep->mpa_attr.version = mpa->revision;
	ep->mpa_attr.p2p_type = FW_RI_INIT_P2PTYPE_DISABLED;

	अगर (mpa->revision == 2) अणु
		ep->mpa_attr.enhanced_rdma_conn =
			mpa->flags & MPA_ENHANCED_RDMA_CONN ? 1 : 0;
		अगर (ep->mpa_attr.enhanced_rdma_conn) अणु
			mpa_v2_params = (काष्ठा mpa_v2_conn_params *)
				(ep->mpa_pkt + माप(*mpa));
			resp_ird = ntohs(mpa_v2_params->ird) &
				MPA_V2_IRD_ORD_MASK;
			resp_ord = ntohs(mpa_v2_params->ord) &
				MPA_V2_IRD_ORD_MASK;
			pr_debug("responder ird %u ord %u ep ird %u ord %u\n",
				 resp_ird, resp_ord, ep->ird, ep->ord);

			/*
			 * This is a द्विगुन-check. Ideally, below checks are
			 * not required since ird/ord stuff has been taken
			 * care of in c4iw_accept_cr
			 */
			अगर (ep->ird < resp_ord) अणु
				अगर (RELAXED_IRD_NEGOTIATION && resp_ord <=
				    ep->com.dev->rdev.lldi.max_ordird_qp)
					ep->ird = resp_ord;
				अन्यथा
					insuff_ird = 1;
			पूर्ण अन्यथा अगर (ep->ird > resp_ord) अणु
				ep->ird = resp_ord;
			पूर्ण
			अगर (ep->ord > resp_ird) अणु
				अगर (RELAXED_IRD_NEGOTIATION)
					ep->ord = resp_ird;
				अन्यथा
					insuff_ird = 1;
			पूर्ण
			अगर (insuff_ird) अणु
				err = -ENOMEM;
				ep->ird = resp_ord;
				ep->ord = resp_ird;
			पूर्ण

			अगर (ntohs(mpa_v2_params->ird) &
					MPA_V2_PEER2PEER_MODEL) अणु
				अगर (ntohs(mpa_v2_params->ord) &
						MPA_V2_RDMA_WRITE_RTR)
					ep->mpa_attr.p2p_type =
						FW_RI_INIT_P2PTYPE_RDMA_WRITE;
				अन्यथा अगर (ntohs(mpa_v2_params->ord) &
						MPA_V2_RDMA_READ_RTR)
					ep->mpa_attr.p2p_type =
						FW_RI_INIT_P2PTYPE_READ_REQ;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (mpa->revision == 1)
		अगर (peer2peer)
			ep->mpa_attr.p2p_type = p2p_type;

	pr_debug("crc_enabled=%d, recv_marker_enabled=%d, xmit_marker_enabled=%d, version=%d p2p_type=%d local-p2p_type = %d\n",
		 ep->mpa_attr.crc_enabled,
		 ep->mpa_attr.recv_marker_enabled,
		 ep->mpa_attr.xmit_marker_enabled, ep->mpa_attr.version,
		 ep->mpa_attr.p2p_type, p2p_type);

	/*
	 * If responder's RTR करोes not match with that of initiator, assign
	 * FW_RI_INIT_P2PTYPE_DISABLED in mpa attributes so that RTR is not
	 * generated when moving QP to RTS state.
	 * A TERM message will be sent after QP has moved to RTS state
	 */
	अगर ((ep->mpa_attr.version == 2) && peer2peer &&
			(ep->mpa_attr.p2p_type != p2p_type)) अणु
		ep->mpa_attr.p2p_type = FW_RI_INIT_P2PTYPE_DISABLED;
		rtr_mismatch = 1;
	पूर्ण

	attrs.mpa_attr = ep->mpa_attr;
	attrs.max_ird = ep->ird;
	attrs.max_ord = ep->ord;
	attrs.llp_stream_handle = ep;
	attrs.next_state = C4IW_QP_STATE_RTS;

	mask = C4IW_QP_ATTR_NEXT_STATE |
	    C4IW_QP_ATTR_LLP_STREAM_HANDLE | C4IW_QP_ATTR_MPA_ATTR |
	    C4IW_QP_ATTR_MAX_IRD | C4IW_QP_ATTR_MAX_ORD;

	/* bind QP and TID with INIT_WR */
	err = c4iw_modअगरy_qp(ep->com.qp->rhp,
			     ep->com.qp, mask, &attrs, 1);
	अगर (err)
		जाओ err;

	/*
	 * If responder's RTR requirement did not match with what initiator
	 * supports, generate TERM message
	 */
	अगर (rtr_mismatch) अणु
		pr_err("%s: RTR mismatch, sending TERM\n", __func__);
		attrs.layer_etype = LAYER_MPA | DDP_LLP;
		attrs.ecode = MPA_NOMATCH_RTR;
		attrs.next_state = C4IW_QP_STATE_TERMINATE;
		attrs.send_term = 1;
		err = c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
				C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		err = -ENOMEM;
		disconnect = 1;
		जाओ out;
	पूर्ण

	/*
	 * Generate TERM अगर initiator IRD is not sufficient क्रम responder
	 * provided ORD. Currently, we करो the same behaviour even when
	 * responder provided IRD is also not sufficient as regards to
	 * initiator ORD.
	 */
	अगर (insuff_ird) अणु
		pr_err("%s: Insufficient IRD, sending TERM\n", __func__);
		attrs.layer_etype = LAYER_MPA | DDP_LLP;
		attrs.ecode = MPA_INSUFF_IRD;
		attrs.next_state = C4IW_QP_STATE_TERMINATE;
		attrs.send_term = 1;
		err = c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
				C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		err = -ENOMEM;
		disconnect = 1;
		जाओ out;
	पूर्ण
	जाओ out;
err_stop_समयr:
	stop_ep_समयr(ep);
err:
	disconnect = 2;
out:
	connect_reply_upcall(ep, err);
	वापस disconnect;
पूर्ण

/*
 * process_mpa_request - process streaming mode MPA request
 *
 * Returns:
 *
 * 0 upon success indicating a connect request was delivered to the ULP
 * or the mpa request is incomplete but valid so far.
 *
 * 1 अगर a failure requires the caller to बंद the connection.
 *
 * 2 अगर a failure requires the caller to पात the connection.
 */
अटल पूर्णांक process_mpa_request(काष्ठा c4iw_ep *ep, काष्ठा sk_buff *skb)
अणु
	काष्ठा mpa_message *mpa;
	काष्ठा mpa_v2_conn_params *mpa_v2_params;
	u16 plen;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	/*
	 * If we get more than the supported amount of निजी data
	 * then we must fail this connection.
	 */
	अगर (ep->mpa_pkt_len + skb->len > माप(ep->mpa_pkt))
		जाओ err_stop_समयr;

	pr_debug("enter (%s line %u)\n", __खाता__, __LINE__);

	/*
	 * Copy the new data पूर्णांकo our accumulation buffer.
	 */
	skb_copy_from_linear_data(skb, &(ep->mpa_pkt[ep->mpa_pkt_len]),
				  skb->len);
	ep->mpa_pkt_len += skb->len;

	/*
	 * If we करोn't even have the mpa message, then bail.
	 * We'll जारी process when more data arrives.
	 */
	अगर (ep->mpa_pkt_len < माप(*mpa))
		वापस 0;

	pr_debug("enter (%s line %u)\n", __खाता__, __LINE__);
	mpa = (काष्ठा mpa_message *) ep->mpa_pkt;

	/*
	 * Validate MPA Header.
	 */
	अगर (mpa->revision > mpa_rev) अणु
		pr_err("%s MPA version mismatch. Local = %d, Received = %d\n",
		       __func__, mpa_rev, mpa->revision);
		जाओ err_stop_समयr;
	पूर्ण

	अगर (स_भेद(mpa->key, MPA_KEY_REQ, माप(mpa->key)))
		जाओ err_stop_समयr;

	plen = ntohs(mpa->निजी_data_size);

	/*
	 * Fail अगर there's too much निजी data.
	 */
	अगर (plen > MPA_MAX_PRIVATE_DATA)
		जाओ err_stop_समयr;

	/*
	 * If plen करोes not account क्रम pkt size
	 */
	अगर (ep->mpa_pkt_len > (माप(*mpa) + plen))
		जाओ err_stop_समयr;
	ep->plen = (u8) plen;

	/*
	 * If we करोn't have all the pdata yet, then bail.
	 */
	अगर (ep->mpa_pkt_len < (माप(*mpa) + plen))
		वापस 0;

	/*
	 * If we get here we have accumulated the entire mpa
	 * start reply message including निजी data.
	 */
	ep->mpa_attr.initiator = 0;
	ep->mpa_attr.crc_enabled = (mpa->flags & MPA_CRC) | crc_enabled ? 1 : 0;
	ep->mpa_attr.recv_marker_enabled = markers_enabled;
	ep->mpa_attr.xmit_marker_enabled = mpa->flags & MPA_MARKERS ? 1 : 0;
	ep->mpa_attr.version = mpa->revision;
	अगर (mpa->revision == 1)
		ep->tried_with_mpa_v1 = 1;
	ep->mpa_attr.p2p_type = FW_RI_INIT_P2PTYPE_DISABLED;

	अगर (mpa->revision == 2) अणु
		ep->mpa_attr.enhanced_rdma_conn =
			mpa->flags & MPA_ENHANCED_RDMA_CONN ? 1 : 0;
		अगर (ep->mpa_attr.enhanced_rdma_conn) अणु
			mpa_v2_params = (काष्ठा mpa_v2_conn_params *)
				(ep->mpa_pkt + माप(*mpa));
			ep->ird = ntohs(mpa_v2_params->ird) &
				MPA_V2_IRD_ORD_MASK;
			ep->ird = min_t(u32, ep->ird,
					cur_max_पढ़ो_depth(ep->com.dev));
			ep->ord = ntohs(mpa_v2_params->ord) &
				MPA_V2_IRD_ORD_MASK;
			ep->ord = min_t(u32, ep->ord,
					cur_max_पढ़ो_depth(ep->com.dev));
			pr_debug("initiator ird %u ord %u\n",
				 ep->ird, ep->ord);
			अगर (ntohs(mpa_v2_params->ird) & MPA_V2_PEER2PEER_MODEL)
				अगर (peer2peer) अणु
					अगर (ntohs(mpa_v2_params->ord) &
							MPA_V2_RDMA_WRITE_RTR)
						ep->mpa_attr.p2p_type =
						FW_RI_INIT_P2PTYPE_RDMA_WRITE;
					अन्यथा अगर (ntohs(mpa_v2_params->ord) &
							MPA_V2_RDMA_READ_RTR)
						ep->mpa_attr.p2p_type =
						FW_RI_INIT_P2PTYPE_READ_REQ;
				पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (mpa->revision == 1)
		अगर (peer2peer)
			ep->mpa_attr.p2p_type = p2p_type;

	pr_debug("crc_enabled=%d, recv_marker_enabled=%d, xmit_marker_enabled=%d, version=%d p2p_type=%d\n",
		 ep->mpa_attr.crc_enabled, ep->mpa_attr.recv_marker_enabled,
		 ep->mpa_attr.xmit_marker_enabled, ep->mpa_attr.version,
		 ep->mpa_attr.p2p_type);

	__state_set(&ep->com, MPA_REQ_RCVD);

	/* drive upcall */
	mutex_lock_nested(&ep->parent_ep->com.mutex, SINGLE_DEPTH_NESTING);
	अगर (ep->parent_ep->com.state != DEAD) अणु
		अगर (connect_request_upcall(ep))
			जाओ err_unlock_parent;
	पूर्ण अन्यथा अणु
		जाओ err_unlock_parent;
	पूर्ण
	mutex_unlock(&ep->parent_ep->com.mutex);
	वापस 0;

err_unlock_parent:
	mutex_unlock(&ep->parent_ep->com.mutex);
	जाओ err_out;
err_stop_समयr:
	(व्योम)stop_ep_समयr(ep);
err_out:
	वापस 2;
पूर्ण

अटल पूर्णांक rx_data(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_rx_data *hdr = cplhdr(skb);
	अचिन्हित पूर्णांक dlen = ntohs(hdr->len);
	अचिन्हित पूर्णांक tid = GET_TID(hdr);
	__u8 status = hdr->status;
	पूर्णांक disconnect = 0;

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;
	pr_debug("ep %p tid %u dlen %u\n", ep, ep->hwtid, dlen);
	skb_pull(skb, माप(*hdr));
	skb_trim(skb, dlen);
	mutex_lock(&ep->com.mutex);

	चयन (ep->com.state) अणु
	हाल MPA_REQ_SENT:
		update_rx_credits(ep, dlen);
		ep->rcv_seq += dlen;
		disconnect = process_mpa_reply(ep, skb);
		अवरोध;
	हाल MPA_REQ_WAIT:
		update_rx_credits(ep, dlen);
		ep->rcv_seq += dlen;
		disconnect = process_mpa_request(ep, skb);
		अवरोध;
	हाल FPDU_MODE: अणु
		काष्ठा c4iw_qp_attributes attrs;

		update_rx_credits(ep, dlen);
		अगर (status)
			pr_err("%s Unexpected streaming data." \
			       " qpid %u ep %p state %d tid %u status %d\n",
			       __func__, ep->com.qp->wq.sq.qid, ep,
			       ep->com.state, ep->hwtid, status);
		attrs.next_state = C4IW_QP_STATE_TERMINATE;
		c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
			       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		disconnect = 1;
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&ep->com.mutex);
	अगर (disconnect)
		c4iw_ep_disconnect(ep, disconnect == 2, GFP_KERNEL);
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

अटल व्योम complete_cached_srq_buffers(काष्ठा c4iw_ep *ep, u32 srqidx)
अणु
	क्रमागत chip_type adapter_type;

	adapter_type = ep->com.dev->rdev.lldi.adapter_type;

	/*
	 * If this TCB had a srq buffer cached, then we must complete
	 * it. For user mode, that means saving the srqidx in the
	 * user/kernel status page क्रम this qp.  For kernel mode, just
	 * synthesize the CQE now.
	 */
	अगर (CHELSIO_CHIP_VERSION(adapter_type) > CHELSIO_T5 && srqidx) अणु
		अगर (ep->com.qp->ibqp.uobject)
			t4_set_wq_in_error(&ep->com.qp->wq, srqidx);
		अन्यथा
			c4iw_flush_srqidx(ep->com.qp, srqidx);
	पूर्ण
पूर्ण

अटल पूर्णांक पात_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	u32 srqidx;
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_पात_rpl_rss6 *rpl = cplhdr(skb);
	पूर्णांक release = 0;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep) अणु
		pr_warn("Abort rpl to freed endpoint\n");
		वापस 0;
	पूर्ण

	अगर (ep->com.qp && ep->com.qp->srq) अणु
		srqidx = ABORT_RSS_SRQIDX_G(be32_to_cpu(rpl->srqidx_status));
		complete_cached_srq_buffers(ep, srqidx ? srqidx : ep->srqe_idx);
	पूर्ण

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	mutex_lock(&ep->com.mutex);
	चयन (ep->com.state) अणु
	हाल ABORTING:
		c4iw_wake_up_noref(ep->com.wr_रुकोp, -ECONNRESET);
		__state_set(&ep->com, DEAD);
		release = 1;
		अवरोध;
	शेष:
		pr_err("%s ep %p state %d\n", __func__, ep, ep->com.state);
		अवरोध;
	पूर्ण
	mutex_unlock(&ep->com.mutex);

	अगर (release) अणु
		बंद_complete_upcall(ep, -ECONNRESET);
		release_ep_resources(ep);
	पूर्ण
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

अटल पूर्णांक send_fw_act_खोलो_req(काष्ठा c4iw_ep *ep, अचिन्हित पूर्णांक atid)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fw_ofld_connection_wr *req;
	अचिन्हित पूर्णांक mtu_idx;
	u32 wscale;
	काष्ठा sockaddr_in *sin;
	पूर्णांक win;

	skb = get_skb(शून्य, माप(*req), GFP_KERNEL);
	req = __skb_put_zero(skb, माप(*req));
	req->op_compl = htonl(WR_OP_V(FW_OFLD_CONNECTION_WR));
	req->len16_pkd = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(माप(*req), 16)));
	req->le.filter = cpu_to_be32(cxgb4_select_ntuple(
				     ep->com.dev->rdev.lldi.ports[0],
				     ep->l2t));
	sin = (काष्ठा sockaddr_in *)&ep->com.local_addr;
	req->le.lport = sin->sin_port;
	req->le.u.ipv4.lip = sin->sin_addr.s_addr;
	sin = (काष्ठा sockaddr_in *)&ep->com.remote_addr;
	req->le.pport = sin->sin_port;
	req->le.u.ipv4.pip = sin->sin_addr.s_addr;
	req->tcb.t_state_to_astid =
			htonl(FW_OFLD_CONNECTION_WR_T_STATE_V(TCP_SYN_SENT) |
			FW_OFLD_CONNECTION_WR_ASTID_V(atid));
	req->tcb.cplrxdataack_cplpassacceptrpl =
			htons(FW_OFLD_CONNECTION_WR_CPLRXDATAACK_F);
	req->tcb.tx_max = (__क्रमce __be32) jअगरfies;
	req->tcb.rcv_adv = htons(1);
	cxgb_best_mtu(ep->com.dev->rdev.lldi.mtus, ep->mtu, &mtu_idx,
		      enable_tcp_बारtamps,
		      (ep->com.remote_addr.ss_family == AF_INET) ? 0 : 1);
	wscale = cxgb_compute_wscale(rcv_win);

	/*
	 * Specअगरy the largest winकरोw that will fit in opt0. The
	 * reमुख्यder will be specअगरied in the rx_data_ack.
	 */
	win = ep->rcv_win >> 10;
	अगर (win > RCV_बफ_मान_M)
		win = RCV_बफ_मान_M;

	req->tcb.opt0 = (__क्रमce __be64) (TCAM_BYPASS_F |
		(nocong ? NO_CONG_F : 0) |
		KEEP_ALIVE_F |
		DELACK_F |
		WND_SCALE_V(wscale) |
		MSS_IDX_V(mtu_idx) |
		L2T_IDX_V(ep->l2t->idx) |
		TX_CHAN_V(ep->tx_chan) |
		SMAC_SEL_V(ep->smac_idx) |
		DSCP_V(ep->tos >> 2) |
		ULP_MODE_V(ULP_MODE_TCPDDP) |
		RCV_बफ_मान_V(win));
	req->tcb.opt2 = (__क्रमce __be32) (PACE_V(1) |
		TX_QUEUE_V(ep->com.dev->rdev.lldi.tx_modq[ep->tx_chan]) |
		RX_CHANNEL_V(0) |
		CCTRL_ECN_V(enable_ecn) |
		RSS_QUEUE_VALID_F | RSS_QUEUE_V(ep->rss_qid));
	अगर (enable_tcp_बारtamps)
		req->tcb.opt2 |= (__क्रमce __be32)TSTAMPS_EN_F;
	अगर (enable_tcp_sack)
		req->tcb.opt2 |= (__क्रमce __be32)SACK_EN_F;
	अगर (wscale && enable_tcp_winकरोw_scaling)
		req->tcb.opt2 |= (__क्रमce __be32)WND_SCALE_EN_F;
	req->tcb.opt0 = cpu_to_be64((__क्रमce u64)req->tcb.opt0);
	req->tcb.opt2 = cpu_to_be32((__क्रमce u32)req->tcb.opt2);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, ep->ctrlq_idx);
	set_bit(ACT_OFLD_CONN, &ep->com.history);
	वापस c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
पूर्ण

/*
 * Some of the error codes above implicitly indicate that there is no TID
 * allocated with the result of an ACT_OPEN.  We use this predicate to make
 * that explicit.
 */
अटल अंतरभूत पूर्णांक act_खोलो_has_tid(पूर्णांक status)
अणु
	वापस (status != CPL_ERR_TCAM_PARITY &&
		status != CPL_ERR_TCAM_MISS &&
		status != CPL_ERR_TCAM_FULL &&
		status != CPL_ERR_CONN_EXIST_SYNRECV &&
		status != CPL_ERR_CONN_EXIST);
पूर्ण

अटल अक्षर *neg_adv_str(अचिन्हित पूर्णांक status)
अणु
	चयन (status) अणु
	हाल CPL_ERR_RTX_NEG_ADVICE:
		वापस "Retransmit timeout";
	हाल CPL_ERR_PERSIST_NEG_ADVICE:
		वापस "Persist timeout";
	हाल CPL_ERR_KEEPALV_NEG_ADVICE:
		वापस "Keepalive timeout";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल व्योम set_tcp_winकरोw(काष्ठा c4iw_ep *ep, काष्ठा port_info *pi)
अणु
	ep->snd_win = snd_win;
	ep->rcv_win = rcv_win;
	pr_debug("snd_win %d rcv_win %d\n",
		 ep->snd_win, ep->rcv_win);
पूर्ण

#घोषणा ACT_OPEN_RETRY_COUNT 2

अटल पूर्णांक import_ep(काष्ठा c4iw_ep *ep, पूर्णांक iptype, __u8 *peer_ip,
		     काष्ठा dst_entry *dst, काष्ठा c4iw_dev *cdev,
		     bool clear_mpa_v1, क्रमागत chip_type adapter_type, u8 tos)
अणु
	काष्ठा neighbour *n;
	पूर्णांक err, step;
	काष्ठा net_device *pdev;

	n = dst_neigh_lookup(dst, peer_ip);
	अगर (!n)
		वापस -ENODEV;

	rcu_पढ़ो_lock();
	err = -ENOMEM;
	अगर (n->dev->flags & IFF_LOOPBACK) अणु
		अगर (iptype == 4)
			pdev = ip_dev_find(&init_net, *(__be32 *)peer_ip);
		अन्यथा अगर (IS_ENABLED(CONFIG_IPV6))
			क्रम_each_netdev(&init_net, pdev) अणु
				अगर (ipv6_chk_addr(&init_net,
						  (काष्ठा in6_addr *)peer_ip,
						  pdev, 1))
					अवरोध;
			पूर्ण
		अन्यथा
			pdev = शून्य;

		अगर (!pdev) अणु
			err = -ENODEV;
			जाओ out;
		पूर्ण
		ep->l2t = cxgb4_l2t_get(cdev->rdev.lldi.l2t,
					n, pdev, rt_tos2priority(tos));
		अगर (!ep->l2t) अणु
			dev_put(pdev);
			जाओ out;
		पूर्ण
		ep->mtu = pdev->mtu;
		ep->tx_chan = cxgb4_port_chan(pdev);
		ep->smac_idx = ((काष्ठा port_info *)netdev_priv(pdev))->smt_idx;
		step = cdev->rdev.lldi.ntxq /
			cdev->rdev.lldi.nchan;
		ep->txq_idx = cxgb4_port_idx(pdev) * step;
		step = cdev->rdev.lldi.nrxq /
			cdev->rdev.lldi.nchan;
		ep->ctrlq_idx = cxgb4_port_idx(pdev);
		ep->rss_qid = cdev->rdev.lldi.rxq_ids[
			cxgb4_port_idx(pdev) * step];
		set_tcp_winकरोw(ep, (काष्ठा port_info *)netdev_priv(pdev));
		dev_put(pdev);
	पूर्ण अन्यथा अणु
		pdev = get_real_dev(n->dev);
		ep->l2t = cxgb4_l2t_get(cdev->rdev.lldi.l2t,
					n, pdev, rt_tos2priority(tos));
		अगर (!ep->l2t)
			जाओ out;
		ep->mtu = dst_mtu(dst);
		ep->tx_chan = cxgb4_port_chan(pdev);
		ep->smac_idx = ((काष्ठा port_info *)netdev_priv(pdev))->smt_idx;
		step = cdev->rdev.lldi.ntxq /
			cdev->rdev.lldi.nchan;
		ep->txq_idx = cxgb4_port_idx(pdev) * step;
		ep->ctrlq_idx = cxgb4_port_idx(pdev);
		step = cdev->rdev.lldi.nrxq /
			cdev->rdev.lldi.nchan;
		ep->rss_qid = cdev->rdev.lldi.rxq_ids[
			cxgb4_port_idx(pdev) * step];
		set_tcp_winकरोw(ep, (काष्ठा port_info *)netdev_priv(pdev));

		अगर (clear_mpa_v1) अणु
			ep->retry_with_mpa_v1 = 0;
			ep->tried_with_mpa_v1 = 0;
		पूर्ण
	पूर्ण
	err = 0;
out:
	rcu_पढ़ो_unlock();

	neigh_release(n);

	वापस err;
पूर्ण

अटल पूर्णांक c4iw_reconnect(काष्ठा c4iw_ep *ep)
अणु
	पूर्णांक err = 0;
	पूर्णांक size = 0;
	काष्ठा sockaddr_in *laddr = (काष्ठा sockaddr_in *)
				    &ep->com.cm_id->m_local_addr;
	काष्ठा sockaddr_in *raddr = (काष्ठा sockaddr_in *)
				    &ep->com.cm_id->m_remote_addr;
	काष्ठा sockaddr_in6 *laddr6 = (काष्ठा sockaddr_in6 *)
				      &ep->com.cm_id->m_local_addr;
	काष्ठा sockaddr_in6 *raddr6 = (काष्ठा sockaddr_in6 *)
				      &ep->com.cm_id->m_remote_addr;
	पूर्णांक iptype;
	__u8 *ra;

	pr_debug("qp %p cm_id %p\n", ep->com.qp, ep->com.cm_id);
	c4iw_init_wr_रुको(ep->com.wr_रुकोp);

	/* When MPA revision is dअगरferent on nodes, the node with MPA_rev=2
	 * tries to reconnect with MPA_rev 1 क्रम the same EP through
	 * c4iw_reconnect(), where the same EP is asचिन्हित with new tid क्रम
	 * further connection establishment. As we are using the same EP poपूर्णांकer
	 * क्रम reconnect, few skbs are used during the previous c4iw_connect(),
	 * which leaves the EP with inadequate skbs क्रम further
	 * c4iw_reconnect(), Further causing a crash due to an empty
	 * skb_list() during peer_पात(). Allocate skbs which is alपढ़ोy used.
	 */
	size = (CN_MAX_CON_BUF - skb_queue_len(&ep->com.ep_skb_list));
	अगर (alloc_ep_skb_list(&ep->com.ep_skb_list, size)) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	/*
	 * Allocate an active TID to initiate a TCP connection.
	 */
	ep->atid = cxgb4_alloc_atid(ep->com.dev->rdev.lldi.tids, ep);
	अगर (ep->atid == -1) अणु
		pr_err("%s - cannot alloc atid\n", __func__);
		err = -ENOMEM;
		जाओ fail2;
	पूर्ण
	err = xa_insert_irq(&ep->com.dev->atids, ep->atid, ep, GFP_KERNEL);
	अगर (err)
		जाओ fail2a;

	/* find a route */
	अगर (ep->com.cm_id->m_local_addr.ss_family == AF_INET) अणु
		ep->dst = cxgb_find_route(&ep->com.dev->rdev.lldi, get_real_dev,
					  laddr->sin_addr.s_addr,
					  raddr->sin_addr.s_addr,
					  laddr->sin_port,
					  raddr->sin_port, ep->com.cm_id->tos);
		iptype = 4;
		ra = (__u8 *)&raddr->sin_addr;
	पूर्ण अन्यथा अणु
		ep->dst = cxgb_find_route6(&ep->com.dev->rdev.lldi,
					   get_real_dev,
					   laddr6->sin6_addr.s6_addr,
					   raddr6->sin6_addr.s6_addr,
					   laddr6->sin6_port,
					   raddr6->sin6_port,
					   ep->com.cm_id->tos,
					   raddr6->sin6_scope_id);
		iptype = 6;
		ra = (__u8 *)&raddr6->sin6_addr;
	पूर्ण
	अगर (!ep->dst) अणु
		pr_err("%s - cannot find route\n", __func__);
		err = -EHOSTUNREACH;
		जाओ fail3;
	पूर्ण
	err = import_ep(ep, iptype, ra, ep->dst, ep->com.dev, false,
			ep->com.dev->rdev.lldi.adapter_type,
			ep->com.cm_id->tos);
	अगर (err) अणु
		pr_err("%s - cannot alloc l2e\n", __func__);
		जाओ fail4;
	पूर्ण

	pr_debug("txq_idx %u tx_chan %u smac_idx %u rss_qid %u l2t_idx %u\n",
		 ep->txq_idx, ep->tx_chan, ep->smac_idx, ep->rss_qid,
		 ep->l2t->idx);

	state_set(&ep->com, CONNECTING);
	ep->tos = ep->com.cm_id->tos;

	/* send connect request to rnic */
	err = send_connect(ep);
	अगर (!err)
		जाओ out;

	cxgb4_l2t_release(ep->l2t);
fail4:
	dst_release(ep->dst);
fail3:
	xa_erase_irq(&ep->com.dev->atids, ep->atid);
fail2a:
	cxgb4_मुक्त_atid(ep->com.dev->rdev.lldi.tids, ep->atid);
fail2:
	/*
	 * remember to send notअगरication to upper layer.
	 * We are in here so the upper layer is not aware that this is
	 * re-connect attempt and so, upper layer is still रुकोing क्रम
	 * response of 1st connect request.
	 */
	connect_reply_upcall(ep, -ECONNRESET);
fail1:
	c4iw_put_ep(&ep->com);
out:
	वापस err;
पूर्ण

अटल पूर्णांक act_खोलो_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_act_खोलो_rpl *rpl = cplhdr(skb);
	अचिन्हित पूर्णांक atid = TID_TID_G(AOPEN_ATID_G(
				      ntohl(rpl->atid_status)));
	काष्ठा tid_info *t = dev->rdev.lldi.tids;
	पूर्णांक status = AOPEN_STATUS_G(ntohl(rpl->atid_status));
	काष्ठा sockaddr_in *la;
	काष्ठा sockaddr_in *ra;
	काष्ठा sockaddr_in6 *la6;
	काष्ठा sockaddr_in6 *ra6;
	पूर्णांक ret = 0;

	ep = lookup_atid(t, atid);
	la = (काष्ठा sockaddr_in *)&ep->com.local_addr;
	ra = (काष्ठा sockaddr_in *)&ep->com.remote_addr;
	la6 = (काष्ठा sockaddr_in6 *)&ep->com.local_addr;
	ra6 = (काष्ठा sockaddr_in6 *)&ep->com.remote_addr;

	pr_debug("ep %p atid %u status %u errno %d\n", ep, atid,
		 status, status2त्रुटि_सं(status));

	अगर (cxgb_is_neg_adv(status)) अणु
		pr_debug("Connection problems for atid %u status %u (%s)\n",
			 atid, status, neg_adv_str(status));
		ep->stats.connect_neg_adv++;
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.neg_adv++;
		mutex_unlock(&dev->rdev.stats.lock);
		वापस 0;
	पूर्ण

	set_bit(ACT_OPEN_RPL, &ep->com.history);

	/*
	 * Log पूर्णांकeresting failures.
	 */
	चयन (status) अणु
	हाल CPL_ERR_CONN_RESET:
	हाल CPL_ERR_CONN_TIMEDOUT:
		अवरोध;
	हाल CPL_ERR_TCAM_FULL:
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.tcam_full++;
		mutex_unlock(&dev->rdev.stats.lock);
		अगर (ep->com.local_addr.ss_family == AF_INET &&
		    dev->rdev.lldi.enable_fw_ofld_conn) अणु
			ret = send_fw_act_खोलो_req(ep, TID_TID_G(AOPEN_ATID_G(
						   ntohl(rpl->atid_status))));
			अगर (ret)
				जाओ fail;
			वापस 0;
		पूर्ण
		अवरोध;
	हाल CPL_ERR_CONN_EXIST:
		अगर (ep->retry_count++ < ACT_OPEN_RETRY_COUNT) अणु
			set_bit(ACT_RETRY_INUSE, &ep->com.history);
			अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
				काष्ठा sockaddr_in6 *sin6 =
						(काष्ठा sockaddr_in6 *)
						&ep->com.local_addr;
				cxgb4_clip_release(
						ep->com.dev->rdev.lldi.ports[0],
						(स्थिर u32 *)
						&sin6->sin6_addr.s6_addr, 1);
			पूर्ण
			xa_erase_irq(&ep->com.dev->atids, atid);
			cxgb4_मुक्त_atid(t, atid);
			dst_release(ep->dst);
			cxgb4_l2t_release(ep->l2t);
			c4iw_reconnect(ep);
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अगर (ep->com.local_addr.ss_family == AF_INET) अणु
			pr_info("Active open failure - atid %u status %u errno %d %pI4:%u->%pI4:%u\n",
				atid, status, status2त्रुटि_सं(status),
				&la->sin_addr.s_addr, ntohs(la->sin_port),
				&ra->sin_addr.s_addr, ntohs(ra->sin_port));
		पूर्ण अन्यथा अणु
			pr_info("Active open failure - atid %u status %u errno %d %pI6:%u->%pI6:%u\n",
				atid, status, status2त्रुटि_सं(status),
				la6->sin6_addr.s6_addr, ntohs(la6->sin6_port),
				ra6->sin6_addr.s6_addr, ntohs(ra6->sin6_port));
		पूर्ण
		अवरोध;
	पूर्ण

fail:
	connect_reply_upcall(ep, status2त्रुटि_सं(status));
	state_set(&ep->com, DEAD);

	अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 =
			(काष्ठा sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
	पूर्ण
	अगर (status && act_खोलो_has_tid(status))
		cxgb4_हटाओ_tid(ep->com.dev->rdev.lldi.tids, 0, GET_TID(rpl),
				 ep->com.local_addr.ss_family);

	xa_erase_irq(&ep->com.dev->atids, atid);
	cxgb4_मुक्त_atid(t, atid);
	dst_release(ep->dst);
	cxgb4_l2t_release(ep->l2t);
	c4iw_put_ep(&ep->com);

	वापस 0;
पूर्ण

अटल पूर्णांक pass_खोलो_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_खोलो_rpl *rpl = cplhdr(skb);
	अचिन्हित पूर्णांक stid = GET_TID(rpl);
	काष्ठा c4iw_listen_ep *ep = get_ep_from_stid(dev, stid);

	अगर (!ep) अणु
		pr_warn("%s stid %d lookup failure!\n", __func__, stid);
		जाओ out;
	पूर्ण
	pr_debug("ep %p status %d error %d\n", ep,
		 rpl->status, status2त्रुटि_सं(rpl->status));
	c4iw_wake_up_noref(ep->com.wr_रुकोp, status2त्रुटि_सं(rpl->status));
	c4iw_put_ep(&ep->com);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक बंद_listsrv_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_बंद_listsvr_rpl *rpl = cplhdr(skb);
	अचिन्हित पूर्णांक stid = GET_TID(rpl);
	काष्ठा c4iw_listen_ep *ep = get_ep_from_stid(dev, stid);

	अगर (!ep) अणु
		pr_warn("%s stid %d lookup failure!\n", __func__, stid);
		जाओ out;
	पूर्ण
	pr_debug("ep %p\n", ep);
	c4iw_wake_up_noref(ep->com.wr_रुकोp, status2त्रुटि_सं(rpl->status));
	c4iw_put_ep(&ep->com);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक accept_cr(काष्ठा c4iw_ep *ep, काष्ठा sk_buff *skb,
		     काष्ठा cpl_pass_accept_req *req)
अणु
	काष्ठा cpl_pass_accept_rpl *rpl;
	अचिन्हित पूर्णांक mtu_idx;
	u64 opt0;
	u32 opt2;
	u32 wscale;
	काष्ठा cpl_t5_pass_accept_rpl *rpl5 = शून्य;
	पूर्णांक win;
	क्रमागत chip_type adapter_type = ep->com.dev->rdev.lldi.adapter_type;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	cxgb_best_mtu(ep->com.dev->rdev.lldi.mtus, ep->mtu, &mtu_idx,
		      enable_tcp_बारtamps && req->tcpopt.tstamp,
		      (ep->com.remote_addr.ss_family == AF_INET) ? 0 : 1);
	wscale = cxgb_compute_wscale(rcv_win);

	/*
	 * Specअगरy the largest winकरोw that will fit in opt0. The
	 * reमुख्यder will be specअगरied in the rx_data_ack.
	 */
	win = ep->rcv_win >> 10;
	अगर (win > RCV_बफ_मान_M)
		win = RCV_बफ_मान_M;
	opt0 = (nocong ? NO_CONG_F : 0) |
	       KEEP_ALIVE_F |
	       DELACK_F |
	       WND_SCALE_V(wscale) |
	       MSS_IDX_V(mtu_idx) |
	       L2T_IDX_V(ep->l2t->idx) |
	       TX_CHAN_V(ep->tx_chan) |
	       SMAC_SEL_V(ep->smac_idx) |
	       DSCP_V(ep->tos >> 2) |
	       ULP_MODE_V(ULP_MODE_TCPDDP) |
	       RCV_बफ_मान_V(win);
	opt2 = RX_CHANNEL_V(0) |
	       RSS_QUEUE_VALID_F | RSS_QUEUE_V(ep->rss_qid);

	अगर (enable_tcp_बारtamps && req->tcpopt.tstamp)
		opt2 |= TSTAMPS_EN_F;
	अगर (enable_tcp_sack && req->tcpopt.sack)
		opt2 |= SACK_EN_F;
	अगर (wscale && enable_tcp_winकरोw_scaling)
		opt2 |= WND_SCALE_EN_F;
	अगर (enable_ecn) अणु
		स्थिर काष्ठा tcphdr *tcph;
		u32 hlen = ntohl(req->hdr_len);

		अगर (CHELSIO_CHIP_VERSION(adapter_type) <= CHELSIO_T5)
			tcph = (स्थिर व्योम *)(req + 1) + ETH_HDR_LEN_G(hlen) +
				IP_HDR_LEN_G(hlen);
		अन्यथा
			tcph = (स्थिर व्योम *)(req + 1) +
				T6_ETH_HDR_LEN_G(hlen) + T6_IP_HDR_LEN_G(hlen);
		अगर (tcph->ece && tcph->cwr)
			opt2 |= CCTRL_ECN_V(1);
	पूर्ण

	skb_get(skb);
	rpl = cplhdr(skb);
	अगर (!is_t4(adapter_type)) अणु
		skb_trim(skb, roundup(माप(*rpl5), 16));
		rpl5 = (व्योम *)rpl;
		INIT_TP_WR(rpl5, ep->hwtid);
	पूर्ण अन्यथा अणु
		skb_trim(skb, माप(*rpl));
		INIT_TP_WR(rpl, ep->hwtid);
	पूर्ण
	OPCODE_TID(rpl) = cpu_to_be32(MK_OPCODE_TID(CPL_PASS_ACCEPT_RPL,
						    ep->hwtid));

	अगर (CHELSIO_CHIP_VERSION(adapter_type) > CHELSIO_T4) अणु
		u32 isn = (pअक्रमom_u32() & ~7UL) - 1;
		opt2 |= T5_OPT_2_VALID_F;
		opt2 |= CONG_CNTRL_V(CONG_ALG_TAHOE);
		opt2 |= T5_ISS_F;
		rpl5 = (व्योम *)rpl;
		स_रखो(&rpl5->iss, 0, roundup(माप(*rpl5)-माप(*rpl), 16));
		अगर (peer2peer)
			isn += 4;
		rpl5->iss = cpu_to_be32(isn);
		pr_debug("iss %u\n", be32_to_cpu(rpl5->iss));
	पूर्ण

	rpl->opt0 = cpu_to_be64(opt0);
	rpl->opt2 = cpu_to_be32(opt2);
	set_wr_txq(skb, CPL_PRIORITY_SETUP, ep->ctrlq_idx);
	t4_set_arp_err_handler(skb, ep, pass_accept_rpl_arp_failure);

	वापस c4iw_l2t_send(&ep->com.dev->rdev, skb, ep->l2t);
पूर्ण

अटल व्योम reject_cr(काष्ठा c4iw_dev *dev, u32 hwtid, काष्ठा sk_buff *skb)
अणु
	pr_debug("c4iw_dev %p tid %u\n", dev, hwtid);
	skb_trim(skb, माप(काष्ठा cpl_tid_release));
	release_tid(&dev->rdev, hwtid, skb);
	वापस;
पूर्ण

अटल पूर्णांक pass_accept_req(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *child_ep = शून्य, *parent_ep;
	काष्ठा cpl_pass_accept_req *req = cplhdr(skb);
	अचिन्हित पूर्णांक stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	काष्ठा tid_info *t = dev->rdev.lldi.tids;
	अचिन्हित पूर्णांक hwtid = GET_TID(req);
	काष्ठा dst_entry *dst;
	__u8 local_ip[16], peer_ip[16];
	__be16 local_port, peer_port;
	काष्ठा sockaddr_in6 *sin6;
	पूर्णांक err;
	u16 peer_mss = ntohs(req->tcpopt.mss);
	पूर्णांक iptype;
	अचिन्हित लघु hdrs;
	u8 tos;

	parent_ep = (काष्ठा c4iw_ep *)get_ep_from_stid(dev, stid);
	अगर (!parent_ep) अणु
		pr_err("%s connect request on invalid stid %d\n",
		       __func__, stid);
		जाओ reject;
	पूर्ण

	अगर (state_पढ़ो(&parent_ep->com) != LISTEN) अणु
		pr_err("%s - listening ep not in LISTEN\n", __func__);
		जाओ reject;
	पूर्ण

	अगर (parent_ep->com.cm_id->tos_set)
		tos = parent_ep->com.cm_id->tos;
	अन्यथा
		tos = PASS_OPEN_TOS_G(ntohl(req->tos_stid));

	cxgb_get_4tuple(req, parent_ep->com.dev->rdev.lldi.adapter_type,
			&iptype, local_ip, peer_ip, &local_port, &peer_port);

	/* Find output route */
	अगर (iptype == 4)  अणु
		pr_debug("parent ep %p hwtid %u laddr %pI4 raddr %pI4 lport %d rport %d peer_mss %d\n"
			 , parent_ep, hwtid,
			 local_ip, peer_ip, ntohs(local_port),
			 ntohs(peer_port), peer_mss);
		dst = cxgb_find_route(&dev->rdev.lldi, get_real_dev,
				      *(__be32 *)local_ip, *(__be32 *)peer_ip,
				      local_port, peer_port, tos);
	पूर्ण अन्यथा अणु
		pr_debug("parent ep %p hwtid %u laddr %pI6 raddr %pI6 lport %d rport %d peer_mss %d\n"
			 , parent_ep, hwtid,
			 local_ip, peer_ip, ntohs(local_port),
			 ntohs(peer_port), peer_mss);
		dst = cxgb_find_route6(&dev->rdev.lldi, get_real_dev,
				local_ip, peer_ip, local_port, peer_port,
				tos,
				((काष्ठा sockaddr_in6 *)
				 &parent_ep->com.local_addr)->sin6_scope_id);
	पूर्ण
	अगर (!dst) अणु
		pr_err("%s - failed to find dst entry!\n", __func__);
		जाओ reject;
	पूर्ण

	child_ep = alloc_ep(माप(*child_ep), GFP_KERNEL);
	अगर (!child_ep) अणु
		pr_err("%s - failed to allocate ep entry!\n", __func__);
		dst_release(dst);
		जाओ reject;
	पूर्ण

	err = import_ep(child_ep, iptype, peer_ip, dst, dev, false,
			parent_ep->com.dev->rdev.lldi.adapter_type, tos);
	अगर (err) अणु
		pr_err("%s - failed to allocate l2t entry!\n", __func__);
		dst_release(dst);
		kमुक्त(child_ep);
		जाओ reject;
	पूर्ण

	hdrs = ((iptype == 4) ? माप(काष्ठा iphdr) : माप(काष्ठा ipv6hdr)) +
	       माप(काष्ठा tcphdr) +
	       ((enable_tcp_बारtamps && req->tcpopt.tstamp) ? 12 : 0);
	अगर (peer_mss && child_ep->mtu > (peer_mss + hdrs))
		child_ep->mtu = peer_mss + hdrs;

	skb_queue_head_init(&child_ep->com.ep_skb_list);
	अगर (alloc_ep_skb_list(&child_ep->com.ep_skb_list, CN_MAX_CON_BUF))
		जाओ fail;

	state_set(&child_ep->com, CONNECTING);
	child_ep->com.dev = dev;
	child_ep->com.cm_id = शून्य;

	अगर (iptype == 4) अणु
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)
			&child_ep->com.local_addr;

		sin->sin_family = AF_INET;
		sin->sin_port = local_port;
		sin->sin_addr.s_addr = *(__be32 *)local_ip;

		sin = (काष्ठा sockaddr_in *)&child_ep->com.local_addr;
		sin->sin_family = AF_INET;
		sin->sin_port = ((काष्ठा sockaddr_in *)
				 &parent_ep->com.local_addr)->sin_port;
		sin->sin_addr.s_addr = *(__be32 *)local_ip;

		sin = (काष्ठा sockaddr_in *)&child_ep->com.remote_addr;
		sin->sin_family = AF_INET;
		sin->sin_port = peer_port;
		sin->sin_addr.s_addr = *(__be32 *)peer_ip;
	पूर्ण अन्यथा अणु
		sin6 = (काष्ठा sockaddr_in6 *)&child_ep->com.local_addr;
		sin6->sin6_family = PF_INET6;
		sin6->sin6_port = local_port;
		स_नकल(sin6->sin6_addr.s6_addr, local_ip, 16);

		sin6 = (काष्ठा sockaddr_in6 *)&child_ep->com.local_addr;
		sin6->sin6_family = PF_INET6;
		sin6->sin6_port = ((काष्ठा sockaddr_in6 *)
				   &parent_ep->com.local_addr)->sin6_port;
		स_नकल(sin6->sin6_addr.s6_addr, local_ip, 16);

		sin6 = (काष्ठा sockaddr_in6 *)&child_ep->com.remote_addr;
		sin6->sin6_family = PF_INET6;
		sin6->sin6_port = peer_port;
		स_नकल(sin6->sin6_addr.s6_addr, peer_ip, 16);
	पूर्ण

	c4iw_get_ep(&parent_ep->com);
	child_ep->parent_ep = parent_ep;
	child_ep->tos = tos;
	child_ep->dst = dst;
	child_ep->hwtid = hwtid;

	pr_debug("tx_chan %u smac_idx %u rss_qid %u\n",
		 child_ep->tx_chan, child_ep->smac_idx, child_ep->rss_qid);

	समयr_setup(&child_ep->समयr, ep_समयout, 0);
	cxgb4_insert_tid(t, child_ep, hwtid,
			 child_ep->com.local_addr.ss_family);
	insert_ep_tid(child_ep);
	अगर (accept_cr(child_ep, skb, req)) अणु
		c4iw_put_ep(&parent_ep->com);
		release_ep_resources(child_ep);
	पूर्ण अन्यथा अणु
		set_bit(PASS_ACCEPT_REQ, &child_ep->com.history);
	पूर्ण
	अगर (iptype == 6) अणु
		sin6 = (काष्ठा sockaddr_in6 *)&child_ep->com.local_addr;
		cxgb4_clip_get(child_ep->com.dev->rdev.lldi.ports[0],
			       (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
	पूर्ण
	जाओ out;
fail:
	c4iw_put_ep(&child_ep->com);
reject:
	reject_cr(dev, hwtid, skb);
out:
	अगर (parent_ep)
		c4iw_put_ep(&parent_ep->com);
	वापस 0;
पूर्ण

अटल पूर्णांक pass_establish(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_pass_establish *req = cplhdr(skb);
	अचिन्हित पूर्णांक tid = GET_TID(req);
	पूर्णांक ret;
	u16 tcp_opt = ntohs(req->tcp_opt);

	ep = get_ep_from_tid(dev, tid);
	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	ep->snd_seq = be32_to_cpu(req->snd_isn);
	ep->rcv_seq = be32_to_cpu(req->rcv_isn);
	ep->snd_wscale = TCPOPT_SND_WSCALE_G(tcp_opt);

	pr_debug("ep %p hwtid %u tcp_opt 0x%02x\n", ep, tid, tcp_opt);

	set_emss(ep, tcp_opt);

	dst_confirm(ep->dst);
	mutex_lock(&ep->com.mutex);
	ep->com.state = MPA_REQ_WAIT;
	start_ep_समयr(ep);
	set_bit(PASS_ESTAB, &ep->com.history);
	ret = send_flowc(ep);
	mutex_unlock(&ep->com.mutex);
	अगर (ret)
		c4iw_ep_disconnect(ep, 1, GFP_KERNEL);
	c4iw_put_ep(&ep->com);

	वापस 0;
पूर्ण

अटल पूर्णांक peer_बंद(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_peer_बंद *hdr = cplhdr(skb);
	काष्ठा c4iw_ep *ep;
	काष्ठा c4iw_qp_attributes attrs;
	पूर्णांक disconnect = 1;
	पूर्णांक release = 0;
	अचिन्हित पूर्णांक tid = GET_TID(hdr);
	पूर्णांक ret;

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);
	dst_confirm(ep->dst);

	set_bit(PEER_CLOSE, &ep->com.history);
	mutex_lock(&ep->com.mutex);
	चयन (ep->com.state) अणु
	हाल MPA_REQ_WAIT:
		__state_set(&ep->com, CLOSING);
		अवरोध;
	हाल MPA_REQ_SENT:
		__state_set(&ep->com, CLOSING);
		connect_reply_upcall(ep, -ECONNRESET);
		अवरोध;
	हाल MPA_REQ_RCVD:

		/*
		 * We're gonna mark this puppy DEAD, but keep
		 * the reference on it until the ULP accepts or
		 * rejects the CR. Also wake up anyone रुकोing
		 * in rdma connection migration (see c4iw_accept_cr()).
		 */
		__state_set(&ep->com, CLOSING);
		pr_debug("waking up ep %p tid %u\n", ep, ep->hwtid);
		c4iw_wake_up_noref(ep->com.wr_रुकोp, -ECONNRESET);
		अवरोध;
	हाल MPA_REP_SENT:
		__state_set(&ep->com, CLOSING);
		pr_debug("waking up ep %p tid %u\n", ep, ep->hwtid);
		c4iw_wake_up_noref(ep->com.wr_रुकोp, -ECONNRESET);
		अवरोध;
	हाल FPDU_MODE:
		start_ep_समयr(ep);
		__state_set(&ep->com, CLOSING);
		attrs.next_state = C4IW_QP_STATE_CLOSING;
		ret = c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		अगर (ret != -ECONNRESET) अणु
			peer_बंद_upcall(ep);
			disconnect = 1;
		पूर्ण
		अवरोध;
	हाल ABORTING:
		disconnect = 0;
		अवरोध;
	हाल CLOSING:
		__state_set(&ep->com, MORIBUND);
		disconnect = 0;
		अवरोध;
	हाल MORIBUND:
		(व्योम)stop_ep_समयr(ep);
		अगर (ep->com.cm_id && ep->com.qp) अणु
			attrs.next_state = C4IW_QP_STATE_IDLE;
			c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		पूर्ण
		बंद_complete_upcall(ep, 0);
		__state_set(&ep->com, DEAD);
		release = 1;
		disconnect = 0;
		अवरोध;
	हाल DEAD:
		disconnect = 0;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
	पूर्ण
	mutex_unlock(&ep->com.mutex);
	अगर (disconnect)
		c4iw_ep_disconnect(ep, 0, GFP_KERNEL);
	अगर (release)
		release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

अटल व्योम finish_peer_पात(काष्ठा c4iw_dev *dev, काष्ठा c4iw_ep *ep)
अणु
	complete_cached_srq_buffers(ep, ep->srqe_idx);
	अगर (ep->com.cm_id && ep->com.qp) अणु
		काष्ठा c4iw_qp_attributes attrs;

		attrs.next_state = C4IW_QP_STATE_ERROR;
		c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
			       C4IW_QP_ATTR_NEXT_STATE,	&attrs, 1);
	पूर्ण
	peer_पात_upcall(ep);
	release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
पूर्ण

अटल पूर्णांक peer_पात(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req_rss6 *req = cplhdr(skb);
	काष्ठा c4iw_ep *ep;
	काष्ठा sk_buff *rpl_skb;
	काष्ठा c4iw_qp_attributes attrs;
	पूर्णांक ret;
	पूर्णांक release = 0;
	अचिन्हित पूर्णांक tid = GET_TID(req);
	u8 status;
	u32 srqidx;

	u32 len = roundup(माप(काष्ठा cpl_पात_rpl), 16);

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;

	status = ABORT_RSS_STATUS_G(be32_to_cpu(req->srqidx_status));

	अगर (cxgb_is_neg_adv(status)) अणु
		pr_debug("Negative advice on abort- tid %u status %d (%s)\n",
			 ep->hwtid, status, neg_adv_str(status));
		ep->stats.पात_neg_adv++;
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.neg_adv++;
		mutex_unlock(&dev->rdev.stats.lock);
		जाओ deref_ep;
	पूर्ण

	pr_debug("ep %p tid %u state %u\n", ep, ep->hwtid,
		 ep->com.state);
	set_bit(PEER_ABORT, &ep->com.history);

	/*
	 * Wake up any thपढ़ोs in rdma_init() or rdma_fini().
	 * However, this is not needed अगर com state is just
	 * MPA_REQ_SENT
	 */
	अगर (ep->com.state != MPA_REQ_SENT)
		c4iw_wake_up_noref(ep->com.wr_रुकोp, -ECONNRESET);

	mutex_lock(&ep->com.mutex);
	चयन (ep->com.state) अणु
	हाल CONNECTING:
		c4iw_put_ep(&ep->parent_ep->com);
		अवरोध;
	हाल MPA_REQ_WAIT:
		(व्योम)stop_ep_समयr(ep);
		अवरोध;
	हाल MPA_REQ_SENT:
		(व्योम)stop_ep_समयr(ep);
		अगर (status != CPL_ERR_CONN_RESET || mpa_rev == 1 ||
		    (mpa_rev == 2 && ep->tried_with_mpa_v1))
			connect_reply_upcall(ep, -ECONNRESET);
		अन्यथा अणु
			/*
			 * we just करोn't send notअगरication upwards because we
			 * want to retry with mpa_v1 without upper layers even
			 * knowing it.
			 *
			 * करो some housekeeping so as to re-initiate the
			 * connection
			 */
			pr_info("%s: mpa_rev=%d. Retrying with mpav1\n",
				__func__, mpa_rev);
			ep->retry_with_mpa_v1 = 1;
		पूर्ण
		अवरोध;
	हाल MPA_REP_SENT:
		अवरोध;
	हाल MPA_REQ_RCVD:
		अवरोध;
	हाल MORIBUND:
	हाल CLOSING:
		stop_ep_समयr(ep);
		fallthrough;
	हाल FPDU_MODE:
		अगर (ep->com.qp && ep->com.qp->srq) अणु
			srqidx = ABORT_RSS_SRQIDX_G(
					be32_to_cpu(req->srqidx_status));
			अगर (srqidx) अणु
				complete_cached_srq_buffers(ep, srqidx);
			पूर्ण अन्यथा अणु
				/* Hold ep ref until finish_peer_पात() */
				c4iw_get_ep(&ep->com);
				__state_set(&ep->com, ABORTING);
				set_bit(PEER_ABORT_IN_PROGRESS, &ep->com.flags);
				पढ़ो_tcb(ep);
				अवरोध;

			पूर्ण
		पूर्ण

		अगर (ep->com.cm_id && ep->com.qp) अणु
			attrs.next_state = C4IW_QP_STATE_ERROR;
			ret = c4iw_modअगरy_qp(ep->com.qp->rhp,
				     ep->com.qp, C4IW_QP_ATTR_NEXT_STATE,
				     &attrs, 1);
			अगर (ret)
				pr_err("%s - qp <- error failed!\n", __func__);
		पूर्ण
		peer_पात_upcall(ep);
		अवरोध;
	हाल ABORTING:
		अवरोध;
	हाल DEAD:
		pr_warn("%s PEER_ABORT IN DEAD STATE!!!!\n", __func__);
		mutex_unlock(&ep->com.mutex);
		जाओ deref_ep;
	शेष:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
		अवरोध;
	पूर्ण
	dst_confirm(ep->dst);
	अगर (ep->com.state != ABORTING) अणु
		__state_set(&ep->com, DEAD);
		/* we करोn't release अगर we want to retry with mpa_v1 */
		अगर (!ep->retry_with_mpa_v1)
			release = 1;
	पूर्ण
	mutex_unlock(&ep->com.mutex);

	rpl_skb = skb_dequeue(&ep->com.ep_skb_list);
	अगर (WARN_ON(!rpl_skb)) अणु
		release = 1;
		जाओ out;
	पूर्ण

	cxgb_mk_पात_rpl(rpl_skb, len, ep->hwtid, ep->txq_idx);

	c4iw_ofld_send(&ep->com.dev->rdev, rpl_skb);
out:
	अगर (release)
		release_ep_resources(ep);
	अन्यथा अगर (ep->retry_with_mpa_v1) अणु
		अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
			काष्ठा sockaddr_in6 *sin6 =
					(काष्ठा sockaddr_in6 *)
					&ep->com.local_addr;
			cxgb4_clip_release(
					ep->com.dev->rdev.lldi.ports[0],
					(स्थिर u32 *)&sin6->sin6_addr.s6_addr,
					1);
		पूर्ण
		xa_erase_irq(&ep->com.dev->hwtids, ep->hwtid);
		cxgb4_हटाओ_tid(ep->com.dev->rdev.lldi.tids, 0, ep->hwtid,
				 ep->com.local_addr.ss_family);
		dst_release(ep->dst);
		cxgb4_l2t_release(ep->l2t);
		c4iw_reconnect(ep);
	पूर्ण

deref_ep:
	c4iw_put_ep(&ep->com);
	/* Dereferencing ep, referenced in peer_पात_पूर्णांकr() */
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

अटल पूर्णांक बंद_con_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा c4iw_qp_attributes attrs;
	काष्ठा cpl_बंद_con_rpl *rpl = cplhdr(skb);
	पूर्णांक release = 0;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	/* The cm_id may be null अगर we failed to connect */
	mutex_lock(&ep->com.mutex);
	set_bit(CLOSE_CON_RPL, &ep->com.history);
	चयन (ep->com.state) अणु
	हाल CLOSING:
		__state_set(&ep->com, MORIBUND);
		अवरोध;
	हाल MORIBUND:
		(व्योम)stop_ep_समयr(ep);
		अगर ((ep->com.cm_id) && (ep->com.qp)) अणु
			attrs.next_state = C4IW_QP_STATE_IDLE;
			c4iw_modअगरy_qp(ep->com.qp->rhp,
					     ep->com.qp,
					     C4IW_QP_ATTR_NEXT_STATE,
					     &attrs, 1);
		पूर्ण
		बंद_complete_upcall(ep, 0);
		__state_set(&ep->com, DEAD);
		release = 1;
		अवरोध;
	हाल ABORTING:
	हाल DEAD:
		अवरोध;
	शेष:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
		अवरोध;
	पूर्ण
	mutex_unlock(&ep->com.mutex);
	अगर (release)
		release_ep_resources(ep);
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

अटल पूर्णांक terminate(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_rdma_terminate *rpl = cplhdr(skb);
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा c4iw_ep *ep;
	काष्ठा c4iw_qp_attributes attrs;

	ep = get_ep_from_tid(dev, tid);

	अगर (ep) अणु
		अगर (ep->com.qp) अणु
			pr_warn("TERM received tid %u qpid %u\n", tid,
				ep->com.qp->wq.sq.qid);
			attrs.next_state = C4IW_QP_STATE_TERMINATE;
			c4iw_modअगरy_qp(ep->com.qp->rhp, ep->com.qp,
				       C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
		पूर्ण

		/* As per draft-hilland-iwarp-verbs-v1.0, sec 6.2.3,
		 * when entering the TERM state the RNIC MUST initiate a CLOSE.
		 */
		c4iw_ep_disconnect(ep, 1, GFP_KERNEL);
		c4iw_put_ep(&ep->com);
	पूर्ण अन्यथा
		pr_warn("TERM received tid %u no ep/qp\n", tid);

	वापस 0;
पूर्ण

/*
 * Upcall from the adapter indicating data has been transmitted.
 * For us its just the single MPA request or reply.  We can now मुक्त
 * the skb holding the mpa message.
 */
अटल पूर्णांक fw4_ack(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा c4iw_ep *ep;
	काष्ठा cpl_fw4_ack *hdr = cplhdr(skb);
	u8 credits = hdr->credits;
	अचिन्हित पूर्णांक tid = GET_TID(hdr);


	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;
	pr_debug("ep %p tid %u credits %u\n",
		 ep, ep->hwtid, credits);
	अगर (credits == 0) अणु
		pr_debug("0 credit ack ep %p tid %u state %u\n",
			 ep, ep->hwtid, state_पढ़ो(&ep->com));
		जाओ out;
	पूर्ण

	dst_confirm(ep->dst);
	अगर (ep->mpa_skb) अणु
		pr_debug("last streaming msg ack ep %p tid %u state %u initiator %u freeing skb\n",
			 ep, ep->hwtid, state_पढ़ो(&ep->com),
			 ep->mpa_attr.initiator ? 1 : 0);
		mutex_lock(&ep->com.mutex);
		kमुक्त_skb(ep->mpa_skb);
		ep->mpa_skb = शून्य;
		अगर (test_bit(STOP_MPA_TIMER, &ep->com.flags))
			stop_ep_समयr(ep);
		mutex_unlock(&ep->com.mutex);
	पूर्ण
out:
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

पूर्णांक c4iw_reject_cr(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata, u8 pdata_len)
अणु
	पूर्णांक पात;
	काष्ठा c4iw_ep *ep = to_ep(cm_id);

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	mutex_lock(&ep->com.mutex);
	अगर (ep->com.state != MPA_REQ_RCVD) अणु
		mutex_unlock(&ep->com.mutex);
		c4iw_put_ep(&ep->com);
		वापस -ECONNRESET;
	पूर्ण
	set_bit(ULP_REJECT, &ep->com.history);
	अगर (mpa_rev == 0)
		पात = 1;
	अन्यथा
		पात = send_mpa_reject(ep, pdata, pdata_len);
	mutex_unlock(&ep->com.mutex);

	stop_ep_समयr(ep);
	c4iw_ep_disconnect(ep, पात != 0, GFP_KERNEL);
	c4iw_put_ep(&ep->com);
	वापस 0;
पूर्ण

पूर्णांक c4iw_accept_cr(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	पूर्णांक err;
	काष्ठा c4iw_qp_attributes attrs;
	क्रमागत c4iw_qp_attr_mask mask;
	काष्ठा c4iw_ep *ep = to_ep(cm_id);
	काष्ठा c4iw_dev *h = to_c4iw_dev(cm_id->device);
	काष्ठा c4iw_qp *qp = get_qhp(h, conn_param->qpn);
	पूर्णांक पात = 0;

	pr_debug("ep %p tid %u\n", ep, ep->hwtid);

	mutex_lock(&ep->com.mutex);
	अगर (ep->com.state != MPA_REQ_RCVD) अणु
		err = -ECONNRESET;
		जाओ err_out;
	पूर्ण

	अगर (!qp) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	set_bit(ULP_ACCEPT, &ep->com.history);
	अगर ((conn_param->ord > cur_max_पढ़ो_depth(ep->com.dev)) ||
	    (conn_param->ird > cur_max_पढ़ो_depth(ep->com.dev))) अणु
		err = -EINVAL;
		जाओ err_पात;
	पूर्ण

	अगर (ep->mpa_attr.version == 2 && ep->mpa_attr.enhanced_rdma_conn) अणु
		अगर (conn_param->ord > ep->ird) अणु
			अगर (RELAXED_IRD_NEGOTIATION) अणु
				conn_param->ord = ep->ird;
			पूर्ण अन्यथा अणु
				ep->ird = conn_param->ird;
				ep->ord = conn_param->ord;
				send_mpa_reject(ep, conn_param->निजी_data,
						conn_param->निजी_data_len);
				err = -ENOMEM;
				जाओ err_पात;
			पूर्ण
		पूर्ण
		अगर (conn_param->ird < ep->ord) अणु
			अगर (RELAXED_IRD_NEGOTIATION &&
			    ep->ord <= h->rdev.lldi.max_ordird_qp) अणु
				conn_param->ird = ep->ord;
			पूर्ण अन्यथा अणु
				err = -ENOMEM;
				जाओ err_पात;
			पूर्ण
		पूर्ण
	पूर्ण
	ep->ird = conn_param->ird;
	ep->ord = conn_param->ord;

	अगर (ep->mpa_attr.version == 1) अणु
		अगर (peer2peer && ep->ird == 0)
			ep->ird = 1;
	पूर्ण अन्यथा अणु
		अगर (peer2peer &&
		    (ep->mpa_attr.p2p_type != FW_RI_INIT_P2PTYPE_DISABLED) &&
		    (p2p_type == FW_RI_INIT_P2PTYPE_READ_REQ) && ep->ird == 0)
			ep->ird = 1;
	पूर्ण

	pr_debug("ird %d ord %d\n", ep->ird, ep->ord);

	ep->com.cm_id = cm_id;
	ref_cm_id(&ep->com);
	ep->com.qp = qp;
	ref_qp(ep);

	/* bind QP to EP and move to RTS */
	attrs.mpa_attr = ep->mpa_attr;
	attrs.max_ird = ep->ird;
	attrs.max_ord = ep->ord;
	attrs.llp_stream_handle = ep;
	attrs.next_state = C4IW_QP_STATE_RTS;

	/* bind QP and TID with INIT_WR */
	mask = C4IW_QP_ATTR_NEXT_STATE |
			     C4IW_QP_ATTR_LLP_STREAM_HANDLE |
			     C4IW_QP_ATTR_MPA_ATTR |
			     C4IW_QP_ATTR_MAX_IRD |
			     C4IW_QP_ATTR_MAX_ORD;

	err = c4iw_modअगरy_qp(ep->com.qp->rhp,
			     ep->com.qp, mask, &attrs, 1);
	अगर (err)
		जाओ err_deref_cm_id;

	set_bit(STOP_MPA_TIMER, &ep->com.flags);
	err = send_mpa_reply(ep, conn_param->निजी_data,
			     conn_param->निजी_data_len);
	अगर (err)
		जाओ err_deref_cm_id;

	__state_set(&ep->com, FPDU_MODE);
	established_upcall(ep);
	mutex_unlock(&ep->com.mutex);
	c4iw_put_ep(&ep->com);
	वापस 0;
err_deref_cm_id:
	deref_cm_id(&ep->com);
err_पात:
	पात = 1;
err_out:
	mutex_unlock(&ep->com.mutex);
	अगर (पात)
		c4iw_ep_disconnect(ep, 1, GFP_KERNEL);
	c4iw_put_ep(&ep->com);
	वापस err;
पूर्ण

अटल पूर्णांक pick_local_ipaddrs(काष्ठा c4iw_dev *dev, काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा in_device *ind;
	पूर्णांक found = 0;
	काष्ठा sockaddr_in *laddr = (काष्ठा sockaddr_in *)&cm_id->m_local_addr;
	काष्ठा sockaddr_in *raddr = (काष्ठा sockaddr_in *)&cm_id->m_remote_addr;
	स्थिर काष्ठा in_अगरaddr *अगरa;

	ind = in_dev_get(dev->rdev.lldi.ports[0]);
	अगर (!ind)
		वापस -EADDRNOTAVAIL;
	rcu_पढ़ो_lock();
	in_dev_क्रम_each_अगरa_rcu(अगरa, ind) अणु
		अगर (अगरa->अगरa_flags & IFA_F_SECONDARY)
			जारी;
		laddr->sin_addr.s_addr = अगरa->अगरa_address;
		raddr->sin_addr.s_addr = अगरa->अगरa_address;
		found = 1;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	in_dev_put(ind);
	वापस found ? 0 : -EADDRNOTAVAIL;
पूर्ण

अटल पूर्णांक get_lladdr(काष्ठा net_device *dev, काष्ठा in6_addr *addr,
		      अचिन्हित अक्षर banned_flags)
अणु
	काष्ठा inet6_dev *idev;
	पूर्णांक err = -EADDRNOTAVAIL;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dev);
	अगर (idev != शून्य) अणु
		काष्ठा inet6_अगरaddr *अगरp;

		पढ़ो_lock_bh(&idev->lock);
		list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
			अगर (अगरp->scope == IFA_LINK &&
			    !(अगरp->flags & banned_flags)) अणु
				स_नकल(addr, &अगरp->addr, 16);
				err = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock_bh(&idev->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक pick_local_ip6addrs(काष्ठा c4iw_dev *dev, काष्ठा iw_cm_id *cm_id)
अणु
	काष्ठा in6_addr addr;
	काष्ठा sockaddr_in6 *la6 = (काष्ठा sockaddr_in6 *)&cm_id->m_local_addr;
	काष्ठा sockaddr_in6 *ra6 = (काष्ठा sockaddr_in6 *)&cm_id->m_remote_addr;

	अगर (!get_lladdr(dev->rdev.lldi.ports[0], &addr, IFA_F_TENTATIVE)) अणु
		स_नकल(la6->sin6_addr.s6_addr, &addr, 16);
		स_नकल(ra6->sin6_addr.s6_addr, &addr, 16);
		वापस 0;
	पूर्ण
	वापस -EADDRNOTAVAIL;
पूर्ण

पूर्णांक c4iw_connect(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param)
अणु
	काष्ठा c4iw_dev *dev = to_c4iw_dev(cm_id->device);
	काष्ठा c4iw_ep *ep;
	पूर्णांक err = 0;
	काष्ठा sockaddr_in *laddr;
	काष्ठा sockaddr_in *raddr;
	काष्ठा sockaddr_in6 *laddr6;
	काष्ठा sockaddr_in6 *raddr6;
	__u8 *ra;
	पूर्णांक iptype;

	अगर ((conn_param->ord > cur_max_पढ़ो_depth(dev)) ||
	    (conn_param->ird > cur_max_पढ़ो_depth(dev))) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण
	ep = alloc_ep(माप(*ep), GFP_KERNEL);
	अगर (!ep) अणु
		pr_err("%s - cannot alloc ep\n", __func__);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	skb_queue_head_init(&ep->com.ep_skb_list);
	अगर (alloc_ep_skb_list(&ep->com.ep_skb_list, CN_MAX_CON_BUF)) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	समयr_setup(&ep->समयr, ep_समयout, 0);
	ep->plen = conn_param->निजी_data_len;
	अगर (ep->plen)
		स_नकल(ep->mpa_pkt + माप(काष्ठा mpa_message),
		       conn_param->निजी_data, ep->plen);
	ep->ird = conn_param->ird;
	ep->ord = conn_param->ord;

	अगर (peer2peer && ep->ord == 0)
		ep->ord = 1;

	ep->com.cm_id = cm_id;
	ref_cm_id(&ep->com);
	cm_id->provider_data = ep;
	ep->com.dev = dev;
	ep->com.qp = get_qhp(dev, conn_param->qpn);
	अगर (!ep->com.qp) अणु
		pr_warn("%s qpn 0x%x not found!\n", __func__, conn_param->qpn);
		err = -EINVAL;
		जाओ fail2;
	पूर्ण
	ref_qp(ep);
	pr_debug("qpn 0x%x qp %p cm_id %p\n", conn_param->qpn,
		 ep->com.qp, cm_id);

	/*
	 * Allocate an active TID to initiate a TCP connection.
	 */
	ep->atid = cxgb4_alloc_atid(dev->rdev.lldi.tids, ep);
	अगर (ep->atid == -1) अणु
		pr_err("%s - cannot alloc atid\n", __func__);
		err = -ENOMEM;
		जाओ fail2;
	पूर्ण
	err = xa_insert_irq(&dev->atids, ep->atid, ep, GFP_KERNEL);
	अगर (err)
		जाओ fail5;

	स_नकल(&ep->com.local_addr, &cm_id->m_local_addr,
	       माप(ep->com.local_addr));
	स_नकल(&ep->com.remote_addr, &cm_id->m_remote_addr,
	       माप(ep->com.remote_addr));

	laddr = (काष्ठा sockaddr_in *)&ep->com.local_addr;
	raddr = (काष्ठा sockaddr_in *)&ep->com.remote_addr;
	laddr6 = (काष्ठा sockaddr_in6 *)&ep->com.local_addr;
	raddr6 = (काष्ठा sockaddr_in6 *) &ep->com.remote_addr;

	अगर (cm_id->m_remote_addr.ss_family == AF_INET) अणु
		iptype = 4;
		ra = (__u8 *)&raddr->sin_addr;

		/*
		 * Handle loopback requests to INADDR_ANY.
		 */
		अगर (raddr->sin_addr.s_addr == htonl(INADDR_ANY)) अणु
			err = pick_local_ipaddrs(dev, cm_id);
			अगर (err)
				जाओ fail3;
		पूर्ण

		/* find a route */
		pr_debug("saddr %pI4 sport 0x%x raddr %pI4 rport 0x%x\n",
			 &laddr->sin_addr, ntohs(laddr->sin_port),
			 ra, ntohs(raddr->sin_port));
		ep->dst = cxgb_find_route(&dev->rdev.lldi, get_real_dev,
					  laddr->sin_addr.s_addr,
					  raddr->sin_addr.s_addr,
					  laddr->sin_port,
					  raddr->sin_port, cm_id->tos);
	पूर्ण अन्यथा अणु
		iptype = 6;
		ra = (__u8 *)&raddr6->sin6_addr;

		/*
		 * Handle loopback requests to INADDR_ANY.
		 */
		अगर (ipv6_addr_type(&raddr6->sin6_addr) == IPV6_ADDR_ANY) अणु
			err = pick_local_ip6addrs(dev, cm_id);
			अगर (err)
				जाओ fail3;
		पूर्ण

		/* find a route */
		pr_debug("saddr %pI6 sport 0x%x raddr %pI6 rport 0x%x\n",
			 laddr6->sin6_addr.s6_addr,
			 ntohs(laddr6->sin6_port),
			 raddr6->sin6_addr.s6_addr, ntohs(raddr6->sin6_port));
		ep->dst = cxgb_find_route6(&dev->rdev.lldi, get_real_dev,
					   laddr6->sin6_addr.s6_addr,
					   raddr6->sin6_addr.s6_addr,
					   laddr6->sin6_port,
					   raddr6->sin6_port, cm_id->tos,
					   raddr6->sin6_scope_id);
	पूर्ण
	अगर (!ep->dst) अणु
		pr_err("%s - cannot find route\n", __func__);
		err = -EHOSTUNREACH;
		जाओ fail3;
	पूर्ण

	err = import_ep(ep, iptype, ra, ep->dst, ep->com.dev, true,
			ep->com.dev->rdev.lldi.adapter_type, cm_id->tos);
	अगर (err) अणु
		pr_err("%s - cannot alloc l2e\n", __func__);
		जाओ fail4;
	पूर्ण

	pr_debug("txq_idx %u tx_chan %u smac_idx %u rss_qid %u l2t_idx %u\n",
		 ep->txq_idx, ep->tx_chan, ep->smac_idx, ep->rss_qid,
		 ep->l2t->idx);

	state_set(&ep->com, CONNECTING);
	ep->tos = cm_id->tos;

	/* send connect request to rnic */
	err = send_connect(ep);
	अगर (!err)
		जाओ out;

	cxgb4_l2t_release(ep->l2t);
fail4:
	dst_release(ep->dst);
fail3:
	xa_erase_irq(&ep->com.dev->atids, ep->atid);
fail5:
	cxgb4_मुक्त_atid(ep->com.dev->rdev.lldi.tids, ep->atid);
fail2:
	skb_queue_purge(&ep->com.ep_skb_list);
	deref_cm_id(&ep->com);
fail1:
	c4iw_put_ep(&ep->com);
out:
	वापस err;
पूर्ण

अटल पूर्णांक create_server6(काष्ठा c4iw_dev *dev, काष्ठा c4iw_listen_ep *ep)
अणु
	पूर्णांक err;
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)
				    &ep->com.local_addr;

	अगर (ipv6_addr_type(&sin6->sin6_addr) != IPV6_ADDR_ANY) अणु
		err = cxgb4_clip_get(ep->com.dev->rdev.lldi.ports[0],
				     (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
		अगर (err)
			वापस err;
	पूर्ण
	c4iw_init_wr_रुको(ep->com.wr_रुकोp);
	err = cxgb4_create_server6(ep->com.dev->rdev.lldi.ports[0],
				   ep->stid, &sin6->sin6_addr,
				   sin6->sin6_port,
				   ep->com.dev->rdev.lldi.rxq_ids[0]);
	अगर (!err)
		err = c4iw_रुको_क्रम_reply(&ep->com.dev->rdev,
					  ep->com.wr_रुकोp,
					  0, 0, __func__);
	अन्यथा अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);
	अगर (err) अणु
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
		pr_err("cxgb4_create_server6/filter failed err %d stid %d laddr %pI6 lport %d\n",
		       err, ep->stid,
		       sin6->sin6_addr.s6_addr, ntohs(sin6->sin6_port));
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक create_server4(काष्ठा c4iw_dev *dev, काष्ठा c4iw_listen_ep *ep)
अणु
	पूर्णांक err;
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)
				  &ep->com.local_addr;

	अगर (dev->rdev.lldi.enable_fw_ofld_conn) अणु
		करो अणु
			err = cxgb4_create_server_filter(
				ep->com.dev->rdev.lldi.ports[0], ep->stid,
				sin->sin_addr.s_addr, sin->sin_port, 0,
				ep->com.dev->rdev.lldi.rxq_ids[0], 0, 0);
			अगर (err == -EBUSY) अणु
				अगर (c4iw_fatal_error(&ep->com.dev->rdev)) अणु
					err = -EIO;
					अवरोध;
				पूर्ण
				set_current_state(TASK_UNINTERRUPTIBLE);
				schedule_समयout(usecs_to_jअगरfies(100));
			पूर्ण
		पूर्ण जबतक (err == -EBUSY);
	पूर्ण अन्यथा अणु
		c4iw_init_wr_रुको(ep->com.wr_रुकोp);
		err = cxgb4_create_server(ep->com.dev->rdev.lldi.ports[0],
				ep->stid, sin->sin_addr.s_addr, sin->sin_port,
				0, ep->com.dev->rdev.lldi.rxq_ids[0]);
		अगर (!err)
			err = c4iw_रुको_क्रम_reply(&ep->com.dev->rdev,
						  ep->com.wr_रुकोp,
						  0, 0, __func__);
		अन्यथा अगर (err > 0)
			err = net_xmit_त्रुटि_सं(err);
	पूर्ण
	अगर (err)
		pr_err("cxgb4_create_server/filter failed err %d stid %d laddr %pI4 lport %d\n"
		       , err, ep->stid,
		       &sin->sin_addr, ntohs(sin->sin_port));
	वापस err;
पूर्ण

पूर्णांक c4iw_create_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog)
अणु
	पूर्णांक err = 0;
	काष्ठा c4iw_dev *dev = to_c4iw_dev(cm_id->device);
	काष्ठा c4iw_listen_ep *ep;

	might_sleep();

	ep = alloc_ep(माप(*ep), GFP_KERNEL);
	अगर (!ep) अणु
		pr_err("%s - cannot alloc ep\n", __func__);
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण
	skb_queue_head_init(&ep->com.ep_skb_list);
	pr_debug("ep %p\n", ep);
	ep->com.cm_id = cm_id;
	ref_cm_id(&ep->com);
	ep->com.dev = dev;
	ep->backlog = backlog;
	स_नकल(&ep->com.local_addr, &cm_id->m_local_addr,
	       माप(ep->com.local_addr));

	/*
	 * Allocate a server TID.
	 */
	अगर (dev->rdev.lldi.enable_fw_ofld_conn &&
	    ep->com.local_addr.ss_family == AF_INET)
		ep->stid = cxgb4_alloc_sftid(dev->rdev.lldi.tids,
					     cm_id->m_local_addr.ss_family, ep);
	अन्यथा
		ep->stid = cxgb4_alloc_stid(dev->rdev.lldi.tids,
					    cm_id->m_local_addr.ss_family, ep);

	अगर (ep->stid == -1) अणु
		pr_err("%s - cannot alloc stid\n", __func__);
		err = -ENOMEM;
		जाओ fail2;
	पूर्ण
	err = xa_insert_irq(&dev->stids, ep->stid, ep, GFP_KERNEL);
	अगर (err)
		जाओ fail3;

	state_set(&ep->com, LISTEN);
	अगर (ep->com.local_addr.ss_family == AF_INET)
		err = create_server4(dev, ep);
	अन्यथा
		err = create_server6(dev, ep);
	अगर (!err) अणु
		cm_id->provider_data = ep;
		जाओ out;
	पूर्ण
	xa_erase_irq(&ep->com.dev->stids, ep->stid);
fail3:
	cxgb4_मुक्त_stid(ep->com.dev->rdev.lldi.tids, ep->stid,
			ep->com.local_addr.ss_family);
fail2:
	deref_cm_id(&ep->com);
	c4iw_put_ep(&ep->com);
fail1:
out:
	वापस err;
पूर्ण

पूर्णांक c4iw_destroy_listen(काष्ठा iw_cm_id *cm_id)
अणु
	पूर्णांक err;
	काष्ठा c4iw_listen_ep *ep = to_listen_ep(cm_id);

	pr_debug("ep %p\n", ep);

	might_sleep();
	state_set(&ep->com, DEAD);
	अगर (ep->com.dev->rdev.lldi.enable_fw_ofld_conn &&
	    ep->com.local_addr.ss_family == AF_INET) अणु
		err = cxgb4_हटाओ_server_filter(
			ep->com.dev->rdev.lldi.ports[0], ep->stid,
			ep->com.dev->rdev.lldi.rxq_ids[0], false);
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *sin6;
		c4iw_init_wr_रुको(ep->com.wr_रुकोp);
		err = cxgb4_हटाओ_server(
				ep->com.dev->rdev.lldi.ports[0], ep->stid,
				ep->com.dev->rdev.lldi.rxq_ids[0],
				ep->com.local_addr.ss_family == AF_INET6);
		अगर (err)
			जाओ करोne;
		err = c4iw_रुको_क्रम_reply(&ep->com.dev->rdev, ep->com.wr_रुकोp,
					  0, 0, __func__);
		sin6 = (काष्ठा sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
	पूर्ण
	xa_erase_irq(&ep->com.dev->stids, ep->stid);
	cxgb4_मुक्त_stid(ep->com.dev->rdev.lldi.tids, ep->stid,
			ep->com.local_addr.ss_family);
करोne:
	deref_cm_id(&ep->com);
	c4iw_put_ep(&ep->com);
	वापस err;
पूर्ण

पूर्णांक c4iw_ep_disconnect(काष्ठा c4iw_ep *ep, पूर्णांक abrupt, gfp_t gfp)
अणु
	पूर्णांक ret = 0;
	पूर्णांक बंद = 0;
	पूर्णांक fatal = 0;
	काष्ठा c4iw_rdev *rdev;

	mutex_lock(&ep->com.mutex);

	pr_debug("ep %p state %s, abrupt %d\n", ep,
		 states[ep->com.state], abrupt);

	/*
	 * Ref the ep here in हाल we have fatal errors causing the
	 * ep to be released and मुक्तd.
	 */
	c4iw_get_ep(&ep->com);

	rdev = &ep->com.dev->rdev;
	अगर (c4iw_fatal_error(rdev)) अणु
		fatal = 1;
		बंद_complete_upcall(ep, -EIO);
		ep->com.state = DEAD;
	पूर्ण
	चयन (ep->com.state) अणु
	हाल MPA_REQ_WAIT:
	हाल MPA_REQ_SENT:
	हाल MPA_REQ_RCVD:
	हाल MPA_REP_SENT:
	हाल FPDU_MODE:
	हाल CONNECTING:
		बंद = 1;
		अगर (abrupt)
			ep->com.state = ABORTING;
		अन्यथा अणु
			ep->com.state = CLOSING;

			/*
			 * अगर we बंद beक्रमe we see the fw4_ack() then we fix
			 * up the समयr state since we're reusing it.
			 */
			अगर (ep->mpa_skb &&
			    test_bit(STOP_MPA_TIMER, &ep->com.flags)) अणु
				clear_bit(STOP_MPA_TIMER, &ep->com.flags);
				stop_ep_समयr(ep);
			पूर्ण
			start_ep_समयr(ep);
		पूर्ण
		set_bit(CLOSE_SENT, &ep->com.flags);
		अवरोध;
	हाल CLOSING:
		अगर (!test_and_set_bit(CLOSE_SENT, &ep->com.flags)) अणु
			बंद = 1;
			अगर (abrupt) अणु
				(व्योम)stop_ep_समयr(ep);
				ep->com.state = ABORTING;
			पूर्ण अन्यथा
				ep->com.state = MORIBUND;
		पूर्ण
		अवरोध;
	हाल MORIBUND:
	हाल ABORTING:
	हाल DEAD:
		pr_debug("ignoring disconnect ep %p state %u\n",
			 ep, ep->com.state);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Bad endpoint state %u\n", ep->com.state);
		अवरोध;
	पूर्ण

	अगर (बंद) अणु
		अगर (abrupt) अणु
			set_bit(EP_DISC_ABORT, &ep->com.history);
			ret = send_पात(ep);
		पूर्ण अन्यथा अणु
			set_bit(EP_DISC_CLOSE, &ep->com.history);
			ret = send_halख_बंद(ep);
		पूर्ण
		अगर (ret) अणु
			set_bit(EP_DISC_FAIL, &ep->com.history);
			अगर (!abrupt) अणु
				stop_ep_समयr(ep);
				बंद_complete_upcall(ep, -EIO);
			पूर्ण
			अगर (ep->com.qp) अणु
				काष्ठा c4iw_qp_attributes attrs;

				attrs.next_state = C4IW_QP_STATE_ERROR;
				ret = c4iw_modअगरy_qp(ep->com.qp->rhp,
						     ep->com.qp,
						     C4IW_QP_ATTR_NEXT_STATE,
						     &attrs, 1);
				अगर (ret)
					pr_err("%s - qp <- error failed!\n",
					       __func__);
			पूर्ण
			fatal = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ep->com.mutex);
	c4iw_put_ep(&ep->com);
	अगर (fatal)
		release_ep_resources(ep);
	वापस ret;
पूर्ण

अटल व्योम active_ofld_conn_reply(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb,
			काष्ठा cpl_fw6_msg_ofld_connection_wr_rpl *req)
अणु
	काष्ठा c4iw_ep *ep;
	पूर्णांक atid = be32_to_cpu(req->tid);

	ep = (काष्ठा c4iw_ep *)lookup_atid(dev->rdev.lldi.tids,
					   (__क्रमce u32) req->tid);
	अगर (!ep)
		वापस;

	चयन (req->retval) अणु
	हाल FW_ENOMEM:
		set_bit(ACT_RETRY_NOMEM, &ep->com.history);
		अगर (ep->retry_count++ < ACT_OPEN_RETRY_COUNT) अणु
			send_fw_act_खोलो_req(ep, atid);
			वापस;
		पूर्ण
		fallthrough;
	हाल FW_EADDRINUSE:
		set_bit(ACT_RETRY_INUSE, &ep->com.history);
		अगर (ep->retry_count++ < ACT_OPEN_RETRY_COUNT) अणु
			send_fw_act_खोलो_req(ep, atid);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		pr_info("%s unexpected ofld conn wr retval %d\n",
		       __func__, req->retval);
		अवरोध;
	पूर्ण
	pr_err("active ofld_connect_wr failure %d atid %d\n",
	       req->retval, atid);
	mutex_lock(&dev->rdev.stats.lock);
	dev->rdev.stats.act_ofld_conn_fails++;
	mutex_unlock(&dev->rdev.stats.lock);
	connect_reply_upcall(ep, status2त्रुटि_सं(req->retval));
	state_set(&ep->com, DEAD);
	अगर (ep->com.remote_addr.ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 =
			(काष्ठा sockaddr_in6 *)&ep->com.local_addr;
		cxgb4_clip_release(ep->com.dev->rdev.lldi.ports[0],
				   (स्थिर u32 *)&sin6->sin6_addr.s6_addr, 1);
	पूर्ण
	xa_erase_irq(&dev->atids, atid);
	cxgb4_मुक्त_atid(dev->rdev.lldi.tids, atid);
	dst_release(ep->dst);
	cxgb4_l2t_release(ep->l2t);
	c4iw_put_ep(&ep->com);
पूर्ण

अटल व्योम passive_ofld_conn_reply(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb,
			काष्ठा cpl_fw6_msg_ofld_connection_wr_rpl *req)
अणु
	काष्ठा sk_buff *rpl_skb;
	काष्ठा cpl_pass_accept_req *cpl;
	पूर्णांक ret;

	rpl_skb = (काष्ठा sk_buff *)(अचिन्हित दीर्घ)req->cookie;
	अगर (req->retval) अणु
		pr_err("%s passive open failure %d\n", __func__, req->retval);
		mutex_lock(&dev->rdev.stats.lock);
		dev->rdev.stats.pas_ofld_conn_fails++;
		mutex_unlock(&dev->rdev.stats.lock);
		kमुक्त_skb(rpl_skb);
	पूर्ण अन्यथा अणु
		cpl = (काष्ठा cpl_pass_accept_req *)cplhdr(rpl_skb);
		OPCODE_TID(cpl) = htonl(MK_OPCODE_TID(CPL_PASS_ACCEPT_REQ,
					(__क्रमce u32) htonl(
					(__क्रमce u32) req->tid)));
		ret = pass_accept_req(dev, rpl_skb);
		अगर (!ret)
			kमुक्त_skb(rpl_skb);
	पूर्ण
	वापस;
पूर्ण

अटल अंतरभूत u64 t4_tcb_get_field64(__be64 *tcb, u16 word)
अणु
	u64 tlo = be64_to_cpu(tcb[((31 - word) / 2)]);
	u64 thi = be64_to_cpu(tcb[((31 - word) / 2) - 1]);
	u64 t;
	u32 shअगरt = 32;

	t = (thi << shअगरt) | (tlo >> shअगरt);

	वापस t;
पूर्ण

अटल अंतरभूत u32 t4_tcb_get_field32(__be64 *tcb, u16 word, u32 mask, u32 shअगरt)
अणु
	u32 v;
	u64 t = be64_to_cpu(tcb[(31 - word) / 2]);

	अगर (word & 0x1)
		shअगरt += 32;
	v = (t >> shअगरt) & mask;
	वापस v;
पूर्ण

अटल पूर्णांक पढ़ो_tcb_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_get_tcb_rpl *rpl = cplhdr(skb);
	__be64 *tcb = (__be64 *)(rpl + 1);
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	काष्ठा c4iw_ep *ep;
	u64 t_flags_64;
	u32 rx_pdu_out;

	ep = get_ep_from_tid(dev, tid);
	अगर (!ep)
		वापस 0;
	/* Examine the TF_RX_PDU_OUT (bit 49 of the t_flags) in order to
	 * determine अगर there's a rx PDU feedback event pending.
	 *
	 * If that bit is set, it means we'll need to re-read the TCB's
	 * rq_start value. The final value is the one present in a TCB
	 * with the TF_RX_PDU_OUT bit cleared.
	 */

	t_flags_64 = t4_tcb_get_field64(tcb, TCB_T_FLAGS_W);
	rx_pdu_out = (t_flags_64 & TF_RX_PDU_OUT_V(1)) >> TF_RX_PDU_OUT_S;

	c4iw_put_ep(&ep->com); /* from get_ep_from_tid() */
	c4iw_put_ep(&ep->com); /* from पढ़ो_tcb() */

	/* If TF_RX_PDU_OUT bit is set, re-पढ़ो the TCB */
	अगर (rx_pdu_out) अणु
		अगर (++ep->rx_pdu_out_cnt >= 2) अणु
			WARN_ONCE(1, "tcb re-read() reached the guard limit, finishing the cleanup\n");
			जाओ cleanup;
		पूर्ण
		पढ़ो_tcb(ep);
		वापस 0;
	पूर्ण

	ep->srqe_idx = t4_tcb_get_field32(tcb, TCB_RQ_START_W, TCB_RQ_START_M,
					  TCB_RQ_START_S);
cleanup:
	pr_debug("ep %p tid %u %016x\n", ep, ep->hwtid, ep->srqe_idx);

	अगर (test_bit(PEER_ABORT_IN_PROGRESS, &ep->com.flags))
		finish_peer_पात(dev, ep);
	अन्यथा अगर (test_bit(ABORT_REQ_IN_PROGRESS, &ep->com.flags))
		send_पात_req(ep);
	अन्यथा
		WARN_ONCE(1, "unexpected state!");

	वापस 0;
पूर्ण

अटल पूर्णांक deferred_fw6_msg(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_fw6_msg *rpl = cplhdr(skb);
	काष्ठा cpl_fw6_msg_ofld_connection_wr_rpl *req;

	चयन (rpl->type) अणु
	हाल FW6_TYPE_CQE:
		c4iw_ev_dispatch(dev, (काष्ठा t4_cqe *)&rpl->data[0]);
		अवरोध;
	हाल FW6_TYPE_OFLD_CONNECTION_WR_RPL:
		req = (काष्ठा cpl_fw6_msg_ofld_connection_wr_rpl *)rpl->data;
		चयन (req->t_state) अणु
		हाल TCP_SYN_SENT:
			active_ofld_conn_reply(dev, skb, req);
			अवरोध;
		हाल TCP_SYN_RECV:
			passive_ofld_conn_reply(dev, skb, req);
			अवरोध;
		शेष:
			pr_err("%s unexpected ofld conn wr state %d\n",
			       __func__, req->t_state);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम build_cpl_pass_accept_req(काष्ठा sk_buff *skb, पूर्णांक stid , u8 tos)
अणु
	__be32 l2info;
	__be16 hdr_len, vlantag, len;
	u16 eth_hdr_len;
	पूर्णांक tcp_hdr_len, ip_hdr_len;
	u8 पूर्णांकf;
	काष्ठा cpl_rx_pkt *cpl = cplhdr(skb);
	काष्ठा cpl_pass_accept_req *req;
	काष्ठा tcp_options_received पंचांगp_opt;
	काष्ठा c4iw_dev *dev;
	क्रमागत chip_type type;

	dev = *((काष्ठा c4iw_dev **) (skb->cb + माप(व्योम *)));
	/* Store values from cpl_rx_pkt in temporary location. */
	vlantag = cpl->vlan;
	len = cpl->len;
	l2info  = cpl->l2info;
	hdr_len = cpl->hdr_len;
	पूर्णांकf = cpl->अगरf;

	__skb_pull(skb, माप(*req) + माप(काष्ठा rss_header));

	/*
	 * We need to parse the TCP options from SYN packet.
	 * to generate cpl_pass_accept_req.
	 */
	स_रखो(&पंचांगp_opt, 0, माप(पंचांगp_opt));
	tcp_clear_options(&पंचांगp_opt);
	tcp_parse_options(&init_net, skb, &पंचांगp_opt, 0, शून्य);

	req = __skb_push(skb, माप(*req));
	स_रखो(req, 0, माप(*req));
	req->l2info = cpu_to_be16(SYN_INTF_V(पूर्णांकf) |
			 SYN_MAC_IDX_V(RX_MACIDX_G(
			 be32_to_cpu(l2info))) |
			 SYN_XACT_MATCH_F);
	type = dev->rdev.lldi.adapter_type;
	tcp_hdr_len = RX_TCPHDR_LEN_G(be16_to_cpu(hdr_len));
	ip_hdr_len = RX_IPHDR_LEN_G(be16_to_cpu(hdr_len));
	req->hdr_len =
		cpu_to_be32(SYN_RX_CHAN_V(RX_CHAN_G(be32_to_cpu(l2info))));
	अगर (CHELSIO_CHIP_VERSION(type) <= CHELSIO_T5) अणु
		eth_hdr_len = is_t4(type) ?
				RX_ETHHDR_LEN_G(be32_to_cpu(l2info)) :
				RX_T5_ETHHDR_LEN_G(be32_to_cpu(l2info));
		req->hdr_len |= cpu_to_be32(TCP_HDR_LEN_V(tcp_hdr_len) |
					    IP_HDR_LEN_V(ip_hdr_len) |
					    ETH_HDR_LEN_V(eth_hdr_len));
	पूर्ण अन्यथा अणु /* T6 and later */
		eth_hdr_len = RX_T6_ETHHDR_LEN_G(be32_to_cpu(l2info));
		req->hdr_len |= cpu_to_be32(T6_TCP_HDR_LEN_V(tcp_hdr_len) |
					    T6_IP_HDR_LEN_V(ip_hdr_len) |
					    T6_ETH_HDR_LEN_V(eth_hdr_len));
	पूर्ण
	req->vlan = vlantag;
	req->len = len;
	req->tos_stid = cpu_to_be32(PASS_OPEN_TID_V(stid) |
				    PASS_OPEN_TOS_V(tos));
	req->tcpopt.mss = htons(पंचांगp_opt.mss_clamp);
	अगर (पंचांगp_opt.wscale_ok)
		req->tcpopt.wsf = पंचांगp_opt.snd_wscale;
	req->tcpopt.tstamp = पंचांगp_opt.saw_tstamp;
	अगर (पंचांगp_opt.sack_ok)
		req->tcpopt.sack = 1;
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_PASS_ACCEPT_REQ, 0));
	वापस;
पूर्ण

अटल व्योम send_fw_pass_खोलो_req(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb,
				  __be32 laddr, __be16 lport,
				  __be32 raddr, __be16 rport,
				  u32 rcv_isn, u32 filter, u16 winकरोw,
				  u32 rss_qid, u8 port_id)
अणु
	काष्ठा sk_buff *req_skb;
	काष्ठा fw_ofld_connection_wr *req;
	काष्ठा cpl_pass_accept_req *cpl = cplhdr(skb);
	पूर्णांक ret;

	req_skb = alloc_skb(माप(काष्ठा fw_ofld_connection_wr), GFP_KERNEL);
	अगर (!req_skb)
		वापस;
	req = __skb_put_zero(req_skb, माप(*req));
	req->op_compl = htonl(WR_OP_V(FW_OFLD_CONNECTION_WR) | FW_WR_COMPL_F);
	req->len16_pkd = htonl(FW_WR_LEN16_V(DIV_ROUND_UP(माप(*req), 16)));
	req->le.version_cpl = htonl(FW_OFLD_CONNECTION_WR_CPL_F);
	req->le.filter = (__क्रमce __be32) filter;
	req->le.lport = lport;
	req->le.pport = rport;
	req->le.u.ipv4.lip = laddr;
	req->le.u.ipv4.pip = raddr;
	req->tcb.rcv_nxt = htonl(rcv_isn + 1);
	req->tcb.rcv_adv = htons(winकरोw);
	req->tcb.t_state_to_astid =
		 htonl(FW_OFLD_CONNECTION_WR_T_STATE_V(TCP_SYN_RECV) |
			FW_OFLD_CONNECTION_WR_RCV_SCALE_V(cpl->tcpopt.wsf) |
			FW_OFLD_CONNECTION_WR_ASTID_V(
			PASS_OPEN_TID_G(ntohl(cpl->tos_stid))));

	/*
	 * We store the qid in opt2 which will be used by the firmware
	 * to send us the wr response.
	 */
	req->tcb.opt2 = htonl(RSS_QUEUE_V(rss_qid));

	/*
	 * We initialize the MSS index in TCB to 0xF.
	 * So that when driver sends cpl_pass_accept_rpl
	 * TCB picks up the correct value. If this was 0
	 * TP will ignore any value > 0 क्रम MSS index.
	 */
	req->tcb.opt0 = cpu_to_be64(MSS_IDX_V(0xF));
	req->cookie = (uपूर्णांकptr_t)skb;

	set_wr_txq(req_skb, CPL_PRIORITY_CONTROL, port_id);
	ret = cxgb4_ofld_send(dev->rdev.lldi.ports[0], req_skb);
	अगर (ret < 0) अणु
		pr_err("%s - cxgb4_ofld_send error %d - dropping\n", __func__,
		       ret);
		kमुक्त_skb(skb);
		kमुक्त_skb(req_skb);
	पूर्ण
पूर्ण

/*
 * Handler क्रम CPL_RX_PKT message. Need to handle cpl_rx_pkt
 * messages when a filter is being used instead of server to
 * redirect a syn packet. When packets hit filter they are redirected
 * to the offload queue and driver tries to establish the connection
 * using firmware work request.
 */
अटल पूर्णांक rx_pkt(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक stid;
	अचिन्हित पूर्णांक filter;
	काष्ठा ethhdr *eh = शून्य;
	काष्ठा vlan_ethhdr *vlan_eh = शून्य;
	काष्ठा iphdr *iph;
	काष्ठा tcphdr *tcph;
	काष्ठा rss_header *rss = (व्योम *)skb->data;
	काष्ठा cpl_rx_pkt *cpl = (व्योम *)skb->data;
	काष्ठा cpl_pass_accept_req *req = (व्योम *)(rss + 1);
	काष्ठा l2t_entry *e;
	काष्ठा dst_entry *dst;
	काष्ठा c4iw_ep *lep = शून्य;
	u16 winकरोw;
	काष्ठा port_info *pi;
	काष्ठा net_device *pdev;
	u16 rss_qid, eth_hdr_len;
	पूर्णांक step;
	काष्ठा neighbour *neigh;

	/* Drop all non-SYN packets */
	अगर (!(cpl->l2info & cpu_to_be32(RXF_SYN_F)))
		जाओ reject;

	/*
	 * Drop all packets which did not hit the filter.
	 * Unlikely to happen.
	 */
	अगर (!(rss->filter_hit && rss->filter_tid))
		जाओ reject;

	/*
	 * Calculate the server tid from filter hit index from cpl_rx_pkt.
	 */
	stid = (__क्रमce पूर्णांक) cpu_to_be32((__क्रमce u32) rss->hash_val);

	lep = (काष्ठा c4iw_ep *)get_ep_from_stid(dev, stid);
	अगर (!lep) अणु
		pr_warn("%s connect request on invalid stid %d\n",
			__func__, stid);
		जाओ reject;
	पूर्ण

	चयन (CHELSIO_CHIP_VERSION(dev->rdev.lldi.adapter_type)) अणु
	हाल CHELSIO_T4:
		eth_hdr_len = RX_ETHHDR_LEN_G(be32_to_cpu(cpl->l2info));
		अवरोध;
	हाल CHELSIO_T5:
		eth_hdr_len = RX_T5_ETHHDR_LEN_G(be32_to_cpu(cpl->l2info));
		अवरोध;
	हाल CHELSIO_T6:
		eth_hdr_len = RX_T6_ETHHDR_LEN_G(be32_to_cpu(cpl->l2info));
		अवरोध;
	शेष:
		pr_err("T%d Chip is not supported\n",
		       CHELSIO_CHIP_VERSION(dev->rdev.lldi.adapter_type));
		जाओ reject;
	पूर्ण

	अगर (eth_hdr_len == ETH_HLEN) अणु
		eh = (काष्ठा ethhdr *)(req + 1);
		iph = (काष्ठा iphdr *)(eh + 1);
	पूर्ण अन्यथा अणु
		vlan_eh = (काष्ठा vlan_ethhdr *)(req + 1);
		iph = (काष्ठा iphdr *)(vlan_eh + 1);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(cpl->vlan));
	पूर्ण

	अगर (iph->version != 0x4)
		जाओ reject;

	tcph = (काष्ठा tcphdr *)(iph + 1);
	skb_set_network_header(skb, (व्योम *)iph - (व्योम *)rss);
	skb_set_transport_header(skb, (व्योम *)tcph - (व्योम *)rss);
	skb_get(skb);

	pr_debug("lip 0x%x lport %u pip 0x%x pport %u tos %d\n",
		 ntohl(iph->daddr), ntohs(tcph->dest), ntohl(iph->saddr),
		 ntohs(tcph->source), iph->tos);

	dst = cxgb_find_route(&dev->rdev.lldi, get_real_dev,
			      iph->daddr, iph->saddr, tcph->dest,
			      tcph->source, iph->tos);
	अगर (!dst) अणु
		pr_err("%s - failed to find dst entry!\n", __func__);
		जाओ reject;
	पूर्ण
	neigh = dst_neigh_lookup_skb(dst, skb);

	अगर (!neigh) अणु
		pr_err("%s - failed to allocate neigh!\n", __func__);
		जाओ मुक्त_dst;
	पूर्ण

	अगर (neigh->dev->flags & IFF_LOOPBACK) अणु
		pdev = ip_dev_find(&init_net, iph->daddr);
		e = cxgb4_l2t_get(dev->rdev.lldi.l2t, neigh,
				    pdev, 0);
		pi = (काष्ठा port_info *)netdev_priv(pdev);
		dev_put(pdev);
	पूर्ण अन्यथा अणु
		pdev = get_real_dev(neigh->dev);
		e = cxgb4_l2t_get(dev->rdev.lldi.l2t, neigh,
					pdev, 0);
		pi = (काष्ठा port_info *)netdev_priv(pdev);
	पूर्ण
	neigh_release(neigh);
	अगर (!e) अणु
		pr_err("%s - failed to allocate l2t entry!\n",
		       __func__);
		जाओ मुक्त_dst;
	पूर्ण

	step = dev->rdev.lldi.nrxq / dev->rdev.lldi.nchan;
	rss_qid = dev->rdev.lldi.rxq_ids[pi->port_id * step];
	winकरोw = (__क्रमce u16) htons((__क्रमce u16)tcph->winकरोw);

	/* Calcuate filter portion क्रम LE region. */
	filter = (__क्रमce अचिन्हित पूर्णांक) cpu_to_be32(cxgb4_select_ntuple(
						    dev->rdev.lldi.ports[0],
						    e));

	/*
	 * Synthesize the cpl_pass_accept_req. We have everything except the
	 * TID. Once firmware sends a reply with TID we update the TID field
	 * in cpl and pass it through the regular cpl_pass_accept_req path.
	 */
	build_cpl_pass_accept_req(skb, stid, iph->tos);
	send_fw_pass_खोलो_req(dev, skb, iph->daddr, tcph->dest, iph->saddr,
			      tcph->source, ntohl(tcph->seq), filter, winकरोw,
			      rss_qid, pi->port_id);
	cxgb4_l2t_release(e);
मुक्त_dst:
	dst_release(dst);
reject:
	अगर (lep)
		c4iw_put_ep(&lep->com);
	वापस 0;
पूर्ण

/*
 * These are the real handlers that are called from a
 * work queue.
 */
अटल c4iw_handler_func work_handlers[NUM_CPL_CMDS + NUM_FAKE_CPLS] = अणु
	[CPL_ACT_ESTABLISH] = act_establish,
	[CPL_ACT_OPEN_RPL] = act_खोलो_rpl,
	[CPL_RX_DATA] = rx_data,
	[CPL_ABORT_RPL_RSS] = पात_rpl,
	[CPL_ABORT_RPL] = पात_rpl,
	[CPL_PASS_OPEN_RPL] = pass_खोलो_rpl,
	[CPL_CLOSE_LISTSRV_RPL] = बंद_listsrv_rpl,
	[CPL_PASS_ACCEPT_REQ] = pass_accept_req,
	[CPL_PASS_ESTABLISH] = pass_establish,
	[CPL_PEER_CLOSE] = peer_बंद,
	[CPL_ABORT_REQ_RSS] = peer_पात,
	[CPL_CLOSE_CON_RPL] = बंद_con_rpl,
	[CPL_RDMA_TERMINATE] = terminate,
	[CPL_FW4_ACK] = fw4_ack,
	[CPL_GET_TCB_RPL] = पढ़ो_tcb_rpl,
	[CPL_FW6_MSG] = deferred_fw6_msg,
	[CPL_RX_PKT] = rx_pkt,
	[FAKE_CPL_PUT_EP_SAFE] = _put_ep_safe,
	[FAKE_CPL_PASS_PUT_EP_SAFE] = _put_pass_ep_safe
पूर्ण;

अटल व्योम process_समयout(काष्ठा c4iw_ep *ep)
अणु
	काष्ठा c4iw_qp_attributes attrs;
	पूर्णांक पात = 1;

	mutex_lock(&ep->com.mutex);
	pr_debug("ep %p tid %u state %d\n", ep, ep->hwtid, ep->com.state);
	set_bit(TIMEDOUT, &ep->com.history);
	चयन (ep->com.state) अणु
	हाल MPA_REQ_SENT:
		connect_reply_upcall(ep, -ETIMEDOUT);
		अवरोध;
	हाल MPA_REQ_WAIT:
	हाल MPA_REQ_RCVD:
	हाल MPA_REP_SENT:
	हाल FPDU_MODE:
		अवरोध;
	हाल CLOSING:
	हाल MORIBUND:
		अगर (ep->com.cm_id && ep->com.qp) अणु
			attrs.next_state = C4IW_QP_STATE_ERROR;
			c4iw_modअगरy_qp(ep->com.qp->rhp,
				     ep->com.qp, C4IW_QP_ATTR_NEXT_STATE,
				     &attrs, 1);
		पूर्ण
		बंद_complete_upcall(ep, -ETIMEDOUT);
		अवरोध;
	हाल ABORTING:
	हाल DEAD:

		/*
		 * These states are expected अगर the ep समयd out at the same
		 * समय as another thपढ़ो was calling stop_ep_समयr().
		 * So we silently करो nothing क्रम these states.
		 */
		पात = 0;
		अवरोध;
	शेष:
		WARN(1, "%s unexpected state ep %p tid %u state %u\n",
			__func__, ep, ep->hwtid, ep->com.state);
		पात = 0;
	पूर्ण
	mutex_unlock(&ep->com.mutex);
	अगर (पात)
		c4iw_ep_disconnect(ep, 1, GFP_KERNEL);
	c4iw_put_ep(&ep->com);
पूर्ण

अटल व्योम process_समयकरोut_eps(व्योम)
अणु
	काष्ठा c4iw_ep *ep;

	spin_lock_irq(&समयout_lock);
	जबतक (!list_empty(&समयout_list)) अणु
		काष्ठा list_head *पंचांगp;

		पंचांगp = समयout_list.next;
		list_del(पंचांगp);
		पंचांगp->next = शून्य;
		पंचांगp->prev = शून्य;
		spin_unlock_irq(&समयout_lock);
		ep = list_entry(पंचांगp, काष्ठा c4iw_ep, entry);
		process_समयout(ep);
		spin_lock_irq(&समयout_lock);
	पूर्ण
	spin_unlock_irq(&समयout_lock);
पूर्ण

अटल व्योम process_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा c4iw_dev *dev;
	काष्ठा cpl_act_establish *rpl;
	अचिन्हित पूर्णांक opcode;
	पूर्णांक ret;

	process_समयकरोut_eps();
	जबतक ((skb = skb_dequeue(&rxq))) अणु
		rpl = cplhdr(skb);
		dev = *((काष्ठा c4iw_dev **) (skb->cb + माप(व्योम *)));
		opcode = rpl->ot.opcode;

		अगर (opcode >= ARRAY_SIZE(work_handlers) ||
		    !work_handlers[opcode]) अणु
			pr_err("No handler for opcode 0x%x.\n", opcode);
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			ret = work_handlers[opcode](dev, skb);
			अगर (!ret)
				kमुक्त_skb(skb);
		पूर्ण
		process_समयकरोut_eps();
	पूर्ण
पूर्ण

अटल DECLARE_WORK(skb_work, process_work);

अटल व्योम ep_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा c4iw_ep *ep = from_समयr(ep, t, समयr);
	पूर्णांक kickit = 0;

	spin_lock(&समयout_lock);
	अगर (!test_and_set_bit(TIMEOUT, &ep->com.flags)) अणु
		/*
		 * Only insert अगर it is not alपढ़ोy on the list.
		 */
		अगर (!ep->entry.next) अणु
			list_add_tail(&ep->entry, &समयout_list);
			kickit = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&समयout_lock);
	अगर (kickit)
		queue_work(workq, &skb_work);
पूर्ण

/*
 * All the CM events are handled on a work queue to have a safe context.
 */
अटल पूर्णांक sched(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु

	/*
	 * Save dev in the skb->cb area.
	 */
	*((काष्ठा c4iw_dev **) (skb->cb + माप(व्योम *))) = dev;

	/*
	 * Queue the skb and schedule the worker thपढ़ो.
	 */
	skb_queue_tail(&rxq, skb);
	queue_work(workq, &skb_work);
	वापस 0;
पूर्ण

अटल पूर्णांक set_tcb_rpl(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_set_tcb_rpl *rpl = cplhdr(skb);

	अगर (rpl->status != CPL_ERR_NONE) अणु
		pr_err("Unexpected SET_TCB_RPL status %u for tid %u\n",
		       rpl->status, GET_TID(rpl));
	पूर्ण
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक fw6_msg(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_fw6_msg *rpl = cplhdr(skb);
	काष्ठा c4iw_wr_रुको *wr_रुकोp;
	पूर्णांक ret;

	pr_debug("type %u\n", rpl->type);

	चयन (rpl->type) अणु
	हाल FW6_TYPE_WR_RPL:
		ret = (पूर्णांक)((be64_to_cpu(rpl->data[0]) >> 8) & 0xff);
		wr_रुकोp = (काष्ठा c4iw_wr_रुको *)(__क्रमce अचिन्हित दीर्घ) rpl->data[1];
		pr_debug("wr_waitp %p ret %u\n", wr_रुकोp, ret);
		अगर (wr_रुकोp)
			c4iw_wake_up_deref(wr_रुकोp, ret ? -ret : 0);
		kमुक्त_skb(skb);
		अवरोध;
	हाल FW6_TYPE_CQE:
	हाल FW6_TYPE_OFLD_CONNECTION_WR_RPL:
		sched(dev, skb);
		अवरोध;
	शेष:
		pr_err("%s unexpected fw6 msg type %u\n",
		       __func__, rpl->type);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक peer_पात_पूर्णांकr(काष्ठा c4iw_dev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_पात_req_rss *req = cplhdr(skb);
	काष्ठा c4iw_ep *ep;
	अचिन्हित पूर्णांक tid = GET_TID(req);

	ep = get_ep_from_tid(dev, tid);
	/* This EP will be dereferenced in peer_पात() */
	अगर (!ep) अणु
		pr_warn("Abort on non-existent endpoint, tid %d\n", tid);
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	अगर (cxgb_is_neg_adv(req->status)) अणु
		pr_debug("Negative advice on abort- tid %u status %d (%s)\n",
			 ep->hwtid, req->status,
			 neg_adv_str(req->status));
		जाओ out;
	पूर्ण
	pr_debug("ep %p tid %u state %u\n", ep, ep->hwtid, ep->com.state);

	c4iw_wake_up_noref(ep->com.wr_रुकोp, -ECONNRESET);
out:
	sched(dev, skb);
	वापस 0;
पूर्ण

/*
 * Most upcalls from the T4 Core go to sched() to
 * schedule the processing on a work queue.
 */
c4iw_handler_func c4iw_handlers[NUM_CPL_CMDS] = अणु
	[CPL_ACT_ESTABLISH] = sched,
	[CPL_ACT_OPEN_RPL] = sched,
	[CPL_RX_DATA] = sched,
	[CPL_ABORT_RPL_RSS] = sched,
	[CPL_ABORT_RPL] = sched,
	[CPL_PASS_OPEN_RPL] = sched,
	[CPL_CLOSE_LISTSRV_RPL] = sched,
	[CPL_PASS_ACCEPT_REQ] = sched,
	[CPL_PASS_ESTABLISH] = sched,
	[CPL_PEER_CLOSE] = sched,
	[CPL_CLOSE_CON_RPL] = sched,
	[CPL_ABORT_REQ_RSS] = peer_पात_पूर्णांकr,
	[CPL_RDMA_TERMINATE] = sched,
	[CPL_FW4_ACK] = sched,
	[CPL_SET_TCB_RPL] = set_tcb_rpl,
	[CPL_GET_TCB_RPL] = sched,
	[CPL_FW6_MSG] = fw6_msg,
	[CPL_RX_PKT] = sched
पूर्ण;

पूर्णांक __init c4iw_cm_init(व्योम)
अणु
	skb_queue_head_init(&rxq);

	workq = alloc_ordered_workqueue("iw_cxgb4", WQ_MEM_RECLAIM);
	अगर (!workq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम c4iw_cm_term(व्योम)
अणु
	WARN_ON(!list_empty(&समयout_list));
	flush_workqueue(workq);
	destroy_workqueue(workq);
पूर्ण
