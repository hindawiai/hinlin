<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __SST_MFLD_DSP_H__
#घोषणा __SST_MFLD_DSP_H__
/*
 *  sst_mfld_dsp.h - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@linux.पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#घोषणा SST_MAX_BIN_BYTES 1024

#घोषणा MAX_DBG_RW_BYTES 80
#घोषणा MAX_NUM_SCATTER_BUFFERS 8
#घोषणा MAX_LOOP_BACK_DWORDS 8
/* IPC base address and mailbox, बारtamp offsets */
#घोषणा SST_MAILBOX_SIZE 0x0400
#घोषणा SST_MAILBOX_SEND 0x0000
#घोषणा SST_TIME_STAMP 0x1800
#घोषणा SST_TIME_STAMP_MRFLD 0x800
#घोषणा SST_RESERVED_OFFSET 0x1A00
#घोषणा SST_SCU_LPE_MAILBOX 0x1000
#घोषणा SST_LPE_SCU_MAILBOX 0x1400
#घोषणा SST_SCU_LPE_LOG_BUF (SST_SCU_LPE_MAILBOX+16)
#घोषणा PROCESS_MSG 0x80

/* Message ID's क्रम IPC messages */
/* Bits B7: SST or IA/SC ; B6-B4: Msg Category; B3-B0: Msg Type */

/* I2L Firmware/Codec Download msgs */
#घोषणा IPC_IA_PREP_LIB_DNLD 0x01
#घोषणा IPC_IA_LIB_DNLD_CMPLT 0x02
#घोषणा IPC_IA_GET_FW_VERSION 0x04
#घोषणा IPC_IA_GET_FW_BUILD_INF 0x05
#घोषणा IPC_IA_GET_FW_INFO 0x06
#घोषणा IPC_IA_GET_FW_CTXT 0x07
#घोषणा IPC_IA_SET_FW_CTXT 0x08
#घोषणा IPC_IA_PREPARE_SHUTDOWN 0x31
/* I2L Codec Config/control msgs */
#घोषणा IPC_PREP_D3 0x10
#घोषणा IPC_IA_SET_CODEC_PARAMS 0x10
#घोषणा IPC_IA_GET_CODEC_PARAMS 0x11
#घोषणा IPC_IA_SET_PPP_PARAMS 0x12
#घोषणा IPC_IA_GET_PPP_PARAMS 0x13
#घोषणा IPC_SST_PERIOD_ELAPSED_MRFLD 0xA
#घोषणा IPC_IA_ALG_PARAMS 0x1A
#घोषणा IPC_IA_TUNING_PARAMS 0x1B
#घोषणा IPC_IA_SET_RUNTIME_PARAMS 0x1C
#घोषणा IPC_IA_SET_PARAMS 0x1
#घोषणा IPC_IA_GET_PARAMS 0x2

#घोषणा IPC_EFFECTS_CREATE 0xE
#घोषणा IPC_EFFECTS_DESTROY 0xF

/* I2L Stream config/control msgs */
#घोषणा IPC_IA_ALLOC_STREAM_MRFLD 0x2
#घोषणा IPC_IA_ALLOC_STREAM 0x20 /* Allocate a stream ID */
#घोषणा IPC_IA_FREE_STREAM_MRFLD 0x03
#घोषणा IPC_IA_FREE_STREAM 0x21 /* Free the stream ID */
#घोषणा IPC_IA_SET_STREAM_PARAMS 0x22
#घोषणा IPC_IA_SET_STREAM_PARAMS_MRFLD 0x12
#घोषणा IPC_IA_GET_STREAM_PARAMS 0x23
#घोषणा IPC_IA_PAUSE_STREAM 0x24
#घोषणा IPC_IA_PAUSE_STREAM_MRFLD 0x4
#घोषणा IPC_IA_RESUME_STREAM 0x25
#घोषणा IPC_IA_RESUME_STREAM_MRFLD 0x5
#घोषणा IPC_IA_DROP_STREAM 0x26
#घोषणा IPC_IA_DROP_STREAM_MRFLD 0x07
#घोषणा IPC_IA_DRAIN_STREAM 0x27 /* Short msg with str_id */
#घोषणा IPC_IA_DRAIN_STREAM_MRFLD 0x8
#घोषणा IPC_IA_CONTROL_ROUTING 0x29
#घोषणा IPC_IA_VTSV_UPDATE_MODULES 0x20
#घोषणा IPC_IA_VTSV_DETECTED 0x21

#घोषणा IPC_IA_START_STREAM_MRFLD 0X06
#घोषणा IPC_IA_START_STREAM 0x30 /* Short msg with str_id */

#घोषणा IPC_IA_SET_GAIN_MRFLD 0x21
/* Debug msgs */
#घोषणा IPC_IA_DBG_MEM_READ 0x40
#घोषणा IPC_IA_DBG_MEM_WRITE 0x41
#घोषणा IPC_IA_DBG_LOOP_BACK 0x42
#घोषणा IPC_IA_DBG_LOG_ENABLE 0x45
#घोषणा IPC_IA_DBG_SET_PROBE_PARAMS 0x47

/* L2I Firmware/Codec Download msgs */
#घोषणा IPC_IA_FW_INIT_CMPLT 0x81
#घोषणा IPC_IA_FW_INIT_CMPLT_MRFLD 0x01
#घोषणा IPC_IA_FW_ASYNC_ERR_MRFLD 0x11

/* L2I Codec Config/control msgs */
#घोषणा IPC_SST_FRAGMENT_ELPASED 0x90 /* Request IA more data */

#घोषणा IPC_SST_BUF_UNDER_RUN 0x92 /* PB Under run and stopped */
#घोषणा IPC_SST_BUF_OVER_RUN 0x93 /* CAP Under run and stopped */
#घोषणा IPC_SST_DRAIN_END 0x94 /* PB Drain complete and stopped */
#घोषणा IPC_SST_CHNGE_SSP_PARAMS 0x95 /* PB SSP parameters changed */
#घोषणा IPC_SST_STREAM_PROCESS_FATAL_ERR 0x96/* error in processing a stream */
#घोषणा IPC_SST_PERIOD_ELAPSED 0x97 /* period elapsed */

#घोषणा IPC_SST_ERROR_EVENT 0x99 /* Buffer over run occurred */
/* L2S messages */
#घोषणा IPC_SC_DDR_LINK_UP 0xC0
#घोषणा IPC_SC_DDR_LINK_DOWN 0xC1
#घोषणा IPC_SC_SET_LPECLK_REQ 0xC2
#घोषणा IPC_SC_SSP_BIT_BANG 0xC3

/* L2I Error reporting msgs */
#घोषणा IPC_IA_MEM_ALLOC_FAIL 0xE0
#घोषणा IPC_IA_PROC_ERR 0xE1 /* error in processing a
					stream can be used by playback and
					capture modules */

/* L2I Debug msgs */
#घोषणा IPC_IA_PRINT_STRING 0xF0

/* Buffer under-run */
#घोषणा IPC_IA_BUF_UNDER_RUN_MRFLD 0x0B

/* Mrfld specअगरic defines:
 * For asynchronous messages(INIT_CMPLT, PERIOD_ELAPSED, ASYNC_ERROR)
 * received from FW, the क्रमmat is:
 *  - IPC High: pvt_id is set to zero. Always लघु message.
 *  - msg_id is in lower 16-bits of IPC low payload.
 *  - pipe_id is in higher 16-bits of IPC low payload क्रम period_elapsed.
 *  - error id is in higher 16-bits of IPC low payload क्रम async errors.
 */
#घोषणा SST_ASYNC_DRV_ID 0

/* Command Response or Acknowledge message to any IPC message will have
 * same message ID and stream ID inक्रमmation which is sent.
 * There is no specअगरic Ack message ID. The data field is used as response
 * meaning.
 */
क्रमागत ackData अणु
	IPC_ACK_SUCCESS = 0,
	IPC_ACK_FAILURE,
पूर्ण;

क्रमागत ipc_ia_msg_id अणु
	IPC_CMD = 1,		/*!< Task Control message ID */
	IPC_SET_PARAMS = 2,/*!< Task Set param message ID */
	IPC_GET_PARAMS = 3,	/*!< Task Get param message ID */
	IPC_INVALID = 0xFF,	/*!<Task Get param message ID */
पूर्ण;

क्रमागत sst_codec_types अणु
	/*  AUDIO/MUSIC	CODEC Type Definitions */
	SST_CODEC_TYPE_UNKNOWN = 0,
	SST_CODEC_TYPE_PCM,	/* Pass through Audio codec */
	SST_CODEC_TYPE_MP3,
	SST_CODEC_TYPE_MP24,
	SST_CODEC_TYPE_AAC,
	SST_CODEC_TYPE_AACP,
	SST_CODEC_TYPE_eAACP,
पूर्ण;

क्रमागत stream_type अणु
	SST_STREAM_TYPE_NONE = 0,
	SST_STREAM_TYPE_MUSIC = 1,
पूर्ण;

क्रमागत sst_error_codes अणु
	/* Error code,response to msgId: Description */
	/* Common error codes */
	SST_SUCCESS = 0,        /* Success */
	SST_ERR_INVALID_STREAM_ID = 1,
	SST_ERR_INVALID_MSG_ID = 2,
	SST_ERR_INVALID_STREAM_OP = 3,
	SST_ERR_INVALID_PARAMS = 4,
	SST_ERR_INVALID_CODEC = 5,
	SST_ERR_INVALID_MEDIA_TYPE = 6,
	SST_ERR_STREAM_ERR = 7,

	SST_ERR_STREAM_IN_USE = 15,
पूर्ण;

काष्ठा ipc_dsp_hdr अणु
	u16 mod_index_id:8;		/*!< DSP Command ID specअगरic to tasks */
	u16 pipe_id:8;	/*!< instance of the module in the pipeline */
	u16 mod_id;		/*!< Pipe_id */
	u16 cmd_id;		/*!< Module ID = lpe_algo_types_t */
	u16 length;		/*!< Length of the payload only */
पूर्ण __packed;

जोड़ ipc_header_high अणु
	काष्ठा अणु
		u32  msg_id:8;	    /* Message ID - Max 256 Message Types */
		u32  task_id:4;	    /* Task ID associated with this comand */
		u32  drv_id:4;    /* Identअगरier क्रम the driver to track*/
		u32  rsvd1:8;	    /* Reserved */
		u32  result:4;	    /* Reserved */
		u32  res_rqd:1;	    /* Response rqd */
		u32  large:1;	    /* Large Message अगर large = 1 */
		u32  करोne:1;	    /* bit 30 - Done bit */
		u32  busy:1;	    /* bit 31 - busy bit*/
	पूर्ण part;
	u32 full;
पूर्ण __packed;
/* IPC header */
जोड़ ipc_header_mrfld अणु
	काष्ठा अणु
		u32 header_low_payload;
		जोड़ ipc_header_high header_high;
	पूर्ण p;
	u64 full;
पूर्ण __packed;
/* CAUTION NOTE: All IPC message body must be multiple of 32 bits.*/

/* IPC Header */
जोड़ ipc_header अणु
	काष्ठा अणु
		u32  msg_id:8; /* Message ID - Max 256 Message Types */
		u32  str_id:5;
		u32  large:1;	/* Large Message अगर large = 1 */
		u32  reserved:2;	/* Reserved क्रम future use */
		u32  data:14;	/* Ack/Info क्रम msg, size of msg in Mailbox */
		u32  करोne:1; /* bit 30 */
		u32  busy:1; /* bit 31 */
	पूर्ण part;
	u32 full;
पूर्ण __packed;

/* Firmware build info */
काष्ठा sst_fw_build_info अणु
	अचिन्हित अक्षर  date[16]; /* Firmware build date */
	अचिन्हित अक्षर  समय[16]; /* Firmware build समय */
पूर्ण __packed;

/* Firmware Version info */
काष्ठा snd_sst_fw_version अणु
	u8 build;	/* build number*/
	u8 minor;	/* minor number*/
	u8 major;	/* major number*/
	u8 type;	/* build type */
पूर्ण;

काष्ठा ipc_header_fw_init अणु
	काष्ठा snd_sst_fw_version fw_version;/* Firmware version details */
	काष्ठा sst_fw_build_info build_info;
	u16 result;	/* Fw init result */
	u8 module_id; /* Module ID in हाल of error */
	u8 debug_info; /* Debug info from Module ID in हाल of fail */
पूर्ण __packed;

काष्ठा snd_sst_tstamp अणु
	u64 ring_buffer_counter;	/* PB/CP: Bytes copied from/to DDR. */
	u64 hardware_counter;	    /* PB/CP: Bytes DMAed to/from SSP. */
	u64 frames_decoded;
	u64 bytes_decoded;
	u64 bytes_copied;
	u32 sampling_frequency;
	u32 channel_peak[8];
पूर्ण __packed;

/* Stream type params काष्ठाure क्रम Alloc stream */
काष्ठा snd_sst_str_type अणु
	u8 codec_type;		/* Codec type */
	u8 str_type;		/* 1 = voice 2 = music */
	u8 operation;		/* Playback or Capture */
	u8 रक्षित_str;	/* 0=Non DRM, 1=DRM */
	u8 समय_slots;
	u8 reserved;		/* Reserved */
	u16 result;		/* Result used क्रम acknowledgment */
पूर्ण __packed;

/* Library info काष्ठाure */
काष्ठा module_info अणु
	u32 lib_version;
	u32 lib_type;/*TBD- KLOCKWORK u8 lib_type;*/
	u32 media_type;
	u8  lib_name[12];
	u32 lib_caps;
	अचिन्हित अक्षर  b_date[16]; /* Lib build date */
	अचिन्हित अक्षर  b_समय[16]; /* Lib build समय */
पूर्ण __packed;

/* Library slot info */
काष्ठा lib_slot_info अणु
	u8  slot_num; /* 1 or 2 */
	u8  reserved1;
	u16 reserved2;
	u32 iram_size; /* slot size in IRAM */
	u32 dram_size; /* slot size in DRAM */
	u32 iram_offset; /* starting offset of slot in IRAM */
	u32 dram_offset; /* starting offset of slot in DRAM */
पूर्ण __packed;

काष्ठा snd_ppp_mixer_params अणु
	__u32			type; /*Type of the parameter */
	__u32			size;
	__u32			input_stream_biपंचांगap; /*Input stream Bit Map*/
पूर्ण __packed;

काष्ठा snd_sst_lib_करोwnload अणु
	काष्ठा module_info lib_info; /* library info type, capabilities etc */
	काष्ठा lib_slot_info slot_info; /* slot info to be करोwnloaded */
	u32 mod_entry_pt;
पूर्ण;

काष्ठा snd_sst_lib_करोwnload_info अणु
	काष्ठा snd_sst_lib_करोwnload dload_lib;
	u16 result;	/* Result used क्रम acknowledgment */
	u8 pvt_id; /* Private ID */
	u8 reserved;  /* क्रम alignment */
पूर्ण;
काष्ठा snd_pcm_params अणु
	u8 num_chan;	/* 1=Mono, 2=Stereo */
	u8 pcm_wd_sz;	/* 16/24 - bit*/
	u8 use_offload_path;	/* 0-PCM using period elpased & ALSA पूर्णांकerfaces
				   1-PCM stream via compressed पूर्णांकerface  */
	u8 reserved2;
	u32 sfreq;    /* Sampling rate in Hz */
	u8 channel_map[8];
पूर्ण __packed;

/* MP3 Music Parameters Message */
काष्ठा snd_mp3_params अणु
	u8  num_chan;	/* 1=Mono, 2=Stereo	*/
	u8  pcm_wd_sz; /* 16/24 - bit*/
	u8  crc_check; /* crc_check - disable (0) or enable (1) */
	u8  reserved1; /* unused*/
	u16 reserved2;	/* Unused */
पूर्ण __packed;

#घोषणा AAC_BIT_STREAM_ADTS		0
#घोषणा AAC_BIT_STREAM_ADIF		1
#घोषणा AAC_BIT_STREAM_RAW		2

/* AAC Music Parameters Message */
काष्ठा snd_aac_params अणु
	u8 num_chan; /* 1=Mono, 2=Stereo*/
	u8 pcm_wd_sz; /* 16/24 - bit*/
	u8 bकरोwnsample; /*SBR करोwnsampling 0 - disable 1 -enabled AAC+ only */
	u8 bs_क्रमmat; /* input bit stream क्रमmat adts=0, adअगर=1, raw=2 */
	u16  reser2;
	u32 बाह्यalsr; /*sampling rate of basic AAC raw bit stream*/
	u8 sbr_संकेतling;/*disable/enable/set स्वतःmode the SBR tool.AAC+*/
	u8 reser1;
	u16  reser3;
पूर्ण __packed;

/* WMA Music Parameters Message */
काष्ठा snd_wma_params अणु
	u8  num_chan;	/* 1=Mono, 2=Stereo */
	u8  pcm_wd_sz;	/* 16/24 - bit*/
	u16 reserved1;
	u32 brate;	/* Use the hard coded value. */
	u32 sfreq;	/* Sampling freq eg. 8000, 441000, 48000 */
	u32 channel_mask;  /* Channel Mask */
	u16 क्रमmat_tag;	/* Format Tag */
	u16 block_align;	/* packet size */
	u16 wma_encode_opt;/* Encoder option */
	u8 op_align;	/* op align 0- 16 bit, 1- MSB, 2 LSB */
	u8 reserved;	/* reserved */
पूर्ण __packed;

/* Codec params काष्ठाure */
जोड़  snd_sst_codec_params अणु
	काष्ठा snd_pcm_params pcm_params;
	काष्ठा snd_mp3_params mp3_params;
	काष्ठा snd_aac_params aac_params;
	काष्ठा snd_wma_params wma_params;
पूर्ण __packed;

/* Address and size info of a frame buffer */
काष्ठा sst_address_info अणु
	u32 addr; /* Address at IA */
	u32 size; /* Size of the buffer */
पूर्ण;

काष्ठा snd_sst_alloc_params_ext अणु
	__u16 sg_count;
	__u16 reserved;
	__u32 frag_size;	/*Number of samples after which period elapsed
				  message is sent valid only अगर path  = 0*/
	काष्ठा sst_address_info  ring_buf_info[8];
पूर्ण;

काष्ठा snd_sst_stream_params अणु
	जोड़ snd_sst_codec_params uc;
पूर्ण __packed;

काष्ठा snd_sst_params अणु
	u32 result;
	u32 stream_id;
	u8 codec;
	u8 ops;
	u8 stream_type;
	u8 device_type;
	u8 task;
	काष्ठा snd_sst_stream_params sparams;
	काष्ठा snd_sst_alloc_params_ext aparams;
पूर्ण;

काष्ठा snd_sst_alloc_mrfld अणु
	u16 codec_type;
	u8 operation;
	u8 sg_count;
	काष्ठा sst_address_info ring_buf_info[8];
	u32 frag_size;
	u32 ts;
	काष्ठा snd_sst_stream_params codec_params;
पूर्ण __packed;

/* Alloc stream params काष्ठाure */
काष्ठा snd_sst_alloc_params अणु
	काष्ठा snd_sst_str_type str_type;
	काष्ठा snd_sst_stream_params stream_params;
	काष्ठा snd_sst_alloc_params_ext alloc_params;
पूर्ण __packed;

/* Alloc stream response message */
काष्ठा snd_sst_alloc_response अणु
	काष्ठा snd_sst_str_type str_type; /* Stream type क्रम allocation */
	काष्ठा snd_sst_lib_करोwnload lib_dnld; /* Valid only क्रम codec dnld */
पूर्ण;

/* Drop response */
काष्ठा snd_sst_drop_response अणु
	u32 result;
	u32 bytes;
पूर्ण;

काष्ठा snd_sst_async_msg अणु
	u32 msg_id; /* Async msg id */
	u32 payload[0];
पूर्ण;

काष्ठा snd_sst_async_err_msg अणु
	u32 fw_resp; /* Firmware Result */
	u32 lib_resp; /*Library result */
पूर्ण __packed;

काष्ठा snd_sst_vol अणु
	u32	stream_id;
	s32	volume;
	u32	ramp_duration;
	u32	ramp_type;		/* Ramp type, शेष=0 */
पूर्ण;

/* Gain library parameters क्रम mrfld
 * based on DSP command spec v0.82
 */
काष्ठा snd_sst_gain_v2 अणु
	u16 gain_cell_num;  /* num of gain cells to modअगरy*/
	u8 cell_nbr_idx; /* instance index*/
	u8 cell_path_idx; /* pipe-id */
	u16 module_id; /*module id */
	u16 left_cell_gain; /* left gain value in dB*/
	u16 right_cell_gain; /* right gain value in dB*/
	u16 gain_समय_स्थिर; /* gain समय स्थिरant*/
पूर्ण __packed;

काष्ठा snd_sst_mute अणु
	u32	stream_id;
	u32	mute;
पूर्ण;

काष्ठा snd_sst_runसमय_params अणु
	u8 type;
	u8 str_id;
	u8 size;
	u8 rsvd;
	व्योम *addr;
पूर्ण __packed;

क्रमागत stream_param_type अणु
	SST_SET_TIME_SLOT = 0,
	SST_SET_CHANNEL_INFO = 1,
	OTHERS = 2, /*reserved क्रम future params*/
पूर्ण;

/* CSV Voice call routing काष्ठाure */
काष्ठा snd_sst_control_routing अणु
	u8 control; /* 0=start, 1=Stop */
	u8 reserved[3];	/* Reserved- क्रम 32 bit alignment */
पूर्ण;

काष्ठा ipc_post अणु
	काष्ठा list_head node;
	जोड़ ipc_header header; /* driver specअगरic */
	bool is_large;
	bool is_process_reply;
	जोड़ ipc_header_mrfld mrfld_header;
	अक्षर *mailbox_data;
पूर्ण;

काष्ठा snd_sst_ctxt_params अणु
	u32 address; /* Physical Address in DDR where the context is stored */
	u32 size; /* size of the context */
पूर्ण;

काष्ठा snd_sst_lpe_log_params अणु
	u8 dbg_type;
	u8 module_id;
	u8 log_level;
	u8 reserved;
पूर्ण __packed;

क्रमागत snd_sst_bytes_type अणु
	SND_SST_BYTES_SET = 0x1,
	SND_SST_BYTES_GET = 0x2,
पूर्ण;

काष्ठा snd_sst_bytes_v2 अणु
	u8 type;
	u8 ipc_msg;
	u8 block;
	u8 task_id;
	u8 pipe_id;
	u8 rsvd;
	u16 len;
	अक्षर bytes[0];
पूर्ण;

#घोषणा MAX_VTSV_खाताS 2
काष्ठा snd_sst_vtsv_info अणु
	काष्ठा sst_address_info vfiles[MAX_VTSV_खाताS];
पूर्ण __packed;

#पूर्ण_अगर /* __SST_MFLD_DSP_H__ */
