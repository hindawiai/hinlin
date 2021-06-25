<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Alchemy ALSA ASoC audio support.
 *
 * (c) 2007-2011 MSC Vertriebsges.m.b.H.,
 *	Manuel Lauss <manuel.lauss@gmail.com>
 */

#अगर_अघोषित _AU1X_PCM_H
#घोषणा _AU1X_PCM_H

काष्ठा au1xpsc_audio_data अणु
	व्योम __iomem *mmio;

	अचिन्हित दीर्घ cfg;
	अचिन्हित दीर्घ rate;

	काष्ठा snd_soc_dai_driver dai_drv;

	अचिन्हित दीर्घ pm[2];
	काष्ठा mutex lock;
	पूर्णांक dmaids[2];
पूर्ण;

/* easy access macros */
#घोषणा PSC_CTRL(x)	((x)->mmio + PSC_CTRL_OFFSET)
#घोषणा PSC_SEL(x)	((x)->mmio + PSC_SEL_OFFSET)
#घोषणा I2S_STAT(x)	((x)->mmio + PSC_I2SSTAT_OFFSET)
#घोषणा I2S_CFG(x)	((x)->mmio + PSC_I2SCFG_OFFSET)
#घोषणा I2S_PCR(x)	((x)->mmio + PSC_I2SPCR_OFFSET)
#घोषणा AC97_CFG(x)	((x)->mmio + PSC_AC97CFG_OFFSET)
#घोषणा AC97_CDC(x)	((x)->mmio + PSC_AC97CDC_OFFSET)
#घोषणा AC97_EVNT(x)	((x)->mmio + PSC_AC97EVNT_OFFSET)
#घोषणा AC97_PCR(x)	((x)->mmio + PSC_AC97PCR_OFFSET)
#घोषणा AC97_RST(x)	((x)->mmio + PSC_AC97RST_OFFSET)
#घोषणा AC97_STAT(x)	((x)->mmio + PSC_AC97STAT_OFFSET)

#पूर्ण_अगर
