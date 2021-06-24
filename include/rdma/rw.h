<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 HGST, a Western Digital Company.
 */
#अगर_अघोषित _RDMA_RW_H
#घोषणा _RDMA_RW_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/mr_pool.h>

काष्ठा rdma_rw_ctx अणु
	/* number of RDMA READ/WRITE WRs (not counting MR WRs) */
	u32			nr_ops;

	/* tag क्रम the जोड़ below: */
	u8			type;

	जोड़ अणु
		/* क्रम mapping a single SGE: */
		काष्ठा अणु
			काष्ठा ib_sge		sge;
			काष्ठा ib_rdma_wr	wr;
		पूर्ण single;

		/* क्रम mapping of multiple SGEs: */
		काष्ठा अणु
			काष्ठा ib_sge		*sges;
			काष्ठा ib_rdma_wr	*wrs;
		पूर्ण map;

		/* क्रम रेजिस्टरing multiple WRs: */
		काष्ठा rdma_rw_reg_ctx अणु
			काष्ठा ib_sge		sge;
			काष्ठा ib_rdma_wr	wr;
			काष्ठा ib_reg_wr	reg_wr;
			काष्ठा ib_send_wr	inv_wr;
			काष्ठा ib_mr		*mr;
		पूर्ण *reg;
	पूर्ण;
पूर्ण;

पूर्णांक rdma_rw_ctx_init(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp, u32 port_num,
		काष्ठा scatterlist *sg, u32 sg_cnt, u32 sg_offset,
		u64 remote_addr, u32 rkey, क्रमागत dma_data_direction dir);
व्योम rdma_rw_ctx_destroy(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
			 u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
			 क्रमागत dma_data_direction dir);

पूर्णांक rdma_rw_ctx_signature_init(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
		काष्ठा scatterlist *prot_sg, u32 prot_sg_cnt,
		काष्ठा ib_sig_attrs *sig_attrs, u64 remote_addr, u32 rkey,
		क्रमागत dma_data_direction dir);
व्योम rdma_rw_ctx_destroy_signature(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा scatterlist *sg, u32 sg_cnt,
		काष्ठा scatterlist *prot_sg, u32 prot_sg_cnt,
		क्रमागत dma_data_direction dir);

काष्ठा ib_send_wr *rdma_rw_ctx_wrs(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp,
		u32 port_num, काष्ठा ib_cqe *cqe, काष्ठा ib_send_wr *chain_wr);
पूर्णांक rdma_rw_ctx_post(काष्ठा rdma_rw_ctx *ctx, काष्ठा ib_qp *qp, u32 port_num,
		काष्ठा ib_cqe *cqe, काष्ठा ib_send_wr *chain_wr);

अचिन्हित पूर्णांक rdma_rw_mr_factor(काष्ठा ib_device *device, u32 port_num,
		अचिन्हित पूर्णांक maxpages);
व्योम rdma_rw_init_qp(काष्ठा ib_device *dev, काष्ठा ib_qp_init_attr *attr);
पूर्णांक rdma_rw_init_mrs(काष्ठा ib_qp *qp, काष्ठा ib_qp_init_attr *attr);
व्योम rdma_rw_cleanup_mrs(काष्ठा ib_qp *qp);

#पूर्ण_अगर /* _RDMA_RW_H */
