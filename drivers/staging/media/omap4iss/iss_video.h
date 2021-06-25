<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - Generic video node
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_VIDEO_H
#घोषणा OMAP4_ISS_VIDEO_H

#समावेश <linux/v4l2-mediabus.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#घोषणा ISS_VIDEO_DRIVER_NAME		"issvideo"

काष्ठा iss_device;
काष्ठा iss_video;
काष्ठा v4l2_mbus_framefmt;
काष्ठा v4l2_pix_क्रमmat;

/*
 * काष्ठा iss_क्रमmat_info - ISS media bus क्रमmat inक्रमmation
 * @code: V4L2 media bus क्रमmat code
 * @truncated: V4L2 media bus क्रमmat code क्रम the same क्रमmat truncated to 10
 *	bits. Identical to @code अगर the क्रमmat is 10 bits wide or less.
 * @uncompressed: V4L2 media bus क्रमmat code क्रम the corresponding uncompressed
 *	क्रमmat. Identical to @code अगर the क्रमmat is not DPCM compressed.
 * @flavor: V4L2 media bus क्रमmat code क्रम the same pixel layout but
 *	shअगरted to be 8 bits per pixel. =0 अगर क्रमmat is not shअगरtable.
 * @pixelक्रमmat: V4L2 pixel क्रमmat FCC identअगरier
 * @bpp: Bits per pixel
 */
काष्ठा iss_क्रमmat_info अणु
	u32 code;
	u32 truncated;
	u32 uncompressed;
	u32 flavor;
	u32 pixelक्रमmat;
	अचिन्हित पूर्णांक bpp;
पूर्ण;

क्रमागत iss_pipeline_stream_state अणु
	ISS_PIPELINE_STREAM_STOPPED = 0,
	ISS_PIPELINE_STREAM_CONTINUOUS = 1,
	ISS_PIPELINE_STREAM_SINGLESHOT = 2,
पूर्ण;

क्रमागत iss_pipeline_state अणु
	/* The stream has been started on the input video node. */
	ISS_PIPELINE_STREAM_INPUT = 1,
	/* The stream has been started on the output video node. */
	ISS_PIPELINE_STREAM_OUTPUT = (1 << 1),
	/* At least one buffer is queued on the input video node. */
	ISS_PIPELINE_QUEUE_INPUT = (1 << 2),
	/* At least one buffer is queued on the output video node. */
	ISS_PIPELINE_QUEUE_OUTPUT = (1 << 3),
	/* The input entity is idle, पढ़ोy to be started. */
	ISS_PIPELINE_IDLE_INPUT = (1 << 4),
	/* The output entity is idle, पढ़ोy to be started. */
	ISS_PIPELINE_IDLE_OUTPUT = (1 << 5),
	/* The pipeline is currently streaming. */
	ISS_PIPELINE_STREAM = (1 << 6),
पूर्ण;

/*
 * काष्ठा iss_pipeline - An OMAP4 ISS hardware pipeline
 * @ent_क्रमागत: Entities in the pipeline
 * @error: A hardware error occurred during capture
 */
काष्ठा iss_pipeline अणु
	काष्ठा media_pipeline pipe;
	spinlock_t lock;		/* Pipeline state and queue flags */
	अचिन्हित पूर्णांक state;
	क्रमागत iss_pipeline_stream_state stream_state;
	काष्ठा iss_video *input;
	काष्ठा iss_video *output;
	काष्ठा media_entity_क्रमागत ent_क्रमागत;
	atomic_t frame_number;
	bool करो_propagation; /* of frame number */
	bool error;
	काष्ठा v4l2_fract max_समयperframe;
	काष्ठा v4l2_subdev *बाह्यal;
	अचिन्हित पूर्णांक बाह्यal_rate;
	पूर्णांक बाह्यal_bpp;
पूर्ण;

#घोषणा to_iss_pipeline(__e) \
	container_of((__e)->pipe, काष्ठा iss_pipeline, pipe)

अटल अंतरभूत पूर्णांक iss_pipeline_पढ़ोy(काष्ठा iss_pipeline *pipe)
अणु
	वापस pipe->state == (ISS_PIPELINE_STREAM_INPUT |
			       ISS_PIPELINE_STREAM_OUTPUT |
			       ISS_PIPELINE_QUEUE_INPUT |
			       ISS_PIPELINE_QUEUE_OUTPUT |
			       ISS_PIPELINE_IDLE_INPUT |
			       ISS_PIPELINE_IDLE_OUTPUT);
पूर्ण

/*
 * काष्ठा iss_buffer - ISS buffer
 * @buffer: ISS video buffer
 * @iss_addr: Physical address of the buffer.
 */
काष्ठा iss_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer	vb;
	काष्ठा list_head	list;
	dma_addr_t iss_addr;
पूर्ण;

#घोषणा to_iss_buffer(buf)	container_of(buf, काष्ठा iss_buffer, vb)

क्रमागत iss_video_dmaqueue_flags अणु
	/* Set अगर DMA queue becomes empty when ISS_PIPELINE_STREAM_CONTINUOUS */
	ISS_VIDEO_DMAQUEUE_UNDERRUN = (1 << 0),
	/* Set when queuing buffer to an empty DMA queue */
	ISS_VIDEO_DMAQUEUE_QUEUED = (1 << 1),
पूर्ण;

#घोषणा iss_video_dmaqueue_flags_clr(video)	\
			(अणु (video)->dmaqueue_flags = 0; पूर्ण)

/*
 * काष्ठा iss_video_operations - ISS video operations
 * @queue:	Resume streaming when a buffer is queued. Called on VIDIOC_QBUF
 *		अगर there was no buffer previously queued.
 */
काष्ठा iss_video_operations अणु
	पूर्णांक (*queue)(काष्ठा iss_video *video, काष्ठा iss_buffer *buffer);
पूर्ण;

काष्ठा iss_video अणु
	काष्ठा video_device video;
	क्रमागत v4l2_buf_type type;
	काष्ठा media_pad pad;

	काष्ठा mutex mutex;		/* क्रमmat and crop settings */
	atomic_t active;

	काष्ठा iss_device *iss;

	अचिन्हित पूर्णांक capture_mem;
	अचिन्हित पूर्णांक bpl_alignment;	/* alignment value */
	अचिन्हित पूर्णांक bpl_zero_padding;	/* whether the alignment is optional */
	अचिन्हित पूर्णांक bpl_max;		/* maximum bytes per line value */
	अचिन्हित पूर्णांक bpl_value;		/* bytes per line value */
	अचिन्हित पूर्णांक bpl_padding;	/* padding at end of line */

	/* Pipeline state */
	काष्ठा iss_pipeline pipe;
	काष्ठा mutex stream_lock;	/* pipeline and stream states */
	bool error;

	/* Video buffers queue */
	काष्ठा vb2_queue *queue;
	spinlock_t qlock;		/* protects dmaqueue and error */
	काष्ठा list_head dmaqueue;
	क्रमागत iss_video_dmaqueue_flags dmaqueue_flags;

	स्थिर काष्ठा iss_video_operations *ops;
पूर्ण;

#घोषणा to_iss_video(vdev)	container_of(vdev, काष्ठा iss_video, video)

काष्ठा iss_video_fh अणु
	काष्ठा v4l2_fh vfh;
	काष्ठा iss_video *video;
	काष्ठा vb2_queue queue;
	काष्ठा v4l2_क्रमmat क्रमmat;
	काष्ठा v4l2_fract समयperframe;
पूर्ण;

#घोषणा to_iss_video_fh(fh)	container_of(fh, काष्ठा iss_video_fh, vfh)
#घोषणा iss_video_queue_to_iss_video_fh(q) \
				container_of(q, काष्ठा iss_video_fh, queue)

पूर्णांक omap4iss_video_init(काष्ठा iss_video *video, स्थिर अक्षर *name);
व्योम omap4iss_video_cleanup(काष्ठा iss_video *video);
पूर्णांक omap4iss_video_रेजिस्टर(काष्ठा iss_video *video,
			    काष्ठा v4l2_device *vdev);
व्योम omap4iss_video_unरेजिस्टर(काष्ठा iss_video *video);
काष्ठा iss_buffer *omap4iss_video_buffer_next(काष्ठा iss_video *video);
व्योम omap4iss_video_cancel_stream(काष्ठा iss_video *video);
काष्ठा media_pad *omap4iss_video_remote_pad(काष्ठा iss_video *video);

स्थिर काष्ठा iss_क्रमmat_info *
omap4iss_video_क्रमmat_info(u32 code);

#पूर्ण_अगर /* OMAP4_ISS_VIDEO_H */
