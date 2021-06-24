<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_CORE_H_
#घोषणा __MESON_VDEC_CORE_H_

#समावेश <linux/irqवापस.h>
#समावेश <linux/regmap.h>
#समावेश <linux/list.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <linux/soc/amlogic/meson-canvas.h>

#समावेश "vdec_platform.h"

/* 32 buffers in 3-plane YUV420 */
#घोषणा MAX_CANVAS (32 * 3)

काष्ठा amvdec_buffer अणु
	काष्ठा list_head list;
	काष्ठा vb2_buffer *vb;
पूर्ण;

/**
 * काष्ठा amvdec_बारtamp - stores a src बारtamp aदीर्घ with a VIFIFO offset
 *
 * @list: used to make lists out of this काष्ठा
 * @tc: समयcode from the v4l2 buffer
 * @ts: बारtamp from the VB2 buffer
 * @offset: offset in the VIFIFO where the associated packet was written
 * @flags: flags from the v4l2 buffer
 * @used_count: बार this बारtamp was checked क्रम a match with a dst buffer
 */
काष्ठा amvdec_बारtamp अणु
	काष्ठा list_head list;
	काष्ठा v4l2_समयcode tc;
	u64 ts;
	u32 offset;
	u32 flags;
	u32 used_count;
पूर्ण;

काष्ठा amvdec_session;

/**
 * काष्ठा amvdec_core - device parameters, singleton
 *
 * @करोs_base: DOS memory base address
 * @esparser_base: PARSER memory base address
 * @regmap_ao: regmap क्रम the AO bus
 * @dev: core device
 * @dev_dec: decoder device
 * @platक्रमm: platक्रमm-specअगरic data
 * @canvas: canvas provider reference
 * @करोs_parser_clk: DOS_PARSER घड़ी
 * @करोs_clk: DOS घड़ी
 * @vdec_1_clk: VDEC_1 घड़ी
 * @vdec_hevc_clk: VDEC_HEVC घड़ी
 * @esparser_reset: RESET क्रम the PARSER
 * @vdec_dec: video device क्रम the decoder
 * @v4l2_dev: v4l2 device
 * @cur_sess: current decoding session
 */
काष्ठा amvdec_core अणु
	व्योम __iomem *करोs_base;
	व्योम __iomem *esparser_base;
	काष्ठा regmap *regmap_ao;

	काष्ठा device *dev;
	काष्ठा device *dev_dec;
	स्थिर काष्ठा vdec_platक्रमm *platक्रमm;

	काष्ठा meson_canvas *canvas;

	काष्ठा clk *करोs_parser_clk;
	काष्ठा clk *करोs_clk;
	काष्ठा clk *vdec_1_clk;
	काष्ठा clk *vdec_hevc_clk;
	काष्ठा clk *vdec_hevcf_clk;

	काष्ठा reset_control *esparser_reset;

	काष्ठा video_device *vdev_dec;
	काष्ठा v4l2_device v4l2_dev;

	काष्ठा amvdec_session *cur_sess;
	काष्ठा mutex lock; /* video device lock */
पूर्ण;

/**
 * काष्ठा amvdec_ops - vdec operations
 *
 * @start: mandatory call when the vdec needs to initialize
 * @stop: mandatory call when the vdec needs to stop
 * @conf_esparser: mandatory call to let the vdec configure the ESPARSER
 * @vअगरअगरo_level: mandatory call to get the current amount of data
 *		  in the VIFIFO
 * @use_offsets: mandatory call. Returns 1 अगर the VDEC supports vअगरअगरo offsets
 */
काष्ठा amvdec_ops अणु
	पूर्णांक (*start)(काष्ठा amvdec_session *sess);
	पूर्णांक (*stop)(काष्ठा amvdec_session *sess);
	व्योम (*conf_esparser)(काष्ठा amvdec_session *sess);
	u32 (*vअगरअगरo_level)(काष्ठा amvdec_session *sess);
पूर्ण;

/**
 * काष्ठा amvdec_codec_ops - codec operations
 *
 * @start: mandatory call when the codec needs to initialize
 * @stop: mandatory call when the codec needs to stop
 * @load_extended_firmware: optional call to load additional firmware bits
 * @num_pending_bufs: optional call to get the number of dst buffers on hold
 * @can_recycle: optional call to know अगर the codec is पढ़ोy to recycle
 *		 a dst buffer
 * @recycle: optional call to tell the codec to recycle a dst buffer. Must go
 *	     in pair with @can_recycle
 * @drain: optional call अगर the codec has a custom way of draining
 * @eos_sequence: optional call to get an end sequence to send to esparser
 *		  क्रम flush. Mutually exclusive with @drain.
 * @isr: mandatory call when the ISR triggers
 * @thपढ़ोed_isr: mandatory call क्रम the thपढ़ोed ISR
 */
काष्ठा amvdec_codec_ops अणु
	पूर्णांक (*start)(काष्ठा amvdec_session *sess);
	पूर्णांक (*stop)(काष्ठा amvdec_session *sess);
	पूर्णांक (*load_extended_firmware)(काष्ठा amvdec_session *sess,
				      स्थिर u8 *data, u32 len);
	u32 (*num_pending_bufs)(काष्ठा amvdec_session *sess);
	पूर्णांक (*can_recycle)(काष्ठा amvdec_core *core);
	व्योम (*recycle)(काष्ठा amvdec_core *core, u32 buf_idx);
	व्योम (*drain)(काष्ठा amvdec_session *sess);
	व्योम (*resume)(काष्ठा amvdec_session *sess);
	स्थिर u8 * (*eos_sequence)(u32 *len);
	irqवापस_t (*isr)(काष्ठा amvdec_session *sess);
	irqवापस_t (*thपढ़ोed_isr)(काष्ठा amvdec_session *sess);
पूर्ण;

/**
 * काष्ठा amvdec_क्रमmat - describes one of the OUTPUT (src) क्रमmat supported
 *
 * @pixfmt: V4L2 pixel क्रमmat
 * @min_buffers: minimum amount of CAPTURE (dst) buffers
 * @max_buffers: maximum amount of CAPTURE (dst) buffers
 * @max_width: maximum picture width supported
 * @max_height: maximum picture height supported
 * @flags: क्रमागत flags associated with this pixfmt
 * @vdec_ops: the VDEC operations that support this क्रमmat
 * @codec_ops: the codec operations that support this क्रमmat
 * @firmware_path: Path to the firmware that supports this क्रमmat
 * @pixfmts_cap: list of CAPTURE pixel क्रमmats available with pixfmt
 */
काष्ठा amvdec_क्रमmat अणु
	u32 pixfmt;
	u32 min_buffers;
	u32 max_buffers;
	u32 max_width;
	u32 max_height;
	u32 flags;

	काष्ठा amvdec_ops *vdec_ops;
	काष्ठा amvdec_codec_ops *codec_ops;

	अक्षर *firmware_path;
	u32 pixfmts_cap[4];
पूर्ण;

क्रमागत amvdec_status अणु
	STATUS_STOPPED,
	STATUS_INIT,
	STATUS_RUNNING,
	STATUS_NEEDS_RESUME,
पूर्ण;

/**
 * काष्ठा amvdec_session - decoding session parameters
 *
 * @core: reference to the vdec core काष्ठा
 * @fh: v4l2 file handle
 * @m2m_dev: v4l2 m2m device
 * @m2m_ctx: v4l2 m2m context
 * @ctrl_handler: V4L2 control handler
 * @ctrl_min_buf_capture: V4L2 control V4L2_CID_MIN_BUFFERS_FOR_CAPTURE
 * @fmt_out: vdec pixel क्रमmat क्रम the OUTPUT queue
 * @pixfmt_cap: V4L2 pixel क्रमmat क्रम the CAPTURE queue
 * @src_buffer_size: size in bytes of the OUTPUT buffers' only plane
 * @width: current picture width
 * @height: current picture height
 * @colorspace: current colorspace
 * @ycbcr_enc: current ycbcr_enc
 * @quantization: current quantization
 * @xfer_func: current transfer function
 * @pixelaspect: Pixel Aspect Ratio reported by the decoder
 * @esparser_queued_bufs: number of buffers currently queued पूर्णांकo ESPARSER
 * @esparser_queue_work: work काष्ठा क्रम the ESPARSER to process src buffers
 * @streamon_cap: stream on flag क्रम capture queue
 * @streamon_out: stream on flag क्रम output queue
 * @sequence_cap: capture sequence counter
 * @should_stop: flag set अगर userspace संकेतed EOS via command
 *		 or empty buffer
 * @keyframe_found: flag set once a keyframe has been parsed
 * @canvas_alloc: array of all the canvas IDs allocated
 * @canvas_num: number of canvas IDs allocated
 * @vअगरअगरo_vaddr: भव address क्रम the VIFIFO
 * @vअगरअगरo_paddr: physical address क्रम the VIFIFO
 * @vअगरअगरo_size: size of the VIFIFO dma alloc
 * @bufs_recycle: list of buffers that need to be recycled
 * @bufs_recycle_lock: lock क्रम the bufs_recycle list
 * @recycle_thपढ़ो: task काष्ठा क्रम the recycling thपढ़ो
 * @बारtamps: chronological list of src बारtamps
 * @ts_spinlock: spinlock क्रम the बारtamps list
 * @last_irq_jअगरfies: tracks last समय the vdec triggered an IRQ
 * @status: current decoding status
 * @priv: codec निजी data
 */
काष्ठा amvdec_session अणु
	काष्ठा amvdec_core *core;

	काष्ठा v4l2_fh fh;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा v4l2_m2m_ctx *m2m_ctx;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl *ctrl_min_buf_capture;
	काष्ठा mutex lock; /* cap & out queues lock */

	स्थिर काष्ठा amvdec_क्रमmat *fmt_out;
	u32 pixfmt_cap;
	u32 src_buffer_size;

	u32 width;
	u32 height;
	u32 colorspace;
	u8 ycbcr_enc;
	u8 quantization;
	u8 xfer_func;

	काष्ठा v4l2_fract pixelaspect;

	atomic_t esparser_queued_bufs;
	काष्ठा work_काष्ठा esparser_queue_work;

	अचिन्हित पूर्णांक streamon_cap, streamon_out;
	अचिन्हित पूर्णांक sequence_cap, sequence_out;
	अचिन्हित पूर्णांक should_stop;
	अचिन्हित पूर्णांक keyframe_found;
	अचिन्हित पूर्णांक num_dst_bufs;
	अचिन्हित पूर्णांक changed_क्रमmat;

	u8 canvas_alloc[MAX_CANVAS];
	u32 canvas_num;

	व्योम *vअगरअगरo_vaddr;
	dma_addr_t vअगरअगरo_paddr;
	u32 vअगरअगरo_size;

	काष्ठा list_head bufs_recycle;
	काष्ठा mutex bufs_recycle_lock; /* bufs_recycle list lock */
	काष्ठा task_काष्ठा *recycle_thपढ़ो;

	काष्ठा list_head बारtamps;
	spinlock_t ts_spinlock; /* बारtamp list lock */

	u64 last_irq_jअगरfies;
	u32 last_offset;
	u32 wrap_count;
	u32 fw_idx_to_vb2_idx[32];

	क्रमागत amvdec_status status;
	व्योम *priv;
पूर्ण;

u32 amvdec_get_output_size(काष्ठा amvdec_session *sess);

#पूर्ण_अगर
