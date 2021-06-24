<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * skl-tplg-पूर्णांकerface.h - Intel DSP FW निजी data पूर्णांकerface
 *
 * Copyright (C) 2015 Intel Corp
 * Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *	    Nilofer, Samreen <samreen.nilofer@पूर्णांकel.com>
 */

#अगर_अघोषित __HDA_TPLG_INTERFACE_H__
#घोषणा __HDA_TPLG_INTERFACE_H__

#समावेश <linux/types.h>

/*
 * Default types range from 0~12. type can range from 0 to 0xff
 * SST types start at higher to aव्योम any overlapping in future
 */
#घोषणा SKL_CONTROL_TYPE_BYTE_TLV	0x100
#घोषणा SKL_CONTROL_TYPE_MIC_SELECT	0x102
#घोषणा SKL_CONTROL_TYPE_MULTI_IO_SELECT	0x103
#घोषणा SKL_CONTROL_TYPE_MULTI_IO_SELECT_DMIC	0x104

#घोषणा HDA_SST_CFG_MAX	900 /* size of copier cfg*/
#घोषणा MAX_IN_QUEUE 8
#घोषणा MAX_OUT_QUEUE 8

#घोषणा SKL_UUID_STR_SZ 40
/* Event types goes here */
/* Reserve event type 0 क्रम no event handlers */
क्रमागत skl_event_types अणु
	SKL_EVENT_NONE = 0,
	SKL_MIXER_EVENT,
	SKL_MUX_EVENT,
	SKL_VMIXER_EVENT,
	SKL_PGA_EVENT
पूर्ण;

/**
 * क्रमागत skl_ch_cfg - channel configuration
 *
 * @SKL_CH_CFG_MONO:	One channel only
 * @SKL_CH_CFG_STEREO:	L & R
 * @SKL_CH_CFG_2_1:	L, R & LFE
 * @SKL_CH_CFG_3_0:	L, C & R
 * @SKL_CH_CFG_3_1:	L, C, R & LFE
 * @SKL_CH_CFG_QUATRO:	L, R, Ls & Rs
 * @SKL_CH_CFG_4_0:	L, C, R & Cs
 * @SKL_CH_CFG_5_0:	L, C, R, Ls & Rs
 * @SKL_CH_CFG_5_1:	L, C, R, Ls, Rs & LFE
 * @SKL_CH_CFG_DUAL_MONO: One channel replicated in two
 * @SKL_CH_CFG_I2S_DUAL_STEREO_0: Stereo(L,R) in 4 slots, 1st stream:[ L, R, -, - ]
 * @SKL_CH_CFG_I2S_DUAL_STEREO_1: Stereo(L,R) in 4 slots, 2nd stream:[ -, -, L, R ]
 * @SKL_CH_CFG_INVALID:	Invalid
 */
क्रमागत skl_ch_cfg अणु
	SKL_CH_CFG_MONO = 0,
	SKL_CH_CFG_STEREO = 1,
	SKL_CH_CFG_2_1 = 2,
	SKL_CH_CFG_3_0 = 3,
	SKL_CH_CFG_3_1 = 4,
	SKL_CH_CFG_QUATRO = 5,
	SKL_CH_CFG_4_0 = 6,
	SKL_CH_CFG_5_0 = 7,
	SKL_CH_CFG_5_1 = 8,
	SKL_CH_CFG_DUAL_MONO = 9,
	SKL_CH_CFG_I2S_DUAL_STEREO_0 = 10,
	SKL_CH_CFG_I2S_DUAL_STEREO_1 = 11,
	SKL_CH_CFG_4_CHANNEL = 12,
	SKL_CH_CFG_INVALID
पूर्ण;

क्रमागत skl_module_type अणु
	SKL_MODULE_TYPE_MIXER = 0,
	SKL_MODULE_TYPE_COPIER,
	SKL_MODULE_TYPE_UPDWMIX,
	SKL_MODULE_TYPE_SRCINT,
	SKL_MODULE_TYPE_ALGO,
	SKL_MODULE_TYPE_BASE_OUTFMT,
	SKL_MODULE_TYPE_KPB,
	SKL_MODULE_TYPE_MIC_SELECT,
पूर्ण;

क्रमागत skl_core_affinity अणु
	SKL_AFFINITY_CORE_0 = 0,
	SKL_AFFINITY_CORE_1,
	SKL_AFFINITY_CORE_MAX
पूर्ण;

क्रमागत skl_pipe_conn_type अणु
	SKL_PIPE_CONN_TYPE_NONE = 0,
	SKL_PIPE_CONN_TYPE_FE,
	SKL_PIPE_CONN_TYPE_BE
पूर्ण;

क्रमागत skl_hw_conn_type अणु
	SKL_CONN_NONE = 0,
	SKL_CONN_SOURCE = 1,
	SKL_CONN_SINK = 2
पूर्ण;

क्रमागत skl_dev_type अणु
	SKL_DEVICE_BT = 0x0,
	SKL_DEVICE_DMIC = 0x1,
	SKL_DEVICE_I2S = 0x2,
	SKL_DEVICE_SLIMBUS = 0x3,
	SKL_DEVICE_HDALINK = 0x4,
	SKL_DEVICE_HDAHOST = 0x5,
	SKL_DEVICE_NONE
पूर्ण;

/**
 * क्रमागत skl_पूर्णांकerleaving - पूर्णांकerleaving style
 *
 * @SKL_INTERLEAVING_PER_CHANNEL: [s1_ch1...s1_chN,...,sM_ch1...sM_chN]
 * @SKL_INTERLEAVING_PER_SAMPLE: [s1_ch1...sM_ch1,...,s1_chN...sM_chN]
 */
क्रमागत skl_पूर्णांकerleaving अणु
	SKL_INTERLEAVING_PER_CHANNEL = 0,
	SKL_INTERLEAVING_PER_SAMPLE = 1,
पूर्ण;

क्रमागत skl_sample_type अणु
	SKL_SAMPLE_TYPE_INT_MSB = 0,
	SKL_SAMPLE_TYPE_INT_LSB = 1,
	SKL_SAMPLE_TYPE_INT_SIGNED = 2,
	SKL_SAMPLE_TYPE_INT_UNSIGNED = 3,
	SKL_SAMPLE_TYPE_FLOAT = 4
पूर्ण;

क्रमागत module_pin_type अणु
	/* All pins of the module takes same PCM inमाला_दो or outमाला_दो
	* e.g. mixout
	*/
	SKL_PIN_TYPE_HOMOGENEOUS,
	/* All pins of the module takes dअगरferent PCM inमाला_दो or outमाला_दो
	* e.g mux
	*/
	SKL_PIN_TYPE_HETEROGENEOUS,
पूर्ण;

क्रमागत skl_module_param_type अणु
	SKL_PARAM_DEFAULT = 0,
	SKL_PARAM_INIT,
	SKL_PARAM_SET,
	SKL_PARAM_BIND
पूर्ण;

काष्ठा skl_dfw_algo_data अणु
	__u32 set_params:2;
	__u32 rsvd:30;
	__u32 param_id;
	__u32 max;
	अक्षर params[0];
पूर्ण __packed;

क्रमागत skl_tkn_dir अणु
	SKL_सूची_IN,
	SKL_सूची_OUT
पूर्ण;

क्रमागत skl_tuple_type अणु
	SKL_TYPE_TUPLE,
	SKL_TYPE_DATA
पूर्ण;

/* v4 configuration data */

काष्ठा skl_dfw_v4_module_pin अणु
	__u16 module_id;
	__u16 instance_id;
पूर्ण __packed;

काष्ठा skl_dfw_v4_module_fmt अणु
	__u32 channels;
	__u32 freq;
	__u32 bit_depth;
	__u32 valid_bit_depth;
	__u32 ch_cfg;
	__u32 पूर्णांकerleaving_style;
	__u32 sample_type;
	__u32 ch_map;
पूर्ण __packed;

काष्ठा skl_dfw_v4_module_caps अणु
	__u32 set_params:2;
	__u32 rsvd:30;
	__u32 param_id;
	__u32 caps_size;
	__u32 caps[HDA_SST_CFG_MAX];
पूर्ण __packed;

काष्ठा skl_dfw_v4_pipe अणु
	__u8 pipe_id;
	__u8 pipe_priority;
	__u16 conn_type:4;
	__u16 rsvd:4;
	__u16 memory_pages:8;
पूर्ण __packed;

काष्ठा skl_dfw_v4_module अणु
	अक्षर uuid[SKL_UUID_STR_SZ];

	__u16 module_id;
	__u16 instance_id;
	__u32 max_mcps;
	__u32 mem_pages;
	__u32 obs;
	__u32 ibs;
	__u32 vbus_id;

	__u32 max_in_queue:8;
	__u32 max_out_queue:8;
	__u32 समय_slot:8;
	__u32 core_id:4;
	__u32 rsvd1:4;

	__u32 module_type:8;
	__u32 conn_type:4;
	__u32 dev_type:4;
	__u32 hw_conn_type:4;
	__u32 rsvd2:12;

	__u32 params_fixup:8;
	__u32 converter:8;
	__u32 input_pin_type:1;
	__u32 output_pin_type:1;
	__u32 is_dynamic_in_pin:1;
	__u32 is_dynamic_out_pin:1;
	__u32 is_loadable:1;
	__u32 rsvd3:11;

	काष्ठा skl_dfw_v4_pipe pipe;
	काष्ठा skl_dfw_v4_module_fmt in_fmt[MAX_IN_QUEUE];
	काष्ठा skl_dfw_v4_module_fmt out_fmt[MAX_OUT_QUEUE];
	काष्ठा skl_dfw_v4_module_pin in_pin[MAX_IN_QUEUE];
	काष्ठा skl_dfw_v4_module_pin out_pin[MAX_OUT_QUEUE];
	काष्ठा skl_dfw_v4_module_caps caps;
पूर्ण __packed;

#पूर्ण_अगर
