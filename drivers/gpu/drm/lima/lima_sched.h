<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_SCHED_H__
#घोषणा __LIMA_SCHED_H__

#समावेश <drm/gpu_scheduler.h>
#समावेश <linux/list.h>
#समावेश <linux/xarray.h>

काष्ठा lima_device;
काष्ठा lima_vm;

काष्ठा lima_sched_error_task अणु
	काष्ठा list_head list;
	व्योम *data;
	u32 size;
पूर्ण;

काष्ठा lima_sched_task अणु
	काष्ठा drm_sched_job base;

	काष्ठा lima_vm *vm;
	व्योम *frame;

	काष्ठा xarray deps;
	अचिन्हित दीर्घ last_dep;

	काष्ठा lima_bo **bos;
	पूर्णांक num_bos;

	bool recoverable;
	काष्ठा lima_bo *heap;

	/* pipe fence */
	काष्ठा dma_fence *fence;
पूर्ण;

काष्ठा lima_sched_context अणु
	काष्ठा drm_sched_entity base;
पूर्ण;

#घोषणा LIMA_SCHED_PIPE_MAX_MMU       8
#घोषणा LIMA_SCHED_PIPE_MAX_L2_CACHE  2
#घोषणा LIMA_SCHED_PIPE_MAX_PROCESSOR 8

काष्ठा lima_ip;

काष्ठा lima_sched_pipe अणु
	काष्ठा drm_gpu_scheduler base;

	u64 fence_context;
	u32 fence_seqno;
	spinlock_t fence_lock;

	काष्ठा lima_device *ldev;

	काष्ठा lima_sched_task *current_task;
	काष्ठा lima_vm *current_vm;

	काष्ठा lima_ip *mmu[LIMA_SCHED_PIPE_MAX_MMU];
	पूर्णांक num_mmu;

	काष्ठा lima_ip *l2_cache[LIMA_SCHED_PIPE_MAX_L2_CACHE];
	पूर्णांक num_l2_cache;

	काष्ठा lima_ip *processor[LIMA_SCHED_PIPE_MAX_PROCESSOR];
	पूर्णांक num_processor;

	काष्ठा lima_ip *bcast_processor;
	काष्ठा lima_ip *bcast_mmu;

	u32 करोne;
	bool error;
	atomic_t task;

	पूर्णांक frame_size;
	काष्ठा kmem_cache *task_slab;

	पूर्णांक (*task_validate)(काष्ठा lima_sched_pipe *pipe, काष्ठा lima_sched_task *task);
	व्योम (*task_run)(काष्ठा lima_sched_pipe *pipe, काष्ठा lima_sched_task *task);
	व्योम (*task_fini)(काष्ठा lima_sched_pipe *pipe);
	व्योम (*task_error)(काष्ठा lima_sched_pipe *pipe);
	व्योम (*task_mmu_error)(काष्ठा lima_sched_pipe *pipe);
	पूर्णांक (*task_recover)(काष्ठा lima_sched_pipe *pipe);

	काष्ठा work_काष्ठा recover_work;
पूर्ण;

पूर्णांक lima_sched_task_init(काष्ठा lima_sched_task *task,
			 काष्ठा lima_sched_context *context,
			 काष्ठा lima_bo **bos, पूर्णांक num_bos,
			 काष्ठा lima_vm *vm);
व्योम lima_sched_task_fini(काष्ठा lima_sched_task *task);

पूर्णांक lima_sched_context_init(काष्ठा lima_sched_pipe *pipe,
			    काष्ठा lima_sched_context *context,
			    atomic_t *guilty);
व्योम lima_sched_context_fini(काष्ठा lima_sched_pipe *pipe,
			     काष्ठा lima_sched_context *context);
काष्ठा dma_fence *lima_sched_context_queue_task(काष्ठा lima_sched_context *context,
						काष्ठा lima_sched_task *task);

पूर्णांक lima_sched_pipe_init(काष्ठा lima_sched_pipe *pipe, स्थिर अक्षर *name);
व्योम lima_sched_pipe_fini(काष्ठा lima_sched_pipe *pipe);
व्योम lima_sched_pipe_task_करोne(काष्ठा lima_sched_pipe *pipe);

अटल अंतरभूत व्योम lima_sched_pipe_mmu_error(काष्ठा lima_sched_pipe *pipe)
अणु
	pipe->error = true;
	pipe->task_mmu_error(pipe);
पूर्ण

पूर्णांक lima_sched_slab_init(व्योम);
व्योम lima_sched_slab_fini(व्योम);

#पूर्ण_अगर
