<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 * Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
 *         Keyon Jie <yang.jie@linux.पूर्णांकel.com>
 */

/*
 * Topology IDs and tokens.
 *
 * ** MUST BE ALIGNED WITH TOPOLOGY CONFIGURATION TOKEN VALUES **
 */

#अगर_अघोषित __INCLUDE_UAPI_SOF_TOPOLOGY_H__
#घोषणा __INCLUDE_UAPI_SOF_TOPOLOGY_H__

/*
 * Kcontrol IDs
 */
#घोषणा SOF_TPLG_KCTL_VOL_ID	256
#घोषणा SOF_TPLG_KCTL_ENUM_ID	257
#घोषणा SOF_TPLG_KCTL_BYTES_ID	258
#घोषणा SOF_TPLG_KCTL_SWITCH_ID	259
#घोषणा SOF_TPLG_KCTL_BYTES_VOLATILE_RO 260
#घोषणा SOF_TPLG_KCTL_BYTES_VOLATILE_RW 261
#घोषणा SOF_TPLG_KCTL_BYTES_WO_ID 262

/*
 * Tokens - must match values in topology configurations
 */

/* buffers */
#घोषणा SOF_TKN_BUF_SIZE			100
#घोषणा SOF_TKN_BUF_CAPS			101

/* DAI */
/* Token retired with ABI 3.2, करो not use क्रम new capabilities
 * #घोषणा	SOF_TKN_DAI_DMAC_CONFIG			153
 */
#घोषणा SOF_TKN_DAI_TYPE			154
#घोषणा SOF_TKN_DAI_INDEX			155
#घोषणा SOF_TKN_DAI_सूचीECTION			156

/* scheduling */
#घोषणा SOF_TKN_SCHED_PERIOD			200
#घोषणा SOF_TKN_SCHED_PRIORITY			201
#घोषणा SOF_TKN_SCHED_MIPS			202
#घोषणा SOF_TKN_SCHED_CORE			203
#घोषणा SOF_TKN_SCHED_FRAMES			204
#घोषणा SOF_TKN_SCHED_TIME_DOMAIN		205

/* volume */
#घोषणा SOF_TKN_VOLUME_RAMP_STEP_TYPE		250
#घोषणा SOF_TKN_VOLUME_RAMP_STEP_MS		251

/* SRC */
#घोषणा SOF_TKN_SRC_RATE_IN			300
#घोषणा SOF_TKN_SRC_RATE_OUT			301

/* ASRC */
#घोषणा SOF_TKN_ASRC_RATE_IN			320
#घोषणा SOF_TKN_ASRC_RATE_OUT			321
#घोषणा SOF_TKN_ASRC_ASYNCHRONOUS_MODE		322
#घोषणा SOF_TKN_ASRC_OPERATION_MODE		323

/* PCM */
#घोषणा SOF_TKN_PCM_DMAC_CONFIG			353

/* Generic components */
#घोषणा SOF_TKN_COMP_PERIOD_SINK_COUNT		400
#घोषणा SOF_TKN_COMP_PERIOD_SOURCE_COUNT	401
#घोषणा SOF_TKN_COMP_FORMAT			402
/* Token retired with ABI 3.2, करो not use क्रम new capabilities
 * #घोषणा SOF_TKN_COMP_PRELOAD_COUNT		403
 */
#घोषणा SOF_TKN_COMP_CORE_ID			404
#घोषणा SOF_TKN_COMP_UUID                       405

/* SSP */
#घोषणा SOF_TKN_INTEL_SSP_CLKS_CONTROL		500
#घोषणा SOF_TKN_INTEL_SSP_MCLK_ID		501
#घोषणा SOF_TKN_INTEL_SSP_SAMPLE_BITS		502
#घोषणा SOF_TKN_INTEL_SSP_FRAME_PULSE_WIDTH	503
#घोषणा SOF_TKN_INTEL_SSP_QUIRKS		504
#घोषणा SOF_TKN_INTEL_SSP_TDM_PADDING_PER_SLOT	505
#घोषणा SOF_TKN_INTEL_SSP_BCLK_DELAY		506

/* DMIC */
#घोषणा SOF_TKN_INTEL_DMIC_DRIVER_VERSION	600
#घोषणा SOF_TKN_INTEL_DMIC_CLK_MIN		601
#घोषणा SOF_TKN_INTEL_DMIC_CLK_MAX		602
#घोषणा SOF_TKN_INTEL_DMIC_DUTY_MIN		603
#घोषणा SOF_TKN_INTEL_DMIC_DUTY_MAX		604
#घोषणा SOF_TKN_INTEL_DMIC_NUM_PDM_ACTIVE	605
#घोषणा SOF_TKN_INTEL_DMIC_SAMPLE_RATE		608
#घोषणा SOF_TKN_INTEL_DMIC_FIFO_WORD_LENGTH	609
#घोषणा SOF_TKN_INTEL_DMIC_UNMUTE_RAMP_TIME_MS  610

/* DMIC PDM */
#घोषणा SOF_TKN_INTEL_DMIC_PDM_CTRL_ID		700
#घोषणा SOF_TKN_INTEL_DMIC_PDM_MIC_A_Enable	701
#घोषणा SOF_TKN_INTEL_DMIC_PDM_MIC_B_Enable	702
#घोषणा SOF_TKN_INTEL_DMIC_PDM_POLARITY_A	703
#घोषणा SOF_TKN_INTEL_DMIC_PDM_POLARITY_B	704
#घोषणा SOF_TKN_INTEL_DMIC_PDM_CLK_EDGE		705
#घोषणा SOF_TKN_INTEL_DMIC_PDM_SKEW		706

/* Tone */
#घोषणा SOF_TKN_TONE_SAMPLE_RATE		800

/* Processing Components */
#घोषणा SOF_TKN_PROCESS_TYPE                    900

/* क्रम backward compatibility */
#घोषणा SOF_TKN_EFFECT_TYPE	SOF_TKN_PROCESS_TYPE

/* SAI */
#घोषणा SOF_TKN_IMX_SAI_MCLK_ID			1000

/* ESAI */
#घोषणा SOF_TKN_IMX_ESAI_MCLK_ID		1100

/* Stream */
#घोषणा SOF_TKN_STREAM_PLAYBACK_COMPATIBLE_D0I3	1200
#घोषणा SOF_TKN_STREAM_CAPTURE_COMPATIBLE_D0I3	1201

/* Led control क्रम mute चयनes */
#घोषणा SOF_TKN_MUTE_LED_USE			1300
#घोषणा SOF_TKN_MUTE_LED_सूचीECTION		1301

/* ALH */
#घोषणा SOF_TKN_INTEL_ALH_RATE			1400
#घोषणा SOF_TKN_INTEL_ALH_CH			1401

/* HDA */
#घोषणा SOF_TKN_INTEL_HDA_RATE			1500
#घोषणा SOF_TKN_INTEL_HDA_CH			1501

#पूर्ण_अगर
