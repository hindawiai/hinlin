<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Allwinner DE2 rotation driver
 *
 * Copyright (C) 2020 Jernej Skrabec <jernej.skrabec@siol.net>
 */

#अगर_अघोषित _SUN8I_ROTATE_H_
#घोषणा _SUN8I_ROTATE_H_

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश <linux/platक्रमm_device.h>

#घोषणा ROTATE_NAME		"sun8i-rotate"

#घोषणा ROTATE_GLB_CTL			0x00
#घोषणा ROTATE_GLB_CTL_START			BIT(31)
#घोषणा ROTATE_GLB_CTL_RESET			BIT(30)
#घोषणा ROTATE_GLB_CTL_BURST_LEN(x)		((x) << 16)
#घोषणा ROTATE_GLB_CTL_HFLIP			BIT(7)
#घोषणा ROTATE_GLB_CTL_VFLIP			BIT(6)
#घोषणा ROTATE_GLB_CTL_ROTATION(x)		((x) << 4)
#घोषणा ROTATE_GLB_CTL_MODE(x)			((x) << 0)

#घोषणा ROTATE_INT			0x04
#घोषणा ROTATE_INT_FINISH_IRQ_EN		BIT(16)
#घोषणा ROTATE_INT_FINISH_IRQ			BIT(0)

#घोषणा ROTATE_IN_FMT			0x20
#घोषणा ROTATE_IN_FMT_FORMAT(x)			((x) << 0)

#घोषणा ROTATE_IN_SIZE			0x24
#घोषणा ROTATE_IN_PITCH0		0x30
#घोषणा ROTATE_IN_PITCH1		0x34
#घोषणा ROTATE_IN_PITCH2		0x38
#घोषणा ROTATE_IN_ADDRL0		0x40
#घोषणा ROTATE_IN_ADDRH0		0x44
#घोषणा ROTATE_IN_ADDRL1		0x48
#घोषणा ROTATE_IN_ADDRH1		0x4c
#घोषणा ROTATE_IN_ADDRL2		0x50
#घोषणा ROTATE_IN_ADDRH2		0x54
#घोषणा ROTATE_OUT_SIZE			0x84
#घोषणा ROTATE_OUT_PITCH0		0x90
#घोषणा ROTATE_OUT_PITCH1		0x94
#घोषणा ROTATE_OUT_PITCH2		0x98
#घोषणा ROTATE_OUT_ADDRL0		0xA0
#घोषणा ROTATE_OUT_ADDRH0		0xA4
#घोषणा ROTATE_OUT_ADDRL1		0xA8
#घोषणा ROTATE_OUT_ADDRH1		0xAC
#घोषणा ROTATE_OUT_ADDRL2		0xB0
#घोषणा ROTATE_OUT_ADDRH2		0xB4

#घोषणा ROTATE_BURST_8			0x07
#घोषणा ROTATE_BURST_16			0x0f
#घोषणा ROTATE_BURST_32			0x1f
#घोषणा ROTATE_BURST_64			0x3f

#घोषणा ROTATE_MODE_COPY_ROTATE		0x01

#घोषणा ROTATE_FORMAT_ARGB32		0x00
#घोषणा ROTATE_FORMAT_ABGR32		0x01
#घोषणा ROTATE_FORMAT_RGBA32		0x02
#घोषणा ROTATE_FORMAT_BGRA32		0x03
#घोषणा ROTATE_FORMAT_XRGB32		0x04
#घोषणा ROTATE_FORMAT_XBGR32		0x05
#घोषणा ROTATE_FORMAT_RGBX32		0x06
#घोषणा ROTATE_FORMAT_BGRX32		0x07
#घोषणा ROTATE_FORMAT_RGB24		0x08
#घोषणा ROTATE_FORMAT_BGR24		0x09
#घोषणा ROTATE_FORMAT_RGB565		0x0a
#घोषणा ROTATE_FORMAT_BGR565		0x0b
#घोषणा ROTATE_FORMAT_ARGB4444		0x0c
#घोषणा ROTATE_FORMAT_ABGR4444		0x0d
#घोषणा ROTATE_FORMAT_RGBA4444		0x0e
#घोषणा ROTATE_FORMAT_BGRA4444		0x0f
#घोषणा ROTATE_FORMAT_ARGB1555		0x10
#घोषणा ROTATE_FORMAT_ABGR1555		0x11
#घोषणा ROTATE_FORMAT_RGBA5551		0x12
#घोषणा ROTATE_FORMAT_BGRA5551		0x13

#घोषणा ROTATE_FORMAT_YUYV		0x20
#घोषणा ROTATE_FORMAT_UYVY		0x21
#घोषणा ROTATE_FORMAT_YVYU		0x22
#घोषणा ROTATE_FORMAT_VYUV		0x23
#घोषणा ROTATE_FORMAT_NV61		0x24
#घोषणा ROTATE_FORMAT_NV16		0x25
#घोषणा ROTATE_FORMAT_YUV422P		0x26
#घोषणा ROTATE_FORMAT_NV21		0x28
#घोषणा ROTATE_FORMAT_NV12		0x29
#घोषणा ROTATE_FORMAT_YUV420P		0x2A

#घोषणा ROTATE_SIZE(w, h)	(((h) - 1) << 16 | ((w) - 1))

#घोषणा ROTATE_MIN_WIDTH	8U
#घोषणा ROTATE_MIN_HEIGHT	8U
#घोषणा ROTATE_MAX_WIDTH	4096U
#घोषणा ROTATE_MAX_HEIGHT	4096U

काष्ठा rotate_ctx अणु
	काष्ठा v4l2_fh		fh;
	काष्ठा rotate_dev	*dev;

	काष्ठा v4l2_pix_क्रमmat	src_fmt;
	काष्ठा v4l2_pix_क्रमmat	dst_fmt;

	काष्ठा v4l2_ctrl_handler ctrl_handler;

	u32 hflip;
	u32 vflip;
	u32 rotate;
पूर्ण;

काष्ठा rotate_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd;
	काष्ठा device		*dev;
	काष्ठा v4l2_m2m_dev	*m2m_dev;

	/* Device file mutex */
	काष्ठा mutex		dev_mutex;

	व्योम __iomem		*base;

	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;

	काष्ठा reset_control	*rstc;
पूर्ण;

#पूर्ण_अगर
