<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * shmob_drm_kms.c  --  SH Mobile DRM Mode Setting
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "shmob_drm_crtc.h"
#समावेश "shmob_drm_drv.h"
#समावेश "shmob_drm_kms.h"
#समावेश "shmob_drm_regs.h"

/* -----------------------------------------------------------------------------
 * Format helpers
 */

अटल स्थिर काष्ठा shmob_drm_क्रमmat_info shmob_drm_क्रमmat_infos[] = अणु
	अणु
		.fourcc = DRM_FORMAT_RGB565,
		.bpp = 16,
		.yuv = false,
		.lddfr = LDDFR_PKF_RGB16,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGB888,
		.bpp = 24,
		.yuv = false,
		.lddfr = LDDFR_PKF_RGB24,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ARGB8888,
		.bpp = 32,
		.yuv = false,
		.lddfr = LDDFR_PKF_ARGB32,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV12,
		.bpp = 12,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_420,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV21,
		.bpp = 12,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_420,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV16,
		.bpp = 16,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_422,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV61,
		.bpp = 16,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_422,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV24,
		.bpp = 24,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_444,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV42,
		.bpp = 24,
		.yuv = true,
		.lddfr = LDDFR_CC | LDDFR_YF_444,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा shmob_drm_क्रमmat_info *shmob_drm_क्रमmat_info(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(shmob_drm_क्रमmat_infos); ++i) अणु
		अगर (shmob_drm_क्रमmat_infos[i].fourcc == fourcc)
			वापस &shmob_drm_क्रमmat_infos[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame buffer
 */

अटल काष्ठा drm_framebuffer *
shmob_drm_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
		    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	स्थिर काष्ठा shmob_drm_क्रमmat_info *क्रमmat;

	क्रमmat = shmob_drm_क्रमmat_info(mode_cmd->pixel_क्रमmat);
	अगर (क्रमmat == शून्य) अणु
		dev_dbg(dev->dev, "unsupported pixel format %08x\n",
			mode_cmd->pixel_क्रमmat);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (mode_cmd->pitches[0] & 7 || mode_cmd->pitches[0] >= 65536) अणु
		dev_dbg(dev->dev, "invalid pitch value %u\n",
			mode_cmd->pitches[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (क्रमmat->yuv) अणु
		अचिन्हित पूर्णांक chroma_cpp = क्रमmat->bpp == 24 ? 2 : 1;

		अगर (mode_cmd->pitches[1] != mode_cmd->pitches[0] * chroma_cpp) अणु
			dev_dbg(dev->dev,
				"luma and chroma pitches do not match\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	वापस drm_gem_fb_create(dev, file_priv, mode_cmd);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs shmob_drm_mode_config_funcs = अणु
	.fb_create = shmob_drm_fb_create,
पूर्ण;

पूर्णांक shmob_drm_modeset_init(काष्ठा shmob_drm_device *sdev)
अणु
	पूर्णांक ret;

	ret = drmm_mode_config_init(sdev->ddev);
	अगर (ret)
		वापस ret;

	shmob_drm_crtc_create(sdev);
	shmob_drm_encoder_create(sdev);
	shmob_drm_connector_create(sdev, &sdev->encoder.encoder);

	drm_kms_helper_poll_init(sdev->ddev);

	sdev->ddev->mode_config.min_width = 0;
	sdev->ddev->mode_config.min_height = 0;
	sdev->ddev->mode_config.max_width = 4095;
	sdev->ddev->mode_config.max_height = 4095;
	sdev->ddev->mode_config.funcs = &shmob_drm_mode_config_funcs;

	drm_helper_disable_unused_functions(sdev->ddev);

	वापस 0;
पूर्ण
