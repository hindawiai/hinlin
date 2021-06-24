<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR MIT) */
/*
 * Rockchip ISP1 Driver - Common definitions
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on Rockchip ISP1 driver by Rockchip Electronics Co., Ltd.
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#अगर_अघोषित _RKISP1_COMMON_H
#घोषणा _RKISP1_COMMON_H

#समावेश <linux/clk.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rkisp1-config.h>
#समावेश <media/media-device.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "rkisp1-regs.h"

/*
 * flags on the 'direction' field in struct 'rkisp1_isp_mbus_info' that indicate
 * on which pad the media bus क्रमmat is supported
 */
#घोषणा RKISP1_ISP_SD_SRC BIT(0)
#घोषणा RKISP1_ISP_SD_SINK BIT(1)

/* min and max values क्रम the widths and heights of the entities */
#घोषणा RKISP1_ISP_MAX_WIDTH		4032
#घोषणा RKISP1_ISP_MAX_HEIGHT		3024
#घोषणा RKISP1_ISP_MIN_WIDTH		32
#घोषणा RKISP1_ISP_MIN_HEIGHT		32

#घोषणा RKISP1_RSZ_MP_SRC_MAX_WIDTH		4416
#घोषणा RKISP1_RSZ_MP_SRC_MAX_HEIGHT		3312
#घोषणा RKISP1_RSZ_SP_SRC_MAX_WIDTH		1920
#घोषणा RKISP1_RSZ_SP_SRC_MAX_HEIGHT		1920
#घोषणा RKISP1_RSZ_SRC_MIN_WIDTH		32
#घोषणा RKISP1_RSZ_SRC_MIN_HEIGHT		16

/* the शेष width and height of all the entities */
#घोषणा RKISP1_DEFAULT_WIDTH		800
#घोषणा RKISP1_DEFAULT_HEIGHT		600

#घोषणा RKISP1_DRIVER_NAME	"rkisp1"
#घोषणा RKISP1_BUS_INFO		"platform:" RKISP1_DRIVER_NAME

/* maximum number of घड़ीs */
#घोषणा RKISP1_MAX_BUS_CLK	8

/* a biपंचांगask of the पढ़ोy stats */
#घोषणा RKISP1_STATS_MEAS_MASK		(RKISP1_CIF_ISP_AWB_DONE |	\
					 RKISP1_CIF_ISP_AFM_FIN |	\
					 RKISP1_CIF_ISP_EXP_END |	\
					 RKISP1_CIF_ISP_HIST_MEASURE_RDY)

/* क्रमागत क्रम the resizer pads */
क्रमागत rkisp1_rsz_pad अणु
	RKISP1_RSZ_PAD_SINK,
	RKISP1_RSZ_PAD_SRC,
	RKISP1_RSZ_PAD_MAX
पूर्ण;

/* क्रमागत क्रम the capture id */
क्रमागत rkisp1_stream_id अणु
	RKISP1_MAINPATH,
	RKISP1_SELFPATH,
पूर्ण;

/* bayer patterns */
क्रमागत rkisp1_fmt_raw_pat_type अणु
	RKISP1_RAW_RGGB = 0,
	RKISP1_RAW_GRBG,
	RKISP1_RAW_GBRG,
	RKISP1_RAW_BGGR,
पूर्ण;

/* क्रमागत क्रम the isp pads */
क्रमागत rkisp1_isp_pad अणु
	RKISP1_ISP_PAD_SINK_VIDEO,
	RKISP1_ISP_PAD_SINK_PARAMS,
	RKISP1_ISP_PAD_SOURCE_VIDEO,
	RKISP1_ISP_PAD_SOURCE_STATS,
	RKISP1_ISP_PAD_MAX
पूर्ण;

/*
 * काष्ठा rkisp1_sensor_async - A container क्रम the v4l2_async_subdev to add to the notअगरier
 *				of the v4l2-async API
 *
 * @asd:		async_subdev variable क्रम the sensor
 * @lanes:		number of lanes
 * @mbus_type:		type of bus (currently only CSI2 is supported)
 * @mbus_flags:		media bus (V4L2_MBUS_*) flags
 * @sd:			a poपूर्णांकer to v4l2_subdev काष्ठा of the sensor
 * @pixel_rate_ctrl:	pixel rate of the sensor, used to initialize the phy
 * @dphy:		a poपूर्णांकer to the phy
 */
काष्ठा rkisp1_sensor_async अणु
	काष्ठा v4l2_async_subdev asd;
	अचिन्हित पूर्णांक lanes;
	क्रमागत v4l2_mbus_type mbus_type;
	अचिन्हित पूर्णांक mbus_flags;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl *pixel_rate_ctrl;
	काष्ठा phy *dphy;
पूर्ण;

/*
 * काष्ठा rkisp1_isp - ISP subdev entity
 *
 * @sd:				v4l2_subdev variable
 * @rkisp1:			poपूर्णांकer to rkisp1_device
 * @pads:			media pads
 * @pad_cfg:			pads configurations
 * @sink_fmt:			input क्रमmat
 * @src_fmt:			output क्रमmat
 * @ops_lock:			ops serialization
 * @is_dphy_errctrl_disabled:	अगर dphy errctrl is disabled (aव्योम endless पूर्णांकerrupt)
 * @frame_sequence:		used to synchronize frame_id between video devices.
 */
काष्ठा rkisp1_isp अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[RKISP1_ISP_PAD_MAX];
	काष्ठा v4l2_subdev_pad_config pad_cfg[RKISP1_ISP_PAD_MAX];
	स्थिर काष्ठा rkisp1_isp_mbus_info *sink_fmt;
	स्थिर काष्ठा rkisp1_isp_mbus_info *src_fmt;
	काष्ठा mutex ops_lock; /* serialize the subdevice ops */
	bool is_dphy_errctrl_disabled;
	__u32 frame_sequence;
पूर्ण;

/*
 * काष्ठा rkisp1_vdev_node - Container क्रम the video nodes: params, stats, मुख्यpath, selfpath
 *
 * @buf_queue:	queue of buffers
 * @vlock:	lock of the video node
 * @vdev:	video node
 * @pad:	media pad
 */
काष्ठा rkisp1_vdev_node अणु
	काष्ठा vb2_queue buf_queue;
	काष्ठा mutex vlock; /* ioctl serialization mutex */
	काष्ठा video_device vdev;
	काष्ठा media_pad pad;
पूर्ण;

/*
 * काष्ठा rkisp1_buffer - A container क्रम the vb2 buffers used by the video devices:
 *			  params, stats, मुख्यpath, selfpath
 *
 * @vb:		vb2 buffer
 * @queue:	entry of the buffer in the queue
 * @buff_addr:	dma addresses of each plane, used only by the capture devices: selfpath, मुख्यpath
 * @vaddr:	भव address क्रम buffers used by params and stats devices
 */
काष्ठा rkisp1_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head queue;
	जोड़ अणु
		u32 buff_addr[VIDEO_MAX_PLANES];
		व्योम *vaddr;
	पूर्ण;
पूर्ण;

/*
 * काष्ठा rkisp1_dummy_buffer - A buffer to ग_लिखो the next frame to in हाल
 *				there are no vb2 buffers available.
 *
 * @vaddr:	वापस value of call to dma_alloc_attrs.
 * @dma_addr:	dma address of the buffer.
 * @size:	size of the buffer.
 */
काष्ठा rkisp1_dummy_buffer अणु
	व्योम *vaddr;
	dma_addr_t dma_addr;
	u32 size;
पूर्ण;

काष्ठा rkisp1_device;

/*
 * काष्ठा rkisp1_capture - ISP capture video device
 *
 * @vnode:	  video node
 * @rkisp1:	  poपूर्णांकer to rkisp1_device
 * @id:		  id of the capture, one of RKISP1_SELFPATH, RKISP1_MAINPATH
 * @ops:	  list of callbacks to configure the capture device.
 * @config:	  a poपूर्णांकer to the list of रेजिस्टरs to configure the capture क्रमmat.
 * @is_streaming: device is streaming
 * @is_stopping:  stop_streaming callback was called and the device is in the process of
 *		  stopping the streaming.
 * @करोne:	  when stop_streaming callback is called, the device रुकोs क्रम the next irq
 *		  handler to stop the streaming by रुकोing on the 'done' रुको queue.
 *		  If the irq handler is not called, the stream is stopped by the callback
 *		  after समयout.
 * @sp_y_stride:  the selfpath allows to configure a y stride that is दीर्घer than the image width.
 * @buf.lock:	  lock to protect buf.queue
 * @buf.queue:	  queued buffer list
 * @buf.dummy:	  dummy space to store dropped data
 *
 * rkisp1 uses shaकरोw रेजिस्टरs, so it needs two buffers at a समय
 * @buf.curr:	  the buffer used क्रम current frame
 * @buf.next:	  the buffer used क्रम next frame
 * @pix.cfg:	  pixel configuration
 * @pix.info:	  a poपूर्णांकer to the v4l2_क्रमmat_info of the pixel क्रमmat
 * @pix.fmt:	  buffer क्रमmat
 */
काष्ठा rkisp1_capture अणु
	काष्ठा rkisp1_vdev_node vnode;
	काष्ठा rkisp1_device *rkisp1;
	क्रमागत rkisp1_stream_id id;
	स्थिर काष्ठा rkisp1_capture_ops *ops;
	स्थिर काष्ठा rkisp1_capture_config *config;
	bool is_streaming;
	bool is_stopping;
	रुको_queue_head_t करोne;
	अचिन्हित पूर्णांक sp_y_stride;
	काष्ठा अणु
		/* protects queue, curr and next */
		spinlock_t lock;
		काष्ठा list_head queue;
		काष्ठा rkisp1_dummy_buffer dummy;
		काष्ठा rkisp1_buffer *curr;
		काष्ठा rkisp1_buffer *next;
	पूर्ण buf;
	काष्ठा अणु
		स्थिर काष्ठा rkisp1_capture_fmt_cfg *cfg;
		स्थिर काष्ठा v4l2_क्रमmat_info *info;
		काष्ठा v4l2_pix_क्रमmat_mplane fmt;
	पूर्ण pix;
पूर्ण;

/*
 * काष्ठा rkisp1_stats - ISP Statistics device
 *
 * @vnode:	  video node
 * @rkisp1:	  poपूर्णांकer to the rkisp1 device
 * @lock:	  locks the buffer list 'stat'
 * @stat:	  queue of rkisp1_buffer
 * @vdev_fmt:	  v4l2_क्रमmat of the metadata क्रमmat
 */
काष्ठा rkisp1_stats अणु
	काष्ठा rkisp1_vdev_node vnode;
	काष्ठा rkisp1_device *rkisp1;

	spinlock_t lock; /* locks the buffers list 'stats' */
	काष्ठा list_head stat;
	काष्ठा v4l2_क्रमmat vdev_fmt;
पूर्ण;

/*
 * काष्ठा rkisp1_params - ISP input parameters device
 *
 * @vnode:		video node
 * @rkisp1:		poपूर्णांकer to the rkisp1 device
 * @config_lock:	locks the buffer list 'params'
 * @params:		queue of rkisp1_buffer
 * @vdev_fmt:		v4l2_क्रमmat of the metadata क्रमmat
 * @quantization:	the quantization configured on the isp's src pad
 * @raw_type:		the bayer pattern on the isp video sink pad
 */
काष्ठा rkisp1_params अणु
	काष्ठा rkisp1_vdev_node vnode;
	काष्ठा rkisp1_device *rkisp1;

	spinlock_t config_lock; /* locks the buffers list 'params' */
	काष्ठा list_head params;
	काष्ठा v4l2_क्रमmat vdev_fmt;

	क्रमागत v4l2_quantization quantization;
	क्रमागत rkisp1_fmt_raw_pat_type raw_type;
पूर्ण;

/*
 * काष्ठा rkisp1_resizer - Resizer subdev
 *
 * @sd:	       v4l2_subdev variable
 * @id:	       id of the resizer, one of RKISP1_SELFPATH, RKISP1_MAINPATH
 * @rkisp1:    poपूर्णांकer to the rkisp1 device
 * @pads:      media pads
 * @pad_cfg:   configurations क्रम the pads
 * @config:    the set of रेजिस्टरs to configure the resizer
 * @pixel_enc: pixel encoding of the resizer
 * @ops_lock:  a lock क्रम the subdev ops
 */
काष्ठा rkisp1_resizer अणु
	काष्ठा v4l2_subdev sd;
	क्रमागत rkisp1_stream_id id;
	काष्ठा rkisp1_device *rkisp1;
	काष्ठा media_pad pads[RKISP1_RSZ_PAD_MAX];
	काष्ठा v4l2_subdev_pad_config pad_cfg[RKISP1_RSZ_PAD_MAX];
	स्थिर काष्ठा rkisp1_rsz_config *config;
	क्रमागत v4l2_pixel_encoding pixel_enc;
	काष्ठा mutex ops_lock; /* serialize the subdevice ops */
पूर्ण;

/*
 * काष्ठा rkisp1_debug - Values to be exposed on debugfs.
 *			 The parameters are counters of the number of बार the
 *			 event occurred since the driver was loaded.
 *
 * @data_loss:			  loss of data occurred within a line, processing failure
 * @outक्रमm_size_error:		  size error is generated in ouपंचांगux submodule
 * @img_stabilization_size_error: size error is generated in image stabilization submodule
 * @inक्रमm_size_err:		  size error is generated in inक्रमm submodule
 * @mipi_error:			  mipi error occurred
 * @stats_error:		  writing to the 'Interrupt clear register' did not clear
 *				  it in the रेजिस्टर 'Masked interrupt status'
 * @stop_समयout:		  upon stream stop, the capture रुकोs 1 second क्रम the isr to stop
 *				  the stream. This param is incremented in हाल of समयout.
 * @frame_drop:			  a frame was पढ़ोy but the buffer queue was empty so the frame
 *				  was not sent to userspace
 */
काष्ठा rkisp1_debug अणु
	काष्ठा dentry *debugfs_dir;
	अचिन्हित दीर्घ data_loss;
	अचिन्हित दीर्घ outक्रमm_size_error;
	अचिन्हित दीर्घ img_stabilization_size_error;
	अचिन्हित दीर्घ inक्रमm_size_error;
	अचिन्हित दीर्घ irq_delay;
	अचिन्हित दीर्घ mipi_error;
	अचिन्हित दीर्घ stats_error;
	अचिन्हित दीर्घ stop_समयout[2];
	अचिन्हित दीर्घ frame_drop[2];
पूर्ण;

/*
 * काष्ठा rkisp1_device - ISP platक्रमm device
 *
 * @base_addr:	   base रेजिस्टर address
 * @irq:	   the irq number
 * @dev:	   a poपूर्णांकer to the काष्ठा device
 * @clk_size:	   number of घड़ीs
 * @clks:	   array of घड़ीs
 * @v4l2_dev:	   v4l2_device variable
 * @media_dev:	   media_device variable
 * @notअगरier:	   a notअगरier to रेजिस्टर on the v4l2-async API to be notअगरied on the sensor
 * @active_sensor: sensor in-use, set when streaming on
 * @isp:	   ISP sub-device
 * @resizer_devs:  resizer sub-devices
 * @capture_devs:  capture devices
 * @stats:	   ISP statistics metadata capture device
 * @params:	   ISP parameters metadata output device
 * @pipe:	   media pipeline
 * @stream_lock:   serializes अणुstart/stopपूर्ण_streaming callbacks between the capture devices.
 * @debug:	   debug params to be exposed on debugfs
 */
काष्ठा rkisp1_device अणु
	व्योम __iomem *base_addr;
	पूर्णांक irq;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक clk_size;
	काष्ठा clk_bulk_data clks[RKISP1_MAX_BUS_CLK];
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा rkisp1_sensor_async *active_sensor;
	काष्ठा rkisp1_isp isp;
	काष्ठा rkisp1_resizer resizer_devs[2];
	काष्ठा rkisp1_capture capture_devs[2];
	काष्ठा rkisp1_stats stats;
	काष्ठा rkisp1_params params;
	काष्ठा media_pipeline pipe;
	काष्ठा mutex stream_lock; /* serialize अणुstart/stopपूर्ण_streaming cb between capture devices */
	काष्ठा rkisp1_debug debug;
पूर्ण;

/*
 * काष्ठा rkisp1_isp_mbus_info - ISP media bus info, Translates media bus code to hardware
 *				 क्रमmat values
 *
 * @mbus_code: media bus code
 * @pixel_enc: pixel encoding
 * @mipi_dt:   mipi data type
 * @yuv_seq:   the order of the Y, Cb, Cr values
 * @bus_width: bus width
 * @bayer_pat: bayer pattern
 * @direction: a biपंचांगask of the flags indicating on which pad the क्रमmat is supported on
 */
काष्ठा rkisp1_isp_mbus_info अणु
	u32 mbus_code;
	क्रमागत v4l2_pixel_encoding pixel_enc;
	u32 mipi_dt;
	u32 yuv_seq;
	u8 bus_width;
	क्रमागत rkisp1_fmt_raw_pat_type bayer_pat;
	अचिन्हित पूर्णांक direction;
पूर्ण;

अटल अंतरभूत व्योम
rkisp1_ग_लिखो(काष्ठा rkisp1_device *rkisp1, u32 val, अचिन्हित पूर्णांक addr)
अणु
	ग_लिखोl(val, rkisp1->base_addr + addr);
पूर्ण

अटल अंतरभूत u32 rkisp1_पढ़ो(काष्ठा rkisp1_device *rkisp1, अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोl(rkisp1->base_addr + addr);
पूर्ण

/*
 * rkisp1_cap_क्रमागत_mbus_codes - A helper function that वापस the i'th supported mbus code
 *				of the capture entity. This is used to क्रमागतerate the supported
 *				mbus codes on the source pad of the resizer.
 *
 * @cap:  the capture entity
 * @code: the mbus code, the function पढ़ोs the code->index and fills the code->code
 */
पूर्णांक rkisp1_cap_क्रमागत_mbus_codes(काष्ठा rkisp1_capture *cap,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code);

/*
 * rkisp1_sd_adjust_crop_rect - adjust a rectangle to fit पूर्णांकo another rectangle.
 *
 * @crop:   rectangle to adjust.
 * @bounds: rectangle used as bounds.
 */
व्योम rkisp1_sd_adjust_crop_rect(काष्ठा v4l2_rect *crop,
				स्थिर काष्ठा v4l2_rect *bounds);

/*
 * rkisp1_sd_adjust_crop - adjust a rectangle to fit पूर्णांकo media bus क्रमmat
 *
 * @crop:   rectangle to adjust.
 * @bounds: media bus क्रमmat used as bounds.
 */
व्योम rkisp1_sd_adjust_crop(काष्ठा v4l2_rect *crop,
			   स्थिर काष्ठा v4l2_mbus_framefmt *bounds);

/*
 * rkisp1_isp_mbus_info - get the isp info of the media bus code
 *
 * @mbus_code: the media bus code
 */
स्थिर काष्ठा rkisp1_isp_mbus_info *rkisp1_isp_mbus_info_get(u32 mbus_code);

/* rkisp1_params_configure - configure the params when stream starts.
 *			     This function is called by the isp entity upon stream starts.
 *			     The function applies the initial configuration of the parameters.
 *
 * @params:	  poपूर्णांकer to rkisp1_params.
 * @bayer_pat:	  the bayer pattern on the isp video sink pad
 * @quantization: the quantization configured on the isp's src pad
 */
व्योम rkisp1_params_configure(काष्ठा rkisp1_params *params,
			     क्रमागत rkisp1_fmt_raw_pat_type bayer_pat,
			     क्रमागत v4l2_quantization quantization);

/* rkisp1_params_disable - disable all parameters.
 *			   This function is called by the isp entity upon stream start
 *			   when capturing bayer क्रमmat.
 *
 * @params: poपूर्णांकer to rkisp1_params.
 */
व्योम rkisp1_params_disable(काष्ठा rkisp1_params *params);

/* irq handlers */
व्योम rkisp1_isp_isr(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_mipi_isr(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_capture_isr(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_stats_isr(काष्ठा rkisp1_stats *stats, u32 isp_ris);
व्योम rkisp1_params_isr(काष्ठा rkisp1_device *rkisp1);

/* रेजिस्टर/unरेजिस्टरs functions of the entities */
पूर्णांक rkisp1_capture_devs_रेजिस्टर(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_capture_devs_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1);

पूर्णांक rkisp1_isp_रेजिस्टर(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_isp_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1);

पूर्णांक rkisp1_resizer_devs_रेजिस्टर(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_resizer_devs_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1);

पूर्णांक rkisp1_stats_रेजिस्टर(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_stats_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1);

पूर्णांक rkisp1_params_रेजिस्टर(काष्ठा rkisp1_device *rkisp1);
व्योम rkisp1_params_unरेजिस्टर(काष्ठा rkisp1_device *rkisp1);

#पूर्ण_अगर /* _RKISP1_COMMON_H */
