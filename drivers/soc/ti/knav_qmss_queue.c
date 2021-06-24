<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keystone Queue Manager subप्रणाली driver
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/soc/ti/knav_qmss.h>

#समावेश "knav_qmss.h"

अटल काष्ठा knav_device *kdev;
अटल DEFINE_MUTEX(knav_dev_lock);
#घोषणा knav_dev_lock_held() \
	lockdep_is_held(&knav_dev_lock)

/* Queue manager रेजिस्टर indices in DTS */
#घोषणा KNAV_QUEUE_PEEK_REG_INDEX	0
#घोषणा KNAV_QUEUE_STATUS_REG_INDEX	1
#घोषणा KNAV_QUEUE_CONFIG_REG_INDEX	2
#घोषणा KNAV_QUEUE_REGION_REG_INDEX	3
#घोषणा KNAV_QUEUE_PUSH_REG_INDEX	4
#घोषणा KNAV_QUEUE_POP_REG_INDEX	5

/* Queue manager रेजिस्टर indices in DTS क्रम QMSS in K2G NAVSS.
 * There are no status and vbusm push रेजिस्टरs on this version
 * of QMSS. Push रेजिस्टरs are same as pop, So all indices above 1
 * are to be re-defined
 */
#घोषणा KNAV_L_QUEUE_CONFIG_REG_INDEX	1
#घोषणा KNAV_L_QUEUE_REGION_REG_INDEX	2
#घोषणा KNAV_L_QUEUE_PUSH_REG_INDEX	3

/* PDSP रेजिस्टर indices in DTS */
#घोषणा KNAV_QUEUE_PDSP_IRAM_REG_INDEX	0
#घोषणा KNAV_QUEUE_PDSP_REGS_REG_INDEX	1
#घोषणा KNAV_QUEUE_PDSP_INTD_REG_INDEX	2
#घोषणा KNAV_QUEUE_PDSP_CMD_REG_INDEX	3

#घोषणा knav_queue_idx_to_inst(kdev, idx)			\
	(kdev->instances + (idx << kdev->inst_shअगरt))

#घोषणा क्रम_each_handle_rcu(qh, inst)				\
	list_क्रम_each_entry_rcu(qh, &inst->handles, list,	\
				knav_dev_lock_held())

#घोषणा क्रम_each_instance(idx, inst, kdev)		\
	क्रम (idx = 0, inst = kdev->instances;		\
	     idx < (kdev)->num_queues_in_use;			\
	     idx++, inst = knav_queue_idx_to_inst(kdev, idx))

/* All firmware file names end up here. List the firmware file names below.
 * Newest followed by older ones. Search is करोne from start of the array
 * until a firmware file is found.
 */
स्थिर अक्षर *knav_acc_firmwares[] = अणु"ks2_qmss_pdsp_acc48.bin"पूर्ण;

अटल bool device_पढ़ोy;
bool knav_qmss_device_पढ़ोy(व्योम)
अणु
	वापस device_पढ़ोy;
पूर्ण
EXPORT_SYMBOL_GPL(knav_qmss_device_पढ़ोy);

/**
 * knav_queue_notअगरy: qmss queue notfier call
 *
 * @inst:		- qmss queue instance like accumulator
 */
व्योम knav_queue_notअगरy(काष्ठा knav_queue_inst *inst)
अणु
	काष्ठा knav_queue *qh;

	अगर (!inst)
		वापस;

	rcu_पढ़ो_lock();
	क्रम_each_handle_rcu(qh, inst) अणु
		अगर (atomic_पढ़ो(&qh->notअगरier_enabled) <= 0)
			जारी;
		अगर (WARN_ON(!qh->notअगरier_fn))
			जारी;
		this_cpu_inc(qh->stats->notअगरies);
		qh->notअगरier_fn(qh->notअगरier_fn_arg);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_notअगरy);

अटल irqवापस_t knav_queue_पूर्णांक_handler(पूर्णांक irq, व्योम *_instdata)
अणु
	काष्ठा knav_queue_inst *inst = _instdata;

	knav_queue_notअगरy(inst);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक knav_queue_setup_irq(काष्ठा knav_range_info *range,
			  काष्ठा knav_queue_inst *inst)
अणु
	अचिन्हित queue = inst->id - range->queue_base;
	पूर्णांक ret = 0, irq;

	अगर (range->flags & RANGE_HAS_IRQ) अणु
		irq = range->irqs[queue].irq;
		ret = request_irq(irq, knav_queue_पूर्णांक_handler, 0,
					inst->irq_name, inst);
		अगर (ret)
			वापस ret;
		disable_irq(irq);
		अगर (range->irqs[queue].cpu_mask) अणु
			ret = irq_set_affinity_hपूर्णांक(irq, range->irqs[queue].cpu_mask);
			अगर (ret) अणु
				dev_warn(range->kdev->dev,
					 "Failed to set IRQ affinity\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम knav_queue_मुक्त_irq(काष्ठा knav_queue_inst *inst)
अणु
	काष्ठा knav_range_info *range = inst->range;
	अचिन्हित queue = inst->id - inst->range->queue_base;
	पूर्णांक irq;

	अगर (range->flags & RANGE_HAS_IRQ) अणु
		irq = range->irqs[queue].irq;
		irq_set_affinity_hपूर्णांक(irq, शून्य);
		मुक्त_irq(irq, inst);
	पूर्ण
पूर्ण

अटल अंतरभूत bool knav_queue_is_busy(काष्ठा knav_queue_inst *inst)
अणु
	वापस !list_empty(&inst->handles);
पूर्ण

अटल अंतरभूत bool knav_queue_is_reserved(काष्ठा knav_queue_inst *inst)
अणु
	वापस inst->range->flags & RANGE_RESERVED;
पूर्ण

अटल अंतरभूत bool knav_queue_is_shared(काष्ठा knav_queue_inst *inst)
अणु
	काष्ठा knav_queue *पंचांगp;

	rcu_पढ़ो_lock();
	क्रम_each_handle_rcu(पंचांगp, inst) अणु
		अगर (पंचांगp->flags & KNAV_QUEUE_SHARED) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण

अटल अंतरभूत bool knav_queue_match_type(काष्ठा knav_queue_inst *inst,
						अचिन्हित type)
अणु
	अगर ((type == KNAV_QUEUE_QPEND) &&
	    (inst->range->flags & RANGE_HAS_IRQ)) अणु
		वापस true;
	पूर्ण अन्यथा अगर ((type == KNAV_QUEUE_ACC) &&
		(inst->range->flags & RANGE_HAS_ACCUMULATOR)) अणु
		वापस true;
	पूर्ण अन्यथा अगर ((type == KNAV_QUEUE_GP) &&
		!(inst->range->flags &
			(RANGE_HAS_ACCUMULATOR | RANGE_HAS_IRQ))) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा knav_queue_inst *
knav_queue_match_id_to_inst(काष्ठा knav_device *kdev, अचिन्हित id)
अणु
	काष्ठा knav_queue_inst *inst;
	पूर्णांक idx;

	क्रम_each_instance(idx, inst, kdev) अणु
		अगर (inst->id == id)
			वापस inst;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा knav_queue_inst *knav_queue_find_by_id(पूर्णांक id)
अणु
	अगर (kdev->base_id <= id &&
	    kdev->base_id + kdev->num_queues > id) अणु
		id -= kdev->base_id;
		वापस knav_queue_match_id_to_inst(kdev, id);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा knav_queue *__knav_queue_खोलो(काष्ठा knav_queue_inst *inst,
				      स्थिर अक्षर *name, अचिन्हित flags)
अणु
	काष्ठा knav_queue *qh;
	अचिन्हित id;
	पूर्णांक ret = 0;

	qh = devm_kzalloc(inst->kdev->dev, माप(*qh), GFP_KERNEL);
	अगर (!qh)
		वापस ERR_PTR(-ENOMEM);

	qh->stats = alloc_percpu(काष्ठा knav_queue_stats);
	अगर (!qh->stats) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	qh->flags = flags;
	qh->inst = inst;
	id = inst->id - inst->qmgr->start_queue;
	qh->reg_push = &inst->qmgr->reg_push[id];
	qh->reg_pop = &inst->qmgr->reg_pop[id];
	qh->reg_peek = &inst->qmgr->reg_peek[id];

	/* first खोलोer? */
	अगर (!knav_queue_is_busy(inst)) अणु
		काष्ठा knav_range_info *range = inst->range;

		inst->name = kstrndup(name, KNAV_NAME_SIZE - 1, GFP_KERNEL);
		अगर (range->ops && range->ops->खोलो_queue)
			ret = range->ops->खोलो_queue(range, inst, flags);

		अगर (ret)
			जाओ err;
	पूर्ण
	list_add_tail_rcu(&qh->list, &inst->handles);
	वापस qh;

err:
	अगर (qh->stats)
		मुक्त_percpu(qh->stats);
	devm_kमुक्त(inst->kdev->dev, qh);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा knav_queue *
knav_queue_खोलो_by_id(स्थिर अक्षर *name, अचिन्हित id, अचिन्हित flags)
अणु
	काष्ठा knav_queue_inst *inst;
	काष्ठा knav_queue *qh;

	mutex_lock(&knav_dev_lock);

	qh = ERR_PTR(-ENODEV);
	inst = knav_queue_find_by_id(id);
	अगर (!inst)
		जाओ unlock_ret;

	qh = ERR_PTR(-EEXIST);
	अगर (!(flags & KNAV_QUEUE_SHARED) && knav_queue_is_busy(inst))
		जाओ unlock_ret;

	qh = ERR_PTR(-EBUSY);
	अगर ((flags & KNAV_QUEUE_SHARED) &&
	    (knav_queue_is_busy(inst) && !knav_queue_is_shared(inst)))
		जाओ unlock_ret;

	qh = __knav_queue_खोलो(inst, name, flags);

unlock_ret:
	mutex_unlock(&knav_dev_lock);

	वापस qh;
पूर्ण

अटल काष्ठा knav_queue *knav_queue_खोलो_by_type(स्थिर अक्षर *name,
						अचिन्हित type, अचिन्हित flags)
अणु
	काष्ठा knav_queue_inst *inst;
	काष्ठा knav_queue *qh = ERR_PTR(-EINVAL);
	पूर्णांक idx;

	mutex_lock(&knav_dev_lock);

	क्रम_each_instance(idx, inst, kdev) अणु
		अगर (knav_queue_is_reserved(inst))
			जारी;
		अगर (!knav_queue_match_type(inst, type))
			जारी;
		अगर (knav_queue_is_busy(inst))
			जारी;
		qh = __knav_queue_खोलो(inst, name, flags);
		जाओ unlock_ret;
	पूर्ण

unlock_ret:
	mutex_unlock(&knav_dev_lock);
	वापस qh;
पूर्ण

अटल व्योम knav_queue_set_notअगरy(काष्ठा knav_queue_inst *inst, bool enabled)
अणु
	काष्ठा knav_range_info *range = inst->range;

	अगर (range->ops && range->ops->set_notअगरy)
		range->ops->set_notअगरy(range, inst, enabled);
पूर्ण

अटल पूर्णांक knav_queue_enable_notअगरier(काष्ठा knav_queue *qh)
अणु
	काष्ठा knav_queue_inst *inst = qh->inst;
	bool first;

	अगर (WARN_ON(!qh->notअगरier_fn))
		वापस -EINVAL;

	/* Adjust the per handle notअगरier count */
	first = (atomic_inc_वापस(&qh->notअगरier_enabled) == 1);
	अगर (!first)
		वापस 0; /* nothing to करो */

	/* Now adjust the per instance notअगरier count */
	first = (atomic_inc_वापस(&inst->num_notअगरiers) == 1);
	अगर (first)
		knav_queue_set_notअगरy(inst, true);

	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_disable_notअगरier(काष्ठा knav_queue *qh)
अणु
	काष्ठा knav_queue_inst *inst = qh->inst;
	bool last;

	last = (atomic_dec_वापस(&qh->notअगरier_enabled) == 0);
	अगर (!last)
		वापस 0; /* nothing to करो */

	last = (atomic_dec_वापस(&inst->num_notअगरiers) == 0);
	अगर (last)
		knav_queue_set_notअगरy(inst, false);

	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_set_notअगरier(काष्ठा knav_queue *qh,
				काष्ठा knav_queue_notअगरy_config *cfg)
अणु
	knav_queue_notअगरy_fn old_fn = qh->notअगरier_fn;

	अगर (!cfg)
		वापस -EINVAL;

	अगर (!(qh->inst->range->flags & (RANGE_HAS_ACCUMULATOR | RANGE_HAS_IRQ)))
		वापस -ENOTSUPP;

	अगर (!cfg->fn && old_fn)
		knav_queue_disable_notअगरier(qh);

	qh->notअगरier_fn = cfg->fn;
	qh->notअगरier_fn_arg = cfg->fn_arg;

	अगर (cfg->fn && !old_fn)
		knav_queue_enable_notअगरier(qh);

	वापस 0;
पूर्ण

अटल पूर्णांक knav_gp_set_notअगरy(काष्ठा knav_range_info *range,
			       काष्ठा knav_queue_inst *inst,
			       bool enabled)
अणु
	अचिन्हित queue;

	अगर (range->flags & RANGE_HAS_IRQ) अणु
		queue = inst->id - range->queue_base;
		अगर (enabled)
			enable_irq(range->irqs[queue].irq);
		अन्यथा
			disable_irq_nosync(range->irqs[queue].irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक knav_gp_खोलो_queue(काष्ठा knav_range_info *range,
				काष्ठा knav_queue_inst *inst, अचिन्हित flags)
अणु
	वापस knav_queue_setup_irq(range, inst);
पूर्ण

अटल पूर्णांक knav_gp_बंद_queue(काष्ठा knav_range_info *range,
				काष्ठा knav_queue_inst *inst)
अणु
	knav_queue_मुक्त_irq(inst);
	वापस 0;
पूर्ण

अटल काष्ठा knav_range_ops knav_gp_range_ops = अणु
	.set_notअगरy	= knav_gp_set_notअगरy,
	.खोलो_queue	= knav_gp_खोलो_queue,
	.बंद_queue	= knav_gp_बंद_queue,
पूर्ण;


अटल पूर्णांक knav_queue_get_count(व्योम *qhandle)
अणु
	काष्ठा knav_queue *qh = qhandle;
	काष्ठा knav_queue_inst *inst = qh->inst;

	वापस पढ़ोl_relaxed(&qh->reg_peek[0].entry_count) +
		atomic_पढ़ो(&inst->desc_count);
पूर्ण

अटल व्योम knav_queue_debug_show_instance(काष्ठा seq_file *s,
					काष्ठा knav_queue_inst *inst)
अणु
	काष्ठा knav_device *kdev = inst->kdev;
	काष्ठा knav_queue *qh;
	पूर्णांक cpu = 0;
	पूर्णांक pushes = 0;
	पूर्णांक pops = 0;
	पूर्णांक push_errors = 0;
	पूर्णांक pop_errors = 0;
	पूर्णांक notअगरies = 0;

	अगर (!knav_queue_is_busy(inst))
		वापस;

	seq_म_लिखो(s, "\tqueue id %d (%s)\n",
		   kdev->base_id + inst->id, inst->name);
	क्रम_each_handle_rcu(qh, inst) अणु
		क्रम_each_possible_cpu(cpu) अणु
			pushes += per_cpu_ptr(qh->stats, cpu)->pushes;
			pops += per_cpu_ptr(qh->stats, cpu)->pops;
			push_errors += per_cpu_ptr(qh->stats, cpu)->push_errors;
			pop_errors += per_cpu_ptr(qh->stats, cpu)->pop_errors;
			notअगरies += per_cpu_ptr(qh->stats, cpu)->notअगरies;
		पूर्ण

		seq_म_लिखो(s, "\t\thandle %p: pushes %8d, pops %8d, count %8d, notifies %8d, push errors %8d, pop errors %8d\n",
				qh,
				pushes,
				pops,
				knav_queue_get_count(qh),
				notअगरies,
				push_errors,
				pop_errors);
	पूर्ण
पूर्ण

अटल पूर्णांक knav_queue_debug_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा knav_queue_inst *inst;
	पूर्णांक idx;

	mutex_lock(&knav_dev_lock);
	seq_म_लिखो(s, "%s: %u-%u\n",
		   dev_name(kdev->dev), kdev->base_id,
		   kdev->base_id + kdev->num_queues - 1);
	क्रम_each_instance(idx, inst, kdev)
		knav_queue_debug_show_instance(s, inst);
	mutex_unlock(&knav_dev_lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(knav_queue_debug);

अटल अंतरभूत पूर्णांक knav_queue_pdsp_रुको(u32 * __iomem addr, अचिन्हित समयout,
					u32 flags)
अणु
	अचिन्हित दीर्घ end;
	u32 val = 0;

	end = jअगरfies + msecs_to_jअगरfies(समयout);
	जबतक (समय_after(end, jअगरfies)) अणु
		val = पढ़ोl_relaxed(addr);
		अगर (flags)
			val &= flags;
		अगर (!val)
			अवरोध;
		cpu_relax();
	पूर्ण
	वापस val ? -ETIMEDOUT : 0;
पूर्ण


अटल पूर्णांक knav_queue_flush(काष्ठा knav_queue *qh)
अणु
	काष्ठा knav_queue_inst *inst = qh->inst;
	अचिन्हित id = inst->id - inst->qmgr->start_queue;

	atomic_set(&inst->desc_count, 0);
	ग_लिखोl_relaxed(0, &inst->qmgr->reg_push[id].ptr_माप_प्रकारhresh);
	वापस 0;
पूर्ण

/**
 * knav_queue_खोलो()	- खोलो a hardware queue
 * @name:		- name to give the queue handle
 * @id:			- desired queue number अगर any or specअगरes the type
 *			  of queue
 * @flags:		- the following flags are applicable to queues:
 *	KNAV_QUEUE_SHARED - allow the queue to be shared. Queues are
 *			     exclusive by शेष.
 *			     Subsequent attempts to खोलो a shared queue should
 *			     also have this flag.
 *
 * Returns a handle to the खोलो hardware queue अगर successful. Use IS_ERR()
 * to check the वापसed value क्रम error codes.
 */
व्योम *knav_queue_खोलो(स्थिर अक्षर *name, अचिन्हित id,
					अचिन्हित flags)
अणु
	काष्ठा knav_queue *qh = ERR_PTR(-EINVAL);

	चयन (id) अणु
	हाल KNAV_QUEUE_QPEND:
	हाल KNAV_QUEUE_ACC:
	हाल KNAV_QUEUE_GP:
		qh = knav_queue_खोलो_by_type(name, id, flags);
		अवरोध;

	शेष:
		qh = knav_queue_खोलो_by_id(name, id, flags);
		अवरोध;
	पूर्ण
	वापस qh;
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_खोलो);

/**
 * knav_queue_बंद()	- बंद a hardware queue handle
 * @qhandle:		- handle to बंद
 */
व्योम knav_queue_बंद(व्योम *qhandle)
अणु
	काष्ठा knav_queue *qh = qhandle;
	काष्ठा knav_queue_inst *inst = qh->inst;

	जबतक (atomic_पढ़ो(&qh->notअगरier_enabled) > 0)
		knav_queue_disable_notअगरier(qh);

	mutex_lock(&knav_dev_lock);
	list_del_rcu(&qh->list);
	mutex_unlock(&knav_dev_lock);
	synchronize_rcu();
	अगर (!knav_queue_is_busy(inst)) अणु
		काष्ठा knav_range_info *range = inst->range;

		अगर (range->ops && range->ops->बंद_queue)
			range->ops->बंद_queue(range, inst);
	पूर्ण
	मुक्त_percpu(qh->stats);
	devm_kमुक्त(inst->kdev->dev, qh);
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_बंद);

/**
 * knav_queue_device_control()	- Perक्रमm control operations on a queue
 * @qhandle:			- queue handle
 * @cmd:			- control commands
 * @arg:			- command argument
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक knav_queue_device_control(व्योम *qhandle, क्रमागत knav_queue_ctrl_cmd cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा knav_queue *qh = qhandle;
	काष्ठा knav_queue_notअगरy_config *cfg;
	पूर्णांक ret;

	चयन ((पूर्णांक)cmd) अणु
	हाल KNAV_QUEUE_GET_ID:
		ret = qh->inst->kdev->base_id + qh->inst->id;
		अवरोध;

	हाल KNAV_QUEUE_FLUSH:
		ret = knav_queue_flush(qh);
		अवरोध;

	हाल KNAV_QUEUE_SET_NOTIFIER:
		cfg = (व्योम *)arg;
		ret = knav_queue_set_notअगरier(qh, cfg);
		अवरोध;

	हाल KNAV_QUEUE_ENABLE_NOTIFY:
		ret = knav_queue_enable_notअगरier(qh);
		अवरोध;

	हाल KNAV_QUEUE_DISABLE_NOTIFY:
		ret = knav_queue_disable_notअगरier(qh);
		अवरोध;

	हाल KNAV_QUEUE_GET_COUNT:
		ret = knav_queue_get_count(qh);
		अवरोध;

	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_device_control);



/**
 * knav_queue_push()	- push data (or descriptor) to the tail of a queue
 * @qhandle:		- hardware queue handle
 * @dma:		- DMA data to push
 * @size:		- size of data to push
 * @flags:		- can be used to pass additional inक्रमmation
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक knav_queue_push(व्योम *qhandle, dma_addr_t dma,
					अचिन्हित size, अचिन्हित flags)
अणु
	काष्ठा knav_queue *qh = qhandle;
	u32 val;

	val = (u32)dma | ((size / 16) - 1);
	ग_लिखोl_relaxed(val, &qh->reg_push[0].ptr_माप_प्रकारhresh);

	this_cpu_inc(qh->stats->pushes);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_push);

/**
 * knav_queue_pop()	- pop data (or descriptor) from the head of a queue
 * @qhandle:		- hardware queue handle
 * @size:		- (optional) size of the data pop'ed.
 *
 * Returns a DMA address on success, 0 on failure.
 */
dma_addr_t knav_queue_pop(व्योम *qhandle, अचिन्हित *size)
अणु
	काष्ठा knav_queue *qh = qhandle;
	काष्ठा knav_queue_inst *inst = qh->inst;
	dma_addr_t dma;
	u32 val, idx;

	/* are we accumulated? */
	अगर (inst->descs) अणु
		अगर (unlikely(atomic_dec_वापस(&inst->desc_count) < 0)) अणु
			atomic_inc(&inst->desc_count);
			वापस 0;
		पूर्ण
		idx  = atomic_inc_वापस(&inst->desc_head);
		idx &= ACC_DESCS_MASK;
		val = inst->descs[idx];
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(&qh->reg_pop[0].ptr_माप_प्रकारhresh);
		अगर (unlikely(!val))
			वापस 0;
	पूर्ण

	dma = val & DESC_PTR_MASK;
	अगर (size)
		*size = ((val & DESC_SIZE_MASK) + 1) * 16;

	this_cpu_inc(qh->stats->pops);
	वापस dma;
पूर्ण
EXPORT_SYMBOL_GPL(knav_queue_pop);

/* carve out descriptors and push पूर्णांकo queue */
अटल व्योम kdesc_fill_pool(काष्ठा knav_pool *pool)
अणु
	काष्ठा knav_region *region;
	पूर्णांक i;

	region = pool->region;
	pool->desc_size = region->desc_size;
	क्रम (i = 0; i < pool->num_desc; i++) अणु
		पूर्णांक index = pool->region_offset + i;
		dma_addr_t dma_addr;
		अचिन्हित dma_size;
		dma_addr = region->dma_start + (region->desc_size * index);
		dma_size = ALIGN(pool->desc_size, SMP_CACHE_BYTES);
		dma_sync_single_क्रम_device(pool->dev, dma_addr, dma_size,
					   DMA_TO_DEVICE);
		knav_queue_push(pool->queue, dma_addr, dma_size, 0);
	पूर्ण
पूर्ण

/* pop out descriptors and बंद the queue */
अटल व्योम kdesc_empty_pool(काष्ठा knav_pool *pool)
अणु
	dma_addr_t dma;
	अचिन्हित size;
	व्योम *desc;
	पूर्णांक i;

	अगर (!pool->queue)
		वापस;

	क्रम (i = 0;; i++) अणु
		dma = knav_queue_pop(pool->queue, &size);
		अगर (!dma)
			अवरोध;
		desc = knav_pool_desc_dma_to_virt(pool, dma);
		अगर (!desc) अणु
			dev_dbg(pool->kdev->dev,
				"couldn't unmap desc, continuing\n");
			जारी;
		पूर्ण
	पूर्ण
	WARN_ON(i != pool->num_desc);
	knav_queue_बंद(pool->queue);
पूर्ण


/* Get the DMA address of a descriptor */
dma_addr_t knav_pool_desc_virt_to_dma(व्योम *ph, व्योम *virt)
अणु
	काष्ठा knav_pool *pool = ph;
	वापस pool->region->dma_start + (virt - pool->region->virt_start);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_virt_to_dma);

व्योम *knav_pool_desc_dma_to_virt(व्योम *ph, dma_addr_t dma)
अणु
	काष्ठा knav_pool *pool = ph;
	वापस pool->region->virt_start + (dma - pool->region->dma_start);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_dma_to_virt);

/**
 * knav_pool_create()	- Create a pool of descriptors
 * @name:		- name to give the pool handle
 * @num_desc:		- numbers of descriptors in the pool
 * @region_id:		- QMSS region id from which the descriptors are to be
 *			  allocated.
 *
 * Returns a pool handle on success.
 * Use IS_ERR_OR_शून्य() to identअगरy error values on वापस.
 */
व्योम *knav_pool_create(स्थिर अक्षर *name,
					पूर्णांक num_desc, पूर्णांक region_id)
अणु
	काष्ठा knav_region *reg_itr, *region = शून्य;
	काष्ठा knav_pool *pool, *pi;
	काष्ठा list_head *node;
	अचिन्हित last_offset;
	bool slot_found;
	पूर्णांक ret;

	अगर (!kdev)
		वापस ERR_PTR(-EPROBE_DEFER);

	अगर (!kdev->dev)
		वापस ERR_PTR(-ENODEV);

	pool = devm_kzalloc(kdev->dev, माप(*pool), GFP_KERNEL);
	अगर (!pool) अणु
		dev_err(kdev->dev, "out of memory allocating pool\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम_each_region(kdev, reg_itr) अणु
		अगर (reg_itr->id != region_id)
			जारी;
		region = reg_itr;
		अवरोध;
	पूर्ण

	अगर (!region) अणु
		dev_err(kdev->dev, "region-id(%d) not found\n", region_id);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	pool->queue = knav_queue_खोलो(name, KNAV_QUEUE_GP, 0);
	अगर (IS_ERR_OR_शून्य(pool->queue)) अणु
		dev_err(kdev->dev,
			"failed to open queue for pool(%s), error %ld\n",
			name, PTR_ERR(pool->queue));
		ret = PTR_ERR(pool->queue);
		जाओ err;
	पूर्ण

	pool->name = kstrndup(name, KNAV_NAME_SIZE - 1, GFP_KERNEL);
	pool->kdev = kdev;
	pool->dev = kdev->dev;

	mutex_lock(&knav_dev_lock);

	अगर (num_desc > (region->num_desc - region->used_desc)) अणु
		dev_err(kdev->dev, "out of descs in region(%d) for pool(%s)\n",
			region_id, name);
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	/* Region मुख्यtains a sorted (by region offset) list of pools
	 * use the first मुक्त slot which is large enough to accomodate
	 * the request
	 */
	last_offset = 0;
	slot_found = false;
	node = &region->pools;
	list_क्रम_each_entry(pi, &region->pools, region_inst) अणु
		अगर ((pi->region_offset - last_offset) >= num_desc) अणु
			slot_found = true;
			अवरोध;
		पूर्ण
		last_offset = pi->region_offset + pi->num_desc;
	पूर्ण
	node = &pi->region_inst;

	अगर (slot_found) अणु
		pool->region = region;
		pool->num_desc = num_desc;
		pool->region_offset = last_offset;
		region->used_desc += num_desc;
		list_add_tail(&pool->list, &kdev->pools);
		list_add_tail(&pool->region_inst, node);
	पूर्ण अन्यथा अणु
		dev_err(kdev->dev, "pool(%s) create failed: fragmented desc pool in region(%d)\n",
			name, region_id);
		ret = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	mutex_unlock(&knav_dev_lock);
	kdesc_fill_pool(pool);
	वापस pool;

err_unlock:
	mutex_unlock(&knav_dev_lock);
err:
	kमुक्त(pool->name);
	devm_kमुक्त(kdev->dev, pool);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_create);

/**
 * knav_pool_destroy()	- Free a pool of descriptors
 * @ph:		- pool handle
 */
व्योम knav_pool_destroy(व्योम *ph)
अणु
	काष्ठा knav_pool *pool = ph;

	अगर (!pool)
		वापस;

	अगर (!pool->region)
		वापस;

	kdesc_empty_pool(pool);
	mutex_lock(&knav_dev_lock);

	pool->region->used_desc -= pool->num_desc;
	list_del(&pool->region_inst);
	list_del(&pool->list);

	mutex_unlock(&knav_dev_lock);
	kमुक्त(pool->name);
	devm_kमुक्त(kdev->dev, pool);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_destroy);


/**
 * knav_pool_desc_get()	- Get a descriptor from the pool
 * @ph:		- pool handle
 *
 * Returns descriptor from the pool.
 */
व्योम *knav_pool_desc_get(व्योम *ph)
अणु
	काष्ठा knav_pool *pool = ph;
	dma_addr_t dma;
	अचिन्हित size;
	व्योम *data;

	dma = knav_queue_pop(pool->queue, &size);
	अगर (unlikely(!dma))
		वापस ERR_PTR(-ENOMEM);
	data = knav_pool_desc_dma_to_virt(pool, dma);
	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_get);

/**
 * knav_pool_desc_put()	- वापस a descriptor to the pool
 * @ph:		- pool handle
 * @desc:	- भव address
 */
व्योम knav_pool_desc_put(व्योम *ph, व्योम *desc)
अणु
	काष्ठा knav_pool *pool = ph;
	dma_addr_t dma;
	dma = knav_pool_desc_virt_to_dma(pool, desc);
	knav_queue_push(pool->queue, dma, pool->region->desc_size, 0);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_put);

/**
 * knav_pool_desc_map()	- Map descriptor क्रम DMA transfer
 * @ph:				- pool handle
 * @desc:			- address of descriptor to map
 * @size:			- size of descriptor to map
 * @dma:			- DMA address वापस poपूर्णांकer
 * @dma_sz:			- adjusted वापस poपूर्णांकer
 *
 * Returns 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक knav_pool_desc_map(व्योम *ph, व्योम *desc, अचिन्हित size,
					dma_addr_t *dma, अचिन्हित *dma_sz)
अणु
	काष्ठा knav_pool *pool = ph;
	*dma = knav_pool_desc_virt_to_dma(pool, desc);
	size = min(size, pool->region->desc_size);
	size = ALIGN(size, SMP_CACHE_BYTES);
	*dma_sz = size;
	dma_sync_single_क्रम_device(pool->dev, *dma, size, DMA_TO_DEVICE);

	/* Ensure the descriptor reaches to the memory */
	__iowmb();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_map);

/**
 * knav_pool_desc_unmap()	- Unmap descriptor after DMA transfer
 * @ph:				- pool handle
 * @dma:			- DMA address of descriptor to unmap
 * @dma_sz:			- size of descriptor to unmap
 *
 * Returns descriptor address on success, Use IS_ERR_OR_शून्य() to identअगरy
 * error values on वापस.
 */
व्योम *knav_pool_desc_unmap(व्योम *ph, dma_addr_t dma, अचिन्हित dma_sz)
अणु
	काष्ठा knav_pool *pool = ph;
	अचिन्हित desc_sz;
	व्योम *desc;

	desc_sz = min(dma_sz, pool->region->desc_size);
	desc = knav_pool_desc_dma_to_virt(pool, dma);
	dma_sync_single_क्रम_cpu(pool->dev, dma, desc_sz, DMA_FROM_DEVICE);
	prefetch(desc);
	वापस desc;
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_desc_unmap);

/**
 * knav_pool_count()	- Get the number of descriptors in pool.
 * @ph:			- pool handle
 * Returns number of elements in the pool.
 */
पूर्णांक knav_pool_count(व्योम *ph)
अणु
	काष्ठा knav_pool *pool = ph;
	वापस knav_queue_get_count(pool->queue);
पूर्ण
EXPORT_SYMBOL_GPL(knav_pool_count);

अटल व्योम knav_queue_setup_region(काष्ठा knav_device *kdev,
					काष्ठा knav_region *region)
अणु
	अचिन्हित hw_num_desc, hw_desc_size, size;
	काष्ठा knav_reg_region __iomem  *regs;
	काष्ठा knav_qmgr_info *qmgr;
	काष्ठा knav_pool *pool;
	पूर्णांक id = region->id;
	काष्ठा page *page;

	/* unused region? */
	अगर (!region->num_desc) अणु
		dev_warn(kdev->dev, "unused region %s\n", region->name);
		वापस;
	पूर्ण

	/* get hardware descriptor value */
	hw_num_desc = ilog2(region->num_desc - 1) + 1;

	/* did we क्रमce fit ourselves पूर्णांकo nothingness? */
	अगर (region->num_desc < 32) अणु
		region->num_desc = 0;
		dev_warn(kdev->dev, "too few descriptors in region %s\n",
			 region->name);
		वापस;
	पूर्ण

	size = region->num_desc * region->desc_size;
	region->virt_start = alloc_pages_exact(size, GFP_KERNEL | GFP_DMA |
						GFP_DMA32);
	अगर (!region->virt_start) अणु
		region->num_desc = 0;
		dev_err(kdev->dev, "memory alloc failed for region %s\n",
			region->name);
		वापस;
	पूर्ण
	region->virt_end = region->virt_start + size;
	page = virt_to_page(region->virt_start);

	region->dma_start = dma_map_page(kdev->dev, page, 0, size,
					 DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(kdev->dev, region->dma_start)) अणु
		dev_err(kdev->dev, "dma map failed for region %s\n",
			region->name);
		जाओ fail;
	पूर्ण
	region->dma_end = region->dma_start + size;

	pool = devm_kzalloc(kdev->dev, माप(*pool), GFP_KERNEL);
	अगर (!pool) अणु
		dev_err(kdev->dev, "out of memory allocating dummy pool\n");
		जाओ fail;
	पूर्ण
	pool->num_desc = 0;
	pool->region_offset = region->num_desc;
	list_add(&pool->region_inst, &region->pools);

	dev_dbg(kdev->dev,
		"region %s (%d): size:%d, link:%d@%d, dma:%pad-%pad, virt:%p-%p\n",
		region->name, id, region->desc_size, region->num_desc,
		region->link_index, &region->dma_start, &region->dma_end,
		region->virt_start, region->virt_end);

	hw_desc_size = (region->desc_size / 16) - 1;
	hw_num_desc -= 5;

	क्रम_each_qmgr(kdev, qmgr) अणु
		regs = qmgr->reg_region + id;
		ग_लिखोl_relaxed((u32)region->dma_start, &regs->base);
		ग_लिखोl_relaxed(region->link_index, &regs->start_index);
		ग_लिखोl_relaxed(hw_desc_size << 16 | hw_num_desc,
			       &regs->size_count);
	पूर्ण
	वापस;

fail:
	अगर (region->dma_start)
		dma_unmap_page(kdev->dev, region->dma_start, size,
				DMA_BIसूचीECTIONAL);
	अगर (region->virt_start)
		मुक्त_pages_exact(region->virt_start, size);
	region->num_desc = 0;
	वापस;
पूर्ण

अटल स्थिर अक्षर *knav_queue_find_name(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *name;

	अगर (of_property_पढ़ो_string(node, "label", &name) < 0)
		name = node->name;
	अगर (!name)
		name = "unknown";
	वापस name;
पूर्ण

अटल पूर्णांक knav_queue_setup_regions(काष्ठा knav_device *kdev,
					काष्ठा device_node *regions)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा knav_region *region;
	काष्ठा device_node *child;
	u32 temp[2];
	पूर्णांक ret;

	क्रम_each_child_of_node(regions, child) अणु
		region = devm_kzalloc(dev, माप(*region), GFP_KERNEL);
		अगर (!region) अणु
			of_node_put(child);
			dev_err(dev, "out of memory allocating region\n");
			वापस -ENOMEM;
		पूर्ण

		region->name = knav_queue_find_name(child);
		of_property_पढ़ो_u32(child, "id", &region->id);
		ret = of_property_पढ़ो_u32_array(child, "region-spec", temp, 2);
		अगर (!ret) अणु
			region->num_desc  = temp[0];
			region->desc_size = temp[1];
		पूर्ण अन्यथा अणु
			dev_err(dev, "invalid region info %s\n", region->name);
			devm_kमुक्त(dev, region);
			जारी;
		पूर्ण

		अगर (!of_get_property(child, "link-index", शून्य)) अणु
			dev_err(dev, "No link info for %s\n", region->name);
			devm_kमुक्त(dev, region);
			जारी;
		पूर्ण
		ret = of_property_पढ़ो_u32(child, "link-index",
					   &region->link_index);
		अगर (ret) अणु
			dev_err(dev, "link index not found for %s\n",
				region->name);
			devm_kमुक्त(dev, region);
			जारी;
		पूर्ण

		INIT_LIST_HEAD(&region->pools);
		list_add_tail(&region->list, &kdev->regions);
	पूर्ण
	अगर (list_empty(&kdev->regions)) अणु
		dev_err(dev, "no valid region information found\n");
		वापस -ENODEV;
	पूर्ण

	/* Next, we run through the regions and set things up */
	क्रम_each_region(kdev, region)
		knav_queue_setup_region(kdev, region);

	वापस 0;
पूर्ण

अटल पूर्णांक knav_get_link_ram(काष्ठा knav_device *kdev,
				       स्थिर अक्षर *name,
				       काष्ठा knav_link_ram_block *block)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(kdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	u32 temp[2];

	/*
	 * Note: link ram resources are specअगरied in "entry" sized units. In
	 * reality, although entries are ~40bits in hardware, we treat them as
	 * 64-bit entities here.
	 *
	 * For example, to specअगरy the पूर्णांकernal link ram क्रम Keystone-I class
	 * devices, we would set the linkram0 resource to 0x80000-0x83fff.
	 *
	 * This माला_लो a bit weird when other link rams are used.  For example,
	 * अगर the range specअगरied is 0x0c000000-0x0c003fff (i.e., 16K entries
	 * in MSMC SRAM), the actual memory used is 0x0c000000-0x0c020000,
	 * which accounts क्रम 64-bits per entry, क्रम 16K entries.
	 */
	अगर (!of_property_पढ़ो_u32_array(node, name , temp, 2)) अणु
		अगर (temp[0]) अणु
			/*
			 * queue_base specअगरied => using पूर्णांकernal or onchip
			 * link ram WARNING - we करो not "reserve" this block
			 */
			block->dma = (dma_addr_t)temp[0];
			block->virt = शून्य;
			block->size = temp[1];
		पूर्ण अन्यथा अणु
			block->size = temp[1];
			/* queue_base not specअगरic => allocate requested size */
			block->virt = dmam_alloc_coherent(kdev->dev,
						  8 * block->size, &block->dma,
						  GFP_KERNEL);
			अगर (!block->virt) अणु
				dev_err(kdev->dev, "failed to alloc linkram\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_setup_link_ram(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_link_ram_block *block;
	काष्ठा knav_qmgr_info *qmgr;

	क्रम_each_qmgr(kdev, qmgr) अणु
		block = &kdev->link_rams[0];
		dev_dbg(kdev->dev, "linkram0: dma:%pad, virt:%p, size:%x\n",
			&block->dma, block->virt, block->size);
		ग_लिखोl_relaxed((u32)block->dma, &qmgr->reg_config->link_ram_base0);
		अगर (kdev->version == QMSS_66AK2G)
			ग_लिखोl_relaxed(block->size,
				       &qmgr->reg_config->link_ram_size0);
		अन्यथा
			ग_लिखोl_relaxed(block->size - 1,
				       &qmgr->reg_config->link_ram_size0);
		block++;
		अगर (!block->size)
			जारी;

		dev_dbg(kdev->dev, "linkram1: dma:%pad, virt:%p, size:%x\n",
			&block->dma, block->virt, block->size);
		ग_लिखोl_relaxed(block->dma, &qmgr->reg_config->link_ram_base1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक knav_setup_queue_range(काष्ठा knav_device *kdev,
					काष्ठा device_node *node)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा knav_range_info *range;
	काष्ठा knav_qmgr_info *qmgr;
	u32 temp[2], start, end, id, index;
	पूर्णांक ret, i;

	range = devm_kzalloc(dev, माप(*range), GFP_KERNEL);
	अगर (!range) अणु
		dev_err(dev, "out of memory allocating range\n");
		वापस -ENOMEM;
	पूर्ण

	range->kdev = kdev;
	range->name = knav_queue_find_name(node);
	ret = of_property_पढ़ो_u32_array(node, "qrange", temp, 2);
	अगर (!ret) अणु
		range->queue_base = temp[0] - kdev->base_id;
		range->num_queues = temp[1];
	पूर्ण अन्यथा अणु
		dev_err(dev, "invalid queue range %s\n", range->name);
		devm_kमुक्त(dev, range);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < RANGE_MAX_IRQS; i++) अणु
		काष्ठा of_phandle_args oirq;

		अगर (of_irq_parse_one(node, i, &oirq))
			अवरोध;

		range->irqs[i].irq = irq_create_of_mapping(&oirq);
		अगर (range->irqs[i].irq == IRQ_NONE)
			अवरोध;

		range->num_irqs++;

		अगर (IS_ENABLED(CONFIG_SMP) && oirq.args_count == 3) अणु
			अचिन्हित दीर्घ mask;
			पूर्णांक bit;

			range->irqs[i].cpu_mask = devm_kzalloc(dev,
							       cpumask_size(), GFP_KERNEL);
			अगर (!range->irqs[i].cpu_mask)
				वापस -ENOMEM;

			mask = (oirq.args[2] & 0x0000ff00) >> 8;
			क्रम_each_set_bit(bit, &mask, BITS_PER_LONG)
				cpumask_set_cpu(bit, range->irqs[i].cpu_mask);
		पूर्ण
	पूर्ण

	range->num_irqs = min(range->num_irqs, range->num_queues);
	अगर (range->num_irqs)
		range->flags |= RANGE_HAS_IRQ;

	अगर (of_get_property(node, "qalloc-by-id", शून्य))
		range->flags |= RANGE_RESERVED;

	अगर (of_get_property(node, "accumulator", शून्य)) अणु
		ret = knav_init_acc_range(kdev, node, range);
		अगर (ret < 0) अणु
			devm_kमुक्त(dev, range);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		range->ops = &knav_gp_range_ops;
	पूर्ण

	/* set threshold to 1, and flush out the queues */
	क्रम_each_qmgr(kdev, qmgr) अणु
		start = max(qmgr->start_queue, range->queue_base);
		end   = min(qmgr->start_queue + qmgr->num_queues,
			    range->queue_base + range->num_queues);
		क्रम (id = start; id < end; id++) अणु
			index = id - qmgr->start_queue;
			ग_लिखोl_relaxed(THRESH_GTE | 1,
				       &qmgr->reg_peek[index].ptr_माप_प्रकारhresh);
			ग_लिखोl_relaxed(0,
				       &qmgr->reg_push[index].ptr_माप_प्रकारhresh);
		पूर्ण
	पूर्ण

	list_add_tail(&range->list, &kdev->queue_ranges);
	dev_dbg(dev, "added range %s: %d-%d, %d irqs%s%s%s\n",
		range->name, range->queue_base,
		range->queue_base + range->num_queues - 1,
		range->num_irqs,
		(range->flags & RANGE_HAS_IRQ) ? ", has irq" : "",
		(range->flags & RANGE_RESERVED) ? ", reserved" : "",
		(range->flags & RANGE_HAS_ACCUMULATOR) ? ", acc" : "");
	kdev->num_queues_in_use += range->num_queues;
	वापस 0;
पूर्ण

अटल पूर्णांक knav_setup_queue_pools(काष्ठा knav_device *kdev,
				   काष्ठा device_node *queue_pools)
अणु
	काष्ठा device_node *type, *range;

	क्रम_each_child_of_node(queue_pools, type) अणु
		क्रम_each_child_of_node(type, range) अणु
			/* वापस value ignored, we init the rest... */
			knav_setup_queue_range(kdev, range);
		पूर्ण
	पूर्ण

	/* ... and barf अगर they all failed! */
	अगर (list_empty(&kdev->queue_ranges)) अणु
		dev_err(kdev->dev, "no valid queue range found\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम knav_मुक्त_queue_range(काष्ठा knav_device *kdev,
				  काष्ठा knav_range_info *range)
अणु
	अगर (range->ops && range->ops->मुक्त_range)
		range->ops->मुक्त_range(range);
	list_del(&range->list);
	devm_kमुक्त(kdev->dev, range);
पूर्ण

अटल व्योम knav_मुक्त_queue_ranges(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_range_info *range;

	क्रम (;;) अणु
		range = first_queue_range(kdev);
		अगर (!range)
			अवरोध;
		knav_मुक्त_queue_range(kdev, range);
	पूर्ण
पूर्ण

अटल व्योम knav_queue_मुक्त_regions(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_region *region;
	काष्ठा knav_pool *pool, *पंचांगp;
	अचिन्हित size;

	क्रम (;;) अणु
		region = first_region(kdev);
		अगर (!region)
			अवरोध;
		list_क्रम_each_entry_safe(pool, पंचांगp, &region->pools, region_inst)
			knav_pool_destroy(pool);

		size = region->virt_end - region->virt_start;
		अगर (size)
			मुक्त_pages_exact(region->virt_start, size);
		list_del(&region->list);
		devm_kमुक्त(kdev->dev, region);
	पूर्ण
पूर्ण

अटल व्योम __iomem *knav_queue_map_reg(काष्ठा knav_device *kdev,
					काष्ठा device_node *node, पूर्णांक index)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	ret = of_address_to_resource(node, index, &res);
	अगर (ret) अणु
		dev_err(kdev->dev, "Can't translate of node(%pOFn) address for index(%d)\n",
			node, index);
		वापस ERR_PTR(ret);
	पूर्ण

	regs = devm_ioremap_resource(kdev->dev, &res);
	अगर (IS_ERR(regs))
		dev_err(kdev->dev, "Failed to map register base for index(%d) node(%pOFn)\n",
			index, node);
	वापस regs;
पूर्ण

अटल पूर्णांक knav_queue_init_qmgrs(काष्ठा knav_device *kdev,
					काष्ठा device_node *qmgrs)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा knav_qmgr_info *qmgr;
	काष्ठा device_node *child;
	u32 temp[2];
	पूर्णांक ret;

	क्रम_each_child_of_node(qmgrs, child) अणु
		qmgr = devm_kzalloc(dev, माप(*qmgr), GFP_KERNEL);
		अगर (!qmgr) अणु
			of_node_put(child);
			dev_err(dev, "out of memory allocating qmgr\n");
			वापस -ENOMEM;
		पूर्ण

		ret = of_property_पढ़ो_u32_array(child, "managed-queues",
						 temp, 2);
		अगर (!ret) अणु
			qmgr->start_queue = temp[0];
			qmgr->num_queues = temp[1];
		पूर्ण अन्यथा अणु
			dev_err(dev, "invalid qmgr queue range\n");
			devm_kमुक्त(dev, qmgr);
			जारी;
		पूर्ण

		dev_info(dev, "qmgr start queue %d, number of queues %d\n",
			 qmgr->start_queue, qmgr->num_queues);

		qmgr->reg_peek =
			knav_queue_map_reg(kdev, child,
					   KNAV_QUEUE_PEEK_REG_INDEX);

		अगर (kdev->version == QMSS) अणु
			qmgr->reg_status =
				knav_queue_map_reg(kdev, child,
						   KNAV_QUEUE_STATUS_REG_INDEX);
		पूर्ण

		qmgr->reg_config =
			knav_queue_map_reg(kdev, child,
					   (kdev->version == QMSS_66AK2G) ?
					   KNAV_L_QUEUE_CONFIG_REG_INDEX :
					   KNAV_QUEUE_CONFIG_REG_INDEX);
		qmgr->reg_region =
			knav_queue_map_reg(kdev, child,
					   (kdev->version == QMSS_66AK2G) ?
					   KNAV_L_QUEUE_REGION_REG_INDEX :
					   KNAV_QUEUE_REGION_REG_INDEX);

		qmgr->reg_push =
			knav_queue_map_reg(kdev, child,
					   (kdev->version == QMSS_66AK2G) ?
					    KNAV_L_QUEUE_PUSH_REG_INDEX :
					    KNAV_QUEUE_PUSH_REG_INDEX);

		अगर (kdev->version == QMSS) अणु
			qmgr->reg_pop =
				knav_queue_map_reg(kdev, child,
						   KNAV_QUEUE_POP_REG_INDEX);
		पूर्ण

		अगर (IS_ERR(qmgr->reg_peek) ||
		    ((kdev->version == QMSS) &&
		    (IS_ERR(qmgr->reg_status) || IS_ERR(qmgr->reg_pop))) ||
		    IS_ERR(qmgr->reg_config) || IS_ERR(qmgr->reg_region) ||
		    IS_ERR(qmgr->reg_push)) अणु
			dev_err(dev, "failed to map qmgr regs\n");
			अगर (kdev->version == QMSS) अणु
				अगर (!IS_ERR(qmgr->reg_status))
					devm_iounmap(dev, qmgr->reg_status);
				अगर (!IS_ERR(qmgr->reg_pop))
					devm_iounmap(dev, qmgr->reg_pop);
			पूर्ण
			अगर (!IS_ERR(qmgr->reg_peek))
				devm_iounmap(dev, qmgr->reg_peek);
			अगर (!IS_ERR(qmgr->reg_config))
				devm_iounmap(dev, qmgr->reg_config);
			अगर (!IS_ERR(qmgr->reg_region))
				devm_iounmap(dev, qmgr->reg_region);
			अगर (!IS_ERR(qmgr->reg_push))
				devm_iounmap(dev, qmgr->reg_push);
			devm_kमुक्त(dev, qmgr);
			जारी;
		पूर्ण

		/* Use same push रेजिस्टर क्रम pop as well */
		अगर (kdev->version == QMSS_66AK2G)
			qmgr->reg_pop = qmgr->reg_push;

		list_add_tail(&qmgr->list, &kdev->qmgrs);
		dev_info(dev, "added qmgr start queue %d, num of queues %d, reg_peek %p, reg_status %p, reg_config %p, reg_region %p, reg_push %p, reg_pop %p\n",
			 qmgr->start_queue, qmgr->num_queues,
			 qmgr->reg_peek, qmgr->reg_status,
			 qmgr->reg_config, qmgr->reg_region,
			 qmgr->reg_push, qmgr->reg_pop);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_init_pdsps(काष्ठा knav_device *kdev,
					काष्ठा device_node *pdsps)
अणु
	काष्ठा device *dev = kdev->dev;
	काष्ठा knav_pdsp_info *pdsp;
	काष्ठा device_node *child;

	क्रम_each_child_of_node(pdsps, child) अणु
		pdsp = devm_kzalloc(dev, माप(*pdsp), GFP_KERNEL);
		अगर (!pdsp) अणु
			of_node_put(child);
			dev_err(dev, "out of memory allocating pdsp\n");
			वापस -ENOMEM;
		पूर्ण
		pdsp->name = knav_queue_find_name(child);
		pdsp->iram =
			knav_queue_map_reg(kdev, child,
					   KNAV_QUEUE_PDSP_IRAM_REG_INDEX);
		pdsp->regs =
			knav_queue_map_reg(kdev, child,
					   KNAV_QUEUE_PDSP_REGS_REG_INDEX);
		pdsp->पूर्णांकd =
			knav_queue_map_reg(kdev, child,
					   KNAV_QUEUE_PDSP_INTD_REG_INDEX);
		pdsp->command =
			knav_queue_map_reg(kdev, child,
					   KNAV_QUEUE_PDSP_CMD_REG_INDEX);

		अगर (IS_ERR(pdsp->command) || IS_ERR(pdsp->iram) ||
		    IS_ERR(pdsp->regs) || IS_ERR(pdsp->पूर्णांकd)) अणु
			dev_err(dev, "failed to map pdsp %s regs\n",
				pdsp->name);
			अगर (!IS_ERR(pdsp->command))
				devm_iounmap(dev, pdsp->command);
			अगर (!IS_ERR(pdsp->iram))
				devm_iounmap(dev, pdsp->iram);
			अगर (!IS_ERR(pdsp->regs))
				devm_iounmap(dev, pdsp->regs);
			अगर (!IS_ERR(pdsp->पूर्णांकd))
				devm_iounmap(dev, pdsp->पूर्णांकd);
			devm_kमुक्त(dev, pdsp);
			जारी;
		पूर्ण
		of_property_पढ़ो_u32(child, "id", &pdsp->id);
		list_add_tail(&pdsp->list, &kdev->pdsps);
		dev_dbg(dev, "added pdsp %s: command %p, iram %p, regs %p, intd %p\n",
			pdsp->name, pdsp->command, pdsp->iram, pdsp->regs,
			pdsp->पूर्णांकd);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_stop_pdsp(काष्ठा knav_device *kdev,
			  काष्ठा knav_pdsp_info *pdsp)
अणु
	u32 val, समयout = 1000;
	पूर्णांक ret;

	val = पढ़ोl_relaxed(&pdsp->regs->control) & ~PDSP_CTRL_ENABLE;
	ग_लिखोl_relaxed(val, &pdsp->regs->control);
	ret = knav_queue_pdsp_रुको(&pdsp->regs->control, समयout,
					PDSP_CTRL_RUNNING);
	अगर (ret < 0) अणु
		dev_err(kdev->dev, "timed out on pdsp %s stop\n", pdsp->name);
		वापस ret;
	पूर्ण
	pdsp->loaded = false;
	pdsp->started = false;
	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_load_pdsp(काष्ठा knav_device *kdev,
			  काष्ठा knav_pdsp_info *pdsp)
अणु
	पूर्णांक i, ret, fwlen;
	स्थिर काष्ठा firmware *fw;
	bool found = false;
	u32 *fwdata;

	क्रम (i = 0; i < ARRAY_SIZE(knav_acc_firmwares); i++) अणु
		अगर (knav_acc_firmwares[i]) अणु
			ret = request_firmware_direct(&fw,
						      knav_acc_firmwares[i],
						      kdev->dev);
			अगर (!ret) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dev_err(kdev->dev, "failed to get firmware for pdsp\n");
		वापस -ENODEV;
	पूर्ण

	dev_info(kdev->dev, "firmware file %s downloaded for PDSP\n",
		 knav_acc_firmwares[i]);

	ग_लिखोl_relaxed(pdsp->id + 1, pdsp->command + 0x18);
	/* करोwnload the firmware */
	fwdata = (u32 *)fw->data;
	fwlen = (fw->size + माप(u32) - 1) / माप(u32);
	क्रम (i = 0; i < fwlen; i++)
		ग_लिखोl_relaxed(be32_to_cpu(fwdata[i]), pdsp->iram + i);

	release_firmware(fw);
	वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_start_pdsp(काष्ठा knav_device *kdev,
			   काष्ठा knav_pdsp_info *pdsp)
अणु
	u32 val, समयout = 1000;
	पूर्णांक ret;

	/* ग_लिखो a command क्रम sync */
	ग_लिखोl_relaxed(0xffffffff, pdsp->command);
	जबतक (पढ़ोl_relaxed(pdsp->command) != 0xffffffff)
		cpu_relax();

	/* soft reset the PDSP */
	val  = पढ़ोl_relaxed(&pdsp->regs->control);
	val &= ~(PDSP_CTRL_PC_MASK | PDSP_CTRL_SOFT_RESET);
	ग_लिखोl_relaxed(val, &pdsp->regs->control);

	/* enable pdsp */
	val = पढ़ोl_relaxed(&pdsp->regs->control) | PDSP_CTRL_ENABLE;
	ग_लिखोl_relaxed(val, &pdsp->regs->control);

	/* रुको क्रम command रेजिस्टर to clear */
	ret = knav_queue_pdsp_रुको(pdsp->command, समयout, 0);
	अगर (ret < 0) अणु
		dev_err(kdev->dev,
			"timed out on pdsp %s command register wait\n",
			pdsp->name);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम knav_queue_stop_pdsps(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_pdsp_info *pdsp;

	/* disable all pdsps */
	क्रम_each_pdsp(kdev, pdsp)
		knav_queue_stop_pdsp(kdev, pdsp);
पूर्ण

अटल पूर्णांक knav_queue_start_pdsps(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_pdsp_info *pdsp;
	पूर्णांक ret;

	knav_queue_stop_pdsps(kdev);
	/* now load them all. We वापस success even अगर pdsp
	 * is not loaded as acc channels are optional on having
	 * firmware availability in the प्रणाली. We set the loaded
	 * and stated flag and when initialize the acc range, check
	 * it and init the range only अगर pdsp is started.
	 */
	क्रम_each_pdsp(kdev, pdsp) अणु
		ret = knav_queue_load_pdsp(kdev, pdsp);
		अगर (!ret)
			pdsp->loaded = true;
	पूर्ण

	क्रम_each_pdsp(kdev, pdsp) अणु
		अगर (pdsp->loaded) अणु
			ret = knav_queue_start_pdsp(kdev, pdsp);
			अगर (!ret)
				pdsp->started = true;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा knav_qmgr_info *knav_find_qmgr(अचिन्हित id)
अणु
	काष्ठा knav_qmgr_info *qmgr;

	क्रम_each_qmgr(kdev, qmgr) अणु
		अगर ((id >= qmgr->start_queue) &&
		    (id < qmgr->start_queue + qmgr->num_queues))
			वापस qmgr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक knav_queue_init_queue(काष्ठा knav_device *kdev,
					काष्ठा knav_range_info *range,
					काष्ठा knav_queue_inst *inst,
					अचिन्हित id)
अणु
	अक्षर irq_name[KNAV_NAME_SIZE];
	inst->qmgr = knav_find_qmgr(id);
	अगर (!inst->qmgr)
		वापस -1;

	INIT_LIST_HEAD(&inst->handles);
	inst->kdev = kdev;
	inst->range = range;
	inst->irq_num = -1;
	inst->id = id;
	scnम_लिखो(irq_name, माप(irq_name), "hwqueue-%d", id);
	inst->irq_name = kstrndup(irq_name, माप(irq_name), GFP_KERNEL);

	अगर (range->ops && range->ops->init_queue)
		वापस range->ops->init_queue(range, inst);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक knav_queue_init_queues(काष्ठा knav_device *kdev)
अणु
	काष्ठा knav_range_info *range;
	पूर्णांक size, id, base_idx;
	पूर्णांक idx = 0, ret = 0;

	/* how much करो we need क्रम instance data? */
	size = माप(काष्ठा knav_queue_inst);

	/* round this up to a घातer of 2, keep the index to instance
	 * arithmetic fast.
	 * */
	kdev->inst_shअगरt = order_base_2(size);
	size = (1 << kdev->inst_shअगरt) * kdev->num_queues_in_use;
	kdev->instances = devm_kzalloc(kdev->dev, size, GFP_KERNEL);
	अगर (!kdev->instances)
		वापस -ENOMEM;

	क्रम_each_queue_range(kdev, range) अणु
		अगर (range->ops && range->ops->init_range)
			range->ops->init_range(range);
		base_idx = idx;
		क्रम (id = range->queue_base;
		     id < range->queue_base + range->num_queues; id++, idx++) अणु
			ret = knav_queue_init_queue(kdev, range,
					knav_queue_idx_to_inst(kdev, idx), id);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		range->queue_base_inst =
			knav_queue_idx_to_inst(kdev, base_idx);
	पूर्ण
	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id keystone_qmss_of_match[] = अणु
	अणु
		.compatible = "ti,keystone-navigator-qmss",
	पूर्ण,
	अणु
		.compatible = "ti,66ak2g-navss-qm",
		.data	= (व्योम *)QMSS_66AK2G,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, keystone_qmss_of_match);

अटल पूर्णांक knav_queue_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *qmgrs, *queue_pools, *regions, *pdsps;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	u32 temp[2];
	पूर्णांक ret;

	अगर (!node) अणु
		dev_err(dev, "device tree info unavailable\n");
		वापस -ENODEV;
	पूर्ण

	kdev = devm_kzalloc(dev, माप(काष्ठा knav_device), GFP_KERNEL);
	अगर (!kdev) अणु
		dev_err(dev, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	match = of_match_device(of_match_ptr(keystone_qmss_of_match), dev);
	अगर (match && match->data)
		kdev->version = QMSS_66AK2G;

	platक्रमm_set_drvdata(pdev, kdev);
	kdev->dev = dev;
	INIT_LIST_HEAD(&kdev->queue_ranges);
	INIT_LIST_HEAD(&kdev->qmgrs);
	INIT_LIST_HEAD(&kdev->pools);
	INIT_LIST_HEAD(&kdev->regions);
	INIT_LIST_HEAD(&kdev->pdsps);

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		dev_err(dev, "Failed to enable QMSS\n");
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(node, "queue-range", temp, 2)) अणु
		dev_err(dev, "queue-range not specified\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	kdev->base_id    = temp[0];
	kdev->num_queues = temp[1];

	/* Initialize queue managers using device tree configuration */
	qmgrs =  of_get_child_by_name(node, "qmgrs");
	अगर (!qmgrs) अणु
		dev_err(dev, "queue manager info not specified\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	ret = knav_queue_init_qmgrs(kdev, qmgrs);
	of_node_put(qmgrs);
	अगर (ret)
		जाओ err;

	/* get pdsp configuration values from device tree */
	pdsps =  of_get_child_by_name(node, "pdsps");
	अगर (pdsps) अणु
		ret = knav_queue_init_pdsps(kdev, pdsps);
		अगर (ret)
			जाओ err;

		ret = knav_queue_start_pdsps(kdev);
		अगर (ret)
			जाओ err;
	पूर्ण
	of_node_put(pdsps);

	/* get usable queue range values from device tree */
	queue_pools = of_get_child_by_name(node, "queue-pools");
	अगर (!queue_pools) अणु
		dev_err(dev, "queue-pools not specified\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	ret = knav_setup_queue_pools(kdev, queue_pools);
	of_node_put(queue_pools);
	अगर (ret)
		जाओ err;

	ret = knav_get_link_ram(kdev, "linkram0", &kdev->link_rams[0]);
	अगर (ret) अणु
		dev_err(kdev->dev, "could not setup linking ram\n");
		जाओ err;
	पूर्ण

	ret = knav_get_link_ram(kdev, "linkram1", &kdev->link_rams[1]);
	अगर (ret) अणु
		/*
		 * nothing really, we have one linking ram alपढ़ोy, so we just
		 * live within our means
		 */
	पूर्ण

	ret = knav_queue_setup_link_ram(kdev);
	अगर (ret)
		जाओ err;

	regions = of_get_child_by_name(node, "descriptor-regions");
	अगर (!regions) अणु
		dev_err(dev, "descriptor-regions not specified\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	ret = knav_queue_setup_regions(kdev, regions);
	of_node_put(regions);
	अगर (ret)
		जाओ err;

	ret = knav_queue_init_queues(kdev);
	अगर (ret < 0) अणु
		dev_err(dev, "hwqueue initialization failed\n");
		जाओ err;
	पूर्ण

	debugfs_create_file("qmss", S_IFREG | S_IRUGO, शून्य, शून्य,
			    &knav_queue_debug_fops);
	device_पढ़ोy = true;
	वापस 0;

err:
	knav_queue_stop_pdsps(kdev);
	knav_queue_मुक्त_regions(kdev);
	knav_मुक्त_queue_ranges(kdev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक knav_queue_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* TODO: Free resources */
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver keystone_qmss_driver = अणु
	.probe		= knav_queue_probe,
	.हटाओ		= knav_queue_हटाओ,
	.driver		= अणु
		.name	= "keystone-navigator-qmss",
		.of_match_table = keystone_qmss_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(keystone_qmss_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI QMSS driver for Keystone SOCs");
MODULE_AUTHOR("Sandeep Nair <sandeep_n@ti.com>");
MODULE_AUTHOR("Santosh Shilimkar <santosh.shilimkar@ti.com>");
