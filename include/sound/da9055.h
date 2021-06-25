<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DA9055 ALSA Soc codec driver
 *
 * Copyright (c) 2012 Dialog Semiconductor
 *
 * Tested on (Samsung SMDK6410 board + DA9055 EVB) using I2S and I2C
 * Written by David Chen <david.chen@diasemi.com> and
 * Ashish Chavan <ashish.chavan@kpitcummins.com>
 */

#अगर_अघोषित __SOUND_DA9055_H__
#घोषणा __SOUND_DA9055_H__

क्रमागत da9055_micbias_voltage अणु
	DA9055_MICBIAS_1_6V = 0,
	DA9055_MICBIAS_1_8V = 1,
	DA9055_MICBIAS_2_1V = 2,
	DA9055_MICBIAS_2_2V = 3,
पूर्ण;

काष्ठा da9055_platक्रमm_data अणु
	/* Selects which of the two MicBias pins acts as the bias source */
	bool micbias_source;
	/* Selects the micbias voltage */
	क्रमागत da9055_micbias_voltage micbias;
पूर्ण;

#पूर्ण_अगर
