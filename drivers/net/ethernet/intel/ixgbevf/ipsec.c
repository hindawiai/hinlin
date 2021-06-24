<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Oracle and/or its affiliates. All rights reserved. */

#समावेश "ixgbevf.h"
#समावेश <net/xfrm.h>
#समावेश <crypto/aead.h>

#घोषणा IXGBE_IPSEC_KEY_BITS  160
अटल स्थिर अक्षर aes_gcm_name[] = "rfc4106(gcm(aes))";

/**
 * ixgbevf_ipsec_set_pf_sa - ask the PF to set up an SA
 * @adapter: board निजी काष्ठाure
 * @xs: xfrm info to be sent to the PF
 *
 * Returns: positive offload handle from the PF, or negative error code
 **/
अटल पूर्णांक ixgbevf_ipsec_set_pf_sa(काष्ठा ixgbevf_adapter *adapter,
				   काष्ठा xfrm_state *xs)
अणु
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE] = अणु 0 पूर्ण;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा sa_mbx_msg *sam;
	पूर्णांक ret;

	/* send the important bits to the PF */
	sam = (काष्ठा sa_mbx_msg *)(&msgbuf[1]);
	sam->flags = xs->xso.flags;
	sam->spi = xs->id.spi;
	sam->proto = xs->id.proto;
	sam->family = xs->props.family;

	अगर (xs->props.family == AF_INET6)
		स_नकल(sam->addr, &xs->id.daddr.a6, माप(xs->id.daddr.a6));
	अन्यथा
		स_नकल(sam->addr, &xs->id.daddr.a4, माप(xs->id.daddr.a4));
	स_नकल(sam->key, xs->aead->alg_key, माप(sam->key));

	msgbuf[0] = IXGBE_VF_IPSEC_ADD;

	spin_lock_bh(&adapter->mbx_lock);

	ret = hw->mbx.ops.ग_लिखो_posted(hw, msgbuf, IXGBE_VFMAILBOX_SIZE);
	अगर (ret)
		जाओ out;

	ret = hw->mbx.ops.पढ़ो_posted(hw, msgbuf, 2);
	अगर (ret)
		जाओ out;

	ret = (पूर्णांक)msgbuf[1];
	अगर (msgbuf[0] & IXGBE_VT_MSGTYPE_NACK && ret >= 0)
		ret = -1;

out:
	spin_unlock_bh(&adapter->mbx_lock);

	वापस ret;
पूर्ण

/**
 * ixgbevf_ipsec_del_pf_sa - ask the PF to delete an SA
 * @adapter: board निजी काष्ठाure
 * @pfsa: sa index वापसed from PF when created, -1 क्रम all
 *
 * Returns: 0 on success, or negative error code
 **/
अटल पूर्णांक ixgbevf_ipsec_del_pf_sa(काष्ठा ixgbevf_adapter *adapter, पूर्णांक pfsa)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 msgbuf[2];
	पूर्णांक err;

	स_रखो(msgbuf, 0, माप(msgbuf));
	msgbuf[0] = IXGBE_VF_IPSEC_DEL;
	msgbuf[1] = (u32)pfsa;

	spin_lock_bh(&adapter->mbx_lock);

	err = hw->mbx.ops.ग_लिखो_posted(hw, msgbuf, 2);
	अगर (err)
		जाओ out;

	err = hw->mbx.ops.पढ़ो_posted(hw, msgbuf, 2);
	अगर (err)
		जाओ out;

out:
	spin_unlock_bh(&adapter->mbx_lock);
	वापस err;
पूर्ण

/**
 * ixgbevf_ipsec_restore - restore the IPsec HW settings after a reset
 * @adapter: board निजी काष्ठाure
 *
 * Reload the HW tables from the SW tables after they've been bashed
 * by a chip reset.  While we're here, make sure any stale VF data is
 * हटाओd, since we go through reset when num_vfs changes.
 **/
व्योम ixgbevf_ipsec_restore(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i;

	अगर (!(adapter->netdev->features & NETIF_F_HW_ESP))
		वापस;

	/* reload the Rx and Tx keys */
	क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
		काष्ठा rx_sa *r = &ipsec->rx_tbl[i];
		काष्ठा tx_sa *t = &ipsec->tx_tbl[i];
		पूर्णांक ret;

		अगर (r->used) अणु
			ret = ixgbevf_ipsec_set_pf_sa(adapter, r->xs);
			अगर (ret < 0)
				netdev_err(netdev, "reload rx_tbl[%d] failed = %d\n",
					   i, ret);
		पूर्ण

		अगर (t->used) अणु
			ret = ixgbevf_ipsec_set_pf_sa(adapter, t->xs);
			अगर (ret < 0)
				netdev_err(netdev, "reload tx_tbl[%d] failed = %d\n",
					   i, ret);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ixgbevf_ipsec_find_empty_idx - find the first unused security parameter index
 * @ipsec: poपूर्णांकer to IPsec काष्ठा
 * @rxtable: true अगर we need to look in the Rx table
 *
 * Returns the first unused index in either the Rx or Tx SA table
 **/
अटल
पूर्णांक ixgbevf_ipsec_find_empty_idx(काष्ठा ixgbevf_ipsec *ipsec, bool rxtable)
अणु
	u32 i;

	अगर (rxtable) अणु
		अगर (ipsec->num_rx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			वापस -ENOSPC;

		/* search rx sa table */
		क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
			अगर (!ipsec->rx_tbl[i].used)
				वापस i;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ipsec->num_tx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			वापस -ENOSPC;

		/* search tx sa table */
		क्रम (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) अणु
			अगर (!ipsec->tx_tbl[i].used)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * ixgbevf_ipsec_find_rx_state - find the state that matches
 * @ipsec: poपूर्णांकer to IPsec काष्ठा
 * @daddr: inbound address to match
 * @proto: protocol to match
 * @spi: SPI to match
 * @ip4: true अगर using an IPv4 address
 *
 * Returns a poपूर्णांकer to the matching SA state inक्रमmation
 **/
अटल
काष्ठा xfrm_state *ixgbevf_ipsec_find_rx_state(काष्ठा ixgbevf_ipsec *ipsec,
					       __be32 *daddr, u8 proto,
					       __be32 spi, bool ip4)
अणु
	काष्ठा xfrm_state *ret = शून्य;
	काष्ठा rx_sa *rsa;

	rcu_पढ़ो_lock();
	hash_क्रम_each_possible_rcu(ipsec->rx_sa_list, rsa, hlist,
				   (__क्रमce u32)spi) अणु
		अगर (spi == rsa->xs->id.spi &&
		    ((ip4 && *daddr == rsa->xs->id.daddr.a4) ||
		      (!ip4 && !स_भेद(daddr, &rsa->xs->id.daddr.a6,
				       माप(rsa->xs->id.daddr.a6)))) &&
		    proto == rsa->xs->id.proto) अणु
			ret = rsa->xs;
			xfrm_state_hold(ret);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * ixgbevf_ipsec_parse_proto_keys - find the key and salt based on the protocol
 * @xs: poपूर्णांकer to xfrm_state काष्ठा
 * @mykey: poपूर्णांकer to key array to populate
 * @mysalt: poपूर्णांकer to salt value to populate
 *
 * This copies the protocol keys and salt to our own data tables.  The
 * 82599 family only supports the one algorithm.
 **/
अटल पूर्णांक ixgbevf_ipsec_parse_proto_keys(काष्ठा xfrm_state *xs,
					  u32 *mykey, u32 *mysalt)
अणु
	काष्ठा net_device *dev = xs->xso.dev;
	अचिन्हित अक्षर *key_data;
	अक्षर *alg_name = शून्य;
	पूर्णांक key_len;

	अगर (!xs->aead) अणु
		netdev_err(dev, "Unsupported IPsec algorithm\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xs->aead->alg_icv_len != IXGBE_IPSEC_AUTH_BITS) अणु
		netdev_err(dev, "IPsec offload requires %d bit authentication\n",
			   IXGBE_IPSEC_AUTH_BITS);
		वापस -EINVAL;
	पूर्ण

	key_data = &xs->aead->alg_key[0];
	key_len = xs->aead->alg_key_len;
	alg_name = xs->aead->alg_name;

	अगर (म_भेद(alg_name, aes_gcm_name)) अणु
		netdev_err(dev, "Unsupported IPsec algorithm - please use %s\n",
			   aes_gcm_name);
		वापस -EINVAL;
	पूर्ण

	/* The key bytes come करोwn in a big endian array of bytes, so
	 * we करोn't need to करो any byte swapping.
	 * 160 accounts क्रम 16 byte key and 4 byte salt
	 */
	अगर (key_len > IXGBE_IPSEC_KEY_BITS) अणु
		*mysalt = ((u32 *)key_data)[4];
	पूर्ण अन्यथा अगर (key_len == IXGBE_IPSEC_KEY_BITS) अणु
		*mysalt = 0;
	पूर्ण अन्यथा अणु
		netdev_err(dev, "IPsec hw offload only supports keys up to 128 bits with a 32 bit salt\n");
		वापस -EINVAL;
	पूर्ण
	स_नकल(mykey, key_data, 16);

	वापस 0;
पूर्ण

/**
 * ixgbevf_ipsec_add_sa - program device with a security association
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल पूर्णांक ixgbevf_ipsec_add_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *dev = xs->xso.dev;
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;
	u16 sa_idx;
	पूर्णांक ret;

	अगर (xs->id.proto != IPPROTO_ESP && xs->id.proto != IPPROTO_AH) अणु
		netdev_err(dev, "Unsupported protocol 0x%04x for IPsec offload\n",
			   xs->id.proto);
		वापस -EINVAL;
	पूर्ण

	अगर (xs->props.mode != XFRM_MODE_TRANSPORT) अणु
		netdev_err(dev, "Unsupported mode for ipsec offload\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xs->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		काष्ठा rx_sa rsa;

		अगर (xs->calg) अणु
			netdev_err(dev, "Compression offload not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* find the first unused index */
		ret = ixgbevf_ipsec_find_empty_idx(ipsec, true);
		अगर (ret < 0) अणु
			netdev_err(dev, "No space for SA in Rx table!\n");
			वापस ret;
		पूर्ण
		sa_idx = (u16)ret;

		स_रखो(&rsa, 0, माप(rsa));
		rsa.used = true;
		rsa.xs = xs;

		अगर (rsa.xs->id.proto & IPPROTO_ESP)
			rsa.decrypt = xs->ealg || xs->aead;

		/* get the key and salt */
		ret = ixgbevf_ipsec_parse_proto_keys(xs, rsa.key, &rsa.salt);
		अगर (ret) अणु
			netdev_err(dev, "Failed to get key data for Rx SA table\n");
			वापस ret;
		पूर्ण

		/* get ip क्रम rx sa table */
		अगर (xs->props.family == AF_INET6)
			स_नकल(rsa.ipaddr, &xs->id.daddr.a6, 16);
		अन्यथा
			स_नकल(&rsa.ipaddr[3], &xs->id.daddr.a4, 4);

		rsa.mode = IXGBE_RXMOD_VALID;
		अगर (rsa.xs->id.proto & IPPROTO_ESP)
			rsa.mode |= IXGBE_RXMOD_PROTO_ESP;
		अगर (rsa.decrypt)
			rsa.mode |= IXGBE_RXMOD_DECRYPT;
		अगर (rsa.xs->props.family == AF_INET6)
			rsa.mode |= IXGBE_RXMOD_IPV6;

		ret = ixgbevf_ipsec_set_pf_sa(adapter, xs);
		अगर (ret < 0)
			वापस ret;
		rsa.pfsa = ret;

		/* the preparations worked, so save the info */
		स_नकल(&ipsec->rx_tbl[sa_idx], &rsa, माप(rsa));

		xs->xso.offload_handle = sa_idx + IXGBE_IPSEC_BASE_RX_INDEX;

		ipsec->num_rx_sa++;

		/* hash the new entry क्रम faster search in Rx path */
		hash_add_rcu(ipsec->rx_sa_list, &ipsec->rx_tbl[sa_idx].hlist,
			     (__क्रमce u32)rsa.xs->id.spi);
	पूर्ण अन्यथा अणु
		काष्ठा tx_sa tsa;

		/* find the first unused index */
		ret = ixgbevf_ipsec_find_empty_idx(ipsec, false);
		अगर (ret < 0) अणु
			netdev_err(dev, "No space for SA in Tx table\n");
			वापस ret;
		पूर्ण
		sa_idx = (u16)ret;

		स_रखो(&tsa, 0, माप(tsa));
		tsa.used = true;
		tsa.xs = xs;

		अगर (xs->id.proto & IPPROTO_ESP)
			tsa.encrypt = xs->ealg || xs->aead;

		ret = ixgbevf_ipsec_parse_proto_keys(xs, tsa.key, &tsa.salt);
		अगर (ret) अणु
			netdev_err(dev, "Failed to get key data for Tx SA table\n");
			स_रखो(&tsa, 0, माप(tsa));
			वापस ret;
		पूर्ण

		ret = ixgbevf_ipsec_set_pf_sa(adapter, xs);
		अगर (ret < 0)
			वापस ret;
		tsa.pfsa = ret;

		/* the preparations worked, so save the info */
		स_नकल(&ipsec->tx_tbl[sa_idx], &tsa, माप(tsa));

		xs->xso.offload_handle = sa_idx + IXGBE_IPSEC_BASE_TX_INDEX;

		ipsec->num_tx_sa++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbevf_ipsec_del_sa - clear out this specअगरic SA
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल व्योम ixgbevf_ipsec_del_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा net_device *dev = xs->xso.dev;
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;
	u16 sa_idx;

	अगर (xs->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_RX_INDEX;

		अगर (!ipsec->rx_tbl[sa_idx].used) अणु
			netdev_err(dev, "Invalid Rx SA selected sa_idx=%d offload_handle=%lu\n",
				   sa_idx, xs->xso.offload_handle);
			वापस;
		पूर्ण

		ixgbevf_ipsec_del_pf_sa(adapter, ipsec->rx_tbl[sa_idx].pfsa);
		hash_del_rcu(&ipsec->rx_tbl[sa_idx].hlist);
		स_रखो(&ipsec->rx_tbl[sa_idx], 0, माप(काष्ठा rx_sa));
		ipsec->num_rx_sa--;
	पूर्ण अन्यथा अणु
		sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_TX_INDEX;

		अगर (!ipsec->tx_tbl[sa_idx].used) अणु
			netdev_err(dev, "Invalid Tx SA selected sa_idx=%d offload_handle=%lu\n",
				   sa_idx, xs->xso.offload_handle);
			वापस;
		पूर्ण

		ixgbevf_ipsec_del_pf_sa(adapter, ipsec->tx_tbl[sa_idx].pfsa);
		स_रखो(&ipsec->tx_tbl[sa_idx], 0, माप(काष्ठा tx_sa));
		ipsec->num_tx_sa--;
	पूर्ण
पूर्ण

/**
 * ixgbevf_ipsec_offload_ok - can this packet use the xfrm hw offload
 * @skb: current data packet
 * @xs: poपूर्णांकer to transक्रमmer state काष्ठा
 **/
अटल bool ixgbevf_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *xs)
अणु
	अगर (xs->props.family == AF_INET) अणु
		/* Offload with IPv4 options is not supported yet */
		अगर (ip_hdr(skb)->ihl != 5)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Offload with IPv6 extension headers is not support yet */
		अगर (ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops ixgbevf_xfrmdev_ops = अणु
	.xकरो_dev_state_add = ixgbevf_ipsec_add_sa,
	.xकरो_dev_state_delete = ixgbevf_ipsec_del_sa,
	.xकरो_dev_offload_ok = ixgbevf_ipsec_offload_ok,
पूर्ण;

/**
 * ixgbevf_ipsec_tx - setup Tx flags क्रम IPsec offload
 * @tx_ring: outgoing context
 * @first: current data packet
 * @itd: ipsec Tx data क्रम later use in building context descriptor
 **/
पूर्णांक ixgbevf_ipsec_tx(काष्ठा ixgbevf_ring *tx_ring,
		     काष्ठा ixgbevf_tx_buffer *first,
		     काष्ठा ixgbevf_ipsec_tx_data *itd)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(tx_ring->netdev);
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_state *xs;
	काष्ठा sec_path *sp;
	काष्ठा tx_sa *tsa;
	u16 sa_idx;

	sp = skb_sec_path(first->skb);
	अगर (unlikely(!sp->len)) अणु
		netdev_err(tx_ring->netdev, "%s: no xfrm state len = %d\n",
			   __func__, sp->len);
		वापस 0;
	पूर्ण

	xs = xfrm_input_state(first->skb);
	अगर (unlikely(!xs)) अणु
		netdev_err(tx_ring->netdev, "%s: no xfrm_input_state() xs = %p\n",
			   __func__, xs);
		वापस 0;
	पूर्ण

	sa_idx = xs->xso.offload_handle - IXGBE_IPSEC_BASE_TX_INDEX;
	अगर (unlikely(sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT)) अणु
		netdev_err(tx_ring->netdev, "%s: bad sa_idx=%d handle=%lu\n",
			   __func__, sa_idx, xs->xso.offload_handle);
		वापस 0;
	पूर्ण

	tsa = &ipsec->tx_tbl[sa_idx];
	अगर (unlikely(!tsa->used)) अणु
		netdev_err(tx_ring->netdev, "%s: unused sa_idx=%d\n",
			   __func__, sa_idx);
		वापस 0;
	पूर्ण

	itd->pfsa = tsa->pfsa - IXGBE_IPSEC_BASE_TX_INDEX;

	first->tx_flags |= IXGBE_TX_FLAGS_IPSEC | IXGBE_TX_FLAGS_CSUM;

	अगर (xs->id.proto == IPPROTO_ESP) अणु
		itd->flags |= IXGBE_ADVTXD_TUCMD_IPSEC_TYPE_ESP |
			      IXGBE_ADVTXD_TUCMD_L4T_TCP;
		अगर (first->protocol == htons(ETH_P_IP))
			itd->flags |= IXGBE_ADVTXD_TUCMD_IPV4;

		/* The actual trailer length is authlen (16 bytes) plus
		 * 2 bytes क्रम the proto and the padlen values, plus
		 * padlen bytes of padding.  This ends up not the same
		 * as the अटल value found in xs->props.trailer_len (21).
		 *
		 * ... but अगर we're doing GSO, don't bother as the stack
		 * करोesn't add a trailer क्रम those.
		 */
		अगर (!skb_is_gso(first->skb)) अणु
			/* The "correct" way to get the auth length would be
			 * to use
			 *    authlen = crypto_aead_authsize(xs->data);
			 * but since we know we only have one size to worry
			 * about * we can let the compiler use the स्थिरant
			 * and save us a few CPU cycles.
			 */
			स्थिर पूर्णांक authlen = IXGBE_IPSEC_AUTH_BITS / 8;
			काष्ठा sk_buff *skb = first->skb;
			u8 padlen;
			पूर्णांक ret;

			ret = skb_copy_bits(skb, skb->len - (authlen + 2),
					    &padlen, 1);
			अगर (unlikely(ret))
				वापस 0;
			itd->trailer_len = authlen + 2 + padlen;
		पूर्ण
	पूर्ण
	अगर (tsa->encrypt)
		itd->flags |= IXGBE_ADVTXD_TUCMD_IPSEC_ENCRYPT_EN;

	वापस 1;
पूर्ण

/**
 * ixgbevf_ipsec_rx - decode IPsec bits from Rx descriptor
 * @rx_ring: receiving ring
 * @rx_desc: receive data descriptor
 * @skb: current data packet
 *
 * Determine अगर there was an IPsec encapsulation noticed, and अगर so set up
 * the resulting status क्रम later in the receive stack.
 **/
व्योम ixgbevf_ipsec_rx(काष्ठा ixgbevf_ring *rx_ring,
		      जोड़ ixgbe_adv_rx_desc *rx_desc,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(rx_ring->netdev);
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;
	__le16 ipsec_pkt_types = cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_AH |
					     IXGBE_RXDADV_PKTTYPE_IPSEC_ESP);
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;
	काष्ठा xfrm_offload *xo = शून्य;
	काष्ठा xfrm_state *xs = शून्य;
	काष्ठा ipv6hdr *ip6 = शून्य;
	काष्ठा iphdr *ip4 = शून्य;
	काष्ठा sec_path *sp;
	व्योम *daddr;
	__be32 spi;
	u8 *c_hdr;
	u8 proto;

	/* Find the IP and crypto headers in the data.
	 * We can assume no VLAN header in the way, b/c the
	 * hw won't recognize the IPsec packet and anyway the
	 * currently VLAN device करोesn't support xfrm offload.
	 */
	अगर (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPV4)) अणु
		ip4 = (काष्ठा iphdr *)(skb->data + ETH_HLEN);
		daddr = &ip4->daddr;
		c_hdr = (u8 *)ip4 + ip4->ihl * 4;
	पूर्ण अन्यथा अगर (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPV6)) अणु
		ip6 = (काष्ठा ipv6hdr *)(skb->data + ETH_HLEN);
		daddr = &ip6->daddr;
		c_hdr = (u8 *)ip6 + माप(काष्ठा ipv6hdr);
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	चयन (pkt_info & ipsec_pkt_types) अणु
	हाल cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_AH):
		spi = ((काष्ठा ip_auth_hdr *)c_hdr)->spi;
		proto = IPPROTO_AH;
		अवरोध;
	हाल cpu_to_le16(IXGBE_RXDADV_PKTTYPE_IPSEC_ESP):
		spi = ((काष्ठा ip_esp_hdr *)c_hdr)->spi;
		proto = IPPROTO_ESP;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	xs = ixgbevf_ipsec_find_rx_state(ipsec, daddr, proto, spi, !!ip4);
	अगर (unlikely(!xs))
		वापस;

	sp = secpath_set(skb);
	अगर (unlikely(!sp))
		वापस;

	sp->xvec[sp->len++] = xs;
	sp->olen++;
	xo = xfrm_offload(skb);
	xo->flags = CRYPTO_DONE;
	xo->status = CRYPTO_SUCCESS;

	adapter->rx_ipsec++;
पूर्ण

/**
 * ixgbevf_init_ipsec_offload - initialize रेजिस्टरs क्रम IPsec operation
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbevf_init_ipsec_offload(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbevf_ipsec *ipsec;
	माप_प्रकार size;

	चयन (adapter->hw.api_version) अणु
	हाल ixgbe_mbox_api_14:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ipsec = kzalloc(माप(*ipsec), GFP_KERNEL);
	अगर (!ipsec)
		जाओ err1;
	hash_init(ipsec->rx_sa_list);

	size = माप(काष्ठा rx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->rx_tbl = kzalloc(size, GFP_KERNEL);
	अगर (!ipsec->rx_tbl)
		जाओ err2;

	size = माप(काष्ठा tx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->tx_tbl = kzalloc(size, GFP_KERNEL);
	अगर (!ipsec->tx_tbl)
		जाओ err2;

	ipsec->num_rx_sa = 0;
	ipsec->num_tx_sa = 0;

	adapter->ipsec = ipsec;

	adapter->netdev->xfrmdev_ops = &ixgbevf_xfrmdev_ops;

#घोषणा IXGBEVF_ESP_FEATURES	(NETIF_F_HW_ESP | \
				 NETIF_F_HW_ESP_TX_CSUM | \
				 NETIF_F_GSO_ESP)

	adapter->netdev->features |= IXGBEVF_ESP_FEATURES;
	adapter->netdev->hw_enc_features |= IXGBEVF_ESP_FEATURES;

	वापस;

err2:
	kमुक्त(ipsec->rx_tbl);
	kमुक्त(ipsec->tx_tbl);
	kमुक्त(ipsec);
err1:
	netdev_err(adapter->netdev, "Unable to allocate memory for SA tables");
पूर्ण

/**
 * ixgbevf_stop_ipsec_offload - tear करोwn the IPsec offload
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbevf_stop_ipsec_offload(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbevf_ipsec *ipsec = adapter->ipsec;

	adapter->ipsec = शून्य;
	अगर (ipsec) अणु
		kमुक्त(ipsec->rx_tbl);
		kमुक्त(ipsec->tx_tbl);
		kमुक्त(ipsec);
	पूर्ण
पूर्ण
