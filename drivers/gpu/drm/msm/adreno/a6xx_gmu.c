<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017-2019 The Linux Foundation. All rights reserved. */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_opp.h>
#समावेश <soc/qcom/cmd-db.h>
#समावेश <drm/drm_gem.h>

#समावेश "a6xx_gpu.h"
#समावेश "a6xx_gmu.xml.h"
#समावेश "msm_gem.h"
#समावेश "msm_gpu_trace.h"
#समावेश "msm_mmu.h"

अटल व्योम a6xx_gmu_fault(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;

	/* FIXME: add a banner here */
	gmu->hung = true;

	/* Turn off the hangcheck समयr जबतक we are resetting */
	del_समयr(&gpu->hangcheck_समयr);

	/* Queue the GPU handler because we need to treat this as a recovery */
	kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
पूर्ण

अटल irqवापस_t a6xx_gmu_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा a6xx_gmu *gmu = data;
	u32 status;

	status = gmu_पढ़ो(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_STATUS);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR, status);

	अगर (status & A6XX_GMU_AO_HOST_INTERRUPT_STATUS_WDOG_BITE) अणु
		dev_err_ratelimited(gmu->dev, "GMU watchdog expired\n");

		a6xx_gmu_fault(gmu);
	पूर्ण

	अगर (status &  A6XX_GMU_AO_HOST_INTERRUPT_STATUS_HOST_AHB_BUS_ERROR)
		dev_err_ratelimited(gmu->dev, "GMU AHB bus error\n");

	अगर (status & A6XX_GMU_AO_HOST_INTERRUPT_STATUS_FENCE_ERR)
		dev_err_ratelimited(gmu->dev, "GMU fence error: 0x%x\n",
			gmu_पढ़ो(gmu, REG_A6XX_GMU_AHB_FENCE_STATUS));

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t a6xx_hfi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा a6xx_gmu *gmu = data;
	u32 status;

	status = gmu_पढ़ो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, status);

	अगर (status & A6XX_GMU_GMU2HOST_INTR_INFO_CM3_FAULT) अणु
		dev_err_ratelimited(gmu->dev, "GMU firmware fault\n");

		a6xx_gmu_fault(gmu);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

bool a6xx_gmu_sptprac_is_on(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;

	/* This can be called from gpu state code so make sure GMU is valid */
	अगर (!gmu->initialized)
		वापस false;

	val = gmu_पढ़ो(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS);

	वापस !(val &
		(A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SPTPRAC_GDSC_POWER_OFF |
		A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_SP_CLOCK_OFF));
पूर्ण

/* Check to see अगर the GX rail is still घातered */
bool a6xx_gmu_gx_is_on(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;

	/* This can be called from gpu state code so make sure GMU is valid */
	अगर (!gmu->initialized)
		वापस false;

	val = gmu_पढ़ो(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS);

	वापस !(val &
		(A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_GX_HM_GDSC_POWER_OFF |
		A6XX_GMU_SPTPRAC_PWR_CLK_STATUS_GX_HM_CLK_OFF));
पूर्ण

व्योम a6xx_gmu_set_freq(काष्ठा msm_gpu *gpu, काष्ठा dev_pm_opp *opp)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	u32 perf_index;
	अचिन्हित दीर्घ gpu_freq;
	पूर्णांक ret = 0;

	gpu_freq = dev_pm_opp_get_freq(opp);

	अगर (gpu_freq == gmu->freq)
		वापस;

	क्रम (perf_index = 0; perf_index < gmu->nr_gpu_freqs - 1; perf_index++)
		अगर (gpu_freq == gmu->gpu_freqs[perf_index])
			अवरोध;

	gmu->current_perf_index = perf_index;
	gmu->freq = gmu->gpu_freqs[perf_index];

	trace_msm_gmu_freq_change(gmu->freq, perf_index);

	/*
	 * This can get called from devfreq जबतक the hardware is idle. Don't
	 * bring up the घातer अगर it isn't alपढ़ोy active
	 */
	अगर (pm_runसमय_get_अगर_in_use(gmu->dev) == 0)
		वापस;

	अगर (!gmu->legacy) अणु
		a6xx_hfi_set_freq(gmu, perf_index);
		dev_pm_opp_set_opp(&gpu->pdev->dev, opp);
		pm_runसमय_put(gmu->dev);
		वापस;
	पूर्ण

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_DCVS_ACK_OPTION, 0);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_DCVS_PERF_SETTING,
			((3 & 0xf) << 28) | perf_index);

	/*
	 * Send an invalid index as a vote क्रम the bus bandwidth and let the
	 * firmware decide on the right vote
	 */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_DCVS_BW_SETTING, 0xff);

	/* Set and clear the OOB क्रम DCVS to trigger the GMU */
	a6xx_gmu_set_oob(gmu, GMU_OOB_DCVS_SET);
	a6xx_gmu_clear_oob(gmu, GMU_OOB_DCVS_SET);

	ret = gmu_पढ़ो(gmu, REG_A6XX_GMU_DCVS_RETURN);
	अगर (ret)
		dev_err(gmu->dev, "GMU set GPU frequency error: %d\n", ret);

	dev_pm_opp_set_opp(&gpu->pdev->dev, opp);
	pm_runसमय_put(gmu->dev);
पूर्ण

अचिन्हित दीर्घ a6xx_gmu_get_freq(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;

	वापस  gmu->freq;
पूर्ण

अटल bool a6xx_gmu_check_idle_level(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;
	पूर्णांक local = gmu->idle_level;

	/* SPTP and IFPC both report as IFPC */
	अगर (gmu->idle_level == GMU_IDLE_STATE_SPTP)
		local = GMU_IDLE_STATE_IFPC;

	val = gmu_पढ़ो(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE);

	अगर (val == local) अणु
		अगर (gmu->idle_level != GMU_IDLE_STATE_IFPC ||
			!a6xx_gmu_gx_is_on(gmu))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Wait क्रम the GMU to get to its most idle state */
पूर्णांक a6xx_gmu_रुको_क्रम_idle(काष्ठा a6xx_gmu *gmu)
अणु
	वापस spin_until(a6xx_gmu_check_idle_level(gmu));
पूर्ण

अटल पूर्णांक a6xx_gmu_start(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret;
	u32 val;
	u32 mask, reset_val;

	val = gmu_पढ़ो(gmu, REG_A6XX_GMU_CM3_DTCM_START + 0xff8);
	अगर (val <= 0x20010004) अणु
		mask = 0xffffffff;
		reset_val = 0xbabeface;
	पूर्ण अन्यथा अणु
		mask = 0x1ff;
		reset_val = 0x100;
	पूर्ण

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CM3_SYSRESET, 1);

	/* Set the log wptr index
	 * note: करोwnstream saves the value in घातeroff and restores it here
	 */
	gmu_ग_लिखो(gmu, REG_A6XX_GPU_GMU_CX_GMU_PWR_COL_CP_RESP, 0);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CM3_SYSRESET, 0);

	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_CM3_FW_INIT_RESULT, val,
		(val & mask) == reset_val, 100, 10000);

	अगर (ret)
		DRM_DEV_ERROR(gmu->dev, "GMU firmware initialization timed out\n");

	वापस ret;
पूर्ण

अटल पूर्णांक a6xx_gmu_hfi_start(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;
	पूर्णांक ret;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HFI_CTRL_INIT, 1);

	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_HFI_CTRL_STATUS, val,
		val & 1, 100, 10000);
	अगर (ret)
		DRM_DEV_ERROR(gmu->dev, "Unable to start the HFI queues\n");

	वापस ret;
पूर्ण

काष्ठा a6xx_gmu_oob_bits अणु
	पूर्णांक set, ack, set_new, ack_new, clear, clear_new;
	स्थिर अक्षर *name;
पूर्ण;

/* These are the पूर्णांकerrupt / ack bits क्रम each OOB request that are set
 * in a6xx_gmu_set_oob and a6xx_clear_oob
 */
अटल स्थिर काष्ठा a6xx_gmu_oob_bits a6xx_gmu_oob_bits[] = अणु
	[GMU_OOB_GPU_SET] = अणु
		.name = "GPU_SET",
		.set = 16,
		.ack = 24,
		.set_new = 30,
		.ack_new = 31,
		.clear = 24,
		.clear_new = 31,
	पूर्ण,

	[GMU_OOB_PERFCOUNTER_SET] = अणु
		.name = "PERFCOUNTER",
		.set = 17,
		.ack = 25,
		.set_new = 28,
		.ack_new = 30,
		.clear = 25,
		.clear_new = 29,
	पूर्ण,

	[GMU_OOB_BOOT_SLUMBER] = अणु
		.name = "BOOT_SLUMBER",
		.set = 22,
		.ack = 30,
		.clear = 30,
	पूर्ण,

	[GMU_OOB_DCVS_SET] = अणु
		.name = "GPU_DCVS",
		.set = 23,
		.ack = 31,
		.clear = 31,
	पूर्ण,
पूर्ण;

/* Trigger a OOB (out of band) request to the GMU */
पूर्णांक a6xx_gmu_set_oob(काष्ठा a6xx_gmu *gmu, क्रमागत a6xx_gmu_oob_state state)
अणु
	पूर्णांक ret;
	u32 val;
	पूर्णांक request, ack;

	अगर (state >= ARRAY_SIZE(a6xx_gmu_oob_bits))
		वापस -EINVAL;

	अगर (gmu->legacy) अणु
		request = a6xx_gmu_oob_bits[state].set;
		ack = a6xx_gmu_oob_bits[state].ack;
	पूर्ण अन्यथा अणु
		request = a6xx_gmu_oob_bits[state].set_new;
		ack = a6xx_gmu_oob_bits[state].ack_new;
		अगर (!request || !ack) अणु
			DRM_DEV_ERROR(gmu->dev,
				      "Invalid non-legacy GMU request %s\n",
				      a6xx_gmu_oob_bits[state].name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Trigger the equested OOB operation */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET, 1 << request);

	/* Wait क्रम the acknowledge पूर्णांकerrupt */
	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO, val,
		val & (1 << ack), 100, 10000);

	अगर (ret)
		DRM_DEV_ERROR(gmu->dev,
			"Timeout waiting for GMU OOB set %s: 0x%x\n",
				a6xx_gmu_oob_bits[state].name,
				gmu_पढ़ो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_INFO));

	/* Clear the acknowledge पूर्णांकerrupt */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, 1 << ack);

	वापस ret;
पूर्ण

/* Clear a pending OOB state in the GMU */
व्योम a6xx_gmu_clear_oob(काष्ठा a6xx_gmu *gmu, क्रमागत a6xx_gmu_oob_state state)
अणु
	पूर्णांक bit;

	अगर (state >= ARRAY_SIZE(a6xx_gmu_oob_bits))
		वापस;

	अगर (gmu->legacy)
		bit = a6xx_gmu_oob_bits[state].clear;
	अन्यथा
		bit = a6xx_gmu_oob_bits[state].clear_new;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HOST2GMU_INTR_SET, 1 << bit);
पूर्ण

/* Enable CPU control of SPTP घातer घातer collapse */
अटल पूर्णांक a6xx_sptprac_enable(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (!gmu->legacy)
		वापस 0;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GX_SPTPRAC_POWER_CONTROL, 0x778000);

	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS, val,
		(val & 0x38) == 0x28, 1, 100);

	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev, "Unable to power on SPTPRAC: 0x%x\n",
			gmu_पढ़ो(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS));
	पूर्ण

	वापस 0;
पूर्ण

/* Disable CPU control of SPTP घातer घातer collapse */
अटल व्योम a6xx_sptprac_disable(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (!gmu->legacy)
		वापस;

	/* Make sure retention is on */
	gmu_rmw(gmu, REG_A6XX_GPU_CC_GX_GDSCR, 0, (1 << 11));

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GX_SPTPRAC_POWER_CONTROL, 0x778001);

	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS, val,
		(val & 0x04), 100, 10000);

	अगर (ret)
		DRM_DEV_ERROR(gmu->dev, "failed to power off SPTPRAC: 0x%x\n",
			gmu_पढ़ो(gmu, REG_A6XX_GMU_SPTPRAC_PWR_CLK_STATUS));
पूर्ण

/* Let the GMU know we are starting a boot sequence */
अटल पूर्णांक a6xx_gmu_gfx_rail_on(काष्ठा a6xx_gmu *gmu)
अणु
	u32 vote;

	/* Let the GMU know we are getting पढ़ोy क्रम boot */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_BOOT_SLUMBER_OPTION, 0);

	/* Choose the "default" घातer level as the highest available */
	vote = gmu->gx_arc_votes[gmu->nr_gpu_freqs - 1];

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GX_VOTE_IDX, vote & 0xff);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_MX_VOTE_IDX, (vote >> 8) & 0xff);

	/* Let the GMU know the boot sequence has started */
	वापस a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SLUMBER);
पूर्ण

/* Let the GMU know that we are about to go पूर्णांकo slumber */
अटल पूर्णांक a6xx_gmu_notअगरy_slumber(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret;

	/* Disable the घातer counter so the GMU isn't busy */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE, 0);

	/* Disable SPTP_PC अगर the CPU is responsible क्रम it */
	अगर (gmu->idle_level < GMU_IDLE_STATE_SPTP)
		a6xx_sptprac_disable(gmu);

	अगर (!gmu->legacy) अणु
		ret = a6xx_hfi_send_prep_slumber(gmu);
		जाओ out;
	पूर्ण

	/* Tell the GMU to get पढ़ोy to slumber */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_BOOT_SLUMBER_OPTION, 1);

	ret = a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SLUMBER);
	a6xx_gmu_clear_oob(gmu, GMU_OOB_BOOT_SLUMBER);

	अगर (!ret) अणु
		/* Check to see अगर the GMU really did slumber */
		अगर (gmu_पढ़ो(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE)
			!= 0x0f) अणु
			DRM_DEV_ERROR(gmu->dev, "The GMU did not go into slumber\n");
			ret = -ETIMEDOUT;
		पूर्ण
	पूर्ण

out:
	/* Put fence पूर्णांकo allow mode */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AO_AHB_FENCE_CTRL, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक a6xx_rpmh_start(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret;
	u32 val;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 1 << 1);
	/* Wait क्रम the रेजिस्टर to finish posting */
	wmb();

	ret = gmu_poll_समयout(gmu, REG_A6XX_GMU_RSCC_CONTROL_ACK, val,
		val & (1 << 1), 100, 10000);
	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev, "Unable to power on the GPU RSC\n");
		वापस ret;
	पूर्ण

	ret = gmu_poll_समयout_rscc(gmu, REG_A6XX_RSCC_SEQ_BUSY_DRV0, val,
		!val, 100, 10000);

	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev, "GPU RSC sequence stuck while waking up the GPU\n");
		वापस ret;
	पूर्ण

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 0);

	/* Set up CX GMU counter 0 to count busy ticks */
	gmu_ग_लिखो(gmu, REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_MASK, 0xff000000);
	gmu_rmw(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_SELECT_0, 0xff, 0x20);

	/* Enable the घातer counter */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CX_GMU_POWER_COUNTER_ENABLE, 1);
	वापस 0;
पूर्ण

अटल व्योम a6xx_rpmh_stop(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret;
	u32 val;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 1);

	ret = gmu_poll_समयout_rscc(gmu, REG_A6XX_GPU_RSCC_RSC_STATUS0_DRV0,
		val, val & (1 << 16), 100, 10000);
	अगर (ret)
		DRM_DEV_ERROR(gmu->dev, "Unable to power off the GPU RSC\n");

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_RSCC_CONTROL_REQ, 0);
पूर्ण

अटल अंतरभूत व्योम pdc_ग_लिखो(व्योम __iomem *ptr, u32 offset, u32 value)
अणु
	वापस msm_ग_लिखोl(value, ptr + (offset << 2));
पूर्ण

अटल व्योम __iomem *a6xx_gmu_get_mmio(काष्ठा platक्रमm_device *pdev,
		स्थिर अक्षर *name);

अटल व्योम a6xx_gmu_rpmh_init(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(gmu->dev);
	व्योम __iomem *pdcptr = a6xx_gmu_get_mmio(pdev, "gmu_pdc");
	व्योम __iomem *seqptr = a6xx_gmu_get_mmio(pdev, "gmu_pdc_seq");
	uपूर्णांक32_t pdc_address_offset;

	अगर (!pdcptr || !seqptr)
		जाओ err;

	अगर (adreno_is_a618(adreno_gpu) || adreno_is_a640(adreno_gpu))
		pdc_address_offset = 0x30090;
	अन्यथा अगर (adreno_is_a650(adreno_gpu))
		pdc_address_offset = 0x300a0;
	अन्यथा
		pdc_address_offset = 0x30080;

	/* Disable SDE घड़ी gating */
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_GPU_RSCC_RSC_STATUS0_DRV0, BIT(24));

	/* Setup RSC PDC handshake क्रम sleep and wakeup */
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_PDC_SLAVE_ID_DRV0, 1);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA + 2, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR + 2, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_DATA + 4, 0x80000000);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_HIDDEN_TCS_CMD0_ADDR + 4, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_OVERRIDE_START_ADDR, 0);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_PDC_SEQ_START_ADDR, 0x4520);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_PDC_MATCH_VALUE_LO, 0x4510);
	gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_PDC_MATCH_VALUE_HI, 0x4514);

	/* Load RSC sequencer uCode क्रम sleep and wakeup */
	अगर (adreno_is_a650(adreno_gpu)) अणु
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0, 0xeaaae5a0);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 1, 0xe1a1ebab);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 2, 0xa2e0a581);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 3, 0xecac82e2);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 4, 0x0020edad);
	पूर्ण अन्यथा अणु
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0, 0xa7a506a0);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 1, 0xa1e6a6e7);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 2, 0xa2e081e1);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 3, 0xe9a982e2);
		gmu_ग_लिखो_rscc(gmu, REG_A6XX_RSCC_SEQ_MEM_0_DRV0 + 4, 0x0020e8a8);
	पूर्ण

	/* Load PDC sequencer uCode क्रम घातer up and घातer करोwn sequence */
	pdc_ग_लिखो(seqptr, REG_A6XX_PDC_GPU_SEQ_MEM_0, 0xfebea1e1);
	pdc_ग_लिखो(seqptr, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 1, 0xa5a4a3a2);
	pdc_ग_लिखो(seqptr, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 2, 0x8382a6e0);
	pdc_ग_लिखो(seqptr, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 3, 0xbce3e284);
	pdc_ग_लिखो(seqptr, REG_A6XX_PDC_GPU_SEQ_MEM_0 + 4, 0x002081fc);

	/* Set TCS commands used by PDC sequence क्रम low घातer modes */
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD_ENABLE_BANK, 7);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD_WAIT_FOR_CMPL_BANK, 0);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CONTROL, 0);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR, 0x30010);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA, 1);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 4, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR + 4, 0x30000);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 4, 0x0);

	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_MSGID + 8, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_ADDR + 8, pdc_address_offset);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS1_CMD0_DATA + 8, 0x0);

	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD_ENABLE_BANK, 7);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD_WAIT_FOR_CMPL_BANK, 0);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CONTROL, 0);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR, 0x30010);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA, 2);

	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 4, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR + 4, 0x30000);
	अगर (adreno_is_a618(adreno_gpu) || adreno_is_a650(adreno_gpu))
		pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 4, 0x2);
	अन्यथा
		pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 4, 0x3);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_MSGID + 8, 0x10108);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_ADDR + 8, pdc_address_offset);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_TCS3_CMD0_DATA + 8, 0x3);

	/* Setup GPU PDC */
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_SEQ_START_ADDR, 0);
	pdc_ग_लिखो(pdcptr, REG_A6XX_PDC_GPU_ENABLE_PDC, 0x80000001);

	/* ensure no ग_लिखोs happen beक्रमe the uCode is fully written */
	wmb();

err:
	अगर (!IS_ERR_OR_शून्य(pdcptr))
		iounmap(pdcptr);
	अगर (!IS_ERR_OR_शून्य(seqptr))
		iounmap(seqptr);
पूर्ण

/*
 * The lowest 16 bits of this value are the number of XO घड़ी cycles क्रम मुख्य
 * hysteresis which is set at 0x1680 cycles (300 us).  The higher 16 bits are
 * क्रम the लघुer hysteresis that happens after मुख्य - this is 0xa (.5 us)
 */

#घोषणा GMU_PWR_COL_HYST 0x000a1680

/* Set up the idle state क्रम the GMU */
अटल व्योम a6xx_gmu_घातer_config(काष्ठा a6xx_gmu *gmu)
अणु
	/* Disable GMU WB/RB buffer */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_SYS_BUS_CONFIG, 0x1);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_ICACHE_CONFIG, 0x1);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_DCACHE_CONFIG, 0x1);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0x9c40400);

	चयन (gmu->idle_level) अणु
	हाल GMU_IDLE_STATE_IFPC:
		gmu_ग_लिखो(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_HYST,
			GMU_PWR_COL_HYST);
		gmu_rmw(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0,
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_IFPC_ENABLE |
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_HM_POWER_COLLAPSE_ENABLE);
		fallthrough;
	हाल GMU_IDLE_STATE_SPTP:
		gmu_ग_लिखो(gmu, REG_A6XX_GMU_PWR_COL_SPTPRAC_HYST,
			GMU_PWR_COL_HYST);
		gmu_rmw(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0,
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_IFPC_ENABLE |
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_SPTPRAC_POWER_CONTROL_ENABLE);
	पूर्ण

	/* Enable RPMh GPU client */
	gmu_rmw(gmu, REG_A6XX_GMU_RPMH_CTRL, 0,
		A6XX_GMU_RPMH_CTRL_RPMH_INTERFACE_ENABLE |
		A6XX_GMU_RPMH_CTRL_LLC_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_DDR_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_MX_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_CX_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_GFX_VOTE_ENABLE);
पूर्ण

काष्ठा block_header अणु
	u32 addr;
	u32 size;
	u32 type;
	u32 value;
	u32 data[];
पूर्ण;

/* this should be a general kernel helper */
अटल पूर्णांक in_range(u32 addr, u32 start, u32 size)
अणु
	वापस addr >= start && addr < start + size;
पूर्ण

अटल bool fw_block_mem(काष्ठा a6xx_gmu_bo *bo, स्थिर काष्ठा block_header *blk)
अणु
	अगर (!in_range(blk->addr, bo->iova, bo->size))
		वापस false;

	स_नकल(bo->virt + blk->addr - bo->iova, blk->data, blk->size);
	वापस true;
पूर्ण

अटल पूर्णांक a6xx_gmu_fw_load(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	स्थिर काष्ठा firmware *fw_image = adreno_gpu->fw[ADRENO_FW_GMU];
	स्थिर काष्ठा block_header *blk;
	u32 reg_offset;

	u32 itcm_base = 0x00000000;
	u32 dtcm_base = 0x00040000;

	अगर (adreno_is_a650(adreno_gpu))
		dtcm_base = 0x10004000;

	अगर (gmu->legacy) अणु
		/* Sanity check the size of the firmware that was loaded */
		अगर (fw_image->size > 0x8000) अणु
			DRM_DEV_ERROR(gmu->dev,
				"GMU firmware is bigger than the available region\n");
			वापस -EINVAL;
		पूर्ण

		gmu_ग_लिखो_bulk(gmu, REG_A6XX_GMU_CM3_ITCM_START,
			       (u32*) fw_image->data, fw_image->size);
		वापस 0;
	पूर्ण


	क्रम (blk = (स्थिर काष्ठा block_header *) fw_image->data;
	     (स्थिर u8*) blk < fw_image->data + fw_image->size;
	     blk = (स्थिर काष्ठा block_header *) &blk->data[blk->size >> 2]) अणु
		अगर (blk->size == 0)
			जारी;

		अगर (in_range(blk->addr, itcm_base, SZ_16K)) अणु
			reg_offset = (blk->addr - itcm_base) >> 2;
			gmu_ग_लिखो_bulk(gmu,
				REG_A6XX_GMU_CM3_ITCM_START + reg_offset,
				blk->data, blk->size);
		पूर्ण अन्यथा अगर (in_range(blk->addr, dtcm_base, SZ_16K)) अणु
			reg_offset = (blk->addr - dtcm_base) >> 2;
			gmu_ग_लिखो_bulk(gmu,
				REG_A6XX_GMU_CM3_DTCM_START + reg_offset,
				blk->data, blk->size);
		पूर्ण अन्यथा अगर (!fw_block_mem(&gmu->icache, blk) &&
			   !fw_block_mem(&gmu->dcache, blk) &&
			   !fw_block_mem(&gmu->dummy, blk)) अणु
			DRM_DEV_ERROR(gmu->dev,
				"failed to match fw block (addr=%.8x size=%d data[0]=%.8x)\n",
				blk->addr, blk->size, blk->data[0]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_gmu_fw_start(काष्ठा a6xx_gmu *gmu, अचिन्हित पूर्णांक state)
अणु
	अटल bool rpmh_init;
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	पूर्णांक ret;
	u32 chipid;

	अगर (adreno_is_a650(adreno_gpu))
		gmu_ग_लिखो(gmu, REG_A6XX_GPU_GMU_CX_GMU_CX_FAL_INTF, 1);

	अगर (state == GMU_WARM_BOOT) अणु
		ret = a6xx_rpmh_start(gmu);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (WARN(!adreno_gpu->fw[ADRENO_FW_GMU],
			"GMU firmware is not loaded\n"))
			वापस -ENOENT;

		/* Turn on रेजिस्टर retention */
		gmu_ग_लिखो(gmu, REG_A6XX_GMU_GENERAL_7, 1);

		/* We only need to load the RPMh microcode once */
		अगर (!rpmh_init) अणु
			a6xx_gmu_rpmh_init(gmu);
			rpmh_init = true;
		पूर्ण अन्यथा अणु
			ret = a6xx_rpmh_start(gmu);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = a6xx_gmu_fw_load(gmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CM3_FW_INIT_RESULT, 0);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_CM3_BOOT_CONFIG, 0x02);

	/* Write the iova of the HFI table */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HFI_QTBL_ADDR, gmu->hfi.iova);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HFI_QTBL_INFO, 1);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AHB_FENCE_RANGE_0,
		(1 << 31) | (0xa << 18) | (0xa0));

	chipid = adreno_gpu->rev.core << 24;
	chipid |= adreno_gpu->rev.major << 16;
	chipid |= adreno_gpu->rev.minor << 12;
	chipid |= adreno_gpu->rev.patchid << 8;

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_HFI_SFR_ADDR, chipid);

	gmu_ग_लिखो(gmu, REG_A6XX_GPU_GMU_CX_GMU_PWR_COL_CP_MSG,
		  gmu->log.iova | (gmu->log.size / SZ_4K - 1));

	/* Set up the lowest idle level on the GMU */
	a6xx_gmu_घातer_config(gmu);

	ret = a6xx_gmu_start(gmu);
	अगर (ret)
		वापस ret;

	अगर (gmu->legacy) अणु
		ret = a6xx_gmu_gfx_rail_on(gmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enable SPTP_PC अगर the CPU is responsible क्रम it */
	अगर (gmu->idle_level < GMU_IDLE_STATE_SPTP) अणु
		ret = a6xx_sptprac_enable(gmu);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = a6xx_gmu_hfi_start(gmu);
	अगर (ret)
		वापस ret;

	/* FIXME: Do we need this wmb() here? */
	wmb();

	वापस 0;
पूर्ण

#घोषणा A6XX_HFI_IRQ_MASK \
	(A6XX_GMU_GMU2HOST_INTR_INFO_CM3_FAULT)

#घोषणा A6XX_GMU_IRQ_MASK \
	(A6XX_GMU_AO_HOST_INTERRUPT_STATUS_WDOG_BITE | \
	 A6XX_GMU_AO_HOST_INTERRUPT_STATUS_HOST_AHB_BUS_ERROR | \
	 A6XX_GMU_AO_HOST_INTERRUPT_STATUS_FENCE_ERR)

अटल व्योम a6xx_gmu_irq_disable(काष्ठा a6xx_gmu *gmu)
अणु
	disable_irq(gmu->gmu_irq);
	disable_irq(gmu->hfi_irq);

	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK, ~0);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_MASK, ~0);
पूर्ण

अटल व्योम a6xx_gmu_rpmh_off(काष्ठा a6xx_gmu *gmu)
अणु
	u32 val;

	/* Make sure there are no outstanding RPMh votes */
	gmu_poll_समयout_rscc(gmu, REG_A6XX_RSCC_TCS0_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_समयout_rscc(gmu, REG_A6XX_RSCC_TCS1_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_समयout_rscc(gmu, REG_A6XX_RSCC_TCS2_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_समयout_rscc(gmu, REG_A6XX_RSCC_TCS3_DRV0_STATUS, val,
		(val & 1), 100, 1000);
पूर्ण

/* Force the GMU off in हाल it isn't responsive */
अटल व्योम a6xx_gmu_क्रमce_off(काष्ठा a6xx_gmu *gmu)
अणु
	/* Flush all the queues */
	a6xx_hfi_stop(gmu);

	/* Stop the पूर्णांकerrupts */
	a6xx_gmu_irq_disable(gmu);

	/* Force off SPTP in हाल the GMU is managing it */
	a6xx_sptprac_disable(gmu);

	/* Make sure there are no outstanding RPMh votes */
	a6xx_gmu_rpmh_off(gmu);
पूर्ण

अटल व्योम a6xx_gmu_set_initial_freq(काष्ठा msm_gpu *gpu, काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा dev_pm_opp *gpu_opp;
	अचिन्हित दीर्घ gpu_freq = gmu->gpu_freqs[gmu->current_perf_index];

	gpu_opp = dev_pm_opp_find_freq_exact(&gpu->pdev->dev, gpu_freq, true);
	अगर (IS_ERR_OR_शून्य(gpu_opp))
		वापस;

	gmu->freq = 0; /* so a6xx_gmu_set_freq() करोesn't निकास early */
	a6xx_gmu_set_freq(gpu, gpu_opp);
	dev_pm_opp_put(gpu_opp);
पूर्ण

अटल व्योम a6xx_gmu_set_initial_bw(काष्ठा msm_gpu *gpu, काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा dev_pm_opp *gpu_opp;
	अचिन्हित दीर्घ gpu_freq = gmu->gpu_freqs[gmu->current_perf_index];

	gpu_opp = dev_pm_opp_find_freq_exact(&gpu->pdev->dev, gpu_freq, true);
	अगर (IS_ERR_OR_शून्य(gpu_opp))
		वापस;

	dev_pm_opp_set_opp(&gpu->pdev->dev, gpu_opp);
	dev_pm_opp_put(gpu_opp);
पूर्ण

पूर्णांक a6xx_gmu_resume(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	पूर्णांक status, ret;

	अगर (WARN(!gmu->initialized, "The GMU is not set up yet\n"))
		वापस 0;

	gmu->hung = false;

	/* Turn on the resources */
	pm_runसमय_get_sync(gmu->dev);

	/*
	 * "enable" the GX घातer करोमुख्य which won't actually करो anything but it
	 * will make sure that the refcounting is correct in हाल we need to
	 * bring करोwn the GX after a GMU failure
	 */
	अगर (!IS_ERR_OR_शून्य(gmu->gxpd))
		pm_runसमय_get_sync(gmu->gxpd);

	/* Use a known rate to bring up the GMU */
	clk_set_rate(gmu->core_clk, 200000000);
	ret = clk_bulk_prepare_enable(gmu->nr_घड़ीs, gmu->घड़ीs);
	अगर (ret) अणु
		pm_runसमय_put(gmu->gxpd);
		pm_runसमय_put(gmu->dev);
		वापस ret;
	पूर्ण

	/* Set the bus quota to a reasonable value क्रम boot */
	a6xx_gmu_set_initial_bw(gpu, gmu);

	/* Enable the GMU पूर्णांकerrupt */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR, ~0);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK, ~A6XX_GMU_IRQ_MASK);
	enable_irq(gmu->gmu_irq);

	/* Check to see अगर we are करोing a cold or warm boot */
	status = gmu_पढ़ो(gmu, REG_A6XX_GMU_GENERAL_7) == 1 ?
		GMU_WARM_BOOT : GMU_COLD_BOOT;

	/*
	 * Warm boot path करोes not work on newer GPUs
	 * Presumably this is because icache/dcache regions must be restored
	 */
	अगर (!gmu->legacy)
		status = GMU_COLD_BOOT;

	ret = a6xx_gmu_fw_start(gmu, status);
	अगर (ret)
		जाओ out;

	ret = a6xx_hfi_start(gmu, status);
	अगर (ret)
		जाओ out;

	/*
	 * Turn on the GMU firmware fault पूर्णांकerrupt after we know the boot
	 * sequence is successful
	 */
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, ~0);
	gmu_ग_लिखो(gmu, REG_A6XX_GMU_GMU2HOST_INTR_MASK, ~A6XX_HFI_IRQ_MASK);
	enable_irq(gmu->hfi_irq);

	/* Set the GPU to the current freq */
	a6xx_gmu_set_initial_freq(gpu, gmu);

out:
	/* On failure, shut करोwn the GMU to leave it in a good state */
	अगर (ret) अणु
		disable_irq(gmu->gmu_irq);
		a6xx_rpmh_stop(gmu);
		pm_runसमय_put(gmu->gxpd);
		pm_runसमय_put(gmu->dev);
	पूर्ण

	वापस ret;
पूर्ण

bool a6xx_gmu_isidle(काष्ठा a6xx_gmu *gmu)
अणु
	u32 reg;

	अगर (!gmu->initialized)
		वापस true;

	reg = gmu_पढ़ो(gmu, REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS);

	अगर (reg &  A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB)
		वापस false;

	वापस true;
पूर्ण

#घोषणा GBIF_CLIENT_HALT_MASK             BIT(0)
#घोषणा GBIF_ARB_HALT_MASK                BIT(1)

अटल व्योम a6xx_bus_clear_pending_transactions(काष्ठा adreno_gpu *adreno_gpu)
अणु
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;

	अगर (!a6xx_has_gbअगर(adreno_gpu)) अणु
		gpu_ग_लिखो(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL0, 0xf);
		spin_until((gpu_पढ़ो(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL1) &
								0xf) == 0xf);
		gpu_ग_लिखो(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL0, 0);

		वापस;
	पूर्ण

	/* Halt new client requests on GBIF */
	gpu_ग_लिखो(gpu, REG_A6XX_GBIF_HALT, GBIF_CLIENT_HALT_MASK);
	spin_until((gpu_पढ़ो(gpu, REG_A6XX_GBIF_HALT_ACK) &
			(GBIF_CLIENT_HALT_MASK)) == GBIF_CLIENT_HALT_MASK);

	/* Halt all AXI requests on GBIF */
	gpu_ग_लिखो(gpu, REG_A6XX_GBIF_HALT, GBIF_ARB_HALT_MASK);
	spin_until((gpu_पढ़ो(gpu,  REG_A6XX_GBIF_HALT_ACK) &
			(GBIF_ARB_HALT_MASK)) == GBIF_ARB_HALT_MASK);

	/* The GBIF halt needs to be explicitly cleared */
	gpu_ग_लिखो(gpu, REG_A6XX_GBIF_HALT, 0x0);
पूर्ण

/* Gracefully try to shut करोwn the GMU and by extension the GPU */
अटल व्योम a6xx_gmu_shutकरोwn(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	u32 val;

	/*
	 * The GMU may still be in slumber unless the GPU started so check and
	 * skip putting it back पूर्णांकo slumber अगर so
	 */
	val = gmu_पढ़ो(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE);

	अगर (val != 0xf) अणु
		पूर्णांक ret = a6xx_gmu_रुको_क्रम_idle(gmu);

		/* If the GMU isn't responding assume it is hung */
		अगर (ret) अणु
			a6xx_gmu_क्रमce_off(gmu);
			वापस;
		पूर्ण

		a6xx_bus_clear_pending_transactions(adreno_gpu);

		/* tell the GMU we want to slumber */
		a6xx_gmu_notअगरy_slumber(gmu);

		ret = gmu_poll_समयout(gmu,
			REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS, val,
			!(val & A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB),
			100, 10000);

		/*
		 * Let the user know we failed to slumber but करोn't worry too
		 * much because we are घातering करोwn anyway
		 */

		अगर (ret)
			DRM_DEV_ERROR(gmu->dev,
				"Unable to slumber GMU: status = 0%x/0%x\n",
				gmu_पढ़ो(gmu,
					REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS),
				gmu_पढ़ो(gmu,
					REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS2));
	पूर्ण

	/* Turn off HFI */
	a6xx_hfi_stop(gmu);

	/* Stop the पूर्णांकerrupts and mask the hardware */
	a6xx_gmu_irq_disable(gmu);

	/* Tell RPMh to घातer off the GPU */
	a6xx_rpmh_stop(gmu);
पूर्ण


पूर्णांक a6xx_gmu_stop(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	काष्ठा msm_gpu *gpu = &a6xx_gpu->base.base;

	अगर (!pm_runसमय_active(gmu->dev))
		वापस 0;

	/*
	 * Force the GMU off अगर we detected a hang, otherwise try to shut it
	 * करोwn gracefully
	 */
	अगर (gmu->hung)
		a6xx_gmu_क्रमce_off(gmu);
	अन्यथा
		a6xx_gmu_shutकरोwn(gmu);

	/* Remove the bus vote */
	dev_pm_opp_set_opp(&gpu->pdev->dev, शून्य);

	/*
	 * Make sure the GX करोमुख्य is off beक्रमe turning off the GMU (CX)
	 * करोमुख्य. Usually the GMU करोes this but only अगर the shutकरोwn sequence
	 * was successful
	 */
	अगर (!IS_ERR_OR_शून्य(gmu->gxpd))
		pm_runसमय_put_sync(gmu->gxpd);

	clk_bulk_disable_unprepare(gmu->nr_घड़ीs, gmu->घड़ीs);

	pm_runसमय_put_sync(gmu->dev);

	वापस 0;
पूर्ण

अटल व्योम a6xx_gmu_memory_मुक्त(काष्ठा a6xx_gmu *gmu)
अणु
	msm_gem_kernel_put(gmu->hfi.obj, gmu->aspace, false);
	msm_gem_kernel_put(gmu->debug.obj, gmu->aspace, false);
	msm_gem_kernel_put(gmu->icache.obj, gmu->aspace, false);
	msm_gem_kernel_put(gmu->dcache.obj, gmu->aspace, false);
	msm_gem_kernel_put(gmu->dummy.obj, gmu->aspace, false);
	msm_gem_kernel_put(gmu->log.obj, gmu->aspace, false);

	gmu->aspace->mmu->funcs->detach(gmu->aspace->mmu);
	msm_gem_address_space_put(gmu->aspace);
पूर्ण

अटल पूर्णांक a6xx_gmu_memory_alloc(काष्ठा a6xx_gmu *gmu, काष्ठा a6xx_gmu_bo *bo,
		माप_प्रकार size, u64 iova)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा drm_device *dev = a6xx_gpu->base.base.dev;
	uपूर्णांक32_t flags = MSM_BO_WC;
	u64 range_start, range_end;
	पूर्णांक ret;

	size = PAGE_ALIGN(size);
	अगर (!iova) अणु
		/* no fixed address - use GMU's uncached range */
		range_start = 0x60000000 + PAGE_SIZE; /* skip dummy page */
		range_end = 0x80000000;
	पूर्ण अन्यथा अणु
		/* range क्रम fixed address */
		range_start = iova;
		range_end = iova + size;
		/* use IOMMU_PRIV क्रम icache/dcache */
		flags |= MSM_BO_MAP_PRIV;
	पूर्ण

	bo->obj = msm_gem_new(dev, size, flags);
	अगर (IS_ERR(bo->obj))
		वापस PTR_ERR(bo->obj);

	ret = msm_gem_get_and_pin_iova_range(bo->obj, gmu->aspace, &bo->iova,
		range_start >> PAGE_SHIFT, range_end >> PAGE_SHIFT);
	अगर (ret) अणु
		drm_gem_object_put(bo->obj);
		वापस ret;
	पूर्ण

	bo->virt = msm_gem_get_vaddr(bo->obj);
	bo->size = size;

	वापस 0;
पूर्ण

अटल पूर्णांक a6xx_gmu_memory_probe(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा msm_mmu *mmu;

	करोमुख्य = iommu_करोमुख्य_alloc(&platक्रमm_bus_type);
	अगर (!करोमुख्य)
		वापस -ENODEV;

	mmu = msm_iommu_new(gmu->dev, करोमुख्य);
	gmu->aspace = msm_gem_address_space_create(mmu, "gmu", 0x0, 0x80000000);
	अगर (IS_ERR(gmu->aspace)) अणु
		iommu_करोमुख्य_मुक्त(करोमुख्य);
		वापस PTR_ERR(gmu->aspace);
	पूर्ण

	वापस 0;
पूर्ण

/* Return the 'arc-level' क्रम the given frequency */
अटल अचिन्हित पूर्णांक a6xx_gmu_get_arc_level(काष्ठा device *dev,
					   अचिन्हित दीर्घ freq)
अणु
	काष्ठा dev_pm_opp *opp;
	अचिन्हित पूर्णांक val;

	अगर (!freq)
		वापस 0;

	opp = dev_pm_opp_find_freq_exact(dev, freq, true);
	अगर (IS_ERR(opp))
		वापस 0;

	val = dev_pm_opp_get_level(opp);

	dev_pm_opp_put(opp);

	वापस val;
पूर्ण

अटल पूर्णांक a6xx_gmu_rpmh_arc_votes_init(काष्ठा device *dev, u32 *votes,
		अचिन्हित दीर्घ *freqs, पूर्णांक freqs_count, स्थिर अक्षर *id)
अणु
	पूर्णांक i, j;
	स्थिर u16 *pri, *sec;
	माप_प्रकार pri_count, sec_count;

	pri = cmd_db_पढ़ो_aux_data(id, &pri_count);
	अगर (IS_ERR(pri))
		वापस PTR_ERR(pri);
	/*
	 * The data comes back as an array of अचिन्हित लघुs so adjust the
	 * count accordingly
	 */
	pri_count >>= 1;
	अगर (!pri_count)
		वापस -EINVAL;

	sec = cmd_db_पढ़ो_aux_data("mx.lvl", &sec_count);
	अगर (IS_ERR(sec))
		वापस PTR_ERR(sec);

	sec_count >>= 1;
	अगर (!sec_count)
		वापस -EINVAL;

	/* Conकाष्ठा a vote क्रम each frequency */
	क्रम (i = 0; i < freqs_count; i++) अणु
		u8 pindex = 0, sindex = 0;
		अचिन्हित पूर्णांक level = a6xx_gmu_get_arc_level(dev, freqs[i]);

		/* Get the primary index that matches the arc level */
		क्रम (j = 0; j < pri_count; j++) अणु
			अगर (pri[j] >= level) अणु
				pindex = j;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j == pri_count) अणु
			DRM_DEV_ERROR(dev,
				      "Level %u not found in the RPMh list\n",
				      level);
			DRM_DEV_ERROR(dev, "Available levels:\n");
			क्रम (j = 0; j < pri_count; j++)
				DRM_DEV_ERROR(dev, "  %u\n", pri[j]);

			वापस -EINVAL;
		पूर्ण

		/*
		 * Look क्रम a level in in the secondary list that matches. If
		 * nothing fits, use the maximum non zero vote
		 */

		क्रम (j = 0; j < sec_count; j++) अणु
			अगर (sec[j] >= level) अणु
				sindex = j;
				अवरोध;
			पूर्ण अन्यथा अगर (sec[j]) अणु
				sindex = j;
			पूर्ण
		पूर्ण

		/* Conकाष्ठा the vote */
		votes[i] = ((pri[pindex] & 0xffff) << 16) |
			(sindex << 8) | pindex;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The GMU votes with the RPMh क्रम itself and on behalf of the GPU but we need
 * to स्थिरruct the list of votes on the CPU and send it over. Query the RPMh
 * voltage levels and build the votes
 */

अटल पूर्णांक a6xx_gmu_rpmh_votes_init(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	पूर्णांक ret;

	/* Build the GX votes */
	ret = a6xx_gmu_rpmh_arc_votes_init(&gpu->pdev->dev, gmu->gx_arc_votes,
		gmu->gpu_freqs, gmu->nr_gpu_freqs, "gfx.lvl");

	/* Build the CX votes */
	ret |= a6xx_gmu_rpmh_arc_votes_init(gmu->dev, gmu->cx_arc_votes,
		gmu->gmu_freqs, gmu->nr_gmu_freqs, "cx.lvl");

	वापस ret;
पूर्ण

अटल पूर्णांक a6xx_gmu_build_freq_table(काष्ठा device *dev, अचिन्हित दीर्घ *freqs,
		u32 size)
अणु
	पूर्णांक count = dev_pm_opp_get_opp_count(dev);
	काष्ठा dev_pm_opp *opp;
	पूर्णांक i, index = 0;
	अचिन्हित दीर्घ freq = 1;

	/*
	 * The OPP table करोesn't contain the "off" frequency level so we need to
	 * add 1 to the table size to account क्रम it
	 */

	अगर (WARN(count + 1 > size,
		"The GMU frequency table is being truncated\n"))
		count = size - 1;

	/* Set the "off" frequency */
	freqs[index++] = 0;

	क्रम (i = 0; i < count; i++) अणु
		opp = dev_pm_opp_find_freq_उच्चमान(dev, &freq);
		अगर (IS_ERR(opp))
			अवरोध;

		dev_pm_opp_put(opp);
		freqs[index++] = freq++;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक a6xx_gmu_pwrlevels_probe(काष्ठा a6xx_gmu *gmu)
अणु
	काष्ठा a6xx_gpu *a6xx_gpu = container_of(gmu, काष्ठा a6xx_gpu, gmu);
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;

	पूर्णांक ret = 0;

	/*
	 * The GMU handles its own frequency चयनing so build a list of
	 * available frequencies to send during initialization
	 */
	ret = dev_pm_opp_of_add_table(gmu->dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(gmu->dev, "Unable to set the OPP table for the GMU\n");
		वापस ret;
	पूर्ण

	gmu->nr_gmu_freqs = a6xx_gmu_build_freq_table(gmu->dev,
		gmu->gmu_freqs, ARRAY_SIZE(gmu->gmu_freqs));

	/*
	 * The GMU also handles GPU frequency चयनing so build a list
	 * from the GPU OPP table
	 */
	gmu->nr_gpu_freqs = a6xx_gmu_build_freq_table(&gpu->pdev->dev,
		gmu->gpu_freqs, ARRAY_SIZE(gmu->gpu_freqs));

	gmu->current_perf_index = gmu->nr_gpu_freqs - 1;

	/* Build the list of RPMh votes that we'll send to the GMU */
	वापस a6xx_gmu_rpmh_votes_init(gmu);
पूर्ण

अटल पूर्णांक a6xx_gmu_घड़ीs_probe(काष्ठा a6xx_gmu *gmu)
अणु
	पूर्णांक ret = devm_clk_bulk_get_all(gmu->dev, &gmu->घड़ीs);

	अगर (ret < 1)
		वापस ret;

	gmu->nr_घड़ीs = ret;

	gmu->core_clk = msm_clk_bulk_get_घड़ी(gmu->घड़ीs,
		gmu->nr_घड़ीs, "gmu");

	वापस 0;
पूर्ण

अटल व्योम __iomem *a6xx_gmu_get_mmio(काष्ठा platक्रमm_device *pdev,
		स्थिर अक्षर *name)
अणु
	व्योम __iomem *ret;
	काष्ठा resource *res = platक्रमm_get_resource_byname(pdev,
			IORESOURCE_MEM, name);

	अगर (!res) अणु
		DRM_DEV_ERROR(&pdev->dev, "Unable to find the %s registers\n", name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = ioremap(res->start, resource_size(res));
	अगर (!ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "Unable to map the %s registers\n", name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक a6xx_gmu_get_irq(काष्ठा a6xx_gmu *gmu, काष्ठा platक्रमm_device *pdev,
		स्थिर अक्षर *name, irq_handler_t handler)
अणु
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq_byname(pdev, name);

	ret = request_irq(irq, handler, IRQF_TRIGGER_HIGH, name, gmu);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "Unable to get interrupt %s %d\n",
			      name, ret);
		वापस ret;
	पूर्ण

	disable_irq(irq);

	वापस irq;
पूर्ण

व्योम a6xx_gmu_हटाओ(काष्ठा a6xx_gpu *a6xx_gpu)
अणु
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(gmu->dev);

	अगर (!gmu->initialized)
		वापस;

	pm_runसमय_क्रमce_suspend(gmu->dev);

	अगर (!IS_ERR_OR_शून्य(gmu->gxpd)) अणु
		pm_runसमय_disable(gmu->gxpd);
		dev_pm_करोमुख्य_detach(gmu->gxpd, false);
	पूर्ण

	iounmap(gmu->mmio);
	अगर (platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rscc"))
		iounmap(gmu->rscc);
	gmu->mmio = शून्य;
	gmu->rscc = शून्य;

	a6xx_gmu_memory_मुक्त(gmu);

	मुक्त_irq(gmu->gmu_irq, gmu);
	मुक्त_irq(gmu->hfi_irq, gmu);

	/* Drop reference taken in of_find_device_by_node */
	put_device(gmu->dev);

	gmu->initialized = false;
पूर्ण

पूर्णांक a6xx_gmu_init(काष्ठा a6xx_gpu *a6xx_gpu, काष्ठा device_node *node)
अणु
	काष्ठा adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	काष्ठा a6xx_gmu *gmu = &a6xx_gpu->gmu;
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(node);
	पूर्णांक ret;

	अगर (!pdev)
		वापस -ENODEV;

	gmu->dev = &pdev->dev;

	of_dma_configure(gmu->dev, node, true);

	/* Fow now, करोn't करो anything fancy until we get our feet under us */
	gmu->idle_level = GMU_IDLE_STATE_ACTIVE;

	pm_runसमय_enable(gmu->dev);

	/* Get the list of घड़ीs */
	ret = a6xx_gmu_घड़ीs_probe(gmu);
	अगर (ret)
		जाओ err_put_device;

	ret = a6xx_gmu_memory_probe(gmu);
	अगर (ret)
		जाओ err_put_device;

	/* Allocate memory क्रम the GMU dummy page */
	ret = a6xx_gmu_memory_alloc(gmu, &gmu->dummy, SZ_4K, 0x60000000);
	अगर (ret)
		जाओ err_memory;

	अगर (adreno_is_a650(adreno_gpu)) अणु
		ret = a6xx_gmu_memory_alloc(gmu, &gmu->icache,
			SZ_16M - SZ_16K, 0x04000);
		अगर (ret)
			जाओ err_memory;
	पूर्ण अन्यथा अगर (adreno_is_a640(adreno_gpu)) अणु
		ret = a6xx_gmu_memory_alloc(gmu, &gmu->icache,
			SZ_256K - SZ_16K, 0x04000);
		अगर (ret)
			जाओ err_memory;

		ret = a6xx_gmu_memory_alloc(gmu, &gmu->dcache,
			SZ_256K - SZ_16K, 0x44000);
		अगर (ret)
			जाओ err_memory;
	पूर्ण अन्यथा अणु
		/* HFI v1, has sptprac */
		gmu->legacy = true;

		/* Allocate memory क्रम the GMU debug region */
		ret = a6xx_gmu_memory_alloc(gmu, &gmu->debug, SZ_16K, 0);
		अगर (ret)
			जाओ err_memory;
	पूर्ण

	/* Allocate memory क्रम क्रम the HFI queues */
	ret = a6xx_gmu_memory_alloc(gmu, &gmu->hfi, SZ_16K, 0);
	अगर (ret)
		जाओ err_memory;

	/* Allocate memory क्रम the GMU log region */
	ret = a6xx_gmu_memory_alloc(gmu, &gmu->log, SZ_4K, 0);
	अगर (ret)
		जाओ err_memory;

	/* Map the GMU रेजिस्टरs */
	gmu->mmio = a6xx_gmu_get_mmio(pdev, "gmu");
	अगर (IS_ERR(gmu->mmio)) अणु
		ret = PTR_ERR(gmu->mmio);
		जाओ err_memory;
	पूर्ण

	अगर (adreno_is_a650(adreno_gpu)) अणु
		gmu->rscc = a6xx_gmu_get_mmio(pdev, "rscc");
		अगर (IS_ERR(gmu->rscc))
			जाओ err_mmio;
	पूर्ण अन्यथा अणु
		gmu->rscc = gmu->mmio + 0x23000;
	पूर्ण

	/* Get the HFI and GMU पूर्णांकerrupts */
	gmu->hfi_irq = a6xx_gmu_get_irq(gmu, pdev, "hfi", a6xx_hfi_irq);
	gmu->gmu_irq = a6xx_gmu_get_irq(gmu, pdev, "gmu", a6xx_gmu_irq);

	अगर (gmu->hfi_irq < 0 || gmu->gmu_irq < 0)
		जाओ err_mmio;

	/*
	 * Get a link to the GX घातer करोमुख्य to reset the GPU in हाल of GMU
	 * crash
	 */
	gmu->gxpd = dev_pm_करोमुख्य_attach_by_name(gmu->dev, "gx");

	/* Get the घातer levels क्रम the GMU and GPU */
	a6xx_gmu_pwrlevels_probe(gmu);

	/* Set up the HFI queues */
	a6xx_hfi_init(gmu);

	gmu->initialized = true;

	वापस 0;

err_mmio:
	iounmap(gmu->mmio);
	अगर (platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rscc"))
		iounmap(gmu->rscc);
	मुक्त_irq(gmu->gmu_irq, gmu);
	मुक्त_irq(gmu->hfi_irq, gmu);

	ret = -ENODEV;

err_memory:
	a6xx_gmu_memory_मुक्त(gmu);
err_put_device:
	/* Drop reference taken in of_find_device_by_node */
	put_device(gmu->dev);

	वापस ret;
पूर्ण
