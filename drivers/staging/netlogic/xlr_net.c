<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause)
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 */

#समावेश <linux/phy.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/smp.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mipsregs.h>
/*
 * fmn.h - For FMN credit configuration and रेजिस्टरing fmn_handler.
 * FMN is communication mechanism that allows processing agents within
 * XLR/XLS to communicate each other.
 */
#समावेश <यंत्र/netlogic/xlr/fmn.h>

#समावेश "platform_net.h"
#समावेश "xlr_net.h"

/*
 * The पढ़ोl/ग_लिखोl implementation byteswaps on XLR/XLS, so
 * we need to use __raw_ IO to पढ़ो the NAE रेजिस्टरs
 * because they are in the big-endian MMIO area on the SoC.
 */
अटल अंतरभूत व्योम xlr_nae_wreg(u32 __iomem *base, अचिन्हित पूर्णांक reg, u32 val)
अणु
	__raw_ग_लिखोl(val, base + reg);
पूर्ण

अटल अंतरभूत u32 xlr_nae_rdreg(u32 __iomem *base, अचिन्हित पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(base + reg);
पूर्ण

अटल अंतरभूत व्योम xlr_reg_update(u32 *base_addr, u32 off, u32 val, u32 mask)
अणु
	u32 पंचांगp;

	पंचांगp = xlr_nae_rdreg(base_addr, off);
	xlr_nae_wreg(base_addr, off, (पंचांगp & ~mask) | (val & mask));
पूर्ण

#घोषणा MAC_SKB_BACK_PTR_SIZE SMP_CACHE_BYTES

अटल पूर्णांक send_to_rfr_fअगरo(काष्ठा xlr_net_priv *priv, व्योम *addr)
अणु
	काष्ठा nlm_fmn_msg msg;
	पूर्णांक ret = 0, num_try = 0, stnid;
	अचिन्हित दीर्घ paddr, mflags;

	paddr = virt_to_bus(addr);
	msg.msg0 = (u64)paddr & 0xffffffffe0ULL;
	msg.msg1 = 0;
	msg.msg2 = 0;
	msg.msg3 = 0;
	stnid = priv->nd->rfr_station;
	करो अणु
		mflags = nlm_cop2_enable_irqsave();
		ret = nlm_fmn_send(1, 0, stnid, &msg);
		nlm_cop2_disable_irqrestore(mflags);
		अगर (ret == 0)
			वापस 0;
	पूर्ण जबतक (++num_try < 10000);

	netdev_err(priv->ndev, "Send to RFR failed in RX path\n");
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *xlr_alloc_skb(व्योम)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक buf_len = माप(काष्ठा sk_buff *);
	अचिन्हित अक्षर *skb_data;

	/* skb->data is cache aligned */
	skb = alloc_skb(XLR_RX_BUF_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;
	skb_data = skb->data;
	skb_reserve(skb, MAC_SKB_BACK_PTR_SIZE);
	स_नकल(skb_data, &skb, buf_len);

	वापस skb->data;
पूर्ण

अटल व्योम xlr_net_fmn_handler(पूर्णांक bkt, पूर्णांक src_stnid, पूर्णांक size, पूर्णांक code,
				काष्ठा nlm_fmn_msg *msg, व्योम *arg)
अणु
	काष्ठा sk_buff *skb;
	व्योम *skb_data = शून्य;
	काष्ठा net_device *ndev;
	काष्ठा xlr_net_priv *priv;
	u32 port, length;
	अचिन्हित अक्षर *addr;
	काष्ठा xlr_adapter *adapter = arg;

	length = (msg->msg0 >> 40) & 0x3fff;
	अगर (length == 0) अणु
		addr = bus_to_virt(msg->msg0 & 0xffffffffffULL);
		addr = addr - MAC_SKB_BACK_PTR_SIZE;
		skb = (काष्ठा sk_buff *)(*(अचिन्हित दीर्घ *)addr);
		dev_kमुक्त_skb_any((काष्ठा sk_buff *)addr);
	पूर्ण अन्यथा अणु
		addr = (अचिन्हित अक्षर *)
			bus_to_virt(msg->msg0 & 0xffffffffe0ULL);
		length = length - BYTE_OFFSET - MAC_CRC_LEN;
		port = ((पूर्णांक)msg->msg0) & 0x0f;
		addr = addr - MAC_SKB_BACK_PTR_SIZE;
		skb = (काष्ठा sk_buff *)(*(अचिन्हित दीर्घ *)addr);
		skb->dev = adapter->netdev[port];
		अगर (!skb->dev)
			वापस;
		ndev = skb->dev;
		priv = netdev_priv(ndev);

		/* 16 byte IP header align */
		skb_reserve(skb, BYTE_OFFSET);
		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, skb->dev);
		netअगर_rx(skb);
		/* Fill rx ring */
		skb_data = xlr_alloc_skb();
		अगर (skb_data)
			send_to_rfr_fअगरo(priv, skb_data);
	पूर्ण
पूर्ण

अटल काष्ठा phy_device *xlr_get_phydev(काष्ठा xlr_net_priv *priv)
अणु
	वापस mdiobus_get_phy(priv->mii_bus, priv->phy_addr);
पूर्ण

/*
 * Ethtool operation
 */
अटल पूर्णांक xlr_get_link_ksettings(काष्ठा net_device *ndev,
				  काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);

	अगर (!phydev)
		वापस -ENODEV;

	phy_ethtool_ksettings_get(phydev, ecmd);

	वापस 0;
पूर्ण

अटल पूर्णांक xlr_set_link_ksettings(काष्ठा net_device *ndev,
				  स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);

	अगर (!phydev)
		वापस -ENODEV;
	वापस phy_ethtool_ksettings_set(phydev, ecmd);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xlr_ethtool_ops = अणु
	.get_link_ksettings = xlr_get_link_ksettings,
	.set_link_ksettings = xlr_set_link_ksettings,
पूर्ण;

/*
 * Net operations
 */
अटल पूर्णांक xlr_net_fill_rx_ring(काष्ठा net_device *ndev)
अणु
	व्योम *skb_data;
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < MAX_FRIN_SPILL / 4; i++) अणु
		skb_data = xlr_alloc_skb();
		अगर (!skb_data)
			वापस -ENOMEM;
		send_to_rfr_fअगरo(priv, skb_data);
	पूर्ण
	netdev_info(ndev, "Rx ring setup done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक xlr_net_खोलो(काष्ठा net_device *ndev)
अणु
	u32 err;
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);

	/* schedule a link state check */
	phy_start(phydev);

	err = phy_start_aneg(phydev);
	अगर (err) अणु
		pr_err("Autoneg failed\n");
		वापस err;
	पूर्ण
	/* Setup the speed from PHY to पूर्णांकernal reg*/
	xlr_set_gmac_speed(priv);

	netअगर_tx_start_all_queues(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक xlr_net_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);

	phy_stop(phydev);
	netअगर_tx_stop_all_queues(ndev);
	वापस 0;
पूर्ण

अटल व्योम xlr_make_tx_desc(काष्ठा nlm_fmn_msg *msg, अचिन्हित दीर्घ addr,
			     काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ physkb = virt_to_phys(skb);
	पूर्णांक cpu_core = nlm_core_id();
	पूर्णांक fr_stn_id = cpu_core * 8 + XLR_FB_STN;	/* FB to 6th bucket */

	msg->msg0 = (((u64)1 << 63)	|	/* End of packet descriptor */
		((u64)127 << 54)	|	/* No Free back */
		(u64)skb->len << 40	|	/* Length of data */
		((u64)addr));
	msg->msg1 = (((u64)1 << 63)	|
		((u64)fr_stn_id << 54)	|	/* Free back id */
		(u64)0 << 40		|	/* Set len to 0 */
		((u64)physkb  & 0xffffffff));	/* 32bit address */
	msg->msg2 = 0;
	msg->msg3 = 0;
पूर्ण

अटल netdev_tx_t xlr_net_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *ndev)
अणु
	काष्ठा nlm_fmn_msg msg;
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;
	u32 flags;

	xlr_make_tx_desc(&msg, virt_to_phys(skb->data), skb);
	flags = nlm_cop2_enable_irqsave();
	ret = nlm_fmn_send(2, 0, priv->tx_stnid, &msg);
	nlm_cop2_disable_irqrestore(flags);
	अगर (ret)
		dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम xlr_hw_set_mac_addr(काष्ठा net_device *ndev)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);

	/* set mac station address */
	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR0,
		     ((ndev->dev_addr[5] << 24) | (ndev->dev_addr[4] << 16) |
		     (ndev->dev_addr[3] << 8) | (ndev->dev_addr[2])));
	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR0 + 1,
		     ((ndev->dev_addr[1] << 24) | (ndev->dev_addr[0] << 16)));

	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR_MASK2, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR_MASK2 + 1, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR_MASK3, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_MAC_ADDR_MASK3 + 1, 0xffffffff);

	xlr_nae_wreg(priv->base_addr, R_MAC_FILTER_CONFIG,
		     (1 << O_MAC_FILTER_CONFIG__BROADCAST_EN) |
		     (1 << O_MAC_FILTER_CONFIG__ALL_MCAST_EN) |
		     (1 << O_MAC_FILTER_CONFIG__MAC_ADDR0_VALID));

	अगर (priv->nd->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
	    priv->nd->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		xlr_reg_update(priv->base_addr, R_IPG_IFG, MAC_B2B_IPG, 0x7f);
पूर्ण

अटल पूर्णांक xlr_net_set_mac_addr(काष्ठा net_device *ndev, व्योम *data)
अणु
	पूर्णांक err;

	err = eth_mac_addr(ndev, data);
	अगर (err)
		वापस err;
	xlr_hw_set_mac_addr(ndev);
	वापस 0;
पूर्ण

अटल व्योम xlr_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	u32 regval;

	regval = xlr_nae_rdreg(priv->base_addr, R_MAC_FILTER_CONFIG);

	अगर (ndev->flags & IFF_PROMISC) अणु
		regval |= (1 << O_MAC_FILTER_CONFIG__BROADCAST_EN) |
		(1 << O_MAC_FILTER_CONFIG__PAUSE_FRAME_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_MCAST_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_UCAST_EN);
	पूर्ण अन्यथा अणु
		regval &= ~((1 << O_MAC_FILTER_CONFIG__PAUSE_FRAME_EN) |
		(1 << O_MAC_FILTER_CONFIG__ALL_UCAST_EN));
	पूर्ण

	xlr_nae_wreg(priv->base_addr, R_MAC_FILTER_CONFIG, regval);
पूर्ण

अटल व्योम xlr_stats(काष्ठा net_device *ndev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);

	stats->rx_packets = xlr_nae_rdreg(priv->base_addr, RX_PACKET_COUNTER);
	stats->tx_packets = xlr_nae_rdreg(priv->base_addr, TX_PACKET_COUNTER);
	stats->rx_bytes = xlr_nae_rdreg(priv->base_addr, RX_BYTE_COUNTER);
	stats->tx_bytes = xlr_nae_rdreg(priv->base_addr, TX_BYTE_COUNTER);
	stats->tx_errors = xlr_nae_rdreg(priv->base_addr, TX_FCS_ERROR_COUNTER);
	stats->rx_dropped = xlr_nae_rdreg(priv->base_addr,
					  RX_DROP_PACKET_COUNTER);
	stats->tx_dropped = xlr_nae_rdreg(priv->base_addr,
					  TX_DROP_FRAME_COUNTER);

	stats->multicast = xlr_nae_rdreg(priv->base_addr,
					 RX_MULTICAST_PACKET_COUNTER);
	stats->collisions = xlr_nae_rdreg(priv->base_addr,
					  TX_TOTAL_COLLISION_COUNTER);

	stats->rx_length_errors = xlr_nae_rdreg(priv->base_addr,
						RX_FRAME_LENGTH_ERROR_COUNTER);
	stats->rx_over_errors = xlr_nae_rdreg(priv->base_addr,
					      RX_DROP_PACKET_COUNTER);
	stats->rx_crc_errors = xlr_nae_rdreg(priv->base_addr,
					     RX_FCS_ERROR_COUNTER);
	stats->rx_frame_errors = xlr_nae_rdreg(priv->base_addr,
					       RX_ALIGNMENT_ERROR_COUNTER);

	stats->rx_fअगरo_errors = xlr_nae_rdreg(priv->base_addr,
					      RX_DROP_PACKET_COUNTER);
	stats->rx_missed_errors = xlr_nae_rdreg(priv->base_addr,
						RX_CARRIER_SENSE_ERROR_COUNTER);

	stats->rx_errors = (stats->rx_over_errors + stats->rx_crc_errors +
			    stats->rx_frame_errors + stats->rx_fअगरo_errors +
			    stats->rx_missed_errors);

	stats->tx_पातed_errors = xlr_nae_rdreg(priv->base_addr,
						 TX_EXCESSIVE_COLLISION_PACKET_COUNTER);
	stats->tx_carrier_errors = xlr_nae_rdreg(priv->base_addr,
						 TX_DROP_FRAME_COUNTER);
	stats->tx_fअगरo_errors = xlr_nae_rdreg(priv->base_addr,
					      TX_DROP_FRAME_COUNTER);
पूर्ण

अटल स्थिर काष्ठा net_device_ops xlr_netdev_ops = अणु
	.nकरो_खोलो = xlr_net_खोलो,
	.nकरो_stop = xlr_net_stop,
	.nकरो_start_xmit = xlr_net_start_xmit,
	.nकरो_select_queue = dev_pick_tx_cpu_id,
	.nकरो_set_mac_address = xlr_net_set_mac_addr,
	.nकरो_set_rx_mode = xlr_set_rx_mode,
	.nकरो_get_stats64 = xlr_stats,
पूर्ण;

/*
 * Gmac init
 */
अटल व्योम *xlr_config_spill(काष्ठा xlr_net_priv *priv, पूर्णांक reg_start_0,
			      पूर्णांक reg_start_1, पूर्णांक reg_size, पूर्णांक size)
अणु
	व्योम *spill;
	u32 *base;
	अचिन्हित दीर्घ phys_addr;
	u32 spill_size;

	base = priv->base_addr;
	spill_size = size;
	spill = kदो_स्मृति(spill_size + SMP_CACHE_BYTES, GFP_KERNEL);
	अगर (!spill)
		वापस ZERO_SIZE_PTR;

	spill = PTR_ALIGN(spill, SMP_CACHE_BYTES);
	phys_addr = virt_to_phys(spill);
	dev_dbg(&priv->ndev->dev, "Allocated spill %d bytes at %lx\n",
		size, phys_addr);
	xlr_nae_wreg(base, reg_start_0, (phys_addr >> 5) & 0xffffffff);
	xlr_nae_wreg(base, reg_start_1, ((u64)phys_addr >> 37) & 0x07);
	xlr_nae_wreg(base, reg_size, spill_size);

	वापस spill;
पूर्ण

/*
 * Configure the 6 FIFO's that are used by the network accelarator to
 * communicate with the rest of the XLx device. 4 of the FIFO's are क्रम
 * packets from NA --> cpu (called Class FIFO's) and 2 are क्रम feeding
 * the NA with मुक्त descriptors.
 */
अटल व्योम xlr_config_fअगरo_spill_area(काष्ठा xlr_net_priv *priv)
अणु
	priv->frin_spill = xlr_config_spill(priv,
					    R_REG_FRIN_SPILL_MEM_START_0,
					    R_REG_FRIN_SPILL_MEM_START_1,
					    R_REG_FRIN_SPILL_MEM_SIZE,
					    MAX_FRIN_SPILL * माप(u64));
	priv->frout_spill = xlr_config_spill(priv,
					     R_FROUT_SPILL_MEM_START_0,
					     R_FROUT_SPILL_MEM_START_1,
					     R_FROUT_SPILL_MEM_SIZE,
					     MAX_FROUT_SPILL * माप(u64));
	priv->class_0_spill = xlr_config_spill(priv,
					       R_CLASS0_SPILL_MEM_START_0,
					       R_CLASS0_SPILL_MEM_START_1,
					       R_CLASS0_SPILL_MEM_SIZE,
					       MAX_CLASS_0_SPILL * माप(u64));
	priv->class_1_spill = xlr_config_spill(priv,
					       R_CLASS1_SPILL_MEM_START_0,
					       R_CLASS1_SPILL_MEM_START_1,
					       R_CLASS1_SPILL_MEM_SIZE,
					       MAX_CLASS_1_SPILL * माप(u64));
	priv->class_2_spill = xlr_config_spill(priv,
					       R_CLASS2_SPILL_MEM_START_0,
					       R_CLASS2_SPILL_MEM_START_1,
					       R_CLASS2_SPILL_MEM_SIZE,
					       MAX_CLASS_2_SPILL * माप(u64));
	priv->class_3_spill = xlr_config_spill(priv,
					       R_CLASS3_SPILL_MEM_START_0,
					       R_CLASS3_SPILL_MEM_START_1,
					       R_CLASS3_SPILL_MEM_SIZE,
					       MAX_CLASS_3_SPILL * माप(u64));
पूर्ण

/*
 * Configure PDE to Round-Robin distribution of packets to the
 * available cpu
 */
अटल व्योम xlr_config_pde(काष्ठा xlr_net_priv *priv)
अणु
	पूर्णांक i = 0;
	u64 bkt_map = 0;

	/* Each core has 8 buckets(station) */
	क्रम (i = 0; i < hweight32(priv->nd->cpu_mask); i++)
		bkt_map |= (0xff << (i * 8));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_0, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_0 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_1, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_1 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_2, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_2 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_3, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_3 + 1,
		     ((bkt_map >> 32) & 0xffffffff));
पूर्ण

/*
 * Setup the Message ring credits, bucket size and other
 * common configuration
 */
अटल पूर्णांक xlr_config_common(काष्ठा xlr_net_priv *priv)
अणु
	काष्ठा xlr_fmn_info *gmac = priv->nd->gmac_fmn_info;
	पूर्णांक start_stn_id = gmac->start_stn_id;
	पूर्णांक end_stn_id = gmac->end_stn_id;
	पूर्णांक *bucket_size = priv->nd->bucket_size;
	पूर्णांक i, j, err;

	/* Setting non-core MsgBktSize(0x321 - 0x325) */
	क्रम (i = start_stn_id; i <= end_stn_id; i++) अणु
		xlr_nae_wreg(priv->base_addr,
			     R_GMAC_RFR0_BUCKET_SIZE + i - start_stn_id,
			     bucket_size[i]);
	पूर्ण

	/*
	 * Setting non-core Credit counter रेजिस्टर
	 * Distributing Gmac's credit to CPU's
	 */
	क्रम (i = 0; i < 8; i++) अणु
		क्रम (j = 0; j < 8; j++)
			xlr_nae_wreg(priv->base_addr,
				     (R_CC_CPU0_0 + (i * 8)) + j,
				     gmac->credit_config[(i * 8) + j]);
	पूर्ण

	xlr_nae_wreg(priv->base_addr, R_MSG_TX_THRESHOLD, 3);
	xlr_nae_wreg(priv->base_addr, R_DMACR0, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_DMACR1, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_DMACR2, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_DMACR3, 0xffffffff);
	xlr_nae_wreg(priv->base_addr, R_FREEQCARVE, 0);

	err = xlr_net_fill_rx_ring(priv->ndev);
	अगर (err)
		वापस err;
	nlm_रेजिस्टर_fmn_handler(start_stn_id, end_stn_id, xlr_net_fmn_handler,
				 priv->adapter);
	वापस 0;
पूर्ण

अटल व्योम xlr_config_translate_table(काष्ठा xlr_net_priv *priv)
अणु
	u32 cpu_mask;
	u32 val;
	पूर्णांक bkts[32]; /* one bucket is assumed क्रम each cpu */
	पूर्णांक b1, b2, c1, c2, i, j, k;
	पूर्णांक use_bkt;

	use_bkt = 0;
	cpu_mask = priv->nd->cpu_mask;

	pr_info("Using %s-based distribution\n",
		(use_bkt) ? "bucket" : "class");
	j = 0;
	क्रम (i = 0; i < 32; i++) अणु
		अगर ((1 << i) & cpu_mask) अणु
			/* क्रम each cpu, mark the 4+thपढ़ोid bucket */
			bkts[j] = ((i / 4) * 8) + (i % 4);
			j++;
		पूर्ण
	पूर्ण

	/*configure the 128 * 9 Translation table to send to available buckets*/
	k = 0;
	c1 = 3;
	c2 = 0;
	क्रम (i = 0; i < 64; i++) अणु
		/*
		 * On use_bkt set the b0, b1 are used, अन्यथा
		 * the 4 classes are used, here implemented
		 * a logic to distribute the packets to the
		 * buckets equally or based on the class
		 */
		c1 = (c1 + 1) & 3;
		c2 = (c1 + 1) & 3;
		b1 = bkts[k];
		k = (k + 1) % j;
		b2 = bkts[k];
		k = (k + 1) % j;

		val = ((c1 << 23) | (b1 << 17) | (use_bkt << 16) |
				(c2 << 7) | (b2 << 1) | (use_bkt << 0));
		dev_dbg(&priv->ndev->dev, "Table[%d] b1=%d b2=%d c1=%d c2=%d\n",
			i, b1, b2, c1, c2);
		xlr_nae_wreg(priv->base_addr, R_TRANSLATETABLE + i, val);
		c1 = c2;
	पूर्ण
पूर्ण

अटल व्योम xlr_config_parser(काष्ठा xlr_net_priv *priv)
अणु
	u32 val;

	/* Mark it as ETHERNET type */
	xlr_nae_wreg(priv->base_addr, R_L2TYPE_0, 0x01);

	/* Use 7bit CRChash क्रम flow classअगरication with 127 as CRC polynomial*/
	xlr_nae_wreg(priv->base_addr, R_PARSERCONFIGREG,
		     ((0x7f << 8) | (1 << 1)));

	/* configure the parser : L2 Type is configured in the bootloader */
	/* extract IP: src, dest protocol */
	xlr_nae_wreg(priv->base_addr, R_L3CTABLE,
		     (9 << 20) | (1 << 19) | (1 << 18) | (0x01 << 16) |
		     (0x0800 << 0));
	xlr_nae_wreg(priv->base_addr, R_L3CTABLE + 1,
		     (9 << 25) | (1 << 21) | (12 << 14) | (4 << 10) |
		     (16 << 4) | 4);

	/* Configure to extract SRC port and Dest port क्रम TCP and UDP pkts */
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE, 6);
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 2, 17);
	val = ((0 << 21) | (2 << 17) | (2 << 11) | (2 << 7));
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 1, val);
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 3, val);

	xlr_config_translate_table(priv);
पूर्ण

अटल पूर्णांक xlr_phy_ग_लिखो(u32 *base_addr, पूर्णांक phy_addr, पूर्णांक regnum, u16 val)
अणु
	अचिन्हित दीर्घ समयout, stopसमय, checkसमय;
	पूर्णांक समयकरोut;

	/* 100ms समयout*/
	समयout = msecs_to_jअगरfies(100);
	stopसमय = jअगरfies + समयout;
	समयकरोut = 0;

	xlr_nae_wreg(base_addr, R_MII_MGMT_ADDRESS, (phy_addr << 8) | regnum);

	/* Write the data which starts the ग_लिखो cycle */
	xlr_nae_wreg(base_addr, R_MII_MGMT_WRITE_DATA, (u32)val);

	/* poll क्रम the पढ़ो cycle to complete */
	जबतक (!समयकरोut) अणु
		checkसमय = jअगरfies;
		अगर (xlr_nae_rdreg(base_addr, R_MII_MGMT_INDICATORS) == 0)
			अवरोध;
		समयकरोut = समय_after(checkसमय, stopसमय);
	पूर्ण
	अगर (समयकरोut) अणु
		pr_info("Phy device write err: device busy");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlr_phy_पढ़ो(u32 *base_addr, पूर्णांक phy_addr, पूर्णांक regnum)
अणु
	अचिन्हित दीर्घ समयout, stopसमय, checkसमय;
	पूर्णांक समयकरोut;

	/* 100ms समयout*/
	समयout = msecs_to_jअगरfies(100);
	stopसमय = jअगरfies + समयout;
	समयकरोut = 0;

	/* setup the phy reg to be used */
	xlr_nae_wreg(base_addr, R_MII_MGMT_ADDRESS,
		     (phy_addr << 8) | (regnum << 0));

	/* Issue the पढ़ो command */
	xlr_nae_wreg(base_addr, R_MII_MGMT_COMMAND,
		     (1 << O_MII_MGMT_COMMAND__rstat));

	/* poll क्रम the पढ़ो cycle to complete */
	जबतक (!समयकरोut) अणु
		checkसमय = jअगरfies;
		अगर (xlr_nae_rdreg(base_addr, R_MII_MGMT_INDICATORS) == 0)
			अवरोध;
		समयकरोut = समय_after(checkसमय, stopसमय);
	पूर्ण
	अगर (समयकरोut) अणु
		pr_info("Phy device read err: device busy");
		वापस -EBUSY;
	पूर्ण

	/* clear the पढ़ो cycle */
	xlr_nae_wreg(base_addr, R_MII_MGMT_COMMAND, 0);

	/* Read the data */
	वापस xlr_nae_rdreg(base_addr, R_MII_MGMT_STATUS);
पूर्ण

अटल पूर्णांक xlr_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum, u16 val)
अणु
	काष्ठा xlr_net_priv *priv = bus->priv;
	पूर्णांक ret;

	ret = xlr_phy_ग_लिखो(priv->mii_addr, phy_addr, regnum, val);
	dev_dbg(&priv->ndev->dev, "mii_write phy %d : %d <- %x [%x]\n",
		phy_addr, regnum, val, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक xlr_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक regnum)
अणु
	काष्ठा xlr_net_priv *priv = bus->priv;
	पूर्णांक ret;

	ret =  xlr_phy_पढ़ो(priv->mii_addr, phy_addr, regnum);
	dev_dbg(&priv->ndev->dev, "mii_read phy %d : %d [%x]\n",
		phy_addr, regnum, ret);
	वापस ret;
पूर्ण

/*
 * XLR ports are RGMII. XLS ports are SGMII mostly except the port0,
 * which can be configured either SGMII or RGMII, considered SGMII
 * by शेष, अगर board setup to RGMII the port_type need to set
 * accordingly.Serdes and PCS layer need to configured क्रम SGMII
 */
अटल व्योम xlr_sgmii_init(काष्ठा xlr_net_priv *priv)
अणु
	पूर्णांक phy;

	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 0, 0x6DB0);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 1, 0xFFFF);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 2, 0xB6D0);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 3, 0x00FF);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 4, 0x0000);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 5, 0x0000);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 6, 0x0005);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 7, 0x0001);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 8, 0x0000);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 9, 0x0000);
	xlr_phy_ग_लिखो(priv->serdes_addr, 26, 10, 0x0000);

	/* program  GPIO values क्रम serdes init parameters */
	xlr_nae_wreg(priv->gpio_addr, 0x20, 0x7e6802);
	xlr_nae_wreg(priv->gpio_addr, 0x10, 0x7104);

	xlr_nae_wreg(priv->gpio_addr, 0x22, 0x7e6802);
	xlr_nae_wreg(priv->gpio_addr, 0x21, 0x7104);

	/* enable स्वतःneg - more magic */
	phy = priv->phy_addr % 4 + 27;
	xlr_phy_ग_लिखो(priv->pcs_addr, phy, 0, 0x1000);
	xlr_phy_ग_लिखो(priv->pcs_addr, phy, 0, 0x0200);
पूर्ण

व्योम xlr_set_gmac_speed(काष्ठा xlr_net_priv *priv)
अणु
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);
	पूर्णांक speed;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		xlr_sgmii_init(priv);

	अगर (phydev->speed != priv->phy_speed) अणु
		speed = phydev->speed;
		अगर (speed == SPEED_1000) अणु
			/* Set पूर्णांकerface to Byte mode */
			xlr_nae_wreg(priv->base_addr, R_MAC_CONFIG_2, 0x7217);
			priv->phy_speed = speed;
		पूर्ण अन्यथा अगर (speed == SPEED_100 || speed == SPEED_10) अणु
			/* Set पूर्णांकerface to Nibble mode */
			xlr_nae_wreg(priv->base_addr, R_MAC_CONFIG_2, 0x7117);
			priv->phy_speed = speed;
		पूर्ण
		/* Set SGMII speed in Interface control reg */
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
			अगर (speed == SPEED_10)
				xlr_nae_wreg(priv->base_addr,
					     R_INTERFACE_CONTROL,
					     SGMII_SPEED_10);
			अगर (speed == SPEED_100)
				xlr_nae_wreg(priv->base_addr,
					     R_INTERFACE_CONTROL,
					     SGMII_SPEED_100);
			अगर (speed == SPEED_1000)
				xlr_nae_wreg(priv->base_addr,
					     R_INTERFACE_CONTROL,
					     SGMII_SPEED_1000);
		पूर्ण
		अगर (speed == SPEED_10)
			xlr_nae_wreg(priv->base_addr, R_CORECONTROL, 0x2);
		अगर (speed == SPEED_100)
			xlr_nae_wreg(priv->base_addr, R_CORECONTROL, 0x1);
		अगर (speed == SPEED_1000)
			xlr_nae_wreg(priv->base_addr, R_CORECONTROL, 0x0);
	पूर्ण
	pr_info("gmac%d : %dMbps\n", priv->port_id, priv->phy_speed);
पूर्ण

अटल व्योम xlr_gmac_link_adjust(काष्ठा net_device *ndev)
अणु
	काष्ठा xlr_net_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);
	u32 पूर्णांकreg;

	पूर्णांकreg = xlr_nae_rdreg(priv->base_addr, R_INTREG);
	अगर (phydev->link) अणु
		अगर (phydev->speed != priv->phy_speed) अणु
			xlr_set_gmac_speed(priv);
			pr_info("gmac%d : Link up\n", priv->port_id);
		पूर्ण
	पूर्ण अन्यथा अणु
		xlr_set_gmac_speed(priv);
		pr_info("gmac%d : Link down\n", priv->port_id);
	पूर्ण
पूर्ण

अटल पूर्णांक xlr_mii_probe(काष्ठा xlr_net_priv *priv)
अणु
	काष्ठा phy_device *phydev = xlr_get_phydev(priv);

	अगर (!phydev) अणु
		pr_err("no PHY found on phy_addr %d\n", priv->phy_addr);
		वापस -ENODEV;
	पूर्ण

	/* Attach MAC to PHY */
	phydev = phy_connect(priv->ndev, phydev_name(phydev),
			     xlr_gmac_link_adjust, priv->nd->phy_पूर्णांकerface);

	अगर (IS_ERR(phydev)) अणु
		pr_err("could not attach PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण
	phydev->supported &= (ADVERTISED_10baseT_Full
				| ADVERTISED_10baseT_Half
				| ADVERTISED_100baseT_Full
				| ADVERTISED_100baseT_Half
				| ADVERTISED_1000baseT_Full
				| ADVERTISED_Autoneg
				| ADVERTISED_MII);

	phydev->advertising = phydev->supported;
	phy_attached_info(phydev);
	वापस 0;
पूर्ण

अटल पूर्णांक xlr_setup_mdio(काष्ठा xlr_net_priv *priv,
			  काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	priv->mii_bus = mdiobus_alloc();
	अगर (!priv->mii_bus) अणु
		pr_err("mdiobus alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	priv->mii_bus->priv = priv;
	priv->mii_bus->name = "xlr-mdio";
	snम_लिखो(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s-%d",
		 priv->mii_bus->name, priv->port_id);
	priv->mii_bus->पढ़ो = xlr_mii_पढ़ो;
	priv->mii_bus->ग_लिखो = xlr_mii_ग_लिखो;
	priv->mii_bus->parent = &pdev->dev;

	/* Scan only the enabled address */
	priv->mii_bus->phy_mask = ~(1 << priv->phy_addr);

	/* setting घड़ी भागisor to 54 */
	xlr_nae_wreg(priv->base_addr, R_MII_MGMT_CONFIG, 0x7);

	err = mdiobus_रेजिस्टर(priv->mii_bus);
	अगर (err) अणु
		mdiobus_मुक्त(priv->mii_bus);
		pr_err("mdio bus registration failed\n");
		वापस err;
	पूर्ण

	pr_info("Registered mdio bus id : %s\n", priv->mii_bus->id);
	err = xlr_mii_probe(priv);
	अगर (err) अणु
		mdiobus_मुक्त(priv->mii_bus);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम xlr_port_enable(काष्ठा xlr_net_priv *priv)
अणु
	u32 prid = (पढ़ो_c0_prid() & 0xf000);

	/* Setup MAC_CONFIG reg अगर (xls & rgmii) */
	अगर ((prid == 0x8000 || prid == 0x4000 || prid == 0xc000) &&
	    priv->nd->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
		xlr_reg_update(priv->base_addr, R_RX_CONTROL,
			       (1 << O_RX_CONTROL__RGMII),
			       (1 << O_RX_CONTROL__RGMII));

	/* Rx Tx enable */
	xlr_reg_update(priv->base_addr, R_MAC_CONFIG_1,
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)),
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)));

	/* Setup tx control reg */
	xlr_reg_update(priv->base_addr, R_TX_CONTROL,
		       ((1 << O_TX_CONTROL__TXENABLE) |
		       (512 << O_TX_CONTROL__TXTHRESHOLD)), 0x3fff);

	/* Setup rx control reg */
	xlr_reg_update(priv->base_addr, R_RX_CONTROL,
		       1 << O_RX_CONTROL__RXENABLE,
		       1 << O_RX_CONTROL__RXENABLE);
पूर्ण

अटल व्योम xlr_port_disable(काष्ठा xlr_net_priv *priv)
अणु
	/* Setup MAC_CONFIG reg */
	/* Rx Tx disable*/
	xlr_reg_update(priv->base_addr, R_MAC_CONFIG_1,
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)), 0x0);

	/* Setup tx control reg */
	xlr_reg_update(priv->base_addr, R_TX_CONTROL,
		       ((1 << O_TX_CONTROL__TXENABLE) |
		       (512 << O_TX_CONTROL__TXTHRESHOLD)), 0);

	/* Setup rx control reg */
	xlr_reg_update(priv->base_addr, R_RX_CONTROL,
		       1 << O_RX_CONTROL__RXENABLE, 0);
पूर्ण

/*
 * Initialization of gmac
 */
अटल पूर्णांक xlr_gmac_init(काष्ठा xlr_net_priv *priv,
			 काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pr_info("Initializing the gmac%d\n", priv->port_id);

	xlr_port_disable(priv);

	xlr_nae_wreg(priv->base_addr, R_DESC_PACK_CTRL,
		     (1 << O_DESC_PACK_CTRL__MAXENTRY) |
		     (BYTE_OFFSET << O_DESC_PACK_CTRL__BYTखातापूर्णFSET) |
		     (1600 << O_DESC_PACK_CTRL__REGULARSIZE));

	ret = xlr_setup_mdio(priv, pdev);
	अगर (ret)
		वापस ret;
	xlr_port_enable(priv);

	/* Enable Full-duplex/1000Mbps/CRC */
	xlr_nae_wreg(priv->base_addr, R_MAC_CONFIG_2, 0x7217);
	/* speed 2.5Mhz */
	xlr_nae_wreg(priv->base_addr, R_CORECONTROL, 0x02);
	/* Setup Interrupt mask reg */
	xlr_nae_wreg(priv->base_addr, R_INTMASK, (1 << O_INTMASK__TXILLEGAL) |
		     (1 << O_INTMASK__MDINT) | (1 << O_INTMASK__TXFETCHERROR) |
		     (1 << O_INTMASK__P2PSPILLECC) | (1 << O_INTMASK__TAGFULL) |
		     (1 << O_INTMASK__UNDERRUN) | (1 << O_INTMASK__ABORT));

	/* Clear all stats */
	xlr_reg_update(priv->base_addr, R_STATCTRL, 0, 1 << O_STATCTRL__CLRCNT);
	xlr_reg_update(priv->base_addr, R_STATCTRL, 1 << 2, 1 << 2);
	वापस 0;
पूर्ण

अटल पूर्णांक xlr_net_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlr_net_priv *priv = शून्य;
	काष्ठा net_device *ndev;
	काष्ठा resource *res;
	काष्ठा xlr_adapter *adapter;
	पूर्णांक err, port;

	pr_info("XLR/XLS Ethernet Driver controller %d\n", pdev->id);
	/*
	 * Allocate our adapter data काष्ठाure and attach it to the device.
	 */
	adapter = devm_kzalloc(&pdev->dev, माप(*adapter), GFP_KERNEL);
	अगर (!adapter)
		वापस -ENOMEM;

	/*
	 * XLR and XLS have 1 and 2 NAE controller respectively
	 * Each controller has 4 gmac ports, mapping each controller
	 * under one parent device, 4 gmac ports under one device.
	 */
	क्रम (port = 0; port < pdev->num_resources / 2; port++) अणु
		ndev = alloc_etherdev_mq(माप(काष्ठा xlr_net_priv), 32);
		अगर (!ndev) अणु
			dev_err(&pdev->dev,
				"Allocation of Ethernet device failed\n");
			वापस -ENOMEM;
		पूर्ण

		priv = netdev_priv(ndev);
		priv->pdev = pdev;
		priv->ndev = ndev;
		priv->port_id = (pdev->id * 4) + port;
		priv->nd = (काष्ठा xlr_net_data *)pdev->dev.platक्रमm_data;
		priv->base_addr = devm_platक्रमm_ioremap_resource(pdev, port);
		अगर (IS_ERR(priv->base_addr)) अणु
			err = PTR_ERR(priv->base_addr);
			जाओ err_gmac;
		पूर्ण
		priv->adapter = adapter;
		adapter->netdev[port] = ndev;

		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, port);
		अगर (!res) अणु
			dev_err(&pdev->dev, "No irq resource for MAC %d\n",
				priv->port_id);
			err = -ENODEV;
			जाओ err_gmac;
		पूर्ण

		ndev->irq = res->start;

		priv->phy_addr = priv->nd->phy_addr[port];
		priv->tx_stnid = priv->nd->tx_stnid[port];
		priv->mii_addr = priv->nd->mii_addr;
		priv->serdes_addr = priv->nd->serdes_addr;
		priv->pcs_addr = priv->nd->pcs_addr;
		priv->gpio_addr = priv->nd->gpio_addr;

		ndev->netdev_ops = &xlr_netdev_ops;
		ndev->watchकरोg_समयo = HZ;

		/* Setup Mac address and Rx mode */
		eth_hw_addr_अक्रमom(ndev);
		xlr_hw_set_mac_addr(ndev);
		xlr_set_rx_mode(ndev);

		priv->num_rx_desc += MAX_NUM_DESC_SPILL;
		ndev->ethtool_ops = &xlr_ethtool_ops;
		SET_NETDEV_DEV(ndev, &pdev->dev);

		xlr_config_fअगरo_spill_area(priv);
		/* Configure PDE to Round-Robin pkt distribution */
		xlr_config_pde(priv);
		xlr_config_parser(priv);

		/* Call init with respect to port */
		अगर (म_भेद(res->name, "gmac") == 0) अणु
			err = xlr_gmac_init(priv, pdev);
			अगर (err) अणु
				dev_err(&pdev->dev, "gmac%d init failed\n",
					priv->port_id);
				जाओ err_gmac;
			पूर्ण
		पूर्ण

		अगर (priv->port_id == 0 || priv->port_id == 4) अणु
			err = xlr_config_common(priv);
			अगर (err)
				जाओ err_netdev;
		पूर्ण

		err = रेजिस्टर_netdev(ndev);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Registering netdev failed for gmac%d\n",
				priv->port_id);
			जाओ err_netdev;
		पूर्ण
		platक्रमm_set_drvdata(pdev, priv);
	पूर्ण

	वापस 0;

err_netdev:
	mdiobus_मुक्त(priv->mii_bus);
err_gmac:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक xlr_net_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlr_net_priv *priv = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_netdev(priv->ndev);
	mdiobus_unरेजिस्टर(priv->mii_bus);
	mdiobus_मुक्त(priv->mii_bus);
	मुक्त_netdev(priv->ndev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xlr_net_driver = अणु
	.probe		= xlr_net_probe,
	.हटाओ		= xlr_net_हटाओ,
	.driver		= अणु
		.name	= "xlr-net",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlr_net_driver);

MODULE_AUTHOR("Ganesan Ramalingam <ganesanr@broadcom.com>");
MODULE_DESCRIPTION("Ethernet driver for Netlogic XLR/XLS");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:xlr-net");
