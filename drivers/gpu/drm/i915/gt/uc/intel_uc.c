<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016-2019 Intel Corporation
 */

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_reset.h"
#समावेश "intel_guc.h"
#समावेश "intel_guc_ads.h"
#समावेश "intel_guc_submission.h"
#समावेश "intel_uc.h"

#समावेश "i915_drv.h"

अटल स्थिर काष्ठा पूर्णांकel_uc_ops uc_ops_off;
अटल स्थिर काष्ठा पूर्णांकel_uc_ops uc_ops_on;

अटल व्योम uc_expand_शेष_options(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा drm_i915_निजी *i915 = uc_to_gt(uc)->i915;

	अगर (i915->params.enable_guc != -1)
		वापस;

	/* Don't enable GuC/HuC on pre-Gen12 */
	अगर (INTEL_GEN(i915) < 12) अणु
		i915->params.enable_guc = 0;
		वापस;
	पूर्ण

	/* Don't enable GuC/HuC on older Gen12 platक्रमms */
	अगर (IS_TIGERLAKE(i915) || IS_ROCKETLAKE(i915)) अणु
		i915->params.enable_guc = 0;
		वापस;
	पूर्ण

	/* Default: enable HuC authentication only */
	i915->params.enable_guc = ENABLE_GUC_LOAD_HUC;
पूर्ण

/* Reset GuC providing us with fresh state क्रम both GuC and HuC.
 */
अटल पूर्णांक __पूर्णांकel_uc_reset_hw(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_gt *gt = uc_to_gt(uc);
	पूर्णांक ret;
	u32 guc_status;

	ret = i915_inject_probe_error(gt->i915, -ENXIO);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_reset_guc(gt);
	अगर (ret) अणु
		DRM_ERROR("Failed to reset GuC, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	guc_status = पूर्णांकel_uncore_पढ़ो(gt->uncore, GUC_STATUS);
	WARN(!(guc_status & GS_MIA_IN_RESET),
	     "GuC status: 0x%x, MIA core expected to be in reset\n",
	     guc_status);

	वापस ret;
पूर्ण

अटल व्योम __confirm_options(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा drm_i915_निजी *i915 = uc_to_gt(uc)->i915;

	drm_dbg(&i915->drm,
		"enable_guc=%d (guc:%s submission:%s huc:%s)\n",
		i915->params.enable_guc,
		yesno(पूर्णांकel_uc_wants_guc(uc)),
		yesno(पूर्णांकel_uc_wants_guc_submission(uc)),
		yesno(पूर्णांकel_uc_wants_huc(uc)));

	अगर (i915->params.enable_guc == 0) अणु
		GEM_BUG_ON(पूर्णांकel_uc_wants_guc(uc));
		GEM_BUG_ON(पूर्णांकel_uc_wants_guc_submission(uc));
		GEM_BUG_ON(पूर्णांकel_uc_wants_huc(uc));
		वापस;
	पूर्ण

	अगर (!पूर्णांकel_uc_supports_guc(uc))
		drm_info(&i915->drm,
			 "Incompatible option enable_guc=%d - %s\n",
			 i915->params.enable_guc, "GuC is not supported!");

	अगर (i915->params.enable_guc & ENABLE_GUC_LOAD_HUC &&
	    !पूर्णांकel_uc_supports_huc(uc))
		drm_info(&i915->drm,
			 "Incompatible option enable_guc=%d - %s\n",
			 i915->params.enable_guc, "HuC is not supported!");

	अगर (i915->params.enable_guc & ENABLE_GUC_SUBMISSION &&
	    !पूर्णांकel_uc_supports_guc_submission(uc))
		drm_info(&i915->drm,
			 "Incompatible option enable_guc=%d - %s\n",
			 i915->params.enable_guc, "GuC submission is N/A");

	अगर (i915->params.enable_guc & ~ENABLE_GUC_MASK)
		drm_info(&i915->drm,
			 "Incompatible option enable_guc=%d - %s\n",
			 i915->params.enable_guc, "undocumented flag");
पूर्ण

व्योम पूर्णांकel_uc_init_early(काष्ठा पूर्णांकel_uc *uc)
अणु
	uc_expand_शेष_options(uc);

	पूर्णांकel_guc_init_early(&uc->guc);
	पूर्णांकel_huc_init_early(&uc->huc);

	__confirm_options(uc);

	अगर (पूर्णांकel_uc_wants_guc(uc))
		uc->ops = &uc_ops_on;
	अन्यथा
		uc->ops = &uc_ops_off;
पूर्ण

व्योम पूर्णांकel_uc_driver_late_release(काष्ठा पूर्णांकel_uc *uc)
अणु
पूर्ण

/**
 * पूर्णांकel_uc_init_mmio - setup uC MMIO access
 * @uc: the पूर्णांकel_uc काष्ठाure
 *
 * Setup minimal state necessary क्रम MMIO accesses later in the
 * initialization sequence.
 */
व्योम पूर्णांकel_uc_init_mmio(काष्ठा पूर्णांकel_uc *uc)
अणु
	पूर्णांकel_guc_init_send_regs(&uc->guc);
पूर्ण

अटल व्योम __uc_capture_load_err_log(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;

	अगर (guc->log.vma && !uc->load_err_log)
		uc->load_err_log = i915_gem_object_get(guc->log.vma->obj);
पूर्ण

अटल व्योम __uc_मुक्त_load_err_log(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा drm_i915_gem_object *log = fetch_and_zero(&uc->load_err_log);

	अगर (log)
		i915_gem_object_put(log);
पूर्ण

व्योम पूर्णांकel_uc_driver_हटाओ(काष्ठा पूर्णांकel_uc *uc)
अणु
	पूर्णांकel_uc_fini_hw(uc);
	पूर्णांकel_uc_fini(uc);
	__uc_मुक्त_load_err_log(uc);
पूर्ण

अटल अंतरभूत bool guc_communication_enabled(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस पूर्णांकel_guc_ct_enabled(&guc->ct);
पूर्ण

/*
 * Events triggered जबतक CT buffers are disabled are logged in the SCRATCH_15
 * रेजिस्टर using the same bits used in the CT message payload. Since our
 * communication channel with guc is turned off at this poपूर्णांक, we can save the
 * message and handle it after we turn it back on.
 */
अटल व्योम guc_clear_mmio_msg(काष्ठा पूर्णांकel_guc *guc)
अणु
	पूर्णांकel_uncore_ग_लिखो(guc_to_gt(guc)->uncore, SOFT_SCRATCH(15), 0);
पूर्ण

अटल व्योम guc_get_mmio_msg(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 val;

	spin_lock_irq(&guc->irq_lock);

	val = पूर्णांकel_uncore_पढ़ो(guc_to_gt(guc)->uncore, SOFT_SCRATCH(15));
	guc->mmio_msg |= val & guc->msg_enabled_mask;

	/*
	 * clear all events, including the ones we're not currently servicing,
	 * to make sure we करोn't try to process a stale message अगर we enable
	 * handling of more events later.
	 */
	guc_clear_mmio_msg(guc);

	spin_unlock_irq(&guc->irq_lock);
पूर्ण

अटल व्योम guc_handle_mmio_msg(काष्ठा पूर्णांकel_guc *guc)
अणु
	/* we need communication to be enabled to reply to GuC */
	GEM_BUG_ON(!guc_communication_enabled(guc));

	spin_lock_irq(&guc->irq_lock);
	अगर (guc->mmio_msg) अणु
		पूर्णांकel_guc_to_host_process_recv_msg(guc, &guc->mmio_msg, 1);
		guc->mmio_msg = 0;
	पूर्ण
	spin_unlock_irq(&guc->irq_lock);
पूर्ण

अटल व्योम guc_reset_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	guc->पूर्णांकerrupts.reset(guc);
पूर्ण

अटल व्योम guc_enable_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	guc->पूर्णांकerrupts.enable(guc);
पूर्ण

अटल व्योम guc_disable_पूर्णांकerrupts(काष्ठा पूर्णांकel_guc *guc)
अणु
	guc->पूर्णांकerrupts.disable(guc);
पूर्ण

अटल पूर्णांक guc_enable_communication(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	पूर्णांक ret;

	GEM_BUG_ON(guc_communication_enabled(guc));

	ret = i915_inject_probe_error(i915, -ENXIO);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_guc_ct_enable(&guc->ct);
	अगर (ret)
		वापस ret;

	/* check क्रम mmio messages received beक्रमe/during the CT enable */
	guc_get_mmio_msg(guc);
	guc_handle_mmio_msg(guc);

	guc_enable_पूर्णांकerrupts(guc);

	/* check क्रम CT messages received beक्रमe we enabled पूर्णांकerrupts */
	spin_lock_irq(&gt->irq_lock);
	पूर्णांकel_guc_ct_event_handler(&guc->ct);
	spin_unlock_irq(&gt->irq_lock);

	drm_dbg(&i915->drm, "GuC communication enabled\n");

	वापस 0;
पूर्ण

अटल व्योम guc_disable_communication(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा drm_i915_निजी *i915 = guc_to_gt(guc)->i915;

	/*
	 * Events generated during or after CT disable are logged by guc in
	 * via mmio. Make sure the रेजिस्टर is clear beक्रमe disabling CT since
	 * all events we cared about have alपढ़ोy been processed via CT.
	 */
	guc_clear_mmio_msg(guc);

	guc_disable_पूर्णांकerrupts(guc);

	पूर्णांकel_guc_ct_disable(&guc->ct);

	/*
	 * Check क्रम messages received during/after the CT disable. We करो not
	 * expect any messages to have arrived via CT between the पूर्णांकerrupt
	 * disable and the CT disable because GuC should've been idle until we
	 * triggered the CT disable protocol.
	 */
	guc_get_mmio_msg(guc);

	drm_dbg(&i915->drm, "GuC communication disabled\n");
पूर्ण

अटल व्योम __uc_fetch_firmwares(काष्ठा पूर्णांकel_uc *uc)
अणु
	पूर्णांक err;

	GEM_BUG_ON(!पूर्णांकel_uc_wants_guc(uc));

	err = पूर्णांकel_uc_fw_fetch(&uc->guc.fw);
	अगर (err) अणु
		/* Make sure we transition out of transient "SELECTED" state */
		अगर (पूर्णांकel_uc_wants_huc(uc)) अणु
			drm_dbg(&uc_to_gt(uc)->i915->drm,
				"Failed to fetch GuC: %d disabling HuC\n", err);
			पूर्णांकel_uc_fw_change_status(&uc->huc.fw,
						  INTEL_UC_FIRMWARE_ERROR);
		पूर्ण

		वापस;
	पूर्ण

	अगर (पूर्णांकel_uc_wants_huc(uc))
		पूर्णांकel_uc_fw_fetch(&uc->huc.fw);
पूर्ण

अटल व्योम __uc_cleanup_firmwares(काष्ठा पूर्णांकel_uc *uc)
अणु
	पूर्णांकel_uc_fw_cleanup_fetch(&uc->huc.fw);
	पूर्णांकel_uc_fw_cleanup_fetch(&uc->guc.fw);
पूर्ण

अटल पूर्णांक __uc_init(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	काष्ठा पूर्णांकel_huc *huc = &uc->huc;
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_uc_wants_guc(uc));

	अगर (!पूर्णांकel_uc_uses_guc(uc))
		वापस 0;

	अगर (i915_inject_probe_failure(uc_to_gt(uc)->i915))
		वापस -ENOMEM;

	/* XXX: GuC submission is unavailable क्रम now */
	GEM_BUG_ON(पूर्णांकel_uc_uses_guc_submission(uc));

	ret = पूर्णांकel_guc_init(guc);
	अगर (ret)
		वापस ret;

	अगर (पूर्णांकel_uc_uses_huc(uc)) अणु
		ret = पूर्णांकel_huc_init(huc);
		अगर (ret)
			जाओ out_guc;
	पूर्ण

	वापस 0;

out_guc:
	पूर्णांकel_guc_fini(guc);
	वापस ret;
पूर्ण

अटल व्योम __uc_fini(काष्ठा पूर्णांकel_uc *uc)
अणु
	पूर्णांकel_huc_fini(&uc->huc);
	पूर्णांकel_guc_fini(&uc->guc);
पूर्ण

अटल पूर्णांक __uc_sanitize(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	काष्ठा पूर्णांकel_huc *huc = &uc->huc;

	GEM_BUG_ON(!पूर्णांकel_uc_supports_guc(uc));

	पूर्णांकel_huc_sanitize(huc);
	पूर्णांकel_guc_sanitize(guc);

	वापस __पूर्णांकel_uc_reset_hw(uc);
पूर्ण

/* Initialize and verअगरy the uC regs related to uC positioning in WOPCM */
अटल पूर्णांक uc_init_wopcm(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_gt *gt = uc_to_gt(uc);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 base = पूर्णांकel_wopcm_guc_base(&gt->i915->wopcm);
	u32 size = पूर्णांकel_wopcm_guc_size(&gt->i915->wopcm);
	u32 huc_agent = पूर्णांकel_uc_uses_huc(uc) ? HUC_LOADING_AGENT_GUC : 0;
	u32 mask;
	पूर्णांक err;

	अगर (unlikely(!base || !size)) अणु
		i915_probe_error(gt->i915, "Unsuccessful WOPCM partitioning\n");
		वापस -E2BIG;
	पूर्ण

	GEM_BUG_ON(!पूर्णांकel_uc_supports_guc(uc));
	GEM_BUG_ON(!(base & GUC_WOPCM_OFFSET_MASK));
	GEM_BUG_ON(base & ~GUC_WOPCM_OFFSET_MASK);
	GEM_BUG_ON(!(size & GUC_WOPCM_SIZE_MASK));
	GEM_BUG_ON(size & ~GUC_WOPCM_SIZE_MASK);

	err = i915_inject_probe_error(gt->i915, -ENXIO);
	अगर (err)
		वापस err;

	mask = GUC_WOPCM_SIZE_MASK | GUC_WOPCM_SIZE_LOCKED;
	err = पूर्णांकel_uncore_ग_लिखो_and_verअगरy(uncore, GUC_WOPCM_SIZE, size, mask,
					    size | GUC_WOPCM_SIZE_LOCKED);
	अगर (err)
		जाओ err_out;

	mask = GUC_WOPCM_OFFSET_MASK | GUC_WOPCM_OFFSET_VALID | huc_agent;
	err = पूर्णांकel_uncore_ग_लिखो_and_verअगरy(uncore, DMA_GUC_WOPCM_OFFSET,
					    base | huc_agent, mask,
					    base | huc_agent |
					    GUC_WOPCM_OFFSET_VALID);
	अगर (err)
		जाओ err_out;

	वापस 0;

err_out:
	i915_probe_error(gt->i915, "Failed to init uC WOPCM registers!\n");
	i915_probe_error(gt->i915, "%s(%#x)=%#x\n", "DMA_GUC_WOPCM_OFFSET",
			 i915_mmio_reg_offset(DMA_GUC_WOPCM_OFFSET),
			 पूर्णांकel_uncore_पढ़ो(uncore, DMA_GUC_WOPCM_OFFSET));
	i915_probe_error(gt->i915, "%s(%#x)=%#x\n", "GUC_WOPCM_SIZE",
			 i915_mmio_reg_offset(GUC_WOPCM_SIZE),
			 पूर्णांकel_uncore_पढ़ो(uncore, GUC_WOPCM_SIZE));

	वापस err;
पूर्ण

अटल bool uc_is_wopcm_locked(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_gt *gt = uc_to_gt(uc);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;

	वापस (पूर्णांकel_uncore_पढ़ो(uncore, GUC_WOPCM_SIZE) & GUC_WOPCM_SIZE_LOCKED) ||
	       (पूर्णांकel_uncore_पढ़ो(uncore, DMA_GUC_WOPCM_OFFSET) & GUC_WOPCM_OFFSET_VALID);
पूर्ण

अटल पूर्णांक __uc_check_hw(काष्ठा पूर्णांकel_uc *uc)
अणु
	अगर (!पूर्णांकel_uc_supports_guc(uc))
		वापस 0;

	/*
	 * We can silently जारी without GuC only अगर it was never enabled
	 * beक्रमe on this प्रणाली after reboot, otherwise we risk GPU hangs.
	 * To check अगर GuC was loaded beक्रमe we look at WOPCM रेजिस्टरs.
	 */
	अगर (uc_is_wopcm_locked(uc))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक __uc_init_hw(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा drm_i915_निजी *i915 = uc_to_gt(uc)->i915;
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	काष्ठा पूर्णांकel_huc *huc = &uc->huc;
	पूर्णांक ret, attempts;

	GEM_BUG_ON(!पूर्णांकel_uc_supports_guc(uc));
	GEM_BUG_ON(!पूर्णांकel_uc_wants_guc(uc));

	अगर (!पूर्णांकel_uc_fw_is_loadable(&guc->fw)) अणु
		ret = __uc_check_hw(uc) ||
		      पूर्णांकel_uc_fw_is_overridden(&guc->fw) ||
		      पूर्णांकel_uc_wants_guc_submission(uc) ?
		      पूर्णांकel_uc_fw_status_to_error(guc->fw.status) : 0;
		जाओ err_out;
	पूर्ण

	ret = uc_init_wopcm(uc);
	अगर (ret)
		जाओ err_out;

	guc_reset_पूर्णांकerrupts(guc);

	/* WaEnableuKernelHeaderValidFix:skl */
	/* WaEnableGuCBootHashCheckNotSet:skl,bxt,kbl */
	अगर (IS_GEN(i915, 9))
		attempts = 3;
	अन्यथा
		attempts = 1;

	जबतक (attempts--) अणु
		/*
		 * Always reset the GuC just beक्रमe (re)loading, so
		 * that the state and timing are fairly predictable
		 */
		ret = __uc_sanitize(uc);
		अगर (ret)
			जाओ err_out;

		पूर्णांकel_huc_fw_upload(huc);
		पूर्णांकel_guc_ads_reset(guc);
		पूर्णांकel_guc_ग_लिखो_params(guc);
		ret = पूर्णांकel_guc_fw_upload(guc);
		अगर (ret == 0)
			अवरोध;

		DRM_DEBUG_DRIVER("GuC fw load failed: %d; will reset and "
				 "retry %d more time(s)\n", ret, attempts);
	पूर्ण

	/* Did we succeded or run out of retries? */
	अगर (ret)
		जाओ err_log_capture;

	ret = guc_enable_communication(guc);
	अगर (ret)
		जाओ err_log_capture;

	पूर्णांकel_huc_auth(huc);

	ret = पूर्णांकel_guc_sample_क्रमcewake(guc);
	अगर (ret)
		जाओ err_communication;

	अगर (पूर्णांकel_uc_uses_guc_submission(uc))
		पूर्णांकel_guc_submission_enable(guc);

	drm_info(&i915->drm, "%s firmware %s version %u.%u %s:%s\n",
		 पूर्णांकel_uc_fw_type_repr(INTEL_UC_FW_TYPE_GUC), guc->fw.path,
		 guc->fw.major_ver_found, guc->fw.minor_ver_found,
		 "submission",
		 enableddisabled(पूर्णांकel_uc_uses_guc_submission(uc)));

	अगर (पूर्णांकel_uc_uses_huc(uc)) अणु
		drm_info(&i915->drm, "%s firmware %s version %u.%u %s:%s\n",
			 पूर्णांकel_uc_fw_type_repr(INTEL_UC_FW_TYPE_HUC),
			 huc->fw.path,
			 huc->fw.major_ver_found, huc->fw.minor_ver_found,
			 "authenticated",
			 yesno(पूर्णांकel_huc_is_authenticated(huc)));
	पूर्ण

	वापस 0;

	/*
	 * We've failed to load the firmware :(
	 */
err_communication:
	guc_disable_communication(guc);
err_log_capture:
	__uc_capture_load_err_log(uc);
err_out:
	__uc_sanitize(uc);

	अगर (!ret) अणु
		drm_notice(&i915->drm, "GuC is uninitialized\n");
		/* We want to run without GuC submission */
		वापस 0;
	पूर्ण

	i915_probe_error(i915, "GuC initialization failed %d\n", ret);

	/* We want to keep KMS alive */
	वापस -EIO;
पूर्ण

अटल व्योम __uc_fini_hw(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;

	अगर (!पूर्णांकel_guc_is_fw_running(guc))
		वापस;

	अगर (पूर्णांकel_uc_uses_guc_submission(uc))
		पूर्णांकel_guc_submission_disable(guc);

	अगर (guc_communication_enabled(guc))
		guc_disable_communication(guc);

	__uc_sanitize(uc);
पूर्ण

/**
 * पूर्णांकel_uc_reset_prepare - Prepare क्रम reset
 * @uc: the पूर्णांकel_uc काष्ठाure
 *
 * Preparing क्रम full gpu reset.
 */
व्योम पूर्णांकel_uc_reset_prepare(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;

	अगर (!पूर्णांकel_guc_is_पढ़ोy(guc))
		वापस;

	guc_disable_communication(guc);
	__uc_sanitize(uc);
पूर्ण

व्योम पूर्णांकel_uc_runसमय_suspend(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	पूर्णांक err;

	अगर (!पूर्णांकel_guc_is_पढ़ोy(guc))
		वापस;

	err = पूर्णांकel_guc_suspend(guc);
	अगर (err)
		DRM_DEBUG_DRIVER("Failed to suspend GuC, err=%d", err);

	guc_disable_communication(guc);
पूर्ण

व्योम पूर्णांकel_uc_suspend(काष्ठा पूर्णांकel_uc *uc)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	पूर्णांकel_wakeref_t wakeref;

	अगर (!पूर्णांकel_guc_is_पढ़ोy(guc))
		वापस;

	with_पूर्णांकel_runसमय_pm(uc_to_gt(uc)->uncore->rpm, wakeref)
		पूर्णांकel_uc_runसमय_suspend(uc);
पूर्ण

अटल पूर्णांक __uc_resume(काष्ठा पूर्णांकel_uc *uc, bool enable_communication)
अणु
	काष्ठा पूर्णांकel_guc *guc = &uc->guc;
	पूर्णांक err;

	अगर (!पूर्णांकel_guc_is_fw_running(guc))
		वापस 0;

	/* Make sure we enable communication अगर and only अगर it's disabled */
	GEM_BUG_ON(enable_communication == guc_communication_enabled(guc));

	अगर (enable_communication)
		guc_enable_communication(guc);

	err = पूर्णांकel_guc_resume(guc);
	अगर (err) अणु
		DRM_DEBUG_DRIVER("Failed to resume GuC, err=%d", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_uc_resume(काष्ठा पूर्णांकel_uc *uc)
अणु
	/*
	 * When coming out of S3/S4 we sanitize and re-init the HW, so
	 * communication is alपढ़ोy re-enabled at this poपूर्णांक.
	 */
	वापस __uc_resume(uc, false);
पूर्ण

पूर्णांक पूर्णांकel_uc_runसमय_resume(काष्ठा पूर्णांकel_uc *uc)
अणु
	/*
	 * During runसमय resume we करोn't sanitize, so we need to re-init
	 * communication as well.
	 */
	वापस __uc_resume(uc, true);
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_uc_ops uc_ops_off = अणु
	.init_hw = __uc_check_hw,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_uc_ops uc_ops_on = अणु
	.sanitize = __uc_sanitize,

	.init_fw = __uc_fetch_firmwares,
	.fini_fw = __uc_cleanup_firmwares,

	.init = __uc_init,
	.fini = __uc_fini,

	.init_hw = __uc_init_hw,
	.fini_hw = __uc_fini_hw,
पूर्ण;
