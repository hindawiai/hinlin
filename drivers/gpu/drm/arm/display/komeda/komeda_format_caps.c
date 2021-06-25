<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#समावेश <linux/slab.h>
#समावेश "komeda_format_caps.h"
#समावेश "malidp_utils.h"

स्थिर काष्ठा komeda_क्रमmat_caps *
komeda_get_क्रमmat_caps(काष्ठा komeda_क्रमmat_caps_table *table,
		       u32 fourcc, u64 modअगरier)
अणु
	स्थिर काष्ठा komeda_क्रमmat_caps *caps;
	u64 afbc_features = modअगरier & ~(AFBC_FORMAT_MOD_BLOCK_SIZE_MASK);
	u32 afbc_layout = modअगरier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK;
	पूर्णांक id;

	क्रम (id = 0; id < table->n_क्रमmats; id++) अणु
		caps = &table->क्रमmat_caps[id];

		अगर (fourcc != caps->fourcc)
			जारी;

		अगर ((modअगरier == 0ULL) && (caps->supported_afbc_layouts == 0))
			वापस caps;

		अगर (has_bits(afbc_features, caps->supported_afbc_features) &&
		    has_bit(afbc_layout, caps->supported_afbc_layouts))
			वापस caps;
	पूर्ण

	वापस शून्य;
पूर्ण

u32 komeda_get_afbc_क्रमmat_bpp(स्थिर काष्ठा drm_क्रमmat_info *info, u64 modअगरier)
अणु
	u32 bpp;

	चयन (info->क्रमmat) अणु
	हाल DRM_FORMAT_YUV420_8BIT:
		bpp = 12;
		अवरोध;
	हाल DRM_FORMAT_YUV420_10BIT:
		bpp = 15;
		अवरोध;
	शेष:
		bpp = info->cpp[0] * 8;
		अवरोध;
	पूर्ण

	वापस bpp;
पूर्ण

/* Two assumptions
 * 1. RGB always has YTR
 * 2. Tiled RGB always has SC
 */
u64 komeda_supported_modअगरiers[] = अणु
	/* AFBC_16x16 + features: YUV+RGB both */
	AFBC_16x16(0),
	/* SPARSE */
	AFBC_16x16(_SPARSE),
	/* YTR + (SPARSE) */
	AFBC_16x16(_YTR | _SPARSE),
	AFBC_16x16(_YTR),
	/* SPLIT + SPARSE + YTR RGB only */
	/* split mode is only allowed क्रम sparse mode */
	AFBC_16x16(_SPLIT | _SPARSE | _YTR),
	/* TILED + (SPARSE) */
	/* TILED YUV क्रमmat only */
	AFBC_16x16(_TILED | _SPARSE),
	AFBC_16x16(_TILED),
	/* TILED + SC + (SPLIT+SPARSE | SPARSE) + (YTR) */
	AFBC_16x16(_TILED | _SC | _SPLIT | _SPARSE | _YTR),
	AFBC_16x16(_TILED | _SC | _SPARSE | _YTR),
	AFBC_16x16(_TILED | _SC | _YTR),
	/* AFBC_32x8 + features: which are RGB क्रमmats only */
	/* YTR + (SPARSE) */
	AFBC_32x8(_YTR | _SPARSE),
	AFBC_32x8(_YTR),
	/* SPLIT + SPARSE + (YTR) */
	/* split mode is only allowed क्रम sparse mode */
	AFBC_32x8(_SPLIT | _SPARSE | _YTR),
	/* TILED + SC + (SPLIT+SPARSE | SPARSE) + YTR */
	AFBC_32x8(_TILED | _SC | _SPLIT | _SPARSE | _YTR),
	AFBC_32x8(_TILED | _SC | _SPARSE | _YTR),
	AFBC_32x8(_TILED | _SC | _YTR),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

bool komeda_क्रमmat_mod_supported(काष्ठा komeda_क्रमmat_caps_table *table,
				 u32 layer_type, u32 fourcc, u64 modअगरier,
				 u32 rot)
अणु
	स्थिर काष्ठा komeda_क्रमmat_caps *caps;

	caps = komeda_get_क्रमmat_caps(table, fourcc, modअगरier);
	अगर (!caps)
		वापस false;

	अगर (!(caps->supported_layer_types & layer_type))
		वापस false;

	अगर (table->क्रमmat_mod_supported)
		वापस table->क्रमmat_mod_supported(caps, layer_type, modअगरier,
						   rot);

	वापस true;
पूर्ण

u32 *komeda_get_layer_fourcc_list(काष्ठा komeda_क्रमmat_caps_table *table,
				  u32 layer_type, u32 *n_fmts)
अणु
	स्थिर काष्ठा komeda_क्रमmat_caps *cap;
	u32 *fmts;
	पूर्णांक i, j, n = 0;

	fmts = kसुस्मृति(table->n_क्रमmats, माप(u32), GFP_KERNEL);
	अगर (!fmts)
		वापस शून्य;

	क्रम (i = 0; i < table->n_क्रमmats; i++) अणु
		cap = &table->क्रमmat_caps[i];
		अगर (!(layer_type & cap->supported_layer_types) ||
		    (cap->fourcc == 0))
			जारी;

		/* one fourcc may has two caps items in table (afbc/none-afbc),
		 * so check the existing list to aव्योम adding a duplicated one.
		 */
		क्रम (j = n - 1; j >= 0; j--)
			अगर (fmts[j] == cap->fourcc)
				अवरोध;

		अगर (j < 0)
			fmts[n++] = cap->fourcc;
	पूर्ण

	अगर (n_fmts)
		*n_fmts = n;

	वापस fmts;
पूर्ण

व्योम komeda_put_fourcc_list(u32 *fourcc_list)
अणु
	kमुक्त(fourcc_list);
पूर्ण
