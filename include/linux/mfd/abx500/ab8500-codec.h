<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#अगर_अघोषित AB8500_CORE_CODEC_H
#घोषणा AB8500_CORE_CODEC_H

/* Mic-types */
क्रमागत amic_type अणु
	AMIC_TYPE_SINGLE_ENDED,
	AMIC_TYPE_DIFFERENTIAL
पूर्ण;

/* Mic-biases */
क्रमागत amic_micbias अणु
	AMIC_MICBIAS_VAMIC1,
	AMIC_MICBIAS_VAMIC2,
	AMIC_MICBIAS_UNKNOWN
पूर्ण;

/* Bias-voltage */
क्रमागत ear_cm_voltage अणु
	EAR_CMV_0_95V,
	EAR_CMV_1_10V,
	EAR_CMV_1_27V,
	EAR_CMV_1_58V,
	EAR_CMV_UNKNOWN
पूर्ण;

/* Analog microphone settings */
काष्ठा amic_settings अणु
	क्रमागत amic_type mic1_type;
	क्रमागत amic_type mic2_type;
	क्रमागत amic_micbias mic1a_micbias;
	क्रमागत amic_micbias mic1b_micbias;
	क्रमागत amic_micbias mic2_micbias;
पूर्ण;

/* Platक्रमm data काष्ठाure क्रम the audio-parts of the AB8500 */
काष्ठा ab8500_codec_platक्रमm_data अणु
	काष्ठा amic_settings amics;
	क्रमागत ear_cm_voltage ear_cmv;
पूर्ण;

#पूर्ण_अगर
