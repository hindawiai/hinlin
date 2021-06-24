<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * low level पूर्णांकerface with पूर्णांकerrupt and message handling
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_PCXHR_CORE_H
#घोषणा __SOUND_PCXHR_CORE_H

काष्ठा firmware;
काष्ठा pcxhr_mgr;

/* init and firmware करोwnload commands */
व्योम pcxhr_reset_xilinx_com(काष्ठा pcxhr_mgr *mgr);
व्योम pcxhr_reset_dsp(काष्ठा pcxhr_mgr *mgr);
व्योम pcxhr_enable_dsp(काष्ठा pcxhr_mgr *mgr);
पूर्णांक pcxhr_load_xilinx_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *xilinx, पूर्णांक second);
पूर्णांक pcxhr_load_eeprom_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *eeprom);
पूर्णांक pcxhr_load_boot_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *boot);
पूर्णांक pcxhr_load_dsp_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *dsp);

/* DSP समय available on MailBox4 रेजिस्टर : 24 bit समय samples() */
#घोषणा PCXHR_DSP_TIME_MASK		0x00ffffff
#घोषणा PCXHR_DSP_TIME_INVALID		0x10000000


#घोषणा PCXHR_SIZE_MAX_CMD		8
#घोषणा PCXHR_SIZE_MAX_STATUS		16
#घोषणा PCXHR_SIZE_MAX_LONG_STATUS	256

काष्ठा pcxhr_rmh अणु
	u16	cmd_len;		/* length of the command to send (WORDs) */
	u16	stat_len;		/* length of the status received (WORDs) */
	u16	dsp_stat;		/* status type, RMP_SSIZE_XXX */
	u16	cmd_idx;		/* index of the command */
	u32	cmd[PCXHR_SIZE_MAX_CMD];
	u32	stat[PCXHR_SIZE_MAX_STATUS];
पूर्ण;

क्रमागत अणु
	CMD_VERSION,			/* cmd_len = 2	stat_len = 1 */
	CMD_SUPPORTED,			/* cmd_len = 1	stat_len = 4 */
	CMD_TEST_IT,			/* cmd_len = 1	stat_len = 1 */
	CMD_SEND_IRQA,			/* cmd_len = 1	stat_len = 0 */
	CMD_ACCESS_IO_WRITE,		/* cmd_len >= 1	stat_len >= 1 */
	CMD_ACCESS_IO_READ,		/* cmd_len >= 1	stat_len >= 1 */
	CMD_ASYNC,			/* cmd_len = 1	stat_len = 1 */
	CMD_MODIFY_CLOCK,		/* cmd_len = 3	stat_len = 0 */
	CMD_RESYNC_AUDIO_INPUTS,	/* cmd_len = 1	stat_len = 0 */
	CMD_GET_DSP_RESOURCES,		/* cmd_len = 1	stat_len = 4 */
	CMD_SET_TIMER_INTERRUPT,	/* cmd_len = 1	stat_len = 0 */
	CMD_RES_PIPE,			/* cmd_len >=2	stat_len = 0 */
	CMD_FREE_PIPE,			/* cmd_len = 1	stat_len = 0 */
	CMD_CONF_PIPE,			/* cmd_len = 2	stat_len = 0 */
	CMD_STOP_PIPE,			/* cmd_len = 1	stat_len = 0 */
	CMD_PIPE_SAMPLE_COUNT,		/* cmd_len = 2	stat_len = 2 */
	CMD_CAN_START_PIPE,		/* cmd_len >= 1	stat_len = 1 */
	CMD_START_STREAM,		/* cmd_len = 2	stat_len = 0 */
	CMD_STREAM_OUT_LEVEL_ADJUST,	/* cmd_len >= 1	stat_len = 0 */
	CMD_STOP_STREAM,		/* cmd_len = 2	stat_len = 0 */
	CMD_UPDATE_R_BUFFERS,		/* cmd_len = 4	stat_len = 0 */
	CMD_FORMAT_STREAM_OUT,		/* cmd_len >= 2	stat_len = 0 */
	CMD_FORMAT_STREAM_IN,		/* cmd_len >= 4	stat_len = 0 */
	CMD_STREAM_SAMPLE_COUNT,	/* cmd_len = 2	stat_len = (2 * nb_stream) */
	CMD_AUDIO_LEVEL_ADJUST,		/* cmd_len = 3	stat_len = 0 */
	CMD_GET_TIME_CODE,		/* cmd_len = 1  stat_len = 5 */
	CMD_MANAGE_SIGNAL,		/* cmd_len = 1  stat_len = 0 */
	CMD_LAST_INDEX
पूर्ण;

#घोषणा MASK_DSP_WORD		0x00ffffff
#घोषणा MASK_ALL_STREAM		0x00ffffff
#घोषणा MASK_DSP_WORD_LEVEL	0x000001ff
#घोषणा MASK_FIRST_FIELD	0x0000001f
#घोषणा FIELD_SIZE		5

/*
 init the rmh काष्ठा; by शेष cmd_len is set to 1
 */
व्योम pcxhr_init_rmh(काष्ठा pcxhr_rmh *rmh, पूर्णांक cmd);

व्योम pcxhr_set_pipe_cmd_params(काष्ठा pcxhr_rmh* rmh, पूर्णांक capture, अचिन्हित पूर्णांक param1,
			       अचिन्हित पूर्णांक param2, अचिन्हित पूर्णांक param3);

#घोषणा DSP_EXT_CMD_SET(x) (x->dsp_version > 0x012800)

/*
 send the rmh
 */
पूर्णांक pcxhr_send_msg(काष्ठा pcxhr_mgr *mgr, काष्ठा pcxhr_rmh *rmh);


/* values used क्रम CMD_ACCESS_IO_WRITE and CMD_ACCESS_IO_READ */
#घोषणा IO_NUM_REG_CONT			0
#घोषणा IO_NUM_REG_GENCLK		1
#घोषणा IO_NUM_REG_MUTE_OUT		2
#घोषणा IO_NUM_SPEED_RATIO		4
#घोषणा IO_NUM_REG_STATUS		5
#घोषणा IO_NUM_REG_CUER			10
#घोषणा IO_NUM_UER_CHIP_REG		11
#घोषणा IO_NUM_REG_CONFIG_SRC		12
#घोषणा IO_NUM_REG_OUT_ANA_LEVEL	20
#घोषणा IO_NUM_REG_IN_ANA_LEVEL		21

#घोषणा REG_CONT_VALSMPTE		0x000800
#घोषणा REG_CONT_UNMUTE_INPUTS		0x020000

/* parameters used with रेजिस्टर IO_NUM_REG_STATUS */
#घोषणा REG_STATUS_OPTIONS		0
#घोषणा REG_STATUS_AES_SYNC		8
#घोषणा REG_STATUS_AES_1		9
#घोषणा REG_STATUS_AES_2		10
#घोषणा REG_STATUS_AES_3		11
#घोषणा REG_STATUS_AES_4		12
#घोषणा REG_STATUS_WORD_CLOCK		13
#घोषणा REG_STATUS_INTER_SYNC		14
#घोषणा REG_STATUS_CURRENT		0x80
/* results */
#घोषणा REG_STATUS_OPT_NO_VIDEO_SIGNAL	0x01
#घोषणा REG_STATUS_OPT_DAUGHTER_MASK	0x1c
#घोषणा REG_STATUS_OPT_ANALOG_BOARD	0x00
#घोषणा REG_STATUS_OPT_NO_DAUGHTER	0x1c
#घोषणा REG_STATUS_OPT_COMPANION_MASK	0xe0
#घोषणा REG_STATUS_OPT_NO_COMPANION	0xe0
#घोषणा REG_STATUS_SYNC_32000		0x00
#घोषणा REG_STATUS_SYNC_44100		0x01
#घोषणा REG_STATUS_SYNC_48000		0x02
#घोषणा REG_STATUS_SYNC_64000		0x03
#घोषणा REG_STATUS_SYNC_88200		0x04
#घोषणा REG_STATUS_SYNC_96000		0x05
#घोषणा REG_STATUS_SYNC_128000		0x06
#घोषणा REG_STATUS_SYNC_176400		0x07
#घोषणा REG_STATUS_SYNC_192000		0x08

पूर्णांक pcxhr_set_pipe_state(काष्ठा pcxhr_mgr *mgr, पूर्णांक playback_mask, पूर्णांक capture_mask, पूर्णांक start);

पूर्णांक pcxhr_ग_लिखो_io_num_reg_cont(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक value, पूर्णांक *changed);

/* codec parameters */
#घोषणा CS8416_RUN		0x200401
#घोषणा CS8416_FORMAT_DETECT	0x200b00
#घोषणा CS8416_CSB0		0x201900
#घोषणा CS8416_CSB1		0x201a00
#घोषणा CS8416_CSB2		0x201b00
#घोषणा CS8416_CSB3		0x201c00
#घोषणा CS8416_CSB4		0x201d00
#घोषणा CS8416_VERSION		0x207f00

#घोषणा CS8420_DATA_FLOW_CTL	0x200301
#घोषणा CS8420_CLOCK_SRC_CTL	0x200401
#घोषणा CS8420_RECEIVER_ERRORS	0x201000
#घोषणा CS8420_SRC_RATIO	0x201e00
#घोषणा CS8420_CSB0		0x202000
#घोषणा CS8420_CSB1		0x202100
#घोषणा CS8420_CSB2		0x202200
#घोषणा CS8420_CSB3		0x202300
#घोषणा CS8420_CSB4		0x202400
#घोषणा CS8420_VERSION		0x207f00

#घोषणा CS4271_MODE_CTL_1	0x200101
#घोषणा CS4271_DAC_CTL		0x200201
#घोषणा CS4271_VOLMIX		0x200301
#घोषणा CS4271_VOLMUTE_LEFT	0x200401
#घोषणा CS4271_VOLMUTE_RIGHT	0x200501
#घोषणा CS4271_ADC_CTL		0x200601
#घोषणा CS4271_MODE_CTL_2	0x200701

#घोषणा CHIP_SIG_AND_MAP_SPI	0xff7f00

/* codec selection */
#घोषणा CS4271_01_CS		0x160018
#घोषणा CS4271_23_CS		0x160019
#घोषणा CS4271_45_CS		0x16001a
#घोषणा CS4271_67_CS		0x16001b
#घोषणा CS4271_89_CS		0x16001c
#घोषणा CS4271_AB_CS		0x16001d
#घोषणा CS8420_01_CS		0x080090
#घोषणा CS8420_23_CS		0x080092
#घोषणा CS8420_45_CS		0x080094
#घोषणा CS8420_67_CS		0x080096
#घोषणा CS8416_01_CS		0x080098


/* पूर्णांकerrupt handling */
irqवापस_t pcxhr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
irqवापस_t pcxhr_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id);

#पूर्ण_अगर /* __SOUND_PCXHR_CORE_H */
