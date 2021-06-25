<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * wm8350.h - WM8903 audio codec पूर्णांकerface
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 */

#अगर_अघोषित _WM8350_H
#घोषणा _WM8350_H

#समावेश <sound/soc.h>
#समावेश <linux/mfd/wm8350/audपन.स>

क्रमागत wm8350_jack अणु
	WM8350_JDL = 1,
	WM8350_JDR = 2,
पूर्ण;

पूर्णांक wm8350_hp_jack_detect(काष्ठा snd_soc_component *component, क्रमागत wm8350_jack which,
			  काष्ठा snd_soc_jack *jack, पूर्णांक report);
पूर्णांक wm8350_mic_jack_detect(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_jack *jack,
			   पूर्णांक detect_report, पूर्णांक लघु_report);

#पूर्ण_अगर
