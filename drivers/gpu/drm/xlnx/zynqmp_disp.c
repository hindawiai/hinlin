<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ZynqMP Display Controller Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>

#समावेश "zynqmp_disp.h"
#समावेश "zynqmp_disp_regs.h"
#समावेश "zynqmp_dp.h"
#समावेश "zynqmp_dpsub.h"

/*
 * Overview
 * --------
 *
 * The display controller part of ZynqMP DP subप्रणाली, made of the Audio/Video
 * Buffer Manager, the Video Rendering Pipeline (blender) and the Audio Mixer.
 *
 *              +------------------------------------------------------------+
 * +--------+   | +----------------+     +-----------+                       |
 * | DPDMA  | --->|                | --> |   Video   | Video +-------------+ |
 * | 4x vid |   | |                |     | Rendering | -+--> |             | |   +------+
 * | 2x aud |   | |  Audio/Video   | --> | Pipeline  |  |    | DisplayPort |---> | PHY0 |
 * +--------+   | | Buffer Manager |     +-----------+  |    |   Source    | |   +------+
 *              | |    and STC     |     +-----------+  |    | Controller  | |   +------+
 * Live Video --->|                | --> |   Audio   | Audio |             |---> | PHY1 |
 *              | |                |     |   Mixer   | --+-> |             | |   +------+
 * Live Audio --->|                | --> |           |  ||   +-------------+ |
 *              | +----------------+     +-----------+  ||                   |
 *              +---------------------------------------||-------------------+
 *                                                      vv
 *                                                Blended Video and
 *                                                Mixed Audio to PL
 *
 * Only non-live input from the DPDMA and output to the DisplayPort Source
 * Controller are currently supported. Interface with the programmable logic
 * क्रम live streams is not implemented.
 *
 * The display controller code creates planes क्रम the DPDMA video and graphics
 * layers, and a CRTC क्रम the Video Rendering Pipeline.
 */

#घोषणा ZYNQMP_DISP_AV_BUF_NUM_VID_GFX_BUFFERS		4
#घोषणा ZYNQMP_DISP_AV_BUF_NUM_BUFFERS			6

#घोषणा ZYNQMP_DISP_NUM_LAYERS				2
#घोषणा ZYNQMP_DISP_MAX_NUM_SUB_PLANES			3

/**
 * काष्ठा zynqmp_disp_क्रमmat - Display subप्रणाली क्रमmat inक्रमmation
 * @drm_fmt: DRM क्रमmat (4CC)
 * @buf_fmt: AV buffer क्रमmat
 * @bus_fmt: Media bus क्रमmats (live क्रमmats)
 * @swap: Flag to swap R & B क्रम RGB क्रमmats, and U & V क्रम YUV क्रमmats
 * @sf: Scaling factors क्रम color components
 */
काष्ठा zynqmp_disp_क्रमmat अणु
	u32 drm_fmt;
	u32 buf_fmt;
	u32 bus_fmt;
	bool swap;
	स्थिर u32 *sf;
पूर्ण;

/**
 * क्रमागत zynqmp_disp_id - Layer identअगरier
 * @ZYNQMP_DISP_LAYER_VID: Video layer
 * @ZYNQMP_DISP_LAYER_GFX: Graphics layer
 */
क्रमागत zynqmp_disp_layer_id अणु
	ZYNQMP_DISP_LAYER_VID,
	ZYNQMP_DISP_LAYER_GFX
पूर्ण;

/**
 * क्रमागत zynqmp_disp_layer_mode - Layer mode
 * @ZYNQMP_DISP_LAYER_NONLIVE: non-live (memory) mode
 * @ZYNQMP_DISP_LAYER_LIVE: live (stream) mode
 */
क्रमागत zynqmp_disp_layer_mode अणु
	ZYNQMP_DISP_LAYER_NONLIVE,
	ZYNQMP_DISP_LAYER_LIVE
पूर्ण;

/**
 * काष्ठा zynqmp_disp_layer_dma - DMA channel क्रम one data plane of a layer
 * @chan: DMA channel
 * @xt: Interleaved DMA descriptor ढाँचा
 * @sgl: Data chunk क्रम dma_पूर्णांकerleaved_ढाँचा
 */
काष्ठा zynqmp_disp_layer_dma अणु
	काष्ठा dma_chan *chan;
	काष्ठा dma_पूर्णांकerleaved_ढाँचा xt;
	काष्ठा data_chunk sgl;
पूर्ण;

/**
 * काष्ठा zynqmp_disp_layer_info - Static layer inक्रमmation
 * @क्रमmats: Array of supported क्रमmats
 * @num_क्रमmats: Number of क्रमmats in @क्रमmats array
 * @num_channels: Number of DMA channels
 */
काष्ठा zynqmp_disp_layer_info अणु
	स्थिर काष्ठा zynqmp_disp_क्रमmat *क्रमmats;
	अचिन्हित पूर्णांक num_क्रमmats;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

/**
 * काष्ठा zynqmp_disp_layer - Display layer (DRM plane)
 * @plane: DRM plane
 * @id: Layer ID
 * @disp: Back poपूर्णांकer to काष्ठा zynqmp_disp
 * @info: Static layer inक्रमmation
 * @dmas: DMA channels
 * @disp_fmt: Current क्रमmat inक्रमmation
 * @drm_fmt: Current DRM क्रमmat inक्रमmation
 * @mode: Current operation mode
 */
काष्ठा zynqmp_disp_layer अणु
	काष्ठा drm_plane plane;
	क्रमागत zynqmp_disp_layer_id id;
	काष्ठा zynqmp_disp *disp;
	स्थिर काष्ठा zynqmp_disp_layer_info *info;

	काष्ठा zynqmp_disp_layer_dma dmas[ZYNQMP_DISP_MAX_NUM_SUB_PLANES];

	स्थिर काष्ठा zynqmp_disp_क्रमmat *disp_fmt;
	स्थिर काष्ठा drm_क्रमmat_info *drm_fmt;
	क्रमागत zynqmp_disp_layer_mode mode;
पूर्ण;

/**
 * काष्ठा zynqmp_disp_blend - Blender
 * @base: Registers I/O base address
 */
काष्ठा zynqmp_disp_blend अणु
	व्योम __iomem *base;
पूर्ण;

/**
 * काष्ठा zynqmp_disp_avbuf - Audio/video buffer manager
 * @base: Registers I/O base address
 */
काष्ठा zynqmp_disp_avbuf अणु
	व्योम __iomem *base;
पूर्ण;

/**
 * काष्ठा zynqmp_disp_audio - Audio mixer
 * @base: Registers I/O base address
 * @clk: Audio घड़ी
 * @clk_from_ps: True of the audio घड़ी comes from PS, false from PL
 */
काष्ठा zynqmp_disp_audio अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	bool clk_from_ps;
पूर्ण;

/**
 * काष्ठा zynqmp_disp - Display controller
 * @dev: Device काष्ठाure
 * @drm: DRM core
 * @dpsub: Display subप्रणाली
 * @crtc: DRM CRTC
 * @blend: Blender (video rendering pipeline)
 * @avbuf: Audio/video buffer manager
 * @audio: Audio mixer
 * @layers: Layers (planes)
 * @event: Pending vblank event request
 * @pclk: Pixel घड़ी
 * @pclk_from_ps: True of the video घड़ी comes from PS, false from PL
 */
काष्ठा zynqmp_disp अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm;
	काष्ठा zynqmp_dpsub *dpsub;

	काष्ठा drm_crtc crtc;

	काष्ठा zynqmp_disp_blend blend;
	काष्ठा zynqmp_disp_avbuf avbuf;
	काष्ठा zynqmp_disp_audio audio;

	काष्ठा zynqmp_disp_layer layers[ZYNQMP_DISP_NUM_LAYERS];

	काष्ठा drm_pending_vblank_event *event;

	काष्ठा clk *pclk;
	bool pclk_from_ps;
पूर्ण;

/* -----------------------------------------------------------------------------
 * Audio/Video Buffer Manager
 */

अटल स्थिर u32 scaling_factors_444[] = अणु
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
	ZYNQMP_DISP_AV_BUF_4BIT_SF,
पूर्ण;

अटल स्थिर u32 scaling_factors_555[] = अणु
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
पूर्ण;

अटल स्थिर u32 scaling_factors_565[] = अणु
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
	ZYNQMP_DISP_AV_BUF_6BIT_SF,
	ZYNQMP_DISP_AV_BUF_5BIT_SF,
पूर्ण;

अटल स्थिर u32 scaling_factors_888[] = अणु
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
	ZYNQMP_DISP_AV_BUF_8BIT_SF,
पूर्ण;

अटल स्थिर u32 scaling_factors_101010[] = अणु
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
	ZYNQMP_DISP_AV_BUF_10BIT_SF,
पूर्ण;

/* List of video layer क्रमmats */
अटल स्थिर काष्ठा zynqmp_disp_क्रमmat avbuf_vid_fmts[] = अणु
	अणु
		.drm_fmt	= DRM_FORMAT_VYUY,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_VYUY,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_UYVY,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_VYUY,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YUYV,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YUYV,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YVYU,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YUYV,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YUV422,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YVU422,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YUV444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV24,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YVU444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV24,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_NV16,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16CI,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_NV61,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16CI,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGR888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGB888,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGB888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGB888,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_XBGR8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGBA8880,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_XRGB8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGBA8880,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_XBGR2101010,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGB888_10,
		.swap		= false,
		.sf		= scaling_factors_101010,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_XRGB2101010,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_RGB888_10,
		.swap		= true,
		.sf		= scaling_factors_101010,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YUV420,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16_420,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_YVU420,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16_420,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_NV12,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16CI_420,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_NV21,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_VID_YV16CI_420,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण,
पूर्ण;

/* List of graphics layer क्रमmats */
अटल स्थिर काष्ठा zynqmp_disp_क्रमmat avbuf_gfx_fmts[] = अणु
	अणु
		.drm_fmt	= DRM_FORMAT_ABGR8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA8888,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_ARGB8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA8888,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGBA8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_ABGR8888,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGRA8888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_ABGR8888,
		.swap		= true,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGR888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGB888,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGB888,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_BGR888,
		.swap		= false,
		.sf		= scaling_factors_888,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGBA5551,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA5551,
		.swap		= false,
		.sf		= scaling_factors_555,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGRA5551,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA5551,
		.swap		= true,
		.sf		= scaling_factors_555,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGBA4444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA4444,
		.swap		= false,
		.sf		= scaling_factors_444,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGRA4444,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGBA4444,
		.swap		= true,
		.sf		= scaling_factors_444,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_RGB565,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGB565,
		.swap		= false,
		.sf		= scaling_factors_565,
	पूर्ण, अणु
		.drm_fmt	= DRM_FORMAT_BGR565,
		.buf_fmt	= ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_RGB565,
		.swap		= true,
		.sf		= scaling_factors_565,
	पूर्ण,
पूर्ण;

अटल u32 zynqmp_disp_avbuf_पढ़ो(काष्ठा zynqmp_disp_avbuf *avbuf, पूर्णांक reg)
अणु
	वापस पढ़ोl(avbuf->base + reg);
पूर्ण

अटल व्योम zynqmp_disp_avbuf_ग_लिखो(काष्ठा zynqmp_disp_avbuf *avbuf,
				    पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, avbuf->base + reg);
पूर्ण

/**
 * zynqmp_disp_avbuf_set_क्रमmat - Set the input क्रमmat क्रम a layer
 * @avbuf: Audio/video buffer manager
 * @layer: The layer ID
 * @fmt: The क्रमmat inक्रमmation
 *
 * Set the video buffer manager क्रमmat क्रम @layer to @fmt.
 */
अटल व्योम zynqmp_disp_avbuf_set_क्रमmat(काष्ठा zynqmp_disp_avbuf *avbuf,
					 क्रमागत zynqmp_disp_layer_id layer,
					 स्थिर काष्ठा zynqmp_disp_क्रमmat *fmt)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	val = zynqmp_disp_avbuf_पढ़ो(avbuf, ZYNQMP_DISP_AV_BUF_FMT);
	val &= layer == ZYNQMP_DISP_LAYER_VID
	    ? ~ZYNQMP_DISP_AV_BUF_FMT_NL_VID_MASK
	    : ~ZYNQMP_DISP_AV_BUF_FMT_NL_GFX_MASK;
	val |= fmt->buf_fmt;
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_FMT, val);

	क्रम (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_SF; i++) अणु
		अचिन्हित पूर्णांक reg = layer == ZYNQMP_DISP_LAYER_VID
				 ? ZYNQMP_DISP_AV_BUF_VID_COMP_SF(i)
				 : ZYNQMP_DISP_AV_BUF_GFX_COMP_SF(i);

		zynqmp_disp_avbuf_ग_लिखो(avbuf, reg, fmt->sf[i]);
	पूर्ण
पूर्ण

/**
 * zynqmp_disp_avbuf_set_घड़ीs_sources - Set the घड़ीs sources
 * @avbuf: Audio/video buffer manager
 * @video_from_ps: True अगर the video घड़ी originates from the PS
 * @audio_from_ps: True अगर the audio घड़ी originates from the PS
 * @timings_पूर्णांकernal: True अगर video timings are generated पूर्णांकernally
 *
 * Set the source क्रम the video and audio घड़ीs, as well as क्रम the video
 * timings. Clocks can originate from the PS or PL, and timings can be
 * generated पूर्णांकernally or बाह्यally.
 */
अटल व्योम
zynqmp_disp_avbuf_set_घड़ीs_sources(काष्ठा zynqmp_disp_avbuf *avbuf,
				     bool video_from_ps, bool audio_from_ps,
				     bool timings_पूर्णांकernal)
अणु
	u32 val = 0;

	अगर (video_from_ps)
		val |= ZYNQMP_DISP_AV_BUF_CLK_SRC_VID_FROM_PS;
	अगर (audio_from_ps)
		val |= ZYNQMP_DISP_AV_BUF_CLK_SRC_AUD_FROM_PS;
	अगर (timings_पूर्णांकernal)
		val |= ZYNQMP_DISP_AV_BUF_CLK_SRC_VID_INTERNAL_TIMING;

	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_CLK_SRC, val);
पूर्ण

/**
 * zynqmp_disp_avbuf_enable_channels - Enable buffer channels
 * @avbuf: Audio/video buffer manager
 *
 * Enable all (video and audio) buffer channels.
 */
अटल व्योम zynqmp_disp_avbuf_enable_channels(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	val = ZYNQMP_DISP_AV_BUF_CHBUF_EN |
	      (ZYNQMP_DISP_AV_BUF_CHBUF_BURST_LEN_MAX <<
	       ZYNQMP_DISP_AV_BUF_CHBUF_BURST_LEN_SHIFT);

	क्रम (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_VID_GFX_BUFFERS; i++)
		zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					val);

	val = ZYNQMP_DISP_AV_BUF_CHBUF_EN |
	      (ZYNQMP_DISP_AV_BUF_CHBUF_BURST_LEN_AUD_MAX <<
	       ZYNQMP_DISP_AV_BUF_CHBUF_BURST_LEN_SHIFT);

	क्रम (; i < ZYNQMP_DISP_AV_BUF_NUM_BUFFERS; i++)
		zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					val);
पूर्ण

/**
 * zynqmp_disp_avbuf_disable_channels - Disable buffer channels
 * @avbuf: Audio/video buffer manager
 *
 * Disable all (video and audio) buffer channels.
 */
अटल व्योम zynqmp_disp_avbuf_disable_channels(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ZYNQMP_DISP_AV_BUF_NUM_BUFFERS; i++)
		zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_CHBUF(i),
					ZYNQMP_DISP_AV_BUF_CHBUF_FLUSH);
पूर्ण

/**
 * zynqmp_disp_avbuf_enable_audio - Enable audio
 * @avbuf: Audio/video buffer manager
 *
 * Enable all audio buffers with a non-live (memory) source.
 */
अटल व्योम zynqmp_disp_avbuf_enable_audio(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	u32 val;

	val = zynqmp_disp_avbuf_पढ़ो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT);
	val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MASK;
	val |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MEM;
	val |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD2_EN;
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT, val);
पूर्ण

/**
 * zynqmp_disp_avbuf_disable_audio - Disable audio
 * @avbuf: Audio/video buffer manager
 *
 * Disable all audio buffers.
 */
अटल व्योम zynqmp_disp_avbuf_disable_audio(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	u32 val;

	val = zynqmp_disp_avbuf_पढ़ो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT);
	val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_MASK;
	val |= ZYNQMP_DISP_AV_BUF_OUTPUT_AUD1_DISABLE;
	val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_AUD2_EN;
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT, val);
पूर्ण

/**
 * zynqmp_disp_avbuf_enable_video - Enable a video layer
 * @avbuf: Audio/video buffer manager
 * @layer: The layer ID
 * @mode: Operating mode of layer
 *
 * Enable the video/graphics buffer क्रम @layer.
 */
अटल व्योम zynqmp_disp_avbuf_enable_video(काष्ठा zynqmp_disp_avbuf *avbuf,
					   क्रमागत zynqmp_disp_layer_id layer,
					   क्रमागत zynqmp_disp_layer_mode mode)
अणु
	u32 val;

	val = zynqmp_disp_avbuf_पढ़ो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT);
	अगर (layer == ZYNQMP_DISP_LAYER_VID) अणु
		val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MASK;
		अगर (mode == ZYNQMP_DISP_LAYER_NONLIVE)
			val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MEM;
		अन्यथा
			val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_LIVE;
	पूर्ण अन्यथा अणु
		val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MASK;
		val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MEM;
		अगर (mode == ZYNQMP_DISP_LAYER_NONLIVE)
			val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MEM;
		अन्यथा
			val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_LIVE;
	पूर्ण
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT, val);
पूर्ण

/**
 * zynqmp_disp_avbuf_disable_video - Disable a video layer
 * @avbuf: Audio/video buffer manager
 * @layer: The layer ID
 *
 * Disable the video/graphics buffer क्रम @layer.
 */
अटल व्योम zynqmp_disp_avbuf_disable_video(काष्ठा zynqmp_disp_avbuf *avbuf,
					    क्रमागत zynqmp_disp_layer_id layer)
अणु
	u32 val;

	val = zynqmp_disp_avbuf_पढ़ो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT);
	अगर (layer == ZYNQMP_DISP_LAYER_VID) अणु
		val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_MASK;
		val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID1_NONE;
	पूर्ण अन्यथा अणु
		val &= ~ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_MASK;
		val |= ZYNQMP_DISP_AV_BUF_OUTPUT_VID2_DISABLE;
	पूर्ण
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_OUTPUT, val);
पूर्ण

/**
 * zynqmp_disp_avbuf_enable - Enable the video pipe
 * @avbuf: Audio/video buffer manager
 *
 * De-निश्चित the video pipe reset.
 */
अटल व्योम zynqmp_disp_avbuf_enable(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_SRST_REG, 0);
पूर्ण

/**
 * zynqmp_disp_avbuf_disable - Disable the video pipe
 * @avbuf: Audio/video buffer manager
 *
 * Assert the video pipe reset.
 */
अटल व्योम zynqmp_disp_avbuf_disable(काष्ठा zynqmp_disp_avbuf *avbuf)
अणु
	zynqmp_disp_avbuf_ग_लिखो(avbuf, ZYNQMP_DISP_AV_BUF_SRST_REG,
				ZYNQMP_DISP_AV_BUF_SRST_REG_VID_RST);
पूर्ण

/* -----------------------------------------------------------------------------
 * Blender (Video Pipeline)
 */

अटल व्योम zynqmp_disp_blend_ग_लिखो(काष्ठा zynqmp_disp_blend *blend,
				    पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, blend->base + reg);
पूर्ण

/*
 * Colorspace conversion matrices.
 *
 * Hardcode RGB <-> YUV conversion to full-range SDTV क्रम now.
 */
अटल स्थिर u16 csc_zero_matrix[] = अणु
	0x0,    0x0,    0x0,
	0x0,    0x0,    0x0,
	0x0,    0x0,    0x0
पूर्ण;

अटल स्थिर u16 csc_identity_matrix[] = अणु
	0x1000, 0x0,    0x0,
	0x0,    0x1000, 0x0,
	0x0,    0x0,    0x1000
पूर्ण;

अटल स्थिर u32 csc_zero_offsets[] = अणु
	0, 0, 0
पूर्ण;

अटल स्थिर u16 csc_rgb_to_sdtv_matrix[] = अणु
	0x4c9,  0x864,  0x1d3,
	0x7d4d, 0x7ab3, 0x800,
	0x800,  0x794d, 0x7eb3
पूर्ण;

अटल स्थिर u32 csc_rgb_to_sdtv_offsets[] = अणु
	0x0, 0x8000000, 0x8000000
पूर्ण;

अटल स्थिर u16 csc_sdtv_to_rgb_matrix[] = अणु
	0x1000, 0x166f, 0x0,
	0x1000, 0x7483, 0x7a7f,
	0x1000, 0x0,    0x1c5a
पूर्ण;

अटल स्थिर u32 csc_sdtv_to_rgb_offsets[] = अणु
	0x0, 0x1800, 0x1800
पूर्ण;

/**
 * zynqmp_disp_blend_set_output_क्रमmat - Set the output क्रमmat of the blender
 * @blend: Blender object
 * @क्रमmat: Output क्रमmat
 *
 * Set the output क्रमmat of the blender to @क्रमmat.
 */
अटल व्योम zynqmp_disp_blend_set_output_क्रमmat(काष्ठा zynqmp_disp_blend *blend,
						क्रमागत zynqmp_dpsub_क्रमmat क्रमmat)
अणु
	अटल स्थिर अचिन्हित पूर्णांक blend_output_fmts[] = अणु
		[ZYNQMP_DPSUB_FORMAT_RGB] = ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_RGB,
		[ZYNQMP_DPSUB_FORMAT_YCRCB444] = ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_YCBCR444,
		[ZYNQMP_DPSUB_FORMAT_YCRCB422] = ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_YCBCR422
					       | ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_EN_DOWNSAMPLE,
		[ZYNQMP_DPSUB_FORMAT_YONLY] = ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_YONLY,
	पूर्ण;

	u32 fmt = blend_output_fmts[क्रमmat];
	स्थिर u16 *coeffs;
	स्थिर u32 *offsets;
	अचिन्हित पूर्णांक i;

	zynqmp_disp_blend_ग_लिखो(blend, ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT, fmt);
	अगर (fmt == ZYNQMP_DISP_V_BLEND_OUTPUT_VID_FMT_RGB) अणु
		coeffs = csc_identity_matrix;
		offsets = csc_zero_offsets;
	पूर्ण अन्यथा अणु
		coeffs = csc_rgb_to_sdtv_matrix;
		offsets = csc_rgb_to_sdtv_offsets;
	पूर्ण

	क्रम (i = 0; i < ZYNQMP_DISP_V_BLEND_NUM_COEFF; i++)
		zynqmp_disp_blend_ग_लिखो(blend,
					ZYNQMP_DISP_V_BLEND_RGB2YCBCR_COEFF(i),
					coeffs[i]);

	क्रम (i = 0; i < ZYNQMP_DISP_V_BLEND_NUM_OFFSET; i++)
		zynqmp_disp_blend_ग_लिखो(blend,
					ZYNQMP_DISP_V_BLEND_OUTCSC_OFFSET(i),
					offsets[i]);
पूर्ण

/**
 * zynqmp_disp_blend_set_bg_color - Set the background color
 * @blend: Blender object
 * @rcr: Red/Cr color component
 * @gy: Green/Y color component
 * @bcb: Blue/Cb color component
 *
 * Set the background color to (@rcr, @gy, @bcb), corresponding to the R, G and
 * B or Cr, Y and Cb components respectively depending on the selected output
 * क्रमmat.
 */
अटल व्योम zynqmp_disp_blend_set_bg_color(काष्ठा zynqmp_disp_blend *blend,
					   u32 rcr, u32 gy, u32 bcb)
अणु
	zynqmp_disp_blend_ग_लिखो(blend, ZYNQMP_DISP_V_BLEND_BG_CLR_0, rcr);
	zynqmp_disp_blend_ग_लिखो(blend, ZYNQMP_DISP_V_BLEND_BG_CLR_1, gy);
	zynqmp_disp_blend_ग_लिखो(blend, ZYNQMP_DISP_V_BLEND_BG_CLR_2, bcb);
पूर्ण

/**
 * zynqmp_disp_blend_set_global_alpha - Configure global alpha blending
 * @blend: Blender object
 * @enable: True to enable global alpha blending
 * @alpha: Global alpha value (ignored अगर @enabled is false)
 */
अटल व्योम zynqmp_disp_blend_set_global_alpha(काष्ठा zynqmp_disp_blend *blend,
					       bool enable, u32 alpha)
अणु
	zynqmp_disp_blend_ग_लिखो(blend, ZYNQMP_DISP_V_BLEND_SET_GLOBAL_ALPHA,
				ZYNQMP_DISP_V_BLEND_SET_GLOBAL_ALPHA_VALUE(alpha) |
				(enable ? ZYNQMP_DISP_V_BLEND_SET_GLOBAL_ALPHA_EN : 0));
पूर्ण

/**
 * zynqmp_disp_blend_layer_set_csc - Configure colorspace conversion क्रम layer
 * @blend: Blender object
 * @layer: The layer
 * @coeffs: Colorspace conversion matrix
 * @offsets: Colorspace conversion offsets
 *
 * Configure the input colorspace conversion matrix and offsets क्रम the @layer.
 * Columns of the matrix are स्वतःmatically swapped based on the input क्रमmat to
 * handle RGB and YCrCb components permutations.
 */
अटल व्योम zynqmp_disp_blend_layer_set_csc(काष्ठा zynqmp_disp_blend *blend,
					    काष्ठा zynqmp_disp_layer *layer,
					    स्थिर u16 *coeffs,
					    स्थिर u32 *offsets)
अणु
	अचिन्हित पूर्णांक swap[3] = अणु 0, 1, 2 पूर्ण;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक i;

	अगर (layer->disp_fmt->swap) अणु
		अगर (layer->drm_fmt->is_yuv) अणु
			/* Swap U and V. */
			swap[1] = 2;
			swap[2] = 1;
		पूर्ण अन्यथा अणु
			/* Swap R and B. */
			swap[0] = 2;
			swap[2] = 0;
		पूर्ण
	पूर्ण

	अगर (layer->id == ZYNQMP_DISP_LAYER_VID)
		reg = ZYNQMP_DISP_V_BLEND_IN1CSC_COEFF(0);
	अन्यथा
		reg = ZYNQMP_DISP_V_BLEND_IN2CSC_COEFF(0);

	क्रम (i = 0; i < ZYNQMP_DISP_V_BLEND_NUM_COEFF; i += 3, reg += 12) अणु
		zynqmp_disp_blend_ग_लिखो(blend, reg + 0, coeffs[i + swap[0]]);
		zynqmp_disp_blend_ग_लिखो(blend, reg + 4, coeffs[i + swap[1]]);
		zynqmp_disp_blend_ग_लिखो(blend, reg + 8, coeffs[i + swap[2]]);
	पूर्ण

	अगर (layer->id == ZYNQMP_DISP_LAYER_VID)
		reg = ZYNQMP_DISP_V_BLEND_IN1CSC_OFFSET(0);
	अन्यथा
		reg = ZYNQMP_DISP_V_BLEND_IN2CSC_OFFSET(0);

	क्रम (i = 0; i < ZYNQMP_DISP_V_BLEND_NUM_OFFSET; i++)
		zynqmp_disp_blend_ग_लिखो(blend, reg + i * 4, offsets[i]);
पूर्ण

/**
 * zynqmp_disp_blend_layer_enable - Enable a layer
 * @blend: Blender object
 * @layer: The layer
 */
अटल व्योम zynqmp_disp_blend_layer_enable(काष्ठा zynqmp_disp_blend *blend,
					   काष्ठा zynqmp_disp_layer *layer)
अणु
	स्थिर u16 *coeffs;
	स्थिर u32 *offsets;
	u32 val;

	val = (layer->drm_fmt->is_yuv ?
	       0 : ZYNQMP_DISP_V_BLEND_LAYER_CONTROL_RGB) |
	      (layer->drm_fmt->hsub > 1 ?
	       ZYNQMP_DISP_V_BLEND_LAYER_CONTROL_EN_US : 0);

	zynqmp_disp_blend_ग_लिखो(blend,
				ZYNQMP_DISP_V_BLEND_LAYER_CONTROL(layer->id),
				val);

	अगर (layer->drm_fmt->is_yuv) अणु
		coeffs = csc_sdtv_to_rgb_matrix;
		offsets = csc_sdtv_to_rgb_offsets;
	पूर्ण अन्यथा अणु
		coeffs = csc_identity_matrix;
		offsets = csc_zero_offsets;
	पूर्ण

	zynqmp_disp_blend_layer_set_csc(blend, layer, coeffs, offsets);
पूर्ण

/**
 * zynqmp_disp_blend_layer_disable - Disable a layer
 * @blend: Blender object
 * @layer: The layer
 */
अटल व्योम zynqmp_disp_blend_layer_disable(काष्ठा zynqmp_disp_blend *blend,
					    काष्ठा zynqmp_disp_layer *layer)
अणु
	zynqmp_disp_blend_ग_लिखो(blend,
				ZYNQMP_DISP_V_BLEND_LAYER_CONTROL(layer->id),
				0);

	zynqmp_disp_blend_layer_set_csc(blend, layer, csc_zero_matrix,
					csc_zero_offsets);
पूर्ण

/* -----------------------------------------------------------------------------
 * Audio Mixer
 */

अटल व्योम zynqmp_disp_audio_ग_लिखो(काष्ठा zynqmp_disp_audio *audio,
				  पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, audio->base + reg);
पूर्ण

/**
 * zynqmp_disp_audio_enable - Enable the audio mixer
 * @audio: Audio mixer
 *
 * Enable the audio mixer by de-निश्चितing the soft reset. The audio state is set to
 * शेष values by the reset, set the शेष mixer volume explicitly.
 */
अटल व्योम zynqmp_disp_audio_enable(काष्ठा zynqmp_disp_audio *audio)
अणु
	/* Clear the audio soft reset रेजिस्टर as it's an non-reset flop. */
	zynqmp_disp_audio_ग_लिखो(audio, ZYNQMP_DISP_AUD_SOFT_RESET, 0);
	zynqmp_disp_audio_ग_लिखो(audio, ZYNQMP_DISP_AUD_MIXER_VOLUME,
				ZYNQMP_DISP_AUD_MIXER_VOLUME_NO_SCALE);
पूर्ण

/**
 * zynqmp_disp_audio_disable - Disable the audio mixer
 * @audio: Audio mixer
 *
 * Disable the audio mixer by निश्चितing its soft reset.
 */
अटल व्योम zynqmp_disp_audio_disable(काष्ठा zynqmp_disp_audio *audio)
अणु
	zynqmp_disp_audio_ग_लिखो(audio, ZYNQMP_DISP_AUD_SOFT_RESET,
				ZYNQMP_DISP_AUD_SOFT_RESET_AUD_SRST);
पूर्ण

अटल व्योम zynqmp_disp_audio_init(काष्ठा device *dev,
				   काष्ठा zynqmp_disp_audio *audio)
अणु
	/* Try the live PL audio घड़ी. */
	audio->clk = devm_clk_get(dev, "dp_live_audio_aclk");
	अगर (!IS_ERR(audio->clk)) अणु
		audio->clk_from_ps = false;
		वापस;
	पूर्ण

	/* If the live PL audio घड़ी is not valid, fall back to PS घड़ी. */
	audio->clk = devm_clk_get(dev, "dp_aud_clk");
	अगर (!IS_ERR(audio->clk)) अणु
		audio->clk_from_ps = true;
		वापस;
	पूर्ण

	dev_err(dev, "audio disabled due to missing clock\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * ZynqMP Display बाह्यal functions क्रम zynqmp_dp
 */

/**
 * zynqmp_disp_handle_vblank - Handle the vblank event
 * @disp: Display controller
 *
 * This function handles the vblank पूर्णांकerrupt, and sends an event to
 * CRTC object. This will be called by the DP vblank पूर्णांकerrupt handler.
 */
व्योम zynqmp_disp_handle_vblank(काष्ठा zynqmp_disp *disp)
अणु
	काष्ठा drm_crtc *crtc = &disp->crtc;

	drm_crtc_handle_vblank(crtc);
पूर्ण

/**
 * zynqmp_disp_audio_enabled - If the audio is enabled
 * @disp: Display controller
 *
 * Return अगर the audio is enabled depending on the audio घड़ी.
 *
 * Return: true अगर audio is enabled, or false.
 */
bool zynqmp_disp_audio_enabled(काष्ठा zynqmp_disp *disp)
अणु
	वापस !!disp->audio.clk;
पूर्ण

/**
 * zynqmp_disp_get_audio_clk_rate - Get the current audio घड़ी rate
 * @disp: Display controller
 *
 * Return: the current audio घड़ी rate.
 */
अचिन्हित पूर्णांक zynqmp_disp_get_audio_clk_rate(काष्ठा zynqmp_disp *disp)
अणु
	अगर (zynqmp_disp_audio_enabled(disp))
		वापस 0;
	वापस clk_get_rate(disp->audio.clk);
पूर्ण

/**
 * zynqmp_disp_get_crtc_mask - Return the CRTC bit mask
 * @disp: Display controller
 *
 * Return: the crtc mask of the zyqnmp_disp CRTC.
 */
uपूर्णांक32_t zynqmp_disp_get_crtc_mask(काष्ठा zynqmp_disp *disp)
अणु
	वापस drm_crtc_mask(&disp->crtc);
पूर्ण

/* -----------------------------------------------------------------------------
 * ZynqMP Display Layer & DRM Plane
 */

/**
 * zynqmp_disp_layer_find_क्रमmat - Find क्रमmat inक्रमmation क्रम a DRM क्रमmat
 * @layer: The layer
 * @drm_fmt: DRM क्रमmat to search
 *
 * Search display subप्रणाली क्रमmat inक्रमmation corresponding to the given DRM
 * क्रमmat @drm_fmt क्रम the @layer, and वापस a poपूर्णांकer to the क्रमmat
 * descriptor.
 *
 * Return: A poपूर्णांकer to the क्रमmat descriptor अगर found, शून्य otherwise
 */
अटल स्थिर काष्ठा zynqmp_disp_क्रमmat *
zynqmp_disp_layer_find_क्रमmat(काष्ठा zynqmp_disp_layer *layer,
			      u32 drm_fmt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < layer->info->num_क्रमmats; i++) अणु
		अगर (layer->info->क्रमmats[i].drm_fmt == drm_fmt)
			वापस &layer->info->क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * zynqmp_disp_layer_enable - Enable a layer
 * @layer: The layer
 *
 * Enable the @layer in the audio/video buffer manager and the blender. DMA
 * channels are started separately by zynqmp_disp_layer_update().
 */
अटल व्योम zynqmp_disp_layer_enable(काष्ठा zynqmp_disp_layer *layer)
अणु
	zynqmp_disp_avbuf_enable_video(&layer->disp->avbuf, layer->id,
				       ZYNQMP_DISP_LAYER_NONLIVE);
	zynqmp_disp_blend_layer_enable(&layer->disp->blend, layer);

	layer->mode = ZYNQMP_DISP_LAYER_NONLIVE;
पूर्ण

/**
 * zynqmp_disp_layer_disable - Disable the layer
 * @layer: The layer
 *
 * Disable the layer by stopping its DMA channels and disabling it in the
 * audio/video buffer manager and the blender.
 */
अटल व्योम zynqmp_disp_layer_disable(काष्ठा zynqmp_disp_layer *layer)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < layer->drm_fmt->num_planes; i++)
		dmaengine_terminate_sync(layer->dmas[i].chan);

	zynqmp_disp_avbuf_disable_video(&layer->disp->avbuf, layer->id);
	zynqmp_disp_blend_layer_disable(&layer->disp->blend, layer);
पूर्ण

/**
 * zynqmp_disp_layer_set_क्रमmat - Set the layer क्रमmat
 * @layer: The layer
 * @state: The plane state
 *
 * Set the क्रमmat क्रम @layer based on @state->fb->क्रमmat. The layer must be
 * disabled.
 */
अटल व्योम zynqmp_disp_layer_set_क्रमmat(काष्ठा zynqmp_disp_layer *layer,
					 काष्ठा drm_plane_state *state)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = state->fb->क्रमmat;
	अचिन्हित पूर्णांक i;

	layer->disp_fmt = zynqmp_disp_layer_find_क्रमmat(layer, info->क्रमmat);
	layer->drm_fmt = info;

	zynqmp_disp_avbuf_set_क्रमmat(&layer->disp->avbuf, layer->id,
				     layer->disp_fmt);

	/*
	 * Set slave_id क्रम each DMA channel to indicate they're part of a
	 * video group.
	 */
	क्रम (i = 0; i < info->num_planes; i++) अणु
		काष्ठा zynqmp_disp_layer_dma *dma = &layer->dmas[i];
		काष्ठा dma_slave_config config = अणु
			.direction = DMA_MEM_TO_DEV,
			.slave_id = 1,
		पूर्ण;

		dmaengine_slave_config(dma->chan, &config);
	पूर्ण
पूर्ण

/**
 * zynqmp_disp_layer_update - Update the layer framebuffer
 * @layer: The layer
 * @state: The plane state
 *
 * Update the framebuffer क्रम the layer by issuing a new DMA engine transaction
 * क्रम the new framebuffer.
 *
 * Return: 0 on success, or the DMA descriptor failure error otherwise
 */
अटल पूर्णांक zynqmp_disp_layer_update(काष्ठा zynqmp_disp_layer *layer,
				    काष्ठा drm_plane_state *state)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = layer->drm_fmt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < layer->drm_fmt->num_planes; i++) अणु
		अचिन्हित पूर्णांक width = state->crtc_w / (i ? info->hsub : 1);
		अचिन्हित पूर्णांक height = state->crtc_h / (i ? info->vsub : 1);
		काष्ठा zynqmp_disp_layer_dma *dma = &layer->dmas[i];
		काष्ठा dma_async_tx_descriptor *desc;
		dma_addr_t paddr;

		paddr = drm_fb_cma_get_gem_addr(state->fb, state, i);

		dma->xt.numf = height;
		dma->sgl.size = width * info->cpp[i];
		dma->sgl.icg = state->fb->pitches[i] - dma->sgl.size;
		dma->xt.src_start = paddr;
		dma->xt.frame_size = 1;
		dma->xt.dir = DMA_MEM_TO_DEV;
		dma->xt.src_sgl = true;
		dma->xt.dst_sgl = false;

		desc = dmaengine_prep_पूर्णांकerleaved_dma(dma->chan, &dma->xt,
						      DMA_CTRL_ACK |
						      DMA_PREP_REPEAT |
						      DMA_PREP_LOAD_EOT);
		अगर (!desc) अणु
			dev_err(layer->disp->dev,
				"failed to prepare DMA descriptor\n");
			वापस -ENOMEM;
		पूर्ण

		dmaengine_submit(desc);
		dma_async_issue_pending(dma->chan);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा zynqmp_disp_layer *plane_to_layer(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा zynqmp_disp_layer, plane);
पूर्ण

अटल पूर्णांक
zynqmp_disp_plane_atomic_check(काष्ठा drm_plane *plane,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!new_plane_state->crtc)
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state, new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	वापस drm_atomic_helper_check_plane_state(new_plane_state,
						   crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, false);
पूर्ण

अटल व्योम
zynqmp_disp_plane_atomic_disable(काष्ठा drm_plane *plane,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा zynqmp_disp_layer *layer = plane_to_layer(plane);

	अगर (!old_state->fb)
		वापस;

	zynqmp_disp_layer_disable(layer);
पूर्ण

अटल व्योम
zynqmp_disp_plane_atomic_update(काष्ठा drm_plane *plane,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state, plane);
	काष्ठा zynqmp_disp_layer *layer = plane_to_layer(plane);
	bool क्रमmat_changed = false;

	अगर (!old_state->fb ||
	    old_state->fb->क्रमmat->क्रमmat != new_state->fb->क्रमmat->क्रमmat)
		क्रमmat_changed = true;

	/*
	 * If the क्रमmat has changed (including going from a previously
	 * disabled state to any क्रमmat), reconfigure the क्रमmat. Disable the
	 * plane first अगर needed.
	 */
	अगर (क्रमmat_changed) अणु
		अगर (old_state->fb)
			zynqmp_disp_layer_disable(layer);

		zynqmp_disp_layer_set_क्रमmat(layer, new_state);
	पूर्ण

	zynqmp_disp_layer_update(layer, new_state);

	/* Enable or re-enable the plane is the क्रमmat has changed. */
	अगर (क्रमmat_changed)
		zynqmp_disp_layer_enable(layer);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs zynqmp_disp_plane_helper_funcs = अणु
	.atomic_check		= zynqmp_disp_plane_atomic_check,
	.atomic_update		= zynqmp_disp_plane_atomic_update,
	.atomic_disable		= zynqmp_disp_plane_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs zynqmp_disp_plane_funcs = अणु
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल पूर्णांक zynqmp_disp_create_planes(काष्ठा zynqmp_disp *disp)
अणु
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < ZYNQMP_DISP_NUM_LAYERS; i++) अणु
		काष्ठा zynqmp_disp_layer *layer = &disp->layers[i];
		क्रमागत drm_plane_type type;
		u32 *drm_क्रमmats;

		drm_क्रमmats = drmm_kसुस्मृति(disp->drm, माप(*drm_क्रमmats),
					   layer->info->num_क्रमmats,
					   GFP_KERNEL);
		अगर (!drm_क्रमmats)
			वापस -ENOMEM;

		क्रम (j = 0; j < layer->info->num_क्रमmats; ++j)
			drm_क्रमmats[j] = layer->info->क्रमmats[j].drm_fmt;

		/* Graphics layer is primary, and video layer is overlay. */
		type = i == ZYNQMP_DISP_LAYER_GFX
		     ? DRM_PLANE_TYPE_PRIMARY : DRM_PLANE_TYPE_OVERLAY;
		ret = drm_universal_plane_init(disp->drm, &layer->plane, 0,
					       &zynqmp_disp_plane_funcs,
					       drm_क्रमmats,
					       layer->info->num_क्रमmats,
					       शून्य, type, शून्य);
		अगर (ret)
			वापस ret;

		drm_plane_helper_add(&layer->plane,
				     &zynqmp_disp_plane_helper_funcs);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_disp_layer_release_dma - Release DMA channels क्रम a layer
 * @disp: Display controller
 * @layer: The layer
 *
 * Release the DMA channels associated with @layer.
 */
अटल व्योम zynqmp_disp_layer_release_dma(काष्ठा zynqmp_disp *disp,
					  काष्ठा zynqmp_disp_layer *layer)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!layer->info)
		वापस;

	क्रम (i = 0; i < layer->info->num_channels; i++) अणु
		काष्ठा zynqmp_disp_layer_dma *dma = &layer->dmas[i];

		अगर (!dma->chan)
			जारी;

		/* Make sure the channel is terminated beक्रमe release. */
		dmaengine_terminate_sync(dma->chan);
		dma_release_channel(dma->chan);
	पूर्ण
पूर्ण

/**
 * zynqmp_disp_destroy_layers - Destroy all layers
 * @disp: Display controller
 */
अटल व्योम zynqmp_disp_destroy_layers(काष्ठा zynqmp_disp *disp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ZYNQMP_DISP_NUM_LAYERS; i++)
		zynqmp_disp_layer_release_dma(disp, &disp->layers[i]);
पूर्ण

/**
 * zynqmp_disp_layer_request_dma - Request DMA channels क्रम a layer
 * @disp: Display controller
 * @layer: The layer
 *
 * Request all DMA engine channels needed by @layer.
 *
 * Return: 0 on success, or the DMA channel request error otherwise
 */
अटल पूर्णांक zynqmp_disp_layer_request_dma(काष्ठा zynqmp_disp *disp,
					 काष्ठा zynqmp_disp_layer *layer)
अणु
	अटल स्थिर अक्षर * स्थिर dma_names[] = अणु "vid", "gfx" पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < layer->info->num_channels; i++) अणु
		काष्ठा zynqmp_disp_layer_dma *dma = &layer->dmas[i];
		अक्षर dma_channel_name[16];

		snम_लिखो(dma_channel_name, माप(dma_channel_name),
			 "%s%u", dma_names[layer->id], i);
		dma->chan = dma_request_chan(disp->dev, dma_channel_name);
		अगर (IS_ERR(dma->chan)) अणु
			dev_err(disp->dev, "failed to request dma channel\n");
			ret = PTR_ERR(dma->chan);
			dma->chan = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_disp_create_layers - Create and initialize all layers
 * @disp: Display controller
 *
 * Return: 0 on success, or the DMA channel request error otherwise
 */
अटल पूर्णांक zynqmp_disp_create_layers(काष्ठा zynqmp_disp *disp)
अणु
	अटल स्थिर काष्ठा zynqmp_disp_layer_info layer_info[] = अणु
		[ZYNQMP_DISP_LAYER_VID] = अणु
			.क्रमmats = avbuf_vid_fmts,
			.num_क्रमmats = ARRAY_SIZE(avbuf_vid_fmts),
			.num_channels = 3,
		पूर्ण,
		[ZYNQMP_DISP_LAYER_GFX] = अणु
			.क्रमmats = avbuf_gfx_fmts,
			.num_क्रमmats = ARRAY_SIZE(avbuf_gfx_fmts),
			.num_channels = 1,
		पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ZYNQMP_DISP_NUM_LAYERS; i++) अणु
		काष्ठा zynqmp_disp_layer *layer = &disp->layers[i];

		layer->id = i;
		layer->disp = disp;
		layer->info = &layer_info[i];

		ret = zynqmp_disp_layer_request_dma(disp, layer);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	zynqmp_disp_destroy_layers(disp);
	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * ZynqMP Display & DRM CRTC
 */

/**
 * zynqmp_disp_enable - Enable the display controller
 * @disp: Display controller
 */
अटल व्योम zynqmp_disp_enable(काष्ठा zynqmp_disp *disp)
अणु
	zynqmp_disp_avbuf_enable(&disp->avbuf);
	/* Choose घड़ी source based on the DT घड़ी handle. */
	zynqmp_disp_avbuf_set_घड़ीs_sources(&disp->avbuf, disp->pclk_from_ps,
					     disp->audio.clk_from_ps, true);
	zynqmp_disp_avbuf_enable_channels(&disp->avbuf);
	zynqmp_disp_avbuf_enable_audio(&disp->avbuf);

	zynqmp_disp_audio_enable(&disp->audio);
पूर्ण

/**
 * zynqmp_disp_disable - Disable the display controller
 * @disp: Display controller
 */
अटल व्योम zynqmp_disp_disable(काष्ठा zynqmp_disp *disp)
अणु
	zynqmp_disp_audio_disable(&disp->audio);

	zynqmp_disp_avbuf_disable_audio(&disp->avbuf);
	zynqmp_disp_avbuf_disable_channels(&disp->avbuf);
	zynqmp_disp_avbuf_disable(&disp->avbuf);
पूर्ण

अटल अंतरभूत काष्ठा zynqmp_disp *crtc_to_disp(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा zynqmp_disp, crtc);
पूर्ण

अटल पूर्णांक zynqmp_disp_crtc_setup_घड़ी(काष्ठा drm_crtc *crtc,
					काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा zynqmp_disp *disp = crtc_to_disp(crtc);
	अचिन्हित दीर्घ mode_घड़ी = adjusted_mode->घड़ी * 1000;
	अचिन्हित दीर्घ rate;
	दीर्घ dअगरf;
	पूर्णांक ret;

	ret = clk_set_rate(disp->pclk, mode_घड़ी);
	अगर (ret) अणु
		dev_err(disp->dev, "failed to set a pixel clock\n");
		वापस ret;
	पूर्ण

	rate = clk_get_rate(disp->pclk);
	dअगरf = rate - mode_घड़ी;
	अगर (असल(dअगरf) > mode_घड़ी / 20)
		dev_info(disp->dev,
			 "requested pixel rate: %lu actual rate: %lu\n",
			 mode_घड़ी, rate);
	अन्यथा
		dev_dbg(disp->dev,
			"requested pixel rate: %lu actual rate: %lu\n",
			mode_घड़ी, rate);

	वापस 0;
पूर्ण

अटल व्योम
zynqmp_disp_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा zynqmp_disp *disp = crtc_to_disp(crtc);
	काष्ठा drm_display_mode *adjusted_mode = &crtc->state->adjusted_mode;
	पूर्णांक ret, vrefresh;

	zynqmp_disp_crtc_setup_घड़ी(crtc, adjusted_mode);

	pm_runसमय_get_sync(disp->dev);
	ret = clk_prepare_enable(disp->pclk);
	अगर (ret) अणु
		dev_err(disp->dev, "failed to enable a pixel clock\n");
		pm_runसमय_put_sync(disp->dev);
		वापस;
	पूर्ण

	zynqmp_disp_blend_set_output_क्रमmat(&disp->blend,
					    ZYNQMP_DPSUB_FORMAT_RGB);
	zynqmp_disp_blend_set_bg_color(&disp->blend, 0, 0, 0);
	zynqmp_disp_blend_set_global_alpha(&disp->blend, false, 0);

	zynqmp_disp_enable(disp);

	/* Delay of 3 vblank पूर्णांकervals क्रम timing gen to be stable */
	vrefresh = (adjusted_mode->घड़ी * 1000) /
		   (adjusted_mode->vtotal * adjusted_mode->htotal);
	msleep(3 * 1000 / vrefresh);
पूर्ण

अटल व्योम
zynqmp_disp_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा zynqmp_disp *disp = crtc_to_disp(crtc);
	काष्ठा drm_plane_state *old_plane_state;

	/*
	 * Disable the plane अगर active. The old plane state can be शून्य in the
	 * .shutकरोwn() path अगर the plane is alपढ़ोy disabled, skip
	 * zynqmp_disp_plane_atomic_disable() in that हाल.
	 */
	old_plane_state = drm_atomic_get_old_plane_state(state, crtc->primary);
	अगर (old_plane_state)
		zynqmp_disp_plane_atomic_disable(crtc->primary, state);

	zynqmp_disp_disable(disp);

	drm_crtc_vblank_off(&disp->crtc);

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	clk_disable_unprepare(disp->pclk);
	pm_runसमय_put_sync(disp->dev);
पूर्ण

अटल पूर्णांक zynqmp_disp_crtc_atomic_check(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	वापस drm_atomic_add_affected_planes(state, crtc);
पूर्ण

अटल व्योम
zynqmp_disp_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state)
अणु
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम
zynqmp_disp_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state)
अणु
	अगर (crtc->state->event) अणु
		काष्ठा drm_pending_vblank_event *event;

		/* Consume the flip_करोne event from atomic helper. */
		event = crtc->state->event;
		crtc->state->event = शून्य;

		event->pipe = drm_crtc_index(crtc);

		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_arm_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs zynqmp_disp_crtc_helper_funcs = अणु
	.atomic_enable	= zynqmp_disp_crtc_atomic_enable,
	.atomic_disable	= zynqmp_disp_crtc_atomic_disable,
	.atomic_check	= zynqmp_disp_crtc_atomic_check,
	.atomic_begin	= zynqmp_disp_crtc_atomic_begin,
	.atomic_flush	= zynqmp_disp_crtc_atomic_flush,
पूर्ण;

अटल पूर्णांक zynqmp_disp_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zynqmp_disp *disp = crtc_to_disp(crtc);

	zynqmp_dp_enable_vblank(disp->dpsub->dp);

	वापस 0;
पूर्ण

अटल व्योम zynqmp_disp_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा zynqmp_disp *disp = crtc_to_disp(crtc);

	zynqmp_dp_disable_vblank(disp->dpsub->dp);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs zynqmp_disp_crtc_funcs = अणु
	.destroy		= drm_crtc_cleanup,
	.set_config		= drm_atomic_helper_set_config,
	.page_flip		= drm_atomic_helper_page_flip,
	.reset			= drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state	= drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_crtc_destroy_state,
	.enable_vblank		= zynqmp_disp_crtc_enable_vblank,
	.disable_vblank		= zynqmp_disp_crtc_disable_vblank,
पूर्ण;

अटल पूर्णांक zynqmp_disp_create_crtc(काष्ठा zynqmp_disp *disp)
अणु
	काष्ठा drm_plane *plane = &disp->layers[ZYNQMP_DISP_LAYER_GFX].plane;
	पूर्णांक ret;

	ret = drm_crtc_init_with_planes(disp->drm, &disp->crtc, plane,
					शून्य, &zynqmp_disp_crtc_funcs, शून्य);
	अगर (ret < 0)
		वापस ret;

	drm_crtc_helper_add(&disp->crtc, &zynqmp_disp_crtc_helper_funcs);

	/* Start with vertical blanking पूर्णांकerrupt reporting disabled. */
	drm_crtc_vblank_off(&disp->crtc);

	वापस 0;
पूर्ण

अटल व्योम zynqmp_disp_map_crtc_to_plane(काष्ठा zynqmp_disp *disp)
अणु
	u32 possible_crtcs = drm_crtc_mask(&disp->crtc);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ZYNQMP_DISP_NUM_LAYERS; i++)
		disp->layers[i].plane.possible_crtcs = possible_crtcs;
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization & Cleanup
 */

पूर्णांक zynqmp_disp_drm_init(काष्ठा zynqmp_dpsub *dpsub)
अणु
	काष्ठा zynqmp_disp *disp = dpsub->disp;
	पूर्णांक ret;

	ret = zynqmp_disp_create_planes(disp);
	अगर (ret)
		वापस ret;

	ret = zynqmp_disp_create_crtc(disp);
	अगर (ret < 0)
		वापस ret;

	zynqmp_disp_map_crtc_to_plane(disp);

	वापस 0;
पूर्ण

पूर्णांक zynqmp_disp_probe(काष्ठा zynqmp_dpsub *dpsub, काष्ठा drm_device *drm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dpsub->dev);
	काष्ठा zynqmp_disp *disp;
	काष्ठा zynqmp_disp_layer *layer;
	काष्ठा resource *res;
	पूर्णांक ret;

	disp = drmm_kzalloc(drm, माप(*disp), GFP_KERNEL);
	अगर (!disp)
		वापस -ENOMEM;

	disp->dev = &pdev->dev;
	disp->dpsub = dpsub;
	disp->drm = drm;

	dpsub->disp = disp;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "blend");
	disp->blend.base = devm_ioremap_resource(disp->dev, res);
	अगर (IS_ERR(disp->blend.base))
		वापस PTR_ERR(disp->blend.base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "av_buf");
	disp->avbuf.base = devm_ioremap_resource(disp->dev, res);
	अगर (IS_ERR(disp->avbuf.base))
		वापस PTR_ERR(disp->avbuf.base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "aud");
	disp->audio.base = devm_ioremap_resource(disp->dev, res);
	अगर (IS_ERR(disp->audio.base))
		वापस PTR_ERR(disp->audio.base);

	/* Try the live PL video घड़ी */
	disp->pclk = devm_clk_get(disp->dev, "dp_live_video_in_clk");
	अगर (!IS_ERR(disp->pclk))
		disp->pclk_from_ps = false;
	अन्यथा अगर (PTR_ERR(disp->pclk) == -EPROBE_DEFER)
		वापस PTR_ERR(disp->pclk);

	/* If the live PL video घड़ी is not valid, fall back to PS घड़ी */
	अगर (IS_ERR_OR_शून्य(disp->pclk)) अणु
		disp->pclk = devm_clk_get(disp->dev, "dp_vtc_pixel_clk_in");
		अगर (IS_ERR(disp->pclk)) अणु
			dev_err(disp->dev, "failed to init any video clock\n");
			वापस PTR_ERR(disp->pclk);
		पूर्ण
		disp->pclk_from_ps = true;
	पूर्ण

	zynqmp_disp_audio_init(disp->dev, &disp->audio);

	ret = zynqmp_disp_create_layers(disp);
	अगर (ret)
		वापस ret;

	layer = &disp->layers[ZYNQMP_DISP_LAYER_VID];
	dpsub->dma_align = 1 << layer->dmas[0].chan->device->copy_align;

	वापस 0;
पूर्ण

व्योम zynqmp_disp_हटाओ(काष्ठा zynqmp_dpsub *dpsub)
अणु
	काष्ठा zynqmp_disp *disp = dpsub->disp;

	zynqmp_disp_destroy_layers(disp);
पूर्ण
