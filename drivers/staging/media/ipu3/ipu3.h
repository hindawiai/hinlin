<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_H
#घोषणा __IPU3_H

#समावेश <linux/iova.h>
#समावेश <linux/pci.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-dma-sg.h>

#समावेश "ipu3-css.h"

#घोषणा IMGU_NAME			"ipu3-imgu"

/*
 * The semantics of the driver is that whenever there is a buffer available in
 * master queue, the driver queues a buffer also to all other active nodes.
 * If user space hasn't provided a buffer to all other video nodes first,
 * the driver माला_लो an पूर्णांकernal dummy buffer and queues it.
 */
#घोषणा IMGU_QUEUE_MASTER		IPU3_CSS_QUEUE_IN
#घोषणा IMGU_QUEUE_FIRST_INPUT		IPU3_CSS_QUEUE_OUT
#घोषणा IMGU_MAX_QUEUE_DEPTH		(2 + 2)

#घोषणा IMGU_NODE_IN			0 /* Input RAW image */
#घोषणा IMGU_NODE_PARAMS		1 /* Input parameters */
#घोषणा IMGU_NODE_OUT			2 /* Main output क्रम still or video */
#घोषणा IMGU_NODE_VF			3 /* Preview */
#घोषणा IMGU_NODE_STAT_3A		4 /* 3A statistics */
#घोषणा IMGU_NODE_NUM			5

#घोषणा file_to_पूर्णांकel_imgu_node(__file) \
	container_of(video_devdata(__file), काष्ठा imgu_video_device, vdev)

#घोषणा IPU3_INPUT_MIN_WIDTH		0U
#घोषणा IPU3_INPUT_MIN_HEIGHT		0U
#घोषणा IPU3_INPUT_MAX_WIDTH		5120U
#घोषणा IPU3_INPUT_MAX_HEIGHT		38404U
#घोषणा IPU3_OUTPUT_MIN_WIDTH		2U
#घोषणा IPU3_OUTPUT_MIN_HEIGHT		2U
#घोषणा IPU3_OUTPUT_MAX_WIDTH		4480U
#घोषणा IPU3_OUTPUT_MAX_HEIGHT		34004U

काष्ठा imgu_vb2_buffer अणु
	/* Public fields */
	काष्ठा vb2_v4l2_buffer vbb;	/* Must be the first field */

	/* Private fields */
	काष्ठा list_head list;
पूर्ण;

काष्ठा imgu_buffer अणु
	काष्ठा imgu_vb2_buffer vid_buf;	/* Must be the first field */
	काष्ठा imgu_css_buffer css_buf;
	काष्ठा imgu_css_map map;
पूर्ण;

काष्ठा imgu_node_mapping अणु
	अचिन्हित पूर्णांक css_queue;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा imgu_video_device अणु
	स्थिर अक्षर *name;
	bool output;
	bool enabled;
	काष्ठा v4l2_क्रमmat vdev_fmt;	/* Currently set क्रमmat */

	/* Private fields */
	काष्ठा video_device vdev;
	काष्ठा media_pad vdev_pad;
	काष्ठा v4l2_mbus_framefmt pad_fmt;
	काष्ठा vb2_queue vbq;
	काष्ठा list_head buffers;
	/* Protect vb2_queue and vdev काष्ठाs*/
	काष्ठा mutex lock;
	atomic_t sequence;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक pipe;
पूर्ण;

काष्ठा imgu_v4l2_subdev अणु
	अचिन्हित पूर्णांक pipe;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad subdev_pads[IMGU_NODE_NUM];
	काष्ठा अणु
		काष्ठा v4l2_rect eff; /* effective resolution */
		काष्ठा v4l2_rect bds; /* bayer-करोमुख्य scaled resolution*/
		काष्ठा v4l2_rect gdc; /* gdc output resolution */
	पूर्ण rect;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *ctrl;
	atomic_t running_mode;
	bool active;
पूर्ण;

काष्ठा imgu_media_pipe अणु
	अचिन्हित पूर्णांक pipe;

	/* Internally enabled queues */
	काष्ठा अणु
		काष्ठा imgu_css_map dmap;
		काष्ठा imgu_css_buffer dummybufs[IMGU_MAX_QUEUE_DEPTH];
	पूर्ण queues[IPU3_CSS_QUEUES];
	काष्ठा imgu_video_device nodes[IMGU_NODE_NUM];
	bool queue_enabled[IMGU_NODE_NUM];
	काष्ठा media_pipeline pipeline;
	काष्ठा imgu_v4l2_subdev imgu_sd;
पूर्ण;

/*
 * imgu_device -- ImgU (Imaging Unit) driver
 */
काष्ठा imgu_device अणु
	काष्ठा pci_dev *pci_dev;
	व्योम __iomem *base;

	/* Public fields, fill beक्रमe रेजिस्टरing */
	अचिन्हित पूर्णांक buf_काष्ठा_size;
	bool streaming;		/* Public पढ़ो only */

	काष्ठा imgu_media_pipe imgu_pipe[IMGU_MAX_PIPE_NUM];

	/* Private fields */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा v4l2_file_operations v4l2_file_ops;

	/* MMU driver क्रम css */
	काष्ठा imgu_mmu_info *mmu;
	काष्ठा iova_करोमुख्य iova_करोमुख्य;

	/* css - Camera Sub-System */
	काष्ठा imgu_css css;

	/*
	 * Coarse-grained lock to protect
	 * vid_buf.list and css->queue
	 */
	काष्ठा mutex lock;

	/* Lock to protect ग_लिखोs to streaming flag in this काष्ठा */
	काष्ठा mutex streaming_lock;

	/* Forbid streaming and buffer queuing during प्रणाली suspend. */
	atomic_t qbuf_barrier;
	/* Indicate अगर प्रणाली suspend take place जबतक imgu is streaming. */
	bool suspend_in_stream;
	/* Used to रुको क्रम FW buffer queue drain. */
	रुको_queue_head_t buf_drain_wq;
पूर्ण;

अचिन्हित पूर्णांक imgu_node_to_queue(अचिन्हित पूर्णांक node);
अचिन्हित पूर्णांक imgu_map_node(काष्ठा imgu_device *imgu, अचिन्हित पूर्णांक css_queue);
पूर्णांक imgu_queue_buffers(काष्ठा imgu_device *imgu, bool initial,
		       अचिन्हित पूर्णांक pipe);

पूर्णांक imgu_v4l2_रेजिस्टर(काष्ठा imgu_device *dev);
पूर्णांक imgu_v4l2_unरेजिस्टर(काष्ठा imgu_device *dev);
व्योम imgu_v4l2_buffer_करोne(काष्ठा vb2_buffer *vb, क्रमागत vb2_buffer_state state);

पूर्णांक imgu_s_stream(काष्ठा imgu_device *imgu, पूर्णांक enable);

#पूर्ण_अगर
