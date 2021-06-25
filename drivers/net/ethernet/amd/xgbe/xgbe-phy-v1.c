<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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
#समावेश <linux/kmod.h>
#समावेश <linux/device.h>
#समावेश <linux/property.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

#घोषणा XGBE_BLWC_PROPERTY		"amd,serdes-blwc"
#घोषणा XGBE_CDR_RATE_PROPERTY		"amd,serdes-cdr-rate"
#घोषणा XGBE_PQ_SKEW_PROPERTY		"amd,serdes-pq-skew"
#घोषणा XGBE_TX_AMP_PROPERTY		"amd,serdes-tx-amp"
#घोषणा XGBE_DFE_CFG_PROPERTY		"amd,serdes-dfe-tap-config"
#घोषणा XGBE_DFE_ENA_PROPERTY		"amd,serdes-dfe-tap-enable"

/* Default SerDes settings */
#घोषणा XGBE_SPEED_1000_BLWC		1
#घोषणा XGBE_SPEED_1000_CDR		0x2
#घोषणा XGBE_SPEED_1000_PLL		0x0
#घोषणा XGBE_SPEED_1000_PQ		0xa
#घोषणा XGBE_SPEED_1000_RATE		0x3
#घोषणा XGBE_SPEED_1000_TXAMP		0xf
#घोषणा XGBE_SPEED_1000_WORD		0x1
#घोषणा XGBE_SPEED_1000_DFE_TAP_CONFIG	0x3
#घोषणा XGBE_SPEED_1000_DFE_TAP_ENABLE	0x0

#घोषणा XGBE_SPEED_2500_BLWC		1
#घोषणा XGBE_SPEED_2500_CDR		0x2
#घोषणा XGBE_SPEED_2500_PLL		0x0
#घोषणा XGBE_SPEED_2500_PQ		0xa
#घोषणा XGBE_SPEED_2500_RATE		0x1
#घोषणा XGBE_SPEED_2500_TXAMP		0xf
#घोषणा XGBE_SPEED_2500_WORD		0x1
#घोषणा XGBE_SPEED_2500_DFE_TAP_CONFIG	0x3
#घोषणा XGBE_SPEED_2500_DFE_TAP_ENABLE	0x0

#घोषणा XGBE_SPEED_10000_BLWC		0
#घोषणा XGBE_SPEED_10000_CDR		0x7
#घोषणा XGBE_SPEED_10000_PLL		0x1
#घोषणा XGBE_SPEED_10000_PQ		0x12
#घोषणा XGBE_SPEED_10000_RATE		0x0
#घोषणा XGBE_SPEED_10000_TXAMP		0xa
#घोषणा XGBE_SPEED_10000_WORD		0x7
#घोषणा XGBE_SPEED_10000_DFE_TAP_CONFIG	0x1
#घोषणा XGBE_SPEED_10000_DFE_TAP_ENABLE	0x7f

/* Rate-change complete रुको/retry count */
#घोषणा XGBE_RATECHANGE_COUNT		500

अटल स्थिर u32 xgbe_phy_blwc[] = अणु
	XGBE_SPEED_1000_BLWC,
	XGBE_SPEED_2500_BLWC,
	XGBE_SPEED_10000_BLWC,
पूर्ण;

अटल स्थिर u32 xgbe_phy_cdr_rate[] = अणु
	XGBE_SPEED_1000_CDR,
	XGBE_SPEED_2500_CDR,
	XGBE_SPEED_10000_CDR,
पूर्ण;

अटल स्थिर u32 xgbe_phy_pq_skew[] = अणु
	XGBE_SPEED_1000_PQ,
	XGBE_SPEED_2500_PQ,
	XGBE_SPEED_10000_PQ,
पूर्ण;

अटल स्थिर u32 xgbe_phy_tx_amp[] = अणु
	XGBE_SPEED_1000_TXAMP,
	XGBE_SPEED_2500_TXAMP,
	XGBE_SPEED_10000_TXAMP,
पूर्ण;

अटल स्थिर u32 xgbe_phy_dfe_tap_cfg[] = अणु
	XGBE_SPEED_1000_DFE_TAP_CONFIG,
	XGBE_SPEED_2500_DFE_TAP_CONFIG,
	XGBE_SPEED_10000_DFE_TAP_CONFIG,
पूर्ण;

अटल स्थिर u32 xgbe_phy_dfe_tap_ena[] = अणु
	XGBE_SPEED_1000_DFE_TAP_ENABLE,
	XGBE_SPEED_2500_DFE_TAP_ENABLE,
	XGBE_SPEED_10000_DFE_TAP_ENABLE,
पूर्ण;

काष्ठा xgbe_phy_data अणु
	/* 1000/10000 vs 2500/10000 indicator */
	अचिन्हित पूर्णांक speed_set;

	/* SerDes UEFI configurable settings.
	 *   Switching between modes/speeds requires new values क्रम some
	 *   SerDes settings.  The values can be supplied as device
	 *   properties in array क्रमmat.  The first array entry is क्रम
	 *   1GbE, second क्रम 2.5GbE and third क्रम 10GbE
	 */
	u32 blwc[XGBE_SPEEDS];
	u32 cdr_rate[XGBE_SPEEDS];
	u32 pq_skew[XGBE_SPEEDS];
	u32 tx_amp[XGBE_SPEEDS];
	u32 dfe_tap_cfg[XGBE_SPEEDS];
	u32 dfe_tap_ena[XGBE_SPEEDS];
पूर्ण;

अटल व्योम xgbe_phy_kr_training_pre(काष्ठा xgbe_prv_data *pdata)
अणु
		XSIR0_IOWRITE_BITS(pdata, SIR0_KR_RT_1, RESET, 1);
पूर्ण

अटल व्योम xgbe_phy_kr_training_post(काष्ठा xgbe_prv_data *pdata)
अणु
		XSIR0_IOWRITE_BITS(pdata, SIR0_KR_RT_1, RESET, 0);
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_mode mode;
	अचिन्हित पूर्णांक ad_reg, lp_reg;

	XGBE_SET_LP_ADV(lks, Autoneg);
	XGBE_SET_LP_ADV(lks, Backplane);

	/* Compare Advertisement and Link Partner रेजिस्टर 1 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA);
	अगर (lp_reg & 0x400)
		XGBE_SET_LP_ADV(lks, Pause);
	अगर (lp_reg & 0x800)
		XGBE_SET_LP_ADV(lks, Asym_Pause);

	अगर (pdata->phy.छोड़ो_स्वतःneg) अणु
		/* Set flow control based on स्वतः-negotiation result */
		pdata->phy.tx_छोड़ो = 0;
		pdata->phy.rx_छोड़ो = 0;

		अगर (ad_reg & lp_reg & 0x400) अणु
			pdata->phy.tx_छोड़ो = 1;
			pdata->phy.rx_छोड़ो = 1;
		पूर्ण अन्यथा अगर (ad_reg & lp_reg & 0x800) अणु
			अगर (ad_reg & 0x400)
				pdata->phy.rx_छोड़ो = 1;
			अन्यथा अगर (lp_reg & 0x400)
				pdata->phy.tx_छोड़ो = 1;
		पूर्ण
	पूर्ण

	/* Compare Advertisement and Link Partner रेजिस्टर 2 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);
	अगर (lp_reg & 0x80)
		XGBE_SET_LP_ADV(lks, 10000baseKR_Full);
	अगर (lp_reg & 0x20) अणु
		अगर (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			XGBE_SET_LP_ADV(lks, 2500baseX_Full);
		अन्यथा
			XGBE_SET_LP_ADV(lks, 1000baseKX_Full);
	पूर्ण

	ad_reg &= lp_reg;
	अगर (ad_reg & 0x80) अणु
		mode = XGBE_MODE_KR;
	पूर्ण अन्यथा अगर (ad_reg & 0x20) अणु
		अगर (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		अन्यथा
			mode = XGBE_MODE_KX_1000;
	पूर्ण अन्यथा अणु
		mode = XGBE_MODE_UNKNOWN;
	पूर्ण

	/* Compare Advertisement and Link Partner रेजिस्टर 3 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);
	अगर (lp_reg & 0xc000)
		XGBE_SET_LP_ADV(lks, 10000baseR_FEC);

	वापस mode;
पूर्ण

अटल व्योम xgbe_phy_an_advertising(काष्ठा xgbe_prv_data *pdata,
				    काष्ठा ethtool_link_ksettings *dlks)
अणु
	काष्ठा ethtool_link_ksettings *slks = &pdata->phy.lks;

	XGBE_LM_COPY(dlks, advertising, slks, advertising);
पूर्ण

अटल पूर्णांक xgbe_phy_an_config(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Nothing uniquely required क्रम an configuration */
	वापस 0;
पूर्ण

अटल क्रमागत xgbe_an_mode xgbe_phy_an_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस XGBE_AN_MODE_CL73;
पूर्ण

अटल व्योम xgbe_phy_pcs_घातer_cycle(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);

	reg |= MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	usleep_range(75, 100);

	reg &= ~MDIO_CTRL1_LPOWER;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);
पूर्ण

अटल व्योम xgbe_phy_start_ratechange(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Assert Rx and Tx ratechange */
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, RATECHANGE, 1);
पूर्ण

अटल व्योम xgbe_phy_complete_ratechange(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक रुको;
	u16 status;

	/* Release Rx and Tx ratechange */
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, RATECHANGE, 0);

	/* Wait क्रम Rx and Tx पढ़ोy */
	रुको = XGBE_RATECHANGE_COUNT;
	जबतक (रुको--) अणु
		usleep_range(50, 75);

		status = XSIR0_IOREAD(pdata, SIR0_STATUS);
		अगर (XSIR_GET_BITS(status, SIR0_STATUS, RX_READY) &&
		    XSIR_GET_BITS(status, SIR0_STATUS, TX_READY))
			जाओ rx_reset;
	पूर्ण

	netअगर_dbg(pdata, link, pdata->netdev, "SerDes rx/tx not ready (%#hx)\n",
		  status);

rx_reset:
	/* Perक्रमm Rx reset क्रम the DFE changes */
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 0);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 1);
पूर्ण

अटल व्योम xgbe_phy_kr_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक reg;

	/* Set PCS to KR/10G speed */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	reg &= ~MDIO_PCS_CTRL2_TYPE;
	reg |= MDIO_PCS_CTRL2_10GBR;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL2, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	reg &= ~MDIO_CTRL1_SPEEDSEL;
	reg |= MDIO_CTRL1_SPEED10G;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	xgbe_phy_pcs_घातer_cycle(pdata);

	/* Set SerDes to 10G speed */
	xgbe_phy_start_ratechange(pdata);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, DATARATE, XGBE_SPEED_10000_RATE);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, WORDMODE, XGBE_SPEED_10000_WORD);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, PLLSEL, XGBE_SPEED_10000_PLL);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, CDR_RATE,
			   phy_data->cdr_rate[XGBE_SPEED_10000]);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_10000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG20, BLWC_ENA,
			   phy_data->blwc[XGBE_SPEED_10000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG114, PQ_REG,
			   phy_data->pq_skew[XGBE_SPEED_10000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG129, RXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_10000]);
	XRXTX_IOWRITE(pdata, RXTX_REG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_10000]);

	xgbe_phy_complete_ratechange(pdata);

	netअगर_dbg(pdata, link, pdata->netdev, "10GbE KR mode set\n");
पूर्ण

अटल व्योम xgbe_phy_kx_2500_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक reg;

	/* Set PCS to KX/1G speed */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	reg &= ~MDIO_PCS_CTRL2_TYPE;
	reg |= MDIO_PCS_CTRL2_10GBX;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL2, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	reg &= ~MDIO_CTRL1_SPEEDSEL;
	reg |= MDIO_CTRL1_SPEED1G;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	xgbe_phy_pcs_घातer_cycle(pdata);

	/* Set SerDes to 2.5G speed */
	xgbe_phy_start_ratechange(pdata);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, DATARATE, XGBE_SPEED_2500_RATE);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, WORDMODE, XGBE_SPEED_2500_WORD);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, PLLSEL, XGBE_SPEED_2500_PLL);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, CDR_RATE,
			   phy_data->cdr_rate[XGBE_SPEED_2500]);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_2500]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG20, BLWC_ENA,
			   phy_data->blwc[XGBE_SPEED_2500]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG114, PQ_REG,
			   phy_data->pq_skew[XGBE_SPEED_2500]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG129, RXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_2500]);
	XRXTX_IOWRITE(pdata, RXTX_REG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_2500]);

	xgbe_phy_complete_ratechange(pdata);

	netअगर_dbg(pdata, link, pdata->netdev, "2.5GbE KX mode set\n");
पूर्ण

अटल व्योम xgbe_phy_kx_1000_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक reg;

	/* Set PCS to KX/1G speed */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	reg &= ~MDIO_PCS_CTRL2_TYPE;
	reg |= MDIO_PCS_CTRL2_10GBX;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL2, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	reg &= ~MDIO_CTRL1_SPEEDSEL;
	reg |= MDIO_CTRL1_SPEED1G;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	xgbe_phy_pcs_घातer_cycle(pdata);

	/* Set SerDes to 1G speed */
	xgbe_phy_start_ratechange(pdata);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, DATARATE, XGBE_SPEED_1000_RATE);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, WORDMODE, XGBE_SPEED_1000_WORD);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, PLLSEL, XGBE_SPEED_1000_PLL);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, CDR_RATE,
			   phy_data->cdr_rate[XGBE_SPEED_1000]);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, TXAMP,
			   phy_data->tx_amp[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG20, BLWC_ENA,
			   phy_data->blwc[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG114, PQ_REG,
			   phy_data->pq_skew[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG129, RXDFE_CONFIG,
			   phy_data->dfe_tap_cfg[XGBE_SPEED_1000]);
	XRXTX_IOWRITE(pdata, RXTX_REG22,
		      phy_data->dfe_tap_ena[XGBE_SPEED_1000]);

	xgbe_phy_complete_ratechange(pdata);

	netअगर_dbg(pdata, link, pdata->netdev, "1GbE KX mode set\n");
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_cur_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_mode mode;
	अचिन्हित पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	reg &= MDIO_PCS_CTRL2_TYPE;

	अगर (reg == MDIO_PCS_CTRL2_10GBR) अणु
		mode = XGBE_MODE_KR;
	पूर्ण अन्यथा अणु
		अगर (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		अन्यथा
			mode = XGBE_MODE_KX_1000;
	पूर्ण

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_चयन_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_mode mode;

	/* If we are in KR चयन to KX, and vice-versa */
	अगर (xgbe_phy_cur_mode(pdata) == XGBE_MODE_KR) अणु
		अगर (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			mode = XGBE_MODE_KX_2500;
		अन्यथा
			mode = XGBE_MODE_KX_1000;
	पूर्ण अन्यथा अणु
		mode = XGBE_MODE_KR;
	पूर्ण

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_mode(काष्ठा xgbe_prv_data *pdata,
					पूर्णांक speed)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (speed) अणु
	हाल SPEED_1000:
		वापस (phy_data->speed_set == XGBE_SPEEDSET_1000_10000)
			? XGBE_MODE_KX_1000 : XGBE_MODE_UNKNOWN;
	हाल SPEED_2500:
		वापस (phy_data->speed_set == XGBE_SPEEDSET_2500_10000)
			? XGBE_MODE_KX_2500 : XGBE_MODE_UNKNOWN;
	हाल SPEED_10000:
		वापस XGBE_MODE_KR;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_set_mode(काष्ठा xgbe_prv_data *pdata, क्रमागत xgbe_mode mode)
अणु
	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
		xgbe_phy_kx_1000_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KX_2500:
		xgbe_phy_kx_2500_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KR:
		xgbe_phy_kr_mode(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_check_mode(काष्ठा xgbe_prv_data *pdata,
				क्रमागत xgbe_mode mode, bool advert)
अणु
	अगर (pdata->phy.स्वतःneg == AUTONEG_ENABLE) अणु
		वापस advert;
	पूर्ण अन्यथा अणु
		क्रमागत xgbe_mode cur_mode;

		cur_mode = xgbe_phy_get_mode(pdata, pdata->phy.speed);
		अगर (cur_mode == mode)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool xgbe_phy_use_mode(काष्ठा xgbe_prv_data *pdata, क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseKX_Full));
	हाल XGBE_MODE_KX_2500:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 2500baseX_Full));
	हाल XGBE_MODE_KR:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 10000baseKR_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed(काष्ठा xgbe_prv_data *pdata, पूर्णांक speed)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (speed) अणु
	हाल SPEED_1000:
		अगर (phy_data->speed_set != XGBE_SPEEDSET_1000_10000)
			वापस false;
		वापस true;
	हाल SPEED_2500:
		अगर (phy_data->speed_set != XGBE_SPEEDSET_2500_10000)
			वापस false;
		वापस true;
	हाल SPEED_10000:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_phy_link_status(काष्ठा xgbe_prv_data *pdata, पूर्णांक *an_restart)
अणु
	अचिन्हित पूर्णांक reg;

	*an_restart = 0;

	/* Link status is latched low, so पढ़ो once to clear
	 * and then पढ़ो again to get current state
	 */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);

	वापस (reg & MDIO_STAT1_LSTATUS) ? 1 : 0;
पूर्ण

अटल व्योम xgbe_phy_stop(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Nothing uniquely required क्रम stop */
पूर्ण

अटल पूर्णांक xgbe_phy_start(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Nothing uniquely required क्रम start */
	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_phy_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक reg, count;

	/* Perक्रमm a software reset of the PCS */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	reg |= MDIO_CTRL1_RESET;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	count = 50;
	करो अणु
		msleep(20);
		reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	पूर्ण जबतक ((reg & MDIO_CTRL1_RESET) && --count);

	अगर (reg & MDIO_CTRL1_RESET)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम xgbe_phy_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Nothing uniquely required क्रम निकास */
पूर्ण

अटल पूर्णांक xgbe_phy_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data;
	पूर्णांक ret;

	phy_data = devm_kzalloc(pdata->dev, माप(*phy_data), GFP_KERNEL);
	अगर (!phy_data)
		वापस -ENOMEM;

	/* Retrieve the PHY speedset */
	ret = device_property_पढ़ो_u32(pdata->phy_dev, XGBE_SPEEDSET_PROPERTY,
				       &phy_data->speed_set);
	अगर (ret) अणु
		dev_err(pdata->dev, "invalid %s property\n",
			XGBE_SPEEDSET_PROPERTY);
		वापस ret;
	पूर्ण

	चयन (phy_data->speed_set) अणु
	हाल XGBE_SPEEDSET_1000_10000:
	हाल XGBE_SPEEDSET_2500_10000:
		अवरोध;
	शेष:
		dev_err(pdata->dev, "invalid %s property\n",
			XGBE_SPEEDSET_PROPERTY);
		वापस -EINVAL;
	पूर्ण

	/* Retrieve the PHY configuration properties */
	अगर (device_property_present(pdata->phy_dev, XGBE_BLWC_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_BLWC_PROPERTY,
						     phy_data->blwc,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_BLWC_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->blwc, xgbe_phy_blwc,
		       माप(phy_data->blwc));
	पूर्ण

	अगर (device_property_present(pdata->phy_dev, XGBE_CDR_RATE_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_CDR_RATE_PROPERTY,
						     phy_data->cdr_rate,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_CDR_RATE_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->cdr_rate, xgbe_phy_cdr_rate,
		       माप(phy_data->cdr_rate));
	पूर्ण

	अगर (device_property_present(pdata->phy_dev, XGBE_PQ_SKEW_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_PQ_SKEW_PROPERTY,
						     phy_data->pq_skew,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_PQ_SKEW_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->pq_skew, xgbe_phy_pq_skew,
		       माप(phy_data->pq_skew));
	पूर्ण

	अगर (device_property_present(pdata->phy_dev, XGBE_TX_AMP_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_TX_AMP_PROPERTY,
						     phy_data->tx_amp,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_TX_AMP_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->tx_amp, xgbe_phy_tx_amp,
		       माप(phy_data->tx_amp));
	पूर्ण

	अगर (device_property_present(pdata->phy_dev, XGBE_DFE_CFG_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_DFE_CFG_PROPERTY,
						     phy_data->dfe_tap_cfg,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_DFE_CFG_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->dfe_tap_cfg, xgbe_phy_dfe_tap_cfg,
		       माप(phy_data->dfe_tap_cfg));
	पूर्ण

	अगर (device_property_present(pdata->phy_dev, XGBE_DFE_ENA_PROPERTY)) अणु
		ret = device_property_पढ़ो_u32_array(pdata->phy_dev,
						     XGBE_DFE_ENA_PROPERTY,
						     phy_data->dfe_tap_ena,
						     XGBE_SPEEDS);
		अगर (ret) अणु
			dev_err(pdata->dev, "invalid %s property\n",
				XGBE_DFE_ENA_PROPERTY);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(phy_data->dfe_tap_ena, xgbe_phy_dfe_tap_ena,
		       माप(phy_data->dfe_tap_ena));
	पूर्ण

	/* Initialize supported features */
	XGBE_ZERO_SUP(lks);
	XGBE_SET_SUP(lks, Autoneg);
	XGBE_SET_SUP(lks, Pause);
	XGBE_SET_SUP(lks, Asym_Pause);
	XGBE_SET_SUP(lks, Backplane);
	XGBE_SET_SUP(lks, 10000baseKR_Full);
	चयन (phy_data->speed_set) अणु
	हाल XGBE_SPEEDSET_1000_10000:
		XGBE_SET_SUP(lks, 1000baseKX_Full);
		अवरोध;
	हाल XGBE_SPEEDSET_2500_10000:
		XGBE_SET_SUP(lks, 2500baseX_Full);
		अवरोध;
	पूर्ण

	अगर (pdata->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE)
		XGBE_SET_SUP(lks, 10000baseR_FEC);

	pdata->phy_data = phy_data;

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_phy_v1(काष्ठा xgbe_phy_अगर *phy_अगर)
अणु
	काष्ठा xgbe_phy_impl_अगर *phy_impl = &phy_अगर->phy_impl;

	phy_impl->init			= xgbe_phy_init;
	phy_impl->निकास			= xgbe_phy_निकास;

	phy_impl->reset			= xgbe_phy_reset;
	phy_impl->start			= xgbe_phy_start;
	phy_impl->stop			= xgbe_phy_stop;

	phy_impl->link_status		= xgbe_phy_link_status;

	phy_impl->valid_speed		= xgbe_phy_valid_speed;

	phy_impl->use_mode		= xgbe_phy_use_mode;
	phy_impl->set_mode		= xgbe_phy_set_mode;
	phy_impl->get_mode		= xgbe_phy_get_mode;
	phy_impl->चयन_mode		= xgbe_phy_चयन_mode;
	phy_impl->cur_mode		= xgbe_phy_cur_mode;

	phy_impl->an_mode		= xgbe_phy_an_mode;

	phy_impl->an_config		= xgbe_phy_an_config;

	phy_impl->an_advertising	= xgbe_phy_an_advertising;

	phy_impl->an_outcome		= xgbe_phy_an_outcome;

	phy_impl->kr_training_pre	= xgbe_phy_kr_training_pre;
	phy_impl->kr_training_post	= xgbe_phy_kr_training_post;
पूर्ण
