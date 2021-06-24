<शैली गुरु>
/*
 * cxgb4_ptp.c:Chelsio PTP support क्रम T5/T6
 *
 * Copyright (c) 2003-2017 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Written by: Atul Gupta (atul.gupta@chelsio.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/udp.h>

#समावेश "cxgb4.h"
#समावेश "t4_hw.h"
#समावेश "t4_regs.h"
#समावेश "t4_msg.h"
#समावेश "t4fw_api.h"
#समावेश "cxgb4_ptp.h"

/**
 * cxgb4_ptp_is_ptp_tx - determine whether TX packet is PTP or not
 * @skb: skb of outgoing ptp request
 *
 */
bool cxgb4_ptp_is_ptp_tx(काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh;

	uh = udp_hdr(skb);
	वापस skb->len >= PTP_MIN_LENGTH &&
		skb->len <= PTP_IN_TRANSMIT_PACKET_MAXNUM &&
		likely(skb->protocol == htons(ETH_P_IP)) &&
		ip_hdr(skb)->protocol == IPPROTO_UDP &&
		uh->dest == htons(PTP_EVENT_PORT);
पूर्ण

bool is_ptp_enabled(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi;

	pi = netdev_priv(dev);
	वापस (pi->ptp_enable && cxgb4_xmit_with_hwtstamp(skb) &&
		cxgb4_ptp_is_ptp_tx(skb));
पूर्ण

/**
 * cxgb4_ptp_is_ptp_rx - determine whether RX packet is PTP or not
 * @skb: skb of incoming ptp request
 *
 */
bool cxgb4_ptp_is_ptp_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh = (काष्ठा udphdr *)(skb->data + ETH_HLEN +
					      IPV4_HLEN(skb->data));

	वापस  uh->dest == htons(PTP_EVENT_PORT) &&
		uh->source == htons(PTP_EVENT_PORT);
पूर्ण

/**
 * cxgb4_ptp_पढ़ो_hwstamp - पढ़ो बारtamp क्रम TX event PTP message
 * @adapter: board निजी काष्ठाure
 * @pi: port निजी काष्ठाure
 *
 */
व्योम cxgb4_ptp_पढ़ो_hwstamp(काष्ठा adapter *adapter, काष्ठा port_info *pi)
अणु
	काष्ठा skb_shared_hwtstamps *skb_ts = शून्य;
	u64 tx_ts;

	skb_ts = skb_hwtstamps(adapter->ptp_tx_skb);

	tx_ts = t4_पढ़ो_reg(adapter,
			    T5_PORT_REG(pi->port_id, MAC_PORT_TX_TS_VAL_LO));

	tx_ts |= (u64)t4_पढ़ो_reg(adapter,
				  T5_PORT_REG(pi->port_id,
					      MAC_PORT_TX_TS_VAL_HI)) << 32;
	skb_ts->hwtstamp = ns_to_kसमय(tx_ts);
	skb_tstamp_tx(adapter->ptp_tx_skb, skb_ts);
	dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
	spin_lock(&adapter->ptp_lock);
	adapter->ptp_tx_skb = शून्य;
	spin_unlock(&adapter->ptp_lock);
पूर्ण

/**
 * cxgb4_ptprx_बारtamping - Enable Timestamp क्रम RX PTP event message
 * @pi: port निजी काष्ठाure
 * @port: pot number
 * @mode: RX mode
 *
 */
पूर्णांक cxgb4_ptprx_बारtamping(काष्ठा port_info *pi, u8 port, u16 mode)
अणु
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(port));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.init.sc = FW_PTP_SC_RXTIME_STAMP;
	c.u.init.mode = cpu_to_be16(mode);

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);
	वापस err;
पूर्ण

पूर्णांक cxgb4_ptp_txtype(काष्ठा adapter *adapter, u8 port)
अणु
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(port));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.init.sc = FW_PTP_SC_TX_TYPE;
	c.u.init.mode = cpu_to_be16(PTP_TS_NONE);

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);

	वापस err;
पूर्ण

पूर्णांक cxgb4_ptp_redirect_rx_packet(काष्ठा adapter *adapter, काष्ठा port_info *pi)
अणु
	काष्ठा sge *s = &adapter->sge;
	काष्ठा sge_eth_rxq *receive_q =  &s->ethrxq[pi->first_qset];
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(pi->port_id));

	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.init.sc = FW_PTP_SC_RDRX_TYPE;
	c.u.init.txchan = pi->tx_chan;
	c.u.init.असलid = cpu_to_be16(receive_q->rspq.असल_id);

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);
	वापस err;
पूर्ण

/**
 * cxgb4_ptp_adjfreq - Adjust frequency of PHC cycle counter
 * @ptp: ptp घड़ी काष्ठाure
 * @ppb: Desired frequency change in parts per billion
 *
 * Adjust the frequency of the PHC cycle counter by the indicated ppb from
 * the base frequency.
 */
अटल पूर्णांक cxgb4_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा adapter *adapter = (काष्ठा adapter *)container_of(ptp,
				   काष्ठा adapter, ptp_घड़ी_info);
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(0));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.ts.sc = FW_PTP_SC_ADJ_FREQ;
	c.u.ts.sign = (ppb < 0) ? 1 : 0;
	अगर (ppb < 0)
		ppb = -ppb;
	c.u.ts.ppb = cpu_to_be32(ppb);

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);

	वापस err;
पूर्ण

/**
 * cxgb4_ptp_fineadjसमय - Shअगरt the समय of the hardware घड़ी
 * @adapter: board निजी काष्ठाure
 * @delta: Desired change in nanoseconds
 *
 * Adjust the समयr by resetting the समयcounter काष्ठाure.
 */
अटल पूर्णांक  cxgb4_ptp_fineadjसमय(काष्ठा adapter *adapter, s64 delta)
अणु
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
			     FW_CMD_REQUEST_F |
			     FW_CMD_WRITE_F |
			     FW_PTP_CMD_PORTID_V(0));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.ts.sc = FW_PTP_SC_ADJ_FTIME;
	c.u.ts.sign = (delta < 0) ? 1 : 0;
	अगर (delta < 0)
		delta = -delta;
	c.u.ts.पंचांग = cpu_to_be64(delta);

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);
	वापस err;
पूर्ण

/**
 * cxgb4_ptp_adjसमय - Shअगरt the समय of the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @delta: Desired change in nanoseconds
 *
 * Adjust the समयr by resetting the समयcounter काष्ठाure.
 */
अटल पूर्णांक cxgb4_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा adapter *adapter =
		(काष्ठा adapter *)container_of(ptp, काष्ठा adapter,
					       ptp_घड़ी_info);
	काष्ठा fw_ptp_cmd c;
	s64 sign = 1;
	पूर्णांक err;

	अगर (delta < 0)
		sign = -1;

	अगर (delta * sign > PTP_CLOCK_MAX_ADJTIME) अणु
		स_रखो(&c, 0, माप(c));
		c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
					     FW_CMD_REQUEST_F |
					     FW_CMD_WRITE_F |
					     FW_PTP_CMD_PORTID_V(0));
		c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
		c.u.ts.sc = FW_PTP_SC_ADJ_TIME;
		c.u.ts.sign = (delta < 0) ? 1 : 0;
		अगर (delta < 0)
			delta = -delta;
		c.u.ts.पंचांग = cpu_to_be64(delta);

		err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
		अगर (err < 0)
			dev_err(adapter->pdev_dev,
				"PTP: %s error %d\n", __func__, -err);
	पूर्ण अन्यथा अणु
		err = cxgb4_ptp_fineadjसमय(adapter, delta);
	पूर्ण

	वापस err;
पूर्ण

/**
 * cxgb4_ptp_समय_लो - Reads the current समय from the hardware घड़ी
 * @ptp: ptp घड़ी काष्ठाure
 * @ts: बारpec काष्ठाure to hold the current समय value
 *
 * Read the समयcounter and वापस the correct value in ns after converting
 * it पूर्णांकo a काष्ठा बारpec.
 */
अटल पूर्णांक cxgb4_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	काष्ठा adapter *adapter = container_of(ptp, काष्ठा adapter,
					       ptp_घड़ी_info);
	u64 ns;

	ns = t4_पढ़ो_reg(adapter, T5_PORT_REG(0, MAC_PORT_PTP_SUM_LO_A));
	ns |= (u64)t4_पढ़ो_reg(adapter,
			       T5_PORT_REG(0, MAC_PORT_PTP_SUM_HI_A)) << 32;

	/* convert to बारpec*/
	*ts = ns_to_बारpec64(ns);
	वापस 0;
पूर्ण

/**
 *  cxgb4_ptp_समय_रखो - Set the current समय on the hardware घड़ी
 *  @ptp: ptp घड़ी काष्ठाure
 *  @ts: बारpec containing the new समय क्रम the cycle counter
 *
 *  Reset value to new base value instead of the kernel
 *  wall समयr value.
 */
अटल पूर्णांक cxgb4_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			     स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा adapter *adapter = (काष्ठा adapter *)container_of(ptp,
				   काष्ठा adapter, ptp_घड़ी_info);
	काष्ठा fw_ptp_cmd c;
	u64 ns;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(0));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.ts.sc = FW_PTP_SC_SET_TIME;

	ns = बारpec64_to_ns(ts);
	c.u.ts.पंचांग = cpu_to_be64(ns);

	err =  t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);

	वापस err;
पूर्ण

अटल व्योम cxgb4_init_ptp_समयr(काष्ठा adapter *adapter)
अणु
	काष्ठा fw_ptp_cmd c;
	पूर्णांक err;

	स_रखो(&c, 0, माप(c));
	c.op_to_portid = cpu_to_be32(FW_CMD_OP_V(FW_PTP_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_WRITE_F |
				     FW_PTP_CMD_PORTID_V(0));
	c.retval_len16 = cpu_to_be32(FW_CMD_LEN16_V(माप(c) / 16));
	c.u.scmd.sc = FW_PTP_SC_INIT_TIMER;

	err = t4_wr_mbox(adapter, adapter->mbox, &c, माप(c), शून्य);
	अगर (err < 0)
		dev_err(adapter->pdev_dev,
			"PTP: %s error %d\n", __func__, -err);
पूर्ण

/**
 * cxgb4_ptp_enable - enable or disable an ancillary feature
 * @ptp: ptp घड़ी काष्ठाure
 * @request: Desired resource to enable or disable
 * @on: Caller passes one to enable or zero to disable
 *
 * Enable (or disable) ancillary features of the PHC subप्रणाली.
 * Currently, no ancillary features are supported.
 */
अटल पूर्णांक cxgb4_ptp_enable(काष्ठा ptp_घड़ी_info __always_unused *ptp,
			    काष्ठा ptp_घड़ी_request __always_unused *request,
			    पूर्णांक __always_unused on)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info cxgb4_ptp_घड़ी_info = अणु
	.owner          = THIS_MODULE,
	.name           = "cxgb4_clock",
	.max_adj        = MAX_PTP_FREQ_ADJ,
	.n_alarm        = 0,
	.n_ext_ts       = 0,
	.n_per_out      = 0,
	.pps            = 0,
	.adjfreq        = cxgb4_ptp_adjfreq,
	.adjसमय        = cxgb4_ptp_adjसमय,
	.समय_लो64      = cxgb4_ptp_समय_लो,
	.समय_रखो64      = cxgb4_ptp_समय_रखो,
	.enable         = cxgb4_ptp_enable,
पूर्ण;

/**
 * cxgb4_ptp_init - initialize PTP क्रम devices which support it
 * @adapter: board निजी काष्ठाure
 *
 * This function perक्रमms the required steps क्रम enabling PTP support.
 */
व्योम cxgb4_ptp_init(काष्ठा adapter *adapter)
अणु
	काष्ठा बारpec64 now;
	 /* no need to create a घड़ी device अगर we alपढ़ोy have one */
	अगर (!IS_ERR_OR_शून्य(adapter->ptp_घड़ी))
		वापस;

	adapter->ptp_tx_skb = शून्य;
	adapter->ptp_घड़ी_info = cxgb4_ptp_घड़ी_info;
	spin_lock_init(&adapter->ptp_lock);

	adapter->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&adapter->ptp_घड़ी_info,
						&adapter->pdev->dev);
	अगर (IS_ERR_OR_शून्य(adapter->ptp_घड़ी)) अणु
		adapter->ptp_घड़ी = शून्य;
		dev_err(adapter->pdev_dev,
			"PTP %s Clock registration has failed\n", __func__);
		वापस;
	पूर्ण

	now = kसमय_प्रकारo_बारpec64(kसमय_get_real());
	cxgb4_init_ptp_समयr(adapter);
	अगर (cxgb4_ptp_समय_रखो(&adapter->ptp_घड़ी_info, &now) < 0) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		adapter->ptp_घड़ी = शून्य;
	पूर्ण
पूर्ण

/**
 * cxgb4_ptp_हटाओ - disable PTP device and stop the overflow check
 * @adapter: board निजी काष्ठाure
 *
 * Stop the PTP support.
 */
व्योम cxgb4_ptp_stop(काष्ठा adapter *adapter)
अणु
	अगर (adapter->ptp_tx_skb) अणु
		dev_kमुक्त_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = शून्य;
	पूर्ण

	अगर (adapter->ptp_घड़ी) अणु
		ptp_घड़ी_unरेजिस्टर(adapter->ptp_घड़ी);
		adapter->ptp_घड़ी = शून्य;
	पूर्ण
पूर्ण
