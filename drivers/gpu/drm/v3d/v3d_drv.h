<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2015-2018 Broadcom */

#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/gpu_scheduler.h>

#समावेश "uapi/drm/v3d_drm.h"

काष्ठा clk;
काष्ठा platक्रमm_device;
काष्ठा reset_control;

#घोषणा GMP_GRANULARITY (128 * 1024)

/* Enum क्रम each of the V3D queues. */
क्रमागत v3d_queue अणु
	V3D_BIN,
	V3D_RENDER,
	V3D_TFU,
	V3D_CSD,
	V3D_CACHE_CLEAN,
पूर्ण;

#घोषणा V3D_MAX_QUEUES (V3D_CACHE_CLEAN + 1)

काष्ठा v3d_queue_state अणु
	काष्ठा drm_gpu_scheduler sched;

	u64 fence_context;
	u64 emit_seqno;
पूर्ण;

काष्ठा v3d_dev अणु
	काष्ठा drm_device drm;

	/* Short representation (e.g. 33, 41) of the V3D tech version
	 * and revision.
	 */
	पूर्णांक ver;
	bool single_irq_line;

	व्योम __iomem *hub_regs;
	व्योम __iomem *core_regs[3];
	व्योम __iomem *bridge_regs;
	व्योम __iomem *gca_regs;
	काष्ठा clk *clk;
	काष्ठा reset_control *reset;

	/* Virtual and DMA addresses of the single shared page table. */
	अस्थिर u32 *pt;
	dma_addr_t pt_paddr;

	/* Virtual and DMA addresses of the MMU's scratch page.  When
	 * a पढ़ो or ग_लिखो is invalid in the MMU, it will be
	 * redirected here.
	 */
	व्योम *mmu_scratch;
	dma_addr_t mmu_scratch_paddr;
	/* भव address bits from V3D to the MMU. */
	पूर्णांक va_width;

	/* Number of V3D cores. */
	u32 cores;

	/* Allocator managing the address space.  All units are in
	 * number of pages.
	 */
	काष्ठा drm_mm mm;
	spinlock_t mm_lock;

	काष्ठा work_काष्ठा overflow_mem_work;

	काष्ठा v3d_bin_job *bin_job;
	काष्ठा v3d_render_job *render_job;
	काष्ठा v3d_tfu_job *tfu_job;
	काष्ठा v3d_csd_job *csd_job;

	काष्ठा v3d_queue_state queue[V3D_MAX_QUEUES];

	/* Spinlock used to synchronize the overflow memory
	 * management against bin job submission.
	 */
	spinlock_t job_lock;

	/* Protects bo_stats */
	काष्ठा mutex bo_lock;

	/* Lock taken when resetting the GPU, to keep multiple
	 * processes from trying to park the scheduler thपढ़ोs and
	 * reset at once.
	 */
	काष्ठा mutex reset_lock;

	/* Lock taken when creating and pushing the GPU scheduler
	 * jobs, to keep the sched-fence seqnos in order.
	 */
	काष्ठा mutex sched_lock;

	/* Lock taken during a cache clean and when initiating an L2
	 * flush, to keep L2 flushes from पूर्णांकerfering with the
	 * synchronous L2 cleans.
	 */
	काष्ठा mutex cache_clean_lock;

	काष्ठा अणु
		u32 num_allocated;
		u32 pages_allocated;
	पूर्ण bo_stats;
पूर्ण;

अटल अंतरभूत काष्ठा v3d_dev *
to_v3d_dev(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा v3d_dev, drm);
पूर्ण

अटल अंतरभूत bool
v3d_has_csd(काष्ठा v3d_dev *v3d)
अणु
	वापस v3d->ver >= 41;
पूर्ण

#घोषणा v3d_to_pdev(v3d) to_platक्रमm_device((v3d)->drm.dev)

/* The per-fd काष्ठा, which tracks the MMU mappings. */
काष्ठा v3d_file_priv अणु
	काष्ठा v3d_dev *v3d;

	काष्ठा drm_sched_entity sched_entity[V3D_MAX_QUEUES];
पूर्ण;

काष्ठा v3d_bo अणु
	काष्ठा drm_gem_shmem_object base;

	काष्ठा drm_mm_node node;

	/* List entry क्रम the BO's position in
	 * v3d_render_job->unref_list
	 */
	काष्ठा list_head unref_head;
पूर्ण;

अटल अंतरभूत काष्ठा v3d_bo *
to_v3d_bo(काष्ठा drm_gem_object *bo)
अणु
	वापस (काष्ठा v3d_bo *)bo;
पूर्ण

काष्ठा v3d_fence अणु
	काष्ठा dma_fence base;
	काष्ठा drm_device *dev;
	/* v3d seqno क्रम संकेतed() test */
	u64 seqno;
	क्रमागत v3d_queue queue;
पूर्ण;

अटल अंतरभूत काष्ठा v3d_fence *
to_v3d_fence(काष्ठा dma_fence *fence)
अणु
	वापस (काष्ठा v3d_fence *)fence;
पूर्ण

#घोषणा V3D_READ(offset) पढ़ोl(v3d->hub_regs + offset)
#घोषणा V3D_WRITE(offset, val) ग_लिखोl(val, v3d->hub_regs + offset)

#घोषणा V3D_BRIDGE_READ(offset) पढ़ोl(v3d->bridge_regs + offset)
#घोषणा V3D_BRIDGE_WRITE(offset, val) ग_लिखोl(val, v3d->bridge_regs + offset)

#घोषणा V3D_GCA_READ(offset) पढ़ोl(v3d->gca_regs + offset)
#घोषणा V3D_GCA_WRITE(offset, val) ग_लिखोl(val, v3d->gca_regs + offset)

#घोषणा V3D_CORE_READ(core, offset) पढ़ोl(v3d->core_regs[core] + offset)
#घोषणा V3D_CORE_WRITE(core, offset, val) ग_लिखोl(val, v3d->core_regs[core] + offset)

काष्ठा v3d_job अणु
	काष्ठा drm_sched_job base;

	काष्ठा kref refcount;

	काष्ठा v3d_dev *v3d;

	/* This is the array of BOs that were looked up at the start
	 * of submission.
	 */
	काष्ठा drm_gem_object **bo;
	u32 bo_count;

	/* Array of काष्ठा dma_fence * to block on beक्रमe submitting this job.
	 */
	काष्ठा xarray deps;
	अचिन्हित दीर्घ last_dep;

	/* v3d fence to be संकेतed by IRQ handler when the job is complete. */
	काष्ठा dma_fence *irq_fence;

	/* scheduler fence क्रम when the job is considered complete and
	 * the BO reservations can be released.
	 */
	काष्ठा dma_fence *करोne_fence;

	/* Callback क्रम the मुक्तing of the job on refcount going to 0. */
	व्योम (*मुक्त)(काष्ठा kref *ref);
पूर्ण;

काष्ठा v3d_bin_job अणु
	काष्ठा v3d_job base;

	/* GPU भव addresses of the start/end of the CL job. */
	u32 start, end;

	u32 समयकरोut_ctca, समयकरोut_ctra;

	/* Corresponding render job, क्रम attaching our overflow memory. */
	काष्ठा v3d_render_job *render;

	/* Submitted tile memory allocation start/size, tile state. */
	u32 qma, qms, qts;
पूर्ण;

काष्ठा v3d_render_job अणु
	काष्ठा v3d_job base;

	/* GPU भव addresses of the start/end of the CL job. */
	u32 start, end;

	u32 समयकरोut_ctca, समयकरोut_ctra;

	/* List of overflow BOs used in the job that need to be
	 * released once the job is complete.
	 */
	काष्ठा list_head unref_list;
पूर्ण;

काष्ठा v3d_tfu_job अणु
	काष्ठा v3d_job base;

	काष्ठा drm_v3d_submit_tfu args;
पूर्ण;

काष्ठा v3d_csd_job अणु
	काष्ठा v3d_job base;

	u32 समयकरोut_batches;

	काष्ठा drm_v3d_submit_csd args;
पूर्ण;

/**
 * __रुको_क्रम - magic रुको macro
 *
 * Macro to help aव्योम खोलो coding check/रुको/समयout patterns. Note that it's
 * important that we check the condition again after having समयd out, since the
 * समयout could be due to preemption or similar and we've never had a chance to
 * check the condition beक्रमe the समयout.
 */
#घोषणा __रुको_क्रम(OP, COND, US, Wmin, Wmax) (अणु \
	स्थिर kसमय_प्रकार end__ = kसमय_add_ns(kसमय_get_raw(), 1000ll * (US)); \
	दीर्घ रुको__ = (Wmin); /* recommended min क्रम usleep is 10 us */	\
	पूर्णांक ret__;							\
	might_sleep();							\
	क्रम (;;) अणु							\
		स्थिर bool expired__ = kसमय_after(kसमय_get_raw(), end__); \
		OP;							\
		/* Guarantee COND check prior to समयout */		\
		barrier();						\
		अगर (COND) अणु						\
			ret__ = 0;					\
			अवरोध;						\
		पूर्ण							\
		अगर (expired__) अणु					\
			ret__ = -ETIMEDOUT;				\
			अवरोध;						\
		पूर्ण							\
		usleep_range(रुको__, रुको__ * 2);			\
		अगर (रुको__ < (Wmax))					\
			रुको__ <<= 1;					\
	पूर्ण								\
	ret__;								\
पूर्ण)

#घोषणा _रुको_क्रम(COND, US, Wmin, Wmax)	__रुको_क्रम(, (COND), (US), (Wmin), \
						   (Wmax))
#घोषणा रुको_क्रम(COND, MS)		_रुको_क्रम((COND), (MS) * 1000, 10, 1000)

अटल अंतरभूत अचिन्हित दीर्घ nsecs_to_jअगरfies_समयout(स्थिर u64 n)
अणु
	/* nsecs_to_jअगरfies64() करोes not guard against overflow */
	अगर (NSEC_PER_SEC % HZ &&
	    भाग_u64(n, NSEC_PER_SEC) >= MAX_JIFFY_OFFSET / HZ)
		वापस MAX_JIFFY_OFFSET;

	वापस min_t(u64, MAX_JIFFY_OFFSET, nsecs_to_jअगरfies64(n) + 1);
पूर्ण

/* v3d_bo.c */
काष्ठा drm_gem_object *v3d_create_object(काष्ठा drm_device *dev, माप_प्रकार size);
व्योम v3d_मुक्त_object(काष्ठा drm_gem_object *gem_obj);
काष्ठा v3d_bo *v3d_bo_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
			     माप_प्रकार size);
पूर्णांक v3d_create_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक v3d_mmap_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv);
पूर्णांक v3d_get_bo_offset_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv);
काष्ठा drm_gem_object *v3d_prime_import_sg_table(काष्ठा drm_device *dev,
						 काष्ठा dma_buf_attachment *attach,
						 काष्ठा sg_table *sgt);

/* v3d_debugfs.c */
व्योम v3d_debugfs_init(काष्ठा drm_minor *minor);

/* v3d_fence.c */
बाह्य स्थिर काष्ठा dma_fence_ops v3d_fence_ops;
काष्ठा dma_fence *v3d_fence_create(काष्ठा v3d_dev *v3d, क्रमागत v3d_queue queue);

/* v3d_gem.c */
पूर्णांक v3d_gem_init(काष्ठा drm_device *dev);
व्योम v3d_gem_destroy(काष्ठा drm_device *dev);
पूर्णांक v3d_submit_cl_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक v3d_submit_tfu_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक v3d_submit_csd_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक v3d_रुको_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv);
व्योम v3d_job_put(काष्ठा v3d_job *job);
व्योम v3d_reset(काष्ठा v3d_dev *v3d);
व्योम v3d_invalidate_caches(काष्ठा v3d_dev *v3d);
व्योम v3d_clean_caches(काष्ठा v3d_dev *v3d);

/* v3d_irq.c */
पूर्णांक v3d_irq_init(काष्ठा v3d_dev *v3d);
व्योम v3d_irq_enable(काष्ठा v3d_dev *v3d);
व्योम v3d_irq_disable(काष्ठा v3d_dev *v3d);
व्योम v3d_irq_reset(काष्ठा v3d_dev *v3d);

/* v3d_mmu.c */
पूर्णांक v3d_mmu_get_offset(काष्ठा drm_file *file_priv, काष्ठा v3d_bo *bo,
		       u32 *offset);
पूर्णांक v3d_mmu_set_page_table(काष्ठा v3d_dev *v3d);
व्योम v3d_mmu_insert_ptes(काष्ठा v3d_bo *bo);
व्योम v3d_mmu_हटाओ_ptes(काष्ठा v3d_bo *bo);

/* v3d_sched.c */
पूर्णांक v3d_sched_init(काष्ठा v3d_dev *v3d);
व्योम v3d_sched_fini(काष्ठा v3d_dev *v3d);
