<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * hdmi-audio.c -- OMAP4+ DSS HDMI audio support library
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#अगर_अघोषित __OMAP_HDMI_AUDIO_H__
#घोषणा __OMAP_HDMI_AUDIO_H__

#समावेश <linux/platक्रमm_data/omapdss.h>

काष्ठा omap_dss_audio अणु
	काष्ठा snd_aes_iec958 *iec;
	काष्ठा snd_cea_861_aud_अगर *cea;
पूर्ण;

काष्ठा omap_hdmi_audio_ops अणु
	पूर्णांक (*audio_startup)(काष्ठा device *dev,
			     व्योम (*पात_cb)(काष्ठा device *dev));
	पूर्णांक (*audio_shutकरोwn)(काष्ठा device *dev);
	पूर्णांक (*audio_start)(काष्ठा device *dev);
	व्योम (*audio_stop)(काष्ठा device *dev);
	पूर्णांक (*audio_config)(काष्ठा device *dev,
			    काष्ठा omap_dss_audio *dss_audio);
पूर्ण;

/* HDMI audio initalization data */
काष्ठा omap_hdmi_audio_pdata अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक version;
	phys_addr_t audio_dma_addr;

	स्थिर काष्ठा omap_hdmi_audio_ops *ops;
पूर्ण;

#पूर्ण_अगर /* __OMAP_HDMI_AUDIO_H__ */
