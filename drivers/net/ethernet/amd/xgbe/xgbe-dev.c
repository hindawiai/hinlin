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

#समावेश <linux/phy.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32poly.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल अंतरभूत अचिन्हित पूर्णांक xgbe_get_max_frame(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस pdata->netdev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_usec_to_riwt(काष्ठा xgbe_prv_data *pdata,
				      अचिन्हित पूर्णांक usec)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक ret;

	DBGPR("-->xgbe_usec_to_riwt\n");

	rate = pdata->sysclk_rate;

	/*
	 * Convert the input usec value to the watchकरोg समयr value. Each
	 * watchकरोg समयr value is equivalent to 256 घड़ी cycles.
	 * Calculate the required value as:
	 *   ( usec * ( प्रणाली_घड़ी_mhz / 10^6 ) / 256
	 */
	ret = (usec * (rate / 1000000)) / 256;

	DBGPR("<--xgbe_usec_to_riwt\n");

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_riwt_to_usec(काष्ठा xgbe_prv_data *pdata,
				      अचिन्हित पूर्णांक riwt)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक ret;

	DBGPR("-->xgbe_riwt_to_usec\n");

	rate = pdata->sysclk_rate;

	/*
	 * Convert the input watchकरोg समयr value to the usec value. Each
	 * watchकरोg समयr value is equivalent to 256 घड़ी cycles.
	 * Calculate the required value as:
	 *   ( riwt * 256 ) / ( प्रणाली_घड़ी_mhz / 10^6 )
	 */
	ret = (riwt * 256) / (rate / 1000000);

	DBGPR("<--xgbe_riwt_to_usec\n");

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_config_pbl_val(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक pblx8, pbl;
	अचिन्हित पूर्णांक i;

	pblx8 = DMA_PBL_X8_DISABLE;
	pbl = pdata->pbl;

	अगर (pdata->pbl > 32) अणु
		pblx8 = DMA_PBL_X8_ENABLE;
		pbl >>= 3;
	पूर्ण

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_CR, PBLX8,
				       pblx8);

		अगर (pdata->channel[i]->tx_ring)
			XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR,
					       PBL, pbl);

		अगर (pdata->channel[i]->rx_ring)
			XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR,
					       PBL, pbl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_osp_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, OSP,
				       pdata->tx_osp_mode);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_rsf_mode(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RSF, val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_tsf_mode(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TSF, val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_rx_threshold(काष्ठा xgbe_prv_data *pdata,
				    अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RTC, val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_tx_threshold(काष्ठा xgbe_prv_data *pdata,
				    अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TTC, val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_rx_coalesce(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RIWT, RWT,
				       pdata->rx_riwt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_tx_coalesce(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस 0;
पूर्ण

अटल व्योम xgbe_config_rx_buffer_size(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR, RBSZ,
				       pdata->rx_buf_size);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_tso_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, TSE, 1);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_sph_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_CR, SPH, 1);
	पूर्ण

	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, HDSMS, XGBE_SPH_HDSMS_SIZE);
पूर्ण

अटल पूर्णांक xgbe_ग_लिखो_rss_reg(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक type,
			      अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक रुको;
	पूर्णांक ret = 0;

	mutex_lock(&pdata->rss_mutex);

	अगर (XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	XGMAC_IOWRITE(pdata, MAC_RSSDR, val);

	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, RSSIA, index);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, ADDRT, type);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, CT, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, OB, 1);

	रुको = 1000;
	जबतक (रुको--) अणु
		अगर (!XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB))
			जाओ unlock;

		usleep_range(1000, 1500);
	पूर्ण

	ret = -EBUSY;

unlock:
	mutex_unlock(&pdata->rss_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_ग_लिखो_rss_hash_key(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक key_regs = माप(pdata->rss_key) / माप(u32);
	अचिन्हित पूर्णांक *key = (अचिन्हित पूर्णांक *)&pdata->rss_key;
	पूर्णांक ret;

	जबतक (key_regs--) अणु
		ret = xgbe_ग_लिखो_rss_reg(pdata, XGBE_RSS_HASH_KEY_TYPE,
					 key_regs, *key++);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_ग_लिखो_rss_lookup_table(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++) अणु
		ret = xgbe_ग_लिखो_rss_reg(pdata,
					 XGBE_RSS_LOOKUP_TABLE_TYPE, i,
					 pdata->rss_table[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_rss_hash_key(काष्ठा xgbe_prv_data *pdata, स्थिर u8 *key)
अणु
	स_नकल(pdata->rss_key, key, माप(pdata->rss_key));

	वापस xgbe_ग_लिखो_rss_hash_key(pdata);
पूर्ण

अटल पूर्णांक xgbe_set_rss_lookup_table(काष्ठा xgbe_prv_data *pdata,
				     स्थिर u32 *table)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++)
		XGMAC_SET_BITS(pdata->rss_table[i], MAC_RSSDR, DMCH, table[i]);

	वापस xgbe_ग_लिखो_rss_lookup_table(pdata);
पूर्ण

अटल पूर्णांक xgbe_enable_rss(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	अगर (!pdata->hw_feat.rss)
		वापस -EOPNOTSUPP;

	/* Program the hash key */
	ret = xgbe_ग_लिखो_rss_hash_key(pdata);
	अगर (ret)
		वापस ret;

	/* Program the lookup table */
	ret = xgbe_ग_लिखो_rss_lookup_table(pdata);
	अगर (ret)
		वापस ret;

	/* Set the RSS options */
	XGMAC_IOWRITE(pdata, MAC_RSSCR, pdata->rss_options);

	/* Enable RSS */
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSCR, RSSE, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_disable_rss(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!pdata->hw_feat.rss)
		वापस -EOPNOTSUPP;

	XGMAC_IOWRITE_BITS(pdata, MAC_RSSCR, RSSE, 0);

	वापस 0;
पूर्ण

अटल व्योम xgbe_config_rss(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	अगर (!pdata->hw_feat.rss)
		वापस;

	अगर (pdata->netdev->features & NETIF_F_RXHASH)
		ret = xgbe_enable_rss(pdata);
	अन्यथा
		ret = xgbe_disable_rss(pdata);

	अगर (ret)
		netdev_err(pdata->netdev,
			   "error configuring RSS, RSS disabled\n");
पूर्ण

अटल bool xgbe_is_pfc_queue(काष्ठा xgbe_prv_data *pdata,
			      अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक prio, tc;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++) अणु
		/* Does this queue handle the priority? */
		अगर (pdata->prio2q_map[prio] != queue)
			जारी;

		/* Get the Traffic Class क्रम this priority */
		tc = pdata->ets->prio_tc[prio];

		/* Check अगर PFC is enabled क्रम this traffic class */
		अगर (pdata->pfc->pfc_en & (1 << tc))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम xgbe_set_vxlan_id(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Program the VXLAN port */
	XGMAC_IOWRITE_BITS(pdata, MAC_TIR, TNID, pdata->vxlan_port);

	netअगर_dbg(pdata, drv, pdata->netdev, "VXLAN tunnel id set to %hx\n",
		  pdata->vxlan_port);
पूर्ण

अटल व्योम xgbe_enable_vxlan(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!pdata->hw_feat.vxn)
		वापस;

	/* Program the VXLAN port */
	xgbe_set_vxlan_id(pdata);

	/* Allow क्रम IPv6/UDP zero-checksum VXLAN packets */
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, VUCC, 1);

	/* Enable VXLAN tunneling mode */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, VNM, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, VNE, 1);

	netअगर_dbg(pdata, drv, pdata->netdev, "VXLAN acceleration enabled\n");
पूर्ण

अटल व्योम xgbe_disable_vxlan(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!pdata->hw_feat.vxn)
		वापस;

	/* Disable tunneling mode */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, VNE, 0);

	/* Clear IPv6/UDP zero-checksum VXLAN packets setting */
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, VUCC, 0);

	/* Clear the VXLAN port */
	XGMAC_IOWRITE_BITS(pdata, MAC_TIR, TNID, 0);

	netअगर_dbg(pdata, drv, pdata->netdev, "VXLAN acceleration disabled\n");
पूर्ण

अटल पूर्णांक xgbe_disable_tx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक max_q_count, q_count;
	अचिन्हित पूर्णांक reg, reg_val;
	अचिन्हित पूर्णांक i;

	/* Clear MTL flow control */
	क्रम (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, EHFC, 0);

	/* Clear MAC flow control */
	max_q_count = XGMAC_MAX_FLOW_CONTROL_QUEUES;
	q_count = min_t(अचिन्हित पूर्णांक, pdata->tx_q_count, max_q_count);
	reg = MAC_Q0TFCR;
	क्रम (i = 0; i < q_count; i++) अणु
		reg_val = XGMAC_IOREAD(pdata, reg);
		XGMAC_SET_BITS(reg_val, MAC_Q0TFCR, TFE, 0);
		XGMAC_IOWRITE(pdata, reg, reg_val);

		reg += MAC_QTFCR_INC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable_tx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ieee_pfc *pfc = pdata->pfc;
	काष्ठा ieee_ets *ets = pdata->ets;
	अचिन्हित पूर्णांक max_q_count, q_count;
	अचिन्हित पूर्णांक reg, reg_val;
	अचिन्हित पूर्णांक i;

	/* Set MTL flow control */
	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		अचिन्हित पूर्णांक ehfc = 0;

		अगर (pdata->rx_rfd[i]) अणु
			/* Flow control thresholds are established */
			अगर (pfc && ets) अणु
				अगर (xgbe_is_pfc_queue(pdata, i))
					ehfc = 1;
			पूर्ण अन्यथा अणु
				ehfc = 1;
			पूर्ण
		पूर्ण

		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, EHFC, ehfc);

		netअगर_dbg(pdata, drv, pdata->netdev,
			  "flow control %s for RXq%u\n",
			  ehfc ? "enabled" : "disabled", i);
	पूर्ण

	/* Set MAC flow control */
	max_q_count = XGMAC_MAX_FLOW_CONTROL_QUEUES;
	q_count = min_t(अचिन्हित पूर्णांक, pdata->tx_q_count, max_q_count);
	reg = MAC_Q0TFCR;
	क्रम (i = 0; i < q_count; i++) अणु
		reg_val = XGMAC_IOREAD(pdata, reg);

		/* Enable transmit flow control */
		XGMAC_SET_BITS(reg_val, MAC_Q0TFCR, TFE, 1);
		/* Set छोड़ो समय */
		XGMAC_SET_BITS(reg_val, MAC_Q0TFCR, PT, 0xffff);

		XGMAC_IOWRITE(pdata, reg, reg_val);

		reg += MAC_QTFCR_INC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_disable_rx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE_BITS(pdata, MAC_RFCR, RFE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable_rx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE_BITS(pdata, MAC_RFCR, RFE, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_tx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ieee_pfc *pfc = pdata->pfc;

	अगर (pdata->tx_छोड़ो || (pfc && pfc->pfc_en))
		xgbe_enable_tx_flow_control(pdata);
	अन्यथा
		xgbe_disable_tx_flow_control(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_rx_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ieee_pfc *pfc = pdata->pfc;

	अगर (pdata->rx_छोड़ो || (pfc && pfc->pfc_en))
		xgbe_enable_rx_flow_control(pdata);
	अन्यथा
		xgbe_disable_rx_flow_control(pdata);

	वापस 0;
पूर्ण

अटल व्योम xgbe_config_flow_control(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ieee_pfc *pfc = pdata->pfc;

	xgbe_config_tx_flow_control(pdata);
	xgbe_config_rx_flow_control(pdata);

	XGMAC_IOWRITE_BITS(pdata, MAC_RFCR, PFCE,
			   (pfc && pfc->pfc_en) ? 1 : 0);
पूर्ण

अटल व्योम xgbe_enable_dma_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_channel *channel;
	अचिन्हित पूर्णांक i, ver;

	/* Set the पूर्णांकerrupt mode अगर supported */
	अगर (pdata->channel_irq_mode)
		XGMAC_IOWRITE_BITS(pdata, DMA_MR, INTM,
				   pdata->channel_irq_mode);

	ver = XGMAC_GET_BITS(pdata->hw_feat.version, MAC_VR, SNPSVER);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		channel = pdata->channel[i];

		/* Clear all the पूर्णांकerrupts which are set */
		XGMAC_DMA_IOWRITE(channel, DMA_CH_SR,
				  XGMAC_DMA_IOREAD(channel, DMA_CH_SR));

		/* Clear all पूर्णांकerrupt enable bits */
		channel->curr_ier = 0;

		/* Enable following पूर्णांकerrupts
		 *   NIE  - Normal Interrupt Summary Enable
		 *   AIE  - Abnormal Interrupt Summary Enable
		 *   FBEE - Fatal Bus Error Enable
		 */
		अगर (ver < 0x21) अणु
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, NIE20, 1);
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, AIE20, 1);
		पूर्ण अन्यथा अणु
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, NIE, 1);
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, AIE, 1);
		पूर्ण
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, FBEE, 1);

		अगर (channel->tx_ring) अणु
			/* Enable the following Tx पूर्णांकerrupts
			 *   TIE  - Transmit Interrupt Enable (unless using
			 *          per channel पूर्णांकerrupts in edge triggered
			 *          mode)
			 */
			अगर (!pdata->per_channel_irq || pdata->channel_irq_mode)
				XGMAC_SET_BITS(channel->curr_ier,
					       DMA_CH_IER, TIE, 1);
		पूर्ण
		अगर (channel->rx_ring) अणु
			/* Enable following Rx पूर्णांकerrupts
			 *   RBUE - Receive Buffer Unavailable Enable
			 *   RIE  - Receive Interrupt Enable (unless using
			 *          per channel पूर्णांकerrupts in edge triggered
			 *          mode)
			 */
			XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RBUE, 1);
			अगर (!pdata->per_channel_irq || pdata->channel_irq_mode)
				XGMAC_SET_BITS(channel->curr_ier,
					       DMA_CH_IER, RIE, 1);
		पूर्ण

		XGMAC_DMA_IOWRITE(channel, DMA_CH_IER, channel->curr_ier);
	पूर्ण
पूर्ण

अटल व्योम xgbe_enable_mtl_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक mtl_q_isr;
	अचिन्हित पूर्णांक q_count, i;

	q_count = max(pdata->hw_feat.tx_q_cnt, pdata->hw_feat.rx_q_cnt);
	क्रम (i = 0; i < q_count; i++) अणु
		/* Clear all the पूर्णांकerrupts which are set */
		mtl_q_isr = XGMAC_MTL_IOREAD(pdata, i, MTL_Q_ISR);
		XGMAC_MTL_IOWRITE(pdata, i, MTL_Q_ISR, mtl_q_isr);

		/* No MTL पूर्णांकerrupts to be enabled */
		XGMAC_MTL_IOWRITE(pdata, i, MTL_Q_IER, 0);
	पूर्ण
पूर्ण

अटल व्योम xgbe_enable_mac_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक mac_ier = 0;

	/* Enable Timestamp पूर्णांकerrupt */
	XGMAC_SET_BITS(mac_ier, MAC_IER, TSIE, 1);

	XGMAC_IOWRITE(pdata, MAC_IER, mac_ier);

	/* Enable all counter पूर्णांकerrupts */
	XGMAC_IOWRITE_BITS(pdata, MMC_RIER, ALL_INTERRUPTS, 0xffffffff);
	XGMAC_IOWRITE_BITS(pdata, MMC_TIER, ALL_INTERRUPTS, 0xffffffff);

	/* Enable MDIO single command completion पूर्णांकerrupt */
	XGMAC_IOWRITE_BITS(pdata, MAC_MDIOIER, SNGLCOMPIE, 1);
पूर्ण

अटल व्योम xgbe_enable_ecc_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक ecc_isr, ecc_ier = 0;

	अगर (!pdata->vdata->ecc_support)
		वापस;

	/* Clear all the पूर्णांकerrupts which are set */
	ecc_isr = XP_IOREAD(pdata, XP_ECC_ISR);
	XP_IOWRITE(pdata, XP_ECC_ISR, ecc_isr);

	/* Enable ECC पूर्णांकerrupts */
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_SEC, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_SEC, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_DED, 1);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_SEC, 1);

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
पूर्ण

अटल व्योम xgbe_disable_ecc_ded(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक ecc_ier;

	ecc_ier = XP_IOREAD(pdata, XP_ECC_IER);

	/* Disable ECC DED पूर्णांकerrupts */
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_DED, 0);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_DED, 0);
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_DED, 0);

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
पूर्ण

अटल व्योम xgbe_disable_ecc_sec(काष्ठा xgbe_prv_data *pdata,
				 क्रमागत xgbe_ecc_sec sec)
अणु
	अचिन्हित पूर्णांक ecc_ier;

	ecc_ier = XP_IOREAD(pdata, XP_ECC_IER);

	/* Disable ECC SEC पूर्णांकerrupt */
	चयन (sec) अणु
	हाल XGBE_ECC_SEC_TX:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, TX_SEC, 0);
		अवरोध;
	हाल XGBE_ECC_SEC_RX:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, RX_SEC, 0);
		अवरोध;
	हाल XGBE_ECC_SEC_DESC:
	XP_SET_BITS(ecc_ier, XP_ECC_IER, DESC_SEC, 0);
		अवरोध;
	पूर्ण

	XP_IOWRITE(pdata, XP_ECC_IER, ecc_ier);
पूर्ण

अटल पूर्णांक xgbe_set_speed(काष्ठा xgbe_prv_data *pdata, पूर्णांक speed)
अणु
	अचिन्हित पूर्णांक ss;

	चयन (speed) अणु
	हाल SPEED_1000:
		ss = 0x03;
		अवरोध;
	हाल SPEED_2500:
		ss = 0x02;
		अवरोध;
	हाल SPEED_10000:
		ss = 0x00;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (XGMAC_IOREAD_BITS(pdata, MAC_TCR, SS) != ss)
		XGMAC_IOWRITE_BITS(pdata, MAC_TCR, SS, ss);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable_rx_vlan_stripping(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Put the VLAN tag in the Rx descriptor */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, EVLRXS, 1);

	/* Don't check the VLAN type */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, DOVLTC, 1);

	/* Check only C-TAG (0x8100) packets */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, ERSVLM, 0);

	/* Don't consider an S-TAG (0x88A8) packet as a VLAN packet */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, ESVL, 0);

	/* Enable VLAN tag stripping */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, EVLS, 0x3);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_disable_rx_vlan_stripping(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, EVLS, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable_rx_vlan_filtering(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Enable VLAN filtering */
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, VTFE, 1);

	/* Enable VLAN Hash Table filtering */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, VTHM, 1);

	/* Disable VLAN tag inverse matching */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, VTIM, 0);

	/* Only filter on the lower 12-bits of the VLAN tag */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, ETV, 1);

	/* In order क्रम the VLAN Hash Table filtering to be effective,
	 * the VLAN tag identअगरier in the VLAN Tag Register must not
	 * be zero.  Set the VLAN tag identअगरier to "1" to enable the
	 * VLAN Hash Table filtering.  This implies that a VLAN tag of
	 * 1 will always pass filtering.
	 */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANTR, VL, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_disable_rx_vlan_filtering(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Disable VLAN filtering */
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, VTFE, 0);

	वापस 0;
पूर्ण

अटल u32 xgbe_vid_crc32_le(__le16 vid_le)
अणु
	u32 crc = ~0;
	u32 temp = 0;
	अचिन्हित अक्षर *data = (अचिन्हित अक्षर *)&vid_le;
	अचिन्हित अक्षर data_byte = 0;
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

अटल पूर्णांक xgbe_update_vlan_hash_table(काष्ठा xgbe_prv_data *pdata)
अणु
	u32 crc;
	u16 vid;
	__le16 vid_le;
	u16 vlan_hash_table = 0;

	/* Generate the VLAN Hash Table value */
	क्रम_each_set_bit(vid, pdata->active_vlans, VLAN_N_VID) अणु
		/* Get the CRC32 value of the VLAN ID */
		vid_le = cpu_to_le16(vid);
		crc = bitrev32(~xgbe_vid_crc32_le(vid_le)) >> 28;

		vlan_hash_table |= (1 << crc);
	पूर्ण

	/* Set the VLAN Hash Table filtering रेजिस्टर */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANHTR, VLHT, vlan_hash_table);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_promiscuous_mode(काष्ठा xgbe_prv_data *pdata,
				     अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = enable ? 1 : 0;

	अगर (XGMAC_IOREAD_BITS(pdata, MAC_PFR, PR) == val)
		वापस 0;

	netअगर_dbg(pdata, drv, pdata->netdev, "%s promiscuous mode\n",
		  enable ? "entering" : "leaving");
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, PR, val);

	/* Hardware will still perक्रमm VLAN filtering in promiscuous mode */
	अगर (enable) अणु
		xgbe_disable_rx_vlan_filtering(pdata);
	पूर्ण अन्यथा अणु
		अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
			xgbe_enable_rx_vlan_filtering(pdata);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_all_multicast_mode(काष्ठा xgbe_prv_data *pdata,
				       अचिन्हित पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक val = enable ? 1 : 0;

	अगर (XGMAC_IOREAD_BITS(pdata, MAC_PFR, PM) == val)
		वापस 0;

	netअगर_dbg(pdata, drv, pdata->netdev, "%s allmulti mode\n",
		  enable ? "entering" : "leaving");
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, PM, val);

	वापस 0;
पूर्ण

अटल व्योम xgbe_set_mac_reg(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा netdev_hw_addr *ha, अचिन्हित पूर्णांक *mac_reg)
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

		XGMAC_SET_BITS(mac_addr_hi, MAC_MACA1HR, AE, 1);
	पूर्ण

	XGMAC_IOWRITE(pdata, *mac_reg, mac_addr_hi);
	*mac_reg += MAC_MACA_INC;
	XGMAC_IOWRITE(pdata, *mac_reg, mac_addr_lo);
	*mac_reg += MAC_MACA_INC;
पूर्ण

अटल व्योम xgbe_set_mac_addn_addrs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक mac_reg;
	अचिन्हित पूर्णांक addn_macs;

	mac_reg = MAC_MACA1HR;
	addn_macs = pdata->hw_feat.addn_mac;

	अगर (netdev_uc_count(netdev) > addn_macs) अणु
		xgbe_set_promiscuous_mode(pdata, 1);
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			xgbe_set_mac_reg(pdata, ha, &mac_reg);
			addn_macs--;
		पूर्ण

		अगर (netdev_mc_count(netdev) > addn_macs) अणु
			xgbe_set_all_multicast_mode(pdata, 1);
		पूर्ण अन्यथा अणु
			netdev_क्रम_each_mc_addr(ha, netdev) अणु
				xgbe_set_mac_reg(pdata, ha, &mac_reg);
				addn_macs--;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Clear reमुख्यing additional MAC address entries */
	जबतक (addn_macs--)
		xgbe_set_mac_reg(pdata, शून्य, &mac_reg);
पूर्ण

अटल व्योम xgbe_set_mac_hash_table(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक hash_reg;
	अचिन्हित पूर्णांक hash_table_shअगरt, hash_table_count;
	u32 hash_table[XGBE_MAC_HASH_TABLE_SIZE];
	u32 crc;
	अचिन्हित पूर्णांक i;

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
		XGMAC_IOWRITE(pdata, hash_reg, hash_table[i]);
		hash_reg += MAC_HTR_INC;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_add_mac_addresses(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->hw_feat.hash_table_size)
		xgbe_set_mac_hash_table(pdata);
	अन्यथा
		xgbe_set_mac_addn_addrs(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_mac_address(काष्ठा xgbe_prv_data *pdata, u8 *addr)
अणु
	अचिन्हित पूर्णांक mac_addr_hi, mac_addr_lo;

	mac_addr_hi = (addr[5] <<  8) | (addr[4] <<  0);
	mac_addr_lo = (addr[3] << 24) | (addr[2] << 16) |
		      (addr[1] <<  8) | (addr[0] <<  0);

	XGMAC_IOWRITE(pdata, MAC_MACA0HR, mac_addr_hi);
	XGMAC_IOWRITE(pdata, MAC_MACA0LR, mac_addr_lo);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_config_rx_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक pr_mode, am_mode;

	pr_mode = ((netdev->flags & IFF_PROMISC) != 0);
	am_mode = ((netdev->flags & IFF_ALLMULTI) != 0);

	xgbe_set_promiscuous_mode(pdata, pr_mode);
	xgbe_set_all_multicast_mode(pdata, am_mode);

	xgbe_add_mac_addresses(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_clr_gpio(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (gpio > 15)
		वापस -EINVAL;

	reg = XGMAC_IOREAD(pdata, MAC_GPIOSR);

	reg &= ~(1 << (gpio + 16));
	XGMAC_IOWRITE(pdata, MAC_GPIOSR, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_set_gpio(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक gpio)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (gpio > 15)
		वापस -EINVAL;

	reg = XGMAC_IOREAD(pdata, MAC_GPIOSR);

	reg |= (1 << (gpio + 16));
	XGMAC_IOWRITE(pdata, MAC_GPIOSR, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_पढ़ो_mmd_regs_v2(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
				 पूर्णांक mmd_reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mmd_address, index, offset;
	पूर्णांक mmd_data;

	अगर (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	अन्यथा
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS रेजिस्टरs are accessed using mmio. The underlying
	 * management पूर्णांकerface uses indirect addressing to access the MMD
	 * रेजिस्टर sets. This requires accessing of the PCS रेजिस्टर in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio पूर्णांकerface is based on 16-bit offsets and values. All
	 * रेजिस्टर offsets must thereक्रमe be adjusted by left shअगरting the
	 * offset 1 bit and पढ़ोing 16 bits of data.
	 */
	mmd_address <<= 1;
	index = mmd_address & ~pdata->xpcs_winकरोw_mask;
	offset = pdata->xpcs_winकरोw + (mmd_address & pdata->xpcs_winकरोw_mask);

	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, pdata->xpcs_winकरोw_sel_reg, index);
	mmd_data = XPCS16_IOREAD(pdata, offset);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);

	वापस mmd_data;
पूर्ण

अटल व्योम xgbe_ग_लिखो_mmd_regs_v2(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
				   पूर्णांक mmd_reg, पूर्णांक mmd_data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mmd_address, index, offset;

	अगर (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	अन्यथा
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS रेजिस्टरs are accessed using mmio. The underlying
	 * management पूर्णांकerface uses indirect addressing to access the MMD
	 * रेजिस्टर sets. This requires accessing of the PCS रेजिस्टर in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio पूर्णांकerface is based on 16-bit offsets and values. All
	 * रेजिस्टर offsets must thereक्रमe be adjusted by left shअगरting the
	 * offset 1 bit and writing 16 bits of data.
	 */
	mmd_address <<= 1;
	index = mmd_address & ~pdata->xpcs_winकरोw_mask;
	offset = pdata->xpcs_winकरोw + (mmd_address & pdata->xpcs_winकरोw_mask);

	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, pdata->xpcs_winकरोw_sel_reg, index);
	XPCS16_IOWRITE(pdata, offset, mmd_data);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);
पूर्ण

अटल पूर्णांक xgbe_पढ़ो_mmd_regs_v1(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
				 पूर्णांक mmd_reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mmd_address;
	पूर्णांक mmd_data;

	अगर (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	अन्यथा
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS रेजिस्टरs are accessed using mmio. The underlying APB3
	 * management पूर्णांकerface uses indirect addressing to access the MMD
	 * रेजिस्टर sets. This requires accessing of the PCS रेजिस्टर in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio पूर्णांकerface is based on 32-bit offsets and values. All
	 * रेजिस्टर offsets must thereक्रमe be adjusted by left shअगरting the
	 * offset 2 bits and पढ़ोing 32 bits of data.
	 */
	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, PCS_V1_WINDOW_SELECT, mmd_address >> 8);
	mmd_data = XPCS32_IOREAD(pdata, (mmd_address & 0xff) << 2);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);

	वापस mmd_data;
पूर्ण

अटल व्योम xgbe_ग_लिखो_mmd_regs_v1(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
				   पूर्णांक mmd_reg, पूर्णांक mmd_data)
अणु
	अचिन्हित पूर्णांक mmd_address;
	अचिन्हित दीर्घ flags;

	अगर (mmd_reg & MII_ADDR_C45)
		mmd_address = mmd_reg & ~MII_ADDR_C45;
	अन्यथा
		mmd_address = (pdata->mdio_mmd << 16) | (mmd_reg & 0xffff);

	/* The PCS रेजिस्टरs are accessed using mmio. The underlying APB3
	 * management पूर्णांकerface uses indirect addressing to access the MMD
	 * रेजिस्टर sets. This requires accessing of the PCS रेजिस्टर in two
	 * phases, an address phase and a data phase.
	 *
	 * The mmio पूर्णांकerface is based on 32-bit offsets and values. All
	 * रेजिस्टर offsets must thereक्रमe be adjusted by left shअगरting the
	 * offset 2 bits and writing 32 bits of data.
	 */
	spin_lock_irqsave(&pdata->xpcs_lock, flags);
	XPCS32_IOWRITE(pdata, PCS_V1_WINDOW_SELECT, mmd_address >> 8);
	XPCS32_IOWRITE(pdata, (mmd_address & 0xff) << 2, mmd_data);
	spin_unlock_irqrestore(&pdata->xpcs_lock, flags);
पूर्ण

अटल पूर्णांक xgbe_पढ़ो_mmd_regs(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
			      पूर्णांक mmd_reg)
अणु
	चयन (pdata->vdata->xpcs_access) अणु
	हाल XGBE_XPCS_ACCESS_V1:
		वापस xgbe_पढ़ो_mmd_regs_v1(pdata, prtad, mmd_reg);

	हाल XGBE_XPCS_ACCESS_V2:
	शेष:
		वापस xgbe_पढ़ो_mmd_regs_v2(pdata, prtad, mmd_reg);
	पूर्ण
पूर्ण

अटल व्योम xgbe_ग_लिखो_mmd_regs(काष्ठा xgbe_prv_data *pdata, पूर्णांक prtad,
				पूर्णांक mmd_reg, पूर्णांक mmd_data)
अणु
	चयन (pdata->vdata->xpcs_access) अणु
	हाल XGBE_XPCS_ACCESS_V1:
		वापस xgbe_ग_लिखो_mmd_regs_v1(pdata, prtad, mmd_reg, mmd_data);

	हाल XGBE_XPCS_ACCESS_V2:
	शेष:
		वापस xgbe_ग_लिखो_mmd_regs_v2(pdata, prtad, mmd_reg, mmd_data);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_create_mdio_sca(पूर्णांक port, पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक mdio_sca, da;

	da = (reg & MII_ADDR_C45) ? reg >> 16 : 0;

	mdio_sca = 0;
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, RA, reg);
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, PA, port);
	XGMAC_SET_BITS(mdio_sca, MAC_MDIOSCAR, DA, da);

	वापस mdio_sca;
पूर्ण

अटल पूर्णांक xgbe_ग_लिखो_ext_mii_regs(काष्ठा xgbe_prv_data *pdata, पूर्णांक addr,
				   पूर्णांक reg, u16 val)
अणु
	अचिन्हित पूर्णांक mdio_sca, mdio_sccd;

	reinit_completion(&pdata->mdio_complete);

	mdio_sca = xgbe_create_mdio_sca(addr, reg);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCAR, mdio_sca);

	mdio_sccd = 0;
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, DATA, val);
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, CMD, 1);
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, BUSY, 1);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCCDR, mdio_sccd);

	अगर (!रुको_क्रम_completion_समयout(&pdata->mdio_complete, HZ)) अणु
		netdev_err(pdata->netdev, "mdio write operation timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_पढ़ो_ext_mii_regs(काष्ठा xgbe_prv_data *pdata, पूर्णांक addr,
				  पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक mdio_sca, mdio_sccd;

	reinit_completion(&pdata->mdio_complete);

	mdio_sca = xgbe_create_mdio_sca(addr, reg);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCAR, mdio_sca);

	mdio_sccd = 0;
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, CMD, 3);
	XGMAC_SET_BITS(mdio_sccd, MAC_MDIOSCCDR, BUSY, 1);
	XGMAC_IOWRITE(pdata, MAC_MDIOSCCDR, mdio_sccd);

	अगर (!रुको_क्रम_completion_समयout(&pdata->mdio_complete, HZ)) अणु
		netdev_err(pdata->netdev, "mdio read operation timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस XGMAC_IOREAD_BITS(pdata, MAC_MDIOSCCDR, DATA);
पूर्ण

अटल पूर्णांक xgbe_set_ext_mii_mode(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक port,
				 क्रमागत xgbe_mdio_mode mode)
अणु
	अचिन्हित पूर्णांक reg_val = XGMAC_IOREAD(pdata, MAC_MDIOCL22R);

	चयन (mode) अणु
	हाल XGBE_MDIO_MODE_CL22:
		अगर (port > XGMAC_MAX_C22_PORT)
			वापस -EINVAL;
		reg_val |= (1 << port);
		अवरोध;
	हाल XGBE_MDIO_MODE_CL45:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	XGMAC_IOWRITE(pdata, MAC_MDIOCL22R, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_tx_complete(काष्ठा xgbe_ring_desc *rdesc)
अणु
	वापस !XGMAC_GET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN);
पूर्ण

अटल पूर्णांक xgbe_disable_rx_csum(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, IPC, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable_rx_csum(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, IPC, 1);

	वापस 0;
पूर्ण

अटल व्योम xgbe_tx_desc_reset(काष्ठा xgbe_ring_data *rdata)
अणु
	काष्ठा xgbe_ring_desc *rdesc = rdata->rdesc;

	/* Reset the Tx descriptor
	 *   Set buffer 1 (lo) address to zero
	 *   Set buffer 1 (hi) address to zero
	 *   Reset all other control bits (IC, TTSE, B2L & B1L)
	 *   Reset all other control bits (OWN, CTXT, FD, LD, CPC, CIC, etc)
	 */
	rdesc->desc0 = 0;
	rdesc->desc1 = 0;
	rdesc->desc2 = 0;
	rdesc->desc3 = 0;

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
पूर्ण

अटल व्योम xgbe_tx_desc_init(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_ring *ring = channel->tx_ring;
	काष्ठा xgbe_ring_data *rdata;
	पूर्णांक i;
	पूर्णांक start_index = ring->cur;

	DBGPR("-->tx_desc_init\n");

	/* Initialze all descriptors */
	क्रम (i = 0; i < ring->rdesc_count; i++) अणु
		rdata = XGBE_GET_DESC_DATA(ring, i);

		/* Initialize Tx descriptor */
		xgbe_tx_desc_reset(rdata);
	पूर्ण

	/* Update the total number of Tx descriptors */
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDRLR, ring->rdesc_count - 1);

	/* Update the starting address of descriptor ring */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDLR_HI,
			  upper_32_bits(rdata->rdesc_dma));
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDLR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	DBGPR("<--tx_desc_init\n");
पूर्ण

अटल व्योम xgbe_rx_desc_reset(काष्ठा xgbe_prv_data *pdata,
			       काष्ठा xgbe_ring_data *rdata, अचिन्हित पूर्णांक index)
अणु
	काष्ठा xgbe_ring_desc *rdesc = rdata->rdesc;
	अचिन्हित पूर्णांक rx_usecs = pdata->rx_usecs;
	अचिन्हित पूर्णांक rx_frames = pdata->rx_frames;
	अचिन्हित पूर्णांक पूर्णांकe;
	dma_addr_t hdr_dma, buf_dma;

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
	hdr_dma = rdata->rx.hdr.dma_base + rdata->rx.hdr.dma_off;
	buf_dma = rdata->rx.buf.dma_base + rdata->rx.buf.dma_off;
	rdesc->desc0 = cpu_to_le32(lower_32_bits(hdr_dma));
	rdesc->desc1 = cpu_to_le32(upper_32_bits(hdr_dma));
	rdesc->desc2 = cpu_to_le32(lower_32_bits(buf_dma));
	rdesc->desc3 = cpu_to_le32(upper_32_bits(buf_dma));

	XGMAC_SET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, INTE, पूर्णांकe);

	/* Since the Rx DMA engine is likely running, make sure everything
	 * is written to the descriptor(s) beक्रमe setting the OWN bit
	 * क्रम the descriptor
	 */
	dma_wmb();

	XGMAC_SET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, OWN, 1);

	/* Make sure ownership is written to the descriptor */
	dma_wmb();
पूर्ण

अटल व्योम xgbe_rx_desc_init(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_ring *ring = channel->rx_ring;
	काष्ठा xgbe_ring_data *rdata;
	अचिन्हित पूर्णांक start_index = ring->cur;
	अचिन्हित पूर्णांक i;

	DBGPR("-->rx_desc_init\n");

	/* Initialize all descriptors */
	क्रम (i = 0; i < ring->rdesc_count; i++) अणु
		rdata = XGBE_GET_DESC_DATA(ring, i);

		/* Initialize Rx descriptor */
		xgbe_rx_desc_reset(pdata, rdata, i);
	पूर्ण

	/* Update the total number of Rx descriptors */
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDRLR, ring->rdesc_count - 1);

	/* Update the starting address of descriptor ring */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDLR_HI,
			  upper_32_bits(rdata->rdesc_dma));
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDLR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	/* Update the Rx Descriptor Tail Poपूर्णांकer */
	rdata = XGBE_GET_DESC_DATA(ring, start_index + ring->rdesc_count - 1);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_RDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	DBGPR("<--rx_desc_init\n");
पूर्ण

अटल व्योम xgbe_update_tstamp_addend(काष्ठा xgbe_prv_data *pdata,
				      अचिन्हित पूर्णांक addend)
अणु
	अचिन्हित पूर्णांक count = 10000;

	/* Set the addend रेजिस्टर value and tell the device */
	XGMAC_IOWRITE(pdata, MAC_TSAR, addend);
	XGMAC_IOWRITE_BITS(pdata, MAC_TSCR, TSADDREG, 1);

	/* Wait क्रम addend update to complete */
	जबतक (--count && XGMAC_IOREAD_BITS(pdata, MAC_TSCR, TSADDREG))
		udelay(5);

	अगर (!count)
		netdev_err(pdata->netdev,
			   "timed out updating timestamp addend register\n");
पूर्ण

अटल व्योम xgbe_set_tstamp_समय(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक sec,
				 अचिन्हित पूर्णांक nsec)
अणु
	अचिन्हित पूर्णांक count = 10000;

	/* Set the समय values and tell the device */
	XGMAC_IOWRITE(pdata, MAC_STSUR, sec);
	XGMAC_IOWRITE(pdata, MAC_STNUR, nsec);
	XGMAC_IOWRITE_BITS(pdata, MAC_TSCR, TSINIT, 1);

	/* Wait क्रम समय update to complete */
	जबतक (--count && XGMAC_IOREAD_BITS(pdata, MAC_TSCR, TSINIT))
		udelay(5);

	अगर (!count)
		netdev_err(pdata->netdev, "timed out initializing timestamp\n");
पूर्ण

अटल u64 xgbe_get_tstamp_समय(काष्ठा xgbe_prv_data *pdata)
अणु
	u64 nsec;

	nsec = XGMAC_IOREAD(pdata, MAC_STSR);
	nsec *= NSEC_PER_SEC;
	nsec += XGMAC_IOREAD(pdata, MAC_STNR);

	वापस nsec;
पूर्ण

अटल u64 xgbe_get_tx_tstamp(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक tx_snr, tx_ssr;
	u64 nsec;

	अगर (pdata->vdata->tx_tstamp_workaround) अणु
		tx_snr = XGMAC_IOREAD(pdata, MAC_TXSNR);
		tx_ssr = XGMAC_IOREAD(pdata, MAC_TXSSR);
	पूर्ण अन्यथा अणु
		tx_ssr = XGMAC_IOREAD(pdata, MAC_TXSSR);
		tx_snr = XGMAC_IOREAD(pdata, MAC_TXSNR);
	पूर्ण

	अगर (XGMAC_GET_BITS(tx_snr, MAC_TXSNR, TXTSSTSMIS))
		वापस 0;

	nsec = tx_ssr;
	nsec *= NSEC_PER_SEC;
	nsec += tx_snr;

	वापस nsec;
पूर्ण

अटल व्योम xgbe_get_rx_tstamp(काष्ठा xgbe_packet_data *packet,
			       काष्ठा xgbe_ring_desc *rdesc)
अणु
	u64 nsec;

	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_CONTEXT_DESC3, TSA) &&
	    !XGMAC_GET_BITS_LE(rdesc->desc3, RX_CONTEXT_DESC3, TSD)) अणु
		nsec = le32_to_cpu(rdesc->desc1);
		nsec <<= 32;
		nsec |= le32_to_cpu(rdesc->desc0);
		अगर (nsec != 0xffffffffffffffffULL) अणु
			packet->rx_tstamp = nsec;
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       RX_TSTAMP, 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_config_tstamp(काष्ठा xgbe_prv_data *pdata,
			      अचिन्हित पूर्णांक mac_tscr)
अणु
	/* Set one nano-second accuracy */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSCTRLSSR, 1);

	/* Set fine बारtamp update */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TSCFUPDT, 1);

	/* Overग_लिखो earlier बारtamps */
	XGMAC_SET_BITS(mac_tscr, MAC_TSCR, TXTSSTSM, 1);

	XGMAC_IOWRITE(pdata, MAC_TSCR, mac_tscr);

	/* Exit अगर बारtamping is not enabled */
	अगर (!XGMAC_GET_BITS(mac_tscr, MAC_TSCR, TSENA))
		वापस 0;

	/* Initialize समय रेजिस्टरs */
	XGMAC_IOWRITE_BITS(pdata, MAC_SSIR, SSINC, XGBE_TSTAMP_SSINC);
	XGMAC_IOWRITE_BITS(pdata, MAC_SSIR, SNSINC, XGBE_TSTAMP_SNSINC);
	xgbe_update_tstamp_addend(pdata, pdata->tstamp_addend);
	xgbe_set_tstamp_समय(pdata, 0, 0);

	/* Initialize the समयcounter */
	समयcounter_init(&pdata->tstamp_tc, &pdata->tstamp_cc,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	वापस 0;
पूर्ण

अटल व्योम xgbe_tx_start_xmit(काष्ठा xgbe_channel *channel,
			       काष्ठा xgbe_ring *ring)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_ring_data *rdata;

	/* Make sure everything is written beक्रमe the रेजिस्टर ग_लिखो */
	wmb();

	/* Issue a poll command to Tx DMA by writing address
	 * of next immediate मुक्त descriptor */
	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	XGMAC_DMA_IOWRITE(channel, DMA_CH_TDTR_LO,
			  lower_32_bits(rdata->rdesc_dma));

	/* Start the Tx समयr */
	अगर (pdata->tx_usecs && !channel->tx_समयr_active) अणु
		channel->tx_समयr_active = 1;
		mod_समयr(&channel->tx_समयr,
			  jअगरfies + usecs_to_jअगरfies(pdata->tx_usecs));
	पूर्ण

	ring->tx.xmit_more = 0;
पूर्ण

अटल व्योम xgbe_dev_xmit(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_ring *ring = channel->tx_ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;
	काष्ठा xgbe_packet_data *packet = &ring->packet_data;
	अचिन्हित पूर्णांक tx_packets, tx_bytes;
	अचिन्हित पूर्णांक csum, tso, vlan, vxlan;
	अचिन्हित पूर्णांक tso_context, vlan_context;
	अचिन्हित पूर्णांक tx_set_ic;
	पूर्णांक start_index = ring->cur;
	पूर्णांक cur_index = ring->cur;
	पूर्णांक i;

	DBGPR("-->xgbe_dev_xmit\n");

	tx_packets = packet->tx_packets;
	tx_bytes = packet->tx_bytes;

	csum = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			      CSUM_ENABLE);
	tso = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			     TSO_ENABLE);
	vlan = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			      VLAN_CTAG);
	vxlan = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       VXLAN);

	अगर (tso && (packet->mss != ring->tx.cur_mss))
		tso_context = 1;
	अन्यथा
		tso_context = 0;

	अगर (vlan && (packet->vlan_ctag != ring->tx.cur_vlan_ctag))
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
	ring->coalesce_count += tx_packets;
	अगर (!pdata->tx_frames)
		tx_set_ic = 0;
	अन्यथा अगर (tx_packets > pdata->tx_frames)
		tx_set_ic = 1;
	अन्यथा अगर ((ring->coalesce_count % pdata->tx_frames) < tx_packets)
		tx_set_ic = 1;
	अन्यथा
		tx_set_ic = 0;

	rdata = XGBE_GET_DESC_DATA(ring, cur_index);
	rdesc = rdata->rdesc;

	/* Create a context descriptor अगर this is a TSO packet */
	अगर (tso_context || vlan_context) अणु
		अगर (tso_context) अणु
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "TSO context descriptor, mss=%u\n",
				  packet->mss);

			/* Set the MSS size */
			XGMAC_SET_BITS_LE(rdesc->desc2, TX_CONTEXT_DESC2,
					  MSS, packet->mss);

			/* Mark it as a CONTEXT descriptor */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  CTXT, 1);

			/* Indicate this descriptor contains the MSS */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  TCMSSV, 1);

			ring->tx.cur_mss = packet->mss;
		पूर्ण

		अगर (vlan_context) अणु
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "VLAN context descriptor, ctag=%u\n",
				  packet->vlan_ctag);

			/* Mark it as a CONTEXT descriptor */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  CTXT, 1);

			/* Set the VLAN tag */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  VT, packet->vlan_ctag);

			/* Indicate this descriptor contains the VLAN tag */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  VLTV, 1);

			ring->tx.cur_vlan_ctag = packet->vlan_ctag;
		पूर्ण

		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
		rdesc = rdata->rdesc;
	पूर्ण

	/* Update buffer address (क्रम TSO this is the header) */
	rdesc->desc0 =  cpu_to_le32(lower_32_bits(rdata->skb_dma));
	rdesc->desc1 =  cpu_to_le32(upper_32_bits(rdata->skb_dma));

	/* Update the buffer length */
	XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, HL_B1L,
			  rdata->skb_dma_len);

	/* VLAN tag insertion check */
	अगर (vlan)
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, VTIR,
				  TX_NORMAL_DESC2_VLAN_INSERT);

	/* Timestamp enablement check */
	अगर (XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES, PTP))
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, TTSE, 1);

	/* Mark it as First Descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, FD, 1);

	/* Mark it as a NORMAL descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CTXT, 0);

	/* Set OWN bit अगर not the first descriptor */
	अगर (cur_index != start_index)
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

	अगर (tso) अणु
		/* Enable TSO */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TSE, 1);
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TCPPL,
				  packet->tcp_payload_len);
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TCPHDRLEN,
				  packet->tcp_header_len / 4);

		pdata->ext_stats.tx_tso_packets += tx_packets;
	पूर्ण अन्यथा अणु
		/* Enable CRC and Pad Insertion */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CPC, 0);

		/* Enable HW CSUM */
		अगर (csum)
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3,
					  CIC, 0x3);

		/* Set the total length to be transmitted */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, FL,
				  packet->length);
	पूर्ण

	अगर (vxlan) अणु
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, VNP,
				  TX_NORMAL_DESC3_VXLAN_PACKET);

		pdata->ext_stats.tx_vxlan_packets += packet->tx_packets;
	पूर्ण

	क्रम (i = cur_index - start_index + 1; i < packet->rdesc_count; i++) अणु
		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
		rdesc = rdata->rdesc;

		/* Update buffer address */
		rdesc->desc0 = cpu_to_le32(lower_32_bits(rdata->skb_dma));
		rdesc->desc1 = cpu_to_le32(upper_32_bits(rdata->skb_dma));

		/* Update the buffer length */
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, HL_B1L,
				  rdata->skb_dma_len);

		/* Set OWN bit */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

		/* Mark it as NORMAL descriptor */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CTXT, 0);

		/* Enable HW CSUM */
		अगर (csum)
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3,
					  CIC, 0x3);
	पूर्ण

	/* Set LAST bit क्रम the last descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, LD, 1);

	/* Set IC bit based on Tx coalescing settings */
	अगर (tx_set_ic)
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, IC, 1);

	/* Save the Tx info to report back during cleanup */
	rdata->tx.packets = tx_packets;
	rdata->tx.bytes = tx_bytes;

	pdata->ext_stats.txq_packets[channel->queue_index] += tx_packets;
	pdata->ext_stats.txq_bytes[channel->queue_index] += tx_bytes;

	/* In हाल the Tx DMA engine is running, make sure everything
	 * is written to the descriptor(s) beक्रमe setting the OWN bit
	 * क्रम the first descriptor
	 */
	dma_wmb();

	/* Set OWN bit क्रम the first descriptor */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	rdesc = rdata->rdesc;
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

	अगर (netअगर_msg_tx_queued(pdata))
		xgbe_dump_tx_desc(pdata, ring, start_index,
				  packet->rdesc_count, 1);

	/* Make sure ownership is written to the descriptor */
	smp_wmb();

	ring->cur = cur_index + 1;
	अगर (!netdev_xmit_more() ||
	    netअगर_xmit_stopped(netdev_get_tx_queue(pdata->netdev,
						   channel->queue_index)))
		xgbe_tx_start_xmit(channel, ring);
	अन्यथा
		ring->tx.xmit_more = 1;

	DBGPR("  %s: descriptors %u to %u written\n",
	      channel->name, start_index & (ring->rdesc_count - 1),
	      (ring->cur - 1) & (ring->rdesc_count - 1));

	DBGPR("<--xgbe_dev_xmit\n");
पूर्ण

अटल पूर्णांक xgbe_dev_पढ़ो(काष्ठा xgbe_channel *channel)
अणु
	काष्ठा xgbe_prv_data *pdata = channel->pdata;
	काष्ठा xgbe_ring *ring = channel->rx_ring;
	काष्ठा xgbe_ring_data *rdata;
	काष्ठा xgbe_ring_desc *rdesc;
	काष्ठा xgbe_packet_data *packet = &ring->packet_data;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक err, etlt, l34t;

	DBGPR("-->xgbe_dev_read: cur = %d\n", ring->cur);

	rdata = XGBE_GET_DESC_DATA(ring, ring->cur);
	rdesc = rdata->rdesc;

	/* Check क्रम data availability */
	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, OWN))
		वापस 1;

	/* Make sure descriptor fields are पढ़ो after पढ़ोing the OWN bit */
	dma_rmb();

	अगर (netअगर_msg_rx_status(pdata))
		xgbe_dump_rx_desc(pdata, ring, ring->cur);

	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, CTXT)) अणु
		/* Timestamp Context Descriptor */
		xgbe_get_rx_tstamp(packet, rdesc);

		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       CONTEXT, 1);
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       CONTEXT_NEXT, 0);
		वापस 0;
	पूर्ण

	/* Normal Descriptor, be sure Context Descriptor bit is off */
	XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, CONTEXT, 0);

	/* Indicate अगर a Context Descriptor is next */
	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, CDA))
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       CONTEXT_NEXT, 1);

	/* Get the header length */
	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, FD)) अणु
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       FIRST, 1);
		rdata->rx.hdr_len = XGMAC_GET_BITS_LE(rdesc->desc2,
						      RX_NORMAL_DESC2, HL);
		अगर (rdata->rx.hdr_len)
			pdata->ext_stats.rx_split_header_packets++;
	पूर्ण अन्यथा अणु
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       FIRST, 0);
	पूर्ण

	/* Get the RSS hash */
	अगर (XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, RSV)) अणु
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       RSS_HASH, 1);

		packet->rss_hash = le32_to_cpu(rdesc->desc1);

		l34t = XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, L34T);
		चयन (l34t) अणु
		हाल RX_DESC3_L34T_IPV4_TCP:
		हाल RX_DESC3_L34T_IPV4_UDP:
		हाल RX_DESC3_L34T_IPV6_TCP:
		हाल RX_DESC3_L34T_IPV6_UDP:
			packet->rss_hash_type = PKT_HASH_TYPE_L4;
			अवरोध;
		शेष:
			packet->rss_hash_type = PKT_HASH_TYPE_L3;
		पूर्ण
	पूर्ण

	/* Not all the data has been transferred क्रम this packet */
	अगर (!XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, LD))
		वापस 0;

	/* This is the last of the data क्रम this packet */
	XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
		       LAST, 1);

	/* Get the packet length */
	rdata->rx.len = XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, PL);

	/* Set checksum करोne indicator as appropriate */
	अगर (netdev->features & NETIF_F_RXCSUM) अणु
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       CSUM_DONE, 1);
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       TNPCSUM_DONE, 1);
	पूर्ण

	/* Set the tunneled packet indicator */
	अगर (XGMAC_GET_BITS_LE(rdesc->desc2, RX_NORMAL_DESC2, TNP)) अणु
		XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
			       TNP, 1);
		pdata->ext_stats.rx_vxlan_packets++;

		l34t = XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, L34T);
		चयन (l34t) अणु
		हाल RX_DESC3_L34T_IPV4_UNKNOWN:
		हाल RX_DESC3_L34T_IPV6_UNKNOWN:
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       TNPCSUM_DONE, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check क्रम errors (only valid in last descriptor) */
	err = XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, ES);
	etlt = XGMAC_GET_BITS_LE(rdesc->desc3, RX_NORMAL_DESC3, ETLT);
	netअगर_dbg(pdata, rx_status, netdev, "err=%u, etlt=%#x\n", err, etlt);

	अगर (!err || !etlt) अणु
		/* No error अगर err is 0 or etlt is 0 */
		अगर ((etlt == 0x09) &&
		    (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)) अणु
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       VLAN_CTAG, 1);
			packet->vlan_ctag = XGMAC_GET_BITS_LE(rdesc->desc0,
							      RX_NORMAL_DESC0,
							      OVT);
			netअगर_dbg(pdata, rx_status, netdev, "vlan-ctag=%#06x\n",
				  packet->vlan_ctag);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक tnp = XGMAC_GET_BITS(packet->attributes,
						  RX_PACKET_ATTRIBUTES, TNP);

		अगर ((etlt == 0x05) || (etlt == 0x06)) अणु
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       CSUM_DONE, 0);
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       TNPCSUM_DONE, 0);
			pdata->ext_stats.rx_csum_errors++;
		पूर्ण अन्यथा अगर (tnp && ((etlt == 0x09) || (etlt == 0x0a))) अणु
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       CSUM_DONE, 0);
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       TNPCSUM_DONE, 0);
			pdata->ext_stats.rx_vxlan_csum_errors++;
		पूर्ण अन्यथा अणु
			XGMAC_SET_BITS(packet->errors, RX_PACKET_ERRORS,
				       FRAME, 1);
		पूर्ण
	पूर्ण

	pdata->ext_stats.rxq_packets[channel->queue_index]++;
	pdata->ext_stats.rxq_bytes[channel->queue_index] += rdata->rx.len;

	DBGPR("<--xgbe_dev_read: %s - descriptor=%u (cur=%d)\n", channel->name,
	      ring->cur & (ring->rdesc_count - 1), ring->cur);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_is_context_desc(काष्ठा xgbe_ring_desc *rdesc)
अणु
	/* Rx and Tx share CTXT bit, so check TDES3.CTXT bit */
	वापस XGMAC_GET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CTXT);
पूर्ण

अटल पूर्णांक xgbe_is_last_desc(काष्ठा xgbe_ring_desc *rdesc)
अणु
	/* Rx and Tx share LD bit, so check TDES3.LD bit */
	वापस XGMAC_GET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, LD);
पूर्ण

अटल पूर्णांक xgbe_enable_पूर्णांक(काष्ठा xgbe_channel *channel,
			   क्रमागत xgbe_पूर्णांक पूर्णांक_id)
अणु
	चयन (पूर्णांक_id) अणु
	हाल XGMAC_INT_DMA_CH_SR_TI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TIE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TPS:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TXSE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TBU:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TBUE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RIE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RBU:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RBUE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RPS:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RSE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TI_RI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TIE, 1);
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RIE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_FBE:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, FBEE, 1);
		अवरोध;
	हाल XGMAC_INT_DMA_ALL:
		channel->curr_ier |= channel->saved_ier;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	XGMAC_DMA_IOWRITE(channel, DMA_CH_IER, channel->curr_ier);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_disable_पूर्णांक(काष्ठा xgbe_channel *channel,
			    क्रमागत xgbe_पूर्णांक पूर्णांक_id)
अणु
	चयन (पूर्णांक_id) अणु
	हाल XGMAC_INT_DMA_CH_SR_TI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TIE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TPS:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TXSE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TBU:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TBUE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RIE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RBU:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RBUE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_RPS:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RSE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_TI_RI:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, TIE, 0);
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, RIE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_CH_SR_FBE:
		XGMAC_SET_BITS(channel->curr_ier, DMA_CH_IER, FBEE, 0);
		अवरोध;
	हाल XGMAC_INT_DMA_ALL:
		channel->saved_ier = channel->curr_ier;
		channel->curr_ier = 0;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	XGMAC_DMA_IOWRITE(channel, DMA_CH_IER, channel->curr_ier);

	वापस 0;
पूर्ण

अटल पूर्णांक __xgbe_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक count = 2000;

	DBGPR("-->xgbe_exit\n");

	/* Issue a software reset */
	XGMAC_IOWRITE_BITS(pdata, DMA_MR, SWR, 1);
	usleep_range(10, 15);

	/* Poll Until Poll Condition */
	जबतक (--count && XGMAC_IOREAD_BITS(pdata, DMA_MR, SWR))
		usleep_range(500, 600);

	अगर (!count)
		वापस -EBUSY;

	DBGPR("<--xgbe_exit\n");

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	/* To guard against possible incorrectly generated पूर्णांकerrupts,
	 * issue the software reset twice.
	 */
	ret = __xgbe_निकास(pdata);
	अगर (ret)
		वापस ret;

	वापस __xgbe_निकास(pdata);
पूर्ण

अटल पूर्णांक xgbe_flush_tx_queues(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i, count;

	अगर (XGMAC_GET_BITS(pdata->hw_feat.version, MAC_VR, SNPSVER) < 0x21)
		वापस 0;

	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, FTQ, 1);

	/* Poll Until Poll Condition */
	क्रम (i = 0; i < pdata->tx_q_count; i++) अणु
		count = 2000;
		जबतक (--count && XGMAC_MTL_IOREAD_BITS(pdata, i,
							MTL_Q_TQOMR, FTQ))
			usleep_range(500, 600);

		अगर (!count)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgbe_config_dma_bus(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक sbmr;

	sbmr = XGMAC_IOREAD(pdata, DMA_SBMR);

	/* Set enhanced addressing mode */
	XGMAC_SET_BITS(sbmr, DMA_SBMR, EAME, 1);

	/* Set the System Bus mode */
	XGMAC_SET_BITS(sbmr, DMA_SBMR, UNDEF, 1);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, BLEN, pdata->blen >> 2);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, AAL, pdata->aal);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, RD_OSR_LMT, pdata->rd_osr_limit - 1);
	XGMAC_SET_BITS(sbmr, DMA_SBMR, WR_OSR_LMT, pdata->wr_osr_limit - 1);

	XGMAC_IOWRITE(pdata, DMA_SBMR, sbmr);

	/* Set descriptor fetching threshold */
	अगर (pdata->vdata->tx_desc_prefetch)
		XGMAC_IOWRITE_BITS(pdata, DMA_TXEDMACR, TDPS,
				   pdata->vdata->tx_desc_prefetch);

	अगर (pdata->vdata->rx_desc_prefetch)
		XGMAC_IOWRITE_BITS(pdata, DMA_RXEDMACR, RDPS,
				   pdata->vdata->rx_desc_prefetch);
पूर्ण

अटल व्योम xgbe_config_dma_cache(काष्ठा xgbe_prv_data *pdata)
अणु
	XGMAC_IOWRITE(pdata, DMA_AXIARCR, pdata->arcr);
	XGMAC_IOWRITE(pdata, DMA_AXIAWCR, pdata->awcr);
	अगर (pdata->awarcr)
		XGMAC_IOWRITE(pdata, DMA_AXIAWARCR, pdata->awarcr);
पूर्ण

अटल व्योम xgbe_config_mtl_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Set Tx to weighted round robin scheduling algorithm */
	XGMAC_IOWRITE_BITS(pdata, MTL_OMR, ETSALG, MTL_ETSALG_WRR);

	/* Set Tx traffic classes to use WRR algorithm with equal weights */
	क्रम (i = 0; i < pdata->hw_feat.tc_cnt; i++) अणु
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_TC_ETSCR, TSA,
				       MTL_TSA_ETS);
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_TC_QWR, QW, 1);
	पूर्ण

	/* Set Rx to strict priority algorithm */
	XGMAC_IOWRITE_BITS(pdata, MTL_OMR, RAA, MTL_RAA_SP);
पूर्ण

अटल व्योम xgbe_queue_flow_control_threshold(काष्ठा xgbe_prv_data *pdata,
					      अचिन्हित पूर्णांक queue,
					      अचिन्हित पूर्णांक q_fअगरo_size)
अणु
	अचिन्हित पूर्णांक frame_fअगरo_size;
	अचिन्हित पूर्णांक rfa, rfd;

	frame_fअगरo_size = XGMAC_FLOW_CONTROL_ALIGN(xgbe_get_max_frame(pdata));

	अगर (pdata->pfcq[queue] && (q_fअगरo_size > pdata->pfc_rfa)) अणु
		/* PFC is active क्रम this queue */
		rfa = pdata->pfc_rfa;
		rfd = rfa + frame_fअगरo_size;
		अगर (rfd > XGMAC_FLOW_CONTROL_MAX)
			rfd = XGMAC_FLOW_CONTROL_MAX;
		अगर (rfa >= XGMAC_FLOW_CONTROL_MAX)
			rfa = XGMAC_FLOW_CONTROL_MAX - XGMAC_FLOW_CONTROL_UNIT;
	पूर्ण अन्यथा अणु
		/* This path deals with just maximum frame sizes which are
		 * limited to a jumbo frame of 9,000 (plus headers, etc.)
		 * so we can never exceed the maximum allowable RFA/RFD
		 * values.
		 */
		अगर (q_fअगरo_size <= 2048) अणु
			/* rx_rfd to zero to संकेत no flow control */
			pdata->rx_rfa[queue] = 0;
			pdata->rx_rfd[queue] = 0;
			वापस;
		पूर्ण

		अगर (q_fअगरo_size <= 4096) अणु
			/* Between 2048 and 4096 */
			pdata->rx_rfa[queue] = 0;	/* Full - 1024 bytes */
			pdata->rx_rfd[queue] = 1;	/* Full - 1536 bytes */
			वापस;
		पूर्ण

		अगर (q_fअगरo_size <= frame_fअगरo_size) अणु
			/* Between 4096 and max-frame */
			pdata->rx_rfa[queue] = 2;	/* Full - 2048 bytes */
			pdata->rx_rfd[queue] = 5;	/* Full - 3584 bytes */
			वापस;
		पूर्ण

		अगर (q_fअगरo_size <= (frame_fअगरo_size * 3)) अणु
			/* Between max-frame and 3 max-frames,
			 * trigger अगर we get just over a frame of data and
			 * resume when we have just under half a frame left.
			 */
			rfa = q_fअगरo_size - frame_fअगरo_size;
			rfd = rfa + (frame_fअगरo_size / 2);
		पूर्ण अन्यथा अणु
			/* Above 3 max-frames - trigger when just over
			 * 2 frames of space available
			 */
			rfa = frame_fअगरo_size * 2;
			rfa += XGMAC_FLOW_CONTROL_UNIT;
			rfd = rfa + frame_fअगरo_size;
		पूर्ण
	पूर्ण

	pdata->rx_rfa[queue] = XGMAC_FLOW_CONTROL_VALUE(rfa);
	pdata->rx_rfd[queue] = XGMAC_FLOW_CONTROL_VALUE(rfd);
पूर्ण

अटल व्योम xgbe_calculate_flow_control_threshold(काष्ठा xgbe_prv_data *pdata,
						  अचिन्हित पूर्णांक *fअगरo)
अणु
	अचिन्हित पूर्णांक q_fअगरo_size;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		q_fअगरo_size = (fअगरo[i] + 1) * XGMAC_FIFO_UNIT;

		xgbe_queue_flow_control_threshold(pdata, i, q_fअगरo_size);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_flow_control_threshold(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pdata->rx_q_count; i++) अणु
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQFCR, RFA,
				       pdata->rx_rfa[i]);
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQFCR, RFD,
				       pdata->rx_rfd[i]);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_get_tx_fअगरo_size(काष्ठा xgbe_prv_data *pdata)
अणु
	/* The configured value may not be the actual amount of fअगरo RAM */
	वापस min_t(अचिन्हित पूर्णांक, pdata->tx_max_fअगरo_size,
		     pdata->hw_feat.tx_fअगरo_size);
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_get_rx_fअगरo_size(काष्ठा xgbe_prv_data *pdata)
अणु
	/* The configured value may not be the actual amount of fअगरo RAM */
	वापस min_t(अचिन्हित पूर्णांक, pdata->rx_max_fअगरo_size,
		     pdata->hw_feat.rx_fअगरo_size);
पूर्ण

अटल व्योम xgbe_calculate_equal_fअगरo(अचिन्हित पूर्णांक fअगरo_size,
				      अचिन्हित पूर्णांक queue_count,
				      अचिन्हित पूर्णांक *fअगरo)
अणु
	अचिन्हित पूर्णांक q_fअगरo_size;
	अचिन्हित पूर्णांक p_fअगरo;
	अचिन्हित पूर्णांक i;

	q_fअगरo_size = fअगरo_size / queue_count;

	/* Calculate the fअगरo setting by भागiding the queue's fअगरo size
	 * by the fअगरo allocation increment (with 0 representing the
	 * base allocation increment so decrement the result by 1).
	 */
	p_fअगरo = q_fअगरo_size / XGMAC_FIFO_UNIT;
	अगर (p_fअगरo)
		p_fअगरo--;

	/* Distribute the fअगरo equally amongst the queues */
	क्रम (i = 0; i < queue_count; i++)
		fअगरo[i] = p_fअगरo;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_set_nonprio_fअगरos(अचिन्हित पूर्णांक fअगरo_size,
					   अचिन्हित पूर्णांक queue_count,
					   अचिन्हित पूर्णांक *fअगरo)
अणु
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON_NOT_POWER_OF_2(XGMAC_FIFO_MIN_ALLOC);

	अगर (queue_count <= IEEE_8021QAZ_MAX_TCS)
		वापस fअगरo_size;

	/* Rx queues 9 and up are क्रम specialized packets,
	 * such as PTP or DCB control packets, etc. and
	 * करोn't require a large fअगरo
	 */
	क्रम (i = IEEE_8021QAZ_MAX_TCS; i < queue_count; i++) अणु
		fअगरo[i] = (XGMAC_FIFO_MIN_ALLOC / XGMAC_FIFO_UNIT) - 1;
		fअगरo_size -= XGMAC_FIFO_MIN_ALLOC;
	पूर्ण

	वापस fअगरo_size;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_get_pfc_delay(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक delay;

	/* If a delay has been provided, use that */
	अगर (pdata->pfc->delay)
		वापस pdata->pfc->delay / 8;

	/* Allow क्रम two maximum size frames */
	delay = xgbe_get_max_frame(pdata);
	delay += XGMAC_ETH_PREAMBLE;
	delay *= 2;

	/* Allow क्रम PFC frame */
	delay += XGMAC_PFC_DATA_LEN;
	delay += ETH_HLEN + ETH_FCS_LEN;
	delay += XGMAC_ETH_PREAMBLE;

	/* Allow क्रम miscellaneous delays (LPI निकास, cable, etc.) */
	delay += XGMAC_PFC_DELAYS;

	वापस delay;
पूर्ण

अटल अचिन्हित पूर्णांक xgbe_get_pfc_queues(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक count, prio_queues;
	अचिन्हित पूर्णांक i;

	अगर (!pdata->pfc->pfc_en)
		वापस 0;

	count = 0;
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);
	क्रम (i = 0; i < prio_queues; i++) अणु
		अगर (!xgbe_is_pfc_queue(pdata, i))
			जारी;

		pdata->pfcq[i] = 1;
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम xgbe_calculate_dcb_fअगरo(काष्ठा xgbe_prv_data *pdata,
				    अचिन्हित पूर्णांक fअगरo_size,
				    अचिन्हित पूर्णांक *fअगरo)
अणु
	अचिन्हित पूर्णांक q_fअगरo_size, rem_fअगरo, addn_fअगरo;
	अचिन्हित पूर्णांक prio_queues;
	अचिन्हित पूर्णांक pfc_count;
	अचिन्हित पूर्णांक i;

	q_fअगरo_size = XGMAC_FIFO_ALIGN(xgbe_get_max_frame(pdata));
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);
	pfc_count = xgbe_get_pfc_queues(pdata);

	अगर (!pfc_count || ((q_fअगरo_size * prio_queues) > fअगरo_size)) अणु
		/* No traffic classes with PFC enabled or can't करो lossless */
		xgbe_calculate_equal_fअगरo(fअगरo_size, prio_queues, fअगरo);
		वापस;
	पूर्ण

	/* Calculate how much fअगरo we have to play with */
	rem_fअगरo = fअगरo_size - (q_fअगरo_size * prio_queues);

	/* Calculate how much more than base fअगरo PFC needs, which also
	 * becomes the threshold activation poपूर्णांक (RFA)
	 */
	pdata->pfc_rfa = xgbe_get_pfc_delay(pdata);
	pdata->pfc_rfa = XGMAC_FLOW_CONTROL_ALIGN(pdata->pfc_rfa);

	अगर (pdata->pfc_rfa > q_fअगरo_size) अणु
		addn_fअगरo = pdata->pfc_rfa - q_fअगरo_size;
		addn_fअगरo = XGMAC_FIFO_ALIGN(addn_fअगरo);
	पूर्ण अन्यथा अणु
		addn_fअगरo = 0;
	पूर्ण

	/* Calculate DCB fअगरo settings:
	 *   - distribute reमुख्यing fअगरo between the VLAN priority
	 *     queues based on traffic class PFC enablement and overall
	 *     priority (0 is lowest priority, so start at highest)
	 */
	i = prio_queues;
	जबतक (i > 0) अणु
		i--;

		fअगरo[i] = (q_fअगरo_size / XGMAC_FIFO_UNIT) - 1;

		अगर (!pdata->pfcq[i] || !addn_fअगरo)
			जारी;

		अगर (addn_fअगरo > rem_fअगरo) अणु
			netdev_warn(pdata->netdev,
				    "RXq%u cannot set needed fifo size\n", i);
			अगर (!rem_fअगरo)
				जारी;

			addn_fअगरo = rem_fअगरo;
		पूर्ण

		fअगरo[i] += (addn_fअगरo / XGMAC_FIFO_UNIT);
		rem_fअगरo -= addn_fअगरo;
	पूर्ण

	अगर (rem_fअगरo) अणु
		अचिन्हित पूर्णांक inc_fअगरo = rem_fअगरo / prio_queues;

		/* Distribute reमुख्यing fअगरo across queues */
		क्रम (i = 0; i < prio_queues; i++)
			fअगरo[i] += (inc_fअगरo / XGMAC_FIFO_UNIT);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_tx_fअगरo_size(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक fअगरo[XGBE_MAX_QUEUES];
	अचिन्हित पूर्णांक i;

	fअगरo_size = xgbe_get_tx_fअगरo_size(pdata);

	xgbe_calculate_equal_fअगरo(fअगरo_size, pdata->tx_q_count, fअगरo);

	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TQS, fअगरo[i]);

	netअगर_info(pdata, drv, pdata->netdev,
		   "%d Tx hardware queues, %d byte fifo per queue\n",
		   pdata->tx_q_count, ((fअगरo[0] + 1) * XGMAC_FIFO_UNIT));
पूर्ण

अटल व्योम xgbe_config_rx_fअगरo_size(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक fअगरo_size;
	अचिन्हित पूर्णांक fअगरo[XGBE_MAX_QUEUES];
	अचिन्हित पूर्णांक prio_queues;
	अचिन्हित पूर्णांक i;

	/* Clear any DCB related fअगरo/queue inक्रमmation */
	स_रखो(pdata->pfcq, 0, माप(pdata->pfcq));
	pdata->pfc_rfa = 0;

	fअगरo_size = xgbe_get_rx_fअगरo_size(pdata);
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);

	/* Assign a minimum fअगरo to the non-VLAN priority queues */
	fअगरo_size = xgbe_set_nonprio_fअगरos(fअगरo_size, pdata->rx_q_count, fअगरo);

	अगर (pdata->pfc && pdata->ets)
		xgbe_calculate_dcb_fअगरo(pdata, fअगरo_size, fअगरo);
	अन्यथा
		xgbe_calculate_equal_fअगरo(fअगरo_size, prio_queues, fअगरo);

	क्रम (i = 0; i < pdata->rx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_RQOMR, RQS, fअगरo[i]);

	xgbe_calculate_flow_control_threshold(pdata, fअगरo);
	xgbe_config_flow_control_threshold(pdata);

	अगर (pdata->pfc && pdata->ets && pdata->pfc->pfc_en) अणु
		netअगर_info(pdata, drv, pdata->netdev,
			   "%u Rx hardware queues\n", pdata->rx_q_count);
		क्रम (i = 0; i < pdata->rx_q_count; i++)
			netअगर_info(pdata, drv, pdata->netdev,
				   "RxQ%u, %u byte fifo queue\n", i,
				   ((fअगरo[i] + 1) * XGMAC_FIFO_UNIT));
	पूर्ण अन्यथा अणु
		netअगर_info(pdata, drv, pdata->netdev,
			   "%u Rx hardware queues, %u byte fifo per queue\n",
			   pdata->rx_q_count,
			   ((fअगरo[0] + 1) * XGMAC_FIFO_UNIT));
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_queue_mapping(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक qptc, qptc_extra, queue;
	अचिन्हित पूर्णांक prio_queues;
	अचिन्हित पूर्णांक ppq, ppq_extra, prio;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक i, j, reg, reg_val;

	/* Map the MTL Tx Queues to Traffic Classes
	 *   Note: Tx Queues >= Traffic Classes
	 */
	qptc = pdata->tx_q_count / pdata->hw_feat.tc_cnt;
	qptc_extra = pdata->tx_q_count % pdata->hw_feat.tc_cnt;

	क्रम (i = 0, queue = 0; i < pdata->hw_feat.tc_cnt; i++) अणु
		क्रम (j = 0; j < qptc; j++) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TXq%u mapped to TC%u\n", queue, i);
			XGMAC_MTL_IOWRITE_BITS(pdata, queue, MTL_Q_TQOMR,
					       Q2TCMAP, i);
			pdata->q2tc_map[queue++] = i;
		पूर्ण

		अगर (i < qptc_extra) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TXq%u mapped to TC%u\n", queue, i);
			XGMAC_MTL_IOWRITE_BITS(pdata, queue, MTL_Q_TQOMR,
					       Q2TCMAP, i);
			pdata->q2tc_map[queue++] = i;
		पूर्ण
	पूर्ण

	/* Map the 8 VLAN priority values to available MTL Rx queues */
	prio_queues = XGMAC_PRIO_QUEUES(pdata->rx_q_count);
	ppq = IEEE_8021QAZ_MAX_TCS / prio_queues;
	ppq_extra = IEEE_8021QAZ_MAX_TCS % prio_queues;

	reg = MAC_RQC2R;
	reg_val = 0;
	क्रम (i = 0, prio = 0; i < prio_queues;) अणु
		mask = 0;
		क्रम (j = 0; j < ppq; j++) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "PRIO%u mapped to RXq%u\n", prio, i);
			mask |= (1 << prio);
			pdata->prio2q_map[prio++] = i;
		पूर्ण

		अगर (i < ppq_extra) अणु
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "PRIO%u mapped to RXq%u\n", prio, i);
			mask |= (1 << prio);
			pdata->prio2q_map[prio++] = i;
		पूर्ण

		reg_val |= (mask << ((i++ % MAC_RQC2_Q_PER_REG) << 3));

		अगर ((i % MAC_RQC2_Q_PER_REG) && (i != prio_queues))
			जारी;

		XGMAC_IOWRITE(pdata, reg, reg_val);
		reg += MAC_RQC2_INC;
		reg_val = 0;
	पूर्ण

	/* Select dynamic mapping of MTL Rx queue to DMA Rx channel */
	reg = MTL_RQDCM0R;
	reg_val = 0;
	क्रम (i = 0; i < pdata->rx_q_count;) अणु
		reg_val |= (0x80 << ((i++ % MTL_RQDCM_Q_PER_REG) << 3));

		अगर ((i % MTL_RQDCM_Q_PER_REG) && (i != pdata->rx_q_count))
			जारी;

		XGMAC_IOWRITE(pdata, reg, reg_val);

		reg += MTL_RQDCM_INC;
		reg_val = 0;
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_tc(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक offset, queue, prio;
	u8 i;

	netdev_reset_tc(pdata->netdev);
	अगर (!pdata->num_tcs)
		वापस;

	netdev_set_num_tc(pdata->netdev, pdata->num_tcs);

	क्रम (i = 0, queue = 0, offset = 0; i < pdata->num_tcs; i++) अणु
		जबतक ((queue < pdata->tx_q_count) &&
		       (pdata->q2tc_map[queue] == i))
			queue++;

		netअगर_dbg(pdata, drv, pdata->netdev, "TC%u using TXq%u-%u\n",
			  i, offset, queue - 1);
		netdev_set_tc_queue(pdata->netdev, i, queue - offset, offset);
		offset = queue;
	पूर्ण

	अगर (!pdata->ets)
		वापस;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		netdev_set_prio_tc_map(pdata->netdev, prio,
				       pdata->ets->prio_tc[prio]);
पूर्ण

अटल व्योम xgbe_config_dcb_tc(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ieee_ets *ets = pdata->ets;
	अचिन्हित पूर्णांक total_weight, min_weight, weight;
	अचिन्हित पूर्णांक mask, reg, reg_val;
	अचिन्हित पूर्णांक i, prio;

	अगर (!ets)
		वापस;

	/* Set Tx to deficit weighted round robin scheduling algorithm (when
	 * traffic class is using ETS algorithm)
	 */
	XGMAC_IOWRITE_BITS(pdata, MTL_OMR, ETSALG, MTL_ETSALG_DWRR);

	/* Set Traffic Class algorithms */
	total_weight = pdata->netdev->mtu * pdata->hw_feat.tc_cnt;
	min_weight = total_weight / 100;
	अगर (!min_weight)
		min_weight = 1;

	क्रम (i = 0; i < pdata->hw_feat.tc_cnt; i++) अणु
		/* Map the priorities to the traffic class */
		mask = 0;
		क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++) अणु
			अगर (ets->prio_tc[prio] == i)
				mask |= (1 << prio);
		पूर्ण
		mask &= 0xff;

		netअगर_dbg(pdata, drv, pdata->netdev, "TC%u PRIO mask=%#x\n",
			  i, mask);
		reg = MTL_TCPM0R + (MTL_TCPM_INC * (i / MTL_TCPM_TC_PER_REG));
		reg_val = XGMAC_IOREAD(pdata, reg);

		reg_val &= ~(0xff << ((i % MTL_TCPM_TC_PER_REG) << 3));
		reg_val |= (mask << ((i % MTL_TCPM_TC_PER_REG) << 3));

		XGMAC_IOWRITE(pdata, reg, reg_val);

		/* Set the traffic class algorithm */
		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TC%u using SP\n", i);
			XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_TC_ETSCR, TSA,
					       MTL_TSA_SP);
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			weight = total_weight * ets->tc_tx_bw[i] / 100;
			weight = clamp(weight, min_weight, total_weight);

			netअगर_dbg(pdata, drv, pdata->netdev,
				  "TC%u using DWRR (weight %u)\n", i, weight);
			XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_TC_ETSCR, TSA,
					       MTL_TSA_ETS);
			XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_TC_QWR, QW,
					       weight);
			अवरोध;
		पूर्ण
	पूर्ण

	xgbe_config_tc(pdata);
पूर्ण

अटल व्योम xgbe_config_dcb_pfc(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!test_bit(XGBE_DOWN, &pdata->dev_state)) अणु
		/* Just stop the Tx queues जबतक Rx fअगरo is changed */
		netअगर_tx_stop_all_queues(pdata->netdev);

		/* Suspend Rx so that fअगरo's can be adjusted */
		pdata->hw_अगर.disable_rx(pdata);
	पूर्ण

	xgbe_config_rx_fअगरo_size(pdata);
	xgbe_config_flow_control(pdata);

	अगर (!test_bit(XGBE_DOWN, &pdata->dev_state)) अणु
		/* Resume Rx */
		pdata->hw_अगर.enable_rx(pdata);

		/* Resume Tx queues */
		netअगर_tx_start_all_queues(pdata->netdev);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_mac_address(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_set_mac_address(pdata, pdata->netdev->dev_addr);

	/* Filtering is करोne using perfect filtering and hash filtering */
	अगर (pdata->hw_feat.hash_table_size) अणु
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 1);
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 1);
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HMC, 1);
	पूर्ण
पूर्ण

अटल व्योम xgbe_config_jumbo_enable(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक val;

	val = (pdata->netdev->mtu > XGMAC_STD_PACKET_MTU) ? 1 : 0;

	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, JE, val);
पूर्ण

अटल व्योम xgbe_config_mac_speed(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_set_speed(pdata, pdata->phy_speed);
पूर्ण

अटल व्योम xgbe_config_checksum_offload(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->netdev->features & NETIF_F_RXCSUM)
		xgbe_enable_rx_csum(pdata);
	अन्यथा
		xgbe_disable_rx_csum(pdata);
पूर्ण

अटल व्योम xgbe_config_vlan_support(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Indicate that VLAN Tx CTAGs come from context descriptors */
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANIR, CSVL, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_VLANIR, VLTI, 1);

	/* Set the current VLAN Hash Table रेजिस्टर value */
	xgbe_update_vlan_hash_table(pdata);

	अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		xgbe_enable_rx_vlan_filtering(pdata);
	अन्यथा
		xgbe_disable_rx_vlan_filtering(pdata);

	अगर (pdata->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		xgbe_enable_rx_vlan_stripping(pdata);
	अन्यथा
		xgbe_disable_rx_vlan_stripping(pdata);
पूर्ण

अटल u64 xgbe_mmc_पढ़ो(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक reg_lo)
अणु
	bool पढ़ो_hi;
	u64 val;

	अगर (pdata->vdata->mmc_64bit) अणु
		चयन (reg_lo) अणु
		/* These रेजिस्टरs are always 32 bit */
		हाल MMC_RXRUNTERROR:
		हाल MMC_RXJABBERERROR:
		हाल MMC_RXUNDERSIZE_G:
		हाल MMC_RXOVERSIZE_G:
		हाल MMC_RXWATCHDOGERROR:
			पढ़ो_hi = false;
			अवरोध;

		शेष:
			पढ़ो_hi = true;
		पूर्ण
	पूर्ण अन्यथा अणु
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
	पूर्ण

	val = XGMAC_IOREAD(pdata, reg_lo);

	अगर (पढ़ो_hi)
		val |= ((u64)XGMAC_IOREAD(pdata, reg_lo + 4) << 32);

	वापस val;
पूर्ण

अटल व्योम xgbe_tx_mmc_पूर्णांक(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_mmc_stats *stats = &pdata->mmc_stats;
	अचिन्हित पूर्णांक mmc_isr = XGMAC_IOREAD(pdata, MMC_TISR);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXOCTETCOUNT_GB))
		stats->txoctetcount_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXFRAMECOUNT_GB))
		stats->txframecount_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXBROADCASTFRAMES_G))
		stats->txbroadcastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXMULTICASTFRAMES_G))
		stats->txmulticastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX64OCTETS_GB))
		stats->tx64octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX64OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX65TO127OCTETS_GB))
		stats->tx65to127octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX65TO127OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX128TO255OCTETS_GB))
		stats->tx128to255octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX128TO255OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX256TO511OCTETS_GB))
		stats->tx256to511octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX256TO511OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX512TO1023OCTETS_GB))
		stats->tx512to1023octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TX1024TOMAXOCTETS_GB))
		stats->tx1024tomaxoctets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXUNICASTFRAMES_GB))
		stats->txunicastframes_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXMULTICASTFRAMES_GB))
		stats->txmulticastframes_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXBROADCASTFRAMES_GB))
		stats->txbroadcastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXUNDERFLOWERROR))
		stats->txunderflowerror +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXUNDERFLOWERROR_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXOCTETCOUNT_G))
		stats->txoctetcount_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXFRAMECOUNT_G))
		stats->txframecount_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXPAUSEFRAMES))
		stats->txछोड़ोframes +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXPAUSEFRAMES_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_TISR, TXVLANFRAMES_G))
		stats->txvlanframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_TXVLANFRAMES_G_LO);
पूर्ण

अटल व्योम xgbe_rx_mmc_पूर्णांक(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_mmc_stats *stats = &pdata->mmc_stats;
	अचिन्हित पूर्णांक mmc_isr = XGMAC_IOREAD(pdata, MMC_RISR);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXFRAMECOUNT_GB))
		stats->rxframecount_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXFRAMECOUNT_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXOCTETCOUNT_GB))
		stats->rxoctetcount_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXOCTETCOUNT_G))
		stats->rxoctetcount_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXBROADCASTFRAMES_G))
		stats->rxbroadcastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXMULTICASTFRAMES_G))
		stats->rxmulticastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXCRCERROR))
		stats->rxcrcerror +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXCRCERROR_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXRUNTERROR))
		stats->rxrunterror +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXRUNTERROR);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXJABBERERROR))
		stats->rxjabbererror +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXJABBERERROR);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXUNDERSIZE_G))
		stats->rxundersize_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXUNDERSIZE_G);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXOVERSIZE_G))
		stats->rxoversize_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXOVERSIZE_G);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX64OCTETS_GB))
		stats->rx64octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX64OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX65TO127OCTETS_GB))
		stats->rx65to127octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX65TO127OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX128TO255OCTETS_GB))
		stats->rx128to255octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX128TO255OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX256TO511OCTETS_GB))
		stats->rx256to511octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX256TO511OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX512TO1023OCTETS_GB))
		stats->rx512to1023octets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RX1024TOMAXOCTETS_GB))
		stats->rx1024tomaxoctets_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXUNICASTFRAMES_G))
		stats->rxunicastframes_g +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXUNICASTFRAMES_G_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXLENGTHERROR))
		stats->rxlengtherror +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXLENGTHERROR_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXOUTOFRANGETYPE))
		stats->rxoutofrangetype +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXOUTOFRANGETYPE_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXPAUSEFRAMES))
		stats->rxछोड़ोframes +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXPAUSEFRAMES_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXFIFOOVERFLOW))
		stats->rxfअगरooverflow +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXFIFOOVERFLOW_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXVLANFRAMES_GB))
		stats->rxvlanframes_gb +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXVLANFRAMES_GB_LO);

	अगर (XGMAC_GET_BITS(mmc_isr, MMC_RISR, RXWATCHDOGERROR))
		stats->rxwatchकरोgerror +=
			xgbe_mmc_पढ़ो(pdata, MMC_RXWATCHDOGERROR);
पूर्ण

अटल व्योम xgbe_पढ़ो_mmc_stats(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_mmc_stats *stats = &pdata->mmc_stats;

	/* Freeze counters */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 1);

	stats->txoctetcount_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_GB_LO);

	stats->txframecount_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_GB_LO);

	stats->txbroadcastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	stats->txmulticastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	stats->tx64octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX64OCTETS_GB_LO);

	stats->tx65to127octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX65TO127OCTETS_GB_LO);

	stats->tx128to255octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX128TO255OCTETS_GB_LO);

	stats->tx256to511octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX256TO511OCTETS_GB_LO);

	stats->tx512to1023octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	stats->tx1024tomaxoctets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	stats->txunicastframes_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	stats->txmulticastframes_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	stats->txbroadcastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	stats->txunderflowerror +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXUNDERFLOWERROR_LO);

	stats->txoctetcount_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXOCTETCOUNT_G_LO);

	stats->txframecount_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXFRAMECOUNT_G_LO);

	stats->txछोड़ोframes +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXPAUSEFRAMES_LO);

	stats->txvlanframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_TXVLANFRAMES_G_LO);

	stats->rxframecount_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXFRAMECOUNT_GB_LO);

	stats->rxoctetcount_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_GB_LO);

	stats->rxoctetcount_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXOCTETCOUNT_G_LO);

	stats->rxbroadcastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	stats->rxmulticastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	stats->rxcrcerror +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXCRCERROR_LO);

	stats->rxrunterror +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXRUNTERROR);

	stats->rxjabbererror +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXJABBERERROR);

	stats->rxundersize_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXUNDERSIZE_G);

	stats->rxoversize_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXOVERSIZE_G);

	stats->rx64octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX64OCTETS_GB_LO);

	stats->rx65to127octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX65TO127OCTETS_GB_LO);

	stats->rx128to255octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX128TO255OCTETS_GB_LO);

	stats->rx256to511octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX256TO511OCTETS_GB_LO);

	stats->rx512to1023octets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	stats->rx1024tomaxoctets_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	stats->rxunicastframes_g +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXUNICASTFRAMES_G_LO);

	stats->rxlengtherror +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXLENGTHERROR_LO);

	stats->rxoutofrangetype +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXOUTOFRANGETYPE_LO);

	stats->rxछोड़ोframes +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXPAUSEFRAMES_LO);

	stats->rxfअगरooverflow +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXFIFOOVERFLOW_LO);

	stats->rxvlanframes_gb +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXVLANFRAMES_GB_LO);

	stats->rxwatchकरोgerror +=
		xgbe_mmc_पढ़ो(pdata, MMC_RXWATCHDOGERROR);

	/* Un-मुक्तze counters */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 0);
पूर्ण

अटल व्योम xgbe_config_mmc(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set counters to reset on पढ़ो */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, ROR, 1);

	/* Reset the counters */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, CR, 1);
पूर्ण

अटल व्योम xgbe_txq_prepare_tx_stop(काष्ठा xgbe_prv_data *pdata,
				     अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक tx_status;
	अचिन्हित दीर्घ tx_समयout;

	/* The Tx engine cannot be stopped अगर it is actively processing
	 * packets. Wait क्रम the Tx queue to empty the Tx fअगरo.  Don't
	 * रुको क्रमever though...
	 */
	tx_समयout = jअगरfies + (XGBE_DMA_STOP_TIMEOUT * HZ);
	जबतक (समय_beक्रमe(jअगरfies, tx_समयout)) अणु
		tx_status = XGMAC_MTL_IOREAD(pdata, queue, MTL_Q_TQDR);
		अगर ((XGMAC_GET_BITS(tx_status, MTL_Q_TQDR, TRCSTS) != 1) &&
		    (XGMAC_GET_BITS(tx_status, MTL_Q_TQDR, TXQSTS) == 0))
			अवरोध;

		usleep_range(500, 1000);
	पूर्ण

	अगर (!समय_beक्रमe(jअगरfies, tx_समयout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Tx queue %u to empty\n",
			    queue);
पूर्ण

अटल व्योम xgbe_prepare_tx_stop(काष्ठा xgbe_prv_data *pdata,
				 अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक tx_dsr, tx_pos, tx_qidx;
	अचिन्हित पूर्णांक tx_status;
	अचिन्हित दीर्घ tx_समयout;

	अगर (XGMAC_GET_BITS(pdata->hw_feat.version, MAC_VR, SNPSVER) > 0x20)
		वापस xgbe_txq_prepare_tx_stop(pdata, queue);

	/* Calculate the status रेजिस्टर to पढ़ो and the position within */
	अगर (queue < DMA_DSRX_FIRST_QUEUE) अणु
		tx_dsr = DMA_DSR0;
		tx_pos = (queue * DMA_DSR_Q_WIDTH) + DMA_DSR0_TPS_START;
	पूर्ण अन्यथा अणु
		tx_qidx = queue - DMA_DSRX_FIRST_QUEUE;

		tx_dsr = DMA_DSR1 + ((tx_qidx / DMA_DSRX_QPR) * DMA_DSRX_INC);
		tx_pos = ((tx_qidx % DMA_DSRX_QPR) * DMA_DSR_Q_WIDTH) +
			 DMA_DSRX_TPS_START;
	पूर्ण

	/* The Tx engine cannot be stopped अगर it is actively processing
	 * descriptors. Wait क्रम the Tx engine to enter the stopped or
	 * suspended state.  Don't रुको क्रमever though...
	 */
	tx_समयout = jअगरfies + (XGBE_DMA_STOP_TIMEOUT * HZ);
	जबतक (समय_beक्रमe(jअगरfies, tx_समयout)) अणु
		tx_status = XGMAC_IOREAD(pdata, tx_dsr);
		tx_status = GET_BITS(tx_status, tx_pos, DMA_DSR_TPS_WIDTH);
		अगर ((tx_status == DMA_TPS_STOPPED) ||
		    (tx_status == DMA_TPS_SUSPENDED))
			अवरोध;

		usleep_range(500, 1000);
	पूर्ण

	अगर (!समय_beक्रमe(jअगरfies, tx_समयout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Tx DMA channel %u to stop\n",
			    queue);
पूर्ण

अटल व्योम xgbe_enable_tx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Enable each Tx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, ST, 1);
	पूर्ण

	/* Enable each Tx queue */
	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TXQEN,
				       MTL_Q_ENABLED);

	/* Enable MAC Tx */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, TE, 1);
पूर्ण

अटल व्योम xgbe_disable_tx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Prepare क्रम Tx DMA channel stop */
	क्रम (i = 0; i < pdata->tx_q_count; i++)
		xgbe_prepare_tx_stop(pdata, i);

	/* Disable MAC Tx */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, TE, 0);

	/* Disable each Tx queue */
	क्रम (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, TXQEN, 0);

	/* Disable each Tx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, ST, 0);
	पूर्ण
पूर्ण

अटल व्योम xgbe_prepare_rx_stop(काष्ठा xgbe_prv_data *pdata,
				 अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक rx_status;
	अचिन्हित दीर्घ rx_समयout;

	/* The Rx engine cannot be stopped अगर it is actively processing
	 * packets. Wait क्रम the Rx queue to empty the Rx fअगरo.  Don't
	 * रुको क्रमever though...
	 */
	rx_समयout = jअगरfies + (XGBE_DMA_STOP_TIMEOUT * HZ);
	जबतक (समय_beक्रमe(jअगरfies, rx_समयout)) अणु
		rx_status = XGMAC_MTL_IOREAD(pdata, queue, MTL_Q_RQDR);
		अगर ((XGMAC_GET_BITS(rx_status, MTL_Q_RQDR, PRXQ) == 0) &&
		    (XGMAC_GET_BITS(rx_status, MTL_Q_RQDR, RXQSTS) == 0))
			अवरोध;

		usleep_range(500, 1000);
	पूर्ण

	अगर (!समय_beक्रमe(jअगरfies, rx_समयout))
		netdev_info(pdata->netdev,
			    "timed out waiting for Rx queue %u to empty\n",
			    queue);
पूर्ण

अटल व्योम xgbe_enable_rx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक reg_val, i;

	/* Enable each Rx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR, SR, 1);
	पूर्ण

	/* Enable each Rx queue */
	reg_val = 0;
	क्रम (i = 0; i < pdata->rx_q_count; i++)
		reg_val |= (0x02 << (i << 1));
	XGMAC_IOWRITE(pdata, MAC_RQC0R, reg_val);

	/* Enable MAC Rx */
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, DCRCC, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, CST, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, ACS, 1);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, RE, 1);
पूर्ण

अटल व्योम xgbe_disable_rx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Disable MAC Rx */
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, DCRCC, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, CST, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, ACS, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RCR, RE, 0);

	/* Prepare क्रम Rx DMA channel stop */
	क्रम (i = 0; i < pdata->rx_q_count; i++)
		xgbe_prepare_rx_stop(pdata, i);

	/* Disable each Rx queue */
	XGMAC_IOWRITE(pdata, MAC_RQC0R, 0);

	/* Disable each Rx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR, SR, 0);
	पूर्ण
पूर्ण

अटल व्योम xgbe_घातerup_tx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Enable each Tx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, ST, 1);
	पूर्ण

	/* Enable MAC Tx */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, TE, 1);
पूर्ण

अटल व्योम xgbe_घातerकरोwn_tx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Prepare क्रम Tx DMA channel stop */
	क्रम (i = 0; i < pdata->tx_q_count; i++)
		xgbe_prepare_tx_stop(pdata, i);

	/* Disable MAC Tx */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, TE, 0);

	/* Disable each Tx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->tx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_TCR, ST, 0);
	पूर्ण
पूर्ण

अटल व्योम xgbe_घातerup_rx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Enable each Rx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR, SR, 1);
	पूर्ण
पूर्ण

अटल व्योम xgbe_घातerकरोwn_rx(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक i;

	/* Disable each Rx DMA channel */
	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!pdata->channel[i]->rx_ring)
			अवरोध;

		XGMAC_DMA_IOWRITE_BITS(pdata->channel[i], DMA_CH_RCR, SR, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_desc_अगर *desc_अगर = &pdata->desc_अगर;
	पूर्णांक ret;

	DBGPR("-->xgbe_init\n");

	/* Flush Tx queues */
	ret = xgbe_flush_tx_queues(pdata);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "error flushing TX queues\n");
		वापस ret;
	पूर्ण

	/*
	 * Initialize DMA related features
	 */
	xgbe_config_dma_bus(pdata);
	xgbe_config_dma_cache(pdata);
	xgbe_config_osp_mode(pdata);
	xgbe_config_pbl_val(pdata);
	xgbe_config_rx_coalesce(pdata);
	xgbe_config_tx_coalesce(pdata);
	xgbe_config_rx_buffer_size(pdata);
	xgbe_config_tso_mode(pdata);
	xgbe_config_sph_mode(pdata);
	xgbe_config_rss(pdata);
	desc_अगर->wrapper_tx_desc_init(pdata);
	desc_अगर->wrapper_rx_desc_init(pdata);
	xgbe_enable_dma_पूर्णांकerrupts(pdata);

	/*
	 * Initialize MTL related features
	 */
	xgbe_config_mtl_mode(pdata);
	xgbe_config_queue_mapping(pdata);
	xgbe_config_tsf_mode(pdata, pdata->tx_sf_mode);
	xgbe_config_rsf_mode(pdata, pdata->rx_sf_mode);
	xgbe_config_tx_threshold(pdata, pdata->tx_threshold);
	xgbe_config_rx_threshold(pdata, pdata->rx_threshold);
	xgbe_config_tx_fअगरo_size(pdata);
	xgbe_config_rx_fअगरo_size(pdata);
	/*TODO: Error Packet and undersized good Packet क्रमwarding enable
		(FEP and FUP)
	 */
	xgbe_config_dcb_tc(pdata);
	xgbe_enable_mtl_पूर्णांकerrupts(pdata);

	/*
	 * Initialize MAC related features
	 */
	xgbe_config_mac_address(pdata);
	xgbe_config_rx_mode(pdata);
	xgbe_config_jumbo_enable(pdata);
	xgbe_config_flow_control(pdata);
	xgbe_config_mac_speed(pdata);
	xgbe_config_checksum_offload(pdata);
	xgbe_config_vlan_support(pdata);
	xgbe_config_mmc(pdata);
	xgbe_enable_mac_पूर्णांकerrupts(pdata);

	/*
	 * Initialize ECC related features
	 */
	xgbe_enable_ecc_पूर्णांकerrupts(pdata);

	DBGPR("<--xgbe_init\n");

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_dev(काष्ठा xgbe_hw_अगर *hw_अगर)
अणु
	DBGPR("-->xgbe_init_function_ptrs\n");

	hw_अगर->tx_complete = xgbe_tx_complete;

	hw_अगर->set_mac_address = xgbe_set_mac_address;
	hw_अगर->config_rx_mode = xgbe_config_rx_mode;

	hw_अगर->enable_rx_csum = xgbe_enable_rx_csum;
	hw_अगर->disable_rx_csum = xgbe_disable_rx_csum;

	hw_अगर->enable_rx_vlan_stripping = xgbe_enable_rx_vlan_stripping;
	hw_अगर->disable_rx_vlan_stripping = xgbe_disable_rx_vlan_stripping;
	hw_अगर->enable_rx_vlan_filtering = xgbe_enable_rx_vlan_filtering;
	hw_अगर->disable_rx_vlan_filtering = xgbe_disable_rx_vlan_filtering;
	hw_अगर->update_vlan_hash_table = xgbe_update_vlan_hash_table;

	hw_अगर->पढ़ो_mmd_regs = xgbe_पढ़ो_mmd_regs;
	hw_अगर->ग_लिखो_mmd_regs = xgbe_ग_लिखो_mmd_regs;

	hw_अगर->set_speed = xgbe_set_speed;

	hw_अगर->set_ext_mii_mode = xgbe_set_ext_mii_mode;
	hw_अगर->पढ़ो_ext_mii_regs = xgbe_पढ़ो_ext_mii_regs;
	hw_अगर->ग_लिखो_ext_mii_regs = xgbe_ग_लिखो_ext_mii_regs;

	hw_अगर->set_gpio = xgbe_set_gpio;
	hw_अगर->clr_gpio = xgbe_clr_gpio;

	hw_अगर->enable_tx = xgbe_enable_tx;
	hw_अगर->disable_tx = xgbe_disable_tx;
	hw_अगर->enable_rx = xgbe_enable_rx;
	hw_अगर->disable_rx = xgbe_disable_rx;

	hw_अगर->घातerup_tx = xgbe_घातerup_tx;
	hw_अगर->घातerकरोwn_tx = xgbe_घातerकरोwn_tx;
	hw_अगर->घातerup_rx = xgbe_घातerup_rx;
	hw_अगर->घातerकरोwn_rx = xgbe_घातerकरोwn_rx;

	hw_अगर->dev_xmit = xgbe_dev_xmit;
	hw_अगर->dev_पढ़ो = xgbe_dev_पढ़ो;
	hw_अगर->enable_पूर्णांक = xgbe_enable_पूर्णांक;
	hw_अगर->disable_पूर्णांक = xgbe_disable_पूर्णांक;
	hw_अगर->init = xgbe_init;
	hw_अगर->निकास = xgbe_निकास;

	/* Descriptor related Sequences have to be initialized here */
	hw_अगर->tx_desc_init = xgbe_tx_desc_init;
	hw_अगर->rx_desc_init = xgbe_rx_desc_init;
	hw_अगर->tx_desc_reset = xgbe_tx_desc_reset;
	hw_अगर->rx_desc_reset = xgbe_rx_desc_reset;
	hw_अगर->is_last_desc = xgbe_is_last_desc;
	hw_अगर->is_context_desc = xgbe_is_context_desc;
	hw_अगर->tx_start_xmit = xgbe_tx_start_xmit;

	/* For FLOW ctrl */
	hw_अगर->config_tx_flow_control = xgbe_config_tx_flow_control;
	hw_अगर->config_rx_flow_control = xgbe_config_rx_flow_control;

	/* For RX coalescing */
	hw_अगर->config_rx_coalesce = xgbe_config_rx_coalesce;
	hw_अगर->config_tx_coalesce = xgbe_config_tx_coalesce;
	hw_अगर->usec_to_riwt = xgbe_usec_to_riwt;
	hw_अगर->riwt_to_usec = xgbe_riwt_to_usec;

	/* For RX and TX threshold config */
	hw_अगर->config_rx_threshold = xgbe_config_rx_threshold;
	hw_अगर->config_tx_threshold = xgbe_config_tx_threshold;

	/* For RX and TX Store and Forward Mode config */
	hw_अगर->config_rsf_mode = xgbe_config_rsf_mode;
	hw_अगर->config_tsf_mode = xgbe_config_tsf_mode;

	/* For TX DMA Operating on Second Frame config */
	hw_अगर->config_osp_mode = xgbe_config_osp_mode;

	/* For MMC statistics support */
	hw_अगर->tx_mmc_पूर्णांक = xgbe_tx_mmc_पूर्णांक;
	hw_अगर->rx_mmc_पूर्णांक = xgbe_rx_mmc_पूर्णांक;
	hw_अगर->पढ़ो_mmc_stats = xgbe_पढ़ो_mmc_stats;

	/* For PTP config */
	hw_अगर->config_tstamp = xgbe_config_tstamp;
	hw_अगर->update_tstamp_addend = xgbe_update_tstamp_addend;
	hw_अगर->set_tstamp_समय = xgbe_set_tstamp_समय;
	hw_अगर->get_tstamp_समय = xgbe_get_tstamp_समय;
	hw_अगर->get_tx_tstamp = xgbe_get_tx_tstamp;

	/* For Data Center Bridging config */
	hw_अगर->config_tc = xgbe_config_tc;
	hw_अगर->config_dcb_tc = xgbe_config_dcb_tc;
	hw_अगर->config_dcb_pfc = xgbe_config_dcb_pfc;

	/* For Receive Side Scaling */
	hw_अगर->enable_rss = xgbe_enable_rss;
	hw_अगर->disable_rss = xgbe_disable_rss;
	hw_अगर->set_rss_hash_key = xgbe_set_rss_hash_key;
	hw_अगर->set_rss_lookup_table = xgbe_set_rss_lookup_table;

	/* For ECC */
	hw_अगर->disable_ecc_ded = xgbe_disable_ecc_ded;
	hw_अगर->disable_ecc_sec = xgbe_disable_ecc_sec;

	/* For VXLAN */
	hw_अगर->enable_vxlan = xgbe_enable_vxlan;
	hw_अगर->disable_vxlan = xgbe_disable_vxlan;
	hw_अगर->set_vxlan_id = xgbe_set_vxlan_id;

	DBGPR("<--xgbe_init_function_ptrs\n");
पूर्ण
