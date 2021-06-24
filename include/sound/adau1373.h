<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Analog Devices ADAU1373 Audio Codec drive
 *
 * Copyright 2011 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित __SOUND_ADAU1373_H__
#घोषणा __SOUND_ADAU1373_H__

क्रमागत adau1373_micbias_voltage अणु
	ADAU1373_MICBIAS_2_9V = 0,
	ADAU1373_MICBIAS_2_2V = 1,
	ADAU1373_MICBIAS_2_6V = 2,
	ADAU1373_MICBIAS_1_8V = 3,
पूर्ण;

#घोषणा ADAU1373_DRC_SIZE 13

काष्ठा adau1373_platक्रमm_data अणु
	bool input_dअगरferential[4];
	bool lineout_dअगरferential;
	bool lineout_ground_sense;

	अचिन्हित पूर्णांक num_drc;
	uपूर्णांक8_t drc_setting[3][ADAU1373_DRC_SIZE];

	क्रमागत adau1373_micbias_voltage micbias1;
	क्रमागत adau1373_micbias_voltage micbias2;
पूर्ण;

#पूर्ण_अगर
