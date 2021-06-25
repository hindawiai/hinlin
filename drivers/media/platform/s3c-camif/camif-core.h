<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * s3c24xx/s3c64xx SoC series Camera Interface (CAMIF) driver
 *
 * Copyright (C) 2012 Sylwester Nawrocki <sylvester.nawrocki@gmail.com>
 * Copyright (C) 2012 Tomasz Figa <tomasz.figa@gmail.com>
*/

#अगर_अघोषित CAMIF_CORE_H_
#घोषणा CAMIF_CORE_H_

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/drv-पूर्णांकf/s3c_camअगर.h>

#घोषणा S3C_CAMIF_DRIVER_NAME	"s3c-camif"
#घोषणा CAMIF_REQ_BUFS_MIN	3
#घोषणा CAMIF_MAX_OUT_BUFS	4
#घोषणा CAMIF_MAX_PIX_WIDTH	4096
#घोषणा CAMIF_MAX_PIX_HEIGHT	4096
#घोषणा SCALER_MAX_RATIO	64
#घोषणा CAMIF_DEF_WIDTH		640
#घोषणा CAMIF_DEF_HEIGHT	480
#घोषणा CAMIF_STOP_TIMEOUT	1500 /* ms */

#घोषणा S3C244X_CAMIF_IP_REV	0x20 /* 2.0 */
#घोषणा S3C2450_CAMIF_IP_REV	0x30 /* 3.0 - not implemented, not tested */
#घोषणा S3C6400_CAMIF_IP_REV	0x31 /* 3.1 - not implemented, not tested */
#घोषणा S3C6410_CAMIF_IP_REV	0x32 /* 3.2 */

/* काष्ठा camअगर_vp::state */

#घोषणा ST_VP_PENDING		(1 << 0)
#घोषणा ST_VP_RUNNING		(1 << 1)
#घोषणा ST_VP_STREAMING		(1 << 2)
#घोषणा ST_VP_SENSOR_STREAMING	(1 << 3)

#घोषणा ST_VP_ABORTING		(1 << 4)
#घोषणा ST_VP_OFF		(1 << 5)
#घोषणा ST_VP_LASTIRQ		(1 << 6)

#घोषणा ST_VP_CONFIG		(1 << 8)

#घोषणा CAMIF_SD_PAD_SINK	0
#घोषणा CAMIF_SD_PAD_SOURCE_C	1
#घोषणा CAMIF_SD_PAD_SOURCE_P	2
#घोषणा CAMIF_SD_PADS_NUM	3

क्रमागत img_fmt अणु
	IMG_FMT_RGB565 = 0x0010,
	IMG_FMT_RGB666,
	IMG_FMT_XRGB8888,
	IMG_FMT_YCBCR420 = 0x0020,
	IMG_FMT_YCRCB420,
	IMG_FMT_YCBCR422P,
	IMG_FMT_YCBYCR422 = 0x0040,
	IMG_FMT_YCRYCB422,
	IMG_FMT_CBYCRY422,
	IMG_FMT_CRYCBY422,
पूर्ण;

#घोषणा img_fmt_is_rgb(x) ((x) & 0x10)
#घोषणा img_fmt_is_ycbcr(x) ((x) & 0x60)

/* Possible values क्रम काष्ठा camअगर_fmt::flags */
#घोषणा FMT_FL_S3C24XX_CODEC	(1 << 0)
#घोषणा FMT_FL_S3C24XX_PREVIEW	(1 << 1)
#घोषणा FMT_FL_S3C64XX		(1 << 2)

/**
 * काष्ठा camअगर_fmt - pixel क्रमmat description
 * @fourcc:    fourcc code क्रम this क्रमmat, 0 अगर not applicable
 * @color:     a corresponding क्रमागत img_fmt
 * @colplanes: number of physically contiguous data planes
 * @flags:     indicate क्रम which SoCs revisions this क्रमmat is valid
 * @depth:     bits per pixel (total)
 * @ybpp:      number of luminance bytes per pixel
 */
काष्ठा camअगर_fmt अणु
	u32 fourcc;
	u32 color;
	u16 colplanes;
	u16 flags;
	u8 depth;
	u8 ybpp;
पूर्ण;

/**
 * काष्ठा camअगर_dma_offset - pixel offset inक्रमmation क्रम DMA
 * @initial: offset (in pixels) to first pixel
 * @line: offset (in pixels) from end of line to start of next line
 */
काष्ठा camअगर_dma_offset अणु
	पूर्णांक	initial;
	पूर्णांक	line;
पूर्ण;

/**
 * काष्ठा camअगर_frame - source/target frame properties
 * @f_width: full pixel width
 * @f_height: full pixel height
 * @rect: crop/composition rectangle
 * @dma_offset: DMA offset configuration
 */
काष्ठा camअगर_frame अणु
	u16 f_width;
	u16 f_height;
	काष्ठा v4l2_rect rect;
	काष्ठा camअगर_dma_offset dma_offset;
पूर्ण;

/* CAMIF घड़ीs क्रमागतeration */
क्रमागत अणु
	CLK_GATE,
	CLK_CAM,
	CLK_MAX_NUM,
पूर्ण;

काष्ठा vp_pix_limits अणु
	u16 max_out_width;
	u16 max_sc_out_width;
	u16 out_width_align;
	u16 max_height;
	u8 min_out_width;
	u16 out_hor_offset_align;
पूर्ण;

काष्ठा camअगर_pix_limits अणु
	u16 win_hor_offset_align;
पूर्ण;

/**
 * काष्ठा s3c_camअगर_variant - CAMIF variant काष्ठाure
 * @vp_pix_limits:    pixel limits क्रम the codec and preview paths
 * @pix_limits:       pixel limits क्रम the camera input पूर्णांकerface
 * @ip_revision:      the CAMIF IP revision: 0x20 क्रम s3c244x, 0x32 क्रम s3c6410
 * @has_img_effect:   supports image effects
 * @vp_offset:        रेजिस्टर offset
 */
काष्ठा s3c_camअगर_variant अणु
	काष्ठा vp_pix_limits vp_pix_limits[2];
	काष्ठा camअगर_pix_limits pix_limits;
	u8 ip_revision;
	u8 has_img_effect;
	अचिन्हित पूर्णांक vp_offset;
पूर्ण;

काष्ठा s3c_camअगर_drvdata अणु
	स्थिर काष्ठा s3c_camअगर_variant *variant;
	अचिन्हित दीर्घ bus_clk_freq;
पूर्ण;

काष्ठा camअगर_scaler अणु
	u8 scaleup_h;
	u8 scaleup_v;
	u8 copy;
	u8 enable;
	u32 h_shअगरt;
	u32 v_shअगरt;
	u32 pre_h_ratio;
	u32 pre_v_ratio;
	u32 pre_dst_width;
	u32 pre_dst_height;
	u32 मुख्य_h_ratio;
	u32 मुख्य_v_ratio;
पूर्ण;

काष्ठा camअगर_dev;

/**
 * काष्ठा camअगर_vp - CAMIF data processing path काष्ठाure (codec/preview)
 * @irq_queue:	    पूर्णांकerrupt handling रुकोqueue
 * @irq:	    पूर्णांकerrupt number क्रम this data path
 * @camअगर:	    poपूर्णांकer to the camअगर काष्ठाure
 * @pad:	    media pad क्रम the video node
 * @vdev:           video device
 * @ctrl_handler:   video node controls handler
 * @owner:	    file handle that own the streaming
 * @vb_queue:       vb2 buffer queue
 * @pending_buf_q:  pending (empty) buffers queue head
 * @active_buf_q:   active (being written) buffers queue head
 * @active_buffers: counter of buffer set up at the DMA engine
 * @buf_index:	    identअगरier of a last empty buffer set up in H/W
 * @frame_sequence: image frame sequence counter
 * @reqbufs_count:  the number of buffers requested
 * @scaler:	    the scaler काष्ठाure
 * @out_fmt:	    pixel क्रमmat at this video path output
 * @payload:	    the output data frame payload size
 * @out_frame:	    the output pixel resolution
 * @state:	    the video path's state
 * @fmt_flags:	    flags determining supported pixel क्रमmats
 * @id:		    CAMIF id, 0 - codec, 1 - preview
 * @rotation:	    current image rotation value
 * @hflip:	    apply horizontal flip अगर set
 * @vflip:	    apply vertical flip अगर set
 * @offset:	    रेजिस्टर offset
 */
काष्ठा camअगर_vp अणु
	रुको_queue_head_t	irq_queue;
	पूर्णांक			irq;
	काष्ठा camअगर_dev	*camअगर;
	काष्ठा media_pad	pad;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_fh		*owner;
	काष्ठा vb2_queue	vb_queue;
	काष्ठा list_head	pending_buf_q;
	काष्ठा list_head	active_buf_q;
	अचिन्हित पूर्णांक		active_buffers;
	अचिन्हित पूर्णांक		buf_index;
	अचिन्हित पूर्णांक		frame_sequence;
	अचिन्हित पूर्णांक		reqbufs_count;
	काष्ठा camअगर_scaler	scaler;
	स्थिर काष्ठा camअगर_fmt	*out_fmt;
	अचिन्हित पूर्णांक		payload;
	काष्ठा camअगर_frame	out_frame;
	अचिन्हित पूर्णांक		state;
	u16			fmt_flags;
	u8			id;
	u16			rotation;
	u8			hflip;
	u8			vflip;
	अचिन्हित पूर्णांक		offset;
पूर्ण;

/* Video processing path क्रमागतeration */
#घोषणा VP_CODEC	0
#घोषणा VP_PREVIEW	1
#घोषणा CAMIF_VP_NUM	2

/**
 * काष्ठा camअगर_dev - the CAMIF driver निजी data काष्ठाure
 * @media_dev:    top-level media device काष्ठाure
 * @v4l2_dev:	  root v4l2_device
 * @subdev:       camera पूर्णांकerface ("catchcam") subdev
 * @mbus_fmt:	  camera input media bus क्रमmat
 * @camअगर_crop:   camera input पूर्णांकerface crop rectangle
 * @pads:	  the camअगर subdev's media pads
 * @stream_count: the camera पूर्णांकerface streaming reference counter
 * @sensor:       image sensor data काष्ठाure
 * @m_pipeline:	  video entity pipeline description
 * @ctrl_handler: v4l2 control handler (owned by @subdev)
 * @ctrl_test_pattern: V4L2_CID_TEST_PATTERN control
 * @ctrl_colorfx: V4L2_CID_COLORFX control
 * @ctrl_colorfx_cbcr:  V4L2_CID_COLORFX_CBCR control
 * @test_pattern: test pattern
 * @colorfx:	  color effect
 * @colorfx_cb:   Cb value क्रम V4L2_COLORFX_SET_CBCR
 * @colorfx_cr:   Cr value क्रम V4L2_COLORFX_SET_CBCR
 * @vp:           video path (DMA) description (codec/preview)
 * @variant:      variant inक्रमmation क्रम this device
 * @dev:	  poपूर्णांकer to the CAMIF device काष्ठा
 * @pdata:	  a copy of the driver's platक्रमm data
 * @घड़ी:	  घड़ीs required क्रम the CAMIF operation
 * @lock:	  mutex protecting this data काष्ठाure
 * @slock:	  spinlock protecting CAMIF रेजिस्टरs
 * @io_base:	  start address of the mmapped CAMIF रेजिस्टरs
 */
काष्ठा camअगर_dev अणु
	काष्ठा media_device		media_dev;
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा v4l2_subdev		subdev;
	काष्ठा v4l2_mbus_framefmt	mbus_fmt;
	काष्ठा v4l2_rect		camअगर_crop;
	काष्ठा media_pad		pads[CAMIF_SD_PADS_NUM];
	पूर्णांक				stream_count;

	काष्ठा cam_sensor अणु
		काष्ठा v4l2_subdev	*sd;
		लघु			घातer_count;
		लघु			stream_count;
	पूर्ण sensor;
	काष्ठा media_pipeline		*m_pipeline;

	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा v4l2_ctrl		*ctrl_test_pattern;
	काष्ठा अणु
		काष्ठा v4l2_ctrl	*ctrl_colorfx;
		काष्ठा v4l2_ctrl	*ctrl_colorfx_cbcr;
	पूर्ण;
	u8				test_pattern;
	u8				colorfx;
	u8				colorfx_cb;
	u8				colorfx_cr;

	काष्ठा camअगर_vp			vp[CAMIF_VP_NUM];

	स्थिर काष्ठा s3c_camअगर_variant	*variant;
	काष्ठा device			*dev;
	काष्ठा s3c_camअगर_plat_data	pdata;
	काष्ठा clk			*घड़ी[CLK_MAX_NUM];
	काष्ठा mutex			lock;
	spinlock_t			slock;
	व्योम __iomem			*io_base;
पूर्ण;

/**
 * काष्ठा camअगर_addr - Y/Cb/Cr DMA start address काष्ठाure
 * @y:	 luminance plane dma address
 * @cb:	 Cb plane dma address
 * @cr:	 Cr plane dma address
 */
काष्ठा camअगर_addr अणु
	dma_addr_t y;
	dma_addr_t cb;
	dma_addr_t cr;
पूर्ण;

/**
 * काष्ठा camअगर_buffer - the camअगर video buffer काष्ठाure
 * @vb:    vb2 buffer
 * @list:  list head क्रम the buffers queue
 * @paddr: DMA start addresses
 * @index: an identअगरier of this buffer at the DMA engine
 */
काष्ठा camअगर_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	काष्ठा camअगर_addr paddr;
	अचिन्हित पूर्णांक index;
पूर्ण;

स्थिर काष्ठा camअगर_fmt *s3c_camअगर_find_क्रमmat(काष्ठा camअगर_vp *vp,
	      स्थिर u32 *pixelक्रमmat, पूर्णांक index);
पूर्णांक s3c_camअगर_रेजिस्टर_video_node(काष्ठा camअगर_dev *camअगर, पूर्णांक idx);
व्योम s3c_camअगर_unरेजिस्टर_video_node(काष्ठा camअगर_dev *camअगर, पूर्णांक idx);
irqवापस_t s3c_camअगर_irq_handler(पूर्णांक irq, व्योम *priv);
पूर्णांक s3c_camअगर_create_subdev(काष्ठा camअगर_dev *camअगर);
व्योम s3c_camअगर_unरेजिस्टर_subdev(काष्ठा camअगर_dev *camअगर);
पूर्णांक s3c_camअगर_set_शेषs(काष्ठा camअगर_dev *camअगर);
पूर्णांक s3c_camअगर_get_scaler_config(काष्ठा camअगर_vp *vp,
				काष्ठा camअगर_scaler *scaler);

अटल अंतरभूत व्योम camअगर_active_queue_add(काष्ठा camअगर_vp *vp,
					  काष्ठा camअगर_buffer *buf)
अणु
	list_add_tail(&buf->list, &vp->active_buf_q);
	vp->active_buffers++;
पूर्ण

अटल अंतरभूत काष्ठा camअगर_buffer *camअगर_active_queue_pop(
					काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_buffer *buf = list_first_entry(&vp->active_buf_q,
					      काष्ठा camअगर_buffer, list);
	list_del(&buf->list);
	vp->active_buffers--;
	वापस buf;
पूर्ण

अटल अंतरभूत काष्ठा camअगर_buffer *camअगर_active_queue_peek(
			   काष्ठा camअगर_vp *vp, पूर्णांक index)
अणु
	काष्ठा camअगर_buffer *पंचांगp, *buf;

	अगर (WARN_ON(list_empty(&vp->active_buf_q)))
		वापस शून्य;

	list_क्रम_each_entry_safe(buf, पंचांगp, &vp->active_buf_q, list) अणु
		अगर (buf->index == index) अणु
			list_del(&buf->list);
			vp->active_buffers--;
			वापस buf;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम camअगर_pending_queue_add(काष्ठा camअगर_vp *vp,
					   काष्ठा camअगर_buffer *buf)
अणु
	list_add_tail(&buf->list, &vp->pending_buf_q);
पूर्ण

अटल अंतरभूत काष्ठा camअगर_buffer *camअगर_pending_queue_pop(
					काष्ठा camअगर_vp *vp)
अणु
	काष्ठा camअगर_buffer *buf = list_first_entry(&vp->pending_buf_q,
					      काष्ठा camअगर_buffer, list);
	list_del(&buf->list);
	वापस buf;
पूर्ण

#पूर्ण_अगर /* CAMIF_CORE_H_ */
