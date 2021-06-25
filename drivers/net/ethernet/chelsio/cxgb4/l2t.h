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

#अगर_अघोषित __CXGB4_L2T_H
#घोषणा __CXGB4_L2T_H

#समावेश <linux/spinlock.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/atomic.h>

#घोषणा VLAN_NONE 0xfff

क्रमागत अणु L2T_SIZE = 4096 पूर्ण;     /* # of L2T entries */

क्रमागत अणु
	L2T_STATE_VALID,      /* entry is up to date */
	L2T_STATE_STALE,      /* entry may be used but needs revalidation */
	L2T_STATE_RESOLVING,  /* entry needs address resolution */
	L2T_STATE_SYNC_WRITE, /* synchronous ग_लिखो of entry underway */
	L2T_STATE_NOARP,      /* Netdev करोwn or हटाओd*/

	/* when state is one of the below the entry is not hashed */
	L2T_STATE_SWITCHING,  /* entry is being used by a चयनing filter */
	L2T_STATE_UNUSED      /* entry not in use */
पूर्ण;

काष्ठा adapter;
काष्ठा l2t_data;
काष्ठा neighbour;
काष्ठा net_device;
काष्ठा file_operations;
काष्ठा cpl_l2t_ग_लिखो_rpl;

/*
 * Each L2T entry plays multiple roles.  First of all, it keeps state क्रम the
 * corresponding entry of the HW L2 table and मुख्यtains a queue of offload
 * packets aरुकोing address resolution.  Second, it is a node of a hash table
 * chain, where the nodes of the chain are linked together through their next
 * poपूर्णांकer.  Finally, each node is a bucket of a hash table, poपूर्णांकing to the
 * first element in its chain through its first poपूर्णांकer.
 */
काष्ठा l2t_entry अणु
	u16 state;                  /* entry state */
	u16 idx;                    /* entry index within in-memory table */
	u32 addr[4];                /* next hop IP or IPv6 address */
	पूर्णांक अगरindex;                /* neighbor's net_device's अगरindex */
	काष्ठा neighbour *neigh;    /* associated neighbour */
	काष्ठा l2t_entry *first;    /* start of hash chain */
	काष्ठा l2t_entry *next;     /* next l2t_entry on chain */
	काष्ठा sk_buff_head arpq;   /* packet queue aरुकोing resolution */
	spinlock_t lock;
	atomic_t refcnt;            /* entry reference count */
	u16 hash;                   /* hash bucket the entry is on */
	u16 vlan;                   /* VLAN TCI (id: bits 0-11, prio: 13-15 */
	u8 v6;                      /* whether entry is क्रम IPv6 */
	u8 lport;                   /* associated offload logical पूर्णांकerface */
	u8 dmac[ETH_ALEN];          /* neighbour's MAC address */
पूर्ण;

प्रकार व्योम (*arp_err_handler_t)(व्योम *handle, काष्ठा sk_buff *skb);

/*
 * Callback stored in an skb to handle address resolution failure.
 */
काष्ठा l2t_skb_cb अणु
	व्योम *handle;
	arp_err_handler_t arp_err_handler;
पूर्ण;

#घोषणा L2T_SKB_CB(skb) ((काष्ठा l2t_skb_cb *)(skb)->cb)

अटल अंतरभूत व्योम t4_set_arp_err_handler(काष्ठा sk_buff *skb, व्योम *handle,
					  arp_err_handler_t handler)
अणु
	L2T_SKB_CB(skb)->handle = handle;
	L2T_SKB_CB(skb)->arp_err_handler = handler;
पूर्ण

व्योम cxgb4_l2t_release(काष्ठा l2t_entry *e);
पूर्णांक cxgb4_l2t_send(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		   काष्ठा l2t_entry *e);
काष्ठा l2t_entry *cxgb4_l2t_get(काष्ठा l2t_data *d, काष्ठा neighbour *neigh,
				स्थिर काष्ठा net_device *physdev,
				अचिन्हित पूर्णांक priority);
u64 cxgb4_select_ntuple(काष्ठा net_device *dev,
			स्थिर काष्ठा l2t_entry *l2t);
काष्ठा l2t_entry *cxgb4_l2t_alloc_चयनing(काष्ठा net_device *dev, u16 vlan,
					    u8 port, u8 *dmac);
व्योम t4_l2t_update(काष्ठा adapter *adap, काष्ठा neighbour *neigh);
काष्ठा l2t_entry *t4_l2t_alloc_चयनing(काष्ठा adapter *adap, u16 vlan,
					 u8 port, u8 *dmac);
काष्ठा l2t_data *t4_init_l2t(अचिन्हित पूर्णांक l2t_start, अचिन्हित पूर्णांक l2t_end);
व्योम करो_l2t_ग_लिखो_rpl(काष्ठा adapter *p, स्थिर काष्ठा cpl_l2t_ग_लिखो_rpl *rpl);
bool cxgb4_check_l2t_valid(काष्ठा l2t_entry *e);

बाह्य स्थिर काष्ठा file_operations t4_l2t_fops;
#पूर्ण_अगर  /* __CXGB4_L2T_H */
