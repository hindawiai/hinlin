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
#अगर_अघोषित _CHELSIO_L2T_H
#घोषणा _CHELSIO_L2T_H

#समावेश <linux/spinlock.h>
#समावेश "t3cdev.h"
#समावेश <linux/atomic.h>

क्रमागत अणु
	L2T_STATE_VALID,	/* entry is up to date */
	L2T_STATE_STALE,	/* entry may be used but needs revalidation */
	L2T_STATE_RESOLVING,	/* entry needs address resolution */
	L2T_STATE_UNUSED	/* entry not in use */
पूर्ण;

काष्ठा neighbour;
काष्ठा sk_buff;

/*
 * Each L2T entry plays multiple roles.  First of all, it keeps state क्रम the
 * corresponding entry of the HW L2 table and मुख्यtains a queue of offload
 * packets aरुकोing address resolution.  Second, it is a node of a hash table
 * chain, where the nodes of the chain are linked together through their next
 * poपूर्णांकer.  Finally, each node is a bucket of a hash table, poपूर्णांकing to the
 * first element in its chain through its first poपूर्णांकer.
 */
काष्ठा l2t_entry अणु
	u16 state;		/* entry state */
	u16 idx;		/* entry index */
	u32 addr;		/* dest IP address */
	पूर्णांक अगरindex;		/* neighbor's net_device's अगरindex */
	u16 smt_idx;		/* SMT index */
	u16 vlan;		/* VLAN TCI (id: bits 0-11, prio: 13-15 */
	काष्ठा neighbour *neigh;	/* associated neighbour */
	काष्ठा l2t_entry *first;	/* start of hash chain */
	काष्ठा l2t_entry *next;	/* next l2t_entry on chain */
	काष्ठा sk_buff_head arpq;	/* queue of packets aरुकोing resolution */
	spinlock_t lock;
	atomic_t refcnt;	/* entry reference count */
	u8 dmac[6];		/* neighbour's MAC address */
पूर्ण;

काष्ठा l2t_data अणु
	अचिन्हित पूर्णांक nentries;	/* number of entries */
	काष्ठा l2t_entry *rover;	/* starting poपूर्णांक क्रम next allocation */
	atomic_t nमुक्त;		/* number of मुक्त entries */
	rwlock_t lock;
	काष्ठा rcu_head rcu_head;	/* to handle rcu cleanup */
	काष्ठा l2t_entry l2tab[];
पूर्ण;

प्रकार व्योम (*arp_failure_handler_func)(काष्ठा t3cdev * dev,
					 काष्ठा sk_buff * skb);

/*
 * Callback stored in an skb to handle address resolution failure.
 */
काष्ठा l2t_skb_cb अणु
	arp_failure_handler_func arp_failure_handler;
पूर्ण;

#घोषणा L2T_SKB_CB(skb) ((काष्ठा l2t_skb_cb *)(skb)->cb)

अटल अंतरभूत व्योम set_arp_failure_handler(काष्ठा sk_buff *skb,
					   arp_failure_handler_func hnd)
अणु
	L2T_SKB_CB(skb)->arp_failure_handler = hnd;
पूर्ण

/*
 * Getting to the L2 data from an offload device.
 */
#घोषणा L2DATA(cdev) (rcu_dereference((cdev)->l2opt))

#घोषणा W_TCB_L2T_IX    0
#घोषणा S_TCB_L2T_IX    7
#घोषणा M_TCB_L2T_IX    0x7ffULL
#घोषणा V_TCB_L2T_IX(x) ((x) << S_TCB_L2T_IX)

व्योम t3_l2e_मुक्त(काष्ठा l2t_data *d, काष्ठा l2t_entry *e);
व्योम t3_l2t_update(काष्ठा t3cdev *dev, काष्ठा neighbour *neigh);
काष्ठा l2t_entry *t3_l2t_get(काष्ठा t3cdev *cdev, काष्ठा dst_entry *dst,
			     काष्ठा net_device *dev, स्थिर व्योम *daddr);
पूर्णांक t3_l2t_send_slow(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb,
		     काष्ठा l2t_entry *e);
व्योम t3_l2t_send_event(काष्ठा t3cdev *dev, काष्ठा l2t_entry *e);
काष्ठा l2t_data *t3_init_l2t(अचिन्हित पूर्णांक l2t_capacity);

पूर्णांक cxgb3_ofld_send(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb);

अटल अंतरभूत पूर्णांक l2t_send(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb,
			   काष्ठा l2t_entry *e)
अणु
	अगर (likely(e->state == L2T_STATE_VALID))
		वापस cxgb3_ofld_send(dev, skb);
	वापस t3_l2t_send_slow(dev, skb, e);
पूर्ण

अटल अंतरभूत व्योम l2t_release(काष्ठा t3cdev *t, काष्ठा l2t_entry *e)
अणु
	काष्ठा l2t_data *d;

	rcu_पढ़ो_lock();
	d = L2DATA(t);

	अगर (atomic_dec_and_test(&e->refcnt) && d)
		t3_l2e_मुक्त(d, e);

	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम l2t_hold(काष्ठा l2t_data *d, काष्ठा l2t_entry *e)
अणु
	अगर (d && atomic_add_वापस(1, &e->refcnt) == 1)	/* 0 -> 1 transition */
		atomic_dec(&d->nमुक्त);
पूर्ण

#पूर्ण_अगर
