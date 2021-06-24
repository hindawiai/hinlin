<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 */
#अगर_अघोषित VPBE_DISPLAY_H
#घोषणा VPBE_DISPLAY_H

/* Header files */
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe_osd.h>
#समावेश <media/davinci/vpbe.h>

#घोषणा VPBE_DISPLAY_MAX_DEVICES 2

क्रमागत vpbe_display_device_id अणु
	VPBE_DISPLAY_DEVICE_0,
	VPBE_DISPLAY_DEVICE_1
पूर्ण;

#घोषणा VPBE_DISPLAY_DRV_NAME	"vpbe-display"

#घोषणा VPBE_DISPLAY_MAJOR_RELEASE              1
#घोषणा VPBE_DISPLAY_MINOR_RELEASE              0
#घोषणा VPBE_DISPLAY_BUILD                      1
#घोषणा VPBE_DISPLAY_VERSION_CODE ((VPBE_DISPLAY_MAJOR_RELEASE << 16) | \
	(VPBE_DISPLAY_MINOR_RELEASE << 8)  | \
	VPBE_DISPLAY_BUILD)

#घोषणा VPBE_DISPLAY_VALID_FIELD(field)   ((V4L2_FIELD_NONE == field) || \
	 (V4L2_FIELD_ANY == field) || (V4L2_FIELD_INTERLACED == field))

/* Exp ratio numerator and denominator स्थिरants */
#घोषणा VPBE_DISPLAY_H_EXP_RATIO_N	9
#घोषणा VPBE_DISPLAY_H_EXP_RATIO_D	8
#घोषणा VPBE_DISPLAY_V_EXP_RATIO_N	6
#घोषणा VPBE_DISPLAY_V_EXP_RATIO_D	5

/* Zoom multiplication factor */
#घोषणा VPBE_DISPLAY_ZOOM_4X	4
#घोषणा VPBE_DISPLAY_ZOOM_2X	2

/* Structures */
काष्ठा display_layer_info अणु
	पूर्णांक enable;
	/* Layer ID used by Display Manager */
	क्रमागत osd_layer id;
	काष्ठा osd_layer_config config;
	क्रमागत osd_zoom_factor h_zoom;
	क्रमागत osd_zoom_factor v_zoom;
	क्रमागत osd_h_exp_ratio h_exp;
	क्रमागत osd_v_exp_ratio v_exp;
पूर्ण;

काष्ठा vpbe_disp_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

/* vpbe display object काष्ठाure */
काष्ठा vpbe_layer अणु
	/* Poपूर्णांकer to the vpbe_display */
	काष्ठा vpbe_display *disp_dev;
	/* Poपूर्णांकer poपूर्णांकing to current v4l2_buffer */
	काष्ठा vpbe_disp_buffer *cur_frm;
	/* Poपूर्णांकer poपूर्णांकing to next v4l2_buffer */
	काष्ठा vpbe_disp_buffer *next_frm;
	/* videobuf specअगरic parameters
	 * Buffer queue used in video-buf
	 */
	काष्ठा vb2_queue buffer_queue;
	/* Queue of filled frames */
	काष्ठा list_head dma_queue;
	/* Used in video-buf */
	spinlock_t irqlock;
	/* V4l2 specअगरic parameters */
	/* Identअगरies video device क्रम this layer */
	काष्ठा video_device video_dev;
	/* Used to store pixel क्रमmat */
	काष्ठा v4l2_pix_क्रमmat pix_fmt;
	क्रमागत v4l2_field buf_field;
	/* Video layer configuration params */
	काष्ठा display_layer_info layer_info;
	/* vpbe specअगरic parameters
	 * enable winकरोw क्रम display
	 */
	अचिन्हित अक्षर winकरोw_enable;
	/* number of खोलो instances of the layer */
	अचिन्हित पूर्णांक usrs;
	/* Indicates id of the field which is being displayed */
	अचिन्हित पूर्णांक field_id;
	/* Identअगरies device object */
	क्रमागत vpbe_display_device_id device_id;
	/* facilitation of ioctl ops lock by v4l2*/
	काष्ठा mutex opslock;
	u8 layer_first_पूर्णांक;
पूर्ण;

/* vpbe device काष्ठाure */
काष्ठा vpbe_display अणु
	/* layer specअगरic parameters */
	/* lock क्रम isr updates to buf layers*/
	spinlock_t dma_queue_lock;
	/* C-Plane offset from start of y-plane */
	अचिन्हित पूर्णांक cbcr_ofst;
	काष्ठा vpbe_layer *dev[VPBE_DISPLAY_MAX_DEVICES];
	काष्ठा vpbe_device *vpbe_dev;
	काष्ठा osd_state *osd_device;
पूर्ण;

काष्ठा buf_config_params अणु
	अचिन्हित अक्षर min_numbuffers;
	अचिन्हित अक्षर numbuffers[VPBE_DISPLAY_MAX_DEVICES];
	अचिन्हित पूर्णांक min_bufsize[VPBE_DISPLAY_MAX_DEVICES];
	अचिन्हित पूर्णांक layer_bufsize[VPBE_DISPLAY_MAX_DEVICES];
पूर्ण;

#पूर्ण_अगर	/* VPBE_DISPLAY_H */
