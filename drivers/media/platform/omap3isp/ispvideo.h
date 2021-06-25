<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispvideo.h
 *
 * TI OMAP3 ISP - Generic video node
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_VIDEO_H
#घोषणा OMAP3_ISP_VIDEO_H

#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>

#घोषणा ISP_VIDEO_DRIVER_NAME		"ispvideo"
#घोषणा ISP_VIDEO_DRIVER_VERSION	"0.0.2"

काष्ठा isp_device;
काष्ठा isp_video;
काष्ठा v4l2_mbus_framefmt;
काष्ठा v4l2_pix_क्रमmat;

/*
 * काष्ठा isp_क्रमmat_info - ISP media bus क्रमmat inक्रमmation
 * @code: V4L2 media bus क्रमmat code
 * @truncated: V4L2 media bus क्रमmat code क्रम the same क्रमmat truncated to 10
 *	bits. Identical to @code अगर the क्रमmat is 10 bits wide or less.
 * @uncompressed: V4L2 media bus क्रमmat code क्रम the corresponding uncompressed
 *	क्रमmat. Identical to @code अगर the क्रमmat is not DPCM compressed.
 * @flavor: V4L2 media bus क्रमmat code क्रम the same pixel layout but
 *	shअगरted to be 8 bits per pixel. =0 अगर क्रमmat is not shअगरtable.
 * @pixelक्रमmat: V4L2 pixel क्रमmat FCC identअगरier
 * @width: Bits per pixel (when transferred over a bus)
 * @bpp: Bytes per pixel (when stored in memory)
 */
काष्ठा isp_क्रमmat_info अणु
	u32 code;
	u32 truncated;
	u32 uncompressed;
	u32 flavor;
	u32 pixelक्रमmat;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक bpp;
पूर्ण;

क्रमागत isp_pipeline_stream_state अणु
	ISP_PIPELINE_STREAM_STOPPED = 0,
	ISP_PIPELINE_STREAM_CONTINUOUS = 1,
	ISP_PIPELINE_STREAM_SINGLESHOT = 2,
पूर्ण;

क्रमागत isp_pipeline_state अणु
	/* The stream has been started on the input video node. */
	ISP_PIPELINE_STREAM_INPUT = 1,
	/* The stream has been started on the output video node. */
	ISP_PIPELINE_STREAM_OUTPUT = 2,
	/* At least one buffer is queued on the input video node. */
	ISP_PIPELINE_QUEUE_INPUT = 4,
	/* At least one buffer is queued on the output video node. */
	ISP_PIPELINE_QUEUE_OUTPUT = 8,
	/* The input entity is idle, पढ़ोy to be started. */
	ISP_PIPELINE_IDLE_INPUT = 16,
	/* The output entity is idle, पढ़ोy to be started. */
	ISP_PIPELINE_IDLE_OUTPUT = 32,
	/* The pipeline is currently streaming. */
	ISP_PIPELINE_STREAM = 64,
पूर्ण;

/*
 * काष्ठा isp_pipeline - An ISP hardware pipeline
 * @field: The field being processed by the pipeline
 * @error: A hardware error occurred during capture
 * @ent_क्रमागत: Entities in the pipeline
 */
काष्ठा isp_pipeline अणु
	काष्ठा media_pipeline pipe;
	spinlock_t lock;		/* Pipeline state and queue flags */
	अचिन्हित पूर्णांक state;
	क्रमागत isp_pipeline_stream_state stream_state;
	काष्ठा isp_video *input;
	काष्ठा isp_video *output;
	काष्ठा media_entity_क्रमागत ent_क्रमागत;
	अचिन्हित दीर्घ l3_ick;
	अचिन्हित पूर्णांक max_rate;
	क्रमागत v4l2_field field;
	atomic_t frame_number;
	bool करो_propagation; /* of frame number */
	bool error;
	काष्ठा v4l2_fract max_समयperframe;
	काष्ठा v4l2_subdev *बाह्यal;
	अचिन्हित पूर्णांक बाह्यal_rate;
	अचिन्हित पूर्णांक बाह्यal_width;
पूर्ण;

#घोषणा to_isp_pipeline(__e) \
	container_of((__e)->pipe, काष्ठा isp_pipeline, pipe)

अटल अंतरभूत पूर्णांक isp_pipeline_पढ़ोy(काष्ठा isp_pipeline *pipe)
अणु
	वापस pipe->state == (ISP_PIPELINE_STREAM_INPUT |
			       ISP_PIPELINE_STREAM_OUTPUT |
			       ISP_PIPELINE_QUEUE_INPUT |
			       ISP_PIPELINE_QUEUE_OUTPUT |
			       ISP_PIPELINE_IDLE_INPUT |
			       ISP_PIPELINE_IDLE_OUTPUT);
पूर्ण

/**
 * काष्ठा isp_buffer - ISP video buffer
 * @vb: videobuf2 buffer
 * @irqlist: List head क्रम insertion पूर्णांकo IRQ queue
 * @dma: DMA address
 */
काष्ठा isp_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head irqlist;
	dma_addr_t dma;
पूर्ण;

#घोषणा to_isp_buffer(buf)	container_of(buf, काष्ठा isp_buffer, vb)

क्रमागत isp_video_dmaqueue_flags अणु
	/* Set अगर DMA queue becomes empty when ISP_PIPELINE_STREAM_CONTINUOUS */
	ISP_VIDEO_DMAQUEUE_UNDERRUN = (1 << 0),
	/* Set when queuing buffer to an empty DMA queue */
	ISP_VIDEO_DMAQUEUE_QUEUED = (1 << 1),
पूर्ण;

#घोषणा isp_video_dmaqueue_flags_clr(video)	\
			(अणु (video)->dmaqueue_flags = 0; पूर्ण)

/*
 * काष्ठा isp_video_operations - ISP video operations
 * @queue:	Resume streaming when a buffer is queued. Called on VIDIOC_QBUF
 *		अगर there was no buffer previously queued.
 */
काष्ठा isp_video_operations अणु
	पूर्णांक(*queue)(काष्ठा isp_video *video, काष्ठा isp_buffer *buffer);
पूर्ण;

काष्ठा isp_video अणु
	काष्ठा video_device video;
	क्रमागत v4l2_buf_type type;
	काष्ठा media_pad pad;

	काष्ठा mutex mutex;		/* क्रमmat and crop settings */
	atomic_t active;

	काष्ठा isp_device *isp;

	अचिन्हित पूर्णांक capture_mem;
	अचिन्हित पूर्णांक bpl_alignment;	/* alignment value */
	अचिन्हित पूर्णांक bpl_zero_padding;	/* whether the alignment is optional */
	अचिन्हित पूर्णांक bpl_max;		/* maximum bytes per line value */
	अचिन्हित पूर्णांक bpl_value;		/* bytes per line value */
	अचिन्हित पूर्णांक bpl_padding;	/* padding at end of line */

	/* Pipeline state */
	काष्ठा isp_pipeline pipe;
	काष्ठा mutex stream_lock;	/* pipeline and stream states */
	bool error;

	/* Video buffers queue */
	काष्ठा vb2_queue *queue;
	काष्ठा mutex queue_lock;	/* protects the queue */
	spinlock_t irqlock;		/* protects dmaqueue */
	काष्ठा list_head dmaqueue;
	क्रमागत isp_video_dmaqueue_flags dmaqueue_flags;

	स्थिर काष्ठा isp_video_operations *ops;
पूर्ण;

#घोषणा to_isp_video(vdev)	container_of(vdev, काष्ठा isp_video, video)

काष्ठा isp_video_fh अणु
	काष्ठा v4l2_fh vfh;
	काष्ठा isp_video *video;
	काष्ठा vb2_queue queue;
	काष्ठा v4l2_क्रमmat क्रमmat;
	काष्ठा v4l2_fract समयperframe;
पूर्ण;

#घोषणा to_isp_video_fh(fh)	container_of(fh, काष्ठा isp_video_fh, vfh)
#घोषणा isp_video_queue_to_isp_video_fh(q) \
				container_of(q, काष्ठा isp_video_fh, queue)

पूर्णांक omap3isp_video_init(काष्ठा isp_video *video, स्थिर अक्षर *name);
व्योम omap3isp_video_cleanup(काष्ठा isp_video *video);
पूर्णांक omap3isp_video_रेजिस्टर(काष्ठा isp_video *video,
			    काष्ठा v4l2_device *vdev);
व्योम omap3isp_video_unरेजिस्टर(काष्ठा isp_video *video);
काष्ठा isp_buffer *omap3isp_video_buffer_next(काष्ठा isp_video *video);
व्योम omap3isp_video_cancel_stream(काष्ठा isp_video *video);
व्योम omap3isp_video_resume(काष्ठा isp_video *video, पूर्णांक continuous);
काष्ठा media_pad *omap3isp_video_remote_pad(काष्ठा isp_video *video);

स्थिर काष्ठा isp_क्रमmat_info *
omap3isp_video_क्रमmat_info(u32 code);

#पूर्ण_अगर /* OMAP3_ISP_VIDEO_H */
