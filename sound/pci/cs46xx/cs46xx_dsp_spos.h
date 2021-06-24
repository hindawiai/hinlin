<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  The driver क्रम the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#अगर_अघोषित __CS46XX_DSP_SPOS_H__
#घोषणा __CS46XX_DSP_SPOS_H__

#समावेश "cs46xx_dsp_scb_types.h"
#समावेश "cs46xx_dsp_task_types.h"

#घोषणा SYMBOL_CONSTANT  0x0
#घोषणा SYMBOL_SAMPLE    0x1
#घोषणा SYMBOL_PARAMETER 0x2
#घोषणा SYMBOL_CODE      0x3

#घोषणा SEGTYPE_SP_PROGRAM              0x00000001
#घोषणा SEGTYPE_SP_PARAMETER            0x00000002
#घोषणा SEGTYPE_SP_SAMPLE               0x00000003
#घोषणा SEGTYPE_SP_COEFFICIENT          0x00000004

#घोषणा DSP_SPOS_UU      0x0deadul     /* unused */
#घोषणा DSP_SPOS_DC      0x0badul      /* करोn't care */
#घोषणा DSP_SPOS_DC_DC   0x0bad0badul  /* करोn't care */
#घोषणा DSP_SPOS_UUUU    0xdeadc0edul  /* unused */
#घोषणा DSP_SPOS_UUHI    0xdeadul
#घोषणा DSP_SPOS_UULO    0xc0edul
#घोषणा DSP_SPOS_DCDC    0x0badf1d0ul  /* करोn't care */
#घोषणा DSP_SPOS_DCDCHI  0x0badul
#घोषणा DSP_SPOS_DCDCLO  0xf1d0ul

#घोषणा DSP_MAX_TASK_NAME   60
#घोषणा DSP_MAX_SYMBOL_NAME 100
#घोषणा DSP_MAX_SCB_NAME    60
#घोषणा DSP_MAX_SCB_DESC    200
#घोषणा DSP_MAX_TASK_DESC   50

#घोषणा DSP_MAX_PCM_CHANNELS 32
#घोषणा DSP_MAX_SRC_NR       14

#घोषणा DSP_PCM_MAIN_CHANNEL        1
#घोषणा DSP_PCM_REAR_CHANNEL        2
#घोषणा DSP_PCM_CENTER_LFE_CHANNEL  3
#घोषणा DSP_PCM_S71_CHANNEL         4 /* surround 7.1 */
#घोषणा DSP_IEC958_CHANNEL          5

#घोषणा DSP_SPDIF_STATUS_OUTPUT_ENABLED       1
#घोषणा DSP_SPDIF_STATUS_PLAYBACK_OPEN        2
#घोषणा DSP_SPDIF_STATUS_HW_ENABLED           4
#घोषणा DSP_SPDIF_STATUS_INPUT_CTRL_ENABLED   8

काष्ठा dsp_symbol_entry अणु
	u32 address;
	अक्षर symbol_name[DSP_MAX_SYMBOL_NAME];
	पूर्णांक symbol_type;

	/* initialized by driver */
	काष्ठा dsp_module_desc * module;
	पूर्णांक deleted;
पूर्ण;

काष्ठा dsp_symbol_desc अणु
	पूर्णांक nsymbols;

	काष्ठा dsp_symbol_entry *symbols;

	/* initialized by driver */
	पूर्णांक highest_frag_index;
पूर्ण;

काष्ठा dsp_segment_desc अणु
	पूर्णांक segment_type;
	u32 offset;
	u32 size;
	u32 * data;
पूर्ण;

काष्ठा dsp_module_desc अणु
	अक्षर * module_name;
	काष्ठा dsp_symbol_desc symbol_table;
	पूर्णांक nsegments;
	काष्ठा dsp_segment_desc * segments;

	/* initialized by driver */
	u32 overlay_begin_address;
	u32 load_address;
	पूर्णांक nfixups;
पूर्ण;

काष्ठा dsp_scb_descriptor अणु
	अक्षर scb_name[DSP_MAX_SCB_NAME];
	u32 address;
	पूर्णांक index;
	u32 *data;

	काष्ठा dsp_scb_descriptor * sub_list_ptr;
	काष्ठा dsp_scb_descriptor * next_scb_ptr;
	काष्ठा dsp_scb_descriptor * parent_scb_ptr;

	काष्ठा dsp_symbol_entry * task_entry;
	काष्ठा dsp_symbol_entry * scb_symbol;

	काष्ठा snd_info_entry *proc_info;
	पूर्णांक ref_count;

	u16 volume[2];
	अचिन्हित पूर्णांक deleted :1;
	अचिन्हित पूर्णांक updated :1;
	अचिन्हित पूर्णांक volume_set :1;
पूर्ण;

काष्ठा dsp_task_descriptor अणु
	अक्षर task_name[DSP_MAX_TASK_NAME];
	पूर्णांक size;
	u32 address;
	पूर्णांक index;
	u32 *data;
पूर्ण;

काष्ठा dsp_pcm_channel_descriptor अणु
	पूर्णांक active;
	पूर्णांक src_slot;
	पूर्णांक pcm_slot;
	u32 sample_rate;
	u32 unlinked;
	काष्ठा dsp_scb_descriptor * pcm_पढ़ोer_scb;
	काष्ठा dsp_scb_descriptor * src_scb;
	काष्ठा dsp_scb_descriptor * mixer_scb;

	व्योम * निजी_data;
पूर्ण;

काष्ठा dsp_spos_instance अणु
	काष्ठा dsp_symbol_desc symbol_table; /* currently available loaded symbols in SP */

	पूर्णांक nmodules;
	काष्ठा dsp_module_desc * modules; /* modules loaded पूर्णांकo SP */

	काष्ठा dsp_segment_desc code;

	/* Main PCM playback mixer */
	काष्ठा dsp_scb_descriptor * master_mix_scb;
	u16 dac_volume_right;
	u16 dac_volume_left;

	/* Rear/surround PCM playback mixer */
	काष्ठा dsp_scb_descriptor * rear_mix_scb;

	/* Center/LFE mixer */
	काष्ठा dsp_scb_descriptor * center_lfe_mix_scb;

	पूर्णांक npcm_channels;
	पूर्णांक nsrc_scb;
	काष्ठा dsp_pcm_channel_descriptor pcm_channels[DSP_MAX_PCM_CHANNELS];
	पूर्णांक src_scb_slots[DSP_MAX_SRC_NR];

	/* cache this symbols */
	काष्ठा dsp_symbol_entry * null_algorithm; /* used by PCMपढ़ोerSCB's */
	काष्ठा dsp_symbol_entry * s16_up;         /* used by SRCtaskSCB's */

	/* proc fs */  
	काष्ठा snd_card *snd_card;
	काष्ठा snd_info_entry * proc_dsp_dir;

	/* SCB's descriptors */
	पूर्णांक nscb;
	पूर्णांक scb_highest_frag_index;
	काष्ठा dsp_scb_descriptor scbs[DSP_MAX_SCB_DESC];
	काष्ठा dsp_scb_descriptor * the_null_scb;

	/* Task's descriptors */
	पूर्णांक ntask;
	काष्ठा dsp_task_descriptor tasks[DSP_MAX_TASK_DESC];

	/* SPDIF status */
	पूर्णांक spdअगर_status_out;
	पूर्णांक spdअगर_status_in;
	u16 spdअगर_input_volume_right;
	u16 spdअगर_input_volume_left;
	/* spdअगर channel status,
	   left right and user validity bits */
	अचिन्हित पूर्णांक spdअगर_csuv_शेष;
	अचिन्हित पूर्णांक spdअगर_csuv_stream;

	/* SPDIF input sample rate converter */
	काष्ठा dsp_scb_descriptor * spdअगर_in_src;
	/* SPDIF input asynch. receiver */
	काष्ठा dsp_scb_descriptor * asynch_rx_scb;

	/* Capture record mixer SCB */
	काष्ठा dsp_scb_descriptor * record_mixer_scb;
    
	/* CODEC input SCB */
	काष्ठा dsp_scb_descriptor * codec_in_scb;

	/* reference snooper */
	काष्ठा dsp_scb_descriptor * ref_snoop_scb;

	/* SPDIF output  PCM reference  */
	काष्ठा dsp_scb_descriptor * spdअगर_pcm_input_scb;

	/* asynch TX task */
	काष्ठा dsp_scb_descriptor * asynch_tx_scb;

	/* record sources */
	काष्ठा dsp_scb_descriptor * pcm_input;
	काष्ठा dsp_scb_descriptor * adc_input;

	पूर्णांक spdअगर_in_sample_rate;
पूर्ण;

#पूर्ण_अगर /* __DSP_SPOS_H__ */
