<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 *         Rick Chang <rick.chang@mediatek.com>
 *         Xia Jiang <xia.jiang@mediatek.com>
 */

#अगर_अघोषित _MTK_JPEG_CORE_H
#घोषणा _MTK_JPEG_CORE_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>

#घोषणा MTK_JPEG_NAME		"mtk-jpeg"

#घोषणा MTK_JPEG_COMP_MAX		3

#घोषणा MTK_JPEG_FMT_FLAG_OUTPUT	BIT(0)
#घोषणा MTK_JPEG_FMT_FLAG_CAPTURE	BIT(1)

#घोषणा MTK_JPEG_MIN_WIDTH	32U
#घोषणा MTK_JPEG_MIN_HEIGHT	32U
#घोषणा MTK_JPEG_MAX_WIDTH	65535U
#घोषणा MTK_JPEG_MAX_HEIGHT	65535U

#घोषणा MTK_JPEG_DEFAULT_SIZEIMAGE	(1 * 1024 * 1024)

#घोषणा MTK_JPEG_HW_TIMEOUT_MSEC 1000

#घोषणा MTK_JPEG_MAX_EXIF_SIZE	(64 * 1024)

/**
 * क्रमागत mtk_jpeg_ctx_state - states of the context state machine
 * @MTK_JPEG_INIT:		current state is initialized
 * @MTK_JPEG_RUNNING:		current state is running
 * @MTK_JPEG_SOURCE_CHANGE:	current state is source resolution change
 */
क्रमागत mtk_jpeg_ctx_state अणु
	MTK_JPEG_INIT = 0,
	MTK_JPEG_RUNNING,
	MTK_JPEG_SOURCE_CHANGE,
पूर्ण;

/**
 * काष्ठा mtk_jpeg_variant - mtk jpeg driver variant
 * @clks:			घड़ी names
 * @num_clks:			numbers of घड़ी
 * @क्रमmats:			jpeg driver's पूर्णांकernal color क्रमmat
 * @num_क्रमmats:		number of क्रमmats
 * @qops:			the callback of jpeg vb2_ops
 * @irq_handler:		jpeg irq handler callback
 * @hw_reset:			jpeg hardware reset callback
 * @m2m_ops:			the callback of jpeg v4l2_m2m_ops
 * @dev_name:			jpeg device name
 * @ioctl_ops:			the callback of jpeg v4l2_ioctl_ops
 * @out_q_शेष_fourcc:	output queue शेष fourcc
 * @cap_q_शेष_fourcc:	capture queue शेष fourcc
 */
काष्ठा mtk_jpeg_variant अणु
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	काष्ठा mtk_jpeg_fmt *क्रमmats;
	पूर्णांक num_क्रमmats;
	स्थिर काष्ठा vb2_ops *qops;
	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *priv);
	व्योम (*hw_reset)(व्योम __iomem *base);
	स्थिर काष्ठा v4l2_m2m_ops *m2m_ops;
	स्थिर अक्षर *dev_name;
	स्थिर काष्ठा v4l2_ioctl_ops *ioctl_ops;
	u32 out_q_शेष_fourcc;
	u32 cap_q_शेष_fourcc;
पूर्ण;

/**
 * काष्ठा mtk_jpeg_dev - JPEG IP असलtraction
 * @lock:		the mutex protecting this काष्ठाure
 * @hw_lock:		spinlock protecting the hw device resource
 * @workqueue:		decode work queue
 * @dev:		JPEG device
 * @v4l2_dev:		v4l2 device क्रम mem2mem mode
 * @m2m_dev:		v4l2 mem2mem device data
 * @alloc_ctx:		videobuf2 memory allocator's context
 * @vdev:		video device node क्रम jpeg mem2mem mode
 * @reg_base:		JPEG रेजिस्टरs mapping
 * @larb:		SMI device
 * @job_समयout_work:	IRQ समयout काष्ठाure
 * @variant:		driver variant to be used
 */
काष्ठा mtk_jpeg_dev अणु
	काष्ठा mutex		lock;
	spinlock_t		hw_lock;
	काष्ठा workqueue_काष्ठा	*workqueue;
	काष्ठा device		*dev;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	व्योम			*alloc_ctx;
	काष्ठा video_device	*vdev;
	व्योम __iomem		*reg_base;
	काष्ठा device		*larb;
	काष्ठा delayed_work job_समयout_work;
	स्थिर काष्ठा mtk_jpeg_variant *variant;
पूर्ण;

/**
 * काष्ठा mtk_jpeg_fmt - driver's पूर्णांकernal color क्रमmat data
 * @fourcc:	the fourcc code, 0 अगर not applicable
 * @hw_क्रमmat:	hardware क्रमmat value
 * @h_sample:	horizontal sample count of plane in 4 * 4 pixel image
 * @v_sample:	vertical sample count of plane in 4 * 4 pixel image
 * @colplanes:	number of color planes (1 क्रम packed क्रमmats)
 * @h_align:	horizontal alignment order (align to 2^h_align)
 * @v_align:	vertical alignment order (align to 2^v_align)
 * @flags:	flags describing क्रमmat applicability
 */
काष्ठा mtk_jpeg_fmt अणु
	u32	fourcc;
	u32	hw_क्रमmat;
	पूर्णांक	h_sample[VIDEO_MAX_PLANES];
	पूर्णांक	v_sample[VIDEO_MAX_PLANES];
	पूर्णांक	colplanes;
	पूर्णांक	h_align;
	पूर्णांक	v_align;
	u32	flags;
पूर्ण;

/**
 * काष्ठा mtk_jpeg_q_data - parameters of one queue
 * @fmt:	  driver-specअगरic क्रमmat of this queue
 * @pix_mp:	  multiplanar क्रमmat
 * @enc_crop_rect:	jpeg encoder crop inक्रमmation
 */
काष्ठा mtk_jpeg_q_data अणु
	काष्ठा mtk_jpeg_fmt	*fmt;
	काष्ठा v4l2_pix_क्रमmat_mplane pix_mp;
	काष्ठा v4l2_rect enc_crop_rect;
पूर्ण;

/**
 * काष्ठा mtk_jpeg_ctx - the device context data
 * @jpeg:		JPEG IP device क्रम this context
 * @out_q:		source (output) queue inक्रमmation
 * @cap_q:		destination (capture) queue queue inक्रमmation
 * @fh:			V4L2 file handle
 * @state:		state of the context
 * @enable_exअगर:	enable exअगर mode of jpeg encoder
 * @enc_quality:	jpeg encoder quality
 * @restart_पूर्णांकerval:	jpeg encoder restart पूर्णांकerval
 * @ctrl_hdl:		controls handler
 */
काष्ठा mtk_jpeg_ctx अणु
	काष्ठा mtk_jpeg_dev		*jpeg;
	काष्ठा mtk_jpeg_q_data		out_q;
	काष्ठा mtk_jpeg_q_data		cap_q;
	काष्ठा v4l2_fh			fh;
	क्रमागत mtk_jpeg_ctx_state		state;
	bool enable_exअगर;
	u8 enc_quality;
	u8 restart_पूर्णांकerval;
	काष्ठा v4l2_ctrl_handler ctrl_hdl;
पूर्ण;

#पूर्ण_अगर /* _MTK_JPEG_CORE_H */
