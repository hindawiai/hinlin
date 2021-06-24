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

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/eq.h>
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "fpga/core.h"
#समावेश "eswitch.h"
#समावेश "lib/clock.h"
#समावेश "diag/fw_tracer.h"

क्रमागत अणु
	MLX5_EQE_OWNER_INIT_VAL	= 0x1,
पूर्ण;

क्रमागत अणु
	MLX5_EQ_STATE_ARMED		= 0x9,
	MLX5_EQ_STATE_FIRED		= 0xa,
	MLX5_EQ_STATE_ALWAYS_ARMED	= 0xb,
पूर्ण;

क्रमागत अणु
	MLX5_EQ_DOORBEL_OFFSET	= 0x40,
पूर्ण;

/* budget must be smaller than MLX5_NUM_SPARE_EQE to guarantee that we update
 * the ci beक्रमe we polled all the entries in the EQ. MLX5_NUM_SPARE_EQE is
 * used to set the EQ size, budget must be smaller than the EQ size.
 */
क्रमागत अणु
	MLX5_EQ_POLLING_BUDGET	= 128,
पूर्ण;

अटल_निश्चित(MLX5_EQ_POLLING_BUDGET <= MLX5_NUM_SPARE_EQE);

काष्ठा mlx5_eq_table अणु
	काष्ठा list_head        comp_eqs_list;
	काष्ठा mlx5_eq_async    pages_eq;
	काष्ठा mlx5_eq_async    cmd_eq;
	काष्ठा mlx5_eq_async    async_eq;

	काष्ठा atomic_notअगरier_head nh[MLX5_EVENT_TYPE_MAX];

	/* Since CQ DB is stored in async_eq */
	काष्ठा mlx5_nb          cq_err_nb;

	काष्ठा mutex            lock; /* sync async eqs creations */
	पूर्णांक			num_comp_eqs;
	काष्ठा mlx5_irq_table	*irq_table;
पूर्ण;

#घोषणा MLX5_ASYNC_EVENT_MASK ((1ull << MLX5_EVENT_TYPE_PATH_MIG)	    | \
			       (1ull << MLX5_EVENT_TYPE_COMM_EST)	    | \
			       (1ull << MLX5_EVENT_TYPE_SQ_DRAINED)	    | \
			       (1ull << MLX5_EVENT_TYPE_CQ_ERROR)	    | \
			       (1ull << MLX5_EVENT_TYPE_WQ_CATAS_ERROR)	    | \
			       (1ull << MLX5_EVENT_TYPE_PATH_MIG_FAILED)    | \
			       (1ull << MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR) | \
			       (1ull << MLX5_EVENT_TYPE_WQ_ACCESS_ERROR)    | \
			       (1ull << MLX5_EVENT_TYPE_PORT_CHANGE)	    | \
			       (1ull << MLX5_EVENT_TYPE_SRQ_CATAS_ERROR)    | \
			       (1ull << MLX5_EVENT_TYPE_SRQ_LAST_WQE)	    | \
			       (1ull << MLX5_EVENT_TYPE_SRQ_RQ_LIMIT))

अटल पूर्णांक mlx5_cmd_destroy_eq(काष्ठा mlx5_core_dev *dev, u8 eqn)
अणु
	u32 in[MLX5_ST_SZ_DW(destroy_eq_in)] = अणुपूर्ण;

	MLX5_SET(destroy_eq_in, in, opcode, MLX5_CMD_OP_DESTROY_EQ);
	MLX5_SET(destroy_eq_in, in, eq_number, eqn);
	वापस mlx5_cmd_exec_in(dev, destroy_eq, in);
पूर्ण

/* caller must eventually call mlx5_cq_put on the वापसed cq */
अटल काष्ठा mlx5_core_cq *mlx5_eq_cq_get(काष्ठा mlx5_eq *eq, u32 cqn)
अणु
	काष्ठा mlx5_cq_table *table = &eq->cq_table;
	काष्ठा mlx5_core_cq *cq = शून्य;

	rcu_पढ़ो_lock();
	cq = radix_tree_lookup(&table->tree, cqn);
	अगर (likely(cq))
		mlx5_cq_hold(cq);
	rcu_पढ़ो_unlock();

	वापस cq;
पूर्ण

अटल पूर्णांक mlx5_eq_comp_पूर्णांक(काष्ठा notअगरier_block *nb,
			    __always_unused अचिन्हित दीर्घ action,
			    __always_unused व्योम *data)
अणु
	काष्ठा mlx5_eq_comp *eq_comp =
		container_of(nb, काष्ठा mlx5_eq_comp, irq_nb);
	काष्ठा mlx5_eq *eq = &eq_comp->core;
	काष्ठा mlx5_eqe *eqe;
	पूर्णांक num_eqes = 0;
	u32 cqn = -1;

	eqe = next_eqe_sw(eq);
	अगर (!eqe)
		जाओ out;

	करो अणु
		काष्ठा mlx5_core_cq *cq;

		/* Make sure we पढ़ो EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();
		/* Assume (eqe->type) is always MLX5_EVENT_TYPE_COMP */
		cqn = be32_to_cpu(eqe->data.comp.cqn) & 0xffffff;

		cq = mlx5_eq_cq_get(eq, cqn);
		अगर (likely(cq)) अणु
			++cq->arm_sn;
			cq->comp(cq, eqe);
			mlx5_cq_put(cq);
		पूर्ण अन्यथा अणु
			dev_dbg_ratelimited(eq->dev->device,
					    "Completion event for bogus CQ 0x%x\n", cqn);
		पूर्ण

		++eq->cons_index;

	पूर्ण जबतक ((++num_eqes < MLX5_EQ_POLLING_BUDGET) && (eqe = next_eqe_sw(eq)));

out:
	eq_update_ci(eq, 1);

	अगर (cqn != -1)
		tasklet_schedule(&eq_comp->tasklet_ctx.task);

	वापस 0;
पूर्ण

/* Some architectures करोn't latch पूर्णांकerrupts when they are disabled, so using
 * mlx5_eq_poll_irq_disabled could end up losing पूर्णांकerrupts जबतक trying to
 * aव्योम losing them.  It is not recommended to use it, unless this is the last
 * resort.
 */
u32 mlx5_eq_poll_irq_disabled(काष्ठा mlx5_eq_comp *eq)
अणु
	u32 count_eqe;

	disable_irq(eq->core.irqn);
	count_eqe = eq->core.cons_index;
	mlx5_eq_comp_पूर्णांक(&eq->irq_nb, 0, शून्य);
	count_eqe = eq->core.cons_index - count_eqe;
	enable_irq(eq->core.irqn);

	वापस count_eqe;
पूर्ण

अटल व्योम mlx5_eq_async_पूर्णांक_lock(काष्ठा mlx5_eq_async *eq, bool recovery,
				   अचिन्हित दीर्घ *flags)
	__acquires(&eq->lock)
अणु
	अगर (!recovery)
		spin_lock(&eq->lock);
	अन्यथा
		spin_lock_irqsave(&eq->lock, *flags);
पूर्ण

अटल व्योम mlx5_eq_async_पूर्णांक_unlock(काष्ठा mlx5_eq_async *eq, bool recovery,
				     अचिन्हित दीर्घ *flags)
	__releases(&eq->lock)
अणु
	अगर (!recovery)
		spin_unlock(&eq->lock);
	अन्यथा
		spin_unlock_irqrestore(&eq->lock, *flags);
पूर्ण

क्रमागत async_eq_nb_action अणु
	ASYNC_EQ_IRQ_HANDLER = 0,
	ASYNC_EQ_RECOVER = 1,
पूर्ण;

अटल पूर्णांक mlx5_eq_async_पूर्णांक(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा mlx5_eq_async *eq_async =
		container_of(nb, काष्ठा mlx5_eq_async, irq_nb);
	काष्ठा mlx5_eq *eq = &eq_async->core;
	काष्ठा mlx5_eq_table *eqt;
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_eqe *eqe;
	अचिन्हित दीर्घ flags;
	पूर्णांक num_eqes = 0;
	bool recovery;

	dev = eq->dev;
	eqt = dev->priv.eq_table;

	recovery = action == ASYNC_EQ_RECOVER;
	mlx5_eq_async_पूर्णांक_lock(eq_async, recovery, &flags);

	eqe = next_eqe_sw(eq);
	अगर (!eqe)
		जाओ out;

	करो अणु
		/*
		 * Make sure we पढ़ो EQ entry contents after we've
		 * checked the ownership bit.
		 */
		dma_rmb();

		atomic_notअगरier_call_chain(&eqt->nh[eqe->type], eqe->type, eqe);
		atomic_notअगरier_call_chain(&eqt->nh[MLX5_EVENT_TYPE_NOTIFY_ANY], eqe->type, eqe);

		++eq->cons_index;

	पूर्ण जबतक ((++num_eqes < MLX5_EQ_POLLING_BUDGET) && (eqe = next_eqe_sw(eq)));

out:
	eq_update_ci(eq, 1);
	mlx5_eq_async_पूर्णांक_unlock(eq_async, recovery, &flags);

	वापस unlikely(recovery) ? num_eqes : 0;
पूर्ण

व्योम mlx5_cmd_eq_recover(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_async *eq = &dev->priv.eq_table->cmd_eq;
	पूर्णांक eqes;

	eqes = mlx5_eq_async_पूर्णांक(&eq->irq_nb, ASYNC_EQ_RECOVER, शून्य);
	अगर (eqes)
		mlx5_core_warn(dev, "Recovered %d EQEs on cmd_eq\n", eqes);
पूर्ण

अटल व्योम init_eq_buf(काष्ठा mlx5_eq *eq)
अणु
	काष्ठा mlx5_eqe *eqe;
	पूर्णांक i;

	क्रम (i = 0; i < eq_get_size(eq); i++) अणु
		eqe = get_eqe(eq, i);
		eqe->owner = MLX5_EQE_OWNER_INIT_VAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
create_map_eq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
	      काष्ठा mlx5_eq_param *param)
अणु
	u8 log_eq_size = order_base_2(param->nent + MLX5_NUM_SPARE_EQE);
	काष्ठा mlx5_cq_table *cq_table = &eq->cq_table;
	u32 out[MLX5_ST_SZ_DW(create_eq_out)] = अणु0पूर्ण;
	u8 log_eq_stride = ilog2(MLX5_EQE_SIZE);
	काष्ठा mlx5_priv *priv = &dev->priv;
	u8 vecidx = param->irq_index;
	__be64 *pas;
	व्योम *eqc;
	पूर्णांक inlen;
	u32 *in;
	पूर्णांक err;
	पूर्णांक i;

	/* Init CQ table */
	स_रखो(cq_table, 0, माप(*cq_table));
	spin_lock_init(&cq_table->lock);
	INIT_RADIX_TREE(&cq_table->tree, GFP_ATOMIC);

	eq->cons_index = 0;

	err = mlx5_frag_buf_alloc_node(dev, wq_get_byte_sz(log_eq_size, log_eq_stride),
				       &eq->frag_buf, dev->priv.numa_node);
	अगर (err)
		वापस err;

	mlx5_init_fbc(eq->frag_buf.frags, log_eq_stride, log_eq_size, &eq->fbc);
	init_eq_buf(eq);

	inlen = MLX5_ST_SZ_BYTES(create_eq_in) +
		MLX5_FLD_SZ_BYTES(create_eq_in, pas[0]) * eq->frag_buf.npages;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ err_buf;
	पूर्ण

	pas = (__be64 *)MLX5_ADDR_OF(create_eq_in, in, pas);
	mlx5_fill_page_frag_array(&eq->frag_buf, pas);

	MLX5_SET(create_eq_in, in, opcode, MLX5_CMD_OP_CREATE_EQ);
	अगर (!param->mask[0] && MLX5_CAP_GEN(dev, log_max_uctx))
		MLX5_SET(create_eq_in, in, uid, MLX5_SHARED_RESOURCE_UID);

	क्रम (i = 0; i < 4; i++)
		MLX5_ARRAY_SET64(create_eq_in, in, event_biपंचांगask, i,
				 param->mask[i]);

	eqc = MLX5_ADDR_OF(create_eq_in, in, eq_context_entry);
	MLX5_SET(eqc, eqc, log_eq_size, eq->fbc.log_sz);
	MLX5_SET(eqc, eqc, uar_page, priv->uar->index);
	MLX5_SET(eqc, eqc, पूर्णांकr, vecidx);
	MLX5_SET(eqc, eqc, log_page_size,
		 eq->frag_buf.page_shअगरt - MLX5_ADAPTER_PAGE_SHIFT);

	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
	अगर (err)
		जाओ err_in;

	eq->vecidx = vecidx;
	eq->eqn = MLX5_GET(create_eq_out, out, eq_number);
	eq->irqn = pci_irq_vector(dev->pdev, vecidx);
	eq->dev = dev;
	eq->करोorbell = priv->uar->map + MLX5_EQ_DOORBEL_OFFSET;

	err = mlx5_debug_eq_add(dev, eq);
	अगर (err)
		जाओ err_eq;

	kvमुक्त(in);
	वापस 0;

err_eq:
	mlx5_cmd_destroy_eq(dev, eq->eqn);

err_in:
	kvमुक्त(in);

err_buf:
	mlx5_frag_buf_मुक्त(dev, &eq->frag_buf);
	वापस err;
पूर्ण

/**
 * mlx5_eq_enable - Enable EQ क्रम receiving EQEs
 * @dev : Device which owns the eq
 * @eq  : EQ to enable
 * @nb  : Notअगरier call block
 *
 * Must be called after EQ is created in device.
 *
 * @वापस: 0 अगर no error
 */
पूर्णांक mlx5_eq_enable(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
		   काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_eq_table *eq_table = dev->priv.eq_table;
	पूर्णांक err;

	err = mlx5_irq_attach_nb(eq_table->irq_table, eq->vecidx, nb);
	अगर (!err)
		eq_update_ci(eq, 1);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_eq_enable);

/**
 * mlx5_eq_disable - Disable EQ क्रम receiving EQEs
 * @dev : Device which owns the eq
 * @eq  : EQ to disable
 * @nb  : Notअगरier call block
 *
 * Must be called beक्रमe EQ is destroyed.
 */
व्योम mlx5_eq_disable(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq,
		     काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_eq_table *eq_table = dev->priv.eq_table;

	mlx5_irq_detach_nb(eq_table->irq_table, eq->vecidx, nb);
पूर्ण
EXPORT_SYMBOL(mlx5_eq_disable);

अटल पूर्णांक destroy_unmap_eq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq)
अणु
	पूर्णांक err;

	mlx5_debug_eq_हटाओ(dev, eq);

	err = mlx5_cmd_destroy_eq(dev, eq->eqn);
	अगर (err)
		mlx5_core_warn(dev, "failed to destroy a previously created eq: eqn %d\n",
			       eq->eqn);
	synchronize_irq(eq->irqn);

	mlx5_frag_buf_मुक्त(dev, &eq->frag_buf);

	वापस err;
पूर्ण

पूर्णांक mlx5_eq_add_cq(काष्ठा mlx5_eq *eq, काष्ठा mlx5_core_cq *cq)
अणु
	काष्ठा mlx5_cq_table *table = &eq->cq_table;
	पूर्णांक err;

	spin_lock(&table->lock);
	err = radix_tree_insert(&table->tree, cq->cqn, cq);
	spin_unlock(&table->lock);

	वापस err;
पूर्ण

व्योम mlx5_eq_del_cq(काष्ठा mlx5_eq *eq, काष्ठा mlx5_core_cq *cq)
अणु
	काष्ठा mlx5_cq_table *table = &eq->cq_table;
	काष्ठा mlx5_core_cq *पंचांगp;

	spin_lock(&table->lock);
	पंचांगp = radix_tree_delete(&table->tree, cq->cqn);
	spin_unlock(&table->lock);

	अगर (!पंचांगp) अणु
		mlx5_core_dbg(eq->dev, "cq 0x%x not found in eq 0x%x tree\n",
			      eq->eqn, cq->cqn);
		वापस;
	पूर्ण

	अगर (पंचांगp != cq)
		mlx5_core_dbg(eq->dev, "corruption on cqn 0x%x in eq 0x%x\n",
			      eq->eqn, cq->cqn);
पूर्ण

पूर्णांक mlx5_eq_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *eq_table;
	पूर्णांक i;

	eq_table = kvzalloc(माप(*eq_table), GFP_KERNEL);
	अगर (!eq_table)
		वापस -ENOMEM;

	dev->priv.eq_table = eq_table;

	mlx5_eq_debugfs_init(dev);

	mutex_init(&eq_table->lock);
	क्रम (i = 0; i < MLX5_EVENT_TYPE_MAX; i++)
		ATOMIC_INIT_NOTIFIER_HEAD(&eq_table->nh[i]);

	eq_table->irq_table = mlx5_irq_table_get(dev);
	वापस 0;
पूर्ण

व्योम mlx5_eq_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_eq_debugfs_cleanup(dev);
	kvमुक्त(dev->priv.eq_table);
पूर्ण

/* Async EQs */

अटल पूर्णांक create_async_eq(काष्ठा mlx5_core_dev *dev,
			   काष्ठा mlx5_eq *eq, काष्ठा mlx5_eq_param *param)
अणु
	काष्ठा mlx5_eq_table *eq_table = dev->priv.eq_table;
	पूर्णांक err;

	mutex_lock(&eq_table->lock);
	/* Async EQs must share irq index 0 */
	अगर (param->irq_index != 0) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = create_map_eq(dev, eq, param);
unlock:
	mutex_unlock(&eq_table->lock);
	वापस err;
पूर्ण

अटल पूर्णांक destroy_async_eq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq)
अणु
	काष्ठा mlx5_eq_table *eq_table = dev->priv.eq_table;
	पूर्णांक err;

	mutex_lock(&eq_table->lock);
	err = destroy_unmap_eq(dev, eq);
	mutex_unlock(&eq_table->lock);
	वापस err;
पूर्ण

अटल पूर्णांक cq_err_event_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_eq_table *eqt;
	काष्ठा mlx5_core_cq *cq;
	काष्ठा mlx5_eqe *eqe;
	काष्ठा mlx5_eq *eq;
	u32 cqn;

	/* type == MLX5_EVENT_TYPE_CQ_ERROR */

	eqt = mlx5_nb_cof(nb, काष्ठा mlx5_eq_table, cq_err_nb);
	eq  = &eqt->async_eq.core;
	eqe = data;

	cqn = be32_to_cpu(eqe->data.cq_err.cqn) & 0xffffff;
	mlx5_core_warn(eq->dev, "CQ error on CQN 0x%x, syndrome 0x%x\n",
		       cqn, eqe->data.cq_err.syndrome);

	cq = mlx5_eq_cq_get(eq, cqn);
	अगर (unlikely(!cq)) अणु
		mlx5_core_warn(eq->dev, "Async event for bogus CQ 0x%x\n", cqn);
		वापस NOTIFY_OK;
	पूर्ण

	अगर (cq->event)
		cq->event(cq, type);

	mlx5_cq_put(cq);

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम gather_user_async_events(काष्ठा mlx5_core_dev *dev, u64 mask[4])
अणु
	__be64 *user_unaffiliated_events;
	__be64 *user_affiliated_events;
	पूर्णांक i;

	user_affiliated_events =
		MLX5_CAP_DEV_EVENT(dev, user_affiliated_events);
	user_unaffiliated_events =
		MLX5_CAP_DEV_EVENT(dev, user_unaffiliated_events);

	क्रम (i = 0; i < 4; i++)
		mask[i] |= be64_to_cpu(user_affiliated_events[i] |
				       user_unaffiliated_events[i]);
पूर्ण

अटल व्योम gather_async_events_mask(काष्ठा mlx5_core_dev *dev, u64 mask[4])
अणु
	u64 async_event_mask = MLX5_ASYNC_EVENT_MASK;

	अगर (MLX5_VPORT_MANAGER(dev))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_NIC_VPORT_CHANGE);

	अगर (MLX5_CAP_GEN(dev, general_notअगरication_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_GENERAL_EVENT);

	अगर (MLX5_CAP_GEN(dev, port_module_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_PORT_MODULE_EVENT);
	अन्यथा
		mlx5_core_dbg(dev, "port_module_event is not set\n");

	अगर (MLX5_PPS_CAP(dev))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_PPS_EVENT);

	अगर (MLX5_CAP_GEN(dev, fpga))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_FPGA_ERROR) |
				    (1ull << MLX5_EVENT_TYPE_FPGA_QP_ERROR);
	अगर (MLX5_CAP_GEN_MAX(dev, dct))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_DCT_DRAINED);

	अगर (MLX5_CAP_GEN(dev, temp_warn_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_TEMP_WARN_EVENT);

	अगर (MLX5_CAP_MCAM_REG(dev, tracer_रेजिस्टरs))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_DEVICE_TRACER);

	अगर (MLX5_CAP_GEN(dev, max_num_of_monitor_counters))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_MONITOR_COUNTER);

	अगर (mlx5_eचयन_is_funcs_handler(dev))
		async_event_mask |=
			(1ull << MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED);

	अगर (MLX5_CAP_GEN_MAX(dev, vhca_state))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_VHCA_STATE_CHANGE);

	mask[0] = async_event_mask;

	अगर (MLX5_CAP_GEN(dev, event_cap))
		gather_user_async_events(dev, mask);
पूर्ण

अटल पूर्णांक
setup_async_eq(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq_async *eq,
	       काष्ठा mlx5_eq_param *param, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	eq->irq_nb.notअगरier_call = mlx5_eq_async_पूर्णांक;
	spin_lock_init(&eq->lock);

	err = create_async_eq(dev, &eq->core, param);
	अगर (err) अणु
		mlx5_core_warn(dev, "failed to create %s EQ %d\n", name, err);
		वापस err;
	पूर्ण
	err = mlx5_eq_enable(dev, &eq->core, &eq->irq_nb);
	अगर (err) अणु
		mlx5_core_warn(dev, "failed to enable %s EQ %d\n", name, err);
		destroy_async_eq(dev, &eq->core);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम cleanup_async_eq(काष्ठा mlx5_core_dev *dev,
			     काष्ठा mlx5_eq_async *eq, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	mlx5_eq_disable(dev, &eq->core, &eq->irq_nb);
	err = destroy_async_eq(dev, &eq->core);
	अगर (err)
		mlx5_core_err(dev, "failed to destroy %s eq, err(%d)\n",
			      name, err);
पूर्ण

अटल पूर्णांक create_async_eqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;
	काष्ठा mlx5_eq_param param = अणुपूर्ण;
	पूर्णांक err;

	MLX5_NB_INIT(&table->cq_err_nb, cq_err_event_notअगरier, CQ_ERROR);
	mlx5_eq_notअगरier_रेजिस्टर(dev, &table->cq_err_nb);

	param = (काष्ठा mlx5_eq_param) अणु
		.irq_index = 0,
		.nent = MLX5_NUM_CMD_EQE,
		.mask[0] = 1ull << MLX5_EVENT_TYPE_CMD,
	पूर्ण;
	mlx5_cmd_allowed_opcode(dev, MLX5_CMD_OP_CREATE_EQ);
	err = setup_async_eq(dev, &table->cmd_eq, &param, "cmd");
	अगर (err)
		जाओ err1;

	mlx5_cmd_use_events(dev);
	mlx5_cmd_allowed_opcode(dev, CMD_ALLOWED_OPCODE_ALL);

	param = (काष्ठा mlx5_eq_param) अणु
		.irq_index = 0,
		.nent = MLX5_NUM_ASYNC_EQE,
	पूर्ण;

	gather_async_events_mask(dev, param.mask);
	err = setup_async_eq(dev, &table->async_eq, &param, "async");
	अगर (err)
		जाओ err2;

	param = (काष्ठा mlx5_eq_param) अणु
		.irq_index = 0,
		.nent = /* TODO: sriov max_vf + */ 1,
		.mask[0] = 1ull << MLX5_EVENT_TYPE_PAGE_REQUEST,
	पूर्ण;

	err = setup_async_eq(dev, &table->pages_eq, &param, "pages");
	अगर (err)
		जाओ err3;

	वापस 0;

err3:
	cleanup_async_eq(dev, &table->async_eq, "async");
err2:
	mlx5_cmd_use_polling(dev);
	cleanup_async_eq(dev, &table->cmd_eq, "cmd");
err1:
	mlx5_cmd_allowed_opcode(dev, CMD_ALLOWED_OPCODE_ALL);
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &table->cq_err_nb);
	वापस err;
पूर्ण

अटल व्योम destroy_async_eqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;

	cleanup_async_eq(dev, &table->pages_eq, "pages");
	cleanup_async_eq(dev, &table->async_eq, "async");
	mlx5_cmd_allowed_opcode(dev, MLX5_CMD_OP_DESTROY_EQ);
	mlx5_cmd_use_polling(dev);
	cleanup_async_eq(dev, &table->cmd_eq, "cmd");
	mlx5_cmd_allowed_opcode(dev, CMD_ALLOWED_OPCODE_ALL);
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &table->cq_err_nb);
पूर्ण

काष्ठा mlx5_eq *mlx5_get_async_eq(काष्ठा mlx5_core_dev *dev)
अणु
	वापस &dev->priv.eq_table->async_eq.core;
पूर्ण

व्योम mlx5_eq_synchronize_async_irq(काष्ठा mlx5_core_dev *dev)
अणु
	synchronize_irq(dev->priv.eq_table->async_eq.core.irqn);
पूर्ण

व्योम mlx5_eq_synchronize_cmd_irq(काष्ठा mlx5_core_dev *dev)
अणु
	synchronize_irq(dev->priv.eq_table->cmd_eq.core.irqn);
पूर्ण

/* Generic EQ API क्रम mlx5_core consumers
 * Needed For RDMA ODP EQ क्रम now
 */
काष्ठा mlx5_eq *
mlx5_eq_create_generic(काष्ठा mlx5_core_dev *dev,
		       काष्ठा mlx5_eq_param *param)
अणु
	काष्ठा mlx5_eq *eq = kvzalloc(माप(*eq), GFP_KERNEL);
	पूर्णांक err;

	अगर (!eq)
		वापस ERR_PTR(-ENOMEM);

	err = create_async_eq(dev, eq, param);
	अगर (err) अणु
		kvमुक्त(eq);
		eq = ERR_PTR(err);
	पूर्ण

	वापस eq;
पूर्ण
EXPORT_SYMBOL(mlx5_eq_create_generic);

पूर्णांक mlx5_eq_destroy_generic(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_eq *eq)
अणु
	पूर्णांक err;

	अगर (IS_ERR(eq))
		वापस -EINVAL;

	err = destroy_async_eq(dev, eq);
	अगर (err)
		जाओ out;

	kvमुक्त(eq);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_eq_destroy_generic);

काष्ठा mlx5_eqe *mlx5_eq_get_eqe(काष्ठा mlx5_eq *eq, u32 cc)
अणु
	u32 ci = eq->cons_index + cc;
	u32 nent = eq_get_size(eq);
	काष्ठा mlx5_eqe *eqe;

	eqe = get_eqe(eq, ci & (nent - 1));
	eqe = ((eqe->owner & 1) ^ !!(ci & nent)) ? शून्य : eqe;
	/* Make sure we पढ़ो EQ entry contents after we've
	 * checked the ownership bit.
	 */
	अगर (eqe)
		dma_rmb();

	वापस eqe;
पूर्ण
EXPORT_SYMBOL(mlx5_eq_get_eqe);

व्योम mlx5_eq_update_ci(काष्ठा mlx5_eq *eq, u32 cc, bool arm)
अणु
	__be32 __iomem *addr = eq->करोorbell + (arm ? 0 : 2);
	u32 val;

	eq->cons_index += cc;
	val = (eq->cons_index & 0xffffff) | (eq->eqn << 24);

	__raw_ग_लिखोl((__क्रमce u32)cpu_to_be32(val), addr);
	/* We still want ordering, just not swabbing, so add a barrier */
	wmb();
पूर्ण
EXPORT_SYMBOL(mlx5_eq_update_ci);

अटल व्योम destroy_comp_eqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;
	काष्ठा mlx5_eq_comp *eq, *n;

	list_क्रम_each_entry_safe(eq, n, &table->comp_eqs_list, list) अणु
		list_del(&eq->list);
		mlx5_eq_disable(dev, &eq->core, &eq->irq_nb);
		अगर (destroy_unmap_eq(dev, &eq->core))
			mlx5_core_warn(dev, "failed to destroy comp EQ 0x%x\n",
				       eq->core.eqn);
		tasklet_disable(&eq->tasklet_ctx.task);
		kमुक्त(eq);
	पूर्ण
पूर्ण

अटल पूर्णांक create_comp_eqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;
	काष्ठा mlx5_eq_comp *eq;
	पूर्णांक ncomp_eqs;
	पूर्णांक nent;
	पूर्णांक err;
	पूर्णांक i;

	INIT_LIST_HEAD(&table->comp_eqs_list);
	ncomp_eqs = table->num_comp_eqs;
	nent = MLX5_COMP_EQ_SIZE;
	क्रम (i = 0; i < ncomp_eqs; i++) अणु
		पूर्णांक vecidx = i + MLX5_IRQ_VEC_COMP_BASE;
		काष्ठा mlx5_eq_param param = अणुपूर्ण;

		eq = kzalloc(माप(*eq), GFP_KERNEL);
		अगर (!eq) अणु
			err = -ENOMEM;
			जाओ clean;
		पूर्ण

		INIT_LIST_HEAD(&eq->tasklet_ctx.list);
		INIT_LIST_HEAD(&eq->tasklet_ctx.process_list);
		spin_lock_init(&eq->tasklet_ctx.lock);
		tasklet_setup(&eq->tasklet_ctx.task, mlx5_cq_tasklet_cb);

		eq->irq_nb.notअगरier_call = mlx5_eq_comp_पूर्णांक;
		param = (काष्ठा mlx5_eq_param) अणु
			.irq_index = vecidx,
			.nent = nent,
		पूर्ण;
		err = create_map_eq(dev, &eq->core, &param);
		अगर (err) अणु
			kमुक्त(eq);
			जाओ clean;
		पूर्ण
		err = mlx5_eq_enable(dev, &eq->core, &eq->irq_nb);
		अगर (err) अणु
			destroy_unmap_eq(dev, &eq->core);
			kमुक्त(eq);
			जाओ clean;
		पूर्ण

		mlx5_core_dbg(dev, "allocated completion EQN %d\n", eq->core.eqn);
		/* add tail, to keep the list ordered, क्रम mlx5_vector2eqn to work */
		list_add_tail(&eq->list, &table->comp_eqs_list);
	पूर्ण

	वापस 0;

clean:
	destroy_comp_eqs(dev);
	वापस err;
पूर्ण

पूर्णांक mlx5_vector2eqn(काष्ठा mlx5_core_dev *dev, पूर्णांक vector, पूर्णांक *eqn,
		    अचिन्हित पूर्णांक *irqn)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;
	काष्ठा mlx5_eq_comp *eq, *n;
	पूर्णांक err = -ENOENT;
	पूर्णांक i = 0;

	list_क्रम_each_entry_safe(eq, n, &table->comp_eqs_list, list) अणु
		अगर (i++ == vector) अणु
			*eqn = eq->core.eqn;
			*irqn = eq->core.irqn;
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_vector2eqn);

अचिन्हित पूर्णांक mlx5_comp_vectors_count(काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->priv.eq_table->num_comp_eqs;
पूर्ण
EXPORT_SYMBOL(mlx5_comp_vectors_count);

काष्ठा cpumask *
mlx5_comp_irq_get_affinity_mask(काष्ठा mlx5_core_dev *dev, पूर्णांक vector)
अणु
	पूर्णांक vecidx = vector + MLX5_IRQ_VEC_COMP_BASE;

	वापस mlx5_irq_get_affinity_mask(dev->priv.eq_table->irq_table,
					  vecidx);
पूर्ण
EXPORT_SYMBOL(mlx5_comp_irq_get_affinity_mask);

#अगर_घोषित CONFIG_RFS_ACCEL
काष्ठा cpu_rmap *mlx5_eq_table_get_rmap(काष्ठा mlx5_core_dev *dev)
अणु
	वापस mlx5_irq_get_rmap(dev->priv.eq_table->irq_table);
पूर्ण
#पूर्ण_अगर

काष्ठा mlx5_eq_comp *mlx5_eqn2comp_eq(काष्ठा mlx5_core_dev *dev, पूर्णांक eqn)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;
	काष्ठा mlx5_eq_comp *eq;

	list_क्रम_each_entry(eq, &table->comp_eqs_list, list) अणु
		अगर (eq->core.eqn == eqn)
			वापस eq;
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

/* This function should only be called after mlx5_cmd_क्रमce_tearकरोwn_hca */
व्योम mlx5_core_eq_मुक्त_irqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *table = dev->priv.eq_table;

	mutex_lock(&table->lock); /* sync with create/destroy_async_eq */
	mlx5_irq_table_destroy(dev);
	mutex_unlock(&table->lock);
पूर्ण

#अगर_घोषित CONFIG_INFINIBAND_ON_DEMAND_PAGING
#घोषणा MLX5_MAX_ASYNC_EQS 4
#अन्यथा
#घोषणा MLX5_MAX_ASYNC_EQS 3
#पूर्ण_अगर

पूर्णांक mlx5_eq_table_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eq_table *eq_table = dev->priv.eq_table;
	पूर्णांक num_eqs = MLX5_CAP_GEN(dev, max_num_eqs) ?
		      MLX5_CAP_GEN(dev, max_num_eqs) :
		      1 << MLX5_CAP_GEN(dev, log_max_eq);
	पूर्णांक err;

	eq_table->num_comp_eqs =
		min_t(पूर्णांक,
		      mlx5_irq_get_num_comp(eq_table->irq_table),
		      num_eqs - MLX5_MAX_ASYNC_EQS);

	err = create_async_eqs(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to create async EQs\n");
		जाओ err_async_eqs;
	पूर्ण

	err = create_comp_eqs(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to create completion EQs\n");
		जाओ err_comp_eqs;
	पूर्ण

	वापस 0;
err_comp_eqs:
	destroy_async_eqs(dev);
err_async_eqs:
	वापस err;
पूर्ण

व्योम mlx5_eq_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	destroy_comp_eqs(dev);
	destroy_async_eqs(dev);
पूर्ण

पूर्णांक mlx5_eq_notअगरier_रेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_nb *nb)
अणु
	काष्ठा mlx5_eq_table *eqt = dev->priv.eq_table;

	वापस atomic_notअगरier_chain_रेजिस्टर(&eqt->nh[nb->event_type], &nb->nb);
पूर्ण
EXPORT_SYMBOL(mlx5_eq_notअगरier_रेजिस्टर);

पूर्णांक mlx5_eq_notअगरier_unरेजिस्टर(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_nb *nb)
अणु
	काष्ठा mlx5_eq_table *eqt = dev->priv.eq_table;

	वापस atomic_notअगरier_chain_unरेजिस्टर(&eqt->nh[nb->event_type], &nb->nb);
पूर्ण
EXPORT_SYMBOL(mlx5_eq_notअगरier_unरेजिस्टर);
