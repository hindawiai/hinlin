<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 EIA Electronics,
//                         Pieter Beyens <pieter.beyens@eia.be>
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2018 Protonic,
//                         Robin van der Gracht <robin@protonic.nl>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

/* Core of can-j1939 that links j1939 to CAN. */

#समावेश <linux/can/can-ml.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/module.h>

#समावेश "j1939-priv.h"

MODULE_DESCRIPTION("PF_CAN SAE J1939");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("EIA Electronics (Kurt Van Dijck & Pieter Beyens)");
MODULE_ALIAS("can-proto-" __stringअगरy(CAN_J1939));

/* LOWLEVEL CAN पूर्णांकerface */

/* CAN_HDR: #bytes beक्रमe can_frame data part */
#घोषणा J1939_CAN_HDR (दुरत्व(काष्ठा can_frame, data))

/* CAN_FTR: #bytes beyond data part */
#घोषणा J1939_CAN_FTR (माप(काष्ठा can_frame) - J1939_CAN_HDR - \
		 माप(((काष्ठा can_frame *)0)->data))

/* lowest layer */
अटल व्योम j1939_can_recv(काष्ठा sk_buff *iskb, व्योम *data)
अणु
	काष्ठा j1939_priv *priv = data;
	काष्ठा sk_buff *skb;
	काष्ठा j1939_sk_buff_cb *skcb, *iskcb;
	काष्ठा can_frame *cf;

	/* create a copy of the skb
	 * j1939 only delivers the real data bytes,
	 * the header goes पूर्णांकo sockaddr.
	 * j1939 may not touch the incoming skb in such way
	 */
	skb = skb_clone(iskb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	j1939_priv_get(priv);
	can_skb_set_owner(skb, iskb->sk);

	/* get a poपूर्णांकer to the header of the skb
	 * the skb payload (poपूर्णांकer) is moved, so that the next skb_data
	 * वापसs the actual payload
	 */
	cf = (व्योम *)skb->data;
	skb_pull(skb, J1939_CAN_HDR);

	/* fix length, set to dlc, with 8 maximum */
	skb_trim(skb, min_t(uपूर्णांक8_t, cf->len, 8));

	/* set addr */
	skcb = j1939_skb_to_cb(skb);
	स_रखो(skcb, 0, माप(*skcb));

	iskcb = j1939_skb_to_cb(iskb);
	skcb->tskey = iskcb->tskey;
	skcb->priority = (cf->can_id >> 26) & 0x7;
	skcb->addr.sa = cf->can_id;
	skcb->addr.pgn = (cf->can_id >> 8) & J1939_PGN_MAX;
	/* set शेष message type */
	skcb->addr.type = J1939_TP;
	अगर (j1939_pgn_is_pdu1(skcb->addr.pgn)) अणु
		/* Type 1: with destination address */
		skcb->addr.da = skcb->addr.pgn;
		/* normalize pgn: strip dst address */
		skcb->addr.pgn &= 0x3ff00;
	पूर्ण अन्यथा अणु
		/* set broadcast address */
		skcb->addr.da = J1939_NO_ADDR;
	पूर्ण

	/* update localflags */
	पढ़ो_lock_bh(&priv->lock);
	अगर (j1939_address_is_unicast(skcb->addr.sa) &&
	    priv->ents[skcb->addr.sa].nusers)
		skcb->flags |= J1939_ECU_LOCAL_SRC;
	अगर (j1939_address_is_unicast(skcb->addr.da) &&
	    priv->ents[skcb->addr.da].nusers)
		skcb->flags |= J1939_ECU_LOCAL_DST;
	पढ़ो_unlock_bh(&priv->lock);

	/* deliver पूर्णांकo the j1939 stack ... */
	j1939_ac_recv(priv, skb);

	अगर (j1939_tp_recv(priv, skb))
		/* this means the transport layer processed the message */
		जाओ करोne;

	j1939_simple_recv(priv, skb);
	j1939_sk_recv(priv, skb);
 करोne:
	j1939_priv_put(priv);
	kमुक्त_skb(skb);
पूर्ण

/* NETDEV MANAGEMENT */

/* values क्रम can_rx_(un)रेजिस्टर */
#घोषणा J1939_CAN_ID CAN_EFF_FLAG
#घोषणा J1939_CAN_MASK (CAN_EFF_FLAG | CAN_RTR_FLAG)

अटल DEFINE_SPINLOCK(j1939_netdev_lock);

अटल काष्ठा j1939_priv *j1939_priv_create(काष्ठा net_device *ndev)
अणु
	काष्ठा j1939_priv *priv;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस शून्य;

	rwlock_init(&priv->lock);
	INIT_LIST_HEAD(&priv->ecus);
	priv->ndev = ndev;
	kref_init(&priv->kref);
	kref_init(&priv->rx_kref);
	dev_hold(ndev);

	netdev_dbg(priv->ndev, "%s : 0x%p\n", __func__, priv);

	वापस priv;
पूर्ण

अटल अंतरभूत व्योम j1939_priv_set(काष्ठा net_device *ndev,
				  काष्ठा j1939_priv *priv)
अणु
	काष्ठा can_ml_priv *can_ml = can_get_ml_priv(ndev);

	can_ml->j1939_priv = priv;
पूर्ण

अटल व्योम __j1939_priv_release(काष्ठा kref *kref)
अणु
	काष्ठा j1939_priv *priv = container_of(kref, काष्ठा j1939_priv, kref);
	काष्ठा net_device *ndev = priv->ndev;

	netdev_dbg(priv->ndev, "%s: 0x%p\n", __func__, priv);

	WARN_ON_ONCE(!list_empty(&priv->active_session_list));
	WARN_ON_ONCE(!list_empty(&priv->ecus));
	WARN_ON_ONCE(!list_empty(&priv->j1939_socks));

	dev_put(ndev);
	kमुक्त(priv);
पूर्ण

व्योम j1939_priv_put(काष्ठा j1939_priv *priv)
अणु
	kref_put(&priv->kref, __j1939_priv_release);
पूर्ण

व्योम j1939_priv_get(काष्ठा j1939_priv *priv)
अणु
	kref_get(&priv->kref);
पूर्ण

अटल पूर्णांक j1939_can_rx_रेजिस्टर(काष्ठा j1939_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक ret;

	j1939_priv_get(priv);
	ret = can_rx_रेजिस्टर(dev_net(ndev), ndev, J1939_CAN_ID, J1939_CAN_MASK,
			      j1939_can_recv, priv, "j1939", शून्य);
	अगर (ret < 0) अणु
		j1939_priv_put(priv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम j1939_can_rx_unरेजिस्टर(काष्ठा j1939_priv *priv)
अणु
	काष्ठा net_device *ndev = priv->ndev;

	can_rx_unरेजिस्टर(dev_net(ndev), ndev, J1939_CAN_ID, J1939_CAN_MASK,
			  j1939_can_recv, priv);

	j1939_priv_put(priv);
पूर्ण

अटल व्योम __j1939_rx_release(काष्ठा kref *kref)
	__releases(&j1939_netdev_lock)
अणु
	काष्ठा j1939_priv *priv = container_of(kref, काष्ठा j1939_priv,
					       rx_kref);

	j1939_can_rx_unरेजिस्टर(priv);
	j1939_ecu_unmap_all(priv);
	j1939_priv_set(priv->ndev, शून्य);
	spin_unlock(&j1939_netdev_lock);
पूर्ण

/* get poपूर्णांकer to priv without increasing ref counter */
अटल अंतरभूत काष्ठा j1939_priv *j1939_ndev_to_priv(काष्ठा net_device *ndev)
अणु
	काष्ठा can_ml_priv *can_ml = can_get_ml_priv(ndev);

	वापस can_ml->j1939_priv;
पूर्ण

अटल काष्ठा j1939_priv *j1939_priv_get_by_ndev_locked(काष्ठा net_device *ndev)
अणु
	काष्ठा j1939_priv *priv;

	lockdep_निश्चित_held(&j1939_netdev_lock);

	priv = j1939_ndev_to_priv(ndev);
	अगर (priv)
		j1939_priv_get(priv);

	वापस priv;
पूर्ण

अटल काष्ठा j1939_priv *j1939_priv_get_by_ndev(काष्ठा net_device *ndev)
अणु
	काष्ठा j1939_priv *priv;

	spin_lock(&j1939_netdev_lock);
	priv = j1939_priv_get_by_ndev_locked(ndev);
	spin_unlock(&j1939_netdev_lock);

	वापस priv;
पूर्ण

काष्ठा j1939_priv *j1939_netdev_start(काष्ठा net_device *ndev)
अणु
	काष्ठा j1939_priv *priv, *priv_new;
	पूर्णांक ret;

	priv = j1939_priv_get_by_ndev(ndev);
	अगर (priv) अणु
		kref_get(&priv->rx_kref);
		वापस priv;
	पूर्ण

	priv = j1939_priv_create(ndev);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	j1939_tp_init(priv);
	spin_lock_init(&priv->j1939_socks_lock);
	INIT_LIST_HEAD(&priv->j1939_socks);

	spin_lock(&j1939_netdev_lock);
	priv_new = j1939_priv_get_by_ndev_locked(ndev);
	अगर (priv_new) अणु
		/* Someone was faster than us, use their priv and roll
		 * back our's.
		 */
		spin_unlock(&j1939_netdev_lock);
		dev_put(ndev);
		kमुक्त(priv);
		kref_get(&priv_new->rx_kref);
		वापस priv_new;
	पूर्ण
	j1939_priv_set(ndev, priv);
	spin_unlock(&j1939_netdev_lock);

	ret = j1939_can_rx_रेजिस्टर(priv);
	अगर (ret < 0)
		जाओ out_priv_put;

	वापस priv;

 out_priv_put:
	j1939_priv_set(ndev, शून्य);
	dev_put(ndev);
	kमुक्त(priv);

	वापस ERR_PTR(ret);
पूर्ण

व्योम j1939_netdev_stop(काष्ठा j1939_priv *priv)
अणु
	kref_put_lock(&priv->rx_kref, __j1939_rx_release, &j1939_netdev_lock);
	j1939_priv_put(priv);
पूर्ण

पूर्णांक j1939_send_one(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret, dlc;
	canid_t canid;
	काष्ठा j1939_sk_buff_cb *skcb = j1939_skb_to_cb(skb);
	काष्ठा can_frame *cf;

	/* apply sanity checks */
	अगर (j1939_pgn_is_pdu1(skcb->addr.pgn))
		skcb->addr.pgn &= J1939_PGN_PDU1_MAX;
	अन्यथा
		skcb->addr.pgn &= J1939_PGN_MAX;

	अगर (skcb->priority > 7)
		skcb->priority = 6;

	ret = j1939_ac_fixup(priv, skb);
	अगर (unlikely(ret))
		जाओ failed;
	dlc = skb->len;

	/* re-claim the CAN_HDR from the SKB */
	cf = skb_push(skb, J1939_CAN_HDR);

	/* make it a full can frame again */
	skb_put(skb, J1939_CAN_FTR + (8 - dlc));

	canid = CAN_EFF_FLAG |
		(skcb->priority << 26) |
		(skcb->addr.pgn << 8) |
		skcb->addr.sa;
	अगर (j1939_pgn_is_pdu1(skcb->addr.pgn))
		canid |= skcb->addr.da << 8;

	cf->can_id = canid;
	cf->len = dlc;

	वापस can_send(skb, 1);

 failed:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक j1939_netdev_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ msg, व्योम *data)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(data);
	काष्ठा can_ml_priv *can_ml = can_get_ml_priv(ndev);
	काष्ठा j1939_priv *priv;

	अगर (!can_ml)
		जाओ notअगरy_करोne;

	priv = j1939_priv_get_by_ndev(ndev);
	अगर (!priv)
		जाओ notअगरy_करोne;

	चयन (msg) अणु
	हाल NETDEV_DOWN:
		j1939_cancel_active_session(priv, शून्य);
		j1939_sk_netdev_event_netकरोwn(priv);
		j1939_ecu_unmap_all(priv);
		अवरोध;
	पूर्ण

	j1939_priv_put(priv);

notअगरy_करोne:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block j1939_netdev_notअगरier = अणु
	.notअगरier_call = j1939_netdev_notअगरy,
पूर्ण;

/* MODULE पूर्णांकerface */
अटल __init पूर्णांक j1939_module_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("can: SAE J1939\n");

	ret = रेजिस्टर_netdevice_notअगरier(&j1939_netdev_notअगरier);
	अगर (ret)
		जाओ fail_notअगरier;

	ret = can_proto_रेजिस्टर(&j1939_can_proto);
	अगर (ret < 0) अणु
		pr_err("can: registration of j1939 protocol failed\n");
		जाओ fail_sk;
	पूर्ण

	वापस 0;

 fail_sk:
	unरेजिस्टर_netdevice_notअगरier(&j1939_netdev_notअगरier);
 fail_notअगरier:
	वापस ret;
पूर्ण

अटल __निकास व्योम j1939_module_निकास(व्योम)
अणु
	can_proto_unरेजिस्टर(&j1939_can_proto);

	unरेजिस्टर_netdevice_notअगरier(&j1939_netdev_notअगरier);
पूर्ण

module_init(j1939_module_init);
module_निकास(j1939_module_निकास);
