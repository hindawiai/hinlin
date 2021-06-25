<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * at91-pcm.h - ALSA PCM पूर्णांकerface क्रम the Aपंचांगel AT91 SoC.
 *
 *  Copyright (C) 2005 SAN People
 *  Copyright (C) 2008 Aपंचांगel
 *
 * Authors: Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 *
 * Based on at91-pcm. by:
 * Frank Mandarino <fmandarino@endrelia.com>
 * Copyright 2006 Endrelia Technologies Inc.
 *
 * Based on pxa2xx-pcm.c by:
 *
 * Author:	Nicolas Pitre
 * Created:	Nov 30, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 */

#अगर_अघोषित _ATMEL_PCM_H
#घोषणा _ATMEL_PCM_H

#समावेश <linux/aपंचांगel-ssc.h>

#घोषणा ATMEL_SSC_DMABUF_SIZE	(64 * 1024)

/*
 * Registers and status bits that are required by the PCM driver.
 */
काष्ठा aपंचांगel_pdc_regs अणु
	अचिन्हित पूर्णांक	xpr;		/* PDC recv/trans poपूर्णांकer */
	अचिन्हित पूर्णांक	xcr;		/* PDC recv/trans counter */
	अचिन्हित पूर्णांक	xnpr;		/* PDC next recv/trans poपूर्णांकer */
	अचिन्हित पूर्णांक	xncr;		/* PDC next recv/trans counter */
	अचिन्हित पूर्णांक	ptcr;		/* PDC transfer control */
पूर्ण;

काष्ठा aपंचांगel_ssc_mask अणु
	u32	ssc_enable;		/* SSC recv/trans enable */
	u32	ssc_disable;		/* SSC recv/trans disable */
	u32	ssc_error;		/* SSC error conditions */
	u32	ssc_endx;		/* SSC ENDTX or ENDRX */
	u32	ssc_endbuf;		/* SSC TXBUFE or RXBUFF */
	u32	pdc_enable;		/* PDC recv/trans enable */
	u32	pdc_disable;		/* PDC recv/trans disable */
पूर्ण;

/*
 * This काष्ठाure, shared between the PCM driver and the पूर्णांकerface,
 * contains all inक्रमmation required by the PCM driver to perक्रमm the
 * PDC DMA operation.  All fields except dma_पूर्णांकr_handler() are initialized
 * by the पूर्णांकerface.  The dma_पूर्णांकr_handler() poपूर्णांकer is set by the PCM
 * driver and called by the पूर्णांकerface SSC पूर्णांकerrupt handler अगर it is
 * non-शून्य.
 */
काष्ठा aपंचांगel_pcm_dma_params अणु
	अक्षर *name;			/* stream identअगरier */
	पूर्णांक pdc_xfer_size;		/* PDC counter increment in bytes */
	काष्ठा ssc_device *ssc;		/* SSC device क्रम stream */
	काष्ठा aपंचांगel_pdc_regs *pdc;	/* PDC receive or transmit रेजिस्टरs */
	काष्ठा aपंचांगel_ssc_mask *mask;	/* SSC & PDC status bits */
	काष्ठा snd_pcm_substream *substream;
	व्योम (*dma_पूर्णांकr_handler)(u32, काष्ठा snd_pcm_substream *);
पूर्ण;

/*
 * SSC रेजिस्टर access (since ssc_ग_लिखोl() / ssc_पढ़ोl() require literal name)
 */
#घोषणा ssc_पढ़ोx(base, reg)            (__raw_पढ़ोl((base) + (reg)))
#घोषणा ssc_ग_लिखोx(base, reg, value)    __raw_ग_लिखोl((value), (base) + (reg))

#अगर IS_ENABLED(CONFIG_SND_ATMEL_SOC_PDC)
पूर्णांक aपंचांगel_pcm_pdc_platक्रमm_रेजिस्टर(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक aपंचांगel_pcm_pdc_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_ATMEL_SOC_DMA)
पूर्णांक aपंचांगel_pcm_dma_platक्रमm_रेजिस्टर(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक aपंचांगel_pcm_dma_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ATMEL_PCM_H */
