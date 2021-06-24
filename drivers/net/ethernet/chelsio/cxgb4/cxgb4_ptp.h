<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
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
 */

#अगर_अघोषित __CXGB4_PTP_H__
#घोषणा __CXGB4_PTP_H__

/* Maximum parts-per-billion adjusपंचांगent that is acceptable */
#घोषणा MAX_PTP_FREQ_ADJ		1000000
#घोषणा PTP_CLOCK_MAX_ADJTIME		10000000 /* 10 ms */

#घोषणा PTP_MIN_LENGTH			63
#घोषणा PTP_IN_TRANSMIT_PACKET_MAXNUM	240
#घोषणा PTP_EVENT_PORT			319

क्रमागत ptp_rx_filter_mode अणु
	PTP_TS_NONE = 0,
	PTP_TS_L2,
	PTP_TS_L4,
	PTP_TS_L2_L4
पूर्ण;

काष्ठा port_info;

अटल अंतरभूत bool cxgb4_xmit_with_hwtstamp(काष्ठा sk_buff *skb)
अणु
	वापस skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP;
पूर्ण

अटल अंतरभूत व्योम cxgb4_xmit_hwtstamp_pending(काष्ठा sk_buff *skb)
अणु
	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
पूर्ण

व्योम cxgb4_ptp_init(काष्ठा adapter *adap);
व्योम cxgb4_ptp_stop(काष्ठा adapter *adap);
bool cxgb4_ptp_is_ptp_tx(काष्ठा sk_buff *skb);
bool cxgb4_ptp_is_ptp_rx(काष्ठा sk_buff *skb);
पूर्णांक cxgb4_ptprx_बारtamping(काष्ठा port_info *pi, u8 port, u16 mode);
पूर्णांक cxgb4_ptp_redirect_rx_packet(काष्ठा adapter *adap, काष्ठा port_info *pi);
पूर्णांक cxgb4_ptp_txtype(काष्ठा adapter *adap, u8 port_id);
व्योम cxgb4_ptp_पढ़ो_hwstamp(काष्ठा adapter *adap, काष्ठा port_info *pi);
bool is_ptp_enabled(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
#पूर्ण_अगर /* __CXGB4_PTP_H__ */
