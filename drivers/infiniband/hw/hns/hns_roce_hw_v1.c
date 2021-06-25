<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
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

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hem.h"
#समावेश "hns_roce_hw_v1.h"

/**
 * hns_get_gid_index - Get gid index.
 * @hr_dev: poपूर्णांकer to काष्ठाure hns_roce_dev.
 * @port:  port, value range: 0 ~ MAX
 * @gid_index:  gid_index, value range: 0 ~ MAX
 * Description:
 *    N ports shared gids, allocation method as follow:
 *		GID[0][0], GID[1][0],.....GID[N - 1][0],
 *		GID[0][0], GID[1][0],.....GID[N - 1][0],
 *		And so on
 */
u8 hns_get_gid_index(काष्ठा hns_roce_dev *hr_dev, u32 port, पूर्णांक gid_index)
अणु
	वापस gid_index * hr_dev->caps.num_ports + port;
पूर्ण

अटल व्योम set_data_seg(काष्ठा hns_roce_wqe_data_seg *dseg, काष्ठा ib_sge *sg)
अणु
	dseg->lkey = cpu_to_le32(sg->lkey);
	dseg->addr = cpu_to_le64(sg->addr);
	dseg->len  = cpu_to_le32(sg->length);
पूर्ण

अटल व्योम set_raddr_seg(काष्ठा hns_roce_wqe_raddr_seg *rseg, u64 remote_addr,
			  u32 rkey)
अणु
	rseg->raddr = cpu_to_le64(remote_addr);
	rseg->rkey  = cpu_to_le32(rkey);
	rseg->len   = 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_post_send(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_send_wr *wr,
				 स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_ah *ah = to_hr_ah(ud_wr(wr)->ah);
	काष्ठा hns_roce_ud_send_wqe *ud_sq_wqe = शून्य;
	काष्ठा hns_roce_wqe_ctrl_seg *ctrl = शून्य;
	काष्ठा hns_roce_wqe_data_seg *dseg = शून्य;
	काष्ठा hns_roce_qp *qp = to_hr_qp(ibqp);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_sq_db sq_db = अणुपूर्ण;
	पूर्णांक ps_opcode, i;
	अचिन्हित दीर्घ flags = 0;
	व्योम *wqe = शून्य;
	__le32 करोorbell[2];
	पूर्णांक ret = 0;
	पूर्णांक loopback;
	u32 wqe_idx;
	पूर्णांक nreq;
	u8 *smac;

	अगर (unlikely(ibqp->qp_type != IB_QPT_GSI &&
		ibqp->qp_type != IB_QPT_RC)) अणु
		dev_err(dev, "un-supported QP type\n");
		*bad_wr = शून्य;
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_irqsave(&qp->sq.lock, flags);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (hns_roce_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) अणु
			ret = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe_idx = (qp->sq.head + nreq) & (qp->sq.wqe_cnt - 1);

		अगर (unlikely(wr->num_sge > qp->sq.max_gs)) अणु
			dev_err(dev, "num_sge=%d > qp->sq.max_gs=%d\n",
				wr->num_sge, qp->sq.max_gs);
			ret = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = hns_roce_get_send_wqe(qp, wqe_idx);
		qp->sq.wrid[wqe_idx] = wr->wr_id;

		/* Corresponding to the RC and RD type wqe process separately */
		अगर (ibqp->qp_type == IB_QPT_GSI) अणु
			ud_sq_wqe = wqe;
			roce_set_field(ud_sq_wqe->dmac_h,
				       UD_SEND_WQE_U32_4_DMAC_0_M,
				       UD_SEND_WQE_U32_4_DMAC_0_S,
				       ah->av.mac[0]);
			roce_set_field(ud_sq_wqe->dmac_h,
				       UD_SEND_WQE_U32_4_DMAC_1_M,
				       UD_SEND_WQE_U32_4_DMAC_1_S,
				       ah->av.mac[1]);
			roce_set_field(ud_sq_wqe->dmac_h,
				       UD_SEND_WQE_U32_4_DMAC_2_M,
				       UD_SEND_WQE_U32_4_DMAC_2_S,
				       ah->av.mac[2]);
			roce_set_field(ud_sq_wqe->dmac_h,
				       UD_SEND_WQE_U32_4_DMAC_3_M,
				       UD_SEND_WQE_U32_4_DMAC_3_S,
				       ah->av.mac[3]);

			roce_set_field(ud_sq_wqe->u32_8,
				       UD_SEND_WQE_U32_8_DMAC_4_M,
				       UD_SEND_WQE_U32_8_DMAC_4_S,
				       ah->av.mac[4]);
			roce_set_field(ud_sq_wqe->u32_8,
				       UD_SEND_WQE_U32_8_DMAC_5_M,
				       UD_SEND_WQE_U32_8_DMAC_5_S,
				       ah->av.mac[5]);

			smac = (u8 *)hr_dev->dev_addr[qp->port];
			loopback = ether_addr_equal_unaligned(ah->av.mac,
							      smac) ? 1 : 0;
			roce_set_bit(ud_sq_wqe->u32_8,
				     UD_SEND_WQE_U32_8_LOOPBACK_INDICATOR_S,
				     loopback);

			roce_set_field(ud_sq_wqe->u32_8,
				       UD_SEND_WQE_U32_8_OPERATION_TYPE_M,
				       UD_SEND_WQE_U32_8_OPERATION_TYPE_S,
				       HNS_ROCE_WQE_OPCODE_SEND);
			roce_set_field(ud_sq_wqe->u32_8,
				       UD_SEND_WQE_U32_8_NUMBER_OF_DATA_SEG_M,
				       UD_SEND_WQE_U32_8_NUMBER_OF_DATA_SEG_S,
				       2);
			roce_set_bit(ud_sq_wqe->u32_8,
				UD_SEND_WQE_U32_8_SEND_GL_ROUTING_HDR_FLAG_S,
				1);

			ud_sq_wqe->u32_8 |= (wr->send_flags & IB_SEND_SIGNALED ?
				cpu_to_le32(HNS_ROCE_WQE_CQ_NOTIFY) : 0) |
				(wr->send_flags & IB_SEND_SOLICITED ?
				cpu_to_le32(HNS_ROCE_WQE_SE) : 0) |
				((wr->opcode == IB_WR_SEND_WITH_IMM) ?
				cpu_to_le32(HNS_ROCE_WQE_IMM) : 0);

			roce_set_field(ud_sq_wqe->u32_16,
				       UD_SEND_WQE_U32_16_DEST_QP_M,
				       UD_SEND_WQE_U32_16_DEST_QP_S,
				       ud_wr(wr)->remote_qpn);
			roce_set_field(ud_sq_wqe->u32_16,
				       UD_SEND_WQE_U32_16_MAX_STATIC_RATE_M,
				       UD_SEND_WQE_U32_16_MAX_STATIC_RATE_S,
				       ah->av.stat_rate);

			roce_set_field(ud_sq_wqe->u32_36,
				       UD_SEND_WQE_U32_36_FLOW_LABEL_M,
				       UD_SEND_WQE_U32_36_FLOW_LABEL_S,
				       ah->av.flowlabel);
			roce_set_field(ud_sq_wqe->u32_36,
				      UD_SEND_WQE_U32_36_PRIORITY_M,
				      UD_SEND_WQE_U32_36_PRIORITY_S,
				      ah->av.sl);
			roce_set_field(ud_sq_wqe->u32_36,
				       UD_SEND_WQE_U32_36_SGID_INDEX_M,
				       UD_SEND_WQE_U32_36_SGID_INDEX_S,
				       hns_get_gid_index(hr_dev, qp->phy_port,
							 ah->av.gid_index));

			roce_set_field(ud_sq_wqe->u32_40,
				       UD_SEND_WQE_U32_40_HOP_LIMIT_M,
				       UD_SEND_WQE_U32_40_HOP_LIMIT_S,
				       ah->av.hop_limit);
			roce_set_field(ud_sq_wqe->u32_40,
				       UD_SEND_WQE_U32_40_TRAFFIC_CLASS_M,
				       UD_SEND_WQE_U32_40_TRAFFIC_CLASS_S,
				       ah->av.tclass);

			स_नकल(&ud_sq_wqe->dgid[0], &ah->av.dgid[0], GID_LEN);

			ud_sq_wqe->va0_l =
				       cpu_to_le32((u32)wr->sg_list[0].addr);
			ud_sq_wqe->va0_h =
				       cpu_to_le32((wr->sg_list[0].addr) >> 32);
			ud_sq_wqe->l_key0 =
				       cpu_to_le32(wr->sg_list[0].lkey);

			ud_sq_wqe->va1_l =
				       cpu_to_le32((u32)wr->sg_list[1].addr);
			ud_sq_wqe->va1_h =
				       cpu_to_le32((wr->sg_list[1].addr) >> 32);
			ud_sq_wqe->l_key1 =
				       cpu_to_le32(wr->sg_list[1].lkey);
		पूर्ण अन्यथा अगर (ibqp->qp_type == IB_QPT_RC) अणु
			u32 पंचांगp_len = 0;

			ctrl = wqe;
			स_रखो(ctrl, 0, माप(काष्ठा hns_roce_wqe_ctrl_seg));
			क्रम (i = 0; i < wr->num_sge; i++)
				पंचांगp_len += wr->sg_list[i].length;

			ctrl->msg_length =
			  cpu_to_le32(le32_to_cpu(ctrl->msg_length) + पंचांगp_len);

			ctrl->sgl_pa_h = 0;
			ctrl->flag = 0;

			चयन (wr->opcode) अणु
			हाल IB_WR_SEND_WITH_IMM:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				ctrl->imm_data = wr->ex.imm_data;
				अवरोध;
			हाल IB_WR_SEND_WITH_INV:
				ctrl->inv_key =
					cpu_to_le32(wr->ex.invalidate_rkey);
				अवरोध;
			शेष:
				ctrl->imm_data = 0;
				अवरोध;
			पूर्ण

			/* Ctrl field, ctrl set type: sig, solic, imm, fence */
			/* SO रुको क्रम conक्रमming application scenarios */
			ctrl->flag |= (wr->send_flags & IB_SEND_SIGNALED ?
				      cpu_to_le32(HNS_ROCE_WQE_CQ_NOTIFY) : 0) |
				      (wr->send_flags & IB_SEND_SOLICITED ?
				      cpu_to_le32(HNS_ROCE_WQE_SE) : 0) |
				      ((wr->opcode == IB_WR_SEND_WITH_IMM ||
				      wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM) ?
				      cpu_to_le32(HNS_ROCE_WQE_IMM) : 0) |
				      (wr->send_flags & IB_SEND_FENCE ?
				      (cpu_to_le32(HNS_ROCE_WQE_FENCE)) : 0);

			wqe += माप(काष्ठा hns_roce_wqe_ctrl_seg);

			चयन (wr->opcode) अणु
			हाल IB_WR_RDMA_READ:
				ps_opcode = HNS_ROCE_WQE_OPCODE_RDMA_READ;
				set_raddr_seg(wqe,  rdma_wr(wr)->remote_addr,
					       rdma_wr(wr)->rkey);
				अवरोध;
			हाल IB_WR_RDMA_WRITE:
			हाल IB_WR_RDMA_WRITE_WITH_IMM:
				ps_opcode = HNS_ROCE_WQE_OPCODE_RDMA_WRITE;
				set_raddr_seg(wqe,  rdma_wr(wr)->remote_addr,
					      rdma_wr(wr)->rkey);
				अवरोध;
			हाल IB_WR_SEND:
			हाल IB_WR_SEND_WITH_INV:
			हाल IB_WR_SEND_WITH_IMM:
				ps_opcode = HNS_ROCE_WQE_OPCODE_SEND;
				अवरोध;
			हाल IB_WR_LOCAL_INV:
			हाल IB_WR_ATOMIC_CMP_AND_SWP:
			हाल IB_WR_ATOMIC_FETCH_AND_ADD:
			हाल IB_WR_LSO:
			शेष:
				ps_opcode = HNS_ROCE_WQE_OPCODE_MASK;
				अवरोध;
			पूर्ण
			ctrl->flag |= cpu_to_le32(ps_opcode);
			wqe += माप(काष्ठा hns_roce_wqe_raddr_seg);

			dseg = wqe;
			अगर (wr->send_flags & IB_SEND_INLINE && wr->num_sge) अणु
				अगर (le32_to_cpu(ctrl->msg_length) >
				    hr_dev->caps.max_sq_अंतरभूत) अणु
					ret = -EINVAL;
					*bad_wr = wr;
					dev_err(dev, "inline len(1-%d)=%d, illegal",
						le32_to_cpu(ctrl->msg_length),
						hr_dev->caps.max_sq_अंतरभूत);
					जाओ out;
				पूर्ण
				क्रम (i = 0; i < wr->num_sge; i++) अणु
					स_नकल(wqe, ((व्योम *) (uपूर्णांकptr_t)
					       wr->sg_list[i].addr),
					       wr->sg_list[i].length);
					wqe += wr->sg_list[i].length;
				पूर्ण
				ctrl->flag |= cpu_to_le32(HNS_ROCE_WQE_INLINE);
			पूर्ण अन्यथा अणु
				/* sqe num is two */
				क्रम (i = 0; i < wr->num_sge; i++)
					set_data_seg(dseg + i, wr->sg_list + i);

				ctrl->flag |= cpu_to_le32(wr->num_sge <<
					      HNS_ROCE_WQE_SGE_NUM_BIT);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	/* Set DB वापस */
	अगर (likely(nreq)) अणु
		qp->sq.head += nreq;

		roce_set_field(sq_db.u32_4, SQ_DOORBELL_U32_4_SQ_HEAD_M,
			       SQ_DOORBELL_U32_4_SQ_HEAD_S,
			      (qp->sq.head & ((qp->sq.wqe_cnt << 1) - 1)));
		roce_set_field(sq_db.u32_4, SQ_DOORBELL_U32_4_SL_M,
			       SQ_DOORBELL_U32_4_SL_S, qp->sl);
		roce_set_field(sq_db.u32_4, SQ_DOORBELL_U32_4_PORT_M,
			       SQ_DOORBELL_U32_4_PORT_S, qp->phy_port);
		roce_set_field(sq_db.u32_8, SQ_DOORBELL_U32_8_QPN_M,
			       SQ_DOORBELL_U32_8_QPN_S, qp->करोorbell_qpn);
		roce_set_bit(sq_db.u32_8, SQ_DOORBELL_HW_SYNC_S, 1);

		करोorbell[0] = sq_db.u32_4;
		करोorbell[1] = sq_db.u32_8;

		hns_roce_ग_लिखो64_k(करोorbell, qp->sq.db_reg);
	पूर्ण

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_post_recv(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_recv_wr *wr,
				 स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा hns_roce_rq_wqe_ctrl *ctrl = शून्य;
	काष्ठा hns_roce_wqe_data_seg *scat = शून्य;
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_rq_db rq_db = अणुपूर्ण;
	__le32 करोorbell[2] = अणु0पूर्ण;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक wqe_idx;
	पूर्णांक ret = 0;
	पूर्णांक nreq;
	पूर्णांक i;
	u32 reg_val;

	spin_lock_irqsave(&hr_qp->rq.lock, flags);

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (hns_roce_wq_overflow(&hr_qp->rq, nreq,
			hr_qp->ibqp.recv_cq)) अणु
			ret = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe_idx = (hr_qp->rq.head + nreq) & (hr_qp->rq.wqe_cnt - 1);

		अगर (unlikely(wr->num_sge > hr_qp->rq.max_gs)) अणु
			dev_err(dev, "rq:num_sge=%d > qp->sq.max_gs=%d\n",
				wr->num_sge, hr_qp->rq.max_gs);
			ret = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		ctrl = hns_roce_get_recv_wqe(hr_qp, wqe_idx);

		roce_set_field(ctrl->rwqe_byte_12,
			       RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_M,
			       RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_S,
			       wr->num_sge);

		scat = (काष्ठा hns_roce_wqe_data_seg *)(ctrl + 1);

		क्रम (i = 0; i < wr->num_sge; i++)
			set_data_seg(scat + i, wr->sg_list + i);

		hr_qp->rq.wrid[wqe_idx] = wr->wr_id;
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		hr_qp->rq.head += nreq;

		अगर (ibqp->qp_type == IB_QPT_GSI) अणु
			__le32 पंचांगp;

			/* SW update GSI rq header */
			reg_val = roce_पढ़ो(to_hr_dev(ibqp->device),
					    ROCEE_QP1C_CFG3_0_REG +
					    QP1C_CFGN_OFFSET * hr_qp->phy_port);
			पंचांगp = cpu_to_le32(reg_val);
			roce_set_field(पंचांगp,
				       ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_M,
				       ROCEE_QP1C_CFG3_0_ROCEE_QP1C_RQ_HEAD_S,
				       hr_qp->rq.head);
			reg_val = le32_to_cpu(पंचांगp);
			roce_ग_लिखो(to_hr_dev(ibqp->device),
				   ROCEE_QP1C_CFG3_0_REG +
				   QP1C_CFGN_OFFSET * hr_qp->phy_port, reg_val);
		पूर्ण अन्यथा अणु
			roce_set_field(rq_db.u32_4, RQ_DOORBELL_U32_4_RQ_HEAD_M,
				       RQ_DOORBELL_U32_4_RQ_HEAD_S,
				       hr_qp->rq.head);
			roce_set_field(rq_db.u32_8, RQ_DOORBELL_U32_8_QPN_M,
				       RQ_DOORBELL_U32_8_QPN_S, hr_qp->qpn);
			roce_set_field(rq_db.u32_8, RQ_DOORBELL_U32_8_CMD_M,
				       RQ_DOORBELL_U32_8_CMD_S, 1);
			roce_set_bit(rq_db.u32_8, RQ_DOORBELL_U32_8_HW_SYNC_S,
				     1);

			करोorbell[0] = rq_db.u32_4;
			करोorbell[1] = rq_db.u32_8;

			hns_roce_ग_लिखो64_k(करोorbell, hr_qp->rq.db_reg);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hr_qp->rq.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_set_db_event_mode(काष्ठा hns_roce_dev *hr_dev,
				       पूर्णांक sdb_mode, पूर्णांक odb_mode)
अणु
	__le32 पंचांगp;
	u32 val;

	val = roce_पढ़ो(hr_dev, ROCEE_GLB_CFG_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_bit(पंचांगp, ROCEE_GLB_CFG_ROCEE_DB_SQ_MODE_S, sdb_mode);
	roce_set_bit(पंचांगp, ROCEE_GLB_CFG_ROCEE_DB_OTH_MODE_S, odb_mode);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_GLB_CFG_REG, val);
पूर्ण

अटल व्योम hns_roce_set_db_ext_mode(काष्ठा hns_roce_dev *hr_dev, u32 sdb_mode,
				     u32 odb_mode)
अणु
	__le32 पंचांगp;
	u32 val;

	/* Configure SDB/ODB extend mode */
	val = roce_पढ़ो(hr_dev, ROCEE_GLB_CFG_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_bit(पंचांगp, ROCEE_GLB_CFG_SQ_EXT_DB_MODE_S, sdb_mode);
	roce_set_bit(पंचांगp, ROCEE_GLB_CFG_OTH_EXT_DB_MODE_S, odb_mode);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_GLB_CFG_REG, val);
पूर्ण

अटल व्योम hns_roce_set_sdb(काष्ठा hns_roce_dev *hr_dev, u32 sdb_alept,
			     u32 sdb_alful)
अणु
	__le32 पंचांगp;
	u32 val;

	/* Configure SDB */
	val = roce_पढ़ो(hr_dev, ROCEE_DB_SQ_WL_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_M,
		       ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_S, sdb_alful);
	roce_set_field(पंचांगp, ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_EMPTY_M,
		       ROCEE_DB_SQ_WL_ROCEE_DB_SQ_WL_EMPTY_S, sdb_alept);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_DB_SQ_WL_REG, val);
पूर्ण

अटल व्योम hns_roce_set_odb(काष्ठा hns_roce_dev *hr_dev, u32 odb_alept,
			     u32 odb_alful)
अणु
	__le32 पंचांगp;
	u32 val;

	/* Configure ODB */
	val = roce_पढ़ो(hr_dev, ROCEE_DB_OTHERS_WL_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_M,
		       ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_S, odb_alful);
	roce_set_field(पंचांगp, ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_M,
		       ROCEE_DB_OTHERS_WL_ROCEE_DB_OTH_WL_EMPTY_S, odb_alept);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_DB_OTHERS_WL_REG, val);
पूर्ण

अटल व्योम hns_roce_set_sdb_ext(काष्ठा hns_roce_dev *hr_dev, u32 ext_sdb_alept,
				 u32 ext_sdb_alful)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_db_table *db = &priv->db_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	dma_addr_t sdb_dma_addr;
	__le32 पंचांगp;
	u32 val;

	/* Configure extend SDB threshold */
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_SQ_WL_EMPTY_REG, ext_sdb_alept);
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_SQ_WL_REG, ext_sdb_alful);

	/* Configure extend SDB base addr */
	sdb_dma_addr = db->ext_db->sdb_buf_list->map;
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_SQ_REG, (u32)(sdb_dma_addr >> 12));

	/* Configure extend SDB depth */
	val = roce_पढ़ो(hr_dev, ROCEE_EXT_DB_SQ_H_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_SHIFT_M,
		       ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_SHIFT_S,
		       db->ext_db->esdb_dep);
	/*
	 * 44 = 32 + 12, When evaluating addr to hardware, shअगरt 12 because of
	 * using 4K page, and shअगरt more 32 because of
	 * calculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(पंचांगp, ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_BA_H_M,
		       ROCEE_EXT_DB_SQ_H_EXT_DB_SQ_BA_H_S, sdb_dma_addr >> 44);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_SQ_H_REG, val);

	dev_dbg(dev, "ext SDB depth: 0x%x\n", db->ext_db->esdb_dep);
	dev_dbg(dev, "ext SDB threshold: empty: 0x%x, ful: 0x%x\n",
		ext_sdb_alept, ext_sdb_alful);
पूर्ण

अटल व्योम hns_roce_set_odb_ext(काष्ठा hns_roce_dev *hr_dev, u32 ext_odb_alept,
				 u32 ext_odb_alful)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_db_table *db = &priv->db_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	dma_addr_t odb_dma_addr;
	__le32 पंचांगp;
	u32 val;

	/* Configure extend ODB threshold */
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_OTHERS_WL_EMPTY_REG, ext_odb_alept);
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_OTHERS_WL_REG, ext_odb_alful);

	/* Configure extend ODB base addr */
	odb_dma_addr = db->ext_db->odb_buf_list->map;
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_OTH_REG, (u32)(odb_dma_addr >> 12));

	/* Configure extend ODB depth */
	val = roce_पढ़ो(hr_dev, ROCEE_EXT_DB_OTH_H_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_M,
		       ROCEE_EXT_DB_OTH_H_EXT_DB_OTH_SHIFT_S,
		       db->ext_db->eodb_dep);
	roce_set_field(पंचांगp, ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_M,
		       ROCEE_EXT_DB_SQ_H_EXT_DB_OTH_BA_H_S,
		       db->ext_db->eodb_dep);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_EXT_DB_OTH_H_REG, val);

	dev_dbg(dev, "ext ODB depth: 0x%x\n", db->ext_db->eodb_dep);
	dev_dbg(dev, "ext ODB threshold: empty: 0x%x, ful: 0x%x\n",
		ext_odb_alept, ext_odb_alful);
पूर्ण

अटल पूर्णांक hns_roce_db_ext_init(काष्ठा hns_roce_dev *hr_dev, u32 sdb_ext_mod,
				u32 odb_ext_mod)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_db_table *db = &priv->db_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	dma_addr_t sdb_dma_addr;
	dma_addr_t odb_dma_addr;
	पूर्णांक ret = 0;

	db->ext_db = kदो_स्मृति(माप(*db->ext_db), GFP_KERNEL);
	अगर (!db->ext_db)
		वापस -ENOMEM;

	अगर (sdb_ext_mod) अणु
		db->ext_db->sdb_buf_list = kदो_स्मृति(
				माप(*db->ext_db->sdb_buf_list), GFP_KERNEL);
		अगर (!db->ext_db->sdb_buf_list) अणु
			ret = -ENOMEM;
			जाओ ext_sdb_buf_fail_out;
		पूर्ण

		db->ext_db->sdb_buf_list->buf = dma_alloc_coherent(dev,
						     HNS_ROCE_V1_EXT_SDB_SIZE,
						     &sdb_dma_addr, GFP_KERNEL);
		अगर (!db->ext_db->sdb_buf_list->buf) अणु
			ret = -ENOMEM;
			जाओ alloc_sq_db_buf_fail;
		पूर्ण
		db->ext_db->sdb_buf_list->map = sdb_dma_addr;

		db->ext_db->esdb_dep = ilog2(HNS_ROCE_V1_EXT_SDB_DEPTH);
		hns_roce_set_sdb_ext(hr_dev, HNS_ROCE_V1_EXT_SDB_ALEPT,
				     HNS_ROCE_V1_EXT_SDB_ALFUL);
	पूर्ण अन्यथा
		hns_roce_set_sdb(hr_dev, HNS_ROCE_V1_SDB_ALEPT,
				 HNS_ROCE_V1_SDB_ALFUL);

	अगर (odb_ext_mod) अणु
		db->ext_db->odb_buf_list = kदो_स्मृति(
				माप(*db->ext_db->odb_buf_list), GFP_KERNEL);
		अगर (!db->ext_db->odb_buf_list) अणु
			ret = -ENOMEM;
			जाओ ext_odb_buf_fail_out;
		पूर्ण

		db->ext_db->odb_buf_list->buf = dma_alloc_coherent(dev,
						     HNS_ROCE_V1_EXT_ODB_SIZE,
						     &odb_dma_addr, GFP_KERNEL);
		अगर (!db->ext_db->odb_buf_list->buf) अणु
			ret = -ENOMEM;
			जाओ alloc_otr_db_buf_fail;
		पूर्ण
		db->ext_db->odb_buf_list->map = odb_dma_addr;

		db->ext_db->eodb_dep = ilog2(HNS_ROCE_V1_EXT_ODB_DEPTH);
		hns_roce_set_odb_ext(hr_dev, HNS_ROCE_V1_EXT_ODB_ALEPT,
				     HNS_ROCE_V1_EXT_ODB_ALFUL);
	पूर्ण अन्यथा
		hns_roce_set_odb(hr_dev, HNS_ROCE_V1_ODB_ALEPT,
				 HNS_ROCE_V1_ODB_ALFUL);

	hns_roce_set_db_ext_mode(hr_dev, sdb_ext_mod, odb_ext_mod);

	वापस 0;

alloc_otr_db_buf_fail:
	kमुक्त(db->ext_db->odb_buf_list);

ext_odb_buf_fail_out:
	अगर (sdb_ext_mod) अणु
		dma_मुक्त_coherent(dev, HNS_ROCE_V1_EXT_SDB_SIZE,
				  db->ext_db->sdb_buf_list->buf,
				  db->ext_db->sdb_buf_list->map);
	पूर्ण

alloc_sq_db_buf_fail:
	अगर (sdb_ext_mod)
		kमुक्त(db->ext_db->sdb_buf_list);

ext_sdb_buf_fail_out:
	kमुक्त(db->ext_db);
	वापस ret;
पूर्ण

अटल काष्ठा hns_roce_qp *hns_roce_v1_create_lp_qp(काष्ठा hns_roce_dev *hr_dev,
						    काष्ठा ib_pd *pd)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा ib_qp_init_attr init_attr;
	काष्ठा ib_qp *qp;

	स_रखो(&init_attr, 0, माप(काष्ठा ib_qp_init_attr));
	init_attr.qp_type		= IB_QPT_RC;
	init_attr.sq_sig_type		= IB_SIGNAL_ALL_WR;
	init_attr.cap.max_recv_wr	= HNS_ROCE_MIN_WQE_NUM;
	init_attr.cap.max_send_wr	= HNS_ROCE_MIN_WQE_NUM;

	qp = hns_roce_create_qp(pd, &init_attr, शून्य);
	अगर (IS_ERR(qp)) अणु
		dev_err(dev, "Create loop qp for mr free failed!");
		वापस शून्य;
	पूर्ण

	वापस to_hr_qp(qp);
पूर्ण

अटल पूर्णांक hns_roce_v1_rsv_lp_qp(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा ib_cq_init_attr cq_init_attr;
	काष्ठा ib_qp_attr attr = अणु 0 पूर्ण;
	काष्ठा hns_roce_qp *hr_qp;
	काष्ठा ib_cq *cq;
	काष्ठा ib_pd *pd;
	जोड़ ib_gid dgid;
	__be64 subnet_prefix;
	पूर्णांक attr_mask = 0;
	पूर्णांक ret;
	पूर्णांक i, j;
	u8 queue_en[HNS_ROCE_V1_RESV_QP] = अणु 0 पूर्ण;
	u8 phy_port;
	u32 port = 0;
	u8 sl;

	/* Reserved cq क्रम loop qp */
	cq_init_attr.cqe		= HNS_ROCE_MIN_WQE_NUM * 2;
	cq_init_attr.comp_vector	= 0;

	cq = rdma_zalloc_drv_obj(ibdev, ib_cq);
	अगर (!cq)
		वापस -ENOMEM;

	ret = hns_roce_create_cq(cq, &cq_init_attr, शून्य);
	अगर (ret) अणु
		dev_err(dev, "Create cq for reserved loop qp failed!");
		जाओ alloc_cq_failed;
	पूर्ण
	मुक्त_mr->mr_मुक्त_cq = to_hr_cq(cq);
	मुक्त_mr->mr_मुक्त_cq->ib_cq.device		= &hr_dev->ib_dev;
	मुक्त_mr->mr_मुक्त_cq->ib_cq.uobject		= शून्य;
	मुक्त_mr->mr_मुक्त_cq->ib_cq.comp_handler		= शून्य;
	मुक्त_mr->mr_मुक्त_cq->ib_cq.event_handler	= शून्य;
	मुक्त_mr->mr_मुक्त_cq->ib_cq.cq_context		= शून्य;
	atomic_set(&मुक्त_mr->mr_मुक्त_cq->ib_cq.usecnt, 0);

	pd = rdma_zalloc_drv_obj(ibdev, ib_pd);
	अगर (!pd) अणु
		ret = -ENOMEM;
		जाओ alloc_mem_failed;
	पूर्ण

	pd->device  = ibdev;
	ret = hns_roce_alloc_pd(pd, शून्य);
	अगर (ret)
		जाओ alloc_pd_failed;

	मुक्त_mr->mr_मुक्त_pd = to_hr_pd(pd);
	मुक्त_mr->mr_मुक्त_pd->ibpd.device  = &hr_dev->ib_dev;
	मुक्त_mr->mr_मुक्त_pd->ibpd.uobject = शून्य;
	मुक्त_mr->mr_मुक्त_pd->ibpd.__पूर्णांकernal_mr = शून्य;
	atomic_set(&मुक्त_mr->mr_मुक्त_pd->ibpd.usecnt, 0);

	attr.qp_access_flags	= IB_ACCESS_REMOTE_WRITE;
	attr.pkey_index		= 0;
	attr.min_rnr_समयr	= 0;
	/* Disable पढ़ो ability */
	attr.max_dest_rd_atomic = 0;
	attr.max_rd_atomic	= 0;
	/* Use arbitrary values as rq_psn and sq_psn */
	attr.rq_psn		= 0x0808;
	attr.sq_psn		= 0x0808;
	attr.retry_cnt		= 7;
	attr.rnr_retry		= 7;
	attr.समयout		= 0x12;
	attr.path_mtu		= IB_MTU_256;
	attr.ah_attr.type	= RDMA_AH_ATTR_TYPE_ROCE;
	rdma_ah_set_grh(&attr.ah_attr, शून्य, 0, 0, 1, 0);
	rdma_ah_set_अटल_rate(&attr.ah_attr, 3);

	subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	क्रम (i = 0; i < HNS_ROCE_V1_RESV_QP; i++) अणु
		phy_port = (i >= HNS_ROCE_MAX_PORTS) ? (i - 2) :
				(i % HNS_ROCE_MAX_PORTS);
		sl = i / HNS_ROCE_MAX_PORTS;

		क्रम (j = 0; j < caps->num_ports; j++) अणु
			अगर (hr_dev->iboe.phy_port[j] == phy_port) अणु
				queue_en[i] = 1;
				port = j;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!queue_en[i])
			जारी;

		मुक्त_mr->mr_मुक्त_qp[i] = hns_roce_v1_create_lp_qp(hr_dev, pd);
		अगर (!मुक्त_mr->mr_मुक्त_qp[i]) अणु
			dev_err(dev, "Create loop qp failed!\n");
			ret = -ENOMEM;
			जाओ create_lp_qp_failed;
		पूर्ण
		hr_qp = मुक्त_mr->mr_मुक्त_qp[i];

		hr_qp->port		= port;
		hr_qp->phy_port		= phy_port;
		hr_qp->ibqp.qp_type	= IB_QPT_RC;
		hr_qp->ibqp.device	= &hr_dev->ib_dev;
		hr_qp->ibqp.uobject	= शून्य;
		atomic_set(&hr_qp->ibqp.usecnt, 0);
		hr_qp->ibqp.pd		= pd;
		hr_qp->ibqp.recv_cq	= cq;
		hr_qp->ibqp.send_cq	= cq;

		rdma_ah_set_port_num(&attr.ah_attr, port + 1);
		rdma_ah_set_sl(&attr.ah_attr, sl);
		attr.port_num		= port + 1;

		attr.dest_qp_num	= hr_qp->qpn;
		स_नकल(rdma_ah_retrieve_dmac(&attr.ah_attr),
		       hr_dev->dev_addr[port],
		       ETH_ALEN);

		स_नकल(&dgid.raw, &subnet_prefix, माप(u64));
		स_नकल(&dgid.raw[8], hr_dev->dev_addr[port], 3);
		स_नकल(&dgid.raw[13], hr_dev->dev_addr[port] + 3, 3);
		dgid.raw[11] = 0xff;
		dgid.raw[12] = 0xfe;
		dgid.raw[8] ^= 2;
		rdma_ah_set_dgid_raw(&attr.ah_attr, dgid.raw);

		ret = hr_dev->hw->modअगरy_qp(&hr_qp->ibqp, &attr, attr_mask,
					    IB_QPS_RESET, IB_QPS_INIT);
		अगर (ret) अणु
			dev_err(dev, "modify qp failed(%d)!\n", ret);
			जाओ create_lp_qp_failed;
		पूर्ण

		ret = hr_dev->hw->modअगरy_qp(&hr_qp->ibqp, &attr, IB_QP_DEST_QPN,
					    IB_QPS_INIT, IB_QPS_RTR);
		अगर (ret) अणु
			dev_err(dev, "modify qp failed(%d)!\n", ret);
			जाओ create_lp_qp_failed;
		पूर्ण

		ret = hr_dev->hw->modअगरy_qp(&hr_qp->ibqp, &attr, attr_mask,
					    IB_QPS_RTR, IB_QPS_RTS);
		अगर (ret) अणु
			dev_err(dev, "modify qp failed(%d)!\n", ret);
			जाओ create_lp_qp_failed;
		पूर्ण
	पूर्ण

	वापस 0;

create_lp_qp_failed:
	क्रम (i -= 1; i >= 0; i--) अणु
		hr_qp = मुक्त_mr->mr_मुक्त_qp[i];
		अगर (hns_roce_v1_destroy_qp(&hr_qp->ibqp, शून्य))
			dev_err(dev, "Destroy qp %d for mr free failed!\n", i);
	पूर्ण

	hns_roce_dealloc_pd(pd, शून्य);

alloc_pd_failed:
	kमुक्त(pd);

alloc_mem_failed:
	hns_roce_destroy_cq(cq, शून्य);
alloc_cq_failed:
	kमुक्त(cq);
	वापस ret;
पूर्ण

अटल व्योम hns_roce_v1_release_lp_qp(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_qp *hr_qp;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < HNS_ROCE_V1_RESV_QP; i++) अणु
		hr_qp = मुक्त_mr->mr_मुक्त_qp[i];
		अगर (!hr_qp)
			जारी;

		ret = hns_roce_v1_destroy_qp(&hr_qp->ibqp, शून्य);
		अगर (ret)
			dev_err(dev, "Destroy qp %d for mr free failed(%d)!\n",
				i, ret);
	पूर्ण

	hns_roce_destroy_cq(&मुक्त_mr->mr_मुक्त_cq->ib_cq, शून्य);
	kमुक्त(&मुक्त_mr->mr_मुक्त_cq->ib_cq);
	hns_roce_dealloc_pd(&मुक्त_mr->mr_मुक्त_pd->ibpd, शून्य);
	kमुक्त(&मुक्त_mr->mr_मुक्त_pd->ibpd);
पूर्ण

अटल पूर्णांक hns_roce_db_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_db_table *db = &priv->db_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	u32 sdb_ext_mod;
	u32 odb_ext_mod;
	u32 sdb_evt_mod;
	u32 odb_evt_mod;
	पूर्णांक ret;

	स_रखो(db, 0, माप(*db));

	/* Default DB mode */
	sdb_ext_mod = HNS_ROCE_SDB_EXTEND_MODE;
	odb_ext_mod = HNS_ROCE_ODB_EXTEND_MODE;
	sdb_evt_mod = HNS_ROCE_SDB_NORMAL_MODE;
	odb_evt_mod = HNS_ROCE_ODB_POLL_MODE;

	db->sdb_ext_mod = sdb_ext_mod;
	db->odb_ext_mod = odb_ext_mod;

	/* Init extend DB */
	ret = hns_roce_db_ext_init(hr_dev, sdb_ext_mod, odb_ext_mod);
	अगर (ret) अणु
		dev_err(dev, "Failed in extend DB configuration.\n");
		वापस ret;
	पूर्ण

	hns_roce_set_db_event_mode(hr_dev, sdb_evt_mod, odb_evt_mod);

	वापस 0;
पूर्ण

अटल व्योम hns_roce_v1_recreate_lp_qp_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hns_roce_recreate_lp_qp_work *lp_qp_work;
	काष्ठा hns_roce_dev *hr_dev;

	lp_qp_work = container_of(work, काष्ठा hns_roce_recreate_lp_qp_work,
				  work);
	hr_dev = to_hr_dev(lp_qp_work->ib_dev);

	hns_roce_v1_release_lp_qp(hr_dev);

	अगर (hns_roce_v1_rsv_lp_qp(hr_dev))
		dev_err(&hr_dev->pdev->dev, "create reserver qp failed\n");

	अगर (lp_qp_work->comp_flag)
		complete(lp_qp_work->comp);

	kमुक्त(lp_qp_work);
पूर्ण

अटल पूर्णांक hns_roce_v1_recreate_lp_qp(काष्ठा hns_roce_dev *hr_dev)
अणु
	दीर्घ end = HNS_ROCE_V1_RECREATE_LP_QP_TIMEOUT_MSECS;
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	काष्ठा hns_roce_recreate_lp_qp_work *lp_qp_work;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा completion comp;

	lp_qp_work = kzalloc(माप(काष्ठा hns_roce_recreate_lp_qp_work),
			     GFP_KERNEL);
	अगर (!lp_qp_work)
		वापस -ENOMEM;

	INIT_WORK(&(lp_qp_work->work), hns_roce_v1_recreate_lp_qp_work_fn);

	lp_qp_work->ib_dev = &(hr_dev->ib_dev);
	lp_qp_work->comp = &comp;
	lp_qp_work->comp_flag = 1;

	init_completion(lp_qp_work->comp);

	queue_work(मुक्त_mr->मुक्त_mr_wq, &(lp_qp_work->work));

	जबतक (end > 0) अणु
		अगर (try_रुको_क्रम_completion(&comp))
			वापस 0;
		msleep(HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE);
		end -= HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE;
	पूर्ण

	lp_qp_work->comp_flag = 0;
	अगर (try_रुको_क्रम_completion(&comp))
		वापस 0;

	dev_warn(dev, "recreate lp qp failed 20s timeout and return failed!\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hns_roce_v1_send_lp_wqe(काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_qp->ibqp.device);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा ib_send_wr send_wr;
	स्थिर काष्ठा ib_send_wr *bad_wr;
	पूर्णांक ret;

	स_रखो(&send_wr, 0, माप(send_wr));
	send_wr.next	= शून्य;
	send_wr.num_sge	= 0;
	send_wr.send_flags = 0;
	send_wr.sg_list	= शून्य;
	send_wr.wr_id	= (अचिन्हित दीर्घ दीर्घ)&send_wr;
	send_wr.opcode	= IB_WR_RDMA_WRITE;

	ret = hns_roce_v1_post_send(&hr_qp->ibqp, &send_wr, &bad_wr);
	अगर (ret) अणु
		dev_err(dev, "Post write wqe for mr free failed(%d)!", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_roce_v1_mr_मुक्त_work_fn(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ end =
		msecs_to_jअगरfies(HNS_ROCE_V1_FREE_MR_TIMEOUT_MSECS) + jअगरfies;
	काष्ठा hns_roce_mr_मुक्त_work *mr_work =
		container_of(work, काष्ठा hns_roce_mr_मुक्त_work, work);
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(mr_work->ib_dev);
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	काष्ठा hns_roce_cq *mr_मुक्त_cq = मुक्त_mr->mr_मुक्त_cq;
	काष्ठा hns_roce_mr *hr_mr = mr_work->mr;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा ib_wc wc[HNS_ROCE_V1_RESV_QP];
	काष्ठा hns_roce_qp *hr_qp;
	पूर्णांक ne = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < HNS_ROCE_V1_RESV_QP; i++) अणु
		hr_qp = मुक्त_mr->mr_मुक्त_qp[i];
		अगर (!hr_qp)
			जारी;
		ne++;

		ret = hns_roce_v1_send_lp_wqe(hr_qp);
		अगर (ret) अणु
			dev_err(dev,
			     "Send wqe (qp:0x%lx) for mr free failed(%d)!\n",
			     hr_qp->qpn, ret);
			जाओ मुक्त_work;
		पूर्ण
	पूर्ण

	अगर (!ne) अणु
		dev_err(dev, "Reserved loop qp is absent!\n");
		जाओ मुक्त_work;
	पूर्ण

	करो अणु
		ret = hns_roce_v1_poll_cq(&mr_मुक्त_cq->ib_cq, ne, wc);
		अगर (ret < 0 && hr_qp) अणु
			dev_err(dev,
			   "(qp:0x%lx) starts, Poll cqe failed(%d) for mr 0x%x free! Remain %d cqe\n",
			   hr_qp->qpn, ret, hr_mr->key, ne);
			जाओ मुक्त_work;
		पूर्ण
		ne -= ret;
		usleep_range(HNS_ROCE_V1_FREE_MR_WAIT_VALUE * 1000,
			     (1 + HNS_ROCE_V1_FREE_MR_WAIT_VALUE) * 1000);
	पूर्ण जबतक (ne && समय_beक्रमe_eq(jअगरfies, end));

	अगर (ne != 0)
		dev_err(dev,
			"Poll cqe for mr 0x%x free timeout! Remain %d cqe\n",
			hr_mr->key, ne);

मुक्त_work:
	अगर (mr_work->comp_flag)
		complete(mr_work->comp);
	kमुक्त(mr_work);
पूर्ण

अटल पूर्णांक hns_roce_v1_dereg_mr(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_mr *mr, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	दीर्घ end = HNS_ROCE_V1_FREE_MR_TIMEOUT_MSECS;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_mr_मुक्त_work *mr_work;
	अचिन्हित दीर्घ start = jअगरfies;
	काष्ठा completion comp;
	पूर्णांक ret = 0;

	अगर (mr->enabled) अणु
		अगर (hns_roce_hw_destroy_mpt(hr_dev, शून्य,
					    key_to_hw_index(mr->key) &
					    (hr_dev->caps.num_mtpts - 1)))
			dev_warn(dev, "DESTROY_MPT failed!\n");
	पूर्ण

	mr_work = kzalloc(माप(*mr_work), GFP_KERNEL);
	अगर (!mr_work) अणु
		ret = -ENOMEM;
		जाओ मुक्त_mr;
	पूर्ण

	INIT_WORK(&(mr_work->work), hns_roce_v1_mr_मुक्त_work_fn);

	mr_work->ib_dev = &(hr_dev->ib_dev);
	mr_work->comp = &comp;
	mr_work->comp_flag = 1;
	mr_work->mr = (व्योम *)mr;
	init_completion(mr_work->comp);

	queue_work(मुक्त_mr->मुक्त_mr_wq, &(mr_work->work));

	जबतक (end > 0) अणु
		अगर (try_रुको_क्रम_completion(&comp))
			जाओ मुक्त_mr;
		msleep(HNS_ROCE_V1_FREE_MR_WAIT_VALUE);
		end -= HNS_ROCE_V1_FREE_MR_WAIT_VALUE;
	पूर्ण

	mr_work->comp_flag = 0;
	अगर (try_रुको_क्रम_completion(&comp))
		जाओ मुक्त_mr;

	dev_warn(dev, "Free mr work 0x%x over 50s and failed!\n", mr->key);
	ret = -ETIMEDOUT;

मुक्त_mr:
	dev_dbg(dev, "Free mr 0x%x use 0x%x us.\n",
		mr->key, jअगरfies_to_usecs(jअगरfies) - jअगरfies_to_usecs(start));

	hns_roce_biपंचांगap_मुक्त(&hr_dev->mr_table.mtpt_biपंचांगap,
			     key_to_hw_index(mr->key), 0);
	hns_roce_mtr_destroy(hr_dev, &mr->pbl_mtr);
	kमुक्त(mr);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_db_मुक्त(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_db_table *db = &priv->db_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	अगर (db->sdb_ext_mod) अणु
		dma_मुक्त_coherent(dev, HNS_ROCE_V1_EXT_SDB_SIZE,
				  db->ext_db->sdb_buf_list->buf,
				  db->ext_db->sdb_buf_list->map);
		kमुक्त(db->ext_db->sdb_buf_list);
	पूर्ण

	अगर (db->odb_ext_mod) अणु
		dma_मुक्त_coherent(dev, HNS_ROCE_V1_EXT_ODB_SIZE,
				  db->ext_db->odb_buf_list->buf,
				  db->ext_db->odb_buf_list->map);
		kमुक्त(db->ext_db->odb_buf_list);
	पूर्ण

	kमुक्त(db->ext_db);
पूर्ण

अटल पूर्णांक hns_roce_raq_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_raq_table *raq = &priv->raq_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	dma_addr_t addr;
	पूर्णांक raq_shअगरt;
	__le32 पंचांगp;
	u32 val;
	पूर्णांक ret;

	raq->e_raq_buf = kzalloc(माप(*(raq->e_raq_buf)), GFP_KERNEL);
	अगर (!raq->e_raq_buf)
		वापस -ENOMEM;

	raq->e_raq_buf->buf = dma_alloc_coherent(dev, HNS_ROCE_V1_RAQ_SIZE,
						 &addr, GFP_KERNEL);
	अगर (!raq->e_raq_buf->buf) अणु
		ret = -ENOMEM;
		जाओ err_dma_alloc_raq;
	पूर्ण
	raq->e_raq_buf->map = addr;

	/* Configure raq extended address. 48bit 4K align */
	roce_ग_लिखो(hr_dev, ROCEE_EXT_RAQ_REG, raq->e_raq_buf->map >> 12);

	/* Configure raq_shअगरt */
	raq_shअगरt = ilog2(HNS_ROCE_V1_RAQ_SIZE / HNS_ROCE_V1_RAQ_ENTRY);
	val = roce_पढ़ो(hr_dev, ROCEE_EXT_RAQ_H_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_M,
		       ROCEE_EXT_RAQ_H_EXT_RAQ_SHIFT_S, raq_shअगरt);
	/*
	 * 44 = 32 + 12, When evaluating addr to hardware, shअगरt 12 because of
	 * using 4K page, and shअगरt more 32 because of
	 * calculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(पंचांगp, ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_M,
		       ROCEE_EXT_RAQ_H_EXT_RAQ_BA_H_S,
		       raq->e_raq_buf->map >> 44);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_EXT_RAQ_H_REG, val);
	dev_dbg(dev, "Configure raq_shift 0x%x.\n", val);

	/* Configure raq threshold */
	val = roce_पढ़ो(hr_dev, ROCEE_RAQ_WL_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_RAQ_WL_ROCEE_RAQ_WL_M,
		       ROCEE_RAQ_WL_ROCEE_RAQ_WL_S,
		       HNS_ROCE_V1_EXT_RAQ_WF);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_RAQ_WL_REG, val);
	dev_dbg(dev, "Configure raq_wl 0x%x.\n", val);

	/* Enable extend raq */
	val = roce_पढ़ो(hr_dev, ROCEE_WRMS_POL_TIME_INTERVAL_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_M,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_POL_TIME_INTERVAL_S,
		       POL_TIME_INTERVAL_VAL);
	roce_set_bit(पंचांगp, ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_EXT_RAQ_MODE, 1);
	roce_set_field(पंचांगp,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_M,
		       ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_CFG_S,
		       2);
	roce_set_bit(पंचांगp,
		     ROCEE_WRMS_POL_TIME_INTERVAL_WRMS_RAQ_TIMEOUT_CHK_EN_S, 1);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_WRMS_POL_TIME_INTERVAL_REG, val);
	dev_dbg(dev, "Configure WrmsPolTimeInterval 0x%x.\n", val);

	/* Enable raq drop */
	val = roce_पढ़ो(hr_dev, ROCEE_GLB_CFG_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_bit(पंचांगp, ROCEE_GLB_CFG_TRP_RAQ_DROP_EN_S, 1);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_GLB_CFG_REG, val);
	dev_dbg(dev, "Configure GlbCfg = 0x%x.\n", val);

	वापस 0;

err_dma_alloc_raq:
	kमुक्त(raq->e_raq_buf);
	वापस ret;
पूर्ण

अटल व्योम hns_roce_raq_मुक्त(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_raq_table *raq = &priv->raq_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	dma_मुक्त_coherent(dev, HNS_ROCE_V1_RAQ_SIZE, raq->e_raq_buf->buf,
			  raq->e_raq_buf->map);
	kमुक्त(raq->e_raq_buf);
पूर्ण

अटल व्योम hns_roce_port_enable(काष्ठा hns_roce_dev *hr_dev, पूर्णांक enable_flag)
अणु
	__le32 पंचांगp;
	u32 val;

	अगर (enable_flag) अणु
		val = roce_पढ़ो(hr_dev, ROCEE_GLB_CFG_REG);
		 /* Open all ports */
		पंचांगp = cpu_to_le32(val);
		roce_set_field(पंचांगp, ROCEE_GLB_CFG_ROCEE_PORT_ST_M,
			       ROCEE_GLB_CFG_ROCEE_PORT_ST_S,
			       ALL_PORT_VAL_OPEN);
		val = le32_to_cpu(पंचांगp);
		roce_ग_लिखो(hr_dev, ROCEE_GLB_CFG_REG, val);
	पूर्ण अन्यथा अणु
		val = roce_पढ़ो(hr_dev, ROCEE_GLB_CFG_REG);
		/* Close all ports */
		पंचांगp = cpu_to_le32(val);
		roce_set_field(पंचांगp, ROCEE_GLB_CFG_ROCEE_PORT_ST_M,
			       ROCEE_GLB_CFG_ROCEE_PORT_ST_S, 0x0);
		val = le32_to_cpu(पंचांगp);
		roce_ग_लिखो(hr_dev, ROCEE_GLB_CFG_REG, val);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_bt_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	पूर्णांक ret;

	priv->bt_table.qpc_buf.buf = dma_alloc_coherent(dev,
		HNS_ROCE_BT_RSV_BUF_SIZE, &priv->bt_table.qpc_buf.map,
		GFP_KERNEL);
	अगर (!priv->bt_table.qpc_buf.buf)
		वापस -ENOMEM;

	priv->bt_table.mtpt_buf.buf = dma_alloc_coherent(dev,
		HNS_ROCE_BT_RSV_BUF_SIZE, &priv->bt_table.mtpt_buf.map,
		GFP_KERNEL);
	अगर (!priv->bt_table.mtpt_buf.buf) अणु
		ret = -ENOMEM;
		जाओ err_failed_alloc_mtpt_buf;
	पूर्ण

	priv->bt_table.cqc_buf.buf = dma_alloc_coherent(dev,
		HNS_ROCE_BT_RSV_BUF_SIZE, &priv->bt_table.cqc_buf.map,
		GFP_KERNEL);
	अगर (!priv->bt_table.cqc_buf.buf) अणु
		ret = -ENOMEM;
		जाओ err_failed_alloc_cqc_buf;
	पूर्ण

	वापस 0;

err_failed_alloc_cqc_buf:
	dma_मुक्त_coherent(dev, HNS_ROCE_BT_RSV_BUF_SIZE,
		priv->bt_table.mtpt_buf.buf, priv->bt_table.mtpt_buf.map);

err_failed_alloc_mtpt_buf:
	dma_मुक्त_coherent(dev, HNS_ROCE_BT_RSV_BUF_SIZE,
		priv->bt_table.qpc_buf.buf, priv->bt_table.qpc_buf.map);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_bt_मुक्त(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	dma_मुक्त_coherent(dev, HNS_ROCE_BT_RSV_BUF_SIZE,
		priv->bt_table.cqc_buf.buf, priv->bt_table.cqc_buf.map);

	dma_मुक्त_coherent(dev, HNS_ROCE_BT_RSV_BUF_SIZE,
		priv->bt_table.mtpt_buf.buf, priv->bt_table.mtpt_buf.map);

	dma_मुक्त_coherent(dev, HNS_ROCE_BT_RSV_BUF_SIZE,
		priv->bt_table.qpc_buf.buf, priv->bt_table.qpc_buf.map);
पूर्ण

अटल पूर्णांक hns_roce_tptr_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_buf_list *tptr_buf = &priv->tptr_table.tptr_buf;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	/*
	 * This buffer will be used क्रम CQ's tptr(tail poपूर्णांकer), also
	 * named ci(customer index). Every CQ will use 2 bytes to save
	 * cqe ci in hip06. Hardware will पढ़ो this area to get new ci
	 * when the queue is almost full.
	 */
	tptr_buf->buf = dma_alloc_coherent(dev, HNS_ROCE_V1_TPTR_BUF_SIZE,
					   &tptr_buf->map, GFP_KERNEL);
	अगर (!tptr_buf->buf)
		वापस -ENOMEM;

	hr_dev->tptr_dma_addr = tptr_buf->map;
	hr_dev->tptr_size = HNS_ROCE_V1_TPTR_BUF_SIZE;

	वापस 0;
पूर्ण

अटल व्योम hns_roce_tptr_मुक्त(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_buf_list *tptr_buf = &priv->tptr_table.tptr_buf;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	dma_मुक्त_coherent(dev, HNS_ROCE_V1_TPTR_BUF_SIZE,
			  tptr_buf->buf, tptr_buf->map);
पूर्ण

अटल पूर्णांक hns_roce_मुक्त_mr_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	पूर्णांक ret;

	मुक्त_mr->मुक्त_mr_wq = create_singlethपढ़ो_workqueue("hns_roce_free_mr");
	अगर (!मुक्त_mr->मुक्त_mr_wq) अणु
		dev_err(dev, "Create free mr workqueue failed!\n");
		वापस -ENOMEM;
	पूर्ण

	ret = hns_roce_v1_rsv_lp_qp(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Reserved loop qp failed(%d)!\n", ret);
		destroy_workqueue(मुक्त_mr->मुक्त_mr_wq);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns_roce_मुक्त_mr_मुक्त(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_मुक्त_mr *मुक्त_mr = &priv->मुक्त_mr;

	destroy_workqueue(मुक्त_mr->मुक्त_mr_wq);

	hns_roce_v1_release_lp_qp(hr_dev);
पूर्ण

/**
 * hns_roce_v1_reset - reset RoCE
 * @hr_dev: RoCE device काष्ठा poपूर्णांकer
 * @dereset: true -- drop reset, false -- reset
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_roce_v1_reset(काष्ठा hns_roce_dev *hr_dev, bool dereset)
अणु
	काष्ठा device_node *dsaf_node;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक ret;

	/* check अगर this is DT/ACPI हाल */
	अगर (dev_of_node(dev)) अणु
		dsaf_node = of_parse_phandle(np, "dsaf-handle", 0);
		अगर (!dsaf_node) अणु
			dev_err(dev, "could not find dsaf-handle\n");
			वापस -EINVAL;
		पूर्ण
		fwnode = &dsaf_node->fwnode;
	पूर्ण अन्यथा अगर (is_acpi_device_node(dev->fwnode)) अणु
		काष्ठा fwnode_reference_args args;

		ret = acpi_node_get_property_reference(dev->fwnode,
						       "dsaf-handle", 0, &args);
		अगर (ret) अणु
			dev_err(dev, "could not find dsaf-handle\n");
			वापस ret;
		पूर्ण
		fwnode = args.fwnode;
	पूर्ण अन्यथा अणु
		dev_err(dev, "cannot read data from DT or ACPI\n");
		वापस -ENXIO;
	पूर्ण

	ret = hns_dsaf_roce_reset(fwnode, false);
	अगर (ret)
		वापस ret;

	अगर (dereset) अणु
		msleep(SLEEP_TIME_INTERVAL);
		ret = hns_dsaf_roce_reset(fwnode, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_profile(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	पूर्णांक i;

	hr_dev->venकरोr_id = roce_पढ़ो(hr_dev, ROCEE_VENDOR_ID_REG);
	hr_dev->venकरोr_part_id = roce_पढ़ो(hr_dev, ROCEE_VENDOR_PART_ID_REG);
	hr_dev->sys_image_guid = roce_पढ़ो(hr_dev, ROCEE_SYS_IMAGE_GUID_L_REG) |
				((u64)roce_पढ़ो(hr_dev,
					    ROCEE_SYS_IMAGE_GUID_H_REG) << 32);
	hr_dev->hw_rev		= HNS_ROCE_HW_VER1;

	caps->num_qps		= HNS_ROCE_V1_MAX_QP_NUM;
	caps->max_wqes		= HNS_ROCE_V1_MAX_WQE_NUM;
	caps->min_wqes		= HNS_ROCE_MIN_WQE_NUM;
	caps->num_cqs		= HNS_ROCE_V1_MAX_CQ_NUM;
	caps->min_cqes		= HNS_ROCE_MIN_CQE_NUM;
	caps->max_cqes		= HNS_ROCE_V1_MAX_CQE_NUM;
	caps->max_sq_sg		= HNS_ROCE_V1_SG_NUM;
	caps->max_rq_sg		= HNS_ROCE_V1_SG_NUM;
	caps->max_sq_अंतरभूत	= HNS_ROCE_V1_INLINE_SIZE;
	caps->num_uars		= HNS_ROCE_V1_UAR_NUM;
	caps->phy_num_uars	= HNS_ROCE_V1_PHY_UAR_NUM;
	caps->num_aeq_vectors	= HNS_ROCE_V1_AEQE_VEC_NUM;
	caps->num_comp_vectors	= HNS_ROCE_V1_COMP_VEC_NUM;
	caps->num_other_vectors	= HNS_ROCE_V1_ABNORMAL_VEC_NUM;
	caps->num_mtpts		= HNS_ROCE_V1_MAX_MTPT_NUM;
	caps->num_mtt_segs	= HNS_ROCE_V1_MAX_MTT_SEGS;
	caps->num_pds		= HNS_ROCE_V1_MAX_PD_NUM;
	caps->max_qp_init_rdma	= HNS_ROCE_V1_MAX_QP_INIT_RDMA;
	caps->max_qp_dest_rdma	= HNS_ROCE_V1_MAX_QP_DEST_RDMA;
	caps->max_sq_desc_sz	= HNS_ROCE_V1_MAX_SQ_DESC_SZ;
	caps->max_rq_desc_sz	= HNS_ROCE_V1_MAX_RQ_DESC_SZ;
	caps->qpc_sz		= HNS_ROCE_V1_QPC_SIZE;
	caps->irrl_entry_sz	= HNS_ROCE_V1_IRRL_ENTRY_SIZE;
	caps->cqc_entry_sz	= HNS_ROCE_V1_CQC_ENTRY_SIZE;
	caps->mtpt_entry_sz	= HNS_ROCE_V1_MTPT_ENTRY_SIZE;
	caps->mtt_entry_sz	= HNS_ROCE_V1_MTT_ENTRY_SIZE;
	caps->cqe_sz		= HNS_ROCE_V1_CQE_SIZE;
	caps->page_size_cap	= HNS_ROCE_V1_PAGE_SIZE_SUPPORT;
	caps->reserved_lkey	= 0;
	caps->reserved_pds	= 0;
	caps->reserved_mrws	= 1;
	caps->reserved_uars	= 0;
	caps->reserved_cqs	= 0;
	caps->reserved_qps	= 12; /* 2 SQP per port, six ports total 12 */
	caps->chunk_sz		= HNS_ROCE_V1_TABLE_CHUNK_SIZE;

	क्रम (i = 0; i < caps->num_ports; i++)
		caps->pkey_table_len[i] = 1;

	क्रम (i = 0; i < caps->num_ports; i++) अणु
		/* Six ports shared 16 GID in v1 engine */
		अगर (i >= (HNS_ROCE_V1_GID_NUM % caps->num_ports))
			caps->gid_table_len[i] = HNS_ROCE_V1_GID_NUM /
						 caps->num_ports;
		अन्यथा
			caps->gid_table_len[i] = HNS_ROCE_V1_GID_NUM /
						 caps->num_ports + 1;
	पूर्ण

	caps->ceqe_depth = HNS_ROCE_V1_COMP_EQE_NUM;
	caps->aeqe_depth = HNS_ROCE_V1_ASYNC_EQE_NUM;
	caps->local_ca_ack_delay = roce_पढ़ो(hr_dev, ROCEE_ACK_DELAY_REG);
	caps->max_mtu = IB_MTU_2048;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक ret;
	u32 val;
	__le32 पंचांगp;
	काष्ठा device *dev = &hr_dev->pdev->dev;

	/* DMAE user config */
	val = roce_पढ़ो(hr_dev, ROCEE_DMAE_USER_CFG1_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_M,
		       ROCEE_DMAE_USER_CFG1_ROCEE_CACHE_TB_CFG_S, 0xf);
	roce_set_field(पंचांगp, ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_M,
		       ROCEE_DMAE_USER_CFG1_ROCEE_STREAM_ID_TB_CFG_S,
		       1 << PAGES_SHIFT_16);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_DMAE_USER_CFG1_REG, val);

	val = roce_पढ़ो(hr_dev, ROCEE_DMAE_USER_CFG2_REG);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_M,
		       ROCEE_DMAE_USER_CFG2_ROCEE_CACHE_PKT_CFG_S, 0xf);
	roce_set_field(पंचांगp, ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_M,
		       ROCEE_DMAE_USER_CFG2_ROCEE_STREAM_ID_PKT_CFG_S,
		       1 << PAGES_SHIFT_16);

	ret = hns_roce_db_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "doorbell init failed!\n");
		वापस ret;
	पूर्ण

	ret = hns_roce_raq_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "raq init failed!\n");
		जाओ error_failed_raq_init;
	पूर्ण

	ret = hns_roce_bt_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "bt init failed!\n");
		जाओ error_failed_bt_init;
	पूर्ण

	ret = hns_roce_tptr_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "tptr init failed!\n");
		जाओ error_failed_tptr_init;
	पूर्ण

	ret = hns_roce_मुक्त_mr_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "free mr init failed!\n");
		जाओ error_failed_मुक्त_mr_init;
	पूर्ण

	hns_roce_port_enable(hr_dev, HNS_ROCE_PORT_UP);

	वापस 0;

error_failed_मुक्त_mr_init:
	hns_roce_tptr_मुक्त(hr_dev);

error_failed_tptr_init:
	hns_roce_bt_मुक्त(hr_dev);

error_failed_bt_init:
	hns_roce_raq_मुक्त(hr_dev);

error_failed_raq_init:
	hns_roce_db_मुक्त(hr_dev);
	वापस ret;
पूर्ण

अटल व्योम hns_roce_v1_निकास(काष्ठा hns_roce_dev *hr_dev)
अणु
	hns_roce_port_enable(hr_dev, HNS_ROCE_PORT_DOWN);
	hns_roce_मुक्त_mr_मुक्त(hr_dev);
	hns_roce_tptr_मुक्त(hr_dev);
	hns_roce_bt_मुक्त(hr_dev);
	hns_roce_raq_मुक्त(hr_dev);
	hns_roce_db_मुक्त(hr_dev);
पूर्ण

अटल पूर्णांक hns_roce_v1_cmd_pending(काष्ठा hns_roce_dev *hr_dev)
अणु
	u32 status = पढ़ोl(hr_dev->reg_base + ROCEE_MB6_REG);

	वापस (!!(status & (1 << HCR_GO_BIT)));
पूर्ण

अटल पूर्णांक hns_roce_v1_post_mbox(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
				 u64 out_param, u32 in_modअगरier, u8 op_modअगरier,
				 u16 op, u16 token, पूर्णांक event)
अणु
	u32 __iomem *hcr = (u32 __iomem *)(hr_dev->reg_base + ROCEE_MB1_REG);
	अचिन्हित दीर्घ end;
	u32 val = 0;
	__le32 पंचांगp;

	end = msecs_to_jअगरfies(GO_BIT_TIMEOUT_MSECS) + jअगरfies;
	जबतक (hns_roce_v1_cmd_pending(hr_dev)) अणु
		अगर (समय_after(jअगरfies, end)) अणु
			dev_err(hr_dev->dev, "jiffies=%d end=%d\n",
				(पूर्णांक)jअगरfies, (पूर्णांक)end);
			वापस -EAGAIN;
		पूर्ण
		cond_resched();
	पूर्ण

	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_MB6_ROCEE_MB_CMD_M, ROCEE_MB6_ROCEE_MB_CMD_S,
		       op);
	roce_set_field(पंचांगp, ROCEE_MB6_ROCEE_MB_CMD_MDF_M,
		       ROCEE_MB6_ROCEE_MB_CMD_MDF_S, op_modअगरier);
	roce_set_bit(पंचांगp, ROCEE_MB6_ROCEE_MB_EVENT_S, event);
	roce_set_bit(पंचांगp, ROCEE_MB6_ROCEE_MB_HW_RUN_S, 1);
	roce_set_field(पंचांगp, ROCEE_MB6_ROCEE_MB_TOKEN_M,
		       ROCEE_MB6_ROCEE_MB_TOKEN_S, token);

	val = le32_to_cpu(पंचांगp);
	ग_लिखोq(in_param, hcr + 0);
	ग_लिखोq(out_param, hcr + 2);
	ग_लिखोl(in_modअगरier, hcr + 4);
	/* Memory barrier */
	wmb();

	ग_लिखोl(val, hcr + 5);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_chk_mbox(काष्ठा hns_roce_dev *hr_dev,
				अचिन्हित पूर्णांक समयout)
अणु
	u8 __iomem *hcr = hr_dev->reg_base + ROCEE_MB1_REG;
	अचिन्हित दीर्घ end;
	u32 status = 0;

	end = msecs_to_jअगरfies(समयout) + jअगरfies;
	जबतक (hns_roce_v1_cmd_pending(hr_dev) && समय_beक्रमe(jअगरfies, end))
		cond_resched();

	अगर (hns_roce_v1_cmd_pending(hr_dev)) अणु
		dev_err(hr_dev->dev, "[cmd_poll]hw run cmd TIMEDOUT!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	status = le32_to_cpu((__क्रमce __le32)
			      __raw_पढ़ोl(hcr + HCR_STATUS_OFFSET));
	अगर ((status & STATUS_MASK) != 0x1) अणु
		dev_err(hr_dev->dev, "mailbox status 0x%x!\n", status);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_set_gid(काष्ठा hns_roce_dev *hr_dev, u32 port,
			       पूर्णांक gid_index, स्थिर जोड़ ib_gid *gid,
			       स्थिर काष्ठा ib_gid_attr *attr)
अणु
	अचिन्हित दीर्घ flags;
	u32 *p = शून्य;
	u8 gid_idx;

	gid_idx = hns_get_gid_index(hr_dev, port, gid_index);

	spin_lock_irqsave(&hr_dev->iboe.lock, flags);

	p = (u32 *)&gid->raw[0];
	roce_raw_ग_लिखो(*p, hr_dev->reg_base + ROCEE_PORT_GID_L_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[4];
	roce_raw_ग_लिखो(*p, hr_dev->reg_base + ROCEE_PORT_GID_ML_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[8];
	roce_raw_ग_लिखो(*p, hr_dev->reg_base + ROCEE_PORT_GID_MH_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	p = (u32 *)&gid->raw[0xc];
	roce_raw_ग_लिखो(*p, hr_dev->reg_base + ROCEE_PORT_GID_H_0_REG +
		       (HNS_ROCE_V1_GID_NUM * gid_idx));

	spin_unlock_irqrestore(&hr_dev->iboe.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_set_mac(काष्ठा hns_roce_dev *hr_dev, u8 phy_port,
			       u8 *addr)
अणु
	u32 reg_smac_l;
	u16 reg_smac_h;
	__le32 पंचांगp;
	u16 *p_h;
	u32 *p;
	u32 val;

	/*
	 * When mac changed, loopback may fail
	 * because of smac not equal to dmac.
	 * We Need to release and create reserved qp again.
	 */
	अगर (hr_dev->hw->dereg_mr) अणु
		पूर्णांक ret;

		ret = hns_roce_v1_recreate_lp_qp(hr_dev);
		अगर (ret && ret != -ETIMEDOUT)
			वापस ret;
	पूर्ण

	p = (u32 *)(&addr[0]);
	reg_smac_l = *p;
	roce_raw_ग_लिखो(reg_smac_l, hr_dev->reg_base + ROCEE_SMAC_L_0_REG +
		       PHY_PORT_OFFSET * phy_port);

	val = roce_पढ़ो(hr_dev,
			ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET);
	पंचांगp = cpu_to_le32(val);
	p_h = (u16 *)(&addr[4]);
	reg_smac_h  = *p_h;
	roce_set_field(पंचांगp, ROCEE_SMAC_H_ROCEE_SMAC_H_M,
		       ROCEE_SMAC_H_ROCEE_SMAC_H_S, reg_smac_h);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET,
		   val);

	वापस 0;
पूर्ण

अटल व्योम hns_roce_v1_set_mtu(काष्ठा hns_roce_dev *hr_dev, u8 phy_port,
				क्रमागत ib_mtu mtu)
अणु
	__le32 पंचांगp;
	u32 val;

	val = roce_पढ़ो(hr_dev,
			ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET);
	पंचांगp = cpu_to_le32(val);
	roce_set_field(पंचांगp, ROCEE_SMAC_H_ROCEE_PORT_MTU_M,
		       ROCEE_SMAC_H_ROCEE_PORT_MTU_S, mtu);
	val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_SMAC_H_0_REG + phy_port * PHY_PORT_OFFSET,
		   val);
पूर्ण

अटल पूर्णांक hns_roce_v1_ग_लिखो_mtpt(काष्ठा hns_roce_dev *hr_dev, व्योम *mb_buf,
				  काष्ठा hns_roce_mr *mr,
				  अचिन्हित दीर्घ mtpt_idx)
अणु
	u64 pages[HNS_ROCE_MAX_INNER_MTPT_NUM] = अणु 0 पूर्ण;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_v1_mpt_entry *mpt_entry;
	dma_addr_t pbl_ba;
	पूर्णांक count;
	पूर्णांक i;

	/* MPT filled पूर्णांकo mailbox buf */
	mpt_entry = (काष्ठा hns_roce_v1_mpt_entry *)mb_buf;
	स_रखो(mpt_entry, 0, माप(*mpt_entry));

	roce_set_field(mpt_entry->mpt_byte_4, MPT_BYTE_4_KEY_STATE_M,
		       MPT_BYTE_4_KEY_STATE_S, KEY_VALID);
	roce_set_field(mpt_entry->mpt_byte_4, MPT_BYTE_4_KEY_M,
		       MPT_BYTE_4_KEY_S, mr->key);
	roce_set_field(mpt_entry->mpt_byte_4, MPT_BYTE_4_PAGE_SIZE_M,
		       MPT_BYTE_4_PAGE_SIZE_S, MR_SIZE_4K);
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_MW_TYPE_S, 0);
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_MW_BIND_ENABLE_S,
		     (mr->access & IB_ACCESS_MW_BIND ? 1 : 0));
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_OWN_S, 0);
	roce_set_field(mpt_entry->mpt_byte_4, MPT_BYTE_4_MEMORY_LOCATION_TYPE_M,
		       MPT_BYTE_4_MEMORY_LOCATION_TYPE_S, mr->type);
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_REMOTE_ATOMIC_S, 0);
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_LOCAL_WRITE_S,
		     (mr->access & IB_ACCESS_LOCAL_WRITE ? 1 : 0));
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_REMOTE_WRITE_S,
		     (mr->access & IB_ACCESS_REMOTE_WRITE ? 1 : 0));
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_REMOTE_READ_S,
		     (mr->access & IB_ACCESS_REMOTE_READ ? 1 : 0));
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_REMOTE_INVAL_ENABLE_S,
		     0);
	roce_set_bit(mpt_entry->mpt_byte_4, MPT_BYTE_4_ADDRESS_TYPE_S, 0);

	roce_set_field(mpt_entry->mpt_byte_12, MPT_BYTE_12_PBL_ADDR_H_M,
		       MPT_BYTE_12_PBL_ADDR_H_S, 0);
	roce_set_field(mpt_entry->mpt_byte_12, MPT_BYTE_12_MW_BIND_COUNTER_M,
		       MPT_BYTE_12_MW_BIND_COUNTER_S, 0);

	mpt_entry->virt_addr_l = cpu_to_le32((u32)mr->iova);
	mpt_entry->virt_addr_h = cpu_to_le32((u32)(mr->iova >> 32));
	mpt_entry->length = cpu_to_le32((u32)mr->size);

	roce_set_field(mpt_entry->mpt_byte_28, MPT_BYTE_28_PD_M,
		       MPT_BYTE_28_PD_S, mr->pd);
	roce_set_field(mpt_entry->mpt_byte_28, MPT_BYTE_28_L_KEY_IDX_L_M,
		       MPT_BYTE_28_L_KEY_IDX_L_S, mtpt_idx);
	roce_set_field(mpt_entry->mpt_byte_64, MPT_BYTE_64_L_KEY_IDX_H_M,
		       MPT_BYTE_64_L_KEY_IDX_H_S, mtpt_idx >> MTPT_IDX_SHIFT);

	/* DMA memory रेजिस्टर */
	अगर (mr->type == MR_TYPE_DMA)
		वापस 0;

	count = hns_roce_mtr_find(hr_dev, &mr->pbl_mtr, 0, pages,
				  ARRAY_SIZE(pages), &pbl_ba);
	अगर (count < 1) अणु
		ibdev_err(ibdev, "failed to find PBL mtr, count = %d.", count);
		वापस -ENOBUFS;
	पूर्ण

	/* Register user mr */
	क्रम (i = 0; i < count; i++) अणु
		चयन (i) अणु
		हाल 0:
			mpt_entry->pa0_l = cpu_to_le32((u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_36,
				MPT_BYTE_36_PA0_H_M,
				MPT_BYTE_36_PA0_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_32));
			अवरोध;
		हाल 1:
			roce_set_field(mpt_entry->mpt_byte_36,
				       MPT_BYTE_36_PA1_L_M,
				       MPT_BYTE_36_PA1_L_S, (u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_40,
				MPT_BYTE_40_PA1_H_M,
				MPT_BYTE_40_PA1_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_24));
			अवरोध;
		हाल 2:
			roce_set_field(mpt_entry->mpt_byte_40,
				       MPT_BYTE_40_PA2_L_M,
				       MPT_BYTE_40_PA2_L_S, (u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_44,
				MPT_BYTE_44_PA2_H_M,
				MPT_BYTE_44_PA2_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_16));
			अवरोध;
		हाल 3:
			roce_set_field(mpt_entry->mpt_byte_44,
				       MPT_BYTE_44_PA3_L_M,
				       MPT_BYTE_44_PA3_L_S, (u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_48,
				MPT_BYTE_48_PA3_H_M,
				MPT_BYTE_48_PA3_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_8));
			अवरोध;
		हाल 4:
			mpt_entry->pa4_l = cpu_to_le32((u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_56,
				MPT_BYTE_56_PA4_H_M,
				MPT_BYTE_56_PA4_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_32));
			अवरोध;
		हाल 5:
			roce_set_field(mpt_entry->mpt_byte_56,
				       MPT_BYTE_56_PA5_L_M,
				       MPT_BYTE_56_PA5_L_S, (u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_60,
				MPT_BYTE_60_PA5_H_M,
				MPT_BYTE_60_PA5_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_24));
			अवरोध;
		हाल 6:
			roce_set_field(mpt_entry->mpt_byte_60,
				       MPT_BYTE_60_PA6_L_M,
				       MPT_BYTE_60_PA6_L_S, (u32)(pages[i]));
			roce_set_field(mpt_entry->mpt_byte_64,
				MPT_BYTE_64_PA6_H_M,
				MPT_BYTE_64_PA6_H_S,
				(u32)(pages[i] >> PAGES_SHIFT_16));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	mpt_entry->pbl_addr_l = cpu_to_le32(pbl_ba);
	roce_set_field(mpt_entry->mpt_byte_12, MPT_BYTE_12_PBL_ADDR_H_M,
		       MPT_BYTE_12_PBL_ADDR_H_S, upper_32_bits(pbl_ba));

	वापस 0;
पूर्ण

अटल व्योम *get_cqe(काष्ठा hns_roce_cq *hr_cq, पूर्णांक n)
अणु
	वापस hns_roce_buf_offset(hr_cq->mtr.kmem, n * HNS_ROCE_V1_CQE_SIZE);
पूर्ण

अटल व्योम *get_sw_cqe(काष्ठा hns_roce_cq *hr_cq, पूर्णांक n)
अणु
	काष्ठा hns_roce_cqe *hr_cqe = get_cqe(hr_cq, n & hr_cq->ib_cq.cqe);

	/* Get cqe when Owner bit is Conversely with the MSB of cons_idx */
	वापस (roce_get_bit(hr_cqe->cqe_byte_4, CQE_BYTE_4_OWNER_S) ^
		!!(n & hr_cq->cq_depth)) ? hr_cqe : शून्य;
पूर्ण

अटल काष्ठा hns_roce_cqe *next_cqe_sw(काष्ठा hns_roce_cq *hr_cq)
अणु
	वापस get_sw_cqe(hr_cq, hr_cq->cons_index);
पूर्ण

अटल व्योम hns_roce_v1_cq_set_ci(काष्ठा hns_roce_cq *hr_cq, u32 cons_index)
अणु
	__le32 करोorbell[2];

	करोorbell[0] = cpu_to_le32(cons_index & ((hr_cq->cq_depth << 1) - 1));
	करोorbell[1] = 0;
	roce_set_bit(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_HW_SYNS_S, 1);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S, 3);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S, 0);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S, hr_cq->cqn);

	hns_roce_ग_लिखो64_k(करोorbell, hr_cq->db_reg);
पूर्ण

अटल व्योम __hns_roce_v1_cq_clean(काष्ठा hns_roce_cq *hr_cq, u32 qpn,
				   काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_cqe *cqe, *dest;
	u32 prod_index;
	पूर्णांक nमुक्तd = 0;
	u8 owner_bit;

	क्रम (prod_index = hr_cq->cons_index; get_sw_cqe(hr_cq, prod_index);
	     ++prod_index) अणु
		अगर (prod_index == hr_cq->cons_index + hr_cq->ib_cq.cqe)
			अवरोध;
	पूर्ण

	/*
	 * Now backwards through the CQ, removing CQ entries
	 * that match our QP by overwriting them with next entries.
	 */
	जबतक ((पूर्णांक) --prod_index - (पूर्णांक) hr_cq->cons_index >= 0) अणु
		cqe = get_cqe(hr_cq, prod_index & hr_cq->ib_cq.cqe);
		अगर ((roce_get_field(cqe->cqe_byte_16, CQE_BYTE_16_LOCAL_QPN_M,
				     CQE_BYTE_16_LOCAL_QPN_S) &
				     HNS_ROCE_CQE_QPN_MASK) == qpn) अणु
			/* In v1 engine, not support SRQ */
			++nमुक्तd;
		पूर्ण अन्यथा अगर (nमुक्तd) अणु
			dest = get_cqe(hr_cq, (prod_index + nमुक्तd) &
				       hr_cq->ib_cq.cqe);
			owner_bit = roce_get_bit(dest->cqe_byte_4,
						 CQE_BYTE_4_OWNER_S);
			स_नकल(dest, cqe, माप(*cqe));
			roce_set_bit(dest->cqe_byte_4, CQE_BYTE_4_OWNER_S,
				     owner_bit);
		पूर्ण
	पूर्ण

	अगर (nमुक्तd) अणु
		hr_cq->cons_index += nमुक्तd;
		hns_roce_v1_cq_set_ci(hr_cq, hr_cq->cons_index);
	पूर्ण
पूर्ण

अटल व्योम hns_roce_v1_cq_clean(काष्ठा hns_roce_cq *hr_cq, u32 qpn,
				 काष्ठा hns_roce_srq *srq)
अणु
	spin_lock_irq(&hr_cq->lock);
	__hns_roce_v1_cq_clean(hr_cq, qpn, srq);
	spin_unlock_irq(&hr_cq->lock);
पूर्ण

अटल व्योम hns_roce_v1_ग_लिखो_cqc(काष्ठा hns_roce_dev *hr_dev,
				  काष्ठा hns_roce_cq *hr_cq, व्योम *mb_buf,
				  u64 *mtts, dma_addr_t dma_handle)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_buf_list *tptr_buf = &priv->tptr_table.tptr_buf;
	काष्ठा hns_roce_cq_context *cq_context = mb_buf;
	dma_addr_t tptr_dma_addr;
	पूर्णांक offset;

	स_रखो(cq_context, 0, माप(*cq_context));

	/* Get the tptr क्रम this CQ. */
	offset = hr_cq->cqn * HNS_ROCE_V1_TPTR_ENTRY_SIZE;
	tptr_dma_addr = tptr_buf->map + offset;
	hr_cq->tptr_addr = (u16 *)(tptr_buf->buf + offset);

	/* Register cq_context members */
	roce_set_field(cq_context->cqc_byte_4,
		       CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_M,
		       CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_S, CQ_STATE_VALID);
	roce_set_field(cq_context->cqc_byte_4, CQ_CONTEXT_CQC_BYTE_4_CQN_M,
		       CQ_CONTEXT_CQC_BYTE_4_CQN_S, hr_cq->cqn);

	cq_context->cq_bt_l = cpu_to_le32((u32)dma_handle);

	roce_set_field(cq_context->cqc_byte_12,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_M,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_S,
		       ((u64)dma_handle >> 32));
	roce_set_field(cq_context->cqc_byte_12,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_M,
		       CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_S,
		       ilog2(hr_cq->cq_depth));
	roce_set_field(cq_context->cqc_byte_12, CQ_CONTEXT_CQC_BYTE_12_CEQN_M,
		       CQ_CONTEXT_CQC_BYTE_12_CEQN_S, hr_cq->vector);

	cq_context->cur_cqe_ba0_l = cpu_to_le32((u32)(mtts[0]));

	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_M,
		       CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_S, (mtts[0]) >> 32);
	/* Dedicated hardware, directly set 0 */
	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_M,
		       CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_S, 0);
	/**
	 * 44 = 32 + 12, When evaluating addr to hardware, shअगरt 12 because of
	 * using 4K page, and shअगरt more 32 because of
	 * calculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(cq_context->cqc_byte_20,
		       CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_M,
		       CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_S,
		       tptr_dma_addr >> 44);

	cq_context->cqe_tptr_addr_l = cpu_to_le32((u32)(tptr_dma_addr >> 12));

	roce_set_field(cq_context->cqc_byte_32,
		       CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_M,
		       CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_SE_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_CE_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CONTEXT_CQC_BYTE_32_NOTIFICATION_FLAG_S, 0);
	roce_set_bit(cq_context->cqc_byte_32,
		     CQ_CQNTEXT_CQC_BYTE_32_TYPE_OF_COMPLETION_NOTIFICATION_S,
		     0);
	/* The initial value of cq's ci is 0 */
	roce_set_field(cq_context->cqc_byte_32,
		       CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_M,
		       CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_S, 0);
पूर्ण

अटल पूर्णांक hns_roce_v1_req_notअगरy_cq(काष्ठा ib_cq *ibcq,
				     क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	u32 notअगरication_flag;
	__le32 करोorbell[2] = अणुपूर्ण;

	notअगरication_flag = (flags & IB_CQ_SOLICITED_MASK) ==
			    IB_CQ_SOLICITED ? CQ_DB_REQ_NOT : CQ_DB_REQ_NOT_SOL;
	/*
	 * flags = 0; Notअगरication Flag = 1, next
	 * flags = 1; Notअगरication Flag = 0, solocited
	 */
	करोorbell[0] =
		cpu_to_le32(hr_cq->cons_index & ((hr_cq->cq_depth << 1) - 1));
	roce_set_bit(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_HW_SYNS_S, 1);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_S, 3);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_CMD_MDF_S, 1);
	roce_set_field(करोorbell[1], ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_M,
		       ROCEE_DB_OTHERS_H_ROCEE_DB_OTH_INP_H_S,
		       hr_cq->cqn | notअगरication_flag);

	hns_roce_ग_लिखो64_k(करोorbell, hr_cq->db_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_poll_one(काष्ठा hns_roce_cq *hr_cq,
				काष्ठा hns_roce_qp **cur_qp, काष्ठा ib_wc *wc)
अणु
	पूर्णांक qpn;
	पूर्णांक is_send;
	u16 wqe_ctr;
	u32 status;
	u32 opcode;
	काष्ठा hns_roce_cqe *cqe;
	काष्ठा hns_roce_qp *hr_qp;
	काष्ठा hns_roce_wq *wq;
	काष्ठा hns_roce_wqe_ctrl_seg *sq_wqe;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);
	काष्ठा device *dev = &hr_dev->pdev->dev;

	/* Find cqe according consumer index */
	cqe = next_cqe_sw(hr_cq);
	अगर (!cqe)
		वापस -EAGAIN;

	++hr_cq->cons_index;
	/* Memory barrier */
	rmb();
	/* 0->SQ, 1->RQ */
	is_send  = !(roce_get_bit(cqe->cqe_byte_4, CQE_BYTE_4_SQ_RQ_FLAG_S));

	/* Local_qpn in UD cqe is always 1, so it needs to compute new qpn */
	अगर (roce_get_field(cqe->cqe_byte_16, CQE_BYTE_16_LOCAL_QPN_M,
			   CQE_BYTE_16_LOCAL_QPN_S) <= 1) अणु
		qpn = roce_get_field(cqe->cqe_byte_20, CQE_BYTE_20_PORT_NUM_M,
				     CQE_BYTE_20_PORT_NUM_S) +
		      roce_get_field(cqe->cqe_byte_16, CQE_BYTE_16_LOCAL_QPN_M,
				     CQE_BYTE_16_LOCAL_QPN_S) *
				     HNS_ROCE_MAX_PORTS;
	पूर्ण अन्यथा अणु
		qpn = roce_get_field(cqe->cqe_byte_16, CQE_BYTE_16_LOCAL_QPN_M,
				     CQE_BYTE_16_LOCAL_QPN_S);
	पूर्ण

	अगर (!*cur_qp || (qpn & HNS_ROCE_CQE_QPN_MASK) != (*cur_qp)->qpn) अणु
		hr_qp = __hns_roce_qp_lookup(hr_dev, qpn);
		अगर (unlikely(!hr_qp)) अणु
			dev_err(dev, "CQ %06lx with entry for unknown QPN %06x\n",
				hr_cq->cqn, (qpn & HNS_ROCE_CQE_QPN_MASK));
			वापस -EINVAL;
		पूर्ण

		*cur_qp = hr_qp;
	पूर्ण

	wc->qp = &(*cur_qp)->ibqp;
	wc->venकरोr_err = 0;

	status = roce_get_field(cqe->cqe_byte_4,
				CQE_BYTE_4_STATUS_OF_THE_OPERATION_M,
				CQE_BYTE_4_STATUS_OF_THE_OPERATION_S) &
				HNS_ROCE_CQE_STATUS_MASK;
	चयन (status) अणु
	हाल HNS_ROCE_CQE_SUCCESS:
		wc->status = IB_WC_SUCCESS;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		wc->status = IB_WC_LOC_LEN_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		wc->status = IB_WC_LOC_QP_OP_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_LOCAL_PROT_ERR:
		wc->status = IB_WC_LOC_PROT_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_WR_FLUSH_ERR:
		wc->status = IB_WC_WR_FLUSH_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_MEM_MANAGE_OPERATE_ERR:
		wc->status = IB_WC_MW_BIND_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_BAD_RESP_ERR:
		wc->status = IB_WC_BAD_RESP_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		wc->status = IB_WC_LOC_ACCESS_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		wc->status = IB_WC_REM_INV_REQ_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		wc->status = IB_WC_REM_ACCESS_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_REMOTE_OP_ERR:
		wc->status = IB_WC_REM_OP_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		wc->status = IB_WC_RETRY_EXC_ERR;
		अवरोध;
	हाल HNS_ROCE_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		wc->status = IB_WC_RNR_RETRY_EXC_ERR;
		अवरोध;
	शेष:
		wc->status = IB_WC_GENERAL_ERR;
		अवरोध;
	पूर्ण

	/* CQE status error, directly वापस */
	अगर (wc->status != IB_WC_SUCCESS)
		वापस 0;

	अगर (is_send) अणु
		/* SQ conrespond to CQE */
		sq_wqe = hns_roce_get_send_wqe(*cur_qp,
						roce_get_field(cqe->cqe_byte_4,
						CQE_BYTE_4_WQE_INDEX_M,
						CQE_BYTE_4_WQE_INDEX_S) &
						((*cur_qp)->sq.wqe_cnt-1));
		चयन (le32_to_cpu(sq_wqe->flag) & HNS_ROCE_WQE_OPCODE_MASK) अणु
		हाल HNS_ROCE_WQE_OPCODE_SEND:
			wc->opcode = IB_WC_SEND;
			अवरोध;
		हाल HNS_ROCE_WQE_OPCODE_RDMA_READ:
			wc->opcode = IB_WC_RDMA_READ;
			wc->byte_len = le32_to_cpu(cqe->byte_cnt);
			अवरोध;
		हाल HNS_ROCE_WQE_OPCODE_RDMA_WRITE:
			wc->opcode = IB_WC_RDMA_WRITE;
			अवरोध;
		हाल HNS_ROCE_WQE_OPCODE_LOCAL_INV:
			wc->opcode = IB_WC_LOCAL_INV;
			अवरोध;
		हाल HNS_ROCE_WQE_OPCODE_UD_SEND:
			wc->opcode = IB_WC_SEND;
			अवरोध;
		शेष:
			wc->status = IB_WC_GENERAL_ERR;
			अवरोध;
		पूर्ण
		wc->wc_flags = (le32_to_cpu(sq_wqe->flag) & HNS_ROCE_WQE_IMM ?
				IB_WC_WITH_IMM : 0);

		wq = &(*cur_qp)->sq;
		अगर ((*cur_qp)->sq_संकेत_bits) अणु
			/*
			 * If sg_संकेत_bit is 1,
			 * firstly tail poपूर्णांकer updated to wqe
			 * which current cqe correspond to
			 */
			wqe_ctr = (u16)roce_get_field(cqe->cqe_byte_4,
						      CQE_BYTE_4_WQE_INDEX_M,
						      CQE_BYTE_4_WQE_INDEX_S);
			wq->tail += (wqe_ctr - (u16)wq->tail) &
				    (wq->wqe_cnt - 1);
		पूर्ण
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
	पूर्ण अन्यथा अणु
		/* RQ conrespond to CQE */
		wc->byte_len = le32_to_cpu(cqe->byte_cnt);
		opcode = roce_get_field(cqe->cqe_byte_4,
					CQE_BYTE_4_OPERATION_TYPE_M,
					CQE_BYTE_4_OPERATION_TYPE_S) &
					HNS_ROCE_CQE_OPCODE_MASK;
		चयन (opcode) अणु
		हाल HNS_ROCE_OPCODE_RDMA_WITH_IMM_RECEIVE:
			wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
			wc->wc_flags = IB_WC_WITH_IMM;
			wc->ex.imm_data =
				cpu_to_be32(le32_to_cpu(cqe->immediate_data));
			अवरोध;
		हाल HNS_ROCE_OPCODE_SEND_DATA_RECEIVE:
			अगर (roce_get_bit(cqe->cqe_byte_4,
					 CQE_BYTE_4_IMM_INDICATOR_S)) अणु
				wc->opcode = IB_WC_RECV;
				wc->wc_flags = IB_WC_WITH_IMM;
				wc->ex.imm_data = cpu_to_be32(
					le32_to_cpu(cqe->immediate_data));
			पूर्ण अन्यथा अणु
				wc->opcode = IB_WC_RECV;
				wc->wc_flags = 0;
			पूर्ण
			अवरोध;
		शेष:
			wc->status = IB_WC_GENERAL_ERR;
			अवरोध;
		पूर्ण

		/* Update tail poपूर्णांकer, record wr_id */
		wq = &(*cur_qp)->rq;
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;
		wc->sl = (u8)roce_get_field(cqe->cqe_byte_20, CQE_BYTE_20_SL_M,
					    CQE_BYTE_20_SL_S);
		wc->src_qp = (u8)roce_get_field(cqe->cqe_byte_20,
						CQE_BYTE_20_REMOTE_QPN_M,
						CQE_BYTE_20_REMOTE_QPN_S);
		wc->wc_flags |= (roce_get_bit(cqe->cqe_byte_20,
					      CQE_BYTE_20_GRH_PRESENT_S) ?
					      IB_WC_GRH : 0);
		wc->pkey_index = (u16)roce_get_field(cqe->cqe_byte_28,
						     CQE_BYTE_28_P_KEY_IDX_M,
						     CQE_BYTE_28_P_KEY_IDX_S);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_roce_v1_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	काष्ठा hns_roce_qp *cur_qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;
	पूर्णांक ret;

	spin_lock_irqsave(&hr_cq->lock, flags);

	क्रम (npolled = 0; npolled < num_entries; ++npolled) अणु
		ret = hns_roce_v1_poll_one(hr_cq, &cur_qp, wc + npolled);
		अगर (ret)
			अवरोध;
	पूर्ण

	अगर (npolled) अणु
		*hr_cq->tptr_addr = hr_cq->cons_index &
			((hr_cq->cq_depth << 1) - 1);

		hns_roce_v1_cq_set_ci(hr_cq, hr_cq->cons_index);
	पूर्ण

	spin_unlock_irqrestore(&hr_cq->lock, flags);

	अगर (ret == 0 || ret == -EAGAIN)
		वापस npolled;
	अन्यथा
		वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_clear_hem(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_hem_table *table, पूर्णांक obj,
				 पूर्णांक step_idx)
अणु
	काष्ठा hns_roce_v1_priv *priv = hr_dev->priv;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	दीर्घ end = HW_SYNC_TIMEOUT_MSECS;
	__le32 bt_cmd_val[2] = अणु0पूर्ण;
	अचिन्हित दीर्घ flags = 0;
	व्योम __iomem *bt_cmd;
	u64 bt_ba = 0;

	चयन (table->type) अणु
	हाल HEM_TYPE_QPC:
		bt_ba = priv->bt_table.qpc_buf.map >> 12;
		अवरोध;
	हाल HEM_TYPE_MTPT:
		bt_ba = priv->bt_table.mtpt_buf.map >> 12;
		अवरोध;
	हाल HEM_TYPE_CQC:
		bt_ba = priv->bt_table.cqc_buf.map >> 12;
		अवरोध;
	हाल HEM_TYPE_SRQC:
		dev_dbg(dev, "HEM_TYPE_SRQC not support.\n");
		वापस -EINVAL;
	शेष:
		वापस 0;
	पूर्ण
	roce_set_field(bt_cmd_val[1], ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_M,
			ROCEE_BT_CMD_H_ROCEE_BT_CMD_MDF_S, table->type);
	roce_set_field(bt_cmd_val[1], ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_M,
		ROCEE_BT_CMD_H_ROCEE_BT_CMD_IN_MDF_S, obj);
	roce_set_bit(bt_cmd_val[1], ROCEE_BT_CMD_H_ROCEE_BT_CMD_S, 0);
	roce_set_bit(bt_cmd_val[1], ROCEE_BT_CMD_H_ROCEE_BT_CMD_HW_SYNS_S, 1);

	spin_lock_irqsave(&hr_dev->bt_cmd_lock, flags);

	bt_cmd = hr_dev->reg_base + ROCEE_BT_CMD_H_REG;

	जबतक (1) अणु
		अगर (पढ़ोl(bt_cmd) >> BT_CMD_SYNC_SHIFT) अणु
			अगर (!end) अणु
				dev_err(dev, "Write bt_cmd err,hw_sync is not zero.\n");
				spin_unlock_irqrestore(&hr_dev->bt_cmd_lock,
					flags);
				वापस -EBUSY;
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		mdelay(HW_SYNC_SLEEP_TIME_INTERVAL);
		end -= HW_SYNC_SLEEP_TIME_INTERVAL;
	पूर्ण

	bt_cmd_val[0] = cpu_to_le32(bt_ba);
	roce_set_field(bt_cmd_val[1], ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_M,
		ROCEE_BT_CMD_H_ROCEE_BT_CMD_BA_H_S, bt_ba >> 32);
	hns_roce_ग_लिखो64_k(bt_cmd_val, hr_dev->reg_base + ROCEE_BT_CMD_L_REG);

	spin_unlock_irqrestore(&hr_dev->bt_cmd_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_qp_modअगरy(काष्ठा hns_roce_dev *hr_dev,
				 क्रमागत hns_roce_qp_state cur_state,
				 क्रमागत hns_roce_qp_state new_state,
				 काष्ठा hns_roce_qp_context *context,
				 काष्ठा hns_roce_qp *hr_qp)
अणु
	अटल स्थिर u16
	op[HNS_ROCE_QP_NUM_STATE][HNS_ROCE_QP_NUM_STATE] = अणु
		[HNS_ROCE_QP_STATE_RST] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		[HNS_ROCE_QP_STATE_INIT] = HNS_ROCE_CMD_RST2INIT_QP,
		पूर्ण,
		[HNS_ROCE_QP_STATE_INIT] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		/* Note: In v1 engine, HW करोesn't support RST2INIT.
		 * We use RST2INIT cmd instead of INIT2INIT.
		 */
		[HNS_ROCE_QP_STATE_INIT] = HNS_ROCE_CMD_RST2INIT_QP,
		[HNS_ROCE_QP_STATE_RTR] = HNS_ROCE_CMD_INIT2RTR_QP,
		पूर्ण,
		[HNS_ROCE_QP_STATE_RTR] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		[HNS_ROCE_QP_STATE_RTS] = HNS_ROCE_CMD_RTR2RTS_QP,
		पूर्ण,
		[HNS_ROCE_QP_STATE_RTS] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		[HNS_ROCE_QP_STATE_RTS] = HNS_ROCE_CMD_RTS2RTS_QP,
		[HNS_ROCE_QP_STATE_SQD] = HNS_ROCE_CMD_RTS2SQD_QP,
		पूर्ण,
		[HNS_ROCE_QP_STATE_SQD] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		[HNS_ROCE_QP_STATE_RTS] = HNS_ROCE_CMD_SQD2RTS_QP,
		[HNS_ROCE_QP_STATE_SQD] = HNS_ROCE_CMD_SQD2SQD_QP,
		पूर्ण,
		[HNS_ROCE_QP_STATE_ERR] = अणु
		[HNS_ROCE_QP_STATE_RST] = HNS_ROCE_CMD_2RST_QP,
		[HNS_ROCE_QP_STATE_ERR] = HNS_ROCE_CMD_2ERR_QP,
		पूर्ण
	पूर्ण;

	काष्ठा hns_roce_cmd_mailbox *mailbox;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	पूर्णांक ret;

	अगर (cur_state >= HNS_ROCE_QP_NUM_STATE ||
	    new_state >= HNS_ROCE_QP_NUM_STATE ||
	    !op[cur_state][new_state]) अणु
		dev_err(dev, "[modify_qp]not support state %d to %d\n",
			cur_state, new_state);
		वापस -EINVAL;
	पूर्ण

	अगर (op[cur_state][new_state] == HNS_ROCE_CMD_2RST_QP)
		वापस hns_roce_cmd_mbox(hr_dev, 0, 0, hr_qp->qpn, 2,
					 HNS_ROCE_CMD_2RST_QP,
					 HNS_ROCE_CMD_TIMEOUT_MSECS);

	अगर (op[cur_state][new_state] == HNS_ROCE_CMD_2ERR_QP)
		वापस hns_roce_cmd_mbox(hr_dev, 0, 0, hr_qp->qpn, 2,
					 HNS_ROCE_CMD_2ERR_QP,
					 HNS_ROCE_CMD_TIMEOUT_MSECS);

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_नकल(mailbox->buf, context, माप(*context));

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, hr_qp->qpn, 0,
				op[cur_state][new_state],
				HNS_ROCE_CMD_TIMEOUT_MSECS);

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	वापस ret;
पूर्ण

अटल पूर्णांक find_wqe_mtt(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *hr_qp,
			u64 *sq_ba, u64 *rq_ba, dma_addr_t *bt_ba)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक count;

	count = hns_roce_mtr_find(hr_dev, &hr_qp->mtr, 0, sq_ba, 1, bt_ba);
	अगर (count < 1) अणु
		ibdev_err(ibdev, "Failed to find SQ ba\n");
		वापस -ENOBUFS;
	पूर्ण

	count = hns_roce_mtr_find(hr_dev, &hr_qp->mtr, hr_qp->rq.offset, rq_ba,
				  1, शून्य);
	अगर (!count) अणु
		ibdev_err(ibdev, "Failed to find RQ ba\n");
		वापस -ENOBUFS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_m_sqp(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_qp_attr *attr,
			     पूर्णांक attr_mask, क्रमागत ib_qp_state cur_state,
			     क्रमागत ib_qp_state new_state)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_sqp_context *context;
	dma_addr_t dma_handle = 0;
	u32 __iomem *addr;
	u64 sq_ba = 0;
	u64 rq_ba = 0;
	__le32 पंचांगp;
	u32 reg_val;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	/* Search QP buf's MTTs */
	अगर (find_wqe_mtt(hr_dev, hr_qp, &sq_ba, &rq_ba, &dma_handle))
		जाओ out;

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		roce_set_field(context->qp1c_bytes_4,
			       QP1C_BYTES_4_SQ_WQE_SHIFT_M,
			       QP1C_BYTES_4_SQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->sq.wqe_cnt));
		roce_set_field(context->qp1c_bytes_4,
			       QP1C_BYTES_4_RQ_WQE_SHIFT_M,
			       QP1C_BYTES_4_RQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->rq.wqe_cnt));
		roce_set_field(context->qp1c_bytes_4, QP1C_BYTES_4_PD_M,
			       QP1C_BYTES_4_PD_S, to_hr_pd(ibqp->pd)->pdn);

		context->sq_rq_bt_l = cpu_to_le32(dma_handle);
		roce_set_field(context->qp1c_bytes_12,
			       QP1C_BYTES_12_SQ_RQ_BT_H_M,
			       QP1C_BYTES_12_SQ_RQ_BT_H_S,
			       upper_32_bits(dma_handle));

		roce_set_field(context->qp1c_bytes_16, QP1C_BYTES_16_RQ_HEAD_M,
			       QP1C_BYTES_16_RQ_HEAD_S, hr_qp->rq.head);
		roce_set_field(context->qp1c_bytes_16, QP1C_BYTES_16_PORT_NUM_M,
			       QP1C_BYTES_16_PORT_NUM_S, hr_qp->phy_port);
		roce_set_bit(context->qp1c_bytes_16,
			     QP1C_BYTES_16_SIGNALING_TYPE_S,
			     hr_qp->sq_संकेत_bits);
		roce_set_bit(context->qp1c_bytes_16, QP1C_BYTES_16_RQ_BA_FLG_S,
			     1);
		roce_set_bit(context->qp1c_bytes_16, QP1C_BYTES_16_SQ_BA_FLG_S,
			     1);
		roce_set_bit(context->qp1c_bytes_16, QP1C_BYTES_16_QP1_ERR_S,
			     0);

		roce_set_field(context->qp1c_bytes_20, QP1C_BYTES_20_SQ_HEAD_M,
			       QP1C_BYTES_20_SQ_HEAD_S, hr_qp->sq.head);
		roce_set_field(context->qp1c_bytes_20, QP1C_BYTES_20_PKEY_IDX_M,
			       QP1C_BYTES_20_PKEY_IDX_S, attr->pkey_index);

		context->cur_rq_wqe_ba_l = cpu_to_le32(rq_ba);

		roce_set_field(context->qp1c_bytes_28,
			       QP1C_BYTES_28_CUR_RQ_WQE_BA_H_M,
			       QP1C_BYTES_28_CUR_RQ_WQE_BA_H_S,
			       upper_32_bits(rq_ba));
		roce_set_field(context->qp1c_bytes_28,
			       QP1C_BYTES_28_RQ_CUR_IDX_M,
			       QP1C_BYTES_28_RQ_CUR_IDX_S, 0);

		roce_set_field(context->qp1c_bytes_32,
			       QP1C_BYTES_32_RX_CQ_NUM_M,
			       QP1C_BYTES_32_RX_CQ_NUM_S,
			       to_hr_cq(ibqp->recv_cq)->cqn);
		roce_set_field(context->qp1c_bytes_32,
			       QP1C_BYTES_32_TX_CQ_NUM_M,
			       QP1C_BYTES_32_TX_CQ_NUM_S,
			       to_hr_cq(ibqp->send_cq)->cqn);

		context->cur_sq_wqe_ba_l = cpu_to_le32(sq_ba);

		roce_set_field(context->qp1c_bytes_40,
			       QP1C_BYTES_40_CUR_SQ_WQE_BA_H_M,
			       QP1C_BYTES_40_CUR_SQ_WQE_BA_H_S,
			       upper_32_bits(sq_ba));
		roce_set_field(context->qp1c_bytes_40,
			       QP1C_BYTES_40_SQ_CUR_IDX_M,
			       QP1C_BYTES_40_SQ_CUR_IDX_S, 0);

		/* Copy context to QP1C रेजिस्टर */
		addr = (u32 __iomem *)(hr_dev->reg_base +
				       ROCEE_QP1C_CFG0_0_REG +
				       hr_qp->phy_port * माप(*context));

		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_4), addr);
		ग_लिखोl(le32_to_cpu(context->sq_rq_bt_l), addr + 1);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_12), addr + 2);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_16), addr + 3);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_20), addr + 4);
		ग_लिखोl(le32_to_cpu(context->cur_rq_wqe_ba_l), addr + 5);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_28), addr + 6);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_32), addr + 7);
		ग_लिखोl(le32_to_cpu(context->cur_sq_wqe_ba_l), addr + 8);
		ग_लिखोl(le32_to_cpu(context->qp1c_bytes_40), addr + 9);
	पूर्ण

	/* Modअगरy QP1C status */
	reg_val = roce_पढ़ो(hr_dev, ROCEE_QP1C_CFG0_0_REG +
			    hr_qp->phy_port * माप(*context));
	पंचांगp = cpu_to_le32(reg_val);
	roce_set_field(पंचांगp, ROCEE_QP1C_CFG0_0_ROCEE_QP1C_QP_ST_M,
		       ROCEE_QP1C_CFG0_0_ROCEE_QP1C_QP_ST_S, new_state);
	reg_val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_QP1C_CFG0_0_REG +
		    hr_qp->phy_port * माप(*context), reg_val);

	hr_qp->state = new_state;
	अगर (new_state == IB_QPS_RESET) अणु
		hns_roce_v1_cq_clean(to_hr_cq(ibqp->recv_cq), hr_qp->qpn,
				     ibqp->srq ? to_hr_srq(ibqp->srq) : शून्य);
		अगर (ibqp->send_cq != ibqp->recv_cq)
			hns_roce_v1_cq_clean(to_hr_cq(ibqp->send_cq),
					     hr_qp->qpn, शून्य);

		hr_qp->rq.head = 0;
		hr_qp->rq.tail = 0;
		hr_qp->sq.head = 0;
		hr_qp->sq.tail = 0;
	पूर्ण

	kमुक्त(context);
	वापस 0;

out:
	kमुक्त(context);
	वापस -EINVAL;
पूर्ण

अटल bool check_qp_state(क्रमागत ib_qp_state cur_state,
			   क्रमागत ib_qp_state new_state)
अणु
	अटल स्थिर bool sm[][IB_QPS_ERR + 1] = अणु
		[IB_QPS_RESET] = अणु [IB_QPS_RESET] = true,
				   [IB_QPS_INIT] = true पूर्ण,
		[IB_QPS_INIT] = अणु [IB_QPS_RESET] = true,
				  [IB_QPS_INIT] = true,
				  [IB_QPS_RTR] = true,
				  [IB_QPS_ERR] = true पूर्ण,
		[IB_QPS_RTR] = अणु [IB_QPS_RESET] = true,
				 [IB_QPS_RTS] = true,
				 [IB_QPS_ERR] = true पूर्ण,
		[IB_QPS_RTS] = अणु [IB_QPS_RESET] = true, [IB_QPS_ERR] = true पूर्ण,
		[IB_QPS_SQD] = अणुपूर्ण,
		[IB_QPS_SQE] = अणुपूर्ण,
		[IB_QPS_ERR] = अणु [IB_QPS_RESET] = true, [IB_QPS_ERR] = true पूर्ण
	पूर्ण;

	वापस sm[cur_state][new_state];
पूर्ण

अटल पूर्णांक hns_roce_v1_m_qp(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_qp_attr *attr,
			    पूर्णांक attr_mask, क्रमागत ib_qp_state cur_state,
			    क्रमागत ib_qp_state new_state)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_qp_context *context;
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	dma_addr_t dma_handle_2 = 0;
	dma_addr_t dma_handle = 0;
	__le32 करोorbell[2] = अणु0पूर्ण;
	u64 *mtts_2 = शून्य;
	पूर्णांक ret = -EINVAL;
	u64 sq_ba = 0;
	u64 rq_ba = 0;
	u32 port;
	u32 port_num;
	u8 *dmac;
	u8 *smac;

	अगर (!check_qp_state(cur_state, new_state)) अणु
		ibdev_err(ibqp->device,
			  "not support QP(%u) status from %d to %d\n",
			  ibqp->qp_num, cur_state, new_state);
		वापस -EINVAL;
	पूर्ण

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	/* Search qp buf's mtts */
	अगर (find_wqe_mtt(hr_dev, hr_qp, &sq_ba, &rq_ba, &dma_handle))
		जाओ out;

	/* Search IRRL's mtts */
	mtts_2 = hns_roce_table_find(hr_dev, &hr_dev->qp_table.irrl_table,
				     hr_qp->qpn, &dma_handle_2);
	अगर (mtts_2 == शून्य) अणु
		dev_err(dev, "qp irrl_table find failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Reset to init
	 *	Mandatory param:
	 *	IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_PORT | IB_QP_ACCESS_FLAGS
	 *	Optional param: NA
	 */
	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_M,
			       QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_S,
			       to_hr_qp_type(hr_qp->ibqp.qp_type));

		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_ENABLE_FPMR_S, 0);
		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S,
			     !!(attr->qp_access_flags & IB_ACCESS_REMOTE_READ));
		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S,
			     !!(attr->qp_access_flags & IB_ACCESS_REMOTE_WRITE)
			     );
		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_ATOMIC_OPERATION_ENABLE_S,
			     !!(attr->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC)
			     );
		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_RDMAR_USE_S, 1);
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_M,
			       QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->sq.wqe_cnt));
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_M,
			       QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->rq.wqe_cnt));
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_PD_M,
			       QP_CONTEXT_QPC_BYTES_4_PD_S,
			       to_hr_pd(ibqp->pd)->pdn);
		hr_qp->access_flags = attr->qp_access_flags;
		roce_set_field(context->qpc_bytes_8,
			       QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_M,
			       QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_S,
			       to_hr_cq(ibqp->send_cq)->cqn);
		roce_set_field(context->qpc_bytes_8,
			       QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_M,
			       QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_S,
			       to_hr_cq(ibqp->recv_cq)->cqn);

		अगर (ibqp->srq)
			roce_set_field(context->qpc_bytes_12,
				       QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_M,
				       QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_S,
				       to_hr_srq(ibqp->srq)->srqn);

		roce_set_field(context->qpc_bytes_12,
			       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S,
			       attr->pkey_index);
		hr_qp->pkey_index = attr->pkey_index;
		roce_set_field(context->qpc_bytes_16,
			       QP_CONTEXT_QPC_BYTES_16_QP_NUM_M,
			       QP_CONTEXT_QPC_BYTES_16_QP_NUM_S, hr_qp->qpn);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_INIT) अणु
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_M,
			       QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_S,
			       to_hr_qp_type(hr_qp->ibqp.qp_type));
		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_ENABLE_FPMR_S, 0);
		अगर (attr_mask & IB_QP_ACCESS_FLAGS) अणु
			roce_set_bit(context->qpc_bytes_4,
				     QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S,
				     !!(attr->qp_access_flags &
				     IB_ACCESS_REMOTE_READ));
			roce_set_bit(context->qpc_bytes_4,
				     QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S,
				     !!(attr->qp_access_flags &
				     IB_ACCESS_REMOTE_WRITE));
		पूर्ण अन्यथा अणु
			roce_set_bit(context->qpc_bytes_4,
				     QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S,
				     !!(hr_qp->access_flags &
				     IB_ACCESS_REMOTE_READ));
			roce_set_bit(context->qpc_bytes_4,
				     QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S,
				     !!(hr_qp->access_flags &
				     IB_ACCESS_REMOTE_WRITE));
		पूर्ण

		roce_set_bit(context->qpc_bytes_4,
			     QP_CONTEXT_QPC_BYTE_4_RDMAR_USE_S, 1);
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_M,
			       QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->sq.wqe_cnt));
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_M,
			       QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_S,
			       ilog2((अचिन्हित पूर्णांक)hr_qp->rq.wqe_cnt));
		roce_set_field(context->qpc_bytes_4,
			       QP_CONTEXT_QPC_BYTES_4_PD_M,
			       QP_CONTEXT_QPC_BYTES_4_PD_S,
			       to_hr_pd(ibqp->pd)->pdn);

		roce_set_field(context->qpc_bytes_8,
			       QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_M,
			       QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_S,
			       to_hr_cq(ibqp->send_cq)->cqn);
		roce_set_field(context->qpc_bytes_8,
			       QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_M,
			       QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_S,
			       to_hr_cq(ibqp->recv_cq)->cqn);

		अगर (ibqp->srq)
			roce_set_field(context->qpc_bytes_12,
				       QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_M,
				       QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_S,
				       to_hr_srq(ibqp->srq)->srqn);
		अगर (attr_mask & IB_QP_PKEY_INDEX)
			roce_set_field(context->qpc_bytes_12,
				       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M,
				       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S,
				       attr->pkey_index);
		अन्यथा
			roce_set_field(context->qpc_bytes_12,
				       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M,
				       QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S,
				       hr_qp->pkey_index);

		roce_set_field(context->qpc_bytes_16,
			       QP_CONTEXT_QPC_BYTES_16_QP_NUM_M,
			       QP_CONTEXT_QPC_BYTES_16_QP_NUM_S, hr_qp->qpn);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		अगर ((attr_mask & IB_QP_ALT_PATH) ||
		    (attr_mask & IB_QP_ACCESS_FLAGS) ||
		    (attr_mask & IB_QP_PKEY_INDEX) ||
		    (attr_mask & IB_QP_QKEY)) अणु
			dev_err(dev, "INIT2RTR attr_mask error\n");
			जाओ out;
		पूर्ण

		dmac = (u8 *)attr->ah_attr.roce.dmac;

		context->sq_rq_bt_l = cpu_to_le32(dma_handle);
		roce_set_field(context->qpc_bytes_24,
			       QP_CONTEXT_QPC_BYTES_24_SQ_RQ_BT_H_M,
			       QP_CONTEXT_QPC_BYTES_24_SQ_RQ_BT_H_S,
			       upper_32_bits(dma_handle));
		roce_set_bit(context->qpc_bytes_24,
			     QP_CONTEXT_QPC_BYTE_24_REMOTE_ENABLE_E2E_CREDITS_S,
			     1);
		roce_set_field(context->qpc_bytes_24,
			       QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_M,
			       QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S,
			       attr->min_rnr_समयr);
		context->irrl_ba_l = cpu_to_le32((u32)(dma_handle_2));
		roce_set_field(context->qpc_bytes_32,
			       QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_M,
			       QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_S,
			       ((u32)(dma_handle_2 >> 32)) &
				QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_M);
		roce_set_field(context->qpc_bytes_32,
			       QP_CONTEXT_QPC_BYTES_32_MIG_STATE_M,
			       QP_CONTEXT_QPC_BYTES_32_MIG_STATE_S, 0);
		roce_set_bit(context->qpc_bytes_32,
			     QP_CONTEXT_QPC_BYTE_32_LOCAL_ENABLE_E2E_CREDITS_S,
			     1);
		roce_set_bit(context->qpc_bytes_32,
			     QP_CONTEXT_QPC_BYTE_32_SIGNALING_TYPE_S,
			     hr_qp->sq_संकेत_bits);

		port = (attr_mask & IB_QP_PORT) ? (attr->port_num - 1) :
			hr_qp->port;
		smac = (u8 *)hr_dev->dev_addr[port];
		/* when dmac equals smac or loop_idc is 1, it should loopback */
		अगर (ether_addr_equal_unaligned(dmac, smac) ||
		    hr_dev->loop_idc == 0x1)
			roce_set_bit(context->qpc_bytes_32,
			      QP_CONTEXT_QPC_BYTE_32_LOOPBACK_INDICATOR_S, 1);

		roce_set_bit(context->qpc_bytes_32,
			     QP_CONTEXT_QPC_BYTE_32_GLOBAL_HEADER_S,
			     rdma_ah_get_ah_flags(&attr->ah_attr));
		roce_set_field(context->qpc_bytes_32,
			       QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_M,
			       QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S,
			       ilog2((अचिन्हित पूर्णांक)attr->max_dest_rd_atomic));

		अगर (attr_mask & IB_QP_DEST_QPN)
			roce_set_field(context->qpc_bytes_36,
				       QP_CONTEXT_QPC_BYTES_36_DEST_QP_M,
				       QP_CONTEXT_QPC_BYTES_36_DEST_QP_S,
				       attr->dest_qp_num);

		/* Configure GID index */
		port_num = rdma_ah_get_port_num(&attr->ah_attr);
		roce_set_field(context->qpc_bytes_36,
			       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S,
				hns_get_gid_index(hr_dev,
						  port_num - 1,
						  grh->sgid_index));

		स_नकल(&(context->dmac_l), dmac, 4);

		roce_set_field(context->qpc_bytes_44,
			       QP_CONTEXT_QPC_BYTES_44_DMAC_H_M,
			       QP_CONTEXT_QPC_BYTES_44_DMAC_H_S,
			       *((u16 *)(&dmac[4])));
		roce_set_field(context->qpc_bytes_44,
			       QP_CONTEXT_QPC_BYTES_44_MAXIMUM_STATIC_RATE_M,
			       QP_CONTEXT_QPC_BYTES_44_MAXIMUM_STATIC_RATE_S,
			       rdma_ah_get_अटल_rate(&attr->ah_attr));
		roce_set_field(context->qpc_bytes_44,
			       QP_CONTEXT_QPC_BYTES_44_HOPLMT_M,
			       QP_CONTEXT_QPC_BYTES_44_HOPLMT_S,
			       grh->hop_limit);

		roce_set_field(context->qpc_bytes_48,
			       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_M,
			       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S,
			       grh->flow_label);
		roce_set_field(context->qpc_bytes_48,
			       QP_CONTEXT_QPC_BYTES_48_TCLASS_M,
			       QP_CONTEXT_QPC_BYTES_48_TCLASS_S,
			       grh->traffic_class);
		roce_set_field(context->qpc_bytes_48,
			       QP_CONTEXT_QPC_BYTES_48_MTU_M,
			       QP_CONTEXT_QPC_BYTES_48_MTU_S, attr->path_mtu);

		स_नकल(context->dgid, grh->dgid.raw,
		       माप(grh->dgid.raw));

		dev_dbg(dev, "dmac:%x :%lx\n", context->dmac_l,
			roce_get_field(context->qpc_bytes_44,
				       QP_CONTEXT_QPC_BYTES_44_DMAC_H_M,
				       QP_CONTEXT_QPC_BYTES_44_DMAC_H_S));

		roce_set_field(context->qpc_bytes_68,
			       QP_CONTEXT_QPC_BYTES_68_RQ_HEAD_M,
			       QP_CONTEXT_QPC_BYTES_68_RQ_HEAD_S,
			       hr_qp->rq.head);
		roce_set_field(context->qpc_bytes_68,
			       QP_CONTEXT_QPC_BYTES_68_RQ_CUR_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_68_RQ_CUR_INDEX_S, 0);

		context->cur_rq_wqe_ba_l = cpu_to_le32(rq_ba);

		roce_set_field(context->qpc_bytes_76,
			QP_CONTEXT_QPC_BYTES_76_CUR_RQ_WQE_BA_H_M,
			QP_CONTEXT_QPC_BYTES_76_CUR_RQ_WQE_BA_H_S,
			upper_32_bits(rq_ba));
		roce_set_field(context->qpc_bytes_76,
			       QP_CONTEXT_QPC_BYTES_76_RX_REQ_MSN_M,
			       QP_CONTEXT_QPC_BYTES_76_RX_REQ_MSN_S, 0);

		context->rx_rnr_समय = 0;

		roce_set_field(context->qpc_bytes_84,
			       QP_CONTEXT_QPC_BYTES_84_LAST_ACK_PSN_M,
			       QP_CONTEXT_QPC_BYTES_84_LAST_ACK_PSN_S,
			       attr->rq_psn - 1);
		roce_set_field(context->qpc_bytes_84,
			       QP_CONTEXT_QPC_BYTES_84_TRRL_HEAD_M,
			       QP_CONTEXT_QPC_BYTES_84_TRRL_HEAD_S, 0);

		roce_set_field(context->qpc_bytes_88,
			       QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_M,
			       QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S,
			       attr->rq_psn);
		roce_set_bit(context->qpc_bytes_88,
			     QP_CONTEXT_QPC_BYTES_88_RX_REQ_PSN_ERR_FLAG_S, 0);
		roce_set_bit(context->qpc_bytes_88,
			     QP_CONTEXT_QPC_BYTES_88_RX_LAST_OPCODE_FLG_S, 0);
		roce_set_field(context->qpc_bytes_88,
			QP_CONTEXT_QPC_BYTES_88_RQ_REQ_LAST_OPERATION_TYPE_M,
			QP_CONTEXT_QPC_BYTES_88_RQ_REQ_LAST_OPERATION_TYPE_S,
			0);
		roce_set_field(context->qpc_bytes_88,
			       QP_CONTEXT_QPC_BYTES_88_RQ_REQ_RDMA_WR_FLAG_M,
			       QP_CONTEXT_QPC_BYTES_88_RQ_REQ_RDMA_WR_FLAG_S,
			       0);

		context->dma_length = 0;
		context->r_key = 0;
		context->va_l = 0;
		context->va_h = 0;

		roce_set_field(context->qpc_bytes_108,
			       QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_M,
			       QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_S, 0);
		roce_set_bit(context->qpc_bytes_108,
			     QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_FLG_S, 0);
		roce_set_bit(context->qpc_bytes_108,
			     QP_CONTEXT_QPC_BYTES_108_TRRL_TDB_PSN_FLG_S, 0);

		roce_set_field(context->qpc_bytes_112,
			       QP_CONTEXT_QPC_BYTES_112_TRRL_TDB_PSN_M,
			       QP_CONTEXT_QPC_BYTES_112_TRRL_TDB_PSN_S, 0);
		roce_set_field(context->qpc_bytes_112,
			       QP_CONTEXT_QPC_BYTES_112_TRRL_TAIL_M,
			       QP_CONTEXT_QPC_BYTES_112_TRRL_TAIL_S, 0);

		/* For chip resp ack */
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_PORT_NUM_M,
			       QP_CONTEXT_QPC_BYTES_156_PORT_NUM_S,
			       hr_qp->phy_port);
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_SL_M,
			       QP_CONTEXT_QPC_BYTES_156_SL_S,
			       rdma_ah_get_sl(&attr->ah_attr));
		hr_qp->sl = rdma_ah_get_sl(&attr->ah_attr);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_RTR && new_state == IB_QPS_RTS) अणु
		/* If exist optional param, वापस error */
		अगर ((attr_mask & IB_QP_ALT_PATH) ||
		    (attr_mask & IB_QP_ACCESS_FLAGS) ||
		    (attr_mask & IB_QP_QKEY) ||
		    (attr_mask & IB_QP_PATH_MIG_STATE) ||
		    (attr_mask & IB_QP_CUR_STATE) ||
		    (attr_mask & IB_QP_MIN_RNR_TIMER)) अणु
			dev_err(dev, "RTR2RTS attr_mask error\n");
			जाओ out;
		पूर्ण

		context->rx_cur_sq_wqe_ba_l = cpu_to_le32(sq_ba);

		roce_set_field(context->qpc_bytes_120,
			       QP_CONTEXT_QPC_BYTES_120_RX_CUR_SQ_WQE_BA_H_M,
			       QP_CONTEXT_QPC_BYTES_120_RX_CUR_SQ_WQE_BA_H_S,
			       upper_32_bits(sq_ba));

		roce_set_field(context->qpc_bytes_124,
			       QP_CONTEXT_QPC_BYTES_124_RX_ACK_MSN_M,
			       QP_CONTEXT_QPC_BYTES_124_RX_ACK_MSN_S, 0);
		roce_set_field(context->qpc_bytes_124,
			       QP_CONTEXT_QPC_BYTES_124_IRRL_MSG_IDX_M,
			       QP_CONTEXT_QPC_BYTES_124_IRRL_MSG_IDX_S, 0);

		roce_set_field(context->qpc_bytes_128,
			       QP_CONTEXT_QPC_BYTES_128_RX_ACK_EPSN_M,
			       QP_CONTEXT_QPC_BYTES_128_RX_ACK_EPSN_S,
			       attr->sq_psn);
		roce_set_bit(context->qpc_bytes_128,
			     QP_CONTEXT_QPC_BYTES_128_RX_ACK_PSN_ERR_FLG_S, 0);
		roce_set_field(context->qpc_bytes_128,
			     QP_CONTEXT_QPC_BYTES_128_ACK_LAST_OPERATION_TYPE_M,
			     QP_CONTEXT_QPC_BYTES_128_ACK_LAST_OPERATION_TYPE_S,
			     0);
		roce_set_bit(context->qpc_bytes_128,
			     QP_CONTEXT_QPC_BYTES_128_IRRL_PSN_VLD_FLG_S, 0);

		roce_set_field(context->qpc_bytes_132,
			       QP_CONTEXT_QPC_BYTES_132_IRRL_PSN_M,
			       QP_CONTEXT_QPC_BYTES_132_IRRL_PSN_S, 0);
		roce_set_field(context->qpc_bytes_132,
			       QP_CONTEXT_QPC_BYTES_132_IRRL_TAIL_M,
			       QP_CONTEXT_QPC_BYTES_132_IRRL_TAIL_S, 0);

		roce_set_field(context->qpc_bytes_136,
			       QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_PSN_M,
			       QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_PSN_S,
			       attr->sq_psn);
		roce_set_field(context->qpc_bytes_136,
			       QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_FPKT_PSN_L_M,
			       QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_FPKT_PSN_L_S,
			       attr->sq_psn);

		roce_set_field(context->qpc_bytes_140,
			       QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_FPKT_PSN_H_M,
			       QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_FPKT_PSN_H_S,
			       (attr->sq_psn >> SQ_PSN_SHIFT));
		roce_set_field(context->qpc_bytes_140,
			       QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_MSN_M,
			       QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_MSN_S, 0);
		roce_set_bit(context->qpc_bytes_140,
			     QP_CONTEXT_QPC_BYTES_140_RNR_RETRY_FLG_S, 0);

		roce_set_field(context->qpc_bytes_148,
			       QP_CONTEXT_QPC_BYTES_148_CHECK_FLAG_M,
			       QP_CONTEXT_QPC_BYTES_148_CHECK_FLAG_S, 0);
		roce_set_field(context->qpc_bytes_148,
			       QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_M,
			       QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S,
			       attr->retry_cnt);
		roce_set_field(context->qpc_bytes_148,
			       QP_CONTEXT_QPC_BYTES_148_RNR_RETRY_COUNT_M,
			       QP_CONTEXT_QPC_BYTES_148_RNR_RETRY_COUNT_S,
			       attr->rnr_retry);
		roce_set_field(context->qpc_bytes_148,
			       QP_CONTEXT_QPC_BYTES_148_LSN_M,
			       QP_CONTEXT_QPC_BYTES_148_LSN_S, 0x100);

		context->rnr_retry = 0;

		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_RETRY_COUNT_INIT_M,
			       QP_CONTEXT_QPC_BYTES_156_RETRY_COUNT_INIT_S,
			       attr->retry_cnt);
		अगर (attr->समयout < 0x12) अणु
			dev_info(dev, "ack timeout value(0x%x) must bigger than 0x12.\n",
				 attr->समयout);
			roce_set_field(context->qpc_bytes_156,
				       QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M,
				       QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S,
				       0x12);
		पूर्ण अन्यथा अणु
			roce_set_field(context->qpc_bytes_156,
				       QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M,
				       QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S,
				       attr->समयout);
		पूर्ण
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_RNR_RETRY_COUNT_INIT_M,
			       QP_CONTEXT_QPC_BYTES_156_RNR_RETRY_COUNT_INIT_S,
			       attr->rnr_retry);
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_PORT_NUM_M,
			       QP_CONTEXT_QPC_BYTES_156_PORT_NUM_S,
			       hr_qp->phy_port);
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_SL_M,
			       QP_CONTEXT_QPC_BYTES_156_SL_S,
			       rdma_ah_get_sl(&attr->ah_attr));
		hr_qp->sl = rdma_ah_get_sl(&attr->ah_attr);
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_M,
			       QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S,
			       ilog2((अचिन्हित पूर्णांक)attr->max_rd_atomic));
		roce_set_field(context->qpc_bytes_156,
			       QP_CONTEXT_QPC_BYTES_156_ACK_REQ_IND_M,
			       QP_CONTEXT_QPC_BYTES_156_ACK_REQ_IND_S, 0);
		context->pkt_use_len = 0;

		roce_set_field(context->qpc_bytes_164,
			       QP_CONTEXT_QPC_BYTES_164_SQ_PSN_M,
			       QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S, attr->sq_psn);
		roce_set_field(context->qpc_bytes_164,
			       QP_CONTEXT_QPC_BYTES_164_IRRL_HEAD_M,
			       QP_CONTEXT_QPC_BYTES_164_IRRL_HEAD_S, 0);

		roce_set_field(context->qpc_bytes_168,
			       QP_CONTEXT_QPC_BYTES_168_RETRY_SQ_PSN_M,
			       QP_CONTEXT_QPC_BYTES_168_RETRY_SQ_PSN_S,
			       attr->sq_psn);
		roce_set_field(context->qpc_bytes_168,
			       QP_CONTEXT_QPC_BYTES_168_SGE_USE_FLA_M,
			       QP_CONTEXT_QPC_BYTES_168_SGE_USE_FLA_S, 0);
		roce_set_field(context->qpc_bytes_168,
			       QP_CONTEXT_QPC_BYTES_168_DB_TYPE_M,
			       QP_CONTEXT_QPC_BYTES_168_DB_TYPE_S, 0);
		roce_set_bit(context->qpc_bytes_168,
			     QP_CONTEXT_QPC_BYTES_168_MSG_LP_IND_S, 0);
		roce_set_bit(context->qpc_bytes_168,
			     QP_CONTEXT_QPC_BYTES_168_CSDB_LP_IND_S, 0);
		roce_set_bit(context->qpc_bytes_168,
			     QP_CONTEXT_QPC_BYTES_168_QP_ERR_FLG_S, 0);
		context->sge_use_len = 0;

		roce_set_field(context->qpc_bytes_176,
			       QP_CONTEXT_QPC_BYTES_176_DB_CUR_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_176_DB_CUR_INDEX_S, 0);
		roce_set_field(context->qpc_bytes_176,
			       QP_CONTEXT_QPC_BYTES_176_RETRY_DB_CUR_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_176_RETRY_DB_CUR_INDEX_S,
			       0);
		roce_set_field(context->qpc_bytes_180,
			       QP_CONTEXT_QPC_BYTES_180_SQ_CUR_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_180_SQ_CUR_INDEX_S, 0);
		roce_set_field(context->qpc_bytes_180,
			       QP_CONTEXT_QPC_BYTES_180_SQ_HEAD_M,
			       QP_CONTEXT_QPC_BYTES_180_SQ_HEAD_S, 0);

		context->tx_cur_sq_wqe_ba_l = cpu_to_le32(sq_ba);

		roce_set_field(context->qpc_bytes_188,
			       QP_CONTEXT_QPC_BYTES_188_TX_CUR_SQ_WQE_BA_H_M,
			       QP_CONTEXT_QPC_BYTES_188_TX_CUR_SQ_WQE_BA_H_S,
			       upper_32_bits(sq_ba));
		roce_set_bit(context->qpc_bytes_188,
			     QP_CONTEXT_QPC_BYTES_188_PKT_RETRY_FLG_S, 0);
		roce_set_field(context->qpc_bytes_188,
			       QP_CONTEXT_QPC_BYTES_188_TX_RETRY_CUR_INDEX_M,
			       QP_CONTEXT_QPC_BYTES_188_TX_RETRY_CUR_INDEX_S,
			       0);
	पूर्ण

	/* Every status migrate must change state */
	roce_set_field(context->qpc_bytes_144,
		       QP_CONTEXT_QPC_BYTES_144_QP_STATE_M,
		       QP_CONTEXT_QPC_BYTES_144_QP_STATE_S, new_state);

	/* SW pass context to HW */
	ret = hns_roce_v1_qp_modअगरy(hr_dev, to_hns_roce_state(cur_state),
				    to_hns_roce_state(new_state), context,
				    hr_qp);
	अगर (ret) अणु
		dev_err(dev, "hns_roce_qp_modify failed\n");
		जाओ out;
	पूर्ण

	/*
	 * Use rst2init to instead of init2init with drv,
	 * need to hw to flash RQ HEAD by DB again
	 */
	अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_INIT) अणु
		roce_set_field(करोorbell[0], RQ_DOORBELL_U32_4_RQ_HEAD_M,
			       RQ_DOORBELL_U32_4_RQ_HEAD_S, hr_qp->rq.head);
		roce_set_field(करोorbell[1], RQ_DOORBELL_U32_8_QPN_M,
			       RQ_DOORBELL_U32_8_QPN_S, hr_qp->qpn);
		roce_set_field(करोorbell[1], RQ_DOORBELL_U32_8_CMD_M,
			       RQ_DOORBELL_U32_8_CMD_S, 1);
		roce_set_bit(करोorbell[1], RQ_DOORBELL_U32_8_HW_SYNC_S, 1);

		अगर (ibqp->uobject) अणु
			hr_qp->rq.db_reg = hr_dev->reg_base +
				     hr_dev->odb_offset +
				     DB_REG_OFFSET * hr_dev->priv_uar.index;
		पूर्ण

		hns_roce_ग_लिखो64_k(करोorbell, hr_qp->rq.db_reg);
	पूर्ण

	hr_qp->state = new_state;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		hr_qp->resp_depth = attr->max_dest_rd_atomic;
	अगर (attr_mask & IB_QP_PORT) अणु
		hr_qp->port = attr->port_num - 1;
		hr_qp->phy_port = hr_dev->iboe.phy_port[hr_qp->port];
	पूर्ण

	अगर (new_state == IB_QPS_RESET && !ibqp->uobject) अणु
		hns_roce_v1_cq_clean(to_hr_cq(ibqp->recv_cq), hr_qp->qpn,
				     ibqp->srq ? to_hr_srq(ibqp->srq) : शून्य);
		अगर (ibqp->send_cq != ibqp->recv_cq)
			hns_roce_v1_cq_clean(to_hr_cq(ibqp->send_cq),
					     hr_qp->qpn, शून्य);

		hr_qp->rq.head = 0;
		hr_qp->rq.tail = 0;
		hr_qp->sq.head = 0;
		hr_qp->sq.tail = 0;
	पूर्ण
out:
	kमुक्त(context);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_modअगरy_qp(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
				 क्रमागत ib_qp_state cur_state,
				 क्रमागत ib_qp_state new_state)
अणु
	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	अगर (ibqp->qp_type == IB_QPT_GSI || ibqp->qp_type == IB_QPT_SMI)
		वापस hns_roce_v1_m_sqp(ibqp, attr, attr_mask, cur_state,
					 new_state);
	अन्यथा
		वापस hns_roce_v1_m_qp(ibqp, attr, attr_mask, cur_state,
					new_state);
पूर्ण

अटल क्रमागत ib_qp_state to_ib_qp_state(क्रमागत hns_roce_qp_state state)
अणु
	चयन (state) अणु
	हाल HNS_ROCE_QP_STATE_RST:
		वापस IB_QPS_RESET;
	हाल HNS_ROCE_QP_STATE_INIT:
		वापस IB_QPS_INIT;
	हाल HNS_ROCE_QP_STATE_RTR:
		वापस IB_QPS_RTR;
	हाल HNS_ROCE_QP_STATE_RTS:
		वापस IB_QPS_RTS;
	हाल HNS_ROCE_QP_STATE_SQD:
		वापस IB_QPS_SQD;
	हाल HNS_ROCE_QP_STATE_ERR:
		वापस IB_QPS_ERR;
	शेष:
		वापस IB_QPS_ERR;
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_v1_query_qpc(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_qp *hr_qp,
				 काष्ठा hns_roce_qp_context *hr_context)
अणु
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, hr_qp->qpn, 0,
				HNS_ROCE_CMD_QUERY_QP,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (!ret)
		स_नकल(hr_context, mailbox->buf, माप(*hr_context));
	अन्यथा
		dev_err(&hr_dev->pdev->dev, "QUERY QP cmd process error\n");

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_q_sqp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
			     पूर्णांक qp_attr_mask,
			     काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_sqp_context context;
	u32 addr;

	mutex_lock(&hr_qp->mutex);

	अगर (hr_qp->state == IB_QPS_RESET) अणु
		qp_attr->qp_state = IB_QPS_RESET;
		जाओ करोne;
	पूर्ण

	addr = ROCEE_QP1C_CFG0_0_REG +
		hr_qp->port * माप(काष्ठा hns_roce_sqp_context);
	context.qp1c_bytes_4 = cpu_to_le32(roce_पढ़ो(hr_dev, addr));
	context.sq_rq_bt_l = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 1));
	context.qp1c_bytes_12 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 2));
	context.qp1c_bytes_16 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 3));
	context.qp1c_bytes_20 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 4));
	context.cur_rq_wqe_ba_l = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 5));
	context.qp1c_bytes_28 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 6));
	context.qp1c_bytes_32 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 7));
	context.cur_sq_wqe_ba_l = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 8));
	context.qp1c_bytes_40 = cpu_to_le32(roce_पढ़ो(hr_dev, addr + 9));

	hr_qp->state = roce_get_field(context.qp1c_bytes_4,
				      QP1C_BYTES_4_QP_STATE_M,
				      QP1C_BYTES_4_QP_STATE_S);
	qp_attr->qp_state	= hr_qp->state;
	qp_attr->path_mtu	= IB_MTU_256;
	qp_attr->path_mig_state	= IB_MIG_ARMED;
	qp_attr->qkey		= QKEY_VAL;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	qp_attr->rq_psn		= 0;
	qp_attr->sq_psn		= 0;
	qp_attr->dest_qp_num	= 1;
	qp_attr->qp_access_flags = 6;

	qp_attr->pkey_index = roce_get_field(context.qp1c_bytes_20,
					     QP1C_BYTES_20_PKEY_IDX_M,
					     QP1C_BYTES_20_PKEY_IDX_S);
	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 0;
	qp_attr->max_dest_rd_atomic = 0;
	qp_attr->min_rnr_समयr = 0;
	qp_attr->समयout = 0;
	qp_attr->retry_cnt = 0;
	qp_attr->rnr_retry = 0;
	qp_attr->alt_समयout = 0;

करोne:
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr = hr_qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge = hr_qp->rq.max_gs;
	qp_attr->cap.max_send_wr = hr_qp->sq.wqe_cnt;
	qp_attr->cap.max_send_sge = hr_qp->sq.max_gs;
	qp_attr->cap.max_अंतरभूत_data = 0;
	qp_init_attr->cap = qp_attr->cap;
	qp_init_attr->create_flags = 0;

	mutex_unlock(&hr_qp->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_q_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
			    पूर्णांक qp_attr_mask,
			    काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_qp_context *context;
	पूर्णांक पंचांगp_qp_state;
	पूर्णांक ret = 0;
	पूर्णांक state;

	context = kzalloc(माप(*context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	स_रखो(qp_attr, 0, माप(*qp_attr));
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));

	mutex_lock(&hr_qp->mutex);

	अगर (hr_qp->state == IB_QPS_RESET) अणु
		qp_attr->qp_state = IB_QPS_RESET;
		जाओ करोne;
	पूर्ण

	ret = hns_roce_v1_query_qpc(hr_dev, hr_qp, context);
	अगर (ret) अणु
		dev_err(dev, "query qpc error\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	state = roce_get_field(context->qpc_bytes_144,
			       QP_CONTEXT_QPC_BYTES_144_QP_STATE_M,
			       QP_CONTEXT_QPC_BYTES_144_QP_STATE_S);
	पंचांगp_qp_state = (पूर्णांक)to_ib_qp_state((क्रमागत hns_roce_qp_state)state);
	अगर (पंचांगp_qp_state == -1) अणु
		dev_err(dev, "to_ib_qp_state error\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	hr_qp->state = (u8)पंचांगp_qp_state;
	qp_attr->qp_state = (क्रमागत ib_qp_state)hr_qp->state;
	qp_attr->path_mtu = (क्रमागत ib_mtu)roce_get_field(context->qpc_bytes_48,
					       QP_CONTEXT_QPC_BYTES_48_MTU_M,
					       QP_CONTEXT_QPC_BYTES_48_MTU_S);
	qp_attr->path_mig_state = IB_MIG_ARMED;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	अगर (hr_qp->ibqp.qp_type == IB_QPT_UD)
		qp_attr->qkey = QKEY_VAL;

	qp_attr->rq_psn = roce_get_field(context->qpc_bytes_88,
					 QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_M,
					 QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S);
	qp_attr->sq_psn = (u32)roce_get_field(context->qpc_bytes_164,
					     QP_CONTEXT_QPC_BYTES_164_SQ_PSN_M,
					     QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S);
	qp_attr->dest_qp_num = (u8)roce_get_field(context->qpc_bytes_36,
					QP_CONTEXT_QPC_BYTES_36_DEST_QP_M,
					QP_CONTEXT_QPC_BYTES_36_DEST_QP_S);
	qp_attr->qp_access_flags = ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S)) << 2) |
				   ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S)) << 1) |
				   ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_ATOMIC_OPERATION_ENABLE_S)) << 3);

	अगर (hr_qp->ibqp.qp_type == IB_QPT_RC) अणु
		काष्ठा ib_global_route *grh =
			rdma_ah_retrieve_grh(&qp_attr->ah_attr);

		rdma_ah_set_sl(&qp_attr->ah_attr,
			       roce_get_field(context->qpc_bytes_156,
					      QP_CONTEXT_QPC_BYTES_156_SL_M,
					      QP_CONTEXT_QPC_BYTES_156_SL_S));
		rdma_ah_set_ah_flags(&qp_attr->ah_attr, IB_AH_GRH);
		grh->flow_label =
			roce_get_field(context->qpc_bytes_48,
				       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_M,
				       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S);
		grh->sgid_index =
			roce_get_field(context->qpc_bytes_36,
				       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_M,
				       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S);
		grh->hop_limit =
			roce_get_field(context->qpc_bytes_44,
				       QP_CONTEXT_QPC_BYTES_44_HOPLMT_M,
				       QP_CONTEXT_QPC_BYTES_44_HOPLMT_S);
		grh->traffic_class =
			roce_get_field(context->qpc_bytes_48,
				       QP_CONTEXT_QPC_BYTES_48_TCLASS_M,
				       QP_CONTEXT_QPC_BYTES_48_TCLASS_S);

		स_नकल(grh->dgid.raw, context->dgid,
		       माप(grh->dgid.raw));
	पूर्ण

	qp_attr->pkey_index = roce_get_field(context->qpc_bytes_12,
			      QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M,
			      QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S);
	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 1 << roce_get_field(context->qpc_bytes_156,
				 QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_M,
				 QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S);
	qp_attr->max_dest_rd_atomic = 1 << roce_get_field(context->qpc_bytes_32,
				 QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_M,
				 QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S);
	qp_attr->min_rnr_समयr = (u8)(roce_get_field(context->qpc_bytes_24,
			QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_M,
			QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S));
	qp_attr->समयout = (u8)(roce_get_field(context->qpc_bytes_156,
			    QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M,
			    QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S));
	qp_attr->retry_cnt = roce_get_field(context->qpc_bytes_148,
			     QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_M,
			     QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S);
	qp_attr->rnr_retry = (u8)le32_to_cpu(context->rnr_retry);

करोne:
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr = hr_qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge = hr_qp->rq.max_gs;

	अगर (!ibqp->uobject) अणु
		qp_attr->cap.max_send_wr = hr_qp->sq.wqe_cnt;
		qp_attr->cap.max_send_sge = hr_qp->sq.max_gs;
	पूर्ण अन्यथा अणु
		qp_attr->cap.max_send_wr = 0;
		qp_attr->cap.max_send_sge = 0;
	पूर्ण

	qp_init_attr->cap = qp_attr->cap;

out:
	mutex_unlock(&hr_qp->mutex);
	kमुक्त(context);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
				पूर्णांक qp_attr_mask,
				काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	वापस hr_qp->करोorbell_qpn <= 1 ?
		hns_roce_v1_q_sqp(ibqp, qp_attr, qp_attr_mask, qp_init_attr) :
		hns_roce_v1_q_qp(ibqp, qp_attr, qp_attr_mask, qp_init_attr);
पूर्ण

पूर्णांक hns_roce_v1_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_cq *send_cq, *recv_cq;
	पूर्णांक ret;

	ret = hns_roce_v1_modअगरy_qp(ibqp, शून्य, 0, hr_qp->state, IB_QPS_RESET);
	अगर (ret)
		वापस ret;

	send_cq = hr_qp->ibqp.send_cq ? to_hr_cq(hr_qp->ibqp.send_cq) : शून्य;
	recv_cq = hr_qp->ibqp.recv_cq ? to_hr_cq(hr_qp->ibqp.recv_cq) : शून्य;

	hns_roce_lock_cqs(send_cq, recv_cq);
	अगर (!udata) अणु
		अगर (recv_cq)
			__hns_roce_v1_cq_clean(recv_cq, hr_qp->qpn,
					       (hr_qp->ibqp.srq ?
						to_hr_srq(hr_qp->ibqp.srq) :
						शून्य));

		अगर (send_cq && send_cq != recv_cq)
			__hns_roce_v1_cq_clean(send_cq, hr_qp->qpn, शून्य);
	पूर्ण
	hns_roce_qp_हटाओ(hr_dev, hr_qp);
	hns_roce_unlock_cqs(send_cq, recv_cq);

	hns_roce_qp_destroy(hr_dev, hr_qp, udata);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v1_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibcq->device);
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	काष्ठा device *dev = &hr_dev->pdev->dev;
	u32 cqe_cnt_ori;
	u32 cqe_cnt_cur;
	पूर्णांक रुको_समय = 0;

	/*
	 * Beक्रमe मुक्तing cq buffer, we need to ensure that the outstanding CQE
	 * have been written by checking the CQE counter.
	 */
	cqe_cnt_ori = roce_पढ़ो(hr_dev, ROCEE_SCAEP_WR_CQE_CNT);
	जबतक (1) अणु
		अगर (roce_पढ़ो(hr_dev, ROCEE_CAEP_CQE_WCMD_EMPTY) &
		    HNS_ROCE_CQE_WCMD_EMPTY_BIT)
			अवरोध;

		cqe_cnt_cur = roce_पढ़ो(hr_dev, ROCEE_SCAEP_WR_CQE_CNT);
		अगर ((cqe_cnt_cur - cqe_cnt_ori) >= HNS_ROCE_MIN_CQE_CNT)
			अवरोध;

		msleep(HNS_ROCE_EACH_FREE_CQ_WAIT_MSECS);
		अगर (रुको_समय > HNS_ROCE_MAX_FREE_CQ_WAIT_CNT) अणु
			dev_warn(dev, "Destroy cq 0x%lx timeout!\n",
				hr_cq->cqn);
			अवरोध;
		पूर्ण
		रुको_समय++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम set_eq_cons_index_v1(काष्ठा hns_roce_eq *eq, u32 req_not)
अणु
	roce_raw_ग_लिखो((eq->cons_index & HNS_ROCE_V1_CONS_IDX_M) |
		       (req_not << eq->log_entries), eq->db_reg);
पूर्ण

अटल व्योम hns_roce_v1_wq_catas_err_handle(काष्ठा hns_roce_dev *hr_dev,
					    काष्ठा hns_roce_aeqe *aeqe, पूर्णांक qpn)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;

	dev_warn(dev, "Local Work Queue Catastrophic Error.\n");
	चयन (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) अणु
	हाल HNS_ROCE_LWQCE_QPC_ERROR:
		dev_warn(dev, "QP %d, QPC error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_MTU_ERROR:
		dev_warn(dev, "QP %d, MTU error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_WQE_BA_ADDR_ERROR:
		dev_warn(dev, "QP %d, WQE BA addr error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_WQE_ADDR_ERROR:
		dev_warn(dev, "QP %d, WQE addr error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_SQ_WQE_SHIFT_ERROR:
		dev_warn(dev, "QP %d, WQE shift error\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_SL_ERROR:
		dev_warn(dev, "QP %d, SL error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LWQCE_PORT_ERROR:
		dev_warn(dev, "QP %d, port error.\n", qpn);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hns_roce_v1_local_wq_access_err_handle(काष्ठा hns_roce_dev *hr_dev,
						   काष्ठा hns_roce_aeqe *aeqe,
						   पूर्णांक qpn)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;

	dev_warn(dev, "Local Access Violation Work Queue Error.\n");
	चयन (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) अणु
	हाल HNS_ROCE_LAVWQE_R_KEY_VIOLATION:
		dev_warn(dev, "QP %d, R_key violation.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_LENGTH_ERROR:
		dev_warn(dev, "QP %d, length error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_VA_ERROR:
		dev_warn(dev, "QP %d, VA error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_PD_ERROR:
		dev_err(dev, "QP %d, PD error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_RW_ACC_ERROR:
		dev_warn(dev, "QP %d, rw acc error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_KEY_STATE_ERROR:
		dev_warn(dev, "QP %d, key state error.\n", qpn);
		अवरोध;
	हाल HNS_ROCE_LAVWQE_MR_OPERATION_ERROR:
		dev_warn(dev, "QP %d, MR operation error.\n", qpn);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hns_roce_v1_qp_err_handle(काष्ठा hns_roce_dev *hr_dev,
				      काष्ठा hns_roce_aeqe *aeqe,
				      पूर्णांक event_type)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;
	पूर्णांक phy_port;
	पूर्णांक qpn;

	qpn = roce_get_field(aeqe->event.queue_event.num,
			     HNS_ROCE_AEQE_EVENT_QP_EVENT_QP_QPN_M,
			     HNS_ROCE_AEQE_EVENT_QP_EVENT_QP_QPN_S);
	phy_port = roce_get_field(aeqe->event.queue_event.num,
				  HNS_ROCE_AEQE_EVENT_QP_EVENT_PORT_NUM_M,
				  HNS_ROCE_AEQE_EVENT_QP_EVENT_PORT_NUM_S);
	अगर (qpn <= 1)
		qpn = HNS_ROCE_MAX_PORTS * qpn + phy_port;

	चयन (event_type) अणु
	हाल HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		dev_warn(dev, "Invalid Req Local Work Queue Error.\n"
			 "QP %d, phy_port %d.\n", qpn, phy_port);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		hns_roce_v1_wq_catas_err_handle(hr_dev, aeqe, qpn);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
		hns_roce_v1_local_wq_access_err_handle(hr_dev, aeqe, qpn);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	hns_roce_qp_event(hr_dev, qpn, event_type);
पूर्ण

अटल व्योम hns_roce_v1_cq_err_handle(काष्ठा hns_roce_dev *hr_dev,
				      काष्ठा hns_roce_aeqe *aeqe,
				      पूर्णांक event_type)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;
	u32 cqn;

	cqn = roce_get_field(aeqe->event.queue_event.num,
			     HNS_ROCE_AEQE_EVENT_CQ_EVENT_CQ_CQN_M,
			     HNS_ROCE_AEQE_EVENT_CQ_EVENT_CQ_CQN_S);

	चयन (event_type) अणु
	हाल HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		dev_warn(dev, "CQ 0x%x access err.\n", cqn);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
		dev_warn(dev, "CQ 0x%x overflow\n", cqn);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID:
		dev_warn(dev, "CQ 0x%x ID invalid.\n", cqn);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	hns_roce_cq_event(hr_dev, cqn, event_type);
पूर्ण

अटल व्योम hns_roce_v1_db_overflow_handle(काष्ठा hns_roce_dev *hr_dev,
					   काष्ठा hns_roce_aeqe *aeqe)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;

	चयन (roce_get_field(aeqe->asyn, HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M,
			       HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S)) अणु
	हाल HNS_ROCE_DB_SUBTYPE_SDB_OVF:
		dev_warn(dev, "SDB overflow.\n");
		अवरोध;
	हाल HNS_ROCE_DB_SUBTYPE_SDB_ALM_OVF:
		dev_warn(dev, "SDB almost overflow.\n");
		अवरोध;
	हाल HNS_ROCE_DB_SUBTYPE_SDB_ALM_EMP:
		dev_warn(dev, "SDB almost empty.\n");
		अवरोध;
	हाल HNS_ROCE_DB_SUBTYPE_ODB_OVF:
		dev_warn(dev, "ODB overflow.\n");
		अवरोध;
	हाल HNS_ROCE_DB_SUBTYPE_ODB_ALM_OVF:
		dev_warn(dev, "ODB almost overflow.\n");
		अवरोध;
	हाल HNS_ROCE_DB_SUBTYPE_ODB_ALM_EMP:
		dev_warn(dev, "SDB almost empty.\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा hns_roce_aeqe *get_aeqe_v1(काष्ठा hns_roce_eq *eq, u32 entry)
अणु
	अचिन्हित दीर्घ off = (entry & (eq->entries - 1)) * HNS_ROCE_AEQE_SIZE;

	वापस (काष्ठा hns_roce_aeqe *)((u8 *)
		(eq->buf_list[off / HNS_ROCE_BA_SIZE].buf) +
		off % HNS_ROCE_BA_SIZE);
पूर्ण

अटल काष्ठा hns_roce_aeqe *next_aeqe_sw_v1(काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_aeqe *aeqe = get_aeqe_v1(eq, eq->cons_index);

	वापस (roce_get_bit(aeqe->asyn, HNS_ROCE_AEQE_U32_4_OWNER_S) ^
		!!(eq->cons_index & eq->entries)) ? aeqe : शून्य;
पूर्ण

अटल पूर्णांक hns_roce_v1_aeq_पूर्णांक(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_aeqe *aeqe;
	पूर्णांक aeqes_found = 0;
	पूर्णांक event_type;

	जबतक ((aeqe = next_aeqe_sw_v1(eq))) अणु
		/* Make sure we पढ़ो the AEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		dev_dbg(dev, "aeqe = %pK, aeqe->asyn.event_type = 0x%lx\n",
			aeqe,
			roce_get_field(aeqe->asyn,
				       HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M,
				       HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S));
		event_type = roce_get_field(aeqe->asyn,
					    HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M,
					    HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S);
		चयन (event_type) अणु
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG:
			dev_warn(dev, "PATH MIG not supported\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_COMM_EST:
			dev_warn(dev, "COMMUNICATION established\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
			dev_warn(dev, "SQ DRAINED not supported\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
			dev_warn(dev, "PATH MIG failed\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
			hns_roce_v1_qp_err_handle(hr_dev, aeqe, event_type);
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
		हाल HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
			dev_warn(dev, "SRQ not support!\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
		हाल HNS_ROCE_EVENT_TYPE_CQ_ID_INVALID:
			hns_roce_v1_cq_err_handle(hr_dev, aeqe, event_type);
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_PORT_CHANGE:
			dev_warn(dev, "port change.\n");
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_MB:
			hns_roce_cmd_event(hr_dev,
					   le16_to_cpu(aeqe->event.cmd.token),
					   aeqe->event.cmd.status,
					   le64_to_cpu(aeqe->event.cmd.out_param
					   ));
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_DB_OVERFLOW:
			hns_roce_v1_db_overflow_handle(hr_dev, aeqe);
			अवरोध;
		शेष:
			dev_warn(dev, "Unhandled event %d on EQ %d at idx %u.\n",
				 event_type, eq->eqn, eq->cons_index);
			अवरोध;
		पूर्ण

		eq->cons_index++;
		aeqes_found = 1;

		अगर (eq->cons_index > 2 * hr_dev->caps.aeqe_depth - 1)
			eq->cons_index = 0;
	पूर्ण

	set_eq_cons_index_v1(eq, 0);

	वापस aeqes_found;
पूर्ण

अटल काष्ठा hns_roce_ceqe *get_ceqe_v1(काष्ठा hns_roce_eq *eq, u32 entry)
अणु
	अचिन्हित दीर्घ off = (entry & (eq->entries - 1)) * HNS_ROCE_CEQE_SIZE;

	वापस (काष्ठा hns_roce_ceqe *)((u8 *)
			(eq->buf_list[off / HNS_ROCE_BA_SIZE].buf) +
			off % HNS_ROCE_BA_SIZE);
पूर्ण

अटल काष्ठा hns_roce_ceqe *next_ceqe_sw_v1(काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_ceqe *ceqe = get_ceqe_v1(eq, eq->cons_index);

	वापस (!!(roce_get_bit(ceqe->comp,
		HNS_ROCE_CEQE_CEQE_COMP_OWNER_S))) ^
		(!!(eq->cons_index & eq->entries)) ? ceqe : शून्य;
पूर्ण

अटल पूर्णांक hns_roce_v1_ceq_पूर्णांक(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_ceqe *ceqe;
	पूर्णांक ceqes_found = 0;
	u32 cqn;

	जबतक ((ceqe = next_ceqe_sw_v1(eq))) अणु
		/* Make sure we पढ़ो CEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		cqn = roce_get_field(ceqe->comp,
				     HNS_ROCE_CEQE_CEQE_COMP_CQN_M,
				     HNS_ROCE_CEQE_CEQE_COMP_CQN_S);
		hns_roce_cq_completion(hr_dev, cqn);

		++eq->cons_index;
		ceqes_found = 1;

		अगर (eq->cons_index >
		    EQ_DEPTH_COEFF * hr_dev->caps.ceqe_depth - 1)
			eq->cons_index = 0;
	पूर्ण

	set_eq_cons_index_v1(eq, 0);

	वापस ceqes_found;
पूर्ण

अटल irqवापस_t hns_roce_v1_msix_पूर्णांकerrupt_eq(पूर्णांक irq, व्योम *eq_ptr)
अणु
	काष्ठा hns_roce_eq  *eq  = eq_ptr;
	काष्ठा hns_roce_dev *hr_dev = eq->hr_dev;
	पूर्णांक पूर्णांक_work;

	अगर (eq->type_flag == HNS_ROCE_CEQ)
		/* CEQ irq routine, CEQ is pulse irq, not clear */
		पूर्णांक_work = hns_roce_v1_ceq_पूर्णांक(hr_dev, eq);
	अन्यथा
		/* AEQ irq routine, AEQ is pulse irq, not clear */
		पूर्णांक_work = hns_roce_v1_aeq_पूर्णांक(hr_dev, eq);

	वापस IRQ_RETVAL(पूर्णांक_work);
पूर्ण

अटल irqवापस_t hns_roce_v1_msix_पूर्णांकerrupt_abn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hns_roce_dev *hr_dev = dev_id;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	पूर्णांक पूर्णांक_work = 0;
	u32 caepaemask_val;
	u32 cealmovf_val;
	u32 caepaest_val;
	u32 aeshअगरt_val;
	u32 ceshअगरt_val;
	u32 cemask_val;
	__le32 पंचांगp;
	पूर्णांक i;

	/*
	 * Abnormal पूर्णांकerrupt:
	 * AEQ overflow, ECC multi-bit err, CEQ overflow must clear
	 * पूर्णांकerrupt, mask irq, clear irq, cancel mask operation
	 */
	aeshअगरt_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_AEQC_AEQE_SHIFT_REG);
	पंचांगp = cpu_to_le32(aeshअगरt_val);

	/* AEQE overflow */
	अगर (roce_get_bit(पंचांगp,
		ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQ_ALM_OVF_INT_ST_S) == 1) अणु
		dev_warn(dev, "AEQ overflow!\n");

		/* Set mask */
		caepaemask_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_AE_MASK_REG);
		पंचांगp = cpu_to_le32(caepaemask_val);
		roce_set_bit(पंचांगp, ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S,
			     HNS_ROCE_INT_MASK_ENABLE);
		caepaemask_val = le32_to_cpu(पंचांगp);
		roce_ग_लिखो(hr_dev, ROCEE_CAEP_AE_MASK_REG, caepaemask_val);

		/* Clear पूर्णांक state(INT_WC : ग_लिखो 1 clear) */
		caepaest_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_AE_ST_REG);
		पंचांगp = cpu_to_le32(caepaest_val);
		roce_set_bit(पंचांगp, ROCEE_CAEP_AE_ST_CAEP_AEQ_ALM_OVF_S, 1);
		caepaest_val = le32_to_cpu(पंचांगp);
		roce_ग_लिखो(hr_dev, ROCEE_CAEP_AE_ST_REG, caepaest_val);

		/* Clear mask */
		caepaemask_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_AE_MASK_REG);
		पंचांगp = cpu_to_le32(caepaemask_val);
		roce_set_bit(पंचांगp, ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S,
			     HNS_ROCE_INT_MASK_DISABLE);
		caepaemask_val = le32_to_cpu(पंचांगp);
		roce_ग_लिखो(hr_dev, ROCEE_CAEP_AE_MASK_REG, caepaemask_val);
	पूर्ण

	/* CEQ almost overflow */
	क्रम (i = 0; i < hr_dev->caps.num_comp_vectors; i++) अणु
		ceshअगरt_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_CEQC_SHIFT_0_REG +
					i * CEQ_REG_OFFSET);
		पंचांगp = cpu_to_le32(ceshअगरt_val);

		अगर (roce_get_bit(पंचांगp,
			ROCEE_CAEP_CEQC_SHIFT_CAEP_CEQ_ALM_OVF_INT_ST_S) == 1) अणु
			dev_warn(dev, "CEQ[%d] almost overflow!\n", i);
			पूर्णांक_work++;

			/* Set mask */
			cemask_val = roce_पढ़ो(hr_dev,
					       ROCEE_CAEP_CE_IRQ_MASK_0_REG +
					       i * CEQ_REG_OFFSET);
			पंचांगp = cpu_to_le32(cemask_val);
			roce_set_bit(पंचांगp,
				ROCEE_CAEP_CE_IRQ_MASK_CAEP_CEQ_ALM_OVF_MASK_S,
				HNS_ROCE_INT_MASK_ENABLE);
			cemask_val = le32_to_cpu(पंचांगp);
			roce_ग_लिखो(hr_dev, ROCEE_CAEP_CE_IRQ_MASK_0_REG +
				   i * CEQ_REG_OFFSET, cemask_val);

			/* Clear पूर्णांक state(INT_WC : ग_लिखो 1 clear) */
			cealmovf_val = roce_पढ़ो(hr_dev,
				       ROCEE_CAEP_CEQ_ALM_OVF_0_REG +
				       i * CEQ_REG_OFFSET);
			पंचांगp = cpu_to_le32(cealmovf_val);
			roce_set_bit(पंचांगp,
				     ROCEE_CAEP_CEQ_ALM_OVF_CAEP_CEQ_ALM_OVF_S,
				     1);
			cealmovf_val = le32_to_cpu(पंचांगp);
			roce_ग_लिखो(hr_dev, ROCEE_CAEP_CEQ_ALM_OVF_0_REG +
				   i * CEQ_REG_OFFSET, cealmovf_val);

			/* Clear mask */
			cemask_val = roce_पढ़ो(hr_dev,
				     ROCEE_CAEP_CE_IRQ_MASK_0_REG +
				     i * CEQ_REG_OFFSET);
			पंचांगp = cpu_to_le32(cemask_val);
			roce_set_bit(पंचांगp,
			       ROCEE_CAEP_CE_IRQ_MASK_CAEP_CEQ_ALM_OVF_MASK_S,
			       HNS_ROCE_INT_MASK_DISABLE);
			cemask_val = le32_to_cpu(पंचांगp);
			roce_ग_लिखो(hr_dev, ROCEE_CAEP_CE_IRQ_MASK_0_REG +
				   i * CEQ_REG_OFFSET, cemask_val);
		पूर्ण
	पूर्ण

	/* ECC multi-bit error alarm */
	dev_warn(dev, "ECC UCERR ALARM: 0x%x, 0x%x, 0x%x\n",
		 roce_पढ़ो(hr_dev, ROCEE_ECC_UCERR_ALM0_REG),
		 roce_पढ़ो(hr_dev, ROCEE_ECC_UCERR_ALM1_REG),
		 roce_पढ़ो(hr_dev, ROCEE_ECC_UCERR_ALM2_REG));

	dev_warn(dev, "ECC CERR ALARM: 0x%x, 0x%x, 0x%x\n",
		 roce_पढ़ो(hr_dev, ROCEE_ECC_CERR_ALM0_REG),
		 roce_पढ़ो(hr_dev, ROCEE_ECC_CERR_ALM1_REG),
		 roce_पढ़ो(hr_dev, ROCEE_ECC_CERR_ALM2_REG));

	वापस IRQ_RETVAL(पूर्णांक_work);
पूर्ण

अटल व्योम hns_roce_v1_पूर्णांक_mask_enable(काष्ठा hns_roce_dev *hr_dev)
अणु
	u32 aemask_val;
	पूर्णांक masken = 0;
	__le32 पंचांगp;
	पूर्णांक i;

	/* AEQ INT */
	aemask_val = roce_पढ़ो(hr_dev, ROCEE_CAEP_AE_MASK_REG);
	पंचांगp = cpu_to_le32(aemask_val);
	roce_set_bit(पंचांगp, ROCEE_CAEP_AE_MASK_CAEP_AEQ_ALM_OVF_MASK_S,
		     masken);
	roce_set_bit(पंचांगp, ROCEE_CAEP_AE_MASK_CAEP_AE_IRQ_MASK_S, masken);
	aemask_val = le32_to_cpu(पंचांगp);
	roce_ग_लिखो(hr_dev, ROCEE_CAEP_AE_MASK_REG, aemask_val);

	/* CEQ INT */
	क्रम (i = 0; i < hr_dev->caps.num_comp_vectors; i++) अणु
		/* IRQ mask */
		roce_ग_लिखो(hr_dev, ROCEE_CAEP_CE_IRQ_MASK_0_REG +
			   i * CEQ_REG_OFFSET, masken);
	पूर्ण
पूर्ण

अटल व्योम hns_roce_v1_मुक्त_eq(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_eq *eq)
अणु
	पूर्णांक npages = (PAGE_ALIGN(eq->eqe_size * eq->entries) +
		      HNS_ROCE_BA_SIZE - 1) / HNS_ROCE_BA_SIZE;
	पूर्णांक i;

	अगर (!eq->buf_list)
		वापस;

	क्रम (i = 0; i < npages; ++i)
		dma_मुक्त_coherent(&hr_dev->pdev->dev, HNS_ROCE_BA_SIZE,
				  eq->buf_list[i].buf, eq->buf_list[i].map);

	kमुक्त(eq->buf_list);
पूर्ण

अटल व्योम hns_roce_v1_enable_eq(काष्ठा hns_roce_dev *hr_dev, पूर्णांक eq_num,
				  पूर्णांक enable_flag)
अणु
	व्योम __iomem *eqc = hr_dev->eq_table.eqc_base[eq_num];
	__le32 पंचांगp;
	u32 val;

	val = पढ़ोl(eqc);
	पंचांगp = cpu_to_le32(val);

	अगर (enable_flag)
		roce_set_field(पंचांगp,
			       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_M,
			       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_S,
			       HNS_ROCE_EQ_STAT_VALID);
	अन्यथा
		roce_set_field(पंचांगp,
			       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_M,
			       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_S,
			       HNS_ROCE_EQ_STAT_INVALID);

	val = le32_to_cpu(पंचांगp);
	ग_लिखोl(val, eqc);
पूर्ण

अटल पूर्णांक hns_roce_v1_create_eq(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_eq *eq)
अणु
	व्योम __iomem *eqc = hr_dev->eq_table.eqc_base[eq->eqn];
	काष्ठा device *dev = &hr_dev->pdev->dev;
	dma_addr_t पंचांगp_dma_addr;
	u32 eqcuridx_val;
	u32 eqconsindx_val;
	u32 eqshअगरt_val;
	__le32 पंचांगp2 = 0;
	__le32 पंचांगp1 = 0;
	__le32 पंचांगp = 0;
	पूर्णांक num_bas;
	पूर्णांक ret;
	पूर्णांक i;

	num_bas = (PAGE_ALIGN(eq->entries * eq->eqe_size) +
		   HNS_ROCE_BA_SIZE - 1) / HNS_ROCE_BA_SIZE;

	अगर ((eq->entries * eq->eqe_size) > HNS_ROCE_BA_SIZE) अणु
		dev_err(dev, "[error]eq buf %d gt ba size(%d) need bas=%d\n",
			(eq->entries * eq->eqe_size), HNS_ROCE_BA_SIZE,
			num_bas);
		वापस -EINVAL;
	पूर्ण

	eq->buf_list = kसुस्मृति(num_bas, माप(*eq->buf_list), GFP_KERNEL);
	अगर (!eq->buf_list)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_bas; ++i) अणु
		eq->buf_list[i].buf = dma_alloc_coherent(dev, HNS_ROCE_BA_SIZE,
							 &पंचांगp_dma_addr,
							 GFP_KERNEL);
		अगर (!eq->buf_list[i].buf) अणु
			ret = -ENOMEM;
			जाओ err_out_मुक्त_pages;
		पूर्ण

		eq->buf_list[i].map = पंचांगp_dma_addr;
	पूर्ण
	eq->cons_index = 0;
	roce_set_field(पंचांगp, ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_M,
		       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_STATE_S,
		       HNS_ROCE_EQ_STAT_INVALID);
	roce_set_field(पंचांगp, ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_AEQE_SHIFT_M,
		       ROCEE_CAEP_AEQC_AEQE_SHIFT_CAEP_AEQC_AEQE_SHIFT_S,
		       eq->log_entries);
	eqshअगरt_val = le32_to_cpu(पंचांगp);
	ग_लिखोl(eqshअगरt_val, eqc);

	/* Configure eq extended address 12~44bit */
	ग_लिखोl((u32)(eq->buf_list[0].map >> 12), eqc + 4);

	/*
	 * Configure eq extended address 45~49 bit.
	 * 44 = 32 + 12, When evaluating addr to hardware, shअगरt 12 because of
	 * using 4K page, and shअगरt more 32 because of
	 * calculating the high 32 bit value evaluated to hardware.
	 */
	roce_set_field(पंचांगp1, ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQ_BT_H_M,
		       ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQ_BT_H_S,
		       eq->buf_list[0].map >> 44);
	roce_set_field(पंचांगp1, ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQE_CUR_IDX_M,
		       ROCEE_CAEP_AEQE_CUR_IDX_CAEP_AEQE_CUR_IDX_S, 0);
	eqcuridx_val = le32_to_cpu(पंचांगp1);
	ग_लिखोl(eqcuridx_val, eqc + 8);

	/* Configure eq consumer index */
	roce_set_field(पंचांगp2, ROCEE_CAEP_AEQE_CONS_IDX_CAEP_AEQE_CONS_IDX_M,
		       ROCEE_CAEP_AEQE_CONS_IDX_CAEP_AEQE_CONS_IDX_S, 0);
	eqconsindx_val = le32_to_cpu(पंचांगp2);
	ग_लिखोl(eqconsindx_val, eqc + 0xc);

	वापस 0;

err_out_मुक्त_pages:
	क्रम (i -= 1; i >= 0; i--)
		dma_मुक्त_coherent(dev, HNS_ROCE_BA_SIZE, eq->buf_list[i].buf,
				  eq->buf_list[i].map);

	kमुक्त(eq->buf_list);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v1_init_eq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_eq_table *eq_table = &hr_dev->eq_table;
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा hns_roce_eq *eq;
	पूर्णांक irq_num;
	पूर्णांक eq_num;
	पूर्णांक ret;
	पूर्णांक i, j;

	eq_num = hr_dev->caps.num_comp_vectors + hr_dev->caps.num_aeq_vectors;
	irq_num = eq_num + hr_dev->caps.num_other_vectors;

	eq_table->eq = kसुस्मृति(eq_num, माप(*eq_table->eq), GFP_KERNEL);
	अगर (!eq_table->eq)
		वापस -ENOMEM;

	eq_table->eqc_base = kसुस्मृति(eq_num, माप(*eq_table->eqc_base),
				     GFP_KERNEL);
	अगर (!eq_table->eqc_base) अणु
		ret = -ENOMEM;
		जाओ err_eqc_base_alloc_fail;
	पूर्ण

	क्रम (i = 0; i < eq_num; i++) अणु
		eq = &eq_table->eq[i];
		eq->hr_dev = hr_dev;
		eq->eqn = i;
		eq->irq = hr_dev->irq[i];
		eq->log_page_size = PAGE_SHIFT;

		अगर (i < hr_dev->caps.num_comp_vectors) अणु
			/* CEQ */
			eq_table->eqc_base[i] = hr_dev->reg_base +
						ROCEE_CAEP_CEQC_SHIFT_0_REG +
						CEQ_REG_OFFSET * i;
			eq->type_flag = HNS_ROCE_CEQ;
			eq->db_reg = hr_dev->reg_base +
				     ROCEE_CAEP_CEQC_CONS_IDX_0_REG +
				     CEQ_REG_OFFSET * i;
			eq->entries = hr_dev->caps.ceqe_depth;
			eq->log_entries = ilog2(eq->entries);
			eq->eqe_size = HNS_ROCE_CEQE_SIZE;
		पूर्ण अन्यथा अणु
			/* AEQ */
			eq_table->eqc_base[i] = hr_dev->reg_base +
						ROCEE_CAEP_AEQC_AEQE_SHIFT_REG;
			eq->type_flag = HNS_ROCE_AEQ;
			eq->db_reg = hr_dev->reg_base +
				     ROCEE_CAEP_AEQE_CONS_IDX_REG;
			eq->entries = hr_dev->caps.aeqe_depth;
			eq->log_entries = ilog2(eq->entries);
			eq->eqe_size = HNS_ROCE_AEQE_SIZE;
		पूर्ण
	पूर्ण

	/* Disable irq */
	hns_roce_v1_पूर्णांक_mask_enable(hr_dev);

	/* Configure ce पूर्णांक पूर्णांकerval */
	roce_ग_लिखो(hr_dev, ROCEE_CAEP_CE_INTERVAL_CFG_REG,
		   HNS_ROCE_CEQ_DEFAULT_INTERVAL);

	/* Configure ce पूर्णांक burst num */
	roce_ग_लिखो(hr_dev, ROCEE_CAEP_CE_BURST_NUM_CFG_REG,
		   HNS_ROCE_CEQ_DEFAULT_BURST_NUM);

	क्रम (i = 0; i < eq_num; i++) अणु
		ret = hns_roce_v1_create_eq(hr_dev, &eq_table->eq[i]);
		अगर (ret) अणु
			dev_err(dev, "eq create failed\n");
			जाओ err_create_eq_fail;
		पूर्ण
	पूर्ण

	क्रम (j = 0; j < irq_num; j++) अणु
		अगर (j < eq_num)
			ret = request_irq(hr_dev->irq[j],
					  hns_roce_v1_msix_पूर्णांकerrupt_eq, 0,
					  hr_dev->irq_names[j],
					  &eq_table->eq[j]);
		अन्यथा
			ret = request_irq(hr_dev->irq[j],
					  hns_roce_v1_msix_पूर्णांकerrupt_abn, 0,
					  hr_dev->irq_names[j], hr_dev);

		अगर (ret) अणु
			dev_err(dev, "request irq error!\n");
			जाओ err_request_irq_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < eq_num; i++)
		hns_roce_v1_enable_eq(hr_dev, i, EQ_ENABLE);

	वापस 0;

err_request_irq_fail:
	क्रम (j -= 1; j >= 0; j--)
		मुक्त_irq(hr_dev->irq[j], &eq_table->eq[j]);

err_create_eq_fail:
	क्रम (i -= 1; i >= 0; i--)
		hns_roce_v1_मुक्त_eq(hr_dev, &eq_table->eq[i]);

	kमुक्त(eq_table->eqc_base);

err_eqc_base_alloc_fail:
	kमुक्त(eq_table->eq);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_v1_cleanup_eq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_eq_table *eq_table = &hr_dev->eq_table;
	पूर्णांक irq_num;
	पूर्णांक eq_num;
	पूर्णांक i;

	eq_num = hr_dev->caps.num_comp_vectors + hr_dev->caps.num_aeq_vectors;
	irq_num = eq_num + hr_dev->caps.num_other_vectors;
	क्रम (i = 0; i < eq_num; i++) अणु
		/* Disable EQ */
		hns_roce_v1_enable_eq(hr_dev, i, EQ_DISABLE);

		मुक्त_irq(hr_dev->irq[i], &eq_table->eq[i]);

		hns_roce_v1_मुक्त_eq(hr_dev, &eq_table->eq[i]);
	पूर्ण
	क्रम (i = eq_num; i < irq_num; i++)
		मुक्त_irq(hr_dev->irq[i], hr_dev);

	kमुक्त(eq_table->eqc_base);
	kमुक्त(eq_table->eq);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops hns_roce_v1_dev_ops = अणु
	.destroy_qp = hns_roce_v1_destroy_qp,
	.poll_cq = hns_roce_v1_poll_cq,
	.post_recv = hns_roce_v1_post_recv,
	.post_send = hns_roce_v1_post_send,
	.query_qp = hns_roce_v1_query_qp,
	.req_notअगरy_cq = hns_roce_v1_req_notअगरy_cq,
पूर्ण;

अटल स्थिर काष्ठा hns_roce_hw hns_roce_hw_v1 = अणु
	.reset = hns_roce_v1_reset,
	.hw_profile = hns_roce_v1_profile,
	.hw_init = hns_roce_v1_init,
	.hw_निकास = hns_roce_v1_निकास,
	.post_mbox = hns_roce_v1_post_mbox,
	.poll_mbox_करोne = hns_roce_v1_chk_mbox,
	.set_gid = hns_roce_v1_set_gid,
	.set_mac = hns_roce_v1_set_mac,
	.set_mtu = hns_roce_v1_set_mtu,
	.ग_लिखो_mtpt = hns_roce_v1_ग_लिखो_mtpt,
	.ग_लिखो_cqc = hns_roce_v1_ग_लिखो_cqc,
	.clear_hem = hns_roce_v1_clear_hem,
	.modअगरy_qp = hns_roce_v1_modअगरy_qp,
	.dereg_mr = hns_roce_v1_dereg_mr,
	.destroy_cq = hns_roce_v1_destroy_cq,
	.init_eq = hns_roce_v1_init_eq_table,
	.cleanup_eq = hns_roce_v1_cleanup_eq_table,
	.hns_roce_dev_ops = &hns_roce_v1_dev_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hns_roce_of_match[] = अणु
	अणु .compatible = "hisilicon,hns-roce-v1", .data = &hns_roce_hw_v1, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hns_roce_of_match);

अटल स्थिर काष्ठा acpi_device_id hns_roce_acpi_match[] = अणु
	अणु "HISI00D1", (kernel_uदीर्घ_t)&hns_roce_hw_v1 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hns_roce_acpi_match);

अटल काष्ठा
platक्रमm_device *hns_roce_find_pdev(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev;

	/* get the 'device' corresponding to the matching 'fwnode' */
	dev = bus_find_device_by_fwnode(&platक्रमm_bus_type, fwnode);
	/* get the platक्रमm device */
	वापस dev ? to_platक्रमm_device(dev) : शून्य;
पूर्ण

अटल पूर्णांक hns_roce_get_cfg(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा device *dev = &hr_dev->pdev->dev;
	काष्ठा platक्रमm_device *pdev = शून्य;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा device_node *net_node;
	पूर्णांक port_cnt = 0;
	u8 phy_port;
	पूर्णांक ret;
	पूर्णांक i;

	/* check अगर we are compatible with the underlying SoC */
	अगर (dev_of_node(dev)) अणु
		स्थिर काष्ठा of_device_id *of_id;

		of_id = of_match_node(hns_roce_of_match, dev->of_node);
		अगर (!of_id) अणु
			dev_err(dev, "device is not compatible!\n");
			वापस -ENXIO;
		पूर्ण
		hr_dev->hw = (स्थिर काष्ठा hns_roce_hw *)of_id->data;
		अगर (!hr_dev->hw) अणु
			dev_err(dev, "couldn't get H/W specific DT data!\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अगर (is_acpi_device_node(dev->fwnode)) अणु
		स्थिर काष्ठा acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(hns_roce_acpi_match, dev);
		अगर (!acpi_id) अणु
			dev_err(dev, "device is not compatible!\n");
			वापस -ENXIO;
		पूर्ण
		hr_dev->hw = (स्थिर काष्ठा hns_roce_hw *) acpi_id->driver_data;
		अगर (!hr_dev->hw) अणु
			dev_err(dev, "couldn't get H/W specific ACPI data!\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "can't read compatibility data from DT or ACPI\n");
		वापस -ENXIO;
	पूर्ण

	/* get the mapped रेजिस्टर base address */
	hr_dev->reg_base = devm_platक्रमm_ioremap_resource(hr_dev->pdev, 0);
	अगर (IS_ERR(hr_dev->reg_base))
		वापस PTR_ERR(hr_dev->reg_base);

	/* पढ़ो the node_guid of IB device from the DT or ACPI */
	ret = device_property_पढ़ो_u8_array(dev, "node-guid",
					    (u8 *)&hr_dev->ib_dev.node_guid,
					    GUID_LEN);
	अगर (ret) अणु
		dev_err(dev, "couldn't get node_guid from DT or ACPI!\n");
		वापस ret;
	पूर्ण

	/* get the RoCE associated ethernet ports or netdevices */
	क्रम (i = 0; i < HNS_ROCE_MAX_PORTS; i++) अणु
		अगर (dev_of_node(dev)) अणु
			net_node = of_parse_phandle(dev->of_node, "eth-handle",
						    i);
			अगर (!net_node)
				जारी;
			pdev = of_find_device_by_node(net_node);
		पूर्ण अन्यथा अगर (is_acpi_device_node(dev->fwnode)) अणु
			काष्ठा fwnode_reference_args args;

			ret = acpi_node_get_property_reference(dev->fwnode,
							       "eth-handle",
							       i, &args);
			अगर (ret)
				जारी;
			pdev = hns_roce_find_pdev(args.fwnode);
		पूर्ण अन्यथा अणु
			dev_err(dev, "cannot read data from DT or ACPI\n");
			वापस -ENXIO;
		पूर्ण

		अगर (pdev) अणु
			netdev = platक्रमm_get_drvdata(pdev);
			phy_port = (u8)i;
			अगर (netdev) अणु
				hr_dev->iboe.netdevs[port_cnt] = netdev;
				hr_dev->iboe.phy_port[port_cnt] = phy_port;
			पूर्ण अन्यथा अणु
				dev_err(dev, "no netdev found with pdev %s\n",
					pdev->name);
				वापस -ENODEV;
			पूर्ण
			port_cnt++;
		पूर्ण
	पूर्ण

	अगर (port_cnt == 0) अणु
		dev_err(dev, "unable to get eth-handle for available ports!\n");
		वापस -EINVAL;
	पूर्ण

	hr_dev->caps.num_ports = port_cnt;

	/* cmd issue mode: 0 is poll, 1 is event */
	hr_dev->cmd_mod = 1;
	hr_dev->loop_idc = 0;
	hr_dev->sdb_offset = ROCEE_DB_SQ_L_0_REG;
	hr_dev->odb_offset = ROCEE_DB_OTHERS_L_0_REG;

	/* पढ़ो the पूर्णांकerrupt names from the DT or ACPI */
	ret = device_property_पढ़ो_string_array(dev, "interrupt-names",
						hr_dev->irq_names,
						HNS_ROCE_V1_MAX_IRQ_NUM);
	अगर (ret < 0) अणु
		dev_err(dev, "couldn't get interrupt names from DT or ACPI!\n");
		वापस ret;
	पूर्ण

	/* fetch the पूर्णांकerrupt numbers */
	क्रम (i = 0; i < HNS_ROCE_V1_MAX_IRQ_NUM; i++) अणु
		hr_dev->irq[i] = platक्रमm_get_irq(hr_dev->pdev, i);
		अगर (hr_dev->irq[i] <= 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_roce_probe - RoCE driver entrance
 * @pdev: poपूर्णांकer to platक्रमm device
 * Return : पूर्णांक
 *
 */
अटल पूर्णांक hns_roce_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा hns_roce_dev *hr_dev;
	काष्ठा device *dev = &pdev->dev;

	hr_dev = ib_alloc_device(hns_roce_dev, ib_dev);
	अगर (!hr_dev)
		वापस -ENOMEM;

	hr_dev->priv = kzalloc(माप(काष्ठा hns_roce_v1_priv), GFP_KERNEL);
	अगर (!hr_dev->priv) अणु
		ret = -ENOMEM;
		जाओ error_failed_kzalloc;
	पूर्ण

	hr_dev->pdev = pdev;
	hr_dev->dev = dev;
	platक्रमm_set_drvdata(pdev, hr_dev);

	अगर (dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64ULL)) &&
	    dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32ULL))) अणु
		dev_err(dev, "Not usable DMA addressing mode\n");
		ret = -EIO;
		जाओ error_failed_get_cfg;
	पूर्ण

	ret = hns_roce_get_cfg(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "Get Configuration failed!\n");
		जाओ error_failed_get_cfg;
	पूर्ण

	ret = hns_roce_init(hr_dev);
	अगर (ret) अणु
		dev_err(dev, "RoCE engine init failed!\n");
		जाओ error_failed_get_cfg;
	पूर्ण

	वापस 0;

error_failed_get_cfg:
	kमुक्त(hr_dev->priv);

error_failed_kzalloc:
	ib_dealloc_device(&hr_dev->ib_dev);

	वापस ret;
पूर्ण

/**
 * hns_roce_हटाओ - हटाओ RoCE device
 * @pdev: poपूर्णांकer to platक्रमm device
 */
अटल पूर्णांक hns_roce_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hns_roce_dev *hr_dev = platक्रमm_get_drvdata(pdev);

	hns_roce_निकास(hr_dev);
	kमुक्त(hr_dev->priv);
	ib_dealloc_device(&hr_dev->ib_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hns_roce_driver = अणु
	.probe = hns_roce_probe,
	.हटाओ = hns_roce_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = hns_roce_of_match,
		.acpi_match_table = ACPI_PTR(hns_roce_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hns_roce_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wei Hu <xavier.huwei@huawei.com>");
MODULE_AUTHOR("Nenglong Zhao <zhaonenglong@hisilicon.com>");
MODULE_AUTHOR("Lijun Ou <oulijun@huawei.com>");
MODULE_DESCRIPTION("Hisilicon Hip06 Family RoCE Driver");
