<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispresizer.h
 *
 * TI OMAP3 ISP - Resizer module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_RESIZER_H
#घोषणा OMAP3_ISP_RESIZER_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/*
 * Constants क्रम filter coefficients count
 */
#घोषणा COEFF_CNT		32

/*
 * काष्ठा isprsz_coef - Structure क्रम resizer filter coefficients.
 * @h_filter_coef_4tap: Horizontal filter coefficients क्रम 8-phase/4-tap
 *			mode (.5x-4x)
 * @v_filter_coef_4tap: Vertical filter coefficients क्रम 8-phase/4-tap
 *			mode (.5x-4x)
 * @h_filter_coef_7tap: Horizontal filter coefficients क्रम 4-phase/7-tap
 *			mode (.25x-.5x)
 * @v_filter_coef_7tap: Vertical filter coefficients क्रम 4-phase/7-tap
 *			mode (.25x-.5x)
 */
काष्ठा isprsz_coef अणु
	u16 h_filter_coef_4tap[32];
	u16 v_filter_coef_4tap[32];
	/* Every 8th value is a dummy value in the following arrays: */
	u16 h_filter_coef_7tap[32];
	u16 v_filter_coef_7tap[32];
पूर्ण;

/* Chrominance horizontal algorithm */
क्रमागत resizer_chroma_algo अणु
	RSZ_THE_SAME = 0,	/* Chrominance the same as Luminance */
	RSZ_BILINEAR = 1,	/* Chrominance uses bilinear पूर्णांकerpolation */
पूर्ण;

/* Resizer input type select */
क्रमागत resizer_colors_type अणु
	RSZ_YUV422 = 0,		/* YUV422 color is पूर्णांकerleaved */
	RSZ_COLOR8 = 1,		/* Color separate data on 8 bits */
पूर्ण;

/*
 * Structure क्रम horizontal and vertical resizing value
 */
काष्ठा resizer_ratio अणु
	u32 horz;
	u32 vert;
पूर्ण;

/*
 * Structure क्रम luminance enhancer parameters.
 */
काष्ठा resizer_luma_yenh अणु
	u8 algo;		/* algorithm select. */
	u8 gain;		/* maximum gain. */
	u8 slope;		/* slope. */
	u8 core;		/* core offset. */
पूर्ण;

क्रमागत resizer_input_entity अणु
	RESIZER_INPUT_NONE,
	RESIZER_INPUT_VP,	/* input video port - prev or ccdc */
	RESIZER_INPUT_MEMORY,
पूर्ण;

/* Sink and source resizer pads */
#घोषणा RESZ_PAD_SINK			0
#घोषणा RESZ_PAD_SOURCE			1
#घोषणा RESZ_PADS_NUM			2

/*
 * काष्ठा isp_res_device - OMAP3 ISP resizer module
 * @lock: Protects क्रमmats and crop rectangles between set_selection and IRQ
 * @crop.request: Crop rectangle requested by the user
 * @crop.active: Active crop rectangle (based on hardware requirements)
 */
काष्ठा isp_res_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[RESZ_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[RESZ_PADS_NUM];

	क्रमागत resizer_input_entity input;
	काष्ठा isp_video video_in;
	काष्ठा isp_video video_out;

	u32 addr_base;   /* stored source buffer address in memory mode */
	u32 crop_offset; /* additional offset क्रम crop in memory mode */
	काष्ठा resizer_ratio ratio;
	पूर्णांक pm_state;
	अचिन्हित पूर्णांक applycrop:1;
	क्रमागत isp_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
	spinlock_t lock;

	काष्ठा अणु
		काष्ठा v4l2_rect request;
		काष्ठा v4l2_rect active;
	पूर्ण crop;
पूर्ण;

काष्ठा isp_device;

पूर्णांक omap3isp_resizer_init(काष्ठा isp_device *isp);
व्योम omap3isp_resizer_cleanup(काष्ठा isp_device *isp);

पूर्णांक omap3isp_resizer_रेजिस्टर_entities(काष्ठा isp_res_device *res,
				       काष्ठा v4l2_device *vdev);
व्योम omap3isp_resizer_unरेजिस्टर_entities(काष्ठा isp_res_device *res);
व्योम omap3isp_resizer_isr_frame_sync(काष्ठा isp_res_device *res);
व्योम omap3isp_resizer_isr(काष्ठा isp_res_device *isp_res);

व्योम omap3isp_resizer_max_rate(काष्ठा isp_res_device *res,
			       अचिन्हित पूर्णांक *max_rate);

व्योम omap3isp_resizer_suspend(काष्ठा isp_res_device *isp_res);

व्योम omap3isp_resizer_resume(काष्ठा isp_res_device *isp_res);

पूर्णांक omap3isp_resizer_busy(काष्ठा isp_res_device *isp_res);

#पूर्ण_अगर	/* OMAP3_ISP_RESIZER_H */
