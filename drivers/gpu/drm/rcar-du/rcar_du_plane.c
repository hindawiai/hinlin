<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_plane.c  --  R-Car Display Unit Planes
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_group.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_plane.h"
#समावेश "rcar_du_regs.h"

/* -----------------------------------------------------------------------------
 * Atomic hardware plane allocator
 *
 * The hardware plane allocator is solely based on the atomic plane states
 * without keeping any बाह्यal state to aव्योम races between .atomic_check()
 * and .atomic_commit().
 *
 * The core idea is to aव्योम using a मुक्त planes biपंचांगask that would need to be
 * shared between check and commit handlers with a collective knowledge based on
 * the allocated hardware plane(s) क्रम each KMS plane. The allocator then loops
 * over all plane states to compute the मुक्त planes biपंचांगask, allocates hardware
 * planes based on that biपंचांगask, and stores the result back in the plane states.
 *
 * For this to work we need to access the current state of planes not touched by
 * the atomic update. To ensure that it won't be modअगरied, we need to lock all
 * planes using drm_atomic_get_plane_state(). This effectively serializes atomic
 * updates from .atomic_check() up to completion (when swapping the states अगर
 * the check step has succeeded) or rollback (when मुक्तing the states अगर the
 * check step has failed).
 *
 * Allocation is perक्रमmed in the .atomic_check() handler and applied
 * स्वतःmatically when the core swaps the old and new states.
 */

अटल bool rcar_du_plane_needs_पुनः_स्मृति(
				स्थिर काष्ठा rcar_du_plane_state *old_state,
				स्थिर काष्ठा rcar_du_plane_state *new_state)
अणु
	/*
	 * Lowering the number of planes करोesn't strictly require पुनः_स्मृतिation
	 * as the extra hardware plane will be मुक्तd when committing, but करोing
	 * so could lead to more fragmentation.
	 */
	अगर (!old_state->क्रमmat ||
	    old_state->क्रमmat->planes != new_state->क्रमmat->planes)
		वापस true;

	/* Reallocate hardware planes अगर the source has changed. */
	अगर (old_state->source != new_state->source)
		वापस true;

	वापस false;
पूर्ण

अटल अचिन्हित पूर्णांक rcar_du_plane_hwmask(काष्ठा rcar_du_plane_state *state)
अणु
	अचिन्हित पूर्णांक mask;

	अगर (state->hwindex == -1)
		वापस 0;

	mask = 1 << state->hwindex;
	अगर (state->क्रमmat->planes == 2)
		mask |= 1 << ((state->hwindex + 1) % 8);

	वापस mask;
पूर्ण

/*
 * The R8A7790 DU can source frames directly from the VSP1 devices VSPD0 and
 * VSPD1. VSPD0 feeds DU0/1 plane 0, and VSPD1 feeds either DU2 plane 0 or
 * DU0/1 plane 1.
 *
 * Allocate the correct fixed plane when sourcing frames from VSPD0 or VSPD1,
 * and allocate planes in reverse index order otherwise to ensure maximum
 * availability of planes 0 and 1.
 *
 * The caller is responsible क्रम ensuring that the requested source is
 * compatible with the DU revision.
 */
अटल पूर्णांक rcar_du_plane_hwalloc(काष्ठा rcar_du_plane *plane,
				 काष्ठा rcar_du_plane_state *state,
				 अचिन्हित पूर्णांक मुक्त)
अणु
	अचिन्हित पूर्णांक num_planes = state->क्रमmat->planes;
	पूर्णांक fixed = -1;
	पूर्णांक i;

	अगर (state->source == RCAR_DU_PLANE_VSPD0) अणु
		/* VSPD0 feeds plane 0 on DU0/1. */
		अगर (plane->group->index != 0)
			वापस -EINVAL;

		fixed = 0;
	पूर्ण अन्यथा अगर (state->source == RCAR_DU_PLANE_VSPD1) अणु
		/* VSPD1 feeds plane 1 on DU0/1 or plane 0 on DU2. */
		fixed = plane->group->index == 0 ? 1 : 0;
	पूर्ण

	अगर (fixed >= 0)
		वापस मुक्त & (1 << fixed) ? fixed : -EBUSY;

	क्रम (i = RCAR_DU_NUM_HW_PLANES - 1; i >= 0; --i) अणु
		अगर (!(मुक्त & (1 << i)))
			जारी;

		अगर (num_planes == 1 || मुक्त & (1 << ((i + 1) % 8)))
			अवरोध;
	पूर्ण

	वापस i < 0 ? -EBUSY : i;
पूर्ण

पूर्णांक rcar_du_atomic_check_planes(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	अचिन्हित पूर्णांक group_मुक्तd_planes[RCAR_DU_MAX_GROUPS] = अणु 0, पूर्ण;
	अचिन्हित पूर्णांक group_मुक्त_planes[RCAR_DU_MAX_GROUPS] = अणु 0, पूर्ण;
	bool needs_पुनः_स्मृति = false;
	अचिन्हित पूर्णांक groups = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा drm_plane *drm_plane;
	काष्ठा drm_plane_state *old_drm_plane_state;
	काष्ठा drm_plane_state *new_drm_plane_state;

	/* Check अगर hardware planes need to be पुनः_स्मृतिated. */
	क्रम_each_oldnew_plane_in_state(state, drm_plane, old_drm_plane_state,
				       new_drm_plane_state, i) अणु
		काष्ठा rcar_du_plane_state *old_plane_state;
		काष्ठा rcar_du_plane_state *new_plane_state;
		काष्ठा rcar_du_plane *plane;
		अचिन्हित पूर्णांक index;

		plane = to_rcar_plane(drm_plane);
		old_plane_state = to_rcar_plane_state(old_drm_plane_state);
		new_plane_state = to_rcar_plane_state(new_drm_plane_state);

		dev_dbg(rcdu->dev, "%s: checking plane (%u,%tu)\n", __func__,
			plane->group->index, plane - plane->group->planes);

		/*
		 * If the plane is being disabled we करोn't need to go through
		 * the full पुनः_स्मृतिation procedure. Just mark the hardware
		 * plane(s) as मुक्तd.
		 */
		अगर (!new_plane_state->क्रमmat) अणु
			dev_dbg(rcdu->dev, "%s: plane is being disabled\n",
				__func__);
			index = plane - plane->group->planes;
			group_मुक्तd_planes[plane->group->index] |= 1 << index;
			new_plane_state->hwindex = -1;
			जारी;
		पूर्ण

		/*
		 * If the plane needs to be पुनः_स्मृतिated mark it as such, and
		 * mark the hardware plane(s) as मुक्त.
		 */
		अगर (rcar_du_plane_needs_पुनः_स्मृति(old_plane_state, new_plane_state)) अणु
			dev_dbg(rcdu->dev, "%s: plane needs reallocation\n",
				__func__);
			groups |= 1 << plane->group->index;
			needs_पुनः_स्मृति = true;

			index = plane - plane->group->planes;
			group_मुक्तd_planes[plane->group->index] |= 1 << index;
			new_plane_state->hwindex = -1;
		पूर्ण
	पूर्ण

	अगर (!needs_पुनः_स्मृति)
		वापस 0;

	/*
	 * Grab all plane states क्रम the groups that need पुनः_स्मृतिation to ensure
	 * locking and aव्योम racy updates. This serializes the update operation,
	 * but there's not much we can do about it as that's the hardware
	 * design.
	 *
	 * Compute the used planes mask क्रम each group at the same समय to aव्योम
	 * looping over the planes separately later.
	 */
	जबतक (groups) अणु
		अचिन्हित पूर्णांक index = ffs(groups) - 1;
		काष्ठा rcar_du_group *group = &rcdu->groups[index];
		अचिन्हित पूर्णांक used_planes = 0;

		dev_dbg(rcdu->dev, "%s: finding free planes for group %u\n",
			__func__, index);

		क्रम (i = 0; i < group->num_planes; ++i) अणु
			काष्ठा rcar_du_plane *plane = &group->planes[i];
			काष्ठा rcar_du_plane_state *new_plane_state;
			काष्ठा drm_plane_state *s;

			s = drm_atomic_get_plane_state(state, &plane->plane);
			अगर (IS_ERR(s))
				वापस PTR_ERR(s);

			/*
			 * If the plane has been मुक्तd in the above loop its
			 * hardware planes must not be added to the used planes
			 * biपंचांगask. However, the current state करोesn't reflect
			 * the मुक्त state yet, as we've modअगरied the new state
			 * above. Use the local मुक्तd planes list to check क्रम
			 * that condition instead.
			 */
			अगर (group_मुक्तd_planes[index] & (1 << i)) अणु
				dev_dbg(rcdu->dev,
					"%s: plane (%u,%tu) has been freed, skipping\n",
					__func__, plane->group->index,
					plane - plane->group->planes);
				जारी;
			पूर्ण

			new_plane_state = to_rcar_plane_state(s);
			used_planes |= rcar_du_plane_hwmask(new_plane_state);

			dev_dbg(rcdu->dev,
				"%s: plane (%u,%tu) uses %u hwplanes (index %d)\n",
				__func__, plane->group->index,
				plane - plane->group->planes,
				new_plane_state->क्रमmat ?
				new_plane_state->क्रमmat->planes : 0,
				new_plane_state->hwindex);
		पूर्ण

		group_मुक्त_planes[index] = 0xff & ~used_planes;
		groups &= ~(1 << index);

		dev_dbg(rcdu->dev, "%s: group %u free planes mask 0x%02x\n",
			__func__, index, group_मुक्त_planes[index]);
	पूर्ण

	/* Reallocate hardware planes क्रम each plane that needs it. */
	क्रम_each_oldnew_plane_in_state(state, drm_plane, old_drm_plane_state,
				       new_drm_plane_state, i) अणु
		काष्ठा rcar_du_plane_state *old_plane_state;
		काष्ठा rcar_du_plane_state *new_plane_state;
		काष्ठा rcar_du_plane *plane;
		अचिन्हित पूर्णांक crtc_planes;
		अचिन्हित पूर्णांक मुक्त;
		पूर्णांक idx;

		plane = to_rcar_plane(drm_plane);
		old_plane_state = to_rcar_plane_state(old_drm_plane_state);
		new_plane_state = to_rcar_plane_state(new_drm_plane_state);

		dev_dbg(rcdu->dev, "%s: allocating plane (%u,%tu)\n", __func__,
			plane->group->index, plane - plane->group->planes);

		/*
		 * Skip planes that are being disabled or करोn't need to be
		 * पुनः_स्मृतिated.
		 */
		अगर (!new_plane_state->क्रमmat ||
		    !rcar_du_plane_needs_पुनः_स्मृति(old_plane_state, new_plane_state))
			जारी;

		/*
		 * Try to allocate the plane from the मुक्त planes currently
		 * associated with the target CRTC to aव्योम restarting the CRTC
		 * group and thus minimize flicker. If it fails fall back to
		 * allocating from all मुक्त planes.
		 */
		crtc_planes = to_rcar_crtc(new_plane_state->state.crtc)->index % 2
			    ? plane->group->dptsr_planes
			    : ~plane->group->dptsr_planes;
		मुक्त = group_मुक्त_planes[plane->group->index];

		idx = rcar_du_plane_hwalloc(plane, new_plane_state,
					    मुक्त & crtc_planes);
		अगर (idx < 0)
			idx = rcar_du_plane_hwalloc(plane, new_plane_state,
						    मुक्त);
		अगर (idx < 0) अणु
			dev_dbg(rcdu->dev, "%s: no available hardware plane\n",
				__func__);
			वापस idx;
		पूर्ण

		dev_dbg(rcdu->dev, "%s: allocated %u hwplanes (index %u)\n",
			__func__, new_plane_state->क्रमmat->planes, idx);

		new_plane_state->hwindex = idx;

		group_मुक्त_planes[plane->group->index] &=
			~rcar_du_plane_hwmask(new_plane_state);

		dev_dbg(rcdu->dev, "%s: group %u free planes mask 0x%02x\n",
			__func__, plane->group->index,
			group_मुक्त_planes[plane->group->index]);
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Plane Setup
 */

#घोषणा RCAR_DU_COLORKEY_NONE		(0 << 24)
#घोषणा RCAR_DU_COLORKEY_SOURCE		(1 << 24)
#घोषणा RCAR_DU_COLORKEY_MASK		(1 << 24)

अटल व्योम rcar_du_plane_ग_लिखो(काष्ठा rcar_du_group *rgrp,
				अचिन्हित पूर्णांक index, u32 reg, u32 data)
अणु
	rcar_du_ग_लिखो(rgrp->dev, rgrp->mmio_offset + index * PLANE_OFF + reg,
		      data);
पूर्ण

अटल व्योम rcar_du_plane_setup_scanout(काष्ठा rcar_du_group *rgrp,
					स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	अचिन्हित पूर्णांक src_x = state->state.src.x1 >> 16;
	अचिन्हित पूर्णांक src_y = state->state.src.y1 >> 16;
	अचिन्हित पूर्णांक index = state->hwindex;
	अचिन्हित पूर्णांक pitch;
	bool पूर्णांकerlaced;
	u32 dma[2];

	पूर्णांकerlaced = state->state.crtc->state->adjusted_mode.flags
		   & DRM_MODE_FLAG_INTERLACE;

	अगर (state->source == RCAR_DU_PLANE_MEMORY) अणु
		काष्ठा drm_framebuffer *fb = state->state.fb;
		काष्ठा drm_gem_cma_object *gem;
		अचिन्हित पूर्णांक i;

		अगर (state->क्रमmat->planes == 2)
			pitch = fb->pitches[0];
		अन्यथा
			pitch = fb->pitches[0] * 8 / state->क्रमmat->bpp;

		क्रम (i = 0; i < state->क्रमmat->planes; ++i) अणु
			gem = drm_fb_cma_get_gem_obj(fb, i);
			dma[i] = gem->paddr + fb->offsets[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		pitch = drm_rect_width(&state->state.src) >> 16;
		dma[0] = 0;
		dma[1] = 0;
	पूर्ण

	/*
	 * Memory pitch (expressed in pixels). Must be द्विगुनd क्रम पूर्णांकerlaced
	 * operation with 32bpp क्रमmats.
	 */
	rcar_du_plane_ग_लिखो(rgrp, index, PnMWR,
			    (पूर्णांकerlaced && state->क्रमmat->bpp == 32) ?
			    pitch * 2 : pitch);

	/*
	 * The Y position is expressed in raster line units and must be द्विगुनd
	 * क्रम 32bpp क्रमmats, according to the R8A7790 datasheet. No mention of
	 * करोubling the Y position is found in the R8A7779 datasheet, but the
	 * rule seems to apply there as well.
	 *
	 * Despite not being करोcumented, करोubling seem not to be needed when
	 * operating in पूर्णांकerlaced mode.
	 *
	 * Similarly, क्रम the second plane, NV12 and NV21 क्रमmats seem to
	 * require a halved Y position value, in both progressive and पूर्णांकerlaced
	 * modes.
	 */
	rcar_du_plane_ग_लिखो(rgrp, index, PnSPXR, src_x);
	rcar_du_plane_ग_लिखो(rgrp, index, PnSPYR, src_y *
			    (!पूर्णांकerlaced && state->क्रमmat->bpp == 32 ? 2 : 1));

	rcar_du_plane_ग_लिखो(rgrp, index, PnDSA0R, dma[0]);

	अगर (state->क्रमmat->planes == 2) अणु
		index = (index + 1) % 8;

		rcar_du_plane_ग_लिखो(rgrp, index, PnMWR, pitch);

		rcar_du_plane_ग_लिखो(rgrp, index, PnSPXR, src_x);
		rcar_du_plane_ग_लिखो(rgrp, index, PnSPYR, src_y *
				    (state->क्रमmat->bpp == 16 ? 2 : 1) / 2);

		rcar_du_plane_ग_लिखो(rgrp, index, PnDSA0R, dma[1]);
	पूर्ण
पूर्ण

अटल व्योम rcar_du_plane_setup_mode(काष्ठा rcar_du_group *rgrp,
				     अचिन्हित पूर्णांक index,
				     स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	u32 colorkey;
	u32 pnmr;

	/*
	 * The PnALPHAR रेजिस्टर controls alpha-blending in 16bpp क्रमmats
	 * (ARGB1555 and XRGB1555).
	 *
	 * For ARGB, set the alpha value to 0, and enable alpha-blending when
	 * the A bit is 0. This maps A=0 to alpha=0 and A=1 to alpha=255.
	 *
	 * For XRGB, set the alpha value to the plane-wide alpha value and
	 * enable alpha-blending regardless of the X bit value.
	 */
	अगर (state->क्रमmat->fourcc != DRM_FORMAT_XRGB1555)
		rcar_du_plane_ग_लिखो(rgrp, index, PnALPHAR, PnALPHAR_ABIT_0);
	अन्यथा
		rcar_du_plane_ग_लिखो(rgrp, index, PnALPHAR,
				    PnALPHAR_ABIT_X | state->state.alpha >> 8);

	pnmr = PnMR_BM_MD | state->क्रमmat->pnmr;

	/*
	 * Disable color keying when requested. YUV क्रमmats have the
	 * PnMR_SPIM_TP_OFF bit set in their pnmr field, disabling color keying
	 * स्वतःmatically.
	 */
	अगर ((state->colorkey & RCAR_DU_COLORKEY_MASK) == RCAR_DU_COLORKEY_NONE)
		pnmr |= PnMR_SPIM_TP_OFF;

	/* For packed YUV क्रमmats we need to select the U/V order. */
	अगर (state->क्रमmat->fourcc == DRM_FORMAT_YUYV)
		pnmr |= PnMR_YCDF_YUYV;

	rcar_du_plane_ग_लिखो(rgrp, index, PnMR, pnmr);

	चयन (state->क्रमmat->fourcc) अणु
	हाल DRM_FORMAT_RGB565:
		colorkey = ((state->colorkey & 0xf80000) >> 8)
			 | ((state->colorkey & 0x00fc00) >> 5)
			 | ((state->colorkey & 0x0000f8) >> 3);
		rcar_du_plane_ग_लिखो(rgrp, index, PnTC2R, colorkey);
		अवरोध;

	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		colorkey = ((state->colorkey & 0xf80000) >> 9)
			 | ((state->colorkey & 0x00f800) >> 6)
			 | ((state->colorkey & 0x0000f8) >> 3);
		rcar_du_plane_ग_लिखो(rgrp, index, PnTC2R, colorkey);
		अवरोध;

	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		rcar_du_plane_ग_लिखो(rgrp, index, PnTC3R,
				    PnTC3R_CODE | (state->colorkey & 0xffffff));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rcar_du_plane_setup_क्रमmat_gen2(काष्ठा rcar_du_group *rgrp,
					    अचिन्हित पूर्णांक index,
					    स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	u32 ddcr2 = PnDDCR2_CODE;
	u32 ddcr4;

	/*
	 * Data क्रमmat
	 *
	 * The data क्रमmat is selected by the DDDF field in PnMR and the EDF
	 * field in DDCR4.
	 */

	rcar_du_plane_setup_mode(rgrp, index, state);

	अगर (state->क्रमmat->planes == 2) अणु
		अगर (state->hwindex != index) अणु
			अगर (state->क्रमmat->fourcc == DRM_FORMAT_NV12 ||
			    state->क्रमmat->fourcc == DRM_FORMAT_NV21)
				ddcr2 |= PnDDCR2_Y420;

			अगर (state->क्रमmat->fourcc == DRM_FORMAT_NV21)
				ddcr2 |= PnDDCR2_NV21;

			ddcr2 |= PnDDCR2_DIVU;
		पूर्ण अन्यथा अणु
			ddcr2 |= PnDDCR2_DIVY;
		पूर्ण
	पूर्ण

	rcar_du_plane_ग_लिखो(rgrp, index, PnDDCR2, ddcr2);

	ddcr4 = state->क्रमmat->edf | PnDDCR4_CODE;
	अगर (state->source != RCAR_DU_PLANE_MEMORY)
		ddcr4 |= PnDDCR4_VSPS;

	rcar_du_plane_ग_लिखो(rgrp, index, PnDDCR4, ddcr4);
पूर्ण

अटल व्योम rcar_du_plane_setup_क्रमmat_gen3(काष्ठा rcar_du_group *rgrp,
					    अचिन्हित पूर्णांक index,
					    स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	rcar_du_plane_ग_लिखो(rgrp, index, PnMR,
			    PnMR_SPIM_TP_OFF | state->क्रमmat->pnmr);

	rcar_du_plane_ग_लिखो(rgrp, index, PnDDCR4,
			    state->क्रमmat->edf | PnDDCR4_CODE);
पूर्ण

अटल व्योम rcar_du_plane_setup_क्रमmat(काष्ठा rcar_du_group *rgrp,
				       अचिन्हित पूर्णांक index,
				       स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	स्थिर काष्ठा drm_rect *dst = &state->state.dst;

	अगर (rcdu->info->gen < 3)
		rcar_du_plane_setup_क्रमmat_gen2(rgrp, index, state);
	अन्यथा
		rcar_du_plane_setup_क्रमmat_gen3(rgrp, index, state);

	/* Destination position and size */
	rcar_du_plane_ग_लिखो(rgrp, index, PnDSXR, drm_rect_width(dst));
	rcar_du_plane_ग_लिखो(rgrp, index, PnDSYR, drm_rect_height(dst));
	rcar_du_plane_ग_लिखो(rgrp, index, PnDPXR, dst->x1);
	rcar_du_plane_ग_लिखो(rgrp, index, PnDPYR, dst->y1);

	अगर (rcdu->info->gen < 3) अणु
		/* Wrap-around and blinking, disabled */
		rcar_du_plane_ग_लिखो(rgrp, index, PnWASPR, 0);
		rcar_du_plane_ग_लिखो(rgrp, index, PnWAMWR, 4095);
		rcar_du_plane_ग_लिखो(rgrp, index, PnBTR, 0);
		rcar_du_plane_ग_लिखो(rgrp, index, PnMLR, 0);
	पूर्ण
पूर्ण

व्योम __rcar_du_plane_setup(काष्ठा rcar_du_group *rgrp,
			   स्थिर काष्ठा rcar_du_plane_state *state)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;

	rcar_du_plane_setup_क्रमmat(rgrp, state->hwindex, state);
	अगर (state->क्रमmat->planes == 2)
		rcar_du_plane_setup_क्रमmat(rgrp, (state->hwindex + 1) % 8,
					   state);

	अगर (rcdu->info->gen < 3)
		rcar_du_plane_setup_scanout(rgrp, state);

	अगर (state->source == RCAR_DU_PLANE_VSPD1) अणु
		अचिन्हित पूर्णांक vspd1_sink = rgrp->index ? 2 : 0;

		अगर (rcdu->vspd1_sink != vspd1_sink) अणु
			rcdu->vspd1_sink = vspd1_sink;
			rcar_du_set_dpad0_vsp1_routing(rcdu);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __rcar_du_plane_atomic_check(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *state,
				 स्थिर काष्ठा rcar_du_क्रमmat_info **क्रमmat)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा drm_crtc_state *crtc_state;
	पूर्णांक ret;

	अगर (!state->crtc) अणु
		/*
		 * The visible field is not reset by the DRM core but only
		 * updated by drm_plane_helper_check_state(), set it manually.
		 */
		state->visible = false;
		*क्रमmat = शून्य;
		वापस 0;
	पूर्ण

	crtc_state = drm_atomic_get_crtc_state(state->state, state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	अगर (ret < 0)
		वापस ret;

	अगर (!state->visible) अणु
		*क्रमmat = शून्य;
		वापस 0;
	पूर्ण

	*क्रमmat = rcar_du_क्रमmat_info(state->fb->क्रमmat->क्रमmat);
	अगर (*क्रमmat == शून्य) अणु
		dev_dbg(dev->dev, "%s: unsupported format %08x\n", __func__,
			state->fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_du_plane_atomic_check(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा rcar_du_plane_state *rstate = to_rcar_plane_state(new_plane_state);

	वापस __rcar_du_plane_atomic_check(plane, new_plane_state,
					    &rstate->क्रमmat);
पूर्ण

अटल व्योम rcar_du_plane_atomic_update(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state, plane);
	काष्ठा rcar_du_plane *rplane = to_rcar_plane(plane);
	काष्ठा rcar_du_plane_state *old_rstate;
	काष्ठा rcar_du_plane_state *new_rstate;

	अगर (!new_state->visible)
		वापस;

	rcar_du_plane_setup(rplane);

	/*
	 * Check whether the source has changed from memory to live source or
	 * from live source to memory. The source has been configured by the
	 * VSPS bit in the PnDDCR4 रेजिस्टर. Although the datasheet states that
	 * the bit is updated during vertical blanking, it seems that updates
	 * only occur when the DU group is held in reset through the DSYSR.DRES
	 * bit. We thus need to restart the group अगर the source changes.
	 */
	old_rstate = to_rcar_plane_state(old_state);
	new_rstate = to_rcar_plane_state(new_state);

	अगर ((old_rstate->source == RCAR_DU_PLANE_MEMORY) !=
	    (new_rstate->source == RCAR_DU_PLANE_MEMORY))
		rplane->group->need_restart = true;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs rcar_du_plane_helper_funcs = अणु
	.atomic_check = rcar_du_plane_atomic_check,
	.atomic_update = rcar_du_plane_atomic_update,
पूर्ण;

अटल काष्ठा drm_plane_state *
rcar_du_plane_atomic_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा rcar_du_plane_state *state;
	काष्ठा rcar_du_plane_state *copy;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	state = to_rcar_plane_state(plane->state);
	copy = kmemdup(state, माप(*state), GFP_KERNEL);
	अगर (copy == शून्य)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->state);

	वापस &copy->state;
पूर्ण

अटल व्योम rcar_du_plane_atomic_destroy_state(काष्ठा drm_plane *plane,
					       काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(to_rcar_plane_state(state));
पूर्ण

अटल व्योम rcar_du_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा rcar_du_plane_state *state;

	अगर (plane->state) अणु
		rcar_du_plane_atomic_destroy_state(plane, plane->state);
		plane->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस;

	__drm_atomic_helper_plane_reset(plane, &state->state);

	state->hwindex = -1;
	state->source = RCAR_DU_PLANE_MEMORY;
	state->colorkey = RCAR_DU_COLORKEY_NONE;
	state->state.zpos = plane->type == DRM_PLANE_TYPE_PRIMARY ? 0 : 1;
पूर्ण

अटल पूर्णांक rcar_du_plane_atomic_set_property(काष्ठा drm_plane *plane,
					     काष्ठा drm_plane_state *state,
					     काष्ठा drm_property *property,
					     uपूर्णांक64_t val)
अणु
	काष्ठा rcar_du_plane_state *rstate = to_rcar_plane_state(state);
	काष्ठा rcar_du_device *rcdu = to_rcar_plane(plane)->group->dev;

	अगर (property == rcdu->props.colorkey)
		rstate->colorkey = val;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_du_plane_atomic_get_property(काष्ठा drm_plane *plane,
	स्थिर काष्ठा drm_plane_state *state, काष्ठा drm_property *property,
	uपूर्णांक64_t *val)
अणु
	स्थिर काष्ठा rcar_du_plane_state *rstate =
		container_of(state, स्थिर काष्ठा rcar_du_plane_state, state);
	काष्ठा rcar_du_device *rcdu = to_rcar_plane(plane)->group->dev;

	अगर (property == rcdu->props.colorkey)
		*val = rstate->colorkey;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs rcar_du_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.reset = rcar_du_plane_reset,
	.destroy = drm_plane_cleanup,
	.atomic_duplicate_state = rcar_du_plane_atomic_duplicate_state,
	.atomic_destroy_state = rcar_du_plane_atomic_destroy_state,
	.atomic_set_property = rcar_du_plane_atomic_set_property,
	.atomic_get_property = rcar_du_plane_atomic_get_property,
पूर्ण;

अटल स्थिर uपूर्णांक32_t क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV16,
पूर्ण;

पूर्णांक rcar_du_planes_init(काष्ठा rcar_du_group *rgrp)
अणु
	काष्ठा rcar_du_device *rcdu = rgrp->dev;
	अचिन्हित पूर्णांक crtcs;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	 /*
	  * Create one primary plane per CRTC in this group and seven overlay
	  * planes.
	  */
	rgrp->num_planes = rgrp->num_crtcs + 7;

	crtcs = ((1 << rcdu->num_crtcs) - 1) & (3 << (2 * rgrp->index));

	क्रम (i = 0; i < rgrp->num_planes; ++i) अणु
		क्रमागत drm_plane_type type = i < rgrp->num_crtcs
					 ? DRM_PLANE_TYPE_PRIMARY
					 : DRM_PLANE_TYPE_OVERLAY;
		काष्ठा rcar_du_plane *plane = &rgrp->planes[i];

		plane->group = rgrp;

		ret = drm_universal_plane_init(&rcdu->ddev, &plane->plane,
					       crtcs, &rcar_du_plane_funcs,
					       क्रमmats, ARRAY_SIZE(क्रमmats),
					       शून्य, type, शून्य);
		अगर (ret < 0)
			वापस ret;

		drm_plane_helper_add(&plane->plane,
				     &rcar_du_plane_helper_funcs);

		drm_plane_create_alpha_property(&plane->plane);

		अगर (type == DRM_PLANE_TYPE_PRIMARY) अणु
			drm_plane_create_zpos_immutable_property(&plane->plane,
								 0);
		पूर्ण अन्यथा अणु
			drm_object_attach_property(&plane->plane.base,
						   rcdu->props.colorkey,
						   RCAR_DU_COLORKEY_NONE);
			drm_plane_create_zpos_property(&plane->plane, 1, 1, 7);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
