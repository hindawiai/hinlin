<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2015 EZchip Technologies.
 */

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश "nps_enet.h"

#घोषणा DRV_NAME			"nps_mgt_enet"

अटल अंतरभूत bool nps_enet_is_tx_pending(काष्ठा nps_enet_priv *priv)
अणु
	u32 tx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_TX_CTL);
	u32 tx_ctrl_ct = (tx_ctrl_value & TX_CTL_CT_MASK) >> TX_CTL_CT_SHIFT;

	वापस (!tx_ctrl_ct && priv->tx_skb);
पूर्ण

अटल व्योम nps_enet_clean_rx_fअगरo(काष्ठा net_device *ndev, u32 frame_len)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 i, len = DIV_ROUND_UP(frame_len, माप(u32));

	/* Empty Rx FIFO buffer by पढ़ोing all words */
	क्रम (i = 0; i < len; i++)
		nps_enet_reg_get(priv, NPS_ENET_REG_RX_BUF);
पूर्ण

अटल व्योम nps_enet_पढ़ो_rx_fअगरo(काष्ठा net_device *ndev,
				  अचिन्हित अक्षर *dst, u32 length)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	s32 i, last = length & (माप(u32) - 1);
	u32 *reg = (u32 *)dst, len = length / माप(u32);
	bool dst_is_aligned = IS_ALIGNED((अचिन्हित दीर्घ)dst, माप(u32));

	/* In हाल dst is not aligned we need an पूर्णांकermediate buffer */
	अगर (dst_is_aligned) अणु
		ioपढ़ो32_rep(priv->regs_base + NPS_ENET_REG_RX_BUF, reg, len);
		reg += len;
	पूर्ण अन्यथा अणु /* !dst_is_aligned */
		क्रम (i = 0; i < len; i++, reg++) अणु
			u32 buf = nps_enet_reg_get(priv, NPS_ENET_REG_RX_BUF);

			put_unaligned_be32(buf, reg);
		पूर्ण
	पूर्ण
	/* copy last bytes (अगर any) */
	अगर (last) अणु
		u32 buf;

		ioपढ़ो32_rep(priv->regs_base + NPS_ENET_REG_RX_BUF, &buf, 1);
		स_नकल((u8 *)reg, &buf, last);
	पूर्ण
पूर्ण

अटल u32 nps_enet_rx_handler(काष्ठा net_device *ndev)
अणु
	u32 frame_len, err = 0;
	u32 work_करोne = 0;
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	काष्ठा sk_buff *skb;
	u32 rx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_RX_CTL);
	u32 rx_ctrl_cr = (rx_ctrl_value & RX_CTL_CR_MASK) >> RX_CTL_CR_SHIFT;
	u32 rx_ctrl_er = (rx_ctrl_value & RX_CTL_ER_MASK) >> RX_CTL_ER_SHIFT;
	u32 rx_ctrl_crc = (rx_ctrl_value & RX_CTL_CRC_MASK) >> RX_CTL_CRC_SHIFT;

	frame_len = (rx_ctrl_value & RX_CTL_NR_MASK) >> RX_CTL_NR_SHIFT;

	/* Check अगर we got RX */
	अगर (!rx_ctrl_cr)
		वापस work_करोne;

	/* If we got here there is a work क्रम us */
	work_करोne++;

	/* Check Rx error */
	अगर (rx_ctrl_er) अणु
		ndev->stats.rx_errors++;
		err = 1;
	पूर्ण

	/* Check Rx CRC error */
	अगर (rx_ctrl_crc) अणु
		ndev->stats.rx_crc_errors++;
		ndev->stats.rx_dropped++;
		err = 1;
	पूर्ण

	/* Check Frame length Min 64b */
	अगर (unlikely(frame_len < ETH_ZLEN)) अणु
		ndev->stats.rx_length_errors++;
		ndev->stats.rx_dropped++;
		err = 1;
	पूर्ण

	अगर (err)
		जाओ rx_irq_clean;

	/* Skb allocation */
	skb = netdev_alloc_skb_ip_align(ndev, frame_len);
	अगर (unlikely(!skb)) अणु
		ndev->stats.rx_errors++;
		ndev->stats.rx_dropped++;
		जाओ rx_irq_clean;
	पूर्ण

	/* Copy frame from Rx fअगरo पूर्णांकo the skb */
	nps_enet_पढ़ो_rx_fअगरo(ndev, skb->data, frame_len);

	skb_put(skb, frame_len);
	skb->protocol = eth_type_trans(skb, ndev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	ndev->stats.rx_packets++;
	ndev->stats.rx_bytes += frame_len;
	netअगर_receive_skb(skb);

	जाओ rx_irq_frame_करोne;

rx_irq_clean:
	/* Clean Rx fअगरo */
	nps_enet_clean_rx_fअगरo(ndev, frame_len);

rx_irq_frame_करोne:
	/* Ack Rx ctrl रेजिस्टर */
	nps_enet_reg_set(priv, NPS_ENET_REG_RX_CTL, 0);

	वापस work_करोne;
पूर्ण

अटल व्योम nps_enet_tx_handler(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 tx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_TX_CTL);
	u32 tx_ctrl_et = (tx_ctrl_value & TX_CTL_ET_MASK) >> TX_CTL_ET_SHIFT;
	u32 tx_ctrl_nt = (tx_ctrl_value & TX_CTL_NT_MASK) >> TX_CTL_NT_SHIFT;

	/* Check अगर we got TX */
	अगर (!nps_enet_is_tx_pending(priv))
		वापस;

	/* Ack Tx ctrl रेजिस्टर */
	nps_enet_reg_set(priv, NPS_ENET_REG_TX_CTL, 0);

	/* Check Tx transmit error */
	अगर (unlikely(tx_ctrl_et)) अणु
		ndev->stats.tx_errors++;
	पूर्ण अन्यथा अणु
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += tx_ctrl_nt;
	पूर्ण

	dev_kमुक्त_skb(priv->tx_skb);
	priv->tx_skb = शून्य;

	अगर (netअगर_queue_stopped(ndev))
		netअगर_wake_queue(ndev);
पूर्ण

/**
 * nps_enet_poll - NAPI poll handler.
 * @napi:       Poपूर्णांकer to napi_काष्ठा काष्ठाure.
 * @budget:     How many frames to process on one call.
 *
 * वापसs:     Number of processed frames
 */
अटल पूर्णांक nps_enet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 work_करोne;

	nps_enet_tx_handler(ndev);
	work_करोne = nps_enet_rx_handler(ndev);
	अगर ((work_करोne < budget) && napi_complete_करोne(napi, work_करोne)) अणु
		u32 buf_पूर्णांक_enable_value = 0;

		/* set tx_करोne and rx_rdy bits */
		buf_पूर्णांक_enable_value |= NPS_ENET_ENABLE << RX_RDY_SHIFT;
		buf_पूर्णांक_enable_value |= NPS_ENET_ENABLE << TX_DONE_SHIFT;

		nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE,
				 buf_पूर्णांक_enable_value);

		/* in हाल we will get a tx पूर्णांकerrupt जबतक पूर्णांकerrupts
		 * are masked, we will lose it since the tx is edge पूर्णांकerrupt.
		 * specअगरically, जबतक executing the code section above,
		 * between nps_enet_tx_handler and the पूर्णांकerrupts enable, all
		 * tx requests will be stuck until we will get an rx पूर्णांकerrupt.
		 * the two code lines below will solve this situation by
		 * re-adding ourselves to the poll list.
		 */
		अगर (nps_enet_is_tx_pending(priv)) अणु
			nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);
			napi_reschedule(napi);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

/**
 * nps_enet_irq_handler - Global पूर्णांकerrupt handler क्रम ENET.
 * @irq:                irq number.
 * @dev_instance:       device instance.
 *
 * वापसs: IRQ_HANDLED क्रम all हालs.
 *
 * EZchip ENET has 2 पूर्णांकerrupt causes, and depending on bits उठाओd in
 * CTRL रेजिस्टरs we may tell what is a reason क्रम पूर्णांकerrupt to fire up.
 * We got one क्रम RX and the other क्रम TX (completion).
 */
अटल irqवापस_t nps_enet_irq_handler(s32 irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *ndev = dev_instance;
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 rx_ctrl_value = nps_enet_reg_get(priv, NPS_ENET_REG_RX_CTL);
	u32 rx_ctrl_cr = (rx_ctrl_value & RX_CTL_CR_MASK) >> RX_CTL_CR_SHIFT;

	अगर (nps_enet_is_tx_pending(priv) || rx_ctrl_cr)
		अगर (likely(napi_schedule_prep(&priv->napi))) अणु
			nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);
			__napi_schedule(&priv->napi);
		पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nps_enet_set_hw_mac_address(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 ge_mac_cfg_1_value = 0;
	u32 *ge_mac_cfg_2_value = &priv->ge_mac_cfg_2_value;

	/* set MAC address in HW */
	ge_mac_cfg_1_value |= ndev->dev_addr[0] << CFG_1_OCTET_0_SHIFT;
	ge_mac_cfg_1_value |= ndev->dev_addr[1] << CFG_1_OCTET_1_SHIFT;
	ge_mac_cfg_1_value |= ndev->dev_addr[2] << CFG_1_OCTET_2_SHIFT;
	ge_mac_cfg_1_value |= ndev->dev_addr[3] << CFG_1_OCTET_3_SHIFT;
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_OCTET_4_MASK)
		 | ndev->dev_addr[4] << CFG_2_OCTET_4_SHIFT;
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_OCTET_5_MASK)
		 | ndev->dev_addr[5] << CFG_2_OCTET_5_SHIFT;

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_1,
			 ge_mac_cfg_1_value);

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_2,
			 *ge_mac_cfg_2_value);
पूर्ण

/**
 * nps_enet_hw_reset - Reset the network device.
 * @ndev:       Poपूर्णांकer to the network device.
 *
 * This function reset the PCS and TX fअगरo.
 * The programming model is to set the relevant reset bits
 * रुको क्रम some समय क्रम this to propagate and then unset
 * the reset bits. This way we ensure that reset procedure
 * is करोne successfully by device.
 */
अटल व्योम nps_enet_hw_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 ge_rst_value = 0, phase_fअगरo_ctl_value = 0;

	/* Pcs reset sequence*/
	ge_rst_value |= NPS_ENET_ENABLE << RST_GMAC_0_SHIFT;
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_RST, ge_rst_value);
	usleep_range(10, 20);
	ge_rst_value = 0;
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_RST, ge_rst_value);

	/* Tx fअगरo reset sequence */
	phase_fअगरo_ctl_value |= NPS_ENET_ENABLE << PHASE_FIFO_CTL_RST_SHIFT;
	phase_fअगरo_ctl_value |= NPS_ENET_ENABLE << PHASE_FIFO_CTL_INIT_SHIFT;
	nps_enet_reg_set(priv, NPS_ENET_REG_PHASE_FIFO_CTL,
			 phase_fअगरo_ctl_value);
	usleep_range(10, 20);
	phase_fअगरo_ctl_value = 0;
	nps_enet_reg_set(priv, NPS_ENET_REG_PHASE_FIFO_CTL,
			 phase_fअगरo_ctl_value);
पूर्ण

अटल व्योम nps_enet_hw_enable_control(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 ge_mac_cfg_0_value = 0, buf_पूर्णांक_enable_value = 0;
	u32 *ge_mac_cfg_2_value = &priv->ge_mac_cfg_2_value;
	u32 *ge_mac_cfg_3_value = &priv->ge_mac_cfg_3_value;
	s32 max_frame_length;

	/* Enable Rx and Tx statistics */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_STAT_EN_MASK)
		 | NPS_ENET_GE_MAC_CFG_2_STAT_EN << CFG_2_STAT_EN_SHIFT;

	/* Discard packets with dअगरferent MAC address */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_DISK_DA_MASK)
		 | NPS_ENET_ENABLE << CFG_2_DISK_DA_SHIFT;

	/* Discard multicast packets */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_DISK_MC_MASK)
		 | NPS_ENET_ENABLE << CFG_2_DISK_MC_SHIFT;

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_2,
			 *ge_mac_cfg_2_value);

	/* Discard Packets bigger than max frame length */
	max_frame_length = ETH_HLEN + ndev->mtu + ETH_FCS_LEN;
	अगर (max_frame_length <= NPS_ENET_MAX_FRAME_LENGTH) अणु
		*ge_mac_cfg_3_value =
			 (*ge_mac_cfg_3_value & ~CFG_3_MAX_LEN_MASK)
			 | max_frame_length << CFG_3_MAX_LEN_SHIFT;
	पूर्ण

	/* Enable पूर्णांकerrupts */
	buf_पूर्णांक_enable_value |= NPS_ENET_ENABLE << RX_RDY_SHIFT;
	buf_पूर्णांक_enable_value |= NPS_ENET_ENABLE << TX_DONE_SHIFT;
	nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE,
			 buf_पूर्णांक_enable_value);

	/* Write device MAC address to HW */
	nps_enet_set_hw_mac_address(ndev);

	/* Rx and Tx HW features */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_PAD_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_CRC_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_CRC_STRIP_SHIFT;

	/* IFG configuration */
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_RX_IFG << CFG_0_RX_IFG_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_IFG << CFG_0_TX_IFG_SHIFT;

	/* preamble configuration */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_PR_CHECK_EN_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_PR_LEN << CFG_0_TX_PR_LEN_SHIFT;

	/* enable flow control frames */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_FC_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_FC_EN_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_FC_RETR << CFG_0_TX_FC_RETR_SHIFT;
	*ge_mac_cfg_3_value = (*ge_mac_cfg_3_value & ~CFG_3_CF_DROP_MASK)
		 | NPS_ENET_ENABLE << CFG_3_CF_DROP_SHIFT;

	/* Enable Rx and Tx */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_EN_SHIFT;

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_3,
			 *ge_mac_cfg_3_value);
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_0,
			 ge_mac_cfg_0_value);
पूर्ण

अटल व्योम nps_enet_hw_disable_control(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);

	/* Disable पूर्णांकerrupts */
	nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE, 0);

	/* Disable Rx and Tx */
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_0, 0);
पूर्ण

अटल व्योम nps_enet_send_frame(काष्ठा net_device *ndev,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 tx_ctrl_value = 0;
	लघु length = skb->len;
	u32 i, len = DIV_ROUND_UP(length, माप(u32));
	u32 *src = (व्योम *)skb->data;
	bool src_is_aligned = IS_ALIGNED((अचिन्हित दीर्घ)src, माप(u32));

	/* In हाल src is not aligned we need an पूर्णांकermediate buffer */
	अगर (src_is_aligned)
		ioग_लिखो32_rep(priv->regs_base + NPS_ENET_REG_TX_BUF, src, len);
	अन्यथा /* !src_is_aligned */
		क्रम (i = 0; i < len; i++, src++)
			nps_enet_reg_set(priv, NPS_ENET_REG_TX_BUF,
					 get_unaligned_be32(src));

	/* Write the length of the Frame */
	tx_ctrl_value |= length << TX_CTL_NT_SHIFT;

	tx_ctrl_value |= NPS_ENET_ENABLE << TX_CTL_CT_SHIFT;
	/* Send Frame */
	nps_enet_reg_set(priv, NPS_ENET_REG_TX_CTL, tx_ctrl_value);
पूर्ण

/**
 * nps_enet_set_mac_address - Set the MAC address क्रम this device.
 * @ndev:       Poपूर्णांकer to net_device काष्ठाure.
 * @p:          6 byte Address to be written as MAC address.
 *
 * This function copies the HW address from the sockaddr काष्ठाure to the
 * net_device काष्ठाure and updates the address in HW.
 *
 * वापसs:     -EBUSY अगर the net device is busy or 0 अगर the address is set
 *              successfully.
 */
अटल s32 nps_enet_set_mac_address(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	s32 res;

	अगर (netअगर_running(ndev))
		वापस -EBUSY;

	res = eth_mac_addr(ndev, p);
	अगर (!res) अणु
		ether_addr_copy(ndev->dev_addr, addr->sa_data);
		nps_enet_set_hw_mac_address(ndev);
	पूर्ण

	वापस res;
पूर्ण

/**
 * nps_enet_set_rx_mode - Change the receive filtering mode.
 * @ndev:       Poपूर्णांकer to the network device.
 *
 * This function enables/disables promiscuous mode
 */
अटल व्योम nps_enet_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	u32 ge_mac_cfg_2_value = priv->ge_mac_cfg_2_value;

	अगर (ndev->flags & IFF_PROMISC) अणु
		ge_mac_cfg_2_value = (ge_mac_cfg_2_value & ~CFG_2_DISK_DA_MASK)
			 | NPS_ENET_DISABLE << CFG_2_DISK_DA_SHIFT;
		ge_mac_cfg_2_value = (ge_mac_cfg_2_value & ~CFG_2_DISK_MC_MASK)
			 | NPS_ENET_DISABLE << CFG_2_DISK_MC_SHIFT;

	पूर्ण अन्यथा अणु
		ge_mac_cfg_2_value = (ge_mac_cfg_2_value & ~CFG_2_DISK_DA_MASK)
			 | NPS_ENET_ENABLE << CFG_2_DISK_DA_SHIFT;
		ge_mac_cfg_2_value = (ge_mac_cfg_2_value & ~CFG_2_DISK_MC_MASK)
			 | NPS_ENET_ENABLE << CFG_2_DISK_MC_SHIFT;
	पूर्ण

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_2, ge_mac_cfg_2_value);
पूर्ण

/**
 * nps_enet_खोलो - Open the network device.
 * @ndev:       Poपूर्णांकer to the network device.
 *
 * वापसs: 0, on success or non-zero error value on failure.
 *
 * This function sets the MAC address, requests and enables an IRQ
 * क्रम the ENET device and starts the Tx queue.
 */
अटल s32 nps_enet_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);
	s32 err;

	/* Reset निजी variables */
	priv->tx_skb = शून्य;
	priv->ge_mac_cfg_2_value = 0;
	priv->ge_mac_cfg_3_value = 0;

	/* ge_mac_cfg_3 शेष values */
	priv->ge_mac_cfg_3_value |=
		 NPS_ENET_GE_MAC_CFG_3_RX_IFG_TH << CFG_3_RX_IFG_TH_SHIFT;

	priv->ge_mac_cfg_3_value |=
		 NPS_ENET_GE_MAC_CFG_3_MAX_LEN << CFG_3_MAX_LEN_SHIFT;

	/* Disable HW device */
	nps_enet_hw_disable_control(ndev);

	/* irq Rx allocation */
	err = request_irq(priv->irq, nps_enet_irq_handler,
			  0, "enet-rx-tx", ndev);
	अगर (err)
		वापस err;

	napi_enable(&priv->napi);

	/* Enable HW device */
	nps_enet_hw_reset(ndev);
	nps_enet_hw_enable_control(ndev);

	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

/**
 * nps_enet_stop - Close the network device.
 * @ndev:       Poपूर्णांकer to the network device.
 *
 * This function stops the Tx queue, disables पूर्णांकerrupts क्रम the ENET device.
 */
अटल s32 nps_enet_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);
	netअगर_stop_queue(ndev);
	nps_enet_hw_disable_control(ndev);
	मुक्त_irq(priv->irq, ndev);

	वापस 0;
पूर्ण

/**
 * nps_enet_start_xmit - Starts the data transmission.
 * @skb:        sk_buff poपूर्णांकer that contains data to be Transmitted.
 * @ndev:       Poपूर्णांकer to net_device काष्ठाure.
 *
 * वापसs: NETDEV_TX_OK, on success
 *              NETDEV_TX_BUSY, अगर any of the descriptors are not मुक्त.
 *
 * This function is invoked from upper layers to initiate transmission.
 */
अटल netdev_tx_t nps_enet_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *ndev)
अणु
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);

	/* This driver handles one frame at a समय  */
	netअगर_stop_queue(ndev);

	priv->tx_skb = skb;

	/* make sure tx_skb is actually written to the memory
	 * beक्रमe the HW is inक्रमmed and the IRQ is fired.
	 */
	wmb();

	nps_enet_send_frame(ndev, skb);

	वापस NETDEV_TX_OK;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम nps_enet_poll_controller(काष्ठा net_device *ndev)
अणु
	disable_irq(ndev->irq);
	nps_enet_irq_handler(ndev->irq, ndev);
	enable_irq(ndev->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops nps_netdev_ops = अणु
	.nकरो_खोलो		= nps_enet_खोलो,
	.nकरो_stop		= nps_enet_stop,
	.nकरो_start_xmit		= nps_enet_start_xmit,
	.nकरो_set_mac_address	= nps_enet_set_mac_address,
	.nकरो_set_rx_mode        = nps_enet_set_rx_mode,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= nps_enet_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल s32 nps_enet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा net_device *ndev;
	काष्ठा nps_enet_priv *priv;
	s32 err = 0;

	अगर (!dev->of_node)
		वापस -ENODEV;

	ndev = alloc_etherdev(माप(काष्ठा nps_enet_priv));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);
	priv = netdev_priv(ndev);

	/* The EZ NET specअगरic entries in the device काष्ठाure. */
	ndev->netdev_ops = &nps_netdev_ops;
	ndev->watchकरोg_समयo = (400 * HZ / 1000);
	/* FIXME :: no multicast support yet */
	ndev->flags &= ~IFF_MULTICAST;

	priv->regs_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs_base)) अणु
		err = PTR_ERR(priv->regs_base);
		जाओ out_netdev;
	पूर्ण
	dev_dbg(dev, "Registers base address is 0x%p\n", priv->regs_base);

	/* set kernel MAC address to dev */
	err = of_get_mac_address(dev->of_node, ndev->dev_addr);
	अगर (err)
		eth_hw_addr_अक्रमom(ndev);

	/* Get IRQ number */
	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (!priv->irq) अणु
		dev_err(dev, "failed to retrieve <irq Rx-Tx> value from device tree\n");
		err = -ENODEV;
		जाओ out_netdev;
	पूर्ण

	netअगर_napi_add(ndev, &priv->napi, nps_enet_poll,
		       NPS_ENET_NAPI_POLL_WEIGHT);

	/* Register the driver. Should be the last thing in probe */
	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		dev_err(dev, "Failed to register ndev for %s, err = 0x%08x\n",
			ndev->name, (s32)err);
		जाओ out_netअगर_api;
	पूर्ण

	dev_info(dev, "(rx/tx=%d)\n", priv->irq);
	वापस 0;

out_netअगर_api:
	netअगर_napi_del(&priv->napi);
out_netdev:
	अगर (err)
		मुक्त_netdev(ndev);

	वापस err;
पूर्ण

अटल s32 nps_enet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा nps_enet_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_netdev(ndev);
	मुक्त_netdev(ndev);
	netअगर_napi_del(&priv->napi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id nps_enet_dt_ids[] = अणु
	अणु .compatible = "ezchip,nps-mgt-enet" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nps_enet_dt_ids);

अटल काष्ठा platक्रमm_driver nps_enet_driver = अणु
	.probe = nps_enet_probe,
	.हटाओ = nps_enet_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table  = nps_enet_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(nps_enet_driver);

MODULE_AUTHOR("EZchip Semiconductor");
MODULE_LICENSE("GPL v2");
