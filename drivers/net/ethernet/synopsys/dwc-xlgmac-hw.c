<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#समावेश <linux/phy.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32poly.h>
#समावेश <linux/dcbnl.h>

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

अटल पूर्णांक xlgmac_tx_complete(काष्ठा xlgmac_dma_desc *dma_desc)
अणु
	वापस !XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				TX_NORMAL_DESC3_OWN_POS,
				TX_NORMAL_DESC3_OWN_LEN);
पूर्ण

अटल पूर्णांक xlgmac_disable_rx_csum(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_IPC_POS,
				     MAC_RCR_IPC_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_enable_rx_csum(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_IPC_POS,
				     MAC_RCR_IPC_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_mac_address(काष्ठा xlgmac_pdata *pdata, u8 *addr)
अणु
	अचिन्हित पूर्णांक mac_addr_hi, mac_addr_lo;

	mac_addr_hi = (addr[5] <<  8) | (addr[4] <<  0);
	mac_addr_lo = (addr[3] << 24) | (addr[2] << 16) |
		      (addr[1] <<  8) | (addr[0] <<  0);

	ग_लिखोl(mac_addr_hi, pdata->mac_regs + MAC_MACA0HR);
	ग_लिखोl(mac_addr_lo, pdata->mac_regs + MAC_MACA0LR);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_set_mac_reg(काष्ठा xlgmac_pdata *pdata,
			       काष्ठा netdev_hw_addr *ha,
			       अचिन्हित पूर्णांक *mac_reg)
अणु
	अचिन्हित पूर्णांक mac_addr_hi, mac_addr_lo;
	u8 *mac_addr;

	mac_addr_lo = 0;
	mac_addr_hi = 0;

	अगर (ha) अणु
		mac_addr = (u8 *)&mac_addr_lo;
		mac_addr[0] = ha->addr[0];
		mac_addr[1] = ha->addr[1];
		mac_addr[2] = ha->addr[2];
		mac_addr[3] = ha->addr[3];
		mac_addr = (u8 *)&mac_addr_hi;
		mac_addr[0] = ha->addr[4];
		mac_addr[1] = ha->addr[5];

		netअगर_dbg(pdata, drv, pdata->netdev,
			  "adding mac address %pM at %#x\n",
			  ha->addr, *mac_reg);

		mac_addr_hi = XLGMAC_SET_REG_BITS(mac_addr_hi,
						  MAC_MACA1HR_AE_POS,
						MAC_MACA1HR_AE_LEN,
						1);
	पूर्ण

	ग_लिखोl(mac_addr_hi, pdata->mac_regs + *mac_reg);
	*mac_reg += MAC_MACA_INC;
	ग_लिखोl(mac_addr_lo, pdata->mac_regs + *mac_reg);
	*mac_reg += MAC_MACA_INC;
पूर्ण

अटल पूर्णांक xlgmac_enable_rx_vlan_stripping(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_VLANTR);
	/* Put the VLAN tag in the Rx descriptor */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_EVLRXS_POS,
				     MAC_VLANTR_EVLRXS_LEN, 1);
	/* Don't check the VLAN type */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_DOVLTC_POS,
				     MAC_VLANTR_DOVLTC_LEN, 1);
	/* Check only C-TAG (0x8100) packets */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_ERSVLM_POS,
				     MAC_VLANTR_ERSVLM_LEN, 0);
	/* Don't consider an S-TAG (0x88A8) packet as a VLAN packet */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_ESVL_POS,
				     MAC_VLANTR_ESVL_LEN, 0);
	/* Enable VLAN tag stripping */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_EVLS_POS,
				     MAC_VLANTR_EVLS_LEN, 0x3);
	ग_लिखोl(regval, pdata->mac_regs + MAC_VLANTR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_disable_rx_vlan_stripping(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_VLANTR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_EVLS_POS,
				     MAC_VLANTR_EVLS_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_VLANTR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_enable_rx_vlan_filtering(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_PFR);
	/* Enable VLAN filtering */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_VTFE_POS,
				     MAC_PFR_VTFE_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_PFR);

	regval = पढ़ोl(pdata->mac_regs + MAC_VLANTR);
	/* Enable VLAN Hash Table filtering */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VTHM_POS,
				     MAC_VLANTR_VTHM_LEN, 1);
	/* Disable VLAN tag inverse matching */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VTIM_POS,
				     MAC_VLANTR_VTIM_LEN, 0);
	/* Only filter on the lower 12-bits of the VLAN tag */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_ETV_POS,
				     MAC_VLANTR_ETV_LEN, 1);
	/* In order क्रम the VLAN Hash Table filtering to be effective,
	 * the VLAN tag identअगरier in the VLAN Tag Register must not
	 * be zero.  Set the VLAN tag identअगरier to "1" to enable the
	 * VLAN Hash Table filtering.  This implies that a VLAN tag of
	 * 1 will always pass filtering.
	 */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANTR_VL_POS,
				     MAC_VLANTR_VL_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_VLANTR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_disable_rx_vlan_filtering(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_PFR);
	/* Disable VLAN filtering */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_VTFE_POS,
				     MAC_PFR_VTFE_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_PFR);

	वापस 0;
पूर्ण

अटल u32 xlgmac_vid_crc32_le(__le16 vid_le)
अणु
	अचिन्हित अक्षर *data = (अचिन्हित अक्षर *)&vid_le;
	अचिन्हित अक्षर data_byte = 0;
	u32 crc = ~0;
	u32 temp = 0;
	पूर्णांक i, bits;

	bits = get_biपंचांगask_order(VLAN_VID_MASK);
	क्रम (i = 0; i < bits; i++) अणु
		अगर ((i % 8) == 0)
			data_byte = data[i / 8];

		temp = ((crc & 1) ^ data_byte) & 1;
		crc >>= 1;
		data_byte >>= 1;

		अगर (temp)
			crc ^= CRC32_POLY_LE;
	पूर्ण

	वापस crc;
पूर्ण

अटल पूर्णांक xlgmac_update_vlan_hash_table(काष्ठा xlgmac_pdata *pdata)
अणु
	u16 vlan_hash_table = 0;
	__le16 vid_le;
	u32 regval;
	u32 crc;
	u16 vid;

	/* Generate the VLAN Hash Table value */
	क्रम_each_set_bit(vid, pdata->active_vlans, VLAN_N_VID) अणु
		/* Get the CRC32 value of the VLAN ID */
		vid_le = cpu_to_le16(vid);
		crc = bitrev32(~xlgmac_vid_crc32_le(vid_le)) >> 28;

		vlan_hash_table |= (1 << crc);
	पूर्ण

	regval = पढ़ोl(pdata->mac_regs + MAC_VLANHTR);
	/* Set the VLAN Hash Table filtering रेजिस्टर */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANHTR_VLHT_POS,
				     MAC_VLANHTR_VLHT_LEN, vlan_hash_table);
	ग_लिखोl(regval, pdata->mac_regs + MAC_VLANHTR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_promiscuous_mode(काष्ठा xlgmac_pdata *pdata,
				       अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = enable ? 1 : 0;
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_PFR),
				     MAC_PFR_PR_POS, MAC_PFR_PR_LEN);
	अगर (regval == val)
		वापस 0;

	netअगर_dbg(pdata, drv, pdata->netdev, "%s promiscuous mode\n",
		  enable ? "entering" : "leaving");

	regval = पढ़ोl(pdata->mac_regs + MAC_PFR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_PR_POS,
				     MAC_PFR_PR_LEN, val);
	ग_लिखोl(regval, pdata->mac_regs + MAC_PFR);

	/* Hardware will still perक्रमm VLAN filtering in promiscuous mode */
	अगर (enable) अणु
		xlgmac_disable_rx_vlan_filtering(pdata);
	पूर्ण अन्यथा अणु
		अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
			xlgmac_enable_rx_vlan_filtering(pdata);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_all_multicast_mode(काष्ठा xlgmac_pdata *pdata,
					 अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = enable ? 1 : 0;
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_PFR),
				     MAC_PFR_PM_POS, MAC_PFR_PM_LEN);
	अगर (regval == val)
		वापस 0;

	netअगर_dbg(pdata, drv, pdata->netdev, "%s allmulti mode\n",
		  enable ? "entering" : "leaving");

	regval = पढ़ोl(pdata->mac_regs + MAC_PFR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_PM_POS,
				     MAC_PFR_PM_LEN, val);
	ग_लिखोl(regval, pdata->mac_regs + MAC_PFR);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_set_mac_addn_addrs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक addn_macs;
	अचिन्हित पूर्णांक mac_reg;

	mac_reg = MAC_MACA1HR;
	addn_macs = pdata->hw_feat.addn_mac;

	अगर (netdev_uc_count(netdev) > addn_macs) अणु
		xlgmac_set_promiscuous_mode(pdata, 1);
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			xlgmac_set_mac_reg(pdata, ha, &mac_reg);
			addn_macs--;
		पूर्ण

		अगर (netdev_mc_count(netdev) > addn_macs) अणु
			xlgmac_set_all_multicast_mode(pdata, 1);
		पूर्ण अन्यथा अणु
			netdev_क्रम_each_mc_addr(ha, netdev) अणु
				xlgmac_set_mac_reg(pdata, ha, &mac_reg);
				addn_macs--;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Clear reमुख्यing additional MAC address entries */
	जबतक (addn_macs--)
		xlgmac_set_mac_reg(pdata, शून्य, &mac_reg);
पूर्ण

अटल व्योम xlgmac_set_mac_hash_table(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक hash_table_shअगरt, hash_table_count;
	u32 hash_table[XLGMAC_MAC_HASH_TABLE_SIZE];
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक hash_reg;
	अचिन्हित पूर्णांक i;
	u32 crc;

	hash_table_shअगरt = 26 - (pdata->hw_feat.hash_table_size >> 7);
	hash_table_count = pdata->hw_feat.hash_table_size / 32;
	स_रखो(hash_table, 0, माप(hash_table));

	/* Build the MAC Hash Table रेजिस्टर values */
	netdev_क्रम_each_uc_addr(ha, netdev) अणु
		crc = bitrev32(~crc32_le(~0, ha->addr, ETH_ALEN));
		crc >>= hash_table_shअगरt;
		hash_table[crc >> 5] |= (1 << (crc & 0x1f));
	पूर्ण

	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		crc = bitrev32(~crc32_le(~0, ha->addr, ETH_ALEN));
		crc >>= hash_table_shअगरt;
		hash_table[crc >> 5] |= (1 << (crc & 0x1f));
	पूर्ण

	/* Set the MAC Hash Table रेजिस्टरs */
	hash_reg = MAC_HTR0;
	क्रम (i = 0; i < hash_table_count; i++) अणु
		ग_लिखोl(hash_table[i], pdata->mac_regs + hash_reg);
		hash_reg += MAC_HTR_INC;
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_add_mac_addresses(काष्ठा xlgmac_pdata *pdata)
अणु
	अगर (pdata->hw_feat.hash_table_size)
		xlgmac_set_mac_hash_table(pdata);
	अन्यथा
		xlgmac_set_mac_addn_addrs(pdata);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_mac_address(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	xlgmac_set_mac_address(pdata, pdata->netdev->dev_addr);

	/* Filtering is करोne using perfect filtering and hash filtering */
	अगर (pdata->hw_feat.hash_table_size) अणु
		regval = पढ़ोl(pdata->mac_regs + MAC_PFR);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HPF_POS,
					     MAC_PFR_HPF_LEN, 1);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HUC_POS,
					     MAC_PFR_HUC_LEN, 1);
		regval = XLGMAC_SET_REG_BITS(regval, MAC_PFR_HMC_POS,
					     MAC_PFR_HMC_LEN, 1);
		ग_लिखोl(regval, pdata->mac_regs + MAC_PFR);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_config_jumbo_enable(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक val;
	u32 regval;

	val = (pdata->netdev->mtu > XLGMAC_STD_PACKET_MTU) ? 1 : 0;

	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_JE_POS,
				     MAC_RCR_JE_LEN, val);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);
पूर्ण

अटल व्योम xlgmac_config_checksum_offload(काष्ठा xlgmac_pdata *pdata)
अणु
	अगर (pdata->netdev->features & NETIF_F_RXCSUM)
		xlgmac_enable_rx_csum(pdata);
	अन्यथा
		xlgmac_disable_rx_csum(pdata);
पूर्ण

अटल व्योम xlgmac_config_vlan_support(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_VLANIR);
	/* Indicate that VLAN Tx CTAGs come from context descriptors */
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANIR_CSVL_POS,
				     MAC_VLANIR_CSVL_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_VLANIR_VLTI_POS,
				     MAC_VLANIR_VLTI_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_VLANIR);

	/* Set the current VLAN Hash Table रेजिस्टर value */
	xlgmac_update_vlan_hash_table(pdata);

	अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		xlgmac_enable_rx_vlan_filtering(pdata);
	अन्यथा
		xlgmac_disable_rx_vlan_filtering(pdata);

	अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		xlgmac_enable_rx_vlan_stripping(pdata);
	अन्यथा
		xlgmac_disable_rx_vlan_stripping(pdata);
पूर्ण

अटल पूर्णांक xlgmac_config_rx_mode(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक pr_mode, am_mode;

	pr_mode = ((netdev->flags & IFF_PROMISC) != 0);
	am_mode = ((netdev->flags & IFF_ALLMULTI) != 0);

	xlgmac_set_promiscuous_mode(pdata, pr_mode);
	xlgmac_set_all_multicast_mode(pdata, am_mode);

	xlgmac_add_mac_addresses(pdata);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_prepare_tx_stop(काष्ठा xlgmac_pdata *pdata,
				   काष्ठा xlgmac_channel *channel)
अणु
	अचिन्हित पूर्णांक tx_dsr, tx_pos, tx_qidx;
	अचिन्हित दीर्घ tx_समयout;
	अचिन्हित पूर्णांक tx_status;

	/* Calculate the status रेजिस्टर to पढ़ो and the position within */
	अगर (channel->queue_index < DMA_DSRX_FIRST_QUEUE) अणु
		tx_dsr = DMA_DSR0;
		tx_pos = (channel->queue_index * DMA_DSR_Q_LEN) +
			 DMA_DSR0_TPS_START;
	पूर्ण अन्यथा अणु
		tx_qidx = channel->queue_index - DMA_DSRX_FIRST_QUEUE;

		tx_dsr = DMA_DSR1 + ((tx_qidx / DMA_DSRX_QPR) * DMA_DSRX_INC);
		tx_pos = ((tx_qidx % DMA_DSRX_QPR) * DMA_DSR_Q_LEN) +
			 DMA_DSRX_TPS_START;
	पूर्ण

	/* The Tx engine cannot be stopped अगर it is actively processing
	 * descriptors. Wait क्रम the Tx engine to enter the stopped or
	 * suspended state.  Don't रुको क्रमever though...
	 */
	tx_समयout = jअगरfies + (XLGMAC_DMA_STOP_TIMEOUT * HZ);
	जबतक (समय_beक्रमe(jअगरfies, tx_समयout)) अणु
		tx_status = पढ़ोl(pdata->mac_regs + tx_dsr);
		tx_status = XLGMAC_GET_REG_BITS(tx_status, tx_pos,
						DMA_DSR_TPS_LEN);
		अगर ((tx_status == DMA_TPS_STOPPED) ||
		    (tx_status == DMA_TPS_SUSPENDED))
			अवरोध;

		usleep_range(500, 1000);
	पूर्ण

	अगर (!समय_beक्रमe(jअगरfies, tx_समयout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Tx DMA channel %u to stop\n",
			    channel->queue_index);
पूर्ण

अटल व्योम xlgmac_enable_tx(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	/* Enable each Tx DMA channel */
	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_ST_POS,
					     DMA_CH_TCR_ST_LEN, 1);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
	पूर्ण

	/* Enable each Tx queue */
	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TXQEN_POS,
					     MTL_Q_TQOMR_TXQEN_LEN,
					MTL_Q_ENABLED);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	/* Enable MAC Tx */
	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_TE_POS,
				     MAC_TCR_TE_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);
पूर्ण

अटल व्योम xlgmac_disable_tx(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	/* Prepare क्रम Tx DMA channel stop */
	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		xlgmac_prepare_tx_stop(pdata, channel);
	पूर्ण

	/* Disable MAC Tx */
	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_TE_POS,
				     MAC_TCR_TE_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);

	/* Disable each Tx queue */
	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TXQEN_POS,
					     MTL_Q_TQOMR_TXQEN_LEN, 0);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	/* Disable each Tx DMA channel */
	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_ST_POS,
					     DMA_CH_TCR_ST_LEN, 0);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_prepare_rx_stop(काष्ठा xlgmac_pdata *pdata,
				   अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक rx_status, prxq, rxqsts;
	अचिन्हित दीर्घ rx_समयout;

	/* The Rx engine cannot be stopped अगर it is actively processing
	 * packets. Wait क्रम the Rx queue to empty the Rx fअगरo.  Don't
	 * रुको क्रमever though...
	 */
	rx_समयout = jअगरfies + (XLGMAC_DMA_STOP_TIMEOUT * HZ);
	जबतक (समय_beक्रमe(jअगरfies, rx_समयout)) अणु
		rx_status = पढ़ोl(XLGMAC_MTL_REG(pdata, queue, MTL_Q_RQDR));
		prxq = XLGMAC_GET_REG_BITS(rx_status, MTL_Q_RQDR_PRXQ_POS,
					   MTL_Q_RQDR_PRXQ_LEN);
		rxqsts = XLGMAC_GET_REG_BITS(rx_status, MTL_Q_RQDR_RXQSTS_POS,
					     MTL_Q_RQDR_RXQSTS_LEN);
		अगर ((prxq == 0) && (rxqsts == 0))
			अवरोध;

		usleep_range(500, 1000);
	पूर्ण

	अगर (!समय_beक्रमe(jअगरfies, rx_समयout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Rx queue %u to empty\n",
			    queue);
पूर्ण

अटल व्योम xlgmac_enable_rx(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक regval, i;

	/* Enable each Rx DMA channel */
	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_RCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RCR_SR_POS,
					     DMA_CH_RCR_SR_LEN, 1);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_RCR));
	पूर्ण

	/* Enable each Rx queue */
	regval = 0;
	क्रम (i = 0; i < pdata->rx_q_count; i++)
		regval |= (0x02 << (i << 1));
	ग_लिखोl(regval, pdata->mac_regs + MAC_RQC0R);

	/* Enable MAC Rx */
	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_DCRCC_POS,
				     MAC_RCR_DCRCC_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_CST_POS,
				     MAC_RCR_CST_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_ACS_POS,
				     MAC_RCR_ACS_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_RE_POS,
				     MAC_RCR_RE_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);
पूर्ण

अटल व्योम xlgmac_disable_rx(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	/* Disable MAC Rx */
	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_DCRCC_POS,
				     MAC_RCR_DCRCC_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_CST_POS,
				     MAC_RCR_CST_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_ACS_POS,
				     MAC_RCR_ACS_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_RE_POS,
				     MAC_RCR_RE_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);

	/* Prepare क्रम Rx DMA channel stop */
	क्रम (i = 0; i < pdata->rx_q_count; i++)
		xlgmac_prepare_rx_stop(pdata, i);

	/* Disable each Rx queue */
	ग_लिखोl(0, pdata->mac_regs + MAC_RQC0R);

	/* Disable each Rx DMA channel */
	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_RCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RCR_SR_POS,
					     DMA_CH_RCR_SR_LEN, 0);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_RCR));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_tx_start_xmit(काष्ठा xlgmac_channel *channel,
				 काष्ठा xlgmac_ring *ring)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_desc_data *desc_data;

	/* Make sure everything is written beक्रमe the रेजिस्टर ग_लिखो */
	wmb();

	/* Issue a poll command to Tx DMA by writing address
	 * of next immediate मुक्त descriptor
	 */
	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	ग_लिखोl(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDTR_LO));

	/* Start the Tx समयr */
	अगर (pdata->tx_usecs && !channel->tx_समयr_active) अणु
		channel->tx_समयr_active = 1;
		mod_समयr(&channel->tx_समयr,
			  jअगरfies + usecs_to_jअगरfies(pdata->tx_usecs));
	पूर्ण

	ring->tx.xmit_more = 0;
पूर्ण

अटल व्योम xlgmac_dev_xmit(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->tx_ring;
	अचिन्हित पूर्णांक tso_context, vlan_context;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;
	काष्ठा xlgmac_pkt_info *pkt_info;
	अचिन्हित पूर्णांक csum, tso, vlan;
	पूर्णांक start_index = ring->cur;
	पूर्णांक cur_index = ring->cur;
	अचिन्हित पूर्णांक tx_set_ic;
	पूर्णांक i;

	pkt_info = &ring->pkt_info;
	csum = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				   TX_PACKET_ATTRIBUTES_CSUM_ENABLE_POS,
				TX_PACKET_ATTRIBUTES_CSUM_ENABLE_LEN);
	tso = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				  TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS,
				TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN);
	vlan = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				   TX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
				TX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN);

	अगर (tso && (pkt_info->mss != ring->tx.cur_mss))
		tso_context = 1;
	अन्यथा
		tso_context = 0;

	अगर (vlan && (pkt_info->vlan_ctag != ring->tx.cur_vlan_ctag))
		vlan_context = 1;
	अन्यथा
		vlan_context = 0;

	/* Determine अगर an पूर्णांकerrupt should be generated क्रम this Tx:
	 *   Interrupt:
	 *     - Tx frame count exceeds the frame count setting
	 *     - Addition of Tx frame count to the frame count since the
	 *       last पूर्णांकerrupt was set exceeds the frame count setting
	 *   No पूर्णांकerrupt:
	 *     - No frame count setting specअगरied (ethtool -C ethX tx-frames 0)
	 *     - Addition of Tx frame count to the frame count since the
	 *       last पूर्णांकerrupt was set करोes not exceed the frame count setting
	 */
	ring->coalesce_count += pkt_info->tx_packets;
	अगर (!pdata->tx_frames)
		tx_set_ic = 0;
	अन्यथा अगर (pkt_info->tx_packets > pdata->tx_frames)
		tx_set_ic = 1;
	अन्यथा अगर ((ring->coalesce_count % pdata->tx_frames) <
		 pkt_info->tx_packets)
		tx_set_ic = 1;
	अन्यथा
		tx_set_ic = 0;

	desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
	dma_desc = desc_data->dma_desc;

	/* Create a context descriptor अगर this is a TSO pkt_info */
	अगर (tso_context || vlan_context) अणु
		अगर (tso_context) अणु
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "TSO context descriptor, mss=%u\n",
				  pkt_info->mss);

			/* Set the MSS size */
			dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc2,
						TX_CONTEXT_DESC2_MSS_POS,
						TX_CONTEXT_DESC2_MSS_LEN,
						pkt_info->mss);

			/* Mark it as a CONTEXT descriptor */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_CTXT_POS,
						TX_CONTEXT_DESC3_CTXT_LEN,
						1);

			/* Indicate this descriptor contains the MSS */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_TCMSSV_POS,
						TX_CONTEXT_DESC3_TCMSSV_LEN,
						1);

			ring->tx.cur_mss = pkt_info->mss;
		पूर्ण

		अगर (vlan_context) अणु
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "VLAN context descriptor, ctag=%u\n",
				  pkt_info->vlan_ctag);

			/* Mark it as a CONTEXT descriptor */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_CTXT_POS,
						TX_CONTEXT_DESC3_CTXT_LEN,
						1);

			/* Set the VLAN tag */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_VT_POS,
						TX_CONTEXT_DESC3_VT_LEN,
						pkt_info->vlan_ctag);

			/* Indicate this descriptor contains the VLAN tag */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_VLTV_POS,
						TX_CONTEXT_DESC3_VLTV_LEN,
						1);

			ring->tx.cur_vlan_ctag = pkt_info->vlan_ctag;
		पूर्ण

		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
		dma_desc = desc_data->dma_desc;
	पूर्ण

	/* Update buffer address (क्रम TSO this is the header) */
	dma_desc->desc0 =  cpu_to_le32(lower_32_bits(desc_data->skb_dma));
	dma_desc->desc1 =  cpu_to_le32(upper_32_bits(desc_data->skb_dma));

	/* Update the buffer length */
	dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc2,
				TX_NORMAL_DESC2_HL_B1L_POS,
				TX_NORMAL_DESC2_HL_B1L_LEN,
				desc_data->skb_dma_len);

	/* VLAN tag insertion check */
	अगर (vlan) अणु
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_VTIR_POS,
					TX_NORMAL_DESC2_VTIR_LEN,
					TX_NORMAL_DESC2_VLAN_INSERT);
		pdata->stats.tx_vlan_packets++;
	पूर्ण

	/* Timestamp enablement check */
	अगर (XLGMAC_GET_REG_BITS(pkt_info->attributes,
				TX_PACKET_ATTRIBUTES_PTP_POS,
				TX_PACKET_ATTRIBUTES_PTP_LEN))
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_TTSE_POS,
					TX_NORMAL_DESC2_TTSE_LEN,
					1);

	/* Mark it as First Descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_FD_POS,
				TX_NORMAL_DESC3_FD_LEN,
				1);

	/* Mark it as a NORMAL descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_CTXT_POS,
				TX_NORMAL_DESC3_CTXT_LEN,
				0);

	/* Set OWN bit अगर not the first descriptor */
	अगर (cur_index != start_index)
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_OWN_POS,
					TX_NORMAL_DESC3_OWN_LEN,
					1);

	अगर (tso) अणु
		/* Enable TSO */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TSE_POS,
					TX_NORMAL_DESC3_TSE_LEN, 1);
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TCPPL_POS,
					TX_NORMAL_DESC3_TCPPL_LEN,
					pkt_info->tcp_payload_len);
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TCPHDRLEN_POS,
					TX_NORMAL_DESC3_TCPHDRLEN_LEN,
					pkt_info->tcp_header_len / 4);

		pdata->stats.tx_tso_packets++;
	पूर्ण अन्यथा अणु
		/* Enable CRC and Pad Insertion */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_CPC_POS,
					TX_NORMAL_DESC3_CPC_LEN, 0);

		/* Enable HW CSUM */
		अगर (csum)
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_NORMAL_DESC3_CIC_POS,
						TX_NORMAL_DESC3_CIC_LEN,
						0x3);

		/* Set the total length to be transmitted */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_FL_POS,
					TX_NORMAL_DESC3_FL_LEN,
					pkt_info->length);
	पूर्ण

	क्रम (i = cur_index - start_index + 1; i < pkt_info->desc_count; i++) अणु
		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
		dma_desc = desc_data->dma_desc;

		/* Update buffer address */
		dma_desc->desc0 =
			cpu_to_le32(lower_32_bits(desc_data->skb_dma));
		dma_desc->desc1 =
			cpu_to_le32(upper_32_bits(desc_data->skb_dma));

		/* Update the buffer length */
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_HL_B1L_POS,
					TX_NORMAL_DESC2_HL_B1L_LEN,
					desc_data->skb_dma_len);

		/* Set OWN bit */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_OWN_POS,
					TX_NORMAL_DESC3_OWN_LEN, 1);

		/* Mark it as NORMAL descriptor */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_CTXT_POS,
					TX_NORMAL_DESC3_CTXT_LEN, 0);

		/* Enable HW CSUM */
		अगर (csum)
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_NORMAL_DESC3_CIC_POS,
						TX_NORMAL_DESC3_CIC_LEN,
						0x3);
	पूर्ण

	/* Set LAST bit क्रम the last descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_LD_POS,
				TX_NORMAL_DESC3_LD_LEN, 1);

	/* Set IC bit based on Tx coalescing settings */
	अगर (tx_set_ic)
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_IC_POS,
					TX_NORMAL_DESC2_IC_LEN, 1);

	/* Save the Tx info to report back during cleanup */
	desc_data->tx.packets = pkt_info->tx_packets;
	desc_data->tx.bytes = pkt_info->tx_bytes;

	/* In हाल the Tx DMA engine is running, make sure everything
	 * is written to the descriptor(s) beक्रमe setting the OWN bit
	 * क्रम the first descriptor
	 */
	dma_wmb();

	/* Set OWN bit क्रम the first descriptor */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index);
	dma_desc = desc_data->dma_desc;
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_OWN_POS,
				TX_NORMAL_DESC3_OWN_LEN, 1);

	अगर (netअगर_msg_tx_queued(pdata))
		xlgmac_dump_tx_desc(pdata, ring, start_index,
				    pkt_info->desc_count, 1);

	/* Make sure ownership is written to the descriptor */
	smp_wmb();

	ring->cur = cur_index + 1;
	अगर (!netdev_xmit_more() ||
	    netअगर_xmit_stopped(netdev_get_tx_queue(pdata->netdev,
						   channel->queue_index)))
		xlgmac_tx_start_xmit(channel, ring);
	अन्यथा
		ring->tx.xmit_more = 1;

	XLGMAC_PR("%s: descriptors %u to %u written\n",
		  channel->name, start_index & (ring->dma_desc_count - 1),
		  (ring->cur - 1) & (ring->dma_desc_count - 1));
पूर्ण

अटल व्योम xlgmac_get_rx_tstamp(काष्ठा xlgmac_pkt_info *pkt_info,
				 काष्ठा xlgmac_dma_desc *dma_desc)
अणु
	u32 tsa, tsd;
	u64 nsec;

	tsa = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_CONTEXT_DESC3_TSA_POS,
				RX_CONTEXT_DESC3_TSA_LEN);
	tsd = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_CONTEXT_DESC3_TSD_POS,
				RX_CONTEXT_DESC3_TSD_LEN);
	अगर (tsa && !tsd) अणु
		nsec = le32_to_cpu(dma_desc->desc1);
		nsec <<= 32;
		nsec |= le32_to_cpu(dma_desc->desc0);
		अगर (nsec != 0xffffffffffffffffULL) अणु
			pkt_info->rx_tstamp = nsec;
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_RX_TSTAMP_POS,
					RX_PACKET_ATTRIBUTES_RX_TSTAMP_LEN,
					1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xlgmac_tx_desc_reset(काष्ठा xlgmac_desc_data *desc_data)
अणु
	काष्ठा xlgmac_dma_desc *dma_desc = desc_data->dma_desc;

	/* Reset the Tx descriptor
	 *   Set buffer 1 (lo) address to zero
	 *   Set buffer 1 (hi) address to zero
	 *   Reset all other control bits (IC, TTSE, B2L & B1L)
	 *   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
	 */
	dma_desc->desc0 = 0;
	dma_desc->desc1 = 0;
	dma_desc->desc2 = 0;
	dma_desc->desc3 = 0;

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
पूर्ण

अटल व्योम xlgmac_tx_desc_init(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_ring *ring = channel->tx_ring;
	काष्ठा xlgmac_desc_data *desc_data;
	पूर्णांक start_index = ring->cur;
	पूर्णांक i;

	/* Initialze all descriptors */
	क्रम (i = 0; i < ring->dma_desc_count; i++) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, i);

		/* Initialize Tx descriptor */
		xlgmac_tx_desc_reset(desc_data);
	पूर्ण

	/* Update the total number of Tx descriptors */
	ग_लिखोl(ring->dma_desc_count - 1, XLGMAC_DMA_REG(channel, DMA_CH_TDRLR));

	/* Update the starting address of descriptor ring */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index);
	ग_लिखोl(upper_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDLR_HI));
	ग_लिखोl(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_TDLR_LO));
पूर्ण

अटल व्योम xlgmac_rx_desc_reset(काष्ठा xlgmac_pdata *pdata,
				 काष्ठा xlgmac_desc_data *desc_data,
				 अचिन्हित पूर्णांक index)
अणु
	काष्ठा xlgmac_dma_desc *dma_desc = desc_data->dma_desc;
	अचिन्हित पूर्णांक rx_frames = pdata->rx_frames;
	अचिन्हित पूर्णांक rx_usecs = pdata->rx_usecs;
	dma_addr_t hdr_dma, buf_dma;
	अचिन्हित पूर्णांक पूर्णांकe;

	अगर (!rx_usecs && !rx_frames) अणु
		/* No coalescing, पूर्णांकerrupt क्रम every descriptor */
		पूर्णांकe = 1;
	पूर्ण अन्यथा अणु
		/* Set पूर्णांकerrupt based on Rx frame coalescing setting */
		अगर (rx_frames && !((index + 1) % rx_frames))
			पूर्णांकe = 1;
		अन्यथा
			पूर्णांकe = 0;
	पूर्ण

	/* Reset the Rx descriptor
	 *   Set buffer 1 (lo) address to header dma address (lo)
	 *   Set buffer 1 (hi) address to header dma address (hi)
	 *   Set buffer 2 (lo) address to buffer dma address (lo)
	 *   Set buffer 2 (hi) address to buffer dma address (hi) and
	 *     set control bits OWN and INTE
	 */
	hdr_dma = desc_data->rx.hdr.dma_base + desc_data->rx.hdr.dma_off;
	buf_dma = desc_data->rx.buf.dma_base + desc_data->rx.buf.dma_off;
	dma_desc->desc0 = cpu_to_le32(lower_32_bits(hdr_dma));
	dma_desc->desc1 = cpu_to_le32(upper_32_bits(hdr_dma));
	dma_desc->desc2 = cpu_to_le32(lower_32_bits(buf_dma));
	dma_desc->desc3 = cpu_to_le32(upper_32_bits(buf_dma));

	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				RX_NORMAL_DESC3_INTE_POS,
				RX_NORMAL_DESC3_INTE_LEN,
				पूर्णांकe);

	/* Since the Rx DMA engine is likely running, make sure everything
	 * is written to the descriptor(s) beक्रमe setting the OWN bit
	 * क्रम the descriptor
	 */
	dma_wmb();

	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				RX_NORMAL_DESC3_OWN_POS,
				RX_NORMAL_DESC3_OWN_LEN,
				1);

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
पूर्ण

अटल व्योम xlgmac_rx_desc_init(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->rx_ring;
	अचिन्हित पूर्णांक start_index = ring->cur;
	काष्ठा xlgmac_desc_data *desc_data;
	अचिन्हित पूर्णांक i;

	/* Initialize all descriptors */
	क्रम (i = 0; i < ring->dma_desc_count; i++) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, i);

		/* Initialize Rx descriptor */
		xlgmac_rx_desc_reset(pdata, desc_data, i);
	पूर्ण

	/* Update the total number of Rx descriptors */
	ग_लिखोl(ring->dma_desc_count - 1, XLGMAC_DMA_REG(channel, DMA_CH_RDRLR));

	/* Update the starting address of descriptor ring */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index);
	ग_लिखोl(upper_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_RDLR_HI));
	ग_लिखोl(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_RDLR_LO));

	/* Update the Rx Descriptor Tail Poपूर्णांकer */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index +
					  ring->dma_desc_count - 1);
	ग_लिखोl(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_RDTR_LO));
पूर्ण

अटल पूर्णांक xlgmac_is_context_desc(काष्ठा xlgmac_dma_desc *dma_desc)
अणु
	/* Rx and Tx share CTXT bit, so check TDES3.CTXT bit */
	वापस XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				TX_NORMAL_DESC3_CTXT_POS,
				TX_NORMAL_DESC3_CTXT_LEN);
पूर्ण

अटल पूर्णांक xlgmac_is_last_desc(काष्ठा xlgmac_dma_desc *dma_desc)
अणु
	/* Rx and Tx share LD bit, so check TDES3.LD bit */
	वापस XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				TX_NORMAL_DESC3_LD_POS,
				TX_NORMAL_DESC3_LD_LEN);
पूर्ण

अटल पूर्णांक xlgmac_disable_tx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक max_q_count, q_count;
	अचिन्हित पूर्णांक reg, regval;
	अचिन्हित पूर्णांक i;

	/* Clear MTL flow control */
	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_EHFC_POS,
					     MTL_Q_RQOMR_EHFC_LEN, 0);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण

	/* Clear MAC flow control */
	max_q_count = XLGMAC_MAX_FLOW_CONTROL_QUEUES;
	q_count = min_t(अचिन्हित पूर्णांक, pdata->tx_q_count, max_q_count);
	reg = MAC_Q0TFCR;
	क्रम (i = 0; i < q_count; i++) अणु
		regval = पढ़ोl(pdata->mac_regs + reg);
		regval = XLGMAC_SET_REG_BITS(regval,
					     MAC_Q0TFCR_TFE_POS,
					MAC_Q0TFCR_TFE_LEN,
					0);
		ग_लिखोl(regval, pdata->mac_regs + reg);

		reg += MAC_QTFCR_INC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_enable_tx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक max_q_count, q_count;
	अचिन्हित पूर्णांक reg, regval;
	अचिन्हित पूर्णांक i;

	/* Set MTL flow control */
	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_EHFC_POS,
					     MTL_Q_RQOMR_EHFC_LEN, 1);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण

	/* Set MAC flow control */
	max_q_count = XLGMAC_MAX_FLOW_CONTROL_QUEUES;
	q_count = min_t(अचिन्हित पूर्णांक, pdata->tx_q_count, max_q_count);
	reg = MAC_Q0TFCR;
	क्रम (i = 0; i < q_count; i++) अणु
		regval = पढ़ोl(pdata->mac_regs + reg);

		/* Enable transmit flow control */
		regval = XLGMAC_SET_REG_BITS(regval, MAC_Q0TFCR_TFE_POS,
					     MAC_Q0TFCR_TFE_LEN, 1);
		/* Set छोड़ो समय */
		regval = XLGMAC_SET_REG_BITS(regval, MAC_Q0TFCR_PT_POS,
					     MAC_Q0TFCR_PT_LEN, 0xffff);

		ग_लिखोl(regval, pdata->mac_regs + reg);

		reg += MAC_QTFCR_INC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_disable_rx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_RFCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RFCR_RFE_POS,
				     MAC_RFCR_RFE_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RFCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_enable_rx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MAC_RFCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RFCR_RFE_POS,
				     MAC_RFCR_RFE_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RFCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_tx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	अगर (pdata->tx_छोड़ो)
		xlgmac_enable_tx_flow_control(pdata);
	अन्यथा
		xlgmac_disable_tx_flow_control(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_rx_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	अगर (pdata->rx_छोड़ो)
		xlgmac_enable_rx_flow_control(pdata);
	अन्यथा
		xlgmac_disable_rx_flow_control(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_rx_coalesce(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_RIWT));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RIWT_RWT_POS,
					     DMA_CH_RIWT_RWT_LEN,
					     pdata->rx_riwt);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_RIWT));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_flow_control(काष्ठा xlgmac_pdata *pdata)
अणु
	xlgmac_config_tx_flow_control(pdata);
	xlgmac_config_rx_flow_control(pdata);
पूर्ण

अटल व्योम xlgmac_config_rx_fep_enable(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_FEP_POS,
					     MTL_Q_RQOMR_FEP_LEN, 1);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_config_rx_fup_enable(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_FUP_POS,
					     MTL_Q_RQOMR_FUP_LEN, 1);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_config_tx_coalesce(काष्ठा xlgmac_pdata *pdata)
अणु
	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_rx_buffer_size(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_RCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RCR_RBSZ_POS,
					     DMA_CH_RCR_RBSZ_LEN,
					pdata->rx_buf_size);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_RCR));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_config_tso_mode(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		अगर (pdata->hw_feat.tso) अणु
			regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
			regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_TSE_POS,
						     DMA_CH_TCR_TSE_LEN, 1);
			ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xlgmac_config_sph_mode(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_CR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_CR_SPH_POS,
					     DMA_CH_CR_SPH_LEN, 1);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_CR));
	पूर्ण

	regval = पढ़ोl(pdata->mac_regs + MAC_RCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RCR_HDSMS_POS,
				     MAC_RCR_HDSMS_LEN,
				XLGMAC_SPH_HDSMS_SIZE);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RCR);
पूर्ण

अटल अचिन्हित पूर्णांक xlgmac_usec_to_riwt(काष्ठा xlgmac_pdata *pdata,
					अचिन्हित पूर्णांक usec)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक ret;

	rate = pdata->sysclk_rate;

	/* Convert the input usec value to the watchकरोg समयr value. Each
	 * watchकरोg समयr value is equivalent to 256 घड़ी cycles.
	 * Calculate the required value as:
	 *   ( usec * ( प्रणाली_घड़ी_mhz / 10^6 ) / 256
	 */
	ret = (usec * (rate / 1000000)) / 256;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक xlgmac_riwt_to_usec(काष्ठा xlgmac_pdata *pdata,
					अचिन्हित पूर्णांक riwt)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक ret;

	rate = pdata->sysclk_rate;

	/* Convert the input watchकरोg समयr value to the usec value. Each
	 * watchकरोg समयr value is equivalent to 256 घड़ी cycles.
	 * Calculate the required value as:
	 *   ( riwt * 256 ) / ( प्रणाली_घड़ी_mhz / 10^6 )
	 */
	ret = (riwt * 256) / (rate / 1000000);

	वापस ret;
पूर्ण

अटल पूर्णांक xlgmac_config_rx_threshold(काष्ठा xlgmac_pdata *pdata,
				      अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_RTC_POS,
					     MTL_Q_RQOMR_RTC_LEN, val);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_mtl_mode(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	/* Set Tx to weighted round robin scheduling algorithm */
	regval = पढ़ोl(pdata->mac_regs + MTL_OMR);
	regval = XLGMAC_SET_REG_BITS(regval, MTL_OMR_ETSALG_POS,
				     MTL_OMR_ETSALG_LEN, MTL_ETSALG_WRR);
	ग_लिखोl(regval, pdata->mac_regs + MTL_OMR);

	/* Set Tx traffic classes to use WRR algorithm with equal weights */
	क्रम (i = 0; i < pdata->hw_feat.tc_cnt; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_TC_ETSCR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_TC_ETSCR_TSA_POS,
					     MTL_TC_ETSCR_TSA_LEN, MTL_TSA_ETS);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_TC_ETSCR));

		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_TC_QWR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_TC_QWR_QW_POS,
					     MTL_TC_QWR_QW_LEN, 1);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_TC_QWR));
	पूर्ण

	/* Set Rx to strict priority algorithm */
	regval = पढ़ोl(pdata->mac_regs + MTL_OMR);
	regval = XLGMAC_SET_REG_BITS(regval, MTL_OMR_RAA_POS,
				     MTL_OMR_RAA_LEN, MTL_RAA_SP);
	ग_लिखोl(regval, pdata->mac_regs + MTL_OMR);
पूर्ण

अटल व्योम xlgmac_config_queue_mapping(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक ppq, ppq_extra, prio, prio_queues;
	अचिन्हित पूर्णांक qptc, qptc_extra, queue;
	अचिन्हित पूर्णांक reg, regval;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक i, j;

	/* Map the MTL Tx Queues to Traffic Classes
	 *   Note: Tx Queues >= Traffic Classes
	 */
	qptc = pdata->tx_q_count / pdata->hw_feat.tc_cnt;
	qptc_extra = pdata->tx_q_count % pdata->hw_feat.tc_cnt;

	क्रम (i = 0, queue = 0; i < pdata->hw_feat.tc_cnt; i++) अणु
		क्रम (j = 0; j < qptc; j++) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TXq%u mapped to TC%u\n", queue, i);
			regval = पढ़ोl(XLGMAC_MTL_REG(pdata, queue,
						      MTL_Q_TQOMR));
			regval = XLGMAC_SET_REG_BITS(regval,
						     MTL_Q_TQOMR_Q2TCMAP_POS,
						     MTL_Q_TQOMR_Q2TCMAP_LEN,
						     i);
			ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, queue,
						      MTL_Q_TQOMR));
			queue++;
		पूर्ण

		अगर (i < qptc_extra) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TXq%u mapped to TC%u\n", queue, i);
			regval = पढ़ोl(XLGMAC_MTL_REG(pdata, queue,
						      MTL_Q_TQOMR));
			regval = XLGMAC_SET_REG_BITS(regval,
						     MTL_Q_TQOMR_Q2TCMAP_POS,
						     MTL_Q_TQOMR_Q2TCMAP_LEN,
						     i);
			ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, queue,
						      MTL_Q_TQOMR));
			queue++;
		पूर्ण
	पूर्ण

	/* Map the 8 VLAN priority values to available MTL Rx queues */
	prio_queues = min_t(अचिन्हित पूर्णांक, IEEE_8021QAZ_MAX_TCS,
			    pdata->rx_q_count);
	ppq = IEEE_8021QAZ_MAX_TCS / prio_queues;
	ppq_extra = IEEE_8021QAZ_MAX_TCS % prio_queues;

	reg = MAC_RQC2R;
	regval = 0;
	क्रम (i = 0, prio = 0; i < prio_queues;) अणु
		mask = 0;
		क्रम (j = 0; j < ppq; j++) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "PRIO%u mapped to RXq%u\n", prio, i);
			mask |= (1 << prio);
			prio++;
		पूर्ण

		अगर (i < ppq_extra) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "PRIO%u mapped to RXq%u\n", prio, i);
			mask |= (1 << prio);
			prio++;
		पूर्ण

		regval |= (mask << ((i++ % MAC_RQC2_Q_PER_REG) << 3));

		अगर ((i % MAC_RQC2_Q_PER_REG) && (i != prio_queues))
			जारी;

		ग_लिखोl(regval, pdata->mac_regs + reg);
		reg += MAC_RQC2_INC;
		regval = 0;
	पूर्ण

	/* Configure one to one, MTL Rx queue to DMA Rx channel mapping
	 *  ie Q0 <--> CH0, Q1 <--> CH1 ... Q11 <--> CH11
	 */
	reg = MTL_RQDCM0R;
	regval = पढ़ोl(pdata->mac_regs + reg);
	regval |= (MTL_RQDCM0R_Q0MDMACH | MTL_RQDCM0R_Q1MDMACH |
		    MTL_RQDCM0R_Q2MDMACH | MTL_RQDCM0R_Q3MDMACH);
	ग_लिखोl(regval, pdata->mac_regs + reg);

	reg += MTL_RQDCM_INC;
	regval = पढ़ोl(pdata->mac_regs + reg);
	regval |= (MTL_RQDCM1R_Q4MDMACH | MTL_RQDCM1R_Q5MDMACH |
		    MTL_RQDCM1R_Q6MDMACH | MTL_RQDCM1R_Q7MDMACH);
	ग_लिखोl(regval, pdata->mac_regs + reg);

	reg += MTL_RQDCM_INC;
	regval = पढ़ोl(pdata->mac_regs + reg);
	regval |= (MTL_RQDCM2R_Q8MDMACH | MTL_RQDCM2R_Q9MDMACH |
		    MTL_RQDCM2R_Q10MDMACH | MTL_RQDCM2R_Q11MDMACH);
	ग_लिखोl(regval, pdata->mac_regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक xlgmac_calculate_per_queue_fअगरo(
					अचिन्हित पूर्णांक fअगरo_size,
					अचिन्हित पूर्णांक queue_count)
अणु
	अचिन्हित पूर्णांक q_fअगरo_size;
	अचिन्हित पूर्णांक p_fअगरo;

	/* Calculate the configured fअगरo size */
	q_fअगरo_size = 1 << (fअगरo_size + 7);

	/* The configured value may not be the actual amount of fअगरo RAM */
	q_fअगरo_size = min_t(अचिन्हित पूर्णांक, XLGMAC_MAX_FIFO, q_fअगरo_size);

	q_fअगरo_size = q_fअगरo_size / queue_count;

	/* Each increment in the queue fअगरo size represents 256 bytes of
	 * fअगरo, with 0 representing 256 bytes. Distribute the fअगरo equally
	 * between the queues.
	 */
	p_fअगरo = q_fअगरo_size / 256;
	अगर (p_fअगरo)
		p_fअगरo--;

	वापस p_fअगरo;
पूर्ण

अटल व्योम xlgmac_config_tx_fअगरo_size(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक i;
	u32 regval;

	fअगरo_size = xlgmac_calculate_per_queue_fअगरo(
				pdata->hw_feat.tx_fअगरo_size,
				pdata->tx_q_count);

	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TQS_POS,
					     MTL_Q_TQOMR_TQS_LEN, fअगरo_size);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	netअगर_info(pdata, drv, pdata->netdev,
		   "%d Tx hardware queues, %d byte fifo per queue\n",
		   pdata->tx_q_count, ((fअगरo_size + 1) * 256));
पूर्ण

अटल व्योम xlgmac_config_rx_fअगरo_size(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक i;
	u32 regval;

	fअगरo_size = xlgmac_calculate_per_queue_fअगरo(
					pdata->hw_feat.rx_fअगरo_size,
					pdata->rx_q_count);

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_RQS_POS,
					     MTL_Q_RQOMR_RQS_LEN, fअगरo_size);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण

	netअगर_info(pdata, drv, pdata->netdev,
		   "%d Rx hardware queues, %d byte fifo per queue\n",
		   pdata->rx_q_count, ((fअगरo_size + 1) * 256));
पूर्ण

अटल व्योम xlgmac_config_flow_control_threshold(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQFCR));
		/* Activate flow control when less than 4k left in fअगरo */
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQFCR_RFA_POS,
					     MTL_Q_RQFCR_RFA_LEN, 2);
		/* De-activate flow control when more than 6k left in fअगरo */
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQFCR_RFD_POS,
					     MTL_Q_RQFCR_RFD_LEN, 4);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQFCR));
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_config_tx_threshold(काष्ठा xlgmac_pdata *pdata,
				      अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TTC_POS,
					     MTL_Q_TQOMR_TTC_LEN, val);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_rsf_mode(काष्ठा xlgmac_pdata *pdata,
				  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_RQOMR_RSF_POS,
					     MTL_Q_RQOMR_RSF_LEN, val);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_RQOMR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_tsf_mode(काष्ठा xlgmac_pdata *pdata,
				  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_TSF_POS,
					     MTL_Q_TQOMR_TSF_LEN, val);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_osp_mode(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_OSP_POS,
					     DMA_CH_TCR_OSP_LEN,
					pdata->tx_osp_mode);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_config_pblx8(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_CR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_CR_PBLX8_POS,
					     DMA_CH_CR_PBLX8_LEN,
					pdata->pblx8);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_CR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_get_tx_pbl_val(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(XLGMAC_DMA_REG(pdata->channel_head, DMA_CH_TCR));
	regval = XLGMAC_GET_REG_BITS(regval, DMA_CH_TCR_PBL_POS,
				     DMA_CH_TCR_PBL_LEN);
	वापस regval;
पूर्ण

अटल पूर्णांक xlgmac_config_tx_pbl_val(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_TCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_TCR_PBL_POS,
					     DMA_CH_TCR_PBL_LEN,
					pdata->tx_pbl);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_TCR));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_get_rx_pbl_val(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(XLGMAC_DMA_REG(pdata->channel_head, DMA_CH_RCR));
	regval = XLGMAC_GET_REG_BITS(regval, DMA_CH_RCR_PBL_POS,
				     DMA_CH_RCR_PBL_LEN);
	वापस regval;
पूर्ण

अटल पूर्णांक xlgmac_config_rx_pbl_val(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	u32 regval;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->rx_ring)
			अवरोध;

		regval = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_RCR));
		regval = XLGMAC_SET_REG_BITS(regval, DMA_CH_RCR_PBL_POS,
					     DMA_CH_RCR_PBL_LEN,
					pdata->rx_pbl);
		ग_लिखोl(regval, XLGMAC_DMA_REG(channel, DMA_CH_RCR));
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 xlgmac_mmc_पढ़ो(काष्ठा xlgmac_pdata *pdata, अचिन्हित पूर्णांक reg_lo)
अणु
	bool पढ़ो_hi;
	u64 val;

	चयन (reg_lo) अणु
	/* These रेजिस्टरs are always 64 bit */
	हाल MMC_TXOCTETCOUNT_GB_LO:
	हाल MMC_TXOCTETCOUNT_G_LO:
	हाल MMC_RXOCTETCOUNT_GB_LO:
	हाल MMC_RXOCTETCOUNT_G_LO:
		पढ़ो_hi = true;
		अवरोध;

	शेष:
		पढ़ो_hi = false;
	पूर्ण

	val = (u64)पढ़ोl(pdata->mac_regs + reg_lo);

	अगर (पढ़ो_hi)
		val |= ((u64)पढ़ोl(pdata->mac_regs + reg_lo + 4) << 32);

	वापस val;
पूर्ण

अटल व्योम xlgmac_tx_mmc_पूर्णांक(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक mmc_isr = पढ़ोl(pdata->mac_regs + MMC_TISR);
	काष्ठा xlgmac_stats *stats = &pdata->stats;

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXOCTETCOUNT_GB_POS,
				MMC_TISR_TXOCTETCOUNT_GB_LEN))
		stats->txoctetcount_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXFRAMECOUNT_GB_POS,
				MMC_TISR_TXFRAMECOUNT_GB_LEN))
		stats->txframecount_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXBROADCASTFRAMES_G_POS,
				MMC_TISR_TXBROADCASTFRAMES_G_LEN))
		stats->txbroadcastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXMULTICASTFRAMES_G_POS,
				MMC_TISR_TXMULTICASTFRAMES_G_LEN))
		stats->txmulticastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX64OCTETS_GB_POS,
				MMC_TISR_TX64OCTETS_GB_LEN))
		stats->tx64octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX64OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX65TO127OCTETS_GB_POS,
				MMC_TISR_TX65TO127OCTETS_GB_LEN))
		stats->tx65to127octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX65TO127OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX128TO255OCTETS_GB_POS,
				MMC_TISR_TX128TO255OCTETS_GB_LEN))
		stats->tx128to255octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX128TO255OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX256TO511OCTETS_GB_POS,
				MMC_TISR_TX256TO511OCTETS_GB_LEN))
		stats->tx256to511octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX256TO511OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX512TO1023OCTETS_GB_POS,
				MMC_TISR_TX512TO1023OCTETS_GB_LEN))
		stats->tx512to1023octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TX1024TOMAXOCTETS_GB_POS,
				MMC_TISR_TX1024TOMAXOCTETS_GB_LEN))
		stats->tx1024tomaxoctets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXUNICASTFRAMES_GB_POS,
				MMC_TISR_TXUNICASTFRAMES_GB_LEN))
		stats->txunicastframes_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXMULTICASTFRAMES_GB_POS,
				MMC_TISR_TXMULTICASTFRAMES_GB_LEN))
		stats->txmulticastframes_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXBROADCASTFRAMES_GB_POS,
				MMC_TISR_TXBROADCASTFRAMES_GB_LEN))
		stats->txbroadcastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXUNDERFLOWERROR_POS,
				MMC_TISR_TXUNDERFLOWERROR_LEN))
		stats->txunderflowerror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXUNDERFLOWERROR_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXOCTETCOUNT_G_POS,
				MMC_TISR_TXOCTETCOUNT_G_LEN))
		stats->txoctetcount_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXFRAMECOUNT_G_POS,
				MMC_TISR_TXFRAMECOUNT_G_LEN))
		stats->txframecount_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXPAUSEFRAMES_POS,
				MMC_TISR_TXPAUSEFRAMES_LEN))
		stats->txछोड़ोframes +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXPAUSEFRAMES_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_TISR_TXVLANFRAMES_G_POS,
				MMC_TISR_TXVLANFRAMES_G_LEN))
		stats->txvlanframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_TXVLANFRAMES_G_LO);
पूर्ण

अटल व्योम xlgmac_rx_mmc_पूर्णांक(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक mmc_isr = पढ़ोl(pdata->mac_regs + MMC_RISR);
	काष्ठा xlgmac_stats *stats = &pdata->stats;

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXFRAMECOUNT_GB_POS,
				MMC_RISR_RXFRAMECOUNT_GB_LEN))
		stats->rxframecount_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXFRAMECOUNT_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOCTETCOUNT_GB_POS,
				MMC_RISR_RXOCTETCOUNT_GB_LEN))
		stats->rxoctetcount_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOCTETCOUNT_G_POS,
				MMC_RISR_RXOCTETCOUNT_G_LEN))
		stats->rxoctetcount_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXBROADCASTFRAMES_G_POS,
				MMC_RISR_RXBROADCASTFRAMES_G_LEN))
		stats->rxbroadcastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXMULTICASTFRAMES_G_POS,
				MMC_RISR_RXMULTICASTFRAMES_G_LEN))
		stats->rxmulticastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXCRCERROR_POS,
				MMC_RISR_RXCRCERROR_LEN))
		stats->rxcrcerror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXCRCERROR_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXRUNTERROR_POS,
				MMC_RISR_RXRUNTERROR_LEN))
		stats->rxrunterror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXRUNTERROR);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXJABBERERROR_POS,
				MMC_RISR_RXJABBERERROR_LEN))
		stats->rxjabbererror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXJABBERERROR);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXUNDERSIZE_G_POS,
				MMC_RISR_RXUNDERSIZE_G_LEN))
		stats->rxundersize_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXUNDERSIZE_G);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOVERSIZE_G_POS,
				MMC_RISR_RXOVERSIZE_G_LEN))
		stats->rxoversize_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXOVERSIZE_G);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX64OCTETS_GB_POS,
				MMC_RISR_RX64OCTETS_GB_LEN))
		stats->rx64octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX64OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX65TO127OCTETS_GB_POS,
				MMC_RISR_RX65TO127OCTETS_GB_LEN))
		stats->rx65to127octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX65TO127OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX128TO255OCTETS_GB_POS,
				MMC_RISR_RX128TO255OCTETS_GB_LEN))
		stats->rx128to255octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX128TO255OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX256TO511OCTETS_GB_POS,
				MMC_RISR_RX256TO511OCTETS_GB_LEN))
		stats->rx256to511octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX256TO511OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX512TO1023OCTETS_GB_POS,
				MMC_RISR_RX512TO1023OCTETS_GB_LEN))
		stats->rx512to1023octets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RX1024TOMAXOCTETS_GB_POS,
				MMC_RISR_RX1024TOMAXOCTETS_GB_LEN))
		stats->rx1024tomaxoctets_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXUNICASTFRAMES_G_POS,
				MMC_RISR_RXUNICASTFRAMES_G_LEN))
		stats->rxunicastframes_g +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXUNICASTFRAMES_G_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXLENGTHERROR_POS,
				MMC_RISR_RXLENGTHERROR_LEN))
		stats->rxlengtherror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXLENGTHERROR_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXOUTOFRANGETYPE_POS,
				MMC_RISR_RXOUTOFRANGETYPE_LEN))
		stats->rxoutofrangetype +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXOUTOFRANGETYPE_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXPAUSEFRAMES_POS,
				MMC_RISR_RXPAUSEFRAMES_LEN))
		stats->rxछोड़ोframes +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXPAUSEFRAMES_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXFIFOOVERFLOW_POS,
				MMC_RISR_RXFIFOOVERFLOW_LEN))
		stats->rxfअगरooverflow +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXFIFOOVERFLOW_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXVLANFRAMES_GB_POS,
				MMC_RISR_RXVLANFRAMES_GB_LEN))
		stats->rxvlanframes_gb +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXVLANFRAMES_GB_LO);

	अगर (XLGMAC_GET_REG_BITS(mmc_isr,
				MMC_RISR_RXWATCHDOGERROR_POS,
				MMC_RISR_RXWATCHDOGERROR_LEN))
		stats->rxwatchकरोgerror +=
			xlgmac_mmc_पढ़ो(pdata, MMC_RXWATCHDOGERROR);
पूर्ण

अटल व्योम xlgmac_पढ़ो_mmc_stats(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_stats *stats = &pdata->stats;
	u32 regval;

	/* Freeze counters */
	regval = पढ़ोl(pdata->mac_regs + MMC_CR);
	regval = XLGMAC_SET_REG_BITS(regval, MMC_CR_MCF_POS,
				     MMC_CR_MCF_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MMC_CR);

	stats->txoctetcount_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_GB_LO);

	stats->txframecount_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_GB_LO);

	stats->txbroadcastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	stats->txmulticastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	stats->tx64octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX64OCTETS_GB_LO);

	stats->tx65to127octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX65TO127OCTETS_GB_LO);

	stats->tx128to255octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX128TO255OCTETS_GB_LO);

	stats->tx256to511octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX256TO511OCTETS_GB_LO);

	stats->tx512to1023octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	stats->tx1024tomaxoctets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	stats->txunicastframes_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	stats->txmulticastframes_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	stats->txbroadcastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	stats->txunderflowerror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXUNDERFLOWERROR_LO);

	stats->txoctetcount_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_G_LO);

	stats->txframecount_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_G_LO);

	stats->txछोड़ोframes +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXPAUSEFRAMES_LO);

	stats->txvlanframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_TXVLANFRAMES_G_LO);

	stats->rxframecount_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXFRAMECOUNT_GB_LO);

	stats->rxoctetcount_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_GB_LO);

	stats->rxoctetcount_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_G_LO);

	stats->rxbroadcastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	stats->rxmulticastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	stats->rxcrcerror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXCRCERROR_LO);

	stats->rxrunterror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXRUNTERROR);

	stats->rxjabbererror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXJABBERERROR);

	stats->rxundersize_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXUNDERSIZE_G);

	stats->rxoversize_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXOVERSIZE_G);

	stats->rx64octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX64OCTETS_GB_LO);

	stats->rx65to127octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX65TO127OCTETS_GB_LO);

	stats->rx128to255octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX128TO255OCTETS_GB_LO);

	stats->rx256to511octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX256TO511OCTETS_GB_LO);

	stats->rx512to1023octets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	stats->rx1024tomaxoctets_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	stats->rxunicastframes_g +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXUNICASTFRAMES_G_LO);

	stats->rxlengtherror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXLENGTHERROR_LO);

	stats->rxoutofrangetype +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXOUTOFRANGETYPE_LO);

	stats->rxछोड़ोframes +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXPAUSEFRAMES_LO);

	stats->rxfअगरooverflow +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXFIFOOVERFLOW_LO);

	stats->rxvlanframes_gb +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXVLANFRAMES_GB_LO);

	stats->rxwatchकरोgerror +=
		xlgmac_mmc_पढ़ो(pdata, MMC_RXWATCHDOGERROR);

	/* Un-मुक्तze counters */
	regval = पढ़ोl(pdata->mac_regs + MMC_CR);
	regval = XLGMAC_SET_REG_BITS(regval, MMC_CR_MCF_POS,
				     MMC_CR_MCF_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MMC_CR);
पूर्ण

अटल व्योम xlgmac_config_mmc(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + MMC_CR);
	/* Set counters to reset on पढ़ो */
	regval = XLGMAC_SET_REG_BITS(regval, MMC_CR_ROR_POS,
				     MMC_CR_ROR_LEN, 1);
	/* Reset the counters */
	regval = XLGMAC_SET_REG_BITS(regval, MMC_CR_CR_POS,
				     MMC_CR_CR_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MMC_CR);
पूर्ण

अटल पूर्णांक xlgmac_ग_लिखो_rss_reg(काष्ठा xlgmac_pdata *pdata, अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक रुको;
	पूर्णांक ret = 0;
	u32 regval;

	mutex_lock(&pdata->rss_mutex);

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_RSSAR),
				     MAC_RSSAR_OB_POS, MAC_RSSAR_OB_LEN);
	अगर (regval) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	ग_लिखोl(val, pdata->mac_regs + MAC_RSSDR);

	regval = पढ़ोl(pdata->mac_regs + MAC_RSSAR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_RSSIA_POS,
				     MAC_RSSAR_RSSIA_LEN, index);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_ADDRT_POS,
				     MAC_RSSAR_ADDRT_LEN, type);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_CT_POS,
				     MAC_RSSAR_CT_LEN, 0);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSAR_OB_POS,
				     MAC_RSSAR_OB_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RSSAR);

	रुको = 1000;
	जबतक (रुको--) अणु
		regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_RSSAR),
					     MAC_RSSAR_OB_POS,
					     MAC_RSSAR_OB_LEN);
		अगर (!regval)
			जाओ unlock;

		usleep_range(1000, 1500);
	पूर्ण

	ret = -EBUSY;

unlock:
	mutex_unlock(&pdata->rss_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक xlgmac_ग_लिखो_rss_hash_key(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक key_regs = माप(pdata->rss_key) / माप(u32);
	अचिन्हित पूर्णांक *key = (अचिन्हित पूर्णांक *)&pdata->rss_key;
	पूर्णांक ret;

	जबतक (key_regs--) अणु
		ret = xlgmac_ग_लिखो_rss_reg(pdata, XLGMAC_RSS_HASH_KEY_TYPE,
					   key_regs, *key++);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_ग_लिखो_rss_lookup_table(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++) अणु
		ret = xlgmac_ग_लिखो_rss_reg(pdata,
					   XLGMAC_RSS_LOOKUP_TABLE_TYPE, i,
					   pdata->rss_table[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_rss_hash_key(काष्ठा xlgmac_pdata *pdata, स्थिर u8 *key)
अणु
	स_नकल(pdata->rss_key, key, माप(pdata->rss_key));

	वापस xlgmac_ग_लिखो_rss_hash_key(pdata);
पूर्ण

अटल पूर्णांक xlgmac_set_rss_lookup_table(काष्ठा xlgmac_pdata *pdata,
				       स्थिर u32 *table)
अणु
	अचिन्हित पूर्णांक i;
	u32 tval;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++) अणु
		tval = table[i];
		pdata->rss_table[i] = XLGMAC_SET_REG_BITS(
						pdata->rss_table[i],
						MAC_RSSDR_DMCH_POS,
						MAC_RSSDR_DMCH_LEN,
						tval);
	पूर्ण

	वापस xlgmac_ग_लिखो_rss_lookup_table(pdata);
पूर्ण

अटल पूर्णांक xlgmac_enable_rss(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;
	पूर्णांक ret;

	अगर (!pdata->hw_feat.rss)
		वापस -EOPNOTSUPP;

	/* Program the hash key */
	ret = xlgmac_ग_लिखो_rss_hash_key(pdata);
	अगर (ret)
		वापस ret;

	/* Program the lookup table */
	ret = xlgmac_ग_लिखो_rss_lookup_table(pdata);
	अगर (ret)
		वापस ret;

	/* Set the RSS options */
	ग_लिखोl(pdata->rss_options, pdata->mac_regs + MAC_RSSCR);

	/* Enable RSS */
	regval = पढ़ोl(pdata->mac_regs + MAC_RSSCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSCR_RSSE_POS,
				     MAC_RSSCR_RSSE_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RSSCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_disable_rss(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	अगर (!pdata->hw_feat.rss)
		वापस -EOPNOTSUPP;

	regval = पढ़ोl(pdata->mac_regs + MAC_RSSCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_RSSCR_RSSE_POS,
				     MAC_RSSCR_RSSE_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_RSSCR);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_rss(काष्ठा xlgmac_pdata *pdata)
अणु
	पूर्णांक ret;

	अगर (!pdata->hw_feat.rss)
		वापस;

	अगर (pdata->netdev->features & NETIF_F_RXHASH)
		ret = xlgmac_enable_rss(pdata);
	अन्यथा
		ret = xlgmac_disable_rss(pdata);

	अगर (ret)
		netdev_err(pdata->netdev,
			   "error configuring RSS, RSS disabled\n");
पूर्ण

अटल व्योम xlgmac_enable_dma_पूर्णांकerrupts(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक dma_ch_isr, dma_ch_ier;
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		/* Clear all the पूर्णांकerrupts which are set */
		dma_ch_isr = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_SR));
		ग_लिखोl(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_SR));

		/* Clear all पूर्णांकerrupt enable bits */
		dma_ch_ier = 0;

		/* Enable following पूर्णांकerrupts
		 *   NIE  - Normal Interrupt Summary Enable
		 *   AIE  - Abnormal Interrupt Summary Enable
		 *   FBEE - Fatal Bus Error Enable
		 */
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_NIE_POS,
					DMA_CH_IER_NIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_AIE_POS,
					DMA_CH_IER_AIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(dma_ch_ier,
						 DMA_CH_IER_FBEE_POS,
					DMA_CH_IER_FBEE_LEN, 1);

		अगर (channel->tx_ring) अणु
			/* Enable the following Tx पूर्णांकerrupts
			 *   TIE  - Transmit Interrupt Enable (unless using
			 *          per channel पूर्णांकerrupts)
			 */
			अगर (!pdata->per_channel_irq)
				dma_ch_ier = XLGMAC_SET_REG_BITS(
						dma_ch_ier,
						DMA_CH_IER_TIE_POS,
						DMA_CH_IER_TIE_LEN,
						1);
		पूर्ण
		अगर (channel->rx_ring) अणु
			/* Enable following Rx पूर्णांकerrupts
			 *   RBUE - Receive Buffer Unavailable Enable
			 *   RIE  - Receive Interrupt Enable (unless using
			 *          per channel पूर्णांकerrupts)
			 */
			dma_ch_ier = XLGMAC_SET_REG_BITS(
					dma_ch_ier,
					DMA_CH_IER_RBUE_POS,
					DMA_CH_IER_RBUE_LEN,
					1);
			अगर (!pdata->per_channel_irq)
				dma_ch_ier = XLGMAC_SET_REG_BITS(
						dma_ch_ier,
						DMA_CH_IER_RIE_POS,
						DMA_CH_IER_RIE_LEN,
						1);
		पूर्ण

		ग_लिखोl(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_IER));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_enable_mtl_पूर्णांकerrupts(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक q_count, i;
	अचिन्हित पूर्णांक mtl_q_isr;

	q_count = max(pdata->hw_feat.tx_q_cnt, pdata->hw_feat.rx_q_cnt);
	क्रम (i = 0; i < q_count; i++) अणु
		/* Clear all the पूर्णांकerrupts which are set */
		mtl_q_isr = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_ISR));
		ग_लिखोl(mtl_q_isr, XLGMAC_MTL_REG(pdata, i, MTL_Q_ISR));

		/* No MTL पूर्णांकerrupts to be enabled */
		ग_लिखोl(0, XLGMAC_MTL_REG(pdata, i, MTL_Q_IER));
	पूर्ण
पूर्ण

अटल व्योम xlgmac_enable_mac_पूर्णांकerrupts(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक mac_ier = 0;
	u32 regval;

	/* Enable Timestamp पूर्णांकerrupt */
	mac_ier = XLGMAC_SET_REG_BITS(mac_ier, MAC_IER_TSIE_POS,
				      MAC_IER_TSIE_LEN, 1);

	ग_लिखोl(mac_ier, pdata->mac_regs + MAC_IER);

	/* Enable all counter पूर्णांकerrupts */
	regval = पढ़ोl(pdata->mac_regs + MMC_RIER);
	regval = XLGMAC_SET_REG_BITS(regval, MMC_RIER_ALL_INTERRUPTS_POS,
				     MMC_RIER_ALL_INTERRUPTS_LEN, 0xffffffff);
	ग_लिखोl(regval, pdata->mac_regs + MMC_RIER);
	regval = पढ़ोl(pdata->mac_regs + MMC_TIER);
	regval = XLGMAC_SET_REG_BITS(regval, MMC_TIER_ALL_INTERRUPTS_POS,
				     MMC_TIER_ALL_INTERRUPTS_LEN, 0xffffffff);
	ग_लिखोl(regval, pdata->mac_regs + MMC_TIER);
पूर्ण

अटल पूर्णांक xlgmac_set_xlgmii_25000_speed(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_TCR),
				     MAC_TCR_SS_POS, MAC_TCR_SS_LEN);
	अगर (regval == 0x1)
		वापस 0;

	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_SS_POS,
				     MAC_TCR_SS_LEN, 0x1);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_xlgmii_40000_speed(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_TCR),
				     MAC_TCR_SS_POS, MAC_TCR_SS_LEN);
	अगर (regval == 0)
		वापस 0;

	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_SS_POS,
				     MAC_TCR_SS_LEN, 0);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_xlgmii_50000_speed(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_TCR),
				     MAC_TCR_SS_POS, MAC_TCR_SS_LEN);
	अगर (regval == 0x2)
		वापस 0;

	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_SS_POS,
				     MAC_TCR_SS_LEN, 0x2);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_set_xlgmii_100000_speed(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + MAC_TCR),
				     MAC_TCR_SS_POS, MAC_TCR_SS_LEN);
	अगर (regval == 0x3)
		वापस 0;

	regval = पढ़ोl(pdata->mac_regs + MAC_TCR);
	regval = XLGMAC_SET_REG_BITS(regval, MAC_TCR_SS_POS,
				     MAC_TCR_SS_LEN, 0x3);
	ग_लिखोl(regval, pdata->mac_regs + MAC_TCR);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_mac_speed(काष्ठा xlgmac_pdata *pdata)
अणु
	चयन (pdata->phy_speed) अणु
	हाल SPEED_100000:
		xlgmac_set_xlgmii_100000_speed(pdata);
		अवरोध;

	हाल SPEED_50000:
		xlgmac_set_xlgmii_50000_speed(pdata);
		अवरोध;

	हाल SPEED_40000:
		xlgmac_set_xlgmii_40000_speed(pdata);
		अवरोध;

	हाल SPEED_25000:
		xlgmac_set_xlgmii_25000_speed(pdata);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_dev_पढ़ो(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->rx_ring;
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;
	काष्ठा xlgmac_pkt_info *pkt_info;
	अचिन्हित पूर्णांक err, etlt, l34t;

	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	dma_desc = desc_data->dma_desc;
	pkt_info = &ring->pkt_info;

	/* Check क्रम data availability */
	अगर (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_OWN_POS,
				   RX_NORMAL_DESC3_OWN_LEN))
		वापस 1;

	/* Make sure descriptor fields are पढ़ो after पढ़ोing the OWN bit */
	dma_rmb();

	अगर (netअगर_msg_rx_status(pdata))
		xlgmac_dump_rx_desc(pdata, ring, ring->cur);

	अगर (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_CTXT_POS,
				   RX_NORMAL_DESC3_CTXT_LEN)) अणु
		/* Timestamp Context Descriptor */
		xlgmac_get_rx_tstamp(pkt_info, dma_desc);

		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_LEN,
					1);
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN,
				0);
		वापस 0;
	पूर्ण

	/* Normal Descriptor, be sure Context Descriptor bit is off */
	pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_LEN,
				0);

	/* Indicate अगर a Context Descriptor is next */
	अगर (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_CDA_POS,
				   RX_NORMAL_DESC3_CDA_LEN))
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN,
				1);

	/* Get the header length */
	अगर (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_FD_POS,
				   RX_NORMAL_DESC3_FD_LEN)) अणु
		desc_data->rx.hdr_len = XLGMAC_GET_REG_BITS_LE(dma_desc->desc2,
							RX_NORMAL_DESC2_HL_POS,
							RX_NORMAL_DESC2_HL_LEN);
		अगर (desc_data->rx.hdr_len)
			pdata->stats.rx_split_header_packets++;
	पूर्ण

	/* Get the RSS hash */
	अगर (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_RSV_POS,
				   RX_NORMAL_DESC3_RSV_LEN)) अणु
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_RSS_HASH_POS,
				RX_PACKET_ATTRIBUTES_RSS_HASH_LEN,
				1);

		pkt_info->rss_hash = le32_to_cpu(dma_desc->desc1);

		l34t = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
					      RX_NORMAL_DESC3_L34T_POS,
					  RX_NORMAL_DESC3_L34T_LEN);
		चयन (l34t) अणु
		हाल RX_DESC3_L34T_IPV4_TCP:
		हाल RX_DESC3_L34T_IPV4_UDP:
		हाल RX_DESC3_L34T_IPV6_TCP:
		हाल RX_DESC3_L34T_IPV6_UDP:
			pkt_info->rss_hash_type = PKT_HASH_TYPE_L4;
			अवरोध;
		शेष:
			pkt_info->rss_hash_type = PKT_HASH_TYPE_L3;
		पूर्ण
	पूर्ण

	/* Get the pkt_info length */
	desc_data->rx.len = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
					RX_NORMAL_DESC3_PL_POS,
					RX_NORMAL_DESC3_PL_LEN);

	अगर (!XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				    RX_NORMAL_DESC3_LD_POS,
				    RX_NORMAL_DESC3_LD_LEN)) अणु
		/* Not all the data has been transferred क्रम this pkt_info */
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
				RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN,
				1);
		वापस 0;
	पूर्ण

	/* This is the last of the data क्रम this pkt_info */
	pkt_info->attributes = XLGMAC_SET_REG_BITS(
			pkt_info->attributes,
			RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
			RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN,
			0);

	/* Set checksum करोne indicator as appropriate */
	अगर (netdev->features & NETIF_F_RXCSUM)
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
				RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN,
				1);

	/* Check क्रम errors (only valid in last descriptor) */
	err = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_NORMAL_DESC3_ES_POS,
				     RX_NORMAL_DESC3_ES_LEN);
	etlt = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				      RX_NORMAL_DESC3_ETLT_POS,
				      RX_NORMAL_DESC3_ETLT_LEN);
	netअगर_dbg(pdata, rx_status, netdev, "err=%u, etlt=%#x\n", err, etlt);

	अगर (!err || !etlt) अणु
		/* No error अगर err is 0 or etlt is 0 */
		अगर ((etlt == 0x09) &&
		    (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)) अणु
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN,
					1);
			pkt_info->vlan_ctag =
				XLGMAC_GET_REG_BITS_LE(dma_desc->desc0,
						       RX_NORMAL_DESC0_OVT_POS,
						   RX_NORMAL_DESC0_OVT_LEN);
			netअगर_dbg(pdata, rx_status, netdev, "vlan-ctag=%#06x\n",
				  pkt_info->vlan_ctag);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((etlt == 0x05) || (etlt == 0x06))
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN,
					0);
		अन्यथा
			pkt_info->errors = XLGMAC_SET_REG_BITS(
					pkt_info->errors,
					RX_PACKET_ERRORS_FRAME_POS,
					RX_PACKET_ERRORS_FRAME_LEN,
					1);
	पूर्ण

	XLGMAC_PR("%s - descriptor=%u (cur=%d)\n", channel->name,
		  ring->cur & (ring->dma_desc_count - 1), ring->cur);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_enable_पूर्णांक(काष्ठा xlgmac_channel *channel,
			     क्रमागत xlgmac_पूर्णांक पूर्णांक_id)
अणु
	अचिन्हित पूर्णांक dma_ch_ier;

	dma_ch_ier = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_IER));

	चयन (पूर्णांक_id) अणु
	हाल XLGMAC_INT_DMA_CH_SR_TI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TXSE_POS,
				DMA_CH_IER_TXSE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TBUE_POS,
				DMA_CH_IER_TBUE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RBUE_POS,
				DMA_CH_IER_RBUE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RSE_POS,
				DMA_CH_IER_RSE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TI_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 1);
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_FBE:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_FBEE_POS,
				DMA_CH_IER_FBEE_LEN, 1);
		अवरोध;
	हाल XLGMAC_INT_DMA_ALL:
		dma_ch_ier |= channel->saved_ier;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	ग_लिखोl(dma_ch_ier, XLGMAC_DMA_REG(channel, DMA_CH_IER));

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_disable_पूर्णांक(काष्ठा xlgmac_channel *channel,
			      क्रमागत xlgmac_पूर्णांक पूर्णांक_id)
अणु
	अचिन्हित पूर्णांक dma_ch_ier;

	dma_ch_ier = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_IER));

	चयन (पूर्णांक_id) अणु
	हाल XLGMAC_INT_DMA_CH_SR_TI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TXSE_POS,
				DMA_CH_IER_TXSE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TBUE_POS,
				DMA_CH_IER_TBUE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RBU:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RBUE_POS,
				DMA_CH_IER_RBUE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_RPS:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RSE_POS,
				DMA_CH_IER_RSE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_TI_RI:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_TIE_POS,
				DMA_CH_IER_TIE_LEN, 0);
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_RIE_POS,
				DMA_CH_IER_RIE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_CH_SR_FBE:
		dma_ch_ier = XLGMAC_SET_REG_BITS(
				dma_ch_ier, DMA_CH_IER_FBEE_POS,
				DMA_CH_IER_FBEE_LEN, 0);
		अवरोध;
	हाल XLGMAC_INT_DMA_ALL:
		channel->saved_ier = dma_ch_ier & XLGMAC_DMA_INTERRUPT_MASK;
		dma_ch_ier &= ~XLGMAC_DMA_INTERRUPT_MASK;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	ग_लिखोl(dma_ch_ier, XLGMAC_DMA_REG(channel, DMA_CH_IER));

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_flush_tx_queues(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक i, count;
	u32 regval;

	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_SET_REG_BITS(regval, MTL_Q_TQOMR_FTQ_POS,
					     MTL_Q_TQOMR_FTQ_LEN, 1);
		ग_लिखोl(regval, XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
	पूर्ण

	/* Poll Until Poll Condition */
	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		count = 2000;
		regval = पढ़ोl(XLGMAC_MTL_REG(pdata, i, MTL_Q_TQOMR));
		regval = XLGMAC_GET_REG_BITS(regval, MTL_Q_TQOMR_FTQ_POS,
					     MTL_Q_TQOMR_FTQ_LEN);
		जबतक (--count && regval)
			usleep_range(500, 600);

		अगर (!count)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xlgmac_config_dma_bus(काष्ठा xlgmac_pdata *pdata)
अणु
	u32 regval;

	regval = पढ़ोl(pdata->mac_regs + DMA_SBMR);
	/* Set enhanced addressing mode */
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_EAME_POS,
				     DMA_SBMR_EAME_LEN, 1);
	/* Set the System Bus mode */
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_UNDEF_POS,
				     DMA_SBMR_UNDEF_LEN, 1);
	regval = XLGMAC_SET_REG_BITS(regval, DMA_SBMR_BLEN_256_POS,
				     DMA_SBMR_BLEN_256_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + DMA_SBMR);
पूर्ण

अटल पूर्णांक xlgmac_hw_init(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_desc_ops *desc_ops = &pdata->desc_ops;
	पूर्णांक ret;

	/* Flush Tx queues */
	ret = xlgmac_flush_tx_queues(pdata);
	अगर (ret)
		वापस ret;

	/* Initialize DMA related features */
	xlgmac_config_dma_bus(pdata);
	xlgmac_config_osp_mode(pdata);
	xlgmac_config_pblx8(pdata);
	xlgmac_config_tx_pbl_val(pdata);
	xlgmac_config_rx_pbl_val(pdata);
	xlgmac_config_rx_coalesce(pdata);
	xlgmac_config_tx_coalesce(pdata);
	xlgmac_config_rx_buffer_size(pdata);
	xlgmac_config_tso_mode(pdata);
	xlgmac_config_sph_mode(pdata);
	xlgmac_config_rss(pdata);
	desc_ops->tx_desc_init(pdata);
	desc_ops->rx_desc_init(pdata);
	xlgmac_enable_dma_पूर्णांकerrupts(pdata);

	/* Initialize MTL related features */
	xlgmac_config_mtl_mode(pdata);
	xlgmac_config_queue_mapping(pdata);
	xlgmac_config_tsf_mode(pdata, pdata->tx_sf_mode);
	xlgmac_config_rsf_mode(pdata, pdata->rx_sf_mode);
	xlgmac_config_tx_threshold(pdata, pdata->tx_threshold);
	xlgmac_config_rx_threshold(pdata, pdata->rx_threshold);
	xlgmac_config_tx_fअगरo_size(pdata);
	xlgmac_config_rx_fअगरo_size(pdata);
	xlgmac_config_flow_control_threshold(pdata);
	xlgmac_config_rx_fep_enable(pdata);
	xlgmac_config_rx_fup_enable(pdata);
	xlgmac_enable_mtl_पूर्णांकerrupts(pdata);

	/* Initialize MAC related features */
	xlgmac_config_mac_address(pdata);
	xlgmac_config_rx_mode(pdata);
	xlgmac_config_jumbo_enable(pdata);
	xlgmac_config_flow_control(pdata);
	xlgmac_config_mac_speed(pdata);
	xlgmac_config_checksum_offload(pdata);
	xlgmac_config_vlan_support(pdata);
	xlgmac_config_mmc(pdata);
	xlgmac_enable_mac_पूर्णांकerrupts(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_hw_निकास(काष्ठा xlgmac_pdata *pdata)
अणु
	अचिन्हित पूर्णांक count = 2000;
	u32 regval;

	/* Issue a software reset */
	regval = पढ़ोl(pdata->mac_regs + DMA_MR);
	regval = XLGMAC_SET_REG_BITS(regval, DMA_MR_SWR_POS,
				     DMA_MR_SWR_LEN, 1);
	ग_लिखोl(regval, pdata->mac_regs + DMA_MR);
	usleep_range(10, 15);

	/* Poll Until Poll Condition */
	जबतक (--count &&
	       XLGMAC_GET_REG_BITS(पढ़ोl(pdata->mac_regs + DMA_MR),
				   DMA_MR_SWR_POS, DMA_MR_SWR_LEN))
		usleep_range(500, 600);

	अगर (!count)
		वापस -EBUSY;

	वापस 0;
पूर्ण

व्योम xlgmac_init_hw_ops(काष्ठा xlgmac_hw_ops *hw_ops)
अणु
	hw_ops->init = xlgmac_hw_init;
	hw_ops->निकास = xlgmac_hw_निकास;

	hw_ops->tx_complete = xlgmac_tx_complete;

	hw_ops->enable_tx = xlgmac_enable_tx;
	hw_ops->disable_tx = xlgmac_disable_tx;
	hw_ops->enable_rx = xlgmac_enable_rx;
	hw_ops->disable_rx = xlgmac_disable_rx;

	hw_ops->dev_xmit = xlgmac_dev_xmit;
	hw_ops->dev_पढ़ो = xlgmac_dev_पढ़ो;
	hw_ops->enable_पूर्णांक = xlgmac_enable_पूर्णांक;
	hw_ops->disable_पूर्णांक = xlgmac_disable_पूर्णांक;

	hw_ops->set_mac_address = xlgmac_set_mac_address;
	hw_ops->config_rx_mode = xlgmac_config_rx_mode;
	hw_ops->enable_rx_csum = xlgmac_enable_rx_csum;
	hw_ops->disable_rx_csum = xlgmac_disable_rx_csum;

	/* For MII speed configuration */
	hw_ops->set_xlgmii_25000_speed = xlgmac_set_xlgmii_25000_speed;
	hw_ops->set_xlgmii_40000_speed = xlgmac_set_xlgmii_40000_speed;
	hw_ops->set_xlgmii_50000_speed = xlgmac_set_xlgmii_50000_speed;
	hw_ops->set_xlgmii_100000_speed = xlgmac_set_xlgmii_100000_speed;

	/* For descriptor related operation */
	hw_ops->tx_desc_init = xlgmac_tx_desc_init;
	hw_ops->rx_desc_init = xlgmac_rx_desc_init;
	hw_ops->tx_desc_reset = xlgmac_tx_desc_reset;
	hw_ops->rx_desc_reset = xlgmac_rx_desc_reset;
	hw_ops->is_last_desc = xlgmac_is_last_desc;
	hw_ops->is_context_desc = xlgmac_is_context_desc;
	hw_ops->tx_start_xmit = xlgmac_tx_start_xmit;

	/* For Flow Control */
	hw_ops->config_tx_flow_control = xlgmac_config_tx_flow_control;
	hw_ops->config_rx_flow_control = xlgmac_config_rx_flow_control;

	/* For Vlan related config */
	hw_ops->enable_rx_vlan_stripping = xlgmac_enable_rx_vlan_stripping;
	hw_ops->disable_rx_vlan_stripping = xlgmac_disable_rx_vlan_stripping;
	hw_ops->enable_rx_vlan_filtering = xlgmac_enable_rx_vlan_filtering;
	hw_ops->disable_rx_vlan_filtering = xlgmac_disable_rx_vlan_filtering;
	hw_ops->update_vlan_hash_table = xlgmac_update_vlan_hash_table;

	/* For RX coalescing */
	hw_ops->config_rx_coalesce = xlgmac_config_rx_coalesce;
	hw_ops->config_tx_coalesce = xlgmac_config_tx_coalesce;
	hw_ops->usec_to_riwt = xlgmac_usec_to_riwt;
	hw_ops->riwt_to_usec = xlgmac_riwt_to_usec;

	/* For RX and TX threshold config */
	hw_ops->config_rx_threshold = xlgmac_config_rx_threshold;
	hw_ops->config_tx_threshold = xlgmac_config_tx_threshold;

	/* For RX and TX Store and Forward Mode config */
	hw_ops->config_rsf_mode = xlgmac_config_rsf_mode;
	hw_ops->config_tsf_mode = xlgmac_config_tsf_mode;

	/* For TX DMA Operating on Second Frame config */
	hw_ops->config_osp_mode = xlgmac_config_osp_mode;

	/* For RX and TX PBL config */
	hw_ops->config_rx_pbl_val = xlgmac_config_rx_pbl_val;
	hw_ops->get_rx_pbl_val = xlgmac_get_rx_pbl_val;
	hw_ops->config_tx_pbl_val = xlgmac_config_tx_pbl_val;
	hw_ops->get_tx_pbl_val = xlgmac_get_tx_pbl_val;
	hw_ops->config_pblx8 = xlgmac_config_pblx8;

	/* For MMC statistics support */
	hw_ops->tx_mmc_पूर्णांक = xlgmac_tx_mmc_पूर्णांक;
	hw_ops->rx_mmc_पूर्णांक = xlgmac_rx_mmc_पूर्णांक;
	hw_ops->पढ़ो_mmc_stats = xlgmac_पढ़ो_mmc_stats;

	/* For Receive Side Scaling */
	hw_ops->enable_rss = xlgmac_enable_rss;
	hw_ops->disable_rss = xlgmac_disable_rss;
	hw_ops->set_rss_hash_key = xlgmac_set_rss_hash_key;
	hw_ops->set_rss_lookup_table = xlgmac_set_rss_lookup_table;
पूर्ण
