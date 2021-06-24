<शैली गुरु>
/* Copyright 2008-2015 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/device.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/libfdt_env.h>

#समावेश "mac.h"
#समावेश "fman_mac.h"
#समावेश "fman_dtsec.h"
#समावेश "fman_tgec.h"
#समावेश "fman_memac.h"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("FSL FMan MAC API based driver");

काष्ठा mac_priv_s अणु
	काष्ठा device			*dev;
	व्योम __iomem			*vaddr;
	u8				cell_index;
	काष्ठा fman			*fman;
	काष्ठा device_node		*पूर्णांकernal_phy_node;
	/* List of multicast addresses */
	काष्ठा list_head		mc_addr_list;
	काष्ठा platक्रमm_device		*eth_dev;
	काष्ठा fixed_phy_status		*fixed_link;
	u16				speed;
	u16				max_speed;

	पूर्णांक (*enable)(काष्ठा fman_mac *mac_dev, क्रमागत comm_mode mode);
	पूर्णांक (*disable)(काष्ठा fman_mac *mac_dev, क्रमागत comm_mode mode);
पूर्ण;

काष्ठा mac_address अणु
	u8 addr[ETH_ALEN];
	काष्ठा list_head list;
पूर्ण;

अटल व्योम mac_exception(व्योम *handle, क्रमागत fman_mac_exceptions ex)
अणु
	काष्ठा mac_device	*mac_dev;
	काष्ठा mac_priv_s	*priv;

	mac_dev = handle;
	priv = mac_dev->priv;

	अगर (ex == FM_MAC_EX_10G_RX_FIFO_OVFL) अणु
		/* करोn't flag RX FIFO after the first */
		mac_dev->set_exception(mac_dev->fman_mac,
				       FM_MAC_EX_10G_RX_FIFO_OVFL, false);
		dev_err(priv->dev, "10G MAC got RX FIFO Error = %x\n", ex);
	पूर्ण

	dev_dbg(priv->dev, "%s:%s() -> %d\n", KBUILD_BASENAME ".c",
		__func__, ex);
पूर्ण

अटल व्योम set_fman_mac_params(काष्ठा mac_device *mac_dev,
				काष्ठा fman_mac_params *params)
अणु
	काष्ठा mac_priv_s *priv = mac_dev->priv;

	params->base_addr = (typeof(params->base_addr))
		devm_ioremap(priv->dev, mac_dev->res->start,
			     resource_size(mac_dev->res));
	स_नकल(&params->addr, mac_dev->addr, माप(mac_dev->addr));
	params->max_speed	= priv->max_speed;
	params->phy_अगर		= mac_dev->phy_अगर;
	params->basex_अगर	= false;
	params->mac_id		= priv->cell_index;
	params->fm		= (व्योम *)priv->fman;
	params->exception_cb	= mac_exception;
	params->event_cb	= mac_exception;
	params->dev_id		= mac_dev;
	params->पूर्णांकernal_phy_node = priv->पूर्णांकernal_phy_node;
पूर्ण

अटल पूर्णांक tgec_initialization(काष्ठा mac_device *mac_dev)
अणु
	पूर्णांक err;
	काष्ठा mac_priv_s	*priv;
	काष्ठा fman_mac_params	params;
	u32			version;

	priv = mac_dev->priv;

	set_fman_mac_params(mac_dev, &params);

	mac_dev->fman_mac = tgec_config(&params);
	अगर (!mac_dev->fman_mac) अणु
		err = -EINVAL;
		जाओ _वापस;
	पूर्ण

	err = tgec_cfg_max_frame_len(mac_dev->fman_mac, fman_get_max_frm());
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = tgec_init(mac_dev->fman_mac);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	/* For 10G MAC, disable Tx ECC exception */
	err = mac_dev->set_exception(mac_dev->fman_mac,
				     FM_MAC_EX_10G_TX_ECC_ER, false);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = tgec_get_version(mac_dev->fman_mac, &version);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	dev_info(priv->dev, "FMan XGEC version: 0x%08x\n", version);

	जाओ _वापस;

_वापस_fm_mac_मुक्त:
	tgec_मुक्त(mac_dev->fman_mac);

_वापस:
	वापस err;
पूर्ण

अटल पूर्णांक dtsec_initialization(काष्ठा mac_device *mac_dev)
अणु
	पूर्णांक			err;
	काष्ठा mac_priv_s	*priv;
	काष्ठा fman_mac_params	params;
	u32			version;

	priv = mac_dev->priv;

	set_fman_mac_params(mac_dev, &params);

	mac_dev->fman_mac = dtsec_config(&params);
	अगर (!mac_dev->fman_mac) अणु
		err = -EINVAL;
		जाओ _वापस;
	पूर्ण

	err = dtsec_cfg_max_frame_len(mac_dev->fman_mac, fman_get_max_frm());
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = dtsec_cfg_pad_and_crc(mac_dev->fman_mac, true);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = dtsec_init(mac_dev->fman_mac);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	/* For 1G MAC, disable by शेष the MIB counters overflow पूर्णांकerrupt */
	err = mac_dev->set_exception(mac_dev->fman_mac,
				     FM_MAC_EX_1G_RX_MIB_CNT_OVFL, false);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = dtsec_get_version(mac_dev->fman_mac, &version);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	dev_info(priv->dev, "FMan dTSEC version: 0x%08x\n", version);

	जाओ _वापस;

_वापस_fm_mac_मुक्त:
	dtsec_मुक्त(mac_dev->fman_mac);

_वापस:
	वापस err;
पूर्ण

अटल पूर्णांक memac_initialization(काष्ठा mac_device *mac_dev)
अणु
	पूर्णांक			 err;
	काष्ठा mac_priv_s	*priv;
	काष्ठा fman_mac_params	 params;

	priv = mac_dev->priv;

	set_fman_mac_params(mac_dev, &params);

	अगर (priv->max_speed == SPEED_10000)
		params.phy_अगर = PHY_INTERFACE_MODE_XGMII;

	mac_dev->fman_mac = memac_config(&params);
	अगर (!mac_dev->fman_mac) अणु
		err = -EINVAL;
		जाओ _वापस;
	पूर्ण

	err = memac_cfg_max_frame_len(mac_dev->fman_mac, fman_get_max_frm());
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = memac_cfg_reset_on_init(mac_dev->fman_mac, true);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = memac_cfg_fixed_link(mac_dev->fman_mac, priv->fixed_link);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	err = memac_init(mac_dev->fman_mac);
	अगर (err < 0)
		जाओ _वापस_fm_mac_मुक्त;

	dev_info(priv->dev, "FMan MEMAC\n");

	जाओ _वापस;

_वापस_fm_mac_मुक्त:
	memac_मुक्त(mac_dev->fman_mac);

_वापस:
	वापस err;
पूर्ण

अटल पूर्णांक start(काष्ठा mac_device *mac_dev)
अणु
	पूर्णांक	 err;
	काष्ठा phy_device *phy_dev = mac_dev->phy_dev;
	काष्ठा mac_priv_s *priv = mac_dev->priv;

	err = priv->enable(mac_dev->fman_mac, COMM_MODE_RX_AND_TX);
	अगर (!err && phy_dev)
		phy_start(phy_dev);

	वापस err;
पूर्ण

अटल पूर्णांक stop(काष्ठा mac_device *mac_dev)
अणु
	काष्ठा mac_priv_s *priv = mac_dev->priv;

	अगर (mac_dev->phy_dev)
		phy_stop(mac_dev->phy_dev);

	वापस priv->disable(mac_dev->fman_mac, COMM_MODE_RX_AND_TX);
पूर्ण

अटल पूर्णांक set_multi(काष्ठा net_device *net_dev, काष्ठा mac_device *mac_dev)
अणु
	काष्ठा mac_priv_s	*priv;
	काष्ठा mac_address	*old_addr, *पंचांगp;
	काष्ठा netdev_hw_addr	*ha;
	पूर्णांक			err;
	enet_addr_t		*addr;

	priv = mac_dev->priv;

	/* Clear previous address list */
	list_क्रम_each_entry_safe(old_addr, पंचांगp, &priv->mc_addr_list, list) अणु
		addr = (enet_addr_t *)old_addr->addr;
		err = mac_dev->हटाओ_hash_mac_addr(mac_dev->fman_mac, addr);
		अगर (err < 0)
			वापस err;

		list_del(&old_addr->list);
		kमुक्त(old_addr);
	पूर्ण

	/* Add all the addresses from the new list */
	netdev_क्रम_each_mc_addr(ha, net_dev) अणु
		addr = (enet_addr_t *)ha->addr;
		err = mac_dev->add_hash_mac_addr(mac_dev->fman_mac, addr);
		अगर (err < 0)
			वापस err;

		पंचांगp = kदो_स्मृति(माप(*पंचांगp), GFP_ATOMIC);
		अगर (!पंचांगp)
			वापस -ENOMEM;

		ether_addr_copy(पंचांगp->addr, ha->addr);
		list_add(&पंचांगp->list, &priv->mc_addr_list);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fman_set_mac_active_छोड़ो
 * @mac_dev:	A poपूर्णांकer to the MAC device
 * @rx:		Pause frame setting क्रम RX
 * @tx:		Pause frame setting क्रम TX
 *
 * Set the MAC RX/TX PAUSE frames settings
 *
 * Aव्योम redundant calls to FMD, अगर the MAC driver alपढ़ोy contains the desired
 * active PAUSE settings. Otherwise, the new active settings should be reflected
 * in FMan.
 *
 * Return: 0 on success; Error code otherwise.
 */
पूर्णांक fman_set_mac_active_छोड़ो(काष्ठा mac_device *mac_dev, bool rx, bool tx)
अणु
	काष्ठा fman_mac *fman_mac = mac_dev->fman_mac;
	पूर्णांक err = 0;

	अगर (rx != mac_dev->rx_छोड़ो_active) अणु
		err = mac_dev->set_rx_छोड़ो(fman_mac, rx);
		अगर (likely(err == 0))
			mac_dev->rx_छोड़ो_active = rx;
	पूर्ण

	अगर (tx != mac_dev->tx_छोड़ो_active) अणु
		u16 छोड़ो_समय = (tx ? FSL_FM_PAUSE_TIME_ENABLE :
					 FSL_FM_PAUSE_TIME_DISABLE);

		err = mac_dev->set_tx_छोड़ो(fman_mac, 0, छोड़ो_समय, 0);

		अगर (likely(err == 0))
			mac_dev->tx_छोड़ो_active = tx;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(fman_set_mac_active_छोड़ो);

/**
 * fman_get_छोड़ो_cfg
 * @mac_dev:	A poपूर्णांकer to the MAC device
 * @rx_छोड़ो:	Return value क्रम RX setting
 * @tx_छोड़ो:	Return value क्रम TX setting
 *
 * Determine the MAC RX/TX PAUSE frames settings based on PHY
 * स्वतःnegotiation or values set by eththool.
 *
 * Return: Poपूर्णांकer to FMan device.
 */
व्योम fman_get_छोड़ो_cfg(काष्ठा mac_device *mac_dev, bool *rx_छोड़ो,
			bool *tx_छोड़ो)
अणु
	काष्ठा phy_device *phy_dev = mac_dev->phy_dev;
	u16 lcl_adv, rmt_adv;
	u8 flowctrl;

	*rx_छोड़ो = *tx_छोड़ो = false;

	अगर (!phy_dev->duplex)
		वापस;

	/* If PAUSE स्वतःnegotiation is disabled, the TX/RX PAUSE settings
	 * are those set by ethtool.
	 */
	अगर (!mac_dev->स्वतःneg_छोड़ो) अणु
		*rx_छोड़ो = mac_dev->rx_छोड़ो_req;
		*tx_छोड़ो = mac_dev->tx_छोड़ो_req;
		वापस;
	पूर्ण

	/* Else अगर PAUSE स्वतःnegotiation is enabled, the TX/RX PAUSE
	 * settings depend on the result of the link negotiation.
	 */

	/* get local capabilities */
	lcl_adv = linkmode_adv_to_lcl_adv_t(phy_dev->advertising);

	/* get link partner capabilities */
	rmt_adv = 0;
	अगर (phy_dev->छोड़ो)
		rmt_adv |= LPA_PAUSE_CAP;
	अगर (phy_dev->asym_छोड़ो)
		rmt_adv |= LPA_PAUSE_ASYM;

	/* Calculate TX/RX settings based on local and peer advertised
	 * symmetric/asymmetric PAUSE capabilities.
	 */
	flowctrl = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
	अगर (flowctrl & FLOW_CTRL_RX)
		*rx_छोड़ो = true;
	अगर (flowctrl & FLOW_CTRL_TX)
		*tx_छोड़ो = true;
पूर्ण
EXPORT_SYMBOL(fman_get_छोड़ो_cfg);

अटल व्योम adjust_link_व्योम(काष्ठा mac_device *mac_dev)
अणु
पूर्ण

अटल व्योम adjust_link_dtsec(काष्ठा mac_device *mac_dev)
अणु
	काष्ठा phy_device *phy_dev = mac_dev->phy_dev;
	काष्ठा fman_mac *fman_mac;
	bool rx_छोड़ो, tx_छोड़ो;
	पूर्णांक err;

	fman_mac = mac_dev->fman_mac;
	अगर (!phy_dev->link) अणु
		dtsec_restart_स्वतःneg(fman_mac);

		वापस;
	पूर्ण

	dtsec_adjust_link(fman_mac, phy_dev->speed);
	fman_get_छोड़ो_cfg(mac_dev, &rx_छोड़ो, &tx_छोड़ो);
	err = fman_set_mac_active_छोड़ो(mac_dev, rx_छोड़ो, tx_छोड़ो);
	अगर (err < 0)
		dev_err(mac_dev->priv->dev, "fman_set_mac_active_pause() = %d\n",
			err);
पूर्ण

अटल व्योम adjust_link_memac(काष्ठा mac_device *mac_dev)
अणु
	काष्ठा phy_device *phy_dev = mac_dev->phy_dev;
	काष्ठा fman_mac *fman_mac;
	bool rx_छोड़ो, tx_छोड़ो;
	पूर्णांक err;

	fman_mac = mac_dev->fman_mac;
	memac_adjust_link(fman_mac, phy_dev->speed);

	fman_get_छोड़ो_cfg(mac_dev, &rx_छोड़ो, &tx_छोड़ो);
	err = fman_set_mac_active_छोड़ो(mac_dev, rx_छोड़ो, tx_छोड़ो);
	अगर (err < 0)
		dev_err(mac_dev->priv->dev, "fman_set_mac_active_pause() = %d\n",
			err);
पूर्ण

अटल व्योम setup_dtsec(काष्ठा mac_device *mac_dev)
अणु
	mac_dev->init			= dtsec_initialization;
	mac_dev->set_promisc		= dtsec_set_promiscuous;
	mac_dev->change_addr		= dtsec_modअगरy_mac_address;
	mac_dev->add_hash_mac_addr	= dtsec_add_hash_mac_address;
	mac_dev->हटाओ_hash_mac_addr	= dtsec_del_hash_mac_address;
	mac_dev->set_tx_छोड़ो		= dtsec_set_tx_छोड़ो_frames;
	mac_dev->set_rx_छोड़ो		= dtsec_accept_rx_छोड़ो_frames;
	mac_dev->set_exception		= dtsec_set_exception;
	mac_dev->set_allmulti		= dtsec_set_allmulti;
	mac_dev->set_tstamp		= dtsec_set_tstamp;
	mac_dev->set_multi		= set_multi;
	mac_dev->start			= start;
	mac_dev->stop			= stop;
	mac_dev->adjust_link            = adjust_link_dtsec;
	mac_dev->priv->enable		= dtsec_enable;
	mac_dev->priv->disable		= dtsec_disable;
पूर्ण

अटल व्योम setup_tgec(काष्ठा mac_device *mac_dev)
अणु
	mac_dev->init			= tgec_initialization;
	mac_dev->set_promisc		= tgec_set_promiscuous;
	mac_dev->change_addr		= tgec_modअगरy_mac_address;
	mac_dev->add_hash_mac_addr	= tgec_add_hash_mac_address;
	mac_dev->हटाओ_hash_mac_addr	= tgec_del_hash_mac_address;
	mac_dev->set_tx_छोड़ो		= tgec_set_tx_छोड़ो_frames;
	mac_dev->set_rx_छोड़ो		= tgec_accept_rx_छोड़ो_frames;
	mac_dev->set_exception		= tgec_set_exception;
	mac_dev->set_allmulti		= tgec_set_allmulti;
	mac_dev->set_tstamp		= tgec_set_tstamp;
	mac_dev->set_multi		= set_multi;
	mac_dev->start			= start;
	mac_dev->stop			= stop;
	mac_dev->adjust_link            = adjust_link_व्योम;
	mac_dev->priv->enable		= tgec_enable;
	mac_dev->priv->disable		= tgec_disable;
पूर्ण

अटल व्योम setup_memac(काष्ठा mac_device *mac_dev)
अणु
	mac_dev->init			= memac_initialization;
	mac_dev->set_promisc		= memac_set_promiscuous;
	mac_dev->change_addr		= memac_modअगरy_mac_address;
	mac_dev->add_hash_mac_addr	= memac_add_hash_mac_address;
	mac_dev->हटाओ_hash_mac_addr	= memac_del_hash_mac_address;
	mac_dev->set_tx_छोड़ो		= memac_set_tx_छोड़ो_frames;
	mac_dev->set_rx_छोड़ो		= memac_accept_rx_छोड़ो_frames;
	mac_dev->set_exception		= memac_set_exception;
	mac_dev->set_allmulti		= memac_set_allmulti;
	mac_dev->set_tstamp		= memac_set_tstamp;
	mac_dev->set_multi		= set_multi;
	mac_dev->start			= start;
	mac_dev->stop			= stop;
	mac_dev->adjust_link            = adjust_link_memac;
	mac_dev->priv->enable		= memac_enable;
	mac_dev->priv->disable		= memac_disable;
पूर्ण

#घोषणा DTSEC_SUPPORTED \
	(SUPPORTED_10baseT_Half \
	| SUPPORTED_10baseT_Full \
	| SUPPORTED_100baseT_Half \
	| SUPPORTED_100baseT_Full \
	| SUPPORTED_Autoneg \
	| SUPPORTED_Pause \
	| SUPPORTED_Asym_Pause \
	| SUPPORTED_MII)

अटल DEFINE_MUTEX(eth_lock);

अटल स्थिर u16 phy2speed[] = अणु
	[PHY_INTERFACE_MODE_MII]		= SPEED_100,
	[PHY_INTERFACE_MODE_GMII]		= SPEED_1000,
	[PHY_INTERFACE_MODE_SGMII]		= SPEED_1000,
	[PHY_INTERFACE_MODE_TBI]		= SPEED_1000,
	[PHY_INTERFACE_MODE_RMII]		= SPEED_100,
	[PHY_INTERFACE_MODE_RGMII]		= SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_ID]		= SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_RXID]	= SPEED_1000,
	[PHY_INTERFACE_MODE_RGMII_TXID]	= SPEED_1000,
	[PHY_INTERFACE_MODE_RTBI]		= SPEED_1000,
	[PHY_INTERFACE_MODE_QSGMII]		= SPEED_1000,
	[PHY_INTERFACE_MODE_XGMII]		= SPEED_10000
पूर्ण;

अटल काष्ठा platक्रमm_device *dpaa_eth_add_device(पूर्णांक fman_id,
						   काष्ठा mac_device *mac_dev)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dpaa_eth_data data;
	काष्ठा mac_priv_s	*priv;
	अटल पूर्णांक dpaa_eth_dev_cnt;
	पूर्णांक ret;

	priv = mac_dev->priv;

	data.mac_dev = mac_dev;
	data.mac_hw_id = priv->cell_index;
	data.fman_hw_id = fman_id;

	mutex_lock(&eth_lock);
	pdev = platक्रमm_device_alloc("dpaa-ethernet", dpaa_eth_dev_cnt);
	अगर (!pdev) अणु
		ret = -ENOMEM;
		जाओ no_mem;
	पूर्ण

	pdev->dev.parent = priv->dev;

	ret = platक्रमm_device_add_data(pdev, &data, माप(data));
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ err;

	dpaa_eth_dev_cnt++;
	mutex_unlock(&eth_lock);

	वापस pdev;

err:
	platक्रमm_device_put(pdev);
no_mem:
	mutex_unlock(&eth_lock);

	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा of_device_id mac_match[] = अणु
	अणु .compatible	= "fsl,fman-dtsec" पूर्ण,
	अणु .compatible	= "fsl,fman-xgec" पूर्ण,
	अणु .compatible	= "fsl,fman-memac" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mac_match);

अटल पूर्णांक mac_probe(काष्ठा platक्रमm_device *_of_dev)
अणु
	पूर्णांक			 err, i, nph;
	काष्ठा device		*dev;
	काष्ठा device_node	*mac_node, *dev_node;
	काष्ठा mac_device	*mac_dev;
	काष्ठा platक्रमm_device	*of_dev;
	काष्ठा resource		 res;
	काष्ठा mac_priv_s	*priv;
	u32			 val;
	u8			fman_id;
	phy_पूर्णांकerface_t          phy_अगर;

	dev = &_of_dev->dev;
	mac_node = dev->of_node;

	mac_dev = devm_kzalloc(dev, माप(*mac_dev), GFP_KERNEL);
	अगर (!mac_dev) अणु
		err = -ENOMEM;
		जाओ _वापस;
	पूर्ण
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		err = -ENOMEM;
		जाओ _वापस;
	पूर्ण

	/* Save निजी inक्रमmation */
	mac_dev->priv = priv;
	priv->dev = dev;

	अगर (of_device_is_compatible(mac_node, "fsl,fman-dtsec")) अणु
		setup_dtsec(mac_dev);
		priv->पूर्णांकernal_phy_node = of_parse_phandle(mac_node,
							  "tbi-handle", 0);
	पूर्ण अन्यथा अगर (of_device_is_compatible(mac_node, "fsl,fman-xgec")) अणु
		setup_tgec(mac_dev);
	पूर्ण अन्यथा अगर (of_device_is_compatible(mac_node, "fsl,fman-memac")) अणु
		setup_memac(mac_dev);
		priv->पूर्णांकernal_phy_node = of_parse_phandle(mac_node,
							  "pcsphy-handle", 0);
	पूर्ण अन्यथा अणु
		dev_err(dev, "MAC node (%pOF) contains unsupported MAC\n",
			mac_node);
		err = -EINVAL;
		जाओ _वापस;
	पूर्ण

	INIT_LIST_HEAD(&priv->mc_addr_list);

	/* Get the FM node */
	dev_node = of_get_parent(mac_node);
	अगर (!dev_node) अणु
		dev_err(dev, "of_get_parent(%pOF) failed\n",
			mac_node);
		err = -EINVAL;
		जाओ _वापस_of_get_parent;
	पूर्ण

	of_dev = of_find_device_by_node(dev_node);
	अगर (!of_dev) अणु
		dev_err(dev, "of_find_device_by_node(%pOF) failed\n", dev_node);
		err = -EINVAL;
		जाओ _वापस_of_node_put;
	पूर्ण

	/* Get the FMan cell-index */
	err = of_property_पढ़ो_u32(dev_node, "cell-index", &val);
	अगर (err) अणु
		dev_err(dev, "failed to read cell-index for %pOF\n", dev_node);
		err = -EINVAL;
		जाओ _वापस_of_node_put;
	पूर्ण
	/* cell-index 0 => FMan id 1 */
	fman_id = (u8)(val + 1);

	priv->fman = fman_bind(&of_dev->dev);
	अगर (!priv->fman) अणु
		dev_err(dev, "fman_bind(%pOF) failed\n", dev_node);
		err = -ENODEV;
		जाओ _वापस_of_node_put;
	पूर्ण

	of_node_put(dev_node);

	/* Get the address of the memory mapped रेजिस्टरs */
	err = of_address_to_resource(mac_node, 0, &res);
	अगर (err < 0) अणु
		dev_err(dev, "of_address_to_resource(%pOF) = %d\n",
			mac_node, err);
		जाओ _वापस_of_get_parent;
	पूर्ण

	mac_dev->res = __devm_request_region(dev,
					     fman_get_mem_region(priv->fman),
					     res.start, resource_size(&res),
					     "mac");
	अगर (!mac_dev->res) अणु
		dev_err(dev, "__devm_request_mem_region(mac) failed\n");
		err = -EBUSY;
		जाओ _वापस_of_get_parent;
	पूर्ण

	priv->vaddr = devm_ioremap(dev, mac_dev->res->start,
				   resource_size(mac_dev->res));
	अगर (!priv->vaddr) अणु
		dev_err(dev, "devm_ioremap() failed\n");
		err = -EIO;
		जाओ _वापस_of_get_parent;
	पूर्ण

	अगर (!of_device_is_available(mac_node)) अणु
		err = -ENODEV;
		जाओ _वापस_of_get_parent;
	पूर्ण

	/* Get the cell-index */
	err = of_property_पढ़ो_u32(mac_node, "cell-index", &val);
	अगर (err) अणु
		dev_err(dev, "failed to read cell-index for %pOF\n", mac_node);
		err = -EINVAL;
		जाओ _वापस_of_get_parent;
	पूर्ण
	priv->cell_index = (u8)val;

	/* Get the MAC address */
	err = of_get_mac_address(mac_node, mac_dev->addr);
	अगर (err)
		dev_warn(dev, "of_get_mac_address(%pOF) failed\n", mac_node);

	/* Get the port handles */
	nph = of_count_phandle_with_args(mac_node, "fsl,fman-ports", शून्य);
	अगर (unlikely(nph < 0)) अणु
		dev_err(dev, "of_count_phandle_with_args(%pOF, fsl,fman-ports) failed\n",
			mac_node);
		err = nph;
		जाओ _वापस_of_get_parent;
	पूर्ण

	अगर (nph != ARRAY_SIZE(mac_dev->port)) अणु
		dev_err(dev, "Not supported number of fman-ports handles of mac node %pOF from device tree\n",
			mac_node);
		err = -EINVAL;
		जाओ _वापस_of_get_parent;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mac_dev->port); i++) अणु
		/* Find the port node */
		dev_node = of_parse_phandle(mac_node, "fsl,fman-ports", i);
		अगर (!dev_node) अणु
			dev_err(dev, "of_parse_phandle(%pOF, fsl,fman-ports) failed\n",
				mac_node);
			err = -EINVAL;
			जाओ _वापस_of_node_put;
		पूर्ण

		of_dev = of_find_device_by_node(dev_node);
		अगर (!of_dev) अणु
			dev_err(dev, "of_find_device_by_node(%pOF) failed\n",
				dev_node);
			err = -EINVAL;
			जाओ _वापस_of_node_put;
		पूर्ण

		mac_dev->port[i] = fman_port_bind(&of_dev->dev);
		अगर (!mac_dev->port[i]) अणु
			dev_err(dev, "dev_get_drvdata(%pOF) failed\n",
				dev_node);
			err = -EINVAL;
			जाओ _वापस_of_node_put;
		पूर्ण
		of_node_put(dev_node);
	पूर्ण

	/* Get the PHY connection type */
	err = of_get_phy_mode(mac_node, &phy_अगर);
	अगर (err) अणु
		dev_warn(dev,
			 "of_get_phy_mode() for %pOF failed. Defaulting to SGMII\n",
			 mac_node);
		phy_अगर = PHY_INTERFACE_MODE_SGMII;
	पूर्ण
	mac_dev->phy_अगर = phy_अगर;

	priv->speed		= phy2speed[mac_dev->phy_अगर];
	priv->max_speed		= priv->speed;
	mac_dev->अगर_support	= DTSEC_SUPPORTED;
	/* We करोn't support half-duplex in SGMII mode */
	अगर (mac_dev->phy_अगर == PHY_INTERFACE_MODE_SGMII)
		mac_dev->अगर_support &= ~(SUPPORTED_10baseT_Half |
					SUPPORTED_100baseT_Half);

	/* Gigabit support (no half-duplex) */
	अगर (priv->max_speed == 1000)
		mac_dev->अगर_support |= SUPPORTED_1000baseT_Full;

	/* The 10G पूर्णांकerface only supports one mode */
	अगर (mac_dev->phy_अगर == PHY_INTERFACE_MODE_XGMII)
		mac_dev->अगर_support = SUPPORTED_10000baseT_Full;

	/* Get the rest of the PHY inक्रमmation */
	mac_dev->phy_node = of_parse_phandle(mac_node, "phy-handle", 0);
	अगर (!mac_dev->phy_node && of_phy_is_fixed_link(mac_node)) अणु
		काष्ठा phy_device *phy;

		err = of_phy_रेजिस्टर_fixed_link(mac_node);
		अगर (err)
			जाओ _वापस_of_get_parent;

		priv->fixed_link = kzalloc(माप(*priv->fixed_link),
					   GFP_KERNEL);
		अगर (!priv->fixed_link) अणु
			err = -ENOMEM;
			जाओ _वापस_of_get_parent;
		पूर्ण

		mac_dev->phy_node = of_node_get(mac_node);
		phy = of_phy_find_device(mac_dev->phy_node);
		अगर (!phy) अणु
			err = -EINVAL;
			of_node_put(mac_dev->phy_node);
			जाओ _वापस_of_get_parent;
		पूर्ण

		priv->fixed_link->link = phy->link;
		priv->fixed_link->speed = phy->speed;
		priv->fixed_link->duplex = phy->duplex;
		priv->fixed_link->छोड़ो = phy->छोड़ो;
		priv->fixed_link->asym_छोड़ो = phy->asym_छोड़ो;

		put_device(&phy->mdio.dev);
	पूर्ण

	err = mac_dev->init(mac_dev);
	अगर (err < 0) अणु
		dev_err(dev, "mac_dev->init() = %d\n", err);
		of_node_put(mac_dev->phy_node);
		जाओ _वापस_of_get_parent;
	पूर्ण

	/* छोड़ो frame स्वतःnegotiation enabled */
	mac_dev->स्वतःneg_छोड़ो = true;

	/* By पूर्णांकializing the values to false, क्रमce FMD to enable PAUSE frames
	 * on RX and TX
	 */
	mac_dev->rx_छोड़ो_req = true;
	mac_dev->tx_छोड़ो_req = true;
	mac_dev->rx_छोड़ो_active = false;
	mac_dev->tx_छोड़ो_active = false;
	err = fman_set_mac_active_छोड़ो(mac_dev, true, true);
	अगर (err < 0)
		dev_err(dev, "fman_set_mac_active_pause() = %d\n", err);

	अगर (!is_zero_ether_addr(mac_dev->addr))
		dev_info(dev, "FMan MAC address: %pM\n", mac_dev->addr);

	priv->eth_dev = dpaa_eth_add_device(fman_id, mac_dev);
	अगर (IS_ERR(priv->eth_dev)) अणु
		dev_err(dev, "failed to add Ethernet platform device for MAC %d\n",
			priv->cell_index);
		priv->eth_dev = शून्य;
	पूर्ण

	जाओ _वापस;

_वापस_of_node_put:
	of_node_put(dev_node);
_वापस_of_get_parent:
	kमुक्त(priv->fixed_link);
_वापस:
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver mac_driver = अणु
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= mac_match,
	पूर्ण,
	.probe		= mac_probe,
पूर्ण;

builtin_platक्रमm_driver(mac_driver);
