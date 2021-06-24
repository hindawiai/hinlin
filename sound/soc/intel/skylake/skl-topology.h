<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  skl_topology.h - Intel HDA Platक्रमm topology header file
 *
 *  Copyright (C) 2014-15 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#अगर_अघोषित __SKL_TOPOLOGY_H__
#घोषणा __SKL_TOPOLOGY_H__

#समावेश <linux/types.h>

#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/soc.h>
#समावेश <uapi/sound/skl-tplg-पूर्णांकerface.h>
#समावेश "skl.h"

#घोषणा BITS_PER_BYTE 8
#घोषणा MAX_TS_GROUPS 8
#घोषणा MAX_DMIC_TS_GROUPS 4
#घोषणा MAX_FIXED_DMIC_PARAMS_SIZE 727

/* Maximum number of coefficients up करोwn mixer module */
#घोषणा UP_DOWN_MIXER_MAX_COEFF		8

#घोषणा MODULE_MAX_IN_PINS	8
#घोषणा MODULE_MAX_OUT_PINS	8

#घोषणा SKL_MIC_CH_SUPPORT	4
#घोषणा SKL_MIC_MAX_CH_SUPPORT	8
#घोषणा SKL_DEFAULT_MIC_SEL_GAIN	0x3FF
#घोषणा SKL_MIC_SEL_SWITCH	0x3

#घोषणा SKL_OUTPUT_PIN		0
#घोषणा SKL_INPUT_PIN		1
#घोषणा SKL_MAX_PATH_CONFIGS	8
#घोषणा SKL_MAX_MODULES_IN_PIPE	8
#घोषणा SKL_MAX_MODULE_FORMATS		32
#घोषणा SKL_MAX_MODULE_RESOURCES	32

क्रमागत skl_channel_index अणु
	SKL_CHANNEL_LEFT = 0,
	SKL_CHANNEL_RIGHT = 1,
	SKL_CHANNEL_CENTER = 2,
	SKL_CHANNEL_LEFT_SURROUND = 3,
	SKL_CHANNEL_CENTER_SURROUND = 3,
	SKL_CHANNEL_RIGHT_SURROUND = 4,
	SKL_CHANNEL_LFE = 7,
	SKL_CHANNEL_INVALID = 0xF,
पूर्ण;

क्रमागत skl_bitdepth अणु
	SKL_DEPTH_8BIT = 8,
	SKL_DEPTH_16BIT = 16,
	SKL_DEPTH_24BIT = 24,
	SKL_DEPTH_32BIT = 32,
	SKL_DEPTH_INVALID
पूर्ण;


क्रमागत skl_s_freq अणु
	SKL_FS_8000 = 8000,
	SKL_FS_11025 = 11025,
	SKL_FS_12000 = 12000,
	SKL_FS_16000 = 16000,
	SKL_FS_22050 = 22050,
	SKL_FS_24000 = 24000,
	SKL_FS_32000 = 32000,
	SKL_FS_44100 = 44100,
	SKL_FS_48000 = 48000,
	SKL_FS_64000 = 64000,
	SKL_FS_88200 = 88200,
	SKL_FS_96000 = 96000,
	SKL_FS_128000 = 128000,
	SKL_FS_176400 = 176400,
	SKL_FS_192000 = 192000,
	SKL_FS_INVALID
पूर्ण;

क्रमागत skl_widget_type अणु
	SKL_WIDGET_VMIXER = 1,
	SKL_WIDGET_MIXER = 2,
	SKL_WIDGET_PGA = 3,
	SKL_WIDGET_MUX = 4
पूर्ण;

काष्ठा skl_audio_data_क्रमmat अणु
	क्रमागत skl_s_freq s_freq;
	क्रमागत skl_bitdepth bit_depth;
	u32 channel_map;
	क्रमागत skl_ch_cfg ch_cfg;
	क्रमागत skl_पूर्णांकerleaving पूर्णांकerleaving;
	u8 number_of_channels;
	u8 valid_bit_depth;
	u8 sample_type;
	u8 reserved;
पूर्ण __packed;

काष्ठा skl_base_cfg अणु
	u32 cpc;
	u32 ibs;
	u32 obs;
	u32 is_pages;
	काष्ठा skl_audio_data_क्रमmat audio_fmt;
पूर्ण;

काष्ठा skl_cpr_gtw_cfg अणु
	u32 node_id;
	u32 dma_buffer_size;
	u32 config_length;
	/* not mandatory; required only क्रम DMIC/I2S */
	u32 config_data[1];
पूर्ण __packed;

काष्ठा skl_dma_control अणु
	u32 node_id;
	u32 config_length;
	u32 config_data[];
पूर्ण __packed;

काष्ठा skl_cpr_cfg अणु
	काष्ठा skl_base_cfg base_cfg;
	काष्ठा skl_audio_data_क्रमmat out_fmt;
	u32 cpr_feature_mask;
	काष्ठा skl_cpr_gtw_cfg gtw_cfg;
पूर्ण __packed;

काष्ठा skl_cpr_pin_fmt अणु
	u32 sink_id;
	काष्ठा skl_audio_data_क्रमmat src_fmt;
	काष्ठा skl_audio_data_क्रमmat dst_fmt;
पूर्ण __packed;

काष्ठा skl_src_module_cfg अणु
	काष्ठा skl_base_cfg base_cfg;
	क्रमागत skl_s_freq src_cfg;
पूर्ण __packed;

काष्ठा skl_up_करोwn_mixer_cfg अणु
	काष्ठा skl_base_cfg base_cfg;
	क्रमागत skl_ch_cfg out_ch_cfg;
	/* This should be set to 1 अगर user coefficients are required */
	u32 coeff_sel;
	/* Pass the user coeff in this array */
	s32 coeff[UP_DOWN_MIXER_MAX_COEFF];
	u32 ch_map;
पूर्ण __packed;

काष्ठा skl_algo_cfg अणु
	काष्ठा skl_base_cfg  base_cfg;
	अक्षर params[];
पूर्ण __packed;

काष्ठा skl_base_outfmt_cfg अणु
	काष्ठा skl_base_cfg base_cfg;
	काष्ठा skl_audio_data_क्रमmat out_fmt;
पूर्ण __packed;

क्रमागत skl_dma_type अणु
	SKL_DMA_HDA_HOST_OUTPUT_CLASS = 0,
	SKL_DMA_HDA_HOST_INPUT_CLASS = 1,
	SKL_DMA_HDA_HOST_INOUT_CLASS = 2,
	SKL_DMA_HDA_LINK_OUTPUT_CLASS = 8,
	SKL_DMA_HDA_LINK_INPUT_CLASS = 9,
	SKL_DMA_HDA_LINK_INOUT_CLASS = 0xA,
	SKL_DMA_DMIC_LINK_INPUT_CLASS = 0xB,
	SKL_DMA_I2S_LINK_OUTPUT_CLASS = 0xC,
	SKL_DMA_I2S_LINK_INPUT_CLASS = 0xD,
पूर्ण;

जोड़ skl_ssp_dma_node अणु
	u8 val;
	काष्ठा अणु
		u8 समय_slot_index:4;
		u8 i2s_instance:4;
	पूर्ण dma_node;
पूर्ण;

जोड़ skl_connector_node_id अणु
	u32 val;
	काष्ठा अणु
		u32 vindex:8;
		u32 dma_type:4;
		u32 rsvd:20;
	पूर्ण node;
पूर्ण;

काष्ठा skl_module_fmt अणु
	u32 channels;
	u32 s_freq;
	u32 bit_depth;
	u32 valid_bit_depth;
	u32 ch_cfg;
	u32 पूर्णांकerleaving_style;
	u32 sample_type;
	u32 ch_map;
पूर्ण;

काष्ठा skl_module_cfg;

काष्ठा skl_mod_inst_map अणु
	u16 mod_id;
	u16 inst_id;
पूर्ण;

काष्ठा skl_uuid_inst_map अणु
	u16 inst_id;
	u16 reserved;
	guid_t mod_uuid;
पूर्ण __packed;

काष्ठा skl_kpb_params अणु
	u32 num_modules;
	जोड़ अणु
		काष्ठा skl_mod_inst_map map[0];
		काष्ठा skl_uuid_inst_map map_uuid[0];
	पूर्ण u;
पूर्ण;

काष्ठा skl_module_inst_id अणु
	guid_t mod_uuid;
	पूर्णांक module_id;
	u32 instance_id;
	पूर्णांक pvt_id;
पूर्ण;

क्रमागत skl_module_pin_state अणु
	SKL_PIN_UNBIND = 0,
	SKL_PIN_BIND_DONE = 1,
पूर्ण;

काष्ठा skl_module_pin अणु
	काष्ठा skl_module_inst_id id;
	bool is_dynamic;
	bool in_use;
	क्रमागत skl_module_pin_state pin_state;
	काष्ठा skl_module_cfg *tgt_mcfg;
पूर्ण;

काष्ठा skl_specअगरic_cfg अणु
	u32 set_params;
	u32 param_id;
	u32 caps_size;
	u32 *caps;
पूर्ण;

क्रमागत skl_pipe_state अणु
	SKL_PIPE_INVALID = 0,
	SKL_PIPE_CREATED = 1,
	SKL_PIPE_PAUSED = 2,
	SKL_PIPE_STARTED = 3,
	SKL_PIPE_RESET = 4
पूर्ण;

काष्ठा skl_pipe_module अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा list_head node;
पूर्ण;

काष्ठा skl_pipe_params अणु
	u8 host_dma_id;
	u8 link_dma_id;
	u32 ch;
	u32 s_freq;
	u32 s_fmt;
	u8 linktype;
	snd_pcm_क्रमmat_t क्रमmat;
	पूर्णांक link_index;
	पूर्णांक stream;
	अचिन्हित पूर्णांक host_bps;
	अचिन्हित पूर्णांक link_bps;
पूर्ण;

काष्ठा skl_pipe_fmt अणु
	u32 freq;
	u8 channels;
	u8 bps;
पूर्ण;

काष्ठा skl_pipe_mcfg अणु
	u8 res_idx;
	u8 fmt_idx;
पूर्ण;

काष्ठा skl_path_config अणु
	u8 mem_pages;
	काष्ठा skl_pipe_fmt in_fmt;
	काष्ठा skl_pipe_fmt out_fmt;
पूर्ण;

काष्ठा skl_pipe अणु
	u8 ppl_id;
	u8 pipe_priority;
	u16 conn_type;
	u32 memory_pages;
	u8 lp_mode;
	काष्ठा skl_pipe_params *p_params;
	क्रमागत skl_pipe_state state;
	u8 direction;
	u8 cur_config_idx;
	u8 nr_cfgs;
	काष्ठा skl_path_config configs[SKL_MAX_PATH_CONFIGS];
	काष्ठा list_head w_list;
	bool passthru;
	u32 pipe_config_idx;
पूर्ण;

क्रमागत skl_module_state अणु
	SKL_MODULE_UNINIT = 0,
	SKL_MODULE_LOADED = 1,
	SKL_MODULE_INIT_DONE = 2,
	SKL_MODULE_BIND_DONE = 3,
	SKL_MODULE_UNLOADED = 4,
पूर्ण;

क्रमागत d0i3_capability अणु
	SKL_D0I3_NONE = 0,
	SKL_D0I3_STREAMING = 1,
	SKL_D0I3_NON_STREAMING = 2,
पूर्ण;

काष्ठा skl_module_pin_fmt अणु
	u8 id;
	काष्ठा skl_module_fmt fmt;
पूर्ण;

काष्ठा skl_module_अगरace अणु
	u8 fmt_idx;
	u8 nr_in_fmt;
	u8 nr_out_fmt;
	काष्ठा skl_module_pin_fmt inमाला_दो[MAX_IN_QUEUE];
	काष्ठा skl_module_pin_fmt outमाला_दो[MAX_OUT_QUEUE];
पूर्ण;

काष्ठा skl_module_pin_resources अणु
	u8 pin_index;
	u32 buf_size;
पूर्ण;

काष्ठा skl_module_res अणु
	u8 id;
	u32 is_pages;
	u32 ibs;
	u32 obs;
	u32 dma_buffer_size;
	u32 cpc;
	u8 nr_input_pins;
	u8 nr_output_pins;
	काष्ठा skl_module_pin_resources input[MAX_IN_QUEUE];
	काष्ठा skl_module_pin_resources output[MAX_OUT_QUEUE];
पूर्ण;

काष्ठा skl_module अणु
	guid_t uuid;
	u8 loadable;
	u8 input_pin_type;
	u8 output_pin_type;
	u8 max_input_pins;
	u8 max_output_pins;
	u8 nr_resources;
	u8 nr_पूर्णांकerfaces;
	काष्ठा skl_module_res resources[SKL_MAX_MODULE_RESOURCES];
	काष्ठा skl_module_अगरace क्रमmats[SKL_MAX_MODULE_FORMATS];
पूर्ण;

काष्ठा skl_module_cfg अणु
	u8 guid[16];
	काष्ठा skl_module_inst_id id;
	काष्ठा skl_module *module;
	पूर्णांक res_idx;
	पूर्णांक fmt_idx;
	u8 करोमुख्य;
	bool homogenous_inमाला_दो;
	bool homogenous_outमाला_दो;
	काष्ठा skl_module_fmt in_fmt[MODULE_MAX_IN_PINS];
	काष्ठा skl_module_fmt out_fmt[MODULE_MAX_OUT_PINS];
	u8 max_in_queue;
	u8 max_out_queue;
	u8 in_queue_mask;
	u8 out_queue_mask;
	u8 in_queue;
	u8 out_queue;
	u8 is_loadable;
	u8 core_id;
	u8 dev_type;
	u8 dma_id;
	u8 समय_slot;
	u8 dmic_ch_combo_index;
	u32 dmic_ch_type;
	u32 params_fixup;
	u32 converter;
	u32 vbus_id;
	u32 mem_pages;
	क्रमागत d0i3_capability d0i3_caps;
	u32 dma_buffer_size; /* in milli seconds */
	काष्ठा skl_module_pin *m_in_pin;
	काष्ठा skl_module_pin *m_out_pin;
	क्रमागत skl_module_type m_type;
	क्रमागत skl_hw_conn_type  hw_conn_type;
	क्रमागत skl_module_state m_state;
	काष्ठा skl_pipe *pipe;
	काष्ठा skl_specअगरic_cfg क्रमmats_config;
	काष्ठा skl_pipe_mcfg mod_cfg[SKL_MAX_MODULES_IN_PIPE];
पूर्ण;

काष्ठा skl_algo_data अणु
	u32 param_id;
	u32 set_params;
	u32 max;
	u32 size;
	अक्षर *params;
पूर्ण;

काष्ठा skl_pipeline अणु
	काष्ठा skl_pipe *pipe;
	काष्ठा list_head node;
पूर्ण;

काष्ठा skl_module_deferred_bind अणु
	काष्ठा skl_module_cfg *src;
	काष्ठा skl_module_cfg *dst;
	काष्ठा list_head node;
पूर्ण;

काष्ठा skl_mic_sel_config अणु
	u16 mic_चयन;
	u16 flags;
	u16 blob[SKL_MIC_MAX_CH_SUPPORT][SKL_MIC_MAX_CH_SUPPORT];
पूर्ण __packed;

क्रमागत skl_channel अणु
	SKL_CH_MONO = 1,
	SKL_CH_STEREO = 2,
	SKL_CH_TRIO = 3,
	SKL_CH_QUATRO = 4,
पूर्ण;

अटल अंतरभूत काष्ठा skl_dev *get_skl_ctx(काष्ठा device *dev)
अणु
	काष्ठा hdac_bus *bus = dev_get_drvdata(dev);

	वापस bus_to_skl(bus);
पूर्ण

पूर्णांक skl_tplg_be_update_params(काष्ठा snd_soc_dai *dai,
	काष्ठा skl_pipe_params *params);
पूर्णांक skl_dsp_set_dma_control(काष्ठा skl_dev *skl, u32 *caps,
			u32 caps_size, u32 node_id);
व्योम skl_tplg_set_be_dmic_config(काष्ठा snd_soc_dai *dai,
	काष्ठा skl_pipe_params *params, पूर्णांक stream);
पूर्णांक skl_tplg_init(काष्ठा snd_soc_component *component,
				काष्ठा hdac_bus *bus);
व्योम skl_tplg_निकास(काष्ठा snd_soc_component *component,
				काष्ठा hdac_bus *bus);
काष्ठा skl_module_cfg *skl_tplg_fe_get_cpr_module(
		काष्ठा snd_soc_dai *dai, पूर्णांक stream);
पूर्णांक skl_tplg_update_pipe_params(काष्ठा device *dev,
		काष्ठा skl_module_cfg *mconfig, काष्ठा skl_pipe_params *params);

व्योम skl_tplg_d0i3_get(काष्ठा skl_dev *skl, क्रमागत d0i3_capability caps);
व्योम skl_tplg_d0i3_put(काष्ठा skl_dev *skl, क्रमागत d0i3_capability caps);

पूर्णांक skl_create_pipeline(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_run_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_छोड़ो_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_delete_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_stop_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_reset_pipe(काष्ठा skl_dev *skl, काष्ठा skl_pipe *pipe);

पूर्णांक skl_init_module(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg *mconfig);

पूर्णांक skl_bind_modules(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg
	*src_mcfg, काष्ठा skl_module_cfg *dst_mcfg);

पूर्णांक skl_unbind_modules(काष्ठा skl_dev *skl, काष्ठा skl_module_cfg
	*src_mcfg, काष्ठा skl_module_cfg *dst_mcfg);

पूर्णांक skl_set_module_params(काष्ठा skl_dev *skl, u32 *params, पूर्णांक size,
			u32 param_id, काष्ठा skl_module_cfg *mcfg);
पूर्णांक skl_get_module_params(काष्ठा skl_dev *skl, u32 *params, पूर्णांक size,
			  u32 param_id, काष्ठा skl_module_cfg *mcfg);

काष्ठा skl_module_cfg *skl_tplg_be_get_cpr_module(काष्ठा snd_soc_dai *dai,
								पूर्णांक stream);
क्रमागत skl_bitdepth skl_get_bit_depth(पूर्णांक params);
पूर्णांक skl_pcm_host_dma_prepare(काष्ठा device *dev,
			काष्ठा skl_pipe_params *params);
पूर्णांक skl_pcm_link_dma_prepare(काष्ठा device *dev,
			काष्ठा skl_pipe_params *params);

पूर्णांक skl_dai_load(काष्ठा snd_soc_component *cmp, पूर्णांक index,
		काष्ठा snd_soc_dai_driver *dai_drv,
		काष्ठा snd_soc_tplg_pcm *pcm, काष्ठा snd_soc_dai *dai);
व्योम skl_tplg_add_moduleid_in_bind_params(काष्ठा skl_dev *skl,
				काष्ठा snd_soc_dapm_widget *w);
#पूर्ण_अगर
