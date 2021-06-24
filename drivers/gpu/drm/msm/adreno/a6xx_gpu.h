<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2017, 2019 The Linux Foundation. All rights reserved. */

#अगर_अघोषित __A6XX_GPU_H__
#घोषणा __A6XX_GPU_H__


#समावेश "adreno_gpu.h"
#समावेश "a6xx.xml.h"

#समावेश "a6xx_gmu.h"

बाह्य bool hang_debug;

काष्ठा a6xx_gpu अणु
	काष्ठा adreno_gpu base;

	काष्ठा drm_gem_object *sqe_bo;
	uपूर्णांक64_t sqe_iova;

	काष्ठा msm_ringbuffer *cur_ring;
	काष्ठा msm_file_निजी *cur_ctx;

	काष्ठा a6xx_gmu gmu;

	काष्ठा drm_gem_object *shaकरोw_bo;
	uपूर्णांक64_t shaकरोw_iova;
	uपूर्णांक32_t *shaकरोw;

	bool has_whereami;

	व्योम __iomem *llc_mmio;
	व्योम *llc_slice;
	व्योम *htw_llc_slice;
	bool have_mmu500;

	काष्ठा opp_table *opp_table;
पूर्ण;

#घोषणा to_a6xx_gpu(x) container_of(x, काष्ठा a6xx_gpu, base)

/*
 * Given a रेजिस्टर and a count, वापस a value to program पूर्णांकo
 * REG_CP_PROTECT_REG(n) - this will block both पढ़ोs and ग_लिखोs क्रम _len
 * रेजिस्टरs starting at _reg.
 */
#घोषणा A6XX_PROTECT_NORDWR(_reg, _len) \
	((1 << 31) | \
	(((_len) & 0x3FFF) << 18) | ((_reg) & 0x3FFFF))

/*
 * Same as above, but allow पढ़ोs over the range. For areas of mixed use (such
 * as perक्रमmance counters) this allows us to protect a much larger range with a
 * single रेजिस्टर
 */
#घोषणा A6XX_PROTECT_RDONLY(_reg, _len) \
	((((_len) & 0x3FFF) << 18) | ((_reg) & 0x3FFFF))

अटल अंतरभूत bool a6xx_has_gbअगर(काष्ठा adreno_gpu *gpu)
अणु
	अगर(adreno_is_a630(gpu))
		वापस false;

	वापस true;
पूर्ण

#घोषणा shaकरोwptr(_a6xx_gpu, _ring) ((_a6xx_gpu)->shaकरोw_iova + \
		((_ring)->id * माप(uपूर्णांक32_t)))

पूर्णांक a6xx_gmu_resume(काष्ठा a6xx_gpu *gpu);
पूर्णांक a6xx_gmu_stop(काष्ठा a6xx_gpu *gpu);

पूर्णांक a6xx_gmu_रुको_क्रम_idle(काष्ठा a6xx_gmu *gmu);

bool a6xx_gmu_isidle(काष्ठा a6xx_gmu *gmu);

पूर्णांक a6xx_gmu_set_oob(काष्ठा a6xx_gmu *gmu, क्रमागत a6xx_gmu_oob_state state);
व्योम a6xx_gmu_clear_oob(काष्ठा a6xx_gmu *gmu, क्रमागत a6xx_gmu_oob_state state);

पूर्णांक a6xx_gmu_init(काष्ठा a6xx_gpu *a6xx_gpu, काष्ठा device_node *node);
व्योम a6xx_gmu_हटाओ(काष्ठा a6xx_gpu *a6xx_gpu);

व्योम a6xx_gmu_set_freq(काष्ठा msm_gpu *gpu, काष्ठा dev_pm_opp *opp);
अचिन्हित दीर्घ a6xx_gmu_get_freq(काष्ठा msm_gpu *gpu);

व्योम a6xx_show(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
		काष्ठा drm_prपूर्णांकer *p);

काष्ठा msm_gpu_state *a6xx_gpu_state_get(काष्ठा msm_gpu *gpu);
पूर्णांक a6xx_gpu_state_put(काष्ठा msm_gpu_state *state);

#पूर्ण_अगर /* __A6XX_GPU_H__ */
