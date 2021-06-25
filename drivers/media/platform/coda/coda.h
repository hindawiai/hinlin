<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Coda multi-standard codec IP
 *
 * Copyright (C) 2012 Vista Silicon S.L.
 *    Javier Martin, <javier.martin@vista-silicon.com>
 *    Xavier Duret
 * Copyright (C) 2012-2014 Philipp Zabel, Pengutronix
 */

#अगर_अघोषित __CODA_H__
#घोषणा __CODA_H__

#समावेश <linux/debugfs.h>
#समावेश <linux/idr.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/ratelimit.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "coda_regs.h"

#घोषणा CODA_MAX_FRAMEBUFFERS	19
#घोषणा FMO_SLICE_SAVE_BUF_SIZE	(32)

/*
 * This control allows applications to पढ़ो the per-stream
 * (i.e. per-context) Macroblocks Error Count. This value
 * is CODA specअगरic.
 */
#घोषणा V4L2_CID_CODA_MB_ERR_CNT (V4L2_CID_USER_CODA_BASE + 0)

क्रमागत अणु
	V4L2_M2M_SRC = 0,
	V4L2_M2M_DST = 1,
पूर्ण;

क्रमागत coda_inst_type अणु
	CODA_INST_ENCODER,
	CODA_INST_DECODER,
पूर्ण;

क्रमागत coda_product अणु
	CODA_DX6 = 0xf001,
	CODA_HX4 = 0xf00a,
	CODA_7541 = 0xf012,
	CODA_960 = 0xf020,
पूर्ण;

काष्ठा coda_video_device;

काष्ठा coda_devtype अणु
	अक्षर			*firmware[3];
	क्रमागत coda_product	product;
	स्थिर काष्ठा coda_codec	*codecs;
	अचिन्हित पूर्णांक		num_codecs;
	स्थिर काष्ठा coda_video_device **vdevs;
	अचिन्हित पूर्णांक		num_vdevs;
	माप_प्रकार			workbuf_size;
	माप_प्रकार			tempbuf_size;
	माप_प्रकार			iram_size;
पूर्ण;

काष्ठा coda_aux_buf अणु
	व्योम			*vaddr;
	dma_addr_t		paddr;
	u32			size;
	काष्ठा debugfs_blob_wrapper blob;
	काष्ठा dentry		*dentry;
पूर्ण;

काष्ठा coda_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	vfd[6];
	काष्ठा device		*dev;
	स्थिर काष्ठा coda_devtype *devtype;
	पूर्णांक			firmware;
	काष्ठा vकरोa_data	*vकरोa;

	व्योम __iomem		*regs_base;
	काष्ठा clk		*clk_per;
	काष्ठा clk		*clk_ahb;
	काष्ठा reset_control	*rstc;

	काष्ठा coda_aux_buf	codebuf;
	काष्ठा coda_aux_buf	tempbuf;
	काष्ठा coda_aux_buf	workbuf;
	काष्ठा gen_pool		*iram_pool;
	काष्ठा coda_aux_buf	iram;

	काष्ठा mutex		dev_mutex;
	काष्ठा mutex		coda_mutex;
	काष्ठा workqueue_काष्ठा	*workqueue;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा ida		ida;
	काष्ठा dentry		*debugfs_root;
	काष्ठा ratelimit_state	mb_err_rs;
पूर्ण;

काष्ठा coda_codec अणु
	u32 mode;
	u32 src_fourcc;
	u32 dst_fourcc;
	u32 max_w;
	u32 max_h;
पूर्ण;

काष्ठा coda_huff_tab;

काष्ठा coda_params अणु
	u8			rot_mode;
	u8			h264_पूर्णांकra_qp;
	u8			h264_पूर्णांकer_qp;
	u8			h264_min_qp;
	u8			h264_max_qp;
	u8			h264_disable_deblocking_filter_idc;
	s8			h264_slice_alpha_c0_offset_भाग2;
	s8			h264_slice_beta_offset_भाग2;
	bool			h264_स्थिरrained_पूर्णांकra_pred_flag;
	s8			h264_chroma_qp_index_offset;
	u8			h264_profile_idc;
	u8			h264_level_idc;
	u8			mpeg2_profile_idc;
	u8			mpeg2_level_idc;
	u8			mpeg4_पूर्णांकra_qp;
	u8			mpeg4_पूर्णांकer_qp;
	u8			gop_size;
	पूर्णांक			पूर्णांकra_refresh;
	क्रमागत v4l2_jpeg_chroma_subsampling jpeg_chroma_subsampling;
	u8			jpeg_quality;
	u8			jpeg_restart_पूर्णांकerval;
	u8			*jpeg_qmat_tab[3];
	पूर्णांक			jpeg_qmat_index[3];
	पूर्णांक			jpeg_huff_dc_index[3];
	पूर्णांक			jpeg_huff_ac_index[3];
	u32			*jpeg_huff_data;
	काष्ठा coda_huff_tab	*jpeg_huff_tab;
	पूर्णांक			codec_mode;
	पूर्णांक			codec_mode_aux;
	क्रमागत v4l2_mpeg_video_multi_slice_mode slice_mode;
	u32			framerate;
	u16			bitrate;
	u16			vbv_delay;
	u32			vbv_size;
	u32			slice_max_bits;
	u32			slice_max_mb;
	bool			क्रमce_ipicture;
	bool			gop_size_changed;
	bool			bitrate_changed;
	bool			framerate_changed;
	bool			h264_पूर्णांकra_qp_changed;
	bool			पूर्णांकra_refresh_changed;
	bool			slice_mode_changed;
	bool			frame_rc_enable;
	bool			mb_rc_enable;
पूर्ण;

काष्ठा coda_buffer_meta अणु
	काष्ठा list_head	list;
	u32			sequence;
	काष्ठा v4l2_समयcode	समयcode;
	u64			बारtamp;
	अचिन्हित पूर्णांक		start;
	अचिन्हित पूर्णांक		end;
	bool			last;
पूर्ण;

/* Per-queue, driver-specअगरic निजी data */
काष्ठा coda_q_data अणु
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	अचिन्हित पूर्णांक		bytesperline;
	अचिन्हित पूर्णांक		sizeimage;
	अचिन्हित पूर्णांक		fourcc;
	काष्ठा v4l2_rect	rect;
पूर्ण;

काष्ठा coda_iram_info अणु
	u32		axi_sram_use;
	phys_addr_t	buf_bit_use;
	phys_addr_t	buf_ip_ac_dc_use;
	phys_addr_t	buf_dbk_y_use;
	phys_addr_t	buf_dbk_c_use;
	phys_addr_t	buf_ovl_use;
	phys_addr_t	buf_btp_use;
	phys_addr_t	search_ram_paddr;
	पूर्णांक		search_ram_size;
	पूर्णांक		reमुख्यing;
	phys_addr_t	next_paddr;
पूर्ण;

#घोषणा GDI_LINEAR_FRAME_MAP 0
#घोषणा GDI_TILED_FRAME_MB_RASTER_MAP 1

काष्ठा coda_ctx;

काष्ठा coda_context_ops अणु
	पूर्णांक (*queue_init)(व्योम *priv, काष्ठा vb2_queue *src_vq,
			  काष्ठा vb2_queue *dst_vq);
	पूर्णांक (*reqbufs)(काष्ठा coda_ctx *ctx, काष्ठा v4l2_requestbuffers *rb);
	पूर्णांक (*start_streaming)(काष्ठा coda_ctx *ctx);
	पूर्णांक (*prepare_run)(काष्ठा coda_ctx *ctx);
	व्योम (*finish_run)(काष्ठा coda_ctx *ctx);
	व्योम (*run_समयout)(काष्ठा coda_ctx *ctx);
	व्योम (*seq_init_work)(काष्ठा work_काष्ठा *work);
	व्योम (*seq_end_work)(काष्ठा work_काष्ठा *work);
	व्योम (*release)(काष्ठा coda_ctx *ctx);
पूर्ण;

काष्ठा coda_पूर्णांकernal_frame अणु
	काष्ठा coda_aux_buf		buf;
	काष्ठा coda_buffer_meta		meta;
	u32				type;
	u32				error;
पूर्ण;

काष्ठा coda_ctx अणु
	काष्ठा coda_dev			*dev;
	काष्ठा mutex			buffer_mutex;
	काष्ठा work_काष्ठा		pic_run_work;
	काष्ठा work_काष्ठा		seq_init_work;
	काष्ठा work_काष्ठा		seq_end_work;
	काष्ठा completion		completion;
	स्थिर काष्ठा coda_video_device	*cvd;
	स्थिर काष्ठा coda_context_ops	*ops;
	पूर्णांक				पातing;
	पूर्णांक				initialized;
	पूर्णांक				streamon_out;
	पूर्णांक				streamon_cap;
	u32				qsequence;
	u32				osequence;
	u32				sequence_offset;
	काष्ठा coda_q_data		q_data[2];
	क्रमागत coda_inst_type		inst_type;
	स्थिर काष्ठा coda_codec		*codec;
	क्रमागत v4l2_colorspace		colorspace;
	क्रमागत v4l2_xfer_func		xfer_func;
	क्रमागत v4l2_ycbcr_encoding	ycbcr_enc;
	क्रमागत v4l2_quantization		quantization;
	काष्ठा coda_params		params;
	काष्ठा v4l2_ctrl_handler	ctrls;
	काष्ठा v4l2_ctrl		*h264_profile_ctrl;
	काष्ठा v4l2_ctrl		*h264_level_ctrl;
	काष्ठा v4l2_ctrl		*mpeg2_profile_ctrl;
	काष्ठा v4l2_ctrl		*mpeg2_level_ctrl;
	काष्ठा v4l2_ctrl		*mpeg4_profile_ctrl;
	काष्ठा v4l2_ctrl		*mpeg4_level_ctrl;
	काष्ठा v4l2_ctrl		*mb_err_cnt_ctrl;
	काष्ठा v4l2_fh			fh;
	पूर्णांक				gopcounter;
	पूर्णांक				runcounter;
	पूर्णांक				jpeg_ecs_offset;
	अक्षर				vpu_header[3][64];
	पूर्णांक				vpu_header_size[3];
	काष्ठा kfअगरo			bitstream_fअगरo;
	काष्ठा mutex			bitstream_mutex;
	काष्ठा coda_aux_buf		bitstream;
	bool				hold;
	काष्ठा coda_aux_buf		parabuf;
	काष्ठा coda_aux_buf		psbuf;
	काष्ठा coda_aux_buf		slicebuf;
	काष्ठा coda_पूर्णांकernal_frame	पूर्णांकernal_frames[CODA_MAX_FRAMEBUFFERS];
	काष्ठा list_head		buffer_meta_list;
	spinlock_t			buffer_meta_lock;
	पूर्णांक				num_metas;
	अचिन्हित पूर्णांक			first_frame_sequence;
	काष्ठा coda_aux_buf		workbuf;
	पूर्णांक				num_पूर्णांकernal_frames;
	पूर्णांक				idx;
	पूर्णांक				reg_idx;
	काष्ठा coda_iram_info		iram_info;
	पूर्णांक				tiled_map_type;
	u32				bit_stream_param;
	u32				frm_dis_flg;
	u32				frame_mem_ctrl;
	u32				para_change;
	पूर्णांक				display_idx;
	काष्ठा dentry			*debugfs_entry;
	bool				use_bit;
	bool				use_vकरोa;
	काष्ठा vकरोa_ctx			*vकरोa;
	/*
	 * wakeup mutex used to serialize encoder stop command and finish_run,
	 * ensures that finish_run always either flags the last वापसed buffer
	 * or wakes up the capture queue to संकेत EOS afterwards.
	 */
	काष्ठा mutex			wakeup_mutex;
पूर्ण;

बाह्य पूर्णांक coda_debug;

#घोषणा coda_dbg(level, ctx, fmt, arg...)				\
	करो अणु								\
		अगर (coda_debug >= (level))				\
			v4l2_dbg((level), coda_debug, &(ctx)->dev->v4l2_dev, \
			 "%u: " fmt, (ctx)->idx, ##arg);		\
	पूर्ण जबतक (0)

व्योम coda_ग_लिखो(काष्ठा coda_dev *dev, u32 data, u32 reg);
अचिन्हित पूर्णांक coda_पढ़ो(काष्ठा coda_dev *dev, u32 reg);
व्योम coda_ग_लिखो_base(काष्ठा coda_ctx *ctx, काष्ठा coda_q_data *q_data,
		     काष्ठा vb2_v4l2_buffer *buf, अचिन्हित पूर्णांक reg_y);

पूर्णांक coda_alloc_aux_buf(काष्ठा coda_dev *dev, काष्ठा coda_aux_buf *buf,
		       माप_प्रकार size, स्थिर अक्षर *name, काष्ठा dentry *parent);
व्योम coda_मुक्त_aux_buf(काष्ठा coda_dev *dev, काष्ठा coda_aux_buf *buf);

पूर्णांक coda_encoder_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			    काष्ठा vb2_queue *dst_vq);
पूर्णांक coda_decoder_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
			    काष्ठा vb2_queue *dst_vq);

पूर्णांक coda_hw_reset(काष्ठा coda_ctx *ctx);

व्योम coda_fill_bitstream(काष्ठा coda_ctx *ctx, काष्ठा list_head *buffer_list);

व्योम coda_set_gdi_regs(काष्ठा coda_ctx *ctx);

अटल अंतरभूत काष्ठा coda_q_data *get_q_data(काष्ठा coda_ctx *ctx,
					     क्रमागत v4l2_buf_type type)
अणु
	चयन (type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_OUTPUT:
		वापस &(ctx->q_data[V4L2_M2M_SRC]);
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस &(ctx->q_data[V4L2_M2M_DST]);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

स्थिर अक्षर *coda_product_name(पूर्णांक product);

पूर्णांक coda_check_firmware(काष्ठा coda_dev *dev);

अटल अंतरभूत अचिन्हित पूर्णांक coda_get_bitstream_payload(काष्ठा coda_ctx *ctx)
अणु
	वापस kfअगरo_len(&ctx->bitstream_fअगरo);
पूर्ण

/*
 * The bitstream prefetcher needs to पढ़ो at least 2 256 byte periods past
 * the desired bitstream position क्रम all data to reach the decoder.
 */
अटल अंतरभूत bool coda_bitstream_can_fetch_past(काष्ठा coda_ctx *ctx,
						 अचिन्हित पूर्णांक pos)
अणु
	वापस (पूर्णांक)(ctx->bitstream_fअगरo.kfअगरo.in - ALIGN(pos, 256)) > 512;
पूर्ण

bool coda_bitstream_can_fetch_past(काष्ठा coda_ctx *ctx, अचिन्हित पूर्णांक pos);
पूर्णांक coda_bitstream_flush(काष्ठा coda_ctx *ctx);

व्योम coda_bit_stream_end_flag(काष्ठा coda_ctx *ctx);

व्योम coda_m2m_buf_करोne(काष्ठा coda_ctx *ctx, काष्ठा vb2_v4l2_buffer *buf,
		       क्रमागत vb2_buffer_state state);

पूर्णांक coda_h264_filler_nal(पूर्णांक size, अक्षर *p);
पूर्णांक coda_h264_padding(पूर्णांक size, अक्षर *p);
पूर्णांक coda_h264_profile(पूर्णांक profile_idc);
पूर्णांक coda_h264_level(पूर्णांक level_idc);
पूर्णांक coda_sps_parse_profile(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb);
पूर्णांक coda_h264_sps_fixup(काष्ठा coda_ctx *ctx, पूर्णांक width, पूर्णांक height, अक्षर *buf,
			पूर्णांक *size, पूर्णांक max_size);

पूर्णांक coda_mpeg2_profile(पूर्णांक profile_idc);
पूर्णांक coda_mpeg2_level(पूर्णांक level_idc);
u32 coda_mpeg2_parse_headers(काष्ठा coda_ctx *ctx, u8 *buf, u32 size);
पूर्णांक coda_mpeg4_profile(पूर्णांक profile_idc);
पूर्णांक coda_mpeg4_level(पूर्णांक level_idc);
u32 coda_mpeg4_parse_headers(काष्ठा coda_ctx *ctx, u8 *buf, u32 size);

व्योम coda_update_profile_level_ctrls(काष्ठा coda_ctx *ctx, u8 profile_idc,
				     u8 level_idc);

bool coda_jpeg_check_buffer(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb);
पूर्णांक coda_jpeg_decode_header(काष्ठा coda_ctx *ctx, काष्ठा vb2_buffer *vb);
पूर्णांक coda_jpeg_ग_लिखो_tables(काष्ठा coda_ctx *ctx);
व्योम coda_set_jpeg_compression_quality(काष्ठा coda_ctx *ctx, पूर्णांक quality);

बाह्य स्थिर काष्ठा coda_context_ops coda_bit_encode_ops;
बाह्य स्थिर काष्ठा coda_context_ops coda_bit_decode_ops;
बाह्य स्थिर काष्ठा coda_context_ops coda9_jpeg_encode_ops;
बाह्य स्थिर काष्ठा coda_context_ops coda9_jpeg_decode_ops;

irqवापस_t coda_irq_handler(पूर्णांक irq, व्योम *data);
irqवापस_t coda9_jpeg_irq_handler(पूर्णांक irq, व्योम *data);

#पूर्ण_अगर /* __CODA_H__ */
