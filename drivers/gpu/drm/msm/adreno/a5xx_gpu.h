<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित __A5XX_GPU_H__
#घोषणा __A5XX_GPU_H__

#समावेश "adreno_gpu.h"

/* Bringing over the hack from the previous tarमाला_लो */
#अघोषित ROP_COPY
#अघोषित ROP_XOR

#समावेश "a5xx.xml.h"

काष्ठा a5xx_gpu अणु
	काष्ठा adreno_gpu base;

	काष्ठा drm_gem_object *pm4_bo;
	uपूर्णांक64_t pm4_iova;

	काष्ठा drm_gem_object *pfp_bo;
	uपूर्णांक64_t pfp_iova;

	काष्ठा drm_gem_object *gpmu_bo;
	uपूर्णांक64_t gpmu_iova;
	uपूर्णांक32_t gpmu_dwords;

	uपूर्णांक32_t lm_leakage;

	काष्ठा msm_ringbuffer *cur_ring;
	काष्ठा msm_ringbuffer *next_ring;

	काष्ठा drm_gem_object *preempt_bo[MSM_GPU_MAX_RINGS];
	काष्ठा drm_gem_object *preempt_counters_bo[MSM_GPU_MAX_RINGS];
	काष्ठा a5xx_preempt_record *preempt[MSM_GPU_MAX_RINGS];
	uपूर्णांक64_t preempt_iova[MSM_GPU_MAX_RINGS];

	atomic_t preempt_state;
	काष्ठा समयr_list preempt_समयr;

	काष्ठा drm_gem_object *shaकरोw_bo;
	uपूर्णांक64_t shaकरोw_iova;
	uपूर्णांक32_t *shaकरोw;

	/* True अगर the microcode supports the WHERE_AM_I opcode */
	bool has_whereami;
पूर्ण;

#घोषणा to_a5xx_gpu(x) container_of(x, काष्ठा a5xx_gpu, base)

#अगर_घोषित CONFIG_DEBUG_FS
व्योम a5xx_debugfs_init(काष्ठा msm_gpu *gpu, काष्ठा drm_minor *minor);
#पूर्ण_अगर

/*
 * In order to करो lockless preemption we use a simple state machine to progress
 * through the process.
 *
 * PREEMPT_NONE - no preemption in progress.  Next state START.
 * PREEMPT_START - The trigger is evaulating अगर preemption is possible. Next
 * states: TRIGGERED, NONE
 * PREEMPT_ABORT - An पूर्णांकermediate state beक्रमe moving back to NONE. Next
 * state: NONE.
 * PREEMPT_TRIGGERED: A preemption has been executed on the hardware. Next
 * states: FAULTED, PENDING
 * PREEMPT_FAULTED: A preemption समयd out (never completed). This will trigger
 * recovery.  Next state: N/A
 * PREEMPT_PENDING: Preemption complete पूर्णांकerrupt fired - the callback is
 * checking the success of the operation. Next state: FAULTED, NONE.
 */

क्रमागत preempt_state अणु
	PREEMPT_NONE = 0,
	PREEMPT_START,
	PREEMPT_ABORT,
	PREEMPT_TRIGGERED,
	PREEMPT_FAULTED,
	PREEMPT_PENDING,
पूर्ण;

/*
 * काष्ठा a5xx_preempt_record is a shared buffer between the microcode and the
 * CPU to store the state क्रम preemption. The record itself is much larger
 * (64k) but most of that is used by the CP क्रम storage.
 *
 * There is a preemption record asचिन्हित per ringbuffer. When the CPU triggers a
 * preemption, it fills out the record with the useful inक्रमmation (wptr, ring
 * base, etc) and the microcode uses that inक्रमmation to set up the CP following
 * the preemption.  When a ring is चयनed out, the CP will save the ringbuffer
 * state back to the record. In this way, once the records are properly set up
 * the CPU can quickly चयन back and क्रमth between ringbuffers by only
 * updating a few रेजिस्टरs (often only the wptr).
 *
 * These are the CPU aware रेजिस्टरs in the record:
 * @magic: Must always be 0x27C4BAFC
 * @info: Type of the record - written 0 by the CPU, updated by the CP
 * @data: Data field from SET_RENDER_MODE or a checkpoपूर्णांक. Written and used by
 * the CP
 * @cntl: Value of RB_CNTL written by CPU, save/restored by CP
 * @rptr: Value of RB_RPTR written by CPU, save/restored by CP
 * @wptr: Value of RB_WPTR written by CPU, save/restored by CP
 * @rptr_addr: Value of RB_RPTR_ADDR written by CPU, save/restored by CP
 * @rbase: Value of RB_BASE written by CPU, save/restored by CP
 * @counter: GPU address of the storage area क्रम the perक्रमmance counters
 */
काष्ठा a5xx_preempt_record अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t info;
	uपूर्णांक32_t data;
	uपूर्णांक32_t cntl;
	uपूर्णांक32_t rptr;
	uपूर्णांक32_t wptr;
	uपूर्णांक64_t rptr_addr;
	uपूर्णांक64_t rbase;
	uपूर्णांक64_t counter;
पूर्ण;

/* Magic identअगरier क्रम the preemption record */
#घोषणा A5XX_PREEMPT_RECORD_MAGIC 0x27C4BAFCUL

/*
 * Even though the काष्ठाure above is only a few bytes, we need a full 64k to
 * store the entire preemption record from the CP
 */
#घोषणा A5XX_PREEMPT_RECORD_SIZE (64 * 1024)

/*
 * The preemption counter block is a storage area क्रम the value of the
 * preemption counters that are saved immediately beक्रमe context चयन. We
 * append it on to the end of the allocation क्रम the preemption record.
 */
#घोषणा A5XX_PREEMPT_COUNTER_SIZE (16 * 4)


पूर्णांक a5xx_घातer_init(काष्ठा msm_gpu *gpu);
व्योम a5xx_gpmu_ucode_init(काष्ठा msm_gpu *gpu);

अटल अंतरभूत पूर्णांक spin_usecs(काष्ठा msm_gpu *gpu, uपूर्णांक32_t usecs,
		uपूर्णांक32_t reg, uपूर्णांक32_t mask, uपूर्णांक32_t value)
अणु
	जबतक (usecs--) अणु
		udelay(1);
		अगर ((gpu_पढ़ो(gpu, reg) & mask) == value)
			वापस 0;
		cpu_relax();
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

#घोषणा shaकरोwptr(a5xx_gpu, ring) ((a5xx_gpu)->shaकरोw_iova + \
		((ring)->id * माप(uपूर्णांक32_t)))

bool a5xx_idle(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring);
व्योम a5xx_set_hwcg(काष्ठा msm_gpu *gpu, bool state);

व्योम a5xx_preempt_init(काष्ठा msm_gpu *gpu);
व्योम a5xx_preempt_hw_init(काष्ठा msm_gpu *gpu);
व्योम a5xx_preempt_trigger(काष्ठा msm_gpu *gpu);
व्योम a5xx_preempt_irq(काष्ठा msm_gpu *gpu);
व्योम a5xx_preempt_fini(काष्ठा msm_gpu *gpu);

व्योम a5xx_flush(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring, bool sync);

/* Return true अगर we are in a preempt state */
अटल अंतरभूत bool a5xx_in_preempt(काष्ठा a5xx_gpu *a5xx_gpu)
अणु
	पूर्णांक preempt_state = atomic_पढ़ो(&a5xx_gpu->preempt_state);

	वापस !(preempt_state == PREEMPT_NONE ||
			preempt_state == PREEMPT_ABORT);
पूर्ण

#पूर्ण_अगर /* __A5XX_GPU_H__ */
