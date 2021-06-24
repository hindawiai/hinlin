<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * cec - HDMI Consumer Electronics Control message functions
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _CEC_UAPI_FUNCS_H
#घोषणा _CEC_UAPI_FUNCS_H

#समावेश <linux/cec.h>

/* One Touch Play Feature */
अटल अंतरभूत व्योम cec_msg_active_source(काष्ठा cec_msg *msg, __u16 phys_addr)
अणु
	msg->len = 4;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_ACTIVE_SOURCE;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_active_source(स्थिर काष्ठा cec_msg *msg,
					 __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_image_view_on(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_IMAGE_VIEW_ON;
पूर्ण

अटल अंतरभूत व्योम cec_msg_text_view_on(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_TEXT_VIEW_ON;
पूर्ण


/* Routing Control Feature */
अटल अंतरभूत व्योम cec_msg_inactive_source(काष्ठा cec_msg *msg,
					   __u16 phys_addr)
अणु
	msg->len = 4;
	msg->msg[1] = CEC_MSG_INACTIVE_SOURCE;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_inactive_source(स्थिर काष्ठा cec_msg *msg,
					   __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_request_active_source(काष्ठा cec_msg *msg,
						 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_REQUEST_ACTIVE_SOURCE;
	msg->reply = reply ? CEC_MSG_ACTIVE_SOURCE : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_routing_inक्रमmation(काष्ठा cec_msg *msg,
					       __u16 phys_addr)
अणु
	msg->len = 4;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_ROUTING_INFORMATION;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_routing_inक्रमmation(स्थिर काष्ठा cec_msg *msg,
					       __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_routing_change(काष्ठा cec_msg *msg,
					  पूर्णांक reply,
					  __u16 orig_phys_addr,
					  __u16 new_phys_addr)
अणु
	msg->len = 6;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_ROUTING_CHANGE;
	msg->msg[2] = orig_phys_addr >> 8;
	msg->msg[3] = orig_phys_addr & 0xff;
	msg->msg[4] = new_phys_addr >> 8;
	msg->msg[5] = new_phys_addr & 0xff;
	msg->reply = reply ? CEC_MSG_ROUTING_INFORMATION : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_routing_change(स्थिर काष्ठा cec_msg *msg,
					  __u16 *orig_phys_addr,
					  __u16 *new_phys_addr)
अणु
	*orig_phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*new_phys_addr = (msg->msg[4] << 8) | msg->msg[5];
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_stream_path(काष्ठा cec_msg *msg, __u16 phys_addr)
अणु
	msg->len = 4;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_SET_STREAM_PATH;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_stream_path(स्थिर काष्ठा cec_msg *msg,
					   __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण


/* Standby Feature */
अटल अंतरभूत व्योम cec_msg_standby(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_STANDBY;
पूर्ण


/* One Touch Record Feature */
अटल अंतरभूत व्योम cec_msg_record_off(काष्ठा cec_msg *msg, पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_RECORD_OFF;
	msg->reply = reply ? CEC_MSG_RECORD_STATUS : 0;
पूर्ण

काष्ठा cec_op_arib_data अणु
	__u16 transport_id;
	__u16 service_id;
	__u16 orig_network_id;
पूर्ण;

काष्ठा cec_op_atsc_data अणु
	__u16 transport_id;
	__u16 program_number;
पूर्ण;

काष्ठा cec_op_dvb_data अणु
	__u16 transport_id;
	__u16 service_id;
	__u16 orig_network_id;
पूर्ण;

काष्ठा cec_op_channel_data अणु
	__u8 channel_number_fmt;
	__u16 major;
	__u16 minor;
पूर्ण;

काष्ठा cec_op_digital_service_id अणु
	__u8 service_id_method;
	__u8 dig_bcast_प्रणाली;
	जोड़ अणु
		काष्ठा cec_op_arib_data arib;
		काष्ठा cec_op_atsc_data atsc;
		काष्ठा cec_op_dvb_data dvb;
		काष्ठा cec_op_channel_data channel;
	पूर्ण;
पूर्ण;

काष्ठा cec_op_record_src अणु
	__u8 type;
	जोड़ अणु
		काष्ठा cec_op_digital_service_id digital;
		काष्ठा अणु
			__u8 ana_bcast_type;
			__u16 ana_freq;
			__u8 bcast_प्रणाली;
		पूर्ण analog;
		काष्ठा अणु
			__u8 plug;
		पूर्ण ext_plug;
		काष्ठा अणु
			__u16 phys_addr;
		पूर्ण ext_phys_addr;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम cec_set_digital_service_id(__u8 *msg,
	      स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	*msg++ = (digital->service_id_method << 7) | digital->dig_bcast_प्रणाली;
	अगर (digital->service_id_method == CEC_OP_SERVICE_ID_METHOD_BY_CHANNEL) अणु
		*msg++ = (digital->channel.channel_number_fmt << 2) |
			 (digital->channel.major >> 8);
		*msg++ = digital->channel.major & 0xff;
		*msg++ = digital->channel.minor >> 8;
		*msg++ = digital->channel.minor & 0xff;
		*msg++ = 0;
		*msg++ = 0;
		वापस;
	पूर्ण
	चयन (digital->dig_bcast_प्रणाली) अणु
	हाल CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_GEN:
	हाल CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_CABLE:
	हाल CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_SAT:
	हाल CEC_OP_DIG_SERVICE_BCAST_SYSTEM_ATSC_T:
		*msg++ = digital->atsc.transport_id >> 8;
		*msg++ = digital->atsc.transport_id & 0xff;
		*msg++ = digital->atsc.program_number >> 8;
		*msg++ = digital->atsc.program_number & 0xff;
		*msg++ = 0;
		*msg++ = 0;
		अवरोध;
	शेष:
		*msg++ = digital->dvb.transport_id >> 8;
		*msg++ = digital->dvb.transport_id & 0xff;
		*msg++ = digital->dvb.service_id >> 8;
		*msg++ = digital->dvb.service_id & 0xff;
		*msg++ = digital->dvb.orig_network_id >> 8;
		*msg++ = digital->dvb.orig_network_id & 0xff;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_get_digital_service_id(स्थिर __u8 *msg,
	      काष्ठा cec_op_digital_service_id *digital)
अणु
	digital->service_id_method = msg[0] >> 7;
	digital->dig_bcast_प्रणाली = msg[0] & 0x7f;
	अगर (digital->service_id_method == CEC_OP_SERVICE_ID_METHOD_BY_CHANNEL) अणु
		digital->channel.channel_number_fmt = msg[1] >> 2;
		digital->channel.major = ((msg[1] & 3) << 6) | msg[2];
		digital->channel.minor = (msg[3] << 8) | msg[4];
		वापस;
	पूर्ण
	digital->dvb.transport_id = (msg[1] << 8) | msg[2];
	digital->dvb.service_id = (msg[3] << 8) | msg[4];
	digital->dvb.orig_network_id = (msg[5] << 8) | msg[6];
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on_own(काष्ठा cec_msg *msg)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_RECORD_ON;
	msg->msg[2] = CEC_OP_RECORD_SRC_OWN;
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on_digital(काष्ठा cec_msg *msg,
			     स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	msg->len = 10;
	msg->msg[1] = CEC_MSG_RECORD_ON;
	msg->msg[2] = CEC_OP_RECORD_SRC_DIGITAL;
	cec_set_digital_service_id(msg->msg + 3, digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on_analog(काष्ठा cec_msg *msg,
					    __u8 ana_bcast_type,
					    __u16 ana_freq,
					    __u8 bcast_प्रणाली)
अणु
	msg->len = 7;
	msg->msg[1] = CEC_MSG_RECORD_ON;
	msg->msg[2] = CEC_OP_RECORD_SRC_ANALOG;
	msg->msg[3] = ana_bcast_type;
	msg->msg[4] = ana_freq >> 8;
	msg->msg[5] = ana_freq & 0xff;
	msg->msg[6] = bcast_प्रणाली;
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on_plug(काष्ठा cec_msg *msg,
					  __u8 plug)
अणु
	msg->len = 4;
	msg->msg[1] = CEC_MSG_RECORD_ON;
	msg->msg[2] = CEC_OP_RECORD_SRC_EXT_PLUG;
	msg->msg[3] = plug;
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on_phys_addr(काष्ठा cec_msg *msg,
					       __u16 phys_addr)
अणु
	msg->len = 5;
	msg->msg[1] = CEC_MSG_RECORD_ON;
	msg->msg[2] = CEC_OP_RECORD_SRC_EXT_PHYS_ADDR;
	msg->msg[3] = phys_addr >> 8;
	msg->msg[4] = phys_addr & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_on(काष्ठा cec_msg *msg,
				     पूर्णांक reply,
				     स्थिर काष्ठा cec_op_record_src *rec_src)
अणु
	चयन (rec_src->type) अणु
	हाल CEC_OP_RECORD_SRC_OWN:
		cec_msg_record_on_own(msg);
		अवरोध;
	हाल CEC_OP_RECORD_SRC_DIGITAL:
		cec_msg_record_on_digital(msg, &rec_src->digital);
		अवरोध;
	हाल CEC_OP_RECORD_SRC_ANALOG:
		cec_msg_record_on_analog(msg,
					 rec_src->analog.ana_bcast_type,
					 rec_src->analog.ana_freq,
					 rec_src->analog.bcast_प्रणाली);
		अवरोध;
	हाल CEC_OP_RECORD_SRC_EXT_PLUG:
		cec_msg_record_on_plug(msg, rec_src->ext_plug.plug);
		अवरोध;
	हाल CEC_OP_RECORD_SRC_EXT_PHYS_ADDR:
		cec_msg_record_on_phys_addr(msg,
					    rec_src->ext_phys_addr.phys_addr);
		अवरोध;
	पूर्ण
	msg->reply = reply ? CEC_MSG_RECORD_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_record_on(स्थिर काष्ठा cec_msg *msg,
				     काष्ठा cec_op_record_src *rec_src)
अणु
	rec_src->type = msg->msg[2];
	चयन (rec_src->type) अणु
	हाल CEC_OP_RECORD_SRC_OWN:
		अवरोध;
	हाल CEC_OP_RECORD_SRC_DIGITAL:
		cec_get_digital_service_id(msg->msg + 3, &rec_src->digital);
		अवरोध;
	हाल CEC_OP_RECORD_SRC_ANALOG:
		rec_src->analog.ana_bcast_type = msg->msg[3];
		rec_src->analog.ana_freq =
			(msg->msg[4] << 8) | msg->msg[5];
		rec_src->analog.bcast_प्रणाली = msg->msg[6];
		अवरोध;
	हाल CEC_OP_RECORD_SRC_EXT_PLUG:
		rec_src->ext_plug.plug = msg->msg[3];
		अवरोध;
	हाल CEC_OP_RECORD_SRC_EXT_PHYS_ADDR:
		rec_src->ext_phys_addr.phys_addr =
			(msg->msg[3] << 8) | msg->msg[4];
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_status(काष्ठा cec_msg *msg, __u8 rec_status)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_RECORD_STATUS;
	msg->msg[2] = rec_status;
पूर्ण

अटल अंतरभूत व्योम cec_ops_record_status(स्थिर काष्ठा cec_msg *msg,
					 __u8 *rec_status)
अणु
	*rec_status = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_record_tv_screen(काष्ठा cec_msg *msg,
					    पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_RECORD_TV_SCREEN;
	msg->reply = reply ? CEC_MSG_RECORD_ON : 0;
पूर्ण


/* Timer Programming Feature */
अटल अंतरभूत व्योम cec_msg_समयr_status(काष्ठा cec_msg *msg,
					__u8 समयr_overlap_warning,
					__u8 media_info,
					__u8 prog_info,
					__u8 prog_error,
					__u8 duration_hr,
					__u8 duration_min)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_TIMER_STATUS;
	msg->msg[2] = (समयr_overlap_warning << 7) |
		(media_info << 5) |
		(prog_info ? 0x10 : 0) |
		(prog_info ? prog_info : prog_error);
	अगर (prog_info == CEC_OP_PROG_INFO_NOT_ENOUGH_SPACE ||
	    prog_info == CEC_OP_PROG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE ||
	    prog_error == CEC_OP_PROG_ERROR_DUPLICATE) अणु
		msg->len += 2;
		msg->msg[3] = ((duration_hr / 10) << 4) | (duration_hr % 10);
		msg->msg[4] = ((duration_min / 10) << 4) | (duration_min % 10);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_ops_समयr_status(स्थिर काष्ठा cec_msg *msg,
					__u8 *समयr_overlap_warning,
					__u8 *media_info,
					__u8 *prog_info,
					__u8 *prog_error,
					__u8 *duration_hr,
					__u8 *duration_min)
अणु
	*समयr_overlap_warning = msg->msg[2] >> 7;
	*media_info = (msg->msg[2] >> 5) & 3;
	अगर (msg->msg[2] & 0x10) अणु
		*prog_info = msg->msg[2] & 0xf;
		*prog_error = 0;
	पूर्ण अन्यथा अणु
		*prog_info = 0;
		*prog_error = msg->msg[2] & 0xf;
	पूर्ण
	अगर (*prog_info == CEC_OP_PROG_INFO_NOT_ENOUGH_SPACE ||
	    *prog_info == CEC_OP_PROG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE ||
	    *prog_error == CEC_OP_PROG_ERROR_DUPLICATE) अणु
		*duration_hr = (msg->msg[3] >> 4) * 10 + (msg->msg[3] & 0xf);
		*duration_min = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	पूर्ण अन्यथा अणु
		*duration_hr = *duration_min = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_msg_समयr_cleared_status(काष्ठा cec_msg *msg,
						__u8 समयr_cleared_status)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_TIMER_CLEARED_STATUS;
	msg->msg[2] = समयr_cleared_status;
पूर्ण

अटल अंतरभूत व्योम cec_ops_समयr_cleared_status(स्थिर काष्ठा cec_msg *msg,
						__u8 *समयr_cleared_status)
अणु
	*समयr_cleared_status = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_clear_analogue_समयr(काष्ठा cec_msg *msg,
						पूर्णांक reply,
						__u8 day,
						__u8 month,
						__u8 start_hr,
						__u8 start_min,
						__u8 duration_hr,
						__u8 duration_min,
						__u8 recording_seq,
						__u8 ana_bcast_type,
						__u16 ana_freq,
						__u8 bcast_प्रणाली)
अणु
	msg->len = 13;
	msg->msg[1] = CEC_MSG_CLEAR_ANALOGUE_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	msg->msg[9] = ana_bcast_type;
	msg->msg[10] = ana_freq >> 8;
	msg->msg[11] = ana_freq & 0xff;
	msg->msg[12] = bcast_प्रणाली;
	msg->reply = reply ? CEC_MSG_TIMER_CLEARED_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_clear_analogue_समयr(स्थिर काष्ठा cec_msg *msg,
						__u8 *day,
						__u8 *month,
						__u8 *start_hr,
						__u8 *start_min,
						__u8 *duration_hr,
						__u8 *duration_min,
						__u8 *recording_seq,
						__u8 *ana_bcast_type,
						__u16 *ana_freq,
						__u8 *bcast_प्रणाली)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	*ana_bcast_type = msg->msg[9];
	*ana_freq = (msg->msg[10] << 8) | msg->msg[11];
	*bcast_प्रणाली = msg->msg[12];
पूर्ण

अटल अंतरभूत व्योम cec_msg_clear_digital_समयr(काष्ठा cec_msg *msg,
				पूर्णांक reply,
				__u8 day,
				__u8 month,
				__u8 start_hr,
				__u8 start_min,
				__u8 duration_hr,
				__u8 duration_min,
				__u8 recording_seq,
				स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	msg->len = 16;
	msg->reply = reply ? CEC_MSG_TIMER_CLEARED_STATUS : 0;
	msg->msg[1] = CEC_MSG_CLEAR_DIGITAL_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	cec_set_digital_service_id(msg->msg + 9, digital);
पूर्ण

अटल अंतरभूत व्योम cec_ops_clear_digital_समयr(स्थिर काष्ठा cec_msg *msg,
				__u8 *day,
				__u8 *month,
				__u8 *start_hr,
				__u8 *start_min,
				__u8 *duration_hr,
				__u8 *duration_min,
				__u8 *recording_seq,
				काष्ठा cec_op_digital_service_id *digital)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	cec_get_digital_service_id(msg->msg + 9, digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_clear_ext_समयr(काष्ठा cec_msg *msg,
					   पूर्णांक reply,
					   __u8 day,
					   __u8 month,
					   __u8 start_hr,
					   __u8 start_min,
					   __u8 duration_hr,
					   __u8 duration_min,
					   __u8 recording_seq,
					   __u8 ext_src_spec,
					   __u8 plug,
					   __u16 phys_addr)
अणु
	msg->len = 13;
	msg->msg[1] = CEC_MSG_CLEAR_EXT_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	msg->msg[9] = ext_src_spec;
	msg->msg[10] = plug;
	msg->msg[11] = phys_addr >> 8;
	msg->msg[12] = phys_addr & 0xff;
	msg->reply = reply ? CEC_MSG_TIMER_CLEARED_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_clear_ext_समयr(स्थिर काष्ठा cec_msg *msg,
					   __u8 *day,
					   __u8 *month,
					   __u8 *start_hr,
					   __u8 *start_min,
					   __u8 *duration_hr,
					   __u8 *duration_min,
					   __u8 *recording_seq,
					   __u8 *ext_src_spec,
					   __u8 *plug,
					   __u16 *phys_addr)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	*ext_src_spec = msg->msg[9];
	*plug = msg->msg[10];
	*phys_addr = (msg->msg[11] << 8) | msg->msg[12];
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_analogue_समयr(काष्ठा cec_msg *msg,
					      पूर्णांक reply,
					      __u8 day,
					      __u8 month,
					      __u8 start_hr,
					      __u8 start_min,
					      __u8 duration_hr,
					      __u8 duration_min,
					      __u8 recording_seq,
					      __u8 ana_bcast_type,
					      __u16 ana_freq,
					      __u8 bcast_प्रणाली)
अणु
	msg->len = 13;
	msg->msg[1] = CEC_MSG_SET_ANALOGUE_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	msg->msg[9] = ana_bcast_type;
	msg->msg[10] = ana_freq >> 8;
	msg->msg[11] = ana_freq & 0xff;
	msg->msg[12] = bcast_प्रणाली;
	msg->reply = reply ? CEC_MSG_TIMER_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_analogue_समयr(स्थिर काष्ठा cec_msg *msg,
					      __u8 *day,
					      __u8 *month,
					      __u8 *start_hr,
					      __u8 *start_min,
					      __u8 *duration_hr,
					      __u8 *duration_min,
					      __u8 *recording_seq,
					      __u8 *ana_bcast_type,
					      __u16 *ana_freq,
					      __u8 *bcast_प्रणाली)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	*ana_bcast_type = msg->msg[9];
	*ana_freq = (msg->msg[10] << 8) | msg->msg[11];
	*bcast_प्रणाली = msg->msg[12];
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_digital_समयr(काष्ठा cec_msg *msg,
			पूर्णांक reply,
			__u8 day,
			__u8 month,
			__u8 start_hr,
			__u8 start_min,
			__u8 duration_hr,
			__u8 duration_min,
			__u8 recording_seq,
			स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	msg->len = 16;
	msg->reply = reply ? CEC_MSG_TIMER_STATUS : 0;
	msg->msg[1] = CEC_MSG_SET_DIGITAL_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	cec_set_digital_service_id(msg->msg + 9, digital);
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_digital_समयr(स्थिर काष्ठा cec_msg *msg,
			__u8 *day,
			__u8 *month,
			__u8 *start_hr,
			__u8 *start_min,
			__u8 *duration_hr,
			__u8 *duration_min,
			__u8 *recording_seq,
			काष्ठा cec_op_digital_service_id *digital)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	cec_get_digital_service_id(msg->msg + 9, digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_ext_समयr(काष्ठा cec_msg *msg,
					 पूर्णांक reply,
					 __u8 day,
					 __u8 month,
					 __u8 start_hr,
					 __u8 start_min,
					 __u8 duration_hr,
					 __u8 duration_min,
					 __u8 recording_seq,
					 __u8 ext_src_spec,
					 __u8 plug,
					 __u16 phys_addr)
अणु
	msg->len = 13;
	msg->msg[1] = CEC_MSG_SET_EXT_TIMER;
	msg->msg[2] = day;
	msg->msg[3] = month;
	/* Hours and minutes are in BCD क्रमmat */
	msg->msg[4] = ((start_hr / 10) << 4) | (start_hr % 10);
	msg->msg[5] = ((start_min / 10) << 4) | (start_min % 10);
	msg->msg[6] = ((duration_hr / 10) << 4) | (duration_hr % 10);
	msg->msg[7] = ((duration_min / 10) << 4) | (duration_min % 10);
	msg->msg[8] = recording_seq;
	msg->msg[9] = ext_src_spec;
	msg->msg[10] = plug;
	msg->msg[11] = phys_addr >> 8;
	msg->msg[12] = phys_addr & 0xff;
	msg->reply = reply ? CEC_MSG_TIMER_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_ext_समयr(स्थिर काष्ठा cec_msg *msg,
					 __u8 *day,
					 __u8 *month,
					 __u8 *start_hr,
					 __u8 *start_min,
					 __u8 *duration_hr,
					 __u8 *duration_min,
					 __u8 *recording_seq,
					 __u8 *ext_src_spec,
					 __u8 *plug,
					 __u16 *phys_addr)
अणु
	*day = msg->msg[2];
	*month = msg->msg[3];
	/* Hours and minutes are in BCD क्रमmat */
	*start_hr = (msg->msg[4] >> 4) * 10 + (msg->msg[4] & 0xf);
	*start_min = (msg->msg[5] >> 4) * 10 + (msg->msg[5] & 0xf);
	*duration_hr = (msg->msg[6] >> 4) * 10 + (msg->msg[6] & 0xf);
	*duration_min = (msg->msg[7] >> 4) * 10 + (msg->msg[7] & 0xf);
	*recording_seq = msg->msg[8];
	*ext_src_spec = msg->msg[9];
	*plug = msg->msg[10];
	*phys_addr = (msg->msg[11] << 8) | msg->msg[12];
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_समयr_program_title(काष्ठा cec_msg *msg,
						   स्थिर अक्षर *prog_title)
अणु
	अचिन्हित पूर्णांक len = म_माप(prog_title);

	अगर (len > 14)
		len = 14;
	msg->len = 2 + len;
	msg->msg[1] = CEC_MSG_SET_TIMER_PROGRAM_TITLE;
	स_नकल(msg->msg + 2, prog_title, len);
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_समयr_program_title(स्थिर काष्ठा cec_msg *msg,
						   अक्षर *prog_title)
अणु
	अचिन्हित पूर्णांक len = msg->len > 2 ? msg->len - 2 : 0;

	अगर (len > 14)
		len = 14;
	स_नकल(prog_title, msg->msg + 2, len);
	prog_title[len] = '\0';
पूर्ण

/* System Inक्रमmation Feature */
अटल अंतरभूत व्योम cec_msg_cec_version(काष्ठा cec_msg *msg, __u8 cec_version)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_CEC_VERSION;
	msg->msg[2] = cec_version;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cec_version(स्थिर काष्ठा cec_msg *msg,
				       __u8 *cec_version)
अणु
	*cec_version = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_get_cec_version(काष्ठा cec_msg *msg,
					   पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GET_CEC_VERSION;
	msg->reply = reply ? CEC_MSG_CEC_VERSION : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_report_physical_addr(काष्ठा cec_msg *msg,
					__u16 phys_addr, __u8 prim_devtype)
अणु
	msg->len = 5;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_REPORT_PHYSICAL_ADDR;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
	msg->msg[4] = prim_devtype;
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_physical_addr(स्थिर काष्ठा cec_msg *msg,
					__u16 *phys_addr, __u8 *prim_devtype)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*prim_devtype = msg->msg[4];
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_physical_addr(काष्ठा cec_msg *msg,
					      पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_PHYSICAL_ADDR;
	msg->reply = reply ? CEC_MSG_REPORT_PHYSICAL_ADDR : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_menu_language(काष्ठा cec_msg *msg,
					     स्थिर अक्षर *language)
अणु
	msg->len = 5;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_SET_MENU_LANGUAGE;
	स_नकल(msg->msg + 2, language, 3);
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_menu_language(स्थिर काष्ठा cec_msg *msg,
					     अक्षर *language)
अणु
	स_नकल(language, msg->msg + 2, 3);
	language[3] = '\0';
पूर्ण

अटल अंतरभूत व्योम cec_msg_get_menu_language(काष्ठा cec_msg *msg,
					     पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GET_MENU_LANGUAGE;
	msg->reply = reply ? CEC_MSG_SET_MENU_LANGUAGE : 0;
पूर्ण

/*
 * Assumes a single RC Profile byte and a single Device Features byte,
 * i.e. no extended features are supported by this helper function.
 *
 * As of CEC 2.0 no extended features are defined, should those be added
 * in the future, then this function needs to be adapted or a new function
 * should be added.
 */
अटल अंतरभूत व्योम cec_msg_report_features(काष्ठा cec_msg *msg,
				__u8 cec_version, __u8 all_device_types,
				__u8 rc_profile, __u8 dev_features)
अणु
	msg->len = 6;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_REPORT_FEATURES;
	msg->msg[2] = cec_version;
	msg->msg[3] = all_device_types;
	msg->msg[4] = rc_profile;
	msg->msg[5] = dev_features;
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_features(स्थिर काष्ठा cec_msg *msg,
			__u8 *cec_version, __u8 *all_device_types,
			स्थिर __u8 **rc_profile, स्थिर __u8 **dev_features)
अणु
	स्थिर __u8 *p = &msg->msg[4];

	*cec_version = msg->msg[2];
	*all_device_types = msg->msg[3];
	*rc_profile = p;
	*dev_features = शून्य;
	जबतक (p < &msg->msg[14] && (*p & CEC_OP_FEAT_EXT))
		p++;
	अगर (!(*p & CEC_OP_FEAT_EXT)) अणु
		*dev_features = p + 1;
		जबतक (p < &msg->msg[15] && (*p & CEC_OP_FEAT_EXT))
			p++;
	पूर्ण
	अगर (*p & CEC_OP_FEAT_EXT)
		*rc_profile = *dev_features = शून्य;
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_features(काष्ठा cec_msg *msg,
					 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_FEATURES;
	msg->reply = reply ? CEC_MSG_REPORT_FEATURES : 0;
पूर्ण

/* Deck Control Feature */
अटल अंतरभूत व्योम cec_msg_deck_control(काष्ठा cec_msg *msg,
					__u8 deck_control_mode)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_DECK_CONTROL;
	msg->msg[2] = deck_control_mode;
पूर्ण

अटल अंतरभूत व्योम cec_ops_deck_control(स्थिर काष्ठा cec_msg *msg,
					__u8 *deck_control_mode)
अणु
	*deck_control_mode = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_deck_status(काष्ठा cec_msg *msg,
				       __u8 deck_info)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_DECK_STATUS;
	msg->msg[2] = deck_info;
पूर्ण

अटल अंतरभूत व्योम cec_ops_deck_status(स्थिर काष्ठा cec_msg *msg,
				       __u8 *deck_info)
अणु
	*deck_info = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_deck_status(काष्ठा cec_msg *msg,
					    पूर्णांक reply,
					    __u8 status_req)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_GIVE_DECK_STATUS;
	msg->msg[2] = status_req;
	msg->reply = (reply && status_req != CEC_OP_STATUS_REQ_OFF) ?
				CEC_MSG_DECK_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_give_deck_status(स्थिर काष्ठा cec_msg *msg,
					    __u8 *status_req)
अणु
	*status_req = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_play(काष्ठा cec_msg *msg,
				__u8 play_mode)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_PLAY;
	msg->msg[2] = play_mode;
पूर्ण

अटल अंतरभूत व्योम cec_ops_play(स्थिर काष्ठा cec_msg *msg,
				__u8 *play_mode)
अणु
	*play_mode = msg->msg[2];
पूर्ण


/* Tuner Control Feature */
काष्ठा cec_op_tuner_device_info अणु
	__u8 rec_flag;
	__u8 tuner_display_info;
	__u8 is_analog;
	जोड़ अणु
		काष्ठा cec_op_digital_service_id digital;
		काष्ठा अणु
			__u8 ana_bcast_type;
			__u16 ana_freq;
			__u8 bcast_प्रणाली;
		पूर्ण analog;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम cec_msg_tuner_device_status_analog(काष्ठा cec_msg *msg,
						      __u8 rec_flag,
						      __u8 tuner_display_info,
						      __u8 ana_bcast_type,
						      __u16 ana_freq,
						      __u8 bcast_प्रणाली)
अणु
	msg->len = 7;
	msg->msg[1] = CEC_MSG_TUNER_DEVICE_STATUS;
	msg->msg[2] = (rec_flag << 7) | tuner_display_info;
	msg->msg[3] = ana_bcast_type;
	msg->msg[4] = ana_freq >> 8;
	msg->msg[5] = ana_freq & 0xff;
	msg->msg[6] = bcast_प्रणाली;
पूर्ण

अटल अंतरभूत व्योम cec_msg_tuner_device_status_digital(काष्ठा cec_msg *msg,
		   __u8 rec_flag, __u8 tuner_display_info,
		   स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	msg->len = 10;
	msg->msg[1] = CEC_MSG_TUNER_DEVICE_STATUS;
	msg->msg[2] = (rec_flag << 7) | tuner_display_info;
	cec_set_digital_service_id(msg->msg + 3, digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_tuner_device_status(काष्ठा cec_msg *msg,
			स्थिर काष्ठा cec_op_tuner_device_info *tuner_dev_info)
अणु
	अगर (tuner_dev_info->is_analog)
		cec_msg_tuner_device_status_analog(msg,
			tuner_dev_info->rec_flag,
			tuner_dev_info->tuner_display_info,
			tuner_dev_info->analog.ana_bcast_type,
			tuner_dev_info->analog.ana_freq,
			tuner_dev_info->analog.bcast_प्रणाली);
	अन्यथा
		cec_msg_tuner_device_status_digital(msg,
			tuner_dev_info->rec_flag,
			tuner_dev_info->tuner_display_info,
			&tuner_dev_info->digital);
पूर्ण

अटल अंतरभूत व्योम cec_ops_tuner_device_status(स्थिर काष्ठा cec_msg *msg,
				काष्ठा cec_op_tuner_device_info *tuner_dev_info)
अणु
	tuner_dev_info->is_analog = msg->len < 10;
	tuner_dev_info->rec_flag = msg->msg[2] >> 7;
	tuner_dev_info->tuner_display_info = msg->msg[2] & 0x7f;
	अगर (tuner_dev_info->is_analog) अणु
		tuner_dev_info->analog.ana_bcast_type = msg->msg[3];
		tuner_dev_info->analog.ana_freq = (msg->msg[4] << 8) | msg->msg[5];
		tuner_dev_info->analog.bcast_प्रणाली = msg->msg[6];
		वापस;
	पूर्ण
	cec_get_digital_service_id(msg->msg + 3, &tuner_dev_info->digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_tuner_device_status(काष्ठा cec_msg *msg,
						    पूर्णांक reply,
						    __u8 status_req)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_GIVE_TUNER_DEVICE_STATUS;
	msg->msg[2] = status_req;
	msg->reply = (reply && status_req != CEC_OP_STATUS_REQ_OFF) ?
				CEC_MSG_TUNER_DEVICE_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_give_tuner_device_status(स्थिर काष्ठा cec_msg *msg,
						    __u8 *status_req)
अणु
	*status_req = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_select_analogue_service(काष्ठा cec_msg *msg,
						   __u8 ana_bcast_type,
						   __u16 ana_freq,
						   __u8 bcast_प्रणाली)
अणु
	msg->len = 6;
	msg->msg[1] = CEC_MSG_SELECT_ANALOGUE_SERVICE;
	msg->msg[2] = ana_bcast_type;
	msg->msg[3] = ana_freq >> 8;
	msg->msg[4] = ana_freq & 0xff;
	msg->msg[5] = bcast_प्रणाली;
पूर्ण

अटल अंतरभूत व्योम cec_ops_select_analogue_service(स्थिर काष्ठा cec_msg *msg,
						   __u8 *ana_bcast_type,
						   __u16 *ana_freq,
						   __u8 *bcast_प्रणाली)
अणु
	*ana_bcast_type = msg->msg[2];
	*ana_freq = (msg->msg[3] << 8) | msg->msg[4];
	*bcast_प्रणाली = msg->msg[5];
पूर्ण

अटल अंतरभूत व्योम cec_msg_select_digital_service(काष्ठा cec_msg *msg,
				स्थिर काष्ठा cec_op_digital_service_id *digital)
अणु
	msg->len = 9;
	msg->msg[1] = CEC_MSG_SELECT_DIGITAL_SERVICE;
	cec_set_digital_service_id(msg->msg + 2, digital);
पूर्ण

अटल अंतरभूत व्योम cec_ops_select_digital_service(स्थिर काष्ठा cec_msg *msg,
				काष्ठा cec_op_digital_service_id *digital)
अणु
	cec_get_digital_service_id(msg->msg + 2, digital);
पूर्ण

अटल अंतरभूत व्योम cec_msg_tuner_step_decrement(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_TUNER_STEP_DECREMENT;
पूर्ण

अटल अंतरभूत व्योम cec_msg_tuner_step_increment(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_TUNER_STEP_INCREMENT;
पूर्ण


/* Venकरोr Specअगरic Commands Feature */
अटल अंतरभूत व्योम cec_msg_device_venकरोr_id(काष्ठा cec_msg *msg, __u32 venकरोr_id)
अणु
	msg->len = 5;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_DEVICE_VENDOR_ID;
	msg->msg[2] = venकरोr_id >> 16;
	msg->msg[3] = (venकरोr_id >> 8) & 0xff;
	msg->msg[4] = venकरोr_id & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_device_venकरोr_id(स्थिर काष्ठा cec_msg *msg,
					    __u32 *venकरोr_id)
अणु
	*venकरोr_id = (msg->msg[2] << 16) | (msg->msg[3] << 8) | msg->msg[4];
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_device_venकरोr_id(काष्ठा cec_msg *msg,
						 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_DEVICE_VENDOR_ID;
	msg->reply = reply ? CEC_MSG_DEVICE_VENDOR_ID : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_venकरोr_command(काष्ठा cec_msg *msg,
					  __u8 size, स्थिर __u8 *venकरोr_cmd)
अणु
	अगर (size > 14)
		size = 14;
	msg->len = 2 + size;
	msg->msg[1] = CEC_MSG_VENDOR_COMMAND;
	स_नकल(msg->msg + 2, venकरोr_cmd, size);
पूर्ण

अटल अंतरभूत व्योम cec_ops_venकरोr_command(स्थिर काष्ठा cec_msg *msg,
					  __u8 *size,
					  स्थिर __u8 **venकरोr_cmd)
अणु
	*size = msg->len - 2;

	अगर (*size > 14)
		*size = 14;
	*venकरोr_cmd = msg->msg + 2;
पूर्ण

अटल अंतरभूत व्योम cec_msg_venकरोr_command_with_id(काष्ठा cec_msg *msg,
						  __u32 venकरोr_id, __u8 size,
						  स्थिर __u8 *venकरोr_cmd)
अणु
	अगर (size > 11)
		size = 11;
	msg->len = 5 + size;
	msg->msg[1] = CEC_MSG_VENDOR_COMMAND_WITH_ID;
	msg->msg[2] = venकरोr_id >> 16;
	msg->msg[3] = (venकरोr_id >> 8) & 0xff;
	msg->msg[4] = venकरोr_id & 0xff;
	स_नकल(msg->msg + 5, venकरोr_cmd, size);
पूर्ण

अटल अंतरभूत व्योम cec_ops_venकरोr_command_with_id(स्थिर काष्ठा cec_msg *msg,
						  __u32 *venकरोr_id,  __u8 *size,
						  स्थिर __u8 **venकरोr_cmd)
अणु
	*size = msg->len - 5;

	अगर (*size > 11)
		*size = 11;
	*venकरोr_id = (msg->msg[2] << 16) | (msg->msg[3] << 8) | msg->msg[4];
	*venकरोr_cmd = msg->msg + 5;
पूर्ण

अटल अंतरभूत व्योम cec_msg_venकरोr_remote_button_करोwn(काष्ठा cec_msg *msg,
						     __u8 size,
						     स्थिर __u8 *rc_code)
अणु
	अगर (size > 14)
		size = 14;
	msg->len = 2 + size;
	msg->msg[1] = CEC_MSG_VENDOR_REMOTE_BUTTON_DOWN;
	स_नकल(msg->msg + 2, rc_code, size);
पूर्ण

अटल अंतरभूत व्योम cec_ops_venकरोr_remote_button_करोwn(स्थिर काष्ठा cec_msg *msg,
						     __u8 *size,
						     स्थिर __u8 **rc_code)
अणु
	*size = msg->len - 2;

	अगर (*size > 14)
		*size = 14;
	*rc_code = msg->msg + 2;
पूर्ण

अटल अंतरभूत व्योम cec_msg_venकरोr_remote_button_up(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_VENDOR_REMOTE_BUTTON_UP;
पूर्ण


/* OSD Display Feature */
अटल अंतरभूत व्योम cec_msg_set_osd_string(काष्ठा cec_msg *msg,
					  __u8 disp_ctl,
					  स्थिर अक्षर *osd)
अणु
	अचिन्हित पूर्णांक len = म_माप(osd);

	अगर (len > 13)
		len = 13;
	msg->len = 3 + len;
	msg->msg[1] = CEC_MSG_SET_OSD_STRING;
	msg->msg[2] = disp_ctl;
	स_नकल(msg->msg + 3, osd, len);
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_osd_string(स्थिर काष्ठा cec_msg *msg,
					  __u8 *disp_ctl,
					  अक्षर *osd)
अणु
	अचिन्हित पूर्णांक len = msg->len > 3 ? msg->len - 3 : 0;

	*disp_ctl = msg->msg[2];
	अगर (len > 13)
		len = 13;
	स_नकल(osd, msg->msg + 3, len);
	osd[len] = '\0';
पूर्ण


/* Device OSD Transfer Feature */
अटल अंतरभूत व्योम cec_msg_set_osd_name(काष्ठा cec_msg *msg, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक len = म_माप(name);

	अगर (len > 14)
		len = 14;
	msg->len = 2 + len;
	msg->msg[1] = CEC_MSG_SET_OSD_NAME;
	स_नकल(msg->msg + 2, name, len);
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_osd_name(स्थिर काष्ठा cec_msg *msg,
					अक्षर *name)
अणु
	अचिन्हित पूर्णांक len = msg->len > 2 ? msg->len - 2 : 0;

	अगर (len > 14)
		len = 14;
	स_नकल(name, msg->msg + 2, len);
	name[len] = '\0';
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_osd_name(काष्ठा cec_msg *msg,
					 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_OSD_NAME;
	msg->reply = reply ? CEC_MSG_SET_OSD_NAME : 0;
पूर्ण


/* Device Menu Control Feature */
अटल अंतरभूत व्योम cec_msg_menu_status(काष्ठा cec_msg *msg,
				       __u8 menu_state)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_MENU_STATUS;
	msg->msg[2] = menu_state;
पूर्ण

अटल अंतरभूत व्योम cec_ops_menu_status(स्थिर काष्ठा cec_msg *msg,
				       __u8 *menu_state)
अणु
	*menu_state = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_menu_request(काष्ठा cec_msg *msg,
					पूर्णांक reply,
					__u8 menu_req)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_MENU_REQUEST;
	msg->msg[2] = menu_req;
	msg->reply = reply ? CEC_MSG_MENU_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_menu_request(स्थिर काष्ठा cec_msg *msg,
					__u8 *menu_req)
अणु
	*menu_req = msg->msg[2];
पूर्ण

काष्ठा cec_op_ui_command अणु
	__u8 ui_cmd;
	__u8 has_opt_arg;
	जोड़ अणु
		काष्ठा cec_op_channel_data channel_identअगरier;
		__u8 ui_broadcast_type;
		__u8 ui_sound_presentation_control;
		__u8 play_mode;
		__u8 ui_function_media;
		__u8 ui_function_select_av_input;
		__u8 ui_function_select_audio_input;
	पूर्ण;
पूर्ण;

अटल अंतरभूत व्योम cec_msg_user_control_pressed(काष्ठा cec_msg *msg,
					स्थिर काष्ठा cec_op_ui_command *ui_cmd)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_USER_CONTROL_PRESSED;
	msg->msg[2] = ui_cmd->ui_cmd;
	अगर (!ui_cmd->has_opt_arg)
		वापस;
	चयन (ui_cmd->ui_cmd) अणु
	हाल CEC_OP_UI_CMD_SELECT_BROADCAST_TYPE:
	हाल CEC_OP_UI_CMD_SELECT_SOUND_PRESENTATION:
	हाल CEC_OP_UI_CMD_PLAY_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_MEDIA_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_AV_INPUT_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_AUDIO_INPUT_FUNCTION:
		/* The optional opeअक्रम is one byte क्रम all these ui commands */
		msg->len++;
		msg->msg[3] = ui_cmd->play_mode;
		अवरोध;
	हाल CEC_OP_UI_CMD_TUNE_FUNCTION:
		msg->len += 4;
		msg->msg[3] = (ui_cmd->channel_identअगरier.channel_number_fmt << 2) |
			      (ui_cmd->channel_identअगरier.major >> 8);
		msg->msg[4] = ui_cmd->channel_identअगरier.major & 0xff;
		msg->msg[5] = ui_cmd->channel_identअगरier.minor >> 8;
		msg->msg[6] = ui_cmd->channel_identअगरier.minor & 0xff;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_ops_user_control_pressed(स्थिर काष्ठा cec_msg *msg,
						काष्ठा cec_op_ui_command *ui_cmd)
अणु
	ui_cmd->ui_cmd = msg->msg[2];
	ui_cmd->has_opt_arg = 0;
	अगर (msg->len == 3)
		वापस;
	चयन (ui_cmd->ui_cmd) अणु
	हाल CEC_OP_UI_CMD_SELECT_BROADCAST_TYPE:
	हाल CEC_OP_UI_CMD_SELECT_SOUND_PRESENTATION:
	हाल CEC_OP_UI_CMD_PLAY_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_MEDIA_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_AV_INPUT_FUNCTION:
	हाल CEC_OP_UI_CMD_SELECT_AUDIO_INPUT_FUNCTION:
		/* The optional opeअक्रम is one byte क्रम all these ui commands */
		ui_cmd->play_mode = msg->msg[3];
		ui_cmd->has_opt_arg = 1;
		अवरोध;
	हाल CEC_OP_UI_CMD_TUNE_FUNCTION:
		अगर (msg->len < 7)
			अवरोध;
		ui_cmd->has_opt_arg = 1;
		ui_cmd->channel_identअगरier.channel_number_fmt = msg->msg[3] >> 2;
		ui_cmd->channel_identअगरier.major = ((msg->msg[3] & 3) << 6) | msg->msg[4];
		ui_cmd->channel_identअगरier.minor = (msg->msg[5] << 8) | msg->msg[6];
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_msg_user_control_released(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_USER_CONTROL_RELEASED;
पूर्ण

/* Remote Control Passthrough Feature */

/* Power Status Feature */
अटल अंतरभूत व्योम cec_msg_report_घातer_status(काष्ठा cec_msg *msg,
					       __u8 pwr_state)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_REPORT_POWER_STATUS;
	msg->msg[2] = pwr_state;
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_घातer_status(स्थिर काष्ठा cec_msg *msg,
					       __u8 *pwr_state)
अणु
	*pwr_state = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_device_घातer_status(काष्ठा cec_msg *msg,
						    पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_DEVICE_POWER_STATUS;
	msg->reply = reply ? CEC_MSG_REPORT_POWER_STATUS : 0;
पूर्ण

/* General Protocol Messages */
अटल अंतरभूत व्योम cec_msg_feature_पात(काष्ठा cec_msg *msg,
					 __u8 पात_msg, __u8 reason)
अणु
	msg->len = 4;
	msg->msg[1] = CEC_MSG_FEATURE_ABORT;
	msg->msg[2] = पात_msg;
	msg->msg[3] = reason;
पूर्ण

अटल अंतरभूत व्योम cec_ops_feature_पात(स्थिर काष्ठा cec_msg *msg,
					 __u8 *पात_msg, __u8 *reason)
अणु
	*पात_msg = msg->msg[2];
	*reason = msg->msg[3];
पूर्ण

/* This changes the current message पूर्णांकo a feature पात message */
अटल अंतरभूत व्योम cec_msg_reply_feature_पात(काष्ठा cec_msg *msg, __u8 reason)
अणु
	cec_msg_set_reply_to(msg, msg);
	msg->len = 4;
	msg->msg[2] = msg->msg[1];
	msg->msg[3] = reason;
	msg->msg[1] = CEC_MSG_FEATURE_ABORT;
पूर्ण

अटल अंतरभूत व्योम cec_msg_पात(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_ABORT;
पूर्ण


/* System Audio Control Feature */
अटल अंतरभूत व्योम cec_msg_report_audio_status(काष्ठा cec_msg *msg,
					       __u8 aud_mute_status,
					       __u8 aud_vol_status)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_REPORT_AUDIO_STATUS;
	msg->msg[2] = (aud_mute_status << 7) | (aud_vol_status & 0x7f);
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_audio_status(स्थिर काष्ठा cec_msg *msg,
					       __u8 *aud_mute_status,
					       __u8 *aud_vol_status)
अणु
	*aud_mute_status = msg->msg[2] >> 7;
	*aud_vol_status = msg->msg[2] & 0x7f;
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_audio_status(काष्ठा cec_msg *msg,
					     पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_AUDIO_STATUS;
	msg->reply = reply ? CEC_MSG_REPORT_AUDIO_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_set_प्रणाली_audio_mode(काष्ठा cec_msg *msg,
						 __u8 sys_aud_status)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_SET_SYSTEM_AUDIO_MODE;
	msg->msg[2] = sys_aud_status;
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_प्रणाली_audio_mode(स्थिर काष्ठा cec_msg *msg,
						 __u8 *sys_aud_status)
अणु
	*sys_aud_status = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_प्रणाली_audio_mode_request(काष्ठा cec_msg *msg,
						     पूर्णांक reply,
						     __u16 phys_addr)
अणु
	msg->len = phys_addr == 0xffff ? 2 : 4;
	msg->msg[1] = CEC_MSG_SYSTEM_AUDIO_MODE_REQUEST;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
	msg->reply = reply ? CEC_MSG_SET_SYSTEM_AUDIO_MODE : 0;

पूर्ण

अटल अंतरभूत व्योम cec_ops_प्रणाली_audio_mode_request(स्थिर काष्ठा cec_msg *msg,
						     __u16 *phys_addr)
अणु
	अगर (msg->len < 4)
		*phys_addr = 0xffff;
	अन्यथा
		*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_प्रणाली_audio_mode_status(काष्ठा cec_msg *msg,
						    __u8 sys_aud_status)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_SYSTEM_AUDIO_MODE_STATUS;
	msg->msg[2] = sys_aud_status;
पूर्ण

अटल अंतरभूत व्योम cec_ops_प्रणाली_audio_mode_status(स्थिर काष्ठा cec_msg *msg,
						    __u8 *sys_aud_status)
अणु
	*sys_aud_status = msg->msg[2];
पूर्ण

अटल अंतरभूत व्योम cec_msg_give_प्रणाली_audio_mode_status(काष्ठा cec_msg *msg,
							 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_GIVE_SYSTEM_AUDIO_MODE_STATUS;
	msg->reply = reply ? CEC_MSG_SYSTEM_AUDIO_MODE_STATUS : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_report_लघु_audio_descriptor(काष्ठा cec_msg *msg,
					__u8 num_descriptors,
					स्थिर __u32 *descriptors)
अणु
	अचिन्हित पूर्णांक i;

	अगर (num_descriptors > 4)
		num_descriptors = 4;
	msg->len = 2 + num_descriptors * 3;
	msg->msg[1] = CEC_MSG_REPORT_SHORT_AUDIO_DESCRIPTOR;
	क्रम (i = 0; i < num_descriptors; i++) अणु
		msg->msg[2 + i * 3] = (descriptors[i] >> 16) & 0xff;
		msg->msg[3 + i * 3] = (descriptors[i] >> 8) & 0xff;
		msg->msg[4 + i * 3] = descriptors[i] & 0xff;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_लघु_audio_descriptor(स्थिर काष्ठा cec_msg *msg,
							 __u8 *num_descriptors,
							 __u32 *descriptors)
अणु
	अचिन्हित पूर्णांक i;

	*num_descriptors = (msg->len - 2) / 3;
	अगर (*num_descriptors > 4)
		*num_descriptors = 4;
	क्रम (i = 0; i < *num_descriptors; i++)
		descriptors[i] = (msg->msg[2 + i * 3] << 16) |
			(msg->msg[3 + i * 3] << 8) |
			msg->msg[4 + i * 3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_request_लघु_audio_descriptor(काष्ठा cec_msg *msg,
					पूर्णांक reply,
					__u8 num_descriptors,
					स्थिर __u8 *audio_क्रमmat_id,
					स्थिर __u8 *audio_क्रमmat_code)
अणु
	अचिन्हित पूर्णांक i;

	अगर (num_descriptors > 4)
		num_descriptors = 4;
	msg->len = 2 + num_descriptors;
	msg->msg[1] = CEC_MSG_REQUEST_SHORT_AUDIO_DESCRIPTOR;
	msg->reply = reply ? CEC_MSG_REPORT_SHORT_AUDIO_DESCRIPTOR : 0;
	क्रम (i = 0; i < num_descriptors; i++)
		msg->msg[2 + i] = (audio_क्रमmat_id[i] << 6) |
				  (audio_क्रमmat_code[i] & 0x3f);
पूर्ण

अटल अंतरभूत व्योम cec_ops_request_लघु_audio_descriptor(स्थिर काष्ठा cec_msg *msg,
					__u8 *num_descriptors,
					__u8 *audio_क्रमmat_id,
					__u8 *audio_क्रमmat_code)
अणु
	अचिन्हित पूर्णांक i;

	*num_descriptors = msg->len - 2;
	अगर (*num_descriptors > 4)
		*num_descriptors = 4;
	क्रम (i = 0; i < *num_descriptors; i++) अणु
		audio_क्रमmat_id[i] = msg->msg[2 + i] >> 6;
		audio_क्रमmat_code[i] = msg->msg[2 + i] & 0x3f;
	पूर्ण
पूर्ण


/* Audio Rate Control Feature */
अटल अंतरभूत व्योम cec_msg_set_audio_rate(काष्ठा cec_msg *msg,
					  __u8 audio_rate)
अणु
	msg->len = 3;
	msg->msg[1] = CEC_MSG_SET_AUDIO_RATE;
	msg->msg[2] = audio_rate;
पूर्ण

अटल अंतरभूत व्योम cec_ops_set_audio_rate(स्थिर काष्ठा cec_msg *msg,
					  __u8 *audio_rate)
अणु
	*audio_rate = msg->msg[2];
पूर्ण


/* Audio Return Channel Control Feature */
अटल अंतरभूत व्योम cec_msg_report_arc_initiated(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_REPORT_ARC_INITIATED;
पूर्ण

अटल अंतरभूत व्योम cec_msg_initiate_arc(काष्ठा cec_msg *msg,
					पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_INITIATE_ARC;
	msg->reply = reply ? CEC_MSG_REPORT_ARC_INITIATED : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_request_arc_initiation(काष्ठा cec_msg *msg,
						  पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_REQUEST_ARC_INITIATION;
	msg->reply = reply ? CEC_MSG_INITIATE_ARC : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_report_arc_terminated(काष्ठा cec_msg *msg)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_REPORT_ARC_TERMINATED;
पूर्ण

अटल अंतरभूत व्योम cec_msg_terminate_arc(काष्ठा cec_msg *msg,
					 पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_TERMINATE_ARC;
	msg->reply = reply ? CEC_MSG_REPORT_ARC_TERMINATED : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_request_arc_termination(काष्ठा cec_msg *msg,
						   पूर्णांक reply)
अणु
	msg->len = 2;
	msg->msg[1] = CEC_MSG_REQUEST_ARC_TERMINATION;
	msg->reply = reply ? CEC_MSG_TERMINATE_ARC : 0;
पूर्ण


/* Dynamic Audio Lipsync Feature */
/* Only क्रम CEC 2.0 and up */
अटल अंतरभूत व्योम cec_msg_report_current_latency(काष्ठा cec_msg *msg,
						  __u16 phys_addr,
						  __u8 video_latency,
						  __u8 low_latency_mode,
						  __u8 audio_out_compensated,
						  __u8 audio_out_delay)
अणु
	msg->len = 6;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_REPORT_CURRENT_LATENCY;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
	msg->msg[4] = video_latency;
	msg->msg[5] = (low_latency_mode << 2) | audio_out_compensated;
	अगर (audio_out_compensated == 3)
		msg->msg[msg->len++] = audio_out_delay;
पूर्ण

अटल अंतरभूत व्योम cec_ops_report_current_latency(स्थिर काष्ठा cec_msg *msg,
						  __u16 *phys_addr,
						  __u8 *video_latency,
						  __u8 *low_latency_mode,
						  __u8 *audio_out_compensated,
						  __u8 *audio_out_delay)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*video_latency = msg->msg[4];
	*low_latency_mode = (msg->msg[5] >> 2) & 1;
	*audio_out_compensated = msg->msg[5] & 3;
	अगर (*audio_out_compensated == 3 && msg->len >= 7)
		*audio_out_delay = msg->msg[6];
	अन्यथा
		*audio_out_delay = 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_request_current_latency(काष्ठा cec_msg *msg,
						   पूर्णांक reply,
						   __u16 phys_addr)
अणु
	msg->len = 4;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_REQUEST_CURRENT_LATENCY;
	msg->msg[2] = phys_addr >> 8;
	msg->msg[3] = phys_addr & 0xff;
	msg->reply = reply ? CEC_MSG_REPORT_CURRENT_LATENCY : 0;
पूर्ण

अटल अंतरभूत व्योम cec_ops_request_current_latency(स्थिर काष्ठा cec_msg *msg,
						   __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण


/* Capability Discovery and Control Feature */
अटल अंतरभूत व्योम cec_msg_cdc_hec_inquire_state(काष्ठा cec_msg *msg,
						 __u16 phys_addr1,
						 __u16 phys_addr2)
अणु
	msg->len = 9;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_INQUIRE_STATE;
	msg->msg[5] = phys_addr1 >> 8;
	msg->msg[6] = phys_addr1 & 0xff;
	msg->msg[7] = phys_addr2 >> 8;
	msg->msg[8] = phys_addr2 & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_inquire_state(स्थिर काष्ठा cec_msg *msg,
						 __u16 *phys_addr,
						 __u16 *phys_addr1,
						 __u16 *phys_addr2)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addr1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addr2 = (msg->msg[7] << 8) | msg->msg[8];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_report_state(काष्ठा cec_msg *msg,
						__u16 target_phys_addr,
						__u8 hec_func_state,
						__u8 host_func_state,
						__u8 enc_func_state,
						__u8 cdc_errcode,
						__u8 has_field,
						__u16 hec_field)
अणु
	msg->len = has_field ? 10 : 8;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_REPORT_STATE;
	msg->msg[5] = target_phys_addr >> 8;
	msg->msg[6] = target_phys_addr & 0xff;
	msg->msg[7] = (hec_func_state << 6) |
		      (host_func_state << 4) |
		      (enc_func_state << 2) |
		      cdc_errcode;
	अगर (has_field) अणु
		msg->msg[8] = hec_field >> 8;
		msg->msg[9] = hec_field & 0xff;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_report_state(स्थिर काष्ठा cec_msg *msg,
						__u16 *phys_addr,
						__u16 *target_phys_addr,
						__u8 *hec_func_state,
						__u8 *host_func_state,
						__u8 *enc_func_state,
						__u8 *cdc_errcode,
						__u8 *has_field,
						__u16 *hec_field)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*target_phys_addr = (msg->msg[5] << 8) | msg->msg[6];
	*hec_func_state = msg->msg[7] >> 6;
	*host_func_state = (msg->msg[7] >> 4) & 3;
	*enc_func_state = (msg->msg[7] >> 4) & 3;
	*cdc_errcode = msg->msg[7] & 3;
	*has_field = msg->len >= 10;
	*hec_field = *has_field ? ((msg->msg[8] << 8) | msg->msg[9]) : 0;
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_set_state(काष्ठा cec_msg *msg,
					     __u16 phys_addr1,
					     __u16 phys_addr2,
					     __u8 hec_set_state,
					     __u16 phys_addr3,
					     __u16 phys_addr4,
					     __u16 phys_addr5)
अणु
	msg->len = 10;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_INQUIRE_STATE;
	msg->msg[5] = phys_addr1 >> 8;
	msg->msg[6] = phys_addr1 & 0xff;
	msg->msg[7] = phys_addr2 >> 8;
	msg->msg[8] = phys_addr2 & 0xff;
	msg->msg[9] = hec_set_state;
	अगर (phys_addr3 != CEC_PHYS_ADDR_INVALID) अणु
		msg->msg[msg->len++] = phys_addr3 >> 8;
		msg->msg[msg->len++] = phys_addr3 & 0xff;
		अगर (phys_addr4 != CEC_PHYS_ADDR_INVALID) अणु
			msg->msg[msg->len++] = phys_addr4 >> 8;
			msg->msg[msg->len++] = phys_addr4 & 0xff;
			अगर (phys_addr5 != CEC_PHYS_ADDR_INVALID) अणु
				msg->msg[msg->len++] = phys_addr5 >> 8;
				msg->msg[msg->len++] = phys_addr5 & 0xff;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_set_state(स्थिर काष्ठा cec_msg *msg,
					     __u16 *phys_addr,
					     __u16 *phys_addr1,
					     __u16 *phys_addr2,
					     __u8 *hec_set_state,
					     __u16 *phys_addr3,
					     __u16 *phys_addr4,
					     __u16 *phys_addr5)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addr1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addr2 = (msg->msg[7] << 8) | msg->msg[8];
	*hec_set_state = msg->msg[9];
	*phys_addr3 = *phys_addr4 = *phys_addr5 = CEC_PHYS_ADDR_INVALID;
	अगर (msg->len >= 12)
		*phys_addr3 = (msg->msg[10] << 8) | msg->msg[11];
	अगर (msg->len >= 14)
		*phys_addr4 = (msg->msg[12] << 8) | msg->msg[13];
	अगर (msg->len >= 16)
		*phys_addr5 = (msg->msg[14] << 8) | msg->msg[15];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_set_state_adjacent(काष्ठा cec_msg *msg,
						      __u16 phys_addr1,
						      __u8 hec_set_state)
अणु
	msg->len = 8;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_SET_STATE_ADJACENT;
	msg->msg[5] = phys_addr1 >> 8;
	msg->msg[6] = phys_addr1 & 0xff;
	msg->msg[7] = hec_set_state;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_set_state_adjacent(स्थिर काष्ठा cec_msg *msg,
						      __u16 *phys_addr,
						      __u16 *phys_addr1,
						      __u8 *hec_set_state)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addr1 = (msg->msg[5] << 8) | msg->msg[6];
	*hec_set_state = msg->msg[7];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_request_deactivation(काष्ठा cec_msg *msg,
							__u16 phys_addr1,
							__u16 phys_addr2,
							__u16 phys_addr3)
अणु
	msg->len = 11;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_REQUEST_DEACTIVATION;
	msg->msg[5] = phys_addr1 >> 8;
	msg->msg[6] = phys_addr1 & 0xff;
	msg->msg[7] = phys_addr2 >> 8;
	msg->msg[8] = phys_addr2 & 0xff;
	msg->msg[9] = phys_addr3 >> 8;
	msg->msg[10] = phys_addr3 & 0xff;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_request_deactivation(स्थिर काष्ठा cec_msg *msg,
							__u16 *phys_addr,
							__u16 *phys_addr1,
							__u16 *phys_addr2,
							__u16 *phys_addr3)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*phys_addr1 = (msg->msg[5] << 8) | msg->msg[6];
	*phys_addr2 = (msg->msg[7] << 8) | msg->msg[8];
	*phys_addr3 = (msg->msg[9] << 8) | msg->msg[10];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_notअगरy_alive(काष्ठा cec_msg *msg)
अणु
	msg->len = 5;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_NOTIFY_ALIVE;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_notअगरy_alive(स्थिर काष्ठा cec_msg *msg,
						__u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hec_discover(काष्ठा cec_msg *msg)
अणु
	msg->len = 5;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HEC_DISCOVER;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hec_discover(स्थिर काष्ठा cec_msg *msg,
					    __u16 *phys_addr)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hpd_set_state(काष्ठा cec_msg *msg,
					     __u8 input_port,
					     __u8 hpd_state)
अणु
	msg->len = 6;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HPD_SET_STATE;
	msg->msg[5] = (input_port << 4) | hpd_state;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hpd_set_state(स्थिर काष्ठा cec_msg *msg,
					    __u16 *phys_addr,
					    __u8 *input_port,
					    __u8 *hpd_state)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*input_port = msg->msg[5] >> 4;
	*hpd_state = msg->msg[5] & 0xf;
पूर्ण

अटल अंतरभूत व्योम cec_msg_cdc_hpd_report_state(काष्ठा cec_msg *msg,
						__u8 hpd_state,
						__u8 hpd_error)
अणु
	msg->len = 6;
	msg->msg[0] |= 0xf; /* broadcast */
	msg->msg[1] = CEC_MSG_CDC_MESSAGE;
	/* msg[2] and msg[3] (phys_addr) are filled in by the CEC framework */
	msg->msg[4] = CEC_MSG_CDC_HPD_REPORT_STATE;
	msg->msg[5] = (hpd_state << 4) | hpd_error;
पूर्ण

अटल अंतरभूत व्योम cec_ops_cdc_hpd_report_state(स्थिर काष्ठा cec_msg *msg,
						__u16 *phys_addr,
						__u8 *hpd_state,
						__u8 *hpd_error)
अणु
	*phys_addr = (msg->msg[2] << 8) | msg->msg[3];
	*hpd_state = msg->msg[5] >> 4;
	*hpd_error = msg->msg[5] & 0xf;
पूर्ण

#पूर्ण_अगर
