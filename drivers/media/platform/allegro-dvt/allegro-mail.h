<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Allegro VCU firmware mailbox mail definitions
 */

#अगर_अघोषित ALLEGRO_MAIL_H
#घोषणा ALLEGRO_MAIL_H

#समावेश <linux/kernel.h>

क्रमागत mcu_msg_type अणु
	MCU_MSG_TYPE_INIT = 0x0000,
	MCU_MSG_TYPE_CREATE_CHANNEL = 0x0005,
	MCU_MSG_TYPE_DESTROY_CHANNEL = 0x0006,
	MCU_MSG_TYPE_ENCODE_FRAME = 0x0007,
	MCU_MSG_TYPE_PUT_STREAM_BUFFER = 0x0012,
	MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE = 0x000e,
	MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE = 0x000f,
पूर्ण;

क्रमागत mcu_msg_version अणु
	MCU_MSG_VERSION_2018_2,
	MCU_MSG_VERSION_2019_2,
पूर्ण;

स्थिर अक्षर *msg_type_name(क्रमागत mcu_msg_type type);

काष्ठा mcu_msg_header अणु
	क्रमागत mcu_msg_type type;
	क्रमागत mcu_msg_version version;
पूर्ण;

काष्ठा mcu_msg_init_request अणु
	काष्ठा mcu_msg_header header;
	u32 reserved0;		/* maybe a unused channel id */
	u32 suballoc_dma;
	u32 suballoc_size;
	s32 l2_cache[3];
पूर्ण;

काष्ठा mcu_msg_init_response अणु
	काष्ठा mcu_msg_header header;
	u32 reserved0;
पूर्ण;

काष्ठा create_channel_param अणु
	क्रमागत mcu_msg_version version;
	u32 layer_id;
	u16 width;
	u16 height;
	u32 videomode;
	u32 क्रमmat;
	u32 colorspace;
	u32 src_mode;
	u32 src_bit_depth;
	u8 profile;
	u16 स्थिरraपूर्णांक_set_flags;
	u32 codec;
	u16 level;
	u16 tier;
	u32 log2_max_poc;
	u32 log2_max_frame_num;
	u32 temporal_mvp_enable;
	u32 enable_reordering;
	u32 dbf_ovr_en;
	u32 override_lf;
	u32 num_ref_idx_l0;
	u32 num_ref_idx_l1;
	u32 custom_lda;
	u32 rकरो_cost_mode;
	u32 lf;
	u32 lf_x_tile;
	u32 lf_x_slice;
	s8 beta_offset;
	s8 tc_offset;
	u16 reserved10;
	u32 unknown11;
	u32 unknown12;
	u16 num_slices;
	u16 prefetch_स्वतः;
	u32 prefetch_mem_offset;
	u32 prefetch_mem_size;
	u16 clip_hrz_range;
	u16 clip_vrt_range;
	u16 me_range[4];
	u8 max_cu_size;
	u8 min_cu_size;
	u8 max_tu_size;
	u8 min_tu_size;
	u8 max_transfo_depth_पूर्णांकer;
	u8 max_transfo_depth_पूर्णांकra;
	u16 reserved20;
	u32 entropy_mode;
	u32 wp_mode;

	/* rate control param */
	u32 rate_control_mode;
	u32 initial_rem_delay;
	u32 cpb_size;
	u16 framerate;
	u16 clk_ratio;
	u32 target_bitrate;
	u32 max_bitrate;
	u16 initial_qp;
	u16 min_qp;
	u16 max_qp;
	s16 ip_delta;
	s16 pb_delta;
	u16 golden_ref;
	u16 golden_delta;
	u16 golden_ref_frequency;
	u32 rate_control_option;
	u32 num_pixel;
	u16 max_psnr;
	u16 max_pixel_value;
	u32 maxpicturesize[3];

	/* gop param */
	u32 gop_ctrl_mode;
	u32 freq_idr;
	u32 freq_lt;
	u32 gdr_mode;
	u16 gop_length;
	u8 num_b;
	u8 freq_golden_ref;
	u32 enable_lt;
	u32 पंचांगpdqp;

	u32 subframe_latency;
	u32 lda_control_mode;
	u32 unknown41;

	u32 lda_factors[6];

	u32 max_num_merge_cand;
पूर्ण;

काष्ठा mcu_msg_create_channel अणु
	काष्ठा mcu_msg_header header;
	u32 user_id;
	u32 *blob;
	माप_प्रकार blob_size;
	u32 blob_mcu_addr;
	u32 ep1_addr;
पूर्ण;

काष्ठा mcu_msg_create_channel_response अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
	u32 user_id;
	u32 options;
	u32 num_core;
	u32 num_ref_idx_l0;
	u32 num_ref_idx_l1;
	u32 पूर्णांक_buffers_count;
	u32 पूर्णांक_buffers_size;
	u32 rec_buffers_count;
	u32 rec_buffers_size;
	u32 reserved;
	u32 error_code;
पूर्ण;

काष्ठा mcu_msg_destroy_channel अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
पूर्ण;

काष्ठा mcu_msg_destroy_channel_response अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
पूर्ण;

काष्ठा mcu_msg_push_buffers_पूर्णांकernal_buffer अणु
	u32 dma_addr;
	u32 mcu_addr;
	u32 size;
पूर्ण;

काष्ठा mcu_msg_push_buffers_पूर्णांकernal अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
	माप_प्रकार num_buffers;
	काष्ठा mcu_msg_push_buffers_पूर्णांकernal_buffer buffer[];
पूर्ण;

काष्ठा mcu_msg_put_stream_buffer अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
	u32 dma_addr;
	u32 mcu_addr;
	u32 size;
	u32 offset;
	u64 dst_handle;
पूर्ण;

काष्ठा mcu_msg_encode_frame अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
	u32 reserved;

	u32 encoding_options;
#घोषणा AL_OPT_USE_QP_TABLE		BIT(0)
#घोषणा AL_OPT_FORCE_LOAD		BIT(1)
#घोषणा AL_OPT_USE_L2			BIT(2)
#घोषणा AL_OPT_DISABLE_INTRA		BIT(3)
#घोषणा AL_OPT_DEPENDENT_SLICES		BIT(4)

	s16 pps_qp;
	u16 padding;
	u64 user_param;
	u64 src_handle;

	u32 request_options;
#घोषणा AL_OPT_SCENE_CHANGE		BIT(0)
#घोषणा AL_OPT_RESTART_GOP		BIT(1)
#घोषणा AL_OPT_USE_LONG_TERM		BIT(2)
#घोषणा AL_OPT_UPDATE_PARAMS		BIT(3)

	/* u32 scene_change_delay (optional) */
	/* rate control param (optional) */
	/* gop param (optional) */
	/* dynamic resolution params (optional) */
	u32 src_y;
	u32 src_uv;
	u32 is_10_bit;
	u32 stride;
	u32 क्रमmat;
	u32 ep2;
	u64 ep2_v;
पूर्ण;

काष्ठा mcu_msg_encode_frame_response अणु
	काष्ठा mcu_msg_header header;
	u32 channel_id;
	u64 dst_handle;		/* see mcu_msg_put_stream_buffer */
	u64 user_param;		/* see mcu_msg_encode_frame */
	u64 src_handle;		/* see mcu_msg_encode_frame */
	u16 skip;
	u16 is_ref;
	u32 initial_removal_delay;
	u32 dpb_output_delay;
	u32 size;
	u32 frame_tag_size;
	s32 stuffing;
	s32 filler;
	u16 num_column;
	u16 num_row;
	u16 qp;
	u8 num_ref_idx_l0;
	u8 num_ref_idx_l1;
	u32 partition_table_offset;
	s32 partition_table_size;
	u32 sum_complex;
	s32 tile_width[4];
	s32 tile_height[22];
	u32 error_code;

	u32 slice_type;
#घोषणा AL_ENC_SLICE_TYPE_B             0
#घोषणा AL_ENC_SLICE_TYPE_P             1
#घोषणा AL_ENC_SLICE_TYPE_I             2

	u32 pic_काष्ठा;
	u8 is_idr;
	u8 is_first_slice;
	u8 is_last_slice;
	u8 reserved;
	u16 pps_qp;
	u16 reserved1;
	u32 reserved2;
	u32 reserved3;
	u32 reserved4;
	u32 reserved5;
	u32 reserved6;
पूर्ण;

जोड़ mcu_msg_response अणु
	काष्ठा mcu_msg_header header;
	काष्ठा mcu_msg_init_response init;
	काष्ठा mcu_msg_create_channel_response create_channel;
	काष्ठा mcu_msg_destroy_channel_response destroy_channel;
	काष्ठा mcu_msg_encode_frame_response encode_frame;
पूर्ण;

sमाप_प्रकार allegro_encode_config_blob(u32 *dst, काष्ठा create_channel_param *param);
sमाप_प्रकार allegro_decode_config_blob(काष्ठा create_channel_param *param,
				   काष्ठा mcu_msg_create_channel_response *msg,
				   u32 *src);

पूर्णांक allegro_decode_mail(व्योम *msg, u32 *src);
sमाप_प्रकार allegro_encode_mail(u32 *dst, व्योम *msg);

#पूर्ण_अगर
