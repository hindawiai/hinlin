<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "debugfs_gt.h"
#समावेश "intel_sseu_debugfs.h"
#समावेश "i915_drv.h"

अटल व्योम sseu_copy_subslices(स्थिर काष्ठा sseu_dev_info *sseu,
				पूर्णांक slice, u8 *to_mask)
अणु
	पूर्णांक offset = slice * sseu->ss_stride;

	स_नकल(&to_mask[offset], &sseu->subslice_mask[offset], sseu->ss_stride);
पूर्ण

अटल व्योम cherryview_sseu_device_status(काष्ठा पूर्णांकel_gt *gt,
					  काष्ठा sseu_dev_info *sseu)
अणु
#घोषणा SS_MAX 2
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	स्थिर पूर्णांक ss_max = SS_MAX;
	u32 sig1[SS_MAX], sig2[SS_MAX];
	पूर्णांक ss;

	sig1[0] = पूर्णांकel_uncore_पढ़ो(uncore, CHV_POWER_SS0_SIG1);
	sig1[1] = पूर्णांकel_uncore_पढ़ो(uncore, CHV_POWER_SS1_SIG1);
	sig2[0] = पूर्णांकel_uncore_पढ़ो(uncore, CHV_POWER_SS0_SIG2);
	sig2[1] = पूर्णांकel_uncore_पढ़ो(uncore, CHV_POWER_SS1_SIG2);

	क्रम (ss = 0; ss < ss_max; ss++) अणु
		अचिन्हित पूर्णांक eu_cnt;

		अगर (sig1[ss] & CHV_SS_PG_ENABLE)
			/* skip disabled subslice */
			जारी;

		sseu->slice_mask = BIT(0);
		sseu->subslice_mask[0] |= BIT(ss);
		eu_cnt = ((sig1[ss] & CHV_EU08_PG_ENABLE) ? 0 : 2) +
			 ((sig1[ss] & CHV_EU19_PG_ENABLE) ? 0 : 2) +
			 ((sig1[ss] & CHV_EU210_PG_ENABLE) ? 0 : 2) +
			 ((sig2[ss] & CHV_EU311_PG_ENABLE) ? 0 : 2);
		sseu->eu_total += eu_cnt;
		sseu->eu_per_subslice = max_t(अचिन्हित पूर्णांक,
					      sseu->eu_per_subslice, eu_cnt);
	पूर्ण
#अघोषित SS_MAX
पूर्ण

अटल व्योम gen10_sseu_device_status(काष्ठा पूर्णांकel_gt *gt,
				     काष्ठा sseu_dev_info *sseu)
अणु
#घोषणा SS_MAX 6
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	स्थिर काष्ठा पूर्णांकel_gt_info *info = &gt->info;
	u32 s_reg[SS_MAX], eu_reg[2 * SS_MAX], eu_mask[2];
	पूर्णांक s, ss;

	क्रम (s = 0; s < info->sseu.max_slices; s++) अणु
		/*
		 * FIXME: Valid SS Mask respects the spec and पढ़ो
		 * only valid bits क्रम those रेजिस्टरs, excluding reserved
		 * although this seems wrong because it would leave many
		 * subslices without ACK.
		 */
		s_reg[s] = पूर्णांकel_uncore_पढ़ो(uncore, GEN10_SLICE_PGCTL_ACK(s)) &
			GEN10_PGCTL_VALID_SS_MASK(s);
		eu_reg[2 * s] = पूर्णांकel_uncore_पढ़ो(uncore,
						  GEN10_SS01_EU_PGCTL_ACK(s));
		eu_reg[2 * s + 1] = पूर्णांकel_uncore_पढ़ो(uncore,
						      GEN10_SS23_EU_PGCTL_ACK(s));
	पूर्ण

	eu_mask[0] = GEN9_PGCTL_SSA_EU08_ACK |
		     GEN9_PGCTL_SSA_EU19_ACK |
		     GEN9_PGCTL_SSA_EU210_ACK |
		     GEN9_PGCTL_SSA_EU311_ACK;
	eu_mask[1] = GEN9_PGCTL_SSB_EU08_ACK |
		     GEN9_PGCTL_SSB_EU19_ACK |
		     GEN9_PGCTL_SSB_EU210_ACK |
		     GEN9_PGCTL_SSB_EU311_ACK;

	क्रम (s = 0; s < info->sseu.max_slices; s++) अणु
		अगर ((s_reg[s] & GEN9_PGCTL_SLICE_ACK) == 0)
			/* skip disabled slice */
			जारी;

		sseu->slice_mask |= BIT(s);
		sseu_copy_subslices(&info->sseu, s, sseu->subslice_mask);

		क्रम (ss = 0; ss < info->sseu.max_subslices; ss++) अणु
			अचिन्हित पूर्णांक eu_cnt;

			अगर (info->sseu.has_subslice_pg &&
			    !(s_reg[s] & (GEN9_PGCTL_SS_ACK(ss))))
				/* skip disabled subslice */
				जारी;

			eu_cnt = 2 * hweight32(eu_reg[2 * s + ss / 2] &
					       eu_mask[ss % 2]);
			sseu->eu_total += eu_cnt;
			sseu->eu_per_subslice = max_t(अचिन्हित पूर्णांक,
						      sseu->eu_per_subslice,
						      eu_cnt);
		पूर्ण
	पूर्ण
#अघोषित SS_MAX
पूर्ण

अटल व्योम gen9_sseu_device_status(काष्ठा पूर्णांकel_gt *gt,
				    काष्ठा sseu_dev_info *sseu)
अणु
#घोषणा SS_MAX 3
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	स्थिर काष्ठा पूर्णांकel_gt_info *info = &gt->info;
	u32 s_reg[SS_MAX], eu_reg[2 * SS_MAX], eu_mask[2];
	पूर्णांक s, ss;

	क्रम (s = 0; s < info->sseu.max_slices; s++) अणु
		s_reg[s] = पूर्णांकel_uncore_पढ़ो(uncore, GEN9_SLICE_PGCTL_ACK(s));
		eu_reg[2 * s] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN9_SS01_EU_PGCTL_ACK(s));
		eu_reg[2 * s + 1] =
			पूर्णांकel_uncore_पढ़ो(uncore, GEN9_SS23_EU_PGCTL_ACK(s));
	पूर्ण

	eu_mask[0] = GEN9_PGCTL_SSA_EU08_ACK |
		     GEN9_PGCTL_SSA_EU19_ACK |
		     GEN9_PGCTL_SSA_EU210_ACK |
		     GEN9_PGCTL_SSA_EU311_ACK;
	eu_mask[1] = GEN9_PGCTL_SSB_EU08_ACK |
		     GEN9_PGCTL_SSB_EU19_ACK |
		     GEN9_PGCTL_SSB_EU210_ACK |
		     GEN9_PGCTL_SSB_EU311_ACK;

	क्रम (s = 0; s < info->sseu.max_slices; s++) अणु
		अगर ((s_reg[s] & GEN9_PGCTL_SLICE_ACK) == 0)
			/* skip disabled slice */
			जारी;

		sseu->slice_mask |= BIT(s);

		अगर (IS_GEN9_BC(gt->i915))
			sseu_copy_subslices(&info->sseu, s,
					    sseu->subslice_mask);

		क्रम (ss = 0; ss < info->sseu.max_subslices; ss++) अणु
			अचिन्हित पूर्णांक eu_cnt;
			u8 ss_idx = s * info->sseu.ss_stride +
				    ss / BITS_PER_BYTE;

			अगर (IS_GEN9_LP(gt->i915)) अणु
				अगर (!(s_reg[s] & (GEN9_PGCTL_SS_ACK(ss))))
					/* skip disabled subslice */
					जारी;

				sseu->subslice_mask[ss_idx] |=
					BIT(ss % BITS_PER_BYTE);
			पूर्ण

			eu_cnt = eu_reg[2 * s + ss / 2] & eu_mask[ss % 2];
			eu_cnt = 2 * hweight32(eu_cnt);

			sseu->eu_total += eu_cnt;
			sseu->eu_per_subslice = max_t(अचिन्हित पूर्णांक,
						      sseu->eu_per_subslice,
						      eu_cnt);
		पूर्ण
	पूर्ण
#अघोषित SS_MAX
पूर्ण

अटल व्योम bdw_sseu_device_status(काष्ठा पूर्णांकel_gt *gt,
				   काष्ठा sseu_dev_info *sseu)
अणु
	स्थिर काष्ठा पूर्णांकel_gt_info *info = &gt->info;
	u32 slice_info = पूर्णांकel_uncore_पढ़ो(gt->uncore, GEN8_GT_SLICE_INFO);
	पूर्णांक s;

	sseu->slice_mask = slice_info & GEN8_LSLICESTAT_MASK;

	अगर (sseu->slice_mask) अणु
		sseu->eu_per_subslice = info->sseu.eu_per_subslice;
		क्रम (s = 0; s < fls(sseu->slice_mask); s++)
			sseu_copy_subslices(&info->sseu, s,
					    sseu->subslice_mask);
		sseu->eu_total = sseu->eu_per_subslice *
				 पूर्णांकel_sseu_subslice_total(sseu);

		/* subtract fused off EU(s) from enabled slice(s) */
		क्रम (s = 0; s < fls(sseu->slice_mask); s++) अणु
			u8 subslice_7eu = info->sseu.subslice_7eu[s];

			sseu->eu_total -= hweight8(subslice_7eu);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम i915_prपूर्णांक_sseu_info(काष्ठा seq_file *m,
				 bool is_available_info,
				 bool has_pooled_eu,
				 स्थिर काष्ठा sseu_dev_info *sseu)
अणु
	स्थिर अक्षर *type = is_available_info ? "Available" : "Enabled";
	पूर्णांक s;

	seq_म_लिखो(m, "  %s Slice Mask: %04x\n", type,
		   sseu->slice_mask);
	seq_म_लिखो(m, "  %s Slice Total: %u\n", type,
		   hweight8(sseu->slice_mask));
	seq_म_लिखो(m, "  %s Subslice Total: %u\n", type,
		   पूर्णांकel_sseu_subslice_total(sseu));
	क्रम (s = 0; s < fls(sseu->slice_mask); s++) अणु
		seq_म_लिखो(m, "  %s Slice%i subslices: %u\n", type,
			   s, पूर्णांकel_sseu_subslices_per_slice(sseu, s));
	पूर्ण
	seq_म_लिखो(m, "  %s EU Total: %u\n", type,
		   sseu->eu_total);
	seq_म_लिखो(m, "  %s EU Per Subslice: %u\n", type,
		   sseu->eu_per_subslice);

	अगर (!is_available_info)
		वापस;

	seq_म_लिखो(m, "  Has Pooled EU: %s\n", yesno(has_pooled_eu));
	अगर (has_pooled_eu)
		seq_म_लिखो(m, "  Min EU in pool: %u\n", sseu->min_eu_in_pool);

	seq_म_लिखो(m, "  Has Slice Power Gating: %s\n",
		   yesno(sseu->has_slice_pg));
	seq_म_लिखो(m, "  Has Subslice Power Gating: %s\n",
		   yesno(sseu->has_subslice_pg));
	seq_म_लिखो(m, "  Has EU Power Gating: %s\n",
		   yesno(sseu->has_eu_pg));
पूर्ण

/*
 * this is called from top-level debugfs as well, so we can't get the gt from
 * the seq_file.
 */
पूर्णांक पूर्णांकel_sseu_status(काष्ठा seq_file *m, काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	स्थिर काष्ठा पूर्णांकel_gt_info *info = &gt->info;
	काष्ठा sseu_dev_info sseu;
	पूर्णांकel_wakeref_t wakeref;

	अगर (INTEL_GEN(i915) < 8)
		वापस -ENODEV;

	seq_माला_दो(m, "SSEU Device Info\n");
	i915_prपूर्णांक_sseu_info(m, true, HAS_POOLED_EU(i915), &info->sseu);

	seq_माला_दो(m, "SSEU Device Status\n");
	स_रखो(&sseu, 0, माप(sseu));
	पूर्णांकel_sseu_set_info(&sseu, info->sseu.max_slices,
			    info->sseu.max_subslices,
			    info->sseu.max_eus_per_subslice);

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		अगर (IS_CHERRYVIEW(i915))
			cherryview_sseu_device_status(gt, &sseu);
		अन्यथा अगर (IS_BROADWELL(i915))
			bdw_sseu_device_status(gt, &sseu);
		अन्यथा अगर (IS_GEN(i915, 9))
			gen9_sseu_device_status(gt, &sseu);
		अन्यथा अगर (INTEL_GEN(i915) >= 10)
			gen10_sseu_device_status(gt, &sseu);
	पूर्ण

	i915_prपूर्णांक_sseu_info(m, false, HAS_POOLED_EU(i915), &sseu);

	वापस 0;
पूर्ण

अटल पूर्णांक sseu_status_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;

	वापस पूर्णांकel_sseu_status(m, gt);
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(sseu_status);

अटल पूर्णांक rcs_topology_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	पूर्णांकel_sseu_prपूर्णांक_topology(&gt->info.sseu, &p);

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(rcs_topology);

व्योम पूर्णांकel_sseu_debugfs_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt, काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "sseu_status", &sseu_status_fops, शून्य पूर्ण,
		अणु "rcs_topology", &rcs_topology_fops, शून्य पूर्ण,
	पूर्ण;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), gt);
पूर्ण
