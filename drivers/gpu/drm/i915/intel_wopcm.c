<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2017-2019 Intel Corporation
 */

#समावेश "intel_wopcm.h"
#समावेश "i915_drv.h"

/**
 * DOC: WOPCM Layout
 *
 * The layout of the WOPCM will be fixed after writing to GuC WOPCM size and
 * offset रेजिस्टरs whose values are calculated and determined by HuC/GuC
 * firmware size and set of hardware requirements/restrictions as shown below:
 *
 * ::
 *
 *    +=========> +====================+ <== WOPCM Top
 *    ^           |  HW contexts RSVD  |
 *    |     +===> +====================+ <== GuC WOPCM Top
 *    |     ^     |                    |
 *    |     |     |                    |
 *    |     |     |                    |
 *    |    GuC    |                    |
 *    |   WOPCM   |                    |
 *    |    Size   +--------------------+
 *  WOPCM   |     |    GuC FW RSVD     |
 *    |     |     +--------------------+
 *    |     |     |   GuC Stack RSVD   |
 *    |     |     +------------------- +
 *    |     v     |   GuC WOPCM RSVD   |
 *    |     +===> +====================+ <== GuC WOPCM base
 *    |           |     WOPCM RSVD     |
 *    |           +------------------- + <== HuC Firmware Top
 *    v           |      HuC FW        |
 *    +=========> +====================+ <== WOPCM Base
 *
 * GuC accessible WOPCM starts at GuC WOPCM base and ends at GuC WOPCM top.
 * The top part of the WOPCM is reserved क्रम hardware contexts (e.g. RC6
 * context).
 */

/* Default WOPCM size is 2MB from Gen11, 1MB on previous platक्रमms */
#घोषणा GEN11_WOPCM_SIZE		SZ_2M
#घोषणा GEN9_WOPCM_SIZE			SZ_1M
/* 16KB WOPCM (RSVD WOPCM) is reserved from HuC firmware top. */
#घोषणा WOPCM_RESERVED_SIZE		SZ_16K

/* 16KB reserved at the beginning of GuC WOPCM. */
#घोषणा GUC_WOPCM_RESERVED		SZ_16K
/* 8KB from GUC_WOPCM_RESERVED is reserved क्रम GuC stack. */
#घोषणा GUC_WOPCM_STACK_RESERVED	SZ_8K

/* GuC WOPCM Offset value needs to be aligned to 16KB. */
#घोषणा GUC_WOPCM_OFFSET_ALIGNMENT	(1UL << GUC_WOPCM_OFFSET_SHIFT)

/* 24KB at the end of WOPCM is reserved क्रम RC6 CTX on BXT. */
#घोषणा BXT_WOPCM_RC6_CTX_RESERVED	(SZ_16K + SZ_8K)
/* 36KB WOPCM reserved at the end of WOPCM on CNL. */
#घोषणा CNL_WOPCM_HW_CTX_RESERVED	(SZ_32K + SZ_4K)

/* 128KB from GUC_WOPCM_RESERVED is reserved क्रम FW on Gen9. */
#घोषणा GEN9_GUC_FW_RESERVED	SZ_128K
#घोषणा GEN9_GUC_WOPCM_OFFSET	(GUC_WOPCM_RESERVED + GEN9_GUC_FW_RESERVED)

अटल अंतरभूत काष्ठा drm_i915_निजी *wopcm_to_i915(काष्ठा पूर्णांकel_wopcm *wopcm)
अणु
	वापस container_of(wopcm, काष्ठा drm_i915_निजी, wopcm);
पूर्ण

/**
 * पूर्णांकel_wopcm_init_early() - Early initialization of the WOPCM.
 * @wopcm: poपूर्णांकer to पूर्णांकel_wopcm.
 *
 * Setup the size of WOPCM which will be used by later on WOPCM partitioning.
 */
व्योम पूर्णांकel_wopcm_init_early(काष्ठा पूर्णांकel_wopcm *wopcm)
अणु
	काष्ठा drm_i915_निजी *i915 = wopcm_to_i915(wopcm);

	अगर (!HAS_GT_UC(i915))
		वापस;

	अगर (INTEL_GEN(i915) >= 11)
		wopcm->size = GEN11_WOPCM_SIZE;
	अन्यथा
		wopcm->size = GEN9_WOPCM_SIZE;

	drm_dbg(&i915->drm, "WOPCM: %uK\n", wopcm->size / 1024);
पूर्ण

अटल u32 context_reserved_size(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (IS_GEN9_LP(i915))
		वापस BXT_WOPCM_RC6_CTX_RESERVED;
	अन्यथा अगर (INTEL_GEN(i915) >= 10)
		वापस CNL_WOPCM_HW_CTX_RESERVED;
	अन्यथा
		वापस 0;
पूर्ण

अटल bool gen9_check_dword_gap(काष्ठा drm_i915_निजी *i915,
				 u32 guc_wopcm_base, u32 guc_wopcm_size)
अणु
	u32 offset;

	/*
	 * GuC WOPCM size shall be at least a dword larger than the offset from
	 * WOPCM base (GuC WOPCM offset from WOPCM base + GEN9_GUC_WOPCM_OFFSET)
	 * due to hardware limitation on Gen9.
	 */
	offset = guc_wopcm_base + GEN9_GUC_WOPCM_OFFSET;
	अगर (offset > guc_wopcm_size ||
	    (guc_wopcm_size - offset) < माप(u32)) अणु
		drm_err(&i915->drm,
			"WOPCM: invalid GuC region size: %uK < %uK\n",
			guc_wopcm_size / SZ_1K,
			(u32)(offset + माप(u32)) / SZ_1K);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool gen9_check_huc_fw_fits(काष्ठा drm_i915_निजी *i915,
				   u32 guc_wopcm_size, u32 huc_fw_size)
अणु
	/*
	 * On Gen9 & CNL A0, hardware requires the total available GuC WOPCM
	 * size to be larger than or equal to HuC firmware size. Otherwise,
	 * firmware uploading would fail.
	 */
	अगर (huc_fw_size > guc_wopcm_size - GUC_WOPCM_RESERVED) अणु
		drm_err(&i915->drm, "WOPCM: no space for %s: %uK < %uK\n",
			पूर्णांकel_uc_fw_type_repr(INTEL_UC_FW_TYPE_HUC),
			(guc_wopcm_size - GUC_WOPCM_RESERVED) / SZ_1K,
			huc_fw_size / 1024);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool check_hw_restrictions(काष्ठा drm_i915_निजी *i915,
				  u32 guc_wopcm_base, u32 guc_wopcm_size,
				  u32 huc_fw_size)
अणु
	अगर (IS_GEN(i915, 9) && !gen9_check_dword_gap(i915, guc_wopcm_base,
						     guc_wopcm_size))
		वापस false;

	अगर (IS_GEN(i915, 9) &&
	    !gen9_check_huc_fw_fits(i915, guc_wopcm_size, huc_fw_size))
		वापस false;

	वापस true;
पूर्ण

अटल bool __check_layout(काष्ठा drm_i915_निजी *i915, u32 wopcm_size,
			   u32 guc_wopcm_base, u32 guc_wopcm_size,
			   u32 guc_fw_size, u32 huc_fw_size)
अणु
	स्थिर u32 ctx_rsvd = context_reserved_size(i915);
	u32 size;

	size = wopcm_size - ctx_rsvd;
	अगर (unlikely(range_overflows(guc_wopcm_base, guc_wopcm_size, size))) अणु
		drm_err(&i915->drm,
			"WOPCM: invalid GuC region layout: %uK + %uK > %uK\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K,
			size / SZ_1K);
		वापस false;
	पूर्ण

	size = guc_fw_size + GUC_WOPCM_RESERVED + GUC_WOPCM_STACK_RESERVED;
	अगर (unlikely(guc_wopcm_size < size)) अणु
		drm_err(&i915->drm, "WOPCM: no space for %s: %uK < %uK\n",
			पूर्णांकel_uc_fw_type_repr(INTEL_UC_FW_TYPE_GUC),
			guc_wopcm_size / SZ_1K, size / SZ_1K);
		वापस false;
	पूर्ण

	size = huc_fw_size + WOPCM_RESERVED_SIZE;
	अगर (unlikely(guc_wopcm_base < size)) अणु
		drm_err(&i915->drm, "WOPCM: no space for %s: %uK < %uK\n",
			पूर्णांकel_uc_fw_type_repr(INTEL_UC_FW_TYPE_HUC),
			guc_wopcm_base / SZ_1K, size / SZ_1K);
		वापस false;
	पूर्ण

	वापस check_hw_restrictions(i915, guc_wopcm_base, guc_wopcm_size,
				     huc_fw_size);
पूर्ण

अटल bool __wopcm_regs_locked(काष्ठा पूर्णांकel_uncore *uncore,
				u32 *guc_wopcm_base, u32 *guc_wopcm_size)
अणु
	u32 reg_base = पूर्णांकel_uncore_पढ़ो(uncore, DMA_GUC_WOPCM_OFFSET);
	u32 reg_size = पूर्णांकel_uncore_पढ़ो(uncore, GUC_WOPCM_SIZE);

	अगर (!(reg_size & GUC_WOPCM_SIZE_LOCKED) ||
	    !(reg_base & GUC_WOPCM_OFFSET_VALID))
		वापस false;

	*guc_wopcm_base = reg_base & GUC_WOPCM_OFFSET_MASK;
	*guc_wopcm_size = reg_size & GUC_WOPCM_SIZE_MASK;
	वापस true;
पूर्ण

/**
 * पूर्णांकel_wopcm_init() - Initialize the WOPCM काष्ठाure.
 * @wopcm: poपूर्णांकer to पूर्णांकel_wopcm.
 *
 * This function will partition WOPCM space based on GuC and HuC firmware sizes
 * and will allocate max reमुख्यing क्रम use by GuC. This function will also
 * enक्रमce platक्रमm dependent hardware restrictions on GuC WOPCM offset and
 * size. It will fail the WOPCM init अगर any of these checks fail, so that the
 * following WOPCM रेजिस्टरs setup and GuC firmware uploading would be पातed.
 */
व्योम पूर्णांकel_wopcm_init(काष्ठा पूर्णांकel_wopcm *wopcm)
अणु
	काष्ठा drm_i915_निजी *i915 = wopcm_to_i915(wopcm);
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	u32 guc_fw_size = पूर्णांकel_uc_fw_get_upload_size(&gt->uc.guc.fw);
	u32 huc_fw_size = पूर्णांकel_uc_fw_get_upload_size(&gt->uc.huc.fw);
	u32 ctx_rsvd = context_reserved_size(i915);
	u32 guc_wopcm_base;
	u32 guc_wopcm_size;

	अगर (!guc_fw_size)
		वापस;

	GEM_BUG_ON(!wopcm->size);
	GEM_BUG_ON(wopcm->guc.base);
	GEM_BUG_ON(wopcm->guc.size);
	GEM_BUG_ON(guc_fw_size >= wopcm->size);
	GEM_BUG_ON(huc_fw_size >= wopcm->size);
	GEM_BUG_ON(ctx_rsvd + WOPCM_RESERVED_SIZE >= wopcm->size);

	अगर (i915_inject_probe_failure(i915))
		वापस;

	अगर (__wopcm_regs_locked(gt->uncore, &guc_wopcm_base, &guc_wopcm_size)) अणु
		drm_dbg(&i915->drm, "GuC WOPCM is already locked [%uK, %uK)\n",
			guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);
		जाओ check;
	पूर्ण

	/*
	 * Aligned value of guc_wopcm_base will determine available WOPCM space
	 * क्रम HuC firmware and mandatory reserved area.
	 */
	guc_wopcm_base = huc_fw_size + WOPCM_RESERVED_SIZE;
	guc_wopcm_base = ALIGN(guc_wopcm_base, GUC_WOPCM_OFFSET_ALIGNMENT);

	/*
	 * Need to clamp guc_wopcm_base now to make sure the following math is
	 * correct. Formal check of whole WOPCM layout will be करोne below.
	 */
	guc_wopcm_base = min(guc_wopcm_base, wopcm->size - ctx_rsvd);

	/* Aligned reमुख्यings of usable WOPCM space can be asचिन्हित to GuC. */
	guc_wopcm_size = wopcm->size - ctx_rsvd - guc_wopcm_base;
	guc_wopcm_size &= GUC_WOPCM_SIZE_MASK;

	drm_dbg(&i915->drm, "Calculated GuC WOPCM [%uK, %uK)\n",
		guc_wopcm_base / SZ_1K, guc_wopcm_size / SZ_1K);

check:
	अगर (__check_layout(i915, wopcm->size, guc_wopcm_base, guc_wopcm_size,
			   guc_fw_size, huc_fw_size)) अणु
		wopcm->guc.base = guc_wopcm_base;
		wopcm->guc.size = guc_wopcm_size;
		GEM_BUG_ON(!wopcm->guc.base);
		GEM_BUG_ON(!wopcm->guc.size);
	पूर्ण
पूर्ण
