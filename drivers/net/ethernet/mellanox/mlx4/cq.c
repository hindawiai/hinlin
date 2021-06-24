<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2004 Voltaire, Inc. All rights reserved.
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

#समावेश <linux/hardirq.h>
#समावेश <linux/export.h>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/cq.h>

#समावेश "mlx4.h"
#समावेश "icm.h"

#घोषणा MLX4_CQ_STATUS_OK		( 0 << 28)
#घोषणा MLX4_CQ_STATUS_OVERFLOW		( 9 << 28)
#घोषणा MLX4_CQ_STATUS_WRITE_FAIL	(10 << 28)
#घोषणा MLX4_CQ_FLAG_CC			( 1 << 18)
#घोषणा MLX4_CQ_FLAG_OI			( 1 << 17)
#घोषणा MLX4_CQ_STATE_ARMED		( 9 <<  8)
#घोषणा MLX4_CQ_STATE_ARMED_SOL		( 6 <<  8)
#घोषणा MLX4_EQ_STATE_FIRED		(10 <<  8)

#घोषणा TASKLET_MAX_TIME 2
#घोषणा TASKLET_MAX_TIME_JIFFIES msecs_to_jअगरfies(TASKLET_MAX_TIME)

व्योम mlx4_cq_tasklet_cb(काष्ठा tasklet_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ end = jअगरfies + TASKLET_MAX_TIME_JIFFIES;
	काष्ठा mlx4_eq_tasklet *ctx = from_tasklet(ctx, t, task);
	काष्ठा mlx4_cq *mcq, *temp;

	spin_lock_irqsave(&ctx->lock, flags);
	list_splice_tail_init(&ctx->list, &ctx->process_list);
	spin_unlock_irqrestore(&ctx->lock, flags);

	list_क्रम_each_entry_safe(mcq, temp, &ctx->process_list, tasklet_ctx.list) अणु
		list_del_init(&mcq->tasklet_ctx.list);
		mcq->tasklet_ctx.comp(mcq);
		अगर (refcount_dec_and_test(&mcq->refcount))
			complete(&mcq->मुक्त);
		अगर (समय_after(jअगरfies, end))
			अवरोध;
	पूर्ण

	अगर (!list_empty(&ctx->process_list))
		tasklet_schedule(&ctx->task);
पूर्ण

अटल व्योम mlx4_add_cq_to_tasklet(काष्ठा mlx4_cq *cq)
अणु
	काष्ठा mlx4_eq_tasklet *tasklet_ctx = cq->tasklet_ctx.priv;
	अचिन्हित दीर्घ flags;
	bool kick;

	spin_lock_irqsave(&tasklet_ctx->lock, flags);
	/* When migrating CQs between EQs will be implemented, please note
	 * that you need to sync this poपूर्णांक. It is possible that
	 * जबतक migrating a CQ, completions on the old EQs could
	 * still arrive.
	 */
	अगर (list_empty_careful(&cq->tasklet_ctx.list)) अणु
		refcount_inc(&cq->refcount);
		kick = list_empty(&tasklet_ctx->list);
		list_add_tail(&cq->tasklet_ctx.list, &tasklet_ctx->list);
		अगर (kick)
			tasklet_schedule(&tasklet_ctx->task);
	पूर्ण
	spin_unlock_irqrestore(&tasklet_ctx->lock, flags);
पूर्ण

व्योम mlx4_cq_completion(काष्ठा mlx4_dev *dev, u32 cqn)
अणु
	काष्ठा mlx4_cq *cq;

	rcu_पढ़ो_lock();
	cq = radix_tree_lookup(&mlx4_priv(dev)->cq_table.tree,
			       cqn & (dev->caps.num_cqs - 1));
	rcu_पढ़ो_unlock();

	अगर (!cq) अणु
		mlx4_dbg(dev, "Completion event for bogus CQ %08x\n", cqn);
		वापस;
	पूर्ण

	/* Acessing the CQ outside of rcu_पढ़ो_lock is safe, because
	 * the CQ is मुक्तd only after पूर्णांकerrupt handling is completed.
	 */
	++cq->arm_sn;

	cq->comp(cq);
पूर्ण

व्योम mlx4_cq_event(काष्ठा mlx4_dev *dev, u32 cqn, पूर्णांक event_type)
अणु
	काष्ठा mlx4_cq_table *cq_table = &mlx4_priv(dev)->cq_table;
	काष्ठा mlx4_cq *cq;

	rcu_पढ़ो_lock();
	cq = radix_tree_lookup(&cq_table->tree, cqn & (dev->caps.num_cqs - 1));
	rcu_पढ़ो_unlock();

	अगर (!cq) अणु
		mlx4_dbg(dev, "Async event for bogus CQ %08x\n", cqn);
		वापस;
	पूर्ण

	/* Acessing the CQ outside of rcu_पढ़ो_lock is safe, because
	 * the CQ is मुक्तd only after पूर्णांकerrupt handling is completed.
	 */
	cq->event(cq, event_type);
पूर्ण

अटल पूर्णांक mlx4_SW2HW_CQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			 पूर्णांक cq_num, u8 opmod)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, cq_num, opmod,
			MLX4_CMD_SW2HW_CQ, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_MODIFY_CQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			 पूर्णांक cq_num, u32 opmod)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, cq_num, opmod, MLX4_CMD_MODIFY_CQ,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_HW2SW_CQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			 पूर्णांक cq_num)
अणु
	वापस mlx4_cmd_box(dev, 0, mailbox ? mailbox->dma : 0,
			    cq_num, mailbox ? 0 : 1, MLX4_CMD_HW2SW_CQ,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

पूर्णांक mlx4_cq_modअगरy(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq,
		   u16 count, u16 period)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_cq_context *cq_context;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	cq_context->cq_max_count = cpu_to_be16(count);
	cq_context->cq_period    = cpu_to_be16(period);

	err = mlx4_MODIFY_CQ(dev, mailbox, cq->cqn, 1);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_cq_modअगरy);

पूर्णांक mlx4_cq_resize(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq,
		   पूर्णांक entries, काष्ठा mlx4_mtt *mtt)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_cq_context *cq_context;
	u64 mtt_addr;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	cq_context->logsize_usrpage = cpu_to_be32(ilog2(entries) << 24);
	cq_context->log_page_size   = mtt->page_shअगरt - 12;
	mtt_addr = mlx4_mtt_addr(dev, mtt);
	cq_context->mtt_base_addr_h = mtt_addr >> 32;
	cq_context->mtt_base_addr_l = cpu_to_be32(mtt_addr & 0xffffffff);

	err = mlx4_MODIFY_CQ(dev, mailbox, cq->cqn, 0);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_cq_resize);

पूर्णांक __mlx4_cq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *cqn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cq_table *cq_table = &priv->cq_table;
	पूर्णांक err;

	*cqn = mlx4_biपंचांगap_alloc(&cq_table->biपंचांगap);
	अगर (*cqn == -1)
		वापस -ENOMEM;

	err = mlx4_table_get(dev, &cq_table->table, *cqn);
	अगर (err)
		जाओ err_out;

	err = mlx4_table_get(dev, &cq_table->cmpt_table, *cqn);
	अगर (err)
		जाओ err_put;
	वापस 0;

err_put:
	mlx4_table_put(dev, &cq_table->table, *cqn);

err_out:
	mlx4_biपंचांगap_मुक्त(&cq_table->biपंचांगap, *cqn, MLX4_NO_RR);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_cq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *cqn, u8 usage)
अणु
	u32 in_modअगरier = RES_CQ | (((u32)usage & 3) << 30);
	u64 out_param;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		err = mlx4_cmd_imm(dev, 0, &out_param, in_modअगरier,
				   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err)
			वापस err;
		अन्यथा अणु
			*cqn = get_param_l(&out_param);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस __mlx4_cq_alloc_icm(dev, cqn);
पूर्ण

व्योम __mlx4_cq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक cqn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cq_table *cq_table = &priv->cq_table;

	mlx4_table_put(dev, &cq_table->cmpt_table, cqn);
	mlx4_table_put(dev, &cq_table->table, cqn);
	mlx4_biपंचांगap_मुक्त(&cq_table->biपंचांगap, cqn, MLX4_NO_RR);
पूर्ण

अटल व्योम mlx4_cq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक cqn)
अणु
	u64 in_param = 0;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, cqn);
		err = mlx4_cmd(dev, in_param, RES_CQ, RES_OP_RESERVE_AND_MAP,
			       MLX4_CMD_FREE_RES,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err)
			mlx4_warn(dev, "Failed freeing cq:%d\n", cqn);
	पूर्ण अन्यथा
		__mlx4_cq_मुक्त_icm(dev, cqn);
पूर्ण

अटल पूर्णांक mlx4_init_user_cqes(व्योम *buf, पूर्णांक entries, पूर्णांक cqe_size)
अणु
	पूर्णांक entries_per_copy = PAGE_SIZE / cqe_size;
	व्योम *init_ents;
	पूर्णांक err = 0;
	पूर्णांक i;

	init_ents = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!init_ents)
		वापस -ENOMEM;

	/* Populate a list of CQ entries to reduce the number of
	 * copy_to_user calls. 0xcc is the initialization value
	 * required by the FW.
	 */
	स_रखो(init_ents, 0xcc, PAGE_SIZE);

	अगर (entries_per_copy < entries) अणु
		क्रम (i = 0; i < entries / entries_per_copy; i++) अणु
			err = copy_to_user((व्योम __user *)buf, init_ents, PAGE_SIZE) ?
				-EFAULT : 0;
			अगर (err)
				जाओ out;

			buf += PAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = copy_to_user((व्योम __user *)buf, init_ents, entries * cqe_size) ?
			-EFAULT : 0;
	पूर्ण

out:
	kमुक्त(init_ents);

	वापस err;
पूर्ण

अटल व्योम mlx4_init_kernel_cqes(काष्ठा mlx4_buf *buf,
				  पूर्णांक entries,
				  पूर्णांक cqe_size)
अणु
	पूर्णांक i;

	अगर (buf->nbufs == 1)
		स_रखो(buf->direct.buf, 0xcc, entries * cqe_size);
	अन्यथा
		क्रम (i = 0; i < buf->npages; i++)
			स_रखो(buf->page_list[i].buf, 0xcc,
			       1UL << buf->page_shअगरt);
पूर्ण

पूर्णांक mlx4_cq_alloc(काष्ठा mlx4_dev *dev, पूर्णांक nent,
		  काष्ठा mlx4_mtt *mtt, काष्ठा mlx4_uar *uar, u64 db_rec,
		  काष्ठा mlx4_cq *cq, अचिन्हित vector, पूर्णांक collapsed,
		  पूर्णांक बारtamp_en, व्योम *buf_addr, bool user_cq)
अणु
	bool sw_cq_init = dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SW_CQ_INIT;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cq_table *cq_table = &priv->cq_table;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_cq_context *cq_context;
	u64 mtt_addr;
	पूर्णांक err;

	अगर (vector >= dev->caps.num_comp_vectors)
		वापस -EINVAL;

	cq->vector = vector;

	err = mlx4_cq_alloc_icm(dev, &cq->cqn, cq->usage);
	अगर (err)
		वापस err;

	spin_lock(&cq_table->lock);
	err = radix_tree_insert(&cq_table->tree, cq->cqn, cq);
	spin_unlock(&cq_table->lock);
	अगर (err)
		जाओ err_icm;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_radix;
	पूर्ण

	cq_context = mailbox->buf;
	cq_context->flags	    = cpu_to_be32(!!collapsed << 18);
	अगर (बारtamp_en)
		cq_context->flags  |= cpu_to_be32(1 << 19);

	cq_context->logsize_usrpage =
		cpu_to_be32((ilog2(nent) << 24) |
			    mlx4_to_hw_uar_index(dev, uar->index));
	cq_context->comp_eqn	    = priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(vector)].eqn;
	cq_context->log_page_size   = mtt->page_shअगरt - MLX4_ICM_PAGE_SHIFT;

	mtt_addr = mlx4_mtt_addr(dev, mtt);
	cq_context->mtt_base_addr_h = mtt_addr >> 32;
	cq_context->mtt_base_addr_l = cpu_to_be32(mtt_addr & 0xffffffff);
	cq_context->db_rec_addr     = cpu_to_be64(db_rec);

	अगर (sw_cq_init) अणु
		अगर (user_cq) अणु
			err = mlx4_init_user_cqes(buf_addr, nent,
						  dev->caps.cqe_size);
			अगर (err)
				sw_cq_init = false;
		पूर्ण अन्यथा अणु
			mlx4_init_kernel_cqes(buf_addr, nent,
					      dev->caps.cqe_size);
		पूर्ण
	पूर्ण

	err = mlx4_SW2HW_CQ(dev, mailbox, cq->cqn, sw_cq_init);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (err)
		जाओ err_radix;

	cq->cons_index = 0;
	cq->arm_sn     = 1;
	cq->uar        = uar;
	refcount_set(&cq->refcount, 1);
	init_completion(&cq->मुक्त);
	cq->comp = mlx4_add_cq_to_tasklet;
	cq->tasklet_ctx.priv =
		&priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(vector)].tasklet_ctx;
	INIT_LIST_HEAD(&cq->tasklet_ctx.list);


	cq->irq = priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(vector)].irq;
	वापस 0;

err_radix:
	spin_lock(&cq_table->lock);
	radix_tree_delete(&cq_table->tree, cq->cqn);
	spin_unlock(&cq_table->lock);

err_icm:
	mlx4_cq_मुक्त_icm(dev, cq->cqn);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_cq_alloc);

व्योम mlx4_cq_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cq *cq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cq_table *cq_table = &priv->cq_table;
	पूर्णांक err;

	err = mlx4_HW2SW_CQ(dev, शून्य, cq->cqn);
	अगर (err)
		mlx4_warn(dev, "HW2SW_CQ failed (%d) for CQN %06x\n", err, cq->cqn);

	spin_lock(&cq_table->lock);
	radix_tree_delete(&cq_table->tree, cq->cqn);
	spin_unlock(&cq_table->lock);

	synchronize_irq(priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq->vector)].irq);
	अगर (priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq->vector)].irq !=
	    priv->eq_table.eq[MLX4_EQ_ASYNC].irq)
		synchronize_irq(priv->eq_table.eq[MLX4_EQ_ASYNC].irq);

	अगर (refcount_dec_and_test(&cq->refcount))
		complete(&cq->मुक्त);
	रुको_क्रम_completion(&cq->मुक्त);

	mlx4_cq_मुक्त_icm(dev, cq->cqn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_cq_मुक्त);

पूर्णांक mlx4_init_cq_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_cq_table *cq_table = &mlx4_priv(dev)->cq_table;

	spin_lock_init(&cq_table->lock);
	INIT_RADIX_TREE(&cq_table->tree, GFP_ATOMIC);
	अगर (mlx4_is_slave(dev))
		वापस 0;

	वापस mlx4_biपंचांगap_init(&cq_table->biपंचांगap, dev->caps.num_cqs,
				dev->caps.num_cqs - 1, dev->caps.reserved_cqs, 0);
पूर्ण

व्योम mlx4_cleanup_cq_table(काष्ठा mlx4_dev *dev)
अणु
	अगर (mlx4_is_slave(dev))
		वापस;
	/* Nothing to करो to clean up radix_tree */
	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->cq_table.biपंचांगap);
पूर्ण
