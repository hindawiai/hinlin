<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-2019 The Linux Foundation. All rights reserved. */


#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"
#समावेश "msm_gpu_trace.h"
#समावेश "a6xx_gpu.h"
#समावेश "a6xx_gmu.xml.h"

#समावेश <linux/bitfield.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/soc/qcom/llcc-qcom.h>

#घोषणा GPU_PAS_ID 13

अटल अंतरभूत bool _a6xx_check_idle(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	/* Check that the GMU is idle */
	अगर (!a6xx_gmu_isidle(&a6xx_gpu->gmu))
		वापस false;

	/* Check tha the CX master is idle */
	अगर (gpu_पढ़ो(gpu, REG_A6XX_RBBM_STATUS) &
			~A6XX_RBBM_STATUS_CP_AHB_BUSY_CX_MASTER)
		वापस false;

	वापस !(gpu_पढ़ो(gpu, REG_A6XX_RBBM_INT_0_STATUS) &
		A6XX_RBBM_INT_0_MASK_RBBM_HANG_DETECT);
पूर्ण

अटल bool a6xx_idle(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	/* रुको क्रम CP to drain ringbuffer: */
	अगर (!adreno_idle(gpu, ring))
		वापस false;

	अगर (spin_until(_a6xx_check_idle(gpu))) अणु
		DRM_ERROR("%s: %ps: timeout waiting for GPU to idle: status %8.8X irq %8.8X rptr/wptr %d/%d\n",
			gpu->name, __builtin_वापस_address(0),
			gpu_पढ़ो(gpu, REG_A6XX_RBBM_STATUS),
			gpu_पढ़ो(gpu, REG_A6XX_RBBM_INT_0_STATUS),
			gpu_पढ़ो(gpu, REG_A6XX_CP_RB_RPTR),
			gpu_पढ़ो(gpu, REG_A6XX_CP_RB_WPTR));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम a6xx_flush(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	uपूर्णांक32_t wptr;
	अचिन्हित दीर्घ flags;

	/* Expanded APRIV करोesn't need to issue the WHERE_AM_I opcode */
	अगर (a6xx_gpu->has_whereami && !adreno_gpu->base.hw_apriv) अणु
		काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

		OUT_PKT7(ring, CP_WHERE_AM_I, 2);
		OUT_RING(ring, lower_32_bits(shaकरोwptr(a6xx_gpu, ring)));
		OUT_RING(ring, upper_32_bits(shaकरोwptr(a6xx_gpu, ring)));
	पूर्ण

	spin_lock_irqsave(&ring->preempt_lock, flags);

	/* Copy the shaकरोw to the actual रेजिस्टर */
	ring->cur = ring->next;

	/* Make sure to wrap wptr अगर we need to */
	wptr = get_wptr(ring);

	spin_unlock_irqrestore(&ring->preempt_lock, flags);

	/* Make sure everything is posted beक्रमe making a decision */
	mb();

	gpu_ग_लिखो(gpu, REG_A6XX_CP_RB_WPTR, wptr);
पूर्ण

अटल व्योम get_stats_counter(काष्ठा msm_ringbuffer *ring, u32 counter,
		u64 iova)
अणु
	OUT_PKT7(ring, CP_REG_TO_MEM, 3);
	OUT_RING(ring, CP_REG_TO_MEM_0_REG(counter) |
		CP_REG_TO_MEM_0_CNT(2) |
		CP_REG_TO_MEM_0_64B);
	OUT_RING(ring, lower_32_bits(iova));
	OUT_RING(ring, upper_32_bits(iova));
पूर्ण

अटल व्योम a6xx_set_pagetable(काष्ठा a6xx_gpu *a6xx_gpu,
		काष्ठा msm_ringbuffer *ring, काष्ठा msm_file_निजी *ctx)
अणु
	phys_addr_t ttbr;
	u32 asid;
	u64 memptr = rbmemptr(ring, ttbr0);

	अगर (ctx == a6xx_gpu->cur_ctx)
		वापस;

	अगर (msm_iommu_pagetable_params(ctx->aspace->mmu, &ttbr, &asid))
		वापस;

	/* Execute the table update */
	OUT_PKT7(ring, CP_SMMU_TABLE_UPDATE, 4);
	OUT_RING(ring, CP_SMMU_TABLE_UPDATE_0_TTBR0_LO(lower_32_bits(ttbr)));

	OUT_RING(ring,
		CP_SMMU_TABLE_UPDATE_1_TTBR0_HI(upper_32_bits(ttbr)) |
		CP_SMMU_TABLE_UPDATE_1_ASID(asid));
	OUT_RING(ring, CP_SMMU_TABLE_UPDATE_2_CONTEXTIDR(0));
	OUT_RING(ring, CP_SMMU_TABLE_UPDATE_3_CONTEXTBANK(0));

	/*
	 * Write the new TTBR0 to the memstore. This is good क्रम debugging.
	 */
	OUT_PKT7(ring, CP_MEM_WRITE, 4);
	OUT_RING(ring, CP_MEM_WRITE_0_ADDR_LO(lower_32_bits(memptr)));
	OUT_RING(ring, CP_MEM_WRITE_1_ADDR_HI(upper_32_bits(memptr)));
	OUT_RING(ring, lower_32_bits(ttbr));
	OUT_RING(ring, (asid << 16) | upper_32_bits(ttbr));

	/*
	 * And finally, trigger a uche flush to be sure there isn't anything
	 * lingering in that part of the GPU
	 */

	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, 0x31);

	a6xx_gpu->cur_ctx = ctx;
पूर्ण

अटल व्योम a6xx_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
अणु
	अचिन्हित पूर्णांक index = submit->seqno % MSM_GPU_SUBMIT_STATS_COUNT;
	काष्ठा msm_drm_निजी *priv = gpu->dev->dev_निजी;
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा msm_ringbuffer *ring = submit->ring;
	अचिन्हित पूर्णांक i;

	a6xx_set_pagetable(a6xx_gpu, ring, submit->queue->ctx);

	get_stats_counter(ring, REG_A6XX_RBBM_PERFCTR_CP_0_LO,
		rbmemptr_stats(ring, index, cpcycles_start));

	/*
	 * For PM4 the GMU रेजिस्टर offsets are calculated from the base of the
	 * GPU रेजिस्टरs so we need to add 0x1a800 to the रेजिस्टर value on A630
	 * to get the right value from PM4.
	 */
	get_stats_counter(ring, REG_A6XX_CP_ALWAYS_ON_COUNTER_LO,
		rbmemptr_stats(ring, index, alwayson_start));

	/* Invalidate CCU depth and color */
	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(PC_CCU_INVALIDATE_DEPTH));

	OUT_PKT7(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, CP_EVENT_WRITE_0_EVENT(PC_CCU_INVALIDATE_COLOR));

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
			अवरोध;
		पूर्ण
	पूर्ण

	get_stats_counter(ring, REG_A6XX_RBBM_PERFCTR_CP_0_LO,
		rbmemptr_stats(ring, index, cpcycles_end));
	get_stats_counter(ring, REG_A6XX_CP_ALWAYS_ON_COUNTER_LO,
		rbmemptr_stats(ring, index, alwayson_end));

	/* Write the fence to the scratch रेजिस्टर */
	OUT_PKT4(ring, REG_A6XX_CP_SCRATCH_REG(2), 1);
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

	trace_msm_gpu_submit_flush(submit,
		gpu_पढ़ो64(gpu, REG_A6XX_CP_ALWAYS_ON_COUNTER_LO,
			REG_A6XX_CP_ALWAYS_ON_COUNTER_HI));

	a6xx_flush(gpu, ring);
पूर्ण

स्थिर काष्ठा adreno_reglist a630_hwcg[] = अणु
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP1, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP2, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP3, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP0, 0x02022220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP1, 0x02022220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP2, 0x02022220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP3, 0x02022220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP1, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP2, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP3, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP0, 0x0000f3cfपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP1, 0x0000f3cfपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP2, 0x0000f3cfपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP3, 0x0000f3cfपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP0, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP1, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP2, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP3, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP1, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP2, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP3, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP1, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP2, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP3, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP0, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP1, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP2, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP3, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP1, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP2, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP3, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP1, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP2, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP3, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP1, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP2, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP3, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP0, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP1, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP2, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP3, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP1, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP2, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP3, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP1, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP2, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP3, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP1, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP2, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP3, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP0, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP1, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP2, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP3, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_UCHE, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_UCHE, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_UCHE, 0x00222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_UCHE, 0x00000004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB1, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB2, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB3, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB0, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB1, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB2, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB3, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU0, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU1, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU2, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU3, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU0, 0x00040f00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU1, 0x00040f00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU2, 0x00040f00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU3, 0x00040f00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RAC, 0x05022022पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RAC, 0x00005555पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_RAC, 0x00000011पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RAC, 0x00445044पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_GPC, 0x00222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ_2, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_HLSQ, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_GMU_GX, 0x00000222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GMU_GX, 0x00000111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GMU_GX, 0x00000555पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा adreno_reglist a640_hwcg[] = अणु
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP0, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP0, 0x02222220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP0, 0x0000F3CFपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP0, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP0, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP0, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP0, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB0, 0x01002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU0, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU0, 0x00040F00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RAC, 0x05222022पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RAC, 0x00005555पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_RAC, 0x00000011पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RAC, 0x00445044पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_GPC, 0x00222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ_2, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_HLSQ, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_HLSQ, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TEX_FCHE, 0x00000222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TEX_FCHE, 0x00000111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TEX_FCHE, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_UCHE, 0x00000004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_ISDB_CNT, 0x00000182पूर्ण,
	अणुREG_A6XX_RBBM_RAC_THRESHOLD_CNT, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_SP_HYST_CNT, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_GMU_GX, 0x00000222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GMU_GX, 0x00000111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GMU_GX, 0x00000555पूर्ण,
	अणुपूर्ण,
पूर्ण;

स्थिर काष्ठा adreno_reglist a650_hwcg[] = अणु
	अणुREG_A6XX_RBBM_CLOCK_CNTL_SP0, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_SP0, 0x02222220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_SP0, 0x00000080पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_SP0, 0x0000F3CFपूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TP0, 0x02222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL3_TP0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL4_TP0, 0x00022222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY2_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY3_TP0, 0x11111111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY4_TP0, 0x00011111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST2_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST3_TP0, 0x77777777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST4_TP0, 0x00077777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RB0, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RB0, 0x01002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_CCU0, 0x00002220पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RB_CCU0, 0x00040F00पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_RAC, 0x25222022पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL2_RAC, 0x00005555पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_RAC, 0x00000011पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_RAC, 0x00445044पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TSE_RAS_RBBM, 0x04222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_GPC, 0x00222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ_2, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_MODE_HLSQ, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00004000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_VFD, 0x00002222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GPC, 0x00000200पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_HLSQ, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_VFD, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GPC, 0x04104004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_HLSQ, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_TEX_FCHE, 0x00000222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_TEX_FCHE, 0x00000111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_TEX_FCHE, 0x00000777पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_UCHE, 0x22222222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_UCHE, 0x00000004पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_UCHE, 0x00000002पूर्ण,
	अणुREG_A6XX_RBBM_ISDB_CNT, 0x00000182पूर्ण,
	अणुREG_A6XX_RBBM_RAC_THRESHOLD_CNT, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_SP_HYST_CNT, 0x00000000पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_CNTL_GMU_GX, 0x00000222पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_DELAY_GMU_GX, 0x00000111पूर्ण,
	अणुREG_A6XX_RBBM_CLOCK_HYST_GMU_GX, 0x00000555पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम a6xx_set_hwcg(काष्ठा msm_gpu *gpu, bool state)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	स्थिर काष्ठा adreno_reglist *reg;
	अचिन्हित पूर्णांक i;
	u32 val, घड़ी_cntl_on;

	अगर (!adreno_gpu->info->hwcg)
		वापस;

	अगर (adreno_is_a630(adreno_gpu))
		घड़ी_cntl_on = 0x8aa8aa02;
	अन्यथा
		घड़ी_cntl_on = 0x8aa8aa82;

	val = gpu_पढ़ो(gpu, REG_A6XX_RBBM_CLOCK_CNTL);

	/* Don't re-program the रेजिस्टरs अगर they are alपढ़ोy correct */
	अगर ((!state && !val) || (state && (val == घड़ी_cntl_on)))
		वापस;

	/* Disable SP घड़ी beक्रमe programming HWCG रेजिस्टरs */
	gmu_rmw(gmu, REG_A6XX_GPU_GMU_GX_SPTPRAC_CLOCK_CONTROL, 1, 0);

	क्रम (i = 0; (reg = &adreno_gpu->info->hwcg[i], reg->offset); i++)
		gpu_ग_लिखो(gpu, reg->offset, state ? reg->value : 0);

	/* Enable SP घड़ी */
	gmu_rmw(gmu, REG_A6XX_GPU_GMU_GX_SPTPRAC_CLOCK_CONTROL, 0, 1);

	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_CLOCK_CNTL, state ? घड़ी_cntl_on : 0);
पूर्ण

/* For a615, a616, a618, A619, a630, a640 and a680 */
अटल स्थिर u32 a6xx_protect[] = अणु
	A6XX_PROTECT_RDONLY(0x00000, 0x04ff),
	A6XX_PROTECT_RDONLY(0x00501, 0x0005),
	A6XX_PROTECT_RDONLY(0x0050b, 0x02f4),
	A6XX_PROTECT_NORDWR(0x0050e, 0x0000),
	A6XX_PROTECT_NORDWR(0x00510, 0x0000),
	A6XX_PROTECT_NORDWR(0x00534, 0x0000),
	A6XX_PROTECT_NORDWR(0x00800, 0x0082),
	A6XX_PROTECT_NORDWR(0x008a0, 0x0008),
	A6XX_PROTECT_NORDWR(0x008ab, 0x0024),
	A6XX_PROTECT_RDONLY(0x008de, 0x00ae),
	A6XX_PROTECT_NORDWR(0x00900, 0x004d),
	A6XX_PROTECT_NORDWR(0x0098d, 0x0272),
	A6XX_PROTECT_NORDWR(0x00e00, 0x0001),
	A6XX_PROTECT_NORDWR(0x00e03, 0x000c),
	A6XX_PROTECT_NORDWR(0x03c00, 0x00c3),
	A6XX_PROTECT_RDONLY(0x03cc4, 0x1fff),
	A6XX_PROTECT_NORDWR(0x08630, 0x01cf),
	A6XX_PROTECT_NORDWR(0x08e00, 0x0000),
	A6XX_PROTECT_NORDWR(0x08e08, 0x0000),
	A6XX_PROTECT_NORDWR(0x08e50, 0x001f),
	A6XX_PROTECT_NORDWR(0x09624, 0x01db),
	A6XX_PROTECT_NORDWR(0x09e70, 0x0001),
	A6XX_PROTECT_NORDWR(0x09e78, 0x0187),
	A6XX_PROTECT_NORDWR(0x0a630, 0x01cf),
	A6XX_PROTECT_NORDWR(0x0ae02, 0x0000),
	A6XX_PROTECT_NORDWR(0x0ae50, 0x032f),
	A6XX_PROTECT_NORDWR(0x0b604, 0x0000),
	A6XX_PROTECT_NORDWR(0x0be02, 0x0001),
	A6XX_PROTECT_NORDWR(0x0be20, 0x17df),
	A6XX_PROTECT_NORDWR(0x0f000, 0x0bff),
	A6XX_PROTECT_RDONLY(0x0fc00, 0x1fff),
	A6XX_PROTECT_NORDWR(0x11c00, 0x0000), /* note: infinite range */
पूर्ण;

/* These are क्रम a620 and a650 */
अटल स्थिर u32 a650_protect[] = अणु
	A6XX_PROTECT_RDONLY(0x00000, 0x04ff),
	A6XX_PROTECT_RDONLY(0x00501, 0x0005),
	A6XX_PROTECT_RDONLY(0x0050b, 0x02f4),
	A6XX_PROTECT_NORDWR(0x0050e, 0x0000),
	A6XX_PROTECT_NORDWR(0x00510, 0x0000),
	A6XX_PROTECT_NORDWR(0x00534, 0x0000),
	A6XX_PROTECT_NORDWR(0x00800, 0x0082),
	A6XX_PROTECT_NORDWR(0x008a0, 0x0008),
	A6XX_PROTECT_NORDWR(0x008ab, 0x0024),
	A6XX_PROTECT_RDONLY(0x008de, 0x00ae),
	A6XX_PROTECT_NORDWR(0x00900, 0x004d),
	A6XX_PROTECT_NORDWR(0x0098d, 0x0272),
	A6XX_PROTECT_NORDWR(0x00e00, 0x0001),
	A6XX_PROTECT_NORDWR(0x00e03, 0x000c),
	A6XX_PROTECT_NORDWR(0x03c00, 0x00c3),
	A6XX_PROTECT_RDONLY(0x03cc4, 0x1fff),
	A6XX_PROTECT_NORDWR(0x08630, 0x01cf),
	A6XX_PROTECT_NORDWR(0x08e00, 0x0000),
	A6XX_PROTECT_NORDWR(0x08e08, 0x0000),
	A6XX_PROTECT_NORDWR(0x08e50, 0x001f),
	A6XX_PROTECT_NORDWR(0x08e80, 0x027f),
	A6XX_PROTECT_NORDWR(0x09624, 0x01db),
	A6XX_PROTECT_NORDWR(0x09e60, 0x0011),
	A6XX_PROTECT_NORDWR(0x09e78, 0x0187),
	A6XX_PROTECT_NORDWR(0x0a630, 0x01cf),
	A6XX_PROTECT_NORDWR(0x0ae02, 0x0000),
	A6XX_PROTECT_NORDWR(0x0ae50, 0x032f),
	A6XX_PROTECT_NORDWR(0x0b604, 0x0000),
	A6XX_PROTECT_NORDWR(0x0b608, 0x0007),
	A6XX_PROTECT_NORDWR(0x0be02, 0x0001),
	A6XX_PROTECT_NORDWR(0x0be20, 0x17df),
	A6XX_PROTECT_NORDWR(0x0f000, 0x0bff),
	A6XX_PROTECT_RDONLY(0x0fc00, 0x1fff),
	A6XX_PROTECT_NORDWR(0x18400, 0x1fff),
	A6XX_PROTECT_NORDWR(0x1a800, 0x1fff),
	A6XX_PROTECT_NORDWR(0x1f400, 0x0443),
	A6XX_PROTECT_RDONLY(0x1f844, 0x007b),
	A6XX_PROTECT_NORDWR(0x1f887, 0x001b),
	A6XX_PROTECT_NORDWR(0x1f8c0, 0x0000), /* note: infinite range */
पूर्ण;

अटल व्योम a6xx_set_cp_protect(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	स्थिर u32 *regs = a6xx_protect;
	अचिन्हित i, count = ARRAY_SIZE(a6xx_protect), count_max = 32;

	BUILD_BUG_ON(ARRAY_SIZE(a6xx_protect) > 32);
	BUILD_BUG_ON(ARRAY_SIZE(a650_protect) > 48);

	अगर (adreno_is_a650(adreno_gpu)) अणु
		regs = a650_protect;
		count = ARRAY_SIZE(a650_protect);
		count_max = 48;
	पूर्ण

	/*
	 * Enable access protection to privileged रेजिस्टरs, fault on an access
	 * protect violation and select the last span to protect from the start
	 * address all the way to the end of the रेजिस्टर address space
	 */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_PROTECT_CNTL, BIT(0) | BIT(1) | BIT(3));

	क्रम (i = 0; i < count - 1; i++)
		gpu_ग_लिखो(gpu, REG_A6XX_CP_PROTECT(i), regs[i]);
	/* last CP_PROTECT to have "infinite" length on the last entry */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_PROTECT(count_max - 1), regs[i]);
पूर्ण

अटल व्योम a6xx_set_ubwc_config(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	u32 lower_bit = 2;
	u32 amsbc = 0;
	u32 rgb565_predicator = 0;
	u32 uavflagprd_inv = 0;

	/* a618 is using the hw शेष values */
	अगर (adreno_is_a618(adreno_gpu))
		वापस;

	अगर (adreno_is_a640(adreno_gpu))
		amsbc = 1;

	अगर (adreno_is_a650(adreno_gpu)) अणु
		/* TODO: get ddr type from bootloader and use 2 क्रम LPDDR4 */
		lower_bit = 3;
		amsbc = 1;
		rgb565_predicator = 1;
		uavflagprd_inv = 2;
	पूर्ण

	gpu_ग_लिखो(gpu, REG_A6XX_RB_NC_MODE_CNTL,
		rgb565_predicator << 11 | amsbc << 4 | lower_bit << 1);
	gpu_ग_लिखो(gpu, REG_A6XX_TPL1_NC_MODE_CNTL, lower_bit << 1);
	gpu_ग_लिखो(gpu, REG_A6XX_SP_NC_MODE_CNTL,
		uavflagprd_inv << 4 | lower_bit << 1);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_MODE_CNTL, lower_bit << 21);
पूर्ण

अटल पूर्णांक a6xx_cp_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT7(ring, CP_ME_INIT, 8);

	OUT_RING(ring, 0x0000002f);

	/* Enable multiple hardware contexts */
	OUT_RING(ring, 0x00000003);

	/* Enable error detection */
	OUT_RING(ring, 0x20000000);

	/* Don't enable header dump */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	/* No workarounds enabled */
	OUT_RING(ring, 0x00000000);

	/* Pad rest of the cmds with 0's */
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	a6xx_flush(gpu, ring);
	वापस a6xx_idle(gpu, ring) ? 0 : -EINVAL;
पूर्ण

/*
 * Check that the microcode version is new enough to include several key
 * security fixes. Return true अगर the ucode is safe.
 */
अटल bool a6xx_ucode_check_version(काष्ठा a6xx_gpu *a6xx_gpu,
		काष्ठा drm_gem_object *obj)
अणु
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	u32 *buf = msm_gem_get_vaddr(obj);
	bool ret = false;

	अगर (IS_ERR(buf))
		वापस false;

	/*
	 * Tarमाला_लो up to a640 (a618, a630 and a640) need to check क्रम a
	 * microcode version that is patched to support the whereami opcode or
	 * one that is new enough to include it by शेष.
	 */
	अगर (adreno_is_a618(adreno_gpu) || adreno_is_a630(adreno_gpu) ||
		adreno_is_a640(adreno_gpu)) अणु
		/*
		 * If the lowest nibble is 0xa that is an indication that this
		 * microcode has been patched. The actual version is in dword
		 * [3] but we only care about the patchlevel which is the lowest
		 * nibble of dword [3]
		 *
		 * Otherwise check that the firmware is greater than or equal
		 * to 1.90 which was the first version that had this fix built
		 * in
		 */
		अगर ((((buf[0] & 0xf) == 0xa) && (buf[2] & 0xf) >= 1) ||
			(buf[0] & 0xfff) >= 0x190) अणु
			a6xx_gpu->has_whereami = true;
			ret = true;
			जाओ out;
		पूर्ण

		DRM_DEV_ERROR(&gpu->pdev->dev,
			"a630 SQE ucode is too old. Have version %x need at least %x\n",
			buf[0] & 0xfff, 0x190);
	पूर्ण  अन्यथा अणु
		/*
		 * a650 tier tarमाला_लो करोn't need whereami but still need to be
		 * equal to or newer than 0.95 क्रम other security fixes
		 */
		अगर (adreno_is_a650(adreno_gpu)) अणु
			अगर ((buf[0] & 0xfff) >= 0x095) अणु
				ret = true;
				जाओ out;
			पूर्ण

			DRM_DEV_ERROR(&gpu->pdev->dev,
				"a650 SQE ucode is too old. Have version %x need at least %x\n",
				buf[0] & 0xfff, 0x095);
		पूर्ण

		/*
		 * When a660 is added those tarमाला_लो should वापस true here
		 * since those have all the critical security fixes built in
		 * from the start
		 */
	पूर्ण
out:
	msm_gem_put_vaddr(obj);
	वापस ret;
पूर्ण

अटल पूर्णांक a6xx_ucode_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	अगर (!a6xx_gpu->sqe_bo) अणु
		a6xx_gpu->sqe_bo = adreno_fw_create_bo(gpu,
			adreno_gpu->fw[ADRENO_FW_SQE], &a6xx_gpu->sqe_iova);

		अगर (IS_ERR(a6xx_gpu->sqe_bo)) अणु
			पूर्णांक ret = PTR_ERR(a6xx_gpu->sqe_bo);

			a6xx_gpu->sqe_bo = शून्य;
			DRM_DEV_ERROR(&gpu->pdev->dev,
				"Could not allocate SQE ucode: %d\n", ret);

			वापस ret;
		पूर्ण

		msm_gem_object_set_name(a6xx_gpu->sqe_bo, "sqefw");
		अगर (!a6xx_ucode_check_version(a6xx_gpu, a6xx_gpu->sqe_bo)) अणु
			msm_gem_unpin_iova(a6xx_gpu->sqe_bo, gpu->aspace);
			drm_gem_object_put(a6xx_gpu->sqe_bo);

			a6xx_gpu->sqe_bo = शून्य;
			वापस -EPERM;
		पूर्ण
	पूर्ण

	gpu_ग_लिखो64(gpu, REG_A6XX_CP_SQE_INSTR_BASE_LO,
		REG_A6XX_CP_SQE_INSTR_BASE_HI, a6xx_gpu->sqe_iova);

	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_zap_shader_init(काष्ठा msm_gpu *gpu)
अणु
	अटल bool loaded;
	पूर्णांक ret;

	अगर (loaded)
		वापस 0;

	ret = adreno_zap_shader_load(gpu, GPU_PAS_ID);

	loaded = !ret;
	वापस ret;
पूर्ण

#घोषणा A6XX_INT_MASK (A6XX_RBBM_INT_0_MASK_CP_AHB_ERROR | \
	  A6XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNCFIFO_OVERFLOW | \
	  A6XX_RBBM_INT_0_MASK_CP_HW_ERROR | \
	  A6XX_RBBM_INT_0_MASK_CP_IB2 | \
	  A6XX_RBBM_INT_0_MASK_CP_IB1 | \
	  A6XX_RBBM_INT_0_MASK_CP_RB | \
	  A6XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS | \
	  A6XX_RBBM_INT_0_MASK_RBBM_ATB_BUS_OVERFLOW | \
	  A6XX_RBBM_INT_0_MASK_RBBM_HANG_DETECT | \
	  A6XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS | \
	  A6XX_RBBM_INT_0_MASK_UCHE_TRAP_INTR)

अटल पूर्णांक a6xx_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	पूर्णांक ret;

	/* Make sure the GMU keeps the GPU on जबतक we set it up */
	a6xx_gmu_set_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);

	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_SECVID_TSB_CNTL, 0);

	/*
	 * Disable the trusted memory range - we करोn't actually supported secure
	 * memory rendering at this poपूर्णांक in समय and we करोn't want to block off
	 * part of the भव memory space.
	 */
	gpu_ग_लिखो64(gpu, REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_LO,
		REG_A6XX_RBBM_SECVID_TSB_TRUSTED_BASE_HI, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_SECVID_TSB_TRUSTED_SIZE, 0x00000000);

	/* Turn on 64 bit addressing क्रम all blocks */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_VSC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_GRAS_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_RB_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_PC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_HLSQ_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_VFD_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_VPC_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_SP_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_TPL1_ADDR_MODE_CNTL, 0x1);
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_SECVID_TSB_ADDR_MODE_CNTL, 0x1);

	/* enable hardware घड़ीgating */
	a6xx_set_hwcg(gpu, true);

	/* VBIF/GBIF start*/
	अगर (adreno_is_a640(adreno_gpu) || adreno_is_a650(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A6XX_GBIF_QSB_SIDE0, 0x00071620);
		gpu_ग_लिखो(gpu, REG_A6XX_GBIF_QSB_SIDE1, 0x00071620);
		gpu_ग_लिखो(gpu, REG_A6XX_GBIF_QSB_SIDE2, 0x00071620);
		gpu_ग_लिखो(gpu, REG_A6XX_GBIF_QSB_SIDE3, 0x00071620);
		gpu_ग_लिखो(gpu, REG_A6XX_GBIF_QSB_SIDE3, 0x00071620);
		gpu_ग_लिखो(gpu, REG_A6XX_RBBM_GBIF_CLIENT_QOS_CNTL, 0x3);
	पूर्ण अन्यथा अणु
		gpu_ग_लिखो(gpu, REG_A6XX_RBBM_VBIF_CLIENT_QOS_CNTL, 0x3);
	पूर्ण

	अगर (adreno_is_a630(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A6XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000009);

	/* Make all blocks contribute to the GPU BUSY perf counter */
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_PERFCTR_GPU_BUSY_MASKED, 0xffffffff);

	/* Disable L2 bypass in the UCHE */
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_WRITE_RANGE_MAX_LO, 0xffffffc0);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_WRITE_RANGE_MAX_HI, 0x0001ffff);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_TRAP_BASE_LO, 0xfffff000);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_TRAP_BASE_HI, 0x0001ffff);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_WRITE_THRU_BASE_LO, 0xfffff000);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_WRITE_THRU_BASE_HI, 0x0001ffff);

	अगर (!adreno_is_a650(adreno_gpu)) अणु
		/* Set the GMEM VA range [0x100000:0x100000 + gpu->gmem - 1] */
		gpu_ग_लिखो64(gpu, REG_A6XX_UCHE_GMEM_RANGE_MIN_LO,
			REG_A6XX_UCHE_GMEM_RANGE_MIN_HI, 0x00100000);

		gpu_ग_लिखो64(gpu, REG_A6XX_UCHE_GMEM_RANGE_MAX_LO,
			REG_A6XX_UCHE_GMEM_RANGE_MAX_HI,
			0x00100000 + adreno_gpu->gmem - 1);
	पूर्ण

	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_FILTER_CNTL, 0x804);
	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_CACHE_WAYS, 0x4);

	अगर (adreno_is_a640(adreno_gpu) || adreno_is_a650(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A6XX_CP_ROQ_THRESHOLDS_2, 0x02000140);
	अन्यथा
		gpu_ग_लिखो(gpu, REG_A6XX_CP_ROQ_THRESHOLDS_2, 0x010000c0);
	gpu_ग_लिखो(gpu, REG_A6XX_CP_ROQ_THRESHOLDS_1, 0x8040362c);

	/* Setting the mem pool size */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_MEM_POOL_SIZE, 128);

	/* Setting the primFअगरo thresholds शेष values */
	अगर (adreno_is_a650(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A6XX_PC_DBG_ECO_CNTL, 0x00300000);
	अन्यथा अगर (adreno_is_a640(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A6XX_PC_DBG_ECO_CNTL, 0x00200000);
	अन्यथा
		gpu_ग_लिखो(gpu, REG_A6XX_PC_DBG_ECO_CNTL, (0x300 << 11));

	/* Set the AHB शेष slave response to "ERROR" */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_AHB_CNTL, 0x1);

	/* Turn on perक्रमmance counters */
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_PERFCTR_CNTL, 0x1);

	/* Select CP0 to always count cycles */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_PERFCTR_CP_SEL_0, PERF_CP_ALWAYS_COUNT);

	a6xx_set_ubwc_config(gpu);

	/* Enable fault detection */
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_INTERFACE_HANG_INT_CNTL,
		(1 << 30) | 0x1fffff);

	gpu_ग_लिखो(gpu, REG_A6XX_UCHE_CLIENT_PF, 1);

	/* Set weights क्रम bicubic filtering */
	अगर (adreno_is_a650(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_0, 0);
		gpu_ग_लिखो(gpu, REG_A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_1,
			0x3fe05ff4);
		gpu_ग_लिखो(gpu, REG_A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_2,
			0x3fa0ebee);
		gpu_ग_लिखो(gpu, REG_A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_3,
			0x3f5193ed);
		gpu_ग_लिखो(gpu, REG_A6XX_TPL1_BICUBIC_WEIGHTS_TABLE_4,
			0x3f0243f0);
	पूर्ण

	/* Protect रेजिस्टरs from the CP */
	a6xx_set_cp_protect(gpu);

	/* Enable expanded apriv क्रम tarमाला_लो that support it */
	अगर (gpu->hw_apriv) अणु
		gpu_ग_लिखो(gpu, REG_A6XX_CP_APRIV_CNTL,
			(1 << 6) | (1 << 5) | (1 << 3) | (1 << 2) | (1 << 1));
	पूर्ण

	/* Enable पूर्णांकerrupts */
	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_INT_0_MASK, A6XX_INT_MASK);

	ret = adreno_hw_init(gpu);
	अगर (ret)
		जाओ out;

	ret = a6xx_ucode_init(gpu);
	अगर (ret)
		जाओ out;

	/* Set the ringbuffer address */
	gpu_ग_लिखो64(gpu, REG_A6XX_CP_RB_BASE, REG_A6XX_CP_RB_BASE_HI,
		gpu->rb[0]->iova);

	/* Tarमाला_लो that support extended APRIV can use the RPTR shaकरोw from
	 * hardware but all the other ones need to disable the feature. Tarमाला_लो
	 * that support the WHERE_AM_I opcode can use that instead
	 */
	अगर (adreno_gpu->base.hw_apriv)
		gpu_ग_लिखो(gpu, REG_A6XX_CP_RB_CNTL, MSM_GPU_RB_CNTL_DEFAULT);
	अन्यथा
		gpu_ग_लिखो(gpu, REG_A6XX_CP_RB_CNTL,
			MSM_GPU_RB_CNTL_DEFAULT | AXXX_CP_RB_CNTL_NO_UPDATE);

	/*
	 * Expanded APRIV and tarमाला_लो that support WHERE_AM_I both need a
	 * privileged buffer to store the RPTR shaकरोw
	 */

	अगर (adreno_gpu->base.hw_apriv || a6xx_gpu->has_whereami) अणु
		अगर (!a6xx_gpu->shaकरोw_bo) अणु
			a6xx_gpu->shaकरोw = msm_gem_kernel_new_locked(gpu->dev,
				माप(u32) * gpu->nr_rings,
				MSM_BO_UNCACHED | MSM_BO_MAP_PRIV,
				gpu->aspace, &a6xx_gpu->shaकरोw_bo,
				&a6xx_gpu->shaकरोw_iova);

			अगर (IS_ERR(a6xx_gpu->shaकरोw))
				वापस PTR_ERR(a6xx_gpu->shaकरोw);
		पूर्ण

		gpu_ग_लिखो64(gpu, REG_A6XX_CP_RB_RPTR_ADDR_LO,
			REG_A6XX_CP_RB_RPTR_ADDR_HI,
			shaकरोwptr(a6xx_gpu, gpu->rb[0]));
	पूर्ण

	/* Always come up on rb 0 */
	a6xx_gpu->cur_ring = gpu->rb[0];

	a6xx_gpu->cur_ctx = शून्य;

	/* Enable the SQE_to start the CP engine */
	gpu_ग_लिखो(gpu, REG_A6XX_CP_SQE_CNTL, 1);

	ret = a6xx_cp_init(gpu);
	अगर (ret)
		जाओ out;

	/*
	 * Try to load a zap shader पूर्णांकo the secure world. If successful
	 * we can use the CP to चयन out of secure mode. If not then we
	 * have no resource but to try to चयन ourselves out manually. If we
	 * guessed wrong then access to the RBBM_SECVID_TRUST_CNTL रेजिस्टर will
	 * be blocked and a permissions violation will soon follow.
	 */
	ret = a6xx_zap_shader_init(gpu);
	अगर (!ret) अणु
		OUT_PKT7(gpu->rb[0], CP_SET_SECURE_MODE, 1);
		OUT_RING(gpu->rb[0], 0x00000000);

		a6xx_flush(gpu, gpu->rb[0]);
		अगर (!a6xx_idle(gpu, gpu->rb[0]))
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
		gpu_ग_लिखो(gpu, REG_A6XX_RBBM_SECVID_TRUST_CNTL, 0x0);
		ret = 0;
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

out:
	/*
	 * Tell the GMU that we are करोne touching the GPU and it can start घातer
	 * management
	 */
	a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);

	अगर (a6xx_gpu->gmu.legacy) अणु
		/* Take the GMU out of its special boot mode */
		a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_BOOT_SLUMBER);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम a6xx_dump(काष्ठा msm_gpu *gpu)
अणु
	DRM_DEV_INFO(&gpu->pdev->dev, "status:   %08x\n",
			gpu_पढ़ो(gpu, REG_A6XX_RBBM_STATUS));
	adreno_dump(gpu);
पूर्ण

#घोषणा VBIF_RESET_ACK_TIMEOUT	100
#घोषणा VBIF_RESET_ACK_MASK	0x00f0

अटल व्योम a6xx_recover(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	पूर्णांक i;

	adreno_dump_info(gpu);

	क्रम (i = 0; i < 8; i++)
		DRM_DEV_INFO(&gpu->pdev->dev, "CP_SCRATCH_REG%d: %u\n", i,
			gpu_पढ़ो(gpu, REG_A6XX_CP_SCRATCH_REG(i)));

	अगर (hang_debug)
		a6xx_dump(gpu);

	/*
	 * Turn off keep alive that might have been enabled by the hang
	 * पूर्णांकerrupt
	 */
	gmu_ग_लिखो(&a6xx_gpu->gmu, REG_A6XX_GMU_GMU_PWR_COL_KEEPALIVE, 0);

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->pm_resume(gpu);

	msm_gpu_hw_init(gpu);
पूर्ण

अटल पूर्णांक a6xx_fault_handler(व्योम *arg, अचिन्हित दीर्घ iova, पूर्णांक flags)
अणु
	काष्ठा msm_gpu *gpu = arg;

	pr_warn_ratelimited("*** gpu fault: iova=%08lx, flags=%d (%u,%u,%u,%u)\n",
			iova, flags,
			gpu_पढ़ो(gpu, REG_A6XX_CP_SCRATCH_REG(4)),
			gpu_पढ़ो(gpu, REG_A6XX_CP_SCRATCH_REG(5)),
			gpu_पढ़ो(gpu, REG_A6XX_CP_SCRATCH_REG(6)),
			gpu_पढ़ो(gpu, REG_A6XX_CP_SCRATCH_REG(7)));

	वापस -EFAULT;
पूर्ण

अटल व्योम a6xx_cp_hw_err_irq(काष्ठा msm_gpu *gpu)
अणु
	u32 status = gpu_पढ़ो(gpu, REG_A6XX_CP_INTERRUPT_STATUS);

	अगर (status & A6XX_CP_INT_CP_OPCODE_ERROR) अणु
		u32 val;

		gpu_ग_लिखो(gpu, REG_A6XX_CP_SQE_STAT_ADDR, 1);
		val = gpu_पढ़ो(gpu, REG_A6XX_CP_SQE_STAT_DATA);
		dev_err_ratelimited(&gpu->pdev->dev,
			"CP | opcode error | possible opcode=0x%8.8X\n",
			val);
	पूर्ण

	अगर (status & A6XX_CP_INT_CP_UCODE_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev,
			"CP ucode error interrupt\n");

	अगर (status & A6XX_CP_INT_CP_HW_FAULT_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP | HW fault | status=0x%8.8X\n",
			gpu_पढ़ो(gpu, REG_A6XX_CP_HW_FAULT));

	अगर (status & A6XX_CP_INT_CP_REGISTER_PROTECTION_ERROR) अणु
		u32 val = gpu_पढ़ो(gpu, REG_A6XX_CP_PROTECT_STATUS);

		dev_err_ratelimited(&gpu->pdev->dev,
			"CP | protected mode error | %s | addr=0x%8.8X | status=0x%8.8X\n",
			val & (1 << 20) ? "READ" : "WRITE",
			(val & 0x3ffff), val);
	पूर्ण

	अगर (status & A6XX_CP_INT_CP_AHB_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP AHB error interrupt\n");

	अगर (status & A6XX_CP_INT_CP_VSD_PARITY_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP VSD decoder parity error\n");

	अगर (status & A6XX_CP_INT_CP_ILLEGAL_INSTR_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP illegal instruction error\n");

पूर्ण

अटल व्योम a6xx_fault_detect_irq(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा msm_ringbuffer *ring = gpu->funcs->active_ring(gpu);

	/*
	 * Force the GPU to stay on until after we finish
	 * collecting inक्रमmation
	 */
	gmu_ग_लिखो(&a6xx_gpu->gmu, REG_A6XX_GMU_GMU_PWR_COL_KEEPALIVE, 1);

	DRM_DEV_ERROR(&gpu->pdev->dev,
		"gpu fault ring %d fence %x status %8.8X rb %4.4x/%4.4x ib1 %16.16llX/%4.4x ib2 %16.16llX/%4.4x\n",
		ring ? ring->id : -1, ring ? ring->seqno : 0,
		gpu_पढ़ो(gpu, REG_A6XX_RBBM_STATUS),
		gpu_पढ़ो(gpu, REG_A6XX_CP_RB_RPTR),
		gpu_पढ़ो(gpu, REG_A6XX_CP_RB_WPTR),
		gpu_पढ़ो64(gpu, REG_A6XX_CP_IB1_BASE, REG_A6XX_CP_IB1_BASE_HI),
		gpu_पढ़ो(gpu, REG_A6XX_CP_IB1_REM_SIZE),
		gpu_पढ़ो64(gpu, REG_A6XX_CP_IB2_BASE, REG_A6XX_CP_IB2_BASE_HI),
		gpu_पढ़ो(gpu, REG_A6XX_CP_IB2_REM_SIZE));

	/* Turn off the hangcheck समयr to keep it from bothering us */
	del_समयr(&gpu->hangcheck_समयr);

	kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
पूर्ण

अटल irqवापस_t a6xx_irq(काष्ठा msm_gpu *gpu)
अणु
	u32 status = gpu_पढ़ो(gpu, REG_A6XX_RBBM_INT_0_STATUS);

	gpu_ग_लिखो(gpu, REG_A6XX_RBBM_INT_CLEAR_CMD, status);

	अगर (status & A6XX_RBBM_INT_0_MASK_RBBM_HANG_DETECT)
		a6xx_fault_detect_irq(gpu);

	अगर (status & A6XX_RBBM_INT_0_MASK_CP_AHB_ERROR)
		dev_err_ratelimited(&gpu->pdev->dev, "CP | AHB bus error\n");

	अगर (status & A6XX_RBBM_INT_0_MASK_CP_HW_ERROR)
		a6xx_cp_hw_err_irq(gpu);

	अगर (status & A6XX_RBBM_INT_0_MASK_RBBM_ATB_ASYNCFIFO_OVERFLOW)
		dev_err_ratelimited(&gpu->pdev->dev, "RBBM | ATB ASYNC overflow\n");

	अगर (status & A6XX_RBBM_INT_0_MASK_RBBM_ATB_BUS_OVERFLOW)
		dev_err_ratelimited(&gpu->pdev->dev, "RBBM | ATB bus overflow\n");

	अगर (status & A6XX_RBBM_INT_0_MASK_UCHE_OOB_ACCESS)
		dev_err_ratelimited(&gpu->pdev->dev, "UCHE | Out of bounds access\n");

	अगर (status & A6XX_RBBM_INT_0_MASK_CP_CACHE_FLUSH_TS)
		msm_gpu_retire(gpu);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम a6xx_llc_rmw(काष्ठा a6xx_gpu *a6xx_gpu, u32 reg, u32 mask, u32 or)
अणु
	वापस msm_rmw(a6xx_gpu->llc_mmio + (reg << 2), mask, or);
पूर्ण

अटल व्योम a6xx_llc_ग_लिखो(काष्ठा a6xx_gpu *a6xx_gpu, u32 reg, u32 value)
अणु
	वापस msm_ग_लिखोl(value, a6xx_gpu->llc_mmio + (reg << 2));
पूर्ण

अटल व्योम a6xx_llc_deactivate(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	llcc_slice_deactivate(a6xx_gpu->llc_slice);
	llcc_slice_deactivate(a6xx_gpu->htw_llc_slice);
पूर्ण

अटल व्योम a6xx_llc_activate(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	u32 cntl1_regval = 0;

	अगर (IS_ERR(a6xx_gpu->llc_mmio))
		वापस;

	अगर (!llcc_slice_activate(a6xx_gpu->llc_slice)) अणु
		u32 gpu_scid = llcc_get_slice_id(a6xx_gpu->llc_slice);

		gpu_scid &= 0x1f;
		cntl1_regval = (gpu_scid << 0) | (gpu_scid << 5) | (gpu_scid << 10) |
			       (gpu_scid << 15) | (gpu_scid << 20);
	पूर्ण

	/*
	 * For tarमाला_लो with a MMU500, activate the slice but करोn't program the
	 * रेजिस्टर.  The XBL will take care of that.
	 */
	अगर (!llcc_slice_activate(a6xx_gpu->htw_llc_slice)) अणु
		अगर (!a6xx_gpu->have_mmu500) अणु
			u32 gpuhtw_scid = llcc_get_slice_id(a6xx_gpu->htw_llc_slice);

			gpuhtw_scid &= 0x1f;
			cntl1_regval |= FIELD_PREP(GENMASK(29, 25), gpuhtw_scid);
		पूर्ण
	पूर्ण

	अगर (cntl1_regval) अणु
		/*
		 * Program the slice IDs क्रम the various GPU blocks and GPU MMU
		 * pagetables
		 */
		अगर (a6xx_gpu->have_mmu500)
			gpu_rmw(gpu, REG_A6XX_GBIF_SCACHE_CNTL1, GENMASK(24, 0),
				cntl1_regval);
		अन्यथा अणु
			a6xx_llc_ग_लिखो(a6xx_gpu,
				REG_A6XX_CX_MISC_SYSTEM_CACHE_CNTL_1, cntl1_regval);

			/*
			 * Program cacheability overrides to not allocate cache
			 * lines on a ग_लिखो miss
			 */
			a6xx_llc_rmw(a6xx_gpu,
				REG_A6XX_CX_MISC_SYSTEM_CACHE_CNTL_0, 0xF, 0x03);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम a6xx_llc_slices_destroy(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	llcc_slice_putd(a6xx_gpu->llc_slice);
	llcc_slice_putd(a6xx_gpu->htw_llc_slice);
पूर्ण

अटल व्योम a6xx_llc_slices_init(काष्ठा platक्रमm_device *pdev,
		काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	काष्ठा device_node *phandle;

	/*
	 * There is a dअगरferent programming path क्रम tarमाला_लो with an mmu500
	 * attached, so detect अगर that is the हाल
	 */
	phandle = of_parse_phandle(pdev->dev.of_node, "iommus", 0);
	a6xx_gpu->have_mmu500 = (phandle &&
		of_device_is_compatible(phandle, "arm,mmu-500"));
	of_node_put(phandle);

	अगर (a6xx_gpu->have_mmu500)
		a6xx_gpu->llc_mmio = शून्य;
	अन्यथा
		a6xx_gpu->llc_mmio = msm_ioremap(pdev, "cx_mem", "gpu_cx");

	a6xx_gpu->llc_slice = llcc_slice_getd(LLCC_GPU);
	a6xx_gpu->htw_llc_slice = llcc_slice_getd(LLCC_GPUHTW);

	अगर (IS_ERR_OR_शून्य(a6xx_gpu->llc_slice) && IS_ERR_OR_शून्य(a6xx_gpu->htw_llc_slice))
		a6xx_gpu->llc_mmio = ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक a6xx_pm_resume(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	पूर्णांक ret;

	gpu->needs_hw_init = true;

	trace_msm_gpu_resume(0);

	ret = a6xx_gmu_resume(a6xx_gpu);
	अगर (ret)
		वापस ret;

	msm_gpu_resume_devfreq(gpu);

	a6xx_llc_activate(a6xx_gpu);

	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_pm_suspend(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	पूर्णांक i, ret;

	trace_msm_gpu_suspend(0);

	a6xx_llc_deactivate(a6xx_gpu);

	devfreq_suspend_device(gpu->devfreq.devfreq);

	ret = a6xx_gmu_stop(a6xx_gpu);
	अगर (ret)
		वापस ret;

	अगर (a6xx_gpu->shaकरोw_bo)
		क्रम (i = 0; i < gpu->nr_rings; i++)
			a6xx_gpu->shaकरोw[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_get_बारtamp(काष्ठा msm_gpu *gpu, uपूर्णांक64_t *value)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	अटल DEFINE_MUTEX(perfcounter_oob);

	mutex_lock(&perfcounter_oob);

	/* Force the GPU घातer on so we can पढ़ो this रेजिस्टर */
	a6xx_gmu_set_oob(&a6xx_gpu->gmu, GMU_OOB_PERFCOUNTER_SET);

	*value = gpu_पढ़ो64(gpu, REG_A6XX_CP_ALWAYS_ON_COUNTER_LO,
		REG_A6XX_CP_ALWAYS_ON_COUNTER_HI);

	a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_PERFCOUNTER_SET);
	mutex_unlock(&perfcounter_oob);
	वापस 0;
पूर्ण

अटल काष्ठा msm_ringbuffer *a6xx_active_ring(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	वापस a6xx_gpu->cur_ring;
पूर्ण

अटल व्योम a6xx_destroy(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	अगर (a6xx_gpu->sqe_bo) अणु
		msm_gem_unpin_iova(a6xx_gpu->sqe_bo, gpu->aspace);
		drm_gem_object_put(a6xx_gpu->sqe_bo);
	पूर्ण

	अगर (a6xx_gpu->shaकरोw_bo) अणु
		msm_gem_unpin_iova(a6xx_gpu->shaकरोw_bo, gpu->aspace);
		drm_gem_object_put(a6xx_gpu->shaकरोw_bo);
	पूर्ण

	a6xx_llc_slices_destroy(a6xx_gpu);

	a6xx_gmu_हटाओ(a6xx_gpu);

	adreno_gpu_cleanup(adreno_gpu);

	अगर (a6xx_gpu->opp_table)
		dev_pm_opp_put_supported_hw(a6xx_gpu->opp_table);

	kमुक्त(a6xx_gpu);
पूर्ण

अटल अचिन्हित दीर्घ a6xx_gpu_busy(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	u64 busy_cycles, busy_समय;


	/* Only पढ़ो the gpu busy अगर the hardware is alपढ़ोy active */
	अगर (pm_runसमय_get_अगर_in_use(a6xx_gpu->gmu.dev) == 0)
		वापस 0;

	busy_cycles = gmu_पढ़ो64(&a6xx_gpu->gmu,
			REG_A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_0_L,
			REG_A6XX_GMU_CX_GMU_POWER_COUNTER_XOCLK_0_H);

	busy_समय = (busy_cycles - gpu->devfreq.busy_cycles) * 10;
	करो_भाग(busy_समय, 192);

	gpu->devfreq.busy_cycles = busy_cycles;

	pm_runसमय_put(a6xx_gpu->gmu.dev);

	अगर (WARN_ON(busy_समय > ~0LU))
		वापस ~0LU;

	वापस (अचिन्हित दीर्घ)busy_समय;
पूर्ण

अटल काष्ठा msm_gem_address_space *
a6xx_create_address_space(काष्ठा msm_gpu *gpu, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा iommu_करोमुख्य *iommu;
	काष्ठा msm_mmu *mmu;
	काष्ठा msm_gem_address_space *aspace;
	u64 start, size;

	iommu = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!iommu)
		वापस शून्य;

	/*
	 * This allows GPU to set the bus attributes required to use प्रणाली
	 * cache on behalf of the iommu page table walker.
	 */
	अगर (!IS_ERR_OR_शून्य(a6xx_gpu->htw_llc_slice))
		adreno_set_llc_attributes(iommu);

	mmu = msm_iommu_new(&pdev->dev, iommu);
	अगर (IS_ERR(mmu)) अणु
		iommu_करोमुख्य_मुक्त(iommu);
		वापस ERR_CAST(mmu);
	पूर्ण

	/*
	 * Use the aperture start or SZ_16M, whichever is greater. This will
	 * ensure that we align with the allocated pagetable range जबतक still
	 * allowing room in the lower 32 bits क्रम GMEM and whatnot
	 */
	start = max_t(u64, SZ_16M, iommu->geometry.aperture_start);
	size = iommu->geometry.aperture_end - start + 1;

	aspace = msm_gem_address_space_create(mmu, "gpu",
		start & GENMASK_ULL(48, 0), size);

	अगर (IS_ERR(aspace) && !IS_ERR(mmu))
		mmu->funcs->destroy(mmu);

	वापस aspace;
पूर्ण

अटल काष्ठा msm_gem_address_space *
a6xx_create_निजी_address_space(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_mmu *mmu;

	mmu = msm_iommu_pagetable_create(gpu->aspace->mmu);

	अगर (IS_ERR(mmu))
		वापस ERR_CAST(mmu);

	वापस msm_gem_address_space_create(mmu,
		"gpu", 0x100000000ULL, 0x1ffffffffULL);
पूर्ण

अटल uपूर्णांक32_t a6xx_get_rptr(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	अगर (adreno_gpu->base.hw_apriv || a6xx_gpu->has_whereami)
		वापस a6xx_gpu->shaकरोw[ring->id];

	वापस ring->memptrs->rptr = gpu_पढ़ो(gpu, REG_A6XX_CP_RB_RPTR);
पूर्ण

अटल u32 a618_get_speed_bin(u32 fuse)
अणु
	अगर (fuse == 0)
		वापस 0;
	अन्यथा अगर (fuse == 169)
		वापस 1;
	अन्यथा अगर (fuse == 174)
		वापस 2;

	वापस अच_पूर्णांक_उच्च;
पूर्ण

अटल u32 fuse_to_supp_hw(काष्ठा device *dev, u32 revn, u32 fuse)
अणु
	u32 val = अच_पूर्णांक_उच्च;

	अगर (revn == 618)
		val = a618_get_speed_bin(fuse);

	अगर (val == अच_पूर्णांक_उच्च) अणु
		DRM_DEV_ERROR(dev,
			"missing support for speed-bin: %u. Some OPPs may not be supported by hardware",
			fuse);
		वापस अच_पूर्णांक_उच्च;
	पूर्ण

	वापस (1 << val);
पूर्ण

अटल पूर्णांक a6xx_set_supported_hw(काष्ठा device *dev, काष्ठा a6xx_gpu *a6xx_gpu,
		u32 revn)
अणु
	काष्ठा opp_table *opp_table;
	u32 supp_hw = अच_पूर्णांक_उच्च;
	u16 speedbin;
	पूर्णांक ret;

	ret = nvmem_cell_पढ़ो_u16(dev, "speed_bin", &speedbin);
	/*
	 * -ENOENT means that the platक्रमm करोesn't support speedbin which is
	 * fine
	 */
	अगर (ret == -ENOENT) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (ret) अणु
		DRM_DEV_ERROR(dev,
			      "failed to read speed-bin (%d). Some OPPs may not be supported by hardware",
			      ret);
		जाओ करोne;
	पूर्ण
	speedbin = le16_to_cpu(speedbin);

	supp_hw = fuse_to_supp_hw(dev, revn, speedbin);

करोne:
	opp_table = dev_pm_opp_set_supported_hw(dev, &supp_hw, 1);
	अगर (IS_ERR(opp_table))
		वापस PTR_ERR(opp_table);

	a6xx_gpu->opp_table = opp_table;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा adreno_gpu_funcs funcs = अणु
	.base = अणु
		.get_param = adreno_get_param,
		.hw_init = a6xx_hw_init,
		.pm_suspend = a6xx_pm_suspend,
		.pm_resume = a6xx_pm_resume,
		.recover = a6xx_recover,
		.submit = a6xx_submit,
		.active_ring = a6xx_active_ring,
		.irq = a6xx_irq,
		.destroy = a6xx_destroy,
#अगर defined(CONFIG_DRM_MSM_GPU_STATE)
		.show = a6xx_show,
#पूर्ण_अगर
		.gpu_busy = a6xx_gpu_busy,
		.gpu_get_freq = a6xx_gmu_get_freq,
		.gpu_set_freq = a6xx_gmu_set_freq,
#अगर defined(CONFIG_DRM_MSM_GPU_STATE)
		.gpu_state_get = a6xx_gpu_state_get,
		.gpu_state_put = a6xx_gpu_state_put,
#पूर्ण_अगर
		.create_address_space = a6xx_create_address_space,
		.create_निजी_address_space = a6xx_create_निजी_address_space,
		.get_rptr = a6xx_get_rptr,
	पूर्ण,
	.get_बारtamp = a6xx_get_बारtamp,
पूर्ण;

काष्ठा msm_gpu *a6xx_gpu_init(काष्ठा drm_device *dev)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	काष्ठा adreno_platक्रमm_config *config = pdev->dev.platक्रमm_data;
	स्थिर काष्ठा adreno_info *info;
	काष्ठा device_node *node;
	काष्ठा a6xx_gpu *a6xx_gpu;
	काष्ठा adreno_gpu *adreno_gpu;
	काष्ठा msm_gpu *gpu;
	पूर्णांक ret;

	a6xx_gpu = kzalloc(माप(*a6xx_gpu), GFP_KERNEL);
	अगर (!a6xx_gpu)
		वापस ERR_PTR(-ENOMEM);

	adreno_gpu = &a6xx_gpu->base;
	gpu = &adreno_gpu->base;

	adreno_gpu->रेजिस्टरs = शून्य;

	/*
	 * We need to know the platक्रमm type beक्रमe calling पूर्णांकo adreno_gpu_init
	 * so that the hw_apriv flag can be correctly set. Snoop पूर्णांकo the info
	 * and grab the revision number
	 */
	info = adreno_info(config->rev);

	अगर (info && info->revn == 650)
		adreno_gpu->base.hw_apriv = true;

	a6xx_llc_slices_init(pdev, a6xx_gpu);

	ret = a6xx_set_supported_hw(&pdev->dev, a6xx_gpu, info->revn);
	अगर (ret) अणु
		a6xx_destroy(&(a6xx_gpu->base.base));
		वापस ERR_PTR(ret);
	पूर्ण

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	अगर (ret) अणु
		a6xx_destroy(&(a6xx_gpu->base.base));
		वापस ERR_PTR(ret);
	पूर्ण

	/* Check अगर there is a GMU phandle and set it up */
	node = of_parse_phandle(pdev->dev.of_node, "qcom,gmu", 0);

	/* FIXME: How करो we gracefully handle this? */
	BUG_ON(!node);

	ret = a6xx_gmu_init(a6xx_gpu, node);
	अगर (ret) अणु
		a6xx_destroy(&(a6xx_gpu->base.base));
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (gpu->aspace)
		msm_mmu_set_fault_handler(gpu->aspace->mmu, gpu,
				a6xx_fault_handler);

	वापस gpu;
पूर्ण
