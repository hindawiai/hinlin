<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Sylwester Nawrocki <s.nawrocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#अगर_अघोषित FIMC_ISP_H_
#घोषणा FIMC_ISP_H_

#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

बाह्य पूर्णांक fimc_isp_debug;

#घोषणा isp_dbg(level, dev, fmt, arg...) \
	v4l2_dbg(level, fimc_isp_debug, dev, fmt, ## arg)

/* FIXME: revisit these स्थिरraपूर्णांकs */
#घोषणा FIMC_ISP_SINK_WIDTH_MIN		(16 + 8)
#घोषणा FIMC_ISP_SINK_HEIGHT_MIN	(12 + 8)
#घोषणा FIMC_ISP_SOURCE_WIDTH_MIN	8
#घोषणा FIMC_ISP_SOURCE_HEIGHT_MIN	8
#घोषणा FIMC_ISP_CAC_MARGIN_WIDTH	16
#घोषणा FIMC_ISP_CAC_MARGIN_HEIGHT	12

#घोषणा FIMC_ISP_SINK_WIDTH_MAX		(4000 - 16)
#घोषणा FIMC_ISP_SINK_HEIGHT_MAX	(4000 + 12)
#घोषणा FIMC_ISP_SOURCE_WIDTH_MAX	4000
#घोषणा FIMC_ISP_SOURCE_HEIGHT_MAX	4000

#घोषणा FIMC_ISP_NUM_FORMATS		3
#घोषणा FIMC_ISP_REQ_BUFS_MIN		2
#घोषणा FIMC_ISP_REQ_BUFS_MAX		32

#घोषणा FIMC_ISP_SD_PAD_SINK		0
#घोषणा FIMC_ISP_SD_PAD_SRC_FIFO	1
#घोषणा FIMC_ISP_SD_PAD_SRC_DMA		2
#घोषणा FIMC_ISP_SD_PADS_NUM		3
#घोषणा FIMC_ISP_MAX_PLANES		1

/**
 * काष्ठा fimc_isp_frame - source/target frame properties
 * @width: full image width
 * @height: full image height
 * @rect: crop/composition rectangle
 */
काष्ठा fimc_isp_frame अणु
	u16 width;
	u16 height;
	काष्ठा v4l2_rect rect;
पूर्ण;

काष्ठा fimc_isp_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;

	/* Auto white balance */
	काष्ठा v4l2_ctrl *स्वतः_wb;
	/* Auto ISO control cluster */
	काष्ठा अणु
		काष्ठा v4l2_ctrl *स्वतः_iso;
		काष्ठा v4l2_ctrl *iso;
	पूर्ण;
	/* Adjust - contrast */
	काष्ठा v4l2_ctrl *contrast;
	/* Adjust - saturation */
	काष्ठा v4l2_ctrl *saturation;
	/* Adjust - sharpness */
	काष्ठा v4l2_ctrl *sharpness;
	/* Adjust - brightness */
	काष्ठा v4l2_ctrl *brightness;
	/* Adjust - hue */
	काष्ठा v4l2_ctrl *hue;

	/* Auto/manual exposure */
	काष्ठा v4l2_ctrl *स्वतः_exp;
	/* Manual exposure value */
	काष्ठा v4l2_ctrl *exposure;
	/* AE/AWB lock/unlock */
	काष्ठा v4l2_ctrl *aewb_lock;
	/* Exposure metering mode */
	काष्ठा v4l2_ctrl *exp_metering;
	/* AFC */
	काष्ठा v4l2_ctrl *afc;
	/* ISP image effect */
	काष्ठा v4l2_ctrl *colorfx;
पूर्ण;

काष्ठा isp_video_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	dma_addr_t dma_addr[FIMC_ISP_MAX_PLANES];
	अचिन्हित पूर्णांक index;
पूर्ण;

#घोषणा to_isp_video_buf(_b) container_of(_b, काष्ठा isp_video_buf, vb)

#घोषणा FIMC_ISP_MAX_BUFS	4

/**
 * काष्ठा fimc_is_video - fimc-is video device काष्ठाure
 * @ve: video_device काष्ठाure and media pipeline
 * @type: video device type (CAPTURE/OUTPUT)
 * @pad: video device media (sink) pad
 * @pending_buf_q: pending buffers queue head
 * @active_buf_q: a queue head of buffers scheduled in hardware
 * @vb_queue: vb2 buffer queue
 * @reqbufs_count: the number of buffers requested in REQBUFS ioctl
 * @buf_count: number of video buffers scheduled in hardware
 * @buf_mask: biपंचांगask of the queued video buffer indices
 * @frame_count: counter of frames dequeued to user space
 * @streaming: is streaming in progress?
 * @buffers: buffer info
 * @क्रमmat: current fimc pixel क्रमmat
 * @pixfmt: current pixel क्रमmat
 */
काष्ठा fimc_is_video अणु
	काष्ठा exynos_video_entity ve;
	क्रमागत v4l2_buf_type	type;
	काष्ठा media_pad	pad;
	काष्ठा list_head	pending_buf_q;
	काष्ठा list_head	active_buf_q;
	काष्ठा vb2_queue	vb_queue;
	अचिन्हित पूर्णांक		reqbufs_count;
	अचिन्हित पूर्णांक		buf_count;
	अचिन्हित पूर्णांक		buf_mask;
	अचिन्हित पूर्णांक		frame_count;
	पूर्णांक			streaming;
	काष्ठा isp_video_buf	*buffers[FIMC_ISP_MAX_BUFS];
	स्थिर काष्ठा fimc_fmt	*क्रमmat;
	काष्ठा v4l2_pix_क्रमmat_mplane pixfmt;
पूर्ण;

/* काष्ठा fimc_isp:state bit definitions */
#घोषणा ST_ISP_VID_CAP_BUF_PREP		0
#घोषणा ST_ISP_VID_CAP_STREAMING	1

/**
 * काष्ठा fimc_isp - FIMC-IS ISP data काष्ठाure
 * @pdev: poपूर्णांकer to FIMC-IS platक्रमm device
 * @subdev: ISP v4l2_subdev
 * @subdev_pads: the ISP subdev media pads
 * @src_fmt: source mediabus क्रमmat
 * @sink_fmt: sink mediabus क्रमmat
 * @test_pattern: test pattern controls
 * @ctrls: v4l2 controls काष्ठाure
 * @video_lock: mutex serializing video device operations
 * @subdev_lock: mutex serializing subdev operations
 * @cac_margin_x: horizontal CAC margin in pixels
 * @cac_margin_y: vertical CAC margin in pixels
 * @state: driver state flags
 * @video_capture: the ISP block video capture device
 */
काष्ठा fimc_isp अणु
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा v4l2_subdev		subdev;
	काष्ठा media_pad		subdev_pads[FIMC_ISP_SD_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt	src_fmt;
	काष्ठा v4l2_mbus_framefmt	sink_fmt;
	काष्ठा v4l2_ctrl		*test_pattern;
	काष्ठा fimc_isp_ctrls		ctrls;

	काष्ठा mutex			video_lock;
	काष्ठा mutex			subdev_lock;

	अचिन्हित पूर्णांक			cac_margin_x;
	अचिन्हित पूर्णांक			cac_margin_y;

	अचिन्हित दीर्घ			state;

	काष्ठा fimc_is_video		video_capture;
पूर्ण;

#घोषणा ctrl_to_fimc_isp(_ctrl) \
	container_of(ctrl->handler, काष्ठा fimc_isp, ctrls.handler)

काष्ठा fimc_is;

पूर्णांक fimc_isp_subdev_create(काष्ठा fimc_isp *isp);
व्योम fimc_isp_subdev_destroy(काष्ठा fimc_isp *isp);
व्योम fimc_isp_irq_handler(काष्ठा fimc_is *is);
पूर्णांक fimc_is_create_controls(काष्ठा fimc_isp *isp);
पूर्णांक fimc_is_delete_controls(काष्ठा fimc_isp *isp);
स्थिर काष्ठा fimc_fmt *fimc_isp_find_क्रमmat(स्थिर u32 *pixelक्रमmat,
					स्थिर u32 *mbus_code, पूर्णांक index);
#पूर्ण_अगर /* FIMC_ISP_H_ */
