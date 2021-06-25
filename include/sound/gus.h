<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_GUS_H
#घोषणा __SOUND_GUS_H

/*
 *  Global काष्ठाures used क्रम GUS part of ALSA driver
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/समयr.h>
#समावेश <sound/seq_midi_emul.h>
#समावेश <sound/seq_device.h>
#समावेश <linux/पन.स>

/* IO ports */

#घोषणा GUSP(gus, x)			((gus)->gf1.port + SNDRV_g_u_s_##x)

#घोषणा SNDRV_g_u_s_MIDICTRL		(0x320-0x220)
#घोषणा SNDRV_g_u_s_MIDISTAT		(0x320-0x220)
#घोषणा SNDRV_g_u_s_MIDIDATA		(0x321-0x220)

#घोषणा SNDRV_g_u_s_GF1PAGE		(0x322-0x220)
#घोषणा SNDRV_g_u_s_GF1REGSEL		(0x323-0x220)
#घोषणा SNDRV_g_u_s_GF1DATALOW		(0x324-0x220)
#घोषणा SNDRV_g_u_s_GF1DATAHIGH		(0x325-0x220)
#घोषणा SNDRV_g_u_s_IRQSTAT		(0x226-0x220)
#घोषणा SNDRV_g_u_s_TIMERCNTRL		(0x228-0x220)
#घोषणा SNDRV_g_u_s_TIMERDATA		(0x229-0x220)
#घोषणा SNDRV_g_u_s_DRAM		(0x327-0x220)
#घोषणा SNDRV_g_u_s_MIXCNTRLREG		(0x220-0x220)
#घोषणा SNDRV_g_u_s_IRQDMACNTRLREG	(0x22b-0x220)
#घोषणा SNDRV_g_u_s_REGCNTRLS		(0x22f-0x220)
#घोषणा SNDRV_g_u_s_BOARDVERSION	(0x726-0x220)
#घोषणा SNDRV_g_u_s_MIXCNTRLPORT	(0x726-0x220)
#घोषणा SNDRV_g_u_s_IVER		(0x325-0x220)
#घोषणा SNDRV_g_u_s_MIXDATAPORT		(0x326-0x220)
#घोषणा SNDRV_g_u_s_MAXCNTRLPORT	(0x326-0x220)

/* GF1 रेजिस्टरs */

/* global रेजिस्टरs */
#घोषणा SNDRV_GF1_GB_ACTIVE_VOICES		0x0e
#घोषणा SNDRV_GF1_GB_VOICES_IRQ			0x0f
#घोषणा SNDRV_GF1_GB_GLOBAL_MODE		0x19
#घोषणा SNDRV_GF1_GW_LFO_BASE			0x1a
#घोषणा SNDRV_GF1_GB_VOICES_IRQ_READ		0x1f
#घोषणा SNDRV_GF1_GB_DRAM_DMA_CONTROL		0x41
#घोषणा SNDRV_GF1_GW_DRAM_DMA_LOW		0x42
#घोषणा SNDRV_GF1_GW_DRAM_IO_LOW		0x43
#घोषणा SNDRV_GF1_GB_DRAM_IO_HIGH		0x44
#घोषणा SNDRV_GF1_GB_SOUND_BLASTER_CONTROL	0x45
#घोषणा SNDRV_GF1_GB_ADLIB_TIMER_1		0x46
#घोषणा SNDRV_GF1_GB_ADLIB_TIMER_2		0x47
#घोषणा SNDRV_GF1_GB_RECORD_RATE		0x48
#घोषणा SNDRV_GF1_GB_REC_DMA_CONTROL		0x49
#घोषणा SNDRV_GF1_GB_JOYSTICK_DAC_LEVEL		0x4b
#घोषणा SNDRV_GF1_GB_RESET			0x4c
#घोषणा SNDRV_GF1_GB_DRAM_DMA_HIGH		0x50
#घोषणा SNDRV_GF1_GW_DRAM_IO16			0x51
#घोषणा SNDRV_GF1_GW_MEMORY_CONFIG		0x52
#घोषणा SNDRV_GF1_GB_MEMORY_CONTROL		0x53
#घोषणा SNDRV_GF1_GW_FIFO_RECORD_BASE_ADDR	0x54
#घोषणा SNDRV_GF1_GW_FIFO_PLAY_BASE_ADDR	0x55
#घोषणा SNDRV_GF1_GW_FIFO_SIZE			0x56
#घोषणा SNDRV_GF1_GW_INTERLEAVE			0x57
#घोषणा SNDRV_GF1_GB_COMPATIBILITY		0x59
#घोषणा SNDRV_GF1_GB_DECODE_CONTROL		0x5a
#घोषणा SNDRV_GF1_GB_VERSION_NUMBER		0x5b
#घोषणा SNDRV_GF1_GB_MPU401_CONTROL_A		0x5c
#घोषणा SNDRV_GF1_GB_MPU401_CONTROL_B		0x5d
#घोषणा SNDRV_GF1_GB_EMULATION_IRQ		0x60
/* voice specअगरic रेजिस्टरs */
#घोषणा SNDRV_GF1_VB_ADDRESS_CONTROL		0x00
#घोषणा SNDRV_GF1_VW_FREQUENCY			0x01
#घोषणा SNDRV_GF1_VW_START_HIGH			0x02
#घोषणा SNDRV_GF1_VW_START_LOW			0x03
#घोषणा SNDRV_GF1_VA_START			SNDRV_GF1_VW_START_HIGH
#घोषणा SNDRV_GF1_VW_END_HIGH			0x04
#घोषणा SNDRV_GF1_VW_END_LOW			0x05
#घोषणा SNDRV_GF1_VA_END			SNDRV_GF1_VW_END_HIGH
#घोषणा SNDRV_GF1_VB_VOLUME_RATE		0x06
#घोषणा SNDRV_GF1_VB_VOLUME_START		0x07
#घोषणा SNDRV_GF1_VB_VOLUME_END			0x08
#घोषणा SNDRV_GF1_VW_VOLUME			0x09
#घोषणा SNDRV_GF1_VW_CURRENT_HIGH		0x0a
#घोषणा SNDRV_GF1_VW_CURRENT_LOW		0x0b
#घोषणा SNDRV_GF1_VA_CURRENT			SNDRV_GF1_VW_CURRENT_HIGH
#घोषणा SNDRV_GF1_VB_PAN			0x0c
#घोषणा SNDRV_GF1_VW_OFFSET_RIGHT		0x0c
#घोषणा SNDRV_GF1_VB_VOLUME_CONTROL		0x0d
#घोषणा SNDRV_GF1_VB_UPPER_ADDRESS		0x10
#घोषणा SNDRV_GF1_VW_EFFECT_HIGH		0x11
#घोषणा SNDRV_GF1_VW_EFFECT_LOW			0x12
#घोषणा SNDRV_GF1_VA_EFFECT			SNDRV_GF1_VW_EFFECT_HIGH
#घोषणा SNDRV_GF1_VW_OFFSET_LEFT		0x13
#घोषणा SNDRV_GF1_VB_ACCUMULATOR		0x14
#घोषणा SNDRV_GF1_VB_MODE			0x15
#घोषणा SNDRV_GF1_VW_EFFECT_VOLUME		0x16
#घोषणा SNDRV_GF1_VB_FREQUENCY_LFO		0x17
#घोषणा SNDRV_GF1_VB_VOLUME_LFO			0x18
#घोषणा SNDRV_GF1_VW_OFFSET_RIGHT_FINAL		0x1b
#घोषणा SNDRV_GF1_VW_OFFSET_LEFT_FINAL		0x1c
#घोषणा SNDRV_GF1_VW_EFFECT_VOLUME_FINAL	0x1d

/* ICS रेजिस्टरs */

#घोषणा SNDRV_ICS_MIC_DEV		0
#घोषणा SNDRV_ICS_LINE_DEV		1
#घोषणा SNDRV_ICS_CD_DEV		2
#घोषणा SNDRV_ICS_GF1_DEV		3
#घोषणा SNDRV_ICS_NONE_DEV		4
#घोषणा SNDRV_ICS_MASTER_DEV		5

/* LFO */

#घोषणा SNDRV_LFO_TREMOLO		0
#घोषणा SNDRV_LFO_VIBRATO		1

/* misc */

#घोषणा SNDRV_GF1_DMA_UNSIGNED	0x80
#घोषणा SNDRV_GF1_DMA_16BIT	0x40
#घोषणा SNDRV_GF1_DMA_IRQ	0x20
#घोषणा SNDRV_GF1_DMA_WIDTH16	0x04
#घोषणा SNDRV_GF1_DMA_READ	0x02	/* पढ़ो from GUS's DRAM */
#घोषणा SNDRV_GF1_DMA_ENABLE	0x01

/* ramp ranges */

#घोषणा SNDRV_GF1_ATTEN(x)	(snd_gf1_atten_table[x])
#घोषणा SNDRV_GF1_MIN_VOLUME	1800
#घोषणा SNDRV_GF1_MAX_VOLUME	4095
#घोषणा SNDRV_GF1_MIN_OFFSET	(SNDRV_GF1_MIN_VOLUME>>4)
#घोषणा SNDRV_GF1_MAX_OFFSET	255
#घोषणा SNDRV_GF1_MAX_TDEPTH	90

/* defines क्रम memory manager */

#घोषणा SNDRV_GF1_MEM_BLOCK_16BIT	0x0001

#घोषणा SNDRV_GF1_MEM_OWNER_DRIVER	0x0001
#घोषणा SNDRV_GF1_MEM_OWNER_WAVE_SIMPLE	0x0002
#घोषणा SNDRV_GF1_MEM_OWNER_WAVE_GF1	0x0003
#घोषणा SNDRV_GF1_MEM_OWNER_WAVE_IWFFFF	0x0004

/* स्थिरants क्रम पूर्णांकerrupt handlers */

#घोषणा SNDRV_GF1_HANDLER_MIDI_OUT	0x00010000
#घोषणा SNDRV_GF1_HANDLER_MIDI_IN	0x00020000
#घोषणा SNDRV_GF1_HANDLER_TIMER1	0x00040000
#घोषणा SNDRV_GF1_HANDLER_TIMER2	0x00080000
#घोषणा SNDRV_GF1_HANDLER_VOICE		0x00100000
#घोषणा SNDRV_GF1_HANDLER_DMA_WRITE	0x00200000
#घोषणा SNDRV_GF1_HANDLER_DMA_READ	0x00400000
#घोषणा SNDRV_GF1_HANDLER_ALL		(0xffff0000&~SNDRV_GF1_HANDLER_VOICE)

/* स्थिरants क्रम DMA flags */

#घोषणा SNDRV_GF1_DMA_TRIGGER		1

/* --- */

काष्ठा snd_gus_card;

/* GF1 specअगरic काष्ठाure */

काष्ठा snd_gf1_bank_info अणु
	अचिन्हित पूर्णांक address;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा snd_gf1_mem_block अणु
	अचिन्हित लघु flags;	/* flags - SNDRV_GF1_MEM_BLOCK_XXXX */
	अचिन्हित लघु owner;	/* owner - SNDRV_GF1_MEM_OWNER_XXXX */
	अचिन्हित पूर्णांक share;	/* share count */
	अचिन्हित पूर्णांक share_id[4]; /* share ID */
	अचिन्हित पूर्णांक ptr;
	अचिन्हित पूर्णांक size;
	अक्षर *name;
	काष्ठा snd_gf1_mem_block *next;
	काष्ठा snd_gf1_mem_block *prev;
पूर्ण;

काष्ठा snd_gf1_mem अणु
	काष्ठा snd_gf1_bank_info banks_8[4];
	काष्ठा snd_gf1_bank_info banks_16[4];
	काष्ठा snd_gf1_mem_block *first;
	काष्ठा snd_gf1_mem_block *last;
	काष्ठा mutex memory_mutex;
पूर्ण;

काष्ठा snd_gf1_dma_block अणु
	व्योम *buffer;		/* buffer in computer's RAM */
	अचिन्हित दीर्घ buf_addr;	/* buffer address */
	अचिन्हित पूर्णांक addr;	/* address in onboard memory */
	अचिन्हित पूर्णांक count;	/* count in bytes */
	अचिन्हित पूर्णांक cmd;	/* DMA command (क्रमmat) */
	व्योम (*ack)(काष्ठा snd_gus_card * gus, व्योम *निजी_data);
	व्योम *निजी_data;
	काष्ठा snd_gf1_dma_block *next;
पूर्ण;

काष्ठा snd_gus_port अणु
	काष्ठा snd_midi_channel_set * chset;
	काष्ठा snd_gus_card * gus;
	पूर्णांक mode;		/* operation mode */
	पूर्णांक client;		/* sequencer client number */
	पूर्णांक port;		/* sequencer port number */
	अचिन्हित पूर्णांक midi_has_voices: 1;
पूर्ण;

काष्ठा snd_gus_voice;

#घोषणा SNDRV_GF1_VOICE_TYPE_PCM	0
#घोषणा SNDRV_GF1_VOICE_TYPE_SYNTH 	1
#घोषणा SNDRV_GF1_VOICE_TYPE_MIDI	2

#घोषणा SNDRV_GF1_VFLG_RUNNING		(1<<0)
#घोषणा SNDRV_GF1_VFLG_EFFECT_TIMER1	(1<<1)
#घोषणा SNDRV_GF1_VFLG_PAN		(1<<2)

क्रमागत snd_gus_volume_state अणु
	VENV_BEFORE,
	VENV_ATTACK,
	VENV_SUSTAIN,
	VENV_RELEASE,
	VENV_DONE,
	VENV_VOLUME
पूर्ण;

काष्ठा snd_gus_voice अणु
	पूर्णांक number;
	अचिन्हित पूर्णांक use: 1,
	    pcm: 1,
	    synth:1,
	    midi: 1;
	अचिन्हित पूर्णांक flags;
	अचिन्हित अक्षर client;
	अचिन्हित अक्षर port;
	अचिन्हित अक्षर index;
	अचिन्हित अक्षर pad;
	
#अगर_घोषित CONFIG_SND_DEBUG
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_wave;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_volume;
#पूर्ण_अगर
	व्योम (*handler_wave) (काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice * voice);
	व्योम (*handler_volume) (काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice * voice);
	व्योम (*handler_effect) (काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice * voice);
	व्योम (*volume_change) (काष्ठा snd_gus_card * gus);

	काष्ठा snd_gus_sample_ops *sample_ops;

	/* running status / रेजिस्टरs */

	अचिन्हित लघु fc_रेजिस्टर;
	अचिन्हित लघु fc_lfo;
	अचिन्हित लघु gf1_volume;
	अचिन्हित अक्षर control;
	अचिन्हित अक्षर mode;
	अचिन्हित अक्षर gf1_pan;
	अचिन्हित अक्षर effect_accumulator;
	अचिन्हित अक्षर volume_control;
	अचिन्हित अक्षर venv_value_next;
	क्रमागत snd_gus_volume_state venv_state;
	क्रमागत snd_gus_volume_state venv_state_prev;
	अचिन्हित लघु vlo;
	अचिन्हित लघु vro;
	अचिन्हित लघु gf1_effect_volume;
	
	/* --- */

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_gus_voice *voice);
पूर्ण;

काष्ठा snd_gf1 अणु

	अचिन्हित पूर्णांक enh_mode:1,	/* enhanced mode (GFA1) */
		     hw_lfo:1,		/* use hardware LFO */
		     sw_lfo:1,		/* use software LFO */
		     effect:1;		/* use effect voices */

	अचिन्हित दीर्घ port;		/* port of GF1 chip */
	काष्ठा resource *res_port1;
	काष्ठा resource *res_port2;
	पूर्णांक irq;			/* IRQ number */
	पूर्णांक dma1;			/* DMA1 number */
	पूर्णांक dma2;			/* DMA2 number */
	अचिन्हित पूर्णांक memory;		/* GUS's DRAM size in bytes */
	अचिन्हित पूर्णांक rom_memory;	/* GUS's ROM size in bytes */
	अचिन्हित पूर्णांक rom_present;	/* biपंचांगask */
	अचिन्हित पूर्णांक rom_banks;		/* GUS's ROM banks */

	काष्ठा snd_gf1_mem mem_alloc;

	/* रेजिस्टरs */
	अचिन्हित लघु reg_page;
	अचिन्हित लघु reg_regsel;
	अचिन्हित लघु reg_data8;
	अचिन्हित लघु reg_data16;
	अचिन्हित लघु reg_irqstat;
	अचिन्हित लघु reg_dram;
	अचिन्हित लघु reg_समयrctrl;
	अचिन्हित लघु reg_समयrdata;
	अचिन्हित अक्षर ics_regs[6][2];
	/* --------- */

	अचिन्हित अक्षर active_voices;	/* active voices */
	अचिन्हित अक्षर active_voice;	/* selected voice (GF1PAGE रेजिस्टर) */

	काष्ठा snd_gus_voice voices[32];	/* GF1 voices */

	अचिन्हित पूर्णांक शेष_voice_address;

	अचिन्हित लघु playback_freq;	/* GF1 playback (mixing) frequency */
	अचिन्हित लघु mode;		/* see to SNDRV_GF1_MODE_XXXX */
	अचिन्हित अक्षर volume_ramp;
	अचिन्हित अक्षर smooth_pan;
	अचिन्हित अक्षर full_range_pan;
	अचिन्हित अक्षर pad0;

	अचिन्हित अक्षर *lfos;

	/* पूर्णांकerrupt handlers */

	व्योम (*पूर्णांकerrupt_handler_midi_out) (काष्ठा snd_gus_card * gus);
	व्योम (*पूर्णांकerrupt_handler_midi_in) (काष्ठा snd_gus_card * gus);
	व्योम (*पूर्णांकerrupt_handler_समयr1) (काष्ठा snd_gus_card * gus);
	व्योम (*पूर्णांकerrupt_handler_समयr2) (काष्ठा snd_gus_card * gus);
	व्योम (*पूर्णांकerrupt_handler_dma_ग_लिखो) (काष्ठा snd_gus_card * gus);
	व्योम (*पूर्णांकerrupt_handler_dma_पढ़ो) (काष्ठा snd_gus_card * gus);

#अगर_घोषित CONFIG_SND_DEBUG
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_midi_out;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_midi_in;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_समयr1;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_समयr2;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_dma_ग_लिखो;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_dma_पढ़ो;
	अचिन्हित पूर्णांक पूर्णांकerrupt_stat_voice_lost;
#पूर्ण_अगर

	/* synthesizer */

	पूर्णांक seq_client;
	काष्ठा snd_gus_port seq_ports[4];

	/* समयr */

	अचिन्हित लघु समयr_enabled;
	काष्ठा snd_समयr *समयr1;
	काष्ठा snd_समयr *समयr2;

	/* midi */

	अचिन्हित लघु uart_cmd;
	अचिन्हित पूर्णांक uart_framing;
	अचिन्हित पूर्णांक uart_overrun;

	/* dma operations */

	अचिन्हित पूर्णांक dma_flags;
	अचिन्हित पूर्णांक dma_shared;
	काष्ठा snd_gf1_dma_block *dma_data_pcm;
	काष्ठा snd_gf1_dma_block *dma_data_pcm_last;
	काष्ठा snd_gf1_dma_block *dma_data_synth;
	काष्ठा snd_gf1_dma_block *dma_data_synth_last;
	व्योम (*dma_ack)(काष्ठा snd_gus_card * gus, व्योम *निजी_data);
	व्योम *dma_निजी_data;

	/* pcm */
	पूर्णांक pcm_channels;
	पूर्णांक pcm_alloc_voices;
        अचिन्हित लघु pcm_volume_level_left;
	अचिन्हित लघु pcm_volume_level_right;
	अचिन्हित लघु pcm_volume_level_left1;
	अचिन्हित लघु pcm_volume_level_right1;
                                
	अचिन्हित अक्षर pcm_rcntrl_reg;
	अचिन्हित अक्षर pad_end;
पूर्ण;

/* मुख्य काष्ठाure क्रम GUS card */

काष्ठा snd_gus_card अणु
	काष्ठा snd_card *card;

	अचिन्हित पूर्णांक
	 initialized: 1,		/* resources were initialized */
	 equal_irq:1,			/* GF1 and CODEC shares IRQ (GUS MAX only) */
	 equal_dma:1,			/* अगर dma channels are equal (not valid क्रम daughter board) */
	 ics_flag:1,			/* have we ICS mixer chip */
	 ics_flipped:1,			/* ICS mixer have flipped some channels? */
	 codec_flag:1,			/* have we CODEC chip? */
	 max_flag:1,			/* have we GUS MAX card? */
	 max_ctrl_flag:1,		/* have we original GUS MAX card? */
	 daughter_flag:1,		/* have we daughter board? */
	 पूर्णांकerwave:1,			/* hey - we have InterWave card */
	 ess_flag:1,			/* ESS chip found... GUS Extreme */
	 ace_flag:1,			/* GUS ACE detected */
	 uart_enable:1;			/* enable MIDI UART */
	अचिन्हित लघु revision;	/* revision of chip */
	अचिन्हित लघु max_cntrl_val;	/* GUS MAX control value */
	अचिन्हित लघु mix_cntrl_reg;	/* mixer control रेजिस्टर */
	अचिन्हित लघु joystick_dac;	/* joystick DAC level */
	पूर्णांक समयr_dev;			/* समयr device */

	काष्ठा snd_gf1 gf1;	/* gf1 specअगरic variables */
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *pcm_cap_substream;
	अचिन्हित पूर्णांक c_dma_size;
	अचिन्हित पूर्णांक c_period_size;
	अचिन्हित पूर्णांक c_pos;

	काष्ठा snd_rawmidi *midi_uart;
	काष्ठा snd_rawmidi_substream *midi_substream_output;
	काष्ठा snd_rawmidi_substream *midi_substream_input;

	spinlock_t reg_lock;
	spinlock_t voice_alloc;
	spinlock_t active_voice_lock;
	spinlock_t event_lock;
	spinlock_t dma_lock;
	spinlock_t pcm_volume_level_lock;
	spinlock_t uart_cmd_lock;
	काष्ठा mutex dma_mutex;
	काष्ठा mutex रेजिस्टर_mutex;
पूर्ण;

/* I/O functions क्रम GF1/InterWave chip - gus_io.c */

अटल अंतरभूत व्योम snd_gf1_select_voice(काष्ठा snd_gus_card * gus, पूर्णांक voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->active_voice_lock, flags);
	अगर (voice != gus->gf1.active_voice) अणु
		gus->gf1.active_voice = voice;
		outb(voice, GUSP(gus, GF1PAGE));
	पूर्ण
	spin_unlock_irqrestore(&gus->active_voice_lock, flags);
पूर्ण

अटल अंतरभूत व्योम snd_gf1_uart_cmd(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर b)
अणु
	outb(gus->gf1.uart_cmd = b, GUSP(gus, MIDICTRL));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर snd_gf1_uart_stat(काष्ठा snd_gus_card * gus)
अणु
	वापस inb(GUSP(gus, MIDISTAT));
पूर्ण

अटल अंतरभूत व्योम snd_gf1_uart_put(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर b)
अणु
	outb(b, GUSP(gus, MIDIDATA));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर snd_gf1_uart_get(काष्ठा snd_gus_card * gus)
अणु
	वापस inb(GUSP(gus, MIDIDATA));
पूर्ण

बाह्य व्योम snd_gf1_delay(काष्ठा snd_gus_card * gus);

बाह्य व्योम snd_gf1_ctrl_stop(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);

बाह्य व्योम snd_gf1_ग_लिखो8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);
बाह्य अचिन्हित अक्षर snd_gf1_look8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);
अटल अंतरभूत अचिन्हित अक्षर snd_gf1_पढ़ो8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस snd_gf1_look8(gus, reg | 0x80);
पूर्ण
बाह्य व्योम snd_gf1_ग_लिखो16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित पूर्णांक data);
बाह्य अचिन्हित लघु snd_gf1_look16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);
अटल अंतरभूत अचिन्हित लघु snd_gf1_पढ़ो16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस snd_gf1_look16(gus, reg | 0x80);
पूर्ण
बाह्य व्योम snd_gf1_adlib_ग_लिखो(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);
बाह्य व्योम snd_gf1_dram_addr(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr);
बाह्य व्योम snd_gf1_poke(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr, अचिन्हित अक्षर data);
बाह्य अचिन्हित अक्षर snd_gf1_peek(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक addr);
बाह्य व्योम snd_gf1_ग_लिखो_addr(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित पूर्णांक addr, लघु w_16bit);
बाह्य अचिन्हित पूर्णांक snd_gf1_पढ़ो_addr(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, लघु w_16bit);
बाह्य व्योम snd_gf1_i_ctrl_stop(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);
बाह्य व्योम snd_gf1_i_ग_लिखो8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित अक्षर data);
बाह्य अचिन्हित अक्षर snd_gf1_i_look8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);
बाह्य व्योम snd_gf1_i_ग_लिखो16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg, अचिन्हित पूर्णांक data);
अटल अंतरभूत अचिन्हित अक्षर snd_gf1_i_पढ़ो8(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस snd_gf1_i_look8(gus, reg | 0x80);
पूर्ण
बाह्य अचिन्हित लघु snd_gf1_i_look16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg);
अटल अंतरभूत अचिन्हित लघु snd_gf1_i_पढ़ो16(काष्ठा snd_gus_card * gus, अचिन्हित अक्षर reg)
अणु
	वापस snd_gf1_i_look16(gus, reg | 0x80);
पूर्ण

बाह्य व्योम snd_gf1_select_active_voices(काष्ठा snd_gus_card * gus);

/* gus_lfo.c */

काष्ठा _SND_IW_LFO_PROGRAM अणु
	अचिन्हित लघु freq_and_control;
	अचिन्हित अक्षर depth_final;
	अचिन्हित अक्षर depth_inc;
	अचिन्हित लघु twave;
	अचिन्हित लघु depth;
पूर्ण;

#अगर 0
बाह्य irqवापस_t snd_gf1_lfo_effect_पूर्णांकerrupt(काष्ठा snd_gus_card * gus, snd_gf1_voice_t * voice);
#पूर्ण_अगर
बाह्य व्योम snd_gf1_lfo_init(काष्ठा snd_gus_card * gus);
बाह्य व्योम snd_gf1_lfo_करोne(काष्ठा snd_gus_card * gus);
बाह्य व्योम snd_gf1_lfo_program(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type, काष्ठा _SND_IW_LFO_PROGRAM *program);
बाह्य व्योम snd_gf1_lfo_enable(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type);
बाह्य व्योम snd_gf1_lfo_disable(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type);
बाह्य व्योम snd_gf1_lfo_change_freq(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type, पूर्णांक freq);
बाह्य व्योम snd_gf1_lfo_change_depth(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type, पूर्णांक depth);
बाह्य व्योम snd_gf1_lfo_setup(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type, पूर्णांक freq, पूर्णांक current_depth, पूर्णांक depth, पूर्णांक sweep, पूर्णांक shape);
बाह्य व्योम snd_gf1_lfo_shutकरोwn(काष्ठा snd_gus_card * gus, पूर्णांक voice, पूर्णांक lfo_type);
#अगर 0
बाह्य व्योम snd_gf1_lfo_command(काष्ठा snd_gus_card * gus, पूर्णांक voice, अचिन्हित अक्षर *command);
#पूर्ण_अगर

/* gus_mem.c */

व्योम snd_gf1_mem_lock(काष्ठा snd_gf1_mem * alloc, पूर्णांक xup);
पूर्णांक snd_gf1_mem_xमुक्त(काष्ठा snd_gf1_mem * alloc, काष्ठा snd_gf1_mem_block * block);
काष्ठा snd_gf1_mem_block *snd_gf1_mem_alloc(काष्ठा snd_gf1_mem * alloc, पूर्णांक owner,
				       अक्षर *name, पूर्णांक size, पूर्णांक w_16,
				       पूर्णांक align, अचिन्हित पूर्णांक *share_id);
पूर्णांक snd_gf1_mem_मुक्त(काष्ठा snd_gf1_mem * alloc, अचिन्हित पूर्णांक address);
पूर्णांक snd_gf1_mem_मुक्त_owner(काष्ठा snd_gf1_mem * alloc, पूर्णांक owner);
पूर्णांक snd_gf1_mem_init(काष्ठा snd_gus_card * gus);
पूर्णांक snd_gf1_mem_करोne(काष्ठा snd_gus_card * gus);

/* gus_mem_proc.c */

पूर्णांक snd_gf1_mem_proc_init(काष्ठा snd_gus_card * gus);

/* gus_dma.c */

पूर्णांक snd_gf1_dma_init(काष्ठा snd_gus_card * gus);
पूर्णांक snd_gf1_dma_करोne(काष्ठा snd_gus_card * gus);
पूर्णांक snd_gf1_dma_transfer_block(काष्ठा snd_gus_card * gus,
			       काष्ठा snd_gf1_dma_block * block,
			       पूर्णांक atomic,
			       पूर्णांक synth);

/* gus_volume.c */

अचिन्हित लघु snd_gf1_lvol_to_gvol_raw(अचिन्हित पूर्णांक vol);
अचिन्हित लघु snd_gf1_translate_freq(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक freq2);

/* gus_reset.c */

व्योम snd_gf1_set_शेष_handlers(काष्ठा snd_gus_card * gus, अचिन्हित पूर्णांक what);
व्योम snd_gf1_smart_stop_voice(काष्ठा snd_gus_card * gus, अचिन्हित लघु voice);
व्योम snd_gf1_stop_voice(काष्ठा snd_gus_card * gus, अचिन्हित लघु voice);
व्योम snd_gf1_stop_voices(काष्ठा snd_gus_card * gus, अचिन्हित लघु v_min, अचिन्हित लघु v_max);
काष्ठा snd_gus_voice *snd_gf1_alloc_voice(काष्ठा snd_gus_card * gus, पूर्णांक type, पूर्णांक client, पूर्णांक port);
व्योम snd_gf1_मुक्त_voice(काष्ठा snd_gus_card * gus, काष्ठा snd_gus_voice *voice);
पूर्णांक snd_gf1_start(काष्ठा snd_gus_card * gus);
पूर्णांक snd_gf1_stop(काष्ठा snd_gus_card * gus);

/* gus_mixer.c */

पूर्णांक snd_gf1_new_mixer(काष्ठा snd_gus_card * gus);

/* gus_pcm.c */

पूर्णांक snd_gf1_pcm_new(काष्ठा snd_gus_card *gus, पूर्णांक pcm_dev, पूर्णांक control_index);

#अगर_घोषित CONFIG_SND_DEBUG
बाह्य व्योम snd_gf1_prपूर्णांक_voice_रेजिस्टरs(काष्ठा snd_gus_card * gus);
#पूर्ण_अगर

/* gus.c */

पूर्णांक snd_gus_use_inc(काष्ठा snd_gus_card * gus);
व्योम snd_gus_use_dec(काष्ठा snd_gus_card * gus);
पूर्णांक snd_gus_create(काष्ठा snd_card *card,
		   अचिन्हित दीर्घ port,
		   पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		   पूर्णांक समयr_dev,
		   पूर्णांक voices,
		   पूर्णांक pcm_channels,
		   पूर्णांक effect,
		   काष्ठा snd_gus_card ** rgus);
पूर्णांक snd_gus_initialize(काष्ठा snd_gus_card * gus);

/* gus_irq.c */

irqवापस_t snd_gus_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
#अगर_घोषित CONFIG_SND_DEBUG
व्योम snd_gus_irq_profile_init(काष्ठा snd_gus_card *gus);
#पूर्ण_अगर

/* gus_uart.c */

पूर्णांक snd_gf1_rawmidi_new(काष्ठा snd_gus_card *gus, पूर्णांक device);

/* gus_dram.c */
पूर्णांक snd_gus_dram_ग_लिखो(काष्ठा snd_gus_card *gus, अक्षर __user *ptr,
		       अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक size);
पूर्णांक snd_gus_dram_पढ़ो(काष्ठा snd_gus_card *gus, अक्षर __user *ptr,
		      अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक size, पूर्णांक rom);

/* gus_समयr.c */
व्योम snd_gf1_समयrs_init(काष्ठा snd_gus_card *gus);
व्योम snd_gf1_समयrs_करोne(काष्ठा snd_gus_card *gus);

#पूर्ण_अगर /* __SOUND_GUS_H */
