<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-video.c
 *
 * Qualcomm MSM Camera Subप्रणाली - V4L2 device node
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#समावेश <linux/slab.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "camss-video.h"
#समावेश "camss.h"

#घोषणा CAMSS_FRAME_MIN_WIDTH		1
#घोषणा CAMSS_FRAME_MAX_WIDTH		8191
#घोषणा CAMSS_FRAME_MIN_HEIGHT		1
#घोषणा CAMSS_FRAME_MAX_HEIGHT_RDI	8191
#घोषणा CAMSS_FRAME_MAX_HEIGHT_PIX	4096

काष्ठा fract अणु
	u8 numerator;
	u8 denominator;
पूर्ण;

/*
 * काष्ठा camss_क्रमmat_info - ISP media bus क्रमmat inक्रमmation
 * @code: V4L2 media bus क्रमmat code
 * @pixelक्रमmat: V4L2 pixel क्रमmat FCC identअगरier
 * @planes: Number of planes
 * @hsub: Horizontal subsampling (क्रम each plane)
 * @vsub: Vertical subsampling (क्रम each plane)
 * @bpp: Bits per pixel when stored in memory (क्रम each plane)
 */
काष्ठा camss_क्रमmat_info अणु
	u32 code;
	u32 pixelक्रमmat;
	u8 planes;
	काष्ठा fract hsub[3];
	काष्ठा fract vsub[3];
	अचिन्हित पूर्णांक bpp[3];
पूर्ण;

अटल स्थिर काष्ठा camss_क्रमmat_info क्रमmats_rdi_8x16[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_UYVY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_VYUY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_YUYV, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_YVYU, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, V4L2_PIX_FMT_SBGGR8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, V4L2_PIX_FMT_SGBRG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, V4L2_PIX_FMT_SGRBG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, V4L2_PIX_FMT_SRGGB8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, V4L2_PIX_FMT_SBGGR10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, V4L2_PIX_FMT_SGBRG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, V4L2_PIX_FMT_SGRBG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, V4L2_PIX_FMT_SRGGB10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, V4L2_PIX_FMT_SBGGR12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, V4L2_PIX_FMT_SGBRG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, V4L2_PIX_FMT_SGRBG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, V4L2_PIX_FMT_SRGGB12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, V4L2_PIX_FMT_Y10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा camss_क्रमmat_info क्रमmats_rdi_8x96[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_UYVY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_VYUY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_YUYV, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_YVYU, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, V4L2_PIX_FMT_SBGGR8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, V4L2_PIX_FMT_SGBRG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, V4L2_PIX_FMT_SGRBG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, V4L2_PIX_FMT_SRGGB8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, V4L2_PIX_FMT_SBGGR10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, V4L2_PIX_FMT_SGBRG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, V4L2_PIX_FMT_SGRBG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, V4L2_PIX_FMT_SRGGB10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, V4L2_PIX_FMT_SBGGR10, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, V4L2_PIX_FMT_SBGGR12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, V4L2_PIX_FMT_SGBRG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, V4L2_PIX_FMT_SGRBG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, V4L2_PIX_FMT_SRGGB12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, V4L2_PIX_FMT_SBGGR14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, V4L2_PIX_FMT_SGBRG14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, V4L2_PIX_FMT_SGRBG14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, V4L2_PIX_FMT_SRGGB14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, V4L2_PIX_FMT_Y10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_2X8_PADHI_LE, V4L2_PIX_FMT_Y10, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा camss_क्रमmat_info क्रमmats_rdi_845[] = अणु
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_UYVY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_VYUY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_YUYV, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_YVYU, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR8_1X8, V4L2_PIX_FMT_SBGGR8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG8_1X8, V4L2_PIX_FMT_SGBRG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG8_1X8, V4L2_PIX_FMT_SGRBG8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB8_1X8, V4L2_PIX_FMT_SRGGB8, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_1X10, V4L2_PIX_FMT_SBGGR10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG10_1X10, V4L2_PIX_FMT_SGBRG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG10_1X10, V4L2_PIX_FMT_SGRBG10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB10_1X10, V4L2_PIX_FMT_SRGGB10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE, V4L2_PIX_FMT_SBGGR10, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR12_1X12, V4L2_PIX_FMT_SBGGR12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG12_1X12, V4L2_PIX_FMT_SGBRG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG12_1X12, V4L2_PIX_FMT_SGRBG12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB12_1X12, V4L2_PIX_FMT_SRGGB12P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 12 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SBGGR14_1X14, V4L2_PIX_FMT_SBGGR14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGBRG14_1X14, V4L2_PIX_FMT_SGBRG14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SGRBG14_1X14, V4L2_PIX_FMT_SGRBG14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_SRGGB14_1X14, V4L2_PIX_FMT_SRGGB14P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 14 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_1X10, V4L2_PIX_FMT_Y10P, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 10 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_Y10_2X8_PADHI_LE, V4L2_PIX_FMT_Y10, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा camss_क्रमmat_info क्रमmats_pix_8x16[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा camss_क्रमmat_info क्रमmats_pix_8x96[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1_5X8, V4L2_PIX_FMT_NV12, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_1_5X8, V4L2_PIX_FMT_NV21, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 2, 3 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_NV16, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_NV61, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 2 पूर्ण पूर्ण, अणु 8 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_UYVY8_2X8, V4L2_PIX_FMT_UYVY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_VYUY8_2X8, V4L2_PIX_FMT_VYUY, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YUYV8_2X8, V4L2_PIX_FMT_YUYV, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
	अणु MEDIA_BUS_FMT_YVYU8_2X8, V4L2_PIX_FMT_YVYU, 1,
	  अणु अणु 1, 1 पूर्ण पूर्ण, अणु अणु 1, 1 पूर्ण पूर्ण, अणु 16 पूर्ण पूर्ण,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Helper functions
 */

अटल पूर्णांक video_find_क्रमmat(u32 code, u32 pixelक्रमmat,
			     स्थिर काष्ठा camss_क्रमmat_info *क्रमmats,
			     अचिन्हित पूर्णांक nक्रमmats)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nक्रमmats; i++) अणु
		अगर (क्रमmats[i].code == code &&
		    क्रमmats[i].pixelक्रमmat == pixelक्रमmat)
			वापस i;
	पूर्ण

	क्रम (i = 0; i < nक्रमmats; i++)
		अगर (क्रमmats[i].code == code)
			वापस i;

	WARN_ON(1);

	वापस -EINVAL;
पूर्ण

/*
 * video_mbus_to_pix_mp - Convert v4l2_mbus_framefmt to v4l2_pix_क्रमmat_mplane
 * @mbus: v4l2_mbus_framefmt क्रमmat (input)
 * @pix: v4l2_pix_क्रमmat_mplane क्रमmat (output)
 * @f: a poपूर्णांकer to क्रमmats array element to be used क्रम the conversion
 * @alignment: bytesperline alignment value
 *
 * Fill the output pix काष्ठाure with inक्रमmation from the input mbus क्रमmat.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक video_mbus_to_pix_mp(स्थिर काष्ठा v4l2_mbus_framefmt *mbus,
				काष्ठा v4l2_pix_क्रमmat_mplane *pix,
				स्थिर काष्ठा camss_क्रमmat_info *f,
				अचिन्हित पूर्णांक alignment)
अणु
	अचिन्हित पूर्णांक i;
	u32 bytesperline;

	स_रखो(pix, 0, माप(*pix));
	v4l2_fill_pix_क्रमmat_mplane(pix, mbus);
	pix->pixelक्रमmat = f->pixelक्रमmat;
	pix->num_planes = f->planes;
	क्रम (i = 0; i < pix->num_planes; i++) अणु
		bytesperline = pix->width / f->hsub[i].numerator *
			f->hsub[i].denominator * f->bpp[i] / 8;
		bytesperline = ALIGN(bytesperline, alignment);
		pix->plane_fmt[i].bytesperline = bytesperline;
		pix->plane_fmt[i].sizeimage = pix->height /
				f->vsub[i].numerator * f->vsub[i].denominator *
				bytesperline;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_subdev *video_remote_subdev(काष्ठा camss_video *video,
					       u32 *pad)
अणु
	काष्ठा media_pad *remote;

	remote = media_entity_remote_pad(&video->pad);

	अगर (!remote || !is_media_entity_v4l2_subdev(remote->entity))
		वापस शून्य;

	अगर (pad)
		*pad = remote->index;

	वापस media_entity_to_v4l2_subdev(remote->entity);
पूर्ण

अटल पूर्णांक video_get_subdev_क्रमmat(काष्ठा camss_video *video,
				   काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt;
	काष्ठा v4l2_subdev *subdev;
	u32 pad;
	पूर्णांक ret;

	subdev = video_remote_subdev(video, &pad);
	अगर (subdev == शून्य)
		वापस -EPIPE;

	fmt.pad = pad;
	fmt.which = V4L2_SUBDEV_FORMAT_ACTIVE;

	ret = v4l2_subdev_call(subdev, pad, get_fmt, शून्य, &fmt);
	अगर (ret)
		वापस ret;

	ret = video_find_क्रमmat(fmt.क्रमmat.code,
				क्रमmat->fmt.pix_mp.pixelक्रमmat,
				video->क्रमmats, video->nक्रमmats);
	अगर (ret < 0)
		वापस ret;

	क्रमmat->type = video->type;

	वापस video_mbus_to_pix_mp(&fmt.क्रमmat, &क्रमmat->fmt.pix_mp,
				    &video->क्रमmats[ret], video->bpl_alignment);
पूर्ण

/* -----------------------------------------------------------------------------
 * Video queue operations
 */

अटल पूर्णांक video_queue_setup(काष्ठा vb2_queue *q,
	अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
	अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा camss_video *video = vb2_get_drv_priv(q);
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat =
						&video->active_fmt.fmt.pix_mp;
	अचिन्हित पूर्णांक i;

	अगर (*num_planes) अणु
		अगर (*num_planes != क्रमmat->num_planes)
			वापस -EINVAL;

		क्रम (i = 0; i < *num_planes; i++)
			अगर (sizes[i] < क्रमmat->plane_fmt[i].sizeimage)
				वापस -EINVAL;

		वापस 0;
	पूर्ण

	*num_planes = क्रमmat->num_planes;

	क्रम (i = 0; i < *num_planes; i++)
		sizes[i] = क्रमmat->plane_fmt[i].sizeimage;

	वापस 0;
पूर्ण

अटल पूर्णांक video_buf_init(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा camss_video *video = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा camss_buffer *buffer = container_of(vbuf, काष्ठा camss_buffer,
						   vb);
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat =
						&video->active_fmt.fmt.pix_mp;
	काष्ठा sg_table *sgt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < क्रमmat->num_planes; i++) अणु
		sgt = vb2_dma_sg_plane_desc(vb, i);
		अगर (!sgt)
			वापस -EFAULT;

		buffer->addr[i] = sg_dma_address(sgt->sgl);
	पूर्ण

	अगर (क्रमmat->pixelक्रमmat == V4L2_PIX_FMT_NV12 ||
			क्रमmat->pixelक्रमmat == V4L2_PIX_FMT_NV21 ||
			क्रमmat->pixelक्रमmat == V4L2_PIX_FMT_NV16 ||
			क्रमmat->pixelक्रमmat == V4L2_PIX_FMT_NV61)
		buffer->addr[1] = buffer->addr[0] +
				क्रमmat->plane_fmt[0].bytesperline *
				क्रमmat->height;

	वापस 0;
पूर्ण

अटल पूर्णांक video_buf_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा camss_video *video = vb2_get_drv_priv(vb->vb2_queue);
	स्थिर काष्ठा v4l2_pix_क्रमmat_mplane *क्रमmat =
						&video->active_fmt.fmt.pix_mp;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < क्रमmat->num_planes; i++) अणु
		अगर (क्रमmat->plane_fmt[i].sizeimage > vb2_plane_size(vb, i))
			वापस -EINVAL;

		vb2_set_plane_payload(vb, i, क्रमmat->plane_fmt[i].sizeimage);
	पूर्ण

	vbuf->field = V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल व्योम video_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा camss_video *video = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा camss_buffer *buffer = container_of(vbuf, काष्ठा camss_buffer,
						   vb);

	video->ops->queue_buffer(video, buffer);
पूर्ण

अटल पूर्णांक video_check_क्रमmat(काष्ठा camss_video *video)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix = &video->active_fmt.fmt.pix_mp;
	काष्ठा v4l2_क्रमmat क्रमmat;
	काष्ठा v4l2_pix_क्रमmat_mplane *sd_pix = &क्रमmat.fmt.pix_mp;
	पूर्णांक ret;

	sd_pix->pixelक्रमmat = pix->pixelक्रमmat;
	ret = video_get_subdev_क्रमmat(video, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	अगर (pix->pixelक्रमmat != sd_pix->pixelक्रमmat ||
	    pix->height != sd_pix->height ||
	    pix->width != sd_pix->width ||
	    pix->num_planes != sd_pix->num_planes ||
	    pix->field != क्रमmat.fmt.pix_mp.field)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल पूर्णांक video_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा camss_video *video = vb2_get_drv_priv(q);
	काष्ठा video_device *vdev = &video->vdev;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;
	पूर्णांक ret;

	ret = media_pipeline_start(&vdev->entity, &video->pipe);
	अगर (ret < 0)
		वापस ret;

	ret = video_check_क्रमmat(video);
	अगर (ret < 0)
		जाओ error;

	entity = &vdev->entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		ret = v4l2_subdev_call(subdev, video, s_stream, 1);
		अगर (ret < 0 && ret != -ENOIOCTLCMD)
			जाओ error;
	पूर्ण

	वापस 0;

error:
	media_pipeline_stop(&vdev->entity);

	video->ops->flush_buffers(video, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

अटल व्योम video_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा camss_video *video = vb2_get_drv_priv(q);
	काष्ठा video_device *vdev = &video->vdev;
	काष्ठा media_entity *entity;
	काष्ठा media_pad *pad;
	काष्ठा v4l2_subdev *subdev;

	entity = &vdev->entity;
	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			अवरोध;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		entity = pad->entity;
		subdev = media_entity_to_v4l2_subdev(entity);

		v4l2_subdev_call(subdev, video, s_stream, 0);
	पूर्ण

	media_pipeline_stop(&vdev->entity);

	video->ops->flush_buffers(video, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops msm_video_vb2_q_ops = अणु
	.queue_setup     = video_queue_setup,
	.रुको_prepare    = vb2_ops_रुको_prepare,
	.रुको_finish     = vb2_ops_रुको_finish,
	.buf_init        = video_buf_init,
	.buf_prepare     = video_buf_prepare,
	.buf_queue       = video_buf_queue,
	.start_streaming = video_start_streaming,
	.stop_streaming  = video_stop_streaming,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 ioctls
 */

अटल पूर्णांक video_querycap(काष्ठा file *file, व्योम *fh,
			  काष्ठा v4l2_capability *cap)
अणु
	काष्ठा camss_video *video = video_drvdata(file);

	strscpy(cap->driver, "qcom-camss", माप(cap->driver));
	strscpy(cap->card, "Qualcomm Camera Subsystem", माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "platform:%s",
		 dev_name(video->camss->dev));

	वापस 0;
पूर्ण

अटल पूर्णांक video_क्रमागत_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा camss_video *video = video_drvdata(file);
	पूर्णांक i, j, k;
	u32 mcode = f->mbus_code;

	अगर (f->type != video->type)
		वापस -EINVAL;

	अगर (f->index >= video->nक्रमmats)
		वापस -EINVAL;

	/*
	 * Find index "i" of "k"th unique pixelक्रमmat in क्रमmats array.
	 *
	 * If f->mbus_code passed to video_क्रमागत_fmt() is not zero, a device
	 * with V4L2_CAP_IO_MC capability restricts क्रमागतeration to only the
	 * pixel क्रमmats that can be produced from that media bus code.
	 * This is implemented by skipping video->क्रमmats[] entries with
	 * code != f->mbus_code (अगर f->mbus_code is not zero).
	 * If the f->mbus_code passed to video_क्रमागत_fmt() is not supported,
	 * -EINVAL is वापसed.
	 * If f->mbus_code is zero, all the pixel क्रमmats are क्रमागतerated.
	 */
	k = -1;
	क्रम (i = 0; i < video->nक्रमmats; i++) अणु
		अगर (mcode != 0 && video->क्रमmats[i].code != mcode)
			जारी;

		क्रम (j = 0; j < i; j++) अणु
			अगर (mcode != 0 && video->क्रमmats[j].code != mcode)
				जारी;
			अगर (video->क्रमmats[i].pixelक्रमmat ==
					video->क्रमmats[j].pixelक्रमmat)
				अवरोध;
		पूर्ण

		अगर (j == i)
			k++;

		अगर (k == f->index)
			अवरोध;
	पूर्ण

	अगर (k == -1 || k < f->index)
		/*
		 * All the unique pixel क्रमmats matching the arguments
		 * have been क्रमागतerated (k >= 0 and f->index > 0), or
		 * no pixel क्रमmats match the non-zero f->mbus_code (k == -1).
		 */
		वापस -EINVAL;

	f->pixelक्रमmat = video->क्रमmats[i].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक video_क्रमागत_framesizes(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा camss_video *video = video_drvdata(file);
	पूर्णांक i;

	अगर (fsize->index)
		वापस -EINVAL;

	/* Only accept pixel क्रमmat present in the क्रमmats[] table */
	क्रम (i = 0; i < video->nक्रमmats; i++) अणु
		अगर (video->क्रमmats[i].pixelक्रमmat == fsize->pixel_क्रमmat)
			अवरोध;
	पूर्ण

	अगर (i == video->nक्रमmats)
		वापस -EINVAL;

	fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = CAMSS_FRAME_MIN_WIDTH;
	fsize->stepwise.max_width = CAMSS_FRAME_MAX_WIDTH;
	fsize->stepwise.min_height = CAMSS_FRAME_MIN_HEIGHT;
	fsize->stepwise.max_height = (video->line_based) ?
		CAMSS_FRAME_MAX_HEIGHT_PIX : CAMSS_FRAME_MAX_HEIGHT_RDI;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक video_g_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camss_video *video = video_drvdata(file);

	*f = video->active_fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक __video_try_fmt(काष्ठा camss_video *video, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा v4l2_pix_क्रमmat_mplane *pix_mp;
	स्थिर काष्ठा camss_क्रमmat_info *fi;
	काष्ठा v4l2_plane_pix_क्रमmat *p;
	u32 bytesperline[3] = अणु 0 पूर्ण;
	u32 sizeimage[3] = अणु 0 पूर्ण;
	u32 width, height;
	u32 bpl, lines;
	पूर्णांक i, j;

	pix_mp = &f->fmt.pix_mp;

	अगर (video->line_based)
		क्रम (i = 0; i < pix_mp->num_planes && i < 3; i++) अणु
			p = &pix_mp->plane_fmt[i];
			bytesperline[i] = clamp_t(u32, p->bytesperline,
						  1, 65528);
			sizeimage[i] = clamp_t(u32, p->sizeimage,
					       bytesperline[i],
					       bytesperline[i] * CAMSS_FRAME_MAX_HEIGHT_PIX);
		पूर्ण

	क्रम (j = 0; j < video->nक्रमmats; j++)
		अगर (pix_mp->pixelक्रमmat == video->क्रमmats[j].pixelक्रमmat)
			अवरोध;

	अगर (j == video->nक्रमmats)
		j = 0; /* शेष क्रमmat */

	fi = &video->क्रमmats[j];
	width = pix_mp->width;
	height = pix_mp->height;

	स_रखो(pix_mp, 0, माप(*pix_mp));

	pix_mp->pixelक्रमmat = fi->pixelक्रमmat;
	pix_mp->width = clamp_t(u32, width, 1, CAMSS_FRAME_MAX_WIDTH);
	pix_mp->height = clamp_t(u32, height, 1, CAMSS_FRAME_MAX_HEIGHT_RDI);
	pix_mp->num_planes = fi->planes;
	क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
		bpl = pix_mp->width / fi->hsub[i].numerator *
			fi->hsub[i].denominator * fi->bpp[i] / 8;
		bpl = ALIGN(bpl, video->bpl_alignment);
		pix_mp->plane_fmt[i].bytesperline = bpl;
		pix_mp->plane_fmt[i].sizeimage = pix_mp->height /
			fi->vsub[i].numerator * fi->vsub[i].denominator * bpl;
	पूर्ण

	pix_mp->field = V4L2_FIELD_NONE;
	pix_mp->colorspace = V4L2_COLORSPACE_SRGB;
	pix_mp->flags = 0;
	pix_mp->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(pix_mp->colorspace);
	pix_mp->quantization = V4L2_MAP_QUANTIZATION_DEFAULT(true,
					pix_mp->colorspace, pix_mp->ycbcr_enc);
	pix_mp->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(pix_mp->colorspace);

	अगर (video->line_based)
		क्रम (i = 0; i < pix_mp->num_planes; i++) अणु
			p = &pix_mp->plane_fmt[i];
			p->bytesperline = clamp_t(u32, p->bytesperline,
						  1, 65528);
			p->sizeimage = clamp_t(u32, p->sizeimage,
					       p->bytesperline,
					       p->bytesperline * CAMSS_FRAME_MAX_HEIGHT_PIX);
			lines = p->sizeimage / p->bytesperline;

			अगर (p->bytesperline < bytesperline[i])
				p->bytesperline = ALIGN(bytesperline[i], 8);

			अगर (p->sizeimage < p->bytesperline * lines)
				p->sizeimage = p->bytesperline * lines;

			अगर (p->sizeimage < sizeimage[i])
				p->sizeimage = sizeimage[i];
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक video_try_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camss_video *video = video_drvdata(file);

	वापस __video_try_fmt(video, f);
पूर्ण

अटल पूर्णांक video_s_fmt(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा camss_video *video = video_drvdata(file);
	पूर्णांक ret;

	अगर (vb2_is_busy(&video->vb2_q))
		वापस -EBUSY;

	ret = __video_try_fmt(video, f);
	अगर (ret < 0)
		वापस ret;

	video->active_fmt = *f;

	वापस 0;
पूर्ण

अटल पूर्णांक video_क्रमागत_input(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_input *input)
अणु
	अगर (input->index > 0)
		वापस -EINVAL;

	strscpy(input->name, "camera", माप(input->name));
	input->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक video_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *input)
अणु
	*input = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक video_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक input)
अणु
	वापस input == 0 ? 0 : -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops msm_vid_ioctl_ops = अणु
	.vidioc_querycap		= video_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= video_क्रमागत_fmt,
	.vidioc_क्रमागत_framesizes		= video_क्रमागत_framesizes,
	.vidioc_g_fmt_vid_cap_mplane	= video_g_fmt,
	.vidioc_s_fmt_vid_cap_mplane	= video_s_fmt,
	.vidioc_try_fmt_vid_cap_mplane	= video_try_fmt,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_create_bufs		= vb2_ioctl_create_bufs,
	.vidioc_prepare_buf		= vb2_ioctl_prepare_buf,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_क्रमागत_input		= video_क्रमागत_input,
	.vidioc_g_input			= video_g_input,
	.vidioc_s_input			= video_s_input,
पूर्ण;

/* -----------------------------------------------------------------------------
 * V4L2 file operations
 */

अटल पूर्णांक video_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा camss_video *video = video_drvdata(file);
	काष्ठा v4l2_fh *vfh;
	पूर्णांक ret;

	mutex_lock(&video->lock);

	vfh = kzalloc(माप(*vfh), GFP_KERNEL);
	अगर (vfh == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_alloc;
	पूर्ण

	v4l2_fh_init(vfh, vdev);
	v4l2_fh_add(vfh);

	file->निजी_data = vfh;

	ret = v4l2_pipeline_pm_get(&vdev->entity);
	अगर (ret < 0) अणु
		dev_err(video->camss->dev, "Failed to power up pipeline: %d\n",
			ret);
		जाओ error_pm_use;
	पूर्ण

	mutex_unlock(&video->lock);

	वापस 0;

error_pm_use:
	v4l2_fh_release(file);

error_alloc:
	mutex_unlock(&video->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक video_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);

	vb2_fop_release(file);

	v4l2_pipeline_pm_put(&vdev->entity);

	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations msm_vid_fops = अणु
	.owner          = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो           = video_खोलो,
	.release        = video_release,
	.poll           = vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.पढ़ो		= vb2_fop_पढ़ो,
पूर्ण;

/* -----------------------------------------------------------------------------
 * CAMSS video core
 */

अटल व्योम msm_video_release(काष्ठा video_device *vdev)
अणु
	काष्ठा camss_video *video = video_get_drvdata(vdev);

	media_entity_cleanup(&vdev->entity);

	mutex_destroy(&video->q_lock);
	mutex_destroy(&video->lock);

	अगर (atomic_dec_and_test(&video->camss->ref_count))
		camss_delete(video->camss);
पूर्ण

/*
 * msm_video_init_क्रमmat - Helper function to initialize क्रमmat
 * @video: काष्ठा camss_video
 *
 * Initialize pad क्रमmat with शेष value.
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक msm_video_init_क्रमmat(काष्ठा camss_video *video)
अणु
	पूर्णांक ret;
	काष्ठा v4l2_क्रमmat क्रमmat = अणु
		.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE,
		.fmt.pix_mp = अणु
			.width = 1920,
			.height = 1080,
			.pixelक्रमmat = video->क्रमmats[0].pixelक्रमmat,
		पूर्ण,
	पूर्ण;

	ret = __video_try_fmt(video, &क्रमmat);
	अगर (ret < 0)
		वापस ret;

	video->active_fmt = क्रमmat;

	वापस 0;
पूर्ण

/*
 * msm_video_रेजिस्टर - Register a video device node
 * @video: काष्ठा camss_video
 * @v4l2_dev: V4L2 device
 * @name: name to be used क्रम the video device node
 *
 * Initialize and रेजिस्टर a video device node to a V4L2 device. Also
 * initialize the vb2 queue.
 *
 * Return 0 on success or a negative error code otherwise
 */

पूर्णांक msm_video_रेजिस्टर(काष्ठा camss_video *video, काष्ठा v4l2_device *v4l2_dev,
		       स्थिर अक्षर *name, पूर्णांक is_pix)
अणु
	काष्ठा media_pad *pad = &video->pad;
	काष्ठा video_device *vdev;
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	vdev = &video->vdev;

	mutex_init(&video->q_lock);

	q = &video->vb2_q;
	q->drv_priv = video;
	q->mem_ops = &vb2_dma_sg_memops;
	q->ops = &msm_video_vb2_q_ops;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_DMABUF | VB2_MMAP | VB2_READ;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->buf_काष्ठा_size = माप(काष्ठा camss_buffer);
	q->dev = video->camss->dev;
	q->lock = &video->q_lock;
	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		dev_err(v4l2_dev->dev, "Failed to init vb2 queue: %d\n", ret);
		जाओ error_vb2_init;
	पूर्ण

	pad->flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vdev->entity, 1, pad);
	अगर (ret < 0) अणु
		dev_err(v4l2_dev->dev, "Failed to init video entity: %d\n",
			ret);
		जाओ error_vb2_init;
	पूर्ण

	mutex_init(&video->lock);

	अगर (video->camss->version == CAMSS_8x16) अणु
		अगर (is_pix) अणु
			video->क्रमmats = क्रमmats_pix_8x16;
			video->nक्रमmats = ARRAY_SIZE(क्रमmats_pix_8x16);
		पूर्ण अन्यथा अणु
			video->क्रमmats = क्रमmats_rdi_8x16;
			video->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_8x16);
		पूर्ण
	पूर्ण अन्यथा अगर (video->camss->version == CAMSS_8x96 ||
		   video->camss->version == CAMSS_660) अणु
		अगर (is_pix) अणु
			video->क्रमmats = क्रमmats_pix_8x96;
			video->nक्रमmats = ARRAY_SIZE(क्रमmats_pix_8x96);
		पूर्ण अन्यथा अणु
			video->क्रमmats = क्रमmats_rdi_8x96;
			video->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_8x96);
		पूर्ण
	पूर्ण  अन्यथा अगर (video->camss->version == CAMSS_845) अणु
		video->क्रमmats = क्रमmats_rdi_845;
		video->nक्रमmats = ARRAY_SIZE(क्रमmats_rdi_845);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ error_video_रेजिस्टर;
	पूर्ण

	ret = msm_video_init_क्रमmat(video);
	अगर (ret < 0) अणु
		dev_err(v4l2_dev->dev, "Failed to init format: %d\n", ret);
		जाओ error_video_रेजिस्टर;
	पूर्ण

	vdev->fops = &msm_vid_fops;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING
			  | V4L2_CAP_READWRITE | V4L2_CAP_IO_MC;
	vdev->ioctl_ops = &msm_vid_ioctl_ops;
	vdev->release = msm_video_release;
	vdev->v4l2_dev = v4l2_dev;
	vdev->vfl_dir = VFL_सूची_RX;
	vdev->queue = &video->vb2_q;
	vdev->lock = &video->lock;
	strscpy(vdev->name, name, माप(vdev->name));

	ret = video_रेजिस्टर_device(vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_err(v4l2_dev->dev, "Failed to register video device: %d\n",
			ret);
		जाओ error_video_रेजिस्टर;
	पूर्ण

	video_set_drvdata(vdev, video);
	atomic_inc(&video->camss->ref_count);

	वापस 0;

error_video_रेजिस्टर:
	media_entity_cleanup(&vdev->entity);
	mutex_destroy(&video->lock);
error_vb2_init:
	mutex_destroy(&video->q_lock);

	वापस ret;
पूर्ण

व्योम msm_video_unरेजिस्टर(काष्ठा camss_video *video)
अणु
	atomic_inc(&video->camss->ref_count);
	vb2_video_unरेजिस्टर_device(&video->vdev);
	atomic_dec(&video->camss->ref_count);
पूर्ण
