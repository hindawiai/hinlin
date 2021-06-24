<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_sseu.h"

व्योम पूर्णांकel_sseu_set_info(काष्ठा sseu_dev_info *sseu, u8 max_slices,
			 u8 max_subslices, u8 max_eus_per_subslice)
अणु
	sseu->max_slices = max_slices;
	sseu->max_subslices = max_subslices;
	sseu->max_eus_per_subslice = max_eus_per_subslice;

	sseu->ss_stride = GEN_SSEU_STRIDE(sseu->max_subslices);
	GEM_BUG_ON(sseu->ss_stride > GEN_MAX_SUBSLICE_STRIDE);
	sseu->eu_stride = GEN_SSEU_STRIDE(sseu->max_eus_per_subslice);
	GEM_BUG_ON(sseu->eu_stride > GEN_MAX_EU_STRIDE);
पूर्ण

अचिन्हित पूर्णांक
पूर्णांकel_sseu_subslice_total(स्थिर काष्ठा sseu_dev_info *sseu)
अणु
	अचिन्हित पूर्णांक i, total = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sseu->subslice_mask); i++)
		total += hweight8(sseu->subslice_mask[i]);

	वापस total;
पूर्ण

u32 पूर्णांकel_sseu_get_subslices(स्थिर काष्ठा sseu_dev_info *sseu, u8 slice)
अणु
	पूर्णांक i, offset = slice * sseu->ss_stride;
	u32 mask = 0;

	GEM_BUG_ON(slice >= sseu->max_slices);

	क्रम (i = 0; i < sseu->ss_stride; i++)
		mask |= (u32)sseu->subslice_mask[offset + i] <<
			i * BITS_PER_BYTE;

	वापस mask;
पूर्ण

व्योम पूर्णांकel_sseu_set_subslices(काष्ठा sseu_dev_info *sseu, पूर्णांक slice,
			      u32 ss_mask)
अणु
	पूर्णांक offset = slice * sseu->ss_stride;

	स_नकल(&sseu->subslice_mask[offset], &ss_mask, sseu->ss_stride);
पूर्ण

अचिन्हित पूर्णांक
पूर्णांकel_sseu_subslices_per_slice(स्थिर काष्ठा sseu_dev_info *sseu, u8 slice)
अणु
	वापस hweight32(पूर्णांकel_sseu_get_subslices(sseu, slice));
पूर्ण

अटल पूर्णांक sseu_eu_idx(स्थिर काष्ठा sseu_dev_info *sseu, पूर्णांक slice,
		       पूर्णांक subslice)
अणु
	पूर्णांक slice_stride = sseu->max_subslices * sseu->eu_stride;

	वापस slice * slice_stride + subslice * sseu->eu_stride;
पूर्ण

अटल u16 sseu_get_eus(स्थिर काष्ठा sseu_dev_info *sseu, पूर्णांक slice,
			पूर्णांक subslice)
अणु
	पूर्णांक i, offset = sseu_eu_idx(sseu, slice, subslice);
	u16 eu_mask = 0;

	क्रम (i = 0; i < sseu->eu_stride; i++)
		eu_mask |=
			((u16)sseu->eu_mask[offset + i]) << (i * BITS_PER_BYTE);

	वापस eu_mask;
पूर्ण

अटल व्योम sseu_set_eus(काष्ठा sseu_dev_info *sseu, पूर्णांक slice, पूर्णांक subslice,
			 u16 eu_mask)
अणु
	पूर्णांक i, offset = sseu_eu_idx(sseu, slice, subslice);

	क्रम (i = 0; i < sseu->eu_stride; i++)
		sseu->eu_mask[offset + i] =
			(eu_mask >> (BITS_PER_BYTE * i)) & 0xff;
पूर्ण

अटल u16 compute_eu_total(स्थिर काष्ठा sseu_dev_info *sseu)
अणु
	u16 i, total = 0;

	क्रम (i = 0; i < ARRAY_SIZE(sseu->eu_mask); i++)
		total += hweight8(sseu->eu_mask[i]);

	वापस total;
पूर्ण

अटल व्योम gen11_compute_sseu_info(काष्ठा sseu_dev_info *sseu,
				    u8 s_en, u32 ss_en, u16 eu_en)
अणु
	पूर्णांक s, ss;

	/* ss_en represents entire subslice mask across all slices */
	GEM_BUG_ON(sseu->max_slices * sseu->max_subslices >
		   माप(ss_en) * BITS_PER_BYTE);

	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		अगर ((s_en & BIT(s)) == 0)
			जारी;

		sseu->slice_mask |= BIT(s);

		पूर्णांकel_sseu_set_subslices(sseu, s, ss_en);

		क्रम (ss = 0; ss < sseu->max_subslices; ss++)
			अगर (पूर्णांकel_sseu_has_subslice(sseu, s, ss))
				sseu_set_eus(sseu, s, ss, eu_en);
	पूर्ण
	sseu->eu_per_subslice = hweight16(eu_en);
	sseu->eu_total = compute_eu_total(sseu);
पूर्ण

अटल व्योम gen12_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 dss_en;
	u16 eu_en = 0;
	u8 eu_en_fuse;
	u8 s_en;
	पूर्णांक eu;

	/*
	 * Gen12 has Dual-Subslices, which behave similarly to 2 gen11 SS.
	 * Instead of splitting these, provide userspace with an array
	 * of DSS to more बंदly represent the hardware resource.
	 */
	पूर्णांकel_sseu_set_info(sseu, 1, 6, 16);

	s_en = पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GT_SLICE_ENABLE) &
		GEN11_GT_S_ENA_MASK;

	dss_en = पूर्णांकel_uncore_पढ़ो(uncore, GEN12_GT_DSS_ENABLE);

	/* one bit per pair of EUs */
	eu_en_fuse = ~(पूर्णांकel_uncore_पढ़ो(uncore, GEN11_EU_DISABLE) &
		       GEN11_EU_DIS_MASK);
	क्रम (eu = 0; eu < sseu->max_eus_per_subslice / 2; eu++)
		अगर (eu_en_fuse & BIT(eu))
			eu_en |= BIT(eu * 2) | BIT(eu * 2 + 1);

	gen11_compute_sseu_info(sseu, s_en, dss_en, eu_en);

	/* TGL only supports slice-level घातer gating */
	sseu->has_slice_pg = 1;
पूर्ण

अटल व्योम gen11_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 ss_en;
	u8 eu_en;
	u8 s_en;

	अगर (IS_JSL_EHL(gt->i915))
		पूर्णांकel_sseu_set_info(sseu, 1, 4, 8);
	अन्यथा
		पूर्णांकel_sseu_set_info(sseu, 1, 8, 8);

	s_en = पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GT_SLICE_ENABLE) &
		GEN11_GT_S_ENA_MASK;
	ss_en = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN11_GT_SUBSLICE_DISABLE);

	eu_en = ~(पूर्णांकel_uncore_पढ़ो(uncore, GEN11_EU_DISABLE) &
		  GEN11_EU_DIS_MASK);

	gen11_compute_sseu_info(sseu, s_en, ss_en, eu_en);

	/* ICL has no घातer gating restrictions. */
	sseu->has_slice_pg = 1;
	sseu->has_subslice_pg = 1;
	sseu->has_eu_pg = 1;
पूर्ण

अटल व्योम gen10_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	स्थिर u32 fuse2 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_FUSE2);
	स्थिर पूर्णांक eu_mask = 0xff;
	u32 subslice_mask, eu_en;
	पूर्णांक s, ss;

	पूर्णांकel_sseu_set_info(sseu, 6, 4, 8);

	sseu->slice_mask = (fuse2 & GEN10_F2_S_ENA_MASK) >>
		GEN10_F2_S_ENA_SHIFT;

	/* Slice0 */
	eu_en = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE0);
	क्रम (ss = 0; ss < sseu->max_subslices; ss++)
		sseu_set_eus(sseu, 0, ss, (eu_en >> (8 * ss)) & eu_mask);
	/* Slice1 */
	sseu_set_eus(sseu, 1, 0, (eu_en >> 24) & eu_mask);
	eu_en = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE1);
	sseu_set_eus(sseu, 1, 1, eu_en & eu_mask);
	/* Slice2 */
	sseu_set_eus(sseu, 2, 0, (eu_en >> 8) & eu_mask);
	sseu_set_eus(sseu, 2, 1, (eu_en >> 16) & eu_mask);
	/* Slice3 */
	sseu_set_eus(sseu, 3, 0, (eu_en >> 24) & eu_mask);
	eu_en = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE2);
	sseu_set_eus(sseu, 3, 1, eu_en & eu_mask);
	/* Slice4 */
	sseu_set_eus(sseu, 4, 0, (eu_en >> 8) & eu_mask);
	sseu_set_eus(sseu, 4, 1, (eu_en >> 16) & eu_mask);
	/* Slice5 */
	sseu_set_eus(sseu, 5, 0, (eu_en >> 24) & eu_mask);
	eu_en = ~पूर्णांकel_uncore_पढ़ो(uncore, GEN10_EU_DISABLE3);
	sseu_set_eus(sseu, 5, 1, eu_en & eu_mask);

	subslice_mask = (1 << 4) - 1;
	subslice_mask &= ~((fuse2 & GEN10_F2_SS_DIS_MASK) >>
			   GEN10_F2_SS_DIS_SHIFT);

	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		u32 subslice_mask_with_eus = subslice_mask;

		क्रम (ss = 0; ss < sseu->max_subslices; ss++) अणु
			अगर (sseu_get_eus(sseu, s, ss) == 0)
				subslice_mask_with_eus &= ~BIT(ss);
		पूर्ण

		/*
		 * Slice0 can have up to 3 subslices, but there are only 2 in
		 * slice1/2.
		 */
		पूर्णांकel_sseu_set_subslices(sseu, s, s == 0 ?
					 subslice_mask_with_eus :
					 subslice_mask_with_eus & 0x3);
	पूर्ण

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * CNL is expected to always have a unअगरorm distribution
	 * of EU across subslices with the exception that any one
	 * EU in any one subslice may be fused off क्रम die
	 * recovery.
	 */
	sseu->eu_per_subslice =
		पूर्णांकel_sseu_subslice_total(sseu) ?
		DIV_ROUND_UP(sseu->eu_total, पूर्णांकel_sseu_subslice_total(sseu)) :
		0;

	/* No restrictions on Power Gating */
	sseu->has_slice_pg = 1;
	sseu->has_subslice_pg = 1;
	sseu->has_eu_pg = 1;
पूर्ण

अटल व्योम cherryview_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	u32 fuse;
	u8 subslice_mask = 0;

	fuse = पूर्णांकel_uncore_पढ़ो(gt->uncore, CHV_FUSE_GT);

	sseu->slice_mask = BIT(0);
	पूर्णांकel_sseu_set_info(sseu, 1, 2, 8);

	अगर (!(fuse & CHV_FGT_DISABLE_SS0)) अणु
		u8 disabled_mask =
			((fuse & CHV_FGT_EU_DIS_SS0_R0_MASK) >>
			 CHV_FGT_EU_DIS_SS0_R0_SHIFT) |
			(((fuse & CHV_FGT_EU_DIS_SS0_R1_MASK) >>
			  CHV_FGT_EU_DIS_SS0_R1_SHIFT) << 4);

		subslice_mask |= BIT(0);
		sseu_set_eus(sseu, 0, 0, ~disabled_mask);
	पूर्ण

	अगर (!(fuse & CHV_FGT_DISABLE_SS1)) अणु
		u8 disabled_mask =
			((fuse & CHV_FGT_EU_DIS_SS1_R0_MASK) >>
			 CHV_FGT_EU_DIS_SS1_R0_SHIFT) |
			(((fuse & CHV_FGT_EU_DIS_SS1_R1_MASK) >>
			  CHV_FGT_EU_DIS_SS1_R1_SHIFT) << 4);

		subslice_mask |= BIT(1);
		sseu_set_eus(sseu, 0, 1, ~disabled_mask);
	पूर्ण

	पूर्णांकel_sseu_set_subslices(sseu, 0, subslice_mask);

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * CHV expected to always have a unअगरorm distribution of EU
	 * across subslices.
	 */
	sseu->eu_per_subslice = पूर्णांकel_sseu_subslice_total(sseu) ?
		sseu->eu_total /
		पूर्णांकel_sseu_subslice_total(sseu) :
		0;
	/*
	 * CHV supports subslice घातer gating on devices with more than
	 * one subslice, and supports EU घातer gating on devices with
	 * more than one EU pair per subslice.
	 */
	sseu->has_slice_pg = 0;
	sseu->has_subslice_pg = पूर्णांकel_sseu_subslice_total(sseu) > 1;
	sseu->has_eu_pg = (sseu->eu_per_subslice > 2);
पूर्ण

अटल व्योम gen9_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_device_info *info = mkग_लिखो_device_info(i915);
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	u32 fuse2, eu_disable, subslice_mask;
	स्थिर u8 eu_mask = 0xff;
	पूर्णांक s, ss;

	fuse2 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_FUSE2);
	sseu->slice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;

	/* BXT has a single slice and at most 3 subslices. */
	पूर्णांकel_sseu_set_info(sseu, IS_GEN9_LP(i915) ? 1 : 3,
			    IS_GEN9_LP(i915) ? 3 : 4, 8);

	/*
	 * The subslice disable field is global, i.e. it applies
	 * to each of the enabled slices.
	 */
	subslice_mask = (1 << sseu->max_subslices) - 1;
	subslice_mask &= ~((fuse2 & GEN9_F2_SS_DIS_MASK) >>
			   GEN9_F2_SS_DIS_SHIFT);

	/*
	 * Iterate through enabled slices and subslices to
	 * count the total enabled EU.
	 */
	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		अगर (!(sseu->slice_mask & BIT(s)))
			/* skip disabled slice */
			जारी;

		पूर्णांकel_sseu_set_subslices(sseu, s, subslice_mask);

		eu_disable = पूर्णांकel_uncore_पढ़ो(uncore, GEN9_EU_DISABLE(s));
		क्रम (ss = 0; ss < sseu->max_subslices; ss++) अणु
			पूर्णांक eu_per_ss;
			u8 eu_disabled_mask;

			अगर (!पूर्णांकel_sseu_has_subslice(sseu, s, ss))
				/* skip disabled subslice */
				जारी;

			eu_disabled_mask = (eu_disable >> (ss * 8)) & eu_mask;

			sseu_set_eus(sseu, s, ss, ~eu_disabled_mask);

			eu_per_ss = sseu->max_eus_per_subslice -
				hweight8(eu_disabled_mask);

			/*
			 * Record which subslice(s) has(have) 7 EUs. we
			 * can tune the hash used to spपढ़ो work among
			 * subslices अगर they are unbalanced.
			 */
			अगर (eu_per_ss == 7)
				sseu->subslice_7eu[s] |= BIT(ss);
		पूर्ण
	पूर्ण

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * SKL is expected to always have a unअगरorm distribution
	 * of EU across subslices with the exception that any one
	 * EU in any one subslice may be fused off क्रम die
	 * recovery. BXT is expected to be perfectly unअगरorm in EU
	 * distribution.
	 */
	sseu->eu_per_subslice =
		पूर्णांकel_sseu_subslice_total(sseu) ?
		DIV_ROUND_UP(sseu->eu_total, पूर्णांकel_sseu_subslice_total(sseu)) :
		0;

	/*
	 * SKL+ supports slice घातer gating on devices with more than
	 * one slice, and supports EU घातer gating on devices with
	 * more than one EU pair per subslice. BXT+ supports subslice
	 * घातer gating on devices with more than one subslice, and
	 * supports EU घातer gating on devices with more than one EU
	 * pair per subslice.
	 */
	sseu->has_slice_pg =
		!IS_GEN9_LP(i915) && hweight8(sseu->slice_mask) > 1;
	sseu->has_subslice_pg =
		IS_GEN9_LP(i915) && पूर्णांकel_sseu_subslice_total(sseu) > 1;
	sseu->has_eu_pg = sseu->eu_per_subslice > 2;

	अगर (IS_GEN9_LP(i915)) अणु
#घोषणा IS_SS_DISABLED(ss)	(!(sseu->subslice_mask[0] & BIT(ss)))
		info->has_pooled_eu = hweight8(sseu->subslice_mask[0]) == 3;

		sseu->min_eu_in_pool = 0;
		अगर (info->has_pooled_eu) अणु
			अगर (IS_SS_DISABLED(2) || IS_SS_DISABLED(0))
				sseu->min_eu_in_pool = 3;
			अन्यथा अगर (IS_SS_DISABLED(1))
				sseu->min_eu_in_pool = 6;
			अन्यथा
				sseu->min_eu_in_pool = 9;
		पूर्ण
#अघोषित IS_SS_DISABLED
	पूर्ण
पूर्ण

अटल व्योम bdw_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	पूर्णांक s, ss;
	u32 fuse2, subslice_mask, eu_disable[3]; /* s_max */
	u32 eu_disable0, eu_disable1, eu_disable2;

	fuse2 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_FUSE2);
	sseu->slice_mask = (fuse2 & GEN8_F2_S_ENA_MASK) >> GEN8_F2_S_ENA_SHIFT;
	पूर्णांकel_sseu_set_info(sseu, 3, 3, 8);

	/*
	 * The subslice disable field is global, i.e. it applies
	 * to each of the enabled slices.
	 */
	subslice_mask = GENMASK(sseu->max_subslices - 1, 0);
	subslice_mask &= ~((fuse2 & GEN8_F2_SS_DIS_MASK) >>
			   GEN8_F2_SS_DIS_SHIFT);
	eu_disable0 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE0);
	eu_disable1 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE1);
	eu_disable2 = पूर्णांकel_uncore_पढ़ो(uncore, GEN8_EU_DISABLE2);
	eu_disable[0] = eu_disable0 & GEN8_EU_DIS0_S0_MASK;
	eu_disable[1] = (eu_disable0 >> GEN8_EU_DIS0_S1_SHIFT) |
		((eu_disable1 & GEN8_EU_DIS1_S1_MASK) <<
		 (32 - GEN8_EU_DIS0_S1_SHIFT));
	eu_disable[2] = (eu_disable1 >> GEN8_EU_DIS1_S2_SHIFT) |
		((eu_disable2 & GEN8_EU_DIS2_S2_MASK) <<
		 (32 - GEN8_EU_DIS1_S2_SHIFT));

	/*
	 * Iterate through enabled slices and subslices to
	 * count the total enabled EU.
	 */
	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		अगर (!(sseu->slice_mask & BIT(s)))
			/* skip disabled slice */
			जारी;

		पूर्णांकel_sseu_set_subslices(sseu, s, subslice_mask);

		क्रम (ss = 0; ss < sseu->max_subslices; ss++) अणु
			u8 eu_disabled_mask;
			u32 n_disabled;

			अगर (!पूर्णांकel_sseu_has_subslice(sseu, s, ss))
				/* skip disabled subslice */
				जारी;

			eu_disabled_mask =
				eu_disable[s] >> (ss * sseu->max_eus_per_subslice);

			sseu_set_eus(sseu, s, ss, ~eu_disabled_mask);

			n_disabled = hweight8(eu_disabled_mask);

			/*
			 * Record which subslices have 7 EUs.
			 */
			अगर (sseu->max_eus_per_subslice - n_disabled == 7)
				sseu->subslice_7eu[s] |= 1 << ss;
		पूर्ण
	पूर्ण

	sseu->eu_total = compute_eu_total(sseu);

	/*
	 * BDW is expected to always have a unअगरorm distribution of EU across
	 * subslices with the exception that any one EU in any one subslice may
	 * be fused off क्रम die recovery.
	 */
	sseu->eu_per_subslice =
		पूर्णांकel_sseu_subslice_total(sseu) ?
		DIV_ROUND_UP(sseu->eu_total, पूर्णांकel_sseu_subslice_total(sseu)) :
		0;

	/*
	 * BDW supports slice घातer gating on devices with more than
	 * one slice.
	 */
	sseu->has_slice_pg = hweight8(sseu->slice_mask) > 1;
	sseu->has_subslice_pg = 0;
	sseu->has_eu_pg = 0;
पूर्ण

अटल व्योम hsw_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	u32 fuse1;
	u8 subslice_mask = 0;
	पूर्णांक s, ss;

	/*
	 * There isn't a रेजिस्टर to tell us how many slices/subslices. We
	 * work off the PCI-ids here.
	 */
	चयन (INTEL_INFO(i915)->gt) अणु
	शेष:
		MISSING_CASE(INTEL_INFO(i915)->gt);
		fallthrough;
	हाल 1:
		sseu->slice_mask = BIT(0);
		subslice_mask = BIT(0);
		अवरोध;
	हाल 2:
		sseu->slice_mask = BIT(0);
		subslice_mask = BIT(0) | BIT(1);
		अवरोध;
	हाल 3:
		sseu->slice_mask = BIT(0) | BIT(1);
		subslice_mask = BIT(0) | BIT(1);
		अवरोध;
	पूर्ण

	fuse1 = पूर्णांकel_uncore_पढ़ो(gt->uncore, HSW_PAVP_FUSE1);
	चयन ((fuse1 & HSW_F1_EU_DIS_MASK) >> HSW_F1_EU_DIS_SHIFT) अणु
	शेष:
		MISSING_CASE((fuse1 & HSW_F1_EU_DIS_MASK) >>
			     HSW_F1_EU_DIS_SHIFT);
		fallthrough;
	हाल HSW_F1_EU_DIS_10EUS:
		sseu->eu_per_subslice = 10;
		अवरोध;
	हाल HSW_F1_EU_DIS_8EUS:
		sseu->eu_per_subslice = 8;
		अवरोध;
	हाल HSW_F1_EU_DIS_6EUS:
		sseu->eu_per_subslice = 6;
		अवरोध;
	पूर्ण

	पूर्णांकel_sseu_set_info(sseu, hweight8(sseu->slice_mask),
			    hweight8(subslice_mask),
			    sseu->eu_per_subslice);

	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		पूर्णांकel_sseu_set_subslices(sseu, s, subslice_mask);

		क्रम (ss = 0; ss < sseu->max_subslices; ss++) अणु
			sseu_set_eus(sseu, s, ss,
				     (1UL << sseu->eu_per_subslice) - 1);
		पूर्ण
	पूर्ण

	sseu->eu_total = compute_eu_total(sseu);

	/* No घातergating क्रम you. */
	sseu->has_slice_pg = 0;
	sseu->has_subslice_pg = 0;
	sseu->has_eu_pg = 0;
पूर्ण

व्योम पूर्णांकel_sseu_info_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;

	अगर (IS_HASWELL(i915))
		hsw_sseu_info_init(gt);
	अन्यथा अगर (IS_CHERRYVIEW(i915))
		cherryview_sseu_info_init(gt);
	अन्यथा अगर (IS_BROADWELL(i915))
		bdw_sseu_info_init(gt);
	अन्यथा अगर (IS_GEN(i915, 9))
		gen9_sseu_info_init(gt);
	अन्यथा अगर (IS_GEN(i915, 10))
		gen10_sseu_info_init(gt);
	अन्यथा अगर (IS_GEN(i915, 11))
		gen11_sseu_info_init(gt);
	अन्यथा अगर (INTEL_GEN(i915) >= 12)
		gen12_sseu_info_init(gt);
पूर्ण

u32 पूर्णांकel_sseu_make_rpcs(काष्ठा पूर्णांकel_gt *gt,
			 स्थिर काष्ठा पूर्णांकel_sseu *req_sseu)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	स्थिर काष्ठा sseu_dev_info *sseu = &gt->info.sseu;
	bool subslice_pg = sseu->has_subslice_pg;
	u8 slices, subslices;
	u32 rpcs = 0;

	/*
	 * No explicit RPCS request is needed to ensure full
	 * slice/subslice/EU enablement prior to Gen9.
	 */
	अगर (INTEL_GEN(i915) < 9)
		वापस 0;

	/*
	 * If i915/perf is active, we want a stable घातergating configuration
	 * on the प्रणाली. Use the configuration pinned by i915/perf.
	 */
	अगर (i915->perf.exclusive_stream)
		req_sseu = &i915->perf.sseu;

	slices = hweight8(req_sseu->slice_mask);
	subslices = hweight8(req_sseu->subslice_mask);

	/*
	 * Since the SScount bitfield in GEN8_R_PWR_CLK_STATE is only three bits
	 * wide and Icelake has up to eight subslices, specfial programming is
	 * needed in order to correctly enable all subslices.
	 *
	 * According to करोcumentation software must consider the configuration
	 * as 2x4x8 and hardware will translate this to 1x8x8.
	 *
	 * Furthemore, even though SScount is three bits, maximum करोcumented
	 * value क्रम it is four. From this some rules/restrictions follow:
	 *
	 * 1.
	 * If enabled subslice count is greater than four, two whole slices must
	 * be enabled instead.
	 *
	 * 2.
	 * When more than one slice is enabled, hardware ignores the subslice
	 * count altogether.
	 *
	 * From these restrictions it follows that it is not possible to enable
	 * a count of subslices between the SScount maximum of four restriction,
	 * and the maximum available number on a particular SKU. Either all
	 * subslices are enabled, or a count between one and four on the first
	 * slice.
	 */
	अगर (IS_GEN(i915, 11) &&
	    slices == 1 &&
	    subslices > min_t(u8, 4, hweight8(sseu->subslice_mask[0]) / 2)) अणु
		GEM_BUG_ON(subslices & 1);

		subslice_pg = false;
		slices *= 2;
	पूर्ण

	/*
	 * Starting in Gen9, render घातer gating can leave
	 * slice/subslice/EU in a partially enabled state. We
	 * must make an explicit request through RPCS क्रम full
	 * enablement.
	 */
	अगर (sseu->has_slice_pg) अणु
		u32 mask, val = slices;

		अगर (INTEL_GEN(i915) >= 11) अणु
			mask = GEN11_RPCS_S_CNT_MASK;
			val <<= GEN11_RPCS_S_CNT_SHIFT;
		पूर्ण अन्यथा अणु
			mask = GEN8_RPCS_S_CNT_MASK;
			val <<= GEN8_RPCS_S_CNT_SHIFT;
		पूर्ण

		GEM_BUG_ON(val & ~mask);
		val &= mask;

		rpcs |= GEN8_RPCS_ENABLE | GEN8_RPCS_S_CNT_ENABLE | val;
	पूर्ण

	अगर (subslice_pg) अणु
		u32 val = subslices;

		val <<= GEN8_RPCS_SS_CNT_SHIFT;

		GEM_BUG_ON(val & ~GEN8_RPCS_SS_CNT_MASK);
		val &= GEN8_RPCS_SS_CNT_MASK;

		rpcs |= GEN8_RPCS_ENABLE | GEN8_RPCS_SS_CNT_ENABLE | val;
	पूर्ण

	अगर (sseu->has_eu_pg) अणु
		u32 val;

		val = req_sseu->min_eus_per_subslice << GEN8_RPCS_EU_MIN_SHIFT;
		GEM_BUG_ON(val & ~GEN8_RPCS_EU_MIN_MASK);
		val &= GEN8_RPCS_EU_MIN_MASK;

		rpcs |= val;

		val = req_sseu->max_eus_per_subslice << GEN8_RPCS_EU_MAX_SHIFT;
		GEM_BUG_ON(val & ~GEN8_RPCS_EU_MAX_MASK);
		val &= GEN8_RPCS_EU_MAX_MASK;

		rpcs |= val;

		rpcs |= GEN8_RPCS_ENABLE;
	पूर्ण

	वापस rpcs;
पूर्ण

व्योम पूर्णांकel_sseu_dump(स्थिर काष्ठा sseu_dev_info *sseu, काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक s;

	drm_म_लिखो(p, "slice total: %u, mask=%04x\n",
		   hweight8(sseu->slice_mask), sseu->slice_mask);
	drm_म_लिखो(p, "subslice total: %u\n", पूर्णांकel_sseu_subslice_total(sseu));
	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		drm_म_लिखो(p, "slice%d: %u subslices, mask=%08x\n",
			   s, पूर्णांकel_sseu_subslices_per_slice(sseu, s),
			   पूर्णांकel_sseu_get_subslices(sseu, s));
	पूर्ण
	drm_म_लिखो(p, "EU total: %u\n", sseu->eu_total);
	drm_म_लिखो(p, "EU per subslice: %u\n", sseu->eu_per_subslice);
	drm_म_लिखो(p, "has slice power gating: %s\n",
		   yesno(sseu->has_slice_pg));
	drm_म_लिखो(p, "has subslice power gating: %s\n",
		   yesno(sseu->has_subslice_pg));
	drm_म_लिखो(p, "has EU power gating: %s\n", yesno(sseu->has_eu_pg));
पूर्ण

व्योम पूर्णांकel_sseu_prपूर्णांक_topology(स्थिर काष्ठा sseu_dev_info *sseu,
			       काष्ठा drm_prपूर्णांकer *p)
अणु
	पूर्णांक s, ss;

	अगर (sseu->max_slices == 0) अणु
		drm_म_लिखो(p, "Unavailable\n");
		वापस;
	पूर्ण

	क्रम (s = 0; s < sseu->max_slices; s++) अणु
		drm_म_लिखो(p, "slice%d: %u subslice(s) (0x%08x):\n",
			   s, पूर्णांकel_sseu_subslices_per_slice(sseu, s),
			   पूर्णांकel_sseu_get_subslices(sseu, s));

		क्रम (ss = 0; ss < sseu->max_subslices; ss++) अणु
			u16 enabled_eus = sseu_get_eus(sseu, s, ss);

			drm_म_लिखो(p, "\tsubslice%d: %u EUs (0x%hx)\n",
				   ss, hweight16(enabled_eus), enabled_eus);
		पूर्ण
	पूर्ण
पूर्ण
