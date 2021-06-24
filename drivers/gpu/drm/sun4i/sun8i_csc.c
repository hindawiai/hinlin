<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Jernej Skrabec <jernej.skrabec@siol.net>
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sun8i_csc.h"
#समावेश "sun8i_mixer.h"

अटल स्थिर u32 ccsc_base[2][2] = अणु
	अणुCCSC00_OFFSET, CCSC01_OFFSETपूर्ण,
	अणुCCSC10_OFFSET, CCSC11_OFFSETपूर्ण,
पूर्ण;

/*
 * Factors are in two's complement क्रमmat, 10 bits क्रम fractinal part.
 * First tree values in each line are multiplication factor and last
 * value is स्थिरant, which is added at the end.
 */

अटल स्थिर u32 yuv2rgb[2][2][12] = अणु
	[DRM_COLOR_YCBCR_LIMITED_RANGE] = अणु
		[DRM_COLOR_YCBCR_BT601] = अणु
			0x000004A8, 0x00000000, 0x00000662, 0xFFFC8451,
			0x000004A8, 0xFFFFFE6F, 0xFFFFFCC0, 0x00021E4D,
			0x000004A8, 0x00000811, 0x00000000, 0xFFFBACA9,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT709] = अणु
			0x000004A8, 0x00000000, 0x0000072B, 0xFFFC1F99,
			0x000004A8, 0xFFFFFF26, 0xFFFFFDDF, 0x00013383,
			0x000004A8, 0x00000873, 0x00000000, 0xFFFB7BEF,
		पूर्ण
	पूर्ण,
	[DRM_COLOR_YCBCR_FULL_RANGE] = अणु
		[DRM_COLOR_YCBCR_BT601] = अणु
			0x00000400, 0x00000000, 0x0000059B, 0xFFFD322E,
			0x00000400, 0xFFFFFEA0, 0xFFFFFD25, 0x00021DD5,
			0x00000400, 0x00000716, 0x00000000, 0xFFFC74BD,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT709] = अणु
			0x00000400, 0x00000000, 0x0000064C, 0xFFFCD9B4,
			0x00000400, 0xFFFFFF41, 0xFFFFFE21, 0x00014F96,
			0x00000400, 0x0000076C, 0x00000000, 0xFFFC49EF,
		पूर्ण
	पूर्ण,
पूर्ण;

/*
 * DE3 has a bit dअगरferent CSC units. Factors are in two's complement क्रमmat.
 * First three factors in a row are multiplication factors which have 17 bits
 * क्रम fractional part. Fourth value in a row is comprised of two factors.
 * Upper 16 bits represents dअगरference, which is subtracted from the input
 * value beक्रमe multiplication and lower 16 bits represents स्थिरant, which
 * is addes at the end.
 *
 * x' = c00 * (x + d0) + c01 * (y + d1) + c02 * (z + d2) + स्थिर0
 * y' = c10 * (x + d0) + c11 * (y + d1) + c12 * (z + d2) + स्थिर1
 * z' = c20 * (x + d0) + c21 * (y + d1) + c22 * (z + d2) + स्थिर2
 *
 * Please note that above क्रमmula is true only क्रम Blender CSC. Other DE3 CSC
 * units takes only positive value क्रम dअगरference. From what can be deducted
 * from BSP driver code, those units probably स्वतःmatically assume that
 * dअगरference has to be subtracted.
 *
 * Layout of factors in table:
 * c00 c01 c02 [d0 स्थिर0]
 * c10 c11 c12 [d1 स्थिर1]
 * c20 c21 c22 [d2 स्थिर2]
 */

अटल स्थिर u32 yuv2rgb_de3[2][3][12] = अणु
	[DRM_COLOR_YCBCR_LIMITED_RANGE] = अणु
		[DRM_COLOR_YCBCR_BT601] = अणु
			0x0002542A, 0x00000000, 0x0003312A, 0xFFC00000,
			0x0002542A, 0xFFFF376B, 0xFFFE5FC3, 0xFE000000,
			0x0002542A, 0x000408D2, 0x00000000, 0xFE000000,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT709] = अणु
			0x0002542A, 0x00000000, 0x000395E2, 0xFFC00000,
			0x0002542A, 0xFFFF92D2, 0xFFFEEF27, 0xFE000000,
			0x0002542A, 0x0004398C, 0x00000000, 0xFE000000,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT2020] = अणु
			0x0002542A, 0x00000000, 0x00035B7B, 0xFFC00000,
			0x0002542A, 0xFFFFA017, 0xFFFEB2FC, 0xFE000000,
			0x0002542A, 0x00044896, 0x00000000, 0xFE000000,
		पूर्ण
	पूर्ण,
	[DRM_COLOR_YCBCR_FULL_RANGE] = अणु
		[DRM_COLOR_YCBCR_BT601] = अणु
			0x00020000, 0x00000000, 0x0002CDD2, 0x00000000,
			0x00020000, 0xFFFF4FCE, 0xFFFE925D, 0xFE000000,
			0x00020000, 0x00038B43, 0x00000000, 0xFE000000,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT709] = अणु
			0x00020000, 0x00000000, 0x0003264C, 0x00000000,
			0x00020000, 0xFFFFA018, 0xFFFF1053, 0xFE000000,
			0x00020000, 0x0003B611, 0x00000000, 0xFE000000,
		पूर्ण,
		[DRM_COLOR_YCBCR_BT2020] = अणु
			0x00020000, 0x00000000, 0x0002F2FE, 0x00000000,
			0x00020000, 0xFFFFABC0, 0xFFFEDB78, 0xFE000000,
			0x00020000, 0x0003C346, 0x00000000, 0xFE000000,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल व्योम sun8i_csc_set_coefficients(काष्ठा regmap *map, u32 base,
				       क्रमागत sun8i_csc_mode mode,
				       क्रमागत drm_color_encoding encoding,
				       क्रमागत drm_color_range range)
अणु
	स्थिर u32 *table;
	u32 base_reg;
	पूर्णांक i;

	table = yuv2rgb[range][encoding];

	चयन (mode) अणु
	हाल SUN8I_CSC_MODE_YUV2RGB:
		base_reg = SUN8I_CSC_COEFF(base, 0);
		regmap_bulk_ग_लिखो(map, base_reg, table, 12);
		अवरोध;
	हाल SUN8I_CSC_MODE_YVU2RGB:
		क्रम (i = 0; i < 12; i++) अणु
			अगर ((i & 3) == 1)
				base_reg = SUN8I_CSC_COEFF(base, i + 1);
			अन्यथा अगर ((i & 3) == 2)
				base_reg = SUN8I_CSC_COEFF(base, i - 1);
			अन्यथा
				base_reg = SUN8I_CSC_COEFF(base, i);
			regmap_ग_लिखो(map, base_reg, table[i]);
		पूर्ण
		अवरोध;
	शेष:
		DRM_WARN("Wrong CSC mode specified.\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sun8i_de3_ccsc_set_coefficients(काष्ठा regmap *map, पूर्णांक layer,
					    क्रमागत sun8i_csc_mode mode,
					    क्रमागत drm_color_encoding encoding,
					    क्रमागत drm_color_range range)
अणु
	स्थिर u32 *table;
	u32 addr;
	पूर्णांक i;

	table = yuv2rgb_de3[range][encoding];

	चयन (mode) अणु
	हाल SUN8I_CSC_MODE_YUV2RGB:
		addr = SUN50I_MIXER_BLEND_CSC_COEFF(DE3_BLD_BASE, layer, 0);
		regmap_bulk_ग_लिखो(map, addr, table, 12);
		अवरोध;
	हाल SUN8I_CSC_MODE_YVU2RGB:
		क्रम (i = 0; i < 12; i++) अणु
			अगर ((i & 3) == 1)
				addr = SUN50I_MIXER_BLEND_CSC_COEFF(DE3_BLD_BASE,
								    layer,
								    i + 1);
			अन्यथा अगर ((i & 3) == 2)
				addr = SUN50I_MIXER_BLEND_CSC_COEFF(DE3_BLD_BASE,
								    layer,
								    i - 1);
			अन्यथा
				addr = SUN50I_MIXER_BLEND_CSC_COEFF(DE3_BLD_BASE,
								    layer, i);
			regmap_ग_लिखो(map, addr, table[i]);
		पूर्ण
		अवरोध;
	शेष:
		DRM_WARN("Wrong CSC mode specified.\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sun8i_csc_enable(काष्ठा regmap *map, u32 base, bool enable)
अणु
	u32 val;

	अगर (enable)
		val = SUN8I_CSC_CTRL_EN;
	अन्यथा
		val = 0;

	regmap_update_bits(map, SUN8I_CSC_CTRL(base), SUN8I_CSC_CTRL_EN, val);
पूर्ण

अटल व्योम sun8i_de3_ccsc_enable(काष्ठा regmap *map, पूर्णांक layer, bool enable)
अणु
	u32 val, mask;

	mask = SUN50I_MIXER_BLEND_CSC_CTL_EN(layer);

	अगर (enable)
		val = mask;
	अन्यथा
		val = 0;

	regmap_update_bits(map, SUN50I_MIXER_BLEND_CSC_CTL(DE3_BLD_BASE),
			   mask, val);
पूर्ण

व्योम sun8i_csc_set_ccsc_coefficients(काष्ठा sun8i_mixer *mixer, पूर्णांक layer,
				     क्रमागत sun8i_csc_mode mode,
				     क्रमागत drm_color_encoding encoding,
				     क्रमागत drm_color_range range)
अणु
	u32 base;

	अगर (mixer->cfg->is_de3) अणु
		sun8i_de3_ccsc_set_coefficients(mixer->engine.regs, layer,
						mode, encoding, range);
		वापस;
	पूर्ण

	base = ccsc_base[mixer->cfg->ccsc][layer];

	sun8i_csc_set_coefficients(mixer->engine.regs, base,
				   mode, encoding, range);
पूर्ण

व्योम sun8i_csc_enable_ccsc(काष्ठा sun8i_mixer *mixer, पूर्णांक layer, bool enable)
अणु
	u32 base;

	अगर (mixer->cfg->is_de3) अणु
		sun8i_de3_ccsc_enable(mixer->engine.regs, layer, enable);
		वापस;
	पूर्ण

	base = ccsc_base[mixer->cfg->ccsc][layer];

	sun8i_csc_enable(mixer->engine.regs, base, enable);
पूर्ण
