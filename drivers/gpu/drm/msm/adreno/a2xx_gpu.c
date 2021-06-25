<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 The Linux Foundation. All rights reserved. */

#समावेश "a2xx_gpu.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"

बाह्य bool hang_debug;

अटल व्योम a2xx_dump(काष्ठा msm_gpu *gpu);
अटल bool a2xx_idle(काष्ठा msm_gpu *gpu);

अटल व्योम a2xx_submit(काष्ठा msm_gpu *gpu, काष्ठा msm_gem_submit *submit)
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
			OUT_PKT3(ring, CP_INसूचीECT_BUFFER_PFD, 2);
			OUT_RING(ring, lower_32_bits(submit->cmd[i].iova));
			OUT_RING(ring, submit->cmd[i].size);
			OUT_PKT2(ring);
			अवरोध;
		पूर्ण
	पूर्ण

	OUT_PKT0(ring, REG_AXXX_CP_SCRATCH_REG2, 1);
	OUT_RING(ring, submit->seqno);

	/* रुको क्रम idle beक्रमe cache flush/पूर्णांकerrupt */
	OUT_PKT3(ring, CP_WAIT_FOR_IDLE, 1);
	OUT_RING(ring, 0x00000000);

	OUT_PKT3(ring, CP_EVENT_WRITE, 3);
	OUT_RING(ring, CACHE_FLUSH_TS);
	OUT_RING(ring, rbmemptr(ring, fence));
	OUT_RING(ring, submit->seqno);
	OUT_PKT3(ring, CP_INTERRUPT, 1);
	OUT_RING(ring, 0x80000000);

	adreno_flush(gpu, ring, REG_AXXX_CP_RB_WPTR);
पूर्ण

अटल bool a2xx_me_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_ringbuffer *ring = gpu->rb[0];

	OUT_PKT3(ring, CP_ME_INIT, 18);

	/* All fields present (bits 9:0) */
	OUT_RING(ring, 0x000003ff);
	/* Disable/Enable Real-Time Stream processing (present but ignored) */
	OUT_RING(ring, 0x00000000);
	/* Enable (2D <-> 3D) implicit synchronization (present but ignored) */
	OUT_RING(ring, 0x00000000);

	OUT_RING(ring, REG_A2XX_RB_SURFACE_INFO - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SC_WINDOW_OFFSET - 0x2000);
	OUT_RING(ring, REG_A2XX_VGT_MAX_VTX_INDX - 0x2000);
	OUT_RING(ring, REG_A2XX_SQ_PROGRAM_CNTL - 0x2000);
	OUT_RING(ring, REG_A2XX_RB_DEPTHCONTROL - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SU_POINT_SIZE - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SC_LINE_CNTL - 0x2000);
	OUT_RING(ring, REG_A2XX_PA_SU_POLY_OFFSET_FRONT_SCALE - 0x2000);

	/* Vertex and Pixel Shader Start Addresses in inकाष्ठाions
	 * (3 DWORDS per inकाष्ठाion) */
	OUT_RING(ring, 0x80000180);
	/* Maximum Contexts */
	OUT_RING(ring, 0x00000001);
	/* Write Confirm Interval and The CP will रुको the
	 * रुको_पूर्णांकerval * 16 घड़ीs between polling  */
	OUT_RING(ring, 0x00000000);
	/* NQ and External Memory Swap */
	OUT_RING(ring, 0x00000000);
	/* रक्षित mode error checking (0x1f2 is REG_AXXX_CP_INT_CNTL) */
	OUT_RING(ring, 0x200001f2);
	/* Disable header dumping and Header dump address */
	OUT_RING(ring, 0x00000000);
	/* Header dump size */
	OUT_RING(ring, 0x00000000);

	/* enable रक्षित mode */
	OUT_PKT3(ring, CP_SET_PROTECTED_MODE, 1);
	OUT_RING(ring, 1);

	adreno_flush(gpu, ring, REG_AXXX_CP_RB_WPTR);
	वापस a2xx_idle(gpu);
पूर्ण

अटल पूर्णांक a2xx_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	dma_addr_t pt_base, tran_error;
	uपूर्णांक32_t *ptr, len;
	पूर्णांक i, ret;

	msm_gpummu_params(gpu->aspace->mmu, &pt_base, &tran_error);

	DBG("%s", gpu->name);

	/* halt ME to aव्योम ucode upload issues on a20x */
	gpu_ग_लिखो(gpu, REG_AXXX_CP_ME_CNTL, AXXX_CP_ME_CNTL_HALT);

	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_PM_OVERRIDE1, 0xfffffffe);
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_PM_OVERRIDE2, 0xffffffff);

	/* note: kgsl uses 0x00000001 after first reset on a22x */
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_SOFT_RESET, 0xffffffff);
	msleep(30);
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_SOFT_RESET, 0x00000000);

	अगर (adreno_is_a225(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A2XX_SQ_FLOW_CONTROL, 0x18000000);

	/* note: kgsl uses 0x0000ffff क्रम a20x */
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_CNTL, 0x00004442);

	/* MPU: physical range */
	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_MPU_BASE, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_MPU_END, 0xfffff000);

	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_CONFIG, A2XX_MH_MMU_CONFIG_MMU_ENABLE |
		A2XX_MH_MMU_CONFIG_RB_W_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_W_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R0_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R1_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R2_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R3_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_CP_R4_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_VGT_R0_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_VGT_R1_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_TC_R_CLNT_BEHAVIOR(BEH_TRAN_RNG) |
		A2XX_MH_MMU_CONFIG_PA_W_CLNT_BEHAVIOR(BEH_TRAN_RNG));

	/* same as parameters in adreno_gpu */
	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_VA_RANGE, SZ_16M |
		A2XX_MH_MMU_VA_RANGE_NUM_64KB_REGIONS(0xfff));

	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_PT_BASE, pt_base);
	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_TRAN_ERROR, tran_error);

	gpu_ग_लिखो(gpu, REG_A2XX_MH_MMU_INVALIDATE,
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_ALL |
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_TC);

	gpu_ग_लिखो(gpu, REG_A2XX_MH_ARBITER_CONFIG,
		A2XX_MH_ARBITER_CONFIG_SAME_PAGE_LIMIT(16) |
		A2XX_MH_ARBITER_CONFIG_L1_ARB_ENABLE |
		A2XX_MH_ARBITER_CONFIG_L1_ARB_HOLD_ENABLE |
		A2XX_MH_ARBITER_CONFIG_PAGE_SIZE(1) |
		A2XX_MH_ARBITER_CONFIG_TC_REORDER_ENABLE |
		A2XX_MH_ARBITER_CONFIG_TC_ARB_HOLD_ENABLE |
		A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_IN_FLIGHT_LIMIT(8) |
		A2XX_MH_ARBITER_CONFIG_CP_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_VGT_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_TC_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_RB_CLNT_ENABLE |
		A2XX_MH_ARBITER_CONFIG_PA_CLNT_ENABLE);
	अगर (!adreno_is_a20x(adreno_gpu))
		gpu_ग_लिखो(gpu, REG_A2XX_MH_CLNT_INTF_CTRL_CONFIG1, 0x00032f07);

	gpu_ग_लिखो(gpu, REG_A2XX_SQ_VS_PROGRAM, 0x00000000);
	gpu_ग_लिखो(gpu, REG_A2XX_SQ_PS_PROGRAM, 0x00000000);

	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_PM_OVERRIDE1, 0); /* 0x200 क्रम msm8960? */
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_PM_OVERRIDE2, 0); /* 0x80/0x1a0 क्रम a22x? */

	/* note: gsl करोesn't set this */
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_DEBUG, 0x00080000);

	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_INT_CNTL,
		A2XX_RBBM_INT_CNTL_RDERR_INT_MASK);
	gpu_ग_लिखो(gpu, REG_AXXX_CP_INT_CNTL,
		AXXX_CP_INT_CNTL_T0_PACKET_IN_IB_MASK |
		AXXX_CP_INT_CNTL_OPCODE_ERROR_MASK |
		AXXX_CP_INT_CNTL_PROTECTED_MODE_ERROR_MASK |
		AXXX_CP_INT_CNTL_RESERVED_BIT_ERROR_MASK |
		AXXX_CP_INT_CNTL_IB_ERROR_MASK |
		AXXX_CP_INT_CNTL_IB1_INT_MASK |
		AXXX_CP_INT_CNTL_RB_INT_MASK);
	gpu_ग_लिखो(gpu, REG_A2XX_SQ_INT_CNTL, 0);
	gpu_ग_लिखो(gpu, REG_A2XX_MH_INTERRUPT_MASK,
		A2XX_MH_INTERRUPT_MASK_AXI_READ_ERROR |
		A2XX_MH_INTERRUPT_MASK_AXI_WRITE_ERROR |
		A2XX_MH_INTERRUPT_MASK_MMU_PAGE_FAULT);

	क्रम (i = 3; i <= 5; i++)
		अगर ((SZ_16K << i) == adreno_gpu->gmem)
			अवरोध;
	gpu_ग_लिखो(gpu, REG_A2XX_RB_EDRAM_INFO, i);

	ret = adreno_hw_init(gpu);
	अगर (ret)
		वापस ret;

	gpu_ग_लिखो(gpu, REG_AXXX_CP_RB_CNTL,
		MSM_GPU_RB_CNTL_DEFAULT | AXXX_CP_RB_CNTL_NO_UPDATE);

	gpu_ग_लिखो(gpu, REG_AXXX_CP_RB_BASE, lower_32_bits(gpu->rb[0]->iova));

	/* NOTE: PM4/micro-engine firmware रेजिस्टरs look to be the same
	 * क्रम a2xx and a3xx.. we could possibly push that part करोwn to
	 * adreno_gpu base class.  Or push both PM4 and PFP but
	 * parameterize the pfp ucode addr/data रेजिस्टरs..
	 */

	/* Load PM4: */
	ptr = (uपूर्णांक32_t *)(adreno_gpu->fw[ADRENO_FW_PM4]->data);
	len = adreno_gpu->fw[ADRENO_FW_PM4]->size / 4;
	DBG("loading PM4 ucode version: %x", ptr[1]);

	gpu_ग_लिखो(gpu, REG_AXXX_CP_DEBUG,
			AXXX_CP_DEBUG_MIU_128BIT_WRITE_ENABLE);
	gpu_ग_लिखो(gpu, REG_AXXX_CP_ME_RAM_WADDR, 0);
	क्रम (i = 1; i < len; i++)
		gpu_ग_लिखो(gpu, REG_AXXX_CP_ME_RAM_DATA, ptr[i]);

	/* Load PFP: */
	ptr = (uपूर्णांक32_t *)(adreno_gpu->fw[ADRENO_FW_PFP]->data);
	len = adreno_gpu->fw[ADRENO_FW_PFP]->size / 4;
	DBG("loading PFP ucode version: %x", ptr[5]);

	gpu_ग_लिखो(gpu, REG_A2XX_CP_PFP_UCODE_ADDR, 0);
	क्रम (i = 1; i < len; i++)
		gpu_ग_लिखो(gpu, REG_A2XX_CP_PFP_UCODE_DATA, ptr[i]);

	gpu_ग_लिखो(gpu, REG_AXXX_CP_QUEUE_THRESHOLDS, 0x000C0804);

	/* clear ME_HALT to start micro engine */
	gpu_ग_लिखो(gpu, REG_AXXX_CP_ME_CNTL, 0);

	वापस a2xx_me_init(gpu) ? 0 : -EINVAL;
पूर्ण

अटल व्योम a2xx_recover(काष्ठा msm_gpu *gpu)
अणु
	पूर्णांक i;

	adreno_dump_info(gpu);

	क्रम (i = 0; i < 8; i++) अणु
		prपूर्णांकk("CP_SCRATCH_REG%d: %u\n", i,
			gpu_पढ़ो(gpu, REG_AXXX_CP_SCRATCH_REG0 + i));
	पूर्ण

	/* dump रेजिस्टरs beक्रमe resetting gpu, अगर enabled: */
	अगर (hang_debug)
		a2xx_dump(gpu);

	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_SOFT_RESET, 1);
	gpu_पढ़ो(gpu, REG_A2XX_RBBM_SOFT_RESET);
	gpu_ग_लिखो(gpu, REG_A2XX_RBBM_SOFT_RESET, 0);
	adreno_recover(gpu);
पूर्ण

अटल व्योम a2xx_destroy(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a2xx_gpu *a2xx_gpu = to_a2xx_gpu(adreno_gpu);

	DBG("%s", gpu->name);

	adreno_gpu_cleanup(adreno_gpu);

	kमुक्त(a2xx_gpu);
पूर्ण

अटल bool a2xx_idle(काष्ठा msm_gpu *gpu)
अणु
	/* रुको क्रम ringbuffer to drain: */
	अगर (!adreno_idle(gpu, gpu->rb[0]))
		वापस false;

	/* then रुको क्रम GPU to finish: */
	अगर (spin_until(!(gpu_पढ़ो(gpu, REG_A2XX_RBBM_STATUS) &
			A2XX_RBBM_STATUS_GUI_ACTIVE))) अणु
		DRM_ERROR("%s: timeout waiting for GPU to idle!\n", gpu->name);

		/* TODO maybe we need to reset GPU here to recover from hang? */
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t a2xx_irq(काष्ठा msm_gpu *gpu)
अणु
	uपूर्णांक32_t mstatus, status;

	mstatus = gpu_पढ़ो(gpu, REG_A2XX_MASTER_INT_SIGNAL);

	अगर (mstatus & A2XX_MASTER_INT_SIGNAL_MH_INT_STAT) अणु
		status = gpu_पढ़ो(gpu, REG_A2XX_MH_INTERRUPT_STATUS);

		dev_warn(gpu->dev->dev, "MH_INT: %08X\n", status);
		dev_warn(gpu->dev->dev, "MMU_PAGE_FAULT: %08X\n",
			gpu_पढ़ो(gpu, REG_A2XX_MH_MMU_PAGE_FAULT));

		gpu_ग_लिखो(gpu, REG_A2XX_MH_INTERRUPT_CLEAR, status);
	पूर्ण

	अगर (mstatus & A2XX_MASTER_INT_SIGNAL_CP_INT_STAT) अणु
		status = gpu_पढ़ो(gpu, REG_AXXX_CP_INT_STATUS);

		/* only RB_INT is expected */
		अगर (status & ~AXXX_CP_INT_CNTL_RB_INT_MASK)
			dev_warn(gpu->dev->dev, "CP_INT: %08X\n", status);

		gpu_ग_लिखो(gpu, REG_AXXX_CP_INT_ACK, status);
	पूर्ण

	अगर (mstatus & A2XX_MASTER_INT_SIGNAL_RBBM_INT_STAT) अणु
		status = gpu_पढ़ो(gpu, REG_A2XX_RBBM_INT_STATUS);

		dev_warn(gpu->dev->dev, "RBBM_INT: %08X\n", status);

		gpu_ग_लिखो(gpu, REG_A2XX_RBBM_INT_ACK, status);
	पूर्ण

	msm_gpu_retire(gpu);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक a200_रेजिस्टरs[] = अणु
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x01C0, 0x01C1, 0x01C3, 0x01C8, 0x01D5, 0x01D9,
	0x01DC, 0x01DD, 0x01EA, 0x01EA, 0x01EE, 0x01F3, 0x01F6, 0x01F7,
	0x01FC, 0x01FF, 0x0391, 0x0392, 0x039B, 0x039E, 0x03B2, 0x03B5,
	0x03B7, 0x03B7, 0x03F8, 0x03FB, 0x0440, 0x0440, 0x0443, 0x0444,
	0x044B, 0x044B, 0x044D, 0x044F, 0x0452, 0x0452, 0x0454, 0x045B,
	0x047F, 0x047F, 0x0578, 0x0587, 0x05C9, 0x05C9, 0x05D0, 0x05D0,
	0x0601, 0x0604, 0x0606, 0x0609, 0x060B, 0x060E, 0x0613, 0x0614,
	0x0A29, 0x0A2B, 0x0A2F, 0x0A31, 0x0A40, 0x0A43, 0x0A45, 0x0A45,
	0x0A4E, 0x0A4F, 0x0C2C, 0x0C2C, 0x0C30, 0x0C30, 0x0C38, 0x0C3C,
	0x0C40, 0x0C40, 0x0C44, 0x0C44, 0x0C80, 0x0C86, 0x0C88, 0x0C94,
	0x0C99, 0x0C9A, 0x0CA4, 0x0CA5, 0x0D00, 0x0D03, 0x0D06, 0x0D06,
	0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1, 0x0DC8, 0x0DD4,
	0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04, 0x0E17, 0x0E1E,
	0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0, 0x0ED4, 0x0ED7,
	0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x0F0C, 0x0F0C, 0x0F0E, 0x0F12,
	0x0F26, 0x0F2A, 0x0F2C, 0x0F2C, 0x2000, 0x2002, 0x2006, 0x200F,
	0x2080, 0x2082, 0x2100, 0x2109, 0x210C, 0x2114, 0x2180, 0x2184,
	0x21F5, 0x21F7, 0x2200, 0x2208, 0x2280, 0x2283, 0x2293, 0x2294,
	0x2300, 0x2308, 0x2312, 0x2312, 0x2316, 0x231D, 0x2324, 0x2326,
	0x2380, 0x2383, 0x2400, 0x2402, 0x2406, 0x240F, 0x2480, 0x2482,
	0x2500, 0x2509, 0x250C, 0x2514, 0x2580, 0x2584, 0x25F5, 0x25F7,
	0x2600, 0x2608, 0x2680, 0x2683, 0x2693, 0x2694, 0x2700, 0x2708,
	0x2712, 0x2712, 0x2716, 0x271D, 0x2724, 0x2726, 0x2780, 0x2783,
	0x4000, 0x4003, 0x4800, 0x4805, 0x4900, 0x4900, 0x4908, 0x4908,
	~0   /* sentinel */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक a220_रेजिस्टरs[] = अणु
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x01C0, 0x01C1, 0x01C3, 0x01C8, 0x01D5, 0x01D9,
	0x01DC, 0x01DD, 0x01EA, 0x01EA, 0x01EE, 0x01F3, 0x01F6, 0x01F7,
	0x01FC, 0x01FF, 0x0391, 0x0392, 0x039B, 0x039E, 0x03B2, 0x03B5,
	0x03B7, 0x03B7, 0x03F8, 0x03FB, 0x0440, 0x0440, 0x0443, 0x0444,
	0x044B, 0x044B, 0x044D, 0x044F, 0x0452, 0x0452, 0x0454, 0x045B,
	0x047F, 0x047F, 0x0578, 0x0587, 0x05C9, 0x05C9, 0x05D0, 0x05D0,
	0x0601, 0x0604, 0x0606, 0x0609, 0x060B, 0x060E, 0x0613, 0x0614,
	0x0A29, 0x0A2B, 0x0A2F, 0x0A31, 0x0A40, 0x0A40, 0x0A42, 0x0A43,
	0x0A45, 0x0A45, 0x0A4E, 0x0A4F, 0x0C30, 0x0C30, 0x0C38, 0x0C39,
	0x0C3C, 0x0C3C, 0x0C80, 0x0C81, 0x0C88, 0x0C93, 0x0D00, 0x0D03,
	0x0D05, 0x0D06, 0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1,
	0x0DC8, 0x0DD4, 0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04,
	0x0E17, 0x0E1E, 0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0,
	0x0ED4, 0x0ED7, 0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x2000, 0x2002,
	0x2006, 0x200F, 0x2080, 0x2082, 0x2100, 0x2102, 0x2104, 0x2109,
	0x210C, 0x2114, 0x2180, 0x2184, 0x21F5, 0x21F7, 0x2200, 0x2202,
	0x2204, 0x2204, 0x2208, 0x2208, 0x2280, 0x2282, 0x2294, 0x2294,
	0x2300, 0x2308, 0x2309, 0x230A, 0x2312, 0x2312, 0x2316, 0x2316,
	0x2318, 0x231D, 0x2324, 0x2326, 0x2380, 0x2383, 0x2400, 0x2402,
	0x2406, 0x240F, 0x2480, 0x2482, 0x2500, 0x2502, 0x2504, 0x2509,
	0x250C, 0x2514, 0x2580, 0x2584, 0x25F5, 0x25F7, 0x2600, 0x2602,
	0x2604, 0x2606, 0x2608, 0x2608, 0x2680, 0x2682, 0x2694, 0x2694,
	0x2700, 0x2708, 0x2712, 0x2712, 0x2716, 0x2716, 0x2718, 0x271D,
	0x2724, 0x2726, 0x2780, 0x2783, 0x4000, 0x4003, 0x4800, 0x4805,
	0x4900, 0x4900, 0x4908, 0x4908,
	~0   /* sentinel */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक a225_रेजिस्टरs[] = अणु
	0x0000, 0x0002, 0x0004, 0x000B, 0x003B, 0x003D, 0x0040, 0x0044,
	0x0046, 0x0047, 0x013C, 0x013C, 0x0140, 0x014F, 0x01C0, 0x01C1,
	0x01C3, 0x01C8, 0x01D5, 0x01D9, 0x01DC, 0x01DD, 0x01EA, 0x01EA,
	0x01EE, 0x01F3, 0x01F6, 0x01F7, 0x01FC, 0x01FF, 0x0391, 0x0392,
	0x039B, 0x039E, 0x03B2, 0x03B5, 0x03B7, 0x03B7, 0x03F8, 0x03FB,
	0x0440, 0x0440, 0x0443, 0x0444, 0x044B, 0x044B, 0x044D, 0x044F,
	0x0452, 0x0452, 0x0454, 0x045B, 0x047F, 0x047F, 0x0578, 0x0587,
	0x05C9, 0x05C9, 0x05D0, 0x05D0, 0x0601, 0x0604, 0x0606, 0x0609,
	0x060B, 0x060E, 0x0613, 0x0614, 0x0A29, 0x0A2B, 0x0A2F, 0x0A31,
	0x0A40, 0x0A40, 0x0A42, 0x0A43, 0x0A45, 0x0A45, 0x0A4E, 0x0A4F,
	0x0C01, 0x0C1D, 0x0C30, 0x0C30, 0x0C38, 0x0C39, 0x0C3C, 0x0C3C,
	0x0C80, 0x0C81, 0x0C88, 0x0C93, 0x0D00, 0x0D03, 0x0D05, 0x0D06,
	0x0D08, 0x0D0B, 0x0D34, 0x0D35, 0x0DAE, 0x0DC1, 0x0DC8, 0x0DD4,
	0x0DD8, 0x0DD9, 0x0E00, 0x0E00, 0x0E02, 0x0E04, 0x0E17, 0x0E1E,
	0x0EC0, 0x0EC9, 0x0ECB, 0x0ECC, 0x0ED0, 0x0ED0, 0x0ED4, 0x0ED7,
	0x0EE0, 0x0EE2, 0x0F01, 0x0F02, 0x2000, 0x200F, 0x2080, 0x2082,
	0x2100, 0x2109, 0x210C, 0x2114, 0x2180, 0x2184, 0x21F5, 0x21F7,
	0x2200, 0x2202, 0x2204, 0x2206, 0x2208, 0x2210, 0x2220, 0x2222,
	0x2280, 0x2282, 0x2294, 0x2294, 0x2297, 0x2297, 0x2300, 0x230A,
	0x2312, 0x2312, 0x2315, 0x2316, 0x2318, 0x231D, 0x2324, 0x2326,
	0x2340, 0x2357, 0x2360, 0x2360, 0x2380, 0x2383, 0x2400, 0x240F,
	0x2480, 0x2482, 0x2500, 0x2509, 0x250C, 0x2514, 0x2580, 0x2584,
	0x25F5, 0x25F7, 0x2600, 0x2602, 0x2604, 0x2606, 0x2608, 0x2610,
	0x2620, 0x2622, 0x2680, 0x2682, 0x2694, 0x2694, 0x2697, 0x2697,
	0x2700, 0x270A, 0x2712, 0x2712, 0x2715, 0x2716, 0x2718, 0x271D,
	0x2724, 0x2726, 0x2740, 0x2757, 0x2760, 0x2760, 0x2780, 0x2783,
	0x4000, 0x4003, 0x4800, 0x4806, 0x4808, 0x4808, 0x4900, 0x4900,
	0x4908, 0x4908,
	~0   /* sentinel */
पूर्ण;

/* would be nice to not have to duplicate the _show() stuff with prपूर्णांकk(): */
अटल व्योम a2xx_dump(काष्ठा msm_gpu *gpu)
अणु
	prपूर्णांकk("status:   %08x\n",
			gpu_पढ़ो(gpu, REG_A2XX_RBBM_STATUS));
	adreno_dump(gpu);
पूर्ण

अटल काष्ठा msm_gpu_state *a2xx_gpu_state_get(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_gpu_state *state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (!state)
		वापस ERR_PTR(-ENOMEM);

	adreno_gpu_state_get(gpu, state);

	state->rbbm_status = gpu_पढ़ो(gpu, REG_A2XX_RBBM_STATUS);

	वापस state;
पूर्ण

अटल काष्ठा msm_gem_address_space *
a2xx_create_address_space(काष्ठा msm_gpu *gpu, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_mmu *mmu = msm_gpummu_new(&pdev->dev, gpu);
	काष्ठा msm_gem_address_space *aspace;

	aspace = msm_gem_address_space_create(mmu, "gpu", SZ_16M,
		0xfff * SZ_64K);

	अगर (IS_ERR(aspace) && !IS_ERR(mmu))
		mmu->funcs->destroy(mmu);

	वापस aspace;
पूर्ण

अटल u32 a2xx_get_rptr(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	ring->memptrs->rptr = gpu_पढ़ो(gpu, REG_AXXX_CP_RB_RPTR);
	वापस ring->memptrs->rptr;
पूर्ण

अटल स्थिर काष्ठा adreno_gpu_funcs funcs = अणु
	.base = अणु
		.get_param = adreno_get_param,
		.hw_init = a2xx_hw_init,
		.pm_suspend = msm_gpu_pm_suspend,
		.pm_resume = msm_gpu_pm_resume,
		.recover = a2xx_recover,
		.submit = a2xx_submit,
		.active_ring = adreno_active_ring,
		.irq = a2xx_irq,
		.destroy = a2xx_destroy,
#अगर defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COREDUMP)
		.show = adreno_show,
#पूर्ण_अगर
		.gpu_state_get = a2xx_gpu_state_get,
		.gpu_state_put = adreno_gpu_state_put,
		.create_address_space = a2xx_create_address_space,
		.get_rptr = a2xx_get_rptr,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा msm_gpu_perfcntr perfcntrs[] = अणु
/* TODO */
पूर्ण;

काष्ठा msm_gpu *a2xx_gpu_init(काष्ठा drm_device *dev)
अणु
	काष्ठा a2xx_gpu *a2xx_gpu = शून्य;
	काष्ठा adreno_gpu *adreno_gpu;
	काष्ठा msm_gpu *gpu;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = priv->gpu_pdev;
	पूर्णांक ret;

	अगर (!pdev) अणु
		dev_err(dev->dev, "no a2xx device\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	a2xx_gpu = kzalloc(माप(*a2xx_gpu), GFP_KERNEL);
	अगर (!a2xx_gpu) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	adreno_gpu = &a2xx_gpu->base;
	gpu = &adreno_gpu->base;

	gpu->perfcntrs = perfcntrs;
	gpu->num_perfcntrs = ARRAY_SIZE(perfcntrs);

	अगर (adreno_is_a20x(adreno_gpu))
		adreno_gpu->रेजिस्टरs = a200_रेजिस्टरs;
	अन्यथा अगर (adreno_is_a225(adreno_gpu))
		adreno_gpu->रेजिस्टरs = a225_रेजिस्टरs;
	अन्यथा
		adreno_gpu->रेजिस्टरs = a220_रेजिस्टरs;

	ret = adreno_gpu_init(dev, pdev, adreno_gpu, &funcs, 1);
	अगर (ret)
		जाओ fail;

	अगर (!gpu->aspace) अणु
		dev_err(dev->dev, "No memory protection without MMU\n");
		अगर (!allow_vram_carveout) अणु
			ret = -ENXIO;
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस gpu;

fail:
	अगर (a2xx_gpu)
		a2xx_destroy(&a2xx_gpu->base.base);

	वापस ERR_PTR(ret);
पूर्ण
