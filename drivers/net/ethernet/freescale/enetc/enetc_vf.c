<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2017-2019 NXP */

#समावेश <linux/module.h>
#समावेश "enetc.h"

#घोषणा ENETC_DRV_NAME_STR "ENETC VF driver"

/* Messaging */
अटल व्योम enetc_msg_vsi_ग_लिखो_msg(काष्ठा enetc_hw *hw,
				    काष्ठा enetc_msg_swbd *msg)
अणु
	u32 val;

	val = enetc_vsi_set_msize(msg->size) | lower_32_bits(msg->dma);
	enetc_wr(hw, ENETC_VSIMSGSNDAR1, upper_32_bits(msg->dma));
	enetc_wr(hw, ENETC_VSIMSGSNDAR0, val);
पूर्ण

अटल पूर्णांक enetc_msg_vsi_send(काष्ठा enetc_si *si, काष्ठा enetc_msg_swbd *msg)
अणु
	पूर्णांक समयout = 100;
	u32 vsimsgsr;

	enetc_msg_vsi_ग_लिखो_msg(&si->hw, msg);

	करो अणु
		vsimsgsr = enetc_rd(&si->hw, ENETC_VSIMSGSR);
		अगर (!(vsimsgsr & ENETC_VSIMSGSR_MB))
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (--समयout);

	अगर (!समयout)
		वापस -ETIMEDOUT;

	/* check क्रम message delivery error */
	अगर (vsimsgsr & ENETC_VSIMSGSR_MS) अणु
		dev_err(&si->pdev->dev, "VSI command execute error: %d\n",
			ENETC_SIMSGSR_GET_MC(vsimsgsr));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_msg_vsi_set_primary_mac_addr(काष्ठा enetc_ndev_priv *priv,
					      काष्ठा sockaddr *saddr)
अणु
	काष्ठा enetc_msg_cmd_set_primary_mac *cmd;
	काष्ठा enetc_msg_swbd msg;
	पूर्णांक err;

	msg.size = ALIGN(माप(काष्ठा enetc_msg_cmd_set_primary_mac), 64);
	msg.vaddr = dma_alloc_coherent(priv->dev, msg.size, &msg.dma,
				       GFP_KERNEL);
	अगर (!msg.vaddr) अणु
		dev_err(priv->dev, "Failed to alloc Tx msg (size: %d)\n",
			msg.size);
		वापस -ENOMEM;
	पूर्ण

	cmd = (काष्ठा enetc_msg_cmd_set_primary_mac *)msg.vaddr;
	cmd->header.type = ENETC_MSG_CMD_MNG_MAC;
	cmd->header.id = ENETC_MSG_CMD_MNG_ADD;
	स_नकल(&cmd->mac, saddr, माप(काष्ठा sockaddr));

	/* send the command and रुको */
	err = enetc_msg_vsi_send(priv->si, &msg);

	dma_मुक्त_coherent(priv->dev, msg.size, msg.vaddr, msg.dma);

	वापस err;
पूर्ण

अटल पूर्णांक enetc_vf_set_mac_addr(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा sockaddr *saddr = addr;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	वापस enetc_msg_vsi_set_primary_mac_addr(priv, saddr);
पूर्ण

अटल पूर्णांक enetc_vf_set_features(काष्ठा net_device *ndev,
				 netdev_features_t features)
अणु
	वापस enetc_set_features(ndev, features);
पूर्ण

/* Probing/ Init */
अटल स्थिर काष्ठा net_device_ops enetc_ndev_ops = अणु
	.nकरो_खोलो		= enetc_खोलो,
	.nकरो_stop		= enetc_बंद,
	.nकरो_start_xmit		= enetc_xmit,
	.nकरो_get_stats		= enetc_get_stats,
	.nकरो_set_mac_address	= enetc_vf_set_mac_addr,
	.nकरो_set_features	= enetc_vf_set_features,
	.nकरो_करो_ioctl		= enetc_ioctl,
	.nकरो_setup_tc		= enetc_setup_tc,
पूर्ण;

अटल व्योम enetc_vf_netdev_setup(काष्ठा enetc_si *si, काष्ठा net_device *ndev,
				  स्थिर काष्ठा net_device_ops *ndev_ops)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);

	SET_NETDEV_DEV(ndev, &si->pdev->dev);
	priv->ndev = ndev;
	priv->si = si;
	priv->dev = &si->pdev->dev;
	si->ndev = ndev;

	priv->msg_enable = (NETIF_MSG_IFUP << 1) - 1;
	ndev->netdev_ops = ndev_ops;
	enetc_set_ethtool_ops(ndev);
	ndev->watchकरोg_समयo = 5 * HZ;
	ndev->max_mtu = ENETC_MAX_MTU;

	ndev->hw_features = NETIF_F_SG | NETIF_F_RXCSUM |
			    NETIF_F_HW_VLAN_CTAG_TX |
			    NETIF_F_HW_VLAN_CTAG_RX;
	ndev->features = NETIF_F_HIGHDMA | NETIF_F_SG | NETIF_F_RXCSUM |
			 NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_HW_VLAN_CTAG_RX;

	अगर (si->num_rss)
		ndev->hw_features |= NETIF_F_RXHASH;

	/* pick up primary MAC address from SI */
	enetc_get_primary_mac_addr(&si->hw, ndev->dev_addr);
पूर्ण

अटल पूर्णांक enetc_vf_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा enetc_ndev_priv *priv;
	काष्ठा net_device *ndev;
	काष्ठा enetc_si *si;
	पूर्णांक err;

	err = enetc_pci_probe(pdev, KBUILD_MODNAME, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "PCI probing failed\n");
		वापस err;
	पूर्ण

	si = pci_get_drvdata(pdev);

	enetc_get_si_caps(si);

	ndev = alloc_etherdev_mq(माप(*priv), ENETC_MAX_NUM_TXQS);
	अगर (!ndev) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "netdev creation failed\n");
		जाओ err_alloc_netdev;
	पूर्ण

	enetc_vf_netdev_setup(si, ndev, &enetc_ndev_ops);

	priv = netdev_priv(ndev);

	enetc_init_si_rings_params(priv);

	err = enetc_setup_cbdr(priv->dev, &si->hw, ENETC_CBDR_DEFAULT_SIZE,
			       &si->cbd_ring);
	अगर (err)
		जाओ err_setup_cbdr;

	err = enetc_alloc_si_resources(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "SI resource alloc failed\n");
		जाओ err_alloc_si_res;
	पूर्ण

	err = enetc_configure_si(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to configure SI\n");
		जाओ err_config_si;
	पूर्ण

	err = enetc_alloc_msix(priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "MSIX alloc failed\n");
		जाओ err_alloc_msix;
	पूर्ण

	err = रेजिस्टर_netdev(ndev);
	अगर (err)
		जाओ err_reg_netdev;

	netअगर_carrier_off(ndev);

	वापस 0;

err_reg_netdev:
	enetc_मुक्त_msix(priv);
err_config_si:
err_alloc_msix:
	enetc_मुक्त_si_resources(priv);
err_alloc_si_res:
	enetc_tearकरोwn_cbdr(&si->cbd_ring);
err_setup_cbdr:
	si->ndev = शून्य;
	मुक्त_netdev(ndev);
err_alloc_netdev:
	enetc_pci_हटाओ(pdev);

	वापस err;
पूर्ण

अटल व्योम enetc_vf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा enetc_si *si = pci_get_drvdata(pdev);
	काष्ठा enetc_ndev_priv *priv;

	priv = netdev_priv(si->ndev);
	unरेजिस्टर_netdev(si->ndev);

	enetc_मुक्त_msix(priv);

	enetc_मुक्त_si_resources(priv);
	enetc_tearकरोwn_cbdr(&si->cbd_ring);

	मुक्त_netdev(si->ndev);

	enetc_pci_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id enetc_vf_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, ENETC_DEV_ID_VF) पूर्ण,
	अणु 0, पूर्ण /* End of table. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, enetc_vf_id_table);

अटल काष्ठा pci_driver enetc_vf_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = enetc_vf_id_table,
	.probe = enetc_vf_probe,
	.हटाओ = enetc_vf_हटाओ,
पूर्ण;
module_pci_driver(enetc_vf_driver);

MODULE_DESCRIPTION(ENETC_DRV_NAME_STR);
MODULE_LICENSE("Dual BSD/GPL");
