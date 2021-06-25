<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __DRM_I2C_CH7006_H__
#घोषणा __DRM_I2C_CH7006_H__

/**
 * काष्ठा ch7006_encoder_params
 *
 * Describes how the ch7006 is wired up with the GPU. It should be
 * used as the @params parameter of its @set_config method.
 *
 * See "http://www.chrontel.com/pdf/7006.pdf" क्रम their precise
 * meaning.
 */
काष्ठा ch7006_encoder_params अणु
	क्रमागत अणु
		CH7006_FORMAT_RGB16 = 0,
		CH7006_FORMAT_YCrCb24m16,
		CH7006_FORMAT_RGB24m16,
		CH7006_FORMAT_RGB15,
		CH7006_FORMAT_RGB24m12C,
		CH7006_FORMAT_RGB24m12I,
		CH7006_FORMAT_RGB24m8,
		CH7006_FORMAT_RGB16m8,
		CH7006_FORMAT_RGB15m8,
		CH7006_FORMAT_YCrCb24m8,
	पूर्ण input_क्रमmat;

	क्रमागत अणु
		CH7006_CLOCK_SLAVE = 0,
		CH7006_CLOCK_MASTER,
	पूर्ण घड़ी_mode;

	क्रमागत अणु
		CH7006_CLOCK_EDGE_NEG = 0,
		CH7006_CLOCK_EDGE_POS,
	पूर्ण घड़ी_edge;

	पूर्णांक xcm, pcm;

	क्रमागत अणु
		CH7006_SYNC_SLAVE = 0,
		CH7006_SYNC_MASTER,
	पूर्ण sync_direction;

	क्रमागत अणु
		CH7006_SYNC_SEPARATED = 0,
		CH7006_SYNC_EMBEDDED,
	पूर्ण sync_encoding;

	क्रमागत अणु
		CH7006_POUT_1_8V = 0,
		CH7006_POUT_3_3V,
	पूर्ण pout_level;

	क्रमागत अणु
		CH7006_ACTIVE_HSYNC = 0,
		CH7006_ACTIVE_DSTART,
	पूर्ण active_detect;
पूर्ण;

#पूर्ण_अगर
