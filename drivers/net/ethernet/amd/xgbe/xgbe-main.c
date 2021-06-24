<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/notअगरier.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

MODULE_AUTHOR("Tom Lendacky <thomas.lendacky@amd.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION(XGBE_DRV_DESC);

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, " Network interface message level setting");

अटल स्थिर u32 शेष_msg_level = (NETIF_MSG_LINK | NETIF_MSG_IFDOWN |
				      NETIF_MSG_IFUP);

अटल व्योम xgbe_शेष_config(काष्ठा xgbe_prv_data *pdata)
अणु
	DBGPR("-->xgbe_default_config\n");

	pdata->blen = DMA_SBMR_BLEN_64;
	pdata->pbl = DMA_PBL_128;
	pdata->aal = 1;
	pdata->rd_osr_limit = 8;
	pdata->wr_osr_limit = 8;
	pdata->tx_sf_mode = MTL_TSF_ENABLE;
	pdata->tx_threshold = MTL_TX_THRESHOLD_64;
	pdata->tx_osp_mode = DMA_OSP_ENABLE;
	pdata->rx_sf_mode = MTL_RSF_DISABLE;
	pdata->rx_threshold = MTL_RX_THRESHOLD_64;
	pdata->छोड़ो_स्वतःneg = 1;
	pdata->tx_छोड़ो = 1;
	pdata->rx_छोड़ो = 1;
	pdata->phy_speed = SPEED_UNKNOWN;
	pdata->घातer_करोwn = 0;

	DBGPR("<--xgbe_default_config\n");
पूर्ण

अटल व्योम xgbe_init_all_fptrs(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_init_function_ptrs_dev(&pdata->hw_अगर);
	xgbe_init_function_ptrs_phy(&pdata->phy_अगर);
	xgbe_init_function_ptrs_i2c(&pdata->i2c_अगर);
	xgbe_init_function_ptrs_desc(&pdata->desc_अगर);

	pdata->vdata->init_function_ptrs_phy_impl(&pdata->phy_अगर);
पूर्ण

काष्ठा xgbe_prv_data *xgbe_alloc_pdata(काष्ठा device *dev)
अणु
	काष्ठा xgbe_prv_data *pdata;
	काष्ठा net_device *netdev;

	netdev = alloc_etherdev_mq(माप(काष्ठा xgbe_prv_data),
				   XGBE_MAX_DMA_CHANNELS);
	अगर (!netdev) अणु
		dev_err(dev, "alloc_etherdev_mq failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	SET_NETDEV_DEV(netdev, dev);
	pdata = netdev_priv(netdev);
	pdata->netdev = netdev;
	pdata->dev = dev;

	spin_lock_init(&pdata->lock);
	spin_lock_init(&pdata->xpcs_lock);
	mutex_init(&pdata->rss_mutex);
	spin_lock_init(&pdata->tstamp_lock);
	mutex_init(&pdata->i2c_mutex);
	init_completion(&pdata->i2c_complete);
	init_completion(&pdata->mdio_complete);

	pdata->msg_enable = netअगर_msg_init(debug, शेष_msg_level);

	set_bit(XGBE_DOWN, &pdata->dev_state);
	set_bit(XGBE_STOPPED, &pdata->dev_state);

	वापस pdata;
पूर्ण

व्योम xgbe_मुक्त_pdata(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;

	मुक्त_netdev(netdev);
पूर्ण

व्योम xgbe_set_counts(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set all the function poपूर्णांकers */
	xgbe_init_all_fptrs(pdata);

	/* Populate the hardware features */
	xgbe_get_all_hw_features(pdata);

	/* Set शेष max values अगर not provided */
	अगर (!pdata->tx_max_channel_count)
		pdata->tx_max_channel_count = pdata->hw_feat.tx_ch_cnt;
	अगर (!pdata->rx_max_channel_count)
		pdata->rx_max_channel_count = pdata->hw_feat.rx_ch_cnt;

	अगर (!pdata->tx_max_q_count)
		pdata->tx_max_q_count = pdata->hw_feat.tx_q_cnt;
	अगर (!pdata->rx_max_q_count)
		pdata->rx_max_q_count = pdata->hw_feat.rx_q_cnt;

	/* Calculate the number of Tx and Rx rings to be created
	 *  -Tx (DMA) Channels map 1-to-1 to Tx Queues so set
	 *   the number of Tx queues to the number of Tx channels
	 *   enabled
	 *  -Rx (DMA) Channels करो not map 1-to-1 so use the actual
	 *   number of Rx queues or maximum allowed
	 */
	pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, num_online_cpus(),
				     pdata->hw_feat.tx_ch_cnt);
	pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->tx_ring_count,
				     pdata->tx_max_channel_count);
	pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->tx_ring_count,
				     pdata->tx_max_q_count);

	pdata->tx_q_count = pdata->tx_ring_count;

	pdata->rx_ring_count = min_t(अचिन्हित पूर्णांक, num_online_cpus(),
				     pdata->hw_feat.rx_ch_cnt);
	pdata->rx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->rx_ring_count,
				     pdata->rx_max_channel_count);

	pdata->rx_q_count = min_t(अचिन्हित पूर्णांक, pdata->hw_feat.rx_q_cnt,
				  pdata->rx_max_q_count);

	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "TX/RX DMA channel count = %u/%u\n",
			pdata->tx_ring_count, pdata->rx_ring_count);
		dev_dbg(pdata->dev, "TX/RX hardware queue count = %u/%u\n",
			pdata->tx_q_count, pdata->rx_q_count);
	पूर्ण
पूर्ण

पूर्णांक xgbe_config_netdev(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा device *dev = pdata->dev;
	पूर्णांक ret;

	netdev->irq = pdata->dev_irq;
	netdev->base_addr = (अचिन्हित दीर्घ)pdata->xgmac_regs;
	स_नकल(netdev->dev_addr, pdata->mac_addr, netdev->addr_len);

	/* Initialize ECC बारtamps */
	pdata->tx_sec_period = jअगरfies;
	pdata->tx_ded_period = jअगरfies;
	pdata->rx_sec_period = jअगरfies;
	pdata->rx_ded_period = jअगरfies;
	pdata->desc_sec_period = jअगरfies;
	pdata->desc_ded_period = jअगरfies;

	/* Issue software reset to device */
	ret = pdata->hw_अगर.निकास(pdata);
	अगर (ret) अणु
		dev_err(dev, "software reset failed\n");
		वापस ret;
	पूर्ण

	/* Set शेष configuration data */
	xgbe_शेष_config(pdata);

	/* Set the DMA mask */
	ret = dma_set_mask_and_coherent(dev,
					DMA_BIT_MASK(pdata->hw_feat.dma_width));
	अगर (ret) अणु
		dev_err(dev, "dma_set_mask_and_coherent failed\n");
		वापस ret;
	पूर्ण

	/* Set शेष max values अगर not provided */
	अगर (!pdata->tx_max_fअगरo_size)
		pdata->tx_max_fअगरo_size = pdata->hw_feat.tx_fअगरo_size;
	अगर (!pdata->rx_max_fअगरo_size)
		pdata->rx_max_fअगरo_size = pdata->hw_feat.rx_fअगरo_size;

	/* Set and validate the number of descriptors क्रम a ring */
	BUILD_BUG_ON_NOT_POWER_OF_2(XGBE_TX_DESC_CNT);
	pdata->tx_desc_count = XGBE_TX_DESC_CNT;

	BUILD_BUG_ON_NOT_POWER_OF_2(XGBE_RX_DESC_CNT);
	pdata->rx_desc_count = XGBE_RX_DESC_CNT;

	/* Adjust the number of queues based on पूर्णांकerrupts asचिन्हित */
	अगर (pdata->channel_irq_count) अणु
		pdata->tx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->tx_ring_count,
					     pdata->channel_irq_count);
		pdata->rx_ring_count = min_t(अचिन्हित पूर्णांक, pdata->rx_ring_count,
					     pdata->channel_irq_count);

		अगर (netअगर_msg_probe(pdata))
			dev_dbg(pdata->dev,
				"adjusted TX/RX DMA channel count = %u/%u\n",
				pdata->tx_ring_count, pdata->rx_ring_count);
	पूर्ण

	/* Initialize RSS hash key */
	netdev_rss_key_fill(pdata->rss_key, माप(pdata->rss_key));

	XGMAC_SET_BITS(pdata->rss_options, MAC_RSSCR, IP2TE, 1);
	XGMAC_SET_BITS(pdata->rss_options, MAC_RSSCR, TCP4TE, 1);
	XGMAC_SET_BITS(pdata->rss_options, MAC_RSSCR, UDP4TE, 1);

	/* Call MDIO/PHY initialization routine */
	pdata->debugfs_an_cdr_workaround = pdata->vdata->an_cdr_workaround;
	ret = pdata->phy_अगर.phy_init(pdata);
	अगर (ret)
		वापस ret;

	/* Set device operations */
	netdev->netdev_ops = xgbe_get_netdev_ops();
	netdev->ethtool_ops = xgbe_get_ethtool_ops();
#अगर_घोषित CONFIG_AMD_XGBE_DCB
	netdev->dcbnl_ops = xgbe_get_dcbnl_ops();
#पूर्ण_अगर

	/* Set device features */
	netdev->hw_features = NETIF_F_SG |
			      NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM |
			      NETIF_F_RXCSUM |
			      NETIF_F_TSO |
			      NETIF_F_TSO6 |
			      NETIF_F_GRO |
			      NETIF_F_HW_VLAN_CTAG_RX |
			      NETIF_F_HW_VLAN_CTAG_TX |
			      NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर (pdata->hw_feat.rss)
		netdev->hw_features |= NETIF_F_RXHASH;

	अगर (pdata->hw_feat.vxn) अणु
		netdev->hw_enc_features = NETIF_F_SG |
					  NETIF_F_IP_CSUM |
					  NETIF_F_IPV6_CSUM |
					  NETIF_F_RXCSUM |
					  NETIF_F_TSO |
					  NETIF_F_TSO6 |
					  NETIF_F_GRO |
					  NETIF_F_GSO_UDP_TUNNEL |
					  NETIF_F_GSO_UDP_TUNNEL_CSUM;

		netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL |
				       NETIF_F_GSO_UDP_TUNNEL_CSUM;

		netdev->udp_tunnel_nic_info = xgbe_get_udp_tunnel_info();
	पूर्ण

	netdev->vlan_features |= NETIF_F_SG |
				 NETIF_F_IP_CSUM |
				 NETIF_F_IPV6_CSUM |
				 NETIF_F_TSO |
				 NETIF_F_TSO6;

	netdev->features |= netdev->hw_features;
	pdata->netdev_features = netdev->features;

	netdev->priv_flags |= IFF_UNICAST_FLT;
	netdev->min_mtu = 0;
	netdev->max_mtu = XGMAC_JUMBO_PACKET_MTU;

	/* Use शेष watchकरोg समयout */
	netdev->watchकरोg_समयo = 0;

	xgbe_init_rx_coalesce(pdata);
	xgbe_init_tx_coalesce(pdata);

	netअगर_carrier_off(netdev);
	ret = रेजिस्टर_netdev(netdev);
	अगर (ret) अणु
		dev_err(dev, "net device registration failed\n");
		वापस ret;
	पूर्ण

	अगर (IS_REACHABLE(CONFIG_PTP_1588_CLOCK))
		xgbe_ptp_रेजिस्टर(pdata);

	xgbe_debugfs_init(pdata);

	netअगर_dbg(pdata, drv, pdata->netdev, "%u Tx software queues\n",
		  pdata->tx_ring_count);
	netअगर_dbg(pdata, drv, pdata->netdev, "%u Rx software queues\n",
		  pdata->rx_ring_count);

	वापस 0;
पूर्ण

व्योम xgbe_deconfig_netdev(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;

	xgbe_debugfs_निकास(pdata);

	अगर (IS_REACHABLE(CONFIG_PTP_1588_CLOCK))
		xgbe_ptp_unरेजिस्टर(pdata);

	unरेजिस्टर_netdev(netdev);

	pdata->phy_अगर.phy_निकास(pdata);
पूर्ण

अटल पूर्णांक xgbe_netdev_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			     व्योम *data)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(data);
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	अगर (netdev->netdev_ops != xgbe_get_netdev_ops())
		जाओ out;

	चयन (event) अणु
	हाल NETDEV_CHANGENAME:
		xgbe_debugfs_नाम(pdata);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block xgbe_netdev_notअगरier = अणु
	.notअगरier_call = xgbe_netdev_event,
पूर्ण;

अटल पूर्णांक __init xgbe_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_netdevice_notअगरier(&xgbe_netdev_notअगरier);
	अगर (ret)
		वापस ret;

	ret = xgbe_platक्रमm_init();
	अगर (ret)
		जाओ err_platक्रमm_init;

	ret = xgbe_pci_init();
	अगर (ret)
		जाओ err_pci_init;

	वापस 0;

err_pci_init:
	xgbe_platक्रमm_निकास();
err_platक्रमm_init:
	unरेजिस्टर_netdevice_notअगरier(&xgbe_netdev_notअगरier);
	वापस ret;
पूर्ण

अटल व्योम __निकास xgbe_mod_निकास(व्योम)
अणु
	xgbe_pci_निकास();

	xgbe_platक्रमm_निकास();

	unरेजिस्टर_netdevice_notअगरier(&xgbe_netdev_notअगरier);
पूर्ण

module_init(xgbe_mod_init);
module_निकास(xgbe_mod_निकास);
