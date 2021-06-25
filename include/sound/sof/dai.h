<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_DAI_H__
#घोषणा __INCLUDE_SOUND_SOF_DAI_H__

#समावेश <sound/sof/header.h>
#समावेश <sound/sof/dai-पूर्णांकel.h>
#समावेश <sound/sof/dai-imx.h>

/*
 * DAI Configuration.
 *
 * Each dअगरferent DAI type will have it's own काष्ठाure and IPC cmd.
 */

#घोषणा SOF_DAI_FMT_I2S		1 /**< I2S mode */
#घोषणा SOF_DAI_FMT_RIGHT_J	2 /**< Right Justअगरied mode */
#घोषणा SOF_DAI_FMT_LEFT_J	3 /**< Left Justअगरied mode */
#घोषणा SOF_DAI_FMT_DSP_A	4 /**< L data MSB after FRM LRC */
#घोषणा SOF_DAI_FMT_DSP_B	5 /**< L data MSB during FRM LRC */
#घोषणा SOF_DAI_FMT_PDM		6 /**< Pulse density modulation */

#घोषणा SOF_DAI_FMT_CONT	(1 << 4) /**< continuous घड़ी */
#घोषणा SOF_DAI_FMT_GATED	(0 << 4) /**< घड़ी is gated */

#घोषणा SOF_DAI_FMT_NB_NF	(0 << 8) /**< normal bit घड़ी + frame */
#घोषणा SOF_DAI_FMT_NB_IF	(2 << 8) /**< normal BCLK + inv FRM */
#घोषणा SOF_DAI_FMT_IB_NF	(3 << 8) /**< invert BCLK + nor FRM */
#घोषणा SOF_DAI_FMT_IB_IF	(4 << 8) /**< invert BCLK + FRM */

#घोषणा SOF_DAI_FMT_CBP_CFP	(0 << 12) /**< codec bclk provider & frame provider */
#घोषणा SOF_DAI_FMT_CBC_CFP	(2 << 12) /**< codec bclk consumer & frame provider */
#घोषणा SOF_DAI_FMT_CBP_CFC	(3 << 12) /**< codec bclk provider & frame consumer */
#घोषणा SOF_DAI_FMT_CBC_CFC	(4 << 12) /**< codec bclk consumer & frame consumer */

/* keep old definitions क्रम backwards compatibility */
#घोषणा SOF_DAI_FMT_CBM_CFM	SOF_DAI_FMT_CBP_CFP
#घोषणा SOF_DAI_FMT_CBS_CFM	SOF_DAI_FMT_CBC_CFP
#घोषणा SOF_DAI_FMT_CBM_CFS	SOF_DAI_FMT_CBP_CFC
#घोषणा SOF_DAI_FMT_CBS_CFS	SOF_DAI_FMT_CBC_CFC

#घोषणा SOF_DAI_FMT_FORMAT_MASK		0x000f
#घोषणा SOF_DAI_FMT_CLOCK_MASK		0x00f0
#घोषणा SOF_DAI_FMT_INV_MASK		0x0f00
#घोषणा SOF_DAI_FMT_CLOCK_PROVIDER_MASK	0xf000

/** \मrief Types of DAI */
क्रमागत sof_ipc_dai_type अणु
	SOF_DAI_INTEL_NONE = 0,		/**< None */
	SOF_DAI_INTEL_SSP,		/**< Intel SSP */
	SOF_DAI_INTEL_DMIC,		/**< Intel DMIC */
	SOF_DAI_INTEL_HDA,		/**< Intel HD/A */
	SOF_DAI_INTEL_ALH,		/**< Intel ALH  */
	SOF_DAI_IMX_SAI,		/**< i.MX SAI */
	SOF_DAI_IMX_ESAI,		/**< i.MX ESAI */
पूर्ण;

/* general purpose DAI configuration */
काष्ठा sof_ipc_dai_config अणु
	काष्ठा sof_ipc_cmd_hdr hdr;
	uपूर्णांक32_t type;		/**< DAI type - क्रमागत sof_ipc_dai_type */
	uपूर्णांक32_t dai_index;	/**< index of this type dai */

	/* physical protocol and घड़ीing */
	uपूर्णांक16_t क्रमmat;	/**< SOF_DAI_FMT_ */
	uपूर्णांक16_t reserved16;	/**< alignment */

	/* reserved क्रम future use */
	uपूर्णांक32_t reserved[8];

	/* HW specअगरic data */
	जोड़ अणु
		काष्ठा sof_ipc_dai_ssp_params ssp;
		काष्ठा sof_ipc_dai_dmic_params dmic;
		काष्ठा sof_ipc_dai_hda_params hda;
		काष्ठा sof_ipc_dai_alh_params alh;
		काष्ठा sof_ipc_dai_esai_params esai;
		काष्ठा sof_ipc_dai_sai_params sai;
	पूर्ण;
पूर्ण __packed;

#पूर्ण_अगर
