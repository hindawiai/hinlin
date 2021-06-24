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

#अगर_अघोषित __AUDIO_TYPES_H__
#घोषणा __AUDIO_TYPES_H__

#समावेश "signal_types.h"

#घोषणा AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS 20
#घोषणा MAX_HW_AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS 18
#घोषणा MULTI_CHANNEL_SPLIT_NO_ASSO_INFO 0xFFFFFFFF


काष्ठा audio_crtc_info अणु
	uपूर्णांक32_t h_total;
	uपूर्णांक32_t h_active;
	uपूर्णांक32_t v_active;
	uपूर्णांक32_t pixel_repetition;
	uपूर्णांक32_t requested_pixel_घड़ी_100Hz; /* in 100Hz */
	uपूर्णांक32_t calculated_pixel_घड़ी_100Hz; /* in 100Hz */
	uपूर्णांक32_t refresh_rate;
	क्रमागत dc_color_depth color_depth;
	bool पूर्णांकerlaced;
पूर्ण;
काष्ठा azalia_घड़ी_info अणु
	uपूर्णांक32_t pixel_घड़ी_in_10khz;
	uपूर्णांक32_t audio_dto_phase;
	uपूर्णांक32_t audio_dto_module;
	uपूर्णांक32_t audio_dto_wall_घड़ी_ratio;
पूर्ण;

क्रमागत audio_dto_source अणु
	DTO_SOURCE_UNKNOWN = 0,
	DTO_SOURCE_ID0,
	DTO_SOURCE_ID1,
	DTO_SOURCE_ID2,
	DTO_SOURCE_ID3,
	DTO_SOURCE_ID4,
	DTO_SOURCE_ID5
पूर्ण;

/* PLL inक्रमmation required क्रम AZALIA DTO calculation */

काष्ठा audio_pll_info अणु
	uपूर्णांक32_t dp_dto_source_घड़ी_in_khz;
	uपूर्णांक32_t feed_back_भागider;
	क्रमागत audio_dto_source dto_source;
	bool ss_enabled;
	uपूर्णांक32_t ss_percentage;
	uपूर्णांक32_t ss_percentage_भागider;
पूर्ण;

काष्ठा audio_channel_associate_info अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t ALL_CHANNEL_FL:4;
			uपूर्णांक32_t ALL_CHANNEL_FR:4;
			uपूर्णांक32_t ALL_CHANNEL_FC:4;
			uपूर्णांक32_t ALL_CHANNEL_Sub:4;
			uपूर्णांक32_t ALL_CHANNEL_SL:4;
			uपूर्णांक32_t ALL_CHANNEL_SR:4;
			uपूर्णांक32_t ALL_CHANNEL_BL:4;
			uपूर्णांक32_t ALL_CHANNEL_BR:4;
		पूर्ण bits;
		uपूर्णांक32_t u32all;
	पूर्ण;
पूर्ण;

काष्ठा audio_output अणु
	/* Front DIG id. */
	क्रमागत engine_id engine_id;
	/* encoder output संकेत */
	क्रमागत संकेत_type संकेत;
	/* video timing */
	काष्ठा audio_crtc_info crtc_info;
	/* PLL क्रम audio */
	काष्ठा audio_pll_info pll_info;
पूर्ण;

क्रमागत audio_payload अणु
	CHANNEL_SPLIT_MAPPINGCHANG = 0x9,
पूर्ण;

#पूर्ण_अगर /* __AUDIO_TYPES_H__ */
