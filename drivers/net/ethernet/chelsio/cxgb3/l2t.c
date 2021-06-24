<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
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
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/neighbour.h>
#समावेश "common.h"
#समावेश "t3cdev.h"
#समावेश "cxgb3_defs.h"
#समावेश "l2t.h"
#समावेश "t3_cpl.h"
#समावेश "firmware_exports.h"

#घोषणा VLAN_NONE 0xfff

/*
 * Module locking notes:  There is a RW lock protecting the L2 table as a
 * whole plus a spinlock per L2T entry.  Entry lookups and allocations happen
 * under the protection of the table lock, inभागidual entry changes happen
 * जबतक holding that entry's spinlock.  The table lock nests outside the
 * entry locks.  Allocations of new entries take the table lock as ग_लिखोrs so
 * no other lookups can happen जबतक allocating new entries.  Entry updates
 * take the table lock as पढ़ोers so multiple entries can be updated in
 * parallel.  An L2T entry can be dropped by decrementing its reference count
 * and thereक्रमe can happen in parallel with entry allocation but no entry
 * can change state or increment its ref count during allocation as both of
 * these perक्रमm lookups.
 */

अटल अंतरभूत अचिन्हित पूर्णांक vlan_prio(स्थिर काष्ठा l2t_entry *e)
अणु
	वापस e->vlan >> 13;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक arp_hash(u32 key, पूर्णांक अगरindex,
				    स्थिर काष्ठा l2t_data *d)
अणु
	वापस jhash_2words(key, अगरindex, 0) & (d->nentries - 1);
पूर्ण

अटल अंतरभूत व्योम neigh_replace(काष्ठा l2t_entry *e, काष्ठा neighbour *n)
अणु
	neigh_hold(n);
	अगर (e->neigh)
		neigh_release(e->neigh);
	e->neigh = n;
पूर्ण

/*
 * Set up an L2T entry and send any packets रुकोing in the arp queue.  The
 * supplied skb is used क्रम the CPL_L2T_WRITE_REQ.  Must be called with the
 * entry locked.
 */
अटल पूर्णांक setup_l2e_send_pending(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb,
				  काष्ठा l2t_entry *e)
अणु
	काष्ठा cpl_l2t_ग_लिखो_req *req;
	काष्ठा sk_buff *पंचांगp;

	अगर (!skb) अणु
		skb = alloc_skb(माप(*req), GFP_ATOMIC);
		अगर (!skb)
			वापस -ENOMEM;
	पूर्ण

	req = __skb_put(skb, माप(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_L2T_WRITE_REQ, e->idx));
	req->params = htonl(V_L2T_W_IDX(e->idx) | V_L2T_W_IFF(e->smt_idx) |
			    V_L2T_W_VLAN(e->vlan & VLAN_VID_MASK) |
			    V_L2T_W_PRIO(vlan_prio(e)));
	स_नकल(e->dmac, e->neigh->ha, माप(e->dmac));
	स_नकल(req->dst_mac, e->dmac, माप(req->dst_mac));
	skb->priority = CPL_PRIORITY_CONTROL;
	cxgb3_ofld_send(dev, skb);

	skb_queue_walk_safe(&e->arpq, skb, पंचांगp) अणु
		__skb_unlink(skb, &e->arpq);
		cxgb3_ofld_send(dev, skb);
	पूर्ण
	e->state = L2T_STATE_VALID;

	वापस 0;
पूर्ण

/*
 * Add a packet to the an L2T entry's queue of packets aरुकोing resolution.
 * Must be called with the entry's lock held.
 */
अटल अंतरभूत व्योम arpq_enqueue(काष्ठा l2t_entry *e, काष्ठा sk_buff *skb)
अणु
	__skb_queue_tail(&e->arpq, skb);
पूर्ण

पूर्णांक t3_l2t_send_slow(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb,
		     काष्ठा l2t_entry *e)
अणु
again:
	चयन (e->state) अणु
	हाल L2T_STATE_STALE:	/* entry is stale, kick off revalidation */
		neigh_event_send(e->neigh, शून्य);
		spin_lock_bh(&e->lock);
		अगर (e->state == L2T_STATE_STALE)
			e->state = L2T_STATE_VALID;
		spin_unlock_bh(&e->lock);
		fallthrough;
	हाल L2T_STATE_VALID:	/* fast-path, send the packet on */
		वापस cxgb3_ofld_send(dev, skb);
	हाल L2T_STATE_RESOLVING:
		spin_lock_bh(&e->lock);
		अगर (e->state != L2T_STATE_RESOLVING) अणु
			/* ARP alपढ़ोy completed */
			spin_unlock_bh(&e->lock);
			जाओ again;
		पूर्ण
		arpq_enqueue(e, skb);
		spin_unlock_bh(&e->lock);

		/*
		 * Only the first packet added to the arpq should kick off
		 * resolution.  However, because the alloc_skb below can fail,
		 * we allow each packet added to the arpq to retry resolution
		 * as a way of recovering from transient memory exhaustion.
		 * A better way would be to use a work request to retry L2T
		 * entries when there's no memory.
		 */
		अगर (!neigh_event_send(e->neigh, शून्य)) अणु
			skb = alloc_skb(माप(काष्ठा cpl_l2t_ग_लिखो_req),
					GFP_ATOMIC);
			अगर (!skb)
				अवरोध;

			spin_lock_bh(&e->lock);
			अगर (!skb_queue_empty(&e->arpq))
				setup_l2e_send_pending(dev, skb, e);
			अन्यथा	/* we lost the race */
				__kमुक्त_skb(skb);
			spin_unlock_bh(&e->lock);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(t3_l2t_send_slow);

व्योम t3_l2t_send_event(काष्ठा t3cdev *dev, काष्ठा l2t_entry *e)
अणु
again:
	चयन (e->state) अणु
	हाल L2T_STATE_STALE:	/* entry is stale, kick off revalidation */
		neigh_event_send(e->neigh, शून्य);
		spin_lock_bh(&e->lock);
		अगर (e->state == L2T_STATE_STALE) अणु
			e->state = L2T_STATE_VALID;
		पूर्ण
		spin_unlock_bh(&e->lock);
		वापस;
	हाल L2T_STATE_VALID:	/* fast-path, send the packet on */
		वापस;
	हाल L2T_STATE_RESOLVING:
		spin_lock_bh(&e->lock);
		अगर (e->state != L2T_STATE_RESOLVING) अणु
			/* ARP alपढ़ोy completed */
			spin_unlock_bh(&e->lock);
			जाओ again;
		पूर्ण
		spin_unlock_bh(&e->lock);

		/*
		 * Only the first packet added to the arpq should kick off
		 * resolution.  However, because the alloc_skb below can fail,
		 * we allow each packet added to the arpq to retry resolution
		 * as a way of recovering from transient memory exhaustion.
		 * A better way would be to use a work request to retry L2T
		 * entries when there's no memory.
		 */
		neigh_event_send(e->neigh, शून्य);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(t3_l2t_send_event);

/*
 * Allocate a मुक्त L2T entry.  Must be called with l2t_data.lock held.
 */
अटल काष्ठा l2t_entry *alloc_l2e(काष्ठा l2t_data *d)
अणु
	काष्ठा l2t_entry *end, *e, **p;

	अगर (!atomic_पढ़ो(&d->nमुक्त))
		वापस शून्य;

	/* there's definitely a मुक्त entry */
	क्रम (e = d->rover, end = &d->l2tab[d->nentries]; e != end; ++e)
		अगर (atomic_पढ़ो(&e->refcnt) == 0)
			जाओ found;

	क्रम (e = &d->l2tab[1]; atomic_पढ़ो(&e->refcnt); ++e) ;
found:
	d->rover = e + 1;
	atomic_dec(&d->nमुक्त);

	/*
	 * The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to हटाओ it.
	 */
	अगर (e->state != L2T_STATE_UNUSED) अणु
		पूर्णांक hash = arp_hash(e->addr, e->अगरindex, d);

		क्रम (p = &d->l2tab[hash].first; *p; p = &(*p)->next)
			अगर (*p == e) अणु
				*p = e->next;
				अवरोध;
			पूर्ण
		e->state = L2T_STATE_UNUSED;
	पूर्ण
	वापस e;
पूर्ण

/*
 * Called when an L2T entry has no more users.  The entry is left in the hash
 * table since it is likely to be reused but we also bump nमुक्त to indicate
 * that the entry can be पुनः_स्मृतिated क्रम a dअगरferent neighbor.  We also drop
 * the existing neighbor reference in हाल the neighbor is going away and is
 * रुकोing on our reference.
 *
 * Because entries can be पुनः_स्मृतिated to other neighbors once their ref count
 * drops to 0 we need to take the entry's lock to aव्योम races with a new
 * incarnation.
 */
व्योम t3_l2e_मुक्त(काष्ठा l2t_data *d, काष्ठा l2t_entry *e)
अणु
	spin_lock_bh(&e->lock);
	अगर (atomic_पढ़ो(&e->refcnt) == 0) अणु	/* hasn't been recycled */
		अगर (e->neigh) अणु
			neigh_release(e->neigh);
			e->neigh = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&e->lock);
	atomic_inc(&d->nमुक्त);
पूर्ण

EXPORT_SYMBOL(t3_l2e_मुक्त);

/*
 * Update an L2T entry that was previously used क्रम the same next hop as neigh.
 * Must be called with softirqs disabled.
 */
अटल अंतरभूत व्योम reuse_entry(काष्ठा l2t_entry *e, काष्ठा neighbour *neigh)
अणु
	अचिन्हित पूर्णांक nud_state;

	spin_lock(&e->lock);	/* aव्योम race with t3_l2t_मुक्त */

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

काष्ठा l2t_entry *t3_l2t_get(काष्ठा t3cdev *cdev, काष्ठा dst_entry *dst,
			     काष्ठा net_device *dev, स्थिर व्योम *daddr)
अणु
	काष्ठा l2t_entry *e = शून्य;
	काष्ठा neighbour *neigh;
	काष्ठा port_info *p;
	काष्ठा l2t_data *d;
	पूर्णांक hash;
	u32 addr;
	पूर्णांक अगरidx;
	पूर्णांक smt_idx;

	rcu_पढ़ो_lock();
	neigh = dst_neigh_lookup(dst, daddr);
	अगर (!neigh)
		जाओ करोne_rcu;

	addr = *(u32 *) neigh->primary_key;
	अगरidx = neigh->dev->अगरindex;

	अगर (!dev)
		dev = neigh->dev;
	p = netdev_priv(dev);
	smt_idx = p->port_id;

	d = L2DATA(cdev);
	अगर (!d)
		जाओ करोne_rcu;

	hash = arp_hash(addr, अगरidx, d);

	ग_लिखो_lock_bh(&d->lock);
	क्रम (e = d->l2tab[hash].first; e; e = e->next)
		अगर (e->addr == addr && e->अगरindex == अगरidx &&
		    e->smt_idx == smt_idx) अणु
			l2t_hold(d, e);
			अगर (atomic_पढ़ो(&e->refcnt) == 1)
				reuse_entry(e, neigh);
			जाओ करोne_unlock;
		पूर्ण

	/* Need to allocate a new entry */
	e = alloc_l2e(d);
	अगर (e) अणु
		spin_lock(&e->lock);	/* aव्योम race with t3_l2t_मुक्त */
		e->next = d->l2tab[hash].first;
		d->l2tab[hash].first = e;
		e->state = L2T_STATE_RESOLVING;
		e->addr = addr;
		e->अगरindex = अगरidx;
		e->smt_idx = smt_idx;
		atomic_set(&e->refcnt, 1);
		neigh_replace(e, neigh);
		अगर (is_vlan_dev(neigh->dev))
			e->vlan = vlan_dev_vlan_id(neigh->dev);
		अन्यथा
			e->vlan = VLAN_NONE;
		spin_unlock(&e->lock);
	पूर्ण
करोne_unlock:
	ग_लिखो_unlock_bh(&d->lock);
करोne_rcu:
	अगर (neigh)
		neigh_release(neigh);
	rcu_पढ़ो_unlock();
	वापस e;
पूर्ण

EXPORT_SYMBOL(t3_l2t_get);

/*
 * Called when address resolution fails क्रम an L2T entry to handle packets
 * on the arpq head.  If a packet specअगरies a failure handler it is invoked,
 * otherwise the packets is sent to the offload device.
 *
 * XXX: maybe we should abanकरोn the latter behavior and just require a failure
 * handler.
 */
अटल व्योम handle_failed_resolution(काष्ठा t3cdev *dev, काष्ठा sk_buff_head *arpq)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(arpq, skb, पंचांगp) अणु
		काष्ठा l2t_skb_cb *cb = L2T_SKB_CB(skb);

		__skb_unlink(skb, arpq);
		अगर (cb->arp_failure_handler)
			cb->arp_failure_handler(dev, skb);
		अन्यथा
			cxgb3_ofld_send(dev, skb);
	पूर्ण
पूर्ण

/*
 * Called when the host's ARP layer makes a change to some entry that is
 * loaded पूर्णांकo the HW L2 table.
 */
व्योम t3_l2t_update(काष्ठा t3cdev *dev, काष्ठा neighbour *neigh)
अणु
	काष्ठा sk_buff_head arpq;
	काष्ठा l2t_entry *e;
	काष्ठा l2t_data *d = L2DATA(dev);
	u32 addr = *(u32 *) neigh->primary_key;
	पूर्णांक अगरidx = neigh->dev->अगरindex;
	पूर्णांक hash = arp_hash(addr, अगरidx, d);

	पढ़ो_lock_bh(&d->lock);
	क्रम (e = d->l2tab[hash].first; e; e = e->next)
		अगर (e->addr == addr && e->अगरindex == अगरidx) अणु
			spin_lock(&e->lock);
			जाओ found;
		पूर्ण
	पढ़ो_unlock_bh(&d->lock);
	वापस;

found:
	__skb_queue_head_init(&arpq);

	पढ़ो_unlock(&d->lock);
	अगर (atomic_पढ़ो(&e->refcnt)) अणु
		अगर (neigh != e->neigh)
			neigh_replace(e, neigh);

		अगर (e->state == L2T_STATE_RESOLVING) अणु
			अगर (neigh->nud_state & NUD_FAILED) अणु
				skb_queue_splice_init(&e->arpq, &arpq);
			पूर्ण अन्यथा अगर (neigh->nud_state & (NUD_CONNECTED|NUD_STALE))
				setup_l2e_send_pending(dev, शून्य, e);
		पूर्ण अन्यथा अणु
			e->state = neigh->nud_state & NUD_CONNECTED ?
			    L2T_STATE_VALID : L2T_STATE_STALE;
			अगर (!ether_addr_equal(e->dmac, neigh->ha))
				setup_l2e_send_pending(dev, शून्य, e);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&e->lock);

	अगर (!skb_queue_empty(&arpq))
		handle_failed_resolution(dev, &arpq);
पूर्ण

काष्ठा l2t_data *t3_init_l2t(अचिन्हित पूर्णांक l2t_capacity)
अणु
	काष्ठा l2t_data *d;
	पूर्णांक i;

	d = kvzalloc(काष्ठा_size(d, l2tab, l2t_capacity), GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	d->nentries = l2t_capacity;
	d->rover = &d->l2tab[1];	/* entry 0 is not used */
	atomic_set(&d->nमुक्त, l2t_capacity - 1);
	rwlock_init(&d->lock);

	क्रम (i = 0; i < l2t_capacity; ++i) अणु
		d->l2tab[i].idx = i;
		d->l2tab[i].state = L2T_STATE_UNUSED;
		__skb_queue_head_init(&d->l2tab[i].arpq);
		spin_lock_init(&d->l2tab[i].lock);
		atomic_set(&d->l2tab[i].refcnt, 0);
	पूर्ण
	वापस d;
पूर्ण
