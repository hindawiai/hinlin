<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/host1x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "drm.h"
#समावेश "dc.h"
#समावेश "plane.h"

अटल स्थिर u32 tegra_shared_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	/* new on Tegra114 */
	DRM_FORMAT_ABGR4444,
	DRM_FORMAT_ABGR1555,
	DRM_FORMAT_BGRA5551,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGBX5551,
	DRM_FORMAT_XBGR1555,
	DRM_FORMAT_BGRX5551,
	DRM_FORMAT_BGR565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	/* planar क्रमmats */
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
पूर्ण;

अटल स्थिर u64 tegra_shared_plane_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(0),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(1),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(2),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(3),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(4),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(5),
	/*
	 * The GPU sector layout is only supported on Tegra194, but these will
	 * be filtered out later on by ->क्रमmat_mod_supported() on SoCs where
	 * it isn't supported.
	 */
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(0) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(1) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(2) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(3) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(4) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(5) | DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT,
	/* sentinel */
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक tegra_plane_offset(काष्ठा tegra_plane *plane,
					      अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= 0x500 && offset <= 0x581) अणु
		offset = 0x000 + (offset - 0x500);
		वापस plane->offset + offset;
	पूर्ण

	अगर (offset >= 0x700 && offset <= 0x73c) अणु
		offset = 0x180 + (offset - 0x700);
		वापस plane->offset + offset;
	पूर्ण

	अगर (offset >= 0x800 && offset <= 0x83e) अणु
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

अटल पूर्णांक tegra_winकरोwgroup_enable(काष्ठा tegra_winकरोwgroup *wgrp)
अणु
	पूर्णांक err = 0;

	mutex_lock(&wgrp->lock);

	अगर (wgrp->usecount == 0) अणु
		err = host1x_client_resume(wgrp->parent);
		अगर (err < 0) अणु
			dev_err(wgrp->parent->dev, "failed to resume: %d\n", err);
			जाओ unlock;
		पूर्ण

		reset_control_deनिश्चित(wgrp->rst);
	पूर्ण

	wgrp->usecount++;

unlock:
	mutex_unlock(&wgrp->lock);
	वापस err;
पूर्ण

अटल व्योम tegra_winकरोwgroup_disable(काष्ठा tegra_winकरोwgroup *wgrp)
अणु
	पूर्णांक err;

	mutex_lock(&wgrp->lock);

	अगर (wgrp->usecount == 1) अणु
		err = reset_control_निश्चित(wgrp->rst);
		अगर (err < 0) अणु
			pr_err("failed to assert reset for window group %u\n",
			       wgrp->index);
		पूर्ण

		host1x_client_suspend(wgrp->parent);
	पूर्ण

	wgrp->usecount--;
	mutex_unlock(&wgrp->lock);
पूर्ण

पूर्णांक tegra_display_hub_prepare(काष्ठा tegra_display_hub *hub)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * XXX Enabling/disabling winकरोwgroups needs to happen when the owner
	 * display controller is disabled. There's currently no good poपूर्णांक at
	 * which this could be executed, so unconditionally enable all winकरोw
	 * groups क्रम now.
	 */
	क्रम (i = 0; i < hub->soc->num_wgrps; i++) अणु
		काष्ठा tegra_winकरोwgroup *wgrp = &hub->wgrps[i];

		/* Skip orphaned winकरोw group whose parent DC is disabled */
		अगर (wgrp->parent)
			tegra_winकरोwgroup_enable(wgrp);
	पूर्ण

	वापस 0;
पूर्ण

व्योम tegra_display_hub_cleanup(काष्ठा tegra_display_hub *hub)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * XXX Remove this once winकरोw groups can be more fine-grainedly
	 * enabled and disabled.
	 */
	क्रम (i = 0; i < hub->soc->num_wgrps; i++) अणु
		काष्ठा tegra_winकरोwgroup *wgrp = &hub->wgrps[i];

		/* Skip orphaned winकरोw group whose parent DC is disabled */
		अगर (wgrp->parent)
			tegra_winकरोwgroup_disable(wgrp);
	पूर्ण
पूर्ण

अटल व्योम tegra_shared_plane_update(काष्ठा tegra_plane *plane)
अणु
	काष्ठा tegra_dc *dc = plane->dc;
	अचिन्हित दीर्घ समयout;
	u32 mask, value;

	mask = COMMON_UPDATE | WIN_A_UPDATE << plane->base.index;
	tegra_dc_ग_लिखोl(dc, mask, DC_CMD_STATE_CONTROL);

	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);
		अगर ((value & mask) == 0)
			अवरोध;

		usleep_range(100, 400);
	पूर्ण
पूर्ण

अटल व्योम tegra_shared_plane_activate(काष्ठा tegra_plane *plane)
अणु
	काष्ठा tegra_dc *dc = plane->dc;
	अचिन्हित दीर्घ समयout;
	u32 mask, value;

	mask = COMMON_ACTREQ | WIN_A_ACT_REQ << plane->base.index;
	tegra_dc_ग_लिखोl(dc, mask, DC_CMD_STATE_CONTROL);

	समयout = jअगरfies + msecs_to_jअगरfies(1000);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		value = tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);
		अगर ((value & mask) == 0)
			अवरोध;

		usleep_range(100, 400);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
tegra_shared_plane_get_owner(काष्ठा tegra_plane *plane, काष्ठा tegra_dc *dc)
अणु
	अचिन्हित पूर्णांक offset =
		tegra_plane_offset(plane, DC_WIN_CORE_WINDOWGROUP_SET_CONTROL);

	वापस tegra_dc_पढ़ोl(dc, offset) & OWNER_MASK;
पूर्ण

अटल bool tegra_dc_owns_shared_plane(काष्ठा tegra_dc *dc,
				       काष्ठा tegra_plane *plane)
अणु
	काष्ठा device *dev = dc->dev;

	अगर (tegra_shared_plane_get_owner(plane, dc) == dc->pipe) अणु
		अगर (plane->dc == dc)
			वापस true;

		dev_WARN(dev, "head %u owns window %u but is not attached\n",
			 dc->pipe, plane->index);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tegra_shared_plane_set_owner(काष्ठा tegra_plane *plane,
					काष्ठा tegra_dc *new)
अणु
	अचिन्हित पूर्णांक offset =
		tegra_plane_offset(plane, DC_WIN_CORE_WINDOWGROUP_SET_CONTROL);
	काष्ठा tegra_dc *old = plane->dc, *dc = new ? new : old;
	काष्ठा device *dev = new ? new->dev : old->dev;
	अचिन्हित पूर्णांक owner, index = plane->index;
	u32 value;

	value = tegra_dc_पढ़ोl(dc, offset);
	owner = value & OWNER_MASK;

	अगर (new && (owner != OWNER_MASK && owner != new->pipe)) अणु
		dev_WARN(dev, "window %u owned by head %u\n", index, owner);
		वापस -EBUSY;
	पूर्ण

	/*
	 * This seems to happen whenever the head has been disabled with one
	 * or more winकरोws being active. This is harmless because we'll just
	 * reassign the winकरोw to the new head anyway.
	 */
	अगर (old && owner == OWNER_MASK)
		dev_dbg(dev, "window %u not owned by head %u but %u\n", index,
			old->pipe, owner);

	value &= ~OWNER_MASK;

	अगर (new)
		value |= OWNER(new->pipe);
	अन्यथा
		value |= OWNER_MASK;

	tegra_dc_ग_लिखोl(dc, value, offset);

	plane->dc = new;

	वापस 0;
पूर्ण

अटल व्योम tegra_dc_assign_shared_plane(काष्ठा tegra_dc *dc,
					 काष्ठा tegra_plane *plane)
अणु
	u32 value;
	पूर्णांक err;

	अगर (!tegra_dc_owns_shared_plane(dc, plane)) अणु
		err = tegra_shared_plane_set_owner(plane, dc);
		अगर (err < 0)
			वापस;
	पूर्ण

	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_LINEBUF_CONFIG);
	value |= MODE_FOUR_LINES;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_LINEBUF_CONFIG);

	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_WGRP_FETCH_METER);
	value = SLOTS(1);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_WGRP_FETCH_METER);

	/* disable watermark */
	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLA);
	value &= ~LATENCY_CTL_MODE_ENABLE;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLA);

	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLB);
	value |= WATERMARK_MASK;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_WGRP_LATENCY_CTLB);

	/* pipe meter */
	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_PRECOMP_WGRP_PIPE_METER);
	value = PIPE_METER_INT(0) | PIPE_METER_FRAC(0);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_PRECOMP_WGRP_PIPE_METER);

	/* mempool entries */
	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_WGRP_POOL_CONFIG);
	value = MEMPOOL_ENTRIES(0x331);
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_WGRP_POOL_CONFIG);

	value = tegra_plane_पढ़ोl(plane, DC_WIN_CORE_IHUB_THREAD_GROUP);
	value &= ~THREAD_NUM_MASK;
	value |= THREAD_NUM(plane->base.index);
	value |= THREAD_GROUP_ENABLE;
	tegra_plane_ग_लिखोl(plane, value, DC_WIN_CORE_IHUB_THREAD_GROUP);

	tegra_shared_plane_update(plane);
	tegra_shared_plane_activate(plane);
पूर्ण

अटल व्योम tegra_dc_हटाओ_shared_plane(काष्ठा tegra_dc *dc,
					 काष्ठा tegra_plane *plane)
अणु
	tegra_shared_plane_set_owner(plane, शून्य);
पूर्ण

अटल पूर्णांक tegra_shared_plane_atomic_check(काष्ठा drm_plane *plane,
					   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा tegra_plane_state *plane_state = to_tegra_plane_state(new_plane_state);
	काष्ठा tegra_shared_plane *tegra = to_tegra_shared_plane(plane);
	काष्ठा tegra_bo_tiling *tiling = &plane_state->tiling;
	काष्ठा tegra_dc *dc = to_tegra_dc(new_plane_state->crtc);
	पूर्णांक err;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!new_plane_state->crtc || !new_plane_state->fb)
		वापस 0;

	err = tegra_plane_क्रमmat(new_plane_state->fb->क्रमmat->क्रमmat,
				 &plane_state->क्रमmat,
				 &plane_state->swap);
	अगर (err < 0)
		वापस err;

	err = tegra_fb_get_tiling(new_plane_state->fb, tiling);
	अगर (err < 0)
		वापस err;

	अगर (tiling->mode == TEGRA_BO_TILING_MODE_BLOCK &&
	    !dc->soc->supports_block_linear) अणु
		DRM_ERROR("hardware doesn't support block linear mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (tiling->sector_layout == TEGRA_BO_SECTOR_LAYOUT_GPU &&
	    !dc->soc->supports_sector_layout) अणु
		DRM_ERROR("hardware doesn't support GPU sector layout\n");
		वापस -EINVAL;
	पूर्ण

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

	/* XXX scaling is not yet supported, add a check here */

	err = tegra_plane_state_add(&tegra->base, new_plane_state);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम tegra_shared_plane_atomic_disable(काष्ठा drm_plane *plane,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा tegra_plane *p = to_tegra_plane(plane);
	काष्ठा tegra_dc *dc;
	u32 value;
	पूर्णांक err;

	/* rien ne va plus */
	अगर (!old_state || !old_state->crtc)
		वापस;

	dc = to_tegra_dc(old_state->crtc);

	err = host1x_client_resume(&dc->client);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	/*
	 * XXX Legacy helpers seem to someबार call ->atomic_disable() even
	 * on planes that are alपढ़ोy disabled. Make sure we fallback to the
	 * head क्रम this particular state instead of crashing.
	 */
	अगर (WARN_ON(p->dc == शून्य))
		p->dc = dc;

	value = tegra_plane_पढ़ोl(p, DC_WIN_WIN_OPTIONS);
	value &= ~WIN_ENABLE;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WIN_OPTIONS);

	tegra_dc_हटाओ_shared_plane(dc, p);

	host1x_client_suspend(&dc->client);
पूर्ण

अटल व्योम tegra_shared_plane_atomic_update(काष्ठा drm_plane *plane,
					     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा tegra_plane_state *tegra_plane_state = to_tegra_plane_state(new_state);
	काष्ठा tegra_dc *dc = to_tegra_dc(new_state->crtc);
	अचिन्हित पूर्णांक zpos = new_state->normalized_zpos;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा tegra_plane *p = to_tegra_plane(plane);
	dma_addr_t base;
	u32 value;
	पूर्णांक err;

	/* rien ne va plus */
	अगर (!new_state->crtc || !new_state->fb)
		वापस;

	अगर (!new_state->visible) अणु
		tegra_shared_plane_atomic_disable(plane, state);
		वापस;
	पूर्ण

	err = host1x_client_resume(&dc->client);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	tegra_dc_assign_shared_plane(dc, p);

	tegra_plane_ग_लिखोl(p, VCOUNTER, DC_WIN_CORE_ACT_CONTROL);

	/* blending */
	value = BLEND_FACTOR_DST_ALPHA_ZERO | BLEND_FACTOR_SRC_ALPHA_K2 |
		BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_SRC |
		BLEND_FACTOR_SRC_COLOR_K1_TIMES_SRC;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_BLEND_MATCH_SELECT);

	value = BLEND_FACTOR_DST_ALPHA_ZERO | BLEND_FACTOR_SRC_ALPHA_K2 |
		BLEND_FACTOR_DST_COLOR_NEG_K1_TIMES_SRC |
		BLEND_FACTOR_SRC_COLOR_K1_TIMES_SRC;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_BLEND_NOMATCH_SELECT);

	value = K2(255) | K1(255) | WINDOW_LAYER_DEPTH(255 - zpos);
	tegra_plane_ग_लिखोl(p, value, DC_WIN_BLEND_LAYER_CONTROL);

	/* bypass scaling */
	value = HORIZONTAL_TAPS_5 | VERTICAL_TAPS_5;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WINDOWGROUP_SET_CONTROL_INPUT_SCALER);

	value = INPUT_SCALER_VBYPASS | INPUT_SCALER_HBYPASS;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WINDOWGROUP_SET_INPUT_SCALER_USAGE);

	/* disable compression */
	tegra_plane_ग_लिखोl(p, 0, DC_WINBUF_CDE_CONTROL);

	base = tegra_plane_state->iova[0] + fb->offsets[0];

#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	/*
	 * Physical address bit 39 in Tegra194 is used as a चयन क्रम special
	 * logic that swizzles the memory using either the legacy Tegra or the
	 * dGPU sector layout.
	 */
	अगर (tegra_plane_state->tiling.sector_layout == TEGRA_BO_SECTOR_LAYOUT_GPU)
		base |= BIT_ULL(39);
#पूर्ण_अगर

	tegra_plane_ग_लिखोl(p, tegra_plane_state->क्रमmat, DC_WIN_COLOR_DEPTH);
	tegra_plane_ग_लिखोl(p, 0, DC_WIN_PRECOMP_WGRP_PARAMS);

	value = V_POSITION(new_state->crtc_y) |
		H_POSITION(new_state->crtc_x);
	tegra_plane_ग_लिखोl(p, value, DC_WIN_POSITION);

	value = V_SIZE(new_state->crtc_h) | H_SIZE(new_state->crtc_w);
	tegra_plane_ग_लिखोl(p, value, DC_WIN_SIZE);

	value = WIN_ENABLE | COLOR_EXPAND;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WIN_OPTIONS);

	value = V_SIZE(new_state->crtc_h) | H_SIZE(new_state->crtc_w);
	tegra_plane_ग_लिखोl(p, value, DC_WIN_CROPPED_SIZE);

	tegra_plane_ग_लिखोl(p, upper_32_bits(base), DC_WINBUF_START_ADDR_HI);
	tegra_plane_ग_लिखोl(p, lower_32_bits(base), DC_WINBUF_START_ADDR);

	value = PITCH(fb->pitches[0]);
	tegra_plane_ग_लिखोl(p, value, DC_WIN_PLANAR_STORAGE);

	value = CLAMP_BEFORE_BLEND | DEGAMMA_SRGB | INPUT_RANGE_FULL;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_SET_PARAMS);

	value = OFFSET_X(new_state->src_y >> 16) |
		OFFSET_Y(new_state->src_x >> 16);
	tegra_plane_ग_लिखोl(p, value, DC_WINBUF_CROPPED_POINT);

	अगर (dc->soc->supports_block_linear) अणु
		अचिन्हित दीर्घ height = tegra_plane_state->tiling.value;

		/* XXX */
		चयन (tegra_plane_state->tiling.mode) अणु
		हाल TEGRA_BO_TILING_MODE_PITCH:
			value = DC_WINBUF_SURFACE_KIND_BLOCK_HEIGHT(0) |
				DC_WINBUF_SURFACE_KIND_PITCH;
			अवरोध;

		/* XXX not supported on Tegra186 and later */
		हाल TEGRA_BO_TILING_MODE_TILED:
			value = DC_WINBUF_SURFACE_KIND_TILED;
			अवरोध;

		हाल TEGRA_BO_TILING_MODE_BLOCK:
			value = DC_WINBUF_SURFACE_KIND_BLOCK_HEIGHT(height) |
				DC_WINBUF_SURFACE_KIND_BLOCK;
			अवरोध;
		पूर्ण

		tegra_plane_ग_लिखोl(p, value, DC_WINBUF_SURFACE_KIND);
	पूर्ण

	/* disable gamut CSC */
	value = tegra_plane_पढ़ोl(p, DC_WIN_WINDOW_SET_CONTROL);
	value &= ~CONTROL_CSC_ENABLE;
	tegra_plane_ग_लिखोl(p, value, DC_WIN_WINDOW_SET_CONTROL);

	host1x_client_suspend(&dc->client);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs tegra_shared_plane_helper_funcs = अणु
	.prepare_fb = tegra_plane_prepare_fb,
	.cleanup_fb = tegra_plane_cleanup_fb,
	.atomic_check = tegra_shared_plane_atomic_check,
	.atomic_update = tegra_shared_plane_atomic_update,
	.atomic_disable = tegra_shared_plane_atomic_disable,
पूर्ण;

काष्ठा drm_plane *tegra_shared_plane_create(काष्ठा drm_device *drm,
					    काष्ठा tegra_dc *dc,
					    अचिन्हित पूर्णांक wgrp,
					    अचिन्हित पूर्णांक index)
अणु
	क्रमागत drm_plane_type type = DRM_PLANE_TYPE_OVERLAY;
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा tegra_display_hub *hub = tegra->hub;
	काष्ठा tegra_shared_plane *plane;
	अचिन्हित पूर्णांक possible_crtcs;
	अचिन्हित पूर्णांक num_क्रमmats;
	स्थिर u64 *modअगरiers;
	काष्ठा drm_plane *p;
	स्थिर u32 *क्रमmats;
	पूर्णांक err;

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	plane->base.offset = 0x0a00 + 0x0300 * index;
	plane->base.index = index;

	plane->wgrp = &hub->wgrps[wgrp];
	plane->wgrp->parent = &dc->client;

	p = &plane->base.base;

	/* planes can be asचिन्हित to arbitrary CRTCs */
	possible_crtcs = BIT(tegra->num_crtcs) - 1;

	num_क्रमmats = ARRAY_SIZE(tegra_shared_plane_क्रमmats);
	क्रमmats = tegra_shared_plane_क्रमmats;
	modअगरiers = tegra_shared_plane_modअगरiers;

	err = drm_universal_plane_init(drm, p, possible_crtcs,
				       &tegra_plane_funcs, क्रमmats,
				       num_क्रमmats, modअगरiers, type, शून्य);
	अगर (err < 0) अणु
		kमुक्त(plane);
		वापस ERR_PTR(err);
	पूर्ण

	drm_plane_helper_add(p, &tegra_shared_plane_helper_funcs);
	drm_plane_create_zpos_property(p, 0, 0, 255);

	वापस p;
पूर्ण

अटल काष्ठा drm_निजी_state *
tegra_display_hub_duplicate_state(काष्ठा drm_निजी_obj *obj)
अणु
	काष्ठा tegra_display_hub_state *state;

	state = kmemdup(obj->state, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_निजी_obj_duplicate_state(obj, &state->base);

	वापस &state->base;
पूर्ण

अटल व्योम tegra_display_hub_destroy_state(काष्ठा drm_निजी_obj *obj,
					    काष्ठा drm_निजी_state *state)
अणु
	काष्ठा tegra_display_hub_state *hub_state =
		to_tegra_display_hub_state(state);

	kमुक्त(hub_state);
पूर्ण

अटल स्थिर काष्ठा drm_निजी_state_funcs tegra_display_hub_state_funcs = अणु
	.atomic_duplicate_state = tegra_display_hub_duplicate_state,
	.atomic_destroy_state = tegra_display_hub_destroy_state,
पूर्ण;

अटल काष्ठा tegra_display_hub_state *
tegra_display_hub_get_state(काष्ठा tegra_display_hub *hub,
			    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_निजी_state *priv;

	priv = drm_atomic_get_निजी_obj_state(state, &hub->base);
	अगर (IS_ERR(priv))
		वापस ERR_CAST(priv);

	वापस to_tegra_display_hub_state(priv);
पूर्ण

पूर्णांक tegra_display_hub_atomic_check(काष्ठा drm_device *drm,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा tegra_display_hub_state *hub_state;
	काष्ठा drm_crtc_state *old, *new;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;

	अगर (!tegra->hub)
		वापस 0;

	hub_state = tegra_display_hub_get_state(tegra->hub, state);
	अगर (IS_ERR(hub_state))
		वापस PTR_ERR(hub_state);

	/*
	 * The display hub display घड़ी needs to be fed by the display घड़ी
	 * with the highest frequency to ensure proper functioning of all the
	 * displays.
	 *
	 * Note that this isn't used before Tegra186, but it doesn't hurt and
	 * conditionalizing it would make the code less clean.
	 */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old, new, i) अणु
		काष्ठा tegra_dc_state *dc = to_dc_state(new);

		अगर (new->active) अणु
			अगर (!hub_state->clk || dc->pclk > hub_state->rate) अणु
				hub_state->dc = to_tegra_dc(dc->base.crtc);
				hub_state->clk = hub_state->dc->clk;
				hub_state->rate = dc->pclk;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra_display_hub_update(काष्ठा tegra_dc *dc)
अणु
	u32 value;
	पूर्णांक err;

	err = host1x_client_resume(&dc->client);
	अगर (err < 0) अणु
		dev_err(dc->dev, "failed to resume: %d\n", err);
		वापस;
	पूर्ण

	value = tegra_dc_पढ़ोl(dc, DC_CMD_IHUB_COMMON_MISC_CTL);
	value &= ~LATENCY_EVENT;
	tegra_dc_ग_लिखोl(dc, value, DC_CMD_IHUB_COMMON_MISC_CTL);

	value = tegra_dc_पढ़ोl(dc, DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER);
	value = CURS_SLOTS(1) | WGRP_SLOTS(1);
	tegra_dc_ग_लिखोl(dc, value, DC_DISP_IHUB_COMMON_DISPLAY_FETCH_METER);

	tegra_dc_ग_लिखोl(dc, COMMON_UPDATE, DC_CMD_STATE_CONTROL);
	tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);
	tegra_dc_ग_लिखोl(dc, COMMON_ACTREQ, DC_CMD_STATE_CONTROL);
	tegra_dc_पढ़ोl(dc, DC_CMD_STATE_CONTROL);

	host1x_client_suspend(&dc->client);
पूर्ण

व्योम tegra_display_hub_atomic_commit(काष्ठा drm_device *drm,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा tegra_display_hub *hub = tegra->hub;
	काष्ठा tegra_display_hub_state *hub_state;
	काष्ठा device *dev = hub->client.dev;
	पूर्णांक err;

	hub_state = to_tegra_display_hub_state(hub->base.state);

	अगर (hub_state->clk) अणु
		err = clk_set_rate(hub_state->clk, hub_state->rate);
		अगर (err < 0)
			dev_err(dev, "failed to set rate of %pC to %lu Hz\n",
				hub_state->clk, hub_state->rate);

		err = clk_set_parent(hub->clk_disp, hub_state->clk);
		अगर (err < 0)
			dev_err(dev, "failed to set parent of %pC to %pC: %d\n",
				hub->clk_disp, hub_state->clk, err);
	पूर्ण

	अगर (hub_state->dc)
		tegra_display_hub_update(hub_state->dc);
पूर्ण

अटल पूर्णांक tegra_display_hub_init(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_display_hub *hub = to_tegra_display_hub(client);
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;
	काष्ठा tegra_display_hub_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	drm_atomic_निजी_obj_init(drm, &hub->base, &state->base,
				    &tegra_display_hub_state_funcs);

	tegra->hub = hub;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_display_hub_निकास(काष्ठा host1x_client *client)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(client->host);
	काष्ठा tegra_drm *tegra = drm->dev_निजी;

	drm_atomic_निजी_obj_fini(&tegra->hub->base);
	tegra->hub = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_display_hub_runसमय_suspend(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_display_hub *hub = to_tegra_display_hub(client);
	काष्ठा device *dev = client->dev;
	अचिन्हित पूर्णांक i = hub->num_heads;
	पूर्णांक err;

	err = reset_control_निश्चित(hub->rst);
	अगर (err < 0)
		वापस err;

	जबतक (i--)
		clk_disable_unprepare(hub->clk_heads[i]);

	clk_disable_unprepare(hub->clk_hub);
	clk_disable_unprepare(hub->clk_dsc);
	clk_disable_unprepare(hub->clk_disp);

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_display_hub_runसमय_resume(काष्ठा host1x_client *client)
अणु
	काष्ठा tegra_display_hub *hub = to_tegra_display_hub(client);
	काष्ठा device *dev = client->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(dev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to get runtime PM: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(hub->clk_disp);
	अगर (err < 0)
		जाओ put_rpm;

	err = clk_prepare_enable(hub->clk_dsc);
	अगर (err < 0)
		जाओ disable_disp;

	err = clk_prepare_enable(hub->clk_hub);
	अगर (err < 0)
		जाओ disable_dsc;

	क्रम (i = 0; i < hub->num_heads; i++) अणु
		err = clk_prepare_enable(hub->clk_heads[i]);
		अगर (err < 0)
			जाओ disable_heads;
	पूर्ण

	err = reset_control_deनिश्चित(hub->rst);
	अगर (err < 0)
		जाओ disable_heads;

	वापस 0;

disable_heads:
	जबतक (i--)
		clk_disable_unprepare(hub->clk_heads[i]);

	clk_disable_unprepare(hub->clk_hub);
disable_dsc:
	clk_disable_unprepare(hub->clk_dsc);
disable_disp:
	clk_disable_unprepare(hub->clk_disp);
put_rpm:
	pm_runसमय_put_sync(dev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा host1x_client_ops tegra_display_hub_ops = अणु
	.init = tegra_display_hub_init,
	.निकास = tegra_display_hub_निकास,
	.suspend = tegra_display_hub_runसमय_suspend,
	.resume = tegra_display_hub_runसमय_resume,
पूर्ण;

अटल पूर्णांक tegra_display_hub_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u64 dma_mask = dma_get_mask(pdev->dev.parent);
	काष्ठा device_node *child = शून्य;
	काष्ठा tegra_display_hub *hub;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = dma_coerce_mask_and_coherent(&pdev->dev, dma_mask);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to set DMA mask: %d\n", err);
		वापस err;
	पूर्ण

	hub = devm_kzalloc(&pdev->dev, माप(*hub), GFP_KERNEL);
	अगर (!hub)
		वापस -ENOMEM;

	hub->soc = of_device_get_match_data(&pdev->dev);

	hub->clk_disp = devm_clk_get(&pdev->dev, "disp");
	अगर (IS_ERR(hub->clk_disp)) अणु
		err = PTR_ERR(hub->clk_disp);
		वापस err;
	पूर्ण

	अगर (hub->soc->supports_dsc) अणु
		hub->clk_dsc = devm_clk_get(&pdev->dev, "dsc");
		अगर (IS_ERR(hub->clk_dsc)) अणु
			err = PTR_ERR(hub->clk_dsc);
			वापस err;
		पूर्ण
	पूर्ण

	hub->clk_hub = devm_clk_get(&pdev->dev, "hub");
	अगर (IS_ERR(hub->clk_hub)) अणु
		err = PTR_ERR(hub->clk_hub);
		वापस err;
	पूर्ण

	hub->rst = devm_reset_control_get(&pdev->dev, "misc");
	अगर (IS_ERR(hub->rst)) अणु
		err = PTR_ERR(hub->rst);
		वापस err;
	पूर्ण

	hub->wgrps = devm_kसुस्मृति(&pdev->dev, hub->soc->num_wgrps,
				  माप(*hub->wgrps), GFP_KERNEL);
	अगर (!hub->wgrps)
		वापस -ENOMEM;

	क्रम (i = 0; i < hub->soc->num_wgrps; i++) अणु
		काष्ठा tegra_winकरोwgroup *wgrp = &hub->wgrps[i];
		अक्षर id[8];

		snम_लिखो(id, माप(id), "wgrp%u", i);
		mutex_init(&wgrp->lock);
		wgrp->usecount = 0;
		wgrp->index = i;

		wgrp->rst = devm_reset_control_get(&pdev->dev, id);
		अगर (IS_ERR(wgrp->rst))
			वापस PTR_ERR(wgrp->rst);

		err = reset_control_निश्चित(wgrp->rst);
		अगर (err < 0)
			वापस err;
	पूर्ण

	hub->num_heads = of_get_child_count(pdev->dev.of_node);

	hub->clk_heads = devm_kसुस्मृति(&pdev->dev, hub->num_heads, माप(clk),
				      GFP_KERNEL);
	अगर (!hub->clk_heads)
		वापस -ENOMEM;

	क्रम (i = 0; i < hub->num_heads; i++) अणु
		child = of_get_next_child(pdev->dev.of_node, child);
		अगर (!child) अणु
			dev_err(&pdev->dev, "failed to find node for head %u\n",
				i);
			वापस -ENODEV;
		पूर्ण

		clk = devm_get_clk_from_child(&pdev->dev, child, "dc");
		अगर (IS_ERR(clk)) अणु
			dev_err(&pdev->dev, "failed to get clock for head %u\n",
				i);
			of_node_put(child);
			वापस PTR_ERR(clk);
		पूर्ण

		hub->clk_heads[i] = clk;
	पूर्ण

	of_node_put(child);

	/* XXX: enable घड़ी across reset? */
	err = reset_control_निश्चित(hub->rst);
	अगर (err < 0)
		वापस err;

	platक्रमm_set_drvdata(pdev, hub);
	pm_runसमय_enable(&pdev->dev);

	INIT_LIST_HEAD(&hub->client.list);
	hub->client.ops = &tegra_display_hub_ops;
	hub->client.dev = &pdev->dev;

	err = host1x_client_रेजिस्टर(&hub->client);
	अगर (err < 0)
		dev_err(&pdev->dev, "failed to register host1x client: %d\n",
			err);

	err = devm_of_platक्रमm_populate(&pdev->dev);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	वापस err;

unरेजिस्टर:
	host1x_client_unरेजिस्टर(&hub->client);
	pm_runसमय_disable(&pdev->dev);
	वापस err;
पूर्ण

अटल पूर्णांक tegra_display_hub_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_display_hub *hub = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = host1x_client_unरेजिस्टर(&hub->client);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
	पूर्ण

	क्रम (i = 0; i < hub->soc->num_wgrps; i++) अणु
		काष्ठा tegra_winकरोwgroup *wgrp = &hub->wgrps[i];

		mutex_destroy(&wgrp->lock);
	पूर्ण

	pm_runसमय_disable(&pdev->dev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा tegra_display_hub_soc tegra186_display_hub = अणु
	.num_wgrps = 6,
	.supports_dsc = true,
पूर्ण;

अटल स्थिर काष्ठा tegra_display_hub_soc tegra194_display_hub = अणु
	.num_wgrps = 6,
	.supports_dsc = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_display_hub_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra194-display",
		.data = &tegra194_display_hub
	पूर्ण, अणु
		.compatible = "nvidia,tegra186-display",
		.data = &tegra186_display_hub
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_display_hub_of_match);

काष्ठा platक्रमm_driver tegra_display_hub_driver = अणु
	.driver = अणु
		.name = "tegra-display-hub",
		.of_match_table = tegra_display_hub_of_match,
	पूर्ण,
	.probe = tegra_display_hub_probe,
	.हटाओ = tegra_display_hub_हटाओ,
पूर्ण;
