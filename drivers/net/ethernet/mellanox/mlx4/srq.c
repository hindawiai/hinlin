<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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


#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/srq.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>

#समावेश "mlx4.h"
#समावेश "icm.h"

व्योम mlx4_srq_event(काष्ठा mlx4_dev *dev, u32 srqn, पूर्णांक event_type)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	काष्ठा mlx4_srq *srq;

	rcu_पढ़ो_lock();
	srq = radix_tree_lookup(&srq_table->tree, srqn & (dev->caps.num_srqs - 1));
	rcu_पढ़ो_unlock();
	अगर (srq)
		refcount_inc(&srq->refcount);
	अन्यथा अणु
		mlx4_warn(dev, "Async event for bogus SRQ %08x\n", srqn);
		वापस;
	पूर्ण

	srq->event(srq, event_type);

	अगर (refcount_dec_and_test(&srq->refcount))
		complete(&srq->मुक्त);
पूर्ण

अटल पूर्णांक mlx4_SW2HW_SRQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक srq_num)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, srq_num, 0,
			MLX4_CMD_SW2HW_SRQ, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_HW2SW_SRQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक srq_num)
अणु
	वापस mlx4_cmd_box(dev, 0, mailbox ? mailbox->dma : 0, srq_num,
			    mailbox ? 0 : 1, MLX4_CMD_HW2SW_SRQ,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_ARM_SRQ(काष्ठा mlx4_dev *dev, पूर्णांक srq_num, पूर्णांक limit_watermark)
अणु
	वापस mlx4_cmd(dev, limit_watermark, srq_num, 0, MLX4_CMD_ARM_SRQ,
			MLX4_CMD_TIME_CLASS_B, MLX4_CMD_WRAPPED);
पूर्ण

अटल पूर्णांक mlx4_QUERY_SRQ(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			  पूर्णांक srq_num)
अणु
	वापस mlx4_cmd_box(dev, 0, mailbox->dma, srq_num, 0, MLX4_CMD_QUERY_SRQ,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
पूर्ण

पूर्णांक __mlx4_srq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *srqn)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	पूर्णांक err;


	*srqn = mlx4_biपंचांगap_alloc(&srq_table->biपंचांगap);
	अगर (*srqn == -1)
		वापस -ENOMEM;

	err = mlx4_table_get(dev, &srq_table->table, *srqn);
	अगर (err)
		जाओ err_out;

	err = mlx4_table_get(dev, &srq_table->cmpt_table, *srqn);
	अगर (err)
		जाओ err_put;
	वापस 0;

err_put:
	mlx4_table_put(dev, &srq_table->table, *srqn);

err_out:
	mlx4_biपंचांगap_मुक्त(&srq_table->biपंचांगap, *srqn, MLX4_NO_RR);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_srq_alloc_icm(काष्ठा mlx4_dev *dev, पूर्णांक *srqn)
अणु
	u64 out_param;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		err = mlx4_cmd_imm(dev, 0, &out_param, RES_SRQ,
				   RES_OP_RESERVE_AND_MAP,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (!err)
			*srqn = get_param_l(&out_param);

		वापस err;
	पूर्ण
	वापस __mlx4_srq_alloc_icm(dev, srqn);
पूर्ण

व्योम __mlx4_srq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक srqn)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;

	mlx4_table_put(dev, &srq_table->cmpt_table, srqn);
	mlx4_table_put(dev, &srq_table->table, srqn);
	mlx4_biपंचांगap_मुक्त(&srq_table->biपंचांगap, srqn, MLX4_NO_RR);
पूर्ण

अटल व्योम mlx4_srq_मुक्त_icm(काष्ठा mlx4_dev *dev, पूर्णांक srqn)
अणु
	u64 in_param = 0;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, srqn);
		अगर (mlx4_cmd(dev, in_param, RES_SRQ, RES_OP_RESERVE_AND_MAP,
			     MLX4_CMD_FREE_RES,
			     MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED))
			mlx4_warn(dev, "Failed freeing cq:%d\n", srqn);
		वापस;
	पूर्ण
	__mlx4_srq_मुक्त_icm(dev, srqn);
पूर्ण

पूर्णांक mlx4_srq_alloc(काष्ठा mlx4_dev *dev, u32 pdn, u32 cqn, u16 xrcd,
		   काष्ठा mlx4_mtt *mtt, u64 db_rec, काष्ठा mlx4_srq *srq)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_srq_context *srq_context;
	u64 mtt_addr;
	पूर्णांक err;

	err = mlx4_srq_alloc_icm(dev, &srq->srqn);
	अगर (err)
		वापस err;

	spin_lock_irq(&srq_table->lock);
	err = radix_tree_insert(&srq_table->tree, srq->srqn, srq);
	spin_unlock_irq(&srq_table->lock);
	अगर (err)
		जाओ err_icm;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ err_radix;
	पूर्ण

	srq_context = mailbox->buf;
	srq_context->state_logsize_srqn = cpu_to_be32((ilog2(srq->max) << 24) |
						      srq->srqn);
	srq_context->logstride          = srq->wqe_shअगरt - 4;
	srq_context->xrcd		= cpu_to_be16(xrcd);
	srq_context->pg_offset_cqn	= cpu_to_be32(cqn & 0xffffff);
	srq_context->log_page_size      = mtt->page_shअगरt - MLX4_ICM_PAGE_SHIFT;

	mtt_addr = mlx4_mtt_addr(dev, mtt);
	srq_context->mtt_base_addr_h    = mtt_addr >> 32;
	srq_context->mtt_base_addr_l    = cpu_to_be32(mtt_addr & 0xffffffff);
	srq_context->pd			= cpu_to_be32(pdn);
	srq_context->db_rec_addr        = cpu_to_be64(db_rec);

	err = mlx4_SW2HW_SRQ(dev, mailbox, srq->srqn);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (err)
		जाओ err_radix;

	refcount_set(&srq->refcount, 1);
	init_completion(&srq->मुक्त);

	वापस 0;

err_radix:
	spin_lock_irq(&srq_table->lock);
	radix_tree_delete(&srq_table->tree, srq->srqn);
	spin_unlock_irq(&srq_table->lock);

err_icm:
	mlx4_srq_मुक्त_icm(dev, srq->srqn);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_srq_alloc);

व्योम mlx4_srq_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	पूर्णांक err;

	err = mlx4_HW2SW_SRQ(dev, शून्य, srq->srqn);
	अगर (err)
		mlx4_warn(dev, "HW2SW_SRQ failed (%d) for SRQN %06x\n", err, srq->srqn);

	spin_lock_irq(&srq_table->lock);
	radix_tree_delete(&srq_table->tree, srq->srqn);
	spin_unlock_irq(&srq_table->lock);

	अगर (refcount_dec_and_test(&srq->refcount))
		complete(&srq->मुक्त);
	रुको_क्रम_completion(&srq->मुक्त);

	mlx4_srq_मुक्त_icm(dev, srq->srqn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_srq_मुक्त);

पूर्णांक mlx4_srq_arm(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq, पूर्णांक limit_watermark)
अणु
	वापस mlx4_ARM_SRQ(dev, srq->srqn, limit_watermark);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_srq_arm);

पूर्णांक mlx4_srq_query(काष्ठा mlx4_dev *dev, काष्ठा mlx4_srq *srq, पूर्णांक *limit_watermark)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_srq_context *srq_context;
	पूर्णांक err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	srq_context = mailbox->buf;

	err = mlx4_QUERY_SRQ(dev, mailbox, srq->srqn);
	अगर (err)
		जाओ err_out;
	*limit_watermark = be16_to_cpu(srq_context->limit_watermark);

err_out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_srq_query);

पूर्णांक mlx4_init_srq_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;

	spin_lock_init(&srq_table->lock);
	INIT_RADIX_TREE(&srq_table->tree, GFP_ATOMIC);
	अगर (mlx4_is_slave(dev))
		वापस 0;

	वापस mlx4_biपंचांगap_init(&srq_table->biपंचांगap, dev->caps.num_srqs,
				dev->caps.num_srqs - 1, dev->caps.reserved_srqs, 0);
पूर्ण

व्योम mlx4_cleanup_srq_table(काष्ठा mlx4_dev *dev)
अणु
	अगर (mlx4_is_slave(dev))
		वापस;
	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->srq_table.biपंचांगap);
पूर्ण

काष्ठा mlx4_srq *mlx4_srq_lookup(काष्ठा mlx4_dev *dev, u32 srqn)
अणु
	काष्ठा mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	काष्ठा mlx4_srq *srq;

	rcu_पढ़ो_lock();
	srq = radix_tree_lookup(&srq_table->tree,
				srqn & (dev->caps.num_srqs - 1));
	rcu_पढ़ो_unlock();

	वापस srq;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_srq_lookup);
