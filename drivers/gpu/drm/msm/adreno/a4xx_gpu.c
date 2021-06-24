<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2014 The Linux Foundation. All rights reserved.
 */
#समावेश "a4xx_gpu.h"

#घोषणा A4XX_INT0_MASK \
	(A4XX_INT0_RBBM_AHB_ERROR |        \
	 A4XX_INT0_RBBM_ATB_BUS_OVERFLOW | \
	 A4XX_INT0_CP_T0_PACKET_IN_IB |    \
	 A4XX_INT0_CP_OPCODE_ERROR |       \
	 A4XX_INT0_CP_RESERVED_BIT_ERROR | \
	 A4XX_INT0_CP_HW_FAULT |           \
	 A4XX_INT0_CP_IB1_INT |            \
	 A4XX_INT0_CP_IB2_INT |            \
	 A4XX_INT0_CP_RB_INT |             \
	 A4XX_INT0_CP_REG_PROTECT_FAULT |  \
	 A4XX_INT0_CP_AHB_ERROR_HALT |     \
	 A4XX_INT0_CACHE_FLUSH_TS |        \
	 A4XX_INT0_UCHE_OOB_ACCESS)

बाह्य bool hang_debug;
अटल व्योम a4xx_dump(काष्ठा msm_gpu *gpu);
अटल bool a4xx_idle(काष्ठा msm_gpu *gpu);

अटल व्योम a4xx_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
अणु
	काष्ठा msm_drm_निजी *priv = gpu->dev->dev_निजी;
	काष्ठा msm_ringbuffer *ring = submit->ring;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < submit->nr_cmds; i++) अणु
		चयन (submit->cmd[i].type) अणु
		हाल MSM_SUBMIT_CMD_IB_TARGET_BUF:
			/* ignore IB-tarमाला_लो */
			अवरोध;
		हाल MSM_SUBMIT_CMD_CTX_RESTORE_BUF:
			/* ignore अगर there has not been a ctx चयन: */
			अगर (priv->lastctx == submit->queue->ctx)
				अवरोध;
			fallthrough;
		हाल MSM_SUBMIT_CMD_BUF:
			OUT_PKT3(ring, CP_INसूचीECT_BUFFER_PFE, 2);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			OUT_PKT2(ring);
			अवरोध;
		पूर्ण
	पूर्ण

	OUT_PKT0(ring, REG_AXXX_CP_SCRATCH_REG2, 1);
	OUT_RING(ring, submit->seqno);

	/* Flush HLSQ lazy updates to make sure there is nothing
	 * pending क्रम indirect loads after the बारtamp has
	 * passed:
	 */
	OUT_PKT3(ring, CP_EVENT_WRITE, 1);
	OUT_RING(ring, HLSQ_FLUSH);

	/* रुको क्रम idle beक्रमe cache flush/पूर्णांकerrupt */
	OUT_PKT3(ring, CP_WAIT_FOR_IDLE, 1);
	OUT_RING(ring, 0x00000000);

	/* BIT(31) of CACHE_FLUSH_TS triggers CACHE_FLUSH_TS IRQ from GPU */
	OUT_PKT3(ring, CP_EVENT_WRITE, 3);
	OUT_RING(ring, CACHE_FLUSH_TS | BIT(31));
	OUT_RING(ring, rbmemptr(ring, fence));
	OUT_RING(ring, submit->seqno);

	adreno_flush(gpu, ring, REG_A4XX_CP_RB_WPTR);
पूर्ण

/*
 * a4xx_enable_hwcg() - Program the घड़ी control रेजिस्टरs
 * @device: The adreno device poपूर्णांकer
 */
अटल व्योम a4xx_enable_hwcg(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_TP(i), 0x02222202);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2_TP(i), 0x00002222);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_TP(i), 0x0E739CE7);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_TP(i), 0x00111111);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_SP(i), 0x22222222);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2_SP(i), 0x00222222);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_SP(i), 0x00000104);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_SP(i), 0x00000081);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_UCHE, 0x22222222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2_UCHE, 0x02222222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL3_UCHE, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL4_UCHE, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_UCHE, 0x00004444);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_UCHE, 0x00001112);
	क्रम (i = 0; i < 4; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_RB(i), 0x22222222);

	/* Disable L1 घड़ीing in A420 due to CCU issues with it */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (adreno_is_a420(adreno_gpu)) अणु
			gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2_RB(i),
					0x00002020);
		पूर्ण अन्यथा अणु
			gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2_RB(i),
					0x00022020);
		पूर्ण
	पूर्ण

	/* No CCU क्रम A405 */
	अगर (!adreno_is_a405(adreno_gpu)) अणु
		क्रम (i = 0; i < 4; i++) अणु
			gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_MARB_CCU(i),
					0x00000922);
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_RB_MARB_CCU(i),
					0x00000000);
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_RB_MARB_CCU_L1(i),
					0x00000001);
		पूर्ण
	पूर्ण

	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_MODE_GPC, 0x02222222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_GPC, 0x04100104);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_GPC, 0x00022222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_COM_DCOM, 0x00000022);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_COM_DCOM, 0x0000010F);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_COM_DCOM, 0x00000022);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_TSE_RAS_RBBM, 0x00222222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_TSE_RAS_RBBM, 0x00004104);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_TSE_RAS_RBBM, 0x00000222);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL_HLSQ , 0x00000000);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_HYST_HLSQ, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_HLSQ, 0x00220000);
	/* Early A430's have a timing issue with SP/TP घातer collapse;
	   disabling HW घड़ी gating prevents it. */
	अगर (adreno_is_a430(adreno_gpu) && adreno_gpu->rev.patchid < 2)
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL, 0);
	अन्यथा
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL, 0xAAAAAAAA);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_CTL2, 0);
पूर्ण


अटल bool a4xx_me_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT3(ring, CP_ME_INIT, 17);
	OUT_RING(ring, 0x000003f7);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000080);
	OUT_RING(ring, 0x00000100);
	OUT_RING(ring, 0x00000180);
	OUT_RING(ring, 0x00006600);
	OUT_RING(ring, 0x00000150);
	OUT_RING(ring, 0x0000014e);
	OUT_RING(ring, 0x00000154);
	OUT_RING(ring, 0x00000001);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);
	OUT_RING(ring, 0x00000000);

	adreno_flush(gpu, ring, REG_A4XX_CP_RB_WPTR);
	वापस a4xx_idle(gpu);
पूर्ण

अटल पूर्णांक a4xx_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a4xx_gpu *a4xx_gpu = to_a4xx_gpu(adreno_gpu);
	uपूर्णांक32_t *ptr, len;
	पूर्णांक i, ret;

	अगर (adreno_is_a405(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_ROUND_ROBIN_QOS_ARB, 0x00000003);
	पूर्ण अन्यथा अगर (adreno_is_a420(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_ABIT_SORT, 0x0001001F);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_ABIT_SORT_CONF, 0x000000A4);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000001);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_RD_LIM_CONF0, 0x18181818);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_RD_LIM_CONF1, 0x00000018);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_WR_LIM_CONF0, 0x18181818);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_WR_LIM_CONF1, 0x00000018);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_ROUND_ROBIN_QOS_ARB, 0x00000003);
	पूर्ण अन्यथा अगर (adreno_is_a430(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_GATE_OFF_WRREQ_EN, 0x00000001);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_RD_LIM_CONF0, 0x18181818);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_RD_LIM_CONF1, 0x00000018);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_WR_LIM_CONF0, 0x18181818);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_IN_WR_LIM_CONF1, 0x00000018);
		gpu_ग_लिखो(gpu, REG_A4XX_VBIF_ROUND_ROBIN_QOS_ARB, 0x00000003);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	/* Make all blocks contribute to the GPU BUSY perf counter */
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_GPU_BUSY_MASKED, 0xffffffff);

	/* Tune the hystersis counters क्रम SP and CP idle detection */
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_SP_HYST_CNT, 0x10);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_WAIT_IDLE_CLOCKS_CTL, 0x10);

	अगर (adreno_is_a430(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_WAIT_IDLE_CLOCKS_CTL2, 0x30);
	पूर्ण

	 /* Enable the RBBM error reporting bits */
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_AHB_CTL0, 0x00000001);

	/* Enable AHB error reporting*/
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_AHB_CTL1, 0xa6ffffff);

	/* Enable घातer counters*/
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_RBBM_CTL, 0x00000030);

	/*
	 * Turn on hang detection - this spews a lot of useful inक्रमmation
	 * पूर्णांकo the RBBM रेजिस्टरs on a hang:
	 */
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_INTERFACE_HANG_INT_CTL,
			(1 << 30) | 0xFFFF);

	gpu_ग_लिखो(gpu, REG_A4XX_RB_GMEM_BASE_ADDR,
			(अचिन्हित पूर्णांक)(a4xx_gpu->ocmem.base >> 14));

	/* Turn on perक्रमmance counters: */
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_PERFCTR_CTL, 0x01);

	/* use the first CP counter क्रम बारtamp queries.. userspace may set
	 * this as well but it selects the same counter/countable:
	 */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PERFCTR_CP_SEL_0, CP_ALWAYS_COUNT);

	अगर (adreno_is_a430(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A4XX_UCHE_CACHE_WAYS_VFD, 0x07);

	/* Disable L2 bypass to aव्योम UCHE out of bounds errors */
	gpu_ग_लिखो(gpu, REG_A4XX_UCHE_TRAP_BASE_LO, 0xffff0000);
	gpu_ग_लिखो(gpu, REG_A4XX_UCHE_TRAP_BASE_HI, 0xffff0000);

	gpu_ग_लिखो(gpu, REG_A4XX_CP_DEBUG, (1 << 25) |
			(adreno_is_a420(adreno_gpu) ? (1 << 29) : 0));

	/* On A430 enable SP regfile sleep क्रम घातer savings */
	/* TODO करोwnstream करोes this क्रम !420, so maybe applies क्रम 405 too? */
	अगर (!adreno_is_a420(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_SP_REGखाता_SLEEP_CNTL_0,
			0x00000441);
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_SP_REGखाता_SLEEP_CNTL_1,
			0x00000441);
	पूर्ण

	a4xx_enable_hwcg(gpu);

	/*
	 * For A420 set RBBM_CLOCK_DELAY_HLSQ.CGC_HLSQ_TP_EARLY_CYC >= 2
	 * due to timing issue with HLSQ_TP_CLK_EN
	 */
	अगर (adreno_is_a420(adreno_gpu)) अणु
		अचिन्हित पूर्णांक val;
		val = gpu_पढ़ो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_HLSQ);
		val &= ~A4XX_CGC_HLSQ_EARLY_CYC__MASK;
		val |= 2 << A4XX_CGC_HLSQ_EARLY_CYC__SHIFT;
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_CLOCK_DELAY_HLSQ, val);
	पूर्ण

	/* setup access protection: */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT_CTRL, 0x00000007);

	/* RBBM रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(0), 0x62000010);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(1), 0x63000020);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(2), 0x64000040);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(3), 0x65000080);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(4), 0x66000100);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(5), 0x64000200);

	/* CP रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(6), 0x67000800);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(7), 0x64001600);


	/* RB रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(8), 0x60003300);

	/* HLSQ रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(9), 0x60003800);

	/* VPC रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(10), 0x61003980);

	/* SMMU रेजिस्टरs */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_PROTECT(11), 0x6e010000);

	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_INT_0_MASK, A4XX_INT0_MASK);

	ret = adreno_hw_init(gpu);
	अगर (ret)
		वापस ret;

	/*
	 * Use the शेष ringbuffer size and block size but disable the RPTR
	 * shaकरोw
	 */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_RB_CNTL,
		MSM_GPU_RB_CNTL_DEFAULT | AXXX_CP_RB_CNTL_NO_UPDATE);

	/* Set the ringbuffer address */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_RB_BASE, lower_32_bits(gpu->rb[0]->iova));

	/* Load PM4: */
	ptr = (uपूर्णांक32_t *)(adreno_gpu->fw[ADRENO_FW_PM4]->data);
	len = adreno_gpu->fw[ADRENO_FW_PM4]->size / 4;
	DBG("loading PM4 ucode version: %u", ptr[0]);
	gpu_ग_लिखो(gpu, REG_A4XX_CP_ME_RAM_WADDR, 0);
	क्रम (i = 1; i < len; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_CP_ME_RAM_DATA, ptr[i]);

	/* Load PFP: */
	ptr = (uपूर्णांक32_t *)(adreno_gpu->fw[ADRENO_FW_PFP]->data);
	len = adreno_gpu->fw[ADRENO_FW_PFP]->size / 4;
	DBG("loading PFP ucode version: %u", ptr[0]);

	gpu_ग_लिखो(gpu, REG_A4XX_CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 1; i < len; i++)
		gpu_ग_लिखो(gpu, REG_A4XX_CP_PFP_UCODE_DATA, ptr[i]);

	/* clear ME_HALT to start micro engine */
	gpu_ग_लिखो(gpu, REG_A4XX_CP_ME_CNTL, 0);

	वापस a4xx_me_init(gpu) ? 0 : -EINVAL;
पूर्ण

अटल व्योम a4xx_recover(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	adreno_dump_info(gpu);

	क्रम (i = 0; i < 8; i++) अणु
		prपूर्णांकk("CP_SCRATCH_REG%d: %u\n", i,
			gpu_पढ़ो(gpu, REG_AXXX_CP_SCRATCH_REG0 + i));
	पूर्ण

	/* dump रेजिस्टरs beक्रमe resetting gpu, अगर enabled: */
	अगर (hang_debug)
		a4xx_dump(gpu);

	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_SW_RESET_CMD, 1);
	gpu_पढ़ो(gpu, REG_A4XX_RBBM_SW_RESET_CMD);
	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_SW_RESET_CMD, 0);
	adreno_recover(gpu);
पूर्ण

अटल व्योम a4xx_destroy(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a4xx_gpu *a4xx_gpu = to_a4xx_gpu(adreno_gpu);

	DBG("%s", gpu->name);

	adreno_gpu_cleanup(adreno_gpu);

	adreno_gpu_ocmem_cleanup(&a4xx_gpu->ocmem);

	kमुक्त(a4xx_gpu);
पूर्ण

अटल bool a4xx_idle(काष्ठा msm_gpu *gpu)
अणु
	/* रुको क्रम ringbuffer to drain: */
	अगर (!adreno_idle(gpu, gpu->rb[0]))
		वापस false;

	/* then रुको क्रम GPU to finish: */
	अगर (spin_until(!(gpu_पढ़ो(gpu, REG_A4XX_RBBM_STATUS) &
					A4XX_RBBM_STATUS_GPU_BUSY))) अणु
		DRM_ERROR("%s: timeout waiting for GPU to idle!\n", gpu->name);
		/* TODO maybe we need to reset GPU here to recover from hang? */
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t a4xx_irq(काष्ठा msm_gpu *gpu)
अणु
	uपूर्णांक32_t status;

	status = gpu_पढ़ो(gpu, REG_A4XX_RBBM_INT_0_STATUS);
	DBG("%s: Int status %08x", gpu->name, status);

	अगर (status & A4XX_INT0_CP_REG_PROTECT_FAULT) अणु
		uपूर्णांक32_t reg = gpu_पढ़ो(gpu, REG_A4XX_CP_PROTECT_STATUS);
		prपूर्णांकk("CP | Protected mode error| %s | addr=%x\n",
			reg & (1 << 24) ? "WRITE" : "READ",
			(reg & 0xFFFFF) >> 2);
	पूर्ण

	gpu_ग_लिखो(gpu, REG_A4XX_RBBM_INT_CLEAR_CMD, status);

	msm_gpu_retire(gpu);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक a4xx_रेजिस्टरs[] = अणु
	/* RBBM */
	0x0000, 0x0002, 0x0004, 0x0021, 0x0023, 0x0024, 0x0026, 0x0026,
	0x0028, 0x002B, 0x002E, 0x0034, 0x0037, 0x0044, 0x0047, 0x0066,
	0x0068, 0x0095, 0x009C, 0x0170, 0x0174, 0x01AF,
	/* CP */
	0x0200, 0x0233, 0x0240, 0x0250, 0x04C0, 0x04DD, 0x0500, 0x050B,
	0x0578, 0x058F,
	/* VSC */
	0x0C00, 0x0C03, 0x0C08, 0x0C41, 0x0C50, 0x0C51,
	/* GRAS */
	0x0C80, 0x0C81, 0x0C88, 0x0C8F,
	/* RB */
	0x0CC0, 0x0CC0, 0x0CC4, 0x0CD2,
	/* PC */
	0x0D00, 0x0D0C, 0x0D10, 0x0D17, 0x0D20, 0x0D23,
	/* VFD */
	0x0E40, 0x0E4A,
	/* VPC */
	0x0E60, 0x0E61, 0x0E63, 0x0E68,
	/* UCHE */
	0x0E80, 0x0E84, 0x0E88, 0x0E95,
	/* VMIDMT */
	0x1000, 0x1000, 0x1002, 0x1002, 0x1004, 0x1004, 0x1008, 0x100A,
	0x100C, 0x100D, 0x100F, 0x1010, 0x1012, 0x1016, 0x1024, 0x1024,
	0x1027, 0x1027, 0x1100, 0x1100, 0x1102, 0x1102, 0x1104, 0x1104,
	0x1110, 0x1110, 0x1112, 0x1116, 0x1124, 0x1124, 0x1300, 0x1300,
	0x1380, 0x1380,
	/* GRAS CTX 0 */
	0x2000, 0x2004, 0x2008, 0x2067, 0x2070, 0x2078, 0x207B, 0x216E,
	/* PC CTX 0 */
	0x21C0, 0x21C6, 0x21D0, 0x21D0, 0x21D9, 0x21D9, 0x21E5, 0x21E7,
	/* VFD CTX 0 */
	0x2200, 0x2204, 0x2208, 0x22A9,
	/* GRAS CTX 1 */
	0x2400, 0x2404, 0x2408, 0x2467, 0x2470, 0x2478, 0x247B, 0x256E,
	/* PC CTX 1 */
	0x25C0, 0x25C6, 0x25D0, 0x25D0, 0x25D9, 0x25D9, 0x25E5, 0x25E7,
	/* VFD CTX 1 */
	0x2600, 0x2604, 0x2608, 0x26A9,
	/* XPU */
	0x2C00, 0x2C01, 0x2C10, 0x2C10, 0x2C12, 0x2C16, 0x2C1D, 0x2C20,
	0x2C28, 0x2C28, 0x2C30, 0x2C30, 0x2C32, 0x2C36, 0x2C40, 0x2C40,
	0x2C50, 0x2C50, 0x2C52, 0x2C56, 0x2C80, 0x2C80, 0x2C94, 0x2C95,
	/* VBIF */
	0x3000, 0x3007, 0x300C, 0x3014, 0x3018, 0x301D, 0x3020, 0x3022,
	0x3024, 0x3026, 0x3028, 0x302A, 0x302C, 0x302D, 0x3030, 0x3031,
	0x3034, 0x3036, 0x3038, 0x3038, 0x303C, 0x303D, 0x3040, 0x3040,
	0x3049, 0x3049, 0x3058, 0x3058, 0x305B, 0x3061, 0x3064, 0x3068,
	0x306C, 0x306D, 0x3080, 0x3088, 0x308B, 0x308C, 0x3090, 0x3094,
	0x3098, 0x3098, 0x309C, 0x309C, 0x30C0, 0x30C0, 0x30C8, 0x30C8,
	0x30D0, 0x30D0, 0x30D8, 0x30D8, 0x30E0, 0x30E0, 0x3100, 0x3100,
	0x3108, 0x3108, 0x3110, 0x3110, 0x3118, 0x3118, 0x3120, 0x3120,
	0x3124, 0x3125, 0x3129, 0x3129, 0x3131, 0x3131, 0x330C, 0x330C,
	0x3310, 0x3310, 0x3400, 0x3401, 0x3410, 0x3410, 0x3412, 0x3416,
	0x341D, 0x3420, 0x3428, 0x3428, 0x3430, 0x3430, 0x3432, 0x3436,
	0x3440, 0x3440, 0x3450, 0x3450, 0x3452, 0x3456, 0x3480, 0x3480,
	0x3494, 0x3495, 0x4000, 0x4000, 0x4002, 0x4002, 0x4004, 0x4004,
	0x4008, 0x400A, 0x400C, 0x400D, 0x400F, 0x4012, 0x4014, 0x4016,
	0x401D, 0x401D, 0x4020, 0x4027, 0x4060, 0x4062, 0x4200, 0x4200,
	0x4300, 0x4300, 0x4400, 0x4400, 0x4500, 0x4500, 0x4800, 0x4802,
	0x480F, 0x480F, 0x4811, 0x4811, 0x4813, 0x4813, 0x4815, 0x4816,
	0x482B, 0x482B, 0x4857, 0x4857, 0x4883, 0x4883, 0x48AF, 0x48AF,
	0x48C5, 0x48C5, 0x48E5, 0x48E5, 0x4905, 0x4905, 0x4925, 0x4925,
	0x4945, 0x4945, 0x4950, 0x4950, 0x495B, 0x495B, 0x4980, 0x498E,
	0x4B00, 0x4B00, 0x4C00, 0x4C00, 0x4D00, 0x4D00, 0x4E00, 0x4E00,
	0x4E80, 0x4E80, 0x4F00, 0x4F00, 0x4F08, 0x4F08, 0x4F10, 0x4F10,
	0x4F18, 0x4F18, 0x4F20, 0x4F20, 0x4F30, 0x4F30, 0x4F60, 0x4F60,
	0x4F80, 0x4F81, 0x4F88, 0x4F89, 0x4FEE, 0x4FEE, 0x4FF3, 0x4FF3,
	0x6000, 0x6001, 0x6008, 0x600F, 0x6014, 0x6016, 0x6018, 0x601B,
	0x61FD, 0x61FD, 0x623C, 0x623C, 0x6380, 0x6380, 0x63A0, 0x63A0,
	0x63C0, 0x63C1, 0x63C8, 0x63C9, 0x63D0, 0x63D4, 0x63D6, 0x63D6,
	0x63EE, 0x63EE, 0x6400, 0x6401, 0x6408, 0x640F, 0x6414, 0x6416,
	0x6418, 0x641B, 0x65FD, 0x65FD, 0x663C, 0x663C, 0x6780, 0x6780,
	0x67A0, 0x67A0, 0x67C0, 0x67C1, 0x67C8, 0x67C9, 0x67D0, 0x67D4,
	0x67D6, 0x67D6, 0x67EE, 0x67EE, 0x6800, 0x6801, 0x6808, 0x680F,
	0x6814, 0x6816, 0x6818, 0x681B, 0x69FD, 0x69FD, 0x6A3C, 0x6A3C,
	0x6B80, 0x6B80, 0x6BA0, 0x6BA0, 0x6BC0, 0x6BC1, 0x6BC8, 0x6BC9,
	0x6BD0, 0x6BD4, 0x6BD6, 0x6BD6, 0x6BEE, 0x6BEE,
	~0 /* sentinel */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक a405_रेजिस्टरs[] = अणु
	/* RBBM */
	0x0000, 0x0002, 0x0004, 0x0021, 0x0023, 0x0024, 0x0026, 0x0026,
	0x0028, 0x002B, 0x002E, 0x0034, 0x0037, 0x0044, 0x0047, 0x0066,
	0x0068, 0x0095, 0x009C, 0x0170, 0x0174, 0x01AF,
	/* CP */
	0x0200, 0x0233, 0x0240, 0x0250, 0x04C0, 0x04DD, 0x0500, 0x050B,
	0x0578, 0x058F,
	/* VSC */
	0x0C00, 0x0C03, 0x0C08, 0x0C41, 0x0C50, 0x0C51,
	/* GRAS */
	0x0C80, 0x0C81, 0x0C88, 0x0C8F,
	/* RB */
	0x0CC0, 0x0CC0, 0x0CC4, 0x0CD2,
	/* PC */
	0x0D00, 0x0D0C, 0x0D10, 0x0D17, 0x0D20, 0x0D23,
	/* VFD */
	0x0E40, 0x0E4A,
	/* VPC */
	0x0E60, 0x0E61, 0x0E63, 0x0E68,
	/* UCHE */
	0x0E80, 0x0E84, 0x0E88, 0x0E95,
	/* GRAS CTX 0 */
	0x2000, 0x2004, 0x2008, 0x2067, 0x2070, 0x2078, 0x207B, 0x216E,
	/* PC CTX 0 */
	0x21C0, 0x21C6, 0x21D0, 0x21D0, 0x21D9, 0x21D9, 0x21E5, 0x21E7,
	/* VFD CTX 0 */
	0x2200, 0x2204, 0x2208, 0x22A9,
	/* GRAS CTX 1 */
	0x2400, 0x2404, 0x2408, 0x2467, 0x2470, 0x2478, 0x247B, 0x256E,
	/* PC CTX 1 */
	0x25C0, 0x25C6, 0x25D0, 0x25D0, 0x25D9, 0x25D9, 0x25E5, 0x25E7,
	/* VFD CTX 1 */
	0x2600, 0x2604, 0x2608, 0x26A9,
	/* VBIF version 0x20050000*/
	0x3000, 0x3007, 0x302C, 0x302C, 0x3030, 0x3030, 0x3034, 0x3036,
	0x3038, 0x3038, 0x303C, 0x303D, 0x3040, 0x3040, 0x3049, 0x3049,
	0x3058, 0x3058, 0x305B, 0x3061, 0x3064, 0x3068, 0x306C, 0x306D,
	0x3080, 0x3088, 0x308B, 0x308C, 0x3090, 0x3094, 0x3098, 0x3098,
	0x309C, 0x309C, 0x30C0, 0x30C0, 0x30C8, 0x30C8, 0x30D0, 0x30D0,
	0x30D8, 0x30D8, 0x30E0, 0x30E0, 0x3100, 0x3100, 0x3108, 0x3108,
	0x3110, 0x3110, 0x3118, 0x3118, 0x3120, 0x3120, 0x3124, 0x3125,
	0x3129, 0x3129, 0x340C, 0x340C, 0x3410, 0x3410,
	~0 /* sentinel */
पूर्ण;

अटल काष्ठा msm_gpu_state *a4xx_gpu_state_get(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_gpu_state *state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	adreno_gpu_state_get(gpu, state);

	state->rbbm_status = gpu_पढ़ो(gpu, REG_A4XX_RBBM_STATUS);

	वापस state;
पूर्ण

अटल व्योम a4xx_dump(काष्ठा msm_gpu *gpu)
अणु
	prपूर्णांकk("status:   %08x\n",
			gpu_पढ़ो(gpu, REG_A4XX_RBBM_STATUS));
	adreno_dump(gpu);
पूर्ण

अटल पूर्णांक a4xx_pm_resume(काष्ठा msm_gpu *gpu) अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक ret;

	ret = msm_gpu_pm_resume(gpu);
	अगर (ret)
		वापस ret;

	अगर (adreno_is_a430(adreno_gpu)) अणु
		अचिन्हित पूर्णांक reg;
		/* Set the शेष रेजिस्टर values; set SW_COLLAPSE to 0 */
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_POWER_CNTL_IP, 0x778000);
		करो अणु
			udelay(5);
			reg = gpu_पढ़ो(gpu, REG_A4XX_RBBM_POWER_STATUS);
		पूर्ण जबतक (!(reg & A4XX_RBBM_POWER_CNTL_IP_SP_TP_PWR_ON));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक a4xx_pm_suspend(काष्ठा msm_gpu *gpu) अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	पूर्णांक ret;

	ret = msm_gpu_pm_suspend(gpu);
	अगर (ret)
		वापस ret;

	अगर (adreno_is_a430(adreno_gpu)) अणु
		/* Set the शेष रेजिस्टर values; set SW_COLLAPSE to 1 */
		gpu_ग_लिखो(gpu, REG_A4XX_RBBM_POWER_CNTL_IP, 0x778001);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक a4xx_get_बारtamp(काष्ठा msm_gpu *gpu, uपूर्णांक64_t *value)
अणु
	*value = gpu_पढ़ो64(gpu, REG_A4XX_RBBM_PERFCTR_CP_0_LO,
		REG_A4XX_RBBM_PERFCTR_CP_0_HI);

	वापस 0;
पूर्ण

अटल u32 a4xx_get_rptr(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	ring->memptrs->rptr = gpu_पढ़ो(gpu, REG_A4XX_CP_RB_RPTR);
	वापस ring->memptrs->rptr;
पूर्ण

अटल स्थिर काष्ठा adreno_gpu_funcs funcs = अणु
	.base = अणु
		.get_param = adreno_get_param,
		.hw_init = a4xx_hw_init,
		.pm_suspend = a4xx_pm_suspend,
		.pm_resume = a4xx_pm_resume,
		.recover = a4xx_recover,
		.submit = a4xx_submit,
		.active_ring = adreno_active_ring,
		.irq = a4xx_irq,
		.destroy = a4xx_destroy,
#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
		.show = adreno_show,
#पूर्ण_अगर
		.gpu_state_get = a4xx_gpu_state_get,
		.gpu_state_put = adreno_gpu_state_put,
		.create_address_space = adreno_iommu_create_address_space,
		.get_rptr = a4xx_get_rptr,
	पूर्ण,
	.get_बारtamp = a4xx_get_बारtamp,
पूर्ण;

काष्ठा msm_gpu *a4xx_gpu_init(काष्ठा drm_device *dev)
अणु
	काष्ठा a4xx_gpu *a4xx_gpu = शून्य;
	काष्ठा adreno_gpu *adreno_gpu;
	काष्ठा msm_gpu *gpu;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	काष्ठा icc_path *ocmem_icc_path;
	काष्ठा icc_path *icc_path;
	पूर्णांक ret;

	अगर (!pdev) अणु
		DRM_DEV_ERROR(dev->dev, "no a4xx device\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	a4xx_gpu = kzalloc(माप(*a4xx_gpu), GFP_KERNEL);
	अगर (!a4xx_gpu) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	adreno_gpu = &a4xx_gpu->base;
	gpu = &adreno_gpu->base;

	gpu->perfcntrs = शून्य;
	gpu->num_perfcntrs = 0;

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	अगर (ret)
		जाओ fail;

	adreno_gpu->रेजिस्टरs = adreno_is_a405(adreno_gpu) ? a405_रेजिस्टरs :
							     a4xx_रेजिस्टरs;

	/* अगर needed, allocate gmem: */
	ret = adreno_gpu_ocmem_init(dev->dev, adreno_gpu,
				    &a4xx_gpu->ocmem);
	अगर (ret)
		जाओ fail;

	अगर (!gpu->aspace) अणु
		/* TODO we think it is possible to configure the GPU to
		 * restrict access to VRAM carveout.  But the required
		 * रेजिस्टरs are unknown.  For now just bail out and
		 * limp aदीर्घ with just modesetting.  If it turns out
		 * to not be possible to restrict access, then we must
		 * implement a cmdstream validator.
		 */
		DRM_DEV_ERROR(dev->dev, "No memory protection without IOMMU\n");
		अगर (!allow_vram_carveout) अणु
			ret = -ENXIO;
			जाओ fail;
		पूर्ण
	पूर्ण

	icc_path = devm_of_icc_get(&pdev->dev, "gfx-mem");
	ret = IS_ERR(icc_path);
	अगर (ret)
		जाओ fail;

	ocmem_icc_path = devm_of_icc_get(&pdev->dev, "ocmem");
	ret = IS_ERR(ocmem_icc_path);
	अगर (ret) अणु
		/* allow -ENODATA, ocmem icc is optional */
		अगर (ret != -ENODATA)
			जाओ fail;
		ocmem_icc_path = शून्य;
	पूर्ण

	/*
	 * Set the ICC path to maximum speed क्रम now by multiplying the fastest
	 * frequency by the bus width (8). We'll want to scale this later on to
	 * improve battery lअगरe.
	 */
	icc_set_bw(icc_path, 0, Bps_to_icc(gpu->fast_rate) * 8);
	icc_set_bw(ocmem_icc_path, 0, Bps_to_icc(gpu->fast_rate) * 8);

	वापस gpu;

fail:
	अगर (a4xx_gpu)
		a4xx_destroy(&a4xx_gpu->base.base);

	वापस ERR_PTR(ret);
पूर्ण
