<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2010-2011 EIA Electronics,
//                         Pieter Beyens <pieter.beyens@eia.be>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

/* J1939 Address Claiming.
 * Address Claiming in the kernel
 * - keeps track of the AC states of ECU's,
 * - resolves NAME<=>SA taking पूर्णांकo account the AC states of ECU's.
 *
 * All Address Claim msgs (including host-originated msg) are processed
 * at the receive path (a sent msg is always received again via CAN echo).
 * As such, the processing of AC msgs is करोne in the order on which msgs
 * are sent on the bus.
 *
 * This module करोesn't send msgs itself (e.g. replies on Address Claims),
 * this is the responsibility of a user space application or daemon.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>

#समावेश "j1939-priv.h"

अटल अंतरभूत name_t j1939_skb_to_name(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस le64_to_cpup((__le64 *)skb->data);
पूर्ण

अटल अंतरभूत bool j1939_ac_msg_is_request(काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	पूर्णांक req_pgn;

	अगर (skb->len < 3 || skcb->addr.pgn != J1939_PGN_REQUEST)
		वापस false;

	req_pgn = skb->data[0] | (skb->data[1] << 8) | (skb->data[2] << 16);

	वापस req_pgn == J1939_PGN_ADDRESS_CLAIMED;
पूर्ण

अटल पूर्णांक j1939_ac_verअगरy_outgoing(काष्ठा j1939_priv *priv,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);

	अगर (skb->len != 8) अणु
		netdev_notice(priv->ndev, "tx address claim with dlc %i\n",
			      skb->len);
		वापस -EPROTO;
	पूर्ण

	अगर (skcb->addr.src_name != j1939_skb_to_name(skb)) अणु
		netdev_notice(priv->ndev, "tx address claim with different name\n");
		वापस -EPROTO;
	पूर्ण

	अगर (skcb->addr.sa == J1939_NO_ADDR) अणु
		netdev_notice(priv->ndev, "tx address claim with broadcast sa\n");
		वापस -EPROTO;
	पूर्ण

	/* ac must always be a broadcast */
	अगर (skcb->addr.dst_name || skcb->addr.da != J1939_NO_ADDR) अणु
		netdev_notice(priv->ndev, "tx address claim with dest, not broadcast\n");
		वापस -EPROTO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक j1939_ac_fixup(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	पूर्णांक ret;
	u8 addr;

	/* network mgmt: address claiming msgs */
	अगर (skcb->addr.pgn == J1939_PGN_ADDRESS_CLAIMED) अणु
		काष्ठा j1939_ecu *ecu;

		ret = j1939_ac_verअगरy_outgoing(priv, skb);
		/* वापस both when failure & when successful */
		अगर (ret < 0)
			वापस ret;
		ecu = j1939_ecu_get_by_name(priv, skcb->addr.src_name);
		अगर (!ecu)
			वापस -ENODEV;

		अगर (ecu->addr != skcb->addr.sa)
			/* hold further traffic क्रम ecu, हटाओ from parent */
			j1939_ecu_unmap(ecu);
		j1939_ecu_put(ecu);
	पूर्ण अन्यथा अगर (skcb->addr.src_name) अणु
		/* assign source address */
		addr = j1939_name_to_addr(priv, skcb->addr.src_name);
		अगर (!j1939_address_is_unicast(addr) &&
		    !j1939_ac_msg_is_request(skb)) अणु
			netdev_notice(priv->ndev, "tx drop: invalid sa for name 0x%016llx\n",
				      skcb->addr.src_name);
			वापस -EADDRNOTAVAIL;
		पूर्ण
		skcb->addr.sa = addr;
	पूर्ण

	/* assign destination address */
	अगर (skcb->addr.dst_name) अणु
		addr = j1939_name_to_addr(priv, skcb->addr.dst_name);
		अगर (!j1939_address_is_unicast(addr)) अणु
			netdev_notice(priv->ndev, "tx drop: invalid da for name 0x%016llx\n",
				      skcb->addr.dst_name);
			वापस -EADDRNOTAVAIL;
		पूर्ण
		skcb->addr.da = addr;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम j1939_ac_process(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_ecu *ecu, *prev;
	name_t name;

	अगर (skb->len != 8) अणु
		netdev_notice(priv->ndev, "rx address claim with wrong dlc %i\n",
			      skb->len);
		वापस;
	पूर्ण

	name = j1939_skb_to_name(skb);
	skcb->addr.src_name = name;
	अगर (!name) अणु
		netdev_notice(priv->ndev, "rx address claim without name\n");
		वापस;
	पूर्ण

	अगर (!j1939_address_is_valid(skcb->addr.sa)) अणु
		netdev_notice(priv->ndev, "rx address claim with broadcast sa\n");
		वापस;
	पूर्ण

	ग_लिखो_lock_bh(&priv->lock);

	/* Few words on the ECU ref counting:
	 *
	 * First we get an ECU handle, either with
	 * j1939_ecu_get_by_name_locked() (increments the ref counter)
	 * or j1939_ecu_create_locked() (initializes an ECU object
	 * with a ref counter of 1).
	 *
	 * j1939_ecu_unmap_locked() will decrement the ref counter,
	 * but only अगर the ECU was mapped beक्रमe. So "ecu" still
	 * beदीर्घs to us.
	 *
	 * j1939_ecu_समयr_start() will increment the ref counter
	 * beक्रमe it starts the समयr, so we can put the ecu when
	 * leaving this function.
	 */
	ecu = j1939_ecu_get_by_name_locked(priv, name);
	अगर (!ecu && j1939_address_is_unicast(skcb->addr.sa))
		ecu = j1939_ecu_create_locked(priv, name);

	अगर (IS_ERR_OR_शून्य(ecu))
		जाओ out_unlock_bh;

	/* cancel pending (previous) address claim */
	j1939_ecu_समयr_cancel(ecu);

	अगर (j1939_address_is_idle(skcb->addr.sa)) अणु
		j1939_ecu_unmap_locked(ecu);
		जाओ out_ecu_put;
	पूर्ण

	/* save new addr */
	अगर (ecu->addr != skcb->addr.sa)
		j1939_ecu_unmap_locked(ecu);
	ecu->addr = skcb->addr.sa;

	prev = j1939_ecu_get_by_addr_locked(priv, skcb->addr.sa);
	अगर (prev) अणु
		अगर (ecu->name > prev->name) अणु
			j1939_ecu_unmap_locked(ecu);
			j1939_ecu_put(prev);
			जाओ out_ecu_put;
		पूर्ण अन्यथा अणु
			/* kick prev अगर less or equal */
			j1939_ecu_unmap_locked(prev);
			j1939_ecu_put(prev);
		पूर्ण
	पूर्ण

	j1939_ecu_समयr_start(ecu);
 out_ecu_put:
	j1939_ecu_put(ecu);
 out_unlock_bh:
	ग_लिखो_unlock_bh(&priv->lock);
पूर्ण

व्योम j1939_ac_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा j1939_ecu *ecu;

	/* network mgmt */
	अगर (skcb->addr.pgn == J1939_PGN_ADDRESS_CLAIMED) अणु
		j1939_ac_process(priv, skb);
	पूर्ण अन्यथा अगर (j1939_address_is_unicast(skcb->addr.sa)) अणु
		/* assign source name */
		ecu = j1939_ecu_get_by_addr(priv, skcb->addr.sa);
		अगर (ecu) अणु
			skcb->addr.src_name = ecu->name;
			j1939_ecu_put(ecu);
		पूर्ण
	पूर्ण

	/* assign destination name */
	ecu = j1939_ecu_get_by_addr(priv, skcb->addr.da);
	अगर (ecu) अणु
		skcb->addr.dst_name = ecu->name;
		j1939_ecu_put(ecu);
	पूर्ण
पूर्ण
