<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2009 Samsung Electronics Co. Ltd
 * Author: Jaswinder Singh <jassi.brar@samsung.com>
 */

/* The machine init code calls s3c*_ac97_setup_gpio with
 * one of these defines in order to select appropriate bank
 * of GPIO क्रम AC97 pins
 */
#घोषणा S3C64XX_AC97_GPD  0
#घोषणा S3C64XX_AC97_GPE  1

#समावेश <linux/dmaengine.h>

बाह्य व्योम s3c64xx_ac97_setup_gpio(पूर्णांक);

काष्ठा samsung_i2s_type अणु
/* If the Primary DAI has 5.1 Channels */
#घोषणा QUIRK_PRI_6CHAN		(1 << 0)
/* If the I2S block has a Stereo Overlay Channel */
#घोषणा QUIRK_SEC_DAI		(1 << 1)
/*
 * If the I2S block has no पूर्णांकernal prescalar or MUX (I2SMOD[10] bit)
 * The Machine driver must provide suitably set घड़ी to the I2S block.
 */
#घोषणा QUIRK_NO_MUXPSR		(1 << 2)
#घोषणा QUIRK_NEED_RSTCLR	(1 << 3)
#घोषणा QUIRK_SUPPORTS_TDM	(1 << 4)
#घोषणा QUIRK_SUPPORTS_IDMA	(1 << 5)
	/* Quirks of the I2S controller */
	u32 quirks;
	dma_addr_t idma_addr;
पूर्ण;

/**
 * काष्ठा s3c_audio_pdata - common platक्रमm data क्रम audio device drivers
 * @cfg_gpio: Callback function to setup mux'ed pins in I2S/PCM/AC97 mode
 */
काष्ठा s3c_audio_pdata अणु
	पूर्णांक (*cfg_gpio)(काष्ठा platक्रमm_device *);
	dma_filter_fn dma_filter;
	व्योम *dma_playback;
	व्योम *dma_capture;
	व्योम *dma_play_sec;
	व्योम *dma_capture_mic;
	काष्ठा samsung_i2s_type type;
पूर्ण;
