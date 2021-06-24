<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */

/* Included by drivers/net/dsa/sja1105/sja1105.h and net/dsa/tag_sja1105.c */

#अगर_अघोषित _NET_DSA_SJA1105_H
#घोषणा _NET_DSA_SJA1105_H

#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/dsa/8021q.h>
#समावेश <net/dsa.h>

#घोषणा ETH_P_SJA1105				ETH_P_DSA_8021Q
#घोषणा ETH_P_SJA1105_META			0x0008

/* IEEE 802.3 Annex 57A: Slow Protocols PDUs (01:80:C2:xx:xx:xx) */
#घोषणा SJA1105_LINKLOCAL_FILTER_A		0x0180C2000000ull
#घोषणा SJA1105_LINKLOCAL_FILTER_A_MASK		0xFFFFFF000000ull
/* IEEE 1588 Annex F: Transport of PTP over Ethernet (01:1B:19:xx:xx:xx) */
#घोषणा SJA1105_LINKLOCAL_FILTER_B		0x011B19000000ull
#घोषणा SJA1105_LINKLOCAL_FILTER_B_MASK		0xFFFFFF000000ull

/* Source and Destination MAC of follow-up meta frames.
 * Whereas the choice of SMAC only affects the unique identअगरication of the
 * चयन as sender of meta frames, the DMAC must be an address that is present
 * in the DSA master port's multicast MAC filter.
 * 01-80-C2-00-00-0E is a good choice क्रम this, as all profiles of IEEE 1588
 * over L2 use this address क्रम some purpose alपढ़ोy.
 */
#घोषणा SJA1105_META_SMAC			0x222222222222ull
#घोषणा SJA1105_META_DMAC			0x0180C200000Eull

#घोषणा SJA1105_HWTS_RX_EN			0

/* Global tagger data: each काष्ठा sja1105_port has a reference to
 * the काष्ठाure defined in काष्ठा sja1105_निजी.
 */
काष्ठा sja1105_tagger_data अणु
	काष्ठा sk_buff *stampable_skb;
	/* Protects concurrent access to the meta state machine
	 * from taggers running on multiple ports on SMP प्रणालीs
	 */
	spinlock_t meta_lock;
	अचिन्हित दीर्घ state;
पूर्ण;

काष्ठा sja1105_skb_cb अणु
	काष्ठा sk_buff *clone;
	u32 meta_tstamp;
पूर्ण;

#घोषणा SJA1105_SKB_CB(skb) \
	((काष्ठा sja1105_skb_cb *)((skb)->cb))

काष्ठा sja1105_port अणु
	u16 subvlan_map[DSA_8021Q_N_SUBVLAN];
	काष्ठा kthपढ़ो_worker *xmit_worker;
	काष्ठा kthपढ़ो_work xmit_work;
	काष्ठा sk_buff_head xmit_queue;
	काष्ठा sja1105_tagger_data *data;
	काष्ठा dsa_port *dp;
	bool hwts_tx_en;
	u16 xmit_tpid;
पूर्ण;

#पूर्ण_अगर /* _NET_DSA_SJA1105_H */
