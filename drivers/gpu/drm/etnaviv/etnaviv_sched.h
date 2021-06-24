<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_SCHED_H__
#घोषणा __ETNAVIV_SCHED_H__

#समावेश <drm/gpu_scheduler.h>

काष्ठा etnaviv_gpu;

अटल अंतरभूत
काष्ठा etnaviv_gem_submit *to_etnaviv_submit(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा etnaviv_gem_submit, sched_job);
पूर्ण

पूर्णांक etnaviv_sched_init(काष्ठा etnaviv_gpu *gpu);
व्योम etnaviv_sched_fini(काष्ठा etnaviv_gpu *gpu);
पूर्णांक etnaviv_sched_push_job(काष्ठा drm_sched_entity *sched_entity,
			   काष्ठा etnaviv_gem_submit *submit);

#पूर्ण_अगर /* __ETNAVIV_SCHED_H__ */
