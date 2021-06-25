<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies, Ltd.  All rights reserved.
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

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"
#समावेश <linux/mlx5/transobj.h>

पूर्णांक mlx5_core_alloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 *tdn)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_transport_करोमुख्य_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_transport_करोमुख्य_in, in, opcode,
		 MLX5_CMD_OP_ALLOC_TRANSPORT_DOMAIN);

	err = mlx5_cmd_exec_inout(dev, alloc_transport_करोमुख्य, in, out);
	अगर (!err)
		*tdn = MLX5_GET(alloc_transport_करोमुख्य_out, out,
				transport_करोमुख्य);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_alloc_transport_करोमुख्य);

व्योम mlx5_core_dealloc_transport_करोमुख्य(काष्ठा mlx5_core_dev *dev, u32 tdn)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_transport_करोमुख्य_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_transport_करोमुख्य_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_TRANSPORT_DOMAIN);
	MLX5_SET(dealloc_transport_करोमुख्य_in, in, transport_करोमुख्य, tdn);
	mlx5_cmd_exec_in(dev, dealloc_transport_करोमुख्य, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_dealloc_transport_करोमुख्य);

पूर्णांक mlx5_core_create_rq(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen, u32 *rqn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_rq_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_rq_in, in, opcode, MLX5_CMD_OP_CREATE_RQ);
	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
	अगर (!err)
		*rqn = MLX5_GET(create_rq_out, out, rqn);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_rq);

पूर्णांक mlx5_core_modअगरy_rq(काष्ठा mlx5_core_dev *dev, u32 rqn, u32 *in)
अणु
	MLX5_SET(modअगरy_rq_in, in, rqn, rqn);
	MLX5_SET(modअगरy_rq_in, in, opcode, MLX5_CMD_OP_MODIFY_RQ);

	वापस mlx5_cmd_exec_in(dev, modअगरy_rq, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_modअगरy_rq);

व्योम mlx5_core_destroy_rq(काष्ठा mlx5_core_dev *dev, u32 rqn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rq_in, in, opcode, MLX5_CMD_OP_DESTROY_RQ);
	MLX5_SET(destroy_rq_in, in, rqn, rqn);
	mlx5_cmd_exec_in(dev, destroy_rq, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_rq);

पूर्णांक mlx5_core_query_rq(काष्ठा mlx5_core_dev *dev, u32 rqn, u32 *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_rq_in)] = अणुपूर्ण;

	MLX5_SET(query_rq_in, in, opcode, MLX5_CMD_OP_QUERY_RQ);
	MLX5_SET(query_rq_in, in, rqn, rqn);

	वापस mlx5_cmd_exec_inout(dev, query_rq, in, out);
पूर्ण
EXPORT_SYMBOL(mlx5_core_query_rq);

पूर्णांक mlx5_core_create_sq(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen, u32 *sqn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_sq_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_sq_in, in, opcode, MLX5_CMD_OP_CREATE_SQ);
	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
	अगर (!err)
		*sqn = MLX5_GET(create_sq_out, out, sqn);

	वापस err;
पूर्ण

पूर्णांक mlx5_core_modअगरy_sq(काष्ठा mlx5_core_dev *dev, u32 sqn, u32 *in)
अणु
	MLX5_SET(modअगरy_sq_in, in, sqn, sqn);
	MLX5_SET(modअगरy_sq_in, in, opcode, MLX5_CMD_OP_MODIFY_SQ);
	वापस mlx5_cmd_exec_in(dev, modअगरy_sq, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_modअगरy_sq);

व्योम mlx5_core_destroy_sq(काष्ठा mlx5_core_dev *dev, u32 sqn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_sq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_sq_in, in, opcode, MLX5_CMD_OP_DESTROY_SQ);
	MLX5_SET(destroy_sq_in, in, sqn, sqn);
	mlx5_cmd_exec_in(dev, destroy_sq, in);
पूर्ण

पूर्णांक mlx5_core_query_sq(काष्ठा mlx5_core_dev *dev, u32 sqn, u32 *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_sq_in)] = अणुपूर्ण;

	MLX5_SET(query_sq_in, in, opcode, MLX5_CMD_OP_QUERY_SQ);
	MLX5_SET(query_sq_in, in, sqn, sqn);
	वापस mlx5_cmd_exec_inout(dev, query_sq, in, out);
पूर्ण
EXPORT_SYMBOL(mlx5_core_query_sq);

पूर्णांक mlx5_core_query_sq_state(काष्ठा mlx5_core_dev *dev, u32 sqn, u8 *state)
अणु
	व्योम *out;
	व्योम *sqc;
	पूर्णांक inlen;
	पूर्णांक err;

	inlen = MLX5_ST_SZ_BYTES(query_sq_out);
	out = kvzalloc(inlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	err = mlx5_core_query_sq(dev, sqn, out);
	अगर (err)
		जाओ out;

	sqc = MLX5_ADDR_OF(query_sq_out, out, sq_context);
	*state = MLX5_GET(sqc, sqc, state);

out:
	kvमुक्त(out);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_core_query_sq_state);

पूर्णांक mlx5_core_create_tir(काष्ठा mlx5_core_dev *dev, u32 *in, u32 *tirn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_tir_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_tir_in, in, opcode, MLX5_CMD_OP_CREATE_TIR);
	err = mlx5_cmd_exec_inout(dev, create_tir, in, out);
	अगर (!err)
		*tirn = MLX5_GET(create_tir_out, out, tirn);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_tir);

पूर्णांक mlx5_core_modअगरy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn, u32 *in)
अणु
	MLX5_SET(modअगरy_tir_in, in, tirn, tirn);
	MLX5_SET(modअगरy_tir_in, in, opcode, MLX5_CMD_OP_MODIFY_TIR);
	वापस mlx5_cmd_exec_in(dev, modअगरy_tir, in);
पूर्ण

व्योम mlx5_core_destroy_tir(काष्ठा mlx5_core_dev *dev, u32 tirn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tir_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tir_in, in, opcode, MLX5_CMD_OP_DESTROY_TIR);
	MLX5_SET(destroy_tir_in, in, tirn, tirn);
	mlx5_cmd_exec_in(dev, destroy_tir, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_tir);

पूर्णांक mlx5_core_create_tis(काष्ठा mlx5_core_dev *dev, u32 *in, u32 *tisn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_tis_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_tis_in, in, opcode, MLX5_CMD_OP_CREATE_TIS);
	err = mlx5_cmd_exec_inout(dev, create_tis, in, out);
	अगर (!err)
		*tisn = MLX5_GET(create_tis_out, out, tisn);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_tis);

पूर्णांक mlx5_core_modअगरy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn, u32 *in)
अणु
	MLX5_SET(modअगरy_tis_in, in, tisn, tisn);
	MLX5_SET(modअगरy_tis_in, in, opcode, MLX5_CMD_OP_MODIFY_TIS);

	वापस mlx5_cmd_exec_in(dev, modअगरy_tis, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_modअगरy_tis);

व्योम mlx5_core_destroy_tis(काष्ठा mlx5_core_dev *dev, u32 tisn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_tis_in)] = अणुपूर्ण;

	MLX5_SET(destroy_tis_in, in, opcode, MLX5_CMD_OP_DESTROY_TIS);
	MLX5_SET(destroy_tis_in, in, tisn, tisn);
	mlx5_cmd_exec_in(dev, destroy_tis, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_tis);

पूर्णांक mlx5_core_create_rqt(काष्ठा mlx5_core_dev *dev, u32 *in, पूर्णांक inlen,
			 u32 *rqtn)
अणु
	u32 out[MLX5_ST_SZ_DW(create_rqt_out)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(create_rqt_in, in, opcode, MLX5_CMD_OP_CREATE_RQT);
	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
	अगर (!err)
		*rqtn = MLX5_GET(create_rqt_out, out, rqtn);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_rqt);

पूर्णांक mlx5_core_modअगरy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn, u32 *in,
			 पूर्णांक inlen)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_rqt_out)] = अणुपूर्ण;

	MLX5_SET(modअगरy_rqt_in, in, rqtn, rqtn);
	MLX5_SET(modअगरy_rqt_in, in, opcode, MLX5_CMD_OP_MODIFY_RQT);
	वापस mlx5_cmd_exec(dev, in, inlen, out, माप(out));
पूर्ण

व्योम mlx5_core_destroy_rqt(काष्ठा mlx5_core_dev *dev, u32 rqtn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_rqt_in)] = अणुपूर्ण;

	MLX5_SET(destroy_rqt_in, in, opcode, MLX5_CMD_OP_DESTROY_RQT);
	MLX5_SET(destroy_rqt_in, in, rqtn, rqtn);
	mlx5_cmd_exec_in(dev, destroy_rqt, in);
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_rqt);

अटल पूर्णांक mlx5_hairpin_create_rq(काष्ठा mlx5_core_dev *mdev,
				  काष्ठा mlx5_hairpin_params *params, u32 *rqn)
अणु
	u32 in[MLX5_ST_SZ_DW(create_rq_in)] = अणु0पूर्ण;
	व्योम *rqc, *wq;

	rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
	wq  = MLX5_ADDR_OF(rqc, rqc, wq);

	MLX5_SET(rqc, rqc, hairpin, 1);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RST);
	MLX5_SET(rqc, rqc, counter_set_id, params->q_counter);

	MLX5_SET(wq, wq, log_hairpin_data_sz, params->log_data_size);
	MLX5_SET(wq, wq, log_hairpin_num_packets, params->log_num_packets);

	वापस mlx5_core_create_rq(mdev, in, MLX5_ST_SZ_BYTES(create_rq_in), rqn);
पूर्ण

अटल पूर्णांक mlx5_hairpin_create_sq(काष्ठा mlx5_core_dev *mdev,
				  काष्ठा mlx5_hairpin_params *params, u32 *sqn)
अणु
	u32 in[MLX5_ST_SZ_DW(create_sq_in)] = अणु0पूर्ण;
	व्योम *sqc, *wq;

	sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
	wq  = MLX5_ADDR_OF(sqc, sqc, wq);

	MLX5_SET(sqc, sqc, hairpin, 1);
	MLX5_SET(sqc, sqc, state, MLX5_SQC_STATE_RST);

	MLX5_SET(wq, wq, log_hairpin_data_sz, params->log_data_size);
	MLX5_SET(wq, wq, log_hairpin_num_packets, params->log_num_packets);

	वापस mlx5_core_create_sq(mdev, in, MLX5_ST_SZ_BYTES(create_sq_in), sqn);
पूर्ण

अटल पूर्णांक mlx5_hairpin_create_queues(काष्ठा mlx5_hairpin *hp,
				      काष्ठा mlx5_hairpin_params *params)
अणु
	पूर्णांक i, j, err;

	क्रम (i = 0; i < hp->num_channels; i++) अणु
		err = mlx5_hairpin_create_rq(hp->func_mdev, params, &hp->rqn[i]);
		अगर (err)
			जाओ out_err_rq;
	पूर्ण

	क्रम (i = 0; i < hp->num_channels; i++) अणु
		err = mlx5_hairpin_create_sq(hp->peer_mdev, params, &hp->sqn[i]);
		अगर (err)
			जाओ out_err_sq;
	पूर्ण

	वापस 0;

out_err_sq:
	क्रम (j = 0; j < i; j++)
		mlx5_core_destroy_sq(hp->peer_mdev, hp->sqn[j]);
	i = hp->num_channels;
out_err_rq:
	क्रम (j = 0; j < i; j++)
		mlx5_core_destroy_rq(hp->func_mdev, hp->rqn[j]);
	वापस err;
पूर्ण

अटल व्योम mlx5_hairpin_destroy_queues(काष्ठा mlx5_hairpin *hp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hp->num_channels; i++) अणु
		mlx5_core_destroy_rq(hp->func_mdev, hp->rqn[i]);
		अगर (!hp->peer_gone)
			mlx5_core_destroy_sq(hp->peer_mdev, hp->sqn[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_hairpin_modअगरy_rq(काष्ठा mlx5_core_dev *func_mdev, u32 rqn,
				  पूर्णांक curr_state, पूर्णांक next_state,
				  u16 peer_vhca, u32 peer_sq)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_rq_in)] = अणुपूर्ण;
	व्योम *rqc;

	rqc = MLX5_ADDR_OF(modअगरy_rq_in, in, ctx);

	अगर (next_state == MLX5_RQC_STATE_RDY) अणु
		MLX5_SET(rqc, rqc, hairpin_peer_sq, peer_sq);
		MLX5_SET(rqc, rqc, hairpin_peer_vhca, peer_vhca);
	पूर्ण

	MLX5_SET(modअगरy_rq_in, in, rq_state, curr_state);
	MLX5_SET(rqc, rqc, state, next_state);

	वापस mlx5_core_modअगरy_rq(func_mdev, rqn, in);
पूर्ण

अटल पूर्णांक mlx5_hairpin_modअगरy_sq(काष्ठा mlx5_core_dev *peer_mdev, u32 sqn,
				  पूर्णांक curr_state, पूर्णांक next_state,
				  u16 peer_vhca, u32 peer_rq)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_sq_in)] = अणु0पूर्ण;
	व्योम *sqc;

	sqc = MLX5_ADDR_OF(modअगरy_sq_in, in, ctx);

	अगर (next_state == MLX5_SQC_STATE_RDY) अणु
		MLX5_SET(sqc, sqc, hairpin_peer_rq, peer_rq);
		MLX5_SET(sqc, sqc, hairpin_peer_vhca, peer_vhca);
	पूर्ण

	MLX5_SET(modअगरy_sq_in, in, sq_state, curr_state);
	MLX5_SET(sqc, sqc, state, next_state);

	वापस mlx5_core_modअगरy_sq(peer_mdev, sqn, in);
पूर्ण

अटल पूर्णांक mlx5_hairpin_pair_queues(काष्ठा mlx5_hairpin *hp)
अणु
	पूर्णांक i, j, err;

	/* set peer SQs */
	क्रम (i = 0; i < hp->num_channels; i++) अणु
		err = mlx5_hairpin_modअगरy_sq(hp->peer_mdev, hp->sqn[i],
					     MLX5_SQC_STATE_RST, MLX5_SQC_STATE_RDY,
					     MLX5_CAP_GEN(hp->func_mdev, vhca_id), hp->rqn[i]);
		अगर (err)
			जाओ err_modअगरy_sq;
	पूर्ण

	/* set func RQs */
	क्रम (i = 0; i < hp->num_channels; i++) अणु
		err = mlx5_hairpin_modअगरy_rq(hp->func_mdev, hp->rqn[i],
					     MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY,
					     MLX5_CAP_GEN(hp->peer_mdev, vhca_id), hp->sqn[i]);
		अगर (err)
			जाओ err_modअगरy_rq;
	पूर्ण

	वापस 0;

err_modअगरy_rq:
	क्रम (j = 0; j < i; j++)
		mlx5_hairpin_modअगरy_rq(hp->func_mdev, hp->rqn[j], MLX5_RQC_STATE_RDY,
				       MLX5_RQC_STATE_RST, 0, 0);
	i = hp->num_channels;
err_modअगरy_sq:
	क्रम (j = 0; j < i; j++)
		mlx5_hairpin_modअगरy_sq(hp->peer_mdev, hp->sqn[j], MLX5_SQC_STATE_RDY,
				       MLX5_SQC_STATE_RST, 0, 0);
	वापस err;
पूर्ण

अटल व्योम mlx5_hairpin_unpair_peer_sq(काष्ठा mlx5_hairpin *hp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hp->num_channels; i++)
		mlx5_hairpin_modअगरy_sq(hp->peer_mdev, hp->sqn[i], MLX5_SQC_STATE_RDY,
				       MLX5_SQC_STATE_RST, 0, 0);
पूर्ण

अटल व्योम mlx5_hairpin_unpair_queues(काष्ठा mlx5_hairpin *hp)
अणु
	पूर्णांक i;

	/* unset func RQs */
	क्रम (i = 0; i < hp->num_channels; i++)
		mlx5_hairpin_modअगरy_rq(hp->func_mdev, hp->rqn[i], MLX5_RQC_STATE_RDY,
				       MLX5_RQC_STATE_RST, 0, 0);
	/* unset peer SQs */
	अगर (!hp->peer_gone)
		mlx5_hairpin_unpair_peer_sq(hp);
पूर्ण

काष्ठा mlx5_hairpin *
mlx5_core_hairpin_create(काष्ठा mlx5_core_dev *func_mdev,
			 काष्ठा mlx5_core_dev *peer_mdev,
			 काष्ठा mlx5_hairpin_params *params)
अणु
	काष्ठा mlx5_hairpin *hp;
	पूर्णांक size, err;

	size = माप(*hp) + params->num_channels * 2 * माप(u32);
	hp = kzalloc(size, GFP_KERNEL);
	अगर (!hp)
		वापस ERR_PTR(-ENOMEM);

	hp->func_mdev = func_mdev;
	hp->peer_mdev = peer_mdev;
	hp->num_channels = params->num_channels;

	hp->rqn = (व्योम *)hp + माप(*hp);
	hp->sqn = hp->rqn + params->num_channels;

	/* alloc and pair func --> peer hairpin */
	err = mlx5_hairpin_create_queues(hp, params);
	अगर (err)
		जाओ err_create_queues;

	err = mlx5_hairpin_pair_queues(hp);
	अगर (err)
		जाओ err_pair_queues;

	वापस hp;

err_pair_queues:
	mlx5_hairpin_destroy_queues(hp);
err_create_queues:
	kमुक्त(hp);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlx5_core_hairpin_destroy(काष्ठा mlx5_hairpin *hp)
अणु
	mlx5_hairpin_unpair_queues(hp);
	mlx5_hairpin_destroy_queues(hp);
	kमुक्त(hp);
पूर्ण

व्योम mlx5_core_hairpin_clear_dead_peer(काष्ठा mlx5_hairpin *hp)
अणु
	पूर्णांक i;

	mlx5_hairpin_unpair_peer_sq(hp);

	/* destroy peer SQ */
	क्रम (i = 0; i < hp->num_channels; i++)
		mlx5_core_destroy_sq(hp->peer_mdev, hp->sqn[i]);

	hp->peer_gone = true;
पूर्ण
