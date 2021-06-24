<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * aपंचांगel_ssc_dai.h - ALSA SSC पूर्णांकerface क्रम the Aपंचांगel  SoC
 *
 * Copyright (C) 2005 SAN People
 * Copyright (C) 2008 Aपंचांगel
 *
 * Author: Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 *         ATMEL CORP.
 *
 * Based on at91-ssc.c by
 * Frank Mandarino <fmandarino@endrelia.com>
 * Based on pxa2xx Platक्रमm drivers by
 * Liam Girdwood <lrg@slimlogic.co.uk>
 */

#अगर_अघोषित _ATMEL_SSC_DAI_H
#घोषणा _ATMEL_SSC_DAI_H

#समावेश <linux/types.h>
#समावेश <linux/aपंचांगel-ssc.h>

#समावेश "atmel-pcm.h"

/* SSC प्रणाली घड़ी ids */
#घोषणा ATMEL_SYSCLK_MCK	0 /* SSC uses AT91 MCK as प्रणाली घड़ी */

/* SSC भागider ids */
#घोषणा ATMEL_SSC_CMR_DIV	0 /* MCK भागider क्रम BCLK */
#घोषणा ATMEL_SSC_TCMR_PERIOD	1 /* BCLK भागider क्रम transmit FS */
#घोषणा ATMEL_SSC_RCMR_PERIOD	2 /* BCLK भागider क्रम receive FS */
/*
 * SSC direction masks
 */
#घोषणा SSC_सूची_MASK_UNUSED	0
#घोषणा SSC_सूची_MASK_PLAYBACK	1
#घोषणा SSC_सूची_MASK_CAPTURE	2

/*
 * SSC रेजिस्टर values that Aपंचांगel left out of <linux/aपंचांगel-ssc.h>.  These
 * are expected to be used with SSC_BF
 */
/* START bit field values */
#घोषणा SSC_START_CONTINUOUS	0
#घोषणा SSC_START_TX_RX		1
#घोषणा SSC_START_LOW_RF	2
#घोषणा SSC_START_HIGH_RF	3
#घोषणा SSC_START_FALLING_RF	4
#घोषणा SSC_START_RISING_RF	5
#घोषणा SSC_START_LEVEL_RF	6
#घोषणा SSC_START_EDGE_RF	7
#घोषणा SSS_START_COMPARE_0	8

/* CKI bit field values */
#घोषणा SSC_CKI_FALLING		0
#घोषणा SSC_CKI_RISING		1

/* CKO bit field values */
#घोषणा SSC_CKO_NONE		0
#घोषणा SSC_CKO_CONTINUOUS	1
#घोषणा SSC_CKO_TRANSFER	2

/* CKS bit field values */
#घोषणा SSC_CKS_DIV		0
#घोषणा SSC_CKS_CLOCK		1
#घोषणा SSC_CKS_PIN		2

/* FSEDGE bit field values */
#घोषणा SSC_FSEDGE_POSITIVE	0
#घोषणा SSC_FSEDGE_NEGATIVE	1

/* FSOS bit field values */
#घोषणा SSC_FSOS_NONE		0
#घोषणा SSC_FSOS_NEGATIVE	1
#घोषणा SSC_FSOS_POSITIVE	2
#घोषणा SSC_FSOS_LOW		3
#घोषणा SSC_FSOS_HIGH		4
#घोषणा SSC_FSOS_TOGGLE		5

#घोषणा START_DELAY		1

काष्ठा aपंचांगel_ssc_state अणु
	u32 ssc_cmr;
	u32 ssc_rcmr;
	u32 ssc_rfmr;
	u32 ssc_tcmr;
	u32 ssc_tfmr;
	u32 ssc_sr;
	u32 ssc_imr;
पूर्ण;


काष्ठा aपंचांगel_ssc_info अणु
	अक्षर *name;
	काष्ठा ssc_device *ssc;
	अचिन्हित लघु dir_mask;	/* 0=unused, 1=playback, 2=capture */
	अचिन्हित लघु initialized;	/* true अगर SSC has been initialized */
	अचिन्हित लघु daअगरmt;
	अचिन्हित लघु cmr_भाग;
	अचिन्हित लघु tcmr_period;
	अचिन्हित लघु rcmr_period;
	अचिन्हित पूर्णांक क्रमced_भागider;
	काष्ठा aपंचांगel_pcm_dma_params *dma_params[2];
	काष्ठा aपंचांगel_ssc_state ssc_state;
	अचिन्हित दीर्घ mck_rate;
पूर्ण;

पूर्णांक aपंचांगel_ssc_set_audio(पूर्णांक ssc_id);
व्योम aपंचांगel_ssc_put_audio(पूर्णांक ssc_id);

#पूर्ण_अगर /* _AT91_SSC_DAI_H */
