<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
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

#घोषणा VMW_FENCE_WRAP (1 << 24)

/**
 * vmw_thपढ़ो_fn - Deferred (process context) irq handler
 *
 * @irq: irq number
 * @arg: Closure argument. Poपूर्णांकer to a काष्ठा drm_device cast to व्योम *
 *
 * This function implements the deferred part of irq processing.
 * The function is guaranteed to run at least once after the
 * vmw_irq_handler has वापसed with IRQ_WAKE_THREAD.
 *
 */
अटल irqवापस_t vmw_thपढ़ो_fn(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *)arg;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	irqवापस_t ret = IRQ_NONE;

	अगर (test_and_clear_bit(VMW_IRQTHREAD_FENCE,
			       dev_priv->irqthपढ़ो_pending)) अणु
		vmw_fences_update(dev_priv->fman);
		wake_up_all(&dev_priv->fence_queue);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (test_and_clear_bit(VMW_IRQTHREAD_CMDBUF,
			       dev_priv->irqthपढ़ो_pending)) अणु
		vmw_cmdbuf_irqthपढ़ो(dev_priv->cman);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vmw_irq_handler irq handler
 *
 * @irq: irq number
 * @arg: Closure argument. Poपूर्णांकer to a काष्ठा drm_device cast to व्योम *
 *
 * This function implements the quick part of irq processing.
 * The function perक्रमms fast actions like clearing the device पूर्णांकerrupt
 * flags and also reasonably quick actions like waking processes रुकोing क्रम
 * FIFO space. Other IRQ actions are deferred to the IRQ thपढ़ो.
 */
अटल irqवापस_t vmw_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *)arg;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	uपूर्णांक32_t status, masked_status;
	irqवापस_t ret = IRQ_HANDLED;

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	masked_status = status & READ_ONCE(dev_priv->irq_mask);

	अगर (likely(status))
		outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);

	अगर (!status)
		वापस IRQ_NONE;

	अगर (masked_status & SVGA_IRQFLAG_FIFO_PROGRESS)
		wake_up_all(&dev_priv->fअगरo_queue);

	अगर ((masked_status & (SVGA_IRQFLAG_ANY_FENCE |
			      SVGA_IRQFLAG_FENCE_GOAL)) &&
	    !test_and_set_bit(VMW_IRQTHREAD_FENCE, dev_priv->irqthपढ़ो_pending))
		ret = IRQ_WAKE_THREAD;

	अगर ((masked_status & (SVGA_IRQFLAG_COMMAND_BUFFER |
			      SVGA_IRQFLAG_ERROR)) &&
	    !test_and_set_bit(VMW_IRQTHREAD_CMDBUF,
			      dev_priv->irqthपढ़ो_pending))
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल bool vmw_fअगरo_idle(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t seqno)
अणु

	वापस (vmw_पढ़ो(dev_priv, SVGA_REG_BUSY) == 0);
पूर्ण

व्योम vmw_update_seqno(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_fअगरo_state *fअगरo_state)
अणु
	uपूर्णांक32_t seqno = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_FENCE);

	अगर (dev_priv->last_पढ़ो_seqno != seqno) अणु
		dev_priv->last_पढ़ो_seqno = seqno;
		vmw_fences_update(dev_priv->fman);
	पूर्ण
पूर्ण

bool vmw_seqno_passed(काष्ठा vmw_निजी *dev_priv,
			 uपूर्णांक32_t seqno)
अणु
	काष्ठा vmw_fअगरo_state *fअगरo_state;
	bool ret;

	अगर (likely(dev_priv->last_पढ़ो_seqno - seqno < VMW_FENCE_WRAP))
		वापस true;

	fअगरo_state = &dev_priv->fअगरo;
	vmw_update_seqno(dev_priv, fअगरo_state);
	अगर (likely(dev_priv->last_पढ़ो_seqno - seqno < VMW_FENCE_WRAP))
		वापस true;

	अगर (!(fअगरo_state->capabilities & SVGA_FIFO_CAP_FENCE) &&
	    vmw_fअगरo_idle(dev_priv, seqno))
		वापस true;

	/**
	 * Then check अगर the seqno is higher than what we've actually
	 * emitted. Then the fence is stale and संकेतed.
	 */

	ret = ((atomic_पढ़ो(&dev_priv->marker_seq) - seqno)
	       > VMW_FENCE_WRAP);

	वापस ret;
पूर्ण

पूर्णांक vmw_fallback_रुको(काष्ठा vmw_निजी *dev_priv,
		      bool lazy,
		      bool fअगरo_idle,
		      uपूर्णांक32_t seqno,
		      bool पूर्णांकerruptible,
		      अचिन्हित दीर्घ समयout)
अणु
	काष्ठा vmw_fअगरo_state *fअगरo_state = &dev_priv->fअगरo;

	uपूर्णांक32_t count = 0;
	uपूर्णांक32_t संकेत_seq;
	पूर्णांक ret;
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + समयout;
	bool (*रुको_condition)(काष्ठा vmw_निजी *, uपूर्णांक32_t);
	DEFINE_WAIT(__रुको);

	रुको_condition = (fअगरo_idle) ? &vmw_fअगरo_idle :
		&vmw_seqno_passed;

	/**
	 * Block command submission जबतक रुकोing क्रम idle.
	 */

	अगर (fअगरo_idle) अणु
		करोwn_पढ़ो(&fअगरo_state->rwsem);
		अगर (dev_priv->cman) अणु
			ret = vmw_cmdbuf_idle(dev_priv->cman, पूर्णांकerruptible,
					      10*HZ);
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण

	संकेत_seq = atomic_पढ़ो(&dev_priv->marker_seq);
	ret = 0;

	क्रम (;;) अणु
		prepare_to_रुको(&dev_priv->fence_queue, &__रुको,
				(पूर्णांकerruptible) ?
				TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		अगर (रुको_condition(dev_priv, seqno))
			अवरोध;
		अगर (समय_after_eq(jअगरfies, end_jअगरfies)) अणु
			DRM_ERROR("SVGA device lockup.\n");
			अवरोध;
		पूर्ण
		अगर (lazy)
			schedule_समयout(1);
		अन्यथा अगर ((++count & 0x0F) == 0) अणु
			/**
			 * FIXME: Use schedule_hr_समयout here क्रम
			 * newer kernels and lower CPU utilization.
			 */

			__set_current_state(TASK_RUNNING);
			schedule();
			__set_current_state((पूर्णांकerruptible) ?
					    TASK_INTERRUPTIBLE :
					    TASK_UNINTERRUPTIBLE);
		पूर्ण
		अगर (पूर्णांकerruptible && संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण
	finish_रुको(&dev_priv->fence_queue, &__रुको);
	अगर (ret == 0 && fअगरo_idle)
		vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_FENCE, संकेत_seq);

	wake_up_all(&dev_priv->fence_queue);
out_err:
	अगर (fअगरo_idle)
		up_पढ़ो(&fअगरo_state->rwsem);

	वापस ret;
पूर्ण

व्योम vmw_generic_रुकोer_add(काष्ठा vmw_निजी *dev_priv,
			    u32 flag, पूर्णांक *रुकोer_count)
अणु
	spin_lock_bh(&dev_priv->रुकोer_lock);
	अगर ((*रुकोer_count)++ == 0) अणु
		outl(flag, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
		dev_priv->irq_mask |= flag;
		vmw_ग_लिखो(dev_priv, SVGA_REG_IRQMASK, dev_priv->irq_mask);
	पूर्ण
	spin_unlock_bh(&dev_priv->रुकोer_lock);
पूर्ण

व्योम vmw_generic_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv,
			       u32 flag, पूर्णांक *रुकोer_count)
अणु
	spin_lock_bh(&dev_priv->रुकोer_lock);
	अगर (--(*रुकोer_count) == 0) अणु
		dev_priv->irq_mask &= ~flag;
		vmw_ग_लिखो(dev_priv, SVGA_REG_IRQMASK, dev_priv->irq_mask);
	पूर्ण
	spin_unlock_bh(&dev_priv->रुकोer_lock);
पूर्ण

व्योम vmw_seqno_रुकोer_add(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_generic_रुकोer_add(dev_priv, SVGA_IRQFLAG_ANY_FENCE,
			       &dev_priv->fence_queue_रुकोers);
पूर्ण

व्योम vmw_seqno_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_generic_रुकोer_हटाओ(dev_priv, SVGA_IRQFLAG_ANY_FENCE,
				  &dev_priv->fence_queue_रुकोers);
पूर्ण

व्योम vmw_goal_रुकोer_add(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_generic_रुकोer_add(dev_priv, SVGA_IRQFLAG_FENCE_GOAL,
			       &dev_priv->goal_queue_रुकोers);
पूर्ण

व्योम vmw_goal_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv)
अणु
	vmw_generic_रुकोer_हटाओ(dev_priv, SVGA_IRQFLAG_FENCE_GOAL,
				  &dev_priv->goal_queue_रुकोers);
पूर्ण

पूर्णांक vmw_रुको_seqno(काष्ठा vmw_निजी *dev_priv,
		      bool lazy, uपूर्णांक32_t seqno,
		      bool पूर्णांकerruptible, अचिन्हित दीर्घ समयout)
अणु
	दीर्घ ret;
	काष्ठा vmw_fअगरo_state *fअगरo = &dev_priv->fअगरo;

	अगर (likely(dev_priv->last_पढ़ो_seqno - seqno < VMW_FENCE_WRAP))
		वापस 0;

	अगर (likely(vmw_seqno_passed(dev_priv, seqno)))
		वापस 0;

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);

	अगर (!(fअगरo->capabilities & SVGA_FIFO_CAP_FENCE))
		वापस vmw_fallback_रुको(dev_priv, lazy, true, seqno,
					 पूर्णांकerruptible, समयout);

	अगर (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		वापस vmw_fallback_रुको(dev_priv, lazy, false, seqno,
					 पूर्णांकerruptible, समयout);

	vmw_seqno_रुकोer_add(dev_priv);

	अगर (पूर्णांकerruptible)
		ret = रुको_event_पूर्णांकerruptible_समयout
		    (dev_priv->fence_queue,
		     vmw_seqno_passed(dev_priv, seqno),
		     समयout);
	अन्यथा
		ret = रुको_event_समयout
		    (dev_priv->fence_queue,
		     vmw_seqno_passed(dev_priv, seqno),
		     समयout);

	vmw_seqno_रुकोer_हटाओ(dev_priv);

	अगर (unlikely(ret == 0))
		ret = -EBUSY;
	अन्यथा अगर (likely(ret > 0))
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम vmw_irq_preinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	uपूर्णांक32_t status;

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
पूर्ण

व्योम vmw_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	uपूर्णांक32_t status;

	अगर (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		वापस;

	अगर (!dev->irq_enabled)
		वापस;

	vmw_ग_लिखो(dev_priv, SVGA_REG_IRQMASK, 0);

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);

	dev->irq_enabled = false;
	मुक्त_irq(dev->irq, dev);
पूर्ण

/**
 * vmw_irq_install - Install the irq handlers
 *
 * @dev:  Poपूर्णांकer to the drm device.
 * @irq:  The irq number.
 * Return:  Zero अगर successful. Negative number otherwise.
 */
पूर्णांक vmw_irq_install(काष्ठा drm_device *dev, पूर्णांक irq)
अणु
	पूर्णांक ret;

	अगर (dev->irq_enabled)
		वापस -EBUSY;

	vmw_irq_preinstall(dev);

	ret = request_thपढ़ोed_irq(irq, vmw_irq_handler, vmw_thपढ़ो_fn,
				   IRQF_SHARED, VMWGFX_DRIVER_NAME, dev);
	अगर (ret < 0)
		वापस ret;

	dev->irq_enabled = true;
	dev->irq = irq;

	वापस ret;
पूर्ण
