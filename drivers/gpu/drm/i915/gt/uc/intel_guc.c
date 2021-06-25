<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_irq.h"
#समावेश "gt/intel_gt_pm_irq.h"
#समावेश "intel_guc.h"
#समावेश "intel_guc_ads.h"
#समावेश "intel_guc_submission.h"
#समावेश "i915_drv.h"

/**
 * DOC: GuC
 *
 * The GuC is a microcontroller inside the GT HW, पूर्णांकroduced in gen9. The GuC is
 * deचिन्हित to offload some of the functionality usually perक्रमmed by the host
 * driver; currently the मुख्य operations it can take care of are:
 *
 * - Authentication of the HuC, which is required to fully enable HuC usage.
 * - Low latency graphics context scheduling (a.k.a. GuC submission).
 * - GT Power management.
 *
 * The enable_guc module parameter can be used to select which of those
 * operations to enable within GuC. Note that not all the operations are
 * supported on all gen9+ platक्रमms.
 *
 * Enabling the GuC is not mandatory and thereक्रमe the firmware is only loaded
 * अगर at least one of the operations is selected. However, not loading the GuC
 * might result in the loss of some features that करो require the GuC (currently
 * just the HuC, but more are expected to land in the future).
 */

व्योम पूर्णांकel_guc_notअगरy(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	/*
	 * On Gen11+, the value written to the रेजिस्टर is passes as a payload
	 * to the FW. However, the FW currently treats all values the same way
	 * (H2G पूर्णांकerrupt), so we can just ग_लिखो the value that the HW expects
	 * on older gens.
	 */
	पूर्णांकel_uncore_ग_लिखो(gt->uncore, guc->notअगरy_reg, GUC_SEND_TRIGGER);
पूर्ण

अटल अंतरभूत i915_reg_t guc_send_reg(काष्ठा पूर्णांकel_guc *guc, u32 i)
अणु
	GEM_BUG_ON(!guc->send_regs.base);
	GEM_BUG_ON(!guc->send_regs.count);
	GEM_BUG_ON(i >= guc->send_regs.count);

	वापस _MMIO(guc->send_regs.base + 4 * i);
पूर्ण

व्योम पूर्णांकel_guc_init_send_regs(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	क्रमागत क्रमcewake_करोमुख्यs fw_करोमुख्यs = 0;
	अचिन्हित पूर्णांक i;

	अगर (INTEL_GEN(gt->i915) >= 11) अणु
		guc->send_regs.base =
				i915_mmio_reg_offset(GEN11_SOFT_SCRATCH(0));
		guc->send_regs.count = GEN11_SOFT_SCRATCH_COUNT;
	पूर्ण अन्यथा अणु
		guc->send_regs.base = i915_mmio_reg_offset(SOFT_SCRATCH(0));
		guc->send_regs.count = GUC_MAX_MMIO_MSG_LEN;
		BUILD_BUG_ON(GUC_MAX_MMIO_MSG_LEN > SOFT_SCRATCH_COUNT);
	पूर्ण

	क्रम (i = 0; i < guc->send_regs.count; i++) अणु
		fw_करोमुख्यs |= पूर्णांकel_uncore_क्रमcewake_क्रम_reg(gt->uncore,
					guc_send_reg(guc, i),
					FW_REG_READ | FW_REG_WRITE);
	पूर्ण
	guc->send_regs.fw_करोमुख्यs = fw_करोमुख्यs;
पूर्ण

अटल व्योम gen9_reset_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	निश्चित_rpm_wakelock_held(&gt->i915->runसमय_pm);

	spin_lock_irq(&gt->irq_lock);
	gen6_gt_pm_reset_iir(gt, gt->pm_guc_events);
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

अटल व्योम gen9_enable_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	निश्चित_rpm_wakelock_held(&gt->i915->runसमय_pm);

	spin_lock_irq(&gt->irq_lock);
	अगर (!guc->पूर्णांकerrupts.enabled) अणु
		WARN_ON_ONCE(पूर्णांकel_uncore_पढ़ो(gt->uncore, GEN8_GT_IIR(2)) &
			     gt->pm_guc_events);
		guc->पूर्णांकerrupts.enabled = true;
		gen6_gt_pm_enable_irq(gt, gt->pm_guc_events);
	पूर्ण
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

अटल व्योम gen9_disable_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	निश्चित_rpm_wakelock_held(&gt->i915->runसमय_pm);

	spin_lock_irq(&gt->irq_lock);
	guc->पूर्णांकerrupts.enabled = false;

	gen6_gt_pm_disable_irq(gt, gt->pm_guc_events);

	spin_unlock_irq(&gt->irq_lock);
	पूर्णांकel_synchronize_irq(gt->i915);

	gen9_reset_guc_पूर्णांकerrupts(guc);
पूर्ण

अटल व्योम gen11_reset_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	gen11_gt_reset_one_iir(gt, 0, GEN11_GUC);
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

अटल व्योम gen11_enable_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	अगर (!guc->पूर्णांकerrupts.enabled) अणु
		u32 events = REG_FIELD_PREP(ENGINE1_MASK, GUC_INTR_GUC2HOST);

		WARN_ON_ONCE(gen11_gt_reset_one_iir(gt, 0, GEN11_GUC));
		पूर्णांकel_uncore_ग_लिखो(gt->uncore,
				   GEN11_GUC_SG_INTR_ENABLE, events);
		पूर्णांकel_uncore_ग_लिखो(gt->uncore,
				   GEN11_GUC_SG_INTR_MASK, ~events);
		guc->पूर्णांकerrupts.enabled = true;
	पूर्ण
	spin_unlock_irq(&gt->irq_lock);
पूर्ण

अटल व्योम gen11_disable_guc_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	guc->पूर्णांकerrupts.enabled = false;

	पूर्णांकel_uncore_ग_लिखो(gt->uncore, GEN11_GUC_SG_INTR_MASK, ~0);
	पूर्णांकel_uncore_ग_लिखो(gt->uncore, GEN11_GUC_SG_INTR_ENABLE, 0);

	spin_unlock_irq(&gt->irq_lock);
	पूर्णांकel_synchronize_irq(gt->i915);

	gen11_reset_guc_पूर्णांकerrupts(guc);
पूर्ण

व्योम पूर्णांकel_guc_init_early(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा drm_i915_निजी *i915 = guc_to_gt(guc)->i915;

	पूर्णांकel_uc_fw_init_early(&guc->fw, INTEL_UC_FW_TYPE_GUC);
	पूर्णांकel_guc_ct_init_early(&guc->ct);
	पूर्णांकel_guc_log_init_early(&guc->log);
	पूर्णांकel_guc_submission_init_early(guc);

	mutex_init(&guc->send_mutex);
	spin_lock_init(&guc->irq_lock);
	अगर (INTEL_GEN(i915) >= 11) अणु
		guc->notअगरy_reg = GEN11_GUC_HOST_INTERRUPT;
		guc->पूर्णांकerrupts.reset = gen11_reset_guc_पूर्णांकerrupts;
		guc->पूर्णांकerrupts.enable = gen11_enable_guc_पूर्णांकerrupts;
		guc->पूर्णांकerrupts.disable = gen11_disable_guc_पूर्णांकerrupts;
	पूर्ण अन्यथा अणु
		guc->notअगरy_reg = GUC_SEND_INTERRUPT;
		guc->पूर्णांकerrupts.reset = gen9_reset_guc_पूर्णांकerrupts;
		guc->पूर्णांकerrupts.enable = gen9_enable_guc_पूर्णांकerrupts;
		guc->पूर्णांकerrupts.disable = gen9_disable_guc_पूर्णांकerrupts;
	पूर्ण
पूर्ण

अटल u32 guc_ctl_debug_flags(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 level = पूर्णांकel_guc_log_get_level(&guc->log);
	u32 flags = 0;

	अगर (!GUC_LOG_LEVEL_IS_VERBOSE(level))
		flags |= GUC_LOG_DISABLED;
	अन्यथा
		flags |= GUC_LOG_LEVEL_TO_VERBOSITY(level) <<
			 GUC_LOG_VERBOSITY_SHIFT;

	वापस flags;
पूर्ण

अटल u32 guc_ctl_feature_flags(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 flags = 0;

	अगर (!पूर्णांकel_guc_submission_is_used(guc))
		flags |= GUC_CTL_DISABLE_SCHEDULER;

	वापस flags;
पूर्ण

अटल u32 guc_ctl_log_params_flags(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 offset = पूर्णांकel_guc_ggtt_offset(guc, guc->log.vma) >> PAGE_SHIFT;
	u32 flags;

	#अगर (((CRASH_BUFFER_SIZE) % SZ_1M) == 0)
	#घोषणा UNIT SZ_1M
	#घोषणा FLAG GUC_LOG_ALLOC_IN_MEGABYTE
	#अन्यथा
	#घोषणा UNIT SZ_4K
	#घोषणा FLAG 0
	#पूर्ण_अगर

	BUILD_BUG_ON(!CRASH_BUFFER_SIZE);
	BUILD_BUG_ON(!IS_ALIGNED(CRASH_BUFFER_SIZE, UNIT));
	BUILD_BUG_ON(!DPC_BUFFER_SIZE);
	BUILD_BUG_ON(!IS_ALIGNED(DPC_BUFFER_SIZE, UNIT));
	BUILD_BUG_ON(!ISR_BUFFER_SIZE);
	BUILD_BUG_ON(!IS_ALIGNED(ISR_BUFFER_SIZE, UNIT));

	BUILD_BUG_ON((CRASH_BUFFER_SIZE / UNIT - 1) >
			(GUC_LOG_CRASH_MASK >> GUC_LOG_CRASH_SHIFT));
	BUILD_BUG_ON((DPC_BUFFER_SIZE / UNIT - 1) >
			(GUC_LOG_DPC_MASK >> GUC_LOG_DPC_SHIFT));
	BUILD_BUG_ON((ISR_BUFFER_SIZE / UNIT - 1) >
			(GUC_LOG_ISR_MASK >> GUC_LOG_ISR_SHIFT));

	flags = GUC_LOG_VALID |
		GUC_LOG_NOTIFY_ON_HALF_FULL |
		FLAG |
		((CRASH_BUFFER_SIZE / UNIT - 1) << GUC_LOG_CRASH_SHIFT) |
		((DPC_BUFFER_SIZE / UNIT - 1) << GUC_LOG_DPC_SHIFT) |
		((ISR_BUFFER_SIZE / UNIT - 1) << GUC_LOG_ISR_SHIFT) |
		(offset << GUC_LOG_BUF_ADDR_SHIFT);

	#अघोषित UNIT
	#अघोषित FLAG

	वापस flags;
पूर्ण

अटल u32 guc_ctl_ads_flags(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 ads = पूर्णांकel_guc_ggtt_offset(guc, guc->ads_vma) >> PAGE_SHIFT;
	u32 flags = ads << GUC_ADS_ADDR_SHIFT;

	वापस flags;
पूर्ण

/*
 * Initialise the GuC parameter block beक्रमe starting the firmware
 * transfer. These parameters are पढ़ो by the firmware on startup
 * and cannot be changed thereafter.
 */
अटल व्योम guc_init_params(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 *params = guc->params;
	पूर्णांक i;

	BUILD_BUG_ON(माप(guc->params) != GUC_CTL_MAX_DWORDS * माप(u32));

	params[GUC_CTL_LOG_PARAMS] = guc_ctl_log_params_flags(guc);
	params[GUC_CTL_FEATURE] = guc_ctl_feature_flags(guc);
	params[GUC_CTL_DEBUG] = guc_ctl_debug_flags(guc);
	params[GUC_CTL_ADS] = guc_ctl_ads_flags(guc);

	क्रम (i = 0; i < GUC_CTL_MAX_DWORDS; i++)
		DRM_DEBUG_DRIVER("param[%2d] = %#x\n", i, params[i]);
पूर्ण

/*
 * Initialise the GuC parameter block beक्रमe starting the firmware
 * transfer. These parameters are पढ़ो by the firmware on startup
 * and cannot be changed thereafter.
 */
व्योम पूर्णांकel_guc_ग_लिखो_params(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = guc_to_gt(guc)->uncore;
	पूर्णांक i;

	/*
	 * All SOFT_SCRATCH रेजिस्टरs are in FORCEWAKE_GT करोमुख्य and
	 * they are घातer context saved so it's ok to release क्रमcewake
	 * when we are करोne here and take it again at xfer समय.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_GT);

	पूर्णांकel_uncore_ग_लिखो(uncore, SOFT_SCRATCH(0), 0);

	क्रम (i = 0; i < GUC_CTL_MAX_DWORDS; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, SOFT_SCRATCH(1 + i), guc->params[i]);

	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_GT);
पूर्ण

पूर्णांक पूर्णांकel_guc_init(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	पूर्णांक ret;

	ret = पूर्णांकel_uc_fw_init(&guc->fw);
	अगर (ret)
		जाओ out;

	ret = पूर्णांकel_guc_log_create(&guc->log);
	अगर (ret)
		जाओ err_fw;

	ret = पूर्णांकel_guc_ads_create(guc);
	अगर (ret)
		जाओ err_log;
	GEM_BUG_ON(!guc->ads_vma);

	ret = पूर्णांकel_guc_ct_init(&guc->ct);
	अगर (ret)
		जाओ err_ads;

	अगर (पूर्णांकel_guc_submission_is_used(guc)) अणु
		/*
		 * This is stuff we need to have available at fw load समय
		 * अगर we are planning to enable submission later
		 */
		ret = पूर्णांकel_guc_submission_init(guc);
		अगर (ret)
			जाओ err_ct;
	पूर्ण

	/* now that everything is perma-pinned, initialize the parameters */
	guc_init_params(guc);

	/* We need to notअगरy the guc whenever we change the GGTT */
	i915_ggtt_enable_guc(gt->ggtt);

	पूर्णांकel_uc_fw_change_status(&guc->fw, INTEL_UC_FIRMWARE_LOADABLE);

	वापस 0;

err_ct:
	पूर्णांकel_guc_ct_fini(&guc->ct);
err_ads:
	पूर्णांकel_guc_ads_destroy(guc);
err_log:
	पूर्णांकel_guc_log_destroy(&guc->log);
err_fw:
	पूर्णांकel_uc_fw_fini(&guc->fw);
out:
	i915_probe_error(gt->i915, "failed with %d\n", ret);
	वापस ret;
पूर्ण

व्योम पूर्णांकel_guc_fini(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);

	अगर (!पूर्णांकel_uc_fw_is_loadable(&guc->fw))
		वापस;

	i915_ggtt_disable_guc(gt->ggtt);

	अगर (पूर्णांकel_guc_submission_is_used(guc))
		पूर्णांकel_guc_submission_fini(guc);

	पूर्णांकel_guc_ct_fini(&guc->ct);

	पूर्णांकel_guc_ads_destroy(guc);
	पूर्णांकel_guc_log_destroy(&guc->log);
	पूर्णांकel_uc_fw_fini(&guc->fw);
पूर्ण

/*
 * This function implements the MMIO based host to GuC पूर्णांकerface.
 */
पूर्णांक पूर्णांकel_guc_send_mmio(काष्ठा पूर्णांकel_guc *guc, स्थिर u32 *action, u32 len,
			u32 *response_buf, u32 response_buf_size)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = guc_to_gt(guc)->uncore;
	u32 status;
	पूर्णांक i;
	पूर्णांक ret;

	GEM_BUG_ON(!len);
	GEM_BUG_ON(len > guc->send_regs.count);

	/* We expect only action code */
	GEM_BUG_ON(*action & ~INTEL_GUC_MSG_CODE_MASK);

	/* If CT is available, we expect to use MMIO only during init/fini */
	GEM_BUG_ON(*action != INTEL_GUC_ACTION_REGISTER_COMMAND_TRANSPORT_BUFFER &&
		   *action != INTEL_GUC_ACTION_DEREGISTER_COMMAND_TRANSPORT_BUFFER);

	mutex_lock(&guc->send_mutex);
	पूर्णांकel_uncore_क्रमcewake_get(uncore, guc->send_regs.fw_करोमुख्यs);

	क्रम (i = 0; i < len; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, guc_send_reg(guc, i), action[i]);

	पूर्णांकel_uncore_posting_पढ़ो(uncore, guc_send_reg(guc, i - 1));

	पूर्णांकel_guc_notअगरy(guc);

	/*
	 * No GuC command should ever take दीर्घer than 10ms.
	 * Fast commands should still complete in 10us.
	 */
	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore,
					   guc_send_reg(guc, 0),
					   INTEL_GUC_MSG_TYPE_MASK,
					   INTEL_GUC_MSG_TYPE_RESPONSE <<
					   INTEL_GUC_MSG_TYPE_SHIFT,
					   10, 10, &status);
	/* If GuC explicitly वापसed an error, convert it to -EIO */
	अगर (!ret && !INTEL_GUC_MSG_IS_RESPONSE_SUCCESS(status))
		ret = -EIO;

	अगर (ret) अणु
		DRM_ERROR("MMIO: GuC action %#x failed with error %d %#x\n",
			  action[0], ret, status);
		जाओ out;
	पूर्ण

	अगर (response_buf) अणु
		पूर्णांक count = min(response_buf_size, guc->send_regs.count - 1);

		क्रम (i = 0; i < count; i++)
			response_buf[i] = पूर्णांकel_uncore_पढ़ो(uncore,
							    guc_send_reg(guc, i + 1));
	पूर्ण

	/* Use data from the GuC response as our वापस value */
	ret = INTEL_GUC_MSG_TO_DATA(status);

out:
	पूर्णांकel_uncore_क्रमcewake_put(uncore, guc->send_regs.fw_करोमुख्यs);
	mutex_unlock(&guc->send_mutex);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_guc_to_host_process_recv_msg(काष्ठा पूर्णांकel_guc *guc,
				       स्थिर u32 *payload, u32 len)
अणु
	u32 msg;

	अगर (unlikely(!len))
		वापस -EPROTO;

	/* Make sure to handle only enabled messages */
	msg = payload[0] & guc->msg_enabled_mask;

	अगर (msg & (INTEL_GUC_RECV_MSG_FLUSH_LOG_BUFFER |
		   INTEL_GUC_RECV_MSG_CRASH_DUMP_POSTED))
		पूर्णांकel_guc_log_handle_flush_event(&guc->log);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_guc_sample_क्रमcewake(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = guc_to_gt(guc)->i915;
	u32 action[2];

	action[0] = INTEL_GUC_ACTION_SAMPLE_FORCEWAKE;
	/* WaRsDisableCoarsePowerGating:skl,cnl */
	अगर (!HAS_RC6(dev_priv) || NEEDS_WaRsDisableCoarsePowerGating(dev_priv))
		action[1] = 0;
	अन्यथा
		/* bit 0 and 1 are क्रम Render and Media करोमुख्य separately */
		action[1] = GUC_FORCEWAKE_RENDER | GUC_FORCEWAKE_MEDIA;

	वापस पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
पूर्ण

/**
 * पूर्णांकel_guc_auth_huc() - Send action to GuC to authenticate HuC ucode
 * @guc: पूर्णांकel_guc काष्ठाure
 * @rsa_offset: rsa offset w.r.t ggtt base of huc vma
 *
 * Triggers a HuC firmware authentication request to the GuC via पूर्णांकel_guc_send
 * INTEL_GUC_ACTION_AUTHENTICATE_HUC पूर्णांकerface. This function is invoked by
 * पूर्णांकel_huc_auth().
 *
 * Return:	non-zero code on error
 */
पूर्णांक पूर्णांकel_guc_auth_huc(काष्ठा पूर्णांकel_guc *guc, u32 rsa_offset)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_AUTHENTICATE_HUC,
		rsa_offset
	पूर्ण;

	वापस पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
पूर्ण

/**
 * पूर्णांकel_guc_suspend() - notअगरy GuC entering suspend state
 * @guc:	the guc
 */
पूर्णांक पूर्णांकel_guc_suspend(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = guc_to_gt(guc)->uncore;
	पूर्णांक ret;
	u32 status;
	u32 action[] = अणु
		INTEL_GUC_ACTION_ENTER_S_STATE,
		GUC_POWER_D1, /* any value greater than GUC_POWER_D0 */
	पूर्ण;

	/*
	 * If GuC communication is enabled but submission is not supported,
	 * we करो not need to suspend the GuC.
	 */
	अगर (!पूर्णांकel_guc_submission_is_used(guc) || !पूर्णांकel_guc_is_पढ़ोy(guc))
		वापस 0;

	/*
	 * The ENTER_S_STATE action queues the save/restore operation in GuC FW
	 * and then वापसs, so रुकोing on the H2G is not enough to guarantee
	 * GuC is करोne. When all the processing is करोne, GuC ग_लिखोs
	 * INTEL_GUC_SLEEP_STATE_SUCCESS to scratch रेजिस्टर 14, so we can poll
	 * on that. Note that GuC करोes not ensure that the value in the रेजिस्टर
	 * is dअगरferent from INTEL_GUC_SLEEP_STATE_SUCCESS जबतक the action is
	 * in progress so we need to take care of that ourselves as well.
	 */

	पूर्णांकel_uncore_ग_लिखो(uncore, SOFT_SCRATCH(14),
			   INTEL_GUC_SLEEP_STATE_INVALID_MASK);

	ret = पूर्णांकel_guc_send(guc, action, ARRAY_SIZE(action));
	अगर (ret)
		वापस ret;

	ret = __पूर्णांकel_रुको_क्रम_रेजिस्टर(uncore, SOFT_SCRATCH(14),
					INTEL_GUC_SLEEP_STATE_INVALID_MASK,
					0, 0, 10, &status);
	अगर (ret)
		वापस ret;

	अगर (status != INTEL_GUC_SLEEP_STATE_SUCCESS) अणु
		DRM_ERROR("GuC failed to change sleep state. "
			  "action=0x%x, err=%u\n",
			  action[0], status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_guc_reset_engine() - ask GuC to reset an engine
 * @guc:	पूर्णांकel_guc काष्ठाure
 * @engine:	engine to be reset
 */
पूर्णांक पूर्णांकel_guc_reset_engine(काष्ठा पूर्णांकel_guc *guc,
			   काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	/* XXX: to be implemented with submission पूर्णांकerface rework */

	वापस -ENODEV;
पूर्ण

/**
 * पूर्णांकel_guc_resume() - notअगरy GuC resuming from suspend state
 * @guc:	the guc
 */
पूर्णांक पूर्णांकel_guc_resume(काष्ठा पूर्णांकel_guc *guc)
अणु
	/* XXX: to be implemented with submission पूर्णांकerface rework */
	वापस 0;
पूर्ण

/**
 * DOC: GuC Memory Management
 *
 * GuC can't allocate any memory क्रम its own usage, so all the allocations must
 * be handled by the host driver. GuC accesses the memory via the GGTT, with the
 * exception of the top and bottom parts of the 4GB address space, which are
 * instead re-mapped by the GuC HW to memory location of the FW itself (WOPCM)
 * or other parts of the HW. The driver must take care not to place objects that
 * the GuC is going to access in these reserved ranges. The layout of the GuC
 * address space is shown below:
 *
 * ::
 *
 *     +===========> +====================+ <== FFFF_FFFF
 *     ^             |      Reserved      |
 *     |             +====================+ <== GUC_GGTT_TOP
 *     |             |                    |
 *     |             |        DRAM        |
 *    GuC            |                    |
 *  Address    +===> +====================+ <== GuC ggtt_pin_bias
 *   Space     ^     |                    |
 *     |       |     |                    |
 *     |      GuC    |        GuC         |
 *     |     WOPCM   |       WOPCM        |
 *     |      Size   |                    |
 *     |       |     |                    |
 *     v       v     |                    |
 *     +=======+===> +====================+ <== 0000_0000
 *
 * The lower part of GuC Address Space [0, ggtt_pin_bias) is mapped to GuC WOPCM
 * जबतक upper part of GuC Address Space [ggtt_pin_bias, GUC_GGTT_TOP) is mapped
 * to DRAM. The value of the GuC ggtt_pin_bias is the GuC WOPCM size.
 */

/**
 * पूर्णांकel_guc_allocate_vma() - Allocate a GGTT VMA क्रम GuC usage
 * @guc:	the guc
 * @size:	size of area to allocate (both भव space and memory)
 *
 * This is a wrapper to create an object क्रम use with the GuC. In order to
 * use it inside the GuC, an object needs to be pinned lअगरeसमय, so we allocate
 * both some backing storage and a range inside the Global GTT. We must pin
 * it in the GGTT somewhere other than than [0, GUC ggtt_pin_bias) because that
 * range is reserved inside GuC.
 *
 * Return:	A i915_vma अगर successful, otherwise an ERR_PTR.
 */
काष्ठा i915_vma *पूर्णांकel_guc_allocate_vma(काष्ठा पूर्णांकel_guc *guc, u32 size)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u64 flags;
	पूर्णांक ret;

	obj = i915_gem_object_create_shmem(gt->i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma))
		जाओ err;

	flags = PIN_OFFSET_BIAS | i915_ggtt_pin_bias(vma);
	ret = i915_ggtt_pin(vma, शून्य, 0, flags);
	अगर (ret) अणु
		vma = ERR_PTR(ret);
		जाओ err;
	पूर्ण

	वापस i915_vma_make_unshrinkable(vma);

err:
	i915_gem_object_put(obj);
	वापस vma;
पूर्ण

/**
 * पूर्णांकel_guc_allocate_and_map_vma() - Allocate and map VMA क्रम GuC usage
 * @guc:	the guc
 * @size:	size of area to allocate (both भव space and memory)
 * @out_vma:	वापस variable क्रम the allocated vma poपूर्णांकer
 * @out_vaddr:	वापस variable क्रम the obj mapping
 *
 * This wrapper calls पूर्णांकel_guc_allocate_vma() and then maps the allocated
 * object with I915_MAP_WB.
 *
 * Return:	0 अगर successful, a negative त्रुटि_सं code otherwise.
 */
पूर्णांक पूर्णांकel_guc_allocate_and_map_vma(काष्ठा पूर्णांकel_guc *guc, u32 size,
				   काष्ठा i915_vma **out_vma, व्योम **out_vaddr)
अणु
	काष्ठा i915_vma *vma;
	व्योम *vaddr;

	vma = पूर्णांकel_guc_allocate_vma(guc, size);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	vaddr = i915_gem_object_pin_map_unlocked(vma->obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		i915_vma_unpin_and_release(&vma, 0);
		वापस PTR_ERR(vaddr);
	पूर्ण

	*out_vma = vma;
	*out_vaddr = vaddr;

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_guc_load_status - dump inक्रमmation about GuC load status
 * @guc: the GuC
 * @p: the &drm_prपूर्णांकer
 *
 * Pretty prपूर्णांकer क्रम GuC load status.
 */
व्योम पूर्णांकel_guc_load_status(काष्ठा पूर्णांकel_guc *guc, काष्ठा drm_prपूर्णांकer *p)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_guc_is_supported(guc)) अणु
		drm_म_लिखो(p, "GuC not supported\n");
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_guc_is_wanted(guc)) अणु
		drm_म_लिखो(p, "GuC disabled\n");
		वापस;
	पूर्ण

	पूर्णांकel_uc_fw_dump(&guc->fw, p);

	with_पूर्णांकel_runसमय_pm(uncore->rpm, wakeref) अणु
		u32 status = पूर्णांकel_uncore_पढ़ो(uncore, GUC_STATUS);
		u32 i;

		drm_म_लिखो(p, "\nGuC status 0x%08x:\n", status);
		drm_म_लिखो(p, "\tBootrom status = 0x%x\n",
			   (status & GS_BOOTROM_MASK) >> GS_BOOTROM_SHIFT);
		drm_म_लिखो(p, "\tuKernel status = 0x%x\n",
			   (status & GS_UKERNEL_MASK) >> GS_UKERNEL_SHIFT);
		drm_म_लिखो(p, "\tMIA Core status = 0x%x\n",
			   (status & GS_MIA_MASK) >> GS_MIA_SHIFT);
		drm_माला_दो(p, "\nScratch registers:\n");
		क्रम (i = 0; i < 16; i++) अणु
			drm_म_लिखो(p, "\t%2d: \t0x%x\n",
				   i, पूर्णांकel_uncore_पढ़ो(uncore, SOFT_SCRATCH(i)));
		पूर्ण
	पूर्ण
पूर्ण
