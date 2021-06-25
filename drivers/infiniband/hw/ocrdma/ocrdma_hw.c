<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/log2.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/अगर_ether.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_cache.h>

#समावेश "ocrdma.h"
#समावेश "ocrdma_hw.h"
#समावेश "ocrdma_verbs.h"
#समावेश "ocrdma_ah.h"

क्रमागत mbx_status अणु
	OCRDMA_MBX_STATUS_FAILED		= 1,
	OCRDMA_MBX_STATUS_ILLEGAL_FIELD		= 3,
	OCRDMA_MBX_STATUS_OOR			= 100,
	OCRDMA_MBX_STATUS_INVALID_PD		= 101,
	OCRDMA_MBX_STATUS_PD_INUSE		= 102,
	OCRDMA_MBX_STATUS_INVALID_CQ		= 103,
	OCRDMA_MBX_STATUS_INVALID_QP		= 104,
	OCRDMA_MBX_STATUS_INVALID_LKEY		= 105,
	OCRDMA_MBX_STATUS_ORD_EXCEEDS		= 106,
	OCRDMA_MBX_STATUS_IRD_EXCEEDS		= 107,
	OCRDMA_MBX_STATUS_SENDQ_WQE_EXCEEDS	= 108,
	OCRDMA_MBX_STATUS_RECVQ_RQE_EXCEEDS	= 109,
	OCRDMA_MBX_STATUS_SGE_SEND_EXCEEDS	= 110,
	OCRDMA_MBX_STATUS_SGE_WRITE_EXCEEDS	= 111,
	OCRDMA_MBX_STATUS_SGE_RECV_EXCEEDS	= 112,
	OCRDMA_MBX_STATUS_INVALID_STATE_CHANGE	= 113,
	OCRDMA_MBX_STATUS_MW_BOUND		= 114,
	OCRDMA_MBX_STATUS_INVALID_VA		= 115,
	OCRDMA_MBX_STATUS_INVALID_LENGTH	= 116,
	OCRDMA_MBX_STATUS_INVALID_FBO		= 117,
	OCRDMA_MBX_STATUS_INVALID_ACC_RIGHTS	= 118,
	OCRDMA_MBX_STATUS_INVALID_PBE_SIZE	= 119,
	OCRDMA_MBX_STATUS_INVALID_PBL_ENTRY	= 120,
	OCRDMA_MBX_STATUS_INVALID_PBL_SHIFT	= 121,
	OCRDMA_MBX_STATUS_INVALID_SRQ_ID	= 129,
	OCRDMA_MBX_STATUS_SRQ_ERROR		= 133,
	OCRDMA_MBX_STATUS_RQE_EXCEEDS		= 134,
	OCRDMA_MBX_STATUS_MTU_EXCEEDS		= 135,
	OCRDMA_MBX_STATUS_MAX_QP_EXCEEDS	= 136,
	OCRDMA_MBX_STATUS_SRQ_LIMIT_EXCEEDS	= 137,
	OCRDMA_MBX_STATUS_SRQ_SIZE_UNDERUNS	= 138,
	OCRDMA_MBX_STATUS_QP_BOUND		= 130,
	OCRDMA_MBX_STATUS_INVALID_CHANGE	= 139,
	OCRDMA_MBX_STATUS_ATOMIC_OPS_UNSUP	= 140,
	OCRDMA_MBX_STATUS_INVALID_RNR_NAK_TIMER	= 141,
	OCRDMA_MBX_STATUS_MW_STILL_BOUND	= 142,
	OCRDMA_MBX_STATUS_PKEY_INDEX_INVALID	= 143,
	OCRDMA_MBX_STATUS_PKEY_INDEX_EXCEEDS	= 144
पूर्ण;

क्रमागत additional_status अणु
	OCRDMA_MBX_ADDI_STATUS_INSUFFICIENT_RESOURCES = 22
पूर्ण;

क्रमागत cqe_status अणु
	OCRDMA_MBX_CQE_STATUS_INSUFFICIENT_PRIVILEDGES	= 1,
	OCRDMA_MBX_CQE_STATUS_INVALID_PARAMETER		= 2,
	OCRDMA_MBX_CQE_STATUS_INSUFFICIENT_RESOURCES	= 3,
	OCRDMA_MBX_CQE_STATUS_QUEUE_FLUSHING		= 4,
	OCRDMA_MBX_CQE_STATUS_DMA_FAILED		= 5
पूर्ण;

अटल अंतरभूत व्योम *ocrdma_get_eqe(काष्ठा ocrdma_eq *eq)
अणु
	वापस eq->q.va + (eq->q.tail * माप(काष्ठा ocrdma_eqe));
पूर्ण

अटल अंतरभूत व्योम ocrdma_eq_inc_tail(काष्ठा ocrdma_eq *eq)
अणु
	eq->q.tail = (eq->q.tail + 1) & (OCRDMA_EQ_LEN - 1);
पूर्ण

अटल अंतरभूत व्योम *ocrdma_get_mcqe(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_mcqe *cqe = (काष्ठा ocrdma_mcqe *)
	    (dev->mq.cq.va + (dev->mq.cq.tail * माप(काष्ठा ocrdma_mcqe)));

	अगर (!(le32_to_cpu(cqe->valid_ae_cmpl_cons) & OCRDMA_MCQE_VALID_MASK))
		वापस शून्य;
	वापस cqe;
पूर्ण

अटल अंतरभूत व्योम ocrdma_mcq_inc_tail(काष्ठा ocrdma_dev *dev)
अणु
	dev->mq.cq.tail = (dev->mq.cq.tail + 1) & (OCRDMA_MQ_CQ_LEN - 1);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_mqe *ocrdma_get_mqe(काष्ठा ocrdma_dev *dev)
अणु
	वापस dev->mq.sq.va + (dev->mq.sq.head * माप(काष्ठा ocrdma_mqe));
पूर्ण

अटल अंतरभूत व्योम ocrdma_mq_inc_head(काष्ठा ocrdma_dev *dev)
अणु
	dev->mq.sq.head = (dev->mq.sq.head + 1) & (OCRDMA_MQ_LEN - 1);
पूर्ण

अटल अंतरभूत व्योम *ocrdma_get_mqe_rsp(काष्ठा ocrdma_dev *dev)
अणु
	वापस dev->mq.sq.va + (dev->mqe_ctx.tag * माप(काष्ठा ocrdma_mqe));
पूर्ण

क्रमागत ib_qp_state get_ibqp_state(क्रमागत ocrdma_qp_state qps)
अणु
	चयन (qps) अणु
	हाल OCRDMA_QPS_RST:
		वापस IB_QPS_RESET;
	हाल OCRDMA_QPS_INIT:
		वापस IB_QPS_INIT;
	हाल OCRDMA_QPS_RTR:
		वापस IB_QPS_RTR;
	हाल OCRDMA_QPS_RTS:
		वापस IB_QPS_RTS;
	हाल OCRDMA_QPS_SQD:
	हाल OCRDMA_QPS_SQ_DRAINING:
		वापस IB_QPS_SQD;
	हाल OCRDMA_QPS_SQE:
		वापस IB_QPS_SQE;
	हाल OCRDMA_QPS_ERR:
		वापस IB_QPS_ERR;
	पूर्ण
	वापस IB_QPS_ERR;
पूर्ण

अटल क्रमागत ocrdma_qp_state get_ocrdma_qp_state(क्रमागत ib_qp_state qps)
अणु
	चयन (qps) अणु
	हाल IB_QPS_RESET:
		वापस OCRDMA_QPS_RST;
	हाल IB_QPS_INIT:
		वापस OCRDMA_QPS_INIT;
	हाल IB_QPS_RTR:
		वापस OCRDMA_QPS_RTR;
	हाल IB_QPS_RTS:
		वापस OCRDMA_QPS_RTS;
	हाल IB_QPS_SQD:
		वापस OCRDMA_QPS_SQD;
	हाल IB_QPS_SQE:
		वापस OCRDMA_QPS_SQE;
	हाल IB_QPS_ERR:
		वापस OCRDMA_QPS_ERR;
	पूर्ण
	वापस OCRDMA_QPS_ERR;
पूर्ण

अटल पूर्णांक ocrdma_get_mbx_त्रुटि_सं(u32 status)
अणु
	पूर्णांक err_num;
	u8 mbox_status = (status & OCRDMA_MBX_RSP_STATUS_MASK) >>
					OCRDMA_MBX_RSP_STATUS_SHIFT;
	u8 add_status = (status & OCRDMA_MBX_RSP_ASTATUS_MASK) >>
					OCRDMA_MBX_RSP_ASTATUS_SHIFT;

	चयन (mbox_status) अणु
	हाल OCRDMA_MBX_STATUS_OOR:
	हाल OCRDMA_MBX_STATUS_MAX_QP_EXCEEDS:
		err_num = -EAGAIN;
		अवरोध;

	हाल OCRDMA_MBX_STATUS_INVALID_PD:
	हाल OCRDMA_MBX_STATUS_INVALID_CQ:
	हाल OCRDMA_MBX_STATUS_INVALID_SRQ_ID:
	हाल OCRDMA_MBX_STATUS_INVALID_QP:
	हाल OCRDMA_MBX_STATUS_INVALID_CHANGE:
	हाल OCRDMA_MBX_STATUS_MTU_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_INVALID_RNR_NAK_TIMER:
	हाल OCRDMA_MBX_STATUS_PKEY_INDEX_INVALID:
	हाल OCRDMA_MBX_STATUS_PKEY_INDEX_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_ILLEGAL_FIELD:
	हाल OCRDMA_MBX_STATUS_INVALID_PBL_ENTRY:
	हाल OCRDMA_MBX_STATUS_INVALID_LKEY:
	हाल OCRDMA_MBX_STATUS_INVALID_VA:
	हाल OCRDMA_MBX_STATUS_INVALID_LENGTH:
	हाल OCRDMA_MBX_STATUS_INVALID_FBO:
	हाल OCRDMA_MBX_STATUS_INVALID_ACC_RIGHTS:
	हाल OCRDMA_MBX_STATUS_INVALID_PBE_SIZE:
	हाल OCRDMA_MBX_STATUS_ATOMIC_OPS_UNSUP:
	हाल OCRDMA_MBX_STATUS_SRQ_ERROR:
	हाल OCRDMA_MBX_STATUS_SRQ_SIZE_UNDERUNS:
		err_num = -EINVAL;
		अवरोध;

	हाल OCRDMA_MBX_STATUS_PD_INUSE:
	हाल OCRDMA_MBX_STATUS_QP_BOUND:
	हाल OCRDMA_MBX_STATUS_MW_STILL_BOUND:
	हाल OCRDMA_MBX_STATUS_MW_BOUND:
		err_num = -EBUSY;
		अवरोध;

	हाल OCRDMA_MBX_STATUS_RECVQ_RQE_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_SGE_RECV_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_RQE_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_SRQ_LIMIT_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_ORD_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_IRD_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_SENDQ_WQE_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_SGE_SEND_EXCEEDS:
	हाल OCRDMA_MBX_STATUS_SGE_WRITE_EXCEEDS:
		err_num = -ENOBUFS;
		अवरोध;

	हाल OCRDMA_MBX_STATUS_FAILED:
		चयन (add_status) अणु
		हाल OCRDMA_MBX_ADDI_STATUS_INSUFFICIENT_RESOURCES:
			err_num = -EAGAIN;
			अवरोध;
		शेष:
			err_num = -EFAULT;
		पूर्ण
		अवरोध;
	शेष:
		err_num = -EFAULT;
	पूर्ण
	वापस err_num;
पूर्ण

अक्षर *port_speed_string(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *str = "";
	u16 speeds_supported;

	speeds_supported = dev->phy.fixed_speeds_supported |
				dev->phy.स्वतः_speeds_supported;
	अगर (speeds_supported & OCRDMA_PHY_SPEED_40GBPS)
		str = "40Gbps ";
	अन्यथा अगर (speeds_supported & OCRDMA_PHY_SPEED_10GBPS)
		str = "10Gbps ";
	अन्यथा अगर (speeds_supported & OCRDMA_PHY_SPEED_1GBPS)
		str = "1Gbps ";

	वापस str;
पूर्ण

अटल पूर्णांक ocrdma_get_mbx_cqe_त्रुटि_सं(u16 cqe_status)
अणु
	पूर्णांक err_num = -EINVAL;

	चयन (cqe_status) अणु
	हाल OCRDMA_MBX_CQE_STATUS_INSUFFICIENT_PRIVILEDGES:
		err_num = -EPERM;
		अवरोध;
	हाल OCRDMA_MBX_CQE_STATUS_INVALID_PARAMETER:
		err_num = -EINVAL;
		अवरोध;
	हाल OCRDMA_MBX_CQE_STATUS_INSUFFICIENT_RESOURCES:
	हाल OCRDMA_MBX_CQE_STATUS_QUEUE_FLUSHING:
		err_num = -EINVAL;
		अवरोध;
	हाल OCRDMA_MBX_CQE_STATUS_DMA_FAILED:
	शेष:
		err_num = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err_num;
पूर्ण

व्योम ocrdma_ring_cq_db(काष्ठा ocrdma_dev *dev, u16 cq_id, bool armed,
		       bool solicited, u16 cqe_popped)
अणु
	u32 val = cq_id & OCRDMA_DB_CQ_RING_ID_MASK;

	val |= ((cq_id & OCRDMA_DB_CQ_RING_ID_EXT_MASK) <<
	     OCRDMA_DB_CQ_RING_ID_EXT_MASK_SHIFT);

	अगर (armed)
		val |= (1 << OCRDMA_DB_CQ_REARM_SHIFT);
	अगर (solicited)
		val |= (1 << OCRDMA_DB_CQ_SOLICIT_SHIFT);
	val |= (cqe_popped << OCRDMA_DB_CQ_NUM_POPPED_SHIFT);
	ioग_लिखो32(val, dev->nic_info.db + OCRDMA_DB_CQ_OFFSET);
पूर्ण

अटल व्योम ocrdma_ring_mq_db(काष्ठा ocrdma_dev *dev)
अणु
	u32 val = 0;

	val |= dev->mq.sq.id & OCRDMA_MQ_ID_MASK;
	val |= 1 << OCRDMA_MQ_NUM_MQE_SHIFT;
	ioग_लिखो32(val, dev->nic_info.db + OCRDMA_DB_MQ_OFFSET);
पूर्ण

अटल व्योम ocrdma_ring_eq_db(काष्ठा ocrdma_dev *dev, u16 eq_id,
			      bool arm, bool clear_पूर्णांक, u16 num_eqe)
अणु
	u32 val = 0;

	val |= eq_id & OCRDMA_EQ_ID_MASK;
	val |= ((eq_id & OCRDMA_EQ_ID_EXT_MASK) << OCRDMA_EQ_ID_EXT_MASK_SHIFT);
	अगर (arm)
		val |= (1 << OCRDMA_REARM_SHIFT);
	अगर (clear_पूर्णांक)
		val |= (1 << OCRDMA_EQ_CLR_SHIFT);
	val |= (1 << OCRDMA_EQ_TYPE_SHIFT);
	val |= (num_eqe << OCRDMA_NUM_EQE_SHIFT);
	ioग_लिखो32(val, dev->nic_info.db + OCRDMA_DB_EQ_OFFSET);
पूर्ण

अटल व्योम ocrdma_init_mch(काष्ठा ocrdma_mbx_hdr *cmd_hdr,
			    u8 opcode, u8 subsys, u32 cmd_len)
अणु
	cmd_hdr->subsys_op = (opcode | (subsys << OCRDMA_MCH_SUBSYS_SHIFT));
	cmd_hdr->समयout = 20; /* seconds */
	cmd_hdr->cmd_len = cmd_len - माप(काष्ठा ocrdma_mbx_hdr);
पूर्ण

अटल व्योम *ocrdma_init_emb_mqe(u8 opcode, u32 cmd_len)
अणु
	काष्ठा ocrdma_mqe *mqe;

	mqe = kzalloc(माप(काष्ठा ocrdma_mqe), GFP_KERNEL);
	अगर (!mqe)
		वापस शून्य;
	mqe->hdr.spcl_sge_cnt_emb |=
		(OCRDMA_MQE_EMBEDDED << OCRDMA_MQE_HDR_EMB_SHIFT) &
					OCRDMA_MQE_HDR_EMB_MASK;
	mqe->hdr.pyld_len = cmd_len - माप(काष्ठा ocrdma_mqe_hdr);

	ocrdma_init_mch(&mqe->u.emb_req.mch, opcode, OCRDMA_SUBSYS_ROCE,
			mqe->hdr.pyld_len);
	वापस mqe;
पूर्ण

अटल व्योम ocrdma_मुक्त_q(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_queue_info *q)
अणु
	dma_मुक्त_coherent(&dev->nic_info.pdev->dev, q->size, q->va, q->dma);
पूर्ण

अटल पूर्णांक ocrdma_alloc_q(काष्ठा ocrdma_dev *dev,
			  काष्ठा ocrdma_queue_info *q, u16 len, u16 entry_size)
अणु
	स_रखो(q, 0, माप(*q));
	q->len = len;
	q->entry_size = entry_size;
	q->size = len * entry_size;
	q->va = dma_alloc_coherent(&dev->nic_info.pdev->dev, q->size, &q->dma,
				   GFP_KERNEL);
	अगर (!q->va)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम ocrdma_build_q_pages(काष्ठा ocrdma_pa *q_pa, पूर्णांक cnt,
					dma_addr_t host_pa, पूर्णांक hw_page_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cnt; i++) अणु
		q_pa[i].lo = (u32) (host_pa & 0xffffffff);
		q_pa[i].hi = (u32) upper_32_bits(host_pa);
		host_pa += hw_page_size;
	पूर्ण
पूर्ण

अटल पूर्णांक ocrdma_mbx_delete_q(काष्ठा ocrdma_dev *dev,
			       काष्ठा ocrdma_queue_info *q, पूर्णांक queue_type)
अणु
	u8 opcode = 0;
	पूर्णांक status;
	काष्ठा ocrdma_delete_q_req *cmd = dev->mbx_cmd;

	चयन (queue_type) अणु
	हाल QTYPE_MCCQ:
		opcode = OCRDMA_CMD_DELETE_MQ;
		अवरोध;
	हाल QTYPE_CQ:
		opcode = OCRDMA_CMD_DELETE_CQ;
		अवरोध;
	हाल QTYPE_EQ:
		opcode = OCRDMA_CMD_DELETE_EQ;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	स_रखो(cmd, 0, माप(*cmd));
	ocrdma_init_mch(&cmd->req, opcode, OCRDMA_SUBSYS_COMMON, माप(*cmd));
	cmd->id = q->id;

	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, माप(*cmd), शून्य, शून्य);
	अगर (!status)
		q->created = false;
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_create_eq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_create_eq_req *cmd = dev->mbx_cmd;
	काष्ठा ocrdma_create_eq_rsp *rsp = dev->mbx_cmd;

	स_रखो(cmd, 0, माप(*cmd));
	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_CREATE_EQ, OCRDMA_SUBSYS_COMMON,
			माप(*cmd));

	cmd->req.rsvd_version = 2;
	cmd->num_pages = 4;
	cmd->valid = OCRDMA_CREATE_EQ_VALID;
	cmd->cnt = 4 << OCRDMA_CREATE_EQ_CNT_SHIFT;

	ocrdma_build_q_pages(&cmd->pa[0], cmd->num_pages, eq->q.dma,
			     PAGE_SIZE_4K);
	status = be_roce_mcc_cmd(dev->nic_info.netdev, cmd, माप(*cmd), शून्य,
				 शून्य);
	अगर (!status) अणु
		eq->q.id = rsp->vector_eqid & 0xffff;
		eq->vector = (rsp->vector_eqid >> 16) & 0xffff;
		eq->q.created = true;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_create_eq(काष्ठा ocrdma_dev *dev,
			    काष्ठा ocrdma_eq *eq, u16 q_len)
अणु
	पूर्णांक status;

	status = ocrdma_alloc_q(dev, &eq->q, OCRDMA_EQ_LEN,
				माप(काष्ठा ocrdma_eqe));
	अगर (status)
		वापस status;

	status = ocrdma_mbx_create_eq(dev, eq);
	अगर (status)
		जाओ mbx_err;
	eq->dev = dev;
	ocrdma_ring_eq_db(dev, eq->q.id, true, true, 0);

	वापस 0;
mbx_err:
	ocrdma_मुक्त_q(dev, &eq->q);
	वापस status;
पूर्ण

पूर्णांक ocrdma_get_irq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq)
अणु
	पूर्णांक irq;

	अगर (dev->nic_info.पूर्णांकr_mode == BE_INTERRUPT_MODE_INTX)
		irq = dev->nic_info.pdev->irq;
	अन्यथा
		irq = dev->nic_info.msix.vector_list[eq->vector];
	वापस irq;
पूर्ण

अटल व्योम _ocrdma_destroy_eq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq)
अणु
	अगर (eq->q.created) अणु
		ocrdma_mbx_delete_q(dev, &eq->q, QTYPE_EQ);
		ocrdma_मुक्त_q(dev, &eq->q);
	पूर्ण
पूर्ण

अटल व्योम ocrdma_destroy_eq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq)
अणु
	पूर्णांक irq;

	/* disarm EQ so that पूर्णांकerrupts are not generated
	 * during मुक्तing and EQ delete is in progress.
	 */
	ocrdma_ring_eq_db(dev, eq->q.id, false, false, 0);

	irq = ocrdma_get_irq(dev, eq);
	मुक्त_irq(irq, eq);
	_ocrdma_destroy_eq(dev, eq);
पूर्ण

अटल व्योम ocrdma_destroy_eqs(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->eq_cnt; i++)
		ocrdma_destroy_eq(dev, &dev->eq_tbl[i]);
पूर्ण

अटल पूर्णांक ocrdma_mbx_mq_cq_create(काष्ठा ocrdma_dev *dev,
				   काष्ठा ocrdma_queue_info *cq,
				   काष्ठा ocrdma_queue_info *eq)
अणु
	काष्ठा ocrdma_create_cq_cmd *cmd = dev->mbx_cmd;
	काष्ठा ocrdma_create_cq_cmd_rsp *rsp = dev->mbx_cmd;
	पूर्णांक status;

	स_रखो(cmd, 0, माप(*cmd));
	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_CREATE_CQ,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));

	cmd->req.rsvd_version = OCRDMA_CREATE_CQ_VER2;
	cmd->pgsz_pgcnt = (cq->size / OCRDMA_MIN_Q_PAGE_SIZE) <<
		OCRDMA_CREATE_CQ_PAGE_SIZE_SHIFT;
	cmd->pgsz_pgcnt |= PAGES_4K_SPANNED(cq->va, cq->size);

	cmd->ev_cnt_flags = OCRDMA_CREATE_CQ_DEF_FLAGS;
	cmd->eqn = eq->id;
	cmd->pdid_cqecnt = cq->size / माप(काष्ठा ocrdma_mcqe);

	ocrdma_build_q_pages(&cmd->pa[0], cq->size / OCRDMA_MIN_Q_PAGE_SIZE,
			     cq->dma, PAGE_SIZE_4K);
	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, माप(*cmd), शून्य, शून्य);
	अगर (!status) अणु
		cq->id = (u16) (rsp->cq_id & OCRDMA_CREATE_CQ_RSP_CQ_ID_MASK);
		cq->created = true;
	पूर्ण
	वापस status;
पूर्ण

अटल u32 ocrdma_encoded_q_len(पूर्णांक q_len)
अणु
	u32 len_encoded = fls(q_len);	/* log2(len) + 1 */

	अगर (len_encoded == 16)
		len_encoded = 0;
	वापस len_encoded;
पूर्ण

अटल पूर्णांक ocrdma_mbx_create_mq(काष्ठा ocrdma_dev *dev,
				काष्ठा ocrdma_queue_info *mq,
				काष्ठा ocrdma_queue_info *cq)
अणु
	पूर्णांक num_pages, status;
	काष्ठा ocrdma_create_mq_req *cmd = dev->mbx_cmd;
	काष्ठा ocrdma_create_mq_rsp *rsp = dev->mbx_cmd;
	काष्ठा ocrdma_pa *pa;

	स_रखो(cmd, 0, माप(*cmd));
	num_pages = PAGES_4K_SPANNED(mq->va, mq->size);

	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_CREATE_MQ_EXT,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));
	cmd->req.rsvd_version = 1;
	cmd->cqid_pages = num_pages;
	cmd->cqid_pages |= (cq->id << OCRDMA_CREATE_MQ_CQ_ID_SHIFT);
	cmd->async_cqid_valid = OCRDMA_CREATE_MQ_ASYNC_CQ_VALID;

	cmd->async_event_biपंचांगap = BIT(OCRDMA_ASYNC_GRP5_EVE_CODE);
	cmd->async_event_biपंचांगap |= BIT(OCRDMA_ASYNC_RDMA_EVE_CODE);
	/* Request link events on this  MQ. */
	cmd->async_event_biपंचांगap |= BIT(OCRDMA_ASYNC_LINK_EVE_CODE);

	cmd->async_cqid_ringsize = cq->id;
	cmd->async_cqid_ringsize |= (ocrdma_encoded_q_len(mq->len) <<
				OCRDMA_CREATE_MQ_RING_SIZE_SHIFT);
	cmd->valid = OCRDMA_CREATE_MQ_VALID;
	pa = &cmd->pa[0];

	ocrdma_build_q_pages(pa, num_pages, mq->dma, PAGE_SIZE_4K);
	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, माप(*cmd), शून्य, शून्य);
	अगर (!status) अणु
		mq->id = rsp->id;
		mq->created = true;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_create_mq(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status;

	/* Alloc completion queue क्रम Mailbox queue */
	status = ocrdma_alloc_q(dev, &dev->mq.cq, OCRDMA_MQ_CQ_LEN,
				माप(काष्ठा ocrdma_mcqe));
	अगर (status)
		जाओ alloc_err;

	dev->eq_tbl[0].cq_cnt++;
	status = ocrdma_mbx_mq_cq_create(dev, &dev->mq.cq, &dev->eq_tbl[0].q);
	अगर (status)
		जाओ mbx_cq_मुक्त;

	स_रखो(&dev->mqe_ctx, 0, माप(dev->mqe_ctx));
	init_रुकोqueue_head(&dev->mqe_ctx.cmd_रुको);
	mutex_init(&dev->mqe_ctx.lock);

	/* Alloc Mailbox queue */
	status = ocrdma_alloc_q(dev, &dev->mq.sq, OCRDMA_MQ_LEN,
				माप(काष्ठा ocrdma_mqe));
	अगर (status)
		जाओ mbx_cq_destroy;
	status = ocrdma_mbx_create_mq(dev, &dev->mq.sq, &dev->mq.cq);
	अगर (status)
		जाओ mbx_q_मुक्त;
	ocrdma_ring_cq_db(dev, dev->mq.cq.id, true, false, 0);
	वापस 0;

mbx_q_मुक्त:
	ocrdma_मुक्त_q(dev, &dev->mq.sq);
mbx_cq_destroy:
	ocrdma_mbx_delete_q(dev, &dev->mq.cq, QTYPE_CQ);
mbx_cq_मुक्त:
	ocrdma_मुक्त_q(dev, &dev->mq.cq);
alloc_err:
	वापस status;
पूर्ण

अटल व्योम ocrdma_destroy_mq(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_queue_info *mbxq, *cq;

	/* mqe_ctx lock synchronizes with any other pending cmds. */
	mutex_lock(&dev->mqe_ctx.lock);
	mbxq = &dev->mq.sq;
	अगर (mbxq->created) अणु
		ocrdma_mbx_delete_q(dev, mbxq, QTYPE_MCCQ);
		ocrdma_मुक्त_q(dev, mbxq);
	पूर्ण
	mutex_unlock(&dev->mqe_ctx.lock);

	cq = &dev->mq.cq;
	अगर (cq->created) अणु
		ocrdma_mbx_delete_q(dev, cq, QTYPE_CQ);
		ocrdma_मुक्त_q(dev, cq);
	पूर्ण
पूर्ण

अटल व्योम ocrdma_process_qpcat_error(काष्ठा ocrdma_dev *dev,
				       काष्ठा ocrdma_qp *qp)
अणु
	क्रमागत ib_qp_state new_ib_qps = IB_QPS_ERR;
	क्रमागत ib_qp_state old_ib_qps;

	अगर (qp == शून्य)
		BUG();
	ocrdma_qp_state_change(qp, new_ib_qps, &old_ib_qps);
पूर्ण

अटल व्योम ocrdma_dispatch_ibevent(काष्ठा ocrdma_dev *dev,
				    काष्ठा ocrdma_ae_mcqe *cqe)
अणु
	काष्ठा ocrdma_qp *qp = शून्य;
	काष्ठा ocrdma_cq *cq = शून्य;
	काष्ठा ib_event ib_evt;
	पूर्णांक cq_event = 0;
	पूर्णांक qp_event = 1;
	पूर्णांक srq_event = 0;
	पूर्णांक dev_event = 0;
	पूर्णांक type = (cqe->valid_ae_event & OCRDMA_AE_MCQE_EVENT_TYPE_MASK) >>
	    OCRDMA_AE_MCQE_EVENT_TYPE_SHIFT;
	u16 qpid = cqe->qpvalid_qpid & OCRDMA_AE_MCQE_QPID_MASK;
	u16 cqid = cqe->cqvalid_cqid & OCRDMA_AE_MCQE_CQID_MASK;

	/*
	 * Some FW version वापसs wrong qp or cq ids in CQEs.
	 * Checking whether the IDs are valid
	 */

	अगर (cqe->qpvalid_qpid & OCRDMA_AE_MCQE_QPVALID) अणु
		अगर (qpid < dev->attr.max_qp)
			qp = dev->qp_tbl[qpid];
		अगर (qp == शून्य) अणु
			pr_err("ocrdma%d:Async event - qpid %u is not valid\n",
			       dev->id, qpid);
			वापस;
		पूर्ण
	पूर्ण

	अगर (cqe->cqvalid_cqid & OCRDMA_AE_MCQE_CQVALID) अणु
		अगर (cqid < dev->attr.max_cq)
			cq = dev->cq_tbl[cqid];
		अगर (cq == शून्य) अणु
			pr_err("ocrdma%d:Async event - cqid %u is not valid\n",
			       dev->id, cqid);
			वापस;
		पूर्ण
	पूर्ण

	स_रखो(&ib_evt, 0, माप(ib_evt));

	ib_evt.device = &dev->ibdev;

	चयन (type) अणु
	हाल OCRDMA_CQ_ERROR:
		ib_evt.element.cq = &cq->ibcq;
		ib_evt.event = IB_EVENT_CQ_ERR;
		cq_event = 1;
		qp_event = 0;
		अवरोध;
	हाल OCRDMA_CQ_OVERRUN_ERROR:
		ib_evt.element.cq = &cq->ibcq;
		ib_evt.event = IB_EVENT_CQ_ERR;
		cq_event = 1;
		qp_event = 0;
		अवरोध;
	हाल OCRDMA_CQ_QPCAT_ERROR:
		ib_evt.element.qp = &qp->ibqp;
		ib_evt.event = IB_EVENT_QP_FATAL;
		ocrdma_process_qpcat_error(dev, qp);
		अवरोध;
	हाल OCRDMA_QP_ACCESS_ERROR:
		ib_evt.element.qp = &qp->ibqp;
		ib_evt.event = IB_EVENT_QP_ACCESS_ERR;
		अवरोध;
	हाल OCRDMA_QP_COMM_EST_EVENT:
		ib_evt.element.qp = &qp->ibqp;
		ib_evt.event = IB_EVENT_COMM_EST;
		अवरोध;
	हाल OCRDMA_SQ_DRAINED_EVENT:
		ib_evt.element.qp = &qp->ibqp;
		ib_evt.event = IB_EVENT_SQ_DRAINED;
		अवरोध;
	हाल OCRDMA_DEVICE_FATAL_EVENT:
		ib_evt.element.port_num = 1;
		ib_evt.event = IB_EVENT_DEVICE_FATAL;
		qp_event = 0;
		dev_event = 1;
		अवरोध;
	हाल OCRDMA_SRQCAT_ERROR:
		ib_evt.element.srq = &qp->srq->ibsrq;
		ib_evt.event = IB_EVENT_SRQ_ERR;
		srq_event = 1;
		qp_event = 0;
		अवरोध;
	हाल OCRDMA_SRQ_LIMIT_EVENT:
		ib_evt.element.srq = &qp->srq->ibsrq;
		ib_evt.event = IB_EVENT_SRQ_LIMIT_REACHED;
		srq_event = 1;
		qp_event = 0;
		अवरोध;
	हाल OCRDMA_QP_LAST_WQE_EVENT:
		ib_evt.element.qp = &qp->ibqp;
		ib_evt.event = IB_EVENT_QP_LAST_WQE_REACHED;
		अवरोध;
	शेष:
		cq_event = 0;
		qp_event = 0;
		srq_event = 0;
		dev_event = 0;
		pr_err("%s() unknown type=0x%x\n", __func__, type);
		अवरोध;
	पूर्ण

	अगर (type < OCRDMA_MAX_ASYNC_ERRORS)
		atomic_inc(&dev->async_err_stats[type]);

	अगर (qp_event) अणु
		अगर (qp->ibqp.event_handler)
			qp->ibqp.event_handler(&ib_evt, qp->ibqp.qp_context);
	पूर्ण अन्यथा अगर (cq_event) अणु
		अगर (cq->ibcq.event_handler)
			cq->ibcq.event_handler(&ib_evt, cq->ibcq.cq_context);
	पूर्ण अन्यथा अगर (srq_event) अणु
		अगर (qp->srq->ibsrq.event_handler)
			qp->srq->ibsrq.event_handler(&ib_evt,
						     qp->srq->ibsrq.
						     srq_context);
	पूर्ण अन्यथा अगर (dev_event) अणु
		dev_err(&dev->ibdev.dev, "Fatal event received\n");
		ib_dispatch_event(&ib_evt);
	पूर्ण

पूर्ण

अटल व्योम ocrdma_process_grp5_aync(काष्ठा ocrdma_dev *dev,
					काष्ठा ocrdma_ae_mcqe *cqe)
अणु
	काष्ठा ocrdma_ae_pvid_mcqe *evt;
	पूर्णांक type = (cqe->valid_ae_event & OCRDMA_AE_MCQE_EVENT_TYPE_MASK) >>
			OCRDMA_AE_MCQE_EVENT_TYPE_SHIFT;

	चयन (type) अणु
	हाल OCRDMA_ASYNC_EVENT_PVID_STATE:
		evt = (काष्ठा ocrdma_ae_pvid_mcqe *)cqe;
		अगर ((evt->tag_enabled & OCRDMA_AE_PVID_MCQE_ENABLED_MASK) >>
			OCRDMA_AE_PVID_MCQE_ENABLED_SHIFT)
			dev->pvid = ((evt->tag_enabled &
					OCRDMA_AE_PVID_MCQE_TAG_MASK) >>
					OCRDMA_AE_PVID_MCQE_TAG_SHIFT);
		अवरोध;

	हाल OCRDMA_ASYNC_EVENT_COS_VALUE:
		atomic_set(&dev->update_sl, 1);
		अवरोध;
	शेष:
		/* Not पूर्णांकerested evts. */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ocrdma_process_link_state(काष्ठा ocrdma_dev *dev,
				      काष्ठा ocrdma_ae_mcqe *cqe)
अणु
	काष्ठा ocrdma_ae_lnkst_mcqe *evt;
	u8 lstate;

	evt = (काष्ठा ocrdma_ae_lnkst_mcqe *)cqe;
	lstate = ocrdma_get_ae_link_state(evt->speed_state_ptn);

	अगर (!(lstate & OCRDMA_AE_LSC_LLINK_MASK))
		वापस;

	अगर (dev->flags & OCRDMA_FLAGS_LINK_STATUS_INIT)
		ocrdma_update_link_state(dev, (lstate & OCRDMA_LINK_ST_MASK));
पूर्ण

अटल व्योम ocrdma_process_acqe(काष्ठा ocrdma_dev *dev, व्योम *ae_cqe)
अणु
	/* async CQE processing */
	काष्ठा ocrdma_ae_mcqe *cqe = ae_cqe;
	u32 evt_code = (cqe->valid_ae_event & OCRDMA_AE_MCQE_EVENT_CODE_MASK) >>
			OCRDMA_AE_MCQE_EVENT_CODE_SHIFT;
	चयन (evt_code) अणु
	हाल OCRDMA_ASYNC_LINK_EVE_CODE:
		ocrdma_process_link_state(dev, cqe);
		अवरोध;
	हाल OCRDMA_ASYNC_RDMA_EVE_CODE:
		ocrdma_dispatch_ibevent(dev, cqe);
		अवरोध;
	हाल OCRDMA_ASYNC_GRP5_EVE_CODE:
		ocrdma_process_grp5_aync(dev, cqe);
		अवरोध;
	शेष:
		pr_err("%s(%d) invalid evt code=0x%x\n", __func__,
		       dev->id, evt_code);
	पूर्ण
पूर्ण

अटल व्योम ocrdma_process_mcqe(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mcqe *cqe)
अणु
	अगर (dev->mqe_ctx.tag == cqe->tag_lo && dev->mqe_ctx.cmd_करोne == false) अणु
		dev->mqe_ctx.cqe_status = (cqe->status &
		     OCRDMA_MCQE_STATUS_MASK) >> OCRDMA_MCQE_STATUS_SHIFT;
		dev->mqe_ctx.ext_status =
		    (cqe->status & OCRDMA_MCQE_ESTATUS_MASK)
		    >> OCRDMA_MCQE_ESTATUS_SHIFT;
		dev->mqe_ctx.cmd_करोne = true;
		wake_up(&dev->mqe_ctx.cmd_रुको);
	पूर्ण अन्यथा
		pr_err("%s() cqe for invalid tag0x%x.expected=0x%x\n",
		       __func__, cqe->tag_lo, dev->mqe_ctx.tag);
पूर्ण

अटल पूर्णांक ocrdma_mq_cq_handler(काष्ठा ocrdma_dev *dev, u16 cq_id)
अणु
	u16 cqe_popped = 0;
	काष्ठा ocrdma_mcqe *cqe;

	जबतक (1) अणु
		cqe = ocrdma_get_mcqe(dev);
		अगर (cqe == शून्य)
			अवरोध;
		ocrdma_le32_to_cpu(cqe, माप(*cqe));
		cqe_popped += 1;
		अगर (cqe->valid_ae_cmpl_cons & OCRDMA_MCQE_AE_MASK)
			ocrdma_process_acqe(dev, cqe);
		अन्यथा अगर (cqe->valid_ae_cmpl_cons & OCRDMA_MCQE_CMPL_MASK)
			ocrdma_process_mcqe(dev, cqe);
		स_रखो(cqe, 0, माप(काष्ठा ocrdma_mcqe));
		ocrdma_mcq_inc_tail(dev);
	पूर्ण
	ocrdma_ring_cq_db(dev, dev->mq.cq.id, true, false, cqe_popped);
	वापस 0;
पूर्ण

अटल काष्ठा ocrdma_cq *_ocrdma_qp_buddy_cq_handler(काष्ठा ocrdma_dev *dev,
				काष्ठा ocrdma_cq *cq, bool sq)
अणु
	काष्ठा ocrdma_qp *qp;
	काष्ठा list_head *cur;
	काष्ठा ocrdma_cq *bcq = शून्य;
	काष्ठा list_head *head = sq?(&cq->sq_head):(&cq->rq_head);

	list_क्रम_each(cur, head) अणु
		अगर (sq)
			qp = list_entry(cur, काष्ठा ocrdma_qp, sq_entry);
		अन्यथा
			qp = list_entry(cur, काष्ठा ocrdma_qp, rq_entry);

		अगर (qp->srq)
			जारी;
		/* अगर wq and rq share the same cq, than comp_handler
		 * is alपढ़ोy invoked.
		 */
		अगर (qp->sq_cq == qp->rq_cq)
			जारी;
		/* अगर completion came on sq, rq's cq is buddy cq.
		 * अगर completion came on rq, sq's cq is buddy cq.
		 */
		अगर (qp->sq_cq == cq)
			bcq = qp->rq_cq;
		अन्यथा
			bcq = qp->sq_cq;
		वापस bcq;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम ocrdma_qp_buddy_cq_handler(काष्ठा ocrdma_dev *dev,
				       काष्ठा ocrdma_cq *cq)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_cq *bcq = शून्य;

	/* Go through list of QPs in error state which are using this CQ
	 * and invoke its callback handler to trigger CQE processing क्रम
	 * error/flushed CQE. It is rare to find more than few entries in
	 * this list as most consumers stops after getting error CQE.
	 * List is traversed only once when a matching buddy cq found क्रम a QP.
	 */
	spin_lock_irqsave(&dev->flush_q_lock, flags);
	/* Check अगर buddy CQ is present.
	 * true - Check क्रम  SQ CQ
	 * false - Check क्रम RQ CQ
	 */
	bcq = _ocrdma_qp_buddy_cq_handler(dev, cq, true);
	अगर (bcq == शून्य)
		bcq = _ocrdma_qp_buddy_cq_handler(dev, cq, false);
	spin_unlock_irqrestore(&dev->flush_q_lock, flags);

	/* अगर there is valid buddy cq, look क्रम its completion handler */
	अगर (bcq && bcq->ibcq.comp_handler) अणु
		spin_lock_irqsave(&bcq->comp_handler_lock, flags);
		(*bcq->ibcq.comp_handler) (&bcq->ibcq, bcq->ibcq.cq_context);
		spin_unlock_irqrestore(&bcq->comp_handler_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम ocrdma_qp_cq_handler(काष्ठा ocrdma_dev *dev, u16 cq_idx)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_cq *cq;

	अगर (cq_idx >= OCRDMA_MAX_CQ)
		BUG();

	cq = dev->cq_tbl[cq_idx];
	अगर (cq == शून्य)
		वापस;

	अगर (cq->ibcq.comp_handler) अणु
		spin_lock_irqsave(&cq->comp_handler_lock, flags);
		(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);
		spin_unlock_irqrestore(&cq->comp_handler_lock, flags);
	पूर्ण
	ocrdma_qp_buddy_cq_handler(dev, cq);
पूर्ण

अटल व्योम ocrdma_cq_handler(काष्ठा ocrdma_dev *dev, u16 cq_id)
अणु
	/* process the MQ-CQE. */
	अगर (cq_id == dev->mq.cq.id)
		ocrdma_mq_cq_handler(dev, cq_id);
	अन्यथा
		ocrdma_qp_cq_handler(dev, cq_id);
पूर्ण

अटल irqवापस_t ocrdma_irq_handler(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा ocrdma_eq *eq = handle;
	काष्ठा ocrdma_dev *dev = eq->dev;
	काष्ठा ocrdma_eqe eqe;
	काष्ठा ocrdma_eqe *ptr;
	u16 cq_id;
	u8 mcode;
	पूर्णांक budget = eq->cq_cnt;

	करो अणु
		ptr = ocrdma_get_eqe(eq);
		eqe = *ptr;
		ocrdma_le32_to_cpu(&eqe, माप(eqe));
		mcode = (eqe.id_valid & OCRDMA_EQE_MAJOR_CODE_MASK)
				>> OCRDMA_EQE_MAJOR_CODE_SHIFT;
		अगर (mcode == OCRDMA_MAJOR_CODE_SENTINAL)
			pr_err("EQ full on eqid = 0x%x, eqe = 0x%x\n",
			       eq->q.id, eqe.id_valid);
		अगर ((eqe.id_valid & OCRDMA_EQE_VALID_MASK) == 0)
			अवरोध;

		ptr->id_valid = 0;
		/* ring eq करोorbell as soon as its consumed. */
		ocrdma_ring_eq_db(dev, eq->q.id, false, true, 1);
		/* check whether its CQE or not. */
		अगर ((eqe.id_valid & OCRDMA_EQE_FOR_CQE_MASK) == 0) अणु
			cq_id = eqe.id_valid >> OCRDMA_EQE_RESOURCE_ID_SHIFT;
			ocrdma_cq_handler(dev, cq_id);
		पूर्ण
		ocrdma_eq_inc_tail(eq);

		/* There can be a stale EQE after the last bound CQ is
		 * destroyed. EQE valid and budget == 0 implies this.
		 */
		अगर (budget)
			budget--;

	पूर्ण जबतक (budget);

	eq->aic_obj.eq_पूर्णांकr_cnt++;
	ocrdma_ring_eq_db(dev, eq->q.id, true, true, 0);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ocrdma_post_mqe(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mqe *cmd)
अणु
	काष्ठा ocrdma_mqe *mqe;

	dev->mqe_ctx.tag = dev->mq.sq.head;
	dev->mqe_ctx.cmd_करोne = false;
	mqe = ocrdma_get_mqe(dev);
	cmd->hdr.tag_lo = dev->mq.sq.head;
	ocrdma_copy_cpu_to_le32(mqe, cmd, माप(*mqe));
	/* make sure descriptor is written beक्रमe ringing करोorbell */
	wmb();
	ocrdma_mq_inc_head(dev);
	ocrdma_ring_mq_db(dev);
पूर्ण

अटल पूर्णांक ocrdma_रुको_mqe_cmpl(काष्ठा ocrdma_dev *dev)
अणु
	दीर्घ status;
	/* 30 sec समयout */
	status = रुको_event_समयout(dev->mqe_ctx.cmd_रुको,
				    (dev->mqe_ctx.cmd_करोne != false),
				    msecs_to_jअगरfies(30000));
	अगर (status)
		वापस 0;
	अन्यथा अणु
		dev->mqe_ctx.fw_error_state = true;
		pr_err("%s(%d) mailbox timeout: fw not responding\n",
		       __func__, dev->id);
		वापस -1;
	पूर्ण
पूर्ण

/* issue a mailbox command on the MQ */
अटल पूर्णांक ocrdma_mbx_cmd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mqe *mqe)
अणु
	पूर्णांक status = 0;
	u16 cqe_status, ext_status;
	काष्ठा ocrdma_mqe *rsp_mqe;
	काष्ठा ocrdma_mbx_rsp *rsp = शून्य;

	mutex_lock(&dev->mqe_ctx.lock);
	अगर (dev->mqe_ctx.fw_error_state)
		जाओ mbx_err;
	ocrdma_post_mqe(dev, mqe);
	status = ocrdma_रुको_mqe_cmpl(dev);
	अगर (status)
		जाओ mbx_err;
	cqe_status = dev->mqe_ctx.cqe_status;
	ext_status = dev->mqe_ctx.ext_status;
	rsp_mqe = ocrdma_get_mqe_rsp(dev);
	ocrdma_copy_le32_to_cpu(mqe, rsp_mqe, (माप(*mqe)));
	अगर ((mqe->hdr.spcl_sge_cnt_emb & OCRDMA_MQE_HDR_EMB_MASK) >>
				OCRDMA_MQE_HDR_EMB_SHIFT)
		rsp = &mqe->u.rsp;

	अगर (cqe_status || ext_status) अणु
		pr_err("%s() cqe_status=0x%x, ext_status=0x%x,\n",
		       __func__, cqe_status, ext_status);
		अगर (rsp) अणु
			/* This is क्रम embedded cmds. */
			pr_err("opcode=0x%x, subsystem=0x%x\n",
			       (rsp->subsys_op & OCRDMA_MBX_RSP_OPCODE_MASK) >>
				OCRDMA_MBX_RSP_OPCODE_SHIFT,
				(rsp->subsys_op & OCRDMA_MBX_RSP_SUBSYS_MASK) >>
				OCRDMA_MBX_RSP_SUBSYS_SHIFT);
		पूर्ण
		status = ocrdma_get_mbx_cqe_त्रुटि_सं(cqe_status);
		जाओ mbx_err;
	पूर्ण
	/* For non embedded, rsp errors are handled in ocrdma_nonemb_mbx_cmd */
	अगर (rsp && (mqe->u.rsp.status & OCRDMA_MBX_RSP_STATUS_MASK))
		status = ocrdma_get_mbx_त्रुटि_सं(mqe->u.rsp.status);
mbx_err:
	mutex_unlock(&dev->mqe_ctx.lock);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_nonemb_mbx_cmd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_mqe *mqe,
				 व्योम *payload_va)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_mbx_rsp *rsp = payload_va;

	अगर ((mqe->hdr.spcl_sge_cnt_emb & OCRDMA_MQE_HDR_EMB_MASK) >>
				OCRDMA_MQE_HDR_EMB_SHIFT)
		BUG();

	status = ocrdma_mbx_cmd(dev, mqe);
	अगर (!status)
		/* For non embedded, only CQE failures are handled in
		 * ocrdma_mbx_cmd. We need to check क्रम RSP errors.
		 */
		अगर (rsp->status & OCRDMA_MBX_RSP_STATUS_MASK)
			status = ocrdma_get_mbx_त्रुटि_सं(rsp->status);

	अगर (status)
		pr_err("opcode=0x%x, subsystem=0x%x\n",
		       (rsp->subsys_op & OCRDMA_MBX_RSP_OPCODE_MASK) >>
			OCRDMA_MBX_RSP_OPCODE_SHIFT,
			(rsp->subsys_op & OCRDMA_MBX_RSP_SUBSYS_MASK) >>
			OCRDMA_MBX_RSP_SUBSYS_SHIFT);
	वापस status;
पूर्ण

अटल व्योम ocrdma_get_attr(काष्ठा ocrdma_dev *dev,
			      काष्ठा ocrdma_dev_attr *attr,
			      काष्ठा ocrdma_mbx_query_config *rsp)
अणु
	attr->max_pd =
	    (rsp->max_pd_ca_ack_delay & OCRDMA_MBX_QUERY_CFG_MAX_PD_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_PD_SHIFT;
	attr->udp_encap = (rsp->max_pd_ca_ack_delay &
			   OCRDMA_MBX_QUERY_CFG_L3_TYPE_MASK) >>
			   OCRDMA_MBX_QUERY_CFG_L3_TYPE_SHIFT;
	attr->max_dpp_pds =
	   (rsp->max_dpp_pds_credits & OCRDMA_MBX_QUERY_CFG_MAX_DPP_PDS_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_DPP_PDS_OFFSET;
	attr->max_qp =
	    (rsp->qp_srq_cq_ird_ord & OCRDMA_MBX_QUERY_CFG_MAX_QP_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_QP_SHIFT;
	attr->max_srq =
		(rsp->max_srq_rpir_qps & OCRDMA_MBX_QUERY_CFG_MAX_SRQ_MASK) >>
		OCRDMA_MBX_QUERY_CFG_MAX_SRQ_OFFSET;
	attr->max_send_sge = ((rsp->max_recv_send_sge &
			       OCRDMA_MBX_QUERY_CFG_MAX_SEND_SGE_MASK) >>
			      OCRDMA_MBX_QUERY_CFG_MAX_SEND_SGE_SHIFT);
	attr->max_recv_sge = (rsp->max_recv_send_sge &
			      OCRDMA_MBX_QUERY_CFG_MAX_RECV_SGE_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_RECV_SGE_SHIFT;
	attr->max_srq_sge = (rsp->max_srq_rqe_sge &
			      OCRDMA_MBX_QUERY_CFG_MAX_SRQ_SGE_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_SRQ_SGE_OFFSET;
	attr->max_rdma_sge = (rsp->max_wr_rd_sge &
			      OCRDMA_MBX_QUERY_CFG_MAX_RD_SGE_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_RD_SGE_SHIFT;
	attr->max_ord_per_qp = (rsp->max_ird_ord_per_qp &
				OCRDMA_MBX_QUERY_CFG_MAX_ORD_PER_QP_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_ORD_PER_QP_SHIFT;
	attr->max_ird_per_qp = (rsp->max_ird_ord_per_qp &
				OCRDMA_MBX_QUERY_CFG_MAX_IRD_PER_QP_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_MAX_IRD_PER_QP_SHIFT;
	attr->cq_overflow_detect = (rsp->qp_srq_cq_ird_ord &
				    OCRDMA_MBX_QUERY_CFG_CQ_OVERFLOW_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_CQ_OVERFLOW_SHIFT;
	attr->srq_supported = (rsp->qp_srq_cq_ird_ord &
			       OCRDMA_MBX_QUERY_CFG_SRQ_SUPPORTED_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_SRQ_SUPPORTED_SHIFT;
	attr->local_ca_ack_delay = (rsp->max_pd_ca_ack_delay &
				    OCRDMA_MBX_QUERY_CFG_CA_ACK_DELAY_MASK) >>
	    OCRDMA_MBX_QUERY_CFG_CA_ACK_DELAY_SHIFT;
	attr->max_mw = rsp->max_mw;
	attr->max_mr = rsp->max_mr;
	attr->max_mr_size = ((u64)rsp->max_mr_size_hi << 32) |
			      rsp->max_mr_size_lo;
	attr->max_pages_per_frmr = rsp->max_pages_per_frmr;
	attr->max_num_mr_pbl = rsp->max_num_mr_pbl;
	attr->max_cqe = rsp->max_cq_cqes_per_cq &
			OCRDMA_MBX_QUERY_CFG_MAX_CQES_PER_CQ_MASK;
	attr->max_cq = (rsp->max_cq_cqes_per_cq &
			OCRDMA_MBX_QUERY_CFG_MAX_CQ_MASK) >>
			OCRDMA_MBX_QUERY_CFG_MAX_CQ_OFFSET;
	attr->wqe_size = ((rsp->wqe_rqe_stride_max_dpp_cqs &
		OCRDMA_MBX_QUERY_CFG_MAX_WQE_SIZE_MASK) >>
		OCRDMA_MBX_QUERY_CFG_MAX_WQE_SIZE_OFFSET) *
		OCRDMA_WQE_STRIDE;
	attr->rqe_size = ((rsp->wqe_rqe_stride_max_dpp_cqs &
		OCRDMA_MBX_QUERY_CFG_MAX_RQE_SIZE_MASK) >>
		OCRDMA_MBX_QUERY_CFG_MAX_RQE_SIZE_OFFSET) *
		OCRDMA_WQE_STRIDE;
	attr->max_अंतरभूत_data =
	    attr->wqe_size - (माप(काष्ठा ocrdma_hdr_wqe) +
			      माप(काष्ठा ocrdma_sge));
	अगर (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R) अणु
		attr->ird = 1;
		attr->ird_page_size = OCRDMA_MIN_Q_PAGE_SIZE;
		attr->num_ird_pages = MAX_OCRDMA_IRD_PAGES;
	पूर्ण
	dev->attr.max_wqe = rsp->max_wqes_rqes_per_q >>
		 OCRDMA_MBX_QUERY_CFG_MAX_WQES_PER_WQ_OFFSET;
	dev->attr.max_rqe = rsp->max_wqes_rqes_per_q &
		OCRDMA_MBX_QUERY_CFG_MAX_RQES_PER_RQ_MASK;
पूर्ण

अटल पूर्णांक ocrdma_check_fw_config(काष्ठा ocrdma_dev *dev,
				   काष्ठा ocrdma_fw_conf_rsp *conf)
अणु
	u32 fn_mode;

	fn_mode = conf->fn_mode & OCRDMA_FN_MODE_RDMA;
	अगर (fn_mode != OCRDMA_FN_MODE_RDMA)
		वापस -EINVAL;
	dev->base_eqid = conf->base_eqid;
	dev->max_eq = conf->max_eq;
	वापस 0;
पूर्ण

/* can be issued only during init समय. */
अटल पूर्णांक ocrdma_mbx_query_fw_ver(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_mqe *cmd;
	काष्ठा ocrdma_fw_ver_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_GET_FW_VER, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_GET_FW_VER,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_fw_ver_rsp *)cmd;
	स_रखो(&dev->attr.fw_ver[0], 0, माप(dev->attr.fw_ver));
	स_नकल(&dev->attr.fw_ver[0], &rsp->running_ver[0],
	       माप(rsp->running_ver));
	ocrdma_le32_to_cpu(dev->attr.fw_ver, माप(rsp->running_ver));
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

/* can be issued only during init समय. */
अटल पूर्णांक ocrdma_mbx_query_fw_config(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_mqe *cmd;
	काष्ठा ocrdma_fw_conf_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_GET_FW_CONFIG, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_GET_FW_CONFIG,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_fw_conf_rsp *)cmd;
	status = ocrdma_check_fw_config(dev, rsp);
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_rdma_stats(काष्ठा ocrdma_dev *dev, bool reset)
अणु
	काष्ठा ocrdma_rdma_stats_req *req = dev->stats_mem.va;
	काष्ठा ocrdma_mqe *mqe = &dev->stats_mem.mqe;
	काष्ठा ocrdma_rdma_stats_resp *old_stats;
	पूर्णांक status;

	old_stats = kदो_स्मृति(माप(*old_stats), GFP_KERNEL);
	अगर (old_stats == शून्य)
		वापस -ENOMEM;

	स_रखो(mqe, 0, माप(*mqe));
	mqe->hdr.pyld_len = dev->stats_mem.size;
	mqe->hdr.spcl_sge_cnt_emb |=
			(1 << OCRDMA_MQE_HDR_SGE_CNT_SHIFT) &
				OCRDMA_MQE_HDR_SGE_CNT_MASK;
	mqe->u.nonemb_req.sge[0].pa_lo = (u32) (dev->stats_mem.pa & 0xffffffff);
	mqe->u.nonemb_req.sge[0].pa_hi = (u32) upper_32_bits(dev->stats_mem.pa);
	mqe->u.nonemb_req.sge[0].len = dev->stats_mem.size;

	/* Cache the old stats */
	स_नकल(old_stats, req, माप(काष्ठा ocrdma_rdma_stats_resp));
	स_रखो(req, 0, dev->stats_mem.size);

	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)req,
			OCRDMA_CMD_GET_RDMA_STATS,
			OCRDMA_SUBSYS_ROCE,
			dev->stats_mem.size);
	अगर (reset)
		req->reset_stats = reset;

	status = ocrdma_nonemb_mbx_cmd(dev, mqe, dev->stats_mem.va);
	अगर (status)
		/* Copy from cache, अगर mbox fails */
		स_नकल(req, old_stats, माप(काष्ठा ocrdma_rdma_stats_resp));
	अन्यथा
		ocrdma_le32_to_cpu(req, dev->stats_mem.size);

	kमुक्त(old_stats);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_get_ctrl_attribs(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_dma_mem dma;
	काष्ठा ocrdma_mqe *mqe;
	काष्ठा ocrdma_get_ctrl_attribs_rsp *ctrl_attr_rsp;
	काष्ठा mgmt_hba_attribs *hba_attribs;

	mqe = kzalloc(माप(काष्ठा ocrdma_mqe), GFP_KERNEL);
	अगर (!mqe)
		वापस status;

	dma.size = माप(काष्ठा ocrdma_get_ctrl_attribs_rsp);
	dma.va	 = dma_alloc_coherent(&dev->nic_info.pdev->dev,
					dma.size, &dma.pa, GFP_KERNEL);
	अगर (!dma.va)
		जाओ मुक्त_mqe;

	mqe->hdr.pyld_len = dma.size;
	mqe->hdr.spcl_sge_cnt_emb |=
			(1 << OCRDMA_MQE_HDR_SGE_CNT_SHIFT) &
			OCRDMA_MQE_HDR_SGE_CNT_MASK;
	mqe->u.nonemb_req.sge[0].pa_lo = (u32) (dma.pa & 0xffffffff);
	mqe->u.nonemb_req.sge[0].pa_hi = (u32) upper_32_bits(dma.pa);
	mqe->u.nonemb_req.sge[0].len = dma.size;

	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)dma.va,
			OCRDMA_CMD_GET_CTRL_ATTRIBUTES,
			OCRDMA_SUBSYS_COMMON,
			dma.size);

	status = ocrdma_nonemb_mbx_cmd(dev, mqe, dma.va);
	अगर (!status) अणु
		ctrl_attr_rsp = (काष्ठा ocrdma_get_ctrl_attribs_rsp *)dma.va;
		hba_attribs = &ctrl_attr_rsp->ctrl_attribs.hba_attribs;

		dev->hba_port_num = (hba_attribs->ptpnum_maxकरोms_hbast_cv &
					OCRDMA_HBA_ATTRB_PTNUM_MASK)
					>> OCRDMA_HBA_ATTRB_PTNUM_SHIFT;
		strlcpy(dev->model_number,
			hba_attribs->controller_model_number,
			माप(dev->model_number));
	पूर्ण
	dma_मुक्त_coherent(&dev->nic_info.pdev->dev, dma.size, dma.va, dma.pa);
मुक्त_mqe:
	kमुक्त(mqe);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_query_dev(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_mbx_query_config *rsp;
	काष्ठा ocrdma_mqe *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_CONFIG, माप(*cmd));
	अगर (!cmd)
		वापस status;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_mbx_query_config *)cmd;
	ocrdma_get_attr(dev, &dev->attr, rsp);
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_get_link_speed(काष्ठा ocrdma_dev *dev, u8 *lnk_speed,
			      u8 *lnk_state)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_get_link_speed_rsp *rsp;
	काष्ठा ocrdma_mqe *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_NTWK_LINK_CONFIG_V1,
				  माप(*cmd));
	अगर (!cmd)
		वापस status;
	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_QUERY_NTWK_LINK_CONFIG_V1,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));

	((काष्ठा ocrdma_mbx_hdr *)cmd->u.cmd)->rsvd_version = 0x1;

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;

	rsp = (काष्ठा ocrdma_get_link_speed_rsp *)cmd;
	अगर (lnk_speed)
		*lnk_speed = (rsp->pflt_pps_ld_pnum & OCRDMA_PHY_PS_MASK)
			      >> OCRDMA_PHY_PS_SHIFT;
	अगर (lnk_state)
		*lnk_state = (rsp->res_lnk_st & OCRDMA_LINK_ST_MASK);

mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_get_phy_info(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_mqe *cmd;
	काष्ठा ocrdma_get_phy_info_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_PHY_DETAILS, माप(*cmd));
	अगर (!cmd)
		वापस status;

	ocrdma_init_mch((काष्ठा ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_PHY_DETAILS, OCRDMA_SUBSYS_COMMON,
			माप(*cmd));

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;

	rsp = (काष्ठा ocrdma_get_phy_info_rsp *)cmd;
	dev->phy.phy_type =
			(rsp->ityp_ptyp & OCRDMA_PHY_TYPE_MASK);
	dev->phy.पूर्णांकerface_type =
			(rsp->ityp_ptyp & OCRDMA_IF_TYPE_MASK)
				>> OCRDMA_IF_TYPE_SHIFT;
	dev->phy.स्वतः_speeds_supported  =
			(rsp->fspeed_aspeed & OCRDMA_ASPEED_SUPP_MASK);
	dev->phy.fixed_speeds_supported =
			(rsp->fspeed_aspeed & OCRDMA_FSPEED_SUPP_MASK)
				>> OCRDMA_FSPEED_SUPP_SHIFT;
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_alloc_pd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_pd *pd)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_alloc_pd *cmd;
	काष्ठा ocrdma_alloc_pd_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_PD, माप(*cmd));
	अगर (!cmd)
		वापस status;
	अगर (pd->dpp_enabled)
		cmd->enable_dpp_rsvd |= OCRDMA_ALLOC_PD_ENABLE_DPP;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_alloc_pd_rsp *)cmd;
	pd->id = rsp->dpp_page_pdid & OCRDMA_ALLOC_PD_RSP_PDID_MASK;
	अगर (rsp->dpp_page_pdid & OCRDMA_ALLOC_PD_RSP_DPP) अणु
		pd->dpp_enabled = true;
		pd->dpp_page = rsp->dpp_page_pdid >>
				OCRDMA_ALLOC_PD_RSP_DPP_PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		pd->dpp_enabled = false;
		pd->num_dpp_qp = 0;
	पूर्ण
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_dealloc_pd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_pd *pd)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_dealloc_pd *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->id = pd->id;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	kमुक्त(cmd);
	वापस status;
पूर्ण


अटल पूर्णांक ocrdma_mbx_alloc_pd_range(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = -ENOMEM;
	माप_प्रकार pd_biपंचांगap_size;
	काष्ठा ocrdma_alloc_pd_range *cmd;
	काष्ठा ocrdma_alloc_pd_range_rsp *rsp;

	/* Pre allocate the DPP PDs */
	अगर (dev->attr.max_dpp_pds) अणु
		cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_PD_RANGE,
					  माप(*cmd));
		अगर (!cmd)
			वापस -ENOMEM;
		cmd->pd_count = dev->attr.max_dpp_pds;
		cmd->enable_dpp_rsvd |= OCRDMA_ALLOC_PD_ENABLE_DPP;
		status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
		rsp = (काष्ठा ocrdma_alloc_pd_range_rsp *)cmd;

		अगर (!status && (rsp->dpp_page_pdid & OCRDMA_ALLOC_PD_RSP_DPP) &&
		    rsp->pd_count) अणु
			dev->pd_mgr->dpp_page_index = rsp->dpp_page_pdid >>
					OCRDMA_ALLOC_PD_RSP_DPP_PAGE_SHIFT;
			dev->pd_mgr->pd_dpp_start = rsp->dpp_page_pdid &
					OCRDMA_ALLOC_PD_RNG_RSP_START_PDID_MASK;
			dev->pd_mgr->max_dpp_pd = rsp->pd_count;
			pd_biपंचांगap_size =
				BITS_TO_LONGS(rsp->pd_count) * माप(दीर्घ);
			dev->pd_mgr->pd_dpp_biपंचांगap = kzalloc(pd_biपंचांगap_size,
							     GFP_KERNEL);
		पूर्ण
		kमुक्त(cmd);
	पूर्ण

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_PD_RANGE, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->pd_count = dev->attr.max_pd - dev->attr.max_dpp_pds;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	rsp = (काष्ठा ocrdma_alloc_pd_range_rsp *)cmd;
	अगर (!status && rsp->pd_count) अणु
		dev->pd_mgr->pd_norm_start = rsp->dpp_page_pdid &
					OCRDMA_ALLOC_PD_RNG_RSP_START_PDID_MASK;
		dev->pd_mgr->max_normal_pd = rsp->pd_count;
		pd_biपंचांगap_size = BITS_TO_LONGS(rsp->pd_count) * माप(दीर्घ);
		dev->pd_mgr->pd_norm_biपंचांगap = kzalloc(pd_biपंचांगap_size,
						      GFP_KERNEL);
	पूर्ण
	kमुक्त(cmd);

	अगर (dev->pd_mgr->pd_norm_biपंचांगap || dev->pd_mgr->pd_dpp_biपंचांगap) अणु
		/* Enable PD resource manager */
		dev->pd_mgr->pd_pपुनः_स्मृति_valid = true;
		वापस 0;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम ocrdma_mbx_dealloc_pd_range(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_dealloc_pd_range *cmd;

	/* वापस normal PDs to firmware */
	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE, माप(*cmd));
	अगर (!cmd)
		जाओ mbx_err;

	अगर (dev->pd_mgr->max_normal_pd) अणु
		cmd->start_pd_id = dev->pd_mgr->pd_norm_start;
		cmd->pd_count = dev->pd_mgr->max_normal_pd;
		ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	पूर्ण

	अगर (dev->pd_mgr->max_dpp_pd) अणु
		kमुक्त(cmd);
		/* वापस DPP PDs to firmware */
		cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_PD_RANGE,
					  माप(*cmd));
		अगर (!cmd)
			जाओ mbx_err;

		cmd->start_pd_id = dev->pd_mgr->pd_dpp_start;
		cmd->pd_count = dev->pd_mgr->max_dpp_pd;
		ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	पूर्ण
mbx_err:
	kमुक्त(cmd);
पूर्ण

व्योम ocrdma_alloc_pd_pool(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status;

	dev->pd_mgr = kzalloc(माप(काष्ठा ocrdma_pd_resource_mgr),
			      GFP_KERNEL);
	अगर (!dev->pd_mgr)
		वापस;

	status = ocrdma_mbx_alloc_pd_range(dev);
	अगर (status) अणु
		pr_err("%s(%d) Unable to initialize PD pool, using default.\n",
			 __func__, dev->id);
	पूर्ण
पूर्ण

अटल व्योम ocrdma_मुक्त_pd_pool(काष्ठा ocrdma_dev *dev)
अणु
	ocrdma_mbx_dealloc_pd_range(dev);
	kमुक्त(dev->pd_mgr->pd_norm_biपंचांगap);
	kमुक्त(dev->pd_mgr->pd_dpp_biपंचांगap);
	kमुक्त(dev->pd_mgr);
पूर्ण

अटल पूर्णांक ocrdma_build_q_conf(u32 *num_entries, पूर्णांक entry_size,
			       पूर्णांक *num_pages, पूर्णांक *page_size)
अणु
	पूर्णांक i;
	पूर्णांक mem_size;

	*num_entries = roundup_घात_of_two(*num_entries);
	mem_size = *num_entries * entry_size;
	/* find the possible lowest possible multiplier */
	क्रम (i = 0; i < OCRDMA_MAX_Q_PAGE_SIZE_CNT; i++) अणु
		अगर (mem_size <= (OCRDMA_Q_PAGE_BASE_SIZE << i))
			अवरोध;
	पूर्ण
	अगर (i >= OCRDMA_MAX_Q_PAGE_SIZE_CNT)
		वापस -EINVAL;
	mem_size = roundup(mem_size,
		       ((OCRDMA_Q_PAGE_BASE_SIZE << i) / OCRDMA_MAX_Q_PAGES));
	*num_pages =
	    mem_size / ((OCRDMA_Q_PAGE_BASE_SIZE << i) / OCRDMA_MAX_Q_PAGES);
	*page_size = ((OCRDMA_Q_PAGE_BASE_SIZE << i) / OCRDMA_MAX_Q_PAGES);
	*num_entries = mem_size / entry_size;
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_mbx_create_ah_tbl(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक i;
	पूर्णांक status = -ENOMEM;
	पूर्णांक max_ah;
	काष्ठा ocrdma_create_ah_tbl *cmd;
	काष्ठा ocrdma_create_ah_tbl_rsp *rsp;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa;
	काष्ठा ocrdma_pbe *pbes;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_AH_TBL, माप(*cmd));
	अगर (!cmd)
		वापस status;

	max_ah = OCRDMA_MAX_AH;
	dev->av_tbl.size = माप(काष्ठा ocrdma_av) * max_ah;

	/* number of PBEs in PBL */
	cmd->ah_conf = (OCRDMA_AH_TBL_PAGES <<
				OCRDMA_CREATE_AH_NUM_PAGES_SHIFT) &
				OCRDMA_CREATE_AH_NUM_PAGES_MASK;

	/* page size */
	क्रम (i = 0; i < OCRDMA_MAX_Q_PAGE_SIZE_CNT; i++) अणु
		अगर (PAGE_SIZE == (OCRDMA_MIN_Q_PAGE_SIZE << i))
			अवरोध;
	पूर्ण
	cmd->ah_conf |= (i << OCRDMA_CREATE_AH_PAGE_SIZE_SHIFT) &
				OCRDMA_CREATE_AH_PAGE_SIZE_MASK;

	/* ah_entry size */
	cmd->ah_conf |= (माप(काष्ठा ocrdma_av) <<
				OCRDMA_CREATE_AH_ENTRY_SIZE_SHIFT) &
				OCRDMA_CREATE_AH_ENTRY_SIZE_MASK;

	dev->av_tbl.pbl.va = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
						&dev->av_tbl.pbl.pa,
						GFP_KERNEL);
	अगर (dev->av_tbl.pbl.va == शून्य)
		जाओ mem_err;

	dev->av_tbl.va = dma_alloc_coherent(&pdev->dev, dev->av_tbl.size,
					    &pa, GFP_KERNEL);
	अगर (dev->av_tbl.va == शून्य)
		जाओ mem_err_ah;
	dev->av_tbl.pa = pa;
	dev->av_tbl.num_ah = max_ah;

	pbes = (काष्ठा ocrdma_pbe *)dev->av_tbl.pbl.va;
	क्रम (i = 0; i < dev->av_tbl.size / OCRDMA_MIN_Q_PAGE_SIZE; i++) अणु
		pbes[i].pa_lo = (u32)cpu_to_le32(pa & 0xffffffff);
		pbes[i].pa_hi = (u32)cpu_to_le32(upper_32_bits(pa));
		pa += PAGE_SIZE;
	पूर्ण
	cmd->tbl_addr[0].lo = (u32)(dev->av_tbl.pbl.pa & 0xFFFFFFFF);
	cmd->tbl_addr[0].hi = (u32)upper_32_bits(dev->av_tbl.pbl.pa);
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_create_ah_tbl_rsp *)cmd;
	dev->av_tbl.ahid = rsp->ahid & 0xFFFF;
	kमुक्त(cmd);
	वापस 0;

mbx_err:
	dma_मुक्त_coherent(&pdev->dev, dev->av_tbl.size, dev->av_tbl.va,
			  dev->av_tbl.pa);
	dev->av_tbl.va = शून्य;
mem_err_ah:
	dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->av_tbl.pbl.va,
			  dev->av_tbl.pbl.pa);
	dev->av_tbl.pbl.va = शून्य;
	dev->av_tbl.size = 0;
mem_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल व्योम ocrdma_mbx_delete_ah_tbl(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_delete_ah_tbl *cmd;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;

	अगर (dev->av_tbl.va == शून्य)
		वापस;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_AH_TBL, माप(*cmd));
	अगर (!cmd)
		वापस;
	cmd->ahid = dev->av_tbl.ahid;

	ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	dma_मुक्त_coherent(&pdev->dev, dev->av_tbl.size, dev->av_tbl.va,
			  dev->av_tbl.pa);
	dev->av_tbl.va = शून्य;
	dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dev->av_tbl.pbl.va,
			  dev->av_tbl.pbl.pa);
	kमुक्त(cmd);
पूर्ण

/* Multiple CQs uses the EQ. This routine वापसs least used
 * EQ to associate with CQ. This will distributes the पूर्णांकerrupt
 * processing and CPU load to associated EQ, vector and so to that CPU.
 */
अटल u16 ocrdma_bind_eq(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक i, selected_eq = 0, cq_cnt = 0;
	u16 eq_id;

	mutex_lock(&dev->dev_lock);
	cq_cnt = dev->eq_tbl[0].cq_cnt;
	eq_id = dev->eq_tbl[0].q.id;
	/* find the EQ which is has the least number of
	 * CQs associated with it.
	 */
	क्रम (i = 0; i < dev->eq_cnt; i++) अणु
		अगर (dev->eq_tbl[i].cq_cnt < cq_cnt) अणु
			cq_cnt = dev->eq_tbl[i].cq_cnt;
			eq_id = dev->eq_tbl[i].q.id;
			selected_eq = i;
		पूर्ण
	पूर्ण
	dev->eq_tbl[selected_eq].cq_cnt += 1;
	mutex_unlock(&dev->dev_lock);
	वापस eq_id;
पूर्ण

अटल व्योम ocrdma_unbind_eq(काष्ठा ocrdma_dev *dev, u16 eq_id)
अणु
	पूर्णांक i;

	mutex_lock(&dev->dev_lock);
	i = ocrdma_get_eq_table_index(dev, eq_id);
	अगर (i == -EINVAL)
		BUG();
	dev->eq_tbl[i].cq_cnt -= 1;
	mutex_unlock(&dev->dev_lock);
पूर्ण

पूर्णांक ocrdma_mbx_create_cq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_cq *cq,
			 पूर्णांक entries, पूर्णांक dpp_cq, u16 pd_id)
अणु
	पूर्णांक status = -ENOMEM; पूर्णांक max_hw_cqe;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	काष्ठा ocrdma_create_cq *cmd;
	काष्ठा ocrdma_create_cq_rsp *rsp;
	u32 hw_pages, cqe_size, page_size, cqe_count;

	अगर (entries > dev->attr.max_cqe) अणु
		pr_err("%s(%d) max_cqe=0x%x, requester_cqe=0x%x\n",
		       __func__, dev->id, dev->attr.max_cqe, entries);
		वापस -EINVAL;
	पूर्ण
	अगर (dpp_cq && (ocrdma_get_asic_type(dev) != OCRDMA_ASIC_GEN_SKH_R))
		वापस -EINVAL;

	अगर (dpp_cq) अणु
		cq->max_hw_cqe = 1;
		max_hw_cqe = 1;
		cqe_size = OCRDMA_DPP_CQE_SIZE;
		hw_pages = 1;
	पूर्ण अन्यथा अणु
		cq->max_hw_cqe = dev->attr.max_cqe;
		max_hw_cqe = dev->attr.max_cqe;
		cqe_size = माप(काष्ठा ocrdma_cqe);
		hw_pages = OCRDMA_CREATE_CQ_MAX_PAGES;
	पूर्ण

	cq->len = roundup(max_hw_cqe * cqe_size, OCRDMA_MIN_Q_PAGE_SIZE);

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_CQ, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	ocrdma_init_mch(&cmd->cmd.req, OCRDMA_CMD_CREATE_CQ,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));
	cq->va = dma_alloc_coherent(&pdev->dev, cq->len, &cq->pa, GFP_KERNEL);
	अगर (!cq->va) अणु
		status = -ENOMEM;
		जाओ mem_err;
	पूर्ण
	page_size = cq->len / hw_pages;
	cmd->cmd.pgsz_pgcnt = (page_size / OCRDMA_MIN_Q_PAGE_SIZE) <<
					OCRDMA_CREATE_CQ_PAGE_SIZE_SHIFT;
	cmd->cmd.pgsz_pgcnt |= hw_pages;
	cmd->cmd.ev_cnt_flags = OCRDMA_CREATE_CQ_DEF_FLAGS;

	cq->eqn = ocrdma_bind_eq(dev);
	cmd->cmd.req.rsvd_version = OCRDMA_CREATE_CQ_VER3;
	cqe_count = cq->len / cqe_size;
	cq->cqe_cnt = cqe_count;
	अगर (cqe_count > 1024) अणु
		/* Set cnt to 3 to indicate more than 1024 cq entries */
		cmd->cmd.ev_cnt_flags |= (0x3 << OCRDMA_CREATE_CQ_CNT_SHIFT);
	पूर्ण अन्यथा अणु
		u8 count = 0;
		चयन (cqe_count) अणु
		हाल 256:
			count = 0;
			अवरोध;
		हाल 512:
			count = 1;
			अवरोध;
		हाल 1024:
			count = 2;
			अवरोध;
		शेष:
			जाओ mbx_err;
		पूर्ण
		cmd->cmd.ev_cnt_flags |= (count << OCRDMA_CREATE_CQ_CNT_SHIFT);
	पूर्ण
	/* shared eq between all the consumer cqs. */
	cmd->cmd.eqn = cq->eqn;
	अगर (ocrdma_get_asic_type(dev) == OCRDMA_ASIC_GEN_SKH_R) अणु
		अगर (dpp_cq)
			cmd->cmd.pgsz_pgcnt |= OCRDMA_CREATE_CQ_DPP <<
				OCRDMA_CREATE_CQ_TYPE_SHIFT;
		cq->phase_change = false;
		cmd->cmd.pdid_cqecnt = (cq->len / cqe_size);
	पूर्ण अन्यथा अणु
		cmd->cmd.pdid_cqecnt = (cq->len / cqe_size) - 1;
		cmd->cmd.ev_cnt_flags |= OCRDMA_CREATE_CQ_FLAGS_AUTO_VALID;
		cq->phase_change = true;
	पूर्ण

	/* pd_id valid only क्रम v3 */
	cmd->cmd.pdid_cqecnt |= (pd_id <<
		OCRDMA_CREATE_CQ_CMD_PDID_SHIFT);
	ocrdma_build_q_pages(&cmd->cmd.pa[0], hw_pages, cq->pa, page_size);
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;

	rsp = (काष्ठा ocrdma_create_cq_rsp *)cmd;
	cq->id = (u16) (rsp->rsp.cq_id & OCRDMA_CREATE_CQ_RSP_CQ_ID_MASK);
	kमुक्त(cmd);
	वापस 0;
mbx_err:
	ocrdma_unbind_eq(dev, cq->eqn);
	dma_मुक्त_coherent(&pdev->dev, cq->len, cq->va, cq->pa);
mem_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

व्योम ocrdma_mbx_destroy_cq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_cq *cq)
अणु
	काष्ठा ocrdma_destroy_cq *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_CQ, माप(*cmd));
	अगर (!cmd)
		वापस;
	ocrdma_init_mch(&cmd->req, OCRDMA_CMD_DELETE_CQ,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));

	cmd->bypass_flush_qid |=
	    (cq->id << OCRDMA_DESTROY_CQ_QID_SHIFT) &
	    OCRDMA_DESTROY_CQ_QID_MASK;

	ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	ocrdma_unbind_eq(dev, cq->eqn);
	dma_मुक्त_coherent(&dev->nic_info.pdev->dev, cq->len, cq->va, cq->pa);
	kमुक्त(cmd);
पूर्ण

पूर्णांक ocrdma_mbx_alloc_lkey(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_hw_mr *hwmr,
			  u32 pdid, पूर्णांक addr_check)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_alloc_lkey *cmd;
	काष्ठा ocrdma_alloc_lkey_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_ALLOC_LKEY, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->pdid = pdid;
	cmd->pbl_sz_flags |= addr_check;
	cmd->pbl_sz_flags |= (hwmr->fr_mr << OCRDMA_ALLOC_LKEY_FMR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_wr << OCRDMA_ALLOC_LKEY_REMOTE_WR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_rd << OCRDMA_ALLOC_LKEY_REMOTE_RD_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->local_wr << OCRDMA_ALLOC_LKEY_LOCAL_WR_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->remote_atomic << OCRDMA_ALLOC_LKEY_REMOTE_ATOMIC_SHIFT);
	cmd->pbl_sz_flags |=
	    (hwmr->num_pbls << OCRDMA_ALLOC_LKEY_PBL_SIZE_SHIFT);

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_alloc_lkey_rsp *)cmd;
	hwmr->lkey = rsp->lrkey;
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_dealloc_lkey(काष्ठा ocrdma_dev *dev, पूर्णांक fr_mr, u32 lkey)
अणु
	पूर्णांक status;
	काष्ठा ocrdma_dealloc_lkey *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DEALLOC_LKEY, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	cmd->lkey = lkey;
	cmd->rsvd_frmr = fr_mr ? 1 : 0;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);

	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_reg_mr(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_hw_mr *hwmr,
			     u32 pdid, u32 pbl_cnt, u32 pbe_size, u32 last)
अणु
	पूर्णांक status = -ENOMEM;
	पूर्णांक i;
	काष्ठा ocrdma_reg_nsmr *cmd;
	काष्ठा ocrdma_reg_nsmr_rsp *rsp;
	u64 fbo = hwmr->va & (hwmr->pbe_size - 1);

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_REGISTER_NSMR, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	cmd->num_pbl_pdid =
	    pdid | (hwmr->num_pbls << OCRDMA_REG_NSMR_NUM_PBL_SHIFT);
	cmd->fr_mr = hwmr->fr_mr;

	cmd->flags_hpage_pbe_sz |= (hwmr->remote_wr <<
				    OCRDMA_REG_NSMR_REMOTE_WR_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->remote_rd <<
				    OCRDMA_REG_NSMR_REMOTE_RD_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->local_wr <<
				    OCRDMA_REG_NSMR_LOCAL_WR_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->remote_atomic <<
				    OCRDMA_REG_NSMR_REMOTE_ATOMIC_SHIFT);
	cmd->flags_hpage_pbe_sz |= (hwmr->mw_bind <<
				    OCRDMA_REG_NSMR_BIND_MEMWIN_SHIFT);
	cmd->flags_hpage_pbe_sz |= (last << OCRDMA_REG_NSMR_LAST_SHIFT);

	cmd->flags_hpage_pbe_sz |= (hwmr->pbe_size / OCRDMA_MIN_HPAGE_SIZE);
	cmd->flags_hpage_pbe_sz |= (hwmr->pbl_size / OCRDMA_MIN_HPAGE_SIZE) <<
					OCRDMA_REG_NSMR_HPAGE_SIZE_SHIFT;
	cmd->totlen_low = hwmr->len;
	cmd->totlen_high = upper_32_bits(hwmr->len);
	cmd->fbo_low = lower_32_bits(fbo);
	cmd->fbo_high = upper_32_bits(fbo);
	cmd->va_loaddr = (u32) hwmr->va;
	cmd->va_hiaddr = (u32) upper_32_bits(hwmr->va);

	क्रम (i = 0; i < pbl_cnt; i++) अणु
		cmd->pbl[i].lo = (u32) (hwmr->pbl_table[i].pa & 0xffffffff);
		cmd->pbl[i].hi = upper_32_bits(hwmr->pbl_table[i].pa);
	पूर्ण
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_reg_nsmr_rsp *)cmd;
	hwmr->lkey = rsp->lrkey;
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_reg_mr_cont(काष्ठा ocrdma_dev *dev,
				  काष्ठा ocrdma_hw_mr *hwmr, u32 pbl_cnt,
				  u32 pbl_offset, u32 last)
अणु
	पूर्णांक status;
	पूर्णांक i;
	काष्ठा ocrdma_reg_nsmr_cont *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_REGISTER_NSMR_CONT, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;
	cmd->lrkey = hwmr->lkey;
	cmd->num_pbl_offset = (pbl_cnt << OCRDMA_REG_NSMR_CONT_NUM_PBL_SHIFT) |
	    (pbl_offset & OCRDMA_REG_NSMR_CONT_PBL_SHIFT_MASK);
	cmd->last = last << OCRDMA_REG_NSMR_CONT_LAST_SHIFT;

	क्रम (i = 0; i < pbl_cnt; i++) अणु
		cmd->pbl[i].lo =
		    (u32) (hwmr->pbl_table[i + pbl_offset].pa & 0xffffffff);
		cmd->pbl[i].hi =
		    upper_32_bits(hwmr->pbl_table[i + pbl_offset].pa);
	पूर्ण
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);

	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_reg_mr(काष्ठा ocrdma_dev *dev,
		  काष्ठा ocrdma_hw_mr *hwmr, u32 pdid, पूर्णांक acc)
अणु
	पूर्णांक status;
	u32 last = 0;
	u32 cur_pbl_cnt, pbl_offset;
	u32 pending_pbl_cnt = hwmr->num_pbls;

	pbl_offset = 0;
	cur_pbl_cnt = min(pending_pbl_cnt, MAX_OCRDMA_NSMR_PBL);
	अगर (cur_pbl_cnt == pending_pbl_cnt)
		last = 1;

	status = ocrdma_mbx_reg_mr(dev, hwmr, pdid,
				   cur_pbl_cnt, hwmr->pbe_size, last);
	अगर (status) अणु
		pr_err("%s() status=%d\n", __func__, status);
		वापस status;
	पूर्ण
	/* अगर there is no more pbls to रेजिस्टर then निकास. */
	अगर (last)
		वापस 0;

	जबतक (!last) अणु
		pbl_offset += cur_pbl_cnt;
		pending_pbl_cnt -= cur_pbl_cnt;
		cur_pbl_cnt = min(pending_pbl_cnt, MAX_OCRDMA_NSMR_PBL);
		/* अगर we reach the end of the pbls, then need to set the last
		 * bit, indicating no more pbls to रेजिस्टर क्रम this memory key.
		 */
		अगर (cur_pbl_cnt == pending_pbl_cnt)
			last = 1;

		status = ocrdma_mbx_reg_mr_cont(dev, hwmr, cur_pbl_cnt,
						pbl_offset, last);
		अगर (status)
			अवरोध;
	पूर्ण
	अगर (status)
		pr_err("%s() err. status=%d\n", __func__, status);

	वापस status;
पूर्ण

bool ocrdma_is_qp_in_sq_flushlist(काष्ठा ocrdma_cq *cq, काष्ठा ocrdma_qp *qp)
अणु
	काष्ठा ocrdma_qp *पंचांगp;
	bool found = false;
	list_क्रम_each_entry(पंचांगp, &cq->sq_head, sq_entry) अणु
		अगर (qp == पंचांगp) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

bool ocrdma_is_qp_in_rq_flushlist(काष्ठा ocrdma_cq *cq, काष्ठा ocrdma_qp *qp)
अणु
	काष्ठा ocrdma_qp *पंचांगp;
	bool found = false;
	list_क्रम_each_entry(पंचांगp, &cq->rq_head, rq_entry) अणु
		अगर (qp == पंचांगp) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस found;
पूर्ण

व्योम ocrdma_flush_qp(काष्ठा ocrdma_qp *qp)
अणु
	bool found;
	अचिन्हित दीर्घ flags;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);

	spin_lock_irqsave(&dev->flush_q_lock, flags);
	found = ocrdma_is_qp_in_sq_flushlist(qp->sq_cq, qp);
	अगर (!found)
		list_add_tail(&qp->sq_entry, &qp->sq_cq->sq_head);
	अगर (!qp->srq) अणु
		found = ocrdma_is_qp_in_rq_flushlist(qp->rq_cq, qp);
		अगर (!found)
			list_add_tail(&qp->rq_entry, &qp->rq_cq->rq_head);
	पूर्ण
	spin_unlock_irqrestore(&dev->flush_q_lock, flags);
पूर्ण

अटल व्योम ocrdma_init_hwq_ptr(काष्ठा ocrdma_qp *qp)
अणु
	qp->sq.head = 0;
	qp->sq.tail = 0;
	qp->rq.head = 0;
	qp->rq.tail = 0;
पूर्ण

पूर्णांक ocrdma_qp_state_change(काष्ठा ocrdma_qp *qp, क्रमागत ib_qp_state new_ib_state,
			   क्रमागत ib_qp_state *old_ib_state)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत ocrdma_qp_state new_state;
	new_state = get_ocrdma_qp_state(new_ib_state);

	/* sync with wqe and rqe posting */
	spin_lock_irqsave(&qp->q_lock, flags);

	अगर (old_ib_state)
		*old_ib_state = get_ibqp_state(qp->state);
	अगर (new_state == qp->state) अणु
		spin_unlock_irqrestore(&qp->q_lock, flags);
		वापस 1;
	पूर्ण


	अगर (new_state == OCRDMA_QPS_INIT) अणु
		ocrdma_init_hwq_ptr(qp);
		ocrdma_del_flush_qp(qp);
	पूर्ण अन्यथा अगर (new_state == OCRDMA_QPS_ERR) अणु
		ocrdma_flush_qp(qp);
	पूर्ण

	qp->state = new_state;

	spin_unlock_irqrestore(&qp->q_lock, flags);
	वापस 0;
पूर्ण

अटल u32 ocrdma_set_create_qp_mbx_access_flags(काष्ठा ocrdma_qp *qp)
अणु
	u32 flags = 0;
	अगर (qp->cap_flags & OCRDMA_QP_INB_RD)
		flags |= OCRDMA_CREATE_QP_REQ_INB_RDEN_MASK;
	अगर (qp->cap_flags & OCRDMA_QP_INB_WR)
		flags |= OCRDMA_CREATE_QP_REQ_INB_WREN_MASK;
	अगर (qp->cap_flags & OCRDMA_QP_MW_BIND)
		flags |= OCRDMA_CREATE_QP_REQ_BIND_MEMWIN_MASK;
	अगर (qp->cap_flags & OCRDMA_QP_LKEY0)
		flags |= OCRDMA_CREATE_QP_REQ_ZERO_LKEYEN_MASK;
	अगर (qp->cap_flags & OCRDMA_QP_FAST_REG)
		flags |= OCRDMA_CREATE_QP_REQ_FMR_EN_MASK;
	वापस flags;
पूर्ण

अटल पूर्णांक ocrdma_set_create_qp_sq_cmd(काष्ठा ocrdma_create_qp_req *cmd,
					काष्ठा ib_qp_init_attr *attrs,
					काष्ठा ocrdma_qp *qp)
अणु
	पूर्णांक status;
	u32 len, hw_pages, hw_page_size;
	dma_addr_t pa;
	काष्ठा ocrdma_pd *pd = qp->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	u32 max_wqe_allocated;
	u32 max_sges = attrs->cap.max_send_sge;

	/* QP1 may exceed 127 */
	max_wqe_allocated = min_t(u32, attrs->cap.max_send_wr + 1,
				dev->attr.max_wqe);

	status = ocrdma_build_q_conf(&max_wqe_allocated,
		dev->attr.wqe_size, &hw_pages, &hw_page_size);
	अगर (status) अणु
		pr_err("%s() req. max_send_wr=0x%x\n", __func__,
		       max_wqe_allocated);
		वापस -EINVAL;
	पूर्ण
	qp->sq.max_cnt = max_wqe_allocated;
	len = (hw_pages * hw_page_size);

	qp->sq.va = dma_alloc_coherent(&pdev->dev, len, &pa, GFP_KERNEL);
	अगर (!qp->sq.va)
		वापस -EINVAL;
	qp->sq.len = len;
	qp->sq.pa = pa;
	qp->sq.entry_size = dev->attr.wqe_size;
	ocrdma_build_q_pages(&cmd->wq_addr[0], hw_pages, pa, hw_page_size);

	cmd->type_pgsz_pdn |= (ilog2(hw_page_size / OCRDMA_MIN_Q_PAGE_SIZE)
				<< OCRDMA_CREATE_QP_REQ_SQ_PAGE_SIZE_SHIFT);
	cmd->num_wq_rq_pages |= (hw_pages <<
				 OCRDMA_CREATE_QP_REQ_NUM_WQ_PAGES_SHIFT) &
	    OCRDMA_CREATE_QP_REQ_NUM_WQ_PAGES_MASK;
	cmd->max_sge_send_ग_लिखो |= (max_sges <<
				    OCRDMA_CREATE_QP_REQ_MAX_SGE_SEND_SHIFT) &
	    OCRDMA_CREATE_QP_REQ_MAX_SGE_SEND_MASK;
	cmd->max_sge_send_ग_लिखो |= (max_sges <<
				    OCRDMA_CREATE_QP_REQ_MAX_SGE_WRITE_SHIFT) &
					OCRDMA_CREATE_QP_REQ_MAX_SGE_WRITE_MASK;
	cmd->max_wqe_rqe |= (ilog2(qp->sq.max_cnt) <<
			     OCRDMA_CREATE_QP_REQ_MAX_WQE_SHIFT) &
				OCRDMA_CREATE_QP_REQ_MAX_WQE_MASK;
	cmd->wqe_rqe_size |= (dev->attr.wqe_size <<
			      OCRDMA_CREATE_QP_REQ_WQE_SIZE_SHIFT) &
				OCRDMA_CREATE_QP_REQ_WQE_SIZE_MASK;
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_set_create_qp_rq_cmd(काष्ठा ocrdma_create_qp_req *cmd,
					काष्ठा ib_qp_init_attr *attrs,
					काष्ठा ocrdma_qp *qp)
अणु
	पूर्णांक status;
	u32 len, hw_pages, hw_page_size;
	dma_addr_t pa = 0;
	काष्ठा ocrdma_pd *pd = qp->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	u32 max_rqe_allocated = attrs->cap.max_recv_wr + 1;

	status = ocrdma_build_q_conf(&max_rqe_allocated, dev->attr.rqe_size,
				     &hw_pages, &hw_page_size);
	अगर (status) अणु
		pr_err("%s() req. max_recv_wr=0x%x\n", __func__,
		       attrs->cap.max_recv_wr + 1);
		वापस status;
	पूर्ण
	qp->rq.max_cnt = max_rqe_allocated;
	len = (hw_pages * hw_page_size);

	qp->rq.va = dma_alloc_coherent(&pdev->dev, len, &pa, GFP_KERNEL);
	अगर (!qp->rq.va)
		वापस -ENOMEM;
	qp->rq.pa = pa;
	qp->rq.len = len;
	qp->rq.entry_size = dev->attr.rqe_size;

	ocrdma_build_q_pages(&cmd->rq_addr[0], hw_pages, pa, hw_page_size);
	cmd->type_pgsz_pdn |= (ilog2(hw_page_size / OCRDMA_MIN_Q_PAGE_SIZE) <<
		OCRDMA_CREATE_QP_REQ_RQ_PAGE_SIZE_SHIFT);
	cmd->num_wq_rq_pages |=
	    (hw_pages << OCRDMA_CREATE_QP_REQ_NUM_RQ_PAGES_SHIFT) &
	    OCRDMA_CREATE_QP_REQ_NUM_RQ_PAGES_MASK;
	cmd->max_sge_recv_flags |= (attrs->cap.max_recv_sge <<
				OCRDMA_CREATE_QP_REQ_MAX_SGE_RECV_SHIFT) &
				OCRDMA_CREATE_QP_REQ_MAX_SGE_RECV_MASK;
	cmd->max_wqe_rqe |= (ilog2(qp->rq.max_cnt) <<
				OCRDMA_CREATE_QP_REQ_MAX_RQE_SHIFT) &
				OCRDMA_CREATE_QP_REQ_MAX_RQE_MASK;
	cmd->wqe_rqe_size |= (dev->attr.rqe_size <<
			OCRDMA_CREATE_QP_REQ_RQE_SIZE_SHIFT) &
			OCRDMA_CREATE_QP_REQ_RQE_SIZE_MASK;
	वापस 0;
पूर्ण

अटल व्योम ocrdma_set_create_qp_dpp_cmd(काष्ठा ocrdma_create_qp_req *cmd,
					 काष्ठा ocrdma_pd *pd,
					 काष्ठा ocrdma_qp *qp,
					 u8 enable_dpp_cq, u16 dpp_cq_id)
अणु
	pd->num_dpp_qp--;
	qp->dpp_enabled = true;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	अगर (!enable_dpp_cq)
		वापस;
	cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_ENABLE_DPP_MASK;
	cmd->dpp_credits_cqid = dpp_cq_id;
	cmd->dpp_credits_cqid |= OCRDMA_CREATE_QP_REQ_DPP_CREDIT_LIMIT <<
					OCRDMA_CREATE_QP_REQ_DPP_CREDIT_SHIFT;
पूर्ण

अटल पूर्णांक ocrdma_set_create_qp_ird_cmd(काष्ठा ocrdma_create_qp_req *cmd,
					काष्ठा ocrdma_qp *qp)
अणु
	काष्ठा ocrdma_pd *pd = qp->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa = 0;
	पूर्णांक ird_page_size = dev->attr.ird_page_size;
	पूर्णांक ird_q_len = dev->attr.num_ird_pages * ird_page_size;
	काष्ठा ocrdma_hdr_wqe *rqe;
	पूर्णांक i  = 0;

	अगर (dev->attr.ird == 0)
		वापस 0;

	qp->ird_q_va = dma_alloc_coherent(&pdev->dev, ird_q_len, &pa,
					  GFP_KERNEL);
	अगर (!qp->ird_q_va)
		वापस -ENOMEM;
	ocrdma_build_q_pages(&cmd->ird_addr[0], dev->attr.num_ird_pages,
			     pa, ird_page_size);
	क्रम (; i < ird_q_len / dev->attr.rqe_size; i++) अणु
		rqe = (काष्ठा ocrdma_hdr_wqe *)(qp->ird_q_va +
			(i * dev->attr.rqe_size));
		rqe->cw = 0;
		rqe->cw |= 2;
		rqe->cw |= (OCRDMA_TYPE_LKEY << OCRDMA_WQE_TYPE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_SIZE_SHIFT);
		rqe->cw |= (8 << OCRDMA_WQE_NXT_WQE_SIZE_SHIFT);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ocrdma_get_create_qp_rsp(काष्ठा ocrdma_create_qp_rsp *rsp,
				     काष्ठा ocrdma_qp *qp,
				     काष्ठा ib_qp_init_attr *attrs,
				     u16 *dpp_offset, u16 *dpp_credit_lmt)
अणु
	u32 max_wqe_allocated, max_rqe_allocated;
	qp->id = rsp->qp_id & OCRDMA_CREATE_QP_RSP_QP_ID_MASK;
	qp->rq.dbid = rsp->sq_rq_id & OCRDMA_CREATE_QP_RSP_RQ_ID_MASK;
	qp->sq.dbid = rsp->sq_rq_id >> OCRDMA_CREATE_QP_RSP_SQ_ID_SHIFT;
	qp->max_ird = rsp->max_ord_ird & OCRDMA_CREATE_QP_RSP_MAX_IRD_MASK;
	qp->max_ord = (rsp->max_ord_ird >> OCRDMA_CREATE_QP_RSP_MAX_ORD_SHIFT);
	qp->dpp_enabled = false;
	अगर (rsp->dpp_response & OCRDMA_CREATE_QP_RSP_DPP_ENABLED_MASK) अणु
		qp->dpp_enabled = true;
		*dpp_credit_lmt = (rsp->dpp_response &
				OCRDMA_CREATE_QP_RSP_DPP_CREDITS_MASK) >>
				OCRDMA_CREATE_QP_RSP_DPP_CREDITS_SHIFT;
		*dpp_offset = (rsp->dpp_response &
				OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_MASK) >>
				OCRDMA_CREATE_QP_RSP_DPP_PAGE_OFFSET_SHIFT;
	पूर्ण
	max_wqe_allocated =
		rsp->max_wqe_rqe >> OCRDMA_CREATE_QP_RSP_MAX_WQE_SHIFT;
	max_wqe_allocated = 1 << max_wqe_allocated;
	max_rqe_allocated = 1 << ((u16)rsp->max_wqe_rqe);

	qp->sq.max_cnt = max_wqe_allocated;
	qp->sq.max_wqe_idx = max_wqe_allocated - 1;

	अगर (!attrs->srq) अणु
		qp->rq.max_cnt = max_rqe_allocated;
		qp->rq.max_wqe_idx = max_rqe_allocated - 1;
	पूर्ण
पूर्ण

पूर्णांक ocrdma_mbx_create_qp(काष्ठा ocrdma_qp *qp, काष्ठा ib_qp_init_attr *attrs,
			 u8 enable_dpp_cq, u16 dpp_cq_id, u16 *dpp_offset,
			 u16 *dpp_credit_lmt)
अणु
	पूर्णांक status = -ENOMEM;
	u32 flags = 0;
	काष्ठा ocrdma_pd *pd = qp->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	काष्ठा ocrdma_cq *cq;
	काष्ठा ocrdma_create_qp_req *cmd;
	काष्ठा ocrdma_create_qp_rsp *rsp;
	पूर्णांक qptype;

	चयन (attrs->qp_type) अणु
	हाल IB_QPT_GSI:
		qptype = OCRDMA_QPT_GSI;
		अवरोध;
	हाल IB_QPT_RC:
		qptype = OCRDMA_QPT_RC;
		अवरोध;
	हाल IB_QPT_UD:
		qptype = OCRDMA_QPT_UD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_QP, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->type_pgsz_pdn |= (qptype << OCRDMA_CREATE_QP_REQ_QPT_SHIFT) &
						OCRDMA_CREATE_QP_REQ_QPT_MASK;
	status = ocrdma_set_create_qp_sq_cmd(cmd, attrs, qp);
	अगर (status)
		जाओ sq_err;

	अगर (attrs->srq) अणु
		काष्ठा ocrdma_srq *srq = get_ocrdma_srq(attrs->srq);
		cmd->max_sge_recv_flags |= OCRDMA_CREATE_QP_REQ_USE_SRQ_MASK;
		cmd->rq_addr[0].lo = srq->id;
		qp->srq = srq;
	पूर्ण अन्यथा अणु
		status = ocrdma_set_create_qp_rq_cmd(cmd, attrs, qp);
		अगर (status)
			जाओ rq_err;
	पूर्ण

	status = ocrdma_set_create_qp_ird_cmd(cmd, qp);
	अगर (status)
		जाओ mbx_err;

	cmd->type_pgsz_pdn |= (pd->id << OCRDMA_CREATE_QP_REQ_PD_ID_SHIFT) &
				OCRDMA_CREATE_QP_REQ_PD_ID_MASK;

	flags = ocrdma_set_create_qp_mbx_access_flags(qp);

	cmd->max_sge_recv_flags |= flags;
	cmd->max_ord_ird |= (dev->attr.max_ord_per_qp <<
			     OCRDMA_CREATE_QP_REQ_MAX_ORD_SHIFT) &
				OCRDMA_CREATE_QP_REQ_MAX_ORD_MASK;
	cmd->max_ord_ird |= (dev->attr.max_ird_per_qp <<
			     OCRDMA_CREATE_QP_REQ_MAX_IRD_SHIFT) &
				OCRDMA_CREATE_QP_REQ_MAX_IRD_MASK;
	cq = get_ocrdma_cq(attrs->send_cq);
	cmd->wq_rq_cqid |= (cq->id << OCRDMA_CREATE_QP_REQ_WQ_CQID_SHIFT) &
				OCRDMA_CREATE_QP_REQ_WQ_CQID_MASK;
	qp->sq_cq = cq;
	cq = get_ocrdma_cq(attrs->recv_cq);
	cmd->wq_rq_cqid |= (cq->id << OCRDMA_CREATE_QP_REQ_RQ_CQID_SHIFT) &
				OCRDMA_CREATE_QP_REQ_RQ_CQID_MASK;
	qp->rq_cq = cq;

	अगर (pd->dpp_enabled && attrs->cap.max_अंतरभूत_data && pd->num_dpp_qp &&
	    (attrs->cap.max_अंतरभूत_data <= dev->attr.max_अंतरभूत_data)) अणु
		ocrdma_set_create_qp_dpp_cmd(cmd, pd, qp, enable_dpp_cq,
					     dpp_cq_id);
	पूर्ण

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_create_qp_rsp *)cmd;
	ocrdma_get_create_qp_rsp(rsp, qp, attrs, dpp_offset, dpp_credit_lmt);
	qp->state = OCRDMA_QPS_RST;
	kमुक्त(cmd);
	वापस 0;
mbx_err:
	अगर (qp->rq.va)
		dma_मुक्त_coherent(&pdev->dev, qp->rq.len, qp->rq.va, qp->rq.pa);
rq_err:
	pr_err("%s(%d) rq_err\n", __func__, dev->id);
	dma_मुक्त_coherent(&pdev->dev, qp->sq.len, qp->sq.va, qp->sq.pa);
sq_err:
	pr_err("%s(%d) sq_err\n", __func__, dev->id);
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_query_qp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp,
			काष्ठा ocrdma_qp_params *param)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_query_qp *cmd;
	काष्ठा ocrdma_query_qp_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_QP, माप(*rsp));
	अगर (!cmd)
		वापस status;
	cmd->qp_id = qp->id;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_query_qp_rsp *)cmd;
	स_नकल(param, &rsp->params, माप(काष्ठा ocrdma_qp_params));
mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_set_av_params(काष्ठा ocrdma_qp *qp,
				काष्ठा ocrdma_modअगरy_qp *cmd,
				काष्ठा ib_qp_attr *attrs,
				पूर्णांक attr_mask)
अणु
	पूर्णांक status;
	काष्ठा rdma_ah_attr *ah_attr = &attrs->ah_attr;
	स्थिर काष्ठा ib_gid_attr *sgid_attr;
	u16 vlan_id = 0xFFFF;
	u8 mac_addr[6], hdr_type;
	जोड़ अणु
		काष्ठा sockaddr_in  _sockaddr_in;
		काष्ठा sockaddr_in6 _sockaddr_in6;
	पूर्ण sgid_addr, dgid_addr;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);
	स्थिर काष्ठा ib_global_route *grh;

	अगर ((rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) == 0)
		वापस -EINVAL;
	grh = rdma_ah_पढ़ो_grh(ah_attr);
	अगर (atomic_cmpxchg(&dev->update_sl, 1, 0))
		ocrdma_init_service_level(dev);
	cmd->params.tclass_sq_psn |=
	    (grh->traffic_class << OCRDMA_QP_PARAMS_TCLASS_SHIFT);
	cmd->params.rnt_rc_sl_fl |=
	    (grh->flow_label & OCRDMA_QP_PARAMS_FLOW_LABEL_MASK);
	cmd->params.rnt_rc_sl_fl |= (rdma_ah_get_sl(ah_attr) <<
				     OCRDMA_QP_PARAMS_SL_SHIFT);
	cmd->params.hop_lmt_rq_psn |=
	    (grh->hop_limit << OCRDMA_QP_PARAMS_HOP_LMT_SHIFT);
	cmd->flags |= OCRDMA_QP_PARA_FLOW_LBL_VALID;

	/* GIDs */
	स_नकल(&cmd->params.dgid[0], &grh->dgid.raw[0],
	       माप(cmd->params.dgid));

	sgid_attr = ah_attr->grh.sgid_attr;
	status = rdma_पढ़ो_gid_l2_fields(sgid_attr, &vlan_id, &mac_addr[0]);
	अगर (status)
		वापस status;

	qp->sgid_idx = grh->sgid_index;
	स_नकल(&cmd->params.sgid[0], &sgid_attr->gid.raw[0],
	       माप(cmd->params.sgid));
	status = ocrdma_resolve_dmac(dev, ah_attr, &mac_addr[0]);
	अगर (status)
		वापस status;

	cmd->params.dmac_b0_to_b3 = mac_addr[0] | (mac_addr[1] << 8) |
				(mac_addr[2] << 16) | (mac_addr[3] << 24);

	hdr_type = rdma_gid_attr_network_type(sgid_attr);
	अगर (hdr_type == RDMA_NETWORK_IPV4) अणु
		rdma_gid2ip((काष्ठा sockaddr *)&sgid_addr, &sgid_attr->gid);
		rdma_gid2ip((काष्ठा sockaddr *)&dgid_addr, &grh->dgid);
		स_नकल(&cmd->params.dgid[0],
		       &dgid_addr._sockaddr_in.sin_addr.s_addr, 4);
		स_नकल(&cmd->params.sgid[0],
		       &sgid_addr._sockaddr_in.sin_addr.s_addr, 4);
	पूर्ण
	/* convert them to LE क्रमmat. */
	ocrdma_cpu_to_le32(&cmd->params.dgid[0], माप(cmd->params.dgid));
	ocrdma_cpu_to_le32(&cmd->params.sgid[0], माप(cmd->params.sgid));
	cmd->params.vlan_dmac_b4_to_b5 = mac_addr[4] | (mac_addr[5] << 8);

	अगर (vlan_id == 0xFFFF)
		vlan_id = 0;
	अगर (vlan_id || dev->pfc_state) अणु
		अगर (!vlan_id) अणु
			pr_err("ocrdma%d:Using VLAN with PFC is recommended\n",
			       dev->id);
			pr_err("ocrdma%d:Using VLAN 0 for this connection\n",
			       dev->id);
		पूर्ण
		cmd->params.vlan_dmac_b4_to_b5 |=
		    vlan_id << OCRDMA_QP_PARAMS_VLAN_SHIFT;
		cmd->flags |= OCRDMA_QP_PARA_VLAN_EN_VALID;
		cmd->params.rnt_rc_sl_fl |=
			(dev->sl & 0x07) << OCRDMA_QP_PARAMS_SL_SHIFT;
	पूर्ण
	cmd->params.max_sge_recv_flags |= ((hdr_type <<
					OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_SHIFT) &
					OCRDMA_QP_PARAMS_FLAGS_L3_TYPE_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक ocrdma_set_qp_params(काष्ठा ocrdma_qp *qp,
				काष्ठा ocrdma_modअगरy_qp *cmd,
				काष्ठा ib_qp_attr *attrs, पूर्णांक attr_mask)
अणु
	पूर्णांक status = 0;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(qp->ibqp.device);

	अगर (attr_mask & IB_QP_PKEY_INDEX) अणु
		cmd->params.path_mtu_pkey_indx |= (attrs->pkey_index &
					    OCRDMA_QP_PARAMS_PKEY_INDEX_MASK);
		cmd->flags |= OCRDMA_QP_PARA_PKEY_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_QKEY) अणु
		qp->qkey = attrs->qkey;
		cmd->params.qkey = attrs->qkey;
		cmd->flags |= OCRDMA_QP_PARA_QKEY_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_AV) अणु
		status = ocrdma_set_av_params(qp, cmd, attrs, attr_mask);
		अगर (status)
			वापस status;
	पूर्ण अन्यथा अगर (qp->qp_type == IB_QPT_GSI || qp->qp_type == IB_QPT_UD) अणु
		/* set the शेष mac address क्रम UD, GSI QPs */
		cmd->params.dmac_b0_to_b3 = dev->nic_info.mac_addr[0] |
			(dev->nic_info.mac_addr[1] << 8) |
			(dev->nic_info.mac_addr[2] << 16) |
			(dev->nic_info.mac_addr[3] << 24);
		cmd->params.vlan_dmac_b4_to_b5 = dev->nic_info.mac_addr[4] |
					(dev->nic_info.mac_addr[5] << 8);
	पूर्ण
	अगर ((attr_mask & IB_QP_EN_SQD_ASYNC_NOTIFY) &&
	    attrs->en_sqd_async_notअगरy) अणु
		cmd->params.max_sge_recv_flags |=
			OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC;
		cmd->flags |= OCRDMA_QP_PARA_DST_QPN_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_DEST_QPN) अणु
		cmd->params.ack_to_rnr_rtc_dest_qpn |= (attrs->dest_qp_num &
				OCRDMA_QP_PARAMS_DEST_QPN_MASK);
		cmd->flags |= OCRDMA_QP_PARA_DST_QPN_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_PATH_MTU) अणु
		अगर (attrs->path_mtu < IB_MTU_512 ||
		    attrs->path_mtu > IB_MTU_4096) अणु
			pr_err("ocrdma%d: IB MTU %d is not supported\n",
			       dev->id, ib_mtu_क्रमागत_to_पूर्णांक(attrs->path_mtu));
			status = -EINVAL;
			जाओ pmtu_err;
		पूर्ण
		cmd->params.path_mtu_pkey_indx |=
		    (ib_mtu_क्रमागत_to_पूर्णांक(attrs->path_mtu) <<
		     OCRDMA_QP_PARAMS_PATH_MTU_SHIFT) &
		    OCRDMA_QP_PARAMS_PATH_MTU_MASK;
		cmd->flags |= OCRDMA_QP_PARA_PMTU_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		cmd->params.ack_to_rnr_rtc_dest_qpn |= attrs->समयout <<
		    OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT;
		cmd->flags |= OCRDMA_QP_PARA_ACK_TO_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		cmd->params.rnt_rc_sl_fl |= (attrs->retry_cnt <<
				      OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT) &
		    OCRDMA_QP_PARAMS_RETRY_CNT_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RETRY_CNT_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		cmd->params.rnt_rc_sl_fl |= (attrs->min_rnr_समयr <<
				      OCRDMA_QP_PARAMS_RNR_NAK_TIMER_SHIFT) &
		    OCRDMA_QP_PARAMS_RNR_NAK_TIMER_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RNT_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		cmd->params.ack_to_rnr_rtc_dest_qpn |= (attrs->rnr_retry <<
			OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT)
			& OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK;
		cmd->flags |= OCRDMA_QP_PARA_RRC_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_SQ_PSN) अणु
		cmd->params.tclass_sq_psn |= (attrs->sq_psn & 0x00ffffff);
		cmd->flags |= OCRDMA_QP_PARA_SQPSN_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_RQ_PSN) अणु
		cmd->params.hop_lmt_rq_psn |= (attrs->rq_psn & 0x00ffffff);
		cmd->flags |= OCRDMA_QP_PARA_RQPSN_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		अगर (attrs->max_rd_atomic > dev->attr.max_ord_per_qp) अणु
			status = -EINVAL;
			जाओ pmtu_err;
		पूर्ण
		qp->max_ord = attrs->max_rd_atomic;
		cmd->flags |= OCRDMA_QP_PARA_MAX_ORD_VALID;
	पूर्ण
	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		अगर (attrs->max_dest_rd_atomic > dev->attr.max_ird_per_qp) अणु
			status = -EINVAL;
			जाओ pmtu_err;
		पूर्ण
		qp->max_ird = attrs->max_dest_rd_atomic;
		cmd->flags |= OCRDMA_QP_PARA_MAX_IRD_VALID;
	पूर्ण
	cmd->params.max_ord_ird = (qp->max_ord <<
				OCRDMA_QP_PARAMS_MAX_ORD_SHIFT) |
				(qp->max_ird & OCRDMA_QP_PARAMS_MAX_IRD_MASK);
pmtu_err:
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_modअगरy_qp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp,
			 काष्ठा ib_qp_attr *attrs, पूर्णांक attr_mask)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_modअगरy_qp *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_MODIFY_QP, माप(*cmd));
	अगर (!cmd)
		वापस status;

	cmd->params.id = qp->id;
	cmd->flags = 0;
	अगर (attr_mask & IB_QP_STATE) अणु
		cmd->params.max_sge_recv_flags |=
		    (get_ocrdma_qp_state(attrs->qp_state) <<
		     OCRDMA_QP_PARAMS_STATE_SHIFT) &
		    OCRDMA_QP_PARAMS_STATE_MASK;
		cmd->flags |= OCRDMA_QP_PARA_QPS_VALID;
	पूर्ण अन्यथा अणु
		cmd->params.max_sge_recv_flags |=
		    (qp->state << OCRDMA_QP_PARAMS_STATE_SHIFT) &
		    OCRDMA_QP_PARAMS_STATE_MASK;
	पूर्ण

	status = ocrdma_set_qp_params(qp, cmd, attrs, attr_mask);
	अगर (status)
		जाओ mbx_err;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;

mbx_err:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_destroy_qp(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_qp *qp)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_destroy_qp *cmd;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_QP, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->qp_id = qp->id;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;

mbx_err:
	kमुक्त(cmd);
	अगर (qp->sq.va)
		dma_मुक्त_coherent(&pdev->dev, qp->sq.len, qp->sq.va, qp->sq.pa);
	अगर (!qp->srq && qp->rq.va)
		dma_मुक्त_coherent(&pdev->dev, qp->rq.len, qp->rq.va, qp->rq.pa);
	अगर (qp->dpp_enabled)
		qp->pd->num_dpp_qp++;
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_create_srq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_srq *srq,
			  काष्ठा ib_srq_init_attr *srq_attr,
			  काष्ठा ocrdma_pd *pd)
अणु
	पूर्णांक status = -ENOMEM;
	पूर्णांक hw_pages, hw_page_size;
	पूर्णांक len;
	काष्ठा ocrdma_create_srq_rsp *rsp;
	काष्ठा ocrdma_create_srq *cmd;
	dma_addr_t pa;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	u32 max_rqe_allocated;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_CREATE_SRQ, माप(*cmd));
	अगर (!cmd)
		वापस status;

	cmd->pgsz_pdid = pd->id & OCRDMA_CREATE_SRQ_PD_ID_MASK;
	max_rqe_allocated = srq_attr->attr.max_wr + 1;
	status = ocrdma_build_q_conf(&max_rqe_allocated,
				dev->attr.rqe_size,
				&hw_pages, &hw_page_size);
	अगर (status) अणु
		pr_err("%s() req. max_wr=0x%x\n", __func__,
		       srq_attr->attr.max_wr);
		status = -EINVAL;
		जाओ ret;
	पूर्ण
	len = hw_pages * hw_page_size;
	srq->rq.va = dma_alloc_coherent(&pdev->dev, len, &pa, GFP_KERNEL);
	अगर (!srq->rq.va) अणु
		status = -ENOMEM;
		जाओ ret;
	पूर्ण
	ocrdma_build_q_pages(&cmd->rq_addr[0], hw_pages, pa, hw_page_size);

	srq->rq.entry_size = dev->attr.rqe_size;
	srq->rq.pa = pa;
	srq->rq.len = len;
	srq->rq.max_cnt = max_rqe_allocated;

	cmd->max_sge_rqe = ilog2(max_rqe_allocated);
	cmd->max_sge_rqe |= srq_attr->attr.max_sge <<
				OCRDMA_CREATE_SRQ_MAX_SGE_RECV_SHIFT;

	cmd->pgsz_pdid |= (ilog2(hw_page_size / OCRDMA_MIN_Q_PAGE_SIZE)
		<< OCRDMA_CREATE_SRQ_PG_SZ_SHIFT);
	cmd->pages_rqe_sz |= (dev->attr.rqe_size
		<< OCRDMA_CREATE_SRQ_RQE_SIZE_SHIFT)
		& OCRDMA_CREATE_SRQ_RQE_SIZE_MASK;
	cmd->pages_rqe_sz |= hw_pages << OCRDMA_CREATE_SRQ_NUM_RQ_PAGES_SHIFT;

	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status)
		जाओ mbx_err;
	rsp = (काष्ठा ocrdma_create_srq_rsp *)cmd;
	srq->id = rsp->id;
	srq->rq.dbid = rsp->id;
	max_rqe_allocated = ((rsp->max_sge_rqe_allocated &
		OCRDMA_CREATE_SRQ_RSP_MAX_RQE_ALLOCATED_MASK) >>
		OCRDMA_CREATE_SRQ_RSP_MAX_RQE_ALLOCATED_SHIFT);
	max_rqe_allocated = (1 << max_rqe_allocated);
	srq->rq.max_cnt = max_rqe_allocated;
	srq->rq.max_wqe_idx = max_rqe_allocated - 1;
	srq->rq.max_sges = (rsp->max_sge_rqe_allocated &
		OCRDMA_CREATE_SRQ_RSP_MAX_SGE_RECV_ALLOCATED_MASK) >>
		OCRDMA_CREATE_SRQ_RSP_MAX_SGE_RECV_ALLOCATED_SHIFT;
	जाओ ret;
mbx_err:
	dma_मुक्त_coherent(&pdev->dev, srq->rq.len, srq->rq.va, pa);
ret:
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_modअगरy_srq(काष्ठा ocrdma_srq *srq, काष्ठा ib_srq_attr *srq_attr)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_modअगरy_srq *cmd;
	काष्ठा ocrdma_pd *pd = srq->pd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(pd->ibpd.device);

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_MODIFY_SRQ, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->id = srq->id;
	cmd->limit_max_rqe |= srq_attr->srq_limit <<
	    OCRDMA_MODIFY_SRQ_LIMIT_SHIFT;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	kमुक्त(cmd);
	वापस status;
पूर्ण

पूर्णांक ocrdma_mbx_query_srq(काष्ठा ocrdma_srq *srq, काष्ठा ib_srq_attr *srq_attr)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा ocrdma_query_srq *cmd;
	काष्ठा ocrdma_dev *dev = get_ocrdma_dev(srq->ibsrq.device);

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_QUERY_SRQ, माप(*cmd));
	अगर (!cmd)
		वापस status;
	cmd->id = srq->rq.dbid;
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (status == 0) अणु
		काष्ठा ocrdma_query_srq_rsp *rsp =
		    (काष्ठा ocrdma_query_srq_rsp *)cmd;
		srq_attr->max_sge =
		    rsp->srq_lmt_max_sge &
		    OCRDMA_QUERY_SRQ_RSP_MAX_SGE_RECV_MASK;
		srq_attr->max_wr =
		    rsp->max_rqe_pdid >> OCRDMA_QUERY_SRQ_RSP_MAX_RQE_SHIFT;
		srq_attr->srq_limit = rsp->srq_lmt_max_sge >>
		    OCRDMA_QUERY_SRQ_RSP_SRQ_LIMIT_SHIFT;
	पूर्ण
	kमुक्त(cmd);
	वापस status;
पूर्ण

व्योम ocrdma_mbx_destroy_srq(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_srq *srq)
अणु
	काष्ठा ocrdma_destroy_srq *cmd;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_DELETE_SRQ, माप(*cmd));
	अगर (!cmd)
		वापस;
	cmd->id = srq->id;
	ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);
	अगर (srq->rq.va)
		dma_मुक्त_coherent(&pdev->dev, srq->rq.len,
				  srq->rq.va, srq->rq.pa);
	kमुक्त(cmd);
पूर्ण

अटल पूर्णांक ocrdma_mbx_get_dcbx_config(काष्ठा ocrdma_dev *dev, u32 ptype,
				      काष्ठा ocrdma_dcbx_cfg *dcbxcfg)
अणु
	पूर्णांक status;
	dma_addr_t pa;
	काष्ठा ocrdma_mqe cmd;

	काष्ठा ocrdma_get_dcbx_cfg_req *req = शून्य;
	काष्ठा ocrdma_get_dcbx_cfg_rsp *rsp = शून्य;
	काष्ठा pci_dev *pdev = dev->nic_info.pdev;
	काष्ठा ocrdma_mqe_sge *mqe_sge = cmd.u.nonemb_req.sge;

	स_रखो(&cmd, 0, माप(काष्ठा ocrdma_mqe));
	cmd.hdr.pyld_len = max_t (u32, माप(काष्ठा ocrdma_get_dcbx_cfg_rsp),
					माप(काष्ठा ocrdma_get_dcbx_cfg_req));
	req = dma_alloc_coherent(&pdev->dev, cmd.hdr.pyld_len, &pa, GFP_KERNEL);
	अगर (!req) अणु
		status = -ENOMEM;
		जाओ mem_err;
	पूर्ण

	cmd.hdr.spcl_sge_cnt_emb |= (1 << OCRDMA_MQE_HDR_SGE_CNT_SHIFT) &
					OCRDMA_MQE_HDR_SGE_CNT_MASK;
	mqe_sge->pa_lo = (u32) (pa & 0xFFFFFFFFUL);
	mqe_sge->pa_hi = (u32) upper_32_bits(pa);
	mqe_sge->len = cmd.hdr.pyld_len;

	ocrdma_init_mch(&req->hdr, OCRDMA_CMD_GET_DCBX_CONFIG,
			OCRDMA_SUBSYS_DCBX, cmd.hdr.pyld_len);
	req->param_type = ptype;

	status = ocrdma_mbx_cmd(dev, &cmd);
	अगर (status)
		जाओ mbx_err;

	rsp = (काष्ठा ocrdma_get_dcbx_cfg_rsp *)req;
	ocrdma_le32_to_cpu(rsp, माप(काष्ठा ocrdma_get_dcbx_cfg_rsp));
	स_नकल(dcbxcfg, &rsp->cfg, माप(काष्ठा ocrdma_dcbx_cfg));

mbx_err:
	dma_मुक्त_coherent(&pdev->dev, cmd.hdr.pyld_len, req, pa);
mem_err:
	वापस status;
पूर्ण

#घोषणा OCRDMA_MAX_SERVICE_LEVEL_INDEX	0x08
#घोषणा OCRDMA_DEFAULT_SERVICE_LEVEL	0x05

अटल पूर्णांक ocrdma_parse_dcbxcfg_rsp(काष्ठा ocrdma_dev *dev, पूर्णांक ptype,
				    काष्ठा ocrdma_dcbx_cfg *dcbxcfg,
				    u8 *srvc_lvl)
अणु
	पूर्णांक status = -EINVAL, indx, slindx;
	पूर्णांक ventry_cnt;
	काष्ठा ocrdma_app_parameter *app_param;
	u8 valid, proto_sel;
	u8 app_prio, pfc_prio;
	u16 proto;

	अगर (!(dcbxcfg->tcv_aev_opv_st & OCRDMA_DCBX_STATE_MASK)) अणु
		pr_info("%s ocrdma%d DCBX is disabled\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
		जाओ out;
	पूर्ण

	अगर (!ocrdma_is_enabled_and_synced(dcbxcfg->pfc_state)) अणु
		pr_info("%s ocrdma%d priority flow control(%s) is %s%s\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id,
			(ptype > 0 ? "operational" : "admin"),
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_ENABLED) ?
			"enabled" : "disabled",
			(dcbxcfg->pfc_state & OCRDMA_STATE_FLAG_SYNC) ?
			"" : ", not sync'ed");
		जाओ out;
	पूर्ण अन्यथा अणु
		pr_info("%s ocrdma%d priority flow control is enabled and sync'ed\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
	पूर्ण

	ventry_cnt = (dcbxcfg->tcv_aev_opv_st >>
				OCRDMA_DCBX_APP_ENTRY_SHIFT)
				& OCRDMA_DCBX_STATE_MASK;

	क्रम (indx = 0; indx < ventry_cnt; indx++) अणु
		app_param = &dcbxcfg->app_param[indx];
		valid = (app_param->valid_proto_app >>
				OCRDMA_APP_PARAM_VALID_SHIFT)
				& OCRDMA_APP_PARAM_VALID_MASK;
		proto_sel = (app_param->valid_proto_app
				>>  OCRDMA_APP_PARAM_PROTO_SEL_SHIFT)
				& OCRDMA_APP_PARAM_PROTO_SEL_MASK;
		proto = app_param->valid_proto_app &
				OCRDMA_APP_PARAM_APP_PROTO_MASK;

		अगर (
			valid && proto == ETH_P_IBOE &&
			proto_sel == OCRDMA_PROTO_SELECT_L2) अणु
			क्रम (slindx = 0; slindx <
				OCRDMA_MAX_SERVICE_LEVEL_INDEX; slindx++) अणु
				app_prio = ocrdma_get_app_prio(
						(u8 *)app_param->app_prio,
						slindx);
				pfc_prio = ocrdma_get_pfc_prio(
						(u8 *)dcbxcfg->pfc_prio,
						slindx);

				अगर (app_prio && pfc_prio) अणु
					*srvc_lvl = slindx;
					status = 0;
					जाओ out;
				पूर्ण
			पूर्ण
			अगर (slindx == OCRDMA_MAX_SERVICE_LEVEL_INDEX) अणु
				pr_info("%s ocrdma%d application priority not set for 0x%x protocol\n",
					dev_name(&dev->nic_info.pdev->dev),
					dev->id, proto);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस status;
पूर्ण

व्योम ocrdma_init_service_level(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status = 0, indx;
	काष्ठा ocrdma_dcbx_cfg dcbxcfg;
	u8 srvc_lvl = OCRDMA_DEFAULT_SERVICE_LEVEL;
	पूर्णांक ptype = OCRDMA_PARAMETER_TYPE_OPER;

	क्रम (indx = 0; indx < 2; indx++) अणु
		status = ocrdma_mbx_get_dcbx_config(dev, ptype, &dcbxcfg);
		अगर (status) अणु
			pr_err("%s(): status=%d\n", __func__, status);
			ptype = OCRDMA_PARAMETER_TYPE_ADMIN;
			जारी;
		पूर्ण

		status = ocrdma_parse_dcbxcfg_rsp(dev, ptype,
						  &dcbxcfg, &srvc_lvl);
		अगर (status) अणु
			ptype = OCRDMA_PARAMETER_TYPE_ADMIN;
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (status)
		pr_info("%s ocrdma%d service level default\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id);
	अन्यथा
		pr_info("%s ocrdma%d service level %d\n",
			dev_name(&dev->nic_info.pdev->dev), dev->id,
			srvc_lvl);

	dev->pfc_state = ocrdma_is_enabled_and_synced(dcbxcfg.pfc_state);
	dev->sl = srvc_lvl;
पूर्ण

पूर्णांक ocrdma_alloc_av(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_ah *ah)
अणु
	पूर्णांक i;
	पूर्णांक status = -EINVAL;
	काष्ठा ocrdma_av *av;
	अचिन्हित दीर्घ flags;

	av = dev->av_tbl.va;
	spin_lock_irqsave(&dev->av_tbl.lock, flags);
	क्रम (i = 0; i < dev->av_tbl.num_ah; i++) अणु
		अगर (av->valid == 0) अणु
			av->valid = OCRDMA_AV_VALID;
			ah->av = av;
			ah->id = i;
			status = 0;
			अवरोध;
		पूर्ण
		av++;
	पूर्ण
	अगर (i == dev->av_tbl.num_ah)
		status = -EAGAIN;
	spin_unlock_irqrestore(&dev->av_tbl.lock, flags);
	वापस status;
पूर्ण

व्योम ocrdma_मुक्त_av(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_ah *ah)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&dev->av_tbl.lock, flags);
	ah->av->valid = 0;
	spin_unlock_irqrestore(&dev->av_tbl.lock, flags);
पूर्ण

अटल पूर्णांक ocrdma_create_eqs(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक num_eq, i, status = 0;
	पूर्णांक irq;
	अचिन्हित दीर्घ flags = 0;

	num_eq = dev->nic_info.msix.num_vectors -
			dev->nic_info.msix.start_vector;
	अगर (dev->nic_info.पूर्णांकr_mode == BE_INTERRUPT_MODE_INTX) अणु
		num_eq = 1;
		flags = IRQF_SHARED;
	पूर्ण अन्यथा अणु
		num_eq = min_t(u32, num_eq, num_online_cpus());
	पूर्ण

	अगर (!num_eq)
		वापस -EINVAL;

	dev->eq_tbl = kसुस्मृति(num_eq, माप(काष्ठा ocrdma_eq), GFP_KERNEL);
	अगर (!dev->eq_tbl)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_eq; i++) अणु
		status = ocrdma_create_eq(dev, &dev->eq_tbl[i],
					OCRDMA_EQ_LEN);
		अगर (status) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण
		प्र_लिखो(dev->eq_tbl[i].irq_name, "ocrdma%d-%d",
			dev->id, i);
		irq = ocrdma_get_irq(dev, &dev->eq_tbl[i]);
		status = request_irq(irq, ocrdma_irq_handler, flags,
				     dev->eq_tbl[i].irq_name,
				     &dev->eq_tbl[i]);
		अगर (status)
			जाओ करोne;
		dev->eq_cnt += 1;
	पूर्ण
	/* one eq is sufficient क्रम data path to work */
	वापस 0;
करोne:
	ocrdma_destroy_eqs(dev);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_mbx_modअगरy_eqd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq,
				 पूर्णांक num)
अणु
	पूर्णांक i, status;
	काष्ठा ocrdma_modअगरy_eqd_req *cmd;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_MODIFY_EQ_DELAY, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;

	ocrdma_init_mch(&cmd->cmd.req, OCRDMA_CMD_MODIFY_EQ_DELAY,
			OCRDMA_SUBSYS_COMMON, माप(*cmd));

	cmd->cmd.num_eq = num;
	क्रम (i = 0; i < num; i++) अणु
		cmd->cmd.set_eqd[i].eq_id = eq[i].q.id;
		cmd->cmd.set_eqd[i].phase = 0;
		cmd->cmd.set_eqd[i].delay_multiplier =
				(eq[i].aic_obj.prev_eqd * 65)/100;
	पूर्ण
	status = ocrdma_mbx_cmd(dev, (काष्ठा ocrdma_mqe *)cmd);

	kमुक्त(cmd);
	वापस status;
पूर्ण

अटल पूर्णांक ocrdma_modअगरy_eqd(काष्ठा ocrdma_dev *dev, काष्ठा ocrdma_eq *eq,
			     पूर्णांक num)
अणु
	पूर्णांक num_eqs, i = 0;
	अगर (num > 8) अणु
		जबतक (num) अणु
			num_eqs = min(num, 8);
			ocrdma_mbx_modअगरy_eqd(dev, &eq[i], num_eqs);
			i += num_eqs;
			num -= num_eqs;
		पूर्ण
	पूर्ण अन्यथा अणु
		ocrdma_mbx_modअगरy_eqd(dev, eq, num);
	पूर्ण
	वापस 0;
पूर्ण

व्योम ocrdma_eqd_set_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocrdma_dev *dev =
		container_of(work, काष्ठा ocrdma_dev, eqd_work.work);
	काष्ठा ocrdma_eq *eq = शून्य;
	पूर्णांक i, num = 0;
	u64 eq_पूर्णांकr;

	क्रम (i = 0; i < dev->eq_cnt; i++) अणु
		eq = &dev->eq_tbl[i];
		अगर (eq->aic_obj.eq_पूर्णांकr_cnt > eq->aic_obj.prev_eq_पूर्णांकr_cnt) अणु
			eq_पूर्णांकr = eq->aic_obj.eq_पूर्णांकr_cnt -
				  eq->aic_obj.prev_eq_पूर्णांकr_cnt;
			अगर ((eq_पूर्णांकr > EQ_INTR_PER_SEC_THRSH_HI) &&
			    (eq->aic_obj.prev_eqd == EQ_AIC_MIN_EQD)) अणु
				eq->aic_obj.prev_eqd = EQ_AIC_MAX_EQD;
				num++;
			पूर्ण अन्यथा अगर ((eq_पूर्णांकr < EQ_INTR_PER_SEC_THRSH_LOW) &&
				   (eq->aic_obj.prev_eqd == EQ_AIC_MAX_EQD)) अणु
				eq->aic_obj.prev_eqd = EQ_AIC_MIN_EQD;
				num++;
			पूर्ण
		पूर्ण
		eq->aic_obj.prev_eq_पूर्णांकr_cnt = eq->aic_obj.eq_पूर्णांकr_cnt;
	पूर्ण

	अगर (num)
		ocrdma_modअगरy_eqd(dev, &dev->eq_tbl[0], num);
	schedule_delayed_work(&dev->eqd_work, msecs_to_jअगरfies(1000));
पूर्ण

पूर्णांक ocrdma_init_hw(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक status;

	/* create the eqs  */
	status = ocrdma_create_eqs(dev);
	अगर (status)
		जाओ qpeq_err;
	status = ocrdma_create_mq(dev);
	अगर (status)
		जाओ mq_err;
	status = ocrdma_mbx_query_fw_config(dev);
	अगर (status)
		जाओ conf_err;
	status = ocrdma_mbx_query_dev(dev);
	अगर (status)
		जाओ conf_err;
	status = ocrdma_mbx_query_fw_ver(dev);
	अगर (status)
		जाओ conf_err;
	status = ocrdma_mbx_create_ah_tbl(dev);
	अगर (status)
		जाओ conf_err;
	status = ocrdma_mbx_get_phy_info(dev);
	अगर (status)
		जाओ info_attrb_err;
	status = ocrdma_mbx_get_ctrl_attribs(dev);
	अगर (status)
		जाओ info_attrb_err;

	वापस 0;

info_attrb_err:
	ocrdma_mbx_delete_ah_tbl(dev);
conf_err:
	ocrdma_destroy_mq(dev);
mq_err:
	ocrdma_destroy_eqs(dev);
qpeq_err:
	pr_err("%s() status=%d\n", __func__, status);
	वापस status;
पूर्ण

व्योम ocrdma_cleanup_hw(काष्ठा ocrdma_dev *dev)
अणु
	ocrdma_मुक्त_pd_pool(dev);
	ocrdma_mbx_delete_ah_tbl(dev);

	/* cleanup the control path */
	ocrdma_destroy_mq(dev);

	/* cleanup the eqs */
	ocrdma_destroy_eqs(dev);
पूर्ण
