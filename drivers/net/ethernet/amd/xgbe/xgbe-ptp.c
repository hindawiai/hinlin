<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
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
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल u64 xgbe_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(cc,
						   काष्ठा xgbe_prv_data,
						   tstamp_cc);
	u64 nsec;

	nsec = pdata->hw_अगर.get_tstamp_समय(pdata);

	वापस nsec;
पूर्ण

अटल पूर्णांक xgbe_adjfreq(काष्ठा ptp_घड़ी_info *info, s32 delta)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(info,
						   काष्ठा xgbe_prv_data,
						   ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 adjust;
	u32 addend, dअगरf;
	अचिन्हित पूर्णांक neg_adjust = 0;

	अगर (delta < 0) अणु
		neg_adjust = 1;
		delta = -delta;
	पूर्ण

	adjust = pdata->tstamp_addend;
	adjust *= delta;
	dअगरf = भाग_u64(adjust, 1000000000UL);

	addend = (neg_adjust) ? pdata->tstamp_addend - dअगरf :
				pdata->tstamp_addend + dअगरf;

	spin_lock_irqsave(&pdata->tstamp_lock, flags);

	pdata->hw_अगर.update_tstamp_addend(pdata, addend);

	spin_unlock_irqrestore(&pdata->tstamp_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_adjसमय(काष्ठा ptp_घड़ी_info *info, s64 delta)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(info,
						   काष्ठा xgbe_prv_data,
						   ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->tstamp_lock, flags);
	समयcounter_adjसमय(&pdata->tstamp_tc, delta);
	spin_unlock_irqrestore(&pdata->tstamp_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_समय_लो(काष्ठा ptp_घड़ी_info *info, काष्ठा बारpec64 *ts)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(info,
						   काष्ठा xgbe_prv_data,
						   ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 nsec;

	spin_lock_irqsave(&pdata->tstamp_lock, flags);

	nsec = समयcounter_पढ़ो(&pdata->tstamp_tc);

	spin_unlock_irqrestore(&pdata->tstamp_lock, flags);

	*ts = ns_to_बारpec64(nsec);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_समय_रखो(काष्ठा ptp_घड़ी_info *info,
			स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(info,
						   काष्ठा xgbe_prv_data,
						   ptp_घड़ी_info);
	अचिन्हित दीर्घ flags;
	u64 nsec;

	nsec = बारpec64_to_ns(ts);

	spin_lock_irqsave(&pdata->tstamp_lock, flags);

	समयcounter_init(&pdata->tstamp_tc, &pdata->tstamp_cc, nsec);

	spin_unlock_irqrestore(&pdata->tstamp_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक xgbe_enable(काष्ठा ptp_घड़ी_info *info,
		       काष्ठा ptp_घड़ी_request *request, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

व्योम xgbe_ptp_रेजिस्टर(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ptp_घड़ी_info *info = &pdata->ptp_घड़ी_info;
	काष्ठा ptp_घड़ी *घड़ी;
	काष्ठा cyclecounter *cc = &pdata->tstamp_cc;
	u64 भागidend;

	snम_लिखो(info->name, माप(info->name), "%s",
		 netdev_name(pdata->netdev));
	info->owner = THIS_MODULE;
	info->max_adj = pdata->ptpclk_rate;
	info->adjfreq = xgbe_adjfreq;
	info->adjसमय = xgbe_adjसमय;
	info->समय_लो64 = xgbe_समय_लो;
	info->समय_रखो64 = xgbe_समय_रखो;
	info->enable = xgbe_enable;

	घड़ी = ptp_घड़ी_रेजिस्टर(info, pdata->dev);
	अगर (IS_ERR(घड़ी)) अणु
		dev_err(pdata->dev, "ptp_clock_register failed\n");
		वापस;
	पूर्ण

	pdata->ptp_घड़ी = घड़ी;

	/* Calculate the addend:
	 *   addend = 2^32 / (PTP ref घड़ी / 50Mhz)
	 *          = (2^32 * 50Mhz) / PTP ref घड़ी
	 */
	भागidend = 50000000;
	भागidend <<= 32;
	pdata->tstamp_addend = भाग_u64(भागidend, pdata->ptpclk_rate);

	/* Setup the समयcounter */
	cc->पढ़ो = xgbe_cc_पढ़ो;
	cc->mask = CLOCKSOURCE_MASK(64);
	cc->mult = 1;
	cc->shअगरt = 0;

	समयcounter_init(&pdata->tstamp_tc, &pdata->tstamp_cc,
			 kसमय_प्रकारo_ns(kसमय_get_real()));

	/* Disable all बारtamping to start */
	XGMAC_IOWRITE(pdata, MAC_TSCR, 0);
	pdata->tstamp_config.tx_type = HWTSTAMP_TX_OFF;
	pdata->tstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;
पूर्ण

व्योम xgbe_ptp_unरेजिस्टर(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(pdata->ptp_घड़ी);
पूर्ण
