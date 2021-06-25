<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2012-2019 Red Hat
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License version 2. See the file COPYING in the मुख्य
 * directory of this archive क्रम more details.
 *
 * Authors: Matthew Garrett
 *	    Dave Airlie
 *	    Gerd Hoffmann
 *
 * Portions of this code derived from cirrusfb.c:
 * drivers/video/cirrusfb.c - driver क्रम Cirrus Logic chipsets
 *
 * Copyright 1999-2001 Jeff Garzik <jgarzik@pobox.com>
 */

#समावेश <linux/console.h>
#समावेश <linux/dma-buf-map.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <video/cirrus.h>
#समावेश <video/vga.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#घोषणा DRIVER_NAME "cirrus"
#घोषणा DRIVER_DESC "qemu cirrus vga"
#घोषणा DRIVER_DATE "2019"
#घोषणा DRIVER_MAJOR 2
#घोषणा DRIVER_MINOR 0

#घोषणा CIRRUS_MAX_PITCH (0x1FF << 3)      /* (4096 - 1) & ~111b bytes */
#घोषणा CIRRUS_VRAM_SIZE (4 * 1024 * 1024) /* 4 MB */

काष्ठा cirrus_device अणु
	काष्ठा drm_device	       dev;
	काष्ठा drm_simple_display_pipe pipe;
	काष्ठा drm_connector	       conn;
	अचिन्हित पूर्णांक		       cpp;
	अचिन्हित पूर्णांक		       pitch;
	व्योम __iomem		       *vram;
	व्योम __iomem		       *mmio;
पूर्ण;

#घोषणा to_cirrus(_dev) container_of(_dev, काष्ठा cirrus_device, dev)

/* ------------------------------------------------------------------ */
/*
 * The meat of this driver. The core passes us a mode and we have to program
 * it. The modesetting here is the bare minimum required to satisfy the qemu
 * emulation of this hardware, and running this against a real device is
 * likely to result in an inadequately programmed mode. We've alपढ़ोy had
 * the opportunity to modअगरy the mode, so whatever we receive here should
 * be something that can be correctly programmed and displayed
 */

#घोषणा SEQ_INDEX 4
#घोषणा SEQ_DATA 5

अटल u8 rreg_seq(काष्ठा cirrus_device *cirrus, u8 reg)
अणु
	ioग_लिखो8(reg, cirrus->mmio + SEQ_INDEX);
	वापस ioपढ़ो8(cirrus->mmio + SEQ_DATA);
पूर्ण

अटल व्योम wreg_seq(काष्ठा cirrus_device *cirrus, u8 reg, u8 val)
अणु
	ioग_लिखो8(reg, cirrus->mmio + SEQ_INDEX);
	ioग_लिखो8(val, cirrus->mmio + SEQ_DATA);
पूर्ण

#घोषणा CRT_INDEX 0x14
#घोषणा CRT_DATA 0x15

अटल u8 rreg_crt(काष्ठा cirrus_device *cirrus, u8 reg)
अणु
	ioग_लिखो8(reg, cirrus->mmio + CRT_INDEX);
	वापस ioपढ़ो8(cirrus->mmio + CRT_DATA);
पूर्ण

अटल व्योम wreg_crt(काष्ठा cirrus_device *cirrus, u8 reg, u8 val)
अणु
	ioग_लिखो8(reg, cirrus->mmio + CRT_INDEX);
	ioग_लिखो8(val, cirrus->mmio + CRT_DATA);
पूर्ण

#घोषणा GFX_INDEX 0xe
#घोषणा GFX_DATA 0xf

अटल व्योम wreg_gfx(काष्ठा cirrus_device *cirrus, u8 reg, u8 val)
अणु
	ioग_लिखो8(reg, cirrus->mmio + GFX_INDEX);
	ioग_लिखो8(val, cirrus->mmio + GFX_DATA);
पूर्ण

#घोषणा VGA_DAC_MASK  0x06

अटल व्योम wreg_hdr(काष्ठा cirrus_device *cirrus, u8 val)
अणु
	ioपढ़ो8(cirrus->mmio + VGA_DAC_MASK);
	ioपढ़ो8(cirrus->mmio + VGA_DAC_MASK);
	ioपढ़ो8(cirrus->mmio + VGA_DAC_MASK);
	ioपढ़ो8(cirrus->mmio + VGA_DAC_MASK);
	ioग_लिखो8(val, cirrus->mmio + VGA_DAC_MASK);
पूर्ण

अटल पूर्णांक cirrus_convert_to(काष्ठा drm_framebuffer *fb)
अणु
	अगर (fb->क्रमmat->cpp[0] == 4 && fb->pitches[0] > CIRRUS_MAX_PITCH) अणु
		अगर (fb->width * 3 <= CIRRUS_MAX_PITCH)
			/* convert from XR24 to RG24 */
			वापस 3;
		अन्यथा
			/* convert from XR24 to RG16 */
			वापस 2;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cirrus_cpp(काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक convert_cpp = cirrus_convert_to(fb);

	अगर (convert_cpp)
		वापस convert_cpp;
	वापस fb->क्रमmat->cpp[0];
पूर्ण

अटल पूर्णांक cirrus_pitch(काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक convert_cpp = cirrus_convert_to(fb);

	अगर (convert_cpp)
		वापस convert_cpp * fb->width;
	वापस fb->pitches[0];
पूर्ण

अटल व्योम cirrus_set_start_address(काष्ठा cirrus_device *cirrus, u32 offset)
अणु
	पूर्णांक idx;
	u32 addr;
	u8 पंचांगp;

	अगर (!drm_dev_enter(&cirrus->dev, &idx))
		वापस;

	addr = offset >> 2;
	wreg_crt(cirrus, 0x0c, (u8)((addr >> 8) & 0xff));
	wreg_crt(cirrus, 0x0d, (u8)(addr & 0xff));

	पंचांगp = rreg_crt(cirrus, 0x1b);
	पंचांगp &= 0xf2;
	पंचांगp |= (addr >> 16) & 0x01;
	पंचांगp |= (addr >> 15) & 0x0c;
	wreg_crt(cirrus, 0x1b, पंचांगp);

	पंचांगp = rreg_crt(cirrus, 0x1d);
	पंचांगp &= 0x7f;
	पंचांगp |= (addr >> 12) & 0x80;
	wreg_crt(cirrus, 0x1d, पंचांगp);

	drm_dev_निकास(idx);
पूर्ण

अटल पूर्णांक cirrus_mode_set(काष्ठा cirrus_device *cirrus,
			   काष्ठा drm_display_mode *mode,
			   काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक hsyncstart, hsyncend, htotal, hdispend;
	पूर्णांक vtotal, vdispend;
	पूर्णांक पंचांगp, idx;
	पूर्णांक sr07 = 0, hdr = 0;

	अगर (!drm_dev_enter(&cirrus->dev, &idx))
		वापस -1;

	htotal = mode->htotal / 8;
	hsyncend = mode->hsync_end / 8;
	hsyncstart = mode->hsync_start / 8;
	hdispend = mode->hdisplay / 8;

	vtotal = mode->vtotal;
	vdispend = mode->vdisplay;

	vdispend -= 1;
	vtotal -= 2;

	htotal -= 5;
	hdispend -= 1;
	hsyncstart += 1;
	hsyncend += 1;

	wreg_crt(cirrus, VGA_CRTC_V_SYNC_END, 0x20);
	wreg_crt(cirrus, VGA_CRTC_H_TOTAL, htotal);
	wreg_crt(cirrus, VGA_CRTC_H_DISP, hdispend);
	wreg_crt(cirrus, VGA_CRTC_H_SYNC_START, hsyncstart);
	wreg_crt(cirrus, VGA_CRTC_H_SYNC_END, hsyncend);
	wreg_crt(cirrus, VGA_CRTC_V_TOTAL, vtotal & 0xff);
	wreg_crt(cirrus, VGA_CRTC_V_DISP_END, vdispend & 0xff);

	पंचांगp = 0x40;
	अगर ((vdispend + 1) & 512)
		पंचांगp |= 0x20;
	wreg_crt(cirrus, VGA_CRTC_MAX_SCAN, पंचांगp);

	/*
	 * Overflow bits क्रम values that करोn't fit in the standard रेजिस्टरs
	 */
	पंचांगp = 0x10;
	अगर (vtotal & 0x100)
		पंचांगp |= 0x01;
	अगर (vdispend & 0x100)
		पंचांगp |= 0x02;
	अगर ((vdispend + 1) & 0x100)
		पंचांगp |= 0x08;
	अगर (vtotal & 0x200)
		पंचांगp |= 0x20;
	अगर (vdispend & 0x200)
		पंचांगp |= 0x40;
	wreg_crt(cirrus, VGA_CRTC_OVERFLOW, पंचांगp);

	पंचांगp = 0;

	/* More overflow bits */

	अगर ((htotal + 5) & 0x40)
		पंचांगp |= 0x10;
	अगर ((htotal + 5) & 0x80)
		पंचांगp |= 0x20;
	अगर (vtotal & 0x100)
		पंचांगp |= 0x40;
	अगर (vtotal & 0x200)
		पंचांगp |= 0x80;

	wreg_crt(cirrus, CL_CRT1A, पंचांगp);

	/* Disable Hercules/CGA compatibility */
	wreg_crt(cirrus, VGA_CRTC_MODE, 0x03);

	sr07 = rreg_seq(cirrus, 0x07);
	sr07 &= 0xe0;
	hdr = 0;

	cirrus->cpp = cirrus_cpp(fb);
	चयन (cirrus->cpp * 8) अणु
	हाल 8:
		sr07 |= 0x11;
		अवरोध;
	हाल 16:
		sr07 |= 0x17;
		hdr = 0xc1;
		अवरोध;
	हाल 24:
		sr07 |= 0x15;
		hdr = 0xc5;
		अवरोध;
	हाल 32:
		sr07 |= 0x19;
		hdr = 0xc5;
		अवरोध;
	शेष:
		drm_dev_निकास(idx);
		वापस -1;
	पूर्ण

	wreg_seq(cirrus, 0x7, sr07);

	/* Program the pitch */
	cirrus->pitch = cirrus_pitch(fb);
	पंचांगp = cirrus->pitch / 8;
	wreg_crt(cirrus, VGA_CRTC_OFFSET, पंचांगp);

	/* Enable extended blanking and pitch bits, and enable full memory */
	पंचांगp = 0x22;
	पंचांगp |= (cirrus->pitch >> 7) & 0x10;
	पंचांगp |= (cirrus->pitch >> 6) & 0x40;
	wreg_crt(cirrus, 0x1b, पंचांगp);

	/* Enable high-colour modes */
	wreg_gfx(cirrus, VGA_GFX_MODE, 0x40);

	/* And set graphics mode */
	wreg_gfx(cirrus, VGA_GFX_MISC, 0x01);

	wreg_hdr(cirrus, hdr);

	cirrus_set_start_address(cirrus, 0);

	/* Unblank (needed on S3 resume, vgabios करोesn't करो it then) */
	outb(0x20, 0x3c0);

	drm_dev_निकास(idx);
	वापस 0;
पूर्ण

अटल पूर्णांक cirrus_fb_blit_rect(काष्ठा drm_framebuffer *fb, स्थिर काष्ठा dma_buf_map *map,
			       काष्ठा drm_rect *rect)
अणु
	काष्ठा cirrus_device *cirrus = to_cirrus(fb->dev);
	व्योम *vmap = map->vaddr; /* TODO: Use mapping असलtraction properly */
	पूर्णांक idx;

	अगर (!drm_dev_enter(&cirrus->dev, &idx))
		वापस -ENODEV;

	अगर (cirrus->cpp == fb->क्रमmat->cpp[0])
		drm_fb_स_नकल_dstclip(cirrus->vram,
				      vmap, fb, rect);

	अन्यथा अगर (fb->क्रमmat->cpp[0] == 4 && cirrus->cpp == 2)
		drm_fb_xrgb8888_to_rgb565_dstclip(cirrus->vram,
						  cirrus->pitch,
						  vmap, fb, rect, false);

	अन्यथा अगर (fb->क्रमmat->cpp[0] == 4 && cirrus->cpp == 3)
		drm_fb_xrgb8888_to_rgb888_dstclip(cirrus->vram,
						  cirrus->pitch,
						  vmap, fb, rect);

	अन्यथा
		WARN_ON_ONCE("cpp mismatch");

	drm_dev_निकास(idx);

	वापस 0;
पूर्ण

अटल पूर्णांक cirrus_fb_blit_fullscreen(काष्ठा drm_framebuffer *fb, स्थिर काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_rect fullscreen = अणु
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	पूर्ण;
	वापस cirrus_fb_blit_rect(fb, map, &fullscreen);
पूर्ण

अटल पूर्णांक cirrus_check_size(पूर्णांक width, पूर्णांक height,
			     काष्ठा drm_framebuffer *fb)
अणु
	पूर्णांक pitch = width * 2;

	अगर (fb)
		pitch = cirrus_pitch(fb);

	अगर (pitch > CIRRUS_MAX_PITCH)
		वापस -EINVAL;
	अगर (pitch * height > CIRRUS_VRAM_SIZE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */
/* cirrus connector						      */

अटल पूर्णांक cirrus_conn_get_modes(काष्ठा drm_connector *conn)
अणु
	पूर्णांक count;

	count = drm_add_modes_noedid(conn,
				     conn->dev->mode_config.max_width,
				     conn->dev->mode_config.max_height);
	drm_set_preferred_mode(conn, 1024, 768);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs cirrus_conn_helper_funcs = अणु
	.get_modes = cirrus_conn_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cirrus_conn_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक cirrus_conn_init(काष्ठा cirrus_device *cirrus)
अणु
	drm_connector_helper_add(&cirrus->conn, &cirrus_conn_helper_funcs);
	वापस drm_connector_init(&cirrus->dev, &cirrus->conn,
				  &cirrus_conn_funcs, DRM_MODE_CONNECTOR_VGA);

पूर्ण

/* ------------------------------------------------------------------ */
/* cirrus (simple) display pipe					      */

अटल क्रमागत drm_mode_status cirrus_pipe_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
						   स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (cirrus_check_size(mode->hdisplay, mode->vdisplay, शून्य) < 0)
		वापस MODE_BAD;
	वापस MODE_OK;
पूर्ण

अटल पूर्णांक cirrus_pipe_check(काष्ठा drm_simple_display_pipe *pipe,
			     काष्ठा drm_plane_state *plane_state,
			     काष्ठा drm_crtc_state *crtc_state)
अणु
	काष्ठा drm_framebuffer *fb = plane_state->fb;

	अगर (!fb)
		वापस 0;
	वापस cirrus_check_size(fb->width, fb->height, fb);
पूर्ण

अटल व्योम cirrus_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा cirrus_device *cirrus = to_cirrus(pipe->crtc.dev);
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);

	cirrus_mode_set(cirrus, &crtc_state->mode, plane_state->fb);
	cirrus_fb_blit_fullscreen(plane_state->fb, &shaकरोw_plane_state->map[0]);
पूर्ण

अटल व्योम cirrus_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा cirrus_device *cirrus = to_cirrus(pipe->crtc.dev);
	काष्ठा drm_plane_state *state = pipe->plane.state;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(state);
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_rect rect;

	अगर (state->fb && cirrus->cpp != cirrus_cpp(state->fb))
		cirrus_mode_set(cirrus, &crtc->mode, state->fb);

	अगर (drm_atomic_helper_damage_merged(old_state, state, &rect))
		cirrus_fb_blit_rect(state->fb, &shaकरोw_plane_state->map[0], &rect);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs cirrus_pipe_funcs = अणु
	.mode_valid = cirrus_pipe_mode_valid,
	.check	    = cirrus_pipe_check,
	.enable	    = cirrus_pipe_enable,
	.update	    = cirrus_pipe_update,
	DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS,
पूर्ण;

अटल स्थिर uपूर्णांक32_t cirrus_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक64_t cirrus_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल पूर्णांक cirrus_pipe_init(काष्ठा cirrus_device *cirrus)
अणु
	वापस drm_simple_display_pipe_init(&cirrus->dev,
					    &cirrus->pipe,
					    &cirrus_pipe_funcs,
					    cirrus_क्रमmats,
					    ARRAY_SIZE(cirrus_क्रमmats),
					    cirrus_modअगरiers,
					    &cirrus->conn);
पूर्ण

/* ------------------------------------------------------------------ */
/* cirrus framebuffers & mode config				      */

अटल काष्ठा drm_framebuffer*
cirrus_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
		 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	अगर (mode_cmd->pixel_क्रमmat != DRM_FORMAT_RGB565 &&
	    mode_cmd->pixel_क्रमmat != DRM_FORMAT_RGB888 &&
	    mode_cmd->pixel_क्रमmat != DRM_FORMAT_XRGB8888)
		वापस ERR_PTR(-EINVAL);
	अगर (cirrus_check_size(mode_cmd->width, mode_cmd->height, शून्य) < 0)
		वापस ERR_PTR(-EINVAL);
	वापस drm_gem_fb_create_with_dirty(dev, file_priv, mode_cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs cirrus_mode_config_funcs = अणु
	.fb_create = cirrus_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक cirrus_mode_config_init(काष्ठा cirrus_device *cirrus)
अणु
	काष्ठा drm_device *dev = &cirrus->dev;
	पूर्णांक ret;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = CIRRUS_MAX_PITCH / 2;
	dev->mode_config.max_height = 1024;
	dev->mode_config.preferred_depth = 16;
	dev->mode_config.prefer_shaकरोw = 0;
	dev->mode_config.funcs = &cirrus_mode_config_funcs;

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

DEFINE_DRM_GEM_FOPS(cirrus_fops);

अटल स्थिर काष्ठा drm_driver cirrus_driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM | DRIVER_ATOMIC,

	.name		 = DRIVER_NAME,
	.desc		 = DRIVER_DESC,
	.date		 = DRIVER_DATE,
	.major		 = DRIVER_MAJOR,
	.minor		 = DRIVER_MINOR,

	.fops		 = &cirrus_fops,
	DRM_GEM_SHMEM_DRIVER_OPS,
पूर्ण;

अटल पूर्णांक cirrus_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा drm_device *dev;
	काष्ठा cirrus_device *cirrus;
	पूर्णांक ret;

	ret = drm_fb_helper_हटाओ_conflicting_pci_framebuffers(pdev, "cirrusdrmfb");
	अगर (ret)
		वापस ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret)
		वापस ret;

	ret = -ENOMEM;
	cirrus = devm_drm_dev_alloc(&pdev->dev, &cirrus_driver,
				    काष्ठा cirrus_device, dev);
	अगर (IS_ERR(cirrus))
		वापस PTR_ERR(cirrus);

	dev = &cirrus->dev;

	cirrus->vram = devm_ioremap(&pdev->dev, pci_resource_start(pdev, 0),
				    pci_resource_len(pdev, 0));
	अगर (cirrus->vram == शून्य)
		वापस -ENOMEM;

	cirrus->mmio = devm_ioremap(&pdev->dev, pci_resource_start(pdev, 1),
				    pci_resource_len(pdev, 1));
	अगर (cirrus->mmio == शून्य)
		वापस -ENOMEM;

	ret = cirrus_mode_config_init(cirrus);
	अगर (ret)
		वापस ret;

	ret = cirrus_conn_init(cirrus);
	अगर (ret < 0)
		वापस ret;

	ret = cirrus_pipe_init(cirrus);
	अगर (ret < 0)
		वापस ret;

	drm_mode_config_reset(dev);

	pci_set_drvdata(pdev, dev);
	ret = drm_dev_रेजिस्टर(dev, 0);
	अगर (ret)
		वापस ret;

	drm_fbdev_generic_setup(dev, dev->mode_config.preferred_depth);
	वापस 0;
पूर्ण

अटल व्योम cirrus_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unplug(dev);
	drm_atomic_helper_shutकरोwn(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
	अणु
		.venकरोr    = PCI_VENDOR_ID_CIRRUS,
		.device    = PCI_DEVICE_ID_CIRRUS_5446,
		/* only bind to the cirrus chip in qemu */
		.subvenकरोr = PCI_SUBVENDOR_ID_REDHAT_QUMRANET,
		.subdevice = PCI_SUBDEVICE_ID_QEMU,
	पूर्ण, अणु
		.venकरोr    = PCI_VENDOR_ID_CIRRUS,
		.device    = PCI_DEVICE_ID_CIRRUS_5446,
		.subvenकरोr = PCI_VENDOR_ID_XEN,
		.subdevice = 0x0001,
	पूर्ण,
	अणु /* end अगर list */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver cirrus_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = cirrus_pci_probe,
	.हटाओ = cirrus_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init cirrus_init(व्योम)
अणु
	अगर (vgacon_text_क्रमce())
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&cirrus_pci_driver);
पूर्ण

अटल व्योम __निकास cirrus_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cirrus_pci_driver);
पूर्ण

module_init(cirrus_init);
module_निकास(cirrus_निकास);

MODULE_DEVICE_TABLE(pci, pciidlist);
MODULE_LICENSE("GPL");
