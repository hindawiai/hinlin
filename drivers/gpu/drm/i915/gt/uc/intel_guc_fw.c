<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 *
 * Authors:
 *    Vinit Azad <vinit.azad@पूर्णांकel.com>
 *    Ben Widawsky <ben@bwidawsk.net>
 *    Dave Gorकरोn <david.s.gorकरोn@पूर्णांकel.com>
 *    Alex Dai <yu.dai@पूर्णांकel.com>
 */

#समावेश "gt/intel_gt.h"
#समावेश "intel_guc_fw.h"
#समावेश "i915_drv.h"

अटल व्योम guc_prepare_xfer(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 shim_flags = GUC_DISABLE_SRAM_INIT_TO_ZEROES |
			 GUC_ENABLE_READ_CACHE_LOGIC |
			 GUC_ENABLE_MIA_CACHING |
			 GUC_ENABLE_READ_CACHE_FOR_SRAM_DATA |
			 GUC_ENABLE_READ_CACHE_FOR_WOPCM_DATA |
			 GUC_ENABLE_MIA_CLOCK_GATING;

	/* Must program this रेजिस्टर beक्रमe loading the ucode with DMA */
	पूर्णांकel_uncore_ग_लिखो(uncore, GUC_SHIM_CONTROL, shim_flags);

	अगर (IS_GEN9_LP(uncore->i915))
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN9LP_GT_PM_CONFIG, GT_DOORBELL_ENABLE);
	अन्यथा
		पूर्णांकel_uncore_ग_लिखो(uncore, GEN9_GT_PM_CONFIG, GT_DOORBELL_ENABLE);

	अगर (IS_GEN(uncore->i915, 9)) अणु
		/* DOP Clock Gating Enable क्रम GuC घड़ीs */
		पूर्णांकel_uncore_rmw(uncore, GEN7_MISCCPCTL,
				 0, GEN8_DOP_CLOCK_GATE_GUC_ENABLE);

		/* allows क्रम 5us (in 10ns units) beक्रमe GT can go to RC6 */
		पूर्णांकel_uncore_ग_लिखो(uncore, GUC_ARAT_C6DIS, 0x1FF);
	पूर्ण
पूर्ण

/* Copy RSA signature from the fw image to HW क्रम verअगरication */
अटल व्योम guc_xfer_rsa(काष्ठा पूर्णांकel_uc_fw *guc_fw,
			 काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 rsa[UOS_RSA_SCRATCH_COUNT];
	माप_प्रकार copied;
	पूर्णांक i;

	copied = पूर्णांकel_uc_fw_copy_rsa(guc_fw, rsa, माप(rsa));
	GEM_BUG_ON(copied < माप(rsa));

	क्रम (i = 0; i < UOS_RSA_SCRATCH_COUNT; i++)
		पूर्णांकel_uncore_ग_लिखो(uncore, UOS_RSA_SCRATCH(i), rsa[i]);
पूर्ण

/*
 * Read the GuC status रेजिस्टर (GUC_STATUS) and store it in the
 * specअगरied location; then वापस a boolean indicating whether
 * the value matches either of two values representing completion
 * of the GuC boot process.
 *
 * This is used क्रम polling the GuC status in a रुको_क्रम()
 * loop below.
 */
अटल अंतरभूत bool guc_पढ़ोy(काष्ठा पूर्णांकel_uncore *uncore, u32 *status)
अणु
	u32 val = पूर्णांकel_uncore_पढ़ो(uncore, GUC_STATUS);
	u32 uk_val = val & GS_UKERNEL_MASK;

	*status = val;
	वापस (uk_val == GS_UKERNEL_READY) ||
		((val & GS_MIA_CORE_STATE) && (uk_val == GS_UKERNEL_LAPIC_DONE));
पूर्ण

अटल पूर्णांक guc_रुको_ucode(काष्ठा पूर्णांकel_uncore *uncore)
अणु
	u32 status;
	पूर्णांक ret;

	/*
	 * Wait क्रम the GuC to start up.
	 * NB: Docs recommend not using the पूर्णांकerrupt क्रम completion.
	 * Measurements indicate this should take no more than 20ms, so a
	 * समयout here indicates that the GuC has failed and is unusable.
	 * (Higher levels of the driver may decide to reset the GuC and
	 * attempt the ucode load again अगर this happens.)
	 */
	ret = रुको_क्रम(guc_पढ़ोy(uncore, &status), 100);
	अगर (ret) अणु
		काष्ठा drm_device *drm = &uncore->i915->drm;

		drm_dbg(drm, "GuC load failed: status = 0x%08X\n", status);
		drm_dbg(drm, "GuC load failed: status: Reset = %d, "
			"BootROM = 0x%02X, UKernel = 0x%02X, "
			"MIA = 0x%02X, Auth = 0x%02X\n",
			REG_FIELD_GET(GS_MIA_IN_RESET, status),
			REG_FIELD_GET(GS_BOOTROM_MASK, status),
			REG_FIELD_GET(GS_UKERNEL_MASK, status),
			REG_FIELD_GET(GS_MIA_MASK, status),
			REG_FIELD_GET(GS_AUTH_STATUS_MASK, status));

		अगर ((status & GS_BOOTROM_MASK) == GS_BOOTROM_RSA_FAILED) अणु
			drm_dbg(drm, "GuC firmware signature verification failed\n");
			ret = -ENOEXEC;
		पूर्ण

		अगर ((status & GS_UKERNEL_MASK) == GS_UKERNEL_EXCEPTION) अणु
			drm_dbg(drm, "GuC firmware exception. EIP: %#x\n",
				पूर्णांकel_uncore_पढ़ो(uncore, SOFT_SCRATCH(13)));
			ret = -ENXIO;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_guc_fw_upload() - load GuC uCode to device
 * @guc: पूर्णांकel_guc काष्ठाure
 *
 * Called from पूर्णांकel_uc_init_hw() during driver load, resume from sleep and
 * after a GPU reset.
 *
 * The firmware image should have alपढ़ोy been fetched पूर्णांकo memory, so only
 * check that fetch succeeded, and then transfer the image to the h/w.
 *
 * Return:	non-zero code on error
 */
पूर्णांक पूर्णांकel_guc_fw_upload(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक ret;

	guc_prepare_xfer(uncore);

	/*
	 * Note that GuC needs the CSS header plus uKernel code to be copied
	 * by the DMA engine in one operation, whereas the RSA signature is
	 * loaded via MMIO.
	 */
	guc_xfer_rsa(&guc->fw, uncore);

	/*
	 * Current uCode expects the code to be loaded at 8k; locations below
	 * this are used क्रम the stack.
	 */
	ret = पूर्णांकel_uc_fw_upload(&guc->fw, 0x2000, UOS_MOVE);
	अगर (ret)
		जाओ out;

	ret = guc_रुको_ucode(uncore);
	अगर (ret)
		जाओ out;

	पूर्णांकel_uc_fw_change_status(&guc->fw, INTEL_UC_FIRMWARE_RUNNING);
	वापस 0;

out:
	पूर्णांकel_uc_fw_change_status(&guc->fw, INTEL_UC_FIRMWARE_FAIL);
	वापस ret;
पूर्ण
