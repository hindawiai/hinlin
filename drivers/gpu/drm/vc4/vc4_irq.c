<शैली गुरु>
/*
 * Copyright तऊ 2014 Broadcom
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/**
 * DOC: Interrupt management क्रम the V3D engine
 *
 * We have an पूर्णांकerrupt status रेजिस्टर (V3D_INTCTL) which reports
 * पूर्णांकerrupts, and where writing 1 bits clears those पूर्णांकerrupts.
 * There are also a pair of पूर्णांकerrupt रेजिस्टरs
 * (V3D_INTENA/V3D_INTDIS) where writing a 1 to their bits enables or
 * disables that specअगरic पूर्णांकerrupt, and 0s written are ignored
 * (पढ़ोing either one वापसs the set of enabled पूर्णांकerrupts).
 *
 * When we take a binning flush करोne पूर्णांकerrupt, we need to submit the
 * next frame क्रम binning and move the finished frame to the render
 * thपढ़ो.
 *
 * When we take a render frame पूर्णांकerrupt, we need to wake the
 * processes रुकोing क्रम some frame to be करोne, and get the next frame
 * submitted ASAP (so the hardware करोesn't sit idle when there's work
 * to करो).
 *
 * When we take the binner out of memory पूर्णांकerrupt, we need to
 * allocate some new memory and pass it to the binner so that the
 * current job can make progress.
 */

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

#घोषणा V3D_DRIVER_IRQS (V3D_INT_OUTOMEM | \
			 V3D_INT_FLDONE | \
			 V3D_INT_FRDONE)

DECLARE_WAIT_QUEUE_HEAD(render_रुको);

अटल व्योम
vc4_overflow_mem_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc4_dev *vc4 =
		container_of(work, काष्ठा vc4_dev, overflow_mem_work);
	काष्ठा vc4_bo *bo;
	पूर्णांक bin_bo_slot;
	काष्ठा vc4_exec_info *exec;
	अचिन्हित दीर्घ irqflags;

	mutex_lock(&vc4->bin_bo_lock);

	अगर (!vc4->bin_bo)
		जाओ complete;

	bo = vc4->bin_bo;

	bin_bo_slot = vc4_v3d_get_bin_slot(vc4);
	अगर (bin_bo_slot < 0) अणु
		DRM_ERROR("Couldn't allocate binner overflow mem\n");
		जाओ complete;
	पूर्ण

	spin_lock_irqsave(&vc4->job_lock, irqflags);

	अगर (vc4->bin_alloc_overflow) अणु
		/* If we had overflow memory allocated previously,
		 * then that chunk will मुक्त when the current bin job
		 * is करोne.  If we करोn't have a bin job running, then
		 * the chunk will be करोne whenever the list of render
		 * jobs has drained.
		 */
		exec = vc4_first_bin_job(vc4);
		अगर (!exec)
			exec = vc4_last_render_job(vc4);
		अगर (exec) अणु
			exec->bin_slots |= vc4->bin_alloc_overflow;
		पूर्ण अन्यथा अणु
			/* There's nothing queued in the hardware, so
			 * the old slot is मुक्त immediately.
			 */
			vc4->bin_alloc_used &= ~vc4->bin_alloc_overflow;
		पूर्ण
	पूर्ण
	vc4->bin_alloc_overflow = BIT(bin_bo_slot);

	V3D_WRITE(V3D_BPOA, bo->base.paddr + bin_bo_slot * vc4->bin_alloc_size);
	V3D_WRITE(V3D_BPOS, bo->base.base.size);
	V3D_WRITE(V3D_INTCTL, V3D_INT_OUTOMEM);
	V3D_WRITE(V3D_INTENA, V3D_INT_OUTOMEM);
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

complete:
	mutex_unlock(&vc4->bin_bo_lock);
पूर्ण

अटल व्योम
vc4_irq_finish_bin_job(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *next, *exec = vc4_first_bin_job(vc4);

	अगर (!exec)
		वापस;

	vc4_move_job_to_render(dev, exec);
	next = vc4_first_bin_job(vc4);

	/* Only submit the next job in the bin list अगर it matches the perfmon
	 * attached to the one that just finished (or अगर both jobs करोn't have
	 * perfmon attached to them).
	 */
	अगर (next && next->perfmon == exec->perfmon)
		vc4_submit_next_bin_job(dev);
पूर्ण

अटल व्योम
vc4_cancel_bin_job(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *exec = vc4_first_bin_job(vc4);

	अगर (!exec)
		वापस;

	/* Stop the perfmon so that the next bin job can be started. */
	अगर (exec->perfmon)
		vc4_perfmon_stop(vc4, exec->perfmon, false);

	list_move_tail(&exec->head, &vc4->bin_job_list);
	vc4_submit_next_bin_job(dev);
पूर्ण

अटल व्योम
vc4_irq_finish_render_job(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *exec = vc4_first_render_job(vc4);
	काष्ठा vc4_exec_info *nextbin, *nextrender;

	अगर (!exec)
		वापस;

	vc4->finished_seqno++;
	list_move_tail(&exec->head, &vc4->job_करोne_list);

	nextbin = vc4_first_bin_job(vc4);
	nextrender = vc4_first_render_job(vc4);

	/* Only stop the perfmon अगर following jobs in the queue करोn't expect it
	 * to be enabled.
	 */
	अगर (exec->perfmon && !nextrender &&
	    (!nextbin || nextbin->perfmon != exec->perfmon))
		vc4_perfmon_stop(vc4, exec->perfmon, true);

	/* If there's a render job रुकोing, start it. If this is not the हाल
	 * we may have to unblock the binner अगर it's been stalled because of
	 * perfmon (this can be checked by comparing the perfmon attached to
	 * the finished renderjob to the one attached to the next bin job: अगर
	 * they करोn't match, this means the binner is stalled and should be
	 * restarted).
	 */
	अगर (nextrender)
		vc4_submit_next_render_job(dev);
	अन्यथा अगर (nextbin && nextbin->perfmon != exec->perfmon)
		vc4_submit_next_bin_job(dev);

	अगर (exec->fence) अणु
		dma_fence_संकेत_locked(exec->fence);
		dma_fence_put(exec->fence);
		exec->fence = शून्य;
	पूर्ण

	wake_up_all(&vc4->job_रुको_queue);
	schedule_work(&vc4->job_करोne_work);
पूर्ण

irqवापस_t
vc4_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = arg;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	uपूर्णांक32_t पूर्णांकctl;
	irqवापस_t status = IRQ_NONE;

	barrier();
	पूर्णांकctl = V3D_READ(V3D_INTCTL);

	/* Acknowledge the पूर्णांकerrupts we're handling here. The binner
	 * last flush / render frame करोne पूर्णांकerrupt will be cleared,
	 * जबतक OUTOMEM will stay high until the underlying cause is
	 * cleared.
	 */
	V3D_WRITE(V3D_INTCTL, पूर्णांकctl);

	अगर (पूर्णांकctl & V3D_INT_OUTOMEM) अणु
		/* Disable OUTOMEM until the work is करोne. */
		V3D_WRITE(V3D_INTDIS, V3D_INT_OUTOMEM);
		schedule_work(&vc4->overflow_mem_work);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकctl & V3D_INT_FLDONE) अणु
		spin_lock(&vc4->job_lock);
		vc4_irq_finish_bin_job(dev);
		spin_unlock(&vc4->job_lock);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकctl & V3D_INT_FRDONE) अणु
		spin_lock(&vc4->job_lock);
		vc4_irq_finish_render_job(dev);
		spin_unlock(&vc4->job_lock);
		status = IRQ_HANDLED;
	पूर्ण

	वापस status;
पूर्ण

व्योम
vc4_irq_preinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	अगर (!vc4->v3d)
		वापस;

	init_रुकोqueue_head(&vc4->job_रुको_queue);
	INIT_WORK(&vc4->overflow_mem_work, vc4_overflow_mem_work);

	/* Clear any pending पूर्णांकerrupts someone might have left around
	 * क्रम us.
	 */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);
पूर्ण

पूर्णांक
vc4_irq_postinstall(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	अगर (!vc4->v3d)
		वापस 0;

	/* Enable the render करोne पूर्णांकerrupts. The out-of-memory पूर्णांकerrupt is
	 * enabled as soon as we have a binner BO allocated.
	 */
	V3D_WRITE(V3D_INTENA, V3D_INT_FLDONE | V3D_INT_FRDONE);

	वापस 0;
पूर्ण

व्योम
vc4_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	अगर (!vc4->v3d)
		वापस;

	/* Disable sending पूर्णांकerrupts क्रम our driver's IRQs. */
	V3D_WRITE(V3D_INTDIS, V3D_DRIVER_IRQS);

	/* Clear any pending पूर्णांकerrupts we might have left. */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);

	/* Finish any पूर्णांकerrupt handler still in flight. */
	disable_irq(dev->irq);

	cancel_work_sync(&vc4->overflow_mem_work);
पूर्ण

/** Reinitializes पूर्णांकerrupt रेजिस्टरs when a GPU reset is perक्रमmed. */
व्योम vc4_irq_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	अचिन्हित दीर्घ irqflags;

	/* Acknowledge any stale IRQs. */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);

	/*
	 * Turn all our पूर्णांकerrupts on.  Binner out of memory is the
	 * only one we expect to trigger at this poपूर्णांक, since we've
	 * just come from घातeron and haven't supplied any overflow
	 * memory yet.
	 */
	V3D_WRITE(V3D_INTENA, V3D_DRIVER_IRQS);

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	vc4_cancel_bin_job(dev);
	vc4_irq_finish_render_job(dev);
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);
पूर्ण
