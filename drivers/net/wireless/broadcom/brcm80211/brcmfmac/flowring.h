<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#अगर_अघोषित BRCMFMAC_FLOWRING_H
#घोषणा BRCMFMAC_FLOWRING_H


#घोषणा BRCMF_FLOWRING_HASHSIZE		512		/* has to be 2^x */
#घोषणा BRCMF_FLOWRING_INVALID_ID	0xFFFFFFFF


काष्ठा brcmf_flowring_hash अणु
	u8 mac[ETH_ALEN];
	u8 fअगरo;
	u8 अगरidx;
	u16 flowid;
पूर्ण;

क्रमागत ring_status अणु
	RING_CLOSED,
	RING_CLOSING,
	RING_OPEN
पूर्ण;

काष्ठा brcmf_flowring_ring अणु
	u16 hash_id;
	bool blocked;
	क्रमागत ring_status status;
	काष्ठा sk_buff_head skblist;
पूर्ण;

काष्ठा brcmf_flowring_tdls_entry अणु
	u8 mac[ETH_ALEN];
	काष्ठा brcmf_flowring_tdls_entry *next;
पूर्ण;

काष्ठा brcmf_flowring अणु
	काष्ठा device *dev;
	काष्ठा brcmf_flowring_hash hash[BRCMF_FLOWRING_HASHSIZE];
	काष्ठा brcmf_flowring_ring **rings;
	spinlock_t block_lock;
	क्रमागत proto_addr_mode addr_mode[BRCMF_MAX_IFS];
	u16 nrofrings;
	bool tdls_active;
	काष्ठा brcmf_flowring_tdls_entry *tdls_entry;
पूर्ण;


u32 brcmf_flowring_lookup(काष्ठा brcmf_flowring *flow, u8 da[ETH_ALEN],
			  u8 prio, u8 अगरidx);
u32 brcmf_flowring_create(काष्ठा brcmf_flowring *flow, u8 da[ETH_ALEN],
			  u8 prio, u8 अगरidx);
व्योम brcmf_flowring_delete(काष्ठा brcmf_flowring *flow, u16 flowid);
व्योम brcmf_flowring_खोलो(काष्ठा brcmf_flowring *flow, u16 flowid);
u8 brcmf_flowring_tid(काष्ठा brcmf_flowring *flow, u16 flowid);
u32 brcmf_flowring_enqueue(काष्ठा brcmf_flowring *flow, u16 flowid,
			   काष्ठा sk_buff *skb);
काष्ठा sk_buff *brcmf_flowring_dequeue(काष्ठा brcmf_flowring *flow, u16 flowid);
व्योम brcmf_flowring_reinsert(काष्ठा brcmf_flowring *flow, u16 flowid,
			     काष्ठा sk_buff *skb);
u32 brcmf_flowring_qlen(काष्ठा brcmf_flowring *flow, u16 flowid);
u8 brcmf_flowring_अगरidx_get(काष्ठा brcmf_flowring *flow, u16 flowid);
काष्ठा brcmf_flowring *brcmf_flowring_attach(काष्ठा device *dev, u16 nrofrings);
व्योम brcmf_flowring_detach(काष्ठा brcmf_flowring *flow);
व्योम brcmf_flowring_configure_addr_mode(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
					क्रमागत proto_addr_mode addr_mode);
व्योम brcmf_flowring_delete_peer(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
				u8 peer[ETH_ALEN]);
व्योम brcmf_flowring_add_tdls_peer(काष्ठा brcmf_flowring *flow, पूर्णांक अगरidx,
				  u8 peer[ETH_ALEN]);


#पूर्ण_अगर /* BRCMFMAC_FLOWRING_H */
