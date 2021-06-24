<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * isppreview.h
 *
 * TI OMAP3 ISP - Preview module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_PREVIEW_H
#घोषणा OMAP3_ISP_PREVIEW_H

#समावेश <linux/omap3isp.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "ispvideo.h"

#घोषणा ISPPRV_BRIGHT_STEP		0x1
#घोषणा ISPPRV_BRIGHT_DEF		0x0
#घोषणा ISPPRV_BRIGHT_LOW		0x0
#घोषणा ISPPRV_BRIGHT_HIGH		0xFF
#घोषणा ISPPRV_BRIGHT_UNITS		0x1

#घोषणा ISPPRV_CONTRAST_STEP		0x1
#घोषणा ISPPRV_CONTRAST_DEF		0x10
#घोषणा ISPPRV_CONTRAST_LOW		0x0
#घोषणा ISPPRV_CONTRAST_HIGH		0xFF
#घोषणा ISPPRV_CONTRAST_UNITS		0x1

/* Additional features not listed in linux/omap3isp.h */
#घोषणा OMAP3ISP_PREV_CONTRAST		(1 << 17)
#घोषणा OMAP3ISP_PREV_BRIGHTNESS	(1 << 18)
#घोषणा OMAP3ISP_PREV_FEATURES_END	(1 << 19)

क्रमागत preview_input_entity अणु
	PREVIEW_INPUT_NONE,
	PREVIEW_INPUT_CCDC,
	PREVIEW_INPUT_MEMORY,
पूर्ण;

#घोषणा PREVIEW_OUTPUT_RESIZER		(1 << 1)
#घोषणा PREVIEW_OUTPUT_MEMORY		(1 << 2)

/* Configure byte layout of YUV image */
क्रमागत preview_ycpos_mode अणु
	YCPOS_YCrYCb = 0,
	YCPOS_YCbYCr = 1,
	YCPOS_CbYCrY = 2,
	YCPOS_CrYCbY = 3
पूर्ण;

/*
 * काष्ठा prev_params - Structure क्रम all configuration
 * @busy: Biपंचांगask of busy parameters (being updated or used)
 * @update: Biपंचांगask of the parameters to be updated
 * @features: Set of features enabled.
 * @cfa: CFA coefficients.
 * @csup: Chroma suppression coefficients.
 * @luma: Luma enhancement coefficients.
 * @nf: Noise filter coefficients.
 * @dcor: Noise filter coefficients.
 * @gamma: Gamma coefficients.
 * @wbal: White Balance parameters.
 * @blkadj: Black adjusपंचांगent parameters.
 * @rgb2rgb: RGB blending parameters.
 * @csc: Color space conversion (RGB to YCbCr) parameters.
 * @hmed: Horizontal median filter.
 * @yclimit: YC limits parameters.
 * @contrast: Contrast.
 * @brightness: Brightness.
 */
काष्ठा prev_params अणु
	u32 busy;
	u32 update;
	u32 features;
	काष्ठा omap3isp_prev_cfa cfa;
	काष्ठा omap3isp_prev_csup csup;
	काष्ठा omap3isp_prev_luma luma;
	काष्ठा omap3isp_prev_nf nf;
	काष्ठा omap3isp_prev_dcor dcor;
	काष्ठा omap3isp_prev_gtables gamma;
	काष्ठा omap3isp_prev_wbal wbal;
	काष्ठा omap3isp_prev_blkadj blkadj;
	काष्ठा omap3isp_prev_rgbtorgb rgb2rgb;
	काष्ठा omap3isp_prev_csc csc;
	काष्ठा omap3isp_prev_hmed hmed;
	काष्ठा omap3isp_prev_yclimit yclimit;
	u8 contrast;
	u8 brightness;
पूर्ण;

/* Sink and source previewer pads */
#घोषणा PREV_PAD_SINK			0
#घोषणा PREV_PAD_SOURCE			1
#घोषणा PREV_PADS_NUM			2

/*
 * काष्ठा isp_prev_device - Structure क्रम storing ISP Preview module inक्रमmation
 * @subdev: V4L2 subdevice
 * @pads: Media entity pads
 * @क्रमmats: Active क्रमmats at the subdev pad
 * @crop: Active crop rectangle
 * @input: Module currently connected to the input pad
 * @output: Biपंचांगask of the active output
 * @video_in: Input video entity
 * @video_out: Output video entity
 * @params.params : Active and shaकरोw parameters sets
 * @params.active: Biपंचांगask of parameters active in set 0
 * @params.lock: Parameters lock, protects params.active and params.shaकरोw
 * @underrun: Whether the preview entity has queued buffers on the output
 * @state: Current preview pipeline state
 *
 * This काष्ठाure is used to store the OMAP ISP Preview module Inक्रमmation.
 */
काष्ठा isp_prev_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[PREV_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[PREV_PADS_NUM];
	काष्ठा v4l2_rect crop;

	काष्ठा v4l2_ctrl_handler ctrls;

	क्रमागत preview_input_entity input;
	अचिन्हित पूर्णांक output;
	काष्ठा isp_video video_in;
	काष्ठा isp_video video_out;

	काष्ठा अणु
		अचिन्हित पूर्णांक cfa_order;
		काष्ठा prev_params params[2];
		u32 active;
		spinlock_t lock;
	पूर्ण params;

	क्रमागत isp_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

काष्ठा isp_device;

पूर्णांक omap3isp_preview_init(काष्ठा isp_device *isp);
व्योम omap3isp_preview_cleanup(काष्ठा isp_device *isp);

पूर्णांक omap3isp_preview_रेजिस्टर_entities(काष्ठा isp_prev_device *prv,
				       काष्ठा v4l2_device *vdev);
व्योम omap3isp_preview_unरेजिस्टर_entities(काष्ठा isp_prev_device *prv);

व्योम omap3isp_preview_isr_frame_sync(काष्ठा isp_prev_device *prev);
व्योम omap3isp_preview_isr(काष्ठा isp_prev_device *prev);

पूर्णांक omap3isp_preview_busy(काष्ठा isp_prev_device *isp_prev);

व्योम omap3isp_preview_restore_context(काष्ठा isp_device *isp);

#पूर्ण_अगर	/* OMAP3_ISP_PREVIEW_H */
