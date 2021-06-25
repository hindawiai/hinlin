<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
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

#अगर_अघोषित __DRM_I2C_SIL164_H__
#घोषणा __DRM_I2C_SIL164_H__

/**
 * काष्ठा sil164_encoder_params
 *
 * Describes how the sil164 is connected to the GPU. It should be used
 * as the @params parameter of its @set_config method.
 *
 * See "http://www.siliconimage.com/docs/SiI-DS-0021-E-164.pdf".
 */
काष्ठा sil164_encoder_params अणु
	क्रमागत अणु
		SIL164_INPUT_EDGE_FALLING = 0,
		SIL164_INPUT_EDGE_RISING
	पूर्ण input_edge;

	क्रमागत अणु
		SIL164_INPUT_WIDTH_12BIT = 0,
		SIL164_INPUT_WIDTH_24BIT
	पूर्ण input_width;

	क्रमागत अणु
		SIL164_INPUT_SINGLE_EDGE = 0,
		SIL164_INPUT_DUAL_EDGE
	पूर्ण input_dual;

	क्रमागत अणु
		SIL164_PLL_FILTER_ON = 0,
		SIL164_PLL_FILTER_OFF,
	पूर्ण pll_filter;

	पूर्णांक input_skew; /** < Allowed range [-4, 3], use 0 क्रम no de-skew. */
	पूर्णांक duallink_skew; /** < Allowed range [-4, 3]. */
पूर्ण;

#पूर्ण_अगर
