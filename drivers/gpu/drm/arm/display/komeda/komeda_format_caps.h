<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#अगर_अघोषित _KOMEDA_FORMAT_CAPS_H_
#घोषणा _KOMEDA_FORMAT_CAPS_H_

#समावेश <linux/types.h>
#समावेश <uapi/drm/drm_fourcc.h>
#समावेश <drm/drm_fourcc.h>

#घोषणा AFBC(x)		DRM_FORMAT_MOD_ARM_AFBC(x)

/* afbc layerout */
#घोषणा AFBC_16x16(x)	AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 | (x))
#घोषणा AFBC_32x8(x)	AFBC(AFBC_FORMAT_MOD_BLOCK_SIZE_32x8 | (x))

/* afbc features */
#घोषणा _YTR		AFBC_FORMAT_MOD_YTR
#घोषणा _SPLIT		AFBC_FORMAT_MOD_SPLIT
#घोषणा _SPARSE		AFBC_FORMAT_MOD_SPARSE
#घोषणा _CBR		AFBC_FORMAT_MOD_CBR
#घोषणा _TILED		AFBC_FORMAT_MOD_TILED
#घोषणा _SC		AFBC_FORMAT_MOD_SC

/* layer_type */
#घोषणा KOMEDA_FMT_RICH_LAYER		BIT(0)
#घोषणा KOMEDA_FMT_SIMPLE_LAYER		BIT(1)
#घोषणा KOMEDA_FMT_WB_LAYER		BIT(2)

#घोषणा AFBC_TH_LAYOUT_ALIGNMENT	8
#घोषणा AFBC_HEADER_SIZE		16
#घोषणा AFBC_SUPERBLK_ALIGNMENT		128
#घोषणा AFBC_SUPERBLK_PIXELS		256
#घोषणा AFBC_BODY_START_ALIGNMENT	1024
#घोषणा AFBC_TH_BODY_START_ALIGNMENT	4096

/**
 * काष्ठा komeda_क्रमmat_caps
 *
 * komeda_क्रमmat_caps is क्रम describing ARM display specअगरic features and
 * limitations क्रम a specअगरic क्रमmat, and क्रमmat_caps will be linked पूर्णांकo
 * &komeda_framebuffer like a extension of &drm_क्रमmat_info.
 *
 * NOTE: one fourcc may has two dअगरferent क्रमmat_caps items क्रम fourcc and
 * fourcc+modअगरier
 *
 * @hw_id: hw क्रमmat id, hw specअगरic value.
 * @fourcc: drm fourcc क्रमmat.
 * @supported_layer_types: indicate which layer supports this क्रमmat
 * @supported_rots: allowed rotations क्रम this क्रमmat
 * @supported_afbc_layouts: supported afbc layerout
 * @supported_afbc_features: supported afbc features
 */
काष्ठा komeda_क्रमmat_caps अणु
	u32 hw_id;
	u32 fourcc;
	u32 supported_layer_types;
	u32 supported_rots;
	u32 supported_afbc_layouts;
	u64 supported_afbc_features;
पूर्ण;

/**
 * काष्ठा komeda_क्रमmat_caps_table - क्रमmat_caps mananger
 *
 * @n_क्रमmats: the size of क्रमmat_caps list.
 * @क्रमmat_caps: क्रमmat_caps list.
 * @क्रमmat_mod_supported: Optional. Some HW may have special requirements or
 * limitations which can not be described by क्रमmat_caps, this func supply HW
 * the ability to करो the further HW specअगरic check.
 */
काष्ठा komeda_क्रमmat_caps_table अणु
	u32 n_क्रमmats;
	स्थिर काष्ठा komeda_क्रमmat_caps *क्रमmat_caps;
	bool (*क्रमmat_mod_supported)(स्थिर काष्ठा komeda_क्रमmat_caps *caps,
				     u32 layer_type, u64 modअगरier, u32 rot);
पूर्ण;

बाह्य u64 komeda_supported_modअगरiers[];

स्थिर काष्ठा komeda_क्रमmat_caps *
komeda_get_क्रमmat_caps(काष्ठा komeda_क्रमmat_caps_table *table,
		       u32 fourcc, u64 modअगरier);

u32 komeda_get_afbc_क्रमmat_bpp(स्थिर काष्ठा drm_क्रमmat_info *info,
			       u64 modअगरier);

u32 *komeda_get_layer_fourcc_list(काष्ठा komeda_क्रमmat_caps_table *table,
				  u32 layer_type, u32 *n_fmts);

व्योम komeda_put_fourcc_list(u32 *fourcc_list);

bool komeda_क्रमmat_mod_supported(काष्ठा komeda_क्रमmat_caps_table *table,
				 u32 layer_type, u32 fourcc, u64 modअगरier,
				 u32 rot);

#पूर्ण_अगर
