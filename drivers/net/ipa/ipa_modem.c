<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2014-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_rmnet.h>
#समावेश <linux/remoteproc/qcom_rproc.h>

#समावेश "ipa.h"
#समावेश "ipa_data.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_table.h"
#समावेश "ipa_mem.h"
#समावेश "ipa_modem.h"
#समावेश "ipa_smp2p.h"
#समावेश "ipa_qmi.h"

#घोषणा IPA_NETDEV_NAME		"rmnet_ipa%d"
#घोषणा IPA_NETDEV_TAILROOM	0	/* क्रम padding by mux layer */
#घोषणा IPA_NETDEV_TIMEOUT	10	/* seconds */

क्रमागत ipa_modem_state अणु
	IPA_MODEM_STATE_STOPPED	= 0,
	IPA_MODEM_STATE_STARTING,
	IPA_MODEM_STATE_RUNNING,
	IPA_MODEM_STATE_STOPPING,
पूर्ण;

/** काष्ठा ipa_priv - IPA network device निजी data */
काष्ठा ipa_priv अणु
	काष्ठा ipa *ipa;
पूर्ण;

/** ipa_खोलो() - Opens the modem network पूर्णांकerface */
अटल पूर्णांक ipa_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ipa_priv *priv = netdev_priv(netdev);
	काष्ठा ipa *ipa = priv->ipa;
	पूर्णांक ret;

	ret = ipa_endpoपूर्णांक_enable_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
	अगर (ret)
		वापस ret;
	ret = ipa_endpoपूर्णांक_enable_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]);
	अगर (ret)
		जाओ err_disable_tx;

	netअगर_start_queue(netdev);

	वापस 0;

err_disable_tx:
	ipa_endpoपूर्णांक_disable_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);

	वापस ret;
पूर्ण

/** ipa_stop() - Stops the modem network पूर्णांकerface. */
अटल पूर्णांक ipa_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा ipa_priv *priv = netdev_priv(netdev);
	काष्ठा ipa *ipa = priv->ipa;

	netअगर_stop_queue(netdev);

	ipa_endpoपूर्णांक_disable_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]);
	ipa_endpoपूर्णांक_disable_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);

	वापस 0;
पूर्ण

/** ipa_start_xmit() - Transmits an skb.
 * @skb: skb to be transmitted
 * @dev: network device
 *
 * Return codes:
 * NETDEV_TX_OK: Success
 * NETDEV_TX_BUSY: Error जबतक transmitting the skb. Try again later
 */
अटल पूर्णांक ipa_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा net_device_stats *stats = &netdev->stats;
	काष्ठा ipa_priv *priv = netdev_priv(netdev);
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा ipa *ipa = priv->ipa;
	u32 skb_len = skb->len;
	पूर्णांक ret;

	अगर (!skb_len)
		जाओ err_drop_skb;

	endpoपूर्णांक = ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX];
	अगर (endpoपूर्णांक->data->qmap && skb->protocol != htons(ETH_P_MAP))
		जाओ err_drop_skb;

	ret = ipa_endpoपूर्णांक_skb_tx(endpoपूर्णांक, skb);
	अगर (ret) अणु
		अगर (ret != -E2BIG)
			वापस NETDEV_TX_BUSY;
		जाओ err_drop_skb;
	पूर्ण

	stats->tx_packets++;
	stats->tx_bytes += skb_len;

	वापस NETDEV_TX_OK;

err_drop_skb:
	dev_kमुक्त_skb_any(skb);
	stats->tx_dropped++;

	वापस NETDEV_TX_OK;
पूर्ण

व्योम ipa_modem_skb_rx(काष्ठा net_device *netdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device_stats *stats = &netdev->stats;

	अगर (skb) अणु
		skb->dev = netdev;
		skb->protocol = htons(ETH_P_MAP);
		stats->rx_packets++;
		stats->rx_bytes += skb->len;

		(व्योम)netअगर_receive_skb(skb);
	पूर्ण अन्यथा अणु
		stats->rx_dropped++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops ipa_modem_ops = अणु
	.nकरो_खोलो	= ipa_खोलो,
	.nकरो_stop	= ipa_stop,
	.nकरो_start_xmit	= ipa_start_xmit,
पूर्ण;

/** ipa_modem_netdev_setup() - netdev setup function क्रम the modem */
अटल व्योम ipa_modem_netdev_setup(काष्ठा net_device *netdev)
अणु
	netdev->netdev_ops = &ipa_modem_ops;
	ether_setup(netdev);
	/* No header ops (override value set by ether_setup()) */
	netdev->header_ops = शून्य;
	netdev->type = ARPHRD_RAWIP;
	netdev->hard_header_len = 0;
	netdev->max_mtu = IPA_MTU;
	netdev->mtu = netdev->max_mtu;
	netdev->addr_len = 0;
	netdev->flags &= ~(IFF_BROADCAST | IFF_MULTICAST);
	/* The endpoपूर्णांक is configured क्रम QMAP */
	netdev->needed_headroom = माप(काष्ठा rmnet_map_header);
	netdev->needed_tailroom = IPA_NETDEV_TAILROOM;
	netdev->watchकरोg_समयo = IPA_NETDEV_TIMEOUT * HZ;
	netdev->hw_features = NETIF_F_SG;
पूर्ण

/** ipa_modem_suspend() - suspend callback
 * @netdev:	Network device
 *
 * Suspend the modem's endpoपूर्णांकs.
 */
व्योम ipa_modem_suspend(काष्ठा net_device *netdev)
अणु
	काष्ठा ipa_priv *priv = netdev_priv(netdev);
	काष्ठा ipa *ipa = priv->ipa;

	netअगर_stop_queue(netdev);

	ipa_endpoपूर्णांक_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]);
	ipa_endpoपूर्णांक_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
पूर्ण

/** ipa_modem_resume() - resume callback क्रम runसमय_pm
 * @dev: poपूर्णांकer to device
 *
 * Resume the modem's endpoपूर्णांकs.
 */
व्योम ipa_modem_resume(काष्ठा net_device *netdev)
अणु
	काष्ठा ipa_priv *priv = netdev_priv(netdev);
	काष्ठा ipa *ipa = priv->ipa;

	ipa_endpoपूर्णांक_resume_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
	ipa_endpoपूर्णांक_resume_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]);

	netअगर_wake_queue(netdev);
पूर्ण

पूर्णांक ipa_modem_start(काष्ठा ipa *ipa)
अणु
	क्रमागत ipa_modem_state state;
	काष्ठा net_device *netdev;
	काष्ठा ipa_priv *priv;
	पूर्णांक ret;

	/* Only attempt to start the modem अगर it's stopped */
	state = atomic_cmpxchg(&ipa->modem_state, IPA_MODEM_STATE_STOPPED,
			       IPA_MODEM_STATE_STARTING);

	/* Silently ignore attempts when running, or when changing state */
	अगर (state != IPA_MODEM_STATE_STOPPED)
		वापस 0;

	netdev = alloc_netdev(माप(काष्ठा ipa_priv), IPA_NETDEV_NAME,
			      NET_NAME_UNKNOWN, ipa_modem_netdev_setup);
	अगर (!netdev) अणु
		ret = -ENOMEM;
		जाओ out_set_state;
	पूर्ण

	SET_NETDEV_DEV(netdev, &ipa->pdev->dev);
	priv = netdev_priv(netdev);
	priv->ipa = ipa;

	ret = रेजिस्टर_netdev(netdev);
	अगर (!ret) अणु
		ipa->modem_netdev = netdev;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]->netdev = netdev;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]->netdev = netdev;
	पूर्ण अन्यथा अणु
		मुक्त_netdev(netdev);
	पूर्ण

out_set_state:
	अगर (ret)
		atomic_set(&ipa->modem_state, IPA_MODEM_STATE_STOPPED);
	अन्यथा
		atomic_set(&ipa->modem_state, IPA_MODEM_STATE_RUNNING);
	smp_mb__after_atomic();

	वापस ret;
पूर्ण

पूर्णांक ipa_modem_stop(काष्ठा ipa *ipa)
अणु
	काष्ठा net_device *netdev = ipa->modem_netdev;
	क्रमागत ipa_modem_state state;

	/* Only attempt to stop the modem अगर it's running */
	state = atomic_cmpxchg(&ipa->modem_state, IPA_MODEM_STATE_RUNNING,
			       IPA_MODEM_STATE_STOPPING);

	/* Silently ignore attempts when alपढ़ोy stopped */
	अगर (state == IPA_MODEM_STATE_STOPPED)
		वापस 0;

	/* If we're somewhere between stopped and starting, we're busy */
	अगर (state != IPA_MODEM_STATE_RUNNING)
		वापस -EBUSY;

	/* Prevent the modem from triggering a call to ipa_setup() */
	ipa_smp2p_disable(ipa);

	/* Stop the queue and disable the endpoपूर्णांकs अगर it's खोलो */
	अगर (netdev) अणु
		(व्योम)ipa_stop(netdev);
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_RX]->netdev = शून्य;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]->netdev = शून्य;
		ipa->modem_netdev = शून्य;
		unरेजिस्टर_netdev(netdev);
		मुक्त_netdev(netdev);
	पूर्ण

	atomic_set(&ipa->modem_state, IPA_MODEM_STATE_STOPPED);
	smp_mb__after_atomic();

	वापस 0;
पूर्ण

/* Treat a "clean" modem stop the same as a crash */
अटल व्योम ipa_modem_crashed(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	पूर्णांक ret;

	ipa_endpoपूर्णांक_modem_छोड़ो_all(ipa, true);

	ipa_endpoपूर्णांक_modem_hol_block_clear_all(ipa);

	ipa_table_reset(ipa, true);

	ret = ipa_table_hash_flush(ipa);
	अगर (ret)
		dev_err(dev, "error %d flushing hash caches\n", ret);

	ret = ipa_endpoपूर्णांक_modem_exception_reset_all(ipa);
	अगर (ret)
		dev_err(dev, "error %d resetting exception endpoint\n", ret);

	ipa_endpoपूर्णांक_modem_छोड़ो_all(ipa, false);

	ret = ipa_modem_stop(ipa);
	अगर (ret)
		dev_err(dev, "error %d stopping modem\n", ret);

	/* Now prepare क्रम the next modem boot */
	ret = ipa_mem_zero_modem(ipa);
	अगर (ret)
		dev_err(dev, "error %d zeroing modem memory regions\n", ret);
पूर्ण

अटल पूर्णांक ipa_modem_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	काष्ठा ipa *ipa = container_of(nb, काष्ठा ipa, nb);
	काष्ठा qcom_ssr_notअगरy_data *notअगरy_data = data;
	काष्ठा device *dev = &ipa->pdev->dev;

	चयन (action) अणु
	हाल QCOM_SSR_BEFORE_POWERUP:
		dev_info(dev, "received modem starting event\n");
		ipa_smp2p_notअगरy_reset(ipa);
		अवरोध;

	हाल QCOM_SSR_AFTER_POWERUP:
		dev_info(dev, "received modem running event\n");
		अवरोध;

	हाल QCOM_SSR_BEFORE_SHUTDOWN:
		dev_info(dev, "received modem %s event\n",
			 notअगरy_data->crashed ? "crashed" : "stopping");
		अगर (ipa->setup_complete)
			ipa_modem_crashed(ipa);
		अवरोध;

	हाल QCOM_SSR_AFTER_SHUTDOWN:
		dev_info(dev, "received modem offline event\n");
		अवरोध;

	शेष:
		dev_err(dev, "received unrecognized event %lu\n", action);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

पूर्णांक ipa_modem_init(काष्ठा ipa *ipa, bool modem_init)
अणु
	वापस ipa_smp2p_init(ipa, modem_init);
पूर्ण

व्योम ipa_modem_निकास(काष्ठा ipa *ipa)
अणु
	ipa_smp2p_निकास(ipa);
पूर्ण

पूर्णांक ipa_modem_config(काष्ठा ipa *ipa)
अणु
	व्योम *notअगरier;

	ipa->nb.notअगरier_call = ipa_modem_notअगरy;

	notअगरier = qcom_रेजिस्टर_ssr_notअगरier("mpss", &ipa->nb);
	अगर (IS_ERR(notअगरier))
		वापस PTR_ERR(notअगरier);

	ipa->notअगरier = notअगरier;

	वापस 0;
पूर्ण

व्योम ipa_modem_deconfig(काष्ठा ipa *ipa)
अणु
	काष्ठा device *dev = &ipa->pdev->dev;
	पूर्णांक ret;

	ret = qcom_unरेजिस्टर_ssr_notअगरier(ipa->notअगरier, &ipa->nb);
	अगर (ret)
		dev_err(dev, "error %d unregistering notifier", ret);

	ipa->notअगरier = शून्य;
	स_रखो(&ipa->nb, 0, माप(ipa->nb));
पूर्ण

पूर्णांक ipa_modem_setup(काष्ठा ipa *ipa)
अणु
	वापस ipa_qmi_setup(ipa);
पूर्ण

व्योम ipa_modem_tearकरोwn(काष्ठा ipa *ipa)
अणु
	ipa_qmi_tearकरोwn(ipa);
पूर्ण
