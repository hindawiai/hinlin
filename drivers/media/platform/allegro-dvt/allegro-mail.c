<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 *
 * Helper functions क्रम handling messages that are send via mailbox to the
 * Allegro VCU firmware.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>

#समावेश "allegro-mail.h"

स्थिर अक्षर *msg_type_name(क्रमागत mcu_msg_type type)
अणु
	अटल अक्षर buf[9];

	चयन (type) अणु
	हाल MCU_MSG_TYPE_INIT:
		वापस "INIT";
	हाल MCU_MSG_TYPE_CREATE_CHANNEL:
		वापस "CREATE_CHANNEL";
	हाल MCU_MSG_TYPE_DESTROY_CHANNEL:
		वापस "DESTROY_CHANNEL";
	हाल MCU_MSG_TYPE_ENCODE_FRAME:
		वापस "ENCODE_FRAME";
	हाल MCU_MSG_TYPE_PUT_STREAM_BUFFER:
		वापस "PUT_STREAM_BUFFER";
	हाल MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE:
		वापस "PUSH_BUFFER_INTERMEDIATE";
	हाल MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE:
		वापस "PUSH_BUFFER_REFERENCE";
	शेष:
		snम_लिखो(buf, माप(buf), "(0x%04x)", type);
		वापस buf;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(msg_type_name);

अटल sमाप_प्रकार
allegro_enc_init(u32 *dst, काष्ठा mcu_msg_init_request *msg)
अणु
	अचिन्हित पूर्णांक i = 0;
	क्रमागत mcu_msg_version version = msg->header.version;

	dst[i++] = msg->reserved0;
	dst[i++] = msg->suballoc_dma;
	dst[i++] = msg->suballoc_size;
	dst[i++] = msg->l2_cache[0];
	dst[i++] = msg->l2_cache[1];
	dst[i++] = msg->l2_cache[2];
	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		dst[i++] = -1;
		dst[i++] = 0;
	पूर्ण

	वापस i * माप(*dst);
पूर्ण

अटल अंतरभूत u32 settings_get_mcu_codec(काष्ठा create_channel_param *param)
अणु
	क्रमागत mcu_msg_version version = param->version;
	u32 pixelक्रमmat = param->codec;

	अगर (version < MCU_MSG_VERSION_2019_2) अणु
		चयन (pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_HEVC:
			वापस 2;
		हाल V4L2_PIX_FMT_H264:
		शेष:
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_HEVC:
			वापस 1;
		हाल V4L2_PIX_FMT_H264:
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
पूर्ण

sमाप_प्रकार
allegro_encode_config_blob(u32 *dst, काष्ठा create_channel_param *param)
अणु
	क्रमागत mcu_msg_version version = param->version;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक j = 0;
	u32 val;
	अचिन्हित पूर्णांक codec = settings_get_mcu_codec(param);

	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->layer_id;
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->height) |
		   FIELD_PREP(GENMASK(15, 0), param->width);
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->videomode;
	dst[i++] = param->क्रमmat;
	अगर (version < MCU_MSG_VERSION_2019_2)
		dst[i++] = param->colorspace;
	dst[i++] = param->src_mode;
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->src_bit_depth;
	dst[i++] = FIELD_PREP(GENMASK(31, 24), codec) |
		   FIELD_PREP(GENMASK(23, 8), param->स्थिरraपूर्णांक_set_flags) |
		   FIELD_PREP(GENMASK(7, 0), param->profile);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->tier) |
		   FIELD_PREP(GENMASK(15, 0), param->level);

	val = 0;
	val |= param->temporal_mvp_enable ? BIT(20) : 0;
	val |= FIELD_PREP(GENMASK(7, 4), param->log2_max_frame_num);
	अगर (version >= MCU_MSG_VERSION_2019_2)
		val |= FIELD_PREP(GENMASK(3, 0), param->log2_max_poc - 1);
	अन्यथा
		val |= FIELD_PREP(GENMASK(3, 0), param->log2_max_poc);
	dst[i++] = val;

	val = 0;
	val |= param->enable_reordering ? BIT(0) : 0;
	val |= param->dbf_ovr_en ? BIT(2) : 0;
	val |= param->override_lf ? BIT(12) : 0;
	dst[i++] = val;

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		val = 0;
		val |= param->custom_lda ? BIT(2) : 0;
		val |= param->rकरो_cost_mode ? BIT(20) : 0;
		dst[i++] = val;

		val = 0;
		val |= param->lf ? BIT(2) : 0;
		val |= param->lf_x_tile ? BIT(3) : 0;
		val |= param->lf_x_slice ? BIT(4) : 0;
		dst[i++] = val;
	पूर्ण अन्यथा अणु
		val = 0;
		dst[i++] = val;
	पूर्ण

	dst[i++] = FIELD_PREP(GENMASK(15, 8), param->beta_offset) |
		   FIELD_PREP(GENMASK(7, 0), param->tc_offset);
	dst[i++] = param->unknown11;
	dst[i++] = param->unknown12;
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->num_slices;
	अन्यथा
		dst[i++] = FIELD_PREP(GENMASK(31, 16), param->prefetch_स्वतः) |
			   FIELD_PREP(GENMASK(15, 0), param->num_slices);
	dst[i++] = param->prefetch_mem_offset;
	dst[i++] = param->prefetch_mem_size;
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->clip_vrt_range) |
		   FIELD_PREP(GENMASK(15, 0), param->clip_hrz_range);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->me_range[1]) |
		   FIELD_PREP(GENMASK(15, 0), param->me_range[0]);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->me_range[3]) |
		   FIELD_PREP(GENMASK(15, 0), param->me_range[2]);
	dst[i++] = FIELD_PREP(GENMASK(31, 24), param->min_tu_size) |
		   FIELD_PREP(GENMASK(23, 16), param->max_tu_size) |
		   FIELD_PREP(GENMASK(15, 8), param->min_cu_size) |
		   FIELD_PREP(GENMASK(8, 0), param->max_cu_size);
	dst[i++] = FIELD_PREP(GENMASK(15, 8), param->max_transfo_depth_पूर्णांकra) |
		   FIELD_PREP(GENMASK(7, 0), param->max_transfo_depth_पूर्णांकer);
	dst[i++] = param->entropy_mode;
	dst[i++] = param->wp_mode;

	dst[i++] = param->rate_control_mode;
	dst[i++] = param->initial_rem_delay;
	dst[i++] = param->cpb_size;
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->clk_ratio) |
		   FIELD_PREP(GENMASK(15, 0), param->framerate);
	dst[i++] = param->target_bitrate;
	dst[i++] = param->max_bitrate;
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->min_qp) |
		   FIELD_PREP(GENMASK(15, 0), param->initial_qp);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->ip_delta) |
		   FIELD_PREP(GENMASK(15, 0), param->max_qp);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->golden_ref) |
		   FIELD_PREP(GENMASK(15, 0), param->pb_delta);
	dst[i++] = FIELD_PREP(GENMASK(31, 16), param->golden_ref_frequency) |
		   FIELD_PREP(GENMASK(15, 0), param->golden_delta);
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->rate_control_option;
	अन्यथा
		dst[i++] = 0;

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		dst[i++] = param->num_pixel;
		dst[i++] = FIELD_PREP(GENMASK(31, 16), param->max_pixel_value) |
			FIELD_PREP(GENMASK(15, 0), param->max_psnr);
		क्रम (j = 0; j < 3; j++)
			dst[i++] = param->maxpicturesize[j];
	पूर्ण

	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->gop_ctrl_mode;
	अन्यथा
		dst[i++] = 0;

	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = FIELD_PREP(GENMASK(31, 24), param->freq_golden_ref) |
			   FIELD_PREP(GENMASK(23, 16), param->num_b) |
			   FIELD_PREP(GENMASK(15, 0), param->gop_length);
	dst[i++] = param->freq_idr;
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->enable_lt;
	dst[i++] = param->freq_lt;
	dst[i++] = param->gdr_mode;
	अगर (version < MCU_MSG_VERSION_2019_2)
		dst[i++] = FIELD_PREP(GENMASK(31, 24), param->freq_golden_ref) |
			   FIELD_PREP(GENMASK(23, 16), param->num_b) |
			   FIELD_PREP(GENMASK(15, 0), param->gop_length);

	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = param->पंचांगpdqp;

	dst[i++] = param->subframe_latency;
	dst[i++] = param->lda_control_mode;
	अगर (version < MCU_MSG_VERSION_2019_2)
		dst[i++] = param->unknown41;

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		क्रम (j = 0; j < 6; j++)
			dst[i++] = param->lda_factors[j];
		dst[i++] = param->max_num_merge_cand;
	पूर्ण

	वापस i * माप(*dst);
पूर्ण

अटल sमाप_प्रकार
allegro_enc_create_channel(u32 *dst, काष्ठा mcu_msg_create_channel *msg)
अणु
	क्रमागत mcu_msg_version version = msg->header.version;
	अचिन्हित पूर्णांक i = 0;

	dst[i++] = msg->user_id;

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		dst[i++] = msg->blob_mcu_addr;
	पूर्ण अन्यथा अणु
		स_नकल(&dst[i], msg->blob, msg->blob_size);
		i += msg->blob_size / माप(*dst);
	पूर्ण

	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = msg->ep1_addr;

	वापस i * माप(*dst);
पूर्ण

sमाप_प्रकार allegro_decode_config_blob(काष्ठा create_channel_param *param,
				   काष्ठा mcu_msg_create_channel_response *msg,
				   u32 *src)
अणु
	क्रमागत mcu_msg_version version = msg->header.version;

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		param->num_ref_idx_l0 = FIELD_GET(GENMASK(7, 4), src[9]);
		param->num_ref_idx_l1 = FIELD_GET(GENMASK(11, 8), src[9]);
	पूर्ण अन्यथा अणु
		param->num_ref_idx_l0 = msg->num_ref_idx_l0;
		param->num_ref_idx_l1 = msg->num_ref_idx_l1;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
allegro_enc_destroy_channel(u32 *dst, काष्ठा mcu_msg_destroy_channel *msg)
अणु
	अचिन्हित पूर्णांक i = 0;

	dst[i++] = msg->channel_id;

	वापस i * माप(*dst);
पूर्ण

अटल sमाप_प्रकार
allegro_enc_push_buffers(u32 *dst, काष्ठा mcu_msg_push_buffers_पूर्णांकernal *msg)
अणु
	अचिन्हित पूर्णांक i = 0;
	काष्ठा mcu_msg_push_buffers_पूर्णांकernal_buffer *buffer;
	अचिन्हित पूर्णांक num_buffers = msg->num_buffers;
	अचिन्हित पूर्णांक j;

	dst[i++] = msg->channel_id;

	क्रम (j = 0; j < num_buffers; j++) अणु
		buffer = &msg->buffer[j];
		dst[i++] = buffer->dma_addr;
		dst[i++] = buffer->mcu_addr;
		dst[i++] = buffer->size;
	पूर्ण

	वापस i * माप(*dst);
पूर्ण

अटल sमाप_प्रकार
allegro_enc_put_stream_buffer(u32 *dst,
			      काष्ठा mcu_msg_put_stream_buffer *msg)
अणु
	अचिन्हित पूर्णांक i = 0;

	dst[i++] = msg->channel_id;
	dst[i++] = msg->dma_addr;
	dst[i++] = msg->mcu_addr;
	dst[i++] = msg->size;
	dst[i++] = msg->offset;
	dst[i++] = lower_32_bits(msg->dst_handle);
	dst[i++] = upper_32_bits(msg->dst_handle);

	वापस i * माप(*dst);
पूर्ण

अटल sमाप_प्रकार
allegro_enc_encode_frame(u32 *dst, काष्ठा mcu_msg_encode_frame *msg)
अणु
	क्रमागत mcu_msg_version version = msg->header.version;
	अचिन्हित पूर्णांक i = 0;

	dst[i++] = msg->channel_id;

	dst[i++] = msg->reserved;
	dst[i++] = msg->encoding_options;
	dst[i++] = FIELD_PREP(GENMASK(31, 16), msg->padding) |
		   FIELD_PREP(GENMASK(15, 0), msg->pps_qp);

	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		dst[i++] = 0;
		dst[i++] = 0;
		dst[i++] = 0;
		dst[i++] = 0;
	पूर्ण

	dst[i++] = lower_32_bits(msg->user_param);
	dst[i++] = upper_32_bits(msg->user_param);
	dst[i++] = lower_32_bits(msg->src_handle);
	dst[i++] = upper_32_bits(msg->src_handle);
	dst[i++] = msg->request_options;
	dst[i++] = msg->src_y;
	dst[i++] = msg->src_uv;
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = msg->is_10_bit;
	dst[i++] = msg->stride;
	अगर (version >= MCU_MSG_VERSION_2019_2)
		dst[i++] = msg->क्रमmat;
	dst[i++] = msg->ep2;
	dst[i++] = lower_32_bits(msg->ep2_v);
	dst[i++] = upper_32_bits(msg->ep2_v);

	वापस i * माप(*dst);
पूर्ण

अटल sमाप_प्रकार
allegro_dec_init(काष्ठा mcu_msg_init_response *msg, u32 *src)
अणु
	अचिन्हित पूर्णांक i = 0;

	msg->reserved0 = src[i++];

	वापस i * माप(*src);
पूर्ण

अटल sमाप_प्रकार
allegro_dec_create_channel(काष्ठा mcu_msg_create_channel_response *msg,
			   u32 *src)
अणु
	क्रमागत mcu_msg_version version = msg->header.version;
	अचिन्हित पूर्णांक i = 0;

	msg->channel_id = src[i++];
	msg->user_id = src[i++];
	/*
	 * Version >= MCU_MSG_VERSION_2019_2 is handled in
	 * allegro_decode_config_blob().
	 */
	अगर (version < MCU_MSG_VERSION_2019_2) अणु
		msg->options = src[i++];
		msg->num_core = src[i++];
		msg->num_ref_idx_l0 = FIELD_GET(GENMASK(7, 4), src[i]);
		msg->num_ref_idx_l1 = FIELD_GET(GENMASK(11, 8), src[i++]);
	पूर्ण
	msg->पूर्णांक_buffers_count = src[i++];
	msg->पूर्णांक_buffers_size = src[i++];
	msg->rec_buffers_count = src[i++];
	msg->rec_buffers_size = src[i++];
	msg->reserved = src[i++];
	msg->error_code = src[i++];

	वापस i * माप(*src);
पूर्ण

अटल sमाप_प्रकार
allegro_dec_destroy_channel(काष्ठा mcu_msg_destroy_channel_response *msg,
			    u32 *src)
अणु
	अचिन्हित पूर्णांक i = 0;

	msg->channel_id = src[i++];

	वापस i * माप(*src);
पूर्ण

अटल sमाप_प्रकार
allegro_dec_encode_frame(काष्ठा mcu_msg_encode_frame_response *msg, u32 *src)
अणु
	क्रमागत mcu_msg_version version = msg->header.version;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक j;

	msg->channel_id = src[i++];

	msg->dst_handle = src[i++];
	msg->dst_handle |= (((u64)src[i++]) << 32);
	msg->user_param = src[i++];
	msg->user_param |= (((u64)src[i++]) << 32);
	msg->src_handle = src[i++];
	msg->src_handle |= (((u64)src[i++]) << 32);
	msg->skip = FIELD_GET(GENMASK(31, 16), src[i]);
	msg->is_ref = FIELD_GET(GENMASK(15, 0), src[i++]);
	msg->initial_removal_delay = src[i++];
	msg->dpb_output_delay = src[i++];
	msg->size = src[i++];
	msg->frame_tag_size = src[i++];
	msg->stuffing = src[i++];
	msg->filler = src[i++];
	msg->num_column = FIELD_GET(GENMASK(31, 16), src[i]);
	msg->num_row = FIELD_GET(GENMASK(15, 0), src[i++]);
	msg->num_ref_idx_l1 = FIELD_GET(GENMASK(31, 24), src[i]);
	msg->num_ref_idx_l0 = FIELD_GET(GENMASK(23, 16), src[i]);
	msg->qp = FIELD_GET(GENMASK(15, 0), src[i++]);
	msg->partition_table_offset = src[i++];
	msg->partition_table_size = src[i++];
	msg->sum_complex = src[i++];
	क्रम (j = 0; j < 4; j++)
		msg->tile_width[j] = src[i++];
	क्रम (j = 0; j < 22; j++)
		msg->tile_height[j] = src[i++];
	msg->error_code = src[i++];
	msg->slice_type = src[i++];
	msg->pic_काष्ठा = src[i++];
	msg->reserved = FIELD_GET(GENMASK(31, 24), src[i]);
	msg->is_last_slice = FIELD_GET(GENMASK(23, 16), src[i]);
	msg->is_first_slice = FIELD_GET(GENMASK(15, 8), src[i]);
	msg->is_idr = FIELD_GET(GENMASK(7, 0), src[i++]);

	msg->reserved1 = FIELD_GET(GENMASK(31, 16), src[i]);
	msg->pps_qp = FIELD_GET(GENMASK(15, 0), src[i++]);

	msg->reserved2 = src[i++];
	अगर (version >= MCU_MSG_VERSION_2019_2) अणु
		msg->reserved3 = src[i++];
		msg->reserved4 = src[i++];
		msg->reserved5 = src[i++];
		msg->reserved6 = src[i++];
	पूर्ण

	वापस i * माप(*src);
पूर्ण

/**
 * allegro_encode_mail() - Encode allegro messages to firmware क्रमmat
 * @dst: Poपूर्णांकer to the memory that will be filled with data
 * @msg: The allegro message that will be encoded
 */
sमाप_प्रकार allegro_encode_mail(u32 *dst, व्योम *msg)
अणु
	स्थिर काष्ठा mcu_msg_header *header = msg;
	sमाप_प्रकार size;

	अगर (!msg || !dst)
		वापस -EINVAL;

	चयन (header->type) अणु
	हाल MCU_MSG_TYPE_INIT:
		size = allegro_enc_init(&dst[1], msg);
		अवरोध;
	हाल MCU_MSG_TYPE_CREATE_CHANNEL:
		size = allegro_enc_create_channel(&dst[1], msg);
		अवरोध;
	हाल MCU_MSG_TYPE_DESTROY_CHANNEL:
		size = allegro_enc_destroy_channel(&dst[1], msg);
		अवरोध;
	हाल MCU_MSG_TYPE_ENCODE_FRAME:
		size = allegro_enc_encode_frame(&dst[1], msg);
		अवरोध;
	हाल MCU_MSG_TYPE_PUT_STREAM_BUFFER:
		size = allegro_enc_put_stream_buffer(&dst[1], msg);
		अवरोध;
	हाल MCU_MSG_TYPE_PUSH_BUFFER_INTERMEDIATE:
	हाल MCU_MSG_TYPE_PUSH_BUFFER_REFERENCE:
		size = allegro_enc_push_buffers(&dst[1], msg);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * The encoded messages might have dअगरferent length depending on
	 * the firmware version or certain fields. Thereक्रमe, we have to
	 * set the body length after encoding the message.
	 */
	dst[0] = FIELD_PREP(GENMASK(31, 16), header->type) |
		 FIELD_PREP(GENMASK(15, 0), size);

	वापस size + माप(*dst);
पूर्ण

/**
 * allegro_decode_mail() - Parse allegro messages from the firmware.
 * @msg: The mcu_msg_response that will be filled with parsed values.
 * @src: Poपूर्णांकer to the memory that will be parsed
 *
 * The message क्रमmat in the mailbox depends on the firmware. Parse the
 * dअगरferent क्रमmats पूर्णांकo a unअगरorm message क्रमmat that can be used without
 * taking care of the firmware version.
 */
पूर्णांक allegro_decode_mail(व्योम *msg, u32 *src)
अणु
	काष्ठा mcu_msg_header *header;

	अगर (!src || !msg)
		वापस -EINVAL;

	header = msg;
	header->type = FIELD_GET(GENMASK(31, 16), src[0]);

	src++;
	चयन (header->type) अणु
	हाल MCU_MSG_TYPE_INIT:
		allegro_dec_init(msg, src);
		अवरोध;
	हाल MCU_MSG_TYPE_CREATE_CHANNEL:
		allegro_dec_create_channel(msg, src);
		अवरोध;
	हाल MCU_MSG_TYPE_DESTROY_CHANNEL:
		allegro_dec_destroy_channel(msg, src);
		अवरोध;
	हाल MCU_MSG_TYPE_ENCODE_FRAME:
		allegro_dec_encode_frame(msg, src);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
