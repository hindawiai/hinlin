<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "lima_devfreq.h"
#समावेश "lima_drv.h"
#समावेश "lima_sched.h"
#समावेश "lima_vm.h"
#समावेश "lima_mmu.h"
#समावेश "lima_l2_cache.h"
#समावेश "lima_gem.h"
#समावेश "lima_trace.h"

काष्ठा lima_fence अणु
	काष्ठा dma_fence base;
	काष्ठा lima_sched_pipe *pipe;
पूर्ण;

अटल काष्ठा kmem_cache *lima_fence_slab;
अटल पूर्णांक lima_fence_slab_refcnt;

पूर्णांक lima_sched_slab_init(व्योम)
अणु
	अगर (!lima_fence_slab) अणु
		lima_fence_slab = kmem_cache_create(
			"lima_fence", माप(काष्ठा lima_fence), 0,
			SLAB_HWCACHE_ALIGN, शून्य);
		अगर (!lima_fence_slab)
			वापस -ENOMEM;
	पूर्ण

	lima_fence_slab_refcnt++;
	वापस 0;
पूर्ण

व्योम lima_sched_slab_fini(व्योम)
अणु
	अगर (!--lima_fence_slab_refcnt) अणु
		kmem_cache_destroy(lima_fence_slab);
		lima_fence_slab = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा lima_fence *to_lima_fence(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence, काष्ठा lima_fence, base);
पूर्ण

अटल स्थिर अक्षर *lima_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "lima";
पूर्ण

अटल स्थिर अक्षर *lima_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा lima_fence *f = to_lima_fence(fence);

	वापस f->pipe->base.name;
पूर्ण

अटल व्योम lima_fence_release_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा dma_fence *f = container_of(rcu, काष्ठा dma_fence, rcu);
	काष्ठा lima_fence *fence = to_lima_fence(f);

	kmem_cache_मुक्त(lima_fence_slab, fence);
पूर्ण

अटल व्योम lima_fence_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा lima_fence *f = to_lima_fence(fence);

	call_rcu(&f->base.rcu, lima_fence_release_rcu);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops lima_fence_ops = अणु
	.get_driver_name = lima_fence_get_driver_name,
	.get_समयline_name = lima_fence_get_समयline_name,
	.release = lima_fence_release,
पूर्ण;

अटल काष्ठा lima_fence *lima_fence_create(काष्ठा lima_sched_pipe *pipe)
अणु
	काष्ठा lima_fence *fence;

	fence = kmem_cache_zalloc(lima_fence_slab, GFP_KERNEL);
	अगर (!fence)
		वापस शून्य;

	fence->pipe = pipe;
	dma_fence_init(&fence->base, &lima_fence_ops, &pipe->fence_lock,
		       pipe->fence_context, ++pipe->fence_seqno);

	वापस fence;
पूर्ण

अटल अंतरभूत काष्ठा lima_sched_task *to_lima_task(काष्ठा drm_sched_job *job)
अणु
	वापस container_of(job, काष्ठा lima_sched_task, base);
पूर्ण

अटल अंतरभूत काष्ठा lima_sched_pipe *to_lima_pipe(काष्ठा drm_gpu_scheduler *sched)
अणु
	वापस container_of(sched, काष्ठा lima_sched_pipe, base);
पूर्ण

पूर्णांक lima_sched_task_init(काष्ठा lima_sched_task *task,
			 काष्ठा lima_sched_context *context,
			 काष्ठा lima_bo **bos, पूर्णांक num_bos,
			 काष्ठा lima_vm *vm)
अणु
	पूर्णांक err, i;

	task->bos = kmemdup(bos, माप(*bos) * num_bos, GFP_KERNEL);
	अगर (!task->bos)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_bos; i++)
		drm_gem_object_get(&bos[i]->base.base);

	err = drm_sched_job_init(&task->base, &context->base, vm);
	अगर (err) अणु
		kमुक्त(task->bos);
		वापस err;
	पूर्ण

	task->num_bos = num_bos;
	task->vm = lima_vm_get(vm);

	xa_init_flags(&task->deps, XA_FLAGS_ALLOC);

	वापस 0;
पूर्ण

व्योम lima_sched_task_fini(काष्ठा lima_sched_task *task)
अणु
	काष्ठा dma_fence *fence;
	अचिन्हित दीर्घ index;
	पूर्णांक i;

	drm_sched_job_cleanup(&task->base);

	xa_क्रम_each(&task->deps, index, fence) अणु
		dma_fence_put(fence);
	पूर्ण
	xa_destroy(&task->deps);

	अगर (task->bos) अणु
		क्रम (i = 0; i < task->num_bos; i++)
			drm_gem_object_put(&task->bos[i]->base.base);
		kमुक्त(task->bos);
	पूर्ण

	lima_vm_put(task->vm);
पूर्ण

पूर्णांक lima_sched_context_init(काष्ठा lima_sched_pipe *pipe,
			    काष्ठा lima_sched_context *context,
			    atomic_t *guilty)
अणु
	काष्ठा drm_gpu_scheduler *sched = &pipe->base;

	वापस drm_sched_entity_init(&context->base, DRM_SCHED_PRIORITY_NORMAL,
				     &sched, 1, guilty);
पूर्ण

व्योम lima_sched_context_fini(काष्ठा lima_sched_pipe *pipe,
			     काष्ठा lima_sched_context *context)
अणु
	drm_sched_entity_fini(&context->base);
पूर्ण

काष्ठा dma_fence *lima_sched_context_queue_task(काष्ठा lima_sched_context *context,
						काष्ठा lima_sched_task *task)
अणु
	काष्ठा dma_fence *fence = dma_fence_get(&task->base.s_fence->finished);

	trace_lima_task_submit(task);
	drm_sched_entity_push_job(&task->base, &context->base);
	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *lima_sched_dependency(काष्ठा drm_sched_job *job,
					       काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा lima_sched_task *task = to_lima_task(job);

	अगर (!xa_empty(&task->deps))
		वापस xa_erase(&task->deps, task->last_dep++);

	वापस शून्य;
पूर्ण

अटल पूर्णांक lima_pm_busy(काष्ठा lima_device *ldev)
अणु
	पूर्णांक ret;

	/* resume GPU अगर it has been suspended by runसमय PM */
	ret = pm_runसमय_resume_and_get(ldev->dev);
	अगर (ret < 0)
		वापस ret;

	lima_devfreq_record_busy(&ldev->devfreq);
	वापस 0;
पूर्ण

अटल व्योम lima_pm_idle(काष्ठा lima_device *ldev)
अणु
	lima_devfreq_record_idle(&ldev->devfreq);

	/* GPU can करो स्वतः runसमय suspend */
	pm_runसमय_mark_last_busy(ldev->dev);
	pm_runसमय_put_स्वतःsuspend(ldev->dev);
पूर्ण

अटल काष्ठा dma_fence *lima_sched_run_job(काष्ठा drm_sched_job *job)
अणु
	काष्ठा lima_sched_task *task = to_lima_task(job);
	काष्ठा lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	काष्ठा lima_device *ldev = pipe->ldev;
	काष्ठा lima_fence *fence;
	पूर्णांक i, err;

	/* after GPU reset */
	अगर (job->s_fence->finished.error < 0)
		वापस शून्य;

	fence = lima_fence_create(pipe);
	अगर (!fence)
		वापस शून्य;

	err = lima_pm_busy(ldev);
	अगर (err < 0) अणु
		dma_fence_put(&fence->base);
		वापस शून्य;
	पूर्ण

	task->fence = &fence->base;

	/* क्रम caller usage of the fence, otherwise irq handler
	 * may consume the fence beक्रमe caller use it
	 */
	dma_fence_get(task->fence);

	pipe->current_task = task;

	/* this is needed क्रम MMU to work correctly, otherwise GP/PP
	 * will hang or page fault क्रम unknown reason after running क्रम
	 * a जबतक.
	 *
	 * Need to investigate:
	 * 1. is it related to TLB
	 * 2. how much perक्रमmance will be affected by L2 cache flush
	 * 3. can we reduce the calling of this function because all
	 *    GP/PP use the same L2 cache on mali400
	 *
	 * TODO:
	 * 1. move this to task fini to save some रुको समय?
	 * 2. when GP/PP use dअगरferent l2 cache, need PP रुको GP l2
	 *    cache flush?
	 */
	क्रम (i = 0; i < pipe->num_l2_cache; i++)
		lima_l2_cache_flush(pipe->l2_cache[i]);

	lima_vm_put(pipe->current_vm);
	pipe->current_vm = lima_vm_get(task->vm);

	अगर (pipe->bcast_mmu)
		lima_mmu_चयन_vm(pipe->bcast_mmu, pipe->current_vm);
	अन्यथा अणु
		क्रम (i = 0; i < pipe->num_mmu; i++)
			lima_mmu_चयन_vm(pipe->mmu[i], pipe->current_vm);
	पूर्ण

	trace_lima_task_run(task);

	pipe->error = false;
	pipe->task_run(pipe, task);

	वापस task->fence;
पूर्ण

अटल व्योम lima_sched_build_error_task_list(काष्ठा lima_sched_task *task)
अणु
	काष्ठा lima_sched_error_task *et;
	काष्ठा lima_sched_pipe *pipe = to_lima_pipe(task->base.sched);
	काष्ठा lima_ip *ip = pipe->processor[0];
	पूर्णांक pipe_id = ip->id == lima_ip_gp ? lima_pipe_gp : lima_pipe_pp;
	काष्ठा lima_device *dev = ip->dev;
	काष्ठा lima_sched_context *sched_ctx =
		container_of(task->base.entity,
			     काष्ठा lima_sched_context, base);
	काष्ठा lima_ctx *ctx =
		container_of(sched_ctx, काष्ठा lima_ctx, context[pipe_id]);
	काष्ठा lima_dump_task *dt;
	काष्ठा lima_dump_chunk *chunk;
	काष्ठा lima_dump_chunk_pid *pid_chunk;
	काष्ठा lima_dump_chunk_buffer *buffer_chunk;
	u32 size, task_size, mem_size;
	पूर्णांक i;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	mutex_lock(&dev->error_task_list_lock);

	अगर (dev->dump.num_tasks >= lima_max_error_tasks) अणु
		dev_info(dev->dev, "fail to save task state from %s pid %d: "
			 "error task list is full\n", ctx->pname, ctx->pid);
		जाओ out;
	पूर्ण

	/* frame chunk */
	size = माप(काष्ठा lima_dump_chunk) + pipe->frame_size;
	/* process name chunk */
	size += माप(काष्ठा lima_dump_chunk) + माप(ctx->pname);
	/* pid chunk */
	size += माप(काष्ठा lima_dump_chunk);
	/* buffer chunks */
	क्रम (i = 0; i < task->num_bos; i++) अणु
		काष्ठा lima_bo *bo = task->bos[i];

		size += माप(काष्ठा lima_dump_chunk);
		size += bo->heap_size ? bo->heap_size : lima_bo_size(bo);
	पूर्ण

	task_size = size + माप(काष्ठा lima_dump_task);
	mem_size = task_size + माप(*et);
	et = kvदो_स्मृति(mem_size, GFP_KERNEL);
	अगर (!et) अणु
		dev_err(dev->dev, "fail to alloc task dump buffer of size %x\n",
			mem_size);
		जाओ out;
	पूर्ण

	et->data = et + 1;
	et->size = task_size;

	dt = et->data;
	स_रखो(dt, 0, माप(*dt));
	dt->id = pipe_id;
	dt->size = size;

	chunk = (काष्ठा lima_dump_chunk *)(dt + 1);
	स_रखो(chunk, 0, माप(*chunk));
	chunk->id = LIMA_DUMP_CHUNK_FRAME;
	chunk->size = pipe->frame_size;
	स_नकल(chunk + 1, task->frame, pipe->frame_size);
	dt->num_chunks++;

	chunk = (व्योम *)(chunk + 1) + chunk->size;
	स_रखो(chunk, 0, माप(*chunk));
	chunk->id = LIMA_DUMP_CHUNK_PROCESS_NAME;
	chunk->size = माप(ctx->pname);
	स_नकल(chunk + 1, ctx->pname, माप(ctx->pname));
	dt->num_chunks++;

	pid_chunk = (व्योम *)(chunk + 1) + chunk->size;
	स_रखो(pid_chunk, 0, माप(*pid_chunk));
	pid_chunk->id = LIMA_DUMP_CHUNK_PROCESS_ID;
	pid_chunk->pid = ctx->pid;
	dt->num_chunks++;

	buffer_chunk = (व्योम *)(pid_chunk + 1) + pid_chunk->size;
	क्रम (i = 0; i < task->num_bos; i++) अणु
		काष्ठा lima_bo *bo = task->bos[i];
		व्योम *data;

		स_रखो(buffer_chunk, 0, माप(*buffer_chunk));
		buffer_chunk->id = LIMA_DUMP_CHUNK_BUFFER;
		buffer_chunk->va = lima_vm_get_va(task->vm, bo);

		अगर (bo->heap_size) अणु
			buffer_chunk->size = bo->heap_size;

			data = vmap(bo->base.pages, bo->heap_size >> PAGE_SHIFT,
				    VM_MAP, pgprot_ग_लिखोcombine(PAGE_KERNEL));
			अगर (!data) अणु
				kvमुक्त(et);
				जाओ out;
			पूर्ण

			स_नकल(buffer_chunk + 1, data, buffer_chunk->size);

			vunmap(data);
		पूर्ण अन्यथा अणु
			buffer_chunk->size = lima_bo_size(bo);

			ret = drm_gem_shmem_vmap(&bo->base.base, &map);
			अगर (ret) अणु
				kvमुक्त(et);
				जाओ out;
			पूर्ण

			स_नकल(buffer_chunk + 1, map.vaddr, buffer_chunk->size);

			drm_gem_shmem_vunmap(&bo->base.base, &map);
		पूर्ण

		buffer_chunk = (व्योम *)(buffer_chunk + 1) + buffer_chunk->size;
		dt->num_chunks++;
	पूर्ण

	list_add(&et->list, &dev->error_task_list);
	dev->dump.size += et->size;
	dev->dump.num_tasks++;

	dev_info(dev->dev, "save error task state success\n");

out:
	mutex_unlock(&dev->error_task_list_lock);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat lima_sched_समयकरोut_job(काष्ठा drm_sched_job *job)
अणु
	काष्ठा lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	काष्ठा lima_sched_task *task = to_lima_task(job);
	काष्ठा lima_device *ldev = pipe->ldev;

	अगर (!pipe->error)
		DRM_ERROR("lima job timeout\n");

	drm_sched_stop(&pipe->base, &task->base);

	drm_sched_increase_karma(&task->base);

	lima_sched_build_error_task_list(task);

	pipe->task_error(pipe);

	अगर (pipe->bcast_mmu)
		lima_mmu_page_fault_resume(pipe->bcast_mmu);
	अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < pipe->num_mmu; i++)
			lima_mmu_page_fault_resume(pipe->mmu[i]);
	पूर्ण

	lima_vm_put(pipe->current_vm);
	pipe->current_vm = शून्य;
	pipe->current_task = शून्य;

	lima_pm_idle(ldev);

	drm_sched_resubmit_jobs(&pipe->base);
	drm_sched_start(&pipe->base, true);

	वापस DRM_GPU_SCHED_STAT_NOMINAL;
पूर्ण

अटल व्योम lima_sched_मुक्त_job(काष्ठा drm_sched_job *job)
अणु
	काष्ठा lima_sched_task *task = to_lima_task(job);
	काष्ठा lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	काष्ठा lima_vm *vm = task->vm;
	काष्ठा lima_bo **bos = task->bos;
	पूर्णांक i;

	dma_fence_put(task->fence);

	क्रम (i = 0; i < task->num_bos; i++)
		lima_vm_bo_del(vm, bos[i]);

	lima_sched_task_fini(task);
	kmem_cache_मुक्त(pipe->task_slab, task);
पूर्ण

अटल स्थिर काष्ठा drm_sched_backend_ops lima_sched_ops = अणु
	.dependency = lima_sched_dependency,
	.run_job = lima_sched_run_job,
	.समयकरोut_job = lima_sched_समयकरोut_job,
	.मुक्त_job = lima_sched_मुक्त_job,
पूर्ण;

अटल व्योम lima_sched_recover_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lima_sched_pipe *pipe =
		container_of(work, काष्ठा lima_sched_pipe, recover_work);
	पूर्णांक i;

	क्रम (i = 0; i < pipe->num_l2_cache; i++)
		lima_l2_cache_flush(pipe->l2_cache[i]);

	अगर (pipe->bcast_mmu) अणु
		lima_mmu_flush_tlb(pipe->bcast_mmu);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pipe->num_mmu; i++)
			lima_mmu_flush_tlb(pipe->mmu[i]);
	पूर्ण

	अगर (pipe->task_recover(pipe))
		drm_sched_fault(&pipe->base);
पूर्ण

पूर्णांक lima_sched_pipe_init(काष्ठा lima_sched_pipe *pipe, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक समयout = lima_sched_समयout_ms > 0 ?
			       lima_sched_समयout_ms : 500;

	pipe->fence_context = dma_fence_context_alloc(1);
	spin_lock_init(&pipe->fence_lock);

	INIT_WORK(&pipe->recover_work, lima_sched_recover_work);

	वापस drm_sched_init(&pipe->base, &lima_sched_ops, 1,
			      lima_job_hang_limit, msecs_to_jअगरfies(समयout),
			      शून्य, name);
पूर्ण

व्योम lima_sched_pipe_fini(काष्ठा lima_sched_pipe *pipe)
अणु
	drm_sched_fini(&pipe->base);
पूर्ण

व्योम lima_sched_pipe_task_करोne(काष्ठा lima_sched_pipe *pipe)
अणु
	काष्ठा lima_sched_task *task = pipe->current_task;
	काष्ठा lima_device *ldev = pipe->ldev;

	अगर (pipe->error) अणु
		अगर (task && task->recoverable)
			schedule_work(&pipe->recover_work);
		अन्यथा
			drm_sched_fault(&pipe->base);
	पूर्ण अन्यथा अणु
		pipe->task_fini(pipe);
		dma_fence_संकेत(task->fence);

		lima_pm_idle(ldev);
	पूर्ण
पूर्ण
