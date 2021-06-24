<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm:%s:%d] " fmt, __func__, __LINE__

#समावेश <linux/debugfs.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/kthपढ़ो.h>

#समावेश "dpu_core_irq.h"
#समावेश "dpu_trace.h"

/**
 * dpu_core_irq_callback_handler - dispatch core पूर्णांकerrupts
 * @arg:		निजी data of callback handler
 * @irq_idx:		पूर्णांकerrupt index
 */
अटल व्योम dpu_core_irq_callback_handler(व्योम *arg, पूर्णांक irq_idx)
अणु
	काष्ठा dpu_kms *dpu_kms = arg;
	काष्ठा dpu_irq *irq_obj = &dpu_kms->irq_obj;
	काष्ठा dpu_irq_callback *cb;
	अचिन्हित दीर्घ irq_flags;

	pr_debug("irq_idx=%d\n", irq_idx);

	अगर (list_empty(&irq_obj->irq_cb_tbl[irq_idx])) अणु
		DRM_ERROR("no registered cb, idx:%d enable_count:%d\n", irq_idx,
			atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idx]));
	पूर्ण

	atomic_inc(&irq_obj->irq_counts[irq_idx]);

	/*
	 * Perक्रमm रेजिस्टरed function callback
	 */
	spin_lock_irqsave(&dpu_kms->irq_obj.cb_lock, irq_flags);
	list_क्रम_each_entry(cb, &irq_obj->irq_cb_tbl[irq_idx], list)
		अगर (cb->func)
			cb->func(cb->arg, irq_idx);
	spin_unlock_irqrestore(&dpu_kms->irq_obj.cb_lock, irq_flags);

	/*
	 * Clear pending पूर्णांकerrupt status in HW.
	 * NOTE: dpu_core_irq_callback_handler is रक्षित by top-level
	 *       spinlock, so it is safe to clear any पूर्णांकerrupt status here.
	 */
	dpu_kms->hw_पूर्णांकr->ops.clear_पूर्णांकr_status_nolock(
			dpu_kms->hw_पूर्णांकr,
			irq_idx);
पूर्ण

पूर्णांक dpu_core_irq_idx_lookup(काष्ठा dpu_kms *dpu_kms,
		क्रमागत dpu_पूर्णांकr_type पूर्णांकr_type, u32 instance_idx)
अणु
	अगर (!dpu_kms->hw_पूर्णांकr || !dpu_kms->hw_पूर्णांकr->ops.irq_idx_lookup)
		वापस -EINVAL;

	वापस dpu_kms->hw_पूर्णांकr->ops.irq_idx_lookup(dpu_kms->hw_पूर्णांकr,
			पूर्णांकr_type, instance_idx);
पूर्ण

/**
 * _dpu_core_irq_enable - enable core पूर्णांकerrupt given by the index
 * @dpu_kms:		Poपूर्णांकer to dpu kms context
 * @irq_idx:		पूर्णांकerrupt index
 */
अटल पूर्णांक _dpu_core_irq_enable(काष्ठा dpu_kms *dpu_kms, पूर्णांक irq_idx)
अणु
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ret = 0, enable_count;

	अगर (!dpu_kms->hw_पूर्णांकr ||
			!dpu_kms->irq_obj.enable_counts ||
			!dpu_kms->irq_obj.irq_counts) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq_idx < 0 || irq_idx >= dpu_kms->hw_पूर्णांकr->irq_idx_tbl_size) अणु
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	enable_count = atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idx]);
	DRM_DEBUG_KMS("irq_idx=%d enable_count=%d\n", irq_idx, enable_count);
	trace_dpu_core_irq_enable_idx(irq_idx, enable_count);

	अगर (atomic_inc_वापस(&dpu_kms->irq_obj.enable_counts[irq_idx]) == 1) अणु
		ret = dpu_kms->hw_पूर्णांकr->ops.enable_irq(
				dpu_kms->hw_पूर्णांकr,
				irq_idx);
		अगर (ret)
			DPU_ERROR("Fail to enable IRQ for irq_idx:%d\n",
					irq_idx);

		DPU_DEBUG("irq_idx=%d ret=%d\n", irq_idx, ret);

		spin_lock_irqsave(&dpu_kms->irq_obj.cb_lock, irq_flags);
		/* empty callback list but पूर्णांकerrupt is enabled */
		अगर (list_empty(&dpu_kms->irq_obj.irq_cb_tbl[irq_idx]))
			DPU_ERROR("irq_idx=%d enabled with no callback\n",
					irq_idx);
		spin_unlock_irqrestore(&dpu_kms->irq_obj.cb_lock, irq_flags);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dpu_core_irq_enable(काष्ठा dpu_kms *dpu_kms, पूर्णांक *irq_idxs, u32 irq_count)
अणु
	पूर्णांक i, ret = 0, counts;

	अगर (!irq_idxs || !irq_count) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	counts = atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idxs[0]]);
	अगर (counts)
		DRM_ERROR("irq_idx=%d enable_count=%d\n", irq_idxs[0], counts);

	क्रम (i = 0; (i < irq_count) && !ret; i++)
		ret = _dpu_core_irq_enable(dpu_kms, irq_idxs[i]);

	वापस ret;
पूर्ण

/**
 * _dpu_core_irq_disable - disable core पूर्णांकerrupt given by the index
 * @dpu_kms:		Poपूर्णांकer to dpu kms context
 * @irq_idx:		पूर्णांकerrupt index
 */
अटल पूर्णांक _dpu_core_irq_disable(काष्ठा dpu_kms *dpu_kms, पूर्णांक irq_idx)
अणु
	पूर्णांक ret = 0, enable_count;

	अगर (!dpu_kms->hw_पूर्णांकr || !dpu_kms->irq_obj.enable_counts) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq_idx < 0 || irq_idx >= dpu_kms->hw_पूर्णांकr->irq_idx_tbl_size) अणु
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	enable_count = atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idx]);
	DRM_DEBUG_KMS("irq_idx=%d enable_count=%d\n", irq_idx, enable_count);
	trace_dpu_core_irq_disable_idx(irq_idx, enable_count);

	अगर (atomic_dec_वापस(&dpu_kms->irq_obj.enable_counts[irq_idx]) == 0) अणु
		ret = dpu_kms->hw_पूर्णांकr->ops.disable_irq(
				dpu_kms->hw_पूर्णांकr,
				irq_idx);
		अगर (ret)
			DPU_ERROR("Fail to disable IRQ for irq_idx:%d\n",
					irq_idx);
		DPU_DEBUG("irq_idx=%d ret=%d\n", irq_idx, ret);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dpu_core_irq_disable(काष्ठा dpu_kms *dpu_kms, पूर्णांक *irq_idxs, u32 irq_count)
अणु
	पूर्णांक i, ret = 0, counts;

	अगर (!irq_idxs || !irq_count) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	counts = atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idxs[0]]);
	अगर (counts == 2)
		DRM_ERROR("irq_idx=%d enable_count=%d\n", irq_idxs[0], counts);

	क्रम (i = 0; (i < irq_count) && !ret; i++)
		ret = _dpu_core_irq_disable(dpu_kms, irq_idxs[i]);

	वापस ret;
पूर्ण

u32 dpu_core_irq_पढ़ो(काष्ठा dpu_kms *dpu_kms, पूर्णांक irq_idx, bool clear)
अणु
	अगर (!dpu_kms->hw_पूर्णांकr ||
			!dpu_kms->hw_पूर्णांकr->ops.get_पूर्णांकerrupt_status)
		वापस 0;

	अगर (irq_idx < 0) अणु
		DPU_ERROR("[%pS] invalid irq_idx=%d\n",
				__builtin_वापस_address(0), irq_idx);
		वापस 0;
	पूर्ण

	वापस dpu_kms->hw_पूर्णांकr->ops.get_पूर्णांकerrupt_status(dpu_kms->hw_पूर्णांकr,
			irq_idx, clear);
पूर्ण

पूर्णांक dpu_core_irq_रेजिस्टर_callback(काष्ठा dpu_kms *dpu_kms, पूर्णांक irq_idx,
		काष्ठा dpu_irq_callback *रेजिस्टर_irq_cb)
अणु
	अचिन्हित दीर्घ irq_flags;

	अगर (!dpu_kms->irq_obj.irq_cb_tbl) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!रेजिस्टर_irq_cb || !रेजिस्टर_irq_cb->func) अणु
		DPU_ERROR("invalid irq_cb:%d func:%d\n",
				रेजिस्टर_irq_cb != शून्य,
				रेजिस्टर_irq_cb ?
					रेजिस्टर_irq_cb->func != शून्य : -1);
		वापस -EINVAL;
	पूर्ण

	अगर (irq_idx < 0 || irq_idx >= dpu_kms->hw_पूर्णांकr->irq_idx_tbl_size) अणु
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	DPU_DEBUG("[%pS] irq_idx=%d\n", __builtin_वापस_address(0), irq_idx);

	spin_lock_irqsave(&dpu_kms->irq_obj.cb_lock, irq_flags);
	trace_dpu_core_irq_रेजिस्टर_callback(irq_idx, रेजिस्टर_irq_cb);
	list_del_init(&रेजिस्टर_irq_cb->list);
	list_add_tail(&रेजिस्टर_irq_cb->list,
			&dpu_kms->irq_obj.irq_cb_tbl[irq_idx]);
	spin_unlock_irqrestore(&dpu_kms->irq_obj.cb_lock, irq_flags);

	वापस 0;
पूर्ण

पूर्णांक dpu_core_irq_unरेजिस्टर_callback(काष्ठा dpu_kms *dpu_kms, पूर्णांक irq_idx,
		काष्ठा dpu_irq_callback *रेजिस्टर_irq_cb)
अणु
	अचिन्हित दीर्घ irq_flags;

	अगर (!dpu_kms->irq_obj.irq_cb_tbl) अणु
		DPU_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!रेजिस्टर_irq_cb || !रेजिस्टर_irq_cb->func) अणु
		DPU_ERROR("invalid irq_cb:%d func:%d\n",
				रेजिस्टर_irq_cb != शून्य,
				रेजिस्टर_irq_cb ?
					रेजिस्टर_irq_cb->func != शून्य : -1);
		वापस -EINVAL;
	पूर्ण

	अगर (irq_idx < 0 || irq_idx >= dpu_kms->hw_पूर्णांकr->irq_idx_tbl_size) अणु
		DPU_ERROR("invalid IRQ index: [%d]\n", irq_idx);
		वापस -EINVAL;
	पूर्ण

	DPU_DEBUG("[%pS] irq_idx=%d\n", __builtin_वापस_address(0), irq_idx);

	spin_lock_irqsave(&dpu_kms->irq_obj.cb_lock, irq_flags);
	trace_dpu_core_irq_unरेजिस्टर_callback(irq_idx, रेजिस्टर_irq_cb);
	list_del_init(&रेजिस्टर_irq_cb->list);
	/* empty callback list but पूर्णांकerrupt is still enabled */
	अगर (list_empty(&dpu_kms->irq_obj.irq_cb_tbl[irq_idx]) &&
			atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[irq_idx]))
		DPU_ERROR("irq_idx=%d enabled with no callback\n", irq_idx);
	spin_unlock_irqrestore(&dpu_kms->irq_obj.cb_lock, irq_flags);

	वापस 0;
पूर्ण

अटल व्योम dpu_clear_all_irqs(काष्ठा dpu_kms *dpu_kms)
अणु
	अगर (!dpu_kms->hw_पूर्णांकr || !dpu_kms->hw_पूर्णांकr->ops.clear_all_irqs)
		वापस;

	dpu_kms->hw_पूर्णांकr->ops.clear_all_irqs(dpu_kms->hw_पूर्णांकr);
पूर्ण

अटल व्योम dpu_disable_all_irqs(काष्ठा dpu_kms *dpu_kms)
अणु
	अगर (!dpu_kms->hw_पूर्णांकr || !dpu_kms->hw_पूर्णांकr->ops.disable_all_irqs)
		वापस;

	dpu_kms->hw_पूर्णांकr->ops.disable_all_irqs(dpu_kms->hw_पूर्णांकr);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक dpu_debugfs_core_irq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा dpu_irq *irq_obj = s->निजी;
	काष्ठा dpu_irq_callback *cb;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक i, irq_count, enable_count, cb_count;

	अगर (WARN_ON(!irq_obj->enable_counts || !irq_obj->irq_cb_tbl))
		वापस 0;

	क्रम (i = 0; i < irq_obj->total_irqs; i++) अणु
		spin_lock_irqsave(&irq_obj->cb_lock, irq_flags);
		cb_count = 0;
		irq_count = atomic_पढ़ो(&irq_obj->irq_counts[i]);
		enable_count = atomic_पढ़ो(&irq_obj->enable_counts[i]);
		list_क्रम_each_entry(cb, &irq_obj->irq_cb_tbl[i], list)
			cb_count++;
		spin_unlock_irqrestore(&irq_obj->cb_lock, irq_flags);

		अगर (irq_count || enable_count || cb_count)
			seq_म_लिखो(s, "idx:%d irq:%d enable:%d cb:%d\n",
					i, irq_count, enable_count, cb_count);
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dpu_debugfs_core_irq);

व्योम dpu_debugfs_core_irq_init(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dentry *parent)
अणु
	debugfs_create_file("core_irq", 0600, parent, &dpu_kms->irq_obj,
		&dpu_debugfs_core_irq_fops);
पूर्ण
#पूर्ण_अगर

व्योम dpu_core_irq_preinstall(काष्ठा dpu_kms *dpu_kms)
अणु
	पूर्णांक i;

	pm_runसमय_get_sync(&dpu_kms->pdev->dev);
	dpu_clear_all_irqs(dpu_kms);
	dpu_disable_all_irqs(dpu_kms);
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);

	spin_lock_init(&dpu_kms->irq_obj.cb_lock);

	/* Create irq callbacks क्रम all possible irq_idx */
	dpu_kms->irq_obj.total_irqs = dpu_kms->hw_पूर्णांकr->irq_idx_tbl_size;
	dpu_kms->irq_obj.irq_cb_tbl = kसुस्मृति(dpu_kms->irq_obj.total_irqs,
			माप(काष्ठा list_head), GFP_KERNEL);
	dpu_kms->irq_obj.enable_counts = kसुस्मृति(dpu_kms->irq_obj.total_irqs,
			माप(atomic_t), GFP_KERNEL);
	dpu_kms->irq_obj.irq_counts = kसुस्मृति(dpu_kms->irq_obj.total_irqs,
			माप(atomic_t), GFP_KERNEL);
	क्रम (i = 0; i < dpu_kms->irq_obj.total_irqs; i++) अणु
		INIT_LIST_HEAD(&dpu_kms->irq_obj.irq_cb_tbl[i]);
		atomic_set(&dpu_kms->irq_obj.enable_counts[i], 0);
		atomic_set(&dpu_kms->irq_obj.irq_counts[i], 0);
	पूर्ण
पूर्ण

व्योम dpu_core_irq_uninstall(काष्ठा dpu_kms *dpu_kms)
अणु
	पूर्णांक i;

	pm_runसमय_get_sync(&dpu_kms->pdev->dev);
	क्रम (i = 0; i < dpu_kms->irq_obj.total_irqs; i++)
		अगर (atomic_पढ़ो(&dpu_kms->irq_obj.enable_counts[i]) ||
				!list_empty(&dpu_kms->irq_obj.irq_cb_tbl[i]))
			DPU_ERROR("irq_idx=%d still enabled/registered\n", i);

	dpu_clear_all_irqs(dpu_kms);
	dpu_disable_all_irqs(dpu_kms);
	pm_runसमय_put_sync(&dpu_kms->pdev->dev);

	kमुक्त(dpu_kms->irq_obj.irq_cb_tbl);
	kमुक्त(dpu_kms->irq_obj.enable_counts);
	kमुक्त(dpu_kms->irq_obj.irq_counts);
	dpu_kms->irq_obj.irq_cb_tbl = शून्य;
	dpu_kms->irq_obj.enable_counts = शून्य;
	dpu_kms->irq_obj.irq_counts = शून्य;
	dpu_kms->irq_obj.total_irqs = 0;
पूर्ण

irqवापस_t dpu_core_irq(काष्ठा dpu_kms *dpu_kms)
अणु
	/*
	 * Read पूर्णांकerrupt status from all sources. Interrupt status are
	 * stored within hw_पूर्णांकr.
	 * Function will also clear the पूर्णांकerrupt status after पढ़ोing.
	 * Inभागidual पूर्णांकerrupt status bit will only get stored अगर it
	 * is enabled.
	 */
	dpu_kms->hw_पूर्णांकr->ops.get_पूर्णांकerrupt_statuses(dpu_kms->hw_पूर्णांकr);

	/*
	 * Dispatch to HW driver to handle पूर्णांकerrupt lookup that is being
	 * fired. When matching पूर्णांकerrupt is located, HW driver will call to
	 * dpu_core_irq_callback_handler with the irq_idx from the lookup table.
	 * dpu_core_irq_callback_handler will perक्रमm the रेजिस्टरed function
	 * callback, and करो the पूर्णांकerrupt status clearing once the रेजिस्टरed
	 * callback is finished.
	 */
	dpu_kms->hw_पूर्णांकr->ops.dispatch_irqs(
			dpu_kms->hw_पूर्णांकr,
			dpu_core_irq_callback_handler,
			dpu_kms);

	वापस IRQ_HANDLED;
पूर्ण
