<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat
 *
 * based in parts on udlfb.c:
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>

 */

#समावेश <linux/dma-buf.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_vblank.h>

#समावेश "udl_drv.h"

#घोषणा UDL_COLOR_DEPTH_16BPP	0

/*
 * All DisplayLink bulk operations start with 0xAF, followed by specअगरic code
 * All operations are written to buffers which then later get sent to device
 */
अटल अक्षर *udl_set_रेजिस्टर(अक्षर *buf, u8 reg, u8 val)
अणु
	*buf++ = 0xAF;
	*buf++ = 0x20;
	*buf++ = reg;
	*buf++ = val;
	वापस buf;
पूर्ण

अटल अक्षर *udl_vidreg_lock(अक्षर *buf)
अणु
	वापस udl_set_रेजिस्टर(buf, 0xFF, 0x00);
पूर्ण

अटल अक्षर *udl_vidreg_unlock(अक्षर *buf)
अणु
	वापस udl_set_रेजिस्टर(buf, 0xFF, 0xFF);
पूर्ण

अटल अक्षर *udl_set_blank_mode(अक्षर *buf, u8 mode)
अणु
	वापस udl_set_रेजिस्टर(buf, UDL_REG_BLANK_MODE, mode);
पूर्ण

अटल अक्षर *udl_set_color_depth(अक्षर *buf, u8 selection)
अणु
	वापस udl_set_रेजिस्टर(buf, 0x00, selection);
पूर्ण

अटल अक्षर *udl_set_base16bpp(अक्षर *wrptr, u32 base)
अणु
	/* the base poपूर्णांकer is 16 bits wide, 0x20 is hi byte. */
	wrptr = udl_set_रेजिस्टर(wrptr, 0x20, base >> 16);
	wrptr = udl_set_रेजिस्टर(wrptr, 0x21, base >> 8);
	वापस udl_set_रेजिस्टर(wrptr, 0x22, base);
पूर्ण

/*
 * DisplayLink HW has separate 16bpp and 8bpp framebuffers.
 * In 24bpp modes, the low 323 RGB bits go in the 8bpp framebuffer
 */
अटल अक्षर *udl_set_base8bpp(अक्षर *wrptr, u32 base)
अणु
	wrptr = udl_set_रेजिस्टर(wrptr, 0x26, base >> 16);
	wrptr = udl_set_रेजिस्टर(wrptr, 0x27, base >> 8);
	वापस udl_set_रेजिस्टर(wrptr, 0x28, base);
पूर्ण

अटल अक्षर *udl_set_रेजिस्टर_16(अक्षर *wrptr, u8 reg, u16 value)
अणु
	wrptr = udl_set_रेजिस्टर(wrptr, reg, value >> 8);
	वापस udl_set_रेजिस्टर(wrptr, reg+1, value);
पूर्ण

/*
 * This is kind of weird because the controller takes some
 * रेजिस्टर values in a dअगरferent byte order than other रेजिस्टरs.
 */
अटल अक्षर *udl_set_रेजिस्टर_16be(अक्षर *wrptr, u8 reg, u16 value)
अणु
	wrptr = udl_set_रेजिस्टर(wrptr, reg, value);
	वापस udl_set_रेजिस्टर(wrptr, reg+1, value >> 8);
पूर्ण

/*
 * LFSR is linear feedback shअगरt रेजिस्टर. The reason we have this is
 * because the display controller needs to minimize the घड़ी depth of
 * various counters used in the display path. So this code reverses the
 * provided value पूर्णांकo the lfsr16 value by counting backwards to get
 * the value that needs to be set in the hardware comparator to get the
 * same actual count. This makes sense once you पढ़ो above a couple of
 * बार and think about it from a hardware perspective.
 */
अटल u16 udl_lfsr16(u16 actual_count)
अणु
	u32 lv = 0xFFFF; /* This is the lfsr value that the hw starts with */

	जबतक (actual_count--) अणु
		lv =	 ((lv << 1) |
			(((lv >> 15) ^ (lv >> 4) ^ (lv >> 2) ^ (lv >> 1)) & 1))
			& 0xFFFF;
	पूर्ण

	वापस (u16) lv;
पूर्ण

/*
 * This करोes LFSR conversion on the value that is to be written.
 * See LFSR explanation above क्रम more detail.
 */
अटल अक्षर *udl_set_रेजिस्टर_lfsr16(अक्षर *wrptr, u8 reg, u16 value)
अणु
	वापस udl_set_रेजिस्टर_16(wrptr, reg, udl_lfsr16(value));
पूर्ण

/*
 * This takes a standard fbdev screeninfo काष्ठा and all of its monitor mode
 * details and converts them पूर्णांकo the DisplayLink equivalent रेजिस्टर commands.
  ERR(vreg(dev,               0x00, (color_depth == 16) ? 0 : 1));
  ERR(vreg_lfsr16(dev,        0x01, xDisplayStart));
  ERR(vreg_lfsr16(dev,        0x03, xDisplayEnd));
  ERR(vreg_lfsr16(dev,        0x05, yDisplayStart));
  ERR(vreg_lfsr16(dev,        0x07, yDisplayEnd));
  ERR(vreg_lfsr16(dev,        0x09, xEndCount));
  ERR(vreg_lfsr16(dev,        0x0B, hSyncStart));
  ERR(vreg_lfsr16(dev,        0x0D, hSyncEnd));
  ERR(vreg_big_endian(dev,    0x0F, hPixels));
  ERR(vreg_lfsr16(dev,        0x11, yEndCount));
  ERR(vreg_lfsr16(dev,        0x13, vSyncStart));
  ERR(vreg_lfsr16(dev,        0x15, vSyncEnd));
  ERR(vreg_big_endian(dev,    0x17, vPixels));
  ERR(vreg_little_endian(dev, 0x1B, pixelClock5KHz));

  ERR(vreg(dev,               0x1F, 0));

  ERR(vbuf(dev, WRITE_VIDREG_UNLOCK, DSIZखातापूर्ण(WRITE_VIDREG_UNLOCK)));
 */
अटल अक्षर *udl_set_vid_cmds(अक्षर *wrptr, काष्ठा drm_display_mode *mode)
अणु
	u16 xds, yds;
	u16 xde, yde;
	u16 yec;

	/* x display start */
	xds = mode->crtc_htotal - mode->crtc_hsync_start;
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x01, xds);
	/* x display end */
	xde = xds + mode->crtc_hdisplay;
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x03, xde);

	/* y display start */
	yds = mode->crtc_vtotal - mode->crtc_vsync_start;
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x05, yds);
	/* y display end */
	yde = yds + mode->crtc_vdisplay;
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x07, yde);

	/* x end count is active + blanking - 1 */
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x09,
					mode->crtc_htotal - 1);

	/* libdlo hardcodes hsync start to 1 */
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x0B, 1);

	/* hsync end is width of sync pulse + 1 */
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x0D,
					mode->crtc_hsync_end - mode->crtc_hsync_start + 1);

	/* hpixels is active pixels */
	wrptr = udl_set_रेजिस्टर_16(wrptr, 0x0F, mode->hdisplay);

	/* yendcount is vertical active + vertical blanking */
	yec = mode->crtc_vtotal;
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x11, yec);

	/* libdlo hardcodes vsync start to 0 */
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x13, 0);

	/* vsync end is width of vsync pulse */
	wrptr = udl_set_रेजिस्टर_lfsr16(wrptr, 0x15, mode->crtc_vsync_end - mode->crtc_vsync_start);

	/* vpixels is active pixels */
	wrptr = udl_set_रेजिस्टर_16(wrptr, 0x17, mode->crtc_vdisplay);

	wrptr = udl_set_रेजिस्टर_16be(wrptr, 0x1B,
				      mode->घड़ी / 5);

	वापस wrptr;
पूर्ण

अटल अक्षर *udl_dummy_render(अक्षर *wrptr)
अणु
	*wrptr++ = 0xAF;
	*wrptr++ = 0x6A; /* copy */
	*wrptr++ = 0x00; /* from addr */
	*wrptr++ = 0x00;
	*wrptr++ = 0x00;
	*wrptr++ = 0x01; /* one pixel */
	*wrptr++ = 0x00; /* to address */
	*wrptr++ = 0x00;
	*wrptr++ = 0x00;
	वापस wrptr;
पूर्ण

अटल पूर्णांक udl_crtc_ग_लिखो_mode_to_hw(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा udl_device *udl = to_udl(dev);
	काष्ठा urb *urb;
	अक्षर *buf;
	पूर्णांक retval;

	अगर (udl->mode_buf_len == 0) अणु
		DRM_ERROR("No mode set\n");
		वापस -EINVAL;
	पूर्ण

	urb = udl_get_urb(dev);
	अगर (!urb)
		वापस -ENOMEM;

	buf = (अक्षर *)urb->transfer_buffer;

	स_नकल(buf, udl->mode_buf, udl->mode_buf_len);
	retval = udl_submit_urb(dev, urb, udl->mode_buf_len);
	DRM_DEBUG("write mode info %d\n", udl->mode_buf_len);
	वापस retval;
पूर्ण

अटल दीर्घ udl_log_cpp(अचिन्हित पूर्णांक cpp)
अणु
	अगर (WARN_ON(!is_घातer_of_2(cpp)))
		वापस -EINVAL;
	वापस __ffs(cpp);
पूर्ण

अटल पूर्णांक udl_aligned_damage_clip(काष्ठा drm_rect *clip, पूर्णांक x, पूर्णांक y,
				   पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक x1, x2;

	अगर (WARN_ON_ONCE(x < 0) ||
	    WARN_ON_ONCE(y < 0) ||
	    WARN_ON_ONCE(width < 0) ||
	    WARN_ON_ONCE(height < 0))
		वापस -EINVAL;

	x1 = ALIGN_DOWN(x, माप(अचिन्हित दीर्घ));
	x2 = ALIGN(width + (x - x1), माप(अचिन्हित दीर्घ)) + x1;

	clip->x1 = x1;
	clip->y1 = y;
	clip->x2 = x2;
	clip->y2 = y + height;

	वापस 0;
पूर्ण

अटल पूर्णांक udl_handle_damage(काष्ठा drm_framebuffer *fb, स्थिर काष्ठा dma_buf_map *map,
			     पूर्णांक x, पूर्णांक y, पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा drm_device *dev = fb->dev;
	काष्ठा dma_buf_attachment *import_attach = fb->obj[0]->import_attach;
	व्योम *vaddr = map->vaddr; /* TODO: Use mapping असलtraction properly */
	पूर्णांक i, ret, पंचांगp_ret;
	अक्षर *cmd;
	काष्ठा urb *urb;
	काष्ठा drm_rect clip;
	पूर्णांक log_bpp;

	ret = udl_log_cpp(fb->क्रमmat->cpp[0]);
	अगर (ret < 0)
		वापस ret;
	log_bpp = ret;

	ret = udl_aligned_damage_clip(&clip, x, y, width, height);
	अगर (ret)
		वापस ret;
	अन्यथा अगर ((clip.x2 > fb->width) || (clip.y2 > fb->height))
		वापस -EINVAL;

	अगर (import_attach) अणु
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf,
					       DMA_FROM_DEVICE);
		अगर (ret)
			वापस ret;
	पूर्ण

	urb = udl_get_urb(dev);
	अगर (!urb) अणु
		ret = -ENOMEM;
		जाओ out_dma_buf_end_cpu_access;
	पूर्ण
	cmd = urb->transfer_buffer;

	क्रम (i = clip.y1; i < clip.y2; i++) अणु
		स्थिर पूर्णांक line_offset = fb->pitches[0] * i;
		स्थिर पूर्णांक byte_offset = line_offset + (clip.x1 << log_bpp);
		स्थिर पूर्णांक dev_byte_offset = (fb->width * i + clip.x1) << log_bpp;
		स्थिर पूर्णांक byte_width = (clip.x2 - clip.x1) << log_bpp;
		ret = udl_render_hline(dev, log_bpp, &urb, (अक्षर *)vaddr,
				       &cmd, byte_offset, dev_byte_offset,
				       byte_width);
		अगर (ret)
			जाओ out_dma_buf_end_cpu_access;
	पूर्ण

	अगर (cmd > (अक्षर *)urb->transfer_buffer) अणु
		/* Send partial buffer reमुख्यing beक्रमe निकासing */
		पूर्णांक len;
		अगर (cmd < (अक्षर *)urb->transfer_buffer + urb->transfer_buffer_length)
			*cmd++ = 0xAF;
		len = cmd - (अक्षर *)urb->transfer_buffer;
		ret = udl_submit_urb(dev, urb, len);
	पूर्ण अन्यथा अणु
		udl_urb_completion(urb);
	पूर्ण

	ret = 0;

out_dma_buf_end_cpu_access:
	अगर (import_attach) अणु
		पंचांगp_ret = dma_buf_end_cpu_access(import_attach->dmabuf,
						 DMA_FROM_DEVICE);
		अगर (पंचांगp_ret && !ret)
			ret = पंचांगp_ret; /* only update ret अगर not set yet */
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Simple display pipeline
 */

अटल स्थिर uपूर्णांक32_t udl_simple_display_pipe_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल क्रमागत drm_mode_status
udl_simple_display_pipe_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
				   स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल व्योम
udl_simple_display_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा udl_device *udl = to_udl(dev);
	काष्ठा drm_display_mode *mode = &crtc_state->mode;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);
	अक्षर *buf;
	अक्षर *wrptr;
	पूर्णांक color_depth = UDL_COLOR_DEPTH_16BPP;

	buf = (अक्षर *)udl->mode_buf;

	/* This first section has to करो with setting the base address on the
	 * controller associated with the display. There are 2 base
	 * poपूर्णांकers, currently, we only use the 16 bpp segment.
	 */
	wrptr = udl_vidreg_lock(buf);
	wrptr = udl_set_color_depth(wrptr, color_depth);
	/* set base क्रम 16bpp segment to 0 */
	wrptr = udl_set_base16bpp(wrptr, 0);
	/* set base क्रम 8bpp segment to end of fb */
	wrptr = udl_set_base8bpp(wrptr, 2 * mode->vdisplay * mode->hdisplay);

	wrptr = udl_set_vid_cmds(wrptr, mode);
	wrptr = udl_set_blank_mode(wrptr, UDL_BLANK_MODE_ON);
	wrptr = udl_vidreg_unlock(wrptr);

	wrptr = udl_dummy_render(wrptr);

	udl->mode_buf_len = wrptr - buf;

	udl_handle_damage(fb, &shaकरोw_plane_state->map[0], 0, 0, fb->width, fb->height);

	अगर (!crtc_state->mode_changed)
		वापस;

	/* enable display */
	udl_crtc_ग_लिखो_mode_to_hw(crtc);
पूर्ण

अटल व्योम
udl_simple_display_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा urb *urb;
	अक्षर *buf;

	urb = udl_get_urb(dev);
	अगर (!urb)
		वापस;

	buf = (अक्षर *)urb->transfer_buffer;
	buf = udl_vidreg_lock(buf);
	buf = udl_set_blank_mode(buf, UDL_BLANK_MODE_POWERDOWN);
	buf = udl_vidreg_unlock(buf);
	buf = udl_dummy_render(buf);

	udl_submit_urb(dev, urb, buf - (अक्षर *)urb->transfer_buffer);
पूर्ण

अटल व्योम
udl_simple_display_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_plane_state *old_plane_state)
अणु
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(state);
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_rect rect;

	अगर (!fb)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_plane_state, state, &rect))
		udl_handle_damage(fb, &shaकरोw_plane_state->map[0], rect.x1, rect.y1,
				  rect.x2 - rect.x1, rect.y2 - rect.y1);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs udl_simple_display_pipe_funcs = अणु
	.mode_valid = udl_simple_display_pipe_mode_valid,
	.enable = udl_simple_display_pipe_enable,
	.disable = udl_simple_display_pipe_disable,
	.update = udl_simple_display_pipe_update,
	DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS,
पूर्ण;

/*
 * Modesetting
 */

अटल स्थिर काष्ठा drm_mode_config_funcs udl_mode_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.atomic_check  = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक udl_modeset_init(काष्ठा drm_device *dev)
अणु
	माप_प्रकार क्रमmat_count = ARRAY_SIZE(udl_simple_display_pipe_क्रमmats);
	काष्ठा udl_device *udl = to_udl(dev);
	काष्ठा drm_connector *connector;
	पूर्णांक ret;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	dev->mode_config.min_width = 640;
	dev->mode_config.min_height = 480;

	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;

	dev->mode_config.prefer_shaकरोw = 0;
	dev->mode_config.preferred_depth = 16;

	dev->mode_config.funcs = &udl_mode_funcs;

	connector = udl_connector_init(dev);
	अगर (IS_ERR(connector))
		वापस PTR_ERR(connector);

	क्रमmat_count = ARRAY_SIZE(udl_simple_display_pipe_क्रमmats);

	ret = drm_simple_display_pipe_init(dev, &udl->display_pipe,
					   &udl_simple_display_pipe_funcs,
					   udl_simple_display_pipe_क्रमmats,
					   क्रमmat_count, शून्य, connector);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(dev);

	वापस 0;
पूर्ण
