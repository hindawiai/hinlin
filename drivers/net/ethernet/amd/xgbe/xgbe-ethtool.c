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

#समावेश <linux/spinlock.h>
#समावेश <linux/phy.h>
#समावेश <linux/net_tstamp.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

काष्ठा xgbe_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_size;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा XGMAC_MMC_STAT(_string, _var)				\
	अणु _string,						\
	  माप_field(काष्ठा xgbe_mmc_stats, _var),		\
	  दुरत्व(काष्ठा xgbe_prv_data, mmc_stats._var),	\
	पूर्ण

#घोषणा XGMAC_EXT_STAT(_string, _var)				\
	अणु _string,						\
	  माप_field(काष्ठा xgbe_ext_stats, _var),		\
	  दुरत्व(काष्ठा xgbe_prv_data, ext_stats._var),	\
	पूर्ण

अटल स्थिर काष्ठा xgbe_stats xgbe_gstring_stats[] = अणु
	XGMAC_MMC_STAT("tx_bytes", txoctetcount_gb),
	XGMAC_MMC_STAT("tx_packets", txframecount_gb),
	XGMAC_MMC_STAT("tx_unicast_packets", txunicastframes_gb),
	XGMAC_MMC_STAT("tx_broadcast_packets", txbroadcastframes_gb),
	XGMAC_MMC_STAT("tx_multicast_packets", txmulticastframes_gb),
	XGMAC_MMC_STAT("tx_vlan_packets", txvlanframes_g),
	XGMAC_EXT_STAT("tx_vxlan_packets", tx_vxlan_packets),
	XGMAC_EXT_STAT("tx_tso_packets", tx_tso_packets),
	XGMAC_MMC_STAT("tx_64_byte_packets", tx64octets_gb),
	XGMAC_MMC_STAT("tx_65_to_127_byte_packets", tx65to127octets_gb),
	XGMAC_MMC_STAT("tx_128_to_255_byte_packets", tx128to255octets_gb),
	XGMAC_MMC_STAT("tx_256_to_511_byte_packets", tx256to511octets_gb),
	XGMAC_MMC_STAT("tx_512_to_1023_byte_packets", tx512to1023octets_gb),
	XGMAC_MMC_STAT("tx_1024_to_max_byte_packets", tx1024tomaxoctets_gb),
	XGMAC_MMC_STAT("tx_underflow_errors", txunderflowerror),
	XGMAC_MMC_STAT("tx_pause_frames", txछोड़ोframes),

	XGMAC_MMC_STAT("rx_bytes", rxoctetcount_gb),
	XGMAC_MMC_STAT("rx_packets", rxframecount_gb),
	XGMAC_MMC_STAT("rx_unicast_packets", rxunicastframes_g),
	XGMAC_MMC_STAT("rx_broadcast_packets", rxbroadcastframes_g),
	XGMAC_MMC_STAT("rx_multicast_packets", rxmulticastframes_g),
	XGMAC_MMC_STAT("rx_vlan_packets", rxvlanframes_gb),
	XGMAC_EXT_STAT("rx_vxlan_packets", rx_vxlan_packets),
	XGMAC_MMC_STAT("rx_64_byte_packets", rx64octets_gb),
	XGMAC_MMC_STAT("rx_65_to_127_byte_packets", rx65to127octets_gb),
	XGMAC_MMC_STAT("rx_128_to_255_byte_packets", rx128to255octets_gb),
	XGMAC_MMC_STAT("rx_256_to_511_byte_packets", rx256to511octets_gb),
	XGMAC_MMC_STAT("rx_512_to_1023_byte_packets", rx512to1023octets_gb),
	XGMAC_MMC_STAT("rx_1024_to_max_byte_packets", rx1024tomaxoctets_gb),
	XGMAC_MMC_STAT("rx_undersize_packets", rxundersize_g),
	XGMAC_MMC_STAT("rx_oversize_packets", rxoversize_g),
	XGMAC_MMC_STAT("rx_crc_errors", rxcrcerror),
	XGMAC_MMC_STAT("rx_crc_errors_small_packets", rxrunterror),
	XGMAC_MMC_STAT("rx_crc_errors_giant_packets", rxjabbererror),
	XGMAC_MMC_STAT("rx_length_errors", rxlengtherror),
	XGMAC_MMC_STAT("rx_out_of_range_errors", rxoutofrangetype),
	XGMAC_MMC_STAT("rx_fifo_overflow_errors", rxfअगरooverflow),
	XGMAC_MMC_STAT("rx_watchdog_errors", rxwatchकरोgerror),
	XGMAC_EXT_STAT("rx_csum_errors", rx_csum_errors),
	XGMAC_EXT_STAT("rx_vxlan_csum_errors", rx_vxlan_csum_errors),
	XGMAC_MMC_STAT("rx_pause_frames", rxछोड़ोframes),
	XGMAC_EXT_STAT("rx_split_header_packets", rx_split_header_packets),
	XGMAC_EXT_STAT("rx_buffer_unavailable", rx_buffer_unavailable),
पूर्ण;

#घोषणा XGBE_STATS_COUNT	ARRAY_SIZE(xgbe_gstring_stats)

अटल व्योम xgbe_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < XGBE_STATS_COUNT; i++) अणु
			स_नकल(data, xgbe_gstring_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < pdata->tx_ring_count; i++) अणु
			प्र_लिखो(data, "txq_%u_packets", i);
			data += ETH_GSTRING_LEN;
			प्र_लिखो(data, "txq_%u_bytes", i);
			data += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < pdata->rx_ring_count; i++) अणु
			प्र_लिखो(data, "rxq_%u_packets", i);
			data += ETH_GSTRING_LEN;
			प्र_लिखो(data, "rxq_%u_bytes", i);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	u8 *stat;
	पूर्णांक i;

	pdata->hw_अगर.पढ़ो_mmc_stats(pdata);
	क्रम (i = 0; i < XGBE_STATS_COUNT; i++) अणु
		stat = (u8 *)pdata + xgbe_gstring_stats[i].stat_offset;
		*data++ = *(u64 *)stat;
	पूर्ण
	क्रम (i = 0; i < pdata->tx_ring_count; i++) अणु
		*data++ = pdata->ext_stats.txq_packets[i];
		*data++ = pdata->ext_stats.txq_bytes[i];
	पूर्ण
	क्रम (i = 0; i < pdata->rx_ring_count; i++) अणु
		*data++ = pdata->ext_stats.rxq_packets[i];
		*data++ = pdata->ext_stats.rxq_bytes[i];
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_get_sset_count(काष्ठा net_device *netdev, पूर्णांक stringset)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	पूर्णांक ret;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		ret = XGBE_STATS_COUNT +
		      (pdata->tx_ring_count * 2) +
		      (pdata->rx_ring_count * 2);
		अवरोध;

	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xgbe_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	छोड़ो->स्वतःneg = pdata->phy.छोड़ो_स्वतःneg;
	छोड़ो->tx_छोड़ो = pdata->phy.tx_छोड़ो;
	छोड़ो->rx_छोड़ो = pdata->phy.rx_छोड़ो;
पूर्ण

अटल पूर्णांक xgbe_set_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	पूर्णांक ret = 0;

	अगर (छोड़ो->स्वतःneg && (pdata->phy.स्वतःneg != AUTONEG_ENABLE)) अणु
		netdev_err(netdev,
			   "autoneg disabled, pause autoneg not available\n");
		वापस -EINVAL;
	पूर्ण

	pdata->phy.छोड़ो_स्वतःneg = छोड़ो->स्वतःneg;
	pdata->phy.tx_छोड़ो = छोड़ो->tx_छोड़ो;
	pdata->phy.rx_छोड़ो = छोड़ो->rx_छोड़ो;

	XGBE_CLR_ADV(lks, Pause);
	XGBE_CLR_ADV(lks, Asym_Pause);

	अगर (छोड़ो->rx_छोड़ो) अणु
		XGBE_SET_ADV(lks, Pause);
		XGBE_SET_ADV(lks, Asym_Pause);
	पूर्ण

	अगर (छोड़ो->tx_छोड़ो) अणु
		/* Equivalent to XOR of Asym_Pause */
		अगर (XGBE_ADV(lks, Asym_Pause))
			XGBE_CLR_ADV(lks, Asym_Pause);
		अन्यथा
			XGBE_SET_ADV(lks, Asym_Pause);
	पूर्ण

	अगर (netअगर_running(netdev))
		ret = pdata->phy_अगर.phy_config_aneg(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_get_link_ksettings(काष्ठा net_device *netdev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	cmd->base.phy_address = pdata->phy.address;

	cmd->base.स्वतःneg = pdata->phy.स्वतःneg;
	cmd->base.speed = pdata->phy.speed;
	cmd->base.duplex = pdata->phy.duplex;

	cmd->base.port = PORT_NONE;

	XGBE_LM_COPY(cmd, supported, lks, supported);
	XGBE_LM_COPY(cmd, advertising, lks, advertising);
	XGBE_LM_COPY(cmd, lp_advertising, lks, lp_advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_link_ksettings(काष्ठा net_device *netdev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
	u32 speed;
	पूर्णांक ret;

	speed = cmd->base.speed;

	अगर (cmd->base.phy_address != pdata->phy.address) अणु
		netdev_err(netdev, "invalid phy address %hhu\n",
			   cmd->base.phy_address);
		वापस -EINVAL;
	पूर्ण

	अगर ((cmd->base.स्वतःneg != AUTONEG_ENABLE) &&
	    (cmd->base.स्वतःneg != AUTONEG_DISABLE)) अणु
		netdev_err(netdev, "unsupported autoneg %hhu\n",
			   cmd->base.स्वतःneg);
		वापस -EINVAL;
	पूर्ण

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE) अणु
		अगर (!pdata->phy_अगर.phy_valid_speed(pdata, speed)) अणु
			netdev_err(netdev, "unsupported speed %u\n", speed);
			वापस -EINVAL;
		पूर्ण

		अगर (cmd->base.duplex != DUPLEX_FULL) अणु
			netdev_err(netdev, "unsupported duplex %hhu\n",
				   cmd->base.duplex);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	netअगर_dbg(pdata, link, netdev,
		  "requested advertisement 0x%*pb, phy supported 0x%*pb\n",
		  __ETHTOOL_LINK_MODE_MASK_NBITS, cmd->link_modes.advertising,
		  __ETHTOOL_LINK_MODE_MASK_NBITS, lks->link_modes.supported);

	biपंचांगap_and(advertising,
		   cmd->link_modes.advertising, lks->link_modes.supported,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	अगर ((cmd->base.स्वतःneg == AUTONEG_ENABLE) &&
	    biपंचांगap_empty(advertising, __ETHTOOL_LINK_MODE_MASK_NBITS)) अणु
		netdev_err(netdev,
			   "unsupported requested advertisement\n");
		वापस -EINVAL;
	पूर्ण

	ret = 0;
	pdata->phy.स्वतःneg = cmd->base.स्वतःneg;
	pdata->phy.speed = speed;
	pdata->phy.duplex = cmd->base.duplex;
	biपंचांगap_copy(lks->link_modes.advertising, advertising,
		    __ETHTOOL_LINK_MODE_MASK_NBITS);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE)
		XGBE_SET_ADV(lks, Autoneg);
	अन्यथा
		XGBE_CLR_ADV(lks, Autoneg);

	अगर (netअगर_running(netdev))
		ret = pdata->phy_अगर.phy_config_aneg(pdata);

	वापस ret;
पूर्ण

अटल व्योम xgbe_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_features *hw_feat = &pdata->hw_feat;

	strlcpy(drvinfo->driver, XGBE_DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, dev_name(pdata->dev),
		माप(drvinfo->bus_info));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version), "%d.%d.%d",
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, USERVER),
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, DEVID),
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, SNPSVER));
पूर्ण

अटल u32 xgbe_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	वापस pdata->msg_enable;
पूर्ण

अटल व्योम xgbe_set_msglevel(काष्ठा net_device *netdev, u32 msglevel)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	pdata->msg_enable = msglevel;
पूर्ण

अटल पूर्णांक xgbe_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	स_रखो(ec, 0, माप(काष्ठा ethtool_coalesce));

	ec->rx_coalesce_usecs = pdata->rx_usecs;
	ec->rx_max_coalesced_frames = pdata->rx_frames;

	ec->tx_max_coalesced_frames = pdata->tx_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	अचिन्हित पूर्णांक rx_frames, rx_riwt, rx_usecs;
	अचिन्हित पूर्णांक tx_frames;

	rx_riwt = hw_अगर->usec_to_riwt(pdata, ec->rx_coalesce_usecs);
	rx_usecs = ec->rx_coalesce_usecs;
	rx_frames = ec->rx_max_coalesced_frames;

	/* Use smallest possible value अगर conversion resulted in zero */
	अगर (rx_usecs && !rx_riwt)
		rx_riwt = 1;

	/* Check the bounds of values क्रम Rx */
	अगर (rx_riwt > XGMAC_MAX_DMA_RIWT) अणु
		netdev_err(netdev, "rx-usec is limited to %d usecs\n",
			   hw_अगर->riwt_to_usec(pdata, XGMAC_MAX_DMA_RIWT));
		वापस -EINVAL;
	पूर्ण
	अगर (rx_frames > pdata->rx_desc_count) अणु
		netdev_err(netdev, "rx-frames is limited to %d frames\n",
			   pdata->rx_desc_count);
		वापस -EINVAL;
	पूर्ण

	tx_frames = ec->tx_max_coalesced_frames;

	/* Check the bounds of values क्रम Tx */
	अगर (tx_frames > pdata->tx_desc_count) अणु
		netdev_err(netdev, "tx-frames is limited to %d frames\n",
			   pdata->tx_desc_count);
		वापस -EINVAL;
	पूर्ण

	pdata->rx_riwt = rx_riwt;
	pdata->rx_usecs = rx_usecs;
	pdata->rx_frames = rx_frames;
	hw_अगर->config_rx_coalesce(pdata);

	pdata->tx_frames = tx_frames;
	hw_अगर->config_tx_coalesce(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_get_rxnfc(काष्ठा net_device *netdev,
			  काष्ठा ethtool_rxnfc *rxnfc, u32 *rule_locs)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		rxnfc->data = pdata->rx_ring_count;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 xgbe_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	वापस माप(pdata->rss_key);
पूर्ण

अटल u32 xgbe_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	वापस ARRAY_SIZE(pdata->rss_table);
पूर्ण

अटल पूर्णांक xgbe_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			 u8 *hfunc)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	अचिन्हित पूर्णांक i;

	अगर (indir) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++)
			indir[i] = XGMAC_GET_BITS(pdata->rss_table[i],
						  MAC_RSSDR, DMCH);
	पूर्ण

	अगर (key)
		स_नकल(key, pdata->rss_key, माप(pdata->rss_key));

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			 स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	काष्ठा xgbe_hw_अगर *hw_अगर = &pdata->hw_अगर;
	अचिन्हित पूर्णांक ret;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP) अणु
		netdev_err(netdev, "unsupported hash function\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (indir) अणु
		ret = hw_अगर->set_rss_lookup_table(pdata, indir);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (key) अणु
		ret = hw_अगर->set_rss_hash_key(pdata, key);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_get_ts_info(काष्ठा net_device *netdev,
			    काष्ठा ethtool_ts_info *ts_info)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	ts_info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				   SOF_TIMESTAMPING_RX_SOFTWARE |
				   SOF_TIMESTAMPING_SOFTWARE |
				   SOF_TIMESTAMPING_TX_HARDWARE |
				   SOF_TIMESTAMPING_RX_HARDWARE |
				   SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (pdata->ptp_घड़ी)
		ts_info->phc_index = ptp_घड़ी_index(pdata->ptp_घड़ी);
	अन्यथा
		ts_info->phc_index = -1;

	ts_info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);
	ts_info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
			      (1 << HWTSTAMP_FILTER_ALL);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_get_module_info(काष्ठा net_device *netdev,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	वापस pdata->phy_अगर.module_info(pdata, modinfo);
पूर्ण

अटल पूर्णांक xgbe_get_module_eeprom(काष्ठा net_device *netdev,
				  काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	वापस pdata->phy_अगर.module_eeprom(pdata, eeprom, data);
पूर्ण

अटल व्योम xgbe_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ringparam)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	ringparam->rx_max_pending = XGBE_RX_DESC_CNT_MAX;
	ringparam->tx_max_pending = XGBE_TX_DESC_CNT_MAX;
	ringparam->rx_pending = pdata->rx_desc_count;
	ringparam->tx_pending = pdata->tx_desc_count;
पूर्ण

अटल पूर्णांक xgbe_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ringparam)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	अचिन्हित पूर्णांक rx, tx;

	अगर (ringparam->rx_mini_pending || ringparam->rx_jumbo_pending) अणु
		netdev_err(netdev, "unsupported ring parameter\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ringparam->rx_pending < XGBE_RX_DESC_CNT_MIN) ||
	    (ringparam->rx_pending > XGBE_RX_DESC_CNT_MAX)) अणु
		netdev_err(netdev,
			   "rx ring parameter must be between %u and %u\n",
			   XGBE_RX_DESC_CNT_MIN, XGBE_RX_DESC_CNT_MAX);
		वापस -EINVAL;
	पूर्ण

	अगर ((ringparam->tx_pending < XGBE_TX_DESC_CNT_MIN) ||
	    (ringparam->tx_pending > XGBE_TX_DESC_CNT_MAX)) अणु
		netdev_err(netdev,
			   "tx ring parameter must be between %u and %u\n",
			   XGBE_TX_DESC_CNT_MIN, XGBE_TX_DESC_CNT_MAX);
		वापस -EINVAL;
	पूर्ण

	rx = __roundकरोwn_घात_of_two(ringparam->rx_pending);
	अगर (rx != ringparam->rx_pending)
		netdev_notice(netdev,
			      "rx ring parameter rounded to power of two: %u\n",
			      rx);

	tx = __roundकरोwn_घात_of_two(ringparam->tx_pending);
	अगर (tx != ringparam->tx_pending)
		netdev_notice(netdev,
			      "tx ring parameter rounded to power of two: %u\n",
			      tx);

	अगर ((rx == pdata->rx_desc_count) &&
	    (tx == pdata->tx_desc_count))
		जाओ out;

	pdata->rx_desc_count = rx;
	pdata->tx_desc_count = tx;

	xgbe_restart_dev(pdata);

out:
	वापस 0;
पूर्ण

अटल व्योम xgbe_get_channels(काष्ठा net_device *netdev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	अचिन्हित पूर्णांक rx, tx, combined;

	/* Calculate maximums allowed:
	 *   - Take पूर्णांकo account the number of available IRQs
	 *   - Do not take पूर्णांकo account the number of online CPUs so that
	 *     the user can over-subscribe अगर desired
	 *   - Tx is additionally limited by the number of hardware queues
	 */
	rx = min(pdata->hw_feat.rx_ch_cnt, pdata->rx_max_channel_count);
	rx = min(rx, pdata->channel_irq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channel_count);
	tx = min(tx, pdata->channel_irq_count);
	tx = min(tx, pdata->tx_max_q_count);

	combined = min(rx, tx);

	channels->max_combined = combined;
	channels->max_rx = rx ? rx - 1 : 0;
	channels->max_tx = tx ? tx - 1 : 0;

	/* Get current settings based on device state */
	rx = pdata->new_rx_ring_count ? : pdata->rx_ring_count;
	tx = pdata->new_tx_ring_count ? : pdata->tx_ring_count;

	combined = min(rx, tx);
	rx -= combined;
	tx -= combined;

	channels->combined_count = combined;
	channels->rx_count = rx;
	channels->tx_count = tx;
पूर्ण

अटल व्योम xgbe_prपूर्णांक_set_channels_input(काष्ठा net_device *netdev,
					  काष्ठा ethtool_channels *channels)
अणु
	netdev_err(netdev, "channel inputs: combined=%u, rx-only=%u, tx-only=%u\n",
		   channels->combined_count, channels->rx_count,
		   channels->tx_count);
पूर्ण

अटल पूर्णांक xgbe_set_channels(काष्ठा net_device *netdev,
			     काष्ठा ethtool_channels *channels)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	अचिन्हित पूर्णांक rx, rx_curr, tx, tx_curr, combined;

	/* Calculate maximums allowed:
	 *   - Take पूर्णांकo account the number of available IRQs
	 *   - Do not take पूर्णांकo account the number of online CPUs so that
	 *     the user can over-subscribe अगर desired
	 *   - Tx is additionally limited by the number of hardware queues
	 */
	rx = min(pdata->hw_feat.rx_ch_cnt, pdata->rx_max_channel_count);
	rx = min(rx, pdata->channel_irq_count);
	tx = min(pdata->hw_feat.tx_ch_cnt, pdata->tx_max_channel_count);
	tx = min(tx, pdata->tx_max_q_count);
	tx = min(tx, pdata->channel_irq_count);

	combined = min(rx, tx);

	/* Should not be setting other count */
	अगर (channels->other_count) अणु
		netdev_err(netdev,
			   "other channel count must be zero\n");
		वापस -EINVAL;
	पूर्ण

	/* Require at least one Combined (Rx and Tx) channel */
	अगर (!channels->combined_count) अणु
		netdev_err(netdev,
			   "at least one combined Rx/Tx channel is required\n");
		xgbe_prपूर्णांक_set_channels_input(netdev, channels);
		वापस -EINVAL;
	पूर्ण

	/* Check combined channels */
	अगर (channels->combined_count > combined) अणु
		netdev_err(netdev,
			   "combined channel count cannot exceed %u\n",
			   combined);
		xgbe_prपूर्णांक_set_channels_input(netdev, channels);
		वापस -EINVAL;
	पूर्ण

	/* Can have some Rx-only or Tx-only channels, but not both */
	अगर (channels->rx_count && channels->tx_count) अणु
		netdev_err(netdev,
			   "cannot specify both Rx-only and Tx-only channels\n");
		xgbe_prपूर्णांक_set_channels_input(netdev, channels);
		वापस -EINVAL;
	पूर्ण

	/* Check that we करोn't exceed the maximum number of channels */
	अगर ((channels->combined_count + channels->rx_count) > rx) अणु
		netdev_err(netdev,
			   "total Rx channels (%u) requested exceeds maximum available (%u)\n",
			   channels->combined_count + channels->rx_count, rx);
		xgbe_prपूर्णांक_set_channels_input(netdev, channels);
		वापस -EINVAL;
	पूर्ण

	अगर ((channels->combined_count + channels->tx_count) > tx) अणु
		netdev_err(netdev,
			   "total Tx channels (%u) requested exceeds maximum available (%u)\n",
			   channels->combined_count + channels->tx_count, tx);
		xgbe_prपूर्णांक_set_channels_input(netdev, channels);
		वापस -EINVAL;
	पूर्ण

	rx = channels->combined_count + channels->rx_count;
	tx = channels->combined_count + channels->tx_count;

	rx_curr = pdata->new_rx_ring_count ? : pdata->rx_ring_count;
	tx_curr = pdata->new_tx_ring_count ? : pdata->tx_ring_count;

	अगर ((rx == rx_curr) && (tx == tx_curr))
		जाओ out;

	pdata->new_rx_ring_count = rx;
	pdata->new_tx_ring_count = tx;

	xgbe_full_restart_dev(pdata);

out:
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xgbe_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = xgbe_get_drvinfo,
	.get_msglevel = xgbe_get_msglevel,
	.set_msglevel = xgbe_set_msglevel,
	.get_link = ethtool_op_get_link,
	.get_coalesce = xgbe_get_coalesce,
	.set_coalesce = xgbe_set_coalesce,
	.get_छोड़ोparam = xgbe_get_छोड़ोparam,
	.set_छोड़ोparam = xgbe_set_छोड़ोparam,
	.get_strings = xgbe_get_strings,
	.get_ethtool_stats = xgbe_get_ethtool_stats,
	.get_sset_count = xgbe_get_sset_count,
	.get_rxnfc = xgbe_get_rxnfc,
	.get_rxfh_key_size = xgbe_get_rxfh_key_size,
	.get_rxfh_indir_size = xgbe_get_rxfh_indir_size,
	.get_rxfh = xgbe_get_rxfh,
	.set_rxfh = xgbe_set_rxfh,
	.get_ts_info = xgbe_get_ts_info,
	.get_link_ksettings = xgbe_get_link_ksettings,
	.set_link_ksettings = xgbe_set_link_ksettings,
	.get_module_info = xgbe_get_module_info,
	.get_module_eeprom = xgbe_get_module_eeprom,
	.get_ringparam = xgbe_get_ringparam,
	.set_ringparam = xgbe_set_ringparam,
	.get_channels = xgbe_get_channels,
	.set_channels = xgbe_set_channels,
पूर्ण;

स्थिर काष्ठा ethtool_ops *xgbe_get_ethtool_ops(व्योम)
अणु
	वापस &xgbe_ethtool_ops;
पूर्ण
