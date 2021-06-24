<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_HUC_H_
#घोषणा _INTEL_HUC_H_

#समावेश "i915_reg.h"
#समावेश "intel_uc_fw.h"
#समावेश "intel_huc_fw.h"

काष्ठा पूर्णांकel_huc अणु
	/* Generic uC firmware management */
	काष्ठा पूर्णांकel_uc_fw fw;

	/* HuC-specअगरic additions */
	काष्ठा i915_vma *rsa_data;

	काष्ठा अणु
		i915_reg_t reg;
		u32 mask;
		u32 value;
	पूर्ण status;
पूर्ण;

व्योम पूर्णांकel_huc_init_early(काष्ठा पूर्णांकel_huc *huc);
पूर्णांक पूर्णांकel_huc_init(काष्ठा पूर्णांकel_huc *huc);
व्योम पूर्णांकel_huc_fini(काष्ठा पूर्णांकel_huc *huc);
पूर्णांक पूर्णांकel_huc_auth(काष्ठा पूर्णांकel_huc *huc);
पूर्णांक पूर्णांकel_huc_check_status(काष्ठा पूर्णांकel_huc *huc);

अटल अंतरभूत पूर्णांक पूर्णांकel_huc_sanitize(काष्ठा पूर्णांकel_huc *huc)
अणु
	पूर्णांकel_uc_fw_sanitize(&huc->fw);
	वापस 0;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_huc_is_supported(काष्ठा पूर्णांकel_huc *huc)
अणु
	वापस पूर्णांकel_uc_fw_is_supported(&huc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_huc_is_wanted(काष्ठा पूर्णांकel_huc *huc)
अणु
	वापस पूर्णांकel_uc_fw_is_enabled(&huc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_huc_is_used(काष्ठा पूर्णांकel_huc *huc)
अणु
	GEM_BUG_ON(__पूर्णांकel_uc_fw_status(&huc->fw) == INTEL_UC_FIRMWARE_SELECTED);
	वापस पूर्णांकel_uc_fw_is_available(&huc->fw);
पूर्ण

अटल अंतरभूत bool पूर्णांकel_huc_is_authenticated(काष्ठा पूर्णांकel_huc *huc)
अणु
	वापस पूर्णांकel_uc_fw_is_running(&huc->fw);
पूर्ण

व्योम पूर्णांकel_huc_load_status(काष्ठा पूर्णांकel_huc *huc, काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
