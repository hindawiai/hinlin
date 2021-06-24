<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * DSP commands
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/vx_core.h>
#समावेश "vx_cmd.h"

/*
 * Array of DSP commands
 */
अटल स्थिर काष्ठा vx_cmd_info vx_dsp_cmds[] = अणु
[CMD_VERSION] =			अणु 0x010000, 2, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_SUPPORTED] =		अणु 0x020000, 1, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_TEST_IT] =			अणु 0x040000, 1, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_SEND_IRQA] =		अणु 0x070001, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_IBL] =			अणु 0x080000, 1, RMH_SSIZE_FIXED, 4 पूर्ण,
[CMD_ASYNC] =			अणु 0x0A0000, 1, RMH_SSIZE_ARG, 0 पूर्ण,
[CMD_RES_PIPE] =		अणु 0x400000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_FREE_PIPE] =		अणु 0x410000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_CONF_PIPE] =		अणु 0x42A101, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_ABORT_CONF_PIPE] =		अणु 0x42A100, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PARAM_OUTPUT_PIPE] =	अणु 0x43A000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STOP_PIPE] =		अणु 0x470004, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PIPE_STATE] =		अणु 0x480000, 1, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_PIPE_SPL_COUNT] =		अणु 0x49A000, 2, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_CAN_START_PIPE] =		अणु 0x4b0000, 1, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_SIZE_HBUFFER] =		अणु 0x4C0000, 1, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_START_STREAM] =		अणु 0x80A000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_START_ONE_STREAM] =	अणु 0x800000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PAUSE_STREAM] =		अणु 0x81A000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PAUSE_ONE_STREAM] =	अणु 0x810000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STREAM_OUT_LEVEL_ADJUST] =	अणु 0x828000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STOP_STREAM] =		अणु 0x830000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_FORMAT_STREAM_OUT] =	अणु 0x868000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_FORMAT_STREAM_IN] =	अणु 0x878800, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_GET_STREAM_STATE] =	अणु 0x890001, 2, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_DROP_BYTES_AWAY] =		अणु 0x8A8000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_GET_REMAINING_BYTES] =	अणु 0x8D0800, 1, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_CONNECT_AUDIO] =		अणु 0xC10000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_AUDIO_LEVEL_ADJUST] =	अणु 0xC2A000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_AUDIO_VU_PIC_METER] =	अणु 0xC3A003, 2, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_GET_AUDIO_LEVELS] =	अणु 0xC4A000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_GET_NOTIFY_EVENT] =	अणु 0x4D0000, 1, RMH_SSIZE_ARG, 0 पूर्ण,
[CMD_INFO_NOTIFIED] =		अणु 0x0B0000, 1, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_ACCESS_IO_FCT] =		अणु 0x098000, 1, RMH_SSIZE_ARG, 0 पूर्ण,
[CMD_STATUS_R_BUFFERS] =	अणु 0x440000, 1, RMH_SSIZE_ARG, 0 पूर्ण,
[CMD_UPDATE_R_BUFFERS] =	अणु 0x848000, 4, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_LOAD_EFFECT_CONTEXT] =	अणु 0x0c8000, 3, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_EFFECT_ONE_PIPE] =		अणु 0x458000, 0, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_MODIFY_CLOCK] =		अणु 0x0d0000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STREAM1_OUT_SET_N_LEVELS] =अणु 0x858000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PURGE_STREAM_DCMDS] =	अणु 0x8b8000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_NOTIFY_PIPE_TIME] =	अणु 0x4e0000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_LOAD_EFFECT_CONTEXT_PACKET] = अणु 0x0c8000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_RELIC_R_BUFFER] =		अणु 0x8e0800, 1, RMH_SSIZE_FIXED, 1 पूर्ण,
[CMD_RESYNC_AUDIO_INPUTS] =	अणु 0x0e0000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_NOTIFY_STREAM_TIME] =	अणु 0x8f0000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STREAM_SAMPLE_COUNT] =	अणु 0x900000, 1, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_CONFIG_TIME_CODE] =	अणु 0x050000, 2, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_GET_TIME_CODE] =		अणु 0x060000, 1, RMH_SSIZE_FIXED, 5 पूर्ण,
[CMD_MANAGE_SIGNAL] =		अणु 0x0f0000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_PARAMETER_STREAM_OUT] =	अणु 0x91A000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_READ_BOARD_FREQ] =		अणु 0x030000, 1, RMH_SSIZE_FIXED, 2 पूर्ण,
[CMD_GET_STREAM_LEVELS] =	अणु 0x8c0000, 1, RMH_SSIZE_FIXED, 3 पूर्ण,
[CMD_PURGE_PIPE_DCMDS] =	अणु 0x4f8000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
// [CMD_SET_STREAM_OUT_EFFECTS] =	अणु 0x888000, 34, RMH_SSIZE_FIXED, 0 पूर्ण,
// [CMD_GET_STREAM_OUT_EFFECTS] =	अणु 0x928000, 2, RMH_SSIZE_FIXED, 32 पूर्ण,
[CMD_CONNECT_MONITORING] =	अणु 0xC00000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_STREAM2_OUT_SET_N_LEVELS] = अणु 0x938000, 3, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_CANCEL_R_BUFFERS] =	अणु 0x948000, 4, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_NOTIFY_END_OF_BUFFER] =	अणु 0x950000, 1, RMH_SSIZE_FIXED, 0 पूर्ण,
[CMD_GET_STREAM_VU_METER] =	अणु 0x95A000, 2, RMH_SSIZE_ARG, 0 पूर्ण,
पूर्ण;

/**
 * vx_init_rmh - initialize the RMH instance
 * @rmh: the rmh poपूर्णांकer to be initialized
 * @cmd: the rmh command to be set
 */
व्योम vx_init_rmh(काष्ठा vx_rmh *rmh, अचिन्हित पूर्णांक cmd)
अणु
	अगर (snd_BUG_ON(cmd >= CMD_LAST_INDEX))
		वापस;
	rmh->LgCmd = vx_dsp_cmds[cmd].length;
	rmh->LgStat = vx_dsp_cmds[cmd].st_length;
	rmh->DspStat = vx_dsp_cmds[cmd].st_type;
	rmh->Cmd[0] = vx_dsp_cmds[cmd].opcode;
पूर्ण

