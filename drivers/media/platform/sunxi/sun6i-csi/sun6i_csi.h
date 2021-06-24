<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 2011-2018 Magewell Electronics Co., Ltd. (Nanjing)
 * All rights reserved.
 * Author: Yong Deng <yong.deng@magewell.com>
 */

#अगर_अघोषित __SUN6I_CSI_H__
#घोषणा __SUN6I_CSI_H__

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "sun6i_video.h"

काष्ठा sun6i_csi;

/**
 * काष्ठा sun6i_csi_config - configs क्रम sun6i csi
 * @pixelक्रमmat: v4l2 pixel क्रमmat (V4L2_PIX_FMT_*)
 * @code:	media bus क्रमmat code (MEDIA_BUS_FMT_*)
 * @field:	used पूर्णांकerlacing type (क्रमागत v4l2_field)
 * @width:	frame width
 * @height:	frame height
 */
काष्ठा sun6i_csi_config अणु
	u32		pixelक्रमmat;
	u32		code;
	u32		field;
	u32		width;
	u32		height;
पूर्ण;

काष्ठा sun6i_csi अणु
	काष्ठा device			*dev;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा media_device		media_dev;

	काष्ठा v4l2_async_notअगरier	notअगरier;

	/* video port settings */
	काष्ठा v4l2_fwnode_endpoपूर्णांक	v4l2_ep;

	काष्ठा sun6i_csi_config		config;

	काष्ठा sun6i_video		video;
पूर्ण;

/**
 * sun6i_csi_is_क्रमmat_supported() - check अगर the क्रमmat supported by csi
 * @csi:	poपूर्णांकer to the csi
 * @pixक्रमmat:	v4l2 pixel क्रमmat (V4L2_PIX_FMT_*)
 * @mbus_code:	media bus क्रमmat code (MEDIA_BUS_FMT_*)
 */
bool sun6i_csi_is_क्रमmat_supported(काष्ठा sun6i_csi *csi, u32 pixक्रमmat,
				   u32 mbus_code);

/**
 * sun6i_csi_set_घातer() - घातer on/off the csi
 * @csi:	poपूर्णांकer to the csi
 * @enable:	on/off
 */
पूर्णांक sun6i_csi_set_घातer(काष्ठा sun6i_csi *csi, bool enable);

/**
 * sun6i_csi_update_config() - update the csi रेजिस्टर settings
 * @csi:	poपूर्णांकer to the csi
 * @config:	see काष्ठा sun6i_csi_config
 */
पूर्णांक sun6i_csi_update_config(काष्ठा sun6i_csi *csi,
			    काष्ठा sun6i_csi_config *config);

/**
 * sun6i_csi_update_buf_addr() - update the csi frame buffer address
 * @csi:	poपूर्णांकer to the csi
 * @addr:	frame buffer's physical address
 */
व्योम sun6i_csi_update_buf_addr(काष्ठा sun6i_csi *csi, dma_addr_t addr);

/**
 * sun6i_csi_set_stream() - start/stop csi streaming
 * @csi:	poपूर्णांकer to the csi
 * @enable:	start/stop
 */
व्योम sun6i_csi_set_stream(काष्ठा sun6i_csi *csi, bool enable);

/* get bpp क्रमm v4l2 pixक्रमmat */
अटल अंतरभूत पूर्णांक sun6i_csi_get_bpp(अचिन्हित पूर्णांक pixक्रमmat)
अणु
	चयन (pixक्रमmat) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
	हाल V4L2_PIX_FMT_JPEG:
		वापस 8;
	हाल V4L2_PIX_FMT_SBGGR10:
	हाल V4L2_PIX_FMT_SGBRG10:
	हाल V4L2_PIX_FMT_SGRBG10:
	हाल V4L2_PIX_FMT_SRGGB10:
		वापस 10;
	हाल V4L2_PIX_FMT_SBGGR12:
	हाल V4L2_PIX_FMT_SGBRG12:
	हाल V4L2_PIX_FMT_SGRBG12:
	हाल V4L2_PIX_FMT_SRGGB12:
	हाल V4L2_PIX_FMT_HM12:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
		वापस 12;
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_YVYU:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_VYUY:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
		वापस 16;
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_BGR24:
		वापस 24;
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
		वापस 32;
	शेष:
		WARN(1, "Unsupported pixformat: 0x%x\n", pixक्रमmat);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __SUN6I_CSI_H__ */
