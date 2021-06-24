<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#समावेश "gt/intel_gt.h"
#समावेश "intel_huc_fw.h"
#समावेश "i915_drv.h"

/**
 * पूर्णांकel_huc_fw_upload() - load HuC uCode to device
 * @huc: पूर्णांकel_huc काष्ठाure
 *
 * Called from पूर्णांकel_uc_init_hw() during driver load, resume from sleep and
 * after a GPU reset. Note that HuC must be loaded beक्रमe GuC.
 *
 * The firmware image should have alपढ़ोy been fetched पूर्णांकo memory, so only
 * check that fetch succeeded, and then transfer the image to the h/w.
 *
 * Return:	non-zero code on error
 */
पूर्णांक पूर्णांकel_huc_fw_upload(काष्ठा पूर्णांकel_huc *huc)
अणु
	/* HW करोesn't look at destination address क्रम HuC, so set it to 0 */
	वापस पूर्णांकel_uc_fw_upload(&huc->fw, 0, HUC_UKERNEL);
पूर्ण
