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
#समावेश "wndw.h"
#समावेश "wimm.h"
#समावेश "handles.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>

#समावेश <nvhw/class/cl507c.h>
#समावेश <nvhw/class/cl507e.h>
#समावेश <nvhw/class/clc37e.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "nouveau_bo.h"
#समावेश "nouveau_gem.h"

अटल व्योम
nv50_wndw_ctxdma_del(काष्ठा nv50_wndw_ctxdma *ctxdma)
अणु
	nvअगर_object_dtor(&ctxdma->object);
	list_del(&ctxdma->head);
	kमुक्त(ctxdma);
पूर्ण

अटल काष्ठा nv50_wndw_ctxdma *
nv50_wndw_ctxdma_new(काष्ठा nv50_wndw *wndw, काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(fb->dev);
	काष्ठा nv50_wndw_ctxdma *ctxdma;
	u32 handle;
	u32 unused;
	u8  kind;
	काष्ठा अणु
		काष्ठा nv_dma_v0 base;
		जोड़ अणु
			काष्ठा nv50_dma_v0 nv50;
			काष्ठा gf100_dma_v0 gf100;
			काष्ठा gf119_dma_v0 gf119;
		पूर्ण;
	पूर्ण args = अणुपूर्ण;
	u32 argc = माप(args.base);
	पूर्णांक ret;

	nouveau_framebuffer_get_layout(fb, &unused, &kind);
	handle = NV50_DISP_HANDLE_WNDW_CTX(kind);

	list_क्रम_each_entry(ctxdma, &wndw->ctxdma.list, head) अणु
		अगर (ctxdma->object.handle == handle)
			वापस ctxdma;
	पूर्ण

	अगर (!(ctxdma = kzalloc(माप(*ctxdma), GFP_KERNEL)))
		वापस ERR_PTR(-ENOMEM);
	list_add(&ctxdma->head, &wndw->ctxdma.list);

	args.base.target = NV_DMA_V0_TARGET_VRAM;
	args.base.access = NV_DMA_V0_ACCESS_RDWR;
	args.base.start  = 0;
	args.base.limit  = drm->client.device.info.ram_user - 1;

	अगर (drm->client.device.info.chipset < 0x80) अणु
		args.nv50.part = NV50_DMA_V0_PART_256;
		argc += माप(args.nv50);
	पूर्ण अन्यथा
	अगर (drm->client.device.info.chipset < 0xc0) अणु
		args.nv50.part = NV50_DMA_V0_PART_256;
		args.nv50.kind = kind;
		argc += माप(args.nv50);
	पूर्ण अन्यथा
	अगर (drm->client.device.info.chipset < 0xd0) अणु
		args.gf100.kind = kind;
		argc += माप(args.gf100);
	पूर्ण अन्यथा अणु
		args.gf119.page = GF119_DMA_V0_PAGE_LP;
		args.gf119.kind = kind;
		argc += माप(args.gf119);
	पूर्ण

	ret = nvअगर_object_ctor(wndw->ctxdma.parent, "kmsFbCtxDma", handle,
			       NV_DMA_IN_MEMORY, &args, argc, &ctxdma->object);
	अगर (ret) अणु
		nv50_wndw_ctxdma_del(ctxdma);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ctxdma;
पूर्ण

पूर्णांक
nv50_wndw_रुको_armed(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(wndw->plane.dev);
	अगर (asyw->set.ntfy) अणु
		वापस wndw->func->ntfy_रुको_begun(disp->sync,
						   asyw->ntfy.offset,
						   wndw->wndw.base.device);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
nv50_wndw_flush_clr(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock, bool flush,
		    काष्ठा nv50_wndw_atom *asyw)
अणु
	जोड़ nv50_wndw_atom_mask clr = अणु
		.mask = asyw->clr.mask & ~(flush ? 0 : asyw->set.mask),
	पूर्ण;
	अगर (clr.sema ) wndw->func-> sema_clr(wndw);
	अगर (clr.ntfy ) wndw->func-> ntfy_clr(wndw);
	अगर (clr.xlut ) wndw->func-> xlut_clr(wndw);
	अगर (clr.csc  ) wndw->func->  csc_clr(wndw);
	अगर (clr.image) wndw->func->image_clr(wndw);

	पूर्णांकerlock[wndw->पूर्णांकerlock.type] |= wndw->पूर्णांकerlock.data;
पूर्ण

व्योम
nv50_wndw_flush_set(काष्ठा nv50_wndw *wndw, u32 *पूर्णांकerlock,
		    काष्ठा nv50_wndw_atom *asyw)
अणु
	अगर (पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE]) अणु
		asyw->image.mode = NV507C_SET_PRESENT_CONTROL_BEGIN_MODE_NON_TEARING;
		asyw->image.पूर्णांकerval = 1;
	पूर्ण

	अगर (asyw->set.sema ) wndw->func->sema_set (wndw, asyw);
	अगर (asyw->set.ntfy ) wndw->func->ntfy_set (wndw, asyw);
	अगर (asyw->set.image) wndw->func->image_set(wndw, asyw);

	अगर (asyw->set.xlut ) अणु
		अगर (asyw->ilut) अणु
			asyw->xlut.i.offset =
				nv50_lut_load(&wndw->ilut, asyw->xlut.i.buffer,
					      asyw->ilut, asyw->xlut.i.load);
		पूर्ण
		wndw->func->xlut_set(wndw, asyw);
	पूर्ण

	अगर (asyw->set.csc  ) wndw->func->csc_set  (wndw, asyw);
	अगर (asyw->set.scale) wndw->func->scale_set(wndw, asyw);
	अगर (asyw->set.blend) wndw->func->blend_set(wndw, asyw);
	अगर (asyw->set.poपूर्णांक) अणु
		अगर (asyw->set.poपूर्णांक = false, asyw->set.mask)
			पूर्णांकerlock[wndw->पूर्णांकerlock.type] |= wndw->पूर्णांकerlock.data;
		पूर्णांकerlock[NV50_DISP_INTERLOCK_WIMM] |= wndw->पूर्णांकerlock.wimm;

		wndw->immd->poपूर्णांक(wndw, asyw);
		wndw->immd->update(wndw, पूर्णांकerlock);
	पूर्ण अन्यथा अणु
		पूर्णांकerlock[wndw->पूर्णांकerlock.type] |= wndw->पूर्णांकerlock.data;
	पूर्ण
पूर्ण

व्योम
nv50_wndw_ntfy_enable(काष्ठा nv50_wndw *wndw, काष्ठा nv50_wndw_atom *asyw)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(wndw->plane.dev);

	asyw->ntfy.handle = wndw->wndw.sync.handle;
	asyw->ntfy.offset = wndw->ntfy;
	asyw->ntfy.awaken = false;
	asyw->set.ntfy = true;

	wndw->func->ntfy_reset(disp->sync, wndw->ntfy);
	wndw->ntfy ^= 0x10;
पूर्ण

अटल व्योम
nv50_wndw_atomic_check_release(काष्ठा nv50_wndw *wndw,
			       काष्ठा nv50_wndw_atom *asyw,
			       काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(wndw->plane.dev);
	NV_ATOMIC(drm, "%s release\n", wndw->plane.name);
	wndw->func->release(wndw, asyw, asyh);
	asyw->ntfy.handle = 0;
	asyw->sema.handle = 0;
	asyw->xlut.handle = 0;
	स_रखो(asyw->image.handle, 0x00, माप(asyw->image.handle));
पूर्ण

अटल पूर्णांक
nv50_wndw_atomic_check_acquire_yuv(काष्ठा nv50_wndw_atom *asyw)
अणु
	चयन (asyw->state.fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_YUYV:
		asyw->image.क्रमmat = NV507E_SURFACE_SET_PARAMS_FORMAT_VE8YO8UE8YE8;
		अवरोध;
	हाल DRM_FORMAT_UYVY:
		asyw->image.क्रमmat = NV507E_SURFACE_SET_PARAMS_FORMAT_YO8VE8YE8UE8;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	asyw->image.colorspace = NV507E_SURFACE_SET_PARAMS_COLOR_SPACE_YUV_601;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_wndw_atomic_check_acquire_rgb(काष्ठा nv50_wndw_atom *asyw)
अणु
	चयन (asyw->state.fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_I8;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_A8R8G8B8;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_R5G6B5;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_A1R5G5B5;
		अवरोध;
	हाल DRM_FORMAT_XBGR2101010:
	हाल DRM_FORMAT_ABGR2101010:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_A2B10G10R10;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_ABGR8888:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_A8B8G8R8;
		अवरोध;
	हाल DRM_FORMAT_XRGB2101010:
	हाल DRM_FORMAT_ARGB2101010:
		asyw->image.क्रमmat = NVC37E_SET_PARAMS_FORMAT_A2R10G10B10;
		अवरोध;
	हाल DRM_FORMAT_XBGR16161616F:
	हाल DRM_FORMAT_ABGR16161616F:
		asyw->image.क्रमmat = NV507C_SURFACE_SET_PARAMS_FORMAT_RF16_GF16_BF16_AF16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	asyw->image.colorspace = NV507E_SURFACE_SET_PARAMS_COLOR_SPACE_RGB;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_wndw_atomic_check_acquire(काष्ठा nv50_wndw *wndw, bool modeset,
			       काष्ठा nv50_wndw_atom *armw,
			       काष्ठा nv50_wndw_atom *asyw,
			       काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा drm_framebuffer *fb = asyw->state.fb;
	काष्ठा nouveau_drm *drm = nouveau_drm(wndw->plane.dev);
	uपूर्णांक8_t kind;
	uपूर्णांक32_t tile_mode;
	पूर्णांक ret;

	NV_ATOMIC(drm, "%s acquire\n", wndw->plane.name);

	अगर (fb != armw->state.fb || !armw->visible || modeset) अणु
		nouveau_framebuffer_get_layout(fb, &tile_mode, &kind);

		asyw->image.w = fb->width;
		asyw->image.h = fb->height;
		asyw->image.kind = kind;

		ret = nv50_wndw_atomic_check_acquire_rgb(asyw);
		अगर (ret) अणु
			ret = nv50_wndw_atomic_check_acquire_yuv(asyw);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (asyw->image.kind) अणु
			asyw->image.layout = NV507C_SURFACE_SET_STORAGE_MEMORY_LAYOUT_BLOCKLINEAR;
			अगर (drm->client.device.info.chipset >= 0xc0)
				asyw->image.blockh = tile_mode >> 4;
			अन्यथा
				asyw->image.blockh = tile_mode;
			asyw->image.blocks[0] = fb->pitches[0] / 64;
			asyw->image.pitch[0] = 0;
		पूर्ण अन्यथा अणु
			asyw->image.layout = NV507C_SURFACE_SET_STORAGE_MEMORY_LAYOUT_PITCH;
			asyw->image.blockh = NV507C_SURFACE_SET_STORAGE_BLOCK_HEIGHT_ONE_GOB;
			asyw->image.blocks[0] = 0;
			asyw->image.pitch[0] = fb->pitches[0];
		पूर्ण

		अगर (!asyh->state.async_flip)
			asyw->image.पूर्णांकerval = 1;
		अन्यथा
			asyw->image.पूर्णांकerval = 0;

		अगर (asyw->image.पूर्णांकerval)
			asyw->image.mode = NV507C_SET_PRESENT_CONTROL_BEGIN_MODE_NON_TEARING;
		अन्यथा
			asyw->image.mode = NV507C_SET_PRESENT_CONTROL_BEGIN_MODE_IMMEDIATE;

		asyw->set.image = wndw->func->image_set != शून्य;
	पूर्ण

	अगर (wndw->func->scale_set) अणु
		asyw->scale.sx = asyw->state.src_x >> 16;
		asyw->scale.sy = asyw->state.src_y >> 16;
		asyw->scale.sw = asyw->state.src_w >> 16;
		asyw->scale.sh = asyw->state.src_h >> 16;
		asyw->scale.dw = asyw->state.crtc_w;
		asyw->scale.dh = asyw->state.crtc_h;
		अगर (स_भेद(&armw->scale, &asyw->scale, माप(asyw->scale)))
			asyw->set.scale = true;
	पूर्ण

	अगर (wndw->func->blend_set) अणु
		asyw->blend.depth = 255 - asyw->state.normalized_zpos;
		asyw->blend.k1 = asyw->state.alpha >> 8;
		चयन (asyw->state.pixel_blend_mode) अणु
		हाल DRM_MODE_BLEND_PREMULTI:
			asyw->blend.src_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_SRC_COLOR_FACTOR_MATCH_SELECT_K1;
			asyw->blend.dst_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_DST_COLOR_FACTOR_MATCH_SELECT_NEG_K1_TIMES_SRC;
			अवरोध;
		हाल DRM_MODE_BLEND_COVERAGE:
			asyw->blend.src_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_SRC_COLOR_FACTOR_MATCH_SELECT_K1_TIMES_SRC;
			asyw->blend.dst_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_DST_COLOR_FACTOR_MATCH_SELECT_NEG_K1_TIMES_SRC;
			अवरोध;
		हाल DRM_MODE_BLEND_PIXEL_NONE:
		शेष:
			asyw->blend.src_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_SRC_COLOR_FACTOR_MATCH_SELECT_K1;
			asyw->blend.dst_color = NVC37E_SET_COMPOSITION_FACTOR_SELECT_DST_COLOR_FACTOR_MATCH_SELECT_NEG_K1;
			अवरोध;
		पूर्ण
		अगर (स_भेद(&armw->blend, &asyw->blend, माप(asyw->blend)))
			asyw->set.blend = true;
	पूर्ण

	अगर (wndw->immd) अणु
		asyw->poपूर्णांक.x = asyw->state.crtc_x;
		asyw->poपूर्णांक.y = asyw->state.crtc_y;
		अगर (स_भेद(&armw->poपूर्णांक, &asyw->poपूर्णांक, माप(asyw->poपूर्णांक)))
			asyw->set.poपूर्णांक = true;
	पूर्ण

	वापस wndw->func->acquire(wndw, asyw, asyh);
पूर्ण

अटल पूर्णांक
nv50_wndw_atomic_check_lut(काष्ठा nv50_wndw *wndw,
			   काष्ठा nv50_wndw_atom *armw,
			   काष्ठा nv50_wndw_atom *asyw,
			   काष्ठा nv50_head_atom *asyh)
अणु
	काष्ठा drm_property_blob *ilut = asyh->state.degamma_lut;

	/* I8 क्रमmat without an input LUT makes no sense, and the
	 * HW error-checks क्रम this.
	 *
	 * In order to handle legacy gamma, when there's no input
	 * LUT we need to steal the output LUT and use it instead.
	 */
	अगर (!ilut && asyw->state.fb->क्रमmat->क्रमmat == DRM_FORMAT_C8) अणु
		/* This should be an error, but there's legacy clients
		 * that करो a modeset beक्रमe providing a gamma table.
		 *
		 * We keep the winकरोw disabled to aव्योम angering HW.
		 */
		अगर (!(ilut = asyh->state.gamma_lut)) अणु
			asyw->visible = false;
			वापस 0;
		पूर्ण

		अगर (wndw->func->ilut)
			asyh->wndw.olut |= BIT(wndw->id);
	पूर्ण अन्यथा अणु
		asyh->wndw.olut &= ~BIT(wndw->id);
	पूर्ण

	अगर (!ilut && wndw->func->ilut_identity &&
	    asyw->state.fb->क्रमmat->क्रमmat != DRM_FORMAT_XBGR16161616F &&
	    asyw->state.fb->क्रमmat->क्रमmat != DRM_FORMAT_ABGR16161616F) अणु
		अटल काष्ठा drm_property_blob dummy = अणुपूर्ण;
		ilut = &dummy;
	पूर्ण

	/* Recalculate LUT state. */
	स_रखो(&asyw->xlut, 0x00, माप(asyw->xlut));
	अगर ((asyw->ilut = wndw->func->ilut ? ilut : शून्य)) अणु
		अगर (!wndw->func->ilut(wndw, asyw, drm_color_lut_size(ilut))) अणु
			DRM_DEBUG_KMS("Invalid ilut\n");
			वापस -EINVAL;
		पूर्ण
		asyw->xlut.handle = wndw->wndw.vram.handle;
		asyw->xlut.i.buffer = !asyw->xlut.i.buffer;
		asyw->set.xlut = true;
	पूर्ण अन्यथा अणु
		asyw->clr.xlut = armw->xlut.handle != 0;
	पूर्ण

	/* Handle setting base SET_OUTPUT_LUT_LO_ENABLE_USE_CORE_LUT. */
	अगर (wndw->func->olut_core &&
	    (!armw->visible || (armw->xlut.handle && !asyw->xlut.handle)))
		asyw->set.xlut = true;

	अगर (wndw->func->csc && asyh->state.cपंचांग) अणु
		स्थिर काष्ठा drm_color_cपंचांग *cपंचांग = asyh->state.cपंचांग->data;
		wndw->func->csc(wndw, asyw, cपंचांग);
		asyw->csc.valid = true;
		asyw->set.csc = true;
	पूर्ण अन्यथा अणु
		asyw->csc.valid = false;
		asyw->clr.csc = armw->csc.valid;
	पूर्ण

	/* Can't करो an immediate flip जबतक changing the LUT. */
	asyh->state.async_flip = false;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_wndw_atomic_check(काष्ठा drm_plane *plane,
		       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा nouveau_drm *drm = nouveau_drm(plane->dev);
	काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
	काष्ठा nv50_wndw_atom *armw = nv50_wndw_atom(wndw->plane.state);
	काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(new_plane_state);
	काष्ठा nv50_head_atom *harm = शून्य, *asyh = शून्य;
	bool modeset = false;
	पूर्णांक ret;

	NV_ATOMIC(drm, "%s atomic_check\n", plane->name);

	/* Fetch the assembly state क्रम the head the winकरोw will beदीर्घ to,
	 * and determine whether the winकरोw will be visible.
	 */
	अगर (asyw->state.crtc) अणु
		asyh = nv50_head_atom_get(asyw->state.state, asyw->state.crtc);
		अगर (IS_ERR(asyh))
			वापस PTR_ERR(asyh);
		modeset = drm_atomic_crtc_needs_modeset(&asyh->state);
		asyw->visible = asyh->state.active;
	पूर्ण अन्यथा अणु
		asyw->visible = false;
	पूर्ण

	/* Fetch assembly state क्रम the head the winकरोw used to beदीर्घ to. */
	अगर (armw->state.crtc) अणु
		harm = nv50_head_atom_get(asyw->state.state, armw->state.crtc);
		अगर (IS_ERR(harm))
			वापस PTR_ERR(harm);
	पूर्ण

	/* LUT configuration can potentially cause the winकरोw to be disabled. */
	अगर (asyw->visible && wndw->func->xlut_set &&
	    (!armw->visible ||
	     asyh->state.color_mgmt_changed ||
	     asyw->state.fb->क्रमmat->क्रमmat !=
	     armw->state.fb->क्रमmat->क्रमmat)) अणु
		ret = nv50_wndw_atomic_check_lut(wndw, armw, asyw, asyh);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Calculate new winकरोw state. */
	अगर (asyw->visible) अणु
		ret = nv50_wndw_atomic_check_acquire(wndw, modeset,
						     armw, asyw, asyh);
		अगर (ret)
			वापस ret;

		asyh->wndw.mask |= BIT(wndw->id);
	पूर्ण अन्यथा
	अगर (armw->visible) अणु
		nv50_wndw_atomic_check_release(wndw, asyw, harm);
		harm->wndw.mask &= ~BIT(wndw->id);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	/* Aside from the obvious हाल where the winकरोw is actively being
	 * disabled, we might also need to temporarily disable the winकरोw
	 * when perक्रमming certain modeset operations.
	 */
	अगर (!asyw->visible || modeset) अणु
		asyw->clr.ntfy = armw->ntfy.handle != 0;
		asyw->clr.sema = armw->sema.handle != 0;
		asyw->clr.xlut = armw->xlut.handle != 0;
		अगर (asyw->clr.xlut && asyw->visible)
			asyw->set.xlut = asyw->xlut.handle != 0;
		asyw->clr.csc  = armw->csc.valid;
		अगर (wndw->func->image_clr)
			asyw->clr.image = armw->image.handle[0] != 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv50_wndw_cleanup_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(plane->dev);
	काष्ठा nouveau_bo *nvbo;

	NV_ATOMIC(drm, "%s cleanup: %p\n", plane->name, old_state->fb);
	अगर (!old_state->fb)
		वापस;

	nvbo = nouveau_gem_object(old_state->fb->obj[0]);
	nouveau_bo_unpin(nvbo);
पूर्ण

अटल पूर्णांक
nv50_wndw_prepare_fb(काष्ठा drm_plane *plane, काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा nouveau_drm *drm = nouveau_drm(plane->dev);
	काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
	काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	काष्ठा nouveau_bo *nvbo;
	काष्ठा nv50_head_atom *asyh;
	काष्ठा nv50_wndw_ctxdma *ctxdma;
	पूर्णांक ret;

	NV_ATOMIC(drm, "%s prepare: %p\n", plane->name, fb);
	अगर (!asyw->state.fb)
		वापस 0;

	nvbo = nouveau_gem_object(fb->obj[0]);
	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, true);
	अगर (ret)
		वापस ret;

	अगर (wndw->ctxdma.parent) अणु
		ctxdma = nv50_wndw_ctxdma_new(wndw, fb);
		अगर (IS_ERR(ctxdma)) अणु
			nouveau_bo_unpin(nvbo);
			वापस PTR_ERR(ctxdma);
		पूर्ण

		अगर (asyw->visible)
			asyw->image.handle[0] = ctxdma->object.handle;
	पूर्ण

	asyw->state.fence = dma_resv_get_excl_rcu(nvbo->bo.base.resv);
	asyw->image.offset[0] = nvbo->offset;

	अगर (wndw->func->prepare) अणु
		asyh = nv50_head_atom_get(asyw->state.state, asyw->state.crtc);
		अगर (IS_ERR(asyh))
			वापस PTR_ERR(asyh);

		wndw->func->prepare(wndw, asyh, asyw);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs
nv50_wndw_helper = अणु
	.prepare_fb = nv50_wndw_prepare_fb,
	.cleanup_fb = nv50_wndw_cleanup_fb,
	.atomic_check = nv50_wndw_atomic_check,
पूर्ण;

अटल व्योम
nv50_wndw_atomic_destroy_state(काष्ठा drm_plane *plane,
			       काष्ठा drm_plane_state *state)
अणु
	काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	__drm_atomic_helper_plane_destroy_state(&asyw->state);
	kमुक्त(asyw);
पूर्ण

अटल काष्ठा drm_plane_state *
nv50_wndw_atomic_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा nv50_wndw_atom *armw = nv50_wndw_atom(plane->state);
	काष्ठा nv50_wndw_atom *asyw;
	अगर (!(asyw = kदो_स्मृति(माप(*asyw), GFP_KERNEL)))
		वापस शून्य;
	__drm_atomic_helper_plane_duplicate_state(plane, &asyw->state);
	asyw->sema = armw->sema;
	asyw->ntfy = armw->ntfy;
	asyw->ilut = शून्य;
	asyw->xlut = armw->xlut;
	asyw->csc  = armw->csc;
	asyw->image = armw->image;
	asyw->poपूर्णांक = armw->poपूर्णांक;
	asyw->clr.mask = 0;
	asyw->set.mask = 0;
	वापस &asyw->state;
पूर्ण

अटल पूर्णांक
nv50_wndw_zpos_शेष(काष्ठा drm_plane *plane)
अणु
	वापस (plane->type == DRM_PLANE_TYPE_PRIMARY) ? 0 :
	       (plane->type == DRM_PLANE_TYPE_OVERLAY) ? 1 : 255;
पूर्ण

अटल व्योम
nv50_wndw_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा nv50_wndw_atom *asyw;

	अगर (WARN_ON(!(asyw = kzalloc(माप(*asyw), GFP_KERNEL))))
		वापस;

	अगर (plane->state)
		plane->funcs->atomic_destroy_state(plane, plane->state);

	__drm_atomic_helper_plane_reset(plane, &asyw->state);
	plane->state->zpos = nv50_wndw_zpos_शेष(plane);
	plane->state->normalized_zpos = nv50_wndw_zpos_शेष(plane);
पूर्ण

अटल व्योम
nv50_wndw_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
	काष्ठा nv50_wndw_ctxdma *ctxdma, *ctxपंचांगp;

	list_क्रम_each_entry_safe(ctxdma, ctxपंचांगp, &wndw->ctxdma.list, head) अणु
		nv50_wndw_ctxdma_del(ctxdma);
	पूर्ण

	nvअगर_notअगरy_dtor(&wndw->notअगरy);
	nv50_dmac_destroy(&wndw->wimm);
	nv50_dmac_destroy(&wndw->wndw);

	nv50_lut_fini(&wndw->ilut);

	drm_plane_cleanup(&wndw->plane);
	kमुक्त(wndw);
पूर्ण

/* This function assumes the क्रमmat has alपढ़ोy been validated against the plane
 * and the modअगरier was validated against the device-wides modअगरier list at FB
 * creation समय.
 */
अटल bool nv50_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					    u32 क्रमmat, u64 modअगरier)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(plane->dev);
	uपूर्णांक8_t i;

	अगर (drm->client.device.info.chipset < 0xc0) अणु
		स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);
		स्थिर uपूर्णांक8_t kind = (modअगरier >> 12) & 0xff;

		अगर (!क्रमmat) वापस false;

		क्रम (i = 0; i < info->num_planes; i++)
			अगर ((info->cpp[i] != 4) && kind != 0x70) वापस false;
	पूर्ण

	वापस true;
पूर्ण

स्थिर काष्ठा drm_plane_funcs
nv50_wndw = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = nv50_wndw_destroy,
	.reset = nv50_wndw_reset,
	.atomic_duplicate_state = nv50_wndw_atomic_duplicate_state,
	.atomic_destroy_state = nv50_wndw_atomic_destroy_state,
	.क्रमmat_mod_supported = nv50_plane_क्रमmat_mod_supported,
पूर्ण;

अटल पूर्णांक
nv50_wndw_notअगरy(काष्ठा nvअगर_notअगरy *notअगरy)
अणु
	वापस NVIF_NOTIFY_KEEP;
पूर्ण

व्योम
nv50_wndw_fini(काष्ठा nv50_wndw *wndw)
अणु
	nvअगर_notअगरy_put(&wndw->notअगरy);
पूर्ण

व्योम
nv50_wndw_init(काष्ठा nv50_wndw *wndw)
अणु
	nvअगर_notअगरy_get(&wndw->notअगरy);
पूर्ण

अटल स्थिर u64 nv50_cursor_क्रमmat_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID,
पूर्ण;

पूर्णांक
nv50_wndw_new_(स्थिर काष्ठा nv50_wndw_func *func, काष्ठा drm_device *dev,
	       क्रमागत drm_plane_type type, स्थिर अक्षर *name, पूर्णांक index,
	       स्थिर u32 *क्रमmat, u32 heads,
	       क्रमागत nv50_disp_पूर्णांकerlock_type पूर्णांकerlock_type, u32 पूर्णांकerlock_data,
	       काष्ठा nv50_wndw **pwndw)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvअगर_mmu *mmu = &drm->client.mmu;
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	काष्ठा nv50_wndw *wndw;
	स्थिर u64 *क्रमmat_modअगरiers;
	पूर्णांक nक्रमmat;
	पूर्णांक ret;

	अगर (!(wndw = *pwndw = kzalloc(माप(*wndw), GFP_KERNEL)))
		वापस -ENOMEM;
	wndw->func = func;
	wndw->id = index;
	wndw->पूर्णांकerlock.type = पूर्णांकerlock_type;
	wndw->पूर्णांकerlock.data = पूर्णांकerlock_data;

	wndw->ctxdma.parent = &wndw->wndw.base.user;
	INIT_LIST_HEAD(&wndw->ctxdma.list);

	क्रम (nक्रमmat = 0; क्रमmat[nक्रमmat]; nक्रमmat++);

	अगर (type == DRM_PLANE_TYPE_CURSOR)
		क्रमmat_modअगरiers = nv50_cursor_क्रमmat_modअगरiers;
	अन्यथा
		क्रमmat_modअगरiers = nouveau_display(dev)->क्रमmat_modअगरiers;

	ret = drm_universal_plane_init(dev, &wndw->plane, heads, &nv50_wndw, क्रमmat, nक्रमmat,
				       क्रमmat_modअगरiers, type, "%s-%d", name, index);
	अगर (ret) अणु
		kमुक्त(*pwndw);
		*pwndw = शून्य;
		वापस ret;
	पूर्ण

	drm_plane_helper_add(&wndw->plane, &nv50_wndw_helper);

	अगर (wndw->func->ilut) अणु
		ret = nv50_lut_init(disp, mmu, &wndw->ilut);
		अगर (ret)
			वापस ret;
	पूर्ण

	wndw->notअगरy.func = nv50_wndw_notअगरy;

	अगर (wndw->func->blend_set) अणु
		ret = drm_plane_create_zpos_property(&wndw->plane,
				nv50_wndw_zpos_शेष(&wndw->plane), 0, 254);
		अगर (ret)
			वापस ret;

		ret = drm_plane_create_alpha_property(&wndw->plane);
		अगर (ret)
			वापस ret;

		ret = drm_plane_create_blend_mode_property(&wndw->plane,
				BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				BIT(DRM_MODE_BLEND_PREMULTI) |
				BIT(DRM_MODE_BLEND_COVERAGE));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = drm_plane_create_zpos_immutable_property(&wndw->plane,
				nv50_wndw_zpos_शेष(&wndw->plane));
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv50_wndw_new(काष्ठा nouveau_drm *drm, क्रमागत drm_plane_type type, पूर्णांक index,
	      काष्ठा nv50_wndw **pwndw)
अणु
	काष्ठा अणु
		s32 oclass;
		पूर्णांक version;
		पूर्णांक (*new)(काष्ठा nouveau_drm *, क्रमागत drm_plane_type,
			   पूर्णांक, s32, काष्ठा nv50_wndw **);
	पूर्ण wndws[] = अणु
		अणु GA102_DISP_WINDOW_CHANNEL_DMA, 0, wndwc67e_new पूर्ण,
		अणु TU102_DISP_WINDOW_CHANNEL_DMA, 0, wndwc57e_new पूर्ण,
		अणु GV100_DISP_WINDOW_CHANNEL_DMA, 0, wndwc37e_new पूर्ण,
		अणुपूर्ण
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	पूर्णांक cid, ret;

	cid = nvअगर_mclass(&disp->disp->object, wndws);
	अगर (cid < 0) अणु
		NV_ERROR(drm, "No supported window class\n");
		वापस cid;
	पूर्ण

	ret = wndws[cid].new(drm, type, index, wndws[cid].oclass, pwndw);
	अगर (ret)
		वापस ret;

	वापस nv50_wimm_init(drm, *pwndw);
पूर्ण
