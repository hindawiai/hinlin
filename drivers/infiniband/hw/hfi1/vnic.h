<शैली गुरु>
#अगर_अघोषित _HFI1_VNIC_H
#घोषणा _HFI1_VNIC_H
/*
 * Copyright(c) 2017 - 2020 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <rdma/opa_vnic.h>
#समावेश "hfi.h"
#समावेश "sdma.h"

#घोषणा HFI1_VNIC_MAX_TXQ     16
#घोषणा HFI1_VNIC_MAX_PAD     12

/* L4 header definitions */
#घोषणा HFI1_VNIC_L4_HDR_OFFSET  OPA_VNIC_L2_HDR_LEN

#घोषणा HFI1_VNIC_GET_L4_HDR(data)   \
	(*((u16 *)((u8 *)(data) + HFI1_VNIC_L4_HDR_OFFSET)))

#घोषणा HFI1_VNIC_GET_VESWID(data)   \
	(HFI1_VNIC_GET_L4_HDR(data) & 0xFFF)

/* Service class */
#घोषणा HFI1_VNIC_SC_OFFSET_LOW 6
#घोषणा HFI1_VNIC_SC_OFFSET_HI  7
#घोषणा HFI1_VNIC_SC_SHIFT      4

#घोषणा HFI1_VNIC_MAX_QUEUE 16
#घोषणा HFI1_NUM_VNIC_CTXT 8

/**
 * काष्ठा hfi1_vnic_sdma - VNIC per Tx ring SDMA inक्रमmation
 * @dd - device data poपूर्णांकer
 * @sde - sdma engine
 * @vinfo - vnic info poपूर्णांकer
 * @रुको - ioरुको काष्ठाure
 * @stx - sdma tx request
 * @state - vnic Tx ring SDMA state
 * @q_idx - vnic Tx queue index
 */
काष्ठा hfi1_vnic_sdma अणु
	काष्ठा hfi1_devdata *dd;
	काष्ठा sdma_engine  *sde;
	काष्ठा hfi1_vnic_vport_info *vinfo;
	काष्ठा ioरुको रुको;
	काष्ठा sdma_txreq stx;
	अचिन्हित पूर्णांक state;
	u8 q_idx;
	bool pkts_sent;
पूर्ण;

/**
 * काष्ठा hfi1_vnic_rx_queue - HFI1 VNIC receive queue
 * @idx: queue index
 * @vinfo: poपूर्णांकer to vport inक्रमmation
 * @netdev: network device
 * @napi: netdev napi काष्ठाure
 * @skbq: queue of received socket buffers
 */
काष्ठा hfi1_vnic_rx_queue अणु
	u8                           idx;
	काष्ठा hfi1_vnic_vport_info *vinfo;
	काष्ठा net_device           *netdev;
	काष्ठा napi_काष्ठा           napi;
पूर्ण;

/**
 * काष्ठा hfi1_vnic_vport_info - HFI1 VNIC भव port inक्रमmation
 * @dd: device data poपूर्णांकer
 * @netdev: net device poपूर्णांकer
 * @flags: state flags
 * @lock: vport lock
 * @num_tx_q: number of transmit queues
 * @num_rx_q: number of receive queues
 * @vesw_id: भव चयन id
 * @rxq: Array of receive queues
 * @stats: per queue stats
 * @sdma: VNIC SDMA काष्ठाure per TXQ
 */
काष्ठा hfi1_vnic_vport_info अणु
	काष्ठा hfi1_devdata *dd;
	काष्ठा net_device   *netdev;
	अचिन्हित दीर्घ        flags;

	/* Lock used around state updates */
	काष्ठा mutex         lock;

	u8  num_tx_q;
	u8  num_rx_q;
	u16 vesw_id;
	काष्ठा hfi1_vnic_rx_queue rxq[HFI1_NUM_VNIC_CTXT];

	काष्ठा opa_vnic_stats  stats[HFI1_VNIC_MAX_QUEUE];
	काष्ठा hfi1_vnic_sdma  sdma[HFI1_VNIC_MAX_TXQ];
पूर्ण;

#घोषणा v_dbg(क्रमmat, arg...) \
	netdev_dbg(vinfo->netdev, क्रमmat, ## arg)
#घोषणा v_err(क्रमmat, arg...) \
	netdev_err(vinfo->netdev, क्रमmat, ## arg)
#घोषणा v_info(क्रमmat, arg...) \
	netdev_info(vinfo->netdev, क्रमmat, ## arg)

/* vnic hfi1 पूर्णांकernal functions */
व्योम hfi1_vnic_setup(काष्ठा hfi1_devdata *dd);
पूर्णांक hfi1_vnic_txreq_init(काष्ठा hfi1_devdata *dd);
व्योम hfi1_vnic_txreq_deinit(काष्ठा hfi1_devdata *dd);

व्योम hfi1_vnic_bypass_rcv(काष्ठा hfi1_packet *packet);
व्योम hfi1_vnic_sdma_init(काष्ठा hfi1_vnic_vport_info *vinfo);
bool hfi1_vnic_sdma_ग_लिखो_avail(काष्ठा hfi1_vnic_vport_info *vinfo,
				u8 q_idx);

/* vnic rdma netdev operations */
काष्ठा net_device *hfi1_vnic_alloc_rn(काष्ठा ib_device *device,
				      u32 port_num,
				      क्रमागत rdma_netdev_t type,
				      स्थिर अक्षर *name,
				      अचिन्हित अक्षर name_assign_type,
				      व्योम (*setup)(काष्ठा net_device *));
पूर्णांक hfi1_vnic_send_dma(काष्ठा hfi1_devdata *dd, u8 q_idx,
		       काष्ठा hfi1_vnic_vport_info *vinfo,
		       काष्ठा sk_buff *skb, u64 pbc, u8 plen);

#पूर्ण_अगर /* _HFI1_VNIC_H */
