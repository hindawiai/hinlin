<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/wm5100.h -- Platक्रमm data क्रम WM5100
 *
 * Copyright 2011 Wolfson Microelectronics. PLC.
 */

#अगर_अघोषित __LINUX_SND_WM5100_H
#घोषणा __LINUX_SND_WM5100_H

क्रमागत wm5100_in_mode अणु
	WM5100_IN_SE = 0,
	WM5100_IN_DIFF = 1,
	WM5100_IN_DMIC = 2,
पूर्ण;

क्रमागत wm5100_dmic_sup अणु
	WM5100_DMIC_SUP_MICVDD = 0,
	WM5100_DMIC_SUP_MICBIAS1 = 1,
	WM5100_DMIC_SUP_MICBIAS2 = 2,
	WM5100_DMIC_SUP_MICBIAS3 = 3,
पूर्ण;

क्रमागत wm5100_micdet_bias अणु
	WM5100_MICDET_MICBIAS1 = 0,
	WM5100_MICDET_MICBIAS2 = 1,
	WM5100_MICDET_MICBIAS3 = 2,
पूर्ण;

काष्ठा wm5100_jack_mode अणु
	क्रमागत wm5100_micdet_bias bias;
	पूर्णांक hp_pol;
	पूर्णांक micd_src;
पूर्ण;

#घोषणा WM5100_GPIO_SET 0x10000

काष्ठा wm5100_pdata अणु
	पूर्णांक reset;      /** GPIO controlling /RESET, अगर any */
	पूर्णांक lकरो_ena;    /** GPIO controlling LODENA, अगर any */
	पूर्णांक hp_pol;     /** GPIO controlling headset polarity, अगर any */
	पूर्णांक irq_flags;
	पूर्णांक gpio_base;

	काष्ठा wm5100_jack_mode jack_modes[2];

	/* Input pin mode selection */
	क्रमागत wm5100_in_mode in_mode[4];

	/* DMIC supply selection */
	क्रमागत wm5100_dmic_sup dmic_sup[4];

	पूर्णांक gpio_शेषs[6];
पूर्ण;

#पूर्ण_अगर
