<शैली गुरु>
#अगर_अघोषित _QP_H
#घोषणा _QP_H
/*
 * Copyright(c) 2015 - 2018 Intel Corporation.
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

#समावेश <linux/hash.h>
#समावेश <rdma/rdmavt_qp.h>
#समावेश "verbs.h"
#समावेश "sdma.h"
#समावेश "verbs_txreq.h"

बाह्य अचिन्हित पूर्णांक hfi1_qp_table_size;

बाह्य स्थिर काष्ठा rvt_operation_params hfi1_post_parms[];

/*
 * Driver specअगरic s_flags starting at bit 31 करोwn to HFI1_S_MIN_BIT_MASK
 *
 * HFI1_S_AHG_VALID - ahg header valid on chip
 * HFI1_S_AHG_CLEAR - have send engine clear ahg state
 * HFI1_S_WAIT_PIO_DRAIN - qp रुकोing क्रम PIOs to drain
 * HFI1_S_WAIT_TID_SPACE - a QP is रुकोing क्रम TID resource
 * HFI1_S_WAIT_TID_RESP - रुकोing क्रम a TID RDMA WRITE response
 * HFI1_S_WAIT_HALT - halt the first leg send engine
 * HFI1_S_MIN_BIT_MASK - the lowest bit that can be used by hfi1
 */
#घोषणा HFI1_S_AHG_VALID         0x80000000
#घोषणा HFI1_S_AHG_CLEAR         0x40000000
#घोषणा HFI1_S_WAIT_PIO_DRAIN    0x20000000
#घोषणा HFI1_S_WAIT_TID_SPACE    0x10000000
#घोषणा HFI1_S_WAIT_TID_RESP     0x08000000
#घोषणा HFI1_S_WAIT_HALT         0x04000000
#घोषणा HFI1_S_MIN_BIT_MASK      0x01000000

/*
 * overload रुको defines
 */

#घोषणा HFI1_S_ANY_WAIT_IO (RVT_S_ANY_WAIT_IO | HFI1_S_WAIT_PIO_DRAIN)
#घोषणा HFI1_S_ANY_WAIT (HFI1_S_ANY_WAIT_IO | RVT_S_ANY_WAIT_SEND)
#घोषणा HFI1_S_ANY_TID_WAIT_SEND (RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_DMA)

/*
 * Send अगर not busy or रुकोing क्रम I/O and either
 * a RC response is pending or we can process send work requests.
 */
अटल अंतरभूत पूर्णांक hfi1_send_ok(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	वापस !(qp->s_flags & (RVT_S_BUSY | HFI1_S_ANY_WAIT_IO)) &&
		(verbs_txreq_queued(ioरुको_get_ib_work(&priv->s_ioरुको)) ||
		(qp->s_flags & RVT_S_RESP_PENDING) ||
		 !(qp->s_flags & RVT_S_ANY_WAIT_SEND));
पूर्ण

/*
 * मुक्त_ahg - clear ahg from QP
 */
अटल अंतरभूत व्योम clear_ahg(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	priv->s_ahg->ahgcount = 0;
	qp->s_flags &= ~(HFI1_S_AHG_VALID | HFI1_S_AHG_CLEAR);
	अगर (priv->s_sde && qp->s_ahgidx >= 0)
		sdma_ahg_मुक्त(priv->s_sde, qp->s_ahgidx);
	qp->s_ahgidx = -1;
पूर्ण

/**
 * hfi1_qp_wakeup - wake up on the indicated event
 * @qp: the QP
 * @flag: flag the qp on which the qp is stalled
 */
व्योम hfi1_qp_wakeup(काष्ठा rvt_qp *qp, u32 flag);

काष्ठा sdma_engine *qp_to_sdma_engine(काष्ठा rvt_qp *qp, u8 sc5);
काष्ठा send_context *qp_to_send_context(काष्ठा rvt_qp *qp, u8 sc5);

व्योम qp_iter_prपूर्णांक(काष्ठा seq_file *s, काष्ठा rvt_qp_iter *iter);

bool _hfi1_schedule_send(काष्ठा rvt_qp *qp);
bool hfi1_schedule_send(काष्ठा rvt_qp *qp);

व्योम hfi1_migrate_qp(काष्ठा rvt_qp *qp);

/*
 * Functions provided by hfi1 driver क्रम rdmavt to use
 */
व्योम *qp_priv_alloc(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);
व्योम qp_priv_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);
अचिन्हित मुक्त_all_qps(काष्ठा rvt_dev_info *rdi);
व्योम notअगरy_qp_reset(काष्ठा rvt_qp *qp);
पूर्णांक get_pmtu_from_attr(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
		       काष्ठा ib_qp_attr *attr);
व्योम flush_qp_रुकोers(काष्ठा rvt_qp *qp);
व्योम notअगरy_error_qp(काष्ठा rvt_qp *qp);
व्योम stop_send_queue(काष्ठा rvt_qp *qp);
व्योम quiesce_qp(काष्ठा rvt_qp *qp);
u32 mtu_from_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp, u32 pmtu);
पूर्णांक mtu_to_path_mtu(u32 mtu);
व्योम hfi1_error_port_qps(काष्ठा hfi1_ibport *ibp, u8 sl);
व्योम hfi1_qp_unbusy(काष्ठा rvt_qp *qp, काष्ठा ioरुको_work *रुको);
#पूर्ण_अगर /* _QP_H */
