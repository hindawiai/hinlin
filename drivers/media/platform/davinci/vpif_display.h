<शैली गुरु>
/*
 * VPIF display header file
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित VPIF_DISPLAY_H
#घोषणा VPIF_DISPLAY_H

/* Header files */
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/v4l2-device.h>

#समावेश "vpif.h"

/* Macros */
#घोषणा VPIF_DISPLAY_VERSION	"0.0.2"

#घोषणा VPIF_VALID_FIELD(field) \
	(((V4L2_FIELD_ANY == field) || (V4L2_FIELD_NONE == field)) || \
	(((V4L2_FIELD_INTERLACED == field) || (V4L2_FIELD_SEQ_TB == field)) || \
	(V4L2_FIELD_SEQ_BT == field)))

#घोषणा VPIF_DISPLAY_MAX_DEVICES	(2)
#घोषणा VPIF_SLICED_BUF_SIZE		(256)
#घोषणा VPIF_SLICED_MAX_SERVICES	(3)
#घोषणा VPIF_VIDEO_INDEX		(0)
#घोषणा VPIF_VBI_INDEX			(1)
#घोषणा VPIF_HBI_INDEX			(2)

/* Setting it to 1 as HBI/VBI support yet to be added , अन्यथा 3*/
#घोषणा VPIF_NUMOBJECTS	(1)

/* Macros */
#घोषणा ISALIGNED(a)    (0 == ((a) & 7))

/* क्रमागतerated data types */
/* Enumerated data type to give id to each device per channel */
क्रमागत vpअगर_channel_id अणु
	VPIF_CHANNEL2_VIDEO = 0,	/* Channel2 Video */
	VPIF_CHANNEL3_VIDEO,		/* Channel3 Video */
पूर्ण;

/* काष्ठाures */

काष्ठा video_obj अणु
	क्रमागत v4l2_field buf_field;
	u32 latest_only;		/* indicate whether to वापस
					 * most recent displayed frame only */
	v4l2_std_id stdid;		/* Currently selected or शेष
					 * standard */
	काष्ठा v4l2_dv_timings dv_timings;
पूर्ण;

काष्ठा vpअगर_disp_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

काष्ठा common_obj अणु
	काष्ठा vpअगर_disp_buffer *cur_frm;	/* Poपूर्णांकer poपूर्णांकing to current
						 * vb2_buffer */
	काष्ठा vpअगर_disp_buffer *next_frm;	/* Poपूर्णांकer poपूर्णांकing to next
						 * vb2_buffer */
	काष्ठा v4l2_क्रमmat fmt;			/* Used to store the क्रमmat */
	काष्ठा vb2_queue buffer_queue;		/* Buffer queue used in
						 * video-buf */

	काष्ठा list_head dma_queue;		/* Queue of filled frames */
	spinlock_t irqlock;			/* Used in video-buf */

	/* channel specअगरic parameters */
	काष्ठा mutex lock;			/* lock used to access this
						 * काष्ठाure */
	u32 ytop_off;				/* offset of Y top from the
						 * starting of the buffer */
	u32 ybपंचांग_off;				/* offset of Y bottom from the
						 * starting of the buffer */
	u32 ctop_off;				/* offset of C top from the
						 * starting of the buffer */
	u32 cbपंचांग_off;				/* offset of C bottom from the
						 * starting of the buffer */
	/* Function poपूर्णांकer to set the addresses */
	व्योम (*set_addr)(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	u32 height;
	u32 width;
पूर्ण;

काष्ठा channel_obj अणु
	/* V4l2 specअगरic parameters */
	काष्ठा video_device video_dev;	/* Identअगरies video device क्रम
					 * this channel */
	u32 field_id;			/* Indicates id of the field
					 * which is being displayed */
	u8 initialized;			/* flag to indicate whether
					 * encoder is initialized */
	u32 output_idx;			/* Current output index */
	काष्ठा v4l2_subdev *sd;		/* Current output subdev(may be शून्य) */

	क्रमागत vpअगर_channel_id channel_id;/* Identअगरies channel */
	काष्ठा vpअगर_params vpअगरparams;
	काष्ठा common_obj common[VPIF_NUMOBJECTS];
	काष्ठा video_obj video;
पूर्ण;

/* vpअगर device काष्ठाure */
काष्ठा vpअगर_device अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा channel_obj *dev[VPIF_DISPLAY_NUM_CHANNELS];
	काष्ठा v4l2_subdev **sd;
	काष्ठा vpअगर_display_config *config;
पूर्ण;

#पूर्ण_अगर				/* VPIF_DISPLAY_H */
