<शैली गुरु>
/*
 * Copyright(c) 2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * This file contains OPA VNIC encapsulation/decapsulation function.
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "opa_vnic_internal.h"

/* OPA 16B Header fields */
#घोषणा OPA_16B_LID_MASK        0xFFFFFull
#घोषणा OPA_16B_SLID_HIGH_SHFT  8
#घोषणा OPA_16B_SLID_MASK       0xF00ull
#घोषणा OPA_16B_DLID_MASK       0xF000ull
#घोषणा OPA_16B_DLID_HIGH_SHFT  12
#घोषणा OPA_16B_LEN_SHFT        20
#घोषणा OPA_16B_SC_SHFT         20
#घोषणा OPA_16B_RC_SHFT         25
#घोषणा OPA_16B_PKEY_SHFT       16

#घोषणा OPA_VNIC_L4_HDR_SHFT    16

/* L2+L4 hdr len is 20 bytes (5 quad words) */
#घोषणा OPA_VNIC_HDR_QW_LEN   5

अटल अंतरभूत व्योम opa_vnic_make_header(u8 *hdr, u32 slid, u32 dlid, u16 len,
					u16 pkey, u16 entropy, u8 sc, u8 rc,
					u8 l4_type, u16 l4_hdr)
अणु
	/* h[1]: LT=1, 16B L2=10 */
	u32 h[OPA_VNIC_HDR_QW_LEN] = अणु0, 0xc0000000, 0, 0, 0पूर्ण;

	h[2] = l4_type;
	h[3] = entropy;
	h[4] = l4_hdr << OPA_VNIC_L4_HDR_SHFT;

	/* Extract and set 4 upper bits and 20 lower bits of the lids */
	h[0] |= (slid & OPA_16B_LID_MASK);
	h[2] |= ((slid >> (20 - OPA_16B_SLID_HIGH_SHFT)) & OPA_16B_SLID_MASK);

	h[1] |= (dlid & OPA_16B_LID_MASK);
	h[2] |= ((dlid >> (20 - OPA_16B_DLID_HIGH_SHFT)) & OPA_16B_DLID_MASK);

	h[0] |= (len << OPA_16B_LEN_SHFT);
	h[1] |= (rc << OPA_16B_RC_SHFT);
	h[1] |= (sc << OPA_16B_SC_SHFT);
	h[2] |= ((u32)pkey << OPA_16B_PKEY_SHFT);

	स_नकल(hdr, h, OPA_VNIC_HDR_LEN);
पूर्ण

/*
 * Using a simple hash table क्रम mac table implementation with the last octet
 * of mac address as a key.
 */
अटल व्योम opa_vnic_मुक्त_mac_tbl(काष्ठा hlist_head *mactbl)
अणु
	काष्ठा opa_vnic_mac_tbl_node *node;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक bkt;

	अगर (!mactbl)
		वापस;

	vnic_hash_क्रम_each_safe(mactbl, bkt, पंचांगp, node, hlist) अणु
		hash_del(&node->hlist);
		kमुक्त(node);
	पूर्ण
	kमुक्त(mactbl);
पूर्ण

अटल काष्ठा hlist_head *opa_vnic_alloc_mac_tbl(व्योम)
अणु
	u32 size = माप(काष्ठा hlist_head) * OPA_VNIC_MAC_TBL_SIZE;
	काष्ठा hlist_head *mactbl;

	mactbl = kzalloc(size, GFP_KERNEL);
	अगर (!mactbl)
		वापस ERR_PTR(-ENOMEM);

	vnic_hash_init(mactbl);
	वापस mactbl;
पूर्ण

/* opa_vnic_release_mac_tbl - empty and मुक्त the mac table */
व्योम opa_vnic_release_mac_tbl(काष्ठा opa_vnic_adapter *adapter)
अणु
	काष्ठा hlist_head *mactbl;

	mutex_lock(&adapter->mactbl_lock);
	mactbl = rcu_access_poपूर्णांकer(adapter->mactbl);
	rcu_assign_poपूर्णांकer(adapter->mactbl, शून्य);
	synchronize_rcu();
	opa_vnic_मुक्त_mac_tbl(mactbl);
	adapter->info.vport.mac_tbl_digest = 0;
	mutex_unlock(&adapter->mactbl_lock);
पूर्ण

/*
 * opa_vnic_query_mac_tbl - query the mac table क्रम a section
 *
 * This function implements query of specअगरic function of the mac table.
 * The function also expects the requested range to be valid.
 */
व्योम opa_vnic_query_mac_tbl(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_veswport_mactable *tbl)
अणु
	काष्ठा opa_vnic_mac_tbl_node *node;
	काष्ठा hlist_head *mactbl;
	पूर्णांक bkt;
	u16 loffset, lnum_entries;

	rcu_पढ़ो_lock();
	mactbl = rcu_dereference(adapter->mactbl);
	अगर (!mactbl)
		जाओ get_mac_करोne;

	loffset = be16_to_cpu(tbl->offset);
	lnum_entries = be16_to_cpu(tbl->num_entries);

	vnic_hash_क्रम_each(mactbl, bkt, node, hlist) अणु
		काष्ठा __opa_vnic_mactable_entry *nentry = &node->entry;
		काष्ठा opa_veswport_mactable_entry *entry;

		अगर ((node->index < loffset) ||
		    (node->index >= (loffset + lnum_entries)))
			जारी;

		/* populate entry in the tbl corresponding to the index */
		entry = &tbl->tbl_entries[node->index - loffset];
		स_नकल(entry->mac_addr, nentry->mac_addr,
		       ARRAY_SIZE(entry->mac_addr));
		स_नकल(entry->mac_addr_mask, nentry->mac_addr_mask,
		       ARRAY_SIZE(entry->mac_addr_mask));
		entry->dlid_sd = cpu_to_be32(nentry->dlid_sd);
	पूर्ण
	tbl->mac_tbl_digest = cpu_to_be32(adapter->info.vport.mac_tbl_digest);
get_mac_करोne:
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * opa_vnic_update_mac_tbl - update mac table section
 *
 * This function updates the specअगरied section of the mac table.
 * The procedure includes following steps.
 *  - Allocate a new mac (hash) table.
 *  - Add the specअगरied entries to the new table.
 *    (except the ones that are requested to be deleted).
 *  - Add all the other entries from the old mac table.
 *  - If there is a failure, मुक्त the new table and वापस.
 *  - Switch to the new table.
 *  - Free the old table and वापस.
 *
 * The function also expects the requested range to be valid.
 */
पूर्णांक opa_vnic_update_mac_tbl(काष्ठा opa_vnic_adapter *adapter,
			    काष्ठा opa_veswport_mactable *tbl)
अणु
	काष्ठा opa_vnic_mac_tbl_node *node, *new_node;
	काष्ठा hlist_head *new_mactbl, *old_mactbl;
	पूर्णांक i, bkt, rc = 0;
	u8 key;
	u16 loffset, lnum_entries;

	mutex_lock(&adapter->mactbl_lock);
	/* allocate new mac table */
	new_mactbl = opa_vnic_alloc_mac_tbl();
	अगर (IS_ERR(new_mactbl)) अणु
		mutex_unlock(&adapter->mactbl_lock);
		वापस PTR_ERR(new_mactbl);
	पूर्ण

	loffset = be16_to_cpu(tbl->offset);
	lnum_entries = be16_to_cpu(tbl->num_entries);

	/* add updated entries to the new mac table */
	क्रम (i = 0; i < lnum_entries; i++) अणु
		काष्ठा __opa_vnic_mactable_entry *nentry;
		काष्ठा opa_veswport_mactable_entry *entry =
							&tbl->tbl_entries[i];
		u8 *mac_addr = entry->mac_addr;
		u8 empty_mac[ETH_ALEN] = अणु 0 पूर्ण;

		v_dbg("new mac entry %4d: %02x:%02x:%02x:%02x:%02x:%02x %x\n",
		      loffset + i, mac_addr[0], mac_addr[1], mac_addr[2],
		      mac_addr[3], mac_addr[4], mac_addr[5],
		      entry->dlid_sd);

		/* अगर the entry is being हटाओd, करो not add it */
		अगर (!स_भेद(mac_addr, empty_mac, ARRAY_SIZE(empty_mac)))
			जारी;

		node = kzalloc(माप(*node), GFP_KERNEL);
		अगर (!node) अणु
			rc = -ENOMEM;
			जाओ updt_करोne;
		पूर्ण

		node->index = loffset + i;
		nentry = &node->entry;
		स_नकल(nentry->mac_addr, entry->mac_addr,
		       ARRAY_SIZE(nentry->mac_addr));
		स_नकल(nentry->mac_addr_mask, entry->mac_addr_mask,
		       ARRAY_SIZE(nentry->mac_addr_mask));
		nentry->dlid_sd = be32_to_cpu(entry->dlid_sd);
		key = node->entry.mac_addr[OPA_VNIC_MAC_HASH_IDX];
		vnic_hash_add(new_mactbl, &node->hlist, key);
	पूर्ण

	/* add other entries from current mac table to new mac table */
	old_mactbl = rcu_access_poपूर्णांकer(adapter->mactbl);
	अगर (!old_mactbl)
		जाओ चयन_tbl;

	vnic_hash_क्रम_each(old_mactbl, bkt, node, hlist) अणु
		अगर ((node->index >= loffset) &&
		    (node->index < (loffset + lnum_entries)))
			जारी;

		new_node = kzalloc(माप(*new_node), GFP_KERNEL);
		अगर (!new_node) अणु
			rc = -ENOMEM;
			जाओ updt_करोne;
		पूर्ण

		new_node->index = node->index;
		स_नकल(&new_node->entry, &node->entry, माप(node->entry));
		key = new_node->entry.mac_addr[OPA_VNIC_MAC_HASH_IDX];
		vnic_hash_add(new_mactbl, &new_node->hlist, key);
	पूर्ण

चयन_tbl:
	/* चयन to new table */
	rcu_assign_poपूर्णांकer(adapter->mactbl, new_mactbl);
	synchronize_rcu();

	adapter->info.vport.mac_tbl_digest = be32_to_cpu(tbl->mac_tbl_digest);
updt_करोne:
	/* upon failure, मुक्त the new table; otherwise, मुक्त the old table */
	अगर (rc)
		opa_vnic_मुक्त_mac_tbl(new_mactbl);
	अन्यथा
		opa_vnic_मुक्त_mac_tbl(old_mactbl);

	mutex_unlock(&adapter->mactbl_lock);
	वापस rc;
पूर्ण

/* opa_vnic_chk_mac_tbl - check mac table क्रम dlid */
अटल uपूर्णांक32_t opa_vnic_chk_mac_tbl(काष्ठा opa_vnic_adapter *adapter,
				     काष्ठा ethhdr *mac_hdr)
अणु
	काष्ठा opa_vnic_mac_tbl_node *node;
	काष्ठा hlist_head *mactbl;
	u32 dlid = 0;
	u8 key;

	rcu_पढ़ो_lock();
	mactbl = rcu_dereference(adapter->mactbl);
	अगर (unlikely(!mactbl))
		जाओ chk_करोne;

	key = mac_hdr->h_dest[OPA_VNIC_MAC_HASH_IDX];
	vnic_hash_क्रम_each_possible(mactbl, node, hlist, key) अणु
		काष्ठा __opa_vnic_mactable_entry *entry = &node->entry;

		/* अगर related to source mac, skip */
		अगर (unlikely(OPA_VNIC_DLID_SD_IS_SRC_MAC(entry->dlid_sd)))
			जारी;

		अगर (!स_भेद(node->entry.mac_addr, mac_hdr->h_dest,
			    ARRAY_SIZE(node->entry.mac_addr))) अणु
			/* mac address found */
			dlid = OPA_VNIC_DLID_SD_GET_DLID(node->entry.dlid_sd);
			अवरोध;
		पूर्ण
	पूर्ण

chk_करोne:
	rcu_पढ़ो_unlock();
	वापस dlid;
पूर्ण

/* opa_vnic_get_dlid - find and वापस the DLID */
अटल uपूर्णांक32_t opa_vnic_get_dlid(काष्ठा opa_vnic_adapter *adapter,
				  काष्ठा sk_buff *skb, u8 def_port)
अणु
	काष्ठा __opa_veswport_info *info = &adapter->info;
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	u32 dlid;

	dlid = opa_vnic_chk_mac_tbl(adapter, mac_hdr);
	अगर (dlid)
		वापस dlid;

	अगर (is_multicast_ether_addr(mac_hdr->h_dest)) अणु
		dlid = info->vesw.u_mcast_dlid;
	पूर्ण अन्यथा अणु
		अगर (is_local_ether_addr(mac_hdr->h_dest)) अणु
			dlid = ((uपूर्णांक32_t)mac_hdr->h_dest[5] << 16) |
				((uपूर्णांक32_t)mac_hdr->h_dest[4] << 8)  |
				mac_hdr->h_dest[3];
			अगर (unlikely(!dlid))
				v_warn("Null dlid in MAC address\n");
		पूर्ण अन्यथा अगर (def_port != OPA_VNIC_INVALID_PORT) अणु
			अगर (def_port < OPA_VESW_MAX_NUM_DEF_PORT)
				dlid = info->vesw.u_ucast_dlid[def_port];
		पूर्ण
	पूर्ण

	वापस dlid;
पूर्ण

/* opa_vnic_get_sc - वापस the service class */
अटल u8 opa_vnic_get_sc(काष्ठा __opa_veswport_info *info,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	u16 vlan_tci;
	u8 sc;

	अगर (!__vlan_get_tag(skb, &vlan_tci)) अणु
		u8 pcp = OPA_VNIC_VLAN_PCP(vlan_tci);

		अगर (is_multicast_ether_addr(mac_hdr->h_dest))
			sc = info->vport.pcp_to_sc_mc[pcp];
		अन्यथा
			sc = info->vport.pcp_to_sc_uc[pcp];
	पूर्ण अन्यथा अणु
		अगर (is_multicast_ether_addr(mac_hdr->h_dest))
			sc = info->vport.non_vlan_sc_mc;
		अन्यथा
			sc = info->vport.non_vlan_sc_uc;
	पूर्ण

	वापस sc;
पूर्ण

u8 opa_vnic_get_vl(काष्ठा opa_vnic_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *mac_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	काष्ठा __opa_veswport_info *info = &adapter->info;
	u8 vl;

	अगर (skb_vlan_tag_present(skb)) अणु
		u8 pcp = skb_vlan_tag_get(skb) >> VLAN_PRIO_SHIFT;

		अगर (is_multicast_ether_addr(mac_hdr->h_dest))
			vl = info->vport.pcp_to_vl_mc[pcp];
		अन्यथा
			vl = info->vport.pcp_to_vl_uc[pcp];
	पूर्ण अन्यथा अणु
		अगर (is_multicast_ether_addr(mac_hdr->h_dest))
			vl = info->vport.non_vlan_vl_mc;
		अन्यथा
			vl = info->vport.non_vlan_vl_uc;
	पूर्ण

	वापस vl;
पूर्ण

/* opa_vnic_get_rc - वापस the routing control */
अटल u8 opa_vnic_get_rc(काष्ठा __opa_veswport_info *info,
			  काष्ठा sk_buff *skb)
अणु
	u8 proto, rout_ctrl;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IPV6):
		proto = ipv6_hdr(skb)->nexthdr;
		अगर (proto == IPPROTO_TCP)
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc,
							  IPV6_TCP);
		अन्यथा अगर (proto == IPPROTO_UDP)
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc,
							  IPV6_UDP);
		अन्यथा
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc, IPV6);
		अवरोध;
	हाल htons(ETH_P_IP):
		proto = ip_hdr(skb)->protocol;
		अगर (proto == IPPROTO_TCP)
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc,
							  IPV4_TCP);
		अन्यथा अगर (proto == IPPROTO_UDP)
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc,
							  IPV4_UDP);
		अन्यथा
			rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc, IPV4);
		अवरोध;
	शेष:
		rout_ctrl = OPA_VNIC_ENCAP_RC_EXT(info->vesw.rc, DEFAULT);
	पूर्ण

	वापस rout_ctrl;
पूर्ण

/* opa_vnic_calc_entropy - calculate the packet entropy */
u8 opa_vnic_calc_entropy(काष्ठा sk_buff *skb)
अणु
	u32 hash = skb_get_hash(skb);

	/* store XOR of all bytes in lower 8 bits */
	hash ^= hash >> 8;
	hash ^= hash >> 16;

	/* वापस lower 8 bits as entropy */
	वापस (u8)(hash & 0xFF);
पूर्ण

/* opa_vnic_get_def_port - get शेष port based on entropy */
अटल अंतरभूत u8 opa_vnic_get_def_port(काष्ठा opa_vnic_adapter *adapter,
				       u8 entropy)
अणु
	u8 flow_id;

	/* Add the upper and lower 4-bits of entropy to get the flow id */
	flow_id = ((entropy & 0xf) + (entropy >> 4));
	वापस adapter->flow_tbl[flow_id & (OPA_VNIC_FLOW_TBL_SIZE - 1)];
पूर्ण

/* Calculate packet length including OPA header, crc and padding */
अटल अंतरभूत पूर्णांक opa_vnic_wire_length(काष्ठा sk_buff *skb)
अणु
	u32 pad_len;

	/* padding क्रम 8 bytes size alignment */
	pad_len = -(skb->len + OPA_VNIC_ICRC_TAIL_LEN) & 0x7;
	pad_len += OPA_VNIC_ICRC_TAIL_LEN;

	वापस (skb->len + pad_len) >> 3;
पूर्ण

/* opa_vnic_encap_skb - encapsulate skb packet with OPA header and meta data */
व्योम opa_vnic_encap_skb(काष्ठा opa_vnic_adapter *adapter, काष्ठा sk_buff *skb)
अणु
	काष्ठा __opa_veswport_info *info = &adapter->info;
	काष्ठा opa_vnic_skb_mdata *mdata;
	u8 def_port, sc, rc, entropy, *hdr;
	u16 len, l4_hdr;
	u32 dlid;

	hdr = skb_push(skb, OPA_VNIC_HDR_LEN);

	entropy = opa_vnic_calc_entropy(skb);
	def_port = opa_vnic_get_def_port(adapter, entropy);
	len = opa_vnic_wire_length(skb);
	dlid = opa_vnic_get_dlid(adapter, skb, def_port);
	sc = opa_vnic_get_sc(info, skb);
	rc = opa_vnic_get_rc(info, skb);
	l4_hdr = info->vesw.vesw_id;

	mdata = skb_push(skb, माप(*mdata));
	mdata->vl = opa_vnic_get_vl(adapter, skb);
	mdata->entropy = entropy;
	mdata->flags = 0;
	अगर (unlikely(!dlid)) अणु
		mdata->flags = OPA_VNIC_SKB_MDATA_ENCAP_ERR;
		वापस;
	पूर्ण

	opa_vnic_make_header(hdr, info->vport.encap_slid, dlid, len,
			     info->vesw.pkey, entropy, sc, rc,
			     OPA_VNIC_L4_ETHR, l4_hdr);
पूर्ण
