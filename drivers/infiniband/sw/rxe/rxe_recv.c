<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/skbuff.h>

#समावेश "rxe.h"
#समावेश "rxe_loc.h"

/* check that QP matches packet opcode type and is in a valid state */
अटल पूर्णांक check_type_state(काष्ठा rxe_dev *rxe, काष्ठा rxe_pkt_info *pkt,
			    काष्ठा rxe_qp *qp)
अणु
	अचिन्हित पूर्णांक pkt_type;

	अगर (unlikely(!qp->valid))
		जाओ err1;

	pkt_type = pkt->opcode & 0xe0;

	चयन (qp_type(qp)) अणु
	हाल IB_QPT_RC:
		अगर (unlikely(pkt_type != IB_OPCODE_RC)) अणु
			pr_warn_ratelimited("bad qp type\n");
			जाओ err1;
		पूर्ण
		अवरोध;
	हाल IB_QPT_UC:
		अगर (unlikely(pkt_type != IB_OPCODE_UC)) अणु
			pr_warn_ratelimited("bad qp type\n");
			जाओ err1;
		पूर्ण
		अवरोध;
	हाल IB_QPT_UD:
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
		अगर (unlikely(pkt_type != IB_OPCODE_UD)) अणु
			pr_warn_ratelimited("bad qp type\n");
			जाओ err1;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn_ratelimited("unsupported qp type\n");
		जाओ err1;
	पूर्ण

	अगर (pkt->mask & RXE_REQ_MASK) अणु
		अगर (unlikely(qp->resp.state != QP_STATE_READY))
			जाओ err1;
	पूर्ण अन्यथा अगर (unlikely(qp->req.state < QP_STATE_READY ||
				qp->req.state > QP_STATE_DRAINED)) अणु
		जाओ err1;
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल व्योम set_bad_pkey_cntr(काष्ठा rxe_port *port)
अणु
	spin_lock_bh(&port->port_lock);
	port->attr.bad_pkey_cntr = min((u32)0xffff,
				       port->attr.bad_pkey_cntr + 1);
	spin_unlock_bh(&port->port_lock);
पूर्ण

अटल व्योम set_qkey_viol_cntr(काष्ठा rxe_port *port)
अणु
	spin_lock_bh(&port->port_lock);
	port->attr.qkey_viol_cntr = min((u32)0xffff,
					port->attr.qkey_viol_cntr + 1);
	spin_unlock_bh(&port->port_lock);
पूर्ण

अटल पूर्णांक check_keys(काष्ठा rxe_dev *rxe, काष्ठा rxe_pkt_info *pkt,
		      u32 qpn, काष्ठा rxe_qp *qp)
अणु
	काष्ठा rxe_port *port = &rxe->port;
	u16 pkey = bth_pkey(pkt);

	pkt->pkey_index = 0;

	अगर (!pkey_match(pkey, IB_DEFAULT_PKEY_FULL)) अणु
		pr_warn_ratelimited("bad pkey = 0x%x\n", pkey);
		set_bad_pkey_cntr(port);
		जाओ err1;
	पूर्ण

	अगर (qp_type(qp) == IB_QPT_UD || qp_type(qp) == IB_QPT_GSI) अणु
		u32 qkey = (qpn == 1) ? GSI_QKEY : qp->attr.qkey;

		अगर (unlikely(deth_qkey(pkt) != qkey)) अणु
			pr_warn_ratelimited("bad qkey, got 0x%x expected 0x%x for qpn 0x%x\n",
					    deth_qkey(pkt), qkey, qpn);
			set_qkey_viol_cntr(port);
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_addr(काष्ठा rxe_dev *rxe, काष्ठा rxe_pkt_info *pkt,
		      काष्ठा rxe_qp *qp)
अणु
	काष्ठा sk_buff *skb = PKT_TO_SKB(pkt);

	अगर (qp_type(qp) != IB_QPT_RC && qp_type(qp) != IB_QPT_UC)
		जाओ करोne;

	अगर (unlikely(pkt->port_num != qp->attr.port_num)) अणु
		pr_warn_ratelimited("port %d != qp port %d\n",
				    pkt->port_num, qp->attr.port_num);
		जाओ err1;
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा in_addr *saddr =
			&qp->pri_av.sgid_addr._sockaddr_in.sin_addr;
		काष्ठा in_addr *daddr =
			&qp->pri_av.dgid_addr._sockaddr_in.sin_addr;

		अगर (ip_hdr(skb)->daddr != saddr->s_addr) अणु
			pr_warn_ratelimited("dst addr %pI4 != qp source addr %pI4\n",
					    &ip_hdr(skb)->daddr,
					    &saddr->s_addr);
			जाओ err1;
		पूर्ण

		अगर (ip_hdr(skb)->saddr != daddr->s_addr) अणु
			pr_warn_ratelimited("source addr %pI4 != qp dst addr %pI4\n",
					    &ip_hdr(skb)->saddr,
					    &daddr->s_addr);
			जाओ err1;
		पूर्ण

	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा in6_addr *saddr =
			&qp->pri_av.sgid_addr._sockaddr_in6.sin6_addr;
		काष्ठा in6_addr *daddr =
			&qp->pri_av.dgid_addr._sockaddr_in6.sin6_addr;

		अगर (स_भेद(&ipv6_hdr(skb)->daddr, saddr, माप(*saddr))) अणु
			pr_warn_ratelimited("dst addr %pI6 != qp source addr %pI6\n",
					    &ipv6_hdr(skb)->daddr, saddr);
			जाओ err1;
		पूर्ण

		अगर (स_भेद(&ipv6_hdr(skb)->saddr, daddr, माप(*daddr))) अणु
			pr_warn_ratelimited("source addr %pI6 != qp dst addr %pI6\n",
					    &ipv6_hdr(skb)->saddr, daddr);
			जाओ err1;
		पूर्ण
	पूर्ण

करोne:
	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hdr_check(काष्ठा rxe_pkt_info *pkt)
अणु
	काष्ठा rxe_dev *rxe = pkt->rxe;
	काष्ठा rxe_port *port = &rxe->port;
	काष्ठा rxe_qp *qp = शून्य;
	u32 qpn = bth_qpn(pkt);
	पूर्णांक index;
	पूर्णांक err;

	अगर (unlikely(bth_tver(pkt) != BTH_TVER)) अणु
		pr_warn_ratelimited("bad tver\n");
		जाओ err1;
	पूर्ण

	अगर (unlikely(qpn == 0)) अणु
		pr_warn_once("QP 0 not supported");
		जाओ err1;
	पूर्ण

	अगर (qpn != IB_MULTICAST_QPN) अणु
		index = (qpn == 1) ? port->qp_gsi_index : qpn;

		qp = rxe_pool_get_index(&rxe->qp_pool, index);
		अगर (unlikely(!qp)) अणु
			pr_warn_ratelimited("no qp matches qpn 0x%x\n", qpn);
			जाओ err1;
		पूर्ण

		err = check_type_state(rxe, pkt, qp);
		अगर (unlikely(err))
			जाओ err2;

		err = check_addr(rxe, pkt, qp);
		अगर (unlikely(err))
			जाओ err2;

		err = check_keys(rxe, pkt, qpn, qp);
		अगर (unlikely(err))
			जाओ err2;
	पूर्ण अन्यथा अणु
		अगर (unlikely((pkt->mask & RXE_GRH_MASK) == 0)) अणु
			pr_warn_ratelimited("no grh for mcast qpn\n");
			जाओ err1;
		पूर्ण
	पूर्ण

	pkt->qp = qp;
	वापस 0;

err2:
	rxe_drop_ref(qp);
err1:
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम rxe_rcv_pkt(काष्ठा rxe_pkt_info *pkt, काष्ठा sk_buff *skb)
अणु
	अगर (pkt->mask & RXE_REQ_MASK)
		rxe_resp_queue_pkt(pkt->qp, skb);
	अन्यथा
		rxe_comp_queue_pkt(pkt->qp, skb);
पूर्ण

अटल व्योम rxe_rcv_mcast_pkt(काष्ठा rxe_dev *rxe, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);
	काष्ठा rxe_mc_grp *mcg;
	काष्ठा rxe_mc_elem *mce;
	काष्ठा rxe_qp *qp;
	जोड़ ib_gid dgid;
	पूर्णांक err;

	अगर (skb->protocol == htons(ETH_P_IP))
		ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
				       (काष्ठा in6_addr *)&dgid);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		स_नकल(&dgid, &ipv6_hdr(skb)->daddr, माप(dgid));

	/* lookup mcast group corresponding to mgid, takes a ref */
	mcg = rxe_pool_get_key(&rxe->mc_grp_pool, &dgid);
	अगर (!mcg)
		जाओ drop;	/* mcast group not रेजिस्टरed */

	spin_lock_bh(&mcg->mcg_lock);

	/* this is unreliable datagram service so we let
	 * failures to deliver a multicast packet to a
	 * single QP happen and just move on and try
	 * the rest of them on the list
	 */
	list_क्रम_each_entry(mce, &mcg->qp_list, qp_list) अणु
		qp = mce->qp;

		/* validate qp क्रम incoming packet */
		err = check_type_state(rxe, pkt, qp);
		अगर (err)
			जारी;

		err = check_keys(rxe, pkt, bth_qpn(pkt), qp);
		अगर (err)
			जारी;

		/* क्रम all but the last QP create a new clone of the
		 * skb and pass to the QP. Pass the original skb to
		 * the last QP in the list.
		 */
		अगर (mce->qp_list.next != &mcg->qp_list) अणु
			काष्ठा sk_buff *cskb;
			काष्ठा rxe_pkt_info *cpkt;

			cskb = skb_clone(skb, GFP_ATOMIC);
			अगर (unlikely(!cskb))
				जारी;

			अगर (WARN_ON(!ib_device_try_get(&rxe->ib_dev))) अणु
				kमुक्त_skb(cskb);
				अवरोध;
			पूर्ण

			cpkt = SKB_TO_PKT(cskb);
			cpkt->qp = qp;
			rxe_add_ref(qp);
			rxe_rcv_pkt(cpkt, cskb);
		पूर्ण अन्यथा अणु
			pkt->qp = qp;
			rxe_add_ref(qp);
			rxe_rcv_pkt(pkt, skb);
			skb = शून्य;	/* mark consumed */
		पूर्ण
	पूर्ण

	spin_unlock_bh(&mcg->mcg_lock);

	rxe_drop_ref(mcg);	/* drop ref from rxe_pool_get_key. */

	अगर (likely(!skb))
		वापस;

	/* This only occurs अगर one of the checks fails on the last
	 * QP in the list above
	 */

drop:
	kमुक्त_skb(skb);
	ib_device_put(&rxe->ib_dev);
पूर्ण

/**
 * rxe_chk_dgid - validate destination IP address
 * @rxe: rxe device that received packet
 * @skb: the received packet buffer
 *
 * Accept any loopback packets
 * Extract IP address from packet and
 * Accept अगर multicast packet
 * Accept अगर matches an SGID table entry
 */
अटल पूर्णांक rxe_chk_dgid(काष्ठा rxe_dev *rxe, काष्ठा sk_buff *skb)
अणु
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);
	स्थिर काष्ठा ib_gid_attr *gid_attr;
	जोड़ ib_gid dgid;
	जोड़ ib_gid *pdgid;

	अगर (pkt->mask & RXE_LOOPBACK_MASK)
		वापस 0;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
				       (काष्ठा in6_addr *)&dgid);
		pdgid = &dgid;
	पूर्ण अन्यथा अणु
		pdgid = (जोड़ ib_gid *)&ipv6_hdr(skb)->daddr;
	पूर्ण

	अगर (rdma_is_multicast_addr((काष्ठा in6_addr *)pdgid))
		वापस 0;

	gid_attr = rdma_find_gid_by_port(&rxe->ib_dev, pdgid,
					 IB_GID_TYPE_ROCE_UDP_ENCAP,
					 1, skb->dev);
	अगर (IS_ERR(gid_attr))
		वापस PTR_ERR(gid_attr);

	rdma_put_gid_attr(gid_attr);
	वापस 0;
पूर्ण

/* rxe_rcv is called from the पूर्णांकerface driver */
व्योम rxe_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	काष्ठा rxe_pkt_info *pkt = SKB_TO_PKT(skb);
	काष्ठा rxe_dev *rxe = pkt->rxe;
	__be32 *icrcp;
	u32 calc_icrc, pack_icrc;

	अगर (unlikely(skb->len < RXE_BTH_BYTES))
		जाओ drop;

	अगर (rxe_chk_dgid(rxe, skb) < 0) अणु
		pr_warn_ratelimited("failed checking dgid\n");
		जाओ drop;
	पूर्ण

	pkt->opcode = bth_opcode(pkt);
	pkt->psn = bth_psn(pkt);
	pkt->qp = शून्य;
	pkt->mask |= rxe_opcode[pkt->opcode].mask;

	अगर (unlikely(skb->len < header_size(pkt)))
		जाओ drop;

	err = hdr_check(pkt);
	अगर (unlikely(err))
		जाओ drop;

	/* Verअगरy ICRC */
	icrcp = (__be32 *)(pkt->hdr + pkt->paylen - RXE_ICRC_SIZE);
	pack_icrc = be32_to_cpu(*icrcp);

	calc_icrc = rxe_icrc_hdr(pkt, skb);
	calc_icrc = rxe_crc32(rxe, calc_icrc, (u8 *)payload_addr(pkt),
			      payload_size(pkt) + bth_pad(pkt));
	calc_icrc = (__क्रमce u32)cpu_to_be32(~calc_icrc);
	अगर (unlikely(calc_icrc != pack_icrc)) अणु
		अगर (skb->protocol == htons(ETH_P_IPV6))
			pr_warn_ratelimited("bad ICRC from %pI6c\n",
					    &ipv6_hdr(skb)->saddr);
		अन्यथा अगर (skb->protocol == htons(ETH_P_IP))
			pr_warn_ratelimited("bad ICRC from %pI4\n",
					    &ip_hdr(skb)->saddr);
		अन्यथा
			pr_warn_ratelimited("bad ICRC from unknown\n");

		जाओ drop;
	पूर्ण

	rxe_counter_inc(rxe, RXE_CNT_RCVD_PKTS);

	अगर (unlikely(bth_qpn(pkt) == IB_MULTICAST_QPN))
		rxe_rcv_mcast_pkt(rxe, skb);
	अन्यथा
		rxe_rcv_pkt(pkt, skb);

	वापस;

drop:
	अगर (pkt->qp)
		rxe_drop_ref(pkt->qp);

	kमुक्त_skb(skb);
	ib_device_put(&rxe->ib_dev);
पूर्ण
