<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jhash.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/neighbour.h>
#समावेश "cxgb4.h"
#समावेश "l2t.h"
#समावेश "t4_msg.h"
#समावेश "t4fw_api.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"

/* identअगरies sync vs async L2T_WRITE_REQs */
#घोषणा SYNC_WR_S    12
#घोषणा SYNC_WR_V(x) ((x) << SYNC_WR_S)
#घोषणा SYNC_WR_F    SYNC_WR_V(1)

काष्ठा l2t_data अणु
	अचिन्हित पूर्णांक l2t_start;     /* start index of our piece of the L2T */
	अचिन्हित पूर्णांक l2t_size;      /* number of entries in l2tab */
	rwlock_t lock;
	atomic_t nमुक्त;             /* number of मुक्त entries */
	काष्ठा l2t_entry *rover;    /* starting poपूर्णांक क्रम next allocation */
	काष्ठा l2t_entry l2tab[];  /* MUST BE LAST */
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक vlan_prio(स्थिर काष्ठा l2t_entry *e)
अणु
	वापस e->vlan >> VLAN_PRIO_SHIFT;
पूर्ण

अटल अंतरभूत व्योम l2t_hold(काष्ठा l2t_data *d, काष्ठा l2t_entry *e)
अणु
	अगर (atomic_add_वापस(1, &e->refcnt) == 1)  /* 0 -> 1 transition */
		atomic_dec(&d->nमुक्त);
पूर्ण

/*
 * To aव्योम having to check address families we करो not allow v4 and v6
 * neighbors to be on the same hash chain.  We keep v4 entries in the first
 * half of available hash buckets and v6 in the second.  We need at least two
 * entries in our L2T क्रम this scheme to work.
 */
क्रमागत अणु
	L2T_MIN_HASH_BUCKETS = 2,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक arp_hash(काष्ठा l2t_data *d, स्थिर u32 *key,
				    पूर्णांक अगरindex)
अणु
	अचिन्हित पूर्णांक l2t_size_half = d->l2t_size / 2;

	वापस jhash_2words(*key, अगरindex, 0) % l2t_size_half;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ipv6_hash(काष्ठा l2t_data *d, स्थिर u32 *key,
				     पूर्णांक अगरindex)
अणु
	अचिन्हित पूर्णांक l2t_size_half = d->l2t_size / 2;
	u32 xor = key[0] ^ key[1] ^ key[2] ^ key[3];

	वापस (l2t_size_half +
		(jhash_2words(xor, अगरindex, 0) % l2t_size_half));
पूर्ण

अटल अचिन्हित पूर्णांक addr_hash(काष्ठा l2t_data *d, स्थिर u32 *addr,
			      पूर्णांक addr_len, पूर्णांक अगरindex)
अणु
	वापस addr_len == 4 ? arp_hash(d, addr, अगरindex) :
			       ipv6_hash(d, addr, अगरindex);
पूर्ण

/*
 * Checks अगर an L2T entry is क्रम the given IP/IPv6 address.  It करोes not check
 * whether the L2T entry and the address are of the same address family.
 * Callers ensure an address is only checked against L2T entries of the same
 * family, something made trivial by the separation of IP and IPv6 hash chains
 * mentioned above.  Returns 0 अगर there's a match,
 */
अटल पूर्णांक addreq(स्थिर काष्ठा l2t_entry *e, स्थिर u32 *addr)
अणु
	अगर (e->v6)
		वापस (e->addr[0] ^ addr[0]) | (e->addr[1] ^ addr[1]) |
		       (e->addr[2] ^ addr[2]) | (e->addr[3] ^ addr[3]);
	वापस e->addr[0] ^ addr[0];
पूर्ण

अटल व्योम neigh_replace(काष्ठा l2t_entry *e, काष्ठा neighbour *n)
अणु
	neigh_hold(n);
	अगर (e->neigh)
		neigh_release(e->neigh);
	e->neigh = n;
पूर्ण

/*
 * Write an L2T entry.  Must be called with the entry locked.
 * The ग_लिखो may be synchronous or asynchronous.
 */
अटल पूर्णांक ग_लिखो_l2e(काष्ठा adapter *adap, काष्ठा l2t_entry *e, पूर्णांक sync)
अणु
	काष्ठा l2t_data *d = adap->l2t;
	अचिन्हित पूर्णांक l2t_idx = e->idx + d->l2t_start;
	काष्ठा sk_buff *skb;
	काष्ठा cpl_l2t_ग_लिखो_req *req;

	skb = alloc_skb(माप(*req), GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	req = __skb_put(skb, माप(*req));
	INIT_TP_WR(req, 0);

	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_L2T_WRITE_REQ,
					l2t_idx | (sync ? SYNC_WR_F : 0) |
					TID_QID_V(adap->sge.fw_evtq.असल_id)));
	req->params = htons(L2T_W_PORT_V(e->lport) | L2T_W_NOREPLY_V(!sync));
	req->l2t_idx = htons(l2t_idx);
	req->vlan = htons(e->vlan);
	अगर (e->neigh && !(e->neigh->dev->flags & IFF_LOOPBACK))
		स_नकल(e->dmac, e->neigh->ha, माप(e->dmac));
	स_नकल(req->dst_mac, e->dmac, माप(req->dst_mac));

	t4_mgmt_tx(adap, skb);

	अगर (sync && e->state != L2T_STATE_SWITCHING)
		e->state = L2T_STATE_SYNC_WRITE;
	वापस 0;
पूर्ण

/*
 * Send packets रुकोing in an L2T entry's ARP queue.  Must be called with the
 * entry locked.
 */
अटल व्योम send_pending(काष्ठा adapter *adap, काष्ठा l2t_entry *e)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(&e->arpq)) != शून्य)
		t4_ofld_send(adap, skb);
पूर्ण

/*
 * Process a CPL_L2T_WRITE_RPL.  Wake up the ARP queue अगर it completes a
 * synchronous L2T_WRITE.  Note that the TID in the reply is really the L2T
 * index it refers to.
 */
व्योम करो_l2t_ग_लिखो_rpl(काष्ठा adapter *adap, स्थिर काष्ठा cpl_l2t_ग_लिखो_rpl *rpl)
अणु
	काष्ठा l2t_data *d = adap->l2t;
	अचिन्हित पूर्णांक tid = GET_TID(rpl);
	अचिन्हित पूर्णांक l2t_idx = tid % L2T_SIZE;

	अगर (unlikely(rpl->status != CPL_ERR_NONE)) अणु
		dev_err(adap->pdev_dev,
			"Unexpected L2T_WRITE_RPL status %u for entry %u\n",
			rpl->status, l2t_idx);
		वापस;
	पूर्ण

	अगर (tid & SYNC_WR_F) अणु
		काष्ठा l2t_entry *e = &d->l2tab[l2t_idx - d->l2t_start];

		spin_lock(&e->lock);
		अगर (e->state != L2T_STATE_SWITCHING) अणु
			send_pending(adap, e);
			e->state = (e->neigh->nud_state & NUD_STALE) ?
					L2T_STATE_STALE : L2T_STATE_VALID;
		पूर्ण
		spin_unlock(&e->lock);
	पूर्ण
पूर्ण

/*
 * Add a packet to an L2T entry's queue of packets aरुकोing resolution.
 * Must be called with the entry's lock held.
 */
अटल अंतरभूत व्योम arpq_enqueue(काष्ठा l2t_entry *e, काष्ठा sk_buff *skb)
अणु
	__skb_queue_tail(&e->arpq, skb);
पूर्ण

पूर्णांक cxgb4_l2t_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		   काष्ठा l2t_entry *e)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

again:
	चयन (e->state) अणु
	हाल L2T_STATE_STALE:     /* entry is stale, kick off revalidation */
		neigh_event_send(e->neigh, शून्य);
		spin_lock_bh(&e->lock);
		अगर (e->state == L2T_STATE_STALE)
			e->state = L2T_STATE_VALID;
		spin_unlock_bh(&e->lock);
		fallthrough;
	हाल L2T_STATE_VALID:     /* fast-path, send the packet on */
		वापस t4_ofld_send(adap, skb);
	हाल L2T_STATE_RESOLVING:
	हाल L2T_STATE_SYNC_WRITE:
		spin_lock_bh(&e->lock);
		अगर (e->state != L2T_STATE_SYNC_WRITE &&
		    e->state != L2T_STATE_RESOLVING) अणु
			spin_unlock_bh(&e->lock);
			जाओ again;
		पूर्ण
		arpq_enqueue(e, skb);
		spin_unlock_bh(&e->lock);

		अगर (e->state == L2T_STATE_RESOLVING &&
		    !neigh_event_send(e->neigh, शून्य)) अणु
			spin_lock_bh(&e->lock);
			अगर (e->state == L2T_STATE_RESOLVING &&
			    !skb_queue_empty(&e->arpq))
				ग_लिखो_l2e(adap, e, 1);
			spin_unlock_bh(&e->lock);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cxgb4_l2t_send);

/*
 * Allocate a मुक्त L2T entry.  Must be called with l2t_data.lock held.
 */
अटल काष्ठा l2t_entry *alloc_l2e(काष्ठा l2t_data *d)
अणु
	काष्ठा l2t_entry *end, *e, **p;

	अगर (!atomic_पढ़ो(&d->nमुक्त))
		वापस शून्य;

	/* there's definitely a मुक्त entry */
	क्रम (e = d->rover, end = &d->l2tab[d->l2t_size]; e != end; ++e)
		अगर (atomic_पढ़ो(&e->refcnt) == 0)
			जाओ found;

	क्रम (e = d->l2tab; atomic_पढ़ो(&e->refcnt); ++e)
		;
found:
	d->rover = e + 1;
	atomic_dec(&d->nमुक्त);

	/*
	 * The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to हटाओ it.
	 */
	अगर (e->state < L2T_STATE_SWITCHING)
		क्रम (p = &d->l2tab[e->hash].first; *p; p = &(*p)->next)
			अगर (*p == e) अणु
				*p = e->next;
				e->next = शून्य;
				अवरोध;
			पूर्ण

	e->state = L2T_STATE_UNUSED;
	वापस e;
पूर्ण

अटल काष्ठा l2t_entry *find_or_alloc_l2e(काष्ठा l2t_data *d, u16 vlan,
					   u8 port, u8 *dmac)
अणु
	काष्ठा l2t_entry *end, *e, **p;
	काष्ठा l2t_entry *first_मुक्त = शून्य;

	क्रम (e = &d->l2tab[0], end = &d->l2tab[d->l2t_size]; e != end; ++e) अणु
		अगर (atomic_पढ़ो(&e->refcnt) == 0) अणु
			अगर (!first_मुक्त)
				first_मुक्त = e;
		पूर्ण अन्यथा अणु
			अगर (e->state == L2T_STATE_SWITCHING) अणु
				अगर (ether_addr_equal(e->dmac, dmac) &&
				    (e->vlan == vlan) && (e->lport == port))
					जाओ exists;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (first_मुक्त) अणु
		e = first_मुक्त;
		जाओ found;
	पूर्ण

	वापस शून्य;

found:
	/* The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to हटाओ it.
	 */
	अगर (e->state < L2T_STATE_SWITCHING)
		क्रम (p = &d->l2tab[e->hash].first; *p; p = &(*p)->next)
			अगर (*p == e) अणु
				*p = e->next;
				e->next = शून्य;
				अवरोध;
			पूर्ण
	e->state = L2T_STATE_UNUSED;

exists:
	वापस e;
पूर्ण

/* Called when an L2T entry has no more users.  The entry is left in the hash
 * table since it is likely to be reused but we also bump nमुक्त to indicate
 * that the entry can be पुनः_स्मृतिated क्रम a dअगरferent neighbor.  We also drop
 * the existing neighbor reference in हाल the neighbor is going away and is
 * रुकोing on our reference.
 *
 * Because entries can be पुनः_स्मृतिated to other neighbors once their ref count
 * drops to 0 we need to take the entry's lock to aव्योम races with a new
 * incarnation.
 */
अटल व्योम _t4_l2e_मुक्त(काष्ठा l2t_entry *e)
अणु
	काष्ठा l2t_data *d;

	अगर (atomic_पढ़ो(&e->refcnt) == 0) अणु  /* hasn't been recycled */
		अगर (e->neigh) अणु
			neigh_release(e->neigh);
			e->neigh = शून्य;
		पूर्ण
		__skb_queue_purge(&e->arpq);
	पूर्ण

	d = container_of(e, काष्ठा l2t_data, l2tab[e->idx]);
	atomic_inc(&d->nमुक्त);
पूर्ण

/* Locked version of _t4_l2e_मुक्त */
अटल व्योम t4_l2e_मुक्त(काष्ठा l2t_entry *e)
अणु
	काष्ठा l2t_data *d;

	spin_lock_bh(&e->lock);
	अगर (atomic_पढ़ो(&e->refcnt) == 0) अणु  /* hasn't been recycled */
		अगर (e->neigh) अणु
			neigh_release(e->neigh);
			e->neigh = शून्य;
		पूर्ण
		__skb_queue_purge(&e->arpq);
	पूर्ण
	spin_unlock_bh(&e->lock);

	d = container_of(e, काष्ठा l2t_data, l2tab[e->idx]);
	atomic_inc(&d->nमुक्त);
पूर्ण

व्योम cxgb4_l2t_release(काष्ठा l2t_entry *e)
अणु
	अगर (atomic_dec_and_test(&e->refcnt))
		t4_l2e_मुक्त(e);
पूर्ण
EXPORT_SYMBOL(cxgb4_l2t_release);

/*
 * Update an L2T entry that was previously used क्रम the same next hop as neigh.
 * Must be called with softirqs disabled.
 */
अटल व्योम reuse_entry(काष्ठा l2t_entry *e, काष्ठा neighbour *neigh)
अणु
	अचिन्हित पूर्णांक nud_state;

	spin_lock(&e->lock);                /* aव्योम race with t4_l2t_मुक्त */
	अगर (neigh != e->neigh)
		neigh_replace(e, neigh);
	nud_state = neigh->nud_state;
	अगर (स_भेद(e->dmac, neigh->ha, माप(e->dmac)) ||
	    !(nud_state & NUD_VALID))
		e->state = L2T_STATE_RESOLVING;
	अन्यथा अगर (nud_state & NUD_CONNECTED)
		e->state = L2T_STATE_VALID;
	अन्यथा
		e->state = L2T_STATE_STALE;
	spin_unlock(&e->lock);
पूर्ण

काष्ठा l2t_entry *cxgb4_l2t_get(काष्ठा l2t_data *d, काष्ठा neighbour *neigh,
				स्थिर काष्ठा net_device *physdev,
				अचिन्हित पूर्णांक priority)
अणु
	u8 lport;
	u16 vlan;
	काष्ठा l2t_entry *e;
	अचिन्हित पूर्णांक addr_len = neigh->tbl->key_len;
	u32 *addr = (u32 *)neigh->primary_key;
	पूर्णांक अगरidx = neigh->dev->अगरindex;
	पूर्णांक hash = addr_hash(d, addr, addr_len, अगरidx);

	अगर (neigh->dev->flags & IFF_LOOPBACK)
		lport = netdev2pinfo(physdev)->tx_chan + 4;
	अन्यथा
		lport = netdev2pinfo(physdev)->lport;

	अगर (is_vlan_dev(neigh->dev)) अणु
		vlan = vlan_dev_vlan_id(neigh->dev);
		vlan |= vlan_dev_get_egress_qos_mask(neigh->dev, priority);
	पूर्ण अन्यथा अणु
		vlan = VLAN_NONE;
	पूर्ण

	ग_लिखो_lock_bh(&d->lock);
	क्रम (e = d->l2tab[hash].first; e; e = e->next)
		अगर (!addreq(e, addr) && e->अगरindex == अगरidx &&
		    e->vlan == vlan && e->lport == lport) अणु
			l2t_hold(d, e);
			अगर (atomic_पढ़ो(&e->refcnt) == 1)
				reuse_entry(e, neigh);
			जाओ करोne;
		पूर्ण

	/* Need to allocate a new entry */
	e = alloc_l2e(d);
	अगर (e) अणु
		spin_lock(&e->lock);          /* aव्योम race with t4_l2t_मुक्त */
		e->state = L2T_STATE_RESOLVING;
		अगर (neigh->dev->flags & IFF_LOOPBACK)
			स_नकल(e->dmac, physdev->dev_addr, माप(e->dmac));
		स_नकल(e->addr, addr, addr_len);
		e->अगरindex = अगरidx;
		e->hash = hash;
		e->lport = lport;
		e->v6 = addr_len == 16;
		atomic_set(&e->refcnt, 1);
		neigh_replace(e, neigh);
		e->vlan = vlan;
		e->next = d->l2tab[hash].first;
		d->l2tab[hash].first = e;
		spin_unlock(&e->lock);
	पूर्ण
करोne:
	ग_लिखो_unlock_bh(&d->lock);
	वापस e;
पूर्ण
EXPORT_SYMBOL(cxgb4_l2t_get);

u64 cxgb4_select_ntuple(काष्ठा net_device *dev,
			स्थिर काष्ठा l2t_entry *l2t)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा tp_params *tp = &adap->params.tp;
	u64 ntuple = 0;

	/* Initialize each of the fields which we care about which are present
	 * in the Compressed Filter Tuple.
	 */
	अगर (tp->vlan_shअगरt >= 0 && l2t->vlan != VLAN_NONE)
		ntuple |= (u64)(FT_VLAN_VLD_F | l2t->vlan) << tp->vlan_shअगरt;

	अगर (tp->port_shअगरt >= 0)
		ntuple |= (u64)l2t->lport << tp->port_shअगरt;

	अगर (tp->protocol_shअगरt >= 0)
		ntuple |= (u64)IPPROTO_TCP << tp->protocol_shअगरt;

	अगर (tp->vnic_shअगरt >= 0 && (tp->ingress_config & VNIC_F)) अणु
		काष्ठा port_info *pi = (काष्ठा port_info *)netdev_priv(dev);

		ntuple |= (u64)(FT_VNID_ID_VF_V(pi->vin) |
				FT_VNID_ID_PF_V(adap->pf) |
				FT_VNID_ID_VLD_V(pi->vivld)) << tp->vnic_shअगरt;
	पूर्ण

	वापस ntuple;
पूर्ण
EXPORT_SYMBOL(cxgb4_select_ntuple);

/*
 * Called when the host's neighbor layer makes a change to some entry that is
 * loaded पूर्णांकo the HW L2 table.
 */
व्योम t4_l2t_update(काष्ठा adapter *adap, काष्ठा neighbour *neigh)
अणु
	अचिन्हित पूर्णांक addr_len = neigh->tbl->key_len;
	u32 *addr = (u32 *) neigh->primary_key;
	पूर्णांक hash, अगरidx = neigh->dev->अगरindex;
	काष्ठा sk_buff_head *arpq = शून्य;
	काष्ठा l2t_data *d = adap->l2t;
	काष्ठा l2t_entry *e;

	hash = addr_hash(d, addr, addr_len, अगरidx);
	पढ़ो_lock_bh(&d->lock);
	क्रम (e = d->l2tab[hash].first; e; e = e->next)
		अगर (!addreq(e, addr) && e->अगरindex == अगरidx) अणु
			spin_lock(&e->lock);
			अगर (atomic_पढ़ो(&e->refcnt))
				जाओ found;
			spin_unlock(&e->lock);
			अवरोध;
		पूर्ण
	पढ़ो_unlock_bh(&d->lock);
	वापस;

 found:
	पढ़ो_unlock(&d->lock);

	अगर (neigh != e->neigh)
		neigh_replace(e, neigh);

	अगर (e->state == L2T_STATE_RESOLVING) अणु
		अगर (neigh->nud_state & NUD_FAILED) अणु
			arpq = &e->arpq;
		पूर्ण अन्यथा अगर ((neigh->nud_state & (NUD_CONNECTED | NUD_STALE)) &&
			   !skb_queue_empty(&e->arpq)) अणु
			ग_लिखो_l2e(adap, e, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		e->state = neigh->nud_state & NUD_CONNECTED ?
			L2T_STATE_VALID : L2T_STATE_STALE;
		अगर (स_भेद(e->dmac, neigh->ha, माप(e->dmac)))
			ग_लिखो_l2e(adap, e, 0);
	पूर्ण

	अगर (arpq) अणु
		काष्ठा sk_buff *skb;

		/* Called when address resolution fails क्रम an L2T
		 * entry to handle packets on the arpq head. If a
		 * packet specअगरies a failure handler it is invoked,
		 * otherwise the packet is sent to the device.
		 */
		जबतक ((skb = __skb_dequeue(&e->arpq)) != शून्य) अणु
			स्थिर काष्ठा l2t_skb_cb *cb = L2T_SKB_CB(skb);

			spin_unlock(&e->lock);
			अगर (cb->arp_err_handler)
				cb->arp_err_handler(cb->handle, skb);
			अन्यथा
				t4_ofld_send(adap, skb);
			spin_lock(&e->lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&e->lock);
पूर्ण

/* Allocate an L2T entry क्रम use by a चयनing rule.  Such need to be
 * explicitly मुक्तd and जबतक busy they are not on any hash chain, so normal
 * address resolution updates करो not see them.
 */
काष्ठा l2t_entry *t4_l2t_alloc_चयनing(काष्ठा adapter *adap, u16 vlan,
					 u8 port, u8 *eth_addr)
अणु
	काष्ठा l2t_data *d = adap->l2t;
	काष्ठा l2t_entry *e;
	पूर्णांक ret;

	ग_लिखो_lock_bh(&d->lock);
	e = find_or_alloc_l2e(d, vlan, port, eth_addr);
	अगर (e) अणु
		spin_lock(&e->lock);          /* aव्योम race with t4_l2t_मुक्त */
		अगर (!atomic_पढ़ो(&e->refcnt)) अणु
			e->state = L2T_STATE_SWITCHING;
			e->vlan = vlan;
			e->lport = port;
			ether_addr_copy(e->dmac, eth_addr);
			atomic_set(&e->refcnt, 1);
			ret = ग_लिखो_l2e(adap, e, 0);
			अगर (ret < 0) अणु
				_t4_l2e_मुक्त(e);
				spin_unlock(&e->lock);
				ग_लिखो_unlock_bh(&d->lock);
				वापस शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			atomic_inc(&e->refcnt);
		पूर्ण

		spin_unlock(&e->lock);
	पूर्ण
	ग_लिखो_unlock_bh(&d->lock);
	वापस e;
पूर्ण

/**
 * cxgb4_l2t_alloc_चयनing - Allocates an L2T entry क्रम चयन filters
 * @dev: net_device poपूर्णांकer
 * @vlan: VLAN Id
 * @port: Associated port
 * @dmac: Destination MAC address to add to L2T
 * Returns poपूर्णांकer to the allocated l2t entry
 *
 * Allocates an L2T entry क्रम use by चयनing rule of a filter
 */
काष्ठा l2t_entry *cxgb4_l2t_alloc_चयनing(काष्ठा net_device *dev, u16 vlan,
					    u8 port, u8 *dmac)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	वापस t4_l2t_alloc_चयनing(adap, vlan, port, dmac);
पूर्ण
EXPORT_SYMBOL(cxgb4_l2t_alloc_चयनing);

काष्ठा l2t_data *t4_init_l2t(अचिन्हित पूर्णांक l2t_start, अचिन्हित पूर्णांक l2t_end)
अणु
	अचिन्हित पूर्णांक l2t_size;
	पूर्णांक i;
	काष्ठा l2t_data *d;

	अगर (l2t_start >= l2t_end || l2t_end >= L2T_SIZE)
		वापस शून्य;
	l2t_size = l2t_end - l2t_start + 1;
	अगर (l2t_size < L2T_MIN_HASH_BUCKETS)
		वापस शून्य;

	d = kvzalloc(काष्ठा_size(d, l2tab, l2t_size), GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	d->l2t_start = l2t_start;
	d->l2t_size = l2t_size;

	d->rover = d->l2tab;
	atomic_set(&d->nमुक्त, l2t_size);
	rwlock_init(&d->lock);

	क्रम (i = 0; i < d->l2t_size; ++i) अणु
		d->l2tab[i].idx = i;
		d->l2tab[i].state = L2T_STATE_UNUSED;
		spin_lock_init(&d->l2tab[i].lock);
		atomic_set(&d->l2tab[i].refcnt, 0);
		skb_queue_head_init(&d->l2tab[i].arpq);
	पूर्ण
	वापस d;
पूर्ण

अटल अंतरभूत व्योम *l2t_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा l2t_data *d = seq->निजी;

	वापस pos >= d->l2t_size ? शून्य : &d->l2tab[pos];
पूर्ण

अटल व्योम *l2t_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? l2t_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *l2t_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	v = l2t_get_idx(seq, *pos);
	++(*pos);
	वापस v;
पूर्ण

अटल व्योम l2t_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल अक्षर l2e_state(स्थिर काष्ठा l2t_entry *e)
अणु
	चयन (e->state) अणु
	हाल L2T_STATE_VALID: वापस 'V';
	हाल L2T_STATE_STALE: वापस 'S';
	हाल L2T_STATE_SYNC_WRITE: वापस 'W';
	हाल L2T_STATE_RESOLVING:
		वापस skb_queue_empty(&e->arpq) ? 'R' : 'A';
	हाल L2T_STATE_SWITCHING: वापस 'X';
	शेष:
		वापस 'U';
	पूर्ण
पूर्ण

bool cxgb4_check_l2t_valid(काष्ठा l2t_entry *e)
अणु
	bool valid;

	spin_lock(&e->lock);
	valid = (e->state == L2T_STATE_VALID);
	spin_unlock(&e->lock);
	वापस valid;
पूर्ण
EXPORT_SYMBOL(cxgb4_check_l2t_valid);

अटल पूर्णांक l2t_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, " Idx IP address                "
			 "Ethernet address  VLAN/P LP State Users Port\n");
	अन्यथा अणु
		अक्षर ip[60];
		काष्ठा l2t_data *d = seq->निजी;
		काष्ठा l2t_entry *e = v;

		spin_lock_bh(&e->lock);
		अगर (e->state == L2T_STATE_SWITCHING)
			ip[0] = '\0';
		अन्यथा
			प्र_लिखो(ip, e->v6 ? "%pI6c" : "%pI4", e->addr);
		seq_म_लिखो(seq, "%4u %-25s %17pM %4d %u %2u   %c   %5u %s\n",
			   e->idx + d->l2t_start, ip, e->dmac,
			   e->vlan & VLAN_VID_MASK, vlan_prio(e), e->lport,
			   l2e_state(e), atomic_पढ़ो(&e->refcnt),
			   e->neigh ? e->neigh->dev->name : "");
		spin_unlock_bh(&e->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations l2t_seq_ops = अणु
	.start = l2t_seq_start,
	.next = l2t_seq_next,
	.stop = l2t_seq_stop,
	.show = l2t_seq_show
पूर्ण;

अटल पूर्णांक l2t_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc = seq_खोलो(file, &l2t_seq_ops);

	अगर (!rc) अणु
		काष्ठा adapter *adap = inode->i_निजी;
		काष्ठा seq_file *seq = file->निजी_data;

		seq->निजी = adap->l2t;
	पूर्ण
	वापस rc;
पूर्ण

स्थिर काष्ठा file_operations t4_l2t_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = l2t_seq_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;
