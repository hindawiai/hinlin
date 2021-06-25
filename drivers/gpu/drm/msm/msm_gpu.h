<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#अगर_अघोषित __MSM_GPU_H__
#घोषणा __MSM_GPU_H__

#समावेश <linux/adreno-smmu-priv.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "msm_drv.h"
#समावेश "msm_fence.h"
#समावेश "msm_ringbuffer.h"
#समावेश "msm_gem.h"

काष्ठा msm_gem_submit;
काष्ठा msm_gpu_perfcntr;
काष्ठा msm_gpu_state;

काष्ठा msm_gpu_config अणु
	स्थिर अक्षर *ioname;
	अचिन्हित पूर्णांक nr_rings;
पूर्ण;

/* So far, with hardware that I've seen to date, we can have:
 *  + zero, one, or two z180 2d cores
 *  + a3xx or a2xx 3d core, which share a common CP (the firmware
 *    क्रम the CP seems to implement some dअगरferent PM4 packet types
 *    but the basics of cmdstream submission are the same)
 *
 * Which means that the eventual complete "class" hierarchy, once
 * support क्रम all past and present hw is in place, becomes:
 *  + msm_gpu
 *    + adreno_gpu
 *      + a3xx_gpu
 *      + a2xx_gpu
 *    + z180_gpu
 */
काष्ठा msm_gpu_funcs अणु
	पूर्णांक (*get_param)(काष्ठा msm_gpu *gpu, uपूर्णांक32_t param, uपूर्णांक64_t *value);
	पूर्णांक (*hw_init)(काष्ठा msm_gpu *gpu);
	पूर्णांक (*pm_suspend)(काष्ठा msm_gpu *gpu);
	पूर्णांक (*pm_resume)(काष्ठा msm_gpu *gpu);
	व्योम (*submit)(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit);
	व्योम (*flush)(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring);
	irqवापस_t (*irq)(काष्ठा msm_gpu *irq);
	काष्ठा msm_ringbuffer *(*active_ring)(काष्ठा msm_gpu *gpu);
	व्योम (*recover)(काष्ठा msm_gpu *gpu);
	व्योम (*destroy)(काष्ठा msm_gpu *gpu);
#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
	/* show GPU status in debugfs: */
	व्योम (*show)(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
			काष्ठा drm_prपूर्णांकer *p);
	/* क्रम generation specअगरic debugfs: */
	व्योम (*debugfs_init)(काष्ठा msm_gpu *gpu, काष्ठा drm_minor *minor);
#पूर्ण_अगर
	अचिन्हित दीर्घ (*gpu_busy)(काष्ठा msm_gpu *gpu);
	काष्ठा msm_gpu_state *(*gpu_state_get)(काष्ठा msm_gpu *gpu);
	पूर्णांक (*gpu_state_put)(काष्ठा msm_gpu_state *state);
	अचिन्हित दीर्घ (*gpu_get_freq)(काष्ठा msm_gpu *gpu);
	व्योम (*gpu_set_freq)(काष्ठा msm_gpu *gpu, काष्ठा dev_pm_opp *opp);
	काष्ठा msm_gem_address_space *(*create_address_space)
		(काष्ठा msm_gpu *gpu, काष्ठा platक्रमm_device *pdev);
	काष्ठा msm_gem_address_space *(*create_निजी_address_space)
		(काष्ठा msm_gpu *gpu);
	uपूर्णांक32_t (*get_rptr)(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring);
पूर्ण;

काष्ठा msm_gpu अणु
	स्थिर अक्षर *name;
	काष्ठा drm_device *dev;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा msm_gpu_funcs *funcs;

	काष्ठा adreno_smmu_priv adreno_smmu;

	/* perक्रमmance counters (hw & sw): */
	spinlock_t perf_lock;
	bool perfcntr_active;
	काष्ठा अणु
		bool active;
		kसमय_प्रकार समय;
	पूर्ण last_sample;
	uपूर्णांक32_t totalसमय, activeसमय;    /* sw counters */
	uपूर्णांक32_t last_cntrs[5];            /* hw counters */
	स्थिर काष्ठा msm_gpu_perfcntr *perfcntrs;
	uपूर्णांक32_t num_perfcntrs;

	काष्ठा msm_ringbuffer *rb[MSM_GPU_MAX_RINGS];
	पूर्णांक nr_rings;

	/*
	 * List of GEM active objects on this gpu.  Protected by
	 * msm_drm_निजी::mm_lock
	 */
	काष्ठा list_head active_list;

	/* करोes gpu need hw_init? */
	bool needs_hw_init;

	/* number of GPU hangs (क्रम all contexts) */
	पूर्णांक global_faults;

	व्योम __iomem *mmio;
	पूर्णांक irq;

	काष्ठा msm_gem_address_space *aspace;

	/* Power Control: */
	काष्ठा regulator *gpu_reg, *gpu_cx;
	काष्ठा clk_bulk_data *grp_clks;
	पूर्णांक nr_घड़ीs;
	काष्ठा clk *ebi1_clk, *core_clk, *rbbmसमयr_clk;
	uपूर्णांक32_t fast_rate;

	/* The gfx-mem पूर्णांकerconnect path that's used by all GPU types. */
	काष्ठा icc_path *icc_path;

	/*
	 * Second पूर्णांकerconnect path क्रम some A3xx and all A4xx GPUs to the
	 * On Chip MEMory (OCMEM).
	 */
	काष्ठा icc_path *ocmem_icc_path;

	/* Hang and Inactivity Detection:
	 */
#घोषणा DRM_MSM_INACTIVE_PERIOD   66 /* in ms (roughly four frames) */

#घोषणा DRM_MSM_HANGCHECK_PERIOD 500 /* in ms */
#घोषणा DRM_MSM_HANGCHECK_JIFFIES msecs_to_jअगरfies(DRM_MSM_HANGCHECK_PERIOD)
	काष्ठा समयr_list hangcheck_समयr;

	/* work क्रम handling GPU recovery: */
	काष्ठा kthपढ़ो_work recover_work;

	/* work क्रम handling active-list retiring: */
	काष्ठा kthपढ़ो_work retire_work;

	/* worker क्रम retire/recover: */
	काष्ठा kthपढ़ो_worker *worker;

	काष्ठा drm_gem_object *memptrs_bo;

	काष्ठा अणु
		काष्ठा devfreq *devfreq;
		u64 busy_cycles;
		kसमय_प्रकार समय;
	पूर्ण devfreq;

	uपूर्णांक32_t suspend_count;

	काष्ठा msm_gpu_state *crashstate;
	/* True अगर the hardware supports expanded apriv (a650 and newer) */
	bool hw_apriv;

	काष्ठा thermal_cooling_device *cooling;
पूर्ण;

अटल अंतरभूत काष्ठा msm_gpu *dev_to_gpu(काष्ठा device *dev)
अणु
	काष्ठा adreno_smmu_priv *adreno_smmu = dev_get_drvdata(dev);
	वापस container_of(adreno_smmu, काष्ठा msm_gpu, adreno_smmu);
पूर्ण

/* It turns out that all tarमाला_लो use the same ringbuffer size */
#घोषणा MSM_GPU_RINGBUFFER_SZ SZ_32K
#घोषणा MSM_GPU_RINGBUFFER_BLKSIZE 32

#घोषणा MSM_GPU_RB_CNTL_DEFAULT \
		(AXXX_CP_RB_CNTL_BUFSZ(ilog2(MSM_GPU_RINGBUFFER_SZ / 8)) | \
		AXXX_CP_RB_CNTL_BLKSZ(ilog2(MSM_GPU_RINGBUFFER_BLKSIZE / 8)))

अटल अंतरभूत bool msm_gpu_active(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		अगर (ring->seqno > ring->memptrs->fence)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Perf-Counters:
 * The select_reg and select_val are just there क्रम the benefit of the child
 * class that actually enables the perf counter..  but msm_gpu base class
 * will handle sampling/displaying the counters.
 */

काष्ठा msm_gpu_perfcntr अणु
	uपूर्णांक32_t select_reg;
	uपूर्णांक32_t sample_reg;
	uपूर्णांक32_t select_val;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा msm_gpu_submitqueue अणु
	पूर्णांक id;
	u32 flags;
	u32 prio;
	पूर्णांक faults;
	काष्ठा msm_file_निजी *ctx;
	काष्ठा list_head node;
	काष्ठा kref ref;
पूर्ण;

काष्ठा msm_gpu_state_bo अणु
	u64 iova;
	माप_प्रकार size;
	व्योम *data;
	bool encoded;
पूर्ण;

काष्ठा msm_gpu_state अणु
	काष्ठा kref ref;
	काष्ठा बारpec64 समय;

	काष्ठा अणु
		u64 iova;
		u32 fence;
		u32 seqno;
		u32 rptr;
		u32 wptr;
		व्योम *data;
		पूर्णांक data_size;
		bool encoded;
	पूर्ण ring[MSM_GPU_MAX_RINGS];

	पूर्णांक nr_रेजिस्टरs;
	u32 *रेजिस्टरs;

	u32 rbbm_status;

	अक्षर *comm;
	अक्षर *cmd;

	पूर्णांक nr_bos;
	काष्ठा msm_gpu_state_bo *bos;
पूर्ण;

अटल अंतरभूत व्योम gpu_ग_लिखो(काष्ठा msm_gpu *gpu, u32 reg, u32 data)
अणु
	msm_ग_लिखोl(data, gpu->mmio + (reg << 2));
पूर्ण

अटल अंतरभूत u32 gpu_पढ़ो(काष्ठा msm_gpu *gpu, u32 reg)
अणु
	वापस msm_पढ़ोl(gpu->mmio + (reg << 2));
पूर्ण

अटल अंतरभूत व्योम gpu_rmw(काष्ठा msm_gpu *gpu, u32 reg, u32 mask, u32 or)
अणु
	msm_rmw(gpu->mmio + (reg << 2), mask, or);
पूर्ण

अटल अंतरभूत u64 gpu_पढ़ो64(काष्ठा msm_gpu *gpu, u32 lo, u32 hi)
अणु
	u64 val;

	/*
	 * Why not a पढ़ोq here? Two reasons: 1) many of the LO रेजिस्टरs are
	 * not quad word aligned and 2) the GPU hardware designers have a bit
	 * of a history of putting रेजिस्टरs where they fit, especially in
	 * spins. The दीर्घer a GPU family goes the higher the chance that
	 * we'll get burned.  We could करो a series of validity checks अगर we
	 * wanted to, but really is a पढ़ोq() that much better? Nah.
	 */

	/*
	 * For some lo/hi रेजिस्टरs (like perfcounters), the hi value is latched
	 * when the lo is पढ़ो, so make sure to पढ़ो the lo first to trigger
	 * that
	 */
	val = (u64) msm_पढ़ोl(gpu->mmio + (lo << 2));
	val |= ((u64) msm_पढ़ोl(gpu->mmio + (hi << 2)) << 32);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम gpu_ग_लिखो64(काष्ठा msm_gpu *gpu, u32 lo, u32 hi, u64 val)
अणु
	/* Why not a ग_लिखोq here? Read the screed above */
	msm_ग_लिखोl(lower_32_bits(val), gpu->mmio + (lo << 2));
	msm_ग_लिखोl(upper_32_bits(val), gpu->mmio + (hi << 2));
पूर्ण

पूर्णांक msm_gpu_pm_suspend(काष्ठा msm_gpu *gpu);
पूर्णांक msm_gpu_pm_resume(काष्ठा msm_gpu *gpu);
व्योम msm_gpu_resume_devfreq(काष्ठा msm_gpu *gpu);

पूर्णांक msm_gpu_hw_init(काष्ठा msm_gpu *gpu);

व्योम msm_gpu_perfcntr_start(काष्ठा msm_gpu *gpu);
व्योम msm_gpu_perfcntr_stop(काष्ठा msm_gpu *gpu);
पूर्णांक msm_gpu_perfcntr_sample(काष्ठा msm_gpu *gpu, uपूर्णांक32_t *activeसमय,
		uपूर्णांक32_t *totalसमय, uपूर्णांक32_t ncntrs, uपूर्णांक32_t *cntrs);

व्योम msm_gpu_retire(काष्ठा msm_gpu *gpu);
व्योम msm_gpu_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit);

पूर्णांक msm_gpu_init(काष्ठा drm_device *drm, काष्ठा platक्रमm_device *pdev,
		काष्ठा msm_gpu *gpu, स्थिर काष्ठा msm_gpu_funcs *funcs,
		स्थिर अक्षर *name, काष्ठा msm_gpu_config *config);

काष्ठा msm_gem_address_space *
msm_gpu_create_निजी_address_space(काष्ठा msm_gpu *gpu, काष्ठा task_काष्ठा *task);

व्योम msm_gpu_cleanup(काष्ठा msm_gpu *gpu);

काष्ठा msm_gpu *adreno_load_gpu(काष्ठा drm_device *dev);
व्योम __init adreno_रेजिस्टर(व्योम);
व्योम __निकास adreno_unरेजिस्टर(व्योम);

अटल अंतरभूत व्योम msm_submitqueue_put(काष्ठा msm_gpu_submitqueue *queue)
अणु
	अगर (queue)
		kref_put(&queue->ref, msm_submitqueue_destroy);
पूर्ण

अटल अंतरभूत काष्ठा msm_gpu_state *msm_gpu_crashstate_get(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_gpu_state *state = शून्य;

	mutex_lock(&gpu->dev->काष्ठा_mutex);

	अगर (gpu->crashstate) अणु
		kref_get(&gpu->crashstate->ref);
		state = gpu->crashstate;
	पूर्ण

	mutex_unlock(&gpu->dev->काष्ठा_mutex);

	वापस state;
पूर्ण

अटल अंतरभूत व्योम msm_gpu_crashstate_put(काष्ठा msm_gpu *gpu)
अणु
	mutex_lock(&gpu->dev->काष्ठा_mutex);

	अगर (gpu->crashstate) अणु
		अगर (gpu->funcs->gpu_state_put(gpu->crashstate))
			gpu->crashstate = शून्य;
	पूर्ण

	mutex_unlock(&gpu->dev->काष्ठा_mutex);
पूर्ण

/*
 * Simple macro to semi-cleanly add the MAP_PRIV flag क्रम tarमाला_लो that can
 * support expanded privileges
 */
#घोषणा check_apriv(gpu, flags) \
	(((gpu)->hw_apriv ? MSM_BO_MAP_PRIV : 0) | (flags))


#पूर्ण_अगर /* __MSM_GPU_H__ */
