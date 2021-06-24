<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2019 Collabora ltd. */

#अगर_अघोषित __PANFROST_JOB_H__
#घोषणा __PANFROST_JOB_H__

#समावेश <uapi/drm/panfrost_drm.h>
#समावेश <drm/gpu_scheduler.h>

काष्ठा panfrost_device;
काष्ठा panfrost_gem_object;
काष्ठा panfrost_file_priv;

काष्ठा panfrost_job अणु
	काष्ठा drm_sched_job base;

	काष्ठा kref refcount;

	काष्ठा panfrost_device *pfdev;
	काष्ठा panfrost_file_priv *file_priv;

	/* Optional fences userspace can pass in क्रम the job to depend on. */
	काष्ठा dma_fence **in_fences;
	u32 in_fence_count;

	/* Fence to be संकेतed by IRQ handler when the job is complete. */
	काष्ठा dma_fence *करोne_fence;

	__u64 jc;
	__u32 requirements;
	__u32 flush_id;

	/* Exclusive fences we have taken from the BOs to रुको क्रम */
	काष्ठा dma_fence **implicit_fences;
	काष्ठा panfrost_gem_mapping **mappings;
	काष्ठा drm_gem_object **bos;
	u32 bo_count;

	/* Fence to be संकेतed by drm-sched once its करोne with the job */
	काष्ठा dma_fence *render_करोne_fence;
पूर्ण;

पूर्णांक panfrost_job_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_job_fini(काष्ठा panfrost_device *pfdev);
पूर्णांक panfrost_job_खोलो(काष्ठा panfrost_file_priv *panfrost_priv);
व्योम panfrost_job_बंद(काष्ठा panfrost_file_priv *panfrost_priv);
पूर्णांक panfrost_job_push(काष्ठा panfrost_job *job);
व्योम panfrost_job_put(काष्ठा panfrost_job *job);
व्योम panfrost_job_enable_पूर्णांकerrupts(काष्ठा panfrost_device *pfdev);
पूर्णांक panfrost_job_is_idle(काष्ठा panfrost_device *pfdev);

#पूर्ण_अगर
