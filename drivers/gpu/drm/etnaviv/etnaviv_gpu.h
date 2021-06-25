<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_GPU_H__
#घोषणा __ETNAVIV_GPU_H__

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_mmu.h"
#समावेश "etnaviv_drv.h"

काष्ठा etnaviv_gem_submit;
काष्ठा etnaviv_vram_mapping;

काष्ठा etnaviv_chip_identity अणु
	u32 model;
	u32 revision;
	u32 product_id;
	u32 customer_id;
	u32 eco_id;

	/* Supported feature fields. */
	u32 features;

	/* Supported minor feature fields. */
	u32 minor_features0;
	u32 minor_features1;
	u32 minor_features2;
	u32 minor_features3;
	u32 minor_features4;
	u32 minor_features5;
	u32 minor_features6;
	u32 minor_features7;
	u32 minor_features8;
	u32 minor_features9;
	u32 minor_features10;
	u32 minor_features11;

	/* Number of streams supported. */
	u32 stream_count;

	/* Total number of temporary रेजिस्टरs per thपढ़ो. */
	u32 रेजिस्टर_max;

	/* Maximum number of thपढ़ोs. */
	u32 thपढ़ो_count;

	/* Number of shader cores. */
	u32 shader_core_count;

	/* Size of the vertex cache. */
	u32 vertex_cache_size;

	/* Number of entries in the vertex output buffer. */
	u32 vertex_output_buffer_size;

	/* Number of pixel pipes. */
	u32 pixel_pipes;

	/* Number of inकाष्ठाions. */
	u32 inकाष्ठाion_count;

	/* Number of स्थिरants. */
	u32 num_स्थिरants;

	/* Buffer size */
	u32 buffer_size;

	/* Number of varyings */
	u8 varyings_count;
पूर्ण;

क्रमागत etnaviv_sec_mode अणु
	ETNA_SEC_NONE = 0,
	ETNA_SEC_KERNEL,
	ETNA_SEC_TZ
पूर्ण;

काष्ठा etnaviv_event अणु
	काष्ठा dma_fence *fence;
	काष्ठा etnaviv_gem_submit *submit;

	व्योम (*sync_poपूर्णांक)(काष्ठा etnaviv_gpu *gpu, काष्ठा etnaviv_event *event);
पूर्ण;

काष्ठा etnaviv_cmdbuf_suballoc;
काष्ठा regulator;
काष्ठा clk;

#घोषणा ETNA_NR_EVENTS 30

काष्ठा etnaviv_gpu अणु
	काष्ठा drm_device *drm;
	काष्ठा thermal_cooling_device *cooling;
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा etnaviv_chip_identity identity;
	क्रमागत etnaviv_sec_mode sec_mode;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा drm_gpu_scheduler sched;
	bool initialized;

	/* 'ring'-buffer: */
	काष्ठा etnaviv_cmdbuf buffer;
	पूर्णांक exec_state;

	/* event management: */
	DECLARE_BITMAP(event_biपंचांगap, ETNA_NR_EVENTS);
	काष्ठा etnaviv_event event[ETNA_NR_EVENTS];
	काष्ठा completion event_मुक्त;
	spinlock_t event_spinlock;

	u32 idle_mask;

	/* Fencing support */
	काष्ठा mutex fence_lock;
	काष्ठा idr fence_idr;
	u32 next_fence;
	u32 completed_fence;
	रुको_queue_head_t fence_event;
	u64 fence_context;
	spinlock_t fence_spinlock;

	/* worker क्रम handling 'sync' poपूर्णांकs: */
	काष्ठा work_काष्ठा sync_poपूर्णांक_work;
	पूर्णांक sync_poपूर्णांक_event;

	/* hang detection */
	u32 hangcheck_dma_addr;

	व्योम __iomem *mmio;
	पूर्णांक irq;

	काष्ठा etnaviv_iommu_context *mmu_context;
	अचिन्हित पूर्णांक flush_seq;

	/* Power Control: */
	काष्ठा clk *clk_bus;
	काष्ठा clk *clk_reg;
	काष्ठा clk *clk_core;
	काष्ठा clk *clk_shader;

	अचिन्हित पूर्णांक freq_scale;
	अचिन्हित दीर्घ base_rate_core;
	अचिन्हित दीर्घ base_rate_shader;
पूर्ण;

अटल अंतरभूत व्योम gpu_ग_लिखो(काष्ठा etnaviv_gpu *gpu, u32 reg, u32 data)
अणु
	ग_लिखोl(data, gpu->mmio + reg);
पूर्ण

अटल अंतरभूत u32 gpu_पढ़ो(काष्ठा etnaviv_gpu *gpu, u32 reg)
अणु
	वापस पढ़ोl(gpu->mmio + reg);
पूर्ण

पूर्णांक etnaviv_gpu_get_param(काष्ठा etnaviv_gpu *gpu, u32 param, u64 *value);

पूर्णांक etnaviv_gpu_init(काष्ठा etnaviv_gpu *gpu);
bool etnaviv_fill_identity_from_hwdb(काष्ठा etnaviv_gpu *gpu);

#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक etnaviv_gpu_debugfs(काष्ठा etnaviv_gpu *gpu, काष्ठा seq_file *m);
#पूर्ण_अगर

व्योम etnaviv_gpu_recover_hang(काष्ठा etnaviv_gpu *gpu);
व्योम etnaviv_gpu_retire(काष्ठा etnaviv_gpu *gpu);
पूर्णांक etnaviv_gpu_रुको_fence_पूर्णांकerruptible(काष्ठा etnaviv_gpu *gpu,
	u32 fence, काष्ठा drm_etnaviv_बारpec *समयout);
पूर्णांक etnaviv_gpu_रुको_obj_inactive(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_gem_object *etnaviv_obj,
	काष्ठा drm_etnaviv_बारpec *समयout);
काष्ठा dma_fence *etnaviv_gpu_submit(काष्ठा etnaviv_gem_submit *submit);
पूर्णांक etnaviv_gpu_pm_get_sync(काष्ठा etnaviv_gpu *gpu);
व्योम etnaviv_gpu_pm_put(काष्ठा etnaviv_gpu *gpu);
पूर्णांक etnaviv_gpu_रुको_idle(काष्ठा etnaviv_gpu *gpu, अचिन्हित पूर्णांक समयout_ms);
व्योम etnaviv_gpu_start_fe(काष्ठा etnaviv_gpu *gpu, u32 address, u16 prefetch);

बाह्य काष्ठा platक्रमm_driver etnaviv_gpu_driver;

#पूर्ण_अगर /* __ETNAVIV_GPU_H__ */
