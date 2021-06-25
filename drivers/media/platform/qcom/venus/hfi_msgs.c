<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#समावेश <linux/hash.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "core.h"
#समावेश "hfi.h"
#समावेश "hfi_helper.h"
#समावेश "hfi_msgs.h"
#समावेश "hfi_parser.h"

#घोषणा SMEM_IMG_VER_TBL	469
#घोषणा VER_STR_SZ		128
#घोषणा SMEM_IMG_OFFSET_VENUS	(14 * 128)

अटल व्योम event_seq_changed(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
			      काष्ठा hfi_msg_event_notअगरy_pkt *pkt)
अणु
	क्रमागत hfi_version ver = core->res->hfi_version;
	काष्ठा hfi_event_data event = अणु0पूर्ण;
	पूर्णांक num_properties_changed;
	काष्ठा hfi_framesize *frame_sz;
	काष्ठा hfi_profile_level *profile_level;
	काष्ठा hfi_bit_depth *pixel_depth;
	काष्ठा hfi_pic_काष्ठा *pic_काष्ठा;
	काष्ठा hfi_colour_space *colour_info;
	काष्ठा hfi_buffer_requirements *bufreq;
	काष्ठा hfi_extradata_input_crop *crop;
	u8 *data_ptr;
	u32 ptype;

	inst->error = HFI_ERR_NONE;

	चयन (pkt->event_data1) अणु
	हाल HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_RESOURCES:
	हाल HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_RESOURCES:
		अवरोध;
	शेष:
		inst->error = HFI_ERR_SESSION_INVALID_PARAMETER;
		जाओ करोne;
	पूर्ण

	event.event_type = pkt->event_data1;

	num_properties_changed = pkt->event_data2;
	अगर (!num_properties_changed) अणु
		inst->error = HFI_ERR_SESSION_INSUFFICIENT_RESOURCES;
		जाओ करोne;
	पूर्ण

	data_ptr = (u8 *)&pkt->ext_event_data[0];
	करो अणु
		ptype = *((u32 *)data_ptr);
		चयन (ptype) अणु
		हाल HFI_PROPERTY_PARAM_FRAME_SIZE:
			data_ptr += माप(u32);
			frame_sz = (काष्ठा hfi_framesize *)data_ptr;
			event.width = frame_sz->width;
			event.height = frame_sz->height;
			data_ptr += माप(*frame_sz);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT:
			data_ptr += माप(u32);
			profile_level = (काष्ठा hfi_profile_level *)data_ptr;
			event.profile = profile_level->profile;
			event.level = profile_level->level;
			data_ptr += माप(*profile_level);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_VDEC_PIXEL_BITDEPTH:
			data_ptr += माप(u32);
			pixel_depth = (काष्ठा hfi_bit_depth *)data_ptr;
			event.bit_depth = pixel_depth->bit_depth;
			data_ptr += माप(*pixel_depth);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_VDEC_PIC_STRUCT:
			data_ptr += माप(u32);
			pic_काष्ठा = (काष्ठा hfi_pic_काष्ठा *)data_ptr;
			event.pic_काष्ठा = pic_काष्ठा->progressive_only;
			data_ptr += माप(*pic_काष्ठा);
			अवरोध;
		हाल HFI_PROPERTY_PARAM_VDEC_COLOUR_SPACE:
			data_ptr += माप(u32);
			colour_info = (काष्ठा hfi_colour_space *)data_ptr;
			event.colour_space = colour_info->colour_space;
			data_ptr += माप(*colour_info);
			अवरोध;
		हाल HFI_PROPERTY_CONFIG_VDEC_ENTROPY:
			data_ptr += माप(u32);
			event.entropy_mode = *(u32 *)data_ptr;
			data_ptr += माप(u32);
			अवरोध;
		हाल HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
			data_ptr += माप(u32);
			bufreq = (काष्ठा hfi_buffer_requirements *)data_ptr;
			event.buf_count = HFI_BUFREQ_COUNT_MIN(bufreq, ver);
			data_ptr += माप(*bufreq);
			अवरोध;
		हाल HFI_INDEX_EXTRADATA_INPUT_CROP:
			data_ptr += माप(u32);
			crop = (काष्ठा hfi_extradata_input_crop *)data_ptr;
			event.input_crop.left = crop->left;
			event.input_crop.top = crop->top;
			event.input_crop.width = crop->width;
			event.input_crop.height = crop->height;
			data_ptr += माप(*crop);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		num_properties_changed--;
	पूर्ण जबतक (num_properties_changed > 0);

करोne:
	inst->ops->event_notअगरy(inst, EVT_SYS_EVENT_CHANGE, &event);
पूर्ण

अटल व्योम event_release_buffer_ref(काष्ठा venus_core *core,
				     काष्ठा venus_inst *inst,
				     काष्ठा hfi_msg_event_notअगरy_pkt *pkt)
अणु
	काष्ठा hfi_event_data event = अणु0पूर्ण;
	काष्ठा hfi_msg_event_release_buffer_ref_pkt *data;

	data = (काष्ठा hfi_msg_event_release_buffer_ref_pkt *)
		pkt->ext_event_data;

	event.event_type = HFI_EVENT_RELEASE_BUFFER_REFERENCE;
	event.packet_buffer = data->packet_buffer;
	event.extradata_buffer = data->extradata_buffer;
	event.tag = data->output_tag;

	inst->error = HFI_ERR_NONE;
	inst->ops->event_notअगरy(inst, EVT_SYS_EVENT_CHANGE, &event);
पूर्ण

अटल व्योम event_sys_error(काष्ठा venus_core *core, u32 event,
			    काष्ठा hfi_msg_event_notअगरy_pkt *pkt)
अणु
	अगर (pkt)
		dev_dbg(core->dev, VDBGH
			"sys error (session id:%x, data1:%x, data2:%x)\n",
			pkt->shdr.session_id, pkt->event_data1,
			pkt->event_data2);

	core->core_ops->event_notअगरy(core, event);
पूर्ण

अटल व्योम
event_session_error(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
		    काष्ठा hfi_msg_event_notअगरy_pkt *pkt)
अणु
	काष्ठा device *dev = core->dev;

	dev_dbg(dev, VDBGH "session error: event id:%x, session id:%x\n",
		pkt->event_data1, pkt->shdr.session_id);

	अगर (!inst)
		वापस;

	चयन (pkt->event_data1) अणु
	/* non fatal session errors */
	हाल HFI_ERR_SESSION_INVALID_SCALE_FACTOR:
	हाल HFI_ERR_SESSION_UNSUPPORT_BUFFERTYPE:
	हाल HFI_ERR_SESSION_UNSUPPORTED_SETTING:
	हाल HFI_ERR_SESSION_UPSCALE_NOT_SUPPORTED:
		inst->error = HFI_ERR_NONE;
		अवरोध;
	शेष:
		dev_err(dev, "session error: event id:%x (%x), session id:%x\n",
			pkt->event_data1, pkt->event_data2,
			pkt->shdr.session_id);

		inst->error = pkt->event_data1;
		inst->ops->event_notअगरy(inst, EVT_SESSION_ERROR, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hfi_event_notअगरy(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
			     व्योम *packet)
अणु
	काष्ठा hfi_msg_event_notअगरy_pkt *pkt = packet;

	अगर (!packet)
		वापस;

	चयन (pkt->event_id) अणु
	हाल HFI_EVENT_SYS_ERROR:
		event_sys_error(core, EVT_SYS_ERROR, pkt);
		अवरोध;
	हाल HFI_EVENT_SESSION_ERROR:
		event_session_error(core, inst, pkt);
		अवरोध;
	हाल HFI_EVENT_SESSION_SEQUENCE_CHANGED:
		event_seq_changed(core, inst, pkt);
		अवरोध;
	हाल HFI_EVENT_RELEASE_BUFFER_REFERENCE:
		event_release_buffer_ref(core, inst, pkt);
		अवरोध;
	हाल HFI_EVENT_SESSION_PROPERTY_CHANGED:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hfi_sys_init_करोne(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
			      व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_init_करोne_pkt *pkt = packet;
	पूर्णांक rem_bytes;
	u32 error;

	error = pkt->error_type;
	अगर (error != HFI_ERR_NONE)
		जाओ करोne;

	अगर (!pkt->num_properties) अणु
		error = HFI_ERR_SYS_INVALID_PARAMETER;
		जाओ करोne;
	पूर्ण

	rem_bytes = pkt->hdr.size - माप(*pkt) + माप(u32);
	अगर (rem_bytes <= 0) अणु
		/* missing property data */
		error = HFI_ERR_SYS_INSUFFICIENT_RESOURCES;
		जाओ करोne;
	पूर्ण

	error = hfi_parser(core, inst, pkt->data, rem_bytes);

करोne:
	core->error = error;
	complete(&core->करोne);
पूर्ण

अटल व्योम
sys_get_prop_image_version(काष्ठा device *dev,
			   काष्ठा hfi_msg_sys_property_info_pkt *pkt)
अणु
	u8 *smem_tbl_ptr;
	u8 *img_ver;
	पूर्णांक req_bytes;
	माप_प्रकार smem_blk_sz;

	req_bytes = pkt->hdr.size - माप(*pkt);

	अगर (req_bytes < VER_STR_SZ || !pkt->data[1] || pkt->num_properties > 1)
		/* bad packet */
		वापस;

	img_ver = (u8 *)&pkt->data[1];

	dev_dbg(dev, VDBGL "F/W version: %s\n", img_ver);

	smem_tbl_ptr = qcom_smem_get(QCOM_SMEM_HOST_ANY,
		SMEM_IMG_VER_TBL, &smem_blk_sz);
	अगर (smem_tbl_ptr && smem_blk_sz >= SMEM_IMG_OFFSET_VENUS + VER_STR_SZ)
		स_नकल(smem_tbl_ptr + SMEM_IMG_OFFSET_VENUS,
		       img_ver, VER_STR_SZ);
पूर्ण

अटल व्योम hfi_sys_property_info(काष्ठा venus_core *core,
				  काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_property_info_pkt *pkt = packet;
	काष्ठा device *dev = core->dev;

	अगर (!pkt->num_properties) अणु
		dev_dbg(dev, VDBGL "no properties\n");
		वापस;
	पूर्ण

	चयन (pkt->data[0]) अणु
	हाल HFI_PROPERTY_SYS_IMAGE_VERSION:
		sys_get_prop_image_version(dev, pkt);
		अवरोध;
	शेष:
		dev_dbg(dev, VDBGL "unknown property data\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hfi_sys_rel_resource_करोne(काष्ठा venus_core *core,
				      काष्ठा venus_inst *inst,
				      व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_release_resource_करोne_pkt *pkt = packet;

	core->error = pkt->error_type;
	complete(&core->करोne);
पूर्ण

अटल व्योम hfi_sys_ping_करोne(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
			      व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_ping_ack_pkt *pkt = packet;

	core->error = HFI_ERR_NONE;

	अगर (pkt->client_data != 0xbeef)
		core->error = HFI_ERR_SYS_FATAL;

	complete(&core->करोne);
पूर्ण

अटल व्योम hfi_sys_idle_करोne(काष्ठा venus_core *core, काष्ठा venus_inst *inst,
			      व्योम *packet)
अणु
	dev_dbg(core->dev, VDBGL "sys idle\n");
पूर्ण

अटल व्योम hfi_sys_pc_prepare_करोne(काष्ठा venus_core *core,
				    काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_pc_prep_करोne_pkt *pkt = packet;

	dev_dbg(core->dev, VDBGL "pc prepare done (error %x)\n",
		pkt->error_type);
पूर्ण

अटल अचिन्हित पूर्णांक
session_get_prop_profile_level(काष्ठा hfi_msg_session_property_info_pkt *pkt,
			       काष्ठा hfi_profile_level *profile_level)
अणु
	काष्ठा hfi_profile_level *hfi;
	u32 req_bytes;

	req_bytes = pkt->shdr.hdr.size - माप(*pkt);

	अगर (!req_bytes || req_bytes % माप(काष्ठा hfi_profile_level))
		/* bad packet */
		वापस HFI_ERR_SESSION_INVALID_PARAMETER;

	hfi = (काष्ठा hfi_profile_level *)&pkt->data[1];
	profile_level->profile = hfi->profile;
	profile_level->level = hfi->level;

	वापस HFI_ERR_NONE;
पूर्ण

अटल अचिन्हित पूर्णांक
session_get_prop_buf_req(काष्ठा hfi_msg_session_property_info_pkt *pkt,
			 काष्ठा hfi_buffer_requirements *bufreq)
अणु
	काष्ठा hfi_buffer_requirements *buf_req;
	u32 req_bytes;
	अचिन्हित पूर्णांक idx = 0;

	req_bytes = pkt->shdr.hdr.size - माप(*pkt);

	अगर (!req_bytes || req_bytes % माप(*buf_req) || !pkt->data[1])
		/* bad packet */
		वापस HFI_ERR_SESSION_INVALID_PARAMETER;

	buf_req = (काष्ठा hfi_buffer_requirements *)&pkt->data[1];
	अगर (!buf_req)
		वापस HFI_ERR_SESSION_INVALID_PARAMETER;

	जबतक (req_bytes) अणु
		स_नकल(&bufreq[idx], buf_req, माप(*bufreq));
		idx++;

		अगर (idx > HFI_BUFFER_TYPE_MAX)
			वापस HFI_ERR_SESSION_INVALID_PARAMETER;

		req_bytes -= माप(काष्ठा hfi_buffer_requirements);
		buf_req++;
	पूर्ण

	वापस HFI_ERR_NONE;
पूर्ण

अटल व्योम hfi_session_prop_info(काष्ठा venus_core *core,
				  काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_property_info_pkt *pkt = packet;
	काष्ठा device *dev = core->dev;
	जोड़ hfi_get_property *hprop = &inst->hprop;
	अचिन्हित पूर्णांक error = HFI_ERR_NONE;

	अगर (!pkt->num_properties) अणु
		error = HFI_ERR_SESSION_INVALID_PARAMETER;
		dev_err(dev, "%s: no properties\n", __func__);
		जाओ करोne;
	पूर्ण

	चयन (pkt->data[0]) अणु
	हाल HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS:
		स_रखो(hprop->bufreq, 0, माप(hprop->bufreq));
		error = session_get_prop_buf_req(pkt, hprop->bufreq);
		अवरोध;
	हाल HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT:
		स_रखो(&hprop->profile_level, 0, माप(hprop->profile_level));
		error = session_get_prop_profile_level(pkt,
						       &hprop->profile_level);
		अवरोध;
	हाल HFI_PROPERTY_CONFIG_VDEC_ENTROPY:
		अवरोध;
	शेष:
		dev_dbg(dev, VDBGM "unknown property id:%x\n", pkt->data[0]);
		वापस;
	पूर्ण

करोne:
	inst->error = error;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_init_करोne(काष्ठा venus_core *core,
				  काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_init_करोne_pkt *pkt = packet;
	पूर्णांक rem_bytes;
	u32 error;

	error = pkt->error_type;
	अगर (error != HFI_ERR_NONE)
		जाओ करोne;

	अगर (!IS_V1(core))
		जाओ करोne;

	rem_bytes = pkt->shdr.hdr.size - माप(*pkt) + माप(u32);
	अगर (rem_bytes <= 0) अणु
		error = HFI_ERR_SESSION_INSUFFICIENT_RESOURCES;
		जाओ करोne;
	पूर्ण

	error = hfi_parser(core, inst, pkt->data, rem_bytes);
करोne:
	inst->error = error;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_load_res_करोne(काष्ठा venus_core *core,
				      काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_load_resources_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_flush_करोne(काष्ठा venus_core *core,
				   काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_flush_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
	अगर (inst->ops->flush_करोne)
		inst->ops->flush_करोne(inst);
पूर्ण

अटल व्योम hfi_session_etb_करोne(काष्ठा venus_core *core,
				 काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_empty_buffer_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	inst->ops->buf_करोne(inst, HFI_BUFFER_INPUT, pkt->input_tag,
			    pkt->filled_len, pkt->offset, 0, 0, 0);
पूर्ण

अटल व्योम hfi_session_ftb_करोne(काष्ठा venus_core *core,
				 काष्ठा venus_inst *inst, व्योम *packet)
अणु
	u32 session_type = inst->session_type;
	u64 बारtamp_us = 0;
	u32 बारtamp_hi = 0, बारtamp_lo = 0;
	अचिन्हित पूर्णांक error;
	u32 flags = 0, hfi_flags = 0, offset = 0, filled_len = 0;
	u32 pic_type = 0, buffer_type = 0, output_tag = -1;

	अगर (session_type == VIDC_SESSION_TYPE_ENC) अणु
		काष्ठा hfi_msg_session_fbd_compressed_pkt *pkt = packet;

		बारtamp_hi = pkt->समय_stamp_hi;
		बारtamp_lo = pkt->समय_stamp_lo;
		hfi_flags = pkt->flags;
		offset = pkt->offset;
		filled_len = pkt->filled_len;
		pic_type = pkt->picture_type;
		output_tag = pkt->output_tag;
		buffer_type = HFI_BUFFER_OUTPUT;

		error = pkt->error_type;
	पूर्ण अन्यथा अगर (session_type == VIDC_SESSION_TYPE_DEC) अणु
		काष्ठा hfi_msg_session_fbd_uncompressed_plane0_pkt *pkt =
			packet;

		बारtamp_hi = pkt->समय_stamp_hi;
		बारtamp_lo = pkt->समय_stamp_lo;
		hfi_flags = pkt->flags;
		offset = pkt->offset;
		filled_len = pkt->filled_len;
		pic_type = pkt->picture_type;
		output_tag = pkt->output_tag;

		अगर (pkt->stream_id == 0)
			buffer_type = HFI_BUFFER_OUTPUT;
		अन्यथा अगर (pkt->stream_id == 1)
			buffer_type = HFI_BUFFER_OUTPUT2;

		error = pkt->error_type;
	पूर्ण अन्यथा अणु
		error = HFI_ERR_SESSION_INVALID_PARAMETER;
	पूर्ण

	अगर (buffer_type != HFI_BUFFER_OUTPUT &&
	    buffer_type != HFI_BUFFER_OUTPUT2)
		जाओ करोne;

	अगर (hfi_flags & HFI_BUFFERFLAG_EOS)
		flags |= V4L2_BUF_FLAG_LAST;

	चयन (pic_type) अणु
	हाल HFI_PICTURE_IDR:
	हाल HFI_PICTURE_I:
		flags |= V4L2_BUF_FLAG_KEYFRAME;
		अवरोध;
	हाल HFI_PICTURE_P:
		flags |= V4L2_BUF_FLAG_PFRAME;
		अवरोध;
	हाल HFI_PICTURE_B:
		flags |= V4L2_BUF_FLAG_BFRAME;
		अवरोध;
	हाल HFI_FRAME_NOTCODED:
	हाल HFI_UNUSED_PICT:
	हाल HFI_FRAME_YUV:
	शेष:
		अवरोध;
	पूर्ण

	अगर (!(hfi_flags & HFI_BUFFERFLAG_TIMESTAMPINVALID) && filled_len) अणु
		बारtamp_us = बारtamp_hi;
		बारtamp_us = (बारtamp_us << 32) | बारtamp_lo;
	पूर्ण

करोne:
	inst->error = error;
	inst->ops->buf_करोne(inst, buffer_type, output_tag, filled_len,
			    offset, flags, hfi_flags, बारtamp_us);
पूर्ण

अटल व्योम hfi_session_start_करोne(काष्ठा venus_core *core,
				   काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_start_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_stop_करोne(काष्ठा venus_core *core,
				  काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_stop_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_rel_res_करोne(काष्ठा venus_core *core,
				     काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_release_resources_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_rel_buf_करोne(काष्ठा venus_core *core,
				     काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_release_buffers_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_end_करोne(काष्ठा venus_core *core,
				 काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_end_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_पात_करोne(काष्ठा venus_core *core,
				   काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_sys_session_पात_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

अटल व्योम hfi_session_get_seq_hdr_करोne(काष्ठा venus_core *core,
					 काष्ठा venus_inst *inst, व्योम *packet)
अणु
	काष्ठा hfi_msg_session_get_sequence_hdr_करोne_pkt *pkt = packet;

	inst->error = pkt->error_type;
	complete(&inst->करोne);
पूर्ण

काष्ठा hfi_करोne_handler अणु
	u32 pkt;
	u32 pkt_sz;
	u32 pkt_sz2;
	व्योम (*करोne)(काष्ठा venus_core *, काष्ठा venus_inst *, व्योम *);
	bool is_sys_pkt;
पूर्ण;

अटल स्थिर काष्ठा hfi_करोne_handler handlers[] = अणु
	अणु.pkt = HFI_MSG_EVENT_NOTIFY,
	 .pkt_sz = माप(काष्ठा hfi_msg_event_notअगरy_pkt),
	 .करोne = hfi_event_notअगरy,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_INIT,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_init_करोne_pkt),
	 .करोne = hfi_sys_init_करोne,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_PROPERTY_INFO,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_property_info_pkt),
	 .करोne = hfi_sys_property_info,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_RELEASE_RESOURCE,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_release_resource_करोne_pkt),
	 .करोne = hfi_sys_rel_resource_करोne,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_PING_ACK,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_ping_ack_pkt),
	 .करोne = hfi_sys_ping_करोne,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_IDLE,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_idle_pkt),
	 .करोne = hfi_sys_idle_करोne,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_PC_PREP,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_pc_prep_करोne_pkt),
	 .करोne = hfi_sys_pc_prepare_करोne,
	 .is_sys_pkt = true,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_SESSION_INIT,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_init_करोne_pkt),
	 .करोne = hfi_session_init_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_SESSION_END,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_end_करोne_pkt),
	 .करोne = hfi_session_end_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_LOAD_RESOURCES,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_load_resources_करोne_pkt),
	 .करोne = hfi_session_load_res_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_START,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_start_करोne_pkt),
	 .करोne = hfi_session_start_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_STOP,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_stop_करोne_pkt),
	 .करोne = hfi_session_stop_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SYS_SESSION_ABORT,
	 .pkt_sz = माप(काष्ठा hfi_msg_sys_session_पात_करोne_pkt),
	 .करोne = hfi_session_पात_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_EMPTY_BUFFER,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_empty_buffer_करोne_pkt),
	 .करोne = hfi_session_etb_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_FILL_BUFFER,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_fbd_uncompressed_plane0_pkt),
	 .pkt_sz2 = माप(काष्ठा hfi_msg_session_fbd_compressed_pkt),
	 .करोne = hfi_session_ftb_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_FLUSH,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_flush_करोne_pkt),
	 .करोne = hfi_session_flush_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_PROPERTY_INFO,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_property_info_pkt),
	 .करोne = hfi_session_prop_info,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_RELEASE_RESOURCES,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_release_resources_करोne_pkt),
	 .करोne = hfi_session_rel_res_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_GET_SEQUENCE_HEADER,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_get_sequence_hdr_करोne_pkt),
	 .करोne = hfi_session_get_seq_hdr_करोne,
	पूर्ण,
	अणु.pkt = HFI_MSG_SESSION_RELEASE_BUFFERS,
	 .pkt_sz = माप(काष्ठा hfi_msg_session_release_buffers_करोne_pkt),
	 .करोne = hfi_session_rel_buf_करोne,
	पूर्ण,
पूर्ण;

व्योम hfi_process_watchकरोg_समयout(काष्ठा venus_core *core)
अणु
	event_sys_error(core, EVT_SYS_WATCHDOG_TIMEOUT, शून्य);
पूर्ण

अटल काष्ठा venus_inst *to_instance(काष्ठा venus_core *core, u32 session_id)
अणु
	काष्ठा venus_inst *inst;

	mutex_lock(&core->lock);
	list_क्रम_each_entry(inst, &core->instances, list)
		अगर (hash32_ptr(inst) == session_id) अणु
			mutex_unlock(&core->lock);
			वापस inst;
		पूर्ण
	mutex_unlock(&core->lock);

	वापस शून्य;
पूर्ण

u32 hfi_process_msg_packet(काष्ठा venus_core *core, काष्ठा hfi_pkt_hdr *hdr)
अणु
	स्थिर काष्ठा hfi_करोne_handler *handler;
	काष्ठा device *dev = core->dev;
	काष्ठा venus_inst *inst;
	bool found = false;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(handlers); i++) अणु
		handler = &handlers[i];
		अगर (handler->pkt != hdr->pkt_type)
			जारी;
		found = true;
		अवरोध;
	पूर्ण

	अगर (!found)
		वापस hdr->pkt_type;

	अगर (hdr->size && hdr->size < handler->pkt_sz &&
	    hdr->size < handler->pkt_sz2) अणु
		dev_err(dev, "bad packet size (%d should be %d, pkt type:%x)\n",
			hdr->size, handler->pkt_sz, hdr->pkt_type);

		वापस hdr->pkt_type;
	पूर्ण

	अगर (handler->is_sys_pkt) अणु
		inst = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा hfi_session_pkt *pkt;

		pkt = (काष्ठा hfi_session_pkt *)hdr;
		inst = to_instance(core, pkt->shdr.session_id);

		अगर (!inst)
			dev_warn(dev, "no valid instance(pkt session_id:%x, pkt:%x)\n",
				 pkt->shdr.session_id,
				 handler ? handler->pkt : 0);

		/*
		 * Event of type HFI_EVENT_SYS_ERROR will not have any session
		 * associated with it
		 */
		अगर (!inst && hdr->pkt_type != HFI_MSG_EVENT_NOTIFY) अणु
			dev_err(dev, "got invalid session id:%x\n",
				pkt->shdr.session_id);
			जाओ invalid_session;
		पूर्ण
	पूर्ण

	handler->करोne(core, inst, hdr);

invalid_session:
	वापस hdr->pkt_type;
पूर्ण
