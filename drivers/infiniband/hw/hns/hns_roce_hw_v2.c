<शैली गुरु>
/*
 * Copyright (c) 2016-2017 Hisilicon Limited.
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

#समावेश <linux/acpi.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <net/addrconf.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "hnae3.h"
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hem.h"
#समावेश "hns_roce_hw_v2.h"

क्रमागत अणु
	CMD_RST_PRC_OTHERS,
	CMD_RST_PRC_SUCCESS,
	CMD_RST_PRC_EBUSY,
पूर्ण;

अटल अंतरभूत व्योम set_data_seg_v2(काष्ठा hns_roce_v2_wqe_data_seg *dseg,
				   काष्ठा ib_sge *sg)
अणु
	dseg->lkey = cpu_to_le32(sg->lkey);
	dseg->addr = cpu_to_le64(sg->addr);
	dseg->len  = cpu_to_le32(sg->length);
पूर्ण

/*
 * mapped-value = 1 + real-value
 * The hns wr opcode real value is start from 0, In order to distinguish between
 * initialized and uninitialized map values, we plus 1 to the actual value when
 * defining the mapping, so that the validity can be identअगरied by checking the
 * mapped value is greater than 0.
 */
#घोषणा HR_OPC_MAP(ib_key, hr_key) \
		[IB_WR_ ## ib_key] = 1 + HNS_ROCE_V2_WQE_OP_ ## hr_key

अटल स्थिर u32 hns_roce_op_code[] = अणु
	HR_OPC_MAP(RDMA_WRITE,			RDMA_WRITE),
	HR_OPC_MAP(RDMA_WRITE_WITH_IMM,		RDMA_WRITE_WITH_IMM),
	HR_OPC_MAP(SEND,			SEND),
	HR_OPC_MAP(SEND_WITH_IMM,		SEND_WITH_IMM),
	HR_OPC_MAP(RDMA_READ,			RDMA_READ),
	HR_OPC_MAP(ATOMIC_CMP_AND_SWP,		ATOM_CMP_AND_SWAP),
	HR_OPC_MAP(ATOMIC_FETCH_AND_ADD,	ATOM_FETCH_AND_ADD),
	HR_OPC_MAP(SEND_WITH_INV,		SEND_WITH_INV),
	HR_OPC_MAP(LOCAL_INV,			LOCAL_INV),
	HR_OPC_MAP(MASKED_ATOMIC_CMP_AND_SWP,	ATOM_MSK_CMP_AND_SWAP),
	HR_OPC_MAP(MASKED_ATOMIC_FETCH_AND_ADD,	ATOM_MSK_FETCH_AND_ADD),
	HR_OPC_MAP(REG_MR,			FAST_REG_PMR),
पूर्ण;

अटल u32 to_hr_opcode(u32 ib_opcode)
अणु
	अगर (ib_opcode >= ARRAY_SIZE(hns_roce_op_code))
		वापस HNS_ROCE_V2_WQE_OP_MASK;

	वापस hns_roce_op_code[ib_opcode] ? hns_roce_op_code[ib_opcode] - 1 :
					     HNS_ROCE_V2_WQE_OP_MASK;
पूर्ण

अटल व्योम set_frmr_seg(काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe,
			 स्थिर काष्ठा ib_reg_wr *wr)
अणु
	काष्ठा hns_roce_wqe_frmr_seg *fseg =
		(व्योम *)rc_sq_wqe + माप(काष्ठा hns_roce_v2_rc_send_wqe);
	काष्ठा hns_roce_mr *mr = to_hr_mr(wr->mr);
	u64 pbl_ba;

	/* use ib_access_flags */
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_BIND_EN_S,
		     !!(wr->access & IB_ACCESS_MW_BIND));
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_ATOMIC_S,
		     !!(wr->access & IB_ACCESS_REMOTE_ATOMIC));
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_RR_S,
		     !!(wr->access & IB_ACCESS_REMOTE_READ));
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_RW_S,
		     !!(wr->access & IB_ACCESS_REMOTE_WRITE));
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_LW_S,
		     !!(wr->access & IB_ACCESS_LOCAL_WRITE));

	/* Data काष्ठाure reuse may lead to confusion */
	pbl_ba = mr->pbl_mtr.hem_cfg.root_ba;
	rc_sq_wqe->msg_len = cpu_to_le32(lower_32_bits(pbl_ba));
	rc_sq_wqe->inv_key = cpu_to_le32(upper_32_bits(pbl_ba));

	rc_sq_wqe->byte_16 = cpu_to_le32(wr->mr->length & 0xffffffff);
	rc_sq_wqe->byte_20 = cpu_to_le32(wr->mr->length >> 32);
	rc_sq_wqe->rkey = cpu_to_le32(wr->key);
	rc_sq_wqe->va = cpu_to_le64(wr->mr->iova);

	fseg->pbl_size = cpu_to_le32(mr->npages);
	roce_set_field(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_PBL_BUF_PG_SZ_M,
		       V2_RC_FRMR_WQE_BYTE_40_PBL_BUF_PG_SZ_S,
		       to_hr_hw_page_shअगरt(mr->pbl_mtr.hem_cfg.buf_pg_shअगरt));
	roce_set_bit(fseg->byte_40, V2_RC_FRMR_WQE_BYTE_40_BLK_MODE_S, 0);
पूर्ण

अटल व्योम set_atomic_seg(स्थिर काष्ठा ib_send_wr *wr,
			   काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe,
			   अचिन्हित पूर्णांक valid_num_sge)
अणु
	काष्ठा hns_roce_v2_wqe_data_seg *dseg =
		(व्योम *)rc_sq_wqe + माप(काष्ठा hns_roce_v2_rc_send_wqe);
	काष्ठा hns_roce_wqe_atomic_seg *aseg =
		(व्योम *)dseg + माप(काष्ठा hns_roce_v2_wqe_data_seg);

	set_data_seg_v2(dseg, wr->sg_list);

	अगर (wr->opcode == IB_WR_ATOMIC_CMP_AND_SWP) अणु
		aseg->fetchadd_swap_data = cpu_to_le64(atomic_wr(wr)->swap);
		aseg->cmp_data = cpu_to_le64(atomic_wr(wr)->compare_add);
	पूर्ण अन्यथा अणु
		aseg->fetchadd_swap_data =
			cpu_to_le64(atomic_wr(wr)->compare_add);
		aseg->cmp_data = 0;
	पूर्ण

	roce_set_field(rc_sq_wqe->byte_16, V2_RC_SEND_WQE_BYTE_16_SGE_NUM_M,
		       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_S, valid_num_sge);
पूर्ण

अटल पूर्णांक fill_ext_sge_inl_data(काष्ठा hns_roce_qp *qp,
				 स्थिर काष्ठा ib_send_wr *wr,
				 अचिन्हित पूर्णांक *sge_idx, u32 msg_len)
अणु
	काष्ठा ib_device *ibdev = &(to_hr_dev(qp->ibqp.device))->ib_dev;
	अचिन्हित पूर्णांक dseg_len = माप(काष्ठा hns_roce_v2_wqe_data_seg);
	अचिन्हित पूर्णांक ext_sge_sz = qp->sq.max_gs * dseg_len;
	अचिन्हित पूर्णांक left_len_in_pg;
	अचिन्हित पूर्णांक idx = *sge_idx;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक len;
	व्योम *addr;
	व्योम *dseg;

	अगर (msg_len > ext_sge_sz) अणु
		ibdev_err(ibdev,
			  "no enough extended sge space for inline data.\n");
		वापस -EINVAL;
	पूर्ण

	dseg = hns_roce_get_extend_sge(qp, idx & (qp->sge.sge_cnt - 1));
	left_len_in_pg = hr_hw_page_align((uपूर्णांकptr_t)dseg) - (uपूर्णांकptr_t)dseg;
	len = wr->sg_list[0].length;
	addr = (व्योम *)(अचिन्हित दीर्घ)(wr->sg_list[0].addr);

	/* When copying data to extended sge space, the left length in page may
	 * not दीर्घ enough क्रम current user's sge. So the data should be
	 * splited पूर्णांकo several parts, one in the first page, and the others in
	 * the subsequent pages.
	 */
	जबतक (1) अणु
		अगर (len <= left_len_in_pg) अणु
			स_नकल(dseg, addr, len);

			idx += len / dseg_len;

			i++;
			अगर (i >= wr->num_sge)
				अवरोध;

			left_len_in_pg -= len;
			len = wr->sg_list[i].length;
			addr = (व्योम *)(अचिन्हित दीर्घ)(wr->sg_list[i].addr);
			dseg += len;
		पूर्ण अन्यथा अणु
			स_नकल(dseg, addr, left_len_in_pg);

			len -= left_len_in_pg;
			addr += left_len_in_pg;
			idx += left_len_in_pg / dseg_len;
			dseg = hns_roce_get_extend_sge(qp,
						idx & (qp->sge.sge_cnt - 1));
			left_len_in_pg = 1 << HNS_HW_PAGE_SHIFT;
		पूर्ण
	पूर्ण

	*sge_idx = idx;

	वापस 0;
पूर्ण

अटल व्योम set_extend_sge(काष्ठा hns_roce_qp *qp, काष्ठा ib_sge *sge,
			   अचिन्हित पूर्णांक *sge_ind, अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा hns_roce_v2_wqe_data_seg *dseg;
	अचिन्हित पूर्णांक idx = *sge_ind;

	जबतक (cnt > 0) अणु
		dseg = hns_roce_get_extend_sge(qp, idx & (qp->sge.sge_cnt - 1));
		अगर (likely(sge->length)) अणु
			set_data_seg_v2(dseg, sge);
			idx++;
			cnt--;
		पूर्ण
		sge++;
	पूर्ण

	*sge_ind = idx;
पूर्ण

अटल bool check_inl_data_len(काष्ठा hns_roce_qp *qp, अचिन्हित पूर्णांक len)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(qp->ibqp.device);
	पूर्णांक mtu = ib_mtu_क्रमागत_to_पूर्णांक(qp->path_mtu);

	अगर (len > qp->max_अंतरभूत_data || len > mtu) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "invalid length of data, data len = %u, max inline len = %u, path mtu = %d.\n",
			  len, qp->max_अंतरभूत_data, mtu);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक set_rc_inl(काष्ठा hns_roce_qp *qp, स्थिर काष्ठा ib_send_wr *wr,
		      काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe,
		      अचिन्हित पूर्णांक *sge_idx)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(qp->ibqp.device);
	u32 msg_len = le32_to_cpu(rc_sq_wqe->msg_len);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	अचिन्हित पूर्णांक curr_idx = *sge_idx;
	व्योम *dseg = rc_sq_wqe;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (unlikely(wr->opcode == IB_WR_RDMA_READ)) अणु
		ibdev_err(ibdev, "invalid inline parameters!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!check_inl_data_len(qp, msg_len))
		वापस -EINVAL;

	dseg += माप(काष्ठा hns_roce_v2_rc_send_wqe);

	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_INLINE_S, 1);

	अगर (msg_len <= HNS_ROCE_V2_MAX_RC_INL_INN_SZ) अणु
		roce_set_bit(rc_sq_wqe->byte_20,
			     V2_RC_SEND_WQE_BYTE_20_INL_TYPE_S, 0);

		क्रम (i = 0; i < wr->num_sge; i++) अणु
			स_नकल(dseg, ((व्योम *)wr->sg_list[i].addr),
			       wr->sg_list[i].length);
			dseg += wr->sg_list[i].length;
		पूर्ण
	पूर्ण अन्यथा अणु
		roce_set_bit(rc_sq_wqe->byte_20,
			     V2_RC_SEND_WQE_BYTE_20_INL_TYPE_S, 1);

		ret = fill_ext_sge_inl_data(qp, wr, &curr_idx, msg_len);
		अगर (ret)
			वापस ret;

		roce_set_field(rc_sq_wqe->byte_16,
			       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_M,
			       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_S,
			       curr_idx - *sge_idx);
	पूर्ण

	*sge_idx = curr_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक set_rwqe_data_seg(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
			     काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe,
			     अचिन्हित पूर्णांक *sge_ind,
			     अचिन्हित पूर्णांक valid_num_sge)
अणु
	काष्ठा hns_roce_v2_wqe_data_seg *dseg =
		(व्योम *)rc_sq_wqe + माप(काष्ठा hns_roce_v2_rc_send_wqe);
	काष्ठा hns_roce_qp *qp = to_hr_qp(ibqp);
	पूर्णांक j = 0;
	पूर्णांक i;

	roce_set_field(rc_sq_wqe->byte_20,
		       V2_RC_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_M,
		       V2_RC_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_S,
		       (*sge_ind) & (qp->sge.sge_cnt - 1));

	अगर (wr->send_flags & IB_SEND_INLINE)
		वापस set_rc_inl(qp, wr, rc_sq_wqe, sge_ind);

	अगर (valid_num_sge <= HNS_ROCE_SGE_IN_WQE) अणु
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			अगर (likely(wr->sg_list[i].length)) अणु
				set_data_seg_v2(dseg, wr->sg_list + i);
				dseg++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < wr->num_sge && j < HNS_ROCE_SGE_IN_WQE; i++) अणु
			अगर (likely(wr->sg_list[i].length)) अणु
				set_data_seg_v2(dseg, wr->sg_list + i);
				dseg++;
				j++;
			पूर्ण
		पूर्ण

		set_extend_sge(qp, wr->sg_list + i, sge_ind,
			       valid_num_sge - HNS_ROCE_SGE_IN_WQE);
	पूर्ण

	roce_set_field(rc_sq_wqe->byte_16,
		       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_M,
		       V2_RC_SEND_WQE_BYTE_16_SGE_NUM_S, valid_num_sge);

	वापस 0;
पूर्ण

अटल पूर्णांक check_send_valid(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा ib_qp *ibqp = &hr_qp->ibqp;

	अगर (unlikely(ibqp->qp_type != IB_QPT_RC &&
		     ibqp->qp_type != IB_QPT_GSI &&
		     ibqp->qp_type != IB_QPT_UD)) अणु
		ibdev_err(ibdev, "Not supported QP(0x%x)type!\n",
			  ibqp->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (unlikely(hr_qp->state == IB_QPS_RESET ||
		   hr_qp->state == IB_QPS_INIT ||
		   hr_qp->state == IB_QPS_RTR)) अणु
		ibdev_err(ibdev, "failed to post WQE, QP state %u!\n",
			  hr_qp->state);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (unlikely(hr_dev->state >= HNS_ROCE_DEVICE_STATE_RST_DOWN)) अणु
		ibdev_err(ibdev, "failed to post WQE, dev state %d!\n",
			  hr_dev->state);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक calc_wr_sge_num(स्थिर काष्ठा ib_send_wr *wr,
				    अचिन्हित पूर्णांक *sge_len)
अणु
	अचिन्हित पूर्णांक valid_num = 0;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < wr->num_sge; i++) अणु
		अगर (likely(wr->sg_list[i].length)) अणु
			len += wr->sg_list[i].length;
			valid_num++;
		पूर्ण
	पूर्ण

	*sge_len = len;
	वापस valid_num;
पूर्ण

अटल __le32 get_immtdata(स्थिर काष्ठा ib_send_wr *wr)
अणु
	चयन (wr->opcode) अणु
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		वापस cpu_to_le32(be32_to_cpu(wr->ex.imm_data));
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक set_ud_opcode(काष्ठा hns_roce_v2_ud_send_wqe *ud_sq_wqe,
			 स्थिर काष्ठा ib_send_wr *wr)
अणु
	u32 ib_op = wr->opcode;

	अगर (ib_op != IB_WR_SEND && ib_op != IB_WR_SEND_WITH_IMM)
		वापस -EINVAL;

	ud_sq_wqe->immtdata = get_immtdata(wr);

	roce_set_field(ud_sq_wqe->byte_4, V2_UD_SEND_WQE_BYTE_4_OPCODE_M,
		       V2_UD_SEND_WQE_BYTE_4_OPCODE_S, to_hr_opcode(ib_op));

	वापस 0;
पूर्ण

अटल पूर्णांक fill_ud_av(काष्ठा hns_roce_v2_ud_send_wqe *ud_sq_wqe,
		      काष्ठा hns_roce_ah *ah)
अणु
	काष्ठा ib_device *ib_dev = ah->ibah.device;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_dev);

	roce_set_field(ud_sq_wqe->byte_24, V2_UD_SEND_WQE_BYTE_24_UDPSPN_M,
		       V2_UD_SEND_WQE_BYTE_24_UDPSPN_S, ah->av.udp_sport);

	roce_set_field(ud_sq_wqe->byte_36, V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_M,
		       V2_UD_SEND_WQE_BYTE_36_HOPLIMIT_S, ah->av.hop_limit);
	roce_set_field(ud_sq_wqe->byte_36, V2_UD_SEND_WQE_BYTE_36_TCLASS_M,
		       V2_UD_SEND_WQE_BYTE_36_TCLASS_S, ah->av.tclass);
	roce_set_field(ud_sq_wqe->byte_40, V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_M,
		       V2_UD_SEND_WQE_BYTE_40_FLOW_LABEL_S, ah->av.flowlabel);

	अगर (WARN_ON(ah->av.sl > MAX_SERVICE_LEVEL))
		वापस -EINVAL;

	roce_set_field(ud_sq_wqe->byte_40, V2_UD_SEND_WQE_BYTE_40_SL_M,
		       V2_UD_SEND_WQE_BYTE_40_SL_S, ah->av.sl);

	ud_sq_wqe->sgid_index = ah->av.gid_index;

	स_नकल(ud_sq_wqe->dmac, ah->av.mac, ETH_ALEN);
	स_नकल(ud_sq_wqe->dgid, ah->av.dgid, GID_LEN_V2);

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
		वापस 0;

	roce_set_bit(ud_sq_wqe->byte_40, V2_UD_SEND_WQE_BYTE_40_UD_VLAN_EN_S,
		     ah->av.vlan_en);
	roce_set_field(ud_sq_wqe->byte_36, V2_UD_SEND_WQE_BYTE_36_VLAN_M,
		       V2_UD_SEND_WQE_BYTE_36_VLAN_S, ah->av.vlan_id);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_ud_wqe(काष्ठा hns_roce_qp *qp,
			     स्थिर काष्ठा ib_send_wr *wr,
			     व्योम *wqe, अचिन्हित पूर्णांक *sge_idx,
			     अचिन्हित पूर्णांक owner_bit)
अणु
	काष्ठा hns_roce_ah *ah = to_hr_ah(ud_wr(wr)->ah);
	काष्ठा hns_roce_v2_ud_send_wqe *ud_sq_wqe = wqe;
	अचिन्हित पूर्णांक curr_idx = *sge_idx;
	अचिन्हित पूर्णांक valid_num_sge;
	u32 msg_len = 0;
	पूर्णांक ret;

	valid_num_sge = calc_wr_sge_num(wr, &msg_len);

	ret = set_ud_opcode(ud_sq_wqe, wr);
	अगर (WARN_ON(ret))
		वापस ret;

	ud_sq_wqe->msg_len = cpu_to_le32(msg_len);

	roce_set_bit(ud_sq_wqe->byte_4, V2_UD_SEND_WQE_BYTE_4_CQE_S,
		     !!(wr->send_flags & IB_SEND_SIGNALED));

	roce_set_bit(ud_sq_wqe->byte_4, V2_UD_SEND_WQE_BYTE_4_SE_S,
		     !!(wr->send_flags & IB_SEND_SOLICITED));

	roce_set_field(ud_sq_wqe->byte_16, V2_UD_SEND_WQE_BYTE_16_PD_M,
		       V2_UD_SEND_WQE_BYTE_16_PD_S, to_hr_pd(qp->ibqp.pd)->pdn);

	roce_set_field(ud_sq_wqe->byte_16, V2_UD_SEND_WQE_BYTE_16_SGE_NUM_M,
		       V2_UD_SEND_WQE_BYTE_16_SGE_NUM_S, valid_num_sge);

	roce_set_field(ud_sq_wqe->byte_20,
		       V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_M,
		       V2_UD_SEND_WQE_BYTE_20_MSG_START_SGE_IDX_S,
		       curr_idx & (qp->sge.sge_cnt - 1));

	ud_sq_wqe->qkey = cpu_to_le32(ud_wr(wr)->remote_qkey & 0x80000000 ?
			  qp->qkey : ud_wr(wr)->remote_qkey);
	roce_set_field(ud_sq_wqe->byte_32, V2_UD_SEND_WQE_BYTE_32_DQPN_M,
		       V2_UD_SEND_WQE_BYTE_32_DQPN_S, ud_wr(wr)->remote_qpn);

	ret = fill_ud_av(ud_sq_wqe, ah);
	अगर (ret)
		वापस ret;

	qp->sl = to_hr_ah(ud_wr(wr)->ah)->av.sl;

	set_extend_sge(qp, wr->sg_list, &curr_idx, valid_num_sge);

	/*
	 * The pipeline can sequentially post all valid WQEs पूर्णांकo WQ buffer,
	 * including new WQEs रुकोing क्रम the करोorbell to update the PI again.
	 * Thereक्रमe, the owner bit of WQE MUST be updated after all fields
	 * and extSGEs have been written पूर्णांकo DDR instead of cache.
	 */
	अगर (qp->en_flags & HNS_ROCE_QP_CAP_OWNER_DB)
		dma_wmb();

	*sge_idx = curr_idx;
	roce_set_bit(ud_sq_wqe->byte_4, V2_UD_SEND_WQE_BYTE_4_OWNER_S,
		     owner_bit);

	वापस 0;
पूर्ण

अटल पूर्णांक set_rc_opcode(काष्ठा hns_roce_dev *hr_dev,
			 काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe,
			 स्थिर काष्ठा ib_send_wr *wr)
अणु
	u32 ib_op = wr->opcode;
	पूर्णांक ret = 0;

	rc_sq_wqe->immtdata = get_immtdata(wr);

	चयन (ib_op) अणु
	हाल IB_WR_RDMA_READ:
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		rc_sq_wqe->rkey = cpu_to_le32(rdma_wr(wr)->rkey);
		rc_sq_wqe->va = cpu_to_le64(rdma_wr(wr)->remote_addr);
		अवरोध;
	हाल IB_WR_SEND:
	हाल IB_WR_SEND_WITH_IMM:
		अवरोध;
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		rc_sq_wqe->rkey = cpu_to_le32(atomic_wr(wr)->rkey);
		rc_sq_wqe->va = cpu_to_le64(atomic_wr(wr)->remote_addr);
		अवरोध;
	हाल IB_WR_REG_MR:
		अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
			set_frmr_seg(rc_sq_wqe, reg_wr(wr));
		अन्यथा
			ret = -EOPNOTSUPP;
		अवरोध;
	हाल IB_WR_LOCAL_INV:
		roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_SO_S, 1);
		fallthrough;
	हाल IB_WR_SEND_WITH_INV:
		rc_sq_wqe->inv_key = cpu_to_le32(wr->ex.invalidate_rkey);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (unlikely(ret))
		वापस ret;

	roce_set_field(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_OPCODE_M,
		       V2_RC_SEND_WQE_BYTE_4_OPCODE_S, to_hr_opcode(ib_op));

	वापस ret;
पूर्ण
अटल अंतरभूत पूर्णांक set_rc_wqe(काष्ठा hns_roce_qp *qp,
			     स्थिर काष्ठा ib_send_wr *wr,
			     व्योम *wqe, अचिन्हित पूर्णांक *sge_idx,
			     अचिन्हित पूर्णांक owner_bit)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(qp->ibqp.device);
	काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe = wqe;
	अचिन्हित पूर्णांक curr_idx = *sge_idx;
	अचिन्हित पूर्णांक valid_num_sge;
	u32 msg_len = 0;
	पूर्णांक ret;

	valid_num_sge = calc_wr_sge_num(wr, &msg_len);

	rc_sq_wqe->msg_len = cpu_to_le32(msg_len);

	ret = set_rc_opcode(hr_dev, rc_sq_wqe, wr);
	अगर (WARN_ON(ret))
		वापस ret;

	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_FENCE_S,
		     (wr->send_flags & IB_SEND_FENCE) ? 1 : 0);

	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_SE_S,
		     (wr->send_flags & IB_SEND_SOLICITED) ? 1 : 0);

	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_CQE_S,
		     (wr->send_flags & IB_SEND_SIGNALED) ? 1 : 0);

	अगर (wr->opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
	    wr->opcode == IB_WR_ATOMIC_FETCH_AND_ADD)
		set_atomic_seg(wr, rc_sq_wqe, valid_num_sge);
	अन्यथा अगर (wr->opcode != IB_WR_REG_MR)
		ret = set_rwqe_data_seg(&qp->ibqp, wr, rc_sq_wqe,
					&curr_idx, valid_num_sge);

	/*
	 * The pipeline can sequentially post all valid WQEs पूर्णांकo WQ buffer,
	 * including new WQEs रुकोing क्रम the करोorbell to update the PI again.
	 * Thereक्रमe, the owner bit of WQE MUST be updated after all fields
	 * and extSGEs have been written पूर्णांकo DDR instead of cache.
	 */
	अगर (qp->en_flags & HNS_ROCE_QP_CAP_OWNER_DB)
		dma_wmb();

	*sge_idx = curr_idx;
	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_OWNER_S,
		     owner_bit);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम update_sq_db(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_qp *qp)
अणु
	/*
	 * Hip08 hardware cannot flush the WQEs in SQ अगर the QP state
	 * माला_लो पूर्णांकo errored mode. Hence, as a workaround to this
	 * hardware limitation, driver needs to assist in flushing. But
	 * the flushing operation uses mailbox to convey the QP state to
	 * the hardware and which can sleep due to the mutex protection
	 * around the mailbox calls. Hence, use the deferred flush क्रम
	 * now.
	 */
	अगर (unlikely(qp->state == IB_QPS_ERR)) अणु
		अगर (!test_and_set_bit(HNS_ROCE_FLUSH_FLAG, &qp->flush_flag))
			init_flush_work(hr_dev, qp);
	पूर्ण अन्यथा अणु
		काष्ठा hns_roce_v2_db sq_db = अणुपूर्ण;

		roce_set_field(sq_db.byte_4, V2_DB_TAG_M, V2_DB_TAG_S,
			       qp->करोorbell_qpn);
		roce_set_field(sq_db.byte_4, V2_DB_CMD_M, V2_DB_CMD_S,
			       HNS_ROCE_V2_SQ_DB);

		/* indicates data on new BAR, 0 : SQ करोorbell, 1 : DWQE */
		roce_set_bit(sq_db.byte_4, V2_DB_FLAG_S, 0);
		roce_set_field(sq_db.parameter, V2_DB_PRODUCER_IDX_M,
			       V2_DB_PRODUCER_IDX_S, qp->sq.head);
		roce_set_field(sq_db.parameter, V2_DB_SL_M, V2_DB_SL_S,
			       qp->sl);

		hns_roce_ग_लिखो64(hr_dev, (__le32 *)&sq_db, qp->sq.db_reg);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_rq_db(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_qp *qp)
अणु
	/*
	 * Hip08 hardware cannot flush the WQEs in RQ अगर the QP state
	 * माला_लो पूर्णांकo errored mode. Hence, as a workaround to this
	 * hardware limitation, driver needs to assist in flushing. But
	 * the flushing operation uses mailbox to convey the QP state to
	 * the hardware and which can sleep due to the mutex protection
	 * around the mailbox calls. Hence, use the deferred flush क्रम
	 * now.
	 */
	अगर (unlikely(qp->state == IB_QPS_ERR)) अणु
		अगर (!test_and_set_bit(HNS_ROCE_FLUSH_FLAG, &qp->flush_flag))
			init_flush_work(hr_dev, qp);
	पूर्ण अन्यथा अणु
		अगर (likely(qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)) अणु
			*qp->rdb.db_record =
					qp->rq.head & V2_DB_PRODUCER_IDX_M;
		पूर्ण अन्यथा अणु
			काष्ठा hns_roce_v2_db rq_db = अणुपूर्ण;

			roce_set_field(rq_db.byte_4, V2_DB_TAG_M, V2_DB_TAG_S,
				       qp->qpn);
			roce_set_field(rq_db.byte_4, V2_DB_CMD_M, V2_DB_CMD_S,
				       HNS_ROCE_V2_RQ_DB);
			roce_set_field(rq_db.parameter, V2_DB_PRODUCER_IDX_M,
				       V2_DB_PRODUCER_IDX_S, qp->rq.head);

			hns_roce_ग_लिखो64(hr_dev, (__le32 *)&rq_db,
					 qp->rq.db_reg);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hns_roce_ग_लिखो512(काष्ठा hns_roce_dev *hr_dev, u64 *val,
			      u64 __iomem *dest)
अणु
#घोषणा HNS_ROCE_WRITE_TIMES 8
	काष्ठा hns_roce_v2_priv *priv = (काष्ठा hns_roce_v2_priv *)hr_dev->priv;
	काष्ठा hnae3_handle *handle = priv->handle;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	पूर्णांक i;

	अगर (!hr_dev->dis_db && !ops->get_hw_reset_stat(handle))
		क्रम (i = 0; i < HNS_ROCE_WRITE_TIMES; i++)
			ग_लिखोq_relaxed(*(val + i), dest + i);
पूर्ण

अटल व्योम ग_लिखो_dwqe(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *qp,
		       व्योम *wqe)
अणु
	काष्ठा hns_roce_v2_rc_send_wqe *rc_sq_wqe = wqe;

	/* All kinds of DirectWQE have the same header field layout */
	roce_set_bit(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_FLAG_S, 1);
	roce_set_field(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_DB_SL_L_M,
		       V2_RC_SEND_WQE_BYTE_4_DB_SL_L_S, qp->sl);
	roce_set_field(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_DB_SL_H_M,
		       V2_RC_SEND_WQE_BYTE_4_DB_SL_H_S, qp->sl >> 2);
	roce_set_field(rc_sq_wqe->byte_4, V2_RC_SEND_WQE_BYTE_4_WQE_INDEX_M,
		       V2_RC_SEND_WQE_BYTE_4_WQE_INDEX_S, qp->sq.head);

	hns_roce_ग_लिखो512(hr_dev, wqe, qp->sq.db_reg);
पूर्ण

अटल पूर्णांक hns_roce_v2_post_send(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_send_wr *wr,
				 स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_qp *qp = to_hr_qp(ibqp);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक owner_bit;
	अचिन्हित पूर्णांक sge_idx;
	अचिन्हित पूर्णांक wqe_idx;
	व्योम *wqe = शून्य;
	u32 nreq;
	पूर्णांक ret;

	spin_lock_irqsave(&qp->sq.lock, flags);

	ret = check_send_valid(hr_dev, qp);
	अगर (unlikely(ret)) अणु
		*bad_wr = wr;
		nreq = 0;
		जाओ out;
	पूर्ण

	sge_idx = qp->next_sge;

	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (hns_roce_wq_overflow(&qp->sq, nreq, qp->ibqp.send_cq)) अणु
			ret = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe_idx = (qp->sq.head + nreq) & (qp->sq.wqe_cnt - 1);

		अगर (unlikely(wr->num_sge > qp->sq.max_gs)) अणु
			ibdev_err(ibdev, "num_sge = %d > qp->sq.max_gs = %u.\n",
				  wr->num_sge, qp->sq.max_gs);
			ret = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe = hns_roce_get_send_wqe(qp, wqe_idx);
		qp->sq.wrid[wqe_idx] = wr->wr_id;
		owner_bit =
		       ~(((qp->sq.head + nreq) >> ilog2(qp->sq.wqe_cnt)) & 0x1);

		/* Corresponding to the QP type, wqe process separately */
		अगर (ibqp->qp_type == IB_QPT_GSI || ibqp->qp_type == IB_QPT_UD)
			ret = set_ud_wqe(qp, wr, wqe, &sge_idx, owner_bit);
		अन्यथा अगर (ibqp->qp_type == IB_QPT_RC)
			ret = set_rc_wqe(qp, wr, wqe, &sge_idx, owner_bit);

		अगर (unlikely(ret)) अणु
			*bad_wr = wr;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		qp->sq.head += nreq;
		qp->next_sge = sge_idx;

		अगर (nreq == 1 && qp->sq.head == qp->sq.tail + 1 &&
		    (qp->en_flags & HNS_ROCE_QP_CAP_सूचीECT_WQE))
			ग_लिखो_dwqe(hr_dev, qp, wqe);
		अन्यथा
			update_sq_db(hr_dev, qp);
	पूर्ण

	spin_unlock_irqrestore(&qp->sq.lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक check_recv_valid(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा ib_qp *ibqp = &hr_qp->ibqp;

	अगर (unlikely(ibqp->qp_type != IB_QPT_RC &&
		     ibqp->qp_type != IB_QPT_GSI &&
		     ibqp->qp_type != IB_QPT_UD)) अणु
		ibdev_err(ibdev, "unsupported qp type, qp_type = %d.\n",
			  ibqp->qp_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (unlikely(hr_dev->state >= HNS_ROCE_DEVICE_STATE_RST_DOWN))
		वापस -EIO;

	अगर (hr_qp->state == IB_QPS_RESET)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम fill_recv_sge_to_wqe(स्थिर काष्ठा ib_recv_wr *wr, व्योम *wqe,
				 u32 max_sge, bool rsv)
अणु
	काष्ठा hns_roce_v2_wqe_data_seg *dseg = wqe;
	u32 i, cnt;

	क्रम (i = 0, cnt = 0; i < wr->num_sge; i++) अणु
		/* Skip zero-length sge */
		अगर (!wr->sg_list[i].length)
			जारी;
		set_data_seg_v2(dseg + cnt, wr->sg_list + i);
		cnt++;
	पूर्ण

	/* Fill a reserved sge to make hw stop पढ़ोing reमुख्यing segments */
	अगर (rsv) अणु
		dseg[cnt].lkey = cpu_to_le32(HNS_ROCE_INVALID_LKEY);
		dseg[cnt].addr = 0;
		dseg[cnt].len = cpu_to_le32(HNS_ROCE_INVALID_SGE_LENGTH);
	पूर्ण अन्यथा अणु
		/* Clear reमुख्यing segments to make ROCEE ignore sges */
		अगर (cnt < max_sge)
			स_रखो(dseg + cnt, 0,
			       (max_sge - cnt) * HNS_ROCE_SGE_SIZE);
	पूर्ण
पूर्ण

अटल व्योम fill_rq_wqe(काष्ठा hns_roce_qp *hr_qp, स्थिर काष्ठा ib_recv_wr *wr,
			u32 wqe_idx, u32 max_sge)
अणु
	काष्ठा hns_roce_rinl_sge *sge_list;
	व्योम *wqe = शून्य;
	u32 i;

	wqe = hns_roce_get_recv_wqe(hr_qp, wqe_idx);
	fill_recv_sge_to_wqe(wr, wqe, max_sge, hr_qp->rq.rsv_sge);

	/* rq support अंतरभूत data */
	अगर (hr_qp->rq_inl_buf.wqe_cnt) अणु
		sge_list = hr_qp->rq_inl_buf.wqe_list[wqe_idx].sg_list;
		hr_qp->rq_inl_buf.wqe_list[wqe_idx].sge_cnt = (u32)wr->num_sge;
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			sge_list[i].addr = (व्योम *)(u64)wr->sg_list[i].addr;
			sge_list[i].len = wr->sg_list[i].length;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_v2_post_recv(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_recv_wr *wr,
				 स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u32 wqe_idx, nreq, max_sge;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&hr_qp->rq.lock, flags);

	ret = check_recv_valid(hr_dev, hr_qp);
	अगर (unlikely(ret)) अणु
		*bad_wr = wr;
		nreq = 0;
		जाओ out;
	पूर्ण

	max_sge = hr_qp->rq.max_gs - hr_qp->rq.rsv_sge;
	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		अगर (unlikely(hns_roce_wq_overflow(&hr_qp->rq, nreq,
						  hr_qp->ibqp.recv_cq))) अणु
			ret = -ENOMEM;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		अगर (unlikely(wr->num_sge > max_sge)) अणु
			ibdev_err(ibdev, "num_sge = %d >= max_sge = %u.\n",
				  wr->num_sge, max_sge);
			ret = -EINVAL;
			*bad_wr = wr;
			जाओ out;
		पूर्ण

		wqe_idx = (hr_qp->rq.head + nreq) & (hr_qp->rq.wqe_cnt - 1);
		fill_rq_wqe(hr_qp, wr, wqe_idx, max_sge);
		hr_qp->rq.wrid[wqe_idx] = wr->wr_id;
	पूर्ण

out:
	अगर (likely(nreq)) अणु
		hr_qp->rq.head += nreq;

		update_rq_db(hr_dev, hr_qp);
	पूर्ण
	spin_unlock_irqrestore(&hr_qp->rq.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम *get_srq_wqe_buf(काष्ठा hns_roce_srq *srq, u32 n)
अणु
	वापस hns_roce_buf_offset(srq->buf_mtr.kmem, n << srq->wqe_shअगरt);
पूर्ण

अटल व्योम *get_idx_buf(काष्ठा hns_roce_idx_que *idx_que, u32 n)
अणु
	वापस hns_roce_buf_offset(idx_que->mtr.kmem,
				   n << idx_que->entry_shअगरt);
पूर्ण

अटल व्योम hns_roce_मुक्त_srq_wqe(काष्ठा hns_roce_srq *srq, u32 wqe_index)
अणु
	/* always called with पूर्णांकerrupts disabled. */
	spin_lock(&srq->lock);

	biपंचांगap_clear(srq->idx_que.biपंचांगap, wqe_index, 1);
	srq->idx_que.tail++;

	spin_unlock(&srq->lock);
पूर्ण

अटल पूर्णांक hns_roce_srqwq_overflow(काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;

	वापस idx_que->head - idx_que->tail >= srq->wqe_cnt;
पूर्ण

अटल पूर्णांक check_post_srq_valid(काष्ठा hns_roce_srq *srq, u32 max_sge,
				स्थिर काष्ठा ib_recv_wr *wr)
अणु
	काष्ठा ib_device *ib_dev = srq->ibsrq.device;

	अगर (unlikely(wr->num_sge > max_sge)) अणु
		ibdev_err(ib_dev,
			  "failed to check sge, wr->num_sge = %d, max_sge = %u.\n",
			  wr->num_sge, max_sge);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(hns_roce_srqwq_overflow(srq))) अणु
		ibdev_err(ib_dev,
			  "failed to check srqwq status, srqwq is full.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_srq_wqe_idx(काष्ठा hns_roce_srq *srq, u32 *wqe_idx)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;
	u32 pos;

	pos = find_first_zero_bit(idx_que->biपंचांगap, srq->wqe_cnt);
	अगर (unlikely(pos == srq->wqe_cnt))
		वापस -ENOSPC;

	biपंचांगap_set(idx_que->biपंचांगap, pos, 1);
	*wqe_idx = pos;
	वापस 0;
पूर्ण

अटल व्योम fill_wqe_idx(काष्ठा hns_roce_srq *srq, अचिन्हित पूर्णांक wqe_idx)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;
	अचिन्हित पूर्णांक head;
	__le32 *buf;

	head = idx_que->head & (srq->wqe_cnt - 1);

	buf = get_idx_buf(idx_que, head);
	*buf = cpu_to_le32(wqe_idx);

	idx_que->head++;
पूर्ण

अटल पूर्णांक hns_roce_v2_post_srq_recv(काष्ठा ib_srq *ibsrq,
				     स्थिर काष्ठा ib_recv_wr *wr,
				     स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	काष्ठा hns_roce_srq *srq = to_hr_srq(ibsrq);
	काष्ठा hns_roce_v2_db srq_db;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 max_sge;
	u32 wqe_idx;
	व्योम *wqe;
	u32 nreq;

	spin_lock_irqsave(&srq->lock, flags);

	max_sge = srq->max_gs - srq->rsv_sge;
	क्रम (nreq = 0; wr; ++nreq, wr = wr->next) अणु
		ret = check_post_srq_valid(srq, max_sge, wr);
		अगर (ret) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		ret = get_srq_wqe_idx(srq, &wqe_idx);
		अगर (unlikely(ret)) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		wqe = get_srq_wqe_buf(srq, wqe_idx);
		fill_recv_sge_to_wqe(wr, wqe, max_sge, srq->rsv_sge);
		fill_wqe_idx(srq, wqe_idx);
		srq->wrid[wqe_idx] = wr->wr_id;
	पूर्ण

	अगर (likely(nreq)) अणु
		roce_set_field(srq_db.byte_4, V2_DB_TAG_M, V2_DB_TAG_S,
			       srq->srqn);
		roce_set_field(srq_db.byte_4, V2_DB_CMD_M, V2_DB_CMD_S,
			       HNS_ROCE_V2_SRQ_DB);
		roce_set_field(srq_db.parameter, V2_DB_PRODUCER_IDX_M,
			       V2_DB_PRODUCER_IDX_S, srq->idx_que.head);

		hns_roce_ग_लिखो64(hr_dev, (__le32 *)&srq_db, srq->db_reg);
	पूर्ण

	spin_unlock_irqrestore(&srq->lock, flags);

	वापस ret;
पूर्ण

अटल u32 hns_roce_v2_cmd_hw_reseted(काष्ठा hns_roce_dev *hr_dev,
				      अचिन्हित दीर्घ instance_stage,
				      अचिन्हित दीर्घ reset_stage)
अणु
	/* When hardware reset has been completed once or more, we should stop
	 * sending mailbox&cmq&करोorbell to hardware. If now in .init_instance()
	 * function, we should निकास with error. If now at HNAE3_INIT_CLIENT
	 * stage of soft reset process, we should निकास with error, and then
	 * HNAE3_INIT_CLIENT related process can rollback the operation like
	 * notअगरing hardware to मुक्त resources, HNAE3_INIT_CLIENT related
	 * process will निकास with error to notअगरy NIC driver to reschedule soft
	 * reset process once again.
	 */
	hr_dev->is_reset = true;
	hr_dev->dis_db = true;

	अगर (reset_stage == HNS_ROCE_STATE_RST_INIT ||
	    instance_stage == HNS_ROCE_STATE_INIT)
		वापस CMD_RST_PRC_EBUSY;

	वापस CMD_RST_PRC_SUCCESS;
पूर्ण

अटल u32 hns_roce_v2_cmd_hw_resetting(काष्ठा hns_roce_dev *hr_dev,
					अचिन्हित दीर्घ instance_stage,
					अचिन्हित दीर्घ reset_stage)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hnae3_handle *handle = priv->handle;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	/* When hardware reset is detected, we should stop sending mailbox&cmq&
	 * करोorbell to hardware. If now in .init_instance() function, we should
	 * निकास with error. If now at HNAE3_INIT_CLIENT stage of soft reset
	 * process, we should निकास with error, and then HNAE3_INIT_CLIENT
	 * related process can rollback the operation like notअगरing hardware to
	 * मुक्त resources, HNAE3_INIT_CLIENT related process will निकास with
	 * error to notअगरy NIC driver to reschedule soft reset process once
	 * again.
	 */
	hr_dev->dis_db = true;
	अगर (!ops->get_hw_reset_stat(handle))
		hr_dev->is_reset = true;

	अगर (!hr_dev->is_reset || reset_stage == HNS_ROCE_STATE_RST_INIT ||
	    instance_stage == HNS_ROCE_STATE_INIT)
		वापस CMD_RST_PRC_EBUSY;

	वापस CMD_RST_PRC_SUCCESS;
पूर्ण

अटल u32 hns_roce_v2_cmd_sw_resetting(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hnae3_handle *handle = priv->handle;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	/* When software reset is detected at .init_instance() function, we
	 * should stop sending mailbox&cmq&करोorbell to hardware, and निकास
	 * with error.
	 */
	hr_dev->dis_db = true;
	अगर (ops->ae_dev_reset_cnt(handle) != hr_dev->reset_cnt)
		hr_dev->is_reset = true;

	वापस CMD_RST_PRC_EBUSY;
पूर्ण

अटल u32 check_aedev_reset_status(काष्ठा hns_roce_dev *hr_dev,
				    काष्ठा hnae3_handle *handle)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	अचिन्हित दीर्घ instance_stage; /* the current instance stage */
	अचिन्हित दीर्घ reset_stage; /* the current reset stage */
	अचिन्हित दीर्घ reset_cnt;
	bool sw_resetting;
	bool hw_resetting;

	/* Get inक्रमmation about reset from NIC driver or RoCE driver itself,
	 * the meaning of the following variables from NIC driver are described
	 * as below:
	 * reset_cnt -- The count value of completed hardware reset.
	 * hw_resetting -- Whether hardware device is resetting now.
	 * sw_resetting -- Whether NIC's software reset process is running now.
	 */
	instance_stage = handle->rinfo.instance_state;
	reset_stage = handle->rinfo.reset_state;
	reset_cnt = ops->ae_dev_reset_cnt(handle);
	अगर (reset_cnt != hr_dev->reset_cnt)
		वापस hns_roce_v2_cmd_hw_reseted(hr_dev, instance_stage,
						  reset_stage);

	hw_resetting = ops->get_cmdq_stat(handle);
	अगर (hw_resetting)
		वापस hns_roce_v2_cmd_hw_resetting(hr_dev, instance_stage,
						    reset_stage);

	sw_resetting = ops->ae_dev_resetting(handle);
	अगर (sw_resetting && instance_stage == HNS_ROCE_STATE_INIT)
		वापस hns_roce_v2_cmd_sw_resetting(hr_dev);

	वापस CMD_RST_PRC_OTHERS;
पूर्ण

अटल bool check_device_is_in_reset(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hnae3_handle *handle = priv->handle;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	अगर (hr_dev->reset_cnt != ops->ae_dev_reset_cnt(handle))
		वापस true;

	अगर (ops->get_hw_reset_stat(handle))
		वापस true;

	अगर (ops->ae_dev_resetting(handle))
		वापस true;

	वापस false;
पूर्ण

अटल bool v2_chk_mbox_is_avail(काष्ठा hns_roce_dev *hr_dev, bool *busy)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	u32 status;

	अगर (hr_dev->is_reset)
		status = CMD_RST_PRC_SUCCESS;
	अन्यथा
		status = check_aedev_reset_status(hr_dev, priv->handle);

	*busy = (status == CMD_RST_PRC_EBUSY);

	वापस status == CMD_RST_PRC_OTHERS;
पूर्ण

अटल पूर्णांक hns_roce_alloc_cmq_desc(काष्ठा hns_roce_dev *hr_dev,
				   काष्ठा hns_roce_v2_cmq_ring *ring)
अणु
	पूर्णांक size = ring->desc_num * माप(काष्ठा hns_roce_cmq_desc);

	ring->desc = kzalloc(size, GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	ring->desc_dma_addr = dma_map_single(hr_dev->dev, ring->desc, size,
					     DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(hr_dev->dev, ring->desc_dma_addr)) अणु
		ring->desc_dma_addr = 0;
		kमुक्त(ring->desc);
		ring->desc = शून्य;

		dev_err_ratelimited(hr_dev->dev,
				    "failed to map cmq desc addr.\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_roce_मुक्त_cmq_desc(काष्ठा hns_roce_dev *hr_dev,
				   काष्ठा hns_roce_v2_cmq_ring *ring)
अणु
	dma_unmap_single(hr_dev->dev, ring->desc_dma_addr,
			 ring->desc_num * माप(काष्ठा hns_roce_cmq_desc),
			 DMA_BIसूचीECTIONAL);

	ring->desc_dma_addr = 0;
	kमुक्त(ring->desc);
पूर्ण

अटल पूर्णांक hns_roce_init_cmq_ring(काष्ठा hns_roce_dev *hr_dev, bool ring_type)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_v2_cmq_ring *ring = (ring_type == TYPE_CSQ) ?
					    &priv->cmq.csq : &priv->cmq.crq;

	ring->flag = ring_type;
	ring->head = 0;

	वापस hns_roce_alloc_cmq_desc(hr_dev, ring);
पूर्ण

अटल व्योम hns_roce_cmq_init_regs(काष्ठा hns_roce_dev *hr_dev, bool ring_type)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_v2_cmq_ring *ring = (ring_type == TYPE_CSQ) ?
					    &priv->cmq.csq : &priv->cmq.crq;
	dma_addr_t dma = ring->desc_dma_addr;

	अगर (ring_type == TYPE_CSQ) अणु
		roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_BASEADDR_L_REG, (u32)dma);
		roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_BASEADDR_H_REG,
			   upper_32_bits(dma));
		roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_DEPTH_REG,
			   (u32)ring->desc_num >> HNS_ROCE_CMQ_DESC_NUM_S);

		/* Make sure to ग_लिखो tail first and then head */
		roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_TAIL_REG, 0);
		roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_HEAD_REG, 0);
	पूर्ण अन्यथा अणु
		roce_ग_लिखो(hr_dev, ROCEE_RX_CMQ_BASEADDR_L_REG, (u32)dma);
		roce_ग_लिखो(hr_dev, ROCEE_RX_CMQ_BASEADDR_H_REG,
			   upper_32_bits(dma));
		roce_ग_लिखो(hr_dev, ROCEE_RX_CMQ_DEPTH_REG,
			   (u32)ring->desc_num >> HNS_ROCE_CMQ_DESC_NUM_S);
		roce_ग_लिखो(hr_dev, ROCEE_RX_CMQ_HEAD_REG, 0);
		roce_ग_लिखो(hr_dev, ROCEE_RX_CMQ_TAIL_REG, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_v2_cmq_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	पूर्णांक ret;

	/* Setup the queue entries क्रम command queue */
	priv->cmq.csq.desc_num = CMD_CSQ_DESC_NUM;
	priv->cmq.crq.desc_num = CMD_CRQ_DESC_NUM;

	/* Setup the lock क्रम command queue */
	spin_lock_init(&priv->cmq.csq.lock);
	spin_lock_init(&priv->cmq.crq.lock);

	/* Setup Tx ग_लिखो back समयout */
	priv->cmq.tx_समयout = HNS_ROCE_CMQ_TX_TIMEOUT;

	/* Init CSQ */
	ret = hns_roce_init_cmq_ring(hr_dev, TYPE_CSQ);
	अगर (ret) अणु
		dev_err_ratelimited(hr_dev->dev,
				    "failed to init CSQ, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/* Init CRQ */
	ret = hns_roce_init_cmq_ring(hr_dev, TYPE_CRQ);
	अगर (ret) अणु
		dev_err_ratelimited(hr_dev->dev,
				    "failed to init CRQ, ret = %d.\n", ret);
		जाओ err_crq;
	पूर्ण

	/* Init CSQ REG */
	hns_roce_cmq_init_regs(hr_dev, TYPE_CSQ);

	/* Init CRQ REG */
	hns_roce_cmq_init_regs(hr_dev, TYPE_CRQ);

	वापस 0;

err_crq:
	hns_roce_मुक्त_cmq_desc(hr_dev, &priv->cmq.csq);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_v2_cmq_निकास(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;

	hns_roce_मुक्त_cmq_desc(hr_dev, &priv->cmq.csq);
	hns_roce_मुक्त_cmq_desc(hr_dev, &priv->cmq.crq);
पूर्ण

अटल व्योम hns_roce_cmq_setup_basic_desc(काष्ठा hns_roce_cmq_desc *desc,
					  क्रमागत hns_roce_opcode_type opcode,
					  bool is_पढ़ो)
अणु
	स_रखो((व्योम *)desc, 0, माप(काष्ठा hns_roce_cmq_desc));
	desc->opcode = cpu_to_le16(opcode);
	desc->flag =
		cpu_to_le16(HNS_ROCE_CMD_FLAG_NO_INTR | HNS_ROCE_CMD_FLAG_IN);
	अगर (is_पढ़ो)
		desc->flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_WR);
	अन्यथा
		desc->flag &= cpu_to_le16(~HNS_ROCE_CMD_FLAG_WR);
पूर्ण

अटल पूर्णांक hns_roce_cmq_csq_करोne(काष्ठा hns_roce_dev *hr_dev)
अणु
	u32 tail = roce_पढ़ो(hr_dev, ROCEE_TX_CMQ_TAIL_REG);
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;

	वापस tail == priv->cmq.csq.head;
पूर्ण

अटल पूर्णांक __hns_roce_cmq_send(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_cmq_desc *desc, पूर्णांक num)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_v2_cmq_ring *csq = &priv->cmq.csq;
	u32 समयout = 0;
	u16 desc_ret;
	u32 tail;
	पूर्णांक ret;
	पूर्णांक i;

	spin_lock_bh(&csq->lock);

	tail = csq->head;

	क्रम (i = 0; i < num; i++) अणु
		csq->desc[csq->head++] = desc[i];
		अगर (csq->head == csq->desc_num)
			csq->head = 0;
	पूर्ण

	/* Write to hardware */
	roce_ग_लिखो(hr_dev, ROCEE_TX_CMQ_HEAD_REG, csq->head);

	/* If the command is sync, रुको क्रम the firmware to ग_लिखो back,
	 * अगर multi descriptors to be sent, use the first one to check
	 */
	अगर (le16_to_cpu(desc->flag) & HNS_ROCE_CMD_FLAG_NO_INTR) अणु
		करो अणु
			अगर (hns_roce_cmq_csq_करोne(hr_dev))
				अवरोध;
			udelay(1);
		पूर्ण जबतक (++समयout < priv->cmq.tx_समयout);
	पूर्ण

	अगर (hns_roce_cmq_csq_करोne(hr_dev)) अणु
		क्रम (ret = 0, i = 0; i < num; i++) अणु
			/* check the result of hardware ग_लिखो back */
			desc[i] = csq->desc[tail++];
			अगर (tail == csq->desc_num)
				tail = 0;

			desc_ret = le16_to_cpu(desc[i].retval);
			अगर (likely(desc_ret == CMD_EXEC_SUCCESS))
				जारी;

			dev_err_ratelimited(hr_dev->dev,
					    "Cmdq IO error, opcode = %x, return = %x\n",
					    desc->opcode, desc_ret);
			ret = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* FW/HW reset or incorrect number of desc */
		tail = roce_पढ़ो(hr_dev, ROCEE_TX_CMQ_TAIL_REG);
		dev_warn(hr_dev->dev, "CMDQ move tail from %d to %d\n",
			 csq->head, tail);
		csq->head = tail;

		ret = -EAGAIN;
	पूर्ण

	spin_unlock_bh(&csq->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_cmq_send(काष्ठा hns_roce_dev *hr_dev,
			     काष्ठा hns_roce_cmq_desc *desc, पूर्णांक num)
अणु
	bool busy;
	पूर्णांक ret;

	अगर (!v2_chk_mbox_is_avail(hr_dev, &busy))
		वापस busy ? -EBUSY : 0;

	ret = __hns_roce_cmq_send(hr_dev, desc, num);
	अगर (ret) अणु
		अगर (!v2_chk_mbox_is_avail(hr_dev, &busy))
			वापस busy ? -EBUSY : 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक config_hem_ba_to_hw(काष्ठा hns_roce_dev *hr_dev, अचिन्हित दीर्घ obj,
			       dma_addr_t base_addr, u16 op)
अणु
	काष्ठा hns_roce_cmd_mailbox *mbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	पूर्णांक ret;

	अगर (IS_ERR(mbox))
		वापस PTR_ERR(mbox);

	ret = hns_roce_cmd_mbox(hr_dev, base_addr, mbox->dma, obj, 0, op,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mbox);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_cmq_query_hw_info(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_query_version *resp;
	काष्ठा hns_roce_cmq_desc desc;
	पूर्णांक ret;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_QUERY_HW_VER, true);
	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret)
		वापस ret;

	resp = (काष्ठा hns_roce_query_version *)desc.data;
	hr_dev->hw_rev = le16_to_cpu(resp->rocee_hw_version);
	hr_dev->venकरोr_id = hr_dev->pci_dev->venकरोr;

	वापस 0;
पूर्ण

अटल व्योम func_clr_hw_resetting_state(काष्ठा hns_roce_dev *hr_dev,
					काष्ठा hnae3_handle *handle)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	अचिन्हित दीर्घ end;

	hr_dev->dis_db = true;

	dev_warn(hr_dev->dev,
		 "Func clear is pending, device in resetting state.\n");
	end = HNS_ROCE_V2_HW_RST_TIMEOUT;
	जबतक (end) अणु
		अगर (!ops->get_hw_reset_stat(handle)) अणु
			hr_dev->is_reset = true;
			dev_info(hr_dev->dev,
				 "Func clear success after reset.\n");
			वापस;
		पूर्ण
		msleep(HNS_ROCE_V2_HW_RST_COMPLETION_WAIT);
		end -= HNS_ROCE_V2_HW_RST_COMPLETION_WAIT;
	पूर्ण

	dev_warn(hr_dev->dev, "Func clear failed.\n");
पूर्ण

अटल व्योम func_clr_sw_resetting_state(काष्ठा hns_roce_dev *hr_dev,
					काष्ठा hnae3_handle *handle)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	अचिन्हित दीर्घ end;

	hr_dev->dis_db = true;

	dev_warn(hr_dev->dev,
		 "Func clear is pending, device in resetting state.\n");
	end = HNS_ROCE_V2_HW_RST_TIMEOUT;
	जबतक (end) अणु
		अगर (ops->ae_dev_reset_cnt(handle) !=
		    hr_dev->reset_cnt) अणु
			hr_dev->is_reset = true;
			dev_info(hr_dev->dev,
				 "Func clear success after sw reset\n");
			वापस;
		पूर्ण
		msleep(HNS_ROCE_V2_HW_RST_COMPLETION_WAIT);
		end -= HNS_ROCE_V2_HW_RST_COMPLETION_WAIT;
	पूर्ण

	dev_warn(hr_dev->dev, "Func clear failed because of unfinished sw reset\n");
पूर्ण

अटल व्योम hns_roce_func_clr_rst_proc(काष्ठा hns_roce_dev *hr_dev, पूर्णांक retval,
				       पूर्णांक flag)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hnae3_handle *handle = priv->handle;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;

	अगर (ops->ae_dev_reset_cnt(handle) != hr_dev->reset_cnt) अणु
		hr_dev->dis_db = true;
		hr_dev->is_reset = true;
		dev_info(hr_dev->dev, "Func clear success after reset.\n");
		वापस;
	पूर्ण

	अगर (ops->get_hw_reset_stat(handle)) अणु
		func_clr_hw_resetting_state(hr_dev, handle);
		वापस;
	पूर्ण

	अगर (ops->ae_dev_resetting(handle) &&
	    handle->rinfo.instance_state == HNS_ROCE_STATE_INIT) अणु
		func_clr_sw_resetting_state(hr_dev, handle);
		वापस;
	पूर्ण

	अगर (retval && !flag)
		dev_warn(hr_dev->dev,
			 "Func clear read failed, ret = %d.\n", retval);

	dev_warn(hr_dev->dev, "Func clear failed.\n");
पूर्ण

अटल व्योम __hns_roce_function_clear(काष्ठा hns_roce_dev *hr_dev, पूर्णांक vf_id)
अणु
	bool fclr_ग_लिखो_fail_flag = false;
	काष्ठा hns_roce_func_clear *resp;
	काष्ठा hns_roce_cmq_desc desc;
	अचिन्हित दीर्घ end;
	पूर्णांक ret = 0;

	अगर (check_device_is_in_reset(hr_dev))
		जाओ out;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_FUNC_CLEAR, false);
	resp = (काष्ठा hns_roce_func_clear *)desc.data;
	resp->rst_funcid_en = cpu_to_le32(vf_id);

	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret) अणु
		fclr_ग_लिखो_fail_flag = true;
		dev_err(hr_dev->dev, "Func clear write failed, ret = %d.\n",
			 ret);
		जाओ out;
	पूर्ण

	msleep(HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_INTERVAL);
	end = HNS_ROCE_V2_FUNC_CLEAR_TIMEOUT_MSECS;
	जबतक (end) अणु
		अगर (check_device_is_in_reset(hr_dev))
			जाओ out;
		msleep(HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_FAIL_WAIT);
		end -= HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_FAIL_WAIT;

		hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_FUNC_CLEAR,
					      true);

		resp->rst_funcid_en = cpu_to_le32(vf_id);
		ret = hns_roce_cmq_send(hr_dev, &desc, 1);
		अगर (ret)
			जारी;

		अगर (roce_get_bit(resp->func_करोne, FUNC_CLEAR_RST_FUN_DONE_S)) अणु
			अगर (vf_id == 0)
				hr_dev->is_reset = true;
			वापस;
		पूर्ण
	पूर्ण

out:
	hns_roce_func_clr_rst_proc(hr_dev, ret, fclr_ग_लिखो_fail_flag);
पूर्ण

अटल व्योम hns_roce_मुक्त_vf_resource(काष्ठा hns_roce_dev *hr_dev, पूर्णांक vf_id)
अणु
	क्रमागत hns_roce_opcode_type opcode = HNS_ROCE_OPC_ALLOC_VF_RES;
	काष्ठा hns_roce_cmq_desc desc[2];
	काष्ठा hns_roce_cmq_req *req_a;

	req_a = (काष्ठा hns_roce_cmq_req *)desc[0].data;
	hns_roce_cmq_setup_basic_desc(&desc[0], opcode, false);
	desc[0].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);
	hns_roce_cmq_setup_basic_desc(&desc[1], opcode, false);
	hr_reg_ग_लिखो(req_a, FUNC_RES_A_VF_ID, vf_id);
	hns_roce_cmq_send(hr_dev, desc, 2);
पूर्ण

अटल व्योम hns_roce_function_clear(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक i;

	क्रम (i = hr_dev->func_num - 1; i >= 0; i--) अणु
		__hns_roce_function_clear(hr_dev, i);
		अगर (i != 0)
			hns_roce_मुक्त_vf_resource(hr_dev, i);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_roce_query_fw_ver(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_query_fw_info *resp;
	काष्ठा hns_roce_cmq_desc desc;
	पूर्णांक ret;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_QUERY_FW_VER, true);
	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret)
		वापस ret;

	resp = (काष्ठा hns_roce_query_fw_info *)desc.data;
	hr_dev->caps.fw_ver = (u64)(le32_to_cpu(resp->fw_ver));

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_query_func_info(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	पूर्णांक ret;

	अगर (hr_dev->pci_dev->revision < PCI_REVISION_ID_HIP09) अणु
		hr_dev->func_num = 1;
		वापस 0;
	पूर्ण

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_QUERY_FUNC_INFO,
				      true);
	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret) अणु
		hr_dev->func_num = 1;
		वापस ret;
	पूर्ण

	hr_dev->func_num = le32_to_cpu(desc.func_info.own_func_num);
	hr_dev->cong_algo_पंचांगpl_id = le32_to_cpu(desc.func_info.own_mac_id);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_config_global_param(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cmq_req *req = (काष्ठा hns_roce_cmq_req *)desc.data;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_GLOBAL_PARAM,
				      false);

	hr_reg_ग_लिखो(req, CFG_GLOBAL_PARAM_1US_CYCLES, 0x3e8);
	hr_reg_ग_लिखो(req, CFG_GLOBAL_PARAM_UDP_PORT, ROCE_V2_UDP_DPORT);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक load_func_res_caps(काष्ठा hns_roce_dev *hr_dev, bool is_vf)
अणु
	काष्ठा hns_roce_cmq_desc desc[2];
	काष्ठा hns_roce_cmq_req *r_a = (काष्ठा hns_roce_cmq_req *)desc[0].data;
	काष्ठा hns_roce_cmq_req *r_b = (काष्ठा hns_roce_cmq_req *)desc[1].data;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	क्रमागत hns_roce_opcode_type opcode;
	u32 func_num;
	पूर्णांक ret;

	अगर (is_vf) अणु
		opcode = HNS_ROCE_OPC_QUERY_VF_RES;
		func_num = 1;
	पूर्ण अन्यथा अणु
		opcode = HNS_ROCE_OPC_QUERY_PF_RES;
		func_num = hr_dev->func_num;
	पूर्ण

	hns_roce_cmq_setup_basic_desc(&desc[0], opcode, true);
	desc[0].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);
	hns_roce_cmq_setup_basic_desc(&desc[1], opcode, true);

	ret = hns_roce_cmq_send(hr_dev, desc, 2);
	अगर (ret)
		वापस ret;

	caps->qpc_bt_num = hr_reg_पढ़ो(r_a, FUNC_RES_A_QPC_BT_NUM) / func_num;
	caps->srqc_bt_num = hr_reg_पढ़ो(r_a, FUNC_RES_A_SRQC_BT_NUM) / func_num;
	caps->cqc_bt_num = hr_reg_पढ़ो(r_a, FUNC_RES_A_CQC_BT_NUM) / func_num;
	caps->mpt_bt_num = hr_reg_पढ़ो(r_a, FUNC_RES_A_MPT_BT_NUM) / func_num;
	caps->eqc_bt_num = hr_reg_पढ़ो(r_a, FUNC_RES_A_EQC_BT_NUM) / func_num;
	caps->smac_bt_num = hr_reg_पढ़ो(r_b, FUNC_RES_B_SMAC_NUM) / func_num;
	caps->sgid_bt_num = hr_reg_पढ़ो(r_b, FUNC_RES_B_SGID_NUM) / func_num;
	caps->sccc_bt_num = hr_reg_पढ़ो(r_b, FUNC_RES_B_SCCC_BT_NUM) / func_num;

	अगर (is_vf) अणु
		caps->sl_num = hr_reg_पढ़ो(r_b, FUNC_RES_V_QID_NUM) / func_num;
		caps->gmv_bt_num = hr_reg_पढ़ो(r_b, FUNC_RES_V_GMV_BT_NUM) /
					       func_num;
	पूर्ण अन्यथा अणु
		caps->sl_num = hr_reg_पढ़ो(r_b, FUNC_RES_B_QID_NUM) / func_num;
		caps->gmv_bt_num = hr_reg_पढ़ो(r_b, FUNC_RES_B_GMV_BT_NUM) /
					       func_num;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_query_pf_resource(काष्ठा hns_roce_dev *hr_dev)
अणु
	वापस load_func_res_caps(hr_dev, false);
पूर्ण

अटल पूर्णांक hns_roce_query_vf_resource(काष्ठा hns_roce_dev *hr_dev)
अणु
	वापस load_func_res_caps(hr_dev, true);
पूर्ण

अटल पूर्णांक hns_roce_query_pf_समयr_resource(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cmq_req *req = (काष्ठा hns_roce_cmq_req *)desc.data;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	पूर्णांक ret;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_QUERY_PF_TIMER_RES,
				      true);

	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret)
		वापस ret;

	caps->qpc_समयr_bt_num = hr_reg_पढ़ो(req, PF_TIMER_RES_QPC_ITEM_NUM);
	caps->cqc_समयr_bt_num = hr_reg_पढ़ो(req, PF_TIMER_RES_CQC_ITEM_NUM);

	वापस 0;
पूर्ण

अटल पूर्णांक __hns_roce_set_vf_चयन_param(काष्ठा hns_roce_dev *hr_dev,
					  u32 vf_id)
अणु
	काष्ठा hns_roce_vf_चयन *swt;
	काष्ठा hns_roce_cmq_desc desc;
	पूर्णांक ret;

	swt = (काष्ठा hns_roce_vf_चयन *)desc.data;
	hns_roce_cmq_setup_basic_desc(&desc, HNS_SWITCH_PARAMETER_CFG, true);
	swt->rocee_sel |= cpu_to_le32(HNS_ICL_SWITCH_CMD_ROCEE_SEL);
	roce_set_field(swt->fun_id, VF_SWITCH_DATA_FUN_ID_VF_ID_M,
		       VF_SWITCH_DATA_FUN_ID_VF_ID_S, vf_id);
	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret)
		वापस ret;

	desc.flag =
		cpu_to_le16(HNS_ROCE_CMD_FLAG_NO_INTR | HNS_ROCE_CMD_FLAG_IN);
	desc.flag &= cpu_to_le16(~HNS_ROCE_CMD_FLAG_WR);
	roce_set_bit(swt->cfg, VF_SWITCH_DATA_CFG_ALW_LPBK_S, 1);
	roce_set_bit(swt->cfg, VF_SWITCH_DATA_CFG_ALW_LCL_LPBK_S, 0);
	roce_set_bit(swt->cfg, VF_SWITCH_DATA_CFG_ALW_DST_OVRD_S, 1);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक hns_roce_set_vf_चयन_param(काष्ठा hns_roce_dev *hr_dev)
अणु
	u32 vf_id;
	पूर्णांक ret;

	क्रम (vf_id = 0; vf_id < hr_dev->func_num; vf_id++) अणु
		ret = __hns_roce_set_vf_चयन_param(hr_dev, vf_id);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __hns_roce_alloc_vf_resource(काष्ठा hns_roce_dev *hr_dev, पूर्णांक vf_id)
अणु
	काष्ठा hns_roce_cmq_desc desc[2];
	काष्ठा hns_roce_cmq_req *r_a = (काष्ठा hns_roce_cmq_req *)desc[0].data;
	काष्ठा hns_roce_cmq_req *r_b = (काष्ठा hns_roce_cmq_req *)desc[1].data;
	क्रमागत hns_roce_opcode_type opcode = HNS_ROCE_OPC_ALLOC_VF_RES;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;

	hns_roce_cmq_setup_basic_desc(&desc[0], opcode, false);
	desc[0].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);
	hns_roce_cmq_setup_basic_desc(&desc[1], opcode, false);

	hr_reg_ग_लिखो(r_a, FUNC_RES_A_VF_ID, vf_id);

	hr_reg_ग_लिखो(r_a, FUNC_RES_A_QPC_BT_NUM, caps->qpc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_QPC_BT_IDX, vf_id * caps->qpc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_SRQC_BT_NUM, caps->srqc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_SRQC_BT_IDX, vf_id * caps->srqc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_CQC_BT_NUM, caps->cqc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_CQC_BT_IDX, vf_id * caps->cqc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_MPT_BT_NUM, caps->mpt_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_MPT_BT_IDX, vf_id * caps->mpt_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_EQC_BT_NUM, caps->eqc_bt_num);
	hr_reg_ग_लिखो(r_a, FUNC_RES_A_EQC_BT_IDX, vf_id * caps->eqc_bt_num);
	hr_reg_ग_लिखो(r_b, FUNC_RES_V_QID_NUM, caps->sl_num);
	hr_reg_ग_लिखो(r_b, FUNC_RES_B_QID_IDX, vf_id * caps->sl_num);
	hr_reg_ग_लिखो(r_b, FUNC_RES_B_SCCC_BT_NUM, caps->sccc_bt_num);
	hr_reg_ग_लिखो(r_b, FUNC_RES_B_SCCC_BT_IDX, vf_id * caps->sccc_bt_num);

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09) अणु
		hr_reg_ग_लिखो(r_b, FUNC_RES_V_GMV_BT_NUM, caps->gmv_bt_num);
		hr_reg_ग_लिखो(r_b, FUNC_RES_B_GMV_BT_IDX,
			     vf_id * caps->gmv_bt_num);
	पूर्ण अन्यथा अणु
		hr_reg_ग_लिखो(r_b, FUNC_RES_B_SGID_NUM, caps->sgid_bt_num);
		hr_reg_ग_लिखो(r_b, FUNC_RES_B_SGID_IDX,
			     vf_id * caps->sgid_bt_num);
		hr_reg_ग_लिखो(r_b, FUNC_RES_B_SMAC_NUM, caps->smac_bt_num);
		hr_reg_ग_लिखो(r_b, FUNC_RES_B_SMAC_IDX,
			     vf_id * caps->smac_bt_num);
	पूर्ण

	वापस hns_roce_cmq_send(hr_dev, desc, 2);
पूर्ण

अटल पूर्णांक hns_roce_alloc_vf_resource(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक vf_id;
	पूर्णांक ret;

	क्रम (vf_id = 0; vf_id < hr_dev->func_num; vf_id++) अणु
		ret = __hns_roce_alloc_vf_resource(hr_dev, vf_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_set_bt(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cmq_req *req = (काष्ठा hns_roce_cmq_req *)desc.data;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_BT_ATTR, false);

	hr_reg_ग_लिखो(req, CFG_BT_ATTR_QPC_BA_PGSZ,
		     caps->qpc_ba_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_QPC_BUF_PGSZ,
		     caps->qpc_buf_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_QPC_HOPNUM,
		     to_hr_hem_hopnum(caps->qpc_hop_num, caps->num_qps));

	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SRQC_BA_PGSZ,
		     caps->srqc_ba_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SRQC_BUF_PGSZ,
		     caps->srqc_buf_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SRQC_HOPNUM,
		     to_hr_hem_hopnum(caps->srqc_hop_num, caps->num_srqs));

	hr_reg_ग_लिखो(req, CFG_BT_ATTR_CQC_BA_PGSZ,
		     caps->cqc_ba_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_CQC_BUF_PGSZ,
		     caps->cqc_buf_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_CQC_HOPNUM,
		     to_hr_hem_hopnum(caps->cqc_hop_num, caps->num_cqs));

	hr_reg_ग_लिखो(req, CFG_BT_ATTR_MPT_BA_PGSZ,
		     caps->mpt_ba_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_MPT_BUF_PGSZ,
		     caps->mpt_buf_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_MPT_HOPNUM,
		     to_hr_hem_hopnum(caps->mpt_hop_num, caps->num_mtpts));

	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SCCC_BA_PGSZ,
		     caps->sccc_ba_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SCCC_BUF_PGSZ,
		     caps->sccc_buf_pg_sz + PG_SHIFT_OFFSET);
	hr_reg_ग_लिखो(req, CFG_BT_ATTR_SCCC_HOPNUM,
		     to_hr_hem_hopnum(caps->sccc_hop_num, caps->num_qps));

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल व्योम set_शेष_caps(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;

	caps->num_qps		= HNS_ROCE_V2_MAX_QP_NUM;
	caps->max_wqes		= HNS_ROCE_V2_MAX_WQE_NUM;
	caps->num_cqs		= HNS_ROCE_V2_MAX_CQ_NUM;
	caps->num_srqs		= HNS_ROCE_V2_MAX_SRQ_NUM;
	caps->min_cqes		= HNS_ROCE_MIN_CQE_NUM;
	caps->max_cqes		= HNS_ROCE_V2_MAX_CQE_NUM;
	caps->max_sq_sg		= HNS_ROCE_V2_MAX_SQ_SGE_NUM;
	caps->max_extend_sg	= HNS_ROCE_V2_MAX_EXTEND_SGE_NUM;
	caps->max_rq_sg		= HNS_ROCE_V2_MAX_RQ_SGE_NUM;
	caps->num_uars		= HNS_ROCE_V2_UAR_NUM;
	caps->phy_num_uars	= HNS_ROCE_V2_PHY_UAR_NUM;
	caps->num_aeq_vectors	= HNS_ROCE_V2_AEQE_VEC_NUM;
	caps->num_comp_vectors	=
			min_t(u32, caps->eqc_bt_num - 1,
			      (u32)priv->handle->rinfo.num_vectors - 2);
	caps->num_other_vectors = HNS_ROCE_V2_ABNORMAL_VEC_NUM;
	caps->num_mtpts		= HNS_ROCE_V2_MAX_MTPT_NUM;
	caps->num_mtt_segs	= HNS_ROCE_V2_MAX_MTT_SEGS;
	caps->num_srqwqe_segs	= HNS_ROCE_V2_MAX_SRQWQE_SEGS;
	caps->num_idx_segs	= HNS_ROCE_V2_MAX_IDX_SEGS;
	caps->num_pds		= HNS_ROCE_V2_MAX_PD_NUM;
	caps->num_xrcds		= HNS_ROCE_V2_MAX_XRCD_NUM;
	caps->max_qp_init_rdma	= HNS_ROCE_V2_MAX_QP_INIT_RDMA;
	caps->max_qp_dest_rdma	= HNS_ROCE_V2_MAX_QP_DEST_RDMA;
	caps->max_sq_desc_sz	= HNS_ROCE_V2_MAX_SQ_DESC_SZ;
	caps->max_rq_desc_sz	= HNS_ROCE_V2_MAX_RQ_DESC_SZ;
	caps->max_srq_desc_sz	= HNS_ROCE_V2_MAX_SRQ_DESC_SZ;
	caps->irrl_entry_sz	= HNS_ROCE_V2_IRRL_ENTRY_SZ;
	caps->trrl_entry_sz	= HNS_ROCE_V2_EXT_ATOMIC_TRRL_ENTRY_SZ;
	caps->cqc_entry_sz	= HNS_ROCE_V2_CQC_ENTRY_SZ;
	caps->srqc_entry_sz	= HNS_ROCE_V2_SRQC_ENTRY_SZ;
	caps->mtpt_entry_sz	= HNS_ROCE_V2_MTPT_ENTRY_SZ;
	caps->mtt_entry_sz	= HNS_ROCE_V2_MTT_ENTRY_SZ;
	caps->idx_entry_sz	= HNS_ROCE_V2_IDX_ENTRY_SZ;
	caps->page_size_cap	= HNS_ROCE_V2_PAGE_SIZE_SUPPORTED;
	caps->reserved_lkey	= 0;
	caps->reserved_pds	= 0;
	caps->reserved_xrcds	= HNS_ROCE_V2_RSV_XRCD_NUM;
	caps->reserved_mrws	= 1;
	caps->reserved_uars	= 0;
	caps->reserved_cqs	= 0;
	caps->reserved_srqs	= 0;
	caps->reserved_qps	= HNS_ROCE_V2_RSV_QPS;

	caps->qpc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->srqc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->cqc_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->mpt_hop_num	= HNS_ROCE_CONTEXT_HOP_NUM;
	caps->mtt_hop_num	= HNS_ROCE_MTT_HOP_NUM;
	caps->pbl_hop_num       = HNS_ROCE_PBL_HOP_NUM;
	caps->wqe_sq_hop_num	= HNS_ROCE_SQWQE_HOP_NUM;
	caps->wqe_sge_hop_num	= HNS_ROCE_EXT_SGE_HOP_NUM;
	caps->wqe_rq_hop_num	= HNS_ROCE_RQWQE_HOP_NUM;
	caps->cqe_hop_num	= HNS_ROCE_CQE_HOP_NUM;
	caps->srqwqe_hop_num	= HNS_ROCE_SRQWQE_HOP_NUM;
	caps->idx_hop_num	= HNS_ROCE_IDX_HOP_NUM;
	caps->eqe_hop_num       = HNS_ROCE_EQE_HOP_NUM;
	caps->chunk_sz          = HNS_ROCE_V2_TABLE_CHUNK_SIZE;

	caps->flags		= HNS_ROCE_CAP_FLAG_REREG_MR |
				  HNS_ROCE_CAP_FLAG_ROCE_V1_V2 |
				  HNS_ROCE_CAP_FLAG_CQ_RECORD_DB |
				  HNS_ROCE_CAP_FLAG_QP_RECORD_DB;

	caps->pkey_table_len[0] = 1;
	caps->ceqe_depth	= HNS_ROCE_V2_COMP_EQE_NUM;
	caps->aeqe_depth	= HNS_ROCE_V2_ASYNC_EQE_NUM;
	caps->local_ca_ack_delay = 0;
	caps->max_mtu = IB_MTU_4096;

	caps->max_srq_wrs	= HNS_ROCE_V2_MAX_SRQ_WR;
	caps->max_srq_sges	= HNS_ROCE_V2_MAX_SRQ_SGE;

	caps->flags |= HNS_ROCE_CAP_FLAG_ATOMIC | HNS_ROCE_CAP_FLAG_MW |
		       HNS_ROCE_CAP_FLAG_SRQ | HNS_ROCE_CAP_FLAG_FRMR |
		       HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL | HNS_ROCE_CAP_FLAG_XRC;

	caps->num_qpc_समयr	  = HNS_ROCE_V2_MAX_QPC_TIMER_NUM;
	caps->qpc_समयr_entry_sz  = HNS_ROCE_V2_QPC_TIMER_ENTRY_SZ;
	caps->qpc_समयr_hop_num   = HNS_ROCE_HOP_NUM_0;
	caps->num_cqc_समयr	  = HNS_ROCE_V2_MAX_CQC_TIMER_NUM;
	caps->cqc_समयr_entry_sz  = HNS_ROCE_V2_CQC_TIMER_ENTRY_SZ;
	caps->cqc_समयr_hop_num   = HNS_ROCE_HOP_NUM_0;

	caps->sccc_hop_num	  = HNS_ROCE_SCCC_HOP_NUM;

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09) अणु
		caps->aeqe_size = HNS_ROCE_V3_EQE_SIZE;
		caps->ceqe_size = HNS_ROCE_V3_EQE_SIZE;
		caps->cqe_sz = HNS_ROCE_V3_CQE_SIZE;
		caps->qpc_sz = HNS_ROCE_V3_QPC_SZ;
		caps->sccc_sz = HNS_ROCE_V3_SCCC_SZ;
		caps->gmv_entry_sz = HNS_ROCE_V3_GMV_ENTRY_SZ;
		caps->gmv_entry_num = caps->gmv_bt_num * (PAGE_SIZE /
							  caps->gmv_entry_sz);
		caps->gmv_hop_num = HNS_ROCE_HOP_NUM_0;
		caps->gid_table_len[0] = caps->gmv_bt_num * (HNS_HW_PAGE_SIZE /
					 caps->gmv_entry_sz);
		caps->max_sq_अंतरभूत = HNS_ROCE_V2_MAX_SQ_INL_EXT;
	पूर्ण अन्यथा अणु
		caps->aeqe_size = HNS_ROCE_AEQE_SIZE;
		caps->ceqe_size = HNS_ROCE_CEQE_SIZE;
		caps->cqe_sz = HNS_ROCE_V2_CQE_SIZE;
		caps->qpc_sz = HNS_ROCE_V2_QPC_SZ;
		caps->sccc_sz = HNS_ROCE_V2_SCCC_SZ;
		caps->gid_table_len[0] = HNS_ROCE_V2_GID_INDEX_NUM;
		caps->max_sq_अंतरभूत = HNS_ROCE_V2_MAX_SQ_INLINE;
	पूर्ण
पूर्ण

अटल व्योम calc_pg_sz(u32 obj_num, u32 obj_size, u32 hop_num, u32 ctx_bt_num,
		       u32 *buf_page_size, u32 *bt_page_size, u32 hem_type)
अणु
	u64 obj_per_chunk;
	u64 bt_chunk_size = PAGE_SIZE;
	u64 buf_chunk_size = PAGE_SIZE;
	u64 obj_per_chunk_शेष = buf_chunk_size / obj_size;

	*buf_page_size = 0;
	*bt_page_size = 0;

	चयन (hop_num) अणु
	हाल 3:
		obj_per_chunk = ctx_bt_num * (bt_chunk_size / BA_BYTE_LEN) *
				(bt_chunk_size / BA_BYTE_LEN) *
				(bt_chunk_size / BA_BYTE_LEN) *
				 obj_per_chunk_शेष;
		अवरोध;
	हाल 2:
		obj_per_chunk = ctx_bt_num * (bt_chunk_size / BA_BYTE_LEN) *
				(bt_chunk_size / BA_BYTE_LEN) *
				 obj_per_chunk_शेष;
		अवरोध;
	हाल 1:
		obj_per_chunk = ctx_bt_num * (bt_chunk_size / BA_BYTE_LEN) *
				obj_per_chunk_शेष;
		अवरोध;
	हाल HNS_ROCE_HOP_NUM_0:
		obj_per_chunk = ctx_bt_num * obj_per_chunk_शेष;
		अवरोध;
	शेष:
		pr_err("table %u not support hop_num = %u!\n", hem_type,
		       hop_num);
		वापस;
	पूर्ण

	अगर (hem_type >= HEM_TYPE_MTT)
		*bt_page_size = ilog2(DIV_ROUND_UP(obj_num, obj_per_chunk));
	अन्यथा
		*buf_page_size = ilog2(DIV_ROUND_UP(obj_num, obj_per_chunk));
पूर्ण

अटल व्योम set_hem_page_size(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;

	/* EQ */
	caps->eqe_ba_pg_sz = 0;
	caps->eqe_buf_pg_sz = 0;

	/* Link Table */
	caps->tsq_buf_pg_sz = 0;

	/* MR */
	caps->pbl_ba_pg_sz = HNS_ROCE_BA_PG_SZ_SUPPORTED_16K;
	caps->pbl_buf_pg_sz = 0;
	calc_pg_sz(caps->num_mtpts, caps->mtpt_entry_sz, caps->mpt_hop_num,
		   caps->mpt_bt_num, &caps->mpt_buf_pg_sz, &caps->mpt_ba_pg_sz,
		   HEM_TYPE_MTPT);

	/* QP */
	caps->qpc_समयr_ba_pg_sz  = 0;
	caps->qpc_समयr_buf_pg_sz = 0;
	caps->mtt_ba_pg_sz = 0;
	caps->mtt_buf_pg_sz = 0;
	calc_pg_sz(caps->num_qps, caps->qpc_sz, caps->qpc_hop_num,
		   caps->qpc_bt_num, &caps->qpc_buf_pg_sz, &caps->qpc_ba_pg_sz,
		   HEM_TYPE_QPC);

	अगर (caps->flags & HNS_ROCE_CAP_FLAG_QP_FLOW_CTRL)
		calc_pg_sz(caps->num_qps, caps->sccc_sz, caps->sccc_hop_num,
			   caps->sccc_bt_num, &caps->sccc_buf_pg_sz,
			   &caps->sccc_ba_pg_sz, HEM_TYPE_SCCC);

	/* CQ */
	calc_pg_sz(caps->num_cqs, caps->cqc_entry_sz, caps->cqc_hop_num,
		   caps->cqc_bt_num, &caps->cqc_buf_pg_sz, &caps->cqc_ba_pg_sz,
		   HEM_TYPE_CQC);
	calc_pg_sz(caps->max_cqes, caps->cqe_sz, caps->cqe_hop_num,
		   1, &caps->cqe_buf_pg_sz, &caps->cqe_ba_pg_sz, HEM_TYPE_CQE);

	अगर (caps->cqc_समयr_entry_sz)
		calc_pg_sz(caps->num_cqc_समयr, caps->cqc_समयr_entry_sz,
			   caps->cqc_समयr_hop_num, caps->cqc_समयr_bt_num,
			   &caps->cqc_समयr_buf_pg_sz,
			   &caps->cqc_समयr_ba_pg_sz, HEM_TYPE_CQC_TIMER);

	/* SRQ */
	अगर (caps->flags & HNS_ROCE_CAP_FLAG_SRQ) अणु
		calc_pg_sz(caps->num_srqs, caps->srqc_entry_sz,
			   caps->srqc_hop_num, caps->srqc_bt_num,
			   &caps->srqc_buf_pg_sz, &caps->srqc_ba_pg_sz,
			   HEM_TYPE_SRQC);
		calc_pg_sz(caps->num_srqwqe_segs, caps->mtt_entry_sz,
			   caps->srqwqe_hop_num, 1, &caps->srqwqe_buf_pg_sz,
			   &caps->srqwqe_ba_pg_sz, HEM_TYPE_SRQWQE);
		calc_pg_sz(caps->num_idx_segs, caps->idx_entry_sz,
			   caps->idx_hop_num, 1, &caps->idx_buf_pg_sz,
			   &caps->idx_ba_pg_sz, HEM_TYPE_IDX);
	पूर्ण

	/* GMV */
	caps->gmv_ba_pg_sz = 0;
	caps->gmv_buf_pg_sz = 0;
पूर्ण

अटल पूर्णांक hns_roce_query_pf_caps(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_cmq_desc desc[HNS_ROCE_QUERY_PF_CAPS_CMD_NUM];
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	काष्ठा hns_roce_query_pf_caps_a *resp_a;
	काष्ठा hns_roce_query_pf_caps_b *resp_b;
	काष्ठा hns_roce_query_pf_caps_c *resp_c;
	काष्ठा hns_roce_query_pf_caps_d *resp_d;
	काष्ठा hns_roce_query_pf_caps_e *resp_e;
	पूर्णांक ctx_hop_num;
	पूर्णांक pbl_hop_num;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < HNS_ROCE_QUERY_PF_CAPS_CMD_NUM; i++) अणु
		hns_roce_cmq_setup_basic_desc(&desc[i],
					      HNS_ROCE_OPC_QUERY_PF_CAPS_NUM,
					      true);
		अगर (i < (HNS_ROCE_QUERY_PF_CAPS_CMD_NUM - 1))
			desc[i].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);
		अन्यथा
			desc[i].flag &= ~cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);
	पूर्ण

	ret = hns_roce_cmq_send(hr_dev, desc, HNS_ROCE_QUERY_PF_CAPS_CMD_NUM);
	अगर (ret)
		वापस ret;

	resp_a = (काष्ठा hns_roce_query_pf_caps_a *)desc[0].data;
	resp_b = (काष्ठा hns_roce_query_pf_caps_b *)desc[1].data;
	resp_c = (काष्ठा hns_roce_query_pf_caps_c *)desc[2].data;
	resp_d = (काष्ठा hns_roce_query_pf_caps_d *)desc[3].data;
	resp_e = (काष्ठा hns_roce_query_pf_caps_e *)desc[4].data;

	caps->local_ca_ack_delay     = resp_a->local_ca_ack_delay;
	caps->max_sq_sg		     = le16_to_cpu(resp_a->max_sq_sg);
	caps->max_sq_अंतरभूत	     = le16_to_cpu(resp_a->max_sq_अंतरभूत);
	caps->max_rq_sg		     = le16_to_cpu(resp_a->max_rq_sg);
	caps->max_rq_sg = roundup_घात_of_two(caps->max_rq_sg);
	caps->max_extend_sg	     = le32_to_cpu(resp_a->max_extend_sg);
	caps->num_qpc_समयr	     = le16_to_cpu(resp_a->num_qpc_समयr);
	caps->num_cqc_समयr	     = le16_to_cpu(resp_a->num_cqc_समयr);
	caps->max_srq_sges	     = le16_to_cpu(resp_a->max_srq_sges);
	caps->max_srq_sges = roundup_घात_of_two(caps->max_srq_sges);
	caps->num_aeq_vectors	     = resp_a->num_aeq_vectors;
	caps->num_other_vectors	     = resp_a->num_other_vectors;
	caps->max_sq_desc_sz	     = resp_a->max_sq_desc_sz;
	caps->max_rq_desc_sz	     = resp_a->max_rq_desc_sz;
	caps->max_srq_desc_sz	     = resp_a->max_srq_desc_sz;
	caps->cqe_sz		     = HNS_ROCE_V2_CQE_SIZE;

	caps->mtpt_entry_sz	     = resp_b->mtpt_entry_sz;
	caps->irrl_entry_sz	     = resp_b->irrl_entry_sz;
	caps->trrl_entry_sz	     = resp_b->trrl_entry_sz;
	caps->cqc_entry_sz	     = resp_b->cqc_entry_sz;
	caps->srqc_entry_sz	     = resp_b->srqc_entry_sz;
	caps->idx_entry_sz	     = resp_b->idx_entry_sz;
	caps->sccc_sz		     = resp_b->sccc_sz;
	caps->max_mtu		     = resp_b->max_mtu;
	caps->qpc_sz		     = HNS_ROCE_V2_QPC_SZ;
	caps->min_cqes		     = resp_b->min_cqes;
	caps->min_wqes		     = resp_b->min_wqes;
	caps->page_size_cap	     = le32_to_cpu(resp_b->page_size_cap);
	caps->pkey_table_len[0]	     = resp_b->pkey_table_len;
	caps->phy_num_uars	     = resp_b->phy_num_uars;
	ctx_hop_num		     = resp_b->ctx_hop_num;
	pbl_hop_num		     = resp_b->pbl_hop_num;

	caps->num_pds = 1 << roce_get_field(resp_c->cap_flags_num_pds,
					    V2_QUERY_PF_CAPS_C_NUM_PDS_M,
					    V2_QUERY_PF_CAPS_C_NUM_PDS_S);
	caps->flags = roce_get_field(resp_c->cap_flags_num_pds,
				     V2_QUERY_PF_CAPS_C_CAP_FLAGS_M,
				     V2_QUERY_PF_CAPS_C_CAP_FLAGS_S);
	caps->flags |= le16_to_cpu(resp_d->cap_flags_ex) <<
		       HNS_ROCE_CAP_FLAGS_EX_SHIFT;

	caps->num_cqs = 1 << roce_get_field(resp_c->max_gid_num_cqs,
					    V2_QUERY_PF_CAPS_C_NUM_CQS_M,
					    V2_QUERY_PF_CAPS_C_NUM_CQS_S);
	caps->gid_table_len[0] = roce_get_field(resp_c->max_gid_num_cqs,
						V2_QUERY_PF_CAPS_C_MAX_GID_M,
						V2_QUERY_PF_CAPS_C_MAX_GID_S);

	caps->gid_table_len[0] /= hr_dev->func_num;

	caps->max_cqes = 1 << roce_get_field(resp_c->cq_depth,
					     V2_QUERY_PF_CAPS_C_CQ_DEPTH_M,
					     V2_QUERY_PF_CAPS_C_CQ_DEPTH_S);
	caps->num_mtpts = 1 << roce_get_field(resp_c->num_mrws,
					      V2_QUERY_PF_CAPS_C_NUM_MRWS_M,
					      V2_QUERY_PF_CAPS_C_NUM_MRWS_S);
	caps->num_qps = 1 << roce_get_field(resp_c->ord_num_qps,
					    V2_QUERY_PF_CAPS_C_NUM_QPS_M,
					    V2_QUERY_PF_CAPS_C_NUM_QPS_S);
	caps->max_qp_init_rdma = roce_get_field(resp_c->ord_num_qps,
						V2_QUERY_PF_CAPS_C_MAX_ORD_M,
						V2_QUERY_PF_CAPS_C_MAX_ORD_S);
	caps->max_qp_dest_rdma = caps->max_qp_init_rdma;
	caps->max_wqes = 1 << le16_to_cpu(resp_c->sq_depth);
	caps->num_srqs = 1 << roce_get_field(resp_d->wq_hop_num_max_srqs,
					     V2_QUERY_PF_CAPS_D_NUM_SRQS_M,
					     V2_QUERY_PF_CAPS_D_NUM_SRQS_S);
	caps->cong_type = roce_get_field(resp_d->wq_hop_num_max_srqs,
					 V2_QUERY_PF_CAPS_D_CONG_TYPE_M,
					 V2_QUERY_PF_CAPS_D_CONG_TYPE_S);
	caps->max_srq_wrs = 1 << le16_to_cpu(resp_d->srq_depth);

	caps->ceqe_depth = 1 << roce_get_field(resp_d->num_ceqs_ceq_depth,
					       V2_QUERY_PF_CAPS_D_CEQ_DEPTH_M,
					       V2_QUERY_PF_CAPS_D_CEQ_DEPTH_S);
	caps->num_comp_vectors = roce_get_field(resp_d->num_ceqs_ceq_depth,
						V2_QUERY_PF_CAPS_D_NUM_CEQS_M,
						V2_QUERY_PF_CAPS_D_NUM_CEQS_S);

	caps->aeqe_depth = 1 << roce_get_field(resp_d->arm_st_aeq_depth,
					       V2_QUERY_PF_CAPS_D_AEQ_DEPTH_M,
					       V2_QUERY_PF_CAPS_D_AEQ_DEPTH_S);
	caps->शेष_aeq_arm_st = roce_get_field(resp_d->arm_st_aeq_depth,
					    V2_QUERY_PF_CAPS_D_AEQ_ARM_ST_M,
					    V2_QUERY_PF_CAPS_D_AEQ_ARM_ST_S);
	caps->शेष_ceq_arm_st = roce_get_field(resp_d->arm_st_aeq_depth,
					    V2_QUERY_PF_CAPS_D_CEQ_ARM_ST_M,
					    V2_QUERY_PF_CAPS_D_CEQ_ARM_ST_S);
	caps->reserved_pds = roce_get_field(resp_d->num_uars_rsv_pds,
					    V2_QUERY_PF_CAPS_D_RSV_PDS_M,
					    V2_QUERY_PF_CAPS_D_RSV_PDS_S);
	caps->num_uars = 1 << roce_get_field(resp_d->num_uars_rsv_pds,
					     V2_QUERY_PF_CAPS_D_NUM_UARS_M,
					     V2_QUERY_PF_CAPS_D_NUM_UARS_S);
	caps->reserved_qps = roce_get_field(resp_d->rsv_uars_rsv_qps,
					    V2_QUERY_PF_CAPS_D_RSV_QPS_M,
					    V2_QUERY_PF_CAPS_D_RSV_QPS_S);
	caps->reserved_uars = roce_get_field(resp_d->rsv_uars_rsv_qps,
					     V2_QUERY_PF_CAPS_D_RSV_UARS_M,
					     V2_QUERY_PF_CAPS_D_RSV_UARS_S);
	caps->reserved_mrws = roce_get_field(resp_e->chunk_size_shअगरt_rsv_mrws,
					     V2_QUERY_PF_CAPS_E_RSV_MRWS_M,
					     V2_QUERY_PF_CAPS_E_RSV_MRWS_S);
	caps->chunk_sz = 1 << roce_get_field(resp_e->chunk_size_shअगरt_rsv_mrws,
					 V2_QUERY_PF_CAPS_E_CHUNK_SIZE_SHIFT_M,
					 V2_QUERY_PF_CAPS_E_CHUNK_SIZE_SHIFT_S);
	caps->reserved_cqs = roce_get_field(resp_e->rsv_cqs,
					    V2_QUERY_PF_CAPS_E_RSV_CQS_M,
					    V2_QUERY_PF_CAPS_E_RSV_CQS_S);
	caps->reserved_srqs = roce_get_field(resp_e->rsv_srqs,
					     V2_QUERY_PF_CAPS_E_RSV_SRQS_M,
					     V2_QUERY_PF_CAPS_E_RSV_SRQS_S);
	caps->reserved_lkey = roce_get_field(resp_e->rsv_lkey,
					     V2_QUERY_PF_CAPS_E_RSV_LKEYS_M,
					     V2_QUERY_PF_CAPS_E_RSV_LKEYS_S);
	caps->शेष_ceq_max_cnt = le16_to_cpu(resp_e->ceq_max_cnt);
	caps->शेष_ceq_period = le16_to_cpu(resp_e->ceq_period);
	caps->शेष_aeq_max_cnt = le16_to_cpu(resp_e->aeq_max_cnt);
	caps->शेष_aeq_period = le16_to_cpu(resp_e->aeq_period);

	caps->qpc_समयr_entry_sz = HNS_ROCE_V2_QPC_TIMER_ENTRY_SZ;
	caps->cqc_समयr_entry_sz = HNS_ROCE_V2_CQC_TIMER_ENTRY_SZ;
	caps->mtt_entry_sz = HNS_ROCE_V2_MTT_ENTRY_SZ;
	caps->num_mtt_segs = HNS_ROCE_V2_MAX_MTT_SEGS;
	caps->ceqe_size = HNS_ROCE_CEQE_SIZE;
	caps->aeqe_size = HNS_ROCE_AEQE_SIZE;
	caps->num_xrcds = HNS_ROCE_V2_MAX_XRCD_NUM;
	caps->reserved_xrcds = HNS_ROCE_V2_RSV_XRCD_NUM;
	caps->num_srqwqe_segs = HNS_ROCE_V2_MAX_SRQWQE_SEGS;
	caps->num_idx_segs = HNS_ROCE_V2_MAX_IDX_SEGS;

	caps->qpc_hop_num = ctx_hop_num;
	caps->srqc_hop_num = ctx_hop_num;
	caps->cqc_hop_num = ctx_hop_num;
	caps->mpt_hop_num = ctx_hop_num;
	caps->mtt_hop_num = pbl_hop_num;
	caps->cqe_hop_num = pbl_hop_num;
	caps->srqwqe_hop_num = pbl_hop_num;
	caps->idx_hop_num = pbl_hop_num;
	caps->wqe_sq_hop_num = roce_get_field(resp_d->wq_hop_num_max_srqs,
					  V2_QUERY_PF_CAPS_D_SQWQE_HOP_NUM_M,
					  V2_QUERY_PF_CAPS_D_SQWQE_HOP_NUM_S);
	caps->wqe_sge_hop_num = roce_get_field(resp_d->wq_hop_num_max_srqs,
					  V2_QUERY_PF_CAPS_D_EX_SGE_HOP_NUM_M,
					  V2_QUERY_PF_CAPS_D_EX_SGE_HOP_NUM_S);
	caps->wqe_rq_hop_num = roce_get_field(resp_d->wq_hop_num_max_srqs,
					  V2_QUERY_PF_CAPS_D_RQWQE_HOP_NUM_M,
					  V2_QUERY_PF_CAPS_D_RQWQE_HOP_NUM_S);

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09) अणु
		caps->ceqe_size = HNS_ROCE_V3_EQE_SIZE;
		caps->aeqe_size = HNS_ROCE_V3_EQE_SIZE;
		caps->cqe_sz = HNS_ROCE_V3_CQE_SIZE;
		caps->qpc_sz = HNS_ROCE_V3_QPC_SZ;
		caps->sccc_sz = HNS_ROCE_V3_SCCC_SZ;
		caps->gmv_entry_sz = HNS_ROCE_V3_GMV_ENTRY_SZ;
		caps->gmv_entry_num = caps->gmv_bt_num * (PAGE_SIZE /
						    caps->gmv_entry_sz);
		caps->gmv_hop_num = HNS_ROCE_HOP_NUM_0;
		caps->gid_table_len[0] = caps->gmv_bt_num *
				(HNS_HW_PAGE_SIZE / caps->gmv_entry_sz);
	पूर्ण

	caps->qpc_समयr_hop_num = HNS_ROCE_HOP_NUM_0;
	caps->cqc_समयr_hop_num = HNS_ROCE_HOP_NUM_0;

	वापस 0;
पूर्ण

अटल पूर्णांक config_hem_entry_size(काष्ठा hns_roce_dev *hr_dev, u32 type, u32 val)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cmq_req *req = (काष्ठा hns_roce_cmq_req *)desc.data;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_ENTRY_SIZE,
				      false);

	hr_reg_ग_लिखो(req, CFG_HEM_ENTRY_SIZE_TYPE, type);
	hr_reg_ग_लिखो(req, CFG_HEM_ENTRY_SIZE_VALUE, val);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक hns_roce_config_entry_size(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	पूर्णांक ret;

	अगर (hr_dev->pci_dev->revision < PCI_REVISION_ID_HIP09)
		वापस 0;

	ret = config_hem_entry_size(hr_dev, HNS_ROCE_CFG_QPC_SIZE,
				    caps->qpc_sz);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "failed to cfg qpc sz, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = config_hem_entry_size(hr_dev, HNS_ROCE_CFG_SCCC_SIZE,
				    caps->sccc_sz);
	अगर (ret)
		dev_err(hr_dev->dev, "failed to cfg sccc sz, ret = %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_vf_profile(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक ret;

	hr_dev->venकरोr_part_id = hr_dev->pci_dev->device;
	hr_dev->sys_image_guid = be64_to_cpu(hr_dev->ib_dev.node_guid);
	hr_dev->func_num = 1;

	ret = hns_roce_query_vf_resource(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev,
			"Query the VF resource fail, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	set_शेष_caps(hr_dev);
	set_hem_page_size(hr_dev);

	ret = hns_roce_v2_set_bt(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev,
			"Configure the VF bt attribute fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_profile(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_caps *caps = &hr_dev->caps;
	पूर्णांक ret;

	ret = hns_roce_cmq_query_hw_info(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Query hardware version fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	ret = hns_roce_query_fw_ver(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Query firmware version fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (hr_dev->is_vf)
		वापस hns_roce_v2_vf_profile(hr_dev);

	ret = hns_roce_query_func_info(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Query function info fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	ret = hns_roce_config_global_param(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Configure global param fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	/* Get pf resource owned by every pf */
	ret = hns_roce_query_pf_resource(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Query pf resource fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	ret = hns_roce_query_pf_समयr_resource(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev,
			"failed to query pf timer resource, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	ret = hns_roce_set_vf_चयन_param(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev,
			"failed to set function switch param, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	hr_dev->venकरोr_part_id = hr_dev->pci_dev->device;
	hr_dev->sys_image_guid = be64_to_cpu(hr_dev->ib_dev.node_guid);

	caps->pbl_hop_num	= HNS_ROCE_PBL_HOP_NUM;
	caps->eqe_hop_num	= HNS_ROCE_EQE_HOP_NUM;

	ret = hns_roce_query_pf_caps(hr_dev);
	अगर (ret)
		set_शेष_caps(hr_dev);

	ret = hns_roce_alloc_vf_resource(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "Allocate vf resource fail, ret = %d.\n",
			ret);
		वापस ret;
	पूर्ण

	set_hem_page_size(hr_dev);
	ret = hns_roce_v2_set_bt(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev,
			"Configure bt attribute fail, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/* Configure the size of QPC, SCCC, etc. */
	ret = hns_roce_config_entry_size(hr_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_config_link_table(काष्ठा hns_roce_dev *hr_dev,
				      क्रमागत hns_roce_link_table_type type)
अणु
	काष्ठा hns_roce_cmq_desc desc[2];
	काष्ठा hns_roce_cfg_llm_a *req_a =
				(काष्ठा hns_roce_cfg_llm_a *)desc[0].data;
	काष्ठा hns_roce_cfg_llm_b *req_b =
				(काष्ठा hns_roce_cfg_llm_b *)desc[1].data;
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_link_table *link_tbl;
	काष्ठा hns_roce_link_table_entry *entry;
	क्रमागत hns_roce_opcode_type opcode;
	u32 page_num;

	चयन (type) अणु
	हाल TSQ_LINK_TABLE:
		link_tbl = &priv->tsq;
		opcode = HNS_ROCE_OPC_CFG_EXT_LLM;
		अवरोध;
	हाल TPQ_LINK_TABLE:
		link_tbl = &priv->tpq;
		opcode = HNS_ROCE_OPC_CFG_TMOUT_LLM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	page_num = link_tbl->npages;
	entry = link_tbl->table.buf;

	hns_roce_cmq_setup_basic_desc(&desc[0], opcode, false);
	desc[0].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);

	hns_roce_cmq_setup_basic_desc(&desc[1], opcode, false);

	req_a->base_addr_l = cpu_to_le32(link_tbl->table.map & 0xffffffff);
	req_a->base_addr_h = cpu_to_le32(link_tbl->table.map >> 32);
	roce_set_field(req_a->depth_pgsz_init_en, CFG_LLM_QUE_DEPTH_M,
		       CFG_LLM_QUE_DEPTH_S, link_tbl->npages);
	roce_set_field(req_a->depth_pgsz_init_en, CFG_LLM_QUE_PGSZ_M,
		       CFG_LLM_QUE_PGSZ_S, link_tbl->pg_sz);
	roce_set_field(req_a->depth_pgsz_init_en, CFG_LLM_INIT_EN_M,
		       CFG_LLM_INIT_EN_S, 1);
	req_a->head_ba_l = cpu_to_le32(entry[0].blk_ba0);
	req_a->head_ba_h_nxtptr = cpu_to_le32(entry[0].blk_ba1_nxt_ptr);
	roce_set_field(req_a->head_ptr, CFG_LLM_HEAD_PTR_M, CFG_LLM_HEAD_PTR_S,
		       0);

	req_b->tail_ba_l = cpu_to_le32(entry[page_num - 1].blk_ba0);
	roce_set_field(req_b->tail_ba_h, CFG_LLM_TAIL_BA_H_M,
		       CFG_LLM_TAIL_BA_H_S,
		       entry[page_num - 1].blk_ba1_nxt_ptr &
		       HNS_ROCE_LINK_TABLE_BA1_M);
	roce_set_field(req_b->tail_ptr, CFG_LLM_TAIL_PTR_M, CFG_LLM_TAIL_PTR_S,
		       (entry[page_num - 2].blk_ba1_nxt_ptr &
			HNS_ROCE_LINK_TABLE_NXT_PTR_M) >>
			HNS_ROCE_LINK_TABLE_NXT_PTR_S);

	वापस hns_roce_cmq_send(hr_dev, desc, 2);
पूर्ण

अटल पूर्णांक hns_roce_init_link_table(काष्ठा hns_roce_dev *hr_dev,
				    क्रमागत hns_roce_link_table_type type)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	काष्ठा hns_roce_link_table *link_tbl;
	काष्ठा hns_roce_link_table_entry *entry;
	काष्ठा device *dev = hr_dev->dev;
	u32 buf_chk_sz;
	dma_addr_t t;
	पूर्णांक func_num = 1;
	u32 pg_num_a;
	u32 pg_num_b;
	u32 pg_num;
	u32 size;
	पूर्णांक i;

	चयन (type) अणु
	हाल TSQ_LINK_TABLE:
		link_tbl = &priv->tsq;
		buf_chk_sz = 1 << (hr_dev->caps.tsq_buf_pg_sz + PAGE_SHIFT);
		pg_num_a = hr_dev->caps.num_qps * 8 / buf_chk_sz;
		pg_num_b = hr_dev->caps.sl_num * 4 + 2;
		अवरोध;
	हाल TPQ_LINK_TABLE:
		link_tbl = &priv->tpq;
		buf_chk_sz = 1 << (hr_dev->caps.tpq_buf_pg_sz +	PAGE_SHIFT);
		pg_num_a = hr_dev->caps.num_cqs * 4 / buf_chk_sz;
		pg_num_b = 2 * 4 * func_num + 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pg_num = max(pg_num_a, pg_num_b);
	size = pg_num * माप(काष्ठा hns_roce_link_table_entry);

	link_tbl->table.buf = dma_alloc_coherent(dev, size,
						 &link_tbl->table.map,
						 GFP_KERNEL);
	अगर (!link_tbl->table.buf)
		जाओ out;

	link_tbl->pg_list = kसुस्मृति(pg_num, माप(*link_tbl->pg_list),
				    GFP_KERNEL);
	अगर (!link_tbl->pg_list)
		जाओ err_kसुस्मृति_failed;

	entry = link_tbl->table.buf;
	क्रम (i = 0; i < pg_num; ++i) अणु
		link_tbl->pg_list[i].buf = dma_alloc_coherent(dev, buf_chk_sz,
							      &t, GFP_KERNEL);
		अगर (!link_tbl->pg_list[i].buf)
			जाओ err_alloc_buf_failed;

		link_tbl->pg_list[i].map = t;

		entry[i].blk_ba0 = (u32)(t >> 12);
		entry[i].blk_ba1_nxt_ptr = (u32)(t >> 44);

		अगर (i < (pg_num - 1))
			entry[i].blk_ba1_nxt_ptr |=
				(i + 1) << HNS_ROCE_LINK_TABLE_NXT_PTR_S;
	पूर्ण
	link_tbl->npages = pg_num;
	link_tbl->pg_sz = buf_chk_sz;

	वापस hns_roce_config_link_table(hr_dev, type);

err_alloc_buf_failed:
	क्रम (i -= 1; i >= 0; i--)
		dma_मुक्त_coherent(dev, buf_chk_sz,
				  link_tbl->pg_list[i].buf,
				  link_tbl->pg_list[i].map);
	kमुक्त(link_tbl->pg_list);

err_kसुस्मृति_failed:
	dma_मुक्त_coherent(dev, size, link_tbl->table.buf,
			  link_tbl->table.map);

out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम hns_roce_मुक्त_link_table(काष्ठा hns_roce_dev *hr_dev,
				     काष्ठा hns_roce_link_table *link_tbl)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक size;
	पूर्णांक i;

	size = link_tbl->npages * माप(काष्ठा hns_roce_link_table_entry);

	क्रम (i = 0; i < link_tbl->npages; ++i)
		अगर (link_tbl->pg_list[i].buf)
			dma_मुक्त_coherent(dev, link_tbl->pg_sz,
					  link_tbl->pg_list[i].buf,
					  link_tbl->pg_list[i].map);
	kमुक्त(link_tbl->pg_list);

	dma_मुक्त_coherent(dev, size, link_tbl->table.buf,
			  link_tbl->table.map);
पूर्ण

अटल व्योम मुक्त_dip_list(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_dip *hr_dip;
	काष्ठा hns_roce_dip *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hr_dev->dip_list_lock, flags);

	list_क्रम_each_entry_safe(hr_dip, पंचांगp, &hr_dev->dip_list, node) अणु
		list_del(&hr_dip->node);
		kमुक्त(hr_dip);
	पूर्ण

	spin_unlock_irqrestore(&hr_dev->dip_list_lock, flags);
पूर्ण

अटल पूर्णांक get_hem_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	अचिन्हित पूर्णांक qpc_count;
	अचिन्हित पूर्णांक cqc_count;
	अचिन्हित पूर्णांक gmv_count;
	पूर्णांक ret;
	पूर्णांक i;

	/* Alloc memory क्रम source address table buffer space chunk */
	क्रम (gmv_count = 0; gmv_count < hr_dev->caps.gmv_entry_num;
	     gmv_count++) अणु
		ret = hns_roce_table_get(hr_dev, &hr_dev->gmv_table, gmv_count);
		अगर (ret)
			जाओ err_gmv_failed;
	पूर्ण

	अगर (hr_dev->is_vf)
		वापस 0;

	/* Alloc memory क्रम QPC Timer buffer space chunk */
	क्रम (qpc_count = 0; qpc_count < hr_dev->caps.qpc_समयr_bt_num;
	     qpc_count++) अणु
		ret = hns_roce_table_get(hr_dev, &hr_dev->qpc_समयr_table,
					 qpc_count);
		अगर (ret) अणु
			dev_err(hr_dev->dev, "QPC Timer get failed\n");
			जाओ err_qpc_समयr_failed;
		पूर्ण
	पूर्ण

	/* Alloc memory क्रम CQC Timer buffer space chunk */
	क्रम (cqc_count = 0; cqc_count < hr_dev->caps.cqc_समयr_bt_num;
	     cqc_count++) अणु
		ret = hns_roce_table_get(hr_dev, &hr_dev->cqc_समयr_table,
					 cqc_count);
		अगर (ret) अणु
			dev_err(hr_dev->dev, "CQC Timer get failed\n");
			जाओ err_cqc_समयr_failed;
		पूर्ण
	पूर्ण

	वापस 0;

err_cqc_समयr_failed:
	क्रम (i = 0; i < cqc_count; i++)
		hns_roce_table_put(hr_dev, &hr_dev->cqc_समयr_table, i);

err_qpc_समयr_failed:
	क्रम (i = 0; i < qpc_count; i++)
		hns_roce_table_put(hr_dev, &hr_dev->qpc_समयr_table, i);

err_gmv_failed:
	क्रम (i = 0; i < gmv_count; i++)
		hns_roce_table_put(hr_dev, &hr_dev->gmv_table, i);

	वापस ret;
पूर्ण

अटल व्योम put_hem_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hr_dev->caps.gmv_entry_num; i++)
		hns_roce_table_put(hr_dev, &hr_dev->gmv_table, i);

	अगर (hr_dev->is_vf)
		वापस;

	क्रम (i = 0; i < hr_dev->caps.qpc_समयr_bt_num; i++)
		hns_roce_table_put(hr_dev, &hr_dev->qpc_समयr_table, i);

	क्रम (i = 0; i < hr_dev->caps.cqc_समयr_bt_num; i++)
		hns_roce_table_put(hr_dev, &hr_dev->cqc_समयr_table, i);
पूर्ण

अटल पूर्णांक hns_roce_v2_init(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	पूर्णांक ret;

	ret = get_hem_table(hr_dev);
	अगर (ret)
		वापस ret;

	अगर (hr_dev->is_vf)
		वापस 0;

	/* TSQ includes SQ करोorbell and ack करोorbell */
	ret = hns_roce_init_link_table(hr_dev, TSQ_LINK_TABLE);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "failed to init TSQ, ret = %d.\n", ret);
		जाओ err_tsq_init_failed;
	पूर्ण

	ret = hns_roce_init_link_table(hr_dev, TPQ_LINK_TABLE);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "failed to init TPQ, ret = %d.\n", ret);
		जाओ err_tpq_init_failed;
	पूर्ण

	वापस 0;

err_tsq_init_failed:
	put_hem_table(hr_dev);

err_tpq_init_failed:
	hns_roce_मुक्त_link_table(hr_dev, &priv->tpq);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_v2_निकास(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;

	hns_roce_function_clear(hr_dev);

	अगर (!hr_dev->is_vf) अणु
		hns_roce_मुक्त_link_table(hr_dev, &priv->tpq);
		hns_roce_मुक्त_link_table(hr_dev, &priv->tsq);
	पूर्ण

	अगर (hr_dev->pci_dev->revision == PCI_REVISION_ID_HIP09)
		मुक्त_dip_list(hr_dev);
पूर्ण

अटल पूर्णांक hns_roce_mbox_post(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
			      u64 out_param, u32 in_modअगरier, u8 op_modअगरier,
			      u16 op, u16 token, पूर्णांक event)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_post_mbox *mb = (काष्ठा hns_roce_post_mbox *)desc.data;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_POST_MB, false);

	mb->in_param_l = cpu_to_le32(in_param);
	mb->in_param_h = cpu_to_le32(in_param >> 32);
	mb->out_param_l = cpu_to_le32(out_param);
	mb->out_param_h = cpu_to_le32(out_param >> 32);
	mb->cmd_tag = cpu_to_le32(in_modअगरier << 8 | op);
	mb->token_event_en = cpu_to_le32(event << 16 | token);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक v2_रुको_mbox_complete(काष्ठा hns_roce_dev *hr_dev, u32 समयout,
				 u8 *complete_status)
अणु
	काष्ठा hns_roce_mbox_status *mb_st;
	काष्ठा hns_roce_cmq_desc desc;
	अचिन्हित दीर्घ end;
	पूर्णांक ret = -EBUSY;
	u32 status;
	bool busy;

	mb_st = (काष्ठा hns_roce_mbox_status *)desc.data;
	end = msecs_to_jअगरfies(समयout) + jअगरfies;
	जबतक (v2_chk_mbox_is_avail(hr_dev, &busy)) अणु
		status = 0;
		hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_QUERY_MB_ST,
					      true);
		ret = __hns_roce_cmq_send(hr_dev, &desc, 1);
		अगर (!ret) अणु
			status = le32_to_cpu(mb_st->mb_status_hw_run);
			/* No pending message exists in ROCEE mbox. */
			अगर (!(status & MB_ST_HW_RUN_M))
				अवरोध;
		पूर्ण अन्यथा अगर (!v2_chk_mbox_is_avail(hr_dev, &busy)) अणु
			अवरोध;
		पूर्ण

		अगर (समय_after(jअगरfies, end)) अणु
			dev_err_ratelimited(hr_dev->dev,
					    "failed to wait mbox status 0x%x\n",
					    status);
			वापस -ETIMEDOUT;
		पूर्ण

		cond_resched();
		ret = -EBUSY;
	पूर्ण

	अगर (!ret) अणु
		*complete_status = (u8)(status & MB_ST_COMPLETE_M);
	पूर्ण अन्यथा अगर (!v2_chk_mbox_is_avail(hr_dev, &busy)) अणु
		/* Ignore all errors अगर the mbox is unavailable. */
		ret = 0;
		*complete_status = MB_ST_COMPLETE_M;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक v2_post_mbox(काष्ठा hns_roce_dev *hr_dev, u64 in_param,
			u64 out_param, u32 in_modअगरier, u8 op_modअगरier,
			u16 op, u16 token, पूर्णांक event)
अणु
	u8 status = 0;
	पूर्णांक ret;

	/* Waiting क्रम the mbox to be idle */
	ret = v2_रुको_mbox_complete(hr_dev, HNS_ROCE_V2_GO_BIT_TIMEOUT_MSECS,
				    &status);
	अगर (unlikely(ret)) अणु
		dev_err_ratelimited(hr_dev->dev,
				    "failed to check post mbox status = 0x%x, ret = %d.\n",
				    status, ret);
		वापस ret;
	पूर्ण

	/* Post new message to mbox */
	ret = hns_roce_mbox_post(hr_dev, in_param, out_param, in_modअगरier,
				 op_modअगरier, op, token, event);
	अगर (ret)
		dev_err_ratelimited(hr_dev->dev,
				    "failed to post mailbox, ret = %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक v2_poll_mbox_करोne(काष्ठा hns_roce_dev *hr_dev, अचिन्हित पूर्णांक समयout)
अणु
	u8 status = 0;
	पूर्णांक ret;

	ret = v2_रुको_mbox_complete(hr_dev, समयout, &status);
	अगर (!ret) अणु
		अगर (status != MB_ST_COMPLETE_SUCC)
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		dev_err_ratelimited(hr_dev->dev,
				    "failed to check mbox status = 0x%x, ret = %d.\n",
				    status, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम copy_gid(व्योम *dest, स्थिर जोड़ ib_gid *gid)
अणु
#घोषणा GID_SIZE 4
	स्थिर जोड़ ib_gid *src = gid;
	__le32 (*p)[GID_SIZE] = dest;
	पूर्णांक i;

	अगर (!gid)
		src = &zgid;

	क्रम (i = 0; i < GID_SIZE; i++)
		(*p)[i] = cpu_to_le32(*(u32 *)&src->raw[i * माप(u32)]);
पूर्ण

अटल पूर्णांक config_sgid_table(काष्ठा hns_roce_dev *hr_dev,
			     पूर्णांक gid_index, स्थिर जोड़ ib_gid *gid,
			     क्रमागत hns_roce_sgid_type sgid_type)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cfg_sgid_tb *sgid_tb =
				    (काष्ठा hns_roce_cfg_sgid_tb *)desc.data;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_SGID_TB, false);

	roce_set_field(sgid_tb->table_idx_rsv, CFG_SGID_TB_TABLE_IDX_M,
		       CFG_SGID_TB_TABLE_IDX_S, gid_index);
	roce_set_field(sgid_tb->vf_sgid_type_rsv, CFG_SGID_TB_VF_SGID_TYPE_M,
		       CFG_SGID_TB_VF_SGID_TYPE_S, sgid_type);

	copy_gid(&sgid_tb->vf_sgid_l, gid);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक config_gmv_table(काष्ठा hns_roce_dev *hr_dev,
			    पूर्णांक gid_index, स्थिर जोड़ ib_gid *gid,
			    क्रमागत hns_roce_sgid_type sgid_type,
			    स्थिर काष्ठा ib_gid_attr *attr)
अणु
	काष्ठा hns_roce_cmq_desc desc[2];
	काष्ठा hns_roce_cfg_gmv_tb_a *tb_a =
				(काष्ठा hns_roce_cfg_gmv_tb_a *)desc[0].data;
	काष्ठा hns_roce_cfg_gmv_tb_b *tb_b =
				(काष्ठा hns_roce_cfg_gmv_tb_b *)desc[1].data;

	u16 vlan_id = VLAN_CFI_MASK;
	u8 mac[ETH_ALEN] = अणुपूर्ण;
	पूर्णांक ret;

	अगर (gid) अणु
		ret = rdma_पढ़ो_gid_l2_fields(attr, &vlan_id, mac);
		अगर (ret)
			वापस ret;
	पूर्ण

	hns_roce_cmq_setup_basic_desc(&desc[0], HNS_ROCE_OPC_CFG_GMV_TBL, false);
	desc[0].flag |= cpu_to_le16(HNS_ROCE_CMD_FLAG_NEXT);

	hns_roce_cmq_setup_basic_desc(&desc[1], HNS_ROCE_OPC_CFG_GMV_TBL, false);

	copy_gid(&tb_a->vf_sgid_l, gid);

	roce_set_field(tb_a->vf_sgid_type_vlan, CFG_GMV_TB_VF_SGID_TYPE_M,
		       CFG_GMV_TB_VF_SGID_TYPE_S, sgid_type);
	roce_set_bit(tb_a->vf_sgid_type_vlan, CFG_GMV_TB_VF_VLAN_EN_S,
		     vlan_id < VLAN_CFI_MASK);
	roce_set_field(tb_a->vf_sgid_type_vlan, CFG_GMV_TB_VF_VLAN_ID_M,
		       CFG_GMV_TB_VF_VLAN_ID_S, vlan_id);

	tb_b->vf_smac_l = cpu_to_le32(*(u32 *)mac);
	roce_set_field(tb_b->vf_smac_h, CFG_GMV_TB_SMAC_H_M,
		       CFG_GMV_TB_SMAC_H_S, *(u16 *)&mac[4]);

	roce_set_field(tb_b->table_idx_rsv, CFG_GMV_TB_SGID_IDX_M,
		       CFG_GMV_TB_SGID_IDX_S, gid_index);

	वापस hns_roce_cmq_send(hr_dev, desc, 2);
पूर्ण

अटल पूर्णांक hns_roce_v2_set_gid(काष्ठा hns_roce_dev *hr_dev, u32 port,
			       पूर्णांक gid_index, स्थिर जोड़ ib_gid *gid,
			       स्थिर काष्ठा ib_gid_attr *attr)
अणु
	क्रमागत hns_roce_sgid_type sgid_type = GID_TYPE_FLAG_ROCE_V1;
	पूर्णांक ret;

	अगर (gid) अणु
		अगर (attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) अणु
			अगर (ipv6_addr_v4mapped((व्योम *)gid))
				sgid_type = GID_TYPE_FLAG_ROCE_V2_IPV4;
			अन्यथा
				sgid_type = GID_TYPE_FLAG_ROCE_V2_IPV6;
		पूर्ण अन्यथा अगर (attr->gid_type == IB_GID_TYPE_ROCE) अणु
			sgid_type = GID_TYPE_FLAG_ROCE_V1;
		पूर्ण
	पूर्ण

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
		ret = config_gmv_table(hr_dev, gid_index, gid, sgid_type, attr);
	अन्यथा
		ret = config_sgid_table(hr_dev, gid_index, gid, sgid_type);

	अगर (ret)
		ibdev_err(&hr_dev->ib_dev, "failed to set gid, ret = %d!\n",
			  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_set_mac(काष्ठा hns_roce_dev *hr_dev, u8 phy_port,
			       u8 *addr)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cfg_smac_tb *smac_tb =
				    (काष्ठा hns_roce_cfg_smac_tb *)desc.data;
	u16 reg_smac_h;
	u32 reg_smac_l;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_SMAC_TB, false);

	reg_smac_l = *(u32 *)(&addr[0]);
	reg_smac_h = *(u16 *)(&addr[4]);

	roce_set_field(smac_tb->tb_idx_rsv, CFG_SMAC_TB_IDX_M,
		       CFG_SMAC_TB_IDX_S, phy_port);
	roce_set_field(smac_tb->vf_smac_h_rsv, CFG_SMAC_TB_VF_SMAC_H_M,
		       CFG_SMAC_TB_VF_SMAC_H_S, reg_smac_h);
	smac_tb->vf_smac_l = cpu_to_le32(reg_smac_l);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक set_mtpt_pbl(काष्ठा hns_roce_dev *hr_dev,
			काष्ठा hns_roce_v2_mpt_entry *mpt_entry,
			काष्ठा hns_roce_mr *mr)
अणु
	u64 pages[HNS_ROCE_V2_MAX_INNER_MTPT_NUM] = अणु 0 पूर्ण;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	dma_addr_t pbl_ba;
	पूर्णांक i, count;

	count = hns_roce_mtr_find(hr_dev, &mr->pbl_mtr, 0, pages,
				  ARRAY_SIZE(pages), &pbl_ba);
	अगर (count < 1) अणु
		ibdev_err(ibdev, "failed to find PBL mtr, count = %d.\n",
			  count);
		वापस -ENOBUFS;
	पूर्ण

	/* Aligned to the hardware address access unit */
	क्रम (i = 0; i < count; i++)
		pages[i] >>= 6;

	mpt_entry->pbl_size = cpu_to_le32(mr->npages);
	mpt_entry->pbl_ba_l = cpu_to_le32(pbl_ba >> 3);
	roce_set_field(mpt_entry->byte_48_mode_ba,
		       V2_MPT_BYTE_48_PBL_BA_H_M, V2_MPT_BYTE_48_PBL_BA_H_S,
		       upper_32_bits(pbl_ba >> 3));

	mpt_entry->pa0_l = cpu_to_le32(lower_32_bits(pages[0]));
	roce_set_field(mpt_entry->byte_56_pa0_h, V2_MPT_BYTE_56_PA0_H_M,
		       V2_MPT_BYTE_56_PA0_H_S, upper_32_bits(pages[0]));

	mpt_entry->pa1_l = cpu_to_le32(lower_32_bits(pages[1]));
	roce_set_field(mpt_entry->byte_64_buf_pa1, V2_MPT_BYTE_64_PA1_H_M,
		       V2_MPT_BYTE_64_PA1_H_S, upper_32_bits(pages[1]));
	roce_set_field(mpt_entry->byte_64_buf_pa1,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_M,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_S,
		       to_hr_hw_page_shअगरt(mr->pbl_mtr.hem_cfg.buf_pg_shअगरt));

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_ग_लिखो_mtpt(काष्ठा hns_roce_dev *hr_dev,
				  व्योम *mb_buf, काष्ठा hns_roce_mr *mr,
				  अचिन्हित दीर्घ mtpt_idx)
अणु
	काष्ठा hns_roce_v2_mpt_entry *mpt_entry;
	पूर्णांक ret;

	mpt_entry = mb_buf;
	स_रखो(mpt_entry, 0, माप(*mpt_entry));

	hr_reg_ग_लिखो(mpt_entry, MPT_ST, V2_MPT_ST_VALID);
	hr_reg_ग_लिखो(mpt_entry, MPT_PD, mr->pd);
	hr_reg_enable(mpt_entry, MPT_L_INV_EN);

	hr_reg_ग_लिखो(mpt_entry, MPT_BIND_EN,
		     !!(mr->access & IB_ACCESS_MW_BIND));
	hr_reg_ग_लिखो(mpt_entry, MPT_ATOMIC_EN,
		     !!(mr->access & IB_ACCESS_REMOTE_ATOMIC));
	hr_reg_ग_लिखो(mpt_entry, MPT_RR_EN,
		     !!(mr->access & IB_ACCESS_REMOTE_READ));
	hr_reg_ग_लिखो(mpt_entry, MPT_RW_EN,
		     !!(mr->access & IB_ACCESS_REMOTE_WRITE));
	hr_reg_ग_लिखो(mpt_entry, MPT_LW_EN,
		     !!((mr->access & IB_ACCESS_LOCAL_WRITE)));

	mpt_entry->len_l = cpu_to_le32(lower_32_bits(mr->size));
	mpt_entry->len_h = cpu_to_le32(upper_32_bits(mr->size));
	mpt_entry->lkey = cpu_to_le32(mr->key);
	mpt_entry->va_l = cpu_to_le32(lower_32_bits(mr->iova));
	mpt_entry->va_h = cpu_to_le32(upper_32_bits(mr->iova));

	अगर (mr->type != MR_TYPE_MR)
		hr_reg_enable(mpt_entry, MPT_PA);

	अगर (mr->type == MR_TYPE_DMA)
		वापस 0;

	अगर (mr->pbl_hop_num != HNS_ROCE_HOP_NUM_0)
		hr_reg_ग_लिखो(mpt_entry, MPT_PBL_HOP_NUM, mr->pbl_hop_num);

	hr_reg_ग_लिखो(mpt_entry, MPT_PBL_BA_PG_SZ,
		     to_hr_hw_page_shअगरt(mr->pbl_mtr.hem_cfg.ba_pg_shअगरt));
	hr_reg_enable(mpt_entry, MPT_INNER_PA_VLD);

	ret = set_mtpt_pbl(hr_dev, mpt_entry, mr);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_rereg_ग_लिखो_mtpt(काष्ठा hns_roce_dev *hr_dev,
					काष्ठा hns_roce_mr *mr, पूर्णांक flags,
					व्योम *mb_buf)
अणु
	काष्ठा hns_roce_v2_mpt_entry *mpt_entry = mb_buf;
	u32 mr_access_flags = mr->access;
	पूर्णांक ret = 0;

	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_MPT_ST_M,
		       V2_MPT_BYTE_4_MPT_ST_S, V2_MPT_ST_VALID);

	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PD_M,
		       V2_MPT_BYTE_4_PD_S, mr->pd);

	अगर (flags & IB_MR_REREG_ACCESS) अणु
		roce_set_bit(mpt_entry->byte_8_mw_cnt_en,
			     V2_MPT_BYTE_8_BIND_EN_S,
			     (mr_access_flags & IB_ACCESS_MW_BIND ? 1 : 0));
		roce_set_bit(mpt_entry->byte_8_mw_cnt_en,
			     V2_MPT_BYTE_8_ATOMIC_EN_S,
			     mr_access_flags & IB_ACCESS_REMOTE_ATOMIC ? 1 : 0);
		roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_RR_EN_S,
			     mr_access_flags & IB_ACCESS_REMOTE_READ ? 1 : 0);
		roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_RW_EN_S,
			     mr_access_flags & IB_ACCESS_REMOTE_WRITE ? 1 : 0);
		roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_LW_EN_S,
			     mr_access_flags & IB_ACCESS_LOCAL_WRITE ? 1 : 0);
	पूर्ण

	अगर (flags & IB_MR_REREG_TRANS) अणु
		mpt_entry->va_l = cpu_to_le32(lower_32_bits(mr->iova));
		mpt_entry->va_h = cpu_to_le32(upper_32_bits(mr->iova));
		mpt_entry->len_l = cpu_to_le32(lower_32_bits(mr->size));
		mpt_entry->len_h = cpu_to_le32(upper_32_bits(mr->size));

		ret = set_mtpt_pbl(hr_dev, mpt_entry, mr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_frmr_ग_लिखो_mtpt(काष्ठा hns_roce_dev *hr_dev,
				       व्योम *mb_buf, काष्ठा hns_roce_mr *mr)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_v2_mpt_entry *mpt_entry;
	dma_addr_t pbl_ba = 0;

	mpt_entry = mb_buf;
	स_रखो(mpt_entry, 0, माप(*mpt_entry));

	अगर (hns_roce_mtr_find(hr_dev, &mr->pbl_mtr, 0, शून्य, 0, &pbl_ba) < 0) अणु
		ibdev_err(ibdev, "failed to find frmr mtr.\n");
		वापस -ENOBUFS;
	पूर्ण

	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_MPT_ST_M,
		       V2_MPT_BYTE_4_MPT_ST_S, V2_MPT_ST_FREE);
	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PBL_HOP_NUM_M,
		       V2_MPT_BYTE_4_PBL_HOP_NUM_S, 1);
	roce_set_field(mpt_entry->byte_4_pd_hop_st,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_M,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_S,
		       to_hr_hw_page_shअगरt(mr->pbl_mtr.hem_cfg.ba_pg_shअगरt));
	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PD_M,
		       V2_MPT_BYTE_4_PD_S, mr->pd);

	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_RA_EN_S, 1);
	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_R_INV_EN_S, 1);
	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_L_INV_EN_S, 1);

	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_FRE_S, 1);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_PA_S, 0);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_MR_MW_S, 0);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_BPD_S, 1);

	mpt_entry->pbl_size = cpu_to_le32(mr->npages);

	mpt_entry->pbl_ba_l = cpu_to_le32(lower_32_bits(pbl_ba >> 3));
	roce_set_field(mpt_entry->byte_48_mode_ba, V2_MPT_BYTE_48_PBL_BA_H_M,
		       V2_MPT_BYTE_48_PBL_BA_H_S,
		       upper_32_bits(pbl_ba >> 3));

	roce_set_field(mpt_entry->byte_64_buf_pa1,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_M,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_S,
		       to_hr_hw_page_shअगरt(mr->pbl_mtr.hem_cfg.buf_pg_shअगरt));

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_mw_ग_लिखो_mtpt(व्योम *mb_buf, काष्ठा hns_roce_mw *mw)
अणु
	काष्ठा hns_roce_v2_mpt_entry *mpt_entry;

	mpt_entry = mb_buf;
	स_रखो(mpt_entry, 0, माप(*mpt_entry));

	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_MPT_ST_M,
		       V2_MPT_BYTE_4_MPT_ST_S, V2_MPT_ST_FREE);
	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PD_M,
		       V2_MPT_BYTE_4_PD_S, mw->pdn);
	roce_set_field(mpt_entry->byte_4_pd_hop_st, V2_MPT_BYTE_4_PBL_HOP_NUM_M,
		       V2_MPT_BYTE_4_PBL_HOP_NUM_S,
		       mw->pbl_hop_num == HNS_ROCE_HOP_NUM_0 ? 0 :
							       mw->pbl_hop_num);
	roce_set_field(mpt_entry->byte_4_pd_hop_st,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_M,
		       V2_MPT_BYTE_4_PBL_BA_PG_SZ_S,
		       mw->pbl_ba_pg_sz + PG_SHIFT_OFFSET);

	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_R_INV_EN_S, 1);
	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_L_INV_EN_S, 1);
	roce_set_bit(mpt_entry->byte_8_mw_cnt_en, V2_MPT_BYTE_8_LW_EN_S, 1);

	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_PA_S, 0);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_MR_MW_S, 1);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_BPD_S, 1);
	roce_set_bit(mpt_entry->byte_12_mw_pa, V2_MPT_BYTE_12_BQP_S,
		     mw->ibmw.type == IB_MW_TYPE_1 ? 0 : 1);

	roce_set_field(mpt_entry->byte_64_buf_pa1,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_M,
		       V2_MPT_BYTE_64_PBL_BUF_PG_SZ_S,
		       mw->pbl_buf_pg_sz + PG_SHIFT_OFFSET);

	mpt_entry->lkey = cpu_to_le32(mw->rkey);

	वापस 0;
पूर्ण

अटल व्योम *get_cqe_v2(काष्ठा hns_roce_cq *hr_cq, पूर्णांक n)
अणु
	वापस hns_roce_buf_offset(hr_cq->mtr.kmem, n * hr_cq->cqe_size);
पूर्ण

अटल व्योम *get_sw_cqe_v2(काष्ठा hns_roce_cq *hr_cq, अचिन्हित पूर्णांक n)
अणु
	काष्ठा hns_roce_v2_cqe *cqe = get_cqe_v2(hr_cq, n & hr_cq->ib_cq.cqe);

	/* Get cqe when Owner bit is Conversely with the MSB of cons_idx */
	वापस (roce_get_bit(cqe->byte_4, V2_CQE_BYTE_4_OWNER_S) ^
		!!(n & hr_cq->cq_depth)) ? cqe : शून्य;
पूर्ण

अटल अंतरभूत व्योम update_cq_db(काष्ठा hns_roce_dev *hr_dev,
				काष्ठा hns_roce_cq *hr_cq)
अणु
	अगर (likely(hr_cq->flags & HNS_ROCE_CQ_FLAG_RECORD_DB)) अणु
		*hr_cq->set_ci_db = hr_cq->cons_index & V2_CQ_DB_CONS_IDX_M;
	पूर्ण अन्यथा अणु
		काष्ठा hns_roce_v2_db cq_db = अणुपूर्ण;

		roce_set_field(cq_db.byte_4, V2_DB_TAG_M, V2_DB_TAG_S,
			       hr_cq->cqn);
		roce_set_field(cq_db.byte_4, V2_DB_CMD_M, V2_DB_CMD_S,
			       HNS_ROCE_V2_CQ_DB);
		roce_set_field(cq_db.parameter, V2_CQ_DB_CONS_IDX_M,
			       V2_CQ_DB_CONS_IDX_S, hr_cq->cons_index);
		roce_set_field(cq_db.parameter, V2_CQ_DB_CMD_SN_M,
			       V2_CQ_DB_CMD_SN_S, 1);

		hns_roce_ग_लिखो64(hr_dev, (__le32 *)&cq_db, hr_cq->db_reg);
	पूर्ण
पूर्ण

अटल व्योम __hns_roce_v2_cq_clean(काष्ठा hns_roce_cq *hr_cq, u32 qpn,
				   काष्ठा hns_roce_srq *srq)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);
	काष्ठा hns_roce_v2_cqe *cqe, *dest;
	u32 prod_index;
	पूर्णांक nमुक्तd = 0;
	पूर्णांक wqe_index;
	u8 owner_bit;

	क्रम (prod_index = hr_cq->cons_index; get_sw_cqe_v2(hr_cq, prod_index);
	     ++prod_index) अणु
		अगर (prod_index > hr_cq->cons_index + hr_cq->ib_cq.cqe)
			अवरोध;
	पूर्ण

	/*
	 * Now backwards through the CQ, removing CQ entries
	 * that match our QP by overwriting them with next entries.
	 */
	जबतक ((पूर्णांक) --prod_index - (पूर्णांक) hr_cq->cons_index >= 0) अणु
		cqe = get_cqe_v2(hr_cq, prod_index & hr_cq->ib_cq.cqe);
		अगर ((roce_get_field(cqe->byte_16, V2_CQE_BYTE_16_LCL_QPN_M,
				    V2_CQE_BYTE_16_LCL_QPN_S) &
				    HNS_ROCE_V2_CQE_QPN_MASK) == qpn) अणु
			अगर (srq &&
			    roce_get_bit(cqe->byte_4, V2_CQE_BYTE_4_S_R_S)) अणु
				wqe_index = roce_get_field(cqe->byte_4,
						     V2_CQE_BYTE_4_WQE_INDX_M,
						     V2_CQE_BYTE_4_WQE_INDX_S);
				hns_roce_मुक्त_srq_wqe(srq, wqe_index);
			पूर्ण
			++nमुक्तd;
		पूर्ण अन्यथा अगर (nमुक्तd) अणु
			dest = get_cqe_v2(hr_cq, (prod_index + nमुक्तd) &
					  hr_cq->ib_cq.cqe);
			owner_bit = roce_get_bit(dest->byte_4,
						 V2_CQE_BYTE_4_OWNER_S);
			स_नकल(dest, cqe, माप(*cqe));
			roce_set_bit(dest->byte_4, V2_CQE_BYTE_4_OWNER_S,
				     owner_bit);
		पूर्ण
	पूर्ण

	अगर (nमुक्तd) अणु
		hr_cq->cons_index += nमुक्तd;
		update_cq_db(hr_dev, hr_cq);
	पूर्ण
पूर्ण

अटल व्योम hns_roce_v2_cq_clean(काष्ठा hns_roce_cq *hr_cq, u32 qpn,
				 काष्ठा hns_roce_srq *srq)
अणु
	spin_lock_irq(&hr_cq->lock);
	__hns_roce_v2_cq_clean(hr_cq, qpn, srq);
	spin_unlock_irq(&hr_cq->lock);
पूर्ण

अटल व्योम hns_roce_v2_ग_लिखो_cqc(काष्ठा hns_roce_dev *hr_dev,
				  काष्ठा hns_roce_cq *hr_cq, व्योम *mb_buf,
				  u64 *mtts, dma_addr_t dma_handle)
अणु
	काष्ठा hns_roce_v2_cq_context *cq_context;

	cq_context = mb_buf;
	स_रखो(cq_context, 0, माप(*cq_context));

	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_CQ_ST_M,
		       V2_CQC_BYTE_4_CQ_ST_S, V2_CQ_STATE_VALID);
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_ARM_ST_M,
		       V2_CQC_BYTE_4_ARM_ST_S, REG_NXT_CEQE);
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_SHIFT_M,
		       V2_CQC_BYTE_4_SHIFT_S, ilog2(hr_cq->cq_depth));
	roce_set_field(cq_context->byte_4_pg_ceqn, V2_CQC_BYTE_4_CEQN_M,
		       V2_CQC_BYTE_4_CEQN_S, hr_cq->vector);

	roce_set_field(cq_context->byte_8_cqn, V2_CQC_BYTE_8_CQN_M,
		       V2_CQC_BYTE_8_CQN_S, hr_cq->cqn);

	roce_set_field(cq_context->byte_8_cqn, V2_CQC_BYTE_8_CQE_SIZE_M,
		       V2_CQC_BYTE_8_CQE_SIZE_S, hr_cq->cqe_size ==
		       HNS_ROCE_V3_CQE_SIZE ? 1 : 0);

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_STASH)
		hr_reg_enable(cq_context, CQC_STASH);

	cq_context->cqe_cur_blk_addr = cpu_to_le32(to_hr_hw_page_addr(mtts[0]));

	roce_set_field(cq_context->byte_16_hop_addr,
		       V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_M,
		       V2_CQC_BYTE_16_CQE_CUR_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(mtts[0])));
	roce_set_field(cq_context->byte_16_hop_addr,
		       V2_CQC_BYTE_16_CQE_HOP_NUM_M,
		       V2_CQC_BYTE_16_CQE_HOP_NUM_S, hr_dev->caps.cqe_hop_num ==
		       HNS_ROCE_HOP_NUM_0 ? 0 : hr_dev->caps.cqe_hop_num);

	cq_context->cqe_nxt_blk_addr = cpu_to_le32(to_hr_hw_page_addr(mtts[1]));
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_M,
		       V2_CQC_BYTE_24_CQE_NXT_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(mtts[1])));
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_BA_PG_SZ_M,
		       V2_CQC_BYTE_24_CQE_BA_PG_SZ_S,
		       to_hr_hw_page_shअगरt(hr_cq->mtr.hem_cfg.ba_pg_shअगरt));
	roce_set_field(cq_context->byte_24_pgsz_addr,
		       V2_CQC_BYTE_24_CQE_BUF_PG_SZ_M,
		       V2_CQC_BYTE_24_CQE_BUF_PG_SZ_S,
		       to_hr_hw_page_shअगरt(hr_cq->mtr.hem_cfg.buf_pg_shअगरt));

	cq_context->cqe_ba = cpu_to_le32(dma_handle >> 3);

	roce_set_field(cq_context->byte_40_cqe_ba, V2_CQC_BYTE_40_CQE_BA_M,
		       V2_CQC_BYTE_40_CQE_BA_S, (dma_handle >> (32 + 3)));

	roce_set_bit(cq_context->byte_44_db_record,
		     V2_CQC_BYTE_44_DB_RECORD_EN_S,
		     (hr_cq->flags & HNS_ROCE_CQ_FLAG_RECORD_DB) ? 1 : 0);

	roce_set_field(cq_context->byte_44_db_record,
		       V2_CQC_BYTE_44_DB_RECORD_ADDR_M,
		       V2_CQC_BYTE_44_DB_RECORD_ADDR_S,
		       ((u32)hr_cq->db.dma) >> 1);
	cq_context->db_record_addr = cpu_to_le32(hr_cq->db.dma >> 32);

	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       HNS_ROCE_V2_CQ_DEFAULT_BURST_NUM);
	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M,
		       V2_CQC_BYTE_56_CQ_PERIOD_S,
		       HNS_ROCE_V2_CQ_DEFAULT_INTERVAL);
पूर्ण

अटल पूर्णांक hns_roce_v2_req_notअगरy_cq(काष्ठा ib_cq *ibcq,
				     क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibcq->device);
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	काष्ठा hns_roce_v2_db cq_db = अणुपूर्ण;
	u32 notअगरy_flag;

	/*
	 * flags = 0, then notअगरy_flag : next
	 * flags = 1, then notअगरy flag : solocited
	 */
	notअगरy_flag = (flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		      V2_CQ_DB_REQ_NOT : V2_CQ_DB_REQ_NOT_SOL;

	roce_set_field(cq_db.byte_4, V2_DB_TAG_M, V2_DB_TAG_S, hr_cq->cqn);
	roce_set_field(cq_db.byte_4, V2_DB_CMD_M, V2_DB_CMD_S,
		       HNS_ROCE_V2_CQ_DB_NOTIFY);
	roce_set_field(cq_db.parameter, V2_CQ_DB_CONS_IDX_M,
		       V2_CQ_DB_CONS_IDX_S, hr_cq->cons_index);
	roce_set_field(cq_db.parameter, V2_CQ_DB_CMD_SN_M,
		       V2_CQ_DB_CMD_SN_S, hr_cq->arm_sn);
	roce_set_bit(cq_db.parameter, V2_CQ_DB_NOTIFY_TYPE_S, notअगरy_flag);

	hns_roce_ग_लिखो64(hr_dev, (__le32 *)&cq_db, hr_cq->db_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_handle_recv_inl_wqe(काष्ठा hns_roce_v2_cqe *cqe,
					काष्ठा hns_roce_qp *qp,
					काष्ठा ib_wc *wc)
अणु
	काष्ठा hns_roce_rinl_sge *sge_list;
	u32 wr_num, wr_cnt, sge_num;
	u32 sge_cnt, data_len, size;
	व्योम *wqe_buf;

	wr_num = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_WQE_INDX_M,
				V2_CQE_BYTE_4_WQE_INDX_S) & 0xffff;
	wr_cnt = wr_num & (qp->rq.wqe_cnt - 1);

	sge_list = qp->rq_inl_buf.wqe_list[wr_cnt].sg_list;
	sge_num = qp->rq_inl_buf.wqe_list[wr_cnt].sge_cnt;
	wqe_buf = hns_roce_get_recv_wqe(qp, wr_cnt);
	data_len = wc->byte_len;

	क्रम (sge_cnt = 0; (sge_cnt < sge_num) && (data_len); sge_cnt++) अणु
		size = min(sge_list[sge_cnt].len, data_len);
		स_नकल((व्योम *)sge_list[sge_cnt].addr, wqe_buf, size);

		data_len -= size;
		wqe_buf += size;
	पूर्ण

	अगर (unlikely(data_len)) अणु
		wc->status = IB_WC_LOC_LEN_ERR;
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sw_comp(काष्ठा hns_roce_qp *hr_qp, काष्ठा hns_roce_wq *wq,
		   पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	अचिन्हित पूर्णांक left;
	पूर्णांक npolled = 0;

	left = wq->head - wq->tail;
	अगर (left == 0)
		वापस 0;

	left = min_t(अचिन्हित पूर्णांक, (अचिन्हित पूर्णांक)num_entries, left);
	जबतक (npolled < left) अणु
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->venकरोr_err = 0;
		wc->qp = &hr_qp->ibqp;

		wq->tail++;
		wc++;
		npolled++;
	पूर्ण

	वापस npolled;
पूर्ण

अटल पूर्णांक hns_roce_v2_sw_poll_cq(काष्ठा hns_roce_cq *hr_cq, पूर्णांक num_entries,
				  काष्ठा ib_wc *wc)
अणु
	काष्ठा hns_roce_qp *hr_qp;
	पूर्णांक npolled = 0;

	list_क्रम_each_entry(hr_qp, &hr_cq->sq_list, sq_node) अणु
		npolled += sw_comp(hr_qp, &hr_qp->sq,
				   num_entries - npolled, wc + npolled);
		अगर (npolled >= num_entries)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(hr_qp, &hr_cq->rq_list, rq_node) अणु
		npolled += sw_comp(hr_qp, &hr_qp->rq,
				   num_entries - npolled, wc + npolled);
		अगर (npolled >= num_entries)
			जाओ out;
	पूर्ण

out:
	वापस npolled;
पूर्ण

अटल व्योम get_cqe_status(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_qp *qp,
			   काष्ठा hns_roce_cq *cq, काष्ठा hns_roce_v2_cqe *cqe,
			   काष्ठा ib_wc *wc)
अणु
	अटल स्थिर काष्ठा अणु
		u32 cqe_status;
		क्रमागत ib_wc_status wc_status;
	पूर्ण map[] = अणु
		अणु HNS_ROCE_CQE_V2_SUCCESS, IB_WC_SUCCESS पूर्ण,
		अणु HNS_ROCE_CQE_V2_LOCAL_LENGTH_ERR, IB_WC_LOC_LEN_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_LOCAL_QP_OP_ERR, IB_WC_LOC_QP_OP_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_LOCAL_PROT_ERR, IB_WC_LOC_PROT_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_WR_FLUSH_ERR, IB_WC_WR_FLUSH_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_MW_BIND_ERR, IB_WC_MW_BIND_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_BAD_RESP_ERR, IB_WC_BAD_RESP_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_LOCAL_ACCESS_ERR, IB_WC_LOC_ACCESS_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_REMOTE_INVAL_REQ_ERR, IB_WC_REM_INV_REQ_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_REMOTE_ACCESS_ERR, IB_WC_REM_ACCESS_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_REMOTE_OP_ERR, IB_WC_REM_OP_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_TRANSPORT_RETRY_EXC_ERR,
		  IB_WC_RETRY_EXC_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_RNR_RETRY_EXC_ERR, IB_WC_RNR_RETRY_EXC_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_REMOTE_ABORT_ERR, IB_WC_REM_ABORT_ERR पूर्ण,
		अणु HNS_ROCE_CQE_V2_GENERAL_ERR, IB_WC_GENERAL_ERRपूर्ण
	पूर्ण;

	u32 cqe_status = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_STATUS_M,
					V2_CQE_BYTE_4_STATUS_S);
	पूर्णांक i;

	wc->status = IB_WC_GENERAL_ERR;
	क्रम (i = 0; i < ARRAY_SIZE(map); i++)
		अगर (cqe_status == map[i].cqe_status) अणु
			wc->status = map[i].wc_status;
			अवरोध;
		पूर्ण

	अगर (likely(wc->status == IB_WC_SUCCESS ||
		   wc->status == IB_WC_WR_FLUSH_ERR))
		वापस;

	ibdev_err(&hr_dev->ib_dev, "error cqe status 0x%x:\n", cqe_status);
	prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_NONE, 16, 4, cqe,
		       cq->cqe_size, false);

	/*
	 * For hns ROCEE, GENERAL_ERR is an error type that is not defined in
	 * the standard protocol, the driver must ignore it and needn't to set
	 * the QP to an error state.
	 */
	अगर (cqe_status == HNS_ROCE_CQE_V2_GENERAL_ERR)
		वापस;

	/*
	 * Hip08 hardware cannot flush the WQEs in SQ/RQ अगर the QP state माला_लो
	 * पूर्णांकo errored mode. Hence, as a workaround to this hardware
	 * limitation, driver needs to assist in flushing. But the flushing
	 * operation uses mailbox to convey the QP state to the hardware and
	 * which can sleep due to the mutex protection around the mailbox calls.
	 * Hence, use the deferred flush क्रम now. Once wc error detected, the
	 * flushing operation is needed.
	 */
	अगर (!test_and_set_bit(HNS_ROCE_FLUSH_FLAG, &qp->flush_flag))
		init_flush_work(hr_dev, qp);
पूर्ण

अटल पूर्णांक get_cur_qp(काष्ठा hns_roce_cq *hr_cq, काष्ठा hns_roce_v2_cqe *cqe,
		      काष्ठा hns_roce_qp **cur_qp)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);
	काष्ठा hns_roce_qp *hr_qp = *cur_qp;
	u32 qpn;

	qpn = roce_get_field(cqe->byte_16, V2_CQE_BYTE_16_LCL_QPN_M,
			     V2_CQE_BYTE_16_LCL_QPN_S) &
	      HNS_ROCE_V2_CQE_QPN_MASK;

	अगर (!hr_qp || qpn != hr_qp->qpn) अणु
		hr_qp = __hns_roce_qp_lookup(hr_dev, qpn);
		अगर (unlikely(!hr_qp)) अणु
			ibdev_err(&hr_dev->ib_dev,
				  "CQ %06lx with entry for unknown QPN %06x\n",
				  hr_cq->cqn, qpn);
			वापस -EINVAL;
		पूर्ण
		*cur_qp = hr_qp;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * mapped-value = 1 + real-value
 * The ib wc opcode's real value is start from 0, In order to distinguish
 * between initialized and uninitialized map values, we plus 1 to the actual
 * value when defining the mapping, so that the validity can be identअगरied by
 * checking whether the mapped value is greater than 0.
 */
#घोषणा HR_WC_OP_MAP(hr_key, ib_key) \
		[HNS_ROCE_V2_WQE_OP_ ## hr_key] = 1 + IB_WC_ ## ib_key

अटल स्थिर u32 wc_send_op_map[] = अणु
	HR_WC_OP_MAP(SEND,			SEND),
	HR_WC_OP_MAP(SEND_WITH_INV,		SEND),
	HR_WC_OP_MAP(SEND_WITH_IMM,		SEND),
	HR_WC_OP_MAP(RDMA_READ,			RDMA_READ),
	HR_WC_OP_MAP(RDMA_WRITE,		RDMA_WRITE),
	HR_WC_OP_MAP(RDMA_WRITE_WITH_IMM,	RDMA_WRITE),
	HR_WC_OP_MAP(LOCAL_INV,			LOCAL_INV),
	HR_WC_OP_MAP(ATOM_CMP_AND_SWAP,		COMP_SWAP),
	HR_WC_OP_MAP(ATOM_FETCH_AND_ADD,	FETCH_ADD),
	HR_WC_OP_MAP(ATOM_MSK_CMP_AND_SWAP,	MASKED_COMP_SWAP),
	HR_WC_OP_MAP(ATOM_MSK_FETCH_AND_ADD,	MASKED_FETCH_ADD),
	HR_WC_OP_MAP(FAST_REG_PMR,		REG_MR),
	HR_WC_OP_MAP(BIND_MW,			REG_MR),
पूर्ण;

अटल पूर्णांक to_ib_wc_send_op(u32 hr_opcode)
अणु
	अगर (hr_opcode >= ARRAY_SIZE(wc_send_op_map))
		वापस -EINVAL;

	वापस wc_send_op_map[hr_opcode] ? wc_send_op_map[hr_opcode] - 1 :
					   -EINVAL;
पूर्ण

अटल स्थिर u32 wc_recv_op_map[] = अणु
	HR_WC_OP_MAP(RDMA_WRITE_WITH_IMM,		WITH_IMM),
	HR_WC_OP_MAP(SEND,				RECV),
	HR_WC_OP_MAP(SEND_WITH_IMM,			WITH_IMM),
	HR_WC_OP_MAP(SEND_WITH_INV,			RECV),
पूर्ण;

अटल पूर्णांक to_ib_wc_recv_op(u32 hr_opcode)
अणु
	अगर (hr_opcode >= ARRAY_SIZE(wc_recv_op_map))
		वापस -EINVAL;

	वापस wc_recv_op_map[hr_opcode] ? wc_recv_op_map[hr_opcode] - 1 :
					   -EINVAL;
पूर्ण

अटल व्योम fill_send_wc(काष्ठा ib_wc *wc, काष्ठा hns_roce_v2_cqe *cqe)
अणु
	u32 hr_opcode;
	पूर्णांक ib_opcode;

	wc->wc_flags = 0;

	hr_opcode = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_OPCODE_M,
				   V2_CQE_BYTE_4_OPCODE_S) & 0x1f;
	चयन (hr_opcode) अणु
	हाल HNS_ROCE_V2_WQE_OP_RDMA_READ:
		wc->byte_len = le32_to_cpu(cqe->byte_cnt);
		अवरोध;
	हाल HNS_ROCE_V2_WQE_OP_SEND_WITH_IMM:
	हाल HNS_ROCE_V2_WQE_OP_RDMA_WRITE_WITH_IMM:
		wc->wc_flags |= IB_WC_WITH_IMM;
		अवरोध;
	हाल HNS_ROCE_V2_WQE_OP_LOCAL_INV:
		wc->wc_flags |= IB_WC_WITH_INVALIDATE;
		अवरोध;
	हाल HNS_ROCE_V2_WQE_OP_ATOM_CMP_AND_SWAP:
	हाल HNS_ROCE_V2_WQE_OP_ATOM_FETCH_AND_ADD:
	हाल HNS_ROCE_V2_WQE_OP_ATOM_MSK_CMP_AND_SWAP:
	हाल HNS_ROCE_V2_WQE_OP_ATOM_MSK_FETCH_AND_ADD:
		wc->byte_len  = 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ib_opcode = to_ib_wc_send_op(hr_opcode);
	अगर (ib_opcode < 0)
		wc->status = IB_WC_GENERAL_ERR;
	अन्यथा
		wc->opcode = ib_opcode;
पूर्ण

अटल अंतरभूत bool is_rq_inl_enabled(काष्ठा ib_wc *wc, u32 hr_opcode,
				     काष्ठा hns_roce_v2_cqe *cqe)
अणु
	वापस wc->qp->qp_type != IB_QPT_UD &&
	       wc->qp->qp_type != IB_QPT_GSI &&
	       (hr_opcode == HNS_ROCE_V2_OPCODE_SEND ||
		hr_opcode == HNS_ROCE_V2_OPCODE_SEND_WITH_IMM ||
		hr_opcode == HNS_ROCE_V2_OPCODE_SEND_WITH_INV) &&
	       roce_get_bit(cqe->byte_4, V2_CQE_BYTE_4_RQ_INLINE_S);
पूर्ण

अटल पूर्णांक fill_recv_wc(काष्ठा ib_wc *wc, काष्ठा hns_roce_v2_cqe *cqe)
अणु
	काष्ठा hns_roce_qp *qp = to_hr_qp(wc->qp);
	u32 hr_opcode;
	पूर्णांक ib_opcode;
	पूर्णांक ret;

	wc->byte_len = le32_to_cpu(cqe->byte_cnt);

	hr_opcode = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_OPCODE_M,
				   V2_CQE_BYTE_4_OPCODE_S) & 0x1f;
	चयन (hr_opcode) अणु
	हाल HNS_ROCE_V2_OPCODE_RDMA_WRITE_IMM:
	हाल HNS_ROCE_V2_OPCODE_SEND_WITH_IMM:
		wc->wc_flags = IB_WC_WITH_IMM;
		wc->ex.imm_data = cpu_to_be32(le32_to_cpu(cqe->immtdata));
		अवरोध;
	हाल HNS_ROCE_V2_OPCODE_SEND_WITH_INV:
		wc->wc_flags = IB_WC_WITH_INVALIDATE;
		wc->ex.invalidate_rkey = le32_to_cpu(cqe->rkey);
		अवरोध;
	शेष:
		wc->wc_flags = 0;
	पूर्ण

	ib_opcode = to_ib_wc_recv_op(hr_opcode);
	अगर (ib_opcode < 0)
		wc->status = IB_WC_GENERAL_ERR;
	अन्यथा
		wc->opcode = ib_opcode;

	अगर (is_rq_inl_enabled(wc, hr_opcode, cqe)) अणु
		ret = hns_roce_handle_recv_inl_wqe(cqe, qp, wc);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण

	wc->sl = roce_get_field(cqe->byte_32, V2_CQE_BYTE_32_SL_M,
				V2_CQE_BYTE_32_SL_S);
	wc->src_qp = roce_get_field(cqe->byte_32, V2_CQE_BYTE_32_RMT_QPN_M,
				    V2_CQE_BYTE_32_RMT_QPN_S);
	wc->slid = 0;
	wc->wc_flags |= roce_get_bit(cqe->byte_32, V2_CQE_BYTE_32_GRH_S) ?
				     IB_WC_GRH : 0;
	wc->port_num = roce_get_field(cqe->byte_32, V2_CQE_BYTE_32_PORTN_M,
				      V2_CQE_BYTE_32_PORTN_S);
	wc->pkey_index = 0;

	अगर (roce_get_bit(cqe->byte_28, V2_CQE_BYTE_28_VID_VLD_S)) अणु
		wc->vlan_id = roce_get_field(cqe->byte_28, V2_CQE_BYTE_28_VID_M,
					     V2_CQE_BYTE_28_VID_S);
		wc->wc_flags |= IB_WC_WITH_VLAN;
	पूर्ण अन्यथा अणु
		wc->vlan_id = 0xffff;
	पूर्ण

	wc->network_hdr_type = roce_get_field(cqe->byte_28,
					      V2_CQE_BYTE_28_PORT_TYPE_M,
					      V2_CQE_BYTE_28_PORT_TYPE_S);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_poll_one(काष्ठा hns_roce_cq *hr_cq,
				काष्ठा hns_roce_qp **cur_qp, काष्ठा ib_wc *wc)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(hr_cq->ib_cq.device);
	काष्ठा hns_roce_qp *qp = *cur_qp;
	काष्ठा hns_roce_srq *srq = शून्य;
	काष्ठा hns_roce_v2_cqe *cqe;
	काष्ठा hns_roce_wq *wq;
	पूर्णांक is_send;
	u16 wqe_idx;
	पूर्णांक ret;

	cqe = get_sw_cqe_v2(hr_cq, hr_cq->cons_index);
	अगर (!cqe)
		वापस -EAGAIN;

	++hr_cq->cons_index;
	/* Memory barrier */
	rmb();

	ret = get_cur_qp(hr_cq, cqe, &qp);
	अगर (ret)
		वापस ret;

	wc->qp = &qp->ibqp;
	wc->venकरोr_err = 0;

	wqe_idx = roce_get_field(cqe->byte_4, V2_CQE_BYTE_4_WQE_INDX_M,
				 V2_CQE_BYTE_4_WQE_INDX_S);

	is_send = !roce_get_bit(cqe->byte_4, V2_CQE_BYTE_4_S_R_S);
	अगर (is_send) अणु
		wq = &qp->sq;

		/* If sg_संकेत_bit is set, tail poपूर्णांकer will be updated to
		 * the WQE corresponding to the current CQE.
		 */
		अगर (qp->sq_संकेत_bits)
			wq->tail += (wqe_idx - (u16)wq->tail) &
				    (wq->wqe_cnt - 1);

		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		++wq->tail;

		fill_send_wc(wc, cqe);
	पूर्ण अन्यथा अणु
		अगर (qp->ibqp.srq) अणु
			srq = to_hr_srq(qp->ibqp.srq);
			wc->wr_id = srq->wrid[wqe_idx];
			hns_roce_मुक्त_srq_wqe(srq, wqe_idx);
		पूर्ण अन्यथा अणु
			wq = &qp->rq;
			wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
			++wq->tail;
		पूर्ण

		ret = fill_recv_wc(wc, cqe);
	पूर्ण

	get_cqe_status(hr_dev, qp, hr_cq, cqe, wc);
	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		वापस 0;

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries,
			       काष्ठा ib_wc *wc)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibcq->device);
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ibcq);
	काष्ठा hns_roce_qp *cur_qp = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;

	spin_lock_irqsave(&hr_cq->lock, flags);

	/*
	 * When the device starts to reset, the state is RST_DOWN. At this समय,
	 * there may still be some valid CQEs in the hardware that are not
	 * polled. Thereक्रमe, it is not allowed to चयन to the software mode
	 * immediately. When the state changes to UNINIT, CQE no दीर्घer exists
	 * in the hardware, and then चयन to software mode.
	 */
	अगर (hr_dev->state == HNS_ROCE_DEVICE_STATE_UNINIT) अणु
		npolled = hns_roce_v2_sw_poll_cq(hr_cq, num_entries, wc);
		जाओ out;
	पूर्ण

	क्रम (npolled = 0; npolled < num_entries; ++npolled) अणु
		अगर (hns_roce_v2_poll_one(hr_cq, &cur_qp, wc + npolled))
			अवरोध;
	पूर्ण

	अगर (npolled)
		update_cq_db(hr_dev, hr_cq);

out:
	spin_unlock_irqrestore(&hr_cq->lock, flags);

	वापस npolled;
पूर्ण

अटल पूर्णांक get_op_क्रम_set_hem(काष्ठा hns_roce_dev *hr_dev, u32 type,
			      पूर्णांक step_idx, u16 *mbox_op)
अणु
	u16 op;

	चयन (type) अणु
	हाल HEM_TYPE_QPC:
		op = HNS_ROCE_CMD_WRITE_QPC_BT0;
		अवरोध;
	हाल HEM_TYPE_MTPT:
		op = HNS_ROCE_CMD_WRITE_MPT_BT0;
		अवरोध;
	हाल HEM_TYPE_CQC:
		op = HNS_ROCE_CMD_WRITE_CQC_BT0;
		अवरोध;
	हाल HEM_TYPE_SRQC:
		op = HNS_ROCE_CMD_WRITE_SRQC_BT0;
		अवरोध;
	हाल HEM_TYPE_SCCC:
		op = HNS_ROCE_CMD_WRITE_SCCC_BT0;
		अवरोध;
	हाल HEM_TYPE_QPC_TIMER:
		op = HNS_ROCE_CMD_WRITE_QPC_TIMER_BT0;
		अवरोध;
	हाल HEM_TYPE_CQC_TIMER:
		op = HNS_ROCE_CMD_WRITE_CQC_TIMER_BT0;
		अवरोध;
	शेष:
		dev_warn(hr_dev->dev, "failed to check hem type %u.\n", type);
		वापस -EINVAL;
	पूर्ण

	*mbox_op = op + step_idx;

	वापस 0;
पूर्ण

अटल पूर्णांक config_gmv_ba_to_hw(काष्ठा hns_roce_dev *hr_dev, अचिन्हित दीर्घ obj,
			       dma_addr_t base_addr)
अणु
	काष्ठा hns_roce_cmq_desc desc;
	काष्ठा hns_roce_cmq_req *req = (काष्ठा hns_roce_cmq_req *)desc.data;
	u32 idx = obj / (HNS_HW_PAGE_SIZE / hr_dev->caps.gmv_entry_sz);
	u64 addr = to_hr_hw_page_addr(base_addr);

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_GMV_BT, false);

	hr_reg_ग_लिखो(req, CFG_GMV_BT_BA_L, lower_32_bits(addr));
	hr_reg_ग_लिखो(req, CFG_GMV_BT_BA_H, upper_32_bits(addr));
	hr_reg_ग_लिखो(req, CFG_GMV_BT_IDX, idx);

	वापस hns_roce_cmq_send(hr_dev, &desc, 1);
पूर्ण

अटल पूर्णांक set_hem_to_hw(काष्ठा hns_roce_dev *hr_dev, पूर्णांक obj,
			 dma_addr_t base_addr, u32 hem_type, पूर्णांक step_idx)
अणु
	पूर्णांक ret;
	u16 op;

	अगर (unlikely(hem_type == HEM_TYPE_GMV))
		वापस config_gmv_ba_to_hw(hr_dev, obj, base_addr);

	अगर (unlikely(hem_type == HEM_TYPE_SCCC && step_idx))
		वापस 0;

	ret = get_op_क्रम_set_hem(hr_dev, hem_type, step_idx, &op);
	अगर (ret < 0)
		वापस ret;

	वापस config_hem_ba_to_hw(hr_dev, obj, base_addr, op);
पूर्ण

अटल पूर्णांक hns_roce_v2_set_hem(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_hem_table *table, पूर्णांक obj,
			       पूर्णांक step_idx)
अणु
	काष्ठा hns_roce_hem_iter iter;
	काष्ठा hns_roce_hem_mhop mhop;
	काष्ठा hns_roce_hem *hem;
	अचिन्हित दीर्घ mhop_obj = obj;
	पूर्णांक i, j, k;
	पूर्णांक ret = 0;
	u64 hem_idx = 0;
	u64 l1_idx = 0;
	u64 bt_ba = 0;
	u32 chunk_ba_num;
	u32 hop_num;

	अगर (!hns_roce_check_whether_mhop(hr_dev, table->type))
		वापस 0;

	hns_roce_calc_hem_mhop(hr_dev, table, &mhop_obj, &mhop);
	i = mhop.l0_idx;
	j = mhop.l1_idx;
	k = mhop.l2_idx;
	hop_num = mhop.hop_num;
	chunk_ba_num = mhop.bt_chunk_size / 8;

	अगर (hop_num == 2) अणु
		hem_idx = i * chunk_ba_num * chunk_ba_num + j * chunk_ba_num +
			  k;
		l1_idx = i * chunk_ba_num + j;
	पूर्ण अन्यथा अगर (hop_num == 1) अणु
		hem_idx = i * chunk_ba_num + j;
	पूर्ण अन्यथा अगर (hop_num == HNS_ROCE_HOP_NUM_0) अणु
		hem_idx = i;
	पूर्ण

	अगर (table->type == HEM_TYPE_SCCC)
		obj = mhop.l0_idx;

	अगर (check_whether_last_step(hop_num, step_idx)) अणु
		hem = table->hem[hem_idx];
		क्रम (hns_roce_hem_first(hem, &iter);
		     !hns_roce_hem_last(&iter); hns_roce_hem_next(&iter)) अणु
			bt_ba = hns_roce_hem_addr(&iter);
			ret = set_hem_to_hw(hr_dev, obj, bt_ba, table->type,
					    step_idx);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (step_idx == 0)
			bt_ba = table->bt_l0_dma_addr[i];
		अन्यथा अगर (step_idx == 1 && hop_num == 2)
			bt_ba = table->bt_l1_dma_addr[l1_idx];

		ret = set_hem_to_hw(hr_dev, obj, bt_ba, table->type, step_idx);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_clear_hem(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_hem_table *table, पूर्णांक obj,
				 पूर्णांक step_idx)
अणु
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;
	u16 op = 0xff;

	अगर (!hns_roce_check_whether_mhop(hr_dev, table->type))
		वापस 0;

	चयन (table->type) अणु
	हाल HEM_TYPE_QPC:
		op = HNS_ROCE_CMD_DESTROY_QPC_BT0;
		अवरोध;
	हाल HEM_TYPE_MTPT:
		op = HNS_ROCE_CMD_DESTROY_MPT_BT0;
		अवरोध;
	हाल HEM_TYPE_CQC:
		op = HNS_ROCE_CMD_DESTROY_CQC_BT0;
		अवरोध;
	हाल HEM_TYPE_SRQC:
		op = HNS_ROCE_CMD_DESTROY_SRQC_BT0;
		अवरोध;
	हाल HEM_TYPE_SCCC:
	हाल HEM_TYPE_QPC_TIMER:
	हाल HEM_TYPE_CQC_TIMER:
	हाल HEM_TYPE_GMV:
		वापस 0;
	शेष:
		dev_warn(dev, "table %u not to be destroyed by mailbox!\n",
			 table->type);
		वापस 0;
	पूर्ण

	op += step_idx;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	/* configure the tag and op */
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, obj, 0, op,
				HNS_ROCE_CMD_TIMEOUT_MSECS);

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_qp_modअगरy(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_v2_qp_context *context,
				 काष्ठा hns_roce_v2_qp_context *qpc_mask,
				 काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक qpc_size;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	/* The qpc size of HIP08 is only 256B, which is half of HIP09 */
	qpc_size = hr_dev->caps.qpc_sz;
	स_नकल(mailbox->buf, context, qpc_size);
	स_नकल(mailbox->buf + qpc_size, qpc_mask, qpc_size);

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, hr_qp->qpn, 0,
				HNS_ROCE_CMD_MODIFY_QPC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ret;
पूर्ण

अटल व्योम set_access_flags(काष्ठा hns_roce_qp *hr_qp,
			     काष्ठा hns_roce_v2_qp_context *context,
			     काष्ठा hns_roce_v2_qp_context *qpc_mask,
			     स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask)
अणु
	u8 dest_rd_atomic;
	u32 access_flags;

	dest_rd_atomic = (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) ?
			 attr->max_dest_rd_atomic : hr_qp->resp_depth;

	access_flags = (attr_mask & IB_QP_ACCESS_FLAGS) ?
		       attr->qp_access_flags : hr_qp->atomic_rd_en;

	अगर (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_READ));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S, 0);

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_WRITE));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S, 0);

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_ATOMIC));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S, 0);
	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_EXT_ATE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_ATOMIC));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_EXT_ATE_S, 0);
पूर्ण

अटल व्योम set_qpc_wqe_cnt(काष्ठा hns_roce_qp *hr_qp,
			    काष्ठा hns_roce_v2_qp_context *context,
			    काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	roce_set_field(context->byte_4_sqpn_tst,
		       V2_QPC_BYTE_4_SGE_SHIFT_M, V2_QPC_BYTE_4_SGE_SHIFT_S,
		       to_hr_hem_entries_shअगरt(hr_qp->sge.sge_cnt,
					       hr_qp->sge.sge_shअगरt));

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S,
		       ilog2(hr_qp->sq.wqe_cnt));

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S,
		       ilog2(hr_qp->rq.wqe_cnt));
पूर्ण

अटल अंतरभूत पूर्णांक get_cqn(काष्ठा ib_cq *ib_cq)
अणु
	वापस ib_cq ? to_hr_cq(ib_cq)->cqn : 0;
पूर्ण

अटल अंतरभूत पूर्णांक get_pdn(काष्ठा ib_pd *ib_pd)
अणु
	वापस ib_pd ? to_hr_pd(ib_pd)->pdn : 0;
पूर्ण

अटल व्योम modअगरy_qp_reset_to_init(काष्ठा ib_qp *ibqp,
				    स्थिर काष्ठा ib_qp_attr *attr,
				    पूर्णांक attr_mask,
				    काष्ठा hns_roce_v2_qp_context *context,
				    काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modअगरying qp. If software need modअगरy some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same समय, अन्यथा set them to 0x1.
	 */
	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, to_hr_qp_type(ibqp->qp_type));

	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, hr_qp->qpn);

	roce_set_field(context->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, get_pdn(ibqp->pd));

	roce_set_field(context->byte_20_smac_sgid_idx, V2_QPC_BYTE_20_RQWS_M,
		       V2_QPC_BYTE_20_RQWS_S, ilog2(hr_qp->rq.max_gs));

	set_qpc_wqe_cnt(hr_qp, context, qpc_mask);

	/* No VLAN need to set 0xFFF */
	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, 0xfff);

	अगर (ibqp->qp_type == IB_QPT_XRC_TGT) अणु
		context->qkey_xrcd = cpu_to_le32(hr_qp->xrcdn);

		roce_set_bit(context->byte_80_rnr_rx_cqn,
			     V2_QPC_BYTE_80_XRC_QP_TYPE_S, 1);
	पूर्ण

	अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)
		roce_set_bit(context->byte_68_rq_db,
			     V2_QPC_BYTE_68_RQ_RECORD_EN_S, 1);

	roce_set_field(context->byte_68_rq_db,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_M,
		       V2_QPC_BYTE_68_RQ_DB_RECORD_ADDR_S,
		       ((u32)hr_qp->rdb.dma) >> 1);
	context->rq_db_record_addr = cpu_to_le32(hr_qp->rdb.dma >> 32);

	अगर (ibqp->qp_type != IB_QPT_UD && ibqp->qp_type != IB_QPT_GSI)
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_RQIE_S,
			     !!(hr_dev->caps.flags &
				HNS_ROCE_CAP_FLAG_RQ_INLINE));

	roce_set_field(context->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, get_cqn(ibqp->recv_cq));

	अगर (ibqp->srq) अणु
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 1);
		roce_set_field(context->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S,
			       to_hr_srq(ibqp->srq)->srqn);
	पूर्ण

	roce_set_bit(context->byte_172_sq_psn, V2_QPC_BYTE_172_FRE_S, 1);

	roce_set_field(context->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, get_cqn(ibqp->send_cq));

	अगर (hr_dev->caps.qpc_sz < HNS_ROCE_V3_QPC_SZ)
		वापस;

	अगर (hr_dev->caps.flags & HNS_ROCE_CAP_FLAG_STASH)
		hr_reg_enable(&context->ext, QPCEX_STASH);
पूर्ण

अटल व्योम modअगरy_qp_init_to_init(काष्ठा ib_qp *ibqp,
				   स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
				   काष्ठा hns_roce_v2_qp_context *context,
				   काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modअगरying qp. If software need modअगरy some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same समय, अन्यथा set them to 0x1.
	 */
	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, to_hr_qp_type(ibqp->qp_type));
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, get_pdn(ibqp->pd));

	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, 0);

	roce_set_field(context->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, get_cqn(ibqp->recv_cq));
	roce_set_field(qpc_mask->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, 0);

	roce_set_field(context->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, get_cqn(ibqp->send_cq));
	roce_set_field(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, 0);

	अगर (ibqp->srq) अणु
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 1);
		roce_set_bit(qpc_mask->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 0);
		roce_set_field(context->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S,
			       to_hr_srq(ibqp->srq)->srqn);
		roce_set_field(qpc_mask->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S, 0);
	पूर्ण

	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, hr_qp->qpn);
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, 0);

	अगर (attr_mask & IB_QP_DEST_QPN) अणु
		roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_DQPN_M,
			       V2_QPC_BYTE_56_DQPN_S, hr_qp->qpn);
		roce_set_field(qpc_mask->byte_56_dqpn_err,
			       V2_QPC_BYTE_56_DQPN_M, V2_QPC_BYTE_56_DQPN_S, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक config_qp_rq_buf(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_qp *hr_qp,
			    काष्ठा hns_roce_v2_qp_context *context,
			    काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	u64 mtts[MTT_MIN_COUNT] = अणु 0 पूर्ण;
	u64 wqe_sge_ba;
	पूर्णांक count;

	/* Search qp buf's mtts */
	count = hns_roce_mtr_find(hr_dev, &hr_qp->mtr, hr_qp->rq.offset, mtts,
				  MTT_MIN_COUNT, &wqe_sge_ba);
	अगर (hr_qp->rq.wqe_cnt && count < 1) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "failed to find RQ WQE, QPN = 0x%lx.\n", hr_qp->qpn);
		वापस -EINVAL;
	पूर्ण

	context->wqe_sge_ba = cpu_to_le32(wqe_sge_ba >> 3);
	qpc_mask->wqe_sge_ba = 0;

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modअगरying qp. If software need modअगरy some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same समय, अन्यथा set them to 0x1.
	 */
	roce_set_field(context->byte_12_sq_hop, V2_QPC_BYTE_12_WQE_SGE_BA_M,
		       V2_QPC_BYTE_12_WQE_SGE_BA_S, wqe_sge_ba >> (32 + 3));
	roce_set_field(qpc_mask->byte_12_sq_hop, V2_QPC_BYTE_12_WQE_SGE_BA_M,
		       V2_QPC_BYTE_12_WQE_SGE_BA_S, 0);

	roce_set_field(context->byte_12_sq_hop, V2_QPC_BYTE_12_SQ_HOP_NUM_M,
		       V2_QPC_BYTE_12_SQ_HOP_NUM_S,
		       to_hr_hem_hopnum(hr_dev->caps.wqe_sq_hop_num,
					hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_12_sq_hop, V2_QPC_BYTE_12_SQ_HOP_NUM_M,
		       V2_QPC_BYTE_12_SQ_HOP_NUM_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_M,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_S,
		       to_hr_hem_hopnum(hr_dev->caps.wqe_sge_hop_num,
					hr_qp->sge.sge_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_M,
		       V2_QPC_BYTE_20_SGE_HOP_NUM_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_M,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_S,
		       to_hr_hem_hopnum(hr_dev->caps.wqe_rq_hop_num,
					hr_qp->rq.wqe_cnt));

	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_M,
		       V2_QPC_BYTE_20_RQ_HOP_NUM_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_S,
		       to_hr_hw_page_shअगरt(hr_qp->mtr.hem_cfg.ba_pg_shअगरt));
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BA_PG_SZ_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_S,
		       to_hr_hw_page_shअगरt(hr_qp->mtr.hem_cfg.buf_pg_shअगरt));
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_M,
		       V2_QPC_BYTE_16_WQE_SGE_BUF_PG_SZ_S, 0);

	context->rq_cur_blk_addr = cpu_to_le32(to_hr_hw_page_addr(mtts[0]));
	qpc_mask->rq_cur_blk_addr = 0;

	roce_set_field(context->byte_92_srq_info,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(mtts[0])));
	roce_set_field(qpc_mask->byte_92_srq_info,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_92_RQ_CUR_BLK_ADDR_S, 0);

	context->rq_nxt_blk_addr = cpu_to_le32(to_hr_hw_page_addr(mtts[1]));
	qpc_mask->rq_nxt_blk_addr = 0;

	roce_set_field(context->byte_104_rq_sge,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_M,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(mtts[1])));
	roce_set_field(qpc_mask->byte_104_rq_sge,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_M,
		       V2_QPC_BYTE_104_RQ_NXT_BLK_ADDR_S, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक config_qp_sq_buf(काष्ठा hns_roce_dev *hr_dev,
			    काष्ठा hns_roce_qp *hr_qp,
			    काष्ठा hns_roce_v2_qp_context *context,
			    काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	u64 sge_cur_blk = 0;
	u64 sq_cur_blk = 0;
	पूर्णांक count;

	/* search qp buf's mtts */
	count = hns_roce_mtr_find(hr_dev, &hr_qp->mtr, 0, &sq_cur_blk, 1, शून्य);
	अगर (count < 1) अणु
		ibdev_err(ibdev, "failed to find QP(0x%lx) SQ buf.\n",
			  hr_qp->qpn);
		वापस -EINVAL;
	पूर्ण
	अगर (hr_qp->sge.sge_cnt > 0) अणु
		count = hns_roce_mtr_find(hr_dev, &hr_qp->mtr,
					  hr_qp->sge.offset,
					  &sge_cur_blk, 1, शून्य);
		अगर (count < 1) अणु
			ibdev_err(ibdev, "failed to find QP(0x%lx) SGE buf.\n",
				  hr_qp->qpn);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modअगरying qp. If software need modअगरy some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same समय, अन्यथा set them to 0x1.
	 */
	context->sq_cur_blk_addr = cpu_to_le32(to_hr_hw_page_addr(sq_cur_blk));
	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(sq_cur_blk)));
	qpc_mask->sq_cur_blk_addr = 0;
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_168_SQ_CUR_BLK_ADDR_S, 0);

	context->sq_cur_sge_blk_addr =
		cpu_to_le32(to_hr_hw_page_addr(sge_cur_blk));
	roce_set_field(context->byte_184_irrl_idx,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_M,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(sge_cur_blk)));
	qpc_mask->sq_cur_sge_blk_addr = 0;
	roce_set_field(qpc_mask->byte_184_irrl_idx,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_M,
		       V2_QPC_BYTE_184_SQ_CUR_SGE_BLK_ADDR_S, 0);

	context->rx_sq_cur_blk_addr =
		cpu_to_le32(to_hr_hw_page_addr(sq_cur_blk));
	roce_set_field(context->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_S,
		       upper_32_bits(to_hr_hw_page_addr(sq_cur_blk)));
	qpc_mask->rx_sq_cur_blk_addr = 0;
	roce_set_field(qpc_mask->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_M,
		       V2_QPC_BYTE_232_RX_SQ_CUR_BLK_ADDR_S, 0);

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत ib_mtu get_mtu(काष्ठा ib_qp *ibqp,
				  स्थिर काष्ठा ib_qp_attr *attr)
अणु
	अगर (ibqp->qp_type == IB_QPT_GSI || ibqp->qp_type == IB_QPT_UD)
		वापस IB_MTU_4096;

	वापस attr->path_mtu;
पूर्ण

अटल पूर्णांक modअगरy_qp_init_to_rtr(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
				 काष्ठा hns_roce_v2_qp_context *context,
				 काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	dma_addr_t trrl_ba;
	dma_addr_t irrl_ba;
	क्रमागत ib_mtu mtu;
	u8 lp_pktn_ini;
	u64 *mtts;
	u8 *dmac;
	u8 *smac;
	u32 port;
	पूर्णांक ret;

	ret = config_qp_rq_buf(hr_dev, hr_qp, context, qpc_mask);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to config rq buf, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/* Search IRRL's mtts */
	mtts = hns_roce_table_find(hr_dev, &hr_dev->qp_table.irrl_table,
				   hr_qp->qpn, &irrl_ba);
	अगर (!mtts) अणु
		ibdev_err(ibdev, "failed to find qp irrl_table.\n");
		वापस -EINVAL;
	पूर्ण

	/* Search TRRL's mtts */
	mtts = hns_roce_table_find(hr_dev, &hr_dev->qp_table.trrl_table,
				   hr_qp->qpn, &trrl_ba);
	अगर (!mtts) अणु
		ibdev_err(ibdev, "failed to find qp trrl_table.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		ibdev_err(ibdev, "INIT2RTR attr_mask (0x%x) error.\n",
			  attr_mask);
		वापस -EINVAL;
	पूर्ण

	roce_set_field(context->byte_132_trrl, V2_QPC_BYTE_132_TRRL_BA_M,
		       V2_QPC_BYTE_132_TRRL_BA_S, trrl_ba >> 4);
	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_BA_M,
		       V2_QPC_BYTE_132_TRRL_BA_S, 0);
	context->trrl_ba = cpu_to_le32(trrl_ba >> (16 + 4));
	qpc_mask->trrl_ba = 0;
	roce_set_field(context->byte_140_raq, V2_QPC_BYTE_140_TRRL_BA_M,
		       V2_QPC_BYTE_140_TRRL_BA_S,
		       (u32)(trrl_ba >> (32 + 16 + 4)));
	roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_TRRL_BA_M,
		       V2_QPC_BYTE_140_TRRL_BA_S, 0);

	context->irrl_ba = cpu_to_le32(irrl_ba >> 6);
	qpc_mask->irrl_ba = 0;
	roce_set_field(context->byte_208_irrl, V2_QPC_BYTE_208_IRRL_BA_M,
		       V2_QPC_BYTE_208_IRRL_BA_S,
		       irrl_ba >> (32 + 6));
	roce_set_field(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_IRRL_BA_M,
		       V2_QPC_BYTE_208_IRRL_BA_S, 0);

	roce_set_bit(context->byte_208_irrl, V2_QPC_BYTE_208_RMT_E2E_S, 1);
	roce_set_bit(qpc_mask->byte_208_irrl, V2_QPC_BYTE_208_RMT_E2E_S, 0);

	roce_set_bit(context->byte_252_err_txcqn, V2_QPC_BYTE_252_SIG_TYPE_S,
		     hr_qp->sq_संकेत_bits);
	roce_set_bit(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_SIG_TYPE_S,
		     0);

	port = (attr_mask & IB_QP_PORT) ? (attr->port_num - 1) : hr_qp->port;

	smac = (u8 *)hr_dev->dev_addr[port];
	dmac = (u8 *)attr->ah_attr.roce.dmac;
	/* when dmac equals smac or loop_idc is 1, it should loopback */
	अगर (ether_addr_equal_unaligned(dmac, smac) ||
	    hr_dev->loop_idc == 0x1) अणु
		roce_set_bit(context->byte_28_at_fl, V2_QPC_BYTE_28_LBI_S, 1);
		roce_set_bit(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_LBI_S, 0);
	पूर्ण

	अगर (attr_mask & IB_QP_DEST_QPN) अणु
		roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_DQPN_M,
			       V2_QPC_BYTE_56_DQPN_S, attr->dest_qp_num);
		roce_set_field(qpc_mask->byte_56_dqpn_err,
			       V2_QPC_BYTE_56_DQPN_M, V2_QPC_BYTE_56_DQPN_S, 0);
	पूर्ण

	स_नकल(&(context->dmac), dmac, माप(u32));
	roce_set_field(context->byte_52_udpspn_dmac, V2_QPC_BYTE_52_DMAC_M,
		       V2_QPC_BYTE_52_DMAC_S, *((u16 *)(&dmac[4])));
	qpc_mask->dmac = 0;
	roce_set_field(qpc_mask->byte_52_udpspn_dmac, V2_QPC_BYTE_52_DMAC_M,
		       V2_QPC_BYTE_52_DMAC_S, 0);

	mtu = get_mtu(ibqp, attr);
	hr_qp->path_mtu = mtu;

	अगर (attr_mask & IB_QP_PATH_MTU) अणु
		roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_MTU_M,
			       V2_QPC_BYTE_24_MTU_S, mtu);
		roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_MTU_M,
			       V2_QPC_BYTE_24_MTU_S, 0);
	पूर्ण

#घोषणा MAX_LP_MSG_LEN 65536
	/* MTU * (2 ^ LP_PKTN_INI) shouldn't be bigger than 64KB */
	lp_pktn_ini = ilog2(MAX_LP_MSG_LEN / ib_mtu_क्रमागत_to_पूर्णांक(mtu));

	roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_LP_PKTN_INI_M,
		       V2_QPC_BYTE_56_LP_PKTN_INI_S, lp_pktn_ini);
	roce_set_field(qpc_mask->byte_56_dqpn_err, V2_QPC_BYTE_56_LP_PKTN_INI_M,
		       V2_QPC_BYTE_56_LP_PKTN_INI_S, 0);

	/* ACK_REQ_FREQ should be larger than or equal to LP_PKTN_INI */
	roce_set_field(context->byte_172_sq_psn, V2_QPC_BYTE_172_ACK_REQ_FREQ_M,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_S, lp_pktn_ini);
	roce_set_field(qpc_mask->byte_172_sq_psn,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_M,
		       V2_QPC_BYTE_172_ACK_REQ_FREQ_S, 0);

	roce_set_bit(qpc_mask->byte_108_rx_reqepsn,
		     V2_QPC_BYTE_108_RX_REQ_PSN_ERR_S, 0);
	roce_set_field(qpc_mask->byte_96_rx_reqmsn, V2_QPC_BYTE_96_RX_REQ_MSN_M,
		       V2_QPC_BYTE_96_RX_REQ_MSN_S, 0);
	roce_set_field(qpc_mask->byte_108_rx_reqepsn,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_M,
		       V2_QPC_BYTE_108_RX_REQ_LAST_OPTYPE_S, 0);

	context->rq_rnr_समयr = 0;
	qpc_mask->rq_rnr_समयr = 0;

	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_HEAD_MAX_M,
		       V2_QPC_BYTE_132_TRRL_HEAD_MAX_S, 0);
	roce_set_field(qpc_mask->byte_132_trrl, V2_QPC_BYTE_132_TRRL_TAIL_MAX_M,
		       V2_QPC_BYTE_132_TRRL_TAIL_MAX_S, 0);

	/* rocee send 2^lp_sgen_ini segs every समय */
	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_LP_SGEN_INI_M,
		       V2_QPC_BYTE_168_LP_SGEN_INI_S, 3);
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_LP_SGEN_INI_M,
		       V2_QPC_BYTE_168_LP_SGEN_INI_S, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक modअगरy_qp_rtr_to_rts(काष्ठा ib_qp *ibqp,
				स्थिर काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask,
				काष्ठा hns_roce_v2_qp_context *context,
				काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक ret;

	/* Not support alternate path and path migration */
	अगर (attr_mask & (IB_QP_ALT_PATH | IB_QP_PATH_MIG_STATE)) अणु
		ibdev_err(ibdev, "RTR2RTS attr_mask (0x%x)error\n", attr_mask);
		वापस -EINVAL;
	पूर्ण

	ret = config_qp_sq_buf(hr_dev, hr_qp, context, qpc_mask);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to config sq buf, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Set some fields in context to zero, Because the शेष values
	 * of all fields in context are zero, we need not set them to 0 again.
	 * but we should set the relevant fields of context mask to 0.
	 */
	roce_set_field(qpc_mask->byte_232_irrl_sge,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_M,
		       V2_QPC_BYTE_232_IRRL_SGE_IDX_S, 0);

	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_RX_ACK_MSN_M,
		       V2_QPC_BYTE_240_RX_ACK_MSN_S, 0);

	roce_set_field(qpc_mask->byte_248_ack_psn,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_M,
		       V2_QPC_BYTE_248_ACK_LAST_OPTYPE_S, 0);
	roce_set_bit(qpc_mask->byte_248_ack_psn,
		     V2_QPC_BYTE_248_IRRL_PSN_VLD_S, 0);
	roce_set_field(qpc_mask->byte_248_ack_psn,
		       V2_QPC_BYTE_248_IRRL_PSN_M,
		       V2_QPC_BYTE_248_IRRL_PSN_S, 0);

	roce_set_field(qpc_mask->byte_240_irrl_tail,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_M,
		       V2_QPC_BYTE_240_IRRL_TAIL_REAL_S, 0);

	roce_set_field(qpc_mask->byte_220_retry_psn_msn,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_M,
		       V2_QPC_BYTE_220_RETRY_MSG_MSN_S, 0);

	roce_set_bit(qpc_mask->byte_248_ack_psn,
		     V2_QPC_BYTE_248_RNR_RETRY_FLAG_S, 0);

	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_CHECK_FLG_M,
		       V2_QPC_BYTE_212_CHECK_FLG_S, 0);

	roce_set_field(context->byte_212_lsn, V2_QPC_BYTE_212_LSN_M,
		       V2_QPC_BYTE_212_LSN_S, 0x100);
	roce_set_field(qpc_mask->byte_212_lsn, V2_QPC_BYTE_212_LSN_M,
		       V2_QPC_BYTE_212_LSN_S, 0);

	roce_set_field(qpc_mask->byte_196_sq_psn, V2_QPC_BYTE_196_IRRL_HEAD_M,
		       V2_QPC_BYTE_196_IRRL_HEAD_S, 0);

	वापस 0;
पूर्ण

अटल अंतरभूत u16 get_udp_sport(u32 fl, u32 lqpn, u32 rqpn)
अणु
	अगर (!fl)
		fl = rdma_calc_flow_label(lqpn, rqpn);

	वापस rdma_flow_label_to_udp_sport(fl);
पूर्ण

अटल पूर्णांक get_dip_ctx_idx(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_qp_attr *attr,
			   u32 *dip_idx)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_dip *hr_dip;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&hr_dev->dip_list_lock, flags);

	list_क्रम_each_entry(hr_dip, &hr_dev->dip_list, node) अणु
		अगर (!स_भेद(grh->dgid.raw, hr_dip->dgid, 16))
			जाओ out;
	पूर्ण

	/* If no dgid is found, a new dip and a mapping between dgid and
	 * dip_idx will be created.
	 */
	hr_dip = kzalloc(माप(*hr_dip), GFP_ATOMIC);
	अगर (!hr_dip) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(hr_dip->dgid, grh->dgid.raw, माप(grh->dgid.raw));
	hr_dip->dip_idx = *dip_idx = ibqp->qp_num;
	list_add_tail(&hr_dip->node, &hr_dev->dip_list);

out:
	spin_unlock_irqrestore(&hr_dev->dip_list_lock, flags);
	वापस ret;
पूर्ण

क्रमागत अणु
	CONG_DCQCN,
	CONG_WINDOW,
पूर्ण;

क्रमागत अणु
	UNSUPPORT_CONG_LEVEL,
	SUPPORT_CONG_LEVEL,
पूर्ण;

क्रमागत अणु
	CONG_LDCP,
	CONG_HC3,
पूर्ण;

क्रमागत अणु
	DIP_INVALID,
	DIP_VALID,
पूर्ण;

अटल पूर्णांक check_cong_type(काष्ठा ib_qp *ibqp,
			   काष्ठा hns_roce_congestion_algorithm *cong_alg)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);

	/* dअगरferent congestion types match dअगरferent configurations */
	चयन (hr_dev->caps.cong_type) अणु
	हाल CONG_TYPE_DCQCN:
		cong_alg->alg_sel = CONG_DCQCN;
		cong_alg->alg_sub_sel = UNSUPPORT_CONG_LEVEL;
		cong_alg->dip_vld = DIP_INVALID;
		अवरोध;
	हाल CONG_TYPE_LDCP:
		cong_alg->alg_sel = CONG_WINDOW;
		cong_alg->alg_sub_sel = CONG_LDCP;
		cong_alg->dip_vld = DIP_INVALID;
		अवरोध;
	हाल CONG_TYPE_HC3:
		cong_alg->alg_sel = CONG_WINDOW;
		cong_alg->alg_sub_sel = CONG_HC3;
		cong_alg->dip_vld = DIP_INVALID;
		अवरोध;
	हाल CONG_TYPE_DIP:
		cong_alg->alg_sel = CONG_DCQCN;
		cong_alg->alg_sub_sel = UNSUPPORT_CONG_LEVEL;
		cong_alg->dip_vld = DIP_VALID;
		अवरोध;
	शेष:
		ibdev_err(&hr_dev->ib_dev,
			  "error type(%u) for congestion selection.\n",
			  hr_dev->caps.cong_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fill_cong_field(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_qp_attr *attr,
			   काष्ठा hns_roce_v2_qp_context *context,
			   काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	काष्ठा hns_roce_congestion_algorithm cong_field;
	काष्ठा ib_device *ibdev = ibqp->device;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibdev);
	u32 dip_idx = 0;
	पूर्णांक ret;

	अगर (hr_dev->pci_dev->revision == PCI_REVISION_ID_HIP08 ||
	    grh->sgid_attr->gid_type == IB_GID_TYPE_ROCE)
		वापस 0;

	ret = check_cong_type(ibqp, &cong_field);
	अगर (ret)
		वापस ret;

	hr_reg_ग_लिखो(context, QPC_CONG_ALGO_TMPL_ID, hr_dev->cong_algo_पंचांगpl_id +
		     hr_dev->caps.cong_type * HNS_ROCE_CONG_SIZE);
	hr_reg_ग_लिखो(qpc_mask, QPC_CONG_ALGO_TMPL_ID, 0);
	hr_reg_ग_लिखो(&context->ext, QPCEX_CONG_ALG_SEL, cong_field.alg_sel);
	hr_reg_ग_लिखो(&qpc_mask->ext, QPCEX_CONG_ALG_SEL, 0);
	hr_reg_ग_लिखो(&context->ext, QPCEX_CONG_ALG_SUB_SEL,
		     cong_field.alg_sub_sel);
	hr_reg_ग_लिखो(&qpc_mask->ext, QPCEX_CONG_ALG_SUB_SEL, 0);
	hr_reg_ग_लिखो(&context->ext, QPCEX_DIP_CTX_IDX_VLD, cong_field.dip_vld);
	hr_reg_ग_लिखो(&qpc_mask->ext, QPCEX_DIP_CTX_IDX_VLD, 0);

	/* अगर dip is disabled, there is no need to set dip idx */
	अगर (cong_field.dip_vld == 0)
		वापस 0;

	ret = get_dip_ctx_idx(ibqp, attr, &dip_idx);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to fill cong field, ret = %d.\n", ret);
		वापस ret;
	पूर्ण

	hr_reg_ग_लिखो(&context->ext, QPCEX_DIP_CTX_IDX, dip_idx);
	hr_reg_ग_लिखो(&qpc_mask->ext, QPCEX_DIP_CTX_IDX, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_set_path(काष्ठा ib_qp *ibqp,
				स्थिर काष्ठा ib_qp_attr *attr,
				पूर्णांक attr_mask,
				काष्ठा hns_roce_v2_qp_context *context,
				काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(&attr->ah_attr);
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	स्थिर काष्ठा ib_gid_attr *gid_attr = शून्य;
	पूर्णांक is_roce_protocol;
	u16 vlan_id = 0xffff;
	bool is_udp = false;
	u8 ib_port;
	u8 hr_port;
	पूर्णांक ret;

	ib_port = (attr_mask & IB_QP_PORT) ? attr->port_num : hr_qp->port + 1;
	hr_port = ib_port - 1;
	is_roce_protocol = rdma_cap_eth_ah(&hr_dev->ib_dev, ib_port) &&
			   rdma_ah_get_ah_flags(&attr->ah_attr) & IB_AH_GRH;

	अगर (is_roce_protocol) अणु
		gid_attr = attr->ah_attr.grh.sgid_attr;
		ret = rdma_पढ़ो_gid_l2_fields(gid_attr, &vlan_id, शून्य);
		अगर (ret)
			वापस ret;

		अगर (gid_attr)
			is_udp = (gid_attr->gid_type ==
				 IB_GID_TYPE_ROCE_UDP_ENCAP);
	पूर्ण

	/* Only HIP08 needs to set the vlan_en bits in QPC */
	अगर (vlan_id < VLAN_N_VID &&
	    hr_dev->pci_dev->revision == PCI_REVISION_ID_HIP08) अणु
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_RQ_VLAN_EN_S, 1);
		roce_set_bit(qpc_mask->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_RQ_VLAN_EN_S, 0);
		roce_set_bit(context->byte_168_irrl_idx,
			     V2_QPC_BYTE_168_SQ_VLAN_EN_S, 1);
		roce_set_bit(qpc_mask->byte_168_irrl_idx,
			     V2_QPC_BYTE_168_SQ_VLAN_EN_S, 0);
	पूर्ण

	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, vlan_id);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_VLAN_ID_M,
		       V2_QPC_BYTE_24_VLAN_ID_S, 0);

	अगर (grh->sgid_index >= hr_dev->caps.gid_table_len[hr_port]) अणु
		ibdev_err(ibdev, "sgid_index(%u) too large. max is %d\n",
			  grh->sgid_index, hr_dev->caps.gid_table_len[hr_port]);
		वापस -EINVAL;
	पूर्ण

	अगर (attr->ah_attr.type != RDMA_AH_ATTR_TYPE_ROCE) अणु
		ibdev_err(ibdev, "ah attr is not RDMA roce type\n");
		वापस -EINVAL;
	पूर्ण

	roce_set_field(context->byte_52_udpspn_dmac, V2_QPC_BYTE_52_UDPSPN_M,
		       V2_QPC_BYTE_52_UDPSPN_S,
		       is_udp ? get_udp_sport(grh->flow_label, ibqp->qp_num,
					      attr->dest_qp_num) : 0);

	roce_set_field(qpc_mask->byte_52_udpspn_dmac, V2_QPC_BYTE_52_UDPSPN_M,
		       V2_QPC_BYTE_52_UDPSPN_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M, V2_QPC_BYTE_20_SGID_IDX_S,
		       grh->sgid_index);

	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SGID_IDX_M, V2_QPC_BYTE_20_SGID_IDX_S, 0);

	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_HOP_LIMIT_M,
		       V2_QPC_BYTE_24_HOP_LIMIT_S, grh->hop_limit);
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_HOP_LIMIT_M,
		       V2_QPC_BYTE_24_HOP_LIMIT_S, 0);

	ret = fill_cong_field(ibqp, attr, context, qpc_mask);
	अगर (ret)
		वापस ret;

	roce_set_field(context->byte_24_mtu_tc, V2_QPC_BYTE_24_TC_M,
		       V2_QPC_BYTE_24_TC_S, get_tclass(&attr->ah_attr.grh));
	roce_set_field(qpc_mask->byte_24_mtu_tc, V2_QPC_BYTE_24_TC_M,
		       V2_QPC_BYTE_24_TC_S, 0);

	roce_set_field(context->byte_28_at_fl, V2_QPC_BYTE_28_FL_M,
		       V2_QPC_BYTE_28_FL_S, grh->flow_label);
	roce_set_field(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_FL_M,
		       V2_QPC_BYTE_28_FL_S, 0);
	स_नकल(context->dgid, grh->dgid.raw, माप(grh->dgid.raw));
	स_रखो(qpc_mask->dgid, 0, माप(grh->dgid.raw));

	hr_qp->sl = rdma_ah_get_sl(&attr->ah_attr);
	अगर (unlikely(hr_qp->sl > MAX_SERVICE_LEVEL)) अणु
		ibdev_err(ibdev,
			  "failed to fill QPC, sl (%d) shouldn't be larger than %d.\n",
			  hr_qp->sl, MAX_SERVICE_LEVEL);
		वापस -EINVAL;
	पूर्ण

	roce_set_field(context->byte_28_at_fl, V2_QPC_BYTE_28_SL_M,
		       V2_QPC_BYTE_28_SL_S, hr_qp->sl);
	roce_set_field(qpc_mask->byte_28_at_fl, V2_QPC_BYTE_28_SL_M,
		       V2_QPC_BYTE_28_SL_S, 0);

	वापस 0;
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
		[IB_QPS_RTS] = अणु [IB_QPS_RESET] = true,
				 [IB_QPS_RTS] = true,
				 [IB_QPS_ERR] = true पूर्ण,
		[IB_QPS_SQD] = अणुपूर्ण,
		[IB_QPS_SQE] = अणुपूर्ण,
		[IB_QPS_ERR] = अणु [IB_QPS_RESET] = true, [IB_QPS_ERR] = true पूर्ण
	पूर्ण;

	वापस sm[cur_state][new_state];
पूर्ण

अटल पूर्णांक hns_roce_v2_set_असल_fields(काष्ठा ib_qp *ibqp,
				      स्थिर काष्ठा ib_qp_attr *attr,
				      पूर्णांक attr_mask,
				      क्रमागत ib_qp_state cur_state,
				      क्रमागत ib_qp_state new_state,
				      काष्ठा hns_roce_v2_qp_context *context,
				      काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	पूर्णांक ret = 0;

	अगर (!check_qp_state(cur_state, new_state)) अणु
		ibdev_err(&hr_dev->ib_dev, "Illegal state for QP!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT) अणु
		स_रखो(qpc_mask, 0, hr_dev->caps.qpc_sz);
		modअगरy_qp_reset_to_init(ibqp, attr, attr_mask, context,
					qpc_mask);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_INIT) अणु
		modअगरy_qp_init_to_init(ibqp, attr, attr_mask, context,
				       qpc_mask);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_INIT && new_state == IB_QPS_RTR) अणु
		ret = modअगरy_qp_init_to_rtr(ibqp, attr, attr_mask, context,
					    qpc_mask);
	पूर्ण अन्यथा अगर (cur_state == IB_QPS_RTR && new_state == IB_QPS_RTS) अणु
		ret = modअगरy_qp_rtr_to_rts(ibqp, attr, attr_mask, context,
					   qpc_mask);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_set_opt_fields(काष्ठा ib_qp *ibqp,
				      स्थिर काष्ठा ib_qp_attr *attr,
				      पूर्णांक attr_mask,
				      काष्ठा hns_roce_v2_qp_context *context,
				      काष्ठा hns_roce_v2_qp_context *qpc_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	पूर्णांक ret = 0;

	अगर (attr_mask & IB_QP_AV) अणु
		ret = hns_roce_v2_set_path(ibqp, attr, attr_mask, context,
					   qpc_mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		अगर (attr->समयout < 31) अणु
			roce_set_field(context->byte_28_at_fl,
				       V2_QPC_BYTE_28_AT_M, V2_QPC_BYTE_28_AT_S,
				       attr->समयout);
			roce_set_field(qpc_mask->byte_28_at_fl,
				       V2_QPC_BYTE_28_AT_M, V2_QPC_BYTE_28_AT_S,
				       0);
		पूर्ण अन्यथा अणु
			ibdev_warn(&hr_dev->ib_dev,
				   "Local ACK timeout shall be 0 to 30.\n");
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		roce_set_field(context->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_S,
			       attr->retry_cnt);
		roce_set_field(qpc_mask->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
			       V2_QPC_BYTE_212_RETRY_NUM_INIT_S, 0);

		roce_set_field(context->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_CNT_M,
			       V2_QPC_BYTE_212_RETRY_CNT_S, attr->retry_cnt);
		roce_set_field(qpc_mask->byte_212_lsn,
			       V2_QPC_BYTE_212_RETRY_CNT_M,
			       V2_QPC_BYTE_212_RETRY_CNT_S, 0);
	पूर्ण

	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_S, attr->rnr_retry);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_M,
			       V2_QPC_BYTE_244_RNR_NUM_INIT_S, 0);

		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_CNT_M,
			       V2_QPC_BYTE_244_RNR_CNT_S, attr->rnr_retry);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RNR_CNT_M,
			       V2_QPC_BYTE_244_RNR_CNT_S, 0);
	पूर्ण

	अगर (attr_mask & IB_QP_SQ_PSN) अणु
		roce_set_field(context->byte_172_sq_psn,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_M,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_172_sq_psn,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_M,
			       V2_QPC_BYTE_172_SQ_CUR_PSN_S, 0);

		roce_set_field(context->byte_196_sq_psn,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_M,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_196_sq_psn,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_M,
			       V2_QPC_BYTE_196_SQ_MAX_PSN_S, 0);

		roce_set_field(context->byte_220_retry_psn_msn,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_220_retry_psn_msn,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_220_RETRY_MSG_PSN_S, 0);

		roce_set_field(context->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_S,
			       attr->sq_psn >> V2_QPC_BYTE_220_RETRY_MSG_PSN_S);
		roce_set_field(qpc_mask->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_PSN_S, 0);

		roce_set_field(context->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S,
			       attr->sq_psn);
		roce_set_field(qpc_mask->byte_224_retry_msg,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_M,
			       V2_QPC_BYTE_224_RETRY_MSG_FPKT_PSN_S, 0);

		roce_set_field(context->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_S, attr->sq_psn);
		roce_set_field(qpc_mask->byte_244_rnr_rxack,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_M,
			       V2_QPC_BYTE_244_RX_ACK_EPSN_S, 0);
	पूर्ण

	अगर ((attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) &&
	     attr->max_dest_rd_atomic) अणु
		roce_set_field(context->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S,
			       fls(attr->max_dest_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_140_raq, V2_QPC_BYTE_140_RR_MAX_M,
			       V2_QPC_BYTE_140_RR_MAX_S, 0);
	पूर्ण

	अगर ((attr_mask & IB_QP_MAX_QP_RD_ATOMIC) && attr->max_rd_atomic) अणु
		roce_set_field(context->byte_208_irrl, V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S,
			       fls(attr->max_rd_atomic - 1));
		roce_set_field(qpc_mask->byte_208_irrl,
			       V2_QPC_BYTE_208_SR_MAX_M,
			       V2_QPC_BYTE_208_SR_MAX_S, 0);
	पूर्ण

	अगर (attr_mask & (IB_QP_ACCESS_FLAGS | IB_QP_MAX_DEST_RD_ATOMIC))
		set_access_flags(hr_qp, context, qpc_mask, attr, attr_mask);

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER) अणु
		roce_set_field(context->byte_80_rnr_rx_cqn,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_S,
			       attr->min_rnr_समयr);
		roce_set_field(qpc_mask->byte_80_rnr_rx_cqn,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_M,
			       V2_QPC_BYTE_80_MIN_RNR_TIME_S, 0);
	पूर्ण

	अगर (attr_mask & IB_QP_RQ_PSN) अणु
		roce_set_field(context->byte_108_rx_reqepsn,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_S, attr->rq_psn);
		roce_set_field(qpc_mask->byte_108_rx_reqepsn,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_M,
			       V2_QPC_BYTE_108_RX_REQ_EPSN_S, 0);

		roce_set_field(context->byte_152_raq, V2_QPC_BYTE_152_RAQ_PSN_M,
			       V2_QPC_BYTE_152_RAQ_PSN_S, attr->rq_psn - 1);
		roce_set_field(qpc_mask->byte_152_raq,
			       V2_QPC_BYTE_152_RAQ_PSN_M,
			       V2_QPC_BYTE_152_RAQ_PSN_S, 0);
	पूर्ण

	अगर (attr_mask & IB_QP_QKEY) अणु
		context->qkey_xrcd = cpu_to_le32(attr->qkey);
		qpc_mask->qkey_xrcd = 0;
		hr_qp->qkey = attr->qkey;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns_roce_v2_record_opt_fields(काष्ठा ib_qp *ibqp,
					  स्थिर काष्ठा ib_qp_attr *attr,
					  पूर्णांक attr_mask)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		hr_qp->atomic_rd_en = attr->qp_access_flags;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		hr_qp->resp_depth = attr->max_dest_rd_atomic;
	अगर (attr_mask & IB_QP_PORT) अणु
		hr_qp->port = attr->port_num - 1;
		hr_qp->phy_port = hr_dev->iboe.phy_port[hr_qp->port];
	पूर्ण
पूर्ण

अटल व्योम clear_qp(काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_qp *ibqp = &hr_qp->ibqp;

	अगर (ibqp->send_cq)
		hns_roce_v2_cq_clean(to_hr_cq(ibqp->send_cq),
				     hr_qp->qpn, शून्य);

	अगर (ibqp->recv_cq  && ibqp->recv_cq != ibqp->send_cq)
		hns_roce_v2_cq_clean(to_hr_cq(ibqp->recv_cq),
				     hr_qp->qpn, ibqp->srq ?
				     to_hr_srq(ibqp->srq) : शून्य);

	अगर (hr_qp->en_flags & HNS_ROCE_QP_CAP_RQ_RECORD_DB)
		*hr_qp->rdb.db_record = 0;

	hr_qp->rq.head = 0;
	hr_qp->rq.tail = 0;
	hr_qp->sq.head = 0;
	hr_qp->sq.tail = 0;
	hr_qp->next_sge = 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_modअगरy_qp(काष्ठा ib_qp *ibqp,
				 स्थिर काष्ठा ib_qp_attr *attr,
				 पूर्णांक attr_mask, क्रमागत ib_qp_state cur_state,
				 क्रमागत ib_qp_state new_state)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_v2_qp_context ctx[2];
	काष्ठा hns_roce_v2_qp_context *context = ctx;
	काष्ठा hns_roce_v2_qp_context *qpc_mask = ctx + 1;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	अचिन्हित दीर्घ sq_flag = 0;
	अचिन्हित दीर्घ rq_flag = 0;
	पूर्णांक ret;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modअगरying qp. If software need modअगरy some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same समय, अन्यथा set them to 0x1.
	 */
	स_रखो(context, 0, hr_dev->caps.qpc_sz);
	स_रखो(qpc_mask, 0xff, hr_dev->caps.qpc_sz);

	ret = hns_roce_v2_set_असल_fields(ibqp, attr, attr_mask, cur_state,
					 new_state, context, qpc_mask);
	अगर (ret)
		जाओ out;

	/* When QP state is err, SQ and RQ WQE should be flushed */
	अगर (new_state == IB_QPS_ERR) अणु
		अगर (ibqp->qp_type != IB_QPT_XRC_TGT) अणु
			spin_lock_irqsave(&hr_qp->sq.lock, sq_flag);
			hr_qp->state = IB_QPS_ERR;
			roce_set_field(context->byte_160_sq_ci_pi,
				       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_M,
				       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_S,
				       hr_qp->sq.head);
			roce_set_field(qpc_mask->byte_160_sq_ci_pi,
				       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_M,
				       V2_QPC_BYTE_160_SQ_PRODUCER_IDX_S, 0);
			spin_unlock_irqrestore(&hr_qp->sq.lock, sq_flag);
		पूर्ण

		अगर (!ibqp->srq && ibqp->qp_type != IB_QPT_XRC_INI &&
		    ibqp->qp_type != IB_QPT_XRC_TGT) अणु
			spin_lock_irqsave(&hr_qp->rq.lock, rq_flag);
			hr_qp->state = IB_QPS_ERR;
			roce_set_field(context->byte_84_rq_ci_pi,
			       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M,
			       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S,
			       hr_qp->rq.head);
			roce_set_field(qpc_mask->byte_84_rq_ci_pi,
			       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_M,
			       V2_QPC_BYTE_84_RQ_PRODUCER_IDX_S, 0);
			spin_unlock_irqrestore(&hr_qp->rq.lock, rq_flag);
		पूर्ण
	पूर्ण

	/* Configure the optional fields */
	ret = hns_roce_v2_set_opt_fields(ibqp, attr, attr_mask, context,
					 qpc_mask);
	अगर (ret)
		जाओ out;

	roce_set_bit(context->byte_108_rx_reqepsn, V2_QPC_BYTE_108_INV_CREDIT_S,
		     ((to_hr_qp_type(hr_qp->ibqp.qp_type) == SERV_TYPE_XRC) ||
		     ibqp->srq) ? 1 : 0);
	roce_set_bit(qpc_mask->byte_108_rx_reqepsn,
		     V2_QPC_BYTE_108_INV_CREDIT_S, 0);

	/* Every status migrate must change state */
	roce_set_field(context->byte_60_qpst_tempid, V2_QPC_BYTE_60_QP_ST_M,
		       V2_QPC_BYTE_60_QP_ST_S, new_state);
	roce_set_field(qpc_mask->byte_60_qpst_tempid, V2_QPC_BYTE_60_QP_ST_M,
		       V2_QPC_BYTE_60_QP_ST_S, 0);

	/* SW pass context to HW */
	ret = hns_roce_v2_qp_modअगरy(hr_dev, context, qpc_mask, hr_qp);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to modify QP, ret = %d.\n", ret);
		जाओ out;
	पूर्ण

	hr_qp->state = new_state;

	hns_roce_v2_record_opt_fields(ibqp, attr, attr_mask);

	अगर (new_state == IB_QPS_RESET && !ibqp->uobject)
		clear_qp(hr_qp);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक to_ib_qp_st(क्रमागत hns_roce_v2_qp_state state)
अणु
	अटल स्थिर क्रमागत ib_qp_state map[] = अणु
		[HNS_ROCE_QP_ST_RST] = IB_QPS_RESET,
		[HNS_ROCE_QP_ST_INIT] = IB_QPS_INIT,
		[HNS_ROCE_QP_ST_RTR] = IB_QPS_RTR,
		[HNS_ROCE_QP_ST_RTS] = IB_QPS_RTS,
		[HNS_ROCE_QP_ST_SQD] = IB_QPS_SQD,
		[HNS_ROCE_QP_ST_SQER] = IB_QPS_SQE,
		[HNS_ROCE_QP_ST_ERR] = IB_QPS_ERR,
		[HNS_ROCE_QP_ST_SQ_DRAINING] = IB_QPS_SQD
	पूर्ण;

	वापस (state < ARRAY_SIZE(map)) ? map[state] : -1;
पूर्ण

अटल पूर्णांक hns_roce_v2_query_qpc(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_qp *hr_qp,
				 काष्ठा hns_roce_v2_qp_context *hr_context)
अणु
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, hr_qp->qpn, 0,
				HNS_ROCE_CMD_QUERY_QPC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret)
		जाओ out;

	स_नकल(hr_context, mailbox->buf, hr_dev->caps.qpc_sz);

out:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
				पूर्णांक qp_attr_mask,
				काष्ठा ib_qp_init_attr *qp_init_attr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	काष्ठा hns_roce_v2_qp_context context = अणुपूर्ण;
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	पूर्णांक पंचांगp_qp_state;
	पूर्णांक state;
	पूर्णांक ret;

	स_रखो(qp_attr, 0, माप(*qp_attr));
	स_रखो(qp_init_attr, 0, माप(*qp_init_attr));

	mutex_lock(&hr_qp->mutex);

	अगर (hr_qp->state == IB_QPS_RESET) अणु
		qp_attr->qp_state = IB_QPS_RESET;
		ret = 0;
		जाओ करोne;
	पूर्ण

	ret = hns_roce_v2_query_qpc(hr_dev, hr_qp, &context);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to query QPC, ret = %d.\n", ret);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	state = roce_get_field(context.byte_60_qpst_tempid,
			       V2_QPC_BYTE_60_QP_ST_M, V2_QPC_BYTE_60_QP_ST_S);
	पंचांगp_qp_state = to_ib_qp_st((क्रमागत hns_roce_v2_qp_state)state);
	अगर (पंचांगp_qp_state == -1) अणु
		ibdev_err(ibdev, "Illegal ib_qp_state\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	hr_qp->state = (u8)पंचांगp_qp_state;
	qp_attr->qp_state = (क्रमागत ib_qp_state)hr_qp->state;
	qp_attr->path_mtu = (क्रमागत ib_mtu)roce_get_field(context.byte_24_mtu_tc,
							V2_QPC_BYTE_24_MTU_M,
							V2_QPC_BYTE_24_MTU_S);
	qp_attr->path_mig_state = IB_MIG_ARMED;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	अगर (hr_qp->ibqp.qp_type == IB_QPT_UD)
		qp_attr->qkey = le32_to_cpu(context.qkey_xrcd);

	qp_attr->rq_psn = roce_get_field(context.byte_108_rx_reqepsn,
					 V2_QPC_BYTE_108_RX_REQ_EPSN_M,
					 V2_QPC_BYTE_108_RX_REQ_EPSN_S);
	qp_attr->sq_psn = (u32)roce_get_field(context.byte_172_sq_psn,
					      V2_QPC_BYTE_172_SQ_CUR_PSN_M,
					      V2_QPC_BYTE_172_SQ_CUR_PSN_S);
	qp_attr->dest_qp_num = (u8)roce_get_field(context.byte_56_dqpn_err,
						  V2_QPC_BYTE_56_DQPN_M,
						  V2_QPC_BYTE_56_DQPN_S);
	qp_attr->qp_access_flags = ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_RRE_S)) << V2_QP_RRE_S) |
				    ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_RWE_S)) << V2_QP_RWE_S) |
				    ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_ATE_S)) << V2_QP_ATE_S);

	अगर (hr_qp->ibqp.qp_type == IB_QPT_RC ||
	    hr_qp->ibqp.qp_type == IB_QPT_XRC_INI ||
	    hr_qp->ibqp.qp_type == IB_QPT_XRC_TGT) अणु
		काष्ठा ib_global_route *grh =
				rdma_ah_retrieve_grh(&qp_attr->ah_attr);

		rdma_ah_set_sl(&qp_attr->ah_attr,
			       roce_get_field(context.byte_28_at_fl,
					      V2_QPC_BYTE_28_SL_M,
					      V2_QPC_BYTE_28_SL_S));
		grh->flow_label = roce_get_field(context.byte_28_at_fl,
						 V2_QPC_BYTE_28_FL_M,
						 V2_QPC_BYTE_28_FL_S);
		grh->sgid_index = roce_get_field(context.byte_20_smac_sgid_idx,
						 V2_QPC_BYTE_20_SGID_IDX_M,
						 V2_QPC_BYTE_20_SGID_IDX_S);
		grh->hop_limit = roce_get_field(context.byte_24_mtu_tc,
						V2_QPC_BYTE_24_HOP_LIMIT_M,
						V2_QPC_BYTE_24_HOP_LIMIT_S);
		grh->traffic_class = roce_get_field(context.byte_24_mtu_tc,
						    V2_QPC_BYTE_24_TC_M,
						    V2_QPC_BYTE_24_TC_S);

		स_नकल(grh->dgid.raw, context.dgid, माप(grh->dgid.raw));
	पूर्ण

	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 1 << roce_get_field(context.byte_208_irrl,
						     V2_QPC_BYTE_208_SR_MAX_M,
						     V2_QPC_BYTE_208_SR_MAX_S);
	qp_attr->max_dest_rd_atomic = 1 << roce_get_field(context.byte_140_raq,
						     V2_QPC_BYTE_140_RR_MAX_M,
						     V2_QPC_BYTE_140_RR_MAX_S);

	qp_attr->min_rnr_समयr = (u8)roce_get_field(context.byte_80_rnr_rx_cqn,
						 V2_QPC_BYTE_80_MIN_RNR_TIME_M,
						 V2_QPC_BYTE_80_MIN_RNR_TIME_S);
	qp_attr->समयout = (u8)roce_get_field(context.byte_28_at_fl,
					      V2_QPC_BYTE_28_AT_M,
					      V2_QPC_BYTE_28_AT_S);
	qp_attr->retry_cnt = roce_get_field(context.byte_212_lsn,
					    V2_QPC_BYTE_212_RETRY_NUM_INIT_M,
					    V2_QPC_BYTE_212_RETRY_NUM_INIT_S);
	qp_attr->rnr_retry = roce_get_field(context.byte_244_rnr_rxack,
					    V2_QPC_BYTE_244_RNR_NUM_INIT_M,
					    V2_QPC_BYTE_244_RNR_NUM_INIT_S);

करोne:
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr = hr_qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge = hr_qp->rq.max_gs - hr_qp->rq.rsv_sge;
	qp_attr->cap.max_अंतरभूत_data = hr_qp->max_अंतरभूत_data;

	अगर (!ibqp->uobject) अणु
		qp_attr->cap.max_send_wr = hr_qp->sq.wqe_cnt;
		qp_attr->cap.max_send_sge = hr_qp->sq.max_gs;
	पूर्ण अन्यथा अणु
		qp_attr->cap.max_send_wr = 0;
		qp_attr->cap.max_send_sge = 0;
	पूर्ण

	qp_init_attr->cap = qp_attr->cap;
	qp_init_attr->sq_sig_type = hr_qp->sq_संकेत_bits;

out:
	mutex_unlock(&hr_qp->mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक modअगरy_qp_is_ok(काष्ठा hns_roce_qp *hr_qp)
अणु
	वापस ((hr_qp->ibqp.qp_type == IB_QPT_RC ||
		 hr_qp->ibqp.qp_type == IB_QPT_UD ||
		 hr_qp->ibqp.qp_type == IB_QPT_XRC_INI ||
		 hr_qp->ibqp.qp_type == IB_QPT_XRC_TGT) &&
		hr_qp->state != IB_QPS_RESET);
पूर्ण

अटल पूर्णांक hns_roce_v2_destroy_qp_common(काष्ठा hns_roce_dev *hr_dev,
					 काष्ठा hns_roce_qp *hr_qp,
					 काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_cq *send_cq, *recv_cq;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (modअगरy_qp_is_ok(hr_qp)) अणु
		/* Modअगरy qp to reset beक्रमe destroying qp */
		ret = hns_roce_v2_modअगरy_qp(&hr_qp->ibqp, शून्य, 0,
					    hr_qp->state, IB_QPS_RESET);
		अगर (ret)
			ibdev_err(ibdev,
				  "failed to modify QP to RST, ret = %d.\n",
				  ret);
	पूर्ण

	send_cq = hr_qp->ibqp.send_cq ? to_hr_cq(hr_qp->ibqp.send_cq) : शून्य;
	recv_cq = hr_qp->ibqp.recv_cq ? to_hr_cq(hr_qp->ibqp.recv_cq) : शून्य;

	spin_lock_irqsave(&hr_dev->qp_list_lock, flags);
	hns_roce_lock_cqs(send_cq, recv_cq);

	अगर (!udata) अणु
		अगर (recv_cq)
			__hns_roce_v2_cq_clean(recv_cq, hr_qp->qpn,
					       (hr_qp->ibqp.srq ?
						to_hr_srq(hr_qp->ibqp.srq) :
						शून्य));

		अगर (send_cq && send_cq != recv_cq)
			__hns_roce_v2_cq_clean(send_cq, hr_qp->qpn, शून्य);

	पूर्ण

	hns_roce_qp_हटाओ(hr_dev, hr_qp);

	hns_roce_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&hr_dev->qp_list_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	काष्ठा hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	पूर्णांक ret;

	ret = hns_roce_v2_destroy_qp_common(hr_dev, hr_qp, udata);
	अगर (ret)
		ibdev_err(&hr_dev->ib_dev,
			  "failed to destroy QP, QPN = 0x%06lx, ret = %d.\n",
			  hr_qp->qpn, ret);

	hns_roce_qp_destroy(hr_dev, hr_qp, udata);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_qp_flow_control_init(काष्ठा hns_roce_dev *hr_dev,
					    काष्ठा hns_roce_qp *hr_qp)
अणु
	काष्ठा ib_device *ibdev = &hr_dev->ib_dev;
	काष्ठा hns_roce_sccc_clr_करोne *resp;
	काष्ठा hns_roce_sccc_clr *clr;
	काष्ठा hns_roce_cmq_desc desc;
	पूर्णांक ret, i;

	अगर (hr_dev->pci_dev->revision >= PCI_REVISION_ID_HIP09)
		वापस 0;

	mutex_lock(&hr_dev->qp_table.scc_mutex);

	/* set scc ctx clear करोne flag */
	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_RESET_SCCC, false);
	ret =  hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to reset SCC ctx, ret = %d.\n", ret);
		जाओ out;
	पूर्ण

	/* clear scc context */
	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CLR_SCCC, false);
	clr = (काष्ठा hns_roce_sccc_clr *)desc.data;
	clr->qpn = cpu_to_le32(hr_qp->qpn);
	ret =  hns_roce_cmq_send(hr_dev, &desc, 1);
	अगर (ret) अणु
		ibdev_err(ibdev, "failed to clear SCC ctx, ret = %d.\n", ret);
		जाओ out;
	पूर्ण

	/* query scc context clear is करोne or not */
	resp = (काष्ठा hns_roce_sccc_clr_करोne *)desc.data;
	क्रम (i = 0; i <= HNS_ROCE_CMQ_SCC_CLR_DONE_CNT; i++) अणु
		hns_roce_cmq_setup_basic_desc(&desc,
					      HNS_ROCE_OPC_QUERY_SCCC, true);
		ret = hns_roce_cmq_send(hr_dev, &desc, 1);
		अगर (ret) अणु
			ibdev_err(ibdev, "failed to query clr cmq, ret = %d\n",
				  ret);
			जाओ out;
		पूर्ण

		अगर (resp->clr_करोne)
			जाओ out;

		msleep(20);
	पूर्ण

	ibdev_err(ibdev, "Query SCC clr done flag overtime.\n");
	ret = -ETIMEDOUT;

out:
	mutex_unlock(&hr_dev->qp_table.scc_mutex);
	वापस ret;
पूर्ण

#घोषणा DMA_IDX_SHIFT 3
#घोषणा DMA_WQE_SHIFT 3

अटल पूर्णांक hns_roce_v2_ग_लिखो_srqc_index_queue(काष्ठा hns_roce_srq *srq,
					      काष्ठा hns_roce_srq_context *ctx)
अणु
	काष्ठा hns_roce_idx_que *idx_que = &srq->idx_que;
	काष्ठा ib_device *ibdev = srq->ibsrq.device;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibdev);
	u64 mtts_idx[MTT_MIN_COUNT] = अणुपूर्ण;
	dma_addr_t dma_handle_idx = 0;
	पूर्णांक ret;

	/* Get physical address of idx que buf */
	ret = hns_roce_mtr_find(hr_dev, &idx_que->mtr, 0, mtts_idx,
				ARRAY_SIZE(mtts_idx), &dma_handle_idx);
	अगर (ret < 1) अणु
		ibdev_err(ibdev, "failed to find mtr for SRQ idx, ret = %d.\n",
			  ret);
		वापस -ENOBUFS;
	पूर्ण

	hr_reg_ग_लिखो(ctx, SRQC_IDX_HOP_NUM,
		     to_hr_hem_hopnum(hr_dev->caps.idx_hop_num, srq->wqe_cnt));

	hr_reg_ग_लिखो(ctx, SRQC_IDX_BT_BA_L, dma_handle_idx >> DMA_IDX_SHIFT);
	hr_reg_ग_लिखो(ctx, SRQC_IDX_BT_BA_H,
		     upper_32_bits(dma_handle_idx >> DMA_IDX_SHIFT));

	hr_reg_ग_लिखो(ctx, SRQC_IDX_BA_PG_SZ,
		     to_hr_hw_page_shअगरt(idx_que->mtr.hem_cfg.ba_pg_shअगरt));
	hr_reg_ग_लिखो(ctx, SRQC_IDX_BUF_PG_SZ,
		     to_hr_hw_page_shअगरt(idx_que->mtr.hem_cfg.buf_pg_shअगरt));

	hr_reg_ग_लिखो(ctx, SRQC_IDX_CUR_BLK_ADDR_L,
		     to_hr_hw_page_addr(mtts_idx[0]));
	hr_reg_ग_लिखो(ctx, SRQC_IDX_CUR_BLK_ADDR_H,
		     upper_32_bits(to_hr_hw_page_addr(mtts_idx[0])));

	hr_reg_ग_लिखो(ctx, SRQC_IDX_NXT_BLK_ADDR_L,
		     to_hr_hw_page_addr(mtts_idx[1]));
	hr_reg_ग_लिखो(ctx, SRQC_IDX_NXT_BLK_ADDR_H,
		     upper_32_bits(to_hr_hw_page_addr(mtts_idx[1])));

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_ग_लिखो_srqc(काष्ठा hns_roce_srq *srq, व्योम *mb_buf)
अणु
	काष्ठा ib_device *ibdev = srq->ibsrq.device;
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibdev);
	काष्ठा hns_roce_srq_context *ctx = mb_buf;
	u64 mtts_wqe[MTT_MIN_COUNT] = अणुपूर्ण;
	dma_addr_t dma_handle_wqe = 0;
	पूर्णांक ret;

	स_रखो(ctx, 0, माप(*ctx));

	/* Get the physical address of srq buf */
	ret = hns_roce_mtr_find(hr_dev, &srq->buf_mtr, 0, mtts_wqe,
				ARRAY_SIZE(mtts_wqe), &dma_handle_wqe);
	अगर (ret < 1) अणु
		ibdev_err(ibdev, "failed to find mtr for SRQ WQE, ret = %d.\n",
			  ret);
		वापस -ENOBUFS;
	पूर्ण

	hr_reg_ग_लिखो(ctx, SRQC_SRQ_ST, 1);
	hr_reg_ग_लिखो(ctx, SRQC_SRQ_TYPE,
		     !!(srq->ibsrq.srq_type == IB_SRQT_XRC));
	hr_reg_ग_लिखो(ctx, SRQC_PD, to_hr_pd(srq->ibsrq.pd)->pdn);
	hr_reg_ग_लिखो(ctx, SRQC_SRQN, srq->srqn);
	hr_reg_ग_लिखो(ctx, SRQC_XRCD, srq->xrcdn);
	hr_reg_ग_लिखो(ctx, SRQC_XRC_CQN, srq->cqn);
	hr_reg_ग_लिखो(ctx, SRQC_SHIFT, ilog2(srq->wqe_cnt));
	hr_reg_ग_लिखो(ctx, SRQC_RQWS,
		     srq->max_gs <= 0 ? 0 : fls(srq->max_gs - 1));

	hr_reg_ग_लिखो(ctx, SRQC_WQE_HOP_NUM,
		     to_hr_hem_hopnum(hr_dev->caps.srqwqe_hop_num,
				      srq->wqe_cnt));

	hr_reg_ग_लिखो(ctx, SRQC_WQE_BT_BA_L, dma_handle_wqe >> DMA_WQE_SHIFT);
	hr_reg_ग_लिखो(ctx, SRQC_WQE_BT_BA_H,
		     upper_32_bits(dma_handle_wqe >> DMA_WQE_SHIFT));

	hr_reg_ग_लिखो(ctx, SRQC_WQE_BA_PG_SZ,
		     to_hr_hw_page_shअगरt(srq->buf_mtr.hem_cfg.ba_pg_shअगरt));
	hr_reg_ग_लिखो(ctx, SRQC_WQE_BUF_PG_SZ,
		     to_hr_hw_page_shअगरt(srq->buf_mtr.hem_cfg.buf_pg_shअगरt));

	वापस hns_roce_v2_ग_लिखो_srqc_index_queue(srq, ctx);
पूर्ण

अटल पूर्णांक hns_roce_v2_modअगरy_srq(काष्ठा ib_srq *ibsrq,
				  काष्ठा ib_srq_attr *srq_attr,
				  क्रमागत ib_srq_attr_mask srq_attr_mask,
				  काष्ठा ib_udata *udata)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	काष्ठा hns_roce_srq *srq = to_hr_srq(ibsrq);
	काष्ठा hns_roce_srq_context *srq_context;
	काष्ठा hns_roce_srq_context *srqc_mask;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	/* Resizing SRQs is not supported yet */
	अगर (srq_attr_mask & IB_SRQ_MAX_WR)
		वापस -EINVAL;

	अगर (srq_attr_mask & IB_SRQ_LIMIT) अणु
		अगर (srq_attr->srq_limit > srq->wqe_cnt)
			वापस -EINVAL;

		mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
		अगर (IS_ERR(mailbox))
			वापस PTR_ERR(mailbox);

		srq_context = mailbox->buf;
		srqc_mask = (काष्ठा hns_roce_srq_context *)mailbox->buf + 1;

		स_रखो(srqc_mask, 0xff, माप(*srqc_mask));

		roce_set_field(srq_context->byte_8_limit_wl,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_M,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_S, srq_attr->srq_limit);
		roce_set_field(srqc_mask->byte_8_limit_wl,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_M,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_S, 0);

		ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, srq->srqn, 0,
					HNS_ROCE_CMD_MODIFY_SRQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
		hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
		अगर (ret) अणु
			ibdev_err(&hr_dev->ib_dev,
				  "failed to handle cmd of modifying SRQ, ret = %d.\n",
				  ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_v2_query_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	काष्ठा hns_roce_srq *srq = to_hr_srq(ibsrq);
	काष्ठा hns_roce_srq_context *srq_context;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक limit_wl;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	srq_context = mailbox->buf;
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, srq->srqn, 0,
				HNS_ROCE_CMD_QUERY_SRQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret) अणु
		ibdev_err(&hr_dev->ib_dev,
			  "failed to process cmd of querying SRQ, ret = %d.\n",
			  ret);
		जाओ out;
	पूर्ण

	limit_wl = roce_get_field(srq_context->byte_8_limit_wl,
				  SRQC_BYTE_8_SRQ_LIMIT_WL_M,
				  SRQC_BYTE_8_SRQ_LIMIT_WL_S);

	attr->srq_limit = limit_wl;
	attr->max_wr = srq->wqe_cnt;
	attr->max_sge = srq->max_gs - srq->rsv_sge;

out:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_v2_modअगरy_cq(काष्ठा ib_cq *cq, u16 cq_count, u16 cq_period)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(cq->device);
	काष्ठा hns_roce_v2_cq_context *cq_context;
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(cq);
	काष्ठा hns_roce_v2_cq_context *cqc_mask;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	cqc_mask = (काष्ठा hns_roce_v2_cq_context *)mailbox->buf + 1;

	स_रखो(cqc_mask, 0xff, माप(*cqc_mask));

	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M, V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       cq_count);
	roce_set_field(cqc_mask->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M, V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       0);
	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M, V2_CQC_BYTE_56_CQ_PERIOD_S,
		       cq_period);
	roce_set_field(cqc_mask->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M, V2_CQC_BYTE_56_CQ_PERIOD_S,
		       0);

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, hr_cq->cqn, 1,
				HNS_ROCE_CMD_MODIFY_CQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);
	अगर (ret)
		ibdev_err(&hr_dev->ib_dev,
			  "failed to process cmd when modifying CQ, ret = %d.\n",
			  ret);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_irq_work_handle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hns_roce_work *irq_work =
				container_of(work, काष्ठा hns_roce_work, work);
	काष्ठा ib_device *ibdev = &irq_work->hr_dev->ib_dev;

	चयन (irq_work->event_type) अणु
	हाल HNS_ROCE_EVENT_TYPE_PATH_MIG:
		ibdev_info(ibdev, "Path migrated succeeded.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
		ibdev_warn(ibdev, "Path migration failed.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_COMM_EST:
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
		ibdev_warn(ibdev, "Send queue drained.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		ibdev_err(ibdev, "Local work queue 0x%x catast error, sub_event type is: %d\n",
			  irq_work->queue_num, irq_work->sub_type);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		ibdev_err(ibdev, "Invalid request local work queue 0x%x error.\n",
			  irq_work->queue_num);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
		ibdev_err(ibdev, "Local access violation work queue 0x%x error, sub_event type is: %d\n",
			  irq_work->queue_num, irq_work->sub_type);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
		ibdev_warn(ibdev, "SRQ limit reach.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
		ibdev_warn(ibdev, "SRQ last wqe reach.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
		ibdev_err(ibdev, "SRQ catas error.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		ibdev_err(ibdev, "CQ 0x%x access err.\n", irq_work->queue_num);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
		ibdev_warn(ibdev, "CQ 0x%x overflow\n", irq_work->queue_num);
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_DB_OVERFLOW:
		ibdev_warn(ibdev, "DB overflow.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_FLR:
		ibdev_warn(ibdev, "Function level reset.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_XRCD_VIOLATION:
		ibdev_err(ibdev, "xrc domain violation error.\n");
		अवरोध;
	हाल HNS_ROCE_EVENT_TYPE_INVALID_XRCETH:
		ibdev_err(ibdev, "invalid xrceth error.\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(irq_work);
पूर्ण

अटल व्योम hns_roce_v2_init_irq_work(काष्ठा hns_roce_dev *hr_dev,
				      काष्ठा hns_roce_eq *eq, u32 queue_num)
अणु
	काष्ठा hns_roce_work *irq_work;

	irq_work = kzalloc(माप(काष्ठा hns_roce_work), GFP_ATOMIC);
	अगर (!irq_work)
		वापस;

	INIT_WORK(&(irq_work->work), hns_roce_irq_work_handle);
	irq_work->hr_dev = hr_dev;
	irq_work->event_type = eq->event_type;
	irq_work->sub_type = eq->sub_type;
	irq_work->queue_num = queue_num;
	queue_work(hr_dev->irq_workq, &(irq_work->work));
पूर्ण

अटल व्योम update_eq_db(काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_dev *hr_dev = eq->hr_dev;
	काष्ठा hns_roce_v2_db eq_db = अणुपूर्ण;

	अगर (eq->type_flag == HNS_ROCE_AEQ) अणु
		roce_set_field(eq_db.byte_4, V2_EQ_DB_CMD_M, V2_EQ_DB_CMD_S,
			       eq->arm_st == HNS_ROCE_V2_EQ_ALWAYS_ARMED ?
			       HNS_ROCE_EQ_DB_CMD_AEQ :
			       HNS_ROCE_EQ_DB_CMD_AEQ_ARMED);
	पूर्ण अन्यथा अणु
		roce_set_field(eq_db.byte_4, V2_EQ_DB_TAG_M, V2_EQ_DB_TAG_S,
			       eq->eqn);

		roce_set_field(eq_db.byte_4, V2_EQ_DB_CMD_M, V2_EQ_DB_CMD_S,
			       eq->arm_st == HNS_ROCE_V2_EQ_ALWAYS_ARMED ?
			       HNS_ROCE_EQ_DB_CMD_CEQ :
			       HNS_ROCE_EQ_DB_CMD_CEQ_ARMED);
	पूर्ण

	roce_set_field(eq_db.parameter, V2_EQ_DB_CONS_IDX_M,
		       V2_EQ_DB_CONS_IDX_S, eq->cons_index);

	hns_roce_ग_लिखो64(hr_dev, (__le32 *)&eq_db, eq->db_reg);
पूर्ण

अटल काष्ठा hns_roce_aeqe *next_aeqe_sw_v2(काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_aeqe *aeqe;

	aeqe = hns_roce_buf_offset(eq->mtr.kmem,
				   (eq->cons_index & (eq->entries - 1)) *
				   eq->eqe_size);

	वापस (roce_get_bit(aeqe->asyn, HNS_ROCE_V2_AEQ_AEQE_OWNER_S) ^
		!!(eq->cons_index & eq->entries)) ? aeqe : शून्य;
पूर्ण

अटल पूर्णांक hns_roce_v2_aeq_पूर्णांक(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_aeqe *aeqe = next_aeqe_sw_v2(eq);
	पूर्णांक aeqe_found = 0;
	पूर्णांक event_type;
	u32 queue_num;
	पूर्णांक sub_type;

	जबतक (aeqe) अणु
		/* Make sure we पढ़ो AEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		event_type = roce_get_field(aeqe->asyn,
					    HNS_ROCE_V2_AEQE_EVENT_TYPE_M,
					    HNS_ROCE_V2_AEQE_EVENT_TYPE_S);
		sub_type = roce_get_field(aeqe->asyn,
					  HNS_ROCE_V2_AEQE_SUB_TYPE_M,
					  HNS_ROCE_V2_AEQE_SUB_TYPE_S);
		queue_num = roce_get_field(aeqe->event.queue_event.num,
					   HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_M,
					   HNS_ROCE_V2_AEQE_EVENT_QUEUE_NUM_S);

		चयन (event_type) अणु
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG:
		हाल HNS_ROCE_EVENT_TYPE_PATH_MIG_FAILED:
		हाल HNS_ROCE_EVENT_TYPE_COMM_EST:
		हाल HNS_ROCE_EVENT_TYPE_SQ_DRAINED:
		हाल HNS_ROCE_EVENT_TYPE_WQ_CATAS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LAST_WQE_REACH:
		हाल HNS_ROCE_EVENT_TYPE_INV_REQ_LOCAL_WQ_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_LOCAL_WQ_ACCESS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_XRCD_VIOLATION:
		हाल HNS_ROCE_EVENT_TYPE_INVALID_XRCETH:
			hns_roce_qp_event(hr_dev, queue_num, event_type);
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_SRQ_LIMIT_REACH:
		हाल HNS_ROCE_EVENT_TYPE_SRQ_CATAS_ERROR:
			hns_roce_srq_event(hr_dev, queue_num, event_type);
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_CQ_ACCESS_ERROR:
		हाल HNS_ROCE_EVENT_TYPE_CQ_OVERFLOW:
			hns_roce_cq_event(hr_dev, queue_num, event_type);
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_MB:
			hns_roce_cmd_event(hr_dev,
					le16_to_cpu(aeqe->event.cmd.token),
					aeqe->event.cmd.status,
					le64_to_cpu(aeqe->event.cmd.out_param));
			अवरोध;
		हाल HNS_ROCE_EVENT_TYPE_DB_OVERFLOW:
		हाल HNS_ROCE_EVENT_TYPE_FLR:
			अवरोध;
		शेष:
			dev_err(dev, "Unhandled event %d on EQ %d at idx %u.\n",
				event_type, eq->eqn, eq->cons_index);
			अवरोध;
		पूर्ण

		eq->event_type = event_type;
		eq->sub_type = sub_type;
		++eq->cons_index;
		aeqe_found = 1;

		hns_roce_v2_init_irq_work(hr_dev, eq, queue_num);

		aeqe = next_aeqe_sw_v2(eq);
	पूर्ण

	update_eq_db(eq);
	वापस aeqe_found;
पूर्ण

अटल काष्ठा hns_roce_ceqe *next_ceqe_sw_v2(काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_ceqe *ceqe;

	ceqe = hns_roce_buf_offset(eq->mtr.kmem,
				   (eq->cons_index & (eq->entries - 1)) *
				   eq->eqe_size);

	वापस (!!(roce_get_bit(ceqe->comp, HNS_ROCE_V2_CEQ_CEQE_OWNER_S))) ^
		(!!(eq->cons_index & eq->entries)) ? ceqe : शून्य;
पूर्ण

अटल पूर्णांक hns_roce_v2_ceq_पूर्णांक(काष्ठा hns_roce_dev *hr_dev,
			       काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_ceqe *ceqe = next_ceqe_sw_v2(eq);
	पूर्णांक ceqe_found = 0;
	u32 cqn;

	जबतक (ceqe) अणु
		/* Make sure we पढ़ो CEQ entry after we have checked the
		 * ownership bit
		 */
		dma_rmb();

		cqn = roce_get_field(ceqe->comp, HNS_ROCE_V2_CEQE_COMP_CQN_M,
				     HNS_ROCE_V2_CEQE_COMP_CQN_S);

		hns_roce_cq_completion(hr_dev, cqn);

		++eq->cons_index;
		ceqe_found = 1;

		ceqe = next_ceqe_sw_v2(eq);
	पूर्ण

	update_eq_db(eq);

	वापस ceqe_found;
पूर्ण

अटल irqवापस_t hns_roce_v2_msix_पूर्णांकerrupt_eq(पूर्णांक irq, व्योम *eq_ptr)
अणु
	काष्ठा hns_roce_eq *eq = eq_ptr;
	काष्ठा hns_roce_dev *hr_dev = eq->hr_dev;
	पूर्णांक पूर्णांक_work;

	अगर (eq->type_flag == HNS_ROCE_CEQ)
		/* Completion event पूर्णांकerrupt */
		पूर्णांक_work = hns_roce_v2_ceq_पूर्णांक(hr_dev, eq);
	अन्यथा
		/* Asychronous event पूर्णांकerrupt */
		पूर्णांक_work = hns_roce_v2_aeq_पूर्णांक(hr_dev, eq);

	वापस IRQ_RETVAL(पूर्णांक_work);
पूर्ण

अटल irqवापस_t hns_roce_v2_msix_पूर्णांकerrupt_abn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hns_roce_dev *hr_dev = dev_id;
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक पूर्णांक_work = 0;
	u32 पूर्णांक_st;
	u32 पूर्णांक_en;

	/* Abnormal पूर्णांकerrupt */
	पूर्णांक_st = roce_पढ़ो(hr_dev, ROCEE_VF_ABN_INT_ST_REG);
	पूर्णांक_en = roce_पढ़ो(hr_dev, ROCEE_VF_ABN_INT_EN_REG);

	अगर (पूर्णांक_st & BIT(HNS_ROCE_V2_VF_INT_ST_AEQ_OVERFLOW_S)) अणु
		काष्ठा pci_dev *pdev = hr_dev->pci_dev;
		काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);
		स्थिर काष्ठा hnae3_ae_ops *ops = ae_dev->ops;

		dev_err(dev, "AEQ overflow!\n");

		पूर्णांक_st |= 1 << HNS_ROCE_V2_VF_INT_ST_AEQ_OVERFLOW_S;
		roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_ST_REG, पूर्णांक_st);

		/* Set reset level क्रम reset_event() */
		अगर (ops->set_शेष_reset_request)
			ops->set_शेष_reset_request(ae_dev,
						       HNAE3_FUNC_RESET);
		अगर (ops->reset_event)
			ops->reset_event(pdev, शून्य);

		पूर्णांक_en |= 1 << HNS_ROCE_V2_VF_ABN_INT_EN_S;
		roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_EN_REG, पूर्णांक_en);

		पूर्णांक_work = 1;
	पूर्ण अन्यथा अगर (पूर्णांक_st & BIT(HNS_ROCE_V2_VF_INT_ST_RAS_INT_S)) अणु
		dev_err(dev, "RAS interrupt!\n");

		पूर्णांक_st |= 1 << HNS_ROCE_V2_VF_INT_ST_RAS_INT_S;
		roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_ST_REG, पूर्णांक_st);

		पूर्णांक_en |= 1 << HNS_ROCE_V2_VF_ABN_INT_EN_S;
		roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_EN_REG, पूर्णांक_en);

		पूर्णांक_work = 1;
	पूर्ण अन्यथा अणु
		dev_err(dev, "There is no abnormal irq found!\n");
	पूर्ण

	वापस IRQ_RETVAL(पूर्णांक_work);
पूर्ण

अटल व्योम hns_roce_v2_पूर्णांक_mask_enable(काष्ठा hns_roce_dev *hr_dev,
					पूर्णांक eq_num, u32 enable_flag)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < eq_num; i++)
		roce_ग_लिखो(hr_dev, ROCEE_VF_EVENT_INT_EN_REG +
			   i * EQ_REG_OFFSET, enable_flag);

	roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_EN_REG, enable_flag);
	roce_ग_लिखो(hr_dev, ROCEE_VF_ABN_INT_CFG_REG, enable_flag);
पूर्ण

अटल व्योम hns_roce_v2_destroy_eqc(काष्ठा hns_roce_dev *hr_dev, पूर्णांक eqn)
अणु
	काष्ठा device *dev = hr_dev->dev;
	पूर्णांक ret;

	अगर (eqn < hr_dev->caps.num_comp_vectors)
		ret = hns_roce_cmd_mbox(hr_dev, 0, 0, eqn & HNS_ROCE_V2_EQN_M,
					0, HNS_ROCE_CMD_DESTROY_CEQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
	अन्यथा
		ret = hns_roce_cmd_mbox(hr_dev, 0, 0, eqn & HNS_ROCE_V2_EQN_M,
					0, HNS_ROCE_CMD_DESTROY_AEQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret)
		dev_err(dev, "[mailbox cmd] destroy eqc(%d) failed.\n", eqn);
पूर्ण

अटल व्योम मुक्त_eq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_eq *eq)
अणु
	hns_roce_mtr_destroy(hr_dev, &eq->mtr);
पूर्ण

अटल व्योम init_eq_config(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_eq *eq)
अणु
	eq->db_reg = hr_dev->reg_base + ROCEE_VF_EQ_DB_CFG0_REG;
	eq->cons_index = 0;
	eq->over_ignore = HNS_ROCE_V2_EQ_OVER_IGNORE_0;
	eq->coalesce = HNS_ROCE_V2_EQ_COALESCE_0;
	eq->arm_st = HNS_ROCE_V2_EQ_ALWAYS_ARMED;
	eq->shअगरt = ilog2((अचिन्हित पूर्णांक)eq->entries);
पूर्ण

अटल पूर्णांक config_eqc(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_eq *eq,
		      व्योम *mb_buf)
अणु
	u64 eqe_ba[MTT_MIN_COUNT] = अणु 0 पूर्ण;
	काष्ठा hns_roce_eq_context *eqc;
	u64 bt_ba = 0;
	पूर्णांक count;

	eqc = mb_buf;
	स_रखो(eqc, 0, माप(काष्ठा hns_roce_eq_context));

	init_eq_config(hr_dev, eq);

	/* अगर not multi-hop, eqe buffer only use one trunk */
	count = hns_roce_mtr_find(hr_dev, &eq->mtr, 0, eqe_ba, MTT_MIN_COUNT,
				  &bt_ba);
	अगर (count < 1) अणु
		dev_err(hr_dev->dev, "failed to find EQE mtr\n");
		वापस -ENOBUFS;
	पूर्ण

	hr_reg_ग_लिखो(eqc, EQC_EQ_ST, HNS_ROCE_V2_EQ_STATE_VALID);
	hr_reg_ग_लिखो(eqc, EQC_EQE_HOP_NUM, eq->hop_num);
	hr_reg_ग_लिखो(eqc, EQC_OVER_IGNORE, eq->over_ignore);
	hr_reg_ग_लिखो(eqc, EQC_COALESCE, eq->coalesce);
	hr_reg_ग_लिखो(eqc, EQC_ARM_ST, eq->arm_st);
	hr_reg_ग_लिखो(eqc, EQC_EQN, eq->eqn);
	hr_reg_ग_लिखो(eqc, EQC_EQE_CNT, HNS_ROCE_EQ_INIT_EQE_CNT);
	hr_reg_ग_लिखो(eqc, EQC_EQE_BA_PG_SZ,
		     to_hr_hw_page_shअगरt(eq->mtr.hem_cfg.ba_pg_shअगरt));
	hr_reg_ग_लिखो(eqc, EQC_EQE_BUF_PG_SZ,
		     to_hr_hw_page_shअगरt(eq->mtr.hem_cfg.buf_pg_shअगरt));
	hr_reg_ग_लिखो(eqc, EQC_EQ_PROD_INDX, HNS_ROCE_EQ_INIT_PROD_IDX);
	hr_reg_ग_लिखो(eqc, EQC_EQ_MAX_CNT, eq->eq_max_cnt);

	hr_reg_ग_लिखो(eqc, EQC_EQ_PERIOD, eq->eq_period);
	hr_reg_ग_लिखो(eqc, EQC_EQE_REPORT_TIMER, HNS_ROCE_EQ_INIT_REPORT_TIMER);
	hr_reg_ग_लिखो(eqc, EQC_EQE_BA_L, bt_ba >> 3);
	hr_reg_ग_लिखो(eqc, EQC_EQE_BA_H, bt_ba >> 35);
	hr_reg_ग_लिखो(eqc, EQC_SHIFT, eq->shअगरt);
	hr_reg_ग_लिखो(eqc, EQC_MSI_INDX, HNS_ROCE_EQ_INIT_MSI_IDX);
	hr_reg_ग_लिखो(eqc, EQC_CUR_EQE_BA_L, eqe_ba[0] >> 12);
	hr_reg_ग_लिखो(eqc, EQC_CUR_EQE_BA_M, eqe_ba[0] >> 28);
	hr_reg_ग_लिखो(eqc, EQC_CUR_EQE_BA_H, eqe_ba[0] >> 60);
	hr_reg_ग_लिखो(eqc, EQC_EQ_CONS_INDX, HNS_ROCE_EQ_INIT_CONS_IDX);
	hr_reg_ग_लिखो(eqc, EQC_NEX_EQE_BA_L, eqe_ba[1] >> 12);
	hr_reg_ग_लिखो(eqc, EQC_NEX_EQE_BA_H, eqe_ba[1] >> 44);
	hr_reg_ग_लिखो(eqc, EQC_EQE_SIZE,
		     !!(eq->eqe_size == HNS_ROCE_V3_EQE_SIZE));

	वापस 0;
पूर्ण

अटल पूर्णांक alloc_eq_buf(काष्ठा hns_roce_dev *hr_dev, काष्ठा hns_roce_eq *eq)
अणु
	काष्ठा hns_roce_buf_attr buf_attr = अणुपूर्ण;
	पूर्णांक err;

	अगर (hr_dev->caps.eqe_hop_num == HNS_ROCE_HOP_NUM_0)
		eq->hop_num = 0;
	अन्यथा
		eq->hop_num = hr_dev->caps.eqe_hop_num;

	buf_attr.page_shअगरt = hr_dev->caps.eqe_buf_pg_sz + HNS_HW_PAGE_SHIFT;
	buf_attr.region[0].size = eq->entries * eq->eqe_size;
	buf_attr.region[0].hopnum = eq->hop_num;
	buf_attr.region_count = 1;

	err = hns_roce_mtr_create(hr_dev, &eq->mtr, &buf_attr,
				  hr_dev->caps.eqe_ba_pg_sz +
				  HNS_HW_PAGE_SHIFT, शून्य, 0);
	अगर (err)
		dev_err(hr_dev->dev, "Failed to alloc EQE mtr, err %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक hns_roce_v2_create_eq(काष्ठा hns_roce_dev *hr_dev,
				 काष्ठा hns_roce_eq *eq,
				 अचिन्हित पूर्णांक eq_cmd)
अणु
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	/* Allocate mailbox memory */
	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR_OR_शून्य(mailbox))
		वापस -ENOMEM;

	ret = alloc_eq_buf(hr_dev, eq);
	अगर (ret)
		जाओ मुक्त_cmd_mbox;

	ret = config_eqc(hr_dev, eq, mailbox->buf);
	अगर (ret)
		जाओ err_cmd_mbox;

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, eq->eqn, 0,
				eq_cmd, HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "[mailbox cmd] create eqc failed.\n");
		जाओ err_cmd_mbox;
	पूर्ण

	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस 0;

err_cmd_mbox:
	मुक्त_eq_buf(hr_dev, eq);

मुक्त_cmd_mbox:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ret;
पूर्ण

अटल पूर्णांक __hns_roce_request_irq(काष्ठा hns_roce_dev *hr_dev, पूर्णांक irq_num,
				  पूर्णांक comp_num, पूर्णांक aeq_num, पूर्णांक other_num)
अणु
	काष्ठा hns_roce_eq_table *eq_table = &hr_dev->eq_table;
	पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < irq_num; i++) अणु
		hr_dev->irq_names[i] = kzalloc(HNS_ROCE_INT_NAME_LEN,
					       GFP_KERNEL);
		अगर (!hr_dev->irq_names[i]) अणु
			ret = -ENOMEM;
			जाओ err_kzalloc_failed;
		पूर्ण
	पूर्ण

	/* irq contains: abnormal + AEQ + CEQ */
	क्रम (j = 0; j < other_num; j++)
		snम_लिखो((अक्षर *)hr_dev->irq_names[j], HNS_ROCE_INT_NAME_LEN,
			 "hns-abn-%d", j);

	क्रम (j = other_num; j < (other_num + aeq_num); j++)
		snम_लिखो((अक्षर *)hr_dev->irq_names[j], HNS_ROCE_INT_NAME_LEN,
			 "hns-aeq-%d", j - other_num);

	क्रम (j = (other_num + aeq_num); j < irq_num; j++)
		snम_लिखो((अक्षर *)hr_dev->irq_names[j], HNS_ROCE_INT_NAME_LEN,
			 "hns-ceq-%d", j - other_num - aeq_num);

	क्रम (j = 0; j < irq_num; j++) अणु
		अगर (j < other_num)
			ret = request_irq(hr_dev->irq[j],
					  hns_roce_v2_msix_पूर्णांकerrupt_abn,
					  0, hr_dev->irq_names[j], hr_dev);

		अन्यथा अगर (j < (other_num + comp_num))
			ret = request_irq(eq_table->eq[j - other_num].irq,
					  hns_roce_v2_msix_पूर्णांकerrupt_eq,
					  0, hr_dev->irq_names[j + aeq_num],
					  &eq_table->eq[j - other_num]);
		अन्यथा
			ret = request_irq(eq_table->eq[j - other_num].irq,
					  hns_roce_v2_msix_पूर्णांकerrupt_eq,
					  0, hr_dev->irq_names[j - comp_num],
					  &eq_table->eq[j - other_num]);
		अगर (ret) अणु
			dev_err(hr_dev->dev, "Request irq error!\n");
			जाओ err_request_failed;
		पूर्ण
	पूर्ण

	वापस 0;

err_request_failed:
	क्रम (j -= 1; j >= 0; j--)
		अगर (j < other_num)
			मुक्त_irq(hr_dev->irq[j], hr_dev);
		अन्यथा
			मुक्त_irq(eq_table->eq[j - other_num].irq,
				 &eq_table->eq[j - other_num]);

err_kzalloc_failed:
	क्रम (i -= 1; i >= 0; i--)
		kमुक्त(hr_dev->irq_names[i]);

	वापस ret;
पूर्ण

अटल व्योम __hns_roce_मुक्त_irq(काष्ठा hns_roce_dev *hr_dev)
अणु
	पूर्णांक irq_num;
	पूर्णांक eq_num;
	पूर्णांक i;

	eq_num = hr_dev->caps.num_comp_vectors + hr_dev->caps.num_aeq_vectors;
	irq_num = eq_num + hr_dev->caps.num_other_vectors;

	क्रम (i = 0; i < hr_dev->caps.num_other_vectors; i++)
		मुक्त_irq(hr_dev->irq[i], hr_dev);

	क्रम (i = 0; i < eq_num; i++)
		मुक्त_irq(hr_dev->eq_table.eq[i].irq, &hr_dev->eq_table.eq[i]);

	क्रम (i = 0; i < irq_num; i++)
		kमुक्त(hr_dev->irq_names[i]);
पूर्ण

अटल पूर्णांक hns_roce_v2_init_eq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_eq_table *eq_table = &hr_dev->eq_table;
	काष्ठा device *dev = hr_dev->dev;
	काष्ठा hns_roce_eq *eq;
	अचिन्हित पूर्णांक eq_cmd;
	पूर्णांक irq_num;
	पूर्णांक eq_num;
	पूर्णांक other_num;
	पूर्णांक comp_num;
	पूर्णांक aeq_num;
	पूर्णांक i;
	पूर्णांक ret;

	other_num = hr_dev->caps.num_other_vectors;
	comp_num = hr_dev->caps.num_comp_vectors;
	aeq_num = hr_dev->caps.num_aeq_vectors;

	eq_num = comp_num + aeq_num;
	irq_num = eq_num + other_num;

	eq_table->eq = kसुस्मृति(eq_num, माप(*eq_table->eq), GFP_KERNEL);
	अगर (!eq_table->eq)
		वापस -ENOMEM;

	/* create eq */
	क्रम (i = 0; i < eq_num; i++) अणु
		eq = &eq_table->eq[i];
		eq->hr_dev = hr_dev;
		eq->eqn = i;
		अगर (i < comp_num) अणु
			/* CEQ */
			eq_cmd = HNS_ROCE_CMD_CREATE_CEQC;
			eq->type_flag = HNS_ROCE_CEQ;
			eq->entries = hr_dev->caps.ceqe_depth;
			eq->eqe_size = hr_dev->caps.ceqe_size;
			eq->irq = hr_dev->irq[i + other_num + aeq_num];
			eq->eq_max_cnt = HNS_ROCE_CEQ_DEFAULT_BURST_NUM;
			eq->eq_period = HNS_ROCE_CEQ_DEFAULT_INTERVAL;
		पूर्ण अन्यथा अणु
			/* AEQ */
			eq_cmd = HNS_ROCE_CMD_CREATE_AEQC;
			eq->type_flag = HNS_ROCE_AEQ;
			eq->entries = hr_dev->caps.aeqe_depth;
			eq->eqe_size = hr_dev->caps.aeqe_size;
			eq->irq = hr_dev->irq[i - comp_num + other_num];
			eq->eq_max_cnt = HNS_ROCE_AEQ_DEFAULT_BURST_NUM;
			eq->eq_period = HNS_ROCE_AEQ_DEFAULT_INTERVAL;
		पूर्ण

		ret = hns_roce_v2_create_eq(hr_dev, eq, eq_cmd);
		अगर (ret) अणु
			dev_err(dev, "eq create failed.\n");
			जाओ err_create_eq_fail;
		पूर्ण
	पूर्ण

	/* enable irq */
	hns_roce_v2_पूर्णांक_mask_enable(hr_dev, eq_num, EQ_ENABLE);

	ret = __hns_roce_request_irq(hr_dev, irq_num, comp_num,
				     aeq_num, other_num);
	अगर (ret) अणु
		dev_err(dev, "Request irq failed.\n");
		जाओ err_request_irq_fail;
	पूर्ण

	hr_dev->irq_workq = alloc_ordered_workqueue("hns_roce_irq_workq", 0);
	अगर (!hr_dev->irq_workq) अणु
		dev_err(dev, "Create irq workqueue failed!\n");
		ret = -ENOMEM;
		जाओ err_create_wq_fail;
	पूर्ण

	वापस 0;

err_create_wq_fail:
	__hns_roce_मुक्त_irq(hr_dev);

err_request_irq_fail:
	hns_roce_v2_पूर्णांक_mask_enable(hr_dev, eq_num, EQ_DISABLE);

err_create_eq_fail:
	क्रम (i -= 1; i >= 0; i--)
		मुक्त_eq_buf(hr_dev, &eq_table->eq[i]);
	kमुक्त(eq_table->eq);

	वापस ret;
पूर्ण

अटल व्योम hns_roce_v2_cleanup_eq_table(काष्ठा hns_roce_dev *hr_dev)
अणु
	काष्ठा hns_roce_eq_table *eq_table = &hr_dev->eq_table;
	पूर्णांक eq_num;
	पूर्णांक i;

	eq_num = hr_dev->caps.num_comp_vectors + hr_dev->caps.num_aeq_vectors;

	/* Disable irq */
	hns_roce_v2_पूर्णांक_mask_enable(hr_dev, eq_num, EQ_DISABLE);

	__hns_roce_मुक्त_irq(hr_dev);
	destroy_workqueue(hr_dev->irq_workq);

	क्रम (i = 0; i < eq_num; i++) अणु
		hns_roce_v2_destroy_eqc(hr_dev, i);

		मुक्त_eq_buf(hr_dev, &eq_table->eq[i]);
	पूर्ण

	kमुक्त(eq_table->eq);
पूर्ण

अटल स्थिर काष्ठा hns_roce_dfx_hw hns_roce_dfx_hw_v2 = अणु
	.query_cqc_info = hns_roce_v2_query_cqc_info,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_v2_dev_ops = अणु
	.destroy_qp = hns_roce_v2_destroy_qp,
	.modअगरy_cq = hns_roce_v2_modअगरy_cq,
	.poll_cq = hns_roce_v2_poll_cq,
	.post_recv = hns_roce_v2_post_recv,
	.post_send = hns_roce_v2_post_send,
	.query_qp = hns_roce_v2_query_qp,
	.req_notअगरy_cq = hns_roce_v2_req_notअगरy_cq,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops hns_roce_v2_dev_srq_ops = अणु
	.modअगरy_srq = hns_roce_v2_modअगरy_srq,
	.post_srq_recv = hns_roce_v2_post_srq_recv,
	.query_srq = hns_roce_v2_query_srq,
पूर्ण;

अटल स्थिर काष्ठा hns_roce_hw hns_roce_hw_v2 = अणु
	.cmq_init = hns_roce_v2_cmq_init,
	.cmq_निकास = hns_roce_v2_cmq_निकास,
	.hw_profile = hns_roce_v2_profile,
	.hw_init = hns_roce_v2_init,
	.hw_निकास = hns_roce_v2_निकास,
	.post_mbox = v2_post_mbox,
	.poll_mbox_करोne = v2_poll_mbox_करोne,
	.chk_mbox_avail = v2_chk_mbox_is_avail,
	.set_gid = hns_roce_v2_set_gid,
	.set_mac = hns_roce_v2_set_mac,
	.ग_लिखो_mtpt = hns_roce_v2_ग_लिखो_mtpt,
	.rereg_ग_लिखो_mtpt = hns_roce_v2_rereg_ग_लिखो_mtpt,
	.frmr_ग_लिखो_mtpt = hns_roce_v2_frmr_ग_लिखो_mtpt,
	.mw_ग_लिखो_mtpt = hns_roce_v2_mw_ग_लिखो_mtpt,
	.ग_लिखो_cqc = hns_roce_v2_ग_लिखो_cqc,
	.set_hem = hns_roce_v2_set_hem,
	.clear_hem = hns_roce_v2_clear_hem,
	.modअगरy_qp = hns_roce_v2_modअगरy_qp,
	.qp_flow_control_init = hns_roce_v2_qp_flow_control_init,
	.init_eq = hns_roce_v2_init_eq_table,
	.cleanup_eq = hns_roce_v2_cleanup_eq_table,
	.ग_लिखो_srqc = hns_roce_v2_ग_लिखो_srqc,
	.hns_roce_dev_ops = &hns_roce_v2_dev_ops,
	.hns_roce_dev_srq_ops = &hns_roce_v2_dev_srq_ops,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hns_roce_hw_v2_pci_tbl[] = अणु
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_25GE_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_50GE_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_100G_RDMA_MACSEC), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_200G_RDMA), 0पूर्ण,
	अणुPCI_VDEVICE(HUAWEI, HNAE3_DEV_ID_RDMA_DCB_PFC_VF),
	 HNAE3_DEV_SUPPORT_ROCE_DCB_BITSपूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hns_roce_hw_v2_pci_tbl);

अटल व्योम hns_roce_hw_v2_get_cfg(काष्ठा hns_roce_dev *hr_dev,
				  काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hns_roce_v2_priv *priv = hr_dev->priv;
	स्थिर काष्ठा pci_device_id *id;
	पूर्णांक i;

	hr_dev->pci_dev = handle->pdev;
	id = pci_match_id(hns_roce_hw_v2_pci_tbl, hr_dev->pci_dev);
	hr_dev->is_vf = id->driver_data;
	hr_dev->dev = &handle->pdev->dev;
	hr_dev->hw = &hns_roce_hw_v2;
	hr_dev->dfx = &hns_roce_dfx_hw_v2;
	hr_dev->sdb_offset = ROCEE_DB_SQ_L_0_REG;
	hr_dev->odb_offset = hr_dev->sdb_offset;

	/* Get info from NIC driver. */
	hr_dev->reg_base = handle->rinfo.roce_io_base;
	hr_dev->mem_base = handle->rinfo.roce_mem_base;
	hr_dev->caps.num_ports = 1;
	hr_dev->iboe.netdevs[0] = handle->rinfo.netdev;
	hr_dev->iboe.phy_port[0] = 0;

	addrconf_addr_eui48((u8 *)&hr_dev->ib_dev.node_guid,
			    hr_dev->iboe.netdevs[0]->dev_addr);

	क्रम (i = 0; i < handle->rinfo.num_vectors; i++)
		hr_dev->irq[i] = pci_irq_vector(handle->pdev,
						i + handle->rinfo.base_vector);

	/* cmd issue mode: 0 is poll, 1 is event */
	hr_dev->cmd_mod = 1;
	hr_dev->loop_idc = 0;

	hr_dev->reset_cnt = handle->ae_algo->ops->ae_dev_reset_cnt(handle);
	priv->handle = handle;
पूर्ण

अटल पूर्णांक __hns_roce_hw_v2_init_instance(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hns_roce_dev *hr_dev;
	पूर्णांक ret;

	hr_dev = ib_alloc_device(hns_roce_dev, ib_dev);
	अगर (!hr_dev)
		वापस -ENOMEM;

	hr_dev->priv = kzalloc(माप(काष्ठा hns_roce_v2_priv), GFP_KERNEL);
	अगर (!hr_dev->priv) अणु
		ret = -ENOMEM;
		जाओ error_failed_kzalloc;
	पूर्ण

	hns_roce_hw_v2_get_cfg(hr_dev, handle);

	ret = hns_roce_init(hr_dev);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "RoCE Engine init failed!\n");
		जाओ error_failed_get_cfg;
	पूर्ण

	handle->priv = hr_dev;

	वापस 0;

error_failed_get_cfg:
	kमुक्त(hr_dev->priv);

error_failed_kzalloc:
	ib_dealloc_device(&hr_dev->ib_dev);

	वापस ret;
पूर्ण

अटल व्योम __hns_roce_hw_v2_uninit_instance(काष्ठा hnae3_handle *handle,
					   bool reset)
अणु
	काष्ठा hns_roce_dev *hr_dev = handle->priv;

	अगर (!hr_dev)
		वापस;

	handle->priv = शून्य;

	hr_dev->state = HNS_ROCE_DEVICE_STATE_UNINIT;
	hns_roce_handle_device_err(hr_dev);

	hns_roce_निकास(hr_dev);
	kमुक्त(hr_dev->priv);
	ib_dealloc_device(&hr_dev->ib_dev);
पूर्ण

अटल पूर्णांक hns_roce_hw_v2_init_instance(काष्ठा hnae3_handle *handle)
अणु
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	स्थिर काष्ठा pci_device_id *id;
	काष्ठा device *dev = &handle->pdev->dev;
	पूर्णांक ret;

	handle->rinfo.instance_state = HNS_ROCE_STATE_INIT;

	अगर (ops->ae_dev_resetting(handle) || ops->get_hw_reset_stat(handle)) अणु
		handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
		जाओ reset_chk_err;
	पूर्ण

	id = pci_match_id(hns_roce_hw_v2_pci_tbl, handle->pdev);
	अगर (!id)
		वापस 0;

	अगर (id->driver_data && handle->pdev->revision < PCI_REVISION_ID_HIP09)
		वापस 0;

	ret = __hns_roce_hw_v2_init_instance(handle);
	अगर (ret) अणु
		handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
		dev_err(dev, "RoCE instance init failed! ret = %d\n", ret);
		अगर (ops->ae_dev_resetting(handle) ||
		    ops->get_hw_reset_stat(handle))
			जाओ reset_chk_err;
		अन्यथा
			वापस ret;
	पूर्ण

	handle->rinfo.instance_state = HNS_ROCE_STATE_INITED;


	वापस 0;

reset_chk_err:
	dev_err(dev, "Device is busy in resetting state.\n"
		     "please retry later.\n");

	वापस -EBUSY;
पूर्ण

अटल व्योम hns_roce_hw_v2_uninit_instance(काष्ठा hnae3_handle *handle,
					   bool reset)
अणु
	अगर (handle->rinfo.instance_state != HNS_ROCE_STATE_INITED)
		वापस;

	handle->rinfo.instance_state = HNS_ROCE_STATE_UNINIT;

	__hns_roce_hw_v2_uninit_instance(handle, reset);

	handle->rinfo.instance_state = HNS_ROCE_STATE_NON_INIT;
पूर्ण
अटल पूर्णांक hns_roce_hw_v2_reset_notअगरy_करोwn(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hns_roce_dev *hr_dev;

	अगर (handle->rinfo.instance_state != HNS_ROCE_STATE_INITED) अणु
		set_bit(HNS_ROCE_RST_सूचीECT_RETURN, &handle->rinfo.state);
		वापस 0;
	पूर्ण

	handle->rinfo.reset_state = HNS_ROCE_STATE_RST_DOWN;
	clear_bit(HNS_ROCE_RST_सूचीECT_RETURN, &handle->rinfo.state);

	hr_dev = handle->priv;
	अगर (!hr_dev)
		वापस 0;

	hr_dev->is_reset = true;
	hr_dev->active = false;
	hr_dev->dis_db = true;

	hr_dev->state = HNS_ROCE_DEVICE_STATE_RST_DOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_hw_v2_reset_notअगरy_init(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा device *dev = &handle->pdev->dev;
	पूर्णांक ret;

	अगर (test_and_clear_bit(HNS_ROCE_RST_सूचीECT_RETURN,
			       &handle->rinfo.state)) अणु
		handle->rinfo.reset_state = HNS_ROCE_STATE_RST_INITED;
		वापस 0;
	पूर्ण

	handle->rinfo.reset_state = HNS_ROCE_STATE_RST_INIT;

	dev_info(&handle->pdev->dev, "In reset process RoCE client reinit.\n");
	ret = __hns_roce_hw_v2_init_instance(handle);
	अगर (ret) अणु
		/* when reset notअगरy type is HNAE3_INIT_CLIENT In reset notअगरy
		 * callback function, RoCE Engine reinitialize. If RoCE reinit
		 * failed, we should inक्रमm NIC driver.
		 */
		handle->priv = शून्य;
		dev_err(dev, "In reset process RoCE reinit failed %d.\n", ret);
	पूर्ण अन्यथा अणु
		handle->rinfo.reset_state = HNS_ROCE_STATE_RST_INITED;
		dev_info(dev, "Reset done, RoCE client reinit finished.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hns_roce_hw_v2_reset_notअगरy_uninit(काष्ठा hnae3_handle *handle)
अणु
	अगर (test_bit(HNS_ROCE_RST_सूचीECT_RETURN, &handle->rinfo.state))
		वापस 0;

	handle->rinfo.reset_state = HNS_ROCE_STATE_RST_UNINIT;
	dev_info(&handle->pdev->dev, "In reset process RoCE client uninit.\n");
	msleep(HNS_ROCE_V2_HW_RST_UNINT_DELAY);
	__hns_roce_hw_v2_uninit_instance(handle, false);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_roce_hw_v2_reset_notअगरy(काष्ठा hnae3_handle *handle,
				       क्रमागत hnae3_reset_notअगरy_type type)
अणु
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल HNAE3_DOWN_CLIENT:
		ret = hns_roce_hw_v2_reset_notअगरy_करोwn(handle);
		अवरोध;
	हाल HNAE3_INIT_CLIENT:
		ret = hns_roce_hw_v2_reset_notअगरy_init(handle);
		अवरोध;
	हाल HNAE3_UNINIT_CLIENT:
		ret = hns_roce_hw_v2_reset_notअगरy_uninit(handle);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hnae3_client_ops hns_roce_hw_v2_ops = अणु
	.init_instance = hns_roce_hw_v2_init_instance,
	.uninit_instance = hns_roce_hw_v2_uninit_instance,
	.reset_notअगरy = hns_roce_hw_v2_reset_notअगरy,
पूर्ण;

अटल काष्ठा hnae3_client hns_roce_hw_v2_client = अणु
	.name = "hns_roce_hw_v2",
	.type = HNAE3_CLIENT_ROCE,
	.ops = &hns_roce_hw_v2_ops,
पूर्ण;

अटल पूर्णांक __init hns_roce_hw_v2_init(व्योम)
अणु
	वापस hnae3_रेजिस्टर_client(&hns_roce_hw_v2_client);
पूर्ण

अटल व्योम __निकास hns_roce_hw_v2_निकास(व्योम)
अणु
	hnae3_unरेजिस्टर_client(&hns_roce_hw_v2_client);
पूर्ण

module_init(hns_roce_hw_v2_init);
module_निकास(hns_roce_hw_v2_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Wei Hu <xavier.huwei@huawei.com>");
MODULE_AUTHOR("Lijun Ou <oulijun@huawei.com>");
MODULE_AUTHOR("Shaobo Xu <xushaobo2@huawei.com>");
MODULE_DESCRIPTION("Hisilicon Hip08 Family RoCE Driver");
