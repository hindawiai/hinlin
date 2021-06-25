<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2013-2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_ib.h"
#समावेश "srq.h"
#समावेश "qp.h"

अटल पूर्णांक get_pas_size(काष्ठा mlx5_srq_attr *in)
अणु
	u32 log_page_size = in->log_page_size + 12;
	u32 log_srq_size  = in->log_size;
	u32 log_rq_stride = in->wqe_shअगरt;
	u32 page_offset   = in->page_offset;
	u32 po_quanta	  = 1 << (log_page_size - 6);
	u32 rq_sz	  = 1 << (log_srq_size + 4 + log_rq_stride);
	u32 page_size	  = 1 << log_page_size;
	u32 rq_sz_po      = rq_sz + (page_offset * po_quanta);
	u32 rq_num_pas    = DIV_ROUND_UP(rq_sz_po, page_size);

	वापस rq_num_pas * माप(u64);
पूर्ण

अटल व्योम set_wq(व्योम *wq, काष्ठा mlx5_srq_attr *in)
अणु
	MLX5_SET(wq,   wq, wq_signature,  !!(in->flags
		 & MLX5_SRQ_FLAG_WQ_SIG));
	MLX5_SET(wq,   wq, log_wq_pg_sz,  in->log_page_size);
	MLX5_SET(wq,   wq, log_wq_stride, in->wqe_shअगरt + 4);
	MLX5_SET(wq,   wq, log_wq_sz,     in->log_size);
	MLX5_SET(wq,   wq, page_offset,   in->page_offset);
	MLX5_SET(wq,   wq, lwm,		  in->lwm);
	MLX5_SET(wq,   wq, pd,		  in->pd);
	MLX5_SET64(wq, wq, dbr_addr,	  in->db_record);
पूर्ण

अटल व्योम set_srqc(व्योम *srqc, काष्ठा mlx5_srq_attr *in)
अणु
	MLX5_SET(srqc,   srqc, wq_signature,  !!(in->flags
		 & MLX5_SRQ_FLAG_WQ_SIG));
	MLX5_SET(srqc,   srqc, log_page_size, in->log_page_size);
	MLX5_SET(srqc,   srqc, log_rq_stride, in->wqe_shअगरt);
	MLX5_SET(srqc,   srqc, log_srq_size,  in->log_size);
	MLX5_SET(srqc,   srqc, page_offset,   in->page_offset);
	MLX5_SET(srqc,	 srqc, lwm,	      in->lwm);
	MLX5_SET(srqc,	 srqc, pd,	      in->pd);
	MLX5_SET64(srqc, srqc, dbr_addr,      in->db_record);
	MLX5_SET(srqc,	 srqc, xrcd,	      in->xrcd);
	MLX5_SET(srqc,	 srqc, cqn,	      in->cqn);
पूर्ण

अटल व्योम get_wq(व्योम *wq, काष्ठा mlx5_srq_attr *in)
अणु
	अगर (MLX5_GET(wq, wq, wq_signature))
		in->flags &= MLX5_SRQ_FLAG_WQ_SIG;
	in->log_page_size = MLX5_GET(wq,   wq, log_wq_pg_sz);
	in->wqe_shअगरt	  = MLX5_GET(wq,   wq, log_wq_stride) - 4;
	in->log_size	  = MLX5_GET(wq,   wq, log_wq_sz);
	in->page_offset   = MLX5_GET(wq,   wq, page_offset);
	in->lwm		  = MLX5_GET(wq,   wq, lwm);
	in->pd		  = MLX5_GET(wq,   wq, pd);
	in->db_record	  = MLX5_GET64(wq, wq, dbr_addr);
पूर्ण

अटल व्योम get_srqc(व्योम *srqc, काष्ठा mlx5_srq_attr *in)
अणु
	अगर (MLX5_GET(srqc, srqc, wq_signature))
		in->flags &= MLX5_SRQ_FLAG_WQ_SIG;
	in->log_page_size = MLX5_GET(srqc,   srqc, log_page_size);
	in->wqe_shअगरt	  = MLX5_GET(srqc,   srqc, log_rq_stride);
	in->log_size	  = MLX5_GET(srqc,   srqc, log_srq_size);
	in->page_offset   = MLX5_GET(srqc,   srqc, page_offset);
	in->lwm		  = MLX5_GET(srqc,   srqc, lwm);
	in->pd		  = MLX5_GET(srqc,   srqc, pd);
	in->db_record	  = MLX5_GET64(srqc, srqc, dbr_addr);
पूर्ण

काष्ठा mlx5_core_srq *mlx5_cmd_get_srq(काष्ठा mlx5_ib_dev *dev, u32 srqn)
अणु
	काष्ठा mlx5_srq_table *table = &dev->srq_table;
	काष्ठा mlx5_core_srq *srq;

	xa_lock_irq(&table->array);
	srq = xa_load(&table->array, srqn);
	अगर (srq)
		refcount_inc(&srq->common.refcount);
	xa_unlock_irq(&table->array);

	वापस srq;
पूर्ण

अटल पूर्णांक __set_srq_page_size(काष्ठा mlx5_srq_attr *in,
			       अचिन्हित दीर्घ page_size)
अणु
	अगर (!page_size)
		वापस -EINVAL;
	in->log_page_size = order_base_2(page_size) - MLX5_ADAPTER_PAGE_SHIFT;

	अगर (WARN_ON(get_pas_size(in) !=
		    ib_umem_num_dma_blocks(in->umem, page_size) * माप(u64)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

#घोषणा set_srq_page_size(in, typ, log_pgsz_fld)                               \
	__set_srq_page_size(in, mlx5_umem_find_best_quantized_pgoff(           \
					(in)->umem, typ, log_pgsz_fld,         \
					MLX5_ADAPTER_PAGE_SHIFT, page_offset,  \
					64, &(in)->page_offset))

अटल पूर्णांक create_srq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			  काष्ठा mlx5_srq_attr *in)
अणु
	u32 create_out[MLX5_ST_SZ_DW(create_srq_out)] = अणु0पूर्ण;
	व्योम *create_in;
	व्योम *srqc;
	व्योम *pas;
	पूर्णांक pas_size;
	पूर्णांक inlen;
	पूर्णांक err;

	अगर (in->umem) अणु
		err = set_srq_page_size(in, srqc, log_page_size);
		अगर (err)
			वापस err;
	पूर्ण

	pas_size  = get_pas_size(in);
	inlen	  = MLX5_ST_SZ_BYTES(create_srq_in) + pas_size;
	create_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!create_in)
		वापस -ENOMEM;

	MLX5_SET(create_srq_in, create_in, uid, in->uid);
	srqc = MLX5_ADDR_OF(create_srq_in, create_in, srq_context_entry);
	pas = MLX5_ADDR_OF(create_srq_in, create_in, pas);

	set_srqc(srqc, in);
	अगर (in->umem)
		mlx5_ib_populate_pas(
			in->umem,
			1UL << (in->log_page_size + MLX5_ADAPTER_PAGE_SHIFT),
			pas, 0);
	अन्यथा
		स_नकल(pas, in->pas, pas_size);

	MLX5_SET(create_srq_in, create_in, opcode,
		 MLX5_CMD_OP_CREATE_SRQ);

	err = mlx5_cmd_exec(dev->mdev, create_in, inlen, create_out,
			    माप(create_out));
	kvमुक्त(create_in);
	अगर (!err) अणु
		srq->srqn = MLX5_GET(create_srq_out, create_out, srqn);
		srq->uid = in->uid;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक destroy_srq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_srq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_srq_in, in, opcode, MLX5_CMD_OP_DESTROY_SRQ);
	MLX5_SET(destroy_srq_in, in, srqn, srq->srqn);
	MLX5_SET(destroy_srq_in, in, uid, srq->uid);

	वापस mlx5_cmd_exec_in(dev->mdev, destroy_srq, in);
पूर्ण

अटल पूर्णांक arm_srq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		       u16 lwm, पूर्णांक is_srq)
अणु
	u32 in[MLX5_ST_SZ_DW(arm_rq_in)] = अणुपूर्ण;

	MLX5_SET(arm_rq_in, in, opcode, MLX5_CMD_OP_ARM_RQ);
	MLX5_SET(arm_rq_in, in, op_mod, MLX5_ARM_RQ_IN_OP_MOD_SRQ);
	MLX5_SET(arm_rq_in, in, srq_number, srq->srqn);
	MLX5_SET(arm_rq_in, in, lwm, lwm);
	MLX5_SET(arm_rq_in, in, uid, srq->uid);

	वापस mlx5_cmd_exec_in(dev->mdev, arm_rq, in);
पूर्ण

अटल पूर्णांक query_srq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			 काष्ठा mlx5_srq_attr *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_srq_in)] = अणुपूर्ण;
	u32 *srq_out;
	व्योम *srqc;
	पूर्णांक err;

	srq_out = kvzalloc(MLX5_ST_SZ_BYTES(query_srq_out), GFP_KERNEL);
	अगर (!srq_out)
		वापस -ENOMEM;

	MLX5_SET(query_srq_in, in, opcode, MLX5_CMD_OP_QUERY_SRQ);
	MLX5_SET(query_srq_in, in, srqn, srq->srqn);
	err = mlx5_cmd_exec_inout(dev->mdev, query_srq, in, srq_out);
	अगर (err)
		जाओ out;

	srqc = MLX5_ADDR_OF(query_srq_out, srq_out, srq_context_entry);
	get_srqc(srqc, out);
	अगर (MLX5_GET(srqc, srqc, state) != MLX5_SRQC_STATE_GOOD)
		out->flags |= MLX5_SRQ_FLAG_ERR;
out:
	kvमुक्त(srq_out);
	वापस err;
पूर्ण

अटल पूर्णांक create_xrc_srq_cmd(काष्ठा mlx5_ib_dev *dev,
			      काष्ठा mlx5_core_srq *srq,
			      काष्ठा mlx5_srq_attr *in)
अणु
	u32 create_out[MLX5_ST_SZ_DW(create_xrc_srq_out)];
	व्योम *create_in;
	व्योम *xrc_srqc;
	व्योम *pas;
	पूर्णांक pas_size;
	पूर्णांक inlen;
	पूर्णांक err;

	अगर (in->umem) अणु
		err = set_srq_page_size(in, xrc_srqc, log_page_size);
		अगर (err)
			वापस err;
	पूर्ण

	pas_size  = get_pas_size(in);
	inlen	  = MLX5_ST_SZ_BYTES(create_xrc_srq_in) + pas_size;
	create_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!create_in)
		वापस -ENOMEM;

	MLX5_SET(create_xrc_srq_in, create_in, uid, in->uid);
	xrc_srqc = MLX5_ADDR_OF(create_xrc_srq_in, create_in,
				xrc_srq_context_entry);
	pas	 = MLX5_ADDR_OF(create_xrc_srq_in, create_in, pas);

	set_srqc(xrc_srqc, in);
	MLX5_SET(xrc_srqc, xrc_srqc, user_index, in->user_index);
	अगर (in->umem)
		mlx5_ib_populate_pas(
			in->umem,
			1UL << (in->log_page_size + MLX5_ADAPTER_PAGE_SHIFT),
			pas, 0);
	अन्यथा
		स_नकल(pas, in->pas, pas_size);
	MLX5_SET(create_xrc_srq_in, create_in, opcode,
		 MLX5_CMD_OP_CREATE_XRC_SRQ);

	स_रखो(create_out, 0, माप(create_out));
	err = mlx5_cmd_exec(dev->mdev, create_in, inlen, create_out,
			    माप(create_out));
	अगर (err)
		जाओ out;

	srq->srqn = MLX5_GET(create_xrc_srq_out, create_out, xrc_srqn);
	srq->uid = in->uid;
out:
	kvमुक्त(create_in);
	वापस err;
पूर्ण

अटल पूर्णांक destroy_xrc_srq_cmd(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा mlx5_core_srq *srq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_xrc_srq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_xrc_srq_in, in, opcode, MLX5_CMD_OP_DESTROY_XRC_SRQ);
	MLX5_SET(destroy_xrc_srq_in, in, xrc_srqn, srq->srqn);
	MLX5_SET(destroy_xrc_srq_in, in, uid, srq->uid);

	वापस mlx5_cmd_exec_in(dev->mdev, destroy_xrc_srq, in);
पूर्ण

अटल पूर्णांक arm_xrc_srq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			   u16 lwm)
अणु
	u32 in[MLX5_ST_SZ_DW(arm_xrc_srq_in)] = अणुपूर्ण;

	MLX5_SET(arm_xrc_srq_in, in, opcode, MLX5_CMD_OP_ARM_XRC_SRQ);
	MLX5_SET(arm_xrc_srq_in, in, op_mod,
		 MLX5_ARM_XRC_SRQ_IN_OP_MOD_XRC_SRQ);
	MLX5_SET(arm_xrc_srq_in, in, xrc_srqn, srq->srqn);
	MLX5_SET(arm_xrc_srq_in, in, lwm, lwm);
	MLX5_SET(arm_xrc_srq_in, in, uid, srq->uid);

	वापस  mlx5_cmd_exec_in(dev->mdev, arm_xrc_srq, in);
पूर्ण

अटल पूर्णांक query_xrc_srq_cmd(काष्ठा mlx5_ib_dev *dev,
			     काष्ठा mlx5_core_srq *srq,
			     काष्ठा mlx5_srq_attr *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_xrc_srq_in)] = अणुपूर्ण;
	u32 *xrcsrq_out;
	व्योम *xrc_srqc;
	पूर्णांक err;

	xrcsrq_out = kvzalloc(MLX5_ST_SZ_BYTES(query_xrc_srq_out), GFP_KERNEL);
	अगर (!xrcsrq_out)
		वापस -ENOMEM;

	MLX5_SET(query_xrc_srq_in, in, opcode, MLX5_CMD_OP_QUERY_XRC_SRQ);
	MLX5_SET(query_xrc_srq_in, in, xrc_srqn, srq->srqn);

	err = mlx5_cmd_exec_inout(dev->mdev, query_xrc_srq, in, xrcsrq_out);
	अगर (err)
		जाओ out;

	xrc_srqc = MLX5_ADDR_OF(query_xrc_srq_out, xrcsrq_out,
				xrc_srq_context_entry);
	get_srqc(xrc_srqc, out);
	अगर (MLX5_GET(xrc_srqc, xrc_srqc, state) != MLX5_XRC_SRQC_STATE_GOOD)
		out->flags |= MLX5_SRQ_FLAG_ERR;

out:
	kvमुक्त(xrcsrq_out);
	वापस err;
पूर्ण

अटल पूर्णांक create_rmp_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			  काष्ठा mlx5_srq_attr *in)
अणु
	व्योम *create_out = शून्य;
	व्योम *create_in = शून्य;
	व्योम *rmpc;
	व्योम *wq;
	व्योम *pas;
	पूर्णांक pas_size;
	पूर्णांक outlen;
	पूर्णांक inlen;
	पूर्णांक err;

	अगर (in->umem) अणु
		err = set_srq_page_size(in, wq, log_wq_pg_sz);
		अगर (err)
			वापस err;
	पूर्ण

	pas_size = get_pas_size(in);
	inlen = MLX5_ST_SZ_BYTES(create_rmp_in) + pas_size;
	outlen = MLX5_ST_SZ_BYTES(create_rmp_out);
	create_in = kvzalloc(inlen, GFP_KERNEL);
	create_out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!create_in || !create_out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rmpc = MLX5_ADDR_OF(create_rmp_in, create_in, ctx);
	wq = MLX5_ADDR_OF(rmpc, rmpc, wq);

	MLX5_SET(rmpc, rmpc, state, MLX5_RMPC_STATE_RDY);
	MLX5_SET(create_rmp_in, create_in, uid, in->uid);
	pas = MLX5_ADDR_OF(rmpc, rmpc, wq.pas);

	set_wq(wq, in);
	अगर (in->umem)
		mlx5_ib_populate_pas(
			in->umem,
			1UL << (in->log_page_size + MLX5_ADAPTER_PAGE_SHIFT),
			pas, 0);
	अन्यथा
		स_नकल(pas, in->pas, pas_size);

	MLX5_SET(create_rmp_in, create_in, opcode, MLX5_CMD_OP_CREATE_RMP);
	err = mlx5_cmd_exec(dev->mdev, create_in, inlen, create_out, outlen);
	अगर (!err) अणु
		srq->srqn = MLX5_GET(create_rmp_out, create_out, rmpn);
		srq->uid = in->uid;
	पूर्ण

out:
	kvमुक्त(create_in);
	kvमुक्त(create_out);
	वापस err;
पूर्ण

अटल पूर्णांक destroy_rmp_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rmp_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rmp_in, in, opcode, MLX5_CMD_OP_DESTROY_RMP);
	MLX5_SET(destroy_rmp_in, in, rmpn, srq->srqn);
	MLX5_SET(destroy_rmp_in, in, uid, srq->uid);
	वापस mlx5_cmd_exec_in(dev->mdev, destroy_rmp, in);
पूर्ण

अटल पूर्णांक arm_rmp_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		       u16 lwm)
अणु
	व्योम *out = शून्य;
	व्योम *in = शून्य;
	व्योम *rmpc;
	व्योम *wq;
	व्योम *biपंचांगask;
	पूर्णांक outlen;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_rmp_in);
	outlen = MLX5_ST_SZ_BYTES(modअगरy_rmp_out);

	in = kvzalloc(inlen, GFP_KERNEL);
	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!in || !out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	rmpc =	  MLX5_ADDR_OF(modअगरy_rmp_in,   in,   ctx);
	biपंचांगask = MLX5_ADDR_OF(modअगरy_rmp_in,   in,   biपंचांगask);
	wq   =	  MLX5_ADDR_OF(rmpc,	        rmpc, wq);

	MLX5_SET(modअगरy_rmp_in, in,	 rmp_state, MLX5_RMPC_STATE_RDY);
	MLX5_SET(modअगरy_rmp_in, in,	 rmpn,      srq->srqn);
	MLX5_SET(modअगरy_rmp_in, in, uid, srq->uid);
	MLX5_SET(wq,		wq,	 lwm,	    lwm);
	MLX5_SET(rmp_biपंचांगask,	biपंचांगask, lwm,	    1);
	MLX5_SET(rmpc, rmpc, state, MLX5_RMPC_STATE_RDY);
	MLX5_SET(modअगरy_rmp_in, in, opcode, MLX5_CMD_OP_MODIFY_RMP);

	err = mlx5_cmd_exec_inout(dev->mdev, modअगरy_rmp, in, out);

out:
	kvमुक्त(in);
	kvमुक्त(out);
	वापस err;
पूर्ण

अटल पूर्णांक query_rmp_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			 काष्ठा mlx5_srq_attr *out)
अणु
	u32 *rmp_out = शून्य;
	u32 *rmp_in = शून्य;
	व्योम *rmpc;
	पूर्णांक outlen;
	पूर्णांक inlen;
	पूर्णांक err;

	outlen = MLX5_ST_SZ_BYTES(query_rmp_out);
	inlen = MLX5_ST_SZ_BYTES(query_rmp_in);

	rmp_out = kvzalloc(outlen, GFP_KERNEL);
	rmp_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!rmp_out || !rmp_in) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	MLX5_SET(query_rmp_in, rmp_in, opcode, MLX5_CMD_OP_QUERY_RMP);
	MLX5_SET(query_rmp_in, rmp_in, rmpn,   srq->srqn);
	err = mlx5_cmd_exec_inout(dev->mdev, query_rmp, rmp_in, rmp_out);
	अगर (err)
		जाओ out;

	rmpc = MLX5_ADDR_OF(query_rmp_out, rmp_out, rmp_context);
	get_wq(MLX5_ADDR_OF(rmpc, rmpc, wq), out);
	अगर (MLX5_GET(rmpc, rmpc, state) != MLX5_RMPC_STATE_RDY)
		out->flags |= MLX5_SRQ_FLAG_ERR;

out:
	kvमुक्त(rmp_out);
	kvमुक्त(rmp_in);
	वापस err;
पूर्ण

अटल पूर्णांक create_xrq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			  काष्ठा mlx5_srq_attr *in)
अणु
	u32 create_out[MLX5_ST_SZ_DW(create_xrq_out)] = अणु0पूर्ण;
	व्योम *create_in;
	व्योम *xrqc;
	व्योम *wq;
	व्योम *pas;
	पूर्णांक pas_size;
	पूर्णांक inlen;
	पूर्णांक err;

	अगर (in->umem) अणु
		err = set_srq_page_size(in, wq, log_wq_pg_sz);
		अगर (err)
			वापस err;
	पूर्ण

	pas_size = get_pas_size(in);
	inlen = MLX5_ST_SZ_BYTES(create_xrq_in) + pas_size;
	create_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!create_in)
		वापस -ENOMEM;

	xrqc = MLX5_ADDR_OF(create_xrq_in, create_in, xrq_context);
	wq = MLX5_ADDR_OF(xrqc, xrqc, wq);
	pas = MLX5_ADDR_OF(xrqc, xrqc, wq.pas);

	set_wq(wq, in);
	अगर (in->umem)
		mlx5_ib_populate_pas(
			in->umem,
			1UL << (in->log_page_size + MLX5_ADAPTER_PAGE_SHIFT),
			pas, 0);
	अन्यथा
		स_नकल(pas, in->pas, pas_size);

	अगर (in->type == IB_SRQT_TM) अणु
		MLX5_SET(xrqc, xrqc, topology, MLX5_XRQC_TOPOLOGY_TAG_MATCHING);
		अगर (in->flags & MLX5_SRQ_FLAG_RNDV)
			MLX5_SET(xrqc, xrqc, offload, MLX5_XRQC_OFFLOAD_RNDV);
		MLX5_SET(xrqc, xrqc,
			 tag_matching_topology_context.log_matching_list_sz,
			 in->पंचांग_log_list_size);
	पूर्ण
	MLX5_SET(xrqc, xrqc, user_index, in->user_index);
	MLX5_SET(xrqc, xrqc, cqn, in->cqn);
	MLX5_SET(create_xrq_in, create_in, opcode, MLX5_CMD_OP_CREATE_XRQ);
	MLX5_SET(create_xrq_in, create_in, uid, in->uid);
	err = mlx5_cmd_exec(dev->mdev, create_in, inlen, create_out,
			    माप(create_out));
	kvमुक्त(create_in);
	अगर (!err) अणु
		srq->srqn = MLX5_GET(create_xrq_out, create_out, xrqn);
		srq->uid = in->uid;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक destroy_xrq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_xrq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_xrq_in, in, opcode, MLX5_CMD_OP_DESTROY_XRQ);
	MLX5_SET(destroy_xrq_in, in, xrqn, srq->srqn);
	MLX5_SET(destroy_xrq_in, in, uid, srq->uid);

	वापस mlx5_cmd_exec_in(dev->mdev, destroy_xrq, in);
पूर्ण

अटल पूर्णांक arm_xrq_cmd(काष्ठा mlx5_ib_dev *dev,
		       काष्ठा mlx5_core_srq *srq,
		       u16 lwm)
अणु
	u32 in[MLX5_ST_SZ_DW(arm_rq_in)] = अणुपूर्ण;

	MLX5_SET(arm_rq_in, in, opcode, MLX5_CMD_OP_ARM_RQ);
	MLX5_SET(arm_rq_in, in, op_mod, MLX5_ARM_RQ_IN_OP_MOD_XRQ);
	MLX5_SET(arm_rq_in, in, srq_number, srq->srqn);
	MLX5_SET(arm_rq_in, in, lwm, lwm);
	MLX5_SET(arm_rq_in, in, uid, srq->uid);

	वापस mlx5_cmd_exec_in(dev->mdev, arm_rq, in);
पूर्ण

अटल पूर्णांक query_xrq_cmd(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			 काष्ठा mlx5_srq_attr *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_xrq_in)] = अणुपूर्ण;
	u32 *xrq_out;
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_xrq_out);
	व्योम *xrqc;
	पूर्णांक err;

	xrq_out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!xrq_out)
		वापस -ENOMEM;

	MLX5_SET(query_xrq_in, in, opcode, MLX5_CMD_OP_QUERY_XRQ);
	MLX5_SET(query_xrq_in, in, xrqn, srq->srqn);

	err = mlx5_cmd_exec_inout(dev->mdev, query_xrq, in, xrq_out);
	अगर (err)
		जाओ out;

	xrqc = MLX5_ADDR_OF(query_xrq_out, xrq_out, xrq_context);
	get_wq(MLX5_ADDR_OF(xrqc, xrqc, wq), out);
	अगर (MLX5_GET(xrqc, xrqc, state) != MLX5_XRQC_STATE_GOOD)
		out->flags |= MLX5_SRQ_FLAG_ERR;
	out->पंचांग_next_tag =
		MLX5_GET(xrqc, xrqc,
			 tag_matching_topology_context.append_next_index);
	out->पंचांग_hw_phase_cnt =
		MLX5_GET(xrqc, xrqc,
			 tag_matching_topology_context.hw_phase_cnt);
	out->पंचांग_sw_phase_cnt =
		MLX5_GET(xrqc, xrqc,
			 tag_matching_topology_context.sw_phase_cnt);

out:
	kvमुक्त(xrq_out);
	वापस err;
पूर्ण

अटल पूर्णांक create_srq_split(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			    काष्ठा mlx5_srq_attr *in)
अणु
	अगर (!dev->mdev->issi)
		वापस create_srq_cmd(dev, srq, in);
	चयन (srq->common.res) अणु
	हाल MLX5_RES_XSRQ:
		वापस create_xrc_srq_cmd(dev, srq, in);
	हाल MLX5_RES_XRQ:
		वापस create_xrq_cmd(dev, srq, in);
	शेष:
		वापस create_rmp_cmd(dev, srq, in);
	पूर्ण
पूर्ण

अटल पूर्णांक destroy_srq_split(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq)
अणु
	अगर (!dev->mdev->issi)
		वापस destroy_srq_cmd(dev, srq);
	चयन (srq->common.res) अणु
	हाल MLX5_RES_XSRQ:
		वापस destroy_xrc_srq_cmd(dev, srq);
	हाल MLX5_RES_XRQ:
		वापस destroy_xrq_cmd(dev, srq);
	शेष:
		वापस destroy_rmp_cmd(dev, srq);
	पूर्ण
पूर्ण

पूर्णांक mlx5_cmd_create_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
			काष्ठा mlx5_srq_attr *in)
अणु
	काष्ठा mlx5_srq_table *table = &dev->srq_table;
	पूर्णांक err;

	चयन (in->type) अणु
	हाल IB_SRQT_XRC:
		srq->common.res = MLX5_RES_XSRQ;
		अवरोध;
	हाल IB_SRQT_TM:
		srq->common.res = MLX5_RES_XRQ;
		अवरोध;
	शेष:
		srq->common.res = MLX5_RES_SRQ;
	पूर्ण

	err = create_srq_split(dev, srq, in);
	अगर (err)
		वापस err;

	refcount_set(&srq->common.refcount, 1);
	init_completion(&srq->common.मुक्त);

	err = xa_err(xa_store_irq(&table->array, srq->srqn, srq, GFP_KERNEL));
	अगर (err)
		जाओ err_destroy_srq_split;

	वापस 0;

err_destroy_srq_split:
	destroy_srq_split(dev, srq);

	वापस err;
पूर्ण

पूर्णांक mlx5_cmd_destroy_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq)
अणु
	काष्ठा mlx5_srq_table *table = &dev->srq_table;
	काष्ठा mlx5_core_srq *पंचांगp;
	पूर्णांक err;

	/* Delete entry, but leave index occupied */
	पंचांगp = xa_cmpxchg_irq(&table->array, srq->srqn, srq, XA_ZERO_ENTRY, 0);
	अगर (WARN_ON(पंचांगp != srq))
		वापस xa_err(पंचांगp) ?: -EINVAL;

	err = destroy_srq_split(dev, srq);
	अगर (err) अणु
		/*
		 * We करोn't need to check वापसed result क्रम an error,
		 * because  we are storing in pre-allocated space xarray
		 * entry and it can't fail at this stage.
		 */
		xa_cmpxchg_irq(&table->array, srq->srqn, XA_ZERO_ENTRY, srq, 0);
		वापस err;
	पूर्ण
	xa_erase_irq(&table->array, srq->srqn);

	mlx5_core_res_put(&srq->common);
	रुको_क्रम_completion(&srq->common.मुक्त);
	वापस 0;
पूर्ण

पूर्णांक mlx5_cmd_query_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		       काष्ठा mlx5_srq_attr *out)
अणु
	अगर (!dev->mdev->issi)
		वापस query_srq_cmd(dev, srq, out);
	चयन (srq->common.res) अणु
	हाल MLX5_RES_XSRQ:
		वापस query_xrc_srq_cmd(dev, srq, out);
	हाल MLX5_RES_XRQ:
		वापस query_xrq_cmd(dev, srq, out);
	शेष:
		वापस query_rmp_cmd(dev, srq, out);
	पूर्ण
पूर्ण

पूर्णांक mlx5_cmd_arm_srq(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_srq *srq,
		     u16 lwm, पूर्णांक is_srq)
अणु
	अगर (!dev->mdev->issi)
		वापस arm_srq_cmd(dev, srq, lwm, is_srq);
	चयन (srq->common.res) अणु
	हाल MLX5_RES_XSRQ:
		वापस arm_xrc_srq_cmd(dev, srq, lwm);
	हाल MLX5_RES_XRQ:
		वापस arm_xrq_cmd(dev, srq, lwm);
	शेष:
		वापस arm_rmp_cmd(dev, srq, lwm);
	पूर्ण
पूर्ण

अटल पूर्णांक srq_event_notअगरier(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_srq_table *table;
	काष्ठा mlx5_core_srq *srq;
	काष्ठा mlx5_eqe *eqe;
	u32 srqn;

	अगर (type != MLX5_EVENT_TYPE_SRQ_CATAS_ERROR &&
	    type != MLX5_EVENT_TYPE_SRQ_RQ_LIMIT)
		वापस NOTIFY_DONE;

	table = container_of(nb, काष्ठा mlx5_srq_table, nb);

	eqe = data;
	srqn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;

	xa_lock(&table->array);
	srq = xa_load(&table->array, srqn);
	अगर (srq)
		refcount_inc(&srq->common.refcount);
	xa_unlock(&table->array);

	अगर (!srq)
		वापस NOTIFY_OK;

	srq->event(srq, eqe->type);

	mlx5_core_res_put(&srq->common);

	वापस NOTIFY_OK;
पूर्ण

पूर्णांक mlx5_init_srq_table(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_srq_table *table = &dev->srq_table;

	स_रखो(table, 0, माप(*table));
	xa_init_flags(&table->array, XA_FLAGS_LOCK_IRQ);

	table->nb.notअगरier_call = srq_event_notअगरier;
	mlx5_notअगरier_रेजिस्टर(dev->mdev, &table->nb);

	वापस 0;
पूर्ण

व्योम mlx5_cleanup_srq_table(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_srq_table *table = &dev->srq_table;

	mlx5_notअगरier_unरेजिस्टर(dev->mdev, &table->nb);
पूर्ण
