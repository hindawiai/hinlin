<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित FIMC_LITE_H_
#घोषणा FIMC_LITE_H_

#समावेश <linux/sizes.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>

#घोषणा FIMC_LITE_DRV_NAME	"exynos-fimc-lite"
#घोषणा FLITE_CLK_NAME		"flite"
#घोषणा FIMC_LITE_MAX_DEVS	3
#घोषणा FLITE_REQ_BUFS_MIN	2
#घोषणा FLITE_DEFAULT_WIDTH	640
#घोषणा FLITE_DEFAULT_HEIGHT	480

/* Bit index definitions क्रम काष्ठा fimc_lite::state */
क्रमागत अणु
	ST_FLITE_LPM,
	ST_FLITE_PENDING,
	ST_FLITE_RUN,
	ST_FLITE_STREAM,
	ST_FLITE_SUSPENDED,
	ST_FLITE_OFF,
	ST_FLITE_IN_USE,
	ST_FLITE_CONFIG,
	ST_SENSOR_STREAM,
पूर्ण;

#घोषणा FLITE_SD_PAD_SINK	0
#घोषणा FLITE_SD_PAD_SOURCE_DMA	1
#घोषणा FLITE_SD_PAD_SOURCE_ISP	2
#घोषणा FLITE_SD_PADS_NUM	3

/**
 * काष्ठा flite_drvdata - FIMC-LITE IP variant data काष्ठाure
 * @max_width: maximum camera पूर्णांकerface input width in pixels
 * @max_height: maximum camera पूर्णांकerface input height in pixels
 * @out_width_align: minimum output width alignment in pixels
 * @win_hor_offs_align: minimum camera पूर्णांकerface crop winकरोw horizontal
 *			offset alignment in pixels
 * @out_hor_offs_align: minimum output DMA compose rectangle horizontal
 *			offset alignment in pixels
 * @max_dma_bufs: number of output DMA buffer start address रेजिस्टरs
 * @num_instances: total number of FIMC-LITE IP instances available
 */
काष्ठा flite_drvdata अणु
	अचिन्हित लघु max_width;
	अचिन्हित लघु max_height;
	अचिन्हित लघु out_width_align;
	अचिन्हित लघु win_hor_offs_align;
	अचिन्हित लघु out_hor_offs_align;
	अचिन्हित लघु max_dma_bufs;
	अचिन्हित लघु num_instances;
पूर्ण;

काष्ठा fimc_lite_events अणु
	अचिन्हित पूर्णांक data_overflow;
पूर्ण;

#घोषणा FLITE_MAX_PLANES	1

/**
 * काष्ठा flite_frame - source/target frame properties
 * @f_width: full pixel width
 * @f_height: full pixel height
 * @rect: crop/composition rectangle
 * @fmt: poपूर्णांकer to pixel क्रमmat description data काष्ठाure
 */
काष्ठा flite_frame अणु
	u16 f_width;
	u16 f_height;
	काष्ठा v4l2_rect rect;
	स्थिर काष्ठा fimc_fmt *fmt;
पूर्ण;

/**
 * काष्ठा flite_buffer - video buffer काष्ठाure
 * @vb:    vb2 buffer
 * @list:  list head क्रम the buffers queue
 * @addr: DMA buffer start address
 * @index: DMA start address रेजिस्टर's index
 */
काष्ठा flite_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	dma_addr_t addr;
	अचिन्हित लघु index;
पूर्ण;

/**
 * काष्ठा fimc_lite - fimc lite काष्ठाure
 * @pdev: poपूर्णांकer to FIMC-LITE platक्रमm device
 * @dd: SoC specअगरic driver data काष्ठाure
 * @ve: exynos video device entity काष्ठाure
 * @v4l2_dev: poपूर्णांकer to top the level v4l2_device
 * @fh: v4l2 file handle
 * @subdev: FIMC-LITE subdev
 * @vd_pad: media (sink) pad क्रम the capture video node
 * @subdev_pads: the subdev media pads
 * @sensor: sensor subdev attached to FIMC-LITE directly or through MIPI-CSIS
 * @ctrl_handler: v4l2 control handler
 * @test_pattern: test pattern controls
 * @index: FIMC-LITE platक्रमm device index
 * @pipeline: video capture pipeline data काष्ठाure
 * @pipeline_ops: media pipeline ops क्रम the video node driver
 * @slock: spinlock protecting this data काष्ठाure and the hw रेजिस्टरs
 * @lock: mutex serializing video device and the subdev operations
 * @घड़ी: FIMC-LITE gate घड़ी
 * @regs: memory mapped io रेजिस्टरs
 * @irq_queue: पूर्णांकerrupt handler रुकोqueue
 * @payload: image size in bytes (w x h x bpp)
 * @inp_frame: camera input frame काष्ठाure
 * @out_frame: DMA output frame काष्ठाure
 * @out_path: output data path (DMA or FIFO)
 * @source_subdev_grp_id: source subdev group id
 * @state: driver state flags
 * @pending_buf_q: pending buffers queue head
 * @active_buf_q: the queue head of buffers scheduled in hardware
 * @vb_queue: vb2 buffers queue
 * @buf_index: helps to keep track of the DMA start address रेजिस्टर index
 * @active_buf_count: number of video buffers scheduled in hardware
 * @frame_count: the captured frames counter
 * @reqbufs_count: the number of buffers requested with REQBUFS ioctl
 * @events: event info
 * @streaming: is streaming in progress?
 */
काष्ठा fimc_lite अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा flite_drvdata	*dd;
	काष्ठा exynos_video_entity ve;
	काष्ठा v4l2_device	*v4l2_dev;
	काष्ठा v4l2_fh		fh;
	काष्ठा v4l2_subdev	subdev;
	काष्ठा media_pad	vd_pad;
	काष्ठा media_pad	subdev_pads[FLITE_SD_PADS_NUM];
	काष्ठा v4l2_subdev	*sensor;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl	*test_pattern;
	पूर्णांक			index;

	काष्ठा mutex		lock;
	spinlock_t		slock;

	काष्ठा clk		*घड़ी;
	व्योम __iomem		*regs;
	रुको_queue_head_t	irq_queue;

	अचिन्हित दीर्घ		payload[FLITE_MAX_PLANES];
	काष्ठा flite_frame	inp_frame;
	काष्ठा flite_frame	out_frame;
	atomic_t		out_path;
	अचिन्हित पूर्णांक		source_subdev_grp_id;

	अचिन्हित दीर्घ		state;
	काष्ठा list_head	pending_buf_q;
	काष्ठा list_head	active_buf_q;
	काष्ठा vb2_queue	vb_queue;
	अचिन्हित लघु		buf_index;
	अचिन्हित पूर्णांक		frame_count;
	अचिन्हित पूर्णांक		reqbufs_count;

	काष्ठा fimc_lite_events	events;
	bool			streaming;
पूर्ण;

अटल अंतरभूत bool fimc_lite_active(काष्ठा fimc_lite *fimc)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&fimc->slock, flags);
	ret = fimc->state & (1 << ST_FLITE_RUN) ||
		fimc->state & (1 << ST_FLITE_PENDING);
	spin_unlock_irqrestore(&fimc->slock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम fimc_lite_active_queue_add(काष्ठा fimc_lite *dev,
					 काष्ठा flite_buffer *buf)
अणु
	list_add_tail(&buf->list, &dev->active_buf_q);
पूर्ण

अटल अंतरभूत काष्ठा flite_buffer *fimc_lite_active_queue_pop(
					काष्ठा fimc_lite *dev)
अणु
	काष्ठा flite_buffer *buf = list_entry(dev->active_buf_q.next,
					      काष्ठा flite_buffer, list);
	list_del(&buf->list);
	वापस buf;
पूर्ण

अटल अंतरभूत व्योम fimc_lite_pending_queue_add(काष्ठा fimc_lite *dev,
					काष्ठा flite_buffer *buf)
अणु
	list_add_tail(&buf->list, &dev->pending_buf_q);
पूर्ण

अटल अंतरभूत काष्ठा flite_buffer *fimc_lite_pending_queue_pop(
					काष्ठा fimc_lite *dev)
अणु
	काष्ठा flite_buffer *buf = list_entry(dev->pending_buf_q.next,
					      काष्ठा flite_buffer, list);
	list_del(&buf->list);
	वापस buf;
पूर्ण

#पूर्ण_अगर /* FIMC_LITE_H_ */
