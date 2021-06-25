<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hash.h>

#समावेश "hfi_cmds.h"

अटल क्रमागत hfi_version hfi_ver;

व्योम pkt_sys_init(काष्ठा hfi_sys_init_pkt *pkt, u32 arch_type)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_INIT;
	pkt->arch_type = arch_type;
पूर्ण

व्योम pkt_sys_pc_prep(काष्ठा hfi_sys_pc_prep_pkt *pkt)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_PC_PREP;
पूर्ण

व्योम pkt_sys_idle_indicator(काष्ठा hfi_sys_set_property_pkt *pkt, u32 enable)
अणु
	काष्ठा hfi_enable *hfi = (काष्ठा hfi_enable *)&pkt->data[1];

	pkt->hdr.size = माप(*pkt) + माप(*hfi) + माप(u32);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_IDLE_INDICATOR;
	hfi->enable = enable;
पूर्ण

व्योम pkt_sys_debug_config(काष्ठा hfi_sys_set_property_pkt *pkt, u32 mode,
			  u32 config)
अणु
	काष्ठा hfi_debug_config *hfi;

	pkt->hdr.size = माप(*pkt) + माप(*hfi) + माप(u32);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_DEBUG_CONFIG;
	hfi = (काष्ठा hfi_debug_config *)&pkt->data[1];
	hfi->config = config;
	hfi->mode = mode;
पूर्ण

व्योम pkt_sys_coverage_config(काष्ठा hfi_sys_set_property_pkt *pkt, u32 mode)
अणु
	pkt->hdr.size = माप(*pkt) + माप(u32);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_CONFIG_COVERAGE;
	pkt->data[1] = mode;
पूर्ण

पूर्णांक pkt_sys_set_resource(काष्ठा hfi_sys_set_resource_pkt *pkt, u32 id, u32 size,
			 u32 addr, व्योम *cookie)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_RESOURCE;
	pkt->resource_handle = hash32_ptr(cookie);

	चयन (id) अणु
	हाल VIDC_RESOURCE_OCMEM:
	हाल VIDC_RESOURCE_VMEM: अणु
		काष्ठा hfi_resource_ocmem *res =
			(काष्ठा hfi_resource_ocmem *)&pkt->resource_data[0];

		res->size = size;
		res->mem = addr;
		pkt->resource_type = HFI_RESOURCE_OCMEM;
		pkt->hdr.size += माप(*res) - माप(u32);
		अवरोध;
	पूर्ण
	हाल VIDC_RESOURCE_NONE:
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pkt_sys_unset_resource(काष्ठा hfi_sys_release_resource_pkt *pkt, u32 id,
			   u32 size, व्योम *cookie)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_RELEASE_RESOURCE;
	pkt->resource_handle = hash32_ptr(cookie);

	चयन (id) अणु
	हाल VIDC_RESOURCE_OCMEM:
	हाल VIDC_RESOURCE_VMEM:
		pkt->resource_type = HFI_RESOURCE_OCMEM;
		अवरोध;
	हाल VIDC_RESOURCE_NONE:
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

व्योम pkt_sys_ping(काष्ठा hfi_sys_ping_pkt *pkt, u32 cookie)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_PING;
	pkt->client_data = cookie;
पूर्ण

व्योम pkt_sys_घातer_control(काष्ठा hfi_sys_set_property_pkt *pkt, u32 enable)
अणु
	काष्ठा hfi_enable *hfi = (काष्ठा hfi_enable *)&pkt->data[1];

	pkt->hdr.size = माप(*pkt) + माप(*hfi) + माप(u32);
	pkt->hdr.pkt_type = HFI_CMD_SYS_SET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_CODEC_POWER_PLANE_CTRL;
	hfi->enable = enable;
पूर्ण

पूर्णांक pkt_sys_ssr_cmd(काष्ठा hfi_sys_test_ssr_pkt *pkt, u32 trigger_type)
अणु
	चयन (trigger_type) अणु
	हाल HFI_TEST_SSR_SW_ERR_FATAL:
	हाल HFI_TEST_SSR_SW_DIV_BY_ZERO:
	हाल HFI_TEST_SSR_HW_WDOG_IRQ:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_TEST_SSR;
	pkt->trigger_type = trigger_type;

	वापस 0;
पूर्ण

व्योम pkt_sys_image_version(काष्ठा hfi_sys_get_property_pkt *pkt)
अणु
	pkt->hdr.size = माप(*pkt);
	pkt->hdr.pkt_type = HFI_CMD_SYS_GET_PROPERTY;
	pkt->num_properties = 1;
	pkt->data[0] = HFI_PROPERTY_SYS_IMAGE_VERSION;
पूर्ण

पूर्णांक pkt_session_init(काष्ठा hfi_session_init_pkt *pkt, व्योम *cookie,
		     u32 session_type, u32 codec)
अणु
	अगर (!pkt || !cookie || !codec)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SYS_SESSION_INIT;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->session_करोमुख्य = session_type;
	pkt->session_codec = codec;

	वापस 0;
पूर्ण

व्योम pkt_session_cmd(काष्ठा hfi_session_pkt *pkt, u32 pkt_type, व्योम *cookie)
अणु
	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = pkt_type;
	pkt->shdr.session_id = hash32_ptr(cookie);
पूर्ण

पूर्णांक pkt_session_set_buffers(काष्ठा hfi_session_set_buffers_pkt *pkt,
			    व्योम *cookie, काष्ठा hfi_buffer_desc *bd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!cookie || !pkt || !bd)
		वापस -EINVAL;

	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_BUFFERS;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->buffer_size = bd->buffer_size;
	pkt->min_buffer_size = bd->buffer_size;
	pkt->num_buffers = bd->num_buffers;

	अगर (bd->buffer_type == HFI_BUFFER_OUTPUT ||
	    bd->buffer_type == HFI_BUFFER_OUTPUT2) अणु
		काष्ठा hfi_buffer_info *bi;

		pkt->extradata_size = bd->extradata_size;
		pkt->shdr.hdr.size = माप(*pkt) - माप(u32) +
			(bd->num_buffers * माप(*bi));
		bi = (काष्ठा hfi_buffer_info *)pkt->buffer_info;
		क्रम (i = 0; i < pkt->num_buffers; i++) अणु
			bi->buffer_addr = bd->device_addr;
			bi->extradata_addr = bd->extradata_addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		pkt->extradata_size = 0;
		pkt->shdr.hdr.size = माप(*pkt) +
			((bd->num_buffers - 1) * माप(u32));
		क्रम (i = 0; i < pkt->num_buffers; i++)
			pkt->buffer_info[i] = bd->device_addr;
	पूर्ण

	pkt->buffer_type = bd->buffer_type;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_unset_buffers(काष्ठा hfi_session_release_buffer_pkt *pkt,
			      व्योम *cookie, काष्ठा hfi_buffer_desc *bd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!cookie || !pkt || !bd)
		वापस -EINVAL;

	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_RELEASE_BUFFERS;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->buffer_size = bd->buffer_size;
	pkt->num_buffers = bd->num_buffers;

	अगर (bd->buffer_type == HFI_BUFFER_OUTPUT ||
	    bd->buffer_type == HFI_BUFFER_OUTPUT2) अणु
		काष्ठा hfi_buffer_info *bi;

		bi = (काष्ठा hfi_buffer_info *)pkt->buffer_info;
		क्रम (i = 0; i < pkt->num_buffers; i++) अणु
			bi->buffer_addr = bd->device_addr;
			bi->extradata_addr = bd->extradata_addr;
		पूर्ण
		pkt->shdr.hdr.size =
				माप(काष्ठा hfi_session_set_buffers_pkt) -
				माप(u32) + (bd->num_buffers * माप(*bi));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pkt->num_buffers; i++)
			pkt->buffer_info[i] = bd->device_addr;

		pkt->extradata_size = 0;
		pkt->shdr.hdr.size =
				माप(काष्ठा hfi_session_set_buffers_pkt) +
				((bd->num_buffers - 1) * माप(u32));
	पूर्ण

	pkt->response_req = bd->response_required;
	pkt->buffer_type = bd->buffer_type;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_etb_decoder(काष्ठा hfi_session_empty_buffer_compressed_pkt *pkt,
			    व्योम *cookie, काष्ठा hfi_frame_data *in_frame)
अणु
	अगर (!cookie)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_EMPTY_BUFFER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->समय_stamp_hi = upper_32_bits(in_frame->बारtamp);
	pkt->समय_stamp_lo = lower_32_bits(in_frame->बारtamp);
	pkt->flags = in_frame->flags;
	pkt->mark_target = in_frame->mark_target;
	pkt->mark_data = in_frame->mark_data;
	pkt->offset = in_frame->offset;
	pkt->alloc_len = in_frame->alloc_len;
	pkt->filled_len = in_frame->filled_len;
	pkt->input_tag = in_frame->clnt_data;
	pkt->packet_buffer = in_frame->device_addr;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_etb_encoder(
		काष्ठा hfi_session_empty_buffer_uncompressed_plane0_pkt *pkt,
		व्योम *cookie, काष्ठा hfi_frame_data *in_frame)
अणु
	अगर (!cookie || !in_frame->device_addr)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_EMPTY_BUFFER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->view_id = 0;
	pkt->समय_stamp_hi = upper_32_bits(in_frame->बारtamp);
	pkt->समय_stamp_lo = lower_32_bits(in_frame->बारtamp);
	pkt->flags = in_frame->flags;
	pkt->mark_target = in_frame->mark_target;
	pkt->mark_data = in_frame->mark_data;
	pkt->offset = in_frame->offset;
	pkt->alloc_len = in_frame->alloc_len;
	pkt->filled_len = in_frame->filled_len;
	pkt->input_tag = in_frame->clnt_data;
	pkt->packet_buffer = in_frame->device_addr;
	pkt->extradata_buffer = in_frame->extradata_addr;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_ftb(काष्ठा hfi_session_fill_buffer_pkt *pkt, व्योम *cookie,
		    काष्ठा hfi_frame_data *out_frame)
अणु
	अगर (!cookie || !out_frame || !out_frame->device_addr)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_FILL_BUFFER;
	pkt->shdr.session_id = hash32_ptr(cookie);

	अगर (out_frame->buffer_type == HFI_BUFFER_OUTPUT)
		pkt->stream_id = 0;
	अन्यथा अगर (out_frame->buffer_type == HFI_BUFFER_OUTPUT2)
		pkt->stream_id = 1;

	pkt->output_tag = out_frame->clnt_data;
	pkt->packet_buffer = out_frame->device_addr;
	pkt->extradata_buffer = out_frame->extradata_addr;
	pkt->alloc_len = out_frame->alloc_len;
	pkt->filled_len = out_frame->filled_len;
	pkt->offset = out_frame->offset;
	pkt->data[0] = out_frame->extradata_size;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_parse_seq_header(
		काष्ठा hfi_session_parse_sequence_header_pkt *pkt,
		व्योम *cookie, u32 seq_hdr, u32 seq_hdr_len)
अणु
	अगर (!cookie || !seq_hdr || !seq_hdr_len)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_PARSE_SEQUENCE_HEADER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->header_len = seq_hdr_len;
	pkt->packet_buffer = seq_hdr;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_get_seq_hdr(काष्ठा hfi_session_get_sequence_header_pkt *pkt,
			    व्योम *cookie, u32 seq_hdr, u32 seq_hdr_len)
अणु
	अगर (!cookie || !seq_hdr || !seq_hdr_len)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_GET_SEQUENCE_HEADER;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->buffer_len = seq_hdr_len;
	pkt->packet_buffer = seq_hdr;

	वापस 0;
पूर्ण

पूर्णांक pkt_session_flush(काष्ठा hfi_session_flush_pkt *pkt, व्योम *cookie, u32 type)
अणु
	चयन (type) अणु
	हाल HFI_FLUSH_INPUT:
	हाल HFI_FLUSH_OUTPUT:
	हाल HFI_FLUSH_OUTPUT2:
	हाल HFI_FLUSH_ALL:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_FLUSH;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->flush_type = type;

	वापस 0;
पूर्ण

अटल पूर्णांक pkt_session_get_property_1x(काष्ठा hfi_session_get_property_pkt *pkt,
				       व्योम *cookie, u32 ptype)
अणु
	चयन (ptype) अणु
	हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT:
	हाल HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_GET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	वापस 0;
पूर्ण

अटल पूर्णांक pkt_session_set_property_1x(काष्ठा hfi_session_set_property_pkt *pkt,
				       व्योम *cookie, u32 ptype, व्योम *pdata)
अणु
	व्योम *prop_data;
	पूर्णांक ret = 0;

	अगर (!pkt || !cookie || !pdata)
		वापस -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	चयन (ptype) अणु
	हाल HFI_PROPERTY_CONFIG_FRAME_RATE: अणु
		काष्ठा hfi_framerate *in = pdata, *frate = prop_data;

		frate->buffer_type = in->buffer_type;
		frate->framerate = in->framerate;
		pkt->shdr.hdr.size += माप(u32) + माप(*frate);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SELECT: अणु
		काष्ठा hfi_uncompressed_क्रमmat_select *in = pdata;
		काष्ठा hfi_uncompressed_क्रमmat_select *hfi = prop_data;

		hfi->buffer_type = in->buffer_type;
		hfi->क्रमmat = in->क्रमmat;
		pkt->shdr.hdr.size += माप(u32) + माप(*hfi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_FRAME_SIZE: अणु
		काष्ठा hfi_framesize *in = pdata, *fsize = prop_data;

		fsize->buffer_type = in->buffer_type;
		fsize->height = in->height;
		fsize->width = in->width;
		pkt->shdr.hdr.size += माप(u32) + माप(*fsize);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_REALTIME: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL: अणु
		काष्ठा hfi_buffer_count_actual *in = pdata, *count = prop_data;

		count->count_actual = in->count_actual;
		count->type = in->type;
		pkt->shdr.hdr.size += माप(u32) + माप(*count);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL: अणु
		काष्ठा hfi_buffer_size_actual *in = pdata, *sz = prop_data;

		sz->size = in->size;
		sz->type = in->type;
		pkt->shdr.hdr.size += माप(u32) + माप(*sz);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_BUFFER_DISPLAY_HOLD_COUNT_ACTUAL: अणु
		काष्ठा hfi_buffer_display_hold_count_actual *in = pdata;
		काष्ठा hfi_buffer_display_hold_count_actual *count = prop_data;

		count->hold_count = in->hold_count;
		count->type = in->type;
		pkt->shdr.hdr.size += माप(u32) + माप(*count);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SELECT: अणु
		काष्ठा hfi_nal_stream_क्रमmat_select *in = pdata;
		काष्ठा hfi_nal_stream_क्रमmat_select *fmt = prop_data;

		fmt->क्रमmat = in->क्रमmat;
		pkt->shdr.hdr.size += माप(u32) + माप(*fmt);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_OUTPUT_ORDER: अणु
		u32 *in = pdata;

		चयन (*in) अणु
		हाल HFI_OUTPUT_ORDER_DECODE:
		हाल HFI_OUTPUT_ORDER_DISPLAY:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_PICTURE_TYPE_DECODE: अणु
		काष्ठा hfi_enable_picture *in = pdata, *en = prop_data;

		en->picture_type = in->picture_type;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_OUTPUT2_KEEP_ASPECT_RATIO: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER: अणु
		काष्ठा hfi_enable *in = pdata;
		काष्ठा hfi_enable *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM: अणु
		काष्ठा hfi_multi_stream *in = pdata, *multi = prop_data;

		multi->buffer_type = in->buffer_type;
		multi->enable = in->enable;
		multi->width = in->width;
		multi->height = in->height;
		pkt->shdr.hdr.size += माप(u32) + माप(*multi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_DISPLAY_PICTURE_BUFFER_COUNT: अणु
		काष्ठा hfi_display_picture_buffer_count *in = pdata;
		काष्ठा hfi_display_picture_buffer_count *count = prop_data;

		count->count = in->count;
		count->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*count);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_DIVX_FORMAT: अणु
		u32 *in = pdata;

		चयन (*in) अणु
		हाल HFI_DIVX_FORMAT_4:
		हाल HFI_DIVX_FORMAT_5:
		हाल HFI_DIVX_FORMAT_6:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VDEC_MB_ERROR_MAP_REPORTING: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_THUMBNAIL_MODE: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME:
		pkt->shdr.hdr.size += माप(u32);
		अवरोध;
	हाल HFI_PROPERTY_PARAM_VENC_MPEG4_SHORT_HEADER:
		अवरोध;
	हाल HFI_PROPERTY_PARAM_VENC_MPEG4_AC_PREDICTION:
		अवरोध;
	हाल HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE: अणु
		काष्ठा hfi_bitrate *in = pdata, *brate = prop_data;

		brate->bitrate = in->bitrate;
		brate->layer_id = in->layer_id;
		pkt->shdr.hdr.size += माप(u32) + माप(*brate);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE: अणु
		काष्ठा hfi_bitrate *in = pdata, *hfi = prop_data;

		hfi->bitrate = in->bitrate;
		hfi->layer_id = in->layer_id;
		pkt->shdr.hdr.size += माप(u32) + माप(*hfi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT: अणु
		काष्ठा hfi_profile_level *in = pdata, *pl = prop_data;

		pl->level = in->level;
		pl->profile = in->profile;
		अगर (pl->profile <= 0)
			/* Profile not supported, falling back to high */
			pl->profile = HFI_H264_PROखाता_HIGH;

		अगर (!pl->level)
			/* Level not supported, falling back to 1 */
			pl->level = 1;

		pkt->shdr.hdr.size += माप(u32) + माप(*pl);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_ENTROPY_CONTROL: अणु
		काष्ठा hfi_h264_entropy_control *in = pdata, *hfi = prop_data;

		hfi->entropy_mode = in->entropy_mode;
		अगर (hfi->entropy_mode == HFI_H264_ENTROPY_CABAC)
			hfi->cabac_model = in->cabac_model;
		pkt->shdr.hdr.size += माप(u32) + माप(*hfi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_RATE_CONTROL: अणु
		u32 *in = pdata;

		चयन (*in) अणु
		हाल HFI_RATE_CONTROL_OFF:
		हाल HFI_RATE_CONTROL_CBR_CFR:
		हाल HFI_RATE_CONTROL_CBR_VFR:
		हाल HFI_RATE_CONTROL_VBR_CFR:
		हाल HFI_RATE_CONTROL_VBR_VFR:
		हाल HFI_RATE_CONTROL_CQ:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_MPEG4_TIME_RESOLUTION: अणु
		काष्ठा hfi_mpeg4_समय_resolution *in = pdata, *res = prop_data;

		res->समय_increment_resolution = in->समय_increment_resolution;
		pkt->shdr.hdr.size += माप(u32) + माप(*res);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_MPEG4_HEADER_EXTENSION: अणु
		काष्ठा hfi_mpeg4_header_extension *in = pdata, *ext = prop_data;

		ext->header_extension = in->header_extension;
		pkt->shdr.hdr.size += माप(u32) + माप(*ext);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_DEBLOCK_CONTROL: अणु
		काष्ठा hfi_h264_db_control *in = pdata, *db = prop_data;

		चयन (in->mode) अणु
		हाल HFI_H264_DB_MODE_DISABLE:
		हाल HFI_H264_DB_MODE_SKIP_SLICE_BOUNDARY:
		हाल HFI_H264_DB_MODE_ALL_BOUNDARY:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		db->mode = in->mode;
		db->slice_alpha_offset = in->slice_alpha_offset;
		db->slice_beta_offset = in->slice_beta_offset;
		pkt->shdr.hdr.size += माप(u32) + माप(*db);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_SESSION_QP: अणु
		काष्ठा hfi_quantization *in = pdata, *quant = prop_data;

		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		quant->layer_id = in->layer_id;
		pkt->shdr.hdr.size += माप(u32) + माप(*quant);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE: अणु
		काष्ठा hfi_quantization_range *in = pdata, *range = prop_data;
		u32 min_qp, max_qp;

		min_qp = in->min_qp;
		max_qp = in->max_qp;

		/* We'll be packing in the qp, so make sure we
		 * won't be losing data when masking
		 */
		अगर (min_qp > 0xff || max_qp > 0xff) अणु
			ret = -दुस्फल;
			अवरोध;
		पूर्ण

		/* When creating the packet, pack the qp value as
		 * 0xiippbb, where ii = qp range क्रम I-frames,
		 * pp = qp range क्रम P-frames, etc.
		 */
		range->min_qp = min_qp | min_qp << 8 | min_qp << 16;
		range->max_qp = max_qp | max_qp << 8 | max_qp << 16;
		range->layer_id = in->layer_id;

		pkt->shdr.hdr.size += माप(u32) + माप(*range);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_VC1_PERF_CFG: अणु
		काष्ठा hfi_vc1e_perf_cfg_type *in = pdata, *perf = prop_data;

		स_नकल(perf->search_range_x_subsampled,
		       in->search_range_x_subsampled,
		       माप(perf->search_range_x_subsampled));
		स_नकल(perf->search_range_y_subsampled,
		       in->search_range_y_subsampled,
		       माप(perf->search_range_y_subsampled));

		pkt->shdr.hdr.size += माप(u32) + माप(*perf);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_MAX_NUM_B_FRAMES: अणु
		काष्ठा hfi_max_num_b_frames *bframes = prop_data;
		u32 *in = pdata;

		bframes->max_num_b_frames = *in;
		pkt->shdr.hdr.size += माप(u32) + माप(*bframes);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_INTRA_PERIOD: अणु
		काष्ठा hfi_पूर्णांकra_period *in = pdata, *पूर्णांकra = prop_data;

		पूर्णांकra->pframes = in->pframes;
		पूर्णांकra->bframes = in->bframes;
		pkt->shdr.hdr.size += माप(u32) + माप(*पूर्णांकra);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_IDR_PERIOD: अणु
		काष्ठा hfi_idr_period *in = pdata, *idr = prop_data;

		idr->idr_period = in->idr_period;
		pkt->shdr.hdr.size += माप(u32) + माप(*idr);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR: अणु
		काष्ठा hfi_conceal_color *color = prop_data;
		u32 *in = pdata;

		color->conceal_color = *in & 0xff;
		color->conceal_color |= ((*in >> 10) & 0xff) << 8;
		color->conceal_color |= ((*in >> 20) & 0xff) << 16;
		pkt->shdr.hdr.size += माप(u32) + माप(*color);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VPE_OPERATIONS: अणु
		काष्ठा hfi_operations_type *in = pdata, *ops = prop_data;

		चयन (in->rotation) अणु
		हाल HFI_ROTATE_NONE:
		हाल HFI_ROTATE_90:
		हाल HFI_ROTATE_180:
		हाल HFI_ROTATE_270:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		चयन (in->flip) अणु
		हाल HFI_FLIP_NONE:
		हाल HFI_FLIP_HORIZONTAL:
		हाल HFI_FLIP_VERTICAL:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ops->rotation = in->rotation;
		ops->flip = in->flip;
		pkt->shdr.hdr.size += माप(u32) + माप(*ops);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH: अणु
		काष्ठा hfi_पूर्णांकra_refresh *in = pdata, *पूर्णांकra = prop_data;

		चयन (in->mode) अणु
		हाल HFI_INTRA_REFRESH_NONE:
		हाल HFI_INTRA_REFRESH_ADAPTIVE:
		हाल HFI_INTRA_REFRESH_CYCLIC:
		हाल HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE:
		हाल HFI_INTRA_REFRESH_RANDOM:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		पूर्णांकra->mode = in->mode;
		पूर्णांकra->air_mbs = in->air_mbs;
		पूर्णांकra->air_ref = in->air_ref;
		पूर्णांकra->cir_mbs = in->cir_mbs;
		pkt->shdr.hdr.size += माप(u32) + माप(*पूर्णांकra);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_CONTROL: अणु
		काष्ठा hfi_multi_slice_control *in = pdata, *multi = prop_data;

		चयन (in->multi_slice) अणु
		हाल HFI_MULTI_SLICE_OFF:
		हाल HFI_MULTI_SLICE_GOB:
		हाल HFI_MULTI_SLICE_BY_MB_COUNT:
		हाल HFI_MULTI_SLICE_BY_BYTE_COUNT:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		multi->multi_slice = in->multi_slice;
		multi->slice_size = in->slice_size;
		pkt->shdr.hdr.size += माप(u32) + माप(*multi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_SLICE_DELIVERY_MODE: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_VUI_TIMING_INFO: अणु
		काष्ठा hfi_h264_vui_timing_info *in = pdata, *vui = prop_data;

		vui->enable = in->enable;
		vui->fixed_framerate = in->fixed_framerate;
		vui->समय_scale = in->समय_scale;
		pkt->shdr.hdr.size += माप(u32) + माप(*vui);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VPE_DEINTERLACE: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_GENERATE_AUDNAL: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE: अणु
		काष्ठा hfi_buffer_alloc_mode *in = pdata, *mode = prop_data;

		mode->type = in->type;
		mode->mode = in->mode;
		pkt->shdr.hdr.size += माप(u32) + माप(*mode);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_FRAME_ASSEMBLY: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_VUI_BITSTREAM_RESTRC: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_PRESERVE_TEXT_QUALITY: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_SCS_THRESHOLD: अणु
		काष्ठा hfi_scs_threshold *thres = prop_data;
		u32 *in = pdata;

		thres->threshold_value = *in;
		pkt->shdr.hdr.size += माप(u32) + माप(*thres);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_MVC_BUFFER_LAYOUT: अणु
		काष्ठा hfi_mvc_buffer_layout_descp_type *in = pdata;
		काष्ठा hfi_mvc_buffer_layout_descp_type *mvc = prop_data;

		चयन (in->layout_type) अणु
		हाल HFI_MVC_BUFFER_LAYOUT_TOP_BOTTOM:
		हाल HFI_MVC_BUFFER_LAYOUT_SEQ:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		mvc->layout_type = in->layout_type;
		mvc->bright_view_first = in->bright_view_first;
		mvc->ngap = in->ngap;
		pkt->shdr.hdr.size += माप(u32) + माप(*mvc);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_LTRMODE: अणु
		काष्ठा hfi_ltr_mode *in = pdata, *ltr = prop_data;

		चयन (in->ltr_mode) अणु
		हाल HFI_LTR_MODE_DISABLE:
		हाल HFI_LTR_MODE_MANUAL:
		हाल HFI_LTR_MODE_PERIODIC:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ltr->ltr_mode = in->ltr_mode;
		ltr->ltr_count = in->ltr_count;
		ltr->trust_mode = in->trust_mode;
		pkt->shdr.hdr.size += माप(u32) + माप(*ltr);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_USELTRFRAME: अणु
		काष्ठा hfi_ltr_use *in = pdata, *ltr_use = prop_data;

		ltr_use->frames = in->frames;
		ltr_use->ref_ltr = in->ref_ltr;
		ltr_use->use_स्थिरrnt = in->use_स्थिरrnt;
		pkt->shdr.hdr.size += माप(u32) + माप(*ltr_use);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_MARKLTRFRAME: अणु
		काष्ठा hfi_ltr_mark *in = pdata, *ltr_mark = prop_data;

		ltr_mark->mark_frame = in->mark_frame;
		pkt->shdr.hdr.size += माप(u32) + माप(*ltr_mark);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_HIER_P_MAX_NUM_ENH_LAYER: अणु
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_HIER_P_ENH_LAYER: अणु
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_DISABLE_RC_TIMESTAMP: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_INITIAL_QP: अणु
		काष्ठा hfi_initial_quantization *in = pdata, *quant = prop_data;

		quant->init_qp_enable = in->init_qp_enable;
		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		pkt->shdr.hdr.size += माप(u32) + माप(*quant);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VPE_COLOR_SPACE_CONVERSION: अणु
		काष्ठा hfi_vpe_color_space_conversion *in = pdata;
		काष्ठा hfi_vpe_color_space_conversion *csc = prop_data;

		स_नकल(csc->csc_matrix, in->csc_matrix,
		       माप(csc->csc_matrix));
		स_नकल(csc->csc_bias, in->csc_bias, माप(csc->csc_bias));
		स_नकल(csc->csc_limit, in->csc_limit, माप(csc->csc_limit));
		pkt->shdr.hdr.size += माप(u32) + माप(*csc);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_VPX_ERROR_RESILIENCE_MODE: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_H264_NAL_SVC_EXT: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VENC_PERF_MODE: अणु
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_HIER_B_MAX_NUM_ENH_LAYER: अणु
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdr.hdr.size += माप(u32) * 2;
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_NONCP_OUTPUT2: अणु
		काष्ठा hfi_enable *in = pdata, *en = prop_data;

		en->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*en);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_HIER_P_HYBRID_MODE: अणु
		काष्ठा hfi_hybrid_hierp *in = pdata, *hierp = prop_data;

		hierp->layers = in->layers;
		pkt->shdr.hdr.size += माप(u32) + माप(*hierp);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_INFO: अणु
		काष्ठा hfi_uncompressed_plane_actual_info *in = pdata;
		काष्ठा hfi_uncompressed_plane_actual_info *info = prop_data;

		info->buffer_type = in->buffer_type;
		info->num_planes = in->num_planes;
		info->plane_क्रमmat[0] = in->plane_क्रमmat[0];
		अगर (in->num_planes > 1)
			info->plane_क्रमmat[1] = in->plane_क्रमmat[1];
		pkt->shdr.hdr.size += माप(u32) + माप(*info);
		अवरोध;
	पूर्ण

	/* FOLLOWING PROPERTIES ARE NOT IMPLEMENTED IN CORE YET */
	हाल HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
	हाल HFI_PROPERTY_CONFIG_PRIORITY:
	हाल HFI_PROPERTY_CONFIG_BATCH_INFO:
	हाल HFI_PROPERTY_SYS_IDLE_INDICATOR:
	हाल HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_INTERLACE_FORMAT_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_CHROMA_SITE:
	हाल HFI_PROPERTY_PARAM_PROPERTIES_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_MULTI_VIEW_FORMAT:
	हाल HFI_PROPERTY_PARAM_MAX_SEQUENCE_HEADER_SIZE:
	हाल HFI_PROPERTY_PARAM_CODEC_SUPPORTED:
	हाल HFI_PROPERTY_PARAM_VDEC_MULTI_VIEW_SELECT:
	हाल HFI_PROPERTY_PARAM_VDEC_MB_QUANTIZATION:
	हाल HFI_PROPERTY_PARAM_VDEC_NUM_CONCEALED_MB:
	हाल HFI_PROPERTY_PARAM_VDEC_H264_ENTROPY_SWITCHING:
	हाल HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_INFO:
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
pkt_session_get_property_3xx(काष्ठा hfi_session_get_property_pkt *pkt,
			     व्योम *cookie, u32 ptype)
अणु
	पूर्णांक ret = 0;

	अगर (!pkt || !cookie)
		वापस -EINVAL;

	pkt->shdr.hdr.size = माप(काष्ठा hfi_session_get_property_pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_GET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;

	चयन (ptype) अणु
	हाल HFI_PROPERTY_CONFIG_VDEC_ENTROPY:
		pkt->data[0] = HFI_PROPERTY_CONFIG_VDEC_ENTROPY;
		अवरोध;
	शेष:
		ret = pkt_session_get_property_1x(pkt, cookie, ptype);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
pkt_session_set_property_3xx(काष्ठा hfi_session_set_property_pkt *pkt,
			     व्योम *cookie, u32 ptype, व्योम *pdata)
अणु
	व्योम *prop_data;
	पूर्णांक ret = 0;

	अगर (!pkt || !cookie || !pdata)
		वापस -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	/*
	 * Any session set property which is dअगरferent in 3XX packetization
	 * should be added as a new हाल below. All unchanged session set
	 * properties will be handled in the शेष हाल.
	 */
	चयन (ptype) अणु
	हाल HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM: अणु
		काष्ठा hfi_multi_stream *in = pdata;
		काष्ठा hfi_multi_stream_3x *multi = prop_data;

		multi->buffer_type = in->buffer_type;
		multi->enable = in->enable;
		pkt->shdr.hdr.size += माप(u32) + माप(*multi);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH: अणु
		काष्ठा hfi_पूर्णांकra_refresh *in = pdata;
		काष्ठा hfi_पूर्णांकra_refresh_3x *पूर्णांकra = prop_data;

		चयन (in->mode) अणु
		हाल HFI_INTRA_REFRESH_NONE:
		हाल HFI_INTRA_REFRESH_ADAPTIVE:
		हाल HFI_INTRA_REFRESH_CYCLIC:
		हाल HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE:
		हाल HFI_INTRA_REFRESH_RANDOM:
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		पूर्णांकra->mode = in->mode;
		पूर्णांकra->mbs = in->cir_mbs;
		pkt->shdr.hdr.size += माप(u32) + माप(*पूर्णांकra);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER:
		/* क्रम 3xx fw version session_जारी is used */
		अवरोध;
	शेष:
		ret = pkt_session_set_property_1x(pkt, cookie, ptype, pdata);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
pkt_session_set_property_4xx(काष्ठा hfi_session_set_property_pkt *pkt,
			     व्योम *cookie, u32 ptype, व्योम *pdata)
अणु
	व्योम *prop_data;

	अगर (!pkt || !cookie || !pdata)
		वापस -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	/*
	 * Any session set property which is dअगरferent in 3XX packetization
	 * should be added as a new हाल below. All unchanged session set
	 * properties will be handled in the शेष हाल.
	 */
	चयन (ptype) अणु
	हाल HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL: अणु
		काष्ठा hfi_buffer_count_actual *in = pdata;
		काष्ठा hfi_buffer_count_actual_4xx *count = prop_data;

		count->count_actual = in->count_actual;
		count->type = in->type;
		count->count_min_host = in->count_actual;
		pkt->shdr.hdr.size += माप(u32) + माप(*count);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_WORK_MODE: अणु
		काष्ठा hfi_video_work_mode *in = pdata, *wm = prop_data;

		wm->video_work_mode = in->video_work_mode;
		pkt->shdr.hdr.size += माप(u32) + माप(*wm);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE: अणु
		काष्ठा hfi_videocores_usage_type *in = pdata, *cu = prop_data;

		cu->video_core_enable_mask = in->video_core_enable_mask;
		pkt->shdr.hdr.size += माप(u32) + माप(*cu);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VENC_HDR10_PQ_SEI: अणु
		काष्ठा hfi_hdr10_pq_sei *in = pdata, *hdr10 = prop_data;

		स_नकल(hdr10, in, माप(*hdr10));
		pkt->shdr.hdr.size += माप(u32) + माप(*hdr10);
		अवरोध;
	पूर्ण

	हाल HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE:
	हाल HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER:
	हाल HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE:
	हाल HFI_PROPERTY_PARAM_VENC_SESSION_QP:
	हाल HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE:
		/* not implemented on Venus 4xx */
		वापस -ENOTSUPP;
	शेष:
		वापस pkt_session_set_property_3xx(pkt, cookie, ptype, pdata);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
pkt_session_set_property_6xx(काष्ठा hfi_session_set_property_pkt *pkt,
			     व्योम *cookie, u32 ptype, व्योम *pdata)
अणु
	व्योम *prop_data;

	अगर (!pkt || !cookie || !pdata)
		वापस -EINVAL;

	prop_data = &pkt->data[1];

	pkt->shdr.hdr.size = माप(*pkt);
	pkt->shdr.hdr.pkt_type = HFI_CMD_SESSION_SET_PROPERTY;
	pkt->shdr.session_id = hash32_ptr(cookie);
	pkt->num_properties = 1;
	pkt->data[0] = ptype;

	चयन (ptype) अणु
	हाल HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_CONSTRAINTS_INFO: अणु
		काष्ठा hfi_uncompressed_plane_actual_स्थिरraपूर्णांकs_info *in = pdata;
		काष्ठा hfi_uncompressed_plane_actual_स्थिरraपूर्णांकs_info *info = prop_data;

		info->buffer_type = in->buffer_type;
		info->num_planes = in->num_planes;
		info->plane_क्रमmat[0] = in->plane_क्रमmat[0];
		अगर (in->num_planes > 1)
			info->plane_क्रमmat[1] = in->plane_क्रमmat[1];

		pkt->shdr.hdr.size += माप(u32) + माप(*info);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_CONFIG_HEIC_FRAME_QUALITY: अणु
		काष्ठा hfi_heic_frame_quality *in = pdata, *cq = prop_data;

		cq->frame_quality = in->frame_quality;
		pkt->shdr.hdr.size += माप(u32) + माप(*cq);
		अवरोध;
	पूर्ण
	हाल HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR: अणु
		काष्ठा hfi_conceal_color_v4 *color = prop_data;
		u32 *in = pdata;

		color->conceal_color_8bit = *in & 0xff;
		color->conceal_color_8bit |= ((*in >> 10) & 0xff) << 8;
		color->conceal_color_8bit |= ((*in >> 20) & 0xff) << 16;
		color->conceal_color_10bit = *in;
		pkt->shdr.hdr.size += माप(u32) + माप(*color);
		अवरोध;
	पूर्ण
	शेष:
		वापस pkt_session_set_property_4xx(pkt, cookie, ptype, pdata);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pkt_session_get_property(काष्ठा hfi_session_get_property_pkt *pkt,
			     व्योम *cookie, u32 ptype)
अणु
	अगर (hfi_ver == HFI_VERSION_1XX)
		वापस pkt_session_get_property_1x(pkt, cookie, ptype);

	वापस pkt_session_get_property_3xx(pkt, cookie, ptype);
पूर्ण

पूर्णांक pkt_session_set_property(काष्ठा hfi_session_set_property_pkt *pkt,
			     व्योम *cookie, u32 ptype, व्योम *pdata)
अणु
	अगर (hfi_ver == HFI_VERSION_1XX)
		वापस pkt_session_set_property_1x(pkt, cookie, ptype, pdata);

	अगर (hfi_ver == HFI_VERSION_3XX)
		वापस pkt_session_set_property_3xx(pkt, cookie, ptype, pdata);

	अगर (hfi_ver == HFI_VERSION_4XX)
		वापस pkt_session_set_property_4xx(pkt, cookie, ptype, pdata);

	वापस pkt_session_set_property_6xx(pkt, cookie, ptype, pdata);
पूर्ण

व्योम pkt_set_version(क्रमागत hfi_version version)
अणु
	hfi_ver = version;
पूर्ण
