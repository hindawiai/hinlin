<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX5_CORE_CQ_H
#घोषणा MLX5_CORE_CQ_H

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/refcount.h>

काष्ठा mlx5_core_cq अणु
	u32			cqn;
	पूर्णांक			cqe_sz;
	__be32		       *set_ci_db;
	__be32		       *arm_db;
	काष्ठा mlx5_uars_page  *uar;
	refcount_t		refcount;
	काष्ठा completion	मुक्त;
	अचिन्हित		vector;
	अचिन्हित पूर्णांक		irqn;
	व्योम (*comp)(काष्ठा mlx5_core_cq *cq, काष्ठा mlx5_eqe *eqe);
	व्योम (*event)		(काष्ठा mlx5_core_cq *, क्रमागत mlx5_event);
	u32			cons_index;
	अचिन्हित		arm_sn;
	काष्ठा mlx5_rsc_debug	*dbg;
	पूर्णांक			pid;
	काष्ठा अणु
		काष्ठा list_head list;
		व्योम (*comp)(काष्ठा mlx5_core_cq *cq, काष्ठा mlx5_eqe *eqe);
		व्योम		*priv;
	पूर्ण tasklet_ctx;
	पूर्णांक			reset_notअगरy_added;
	काष्ठा list_head	reset_notअगरy;
	काष्ठा mlx5_eq_comp	*eq;
	u16 uid;
पूर्ण;


क्रमागत अणु
	MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR		= 0x01,
	MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR		= 0x02,
	MLX5_CQE_SYNDROME_LOCAL_PROT_ERR		= 0x04,
	MLX5_CQE_SYNDROME_WR_FLUSH_ERR			= 0x05,
	MLX5_CQE_SYNDROME_MW_BIND_ERR			= 0x06,
	MLX5_CQE_SYNDROME_BAD_RESP_ERR			= 0x10,
	MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR		= 0x11,
	MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR		= 0x12,
	MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR		= 0x13,
	MLX5_CQE_SYNDROME_REMOTE_OP_ERR			= 0x14,
	MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR	= 0x15,
	MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR		= 0x16,
	MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR		= 0x22,
पूर्ण;

क्रमागत अणु
	MLX5_CQE_OWNER_MASK	= 1,
	MLX5_CQE_REQ		= 0,
	MLX5_CQE_RESP_WR_IMM	= 1,
	MLX5_CQE_RESP_SEND	= 2,
	MLX5_CQE_RESP_SEND_IMM	= 3,
	MLX5_CQE_RESP_SEND_INV	= 4,
	MLX5_CQE_RESIZE_CQ	= 5,
	MLX5_CQE_संक_त्रुटि	= 12,
	MLX5_CQE_REQ_ERR	= 13,
	MLX5_CQE_RESP_ERR	= 14,
	MLX5_CQE_INVALID	= 15,
पूर्ण;

क्रमागत अणु
	MLX5_CQ_MODIFY_PERIOD	= 1 << 0,
	MLX5_CQ_MODIFY_COUNT	= 1 << 1,
	MLX5_CQ_MODIFY_OVERRUN	= 1 << 2,
पूर्ण;

क्रमागत अणु
	MLX5_CQ_OPMOD_RESIZE		= 1,
	MLX5_MODIFY_CQ_MASK_LOG_SIZE	= 1 << 0,
	MLX5_MODIFY_CQ_MASK_PG_OFFSET	= 1 << 1,
	MLX5_MODIFY_CQ_MASK_PG_SIZE	= 1 << 2,
पूर्ण;

काष्ठा mlx5_cq_modअगरy_params अणु
	पूर्णांक	type;
	जोड़ अणु
		काष्ठा अणु
			u32	page_offset;
			u8	log_cq_size;
		पूर्ण resize;

		काष्ठा अणु
		पूर्ण moder;

		काष्ठा अणु
		पूर्ण mapping;
	पूर्ण params;
पूर्ण;

क्रमागत अणु
	CQE_STRIDE_64 = 0,
	CQE_STRIDE_128 = 1,
	CQE_STRIDE_128_PAD = 2,
पूर्ण;

#घोषणा MLX5_MAX_CQ_PERIOD (BIT(__mlx5_bit_sz(cqc, cq_period)) - 1)
#घोषणा MLX5_MAX_CQ_COUNT (BIT(__mlx5_bit_sz(cqc, cq_max_count)) - 1)

अटल अंतरभूत पूर्णांक cqe_sz_to_mlx_sz(u8 size, पूर्णांक padding_128_en)
अणु
	वापस padding_128_en ? CQE_STRIDE_128_PAD :
				size == 64 ? CQE_STRIDE_64 : CQE_STRIDE_128;
पूर्ण

अटल अंतरभूत व्योम mlx5_cq_set_ci(काष्ठा mlx5_core_cq *cq)
अणु
	*cq->set_ci_db = cpu_to_be32(cq->cons_index & 0xffffff);
पूर्ण

क्रमागत अणु
	MLX5_CQ_DB_REQ_NOT_SOL		= 1 << 24,
	MLX5_CQ_DB_REQ_NOT		= 0 << 24
पूर्ण;

अटल अंतरभूत व्योम mlx5_cq_arm(काष्ठा mlx5_core_cq *cq, u32 cmd,
			       व्योम __iomem *uar_page,
			       u32 cons_index)
अणु
	__be32 करोorbell[2];
	u32 sn;
	u32 ci;

	sn = cq->arm_sn & 3;
	ci = cons_index & 0xffffff;

	*cq->arm_db = cpu_to_be32(sn << 28 | cmd | ci);

	/* Make sure that the करोorbell record in host memory is
	 * written beक्रमe ringing the करोorbell via PCI MMIO.
	 */
	wmb();

	करोorbell[0] = cpu_to_be32(sn << 28 | cmd | ci);
	करोorbell[1] = cpu_to_be32(cq->cqn);

	mlx5_ग_लिखो64(करोorbell, uar_page + MLX5_CQ_DOORBELL);
पूर्ण

अटल अंतरभूत व्योम mlx5_cq_hold(काष्ठा mlx5_core_cq *cq)
अणु
	refcount_inc(&cq->refcount);
पूर्ण

अटल अंतरभूत व्योम mlx5_cq_put(काष्ठा mlx5_core_cq *cq)
अणु
	अगर (refcount_dec_and_test(&cq->refcount))
		complete(&cq->मुक्त);
पूर्ण

पूर्णांक mlx5_core_create_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
			u32 *in, पूर्णांक inlen, u32 *out, पूर्णांक outlen);
पूर्णांक mlx5_core_destroy_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq);
पूर्णांक mlx5_core_query_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
		       u32 *out);
पूर्णांक mlx5_core_modअगरy_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
			u32 *in, पूर्णांक inlen);
पूर्णांक mlx5_core_modअगरy_cq_moderation(काष्ठा mlx5_core_dev *dev,
				   काष्ठा mlx5_core_cq *cq, u16 cq_period,
				   u16 cq_max_count);
अटल अंतरभूत व्योम mlx5_dump_err_cqe(काष्ठा mlx5_core_dev *dev,
				     काष्ठा mlx5_err_cqe *err_cqe)
अणु
	prपूर्णांक_hex_dump(KERN_WARNING, "", DUMP_PREFIX_OFFSET, 16, 1, err_cqe,
		       माप(*err_cqe), false);
पूर्ण
पूर्णांक mlx5_debug_cq_add(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq);
व्योम mlx5_debug_cq_हटाओ(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq);

#पूर्ण_अगर /* MLX5_CORE_CQ_H */
