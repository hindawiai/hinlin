<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020,2021 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_step.h"

/*
 * KBL revision ID ordering is bizarre; higher revision ID's map to lower
 * steppings in some हालs.  So rather than test against the revision ID
 * directly, let's map that into our own range of increasing ID's that we
 * can test against in a regular manner.
 */


/* FIXME: what about REVID_E0 */
अटल स्थिर काष्ठा पूर्णांकel_step_info kbl_revids[] = अणु
	[0] = अणु .gt_step = STEP_A0, .display_step = STEP_A0 पूर्ण,
	[1] = अणु .gt_step = STEP_B0, .display_step = STEP_B0 पूर्ण,
	[2] = अणु .gt_step = STEP_C0, .display_step = STEP_B0 पूर्ण,
	[3] = अणु .gt_step = STEP_D0, .display_step = STEP_B0 पूर्ण,
	[4] = अणु .gt_step = STEP_F0, .display_step = STEP_C0 पूर्ण,
	[5] = अणु .gt_step = STEP_C0, .display_step = STEP_B1 पूर्ण,
	[6] = अणु .gt_step = STEP_D1, .display_step = STEP_B1 पूर्ण,
	[7] = अणु .gt_step = STEP_G0, .display_step = STEP_C0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_step_info tgl_uy_revid_step_tbl[] = अणु
	[0] = अणु .gt_step = STEP_A0, .display_step = STEP_A0 पूर्ण,
	[1] = अणु .gt_step = STEP_B0, .display_step = STEP_C0 पूर्ण,
	[2] = अणु .gt_step = STEP_B1, .display_step = STEP_C0 पूर्ण,
	[3] = अणु .gt_step = STEP_C0, .display_step = STEP_D0 पूर्ण,
पूर्ण;

/* Same GT stepping between tgl_uy_revids and tgl_revids करोn't mean the same HW */
अटल स्थिर काष्ठा पूर्णांकel_step_info tgl_revid_step_tbl[] = अणु
	[0] = अणु .gt_step = STEP_A0, .display_step = STEP_B0 पूर्ण,
	[1] = अणु .gt_step = STEP_B0, .display_step = STEP_D0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_step_info adls_revid_step_tbl[] = अणु
	[0x0] = अणु .gt_step = STEP_A0, .display_step = STEP_A0 पूर्ण,
	[0x1] = अणु .gt_step = STEP_A0, .display_step = STEP_A2 पूर्ण,
	[0x4] = अणु .gt_step = STEP_B0, .display_step = STEP_B0 पूर्ण,
	[0x8] = अणु .gt_step = STEP_C0, .display_step = STEP_B0 पूर्ण,
	[0xC] = अणु .gt_step = STEP_D0, .display_step = STEP_C0 पूर्ण,
पूर्ण;

व्योम पूर्णांकel_step_init(काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर काष्ठा पूर्णांकel_step_info *revids = शून्य;
	पूर्णांक size = 0;
	पूर्णांक revid = INTEL_REVID(i915);
	काष्ठा पूर्णांकel_step_info step = अणुपूर्ण;

	अगर (IS_ALDERLAKE_S(i915)) अणु
		revids = adls_revid_step_tbl;
		size = ARRAY_SIZE(adls_revid_step_tbl);
	पूर्ण अन्यथा अगर (IS_TGL_U(i915) || IS_TGL_Y(i915)) अणु
		revids = tgl_uy_revid_step_tbl;
		size = ARRAY_SIZE(tgl_uy_revid_step_tbl);
	पूर्ण अन्यथा अगर (IS_TIGERLAKE(i915)) अणु
		revids = tgl_revid_step_tbl;
		size = ARRAY_SIZE(tgl_revid_step_tbl);
	पूर्ण अन्यथा अगर (IS_KABYLAKE(i915)) अणु
		revids = kbl_revids;
		size = ARRAY_SIZE(kbl_revids);
	पूर्ण

	/* Not using the stepping scheme क्रम the platक्रमm yet. */
	अगर (!revids)
		वापस;

	अगर (revid < size && revids[revid].gt_step != STEP_NONE) अणु
		step = revids[revid];
	पूर्ण अन्यथा अणु
		drm_warn(&i915->drm, "Unknown revid 0x%02x\n", revid);

		/*
		 * If we hit a gap in the revid array, use the inक्रमmation क्रम
		 * the next revid.
		 *
		 * This may be wrong in all sorts of ways, especially अगर the
		 * steppings in the array are not monotonically increasing, but
		 * it's better than शेषing to 0.
		 */
		जबतक (revid < size && revids[revid].gt_step == STEP_NONE)
			revid++;

		अगर (revid < size) अणु
			drm_dbg(&i915->drm, "Using steppings for revid 0x%02x\n",
				revid);
			step = revids[revid];
		पूर्ण अन्यथा अणु
			drm_dbg(&i915->drm, "Using future steppings\n");
			step.gt_step = STEP_FUTURE;
			step.display_step = STEP_FUTURE;
		पूर्ण
	पूर्ण

	अगर (drm_WARN_ON(&i915->drm, step.gt_step == STEP_NONE))
		वापस;

	RUNTIME_INFO(i915)->step = step;
पूर्ण
