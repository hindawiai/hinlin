<शैली गुरु>
/*
 * This file is part of the Chelsio T4/T5/T6 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2017 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __T4_TCB_H
#घोषणा __T4_TCB_H

#घोषणा TCB_L2T_IX_W		0
#घोषणा TCB_L2T_IX_S		12
#घोषणा TCB_L2T_IX_M		0xfffULL
#घोषणा TCB_L2T_IX_V(x)		((x) << TCB_L2T_IX_S)

#घोषणा TCB_T_FLAGS_W           1
#घोषणा TCB_T_FLAGS_S           0
#घोषणा TCB_T_FLAGS_M           0xffffffffffffffffULL
#घोषणा TCB_T_FLAGS_V(x)        ((__u64)(x) << TCB_T_FLAGS_S)

#घोषणा TCB_FIELD_COOKIE_TFLAG	1

#घोषणा TCB_SMAC_SEL_W		0
#घोषणा TCB_SMAC_SEL_S		24
#घोषणा TCB_SMAC_SEL_M		0xffULL
#घोषणा TCB_SMAC_SEL_V(x)	((x) << TCB_SMAC_SEL_S)

#घोषणा TCB_T_FLAGS_W		1
#घोषणा TCB_T_FLAGS_S		0
#घोषणा TCB_T_FLAGS_M		0xffffffffffffffffULL
#घोषणा TCB_T_FLAGS_V(x)	((__u64)(x) << TCB_T_FLAGS_S)

#घोषणा TF_DROP_S		22
#घोषणा TF_सूचीECT_STEER_S	23
#घोषणा TF_LPBK_S		59

#घोषणा TF_CCTRL_ECE_S		60
#घोषणा TF_CCTRL_CWR_S		61
#घोषणा TF_CCTRL_RFR_S		62

#घोषणा TCB_RSS_INFO_W		3
#घोषणा TCB_RSS_INFO_S		0
#घोषणा TCB_RSS_INFO_M		0x3ffULL
#घोषणा TCB_RSS_INFO_V(x)	((x) << TCB_RSS_INFO_S)

#घोषणा TCB_T_STATE_W		3
#घोषणा TCB_T_STATE_S		16
#घोषणा TCB_T_STATE_M		0xfULL
#घोषणा TCB_T_STATE_V(x)	((x) << TCB_T_STATE_S)

#घोषणा TCB_TIMESTAMP_W		5
#घोषणा TCB_TIMESTAMP_S		0
#घोषणा TCB_TIMESTAMP_M		0xffffffffULL
#घोषणा TCB_TIMESTAMP_V(x)	((x) << TCB_TIMESTAMP_S)

#घोषणा TCB_RTT_TS_RECENT_AGE_W		6
#घोषणा TCB_RTT_TS_RECENT_AGE_S		0
#घोषणा TCB_RTT_TS_RECENT_AGE_M		0xffffffffULL
#घोषणा TCB_RTT_TS_RECENT_AGE_V(x)	((x) << TCB_RTT_TS_RECENT_AGE_S)

#घोषणा TCB_T_RTSEQ_RECENT_W    7
#घोषणा TCB_T_RTSEQ_RECENT_S    0
#घोषणा TCB_T_RTSEQ_RECENT_M    0xffffffffULL
#घोषणा TCB_T_RTSEQ_RECENT_V(x) ((x) << TCB_T_RTSEQ_RECENT_S)

#घोषणा TCB_TX_MAX_W		9
#घोषणा TCB_TX_MAX_S		0
#घोषणा TCB_TX_MAX_M		0xffffffffULL
#घोषणा TCB_TX_MAX_V(x)		((x) << TCB_TX_MAX_S)

#घोषणा TCB_SND_UNA_RAW_W	10
#घोषणा TCB_SND_UNA_RAW_S	0
#घोषणा TCB_SND_UNA_RAW_M	0xfffffffULL
#घोषणा TCB_SND_UNA_RAW_V(x)	((x) << TCB_SND_UNA_RAW_S)

#घोषणा TCB_SND_NXT_RAW_W	10
#घोषणा TCB_SND_NXT_RAW_S	28
#घोषणा TCB_SND_NXT_RAW_M	0xfffffffULL
#घोषणा TCB_SND_NXT_RAW_V(x)	((x) << TCB_SND_NXT_RAW_S)

#घोषणा TCB_SND_MAX_RAW_W	11
#घोषणा TCB_SND_MAX_RAW_S	24
#घोषणा TCB_SND_MAX_RAW_M	0xfffffffULL
#घोषणा TCB_SND_MAX_RAW_V(x)	((x) << TCB_SND_MAX_RAW_S)

#घोषणा TCB_RCV_NXT_W		16
#घोषणा TCB_RCV_NXT_S		10
#घोषणा TCB_RCV_NXT_M		0xffffffffULL
#घोषणा TCB_RCV_NXT_V(x)	((x) << TCB_RCV_NXT_S)

#घोषणा TCB_RCV_WND_W		17
#घोषणा TCB_RCV_WND_S		10
#घोषणा TCB_RCV_WND_M		0xffffffULL
#घोषणा TCB_RCV_WND_V(x)	((x) << TCB_RCV_WND_S)

#घोषणा TCB_RX_FRAG2_PTR_RAW_W	27
#घोषणा TCB_RX_FRAG3_LEN_RAW_W	29
#घोषणा TCB_RX_FRAG3_START_IDX_OFFSET_RAW_W	30
#घोषणा TCB_PDU_HDR_LEN_W	31

#घोषणा TCB_RQ_START_W		30
#घोषणा TCB_RQ_START_S		0
#घोषणा TCB_RQ_START_M		0x3ffffffULL
#घोषणा TCB_RQ_START_V(x)	((x) << TCB_RQ_START_S)

#घोषणा TF_RX_PDU_OUT_S		49
#घोषणा TF_RX_PDU_OUT_V(x)	((__u64)(x) << TF_RX_PDU_OUT_S)

#घोषणा TF_CORE_BYPASS_S	63
#घोषणा TF_CORE_BYPASS_V(x)	((__u64)(x) << TF_CORE_BYPASS_S)
#घोषणा TF_CORE_BYPASS_F	TF_CORE_BYPASS_V(1)

#घोषणा TF_NON_OFFLOAD_S	1
#घोषणा TF_NON_OFFLOAD_V(x)	((x) << TF_NON_OFFLOAD_S)
#घोषणा TF_NON_OFFLOAD_F	TF_NON_OFFLOAD_V(1)

#पूर्ण_अगर /* __T4_TCB_H */
