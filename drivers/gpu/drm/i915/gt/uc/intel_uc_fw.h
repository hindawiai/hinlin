<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_UC_FW_H_
#घोषणा _INTEL_UC_FW_H_

#समावेश <linux/types.h>
#समावेश "intel_uc_fw_abi.h"
#समावेश "intel_device_info.h"
#समावेश "i915_gem.h"

काष्ठा drm_prपूर्णांकer;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_gt;

/* Home of GuC, HuC and DMC firmwares */
#घोषणा INTEL_UC_FIRMWARE_URL "https://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git/tree/i915"

/*
 * +------------+---------------------------------------------------+
 * |   PHASE    |           FIRMWARE STATUS TRANSITIONS             |
 * +============+===================================================+
 * |            |               UNINITIALIZED                       |
 * +------------+-               /   |   \                         -+
 * |            |   DISABLED <--/    |    \--> NOT_SUPPORTED        |
 * | init_early |                    V                              |
 * |            |                 SELECTED                          |
 * +------------+-               /   |   \                         -+
 * |            |    MISSING <--/    |    \--> ERROR                |
 * |   fetch    |                    V                              |
 * |            |                 AVAILABLE                         |
 * +------------+-                   |                             -+
 * |   init     |                    V                              |
 * |            |        /------> LOADABLE <----<-----------\       |
 * +------------+-       \         /    \        \           \     -+
 * |            |         FAIL <--<      \--> TRANSFERRED     \     |
 * |   upload   |                  \           /   \          /     |
 * |            |                   \---------/     \--> RUNNING    |
 * +------------+---------------------------------------------------+
 */

क्रमागत पूर्णांकel_uc_fw_status अणु
	INTEL_UC_FIRMWARE_NOT_SUPPORTED = -1, /* no uc HW */
	INTEL_UC_FIRMWARE_UNINITIALIZED = 0, /* used to catch checks करोne too early */
	INTEL_UC_FIRMWARE_DISABLED, /* disabled */
	INTEL_UC_FIRMWARE_SELECTED, /* selected the blob we want to load */
	INTEL_UC_FIRMWARE_MISSING, /* blob not found on the प्रणाली */
	INTEL_UC_FIRMWARE_ERROR, /* invalid क्रमmat or version */
	INTEL_UC_FIRMWARE_AVAILABLE, /* blob found and copied in mem */
	INTEL_UC_FIRMWARE_LOADABLE, /* all fw-required objects are पढ़ोy */
	INTEL_UC_FIRMWARE_FAIL, /* failed to xfer or init/auth the fw */
	INTEL_UC_FIRMWARE_TRANSFERRED, /* dma xfer करोne */
	INTEL_UC_FIRMWARE_RUNNING /* init/auth करोne */
पूर्ण;

क्रमागत पूर्णांकel_uc_fw_type अणु
	INTEL_UC_FW_TYPE_GUC = 0,
	INTEL_UC_FW_TYPE_HUC
पूर्ण;
#घोषणा INTEL_UC_FW_NUM_TYPES 2

/*
 * This काष्ठाure encapsulates all the data needed during the process
 * of fetching, caching, and loading the firmware image पूर्णांकo the uC.
 */
काष्ठा पूर्णांकel_uc_fw अणु
	क्रमागत पूर्णांकel_uc_fw_type type;
	जोड़ अणु
		स्थिर क्रमागत पूर्णांकel_uc_fw_status status;
		क्रमागत पूर्णांकel_uc_fw_status __status; /* no accidental overग_लिखोs */
	पूर्ण;
	स्थिर अक्षर *path;
	bool user_overridden;
	माप_प्रकार size;
	काष्ठा drm_i915_gem_object *obj;

	/*
	 * The firmware build process will generate a version header file with major and
	 * minor version defined. The versions are built पूर्णांकo CSS header of firmware.
	 * i915 kernel driver set the minimal firmware version required per platक्रमm.
	 */
	u16 major_ver_wanted;
	u16 minor_ver_wanted;
	u16 major_ver_found;
	u16 minor_ver_found;

	u32 rsa_size;
	u32 ucode_size;

	u32 निजी_data_size;
पूर्ण;

#अगर_घोषित CONFIG_DRM_I915_DEBUG_GUC
व्योम पूर्णांकel_uc_fw_change_status(काष्ठा पूर्णांकel_uc_fw *uc_fw,
			       क्रमागत पूर्णांकel_uc_fw_status status);
#अन्यथा
अटल अंतरभूत व्योम पूर्णांकel_uc_fw_change_status(काष्ठा पूर्णांकel_uc_fw *uc_fw,
					     क्रमागत पूर्णांकel_uc_fw_status status)
अणु
	uc_fw->__status = status;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत
स्थिर अक्षर *पूर्णांकel_uc_fw_status_repr(क्रमागत पूर्णांकel_uc_fw_status status)
अणु
	चयन (status) अणु
	हाल INTEL_UC_FIRMWARE_NOT_SUPPORTED:
		वापस "N/A";
	हाल INTEL_UC_FIRMWARE_UNINITIALIZED:
		वापस "UNINITIALIZED";
	हाल INTEL_UC_FIRMWARE_DISABLED:
		वापस "DISABLED";
	हाल INTEL_UC_FIRMWARE_SELECTED:
		वापस "SELECTED";
	हाल INTEL_UC_FIRMWARE_MISSING:
		वापस "MISSING";
	हाल INTEL_UC_FIRMWARE_ERROR:
		वापस "ERROR";
	हाल INTEL_UC_FIRMWARE_AVAILABLE:
		वापस "AVAILABLE";
	हाल INTEL_UC_FIRMWARE_LOADABLE:
		वापस "LOADABLE";
	हाल INTEL_UC_FIRMWARE_FAIL:
		वापस "FAIL";
	हाल INTEL_UC_FIRMWARE_TRANSFERRED:
		वापस "TRANSFERRED";
	हाल INTEL_UC_FIRMWARE_RUNNING:
		वापस "RUNNING";
	पूर्ण
	वापस "<invalid>";
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकel_uc_fw_status_to_error(क्रमागत पूर्णांकel_uc_fw_status status)
अणु
	चयन (status) अणु
	हाल INTEL_UC_FIRMWARE_NOT_SUPPORTED:
		वापस -ENODEV;
	हाल INTEL_UC_FIRMWARE_UNINITIALIZED:
		वापस -EACCES;
	हाल INTEL_UC_FIRMWARE_DISABLED:
		वापस -EPERM;
	हाल INTEL_UC_FIRMWARE_MISSING:
		वापस -ENOENT;
	हाल INTEL_UC_FIRMWARE_ERROR:
		वापस -ENOEXEC;
	हाल INTEL_UC_FIRMWARE_FAIL:
		वापस -EIO;
	हाल INTEL_UC_FIRMWARE_SELECTED:
		वापस -ESTALE;
	हाल INTEL_UC_FIRMWARE_AVAILABLE:
	हाल INTEL_UC_FIRMWARE_LOADABLE:
	हाल INTEL_UC_FIRMWARE_TRANSFERRED:
	हाल INTEL_UC_FIRMWARE_RUNNING:
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *पूर्णांकel_uc_fw_type_repr(क्रमागत पूर्णांकel_uc_fw_type type)
अणु
	चयन (type) अणु
	हाल INTEL_UC_FW_TYPE_GUC:
		वापस "GuC";
	हाल INTEL_UC_FW_TYPE_HUC:
		वापस "HuC";
	पूर्ण
	वापस "uC";
पूर्ण

अटल अंतरभूत क्रमागत पूर्णांकel_uc_fw_status
__पूर्णांकel_uc_fw_status(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	/* shouldn't call this beक्रमe checking hw/blob availability */
	GEM_BUG_ON(uc_fw->status == INTEL_UC_FIRMWARE_UNINITIALIZED);
	वापस uc_fw->status;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_supported(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) != INTEL_UC_FIRMWARE_NOT_SUPPORTED;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_enabled(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) > INTEL_UC_FIRMWARE_DISABLED;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_available(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) >= INTEL_UC_FIRMWARE_AVAILABLE;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_loadable(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) >= INTEL_UC_FIRMWARE_LOADABLE;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_loaded(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) >= INTEL_UC_FIRMWARE_TRANSFERRED;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_running(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस __पूर्णांकel_uc_fw_status(uc_fw) == INTEL_UC_FIRMWARE_RUNNING;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_uc_fw_is_overridden(स्थिर काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस uc_fw->user_overridden;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_uc_fw_sanitize(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	अगर (पूर्णांकel_uc_fw_is_loaded(uc_fw))
		पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_LOADABLE);
पूर्ण

अटल अंतरभूत u32 __पूर्णांकel_uc_fw_get_upload_size(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	वापस माप(काष्ठा uc_css_header) + uc_fw->ucode_size;
पूर्ण

/**
 * पूर्णांकel_uc_fw_get_upload_size() - Get size of firmware needed to be uploaded.
 * @uc_fw: uC firmware.
 *
 * Get the size of the firmware and header that will be uploaded to WOPCM.
 *
 * Return: Upload firmware size, or zero on firmware fetch failure.
 */
अटल अंतरभूत u32 पूर्णांकel_uc_fw_get_upload_size(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	अगर (!पूर्णांकel_uc_fw_is_available(uc_fw))
		वापस 0;

	वापस __पूर्णांकel_uc_fw_get_upload_size(uc_fw);
पूर्ण

व्योम पूर्णांकel_uc_fw_init_early(काष्ठा पूर्णांकel_uc_fw *uc_fw,
			    क्रमागत पूर्णांकel_uc_fw_type type);
पूर्णांक पूर्णांकel_uc_fw_fetch(काष्ठा पूर्णांकel_uc_fw *uc_fw);
व्योम पूर्णांकel_uc_fw_cleanup_fetch(काष्ठा पूर्णांकel_uc_fw *uc_fw);
पूर्णांक पूर्णांकel_uc_fw_upload(काष्ठा पूर्णांकel_uc_fw *uc_fw, u32 offset, u32 dma_flags);
पूर्णांक पूर्णांकel_uc_fw_init(काष्ठा पूर्णांकel_uc_fw *uc_fw);
व्योम पूर्णांकel_uc_fw_fini(काष्ठा पूर्णांकel_uc_fw *uc_fw);
माप_प्रकार पूर्णांकel_uc_fw_copy_rsa(काष्ठा पूर्णांकel_uc_fw *uc_fw, व्योम *dst, u32 max_len);
व्योम पूर्णांकel_uc_fw_dump(स्थिर काष्ठा पूर्णांकel_uc_fw *uc_fw, काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
