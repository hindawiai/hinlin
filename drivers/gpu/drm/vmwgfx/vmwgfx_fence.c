<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2011-2014 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश <linux/sched/संकेत.स>

#समावेश "vmwgfx_drv.h"

#घोषणा VMW_FENCE_WRAP (1 << 31)

काष्ठा vmw_fence_manager अणु
	पूर्णांक num_fence_objects;
	काष्ठा vmw_निजी *dev_priv;
	spinlock_t lock;
	काष्ठा list_head fence_list;
	काष्ठा work_काष्ठा work;
	u32 user_fence_size;
	u32 fence_size;
	u32 event_fence_action_size;
	bool fअगरo_करोwn;
	काष्ठा list_head cleanup_list;
	uपूर्णांक32_t pending_actions[VMW_ACTION_MAX];
	काष्ठा mutex goal_irq_mutex;
	bool goal_irq_on; /* Protected by @goal_irq_mutex */
	bool seqno_valid; /* Protected by @lock, and may not be set to true
			     without the @goal_irq_mutex held. */
	u64 ctx;
पूर्ण;

काष्ठा vmw_user_fence अणु
	काष्ठा tपंचांग_base_object base;
	काष्ठा vmw_fence_obj fence;
पूर्ण;

/**
 * काष्ठा vmw_event_fence_action - fence action that delivers a drm event.
 *
 * @action: A काष्ठा vmw_fence_action to hook up to a fence.
 * @event: A poपूर्णांकer to the pending event.
 * @fence: A referenced poपूर्णांकer to the fence to keep it alive जबतक @action
 * hangs on it.
 * @dev: Poपूर्णांकer to a काष्ठा drm_device so we can access the event stuff.
 * @tv_sec: If non-null, the variable poपूर्णांकed to will be asचिन्हित
 * current समय tv_sec val when the fence संकेतs.
 * @tv_usec: Must be set अगर @tv_sec is set, and the variable poपूर्णांकed to will
 * be asचिन्हित the current समय tv_usec val when the fence संकेतs.
 */
काष्ठा vmw_event_fence_action अणु
	काष्ठा vmw_fence_action action;

	काष्ठा drm_pending_event *event;
	काष्ठा vmw_fence_obj *fence;
	काष्ठा drm_device *dev;

	uपूर्णांक32_t *tv_sec;
	uपूर्णांक32_t *tv_usec;
पूर्ण;

अटल काष्ठा vmw_fence_manager *
fman_from_fence(काष्ठा vmw_fence_obj *fence)
अणु
	वापस container_of(fence->base.lock, काष्ठा vmw_fence_manager, lock);
पूर्ण

/*
 * Note on fencing subप्रणाली usage of irqs:
 * Typically the vmw_fences_update function is called
 *
 * a) When a new fence seqno has been submitted by the fअगरo code.
 * b) On-demand when we have रुकोers. Sleeping रुकोers will चयन on the
 * ANY_FENCE irq and call vmw_fences_update function each समय an ANY_FENCE
 * irq is received. When the last fence रुकोer is gone, that IRQ is masked
 * away.
 *
 * In situations where there are no रुकोers and we करोn't submit any new fences,
 * fence objects may not be संकेतed. This is perfectly OK, since there are
 * no consumers of the संकेतed data, but that is NOT ok when there are fence
 * actions attached to a fence. The fencing subप्रणाली then makes use of the
 * FENCE_GOAL irq and sets the fence goal seqno to that of the next fence
 * which has an action attached, and each समय vmw_fences_update is called,
 * the subप्रणाली makes sure the fence goal seqno is updated.
 *
 * The fence goal seqno irq is on as दीर्घ as there are unसंकेतed fence
 * objects with actions attached to them.
 */

अटल व्योम vmw_fence_obj_destroy(काष्ठा dma_fence *f)
अणु
	काष्ठा vmw_fence_obj *fence =
		container_of(f, काष्ठा vmw_fence_obj, base);

	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);

	spin_lock(&fman->lock);
	list_del_init(&fence->head);
	--fman->num_fence_objects;
	spin_unlock(&fman->lock);
	fence->destroy(fence);
पूर्ण

अटल स्थिर अक्षर *vmw_fence_get_driver_name(काष्ठा dma_fence *f)
अणु
	वापस "vmwgfx";
पूर्ण

अटल स्थिर अक्षर *vmw_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	वापस "svga";
पूर्ण

अटल bool vmw_fence_enable_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा vmw_fence_obj *fence =
		container_of(f, काष्ठा vmw_fence_obj, base);

	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);
	काष्ठा vmw_निजी *dev_priv = fman->dev_priv;

	u32 seqno = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_FENCE);
	अगर (seqno - fence->base.seqno < VMW_FENCE_WRAP)
		वापस false;

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);

	वापस true;
पूर्ण

काष्ठा vmwgfx_रुको_cb अणु
	काष्ठा dma_fence_cb base;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल व्योम
vmwgfx_रुको_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा vmwgfx_रुको_cb *रुको =
		container_of(cb, काष्ठा vmwgfx_रुको_cb, base);

	wake_up_process(रुको->task);
पूर्ण

अटल व्योम __vmw_fences_update(काष्ठा vmw_fence_manager *fman);

अटल दीर्घ vmw_fence_रुको(काष्ठा dma_fence *f, bool पूर्णांकr, चिन्हित दीर्घ समयout)
अणु
	काष्ठा vmw_fence_obj *fence =
		container_of(f, काष्ठा vmw_fence_obj, base);

	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);
	काष्ठा vmw_निजी *dev_priv = fman->dev_priv;
	काष्ठा vmwgfx_रुको_cb cb;
	दीर्घ ret = समयout;

	अगर (likely(vmw_fence_obj_संकेतed(fence)))
		वापस समयout;

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
	vmw_seqno_रुकोer_add(dev_priv);

	spin_lock(f->lock);

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &f->flags))
		जाओ out;

	अगर (पूर्णांकr && संकेत_pending(current)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	cb.base.func = vmwgfx_रुको_cb;
	cb.task = current;
	list_add(&cb.base.node, &f->cb_list);

	क्रम (;;) अणु
		__vmw_fences_update(fman);

		/*
		 * We can use the barrier मुक्त __set_current_state() since
		 * DMA_FENCE_FLAG_SIGNALED_BIT + wakeup is रक्षित by the
		 * fence spinlock.
		 */
		अगर (पूर्णांकr)
			__set_current_state(TASK_INTERRUPTIBLE);
		अन्यथा
			__set_current_state(TASK_UNINTERRUPTIBLE);

		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &f->flags)) अणु
			अगर (ret == 0 && समयout > 0)
				ret = 1;
			अवरोध;
		पूर्ण

		अगर (पूर्णांकr && संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (ret == 0)
			अवरोध;

		spin_unlock(f->lock);

		ret = schedule_समयout(ret);

		spin_lock(f->lock);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	अगर (!list_empty(&cb.base.node))
		list_del(&cb.base.node);

out:
	spin_unlock(f->lock);

	vmw_seqno_रुकोer_हटाओ(dev_priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops vmw_fence_ops = अणु
	.get_driver_name = vmw_fence_get_driver_name,
	.get_समयline_name = vmw_fence_get_समयline_name,
	.enable_संकेतing = vmw_fence_enable_संकेतing,
	.रुको = vmw_fence_रुको,
	.release = vmw_fence_obj_destroy,
पूर्ण;


/*
 * Execute संकेत actions on fences recently संकेतed.
 * This is करोne from a workqueue so we करोn't have to execute
 * संकेत actions from atomic context.
 */

अटल व्योम vmw_fence_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmw_fence_manager *fman =
		container_of(work, काष्ठा vmw_fence_manager, work);
	काष्ठा list_head list;
	काष्ठा vmw_fence_action *action, *next_action;
	bool seqno_valid;

	करो अणु
		INIT_LIST_HEAD(&list);
		mutex_lock(&fman->goal_irq_mutex);

		spin_lock(&fman->lock);
		list_splice_init(&fman->cleanup_list, &list);
		seqno_valid = fman->seqno_valid;
		spin_unlock(&fman->lock);

		अगर (!seqno_valid && fman->goal_irq_on) अणु
			fman->goal_irq_on = false;
			vmw_goal_रुकोer_हटाओ(fman->dev_priv);
		पूर्ण
		mutex_unlock(&fman->goal_irq_mutex);

		अगर (list_empty(&list))
			वापस;

		/*
		 * At this poपूर्णांक, only we should be able to manipulate the
		 * list heads of the actions we have on the निजी list.
		 * hence fman::lock not held.
		 */

		list_क्रम_each_entry_safe(action, next_action, &list, head) अणु
			list_del_init(&action->head);
			अगर (action->cleanup)
				action->cleanup(action);
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

काष्ठा vmw_fence_manager *vmw_fence_manager_init(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_fence_manager *fman = kzalloc(माप(*fman), GFP_KERNEL);

	अगर (unlikely(!fman))
		वापस शून्य;

	fman->dev_priv = dev_priv;
	spin_lock_init(&fman->lock);
	INIT_LIST_HEAD(&fman->fence_list);
	INIT_LIST_HEAD(&fman->cleanup_list);
	INIT_WORK(&fman->work, &vmw_fence_work_func);
	fman->fअगरo_करोwn = true;
	fman->user_fence_size = tपंचांग_round_pot(माप(काष्ठा vmw_user_fence)) +
		TTM_OBJ_EXTRA_SIZE;
	fman->fence_size = tपंचांग_round_pot(माप(काष्ठा vmw_fence_obj));
	fman->event_fence_action_size =
		tपंचांग_round_pot(माप(काष्ठा vmw_event_fence_action));
	mutex_init(&fman->goal_irq_mutex);
	fman->ctx = dma_fence_context_alloc(1);

	वापस fman;
पूर्ण

व्योम vmw_fence_manager_takeकरोwn(काष्ठा vmw_fence_manager *fman)
अणु
	bool lists_empty;

	(व्योम) cancel_work_sync(&fman->work);

	spin_lock(&fman->lock);
	lists_empty = list_empty(&fman->fence_list) &&
		list_empty(&fman->cleanup_list);
	spin_unlock(&fman->lock);

	BUG_ON(!lists_empty);
	kमुक्त(fman);
पूर्ण

अटल पूर्णांक vmw_fence_obj_init(काष्ठा vmw_fence_manager *fman,
			      काष्ठा vmw_fence_obj *fence, u32 seqno,
			      व्योम (*destroy) (काष्ठा vmw_fence_obj *fence))
अणु
	पूर्णांक ret = 0;

	dma_fence_init(&fence->base, &vmw_fence_ops, &fman->lock,
		       fman->ctx, seqno);
	INIT_LIST_HEAD(&fence->seq_passed_actions);
	fence->destroy = destroy;

	spin_lock(&fman->lock);
	अगर (unlikely(fman->fअगरo_करोwn)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	list_add_tail(&fence->head, &fman->fence_list);
	++fman->num_fence_objects;

out_unlock:
	spin_unlock(&fman->lock);
	वापस ret;

पूर्ण

अटल व्योम vmw_fences_perक्रमm_actions(काष्ठा vmw_fence_manager *fman,
				काष्ठा list_head *list)
अणु
	काष्ठा vmw_fence_action *action, *next_action;

	list_क्रम_each_entry_safe(action, next_action, list, head) अणु
		list_del_init(&action->head);
		fman->pending_actions[action->type]--;
		अगर (action->seq_passed != शून्य)
			action->seq_passed(action);

		/*
		 * Add the cleanup action to the cleanup list so that
		 * it will be perक्रमmed by a worker task.
		 */

		list_add_tail(&action->head, &fman->cleanup_list);
	पूर्ण
पूर्ण

/**
 * vmw_fence_goal_new_locked - Figure out a new device fence goal
 * seqno अगर needed.
 *
 * @fman: Poपूर्णांकer to a fence manager.
 * @passed_seqno: The seqno the device currently संकेतs as passed.
 *
 * This function should be called with the fence manager lock held.
 * It is typically called when we have a new passed_seqno, and
 * we might need to update the fence goal. It checks to see whether
 * the current fence goal has alपढ़ोy passed, and, in that हाल,
 * scans through all unसंकेतed fences to get the next fence object with an
 * action attached, and sets the seqno of that fence as a new fence goal.
 *
 * वापसs true अगर the device goal seqno was updated. False otherwise.
 */
अटल bool vmw_fence_goal_new_locked(काष्ठा vmw_fence_manager *fman,
				      u32 passed_seqno)
अणु
	u32 goal_seqno;
	काष्ठा vmw_fence_obj *fence;

	अगर (likely(!fman->seqno_valid))
		वापस false;

	goal_seqno = vmw_fअगरo_mem_पढ़ो(fman->dev_priv, SVGA_FIFO_FENCE_GOAL);
	अगर (likely(passed_seqno - goal_seqno >= VMW_FENCE_WRAP))
		वापस false;

	fman->seqno_valid = false;
	list_क्रम_each_entry(fence, &fman->fence_list, head) अणु
		अगर (!list_empty(&fence->seq_passed_actions)) अणु
			fman->seqno_valid = true;
			vmw_fअगरo_mem_ग_लिखो(fman->dev_priv,
					   SVGA_FIFO_FENCE_GOAL,
					   fence->base.seqno);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण


/**
 * vmw_fence_goal_check_locked - Replace the device fence goal seqno अगर
 * needed.
 *
 * @fence: Poपूर्णांकer to a काष्ठा vmw_fence_obj the seqno of which should be
 * considered as a device fence goal.
 *
 * This function should be called with the fence manager lock held.
 * It is typically called when an action has been attached to a fence to
 * check whether the seqno of that fence should be used क्रम a fence
 * goal पूर्णांकerrupt. This is typically needed अगर the current fence goal is
 * invalid, or has a higher seqno than that of the current fence object.
 *
 * वापसs true अगर the device goal seqno was updated. False otherwise.
 */
अटल bool vmw_fence_goal_check_locked(काष्ठा vmw_fence_obj *fence)
अणु
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);
	u32 goal_seqno;

	अगर (dma_fence_is_संकेतed_locked(&fence->base))
		वापस false;

	goal_seqno = vmw_fअगरo_mem_पढ़ो(fman->dev_priv, SVGA_FIFO_FENCE_GOAL);
	अगर (likely(fman->seqno_valid &&
		   goal_seqno - fence->base.seqno < VMW_FENCE_WRAP))
		वापस false;

	vmw_fअगरo_mem_ग_लिखो(fman->dev_priv, SVGA_FIFO_FENCE_GOAL,
			   fence->base.seqno);
	fman->seqno_valid = true;

	वापस true;
पूर्ण

अटल व्योम __vmw_fences_update(काष्ठा vmw_fence_manager *fman)
अणु
	काष्ठा vmw_fence_obj *fence, *next_fence;
	काष्ठा list_head action_list;
	bool needs_rerun;
	uपूर्णांक32_t seqno, new_seqno;

	seqno = vmw_fअगरo_mem_पढ़ो(fman->dev_priv, SVGA_FIFO_FENCE);
rerun:
	list_क्रम_each_entry_safe(fence, next_fence, &fman->fence_list, head) अणु
		अगर (seqno - fence->base.seqno < VMW_FENCE_WRAP) अणु
			list_del_init(&fence->head);
			dma_fence_संकेत_locked(&fence->base);
			INIT_LIST_HEAD(&action_list);
			list_splice_init(&fence->seq_passed_actions,
					 &action_list);
			vmw_fences_perक्रमm_actions(fman, &action_list);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	/*
	 * Rerun अगर the fence goal seqno was updated, and the
	 * hardware might have raced with that update, so that
	 * we missed a fence_goal irq.
	 */

	needs_rerun = vmw_fence_goal_new_locked(fman, seqno);
	अगर (unlikely(needs_rerun)) अणु
		new_seqno = vmw_fअगरo_mem_पढ़ो(fman->dev_priv, SVGA_FIFO_FENCE);
		अगर (new_seqno != seqno) अणु
			seqno = new_seqno;
			जाओ rerun;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&fman->cleanup_list))
		(व्योम) schedule_work(&fman->work);
पूर्ण

व्योम vmw_fences_update(काष्ठा vmw_fence_manager *fman)
अणु
	spin_lock(&fman->lock);
	__vmw_fences_update(fman);
	spin_unlock(&fman->lock);
पूर्ण

bool vmw_fence_obj_संकेतed(काष्ठा vmw_fence_obj *fence)
अणु
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->base.flags))
		वापस true;

	vmw_fences_update(fman);

	वापस dma_fence_is_संकेतed(&fence->base);
पूर्ण

पूर्णांक vmw_fence_obj_रुको(काष्ठा vmw_fence_obj *fence, bool lazy,
		       bool पूर्णांकerruptible, अचिन्हित दीर्घ समयout)
अणु
	दीर्घ ret = dma_fence_रुको_समयout(&fence->base, पूर्णांकerruptible, समयout);

	अगर (likely(ret > 0))
		वापस 0;
	अन्यथा अगर (ret == 0)
		वापस -EBUSY;
	अन्यथा
		वापस ret;
पूर्ण

व्योम vmw_fence_obj_flush(काष्ठा vmw_fence_obj *fence)
अणु
	काष्ठा vmw_निजी *dev_priv = fman_from_fence(fence)->dev_priv;

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
पूर्ण

अटल व्योम vmw_fence_destroy(काष्ठा vmw_fence_obj *fence)
अणु
	dma_fence_मुक्त(&fence->base);
पूर्ण

पूर्णांक vmw_fence_create(काष्ठा vmw_fence_manager *fman,
		     uपूर्णांक32_t seqno,
		     काष्ठा vmw_fence_obj **p_fence)
अणु
	काष्ठा vmw_fence_obj *fence;
 	पूर्णांक ret;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (unlikely(!fence))
		वापस -ENOMEM;

	ret = vmw_fence_obj_init(fman, fence, seqno,
				 vmw_fence_destroy);
	अगर (unlikely(ret != 0))
		जाओ out_err_init;

	*p_fence = fence;
	वापस 0;

out_err_init:
	kमुक्त(fence);
	वापस ret;
पूर्ण


अटल व्योम vmw_user_fence_destroy(काष्ठा vmw_fence_obj *fence)
अणु
	काष्ठा vmw_user_fence *ufence =
		container_of(fence, काष्ठा vmw_user_fence, fence);
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);

	tपंचांग_base_object_kमुक्त(ufence, base);
	/*
	 * Free kernel space accounting.
	 */
	tपंचांग_mem_global_मुक्त(vmw_mem_glob(fman->dev_priv),
			    fman->user_fence_size);
पूर्ण

अटल व्योम vmw_user_fence_base_release(काष्ठा tपंचांग_base_object **p_base)
अणु
	काष्ठा tपंचांग_base_object *base = *p_base;
	काष्ठा vmw_user_fence *ufence =
		container_of(base, काष्ठा vmw_user_fence, base);
	काष्ठा vmw_fence_obj *fence = &ufence->fence;

	*p_base = शून्य;
	vmw_fence_obj_unreference(&fence);
पूर्ण

पूर्णांक vmw_user_fence_create(काष्ठा drm_file *file_priv,
			  काष्ठा vmw_fence_manager *fman,
			  uपूर्णांक32_t seqno,
			  काष्ठा vmw_fence_obj **p_fence,
			  uपूर्णांक32_t *p_handle)
अणु
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_user_fence *ufence;
	काष्ठा vmw_fence_obj *पंचांगp;
	काष्ठा tपंचांग_mem_global *mem_glob = vmw_mem_glob(fman->dev_priv);
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	पूर्णांक ret;

	/*
	 * Kernel memory space accounting, since this object may
	 * be created by a user-space request.
	 */

	ret = tपंचांग_mem_global_alloc(mem_glob, fman->user_fence_size,
				   &ctx);
	अगर (unlikely(ret != 0))
		वापस ret;

	ufence = kzalloc(माप(*ufence), GFP_KERNEL);
	अगर (unlikely(!ufence)) अणु
		ret = -ENOMEM;
		जाओ out_no_object;
	पूर्ण

	ret = vmw_fence_obj_init(fman, &ufence->fence, seqno,
				 vmw_user_fence_destroy);
	अगर (unlikely(ret != 0)) अणु
		kमुक्त(ufence);
		जाओ out_no_object;
	पूर्ण

	/*
	 * The base object holds a reference which is मुक्तd in
	 * vmw_user_fence_base_release.
	 */
	पंचांगp = vmw_fence_obj_reference(&ufence->fence);
	ret = tपंचांग_base_object_init(tfile, &ufence->base, false,
				   VMW_RES_FENCE,
				   &vmw_user_fence_base_release, शून्य);


	अगर (unlikely(ret != 0)) अणु
		/*
		 * Free the base object's reference
		 */
		vmw_fence_obj_unreference(&पंचांगp);
		जाओ out_err;
	पूर्ण

	*p_fence = &ufence->fence;
	*p_handle = ufence->base.handle;

	वापस 0;
out_err:
	पंचांगp = &ufence->fence;
	vmw_fence_obj_unreference(&पंचांगp);
out_no_object:
	tपंचांग_mem_global_मुक्त(mem_glob, fman->user_fence_size);
	वापस ret;
पूर्ण


/**
 * vmw_रुको_dma_fence - Wait क्रम a dma fence
 *
 * @fman: poपूर्णांकer to a fence manager
 * @fence: DMA fence to रुको on
 *
 * This function handles the हाल when the fence is actually a fence
 * array.  If that's the case, it'll रुको on each of the child fence
 */
पूर्णांक vmw_रुको_dma_fence(काष्ठा vmw_fence_manager *fman,
		       काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence_array *fence_array;
	पूर्णांक ret = 0;
	पूर्णांक i;


	अगर (dma_fence_is_संकेतed(fence))
		वापस 0;

	अगर (!dma_fence_is_array(fence))
		वापस dma_fence_रुको(fence, true);

	/* From i915: Note that अगर the fence-array was created in
	 * संकेत-on-any mode, we should *not* decompose it पूर्णांकo its inभागidual
	 * fences. However, we करोn't currently store which mode the fence-array
	 * is operating in. Fortunately, the only user of संकेत-on-any is
	 * निजी to amdgpu and we should not see any incoming fence-array
	 * from sync-file being in संकेत-on-any mode.
	 */

	fence_array = to_dma_fence_array(fence);
	क्रम (i = 0; i < fence_array->num_fences; i++) अणु
		काष्ठा dma_fence *child = fence_array->fences[i];

		ret = dma_fence_रुको(child, true);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * vmw_fence_fअगरo_करोwn - संकेत all unसंकेतed fence objects.
 */

व्योम vmw_fence_fअगरo_करोwn(काष्ठा vmw_fence_manager *fman)
अणु
	काष्ठा list_head action_list;
	पूर्णांक ret;

	/*
	 * The list may be altered जबतक we traverse it, so always
	 * restart when we've released the fman->lock.
	 */

	spin_lock(&fman->lock);
	fman->fअगरo_करोwn = true;
	जबतक (!list_empty(&fman->fence_list)) अणु
		काष्ठा vmw_fence_obj *fence =
			list_entry(fman->fence_list.prev, काष्ठा vmw_fence_obj,
				   head);
		dma_fence_get(&fence->base);
		spin_unlock(&fman->lock);

		ret = vmw_fence_obj_रुको(fence, false, false,
					 VMW_FENCE_WAIT_TIMEOUT);

		अगर (unlikely(ret != 0)) अणु
			list_del_init(&fence->head);
			dma_fence_संकेत(&fence->base);
			INIT_LIST_HEAD(&action_list);
			list_splice_init(&fence->seq_passed_actions,
					 &action_list);
			vmw_fences_perक्रमm_actions(fman, &action_list);
		पूर्ण

		BUG_ON(!list_empty(&fence->head));
		dma_fence_put(&fence->base);
		spin_lock(&fman->lock);
	पूर्ण
	spin_unlock(&fman->lock);
पूर्ण

व्योम vmw_fence_fअगरo_up(काष्ठा vmw_fence_manager *fman)
अणु
	spin_lock(&fman->lock);
	fman->fअगरo_करोwn = false;
	spin_unlock(&fman->lock);
पूर्ण


/**
 * vmw_fence_obj_lookup - Look up a user-space fence object
 *
 * @tfile: A काष्ठा tपंचांग_object_file identअगरying the caller.
 * @handle: A handle identअगरying the fence object.
 * @वापस: A काष्ठा vmw_user_fence base tपंचांग object on success or
 * an error poपूर्णांकer on failure.
 *
 * The fence object is looked up and type-checked. The caller needs
 * to have खोलोed the fence object first, but since that happens on
 * creation and fence objects aren't shareable, that's not an
 * issue currently.
 */
अटल काष्ठा tपंचांग_base_object *
vmw_fence_obj_lookup(काष्ठा tपंचांग_object_file *tfile, u32 handle)
अणु
	काष्ठा tपंचांग_base_object *base = tपंचांग_base_object_lookup(tfile, handle);

	अगर (!base) अणु
		pr_err("Invalid fence object handle 0x%08lx.\n",
		       (अचिन्हित दीर्घ)handle);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (base->refcount_release != vmw_user_fence_base_release) अणु
		pr_err("Invalid fence object handle 0x%08lx.\n",
		       (अचिन्हित दीर्घ)handle);
		tपंचांग_base_object_unref(&base);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस base;
पूर्ण


पूर्णांक vmw_fence_obj_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_fence_रुको_arg *arg =
	    (काष्ठा drm_vmw_fence_रुको_arg *)data;
	अचिन्हित दीर्घ समयout;
	काष्ठा tपंचांग_base_object *base;
	काष्ठा vmw_fence_obj *fence;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	पूर्णांक ret;
	uपूर्णांक64_t रुको_समयout = ((uपूर्णांक64_t)arg->समयout_us * HZ);

	/*
	 * 64-bit भागision not present on 32-bit प्रणालीs, so करो an
	 * approximation. (Divide by 1000000).
	 */

	रुको_समयout = (रुको_समयout >> 20) + (रुको_समयout >> 24) -
	  (रुको_समयout >> 26);

	अगर (!arg->cookie_valid) अणु
		arg->cookie_valid = 1;
		arg->kernel_cookie = jअगरfies + रुको_समयout;
	पूर्ण

	base = vmw_fence_obj_lookup(tfile, arg->handle);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	fence = &(container_of(base, काष्ठा vmw_user_fence, base)->fence);

	समयout = jअगरfies;
	अगर (समय_after_eq(समयout, (अचिन्हित दीर्घ)arg->kernel_cookie)) अणु
		ret = ((vmw_fence_obj_संकेतed(fence)) ?
		       0 : -EBUSY);
		जाओ out;
	पूर्ण

	समयout = (अचिन्हित दीर्घ)arg->kernel_cookie - समयout;

	ret = vmw_fence_obj_रुको(fence, arg->lazy, true, समयout);

out:
	tपंचांग_base_object_unref(&base);

	/*
	 * Optionally unref the fence object.
	 */

	अगर (ret == 0 && (arg->रुको_options & DRM_VMW_WAIT_OPTION_UNREF))
		वापस tपंचांग_ref_object_base_unref(tfile, arg->handle,
						 TTM_REF_USAGE);
	वापस ret;
पूर्ण

पूर्णांक vmw_fence_obj_संकेतed_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_fence_संकेतed_arg *arg =
		(काष्ठा drm_vmw_fence_संकेतed_arg *) data;
	काष्ठा tपंचांग_base_object *base;
	काष्ठा vmw_fence_obj *fence;
	काष्ठा vmw_fence_manager *fman;
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);

	base = vmw_fence_obj_lookup(tfile, arg->handle);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	fence = &(container_of(base, काष्ठा vmw_user_fence, base)->fence);
	fman = fman_from_fence(fence);

	arg->संकेतed = vmw_fence_obj_संकेतed(fence);

	arg->संकेतed_flags = arg->flags;
	spin_lock(&fman->lock);
	arg->passed_seqno = dev_priv->last_पढ़ो_seqno;
	spin_unlock(&fman->lock);

	tपंचांग_base_object_unref(&base);

	वापस 0;
पूर्ण


पूर्णांक vmw_fence_obj_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_fence_arg *arg =
		(काष्ठा drm_vmw_fence_arg *) data;

	वापस tपंचांग_ref_object_base_unref(vmw_fpriv(file_priv)->tfile,
					 arg->handle,
					 TTM_REF_USAGE);
पूर्ण

/**
 * vmw_event_fence_action_seq_passed
 *
 * @action: The काष्ठा vmw_fence_action embedded in a काष्ठा
 * vmw_event_fence_action.
 *
 * This function is called when the seqno of the fence where @action is
 * attached has passed. It queues the event on the submitter's event list.
 * This function is always called from atomic context.
 */
अटल व्योम vmw_event_fence_action_seq_passed(काष्ठा vmw_fence_action *action)
अणु
	काष्ठा vmw_event_fence_action *eaction =
		container_of(action, काष्ठा vmw_event_fence_action, action);
	काष्ठा drm_device *dev = eaction->dev;
	काष्ठा drm_pending_event *event = eaction->event;

	अगर (unlikely(event == शून्य))
		वापस;

	spin_lock_irq(&dev->event_lock);

	अगर (likely(eaction->tv_sec != शून्य)) अणु
		काष्ठा बारpec64 ts;

		kसमय_get_ts64(&ts);
		/* monotonic समय, so no y2038 overflow */
		*eaction->tv_sec = ts.tv_sec;
		*eaction->tv_usec = ts.tv_nsec / NSEC_PER_USEC;
	पूर्ण

	drm_send_event_locked(dev, eaction->event);
	eaction->event = शून्य;
	spin_unlock_irq(&dev->event_lock);
पूर्ण

/**
 * vmw_event_fence_action_cleanup
 *
 * @action: The काष्ठा vmw_fence_action embedded in a काष्ठा
 * vmw_event_fence_action.
 *
 * This function is the काष्ठा vmw_fence_action deकाष्ठाor. It's typically
 * called from a workqueue.
 */
अटल व्योम vmw_event_fence_action_cleanup(काष्ठा vmw_fence_action *action)
अणु
	काष्ठा vmw_event_fence_action *eaction =
		container_of(action, काष्ठा vmw_event_fence_action, action);

	vmw_fence_obj_unreference(&eaction->fence);
	kमुक्त(eaction);
पूर्ण


/**
 * vmw_fence_obj_add_action - Add an action to a fence object.
 *
 * @fence: The fence object.
 * @action: The action to add.
 *
 * Note that the action callbacks may be executed beक्रमe this function
 * वापसs.
 */
अटल व्योम vmw_fence_obj_add_action(काष्ठा vmw_fence_obj *fence,
			      काष्ठा vmw_fence_action *action)
अणु
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);
	bool run_update = false;

	mutex_lock(&fman->goal_irq_mutex);
	spin_lock(&fman->lock);

	fman->pending_actions[action->type]++;
	अगर (dma_fence_is_संकेतed_locked(&fence->base)) अणु
		काष्ठा list_head action_list;

		INIT_LIST_HEAD(&action_list);
		list_add_tail(&action->head, &action_list);
		vmw_fences_perक्रमm_actions(fman, &action_list);
	पूर्ण अन्यथा अणु
		list_add_tail(&action->head, &fence->seq_passed_actions);

		/*
		 * This function may set fman::seqno_valid, so it must
		 * be run with the goal_irq_mutex held.
		 */
		run_update = vmw_fence_goal_check_locked(fence);
	पूर्ण

	spin_unlock(&fman->lock);

	अगर (run_update) अणु
		अगर (!fman->goal_irq_on) अणु
			fman->goal_irq_on = true;
			vmw_goal_रुकोer_add(fman->dev_priv);
		पूर्ण
		vmw_fences_update(fman);
	पूर्ण
	mutex_unlock(&fman->goal_irq_mutex);

पूर्ण

/**
 * vmw_event_fence_action_create - Post an event क्रम sending when a fence
 * object seqno has passed.
 *
 * @file_priv: The file connection on which the event should be posted.
 * @fence: The fence object on which to post the event.
 * @event: Event to be posted. This event should've been alloced
 * using k[mz]alloc, and should've been completely initialized.
 * @tv_sec: If non-null, the variable poपूर्णांकed to will be asचिन्हित
 * current समय tv_sec val when the fence संकेतs.
 * @tv_usec: Must be set अगर @tv_sec is set, and the variable poपूर्णांकed to will
 * be asचिन्हित the current समय tv_usec val when the fence संकेतs.
 * @पूर्णांकerruptible: Interruptible रुकोs अगर possible.
 *
 * As a side effect, the object poपूर्णांकed to by @event may have been
 * मुक्तd when this function वापसs. If this function वापसs with
 * an error code, the caller needs to मुक्त that object.
 */

पूर्णांक vmw_event_fence_action_queue(काष्ठा drm_file *file_priv,
				 काष्ठा vmw_fence_obj *fence,
				 काष्ठा drm_pending_event *event,
				 uपूर्णांक32_t *tv_sec,
				 uपूर्णांक32_t *tv_usec,
				 bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_event_fence_action *eaction;
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);

	eaction = kzalloc(माप(*eaction), GFP_KERNEL);
	अगर (unlikely(!eaction))
		वापस -ENOMEM;

	eaction->event = event;

	eaction->action.seq_passed = vmw_event_fence_action_seq_passed;
	eaction->action.cleanup = vmw_event_fence_action_cleanup;
	eaction->action.type = VMW_ACTION_EVENT;

	eaction->fence = vmw_fence_obj_reference(fence);
	eaction->dev = &fman->dev_priv->drm;
	eaction->tv_sec = tv_sec;
	eaction->tv_usec = tv_usec;

	vmw_fence_obj_add_action(fence, &eaction->action);

	वापस 0;
पूर्ण

काष्ठा vmw_event_fence_pending अणु
	काष्ठा drm_pending_event base;
	काष्ठा drm_vmw_event_fence event;
पूर्ण;

अटल पूर्णांक vmw_event_fence_action_create(काष्ठा drm_file *file_priv,
				  काष्ठा vmw_fence_obj *fence,
				  uपूर्णांक32_t flags,
				  uपूर्णांक64_t user_data,
				  bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_event_fence_pending *event;
	काष्ठा vmw_fence_manager *fman = fman_from_fence(fence);
	काष्ठा drm_device *dev = &fman->dev_priv->drm;
	पूर्णांक ret;

	event = kzalloc(माप(*event), GFP_KERNEL);
	अगर (unlikely(!event)) अणु
		DRM_ERROR("Failed to allocate an event.\n");
		ret = -ENOMEM;
		जाओ out_no_space;
	पूर्ण

	event->event.base.type = DRM_VMW_EVENT_FENCE_SIGNALED;
	event->event.base.length = माप(*event);
	event->event.user_data = user_data;

	ret = drm_event_reserve_init(dev, file_priv, &event->base, &event->event.base);

	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to allocate event space for this file.\n");
		kमुक्त(event);
		जाओ out_no_space;
	पूर्ण

	अगर (flags & DRM_VMW_FE_FLAG_REQ_TIME)
		ret = vmw_event_fence_action_queue(file_priv, fence,
						   &event->base,
						   &event->event.tv_sec,
						   &event->event.tv_usec,
						   पूर्णांकerruptible);
	अन्यथा
		ret = vmw_event_fence_action_queue(file_priv, fence,
						   &event->base,
						   शून्य,
						   शून्य,
						   पूर्णांकerruptible);
	अगर (ret != 0)
		जाओ out_no_queue;

	वापस 0;

out_no_queue:
	drm_event_cancel_मुक्त(dev, &event->base);
out_no_space:
	वापस ret;
पूर्ण

पूर्णांक vmw_fence_event_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_vmw_fence_event_arg *arg =
		(काष्ठा drm_vmw_fence_event_arg *) data;
	काष्ठा vmw_fence_obj *fence = शून्य;
	काष्ठा vmw_fpriv *vmw_fp = vmw_fpriv(file_priv);
	काष्ठा tपंचांग_object_file *tfile = vmw_fp->tfile;
	काष्ठा drm_vmw_fence_rep __user *user_fence_rep =
		(काष्ठा drm_vmw_fence_rep __user *)(अचिन्हित दीर्घ)
		arg->fence_rep;
	uपूर्णांक32_t handle;
	पूर्णांक ret;

	/*
	 * Look up an existing fence object,
	 * and अगर user-space wants a new reference,
	 * add one.
	 */
	अगर (arg->handle) अणु
		काष्ठा tपंचांग_base_object *base =
			vmw_fence_obj_lookup(tfile, arg->handle);

		अगर (IS_ERR(base))
			वापस PTR_ERR(base);

		fence = &(container_of(base, काष्ठा vmw_user_fence,
				       base)->fence);
		(व्योम) vmw_fence_obj_reference(fence);

		अगर (user_fence_rep != शून्य) अणु
			ret = tपंचांग_ref_object_add(vmw_fp->tfile, base,
						 TTM_REF_USAGE, शून्य, false);
			अगर (unlikely(ret != 0)) अणु
				DRM_ERROR("Failed to reference a fence "
					  "object.\n");
				जाओ out_no_ref_obj;
			पूर्ण
			handle = base->handle;
		पूर्ण
		tपंचांग_base_object_unref(&base);
	पूर्ण

	/*
	 * Create a new fence object.
	 */
	अगर (!fence) अणु
		ret = vmw_execbuf_fence_commands(file_priv, dev_priv,
						 &fence,
						 (user_fence_rep) ?
						 &handle : शून्य);
		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Fence event failed to create fence.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	BUG_ON(fence == शून्य);

	ret = vmw_event_fence_action_create(file_priv, fence,
					    arg->flags,
					    arg->user_data,
					    true);
	अगर (unlikely(ret != 0)) अणु
		अगर (ret != -ERESTARTSYS)
			DRM_ERROR("Failed to attach event to fence.\n");
		जाओ out_no_create;
	पूर्ण

	vmw_execbuf_copy_fence_user(dev_priv, vmw_fp, 0, user_fence_rep, fence,
				    handle, -1, शून्य);
	vmw_fence_obj_unreference(&fence);
	वापस 0;
out_no_create:
	अगर (user_fence_rep != शून्य)
		tपंचांग_ref_object_base_unref(tfile, handle, TTM_REF_USAGE);
out_no_ref_obj:
	vmw_fence_obj_unreference(&fence);
	वापस ret;
पूर्ण
