<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram VX soundcards
 *
 * Definitions of DSP commands
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __VX_CMD_H
#घोषणा __VX_CMD_H

क्रमागत अणु
	CMD_VERSION,
	CMD_SUPPORTED,
	CMD_TEST_IT,
	CMD_SEND_IRQA,
	CMD_IBL,
	CMD_ASYNC,
	CMD_RES_PIPE,
	CMD_FREE_PIPE,
	CMD_CONF_PIPE,
	CMD_ABORT_CONF_PIPE,
	CMD_PARAM_OUTPUT_PIPE,
	CMD_STOP_PIPE,
	CMD_PIPE_STATE,
	CMD_PIPE_SPL_COUNT,
	CMD_CAN_START_PIPE,
	CMD_SIZE_HBUFFER,
	CMD_START_STREAM,
	CMD_START_ONE_STREAM,
	CMD_PAUSE_STREAM,
	CMD_PAUSE_ONE_STREAM,
	CMD_STREAM_OUT_LEVEL_ADJUST,
	CMD_STOP_STREAM,
	CMD_FORMAT_STREAM_OUT,
	CMD_FORMAT_STREAM_IN,
	CMD_GET_STREAM_STATE,
	CMD_DROP_BYTES_AWAY,
	CMD_GET_REMAINING_BYTES,
	CMD_CONNECT_AUDIO,
	CMD_AUDIO_LEVEL_ADJUST,
	CMD_AUDIO_VU_PIC_METER,
	CMD_GET_AUDIO_LEVELS,
	CMD_GET_NOTIFY_EVENT,
	CMD_INFO_NOTIFIED,
	CMD_ACCESS_IO_FCT,
	CMD_STATUS_R_BUFFERS,
	CMD_UPDATE_R_BUFFERS,
	CMD_LOAD_EFFECT_CONTEXT,
	CMD_EFFECT_ONE_PIPE,
	CMD_MODIFY_CLOCK,
	CMD_STREAM1_OUT_SET_N_LEVELS,
	CMD_PURGE_STREAM_DCMDS,
	CMD_NOTIFY_PIPE_TIME,
	CMD_LOAD_EFFECT_CONTEXT_PACKET,
	CMD_RELIC_R_BUFFER,
	CMD_RESYNC_AUDIO_INPUTS,
	CMD_NOTIFY_STREAM_TIME,
	CMD_STREAM_SAMPLE_COUNT,
	CMD_CONFIG_TIME_CODE,
	CMD_GET_TIME_CODE,
	CMD_MANAGE_SIGNAL,
	CMD_PARAMETER_STREAM_OUT,
	CMD_READ_BOARD_FREQ,
	CMD_GET_STREAM_LEVELS,
	CMD_PURGE_PIPE_DCMDS,
	// CMD_SET_STREAM_OUT_EFFECTS,
	// CMD_GET_STREAM_OUT_EFFECTS,
	CMD_CONNECT_MONITORING,
	CMD_STREAM2_OUT_SET_N_LEVELS,
	CMD_CANCEL_R_BUFFERS,
	CMD_NOTIFY_END_OF_BUFFER,
	CMD_GET_STREAM_VU_METER,
	CMD_LAST_INDEX
पूर्ण;

काष्ठा vx_cmd_info अणु
	अचिन्हित पूर्णांक opcode;	/* command word */
	पूर्णांक length;		/* command length (in words) */
	पूर्णांक st_type;		/* status type (RMH_SSIZE_XXX) */
	पूर्णांक st_length;		/* fixed length */
पूर्ण;

/* Family and code op of some DSP requests. */
#घोषणा CODE_OP_PIPE_TIME                       0x004e0000
#घोषणा CODE_OP_START_STREAM                    0x00800000
#घोषणा CODE_OP_PAUSE_STREAM                    0x00810000
#घोषणा CODE_OP_OUT_STREAM_LEVEL                0x00820000
#घोषणा CODE_OP_UPDATE_R_BUFFERS                0x00840000
#घोषणा CODE_OP_OUT_STREAM1_LEVEL_CURVE         0x00850000
#घोषणा CODE_OP_OUT_STREAM2_LEVEL_CURVE         0x00930000
#घोषणा CODE_OP_OUT_STREAM_FORMAT               0x00860000
#घोषणा CODE_OP_STREAM_TIME                     0x008f0000
#घोषणा CODE_OP_OUT_STREAM_EXTRAPARAMETER       0x00910000
#घोषणा CODE_OP_OUT_AUDIO_LEVEL                 0x00c20000

#घोषणा NOTIFY_LAST_COMMAND     0x00400000

/* Values क्रम a user delay */
#घोषणा DC_DIFFERED_DELAY       (1<<BIT_DIFFERED_COMMAND)
#घोषणा DC_NOTIFY_DELAY         (1<<BIT_NOTIFIED_COMMAND)
#घोषणा DC_HBUFFER_DELAY        (1<<BIT_TIME_RELATIVE_TO_BUFFER)
#घोषणा DC_MULTIPLE_DELAY       (1<<BIT_RESERVED)
#घोषणा DC_STREAM_TIME_DELAY    (1<<BIT_STREAM_TIME)
#घोषणा DC_CANCELLED_DELAY      (1<<BIT_CANCELLED_COMMAND)

/* Values क्रम tiDelayed field in TIME_INFO काष्ठाure,
 * and क्रम pbPause field in PLAY_BUFFER_INFO काष्ठाure
 */
#घोषणा BIT_DIFFERED_COMMAND                0
#घोषणा BIT_NOTIFIED_COMMAND                1
#घोषणा BIT_TIME_RELATIVE_TO_BUFFER         2
#घोषणा BIT_RESERVED                        3
#घोषणा BIT_STREAM_TIME                     4
#घोषणा BIT_CANCELLED_COMMAND               5

/* Access to the "Size" field of the response of the CMD_GET_NOTIFY_EVENT request. */
#घोषणा GET_NOTIFY_EVENT_SIZE_FIELD_MASK    0x000000ff

/* DSP commands general masks */
#घोषणा OPCODE_MASK                 0x00ff0000
#घोषणा DSP_DIFFERED_COMMAND_MASK   0x0000C000

/* Notअगरications (NOTIFY_INFO) */
#घोषणा ALL_CMDS_NOTIFIED                   0x0000  // reserved
#घोषणा START_STREAM_NOTIFIED               0x0001
#घोषणा PAUSE_STREAM_NOTIFIED               0x0002
#घोषणा OUT_STREAM_LEVEL_NOTIFIED           0x0003
#घोषणा OUT_STREAM_PARAMETER_NOTIFIED       0x0004  // left क्रम backward compatibility
#घोषणा OUT_STREAM_FORMAT_NOTIFIED          0x0004
#घोषणा PIPE_TIME_NOTIFIED                  0x0005
#घोषणा OUT_AUDIO_LEVEL_NOTIFIED            0x0006
#घोषणा OUT_STREAM_LEVEL_CURVE_NOTIFIED     0x0007
#घोषणा STREAM_TIME_NOTIFIED                0x0008
#घोषणा OUT_STREAM_EXTRAPARAMETER_NOTIFIED  0x0009
#घोषणा UNKNOWN_COMMAND_NOTIFIED            0xffff

/* Output pipe parameters setting */
#घोषणा MASK_VALID_PIPE_MPEG_PARAM      0x000040
#घोषणा MASK_VALID_PIPE_BACKWARD_PARAM  0x000020
#घोषणा MASK_SET_PIPE_MPEG_PARAM        0x000002
#घोषणा MASK_SET_PIPE_BACKWARD_PARAM    0x000001

#घोषणा MASK_DSP_WORD           0x00FFFFFF
#घोषणा MASK_ALL_STREAM         0x00FFFFFF
#घोषणा MASK_DSP_WORD_LEVEL     0x000001FF
#घोषणा MASK_FIRST_FIELD        0x0000001F
#घोषणा FIELD_SIZE              5

#घोषणा COMMAND_RECORD_MASK     0x000800

/* PipeManagement definition bits (PIPE_DECL_INFO) */
#घोषणा P_UNDERRUN_SKIP_SOUND_MASK				0x01
#घोषणा P_PREPARE_FOR_MPEG3_MASK				0x02
#घोषणा P_DO_NOT_RESET_ANALOG_LEVELS			0x04
#घोषणा P_ALLOW_UNDER_ALLOCATION_MASK			0x08
#घोषणा P_DATA_MODE_MASK				0x10
#घोषणा P_ASIO_BUFFER_MANAGEMENT_MASK			0x20

#घोषणा BIT_SKIP_SOUND					0x08	// bit 3
#घोषणा BIT_DATA_MODE					0x10	// bit 4
    
/* Bits in the CMD_MODIFY_CLOCK request. */
#घोषणा CMD_MODIFY_CLOCK_FD_BIT     0x00000001
#घोषणा CMD_MODIFY_CLOCK_T_BIT      0x00000002
#घोषणा CMD_MODIFY_CLOCK_S_BIT      0x00000004

/* Access to the results of the CMD_GET_TIME_CODE RMH. */
#घोषणा TIME_CODE_V_MASK            0x00800000
#घोषणा TIME_CODE_N_MASK            0x00400000
#घोषणा TIME_CODE_B_MASK            0x00200000
#घोषणा TIME_CODE_W_MASK            0x00100000

/* Values क्रम the CMD_MANAGE_SIGNAL RMH. */
#घोषणा MANAGE_SIGNAL_TIME_CODE     0x01
#घोषणा MANAGE_SIGNAL_MIDI          0x02

/* Values क्रम the CMD_CONFIG_TIME_CODE RMH. */
#घोषणा CONFIG_TIME_CODE_CANCEL     0x00001000
    
/* Mask to get only the effective समय from the
 * high word out of the 2 वापसed by the DSP
 */
#घोषणा PCX_TIME_HI_MASK        0x000fffff

/* Values क्रम setting a H-Buffer समय */
#घोषणा HBUFFER_TIME_HIGH       0x00200000
#घोषणा HBUFFER_TIME_LOW        0x00000000

#घोषणा NOTIFY_MASK_TIME_HIGH   0x00400000
#घोषणा MULTIPLE_MASK_TIME_HIGH 0x00100000
#घोषणा STREAM_MASK_TIME_HIGH   0x00800000


/*
 *
 */
व्योम vx_init_rmh(काष्ठा vx_rmh *rmh, अचिन्हित पूर्णांक cmd);

/**
 * vx_send_pipe_cmd_params - fill first command word क्रम pipe commands
 * @rmh: the rmh to be modअगरied
 * @is_capture: 0 = playback, 1 = capture operation
 * @param1: first pipe-parameter
 * @param2: second pipe-parameter
 */
अटल अंतरभूत व्योम vx_set_pipe_cmd_params(काष्ठा vx_rmh *rmh, पूर्णांक is_capture,
					  पूर्णांक param1, पूर्णांक param2)
अणु
	अगर (is_capture)
		rmh->Cmd[0] |= COMMAND_RECORD_MASK;
	rmh->Cmd[0] |= (((u32)param1 & MASK_FIRST_FIELD) << FIELD_SIZE) & MASK_DSP_WORD;
		
	अगर (param2)
		rmh->Cmd[0] |= ((u32)param2 & MASK_FIRST_FIELD) & MASK_DSP_WORD;
	
पूर्ण

/**
 * vx_set_stream_cmd_params - fill first command word क्रम stream commands
 * @rmh: the rmh to be modअगरied
 * @is_capture: 0 = playback, 1 = capture operation
 * @pipe: the pipe index (zero-based)
 */
अटल अंतरभूत व्योम vx_set_stream_cmd_params(काष्ठा vx_rmh *rmh, पूर्णांक is_capture, पूर्णांक pipe)
अणु
	अगर (is_capture)
		rmh->Cmd[0] |= COMMAND_RECORD_MASK;
	rmh->Cmd[0] |= (((u32)pipe & MASK_FIRST_FIELD) << FIELD_SIZE) & MASK_DSP_WORD;
पूर्ण

#पूर्ण_अगर /* __VX_CMD_H */
