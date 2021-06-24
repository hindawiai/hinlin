<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <soc/tegra/pmc.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "dc.h"
#समावेश "drm.h"
#समावेश "gem.h"
#समावेश "hub.h"
#समावेश "plane.h"

अटल व्योम tegra_crtc_atomic_destroy_state(काष्ठा drm_crtc *crtc,
					    काष्ठा drm_crtc_state *state);

अटल व्योम tegra_dc_stats_reset(काष्ठा tegra_dc_stats *stats)
अणु
	stats->frames = 0;
	stats->vblank = 0;
	stats->underflow = 0;
	stats->overflow = 0;
पूर्ण

/* Reads the active copy of a रेजिस्टर. */
अटल u32 tegra_dc_पढ़ोl_active(काष्ठा tegra_dc *dc, अचिन्हित दीर्घ offset)
अणु
	u32 value;

	tegra_dc_ग_लिखोl(dc, READ_MUX, DC_CMD_STATE_ACCESS);
	value = tegra_dc_पढ़ोl(dc, offset);
	tegra_dc_ग_लिखोl(dc, 0, DC_CMD_STATE_ACCESS);

	वापस value;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tegra_plane_offset(काष्ठा tegra_plane *plane,
					      अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= 0x500 && offset <= 0x638) अणु
		offset = 0x000 + (offset - 0x500);
		वापस plane->offset + offset;
	पूर्ण

	अगर (offset >= 0x700 && offset <= 0x719) अणु
		offset = 0x180 + (offset - 0x700);
		वापस plane->offset + offset;
	पूर्ण

	अगर (offset >= 0x800 && offset <= 0x839) अणु
		offset = 0x1c0 + (offset - 0x800);
		वापस plane->offset + offset;
	पूर्ण

	dev_WARN(plane->dc->dev, "invalid offset: %x\n", offset);

	वापस plane->offset + offset;
पूर्ण

अटल अंतरभूत u32 tegra_plane_पढ़ोl(काष्ठा tegra_plane *plane,
				    अचिन्हित पूर्णांक offset)
अणु
	वापस tegra_dc_पढ़ोl(plane->dc, tegra_plane_offset(plane, offset));
पूर्ण

अटल अंतरभूत व्योम tegra_plane_ग_लिखोl(काष्ठा tegra_plane *plane, u32 value,
				      अचिन्हित पूर्णांक offset)
अणु
	tegra_dc_ग_लिखोl(plane->dc, value, tegra_plane_offset(plane, offset));
पूर्ण

bool tegra_dc_has_output(काष्ठा tegra_dc *dc, काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dc->dev->of_node;
	काष्ठा of_phandle_iterator it;
	पूर्णांक err;

	of_क्रम_each_phandle(&it, err, np, "nvidia,outputs", शून्य, 0)
		अगर (it.node == dev->of_node)
			वापस true;

	वापस false;
पूर्ण

/*
 * Double-buffered रेजिस्टरs have two copies: ASSEMBLY and ACTIVE. When the
 * *_ACT_REQ bits are set the ASSEMBLY copy is latched पूर्णांकo the ACTIVE copy.
 * Latching happens mmediately अगर the display controller is in STOP mode or
 * on the next frame boundary otherwise.
 *
 * Triple-buffered रेजिस्टरs have three copies: ASSEMBLY, ARM and ACTIVE. The
 * ASSEMBLY copy is latched पूर्णांकo the ARM copy immediately after *_UPDATE bits
 * are written. When the *_ACT_REQ bits are written, the ARM copy is latched
 * पूर्णांकo the ACTIVE copy, either immediately अगर the display controller is in
 * STOP mode, or at the next frame boundary otherwise.
 */
व्योम tegra_dc_commit(काष्ठा tegra_dc *dc)
अणु
	tegra_dc_ग_लिखोl(dc, GENERAL_ACT_REQ << 8, DC_CMD_STATE_CONTROL);
	tegra_dc_ग_लिखोl(dc, GENERAL_ACT_REQ, DC_CMD_STATE_CONTROL);
पूर्ण

अटल अंतरभूत u32 compute_dda_inc(अचिन्हित पूर्णांक in, अचिन्हित पूर्णांक out, bool v,
				  अचिन्हित पूर्णांक bpp)
अणु
	fixed20_12 outf = dfixed_init(out);
	fixed20_12 inf = dfixed_init(in);
	u32 dda_inc;
	पूर्णांक max;

	अगर (v)
		max = 15;
	अन्यथा अणु
		चयन (bpp) अणु
		हाल 2:
			max = 8;
			अवरोध;

		शेष:
			WARN_ON_ONCE(1);
			fallthrough;
		हाल 4:
			max = 4;
			अवरोध;
		पूर्ण
	पूर्ण

	outf.full = max_t(u32, outf.full - dfixed_स्थिर(1), dfixed_स्थिर(1));
	inf.full -= dfixed_स्थिर(1);

	dda_inc = dfixed_भाग(inf, outf);
	dda_inc = min_t(u32, dda_inc, dfixed_स्थिर(max));

	वापस dda_inc;
पूर्ण

अटल अंतरभूत u32 compute_initial_dda(अचिन्हित पूर्णांक in)
अणु
	fixed20_12 inf = dfixed_init(in);
	वापस dfixed_frac(inf);
पूर्ण

अटल व्योम tegra_plane_setup_blending_legacy(काष्ठा tegra_plane *plane)
अणु
	u32 background[3] = अणु
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
	पूर्ण;
	u32 क्रमeground = BLEND_WEIGHT1(255) | BLEND_WEIGHT0(255) |
			 BLEND_COLOR_KEY_NONE;
	u32 blendnokey = BLEND_WEIGHT1(255) | BLEND_WEIGHT0(255);
	काष्ठा tegra_plane_state *state;
	u32 blending[2];
	अचिन्हित पूर्णांक i;

	/* disable blending क्रम non-overlapping हाल */
	tegra_plane_ग_लिखोl(plane, blendnokey, DC_WIN_BLEND_NOKEY);
	tegra_plane_ग_लिखोl(plane, क्रमeground, DC_WIN_BLEND_1WIN);

	state = to_tegra_plane_state(plane->base.state);

	अगर (state->opaque) अणु
		/*
		 * Since custom fix-weight blending isn't utilized and weight
		 * of top winकरोw is set to max, we can enक्रमce dependent
		 * blending which in this हाल results in transparent bottom
		 * winकरोw अगर top winकरोw is opaque and अगर top winकरोw enables
		 * alpha blending, then bottom winकरोw is getting alpha value
		 * of 1 minus the sum of alpha components of the overlapping
		 * plane.
		 */
		background[0] |= BLEND_CONTROL_DEPENDENT;
		background[1] |= BLEND_CONTROL_DEPENDENT;

		/*
		 * The region where three winकरोws overlap is the पूर्णांकersection
		 * of the two regions where two winकरोws overlap. It contributes
		 * to the area अगर all of the winकरोws on top of it have an alpha
		 * component.
		 */
		चयन (state->base.normalized_zpos) अणु
		हाल 0:
			अगर (state->blending[0].alpha &&
			    state->blending[1].alpha)
				background[2] |= BLEND_CONTROL_DEPENDENT;
			अवरोध;

		हाल 1:
			background[2] |= BLEND_CONTROL_DEPENDENT;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Enable alpha blending अगर pixel क्रमmat has an alpha
		 * component.
		 */
		क्रमeground |= BLEND_CONTROL_ALPHA;

		/*
		 * If any of the winकरोws on top of this winकरोw is opaque, it
		 * will completely conceal this winकरोw within that area. If
		 * top winकरोw has an alpha component, it is blended over the
		 * bottom winकरोw.
		 */
		क्रम (i = 0; i < 2; i++) अणु
			अगर (state->blending[i].alpha &&
			    state->blending[i].top)
				background[i] |= BLEND_CONTROL_DEPENDENT;
		पूर्ण

		चयन (state->base.normalized_zpos) अणु
		हाल 0:
			अगर (state->blending[0].alpha &&
			    state->blending[1].alpha)
				background[2] |= BLEND_CONTROL_DEPENDENT;
			अवरोध;

		हाल 1:
			/*
			 * When both middle and topmost winकरोws have an alpha,
			 * these winकरोws a mixed together and then the result
			 * is blended over the bottom winकरोw.
			 */
			अगर (state->blending[0].alpha &&
			    state->blending[0].top)
				background[2] |= BLEND_CONTROL_ALPHA;

			अगर (state->blending[1].alpha &&
			    state->blending[1].top)
				background[2] |= BLEND_CONTROL_ALPHA;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (state->base.normalized_zpos) अणु
	हाल 0:
		tegra_plane_ग_लिखोl(plane, background[0], DC_WIN_BLEND_2WIN_X);
		tegra_plane_ग_लिखोl(plane, background[1], DC_WIN_BLEND_2WIN_Y);
		tegra_plane_ग_लिखोl(plane, background[2], DC_WIN_BLEND_3WIN_XY);
		अवरोध;

	हाल 1:
		/*
		 * If winकरोw B / C is topmost, then X / Y रेजिस्टरs are
		 * matching the order of blending[...] state indices,
		 * otherwise a swap is required.
		 */
		अगर (!state->blending[0].top && state->blending[1].top) अणु
			blending[0] = क्रमeground;
			blending[1] = background[1];
		पूर्ण अन्यथा अणु
			blending[0] = background[0];
			blending[1] = क्रमeground;
		पूर्ण

		tegra_plane_ग_लिखोl(plane, blending[0], DC_WIN_BLEND_2WIN_X);
		tegra_plane_ग_लिखोl(plane, blending[1], DC_WIN_BLEND_2WIN_Y);
		tegra_plane_ग_लिखोl(plane, background[2], DC_WIN_BLEND_3WIN_XY);
		अवरोध;

	हाल 2:
		tegra_plane_ग_लिखोl(plane, क्रमeground, DC_WIN_BLEND_2WIN_X);
		tegra_plane_ग_लिखोl(plane, क्रमeground, DC_WIN_BLEND_2WIN_Y);
		tegra_plane_ग_लिखोl(plane, क्रमeground, DC_WIN_BLEND_3WIN_XY);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tegra_plane_setup_blending(काष्ठा tegra_plane *plane,
				       स्थिर काष्ठा tegra_dc_winकरोw *winकरोw)
अणु
	u32 value;

	value = BLEND_FACTOR_DST_ALPHA_ZERO | BLEND_FACTOR_SRC_ALPHA_K2 |
		BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_SRC |
		BLEND_FACTOR_SRC_COLOR_K1_TIMES_SRC;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_BLEND_MATCH_SELECT);

	value = BLEND_FACTOR_DST_ALPHA_ZERO | BLEND_FACTOR_SRC_ALPHA_K2 |
		BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_SRC |
		BLEND_FACTOR_SRC_COLOR_K1_TIMES_SRC;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_BLEND_NOMATCH_SELECT);

	value = K2(255) | K1(255) | WINDOW_LAYER_DEPTH(255 - winकरोw->zpos);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_BLEND_LAYER_CONTROL);
पूर्ण

अटल bool
tegra_plane_use_horizontal_filtering(काष्ठा tegra_plane *plane,
				     स्थिर काष्ठा tegra_dc_winकरोw *winकरोw)
अणु
	काष्ठा tegra_dc *dc = plane->dc;

	अगर (winकरोw->src.w == winकरोw->dst.w)
		वापस false;

	अगर (plane->index == 0 && dc->soc->has_win_a_without_filters)
		वापस false;

	वापस true;
पूर्ण

अटल bool
tegra_plane_use_vertical_filtering(काष्ठा tegra_plane *plane,
				   स्थिर काष्ठा tegra_dc_winकरोw *winकरोw)
अणु
	काष्ठा tegra_dc *dc = plane->dc;

	अगर (winकरोw->src.h == winकरोw->dst.h)
		वापस false;

	अगर (plane->index == 0 && dc->soc->has_win_a_without_filters)
		वापस false;

	अगर (plane->index == 2 && dc->soc->has_win_c_without_vert_filter)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम tegra_dc_setup_winकरोw(काष्ठा tegra_plane *plane,
				  स्थिर काष्ठा tegra_dc_winकरोw *winकरोw)
अणु
	अचिन्हित h_offset, v_offset, h_size, v_size, h_dda, v_dda, bpp;
	काष्ठा tegra_dc *dc = plane->dc;
	bool yuv, planar;
	u32 value;

	/*
	 * For YUV planar modes, the number of bytes per pixel takes पूर्णांकo
	 * account only the luma component and thereक्रमe is 1.
	 */
	yuv = tegra_plane_क्रमmat_is_yuv(winकरोw->क्रमmat, &planar);
	अगर (!yuv)
		bpp = winकरोw->bits_per_pixel / 8;
	अन्यथा
		bpp = planar ? 1 : 2;

	tegra_plane_ग_लिखोl(plane, winकरोw->क्रमmat, DC_WIN_COLOR_DEPTH);
	tegra_plane_ग_लिखोl(plane, winकरोw->swap, DC_WIN_BYTE_SWAP);

	value = V_POSITION(winकरोw->dst.y) | H_POSITION(winकरोw->dst.x);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_POSITION);

	value = V_SIZE(winकरोw->dst.h) | H_SIZE(winकरोw->dst.w);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_SIZE);

	h_offset = winकरोw->src.x * bpp;
	v_offset = winकरोw->src.y;
	h_size = winकरोw->src.w * bpp;
	v_size = winकरोw->src.h;

	अगर (winकरोw->reflect_x)
		h_offset += (winकरोw->src.w - 1) * bpp;

	अगर (winकरोw->reflect_y)
		v_offset += winकरोw->src.h - 1;

	value = V_PRESCALED_SIZE(v_size) | H_PRESCALED_SIZE(h_size);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_PRESCALED_SIZE);

	/*
	 * For DDA computations the number of bytes per pixel क्रम YUV planar
	 * modes needs to take पूर्णांकo account all Y, U and V components.
	 */
	अगर (yuv && planar)
		bpp = 2;

	h_dda = compute_dda_inc(winकरोw->src.w, winकरोw->dst.w, false, bpp);
	v_dda = compute_dda_inc(winकरोw->src.h, winकरोw->dst.h, true, bpp);

	value = V_DDA_INC(v_dda) | H_DDA_INC(h_dda);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_DDA_INC);

	h_dda = compute_initial_dda(winकरोw->src.x);
	v_dda = compute_initial_dda(winकरोw->src.y);

	tegra_plane_ग_लिखोl(plane, h_dda, DC_WIN_H_INITIAL_DDA);
	tegra_plane_ग_लिखोl(plane, v_dda, DC_WIN_V_INITIAL_DDA);

	tegra_plane_ग_लिखोl(plane, 0, DC_WIN_UV_BUF_STRIDE);
	tegra_plane_ग_लिखोl(plane, 0, DC_WIN_BUF_STRIDE);

	tegra_plane_ग_लिखोl(plane, winकरोw->base[0], DC_WINBUF_START_ADDR);

	अगर (yuv && planar) अणु
		tegra_plane_ग_लिखोl(plane, winकरोw->base[1], DC_WINBUF_START_ADDR_U);
		tegra_plane_ग_लिखोl(plane, winकरोw->base[2], DC_WINBUF_START_ADDR_V);
		value = winकरोw->stride[1] << 16 | winकरोw->stride[0];
		tegra_plane_ग_लिखोl(plane, value, DC_WIN_LINE_STRIDE);
	पूर्ण अन्यथा अणु
		tegra_plane_ग_लिखोl(plane, winकरोw->stride[0], DC_WIN_LINE_STRIDE);
	पूर्ण

	tegra_plane_ग_लिखोl(plane, h_offset, DC_WINBUF_ADDR_H_OFFSET);
	tegra_plane_ग_लिखोl(plane, v_offset, DC_WINBUF_ADDR_V_OFFSET);

	अगर (dc->soc->supports_block_linear) अणु
		अचिन्हित दीर्घ height = winकरोw->tiling.value;

		चयन (winकरोw->tiling.mode) अणु
		हाल TEGRA_BO_TILING_MODE_PITCH:
			value = DC_WINBUF_SURFACE_KIND_PITCH;
			अवरोध;

		हाल TEGRA_BO_TILING_MODE_TILED:
			value = DC_WINBUF_SURFACE_KIND_TILED;
			अवरोध;

		हाल TEGRA_BO_TILING_MODE_BLOCK:
			value = DC_WINBUF_SURFACE_KIND_BLOCK_HEIGHT(height) |
				DC_WINBUF_SURFACE_KIND_BLOCK;
			अवरोध;
		पूर्ण

		tegra_plane_ग_लिखोl(plane, value, DC_WINBUF_SURFACE_KIND);
	पूर्ण अन्यथा अणु
		चयन (winकरोw->tiling.mode) अणु
		हाल TEGRA_BO_TILING_MODE_PITCH:
			value = DC_WIN_BUFFER_ADDR_MODE_LINEAR_UV |
				DC_WIN_BUFFER_ADDR_MODE_LINEAR;
			अवरोध;

		हाल TEGRA_BO_TILING_MODE_TILED:
			value = DC_WIN_BUFFER_ADDR_MODE_TILE_UV |
				DC_WIN_BUFFER_ADDR_MODE_TILE;
			अवरोध;

		हाल TEGRA_BO_TILING_MODE_BLOCK:
			/*
			 * No need to handle this here because ->atomic_check
			 * will alपढ़ोy have filtered it out.
			 */
			अवरोध;
		पूर्ण

		tegra_plane_ग_लिखोl(plane, value, DC_WIN_BUFFER_ADDR_MODE);
	पूर्ण

	value = WIN_ENABLE;

	अगर (yuv) अणु
		/* setup शेष colorspace conversion coefficients */
		tegra_plane_ग_लिखोl(plane, 0x00f0, DC_WIN_CSC_YOF);
		tegra_plane_ग_लिखोl(plane, 0x012a, DC_WIN_CSC_KYRGB);
		tegra_plane_ग_लिखोl(plane, 0x0000, DC_WIN_CSC_KUR);
		tegra_plane_ग_लिखोl(plane, 0x0198, DC_WIN_CSC_KVR);
		tegra_plane_ग_लिखोl(plane, 0x039b, DC_WIN_CSC_KUG);
		tegra_plane_ग_लिखोl(plane, 0x032f, DC_WIN_CSC_KVG);
		tegra_plane_ग_लिखोl(plane, 0x0204, DC_WIN_CSC_KUB);
		tegra_plane_ग_लिखोl(plane, 0x0000, DC_WIN_CSC_KVB);

		value |= CSC_ENABLE;
	पूर्ण अन्यथा अगर (winकरोw->bits_per_pixel < 24) अणु
		value |= COLOR_EXPAND;
	पूर्ण

	अगर (winकरोw->reflect_x)
		value |= H_सूचीECTION;

	अगर (winकरोw->reflect_y)
		value |= V_सूचीECTION;

	अगर (tegra_plane_use_horizontal_filtering(plane, winकरोw)) अणु
		/*
		 * Enable horizontal 6-tap filter and set filtering
		 * coefficients to the शेष values defined in TRM.
		 */
		tegra_plane_ग_लिखोl(plane, 0x00008000, DC_WIN_H_FILTER_P(0));
		tegra_plane_ग_लिखोl(plane, 0x3e087ce1, DC_WIN_H_FILTER_P(1));
		tegra_plane_ग_लिखोl(plane, 0x3b117ac1, DC_WIN_H_FILTER_P(2));
		tegra_plane_ग_लिखोl(plane, 0x591b73aa, DC_WIN_H_FILTER_P(3));
		tegra_plane_ग_लिखोl(plane, 0x57256d9a, DC_WIN_H_FILTER_P(4));
		tegra_plane_ग_लिखोl(plane, 0x552f668b, DC_WIN_H_FILTER_P(5));
		tegra_plane_ग_लिखोl(plane, 0x73385e8b, DC_WIN_H_FILTER_P(6));
		tegra_plane_ग_लिखोl(plane, 0x72435583, DC_WIN_H_FILTER_P(7));
		tegra_plane_ग_लिखोl(plane, 0x714c4c8b, DC_WIN_H_FILTER_P(8));
		tegra_plane_ग_लिखोl(plane, 0x70554393, DC_WIN_H_FILTER_P(9));
		tegra_plane_ग_लिखोl(plane, 0x715e389b, DC_WIN_H_FILTER_P(10));
		tegra_plane_ग_लिखोl(plane, 0x71662faa, DC_WIN_H_FILTER_P(11));
		tegra_plane_ग_लिखोl(plane, 0x536d25ba, DC_WIN_H_FILTER_P(12));
		tegra_plane_ग_लिखोl(plane, 0x55731bca, DC_WIN_H_FILTER_P(13));
		tegra_plane_ग_लिखोl(plane, 0x387a11d9, DC_WIN_H_FILTER_P(14));
		tegra_plane_ग_लिखोl(plane, 0x3c7c08f1, DC_WIN_H_FILTER_P(15));

		value |= H_FILTER;
	पूर्ण

	अगर (tegra_plane_use_vertical_filtering(plane, winकरोw)) अणु
		अचिन्हित पूर्णांक i, k;

		/*
		 * Enable vertical 2-tap filter and set filtering
		 * coefficients to the शेष values defined in TRM.
		 */
		क्रम (i = 0, k = 128; i < 16; i++, k -= 8)
			tegra_plane_ग_लिखोl(plane, k, DC_WIN_V_FILTER_P(i));

		value |= V_FILTER;
	पूर्ण

	tegra_plane_ग_लिखोl(plane, value, DC_WIN_WIN_OPTIONS);

	अगर (dc->soc->has_legacy_blending)
		tegra_plane_setup_blending_legacy(plane);
	अन्यथा
		tegra_plane_setup_blending(plane, winकरोw);
पूर्ण

अटल स्थिर u32 tegra20_primary_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* non-native क्रमmats */
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर u64 tegra20_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_NVIDIA_TEGRA_TILED,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल स्थिर u32 tegra114_primary_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* new on Tegra114 */
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
पूर्ण;

अटल स्थिर u32 tegra124_primary_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* new on Tegra114 */
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	/* new on Tegra124 */
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRX8888,
पूर्ण;

अटल स्थिर u64 tegra124_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(0),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(1),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(2),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(3),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(4),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(5),
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल पूर्णांक tegra_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा tegra_plane_state *plane_state = to_tegra_plane_state(new_plane_state);
	अचिन्हित पूर्णांक supported_rotation = DRM_MODE_ROTATE_0 |
					  DRM_MODE_REFLECT_X |
					  DRM_MODE_REFLECT_Y;
	अचिन्हित पूर्णांक rotation = new_plane_state->rotation;
	काष्ठा tegra_bo_tiling *tiling = &plane_state->tiling;
	काष्ठा tegra_plane *tegra = to_tegra_plane(plane);
	काष्ठा tegra_dc *dc = to_tegra_dc(new_plane_state->crtc);
	पूर्णांक err;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!new_plane_state->crtc)
		वापस 0;

	err = tegra_plane_क्रमmat(new_plane_state->fb->क्रमmat->क्रमmat,
				 &plane_state->क्रमmat,
				 &plane_state->swap);
	अगर (err < 0)
		वापस err;

	/*
	 * Tegra20 and Tegra30 are special हालs here because they support
	 * only variants of specअगरic क्रमmats with an alpha component, but not
	 * the corresponding opaque क्रमmats. However, the opaque क्रमmats can
	 * be emulated by disabling alpha blending क्रम the plane.
	 */
	अगर (dc->soc->has_legacy_blending) अणु
		err = tegra_plane_setup_legacy_state(tegra, plane_state);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = tegra_fb_get_tiling(new_plane_state->fb, tiling);
	अगर (err < 0)
		वापस err;

	अगर (tiling->mode == TEGRA_BO_TILING_MODE_BLOCK &&
	    !dc->soc->supports_block_linear) अणु
		DRM_ERROR("hardware doesn't support block linear mode\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Older userspace used custom BO flag in order to specअगरy the Y
	 * reflection, जबतक modern userspace uses the generic DRM rotation
	 * property in order to achieve the same result.  The legacy BO flag
	 * duplicates the DRM rotation property when both are set.
	 */
	अगर (tegra_fb_is_bottom_up(new_plane_state->fb))
		rotation |= DRM_MODE_REFLECT_Y;

	rotation = drm_rotation_simplअगरy(rotation, supported_rotation);

	अगर (rotation & DRM_MODE_REFLECT_X)
		plane_state->reflect_x = true;
	अन्यथा
		plane_state->reflect_x = false;

	अगर (rotation & DRM_MODE_REFLECT_Y)
		plane_state->reflect_y = true;
	अन्यथा
		plane_state->reflect_y = false;

	/*
	 * Tegra करोesn't support dअगरferent strides क्रम U and V planes so we
	 * error out अगर the user tries to display a framebuffer with such a
	 * configuration.
	 */
	अगर (new_plane_state->fb->क्रमmat->num_planes > 2) अणु
		अगर (new_plane_state->fb->pitches[2] != new_plane_state->fb->pitches[1]) अणु
			DRM_ERROR("unsupported UV-plane configuration\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = tegra_plane_state_add(tegra, new_plane_state);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम tegra_plane_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा tegra_plane *p = to_tegra_plane(plane);
	u32 value;

	/* rien ne va plus */
	अगर (!old_state || !old_state->crtc)
		वापस;

	value = tegra_plane_पढ़ोl(p, DC_WIN_WIN_OPTIONS);
	value &= ~WIN_ENABLE;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WIN_OPTIONS);
पूर्ण

अटल व्योम tegra_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा tegra_plane_state *tegra_plane_state = to_tegra_plane_state(new_state);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा tegra_plane *p = to_tegra_plane(plane);
	काष्ठा tegra_dc_winकरोw winकरोw;
	अचिन्हित पूर्णांक i;

	/* rien ne va plus */
	अगर (!new_state->crtc || !new_state->fb)
		वापस;

	अगर (!new_state->visible)
		वापस tegra_plane_atomic_disable(plane, state);

	स_रखो(&winकरोw, 0, माप(winकरोw));
	winकरोw.src.x = new_state->src.x1 >> 16;
	winकरोw.src.y = new_state->src.y1 >> 16;
	winकरोw.src.w = drm_rect_width(&new_state->src) >> 16;
	winकरोw.src.h = drm_rect_height(&new_state->src) >> 16;
	winकरोw.dst.x = new_state->dst.x1;
	winकरोw.dst.y = new_state->dst.y1;
	winकरोw.dst.w = drm_rect_width(&new_state->dst);
	winकरोw.dst.h = drm_rect_height(&new_state->dst);
	winकरोw.bits_per_pixel = fb->क्रमmat->cpp[0] * 8;
	winकरोw.reflect_x = tegra_plane_state->reflect_x;
	winकरोw.reflect_y = tegra_plane_state->reflect_y;

	/* copy from state */
	winकरोw.zpos = new_state->normalized_zpos;
	winकरोw.tiling = tegra_plane_state->tiling;
	winकरोw.क्रमmat = tegra_plane_state->क्रमmat;
	winकरोw.swap = tegra_plane_state->swap;

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		winकरोw.base[i] = tegra_plane_state->iova[i] + fb->offsets[i];

		/*
		 * Tegra uses a shared stride क्रम UV planes. Framebuffers are
		 * alपढ़ोy checked क्रम this in the tegra_plane_atomic_check()
		 * function, so it's safe to ignore the V-plane pitch here.
		 */
		अगर (i < 2)
			winकरोw.stride[i] = fb->pitches[i];
	पूर्ण

	tegra_dc_setup_winकरोw(p, &winकरोw);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs tegra_plane_helper_funcs = अणु
	.prepare_fb = tegra_plane_prepare_fb,
	.cleanup_fb = tegra_plane_cleanup_fb,
	.atomic_check = tegra_plane_atomic_check,
	.atomic_disable = tegra_plane_atomic_disable,
	.atomic_update = tegra_plane_atomic_update,
पूर्ण;

अटल अचिन्हित दीर्घ tegra_plane_get_possible_crtcs(काष्ठा drm_device *drm)
अणु
	/*
	 * Ideally this would use drm_crtc_mask(), but that would require the
	 * CRTC to alपढ़ोy be in the mode_config's list of CRTCs. However, it
	 * will only be added to that list in the drm_crtc_init_with_planes()
	 * (in tegra_dc_init()), which in turn requires registration of these
	 * planes. So we have ourselves a nice little chicken and egg problem
	 * here.
	 *
	 * We work around this by manually creating the mask from the number
	 * of CRTCs that have been रेजिस्टरed, and should thereक्रमe always be
	 * the same as drm_crtc_index() after registration.
	 */
	वापस 1 << drm->mode_config.num_crtc;
पूर्ण

अटल काष्ठा drm_plane *tegra_primary_plane_create(काष्ठा drm_device *drm,
						    काष्ठा tegra_dc *dc)
अणु
	अचिन्हित दीर्घ possible_crtcs = tegra_plane_get_possible_crtcs(drm);
	क्रमागत drm_plane_type type = DRM_PLANE_TYPE_PRIMARY;
	काष्ठा tegra_plane *plane;
	अचिन्हित पूर्णांक num_क्रमmats;
	स्थिर u64 *modअगरiers;
	स्थिर u32 *क्रमmats;
	पूर्णांक err;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	/* Always use winकरोw A as primary winकरोw */
	plane->offset = 0xa00;
	plane->index = 0;
	plane->dc = dc;

	num_क्रमmats = dc->soc->num_primary_क्रमmats;
	क्रमmats = dc->soc->primary_क्रमmats;
	modअगरiers = dc->soc->modअगरiers;

	err = drm_universal_plane_init(drm, &plane->base, possible_crtcs,
				       &tegra_plane_funcs, क्रमmats,
				       num_क्रमmats, modअगरiers, type, शून्य);
	अगर (err < 0) अणु
		kमुक्त(plane);
		वापस ERR_PTR(err);
	पूर्ण

	drm_plane_helper_add(&plane->base, &tegra_plane_helper_funcs);
	drm_plane_create_zpos_property(&plane->base, plane->index, 0, 255);

	err = drm_plane_create_rotation_property(&plane->base,
						 DRM_MODE_ROTATE_0,
						 DRM_MODE_ROTATE_0 |
						 DRM_MODE_ROTATE_180 |
						 DRM_MODE_REFLECT_X |
						 DRM_MODE_REFLECT_Y);
	अगर (err < 0)
		dev_err(dc->dev, "failed to create rotation property: %d\n",
			err);

	वापस &plane->base;
पूर्ण

अटल स्थिर u32 tegra_legacy_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_RGBA8888,
पूर्ण;

अटल स्थिर u32 tegra_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल पूर्णांक tegra_cursor_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा tegra_plane *tegra = to_tegra_plane(plane);
	पूर्णांक err;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!new_plane_state->crtc)
		वापस 0;

	/* scaling not supported क्रम cursor */
	अगर ((new_plane_state->src_w >> 16 != new_plane_state->crtc_w) ||
	    (new_plane_state->src_h >> 16 != new_plane_state->crtc_h))
		वापस -EINVAL;

	/* only square cursors supported */
	अगर (new_plane_state->src_w != new_plane_state->src_h)
		वापस -EINVAL;

	अगर (new_plane_state->crtc_w != 32 && new_plane_state->crtc_w != 64 &&
	    new_plane_state->crtc_w != 128 && new_plane_state->crtc_w != 256)
		वापस -EINVAL;

	err = tegra_plane_state_add(tegra, new_plane_state);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम tegra_cursor_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा tegra_plane_state *tegra_plane_state = to_tegra_plane_state(new_state);
	काष्ठा tegra_dc *dc = to_tegra_dc(new_state->crtc);
	काष्ठा tegra_drm *tegra = plane->dev->dev_निजी;
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	u64 dma_mask = *dc->dev->dma_mask;
#पूर्ण_अगर
	अचिन्हित पूर्णांक x, y;
	u32 value = 0;

	/* rien ne va plus */
	अगर (!new_state->crtc || !new_state->fb)
		वापस;

	/*
	 * Legacy display supports hardware clipping of the cursor, but
	 * nvdisplay relies on software to clip the cursor to the screen.
	 */
	अगर (!dc->soc->has_nvdisplay)
		value |= CURSOR_CLIP_DISPLAY;

	चयन (new_state->crtc_w) अणु
	हाल 32:
		value |= CURSOR_SIZE_32x32;
		अवरोध;

	हाल 64:
		value |= CURSOR_SIZE_64x64;
		अवरोध;

	हाल 128:
		value |= CURSOR_SIZE_128x128;
		अवरोध;

	हाल 256:
		value |= CURSOR_SIZE_256x256;
		अवरोध;

	शेष:
		WARN(1, "cursor size %ux%u not supported\n",
		     new_state->crtc_w, new_state->crtc_h);
		वापस;
	पूर्ण

	value |= (tegra_plane_state->iova[0] >> 10) & 0x3fffff;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_CURSOR_START_ADDR);

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	value = (tegra_plane_state->iova[0] >> 32) & (dma_mask >> 32);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_CURSOR_START_ADDR_HI);
#पूर्ण_अगर

	/* enable cursor and set blend mode */
	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= CURSOR_ENABLE;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_BLEND_CURSOR_CONTROL);
	value &= ~CURSOR_DST_BLEND_MASK;
	value &= ~CURSOR_SRC_BLEND_MASK;

	अगर (dc->soc->has_nvdisplay)
		value &= ~CURSOR_COMPOSITION_MODE_XOR;
	अन्यथा
		value |= CURSOR_MODE_NORMAL;

	value |= CURSOR_DST_BLEND_NEG_K1_TIMES_SRC;
	value |= CURSOR_SRC_BLEND_K1_TIMES_SRC;
	value |= CURSOR_ALPHA;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_BLEND_CURSOR_CONTROL);

	/* nvdisplay relies on software क्रम clipping */
	अगर (dc->soc->has_nvdisplay) अणु
		काष्ठा drm_rect src;

		x = new_state->dst.x1;
		y = new_state->dst.y1;

		drm_rect_fp_to_पूर्णांक(&src, &new_state->src);

		value = (src.y1 & tegra->vmask) << 16 | (src.x1 & tegra->hmask);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_PCALC_HEAD_SET_CROPPED_POINT_IN_CURSOR);

		value = (drm_rect_height(&src) & tegra->vmask) << 16 |
			(drm_rect_width(&src) & tegra->hmask);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_PCALC_HEAD_SET_CROPPED_SIZE_IN_CURSOR);
	पूर्ण अन्यथा अणु
		x = new_state->crtc_x;
		y = new_state->crtc_y;
	पूर्ण

	/* position the cursor */
	value = ((y & tegra->vmask) << 16) | (x & tegra->hmask);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_CURSOR_POSITION);
पूर्ण

अटल व्योम tegra_cursor_atomic_disable(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा tegra_dc *dc;
	u32 value;

	/* rien ne va plus */
	अगर (!old_state || !old_state->crtc)
		वापस;

	dc = to_tegra_dc(old_state->crtc);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value &= ~CURSOR_ENABLE;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_WIN_OPTIONS);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs tegra_cursor_plane_helper_funcs = अणु
	.prepare_fb = tegra_plane_prepare_fb,
	.cleanup_fb = tegra_plane_cleanup_fb,
	.atomic_check = tegra_cursor_atomic_check,
	.atomic_update = tegra_cursor_atomic_update,
	.atomic_disable = tegra_cursor_atomic_disable,
पूर्ण;

अटल काष्ठा drm_plane *tegra_dc_cursor_plane_create(काष्ठा drm_device *drm,
						      काष्ठा tegra_dc *dc)
अणु
	अचिन्हित दीर्घ possible_crtcs = tegra_plane_get_possible_crtcs(drm);
	काष्ठा tegra_plane *plane;
	अचिन्हित पूर्णांक num_क्रमmats;
	स्थिर u32 *क्रमmats;
	पूर्णांक err;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * This index is kind of fake. The cursor isn't a regular plane, but
	 * its update and activation request bits in DC_CMD_STATE_CONTROL करो
	 * use the same programming. Setting this fake index here allows the
	 * code in tegra_add_plane_state() to करो the right thing without the
	 * need to special-casing the cursor plane.
	 */
	plane->index = 6;
	plane->dc = dc;

	अगर (!dc->soc->has_nvdisplay) अणु
		num_क्रमmats = ARRAY_SIZE(tegra_legacy_cursor_plane_क्रमmats);
		क्रमmats = tegra_legacy_cursor_plane_क्रमmats;
	पूर्ण अन्यथा अणु
		num_क्रमmats = ARRAY_SIZE(tegra_cursor_plane_क्रमmats);
		क्रमmats = tegra_cursor_plane_क्रमmats;
	पूर्ण

	err = drm_universal_plane_init(drm, &plane->base, possible_crtcs,
				       &tegra_plane_funcs, क्रमmats,
				       num_क्रमmats, शून्य,
				       DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (err < 0) अणु
		kमुक्त(plane);
		वापस ERR_PTR(err);
	पूर्ण

	drm_plane_helper_add(&plane->base, &tegra_cursor_plane_helper_funcs);
	drm_plane_create_zpos_immutable_property(&plane->base, 255);

	वापस &plane->base;
पूर्ण

अटल स्थिर u32 tegra20_overlay_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* non-native क्रमmats */
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_XRGB8888,
	/* planar क्रमmats */
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
पूर्ण;

अटल स्थिर u32 tegra114_overlay_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* new on Tegra114 */
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	/* planar क्रमmats */
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
पूर्ण;

अटल स्थिर u32 tegra124_overlay_क्रमmats[] = अणु
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_ARGB8888,
	/* new on Tegra114 */
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	/* new on Tegra124 */
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRX8888,
	/* planar क्रमmats */
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
पूर्ण;

अटल काष्ठा drm_plane *tegra_dc_overlay_plane_create(काष्ठा drm_device *drm,
						       काष्ठा tegra_dc *dc,
						       अचिन्हित पूर्णांक index,
						       bool cursor)
अणु
	अचिन्हित दीर्घ possible_crtcs = tegra_plane_get_possible_crtcs(drm);
	काष्ठा tegra_plane *plane;
	अचिन्हित पूर्णांक num_क्रमmats;
	क्रमागत drm_plane_type type;
	स्थिर u32 *क्रमmats;
	पूर्णांक err;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	plane->offset = 0xa00 + 0x200 * index;
	plane->index = index;
	plane->dc = dc;

	num_क्रमmats = dc->soc->num_overlay_क्रमmats;
	क्रमmats = dc->soc->overlay_क्रमmats;

	अगर (!cursor)
		type = DRM_PLANE_TYPE_OVERLAY;
	अन्यथा
		type = DRM_PLANE_TYPE_CURSOR;

	err = drm_universal_plane_init(drm, &plane->base, possible_crtcs,
				       &tegra_plane_funcs, क्रमmats,
				       num_क्रमmats, शून्य, type, शून्य);
	अगर (err < 0) अणु
		kमुक्त(plane);
		वापस ERR_PTR(err);
	पूर्ण

	drm_plane_helper_add(&plane->base, &tegra_plane_helper_funcs);
	drm_plane_create_zpos_property(&plane->base, plane->index, 0, 255);

	err = drm_plane_create_rotation_property(&plane->base,
						 DRM_MODE_ROTATE_0,
						 DRM_MODE_ROTATE_0 |
						 DRM_MODE_ROTATE_180 |
						 DRM_MODE_REFLECT_X |
						 DRM_MODE_REFLECT_Y);
	अगर (err < 0)
		dev_err(dc->dev, "failed to create rotation property: %d\n",
			err);

	वापस &plane->base;
पूर्ण

अटल काष्ठा drm_plane *tegra_dc_add_shared_planes(काष्ठा drm_device *drm,
						    काष्ठा tegra_dc *dc)
अणु
	काष्ठा drm_plane *plane, *primary = शून्य;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < dc->soc->num_wgrps; i++) अणु
		स्थिर काष्ठा tegra_winकरोwgroup_soc *wgrp = &dc->soc->wgrps[i];

		अगर (wgrp->dc == dc->pipe) अणु
			क्रम (j = 0; j < wgrp->num_winकरोws; j++) अणु
				अचिन्हित पूर्णांक index = wgrp->winकरोws[j];

				plane = tegra_shared_plane_create(drm, dc,
								  wgrp->index,
								  index);
				अगर (IS_ERR(plane))
					वापस plane;

				/*
				 * Choose the first shared plane owned by this
				 * head as the primary plane.
				 */
				अगर (!primary) अणु
					plane->type = DRM_PLANE_TYPE_PRIMARY;
					primary = plane;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस primary;
पूर्ण

अटल काष्ठा drm_plane *tegra_dc_add_planes(काष्ठा drm_device *drm,
					     काष्ठा tegra_dc *dc)
अणु
	काष्ठा drm_plane *planes[2], *primary;
	अचिन्हित पूर्णांक planes_num;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	primary = tegra_primary_plane_create(drm, dc);
	अगर (IS_ERR(primary))
		वापस primary;

	अगर (dc->soc->supports_cursor)
		planes_num = 2;
	अन्यथा
		planes_num = 1;

	क्रम (i = 0; i < planes_num; i++) अणु
		planes[i] = tegra_dc_overlay_plane_create(drm, dc, 1 + i,
							  false);
		अगर (IS_ERR(planes[i])) अणु
			err = PTR_ERR(planes[i]);

			जबतक (i--)
				tegra_plane_funcs.destroy(planes[i]);

			tegra_plane_funcs.destroy(primary);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	वापस primary;
पूर्ण

अटल व्योम tegra_dc_destroy(काष्ठा drm_crtc *crtc)
अणु
	drm_crtc_cleanup(crtc);
पूर्ण

अटल व्योम tegra_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tegra_dc_state *state = kzalloc(माप(*state), GFP_KERNEL);

	अगर (crtc->state)
		tegra_crtc_atomic_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *
tegra_crtc_atomic_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tegra_dc_state *state = to_dc_state(crtc->state);
	काष्ठा tegra_dc_state *copy;

	copy = kदो_स्मृति(माप(*copy), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &copy->base);
	copy->clk = state->clk;
	copy->pclk = state->pclk;
	copy->भाग = state->भाग;
	copy->planes = state->planes;

	वापस &copy->base;
पूर्ण

अटल व्योम tegra_crtc_atomic_destroy_state(काष्ठा drm_crtc *crtc,
					    काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(state);
पूर्ण

#घोषणा DEBUGFS_REG32(_name) अणु .name = #_name, .offset = _name पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 tegra_dc_regs[] = अणु
	DEBUGFS_REG32(DC_CMD_GENERAL_INCR_SYNCPT),
	DEBUGFS_REG32(DC_CMD_GENERAL_INCR_SYNCPT_CNTRL),
	DEBUGFS_REG32(DC_CMD_GENERAL_INCR_SYNCPT_ERROR),
	DEBUGFS_REG32(DC_CMD_WIN_A_INCR_SYNCPT),
	DEBUGFS_REG32(DC_CMD_WIN_A_INCR_SYNCPT_CNTRL),
	DEBUGFS_REG32(DC_CMD_WIN_A_INCR_SYNCPT_ERROR),
	DEBUGFS_REG32(DC_CMD_WIN_B_INCR_SYNCPT),
	DEBUGFS_REG32(DC_CMD_WIN_B_INCR_SYNCPT_CNTRL),
	DEBUGFS_REG32(DC_CMD_WIN_B_INCR_SYNCPT_ERROR),
	DEBUGFS_REG32(DC_CMD_WIN_C_INCR_SYNCPT),
	DEBUGFS_REG32(DC_CMD_WIN_C_INCR_SYNCPT_CNTRL),
	DEBUGFS_REG32(DC_CMD_WIN_C_INCR_SYNCPT_ERROR),
	DEBUGFS_REG32(DC_CMD_CONT_SYNCPT_VSYNC),
	DEBUGFS_REG32(DC_CMD_DISPLAY_COMMAND_OPTION0),
	DEBUGFS_REG32(DC_CMD_DISPLAY_COMMAND),
	DEBUGFS_REG32(DC_CMD_SIGNAL_RAISE),
	DEBUGFS_REG32(DC_CMD_DISPLAY_POWER_CONTROL),
	DEBUGFS_REG32(DC_CMD_INT_STATUS),
	DEBUGFS_REG32(DC_CMD_INT_MASK),
	DEBUGFS_REG32(DC_CMD_INT_ENABLE),
	DEBUGFS_REG32(DC_CMD_INT_TYPE),
	DEBUGFS_REG32(DC_CMD_INT_POLARITY),
	DEBUGFS_REG32(DC_CMD_SIGNAL_RAISE1),
	DEBUGFS_REG32(DC_CMD_SIGNAL_RAISE2),
	DEBUGFS_REG32(DC_CMD_SIGNAL_RAISE3),
	DEBUGFS_REG32(DC_CMD_STATE_ACCESS),
	DEBUGFS_REG32(DC_CMD_STATE_CONTROL),
	DEBUGFS_REG32(DC_CMD_DISPLAY_WINDOW_HEADER),
	DEBUGFS_REG32(DC_CMD_REG_ACT_CONTROL),
	DEBUGFS_REG32(DC_COM_CRC_CONTROL),
	DEBUGFS_REG32(DC_COM_CRC_CHECKSUM),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_ENABLE(0)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_ENABLE(1)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_ENABLE(2)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_ENABLE(3)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_POLARITY(0)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_POLARITY(1)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_POLARITY(2)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_POLARITY(3)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_DATA(0)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_DATA(1)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_DATA(2)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_DATA(3)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_ENABLE(0)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_ENABLE(1)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_ENABLE(2)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_ENABLE(3)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_DATA(0)),
	DEBUGFS_REG32(DC_COM_PIN_INPUT_DATA(1)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(0)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(1)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(2)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(3)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(4)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(5)),
	DEBUGFS_REG32(DC_COM_PIN_OUTPUT_SELECT(6)),
	DEBUGFS_REG32(DC_COM_PIN_MISC_CONTROL),
	DEBUGFS_REG32(DC_COM_PIN_PM0_CONTROL),
	DEBUGFS_REG32(DC_COM_PIN_PM0_DUTY_CYCLE),
	DEBUGFS_REG32(DC_COM_PIN_PM1_CONTROL),
	DEBUGFS_REG32(DC_COM_PIN_PM1_DUTY_CYCLE),
	DEBUGFS_REG32(DC_COM_SPI_CONTROL),
	DEBUGFS_REG32(DC_COM_SPI_START_BYTE),
	DEBUGFS_REG32(DC_COM_HSPI_WRITE_DATA_AB),
	DEBUGFS_REG32(DC_COM_HSPI_WRITE_DATA_CD),
	DEBUGFS_REG32(DC_COM_HSPI_CS_DC),
	DEBUGFS_REG32(DC_COM_SCRATCH_REGISTER_A),
	DEBUGFS_REG32(DC_COM_SCRATCH_REGISTER_B),
	DEBUGFS_REG32(DC_COM_GPIO_CTRL),
	DEBUGFS_REG32(DC_COM_GPIO_DEBOUNCE_COUNTER),
	DEBUGFS_REG32(DC_COM_CRC_CHECKSUM_LATCHED),
	DEBUGFS_REG32(DC_DISP_DISP_SIGNAL_OPTIONS0),
	DEBUGFS_REG32(DC_DISP_DISP_SIGNAL_OPTIONS1),
	DEBUGFS_REG32(DC_DISP_DISP_WIN_OPTIONS),
	DEBUGFS_REG32(DC_DISP_DISP_MEM_HIGH_PRIORITY),
	DEBUGFS_REG32(DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER),
	DEBUGFS_REG32(DC_DISP_DISP_TIMING_OPTIONS),
	DEBUGFS_REG32(DC_DISP_REF_TO_SYNC),
	DEBUGFS_REG32(DC_DISP_SYNC_WIDTH),
	DEBUGFS_REG32(DC_DISP_BACK_PORCH),
	DEBUGFS_REG32(DC_DISP_ACTIVE),
	DEBUGFS_REG32(DC_DISP_FRONT_PORCH),
	DEBUGFS_REG32(DC_DISP_H_PULSE0_CONTROL),
	DEBUGFS_REG32(DC_DISP_H_PULSE0_POSITION_A),
	DEBUGFS_REG32(DC_DISP_H_PULSE0_POSITION_B),
	DEBUGFS_REG32(DC_DISP_H_PULSE0_POSITION_C),
	DEBUGFS_REG32(DC_DISP_H_PULSE0_POSITION_D),
	DEBUGFS_REG32(DC_DISP_H_PULSE1_CONTROL),
	DEBUGFS_REG32(DC_DISP_H_PULSE1_POSITION_A),
	DEBUGFS_REG32(DC_DISP_H_PULSE1_POSITION_B),
	DEBUGFS_REG32(DC_DISP_H_PULSE1_POSITION_C),
	DEBUGFS_REG32(DC_DISP_H_PULSE1_POSITION_D),
	DEBUGFS_REG32(DC_DISP_H_PULSE2_CONTROL),
	DEBUGFS_REG32(DC_DISP_H_PULSE2_POSITION_A),
	DEBUGFS_REG32(DC_DISP_H_PULSE2_POSITION_B),
	DEBUGFS_REG32(DC_DISP_H_PULSE2_POSITION_C),
	DEBUGFS_REG32(DC_DISP_H_PULSE2_POSITION_D),
	DEBUGFS_REG32(DC_DISP_V_PULSE0_CONTROL),
	DEBUGFS_REG32(DC_DISP_V_PULSE0_POSITION_A),
	DEBUGFS_REG32(DC_DISP_V_PULSE0_POSITION_B),
	DEBUGFS_REG32(DC_DISP_V_PULSE0_POSITION_C),
	DEBUGFS_REG32(DC_DISP_V_PULSE1_CONTROL),
	DEBUGFS_REG32(DC_DISP_V_PULSE1_POSITION_A),
	DEBUGFS_REG32(DC_DISP_V_PULSE1_POSITION_B),
	DEBUGFS_REG32(DC_DISP_V_PULSE1_POSITION_C),
	DEBUGFS_REG32(DC_DISP_V_PULSE2_CONTROL),
	DEBUGFS_REG32(DC_DISP_V_PULSE2_POSITION_A),
	DEBUGFS_REG32(DC_DISP_V_PULSE3_CONTROL),
	DEBUGFS_REG32(DC_DISP_V_PULSE3_POSITION_A),
	DEBUGFS_REG32(DC_DISP_M0_CONTROL),
	DEBUGFS_REG32(DC_DISP_M1_CONTROL),
	DEBUGFS_REG32(DC_DISP_DI_CONTROL),
	DEBUGFS_REG32(DC_DISP_PP_CONTROL),
	DEBUGFS_REG32(DC_DISP_PP_SELECT_A),
	DEBUGFS_REG32(DC_DISP_PP_SELECT_B),
	DEBUGFS_REG32(DC_DISP_PP_SELECT_C),
	DEBUGFS_REG32(DC_DISP_PP_SELECT_D),
	DEBUGFS_REG32(DC_DISP_DISP_CLOCK_CONTROL),
	DEBUGFS_REG32(DC_DISP_DISP_INTERFACE_CONTROL),
	DEBUGFS_REG32(DC_DISP_DISP_COLOR_CONTROL),
	DEBUGFS_REG32(DC_DISP_SHIFT_CLOCK_OPTIONS),
	DEBUGFS_REG32(DC_DISP_DATA_ENABLE_OPTIONS),
	DEBUGFS_REG32(DC_DISP_SERIAL_INTERFACE_OPTIONS),
	DEBUGFS_REG32(DC_DISP_LCD_SPI_OPTIONS),
	DEBUGFS_REG32(DC_DISP_BORDER_COLOR),
	DEBUGFS_REG32(DC_DISP_COLOR_KEY0_LOWER),
	DEBUGFS_REG32(DC_DISP_COLOR_KEY0_UPPER),
	DEBUGFS_REG32(DC_DISP_COLOR_KEY1_LOWER),
	DEBUGFS_REG32(DC_DISP_COLOR_KEY1_UPPER),
	DEBUGFS_REG32(DC_DISP_CURSOR_FOREGROUND),
	DEBUGFS_REG32(DC_DISP_CURSOR_BACKGROUND),
	DEBUGFS_REG32(DC_DISP_CURSOR_START_ADDR),
	DEBUGFS_REG32(DC_DISP_CURSOR_START_ADDR_NS),
	DEBUGFS_REG32(DC_DISP_CURSOR_POSITION),
	DEBUGFS_REG32(DC_DISP_CURSOR_POSITION_NS),
	DEBUGFS_REG32(DC_DISP_INIT_SEQ_CONTROL),
	DEBUGFS_REG32(DC_DISP_SPI_INIT_SEQ_DATA_A),
	DEBUGFS_REG32(DC_DISP_SPI_INIT_SEQ_DATA_B),
	DEBUGFS_REG32(DC_DISP_SPI_INIT_SEQ_DATA_C),
	DEBUGFS_REG32(DC_DISP_SPI_INIT_SEQ_DATA_D),
	DEBUGFS_REG32(DC_DISP_DC_MCCIF_FIFOCTRL),
	DEBUGFS_REG32(DC_DISP_MCCIF_DISPLAY0A_HYST),
	DEBUGFS_REG32(DC_DISP_MCCIF_DISPLAY0B_HYST),
	DEBUGFS_REG32(DC_DISP_MCCIF_DISPLAY1A_HYST),
	DEBUGFS_REG32(DC_DISP_MCCIF_DISPLAY1B_HYST),
	DEBUGFS_REG32(DC_DISP_DAC_CRT_CTRL),
	DEBUGFS_REG32(DC_DISP_DISP_MISC_CONTROL),
	DEBUGFS_REG32(DC_DISP_SD_CONTROL),
	DEBUGFS_REG32(DC_DISP_SD_CSC_COEFF),
	DEBUGFS_REG32(DC_DISP_SD_LUT(0)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(1)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(2)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(3)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(4)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(5)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(6)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(7)),
	DEBUGFS_REG32(DC_DISP_SD_LUT(8)),
	DEBUGFS_REG32(DC_DISP_SD_FLICKER_CONTROL),
	DEBUGFS_REG32(DC_DISP_DC_PIXEL_COUNT),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(0)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(1)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(2)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(3)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(4)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(5)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(6)),
	DEBUGFS_REG32(DC_DISP_SD_HISTOGRAM(7)),
	DEBUGFS_REG32(DC_DISP_SD_BL_TF(0)),
	DEBUGFS_REG32(DC_DISP_SD_BL_TF(1)),
	DEBUGFS_REG32(DC_DISP_SD_BL_TF(2)),
	DEBUGFS_REG32(DC_DISP_SD_BL_TF(3)),
	DEBUGFS_REG32(DC_DISP_SD_BL_CONTROL),
	DEBUGFS_REG32(DC_DISP_SD_HW_K_VALUES),
	DEBUGFS_REG32(DC_DISP_SD_MAN_K_VALUES),
	DEBUGFS_REG32(DC_DISP_CURSOR_START_ADDR_HI),
	DEBUGFS_REG32(DC_DISP_BLEND_CURSOR_CONTROL),
	DEBUGFS_REG32(DC_WIN_WIN_OPTIONS),
	DEBUGFS_REG32(DC_WIN_BYTE_SWAP),
	DEBUGFS_REG32(DC_WIN_BUFFER_CONTROL),
	DEBUGFS_REG32(DC_WIN_COLOR_DEPTH),
	DEBUGFS_REG32(DC_WIN_POSITION),
	DEBUGFS_REG32(DC_WIN_SIZE),
	DEBUGFS_REG32(DC_WIN_PRESCALED_SIZE),
	DEBUGFS_REG32(DC_WIN_H_INITIAL_DDA),
	DEBUGFS_REG32(DC_WIN_V_INITIAL_DDA),
	DEBUGFS_REG32(DC_WIN_DDA_INC),
	DEBUGFS_REG32(DC_WIN_LINE_STRIDE),
	DEBUGFS_REG32(DC_WIN_BUF_STRIDE),
	DEBUGFS_REG32(DC_WIN_UV_BUF_STRIDE),
	DEBUGFS_REG32(DC_WIN_BUFFER_ADDR_MODE),
	DEBUGFS_REG32(DC_WIN_DV_CONTROL),
	DEBUGFS_REG32(DC_WIN_BLEND_NOKEY),
	DEBUGFS_REG32(DC_WIN_BLEND_1WIN),
	DEBUGFS_REG32(DC_WIN_BLEND_2WIN_X),
	DEBUGFS_REG32(DC_WIN_BLEND_2WIN_Y),
	DEBUGFS_REG32(DC_WIN_BLEND_3WIN_XY),
	DEBUGFS_REG32(DC_WIN_HP_FETCH_CONTROL),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR_NS),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR_U),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR_U_NS),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR_V),
	DEBUGFS_REG32(DC_WINBUF_START_ADDR_V_NS),
	DEBUGFS_REG32(DC_WINBUF_ADDR_H_OFFSET),
	DEBUGFS_REG32(DC_WINBUF_ADDR_H_OFFSET_NS),
	DEBUGFS_REG32(DC_WINBUF_ADDR_V_OFFSET),
	DEBUGFS_REG32(DC_WINBUF_ADDR_V_OFFSET_NS),
	DEBUGFS_REG32(DC_WINBUF_UFLOW_STATUS),
	DEBUGFS_REG32(DC_WINBUF_AD_UFLOW_STATUS),
	DEBUGFS_REG32(DC_WINBUF_BD_UFLOW_STATUS),
	DEBUGFS_REG32(DC_WINBUF_CD_UFLOW_STATUS),
पूर्ण;

अटल पूर्णांक tegra_dc_show_regs(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_dc *dc = node->info_ent->data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	drm_modeset_lock(&dc->base.mutex, शून्य);

	अगर (!dc->base.state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(tegra_dc_regs); i++) अणु
		अचिन्हित पूर्णांक offset = tegra_dc_regs[i].offset;

		seq_म_लिखो(s, "%-40s %#05x %08x\n", tegra_dc_regs[i].name,
			   offset, tegra_dc_पढ़ोl(dc, offset));
	पूर्ण

unlock:
	drm_modeset_unlock(&dc->base.mutex);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_dc_show_crc(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_dc *dc = node->info_ent->data;
	पूर्णांक err = 0;
	u32 value;

	drm_modeset_lock(&dc->base.mutex, शून्य);

	अगर (!dc->base.state->active) अणु
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	value = DC_COM_CRC_CONTROL_ACTIVE_DATA | DC_COM_CRC_CONTROL_ENABLE;
	tegra_dc_ग_लिखोl(dc, value, DC_COM_CRC_CONTROL);
	tegra_dc_commit(dc);

	drm_crtc_रुको_one_vblank(&dc->base);
	drm_crtc_रुको_one_vblank(&dc->base);

	value = tegra_dc_पढ़ोl(dc, DC_COM_CRC_CHECKSUM);
	seq_म_लिखो(s, "%08x\n", value);

	tegra_dc_ग_लिखोl(dc, 0, DC_COM_CRC_CONTROL);

unlock:
	drm_modeset_unlock(&dc->base.mutex);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_dc_show_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा tegra_dc *dc = node->info_ent->data;

	seq_म_लिखो(s, "frames: %lu\n", dc->stats.frames);
	seq_म_लिखो(s, "vblank: %lu\n", dc->stats.vblank);
	seq_म_लिखो(s, "underflow: %lu\n", dc->stats.underflow);
	seq_म_लिखो(s, "overflow: %lu\n", dc->stats.overflow);

	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list debugfs_files[] = अणु
	अणु "regs", tegra_dc_show_regs, 0, शून्य पूर्ण,
	अणु "crc", tegra_dc_show_crc, 0, शून्य पूर्ण,
	अणु "stats", tegra_dc_show_stats, 0, शून्य पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_dc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	अचिन्हित पूर्णांक i, count = ARRAY_SIZE(debugfs_files);
	काष्ठा drm_minor *minor = crtc->dev->primary;
	काष्ठा dentry *root;
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);

#अगर_घोषित CONFIG_DEBUG_FS
	root = crtc->debugfs_entry;
#अन्यथा
	root = शून्य;
#पूर्ण_अगर

	dc->debugfs_files = kmemdup(debugfs_files, माप(debugfs_files),
				    GFP_KERNEL);
	अगर (!dc->debugfs_files)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++)
		dc->debugfs_files[i].data = dc;

	drm_debugfs_create_files(dc->debugfs_files, count, root, minor);

	वापस 0;
पूर्ण

अटल व्योम tegra_dc_early_unरेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	अचिन्हित पूर्णांक count = ARRAY_SIZE(debugfs_files);
	काष्ठा drm_minor *minor = crtc->dev->primary;
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);

	drm_debugfs_हटाओ_files(dc->debugfs_files, count, minor);
	kमुक्त(dc->debugfs_files);
	dc->debugfs_files = शून्य;
पूर्ण

अटल u32 tegra_dc_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);

	/* XXX vblank syncpoपूर्णांकs करोn't work with nvdisplay yet */
	अगर (dc->syncpt && !dc->soc->has_nvdisplay)
		वापस host1x_syncpt_पढ़ो(dc->syncpt);

	/* fallback to software emulated VBLANK counter */
	वापस (u32)drm_crtc_vblank_count(&dc->base);
पूर्ण

अटल पूर्णांक tegra_dc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	value = tegra_dc_पढ़ोl(dc, DC_CMD_INT_MASK);
	value |= VBLANK_INT;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_MASK);

	वापस 0;
पूर्ण

अटल व्योम tegra_dc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	value = tegra_dc_पढ़ोl(dc, DC_CMD_INT_MASK);
	value &= ~VBLANK_INT;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_MASK);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs tegra_crtc_funcs = अणु
	.page_flip = drm_atomic_helper_page_flip,
	.set_config = drm_atomic_helper_set_config,
	.destroy = tegra_dc_destroy,
	.reset = tegra_crtc_reset,
	.atomic_duplicate_state = tegra_crtc_atomic_duplicate_state,
	.atomic_destroy_state = tegra_crtc_atomic_destroy_state,
	.late_रेजिस्टर = tegra_dc_late_रेजिस्टर,
	.early_unरेजिस्टर = tegra_dc_early_unरेजिस्टर,
	.get_vblank_counter = tegra_dc_get_vblank_counter,
	.enable_vblank = tegra_dc_enable_vblank,
	.disable_vblank = tegra_dc_disable_vblank,
पूर्ण;

अटल पूर्णांक tegra_dc_set_timings(काष्ठा tegra_dc *dc,
				काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक h_ref_to_sync = 1;
	अचिन्हित पूर्णांक v_ref_to_sync = 1;
	अचिन्हित दीर्घ value;

	अगर (!dc->soc->has_nvdisplay) अणु
		tegra_dc_ग_लिखोl(dc, 0x0, DC_DISP_DISP_TIMING_OPTIONS);

		value = (v_ref_to_sync << 16) | h_ref_to_sync;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_REF_TO_SYNC);
	पूर्ण

	value = ((mode->vsync_end - mode->vsync_start) << 16) |
		((mode->hsync_end - mode->hsync_start) <<  0);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_SYNC_WIDTH);

	value = ((mode->vtotal - mode->vsync_end) << 16) |
		((mode->htotal - mode->hsync_end) <<  0);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_BACK_PORCH);

	value = ((mode->vsync_start - mode->vdisplay) << 16) |
		((mode->hsync_start - mode->hdisplay) <<  0);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_FRONT_PORCH);

	value = (mode->vdisplay << 16) | mode->hdisplay;
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_ACTIVE);

	वापस 0;
पूर्ण

/**
 * tegra_dc_state_setup_घड़ी - check घड़ी settings and store them in atomic
 *     state
 * @dc: display controller
 * @crtc_state: CRTC atomic state
 * @clk: parent घड़ी क्रम display controller
 * @pclk: pixel घड़ी
 * @भाग: shअगरt घड़ी भागider
 *
 * Returns:
 * 0 on success or a negative error-code on failure.
 */
पूर्णांक tegra_dc_state_setup_घड़ी(काष्ठा tegra_dc *dc,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा clk *clk, अचिन्हित दीर्घ pclk,
			       अचिन्हित पूर्णांक भाग)
अणु
	काष्ठा tegra_dc_state *state = to_dc_state(crtc_state);

	अगर (!clk_has_parent(dc->clk, clk))
		वापस -EINVAL;

	state->clk = clk;
	state->pclk = pclk;
	state->भाग = भाग;

	वापस 0;
पूर्ण

अटल व्योम tegra_dc_commit_state(काष्ठा tegra_dc *dc,
				  काष्ठा tegra_dc_state *state)
अणु
	u32 value;
	पूर्णांक err;

	err = clk_set_parent(dc->clk, state->clk);
	अगर (err < 0)
		dev_err(dc->dev, "failed to set parent clock: %d\n", err);

	/*
	 * Outमाला_दो may not want to change the parent घड़ी rate. This is only
	 * relevant to Tegra20 where only a single display PLL is available.
	 * Since that PLL would typically be used क्रम HDMI, an पूर्णांकernal LVDS
	 * panel would need to be driven by some other घड़ी such as PLL_P
	 * which is shared with other peripherals. Changing the घड़ी rate
	 * should thereक्रमe be aव्योमed.
	 */
	अगर (state->pclk > 0) अणु
		err = clk_set_rate(state->clk, state->pclk);
		अगर (err < 0)
			dev_err(dc->dev,
				"failed to set clock rate to %lu Hz\n",
				state->pclk);

		err = clk_set_rate(dc->clk, state->pclk);
		अगर (err < 0)
			dev_err(dc->dev, "failed to set clock %pC to %lu Hz: %d\n",
				dc->clk, state->pclk, err);
	पूर्ण

	DRM_DEBUG_KMS("rate: %lu, div: %u\n", clk_get_rate(dc->clk),
		      state->भाग);
	DRM_DEBUG_KMS("pclk: %lu\n", state->pclk);

	अगर (!dc->soc->has_nvdisplay) अणु
		value = SHIFT_CLK_DIVIDER(state->भाग) | PIXEL_CLK_DIVIDER_PCD1;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_CLOCK_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम tegra_dc_stop(काष्ठा tegra_dc *dc)
अणु
	u32 value;

	/* stop the display controller */
	value = tegra_dc_पढ़ोl(dc, DC_CMD_DISPLAY_COMMAND);
	value &= ~DISP_CTRL_MODE_MASK;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_DISPLAY_COMMAND);

	tegra_dc_commit(dc);
पूर्ण

अटल bool tegra_dc_idle(काष्ठा tegra_dc *dc)
अणु
	u32 value;

	value = tegra_dc_पढ़ोl_active(dc, DC_CMD_DISPLAY_COMMAND);

	वापस (value & DISP_CTRL_MODE_MASK) == 0;
पूर्ण

अटल पूर्णांक tegra_dc_रुको_idle(काष्ठा tegra_dc *dc, अचिन्हित दीर्घ समयout)
अणु
	समयout = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (tegra_dc_idle(dc))
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	dev_dbg(dc->dev, "timeout waiting for DC to become idle\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम tegra_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;
	पूर्णांक err;

	अगर (!tegra_dc_idle(dc)) अणु
		tegra_dc_stop(dc);

		/*
		 * Ignore the वापस value, there isn't anything useful to करो
		 * in हाल this fails.
		 */
		tegra_dc_रुको_idle(dc, 100);
	पूर्ण

	/*
	 * This should really be part of the RGB encoder driver, but clearing
	 * these bits has the side-effect of stopping the display controller.
	 * When that happens no VBLANK पूर्णांकerrupts will be उठाओd. At the same
	 * समय the encoder is disabled beक्रमe the display controller, so the
	 * above code is always going to समयout रुकोing क्रम the controller
	 * to go idle.
	 *
	 * Given the बंद coupling between the RGB encoder and the display
	 * controller करोing it here is still kind of okay. None of the other
	 * encoder drivers require these bits to be cleared.
	 *
	 * XXX: Perhaps given that the display controller is चयनed off at
	 * this poपूर्णांक anyway maybe clearing these bits isn't even useful क्रम
	 * the RGB encoder?
	 */
	अगर (dc->rgb) अणु
		value = tegra_dc_पढ़ोl(dc, DC_CMD_DISPLAY_POWER_CONTROL);
		value &= ~(PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE |
			   PW4_ENABLE | PM0_ENABLE | PM1_ENABLE);
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_DISPLAY_POWER_CONTROL);
	पूर्ण

	tegra_dc_stats_reset(&dc->stats);
	drm_crtc_vblank_off(crtc);

	spin_lock_irq(&crtc->dev->event_lock);

	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण

	spin_unlock_irq(&crtc->dev->event_lock);

	err = host1x_client_suspend(&dc->client);
	अगर (err < 0)
		dev_err(dc->dev, "failed to suspend: %d\n", err);
पूर्ण

अटल व्योम tegra_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा tegra_dc_state *crtc_state = to_dc_state(crtc->state);
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;
	पूर्णांक err;

	err = host1x_client_resume(&dc->client);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	/* initialize display controller */
	अगर (dc->syncpt) अणु
		u32 syncpt = host1x_syncpt_id(dc->syncpt), enable;

		अगर (dc->soc->has_nvdisplay)
			enable = 1 << 31;
		अन्यथा
			enable = 1 << 8;

		value = SYNCPT_CNTRL_NO_STALL;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_GENERAL_INCR_SYNCPT_CNTRL);

		value = enable | syncpt;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_CONT_SYNCPT_VSYNC);
	पूर्ण

	अगर (dc->soc->has_nvdisplay) अणु
		value = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_RBUF_UF_INT |
			DSC_OBUF_UF_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_TYPE);

		value = DSC_TO_UF_INT | DSC_BBUF_UF_INT | DSC_RBUF_UF_INT |
			DSC_OBUF_UF_INT | SD3_BUCKET_WALK_DONE_INT |
			HEAD_UF_INT | MSF_INT | REG_TMOUT_INT |
			REGION_CRC_INT | V_PULSE2_INT | V_PULSE3_INT |
			VBLANK_INT | FRAME_END_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_POLARITY);

		value = SD3_BUCKET_WALK_DONE_INT | HEAD_UF_INT | VBLANK_INT |
			FRAME_END_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_ENABLE);

		value = HEAD_UF_INT | REG_TMOUT_INT | FRAME_END_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_MASK);

		tegra_dc_ग_लिखोl(dc, READ_MUX, DC_CMD_STATE_ACCESS);
	पूर्ण अन्यथा अणु
		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_TYPE);

		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_POLARITY);

		/* initialize समयr */
		value = CURSOR_THRESHOLD(0) | WINDOW_A_THRESHOLD(0x20) |
			WINDOW_B_THRESHOLD(0x20) | WINDOW_C_THRESHOLD(0x20);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_MEM_HIGH_PRIORITY);

		value = CURSOR_THRESHOLD(0) | WINDOW_A_THRESHOLD(1) |
			WINDOW_B_THRESHOLD(1) | WINDOW_C_THRESHOLD(1);
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_DISP_MEM_HIGH_PRIORITY_TIMER);

		value = VBLANK_INT | WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_ENABLE);

		value = WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT |
			WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_INT_MASK);
	पूर्ण

	अगर (dc->soc->supports_background_color)
		tegra_dc_ग_लिखोl(dc, 0, DC_DISP_BLEND_BACKGROUND_COLOR);
	अन्यथा
		tegra_dc_ग_लिखोl(dc, 0, DC_DISP_BORDER_COLOR);

	/* apply PLL and pixel घड़ी changes */
	tegra_dc_commit_state(dc, crtc_state);

	/* program display mode */
	tegra_dc_set_timings(dc, mode);

	/* पूर्णांकerlacing isn't supported yet, so disable it */
	अगर (dc->soc->supports_पूर्णांकerlacing) अणु
		value = tegra_dc_पढ़ोl(dc, DC_DISP_INTERLACE_CONTROL);
		value &= ~INTERLACE_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_DISP_INTERLACE_CONTROL);
	पूर्ण

	value = tegra_dc_पढ़ोl(dc, DC_CMD_DISPLAY_COMMAND);
	value &= ~DISP_CTRL_MODE_MASK;
	value |= DISP_CTRL_MODE_C_DISPLAY;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_DISPLAY_COMMAND);

	अगर (!dc->soc->has_nvdisplay) अणु
		value = tegra_dc_पढ़ोl(dc, DC_CMD_DISPLAY_POWER_CONTROL);
		value |= PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE |
			 PW4_ENABLE | PM0_ENABLE | PM1_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_CMD_DISPLAY_POWER_CONTROL);
	पूर्ण

	/* enable underflow reporting and display red क्रम missing pixels */
	अगर (dc->soc->has_nvdisplay) अणु
		value = UNDERFLOW_MODE_RED | UNDERFLOW_REPORT_ENABLE;
		tegra_dc_ग_लिखोl(dc, value, DC_COM_RG_UNDERFLOW);
	पूर्ण

	tegra_dc_commit(dc);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम tegra_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	अचिन्हित दीर्घ flags;

	अगर (crtc->state->event) अणु
		spin_lock_irqsave(&crtc->dev->event_lock, flags);

		अगर (drm_crtc_vblank_get(crtc) != 0)
			drm_crtc_send_vblank_event(crtc, crtc->state->event);
		अन्यथा
			drm_crtc_arm_vblank_event(crtc, crtc->state->event);

		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम tegra_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा tegra_dc_state *dc_state = to_dc_state(crtc_state);
	काष्ठा tegra_dc *dc = to_tegra_dc(crtc);
	u32 value;

	value = dc_state->planes << 8 | GENERAL_UPDATE;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_STATE_CONTROL);
	value = tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);

	value = dc_state->planes | GENERAL_ACT_REQ;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_STATE_CONTROL);
	value = tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs tegra_crtc_helper_funcs = अणु
	.atomic_begin = tegra_crtc_atomic_begin,
	.atomic_flush = tegra_crtc_atomic_flush,
	.atomic_enable = tegra_crtc_atomic_enable,
	.atomic_disable = tegra_crtc_atomic_disable,
पूर्ण;

अटल irqवापस_t tegra_dc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tegra_dc *dc = data;
	अचिन्हित दीर्घ status;

	status = tegra_dc_पढ़ोl(dc, DC_CMD_INT_STATUS);
	tegra_dc_ग_लिखोl(dc, status, DC_CMD_INT_STATUS);

	अगर (status & FRAME_END_INT) अणु
		/*
		dev_dbg(dc->dev, "%s(): frame end\n", __func__);
		*/
		dc->stats.frames++;
	पूर्ण

	अगर (status & VBLANK_INT) अणु
		/*
		dev_dbg(dc->dev, "%s(): vertical blank\n", __func__);
		*/
		drm_crtc_handle_vblank(&dc->base);
		dc->stats.vblank++;
	पूर्ण

	अगर (status & (WIN_A_UF_INT | WIN_B_UF_INT | WIN_C_UF_INT)) अणु
		/*
		dev_dbg(dc->dev, "%s(): underflow\n", __func__);
		*/
		dc->stats.underflow++;
	पूर्ण

	अगर (status & (WIN_A_OF_INT | WIN_B_OF_INT | WIN_C_OF_INT)) अणु
		/*
		dev_dbg(dc->dev, "%s(): overflow\n", __func__);
		*/
		dc->stats.overflow++;
	पूर्ण

	अगर (status & HEAD_UF_INT) अणु
		dev_dbg_ratelimited(dc->dev, "%s(): head underflow\n", __func__);
		dc->stats.underflow++;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल bool tegra_dc_has_winकरोw_groups(काष्ठा tegra_dc *dc)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!dc->soc->wgrps)
		वापस true;

	क्रम (i = 0; i < dc->soc->num_wgrps; i++) अणु
		स्थिर काष्ठा tegra_winकरोwgroup_soc *wgrp = &dc->soc->wgrps[i];

		अगर (wgrp->dc == dc->pipe && wgrp->num_winकरोws > 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tegra_dc_early_init(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	tegra->num_crtcs++;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_init(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	अचिन्हित दीर्घ flags = HOST1X_SYNCPT_CLIENT_MANAGED;
	काष्ठा tegra_dc *dc = host1x_client_to_dc(client);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा drm_plane *primary = शून्य;
	काष्ठा drm_plane *cursor = शून्य;
	पूर्णांक err;

	/*
	 * DC has been reset by now, so VBLANK syncpoपूर्णांक can be released
	 * क्रम general use.
	 */
	host1x_syncpt_release_vblank_reservation(client, 26 + dc->pipe);

	/*
	 * XXX करो not रेजिस्टर DCs with no winकरोw groups because we cannot
	 * assign a primary plane to them, which in turn will cause KMS to
	 * crash.
	 */
	अगर (!tegra_dc_has_winकरोw_groups(dc))
		वापस 0;

	/*
	 * Set the display hub as the host1x client parent क्रम the display
	 * controller. This is needed क्रम the runसमय reference counting that
	 * ensures the display hub is always घातered when any of the display
	 * controllers are.
	 */
	अगर (dc->soc->has_nvdisplay)
		client->parent = &tegra->hub->client;

	dc->syncpt = host1x_syncpt_request(client, flags);
	अगर (!dc->syncpt)
		dev_warn(dc->dev, "failed to allocate syncpoint\n");

	err = host1x_client_iommu_attach(client);
	अगर (err < 0 && err != -ENODEV) अणु
		dev_err(client->dev, "failed to attach to domain: %d\n", err);
		वापस err;
	पूर्ण

	अगर (dc->soc->wgrps)
		primary = tegra_dc_add_shared_planes(drm, dc);
	अन्यथा
		primary = tegra_dc_add_planes(drm, dc);

	अगर (IS_ERR(primary)) अणु
		err = PTR_ERR(primary);
		जाओ cleanup;
	पूर्ण

	अगर (dc->soc->supports_cursor) अणु
		cursor = tegra_dc_cursor_plane_create(drm, dc);
		अगर (IS_ERR(cursor)) अणु
			err = PTR_ERR(cursor);
			जाओ cleanup;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* dedicate one overlay to mouse cursor */
		cursor = tegra_dc_overlay_plane_create(drm, dc, 2, true);
		अगर (IS_ERR(cursor)) अणु
			err = PTR_ERR(cursor);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	err = drm_crtc_init_with_planes(drm, &dc->base, primary, cursor,
					&tegra_crtc_funcs, शून्य);
	अगर (err < 0)
		जाओ cleanup;

	drm_crtc_helper_add(&dc->base, &tegra_crtc_helper_funcs);

	/*
	 * Keep track of the minimum pitch alignment across all display
	 * controllers.
	 */
	अगर (dc->soc->pitch_align > tegra->pitch_align)
		tegra->pitch_align = dc->soc->pitch_align;

	/* track maximum resolution */
	अगर (dc->soc->has_nvdisplay)
		drm->mode_config.max_width = drm->mode_config.max_height = 16384;
	अन्यथा
		drm->mode_config.max_width = drm->mode_config.max_height = 4096;

	err = tegra_dc_rgb_init(drm, dc);
	अगर (err < 0 && err != -ENODEV) अणु
		dev_err(dc->dev, "failed to initialize RGB output: %d\n", err);
		जाओ cleanup;
	पूर्ण

	err = devm_request_irq(dc->dev, dc->irq, tegra_dc_irq, 0,
			       dev_name(dc->dev), dc);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to request IRQ#%u: %d\n", dc->irq,
			err);
		जाओ cleanup;
	पूर्ण

	/*
	 * Inherit the DMA parameters (such as maximum segment size) from the
	 * parent host1x device.
	 */
	client->dev->dma_parms = client->host->dma_parms;

	वापस 0;

cleanup:
	अगर (!IS_ERR_OR_शून्य(cursor))
		drm_plane_cleanup(cursor);

	अगर (!IS_ERR(primary))
		drm_plane_cleanup(primary);

	host1x_client_iommu_detach(client);
	host1x_syncpt_put(dc->syncpt);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_dc_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dc *dc = host1x_client_to_dc(client);
	पूर्णांक err;

	अगर (!tegra_dc_has_winकरोw_groups(dc))
		वापस 0;

	/* aव्योम a dangling poपूर्णांकer just in हाल this disappears */
	client->dev->dma_parms = शून्य;

	devm_मुक्त_irq(dc->dev, dc->irq, dc);

	err = tegra_dc_rgb_निकास(dc);
	अगर (err) अणु
		dev_err(dc->dev, "failed to shutdown RGB output: %d\n", err);
		वापस err;
	पूर्ण

	host1x_client_iommu_detach(client);
	host1x_syncpt_put(dc->syncpt);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_late_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	tegra->num_crtcs--;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_runसमय_suspend(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dc *dc = host1x_client_to_dc(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = reset_control_निश्चित(dc->rst);
	अगर (err < 0) अणु
		dev_err(dev, "failed to assert reset: %d\n", err);
		वापस err;
	पूर्ण

	अगर (dc->soc->has_घातergate)
		tegra_घातergate_घातer_off(dc->घातergate);

	clk_disable_unprepare(dc->clk);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_runसमय_resume(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_dc *dc = host1x_client_to_dc(client);
	काष्ठा device *dev = client->dev;
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", err);
		वापस err;
	पूर्ण

	अगर (dc->soc->has_घातergate) अणु
		err = tegra_घातergate_sequence_घातer_up(dc->घातergate, dc->clk,
							dc->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to power partition: %d\n", err);
			जाओ put_rpm;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = clk_prepare_enable(dc->clk);
		अगर (err < 0) अणु
			dev_err(dev, "failed to enable clock: %d\n", err);
			जाओ put_rpm;
		पूर्ण

		err = reset_control_deनिश्चित(dc->rst);
		अगर (err < 0) अणु
			dev_err(dev, "failed to deassert reset: %d\n", err);
			जाओ disable_clk;
		पूर्ण
	पूर्ण

	वापस 0;

disable_clk:
	clk_disable_unprepare(dc->clk);
put_rpm:
	pm_runसमय_put_sync(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops dc_client_ops = अणु
	.early_init = tegra_dc_early_init,
	.init = tegra_dc_init,
	.निकास = tegra_dc_निकास,
	.late_निकास = tegra_dc_late_निकास,
	.suspend = tegra_dc_runसमय_suspend,
	.resume = tegra_dc_runसमय_resume,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra20_dc_soc_info = अणु
	.supports_background_color = false,
	.supports_पूर्णांकerlacing = false,
	.supports_cursor = false,
	.supports_block_linear = false,
	.supports_sector_layout = false,
	.has_legacy_blending = true,
	.pitch_align = 8,
	.has_घातergate = false,
	.coupled_pm = true,
	.has_nvdisplay = false,
	.num_primary_क्रमmats = ARRAY_SIZE(tegra20_primary_क्रमmats),
	.primary_क्रमmats = tegra20_primary_क्रमmats,
	.num_overlay_क्रमmats = ARRAY_SIZE(tegra20_overlay_क्रमmats),
	.overlay_क्रमmats = tegra20_overlay_क्रमmats,
	.modअगरiers = tegra20_modअगरiers,
	.has_win_a_without_filters = true,
	.has_win_c_without_vert_filter = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra30_dc_soc_info = अणु
	.supports_background_color = false,
	.supports_पूर्णांकerlacing = false,
	.supports_cursor = false,
	.supports_block_linear = false,
	.supports_sector_layout = false,
	.has_legacy_blending = true,
	.pitch_align = 8,
	.has_घातergate = false,
	.coupled_pm = false,
	.has_nvdisplay = false,
	.num_primary_क्रमmats = ARRAY_SIZE(tegra20_primary_क्रमmats),
	.primary_क्रमmats = tegra20_primary_क्रमmats,
	.num_overlay_क्रमmats = ARRAY_SIZE(tegra20_overlay_क्रमmats),
	.overlay_क्रमmats = tegra20_overlay_क्रमmats,
	.modअगरiers = tegra20_modअगरiers,
	.has_win_a_without_filters = false,
	.has_win_c_without_vert_filter = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra114_dc_soc_info = अणु
	.supports_background_color = false,
	.supports_पूर्णांकerlacing = false,
	.supports_cursor = false,
	.supports_block_linear = false,
	.supports_sector_layout = false,
	.has_legacy_blending = true,
	.pitch_align = 64,
	.has_घातergate = true,
	.coupled_pm = false,
	.has_nvdisplay = false,
	.num_primary_क्रमmats = ARRAY_SIZE(tegra114_primary_क्रमmats),
	.primary_क्रमmats = tegra114_primary_क्रमmats,
	.num_overlay_क्रमmats = ARRAY_SIZE(tegra114_overlay_क्रमmats),
	.overlay_क्रमmats = tegra114_overlay_क्रमmats,
	.modअगरiers = tegra20_modअगरiers,
	.has_win_a_without_filters = false,
	.has_win_c_without_vert_filter = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra124_dc_soc_info = अणु
	.supports_background_color = true,
	.supports_पूर्णांकerlacing = true,
	.supports_cursor = true,
	.supports_block_linear = true,
	.supports_sector_layout = false,
	.has_legacy_blending = false,
	.pitch_align = 64,
	.has_घातergate = true,
	.coupled_pm = false,
	.has_nvdisplay = false,
	.num_primary_क्रमmats = ARRAY_SIZE(tegra124_primary_क्रमmats),
	.primary_क्रमmats = tegra124_primary_क्रमmats,
	.num_overlay_क्रमmats = ARRAY_SIZE(tegra124_overlay_क्रमmats),
	.overlay_क्रमmats = tegra124_overlay_क्रमmats,
	.modअगरiers = tegra124_modअगरiers,
	.has_win_a_without_filters = false,
	.has_win_c_without_vert_filter = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra210_dc_soc_info = अणु
	.supports_background_color = true,
	.supports_पूर्णांकerlacing = true,
	.supports_cursor = true,
	.supports_block_linear = true,
	.supports_sector_layout = false,
	.has_legacy_blending = false,
	.pitch_align = 64,
	.has_घातergate = true,
	.coupled_pm = false,
	.has_nvdisplay = false,
	.num_primary_क्रमmats = ARRAY_SIZE(tegra114_primary_क्रमmats),
	.primary_क्रमmats = tegra114_primary_क्रमmats,
	.num_overlay_क्रमmats = ARRAY_SIZE(tegra114_overlay_क्रमmats),
	.overlay_क्रमmats = tegra114_overlay_क्रमmats,
	.modअगरiers = tegra124_modअगरiers,
	.has_win_a_without_filters = false,
	.has_win_c_without_vert_filter = false,
पूर्ण;

अटल स्थिर काष्ठा tegra_winकरोwgroup_soc tegra186_dc_wgrps[] = अणु
	अणु
		.index = 0,
		.dc = 0,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 0 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 1,
		.dc = 1,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 1 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 2,
		.dc = 1,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 2 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 3,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 3 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 4,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 4 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 5,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 5 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra186_dc_soc_info = अणु
	.supports_background_color = true,
	.supports_पूर्णांकerlacing = true,
	.supports_cursor = true,
	.supports_block_linear = true,
	.supports_sector_layout = false,
	.has_legacy_blending = false,
	.pitch_align = 64,
	.has_घातergate = false,
	.coupled_pm = false,
	.has_nvdisplay = true,
	.wgrps = tegra186_dc_wgrps,
	.num_wgrps = ARRAY_SIZE(tegra186_dc_wgrps),
पूर्ण;

अटल स्थिर काष्ठा tegra_winकरोwgroup_soc tegra194_dc_wgrps[] = अणु
	अणु
		.index = 0,
		.dc = 0,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 0 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 1,
		.dc = 1,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 1 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 2,
		.dc = 1,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 2 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 3,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 3 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 4,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 4 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण, अणु
		.index = 5,
		.dc = 2,
		.winकरोws = (स्थिर अचिन्हित पूर्णांक[]) अणु 5 पूर्ण,
		.num_winकरोws = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tegra_dc_soc_info tegra194_dc_soc_info = अणु
	.supports_background_color = true,
	.supports_पूर्णांकerlacing = true,
	.supports_cursor = true,
	.supports_block_linear = true,
	.supports_sector_layout = true,
	.has_legacy_blending = false,
	.pitch_align = 64,
	.has_घातergate = false,
	.coupled_pm = false,
	.has_nvdisplay = true,
	.wgrps = tegra194_dc_wgrps,
	.num_wgrps = ARRAY_SIZE(tegra194_dc_wgrps),
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_dc_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra194-dc",
		.data = &tegra194_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra186-dc",
		.data = &tegra186_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra210-dc",
		.data = &tegra210_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra124-dc",
		.data = &tegra124_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra114-dc",
		.data = &tegra114_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra30-dc",
		.data = &tegra30_dc_soc_info,
	पूर्ण, अणु
		.compatible = "nvidia,tegra20-dc",
		.data = &tegra20_dc_soc_info,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_dc_of_match);

अटल पूर्णांक tegra_dc_parse_dt(काष्ठा tegra_dc *dc)
अणु
	काष्ठा device_node *np;
	u32 value = 0;
	पूर्णांक err;

	err = of_property_पढ़ो_u32(dc->dev->of_node, "nvidia,head", &value);
	अगर (err < 0) अणु
		dev_err(dc->dev, "missing \"nvidia,head\" property\n");

		/*
		 * If the nvidia,head property isn't present, try to find the
		 * correct head number by looking up the position of this
		 * display controller's node within the device tree. Assuming
		 * that the nodes are ordered properly in the DTS file and
		 * that the translation पूर्णांकo a flattened device tree blob
		 * preserves that ordering this will actually yield the right
		 * head number.
		 *
		 * If those assumptions करोn't hold, this will still work क्रम
		 * हालs where only a single display controller is used.
		 */
		क्रम_each_matching_node(np, tegra_dc_of_match) अणु
			अगर (np == dc->dev->of_node) अणु
				of_node_put(np);
				अवरोध;
			पूर्ण

			value++;
		पूर्ण
	पूर्ण

	dc->pipe = value;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_match_by_pipe(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा tegra_dc *dc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक pipe = (अचिन्हित दीर्घ)(व्योम *)data;

	वापस dc->pipe == pipe;
पूर्ण

अटल पूर्णांक tegra_dc_couple(काष्ठा tegra_dc *dc)
अणु
	/*
	 * On Tegra20, DC1 requires DC0 to be taken out of reset in order to
	 * be enabled, otherwise CPU hangs on writing to CMD_DISPLAY_COMMAND /
	 * POWER_CONTROL रेजिस्टरs during CRTC enabling.
	 */
	अगर (dc->soc->coupled_pm && dc->pipe == 1) अणु
		काष्ठा device *companion;
		काष्ठा tegra_dc *parent;

		companion = driver_find_device(dc->dev->driver, शून्य, (स्थिर व्योम *)0,
					       tegra_dc_match_by_pipe);
		अगर (!companion)
			वापस -EPROBE_DEFER;

		parent = dev_get_drvdata(companion);
		dc->client.parent = &parent->client;

		dev_dbg(dc->dev, "coupled to %s\n", dev_name(companion));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u64 dma_mask = dma_get_mask(pdev->dev.parent);
	काष्ठा tegra_dc *dc;
	पूर्णांक err;

	err = dma_coerce_mask_and_coherent(&pdev->dev, dma_mask);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		वापस err;
	पूर्ण

	dc = devm_kzalloc(&pdev->dev, माप(*dc), GFP_KERNEL);
	अगर (!dc)
		वापस -ENOMEM;

	dc->soc = of_device_get_match_data(&pdev->dev);

	INIT_LIST_HEAD(&dc->list);
	dc->dev = &pdev->dev;

	err = tegra_dc_parse_dt(dc);
	अगर (err < 0)
		वापस err;

	err = tegra_dc_couple(dc);
	अगर (err < 0)
		वापस err;

	dc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dc->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(dc->clk);
	पूर्ण

	dc->rst = devm_reset_control_get(&pdev->dev, "dc");
	अगर (IS_ERR(dc->rst)) अणु
		dev_err(&pdev->dev, "failed to get reset\n");
		वापस PTR_ERR(dc->rst);
	पूर्ण

	/* निश्चित reset and disable घड़ी */
	err = clk_prepare_enable(dc->clk);
	अगर (err < 0)
		वापस err;

	usleep_range(2000, 4000);

	err = reset_control_निश्चित(dc->rst);
	अगर (err < 0)
		वापस err;

	usleep_range(2000, 4000);

	clk_disable_unprepare(dc->clk);

	अगर (dc->soc->has_घातergate) अणु
		अगर (dc->pipe == 0)
			dc->घातergate = TEGRA_POWERGATE_DIS;
		अन्यथा
			dc->घातergate = TEGRA_POWERGATE_DISB;

		tegra_घातergate_घातer_off(dc->घातergate);
	पूर्ण

	dc->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dc->regs))
		वापस PTR_ERR(dc->regs);

	dc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dc->irq < 0)
		वापस -ENXIO;

	err = tegra_dc_rgb_probe(dc);
	अगर (err < 0 && err != -ENODEV) अणु
		स्थिर अक्षर *level = KERN_ERR;

		अगर (err == -EPROBE_DEFER)
			level = KERN_DEBUG;

		dev_prपूर्णांकk(level, dc->dev, "failed to probe RGB output: %d\n",
			   err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dc);
	pm_runसमय_enable(&pdev->dev);

	INIT_LIST_HEAD(&dc->client.list);
	dc->client.ops = &dc_client_ops;
	dc->client.dev = &pdev->dev;

	err = host1x_client_रेजिस्टर(&dc->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);
		जाओ disable_pm;
	पूर्ण

	वापस 0;

disable_pm:
	pm_runसमय_disable(&pdev->dev);
	tegra_dc_rgb_हटाओ(dc);

	वापस err;
पूर्ण

अटल पूर्णांक tegra_dc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dc *dc = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&dc->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		वापस err;
	पूर्ण

	err = tegra_dc_rgb_हटाओ(dc);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to remove RGB output: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver tegra_dc_driver = अणु
	.driver = अणु
		.name = "tegra-dc",
		.of_match_table = tegra_dc_of_match,
	पूर्ण,
	.probe = tegra_dc_probe,
	.हटाओ = tegra_dc_हटाओ,
पूर्ण;
