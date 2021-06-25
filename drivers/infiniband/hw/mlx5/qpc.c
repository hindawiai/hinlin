<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/mlx5/qp.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_ib.h"
#समावेश "qp.h"

अटल पूर्णांक mlx5_core_drain_dct(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा mlx5_core_dct *dct);

अटल काष्ठा mlx5_core_rsc_common *
mlx5_get_rsc(काष्ठा mlx5_qp_table *table, u32 rsn)
अणु
	काष्ठा mlx5_core_rsc_common *common;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&table->lock, flags);

	common = radix_tree_lookup(&table->tree, rsn);
	अगर (common)
		refcount_inc(&common->refcount);

	spin_unlock_irqrestore(&table->lock, flags);

	वापस common;
पूर्ण

व्योम mlx5_core_put_rsc(काष्ठा mlx5_core_rsc_common *common)
अणु
	अगर (refcount_dec_and_test(&common->refcount))
		complete(&common->मुक्त);
पूर्ण

अटल u64 qp_allowed_event_types(व्योम)
अणु
	u64 mask;

	mask = BIT(MLX5_EVENT_TYPE_PATH_MIG) |
	       BIT(MLX5_EVENT_TYPE_COMM_EST) |
	       BIT(MLX5_EVENT_TYPE_SQ_DRAINED) |
	       BIT(MLX5_EVENT_TYPE_SRQ_LAST_WQE) |
	       BIT(MLX5_EVENT_TYPE_WQ_CATAS_ERROR) |
	       BIT(MLX5_EVENT_TYPE_PATH_MIG_FAILED) |
	       BIT(MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR) |
	       BIT(MLX5_EVENT_TYPE_WQ_ACCESS_ERROR);

	वापस mask;
पूर्ण

अटल u64 rq_allowed_event_types(व्योम)
अणु
	u64 mask;

	mask = BIT(MLX5_EVENT_TYPE_SRQ_LAST_WQE) |
	       BIT(MLX5_EVENT_TYPE_WQ_CATAS_ERROR);

	वापस mask;
पूर्ण

अटल u64 sq_allowed_event_types(व्योम)
अणु
	वापस BIT(MLX5_EVENT_TYPE_WQ_CATAS_ERROR);
पूर्ण

अटल u64 dct_allowed_event_types(व्योम)
अणु
	वापस BIT(MLX5_EVENT_TYPE_DCT_DRAINED);
पूर्ण

अटल bool is_event_type_allowed(पूर्णांक rsc_type, पूर्णांक event_type)
अणु
	चयन (rsc_type) अणु
	हाल MLX5_EVENT_QUEUE_TYPE_QP:
		वापस BIT(event_type) & qp_allowed_event_types();
	हाल MLX5_EVENT_QUEUE_TYPE_RQ:
		वापस BIT(event_type) & rq_allowed_event_types();
	हाल MLX5_EVENT_QUEUE_TYPE_SQ:
		वापस BIT(event_type) & sq_allowed_event_types();
	हाल MLX5_EVENT_QUEUE_TYPE_DCT:
		वापस BIT(event_type) & dct_allowed_event_types();
	शेष:
		WARN(1, "Event arrived for unknown resource type");
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक rsc_event_notअगरier(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_core_rsc_common *common;
	काष्ठा mlx5_qp_table *table;
	काष्ठा mlx5_core_dct *dct;
	u8 event_type = (u8)type;
	काष्ठा mlx5_core_qp *qp;
	काष्ठा mlx5_eqe *eqe;
	u32 rsn;

	चयन (event_type) अणु
	हाल MLX5_EVENT_TYPE_DCT_DRAINED:
		eqe = data;
		rsn = be32_to_cpu(eqe->data.dct.dctn) & 0xffffff;
		rsn |= (MLX5_RES_DCT << MLX5_USER_INDEX_LEN);
		अवरोध;
	हाल MLX5_EVENT_TYPE_PATH_MIG:
	हाल MLX5_EVENT_TYPE_COMM_EST:
	हाल MLX5_EVENT_TYPE_SQ_DRAINED:
	हाल MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	हाल MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	हाल MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	हाल MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	हाल MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
		eqe = data;
		rsn = be32_to_cpu(eqe->data.qp_srq.qp_srq_n) & 0xffffff;
		rsn |= (eqe->data.qp_srq.type << MLX5_USER_INDEX_LEN);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	table = container_of(nb, काष्ठा mlx5_qp_table, nb);
	common = mlx5_get_rsc(table, rsn);
	अगर (!common)
		वापस NOTIFY_OK;

	अगर (!is_event_type_allowed((rsn >> MLX5_USER_INDEX_LEN), event_type))
		जाओ out;

	चयन (common->res) अणु
	हाल MLX5_RES_QP:
	हाल MLX5_RES_RQ:
	हाल MLX5_RES_SQ:
		qp = (काष्ठा mlx5_core_qp *)common;
		qp->event(qp, event_type);
		अवरोध;
	हाल MLX5_RES_DCT:
		dct = (काष्ठा mlx5_core_dct *)common;
		अगर (event_type == MLX5_EVENT_TYPE_DCT_DRAINED)
			complete(&dct->drained);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	mlx5_core_put_rsc(common);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक create_resource_common(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_core_qp *qp, पूर्णांक rsc_type)
अणु
	काष्ठा mlx5_qp_table *table = &dev->qp_table;
	पूर्णांक err;

	qp->common.res = rsc_type;
	spin_lock_irq(&table->lock);
	err = radix_tree_insert(&table->tree,
				qp->qpn | (rsc_type << MLX5_USER_INDEX_LEN),
				qp);
	spin_unlock_irq(&table->lock);
	अगर (err)
		वापस err;

	refcount_set(&qp->common.refcount, 1);
	init_completion(&qp->common.मुक्त);
	qp->pid = current->pid;

	वापस 0;
पूर्ण

अटल व्योम destroy_resource_common(काष्ठा mlx5_ib_dev *dev,
				    काष्ठा mlx5_core_qp *qp)
अणु
	काष्ठा mlx5_qp_table *table = &dev->qp_table;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&table->lock, flags);
	radix_tree_delete(&table->tree,
			  qp->qpn | (qp->common.res << MLX5_USER_INDEX_LEN));
	spin_unlock_irqrestore(&table->lock, flags);
	mlx5_core_put_rsc((काष्ठा mlx5_core_rsc_common *)qp);
	रुको_क्रम_completion(&qp->common.मुक्त);
पूर्ण

अटल पूर्णांक _mlx5_core_destroy_dct(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_core_dct *dct, bool need_cleanup)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_dct_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_qp *qp = &dct->mqp;
	पूर्णांक err;

	err = mlx5_core_drain_dct(dev, dct);
	अगर (err) अणु
		अगर (dev->mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
			जाओ destroy;

		वापस err;
	पूर्ण
	रुको_क्रम_completion(&dct->drained);
destroy:
	अगर (need_cleanup)
		destroy_resource_common(dev, &dct->mqp);
	MLX5_SET(destroy_dct_in, in, opcode, MLX5_CMD_OP_DESTROY_DCT);
	MLX5_SET(destroy_dct_in, in, dctn, qp->qpn);
	MLX5_SET(destroy_dct_in, in, uid, qp->uid);
	err = mlx5_cmd_exec_in(dev->mdev, destroy_dct, in);
	वापस err;
पूर्ण

पूर्णांक mlx5_core_create_dct(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_dct *dct,
			 u32 *in, पूर्णांक inlen, u32 *out, पूर्णांक outlen)
अणु
	काष्ठा mlx5_core_qp *qp = &dct->mqp;
	पूर्णांक err;

	init_completion(&dct->drained);
	MLX5_SET(create_dct_in, in, opcode, MLX5_CMD_OP_CREATE_DCT);

	err = mlx5_cmd_exec(dev->mdev, in, inlen, out, outlen);
	अगर (err)
		वापस err;

	qp->qpn = MLX5_GET(create_dct_out, out, dctn);
	qp->uid = MLX5_GET(create_dct_in, in, uid);
	err = create_resource_common(dev, qp, MLX5_RES_DCT);
	अगर (err)
		जाओ err_cmd;

	वापस 0;
err_cmd:
	_mlx5_core_destroy_dct(dev, dct, false);
	वापस err;
पूर्ण

पूर्णांक mlx5_qpc_create_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp,
		       u32 *in, पूर्णांक inlen, u32 *out)
अणु
	u32 din[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_qp_in, in, opcode, MLX5_CMD_OP_CREATE_QP);

	err = mlx5_cmd_exec(dev->mdev, in, inlen, out,
			    MLX5_ST_SZ_BYTES(create_qp_out));
	अगर (err)
		वापस err;

	qp->uid = MLX5_GET(create_qp_in, in, uid);
	qp->qpn = MLX5_GET(create_qp_out, out, qpn);

	err = create_resource_common(dev, qp, MLX5_RES_QP);
	अगर (err)
		जाओ err_cmd;

	mlx5_debug_qp_add(dev->mdev, qp);

	वापस 0;

err_cmd:
	MLX5_SET(destroy_qp_in, din, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, din, qpn, qp->qpn);
	MLX5_SET(destroy_qp_in, din, uid, qp->uid);
	mlx5_cmd_exec_in(dev->mdev, destroy_qp, din);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_core_drain_dct(काष्ठा mlx5_ib_dev *dev,
			       काष्ठा mlx5_core_dct *dct)
अणु
	u32 in[MLX5_ST_SZ_DW(drain_dct_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_qp *qp = &dct->mqp;

	MLX5_SET(drain_dct_in, in, opcode, MLX5_CMD_OP_DRAIN_DCT);
	MLX5_SET(drain_dct_in, in, dctn, qp->qpn);
	MLX5_SET(drain_dct_in, in, uid, qp->uid);
	वापस mlx5_cmd_exec_in(dev->mdev, drain_dct, in);
पूर्ण

पूर्णांक mlx5_core_destroy_dct(काष्ठा mlx5_ib_dev *dev,
			  काष्ठा mlx5_core_dct *dct)
अणु
	वापस _mlx5_core_destroy_dct(dev, dct, true);
पूर्ण

पूर्णांक mlx5_core_destroy_qp(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_qp_in)] = अणुपूर्ण;

	mlx5_debug_qp_हटाओ(dev->mdev, qp);

	destroy_resource_common(dev, qp);

	MLX5_SET(destroy_qp_in, in, opcode, MLX5_CMD_OP_DESTROY_QP);
	MLX5_SET(destroy_qp_in, in, qpn, qp->qpn);
	MLX5_SET(destroy_qp_in, in, uid, qp->uid);
	mlx5_cmd_exec_in(dev->mdev, destroy_qp, in);
	वापस 0;
पूर्ण

पूर्णांक mlx5_core_set_delay_drop(काष्ठा mlx5_ib_dev *dev,
			     u32 समयout_usec)
अणु
	u32 in[MLX5_ST_SZ_DW(set_delay_drop_params_in)] = अणुपूर्ण;

	MLX5_SET(set_delay_drop_params_in, in, opcode,
		 MLX5_CMD_OP_SET_DELAY_DROP_PARAMS);
	MLX5_SET(set_delay_drop_params_in, in, delay_drop_समयout,
		 समयout_usec / 100);
	वापस mlx5_cmd_exec_in(dev->mdev, set_delay_drop_params, in);
पूर्ण

काष्ठा mbox_info अणु
	u32 *in;
	u32 *out;
	पूर्णांक inlen;
	पूर्णांक outlen;
पूर्ण;

अटल पूर्णांक mbox_alloc(काष्ठा mbox_info *mbox, पूर्णांक inlen, पूर्णांक outlen)
अणु
	mbox->inlen  = inlen;
	mbox->outlen = outlen;
	mbox->in = kzalloc(mbox->inlen, GFP_KERNEL);
	mbox->out = kzalloc(mbox->outlen, GFP_KERNEL);
	अगर (!mbox->in || !mbox->out) अणु
		kमुक्त(mbox->in);
		kमुक्त(mbox->out);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mbox_मुक्त(काष्ठा mbox_info *mbox)
अणु
	kमुक्त(mbox->in);
	kमुक्त(mbox->out);
पूर्ण

अटल पूर्णांक get_ece_from_mbox(व्योम *out, u16 opcode)
अणु
	पूर्णांक ece = 0;

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_INIT2INIT_QP:
		ece = MLX5_GET(init2init_qp_out, out, ece);
		अवरोध;
	हाल MLX5_CMD_OP_INIT2RTR_QP:
		ece = MLX5_GET(init2rtr_qp_out, out, ece);
		अवरोध;
	हाल MLX5_CMD_OP_RTR2RTS_QP:
		ece = MLX5_GET(rtr2rts_qp_out, out, ece);
		अवरोध;
	हाल MLX5_CMD_OP_RTS2RTS_QP:
		ece = MLX5_GET(rts2rts_qp_out, out, ece);
		अवरोध;
	हाल MLX5_CMD_OP_RST2INIT_QP:
		ece = MLX5_GET(rst2init_qp_out, out, ece);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ece;
पूर्ण

अटल पूर्णांक modअगरy_qp_mbox_alloc(काष्ठा mlx5_core_dev *dev, u16 opcode, पूर्णांक qpn,
				u32 opt_param_mask, व्योम *qpc,
				काष्ठा mbox_info *mbox, u16 uid, u32 ece)
अणु
	mbox->out = शून्य;
	mbox->in = शून्य;

#घोषणा MBOX_ALLOC(mbox, typ)  \
	mbox_alloc(mbox, MLX5_ST_SZ_BYTES(typ##_in), MLX5_ST_SZ_BYTES(typ##_out))

#घोषणा MOD_QP_IN_SET(typ, in, _opcode, _qpn, _uid)                            \
	करो अणु                                                                   \
		MLX5_SET(typ##_in, in, opcode, _opcode);                       \
		MLX5_SET(typ##_in, in, qpn, _qpn);                             \
		MLX5_SET(typ##_in, in, uid, _uid);                             \
	पूर्ण जबतक (0)

#घोषणा MOD_QP_IN_SET_QPC(typ, in, _opcode, _qpn, _opt_p, _qpc, _uid)          \
	करो अणु                                                                   \
		MOD_QP_IN_SET(typ, in, _opcode, _qpn, _uid);                   \
		MLX5_SET(typ##_in, in, opt_param_mask, _opt_p);                \
		स_नकल(MLX5_ADDR_OF(typ##_in, in, qpc), _qpc,                  \
		       MLX5_ST_SZ_BYTES(qpc));                                 \
	पूर्ण जबतक (0)

	चयन (opcode) अणु
	/* 2RST & 2ERR */
	हाल MLX5_CMD_OP_2RST_QP:
		अगर (MBOX_ALLOC(mbox, qp_2rst))
			वापस -ENOMEM;
		MOD_QP_IN_SET(qp_2rst, mbox->in, opcode, qpn, uid);
		अवरोध;
	हाल MLX5_CMD_OP_2ERR_QP:
		अगर (MBOX_ALLOC(mbox, qp_2err))
			वापस -ENOMEM;
		MOD_QP_IN_SET(qp_2err, mbox->in, opcode, qpn, uid);
		अवरोध;

	/* MODIFY with QPC */
	हाल MLX5_CMD_OP_RST2INIT_QP:
		अगर (MBOX_ALLOC(mbox, rst2init_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(rst2init_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		MLX5_SET(rst2init_qp_in, mbox->in, ece, ece);
		अवरोध;
	हाल MLX5_CMD_OP_INIT2RTR_QP:
		अगर (MBOX_ALLOC(mbox, init2rtr_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(init2rtr_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		MLX5_SET(init2rtr_qp_in, mbox->in, ece, ece);
		अवरोध;
	हाल MLX5_CMD_OP_RTR2RTS_QP:
		अगर (MBOX_ALLOC(mbox, rtr2rts_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(rtr2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		MLX5_SET(rtr2rts_qp_in, mbox->in, ece, ece);
		अवरोध;
	हाल MLX5_CMD_OP_RTS2RTS_QP:
		अगर (MBOX_ALLOC(mbox, rts2rts_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(rts2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		MLX5_SET(rts2rts_qp_in, mbox->in, ece, ece);
		अवरोध;
	हाल MLX5_CMD_OP_SQERR2RTS_QP:
		अगर (MBOX_ALLOC(mbox, sqerr2rts_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(sqerr2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		अवरोध;
	हाल MLX5_CMD_OP_INIT2INIT_QP:
		अगर (MBOX_ALLOC(mbox, init2init_qp))
			वापस -ENOMEM;
		MOD_QP_IN_SET_QPC(init2init_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc, uid);
		MLX5_SET(init2init_qp_in, mbox->in, ece, ece);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlx5_core_qp_modअगरy(काष्ठा mlx5_ib_dev *dev, u16 opcode, u32 opt_param_mask,
			व्योम *qpc, काष्ठा mlx5_core_qp *qp, u32 *ece)
अणु
	काष्ठा mbox_info mbox;
	पूर्णांक err;

	err = modअगरy_qp_mbox_alloc(dev->mdev, opcode, qp->qpn, opt_param_mask,
				   qpc, &mbox, qp->uid, (ece) ? *ece : 0);
	अगर (err)
		वापस err;

	err = mlx5_cmd_exec(dev->mdev, mbox.in, mbox.inlen, mbox.out,
			    mbox.outlen);

	अगर (ece)
		*ece = get_ece_from_mbox(mbox.out, opcode);

	mbox_मुक्त(&mbox);
	वापस err;
पूर्ण

पूर्णांक mlx5_init_qp_table(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_qp_table *table = &dev->qp_table;

	spin_lock_init(&table->lock);
	INIT_RADIX_TREE(&table->tree, GFP_ATOMIC);
	mlx5_qp_debugfs_init(dev->mdev);

	table->nb.notअगरier_call = rsc_event_notअगरier;
	mlx5_notअगरier_रेजिस्टर(dev->mdev, &table->nb);

	वापस 0;
पूर्ण

व्योम mlx5_cleanup_qp_table(काष्ठा mlx5_ib_dev *dev)
अणु
	काष्ठा mlx5_qp_table *table = &dev->qp_table;

	mlx5_notअगरier_unरेजिस्टर(dev->mdev, &table->nb);
	mlx5_qp_debugfs_cleanup(dev->mdev);
पूर्ण

पूर्णांक mlx5_core_qp_query(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_qp *qp,
		       u32 *out, पूर्णांक outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(query_qp_in)] = अणुपूर्ण;

	MLX5_SET(query_qp_in, in, opcode, MLX5_CMD_OP_QUERY_QP);
	MLX5_SET(query_qp_in, in, qpn, qp->qpn);
	वापस mlx5_cmd_exec(dev->mdev, in, माप(in), out, outlen);
पूर्ण

पूर्णांक mlx5_core_dct_query(काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_core_dct *dct,
			u32 *out, पूर्णांक outlen)
अणु
	u32 in[MLX5_ST_SZ_DW(query_dct_in)] = अणुपूर्ण;
	काष्ठा mlx5_core_qp *qp = &dct->mqp;

	MLX5_SET(query_dct_in, in, opcode, MLX5_CMD_OP_QUERY_DCT);
	MLX5_SET(query_dct_in, in, dctn, qp->qpn);

	वापस mlx5_cmd_exec(dev->mdev, (व्योम *)&in, माप(in), (व्योम *)out,
			     outlen);
पूर्ण

पूर्णांक mlx5_core_xrcd_alloc(काष्ठा mlx5_ib_dev *dev, u32 *xrcdn)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_xrcd_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_xrcd_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_xrcd_in, in, opcode, MLX5_CMD_OP_ALLOC_XRCD);
	err = mlx5_cmd_exec_inout(dev->mdev, alloc_xrcd, in, out);
	अगर (!err)
		*xrcdn = MLX5_GET(alloc_xrcd_out, out, xrcd);
	वापस err;
पूर्ण

पूर्णांक mlx5_core_xrcd_dealloc(काष्ठा mlx5_ib_dev *dev, u32 xrcdn)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_xrcd_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_xrcd_in, in, opcode, MLX5_CMD_OP_DEALLOC_XRCD);
	MLX5_SET(dealloc_xrcd_in, in, xrcd, xrcdn);
	वापस mlx5_cmd_exec_in(dev->mdev, dealloc_xrcd, in);
पूर्ण

अटल व्योम destroy_rq_tracked(काष्ठा mlx5_ib_dev *dev, u32 rqn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rq_in, in, opcode, MLX5_CMD_OP_DESTROY_RQ);
	MLX5_SET(destroy_rq_in, in, rqn, rqn);
	MLX5_SET(destroy_rq_in, in, uid, uid);
	mlx5_cmd_exec_in(dev->mdev, destroy_rq, in);
पूर्ण

पूर्णांक mlx5_core_create_rq_tracked(काष्ठा mlx5_ib_dev *dev, u32 *in, पूर्णांक inlen,
				काष्ठा mlx5_core_qp *rq)
अणु
	पूर्णांक err;
	u32 rqn;

	err = mlx5_core_create_rq(dev->mdev, in, inlen, &rqn);
	अगर (err)
		वापस err;

	rq->uid = MLX5_GET(create_rq_in, in, uid);
	rq->qpn = rqn;
	err = create_resource_common(dev, rq, MLX5_RES_RQ);
	अगर (err)
		जाओ err_destroy_rq;

	वापस 0;

err_destroy_rq:
	destroy_rq_tracked(dev, rq->qpn, rq->uid);

	वापस err;
पूर्ण

पूर्णांक mlx5_core_destroy_rq_tracked(काष्ठा mlx5_ib_dev *dev,
				 काष्ठा mlx5_core_qp *rq)
अणु
	destroy_resource_common(dev, rq);
	destroy_rq_tracked(dev, rq->qpn, rq->uid);
	वापस 0;
पूर्ण

अटल व्योम destroy_sq_tracked(काष्ठा mlx5_ib_dev *dev, u32 sqn, u16 uid)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_sq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_sq_in, in, opcode, MLX5_CMD_OP_DESTROY_SQ);
	MLX5_SET(destroy_sq_in, in, sqn, sqn);
	MLX5_SET(destroy_sq_in, in, uid, uid);
	mlx5_cmd_exec_in(dev->mdev, destroy_sq, in);
पूर्ण

पूर्णांक mlx5_core_create_sq_tracked(काष्ठा mlx5_ib_dev *dev, u32 *in, पूर्णांक inlen,
				काष्ठा mlx5_core_qp *sq)
अणु
	u32 out[MLX5_ST_SZ_DW(create_sq_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_sq_in, in, opcode, MLX5_CMD_OP_CREATE_SQ);
	err = mlx5_cmd_exec(dev->mdev, in, inlen, out, माप(out));
	अगर (err)
		वापस err;

	sq->qpn = MLX5_GET(create_sq_out, out, sqn);
	sq->uid = MLX5_GET(create_sq_in, in, uid);
	err = create_resource_common(dev, sq, MLX5_RES_SQ);
	अगर (err)
		जाओ err_destroy_sq;

	वापस 0;

err_destroy_sq:
	destroy_sq_tracked(dev, sq->qpn, sq->uid);

	वापस err;
पूर्ण

व्योम mlx5_core_destroy_sq_tracked(काष्ठा mlx5_ib_dev *dev,
				  काष्ठा mlx5_core_qp *sq)
अणु
	destroy_resource_common(dev, sq);
	destroy_sq_tracked(dev, sq->qpn, sq->uid);
पूर्ण

काष्ठा mlx5_core_rsc_common *mlx5_core_res_hold(काष्ठा mlx5_ib_dev *dev,
						पूर्णांक res_num,
						क्रमागत mlx5_res_type res_type)
अणु
	u32 rsn = res_num | (res_type << MLX5_USER_INDEX_LEN);
	काष्ठा mlx5_qp_table *table = &dev->qp_table;

	वापस mlx5_get_rsc(table, rsn);
पूर्ण

व्योम mlx5_core_res_put(काष्ठा mlx5_core_rsc_common *res)
अणु
	mlx5_core_put_rsc(res);
पूर्ण
