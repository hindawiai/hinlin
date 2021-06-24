<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 *   redistributing this file, you may करो so under either license.
 *
 *   GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2012 Intel Corporation. All rights reserved.
 *   Copyright (C) 2015 EMC Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary क्रमms, with or without
 *   modअगरication, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copy
 *       notice, this list of conditions and the following disclaimer in
 *       the करोcumentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to enकरोrse or promote products derived
 *       from this software without specअगरic prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * PCIe NTB Network Linux driver
 *
 * Contact Inक्रमmation:
 * Jon Mason <jon.mason@पूर्णांकel.com>
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/ntb.h>
#समावेश <linux/ntb_transport.h>

#घोषणा NTB_NETDEV_VER	"0.7"

MODULE_DESCRIPTION(KBUILD_MODNAME);
MODULE_VERSION(NTB_NETDEV_VER);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel Corporation");

/* Time in usecs क्रम tx resource reaper */
अटल अचिन्हित पूर्णांक tx_समय = 1;

/* Number of descriptors to मुक्त beक्रमe resuming tx */
अटल अचिन्हित पूर्णांक tx_start = 10;

/* Number of descriptors still available beक्रमe stop upper layer tx */
अटल अचिन्हित पूर्णांक tx_stop = 5;

काष्ठा ntb_netdev अणु
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *ndev;
	काष्ठा ntb_transport_qp *qp;
	काष्ठा समयr_list tx_समयr;
पूर्ण;

#घोषणा	NTB_TX_TIMEOUT_MS	1000
#घोषणा	NTB_RXQ_SIZE		100

अटल व्योम ntb_netdev_event_handler(व्योम *data, पूर्णांक link_is_up)
अणु
	काष्ठा net_device *ndev = data;
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);

	netdev_dbg(ndev, "Event %x, Link %x\n", link_is_up,
		   ntb_transport_link_query(dev->qp));

	अगर (link_is_up) अणु
		अगर (ntb_transport_link_query(dev->qp))
			netअगर_carrier_on(ndev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(ndev);
	पूर्ण
पूर्ण

अटल व्योम ntb_netdev_rx_handler(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
				  व्योम *data, पूर्णांक len)
अणु
	काष्ठा net_device *ndev = qp_data;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = data;
	अगर (!skb)
		वापस;

	netdev_dbg(ndev, "%s: %d byte payload received\n", __func__, len);

	अगर (len < 0) अणु
		ndev->stats.rx_errors++;
		ndev->stats.rx_length_errors++;
		जाओ enqueue_again;
	पूर्ण

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, ndev);
	skb->ip_summed = CHECKSUM_NONE;

	अगर (netअगर_rx(skb) == NET_RX_DROP) अणु
		ndev->stats.rx_errors++;
		ndev->stats.rx_dropped++;
	पूर्ण अन्यथा अणु
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += len;
	पूर्ण

	skb = netdev_alloc_skb(ndev, ndev->mtu + ETH_HLEN);
	अगर (!skb) अणु
		ndev->stats.rx_errors++;
		ndev->stats.rx_frame_errors++;
		वापस;
	पूर्ण

enqueue_again:
	rc = ntb_transport_rx_enqueue(qp, skb, skb->data, ndev->mtu + ETH_HLEN);
	अगर (rc) अणु
		dev_kमुक्त_skb(skb);
		ndev->stats.rx_errors++;
		ndev->stats.rx_fअगरo_errors++;
	पूर्ण
पूर्ण

अटल पूर्णांक __ntb_netdev_maybe_stop_tx(काष्ठा net_device *netdev,
				      काष्ठा ntb_transport_qp *qp, पूर्णांक size)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(netdev);

	netअगर_stop_queue(netdev);
	/* Make sure to see the latest value of ntb_transport_tx_मुक्त_entry()
	 * since the queue was last started.
	 */
	smp_mb();

	अगर (likely(ntb_transport_tx_मुक्त_entry(qp) < size)) अणु
		mod_समयr(&dev->tx_समयr, jअगरfies + usecs_to_jअगरfies(tx_समय));
		वापस -EBUSY;
	पूर्ण

	netअगर_start_queue(netdev);
	वापस 0;
पूर्ण

अटल पूर्णांक ntb_netdev_maybe_stop_tx(काष्ठा net_device *ndev,
				    काष्ठा ntb_transport_qp *qp, पूर्णांक size)
अणु
	अगर (netअगर_queue_stopped(ndev) ||
	    (ntb_transport_tx_मुक्त_entry(qp) >= size))
		वापस 0;

	वापस __ntb_netdev_maybe_stop_tx(ndev, qp, size);
पूर्ण

अटल व्योम ntb_netdev_tx_handler(काष्ठा ntb_transport_qp *qp, व्योम *qp_data,
				  व्योम *data, पूर्णांक len)
अणु
	काष्ठा net_device *ndev = qp_data;
	काष्ठा sk_buff *skb;
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);

	skb = data;
	अगर (!skb || !ndev)
		वापस;

	अगर (len > 0) अणु
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += skb->len;
	पूर्ण अन्यथा अणु
		ndev->stats.tx_errors++;
		ndev->stats.tx_पातed_errors++;
	पूर्ण

	dev_kमुक्त_skb(skb);

	अगर (ntb_transport_tx_मुक्त_entry(dev->qp) >= tx_start) अणु
		/* Make sure anybody stopping the queue after this sees the new
		 * value of ntb_transport_tx_मुक्त_entry()
		 */
		smp_mb();
		अगर (netअगर_queue_stopped(ndev))
			netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल netdev_tx_t ntb_netdev_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *ndev)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);
	पूर्णांक rc;

	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	rc = ntb_transport_tx_enqueue(dev->qp, skb, skb->data, skb->len);
	अगर (rc)
		जाओ err;

	/* check क्रम next submit */
	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	वापस NETDEV_TX_OK;

err:
	ndev->stats.tx_dropped++;
	ndev->stats.tx_errors++;
	वापस NETDEV_TX_BUSY;
पूर्ण

अटल व्योम ntb_netdev_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ntb_netdev *dev = from_समयr(dev, t, tx_समयr);
	काष्ठा net_device *ndev = dev->ndev;

	अगर (ntb_transport_tx_मुक्त_entry(dev->qp) < tx_stop) अणु
		mod_समयr(&dev->tx_समयr, jअगरfies + usecs_to_jअगरfies(tx_समय));
	पूर्ण अन्यथा अणु
		/* Make sure anybody stopping the queue after this sees the new
		 * value of ntb_transport_tx_मुक्त_entry()
		 */
		smp_mb();
		अगर (netअगर_queue_stopped(ndev))
			netअगर_wake_queue(ndev);
	पूर्ण
पूर्ण

अटल पूर्णांक ntb_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	पूर्णांक rc, i, len;

	/* Add some empty rx bufs */
	क्रम (i = 0; i < NTB_RXQ_SIZE; i++) अणु
		skb = netdev_alloc_skb(ndev, ndev->mtu + ETH_HLEN);
		अगर (!skb) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		rc = ntb_transport_rx_enqueue(dev->qp, skb, skb->data,
					      ndev->mtu + ETH_HLEN);
		अगर (rc) अणु
			dev_kमुक्त_skb(skb);
			जाओ err;
		पूर्ण
	पूर्ण

	समयr_setup(&dev->tx_समयr, ntb_netdev_tx_समयr, 0);

	netअगर_carrier_off(ndev);
	ntb_transport_link_up(dev->qp);
	netअगर_start_queue(ndev);

	वापस 0;

err:
	जबतक ((skb = ntb_transport_rx_हटाओ(dev->qp, &len)))
		dev_kमुक्त_skb(skb);
	वापस rc;
पूर्ण

अटल पूर्णांक ntb_netdev_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	ntb_transport_link_करोwn(dev->qp);

	जबतक ((skb = ntb_transport_rx_हटाओ(dev->qp, &len)))
		dev_kमुक्त_skb(skb);

	del_समयr_sync(&dev->tx_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक ntb_netdev_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	पूर्णांक len, rc;

	अगर (new_mtu > ntb_transport_max_size(dev->qp) - ETH_HLEN)
		वापस -EINVAL;

	अगर (!netअगर_running(ndev)) अणु
		ndev->mtu = new_mtu;
		वापस 0;
	पूर्ण

	/* Bring करोwn the link and dispose of posted rx entries */
	ntb_transport_link_करोwn(dev->qp);

	अगर (ndev->mtu < new_mtu) अणु
		पूर्णांक i;

		क्रम (i = 0; (skb = ntb_transport_rx_हटाओ(dev->qp, &len)); i++)
			dev_kमुक्त_skb(skb);

		क्रम (; i; i--) अणु
			skb = netdev_alloc_skb(ndev, new_mtu + ETH_HLEN);
			अगर (!skb) अणु
				rc = -ENOMEM;
				जाओ err;
			पूर्ण

			rc = ntb_transport_rx_enqueue(dev->qp, skb, skb->data,
						      new_mtu + ETH_HLEN);
			अगर (rc) अणु
				dev_kमुक्त_skb(skb);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	ndev->mtu = new_mtu;

	ntb_transport_link_up(dev->qp);

	वापस 0;

err:
	ntb_transport_link_करोwn(dev->qp);

	जबतक ((skb = ntb_transport_rx_हटाओ(dev->qp, &len)))
		dev_kमुक्त_skb(skb);

	netdev_err(ndev, "Error changing MTU, device inoperable\n");
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ntb_netdev_ops = अणु
	.nकरो_खोलो = ntb_netdev_खोलो,
	.nकरो_stop = ntb_netdev_बंद,
	.nकरो_start_xmit = ntb_netdev_start_xmit,
	.nकरो_change_mtu = ntb_netdev_change_mtu,
	.nकरो_set_mac_address = eth_mac_addr,
पूर्ण;

अटल व्योम ntb_get_drvinfo(काष्ठा net_device *ndev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->version, NTB_NETDEV_VER, माप(info->version));
	strlcpy(info->bus_info, pci_name(dev->pdev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक ntb_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Backplane);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, Backplane);

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_FULL;
	cmd->base.port = PORT_OTHER;
	cmd->base.phy_address = 0;
	cmd->base.स्वतःneg = AUTONEG_ENABLE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ntb_ethtool_ops = अणु
	.get_drvinfo = ntb_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_link_ksettings = ntb_get_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा ntb_queue_handlers ntb_netdev_handlers = अणु
	.tx_handler = ntb_netdev_tx_handler,
	.rx_handler = ntb_netdev_rx_handler,
	.event_handler = ntb_netdev_event_handler,
पूर्ण;

अटल पूर्णांक ntb_netdev_probe(काष्ठा device *client_dev)
अणु
	काष्ठा ntb_dev *ntb;
	काष्ठा net_device *ndev;
	काष्ठा pci_dev *pdev;
	काष्ठा ntb_netdev *dev;
	पूर्णांक rc;

	ntb = dev_ntb(client_dev->parent);
	pdev = ntb->pdev;
	अगर (!pdev)
		वापस -ENODEV;

	ndev = alloc_etherdev(माप(*dev));
	अगर (!ndev)
		वापस -ENOMEM;

	SET_NETDEV_DEV(ndev, client_dev);

	dev = netdev_priv(ndev);
	dev->ndev = ndev;
	dev->pdev = pdev;
	ndev->features = NETIF_F_HIGHDMA;

	ndev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	ndev->hw_features = ndev->features;
	ndev->watchकरोg_समयo = msecs_to_jअगरfies(NTB_TX_TIMEOUT_MS);

	eth_अक्रमom_addr(ndev->perm_addr);
	स_नकल(ndev->dev_addr, ndev->perm_addr, ndev->addr_len);

	ndev->netdev_ops = &ntb_netdev_ops;
	ndev->ethtool_ops = &ntb_ethtool_ops;

	ndev->min_mtu = 0;
	ndev->max_mtu = ETH_MAX_MTU;

	dev->qp = ntb_transport_create_queue(ndev, client_dev,
					     &ntb_netdev_handlers);
	अगर (!dev->qp) अणु
		rc = -EIO;
		जाओ err;
	पूर्ण

	ndev->mtu = ntb_transport_max_size(dev->qp) - ETH_HLEN;

	rc = रेजिस्टर_netdev(ndev);
	अगर (rc)
		जाओ err1;

	dev_set_drvdata(client_dev, ndev);
	dev_info(&pdev->dev, "%s created\n", ndev->name);
	वापस 0;

err1:
	ntb_transport_मुक्त_queue(dev->qp);
err:
	मुक्त_netdev(ndev);
	वापस rc;
पूर्ण

अटल व्योम ntb_netdev_हटाओ(काष्ठा device *client_dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(client_dev);
	काष्ठा ntb_netdev *dev = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	ntb_transport_मुक्त_queue(dev->qp);
	मुक्त_netdev(ndev);
पूर्ण

अटल काष्ठा ntb_transport_client ntb_netdev_client = अणु
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.probe = ntb_netdev_probe,
	.हटाओ = ntb_netdev_हटाओ,
पूर्ण;

अटल पूर्णांक __init ntb_netdev_init_module(व्योम)
अणु
	पूर्णांक rc;

	rc = ntb_transport_रेजिस्टर_client_dev(KBUILD_MODNAME);
	अगर (rc)
		वापस rc;
	वापस ntb_transport_रेजिस्टर_client(&ntb_netdev_client);
पूर्ण
module_init(ntb_netdev_init_module);

अटल व्योम __निकास ntb_netdev_निकास_module(व्योम)
अणु
	ntb_transport_unरेजिस्टर_client(&ntb_netdev_client);
	ntb_transport_unरेजिस्टर_client_dev(KBUILD_MODNAME);
पूर्ण
module_निकास(ntb_netdev_निकास_module);
