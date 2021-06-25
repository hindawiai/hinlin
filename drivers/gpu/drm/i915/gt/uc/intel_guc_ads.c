<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2019 Intel Corporation
 */

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_lrc.h"
#समावेश "intel_guc_ads.h"
#समावेश "intel_uc.h"
#समावेश "i915_drv.h"

/*
 * The Additional Data Struct (ADS) has poपूर्णांकers क्रम dअगरferent buffers used by
 * the GuC. One single gem object contains the ADS काष्ठा itself (guc_ads) and
 * all the extra buffers indirectly linked via the ADS काष्ठा's entries.
 *
 * Layout of the ADS blob allocated क्रम the GuC:
 *
 *      +---------------------------------------+ <== base
 *      | guc_ads                               |
 *      +---------------------------------------+
 *      | guc_policies                          |
 *      +---------------------------------------+
 *      | guc_gt_प्रणाली_info                    |
 *      +---------------------------------------+
 *      | guc_clients_info                      |
 *      +---------------------------------------+
 *      | guc_ct_pool_entry[size]               |
 *      +---------------------------------------+
 *      | padding                               |
 *      +---------------------------------------+ <== 4K aligned
 *      | निजी data                          |
 *      +---------------------------------------+
 *      | padding                               |
 *      +---------------------------------------+ <== 4K aligned
 */
काष्ठा __guc_ads_blob अणु
	काष्ठा guc_ads ads;
	काष्ठा guc_policies policies;
	काष्ठा guc_gt_प्रणाली_info प्रणाली_info;
	काष्ठा guc_clients_info clients_info;
	काष्ठा guc_ct_pool_entry ct_pool[GUC_CT_POOL_SIZE];
पूर्ण __packed;

अटल u32 guc_ads_निजी_data_size(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस PAGE_ALIGN(guc->fw.निजी_data_size);
पूर्ण

अटल u32 guc_ads_निजी_data_offset(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस PAGE_ALIGN(माप(काष्ठा __guc_ads_blob));
पूर्ण

अटल u32 guc_ads_blob_size(काष्ठा पूर्णांकel_guc *guc)
अणु
	वापस guc_ads_निजी_data_offset(guc) +
	       guc_ads_निजी_data_size(guc);
पूर्ण

अटल व्योम guc_policy_init(काष्ठा guc_policy *policy)
अणु
	policy->execution_quantum = POLICY_DEFAULT_EXECUTION_QUANTUM_US;
	policy->preemption_समय = POLICY_DEFAULT_PREEMPTION_TIME_US;
	policy->fault_समय = POLICY_DEFAULT_FAULT_TIME_US;
	policy->policy_flags = 0;
पूर्ण

अटल व्योम guc_policies_init(काष्ठा guc_policies *policies)
अणु
	काष्ठा guc_policy *policy;
	u32 p, i;

	policies->dpc_promote_समय = POLICY_DEFAULT_DPC_PROMOTE_TIME_US;
	policies->max_num_work_items = POLICY_MAX_NUM_WI;

	क्रम (p = 0; p < GUC_CLIENT_PRIORITY_NUM; p++) अणु
		क्रम (i = 0; i < GUC_MAX_ENGINE_CLASSES; i++) अणु
			policy = &policies->policy[p][i];

			guc_policy_init(policy);
		पूर्ण
	पूर्ण

	policies->is_valid = 1;
पूर्ण

अटल व्योम guc_ct_pool_entries_init(काष्ठा guc_ct_pool_entry *pool, u32 num)
अणु
	स_रखो(pool, 0, num * माप(*pool));
पूर्ण

अटल व्योम guc_mapping_table_init(काष्ठा पूर्णांकel_gt *gt,
				   काष्ठा guc_gt_प्रणाली_info *प्रणाली_info)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* Table must be set to invalid values क्रम entries not used */
	क्रम (i = 0; i < GUC_MAX_ENGINE_CLASSES; ++i)
		क्रम (j = 0; j < GUC_MAX_INSTANCES_PER_CLASS; ++j)
			प्रणाली_info->mapping_table[i][j] =
				GUC_MAX_INSTANCES_PER_CLASS;

	क्रम_each_engine(engine, gt, id) अणु
		u8 guc_class = engine->class;

		प्रणाली_info->mapping_table[guc_class][engine->instance] =
			engine->instance;
	पूर्ण
पूर्ण

/*
 * The first 80 dwords of the रेजिस्टर state context, containing the
 * execlists and ppgtt रेजिस्टरs.
 */
#घोषणा LR_HW_CONTEXT_SIZE	(80 * माप(u32))

अटल व्योम __guc_ads_init(काष्ठा पूर्णांकel_guc *guc)
अणु
	काष्ठा पूर्णांकel_gt *gt = guc_to_gt(guc);
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा __guc_ads_blob *blob = guc->ads_blob;
	स्थिर u32 skipped_size = LRC_PPHWSP_SZ * PAGE_SIZE + LR_HW_CONTEXT_SIZE;
	u32 base;
	u8 engine_class;

	/* GuC scheduling policies */
	guc_policies_init(&blob->policies);

	/*
	 * GuC expects a per-engine-class context image and size
	 * (minus hwsp and ring context). The context image will be
	 * used to reinitialize engines after a reset. It must exist
	 * and be pinned in the GGTT, so that the address won't change after
	 * we have told GuC where to find it. The context size will be used
	 * to validate that the LRC base + size fall within allowed GGTT.
	 */
	क्रम (engine_class = 0; engine_class <= MAX_ENGINE_CLASS; ++engine_class) अणु
		अगर (engine_class == OTHER_CLASS)
			जारी;
		/*
		 * TODO: Set context poपूर्णांकer to शेष state to allow
		 * GuC to re-init guilty contexts after पूर्णांकernal reset.
		 */
		blob->ads.golden_context_lrca[engine_class] = 0;
		blob->ads.eng_state_size[engine_class] =
			पूर्णांकel_engine_context_size(guc_to_gt(guc),
						  engine_class) -
			skipped_size;
	पूर्ण

	/* System info */
	blob->प्रणाली_info.engine_enabled_masks[RENDER_CLASS] = 1;
	blob->प्रणाली_info.engine_enabled_masks[COPY_ENGINE_CLASS] = 1;
	blob->प्रणाली_info.engine_enabled_masks[VIDEO_DECODE_CLASS] = VDBOX_MASK(gt);
	blob->प्रणाली_info.engine_enabled_masks[VIDEO_ENHANCEMENT_CLASS] = VEBOX_MASK(gt);

	blob->प्रणाली_info.generic_gt_sysinfo[GUC_GENERIC_GT_SYSINFO_SLICE_ENABLED] =
		hweight8(gt->info.sseu.slice_mask);
	blob->प्रणाली_info.generic_gt_sysinfo[GUC_GENERIC_GT_SYSINFO_VDBOX_SFC_SUPPORT_MASK] =
		gt->info.vdbox_sfc_access;

	अगर (INTEL_GEN(i915) >= 12 && !IS_DGFX(i915)) अणु
		u32 distdbreg = पूर्णांकel_uncore_पढ़ो(gt->uncore,
						  GEN12_DIST_DBS_POPULATED);
		blob->प्रणाली_info.generic_gt_sysinfo[GUC_GENERIC_GT_SYSINFO_DOORBELL_COUNT_PER_SQIDI] =
			((distdbreg >> GEN12_DOORBELLS_PER_SQIDI_SHIFT) &
			 GEN12_DOORBELLS_PER_SQIDI) + 1;
	पूर्ण

	guc_mapping_table_init(guc_to_gt(guc), &blob->प्रणाली_info);

	base = पूर्णांकel_guc_ggtt_offset(guc, guc->ads_vma);

	/* Clients info  */
	guc_ct_pool_entries_init(blob->ct_pool, ARRAY_SIZE(blob->ct_pool));

	blob->clients_info.clients_num = 1;
	blob->clients_info.ct_pool_addr = base + ptr_offset(blob, ct_pool);
	blob->clients_info.ct_pool_count = ARRAY_SIZE(blob->ct_pool);

	/* ADS */
	blob->ads.scheduler_policies = base + ptr_offset(blob, policies);
	blob->ads.gt_प्रणाली_info = base + ptr_offset(blob, प्रणाली_info);
	blob->ads.clients_info = base + ptr_offset(blob, clients_info);

	/* Private Data */
	blob->ads.निजी_data = base + guc_ads_निजी_data_offset(guc);

	i915_gem_object_flush_map(guc->ads_vma->obj);
पूर्ण

/**
 * पूर्णांकel_guc_ads_create() - allocates and initializes GuC ADS.
 * @guc: पूर्णांकel_guc काष्ठा
 *
 * GuC needs memory block (Additional Data Struct), where it will store
 * some data. Allocate and initialize such memory block क्रम GuC use.
 */
पूर्णांक पूर्णांकel_guc_ads_create(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 size;
	पूर्णांक ret;

	GEM_BUG_ON(guc->ads_vma);

	size = guc_ads_blob_size(guc);

	ret = पूर्णांकel_guc_allocate_and_map_vma(guc, size, &guc->ads_vma,
					     (व्योम **)&guc->ads_blob);
	अगर (ret)
		वापस ret;

	__guc_ads_init(guc);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_guc_ads_destroy(काष्ठा पूर्णांकel_guc *guc)
अणु
	i915_vma_unpin_and_release(&guc->ads_vma, I915_VMA_RELEASE_MAP);
	guc->ads_blob = शून्य;
पूर्ण

अटल व्योम guc_ads_निजी_data_reset(काष्ठा पूर्णांकel_guc *guc)
अणु
	u32 size;

	size = guc_ads_निजी_data_size(guc);
	अगर (!size)
		वापस;

	स_रखो((व्योम *)guc->ads_blob + guc_ads_निजी_data_offset(guc), 0,
	       size);
पूर्ण

/**
 * पूर्णांकel_guc_ads_reset() - prepares GuC Additional Data Struct क्रम reuse
 * @guc: पूर्णांकel_guc काष्ठा
 *
 * GuC stores some data in ADS, which might be stale after a reset.
 * Reinitialize whole ADS in हाल any part of it was corrupted during
 * previous GuC run.
 */
व्योम पूर्णांकel_guc_ads_reset(काष्ठा पूर्णांकel_guc *guc)
अणु
	अगर (!guc->ads_vma)
		वापस;

	__guc_ads_init(guc);

	guc_ads_निजी_data_reset(guc);
पूर्ण
