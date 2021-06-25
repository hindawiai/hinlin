<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_SSEU_H__
#घोषणा __INTEL_SSEU_H__

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#समावेश "i915_gem.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_gt;
काष्ठा drm_prपूर्णांकer;

#घोषणा GEN_MAX_SLICES		(6) /* CNL upper bound */
#घोषणा GEN_MAX_SUBSLICES	(8) /* ICL upper bound */
#घोषणा GEN_SSEU_STRIDE(max_entries) DIV_ROUND_UP(max_entries, BITS_PER_BYTE)
#घोषणा GEN_MAX_SUBSLICE_STRIDE GEN_SSEU_STRIDE(GEN_MAX_SUBSLICES)
#घोषणा GEN_MAX_EUS		(16) /* TGL upper bound */
#घोषणा GEN_MAX_EU_STRIDE GEN_SSEU_STRIDE(GEN_MAX_EUS)

काष्ठा sseu_dev_info अणु
	u8 slice_mask;
	u8 subslice_mask[GEN_MAX_SLICES * GEN_MAX_SUBSLICE_STRIDE];
	u8 eu_mask[GEN_MAX_SLICES * GEN_MAX_SUBSLICES * GEN_MAX_EU_STRIDE];
	u16 eu_total;
	u8 eu_per_subslice;
	u8 min_eu_in_pool;
	/* For each slice, which subslice(s) has(have) 7 EUs (bitfield)? */
	u8 subslice_7eu[3];
	u8 has_slice_pg:1;
	u8 has_subslice_pg:1;
	u8 has_eu_pg:1;

	/* Topology fields */
	u8 max_slices;
	u8 max_subslices;
	u8 max_eus_per_subslice;

	u8 ss_stride;
	u8 eu_stride;
पूर्ण;

/*
 * Powergating configuration क्रम a particular (context,engine).
 */
काष्ठा पूर्णांकel_sseu अणु
	u8 slice_mask;
	u8 subslice_mask;
	u8 min_eus_per_subslice;
	u8 max_eus_per_subslice;
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_sseu
पूर्णांकel_sseu_from_device_info(स्थिर काष्ठा sseu_dev_info *sseu)
अणु
	काष्ठा पूर्णांकel_sseu value = अणु
		.slice_mask = sseu->slice_mask,
		.subslice_mask = sseu->subslice_mask[0],
		.min_eus_per_subslice = sseu->max_eus_per_subslice,
		.max_eus_per_subslice = sseu->max_eus_per_subslice,
	पूर्ण;

	वापस value;
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_sseu_has_subslice(स्थिर काष्ठा sseu_dev_info *sseu, पूर्णांक slice,
			पूर्णांक subslice)
अणु
	u8 mask;
	पूर्णांक ss_idx = subslice / BITS_PER_BYTE;

	GEM_BUG_ON(ss_idx >= sseu->ss_stride);

	mask = sseu->subslice_mask[slice * sseu->ss_stride + ss_idx];

	वापस mask & BIT(subslice % BITS_PER_BYTE);
पूर्ण

व्योम पूर्णांकel_sseu_set_info(काष्ठा sseu_dev_info *sseu, u8 max_slices,
			 u8 max_subslices, u8 max_eus_per_subslice);

अचिन्हित पूर्णांक
पूर्णांकel_sseu_subslice_total(स्थिर काष्ठा sseu_dev_info *sseu);

अचिन्हित पूर्णांक
पूर्णांकel_sseu_subslices_per_slice(स्थिर काष्ठा sseu_dev_info *sseu, u8 slice);

u32  पूर्णांकel_sseu_get_subslices(स्थिर काष्ठा sseu_dev_info *sseu, u8 slice);

व्योम पूर्णांकel_sseu_set_subslices(काष्ठा sseu_dev_info *sseu, पूर्णांक slice,
			      u32 ss_mask);

व्योम पूर्णांकel_sseu_info_init(काष्ठा पूर्णांकel_gt *gt);

u32 पूर्णांकel_sseu_make_rpcs(काष्ठा पूर्णांकel_gt *gt,
			 स्थिर काष्ठा पूर्णांकel_sseu *req_sseu);

व्योम पूर्णांकel_sseu_dump(स्थिर काष्ठा sseu_dev_info *sseu, काष्ठा drm_prपूर्णांकer *p);
व्योम पूर्णांकel_sseu_prपूर्णांक_topology(स्थिर काष्ठा sseu_dev_info *sseu,
			       काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर /* __INTEL_SSEU_H__ */
