<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "msm_gpu.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"
#समावेश "msm_fence.h"
#समावेश "msm_gpu_trace.h"
#समावेश "adreno/adreno_gpu.h"

#समावेश <generated/utsrelease.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq_cooling.h>
#समावेश <linux/devcoredump.h>
#समावेश <linux/sched/task.h>

/*
 * Power Management:
 */

अटल पूर्णांक msm_devfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
		u32 flags)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);
	काष्ठा dev_pm_opp *opp;

	opp = devfreq_recommended_opp(dev, freq, flags);

	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	trace_msm_gpu_freq_change(dev_pm_opp_get_freq(opp));

	अगर (gpu->funcs->gpu_set_freq)
		gpu->funcs->gpu_set_freq(gpu, opp);
	अन्यथा
		clk_set_rate(gpu->core_clk, *freq);

	dev_pm_opp_put(opp);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_devfreq_get_dev_status(काष्ठा device *dev,
		काष्ठा devfreq_dev_status *status)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);
	kसमय_प्रकार समय;

	अगर (gpu->funcs->gpu_get_freq)
		status->current_frequency = gpu->funcs->gpu_get_freq(gpu);
	अन्यथा
		status->current_frequency = clk_get_rate(gpu->core_clk);

	status->busy_समय = gpu->funcs->gpu_busy(gpu);

	समय = kसमय_get();
	status->total_समय = kसमय_us_delta(समय, gpu->devfreq.समय);
	gpu->devfreq.समय = समय;

	वापस 0;
पूर्ण

अटल पूर्णांक msm_devfreq_get_cur_freq(काष्ठा device *dev, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा msm_gpu *gpu = dev_to_gpu(dev);

	अगर (gpu->funcs->gpu_get_freq)
		*freq = gpu->funcs->gpu_get_freq(gpu);
	अन्यथा
		*freq = clk_get_rate(gpu->core_clk);

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile msm_devfreq_profile = अणु
	.polling_ms = 10,
	.target = msm_devfreq_target,
	.get_dev_status = msm_devfreq_get_dev_status,
	.get_cur_freq = msm_devfreq_get_cur_freq,
पूर्ण;

अटल व्योम msm_devfreq_init(काष्ठा msm_gpu *gpu)
अणु
	/* We need target support to करो devfreq */
	अगर (!gpu->funcs->gpu_busy)
		वापस;

	msm_devfreq_profile.initial_freq = gpu->fast_rate;

	/*
	 * Don't set the freq_table or max_state and let devfreq build the table
	 * from OPP
	 * After a deferred probe, these may have be left to non-zero values,
	 * so set them back to zero beक्रमe creating the devfreq device
	 */
	msm_devfreq_profile.freq_table = शून्य;
	msm_devfreq_profile.max_state = 0;

	gpu->devfreq.devfreq = devm_devfreq_add_device(&gpu->pdev->dev,
			&msm_devfreq_profile, DEVFREQ_GOV_SIMPLE_ONDEMAND,
			शून्य);

	अगर (IS_ERR(gpu->devfreq.devfreq)) अणु
		DRM_DEV_ERROR(&gpu->pdev->dev, "Couldn't initialize GPU devfreq\n");
		gpu->devfreq.devfreq = शून्य;
		वापस;
	पूर्ण

	devfreq_suspend_device(gpu->devfreq.devfreq);

	gpu->cooling = of_devfreq_cooling_रेजिस्टर(gpu->pdev->dev.of_node,
			gpu->devfreq.devfreq);
	अगर (IS_ERR(gpu->cooling)) अणु
		DRM_DEV_ERROR(&gpu->pdev->dev,
				"Couldn't register GPU cooling device\n");
		gpu->cooling = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक enable_pwrrail(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा drm_device *dev = gpu->dev;
	पूर्णांक ret = 0;

	अगर (gpu->gpu_reg) अणु
		ret = regulator_enable(gpu->gpu_reg);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to enable 'gpu_reg': %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (gpu->gpu_cx) अणु
		ret = regulator_enable(gpu->gpu_cx);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev->dev, "failed to enable 'gpu_cx': %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक disable_pwrrail(काष्ठा msm_gpu *gpu)
अणु
	अगर (gpu->gpu_cx)
		regulator_disable(gpu->gpu_cx);
	अगर (gpu->gpu_reg)
		regulator_disable(gpu->gpu_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक enable_clk(काष्ठा msm_gpu *gpu)
अणु
	अगर (gpu->core_clk && gpu->fast_rate)
		clk_set_rate(gpu->core_clk, gpu->fast_rate);

	/* Set the RBBM समयr rate to 19.2Mhz */
	अगर (gpu->rbbmसमयr_clk)
		clk_set_rate(gpu->rbbmसमयr_clk, 19200000);

	वापस clk_bulk_prepare_enable(gpu->nr_घड़ीs, gpu->grp_clks);
पूर्ण

अटल पूर्णांक disable_clk(काष्ठा msm_gpu *gpu)
अणु
	clk_bulk_disable_unprepare(gpu->nr_घड़ीs, gpu->grp_clks);

	/*
	 * Set the घड़ी to a deliberately low rate. On older tarमाला_लो the घड़ी
	 * speed had to be non zero to aव्योम problems. On newer tarमाला_लो this
	 * will be rounded करोwn to zero anyway so it all works out.
	 */
	अगर (gpu->core_clk)
		clk_set_rate(gpu->core_clk, 27000000);

	अगर (gpu->rbbmसमयr_clk)
		clk_set_rate(gpu->rbbmसमयr_clk, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक enable_axi(काष्ठा msm_gpu *gpu)
अणु
	वापस clk_prepare_enable(gpu->ebi1_clk);
पूर्ण

अटल पूर्णांक disable_axi(काष्ठा msm_gpu *gpu)
अणु
	clk_disable_unprepare(gpu->ebi1_clk);
	वापस 0;
पूर्ण

व्योम msm_gpu_resume_devfreq(काष्ठा msm_gpu *gpu)
अणु
	gpu->devfreq.busy_cycles = 0;
	gpu->devfreq.समय = kसमय_get();

	devfreq_resume_device(gpu->devfreq.devfreq);
पूर्ण

पूर्णांक msm_gpu_pm_resume(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक ret;

	DBG("%s", gpu->name);
	trace_msm_gpu_resume(0);

	ret = enable_pwrrail(gpu);
	अगर (ret)
		वापस ret;

	ret = enable_clk(gpu);
	अगर (ret)
		वापस ret;

	ret = enable_axi(gpu);
	अगर (ret)
		वापस ret;

	msm_gpu_resume_devfreq(gpu);

	gpu->needs_hw_init = true;

	वापस 0;
पूर्ण

पूर्णांक msm_gpu_pm_suspend(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक ret;

	DBG("%s", gpu->name);
	trace_msm_gpu_suspend(0);

	devfreq_suspend_device(gpu->devfreq.devfreq);

	ret = disable_axi(gpu);
	अगर (ret)
		वापस ret;

	ret = disable_clk(gpu);
	अगर (ret)
		वापस ret;

	ret = disable_pwrrail(gpu);
	अगर (ret)
		वापस ret;

	gpu->suspend_count++;

	वापस 0;
पूर्ण

पूर्णांक msm_gpu_hw_init(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक ret;

	WARN_ON(!mutex_is_locked(&gpu->dev->काष्ठा_mutex));

	अगर (!gpu->needs_hw_init)
		वापस 0;

	disable_irq(gpu->irq);
	ret = gpu->funcs->hw_init(gpu);
	अगर (!ret)
		gpu->needs_hw_init = false;
	enable_irq(gpu->irq);

	वापस ret;
पूर्ण

अटल व्योम update_fences(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring,
		uपूर्णांक32_t fence)
अणु
	काष्ठा msm_gem_submit *submit;

	spin_lock(&ring->submit_lock);
	list_क्रम_each_entry(submit, &ring->submits, node) अणु
		अगर (submit->seqno > fence)
			अवरोध;

		msm_update_fence(submit->ring->fctx,
			submit->fence->seqno);
	पूर्ण
	spin_unlock(&ring->submit_lock);
पूर्ण

#अगर_घोषित CONFIG_DEV_COREDUMP
अटल sमाप_प्रकार msm_gpu_devcoredump_पढ़ो(अक्षर *buffer, loff_t offset,
		माप_प्रकार count, व्योम *data, माप_प्रकार datalen)
अणु
	काष्ठा msm_gpu *gpu = data;
	काष्ठा drm_prपूर्णांक_iterator iter;
	काष्ठा drm_prपूर्णांकer p;
	काष्ठा msm_gpu_state *state;

	state = msm_gpu_crashstate_get(gpu);
	अगर (!state)
		वापस 0;

	iter.data = buffer;
	iter.offset = 0;
	iter.start = offset;
	iter.reमुख्य = count;

	p = drm_coredump_prपूर्णांकer(&iter);

	drm_म_लिखो(&p, "---\n");
	drm_म_लिखो(&p, "kernel: " UTS_RELEASE "\n");
	drm_म_लिखो(&p, "module: " KBUILD_MODNAME "\n");
	drm_म_लिखो(&p, "time: %lld.%09ld\n",
		state->समय.tv_sec, state->समय.tv_nsec);
	अगर (state->comm)
		drm_म_लिखो(&p, "comm: %s\n", state->comm);
	अगर (state->cmd)
		drm_म_लिखो(&p, "cmdline: %s\n", state->cmd);

	gpu->funcs->show(gpu, state, &p);

	msm_gpu_crashstate_put(gpu);

	वापस count - iter.reमुख्य;
पूर्ण

अटल व्योम msm_gpu_devcoredump_मुक्त(व्योम *data)
अणु
	काष्ठा msm_gpu *gpu = data;

	msm_gpu_crashstate_put(gpu);
पूर्ण

अटल व्योम msm_gpu_crashstate_get_bo(काष्ठा msm_gpu_state *state,
		काष्ठा msm_gem_object *obj, u64 iova, u32 flags)
अणु
	काष्ठा msm_gpu_state_bo *state_bo = &state->bos[state->nr_bos];

	/* Don't record ग_लिखो only objects */
	state_bo->size = obj->base.size;
	state_bo->iova = iova;

	/* Only store data क्रम non imported buffer objects marked क्रम पढ़ो */
	अगर ((flags & MSM_SUBMIT_BO_READ) && !obj->base.import_attach) अणु
		व्योम *ptr;

		state_bo->data = kvदो_स्मृति(obj->base.size, GFP_KERNEL);
		अगर (!state_bo->data)
			जाओ out;

		msm_gem_lock(&obj->base);
		ptr = msm_gem_get_vaddr_active(&obj->base);
		msm_gem_unlock(&obj->base);
		अगर (IS_ERR(ptr)) अणु
			kvमुक्त(state_bo->data);
			state_bo->data = शून्य;
			जाओ out;
		पूर्ण

		स_नकल(state_bo->data, ptr, obj->base.size);
		msm_gem_put_vaddr(&obj->base);
	पूर्ण
out:
	state->nr_bos++;
पूर्ण

अटल व्योम msm_gpu_crashstate_capture(काष्ठा msm_gpu *gpu,
		काष्ठा msm_gem_submit *submit, अक्षर *comm, अक्षर *cmd)
अणु
	काष्ठा msm_gpu_state *state;

	/* Check अगर the target supports capturing crash state */
	अगर (!gpu->funcs->gpu_state_get)
		वापस;

	/* Only save one crash state at a समय */
	अगर (gpu->crashstate)
		वापस;

	state = gpu->funcs->gpu_state_get(gpu);
	अगर (IS_ERR_OR_शून्य(state))
		वापस;

	/* Fill in the additional crash state inक्रमmation */
	state->comm = kstrdup(comm, GFP_KERNEL);
	state->cmd = kstrdup(cmd, GFP_KERNEL);

	अगर (submit) अणु
		पूर्णांक i, nr = 0;

		/* count # of buffers to dump: */
		क्रम (i = 0; i < submit->nr_bos; i++)
			अगर (should_dump(submit, i))
				nr++;
		/* always dump cmd bo's, but don't द्विगुन count them: */
		क्रम (i = 0; i < submit->nr_cmds; i++)
			अगर (!should_dump(submit, submit->cmd[i].idx))
				nr++;

		state->bos = kसुस्मृति(nr,
			माप(काष्ठा msm_gpu_state_bo), GFP_KERNEL);

		क्रम (i = 0; i < submit->nr_bos; i++) अणु
			अगर (should_dump(submit, i)) अणु
				msm_gpu_crashstate_get_bo(state, submit->bos[i].obj,
					submit->bos[i].iova, submit->bos[i].flags);
			पूर्ण
		पूर्ण

		क्रम (i = 0; state->bos && i < submit->nr_cmds; i++) अणु
			पूर्णांक idx = submit->cmd[i].idx;

			अगर (!should_dump(submit, submit->cmd[i].idx)) अणु
				msm_gpu_crashstate_get_bo(state, submit->bos[idx].obj,
					submit->bos[idx].iova, submit->bos[idx].flags);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Set the active crash state to be dumped on failure */
	gpu->crashstate = state;

	/* FIXME: Release the crashstate अगर this errors out? */
	dev_coredumpm(gpu->dev->dev, THIS_MODULE, gpu, 0, GFP_KERNEL,
		msm_gpu_devcoredump_पढ़ो, msm_gpu_devcoredump_मुक्त);
पूर्ण
#अन्यथा
अटल व्योम msm_gpu_crashstate_capture(काष्ठा msm_gpu *gpu,
		काष्ठा msm_gem_submit *submit, अक्षर *comm, अक्षर *cmd)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Hangcheck detection क्रम locked gpu:
 */

अटल काष्ठा msm_gem_submit *
find_submit(काष्ठा msm_ringbuffer *ring, uपूर्णांक32_t fence)
अणु
	काष्ठा msm_gem_submit *submit;

	spin_lock(&ring->submit_lock);
	list_क्रम_each_entry(submit, &ring->submits, node) अणु
		अगर (submit->seqno == fence) अणु
			spin_unlock(&ring->submit_lock);
			वापस submit;
		पूर्ण
	पूर्ण
	spin_unlock(&ring->submit_lock);

	वापस शून्य;
पूर्ण

अटल व्योम retire_submits(काष्ठा msm_gpu *gpu);

अटल व्योम recover_worker(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा msm_gpu *gpu = container_of(work, काष्ठा msm_gpu, recover_work);
	काष्ठा drm_device *dev = gpu->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_gem_submit *submit;
	काष्ठा msm_ringbuffer *cur_ring = gpu->funcs->active_ring(gpu);
	अक्षर *comm = शून्य, *cmd = शून्य;
	पूर्णांक i;

	mutex_lock(&dev->काष्ठा_mutex);

	DRM_DEV_ERROR(dev->dev, "%s: hangcheck recover!\n", gpu->name);

	submit = find_submit(cur_ring, cur_ring->memptrs->fence + 1);
	अगर (submit) अणु
		काष्ठा task_काष्ठा *task;

		/* Increment the fault counts */
		gpu->global_faults++;
		submit->queue->faults++;

		task = get_pid_task(submit->pid, PIDTYPE_PID);
		अगर (task) अणु
			comm = kstrdup(task->comm, GFP_KERNEL);
			cmd = kstrdup_quotable_cmdline(task, GFP_KERNEL);
			put_task_काष्ठा(task);
		पूर्ण

		/* msm_rd_dump_submit() needs bo locked to dump: */
		क्रम (i = 0; i < submit->nr_bos; i++)
			msm_gem_lock(&submit->bos[i].obj->base);

		अगर (comm && cmd) अणु
			DRM_DEV_ERROR(dev->dev, "%s: offending task: %s (%s)\n",
				gpu->name, comm, cmd);

			msm_rd_dump_submit(priv->hangrd, submit,
				"offending task: %s (%s)", comm, cmd);
		पूर्ण अन्यथा अणु
			msm_rd_dump_submit(priv->hangrd, submit, शून्य);
		पूर्ण

		क्रम (i = 0; i < submit->nr_bos; i++)
			msm_gem_unlock(&submit->bos[i].obj->base);
	पूर्ण

	/* Record the crash state */
	pm_runसमय_get_sync(&gpu->pdev->dev);
	msm_gpu_crashstate_capture(gpu, submit, comm, cmd);
	pm_runसमय_put_sync(&gpu->pdev->dev);

	kमुक्त(cmd);
	kमुक्त(comm);

	/*
	 * Update all the rings with the latest and greatest fence.. this
	 * needs to happen after msm_rd_dump_submit() to ensure that the
	 * bo's referenced by the offending submit are still around.
	 */
	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		uपूर्णांक32_t fence = ring->memptrs->fence;

		/*
		 * For the current (faulting?) ring/submit advance the fence by
		 * one more to clear the faulting submit
		 */
		अगर (ring == cur_ring)
			fence++;

		update_fences(gpu, ring, fence);
	पूर्ण

	अगर (msm_gpu_active(gpu)) अणु
		/* retire completed submits, plus the one that hung: */
		retire_submits(gpu);

		pm_runसमय_get_sync(&gpu->pdev->dev);
		gpu->funcs->recover(gpu);
		pm_runसमय_put_sync(&gpu->pdev->dev);

		/*
		 * Replay all reमुख्यing submits starting with highest priority
		 * ring
		 */
		क्रम (i = 0; i < gpu->nr_rings; i++) अणु
			काष्ठा msm_ringbuffer *ring = gpu->rb[i];

			spin_lock(&ring->submit_lock);
			list_क्रम_each_entry(submit, &ring->submits, node)
				gpu->funcs->submit(gpu, submit);
			spin_unlock(&ring->submit_lock);
		पूर्ण
	पूर्ण

	mutex_unlock(&dev->काष्ठा_mutex);

	msm_gpu_retire(gpu);
पूर्ण

अटल व्योम hangcheck_समयr_reset(काष्ठा msm_gpu *gpu)
अणु
	mod_समयr(&gpu->hangcheck_समयr,
			round_jअगरfies_up(jअगरfies + DRM_MSM_HANGCHECK_JIFFIES));
पूर्ण

अटल व्योम hangcheck_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा msm_gpu *gpu = from_समयr(gpu, t, hangcheck_समयr);
	काष्ठा drm_device *dev = gpu->dev;
	काष्ठा msm_ringbuffer *ring = gpu->funcs->active_ring(gpu);
	uपूर्णांक32_t fence = ring->memptrs->fence;

	अगर (fence != ring->hangcheck_fence) अणु
		/* some progress has been made.. ya! */
		ring->hangcheck_fence = fence;
	पूर्ण अन्यथा अगर (fence < ring->seqno) अणु
		/* no progress and not करोne.. hung! */
		ring->hangcheck_fence = fence;
		DRM_DEV_ERROR(dev->dev, "%s: hangcheck detected gpu lockup rb %d!\n",
				gpu->name, ring->id);
		DRM_DEV_ERROR(dev->dev, "%s:     completed fence: %u\n",
				gpu->name, fence);
		DRM_DEV_ERROR(dev->dev, "%s:     submitted fence: %u\n",
				gpu->name, ring->seqno);

		kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
	पूर्ण

	/* अगर still more pending work, reset the hangcheck समयr: */
	अगर (ring->seqno > ring->hangcheck_fence)
		hangcheck_समयr_reset(gpu);

	/* workaround क्रम missing irq: */
	kthपढ़ो_queue_work(gpu->worker, &gpu->retire_work);
पूर्ण

/*
 * Perक्रमmance Counters:
 */

/* called under perf_lock */
अटल पूर्णांक update_hw_cntrs(काष्ठा msm_gpu *gpu, uपूर्णांक32_t ncntrs, uपूर्णांक32_t *cntrs)
अणु
	uपूर्णांक32_t current_cntrs[ARRAY_SIZE(gpu->last_cntrs)];
	पूर्णांक i, n = min(ncntrs, gpu->num_perfcntrs);

	/* पढ़ो current values: */
	क्रम (i = 0; i < gpu->num_perfcntrs; i++)
		current_cntrs[i] = gpu_पढ़ो(gpu, gpu->perfcntrs[i].sample_reg);

	/* update cntrs: */
	क्रम (i = 0; i < n; i++)
		cntrs[i] = current_cntrs[i] - gpu->last_cntrs[i];

	/* save current values: */
	क्रम (i = 0; i < gpu->num_perfcntrs; i++)
		gpu->last_cntrs[i] = current_cntrs[i];

	वापस n;
पूर्ण

अटल व्योम update_sw_cntrs(काष्ठा msm_gpu *gpu)
अणु
	kसमय_प्रकार समय;
	uपूर्णांक32_t elapsed;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gpu->perf_lock, flags);
	अगर (!gpu->perfcntr_active)
		जाओ out;

	समय = kसमय_get();
	elapsed = kसमय_प्रकारo_us(kसमय_sub(समय, gpu->last_sample.समय));

	gpu->totalसमय += elapsed;
	अगर (gpu->last_sample.active)
		gpu->activeसमय += elapsed;

	gpu->last_sample.active = msm_gpu_active(gpu);
	gpu->last_sample.समय = समय;

out:
	spin_unlock_irqrestore(&gpu->perf_lock, flags);
पूर्ण

व्योम msm_gpu_perfcntr_start(काष्ठा msm_gpu *gpu)
अणु
	अचिन्हित दीर्घ flags;

	pm_runसमय_get_sync(&gpu->pdev->dev);

	spin_lock_irqsave(&gpu->perf_lock, flags);
	/* we could dynamically enable/disable perfcntr रेजिस्टरs too.. */
	gpu->last_sample.active = msm_gpu_active(gpu);
	gpu->last_sample.समय = kसमय_get();
	gpu->activeसमय = gpu->totalसमय = 0;
	gpu->perfcntr_active = true;
	update_hw_cntrs(gpu, 0, शून्य);
	spin_unlock_irqrestore(&gpu->perf_lock, flags);
पूर्ण

व्योम msm_gpu_perfcntr_stop(काष्ठा msm_gpu *gpu)
अणु
	gpu->perfcntr_active = false;
	pm_runसमय_put_sync(&gpu->pdev->dev);
पूर्ण

/* वापसs -त्रुटि_सं or # of cntrs sampled */
पूर्णांक msm_gpu_perfcntr_sample(काष्ठा msm_gpu *gpu, uपूर्णांक32_t *activeसमय,
		uपूर्णांक32_t *totalसमय, uपूर्णांक32_t ncntrs, uपूर्णांक32_t *cntrs)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&gpu->perf_lock, flags);

	अगर (!gpu->perfcntr_active) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	*activeसमय = gpu->activeसमय;
	*totalसमय = gpu->totalसमय;

	gpu->activeसमय = gpu->totalसमय = 0;

	ret = update_hw_cntrs(gpu, ncntrs, cntrs);

out:
	spin_unlock_irqrestore(&gpu->perf_lock, flags);

	वापस ret;
पूर्ण

/*
 * Cmdstream submission/retirement:
 */

अटल व्योम retire_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring,
		काष्ठा msm_gem_submit *submit)
अणु
	पूर्णांक index = submit->seqno % MSM_GPU_SUBMIT_STATS_COUNT;
	अस्थिर काष्ठा msm_gpu_submit_stats *stats;
	u64 elapsed, घड़ी = 0;
	पूर्णांक i;

	stats = &ring->memptrs->stats[index];
	/* Convert 19.2Mhz alwayson ticks to nanoseconds क्रम elapsed समय */
	elapsed = (stats->alwayson_end - stats->alwayson_start) * 10000;
	करो_भाग(elapsed, 192);

	/* Calculate the घड़ी frequency from the number of CP cycles */
	अगर (elapsed) अणु
		घड़ी = (stats->cpcycles_end - stats->cpcycles_start) * 1000;
		करो_भाग(घड़ी, elapsed);
	पूर्ण

	trace_msm_gpu_submit_retired(submit, elapsed, घड़ी,
		stats->alwayson_start, stats->alwayson_end);

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा drm_gem_object *obj = &submit->bos[i].obj->base;

		msm_gem_lock(obj);
		msm_gem_active_put(obj);
		msm_gem_unpin_iova_locked(obj, submit->aspace);
		msm_gem_unlock(obj);
		drm_gem_object_put(obj);
	पूर्ण

	pm_runसमय_mark_last_busy(&gpu->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&gpu->pdev->dev);

	spin_lock(&ring->submit_lock);
	list_del(&submit->node);
	spin_unlock(&ring->submit_lock);

	msm_gem_submit_put(submit);
पूर्ण

अटल व्योम retire_submits(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	/* Retire the commits starting with highest priority */
	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		जबतक (true) अणु
			काष्ठा msm_gem_submit *submit = शून्य;

			spin_lock(&ring->submit_lock);
			submit = list_first_entry_or_null(&ring->submits,
					काष्ठा msm_gem_submit, node);
			spin_unlock(&ring->submit_lock);

			/*
			 * If no submit, we are करोne.  If submit->fence hasn't
			 * been संकेतled, then later submits are not संकेतled
			 * either, so we are also करोne.
			 */
			अगर (submit && dma_fence_is_संकेतed(submit->fence)) अणु
				retire_submit(gpu, ring, submit);
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम retire_worker(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा msm_gpu *gpu = container_of(work, काष्ठा msm_gpu, retire_work);
	पूर्णांक i;

	क्रम (i = 0; i < gpu->nr_rings; i++)
		update_fences(gpu, gpu->rb[i], gpu->rb[i]->memptrs->fence);

	retire_submits(gpu);
पूर्ण

/* call from irq handler to schedule work to retire bo's */
व्योम msm_gpu_retire(काष्ठा msm_gpu *gpu)
अणु
	kthपढ़ो_queue_work(gpu->worker, &gpu->retire_work);
	update_sw_cntrs(gpu);
पूर्ण

/* add bo's to gpu's ring, and kick gpu: */
व्योम msm_gpu_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
अणु
	काष्ठा drm_device *dev = gpu->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा msm_ringbuffer *ring = submit->ring;
	पूर्णांक i;

	WARN_ON(!mutex_is_locked(&dev->काष्ठा_mutex));

	pm_runसमय_get_sync(&gpu->pdev->dev);

	msm_gpu_hw_init(gpu);

	submit->seqno = ++ring->seqno;

	msm_rd_dump_submit(priv->rd, submit, शून्य);

	update_sw_cntrs(gpu);

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा msm_gem_object *msm_obj = submit->bos[i].obj;
		काष्ठा drm_gem_object *drm_obj = &msm_obj->base;
		uपूर्णांक64_t iova;

		/* submit takes a reference to the bo and iova until retired: */
		drm_gem_object_get(&msm_obj->base);
		msm_gem_get_and_pin_iova_locked(&msm_obj->base, submit->aspace, &iova);

		अगर (submit->bos[i].flags & MSM_SUBMIT_BO_WRITE)
			dma_resv_add_excl_fence(drm_obj->resv, submit->fence);
		अन्यथा अगर (submit->bos[i].flags & MSM_SUBMIT_BO_READ)
			dma_resv_add_shared_fence(drm_obj->resv, submit->fence);

		msm_gem_active_get(drm_obj, gpu);
	पूर्ण

	/*
	 * ring->submits holds a ref to the submit, to deal with the हाल
	 * that a submit completes beक्रमe msm_ioctl_gem_submit() वापसs.
	 */
	msm_gem_submit_get(submit);

	spin_lock(&ring->submit_lock);
	list_add_tail(&submit->node, &ring->submits);
	spin_unlock(&ring->submit_lock);

	gpu->funcs->submit(gpu, submit);
	priv->lastctx = submit->queue->ctx;

	hangcheck_समयr_reset(gpu);
पूर्ण

/*
 * Init/Cleanup:
 */

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा msm_gpu *gpu = data;
	वापस gpu->funcs->irq(gpu);
पूर्ण

अटल पूर्णांक get_घड़ीs(काष्ठा platक्रमm_device *pdev, काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक ret = devm_clk_bulk_get_all(&pdev->dev, &gpu->grp_clks);

	अगर (ret < 1) अणु
		gpu->nr_घड़ीs = 0;
		वापस ret;
	पूर्ण

	gpu->nr_घड़ीs = ret;

	gpu->core_clk = msm_clk_bulk_get_घड़ी(gpu->grp_clks,
		gpu->nr_घड़ीs, "core");

	gpu->rbbmसमयr_clk = msm_clk_bulk_get_घड़ी(gpu->grp_clks,
		gpu->nr_घड़ीs, "rbbmtimer");

	वापस 0;
पूर्ण

/* Return a new address space क्रम a msm_drm_निजी instance */
काष्ठा msm_gem_address_space *
msm_gpu_create_निजी_address_space(काष्ठा msm_gpu *gpu, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा msm_gem_address_space *aspace = शून्य;
	अगर (!gpu)
		वापस शून्य;

	/*
	 * If the target करोesn't support निजी address spaces then वापस
	 * the global one
	 */
	अगर (gpu->funcs->create_निजी_address_space) अणु
		aspace = gpu->funcs->create_निजी_address_space(gpu);
		अगर (!IS_ERR(aspace))
			aspace->pid = get_pid(task_pid(task));
	पूर्ण

	अगर (IS_ERR_OR_शून्य(aspace))
		aspace = msm_gem_address_space_get(gpu->aspace);

	वापस aspace;
पूर्ण

पूर्णांक msm_gpu_init(काष्ठा drm_device *drm, काष्ठा platक्रमm_device *pdev,
		काष्ठा msm_gpu *gpu, स्थिर काष्ठा msm_gpu_funcs *funcs,
		स्थिर अक्षर *name, काष्ठा msm_gpu_config *config)
अणु
	पूर्णांक i, ret, nr_rings = config->nr_rings;
	व्योम *memptrs;
	uपूर्णांक64_t memptrs_iova;

	अगर (WARN_ON(gpu->num_perfcntrs > ARRAY_SIZE(gpu->last_cntrs)))
		gpu->num_perfcntrs = ARRAY_SIZE(gpu->last_cntrs);

	gpu->dev = drm;
	gpu->funcs = funcs;
	gpu->name = name;

	gpu->worker = kthपढ़ो_create_worker(0, "%s-worker", gpu->name);
	अगर (IS_ERR(gpu->worker)) अणु
		ret = PTR_ERR(gpu->worker);
		gpu->worker = शून्य;
		जाओ fail;
	पूर्ण

	sched_set_fअगरo_low(gpu->worker->task);

	INIT_LIST_HEAD(&gpu->active_list);
	kthपढ़ो_init_work(&gpu->retire_work, retire_worker);
	kthपढ़ो_init_work(&gpu->recover_work, recover_worker);

	समयr_setup(&gpu->hangcheck_समयr, hangcheck_handler, 0);

	spin_lock_init(&gpu->perf_lock);


	/* Map रेजिस्टरs: */
	gpu->mmio = msm_ioremap(pdev, config->ioname, name);
	अगर (IS_ERR(gpu->mmio)) अणु
		ret = PTR_ERR(gpu->mmio);
		जाओ fail;
	पूर्ण

	/* Get Interrupt: */
	gpu->irq = platक्रमm_get_irq(pdev, 0);
	अगर (gpu->irq < 0) अणु
		ret = gpu->irq;
		DRM_DEV_ERROR(drm->dev, "failed to get irq: %d\n", ret);
		जाओ fail;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, gpu->irq, irq_handler,
			IRQF_TRIGGER_HIGH, gpu->name, gpu);
	अगर (ret) अणु
		DRM_DEV_ERROR(drm->dev, "failed to request IRQ%u: %d\n", gpu->irq, ret);
		जाओ fail;
	पूर्ण

	ret = get_घड़ीs(pdev, gpu);
	अगर (ret)
		जाओ fail;

	gpu->ebi1_clk = msm_clk_get(pdev, "bus");
	DBG("ebi1_clk: %p", gpu->ebi1_clk);
	अगर (IS_ERR(gpu->ebi1_clk))
		gpu->ebi1_clk = शून्य;

	/* Acquire regulators: */
	gpu->gpu_reg = devm_regulator_get(&pdev->dev, "vdd");
	DBG("gpu_reg: %p", gpu->gpu_reg);
	अगर (IS_ERR(gpu->gpu_reg))
		gpu->gpu_reg = शून्य;

	gpu->gpu_cx = devm_regulator_get(&pdev->dev, "vddcx");
	DBG("gpu_cx: %p", gpu->gpu_cx);
	अगर (IS_ERR(gpu->gpu_cx))
		gpu->gpu_cx = शून्य;

	gpu->pdev = pdev;
	platक्रमm_set_drvdata(pdev, &gpu->adreno_smmu);

	msm_devfreq_init(gpu);


	gpu->aspace = gpu->funcs->create_address_space(gpu, pdev);

	अगर (gpu->aspace == शून्य)
		DRM_DEV_INFO(drm->dev, "%s: no IOMMU, fallback to VRAM carveout!\n", name);
	अन्यथा अगर (IS_ERR(gpu->aspace)) अणु
		ret = PTR_ERR(gpu->aspace);
		जाओ fail;
	पूर्ण

	memptrs = msm_gem_kernel_new(drm,
		माप(काष्ठा msm_rbmemptrs) * nr_rings,
		check_apriv(gpu, MSM_BO_UNCACHED), gpu->aspace, &gpu->memptrs_bo,
		&memptrs_iova);

	अगर (IS_ERR(memptrs)) अणु
		ret = PTR_ERR(memptrs);
		DRM_DEV_ERROR(drm->dev, "could not allocate memptrs: %d\n", ret);
		जाओ fail;
	पूर्ण

	msm_gem_object_set_name(gpu->memptrs_bo, "memptrs");

	अगर (nr_rings > ARRAY_SIZE(gpu->rb)) अणु
		DRM_DEV_INFO_ONCE(drm->dev, "Only creating %zu ringbuffers\n",
			ARRAY_SIZE(gpu->rb));
		nr_rings = ARRAY_SIZE(gpu->rb);
	पूर्ण

	/* Create ringbuffer(s): */
	क्रम (i = 0; i < nr_rings; i++) अणु
		gpu->rb[i] = msm_ringbuffer_new(gpu, i, memptrs, memptrs_iova);

		अगर (IS_ERR(gpu->rb[i])) अणु
			ret = PTR_ERR(gpu->rb[i]);
			DRM_DEV_ERROR(drm->dev,
				"could not create ringbuffer %d: %d\n", i, ret);
			जाओ fail;
		पूर्ण

		memptrs += माप(काष्ठा msm_rbmemptrs);
		memptrs_iova += माप(काष्ठा msm_rbmemptrs);
	पूर्ण

	gpu->nr_rings = nr_rings;

	वापस 0;

fail:
	क्रम (i = 0; i < ARRAY_SIZE(gpu->rb); i++)  अणु
		msm_ringbuffer_destroy(gpu->rb[i]);
		gpu->rb[i] = शून्य;
	पूर्ण

	msm_gem_kernel_put(gpu->memptrs_bo, gpu->aspace, false);

	platक्रमm_set_drvdata(pdev, शून्य);
	वापस ret;
पूर्ण

व्योम msm_gpu_cleanup(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	DBG("%s", gpu->name);

	WARN_ON(!list_empty(&gpu->active_list));

	क्रम (i = 0; i < ARRAY_SIZE(gpu->rb); i++) अणु
		msm_ringbuffer_destroy(gpu->rb[i]);
		gpu->rb[i] = शून्य;
	पूर्ण

	msm_gem_kernel_put(gpu->memptrs_bo, gpu->aspace, false);

	अगर (!IS_ERR_OR_शून्य(gpu->aspace)) अणु
		gpu->aspace->mmu->funcs->detach(gpu->aspace->mmu);
		msm_gem_address_space_put(gpu->aspace);
	पूर्ण

	अगर (gpu->worker) अणु
		kthपढ़ो_destroy_worker(gpu->worker);
	पूर्ण

	devfreq_cooling_unरेजिस्टर(gpu->cooling);
पूर्ण
