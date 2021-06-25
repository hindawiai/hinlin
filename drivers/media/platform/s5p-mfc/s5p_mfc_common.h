<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Samsung S5P Multi Format Codec v 5.0
 *
 * This file contains definitions of क्रमागतs and काष्ठाs used by the codec
 * driver.
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Kamil Debski, <k.debski@samsung.com>
 */

#अगर_अघोषित S5P_MFC_COMMON_H_
#घोषणा S5P_MFC_COMMON_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश "regs-mfc.h"
#समावेश "regs-mfc-v10.h"

#घोषणा S5P_MFC_NAME		"s5p-mfc"

/* Definitions related to MFC memory */

/* Offset base used to dअगरferentiate between CAPTURE and OUTPUT
*  जबतक mmaping */
#घोषणा DST_QUEUE_OFF_BASE	(1 << 30)

#घोषणा BANK_L_CTX	0
#घोषणा BANK_R_CTX	1
#घोषणा BANK_CTX_NUM	2

#घोषणा MFC_BANK1_ALIGN_ORDER	13
#घोषणा MFC_BANK2_ALIGN_ORDER	13
#घोषणा MFC_BASE_ALIGN_ORDER	17

#घोषणा MFC_FW_MAX_VERSIONS	2

#समावेश <media/videobuf2-dma-contig.h>

/* MFC definitions */
#घोषणा MFC_MAX_EXTRA_DPB       5
#घोषणा MFC_MAX_BUFFERS		32
#घोषणा MFC_NUM_CONTEXTS	4
/* Interrupt समयout */
#घोषणा MFC_INT_TIMEOUT		2000
/* Busy रुको समयout */
#घोषणा MFC_BW_TIMEOUT		500
/* Watchकरोg पूर्णांकerval */
#घोषणा MFC_WATCHDOG_INTERVAL   1000
/* After how many executions watchकरोg should assume lock up */
#घोषणा MFC_WATCHDOG_CNT        10
#घोषणा MFC_NO_INSTANCE_SET	-1
#घोषणा MFC_ENC_CAP_PLANE_COUNT	1
#घोषणा MFC_ENC_OUT_PLANE_COUNT	2
#घोषणा STUFF_BYTE		4
#घोषणा MFC_MAX_CTRLS		128

#घोषणा S5P_MFC_CODEC_NONE		-1
#घोषणा S5P_MFC_CODEC_H264_DEC		0
#घोषणा S5P_MFC_CODEC_H264_MVC_DEC	1
#घोषणा S5P_MFC_CODEC_VC1_DEC		2
#घोषणा S5P_MFC_CODEC_MPEG4_DEC		3
#घोषणा S5P_MFC_CODEC_MPEG2_DEC		4
#घोषणा S5P_MFC_CODEC_H263_DEC		5
#घोषणा S5P_MFC_CODEC_VC1RCV_DEC	6
#घोषणा S5P_MFC_CODEC_VP8_DEC		7
#घोषणा S5P_MFC_CODEC_HEVC_DEC		17
#घोषणा S5P_MFC_CODEC_VP9_DEC		18

#घोषणा S5P_MFC_CODEC_H264_ENC		20
#घोषणा S5P_MFC_CODEC_H264_MVC_ENC	21
#घोषणा S5P_MFC_CODEC_MPEG4_ENC		22
#घोषणा S5P_MFC_CODEC_H263_ENC		23
#घोषणा S5P_MFC_CODEC_VP8_ENC		24
#घोषणा S5P_MFC_CODEC_HEVC_ENC		26

#घोषणा S5P_MFC_R2H_CMD_EMPTY			0
#घोषणा S5P_MFC_R2H_CMD_SYS_INIT_RET		1
#घोषणा S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET	2
#घोषणा S5P_MFC_R2H_CMD_SEQ_DONE_RET		3
#घोषणा S5P_MFC_R2H_CMD_INIT_BUFFERS_RET	4
#घोषणा S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET	6
#घोषणा S5P_MFC_R2H_CMD_SLEEP_RET		7
#घोषणा S5P_MFC_R2H_CMD_WAKEUP_RET		8
#घोषणा S5P_MFC_R2H_CMD_COMPLETE_SEQ_RET	9
#घोषणा S5P_MFC_R2H_CMD_DPB_FLUSH_RET		10
#घोषणा S5P_MFC_R2H_CMD_NAL_ABORT_RET		11
#घोषणा S5P_MFC_R2H_CMD_FW_STATUS_RET		12
#घोषणा S5P_MFC_R2H_CMD_FRAME_DONE_RET		13
#घोषणा S5P_MFC_R2H_CMD_FIELD_DONE_RET		14
#घोषणा S5P_MFC_R2H_CMD_SLICE_DONE_RET		15
#घोषणा S5P_MFC_R2H_CMD_ENC_BUFFER_FUL_RET	16
#घोषणा S5P_MFC_R2H_CMD_ERR_RET			32

#घोषणा MFC_MAX_CLOCKS		4

#घोषणा mfc_पढ़ो(dev, offset)		पढ़ोl(dev->regs_base + (offset))
#घोषणा mfc_ग_लिखो(dev, data, offset)	ग_लिखोl((data), dev->regs_base + \
								(offset))

/*
 * क्रमागत s5p_mfc_fmt_type - type of the pixelक्रमmat
 */
क्रमागत s5p_mfc_fmt_type अणु
	MFC_FMT_DEC,
	MFC_FMT_ENC,
	MFC_FMT_RAW,
पूर्ण;

/*
 * क्रमागत s5p_mfc_inst_type - The type of an MFC instance.
 */
क्रमागत s5p_mfc_inst_type अणु
	MFCINST_INVALID,
	MFCINST_DECODER,
	MFCINST_ENCODER,
पूर्ण;

/*
 * क्रमागत s5p_mfc_inst_state - The state of an MFC instance.
 */
क्रमागत s5p_mfc_inst_state अणु
	MFCINST_FREE = 0,
	MFCINST_INIT = 100,
	MFCINST_GOT_INST,
	MFCINST_HEAD_PARSED,
	MFCINST_HEAD_PRODUCED,
	MFCINST_BUFS_SET,
	MFCINST_RUNNING,
	MFCINST_FINISHING,
	MFCINST_FINISHED,
	MFCINST_RETURN_INST,
	MFCINST_ERROR,
	MFCINST_ABORT,
	MFCINST_FLUSH,
	MFCINST_RES_CHANGE_INIT,
	MFCINST_RES_CHANGE_FLUSH,
	MFCINST_RES_CHANGE_END,
पूर्ण;

/*
 * क्रमागत s5p_mfc_queue_state - The state of buffer queue.
 */
क्रमागत s5p_mfc_queue_state अणु
	QUEUE_FREE,
	QUEUE_BUFS_REQUESTED,
	QUEUE_BUFS_QUERIED,
	QUEUE_BUFS_MMAPED,
पूर्ण;

/*
 * क्रमागत s5p_mfc_decode_arg - type of frame decoding
 */
क्रमागत s5p_mfc_decode_arg अणु
	MFC_DEC_FRAME,
	MFC_DEC_LAST_FRAME,
	MFC_DEC_RES_CHANGE,
पूर्ण;

क्रमागत s5p_mfc_fw_ver अणु
	MFC_FW_V1,
	MFC_FW_V2,
पूर्ण;

#घोषणा MFC_BUF_FLAG_USED	(1 << 0)
#घोषणा MFC_BUF_FLAG_EOS	(1 << 1)

काष्ठा s5p_mfc_ctx;

/*
 * काष्ठा s5p_mfc_buf - MFC buffer
 */
काष्ठा s5p_mfc_buf अणु
	काष्ठा vb2_v4l2_buffer *b;
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा अणु
			माप_प्रकार luma;
			माप_प्रकार chroma;
		पूर्ण raw;
		माप_प्रकार stream;
	पूर्ण cookie;
	पूर्णांक flags;
पूर्ण;

/*
 * काष्ठा s5p_mfc_pm - घातer management data काष्ठाure
 */
काष्ठा s5p_mfc_pm अणु
	काष्ठा clk	*घड़ी_gate;
	स्थिर अक्षर * स्थिर *clk_names;
	काष्ठा clk	*घड़ीs[MFC_MAX_CLOCKS];
	पूर्णांक		num_घड़ीs;
	bool		use_घड़ी_gating;

	काष्ठा device	*device;
पूर्ण;

काष्ठा s5p_mfc_buf_size_v5 अणु
	अचिन्हित पूर्णांक h264_ctx;
	अचिन्हित पूर्णांक non_h264_ctx;
	अचिन्हित पूर्णांक dsc;
	अचिन्हित पूर्णांक shm;
पूर्ण;

काष्ठा s5p_mfc_buf_size_v6 अणु
	अचिन्हित पूर्णांक dev_ctx;
	अचिन्हित पूर्णांक h264_dec_ctx;
	अचिन्हित पूर्णांक other_dec_ctx;
	अचिन्हित पूर्णांक h264_enc_ctx;
	अचिन्हित पूर्णांक hevc_enc_ctx;
	अचिन्हित पूर्णांक other_enc_ctx;
पूर्ण;

काष्ठा s5p_mfc_buf_size अणु
	अचिन्हित पूर्णांक fw;
	अचिन्हित पूर्णांक cpb;
	व्योम *priv;
पूर्ण;

काष्ठा s5p_mfc_variant अणु
	अचिन्हित पूर्णांक version;
	अचिन्हित पूर्णांक port_num;
	u32 version_bit;
	काष्ठा s5p_mfc_buf_size *buf_size;
	अक्षर	*fw_name[MFC_FW_MAX_VERSIONS];
	स्थिर अक्षर	*clk_names[MFC_MAX_CLOCKS];
	पूर्णांक		num_घड़ीs;
	bool		use_घड़ी_gating;
पूर्ण;

/**
 * काष्ठा s5p_mfc_priv_buf - represents पूर्णांकernal used buffer
 * @ofs:		offset of each buffer, will be used क्रम MFC
 * @virt:		kernel भव address, only valid when the
 *			buffer accessed by driver
 * @dma:		DMA address, only valid when kernel DMA API used
 * @size:		size of the buffer
 * @ctx:		memory context (bank) used क्रम this allocation
 */
काष्ठा s5p_mfc_priv_buf अणु
	अचिन्हित दीर्घ	ofs;
	व्योम		*virt;
	dma_addr_t	dma;
	माप_प्रकार		size;
	अचिन्हित पूर्णांक	ctx;
पूर्ण;

/**
 * काष्ठा s5p_mfc_dev - The काष्ठा containing driver पूर्णांकernal parameters.
 *
 * @v4l2_dev:		v4l2_device
 * @vfd_dec:		video device क्रम decoding
 * @vfd_enc:		video device क्रम encoding
 * @plat_dev:		platक्रमm device
 * @mem_dev:		child devices of the memory banks
 * @regs_base:		base address of the MFC hw रेजिस्टरs
 * @irq:		irq resource
 * @dec_ctrl_handler:	control framework handler क्रम decoding
 * @enc_ctrl_handler:	control framework handler क्रम encoding
 * @pm:			घातer management control
 * @variant:		MFC hardware variant inक्रमmation
 * @num_inst:		counter of active MFC instances
 * @irqlock:		lock क्रम operations on videobuf2 queues
 * @condlock:		lock क्रम changing/checking अगर a context is पढ़ोy to be
 *			processed
 * @mfc_mutex:		lock क्रम video_device
 * @पूर्णांक_cond:		variable used by the रुकोqueue
 * @पूर्णांक_type:		type of last पूर्णांकerrupt
 * @पूर्णांक_err:		error number क्रम last पूर्णांकerrupt
 * @queue:		रुकोqueue क्रम रुकोing क्रम completion of device commands
 * @fw_buf:		the firmware buffer data काष्ठाure
 * @mem_size:		size of the firmware operation memory
 * @mem_base:		base DMA address of the firmware operation memory
 * @mem_biपंचांगap:		biपंचांगap क्रम managing MFC पूर्णांकernal buffer allocations
 * @mem_virt:		भव address of the firmware operation memory
 * @dma_base:		address of the beginning of memory banks
 * @hw_lock:		used क्रम hardware locking
 * @ctx:		array of driver contexts
 * @curr_ctx:		number of the currently running context
 * @ctx_work_bits:	used to mark which contexts are रुकोing क्रम hardware
 * @watchकरोg_cnt:	counter क्रम the watchकरोg
 * @watchकरोg_समयr:	समयr क्रम the watchकरोg
 * @watchकरोg_workqueue:	workqueue क्रम the watchकरोg
 * @watchकरोg_work:	worker क्रम the watchकरोg
 * @enter_suspend:	flag set when entering suspend
 * @ctx_buf:		common context memory (MFCv6)
 * @warn_start:		hardware error code from which warnings start
 * @mfc_ops:		ops काष्ठाure holding HW operation function poपूर्णांकers
 * @mfc_cmds:		cmd काष्ठाure holding HW commands function poपूर्णांकers
 * @mfc_regs:		काष्ठाure holding MFC रेजिस्टरs
 * @fw_ver:		loaded firmware sub-version
 * @fw_get_करोne:	flag set when request_firmware() is complete and
 *			copied पूर्णांकo fw_buf
 * @risc_on:		flag indicates RISC is on or off
 *
 */
काष्ठा s5p_mfc_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	*vfd_dec;
	काष्ठा video_device	*vfd_enc;
	काष्ठा platक्रमm_device	*plat_dev;
	काष्ठा device		*mem_dev[BANK_CTX_NUM];
	व्योम __iomem		*regs_base;
	पूर्णांक			irq;
	काष्ठा v4l2_ctrl_handler dec_ctrl_handler;
	काष्ठा v4l2_ctrl_handler enc_ctrl_handler;
	काष्ठा s5p_mfc_pm	pm;
	स्थिर काष्ठा s5p_mfc_variant	*variant;
	पूर्णांक num_inst;
	spinlock_t irqlock;	/* lock when operating on context */
	spinlock_t condlock;	/* lock when changing/checking अगर a context is
					पढ़ोy to be processed */
	काष्ठा mutex mfc_mutex; /* video_device lock */
	पूर्णांक पूर्णांक_cond;
	पूर्णांक पूर्णांक_type;
	अचिन्हित पूर्णांक पूर्णांक_err;
	रुको_queue_head_t queue;
	काष्ठा s5p_mfc_priv_buf fw_buf;
	माप_प्रकार mem_size;
	dma_addr_t mem_base;
	अचिन्हित दीर्घ *mem_biपंचांगap;
	व्योम *mem_virt;
	dma_addr_t dma_base[BANK_CTX_NUM];
	अचिन्हित दीर्घ hw_lock;
	काष्ठा s5p_mfc_ctx *ctx[MFC_NUM_CONTEXTS];
	पूर्णांक curr_ctx;
	अचिन्हित दीर्घ ctx_work_bits;
	atomic_t watchकरोg_cnt;
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा workqueue_काष्ठा *watchकरोg_workqueue;
	काष्ठा work_काष्ठा watchकरोg_work;
	अचिन्हित दीर्घ enter_suspend;

	काष्ठा s5p_mfc_priv_buf ctx_buf;
	पूर्णांक warn_start;
	काष्ठा s5p_mfc_hw_ops *mfc_ops;
	काष्ठा s5p_mfc_hw_cmds *mfc_cmds;
	स्थिर काष्ठा s5p_mfc_regs *mfc_regs;
	क्रमागत s5p_mfc_fw_ver fw_ver;
	bool fw_get_करोne;
	bool risc_on; /* indicates अगर RISC is on or off */
पूर्ण;

/*
 * काष्ठा s5p_mfc_h264_enc_params - encoding parameters क्रम h264
 */
काष्ठा s5p_mfc_h264_enc_params अणु
	क्रमागत v4l2_mpeg_video_h264_profile profile;
	क्रमागत v4l2_mpeg_video_h264_loop_filter_mode loop_filter_mode;
	s8 loop_filter_alpha;
	s8 loop_filter_beta;
	क्रमागत v4l2_mpeg_video_h264_entropy_mode entropy_mode;
	u8 max_ref_pic;
	u8 num_ref_pic_4p;
	पूर्णांक _8x8_transक्रमm;
	पूर्णांक rc_mb_dark;
	पूर्णांक rc_mb_smooth;
	पूर्णांक rc_mb_अटल;
	पूर्णांक rc_mb_activity;
	पूर्णांक vui_sar;
	u8 vui_sar_idc;
	u16 vui_ext_sar_width;
	u16 vui_ext_sar_height;
	पूर्णांक खोलो_gop;
	u16 खोलो_gop_size;
	u8 rc_frame_qp;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_p_frame_qp;
	u8 rc_b_frame_qp;
	क्रमागत v4l2_mpeg_video_h264_level level_v4l2;
	पूर्णांक level;
	u16 cpb_size;
	पूर्णांक पूर्णांकerlace;
	u8 hier_qp;
	u8 hier_qp_type;
	u8 hier_qp_layer;
	u8 hier_qp_layer_qp[7];
	u8 sei_frame_packing;
	u8 sei_fp_curr_frame_0;
	u8 sei_fp_arrangement_type;

	u8 fmo;
	u8 fmo_map_type;
	u8 fmo_slice_grp;
	u8 fmo_chg_dir;
	u32 fmo_chg_rate;
	u32 fmo_run_len[4];
	u8 aso;
	u32 aso_slice_order[8];
पूर्ण;

/*
 * काष्ठा s5p_mfc_mpeg4_enc_params - encoding parameters क्रम h263 and mpeg4
 */
काष्ठा s5p_mfc_mpeg4_enc_params अणु
	/* MPEG4 Only */
	क्रमागत v4l2_mpeg_video_mpeg4_profile profile;
	पूर्णांक quarter_pixel;
	/* Common क्रम MPEG4, H263 */
	u16 vop_समय_res;
	u16 vop_frm_delta;
	u8 rc_frame_qp;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_p_frame_qp;
	u8 rc_b_frame_qp;
	क्रमागत v4l2_mpeg_video_mpeg4_level level_v4l2;
	पूर्णांक level;
पूर्ण;

/*
 * काष्ठा s5p_mfc_vp8_enc_params - encoding parameters क्रम vp8
 */
काष्ठा s5p_mfc_vp8_enc_params अणु
	u8 imd_4x4;
	क्रमागत v4l2_vp8_num_partitions num_partitions;
	क्रमागत v4l2_vp8_num_ref_frames num_ref;
	u8 filter_level;
	u8 filter_sharpness;
	u32 golden_frame_ref_period;
	क्रमागत v4l2_vp8_golden_frame_sel golden_frame_sel;
	u8 hier_layer;
	u8 hier_layer_qp[3];
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_frame_qp;
	u8 rc_p_frame_qp;
	u8 profile;
पूर्ण;

काष्ठा s5p_mfc_hevc_enc_params अणु
	क्रमागत v4l2_mpeg_video_hevc_profile profile;
	पूर्णांक level;
	क्रमागत v4l2_mpeg_video_h264_level level_v4l2;
	u8 tier;
	u32 rc_framerate;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_lcu_dark;
	u8 rc_lcu_smooth;
	u8 rc_lcu_अटल;
	u8 rc_lcu_activity;
	u8 rc_frame_qp;
	u8 rc_p_frame_qp;
	u8 rc_b_frame_qp;
	u8 max_partition_depth;
	u8 num_refs_क्रम_p;
	u8 refreshtype;
	u16 refreshperiod;
	s32 lf_beta_offset_भाग2;
	s32 lf_tc_offset_भाग2;
	u8 loopfilter;
	u8 loopfilter_disable;
	u8 loopfilter_across;
	u8 nal_control_length_filed;
	u8 nal_control_user_ref;
	u8 nal_control_store_ref;
	u8 स्थिर_पूर्णांकra_period_enable;
	u8 lossless_cu_enable;
	u8 wavefront_enable;
	u8 enable_ltr;
	u8 hier_qp_enable;
	क्रमागत v4l2_mpeg_video_hevc_hier_coding_type hier_qp_type;
	u8 num_hier_layer;
	u8 hier_qp_layer[7];
	u32 hier_bit_layer[7];
	u8 sign_data_hiding;
	u8 general_pb_enable;
	u8 temporal_id_enable;
	u8 strong_पूर्णांकra_smooth;
	u8 पूर्णांकra_pu_split_disable;
	u8 पंचांगv_prediction_disable;
	u8 max_num_merge_mv;
	u8 eco_mode_enable;
	u8 encoding_nostartcode_enable;
	u8 size_of_length_field;
	u8 prepend_sps_pps_to_idr;
पूर्ण;

/*
 * काष्ठा s5p_mfc_enc_params - general encoding parameters
 */
काष्ठा s5p_mfc_enc_params अणु
	u16 width;
	u16 height;
	u32 mv_h_range;
	u32 mv_v_range;

	u16 gop_size;
	क्रमागत v4l2_mpeg_video_multi_slice_mode slice_mode;
	u16 slice_mb;
	u32 slice_bit;
	u16 पूर्णांकra_refresh_mb;
	पूर्णांक pad;
	u8 pad_luma;
	u8 pad_cb;
	u8 pad_cr;
	पूर्णांक rc_frame;
	पूर्णांक rc_mb;
	u32 rc_bitrate;
	u16 rc_reaction_coeff;
	u16 vbv_size;
	u32 vbv_delay;

	क्रमागत v4l2_mpeg_video_header_mode seq_hdr_mode;
	क्रमागत v4l2_mpeg_mfc51_video_frame_skip_mode frame_skip_mode;
	पूर्णांक fixed_target_bit;

	u8 num_b_frame;
	u32 rc_framerate_num;
	u32 rc_framerate_denom;

	काष्ठा अणु
		काष्ठा s5p_mfc_h264_enc_params h264;
		काष्ठा s5p_mfc_mpeg4_enc_params mpeg4;
		काष्ठा s5p_mfc_vp8_enc_params vp8;
		काष्ठा s5p_mfc_hevc_enc_params hevc;
	पूर्ण codec;

पूर्ण;

/*
 * काष्ठा s5p_mfc_codec_ops - codec ops, used by encoding
 */
काष्ठा s5p_mfc_codec_ops अणु
	/* initialization routines */
	पूर्णांक (*pre_seq_start) (काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*post_seq_start) (काष्ठा s5p_mfc_ctx *ctx);
	/* execution routines */
	पूर्णांक (*pre_frame_start) (काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*post_frame_start) (काष्ठा s5p_mfc_ctx *ctx);
पूर्ण;

#घोषणा call_cop(c, op, args...)				\
	(((c)->c_ops->op) ?					\
		((c)->c_ops->op(args)) : 0)

/**
 * काष्ठा s5p_mfc_ctx - This काष्ठा contains the instance context
 *
 * @dev:		poपूर्णांकer to the s5p_mfc_dev of the device
 * @fh:			काष्ठा v4l2_fh
 * @num:		number of the context that this काष्ठाure describes
 * @पूर्णांक_cond:		variable used by the रुकोqueue
 * @पूर्णांक_type:		type of the last पूर्णांकerrupt
 * @पूर्णांक_err:		error number received from MFC hw in the पूर्णांकerrupt
 * @queue:		रुकोqueue that can be used to रुको क्रम this context to
 *			finish
 * @src_fmt:		source pixelक्रमmat inक्रमmation
 * @dst_fmt:		destination pixelक्रमmat inक्रमmation
 * @vq_src:		vb2 queue क्रम source buffers
 * @vq_dst:		vb2 queue क्रम destination buffers
 * @src_queue:		driver पूर्णांकernal queue क्रम source buffers
 * @dst_queue:		driver पूर्णांकernal queue क्रम destination buffers
 * @src_queue_cnt:	number of buffers queued on the source पूर्णांकernal queue
 * @dst_queue_cnt:	number of buffers queued on the dest पूर्णांकernal queue
 * @type:		type of the instance - decoder or encoder
 * @state:		state of the context
 * @inst_no:		number of hw instance associated with the context
 * @img_width:		width of the image that is decoded or encoded
 * @img_height:		height of the image that is decoded or encoded
 * @buf_width:		width of the buffer क्रम processed image
 * @buf_height:		height of the buffer क्रम processed image
 * @luma_size:		size of a luma plane
 * @chroma_size:	size of a chroma plane
 * @mv_size:		size of a motion vectors buffer
 * @consumed_stream:	number of bytes that have been used so far from the
 *			decoding buffer
 * @dpb_flush_flag:	flag used to indicate that a DPB buffers are being
 *			flushed
 * @head_processed:	flag mentioning whether the header data is processed
 *			completely or not
 * @bank1:		handle to memory allocated क्रम temporary buffers from
 *			memory bank 1
 * @bank2:		handle to memory allocated क्रम temporary buffers from
 *			memory bank 2
 * @capture_state:	state of the capture buffers queue
 * @output_state:	state of the output buffers queue
 * @src_bufs:		inक्रमmation on allocated source buffers
 * @src_bufs_cnt:	number of allocated source buffers
 * @dst_bufs:		inक्रमmation on allocated destination buffers
 * @dst_bufs_cnt:	number of allocated destination buffers
 * @sequence:		counter क्रम the sequence number क्रम v4l2
 * @dec_dst_flag:	flags क्रम buffers queued in the hardware
 * @dec_src_buf_size:	size of the buffer क्रम source buffers in decoding
 * @codec_mode:		number of codec mode used by MFC hw
 * @slice_पूर्णांकerface:	slice पूर्णांकerface flag
 * @loop_filter_mpeg4:	loop filter क्रम MPEG4 flag
 * @display_delay:	value of the display delay क्रम H264
 * @display_delay_enable:	display delay क्रम H264 enable flag
 * @after_packed_pb:	flag used to track buffer when stream is in
 *			Packed PB क्रमmat
 * @sei_fp_parse:	enable/disable parsing of frame packing SEI inक्रमmation
 * @pb_count:		count of the DPB buffers required by MFC hw
 * @total_dpb_count:	count of DPB buffers with additional buffers
 *			requested by the application
 * @ctx:		context buffer inक्रमmation
 * @dsc:		descriptor buffer inक्रमmation
 * @shm:		shared memory buffer inक्रमmation
 * @mv_count:		number of MV buffers allocated क्रम decoding
 * @enc_params:		encoding parameters क्रम MFC
 * @enc_dst_buf_size:	size of the buffers क्रम encoder output
 * @luma_dpb_size:	dpb buffer size क्रम luma
 * @chroma_dpb_size:	dpb buffer size क्रम chroma
 * @me_buffer_size:	size of the motion estimation buffer
 * @पंचांगv_buffer_size:	size of temporal predictor motion vector buffer
 * @frame_type:		used to क्रमce the type of the next encoded frame
 * @ref_queue:		list of the reference buffers क्रम encoding
 * @क्रमce_frame_type:	encoder's frame type क्रमcing control
 * @ref_queue_cnt:	number of the buffers in the reference list
 * @slice_size:		slice size
 * @slice_mode:		mode of भागiding frames पूर्णांकo slices
 * @c_ops:		ops क्रम encoding
 * @ctrls:		array of controls, used when adding controls to the
 *			v4l2 control framework
 * @ctrl_handler:	handler क्रम v4l2 framework
 * @scratch_buf_size:	scratch buffer size
 */
काष्ठा s5p_mfc_ctx अणु
	काष्ठा s5p_mfc_dev *dev;
	काष्ठा v4l2_fh fh;

	पूर्णांक num;

	पूर्णांक पूर्णांक_cond;
	पूर्णांक पूर्णांक_type;
	अचिन्हित पूर्णांक पूर्णांक_err;
	रुको_queue_head_t queue;

	काष्ठा s5p_mfc_fmt *src_fmt;
	काष्ठा s5p_mfc_fmt *dst_fmt;

	काष्ठा vb2_queue vq_src;
	काष्ठा vb2_queue vq_dst;

	काष्ठा list_head src_queue;
	काष्ठा list_head dst_queue;

	अचिन्हित पूर्णांक src_queue_cnt;
	अचिन्हित पूर्णांक dst_queue_cnt;

	क्रमागत s5p_mfc_inst_type type;
	क्रमागत s5p_mfc_inst_state state;
	पूर्णांक inst_no;

	/* Image parameters */
	पूर्णांक img_width;
	पूर्णांक img_height;
	पूर्णांक buf_width;
	पूर्णांक buf_height;

	पूर्णांक luma_size;
	पूर्णांक chroma_size;
	पूर्णांक mv_size;

	अचिन्हित दीर्घ consumed_stream;

	अचिन्हित पूर्णांक dpb_flush_flag;
	अचिन्हित पूर्णांक head_processed;

	काष्ठा s5p_mfc_priv_buf bank1;
	काष्ठा s5p_mfc_priv_buf bank2;

	क्रमागत s5p_mfc_queue_state capture_state;
	क्रमागत s5p_mfc_queue_state output_state;

	काष्ठा s5p_mfc_buf src_bufs[MFC_MAX_BUFFERS];
	पूर्णांक src_bufs_cnt;
	काष्ठा s5p_mfc_buf dst_bufs[MFC_MAX_BUFFERS];
	पूर्णांक dst_bufs_cnt;

	अचिन्हित पूर्णांक sequence;
	अचिन्हित दीर्घ dec_dst_flag;
	माप_प्रकार dec_src_buf_size;

	/* Control values */
	पूर्णांक codec_mode;
	पूर्णांक slice_पूर्णांकerface;
	पूर्णांक loop_filter_mpeg4;
	पूर्णांक display_delay;
	पूर्णांक display_delay_enable;
	पूर्णांक after_packed_pb;
	पूर्णांक sei_fp_parse;

	पूर्णांक pb_count;
	पूर्णांक total_dpb_count;
	पूर्णांक mv_count;
	/* Buffers */
	काष्ठा s5p_mfc_priv_buf ctx;
	काष्ठा s5p_mfc_priv_buf dsc;
	काष्ठा s5p_mfc_priv_buf shm;

	काष्ठा s5p_mfc_enc_params enc_params;

	माप_प्रकार enc_dst_buf_size;
	माप_प्रकार luma_dpb_size;
	माप_प्रकार chroma_dpb_size;
	माप_प्रकार me_buffer_size;
	माप_प्रकार पंचांगv_buffer_size;

	क्रमागत v4l2_mpeg_mfc51_video_क्रमce_frame_type क्रमce_frame_type;

	काष्ठा list_head ref_queue;
	अचिन्हित पूर्णांक ref_queue_cnt;

	क्रमागत v4l2_mpeg_video_multi_slice_mode slice_mode;
	जोड़ अणु
		अचिन्हित पूर्णांक mb;
		अचिन्हित पूर्णांक bits;
	पूर्ण slice_size;

	स्थिर काष्ठा s5p_mfc_codec_ops *c_ops;

	काष्ठा v4l2_ctrl *ctrls[MFC_MAX_CTRLS];
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	माप_प्रकार scratch_buf_size;
पूर्ण;

/*
 * काष्ठा s5p_mfc_fmt -	काष्ठाure used to store inक्रमmation about pixelक्रमmats
 *			used by the MFC
 */
काष्ठा s5p_mfc_fmt अणु
	u32 fourcc;
	u32 codec_mode;
	क्रमागत s5p_mfc_fmt_type type;
	u32 num_planes;
	u32 versions;
पूर्ण;

/*
 * काष्ठा mfc_control -	काष्ठाure used to store inक्रमmation about MFC controls
 *			it is used to initialize the control framework.
 */
काष्ठा mfc_control अणु
	__u32			id;
	क्रमागत v4l2_ctrl_type	type;
	__u8			name[32];  /* Whatever */
	__s32			minimum;   /* Note चिन्हितness */
	__s32			maximum;
	__s32			step;
	__u32			menu_skip_mask;
	__s32			शेष_value;
	__u32			flags;
	__u32			reserved[2];
	__u8			is_अस्थिर;
पूर्ण;

/* Macro क्रम making hardware specअगरic calls */
#घोषणा s5p_mfc_hw_call(f, op, args...) \
	((f && f->op) ? f->op(args) : (typeof(f->op(args)))(-ENODEV))

#घोषणा fh_to_ctx(__fh) container_of(__fh, काष्ठा s5p_mfc_ctx, fh)
#घोषणा ctrl_to_ctx(__ctrl) \
	container_of((__ctrl)->handler, काष्ठा s5p_mfc_ctx, ctrl_handler)

व्योम clear_work_bit(काष्ठा s5p_mfc_ctx *ctx);
व्योम set_work_bit(काष्ठा s5p_mfc_ctx *ctx);
व्योम clear_work_bit_irqsave(काष्ठा s5p_mfc_ctx *ctx);
व्योम set_work_bit_irqsave(काष्ठा s5p_mfc_ctx *ctx);
पूर्णांक s5p_mfc_get_new_ctx(काष्ठा s5p_mfc_dev *dev);
व्योम s5p_mfc_cleanup_queue(काष्ठा list_head *lh, काष्ठा vb2_queue *vq);

#घोषणा HAS_PORTNUM(dev)	(dev ? (dev->variant ? \
				(dev->variant->port_num ? 1 : 0) : 0) : 0)
#घोषणा IS_TWOPORT(dev)		(dev->variant->port_num == 2 ? 1 : 0)
#घोषणा IS_MFCV6_PLUS(dev)	(dev->variant->version >= 0x60 ? 1 : 0)
#घोषणा IS_MFCV7_PLUS(dev)	(dev->variant->version >= 0x70 ? 1 : 0)
#घोषणा IS_MFCV8_PLUS(dev)	(dev->variant->version >= 0x80 ? 1 : 0)
#घोषणा IS_MFCV10(dev)		(dev->variant->version >= 0xA0 ? 1 : 0)
#घोषणा FW_HAS_E_MIN_SCRATCH_BUF(dev) (IS_MFCV10(dev))

#घोषणा MFC_V5_BIT	BIT(0)
#घोषणा MFC_V6_BIT	BIT(1)
#घोषणा MFC_V7_BIT	BIT(2)
#घोषणा MFC_V8_BIT	BIT(3)
#घोषणा MFC_V10_BIT	BIT(5)

#घोषणा MFC_V5PLUS_BITS		(MFC_V5_BIT | MFC_V6_BIT | MFC_V7_BIT | \
					MFC_V8_BIT | MFC_V10_BIT)
#घोषणा MFC_V6PLUS_BITS		(MFC_V6_BIT | MFC_V7_BIT | MFC_V8_BIT | \
					MFC_V10_BIT)
#घोषणा MFC_V7PLUS_BITS		(MFC_V7_BIT | MFC_V8_BIT | MFC_V10_BIT)

#पूर्ण_अगर /* S5P_MFC_COMMON_H_ */
