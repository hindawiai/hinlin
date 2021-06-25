<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016-2019 Intel Corporation
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/firmware.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "intel_uc_fw.h"
#समावेश "intel_uc_fw_abi.h"
#समावेश "i915_drv.h"

अटल अंतरभूत काष्ठा पूर्णांकel_gt *
____uc_fw_to_gt(काष्ठा पूर्णांकel_uc_fw *uc_fw, क्रमागत पूर्णांकel_uc_fw_type type)
अणु
	अगर (type == INTEL_UC_FW_TYPE_GUC)
		वापस container_of(uc_fw, काष्ठा पूर्णांकel_gt, uc.guc.fw);

	GEM_BUG_ON(type != INTEL_UC_FW_TYPE_HUC);
	वापस container_of(uc_fw, काष्ठा पूर्णांकel_gt, uc.huc.fw);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_gt *__uc_fw_to_gt(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	GEM_BUG_ON(uc_fw->status == INTEL_UC_FIRMWARE_UNINITIALIZED);
	वापस ____uc_fw_to_gt(uc_fw, uc_fw->type);
पूर्ण

#अगर_घोषित CONFIG_DRM_I915_DEBUG_GUC
व्योम पूर्णांकel_uc_fw_change_status(काष्ठा पूर्णांकel_uc_fw *uc_fw,
			       क्रमागत पूर्णांकel_uc_fw_status status)
अणु
	uc_fw->__status =  status;
	drm_dbg(&__uc_fw_to_gt(uc_fw)->i915->drm,
		"%s firmware -> %s\n",
		पूर्णांकel_uc_fw_type_repr(uc_fw->type),
		status == INTEL_UC_FIRMWARE_SELECTED ?
		uc_fw->path : पूर्णांकel_uc_fw_status_repr(status));
पूर्ण
#पूर्ण_अगर

/*
 * List of required GuC and HuC binaries per-platक्रमm.
 * Must be ordered based on platक्रमm + revid, from newer to older.
 *
 * Note that RKL and ADL-S have the same GuC/HuC device ID's and use the same
 * firmware as TGL.
 */
#घोषणा INTEL_UC_FIRMWARE_DEFS(fw_def, guc_def, huc_def) \
	fw_def(ALDERLAKE_S, 0, guc_def(tgl, 49, 0, 1), huc_def(tgl,  7, 5, 0)) \
	fw_def(ROCKETLAKE,  0, guc_def(tgl, 49, 0, 1), huc_def(tgl,  7, 5, 0)) \
	fw_def(TIGERLAKE,   0, guc_def(tgl, 49, 0, 1), huc_def(tgl,  7, 5, 0)) \
	fw_def(JASPERLAKE,  0, guc_def(ehl, 49, 0, 1), huc_def(ehl,  9, 0, 0)) \
	fw_def(ELKHARTLAKE, 0, guc_def(ehl, 49, 0, 1), huc_def(ehl,  9, 0, 0)) \
	fw_def(ICELAKE,     0, guc_def(icl, 49, 0, 1), huc_def(icl,  9, 0, 0)) \
	fw_def(COMETLAKE,   5, guc_def(cml, 49, 0, 1), huc_def(cml,  4, 0, 0)) \
	fw_def(COMETLAKE,   0, guc_def(kbl, 49, 0, 1), huc_def(kbl,  4, 0, 0)) \
	fw_def(COFFEELAKE,  0, guc_def(kbl, 49, 0, 1), huc_def(kbl,  4, 0, 0)) \
	fw_def(GEMINILAKE,  0, guc_def(glk, 49, 0, 1), huc_def(glk,  4, 0, 0)) \
	fw_def(KABYLAKE,    0, guc_def(kbl, 49, 0, 1), huc_def(kbl,  4, 0, 0)) \
	fw_def(BROXTON,     0, guc_def(bxt, 49, 0, 1), huc_def(bxt,  2, 0, 0)) \
	fw_def(SKYLAKE,     0, guc_def(skl, 49, 0, 1), huc_def(skl,  2, 0, 0))

#घोषणा __MAKE_UC_FW_PATH(prefix_, name_, major_, minor_, patch_) \
	"i915/" \
	__stringअगरy(prefix_) name_ \
	__stringअगरy(major_) "." \
	__stringअगरy(minor_) "." \
	__stringअगरy(patch_) ".bin"

#घोषणा MAKE_GUC_FW_PATH(prefix_, major_, minor_, patch_) \
	__MAKE_UC_FW_PATH(prefix_, "_guc_", major_, minor_, patch_)

#घोषणा MAKE_HUC_FW_PATH(prefix_, major_, minor_, bld_num_) \
	__MAKE_UC_FW_PATH(prefix_, "_huc_", major_, minor_, bld_num_)

/* All blobs need to be declared via MODULE_FIRMWARE() */
#घोषणा INTEL_UC_MODULE_FW(platक्रमm_, revid_, guc_, huc_) \
	MODULE_FIRMWARE(guc_); \
	MODULE_FIRMWARE(huc_);

INTEL_UC_FIRMWARE_DEFS(INTEL_UC_MODULE_FW, MAKE_GUC_FW_PATH, MAKE_HUC_FW_PATH)

/* The below काष्ठाs and macros are used to iterate across the list of blobs */
काष्ठा __packed uc_fw_blob अणु
	u8 major;
	u8 minor;
	स्थिर अक्षर *path;
पूर्ण;

#घोषणा UC_FW_BLOB(major_, minor_, path_) \
	अणु .major = major_, .minor = minor_, .path = path_ पूर्ण

#घोषणा GUC_FW_BLOB(prefix_, major_, minor_, patch_) \
	UC_FW_BLOB(major_, minor_, \
		   MAKE_GUC_FW_PATH(prefix_, major_, minor_, patch_))

#घोषणा HUC_FW_BLOB(prefix_, major_, minor_, bld_num_) \
	UC_FW_BLOB(major_, minor_, \
		   MAKE_HUC_FW_PATH(prefix_, major_, minor_, bld_num_))

काष्ठा __packed uc_fw_platक्रमm_requirement अणु
	क्रमागत पूर्णांकel_platक्रमm p;
	u8 rev; /* first platक्रमm rev using this FW */
	स्थिर काष्ठा uc_fw_blob blobs[INTEL_UC_FW_NUM_TYPES];
पूर्ण;

#घोषणा MAKE_FW_LIST(platक्रमm_, revid_, guc_, huc_) \
अणु \
	.p = INTEL_##platक्रमm_, \
	.rev = revid_, \
	.blobs[INTEL_UC_FW_TYPE_GUC] = guc_, \
	.blobs[INTEL_UC_FW_TYPE_HUC] = huc_, \
पूर्ण,

अटल व्योम
__uc_fw_स्वतः_select(काष्ठा drm_i915_निजी *i915, काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	अटल स्थिर काष्ठा uc_fw_platक्रमm_requirement fw_blobs[] = अणु
		INTEL_UC_FIRMWARE_DEFS(MAKE_FW_LIST, GUC_FW_BLOB, HUC_FW_BLOB)
	पूर्ण;
	क्रमागत पूर्णांकel_platक्रमm p = INTEL_INFO(i915)->platक्रमm;
	u8 rev = INTEL_REVID(i915);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_blobs) && p <= fw_blobs[i].p; i++) अणु
		अगर (p == fw_blobs[i].p && rev >= fw_blobs[i].rev) अणु
			स्थिर काष्ठा uc_fw_blob *blob =
					&fw_blobs[i].blobs[uc_fw->type];
			uc_fw->path = blob->path;
			uc_fw->major_ver_wanted = blob->major;
			uc_fw->minor_ver_wanted = blob->minor;
			अवरोध;
		पूर्ण
	पूर्ण

	/* make sure the list is ordered as expected */
	अगर (IS_ENABLED(CONFIG_DRM_I915_SELFTEST)) अणु
		क्रम (i = 1; i < ARRAY_SIZE(fw_blobs); i++) अणु
			अगर (fw_blobs[i].p < fw_blobs[i - 1].p)
				जारी;

			अगर (fw_blobs[i].p == fw_blobs[i - 1].p &&
			    fw_blobs[i].rev < fw_blobs[i - 1].rev)
				जारी;

			pr_err("invalid FW blob order: %s r%u comes before %s r%u\n",
			       पूर्णांकel_platक्रमm_name(fw_blobs[i - 1].p),
			       fw_blobs[i - 1].rev,
			       पूर्णांकel_platक्रमm_name(fw_blobs[i].p),
			       fw_blobs[i].rev);

			uc_fw->path = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *__override_guc_firmware_path(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (i915->params.enable_guc & ENABLE_GUC_MASK)
		वापस i915->params.guc_firmware_path;
	वापस "";
पूर्ण

अटल स्थिर अक्षर *__override_huc_firmware_path(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (i915->params.enable_guc & ENABLE_GUC_LOAD_HUC)
		वापस i915->params.huc_firmware_path;
	वापस "";
पूर्ण

अटल व्योम __uc_fw_user_override(काष्ठा drm_i915_निजी *i915, काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	स्थिर अक्षर *path = शून्य;

	चयन (uc_fw->type) अणु
	हाल INTEL_UC_FW_TYPE_GUC:
		path = __override_guc_firmware_path(i915);
		अवरोध;
	हाल INTEL_UC_FW_TYPE_HUC:
		path = __override_huc_firmware_path(i915);
		अवरोध;
	पूर्ण

	अगर (unlikely(path)) अणु
		uc_fw->path = path;
		uc_fw->user_overridden = true;
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_uc_fw_init_early - initialize the uC object and select the firmware
 * @uc_fw: uC firmware
 * @type: type of uC
 *
 * Initialize the state of our uC object and relevant tracking and select the
 * firmware to fetch and load.
 */
व्योम पूर्णांकel_uc_fw_init_early(काष्ठा पूर्णांकel_uc_fw *uc_fw,
			    क्रमागत पूर्णांकel_uc_fw_type type)
अणु
	काष्ठा drm_i915_निजी *i915 = ____uc_fw_to_gt(uc_fw, type)->i915;

	/*
	 * we use FIRMWARE_UNINITIALIZED to detect checks against uc_fw->status
	 * beक्रमe we're looked at the HW caps to see अगर we have uc support
	 */
	BUILD_BUG_ON(INTEL_UC_FIRMWARE_UNINITIALIZED);
	GEM_BUG_ON(uc_fw->status);
	GEM_BUG_ON(uc_fw->path);

	uc_fw->type = type;

	अगर (HAS_GT_UC(i915)) अणु
		__uc_fw_स्वतः_select(i915, uc_fw);
		__uc_fw_user_override(i915, uc_fw);
	पूर्ण

	पूर्णांकel_uc_fw_change_status(uc_fw, uc_fw->path ? *uc_fw->path ?
				  INTEL_UC_FIRMWARE_SELECTED :
				  INTEL_UC_FIRMWARE_DISABLED :
				  INTEL_UC_FIRMWARE_NOT_SUPPORTED);
पूर्ण

अटल व्योम __क्रमce_fw_fetch_failures(काष्ठा पूर्णांकel_uc_fw *uc_fw, पूर्णांक e)
अणु
	काष्ठा drm_i915_निजी *i915 = __uc_fw_to_gt(uc_fw)->i915;
	bool user = e == -EINVAL;

	अगर (i915_inject_probe_error(i915, e)) अणु
		/* non-existing blob */
		uc_fw->path = "<invalid>";
		uc_fw->user_overridden = user;
	पूर्ण अन्यथा अगर (i915_inject_probe_error(i915, e)) अणु
		/* require next major version */
		uc_fw->major_ver_wanted += 1;
		uc_fw->minor_ver_wanted = 0;
		uc_fw->user_overridden = user;
	पूर्ण अन्यथा अगर (i915_inject_probe_error(i915, e)) अणु
		/* require next minor version */
		uc_fw->minor_ver_wanted += 1;
		uc_fw->user_overridden = user;
	पूर्ण अन्यथा अगर (uc_fw->major_ver_wanted &&
		   i915_inject_probe_error(i915, e)) अणु
		/* require prev major version */
		uc_fw->major_ver_wanted -= 1;
		uc_fw->minor_ver_wanted = 0;
		uc_fw->user_overridden = user;
	पूर्ण अन्यथा अगर (uc_fw->minor_ver_wanted &&
		   i915_inject_probe_error(i915, e)) अणु
		/* require prev minor version - hey, this should work! */
		uc_fw->minor_ver_wanted -= 1;
		uc_fw->user_overridden = user;
	पूर्ण अन्यथा अगर (user && i915_inject_probe_error(i915, e)) अणु
		/* officially unsupported platक्रमm */
		uc_fw->major_ver_wanted = 0;
		uc_fw->minor_ver_wanted = 0;
		uc_fw->user_overridden = true;
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_uc_fw_fetch - fetch uC firmware
 * @uc_fw: uC firmware
 *
 * Fetch uC firmware पूर्णांकo GEM obj.
 *
 * Return: 0 on success, a negative त्रुटि_सं code on failure.
 */
पूर्णांक पूर्णांकel_uc_fw_fetch(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	काष्ठा drm_i915_निजी *i915 = __uc_fw_to_gt(uc_fw)->i915;
	काष्ठा device *dev = i915->drm.dev;
	काष्ठा drm_i915_gem_object *obj;
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा uc_css_header *css;
	माप_प्रकार size;
	पूर्णांक err;

	GEM_BUG_ON(!i915->wopcm.size);
	GEM_BUG_ON(!पूर्णांकel_uc_fw_is_enabled(uc_fw));

	err = i915_inject_probe_error(i915, -ENXIO);
	अगर (err)
		जाओ fail;

	__क्रमce_fw_fetch_failures(uc_fw, -EINVAL);
	__क्रमce_fw_fetch_failures(uc_fw, -ESTALE);

	err = request_firmware(&fw, uc_fw->path, dev);
	अगर (err)
		जाओ fail;

	/* Check the size of the blob beक्रमe examining buffer contents */
	अगर (unlikely(fw->size < माप(काष्ठा uc_css_header))) अणु
		drm_warn(&i915->drm, "%s firmware %s: invalid size: %zu < %zu\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 fw->size, माप(काष्ठा uc_css_header));
		err = -ENODATA;
		जाओ fail;
	पूर्ण

	css = (काष्ठा uc_css_header *)fw->data;

	/* Check पूर्णांकegrity of size values inside CSS header */
	size = (css->header_size_dw - css->key_size_dw - css->modulus_size_dw -
		css->exponent_size_dw) * माप(u32);
	अगर (unlikely(size != माप(काष्ठा uc_css_header))) अणु
		drm_warn(&i915->drm,
			 "%s firmware %s: unexpected header size: %zu != %zu\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 fw->size, माप(काष्ठा uc_css_header));
		err = -EPROTO;
		जाओ fail;
	पूर्ण

	/* uCode size must calculated from other sizes */
	uc_fw->ucode_size = (css->size_dw - css->header_size_dw) * माप(u32);

	/* now RSA */
	अगर (unlikely(css->key_size_dw != UOS_RSA_SCRATCH_COUNT)) अणु
		drm_warn(&i915->drm, "%s firmware %s: unexpected key size: %u != %u\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 css->key_size_dw, UOS_RSA_SCRATCH_COUNT);
		err = -EPROTO;
		जाओ fail;
	पूर्ण
	uc_fw->rsa_size = css->key_size_dw * माप(u32);

	/* At least, it should have header, uCode and RSA. Size of all three. */
	size = माप(काष्ठा uc_css_header) + uc_fw->ucode_size + uc_fw->rsa_size;
	अगर (unlikely(fw->size < size)) अणु
		drm_warn(&i915->drm, "%s firmware %s: invalid size: %zu < %zu\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 fw->size, size);
		err = -ENOEXEC;
		जाओ fail;
	पूर्ण

	/* Sanity check whether this fw is not larger than whole WOPCM memory */
	size = __पूर्णांकel_uc_fw_get_upload_size(uc_fw);
	अगर (unlikely(size >= i915->wopcm.size)) अणु
		drm_warn(&i915->drm, "%s firmware %s: invalid size: %zu > %zu\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 size, (माप_प्रकार)i915->wopcm.size);
		err = -E2BIG;
		जाओ fail;
	पूर्ण

	/* Get version numbers from the CSS header */
	uc_fw->major_ver_found = FIELD_GET(CSS_SW_VERSION_UC_MAJOR,
					   css->sw_version);
	uc_fw->minor_ver_found = FIELD_GET(CSS_SW_VERSION_UC_MINOR,
					   css->sw_version);

	अगर (uc_fw->major_ver_found != uc_fw->major_ver_wanted ||
	    uc_fw->minor_ver_found < uc_fw->minor_ver_wanted) अणु
		drm_notice(&i915->drm, "%s firmware %s: unexpected version: %u.%u != %u.%u\n",
			   पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			   uc_fw->major_ver_found, uc_fw->minor_ver_found,
			   uc_fw->major_ver_wanted, uc_fw->minor_ver_wanted);
		अगर (!पूर्णांकel_uc_fw_is_overridden(uc_fw)) अणु
			err = -ENOEXEC;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (uc_fw->type == INTEL_UC_FW_TYPE_GUC)
		uc_fw->निजी_data_size = css->निजी_data_size;

	obj = i915_gem_object_create_shmem_from_data(i915, fw->data, fw->size);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ fail;
	पूर्ण

	uc_fw->obj = obj;
	uc_fw->size = fw->size;
	पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_AVAILABLE);

	release_firmware(fw);
	वापस 0;

fail:
	पूर्णांकel_uc_fw_change_status(uc_fw, err == -ENOENT ?
				  INTEL_UC_FIRMWARE_MISSING :
				  INTEL_UC_FIRMWARE_ERROR);

	drm_notice(&i915->drm, "%s firmware %s: fetch failed with error %d\n",
		   पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path, err);
	drm_info(&i915->drm, "%s firmware(s) can be downloaded from %s\n",
		 पूर्णांकel_uc_fw_type_repr(uc_fw->type), INTEL_UC_FIRMWARE_URL);

	release_firmware(fw);		/* OK even अगर fw is शून्य */
	वापस err;
पूर्ण

अटल u32 uc_fw_ggtt_offset(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	काष्ठा i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	काष्ठा drm_mm_node *node = &ggtt->uc_fw;

	GEM_BUG_ON(!drm_mm_node_allocated(node));
	GEM_BUG_ON(upper_32_bits(node->start));
	GEM_BUG_ON(upper_32_bits(node->start + node->size - 1));

	वापस lower_32_bits(node->start);
पूर्ण

अटल व्योम uc_fw_bind_ggtt(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	काष्ठा drm_i915_gem_object *obj = uc_fw->obj;
	काष्ठा i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	काष्ठा i915_vma dummy = अणु
		.node.start = uc_fw_ggtt_offset(uc_fw),
		.node.size = obj->base.size,
		.pages = obj->mm.pages,
		.vm = &ggtt->vm,
	पूर्ण;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	GEM_BUG_ON(dummy.node.size > ggtt->uc_fw.size);

	/* uc_fw->obj cache करोमुख्यs were not controlled across suspend */
	drm_clflush_sg(dummy.pages);

	ggtt->vm.insert_entries(&ggtt->vm, &dummy, I915_CACHE_NONE, 0);
पूर्ण

अटल व्योम uc_fw_unbind_ggtt(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	काष्ठा drm_i915_gem_object *obj = uc_fw->obj;
	काष्ठा i915_ggtt *ggtt = __uc_fw_to_gt(uc_fw)->ggtt;
	u64 start = uc_fw_ggtt_offset(uc_fw);

	ggtt->vm.clear_range(&ggtt->vm, start, obj->base.size);
पूर्ण

अटल पूर्णांक uc_fw_xfer(काष्ठा पूर्णांकel_uc_fw *uc_fw, u32 dst_offset, u32 dma_flags)
अणु
	काष्ठा पूर्णांकel_gt *gt = __uc_fw_to_gt(uc_fw);
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u64 offset;
	पूर्णांक ret;

	ret = i915_inject_probe_error(gt->i915, -ETIMEDOUT);
	अगर (ret)
		वापस ret;

	पूर्णांकel_uncore_क्रमcewake_get(uncore, FORCEWAKE_ALL);

	/* Set the source address क्रम the uCode */
	offset = uc_fw_ggtt_offset(uc_fw);
	GEM_BUG_ON(upper_32_bits(offset) & 0xFFFF0000);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_ADDR_0_LOW, lower_32_bits(offset));
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_ADDR_0_HIGH, upper_32_bits(offset));

	/* Set the DMA destination */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_ADDR_1_LOW, dst_offset);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_ADDR_1_HIGH, DMA_ADDRESS_SPACE_WOPCM);

	/*
	 * Set the transfer size. The header plus uCode will be copied to WOPCM
	 * via DMA, excluding any other components
	 */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_COPY_SIZE,
			      माप(काष्ठा uc_css_header) + uc_fw->ucode_size);

	/* Start the DMA */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_CTRL,
			      _MASKED_BIT_ENABLE(dma_flags | START_DMA));

	/* Wait क्रम DMA to finish */
	ret = पूर्णांकel_रुको_क्रम_रेजिस्टर_fw(uncore, DMA_CTRL, START_DMA, 0, 100);
	अगर (ret)
		drm_err(&gt->i915->drm, "DMA for %s fw failed, DMA_CTRL=%u\n",
			पूर्णांकel_uc_fw_type_repr(uc_fw->type),
			पूर्णांकel_uncore_पढ़ो_fw(uncore, DMA_CTRL));

	/* Disable the bits once DMA is over */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, DMA_CTRL, _MASKED_BIT_DISABLE(dma_flags));

	पूर्णांकel_uncore_क्रमcewake_put(uncore, FORCEWAKE_ALL);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_uc_fw_upload - load uC firmware using custom loader
 * @uc_fw: uC firmware
 * @dst_offset: destination offset
 * @dma_flags: flags क्रम flags क्रम dma ctrl
 *
 * Loads uC firmware and updates पूर्णांकernal flags.
 *
 * Return: 0 on success, non-zero on failure.
 */
पूर्णांक पूर्णांकel_uc_fw_upload(काष्ठा पूर्णांकel_uc_fw *uc_fw, u32 dst_offset, u32 dma_flags)
अणु
	काष्ठा पूर्णांकel_gt *gt = __uc_fw_to_gt(uc_fw);
	पूर्णांक err;

	/* make sure the status was cleared the last समय we reset the uc */
	GEM_BUG_ON(पूर्णांकel_uc_fw_is_loaded(uc_fw));

	err = i915_inject_probe_error(gt->i915, -ENOEXEC);
	अगर (err)
		वापस err;

	अगर (!पूर्णांकel_uc_fw_is_loadable(uc_fw))
		वापस -ENOEXEC;

	/* Call custom loader */
	uc_fw_bind_ggtt(uc_fw);
	err = uc_fw_xfer(uc_fw, dst_offset, dma_flags);
	uc_fw_unbind_ggtt(uc_fw);
	अगर (err)
		जाओ fail;

	पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_TRANSFERRED);
	वापस 0;

fail:
	i915_probe_error(gt->i915, "Failed to load %s firmware %s (%d)\n",
			 पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path,
			 err);
	पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_FAIL);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_uc_fw_init(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	पूर्णांक err;

	/* this should happen beक्रमe the load! */
	GEM_BUG_ON(पूर्णांकel_uc_fw_is_loaded(uc_fw));

	अगर (!पूर्णांकel_uc_fw_is_available(uc_fw))
		वापस -ENOEXEC;

	err = i915_gem_object_pin_pages_unlocked(uc_fw->obj);
	अगर (err) अणु
		DRM_DEBUG_DRIVER("%s fw pin-pages err=%d\n",
				 पूर्णांकel_uc_fw_type_repr(uc_fw->type), err);
		पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_FAIL);
	पूर्ण

	वापस err;
पूर्ण

व्योम पूर्णांकel_uc_fw_fini(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	अगर (i915_gem_object_has_pinned_pages(uc_fw->obj))
		i915_gem_object_unpin_pages(uc_fw->obj);

	पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_AVAILABLE);
पूर्ण

/**
 * पूर्णांकel_uc_fw_cleanup_fetch - cleanup uC firmware
 * @uc_fw: uC firmware
 *
 * Cleans up uC firmware by releasing the firmware GEM obj.
 */
व्योम पूर्णांकel_uc_fw_cleanup_fetch(काष्ठा पूर्णांकel_uc_fw *uc_fw)
अणु
	अगर (!पूर्णांकel_uc_fw_is_available(uc_fw))
		वापस;

	i915_gem_object_put(fetch_and_zero(&uc_fw->obj));

	पूर्णांकel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_SELECTED);
पूर्ण

/**
 * पूर्णांकel_uc_fw_copy_rsa - copy fw RSA to buffer
 *
 * @uc_fw: uC firmware
 * @dst: dst buffer
 * @max_len: max number of bytes to copy
 *
 * Return: number of copied bytes.
 */
माप_प्रकार पूर्णांकel_uc_fw_copy_rsa(काष्ठा पूर्णांकel_uc_fw *uc_fw, व्योम *dst, u32 max_len)
अणु
	काष्ठा sg_table *pages = uc_fw->obj->mm.pages;
	u32 size = min_t(u32, uc_fw->rsa_size, max_len);
	u32 offset = माप(काष्ठा uc_css_header) + uc_fw->ucode_size;

	GEM_BUG_ON(!पूर्णांकel_uc_fw_is_available(uc_fw));

	वापस sg_pcopy_to_buffer(pages->sgl, pages->nents, dst, size, offset);
पूर्ण

/**
 * पूर्णांकel_uc_fw_dump - dump inक्रमmation about uC firmware
 * @uc_fw: uC firmware
 * @p: the &drm_prपूर्णांकer
 *
 * Pretty prपूर्णांकer क्रम uC firmware.
 */
व्योम पूर्णांकel_uc_fw_dump(स्थिर काष्ठा पूर्णांकel_uc_fw *uc_fw, काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "%s firmware: %s\n",
		   पूर्णांकel_uc_fw_type_repr(uc_fw->type), uc_fw->path);
	drm_म_लिखो(p, "\tstatus: %s\n",
		   पूर्णांकel_uc_fw_status_repr(uc_fw->status));
	drm_म_लिखो(p, "\tversion: wanted %u.%u, found %u.%u\n",
		   uc_fw->major_ver_wanted, uc_fw->minor_ver_wanted,
		   uc_fw->major_ver_found, uc_fw->minor_ver_found);
	drm_म_लिखो(p, "\tuCode: %u bytes\n", uc_fw->ucode_size);
	drm_म_लिखो(p, "\tRSA: %u bytes\n", uc_fw->rsa_size);
पूर्ण
