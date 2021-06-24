<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम Digigram miXart soundcards
 *
 * मुख्य header file
 *
 * Copyright (c) 2003 by Digigram <alsa@digigram.com>
 */

#अगर_अघोषित __SOUND_MIXART_H
#घोषणा __SOUND_MIXART_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <sound/pcm.h>

#घोषणा MIXART_DRIVER_VERSION	0x000100	/* 0.1.0 */


/*
 */

काष्ठा mixart_uid अणु
	u32 object_id;
	u32 desc;
पूर्ण;

काष्ठा mem_area अणु
	अचिन्हित दीर्घ phys;
	व्योम __iomem *virt;
	काष्ठा resource *res;
पूर्ण;


काष्ठा mixart_route अणु
	अचिन्हित अक्षर connected;
	अचिन्हित अक्षर phase_inv;
	पूर्णांक volume;
पूर्ण;


/* firmware status codes  */
#घोषणा MIXART_MOTHERBOARD_XLX_INDEX  0
#घोषणा MIXART_MOTHERBOARD_ELF_INDEX  1
#घोषणा MIXART_AESEBUBOARD_XLX_INDEX  2
#घोषणा MIXART_HARDW_खाताS_MAX_INDEX  3  /* xilinx, elf, AESEBU xilinx */

#घोषणा MIXART_MAX_CARDS	4
#घोषणा MSG_FIFO_SIZE           16

#घोषणा MIXART_MAX_PHYS_CONNECTORS  (MIXART_MAX_CARDS * 2 * 2) /* 4 * stereo * (analog+digital) */

काष्ठा mixart_mgr अणु
	अचिन्हित पूर्णांक num_cards;
	काष्ठा snd_mixart *chip[MIXART_MAX_CARDS];

	काष्ठा pci_dev *pci;

	पूर्णांक irq;

	/* memory-maps */
	काष्ठा mem_area mem[2];

	/* one and only blocking message or notअगरication may be pending  */
	u32 pending_event;
	रुको_queue_head_t msg_sleep;

	/* messages fअगरo */
	u32 msg_fअगरo[MSG_FIFO_SIZE];
	पूर्णांक msg_fअगरo_पढ़ोptr;
	पूर्णांक msg_fअगरo_ग_लिखोptr;
	atomic_t msg_processed;       /* number of messages to be processed in irq thपढ़ो */

	काष्ठा mutex lock;              /* पूर्णांकerrupt lock */
	काष्ठा mutex msg_lock;		/* mailbox lock */

	काष्ठा mutex setup_mutex; /* mutex used in hw_params, खोलो and बंद */

	/* hardware पूर्णांकerface */
	अचिन्हित पूर्णांक dsp_loaded;      /* bit flags of loaded dsp indices */
	अचिन्हित पूर्णांक board_type;      /* पढ़ो from embedded once elf file is loaded, 250 = miXart8, 251 = with AES, 252 = with Cobranet */

	काष्ठा snd_dma_buffer flowinfo;
	काष्ठा snd_dma_buffer bufferinfo;

	काष्ठा mixart_uid         uid_console_manager;
	पूर्णांक sample_rate;
	पूर्णांक ref_count_rate;

	काष्ठा mutex mixer_mutex; /* mutex क्रम mixer */

पूर्ण;


#घोषणा MIXART_STREAM_STATUS_FREE	0
#घोषणा MIXART_STREAM_STATUS_OPEN	1
#घोषणा MIXART_STREAM_STATUS_RUNNING	2
#घोषणा MIXART_STREAM_STATUS_DRAINING	3
#घोषणा MIXART_STREAM_STATUS_PAUSE	4

#घोषणा MIXART_PLAYBACK_STREAMS		4
#घोषणा MIXART_CAPTURE_STREAMS		1

#घोषणा MIXART_PCM_ANALOG		0
#घोषणा MIXART_PCM_DIGITAL		1
#घोषणा MIXART_PCM_TOTAL		2

#घोषणा MIXART_MAX_STREAM_PER_CARD  (MIXART_PCM_TOTAL * (MIXART_PLAYBACK_STREAMS + MIXART_CAPTURE_STREAMS) )


#घोषणा MIXART_NOTIFY_CARD_MASK		0xF000
#घोषणा MIXART_NOTIFY_CARD_OFFSET	12
#घोषणा MIXART_NOTIFY_PCM_MASK		0x0F00
#घोषणा MIXART_NOTIFY_PCM_OFFSET	8
#घोषणा MIXART_NOTIFY_CAPT_MASK		0x0080
#घोषणा MIXART_NOTIFY_SUBS_MASK		0x007F


काष्ठा mixart_stream अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा mixart_pipe *pipe;
	पूर्णांक pcm_number;

	पूर्णांक status;      /* nothing, running, draining */

	u64  असल_period_elapsed;  /* last असलolute stream position where period_elapsed was called (multiple of runसमय->period_size) */
	u32  buf_periods;         /* periods counter in the buffer (< runसमय->periods) */
	u32  buf_period_frag;     /* defines with buf_period_pos the exact position in the buffer (< runसमय->period_size) */

	पूर्णांक channels;
पूर्ण;


क्रमागत mixart_pipe_status अणु
	PIPE_UNDEFINED,
	PIPE_STOPPED,
	PIPE_RUNNING,
	PIPE_CLOCK_SET
पूर्ण;

काष्ठा mixart_pipe अणु
	काष्ठा mixart_uid group_uid;			/* id of the pipe, as वापसed by embedded */
	पूर्णांक          stream_count;
	काष्ठा mixart_uid uid_left_connector;	/* UID's क्रम the audio connectors */
	काष्ठा mixart_uid uid_right_connector;
	क्रमागत mixart_pipe_status status;
	पूर्णांक references;             /* number of subs खोलोned */
	पूर्णांक monitoring;             /* pipe used क्रम monitoring issue */
पूर्ण;


काष्ठा snd_mixart अणु
	काष्ठा snd_card *card;
	काष्ठा mixart_mgr *mgr;
	पूर्णांक chip_idx;               /* zero based */
	काष्ठा snd_hwdep *hwdep;	    /* DSP loader, only क्रम the first card */

	काष्ठा snd_pcm *pcm;             /* PCM analog i/o */
	काष्ठा snd_pcm *pcm_dig;         /* PCM digital i/o */

	/* allocate stereo pipe क्रम instance */
	काष्ठा mixart_pipe pipe_in_ana;
	काष्ठा mixart_pipe pipe_out_ana;

	/* अगर AES/EBU daughter board is available, additional pipes possible on pcm_dig */
	काष्ठा mixart_pipe pipe_in_dig;
	काष्ठा mixart_pipe pipe_out_dig;

	काष्ठा mixart_stream playback_stream[MIXART_PCM_TOTAL][MIXART_PLAYBACK_STREAMS]; /* 0 = pcm, 1 = pcm_dig */
	काष्ठा mixart_stream capture_stream[MIXART_PCM_TOTAL];                           /* 0 = pcm, 1 = pcm_dig */

	/* UID's for the physical io's */
	काष्ठा mixart_uid uid_out_analog_physio;
	काष्ठा mixart_uid uid_in_analog_physio;

	पूर्णांक analog_playback_active[2];		/* Mixer : Master Playback active (!mute) */
	पूर्णांक analog_playback_volume[2];		/* Mixer : Master Playback Volume */
	पूर्णांक analog_capture_volume[2];		/* Mixer : Master Capture Volume */
	पूर्णांक digital_playback_active[2*MIXART_PLAYBACK_STREAMS][2];	/* Mixer : Digital Playback Active [(analog+AES output)*streams][stereo]*/
	पूर्णांक digital_playback_volume[2*MIXART_PLAYBACK_STREAMS][2];	/* Mixer : Digital Playback Volume [(analog+AES output)*streams][stereo]*/
	पूर्णांक digital_capture_volume[2][2];	/* Mixer : Digital Capture Volume [analog+AES output][stereo] */
	पूर्णांक monitoring_active[2];		/* Mixer : Monitoring Active */
	पूर्णांक monitoring_volume[2];		/* Mixer : Monitoring Volume */
पूर्ण;

काष्ठा mixart_bufferinfo
अणु
	u32 buffer_address;
	u32 reserved[5];
	u32 available_length;
	u32 buffer_id;
पूर्ण;

काष्ठा mixart_flowinfo
अणु
	u32 bufferinfo_array_phy_address;
	u32 reserved[11];
	u32 bufferinfo_count;
	u32 capture;
पूर्ण;

/* exported */
पूर्णांक snd_mixart_create_pcm(काष्ठा snd_mixart * chip);
काष्ठा mixart_pipe *snd_mixart_add_ref_pipe(काष्ठा snd_mixart *chip, पूर्णांक pcm_number, पूर्णांक capture, पूर्णांक monitoring);
पूर्णांक snd_mixart_समाप्त_ref_pipe(काष्ठा mixart_mgr *mgr, काष्ठा mixart_pipe *pipe, पूर्णांक monitoring);

#पूर्ण_अगर /* __SOUND_MIXART_H */
