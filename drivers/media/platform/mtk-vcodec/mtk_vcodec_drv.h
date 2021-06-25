<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
* Copyright (c) 2016 MediaTek Inc.
* Author: PC Chen <pc.chen@mediatek.com>
*         Tअगरfany Lin <tअगरfany.lin@mediatek.com>
*/

#अगर_अघोषित _MTK_VCODEC_DRV_H_
#घोषणा _MTK_VCODEC_DRV_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-core.h>
#समावेश "mtk_vcodec_util.h"

#घोषणा MTK_VCODEC_DRV_NAME	"mtk_vcodec_drv"
#घोषणा MTK_VCODEC_DEC_NAME	"mtk-vcodec-dec"
#घोषणा MTK_VCODEC_ENC_NAME	"mtk-vcodec-enc"
#घोषणा MTK_PLATFORM_STR	"platform:mt8173"

#घोषणा MTK_VCODEC_MAX_PLANES	3
#घोषणा MTK_V4L2_BENCHMARK	0
#घोषणा WAIT_INTR_TIMEOUT_MS	1000

/**
 * क्रमागत mtk_hw_reg_idx - MTK hw रेजिस्टर base index
 */
क्रमागत mtk_hw_reg_idx अणु
	VDEC_SYS,
	VDEC_MISC,
	VDEC_LD,
	VDEC_TOP,
	VDEC_CM,
	VDEC_AD,
	VDEC_AV,
	VDEC_PP,
	VDEC_HWD,
	VDEC_HWQ,
	VDEC_HWB,
	VDEC_HWG,
	NUM_MAX_VDEC_REG_BASE,
	/* h264 encoder */
	VENC_SYS = NUM_MAX_VDEC_REG_BASE,
	/* vp8 encoder */
	VENC_LT_SYS,
	NUM_MAX_VCODEC_REG_BASE
पूर्ण;

/**
 * क्रमागत mtk_instance_type - The type of an MTK Vcodec instance.
 */
क्रमागत mtk_instance_type अणु
	MTK_INST_DECODER		= 0,
	MTK_INST_ENCODER		= 1,
पूर्ण;

/**
 * क्रमागत mtk_instance_state - The state of an MTK Vcodec instance.
 * @MTK_STATE_FREE: शेष state when instance is created
 * @MTK_STATE_INIT: vcodec instance is initialized
 * @MTK_STATE_HEADER: vdec had sps/pps header parsed or venc
 *			had sps/pps header encoded
 * @MTK_STATE_FLUSH: vdec is flushing. Only used by decoder
 * @MTK_STATE_ABORT: vcodec should be पातed
 */
क्रमागत mtk_instance_state अणु
	MTK_STATE_FREE = 0,
	MTK_STATE_INIT = 1,
	MTK_STATE_HEADER = 2,
	MTK_STATE_FLUSH = 3,
	MTK_STATE_ABORT = 4,
पूर्ण;

/**
 * क्रमागत mtk_encode_param - General encoding parameters type
 */
क्रमागत mtk_encode_param अणु
	MTK_ENCODE_PARAM_NONE = 0,
	MTK_ENCODE_PARAM_BITRATE = (1 << 0),
	MTK_ENCODE_PARAM_FRAMERATE = (1 << 1),
	MTK_ENCODE_PARAM_INTRA_PERIOD = (1 << 2),
	MTK_ENCODE_PARAM_FORCE_INTRA = (1 << 3),
	MTK_ENCODE_PARAM_GOP_SIZE = (1 << 4),
पूर्ण;

क्रमागत mtk_fmt_type अणु
	MTK_FMT_DEC = 0,
	MTK_FMT_ENC = 1,
	MTK_FMT_FRAME = 2,
पूर्ण;

/**
 * काष्ठा mtk_video_fmt - Structure used to store inक्रमmation about pixelक्रमmats
 */
काष्ठा mtk_video_fmt अणु
	u32	fourcc;
	क्रमागत mtk_fmt_type	type;
	u32	num_planes;
	u32	flags;
पूर्ण;

/**
 * काष्ठा mtk_codec_framesizes - Structure used to store inक्रमmation about
 *							framesizes
 */
काष्ठा mtk_codec_framesizes अणु
	u32	fourcc;
	काष्ठा	v4l2_frmsize_stepwise	stepwise;
पूर्ण;

/**
 * क्रमागत mtk_q_type - Type of queue
 */
क्रमागत mtk_q_type अणु
	MTK_Q_DATA_SRC = 0,
	MTK_Q_DATA_DST = 1,
पूर्ण;

/**
 * काष्ठा mtk_q_data - Structure used to store inक्रमmation about queue
 */
काष्ठा mtk_q_data अणु
	अचिन्हित पूर्णांक	visible_width;
	अचिन्हित पूर्णांक	visible_height;
	अचिन्हित पूर्णांक	coded_width;
	अचिन्हित पूर्णांक	coded_height;
	क्रमागत v4l2_field	field;
	अचिन्हित पूर्णांक	bytesperline[MTK_VCODEC_MAX_PLANES];
	अचिन्हित पूर्णांक	sizeimage[MTK_VCODEC_MAX_PLANES];
	स्थिर काष्ठा mtk_video_fmt	*fmt;
पूर्ण;

/**
 * काष्ठा mtk_enc_params - General encoding parameters
 * @bitrate: target bitrate in bits per second
 * @num_b_frame: number of b frames between p-frame
 * @rc_frame: frame based rate control
 * @rc_mb: macroblock based rate control
 * @seq_hdr_mode: H.264 sequence header is encoded separately or joined
 *		  with the first frame
 * @पूर्णांकra_period: I frame period
 * @gop_size: group of picture size, it's used as the पूर्णांकra frame period
 * @framerate_num: frame rate numerator. ex: framerate_num=30 and
 *		   framerate_denom=1 means FPS is 30
 * @framerate_denom: frame rate denominator. ex: framerate_num=30 and
 *		     framerate_denom=1 means FPS is 30
 * @h264_max_qp: Max value क्रम H.264 quantization parameter
 * @h264_profile: V4L2 defined H.264 profile
 * @h264_level: V4L2 defined H.264 level
 * @क्रमce_पूर्णांकra: क्रमce/insert पूर्णांकra frame
 */
काष्ठा mtk_enc_params अणु
	अचिन्हित पूर्णांक	bitrate;
	अचिन्हित पूर्णांक	num_b_frame;
	अचिन्हित पूर्णांक	rc_frame;
	अचिन्हित पूर्णांक	rc_mb;
	अचिन्हित पूर्णांक	seq_hdr_mode;
	अचिन्हित पूर्णांक	पूर्णांकra_period;
	अचिन्हित पूर्णांक	gop_size;
	अचिन्हित पूर्णांक	framerate_num;
	अचिन्हित पूर्णांक	framerate_denom;
	अचिन्हित पूर्णांक	h264_max_qp;
	अचिन्हित पूर्णांक	h264_profile;
	अचिन्हित पूर्णांक	h264_level;
	अचिन्हित पूर्णांक	क्रमce_पूर्णांकra;
पूर्ण;

/**
 * काष्ठा mtk_vcodec_clk_info - Structure used to store घड़ी name
 */
काष्ठा mtk_vcodec_clk_info अणु
	स्थिर अक्षर	*clk_name;
	काष्ठा clk	*vcodec_clk;
पूर्ण;

/**
 * काष्ठा mtk_vcodec_clk - Structure used to store vcodec घड़ी inक्रमmation
 */
काष्ठा mtk_vcodec_clk अणु
	काष्ठा mtk_vcodec_clk_info	*clk_info;
	पूर्णांक	clk_num;
पूर्ण;

/**
 * काष्ठा mtk_vcodec_pm - Power management data काष्ठाure
 */
काष्ठा mtk_vcodec_pm अणु
	काष्ठा mtk_vcodec_clk	vdec_clk;
	काष्ठा device	*larbvdec;

	काष्ठा mtk_vcodec_clk	venc_clk;
	काष्ठा device	*larbvenc;
	काष्ठा device	*dev;
	काष्ठा mtk_vcodec_dev	*mtkdev;
पूर्ण;

/**
 * काष्ठा vdec_pic_info  - picture size inक्रमmation
 * @pic_w: picture width
 * @pic_h: picture height
 * @buf_w: picture buffer width (64 aligned up from pic_w)
 * @buf_h: picture buffer heiht (64 aligned up from pic_h)
 * @fb_sz: bitstream size of each plane
 * E.g. suppose picture size is 176x144,
 *      buffer size will be aligned to 176x160.
 * @cap_fourcc: fourcc number(may changed when resolution change)
 * @reserved: align काष्ठा to 64-bit in order to adjust 32-bit and 64-bit os.
 */
काष्ठा vdec_pic_info अणु
	अचिन्हित पूर्णांक pic_w;
	अचिन्हित पूर्णांक pic_h;
	अचिन्हित पूर्णांक buf_w;
	अचिन्हित पूर्णांक buf_h;
	अचिन्हित पूर्णांक fb_sz[VIDEO_MAX_PLANES];
	अचिन्हित पूर्णांक cap_fourcc;
	अचिन्हित पूर्णांक reserved;
पूर्ण;

/**
 * काष्ठा mtk_vcodec_ctx - Context (instance) निजी data.
 *
 * @type: type of the instance - decoder or encoder
 * @dev: poपूर्णांकer to the mtk_vcodec_dev of the device
 * @list: link to ctx_list of mtk_vcodec_dev
 * @fh: काष्ठा v4l2_fh
 * @m2m_ctx: poपूर्णांकer to the v4l2_m2m_ctx of the context
 * @q_data: store inक्रमmation of input and output queue
 *	    of the context
 * @id: index of the context that this काष्ठाure describes
 * @state: state of the context
 * @param_change: indicate encode parameter type
 * @enc_params: encoding parameters
 * @dec_अगर: hooked decoder driver पूर्णांकerface
 * @enc_अगर: hoooked encoder driver पूर्णांकerface
 * @drv_handle: driver handle क्रम specअगरic decode/encode instance
 *
 * @picinfo: store picture info after header parsing
 * @dpb_size: store dpb count after header parsing
 * @पूर्णांक_cond: variable used by the रुकोqueue
 * @पूर्णांक_type: type of the last पूर्णांकerrupt
 * @queue: रुकोqueue that can be used to रुको क्रम this context to
 *	   finish
 * @irq_status: irq status
 *
 * @ctrl_hdl: handler क्रम v4l2 framework
 * @decode_work: worker क्रम the decoding
 * @encode_work: worker क्रम the encoding
 * @last_decoded_picinfo: pic inक्रमmation get from latest decode
 * @empty_flush_buf: a fake size-0 capture buffer that indicates flush
 *
 * @colorspace: क्रमागत v4l2_colorspace; supplemental to pixelक्रमmat
 * @ycbcr_enc: क्रमागत v4l2_ycbcr_encoding, Y'CbCr encoding
 * @quantization: क्रमागत v4l2_quantization, colorspace quantization
 * @xfer_func: क्रमागत v4l2_xfer_func, colorspace transfer function
 * @lock: protect variables accessed by V4L2 thपढ़ोs and worker thपढ़ो such as
 *	  mtk_video_dec_buf.
 */
काष्ठा mtk_vcodec_ctx अणु
	क्रमागत mtk_instance_type type;
	काष्ठा mtk_vcodec_dev *dev;
	काष्ठा list_head list;

	काष्ठा v4l2_fh fh;
	काष्ठा v4l2_m2m_ctx *m2m_ctx;
	काष्ठा mtk_q_data q_data[2];
	पूर्णांक id;
	क्रमागत mtk_instance_state state;
	क्रमागत mtk_encode_param param_change;
	काष्ठा mtk_enc_params enc_params;

	स्थिर काष्ठा vdec_common_अगर *dec_अगर;
	स्थिर काष्ठा venc_common_अगर *enc_अगर;
	व्योम *drv_handle;

	काष्ठा vdec_pic_info picinfo;
	पूर्णांक dpb_size;

	पूर्णांक पूर्णांक_cond;
	पूर्णांक पूर्णांक_type;
	रुको_queue_head_t queue;
	अचिन्हित पूर्णांक irq_status;

	काष्ठा v4l2_ctrl_handler ctrl_hdl;
	काष्ठा work_काष्ठा decode_work;
	काष्ठा work_काष्ठा encode_work;
	काष्ठा vdec_pic_info last_decoded_picinfo;
	काष्ठा mtk_video_dec_buf *empty_flush_buf;

	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
	क्रमागत v4l2_xfer_func xfer_func;

	पूर्णांक decoded_frame_cnt;
	काष्ठा mutex lock;

पूर्ण;

क्रमागत mtk_chip अणु
	MTK_MT8173,
	MTK_MT8183,
पूर्ण;

/**
 * काष्ठा mtk_vcodec_enc_pdata - compatible data क्रम each IC
 *
 * @chip: chip this encoder is compatible with
 *
 * @uses_ext: whether the encoder uses the extended firmware messaging क्रमmat
 * @min_birate: minimum supported encoding bitrate
 * @max_bitrate: maximum supported encoding bitrate
 * @capture_क्रमmats: array of supported capture क्रमmats
 * @num_capture_क्रमmats: number of entries in capture_क्रमmats
 * @output_क्रमmats: array of supported output क्रमmats
 * @num_output_क्रमmats: number of entries in output_क्रमmats
 * @core_id: stand क्रम h264 or vp8 encode index
 */
काष्ठा mtk_vcodec_enc_pdata अणु
	क्रमागत mtk_chip chip;

	bool uses_ext;
	अचिन्हित दीर्घ min_bitrate;
	अचिन्हित दीर्घ max_bitrate;
	स्थिर काष्ठा mtk_video_fmt *capture_क्रमmats;
	माप_प्रकार num_capture_क्रमmats;
	स्थिर काष्ठा mtk_video_fmt *output_क्रमmats;
	माप_प्रकार num_output_क्रमmats;
	पूर्णांक core_id;
पूर्ण;

#घोषणा MTK_ENC_CTX_IS_EXT(ctx) ((ctx)->dev->venc_pdata->uses_ext)

/**
 * काष्ठा mtk_vcodec_dev - driver data
 * @v4l2_dev: V4L2 device to रेजिस्टर video devices क्रम.
 * @vfd_dec: Video device क्रम decoder
 * @vfd_enc: Video device क्रम encoder.
 *
 * @m2m_dev_dec: m2m device क्रम decoder
 * @m2m_dev_enc: m2m device क्रम encoder.
 * @plat_dev: platक्रमm device
 * @ctx_list: list of काष्ठा mtk_vcodec_ctx
 * @irqlock: protect data access by irq handler and work thपढ़ो
 * @curr_ctx: The context that is रुकोing क्रम codec hardware
 *
 * @reg_base: Mapped address of MTK Vcodec रेजिस्टरs.
 *
 * @fw_handler: used to communicate with the firmware.
 * @id_counter: used to identअगरy current खोलोed instance
 *
 * @encode_workqueue: encode work queue
 *
 * @पूर्णांक_cond: used to identअगरy पूर्णांकerrupt condition happen
 * @पूर्णांक_type: used to identअगरy what kind of पूर्णांकerrupt condition happen
 * @dev_mutex: video_device lock
 * @queue: रुकोqueue क्रम रुकोing क्रम completion of device commands
 *
 * @dec_irq: decoder irq resource
 * @enc_irq: h264 encoder irq resource
 *
 * @dec_mutex: decoder hardware lock
 * @enc_mutex: encoder hardware lock.
 *
 * @pm: घातer management control
 * @dec_capability: used to identअगरy decode capability, ex: 4k
 * @enc_capability: used to identअगरy encode capability
 */
काष्ठा mtk_vcodec_dev अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device *vfd_dec;
	काष्ठा video_device *vfd_enc;

	काष्ठा v4l2_m2m_dev *m2m_dev_dec;
	काष्ठा v4l2_m2m_dev *m2m_dev_enc;
	काष्ठा platक्रमm_device *plat_dev;
	काष्ठा list_head ctx_list;
	spinlock_t irqlock;
	काष्ठा mtk_vcodec_ctx *curr_ctx;
	व्योम __iomem *reg_base[NUM_MAX_VCODEC_REG_BASE];
	स्थिर काष्ठा mtk_vcodec_enc_pdata *venc_pdata;

	काष्ठा mtk_vcodec_fw *fw_handler;

	अचिन्हित दीर्घ id_counter;

	काष्ठा workqueue_काष्ठा *decode_workqueue;
	काष्ठा workqueue_काष्ठा *encode_workqueue;
	पूर्णांक पूर्णांक_cond;
	पूर्णांक पूर्णांक_type;
	काष्ठा mutex dev_mutex;
	रुको_queue_head_t queue;

	पूर्णांक dec_irq;
	पूर्णांक enc_irq;

	काष्ठा mutex dec_mutex;
	काष्ठा mutex enc_mutex;

	काष्ठा mtk_vcodec_pm pm;
	अचिन्हित पूर्णांक dec_capability;
	अचिन्हित पूर्णांक enc_capability;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_vcodec_ctx *fh_to_ctx(काष्ठा v4l2_fh *fh)
अणु
	वापस container_of(fh, काष्ठा mtk_vcodec_ctx, fh);
पूर्ण

अटल अंतरभूत काष्ठा mtk_vcodec_ctx *ctrl_to_ctx(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस container_of(ctrl->handler, काष्ठा mtk_vcodec_ctx, ctrl_hdl);
पूर्ण

#पूर्ण_अगर /* _MTK_VCODEC_DRV_H_ */
