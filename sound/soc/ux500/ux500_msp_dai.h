<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Roger Nilsson <roger.xr.nilsson@stericsson.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#अगर_अघोषित UX500_msp_dai_H
#घोषणा UX500_msp_dai_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>

#समावेश "ux500_msp_i2s.h"

#घोषणा UX500_NBR_OF_DAI	4

#घोषणा UX500_I2S_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |	\
			SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)

#घोषणा UX500_I2S_FORMATS (SNDRV_PCM_FMTBIT_S16_LE)

#घोषणा FRAME_PER_SINGLE_SLOT_8_KHZ		31
#घोषणा FRAME_PER_SINGLE_SLOT_16_KHZ	124
#घोषणा FRAME_PER_SINGLE_SLOT_44_1_KHZ	63
#घोषणा FRAME_PER_SINGLE_SLOT_48_KHZ	49
#घोषणा FRAME_PER_2_SLOTS				31
#घोषणा FRAME_PER_8_SLOTS				138
#घोषणा FRAME_PER_16_SLOTS				277

#घोषणा UX500_MSP_INTERNAL_CLOCK_FREQ  40000000
#घोषणा UX500_MSP1_INTERNAL_CLOCK_FREQ UX500_MSP_INTERNAL_CLOCK_FREQ

#घोषणा UX500_MSP_MIN_CHANNELS		1
#घोषणा UX500_MSP_MAX_CHANNELS		8

#घोषणा PLAYBACK_CONFIGURED		1
#घोषणा CAPTURE_CONFIGURED		2

क्रमागत ux500_msp_घड़ी_id अणु
	UX500_MSP_MASTER_CLOCK,
पूर्ण;

काष्ठा ux500_msp_i2s_drvdata अणु
	काष्ठा ux500_msp *msp;
	काष्ठा regulator *reg_vape;
	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक tx_mask;
	अचिन्हित पूर्णांक rx_mask;
	पूर्णांक slots;
	पूर्णांक slot_width;

	/* Clocks */
	अचिन्हित पूर्णांक master_clk;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;

	/* Regulators */
	पूर्णांक vape_opp_स्थिरraपूर्णांक;
पूर्ण;

पूर्णांक ux500_msp_dai_set_data_delay(काष्ठा snd_soc_dai *dai, पूर्णांक delay);

#पूर्ण_अगर
