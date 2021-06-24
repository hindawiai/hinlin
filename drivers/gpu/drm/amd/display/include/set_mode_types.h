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

#अगर_अघोषित __DAL_SET_MODE_TYPES_H__
#घोषणा __DAL_SET_MODE_TYPES_H__

#समावेश "dc_types.h"
#समावेश <linux/hdmi.h>

/* Info frame packet status */
क्रमागत info_frame_flag अणु
	INFO_PACKET_PACKET_INVALID = 0,
	INFO_PACKET_PACKET_VALID = 1,
	INFO_PACKET_PACKET_RESET = 2,
	INFO_PACKET_PACKET_UPDATE_SCAN_TYPE = 8
पूर्ण;

काष्ठा hdmi_info_frame_header अणु
	uपूर्णांक8_t info_frame_type;
	uपूर्णांक8_t version;
	uपूर्णांक8_t length;
पूर्ण;

#आशय pack(push)
#आशय pack(1)

काष्ठा info_packet_raw_data अणु
	uपूर्णांक8_t hb0;
	uपूर्णांक8_t hb1;
	uपूर्णांक8_t hb2;
	uपूर्णांक8_t sb[28]; /* sb0~sb27 */
पूर्ण;

जोड़ hdmi_info_packet अणु
	काष्ठा avi_info_frame अणु
		काष्ठा hdmi_info_frame_header header;

		uपूर्णांक8_t CHECK_SUM:8;

		uपूर्णांक8_t S0_S1:2;
		uपूर्णांक8_t B0_B1:2;
		uपूर्णांक8_t A0:1;
		uपूर्णांक8_t Y0_Y1_Y2:3;

		uपूर्णांक8_t R0_R3:4;
		uपूर्णांक8_t M0_M1:2;
		uपूर्णांक8_t C0_C1:2;

		uपूर्णांक8_t SC0_SC1:2;
		uपूर्णांक8_t Q0_Q1:2;
		uपूर्णांक8_t EC0_EC2:3;
		uपूर्णांक8_t ITC:1;

		uपूर्णांक8_t VIC0_VIC7:8;

		uपूर्णांक8_t PR0_PR3:4;
		uपूर्णांक8_t CN0_CN1:2;
		uपूर्णांक8_t YQ0_YQ1:2;

		uपूर्णांक16_t bar_top;
		uपूर्णांक16_t bar_bottom;
		uपूर्णांक16_t bar_left;
		uपूर्णांक16_t bar_right;

		uपूर्णांक8_t F140_F143:4;
		uपूर्णांक8_t ACE0_ACE3:4;

		uपूर्णांक8_t reserved[13];
	पूर्ण bits;

	काष्ठा info_packet_raw_data packet_raw_data;
पूर्ण;

#आशय pack(pop)

#पूर्ण_अगर /* __DAL_SET_MODE_TYPES_H__ */
