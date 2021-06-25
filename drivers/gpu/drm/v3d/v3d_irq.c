<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2014-2018 Broadcom */

/**
 * DOC: Interrupt management क्रम the V3D engine
 *
 * When we take a bin, render, TFU करोne, or CSD करोne पूर्णांकerrupt, we
 * need to संकेत the fence क्रम that job so that the scheduler can
 * queue up the next one and unblock any रुकोers.
 *
 * When we take the binner out of memory पूर्णांकerrupt, we need to
 * allocate some new memory and pass it to the binner so that the
 * current job can make progress.
 */

#समावेश <linux/platक्रमm_device.h>

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"
#समावेश "v3d_trace.h"

#घोषणा V3D_CORE_IRQS ((u32)(V3D_INT_OUTOMEM |	\
			     V3D_INT_FLDONE |	\
			     V3D_INT_FRDONE |	\
			     V3D_INT_CSDDONE |	\
			     V3D_INT_GMPV))

#घोषणा V3D_HUB_IRQS ((u32)(V3D_HUB_INT_MMU_WRV |	\
			    V3D_HUB_INT_MMU_PTI |	\
			    V3D_HUB_INT_MMU_CAP |	\
			    V3D_HUB_INT_TFUC))

अटल irqवापस_t
v3d_hub_irq(पूर्णांक irq, व्योम *arg);

अटल व्योम
v3d_overflow_mem_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा v3d_dev *v3d =
		container_of(work, काष्ठा v3d_dev, overflow_mem_work);
	काष्ठा drm_device *dev = &v3d->drm;
	काष्ठा v3d_bo *bo = v3d_bo_create(dev, शून्य /* XXX: GMP */, 256 * 1024);
	काष्ठा drm_gem_object *obj;
	अचिन्हित दीर्घ irqflags;

	अगर (IS_ERR(bo)) अणु
		DRM_ERROR("Couldn't allocate binner overflow mem\n");
		वापस;
	पूर्ण
	obj = &bo->base.base;

	/* We lost a race, and our work task came in after the bin job
	 * completed and निकासed.  This can happen because the HW
	 * संकेतs OOM beक्रमe it's fully OOM, so the binner might just
	 * barely complete.
	 *
	 * If we lose the race and our work task comes in after a new
	 * bin job got scheduled, that's fine.  We'll just give them
	 * some binner pool anyway.
	 */
	spin_lock_irqsave(&v3d->job_lock, irqflags);
	अगर (!v3d->bin_job) अणु
		spin_unlock_irqrestore(&v3d->job_lock, irqflags);
		जाओ out;
	पूर्ण

	drm_gem_object_get(obj);
	list_add_tail(&bo->unref_head, &v3d->bin_job->render->unref_list);
	spin_unlock_irqrestore(&v3d->job_lock, irqflags);

	V3D_CORE_WRITE(0, V3D_PTB_BPOA, bo->node.start << PAGE_SHIFT);
	V3D_CORE_WRITE(0, V3D_PTB_BPOS, obj->size);

out:
	drm_gem_object_put(obj);
पूर्ण

अटल irqवापस_t
v3d_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा v3d_dev *v3d = arg;
	u32 पूर्णांकsts;
	irqवापस_t status = IRQ_NONE;

	पूर्णांकsts = V3D_CORE_READ(0, V3D_CTL_INT_STS);

	/* Acknowledge the पूर्णांकerrupts we're handling here. */
	V3D_CORE_WRITE(0, V3D_CTL_INT_CLR, पूर्णांकsts);

	अगर (पूर्णांकsts & V3D_INT_OUTOMEM) अणु
		/* Note that the OOM status is edge संकेतed, so the
		 * पूर्णांकerrupt won't happen again until the we actually
		 * add more memory.  Also, as of V3D 4.1, FLDONE won't
		 * be reported until any OOM state has been cleared.
		 */
		schedule_work(&v3d->overflow_mem_work);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकsts & V3D_INT_FLDONE) अणु
		काष्ठा v3d_fence *fence =
			to_v3d_fence(v3d->bin_job->base.irq_fence);

		trace_v3d_bcl_irq(&v3d->drm, fence->seqno);
		dma_fence_संकेत(&fence->base);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकsts & V3D_INT_FRDONE) अणु
		काष्ठा v3d_fence *fence =
			to_v3d_fence(v3d->render_job->base.irq_fence);

		trace_v3d_rcl_irq(&v3d->drm, fence->seqno);
		dma_fence_संकेत(&fence->base);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकsts & V3D_INT_CSDDONE) अणु
		काष्ठा v3d_fence *fence =
			to_v3d_fence(v3d->csd_job->base.irq_fence);

		trace_v3d_csd_irq(&v3d->drm, fence->seqno);
		dma_fence_संकेत(&fence->base);
		status = IRQ_HANDLED;
	पूर्ण

	/* We shouldn't be triggering these अगर we have GMP in
	 * always-allowed mode.
	 */
	अगर (पूर्णांकsts & V3D_INT_GMPV)
		dev_err(v3d->drm.dev, "GMP violation\n");

	/* V3D 4.2 wires the hub and core IRQs together, so अगर we &
	 * didn't see the common one then check hub क्रम MMU IRQs.
	 */
	अगर (v3d->single_irq_line && status == IRQ_NONE)
		वापस v3d_hub_irq(irq, arg);

	वापस status;
पूर्ण

अटल irqवापस_t
v3d_hub_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा v3d_dev *v3d = arg;
	u32 पूर्णांकsts;
	irqवापस_t status = IRQ_NONE;

	पूर्णांकsts = V3D_READ(V3D_HUB_INT_STS);

	/* Acknowledge the पूर्णांकerrupts we're handling here. */
	V3D_WRITE(V3D_HUB_INT_CLR, पूर्णांकsts);

	अगर (पूर्णांकsts & V3D_HUB_INT_TFUC) अणु
		काष्ठा v3d_fence *fence =
			to_v3d_fence(v3d->tfu_job->base.irq_fence);

		trace_v3d_tfu_irq(&v3d->drm, fence->seqno);
		dma_fence_संकेत(&fence->base);
		status = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकsts & (V3D_HUB_INT_MMU_WRV |
		      V3D_HUB_INT_MMU_PTI |
		      V3D_HUB_INT_MMU_CAP)) अणु
		u32 axi_id = V3D_READ(V3D_MMU_VIO_ID);
		u64 vio_addr = ((u64)V3D_READ(V3D_MMU_VIO_ADDR) <<
				(v3d->va_width - 32));
		अटल स्थिर अक्षर *स्थिर v3d41_axi_ids[] = अणु
			"L2T",
			"PTB",
			"PSE",
			"TLB",
			"CLE",
			"TFU",
			"MMU",
			"GMP",
		पूर्ण;
		स्थिर अक्षर *client = "?";

		V3D_WRITE(V3D_MMU_CTL, V3D_READ(V3D_MMU_CTL));

		अगर (v3d->ver >= 41) अणु
			axi_id = axi_id >> 5;
			अगर (axi_id < ARRAY_SIZE(v3d41_axi_ids))
				client = v3d41_axi_ids[axi_id];
		पूर्ण

		dev_err(v3d->drm.dev, "MMU error from client %s (%d) at 0x%llx%s%s%s\n",
			client, axi_id, (दीर्घ दीर्घ)vio_addr,
			((पूर्णांकsts & V3D_HUB_INT_MMU_WRV) ?
			 ", write violation" : ""),
			((पूर्णांकsts & V3D_HUB_INT_MMU_PTI) ?
			 ", pte invalid" : ""),
			((पूर्णांकsts & V3D_HUB_INT_MMU_CAP) ?
			 ", cap exceeded" : ""));
		status = IRQ_HANDLED;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक
v3d_irq_init(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक irq1, ret, core;

	INIT_WORK(&v3d->overflow_mem_work, v3d_overflow_mem_work);

	/* Clear any pending पूर्णांकerrupts someone might have left around
	 * क्रम us.
	 */
	क्रम (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_CLR, V3D_CORE_IRQS);
	V3D_WRITE(V3D_HUB_INT_CLR, V3D_HUB_IRQS);

	irq1 = platक्रमm_get_irq_optional(v3d_to_pdev(v3d), 1);
	अगर (irq1 == -EPROBE_DEFER)
		वापस irq1;
	अगर (irq1 > 0) अणु
		ret = devm_request_irq(v3d->drm.dev, irq1,
				       v3d_irq, IRQF_SHARED,
				       "v3d_core0", v3d);
		अगर (ret)
			जाओ fail;
		ret = devm_request_irq(v3d->drm.dev,
				       platक्रमm_get_irq(v3d_to_pdev(v3d), 0),
				       v3d_hub_irq, IRQF_SHARED,
				       "v3d_hub", v3d);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		v3d->single_irq_line = true;

		ret = devm_request_irq(v3d->drm.dev,
				       platक्रमm_get_irq(v3d_to_pdev(v3d), 0),
				       v3d_irq, IRQF_SHARED,
				       "v3d", v3d);
		अगर (ret)
			जाओ fail;
	पूर्ण

	v3d_irq_enable(v3d);
	वापस 0;

fail:
	अगर (ret != -EPROBE_DEFER)
		dev_err(v3d->drm.dev, "IRQ setup failed: %d\n", ret);
	वापस ret;
पूर्ण

व्योम
v3d_irq_enable(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक core;

	/* Enable our set of पूर्णांकerrupts, masking out any others. */
	क्रम (core = 0; core < v3d->cores; core++) अणु
		V3D_CORE_WRITE(core, V3D_CTL_INT_MSK_SET, ~V3D_CORE_IRQS);
		V3D_CORE_WRITE(core, V3D_CTL_INT_MSK_CLR, V3D_CORE_IRQS);
	पूर्ण

	V3D_WRITE(V3D_HUB_INT_MSK_SET, ~V3D_HUB_IRQS);
	V3D_WRITE(V3D_HUB_INT_MSK_CLR, V3D_HUB_IRQS);
पूर्ण

व्योम
v3d_irq_disable(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक core;

	/* Disable all पूर्णांकerrupts. */
	क्रम (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_MSK_SET, ~0);
	V3D_WRITE(V3D_HUB_INT_MSK_SET, ~0);

	/* Clear any pending पूर्णांकerrupts we might have left. */
	क्रम (core = 0; core < v3d->cores; core++)
		V3D_CORE_WRITE(core, V3D_CTL_INT_CLR, V3D_CORE_IRQS);
	V3D_WRITE(V3D_HUB_INT_CLR, V3D_HUB_IRQS);

	cancel_work_sync(&v3d->overflow_mem_work);
पूर्ण

/** Reinitializes पूर्णांकerrupt रेजिस्टरs when a GPU reset is perक्रमmed. */
व्योम v3d_irq_reset(काष्ठा v3d_dev *v3d)
अणु
	v3d_irq_enable(v3d);
पूर्ण
