<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vsp1_pipe.c  --  R-Car VSP1 Pipeline
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_brx.h"
#समावेश "vsp1_dl.h"
#समावेश "vsp1_entity.h"
#समावेश "vsp1_hgo.h"
#समावेश "vsp1_hgt.h"
#समावेश "vsp1_pipe.h"
#समावेश "vsp1_rwpf.h"
#समावेश "vsp1_uds.h"

/* -----------------------------------------------------------------------------
 * Helper Functions
 */

अटल स्थिर काष्ठा vsp1_क्रमmat_info vsp1_video_क्रमmats[] = अणु
	अणु V4L2_PIX_FMT_RGB332, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGB_332, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 8, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ARGB444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XRGB444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_XRGB_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_RGBA444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_RGBX444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBX_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ABGR444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ABGR_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XBGR444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ABGR_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_BGRA444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_BGRA_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_BGRX444, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_BGRA_4444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ARGB555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_1555, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XRGB555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_XRGB_1555, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_RGBA555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_5551, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_RGBX555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBX_5551, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ABGR555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ABGR_1555, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XBGR555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ABGR_1555, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_BGRA555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_BGRA_5551, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_BGRX555, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_BGRA_5551, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_RGB565, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGB_565, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_BGR24, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_BGR_888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 24, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_RGB24, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGB_888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 24, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ABGR32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XBGR32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_BGRA32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_BGRX32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_RGBA32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_RGBX32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_RGBA_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_ARGB32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, true पूर्ण,
	अणु V4L2_PIX_FMT_XRGB32, MEDIA_BUS_FMT_ARGB8888_1X32,
	  VI6_FMT_ARGB_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_HSV24, MEDIA_BUS_FMT_AHSV8888_1X32,
	  VI6_FMT_RGB_888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 24, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_HSV32, MEDIA_BUS_FMT_AHSV8888_1X32,
	  VI6_FMT_ARGB_8888, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 32, 0, 0 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_UYVY, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 16, 0, 0 पूर्ण, false, false, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_VYUY, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 16, 0, 0 पूर्ण, false, true, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YUYV, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 16, 0, 0 पूर्ण, true, false, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YVYU, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_YUYV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  1, अणु 16, 0, 0 पूर्ण, true, true, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_NV12M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_420, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  2, अणु 8, 16, 0 पूर्ण, false, false, 2, 2, false पूर्ण,
	अणु V4L2_PIX_FMT_NV21M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_420, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  2, अणु 8, 16, 0 पूर्ण, false, true, 2, 2, false पूर्ण,
	अणु V4L2_PIX_FMT_NV16M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  2, अणु 8, 16, 0 पूर्ण, false, false, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_NV61M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_UV_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  2, अणु 8, 16, 0 पूर्ण, false, true, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YUV420M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_420, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, false, 2, 2, false पूर्ण,
	अणु V4L2_PIX_FMT_YVU420M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_420, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, true, 2, 2, false पूर्ण,
	अणु V4L2_PIX_FMT_YUV422M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, false, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YVU422M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_422, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, true, 2, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YUV444M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, false, 1, 1, false पूर्ण,
	अणु V4L2_PIX_FMT_YVU444M, MEDIA_BUS_FMT_AYUV8_1X32,
	  VI6_FMT_Y_U_V_444, VI6_RPF_DSWAP_P_LLS | VI6_RPF_DSWAP_P_LWS |
	  VI6_RPF_DSWAP_P_WDS | VI6_RPF_DSWAP_P_BTS,
	  3, अणु 8, 8, 8 पूर्ण, false, true, 1, 1, false पूर्ण,
पूर्ण;

/**
 * vsp1_get_क्रमmat_info - Retrieve क्रमmat inक्रमmation क्रम a 4CC
 * @vsp1: the VSP1 device
 * @fourcc: the क्रमmat 4CC
 *
 * Return a poपूर्णांकer to the क्रमmat inक्रमmation काष्ठाure corresponding to the
 * given V4L2 क्रमmat 4CC, or शून्य अगर no corresponding क्रमmat can be found.
 */
स्थिर काष्ठा vsp1_क्रमmat_info *vsp1_get_क्रमmat_info(काष्ठा vsp1_device *vsp1,
						    u32 fourcc)
अणु
	अचिन्हित पूर्णांक i;

	/* Special हाल, the VYUY and HSV क्रमmats are supported on Gen2 only. */
	अगर (vsp1->info->gen != 2) अणु
		चयन (fourcc) अणु
		हाल V4L2_PIX_FMT_VYUY:
		हाल V4L2_PIX_FMT_HSV24:
		हाल V4L2_PIX_FMT_HSV32:
			वापस शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vsp1_video_क्रमmats); ++i) अणु
		स्थिर काष्ठा vsp1_क्रमmat_info *info = &vsp1_video_क्रमmats[i];

		अगर (info->fourcc == fourcc)
			वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण

/* -----------------------------------------------------------------------------
 * Pipeline Management
 */

व्योम vsp1_pipeline_reset(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_entity *entity;
	अचिन्हित पूर्णांक i;

	अगर (pipe->brx) अणु
		काष्ठा vsp1_brx *brx = to_brx(&pipe->brx->subdev);

		क्रम (i = 0; i < ARRAY_SIZE(brx->inमाला_दो); ++i)
			brx->inमाला_दो[i].rpf = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pipe->inमाला_दो); ++i)
		pipe->inमाला_दो[i] = शून्य;

	pipe->output = शून्य;

	list_क्रम_each_entry(entity, &pipe->entities, list_pipe)
		entity->pipe = शून्य;

	INIT_LIST_HEAD(&pipe->entities);
	pipe->state = VSP1_PIPELINE_STOPPED;
	pipe->buffers_पढ़ोy = 0;
	pipe->num_inमाला_दो = 0;
	pipe->brx = शून्य;
	pipe->hgo = शून्य;
	pipe->hgt = शून्य;
	pipe->lअगर = शून्य;
	pipe->uds = शून्य;
पूर्ण

व्योम vsp1_pipeline_init(काष्ठा vsp1_pipeline *pipe)
अणु
	mutex_init(&pipe->lock);
	spin_lock_init(&pipe->irqlock);
	init_रुकोqueue_head(&pipe->wq);
	kref_init(&pipe->kref);

	INIT_LIST_HEAD(&pipe->entities);
	pipe->state = VSP1_PIPELINE_STOPPED;
पूर्ण

/* Must be called with the pipe irqlock held. */
व्योम vsp1_pipeline_run(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_device *vsp1 = pipe->output->entity.vsp1;

	अगर (pipe->state == VSP1_PIPELINE_STOPPED) अणु
		vsp1_ग_लिखो(vsp1, VI6_CMD(pipe->output->entity.index),
			   VI6_CMD_STRCMD);
		pipe->state = VSP1_PIPELINE_RUNNING;
	पूर्ण

	pipe->buffers_पढ़ोy = 0;
पूर्ण

bool vsp1_pipeline_stopped(काष्ठा vsp1_pipeline *pipe)
अणु
	अचिन्हित दीर्घ flags;
	bool stopped;

	spin_lock_irqsave(&pipe->irqlock, flags);
	stopped = pipe->state == VSP1_PIPELINE_STOPPED;
	spin_unlock_irqrestore(&pipe->irqlock, flags);

	वापस stopped;
पूर्ण

पूर्णांक vsp1_pipeline_stop(काष्ठा vsp1_pipeline *pipe)
अणु
	काष्ठा vsp1_device *vsp1 = pipe->output->entity.vsp1;
	काष्ठा vsp1_entity *entity;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (pipe->lअगर) अणु
		/*
		 * When using display lists in continuous frame mode the only
		 * way to stop the pipeline is to reset the hardware.
		 */
		ret = vsp1_reset_wpf(vsp1, pipe->output->entity.index);
		अगर (ret == 0) अणु
			spin_lock_irqsave(&pipe->irqlock, flags);
			pipe->state = VSP1_PIPELINE_STOPPED;
			spin_unlock_irqrestore(&pipe->irqlock, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Otherwise just request a stop and रुको. */
		spin_lock_irqsave(&pipe->irqlock, flags);
		अगर (pipe->state == VSP1_PIPELINE_RUNNING)
			pipe->state = VSP1_PIPELINE_STOPPING;
		spin_unlock_irqrestore(&pipe->irqlock, flags);

		ret = रुको_event_समयout(pipe->wq, vsp1_pipeline_stopped(pipe),
					 msecs_to_jअगरfies(500));
		ret = ret == 0 ? -ETIMEDOUT : 0;
	पूर्ण

	list_क्रम_each_entry(entity, &pipe->entities, list_pipe) अणु
		अगर (entity->route && entity->route->reg)
			vsp1_ग_लिखो(vsp1, entity->route->reg,
				   VI6_DPR_NODE_UNUSED);
	पूर्ण

	अगर (pipe->hgo)
		vsp1_ग_लिखो(vsp1, VI6_DPR_HGO_SMPPT,
			   (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
			   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));

	अगर (pipe->hgt)
		vsp1_ग_लिखो(vsp1, VI6_DPR_HGT_SMPPT,
			   (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
			   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));

	v4l2_subdev_call(&pipe->output->entity.subdev, video, s_stream, 0);

	वापस ret;
पूर्ण

bool vsp1_pipeline_पढ़ोy(काष्ठा vsp1_pipeline *pipe)
अणु
	अचिन्हित पूर्णांक mask;

	mask = ((1 << pipe->num_inमाला_दो) - 1) << 1;
	अगर (!pipe->lअगर)
		mask |= 1 << 0;

	वापस pipe->buffers_पढ़ोy == mask;
पूर्ण

व्योम vsp1_pipeline_frame_end(काष्ठा vsp1_pipeline *pipe)
अणु
	अचिन्हित पूर्णांक flags;

	अगर (pipe == शून्य)
		वापस;

	/*
	 * If the DL commit raced with the frame end पूर्णांकerrupt, the commit ends
	 * up being postponed by one frame. The वापसed flags tell whether the
	 * active frame was finished or postponed.
	 */
	flags = vsp1_dlm_irq_frame_end(pipe->output->dlm);

	अगर (pipe->hgo)
		vsp1_hgo_frame_end(pipe->hgo);

	अगर (pipe->hgt)
		vsp1_hgt_frame_end(pipe->hgt);

	/*
	 * Regardless of frame completion we still need to notअगरy the pipe
	 * frame_end to account क्रम vblank events.
	 */
	अगर (pipe->frame_end)
		pipe->frame_end(pipe, flags);

	pipe->sequence++;
पूर्ण

/*
 * Propagate the alpha value through the pipeline.
 *
 * As the UDS has restricted scaling capabilities when the alpha component needs
 * to be scaled, we disable alpha scaling when the UDS input has a fixed alpha
 * value. The UDS then outमाला_दो a fixed alpha value which needs to be programmed
 * from the input RPF alpha.
 */
व्योम vsp1_pipeline_propagate_alpha(काष्ठा vsp1_pipeline *pipe,
				   काष्ठा vsp1_dl_body *dlb, अचिन्हित पूर्णांक alpha)
अणु
	अगर (!pipe->uds)
		वापस;

	/*
	 * The BRU and BRS background color has a fixed alpha value set to 255,
	 * the output alpha value is thus always equal to 255.
	 */
	अगर (pipe->uds_input->type == VSP1_ENTITY_BRU ||
	    pipe->uds_input->type == VSP1_ENTITY_BRS)
		alpha = 255;

	vsp1_uds_set_alpha(pipe->uds, dlb, alpha);
पूर्ण

/*
 * Propagate the partition calculations through the pipeline
 *
 * Work backwards through the pipe, allowing each entity to update the partition
 * parameters based on its configuration, and the entity connected to its
 * source. Each entity must produce the partition required क्रम the previous
 * entity in the pipeline.
 */
व्योम vsp1_pipeline_propagate_partition(काष्ठा vsp1_pipeline *pipe,
				       काष्ठा vsp1_partition *partition,
				       अचिन्हित पूर्णांक index,
				       काष्ठा vsp1_partition_winकरोw *winकरोw)
अणु
	काष्ठा vsp1_entity *entity;

	list_क्रम_each_entry_reverse(entity, &pipe->entities, list_pipe) अणु
		अगर (entity->ops->partition)
			entity->ops->partition(entity, pipe, partition, index,
					       winकरोw);
	पूर्ण
पूर्ण

