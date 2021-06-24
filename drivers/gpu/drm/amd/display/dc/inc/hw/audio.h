<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_AUDIO_H__
#घोषणा __DAL_AUDIO_H__

#समावेश "audio_types.h"

काष्ठा audio;

काष्ठा audio_funcs अणु

	bool (*endpoपूर्णांक_valid)(काष्ठा audio *audio);

	व्योम (*hw_init)(काष्ठा audio *audio);

	व्योम (*az_enable)(काष्ठा audio *audio);

	व्योम (*az_disable)(काष्ठा audio *audio);

	व्योम (*az_configure)(काष्ठा audio *audio,
		क्रमागत संकेत_type संकेत,
		स्थिर काष्ठा audio_crtc_info *crtc_info,
		स्थिर काष्ठा audio_info *audio_info);

	व्योम (*wall_dto_setup)(काष्ठा audio *audio,
		क्रमागत संकेत_type संकेत,
		स्थिर काष्ठा audio_crtc_info *crtc_info,
		स्थिर काष्ठा audio_pll_info *pll_info);

	व्योम (*destroy)(काष्ठा audio **audio);
पूर्ण;

काष्ठा audio अणु
	स्थिर काष्ठा audio_funcs *funcs;
	काष्ठा dc_context *ctx;
	अचिन्हित पूर्णांक inst;
	bool enabled;
पूर्ण;

#पूर्ण_अगर  /* __DAL_AUDIO__ */
