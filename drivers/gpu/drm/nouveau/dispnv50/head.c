<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#समावेश "head.h"
#समावेश "base.h"
#समावेश "core.h"
#समावेश "curs.h"
#समावेश "ovly.h"
#समावेश "crc.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/cl0046.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश "nouveau_connector.h"

व्योम
nv50_head_flush_clr(काष्ठा nv50_head *head,
		    काष्ठा nv50_head_atom *asyh, bool flush)
अणु
	जोड़ nv50_head_atom_mask clr = अणु
		.mask = asyh->clr.mask & ~(flush ? 0 : asyh->set.mask),
	पूर्ण;
	अगर (clr.crc)  nv50_crc_atomic_clr(head);
	अगर (clr.olut) head->func->olut_clr(head);
	अगर (clr.core) head->func->core_clr(head);
	अगर (clr.curs) head->func->curs_clr(head);
पूर्ण

व्योम
nv50_head_flush_set(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	अगर (asyh->set.view   ) head->func->view    (head, asyh);
	अगर (asyh->set.mode   ) head->func->mode    (head, asyh);
	अगर (asyh->set.core   ) head->func->core_set(head, asyh);
	अगर (asyh->set.olut   ) अणु
		asyh->olut.offset = nv50_lut_load(&head->olut,
						  asyh->olut.buffer,
						  asyh->state.gamma_lut,
						  asyh->olut.load);
		head->func->olut_set(head, asyh);
	पूर्ण
	अगर (asyh->set.curs   ) head->func->curs_set(head, asyh);
	अगर (asyh->set.base   ) head->func->base    (head, asyh);
	अगर (asyh->set.ovly   ) head->func->ovly    (head, asyh);
	अगर (asyh->set.dither ) head->func->dither  (head, asyh);
	अगर (asyh->set.procamp) head->func->procamp (head, asyh);
	अगर (asyh->set.crc    ) nv50_crc_atomic_set (head, asyh);
	अगर (asyh->set.or     ) head->func->or      (head, asyh);
पूर्ण

अटल व्योम
nv50_head_atomic_check_procamp(काष्ठा nv50_head_atom *armh,
			       काष्ठा nv50_head_atom *asyh,
			       काष्ठा nouveau_conn_atom *asyc)
अणु
	स्थिर पूर्णांक vib = asyc->procamp.color_vibrance - 100;
	स्थिर पूर्णांक hue = asyc->procamp.vibrant_hue - 90;
	स्थिर पूर्णांक adj = (vib > 0) ? 50 : 0;
	asyh->procamp.sat.cos = ((vib * 2047 + adj) / 100) & 0xfff;
	asyh->procamp.sat.sin = ((hue * 2047) / 100) & 0xfff;
	asyh->set.procamp = true;
पूर्ण

अटल व्योम
nv50_head_atomic_check_dither(काष्ठा nv50_head_atom *armh,
			      काष्ठा nv50_head_atom *asyh,
			      काष्ठा nouveau_conn_atom *asyc)
अणु
	u32 mode = 0x00;

	अगर (asyc->dither.mode) अणु
		अगर (asyc->dither.mode == DITHERING_MODE_AUTO) अणु
			अगर (asyh->base.depth > asyh->or.bpc * 3)
				mode = DITHERING_MODE_DYNAMIC2X2;
		पूर्ण अन्यथा अणु
			mode = asyc->dither.mode;
		पूर्ण

		अगर (asyc->dither.depth == DITHERING_DEPTH_AUTO) अणु
			अगर (asyh->or.bpc >= 8)
				mode |= DITHERING_DEPTH_8BPC;
		पूर्ण अन्यथा अणु
			mode |= asyc->dither.depth;
		पूर्ण
	पूर्ण

	asyh->dither.enable = NVVAL_GET(mode, NV507D, HEAD_SET_DITHER_CONTROL, ENABLE);
	asyh->dither.bits = NVVAL_GET(mode, NV507D, HEAD_SET_DITHER_CONTROL, BITS);
	asyh->dither.mode = NVVAL_GET(mode, NV507D, HEAD_SET_DITHER_CONTROL, MODE);
	asyh->set.dither = true;
पूर्ण

अटल व्योम
nv50_head_atomic_check_view(काष्ठा nv50_head_atom *armh,
			    काष्ठा nv50_head_atom *asyh,
			    काष्ठा nouveau_conn_atom *asyc)
अणु
	काष्ठा drm_connector *connector = asyc->state.connector;
	काष्ठा drm_display_mode *omode = &asyh->state.adjusted_mode;
	काष्ठा drm_display_mode *umode = &asyh->state.mode;
	पूर्णांक mode = asyc->scaler.mode;
	काष्ठा edid *edid;
	पूर्णांक umode_vdisplay, omode_hdisplay, omode_vdisplay;

	अगर (connector->edid_blob_ptr)
		edid = (काष्ठा edid *)connector->edid_blob_ptr->data;
	अन्यथा
		edid = शून्य;

	अगर (!asyc->scaler.full) अणु
		अगर (mode == DRM_MODE_SCALE_NONE)
			omode = umode;
	पूर्ण अन्यथा अणु
		/* Non-EDID LVDS/eDP mode. */
		mode = DRM_MODE_SCALE_FULLSCREEN;
	पूर्ण

	/* For the user-specअगरied mode, we must ignore द्विगुनscan and
	 * the like, but honor frame packing.
	 */
	umode_vdisplay = umode->vdisplay;
	अगर ((umode->flags & DRM_MODE_FLAG_3D_MASK) == DRM_MODE_FLAG_3D_FRAME_PACKING)
		umode_vdisplay += umode->vtotal;
	asyh->view.iW = umode->hdisplay;
	asyh->view.iH = umode_vdisplay;
	/* For the output mode, we can just use the stock helper. */
	drm_mode_get_hv_timing(omode, &omode_hdisplay, &omode_vdisplay);
	asyh->view.oW = omode_hdisplay;
	asyh->view.oH = omode_vdisplay;

	/* Add overscan compensation अगर necessary, will keep the aspect
	 * ratio the same as the backend mode unless overridden by the
	 * user setting both hborder and vborder properties.
	 */
	अगर ((asyc->scaler.underscan.mode == UNDERSCAN_ON ||
	    (asyc->scaler.underscan.mode == UNDERSCAN_AUTO &&
	     drm_detect_hdmi_monitor(edid)))) अणु
		u32 bX = asyc->scaler.underscan.hborder;
		u32 bY = asyc->scaler.underscan.vborder;
		u32 r = (asyh->view.oH << 19) / asyh->view.oW;

		अगर (bX) अणु
			asyh->view.oW -= (bX * 2);
			अगर (bY) asyh->view.oH -= (bY * 2);
			अन्यथा    asyh->view.oH  = ((asyh->view.oW * r) + (r / 2)) >> 19;
		पूर्ण अन्यथा अणु
			asyh->view.oW -= (asyh->view.oW >> 4) + 32;
			अगर (bY) asyh->view.oH -= (bY * 2);
			अन्यथा    asyh->view.oH  = ((asyh->view.oW * r) + (r / 2)) >> 19;
		पूर्ण
	पूर्ण

	/* Handle CENTER/ASPECT scaling, taking पूर्णांकo account the areas
	 * हटाओd alपढ़ोy क्रम overscan compensation.
	 */
	चयन (mode) अणु
	हाल DRM_MODE_SCALE_CENTER:
		/* NOTE: This will cause scaling when the input is
		 * larger than the output.
		 */
		asyh->view.oW = min(asyh->view.iW, asyh->view.oW);
		asyh->view.oH = min(asyh->view.iH, asyh->view.oH);
		अवरोध;
	हाल DRM_MODE_SCALE_ASPECT:
		/* Determine whether the scaling should be on width or on
		 * height. This is करोne by comparing the aspect ratios of the
		 * sizes. If the output AR is larger than input AR, that means
		 * we want to change the width (letterboxed on the
		 * left/right), otherwise on the height (letterboxed on the
		 * top/bottom).
		 *
		 * E.g. 4:3 (1.333) AR image displayed on a 16:10 (1.6) AR
		 * screen will have letterboxes on the left/right. However a
		 * 16:9 (1.777) AR image on that same screen will have
		 * letterboxes on the top/bottom.
		 *
		 * inputAR = iW / iH; outputAR = oW / oH
		 * outputAR > inputAR is equivalent to oW * iH > iW * oH
		 */
		अगर (asyh->view.oW * asyh->view.iH > asyh->view.iW * asyh->view.oH) अणु
			/* Recompute output width, i.e. left/right letterbox */
			u32 r = (asyh->view.iW << 19) / asyh->view.iH;
			asyh->view.oW = ((asyh->view.oH * r) + (r / 2)) >> 19;
		पूर्ण अन्यथा अणु
			/* Recompute output height, i.e. top/bottom letterbox */
			u32 r = (asyh->view.iH << 19) / asyh->view.iW;
			asyh->view.oH = ((asyh->view.oW * r) + (r / 2)) >> 19;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	asyh->set.view = true;
पूर्ण

अटल पूर्णांक
nv50_head_atomic_check_lut(काष्ठा nv50_head *head,
			   काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(head->base.base.dev);
	काष्ठा drm_property_blob *olut = asyh->state.gamma_lut;
	पूर्णांक size;

	/* Determine whether core output LUT should be enabled. */
	अगर (olut) अणु
		/* Check अगर any winकरोw(s) have stolen the core output LUT
		 * to as an input LUT क्रम legacy gamma + I8 colour क्रमmat.
		 */
		अगर (asyh->wndw.olut) अणु
			/* If any winकरोw has stolen the core output LUT,
			 * all of them must.
			 */
			अगर (asyh->wndw.olut != asyh->wndw.mask)
				वापस -EINVAL;
			olut = शून्य;
		पूर्ण
	पूर्ण

	अगर (!olut) अणु
		अगर (!head->func->olut_identity) अणु
			asyh->olut.handle = 0;
			वापस 0;
		पूर्ण
		size = 0;
	पूर्ण अन्यथा अणु
		size = drm_color_lut_size(olut);
	पूर्ण

	अगर (!head->func->olut(head, asyh, size)) अणु
		DRM_DEBUG_KMS("Invalid olut\n");
		वापस -EINVAL;
	पूर्ण
	asyh->olut.handle = disp->core->chan.vram.handle;
	asyh->olut.buffer = !asyh->olut.buffer;

	वापस 0;
पूर्ण

अटल व्योम
nv50_head_atomic_check_mode(काष्ठा nv50_head *head, काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा drm_display_mode *mode = &asyh->state.adjusted_mode;
	काष्ठा nv50_head_mode *m = &asyh->mode;
	u32 blankus;

	drm_mode_set_crtcinfo(mode, CRTC_INTERLACE_HALVE_V | CRTC_STEREO_DOUBLE);

	/*
	 * DRM modes are defined in terms of a repeating पूर्णांकerval
	 * starting with the active display area.  The hardware modes
	 * are defined in terms of a repeating पूर्णांकerval starting one
	 * unit (pixel or line) पूर्णांकo the sync pulse.  So, add bias.
	 */

	m->h.active = mode->crtc_htotal;
	m->h.synce  = mode->crtc_hsync_end - mode->crtc_hsync_start - 1;
	m->h.blanke = mode->crtc_hblank_end - mode->crtc_hsync_start - 1;
	m->h.blanks = m->h.blanke + mode->crtc_hdisplay;

	m->v.active = mode->crtc_vtotal;
	m->v.synce  = mode->crtc_vsync_end - mode->crtc_vsync_start - 1;
	m->v.blanke = mode->crtc_vblank_end - mode->crtc_vsync_start - 1;
	m->v.blanks = m->v.blanke + mode->crtc_vdisplay;

	/*XXX: Safe underestimate, even "0" works */
	blankus = (m->v.active - mode->crtc_vdisplay - 2) * m->h.active;
	blankus *= 1000;
	blankus /= mode->crtc_घड़ी;
	m->v.blankus = blankus;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		m->v.blank2e =  m->v.active + m->v.blanke;
		m->v.blank2s =  m->v.blank2e + mode->crtc_vdisplay;
		m->v.active  = (m->v.active * 2) + 1;
		m->पूर्णांकerlace = true;
	पूर्ण अन्यथा अणु
		m->v.blank2e = 0;
		m->v.blank2s = 1;
		m->पूर्णांकerlace = false;
	पूर्ण
	m->घड़ी = mode->crtc_घड़ी;

	asyh->or.nhsync = !!(mode->flags & DRM_MODE_FLAG_NHSYNC);
	asyh->or.nvsync = !!(mode->flags & DRM_MODE_FLAG_NVSYNC);
	asyh->set.or = head->func->or != शून्य;
	asyh->set.mode = true;
पूर्ण

अटल पूर्णांक
nv50_head_atomic_check(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state = drm_atomic_get_old_crtc_state(state,
									      crtc);
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा nouveau_drm *drm = nouveau_drm(crtc->dev);
	काष्ठा nv50_head *head = nv50_head(crtc);
	काष्ठा nv50_head_atom *armh = nv50_head_atom(old_crtc_state);
	काष्ठा nv50_head_atom *asyh = nv50_head_atom(crtc_state);
	काष्ठा nouveau_conn_atom *asyc = शून्य;
	काष्ठा drm_connector_state *conns;
	काष्ठा drm_connector *conn;
	पूर्णांक i, ret;

	NV_ATOMIC(drm, "%s atomic_check %d\n", crtc->name, asyh->state.active);
	अगर (asyh->state.active) अणु
		क्रम_each_new_connector_in_state(asyh->state.state, conn, conns, i) अणु
			अगर (conns->crtc == crtc) अणु
				asyc = nouveau_conn_atom(conns);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (armh->state.active) अणु
			अगर (asyc) अणु
				अगर (asyh->state.mode_changed)
					asyc->set.scaler = true;
				अगर (armh->base.depth != asyh->base.depth)
					asyc->set.dither = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (asyc)
				asyc->set.mask = ~0;
			asyh->set.mask = ~0;
			asyh->set.or = head->func->or != शून्य;
		पूर्ण

		अगर (asyh->state.mode_changed || asyh->state.connectors_changed)
			nv50_head_atomic_check_mode(head, asyh);

		अगर (asyh->state.color_mgmt_changed ||
		    स_भेद(&armh->wndw, &asyh->wndw, माप(asyh->wndw))) अणु
			पूर्णांक ret = nv50_head_atomic_check_lut(head, asyh);
			अगर (ret)
				वापस ret;

			asyh->olut.visible = asyh->olut.handle != 0;
		पूर्ण

		अगर (asyc) अणु
			अगर (asyc->set.scaler)
				nv50_head_atomic_check_view(armh, asyh, asyc);
			अगर (asyc->set.dither)
				nv50_head_atomic_check_dither(armh, asyh, asyc);
			अगर (asyc->set.procamp)
				nv50_head_atomic_check_procamp(armh, asyh, asyc);
		पूर्ण

		अगर (head->func->core_calc) अणु
			head->func->core_calc(head, asyh);
			अगर (!asyh->core.visible)
				asyh->olut.visible = false;
		पूर्ण

		asyh->set.base = armh->base.cpp != asyh->base.cpp;
		asyh->set.ovly = armh->ovly.cpp != asyh->ovly.cpp;
	पूर्ण अन्यथा अणु
		asyh->olut.visible = false;
		asyh->core.visible = false;
		asyh->curs.visible = false;
		asyh->base.cpp = 0;
		asyh->ovly.cpp = 0;
	पूर्ण

	अगर (!drm_atomic_crtc_needs_modeset(&asyh->state)) अणु
		अगर (asyh->core.visible) अणु
			अगर (स_भेद(&armh->core, &asyh->core, माप(asyh->core)))
				asyh->set.core = true;
		पूर्ण अन्यथा
		अगर (armh->core.visible) अणु
			asyh->clr.core = true;
		पूर्ण

		अगर (asyh->curs.visible) अणु
			अगर (स_भेद(&armh->curs, &asyh->curs, माप(asyh->curs)))
				asyh->set.curs = true;
		पूर्ण अन्यथा
		अगर (armh->curs.visible) अणु
			asyh->clr.curs = true;
		पूर्ण

		अगर (asyh->olut.visible) अणु
			अगर (स_भेद(&armh->olut, &asyh->olut, माप(asyh->olut)))
				asyh->set.olut = true;
		पूर्ण अन्यथा
		अगर (armh->olut.visible) अणु
			asyh->clr.olut = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		asyh->clr.olut = armh->olut.visible;
		asyh->clr.core = armh->core.visible;
		asyh->clr.curs = armh->curs.visible;
		asyh->set.olut = asyh->olut.visible;
		asyh->set.core = asyh->core.visible;
		asyh->set.curs = asyh->curs.visible;
	पूर्ण

	ret = nv50_crc_atomic_check_head(head, asyh, armh);
	अगर (ret)
		वापस ret;

	अगर (asyh->clr.mask || asyh->set.mask)
		nv50_atom(asyh->state.state)->lock_core = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs
nv50_head_help = अणु
	.atomic_check = nv50_head_atomic_check,
	.get_scanout_position = nouveau_display_scanoutpos,
पूर्ण;

अटल व्योम
nv50_head_atomic_destroy_state(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_crtc_state *state)
अणु
	काष्ठा nv50_head_atom *asyh = nv50_head_atom(state);
	__drm_atomic_helper_crtc_destroy_state(&asyh->state);
	kमुक्त(asyh);
पूर्ण

अटल काष्ठा drm_crtc_state *
nv50_head_atomic_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nv50_head_atom *armh = nv50_head_atom(crtc->state);
	काष्ठा nv50_head_atom *asyh;
	अगर (!(asyh = kदो_स्मृति(माप(*asyh), GFP_KERNEL)))
		वापस शून्य;
	__drm_atomic_helper_crtc_duplicate_state(crtc, &asyh->state);
	asyh->wndw = armh->wndw;
	asyh->view = armh->view;
	asyh->mode = armh->mode;
	asyh->olut = armh->olut;
	asyh->core = armh->core;
	asyh->curs = armh->curs;
	asyh->base = armh->base;
	asyh->ovly = armh->ovly;
	asyh->dither = armh->dither;
	asyh->procamp = armh->procamp;
	asyh->crc = armh->crc;
	asyh->or = armh->or;
	asyh->dp = armh->dp;
	asyh->clr.mask = 0;
	asyh->set.mask = 0;
	वापस &asyh->state;
पूर्ण

अटल व्योम
nv50_head_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nv50_head_atom *asyh;

	अगर (WARN_ON(!(asyh = kzalloc(माप(*asyh), GFP_KERNEL))))
		वापस;

	अगर (crtc->state)
		nv50_head_atomic_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &asyh->state);
पूर्ण

अटल पूर्णांक
nv50_head_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	वापस nv50_head_crc_late_रेजिस्टर(nv50_head(crtc));
पूर्ण

अटल व्योम
nv50_head_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nv50_head *head = nv50_head(crtc);

	nvअगर_notअगरy_dtor(&head->base.vblank);
	nv50_lut_fini(&head->olut);
	drm_crtc_cleanup(crtc);
	kमुक्त(head);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs
nv50_head_func = अणु
	.reset = nv50_head_reset,
	.destroy = nv50_head_destroy,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = nv50_head_atomic_duplicate_state,
	.atomic_destroy_state = nv50_head_atomic_destroy_state,
	.enable_vblank = nouveau_display_vblank_enable,
	.disable_vblank = nouveau_display_vblank_disable,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
	.late_रेजिस्टर = nv50_head_late_रेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs
nvd9_head_func = अणु
	.reset = nv50_head_reset,
	.destroy = nv50_head_destroy,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = nv50_head_atomic_duplicate_state,
	.atomic_destroy_state = nv50_head_atomic_destroy_state,
	.enable_vblank = nouveau_display_vblank_enable,
	.disable_vblank = nouveau_display_vblank_disable,
	.get_vblank_बारtamp = drm_crtc_vblank_helper_get_vblank_बारtamp,
	.verअगरy_crc_source = nv50_crc_verअगरy_source,
	.get_crc_sources = nv50_crc_get_sources,
	.set_crc_source = nv50_crc_set_source,
	.late_रेजिस्टर = nv50_head_late_रेजिस्टर,
पूर्ण;

अटल पूर्णांक nv50_head_vblank_handler(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	काष्ठा nouveau_crtc *nv_crtc =
		container_of(notअगरy, काष्ठा nouveau_crtc, vblank);

	अगर (drm_crtc_handle_vblank(&nv_crtc->base))
		nv50_crc_handle_vblank(nv50_head(&nv_crtc->base));

	वापस NVIF_NOTIFY_KEEP;
पूर्ण

काष्ठा nv50_head *
nv50_head_create(काष्ठा drm_device *dev, पूर्णांक index)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	काष्ठा nv50_head *head;
	काष्ठा nv50_wndw *base, *ovly, *curs;
	काष्ठा nouveau_crtc *nv_crtc;
	काष्ठा drm_crtc *crtc;
	स्थिर काष्ठा drm_crtc_funcs *funcs;
	पूर्णांक ret;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (!head)
		वापस ERR_PTR(-ENOMEM);

	head->func = disp->core->func->head;
	head->base.index = index;

	अगर (disp->disp->object.oclass < GF110_DISP)
		funcs = &nv50_head_func;
	अन्यथा
		funcs = &nvd9_head_func;

	अगर (disp->disp->object.oclass < GV100_DISP) अणु
		ret = nv50_base_new(drm, head->base.index, &base);
		ret = nv50_ovly_new(drm, head->base.index, &ovly);
	पूर्ण अन्यथा अणु
		ret = nv50_wndw_new(drm, DRM_PLANE_TYPE_PRIMARY,
				    head->base.index * 2 + 0, &base);
		ret = nv50_wndw_new(drm, DRM_PLANE_TYPE_OVERLAY,
				    head->base.index * 2 + 1, &ovly);
	पूर्ण
	अगर (ret == 0)
		ret = nv50_curs_new(drm, head->base.index, &curs);
	अगर (ret) अणु
		kमुक्त(head);
		वापस ERR_PTR(ret);
	पूर्ण

	nv_crtc = &head->base;
	crtc = &nv_crtc->base;
	drm_crtc_init_with_planes(dev, crtc, &base->plane, &curs->plane,
				  funcs, "head-%d", head->base.index);
	drm_crtc_helper_add(crtc, &nv50_head_help);
	/* Keep the legacy gamma size at 256 to aव्योम compatibility issues */
	drm_mode_crtc_set_gamma_size(crtc, 256);
	drm_crtc_enable_color_mgmt(crtc, base->func->ilut_size,
				   disp->disp->object.oclass >= GF110_DISP,
				   head->func->olut_size);

	अगर (head->func->olut_set) अणु
		ret = nv50_lut_init(disp, &drm->client.mmu, &head->olut);
		अगर (ret) अणु
			nv50_head_destroy(crtc);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	ret = nvअगर_notअगरy_ctor(&disp->disp->object, "kmsVbl", nv50_head_vblank_handler,
			       false, NV04_DISP_NTFY_VBLANK,
			       &(काष्ठा nvअगर_notअगरy_head_req_v0) अणु
				    .head = nv_crtc->index,
			       पूर्ण,
			       माप(काष्ठा nvअगर_notअगरy_head_req_v0),
			       माप(काष्ठा nvअगर_notअगरy_head_rep_v0),
			       &nv_crtc->vblank);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस head;
पूर्ण
