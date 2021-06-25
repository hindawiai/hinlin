<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram pcxhr soundcards
 *
 * मुख्य header file
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_PCXHR_H
#घोषणा __SOUND_PCXHR_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <sound/pcm.h>

#घोषणा PCXHR_DRIVER_VERSION		0x000906	/* 0.9.6 */
#घोषणा PCXHR_DRIVER_VERSION_STRING	"0.9.6"		/* 0.9.6 */


#घोषणा PCXHR_MAX_CARDS		6
#घोषणा PCXHR_PLAYBACK_STREAMS	4

#घोषणा PCXHR_GRANULARITY	96	/* min 96 and multiple of 48 */
/* transfer granularity of pipes and the dsp समय (MBOX4) */
#घोषणा PCXHR_GRANULARITY_MIN	96
/* TODO : granularity could be 64 or 128 */
#घोषणा PCXHR_GRANULARITY_HR22	192	/* granularity क्रम stereo cards */

काष्ठा snd_pcxhr;
काष्ठा pcxhr_mgr;

काष्ठा pcxhr_stream;
काष्ठा pcxhr_pipe;

क्रमागत pcxhr_घड़ी_प्रकारype अणु
	PCXHR_CLOCK_TYPE_INTERNAL = 0,
	PCXHR_CLOCK_TYPE_WORD_CLOCK,
	PCXHR_CLOCK_TYPE_AES_SYNC,
	PCXHR_CLOCK_TYPE_AES_1,
	PCXHR_CLOCK_TYPE_AES_2,
	PCXHR_CLOCK_TYPE_AES_3,
	PCXHR_CLOCK_TYPE_AES_4,
	PCXHR_CLOCK_TYPE_MAX = PCXHR_CLOCK_TYPE_AES_4,
	HR22_CLOCK_TYPE_INTERNAL = PCXHR_CLOCK_TYPE_INTERNAL,
	HR22_CLOCK_TYPE_AES_SYNC,
	HR22_CLOCK_TYPE_AES_1,
	HR22_CLOCK_TYPE_MAX = HR22_CLOCK_TYPE_AES_1,
पूर्ण;

काष्ठा pcxhr_mgr अणु
	अचिन्हित पूर्णांक num_cards;
	काष्ठा snd_pcxhr *chip[PCXHR_MAX_CARDS];

	काष्ठा pci_dev *pci;

	पूर्णांक irq;

	पूर्णांक granularity;

	/* card access with 1 mem bar and 2 io bar's */
	अचिन्हित दीर्घ port[3];

	/* share the name */
	अक्षर name[40];			/* name of this soundcard */

	काष्ठा pcxhr_rmh *prmh;

	काष्ठा mutex lock;		/* पूर्णांकerrupt lock */
	काष्ठा mutex msg_lock;		/* message lock */

	काष्ठा mutex setup_mutex;	/* mutex used in hw_params, खोलो and बंद */
	काष्ठा mutex mixer_mutex;	/* mutex क्रम mixer */

	/* hardware पूर्णांकerface */
	अचिन्हित पूर्णांक dsp_loaded;	/* bit flags of loaded dsp indices */
	अचिन्हित पूर्णांक dsp_version;	/* पढ़ो from embedded once firmware is loaded */
	पूर्णांक playback_chips;
	पूर्णांक capture_chips;
	पूर्णांक fw_file_set;
	पूर्णांक firmware_num;
	अचिन्हित पूर्णांक is_hr_stereo:1;
	अचिन्हित पूर्णांक board_has_aes1:1;	/* अगर 1 board has AES1 plug and SRC */
	अचिन्हित पूर्णांक board_has_analog:1; /* अगर 0 the board is digital only */
	अचिन्हित पूर्णांक board_has_mic:1; /* अगर 1 the board has microphone input */
	अचिन्हित पूर्णांक board_aes_in_192k:1;/* अगर 1 the aes input plugs करो support 192kHz */
	अचिन्हित पूर्णांक mono_capture:1; /* अगर 1 the board करोes mono capture */
	अचिन्हित पूर्णांक capture_ltc:1; /* अगर 1 the board captures LTC input */

	काष्ठा snd_dma_buffer hostport;

	क्रमागत pcxhr_घड़ी_प्रकारype use_घड़ी_प्रकारype;	/* घड़ी type selected by mixer */
	क्रमागत pcxhr_घड़ी_प्रकारype cur_घड़ी_प्रकारype;	/* current घड़ी type synced */
	पूर्णांक sample_rate;
	पूर्णांक ref_count_rate;
	पूर्णांक समयr_toggle;		/* समयr पूर्णांकerrupt toggles between the two values 0x200 and 0x300 */
	पूर्णांक dsp_समय_last;		/* the last dsp समय (पढ़ो by पूर्णांकerrupt) */
	पूर्णांक dsp_समय_err;		/* dsp समय errors */
	अचिन्हित पूर्णांक src_it_dsp;	/* dsp पूर्णांकerrupt source */
	अचिन्हित पूर्णांक io_num_reg_cont;	/* backup of IO_NUM_REG_CONT */
	अचिन्हित पूर्णांक codec_speed;	/* speed mode of the codecs */
	अचिन्हित पूर्णांक sample_rate_real;	/* current real sample rate */
	पूर्णांक last_reg_stat;
	पूर्णांक async_err_stream_xrun;
	पूर्णांक async_err_pipe_xrun;
	पूर्णांक async_err_other_last;

	अचिन्हित अक्षर xlx_cfg;		/* copy of PCXHR_XLX_CFG रेजिस्टर */
	अचिन्हित अक्षर xlx_selmic;	/* copy of PCXHR_XLX_SELMIC रेजिस्टर */
	अचिन्हित अक्षर dsp_reset;	/* copy of PCXHR_DSP_RESET रेजिस्टर */
पूर्ण;


क्रमागत pcxhr_stream_status अणु
	PCXHR_STREAM_STATUS_FREE,
	PCXHR_STREAM_STATUS_OPEN,
	PCXHR_STREAM_STATUS_SCHEDULE_RUN,
	PCXHR_STREAM_STATUS_STARTED,
	PCXHR_STREAM_STATUS_RUNNING,
	PCXHR_STREAM_STATUS_SCHEDULE_STOP,
	PCXHR_STREAM_STATUS_STOPPED,
	PCXHR_STREAM_STATUS_PAUSED
पूर्ण;

काष्ठा pcxhr_stream अणु
	काष्ठा snd_pcm_substream *substream;
	snd_pcm_क्रमmat_t क्रमmat;
	काष्ठा pcxhr_pipe *pipe;

	क्रमागत pcxhr_stream_status status;	/* मुक्त, खोलो, running, draining, छोड़ो */

	u_पूर्णांक64_t समयr_असल_periods;	/* समयr: samples elapsed since TRIGGER_START (multiple of period_size) */
	u_पूर्णांक32_t समयr_period_frag;	/* समयr: samples elapsed since last call to snd_pcm_period_elapsed (0..period_size) */
	u_पूर्णांक32_t समयr_buf_periods;	/* nb of periods in the buffer that have alपढ़ोy elapsed */
	पूर्णांक समयr_is_synced;		/* अगर(0) : समयr needs to be resynced with real hardware poपूर्णांकer */

	पूर्णांक channels;
पूर्ण;


क्रमागत pcxhr_pipe_status अणु
	PCXHR_PIPE_UNDEFINED,
	PCXHR_PIPE_DEFINED
पूर्ण;

काष्ठा pcxhr_pipe अणु
	क्रमागत pcxhr_pipe_status status;
	पूर्णांक is_capture;		/* this is a capture pipe */
	पूर्णांक first_audio;	/* first audio num */
पूर्ण;


काष्ठा snd_pcxhr अणु
	काष्ठा snd_card *card;
	काष्ठा pcxhr_mgr *mgr;
	पूर्णांक chip_idx;		/* zero based */

	काष्ठा snd_pcm *pcm;		/* PCM */

	काष्ठा pcxhr_pipe playback_pipe;	/* 1 stereo pipe only */
	काष्ठा pcxhr_pipe capture_pipe[2];	/* 1 stereo or 2 mono pipes */

	काष्ठा pcxhr_stream playback_stream[PCXHR_PLAYBACK_STREAMS];
	काष्ठा pcxhr_stream capture_stream[2];	/* 1 stereo or 2 mono streams */
	पूर्णांक nb_streams_play;
	पूर्णांक nb_streams_capt;

	पूर्णांक analog_playback_active[2];	/* Mixer : Master Playback !mute */
	पूर्णांक analog_playback_volume[2];	/* Mixer : Master Playback Volume */
	पूर्णांक analog_capture_volume[2];	/* Mixer : Master Capture Volume */
	पूर्णांक digital_playback_active[PCXHR_PLAYBACK_STREAMS][2];
	पूर्णांक digital_playback_volume[PCXHR_PLAYBACK_STREAMS][2];
	पूर्णांक digital_capture_volume[2];	/* Mixer : Digital Capture Volume */
	पूर्णांक monitoring_active[2];	/* Mixer : Monitoring Active */
	पूर्णांक monitoring_volume[2];	/* Mixer : Monitoring Volume */
	पूर्णांक audio_capture_source;	/* Mixer : Audio Capture Source */
	पूर्णांक mic_volume;			/* used by cards with MIC only */
	पूर्णांक mic_boost;			/* used by cards with MIC only */
	पूर्णांक mic_active;			/* used by cards with MIC only */
	पूर्णांक analog_capture_active;	/* used by cards with MIC only */
	पूर्णांक phantom_घातer;		/* used by cards with MIC only */

	अचिन्हित अक्षर aes_bits[5];	/* Mixer : IEC958_AES bits */
पूर्ण;

काष्ठा pcxhr_hostport
अणु
	अक्षर purgebuffer[6];
	अक्षर reserved[2];
पूर्ण;

/* exported */
पूर्णांक pcxhr_create_pcm(काष्ठा snd_pcxhr *chip);
पूर्णांक pcxhr_set_घड़ी(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक rate);
पूर्णांक pcxhr_get_बाह्यal_घड़ी(काष्ठा pcxhr_mgr *mgr,
			     क्रमागत pcxhr_घड़ी_प्रकारype घड़ी_प्रकारype,
			     पूर्णांक *sample_rate);

#पूर्ण_अगर /* __SOUND_PCXHR_H */
