<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm2200.h -- Platक्रमm data क्रम WM2200
 *
 * Copyright 2012 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM2200_H
#घोषणा __LINUX_SND_WM2200_H

#घोषणा WM2200_GPIO_SET 0x10000
#घोषणा WM2200_MAX_MICBIAS 2

क्रमागत wm2200_in_mode अणु
	WM2200_IN_SE = 0,
	WM2200_IN_DIFF = 1,
	WM2200_IN_DMIC = 2,
पूर्ण;

क्रमागत wm2200_dmic_sup अणु
	WM2200_DMIC_SUP_MICVDD = 0,
	WM2200_DMIC_SUP_MICBIAS1 = 1,
	WM2200_DMIC_SUP_MICBIAS2 = 2,
पूर्ण;

क्रमागत wm2200_mbias_lvl अणु
	WM2200_MBIAS_LVL_1V5 = 1,
	WM2200_MBIAS_LVL_1V8 = 2,
	WM2200_MBIAS_LVL_1V9 = 3,
	WM2200_MBIAS_LVL_2V0 = 4,
	WM2200_MBIAS_LVL_2V2 = 5,
	WM2200_MBIAS_LVL_2V4 = 6,
	WM2200_MBIAS_LVL_2V5 = 7,
	WM2200_MBIAS_LVL_2V6 = 8,
पूर्ण;

काष्ठा wm2200_micbias अणु
	क्रमागत wm2200_mbias_lvl mb_lvl;      /** Regulated voltage */
	अचिन्हित पूर्णांक disअक्षरge:1;          /** Actively disअक्षरge */
	अचिन्हित पूर्णांक fast_start:1;         /** Enable aggressive startup ramp rate */
	अचिन्हित पूर्णांक bypass:1;             /** Use bypass mode */
पूर्ण;

काष्ठा wm2200_pdata अणु
	पूर्णांक reset;      /** GPIO controlling /RESET, अगर any */
	पूर्णांक lकरो_ena;    /** GPIO controlling LODENA, अगर any */
	पूर्णांक irq_flags;

	पूर्णांक gpio_शेषs[4];

	क्रमागत wm2200_in_mode in_mode[3];
	क्रमागत wm2200_dmic_sup dmic_sup[3];

	/** MICBIAS configurations */
	काष्ठा wm2200_micbias micbias[WM2200_MAX_MICBIAS];
पूर्ण;

#पूर्ण_अगर
