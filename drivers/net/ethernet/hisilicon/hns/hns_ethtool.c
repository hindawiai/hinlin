<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "hns_enet.h"

#घोषणा HNS_PHY_PAGE_MDIX	0
#घोषणा HNS_PHY_PAGE_LED	3
#घोषणा HNS_PHY_PAGE_COPPER	0

#घोषणा HNS_PHY_PAGE_REG	22	/* Page Selection Reg. */
#घोषणा HNS_PHY_CSC_REG		16	/* Copper Specअगरic Control Register */
#घोषणा HNS_PHY_CSS_REG		17	/* Copper Specअगरic Status Register */
#घोषणा HNS_LED_FC_REG		16	/* LED Function Control Reg. */

#घोषणा HNS_LED_FORCE_ON	9
#घोषणा HNS_LED_FORCE_OFF	8

#घोषणा HNS_CHIP_VERSION 660
#घोषणा HNS_NET_STATS_CNT 26

#घोषणा PHY_MDIX_CTRL_S		(5)
#घोषणा PHY_MDIX_CTRL_M		(3 << PHY_MDIX_CTRL_S)

#घोषणा PHY_MDIX_STATUS_B	(6)
#घोषणा PHY_SPEED_DUP_RESOLVE_B	(11)

/**
 *hns_nic_get_link - get current link status
 *@net_dev: net_device
 *retuen 0 - success , negative --fail
 */
अटल u32 hns_nic_get_link(काष्ठा net_device *net_dev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	u32 link_stat = priv->link;
	काष्ठा hnae_handle *h;

	h = priv->ae_handle;

	अगर (net_dev->phydev) अणु
		अगर (!genphy_पढ़ो_status(net_dev->phydev))
			link_stat = net_dev->phydev->link;
		अन्यथा
			link_stat = 0;
	पूर्ण

	अगर (h->dev && h->dev->ops && h->dev->ops->get_status)
		link_stat = link_stat && h->dev->ops->get_status(h);
	अन्यथा
		link_stat = 0;

	वापस link_stat;
पूर्ण

अटल व्योम hns_get_mdix_mode(काष्ठा net_device *net_dev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	पूर्णांक mdix_ctrl, mdix, retval, is_resolved;
	काष्ठा phy_device *phy_dev = net_dev->phydev;

	अगर (!phy_dev || !phy_dev->mdio.bus) अणु
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
		वापस;
	पूर्ण

	phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_MDIX);

	retval = phy_पढ़ो(phy_dev, HNS_PHY_CSC_REG);
	mdix_ctrl = hnae_get_field(retval, PHY_MDIX_CTRL_M, PHY_MDIX_CTRL_S);

	retval = phy_पढ़ो(phy_dev, HNS_PHY_CSS_REG);
	mdix = hnae_get_bit(retval, PHY_MDIX_STATUS_B);
	is_resolved = hnae_get_bit(retval, PHY_SPEED_DUP_RESOLVE_B);

	phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_COPPER);

	चयन (mdix_ctrl) अणु
	हाल 0x0:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI;
		अवरोध;
	हाल 0x1:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_X;
		अवरोध;
	हाल 0x3:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
		अवरोध;
	शेष:
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;
		अवरोध;
	पूर्ण

	अगर (!is_resolved)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	अन्यथा अगर (mdix)
		cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
	अन्यथा
		cmd->base.eth_tp_mdix = ETH_TP_MDI;
पूर्ण

/**
 *hns_nic_get_link_ksettings - implement ethtool get link ksettings
 *@net_dev: net_device
 *@cmd: ethtool_link_ksettings
 *retuen 0 - success , negative --fail
 */
अटल पूर्णांक hns_nic_get_link_ksettings(काष्ठा net_device *net_dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_handle *h;
	u32 link_stat;
	पूर्णांक ret;
	u8 duplex;
	u16 speed;
	u32 supported, advertising;

	अगर (!priv || !priv->ae_handle)
		वापस -ESRCH;

	h = priv->ae_handle;
	अगर (!h->dev || !h->dev->ops || !h->dev->ops->get_info)
		वापस -ESRCH;

	ret = h->dev->ops->get_info(h, शून्य, &speed, &duplex);
	अगर (ret < 0) अणु
		netdev_err(net_dev, "%s get_info error!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	/* When there is no phy, स्वतःneg is off. */
	cmd->base.स्वतःneg = false;
	cmd->base.speed = speed;
	cmd->base.duplex = duplex;

	अगर (net_dev->phydev)
		phy_ethtool_ksettings_get(net_dev->phydev, cmd);

	link_stat = hns_nic_get_link(net_dev);
	अगर (!link_stat) अणु
		cmd->base.speed = (u32)SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	अगर (cmd->base.स्वतःneg)
		advertising |= ADVERTISED_Autoneg;

	supported |= h->अगर_support;
	अगर (h->phy_अगर == PHY_INTERFACE_MODE_SGMII) अणु
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_1000baseT_Full;
	पूर्ण अन्यथा अगर (h->phy_अगर == PHY_INTERFACE_MODE_XGMII) अणु
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_10000baseKR_Full;
	पूर्ण

	चयन (h->media_type) अणु
	हाल HNAE_MEDIA_TYPE_FIBER:
		cmd->base.port = PORT_FIBRE;
		अवरोध;
	हाल HNAE_MEDIA_TYPE_COPPER:
		cmd->base.port = PORT_TP;
		अवरोध;
	हाल HNAE_MEDIA_TYPE_UNKNOWN:
	शेष:
		अवरोध;
	पूर्ण

	अगर (!(AE_IS_VER1(priv->enet_ver) && h->port_type == HNAE_PORT_DEBUG))
		supported |= SUPPORTED_Pause;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C45 | ETH_MDIO_SUPPORTS_C22;
	hns_get_mdix_mode(net_dev, cmd);

	वापस 0;
पूर्ण

/**
 *hns_nic_set_link_ksettings - implement ethtool set link ksettings
 *@net_dev: net_device
 *@cmd: ethtool_link_ksettings
 *retuen 0 - success , negative --fail
 */
अटल पूर्णांक hns_nic_set_link_ksettings(काष्ठा net_device *net_dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_handle *h;
	u32 speed;

	अगर (!netअगर_running(net_dev))
		वापस -ESRCH;

	अगर (!priv || !priv->ae_handle || !priv->ae_handle->dev ||
	    !priv->ae_handle->dev->ops)
		वापस -ENODEV;

	h = priv->ae_handle;
	speed = cmd->base.speed;

	अगर (h->phy_अगर == PHY_INTERFACE_MODE_XGMII) अणु
		अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE ||
		    speed != SPEED_10000 ||
		    cmd->base.duplex != DUPLEX_FULL)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (h->phy_अगर == PHY_INTERFACE_MODE_SGMII) अणु
		अगर (!net_dev->phydev && cmd->base.स्वतःneg == AUTONEG_ENABLE)
			वापस -EINVAL;

		अगर (speed == SPEED_1000 && cmd->base.duplex == DUPLEX_HALF)
			वापस -EINVAL;
		अगर (net_dev->phydev)
			वापस phy_ethtool_ksettings_set(net_dev->phydev, cmd);

		अगर ((speed != SPEED_10 && speed != SPEED_100 &&
		     speed != SPEED_1000) || (cmd->base.duplex != DUPLEX_HALF &&
		     cmd->base.duplex != DUPLEX_FULL))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		netdev_err(net_dev, "Not supported!");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (h->dev->ops->adjust_link) अणु
		netअगर_carrier_off(net_dev);
		h->dev->ops->adjust_link(h, (पूर्णांक)speed, cmd->base.duplex);
		netअगर_carrier_on(net_dev);
		वापस 0;
	पूर्ण

	netdev_err(net_dev, "Not supported!");
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर अक्षर hns_nic_test_strs[][ETH_GSTRING_LEN] = अणु
	"Mac    Loopback test",
	"Serdes Loopback test",
	"Phy    Loopback test"
पूर्ण;

अटल पूर्णांक hns_nic_config_phy_loopback(काष्ठा phy_device *phy_dev, u8 en)
अणु
	पूर्णांक err;

	अगर (en) अणु
		/* Doing phy loopback in offline state, phy resuming is
		 * needed to घातer up the device.
		 */
		err = phy_resume(phy_dev);
		अगर (err)
			जाओ out;

		err = phy_loopback(phy_dev, true);
	पूर्ण अन्यथा अणु
		err = phy_loopback(phy_dev, false);
		अगर (err)
			जाओ out;

		err = phy_suspend(phy_dev);
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक __lb_setup(काष्ठा net_device *ndev,
		      क्रमागत hnae_loop loop)
अणु
	पूर्णांक ret = 0;
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phy_dev = ndev->phydev;
	काष्ठा hnae_handle *h = priv->ae_handle;

	चयन (loop) अणु
	हाल MAC_INTERNALLOOP_PHY:
		ret = hns_nic_config_phy_loopback(phy_dev, 0x1);
		अगर (!ret)
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		अवरोध;
	हाल MAC_INTERNALLOOP_MAC:
		अगर ((h->dev->ops->set_loopback) &&
		    (priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII))
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		अवरोध;
	हाल MAC_INTERNALLOOP_SERDES:
		अगर (h->dev->ops->set_loopback)
			ret = h->dev->ops->set_loopback(h, loop, 0x1);
		अवरोध;
	हाल MAC_LOOP_PHY_NONE:
		ret = hns_nic_config_phy_loopback(phy_dev, 0x0);
		fallthrough;
	हाल MAC_LOOP_NONE:
		अगर (!ret && h->dev->ops->set_loopback) अणु
			अगर (priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII)
				ret = h->dev->ops->set_loopback(h,
					MAC_INTERNALLOOP_MAC, 0x0);

			अगर (!ret)
				ret = h->dev->ops->set_loopback(h,
					MAC_INTERNALLOOP_SERDES, 0x0);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		अगर (loop == MAC_LOOP_NONE)
			h->dev->ops->set_promisc_mode(
				h, ndev->flags & IFF_PROMISC);
		अन्यथा
			h->dev->ops->set_promisc_mode(h, 1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __lb_up(काष्ठा net_device *ndev,
		   क्रमागत hnae_loop loop_mode)
अणु
#घोषणा NIC_LB_TEST_WAIT_PHY_LINK_TIME 300
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक speed, duplex;
	पूर्णांक ret;

	hns_nic_net_reset(ndev);

	ret = __lb_setup(ndev, loop_mode);
	अगर (ret)
		वापस ret;

	msleep(200);

	ret = h->dev->ops->start ? h->dev->ops->start(h) : 0;
	अगर (ret)
		वापस ret;

	/* link adjust duplex*/
	अगर (priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII)
		speed = 1000;
	अन्यथा
		speed = 10000;
	duplex = 1;

	h->dev->ops->adjust_link(h, speed, duplex);

	/* रुको adjust link करोne and phy पढ़ोy */
	msleep(NIC_LB_TEST_WAIT_PHY_LINK_TIME);

	वापस 0;
पूर्ण

अटल व्योम __lb_other_process(काष्ठा hns_nic_ring_data *ring_data,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *ndev;
	काष्ठा hns_nic_priv *priv;
	काष्ठा hnae_ring *ring;
	काष्ठा netdev_queue *dev_queue;
	काष्ठा sk_buff *new_skb;
	अचिन्हित पूर्णांक frame_size;
	पूर्णांक check_ok;
	u32 i;
	अक्षर buff[33]; /* 32B data and the last अक्षरacter '\0' */

	अगर (!ring_data) अणु /* Just क्रम करोing create frame*/
		ndev = skb->dev;
		priv = netdev_priv(ndev);

		frame_size = skb->len;
		स_रखो(skb->data, 0xFF, frame_size);
		अगर ((!AE_IS_VER1(priv->enet_ver)) &&
		    (priv->ae_handle->port_type == HNAE_PORT_SERVICE)) अणु
			स_नकल(skb->data, ndev->dev_addr, 6);
			skb->data[5] += 0x1f;
		पूर्ण

		frame_size &= ~1ul;
		स_रखो(&skb->data[frame_size / 2], 0xAA, frame_size / 2 - 1);
		स_रखो(&skb->data[frame_size / 2 + 10], 0xBE,
		       frame_size / 2 - 11);
		स_रखो(&skb->data[frame_size / 2 + 12], 0xAF,
		       frame_size / 2 - 13);
		वापस;
	पूर्ण

	ring = ring_data->ring;
	ndev = ring_data->napi.dev;
	अगर (is_tx_ring(ring)) अणु /* क्रम tx queue reset*/
		dev_queue = netdev_get_tx_queue(ndev, ring_data->queue_index);
		netdev_tx_reset_queue(dev_queue);
		वापस;
	पूर्ण

	frame_size = skb->len;
	frame_size &= ~1ul;
	/* क्रम mutl buffer*/
	new_skb = skb_copy(skb, GFP_ATOMIC);
	dev_kमुक्त_skb_any(skb);
	अगर (!new_skb) अणु
		netdev_err(ndev, "skb alloc failed\n");
		वापस;
	पूर्ण
	skb = new_skb;

	check_ok = 0;
	अगर (*(skb->data + 10) == 0xFF) अणु /* क्रम rx check frame*/
		अगर ((*(skb->data + frame_size / 2 + 10) == 0xBE) &&
		    (*(skb->data + frame_size / 2 + 12) == 0xAF))
			check_ok = 1;
	पूर्ण

	अगर (check_ok) अणु
		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += skb->len;
	पूर्ण अन्यथा अणु
		ndev->stats.rx_frame_errors++;
		क्रम (i = 0; i < skb->len; i++) अणु
			snम_लिखो(buff + i % 16 * 2, 3, /* tailing \0*/
				 "%02x", *(skb->data + i));
			अगर ((i % 16 == 15) || (i == skb->len - 1))
				pr_info("%s\n", buff);
		पूर्ण
	पूर्ण
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल पूर्णांक __lb_clean_rings(काष्ठा hns_nic_priv *priv,
			    पूर्णांक ringid0, पूर्णांक ringid1, पूर्णांक budget)
अणु
	पूर्णांक i, ret;
	काष्ठा hns_nic_ring_data *ring_data;
	काष्ठा net_device *ndev = priv->netdev;
	अचिन्हित दीर्घ rx_packets = ndev->stats.rx_packets;
	अचिन्हित दीर्घ rx_bytes = ndev->stats.rx_bytes;
	अचिन्हित दीर्घ rx_frame_errors = ndev->stats.rx_frame_errors;

	क्रम (i = ringid0; i <= ringid1; i++) अणु
		ring_data = &priv->ring_data[i];
		(व्योम)ring_data->poll_one(ring_data,
					  budget, __lb_other_process);
	पूर्ण
	ret = (पूर्णांक)(ndev->stats.rx_packets - rx_packets);
	ndev->stats.rx_packets = rx_packets;
	ndev->stats.rx_bytes = rx_bytes;
	ndev->stats.rx_frame_errors = rx_frame_errors;
	वापस ret;
पूर्ण

/**
 * __lb_run_test -  run loopback test
 * @ndev: net device
 * @loop_mode: loopback mode
 */
अटल पूर्णांक __lb_run_test(काष्ठा net_device *ndev,
			 क्रमागत hnae_loop loop_mode)
अणु
#घोषणा NIC_LB_TEST_PKT_NUM_PER_CYCLE 1
#घोषणा NIC_LB_TEST_RING_ID 0
#घोषणा NIC_LB_TEST_FRAME_SIZE 128
/* nic loopback test err  */
#घोषणा NIC_LB_TEST_NO_MEM_ERR 1
#घोषणा NIC_LB_TEST_TX_CNT_ERR 2
#घोषणा NIC_LB_TEST_RX_CNT_ERR 3

	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक i, j, lc, good_cnt, ret_val = 0;
	अचिन्हित पूर्णांक size;
	netdev_tx_t tx_ret_val;
	काष्ठा sk_buff *skb;

	size = NIC_LB_TEST_FRAME_SIZE;
	/* allocate test skb */
	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस NIC_LB_TEST_NO_MEM_ERR;

	/* place data पूर्णांकo test skb */
	(व्योम)skb_put(skb, size);
	skb->dev = ndev;
	__lb_other_process(शून्य, skb);
	skb->queue_mapping = NIC_LB_TEST_RING_ID;

	lc = 1;
	क्रम (j = 0; j < lc; j++) अणु
		/* reset count of good packets */
		good_cnt = 0;
		/* place 64 packets on the transmit queue*/
		क्रम (i = 0; i < NIC_LB_TEST_PKT_NUM_PER_CYCLE; i++) अणु
			(व्योम)skb_get(skb);

			tx_ret_val = (netdev_tx_t)hns_nic_net_xmit_hw(
				ndev, skb,
				&tx_ring_data(priv, skb->queue_mapping));
			अगर (tx_ret_val == NETDEV_TX_OK)
				good_cnt++;
			अन्यथा
				अवरोध;
		पूर्ण
		अगर (good_cnt != NIC_LB_TEST_PKT_NUM_PER_CYCLE) अणु
			ret_val = NIC_LB_TEST_TX_CNT_ERR;
			dev_err(priv->dev, "%s sent fail, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_strs[loop_mode], good_cnt,
				NIC_LB_TEST_PKT_NUM_PER_CYCLE);
			अवरोध;
		पूर्ण

		/* allow 100 milliseconds क्रम packets to go from Tx to Rx */
		msleep(100);

		good_cnt = __lb_clean_rings(priv,
					    h->q_num, h->q_num * 2 - 1,
					    NIC_LB_TEST_PKT_NUM_PER_CYCLE);
		अगर (good_cnt != NIC_LB_TEST_PKT_NUM_PER_CYCLE) अणु
			ret_val = NIC_LB_TEST_RX_CNT_ERR;
			dev_err(priv->dev, "%s recv fail, cnt=0x%x, budget=0x%x\n",
				hns_nic_test_strs[loop_mode], good_cnt,
				NIC_LB_TEST_PKT_NUM_PER_CYCLE);
			अवरोध;
		पूर्ण
		(व्योम)__lb_clean_rings(priv,
				       NIC_LB_TEST_RING_ID, NIC_LB_TEST_RING_ID,
				       NIC_LB_TEST_PKT_NUM_PER_CYCLE);
	पूर्ण

	/* मुक्त the original skb */
	kमुक्त_skb(skb);

	वापस ret_val;
पूर्ण

अटल पूर्णांक __lb_करोwn(काष्ठा net_device *ndev, क्रमागत hnae_loop loop)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	पूर्णांक ret;

	अगर (loop == MAC_INTERNALLOOP_PHY)
		ret = __lb_setup(ndev, MAC_LOOP_PHY_NONE);
	अन्यथा
		ret = __lb_setup(ndev, MAC_LOOP_NONE);
	अगर (ret)
		netdev_err(ndev, "%s: __lb_setup return error(%d)!\n",
			   __func__,
			   ret);

	अगर (h->dev->ops->stop)
		h->dev->ops->stop(h);

	usleep_range(10000, 20000);
	(व्योम)__lb_clean_rings(priv, 0, h->q_num - 1, 256);

	hns_nic_net_reset(ndev);

	वापस 0;
पूर्ण

/**
 * hns_nic_self_test - self test
 * @ndev: net device
 * @eth_test: test cmd
 * @data: test result
 */
अटल व्योम hns_nic_self_test(काष्ठा net_device *ndev,
			      काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(ndev);
	bool अगर_running = netअगर_running(ndev);
#घोषणा SELF_TEST_TPYE_NUM 3
	पूर्णांक st_param[SELF_TEST_TPYE_NUM][2];
	पूर्णांक i;
	पूर्णांक test_index = 0;

	st_param[0][0] = MAC_INTERNALLOOP_MAC; /* XGE not supported lb */
	st_param[0][1] = (priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII);
	st_param[1][0] = MAC_INTERNALLOOP_SERDES;
	st_param[1][1] = 1; /*serdes must exist*/
	st_param[2][0] = MAC_INTERNALLOOP_PHY; /* only supporte phy node*/
	st_param[2][1] = ((!!(priv->ae_handle->phy_dev)) &&
		(priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII));

	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		set_bit(NIC_STATE_TESTING, &priv->state);

		अगर (अगर_running)
			dev_बंद(ndev);

		क्रम (i = 0; i < SELF_TEST_TPYE_NUM; i++) अणु
			अगर (!st_param[i][1])
				जारी;	/* NEXT testing */

			data[test_index] = __lb_up(ndev,
				(क्रमागत hnae_loop)st_param[i][0]);
			अगर (!data[test_index]) अणु
				data[test_index] = __lb_run_test(
					ndev, (क्रमागत hnae_loop)st_param[i][0]);
				(व्योम)__lb_करोwn(ndev,
						(क्रमागत hnae_loop)st_param[i][0]);
			पूर्ण

			अगर (data[test_index])
				eth_test->flags |= ETH_TEST_FL_FAILED;

			test_index++;
		पूर्ण

		hns_nic_net_reset(priv->netdev);

		clear_bit(NIC_STATE_TESTING, &priv->state);

		अगर (अगर_running)
			(व्योम)dev_खोलो(ndev, शून्य);
	पूर्ण
	/* Online tests aren't run; pass by शेष */

	(व्योम)msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

/**
 * hns_nic_get_drvinfo - get net driver info
 * @net_dev: net device
 * @drvinfo: driver info
 */
अटल व्योम hns_nic_get_drvinfo(काष्ठा net_device *net_dev,
				काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);

	म_नकलन(drvinfo->version, HNAE_DRIVER_VERSION,
		माप(drvinfo->version));
	drvinfo->version[माप(drvinfo->version) - 1] = '\0';

	म_नकलन(drvinfo->driver, HNAE_DRIVER_NAME, माप(drvinfo->driver));
	drvinfo->driver[माप(drvinfo->driver) - 1] = '\0';

	म_नकलन(drvinfo->bus_info, priv->dev->bus->name,
		माप(drvinfo->bus_info));
	drvinfo->bus_info[ETHTOOL_BUSINFO_LEN - 1] = '\0';

	म_नकलन(drvinfo->fw_version, "N/A", ETHTOOL_FWVERS_LEN);
	drvinfo->eedump_len = 0;
पूर्ण

/**
 * hns_get_ringparam - get ring parameter
 * @net_dev: net device
 * @param: ethtool parameter
 */
अटल व्योम hns_get_ringparam(काष्ठा net_device *net_dev,
			      काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;
	काष्ठा hnae_queue *queue;
	u32 uplimit = 0;

	queue = priv->ae_handle->qs[0];
	ops = priv->ae_handle->dev->ops;

	अगर (ops->get_ring_bdnum_limit)
		ops->get_ring_bdnum_limit(queue, &uplimit);

	param->rx_max_pending = uplimit;
	param->tx_max_pending = uplimit;
	param->rx_pending = queue->rx_ring.desc_num;
	param->tx_pending = queue->tx_ring.desc_num;
पूर्ण

/**
 * hns_get_छोड़ोparam - get छोड़ो parameter
 * @net_dev: net device
 * @param: छोड़ो parameter
 */
अटल व्योम hns_get_छोड़ोparam(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_छोड़ोparam *param)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;

	अगर (ops->get_छोड़ोparam)
		ops->get_छोड़ोparam(priv->ae_handle, &param->स्वतःneg,
					    &param->rx_छोड़ो, &param->tx_छोड़ो);
पूर्ण

/**
 * hns_set_छोड़ोparam - set छोड़ो parameter
 * @net_dev: net device
 * @param: छोड़ो parameter
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_set_छोड़ोparam(काष्ठा net_device *net_dev,
			      काष्ठा ethtool_छोड़ोparam *param)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_handle *h;
	काष्ठा hnae_ae_ops *ops;

	h = priv->ae_handle;
	ops = h->dev->ops;

	अगर (!ops->set_छोड़ोparam)
		वापस -ESRCH;

	वापस ops->set_छोड़ोparam(priv->ae_handle, param->स्वतःneg,
				   param->rx_छोड़ो, param->tx_छोड़ो);
पूर्ण

/**
 * hns_get_coalesce - get coalesce info.
 * @net_dev: net device
 * @ec: coalesce info.
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक hns_get_coalesce(काष्ठा net_device *net_dev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;

	ec->use_adaptive_rx_coalesce = priv->ae_handle->coal_adapt_en;
	ec->use_adaptive_tx_coalesce = priv->ae_handle->coal_adapt_en;

	अगर ((!ops->get_coalesce_usecs) ||
	    (!ops->get_max_coalesced_frames))
		वापस -ESRCH;

	ops->get_coalesce_usecs(priv->ae_handle,
					&ec->tx_coalesce_usecs,
					&ec->rx_coalesce_usecs);

	ops->get_max_coalesced_frames(
		priv->ae_handle,
		&ec->tx_max_coalesced_frames,
		&ec->rx_max_coalesced_frames);

	ops->get_coalesce_range(priv->ae_handle,
				&ec->tx_max_coalesced_frames_low,
				&ec->rx_max_coalesced_frames_low,
				&ec->tx_max_coalesced_frames_high,
				&ec->rx_max_coalesced_frames_high,
				&ec->tx_coalesce_usecs_low,
				&ec->rx_coalesce_usecs_low,
				&ec->tx_coalesce_usecs_high,
				&ec->rx_coalesce_usecs_high);

	वापस 0;
पूर्ण

/**
 * hns_set_coalesce - set coalesce info.
 * @net_dev: net device
 * @ec: coalesce info.
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक hns_set_coalesce(काष्ठा net_device *net_dev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;
	पूर्णांक rc1, rc2;

	ops = priv->ae_handle->dev->ops;

	अगर (ec->tx_coalesce_usecs != ec->rx_coalesce_usecs)
		वापस -EINVAL;

	अगर ((!ops->set_coalesce_usecs) ||
	    (!ops->set_coalesce_frames))
		वापस -ESRCH;

	अगर (ec->use_adaptive_rx_coalesce != priv->ae_handle->coal_adapt_en)
		priv->ae_handle->coal_adapt_en = ec->use_adaptive_rx_coalesce;

	rc1 = ops->set_coalesce_usecs(priv->ae_handle,
				      ec->rx_coalesce_usecs);

	rc2 = ops->set_coalesce_frames(priv->ae_handle,
				       ec->tx_max_coalesced_frames,
				       ec->rx_max_coalesced_frames);

	अगर (rc1 || rc2)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * hns_get_channels - get channel info.
 * @net_dev: net device
 * @ch: channel info.
 */
अटल व्योम
hns_get_channels(काष्ठा net_device *net_dev, काष्ठा ethtool_channels *ch)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);

	ch->max_rx = priv->ae_handle->q_num;
	ch->max_tx = priv->ae_handle->q_num;

	ch->rx_count = priv->ae_handle->q_num;
	ch->tx_count = priv->ae_handle->q_num;
पूर्ण

/**
 * hns_get_ethtool_stats - get detail statistics.
 * @netdev: net device
 * @stats: statistics info.
 * @data: statistics data.
 */
अटल व्योम hns_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	u64 *p = data;
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	स्थिर काष्ठा rtnl_link_stats64 *net_stats;
	काष्ठा rtnl_link_stats64 temp;

	अगर (!h->dev->ops->get_stats || !h->dev->ops->update_stats) अणु
		netdev_err(netdev, "get_stats or update_stats is null!\n");
		वापस;
	पूर्ण

	h->dev->ops->update_stats(h, &netdev->stats);

	net_stats = dev_get_stats(netdev, &temp);

	/* get netdev statistics */
	p[0] = net_stats->rx_packets;
	p[1] = net_stats->tx_packets;
	p[2] = net_stats->rx_bytes;
	p[3] = net_stats->tx_bytes;
	p[4] = net_stats->rx_errors;
	p[5] = net_stats->tx_errors;
	p[6] = net_stats->rx_dropped;
	p[7] = net_stats->tx_dropped;
	p[8] = net_stats->multicast;
	p[9] = net_stats->collisions;
	p[10] = net_stats->rx_over_errors;
	p[11] = net_stats->rx_crc_errors;
	p[12] = net_stats->rx_frame_errors;
	p[13] = net_stats->rx_fअगरo_errors;
	p[14] = net_stats->rx_missed_errors;
	p[15] = net_stats->tx_पातed_errors;
	p[16] = net_stats->tx_carrier_errors;
	p[17] = net_stats->tx_fअगरo_errors;
	p[18] = net_stats->tx_heartbeat_errors;
	p[19] = net_stats->rx_length_errors;
	p[20] = net_stats->tx_winकरोw_errors;
	p[21] = net_stats->rx_compressed;
	p[22] = net_stats->tx_compressed;

	p[23] = netdev->rx_dropped.counter;
	p[24] = netdev->tx_dropped.counter;

	p[25] = priv->tx_समयout_count;

	/* get driver statistics */
	h->dev->ops->get_stats(h, &p[26]);
पूर्ण

/**
 * hns_get_strings: Return a set of strings that describe the requested objects
 * @netdev: net device
 * @stringset: string set ID.
 * @data: objects data.
 */
अटल व्योम hns_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	u8 *buff = data;

	अगर (!h->dev->ops->get_strings) अणु
		netdev_err(netdev, "h->dev->ops->get_strings is null!\n");
		वापस;
	पूर्ण

	अगर (stringset == ETH_SS_TEST) अणु
		अगर (priv->ae_handle->phy_अगर != PHY_INTERFACE_MODE_XGMII)
			ethtool_प्र_लिखो(&buff,
					hns_nic_test_strs[MAC_INTERNALLOOP_MAC]);
		ethtool_प्र_लिखो(&buff,
				hns_nic_test_strs[MAC_INTERNALLOOP_SERDES]);
		अगर ((netdev->phydev) && (!netdev->phydev->is_c45))
			ethtool_प्र_लिखो(&buff,
					hns_nic_test_strs[MAC_INTERNALLOOP_PHY]);

	पूर्ण अन्यथा अणु
		ethtool_प्र_लिखो(&buff, "rx_packets");
		ethtool_प्र_लिखो(&buff, "tx_packets");
		ethtool_प्र_लिखो(&buff, "rx_bytes");
		ethtool_प्र_लिखो(&buff, "tx_bytes");
		ethtool_प्र_लिखो(&buff, "rx_errors");
		ethtool_प्र_लिखो(&buff, "tx_errors");
		ethtool_प्र_लिखो(&buff, "rx_dropped");
		ethtool_प्र_लिखो(&buff, "tx_dropped");
		ethtool_प्र_लिखो(&buff, "multicast");
		ethtool_प्र_लिखो(&buff, "collisions");
		ethtool_प्र_लिखो(&buff, "rx_over_errors");
		ethtool_प्र_लिखो(&buff, "rx_crc_errors");
		ethtool_प्र_लिखो(&buff, "rx_frame_errors");
		ethtool_प्र_लिखो(&buff, "rx_fifo_errors");
		ethtool_प्र_लिखो(&buff, "rx_missed_errors");
		ethtool_प्र_लिखो(&buff, "tx_aborted_errors");
		ethtool_प्र_लिखो(&buff, "tx_carrier_errors");
		ethtool_प्र_लिखो(&buff, "tx_fifo_errors");
		ethtool_प्र_लिखो(&buff, "tx_heartbeat_errors");
		ethtool_प्र_लिखो(&buff, "rx_length_errors");
		ethtool_प्र_लिखो(&buff, "tx_window_errors");
		ethtool_प्र_लिखो(&buff, "rx_compressed");
		ethtool_प्र_लिखो(&buff, "tx_compressed");
		ethtool_प्र_लिखो(&buff, "netdev_rx_dropped");
		ethtool_प्र_लिखो(&buff, "netdev_tx_dropped");

		ethtool_प्र_लिखो(&buff, "netdev_tx_timeout");

		h->dev->ops->get_strings(h, stringset, buff);
	पूर्ण
पूर्ण

/**
 * hns_get_sset_count - get string set count वापसed by nic_get_strings
 * @netdev: net device
 * @stringset: string set index, 0: self test string; 1: statistics string.
 *
 * Return string set count.
 */
अटल पूर्णांक hns_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा hnae_ae_ops *ops = h->dev->ops;

	अगर (!ops->get_sset_count) अणु
		netdev_err(netdev, "get_sset_count is null!\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (stringset == ETH_SS_TEST) अणु
		u32 cnt = (माप(hns_nic_test_strs) / ETH_GSTRING_LEN);

		अगर (priv->ae_handle->phy_अगर == PHY_INTERFACE_MODE_XGMII)
			cnt--;

		अगर ((!netdev->phydev) || (netdev->phydev->is_c45))
			cnt--;

		वापस cnt;
	पूर्ण अन्यथा अगर (stringset == ETH_SS_STATS) अणु
		वापस (HNS_NET_STATS_CNT + ops->get_sset_count(h, stringset));
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * hns_phy_led_set - set phy LED status.
 * @netdev: net device
 * @value: LED state.
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक hns_phy_led_set(काष्ठा net_device *netdev, पूर्णांक value)
अणु
	पूर्णांक retval;
	काष्ठा phy_device *phy_dev = netdev->phydev;

	retval = phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_LED);
	retval |= phy_ग_लिखो(phy_dev, HNS_LED_FC_REG, value);
	retval |= phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG, HNS_PHY_PAGE_COPPER);
	अगर (retval) अणु
		netdev_err(netdev, "mdiobus_write fail !\n");
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hns_set_phys_id - set phy identअगरy LED.
 * @netdev: net device
 * @state: LED state.
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक
hns_set_phys_id(काष्ठा net_device *netdev, क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_handle *h = priv->ae_handle;
	काष्ठा phy_device *phy_dev = netdev->phydev;
	पूर्णांक ret;

	अगर (phy_dev)
		चयन (state) अणु
		हाल ETHTOOL_ID_ACTIVE:
			ret = phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG,
					HNS_PHY_PAGE_LED);
			अगर (ret)
				वापस ret;

			priv->phy_led_val = phy_पढ़ो(phy_dev, HNS_LED_FC_REG);

			ret = phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG,
					HNS_PHY_PAGE_COPPER);
			अगर (ret)
				वापस ret;
			वापस 2;
		हाल ETHTOOL_ID_ON:
			ret = hns_phy_led_set(netdev, HNS_LED_FORCE_ON);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल ETHTOOL_ID_OFF:
			ret = hns_phy_led_set(netdev, HNS_LED_FORCE_OFF);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल ETHTOOL_ID_INACTIVE:
			ret = phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG,
					HNS_PHY_PAGE_LED);
			अगर (ret)
				वापस ret;

			ret = phy_ग_लिखो(phy_dev, HNS_LED_FC_REG,
					priv->phy_led_val);
			अगर (ret)
				वापस ret;

			ret = phy_ग_लिखो(phy_dev, HNS_PHY_PAGE_REG,
					HNS_PHY_PAGE_COPPER);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	अन्यथा
		चयन (state) अणु
		हाल ETHTOOL_ID_ACTIVE:
			वापस h->dev->ops->set_led_id(h, HNAE_LED_ACTIVE);
		हाल ETHTOOL_ID_ON:
			वापस h->dev->ops->set_led_id(h, HNAE_LED_ON);
		हाल ETHTOOL_ID_OFF:
			वापस h->dev->ops->set_led_id(h, HNAE_LED_OFF);
		हाल ETHTOOL_ID_INACTIVE:
			वापस h->dev->ops->set_led_id(h, HNAE_LED_INACTIVE);
		शेष:
			वापस -EINVAL;
		पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_get_regs - get net device रेजिस्टर
 * @net_dev: net device
 * @cmd: ethtool cmd
 * @data: रेजिस्टर data
 */
अटल व्योम hns_get_regs(काष्ठा net_device *net_dev, काष्ठा ethtool_regs *cmd,
			 व्योम *data)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;

	cmd->version = HNS_CHIP_VERSION;
	अगर (!ops->get_regs) अणु
		netdev_err(net_dev, "ops->get_regs is null!\n");
		वापस;
	पूर्ण
	ops->get_regs(priv->ae_handle, data);
पूर्ण

/**
 * hns_get_regs_len - get total रेजिस्टर len.
 * @net_dev: net device
 *
 * Return total रेजिस्टर len.
 */
अटल पूर्णांक hns_get_regs_len(काष्ठा net_device *net_dev)
अणु
	u32 reg_num;
	काष्ठा hns_nic_priv *priv = netdev_priv(net_dev);
	काष्ठा hnae_ae_ops *ops;

	ops = priv->ae_handle->dev->ops;
	अगर (!ops->get_regs_len) अणु
		netdev_err(net_dev, "ops->get_regs_len is null!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	reg_num = ops->get_regs_len(priv->ae_handle);
	अगर (reg_num > 0)
		वापस reg_num * माप(u32);
	अन्यथा
		वापस reg_num;	/* error code */
पूर्ण

/**
 * hns_nic_nway_reset - nway reset
 * @netdev: net device
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_nic_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा phy_device *phy = netdev->phydev;

	अगर (!netअगर_running(netdev))
		वापस 0;

	अगर (!phy)
		वापस -EOPNOTSUPP;

	अगर (phy->स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;

	वापस genphy_restart_aneg(phy);
पूर्ण

अटल u32
hns_get_rss_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_ae_ops *ops;

	अगर (AE_IS_VER1(priv->enet_ver)) अणु
		netdev_err(netdev,
			   "RSS feature is not supported on this hardware\n");
		वापस 0;
	पूर्ण

	ops = priv->ae_handle->dev->ops;
	वापस ops->get_rss_key_size(priv->ae_handle);
पूर्ण

अटल u32
hns_get_rss_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_ae_ops *ops;

	अगर (AE_IS_VER1(priv->enet_ver)) अणु
		netdev_err(netdev,
			   "RSS feature is not supported on this hardware\n");
		वापस 0;
	पूर्ण

	ops = priv->ae_handle->dev->ops;
	वापस ops->get_rss_indir_size(priv->ae_handle);
पूर्ण

अटल पूर्णांक
hns_get_rss(काष्ठा net_device *netdev, u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_ae_ops *ops;

	अगर (AE_IS_VER1(priv->enet_ver)) अणु
		netdev_err(netdev,
			   "RSS feature is not supported on this hardware\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ops = priv->ae_handle->dev->ops;

	अगर (!indir)
		वापस 0;

	वापस ops->get_rss(priv->ae_handle, indir, key, hfunc);
पूर्ण

अटल पूर्णांक
hns_set_rss(काष्ठा net_device *netdev, स्थिर u32 *indir, स्थिर u8 *key,
	    स्थिर u8 hfunc)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);
	काष्ठा hnae_ae_ops *ops;

	अगर (AE_IS_VER1(priv->enet_ver)) अणु
		netdev_err(netdev,
			   "RSS feature is not supported on this hardware\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ops = priv->ae_handle->dev->ops;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP) अणु
		netdev_err(netdev, "Invalid hfunc!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ops->set_rss(priv->ae_handle, indir, key, hfunc);
पूर्ण

अटल पूर्णांक hns_get_rxnfc(काष्ठा net_device *netdev,
			 काष्ठा ethtool_rxnfc *cmd,
			 u32 *rule_locs)
अणु
	काष्ठा hns_nic_priv *priv = netdev_priv(netdev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = priv->ae_handle->q_num;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops hns_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE |
				     ETHTOOL_COALESCE_USECS_LOW_HIGH |
				     ETHTOOL_COALESCE_MAX_FRAMES_LOW_HIGH,
	.get_drvinfo = hns_nic_get_drvinfo,
	.get_link  = hns_nic_get_link,
	.get_ringparam = hns_get_ringparam,
	.get_छोड़ोparam = hns_get_छोड़ोparam,
	.set_छोड़ोparam = hns_set_छोड़ोparam,
	.get_coalesce = hns_get_coalesce,
	.set_coalesce = hns_set_coalesce,
	.get_channels = hns_get_channels,
	.self_test = hns_nic_self_test,
	.get_strings = hns_get_strings,
	.get_sset_count = hns_get_sset_count,
	.get_ethtool_stats = hns_get_ethtool_stats,
	.set_phys_id = hns_set_phys_id,
	.get_regs_len = hns_get_regs_len,
	.get_regs = hns_get_regs,
	.nway_reset = hns_nic_nway_reset,
	.get_rxfh_key_size = hns_get_rss_key_size,
	.get_rxfh_indir_size = hns_get_rss_indir_size,
	.get_rxfh = hns_get_rss,
	.set_rxfh = hns_set_rss,
	.get_rxnfc = hns_get_rxnfc,
	.get_link_ksettings  = hns_nic_get_link_ksettings,
	.set_link_ksettings  = hns_nic_set_link_ksettings,
पूर्ण;

व्योम hns_ethtool_set_ops(काष्ठा net_device *ndev)
अणु
	ndev->ethtool_ops = &hns_ethtool_ops;
पूर्ण
