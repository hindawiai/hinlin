<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 *
 * Copyright (c) 2014,2017, 2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __ADRENO_GPU_H__
#घोषणा __ADRENO_GPU_H__

#समावेश <linux/firmware.h>
#समावेश <linux/iopoll.h>

#समावेश "msm_gpu.h"

#समावेश "adreno_common.xml.h"
#समावेश "adreno_pm4.xml.h"

बाह्य bool snapshot_debugbus;
बाह्य bool allow_vram_carveout;

क्रमागत अणु
	ADRENO_FW_PM4 = 0,
	ADRENO_FW_SQE = 0, /* a6xx */
	ADRENO_FW_PFP = 1,
	ADRENO_FW_GMU = 1, /* a6xx */
	ADRENO_FW_GPMU = 2,
	ADRENO_FW_MAX,
पूर्ण;

क्रमागत adreno_quirks अणु
	ADRENO_QUIRK_TWO_PASS_USE_WFI = 1,
	ADRENO_QUIRK_FAULT_DETECT_MASK = 2,
	ADRENO_QUIRK_LMLOADKILL_DISABLE = 3,
पूर्ण;

काष्ठा adreno_rev अणु
	uपूर्णांक8_t  core;
	uपूर्णांक8_t  major;
	uपूर्णांक8_t  minor;
	uपूर्णांक8_t  patchid;
पूर्ण;

#घोषणा ADRENO_REV(core, major, minor, patchid) \
	((काष्ठा adreno_rev)अणु core, major, minor, patchid पूर्ण)

काष्ठा adreno_gpu_funcs अणु
	काष्ठा msm_gpu_funcs base;
	पूर्णांक (*get_बारtamp)(काष्ठा msm_gpu *gpu, uपूर्णांक64_t *value);
पूर्ण;

काष्ठा adreno_reglist अणु
	u32 offset;
	u32 value;
पूर्ण;

बाह्य स्थिर काष्ठा adreno_reglist a630_hwcg[], a640_hwcg[], a650_hwcg[];

काष्ठा adreno_info अणु
	काष्ठा adreno_rev rev;
	uपूर्णांक32_t revn;
	स्थिर अक्षर *name;
	स्थिर अक्षर *fw[ADRENO_FW_MAX];
	uपूर्णांक32_t gmem;
	क्रमागत adreno_quirks quirks;
	काष्ठा msm_gpu *(*init)(काष्ठा drm_device *dev);
	स्थिर अक्षर *zapfw;
	u32 inactive_period;
	स्थिर काष्ठा adreno_reglist *hwcg;
पूर्ण;

स्थिर काष्ठा adreno_info *adreno_info(काष्ठा adreno_rev rev);

काष्ठा adreno_gpu अणु
	काष्ठा msm_gpu base;
	काष्ठा adreno_rev rev;
	स्थिर काष्ठा adreno_info *info;
	uपूर्णांक32_t gmem;  /* actual gmem size */
	uपूर्णांक32_t revn;  /* numeric revision name */
	स्थिर काष्ठा adreno_gpu_funcs *funcs;

	/* पूर्णांकeresting रेजिस्टर offsets to dump: */
	स्थिर अचिन्हित पूर्णांक *रेजिस्टरs;

	/*
	 * Are we loading fw from legacy path?  Prior to addition
	 * of gpu firmware to linux-firmware, the fw files were
	 * placed in toplevel firmware directory, following qcom's
	 * android kernel.  But linux-firmware preferred they be
	 * placed in a 'qcom' subdirectory.
	 *
	 * For backwards compatibility, we try first to load from
	 * the new path, using request_firmware_direct() to aव्योम
	 * any potential समयout रुकोing क्रम usermode helper, then
	 * fall back to the old path (with direct load).  And
	 * finally fall back to request_firmware() with the new
	 * path to allow the usermode helper.
	 */
	क्रमागत अणु
		FW_LOCATION_UNKNOWN = 0,
		FW_LOCATION_NEW,       /* /lib/firmware/qcom/$fwfile */
		FW_LOCATION_LEGACY,    /* /lib/firmware/$fwfile */
		FW_LOCATION_HELPER,
	पूर्ण fwloc;

	/* firmware: */
	स्थिर काष्ठा firmware *fw[ADRENO_FW_MAX];

	/*
	 * Register offsets are dअगरferent between some GPUs.
	 * GPU specअगरic offsets will be exported by GPU specअगरic
	 * code (a3xx_gpu.c) and stored in this common location.
	 */
	स्थिर अचिन्हित पूर्णांक *reg_offsets;
पूर्ण;
#घोषणा to_adreno_gpu(x) container_of(x, काष्ठा adreno_gpu, base)

काष्ठा adreno_ocmem अणु
	काष्ठा ocmem *ocmem;
	अचिन्हित दीर्घ base;
	व्योम *hdl;
पूर्ण;

/* platक्रमm config data (ie. from DT, or pdata) */
काष्ठा adreno_platक्रमm_config अणु
	काष्ठा adreno_rev rev;
पूर्ण;

#घोषणा ADRENO_IDLE_TIMEOUT msecs_to_jअगरfies(1000)

#घोषणा spin_until(X) (अणु                                   \
	पूर्णांक __ret = -ETIMEDOUT;                            \
	अचिन्हित दीर्घ __t = jअगरfies + ADRENO_IDLE_TIMEOUT; \
	करो अणु                                               \
		अगर (X) अणु                                   \
			__ret = 0;                         \
			अवरोध;                             \
		पूर्ण                                          \
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, __t));               \
	__ret;                                             \
पूर्ण)

अटल अंतरभूत bool adreno_is_a2xx(काष्ठा adreno_gpu *gpu)
अणु
	वापस (gpu->revn < 300);
पूर्ण

अटल अंतरभूत bool adreno_is_a20x(काष्ठा adreno_gpu *gpu)
अणु
	वापस (gpu->revn < 210);
पूर्ण

अटल अंतरभूत bool adreno_is_a225(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 225;
पूर्ण

अटल अंतरभूत bool adreno_is_a305(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 305;
पूर्ण

अटल अंतरभूत bool adreno_is_a306(काष्ठा adreno_gpu *gpu)
अणु
	/* yes, 307, because a305c is 306 */
	वापस gpu->revn == 307;
पूर्ण

अटल अंतरभूत bool adreno_is_a320(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 320;
पूर्ण

अटल अंतरभूत bool adreno_is_a330(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 330;
पूर्ण

अटल अंतरभूत bool adreno_is_a330v2(काष्ठा adreno_gpu *gpu)
अणु
	वापस adreno_is_a330(gpu) && (gpu->rev.patchid > 0);
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a405(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 405;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a420(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 420;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a430(काष्ठा adreno_gpu *gpu)
अणु
       वापस gpu->revn == 430;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a508(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 508;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a509(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 509;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a510(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 510;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a512(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 512;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a530(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 530;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a540(काष्ठा adreno_gpu *gpu)
अणु
	वापस gpu->revn == 540;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a618(काष्ठा adreno_gpu *gpu)
अणु
       वापस gpu->revn == 618;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a630(काष्ठा adreno_gpu *gpu)
अणु
       वापस gpu->revn == 630;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a640(काष्ठा adreno_gpu *gpu)
अणु
       वापस gpu->revn == 640;
पूर्ण

अटल अंतरभूत पूर्णांक adreno_is_a650(काष्ठा adreno_gpu *gpu)
अणु
       वापस gpu->revn == 650;
पूर्ण

पूर्णांक adreno_get_param(काष्ठा msm_gpu *gpu, uपूर्णांक32_t param, uपूर्णांक64_t *value);
स्थिर काष्ठा firmware *adreno_request_fw(काष्ठा adreno_gpu *adreno_gpu,
		स्थिर अक्षर *fwname);
काष्ठा drm_gem_object *adreno_fw_create_bo(काष्ठा msm_gpu *gpu,
		स्थिर काष्ठा firmware *fw, u64 *iova);
पूर्णांक adreno_hw_init(काष्ठा msm_gpu *gpu);
व्योम adreno_recover(काष्ठा msm_gpu *gpu);
व्योम adreno_flush(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring, u32 reg);
bool adreno_idle(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring);
#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
व्योम adreno_show(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
		काष्ठा drm_prपूर्णांकer *p);
#पूर्ण_अगर
व्योम adreno_dump_info(काष्ठा msm_gpu *gpu);
व्योम adreno_dump(काष्ठा msm_gpu *gpu);
व्योम adreno_रुको_ring(काष्ठा msm_ringbuffer *ring, uपूर्णांक32_t ndwords);
काष्ठा msm_ringbuffer *adreno_active_ring(काष्ठा msm_gpu *gpu);

पूर्णांक adreno_gpu_ocmem_init(काष्ठा device *dev, काष्ठा adreno_gpu *adreno_gpu,
			  काष्ठा adreno_ocmem *ocmem);
व्योम adreno_gpu_ocmem_cleanup(काष्ठा adreno_ocmem *ocmem);

पूर्णांक adreno_gpu_init(काष्ठा drm_device *drm, काष्ठा platक्रमm_device *pdev,
		काष्ठा adreno_gpu *gpu, स्थिर काष्ठा adreno_gpu_funcs *funcs,
		पूर्णांक nr_rings);
व्योम adreno_gpu_cleanup(काष्ठा adreno_gpu *gpu);
पूर्णांक adreno_load_fw(काष्ठा adreno_gpu *adreno_gpu);

व्योम adreno_gpu_state_destroy(काष्ठा msm_gpu_state *state);

पूर्णांक adreno_gpu_state_get(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state);
पूर्णांक adreno_gpu_state_put(काष्ठा msm_gpu_state *state);

/*
 * Common helper function to initialize the शेष address space क्रम arm-smmu
 * attached tarमाला_लो
 */
काष्ठा msm_gem_address_space *
adreno_iommu_create_address_space(काष्ठा msm_gpu *gpu,
		काष्ठा platक्रमm_device *pdev);

व्योम adreno_set_llc_attributes(काष्ठा iommu_करोमुख्य *iommu);

/*
 * For a5xx and a6xx tarमाला_लो load the zap shader that is used to pull the GPU
 * out of secure mode
 */
पूर्णांक adreno_zap_shader_load(काष्ठा msm_gpu *gpu, u32 pasid);

/* ringbuffer helpers (the parts that are adreno specअगरic) */

अटल अंतरभूत व्योम
OUT_PKT0(काष्ठा msm_ringbuffer *ring, uपूर्णांक16_t regindx, uपूर्णांक16_t cnt)
अणु
	adreno_रुको_ring(ring, cnt+1);
	OUT_RING(ring, CP_TYPE0_PKT | ((cnt-1) << 16) | (regindx & 0x7FFF));
पूर्ण

/* no-op packet: */
अटल अंतरभूत व्योम
OUT_PKT2(काष्ठा msm_ringbuffer *ring)
अणु
	adreno_रुको_ring(ring, 1);
	OUT_RING(ring, CP_TYPE2_PKT);
पूर्ण

अटल अंतरभूत व्योम
OUT_PKT3(काष्ठा msm_ringbuffer *ring, uपूर्णांक8_t opcode, uपूर्णांक16_t cnt)
अणु
	adreno_रुको_ring(ring, cnt+1);
	OUT_RING(ring, CP_TYPE3_PKT | ((cnt-1) << 16) | ((opcode & 0xFF) << 8));
पूर्ण

अटल अंतरभूत u32 PM4_PARITY(u32 val)
अणु
	वापस (0x9669 >> (0xF & (val ^
		(val >> 4) ^ (val >> 8) ^ (val >> 12) ^
		(val >> 16) ^ ((val) >> 20) ^ (val >> 24) ^
		(val >> 28)))) & 1;
पूर्ण

/* Maximum number of values that can be executed क्रम one opcode */
#घोषणा TYPE4_MAX_PAYLOAD 127

#घोषणा PKT4(_reg, _cnt) \
	(CP_TYPE4_PKT | ((_cnt) << 0) | (PM4_PARITY((_cnt)) << 7) | \
	 (((_reg) & 0x3FFFF) << 8) | (PM4_PARITY((_reg)) << 27))

अटल अंतरभूत व्योम
OUT_PKT4(काष्ठा msm_ringbuffer *ring, uपूर्णांक16_t regindx, uपूर्णांक16_t cnt)
अणु
	adreno_रुको_ring(ring, cnt + 1);
	OUT_RING(ring, PKT4(regindx, cnt));
पूर्ण

अटल अंतरभूत व्योम
OUT_PKT7(काष्ठा msm_ringbuffer *ring, uपूर्णांक8_t opcode, uपूर्णांक16_t cnt)
अणु
	adreno_रुको_ring(ring, cnt + 1);
	OUT_RING(ring, CP_TYPE7_PKT | (cnt << 0) | (PM4_PARITY(cnt) << 15) |
		((opcode & 0x7F) << 16) | (PM4_PARITY(opcode) << 23));
पूर्ण

काष्ठा msm_gpu *a2xx_gpu_init(काष्ठा drm_device *dev);
काष्ठा msm_gpu *a3xx_gpu_init(काष्ठा drm_device *dev);
काष्ठा msm_gpu *a4xx_gpu_init(काष्ठा drm_device *dev);
काष्ठा msm_gpu *a5xx_gpu_init(काष्ठा drm_device *dev);
काष्ठा msm_gpu *a6xx_gpu_init(काष्ठा drm_device *dev);

अटल अंतरभूत uपूर्णांक32_t get_wptr(काष्ठा msm_ringbuffer *ring)
अणु
	वापस (ring->cur - ring->start) % (MSM_GPU_RINGBUFFER_SZ >> 2);
पूर्ण

/*
 * Given a रेजिस्टर and a count, वापस a value to program पूर्णांकo
 * REG_CP_PROTECT_REG(n) - this will block both पढ़ोs and ग_लिखोs क्रम _len
 * रेजिस्टरs starting at _reg.
 *
 * The रेजिस्टर base needs to be a multiple of the length. If it is not, the
 * hardware will quietly mask off the bits क्रम you and shअगरt the size. For
 * example, अगर you पूर्णांकend the protection to start at 0x07 क्रम a length of 4
 * (0x07-0x0A) the hardware will actually protect (0x04-0x07) which might
 * expose रेजिस्टरs you पूर्णांकended to protect!
 */
#घोषणा ADRENO_PROTECT_RW(_reg, _len) \
	((1 << 30) | (1 << 29) | \
	((ilog2((_len)) & 0x1F) << 24) | (((_reg) << 2) & 0xFFFFF))

/*
 * Same as above, but allow पढ़ोs over the range. For areas of mixed use (such
 * as perक्रमmance counters) this allows us to protect a much larger range with a
 * single रेजिस्टर
 */
#घोषणा ADRENO_PROTECT_RDONLY(_reg, _len) \
	((1 << 29) \
	((ilog2((_len)) & 0x1F) << 24) | (((_reg) << 2) & 0xFFFFF))


#घोषणा gpu_poll_समयout(gpu, addr, val, cond, पूर्णांकerval, समयout) \
	पढ़ोl_poll_समयout((gpu)->mmio + ((addr) << 2), val, cond, \
		पूर्णांकerval, समयout)

#पूर्ण_अगर /* __ADRENO_GPU_H__ */
