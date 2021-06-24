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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <linux/mlx5/cq.h>
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"

#घोषणा TASKLET_MAX_TIME 2
#घोषणा TASKLET_MAX_TIME_JIFFIES msecs_to_jअगरfies(TASKLET_MAX_TIME)

व्योम mlx5_cq_tasklet_cb(काष्ठा tasklet_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ end = jअगरfies + TASKLET_MAX_TIME_JIFFIES;
	काष्ठा mlx5_eq_tasklet *ctx = from_tasklet(ctx, t, task);
	काष्ठा mlx5_core_cq *mcq;
	काष्ठा mlx5_core_cq *temp;

	spin_lock_irqsave(&ctx->lock, flags);
	list_splice_tail_init(&ctx->list, &ctx->process_list);
	spin_unlock_irqrestore(&ctx->lock, flags);

	list_क्रम_each_entry_safe(mcq, temp, &ctx->process_list,
				 tasklet_ctx.list) अणु
		list_del_init(&mcq->tasklet_ctx.list);
		mcq->tasklet_ctx.comp(mcq, शून्य);
		mlx5_cq_put(mcq);
		अगर (समय_after(jअगरfies, end))
			अवरोध;
	पूर्ण

	अगर (!list_empty(&ctx->process_list))
		tasklet_schedule(&ctx->task);
पूर्ण

अटल व्योम mlx5_add_cq_to_tasklet(काष्ठा mlx5_core_cq *cq,
				   काष्ठा mlx5_eqe *eqe)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mlx5_eq_tasklet *tasklet_ctx = cq->tasklet_ctx.priv;

	spin_lock_irqsave(&tasklet_ctx->lock, flags);
	/* When migrating CQs between EQs will be implemented, please note
	 * that you need to sync this poपूर्णांक. It is possible that
	 * जबतक migrating a CQ, completions on the old EQs could
	 * still arrive.
	 */
	अगर (list_empty_careful(&cq->tasklet_ctx.list)) अणु
		mlx5_cq_hold(cq);
		list_add_tail(&cq->tasklet_ctx.list, &tasklet_ctx->list);
	पूर्ण
	spin_unlock_irqrestore(&tasklet_ctx->lock, flags);
पूर्ण

पूर्णांक mlx5_core_create_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
			u32 *in, पूर्णांक inlen, u32 *out, पूर्णांक outlen)
अणु
	पूर्णांक eqn = MLX5_GET(cqc, MLX5_ADDR_OF(create_cq_in, in, cq_context), c_eqn);
	u32 din[MLX5_ST_SZ_DW(destroy_cq_in)] = अणुपूर्ण;
	काष्ठा mlx5_eq_comp *eq;
	पूर्णांक err;

	eq = mlx5_eqn2comp_eq(dev, eqn);
	अगर (IS_ERR(eq))
		वापस PTR_ERR(eq);

	स_रखो(out, 0, outlen);
	MLX5_SET(create_cq_in, in, opcode, MLX5_CMD_OP_CREATE_CQ);
	err = mlx5_cmd_exec(dev, in, inlen, out, outlen);
	अगर (err)
		वापस err;

	cq->cqn = MLX5_GET(create_cq_out, out, cqn);
	cq->cons_index = 0;
	cq->arm_sn     = 0;
	cq->eq         = eq;
	cq->uid = MLX5_GET(create_cq_in, in, uid);
	refcount_set(&cq->refcount, 1);
	init_completion(&cq->मुक्त);
	अगर (!cq->comp)
		cq->comp = mlx5_add_cq_to_tasklet;
	/* assuming CQ will be deleted beक्रमe the EQ */
	cq->tasklet_ctx.priv = &eq->tasklet_ctx;
	INIT_LIST_HEAD(&cq->tasklet_ctx.list);

	/* Add to comp EQ CQ tree to recv comp events */
	err = mlx5_eq_add_cq(&eq->core, cq);
	अगर (err)
		जाओ err_cmd;

	/* Add to async EQ CQ tree to recv async events */
	err = mlx5_eq_add_cq(mlx5_get_async_eq(dev), cq);
	अगर (err)
		जाओ err_cq_add;

	cq->pid = current->pid;
	err = mlx5_debug_cq_add(dev, cq);
	अगर (err)
		mlx5_core_dbg(dev, "failed adding CP 0x%x to debug file system\n",
			      cq->cqn);

	cq->uar = dev->priv.uar;

	वापस 0;

err_cq_add:
	mlx5_eq_del_cq(&eq->core, cq);
err_cmd:
	MLX5_SET(destroy_cq_in, din, opcode, MLX5_CMD_OP_DESTROY_CQ);
	MLX5_SET(destroy_cq_in, din, cqn, cq->cqn);
	MLX5_SET(destroy_cq_in, din, uid, cq->uid);
	mlx5_cmd_exec_in(dev, destroy_cq, din);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_core_create_cq);

पूर्णांक mlx5_core_destroy_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_cq_in)] = अणुपूर्ण;
	पूर्णांक err;

	mlx5_eq_del_cq(mlx5_get_async_eq(dev), cq);
	mlx5_eq_del_cq(&cq->eq->core, cq);

	MLX5_SET(destroy_cq_in, in, opcode, MLX5_CMD_OP_DESTROY_CQ);
	MLX5_SET(destroy_cq_in, in, cqn, cq->cqn);
	MLX5_SET(destroy_cq_in, in, uid, cq->uid);
	err = mlx5_cmd_exec_in(dev, destroy_cq, in);
	अगर (err)
		वापस err;

	synchronize_irq(cq->irqn);

	mlx5_debug_cq_हटाओ(dev, cq);
	mlx5_cq_put(cq);
	रुको_क्रम_completion(&cq->मुक्त);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlx5_core_destroy_cq);

पूर्णांक mlx5_core_query_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
		       u32 *out)
अणु
	u32 in[MLX5_ST_SZ_DW(query_cq_in)] = अणुपूर्ण;

	MLX5_SET(query_cq_in, in, opcode, MLX5_CMD_OP_QUERY_CQ);
	MLX5_SET(query_cq_in, in, cqn, cq->cqn);
	वापस mlx5_cmd_exec_inout(dev, query_cq, in, out);
पूर्ण
EXPORT_SYMBOL(mlx5_core_query_cq);

पूर्णांक mlx5_core_modअगरy_cq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_core_cq *cq,
			u32 *in, पूर्णांक inlen)
अणु
	u32 out[MLX5_ST_SZ_DW(modअगरy_cq_out)] = अणुपूर्ण;

	MLX5_SET(modअगरy_cq_in, in, opcode, MLX5_CMD_OP_MODIFY_CQ);
	MLX5_SET(modअगरy_cq_in, in, uid, cq->uid);
	वापस mlx5_cmd_exec(dev, in, inlen, out, माप(out));
पूर्ण
EXPORT_SYMBOL(mlx5_core_modअगरy_cq);

पूर्णांक mlx5_core_modअगरy_cq_moderation(काष्ठा mlx5_core_dev *dev,
				   काष्ठा mlx5_core_cq *cq,
				   u16 cq_period,
				   u16 cq_max_count)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_cq_in)] = अणुपूर्ण;
	व्योम *cqc;

	MLX5_SET(modअगरy_cq_in, in, cqn, cq->cqn);
	cqc = MLX5_ADDR_OF(modअगरy_cq_in, in, cq_context);
	MLX5_SET(cqc, cqc, cq_period, cq_period);
	MLX5_SET(cqc, cqc, cq_max_count, cq_max_count);
	MLX5_SET(modअगरy_cq_in, in,
		 modअगरy_field_select_resize_field_select.modअगरy_field_select.modअगरy_field_select,
		 MLX5_CQ_MODIFY_PERIOD | MLX5_CQ_MODIFY_COUNT);

	वापस mlx5_core_modअगरy_cq(dev, cq, in, माप(in));
पूर्ण
EXPORT_SYMBOL(mlx5_core_modअगरy_cq_moderation);
