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

#समावेश <linux/netdevice.h>
#समावेश <net/dcbnl.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल पूर्णांक xgbe_dcb_ieee_getets(काष्ठा net_device *netdev,
				काष्ठा ieee_ets *ets)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	/* Set number of supported traffic classes */
	ets->ets_cap = pdata->hw_feat.tc_cnt;

	अगर (pdata->ets) अणु
		ets->cbs = pdata->ets->cbs;
		स_नकल(ets->tc_tx_bw, pdata->ets->tc_tx_bw,
		       माप(ets->tc_tx_bw));
		स_नकल(ets->tc_tsa, pdata->ets->tc_tsa,
		       माप(ets->tc_tsa));
		स_नकल(ets->prio_tc, pdata->ets->prio_tc,
		       माप(ets->prio_tc));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_dcb_ieee_setets(काष्ठा net_device *netdev,
				काष्ठा ieee_ets *ets)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	अचिन्हित पूर्णांक i, tc_ets, tc_ets_weight;
	u8 max_tc = 0;

	tc_ets = 0;
	tc_ets_weight = 0;
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		netअगर_dbg(pdata, drv, netdev,
			  "TC%u: tx_bw=%hhu, rx_bw=%hhu, tsa=%hhu\n", i,
			  ets->tc_tx_bw[i], ets->tc_rx_bw[i],
			  ets->tc_tsa[i]);
		netअगर_dbg(pdata, drv, netdev, "PRIO%u: TC=%hhu\n", i,
			  ets->prio_tc[i]);

		max_tc = max_t(u8, max_tc, ets->prio_tc[i]);
		अगर ((ets->tc_tx_bw[i] || ets->tc_tsa[i]))
			max_tc = max_t(u8, max_tc, i);

		चयन (ets->tc_tsa[i]) अणु
		हाल IEEE_8021QAZ_TSA_STRICT:
			अवरोध;
		हाल IEEE_8021QAZ_TSA_ETS:
			tc_ets = 1;
			tc_ets_weight += ets->tc_tx_bw[i];
			अवरोध;
		शेष:
			netअगर_err(pdata, drv, netdev,
				  "unsupported TSA algorithm (%hhu)\n",
				  ets->tc_tsa[i]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Check maximum traffic class requested */
	अगर (max_tc >= pdata->hw_feat.tc_cnt) अणु
		netअगर_err(pdata, drv, netdev,
			  "exceeded number of supported traffic classes\n");
		वापस -EINVAL;
	पूर्ण

	/* Weights must add up to 100% */
	अगर (tc_ets && (tc_ets_weight != 100)) अणु
		netअगर_err(pdata, drv, netdev,
			  "sum of ETS algorithm weights is not 100 (%u)\n",
			  tc_ets_weight);
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->ets) अणु
		pdata->ets = devm_kzalloc(pdata->dev, माप(*pdata->ets),
					  GFP_KERNEL);
		अगर (!pdata->ets)
			वापस -ENOMEM;
	पूर्ण

	pdata->num_tcs = max_tc + 1;
	स_नकल(pdata->ets, ets, माप(*pdata->ets));

	pdata->hw_अगर.config_dcb_tc(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_dcb_ieee_getpfc(काष्ठा net_device *netdev,
				काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	/* Set number of supported PFC traffic classes */
	pfc->pfc_cap = pdata->hw_feat.tc_cnt;

	अगर (pdata->pfc) अणु
		pfc->pfc_en = pdata->pfc->pfc_en;
		pfc->mbc = pdata->pfc->mbc;
		pfc->delay = pdata->pfc->delay;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_dcb_ieee_setpfc(काष्ठा net_device *netdev,
				काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);

	netअगर_dbg(pdata, drv, netdev,
		  "cap=%hhu, en=%#hhx, mbc=%hhu, delay=%hhu\n",
		  pfc->pfc_cap, pfc->pfc_en, pfc->mbc, pfc->delay);

	/* Check PFC क्रम supported number of traffic classes */
	अगर (pfc->pfc_en & ~((1 << pdata->hw_feat.tc_cnt) - 1)) अणु
		netअगर_err(pdata, drv, netdev,
			  "PFC requested for unsupported traffic class\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pdata->pfc) अणु
		pdata->pfc = devm_kzalloc(pdata->dev, माप(*pdata->pfc),
					  GFP_KERNEL);
		अगर (!pdata->pfc)
			वापस -ENOMEM;
	पूर्ण

	स_नकल(pdata->pfc, pfc, माप(*pdata->pfc));

	pdata->hw_अगर.config_dcb_pfc(pdata);

	वापस 0;
पूर्ण

अटल u8 xgbe_dcb_getdcbx(काष्ठा net_device *netdev)
अणु
	वापस DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VER_IEEE;
पूर्ण

अटल u8 xgbe_dcb_setdcbx(काष्ठा net_device *netdev, u8 dcbx)
अणु
	काष्ठा xgbe_prv_data *pdata = netdev_priv(netdev);
	u8 support = xgbe_dcb_getdcbx(netdev);

	netअगर_dbg(pdata, drv, netdev, "DCBX=%#hhx\n", dcbx);

	अगर (dcbx & ~support)
		वापस 1;

	अगर ((dcbx & support) != support)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dcbnl_rtnl_ops xgbe_dcbnl_ops = अणु
	/* IEEE 802.1Qaz std */
	.ieee_getets = xgbe_dcb_ieee_getets,
	.ieee_setets = xgbe_dcb_ieee_setets,
	.ieee_getpfc = xgbe_dcb_ieee_getpfc,
	.ieee_setpfc = xgbe_dcb_ieee_setpfc,

	/* DCBX configuration */
	.getdcbx     = xgbe_dcb_getdcbx,
	.setdcbx     = xgbe_dcb_setdcbx,
पूर्ण;

स्थिर काष्ठा dcbnl_rtnl_ops *xgbe_get_dcbnl_ops(व्योम)
अणु
	वापस &xgbe_dcbnl_ops;
पूर्ण
