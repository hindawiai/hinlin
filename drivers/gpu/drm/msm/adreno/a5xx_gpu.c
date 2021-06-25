<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016-2017 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/slab.h>
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"
#समावेश "a5xx_gpu.h"

बाह्य bool hang_debug;
अटल व्योम a5xx_dump(काष्ठा msm_gpu *gpu);

#घोषणा GPU_PAS_ID 13

व्योम a5xx_flush(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring,
		bool sync)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	uपूर्णांक32_t wptr;
	अचिन्हित दीर्घ flags;

	/*
	 * Most flush operations need to issue a WHERE_AM_I opcode to sync up
	 * the rptr shaकरोw
	 */
	अगर (a5xx_gpu->has_whereami && sync) अणु
		OUT_PKT7(ring, CP_WHERE_AM_I, 2);
		OUT_RING(ring, lower_32_bits(shaकरोwptr(a5xx_gpu, ring)));
		OUT_RING(ring, upper_32_bits(shaकरोwptr(a5xx_gpu, ring)));
	पूर्ण

	spin_lock_irqsave(&ring->preempt_lock, flags);

	/* Copy the shaकरोw to the actual रेजिस्टर */
	ring->cur = ring->next;

	/* Make sure to wrap wptr अगर we need to */
	wptr = get_wptr(ring);

	spin_unlock_irqrestore(&ring->preempt_lock, flags);

	/* Make sure everything is posted beक्रमe making a decision */
	mb();

	/* Update HW अगर this is the current ring and we are not in preempt */
	अगर (a5xx_gpu->cur_ring == ring && !a5xx_in_preempt(a5xx_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_CP_RB_WPTR, wptr);
पूर्ण

अटल व्योम a5xx_submit_in_rb(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
अणु
	काष्ठा msm_drm_निजी *priv = gpu->dev->dev_निजी;
	काष्ठा msm_ringbuffer *ring = submit->ring;
	काष्ठा msm_gem_object *obj;
	uपूर्णांक32_t *ptr, dwords;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < submit->nr_cmds; i++) अणु
		चयन (submit->cmd[i].type) अणु
		हाल MSM_SUBMIT_CMD_IB_TARGET_BUF:
			अवरोध;
		हाल MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			अगर (priv->lastctx == submit->queue->ctx)
				अवरोध;
			fallthrough;
		हाल MSM_SUBMIT_CMD_BUF:
			/* copy commands पूर्णांकo RB: */
			obj = submit->bos[submit->cmd[i].idx].obj;
			dwords = submit->cmd[i].size;

			ptr = msm_gem_get_vaddr(&obj->base);

			/* _get_vaddr() shouldn't fail at this poपूर्णांक,
			 * since we've alपढ़ोy mapped it once in
			 * submit_reloc()
			 */
			अगर (WARN_ON(!ptr))
				वापस;

			क्रम (i = 0; i < dwords; i++) अणु
				/* normally the OUT_PKTn() would रुको
				 * क्रम space क्रम the packet.  But since
				 * we just OUT_RING() the whole thing,
				 * need to call adreno_रुको_ring()
				 * ourself:
				 */
				adreno_रुको_ring(ring, 1);
				OUT_RING(ring, ptr[i]);
			पूर्ण

			msm_gem_put_vaddr(&obj->base);

			अवरोध;
		पूर्ण
	पूर्ण

	a5xx_flush(gpu, ring, true);
	a5xx_preempt_trigger(gpu);

	/* we might not necessarily have a cmd from userspace to
	 * trigger an event to know that submit has completed, so
	 * करो this manually:
	 */
	a5xx_idle(gpu, ring);
	ring->memptrs->fence = submit->seqno;
	msm_gpu_retire(gpu);
पूर्ण

अटल व्योम a5xx_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	काष्ठा msm_drm_निजी *priv = gpu->dev->dev_निजी;
	काष्ठा msm_ringbuffer *ring = submit->ring;
	अचिन्हित पूर्णांक i, ibs = 0;

	अगर (IS_ENABLED(CONFIG_DRM_MSM_GPU_SUDO) && submit->in_rb) अणु
		priv->lastctx = शून्य;
		a5xx_submit_in_rb(gpu, submit);
		वापस;
	पूर्ण

	OUT_PKT7(ring, CP_PREEMPT_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x02);

	/* Turn off रक्षित mode to ग_लिखो to special रेजिस्टरs */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 0);

	/* Set the save preemption record क्रम the ring/command */
	OUT_PKT4(ring, REG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDR_LO, 2);
	OUT_RING(ring, lower_32_bits(a5xx_gpu->preempt_iova[submit->ring->id]));
	OUT_RING(ring, upper_32_bits(a5xx_gpu->preempt_iova[submit->ring->id]));

	/* Turn back on रक्षित mode */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	/* Enable local preemption क्रम finegrain preemption */
	OUT_PKT7(ring, CP_PREEMPT_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x02);

	/* Allow CP_CONTEXT_SWITCH_YIELD packets in the IB2 */
	OUT_PKT7(ring, CP_YIELD_ENABLE, 1);
	OUT_RING(ring, 0x02);

	/* Submit the commands */
	क्रम (i = 0; i < submit->nr_cmds; i++) अणु
		चयन (submit->cmd[i].type) अणु
		हाल MSM_SUBMIT_CMD_IB_TARGET_BUF:
			अवरोध;
		हाल MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			अगर (priv->lastctx == submit->queue->ctx)
				अवरोध;
			fallthrough;
		हाल MSM_SUBMIT_CMD_BUF:
			OUT_PKT7(ring, CP_INसूचीECT_BUFFER_PFE, 3);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, upper_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			ibs++;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Write the render mode to शून्य (0) to indicate to the CP that the IBs
	 * are करोne rendering - otherwise a lucky preemption would start
	 * replaying from the last checkpoपूर्णांक
	 */
	OUT_PKT7(ring, CP_SET_RENDER_MODE, 5);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);
	OUT_RING(ring, 0);

	/* Turn off IB level preemptions */
	OUT_PKT7(ring, CP_YIELD_ENABLE, 1);
	OUT_RING(ring, 0x01);

	/* Write the fence to the scratch रेजिस्टर */
	OUT_PKT4(ring, REG_A5XX_CP_SCRATCH_REG(2), 1);
	OUT_RING(ring, submit->seqno);

	/*
	 * Execute a CACHE_FLUSH_TS event. This will ensure that the
	 * बारtamp is written to the memory and then triggers the पूर्णांकerrupt
	 */
	OUT_PKT7(ring, CP_EVENT_WRITE, 4);
	OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(CACHE_FLUSH_TS) |
		CP_EVENT_WRITE_0_IRQ);
	OUT_RING(ring, lower_32_bits(rbmemptr(ring, fence)));
	OUT_RING(ring, upper_32_bits(rbmemptr(ring, fence)));
	OUT_RING(ring, submit->seqno);

	/* Yield the न्यूनमान on command completion */
	OUT_PKT7(ring, CP_CONTEXT_SWITCH_YIELD, 4);
	/*
	 * If dword[2:1] are non zero, they specअगरy an address क्रम the CP to
	 * ग_लिखो the value of dword[3] to on preemption complete. Write 0 to
	 * skip the ग_लिखो
	 */
	OUT_RING(ring, 0x00);
	OUT_RING(ring, 0x00);
	/* Data value - not used अगर the address above is 0 */
	OUT_RING(ring, 0x01);
	/* Set bit 0 to trigger an पूर्णांकerrupt on preempt complete */
	OUT_RING(ring, 0x01);

	/* A WHERE_AM_I packet is not needed after a YIELD */
	a5xx_flush(gpu, ring, false);

	/* Check to see अगर we need to start preemption */
	a5xx_preempt_trigger(gpu);
पूर्ण

अटल स्थिर काष्ठा adreno_five_hwcg_regs अणु
	u32 offset;
	u32 value;
पूर्ण a5xx_hwcg[] = अणु
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP0, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP1, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP2, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP3, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP0, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP1, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP2, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP3, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP0, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP1, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP2, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP3, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP1, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP2, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP3, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP2, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP3, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP2, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP3, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP0, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP1, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP2, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP3, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP1, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP2, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP3, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP1, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP2, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP3, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP0, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP1, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP2, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP3, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP1, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP2, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP3, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP1, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP2, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP3, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP0, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP1, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP2, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP3, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL4_UCHE, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_UCHE, 0x00444444पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB2, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB3, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB0, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB1, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB2, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB3, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU0, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU1, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU2, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU3, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RAC, 0x05522222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RAC, 0x00505555पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU0, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU1, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU2, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU3, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RAC, 0x07444044पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_0, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_1, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_2, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_3, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RAC, 0x00010011पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_GPC, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण
पूर्ण, a50x_hwcg[] = अणु
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP0, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP0, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP0, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP0, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP0, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP0, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL4_UCHE, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_UCHE, 0x00FFFFF4पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB0, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU0, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RAC, 0x05522222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RAC, 0x00505555पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU0, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RAC, 0x07444044पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_0, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RAC, 0x00010011पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_GPC, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण,
पूर्ण, a512_hwcg[] = अणु
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP0, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_SP1, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP0, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_SP1, 0x02222220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP0, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_SP1, 0x0000F3CFपूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_SP1, 0x00000080पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TP1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_TP1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP0, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_TP1, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TP1, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST2_TP1, 0x77777777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP0, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST3_TP1, 0x00007777पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TP1, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY2_TP1, 0x11111111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP0, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY3_TP1, 0x00001111पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL3_UCHE, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL4_UCHE, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_UCHE, 0x00444444पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RB1, 0x22222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB0, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RB1, 0x00222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU0, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_CCU1, 0x00022220पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_RAC, 0x05522222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL2_RAC, 0x00505555पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU0, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RB_CCU1, 0x04040404पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_RAC, 0x07444044पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_0, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RB_CCU_L1_1, 0x00000002पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_RAC, 0x00010011पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_GPC, 0x02222222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A5XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण,
पूर्ण;

व्योम a5xx_set_hwcg(काष्ठा msm_gpu *gpu, bool state)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	स्थिर काष्ठा adreno_five_hwcg_regs *regs;
	अचिन्हित पूर्णांक i, sz;

	अगर (adreno_is_a508(adreno_gpu)) अणु
		regs = a50x_hwcg;
		sz = ARRAY_SIZE(a50x_hwcg);
	पूर्ण अन्यथा अगर (adreno_is_a509(adreno_gpu) || adreno_is_a512(adreno_gpu)) अणु
		regs = a512_hwcg;
		sz = ARRAY_SIZE(a512_hwcg);
	पूर्ण अन्यथा अणु
		regs = a5xx_hwcg;
		sz = ARRAY_SIZE(a5xx_hwcg);
	पूर्ण

	क्रम (i = 0; i < sz; i++)
		gpu_ग_लिखो(gpu, regs[i].offset,
			  state ? regs[i].value : 0);

	अगर (adreno_is_a540(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_CLOCK_DELAY_GPMU, state ? 0x00000770 : 0);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_CLOCK_HYST_GPMU, state ? 0x00000004 : 0);
	पूर्ण

	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_CLOCK_CNTL, state ? 0xAAA8AA00 : 0);
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_ISDB_CNT, state ? 0x182 : 0x180);
पूर्ण

अटल पूर्णांक a5xx_me_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT7(ring, CP_ME_INIT, 8);

	OUT_RING(ring, 0x0000002F);

	/* Enable multiple hardware contexts */
	OUT_RING(ring, 0x00000003);

	/* Enable error detection */
	OUT_RING(ring, 0x20000000);

	/* Don't enable header dump */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	/* Specअगरy workarounds क्रम various microcode issues */
	अगर (adreno_is_a530(adreno_gpu)) अणु
		/* Workaround क्रम token end syncs
		 * Force a WFI after every direct-render 3D mode draw and every
		 * 2D mode 3 draw
		 */
		OUT_RING(ring, 0x0000000B);
	पूर्ण अन्यथा अगर (adreno_is_a510(adreno_gpu)) अणु
		/* Workaround क्रम token and syncs */
		OUT_RING(ring, 0x00000001);
	पूर्ण अन्यथा अणु
		/* No workarounds enabled */
		OUT_RING(ring, 0x00000000);
	पूर्ण

	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	a5xx_flush(gpu, ring, true);
	वापस a5xx_idle(gpu, ring) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक a5xx_preempt_start(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	अगर (gpu->nr_rings == 1)
		वापस 0;

	/* Turn off रक्षित mode to ग_लिखो to special रेजिस्टरs */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 0);

	/* Set the save preemption record क्रम the ring/command */
	OUT_PKT4(ring, REG_A5XX_CP_CONTEXT_SWITCH_SAVE_ADDR_LO, 2);
	OUT_RING(ring, lower_32_bits(a5xx_gpu->preempt_iova[ring->id]));
	OUT_RING(ring, upper_32_bits(a5xx_gpu->preempt_iova[ring->id]));

	/* Turn back on रक्षित mode */
	OUT_PKT7(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	OUT_PKT7(ring, CP_PREEMPT_ENABLE_GLOBAL, 1);
	OUT_RING(ring, 0x00);

	OUT_PKT7(ring, CP_PREEMPT_ENABLE_LOCAL, 1);
	OUT_RING(ring, 0x01);

	OUT_PKT7(ring, CP_YIELD_ENABLE, 1);
	OUT_RING(ring, 0x01);

	/* Yield the न्यूनमान on command completion */
	OUT_PKT7(ring, CP_CONTEXT_SWITCH_YIELD, 4);
	OUT_RING(ring, 0x00);
	OUT_RING(ring, 0x00);
	OUT_RING(ring, 0x01);
	OUT_RING(ring, 0x01);

	/* The WHERE_AMI_I packet is not needed after a YIELD is issued */
	a5xx_flush(gpu, ring, false);

	वापस a5xx_idle(gpu, ring) ? 0 : -EINVAL;
पूर्ण

अटल व्योम a5xx_ucode_check_version(काष्ठा a5xx_gpu *a5xx_gpu,
		काष्ठा drm_gem_object *obj)
अणु
	u32 *buf = msm_gem_get_vaddr(obj);

	अगर (IS_ERR(buf))
		वापस;

	/*
	 * If the lowest nibble is 0xa that is an indication that this microcode
	 * has been patched. The actual version is in dword [3] but we only care
	 * about the patchlevel which is the lowest nibble of dword [3]
	 */
	अगर (((buf[0] & 0xf) == 0xa) && (buf[2] & 0xf) >= 1)
		a5xx_gpu->has_whereami = true;

	msm_gem_put_vaddr(obj);
पूर्ण

अटल पूर्णांक a5xx_ucode_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	पूर्णांक ret;

	अगर (!a5xx_gpu->pm4_bo) अणु
		a5xx_gpu->pm4_bo = adreno_fw_create_bo(gpu,
			adreno_gpu->fw[ADRENO_FW_PM4], &a5xx_gpu->pm4_iova);


		अगर (IS_ERR(a5xx_gpu->pm4_bo)) अणु
			ret = PTR_ERR(a5xx_gpu->pm4_bo);
			a5xx_gpu->pm4_bo = शून्य;
			DRM_DEV_ERROR(gpu->dev->dev, "could not allocate PM4: %d\n",
				ret);
			वापस ret;
		पूर्ण

		msm_gem_object_set_name(a5xx_gpu->pm4_bo, "pm4fw");
	पूर्ण

	अगर (!a5xx_gpu->pfp_bo) अणु
		a5xx_gpu->pfp_bo = adreno_fw_create_bo(gpu,
			adreno_gpu->fw[ADRENO_FW_PFP], &a5xx_gpu->pfp_iova);

		अगर (IS_ERR(a5xx_gpu->pfp_bo)) अणु
			ret = PTR_ERR(a5xx_gpu->pfp_bo);
			a5xx_gpu->pfp_bo = शून्य;
			DRM_DEV_ERROR(gpu->dev->dev, "could not allocate PFP: %d\n",
				ret);
			वापस ret;
		पूर्ण

		msm_gem_object_set_name(a5xx_gpu->pfp_bo, "pfpfw");
		a5xx_ucode_check_version(a5xx_gpu, a5xx_gpu->pfp_bo);
	पूर्ण

	gpu_ग_लिखो64(gpu, REG_A5XX_CP_ME_INSTR_BASE_LO,
		REG_A5XX_CP_ME_INSTR_BASE_HI, a5xx_gpu->pm4_iova);

	gpu_ग_लिखो64(gpu, REG_A5XX_CP_PFP_INSTR_BASE_LO,
		REG_A5XX_CP_PFP_INSTR_BASE_HI, a5xx_gpu->pfp_iova);

	वापस 0;
पूर्ण

#घोषणा SCM_GPU_ZAP_SHADER_RESUME 0

अटल पूर्णांक a5xx_zap_shader_resume(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक ret;

	ret = qcom_scm_set_remote_state(SCM_GPU_ZAP_SHADER_RESUME, GPU_PAS_ID);
	अगर (ret)
		DRM_ERROR("%s: zap-shader resume failed: %d\n",
			gpu->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक a5xx_zap_shader_init(काष्ठा msm_gpu *gpu)
अणु
	अटल bool loaded;
	पूर्णांक ret;

	/*
	 * If the zap shader is alपढ़ोy loaded पूर्णांकo memory we just need to kick
	 * the remote processor to reinitialize it
	 */
	अगर (loaded)
		वापस a5xx_zap_shader_resume(gpu);

	ret = adreno_zap_shader_load(gpu, GPU_PAS_ID);

	loaded = !ret;
	वापस ret;
पूर्ण

#घोषणा A5XX_INT_MASK (A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR | \
	  A5XX_RBBM_INT_0_MASK_RBBM_TRANSFER_TIMEOUT | \
	  A5XX_RBBM_INT_0_MASK_RBBM_ME_MS_TIMEOUT | \
	  A5XX_RBBM_INT_0_MASK_RBBM_PFP_MS_TIMEOUT | \
	  A5XX_RBBM_INT_0_MASK_RBBM_ETS_MS_TIMEOUT | \
	  A5XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNC_OVERFLOW | \
	  A5XX_RBBM_INT_0_MASK_CP_HW_ERROR | \
	  A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT | \
	  A5XX_RBBM_INT_0_MASK_CP_SW | \
	  A5XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS | \
	  A5XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS | \
	  A5XX_RBBM_INT_0_MASK_GPMU_VOLTAGE_DROOP)

अटल पूर्णांक a5xx_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	u32 regbit;
	पूर्णांक ret;

	gpu_ग_लिखो(gpu, REG_A5XX_VBIF_ROUND_ROBIN_QOS_ARB, 0x00000003);

	अगर (adreno_is_a509(adreno_gpu) || adreno_is_a512(adreno_gpu) ||
	    adreno_is_a540(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000009);

	/* Make all blocks contribute to the GPU BUSY perf counter */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_PERFCTR_GPU_BUSY_MASKED, 0xFFFFFFFF);

	/* Enable RBBM error reporting bits */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_AHB_CNTL0, 0x00000001);

	अगर (adreno_gpu->info->quirks & ADRENO_QUIRK_FAULT_DETECT_MASK) अणु
		/*
		 * Mask out the activity संकेतs from RB1-3 to aव्योम false
		 * positives
		 */

		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL11,
			0xF0000000);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL12,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL13,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL14,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL15,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL16,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL17,
			0xFFFFFFFF);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_MASK_CNTL18,
			0xFFFFFFFF);
	पूर्ण

	/* Enable fault detection */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INTERFACE_HANG_INT_CNTL,
		(1 << 30) | 0xFFFF);

	/* Turn on perक्रमmance counters */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_PERFCTR_CNTL, 0x01);

	/* Select CP0 to always count cycles */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PERFCTR_CP_SEL_0, PERF_CP_ALWAYS_COUNT);

	/* Select RBBM0 to countable 6 to get the busy status क्रम devfreq */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_PERFCTR_RBBM_SEL_0, 6);

	/* Increase VFD cache access so LRZ and other data माला_लो evicted less */
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_CACHE_WAYS, 0x02);

	/* Disable L2 bypass in the UCHE */
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_TRAP_BASE_LO, 0xFFFF0000);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_TRAP_BASE_HI, 0x0001FFFF);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_WRITE_THRU_BASE_LO, 0xFFFF0000);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_WRITE_THRU_BASE_HI, 0x0001FFFF);

	/* Set the GMEM VA range (0 to gpu->gmem) */
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_GMEM_RANGE_MIN_LO, 0x00100000);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_GMEM_RANGE_MIN_HI, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_GMEM_RANGE_MAX_LO,
		0x00100000 + adreno_gpu->gmem - 1);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_GMEM_RANGE_MAX_HI, 0x00000000);

	अगर (adreno_is_a508(adreno_gpu) || adreno_is_a510(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A5XX_CP_MEQ_THRESHOLDS, 0x20);
		अगर (adreno_is_a508(adreno_gpu))
			gpu_ग_लिखो(gpu, REG_A5XX_CP_MERCIU_SIZE, 0x400);
		अन्यथा
			gpu_ग_लिखो(gpu, REG_A5XX_CP_MERCIU_SIZE, 0x20);
		gpu_ग_लिखो(gpu, REG_A5XX_CP_ROQ_THRESHOLDS_2, 0x40000030);
		gpu_ग_लिखो(gpu, REG_A5XX_CP_ROQ_THRESHOLDS_1, 0x20100D0A);
	पूर्ण अन्यथा अणु
		gpu_ग_लिखो(gpu, REG_A5XX_CP_MEQ_THRESHOLDS, 0x40);
		अगर (adreno_is_a530(adreno_gpu))
			gpu_ग_लिखो(gpu, REG_A5XX_CP_MERCIU_SIZE, 0x40);
		अन्यथा
			gpu_ग_लिखो(gpu, REG_A5XX_CP_MERCIU_SIZE, 0x400);
		gpu_ग_लिखो(gpu, REG_A5XX_CP_ROQ_THRESHOLDS_2, 0x80000060);
		gpu_ग_लिखो(gpu, REG_A5XX_CP_ROQ_THRESHOLDS_1, 0x40201B16);
	पूर्ण

	अगर (adreno_is_a508(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_PC_DBG_ECO_CNTL,
			  (0x100 << 11 | 0x100 << 22));
	अन्यथा अगर (adreno_is_a509(adreno_gpu) || adreno_is_a510(adreno_gpu) ||
		 adreno_is_a512(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_PC_DBG_ECO_CNTL,
			  (0x200 << 11 | 0x200 << 22));
	अन्यथा
		gpu_ग_लिखो(gpu, REG_A5XX_PC_DBG_ECO_CNTL,
			  (0x400 << 11 | 0x300 << 22));

	अगर (adreno_gpu->info->quirks & ADRENO_QUIRK_TWO_PASS_USE_WFI)
		gpu_rmw(gpu, REG_A5XX_PC_DBG_ECO_CNTL, 0, (1 << 8));

	/*
	 * Disable the RB sampler datapath DP2 घड़ी gating optimization
	 * क्रम 1-SP GPUs, as it is enabled by शेष.
	 */
	अगर (adreno_is_a508(adreno_gpu) || adreno_is_a509(adreno_gpu) ||
	    adreno_is_a512(adreno_gpu))
		gpu_rmw(gpu, REG_A5XX_RB_DBG_ECO_CNTL, 0, (1 << 9));

	/* Disable UCHE global filter as SP can invalidate/flush independently */
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_MODE_CNTL, BIT(29));

	/* Enable USE_RETENTION_FLOPS */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_CHICKEN_DBG, 0x02000000);

	/* Enable ME/PFP split notअगरication */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_AHB_CNTL1, 0xA6FFFFFF);

	/*
	 *  In A5x, CCU can send context_करोne event of a particular context to
	 *  UCHE which ultimately reaches CP even when there is valid
	 *  transaction of that context inside CCU. This can let CP to program
	 *  config रेजिस्टरs, which will make the "valid transaction" inside
	 *  CCU to be पूर्णांकerpreted dअगरferently. This can cause gpu fault. This
	 *  bug is fixed in latest A510 revision. To enable this bug fix -
	 *  bit[11] of RB_DBG_ECO_CNTL need to be set to 0, शेष is 1
	 *  (disable). For older A510 version this bit is unused.
	 */
	अगर (adreno_is_a510(adreno_gpu))
		gpu_rmw(gpu, REG_A5XX_RB_DBG_ECO_CNTL, (1 << 11), 0);

	/* Enable HWCG */
	a5xx_set_hwcg(gpu, true);

	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_AHB_CNTL2, 0x0000003F);

	/* Set the highest bank bit */
	अगर (adreno_is_a540(adreno_gpu))
		regbit = 2;
	अन्यथा
		regbit = 1;

	gpu_ग_लिखो(gpu, REG_A5XX_TPL1_MODE_CNTL, regbit << 7);
	gpu_ग_लिखो(gpu, REG_A5XX_RB_MODE_CNTL, regbit << 1);

	अगर (adreno_is_a509(adreno_gpu) || adreno_is_a512(adreno_gpu) ||
	    adreno_is_a540(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_UCHE_DBG_ECO_CNTL_2, regbit);

	/* Disable All flat shading optimization (ALLFLATOPTDIS) */
	gpu_rmw(gpu, REG_A5XX_VPC_DBG_ECO_CNTL, 0, (1 << 10));

	/* Protect रेजिस्टरs from the CP */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT_CNTL, 0x00000007);

	/* RBBM */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(0), ADRENO_PROTECT_RW(0x04, 4));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(1), ADRENO_PROTECT_RW(0x08, 8));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(2), ADRENO_PROTECT_RW(0x10, 16));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(3), ADRENO_PROTECT_RW(0x20, 32));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(4), ADRENO_PROTECT_RW(0x40, 64));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(5), ADRENO_PROTECT_RW(0x80, 64));

	/* Content protect */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(6),
		ADRENO_PROTECT_RW(REG_A5XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO,
			16));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(7),
		ADRENO_PROTECT_RW(REG_A5XX_RBBM_SECVID_TRUST_CNTL, 2));

	/* CP */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(8), ADRENO_PROTECT_RW(0x800, 64));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(9), ADRENO_PROTECT_RW(0x840, 8));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(10), ADRENO_PROTECT_RW(0x880, 32));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(11), ADRENO_PROTECT_RW(0xAA0, 1));

	/* RB */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(12), ADRENO_PROTECT_RW(0xCC0, 1));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(13), ADRENO_PROTECT_RW(0xCF0, 2));

	/* VPC */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(14), ADRENO_PROTECT_RW(0xE68, 8));
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(15), ADRENO_PROTECT_RW(0xE70, 16));

	/* UCHE */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(16), ADRENO_PROTECT_RW(0xE80, 16));

	अगर (adreno_is_a508(adreno_gpu) || adreno_is_a509(adreno_gpu) ||
	    adreno_is_a510(adreno_gpu) || adreno_is_a512(adreno_gpu) ||
	    adreno_is_a530(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A5XX_CP_PROTECT(17),
			ADRENO_PROTECT_RW(0x10000, 0x8000));

	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SECVID_TSB_CNTL, 0);
	/*
	 * Disable the trusted memory range - we करोn't actually supported secure
	 * memory rendering at this poपूर्णांक in समय and we करोn't want to block off
	 * part of the भव memory space.
	 */
	gpu_ग_लिखो64(gpu, REG_A5XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO,
		REG_A5XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SECVID_TSB_TRUSTED_SIZE, 0x00000000);

	/* Put the GPU पूर्णांकo 64 bit by शेष */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_VSC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_GRAS_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_RB_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_PC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_HLSQ_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_VFD_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_VPC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_UCHE_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_SP_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_TPL1_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL, 0x1);

	/*
	 * VPC corner हाल with local memory load समाप्त leads to corrupt
	 * पूर्णांकernal state. Normal Disable करोes not work क्रम all a5x chips.
	 * So करो the following setting to disable it.
	 */
	अगर (adreno_gpu->info->quirks & ADRENO_QUIRK_LMLOADKILL_DISABLE) अणु
		gpu_rmw(gpu, REG_A5XX_VPC_DBG_ECO_CNTL, 0, BIT(23));
		gpu_rmw(gpu, REG_A5XX_HLSQ_DBG_ECO_CNTL, BIT(18), 0);
	पूर्ण

	ret = adreno_hw_init(gpu);
	अगर (ret)
		वापस ret;

	अगर (!(adreno_is_a508(adreno_gpu) || adreno_is_a509(adreno_gpu) ||
	      adreno_is_a510(adreno_gpu) || adreno_is_a512(adreno_gpu)))
		a5xx_gpmu_ucode_init(gpu);

	ret = a5xx_ucode_init(gpu);
	अगर (ret)
		वापस ret;

	/* Set the ringbuffer address */
	gpu_ग_लिखो64(gpu, REG_A5XX_CP_RB_BASE, REG_A5XX_CP_RB_BASE_HI,
		gpu->rb[0]->iova);

	/*
	 * If the microcode supports the WHERE_AM_I opcode then we can use that
	 * in lieu of the RPTR shaकरोw and enable preemption. Otherwise, we
	 * can't safely use the RPTR shaकरोw or preemption. In either हाल, the
	 * RPTR shaकरोw should be disabled in hardware.
	 */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_RB_CNTL,
		MSM_GPU_RB_CNTL_DEFAULT | AXXX_CP_RB_CNTL_NO_UPDATE);

	/* Create a privileged buffer क्रम the RPTR shaकरोw */
	अगर (a5xx_gpu->has_whereami) अणु
		अगर (!a5xx_gpu->shaकरोw_bo) अणु
			a5xx_gpu->shaकरोw = msm_gem_kernel_new(gpu->dev,
				माप(u32) * gpu->nr_rings,
				MSM_BO_UNCACHED | MSM_BO_MAP_PRIV,
				gpu->aspace, &a5xx_gpu->shaकरोw_bo,
				&a5xx_gpu->shaकरोw_iova);

			अगर (IS_ERR(a5xx_gpu->shaकरोw))
				वापस PTR_ERR(a5xx_gpu->shaकरोw);
		पूर्ण

		gpu_ग_लिखो64(gpu, REG_A5XX_CP_RB_RPTR_ADDR,
			REG_A5XX_CP_RB_RPTR_ADDR_HI, shaकरोwptr(a5xx_gpu, gpu->rb[0]));
	पूर्ण अन्यथा अगर (gpu->nr_rings > 1) अणु
		/* Disable preemption अगर WHERE_AM_I isn't available */
		a5xx_preempt_fini(gpu);
		gpu->nr_rings = 1;
	पूर्ण

	a5xx_preempt_hw_init(gpu);

	/* Disable the पूर्णांकerrupts through the initial bringup stage */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INT_0_MASK, A5XX_INT_MASK);

	/* Clear ME_HALT to start the micro engine */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_PFP_ME_CNTL, 0);
	ret = a5xx_me_init(gpu);
	अगर (ret)
		वापस ret;

	ret = a5xx_घातer_init(gpu);
	अगर (ret)
		वापस ret;

	/*
	 * Send a pipeline event stat to get misbehaving counters to start
	 * ticking correctly
	 */
	अगर (adreno_is_a530(adreno_gpu)) अणु
		OUT_PKT7(gpu->rb[0], CP_EVENT_WRITE, 1);
		OUT_RING(gpu->rb[0], CP_EVENT_WRITE_0_EVENT(STAT_EVENT));

		a5xx_flush(gpu, gpu->rb[0], true);
		अगर (!a5xx_idle(gpu, gpu->rb[0]))
			वापस -EINVAL;
	पूर्ण

	/*
	 * If the chip that we are using करोes support loading one, then
	 * try to load a zap shader पूर्णांकo the secure world. If successful
	 * we can use the CP to चयन out of secure mode. If not then we
	 * have no resource but to try to चयन ourselves out manually. If we
	 * guessed wrong then access to the RBBM_SECVID_TRUST_CNTL रेजिस्टर will
	 * be blocked and a permissions violation will soon follow.
	 */
	ret = a5xx_zap_shader_init(gpu);
	अगर (!ret) अणु
		OUT_PKT7(gpu->rb[0], CP_SET_SECURE_MODE, 1);
		OUT_RING(gpu->rb[0], 0x00000000);

		a5xx_flush(gpu, gpu->rb[0], true);
		अगर (!a5xx_idle(gpu, gpu->rb[0]))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (ret == -ENODEV) अणु
		/*
		 * This device करोes not use zap shader (but prपूर्णांक a warning
		 * just in हाल someone got their dt wrong.. hopefully they
		 * have a debug UART to realize the error of their ways...
		 * अगर you mess this up you are about to crash horribly)
		 */
		dev_warn_once(gpu->dev->dev,
			"Zap shader not enabled - using SECVID_TRUST_CNTL instead\n");
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SECVID_TRUST_CNTL, 0x0);
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	/* Last step - yield the ringbuffer */
	a5xx_preempt_start(gpu);

	वापस 0;
पूर्ण

अटल व्योम a5xx_recover(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	adreno_dump_info(gpu);

	क्रम (i = 0; i < 8; i++) अणु
		prपूर्णांकk("CP_SCRATCH_REG%d: %u\n", i,
			gpu_पढ़ो(gpu, REG_A5XX_CP_SCRATCH_REG(i)));
	पूर्ण

	अगर (hang_debug)
		a5xx_dump(gpu);

	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SW_RESET_CMD, 1);
	gpu_पढ़ो(gpu, REG_A5XX_RBBM_SW_RESET_CMD);
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_SW_RESET_CMD, 0);
	adreno_recover(gpu);
पूर्ण

अटल व्योम a5xx_destroy(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	DBG("%s", gpu->name);

	a5xx_preempt_fini(gpu);

	अगर (a5xx_gpu->pm4_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->pm4_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->pm4_bo);
	पूर्ण

	अगर (a5xx_gpu->pfp_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->pfp_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->pfp_bo);
	पूर्ण

	अगर (a5xx_gpu->gpmu_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->gpmu_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->gpmu_bo);
	पूर्ण

	अगर (a5xx_gpu->shaकरोw_bo) अणु
		msm_gem_unpin_iova(a5xx_gpu->shaकरोw_bo, gpu->aspace);
		drm_gem_object_put(a5xx_gpu->shaकरोw_bo);
	पूर्ण

	adreno_gpu_cleanup(adreno_gpu);
	kमुक्त(a5xx_gpu);
पूर्ण

अटल अंतरभूत bool _a5xx_check_idle(काष्ठा msm_gpu *gpu)
अणु
	अगर (gpu_पढ़ो(gpu, REG_A5XX_RBBM_STATUS) & ~A5XX_RBBM_STATUS_HI_BUSY)
		वापस false;

	/*
	 * Nearly every abnormality ends up pausing the GPU and triggering a
	 * fault so we can safely just watch क्रम this one पूर्णांकerrupt to fire
	 */
	वापस !(gpu_पढ़ो(gpu, REG_A5XX_RBBM_INT_0_STATUS) &
		A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT);
पूर्ण

bool a5xx_idle(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	अगर (ring != a5xx_gpu->cur_ring) अणु
		WARN(1, "Tried to idle a non-current ringbuffer\n");
		वापस false;
	पूर्ण

	/* रुको क्रम CP to drain ringbuffer: */
	अगर (!adreno_idle(gpu, ring))
		वापस false;

	अगर (spin_until(_a5xx_check_idle(gpu))) अणु
		DRM_ERROR("%s: %ps: timeout waiting for GPU to idle: status %8.8X irq %8.8X rptr/wptr %d/%d\n",
			gpu->name, __builtin_वापस_address(0),
			gpu_पढ़ो(gpu, REG_A5XX_RBBM_STATUS),
			gpu_पढ़ो(gpu, REG_A5XX_RBBM_INT_0_STATUS),
			gpu_पढ़ो(gpu, REG_A5XX_CP_RB_RPTR),
			gpu_पढ़ो(gpu, REG_A5XX_CP_RB_WPTR));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक a5xx_fault_handler(व्योम *arg, अचिन्हित दीर्घ iova, पूर्णांक flags)
अणु
	काष्ठा msm_gpu *gpu = arg;
	pr_warn_ratelimited("*** gpu fault: iova=%08lx, flags=%d (%u,%u,%u,%u)\n",
			iova, flags,
			gpu_पढ़ो(gpu, REG_A5XX_CP_SCRATCH_REG(4)),
			gpu_पढ़ो(gpu, REG_A5XX_CP_SCRATCH_REG(5)),
			gpu_पढ़ो(gpu, REG_A5XX_CP_SCRATCH_REG(6)),
			gpu_पढ़ो(gpu, REG_A5XX_CP_SCRATCH_REG(7)));

	वापस -EFAULT;
पूर्ण

अटल व्योम a5xx_cp_err_irq(काष्ठा msm_gpu *gpu)
अणु
	u32 status = gpu_पढ़ो(gpu, REG_A5XX_CP_INTERRUPT_STATUS);

	अगर (status & A5XX_CP_INT_CP_OPCODE_ERROR) अणु
		u32 val;

		gpu_ग_लिखो(gpu, REG_A5XX_CP_PFP_STAT_ADDR, 0);

		/*
		 * REG_A5XX_CP_PFP_STAT_DATA is indexed, and we want index 1 so
		 * पढ़ो it twice
		 */

		gpu_पढ़ो(gpu, REG_A5XX_CP_PFP_STAT_DATA);
		val = gpu_पढ़ो(gpu, REG_A5XX_CP_PFP_STAT_DATA);

		dev_err_ratelimited(gpu->dev->dev, "CP | opcode error | possible opcode=0x%8.8X\n",
			val);
	पूर्ण

	अगर (status & A5XX_CP_INT_CP_HW_FAULT_ERROR)
		dev_err_ratelimited(gpu->dev->dev, "CP | HW fault | status=0x%8.8X\n",
			gpu_पढ़ो(gpu, REG_A5XX_CP_HW_FAULT));

	अगर (status & A5XX_CP_INT_CP_DMA_ERROR)
		dev_err_ratelimited(gpu->dev->dev, "CP | DMA error\n");

	अगर (status & A5XX_CP_INT_CP_REGISTER_PROTECTION_ERROR) अणु
		u32 val = gpu_पढ़ो(gpu, REG_A5XX_CP_PROTECT_STATUS);

		dev_err_ratelimited(gpu->dev->dev,
			"CP | protected mode error | %s | addr=0x%8.8X | status=0x%8.8X\n",
			val & (1 << 24) ? "WRITE" : "READ",
			(val & 0xFFFFF) >> 2, val);
	पूर्ण

	अगर (status & A5XX_CP_INT_CP_AHB_ERROR) अणु
		u32 status = gpu_पढ़ो(gpu, REG_A5XX_CP_AHB_FAULT);
		स्थिर अक्षर *access[16] = अणु "reserved", "reserved",
			"timestamp lo", "timestamp hi", "pfp read", "pfp write",
			"", "", "me read", "me write", "", "", "crashdump read",
			"crashdump write" पूर्ण;

		dev_err_ratelimited(gpu->dev->dev,
			"CP | AHB error | addr=%X access=%s error=%d | status=0x%8.8X\n",
			status & 0xFFFFF, access[(status >> 24) & 0xF],
			(status & (1 << 31)), status);
	पूर्ण
पूर्ण

अटल व्योम a5xx_rbbm_err_irq(काष्ठा msm_gpu *gpu, u32 status)
अणु
	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR) अणु
		u32 val = gpu_पढ़ो(gpu, REG_A5XX_RBBM_AHB_ERROR_STATUS);

		dev_err_ratelimited(gpu->dev->dev,
			"RBBM | AHB bus error | %s | addr=0x%X | ports=0x%X:0x%X\n",
			val & (1 << 28) ? "WRITE" : "READ",
			(val & 0xFFFFF) >> 2, (val >> 20) & 0x3,
			(val >> 24) & 0xF);

		/* Clear the error */
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_AHB_CMD, (1 << 4));

		/* Clear the पूर्णांकerrupt */
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INT_CLEAR_CMD,
			A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR);
	पूर्ण

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_TRANSFER_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | AHB transfer timeout\n");

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_ME_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ME master split | status=0x%X\n",
			gpu_पढ़ो(gpu, REG_A5XX_RBBM_AHB_ME_SPLIT_STATUS));

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_PFP_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | PFP master split | status=0x%X\n",
			gpu_पढ़ो(gpu, REG_A5XX_RBBM_AHB_PFP_SPLIT_STATUS));

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_ETS_MS_TIMEOUT)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ETS master split | status=0x%X\n",
			gpu_पढ़ो(gpu, REG_A5XX_RBBM_AHB_ETS_SPLIT_STATUS));

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNC_OVERFLOW)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ATB ASYNC overflow\n");

	अगर (status & A5XX_RBBM_INT_0_MASK_RBBM_ATB_BUS_OVERFLOW)
		dev_err_ratelimited(gpu->dev->dev, "RBBM | ATB bus overflow\n");
पूर्ण

अटल व्योम a5xx_uche_err_irq(काष्ठा msm_gpu *gpu)
अणु
	uपूर्णांक64_t addr = (uपूर्णांक64_t) gpu_पढ़ो(gpu, REG_A5XX_UCHE_TRAP_LOG_HI);

	addr |= gpu_पढ़ो(gpu, REG_A5XX_UCHE_TRAP_LOG_LO);

	dev_err_ratelimited(gpu->dev->dev, "UCHE | Out of bounds access | addr=0x%llX\n",
		addr);
पूर्ण

अटल व्योम a5xx_gpmu_err_irq(काष्ठा msm_gpu *gpu)
अणु
	dev_err_ratelimited(gpu->dev->dev, "GPMU | voltage droop\n");
पूर्ण

अटल व्योम a5xx_fault_detect_irq(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा drm_device *dev = gpu->dev;
	काष्ठा msm_ringbuffer *ring = gpu->funcs->active_ring(gpu);

	DRM_DEV_ERROR(dev->dev, "gpu fault ring %d fence %x status %8.8X rb %4.4x/%4.4x ib1 %16.16llX/%4.4x ib2 %16.16llX/%4.4x\n",
		ring ? ring->id : -1, ring ? ring->seqno : 0,
		gpu_पढ़ो(gpu, REG_A5XX_RBBM_STATUS),
		gpu_पढ़ो(gpu, REG_A5XX_CP_RB_RPTR),
		gpu_पढ़ो(gpu, REG_A5XX_CP_RB_WPTR),
		gpu_पढ़ो64(gpu, REG_A5XX_CP_IB1_BASE, REG_A5XX_CP_IB1_BASE_HI),
		gpu_पढ़ो(gpu, REG_A5XX_CP_IB1_BUFSZ),
		gpu_पढ़ो64(gpu, REG_A5XX_CP_IB2_BASE, REG_A5XX_CP_IB2_BASE_HI),
		gpu_पढ़ो(gpu, REG_A5XX_CP_IB2_BUFSZ));

	/* Turn off the hangcheck समयr to keep it from bothering us */
	del_समयr(&gpu->hangcheck_समयr);

	kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
पूर्ण

#घोषणा RBBM_ERROR_MASK \
	(A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR | \
	A5XX_RBBM_INT_0_MASK_RBBM_TRANSFER_TIMEOUT | \
	A5XX_RBBM_INT_0_MASK_RBBM_ME_MS_TIMEOUT | \
	A5XX_RBBM_INT_0_MASK_RBBM_PFP_MS_TIMEOUT | \
	A5XX_RBBM_INT_0_MASK_RBBM_ETS_MS_TIMEOUT | \
	A5XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNC_OVERFLOW)

अटल irqवापस_t a5xx_irq(काष्ठा msm_gpu *gpu)
अणु
	u32 status = gpu_पढ़ो(gpu, REG_A5XX_RBBM_INT_0_STATUS);

	/*
	 * Clear all the पूर्णांकerrupts except RBBM_AHB_ERROR - अगर we clear it
	 * beक्रमe the source is cleared the पूर्णांकerrupt will storm.
	 */
	gpu_ग_लिखो(gpu, REG_A5XX_RBBM_INT_CLEAR_CMD,
		status & ~A5XX_RBBM_INT_0_MASK_RBBM_AHB_ERROR);

	/* Pass status to a5xx_rbbm_err_irq because we've alपढ़ोy cleared it */
	अगर (status & RBBM_ERROR_MASK)
		a5xx_rbbm_err_irq(gpu, status);

	अगर (status & A5XX_RBBM_INT_0_MASK_CP_HW_ERROR)
		a5xx_cp_err_irq(gpu);

	अगर (status & A5XX_RBBM_INT_0_MASK_MISC_HANG_DETECT)
		a5xx_fault_detect_irq(gpu);

	अगर (status & A5XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS)
		a5xx_uche_err_irq(gpu);

	अगर (status & A5XX_RBBM_INT_0_MASK_GPMU_VOLTAGE_DROOP)
		a5xx_gpmu_err_irq(gpu);

	अगर (status & A5XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS) अणु
		a5xx_preempt_trigger(gpu);
		msm_gpu_retire(gpu);
	पूर्ण

	अगर (status & A5XX_RBBM_INT_0_MASK_CP_SW)
		a5xx_preempt_irq(gpu);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर u32 a5xx_रेजिस्टरs[] = अणु
	0x0000, 0x0002, 0x0004, 0x0020, 0x0022, 0x0026, 0x0029, 0x002B,
	0x002E, 0x0035, 0x0038, 0x0042, 0x0044, 0x0044, 0x0047, 0x0095,
	0x0097, 0x00BB, 0x03A0, 0x0464, 0x0469, 0x046F, 0x04D2, 0x04D3,
	0x04E0, 0x0533, 0x0540, 0x0555, 0x0800, 0x081A, 0x081F, 0x0841,
	0x0860, 0x0860, 0x0880, 0x08A0, 0x0B00, 0x0B12, 0x0B15, 0x0B28,
	0x0B78, 0x0B7F, 0x0BB0, 0x0BBD, 0x0BC0, 0x0BC6, 0x0BD0, 0x0C53,
	0x0C60, 0x0C61, 0x0C80, 0x0C82, 0x0C84, 0x0C85, 0x0C90, 0x0C98,
	0x0CA0, 0x0CA0, 0x0CB0, 0x0CB2, 0x2180, 0x2185, 0x2580, 0x2585,
	0x0CC1, 0x0CC1, 0x0CC4, 0x0CC7, 0x0CCC, 0x0CCC, 0x0CD0, 0x0CD8,
	0x0CE0, 0x0CE5, 0x0CE8, 0x0CE8, 0x0CEC, 0x0CF1, 0x0CFB, 0x0D0E,
	0x2100, 0x211E, 0x2140, 0x2145, 0x2500, 0x251E, 0x2540, 0x2545,
	0x0D10, 0x0D17, 0x0D20, 0x0D23, 0x0D30, 0x0D30, 0x20C0, 0x20C0,
	0x24C0, 0x24C0, 0x0E40, 0x0E43, 0x0E4A, 0x0E4A, 0x0E50, 0x0E57,
	0x0E60, 0x0E7C, 0x0E80, 0x0E8E, 0x0E90, 0x0E96, 0x0EA0, 0x0EA8,
	0x0EB0, 0x0EB2, 0xE140, 0xE147, 0xE150, 0xE187, 0xE1A0, 0xE1A9,
	0xE1B0, 0xE1B6, 0xE1C0, 0xE1C7, 0xE1D0, 0xE1D1, 0xE200, 0xE201,
	0xE210, 0xE21C, 0xE240, 0xE268, 0xE000, 0xE006, 0xE010, 0xE09A,
	0xE0A0, 0xE0A4, 0xE0AA, 0xE0EB, 0xE100, 0xE105, 0xE380, 0xE38F,
	0xE3B0, 0xE3B0, 0xE400, 0xE405, 0xE408, 0xE4E9, 0xE4F0, 0xE4F0,
	0xE280, 0xE280, 0xE282, 0xE2A3, 0xE2A5, 0xE2C2, 0xE940, 0xE947,
	0xE950, 0xE987, 0xE9A0, 0xE9A9, 0xE9B0, 0xE9B6, 0xE9C0, 0xE9C7,
	0xE9D0, 0xE9D1, 0xEA00, 0xEA01, 0xEA10, 0xEA1C, 0xEA40, 0xEA68,
	0xE800, 0xE806, 0xE810, 0xE89A, 0xE8A0, 0xE8A4, 0xE8AA, 0xE8EB,
	0xE900, 0xE905, 0xEB80, 0xEB8F, 0xEBB0, 0xEBB0, 0xEC00, 0xEC05,
	0xEC08, 0xECE9, 0xECF0, 0xECF0, 0xEA80, 0xEA80, 0xEA82, 0xEAA3,
	0xEAA5, 0xEAC2, 0xA800, 0xA800, 0xA820, 0xA828, 0xA840, 0xA87D,
	0XA880, 0xA88D, 0xA890, 0xA8A3, 0xA8D0, 0xA8D8, 0xA8E0, 0xA8F5,
	0xAC60, 0xAC60, ~0,
पूर्ण;

अटल व्योम a5xx_dump(काष्ठा msm_gpu *gpu)
अणु
	DRM_DEV_INFO(gpu->dev->dev, "status:   %08x\n",
		gpu_पढ़ो(gpu, REG_A5XX_RBBM_STATUS));
	adreno_dump(gpu);
पूर्ण

अटल पूर्णांक a5xx_pm_resume(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक ret;

	/* Turn on the core घातer */
	ret = msm_gpu_pm_resume(gpu);
	अगर (ret)
		वापस ret;

	/* Adreno 508, 509, 510, 512 needs manual RBBM sus/res control */
	अगर (!(adreno_is_a530(adreno_gpu) || adreno_is_a540(adreno_gpu))) अणु
		/* Halt the sp_input_clk at HM level */
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_CLOCK_CNTL, 0x00000055);
		a5xx_set_hwcg(gpu, true);
		/* Turn on sp_input_clk at HM level */
		gpu_rmw(gpu, REG_A5XX_RBBM_CLOCK_CNTL, 0xff, 0);
		वापस 0;
	पूर्ण

	/* Turn the RBCCU करोमुख्य first to limit the chances of voltage droop */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_RBCCU_POWER_CNTL, 0x778000);

	/* Wait 3 usecs beक्रमe polling */
	udelay(3);

	ret = spin_usecs(gpu, 20, REG_A5XX_GPMU_RBCCU_PWR_CLK_STATUS,
		(1 << 20), (1 << 20));
	अगर (ret) अणु
		DRM_ERROR("%s: timeout waiting for RBCCU GDSC enable: %X\n",
			gpu->name,
			gpu_पढ़ो(gpu, REG_A5XX_GPMU_RBCCU_PWR_CLK_STATUS));
		वापस ret;
	पूर्ण

	/* Turn on the SP करोमुख्य */
	gpu_ग_लिखो(gpu, REG_A5XX_GPMU_SP_POWER_CNTL, 0x778000);
	ret = spin_usecs(gpu, 20, REG_A5XX_GPMU_SP_PWR_CLK_STATUS,
		(1 << 20), (1 << 20));
	अगर (ret)
		DRM_ERROR("%s: timeout waiting for SP GDSC enable\n",
			gpu->name);

	वापस ret;
पूर्ण

अटल पूर्णांक a5xx_pm_suspend(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	u32 mask = 0xf;
	पूर्णांक i, ret;

	/* A508, A510 have 3 XIN ports in VBIF */
	अगर (adreno_is_a508(adreno_gpu) || adreno_is_a510(adreno_gpu))
		mask = 0x7;

	/* Clear the VBIF pipe beक्रमe shutting करोwn */
	gpu_ग_लिखो(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL0, mask);
	spin_until((gpu_पढ़ो(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL1) &
				mask) == mask);

	gpu_ग_लिखो(gpu, REG_A5XX_VBIF_XIN_HALT_CTRL0, 0);

	/*
	 * Reset the VBIF beक्रमe घातer collapse to aव्योम issue with FIFO
	 * entries on Adreno A510 and A530 (the others will tend to lock up)
	 */
	अगर (adreno_is_a510(adreno_gpu) || adreno_is_a530(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_BLOCK_SW_RESET_CMD, 0x003C0000);
		gpu_ग_लिखो(gpu, REG_A5XX_RBBM_BLOCK_SW_RESET_CMD, 0x00000000);
	पूर्ण

	ret = msm_gpu_pm_suspend(gpu);
	अगर (ret)
		वापस ret;

	अगर (a5xx_gpu->has_whereami)
		क्रम (i = 0; i < gpu->nr_rings; i++)
			a5xx_gpu->shaकरोw[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक a5xx_get_बारtamp(काष्ठा msm_gpu *gpu, uपूर्णांक64_t *value)
अणु
	*value = gpu_पढ़ो64(gpu, REG_A5XX_RBBM_ALWAYSON_COUNTER_LO,
		REG_A5XX_RBBM_ALWAYSON_COUNTER_HI);

	वापस 0;
पूर्ण

काष्ठा a5xx_crashdumper अणु
	व्योम *ptr;
	काष्ठा drm_gem_object *bo;
	u64 iova;
पूर्ण;

काष्ठा a5xx_gpu_state अणु
	काष्ठा msm_gpu_state base;
	u32 *hlsqregs;
पूर्ण;

अटल पूर्णांक a5xx_crashdumper_init(काष्ठा msm_gpu *gpu,
		काष्ठा a5xx_crashdumper *dumper)
अणु
	dumper->ptr = msm_gem_kernel_new_locked(gpu->dev,
		SZ_1M, MSM_BO_UNCACHED, gpu->aspace,
		&dumper->bo, &dumper->iova);

	अगर (!IS_ERR(dumper->ptr))
		msm_gem_object_set_name(dumper->bo, "crashdump");

	वापस PTR_ERR_OR_ZERO(dumper->ptr);
पूर्ण

अटल पूर्णांक a5xx_crashdumper_run(काष्ठा msm_gpu *gpu,
		काष्ठा a5xx_crashdumper *dumper)
अणु
	u32 val;

	अगर (IS_ERR_OR_शून्य(dumper->ptr))
		वापस -EINVAL;

	gpu_ग_लिखो64(gpu, REG_A5XX_CP_CRASH_SCRIPT_BASE_LO,
		REG_A5XX_CP_CRASH_SCRIPT_BASE_HI, dumper->iova);

	gpu_ग_लिखो(gpu, REG_A5XX_CP_CRASH_DUMP_CNTL, 1);

	वापस gpu_poll_समयout(gpu, REG_A5XX_CP_CRASH_DUMP_CNTL, val,
		val & 0x04, 100, 10000);
पूर्ण

/*
 * These are a list of the रेजिस्टरs that need to be पढ़ो through the HLSQ
 * aperture through the crashdumper.  These are not nominally accessible from
 * the CPU on a secure platक्रमm.
 */
अटल स्थिर काष्ठा अणु
	u32 type;
	u32 regoffset;
	u32 count;
पूर्ण a5xx_hlsq_aperture_regs[] = अणु
	अणु 0x35, 0xe00, 0x32 पूर्ण,   /* HSLQ non-context */
	अणु 0x31, 0x2080, 0x1 पूर्ण,   /* HLSQ 2D context 0 */
	अणु 0x33, 0x2480, 0x1 पूर्ण,   /* HLSQ 2D context 1 */
	अणु 0x32, 0xe780, 0x62 पूर्ण,  /* HLSQ 3D context 0 */
	अणु 0x34, 0xef80, 0x62 पूर्ण,  /* HLSQ 3D context 1 */
	अणु 0x3f, 0x0ec0, 0x40 पूर्ण,  /* SP non-context */
	अणु 0x3d, 0x2040, 0x1 पूर्ण,   /* SP 2D context 0 */
	अणु 0x3b, 0x2440, 0x1 पूर्ण,   /* SP 2D context 1 */
	अणु 0x3e, 0xe580, 0x170 पूर्ण, /* SP 3D context 0 */
	अणु 0x3c, 0xed80, 0x170 पूर्ण, /* SP 3D context 1 */
	अणु 0x3a, 0x0f00, 0x1c पूर्ण,  /* TP non-context */
	अणु 0x38, 0x2000, 0xa पूर्ण,   /* TP 2D context 0 */
	अणु 0x36, 0x2400, 0xa पूर्ण,   /* TP 2D context 1 */
	अणु 0x39, 0xe700, 0x80 पूर्ण,  /* TP 3D context 0 */
	अणु 0x37, 0xef00, 0x80 पूर्ण,  /* TP 3D context 1 */
पूर्ण;

अटल व्योम a5xx_gpu_state_get_hlsq_regs(काष्ठा msm_gpu *gpu,
		काष्ठा a5xx_gpu_state *a5xx_state)
अणु
	काष्ठा a5xx_crashdumper dumper = अणु 0 पूर्ण;
	u32 offset, count = 0;
	u64 *ptr;
	पूर्णांक i;

	अगर (a5xx_crashdumper_init(gpu, &dumper))
		वापस;

	/* The script will be written at offset 0 */
	ptr = dumper.ptr;

	/* Start writing the data at offset 256k */
	offset = dumper.iova + (256 * SZ_1K);

	/* Count how many additional रेजिस्टरs to get from the HLSQ aperture */
	क्रम (i = 0; i < ARRAY_SIZE(a5xx_hlsq_aperture_regs); i++)
		count += a5xx_hlsq_aperture_regs[i].count;

	a5xx_state->hlsqregs = kसुस्मृति(count, माप(u32), GFP_KERNEL);
	अगर (!a5xx_state->hlsqregs)
		वापस;

	/* Build the crashdump script */
	क्रम (i = 0; i < ARRAY_SIZE(a5xx_hlsq_aperture_regs); i++) अणु
		u32 type = a5xx_hlsq_aperture_regs[i].type;
		u32 c = a5xx_hlsq_aperture_regs[i].count;

		/* Write the रेजिस्टर to select the desired bank */
		*ptr++ = ((u64) type << 8);
		*ptr++ = (((u64) REG_A5XX_HLSQ_DBG_READ_SEL) << 44) |
			(1 << 21) | 1;

		*ptr++ = offset;
		*ptr++ = (((u64) REG_A5XX_HLSQ_DBG_AHB_READ_APERTURE) << 44)
			| c;

		offset += c * माप(u32);
	पूर्ण

	/* Write two zeros to बंद off the script */
	*ptr++ = 0;
	*ptr++ = 0;

	अगर (a5xx_crashdumper_run(gpu, &dumper)) अणु
		kमुक्त(a5xx_state->hlsqregs);
		msm_gem_kernel_put(dumper.bo, gpu->aspace, true);
		वापस;
	पूर्ण

	/* Copy the data from the crashdumper to the state */
	स_नकल(a5xx_state->hlsqregs, dumper.ptr + (256 * SZ_1K),
		count * माप(u32));

	msm_gem_kernel_put(dumper.bo, gpu->aspace, true);
पूर्ण

अटल काष्ठा msm_gpu_state *a5xx_gpu_state_get(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा a5xx_gpu_state *a5xx_state = kzalloc(माप(*a5xx_state),
			GFP_KERNEL);

	अगर (!a5xx_state)
		वापस ERR_PTR(-ENOMEM);

	/* Temporarily disable hardware घड़ी gating beक्रमe पढ़ोing the hw */
	a5xx_set_hwcg(gpu, false);

	/* First get the generic state from the adreno core */
	adreno_gpu_state_get(gpu, &(a5xx_state->base));

	a5xx_state->base.rbbm_status = gpu_पढ़ो(gpu, REG_A5XX_RBBM_STATUS);

	/* Get the HLSQ regs with the help of the crashdumper */
	a5xx_gpu_state_get_hlsq_regs(gpu, a5xx_state);

	a5xx_set_hwcg(gpu, true);

	वापस &a5xx_state->base;
पूर्ण

अटल व्योम a5xx_gpu_state_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_gpu_state *state = container_of(kref,
		काष्ठा msm_gpu_state, ref);
	काष्ठा a5xx_gpu_state *a5xx_state = container_of(state,
		काष्ठा a5xx_gpu_state, base);

	kमुक्त(a5xx_state->hlsqregs);

	adreno_gpu_state_destroy(state);
	kमुक्त(a5xx_state);
पूर्ण

अटल पूर्णांक a5xx_gpu_state_put(काष्ठा msm_gpu_state *state)
अणु
	अगर (IS_ERR_OR_शून्य(state))
		वापस 1;

	वापस kref_put(&state->ref, a5xx_gpu_state_destroy);
पूर्ण


#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
अटल व्योम a5xx_show(काष्ठा msm_gpu *gpu, काष्ठा msm_gpu_state *state,
		      काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक i, j;
	u32 pos = 0;
	काष्ठा a5xx_gpu_state *a5xx_state = container_of(state,
		काष्ठा a5xx_gpu_state, base);

	अगर (IS_ERR_OR_शून्य(state))
		वापस;

	adreno_show(gpu, state, p);

	/* Dump the additional a5xx HLSQ रेजिस्टरs */
	अगर (!a5xx_state->hlsqregs)
		वापस;

	drm_म_लिखो(p, "registers-hlsq:\n");

	क्रम (i = 0; i < ARRAY_SIZE(a5xx_hlsq_aperture_regs); i++) अणु
		u32 o = a5xx_hlsq_aperture_regs[i].regoffset;
		u32 c = a5xx_hlsq_aperture_regs[i].count;

		क्रम (j = 0; j < c; j++, pos++, o++) अणु
			/*
			 * To keep the crashdump simple we pull the entire range
			 * क्रम each रेजिस्टर type but not all of the रेजिस्टरs
			 * in the range are valid. Fortunately invalid रेजिस्टरs
			 * stick out like a sore thumb with a value of
			 * 0xdeadbeef
			 */
			अगर (a5xx_state->hlsqregs[pos] == 0xdeadbeef)
				जारी;

			drm_म_लिखो(p, "  - { offset: 0x%04x, value: 0x%08x }\n",
				o << 2, a5xx_state->hlsqregs[pos]);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा msm_ringbuffer *a5xx_active_ring(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	वापस a5xx_gpu->cur_ring;
पूर्ण

अटल अचिन्हित दीर्घ a5xx_gpu_busy(काष्ठा msm_gpu *gpu)
अणु
	u64 busy_cycles, busy_समय;

	/* Only पढ़ो the gpu busy अगर the hardware is alपढ़ोy active */
	अगर (pm_runसमय_get_अगर_in_use(&gpu->pdev->dev) == 0)
		वापस 0;

	busy_cycles = gpu_पढ़ो64(gpu, REG_A5XX_RBBM_PERFCTR_RBBM_0_LO,
			REG_A5XX_RBBM_PERFCTR_RBBM_0_HI);

	busy_समय = busy_cycles - gpu->devfreq.busy_cycles;
	करो_भाग(busy_समय, clk_get_rate(gpu->core_clk) / 1000000);

	gpu->devfreq.busy_cycles = busy_cycles;

	pm_runसमय_put(&gpu->pdev->dev);

	अगर (WARN_ON(busy_समय > ~0LU))
		वापस ~0LU;

	वापस (अचिन्हित दीर्घ)busy_समय;
पूर्ण

अटल uपूर्णांक32_t a5xx_get_rptr(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);

	अगर (a5xx_gpu->has_whereami)
		वापस a5xx_gpu->shaकरोw[ring->id];

	वापस ring->memptrs->rptr = gpu_पढ़ो(gpu, REG_A5XX_CP_RB_RPTR);
पूर्ण

अटल स्थिर काष्ठा adreno_gpu_funcs funcs = अणु
	.base = अणु
		.get_param = adreno_get_param,
		.hw_init = a5xx_hw_init,
		.pm_suspend = a5xx_pm_suspend,
		.pm_resume = a5xx_pm_resume,
		.recover = a5xx_recover,
		.submit = a5xx_submit,
		.active_ring = a5xx_active_ring,
		.irq = a5xx_irq,
		.destroy = a5xx_destroy,
#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
		.show = a5xx_show,
#पूर्ण_अगर
#अगर defined(CONFIG_DEBUG_FS)
		.debugfs_init = a5xx_debugfs_init,
#पूर्ण_अगर
		.gpu_busy = a5xx_gpu_busy,
		.gpu_state_get = a5xx_gpu_state_get,
		.gpu_state_put = a5xx_gpu_state_put,
		.create_address_space = adreno_iommu_create_address_space,
		.get_rptr = a5xx_get_rptr,
	पूर्ण,
	.get_बारtamp = a5xx_get_बारtamp,
पूर्ण;

अटल व्योम check_speed_bin(काष्ठा device *dev)
अणु
	काष्ठा nvmem_cell *cell;
	u32 val;

	/*
	 * If the OPP table specअगरies a opp-supported-hw property then we have
	 * to set something with dev_pm_opp_set_supported_hw() or the table
	 * करोesn't get populated so pick an arbitrary value that should
	 * ensure the शेष frequencies are selected but not conflict with any
	 * actual bins
	 */
	val = 0x80;

	cell = nvmem_cell_get(dev, "speed_bin");

	अगर (!IS_ERR(cell)) अणु
		व्योम *buf = nvmem_cell_पढ़ो(cell, शून्य);

		अगर (!IS_ERR(buf)) अणु
			u8 bin = *((u8 *) buf);

			val = (1 << bin);
			kमुक्त(buf);
		पूर्ण

		nvmem_cell_put(cell);
	पूर्ण

	dev_pm_opp_set_supported_hw(dev, &val, 1);
पूर्ण

काष्ठा msm_gpu *a5xx_gpu_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	काष्ठा a5xx_gpu *a5xx_gpu = शून्य;
	काष्ठा adreno_gpu *adreno_gpu;
	काष्ठा msm_gpu *gpu;
	पूर्णांक ret;

	अगर (!pdev) अणु
		DRM_DEV_ERROR(dev->dev, "No A5XX device is defined\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	a5xx_gpu = kzalloc(माप(*a5xx_gpu), GFP_KERNEL);
	अगर (!a5xx_gpu)
		वापस ERR_PTR(-ENOMEM);

	adreno_gpu = &a5xx_gpu->base;
	gpu = &adreno_gpu->base;

	adreno_gpu->रेजिस्टरs = a5xx_रेजिस्टरs;

	a5xx_gpu->lm_leakage = 0x4E001A;

	check_speed_bin(&pdev->dev);

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 4);
	अगर (ret) अणु
		a5xx_destroy(&(a5xx_gpu->base.base));
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (gpu->aspace)
		msm_mmu_set_fault_handler(gpu->aspace->mmu, gpu, a5xx_fault_handler);

	/* Set up the preemption specअगरic bits and pieces क्रम each ringbuffer */
	a5xx_preempt_init(gpu);

	वापस gpu;
पूर्ण
