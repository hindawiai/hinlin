<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * Copyright 2019 NXP
 *
 * Author: Daniel Baluta <daniel.baluta@nxp.com>
 */

#अगर_अघोषित __INCLUDE_SOUND_SOF_DAI_IMX_H__
#घोषणा __INCLUDE_SOUND_SOF_DAI_IMX_H__

#समावेश <sound/sof/header.h>

/* ESAI Configuration Request - SOF_IPC_DAI_ESAI_CONFIG */
काष्ठा sof_ipc_dai_esai_params अणु
	काष्ठा sof_ipc_hdr hdr;

	/* MCLK */
	uपूर्णांक16_t reserved1;
	uपूर्णांक16_t mclk_id;
	uपूर्णांक32_t mclk_direction;

	uपूर्णांक32_t mclk_rate;	/* MCLK frequency in Hz */
	uपूर्णांक32_t fsync_rate;	/* FSYNC frequency in Hz */
	uपूर्णांक32_t bclk_rate;	/* BCLK frequency in Hz */

	/* TDM */
	uपूर्णांक32_t tdm_slots;
	uपूर्णांक32_t rx_slots;
	uपूर्णांक32_t tx_slots;
	uपूर्णांक16_t tdm_slot_width;
	uपूर्णांक16_t reserved2;	/* alignment */
पूर्ण __packed;

/* SAI Configuration Request - SOF_IPC_DAI_SAI_CONFIG */
काष्ठा sof_ipc_dai_sai_params अणु
	काष्ठा sof_ipc_hdr hdr;

	/* MCLK */
	uपूर्णांक16_t reserved1;
	uपूर्णांक16_t mclk_id;
	uपूर्णांक32_t mclk_direction;

	uपूर्णांक32_t mclk_rate;	/* MCLK frequency in Hz */
	uपूर्णांक32_t fsync_rate;	/* FSYNC frequency in Hz */
	uपूर्णांक32_t bclk_rate;	/* BCLK frequency in Hz */

	/* TDM */
	uपूर्णांक32_t tdm_slots;
	uपूर्णांक32_t rx_slots;
	uपूर्णांक32_t tx_slots;
	uपूर्णांक16_t tdm_slot_width;
	uपूर्णांक16_t reserved2;	/* alignment */
पूर्ण __packed;
#पूर्ण_अगर
