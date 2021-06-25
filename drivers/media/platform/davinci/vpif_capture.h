<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Texas Instruments Inc
 */

#अगर_अघोषित VPIF_CAPTURE_H
#घोषणा VPIF_CAPTURE_H

/* Header files */
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-device.h>

#समावेश "vpif.h"

/* Macros */
#घोषणा VPIF_CAPTURE_VERSION		"0.0.2"

#घोषणा VPIF_VALID_FIELD(field)		(((V4L2_FIELD_ANY == field) || \
	(V4L2_FIELD_NONE == field)) || \
	(((V4L2_FIELD_INTERLACED == field) || \
	(V4L2_FIELD_SEQ_TB == field)) || \
	(V4L2_FIELD_SEQ_BT == field)))

#घोषणा VPIF_CAPTURE_MAX_DEVICES	2
#घोषणा VPIF_VIDEO_INDEX		0
#घोषणा VPIF_NUMBER_OF_OBJECTS		1

/* Enumerated data type to give id to each device per channel */
क्रमागत vpअगर_channel_id अणु
	VPIF_CHANNEL0_VIDEO = 0,
	VPIF_CHANNEL1_VIDEO,
पूर्ण;

काष्ठा video_obj अणु
	क्रमागत v4l2_field buf_field;
	/* Currently selected or शेष standard */
	v4l2_std_id stdid;
	काष्ठा v4l2_dv_timings dv_timings;
पूर्ण;

काष्ठा vpअगर_cap_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा common_obj अणु
	/* Poपूर्णांकer poपूर्णांकing to current v4l2_buffer */
	काष्ठा vpअगर_cap_buffer *cur_frm;
	/* Poपूर्णांकer poपूर्णांकing to current v4l2_buffer */
	काष्ठा vpअगर_cap_buffer *next_frm;
	/* Used to store pixel क्रमmat */
	काष्ठा v4l2_क्रमmat fmt;
	/* Buffer queue used in video-buf */
	काष्ठा vb2_queue buffer_queue;
	/* Queue of filled frames */
	काष्ठा list_head dma_queue;
	/* Protects the dma_queue field */
	spinlock_t irqlock;
	/* lock used to access this काष्ठाure */
	काष्ठा mutex lock;
	/* Function poपूर्णांकer to set the addresses */
	व्योम (*set_addr) (अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			  अचिन्हित दीर्घ);
	/* offset where Y top starts from the starting of the buffer */
	u32 ytop_off;
	/* offset where Y bottom starts from the starting of the buffer */
	u32 ybपंचांग_off;
	/* offset where C top starts from the starting of the buffer */
	u32 ctop_off;
	/* offset where C bottom starts from the starting of the buffer */
	u32 cbपंचांग_off;
	/* Indicates width of the image data */
	u32 width;
	/* Indicates height of the image data */
	u32 height;
पूर्ण;

काष्ठा channel_obj अणु
	/* Identअगरies video device क्रम this channel */
	काष्ठा video_device video_dev;
	/* Indicates id of the field which is being displayed */
	u32 field_id;
	/* flag to indicate whether decoder is initialized */
	u8 initialized;
	/* Identअगरies channel */
	क्रमागत vpअगर_channel_id channel_id;
	/* Current input */
	u32 input_idx;
	/* subdev corresponding to the current input, may be शून्य */
	काष्ठा v4l2_subdev *sd;
	/* vpअगर configuration params */
	काष्ठा vpअगर_params vpअगरparams;
	/* common object array */
	काष्ठा common_obj common[VPIF_NUMBER_OF_OBJECTS];
	/* video object */
	काष्ठा video_obj video;
पूर्ण;

काष्ठा vpअगर_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा channel_obj *dev[VPIF_CAPTURE_NUM_CHANNELS];
	काष्ठा v4l2_subdev **sd;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा vpअगर_capture_config *config;
पूर्ण;

#पूर्ण_अगर				/* VPIF_CAPTURE_H */
