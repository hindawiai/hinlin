<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Video DMA
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __XILINX_VIP_DMA_H__
#घोषणा __XILINX_VIP_DMA_H__

#समावेश <linux/dmaengine.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-v4l2.h>

काष्ठा dma_chan;
काष्ठा xvip_composite_device;
काष्ठा xvip_video_क्रमmat;

/**
 * काष्ठा xvip_pipeline - Xilinx Video IP pipeline काष्ठाure
 * @pipe: media pipeline
 * @lock: protects the pipeline @stream_count
 * @use_count: number of DMA engines using the pipeline
 * @stream_count: number of DMA engines currently streaming
 * @num_dmas: number of DMA engines in the pipeline
 * @output: DMA engine at the output of the pipeline
 */
काष्ठा xvip_pipeline अणु
	काष्ठा media_pipeline pipe;

	काष्ठा mutex lock;
	अचिन्हित पूर्णांक use_count;
	अचिन्हित पूर्णांक stream_count;

	अचिन्हित पूर्णांक num_dmas;
	काष्ठा xvip_dma *output;
पूर्ण;

अटल अंतरभूत काष्ठा xvip_pipeline *to_xvip_pipeline(काष्ठा media_entity *e)
अणु
	वापस container_of(e->pipe, काष्ठा xvip_pipeline, pipe);
पूर्ण

/**
 * काष्ठा xvip_dma - Video DMA channel
 * @list: list entry in a composite device dmas list
 * @video: V4L2 video device associated with the DMA channel
 * @pad: media pad क्रम the video device entity
 * @xdev: composite device the DMA channel beदीर्घs to
 * @pipe: pipeline beदीर्घing to the DMA channel
 * @port: composite device DT node port number क्रम the DMA channel
 * @lock: protects the @क्रमmat, @fmtinfo and @queue fields
 * @क्रमmat: active V4L2 pixel क्रमmat
 * @fmtinfo: क्रमmat inक्रमmation corresponding to the active @क्रमmat
 * @queue: vb2 buffers queue
 * @sequence: V4L2 buffers sequence number
 * @queued_bufs: list of queued buffers
 * @queued_lock: protects the buf_queued list
 * @dma: DMA engine channel
 * @align: transfer alignment required by the DMA channel (in bytes)
 * @xt: dma पूर्णांकerleaved ढाँचा क्रम dma configuration
 * @sgl: data chunk काष्ठाure क्रम dma_पूर्णांकerleaved_ढाँचा
 */
काष्ठा xvip_dma अणु
	काष्ठा list_head list;
	काष्ठा video_device video;
	काष्ठा media_pad pad;

	काष्ठा xvip_composite_device *xdev;
	काष्ठा xvip_pipeline pipe;
	अचिन्हित पूर्णांक port;

	काष्ठा mutex lock;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;
	स्थिर काष्ठा xvip_video_क्रमmat *fmtinfo;

	काष्ठा vb2_queue queue;
	अचिन्हित पूर्णांक sequence;

	काष्ठा list_head queued_bufs;
	spinlock_t queued_lock;

	काष्ठा dma_chan *dma;
	अचिन्हित पूर्णांक align;
	काष्ठा dma_पूर्णांकerleaved_ढाँचा xt;
	काष्ठा data_chunk sgl[1];
पूर्ण;

#घोषणा to_xvip_dma(vdev)	container_of(vdev, काष्ठा xvip_dma, video)

पूर्णांक xvip_dma_init(काष्ठा xvip_composite_device *xdev, काष्ठा xvip_dma *dma,
		  क्रमागत v4l2_buf_type type, अचिन्हित पूर्णांक port);
व्योम xvip_dma_cleanup(काष्ठा xvip_dma *dma);

#पूर्ण_अगर /* __XILINX_VIP_DMA_H__ */
