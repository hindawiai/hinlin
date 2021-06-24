<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#समावेश "disp.h"
#समावेश "atom.h"
#समावेश "core.h"
#समावेश "head.h"
#समावेश "wndw.h"
#समावेश "handles.h"

#समावेश <linux/dma-mapping.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/component.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_scdc_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <nvअगर/push507c.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0002.h>
#समावेश <nvअगर/cl5070.h>
#समावेश <nvअगर/cl507d.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/समयr.h>

#समावेश <nvhw/class/cl507c.h>
#समावेश <nvhw/class/cl507d.h>
#समावेश <nvhw/class/cl837d.h>
#समावेश <nvhw/class/cl887d.h>
#समावेश <nvhw/class/cl907d.h>
#समावेश <nvhw/class/cl917d.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_dma.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_connector.h"
#समावेश "nouveau_encoder.h"
#समावेश "nouveau_fence.h"
#समावेश "nouveau_fbcon.h"

#समावेश <subdev/bios/dp.h>

/******************************************************************************
 * EVO channel
 *****************************************************************************/

अटल पूर्णांक
nv50_chan_create(काष्ठा nvअगर_device *device, काष्ठा nvअगर_object *disp,
		 स्थिर s32 *oclass, u8 head, व्योम *data, u32 size,
		 काष्ठा nv50_chan *chan)
अणु
	काष्ठा nvअगर_sclass *sclass;
	पूर्णांक ret, i, n;

	chan->device = device;

	ret = n = nvअगर_object_sclass_get(disp, &sclass);
	अगर (ret < 0)
		वापस ret;

	जबतक (oclass[0]) अणु
		क्रम (i = 0; i < n; i++) अणु
			अगर (sclass[i].oclass == oclass[0]) अणु
				ret = nvअगर_object_ctor(disp, "kmsChan", 0,
						       oclass[0], data, size,
						       &chan->user);
				अगर (ret == 0)
					nvअगर_object_map(&chan->user, शून्य, 0);
				nvअगर_object_sclass_put(&sclass);
				वापस ret;
			पूर्ण
		पूर्ण
		oclass++;
	पूर्ण

	nvअगर_object_sclass_put(&sclass);
	वापस -ENOSYS;
पूर्ण

अटल व्योम
nv50_chan_destroy(काष्ठा nv50_chan *chan)
अणु
	nvअगर_object_dtor(&chan->user);
पूर्ण

/******************************************************************************
 * DMA EVO channel
 *****************************************************************************/

व्योम
nv50_dmac_destroy(काष्ठा nv50_dmac *dmac)
अणु
	nvअगर_object_dtor(&dmac->vram);
	nvअगर_object_dtor(&dmac->sync);

	nv50_chan_destroy(&dmac->base);

	nvअगर_mem_dtor(&dmac->_push.mem);
पूर्ण

अटल व्योम
nv50_dmac_kick(काष्ठा nvअगर_push *push)
अणु
	काष्ठा nv50_dmac *dmac = container_of(push, typeof(*dmac), _push);

	dmac->cur = push->cur - (u32 *)dmac->_push.mem.object.map.ptr;
	अगर (dmac->put != dmac->cur) अणु
		/* Push buffer fetches are not coherent with BAR1, we need to ensure
		 * ग_लिखोs have been flushed right through to VRAM beक्रमe writing PUT.
		 */
		अगर (dmac->push->mem.type & NVIF_MEM_VRAM) अणु
			काष्ठा nvअगर_device *device = dmac->base.device;
			nvअगर_wr32(&device->object, 0x070000, 0x00000001);
			nvअगर_msec(device, 2000,
				अगर (!(nvअगर_rd32(&device->object, 0x070000) & 0x00000002))
					अवरोध;
			);
		पूर्ण

		NVIF_WV32(&dmac->base.user, NV507C, PUT, PTR, dmac->cur);
		dmac->put = dmac->cur;
	पूर्ण

	push->bgn = push->cur;
पूर्ण

अटल पूर्णांक
nv50_dmac_मुक्त(काष्ठा nv50_dmac *dmac)
अणु
	u32 get = NVIF_RV32(&dmac->base.user, NV507C, GET, PTR);
	अगर (get > dmac->cur) /* NVIDIA stay 5 away from GET, करो the same. */
		वापस get - dmac->cur - 5;
	वापस dmac->max - dmac->cur;
पूर्ण

अटल पूर्णांक
nv50_dmac_wind(काष्ठा nv50_dmac *dmac)
अणु
	/* Wait क्रम GET to depart from the beginning of the push buffer to
	 * prevent writing PUT == GET, which would be ignored by HW.
	 */
	u32 get = NVIF_RV32(&dmac->base.user, NV507C, GET, PTR);
	अगर (get == 0) अणु
		/* Corner-हाल, HW idle, but non-committed work pending. */
		अगर (dmac->put == 0)
			nv50_dmac_kick(dmac->push);

		अगर (nvअगर_msec(dmac->base.device, 2000,
			अगर (NVIF_TV32(&dmac->base.user, NV507C, GET, PTR, >, 0))
				अवरोध;
		) < 0)
			वापस -ETIMEDOUT;
	पूर्ण

	PUSH_RSVD(dmac->push, PUSH_JUMP(dmac->push, 0));
	dmac->cur = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_dmac_रुको(काष्ठा nvअगर_push *push, u32 size)
अणु
	काष्ठा nv50_dmac *dmac = container_of(push, typeof(*dmac), _push);
	पूर्णांक मुक्त;

	अगर (WARN_ON(size > dmac->max))
		वापस -EINVAL;

	dmac->cur = push->cur - (u32 *)dmac->_push.mem.object.map.ptr;
	अगर (dmac->cur + size >= dmac->max) अणु
		पूर्णांक ret = nv50_dmac_wind(dmac);
		अगर (ret)
			वापस ret;

		push->cur = dmac->_push.mem.object.map.ptr;
		push->cur = push->cur + dmac->cur;
		nv50_dmac_kick(push);
	पूर्ण

	अगर (nvअगर_msec(dmac->base.device, 2000,
		अगर ((मुक्त = nv50_dmac_मुक्त(dmac)) >= size)
			अवरोध;
	) < 0) अणु
		WARN_ON(1);
		वापस -ETIMEDOUT;
	पूर्ण

	push->bgn = dmac->_push.mem.object.map.ptr;
	push->bgn = push->bgn + dmac->cur;
	push->cur = push->bgn;
	push->end = push->cur + मुक्त;
	वापस 0;
पूर्ण

MODULE_PARM_DESC(kms_vram_pushbuf, "Place EVO/NVD push buffers in VRAM (default: auto)");
अटल पूर्णांक nv50_dmac_vram_pushbuf = -1;
module_param_named(kms_vram_pushbuf, nv50_dmac_vram_pushbuf, पूर्णांक, 0400);

पूर्णांक
nv50_dmac_create(काष्ठा nvअगर_device *device, काष्ठा nvअगर_object *disp,
		 स्थिर s32 *oclass, u8 head, व्योम *data, u32 size, s64 syncbuf,
		 काष्ठा nv50_dmac *dmac)
अणु
	काष्ठा nouveau_cli *cli = (व्योम *)device->object.client;
	काष्ठा nv50_disp_core_channel_dma_v0 *args = data;
	u8 type = NVIF_MEM_COHERENT;
	पूर्णांक ret;

	mutex_init(&dmac->lock);

	/* Pascal added support क्रम 47-bit physical addresses, but some
	 * parts of EVO still only accept 40-bit PAs.
	 *
	 * To aव्योम issues on प्रणालीs with large amounts of RAM, and on
	 * प्रणालीs where an IOMMU maps pages at a high address, we need
	 * to allocate push buffers in VRAM instead.
	 *
	 * This appears to match NVIDIA's behaviour on Pascal.
	 */
	अगर ((nv50_dmac_vram_pushbuf > 0) ||
	    (nv50_dmac_vram_pushbuf < 0 && device->info.family == NV_DEVICE_INFO_V0_PASCAL))
		type |= NVIF_MEM_VRAM;

	ret = nvअगर_mem_ctor_map(&cli->mmu, "kmsChanPush", type, 0x1000,
				&dmac->_push.mem);
	अगर (ret)
		वापस ret;

	dmac->ptr = dmac->_push.mem.object.map.ptr;
	dmac->_push.रुको = nv50_dmac_रुको;
	dmac->_push.kick = nv50_dmac_kick;
	dmac->push = &dmac->_push;
	dmac->push->bgn = dmac->_push.mem.object.map.ptr;
	dmac->push->cur = dmac->push->bgn;
	dmac->push->end = dmac->push->bgn;
	dmac->max = 0x1000/4 - 1;

	/* EVO channels are affected by a HW bug where the last 12 DWORDs
	 * of the push buffer aren't able to be used safely.
	 */
	अगर (disp->oclass < GV100_DISP)
		dmac->max -= 12;

	args->pushbuf = nvअगर_handle(&dmac->_push.mem.object);

	ret = nv50_chan_create(device, disp, oclass, head, data, size,
			       &dmac->base);
	अगर (ret)
		वापस ret;

	अगर (syncbuf < 0)
		वापस 0;

	ret = nvअगर_object_ctor(&dmac->base.user, "kmsSyncCtxDma", NV50_DISP_HANDLE_SYNCBUF,
			       NV_DMA_IN_MEMORY,
			       &(काष्ठा nv_dma_v0) अणु
					.target = NV_DMA_V0_TARGET_VRAM,
					.access = NV_DMA_V0_ACCESS_RDWR,
					.start = syncbuf + 0x0000,
					.limit = syncbuf + 0x0fff,
			       पूर्ण, माप(काष्ठा nv_dma_v0),
			       &dmac->sync);
	अगर (ret)
		वापस ret;

	ret = nvअगर_object_ctor(&dmac->base.user, "kmsVramCtxDma", NV50_DISP_HANDLE_VRAM,
			       NV_DMA_IN_MEMORY,
			       &(काष्ठा nv_dma_v0) अणु
					.target = NV_DMA_V0_TARGET_VRAM,
					.access = NV_DMA_V0_ACCESS_RDWR,
					.start = 0,
					.limit = device->info.ram_user - 1,
			       पूर्ण, माप(काष्ठा nv_dma_v0),
			       &dmac->vram);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

/******************************************************************************
 * Output path helpers
 *****************************************************************************/
अटल व्योम
nv50_outp_dump_caps(काष्ठा nouveau_drm *drm,
		    काष्ठा nouveau_encoder *outp)
अणु
	NV_DEBUG(drm, "%s caps: dp_interlace=%d\n",
		 outp->base.base.name, outp->caps.dp_पूर्णांकerlace);
पूर्ण

अटल व्योम
nv50_outp_release(काष्ठा nouveau_encoder *nv_encoder)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(nv_encoder->base.base.dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_RELEASE,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = nv_encoder->dcb->hashm,
	पूर्ण;

	nvअगर_mthd(&disp->disp->object, 0, &args, माप(args));
	nv_encoder->or = -1;
	nv_encoder->link = 0;
पूर्ण

अटल पूर्णांक
nv50_outp_acquire(काष्ठा nouveau_encoder *nv_encoder, bool hda)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(nv_encoder->base.base.dev);
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_acquire_v0 info;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_ACQUIRE,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = nv_encoder->dcb->hashm,
		.info.hda = hda,
	पूर्ण;
	पूर्णांक ret;

	ret = nvअगर_mthd(&disp->disp->object, 0, &args, माप(args));
	अगर (ret) अणु
		NV_ERROR(drm, "error acquiring output path: %d\n", ret);
		वापस ret;
	पूर्ण

	nv_encoder->or = args.info.or;
	nv_encoder->link = args.info.link;
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_outp_atomic_check_view(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_crtc_state *crtc_state,
			    काष्ठा drm_connector_state *conn_state,
			    काष्ठा drm_display_mode *native_mode)
अणु
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	काष्ठा drm_display_mode *mode = &crtc_state->mode;
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा nouveau_conn_atom *asyc = nouveau_conn_atom(conn_state);
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);

	NV_ATOMIC(drm, "%s atomic_check\n", encoder->name);
	asyc->scaler.full = false;
	अगर (!native_mode)
		वापस 0;

	अगर (asyc->scaler.mode == DRM_MODE_SCALE_NONE) अणु
		चयन (connector->connector_type) अणु
		हाल DRM_MODE_CONNECTOR_LVDS:
		हाल DRM_MODE_CONNECTOR_eDP:
			/* Don't क्रमce scaler क्रम EDID modes with
			 * same size as the native one (e.g. dअगरferent
			 * refresh rate)
			 */
			अगर (mode->hdisplay == native_mode->hdisplay &&
			    mode->vdisplay == native_mode->vdisplay &&
			    mode->type & DRM_MODE_TYPE_DRIVER)
				अवरोध;
			mode = native_mode;
			asyc->scaler.full = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		mode = native_mode;
	पूर्ण

	अगर (!drm_mode_equal(adjusted_mode, mode)) अणु
		drm_mode_copy(adjusted_mode, mode);
		crtc_state->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_outp_atomic_check(काष्ठा drm_encoder *encoder,
		       काष्ठा drm_crtc_state *crtc_state,
		       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nv50_head_atom *asyh = nv50_head_atom(crtc_state);
	पूर्णांक ret;

	ret = nv50_outp_atomic_check_view(encoder, crtc_state, conn_state,
					  nv_connector->native_mode);
	अगर (ret)
		वापस ret;

	अगर (crtc_state->mode_changed || crtc_state->connectors_changed)
		asyh->or.bpc = connector->display_info.bpc;

	वापस 0;
पूर्ण

काष्ठा nouveau_connector *
nv50_outp_get_new_connector(काष्ठा drm_atomic_state *state, काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	काष्ठा drm_encoder *encoder = to_drm_encoder(outp);
	पूर्णांक i;

	क्रम_each_new_connector_in_state(state, connector, connector_state, i) अणु
		अगर (connector_state->best_encoder == encoder)
			वापस nouveau_connector(connector);
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा nouveau_connector *
nv50_outp_get_old_connector(काष्ठा drm_atomic_state *state, काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	काष्ठा drm_encoder *encoder = to_drm_encoder(outp);
	पूर्णांक i;

	क्रम_each_old_connector_in_state(state, connector, connector_state, i) अणु
		अगर (connector_state->best_encoder == encoder)
			वापस nouveau_connector(connector);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा nouveau_crtc *
nv50_outp_get_new_crtc(स्थिर काष्ठा drm_atomic_state *state, स्थिर काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	स्थिर u32 mask = drm_encoder_mask(&outp->base.base);
	पूर्णांक i;

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (crtc_state->encoder_mask & mask)
			वापस nouveau_crtc(crtc);
	पूर्ण

	वापस शून्य;
पूर्ण

/******************************************************************************
 * DAC
 *****************************************************************************/
अटल व्योम
nv50_dac_atomic_disable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_core *core = nv50_disp(encoder->dev)->core;
	स्थिर u32 ctrl = NVDEF(NV507D, DAC_SET_CONTROL, OWNER, NONE);

	core->func->dac->ctrl(core, nv_encoder->or, ctrl, शून्य);
	nv_encoder->crtc = शून्य;
	nv50_outp_release(nv_encoder);
पूर्ण

अटल व्योम
nv50_dac_atomic_enable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_crtc *nv_crtc = nv50_outp_get_new_crtc(state, nv_encoder);
	काष्ठा nv50_head_atom *asyh =
		nv50_head_atom(drm_atomic_get_new_crtc_state(state, &nv_crtc->base));
	काष्ठा nv50_core *core = nv50_disp(encoder->dev)->core;
	u32 ctrl = 0;

	चयन (nv_crtc->index) अणु
	हाल 0: ctrl |= NVDEF(NV507D, DAC_SET_CONTROL, OWNER, HEAD0); अवरोध;
	हाल 1: ctrl |= NVDEF(NV507D, DAC_SET_CONTROL, OWNER, HEAD1); अवरोध;
	हाल 2: ctrl |= NVDEF(NV907D, DAC_SET_CONTROL, OWNER_MASK, HEAD2); अवरोध;
	हाल 3: ctrl |= NVDEF(NV907D, DAC_SET_CONTROL, OWNER_MASK, HEAD3); अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	ctrl |= NVDEF(NV507D, DAC_SET_CONTROL, PROTOCOL, RGB_CRT);

	nv50_outp_acquire(nv_encoder, false);

	core->func->dac->ctrl(core, nv_encoder->or, ctrl, asyh);
	asyh->or.depth = 0;

	nv_encoder->crtc = &nv_crtc->base;
पूर्ण

अटल क्रमागत drm_connector_status
nv50_dac_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_dac_load_v0 load;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_DAC_LOAD,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = nv_encoder->dcb->hashm,
	पूर्ण;
	पूर्णांक ret;

	args.load.data = nouveau_drm(encoder->dev)->vbios.dactestval;
	अगर (args.load.data == 0)
		args.load.data = 340;

	ret = nvअगर_mthd(&disp->disp->object, 0, &args, माप(args));
	अगर (ret || !args.load.load)
		वापस connector_status_disconnected;

	वापस connector_status_connected;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
nv50_dac_help = अणु
	.atomic_check = nv50_outp_atomic_check,
	.atomic_enable = nv50_dac_atomic_enable,
	.atomic_disable = nv50_dac_atomic_disable,
	.detect = nv50_dac_detect
पूर्ण;

अटल व्योम
nv50_dac_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs
nv50_dac_func = अणु
	.destroy = nv50_dac_destroy,
पूर्ण;

अटल पूर्णांक
nv50_dac_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *dcbe)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nvkm_i2c_bus *bus;
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा drm_encoder *encoder;
	पूर्णांक type = DRM_MODE_ENCODER_DAC;

	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;
	nv_encoder->dcb = dcbe;

	bus = nvkm_i2c_bus_find(i2c, dcbe->i2c_index);
	अगर (bus)
		nv_encoder->i2c = &bus->i2c;

	encoder = to_drm_encoder(nv_encoder);
	encoder->possible_crtcs = dcbe->heads;
	encoder->possible_clones = 0;
	drm_encoder_init(connector->dev, encoder, &nv50_dac_func, type,
			 "dac-%04x-%04x", dcbe->hasht, dcbe->hashm);
	drm_encoder_helper_add(encoder, &nv50_dac_help);

	drm_connector_attach_encoder(connector, encoder);
	वापस 0;
पूर्ण

/*
 * audio component binding क्रम ELD notअगरication
 */
अटल व्योम
nv50_audio_component_eld_notअगरy(काष्ठा drm_audio_component *acomp, पूर्णांक port,
				पूर्णांक dev_id)
अणु
	अगर (acomp && acomp->audio_ops && acomp->audio_ops->pin_eld_notअगरy)
		acomp->audio_ops->pin_eld_notअगरy(acomp->audio_ops->audio_ptr,
						 port, dev_id);
पूर्ण

अटल पूर्णांक
nv50_audio_component_get_eld(काष्ठा device *kdev, पूर्णांक port, पूर्णांक dev_id,
			     bool *enabled, अचिन्हित अक्षर *buf, पूर्णांक max_bytes)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(kdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा drm_encoder *encoder;
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा nouveau_crtc *nv_crtc;
	पूर्णांक ret = 0;

	*enabled = false;

	mutex_lock(&drm->audio.lock);

	drm_क्रम_each_encoder(encoder, drm->dev) अणु
		काष्ठा nouveau_connector *nv_connector = शून्य;

		अगर (encoder->encoder_type == DRM_MODE_ENCODER_DPMST)
			जारी; /* TODO */

		nv_encoder = nouveau_encoder(encoder);
		nv_connector = nouveau_connector(nv_encoder->audio.connector);
		nv_crtc = nouveau_crtc(nv_encoder->crtc);

		अगर (!nv_crtc || nv_encoder->or != port || nv_crtc->index != dev_id)
			जारी;

		*enabled = nv_encoder->audio.enabled;
		अगर (*enabled) अणु
			ret = drm_eld_size(nv_connector->base.eld);
			स_नकल(buf, nv_connector->base.eld,
			       min(max_bytes, ret));
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&drm->audio.lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_ops nv50_audio_component_ops = अणु
	.get_eld = nv50_audio_component_get_eld,
पूर्ण;

अटल पूर्णांक
nv50_audio_component_bind(काष्ठा device *kdev, काष्ठा device *hda_kdev,
			  व्योम *data)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(kdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा drm_audio_component *acomp = data;

	अगर (WARN_ON(!device_link_add(hda_kdev, kdev, DL_FLAG_STATELESS)))
		वापस -ENOMEM;

	drm_modeset_lock_all(drm_dev);
	acomp->ops = &nv50_audio_component_ops;
	acomp->dev = kdev;
	drm->audio.component = acomp;
	drm_modeset_unlock_all(drm_dev);
	वापस 0;
पूर्ण

अटल व्योम
nv50_audio_component_unbind(काष्ठा device *kdev, काष्ठा device *hda_kdev,
			    व्योम *data)
अणु
	काष्ठा drm_device *drm_dev = dev_get_drvdata(kdev);
	काष्ठा nouveau_drm *drm = nouveau_drm(drm_dev);
	काष्ठा drm_audio_component *acomp = data;

	drm_modeset_lock_all(drm_dev);
	drm->audio.component = शून्य;
	acomp->ops = शून्य;
	acomp->dev = शून्य;
	drm_modeset_unlock_all(drm_dev);
पूर्ण

अटल स्थिर काष्ठा component_ops nv50_audio_component_bind_ops = अणु
	.bind   = nv50_audio_component_bind,
	.unbind = nv50_audio_component_unbind,
पूर्ण;

अटल व्योम
nv50_audio_component_init(काष्ठा nouveau_drm *drm)
अणु
	अगर (component_add(drm->dev->dev, &nv50_audio_component_bind_ops))
		वापस;

	drm->audio.component_रेजिस्टरed = true;
	mutex_init(&drm->audio.lock);
पूर्ण

अटल व्योम
nv50_audio_component_fini(काष्ठा nouveau_drm *drm)
अणु
	अगर (!drm->audio.component_रेजिस्टरed)
		वापस;

	component_del(drm->dev->dev, &nv50_audio_component_bind_ops);
	drm->audio.component_रेजिस्टरed = false;
	mutex_destroy(&drm->audio.lock);
पूर्ण

/******************************************************************************
 * Audio
 *****************************************************************************/
अटल व्योम
nv50_audio_disable(काष्ठा drm_encoder *encoder, काष्ठा nouveau_crtc *nv_crtc)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_hda_eld_v0 eld;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method  = NV50_DISP_MTHD_V1_SOR_HDA_ELD,
		.base.hasht   = nv_encoder->dcb->hasht,
		.base.hashm   = (0xf0ff & nv_encoder->dcb->hashm) |
				(0x0100 << nv_crtc->index),
	पूर्ण;

	mutex_lock(&drm->audio.lock);
	अगर (nv_encoder->audio.enabled) अणु
		nv_encoder->audio.enabled = false;
		nv_encoder->audio.connector = शून्य;
		nvअगर_mthd(&disp->disp->object, 0, &args, माप(args));
	पूर्ण
	mutex_unlock(&drm->audio.lock);

	nv50_audio_component_eld_notअगरy(drm->audio.component, nv_encoder->or,
					nv_crtc->index);
पूर्ण

अटल व्योम
nv50_audio_enable(काष्ठा drm_encoder *encoder, काष्ठा nouveau_crtc *nv_crtc,
		  काष्ठा nouveau_connector *nv_connector, काष्ठा drm_atomic_state *state,
		  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा __packed अणु
		काष्ठा अणु
			काष्ठा nv50_disp_mthd_v1 mthd;
			काष्ठा nv50_disp_sor_hda_eld_v0 eld;
		पूर्ण base;
		u8 data[माप(nv_connector->base.eld)];
	पूर्ण args = अणु
		.base.mthd.version = 1,
		.base.mthd.method  = NV50_DISP_MTHD_V1_SOR_HDA_ELD,
		.base.mthd.hasht   = nv_encoder->dcb->hasht,
		.base.mthd.hashm   = (0xf0ff & nv_encoder->dcb->hashm) |
				     (0x0100 << nv_crtc->index),
	पूर्ण;

	अगर (!drm_detect_monitor_audio(nv_connector->edid))
		वापस;

	mutex_lock(&drm->audio.lock);

	स_नकल(args.data, nv_connector->base.eld, माप(args.data));

	nvअगर_mthd(&disp->disp->object, 0, &args,
		  माप(args.base) + drm_eld_size(args.data));
	nv_encoder->audio.enabled = true;
	nv_encoder->audio.connector = &nv_connector->base;

	mutex_unlock(&drm->audio.lock);

	nv50_audio_component_eld_notअगरy(drm->audio.component, nv_encoder->or,
					nv_crtc->index);
पूर्ण

/******************************************************************************
 * HDMI
 *****************************************************************************/
अटल व्योम
nv50_hdmi_disable(काष्ठा drm_encoder *encoder, काष्ठा nouveau_crtc *nv_crtc)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_hdmi_pwr_v0 pwr;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_HDMI_PWR,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = (0xf0ff & nv_encoder->dcb->hashm) |
			       (0x0100 << nv_crtc->index),
	पूर्ण;

	nvअगर_mthd(&disp->disp->object, 0, &args, माप(args));
पूर्ण

अटल व्योम
nv50_hdmi_enable(काष्ठा drm_encoder *encoder, काष्ठा nouveau_crtc *nv_crtc,
		 काष्ठा nouveau_connector *nv_connector, काष्ठा drm_atomic_state *state,
		 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(encoder->dev);
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_hdmi_pwr_v0 pwr;
		u8 infoframes[2 * 17]; /* two frames, up to 17 bytes each */
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_HDMI_PWR,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = (0xf0ff & nv_encoder->dcb->hashm) |
			       (0x0100 << nv_crtc->index),
		.pwr.state = 1,
		.pwr.rekey = 56, /* binary driver, and tegra, स्थिरant */
	पूर्ण;
	काष्ठा drm_hdmi_info *hdmi;
	u32 max_ac_packet;
	जोड़ hdmi_infoframe avi_frame;
	जोड़ hdmi_infoframe venकरोr_frame;
	bool high_पंचांगds_घड़ी_ratio = false, scrambling = false;
	u8 config;
	पूर्णांक ret;
	पूर्णांक size;

	अगर (!drm_detect_hdmi_monitor(nv_connector->edid))
		वापस;

	hdmi = &nv_connector->base.display_info.hdmi;

	ret = drm_hdmi_avi_infoframe_from_display_mode(&avi_frame.avi,
						       &nv_connector->base, mode);
	अगर (!ret) अणु
		/* We have an AVI InfoFrame, populate it to the display */
		args.pwr.avi_infoframe_length
			= hdmi_infoframe_pack(&avi_frame, args.infoframes, 17);
	पूर्ण

	ret = drm_hdmi_venकरोr_infoframe_from_display_mode(&venकरोr_frame.venकरोr.hdmi,
							  &nv_connector->base, mode);
	अगर (!ret) अणु
		/* We have a Venकरोr InfoFrame, populate it to the display */
		args.pwr.venकरोr_infoframe_length
			= hdmi_infoframe_pack(&venकरोr_frame,
					      args.infoframes
					      + args.pwr.avi_infoframe_length,
					      17);
	पूर्ण

	max_ac_packet  = mode->htotal - mode->hdisplay;
	max_ac_packet -= args.pwr.rekey;
	max_ac_packet -= 18; /* स्थिरant from tegra */
	args.pwr.max_ac_packet = max_ac_packet / 32;

	अगर (hdmi->scdc.scrambling.supported) अणु
		high_पंचांगds_घड़ी_ratio = mode->घड़ी > 340000;
		scrambling = high_पंचांगds_घड़ी_ratio ||
			hdmi->scdc.scrambling.low_rates;
	पूर्ण

	args.pwr.scdc =
		NV50_DISP_SOR_HDMI_PWR_V0_SCDC_SCRAMBLE * scrambling |
		NV50_DISP_SOR_HDMI_PWR_V0_SCDC_DIV_BY_4 * high_पंचांगds_घड़ी_ratio;

	size = माप(args.base)
		+ माप(args.pwr)
		+ args.pwr.avi_infoframe_length
		+ args.pwr.venकरोr_infoframe_length;
	nvअगर_mthd(&disp->disp->object, 0, &args, size);

	nv50_audio_enable(encoder, nv_crtc, nv_connector, state, mode);

	/* If SCDC is supported by the करोwnstream monitor, update
	 * भागider / scrambling settings to what we programmed above.
	 */
	अगर (!hdmi->scdc.scrambling.supported)
		वापस;

	ret = drm_scdc_पढ़ोb(nv_encoder->i2c, SCDC_TMDS_CONFIG, &config);
	अगर (ret < 0) अणु
		NV_ERROR(drm, "Failure to read SCDC_TMDS_CONFIG: %d\n", ret);
		वापस;
	पूर्ण
	config &= ~(SCDC_TMDS_BIT_CLOCK_RATIO_BY_40 | SCDC_SCRAMBLING_ENABLE);
	config |= SCDC_TMDS_BIT_CLOCK_RATIO_BY_40 * high_पंचांगds_घड़ी_ratio;
	config |= SCDC_SCRAMBLING_ENABLE * scrambling;
	ret = drm_scdc_ग_लिखोb(nv_encoder->i2c, SCDC_TMDS_CONFIG, config);
	अगर (ret < 0)
		NV_ERROR(drm, "Failure to write SCDC_TMDS_CONFIG = 0x%02x: %d\n",
			 config, ret);
पूर्ण

/******************************************************************************
 * MST
 *****************************************************************************/
#घोषणा nv50_msपंचांग(p) container_of((p), काष्ठा nv50_msपंचांग, mgr)
#घोषणा nv50_mstc(p) container_of((p), काष्ठा nv50_mstc, connector)
#घोषणा nv50_msto(p) container_of((p), काष्ठा nv50_msto, encoder)

काष्ठा nv50_mstc अणु
	काष्ठा nv50_msपंचांग *msपंचांग;
	काष्ठा drm_dp_mst_port *port;
	काष्ठा drm_connector connector;

	काष्ठा drm_display_mode *native;
	काष्ठा edid *edid;
पूर्ण;

काष्ठा nv50_msto अणु
	काष्ठा drm_encoder encoder;

	/* head is अटलally asचिन्हित on msto creation */
	काष्ठा nv50_head *head;
	काष्ठा nv50_mstc *mstc;
	bool disabled;
पूर्ण;

काष्ठा nouveau_encoder *nv50_real_outp(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nv50_msto *msto;

	अगर (encoder->encoder_type != DRM_MODE_ENCODER_DPMST)
		वापस nouveau_encoder(encoder);

	msto = nv50_msto(encoder);
	अगर (!msto->mstc)
		वापस शून्य;
	वापस msto->mstc->msपंचांग->outp;
पूर्ण

अटल काष्ठा drm_dp_payload *
nv50_msto_payload(काष्ठा nv50_msto *msto)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(msto->encoder.dev);
	काष्ठा nv50_mstc *mstc = msto->mstc;
	काष्ठा nv50_msपंचांग *msपंचांग = mstc->msपंचांग;
	पूर्णांक vcpi = mstc->port->vcpi.vcpi, i;

	WARN_ON(!mutex_is_locked(&msपंचांग->mgr.payload_lock));

	NV_ATOMIC(drm, "%s: vcpi %d\n", msto->encoder.name, vcpi);
	क्रम (i = 0; i < msपंचांग->mgr.max_payloads; i++) अणु
		काष्ठा drm_dp_payload *payload = &msपंचांग->mgr.payloads[i];
		NV_ATOMIC(drm, "%s: %d: vcpi %d start 0x%02x slots 0x%02x\n",
			  msपंचांग->outp->base.base.name, i, payload->vcpi,
			  payload->start_slot, payload->num_slots);
	पूर्ण

	क्रम (i = 0; i < msपंचांग->mgr.max_payloads; i++) अणु
		काष्ठा drm_dp_payload *payload = &msपंचांग->mgr.payloads[i];
		अगर (payload->vcpi == vcpi)
			वापस payload;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
nv50_msto_cleanup(काष्ठा nv50_msto *msto)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(msto->encoder.dev);
	काष्ठा nv50_mstc *mstc = msto->mstc;
	काष्ठा nv50_msपंचांग *msपंचांग = mstc->msपंचांग;

	अगर (!msto->disabled)
		वापस;

	NV_ATOMIC(drm, "%s: msto cleanup\n", msto->encoder.name);

	drm_dp_mst_deallocate_vcpi(&msपंचांग->mgr, mstc->port);

	msto->mstc = शून्य;
	msto->disabled = false;
पूर्ण

अटल व्योम
nv50_msto_prepare(काष्ठा nv50_msto *msto)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(msto->encoder.dev);
	काष्ठा nv50_mstc *mstc = msto->mstc;
	काष्ठा nv50_msपंचांग *msपंचांग = mstc->msपंचांग;
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_dp_mst_vcpi_v0 vcpi;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_DP_MST_VCPI,
		.base.hasht  = msपंचांग->outp->dcb->hasht,
		.base.hashm  = (0xf0ff & msपंचांग->outp->dcb->hashm) |
			       (0x0100 << msto->head->base.index),
	पूर्ण;

	mutex_lock(&msपंचांग->mgr.payload_lock);

	NV_ATOMIC(drm, "%s: msto prepare\n", msto->encoder.name);
	अगर (mstc->port->vcpi.vcpi > 0) अणु
		काष्ठा drm_dp_payload *payload = nv50_msto_payload(msto);
		अगर (payload) अणु
			args.vcpi.start_slot = payload->start_slot;
			args.vcpi.num_slots = payload->num_slots;
			args.vcpi.pbn = mstc->port->vcpi.pbn;
			args.vcpi.aligned_pbn = mstc->port->vcpi.aligned_pbn;
		पूर्ण
	पूर्ण

	NV_ATOMIC(drm, "%s: %s: %02x %02x %04x %04x\n",
		  msto->encoder.name, msto->head->base.base.name,
		  args.vcpi.start_slot, args.vcpi.num_slots,
		  args.vcpi.pbn, args.vcpi.aligned_pbn);

	nvअगर_mthd(&drm->display->disp.object, 0, &args, माप(args));
	mutex_unlock(&msपंचांग->mgr.payload_lock);
पूर्ण

अटल पूर्णांक
nv50_msto_atomic_check(काष्ठा drm_encoder *encoder,
		       काष्ठा drm_crtc_state *crtc_state,
		       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_atomic_state *state = crtc_state->state;
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	काष्ठा nv50_msपंचांग *msपंचांग = mstc->msपंचांग;
	काष्ठा nv50_head_atom *asyh = nv50_head_atom(crtc_state);
	पूर्णांक slots;
	पूर्णांक ret;

	ret = nv50_outp_atomic_check_view(encoder, crtc_state, conn_state,
					  mstc->native);
	अगर (ret)
		वापस ret;

	अगर (!crtc_state->mode_changed && !crtc_state->connectors_changed)
		वापस 0;

	/*
	 * When restoring duplicated states, we need to make sure that the bw
	 * reमुख्यs the same and aव्योम recalculating it, as the connector's bpc
	 * may have changed after the state was duplicated
	 */
	अगर (!state->duplicated) अणु
		स्थिर पूर्णांक घड़ी = crtc_state->adjusted_mode.घड़ी;

		asyh->or.bpc = connector->display_info.bpc;
		asyh->dp.pbn = drm_dp_calc_pbn_mode(घड़ी, asyh->or.bpc * 3,
						    false);
	पूर्ण

	slots = drm_dp_atomic_find_vcpi_slots(state, &msपंचांग->mgr, mstc->port,
					      asyh->dp.pbn, 0);
	अगर (slots < 0)
		वापस slots;

	asyh->dp.tu = slots;

	वापस 0;
पूर्ण

अटल u8
nv50_dp_bpc_to_depth(अचिन्हित पूर्णांक bpc)
अणु
	चयन (bpc) अणु
	हाल  6: वापस NV837D_SOR_SET_CONTROL_PIXEL_DEPTH_BPP_18_444;
	हाल  8: वापस NV837D_SOR_SET_CONTROL_PIXEL_DEPTH_BPP_24_444;
	हाल 10:
	शेष: वापस NV837D_SOR_SET_CONTROL_PIXEL_DEPTH_BPP_30_444;
	पूर्ण
पूर्ण

अटल व्योम
nv50_msto_atomic_enable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_msto *msto = nv50_msto(encoder);
	काष्ठा nv50_head *head = msto->head;
	काष्ठा nv50_head_atom *asyh =
		nv50_head_atom(drm_atomic_get_new_crtc_state(state, &head->base.base));
	काष्ठा nv50_mstc *mstc = शून्य;
	काष्ठा nv50_msपंचांग *msपंचांग = शून्य;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	u8 proto;
	bool r;

	drm_connector_list_iter_begin(encoder->dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		अगर (connector->state->best_encoder == &msto->encoder) अणु
			mstc = nv50_mstc(connector);
			msपंचांग = mstc->msपंचांग;
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (WARN_ON(!mstc))
		वापस;

	r = drm_dp_mst_allocate_vcpi(&msपंचांग->mgr, mstc->port, asyh->dp.pbn, asyh->dp.tu);
	अगर (!r)
		DRM_DEBUG_KMS("Failed to allocate VCPI\n");

	अगर (!msपंचांग->links++)
		nv50_outp_acquire(msपंचांग->outp, false /*XXX: MST audio.*/);

	अगर (msपंचांग->outp->link & 1)
		proto = NV917D_SOR_SET_CONTROL_PROTOCOL_DP_A;
	अन्यथा
		proto = NV917D_SOR_SET_CONTROL_PROTOCOL_DP_B;

	msपंचांग->outp->update(msपंचांग->outp, head->base.index, asyh, proto,
			   nv50_dp_bpc_to_depth(asyh->or.bpc));

	msto->mstc = mstc;
	msपंचांग->modअगरied = true;
पूर्ण

अटल व्योम
nv50_msto_atomic_disable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_msto *msto = nv50_msto(encoder);
	काष्ठा nv50_mstc *mstc = msto->mstc;
	काष्ठा nv50_msपंचांग *msपंचांग = mstc->msपंचांग;

	drm_dp_mst_reset_vcpi_slots(&msपंचांग->mgr, mstc->port);

	msपंचांग->outp->update(msपंचांग->outp, msto->head->base.index, शून्य, 0, 0);
	msपंचांग->modअगरied = true;
	अगर (!--msपंचांग->links)
		msपंचांग->disabled = true;
	msto->disabled = true;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
nv50_msto_help = अणु
	.atomic_disable = nv50_msto_atomic_disable,
	.atomic_enable = nv50_msto_atomic_enable,
	.atomic_check = nv50_msto_atomic_check,
पूर्ण;

अटल व्योम
nv50_msto_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nv50_msto *msto = nv50_msto(encoder);
	drm_encoder_cleanup(&msto->encoder);
	kमुक्त(msto);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs
nv50_msto = अणु
	.destroy = nv50_msto_destroy,
पूर्ण;

अटल काष्ठा nv50_msto *
nv50_msto_new(काष्ठा drm_device *dev, काष्ठा nv50_head *head, पूर्णांक id)
अणु
	काष्ठा nv50_msto *msto;
	पूर्णांक ret;

	msto = kzalloc(माप(*msto), GFP_KERNEL);
	अगर (!msto)
		वापस ERR_PTR(-ENOMEM);

	ret = drm_encoder_init(dev, &msto->encoder, &nv50_msto,
			       DRM_MODE_ENCODER_DPMST, "mst-%d", id);
	अगर (ret) अणु
		kमुक्त(msto);
		वापस ERR_PTR(ret);
	पूर्ण

	drm_encoder_helper_add(&msto->encoder, &nv50_msto_help);
	msto->encoder.possible_crtcs = drm_crtc_mask(&head->base.base);
	msto->head = head;
	वापस msto;
पूर्ण

अटल काष्ठा drm_encoder *
nv50_mstc_atomic_best_encoder(काष्ठा drm_connector *connector,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *connector_state = drm_atomic_get_new_connector_state(state,
											 connector);
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	काष्ठा drm_crtc *crtc = connector_state->crtc;

	अगर (!(mstc->msपंचांग->outp->dcb->heads & drm_crtc_mask(crtc)))
		वापस शून्य;

	वापस &nv50_head(crtc)->msto->encoder;
पूर्ण

अटल क्रमागत drm_mode_status
nv50_mstc_mode_valid(काष्ठा drm_connector *connector,
		     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	काष्ठा nouveau_encoder *outp = mstc->msपंचांग->outp;

	/* TODO: calculate the PBN from the करोtघड़ी and validate against the
	 * MSTB's max possible PBN
	 */

	वापस nv50_dp_mode_valid(connector, outp, mode, शून्य);
पूर्ण

अटल पूर्णांक
nv50_mstc_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	पूर्णांक ret = 0;

	mstc->edid = drm_dp_mst_get_edid(&mstc->connector, mstc->port->mgr, mstc->port);
	drm_connector_update_edid_property(&mstc->connector, mstc->edid);
	अगर (mstc->edid)
		ret = drm_add_edid_modes(&mstc->connector, mstc->edid);

	/*
	 * XXX: Since we करोn't use HDR in userspace quite yet, limit the bpc
	 * to 8 to save bandwidth on the topology. In the future, we'll want
	 * to properly fix this by dynamically selecting the highest possible
	 * bpc that would fit in the topology
	 */
	अगर (connector->display_info.bpc)
		connector->display_info.bpc =
			clamp(connector->display_info.bpc, 6U, 8U);
	अन्यथा
		connector->display_info.bpc = 8;

	अगर (mstc->native)
		drm_mode_destroy(mstc->connector.dev, mstc->native);
	mstc->native = nouveau_conn_native_mode(&mstc->connector);
	वापस ret;
पूर्ण

अटल पूर्णांक
nv50_mstc_atomic_check(काष्ठा drm_connector *connector,
		       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	काष्ठा drm_dp_mst_topology_mgr *mgr = &mstc->msपंचांग->mgr;
	काष्ठा drm_connector_state *new_conn_state =
		drm_atomic_get_new_connector_state(state, connector);
	काष्ठा drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(state, connector);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *new_crtc = new_conn_state->crtc;

	अगर (!old_conn_state->crtc)
		वापस 0;

	/* We only want to मुक्त VCPI अगर this state disables the CRTC on this
	 * connector
	 */
	अगर (new_crtc) अणु
		crtc_state = drm_atomic_get_new_crtc_state(state, new_crtc);

		अगर (!crtc_state ||
		    !drm_atomic_crtc_needs_modeset(crtc_state) ||
		    crtc_state->enable)
			वापस 0;
	पूर्ण

	वापस drm_dp_atomic_release_vcpi_slots(state, mgr, mstc->port);
पूर्ण

अटल पूर्णांक
nv50_mstc_detect(काष्ठा drm_connector *connector,
		 काष्ठा drm_modeset_acquire_ctx *ctx, bool क्रमce)
अणु
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);
	पूर्णांक ret;

	अगर (drm_connector_is_unरेजिस्टरed(connector))
		वापस connector_status_disconnected;

	ret = pm_runसमय_get_sync(connector->dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
		वापस connector_status_disconnected;
	पूर्ण

	ret = drm_dp_mst_detect_port(connector, ctx, mstc->port->mgr,
				     mstc->port);
	अगर (ret != connector_status_connected)
		जाओ out;

out:
	pm_runसमय_mark_last_busy(connector->dev->dev);
	pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs
nv50_mstc_help = अणु
	.get_modes = nv50_mstc_get_modes,
	.mode_valid = nv50_mstc_mode_valid,
	.atomic_best_encoder = nv50_mstc_atomic_best_encoder,
	.atomic_check = nv50_mstc_atomic_check,
	.detect_ctx = nv50_mstc_detect,
पूर्ण;

अटल व्योम
nv50_mstc_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा nv50_mstc *mstc = nv50_mstc(connector);

	drm_connector_cleanup(&mstc->connector);
	drm_dp_mst_put_port_दो_स्मृति(mstc->port);

	kमुक्त(mstc);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs
nv50_mstc = अणु
	.reset = nouveau_conn_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = nv50_mstc_destroy,
	.atomic_duplicate_state = nouveau_conn_atomic_duplicate_state,
	.atomic_destroy_state = nouveau_conn_atomic_destroy_state,
	.atomic_set_property = nouveau_conn_atomic_set_property,
	.atomic_get_property = nouveau_conn_atomic_get_property,
पूर्ण;

अटल पूर्णांक
nv50_mstc_new(काष्ठा nv50_msपंचांग *msपंचांग, काष्ठा drm_dp_mst_port *port,
	      स्थिर अक्षर *path, काष्ठा nv50_mstc **pmstc)
अणु
	काष्ठा drm_device *dev = msपंचांग->outp->base.base.dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा nv50_mstc *mstc;
	पूर्णांक ret;

	अगर (!(mstc = *pmstc = kzalloc(माप(*mstc), GFP_KERNEL)))
		वापस -ENOMEM;
	mstc->msपंचांग = msपंचांग;
	mstc->port = port;

	ret = drm_connector_init(dev, &mstc->connector, &nv50_mstc,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		kमुक्त(*pmstc);
		*pmstc = शून्य;
		वापस ret;
	पूर्ण

	drm_connector_helper_add(&mstc->connector, &nv50_mstc_help);

	mstc->connector.funcs->reset(&mstc->connector);
	nouveau_conn_attach_properties(&mstc->connector);

	drm_क्रम_each_crtc(crtc, dev) अणु
		अगर (!(msपंचांग->outp->dcb->heads & drm_crtc_mask(crtc)))
			जारी;

		drm_connector_attach_encoder(&mstc->connector,
					     &nv50_head(crtc)->msto->encoder);
	पूर्ण

	drm_object_attach_property(&mstc->connector.base, dev->mode_config.path_property, 0);
	drm_object_attach_property(&mstc->connector.base, dev->mode_config.tile_property, 0);
	drm_connector_set_path_property(&mstc->connector, path);
	drm_dp_mst_get_port_दो_स्मृति(port);
	वापस 0;
पूर्ण

अटल व्योम
nv50_msपंचांग_cleanup(काष्ठा nv50_msपंचांग *msपंचांग)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(msपंचांग->outp->base.base.dev);
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	NV_ATOMIC(drm, "%s: mstm cleanup\n", msपंचांग->outp->base.base.name);
	ret = drm_dp_check_act_status(&msपंचांग->mgr);

	ret = drm_dp_update_payload_part2(&msपंचांग->mgr);

	drm_क्रम_each_encoder(encoder, msपंचांग->outp->base.base.dev) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_DPMST) अणु
			काष्ठा nv50_msto *msto = nv50_msto(encoder);
			काष्ठा nv50_mstc *mstc = msto->mstc;
			अगर (mstc && mstc->msपंचांग == msपंचांग)
				nv50_msto_cleanup(msto);
		पूर्ण
	पूर्ण

	msपंचांग->modअगरied = false;
पूर्ण

अटल व्योम
nv50_msपंचांग_prepare(काष्ठा nv50_msपंचांग *msपंचांग)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(msपंचांग->outp->base.base.dev);
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret;

	NV_ATOMIC(drm, "%s: mstm prepare\n", msपंचांग->outp->base.base.name);
	ret = drm_dp_update_payload_part1(&msपंचांग->mgr);

	drm_क्रम_each_encoder(encoder, msपंचांग->outp->base.base.dev) अणु
		अगर (encoder->encoder_type == DRM_MODE_ENCODER_DPMST) अणु
			काष्ठा nv50_msto *msto = nv50_msto(encoder);
			काष्ठा nv50_mstc *mstc = msto->mstc;
			अगर (mstc && mstc->msपंचांग == msपंचांग)
				nv50_msto_prepare(msto);
		पूर्ण
	पूर्ण

	अगर (msपंचांग->disabled) अणु
		अगर (!msपंचांग->links)
			nv50_outp_release(msपंचांग->outp);
		msपंचांग->disabled = false;
	पूर्ण
पूर्ण

अटल काष्ठा drm_connector *
nv50_msपंचांग_add_connector(काष्ठा drm_dp_mst_topology_mgr *mgr,
			काष्ठा drm_dp_mst_port *port, स्थिर अक्षर *path)
अणु
	काष्ठा nv50_msपंचांग *msपंचांग = nv50_msपंचांग(mgr);
	काष्ठा nv50_mstc *mstc;
	पूर्णांक ret;

	ret = nv50_mstc_new(msपंचांग, port, path, &mstc);
	अगर (ret)
		वापस शून्य;

	वापस &mstc->connector;
पूर्ण

अटल स्थिर काष्ठा drm_dp_mst_topology_cbs
nv50_msपंचांग = अणु
	.add_connector = nv50_msपंचांग_add_connector,
पूर्ण;

bool
nv50_msपंचांग_service(काष्ठा nouveau_drm *drm,
		  काष्ठा nouveau_connector *nv_connector,
		  काष्ठा nv50_msपंचांग *msपंचांग)
अणु
	काष्ठा drm_dp_aux *aux = &nv_connector->aux;
	bool handled = true, ret = true;
	पूर्णांक rc;
	u8 esi[8] = अणुपूर्ण;

	जबतक (handled) अणु
		rc = drm_dp_dpcd_पढ़ो(aux, DP_SINK_COUNT_ESI, esi, 8);
		अगर (rc != 8) अणु
			ret = false;
			अवरोध;
		पूर्ण

		drm_dp_mst_hpd_irq(&msपंचांग->mgr, esi, &handled);
		अगर (!handled)
			अवरोध;

		rc = drm_dp_dpcd_ग_लिखो(aux, DP_SINK_COUNT_ESI + 1, &esi[1],
				       3);
		अगर (rc != 3) अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ret)
		NV_DEBUG(drm, "Failed to handle ESI on %s: %d\n",
			 nv_connector->base.name, rc);

	वापस ret;
पूर्ण

व्योम
nv50_msपंचांग_हटाओ(काष्ठा nv50_msपंचांग *msपंचांग)
अणु
	msपंचांग->is_mst = false;
	drm_dp_mst_topology_mgr_set_mst(&msपंचांग->mgr, false);
पूर्ण

अटल पूर्णांक
nv50_msपंचांग_enable(काष्ठा nv50_msपंचांग *msपंचांग, पूर्णांक state)
अणु
	काष्ठा nouveau_encoder *outp = msपंचांग->outp;
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_dp_mst_link_v0 mst;
	पूर्ण args = अणु
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_DP_MST_LINK,
		.base.hasht = outp->dcb->hasht,
		.base.hashm = outp->dcb->hashm,
		.mst.state = state,
	पूर्ण;
	काष्ठा nouveau_drm *drm = nouveau_drm(outp->base.base.dev);
	काष्ठा nvअगर_object *disp = &drm->display->disp.object;

	वापस nvअगर_mthd(disp, 0, &args, माप(args));
पूर्ण

पूर्णांक
nv50_msपंचांग_detect(काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा nv50_msपंचांग *msपंचांग = outp->dp.msपंचांग;
	काष्ठा drm_dp_aux *aux;
	पूर्णांक ret;

	अगर (!msपंचांग || !msपंचांग->can_mst)
		वापस 0;

	aux = msपंचांग->mgr.aux;

	/* Clear any leftover MST state we didn't set ourselves by first
	 * disabling MST अगर it was alपढ़ोy enabled
	 */
	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_MSTM_CTRL, 0);
	अगर (ret < 0)
		वापस ret;

	/* And start enabling */
	ret = nv50_msपंचांग_enable(msपंचांग, true);
	अगर (ret)
		वापस ret;

	ret = drm_dp_mst_topology_mgr_set_mst(&msपंचांग->mgr, true);
	अगर (ret) अणु
		nv50_msपंचांग_enable(msपंचांग, false);
		वापस ret;
	पूर्ण

	msपंचांग->is_mst = true;
	वापस 1;
पूर्ण

अटल व्योम
nv50_msपंचांग_fini(काष्ठा nouveau_encoder *outp)
अणु
	काष्ठा nv50_msपंचांग *msपंचांग = outp->dp.msपंचांग;

	अगर (!msपंचांग)
		वापस;

	/* Don't change the MST state of this connector until we've finished
	 * resuming, since we can't safely grab hpd_irq_lock in our resume
	 * path to protect msपंचांग->is_mst without potentially deadlocking
	 */
	mutex_lock(&outp->dp.hpd_irq_lock);
	msपंचांग->suspended = true;
	mutex_unlock(&outp->dp.hpd_irq_lock);

	अगर (msपंचांग->is_mst)
		drm_dp_mst_topology_mgr_suspend(&msपंचांग->mgr);
पूर्ण

अटल व्योम
nv50_msपंचांग_init(काष्ठा nouveau_encoder *outp, bool runसमय)
अणु
	काष्ठा nv50_msपंचांग *msपंचांग = outp->dp.msपंचांग;
	पूर्णांक ret = 0;

	अगर (!msपंचांग)
		वापस;

	अगर (msपंचांग->is_mst) अणु
		ret = drm_dp_mst_topology_mgr_resume(&msपंचांग->mgr, !runसमय);
		अगर (ret == -1)
			nv50_msपंचांग_हटाओ(msपंचांग);
	पूर्ण

	mutex_lock(&outp->dp.hpd_irq_lock);
	msपंचांग->suspended = false;
	mutex_unlock(&outp->dp.hpd_irq_lock);

	अगर (ret == -1)
		drm_kms_helper_hotplug_event(msपंचांग->mgr.dev);
पूर्ण

अटल व्योम
nv50_msपंचांग_del(काष्ठा nv50_msपंचांग **pmsपंचांग)
अणु
	काष्ठा nv50_msपंचांग *msपंचांग = *pmsपंचांग;
	अगर (msपंचांग) अणु
		drm_dp_mst_topology_mgr_destroy(&msपंचांग->mgr);
		kमुक्त(*pmsपंचांग);
		*pmsपंचांग = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
nv50_msपंचांग_new(काष्ठा nouveau_encoder *outp, काष्ठा drm_dp_aux *aux, पूर्णांक aux_max,
	      पूर्णांक conn_base_id, काष्ठा nv50_msपंचांग **pmsपंचांग)
अणु
	स्थिर पूर्णांक max_payloads = hweight8(outp->dcb->heads);
	काष्ठा drm_device *dev = outp->base.base.dev;
	काष्ठा nv50_msपंचांग *msपंचांग;
	पूर्णांक ret;

	अगर (!(msपंचांग = *pmsपंचांग = kzalloc(माप(*msपंचांग), GFP_KERNEL)))
		वापस -ENOMEM;
	msपंचांग->outp = outp;
	msपंचांग->mgr.cbs = &nv50_msपंचांग;

	ret = drm_dp_mst_topology_mgr_init(&msपंचांग->mgr, dev, aux, aux_max,
					   max_payloads, conn_base_id);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/******************************************************************************
 * SOR
 *****************************************************************************/
अटल व्योम
nv50_sor_update(काष्ठा nouveau_encoder *nv_encoder, u8 head,
		काष्ठा nv50_head_atom *asyh, u8 proto, u8 depth)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(nv_encoder->base.base.dev);
	काष्ठा nv50_core *core = disp->core;

	अगर (!asyh) अणु
		nv_encoder->ctrl &= ~BIT(head);
		अगर (NVDEF_TEST(nv_encoder->ctrl, NV507D, SOR_SET_CONTROL, OWNER, ==, NONE))
			nv_encoder->ctrl = 0;
	पूर्ण अन्यथा अणु
		nv_encoder->ctrl |= NVVAL(NV507D, SOR_SET_CONTROL, PROTOCOL, proto);
		nv_encoder->ctrl |= BIT(head);
		asyh->or.depth = depth;
	पूर्ण

	core->func->sor->ctrl(core, nv_encoder->or, nv_encoder->ctrl, asyh);
पूर्ण

अटल व्योम
nv50_sor_atomic_disable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_crtc *nv_crtc = nouveau_crtc(nv_encoder->crtc);
	काष्ठा nouveau_connector *nv_connector = nv50_outp_get_old_connector(state, nv_encoder);
	काष्ठा drm_dp_aux *aux = &nv_connector->aux;
	u8 pwr;

	अगर (nv_encoder->dcb->type == DCB_OUTPUT_DP) अणु
		पूर्णांक ret = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &pwr);

		अगर (ret == 0) अणु
			pwr &= ~DP_SET_POWER_MASK;
			pwr |=  DP_SET_POWER_D3;
			drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, pwr);
		पूर्ण
	पूर्ण

	nv_encoder->update(nv_encoder, nv_crtc->index, शून्य, 0, 0);
	nv50_audio_disable(encoder, nv_crtc);
	nv50_hdmi_disable(&nv_encoder->base.base, nv_crtc);
	nv50_outp_release(nv_encoder);
	nv_encoder->crtc = शून्य;
पूर्ण

अटल व्योम
nv50_sor_atomic_enable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_crtc *nv_crtc = nv50_outp_get_new_crtc(state, nv_encoder);
	काष्ठा nv50_head_atom *asyh =
		nv50_head_atom(drm_atomic_get_new_crtc_state(state, &nv_crtc->base));
	काष्ठा drm_display_mode *mode = &asyh->state.adjusted_mode;
	काष्ठा अणु
		काष्ठा nv50_disp_mthd_v1 base;
		काष्ठा nv50_disp_sor_lvds_script_v0 lvds;
	पूर्ण lvds = अणु
		.base.version = 1,
		.base.method  = NV50_DISP_MTHD_V1_SOR_LVDS_SCRIPT,
		.base.hasht   = nv_encoder->dcb->hasht,
		.base.hashm   = nv_encoder->dcb->hashm,
	पूर्ण;
	काष्ठा nv50_disp *disp = nv50_disp(encoder->dev);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_connector *nv_connector;
	काष्ठा nvbios *bios = &drm->vbios;
	bool hda = false;
	u8 proto = NV507D_SOR_SET_CONTROL_PROTOCOL_CUSTOM;
	u8 depth = NV837D_SOR_SET_CONTROL_PIXEL_DEPTH_DEFAULT;

	nv_connector = nv50_outp_get_new_connector(state, nv_encoder);
	nv_encoder->crtc = &nv_crtc->base;

	अगर ((disp->disp->object.oclass == GT214_DISP ||
	     disp->disp->object.oclass >= GF110_DISP) &&
	    drm_detect_monitor_audio(nv_connector->edid))
		hda = true;
	nv50_outp_acquire(nv_encoder, hda);

	चयन (nv_encoder->dcb->type) अणु
	हाल DCB_OUTPUT_TMDS:
		अगर (nv_encoder->link & 1) अणु
			proto = NV507D_SOR_SET_CONTROL_PROTOCOL_SINGLE_TMDS_A;
			/* Only enable dual-link अगर:
			 *  - Need to (i.e. rate > 165MHz)
			 *  - DCB says we can
			 *  - Not an HDMI monitor, since there's no dual-link
			 *    on HDMI.
			 */
			अगर (mode->घड़ी >= 165000 &&
			    nv_encoder->dcb->duallink_possible &&
			    !drm_detect_hdmi_monitor(nv_connector->edid))
				proto = NV507D_SOR_SET_CONTROL_PROTOCOL_DUAL_TMDS;
		पूर्ण अन्यथा अणु
			proto = NV507D_SOR_SET_CONTROL_PROTOCOL_SINGLE_TMDS_B;
		पूर्ण

		nv50_hdmi_enable(&nv_encoder->base.base, nv_crtc, nv_connector, state, mode);
		अवरोध;
	हाल DCB_OUTPUT_LVDS:
		proto = NV507D_SOR_SET_CONTROL_PROTOCOL_LVDS_CUSTOM;

		अगर (bios->fp_no_ddc) अणु
			अगर (bios->fp.dual_link)
				lvds.lvds.script |= 0x0100;
			अगर (bios->fp.अगर_is_24bit)
				lvds.lvds.script |= 0x0200;
		पूर्ण अन्यथा अणु
			अगर (nv_connector->type == DCB_CONNECTOR_LVDS_SPWG) अणु
				अगर (((u8 *)nv_connector->edid)[121] == 2)
					lvds.lvds.script |= 0x0100;
			पूर्ण अन्यथा
			अगर (mode->घड़ी >= bios->fp.duallink_transition_clk) अणु
				lvds.lvds.script |= 0x0100;
			पूर्ण

			अगर (lvds.lvds.script & 0x0100) अणु
				अगर (bios->fp.strapless_is_24bit & 2)
					lvds.lvds.script |= 0x0200;
			पूर्ण अन्यथा अणु
				अगर (bios->fp.strapless_is_24bit & 1)
					lvds.lvds.script |= 0x0200;
			पूर्ण

			अगर (asyh->or.bpc == 8)
				lvds.lvds.script |= 0x0200;
		पूर्ण

		nvअगर_mthd(&disp->disp->object, 0, &lvds, माप(lvds));
		अवरोध;
	हाल DCB_OUTPUT_DP:
		depth = nv50_dp_bpc_to_depth(asyh->or.bpc);

		अगर (nv_encoder->link & 1)
			proto = NV887D_SOR_SET_CONTROL_PROTOCOL_DP_A;
		अन्यथा
			proto = NV887D_SOR_SET_CONTROL_PROTOCOL_DP_B;

		nv50_audio_enable(encoder, nv_crtc, nv_connector, state, mode);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	nv_encoder->update(nv_encoder, nv_crtc->index, asyh, proto, depth);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
nv50_sor_help = अणु
	.atomic_check = nv50_outp_atomic_check,
	.atomic_enable = nv50_sor_atomic_enable,
	.atomic_disable = nv50_sor_atomic_disable,
पूर्ण;

अटल व्योम
nv50_sor_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	nv50_msपंचांग_del(&nv_encoder->dp.msपंचांग);
	drm_encoder_cleanup(encoder);

	अगर (nv_encoder->dcb->type == DCB_OUTPUT_DP)
		mutex_destroy(&nv_encoder->dp.hpd_irq_lock);

	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs
nv50_sor_func = अणु
	.destroy = nv50_sor_destroy,
पूर्ण;

अटल bool nv50_has_mst(काष्ठा nouveau_drm *drm)
अणु
	काष्ठा nvkm_bios *bios = nvxx_bios(&drm->client.device);
	u32 data;
	u8 ver, hdr, cnt, len;

	data = nvbios_dp_table(bios, &ver, &hdr, &cnt, &len);
	वापस data && ver >= 0x40 && (nvbios_rd08(bios, data + 0x08) & 0x04);
पूर्ण

अटल पूर्णांक
nv50_sor_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *dcbe)
अणु
	काष्ठा nouveau_connector *nv_connector = nouveau_connector(connector);
	काष्ठा nouveau_drm *drm = nouveau_drm(connector->dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा drm_encoder *encoder;
	काष्ठा nv50_disp *disp = nv50_disp(connector->dev);
	पूर्णांक type, ret;

	चयन (dcbe->type) अणु
	हाल DCB_OUTPUT_LVDS: type = DRM_MODE_ENCODER_LVDS; अवरोध;
	हाल DCB_OUTPUT_TMDS:
	हाल DCB_OUTPUT_DP:
	शेष:
		type = DRM_MODE_ENCODER_TMDS;
		अवरोध;
	पूर्ण

	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;
	nv_encoder->dcb = dcbe;
	nv_encoder->update = nv50_sor_update;

	encoder = to_drm_encoder(nv_encoder);
	encoder->possible_crtcs = dcbe->heads;
	encoder->possible_clones = 0;
	drm_encoder_init(connector->dev, encoder, &nv50_sor_func, type,
			 "sor-%04x-%04x", dcbe->hasht, dcbe->hashm);
	drm_encoder_helper_add(encoder, &nv50_sor_help);

	drm_connector_attach_encoder(connector, encoder);

	disp->core->func->sor->get_caps(disp, nv_encoder, ffs(dcbe->or) - 1);
	nv50_outp_dump_caps(drm, nv_encoder);

	अगर (dcbe->type == DCB_OUTPUT_DP) अणु
		काष्ठा nvkm_i2c_aux *aux =
			nvkm_i2c_aux_find(i2c, dcbe->i2c_index);

		mutex_init(&nv_encoder->dp.hpd_irq_lock);

		अगर (aux) अणु
			अगर (disp->disp->object.oclass < GF110_DISP) अणु
				/* HW has no support क्रम address-only
				 * transactions, so we're required to
				 * use custom I2C-over-AUX code.
				 */
				nv_encoder->i2c = &aux->i2c;
			पूर्ण अन्यथा अणु
				nv_encoder->i2c = &nv_connector->aux.ddc;
			पूर्ण
			nv_encoder->aux = aux;
		पूर्ण

		अगर (nv_connector->type != DCB_CONNECTOR_eDP &&
		    nv50_has_mst(drm)) अणु
			ret = nv50_msपंचांग_new(nv_encoder, &nv_connector->aux,
					    16, nv_connector->base.base.id,
					    &nv_encoder->dp.msपंचांग);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा nvkm_i2c_bus *bus =
			nvkm_i2c_bus_find(i2c, dcbe->i2c_index);
		अगर (bus)
			nv_encoder->i2c = &bus->i2c;
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 * PIOR
 *****************************************************************************/
अटल पूर्णांक
nv50_pior_atomic_check(काष्ठा drm_encoder *encoder,
		       काष्ठा drm_crtc_state *crtc_state,
		       काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांक ret = nv50_outp_atomic_check(encoder, crtc_state, conn_state);
	अगर (ret)
		वापस ret;
	crtc_state->adjusted_mode.घड़ी *= 2;
	वापस 0;
पूर्ण

अटल व्योम
nv50_pior_atomic_disable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nv50_core *core = nv50_disp(encoder->dev)->core;
	स्थिर u32 ctrl = NVDEF(NV507D, PIOR_SET_CONTROL, OWNER, NONE);

	core->func->pior->ctrl(core, nv_encoder->or, ctrl, शून्य);
	nv_encoder->crtc = शून्य;
	nv50_outp_release(nv_encoder);
पूर्ण

अटल व्योम
nv50_pior_atomic_enable(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	काष्ठा nouveau_crtc *nv_crtc = nv50_outp_get_new_crtc(state, nv_encoder);
	काष्ठा nv50_head_atom *asyh =
		nv50_head_atom(drm_atomic_get_new_crtc_state(state, &nv_crtc->base));
	काष्ठा nv50_core *core = nv50_disp(encoder->dev)->core;
	u32 ctrl = 0;

	चयन (nv_crtc->index) अणु
	हाल 0: ctrl |= NVDEF(NV507D, PIOR_SET_CONTROL, OWNER, HEAD0); अवरोध;
	हाल 1: ctrl |= NVDEF(NV507D, PIOR_SET_CONTROL, OWNER, HEAD1); अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	nv50_outp_acquire(nv_encoder, false);

	चयन (asyh->or.bpc) अणु
	हाल 10: asyh->or.depth = NV837D_PIOR_SET_CONTROL_PIXEL_DEPTH_BPP_30_444; अवरोध;
	हाल  8: asyh->or.depth = NV837D_PIOR_SET_CONTROL_PIXEL_DEPTH_BPP_24_444; अवरोध;
	हाल  6: asyh->or.depth = NV837D_PIOR_SET_CONTROL_PIXEL_DEPTH_BPP_18_444; अवरोध;
	शेष: asyh->or.depth = NV837D_PIOR_SET_CONTROL_PIXEL_DEPTH_DEFAULT; अवरोध;
	पूर्ण

	चयन (nv_encoder->dcb->type) अणु
	हाल DCB_OUTPUT_TMDS:
	हाल DCB_OUTPUT_DP:
		ctrl |= NVDEF(NV507D, PIOR_SET_CONTROL, PROTOCOL, EXT_TMDS_ENC);
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	core->func->pior->ctrl(core, nv_encoder->or, ctrl, asyh);
	nv_encoder->crtc = &nv_crtc->base;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
nv50_pior_help = अणु
	.atomic_check = nv50_pior_atomic_check,
	.atomic_enable = nv50_pior_atomic_enable,
	.atomic_disable = nv50_pior_atomic_disable,
पूर्ण;

अटल व्योम
nv50_pior_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs
nv50_pior_func = अणु
	.destroy = nv50_pior_destroy,
पूर्ण;

अटल पूर्णांक
nv50_pior_create(काष्ठा drm_connector *connector, काष्ठा dcb_output *dcbe)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	काष्ठा nvkm_i2c *i2c = nvxx_i2c(&drm->client.device);
	काष्ठा nvkm_i2c_bus *bus = शून्य;
	काष्ठा nvkm_i2c_aux *aux = शून्य;
	काष्ठा i2c_adapter *ddc;
	काष्ठा nouveau_encoder *nv_encoder;
	काष्ठा drm_encoder *encoder;
	पूर्णांक type;

	चयन (dcbe->type) अणु
	हाल DCB_OUTPUT_TMDS:
		bus  = nvkm_i2c_bus_find(i2c, NVKM_I2C_BUS_EXT(dcbe->extdev));
		ddc  = bus ? &bus->i2c : शून्य;
		type = DRM_MODE_ENCODER_TMDS;
		अवरोध;
	हाल DCB_OUTPUT_DP:
		aux  = nvkm_i2c_aux_find(i2c, NVKM_I2C_AUX_EXT(dcbe->extdev));
		ddc  = aux ? &aux->i2c : शून्य;
		type = DRM_MODE_ENCODER_TMDS;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	nv_encoder = kzalloc(माप(*nv_encoder), GFP_KERNEL);
	अगर (!nv_encoder)
		वापस -ENOMEM;
	nv_encoder->dcb = dcbe;
	nv_encoder->i2c = ddc;
	nv_encoder->aux = aux;

	encoder = to_drm_encoder(nv_encoder);
	encoder->possible_crtcs = dcbe->heads;
	encoder->possible_clones = 0;
	drm_encoder_init(connector->dev, encoder, &nv50_pior_func, type,
			 "pior-%04x-%04x", dcbe->hasht, dcbe->hashm);
	drm_encoder_helper_add(encoder, &nv50_pior_help);

	drm_connector_attach_encoder(connector, encoder);

	disp->core->func->pior->get_caps(disp, nv_encoder, ffs(dcbe->or) - 1);
	nv50_outp_dump_caps(drm, nv_encoder);

	वापस 0;
पूर्ण

/******************************************************************************
 * Atomic
 *****************************************************************************/

अटल व्योम
nv50_disp_atomic_commit_core(काष्ठा drm_atomic_state *state, u32 *पूर्णांकerlock)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(state->dev);
	काष्ठा nv50_disp *disp = nv50_disp(drm->dev);
	काष्ठा nv50_core *core = disp->core;
	काष्ठा nv50_msपंचांग *msपंचांग;
	काष्ठा drm_encoder *encoder;

	NV_ATOMIC(drm, "commit core %08x\n", पूर्णांकerlock[NV50_DISP_INTERLOCK_BASE]);

	drm_क्रम_each_encoder(encoder, drm->dev) अणु
		अगर (encoder->encoder_type != DRM_MODE_ENCODER_DPMST) अणु
			msपंचांग = nouveau_encoder(encoder)->dp.msपंचांग;
			अगर (msपंचांग && msपंचांग->modअगरied)
				nv50_msपंचांग_prepare(msपंचांग);
		पूर्ण
	पूर्ण

	core->func->ntfy_init(disp->sync, NV50_DISP_CORE_NTFY);
	core->func->update(core, पूर्णांकerlock, true);
	अगर (core->func->ntfy_रुको_करोne(disp->sync, NV50_DISP_CORE_NTFY,
				       disp->core->chan.base.device))
		NV_ERROR(drm, "core notifier timeout\n");

	drm_क्रम_each_encoder(encoder, drm->dev) अणु
		अगर (encoder->encoder_type != DRM_MODE_ENCODER_DPMST) अणु
			msपंचांग = nouveau_encoder(encoder)->dp.msपंचांग;
			अगर (msपंचांग && msपंचांग->modअगरied)
				nv50_msपंचांग_cleanup(msपंचांग);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nv50_disp_atomic_commit_wndw(काष्ठा drm_atomic_state *state, u32 *पूर्णांकerlock)
अणु
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा drm_plane *plane;
	पूर्णांक i;

	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
		अगर (पूर्णांकerlock[wndw->पूर्णांकerlock.type] & wndw->पूर्णांकerlock.data) अणु
			अगर (wndw->func->update)
				wndw->func->update(wndw, पूर्णांकerlock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nv50_disp_atomic_commit_tail(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->dev;
	काष्ठा drm_crtc_state *new_crtc_state, *old_crtc_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा drm_plane *plane;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nv50_disp *disp = nv50_disp(dev);
	काष्ठा nv50_atom *atom = nv50_atom(state);
	काष्ठा nv50_core *core = disp->core;
	काष्ठा nv50_outp_atom *outp, *outt;
	u32 पूर्णांकerlock[NV50_DISP_INTERLOCK__SIZE] = अणुपूर्ण;
	पूर्णांक i;
	bool flushed = false;

	NV_ATOMIC(drm, "commit %d %d\n", atom->lock_core, atom->flush_disable);
	nv50_crc_atomic_stop_reporting(state);
	drm_atomic_helper_रुको_क्रम_fences(dev, state, false);
	drm_atomic_helper_रुको_क्रम_dependencies(state);
	drm_atomic_helper_update_legacy_modeset_state(dev, state);
	drm_atomic_helper_calc_बारtamping_स्थिरants(state);

	अगर (atom->lock_core)
		mutex_lock(&disp->mutex);

	/* Disable head(s). */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(new_crtc_state);
		काष्ठा nv50_head *head = nv50_head(crtc);

		NV_ATOMIC(drm, "%s: clr %04x (set %04x)\n", crtc->name,
			  asyh->clr.mask, asyh->set.mask);

		अगर (old_crtc_state->active && !new_crtc_state->active) अणु
			pm_runसमय_put_noidle(dev->dev);
			drm_crtc_vblank_off(crtc);
		पूर्ण

		अगर (asyh->clr.mask) अणु
			nv50_head_flush_clr(head, asyh, atom->flush_disable);
			पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE] |= 1;
		पूर्ण
	पूर्ण

	/* Disable plane(s). */
	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(new_plane_state);
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);

		NV_ATOMIC(drm, "%s: clr %02x (set %02x)\n", plane->name,
			  asyw->clr.mask, asyw->set.mask);
		अगर (!asyw->clr.mask)
			जारी;

		nv50_wndw_flush_clr(wndw, पूर्णांकerlock, atom->flush_disable, asyw);
	पूर्ण

	/* Disable output path(s). */
	list_क्रम_each_entry(outp, &atom->outp, head) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *help;
		काष्ठा drm_encoder *encoder;

		encoder = outp->encoder;
		help = encoder->helper_निजी;

		NV_ATOMIC(drm, "%s: clr %02x (set %02x)\n", encoder->name,
			  outp->clr.mask, outp->set.mask);

		अगर (outp->clr.mask) अणु
			help->atomic_disable(encoder, state);
			पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE] |= 1;
			अगर (outp->flush_disable) अणु
				nv50_disp_atomic_commit_wndw(state, पूर्णांकerlock);
				nv50_disp_atomic_commit_core(state, पूर्णांकerlock);
				स_रखो(पूर्णांकerlock, 0x00, माप(पूर्णांकerlock));

				flushed = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Flush disable. */
	अगर (पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE]) अणु
		अगर (atom->flush_disable) अणु
			nv50_disp_atomic_commit_wndw(state, पूर्णांकerlock);
			nv50_disp_atomic_commit_core(state, पूर्णांकerlock);
			स_रखो(पूर्णांकerlock, 0x00, माप(पूर्णांकerlock));

			flushed = true;
		पूर्ण
	पूर्ण

	अगर (flushed)
		nv50_crc_atomic_release_notअगरier_contexts(state);
	nv50_crc_atomic_init_notअगरier_contexts(state);

	/* Update output path(s). */
	list_क्रम_each_entry_safe(outp, outt, &atom->outp, head) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *help;
		काष्ठा drm_encoder *encoder;

		encoder = outp->encoder;
		help = encoder->helper_निजी;

		NV_ATOMIC(drm, "%s: set %02x (clr %02x)\n", encoder->name,
			  outp->set.mask, outp->clr.mask);

		अगर (outp->set.mask) अणु
			help->atomic_enable(encoder, state);
			पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE] = 1;
		पूर्ण

		list_del(&outp->head);
		kमुक्त(outp);
	पूर्ण

	/* Update head(s). */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		काष्ठा nv50_head_atom *asyh = nv50_head_atom(new_crtc_state);
		काष्ठा nv50_head *head = nv50_head(crtc);

		NV_ATOMIC(drm, "%s: set %04x (clr %04x)\n", crtc->name,
			  asyh->set.mask, asyh->clr.mask);

		अगर (asyh->set.mask) अणु
			nv50_head_flush_set(head, asyh);
			पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE] = 1;
		पूर्ण

		अगर (new_crtc_state->active) अणु
			अगर (!old_crtc_state->active) अणु
				drm_crtc_vblank_on(crtc);
				pm_runसमय_get_noresume(dev->dev);
			पूर्ण
			अगर (new_crtc_state->event)
				drm_crtc_vblank_get(crtc);
		पूर्ण
	पूर्ण

	/* Update winकरोw->head assignment.
	 *
	 * This has to happen in an update that's not पूर्णांकerlocked with
	 * any winकरोw channels to aव्योम hitting HW error checks.
	 *
	 *TODO: Proper handling of winकरोw ownership (Turing apparently
	 *      supports non-fixed mappings).
	 */
	अगर (core->assign_winकरोws) अणु
		core->func->wndw.owner(core);
		nv50_disp_atomic_commit_core(state, पूर्णांकerlock);
		core->assign_winकरोws = false;
		पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE] = 0;
	पूर्ण

	/* Update plane(s). */
	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(new_plane_state);
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);

		NV_ATOMIC(drm, "%s: set %02x (clr %02x)\n", plane->name,
			  asyw->set.mask, asyw->clr.mask);
		अगर ( !asyw->set.mask &&
		    (!asyw->clr.mask || atom->flush_disable))
			जारी;

		nv50_wndw_flush_set(wndw, पूर्णांकerlock, asyw);
	पूर्ण

	/* Flush update. */
	nv50_disp_atomic_commit_wndw(state, पूर्णांकerlock);

	अगर (पूर्णांकerlock[NV50_DISP_INTERLOCK_CORE]) अणु
		अगर (पूर्णांकerlock[NV50_DISP_INTERLOCK_BASE] ||
		    पूर्णांकerlock[NV50_DISP_INTERLOCK_OVLY] ||
		    पूर्णांकerlock[NV50_DISP_INTERLOCK_WNDW] ||
		    !atom->state.legacy_cursor_update)
			nv50_disp_atomic_commit_core(state, पूर्णांकerlock);
		अन्यथा
			disp->core->func->update(disp->core, पूर्णांकerlock, false);
	पूर्ण

	अगर (atom->lock_core)
		mutex_unlock(&disp->mutex);

	/* Wait क्रम HW to संकेत completion. */
	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(new_plane_state);
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
		पूर्णांक ret = nv50_wndw_रुको_armed(wndw, asyw);
		अगर (ret)
			NV_ERROR(drm, "%s: timeout\n", plane->name);
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->event) अणु
			अचिन्हित दीर्घ flags;
			/* Get correct count/ts अगर racing with vblank irq */
			अगर (new_crtc_state->active)
				drm_crtc_accurate_vblank_count(crtc);
			spin_lock_irqsave(&crtc->dev->event_lock, flags);
			drm_crtc_send_vblank_event(crtc, new_crtc_state->event);
			spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

			new_crtc_state->event = शून्य;
			अगर (new_crtc_state->active)
				drm_crtc_vblank_put(crtc);
		पूर्ण
	पूर्ण

	nv50_crc_atomic_start_reporting(state);
	अगर (!flushed)
		nv50_crc_atomic_release_notअगरier_contexts(state);
	drm_atomic_helper_commit_hw_करोne(state);
	drm_atomic_helper_cleanup_planes(dev, state);
	drm_atomic_helper_commit_cleanup_करोne(state);
	drm_atomic_state_put(state);

	/* Drop the RPM ref we got from nv50_disp_atomic_commit() */
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);
पूर्ण

अटल व्योम
nv50_disp_atomic_commit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_atomic_state *state =
		container_of(work, typeof(*state), commit_work);
	nv50_disp_atomic_commit_tail(state);
पूर्ण

अटल पूर्णांक
nv50_disp_atomic_commit(काष्ठा drm_device *dev,
			काष्ठा drm_atomic_state *state, bool nonblock)
अणु
	काष्ठा drm_plane_state *new_plane_state;
	काष्ठा drm_plane *plane;
	पूर्णांक ret, i;

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस ret;
	पूर्ण

	ret = drm_atomic_helper_setup_commit(state, nonblock);
	अगर (ret)
		जाओ करोne;

	INIT_WORK(&state->commit_work, nv50_disp_atomic_commit_work);

	ret = drm_atomic_helper_prepare_planes(dev, state);
	अगर (ret)
		जाओ करोne;

	अगर (!nonblock) अणु
		ret = drm_atomic_helper_रुको_क्रम_fences(dev, state, true);
		अगर (ret)
			जाओ err_cleanup;
	पूर्ण

	ret = drm_atomic_helper_swap_state(state, true);
	अगर (ret)
		जाओ err_cleanup;

	क्रम_each_new_plane_in_state(state, plane, new_plane_state, i) अणु
		काष्ठा nv50_wndw_atom *asyw = nv50_wndw_atom(new_plane_state);
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);

		अगर (asyw->set.image)
			nv50_wndw_ntfy_enable(wndw, asyw);
	पूर्ण

	drm_atomic_state_get(state);

	/*
	 * Grab another RPM ref क्रम the commit tail, which will release the
	 * ref when it's finished
	 */
	pm_runसमय_get_noresume(dev->dev);

	अगर (nonblock)
		queue_work(प्रणाली_unbound_wq, &state->commit_work);
	अन्यथा
		nv50_disp_atomic_commit_tail(state);

err_cleanup:
	अगर (ret)
		drm_atomic_helper_cleanup_planes(dev, state);
करोne:
	pm_runसमय_put_स्वतःsuspend(dev->dev);
	वापस ret;
पूर्ण

अटल काष्ठा nv50_outp_atom *
nv50_disp_outp_atomic_add(काष्ठा nv50_atom *atom, काष्ठा drm_encoder *encoder)
अणु
	काष्ठा nv50_outp_atom *outp;

	list_क्रम_each_entry(outp, &atom->outp, head) अणु
		अगर (outp->encoder == encoder)
			वापस outp;
	पूर्ण

	outp = kzalloc(माप(*outp), GFP_KERNEL);
	अगर (!outp)
		वापस ERR_PTR(-ENOMEM);

	list_add(&outp->head, &atom->outp);
	outp->encoder = encoder;
	वापस outp;
पूर्ण

अटल पूर्णांक
nv50_disp_outp_atomic_check_clr(काष्ठा nv50_atom *atom,
				काष्ठा drm_connector_state *old_connector_state)
अणु
	काष्ठा drm_encoder *encoder = old_connector_state->best_encoder;
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा nv50_outp_atom *outp;

	अगर (!(crtc = old_connector_state->crtc))
		वापस 0;

	old_crtc_state = drm_atomic_get_old_crtc_state(&atom->state, crtc);
	new_crtc_state = drm_atomic_get_new_crtc_state(&atom->state, crtc);
	अगर (old_crtc_state->active && drm_atomic_crtc_needs_modeset(new_crtc_state)) अणु
		outp = nv50_disp_outp_atomic_add(atom, encoder);
		अगर (IS_ERR(outp))
			वापस PTR_ERR(outp);

		अगर (outp->encoder->encoder_type == DRM_MODE_ENCODER_DPMST) अणु
			outp->flush_disable = true;
			atom->flush_disable = true;
		पूर्ण
		outp->clr.ctrl = true;
		atom->lock_core = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_outp_atomic_check_set(काष्ठा nv50_atom *atom,
				काष्ठा drm_connector_state *connector_state)
अणु
	काष्ठा drm_encoder *encoder = connector_state->best_encoder;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा nv50_outp_atom *outp;

	अगर (!(crtc = connector_state->crtc))
		वापस 0;

	new_crtc_state = drm_atomic_get_new_crtc_state(&atom->state, crtc);
	अगर (new_crtc_state->active && drm_atomic_crtc_needs_modeset(new_crtc_state)) अणु
		outp = nv50_disp_outp_atomic_add(atom, encoder);
		अगर (IS_ERR(outp))
			वापस PTR_ERR(outp);

		outp->set.ctrl = true;
		atom->lock_core = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_atomic_check(काष्ठा drm_device *dev, काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_atom *atom = nv50_atom(state);
	काष्ठा nv50_core *core = nv50_disp(dev)->core;
	काष्ठा drm_connector_state *old_connector_state, *new_connector_state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_crtc *crtc;
	काष्ठा nv50_head *head;
	काष्ठा nv50_head_atom *asyh;
	पूर्णांक ret, i;

	अगर (core->assign_winकरोws && core->func->head->अटल_wndw_map) अणु
		drm_क्रम_each_crtc(crtc, dev) अणु
			new_crtc_state = drm_atomic_get_crtc_state(state,
								   crtc);
			अगर (IS_ERR(new_crtc_state))
				वापस PTR_ERR(new_crtc_state);

			head = nv50_head(crtc);
			asyh = nv50_head_atom(new_crtc_state);
			core->func->head->अटल_wndw_map(head, asyh);
		पूर्ण
	पूर्ण

	/* We need to handle colour management on a per-plane basis. */
	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->color_mgmt_changed) अणु
			ret = drm_atomic_add_affected_planes(state, crtc);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = drm_atomic_helper_check(dev, state);
	अगर (ret)
		वापस ret;

	क्रम_each_oldnew_connector_in_state(state, connector, old_connector_state, new_connector_state, i) अणु
		ret = nv50_disp_outp_atomic_check_clr(atom, old_connector_state);
		अगर (ret)
			वापस ret;

		ret = nv50_disp_outp_atomic_check_set(atom, new_connector_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = drm_dp_mst_atomic_check(state);
	अगर (ret)
		वापस ret;

	nv50_crc_atomic_check_outp(atom);

	वापस 0;
पूर्ण

अटल व्योम
nv50_disp_atomic_state_clear(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_atom *atom = nv50_atom(state);
	काष्ठा nv50_outp_atom *outp, *outt;

	list_क्रम_each_entry_safe(outp, outt, &atom->outp, head) अणु
		list_del(&outp->head);
		kमुक्त(outp);
	पूर्ण

	drm_atomic_state_शेष_clear(state);
पूर्ण

अटल व्योम
nv50_disp_atomic_state_मुक्त(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा nv50_atom *atom = nv50_atom(state);
	drm_atomic_state_शेष_release(&atom->state);
	kमुक्त(atom);
पूर्ण

अटल काष्ठा drm_atomic_state *
nv50_disp_atomic_state_alloc(काष्ठा drm_device *dev)
अणु
	काष्ठा nv50_atom *atom;
	अगर (!(atom = kzalloc(माप(*atom), GFP_KERNEL)) ||
	    drm_atomic_state_init(dev, &atom->state) < 0) अणु
		kमुक्त(atom);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&atom->outp);
	वापस &atom->state;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs
nv50_disp_func = अणु
	.fb_create = nouveau_user_framebuffer_create,
	.output_poll_changed = nouveau_fbcon_output_poll_changed,
	.atomic_check = nv50_disp_atomic_check,
	.atomic_commit = nv50_disp_atomic_commit,
	.atomic_state_alloc = nv50_disp_atomic_state_alloc,
	.atomic_state_clear = nv50_disp_atomic_state_clear,
	.atomic_state_मुक्त = nv50_disp_atomic_state_मुक्त,
पूर्ण;

/******************************************************************************
 * Init
 *****************************************************************************/

अटल व्योम
nv50_display_fini(काष्ठा drm_device *dev, bool runसमय, bool suspend)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_plane *plane;

	drm_क्रम_each_plane(plane, dev) अणु
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
		अगर (plane->funcs != &nv50_wndw)
			जारी;
		nv50_wndw_fini(wndw);
	पूर्ण

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->encoder_type != DRM_MODE_ENCODER_DPMST)
			nv50_msपंचांग_fini(nouveau_encoder(encoder));
	पूर्ण

	अगर (!runसमय)
		cancel_work_sync(&drm->hpd_work);
पूर्ण

अटल पूर्णांक
nv50_display_init(काष्ठा drm_device *dev, bool resume, bool runसमय)
अणु
	काष्ठा nv50_core *core = nv50_disp(dev)->core;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_plane *plane;

	अगर (resume || runसमय)
		core->func->init(core);

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (encoder->encoder_type != DRM_MODE_ENCODER_DPMST) अणु
			काष्ठा nouveau_encoder *nv_encoder =
				nouveau_encoder(encoder);
			nv50_msपंचांग_init(nv_encoder, runसमय);
		पूर्ण
	पूर्ण

	drm_क्रम_each_plane(plane, dev) अणु
		काष्ठा nv50_wndw *wndw = nv50_wndw(plane);
		अगर (plane->funcs != &nv50_wndw)
			जारी;
		nv50_wndw_init(wndw);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nv50_display_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा nv50_disp *disp = nv50_disp(dev);

	nv50_audio_component_fini(nouveau_drm(dev));

	nvअगर_object_unmap(&disp->caps);
	nvअगर_object_dtor(&disp->caps);
	nv50_core_del(&disp->core);

	nouveau_bo_unmap(disp->sync);
	अगर (disp->sync)
		nouveau_bo_unpin(disp->sync);
	nouveau_bo_ref(शून्य, &disp->sync);

	nouveau_display(dev)->priv = शून्य;
	kमुक्त(disp);
पूर्ण

पूर्णांक
nv50_display_create(काष्ठा drm_device *dev)
अणु
	काष्ठा nvअगर_device *device = &nouveau_drm(dev)->client.device;
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा dcb_table *dcb = &drm->vbios.dcb;
	काष्ठा drm_connector *connector, *पंचांगp;
	काष्ठा nv50_disp *disp;
	काष्ठा dcb_output *dcbe;
	पूर्णांक crtcs, ret, i;
	bool has_mst = nv50_has_mst(drm);

	disp = kzalloc(माप(*disp), GFP_KERNEL);
	अगर (!disp)
		वापस -ENOMEM;

	mutex_init(&disp->mutex);

	nouveau_display(dev)->priv = disp;
	nouveau_display(dev)->dtor = nv50_display_destroy;
	nouveau_display(dev)->init = nv50_display_init;
	nouveau_display(dev)->fini = nv50_display_fini;
	disp->disp = &nouveau_display(dev)->disp;
	dev->mode_config.funcs = &nv50_disp_func;
	dev->mode_config.quirk_addfb_prefer_xbgr_30bpp = true;
	dev->mode_config.normalize_zpos = true;

	/* small shared memory area we use क्रम notअगरiers and semaphores */
	ret = nouveau_bo_new(&drm->client, 4096, 0x1000,
			     NOUVEAU_GEM_DOMAIN_VRAM,
			     0, 0x0000, शून्य, शून्य, &disp->sync);
	अगर (!ret) अणु
		ret = nouveau_bo_pin(disp->sync, NOUVEAU_GEM_DOMAIN_VRAM, true);
		अगर (!ret) अणु
			ret = nouveau_bo_map(disp->sync);
			अगर (ret)
				nouveau_bo_unpin(disp->sync);
		पूर्ण
		अगर (ret)
			nouveau_bo_ref(शून्य, &disp->sync);
	पूर्ण

	अगर (ret)
		जाओ out;

	/* allocate master evo channel */
	ret = nv50_core_new(drm, &disp->core);
	अगर (ret)
		जाओ out;

	disp->core->func->init(disp->core);
	अगर (disp->core->func->caps_init) अणु
		ret = disp->core->func->caps_init(drm, disp);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Assign the correct क्रमmat modअगरiers */
	अगर (disp->disp->object.oclass >= TU102_DISP)
		nouveau_display(dev)->क्रमmat_modअगरiers = wndwc57e_modअगरiers;
	अन्यथा
	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_FERMI)
		nouveau_display(dev)->क्रमmat_modअगरiers = disp90xx_modअगरiers;
	अन्यथा
		nouveau_display(dev)->क्रमmat_modअगरiers = disp50xx_modअगरiers;

	/* FIXME: 256x256 cursors are supported on Kepler, however unlike Maxwell and later
	 * generations Kepler requires that we use small pages (4K) क्रम cursor scanout surfaces. The
	 * proper fix क्रम this is to teach nouveau to migrate fbs being used क्रम the cursor plane to
	 * small page allocations in prepare_fb(). When this is implemented, we should also क्रमce
	 * large pages (128K) क्रम ovly fbs in order to fix Kepler ovlys.
	 * But until then, just limit cursors to 128x128 - which is small enough to aव्योम ever using
	 * large pages.
	 */
	अगर (disp->disp->object.oclass >= GM107_DISP) अणु
		dev->mode_config.cursor_width = 256;
		dev->mode_config.cursor_height = 256;
	पूर्ण अन्यथा अगर (disp->disp->object.oclass >= GK104_DISP) अणु
		dev->mode_config.cursor_width = 128;
		dev->mode_config.cursor_height = 128;
	पूर्ण अन्यथा अणु
		dev->mode_config.cursor_width = 64;
		dev->mode_config.cursor_height = 64;
	पूर्ण

	/* create crtc objects to represent the hw heads */
	अगर (disp->disp->object.oclass >= GV100_DISP)
		crtcs = nvअगर_rd32(&device->object, 0x610060) & 0xff;
	अन्यथा
	अगर (disp->disp->object.oclass >= GF110_DISP)
		crtcs = nvअगर_rd32(&device->object, 0x612004) & 0xf;
	अन्यथा
		crtcs = 0x3;

	क्रम (i = 0; i < fls(crtcs); i++) अणु
		काष्ठा nv50_head *head;

		अगर (!(crtcs & (1 << i)))
			जारी;

		head = nv50_head_create(dev, i);
		अगर (IS_ERR(head)) अणु
			ret = PTR_ERR(head);
			जाओ out;
		पूर्ण

		अगर (has_mst) अणु
			head->msto = nv50_msto_new(dev, head, i);
			अगर (IS_ERR(head->msto)) अणु
				ret = PTR_ERR(head->msto);
				head->msto = शून्य;
				जाओ out;
			पूर्ण

			/*
			 * FIXME: This is a hack to workaround the following
			 * issues:
			 *
			 * https://gitlab.gnome.org/GNOME/mutter/issues/759
			 * https://gitlab.मुक्तdesktop.org/xorg/xserver/merge_requests/277
			 *
			 * Once these issues are बंदd, this should be
			 * हटाओd
			 */
			head->msto->encoder.possible_crtcs = crtcs;
		पूर्ण
	पूर्ण

	/* create encoder/connector objects based on VBIOS DCB table */
	क्रम (i = 0, dcbe = &dcb->entry[0]; i < dcb->entries; i++, dcbe++) अणु
		connector = nouveau_connector_create(dev, dcbe);
		अगर (IS_ERR(connector))
			जारी;

		अगर (dcbe->location == DCB_LOC_ON_CHIP) अणु
			चयन (dcbe->type) अणु
			हाल DCB_OUTPUT_TMDS:
			हाल DCB_OUTPUT_LVDS:
			हाल DCB_OUTPUT_DP:
				ret = nv50_sor_create(connector, dcbe);
				अवरोध;
			हाल DCB_OUTPUT_ANALOG:
				ret = nv50_dac_create(connector, dcbe);
				अवरोध;
			शेष:
				ret = -ENODEV;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = nv50_pior_create(connector, dcbe);
		पूर्ण

		अगर (ret) अणु
			NV_WARN(drm, "failed to create encoder %d/%d/%d: %d\n",
				     dcbe->location, dcbe->type,
				     ffs(dcbe->or) - 1, ret);
			ret = 0;
		पूर्ण
	पूर्ण

	/* cull any connectors we created that करोn't have an encoder */
	list_क्रम_each_entry_safe(connector, पंचांगp, &dev->mode_config.connector_list, head) अणु
		अगर (connector->possible_encoders)
			जारी;

		NV_WARN(drm, "%s has no encoders, removing\n",
			connector->name);
		connector->funcs->destroy(connector);
	पूर्ण

	/* Disable vblank irqs aggressively क्रम घातer-saving, safe on nv50+ */
	dev->vblank_disable_immediate = true;

	nv50_audio_component_init(drm);

out:
	अगर (ret)
		nv50_display_destroy(dev);
	वापस ret;
पूर्ण

/******************************************************************************
 * Format modअगरiers
 *****************************************************************************/

/****************************************************************
 *            Log2(block height) ----------------------------+  *
 *            Page Kind ----------------------------------+  |  *
 *            Gob Height/Page Kind Generation ------+     |  |  *
 *                          Sector layout -------+  |     |  |  *
 *                          Compression ------+  |  |     |  |  */
स्थिर u64 disp50xx_modअगरiers[] = अणु /*         |  |  |     |  |  */
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 0),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 1),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 2),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 3),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 4),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x7a, 5),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 0),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 1),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 2),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 3),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 4),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x78, 5),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 0),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 1),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 2),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 3),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 4),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 1, 0x70, 5),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

/****************************************************************
 *            Log2(block height) ----------------------------+  *
 *            Page Kind ----------------------------------+  |  *
 *            Gob Height/Page Kind Generation ------+     |  |  *
 *                          Sector layout -------+  |     |  |  *
 *                          Compression ------+  |  |     |  |  */
स्थिर u64 disp90xx_modअगरiers[] = अणु /*         |  |  |     |  |  */
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 0),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 1),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 2),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 3),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 4),
	DRM_FORMAT_MOD_NVIDIA_BLOCK_LINEAR_2D(0, 1, 0, 0xfe, 5),
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;
