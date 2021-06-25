<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */


#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <brcmu_utils.h>

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "bus.h"
#समावेश "proto.h"
#समावेश "flowring.h"
#समावेश "msgbuf.h"
#समावेश "common.h"


#घोषणा BRCMF_FLOWRING_HIGH		1024
#घोषणा BRCMF_FLOWRING_LOW		(BRCMF_FLOWRING_HIGH - 256)
#घोषणा BRCMF_FLOWRING_INVALID_IFIDX	0xff

#घोषणा BRCMF_FLOWRING_HASH_AP(da, fअगरo, अगरidx) (da[5] * 2 + fअगरo + अगरidx * 16)
#घोषणा BRCMF_FLOWRING_HASH_STA(fअगरo, अगरidx) (fअगरo + अगरidx * 16)

अटल स्थिर u8 brcmf_flowring_prio2fअगरo[] = अणु
	0,
	1,
	1,
	0,
	2,
	2,
	3,
	3
पूर्ण;

अटल स्थिर u8 ALLFFMAC[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;


अटल bool
brcmf_flowring_is_tdls_mac(काष्ठा brcmf_flowring *flow, u8 mac[ETH_ALEN])
अणु
	काष्ठा brcmf_flowring_tdls_entry *search;

	search = flow->tdls_entry;

	जबतक (search) अणु
		अगर (स_भेद(search->mac, mac, ETH_ALEN) == 0)
			वापस true;
		search = search->next;
	पूर्ण

	वापस false;
पूर्ण


u32 brcmf_flowring_lookup(काष्ठा brcmf_flowring *flow, u8 da[ETH_ALEN],
			  u8 prio, u8 अगरidx)
अणु
	काष्ठा brcmf_flowring_hash *hash;
	u16 hash_idx;
	u32 i;
	bool found;
	bool sta;
	u8 fअगरo;
	u8 *mac;

	fअगरo = brcmf_flowring_prio2fअगरo[prio];
	sta = (flow->addr_mode[अगरidx] == ADDR_INसूचीECT);
	mac = da;
	अगर ((!sta) && (is_multicast_ether_addr(da))) अणु
		mac = (u8 *)ALLFFMAC;
		fअगरo = 0;
	पूर्ण
	अगर ((sta) && (flow->tdls_active) &&
	    (brcmf_flowring_is_tdls_mac(flow, da))) अणु
		sta = false;
	पूर्ण
	hash_idx =  sta ? BRCMF_FLOWRING_HASH_STA(fअगरo, अगरidx) :
			  BRCMF_FLOWRING_HASH_AP(mac, fअगरo, अगरidx);
	hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	found = false;
	hash = flow->hash;
	क्रम (i = 0; i < BRCMF_FLOWRING_HASHSIZE; i++) अणु
		अगर ((sta || (स_भेद(hash[hash_idx].mac, mac, ETH_ALEN) == 0)) &&
		    (hash[hash_idx].fअगरo == fअगरo) &&
		    (hash[hash_idx].अगरidx == अगरidx)) अणु
			found = true;
			अवरोध;
		पूर्ण
		hash_idx++;
		hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	पूर्ण
	अगर (found)
		वापस hash[hash_idx].flowid;

	वापस BRCMF_FLOWRING_INVALID_ID;
पूर्ण


u32 brcmf_flowring_create(काष्ठा brcmf_flowring *flow, u8 da[ETH_ALEN],
			  u8 prio, u8 अगरidx)
अणु
	काष्ठा brcmf_flowring_ring *ring;
	काष्ठा brcmf_flowring_hash *hash;
	u16 hash_idx;
	u32 i;
	bool found;
	u8 fअगरo;
	bool sta;
	u8 *mac;

	fअगरo = brcmf_flowring_prio2fअगरo[prio];
	sta = (flow->addr_mode[अगरidx] == ADDR_INसूचीECT);
	mac = da;
	अगर ((!sta) && (is_multicast_ether_addr(da))) अणु
		mac = (u8 *)ALLFFMAC;
		fअगरo = 0;
	पूर्ण
	अगर ((sta) && (flow->tdls_active) &&
	    (brcmf_flowring_is_tdls_mac(flow, da))) अणु
		sta = false;
	पूर्ण
	hash_idx =  sta ? BRCMF_FLOWRING_HASH_STA(fअगरo, अगरidx) :
			  BRCMF_FLOWRING_HASH_AP(mac, fअगरo, अगरidx);
	hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	found = false;
	hash = flow->hash;
	क्रम (i = 0; i < BRCMF_FLOWRING_HASHSIZE; i++) अणु
		अगर ((hash[hash_idx].अगरidx == BRCMF_FLOWRING_INVALID_IFIDX) &&
		    (is_zero_ether_addr(hash[hash_idx].mac))) अणु
			found = true;
			अवरोध;
		पूर्ण
		hash_idx++;
		hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	पूर्ण
	अगर (found) अणु
		क्रम (i = 0; i < flow->nrofrings; i++) अणु
			अगर (flow->rings[i] == शून्य)
				अवरोध;
		पूर्ण
		अगर (i == flow->nrofrings)
			वापस -ENOMEM;

		ring = kzalloc(माप(*ring), GFP_ATOMIC);
		अगर (!ring)
			वापस -ENOMEM;

		स_नकल(hash[hash_idx].mac, mac, ETH_ALEN);
		hash[hash_idx].fअगरo = fअगरo;
		hash[hash_idx].अगरidx = अगरidx;
		hash[hash_idx].flowid = i;

		ring->hash_id = hash_idx;
		ring->status = RING_CLOSED;
		skb_queue_head_init(&ring->skblist);
		flow->rings[i] = ring;

		वापस i;
	पूर्ण
	वापस BRCMF_FLOWRING_INVALID_ID;
पूर्ण


u8 brcmf_flowring_tid(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];

	वापस flow->hash[ring->hash_id].fअगरo;
पूर्ण


अटल व्योम brcmf_flowring_block(काष्ठा brcmf_flowring *flow, u16 flowid,
				 bool blocked)
अणु
	काष्ठा brcmf_flowring_ring *ring;
	काष्ठा brcmf_bus *bus_अगर;
	काष्ठा brcmf_pub *drvr;
	काष्ठा brcmf_अगर *अगरp;
	bool currently_blocked;
	पूर्णांक i;
	u8 अगरidx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&flow->block_lock, flags);

	ring = flow->rings[flowid];
	अगर (ring->blocked == blocked) अणु
		spin_unlock_irqrestore(&flow->block_lock, flags);
		वापस;
	पूर्ण
	अगरidx = brcmf_flowring_अगरidx_get(flow, flowid);

	currently_blocked = false;
	क्रम (i = 0; i < flow->nrofrings; i++) अणु
		अगर ((flow->rings[i]) && (i != flowid)) अणु
			ring = flow->rings[i];
			अगर ((ring->status == RING_OPEN) &&
			    (brcmf_flowring_अगरidx_get(flow, i) == अगरidx)) अणु
				अगर (ring->blocked) अणु
					currently_blocked = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	flow->rings[flowid]->blocked = blocked;
	अगर (currently_blocked) अणु
		spin_unlock_irqrestore(&flow->block_lock, flags);
		वापस;
	पूर्ण

	bus_अगर = dev_get_drvdata(flow->dev);
	drvr = bus_अगर->drvr;
	अगरp = brcmf_get_अगरp(drvr, अगरidx);
	brcmf_txflowblock_अगर(अगरp, BRCMF_NETIF_STOP_REASON_FLOW, blocked);

	spin_unlock_irqrestore(&flow->block_lock, flags);
पूर्ण


व्योम brcmf_flowring_delete(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(flow->dev);
	काष्ठा brcmf_flowring_ring *ring;
	काष्ठा brcmf_अगर *अगरp;
	u16 hash_idx;
	u8 अगरidx;
	काष्ठा sk_buff *skb;

	ring = flow->rings[flowid];
	अगर (!ring)
		वापस;

	अगरidx = brcmf_flowring_अगरidx_get(flow, flowid);
	अगरp = brcmf_get_अगरp(bus_अगर->drvr, अगरidx);

	brcmf_flowring_block(flow, flowid, false);
	hash_idx = ring->hash_id;
	flow->hash[hash_idx].अगरidx = BRCMF_FLOWRING_INVALID_IFIDX;
	eth_zero_addr(flow->hash[hash_idx].mac);
	flow->rings[flowid] = शून्य;

	skb = skb_dequeue(&ring->skblist);
	जबतक (skb) अणु
		brcmf_txfinalize(अगरp, skb, false);
		skb = skb_dequeue(&ring->skblist);
	पूर्ण

	kमुक्त(ring);
पूर्ण


u32 brcmf_flowring_enqueue(काष्ठा brcmf_flowring *flow, u16 flowid,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];

	skb_queue_tail(&ring->skblist, skb);

	अगर (!ring->blocked &&
	    (skb_queue_len(&ring->skblist) > BRCMF_FLOWRING_HIGH)) अणु
		brcmf_flowring_block(flow, flowid, true);
		brcmf_dbg(MSGBUF, "Flowcontrol: BLOCK for ring %d\n", flowid);
		/* To prevent (work around) possible race condition, check
		 * queue len again. It is also possible to use locking to
		 * protect, but that is undesirable क्रम every enqueue and
		 * dequeue. This simple check will solve a possible race
		 * condition अगर it occurs.
		 */
		अगर (skb_queue_len(&ring->skblist) < BRCMF_FLOWRING_LOW)
			brcmf_flowring_block(flow, flowid, false);
	पूर्ण
	वापस skb_queue_len(&ring->skblist);
पूर्ण


काष्ठा sk_buff *brcmf_flowring_dequeue(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_flowring_ring *ring;
	काष्ठा sk_buff *skb;

	ring = flow->rings[flowid];
	अगर (ring->status != RING_OPEN)
		वापस शून्य;

	skb = skb_dequeue(&ring->skblist);

	अगर (ring->blocked &&
	    (skb_queue_len(&ring->skblist) < BRCMF_FLOWRING_LOW)) अणु
		brcmf_flowring_block(flow, flowid, false);
		brcmf_dbg(MSGBUF, "Flowcontrol: OPEN for ring %d\n", flowid);
	पूर्ण

	वापस skb;
पूर्ण


व्योम brcmf_flowring_reinsert(काष्ठा brcmf_flowring *flow, u16 flowid,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];

	skb_queue_head(&ring->skblist, skb);
पूर्ण


u32 brcmf_flowring_qlen(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];
	अगर (!ring)
		वापस 0;

	अगर (ring->status != RING_OPEN)
		वापस 0;

	वापस skb_queue_len(&ring->skblist);
पूर्ण


व्योम brcmf_flowring_खोलो(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];
	अगर (!ring) अणु
		brcmf_err("Ring NULL, for flowid %d\n", flowid);
		वापस;
	पूर्ण

	ring->status = RING_OPEN;
पूर्ण


u8 brcmf_flowring_अगरidx_get(काष्ठा brcmf_flowring *flow, u16 flowid)
अणु
	काष्ठा brcmf_flowring_ring *ring;
	u16 hash_idx;

	ring = flow->rings[flowid];
	hash_idx = ring->hash_id;

	वापस flow->hash[hash_idx].अगरidx;
पूर्ण


काष्ठा brcmf_flowring *brcmf_flowring_attach(काष्ठा device *dev, u16 nrofrings)
अणु
	काष्ठा brcmf_flowring *flow;
	u32 i;

	flow = kzalloc(माप(*flow), GFP_KERNEL);
	अगर (flow) अणु
		flow->dev = dev;
		flow->nrofrings = nrofrings;
		spin_lock_init(&flow->block_lock);
		क्रम (i = 0; i < ARRAY_SIZE(flow->addr_mode); i++)
			flow->addr_mode[i] = ADDR_INसूचीECT;
		क्रम (i = 0; i < ARRAY_SIZE(flow->hash); i++)
			flow->hash[i].अगरidx = BRCMF_FLOWRING_INVALID_IFIDX;
		flow->rings = kसुस्मृति(nrofrings, माप(*flow->rings),
				      GFP_KERNEL);
		अगर (!flow->rings) अणु
			kमुक्त(flow);
			flow = शून्य;
		पूर्ण
	पूर्ण

	वापस flow;
पूर्ण


व्योम brcmf_flowring_detach(काष्ठा brcmf_flowring *flow)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(flow->dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_flowring_tdls_entry *search;
	काष्ठा brcmf_flowring_tdls_entry *हटाओ;
	u16 flowid;

	क्रम (flowid = 0; flowid < flow->nrofrings; flowid++) अणु
		अगर (flow->rings[flowid])
			brcmf_msgbuf_delete_flowring(drvr, flowid);
	पूर्ण

	search = flow->tdls_entry;
	जबतक (search) अणु
		हटाओ = search;
		search = search->next;
		kमुक्त(हटाओ);
	पूर्ण
	kमुक्त(flow->rings);
	kमुक्त(flow);
पूर्ण


व्योम brcmf_flowring_configure_addr_mode(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
					क्रमागत proto_addr_mode addr_mode)
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(flow->dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	u32 i;
	u16 flowid;

	अगर (flow->addr_mode[अगरidx] != addr_mode) अणु
		क्रम (i = 0; i < ARRAY_SIZE(flow->hash); i++) अणु
			अगर (flow->hash[i].अगरidx == अगरidx) अणु
				flowid = flow->hash[i].flowid;
				अगर (flow->rings[flowid]->status != RING_OPEN)
					जारी;
				flow->rings[flowid]->status = RING_CLOSING;
				brcmf_msgbuf_delete_flowring(drvr, flowid);
			पूर्ण
		पूर्ण
		flow->addr_mode[अगरidx] = addr_mode;
	पूर्ण
पूर्ण


व्योम brcmf_flowring_delete_peer(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
				u8 peer[ETH_ALEN])
अणु
	काष्ठा brcmf_bus *bus_अगर = dev_get_drvdata(flow->dev);
	काष्ठा brcmf_pub *drvr = bus_अगर->drvr;
	काष्ठा brcmf_flowring_hash *hash;
	काष्ठा brcmf_flowring_tdls_entry *prev;
	काष्ठा brcmf_flowring_tdls_entry *search;
	u32 i;
	u16 flowid;
	bool sta;

	sta = (flow->addr_mode[अगरidx] == ADDR_INसूचीECT);

	search = flow->tdls_entry;
	prev = शून्य;
	जबतक (search) अणु
		अगर (स_भेद(search->mac, peer, ETH_ALEN) == 0) अणु
			sta = false;
			अवरोध;
		पूर्ण
		prev = search;
		search = search->next;
	पूर्ण

	hash = flow->hash;
	क्रम (i = 0; i < BRCMF_FLOWRING_HASHSIZE; i++) अणु
		अगर ((sta || (स_भेद(hash[i].mac, peer, ETH_ALEN) == 0)) &&
		    (hash[i].अगरidx == अगरidx)) अणु
			flowid = flow->hash[i].flowid;
			अगर (flow->rings[flowid]->status == RING_OPEN) अणु
				flow->rings[flowid]->status = RING_CLOSING;
				brcmf_msgbuf_delete_flowring(drvr, flowid);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (search) अणु
		अगर (prev)
			prev->next = search->next;
		अन्यथा
			flow->tdls_entry = search->next;
		kमुक्त(search);
		अगर (flow->tdls_entry == शून्य)
			flow->tdls_active = false;
	पूर्ण
पूर्ण


व्योम brcmf_flowring_add_tdls_peer(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
				  u8 peer[ETH_ALEN])
अणु
	काष्ठा brcmf_flowring_tdls_entry *tdls_entry;
	काष्ठा brcmf_flowring_tdls_entry *search;

	tdls_entry = kzalloc(माप(*tdls_entry), GFP_ATOMIC);
	अगर (tdls_entry == शून्य)
		वापस;

	स_नकल(tdls_entry->mac, peer, ETH_ALEN);
	tdls_entry->next = शून्य;
	अगर (flow->tdls_entry == शून्य) अणु
		flow->tdls_entry = tdls_entry;
	पूर्ण अन्यथा अणु
		search = flow->tdls_entry;
		अगर (स_भेद(search->mac, peer, ETH_ALEN) == 0)
			जाओ मुक्त_entry;
		जबतक (search->next) अणु
			search = search->next;
			अगर (स_भेद(search->mac, peer, ETH_ALEN) == 0)
				जाओ मुक्त_entry;
		पूर्ण
		search->next = tdls_entry;
	पूर्ण

	flow->tdls_active = true;
	वापस;

मुक्त_entry:
	kमुक्त(tdls_entry);
पूर्ण
