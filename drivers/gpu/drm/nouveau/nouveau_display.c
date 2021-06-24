<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <acpi/video.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "nouveau_fbcon.h"
#समावेश "nouveau_crtc.h"
#समावेश "nouveau_gem.h"
#समावेश "nouveau_connector.h"
#समावेश "nv50_display.h"

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0046.h>
#समावेश <nvअगर/event.h>
#समावेश <dispnv50/crc.h>

पूर्णांक
nouveau_display_vblank_enable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nouveau_crtc *nv_crtc;

	nv_crtc = nouveau_crtc(crtc);
	nvअगर_notअगरy_get(&nv_crtc->vblank);

	वापस 0;
पूर्ण

व्योम
nouveau_display_vblank_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा nouveau_crtc *nv_crtc;

	nv_crtc = nouveau_crtc(crtc);
	nvअगर_notअगरy_put(&nv_crtc->vblank);
पूर्ण

अटल अंतरभूत पूर्णांक
calc(पूर्णांक blanks, पूर्णांक blanke, पूर्णांक total, पूर्णांक line)
अणु
	अगर (blanke >= blanks) अणु
		अगर (line >= blanks)
			line -= total;
	पूर्ण अन्यथा अणु
		अगर (line >= blanks)
			line -= total;
		line -= blanke + 1;
	पूर्ण
	वापस line;
पूर्ण

अटल bool
nouveau_display_scanoutpos_head(काष्ठा drm_crtc *crtc, पूर्णांक *vpos, पूर्णांक *hpos,
				kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय)
अणु
	काष्ठा अणु
		काष्ठा nv04_disp_mthd_v0 base;
		काष्ठा nv04_disp_scanoutpos_v0 scan;
	पूर्ण args = अणु
		.base.method = NV04_DISP_SCANOUTPOS,
		.base.head = nouveau_crtc(crtc)->index,
	पूर्ण;
	काष्ठा nouveau_display *disp = nouveau_display(crtc->dev);
	काष्ठा drm_vblank_crtc *vblank = &crtc->dev->vblank[drm_crtc_index(crtc)];
	पूर्णांक retry = 20;
	bool ret = false;

	करो अणु
		ret = nvअगर_mthd(&disp->disp.object, 0, &args, माप(args));
		अगर (ret != 0)
			वापस false;

		अगर (args.scan.vline) अणु
			ret = true;
			अवरोध;
		पूर्ण

		अगर (retry) ndelay(vblank->linedur_ns);
	पूर्ण जबतक (retry--);

	*hpos = args.scan.hline;
	*vpos = calc(args.scan.vblanks, args.scan.vblanke,
		     args.scan.vtotal, args.scan.vline);
	अगर (sसमय) *sसमय = ns_to_kसमय(args.scan.समय[0]);
	अगर (eसमय) *eसमय = ns_to_kसमय(args.scan.समय[1]);

	वापस ret;
पूर्ण

bool
nouveau_display_scanoutpos(काष्ठा drm_crtc *crtc,
			   bool in_vblank_irq, पूर्णांक *vpos, पूर्णांक *hpos,
			   kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			   स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस nouveau_display_scanoutpos_head(crtc, vpos, hpos,
					       sसमय, eसमय);
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs nouveau_framebuffer_funcs = अणु
	.destroy = drm_gem_fb_destroy,
	.create_handle = drm_gem_fb_create_handle,
पूर्ण;

अटल व्योम
nouveau_decode_mod(काष्ठा nouveau_drm *drm,
		   uपूर्णांक64_t modअगरier,
		   uपूर्णांक32_t *tile_mode,
		   uपूर्णांक8_t *kind)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(drm->dev);
	BUG_ON(!tile_mode || !kind);

	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR) अणु
		/* tile_mode will not be used in this हाल */
		*tile_mode = 0;
		*kind = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Extract the block height and kind from the corresponding
		 * modअगरier fields.  See drm_fourcc.h क्रम details.
		 */

		अगर ((modअगरier & (0xffull << 12)) == 0ull) अणु
			/* Legacy modअगरier.  Translate to this dev's 'kind.' */
			modअगरier |= disp->क्रमmat_modअगरiers[0] & (0xffull << 12);
		पूर्ण

		*tile_mode = (uपूर्णांक32_t)(modअगरier & 0xF);
		*kind = (uपूर्णांक8_t)((modअगरier >> 12) & 0xFF);

		अगर (drm->client.device.info.chipset >= 0xc0)
			*tile_mode <<= 4;
	पूर्ण
पूर्ण

व्योम
nouveau_framebuffer_get_layout(काष्ठा drm_framebuffer *fb,
			       uपूर्णांक32_t *tile_mode,
			       uपूर्णांक8_t *kind)
अणु
	अगर (fb->flags & DRM_MODE_FB_MODIFIERS) अणु
		काष्ठा nouveau_drm *drm = nouveau_drm(fb->dev);

		nouveau_decode_mod(drm, fb->modअगरier, tile_mode, kind);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा nouveau_bo *nvbo = nouveau_gem_object(fb->obj[0]);

		*tile_mode = nvbo->mode;
		*kind = nvbo->kind;
	पूर्ण
पूर्ण

अटल स्थिर u64 legacy_modअगरiers[] = अणु
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(0),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(1),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(2),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(3),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(4),
	DRM_FORMAT_MOD_NVIDIA_16BX2_BLOCK(5),
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल पूर्णांक
nouveau_validate_decode_mod(काष्ठा nouveau_drm *drm,
			    uपूर्णांक64_t modअगरier,
			    uपूर्णांक32_t *tile_mode,
			    uपूर्णांक8_t *kind)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(drm->dev);
	पूर्णांक mod;

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		वापस -EINVAL;
	पूर्ण

	BUG_ON(!disp->क्रमmat_modअगरiers);

	क्रम (mod = 0;
	     (disp->क्रमmat_modअगरiers[mod] != DRM_FORMAT_MOD_INVALID) &&
	     (disp->क्रमmat_modअगरiers[mod] != modअगरier);
	     mod++);

	अगर (disp->क्रमmat_modअगरiers[mod] == DRM_FORMAT_MOD_INVALID) अणु
		क्रम (mod = 0;
		     (legacy_modअगरiers[mod] != DRM_FORMAT_MOD_INVALID) &&
		     (legacy_modअगरiers[mod] != modअगरier);
		     mod++);
		अगर (legacy_modअगरiers[mod] == DRM_FORMAT_MOD_INVALID)
			वापस -EINVAL;
	पूर्ण

	nouveau_decode_mod(drm, modअगरier, tile_mode, kind);

	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nouveau_get_width_in_blocks(uपूर्णांक32_t stride)
अणु
	/* GOBs per block in the x direction is always one, and GOBs are
	 * 64 bytes wide
	 */
	अटल स्थिर uपूर्णांक32_t log_block_width = 6;

	वापस (stride + (1 << log_block_width) - 1) >> log_block_width;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t
nouveau_get_height_in_blocks(काष्ठा nouveau_drm *drm,
			     uपूर्णांक32_t height,
			     uपूर्णांक32_t log_block_height_in_gobs)
अणु
	uपूर्णांक32_t log_gob_height;
	uपूर्णांक32_t log_block_height;

	BUG_ON(drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA);

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_FERMI)
		log_gob_height = 2;
	अन्यथा
		log_gob_height = 3;

	log_block_height = log_block_height_in_gobs + log_gob_height;

	वापस (height + (1 << log_block_height) - 1) >> log_block_height;
पूर्ण

अटल पूर्णांक
nouveau_check_bl_size(काष्ठा nouveau_drm *drm, काष्ठा nouveau_bo *nvbo,
		      uपूर्णांक32_t offset, uपूर्णांक32_t stride, uपूर्णांक32_t h,
		      uपूर्णांक32_t tile_mode)
अणु
	uपूर्णांक32_t gob_size, bw, bh;
	uपूर्णांक64_t bl_size;

	BUG_ON(drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA);

	अगर (drm->client.device.info.chipset >= 0xc0) अणु
		अगर (tile_mode & 0xF)
			वापस -EINVAL;
		tile_mode >>= 4;
	पूर्ण

	अगर (tile_mode & 0xFFFFFFF0)
		वापस -EINVAL;

	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_FERMI)
		gob_size = 256;
	अन्यथा
		gob_size = 512;

	bw = nouveau_get_width_in_blocks(stride);
	bh = nouveau_get_height_in_blocks(drm, h, tile_mode);

	bl_size = bw * bh * (1 << tile_mode) * gob_size;

	DRM_DEBUG_KMS("offset=%u stride=%u h=%u tile_mode=0x%02x bw=%u bh=%u gob_size=%u bl_size=%llu size=%zu\n",
		      offset, stride, h, tile_mode, bw, bh, gob_size, bl_size,
		      nvbo->bo.base.size);

	अगर (bl_size + offset > nvbo->bo.base.size)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

पूर्णांक
nouveau_framebuffer_new(काष्ठा drm_device *dev,
			स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			काष्ठा drm_gem_object *gem,
			काष्ठा drm_framebuffer **pfb)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(gem);
	काष्ठा drm_framebuffer *fb;
	स्थिर काष्ठा drm_क्रमmat_info *info;
	अचिन्हित पूर्णांक width, height, i;
	uपूर्णांक32_t tile_mode;
	uपूर्णांक8_t kind;
	पूर्णांक ret;

        /* YUV overlays have special requirements pre-NV50 */
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA &&

	    (mode_cmd->pixel_क्रमmat == DRM_FORMAT_YUYV ||
	     mode_cmd->pixel_क्रमmat == DRM_FORMAT_UYVY ||
	     mode_cmd->pixel_क्रमmat == DRM_FORMAT_NV12 ||
	     mode_cmd->pixel_क्रमmat == DRM_FORMAT_NV21) &&
	    (mode_cmd->pitches[0] & 0x3f || /* align 64 */
	     mode_cmd->pitches[0] >= 0x10000 || /* at most 64k pitch */
	     (mode_cmd->pitches[1] && /* pitches क्रम planes must match */
	      mode_cmd->pitches[0] != mode_cmd->pitches[1]))) अणु
		DRM_DEBUG_KMS("Unsuitable framebuffer: format: %p4cc; pitches: 0x%x\n 0x%x\n",
			      &mode_cmd->pixel_क्रमmat,
			      mode_cmd->pitches[0], mode_cmd->pitches[1]);
		वापस -EINVAL;
	पूर्ण

	अगर (mode_cmd->flags & DRM_MODE_FB_MODIFIERS) अणु
		अगर (nouveau_validate_decode_mod(drm, mode_cmd->modअगरier[0],
						&tile_mode, &kind)) अणु
			DRM_DEBUG_KMS("Unsupported modifier: 0x%llx\n",
				      mode_cmd->modअगरier[0]);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		tile_mode = nvbo->mode;
		kind = nvbo->kind;
	पूर्ण

	info = drm_get_क्रमmat_info(dev, mode_cmd);

	क्रम (i = 0; i < info->num_planes; i++) अणु
		width = drm_क्रमmat_info_plane_width(info,
						    mode_cmd->width,
						    i);
		height = drm_क्रमmat_info_plane_height(info,
						      mode_cmd->height,
						      i);

		अगर (kind) अणु
			ret = nouveau_check_bl_size(drm, nvbo,
						    mode_cmd->offsets[i],
						    mode_cmd->pitches[i],
						    height, tile_mode);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			uपूर्णांक32_t size = mode_cmd->pitches[i] * height;

			अगर (size + mode_cmd->offsets[i] > nvbo->bo.base.size)
				वापस -दुस्फल;
		पूर्ण
	पूर्ण

	अगर (!(fb = *pfb = kzalloc(माप(*fb), GFP_KERNEL)))
		वापस -ENOMEM;

	drm_helper_mode_fill_fb_काष्ठा(dev, fb, mode_cmd);
	fb->obj[0] = gem;

	ret = drm_framebuffer_init(dev, fb, &nouveau_framebuffer_funcs);
	अगर (ret)
		kमुक्त(fb);
	वापस ret;
पूर्ण

काष्ठा drm_framebuffer *
nouveau_user_framebuffer_create(काष्ठा drm_device *dev,
				काष्ठा drm_file *file_priv,
				स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_gem_object *gem;
	पूर्णांक ret;

	gem = drm_gem_object_lookup(file_priv, mode_cmd->handles[0]);
	अगर (!gem)
		वापस ERR_PTR(-ENOENT);

	ret = nouveau_framebuffer_new(dev, mode_cmd, gem, &fb);
	अगर (ret == 0)
		वापस fb;

	drm_gem_object_put(gem);
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs nouveau_mode_config_funcs = अणु
	.fb_create = nouveau_user_framebuffer_create,
	.output_poll_changed = nouveau_fbcon_output_poll_changed,
पूर्ण;


काष्ठा nouveau_drm_prop_क्रमागत_list अणु
	u8 gen_mask;
	पूर्णांक type;
	अक्षर *name;
पूर्ण;

अटल काष्ठा nouveau_drm_prop_क्रमागत_list underscan[] = अणु
	अणु 6, UNDERSCAN_AUTO, "auto" पूर्ण,
	अणु 6, UNDERSCAN_OFF, "off" पूर्ण,
	अणु 6, UNDERSCAN_ON, "on" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा nouveau_drm_prop_क्रमागत_list dither_mode[] = अणु
	अणु 7, DITHERING_MODE_AUTO, "auto" पूर्ण,
	अणु 7, DITHERING_MODE_OFF, "off" पूर्ण,
	अणु 1, DITHERING_MODE_ON, "on" पूर्ण,
	अणु 6, DITHERING_MODE_STATIC2X2, "static 2x2" पूर्ण,
	अणु 6, DITHERING_MODE_DYNAMIC2X2, "dynamic 2x2" पूर्ण,
	अणु 4, DITHERING_MODE_TEMPORAL, "temporal" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा nouveau_drm_prop_क्रमागत_list dither_depth[] = अणु
	अणु 6, DITHERING_DEPTH_AUTO, "auto" पूर्ण,
	अणु 6, DITHERING_DEPTH_6BPC, "6 bpc" पूर्ण,
	अणु 6, DITHERING_DEPTH_8BPC, "8 bpc" पूर्ण,
	अणुपूर्ण
पूर्ण;

#घोषणा PROP_ENUM(p,gen,n,list) करो अणु                                           \
	काष्ठा nouveau_drm_prop_क्रमागत_list *l = (list);                         \
	पूर्णांक c = 0;                                                             \
	जबतक (l->gen_mask) अणु                                                  \
		अगर (l->gen_mask & (1 << (gen)))                                \
			c++;                                                   \
		l++;                                                           \
	पूर्ण                                                                      \
	अगर (c) अणु                                                               \
		p = drm_property_create(dev, DRM_MODE_PROP_ENUM, n, c);        \
		l = (list);                                                    \
		जबतक (p && l->gen_mask) अणु                                     \
			अगर (l->gen_mask & (1 << (gen))) अणु                      \
				drm_property_add_क्रमागत(p, l->type, l->name);    \
			पूर्ण                                                      \
			l++;                                                   \
		पूर्ण                                                              \
	पूर्ण                                                                      \
पूर्ण जबतक(0)

व्योम
nouveau_display_hpd_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

	mutex_lock(&drm->hpd_lock);
	drm->hpd_pending = ~0;
	mutex_unlock(&drm->hpd_lock);

	schedule_work(&drm->hpd_work);
पूर्ण

अटल व्योम
nouveau_display_hpd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nouveau_drm *drm = container_of(work, typeof(*drm), hpd_work);
	काष्ठा drm_device *dev = drm->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	u32 pending;
	bool changed = false;

	pm_runसमय_get_sync(dev->dev);

	mutex_lock(&drm->hpd_lock);
	pending = drm->hpd_pending;
	drm->hpd_pending = 0;
	mutex_unlock(&drm->hpd_lock);

	/* Nothing to करो, निकास early without updating the last busy counter */
	अगर (!pending)
		जाओ noop;

	mutex_lock(&dev->mode_config.mutex);
	drm_connector_list_iter_begin(dev, &conn_iter);

	nouveau_क्रम_each_non_mst_connector_iter(connector, &conn_iter) अणु
		क्रमागत drm_connector_status old_status = connector->status;
		u64 old_epoch_counter = connector->epoch_counter;

		अगर (!(pending & drm_connector_mask(connector)))
			जारी;

		connector->status = drm_helper_probe_detect(connector, शून्य,
							    false);
		अगर (old_epoch_counter == connector->epoch_counter)
			जारी;

		changed = true;
		drm_dbg_kms(dev, "[CONNECTOR:%d:%s] status updated from %s to %s (epoch counter %llu->%llu)\n",
			    connector->base.id, connector->name,
			    drm_get_connector_status_name(old_status),
			    drm_get_connector_status_name(connector->status),
			    old_epoch_counter, connector->epoch_counter);
	पूर्ण

	drm_connector_list_iter_end(&conn_iter);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (changed)
		drm_kms_helper_hotplug_event(dev);

	pm_runसमय_mark_last_busy(drm->dev->dev);
noop:
	pm_runसमय_put_sync(drm->dev->dev);
पूर्ण

#अगर_घोषित CONFIG_ACPI

अटल पूर्णांक
nouveau_display_acpi_ntfy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			  व्योम *data)
अणु
	काष्ठा nouveau_drm *drm = container_of(nb, typeof(*drm), acpi_nb);
	काष्ठा acpi_bus_event *info = data;
	पूर्णांक ret;

	अगर (!म_भेद(info->device_class, ACPI_VIDEO_CLASS)) अणु
		अगर (info->type == ACPI_VIDEO_NOTIFY_PROBE) अणु
			ret = pm_runसमय_get(drm->dev->dev);
			अगर (ret == 1 || ret == -EACCES) अणु
				/* If the GPU is alपढ़ोy awake, or in a state
				 * where we can't wake it up, it can handle
				 * it's own hotplug events.
				 */
				pm_runसमय_put_स्वतःsuspend(drm->dev->dev);
			पूर्ण अन्यथा अगर (ret == 0) अणु
				/* We've started resuming the GPU alपढ़ोy, so
				 * it will handle scheduling a full reprobe
				 * itself
				 */
				NV_DEBUG(drm, "ACPI requested connector reprobe\n");
				pm_runसमय_put_noidle(drm->dev->dev);
			पूर्ण अन्यथा अणु
				NV_WARN(drm, "Dropped ACPI reprobe event due to RPM error: %d\n",
					ret);
			पूर्ण

			/* acpi-video should not generate keypresses क्रम this */
			वापस NOTIFY_BAD;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

पूर्णांक
nouveau_display_init(काष्ठा drm_device *dev, bool resume, bool runसमय)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	पूर्णांक ret;

	/*
	 * Enable hotplug पूर्णांकerrupts (करोne as early as possible, since we need
	 * them क्रम MST)
	 */
	drm_connector_list_iter_begin(dev, &conn_iter);
	nouveau_क्रम_each_non_mst_connector_iter(connector, &conn_iter) अणु
		काष्ठा nouveau_connector *conn = nouveau_connector(connector);
		nvअगर_notअगरy_get(&conn->hpd);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	ret = disp->init(dev, resume, runसमय);
	अगर (ret)
		वापस ret;

	/* enable connector detection and polling क्रम connectors without HPD
	 * support
	 */
	drm_kms_helper_poll_enable(dev);

	वापस ret;
पूर्ण

व्योम
nouveau_display_fini(काष्ठा drm_device *dev, bool suspend, bool runसमय)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	अगर (!suspend) अणु
		अगर (drm_drv_uses_atomic_modeset(dev))
			drm_atomic_helper_shutकरोwn(dev);
		अन्यथा
			drm_helper_क्रमce_disable_all(dev);
	पूर्ण

	/* disable hotplug पूर्णांकerrupts */
	drm_connector_list_iter_begin(dev, &conn_iter);
	nouveau_क्रम_each_non_mst_connector_iter(connector, &conn_iter) अणु
		काष्ठा nouveau_connector *conn = nouveau_connector(connector);
		nvअगर_notअगरy_put(&conn->hpd);
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (!runसमय)
		cancel_work_sync(&drm->hpd_work);

	drm_kms_helper_poll_disable(dev);
	disp->fini(dev, runसमय, suspend);
पूर्ण

अटल व्योम
nouveau_display_create_properties(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	पूर्णांक gen;

	अगर (disp->disp.object.oclass < NV50_DISP)
		gen = 0;
	अन्यथा
	अगर (disp->disp.object.oclass < GF110_DISP)
		gen = 1;
	अन्यथा
		gen = 2;

	PROP_ENUM(disp->dithering_mode, gen, "dithering mode", dither_mode);
	PROP_ENUM(disp->dithering_depth, gen, "dithering depth", dither_depth);
	PROP_ENUM(disp->underscan_property, gen, "underscan", underscan);

	disp->underscan_hborder_property =
		drm_property_create_range(dev, 0, "underscan hborder", 0, 128);

	disp->underscan_vborder_property =
		drm_property_create_range(dev, 0, "underscan vborder", 0, 128);

	अगर (gen < 1)
		वापस;

	/* -90..+90 */
	disp->vibrant_hue_property =
		drm_property_create_range(dev, 0, "vibrant hue", 0, 180);

	/* -100..+100 */
	disp->color_vibrance_property =
		drm_property_create_range(dev, 0, "color vibrance", 0, 200);
पूर्ण

पूर्णांक
nouveau_display_create(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा nvkm_device *device = nvxx_device(&drm->client.device);
	काष्ठा nouveau_display *disp;
	पूर्णांक ret;

	disp = drm->display = kzalloc(माप(*disp), GFP_KERNEL);
	अगर (!disp)
		वापस -ENOMEM;

	drm_mode_config_init(dev);
	drm_mode_create_scaling_mode_property(dev);
	drm_mode_create_dvi_i_properties(dev);

	dev->mode_config.funcs = &nouveau_mode_config_funcs;
	dev->mode_config.fb_base = device->func->resource_addr(device, 1);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_CELSIUS) अणु
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	पूर्ण अन्यथा
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA) अणु
		dev->mode_config.max_width = 4096;
		dev->mode_config.max_height = 4096;
	पूर्ण अन्यथा
	अगर (drm->client.device.info.family < NV_DEVICE_INFO_V0_FERMI) अणु
		dev->mode_config.max_width = 8192;
		dev->mode_config.max_height = 8192;
	पूर्ण अन्यथा अणु
		dev->mode_config.max_width = 16384;
		dev->mode_config.max_height = 16384;
	पूर्ण

	dev->mode_config.preferred_depth = 24;
	dev->mode_config.prefer_shaकरोw = 1;
	dev->mode_config.allow_fb_modअगरiers = true;

	अगर (drm->client.device.info.chipset < 0x11)
		dev->mode_config.async_page_flip = false;
	अन्यथा
		dev->mode_config.async_page_flip = true;

	drm_kms_helper_poll_init(dev);
	drm_kms_helper_poll_disable(dev);

	अगर (nouveau_modeset != 2 && drm->vbios.dcb.entries) अणु
		ret = nvअगर_disp_ctor(&drm->client.device, "kmsDisp", 0,
				     &disp->disp);
		अगर (ret == 0) अणु
			nouveau_display_create_properties(dev);
			अगर (disp->disp.object.oclass < NV50_DISP)
				ret = nv04_display_create(dev);
			अन्यथा
				ret = nv50_display_create(dev);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	अगर (ret)
		जाओ disp_create_err;

	drm_mode_config_reset(dev);

	अगर (dev->mode_config.num_crtc) अणु
		ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
		अगर (ret)
			जाओ vblank_err;

		अगर (disp->disp.object.oclass >= NV50_DISP)
			nv50_crc_init(dev);
	पूर्ण

	INIT_WORK(&drm->hpd_work, nouveau_display_hpd_work);
	mutex_init(&drm->hpd_lock);
#अगर_घोषित CONFIG_ACPI
	drm->acpi_nb.notअगरier_call = nouveau_display_acpi_ntfy;
	रेजिस्टर_acpi_notअगरier(&drm->acpi_nb);
#पूर्ण_अगर

	वापस 0;

vblank_err:
	disp->dtor(dev);
disp_create_err:
	drm_kms_helper_poll_fini(dev);
	drm_mode_config_cleanup(dev);
	वापस ret;
पूर्ण

व्योम
nouveau_display_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);

#अगर_घोषित CONFIG_ACPI
	unरेजिस्टर_acpi_notअगरier(&drm->acpi_nb);
#पूर्ण_अगर

	drm_kms_helper_poll_fini(dev);
	drm_mode_config_cleanup(dev);

	अगर (disp->dtor)
		disp->dtor(dev);

	nvअगर_disp_dtor(&disp->disp);

	nouveau_drm(dev)->display = शून्य;
	mutex_destroy(&drm->hpd_lock);
	kमुक्त(disp);
पूर्ण

पूर्णांक
nouveau_display_suspend(काष्ठा drm_device *dev, bool runसमय)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);

	अगर (drm_drv_uses_atomic_modeset(dev)) अणु
		अगर (!runसमय) अणु
			disp->suspend = drm_atomic_helper_suspend(dev);
			अगर (IS_ERR(disp->suspend)) अणु
				पूर्णांक ret = PTR_ERR(disp->suspend);
				disp->suspend = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	nouveau_display_fini(dev, true, runसमय);
	वापस 0;
पूर्ण

व्योम
nouveau_display_resume(काष्ठा drm_device *dev, bool runसमय)
अणु
	काष्ठा nouveau_display *disp = nouveau_display(dev);

	nouveau_display_init(dev, true, runसमय);

	अगर (drm_drv_uses_atomic_modeset(dev)) अणु
		अगर (disp->suspend) अणु
			drm_atomic_helper_resume(dev, disp->suspend);
			disp->suspend = शून्य;
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

पूर्णांक
nouveau_display_dumb_create(काष्ठा drm_file *file_priv, काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा nouveau_cli *cli = nouveau_cli(file_priv);
	काष्ठा nouveau_bo *bo;
	uपूर्णांक32_t करोमुख्य;
	पूर्णांक ret;

	args->pitch = roundup(args->width * (args->bpp / 8), 256);
	args->size = args->pitch * args->height;
	args->size = roundup(args->size, PAGE_SIZE);

	/* Use VRAM अगर there is any ; otherwise fallback to प्रणाली memory */
	अगर (nouveau_drm(dev)->client.device.info.ram_size != 0)
		करोमुख्य = NOUVEAU_GEM_DOMAIN_VRAM;
	अन्यथा
		करोमुख्य = NOUVEAU_GEM_DOMAIN_GART;

	ret = nouveau_gem_new(cli, args->size, 0, करोमुख्य, 0, 0, &bo);
	अगर (ret)
		वापस ret;

	ret = drm_gem_handle_create(file_priv, &bo->bo.base, &args->handle);
	drm_gem_object_put(&bo->bo.base);
	वापस ret;
पूर्ण

पूर्णांक
nouveau_display_dumb_map_offset(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *dev,
				uपूर्णांक32_t handle, uपूर्णांक64_t *poffset)
अणु
	काष्ठा drm_gem_object *gem;

	gem = drm_gem_object_lookup(file_priv, handle);
	अगर (gem) अणु
		काष्ठा nouveau_bo *bo = nouveau_gem_object(gem);
		*poffset = drm_vma_node_offset_addr(&bo->bo.base.vma_node);
		drm_gem_object_put(gem);
		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण
