<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2020 Intel Corporation. All rights reserved.
 *
 * Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
 */

#अगर_अघोषित __SND_SOC_INTEL_CATPT_MSG_H
#घोषणा __SND_SOC_INTEL_CATPT_MSG_H

काष्ठा catpt_dev;

/* IPC messages base types  */

क्रमागत catpt_reply_status अणु
	CATPT_REPLY_SUCCESS = 0,
	CATPT_REPLY_ERROR_INVALID_PARAM = 1,
	CATPT_REPLY_UNKNOWN_MESSAGE_TYPE = 2,
	CATPT_REPLY_OUT_OF_RESOURCES = 3,
	CATPT_REPLY_BUSY = 4,
	CATPT_REPLY_PENDING = 5,
	CATPT_REPLY_FAILURE = 6,
	CATPT_REPLY_INVALID_REQUEST = 7,
	CATPT_REPLY_UNINITIALIZED = 8,
	CATPT_REPLY_NOT_FOUND = 9,
	CATPT_REPLY_SOURCE_NOT_STARTED = 10,
पूर्ण;

/* GLOBAL messages */

क्रमागत catpt_global_msg_type अणु
	CATPT_GLB_GET_FW_VERSION = 0,
	CATPT_GLB_ALLOCATE_STREAM = 3,
	CATPT_GLB_FREE_STREAM = 4,
	CATPT_GLB_STREAM_MESSAGE = 6,
	CATPT_GLB_REQUEST_CORE_DUMP = 7,
	CATPT_GLB_SET_DEVICE_FORMATS = 10,
	CATPT_GLB_ENTER_DX_STATE = 12,
	CATPT_GLB_GET_MIXER_STREAM_INFO = 13,
पूर्ण;

जोड़ catpt_global_msg अणु
	u32 val;
	काष्ठा अणु
		u32 status:5;
		u32 context:19; /* stream or module specअगरic */
		u32 global_msg_type:5;
		u32 fw_पढ़ोy:1;
		u32 करोne:1;
		u32 busy:1;
	पूर्ण;
पूर्ण __packed;

#घोषणा CATPT_MSG(hdr) अणु .val = hdr पूर्ण
#घोषणा CATPT_GLOBAL_MSG(msg_type) \
	अणु .global_msg_type = CATPT_GLB_##msg_type पूर्ण

#घोषणा BUILD_HASH_SIZE		40

काष्ठा catpt_fw_version अणु
	u8 build;
	u8 minor;
	u8 major;
	u8 type;
	u8 build_hash[BUILD_HASH_SIZE];
	u32 log_providers_hash;
पूर्ण __packed;

पूर्णांक catpt_ipc_get_fw_version(काष्ठा catpt_dev *cdev,
			     काष्ठा catpt_fw_version *version);

क्रमागत catpt_pin_id अणु
	CATPT_PIN_ID_SYSTEM = 0,
	CATPT_PIN_ID_REFERENCE = 1,
	CATPT_PIN_ID_CAPTURE1 = 2,
	CATPT_PIN_ID_CAPTURE2 = 3,
	CATPT_PIN_ID_OFFLOAD1 = 4,
	CATPT_PIN_ID_OFFLOAD2 = 5,
	CATPT_PIN_ID_MIXER = 7,
	CATPT_PIN_ID_BLUETOOTH_CAPTURE = 8,
	CATPT_PIN_ID_BLUETOOTH_RENDER = 9,
पूर्ण;

क्रमागत catpt_path_id अणु
	CATPT_PATH_SSP0_OUT = 0,
	CATPT_PATH_SSP0_IN = 1,
	CATPT_PATH_SSP1_OUT = 2,
	CATPT_PATH_SSP1_IN = 3,
	/* duplicated audio in capture path */
	CATPT_PATH_SSP0_IN_DUP = 4,
पूर्ण;

क्रमागत catpt_stream_type अणु
	CATPT_STRM_TYPE_RENDER = 0, /* offload */
	CATPT_STRM_TYPE_SYSTEM = 1,
	CATPT_STRM_TYPE_CAPTURE = 2,
	CATPT_STRM_TYPE_LOOPBACK = 3,
	CATPT_STRM_TYPE_BLUETOOTH_RENDER = 4,
	CATPT_STRM_TYPE_BLUETOOTH_CAPTURE = 5,
पूर्ण;

क्रमागत catpt_क्रमmat_id अणु
	CATPT_FORMAT_PCM = 0,
	CATPT_FORMAT_MP3 = 1,
	CATPT_FORMAT_AAC = 2,
	CATPT_FORMAT_WMA = 3,
पूर्ण;

क्रमागत catpt_channel_index अणु
	CATPT_CHANNEL_LEFT = 0x0,
	CATPT_CHANNEL_CENTER = 0x1,
	CATPT_CHANNEL_RIGHT = 0x2,
	CATPT_CHANNEL_LEFT_SURROUND = 0x3,
	CATPT_CHANNEL_CENTER_SURROUND = 0x3,
	CATPT_CHANNEL_RIGHT_SURROUND = 0x4,
	CATPT_CHANNEL_LFE = 0x7,
	CATPT_CHANNEL_INVALID = 0xF,
पूर्ण;

क्रमागत catpt_channel_config अणु
	CATPT_CHANNEL_CONFIG_MONO	= 0, /* One channel only */
	CATPT_CHANNEL_CONFIG_STEREO	= 1, /* L & R */
	CATPT_CHANNEL_CONFIG_2_POINT_1	= 2, /* L, R & LFE; PCM only */
	CATPT_CHANNEL_CONFIG_3_POINT_0	= 3, /* L, C & R; MP3 & AAC only */
	CATPT_CHANNEL_CONFIG_3_POINT_1	= 4, /* L, C, R & LFE; PCM only */
	CATPT_CHANNEL_CONFIG_QUATRO	= 5, /* L, R, Ls & Rs; PCM only */
	CATPT_CHANNEL_CONFIG_4_POINT_0	= 6, /* L, C, R & Cs; MP3 & AAC only */
	CATPT_CHANNEL_CONFIG_5_POINT_0	= 7, /* L, C, R, Ls & Rs */
	CATPT_CHANNEL_CONFIG_5_POINT_1	= 8, /* L, C, R, Ls, Rs & LFE */
	CATPT_CHANNEL_CONFIG_DUAL_MONO	= 9, /* One channel replicated in two */
	CATPT_CHANNEL_CONFIG_INVALID	= 10,
पूर्ण;

क्रमागत catpt_पूर्णांकerleaving_style अणु
	CATPT_INTERLEAVING_PER_CHANNEL	= 0,
	CATPT_INTERLEAVING_PER_SAMPLE	= 1,
पूर्ण;

काष्ठा catpt_audio_क्रमmat अणु
	u32 sample_rate;
	u32 bit_depth;
	u32 channel_map;
	u32 channel_config;
	u32 पूर्णांकerleaving;
	u8 num_channels;
	u8 valid_bit_depth;
	u8 reserved[2];
पूर्ण __packed;

काष्ठा catpt_ring_info अणु
	u32 page_table_addr;
	u32 num_pages;
	u32 size;
	u32 offset;
	u32 ring_first_page_pfn;
पूर्ण __packed;

#घोषणा CATPT_MODULE_COUNT (CATPT_MODID_LAST + 1)

क्रमागत catpt_module_id अणु
	CATPT_MODID_BASE_FW		= 0x0,
	CATPT_MODID_MP3			= 0x1,
	CATPT_MODID_AAC_5_1		= 0x2,
	CATPT_MODID_AAC_2_0		= 0x3,
	CATPT_MODID_SRC			= 0x4,
	CATPT_MODID_WAVES		= 0x5,
	CATPT_MODID_DOLBY		= 0x6,
	CATPT_MODID_BOOST		= 0x7,
	CATPT_MODID_LPAL		= 0x8,
	CATPT_MODID_DTS			= 0x9,
	CATPT_MODID_PCM_CAPTURE		= 0xA,
	CATPT_MODID_PCM_SYSTEM		= 0xB,
	CATPT_MODID_PCM_REFERENCE	= 0xC,
	CATPT_MODID_PCM			= 0xD, /* offload */
	CATPT_MODID_BLUETOOTH_RENDER	= 0xE,
	CATPT_MODID_BLUETOOTH_CAPTURE	= 0xF,
	CATPT_MODID_LAST		= CATPT_MODID_BLUETOOTH_CAPTURE,
पूर्ण;

काष्ठा catpt_module_entry अणु
	u32 module_id;
	u32 entry_poपूर्णांक;
पूर्ण __packed;

काष्ठा catpt_module_map अणु
	u8 num_entries;
	काष्ठा catpt_module_entry entries[];
पूर्ण __packed;

काष्ठा catpt_memory_info अणु
	u32 offset;
	u32 size;
पूर्ण __packed;

#घोषणा CATPT_CHANNELS_MAX	4
#घोषणा CATPT_ALL_CHANNELS_MASK	अच_पूर्णांक_उच्च

काष्ठा catpt_stream_info अणु
	u32 stream_hw_id;
	u32 reserved;
	u32 पढ़ो_pos_regaddr;
	u32 pres_pos_regaddr;
	u32 peak_meter_regaddr[CATPT_CHANNELS_MAX];
	u32 volume_regaddr[CATPT_CHANNELS_MAX];
पूर्ण __packed;

पूर्णांक catpt_ipc_alloc_stream(काष्ठा catpt_dev *cdev,
			   क्रमागत catpt_path_id path_id,
			   क्रमागत catpt_stream_type type,
			   काष्ठा catpt_audio_क्रमmat *afmt,
			   काष्ठा catpt_ring_info *rinfo,
			   u8 num_modules,
			   काष्ठा catpt_module_entry *modules,
			   काष्ठा resource *persistent,
			   काष्ठा resource *scratch,
			   काष्ठा catpt_stream_info *sinfo);
पूर्णांक catpt_ipc_मुक्त_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id);

क्रमागत catpt_ssp_अगरace अणु
	CATPT_SSP_IFACE_0 = 0,
	CATPT_SSP_IFACE_1 = 1,
	CATPT_SSP_IFACE_LAST = CATPT_SSP_IFACE_1,
पूर्ण;

#घोषणा CATPT_SSP_COUNT (CATPT_SSP_IFACE_LAST + 1)

क्रमागत catpt_mclk_frequency अणु
	CATPT_MCLK_OFF = 0,
	CATPT_MCLK_FREQ_6_MHZ = 1,
	CATPT_MCLK_FREQ_21_MHZ = 2,
	CATPT_MCLK_FREQ_24_MHZ = 3,
पूर्ण;

क्रमागत catpt_ssp_mode अणु
	CATPT_SSP_MODE_I2S_CONSUMER = 0,
	CATPT_SSP_MODE_I2S_PROVIDER = 1,
	CATPT_SSP_MODE_TDM_PROVIDER = 2,
पूर्ण;

काष्ठा catpt_ssp_device_क्रमmat अणु
	u32 अगरace;
	u32 mclk;
	u32 mode;
	u16 घड़ी_भागider;
	u8 channels;
पूर्ण __packed;

पूर्णांक catpt_ipc_set_device_क्रमmat(काष्ठा catpt_dev *cdev,
				काष्ठा catpt_ssp_device_क्रमmat *devfmt);

क्रमागत catpt_dx_state अणु
	CATPT_DX_STATE_D3 = 3,
पूर्ण;

क्रमागत catpt_dx_type अणु
	CATPT_DX_TYPE_FW_IMAGE = 0,
	CATPT_DX_TYPE_MEMORY_DUMP = 1,
पूर्ण;

काष्ठा catpt_save_meminfo अणु
	u32 offset;
	u32 size;
	u32 source;
पूर्ण __packed;

#घोषणा SAVE_MEMINFO_MAX	14

काष्ठा catpt_dx_context अणु
	u32 num_meminfo;
	काष्ठा catpt_save_meminfo meminfo[SAVE_MEMINFO_MAX];
पूर्ण __packed;

पूर्णांक catpt_ipc_enter_dxstate(काष्ठा catpt_dev *cdev, क्रमागत catpt_dx_state state,
			    काष्ठा catpt_dx_context *context);

काष्ठा catpt_mixer_stream_info अणु
	u32 mixer_hw_id;
	u32 peak_meter_regaddr[CATPT_CHANNELS_MAX];
	u32 volume_regaddr[CATPT_CHANNELS_MAX];
पूर्ण __packed;

पूर्णांक catpt_ipc_get_mixer_stream_info(काष्ठा catpt_dev *cdev,
				    काष्ठा catpt_mixer_stream_info *info);

/* STREAM messages */

क्रमागत catpt_stream_msg_type अणु
	CATPT_STRM_RESET_STREAM = 0,
	CATPT_STRM_PAUSE_STREAM = 1,
	CATPT_STRM_RESUME_STREAM = 2,
	CATPT_STRM_STAGE_MESSAGE = 3,
	CATPT_STRM_NOTIFICATION = 4,
पूर्ण;

क्रमागत catpt_stage_action अणु
	CATPT_STG_SET_VOLUME = 1,
	CATPT_STG_SET_WRITE_POSITION = 2,
	CATPT_STG_MUTE_LOOPBACK = 3,
पूर्ण;

जोड़ catpt_stream_msg अणु
	u32 val;
	काष्ठा अणु
		u32 status:5;
		u32 reserved:7;
		u32 stage_action:4;
		u32 stream_hw_id:4;
		u32 stream_msg_type:4;
		u32 global_msg_type:5;
		u32 fw_पढ़ोy:1;
		u32 करोne:1;
		u32 busy:1;
	पूर्ण;
पूर्ण __packed;

#घोषणा CATPT_STREAM_MSG(msg_type) \
अणु \
	.stream_msg_type = CATPT_STRM_##msg_type, \
	.global_msg_type = CATPT_GLB_STREAM_MESSAGE पूर्ण
#घोषणा CATPT_STAGE_MSG(msg_type) \
अणु \
	.stage_action = CATPT_STG_##msg_type, \
	.stream_msg_type = CATPT_STRM_STAGE_MESSAGE, \
	.global_msg_type = CATPT_GLB_STREAM_MESSAGE पूर्ण

पूर्णांक catpt_ipc_reset_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id);
पूर्णांक catpt_ipc_छोड़ो_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id);
पूर्णांक catpt_ipc_resume_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id);

/* STREAM messages - STAGE subtype */

क्रमागत catpt_audio_curve_type अणु
	CATPT_AUDIO_CURVE_NONE = 0,
	CATPT_AUDIO_CURVE_WINDOWS_FADE = 1,
पूर्ण;

पूर्णांक catpt_ipc_set_volume(काष्ठा catpt_dev *cdev, u8 stream_hw_id,
			 u32 channel, u32 volume,
			 u32 curve_duration,
			 क्रमागत catpt_audio_curve_type curve_type);

पूर्णांक catpt_ipc_set_ग_लिखो_pos(काष्ठा catpt_dev *cdev, u8 stream_hw_id,
			    u32 pos, bool eob, bool ll);

पूर्णांक catpt_ipc_mute_loopback(काष्ठा catpt_dev *cdev, u8 stream_hw_id, bool mute);

/* NOTIFICATION messages */

क्रमागत catpt_notअगरy_reason अणु
	CATPT_NOTIFY_POSITION_CHANGED = 0,
	CATPT_NOTIFY_GLITCH_OCCURRED = 1,
पूर्ण;

जोड़ catpt_notअगरy_msg अणु
	u32 val;
	काष्ठा अणु
		u32 mailbox_address:29;
		u32 fw_पढ़ोy:1;
		u32 करोne:1;
		u32 busy:1;
	पूर्ण;
	काष्ठा अणु
		u32 status:5;
		u32 reserved:7;
		u32 notअगरy_reason:4;
		u32 stream_hw_id:4;
		u32 stream_msg_type:4;
		u32 global_msg_type:5;
		u32 hdr:3; /* fw_पढ़ोy, करोne, busy */
	पूर्ण;
पूर्ण __packed;

#घोषणा FW_INFO_SIZE_MAX	100

काष्ठा catpt_fw_पढ़ोy अणु
	u32 inbox_offset;
	u32 outbox_offset;
	u32 inbox_size;
	u32 outbox_size;
	u32 fw_info_size;
	अक्षर fw_info[FW_INFO_SIZE_MAX];
पूर्ण __packed;

काष्ठा catpt_notअगरy_position अणु
	u32 stream_position;
	u32 fw_cycle_count;
पूर्ण __packed;

क्रमागत catpt_glitch_type अणु
	CATPT_GLITCH_UNDERRUN = 1,
	CATPT_GLITCH_DECODER_ERROR = 2,
	CATPT_GLITCH_DOUBLED_WRITE_POS = 3,
पूर्ण;

काष्ठा catpt_notअगरy_glitch अणु
	u32 type;
	u64 presentation_pos;
	u32 ग_लिखो_pos;
पूर्ण __packed;

#पूर्ण_अगर
