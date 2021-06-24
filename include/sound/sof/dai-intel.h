<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_DAI_INTEL_H__
#घोषणा __INCLUDE_SOUND_SOF_DAI_INTEL_H__

#समावेश <sound/sof/header.h>

 /* ssc1: TINTE */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_TINTE		(1 << 0)
 /* ssc1: PINTE */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_PINTE		(1 << 1)
 /* ssc2: SMTATF */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_SMTATF		(1 << 2)
 /* ssc2: MMRATF */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_MMRATF		(1 << 3)
 /* ssc2: PSPSTWFDFD */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_PSPSTWFDFD	(1 << 4)
 /* ssc2: PSPSRWFDFD */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_PSPSRWFDFD	(1 << 5)
/* ssc1: LBM */
#घोषणा SOF_DAI_INTEL_SSP_QUIRK_LBM		(1 << 6)

 /* here is the possibility to define others aux macros */

#घोषणा SOF_DAI_INTEL_SSP_FRAME_PULSE_WIDTH_MAX		38
#घोषणा SOF_DAI_INTEL_SSP_SLOT_PADDING_MAX		31

/* SSP घड़ीs control settings
 *
 * Macros क्रम clks_control field in sof_ipc_dai_ssp_params काष्ठा.
 */

/* mclk 0 disable */
#घोषणा SOF_DAI_INTEL_SSP_MCLK_0_DISABLE		BIT(0)
/* mclk 1 disable */
#घोषणा SOF_DAI_INTEL_SSP_MCLK_1_DISABLE		BIT(1)
/* mclk keep active */
#घोषणा SOF_DAI_INTEL_SSP_CLKCTRL_MCLK_KA		BIT(2)
/* bclk keep active */
#घोषणा SOF_DAI_INTEL_SSP_CLKCTRL_BCLK_KA		BIT(3)
/* fs keep active */
#घोषणा SOF_DAI_INTEL_SSP_CLKCTRL_FS_KA			BIT(4)
/* bclk idle */
#घोषणा SOF_DAI_INTEL_SSP_CLKCTRL_BCLK_IDLE_HIGH	BIT(5)

/* DMIC max. four controllers क्रम eight microphone channels */
#घोषणा SOF_DAI_INTEL_DMIC_NUM_CTRL			4

/* SSP Configuration Request - SOF_IPC_DAI_SSP_CONFIG */
काष्ठा sof_ipc_dai_ssp_params अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक16_t reserved1;
	uपूर्णांक16_t mclk_id;

	uपूर्णांक32_t mclk_rate;	/* mclk frequency in Hz */
	uपूर्णांक32_t fsync_rate;	/* fsync frequency in Hz */
	uपूर्णांक32_t bclk_rate;	/* bclk frequency in Hz */

	/* TDM */
	uपूर्णांक32_t tdm_slots;
	uपूर्णांक32_t rx_slots;
	uपूर्णांक32_t tx_slots;

	/* data */
	uपूर्णांक32_t sample_valid_bits;
	uपूर्णांक16_t tdm_slot_width;
	uपूर्णांक16_t reserved2;	/* alignment */

	/* MCLK */
	uपूर्णांक32_t mclk_direction;

	uपूर्णांक16_t frame_pulse_width;
	uपूर्णांक16_t tdm_per_slot_padding_flag;
	uपूर्णांक32_t clks_control;
	uपूर्णांक32_t quirks;
	uपूर्णांक32_t bclk_delay;	/* guaranteed समय (ms) क्रम which BCLK
				 * will be driven, beक्रमe sending data
				 */
पूर्ण __packed;

/* HDA Configuration Request - SOF_IPC_DAI_HDA_CONFIG */
काष्ठा sof_ipc_dai_hda_params अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t link_dma_ch;
	uपूर्णांक32_t rate;
	uपूर्णांक32_t channels;
पूर्ण __packed;

/* ALH Configuration Request - SOF_IPC_DAI_ALH_CONFIG */
काष्ठा sof_ipc_dai_alh_params अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t stream_id;
	uपूर्णांक32_t rate;
	uपूर्णांक32_t channels;

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[13];
पूर्ण __packed;

/* DMIC Configuration Request - SOF_IPC_DAI_DMIC_CONFIG */

/* This काष्ठा is defined per 2ch PDM controller available in the platक्रमm.
 * Normally it is sufficient to set the used microphone specअगरic enables to 1
 * and keep other parameters as zero. The customizations are:
 *
 * 1. If a device mixes dअगरferent microphones types with dअगरferent polarity
 * and/or the असलolute polarity matters the PCM संकेत from a microphone
 * can be inverted with the controls.
 *
 * 2. If the microphones in a stereo pair करो not appear in captured stream
 * in desired order due to board schematics choises they can be swapped with
 * the clk_edge parameter.
 *
 * 3. If PDM bit errors are seen in capture (poor quality) the skew parameter
 * that delays the sampling समय of data by half cycles of DMIC source घड़ी
 * can be tried क्रम improvement. However there is no guarantee क्रम this to fix
 * data पूर्णांकegrity problems.
 */
काष्ठा sof_ipc_dai_dmic_pdm_ctrl अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक16_t id;		/**< PDM controller ID */

	uपूर्णांक16_t enable_mic_a;	/**< Use A (left) channel mic (0 or 1)*/
	uपूर्णांक16_t enable_mic_b;	/**< Use B (right) channel mic (0 or 1)*/

	uपूर्णांक16_t polarity_mic_a; /**< Optionally invert mic A संकेत (0 or 1) */
	uपूर्णांक16_t polarity_mic_b; /**< Optionally invert mic B संकेत (0 or 1) */

	uपूर्णांक16_t clk_edge;	/**< Optionally swap data घड़ी edge (0 or 1) */
	uपूर्णांक16_t skew;		/**< Adjust PDM data sampling vs. घड़ी (0..15) */

	uपूर्णांक16_t reserved[3];	/**< Make sure the total size is 4 bytes aligned */
पूर्ण __packed;

/* This काष्ठा contains the global settings क्रम all 2ch PDM controllers. The
 * version number used in configuration data is checked vs. version used by
 * device driver src/drivers/dmic.c need to match. It is incremented from
 * initial value 1 अगर updates करोne क्रम the to driver would alter the operation
 * of the microphone.
 *
 * Note: The microphone घड़ी (pdmclk_min, pdmclk_max, duty_min, duty_max)
 * parameters need to be set as defined in microphone data sheet. E.g. घड़ी
 * range 1.0 - 3.2 MHz is usually supported microphones. Some microphones are
 * multi-mode capable and there may be denied mic घड़ी frequencies between
 * the modes. In such हाल set the घड़ी range limits of the desired mode to
 * aव्योम the driver to set घड़ी to an illegal rate.
 *
 * The duty cycle could be set to 48-52% अगर not known. Generally these
 * parameters can be altered within data sheet specअगरied limits to match
 * required audio application perक्रमmance घातer.
 *
 * The microphone घड़ी needs to be usually about 50-80 बार the used audio
 * sample rate. With highest sample rates above 48 kHz this can relaxed
 * somewhat.
 *
 * The parameter wake_up_समय describes how दीर्घ समय the microphone needs
 * क्रम the data line to produce valid output from mic घड़ी start. The driver
 * will mute the captured audio क्रम the given समय. The min_घड़ी_on_समय
 * parameter is used to prevent too लघु घड़ी bursts to happen. The driver
 * will keep the घड़ी active after capture stop अगर this समय is not yet
 * met. The unit क्रम both is microseconds (us). Exceed of 100 ms will be
 * treated as an error.
 */
काष्ठा sof_ipc_dai_dmic_params अणु
	काष्ठा sof_ipc_hdr hdr;
	uपूर्णांक32_t driver_ipc_version;	/**< Version (1..N) */

	uपूर्णांक32_t pdmclk_min;	/**< Minimum microphone घड़ी in Hz (100000..N) */
	uपूर्णांक32_t pdmclk_max;	/**< Maximum microphone घड़ी in Hz (min...N) */

	uपूर्णांक32_t fअगरo_fs;	/**< FIFO sample rate in Hz (8000..96000) */
	uपूर्णांक32_t reserved_1;	/**< Reserved */
	uपूर्णांक16_t fअगरo_bits;	/**< FIFO word length (16 or 32) */
	uपूर्णांक16_t fअगरo_bits_b;	/**< Deprecated since firmware ABI 3.0.1 */

	uपूर्णांक16_t duty_min;	/**< Min. mic घड़ी duty cycle in % (20..80) */
	uपूर्णांक16_t duty_max;	/**< Max. mic घड़ी duty cycle in % (min..80) */

	uपूर्णांक32_t num_pdm_active; /**< Number of active pdm controllers. */
				 /**< Range is 1..SOF_DAI_INTEL_DMIC_NUM_CTRL */

	uपूर्णांक32_t wake_up_समय;      /**< Time from घड़ी start to data (us) */
	uपूर्णांक32_t min_घड़ी_on_समय; /**< Min. समय that clk is kept on (us) */
	uपूर्णांक32_t unmute_ramp_समय;  /**< Length of logarithmic gain ramp (ms) */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[5];

	/**< PDM controllers configuration */
	काष्ठा sof_ipc_dai_dmic_pdm_ctrl pdm[SOF_DAI_INTEL_DMIC_NUM_CTRL];
पूर्ण __packed;

#पूर्ण_अगर
