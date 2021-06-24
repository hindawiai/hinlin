<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_kms.c  --  R-Car Display Unit Mode Setting
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
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <linux/device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/रुको.h>

#समावेश "rcar_du_crtc.h"
#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_encoder.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_regs.h"
#समावेश "rcar_du_vsp.h"
#समावेश "rcar_du_writeback.h"

/* -----------------------------------------------------------------------------
 * Format helpers
 */

अटल स्थिर काष्ठा rcar_du_क्रमmat_info rcar_du_क्रमmat_infos[] = अणु
	अणु
		.fourcc = DRM_FORMAT_RGB565,
		.v4l2 = V4L2_PIX_FMT_RGB565,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
		.pnmr = PnMR_SPIM_TP | PnMR_DDDF_16BPP,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ARGB1555,
		.v4l2 = V4L2_PIX_FMT_ARGB555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
		.pnmr = PnMR_SPIM_ALP | PnMR_DDDF_ARGB,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XRGB1555,
		.v4l2 = V4L2_PIX_FMT_XRGB555,
		.bpp = 16,
		.planes = 1,
		.pnmr = PnMR_SPIM_ALP | PnMR_DDDF_ARGB,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XRGB8888,
		.v4l2 = V4L2_PIX_FMT_XBGR32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
		.pnmr = PnMR_SPIM_TP | PnMR_DDDF_16BPP,
		.edf = PnDDCR4_EDF_RGB888,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ARGB8888,
		.v4l2 = V4L2_PIX_FMT_ABGR32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
		.pnmr = PnMR_SPIM_ALP | PnMR_DDDF_16BPP,
		.edf = PnDDCR4_EDF_ARGB8888,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_UYVY,
		.v4l2 = V4L2_PIX_FMT_UYVY,
		.bpp = 16,
		.planes = 1,
		.hsub = 2,
		.pnmr = PnMR_SPIM_TP_OFF | PnMR_DDDF_YC,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YUYV,
		.v4l2 = V4L2_PIX_FMT_YUYV,
		.bpp = 16,
		.planes = 1,
		.hsub = 2,
		.pnmr = PnMR_SPIM_TP_OFF | PnMR_DDDF_YC,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV12,
		.v4l2 = V4L2_PIX_FMT_NV12M,
		.bpp = 12,
		.planes = 2,
		.hsub = 2,
		.pnmr = PnMR_SPIM_TP_OFF | PnMR_DDDF_YC,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV21,
		.v4l2 = V4L2_PIX_FMT_NV21M,
		.bpp = 12,
		.planes = 2,
		.hsub = 2,
		.pnmr = PnMR_SPIM_TP_OFF | PnMR_DDDF_YC,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV16,
		.v4l2 = V4L2_PIX_FMT_NV16M,
		.bpp = 16,
		.planes = 2,
		.hsub = 2,
		.pnmr = PnMR_SPIM_TP_OFF | PnMR_DDDF_YC,
		.edf = PnDDCR4_EDF_NONE,
	पूर्ण,
	/*
	 * The following क्रमmats are not supported on Gen2 and thus have no
	 * associated .pnmr or .edf settings.
	 */
	अणु
		.fourcc = DRM_FORMAT_RGB332,
		.v4l2 = V4L2_PIX_FMT_RGB332,
		.bpp = 8,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ARGB4444,
		.v4l2 = V4L2_PIX_FMT_ARGB444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XRGB4444,
		.v4l2 = V4L2_PIX_FMT_XRGB444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBA4444,
		.v4l2 = V4L2_PIX_FMT_RGBA444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBX4444,
		.v4l2 = V4L2_PIX_FMT_RGBX444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ABGR4444,
		.v4l2 = V4L2_PIX_FMT_ABGR444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XBGR4444,
		.v4l2 = V4L2_PIX_FMT_XBGR444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRA4444,
		.v4l2 = V4L2_PIX_FMT_BGRA444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRX4444,
		.v4l2 = V4L2_PIX_FMT_BGRX444,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBA5551,
		.v4l2 = V4L2_PIX_FMT_RGBA555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBX5551,
		.v4l2 = V4L2_PIX_FMT_RGBX555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ABGR1555,
		.v4l2 = V4L2_PIX_FMT_ABGR555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XBGR1555,
		.v4l2 = V4L2_PIX_FMT_XBGR555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRA5551,
		.v4l2 = V4L2_PIX_FMT_BGRA555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRX5551,
		.v4l2 = V4L2_PIX_FMT_BGRX555,
		.bpp = 16,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGR888,
		.v4l2 = V4L2_PIX_FMT_RGB24,
		.bpp = 24,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGB888,
		.v4l2 = V4L2_PIX_FMT_BGR24,
		.bpp = 24,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBA8888,
		.v4l2 = V4L2_PIX_FMT_BGRA32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_RGBX8888,
		.v4l2 = V4L2_PIX_FMT_BGRX32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_ABGR8888,
		.v4l2 = V4L2_PIX_FMT_RGBA32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_XBGR8888,
		.v4l2 = V4L2_PIX_FMT_RGBX32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRA8888,
		.v4l2 = V4L2_PIX_FMT_ARGB32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_BGRX8888,
		.v4l2 = V4L2_PIX_FMT_XRGB32,
		.bpp = 32,
		.planes = 1,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YVYU,
		.v4l2 = V4L2_PIX_FMT_YVYU,
		.bpp = 16,
		.planes = 1,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_NV61,
		.v4l2 = V4L2_PIX_FMT_NV61M,
		.bpp = 16,
		.planes = 2,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YUV420,
		.v4l2 = V4L2_PIX_FMT_YUV420M,
		.bpp = 12,
		.planes = 3,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YVU420,
		.v4l2 = V4L2_PIX_FMT_YVU420M,
		.bpp = 12,
		.planes = 3,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YUV422,
		.v4l2 = V4L2_PIX_FMT_YUV422M,
		.bpp = 16,
		.planes = 3,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YVU422,
		.v4l2 = V4L2_PIX_FMT_YVU422M,
		.bpp = 16,
		.planes = 3,
		.hsub = 2,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YUV444,
		.v4l2 = V4L2_PIX_FMT_YUV444M,
		.bpp = 24,
		.planes = 3,
		.hsub = 1,
	पूर्ण, अणु
		.fourcc = DRM_FORMAT_YVU444,
		.v4l2 = V4L2_PIX_FMT_YVU444M,
		.bpp = 24,
		.planes = 3,
		.hsub = 1,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा rcar_du_क्रमmat_info *rcar_du_क्रमmat_info(u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rcar_du_क्रमmat_infos); ++i) अणु
		अगर (rcar_du_क्रमmat_infos[i].fourcc == fourcc)
			वापस &rcar_du_क्रमmat_infos[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Frame buffer
 */

पूर्णांक rcar_du_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	अचिन्हित पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	अचिन्हित पूर्णांक align;

	/*
	 * The R8A7779 DU requires a 16 pixels pitch alignment as करोcumented,
	 * but the R8A7790 DU seems to require a 128 bytes pitch alignment.
	 */
	अगर (rcar_du_needs(rcdu, RCAR_DU_QUIRK_ALIGN_128B))
		align = 128;
	अन्यथा
		align = 16 * args->bpp / 8;

	args->pitch = roundup(min_pitch, align);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file, dev, args);
पूर्ण

अटल काष्ठा drm_framebuffer *
rcar_du_fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv,
		  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	स्थिर काष्ठा rcar_du_क्रमmat_info *क्रमmat;
	अचिन्हित पूर्णांक chroma_pitch;
	अचिन्हित पूर्णांक max_pitch;
	अचिन्हित पूर्णांक align;
	अचिन्हित पूर्णांक i;

	क्रमmat = rcar_du_क्रमmat_info(mode_cmd->pixel_क्रमmat);
	अगर (क्रमmat == शून्य) अणु
		dev_dbg(dev->dev, "unsupported pixel format %08x\n",
			mode_cmd->pixel_क्रमmat);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (rcdu->info->gen < 3) अणु
		/*
		 * On Gen2 the DU limits the pitch to 4095 pixels and requires
		 * buffers to be aligned to a 16 pixels boundary (or 128 bytes
		 * on some platक्रमms).
		 */
		अचिन्हित पूर्णांक bpp = क्रमmat->planes == 1 ? क्रमmat->bpp / 8 : 1;

		max_pitch = 4095 * bpp;

		अगर (rcar_du_needs(rcdu, RCAR_DU_QUIRK_ALIGN_128B))
			align = 128;
		अन्यथा
			align = 16 * bpp;
	पूर्ण अन्यथा अणु
		/*
		 * On Gen3 the memory पूर्णांकerface is handled by the VSP that
		 * limits the pitch to 65535 bytes and has no alignment
		 * स्थिरraपूर्णांक.
		 */
		max_pitch = 65535;
		align = 1;
	पूर्ण

	अगर (mode_cmd->pitches[0] & (align - 1) ||
	    mode_cmd->pitches[0] > max_pitch) अणु
		dev_dbg(dev->dev, "invalid pitch value %u\n",
			mode_cmd->pitches[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Calculate the chroma plane(s) pitch using the horizontal subsampling
	 * factor. For semi-planar क्रमmats, the U and V planes are combined, the
	 * pitch must thus be द्विगुनd.
	 */
	chroma_pitch = mode_cmd->pitches[0] / क्रमmat->hsub;
	अगर (क्रमmat->planes == 2)
		chroma_pitch *= 2;

	क्रम (i = 1; i < क्रमmat->planes; ++i) अणु
		अगर (mode_cmd->pitches[i] != chroma_pitch) अणु
			dev_dbg(dev->dev,
				"luma and chroma pitches are not compatible\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	वापस drm_gem_fb_create(dev, file_priv, mode_cmd);
पूर्ण

/* -----------------------------------------------------------------------------
 * Atomic Check and Update
 */

अटल पूर्णांक rcar_du_atomic_check(काष्ठा drm_device *dev,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	पूर्णांक ret;

	ret = drm_atomic_helper_check(dev, state);
	अगर (ret)
		वापस ret;

	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE))
		वापस 0;

	वापस rcar_du_atomic_check_planes(dev, state);
पूर्ण

अटल व्योम rcar_du_atomic_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i;

	/*
	 * Store RGB routing to DPAD0 and DPAD1, the hardware will be configured
	 * when starting the CRTCs.
	 */
	rcdu->dpad1_source = -1;

	क्रम_each_new_crtc_in_state(old_state, crtc, crtc_state, i) अणु
		काष्ठा rcar_du_crtc_state *rcrtc_state =
			to_rcar_crtc_state(crtc_state);
		काष्ठा rcar_du_crtc *rcrtc = to_rcar_crtc(crtc);

		अगर (rcrtc_state->outमाला_दो & BIT(RCAR_DU_OUTPUT_DPAD0))
			rcdu->dpad0_source = rcrtc->index;

		अगर (rcrtc_state->outमाला_दो & BIT(RCAR_DU_OUTPUT_DPAD1))
			rcdu->dpad1_source = rcrtc->index;
	पूर्ण

	/* Apply the atomic update. */
	drm_atomic_helper_commit_modeset_disables(dev, old_state);
	drm_atomic_helper_commit_planes(dev, old_state,
					DRM_PLANE_COMMIT_ACTIVE_ONLY);
	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);
	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, old_state);

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization
 */

अटल स्थिर काष्ठा drm_mode_config_helper_funcs rcar_du_mode_config_helper = अणु
	.atomic_commit_tail = rcar_du_atomic_commit_tail,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_funcs rcar_du_mode_config_funcs = अणु
	.fb_create = rcar_du_fb_create,
	.atomic_check = rcar_du_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक rcar_du_encoders_init_one(काष्ठा rcar_du_device *rcdu,
				     क्रमागत rcar_du_output output,
				     काष्ठा of_endpoपूर्णांक *ep)
अणु
	काष्ठा device_node *entity;
	पूर्णांक ret;

	/* Locate the connected entity and initialize the encoder. */
	entity = of_graph_get_remote_port_parent(ep->local_node);
	अगर (!entity) अणु
		dev_dbg(rcdu->dev, "unconnected endpoint %pOF, skipping\n",
			ep->local_node);
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_available(entity)) अणु
		dev_dbg(rcdu->dev,
			"connected entity %pOF is disabled, skipping\n",
			entity);
		of_node_put(entity);
		वापस -ENODEV;
	पूर्ण

	ret = rcar_du_encoder_init(rcdu, output, entity);
	अगर (ret && ret != -EPROBE_DEFER && ret != -ENOLINK)
		dev_warn(rcdu->dev,
			 "failed to initialize encoder %pOF on output %u (%d), skipping\n",
			 entity, output, ret);

	of_node_put(entity);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_du_encoders_init(काष्ठा rcar_du_device *rcdu)
अणु
	काष्ठा device_node *np = rcdu->dev->of_node;
	काष्ठा device_node *ep_node;
	अचिन्हित पूर्णांक num_encoders = 0;

	/*
	 * Iterate over the endpoपूर्णांकs and create one encoder क्रम each output
	 * pipeline.
	 */
	क्रम_each_endpoपूर्णांक_of_node(np, ep_node) अणु
		क्रमागत rcar_du_output output;
		काष्ठा of_endpoपूर्णांक ep;
		अचिन्हित पूर्णांक i;
		पूर्णांक ret;

		ret = of_graph_parse_endpoपूर्णांक(ep_node, &ep);
		अगर (ret < 0) अणु
			of_node_put(ep_node);
			वापस ret;
		पूर्ण

		/* Find the output route corresponding to the port number. */
		क्रम (i = 0; i < RCAR_DU_OUTPUT_MAX; ++i) अणु
			अगर (rcdu->info->routes[i].possible_crtcs &&
			    rcdu->info->routes[i].port == ep.port) अणु
				output = i;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == RCAR_DU_OUTPUT_MAX) अणु
			dev_warn(rcdu->dev,
				 "port %u references unexisting output, skipping\n",
				 ep.port);
			जारी;
		पूर्ण

		/* Process the output pipeline. */
		ret = rcar_du_encoders_init_one(rcdu, output, &ep);
		अगर (ret < 0) अणु
			अगर (ret == -EPROBE_DEFER) अणु
				of_node_put(ep_node);
				वापस ret;
			पूर्ण

			जारी;
		पूर्ण

		num_encoders++;
	पूर्ण

	वापस num_encoders;
पूर्ण

अटल पूर्णांक rcar_du_properties_init(काष्ठा rcar_du_device *rcdu)
अणु
	/*
	 * The color key is expressed as an RGB888 triplet stored in a 32-bit
	 * पूर्णांकeger in XRGB8888 क्रमmat. Bit 24 is used as a flag to disable (0)
	 * or enable source color keying (1).
	 */
	rcdu->props.colorkey =
		drm_property_create_range(&rcdu->ddev, 0, "colorkey",
					  0, 0x01ffffff);
	अगर (rcdu->props.colorkey == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_du_vsps_init(काष्ठा rcar_du_device *rcdu)
अणु
	स्थिर काष्ठा device_node *np = rcdu->dev->of_node;
	स्थिर अक्षर *vsps_prop_name = "renesas,vsps";
	काष्ठा of_phandle_args args;
	काष्ठा अणु
		काष्ठा device_node *np;
		अचिन्हित पूर्णांक crtcs_mask;
	पूर्ण vsps[RCAR_DU_MAX_VSPS] = अणु अणु शून्य, पूर्ण, पूर्ण;
	अचिन्हित पूर्णांक vsps_count = 0;
	अचिन्हित पूर्णांक cells;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/*
	 * First parse the DT vsps property to populate the list of VSPs. Each
	 * entry contains a poपूर्णांकer to the VSP DT node and a biपंचांगask of the
	 * connected DU CRTCs.
	 */
	ret = of_property_count_u32_elems(np, vsps_prop_name);
	अगर (ret < 0) अणु
		/* Backward compatibility with old DTBs. */
		vsps_prop_name = "vsps";
		ret = of_property_count_u32_elems(np, vsps_prop_name);
	पूर्ण
	cells = ret / rcdu->num_crtcs - 1;
	अगर (cells > 1)
		वापस -EINVAL;

	क्रम (i = 0; i < rcdu->num_crtcs; ++i) अणु
		अचिन्हित पूर्णांक j;

		ret = of_parse_phandle_with_fixed_args(np, vsps_prop_name,
						       cells, i, &args);
		अगर (ret < 0)
			जाओ error;

		/*
		 * Add the VSP to the list or update the corresponding existing
		 * entry अगर the VSP has alपढ़ोy been added.
		 */
		क्रम (j = 0; j < vsps_count; ++j) अणु
			अगर (vsps[j].np == args.np)
				अवरोध;
		पूर्ण

		अगर (j < vsps_count)
			of_node_put(args.np);
		अन्यथा
			vsps[vsps_count++].np = args.np;

		vsps[j].crtcs_mask |= BIT(i);

		/*
		 * Store the VSP poपूर्णांकer and pipe index in the CRTC. If the
		 * second cell of the 'renesas,vsps' specifier isn't present,
		 * शेष to 0 to reमुख्य compatible with older DT bindings.
		 */
		rcdu->crtcs[i].vsp = &rcdu->vsps[j];
		rcdu->crtcs[i].vsp_pipe = cells >= 1 ? args.args[0] : 0;
	पूर्ण

	/*
	 * Then initialize all the VSPs from the node poपूर्णांकers and CRTCs biपंचांगask
	 * computed previously.
	 */
	क्रम (i = 0; i < vsps_count; ++i) अणु
		काष्ठा rcar_du_vsp *vsp = &rcdu->vsps[i];

		vsp->index = i;
		vsp->dev = rcdu;

		ret = rcar_du_vsp_init(vsp, vsps[i].np, vsps[i].crtcs_mask);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	क्रम (i = 0; i < ARRAY_SIZE(vsps); ++i)
		of_node_put(vsps[i].np);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_du_cmm_init(काष्ठा rcar_du_device *rcdu)
अणु
	स्थिर काष्ठा device_node *np = rcdu->dev->of_node;
	अचिन्हित पूर्णांक i;
	पूर्णांक cells;

	cells = of_property_count_u32_elems(np, "renesas,cmms");
	अगर (cells == -EINVAL)
		वापस 0;

	अगर (cells > rcdu->num_crtcs) अणु
		dev_err(rcdu->dev,
			"Invalid number of entries in 'renesas,cmms'\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cells; ++i) अणु
		काष्ठा platक्रमm_device *pdev;
		काष्ठा device_link *link;
		काष्ठा device_node *cmm;
		पूर्णांक ret;

		cmm = of_parse_phandle(np, "renesas,cmms", i);
		अगर (!cmm) अणु
			dev_err(rcdu->dev,
				"Failed to parse 'renesas,cmms' property\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!of_device_is_available(cmm)) अणु
			/* It's fine to have a phandle to a non-enabled CMM. */
			of_node_put(cmm);
			जारी;
		पूर्ण

		pdev = of_find_device_by_node(cmm);
		अगर (!pdev) अणु
			dev_err(rcdu->dev, "No device found for CMM%u\n", i);
			of_node_put(cmm);
			वापस -EINVAL;
		पूर्ण

		of_node_put(cmm);

		/*
		 * -ENODEV is used to report that the CMM config option is
		 * disabled: वापस 0 and let the DU जारी probing.
		 */
		ret = rcar_cmm_init(pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			वापस ret == -ENODEV ? 0 : ret;
		पूर्ण

		rcdu->cmms[i] = pdev;

		/*
		 * Enक्रमce suspend/resume ordering by making the CMM a provider
		 * of the DU: CMM is suspended after and resumed beक्रमe the DU.
		 */
		link = device_link_add(rcdu->dev, &pdev->dev, DL_FLAG_STATELESS);
		अगर (!link) अणु
			dev_err(rcdu->dev,
				"Failed to create device link to CMM%u\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcar_du_modeset_cleanup(काष्ठा drm_device *dev, व्योम *res)
अणु
	काष्ठा rcar_du_device *rcdu = to_rcar_du_device(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rcdu->cmms); ++i)
		platक्रमm_device_put(rcdu->cmms[i]);
पूर्ण

पूर्णांक rcar_du_modeset_init(काष्ठा rcar_du_device *rcdu)
अणु
	अटल स्थिर अचिन्हित पूर्णांक mmio_offsets[] = अणु
		DU0_REG_OFFSET, DU2_REG_OFFSET
	पूर्ण;

	काष्ठा drm_device *dev = &rcdu->ddev;
	काष्ठा drm_encoder *encoder;
	अचिन्हित पूर्णांक dpad0_sources;
	अचिन्हित पूर्णांक num_encoders;
	अचिन्हित पूर्णांक num_groups;
	अचिन्हित पूर्णांक swindex;
	अचिन्हित पूर्णांक hwindex;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = drmm_mode_config_init(dev);
	अगर (ret)
		वापस ret;

	ret = drmm_add_action(&rcdu->ddev, rcar_du_modeset_cleanup, शून्य);
	अगर (ret)
		वापस ret;

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.normalize_zpos = true;
	dev->mode_config.funcs = &rcar_du_mode_config_funcs;
	dev->mode_config.helper_निजी = &rcar_du_mode_config_helper;

	अगर (rcdu->info->gen < 3) अणु
		dev->mode_config.max_width = 4095;
		dev->mode_config.max_height = 2047;
	पूर्ण अन्यथा अणु
		/*
		 * The Gen3 DU uses the VSP1 क्रम memory access, and is limited
		 * to frame sizes of 8190x8190.
		 */
		dev->mode_config.max_width = 8190;
		dev->mode_config.max_height = 8190;
	पूर्ण

	rcdu->num_crtcs = hweight8(rcdu->info->channels_mask);

	ret = rcar_du_properties_init(rcdu);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Initialize vertical blanking पूर्णांकerrupts handling. Start with vblank
	 * disabled क्रम all CRTCs.
	 */
	ret = drm_vblank_init(dev, rcdu->num_crtcs);
	अगर (ret < 0)
		वापस ret;

	/* Initialize the groups. */
	num_groups = DIV_ROUND_UP(rcdu->num_crtcs, 2);

	क्रम (i = 0; i < num_groups; ++i) अणु
		काष्ठा rcar_du_group *rgrp = &rcdu->groups[i];

		mutex_init(&rgrp->lock);

		rgrp->dev = rcdu;
		rgrp->mmio_offset = mmio_offsets[i];
		rgrp->index = i;
		/* Extract the channel mask क्रम this group only. */
		rgrp->channels_mask = (rcdu->info->channels_mask >> (2 * i))
				   & GENMASK(1, 0);
		rgrp->num_crtcs = hweight8(rgrp->channels_mask);

		/*
		 * If we have more than one CRTCs in this group pre-associate
		 * the low-order planes with CRTC 0 and the high-order planes
		 * with CRTC 1 to minimize flicker occurring when the
		 * association is changed.
		 */
		rgrp->dptsr_planes = rgrp->num_crtcs > 1
				   ? (rcdu->info->gen >= 3 ? 0x04 : 0xf0)
				   : 0;

		अगर (!rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE)) अणु
			ret = rcar_du_planes_init(rgrp);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Initialize the compositors. */
	अगर (rcar_du_has(rcdu, RCAR_DU_FEATURE_VSP1_SOURCE)) अणु
		ret = rcar_du_vsps_init(rcdu);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Initialize the Color Management Modules. */
	ret = rcar_du_cmm_init(rcdu);
	अगर (ret)
		वापस ret;

	/* Create the CRTCs. */
	क्रम (swindex = 0, hwindex = 0; swindex < rcdu->num_crtcs; ++hwindex) अणु
		काष्ठा rcar_du_group *rgrp;

		/* Skip unpopulated DU channels. */
		अगर (!(rcdu->info->channels_mask & BIT(hwindex)))
			जारी;

		rgrp = &rcdu->groups[hwindex / 2];

		ret = rcar_du_crtc_create(rgrp, swindex++, hwindex);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Initialize the encoders. */
	ret = rcar_du_encoders_init(rcdu);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0) अणु
		dev_err(rcdu->dev, "error: no encoder could be initialized\n");
		वापस -EINVAL;
	पूर्ण

	num_encoders = ret;

	/*
	 * Set the possible CRTCs and possible clones. There's always at least
	 * one way क्रम all encoders to clone each other, set all bits in the
	 * possible clones field.
	 */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा rcar_du_encoder *renc = to_rcar_encoder(encoder);
		स्थिर काष्ठा rcar_du_output_routing *route =
			&rcdu->info->routes[renc->output];

		encoder->possible_crtcs = route->possible_crtcs;
		encoder->possible_clones = (1 << num_encoders) - 1;
	पूर्ण

	/* Create the ग_लिखोback connectors. */
	अगर (rcdu->info->gen >= 3) अणु
		क्रम (i = 0; i < rcdu->num_crtcs; ++i) अणु
			काष्ठा rcar_du_crtc *rcrtc = &rcdu->crtcs[i];

			ret = rcar_du_ग_लिखोback_init(rcdu, rcrtc);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Initialize the शेष DPAD0 source to the index of the first DU
	 * channel that can be connected to DPAD0. The exact value करोesn't
	 * matter as it should be overwritten by mode setting क्रम the RGB
	 * output, but it is nonetheless required to ensure a valid initial
	 * hardware configuration on Gen3 where DU0 can't always be connected to
	 * DPAD0.
	 */
	dpad0_sources = rcdu->info->routes[RCAR_DU_OUTPUT_DPAD0].possible_crtcs;
	rcdu->dpad0_source = ffs(dpad0_sources) - 1;

	drm_mode_config_reset(dev);

	drm_kms_helper_poll_init(dev);

	वापस 0;
पूर्ण
