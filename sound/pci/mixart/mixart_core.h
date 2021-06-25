<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * low level पूर्णांकerface with पूर्णांकerrupt handling and mail box implementation
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_MIXART_CORE_H
#घोषणा __SOUND_MIXART_CORE_H


क्रमागत mixart_message_id अणु
	MSG_CONNECTOR_GET_AUDIO_INFO         = 0x050008,
	MSG_CONNECTOR_GET_OUT_AUDIO_LEVEL    = 0x050009,
	MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL    = 0x05000A,

	MSG_CONSOLE_MANAGER                  = 0x070000,
	MSG_CONSOLE_GET_CLOCK_UID            = 0x070003,

	MSG_PHYSICALIO_SET_LEVEL             = 0x0F0008,

	MSG_STREAM_ADD_INPUT_GROUP           = 0x130000,
	MSG_STREAM_ADD_OUTPUT_GROUP          = 0x130001,
	MSG_STREAM_DELETE_GROUP              = 0x130004,
	MSG_STREAM_START_STREAM_GRP_PACKET   = 0x130006,
	MSG_STREAM_START_INPUT_STAGE_PACKET  = 0x130007,
	MSG_STREAM_START_OUTPUT_STAGE_PACKET = 0x130008,
	MSG_STREAM_STOP_STREAM_GRP_PACKET    = 0x130009,
	MSG_STREAM_STOP_INPUT_STAGE_PACKET   = 0x13000A,
	MSG_STREAM_STOP_OUTPUT_STAGE_PACKET  = 0x13000B,
	MSG_STREAM_SET_INPUT_STAGE_PARAM     = 0x13000F,
	MSG_STREAM_SET_OUTPUT_STAGE_PARAM    = 0x130010,
	MSG_STREAM_SET_IN_AUDIO_LEVEL        = 0x130015,
	MSG_STREAM_SET_OUT_STREAM_LEVEL      = 0x130017,

	MSG_SYSTEM_FIRST_ID                  = 0x160000,
	MSG_SYSTEM_ENUM_PHYSICAL_IO          = 0x16000E,
	MSG_SYSTEM_ENUM_PLAY_CONNECTOR       = 0x160017,
	MSG_SYSTEM_ENUM_RECORD_CONNECTOR     = 0x160018,
	MSG_SYSTEM_WAIT_SYNCHRO_CMD          = 0x16002C,
	MSG_SYSTEM_SEND_SYNCHRO_CMD          = 0x16002D,

	MSG_SERVICES_TIMER_NOTIFY            = 0x1D0404,
	MSG_SERVICES_REPORT_TRACES           = 0x1D0700,

	MSG_CLOCK_CHECK_PROPERTIES           = 0x200001,
	MSG_CLOCK_SET_PROPERTIES             = 0x200002,
पूर्ण;


काष्ठा mixart_msg
अणु
	u32          message_id;
	काष्ठा mixart_uid uid;
	व्योम*        data;
	माप_प्रकार       size;
पूर्ण;

/* काष्ठाs used to communicate with miXart */

काष्ठा mixart_क्रमागत_connector_resp
अणु
	u32  error_code;
	u32  first_uid_offset;
	u32  uid_count;
	u32  current_uid_index;
	काष्ठा mixart_uid uid[MIXART_MAX_PHYS_CONNECTORS];
पूर्ण __attribute__((packed));


/* used क्रम following काष्ठा */
#घोषणा MIXART_FLOAT_P_22_0_TO_HEX      0x41b00000  /* 22.0f */
#घोषणा MIXART_FLOAT_M_20_0_TO_HEX      0xc1a00000  /* -20.0f */
#घोषणा MIXART_FLOAT____0_0_TO_HEX      0x00000000  /* 0.0f */

काष्ठा mixart_audio_info_req
अणु
	u32 line_max_level;    /* भग्न */
	u32 micro_max_level;   /* भग्न */
	u32 cd_max_level;      /* भग्न */
पूर्ण __attribute__((packed));

काष्ठा mixart_analog_hw_info
अणु
	u32 is_present;
	u32 hw_connection_type;
	u32 max_level;         /* भग्न */
	u32 min_var_level;     /* भग्न */
	u32 max_var_level;     /* भग्न */
	u32 step_var_level;    /* भग्न */
	u32 fix_gain;          /* भग्न */
	u32 zero_var;          /* भग्न */
पूर्ण __attribute__((packed));

काष्ठा mixart_digital_hw_info
अणु
	u32   hw_connection_type;
	u32   presence;
	u32   घड़ी;
	u32   reserved;
पूर्ण __attribute__((packed));

काष्ठा mixart_analog_info
अणु
	u32                     type_mask;
	काष्ठा mixart_analog_hw_info micro_info;
	काष्ठा mixart_analog_hw_info line_info;
	काष्ठा mixart_analog_hw_info cd_info;
	u32                     analog_level_present;
पूर्ण __attribute__((packed));

काष्ठा mixart_digital_info
अणु
	u32 type_mask;
	काष्ठा mixart_digital_hw_info aes_info;
	काष्ठा mixart_digital_hw_info adat_info;
पूर्ण __attribute__((packed));

काष्ठा mixart_audio_info
अणु
	u32                   घड़ी_प्रकारype_mask;
	काष्ठा mixart_analog_info  analog_info;
	काष्ठा mixart_digital_info digital_info;
पूर्ण __attribute__((packed));

काष्ठा mixart_audio_info_resp
अणु
	u32                 txx_status;
	काष्ठा mixart_audio_info info;
पूर्ण __attribute__((packed));


/* used क्रम nb_bytes_max_per_sample */
#घोषणा MIXART_FLOAT_P__4_0_TO_HEX      0x40800000  /* +4.0f */
#घोषणा MIXART_FLOAT_P__8_0_TO_HEX      0x41000000  /* +8.0f */

काष्ठा mixart_stream_info
अणु
	u32 size_max_byte_frame;
	u32 size_max_sample_frame;
	u32 nb_bytes_max_per_sample;  /* भग्न */
पूर्ण __attribute__((packed));

/*  MSG_STREAM_ADD_INPUT_GROUP */
/*  MSG_STREAM_ADD_OUTPUT_GROUP */

काष्ठा mixart_streaming_group_req
अणु
	u32 stream_count;
	u32 channel_count;
	u32 user_grp_number;
	u32 first_phys_audio;
	u32 latency;
	काष्ठा mixart_stream_info stream_info[32];
	काष्ठा mixart_uid connector;
	u32 flow_entry[32];
पूर्ण __attribute__((packed));

काष्ठा mixart_stream_desc
अणु
	काष्ठा mixart_uid stream_uid;
	u32          stream_desc;
पूर्ण __attribute__((packed));

काष्ठा mixart_streaming_group
अणु
	u32                  status;
	काष्ठा mixart_uid    group;
	u32                  pipe_desc;
	u32                  stream_count;
	काष्ठा mixart_stream_desc stream[32];
पूर्ण __attribute__((packed));

/* MSG_STREAM_DELETE_GROUP */

/* request : mixart_uid_t group */

काष्ठा mixart_delete_group_resp
अणु
	u32  status;
	u32  unused[2];
पूर्ण __attribute__((packed));


/* 	MSG_STREAM_START_INPUT_STAGE_PACKET  = 0x130000 + 7,
	MSG_STREAM_START_OUTPUT_STAGE_PACKET = 0x130000 + 8,
	MSG_STREAM_STOP_INPUT_STAGE_PACKET   = 0x130000 + 10,
	MSG_STREAM_STOP_OUTPUT_STAGE_PACKET  = 0x130000 + 11,
 */

काष्ठा mixart_fx_couple_uid
अणु
	काष्ठा mixart_uid uid_fx_code;
	काष्ठा mixart_uid uid_fx_data;
पूर्ण __attribute__((packed));

काष्ठा mixart_txx_stream_desc
अणु
	काष्ठा mixart_uid       uid_pipe;
	u32                     stream_idx;
	u32                     fx_number;
	काष्ठा mixart_fx_couple_uid  uid_fx[4];
पूर्ण __attribute__((packed));

काष्ठा mixart_flow_info
अणु
	काष्ठा mixart_txx_stream_desc  stream_desc;
	u32                       flow_entry;
	u32                       flow_phy_addr;
पूर्ण __attribute__((packed));

काष्ठा mixart_stream_state_req
अणु
	u32                 delayed;
	u64                 scheduler;
	u32                 reserved4np[3];
	u32                 stream_count;  /* set to 1 क्रम instance */
	काष्ठा mixart_flow_info  stream_info;   /* could be an array[stream_count] */
पूर्ण __attribute__((packed));

/* 	MSG_STREAM_START_STREAM_GRP_PACKET   = 0x130000 + 6
	MSG_STREAM_STOP_STREAM_GRP_PACKET    = 0x130000 + 9
 */

काष्ठा mixart_group_state_req
अणु
	u32           delayed;
	u64           scheduler;
	u32           reserved4np[2];
	u32           pipe_count;    /* set to 1 क्रम instance */
	काष्ठा mixart_uid  pipe_uid[1];   /* could be an array[pipe_count] */
पूर्ण __attribute__((packed));

काष्ठा mixart_group_state_resp
अणु
	u32           txx_status;
	u64           scheduler;
पूर्ण __attribute__((packed));



/* Structures used by the MSG_SERVICES_TIMER_NOTIFY command */

काष्ठा mixart_sample_pos
अणु
	u32   buffer_id;
	u32   validity;
	u32   sample_pos_high_part;
	u32   sample_pos_low_part;
पूर्ण __attribute__((packed));

काष्ठा mixart_समयr_notअगरy
अणु
	u32                  stream_count;
	काष्ठा mixart_sample_pos  streams[MIXART_MAX_STREAM_PER_CARD * MIXART_MAX_CARDS];
पूर्ण __attribute__((packed));


/*	MSG_CONSOLE_GET_CLOCK_UID            = 0x070003,
 */

/* request is a uid with desc = MSG_CONSOLE_MANAGER | cardindex */

काष्ठा mixart_वापस_uid
अणु
	u32 error_code;
	काष्ठा mixart_uid uid;
पूर्ण __attribute__((packed));

/*	MSG_CLOCK_CHECK_PROPERTIES           = 0x200001,
	MSG_CLOCK_SET_PROPERTIES             = 0x200002,
*/

क्रमागत mixart_घड़ी_generic_type अणु
	CGT_NO_CLOCK,
	CGT_INTERNAL_CLOCK,
	CGT_PROGRAMMABLE_CLOCK,
	CGT_INTERNAL_ENSLAVED_CLOCK,
	CGT_EXTERNAL_CLOCK,
	CGT_CURRENT_CLOCK
पूर्ण;

क्रमागत mixart_घड़ी_mode अणु
	CM_UNDEFINED,
	CM_MASTER,
	CM_SLAVE,
	CM_STANDALONE,
	CM_NOT_CONCERNED
पूर्ण;


काष्ठा mixart_घड़ी_properties
अणु
	u32 error_code;
	u32 validation_mask;
	u32 frequency;
	u32 reference_frequency;
	u32 घड़ी_generic_type;
	u32 घड़ी_mode;
	काष्ठा mixart_uid uid_घड़ी_source;
	काष्ठा mixart_uid uid_event_source;
	u32 event_mode;
	u32 synchro_संकेत_presence;
	u32 क्रमmat;
	u32 board_mask;
	u32 nb_callers; /* set to 1 (see below) */
	काष्ठा mixart_uid uid_caller[1];
पूर्ण __attribute__((packed));

काष्ठा mixart_घड़ी_properties_resp
अणु
	u32 status;
	u32 घड़ी_mode;
पूर्ण __attribute__((packed));


/*	MSG_STREAM_SET_INPUT_STAGE_PARAM     = 0x13000F */
/*	MSG_STREAM_SET_OUTPUT_STAGE_PARAM    = 0x130010 */

क्रमागत mixart_coding_type अणु
	CT_NOT_DEFINED,
	CT_LINEAR,
	CT_MPEG_L1,
	CT_MPEG_L2,
	CT_MPEG_L3,
	CT_MPEG_L3_LSF,
	CT_GSM
पूर्ण;
क्रमागत mixart_sample_type अणु
	ST_NOT_DEFINED,
	ST_FLOATING_POINT_32BE,
	ST_FLOATING_POINT_32LE,
	ST_FLOATING_POINT_64BE,
	ST_FLOATING_POINT_64LE,
	ST_FIXED_POINT_8,
	ST_FIXED_POINT_16BE,
	ST_FIXED_POINT_16LE,
	ST_FIXED_POINT_24BE,
	ST_FIXED_POINT_24LE,
	ST_FIXED_POINT_32BE,
	ST_FIXED_POINT_32LE,
	ST_INTEGER_8,
	ST_INTEGER_16BE,
	ST_INTEGER_16LE,
	ST_INTEGER_24BE,
	ST_INTEGER_24LE,
	ST_INTEGER_32BE,
	ST_INTEGER_32LE
पूर्ण;

काष्ठा mixart_stream_param_desc
अणु
	u32 coding_type;  /* use क्रमागत mixart_coding_type */
	u32 sample_type;  /* use क्रमागत mixart_sample_type */

	जोड़ अणु
		काष्ठा अणु
			u32 linear_endian_ness;
			u32 linear_bits;
			u32 is_चिन्हित;
			u32 is_भग्न;
		पूर्ण linear_क्रमmat_info;

		काष्ठा अणु
			u32 mpeg_layer;
			u32 mpeg_mode;
			u32 mpeg_mode_extension;
			u32 mpeg_pre_emphasis;
			u32 mpeg_has_padding_bit;
			u32 mpeg_has_crc;
			u32 mpeg_has_extension;
			u32 mpeg_is_original;
			u32 mpeg_has_copyright;
		पूर्ण mpeg_क्रमmat_info;
	पूर्ण क्रमmat_info;

	u32 delayed;
	u64 scheduler;
	u32 sample_size;
	u32 has_header;
	u32 has_suffix;
	u32 has_bitrate;
	u32 samples_per_frame;
	u32 bytes_per_frame;
	u32 bytes_per_sample;
	u32 sampling_freq;
	u32 number_of_channel;
	u32 stream_number;
	u32 buffer_size;
	u32 dअगरfered_समय;
	u32 reserved4np[3];
	u32 pipe_count;                           /* set to 1 (array size !) */
	u32 stream_count;                         /* set to 1 (array size !) */
	काष्ठा mixart_txx_stream_desc stream_desc[1];  /* only one stream per command, but this could be an array */

पूर्ण __attribute__((packed));


/*	MSG_CONNECTOR_GET_OUT_AUDIO_LEVEL    = 0x050009,
 */


काष्ठा mixart_get_out_audio_level
अणु
	u32 txx_status;
	u32 digital_level;   /* भग्न */
	u32 analog_level;    /* भग्न */
	u32 monitor_level;   /* भग्न */
	u32 mute;
	u32 monitor_mute1;
	u32 monitor_mute2;
पूर्ण __attribute__((packed));


/*	MSG_CONNECTOR_SET_OUT_AUDIO_LEVEL    = 0x05000A,
 */

/* used क्रम valid_mask below */
#घोषणा MIXART_AUDIO_LEVEL_ANALOG_MASK	0x01
#घोषणा MIXART_AUDIO_LEVEL_DIGITAL_MASK	0x02
#घोषणा MIXART_AUDIO_LEVEL_MONITOR_MASK	0x04
#घोषणा MIXART_AUDIO_LEVEL_MUTE_MASK	0x08
#घोषणा MIXART_AUDIO_LEVEL_MUTE_M1_MASK	0x10
#घोषणा MIXART_AUDIO_LEVEL_MUTE_M2_MASK	0x20

काष्ठा mixart_set_out_audio_level
अणु
	u32 delayed;
	u64 scheduler;
	u32 valid_mask1;
	u32 valid_mask2;
	u32 digital_level;   /* भग्न */
	u32 analog_level;    /* भग्न */
	u32 monitor_level;   /* भग्न */
	u32 mute;
	u32 monitor_mute1;
	u32 monitor_mute2;
	u32 reserved4np;
पूर्ण __attribute__((packed));


/*	MSG_SYSTEM_ENUM_PHYSICAL_IO          = 0x16000E,
 */

#घोषणा MIXART_MAX_PHYS_IO  (MIXART_MAX_CARDS * 2 * 2) /* 4 * (analog+digital) * (playback+capture) */

काष्ठा mixart_uid_क्रमागतeration
अणु
	u32 error_code;
	u32 first_uid_offset;
	u32 nb_uid;
	u32 current_uid_index;
	काष्ठा mixart_uid uid[MIXART_MAX_PHYS_IO];
पूर्ण __attribute__((packed));


/*	MSG_PHYSICALIO_SET_LEVEL             = 0x0F0008,
	MSG_PHYSICALIO_GET_LEVEL             = 0x0F000C,
*/

काष्ठा mixart_io_channel_level
अणु
	u32 analog_level;   /* भग्न */
	u32 unused[2];
पूर्ण __attribute__((packed));

काष्ठा mixart_io_level
अणु
	s32 channel; /* 0=left, 1=right, -1=both, -2=both same */
	काष्ठा mixart_io_channel_level level[2];
पूर्ण __attribute__((packed));


/*	MSG_STREAM_SET_IN_AUDIO_LEVEL        = 0x130015,
 */

काष्ठा mixart_in_audio_level_info
अणु
	काष्ठा mixart_uid connector;
	u32 valid_mask1;
	u32 valid_mask2;
	u32 digital_level;
	u32 analog_level;
पूर्ण __attribute__((packed));

काष्ठा mixart_set_in_audio_level_req
अणु
	u32 delayed;
	u64 scheduler;
	u32 audio_count;  /* set to <= 2 */
	u32 reserved4np;
	काष्ठा mixart_in_audio_level_info level[2];
पूर्ण __attribute__((packed));

/* response is a 32 bit status */


/*	MSG_STREAM_SET_OUT_STREAM_LEVEL      = 0x130017,
 */

/* defines used क्रम valid_mask1 */
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_LEFT_AUDIO1		0x01
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_LEFT_AUDIO2		0x02
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_RIGHT_AUDIO1	0x04
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_RIGHT_AUDIO2	0x08
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_STREAM_1		0x10
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_STREAM_2		0x20
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_MUTE_1		0x40
#घोषणा MIXART_OUT_STREAM_SET_LEVEL_MUTE_2		0x80

काष्ठा mixart_out_stream_level_info
अणु
	u32 valid_mask1;
	u32 valid_mask2;
	u32 left_to_out1_level;
	u32 left_to_out2_level;
	u32 right_to_out1_level;
	u32 right_to_out2_level;
	u32 digital_level1;
	u32 digital_level2;
	u32 mute1;
	u32 mute2;
पूर्ण __attribute__((packed));

काष्ठा mixart_set_out_stream_level
अणु
	काष्ठा mixart_txx_stream_desc desc;
	काष्ठा mixart_out_stream_level_info out_level;
पूर्ण __attribute__((packed));

काष्ठा mixart_set_out_stream_level_req
अणु
	u32 delayed;
	u64 scheduler;
	u32 reserved4np[2];
	u32 nb_of_stream;  /* set to 1 */
	काष्ठा mixart_set_out_stream_level stream_level; /* could be an array */
पूर्ण __attribute__((packed));

/* response to this request is a u32 status value */


/* exported */
व्योम snd_mixart_init_mailbox(काष्ठा mixart_mgr *mgr);
व्योम snd_mixart_निकास_mailbox(काष्ठा mixart_mgr *mgr);

पूर्णांक  snd_mixart_send_msg(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *request, पूर्णांक max_resp_size, व्योम *resp_data);
पूर्णांक  snd_mixart_send_msg_रुको_notअगर(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *request, u32 notअगर_event);
पूर्णांक  snd_mixart_send_msg_nonblock(काष्ठा mixart_mgr *mgr, काष्ठा mixart_msg *request);

irqवापस_t snd_mixart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t snd_mixart_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id);

व्योम snd_mixart_reset_board(काष्ठा mixart_mgr *mgr);

#पूर्ण_अगर /* __SOUND_MIXART_CORE_H */
