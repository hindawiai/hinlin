<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017 Etnaviv Project
 * Copyright (C) 2017 Zodiac Inflight Innovations
 */

#अगर_अघोषित __ETNAVIV_PERFMON_H__
#घोषणा __ETNAVIV_PERFMON_H__

काष्ठा etnaviv_gpu;
काष्ठा drm_etnaviv_pm_करोमुख्य;
काष्ठा drm_etnaviv_pm_संकेत;

काष्ठा etnaviv_perfmon_request
अणु
	u32 flags;
	u8 करोमुख्य;
	u8 संकेत;
	u32 sequence;

	/* bo to store a value */
	u32 *bo_vma;
	u32 offset;
पूर्ण;

पूर्णांक etnaviv_pm_query_करोm(काष्ठा etnaviv_gpu *gpu,
	काष्ठा drm_etnaviv_pm_करोमुख्य *करोमुख्य);

पूर्णांक etnaviv_pm_query_sig(काष्ठा etnaviv_gpu *gpu,
	काष्ठा drm_etnaviv_pm_संकेत *संकेत);

पूर्णांक etnaviv_pm_req_validate(स्थिर काष्ठा drm_etnaviv_gem_submit_pmr *r,
	u32 exec_state);

व्योम etnaviv_perfmon_process(काष्ठा etnaviv_gpu *gpu,
	स्थिर काष्ठा etnaviv_perfmon_request *pmr, u32 exec_state);

#पूर्ण_अगर /* __ETNAVIV_PERFMON_H__ */
