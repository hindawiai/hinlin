<शैली गुरु>
/*
 * Copyright 2009 Red Hat Inc.
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
 *
 * Author: Ben Skeggs
 */

#समावेश <drm/drm_crtc_helper.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_reg.h"
#समावेश "hw.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_bo.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_chan.h"

#समावेश <nvअगर/अगर0004.h>

काष्ठा nouveau_connector *
nv04_encoder_get_connector(काष्ठा nouveau_encoder *encoder)
अणु
	काष्ठा drm_device *dev = to_drm_encoder(encoder)->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा nouveau_connector *nv_connector = शून्य;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->encoder == to_drm_encoder(encoder))
			nv_connector = nouveau_connector(connector);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	वापस nv_connector;
पूर्ण

अटल व्योम
nv04_display_fini(काष्ठा drm_device *dev, bool runसमय, bool suspend)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv04_display *disp = nv04_display(dev);
	काष्ठा drm_crtc *crtc;

	/* Disable flip completion events. */
	nvअगर_notअगरy_put(&disp->flip);

	/* Disable vblank पूर्णांकerrupts. */
	NVWriteCRTC(dev, 0, NV_PCRTC_INTR_EN_0, 0);
	अगर (nv_two_heads(dev))
		NVWriteCRTC(dev, 1, NV_PCRTC_INTR_EN_0, 0);

	अगर (!runसमय)
		cancel_work_sync(&drm->hpd_work);

	अगर (!suspend)
		वापस;

	/* Un-pin FB and cursors so they'll be evicted to प्रणाली memory. */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा drm_framebuffer *fb = crtc->primary->fb;
		काष्ठा nouveau_bo *nvbo;

		अगर (!fb || !fb->obj[0])
			जारी;
		nvbo = nouveau_gem_object(fb->obj[0]);
		nouveau_bo_unpin(nvbo);
	पूर्ण

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
		अगर (nv_crtc->cursor.nvbo) अणु
			अगर (nv_crtc->cursor.set_offset)
				nouveau_bo_unmap(nv_crtc->cursor.nvbo);
			nouveau_bo_unpin(nv_crtc->cursor.nvbo);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
nv04_display_init(काष्ठा drm_device *dev, bool resume, bool runसमय)
अणु
	काष्ठा nv04_display *disp = nv04_display(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_encoder *encoder;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	/* meh.. modeset apparently करोesn't setup all the regs and depends
	 * on pre-existing state, क्रम now load the state of the card *beक्रमe*
	 * nouveau was loaded, and then करो a modeset.
	 *
	 * best thing to करो probably is to make save/restore routines not
	 * save/restore "pre-load" state, but more general so we can save
	 * on suspend too.
	 */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
		nv_crtc->save(&nv_crtc->base);
	पूर्ण

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, base.base.head)
		encoder->enc_save(&encoder->base.base);

	/* Enable flip completion events. */
	nvअगर_notअगरy_get(&disp->flip);

	अगर (!resume)
		वापस 0;

	/* Re-pin FB/cursors. */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा drm_framebuffer *fb = crtc->primary->fb;
		काष्ठा nouveau_bo *nvbo;

		अगर (!fb || !fb->obj[0])
			जारी;
		nvbo = nouveau_gem_object(fb->obj[0]);
		ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VRAM, true);
		अगर (ret)
			NV_ERROR(drm, "Could not pin framebuffer\n");
	पूर्ण

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
		अगर (!nv_crtc->cursor.nvbo)
			जारी;

		ret = nouveau_bo_pin(nv_crtc->cursor.nvbo,
				     NOUVEAU_GEM_DOMAIN_VRAM, true);
		अगर (!ret && nv_crtc->cursor.set_offset)
			ret = nouveau_bo_map(nv_crtc->cursor.nvbo);
		अगर (ret)
			NV_ERROR(drm, "Could not pin/map cursor.\n");
	पूर्ण

	/* Force CLUT to get re-loaded during modeset. */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

		nv_crtc->lut.depth = 0;
	पूर्ण

	/* This should ensure we करोn't hit a locking problem when someone
	 * wakes us up via a connector.  We should never go पूर्णांकo suspend
	 * जबतक the display is on anyways.
	 */
	अगर (runसमय)
		वापस 0;

	/* Restore mode. */
	drm_helper_resume_क्रमce_mode(dev);

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

		अगर (!nv_crtc->cursor.nvbo)
			जारी;

		अगर (nv_crtc->cursor.set_offset)
			nv_crtc->cursor.set_offset(nv_crtc,
						   nv_crtc->cursor.nvbo->offset);
		nv_crtc->cursor.set_pos(nv_crtc, nv_crtc->cursor_saved_x,
						 nv_crtc->cursor_saved_y);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv04_display_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा nv04_display *disp = nv04_display(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_encoder *encoder;
	काष्ठा nouveau_crtc *nv_crtc;

	/* Restore state */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, base.base.head)
		encoder->enc_restore(&encoder->base.base);

	list_क्रम_each_entry(nv_crtc, &dev->mode_config.crtc_list, base.head)
		nv_crtc->restore(&nv_crtc->base);

	nouveau_hw_save_vga_fonts(dev, 0);

	nvअगर_notअगरy_dtor(&disp->flip);

	nouveau_display(dev)->priv = शून्य;
	kमुक्त(disp);

	nvअगर_object_unmap(&drm->client.device.object);
पूर्ण

पूर्णांक
nv04_display_create(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा dcb_table *dcb = &drm->vbios.dcb;
	काष्ठा drm_connector *connector, *ct;
	काष्ठा drm_encoder *encoder;
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा nouveau_crtc *crtc;
	काष्ठा nv04_display *disp;
	पूर्णांक i, ret;

	disp = kzalloc(माप(*disp), GFP_KERNEL);
	अगर (!disp)
		वापस -ENOMEM;

	nvअगर_object_map(&drm->client.device.object, शून्य, 0);

	nouveau_display(dev)->priv = disp;
	nouveau_display(dev)->dtor = nv04_display_destroy;
	nouveau_display(dev)->init = nv04_display_init;
	nouveau_display(dev)->fini = nv04_display_fini;

	/* Pre-nv50 करोesn't support atomic, so don't expose the ioctls */
	dev->driver_features &= ~DRIVER_ATOMIC;

	/* Request page flip completion event. */
	अगर (drm->channel) अणु
		nvअगर_notअगरy_ctor(&drm->channel->nvsw, "kmsFlip", nv04_flip_complete,
				 false, NV04_NVSW_NTFY_UEVENT,
				 शून्य, 0, 0, &disp->flip);
	पूर्ण

	nouveau_hw_save_vga_fonts(dev, 1);

	nv04_crtc_create(dev, 0);
	अगर (nv_two_heads(dev))
		nv04_crtc_create(dev, 1);

	क्रम (i = 0; i < dcb->entries; i++) अणु
		काष्ठा dcb_output *dcbent = &dcb->entry[i];

		connector = nouveau_connector_create(dev, dcbent);
		अगर (IS_ERR(connector))
			जारी;

		चयन (dcbent->type) अणु
		हाल DCB_OUTPUT_ANALOG:
			ret = nv04_dac_create(connector, dcbent);
			अवरोध;
		हाल DCB_OUTPUT_LVDS:
		हाल DCB_OUTPUT_TMDS:
			ret = nv04_dfp_create(connector, dcbent);
			अवरोध;
		हाल DCB_OUTPUT_TV:
			अगर (dcbent->location == DCB_LOC_ON_CHIP)
				ret = nv17_tv_create(connector, dcbent);
			अन्यथा
				ret = nv04_tv_create(connector, dcbent);
			अवरोध;
		शेष:
			NV_WARN(drm, "DCB type %d not known\n", dcbent->type);
			जारी;
		पूर्ण

		अगर (ret)
			जारी;
	पूर्ण

	list_क्रम_each_entry_safe(connector, ct,
				 &dev->mode_config.connector_list, head) अणु
		अगर (!connector->possible_encoders) अणु
			NV_WARN(drm, "%s has no encoders, removing\n",
				connector->name);
			connector->funcs->destroy(connector);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
		काष्ठा nvkm_i2c_bus *bus =
			nvkm_i2c_bus_find(i2c, nv_encoder->dcb->i2c_index);
		nv_encoder->i2c = bus ? &bus->i2c : शून्य;
	पूर्ण

	/* Save previous state */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, base.head)
		crtc->save(&crtc->base);

	list_क्रम_each_entry(nv_encoder, &dev->mode_config.encoder_list, base.base.head)
		nv_encoder->enc_save(&nv_encoder->base.base);

	nouveau_overlay_init(dev);

	वापस 0;
पूर्ण
